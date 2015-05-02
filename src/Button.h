#pragma once

#include "Drawable.h"
#include "Defines.h"
#include <SFML/Audio.hpp>

class Button : public Drawable
{
public:
	using funcPointer = void(*)(BananaMadness::GameState&);

	static void loadStatics(std::string clickSound, std::string hoverSound, std::string font);
	Button(std::string backgroundImage, std::string title, sf::Vector2u position = {});
	Button(Button& obj, std::string title, sf::Vector2u position = {});
	void render();
	void setPosition(sf::Vector2u position);
private:
	static sf::SoundBuffer clickSoundBuffer;
	static sf::Sound clickSound;
	static sf::SoundBuffer hoverSoundBuffer;
	static sf::Sound hoverSound;
	static sf::Font fontHandle;

	void load(std::string title);
	sf::Text text;
};

