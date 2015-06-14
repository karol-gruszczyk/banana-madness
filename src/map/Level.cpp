#include "Level.h"

Level::Level(sf::RenderWindow& windowHandle, const char** levelPaths) :
	windowHandle(&windowHandle),
	levelPaths(levelPaths)
{
	srand((unsigned)time(nullptr));
	if (!font.loadFromFile(SIMPLE_FONT_PATH))
		throw FileLoadException(SIMPLE_FONT_PATH);
	text.setFont(font);
	text.setColor(sf::Color::Black);
	text.setCharacterSize(30);

	if (!gameOverFont.loadFromFile(HEADER_FONT_PATH))
		throw FileLoadException(HEADER_FONT_PATH);
	gameOverText.setFont(gameOverFont);
	gameOverText.setCharacterSize(100);
	
	if (!levelClearedSoundBuffer.loadFromFile(LEVEL_CLEARED_SOUND_PATH))
		throw FileLoadException(LEVEL_CLEARED_SOUND_PATH);
	levelClearedSound.setBuffer(levelClearedSoundBuffer);

	lifes = 3;
}

Level::operator bool()
{
	return loaded;
}

void Level::loadMap(std::string mapPath)
{
	MapParser parser(mapPath);
	parser.parseFile();
	player = std::make_unique<Playable>(parser.getPlayerSpritePaths(), SPRITE_DELTA_TIME, parser.getPlayerPosition());
	enemies = std::move(parser.getEnemies());
	blocks = std::move(parser.getBlockArray());

	backgroundImage.load(parser.getBackgroundImagePath());
	backgroundImage.setSize();
	auto musicPath = parser.getBackgroundMusicPath();
	if (!levelMusic.openFromFile(musicPath))
		throw FileLoadException(musicPath);

	gameView = sf::View(sf::FloatRect(0.f, 0.f, (float)windowHandle->getSize().x, (float)windowHandle->getSize().y));

	if (!gameOverSoundBuffer.loadFromFile(GAME_OVER_SOUND_PATH))
		throw FileLoadException(GAME_OVER_SOUND_PATH);
	gameOverSound.setBuffer(gameOverSoundBuffer);

	gameOverTextCounter = 0;
	gameOverText.setString("");
	loaded = true;
}

void Level::runFrame(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys, std::vector<unsigned> releasedKeys)
{
	if (player->isAlive())
	{
		if (levelMusic.getStatus() != sf::Music::Status::Playing && gameState == BananaMadness::GameState::IN_GAME)
			levelMusic.play();
		handleInput(gameState, pressedKeys, releasedKeys);
		player->update(blocks, pressedKeys, releasedKeys);
		for (auto enemyIt = enemies->begin(); enemyIt != enemies->end();)
		{
			(*enemyIt)->update(blocks);

			if ((*enemyIt)->isIntersectingWith(player->getGlobalBounds()))
				player->kill();
			if (!(*enemyIt)->isAlive())
				enemyIt = enemies->erase(enemyIt);
			else
				enemyIt++;
		}


		if (player->hasReachedEndOfMap())
		{
			levelMusic.stop();
			levelClearedSound.play();
			gameState = BananaMadness::LEVEL_CLEARED;
		}
	}
	else
	{
		if (gameOverSound.getStatus() != sf::Sound::Playing)
		{
			levelMusic.stop();
			gameOverSound.play();
		}
		else if (gameOverSound.getPlayingOffset() > sf::seconds(GAME_OVER_DELAY))
		{
			lifes--;
			gameState = BananaMadness::GameState::GAME_OVER;
		}
		else
		{
			if (gameOverSound.getPlayingOffset() / sf::milliseconds(100) >= gameOverTextCounter)
			{
				gameOverTextCounter++;
				gameOverText.setString("LOSER");
				sf::Vector2f textPos = { float(rand() % int(windowHandle->getSize().x - gameOverText.getLocalBounds().width)), 
					float(rand() % int(windowHandle->getSize().y - gameOverText.getLocalBounds().height)) };
				gameOverText.setPosition(textPos);
				gameOverText.setRotation(float(rand() % 90) - 45);
				gameOverText.setColor(sf::Color( rand() % 256, rand() % 256, rand() % 256 ));
			}
		}
	}
	render();
}

void Level::render()
{
	deltaTime = lastFrameTime.restart().asMicroseconds() / 1000.f;
	auto bgView = sf::View(sf::FloatRect(0.f, 0.f, (float)windowHandle->getSize().x, (float)windowHandle->getSize().y));
	windowHandle->setView(bgView);
	backgroundImage.render();

	windowHandle->setView(gameView);
	float winWidth2 = windowHandle->getSize().x / 2.f;
	float mapWidth = BLOCK_SIZE * (float)blocks->size();
	float xCenter = std::max(std::min(player->getPosition().x, mapWidth - winWidth2), winWidth2);
	float yCenter = gameView.getCenter().y;
	gameView.setCenter(xCenter, yCenter);

	for (auto& i : *blocks)
		for (auto& j : i)
			if (j)
				j->render();
	for (auto& enemy : *enemies)
		enemy->render();
	player->render();

	windowHandle->setView(bgView);
	std::ostringstream stream;
	stream << "Lifes left: " << lifes;
	text.setString(stream.str());
	text.setPosition({ windowHandle->getSize().x / 2.f, 0.f });
	windowHandle->draw(text);
	windowHandle->draw(gameOverText);
}

void Level::handleInput(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys, std::vector<unsigned> releasedKeys)
{
	for (auto& i : releasedKeys)
	{
		switch (i)
		{
		case sf::Keyboard::Escape:
			levelMusic.pause();
			gameState = BananaMadness::GameState::PAUSED;
			break;
		}

	}
}

void Level::reloadLevel()
{
	loadMap(levelPaths[currentLevel]);
}

void Level::loadLevel(unsigned levelIndex)
{
	currentLevel = levelIndex;
	loadMap(levelPaths[levelIndex]);
}

unsigned Level::getCurrentLevel()
{
	return currentLevel;
}
