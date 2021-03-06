#include "MapParser.h"

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
	parseSprites(file);
	parsePlayer();
	parseMap(file);
	parseEnemies(file);

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

std::vector<std::string> MapParser::getPlayerSpritePaths()
{
	return playerSpritePaths;
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

void MapParser::parseSprites(std::ifstream& file)
{
	auto lines = getLinesFromTag(file, "sprites");
	std::string key, value;
	for (auto& line : *lines)
	{
		getKeyValueFromString(line, key, value);
		spritePaths[key] = getSpritePaths(value);
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
		else if (blockType == "topinvisible")
			blocks[blockName] = std::make_unique<TopInvisibleBlock>(imgPath);
		else if (blockType == "invisible")
			blocks[blockName] = std::make_unique<InvisibleBlock>(imgPath);
		else if (blockType == "spike")
			blocks[blockName] = std::make_unique<SpikeBlock>(imgPath);
		else if (blockType == "falling")
			blocks[blockName] = std::make_unique<FallingBlock>(imgPath);
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
	std::map<std::string, Enemy*> enemyInstances;
	enemyArray = std::make_unique<std::vector<std::unique_ptr<Enemy>>>();
	for (auto& line : *lines)
	{
		std::string key, value;
		getKeyValueFromString(line, key, value);
		value.erase(std::remove_if(value.begin(), value.end(), [](char chr){ return chr == '(' || chr == ')'; }), value.end());

		std::vector<std::string> props;
		for (unsigned i = 0; i < 3; ++i)
		{
			std::vector<std::string> props_tmp = splitString(value, ",");
			props.push_back(props_tmp[0]);
			value = props_tmp[1];
		}
		props.push_back(value);
		
		std::string sprite_key, type;
		sf::Vector2f spawnPos;
		float end;
		for (auto& prop : props)
		{
			std::string prop_key, prop_value;
			getKeyValueFromString(prop, prop_key, prop_value);
			if (prop_key == "start")
			{
				sf::Vector2u mapPos;
				std::istringstream stream(prop_value);
				stream >> mapPos.x >> mapPos.y;
				spawnPos = (*blockArray)[0][0]->getWorldPosition(mapPos);
			}
			else if (prop_key == "end")
			{
				std::istringstream stream(prop_value);
				stream >> end;
				end *= (*blockArray)[0][0]->getSize().x;
			}
			else if (prop_key == "type")
				type = prop_value;
			else if (prop_key == "sprite")
				sprite_key = prop_value;

		}
		if (enemyInstances.find(sprite_key) != enemyInstances.end())
		{
			if (type == "jumping")
				enemyArray->push_back(std::make_unique<JumpingEnemy>(*enemyInstances[sprite_key], spawnPos, end));
			else if (type == "normal")
				enemyArray->push_back(std::make_unique<Enemy>(*enemyInstances[sprite_key], spawnPos, end));
		}
		else
		{
			if (type == "jumping")
				enemyArray->push_back(std::make_unique<JumpingEnemy>(spritePaths[sprite_key], SPRITE_DELTA_TIME, spawnPos, end));
			else if (type == "normal")
				enemyArray->push_back(std::make_unique<Enemy>(spritePaths[sprite_key], SPRITE_DELTA_TIME, spawnPos, end));
			enemyInstances[sprite_key] = (*enemyArray)[enemyArray->size() - 1].get();
		}
	}
}

void MapParser::parsePlayer()
{
	playerSpritePaths = spritePaths[mapAttributes["player"]];
}

std::vector<std::string> MapParser::getSpritePaths(std::string spriteString)
{
	std::string sprites_str = spriteString;
	std::vector<std::string> characterSprites;
	sprites_str.erase(std::remove_if(sprites_str.begin(), sprites_str.end(), [](char chr){ return chr == '(' || chr == ')'; }), sprites_str.end());
	while (sprites_str.find(',') != std::string::npos)
	{
		auto tmp = splitString(sprites_str, ",");
		characterSprites.push_back(filePaths[tmp[0]]);
		sprites_str = tmp[1];
	}
	if (filePaths.find(sprites_str) != filePaths.end())
		characterSprites.push_back(filePaths[sprites_str]);
 	else
 		throw std::invalid_argument(std::string("invalid key '" + sprites_str + "'"));
	return characterSprites;
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
				{
					if (auto ptr = dynamic_cast<SpikeBlock*>(blockInstaces[blockName]))
						(*blockArray)[i][j] = std::make_unique<SpikeBlock>(*ptr, sf::Vector2u{ i, j });
					else if (auto ptr = dynamic_cast<TopInvisibleBlock*>(blockInstaces[blockName]))
						(*blockArray)[i][j] = std::make_unique<TopInvisibleBlock>(*ptr, sf::Vector2u{ i, j });
					else if (auto ptr = dynamic_cast<InvisibleBlock*>(blockInstaces[blockName]))
						(*blockArray)[i][j] = std::make_unique<InvisibleBlock>(*ptr, sf::Vector2u{ i, j });
					else if (auto ptr = dynamic_cast<FallingBlock*>(blockInstaces[blockName]))
						(*blockArray)[i][j] = std::make_unique<FallingBlock>(*ptr, sf::Vector2u{ i, j });
					else
						(*blockArray)[i][j] = std::make_unique<Block>(*blockInstaces[blockName], sf::Vector2u{ i, j });
				}

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

sf::Vector2f MapParser::getPlayerPosition()
{
	sf::Vector2u position;
	auto str = splitString(mapAttributes["player_position"], ",");
	std::stringstream stream;
	stream << str[0] << " " << str[1];
	stream >> position.x >> position.y;
	return Block::getWorldPosition(position);
}

std::unique_ptr< std::vector < std::unique_ptr <Enemy> > >& MapParser::getEnemies()
{
	return enemyArray;
}
