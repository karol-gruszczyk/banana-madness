#pragma once

#include "Drawable.h"
#include <SFML/Audio.hpp>

class Button : public Drawable
{
public:
	typedef void(*funcPointer)();
	Button(std::string title, funcPointer clickFunction);
	void click();
	static void loadSounds(std::string clickSound, std::string hoverSound);
private:
	static sf::SoundBuffer clickSoundBuffer;
	static sf::Sound clickSound;
	static sf::SoundBuffer hoverSoundBuffer;
	static sf::Sound hoverSound;

	funcPointer clickFunction;
	std::string title;
};

