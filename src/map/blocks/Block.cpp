#include "Block.h"

Block::Block(std::string imagePath, sf::Vector2u mapPosition /* = { 0, 0} */)
{
	load(imagePath, mapPosition);
}

Block::Block(Block& instance, sf::Vector2u mapPosition /* = { 0, 0} */) :
	Drawable(instance)
{
	setMapPosition(mapPosition);
}

void Block::load(std::string imagePath, sf::Vector2u mapPosition /* = { 0, 0} */)
{
	Drawable::load(imagePath);
	setMapPosition(mapPosition);
}

sf::Vector2u Block::getMapPosition()
{
	return mapPosition;
}

void Block::setMapPosition(sf::Vector2u mapPosition)
{
	this->mapPosition = mapPosition;
	
	sf::Vector2u position = { mapPosition.x * getSize().x, windowHandle->getSize().y - (mapPosition.y + 1) * getSize().y };
	setPosition((sf::Vector2f)position);
}

sf::Vector2f Block::getWorldPosition(sf::Vector2u mapPosition)
{
	return sf::Vector2f(mapPosition.x * BLOCK_SIZE, windowHandle->getSize().y - (mapPosition.y + 1) * BLOCK_SIZE);
}

bool Block::isCollidable(bool isPlayer, sf::Vector2f direction)
{
	return true;
}

bool Block::kills()
{
	return false;
}
