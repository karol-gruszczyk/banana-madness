#pragma once

#include <SFML/Audio.hpp>

#include <src/base/Drawable.h>

class Button : public Drawable
{
public:
	Button(std::string backgroundImage, std::string hoverSoundPath, std::string clickSoundPath,
		std::string fontPath, std::string title, sf::Vector2f position = {});
	Button(Button& obj, std::string title, sf::Vector2f position = {});

	void render();
	void setPosition(sf::Vector2f position);
	void playHoverSound();
	void playClickSound();
private:
	std::shared_ptr<sf::Sound> clickSound;
	std::shared_ptr<sf::SoundBuffer> clickSoundBuffer;
	std::shared_ptr<sf::Sound> hoverSound;
	std::shared_ptr<sf::SoundBuffer> hoverSoundBuffer;

	std::shared_ptr<sf::Font> fontHandle;

	void load(std::string title);
	sf::Text text;
};

