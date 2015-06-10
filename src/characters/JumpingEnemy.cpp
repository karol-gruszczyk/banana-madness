#include "JumpingEnemy.h"

JumpingEnemy::JumpingEnemy(std::vector<std::string>& texturePaths, float spriteDelta, sf::Vector2f position, float end) :
	Enemy(texturePaths, spriteDelta, position, end)
{}

JumpingEnemy::JumpingEnemy(Enemy& instance, sf::Vector2f position, float end) :
	Enemy(instance, position, end)
{}

void JumpingEnemy::update(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks)
{
	Enemy::update(blocks);
	if (speed == 0.f && !move(blocks, { 0.f, 1.f }, false))
		speed = -ENEMY_JUMP_SPEED;
}
