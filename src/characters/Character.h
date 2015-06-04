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

	void load(std::vector<std::string>& texturePaths, float spriteDelta, sf::Vector2f position = { 0, 0 });
	void render();
	void setPosition(sf::Vector2f newPos);
	bool isAlive();
	sf::Vector2f getPosition();
	sf::Vector2u getSize();
protected:
	static sf::Vector2u getBlockIndices(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks, sf::Vector2f pos);
	bool move(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks, sf::Vector2f deltaPos);
	void handlePhysics(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks);
	float speed;
	float deltaTime;
	bool alive;
private:
	sf::Vector2f position;
	bool moving;
	float spriteDelta;
	float spriteDeltaTime;
	unsigned currentSprite;
	std::clock_t lastFrameTime;
	std::shared_ptr< std::vector<Drawable> > spriteTextures;

	
};

