#pragma once

#include <ctime>
#include <vector>
#include <memory>

#include <src/base/Drawable.h>
#include <src/map/blocks/Block.h>


class Character
{
public:
	Character() {}
	Character(std::vector<std::string>& texturePaths, double spriteDelta, sf::Vector2f position = { 0, 0 });
	Character(Character& instance, sf::Vector2f position = { 0, 0 });

	void load(std::vector<std::string>& texturePaths, double spriteDelta, sf::Vector2f position = { 0, 0 });
	void render();
	void setPosition(sf::Vector2f newPos);
	sf::Vector2f getPosition();
	sf::Vector2u getSize();
protected:
	static sf::Vector2u getBlockIndices(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks, sf::Vector2f pos);
	void move(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks, sf::Vector2f deltaPos);
	void handlePhysics(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks);
	float speed = 0.f;
private:
	sf::Vector2f position;
	bool moving;
	double spriteDelta;
	double deltaTime;
	unsigned currentSprite;
	std::time_t lastFrameTime;
	std::shared_ptr< std::vector<Drawable> > spriteTextures;

	
};

