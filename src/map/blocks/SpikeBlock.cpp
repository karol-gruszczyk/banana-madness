#include "SpikeBlock.h"

SpikeBlock::SpikeBlock(std::string imagePath, sf::Vector2u mapPosition /* = */) :
	InvisibleBlock(imagePath, mapPosition)
{}

SpikeBlock::SpikeBlock(SpikeBlock& instance, sf::Vector2u mapPosition /* = */) :
	InvisibleBlock(instance, mapPosition)
{}

bool SpikeBlock::isCollidable()
{
	InvisibleBlock::isCollidable();
	return false;
}

bool SpikeBlock::kills()
{
	return true;
}
