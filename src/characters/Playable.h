#pragma once

#include <src/characters/Character.h>


class Playable : public Character
{
public:
	Playable() {}
	Playable(std::vector<std::string>& texturePaths, float spriteDelta, sf::Vector2f position = { 0, 0 });
	Playable(Playable& instance, sf::Vector2f position = { 0, 0 });
	void update(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks,
				std::vector<unsigned> pressedKeys, 
				std::vector<unsigned> releasedKeys);
private:
	std::map<unsigned, bool> isKeyPressed;
};

