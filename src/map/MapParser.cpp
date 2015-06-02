#include "MapParser.h"
#include <iostream>

MapParser::MapParser(std::string filename) : filename(filename)
{}

void MapParser::parseFile()
{
	std::ifstream file(filename);
	if (!file.is_open())
		throw FileLoadException(filename);
	parseFilePaths(file);
	parseMapAttributes(file);
	parseBlocks(file);
	parseCharacter(file);
	parseMap(file);

	file.close();
}

std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& MapParser::getBlockArray()
{
	return blockArray;
}

std::string MapParser::getBackgroundImagePath()
{
	return filePaths[mapAttributes["background_image"]];
}

std::string MapParser::getBackgroundMusicPath()
{
	return filePaths[mapAttributes["background_music"]];
}

std::vector<std::string> MapParser::getCharacterSpritePaths()
{
	return characterSpritePaths;
}

void MapParser::parseFilePaths(std::ifstream& file)
{
	auto lines = getLinesFromTag(file, "filepaths");
	std::string key, value;
	for (auto& line : *lines)
	{
		getKeyValueFromString(line, key, value);
		filePaths[key] = value;
	}
}

void MapParser::parseBlocks(std::ifstream& file)
{
	auto lines = getLinesFromTag(file, "blocks");
	std::string key, value, attrs, blockName, imgPath, blockType;
	for (auto& line : *lines)
	{
		getKeyValueFromString(line, blockName, attrs);
		attrs.erase(std::remove_if(attrs.begin(), attrs.end(), [](char chr){ return chr == '(' || chr == ')'; }), attrs.end());
		auto split_attrs = splitString(attrs, ",");
		for (auto& attr : split_attrs)
		{
			getKeyValueFromString(attr, key, value);
			if (key == "img")
				imgPath = filePaths[value];
			else if (key == "type")
				blockType = value;
		}
		
		if (blockType == "normal")
			blocks[blockName] = std::make_unique<Block>(imgPath);
	}
}

void MapParser::parseMapAttributes(std::ifstream& file)
{
	auto lines = getLinesFromTag(file, "mapattributes");
	std::string key, value;
	for (auto& line : *lines)
	{
		getKeyValueFromString(line, key, value);
		mapAttributes[key] = value;
	}
}

void MapParser::parseEnemies(std::ifstream& file)
{
	auto lines = getLinesFromTag(file, "enemies");
	for (auto& line : *lines)
	{

	}
}

void MapParser::parseCharacter(std::ifstream& file)
{
	std::string sprites_str = mapAttributes["player"];
	sprites_str.erase(std::remove_if(sprites_str.begin(), sprites_str.end(), [](char chr){ return chr == '(' || chr == ')'; }), sprites_str.end());
	while (sprites_str.find(',') != std::string::npos)
	{
		auto tmp = splitString(sprites_str, ",");
		characterSpritePaths.push_back(filePaths[tmp[0]]);
		sprites_str = tmp[1];
	}
	characterSpritePaths.push_back(filePaths[sprites_str]);
}

void MapParser::parseMap(std::ifstream& file)
{
	auto lines = getLinesFromTag(file, "map");
	blockArray = std::make_unique<std::vector<std::vector<std::unique_ptr<Block>>>>();
	blockArray->resize(lines->size());
	std::map<std::string, Block*> blockInstaces;

	for (unsigned i = 0; i < lines->size(); i++)
	{
		for (unsigned j = 0; j < (*lines)[i].size(); j++)
		{
			(*blockArray)[i].resize((*lines)[i].size());
			std::string blockName(1, (*lines)[i][j]);
			if (blocks.find(blockName) != blocks.end())
			{
				if (blockInstaces.find(blockName) == blockInstaces.end())
				{
					(*blockArray)[i][j] = std::move(blocks[blockName]);
					(*blockArray)[i][j]->setMapPosition({ i, j });
					blockInstaces[blockName] = &(*(*blockArray)[i][j]);
				}
				else
					(*blockArray)[i][j] = std::make_unique<Block>(*blockInstaces[blockName], sf::Vector2u{ i, j });

			}
		}
	}
}

std::vector<std::string> MapParser::splitString(std::string& str, std::string delimiter)
{
	std::vector<std::string> result(2);
	auto eq_pos = str.find(delimiter);
	result[0] = str.substr(0, eq_pos);
	result[1] = str.substr(eq_pos + 1);
	return result;
}

void MapParser::getKeyValueFromString(std::string& source, std::string& key, std::string& value)
{
	auto split = splitString(source, "=");
	key = split[0];
	value = split[1];
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
