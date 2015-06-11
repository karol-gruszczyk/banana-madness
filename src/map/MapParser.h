#pragma once

#include <fstream>
#include <string>
#include <memory>
#include <map>
#include <algorithm>
#include <sstream>

#include <src/map/blocks/SpikeBlock.h>
#include <src/map/blocks/FallingBlock.h>
#include <src/map/blocks/TopInvisibleBlock.h>
#include <src/characters/JumpingEnemy.h>


class MapParser
{
public:
	MapParser(std::string filename);
	void parseFile();
	std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& getBlockArray();
	std::string getBackgroundImagePath();
	std::string getBackgroundMusicPath();
	std::vector<std::string> getPlayerSpritePaths();
	sf::Vector2f getPlayerPosition();
	std::unique_ptr< std::vector < std::unique_ptr <Enemy> > >& getEnemies();
private:
	std::string filename;
	std::map<std::string, std::string> filePaths;
	std::vector<std::string> playerSpritePaths;
	std::map<std::string, std::unique_ptr< Block> > blocks;
	std::map<std::string, std::string> mapAttributes;
	std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > > blockArray;
	std::unique_ptr< std::vector < std::unique_ptr <Enemy> > > enemyArray;
	std::map<std::string, std::vector<std::string>> spritePaths;

	void parseFilePaths(std::ifstream& file);
	void parseBlocks(std::ifstream& file);
	void parseMapAttributes(std::ifstream& file);
	void parseMap(std::ifstream& file);
	void parseSprites(std::ifstream& file);
	void parseEnemies(std::ifstream& file);
	void parsePlayer();
	std::vector<std::string> getSpritePaths(std::string spriteString);
	
	std::vector<std::string> splitString(std::string& str, std::string delimiter);
	void getKeyValueFromString(std::string& source, std::string& key, std::string& value);
	std::unique_ptr<std::vector<std::string>> getLinesFromTag(std::ifstream& file, std::string tagName);
};

