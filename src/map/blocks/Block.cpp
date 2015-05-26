#include "Block.h"

Block::Block(std::string imagePath, sf::Vector2u mapPosition /* = */)
{
	load(imagePath, mapPosition);
}

Block::Block(Block& instance, sf::Vector2u mapPosition /* = */) : Drawable(instance)
{
	setMapPosition(mapPosition);
}

void Block::load(std::string imagePath, sf::Vector2u mapPosition /* = */)
{
	Drawable::load(imagePath);
	setMapPosition(mapPosition);
}

sf::Vector2u Block::getMapPosition()
{
	return mapPosition;
}

void Block::setMapPosition(sf::Vector2u mapPostion)
{
	this->mapPosition = mapPostion;
	sf::Vector2u position = { mapPosition.x * getSize().x, mapPosition.y * getSize().y };
	setPosition(position);
}
