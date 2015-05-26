#include "Map.h"


Map::Map(std::string mapPath)
{
	load(mapPath);
}

void Map::load(std::string mapPath)
{
	MapParser parser(mapPath);
	parser.parseFile();
	blocks = parser.getBlocks();
}

void Map::render()
{

}

void Map::initBlockArray(std::vector<Block> blocks)
{

}
