#pragma once

#include <fstream>
#include <memory>
#include <algorithm>

#include <SFML/Audio.hpp>

#include <src/base/Drawable.h>
#include <src/map/blocks/Block.h>
#include <src/map/MapParser.h>
#include <src/characters/Playable.h>


class Level
{
public:
	Level(sf::RenderWindow& windowHandle);
	void loadMap(std::string mapPath);
	void runFrame(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys, std::vector<unsigned> releasedKeys);
	void render();
	operator bool();
private:
	sf::RenderWindow* windowHandle;
	sf::View gameView;
	bool loaded;
	std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > > blocks;
	Drawable backgroundImage;
	sf::Music musicHandle;
	Playable player;

	void handleInput(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys, std::vector<unsigned> releasedKeys);
};

