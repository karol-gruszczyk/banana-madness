#pragma once

#include <fstream>
#include <string>
#include <memory>
#include <map>
#include <algorithm>

#include <src/map/blocks/Block.h>

class MapParser
{
public:
	MapParser(std::string filename);
	void parseFile();
	std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& getBlockArray();
	std::string getBackgroundImagePath();
	std::string getBackgroundMusicPath();
	std::vector<std::string> getCharacterSpritePaths();
	void getEnemies();
private:
	std::string filename;
	std::map<std::string, std::string> filePaths;
	std::vector<std::string> characterSpritePaths;
	std::map<std::string, std::unique_ptr< Block> > blocks;
	std::map<std::string, std::string> mapAttributes;
	std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > > blockArray;

	void parseFilePaths(std::ifstream& file);
	void parseBlocks(std::ifstream& file);
	void parseMapAttributes(std::ifstream& file);
	void parseMap(std::ifstream& file);
	void parseEnemies(std::ifstream& file);
	void parseCharacter(std::ifstream& file);
	
	std::vector<std::string> splitString(std::string& str, std::string delimiter);
	void getKeyValueFromString(std::string& source, std::string& key, std::string& value);
	std::unique_ptr<std::vector<std::string>> getLinesFromTag(std::ifstream& file, std::string tagName);
};

