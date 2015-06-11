#pragma once
#include <src/map/blocks/InvisibleBlock.h>

class TopInvisibleBlock : public InvisibleBlock
{
public:
	TopInvisibleBlock(std::string imagePath, sf::Vector2u mapPosition = {});
	TopInvisibleBlock(TopInvisibleBlock& instance, sf::Vector2u mapPosition = {});
	virtual bool isCollidable(bool isPlayer, sf::Vector2f direction);
};

