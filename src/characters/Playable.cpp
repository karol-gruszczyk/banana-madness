#include "Playable.h"


Playable::Playable(std::vector<std::string>& texturePaths, float spriteDelta, sf::Vector2f position /* = { 0, 0 } */ ) :
	Character(texturePaths, spriteDelta, position)
{}

Playable::Playable(Playable& instance, sf::Vector2f position /* = { 0, 0 } */ ) :
	Character(instance, position)
{}

void Playable::update(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks, 
					  std::vector<unsigned> pressedKeys,
					  std::vector<unsigned> releasedKeys)
{
	Character::update(blocks, true);
	for (auto& key : pressedKeys)
	{
		if (key == sf::Keyboard::Space && speed == 0.f)
			speed = -PLAYER_JUMP_SPEED;
		isKeyPressed[key] = true;
	}
	for (auto& key : releasedKeys)
		isKeyPressed[key] = false;

	for (auto& key : isKeyPressed)
	{
		if (!key.second)
			continue;
		switch (key.first)
		{
		case sf::Keyboard::Left:
			move(blocks, { -PLAYER_WALK_SPEED * deltaTime, 0.f });
			break;
		case sf::Keyboard::Right:
			move(blocks, { PLAYER_WALK_SPEED * deltaTime, 0.f });
			break;
		}
	}
}

bool Playable::move(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks, sf::Vector2f deltaPos, bool isPlayer /* = true */)
{
	auto newX = getPosition().x + deltaPos.x;
	auto maxX = BLOCK_SIZE * blocks->size() - getSize().x;
	if (newX > maxX)
		reachedEndOfMap = true;
	return Character::move(blocks, deltaPos, isPlayer);
}

bool Playable::hasReachedEndOfMap()
{
	return reachedEndOfMap;
}
