#include "Playable.h"


Playable::Playable(std::vector<std::string>& texturePaths, double spriteDelta, sf::Vector2f position /* = { 0, 0 } */ ) :
	Character(texturePaths, spriteDelta, position)
{}

Playable::Playable(Playable& instance, sf::Vector2f position /* = { 0, 0 } */ ) :
	Character(instance, position)
{}

void Playable::update(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks, 
					  std::vector<unsigned> pressedKeys,
					  std::vector<unsigned> releasedKeys)
{
	handlePhysics(blocks);
	for (auto& key : pressedKeys)
		isKeyPressed[key] = true;
	for (auto& key : releasedKeys)
		isKeyPressed[key] = false;

	for (auto& key : isKeyPressed)
	{
		if (!key.second)
			continue;
		switch (key.first)
		{
		case sf::Keyboard::Left:
			move(blocks, { -1.f, 0.f });
			break;
		case sf::Keyboard::Right:
			move(blocks, { 1.f, 0.f });
			break;
		}
	}
}
