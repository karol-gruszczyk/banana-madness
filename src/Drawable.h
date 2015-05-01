#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

#include "exceptions/FileLoadException.h"

class Drawable
{
	friend class GameManager;
public:
	Drawable() {}
	Drawable(Drawable& obj, sf::Vector2u position = { 0, 0 });
	Drawable(std::string path, sf::Vector2u position = { 0, 0 });

	void load(std::string path, sf::Vector2u position = { 0, 0 });
	void render();
	void setPosition(sf::Vector2u position);
	sf::Vector2u getPosition();
	void setSize(sf::Vector2u size = { 0, 0 });
	sf::Vector2u getSize();
protected:
	static sf::RenderWindow* windowHandle;
private:
	std::shared_ptr<sf::Texture> textureHandle;
	sf::Sprite spriteHandle;
	sf::Vector2u size;
};

