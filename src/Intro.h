#pragma once

#include <SFML/Audio.hpp>
#include "exceptions/FileLoadException.h"
#include "Header.h"

class Intro
{
public:
	Intro(std::string filename);

	void runFrame(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys);
private:
	sf::Music musicHandle;
	bool musicPlayed;
};

