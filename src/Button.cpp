#include "Button.h"

sf::Font Button::fontHandle;
sf::Sound Button::hoverSound;
sf::SoundBuffer Button::hoverSoundBuffer;
sf::Sound Button::clickSound;
sf::SoundBuffer Button::clickSoundBuffer;

Button::Button(std::string backgroundImage, std::string title, sf::Vector2u position /* = {} */ )
	: Drawable(backgroundImage, position)
{
	load(title);
}

Button::Button(Button& obj, std::string title, sf::Vector2u position /* = {} */ )
	: Drawable(obj, position)
{
	load(title);
}

void Button::load(std::string title)
{
	text.setFont(fontHandle);
	text.setString(title);
	text.setColor(sf::Color::Black);
	text.setCharacterSize(50);
	setPosition(this->getPosition());
}

void Button::loadStatics(std::string clickSound, std::string hoverSound, std::string font)
{
	if (!fontHandle.loadFromFile(font))
		throw FileLoadException(font);
}

void Button::render()
{
	Drawable::render();
	// for some reason the following line is causing an exception on the closing bracket of main()
//	windowHandle->draw(text);
}

void Button::setPosition(sf::Vector2u position)
{
	Drawable::setPosition(position);
	auto& btnPos = (sf::Vector2f)this->getPosition() + sf::Vector2f(this->getSize().x / 2.f, 0.f);
//	text.setPosition({ btnPos.x - text.getLocalBounds().width / 2.f, btnPos.y });
}
