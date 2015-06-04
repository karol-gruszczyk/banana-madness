#include "Level.h"


Level::Level(sf::RenderWindow& windowHandle) : windowHandle(&windowHandle)
{}

Level::operator bool()
{
	return loaded;
}

void Level::loadMap(std::string mapPath)
{
	MapParser parser(mapPath);
	parser.parseFile();
	blocks = std::move(parser.getBlockArray());

	backgroundImage.load(parser.getBackgroundImagePath());
	backgroundImage.setSize();
	auto musicPath = parser.getBackgroundMusicPath();
	if (!musicHandle.openFromFile(musicPath))
		throw FileLoadException(musicPath);

	player.load(parser.getCharacterSpritePaths(), 0.1f);
	gameView = sf::View(sf::FloatRect(0.f, 0.f, (float)windowHandle->getSize().x, (float)windowHandle->getSize().y));

	loaded = true;
}

void Level::runFrame(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys, std::vector<unsigned> releasedKeys)
{
	render();
	if (musicHandle.getStatus() != sf::Music::Status::Playing && gameState == BananaMadness::GameState::IN_GAME)
		musicHandle.play();
	handleInput(gameState, pressedKeys, releasedKeys);
	player.update(blocks, pressedKeys, releasedKeys);
	if (!player.isAlive())
		gameState = BananaMadness::GameState::GAME_OVER;
}

void Level::render()
{
	auto bgView = sf::View(sf::FloatRect(0.f, 0.f, (float)windowHandle->getSize().x, (float)windowHandle->getSize().y));
	windowHandle->setView(bgView);
	backgroundImage.render();

	windowHandle->setView(gameView);
	float winWidth2 = windowHandle->getSize().x / 2.f;
	float mapWidth = (*blocks)[0][0]->getSize().x * (float)(*blocks).size();
	float xCenter = std::max(std::min(player.getPosition().x, mapWidth - winWidth2), winWidth2);
	float yCenter = gameView.getCenter().y;
	gameView.setCenter(xCenter, yCenter);

	for (auto& i : *blocks)
		for (auto& j : i)
			if (j)
				j->render();
	player.render();
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
