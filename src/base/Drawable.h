#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

#include <src/Globals.h>
#include <src/base/exceptions/FileLoadException.h>

class Drawable
{
	friend class GameManager;
public:
	Drawable() {}
	Drawable(Drawable& obj, sf::Vector2f position = { 0, 0 });
	Drawable(std::string path, sf::Vector2f position = { 0, 0 });

	void load(std::string path, sf::Vector2f position = { 0, 0 });
	virtual void render();
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
	void setSize(sf::Vector2u size = { 0, 0 });
	sf::Vector2u getSize();
	void setScale(sf::Vector2f factors);
	sf::Vector2f getScale();
	sf::FloatRect getGlobalBounds();
protected:
	static sf::RenderWindow* windowHandle;
private:
	std::shared_ptr<sf::Texture> textureHandle;
	sf::Sprite spriteHandle;
};

