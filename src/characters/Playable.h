#pragma once

#include <src/characters/Character.h>


class Playable : public Character
{
public:
	Playable(std::vector<std::string>& texturePaths, float spriteDelta, sf::Vector2f position = { 0, 0 });
	Playable(Playable& instance, sf::Vector2f position = { 0, 0 });
	void update(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks,
				std::vector<unsigned> pressedKeys, 
				std::vector<unsigned> releasedKeys);
	bool hasReachedEndOfMap();
protected:
	bool reachedEndOfMap;
	bool move(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks, sf::Vector2f deltaPos, bool isPlayer = true);
private:
	std::map<unsigned, bool> isKeyPressed;
};

