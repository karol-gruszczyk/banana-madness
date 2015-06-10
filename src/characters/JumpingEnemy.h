#pragma once
#include <src/characters/Enemy.h>

class JumpingEnemy : public Enemy
{
public:
	JumpingEnemy(std::vector<std::string>& texturePaths, float spriteDelta, sf::Vector2f position, float end);
	JumpingEnemy(Enemy& instance, sf::Vector2f position, float end);
	void update(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks);
private:
	float startX, endX;
	bool direction;
};

