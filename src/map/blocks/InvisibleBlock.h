#pragma once

#include <src/map/blocks/Block.h>

class InvisibleBlock : public Block
{
public:
	InvisibleBlock(std::string imagePath, sf::Vector2u mapPosition = {});
	InvisibleBlock(InvisibleBlock& instance, sf::Vector2u mapPosition = {});
	virtual void render();
	virtual bool isCollidable(bool isPlayer, sf::Vector2f direction);
protected:
	bool visible;
};

