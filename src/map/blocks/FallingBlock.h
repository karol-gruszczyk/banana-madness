#pragma once

#include <src/map/blocks/Block.h>


class FallingBlock : public Block
{
public:
	FallingBlock(std::string imagePath, sf::Vector2u mapPosition = {});
	FallingBlock(FallingBlock& instance, sf::Vector2u mapPosition = {});
	virtual void render();
	virtual bool isCollidable(bool isPlayer, sf::Vector2f direction);
private:
	bool touched;
};

