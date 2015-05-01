#pragma once

#include "Drawable.h"
#include <SFML/Audio.hpp>

class Button : public Drawable
{
public:
	using funcPointer = void(*)();
	Button(std::string backgroundImage, std::string title, funcPointer clickFunction);
	Button(Button& obj, std::string title, funcPointer clickFunction);
	void click();
	static void loadSounds(std::string clickSound, std::string hoverSound);
private:
	static sf::SoundBuffer clickSoundBuffer;
	static sf::Sound clickSound;
	static sf::SoundBuffer hoverSoundBuffer;
	static sf::Sound hoverSound;

	void load(std::string title, funcPointer clickFunction);
	funcPointer clickFunction;
	std::string title;
};

