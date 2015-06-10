#pragma once

#include <src/map/blocks/InvisibleBlock.h>

class SpikeBlock : public InvisibleBlock
{
public:
	SpikeBlock(std::string imagePath, sf::Vector2u mapPosition = {});
	SpikeBlock(SpikeBlock& instance, sf::Vector2u mapPosition = {});
	bool isCollidable(bool isPlayer = false);
	bool kills();
private:
	bool visible;
};
