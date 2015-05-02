#include "Drawable.h"

sf::RenderWindow* Drawable::windowHandle;

Drawable::Drawable(Drawable& obj, sf::Vector2u position /* = { 0, 0 } */ )
{
	textureHandle = obj.textureHandle;
	spriteHandle.setTexture(*textureHandle);
	setPosition(position);
}

Drawable::Drawable(std::string path, sf::Vector2u position /* = { 0, 0 } */ )
{
	load(path, position);
}

void Drawable::load(std::string path, sf::Vector2u position /* = { 0, 0 } */ )
{
	textureHandle = std::make_shared<sf::Texture>();
	if (!textureHandle->loadFromFile(path))
		throw FileLoadException(path);
	textureHandle->setSmooth(true);
	spriteHandle.setTexture(*textureHandle);
	setPosition(position);
}

void Drawable::render()
{
	windowHandle->draw(spriteHandle);
}

void Drawable::setPosition(sf::Vector2u position)
{
	spriteHandle.setPosition((sf::Vector2f)position);
}

sf::Vector2u Drawable::getPosition()
{
	return (sf::Vector2u)spriteHandle.getPosition();
}

void Drawable::setSize(sf::Vector2u size /* = windowSize */)
{
	this->size = size;
	if (size == sf::Vector2u(0, 0))
		size = windowHandle->getSize();
	auto texSize = textureHandle->getSize();
	spriteHandle.setScale(sf::Vector2f((float)size.x / texSize.x, (float)size.y / texSize.y));
}

sf::Vector2u Drawable::getSize()
{
	return size;
}
