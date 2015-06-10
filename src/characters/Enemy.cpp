#include "Enemy.h"


Enemy::Enemy(std::vector<std::string>& texturePaths, float spriteDelta, sf::Vector2f position, float end) :
	Character(texturePaths, spriteDelta, position),
	spawnPosition(position)
{
	initPositions(position.x, end);
}

Enemy::Enemy(Enemy& instance, sf::Vector2f position, float end) :
	Character(instance, position),
	spawnPosition(position)
{
	initPositions(position.x, end);
}

void Enemy::update(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks)
{
	Character::update(blocks, false);
	auto posX = getPosition().x;
	if (direction)
	{
		if (posX > startX)
			move(blocks, { -ENEMY_MOVING_SPEED * deltaTime, 0.f }, false);
		else
		{
			direction = !direction;
			updateDirection();
		}
	}
	else // moving to endX
	{
		if (posX < endX)
			move(blocks, { ENEMY_MOVING_SPEED * deltaTime, 0.f }, false);
		else
		{
			direction = !direction;
			updateDirection();
		}
	}
}

void Enemy::kill()
{
	setPosition(spawnPosition); //respawning
	updateDirection();
}

void Enemy::initPositions(float begin, float end)
{
	if (end > begin)
	{
		startX = begin;
		endX = end;
	}
	else
	{
		startX = end;
		endX = begin;
	}
}
