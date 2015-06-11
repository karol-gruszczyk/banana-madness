#include "SpikeBlock.h"

SpikeBlock::SpikeBlock(std::string imagePath, sf::Vector2u mapPosition /* = */) :
	InvisibleBlock(imagePath, mapPosition)
{}

SpikeBlock::SpikeBlock(SpikeBlock& instance, sf::Vector2u mapPosition /* = */) :
	InvisibleBlock(instance, mapPosition)
{}

bool SpikeBlock::isCollidable(bool isPlayer, sf::Vector2f direction)
{
	InvisibleBlock::isCollidable(isPlayer, direction);
	return false;
}

bool SpikeBlock::kills()
{
	return true;
}
