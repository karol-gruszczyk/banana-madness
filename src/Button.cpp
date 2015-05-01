#include "Button.h"

Button::Button(std::string backgroundImage, std::string title, funcPointer clickFunction) : Drawable(backgroundImage)
{
	load(title, clickFunction);
}

Button::Button(Button& obj, std::string title, funcPointer clickFunction) : Drawable(obj)
{
	load(title, clickFunction);
}

void Button::load(std::string title, funcPointer clickFunction)
{
	this->title = title;
	this->clickFunction = clickFunction;
}
