#pragma once
#include <fstream>
#include <string>
#include <memory>
#include <map>

#include <src/map/blocks/Block.h>

class MapParser
{
public:
	using BlockArray = std::vector < std::vector<Block> >;

	MapParser(std::string filename);
	void parseFile();
	BlockArray getBlocks();
	void getBackgroundImage();
	void getEnemies();
private:
	std::string filename;
	std::map<std::string, std::string> filePaths;

	void parseFilePaths(std::ifstream& file);
	std::unique_ptr<std::vector<std::string>> getLinesFromTag(std::ifstream& file, std::string tagName);
};

