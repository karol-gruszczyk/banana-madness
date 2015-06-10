#pragma once

#include <ctime>
#include <vector>
#include <memory>

#include <src/base/Drawable.h>
#include <src/map/blocks/Block.h>

class Character
{
public:
	Character();
	Character(std::vector<std::string>& texturePaths, float spriteDelta, sf::Vector2f position = { 0, 0 });
	Character(Character& instance, sf::Vector2f position = { 0, 0 });

	void render();
	virtual void update(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks, bool isPlayer);
	void setPosition(sf::Vector2f newPos);
	bool isAlive();
	virtual void kill();
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	sf::Vector2u getSize();
	bool isIntersectingWith(sf::FloatRect rect);
protected:
	void updateDirection();
	static sf::Vector2u getBlockIndices(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks, sf::Vector2f pos);
	virtual bool move(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks, sf::Vector2f deltaPos, bool isPlayer);
	void handlePhysics(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks, bool isPlayer);
	float speed;
	bool alive;
	bool direction;
private:
	sf::Vector2f position;
	bool moving;
	float spriteDelta;
	float spriteDeltaTime;
	unsigned currentSprite;
	std::vector<std::unique_ptr<Drawable>> spriteTextures;
};

