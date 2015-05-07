#pragma once

#include "Drawable.h"
#include <SFML/Audio.hpp>

class Button : public Drawable
{
public:
	Button(std::string backgroundImage, std::string hoverSoundPath, std::string clickSoundPath,
		std::string fontPath, std::string title, sf::Vector2u position = {});
	Button(Button& obj, std::string title, sf::Vector2u position = {});

	void render();
	void setPosition(sf::Vector2u position);
	void playHoverSound();
	void playClickSound();
private:
	// for the following 4 unique_ptr are deallocated in wrong order, causing an "memory access violation exception" at window close
	std::shared_ptr<sf::Sound> clickSound;
	std::shared_ptr<sf::SoundBuffer> clickSoundBuffer;
	std::shared_ptr<sf::Sound> hoverSound;
	std::shared_ptr<sf::SoundBuffer> hoverSoundBuffer;

	std::shared_ptr<sf::Font> fontHandle;

	void load(std::string title);
	sf::Text text;
};

