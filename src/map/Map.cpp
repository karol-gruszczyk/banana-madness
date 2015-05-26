#include "Map.h"


Map::Map(sf::RenderWindow& windowHandle) : windowHandle(&windowHandle)
{
	gameView = sf::View(sf::FloatRect(0.f, 0.f, (float)windowHandle.getSize().x, (float)windowHandle.getSize().y));
}

Map::operator bool()
{
	return loaded;
}

void Map::loadMap(std::string mapPath)
{
	MapParser parser(mapPath);
	parser.parseFile();
	blocks = std::move(parser.getBlockArray());

	backgroundImage.load(parser.getBackgroundImagePath());
	auto musicPath = parser.getBackgroundMusicPath();
	if (!musicHandle.openFromFile(musicPath))
		throw FileLoadException(musicPath);
	loaded = true;
}

void Map::runFrame(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys, std::vector<unsigned> releasedKeys)
{
	windowHandle->setView(gameView);
	if (musicHandle.getStatus() != sf::Music::Status::Playing)
		musicHandle.play();
	backgroundImage.render();
	for (auto& i : *blocks)
		for (auto& j : i)
			if (j)
				j->render();

}
