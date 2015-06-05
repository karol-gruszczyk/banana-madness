#pragma once
#include <src/characters/Character.h>

class Enemy : public Character
{
public:
	Enemy(std::vector<std::string>& texturePaths, float spriteDelta, sf::Vector2f position, float end);
	Enemy(Enemy& instance, sf::Vector2f position, float end);
	void update(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks);
private:
	float startX, endX;
	bool direction;
};

