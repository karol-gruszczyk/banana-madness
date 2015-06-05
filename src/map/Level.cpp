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
	text.setCharacterSize(15);

	if (!gameOverFont.loadFromFile(HEADER_FONT_PATH))
		throw FileLoadException(HEADER_FONT_PATH);
	gameOverText.setFont(gameOverFont);
	gameOverText.setCharacterSize(100);
}

Level::operator bool()
{
	return loaded;
}

void Level::loadMap(std::string mapPath)
{
	MapParser parser(mapPath);
	parser.parseFile();
	player = std::make_unique<Playable>(parser.getPlayerSpritePaths(), 0.2f, parser.getPlayerPosition());
	blocks = std::move(parser.getBlockArray());

	backgroundImage.load(parser.getBackgroundImagePath());
	backgroundImage.setSize();
	auto musicPath = parser.getBackgroundMusicPath();
	if (!musicHandle.openFromFile(musicPath))
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
		if (musicHandle.getStatus() != sf::Music::Status::Playing && gameState == BananaMadness::GameState::IN_GAME)
			musicHandle.play();
		handleInput(gameState, pressedKeys, releasedKeys);
		player->update(blocks, pressedKeys, releasedKeys);
	}
	else
	{
		if (gameOverSound.getStatus() != sf::Sound::Playing)
		{
			musicHandle.stop();
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
	auto bgView = sf::View(sf::FloatRect(0.f, 0.f, (float)windowHandle->getSize().x, (float)windowHandle->getSize().y));
	windowHandle->setView(bgView);
	backgroundImage.render();
	std::ostringstream stream;
	stream << "Lifes left: " << lifes;
	text.setString(stream.str());
	text.setPosition({ windowHandle->getSize().x - 1.1f * text.getLocalBounds().width, 0.f });
	windowHandle->draw(text);

	windowHandle->setView(gameView);
	float winWidth2 = windowHandle->getSize().x / 2.f;
	float mapWidth = (*blocks)[0][0]->getSize().x * (float)(*blocks).size();
	float xCenter = std::max(std::min(player->getPosition().x, mapWidth - winWidth2), winWidth2);
	float yCenter = gameView.getCenter().y;
	gameView.setCenter(xCenter, yCenter);

	for (auto& i : *blocks)
		for (auto& j : i)
			if (j)
				j->render();
	player->render();
	windowHandle->draw(gameOverText);
}

void Level::handleInput(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys, std::vector<unsigned> releasedKeys)
{
	for (auto& i : releasedKeys)
	{
		switch (i)
		{
		case sf::Keyboard::Escape:
			musicHandle.pause();
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
	lifes = 3;
	currentLevel = levelIndex;
	loadMap(levelPaths[levelIndex]);
}
