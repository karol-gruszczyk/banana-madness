#include "Enemy.h"


Enemy::Enemy(std::vector<std::string>& texturePaths, float spriteDelta, sf::Vector2f position /* = */ ) :
	Character(texturePaths, spriteDelta, position)
{}

Enemy::Enemy(Enemy& instance, sf::Vector2f position /* = */ ) :
	Character(instance, position)
{}
