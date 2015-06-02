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

	player.load(parser.getCharacterSpritePaths(), 0.10);

	gameView.reset(sf::FloatRect(0.f, 0.f, (float)windowHandle->getSize().x, (float)windowHandle->getSize().y));
	loaded = true;
}

void Level::runFrame(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys, std::vector<unsigned> releasedKeys)
{
	windowHandle->setView(gameView);
	handleInput(gameState, pressedKeys, releasedKeys);
	if (musicHandle.getStatus() != sf::Music::Status::Playing && gameState == BananaMadness::GameState::IN_GAME)
		musicHandle.play();
	backgroundImage.render();
	for (auto& i : *blocks)
		for (auto& j : i)
			if (j)
				j->render();
	player.update(blocks, pressedKeys, releasedKeys);
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
