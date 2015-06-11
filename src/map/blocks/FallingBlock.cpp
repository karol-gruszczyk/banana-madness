#include "FallingBlock.h"

FallingBlock::FallingBlock(std::string imagePath, sf::Vector2u mapPosition /* = */) :
	Block(imagePath, mapPosition)
{}

FallingBlock::FallingBlock(FallingBlock& instance, sf::Vector2u mapPosition /* = */) :
	Block(instance, mapPosition)
{}

void FallingBlock::render()
{
	if (touched)
		setPosition({ getPosition().x, getPosition().y + deltaTime });
	Block::render();
}

bool FallingBlock::isCollidable(bool isPlayer, sf::Vector2f direction)
{
	touched = touched || isPlayer;
	return false;
}
