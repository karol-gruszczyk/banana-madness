#pragma once

#include "Drawable.h"
#include <SFML/Audio.hpp>

class Button : public Drawable
{
public:
	Button(std::string backgroundImage, std::string title, sf::Vector2u position = {});
	Button(Button& obj, std::string title, sf::Vector2u position = {});

	static void loadStatics(std::string clickSoundPath, std::string hoverSoundPath, std::string fontPath);

	void render();
	void setPosition(sf::Vector2u position);
	static void playHoverSound();
	static void playClickSound();
private:
	// for the following 4 unique_ptr are deallocated in wrong order, causing an "memory access violation exception" at window close
	static std::unique_ptr<sf::Sound> clickSound;
	static std::unique_ptr<sf::SoundBuffer> clickSoundBuffer;
	static std::unique_ptr<sf::Sound> hoverSound;
	static std::unique_ptr<sf::SoundBuffer> hoverSoundBuffer;

	static std::unique_ptr<sf::Font> fontHandle;

	void load(std::string title);
	sf::Text text;
};

