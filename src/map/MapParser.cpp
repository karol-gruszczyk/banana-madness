#include "MapParser.h"

MapParser::MapParser(std::string filename) : filename(filename)
{}

void MapParser::parseFile()
{
	std::ifstream file(filename);
	parseFilePaths(file);
}

void MapParser::parseFilePaths(std::ifstream& file)
{
	auto lines = getLinesFromTag(file, "filepaths");
	for (auto& line : *lines)
	{
		auto eq_pos = line.find('=');
		filePaths[line.substr(0, eq_pos)] = line.substr(eq_pos + 1);
	}
}

MapParser::BlockArray MapParser::getBlocks()
{
	return BlockArray();
}

std::unique_ptr<std::vector<std::string>> MapParser::getLinesFromTag(std::ifstream& file, std::string tagName)
{
	std::string line;
	auto lines = std::make_unique<std::vector<std::string>>();

	// seek to the beginning of the block
	file.seekg(0);
	do { 
		std::getline(file, line);
	} while (line != tagName);
	while (true)
	{
		std::getline(file, line);
		if ((line == "!" + tagName))
			break;
		lines->push_back(line);
	}
	return lines;
}
