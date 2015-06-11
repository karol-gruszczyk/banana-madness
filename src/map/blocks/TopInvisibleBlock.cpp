#include "TopInvisibleBlock.h"

TopInvisibleBlock::TopInvisibleBlock(std::string imagePath, sf::Vector2u mapPosition /* = */) :
	InvisibleBlock(imagePath, mapPosition)
{}

TopInvisibleBlock::TopInvisibleBlock(TopInvisibleBlock& instance, sf::Vector2u mapPosition /* = */) :
	InvisibleBlock(instance, mapPosition)
{}

bool TopInvisibleBlock::isCollidable(bool isPlayer, sf::Vector2f direction)
{
	if (isPlayer && direction.y < 0.f)
		visible = true;
	return visible;
}
