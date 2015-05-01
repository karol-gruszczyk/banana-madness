#include "Drawable.h"

sf::RenderWindow* Drawable::windowHandle;

Drawable::Drawable(std::string path, sf::Vector2u position /* = {0, 0} */ )
{
	if (!textureHandle.loadFromFile(path))
		throw FileLoadException(path);
	textureHandle.setSmooth(true);
	spriteHandle.setTexture(textureHandle);
}

void Drawable::render()
{
	windowHandle->draw(spriteHandle);
}

void Drawable::setPosition(sf::Vector2u position)
{
	spriteHandle.setPosition((sf::Vector2f)position);
}

void Drawable::setSize(sf::Vector2u size /* = windowSize */)
{
	if (size == sf::Vector2u(0, 0))
		size = windowHandle->getSize();
	auto texSize = textureHandle.getSize();
	spriteHandle.setScale(sf::Vector2f((float)size.x / texSize.x, (float)size.y / texSize.y));
}