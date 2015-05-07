#include "Button.h"

Button::Button(std::string backgroundImage, std::string hoverSoundPath, std::string clickSoundPath,
	std::string fontPath, std::string title, sf::Vector2u position /* = */ )
	: Drawable(backgroundImage, position)
{
	fontHandle = std::make_shared<sf::Font>();
	if (!fontHandle->loadFromFile(fontPath))
		throw FileLoadException(fontPath);

	clickSoundBuffer = std::make_shared<sf::SoundBuffer>();
	if (!clickSoundBuffer->loadFromFile(clickSoundPath))
		throw FileLoadException(clickSoundPath);
	clickSound = std::make_shared<sf::Sound>(*clickSoundBuffer);

	hoverSoundBuffer = std::make_shared<sf::SoundBuffer>();
	if (!hoverSoundBuffer->loadFromFile(hoverSoundPath))
		throw FileLoadException(hoverSoundPath);
	hoverSound = std::make_shared<sf::Sound>(*hoverSoundBuffer);
	load(title);
}

Button::Button(Button& obj, std::string title, sf::Vector2u position /* = {} */ )
	: Drawable(obj, position)
{
	fontHandle = obj.fontHandle;
	hoverSound = obj.hoverSound;
	clickSound = obj.clickSound;
	load(title);
}

void Button::load(std::string title)
{
	text.setFont(*fontHandle);
	text.setString(title);
	text.setColor(sf::Color::Black);
	text.setCharacterSize(50);
	setPosition(this->getPosition());
}

void Button::render()
{
	Drawable::render();
	windowHandle->draw(text);
}

void Button::setPosition(sf::Vector2u position)
{
	Drawable::setPosition(position);
	auto& btnPos = (sf::Vector2f)this->getPosition() + sf::Vector2f(this->getSize().x / 2.f, 0.f);
	text.setPosition({ btnPos.x - text.getLocalBounds().width / 2.f, btnPos.y });
}

void Button::playHoverSound()
{
	hoverSound->play();
}

void Button::playClickSound()
{
	clickSound->play();
}
