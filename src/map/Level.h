#pragma once

#include <fstream>
#include <memory>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include <SFML/Audio.hpp>

#include <src/base/Drawable.h>
#include <src/map/blocks/Block.h>
#include <src/map/MapParser.h>
#include <src/characters/Playable.h>
#include <src/characters/Enemy.h>


class Level
{
public:
	Level(sf::RenderWindow& windowHandle, const char** levelPaths);
	void loadLevel(unsigned levelIndex);
	void reloadLevel();
	void runFrame(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys, std::vector<unsigned> releasedKeys);
	void render();
	operator bool();
private:
	sf::RenderWindow* windowHandle;
	const char** levelPaths;
	unsigned currentLevel;
	sf::View gameView;
	bool loaded;
	int lifes;
	sf::Font font;
	sf::Text text;
	std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > > blocks;
	std::unique_ptr< std::vector < std::unique_ptr < Enemy > > > enemies;
	Drawable backgroundImage;
	sf::Music musicHandle;
	sf::SoundBuffer gameOverSoundBuffer;
	sf::Sound gameOverSound;
	std::unique_ptr<Playable> player;
	sf::Font gameOverFont;
	sf::Text gameOverText;
	unsigned gameOverTextCounter;

	void loadMap(std::string mapPath);
	void handleInput(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys, std::vector<unsigned> releasedKeys);
};

