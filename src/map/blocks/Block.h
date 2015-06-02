#pragma once

#include <src/base/Drawable.h>

class Block : public Drawable
{
public:
	Block() {};
	Block(std::string imagePath, sf::Vector2u mapPosition = {});
	Block(Block& instance, sf::Vector2u mapPosition = {});
	void load(std::string imagePath, sf::Vector2u mapPosition = {});
	sf::Vector2u getMapPosition();
	void setMapPosition(sf::Vector2u mapPostion);
	bool isCollidable();
private:
	sf::Vector2u mapPosition;
	bool collidable;
};

