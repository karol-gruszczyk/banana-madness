#pragma once

#include <src/map/blocks/InvisibleBlock.h>

class SpikeBlock : public InvisibleBlock
{
public:
	SpikeBlock(std::string imagePath, sf::Vector2u mapPosition = {});
	SpikeBlock(SpikeBlock& instance, sf::Vector2u mapPosition = {});
	virtual bool isCollidable(bool isPlayer, sf::Vector2f direction);
	virtual bool kills();
private:
	bool visible;
};
