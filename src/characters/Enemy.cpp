#include "Enemy.h"


Enemy::Enemy(std::vector<std::string>& texturePaths, float spriteDelta, sf::Vector2f position, float end) :
	Character(texturePaths, spriteDelta, position),
	startX(position.x),
	endX(end)
{}

Enemy::Enemy(Enemy& instance, sf::Vector2f position, float end) :
	Character(instance, position),
	startX(position.x),
	endX(end)
{}

void Enemy::update(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks)
{
	Character::update(blocks);
	auto posX = getPosition().x;
	if (direction)
	{
		if (posX > startX)
			move(blocks, { -ENEMY_MOVING_SPEED * deltaTime, 0.f });
		else
		{
			flipX();
			direction = !direction;
		}
	}
	else // moving to endX
	{
		if (posX < endX)
			move(blocks, { ENEMY_MOVING_SPEED * deltaTime, 0.f });
		else
		{
			flipX();
			direction = !direction;
		}
	}
}
