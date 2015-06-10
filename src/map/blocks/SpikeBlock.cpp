#include "SpikeBlock.h"

SpikeBlock::SpikeBlock(std::string imagePath, sf::Vector2u mapPosition /* = */) :
	InvisibleBlock(imagePath, mapPosition)
{}

SpikeBlock::SpikeBlock(SpikeBlock& instance, sf::Vector2u mapPosition /* = */) :
	InvisibleBlock(instance, mapPosition)
{}

bool SpikeBlock::isCollidable(bool isPlayer /* = false */)
{
	InvisibleBlock::isCollidable(isPlayer);
	return false;
}

bool SpikeBlock::kills()
{
	return true;
}
