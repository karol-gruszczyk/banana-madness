#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "exceptions/FileLoadException.h"

class Drawable
{
	friend class GameManager;
public:
	Drawable(std::string path, sf::Vector2u position = {0, 0});
	~Drawable();

	void render();
	void setPosition(sf::Vector2u position);
	void setSize(sf::Vector2u size = { 0, 0 });
protected:
	static sf::RenderWindow* windowHandle;
private:
	sf::Texture textureHandle;
	sf::Sprite spriteHandle;
};

