#include "InvisibleBlock.h"

InvisibleBlock::InvisibleBlock(std::string imagePath, sf::Vector2u mapPosition /* = */ ) :
	Block(imagePath, mapPosition)
{}

InvisibleBlock::InvisibleBlock(InvisibleBlock& instance, sf::Vector2u mapPosition /* = */ ) :
	Block(instance, mapPosition)
{}

void InvisibleBlock::render()
{
	if (visible)
		Block::render();
}

bool InvisibleBlock::isCollidable(bool isPlayer, sf::Vector2f direction)
{
	if (isPlayer)
		visible = true;
	return true;
}
