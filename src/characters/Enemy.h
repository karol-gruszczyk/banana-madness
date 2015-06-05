#pragma once
#include <src/characters/Character.h>

class Enemy : public Character
{
public:
	Enemy(std::vector<std::string>& texturePaths, float spriteDelta, sf::Vector2f position = { 0, 0 });
	Enemy(Enemy& instance, sf::Vector2f position = { 0, 0 });
};

