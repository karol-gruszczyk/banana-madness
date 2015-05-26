#pragma once

#include <fstream>
#include <memory>

#include <src/base/Drawable.h>
#include <src/map/blocks/Block.h>
#include <src/map/MapParser.h>

class Map
{
public:
	Map() {};
	Map(std::string mapPath);
	void load(std::string mapPath);
	void render();
private:
	MapParser::BlockArray blocks;
	Drawable backgroundImage;

	void initBlockArray(std::vector<Block> blocks);
};

