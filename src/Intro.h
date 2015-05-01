#pragma once

#include <SFML/Audio.hpp>
#include "Drawable.h"

class Intro
{
public:
	Intro(std::string filename);

	bool render(sf::RenderWindow& windowHandle);
private:
	sf::Music musicHandle;
	bool musicPlayed;
};

