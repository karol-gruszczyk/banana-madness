#pragma once

#include <src/map/blocks/Block.h>


class FallingBlock : public Block
{
public:
	FallingBlock(std::string imagePath, sf::Vector2u mapPosition = {});
	FallingBlock(FallingBlock& instance, sf::Vector2u mapPosition = {});
	void render();
	bool isCollidable(bool isPlayer = false);
private:
	bool touched;
};

