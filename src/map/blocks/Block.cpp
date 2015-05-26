#include "Block.h"

Block::Block(std::string imagePath, sf::Vector2u mapPosition /* = */)
{
	load(imagePath, mapPosition);
}

void Block::load(std::string imagePath, sf::Vector2u mapPosition /* = */)
{
	Drawable::load(imagePath);
	auto position = { mapPosition.x * getSize().x, mapPosition.y * getSize().y };
	setPosition(mapPosition);
}

sf::Vector2u Block::getMapPosition()
{
	return mapPosition;
}

void Block::setMapPosition(sf::Vector2u mapPostion)
{
	this->mapPosition = mapPostion;
}
