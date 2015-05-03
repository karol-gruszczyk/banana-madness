#include "Button.h"

std::unique_ptr<sf::Font> Button::fontHandle;
std::unique_ptr<sf::Sound> Button::hoverSound;
std::unique_ptr<sf::SoundBuffer> Button::hoverSoundBuffer;
std::unique_ptr<sf::Sound> Button::clickSound;
std::unique_ptr<sf::SoundBuffer> Button::clickSoundBuffer;

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
	text.setFont(*fontHandle);
	text.setString(title);
	text.setColor(sf::Color::Black);
	text.setCharacterSize(50);
	setPosition(this->getPosition());
}

void Button::loadStatics(std::string clickSoundPath, std::string hoverSoundPath, std::string fontPath)
{
	fontHandle = std::make_unique<sf::Font>();
	if (!fontHandle->loadFromFile(fontPath))
		throw FileLoadException(fontPath);

	clickSoundBuffer = std::make_unique<sf::SoundBuffer>();
	if (!clickSoundBuffer->loadFromFile(clickSoundPath))
		throw FileLoadException(clickSoundPath);
	clickSound = std::make_unique<sf::Sound>(*clickSoundBuffer);
 
	hoverSoundBuffer = std::make_unique<sf::SoundBuffer>();
	if (!hoverSoundBuffer->loadFromFile(hoverSoundPath))
		throw FileLoadException(hoverSoundPath);
	hoverSound = std::make_unique<sf::Sound>(*hoverSoundBuffer);
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
