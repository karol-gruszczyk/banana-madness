#pragma once

#include <SFML/Audio.hpp>
#include "exceptions/FileLoadException.h"
#include "Header.h"

class Intro
{
public:
	Intro(std::string filename);

	void render(BananaMadness::GameState& gameState);
private:
	sf::Music musicHandle;
	bool musicPlayed;
};

