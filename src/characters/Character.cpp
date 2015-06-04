#include "Character.h"


Character::Character()
{
	lastFrameTime = clock();
	alive = true;
}

Character::Character(std::vector<std::string>& texturePaths, float spriteDelta, sf::Vector2f position /* = { 0, 0 } */) :
	Character()
{
	load(texturePaths, spriteDelta, position);
}

Character::Character(Character& instance, sf::Vector2f position /* = { 0, 0 } */) :
	Character()
{
	setPosition(position);
	spriteTextures = instance.spriteTextures;
	spriteDelta = instance.spriteDelta;
}

void Character::load(std::vector<std::string>& texturePaths, float spriteDelta, sf::Vector2f position /* = */ )
{
	this->spriteDelta = spriteDelta;
	spriteTextures = std::make_shared<std::vector<Drawable>>(texturePaths.size());
	for (unsigned i = 0; i < texturePaths.size(); ++i)
		(*spriteTextures)[i].load(texturePaths[i]);
	setPosition(position);
}

void Character::render()
{
	deltaTime = (float)difftime(clock(), lastFrameTime) / CLOCKS_PER_SEC * 1000.f;
	if (moving)
	{
		spriteDeltaTime += deltaTime;
		if (spriteDeltaTime >= spriteDelta)
		{
			spriteDeltaTime -= spriteDelta;
			if (++currentSprite >= spriteTextures->size())
				currentSprite = 0;
		}
	}
	else
	{
		spriteDeltaTime = 0;
		currentSprite = 0;
	}
	(*spriteTextures)[currentSprite].render();
	lastFrameTime = clock();
}

void Character::setPosition(sf::Vector2f newPos)
{
	moving = position.x != newPos.x;
	
	position = newPos;
	for (auto& i : *spriteTextures)
		i.setPosition(newPos);
}

sf::Vector2f Character::getPosition()
{
	return position;
}

bool Character::move(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks, sf::Vector2f deltaPos)
{
	if (deltaPos.x != 0.f && deltaPos.y != 0.f)
		return move(blocks, { deltaPos.x, 0.f }) || move(blocks, { 0.f, deltaPos.y });

	sf::Vector2f newPos = { position.x + deltaPos.x, position.y + deltaPos.y };
	if (newPos.x < 0.f || newPos.y < 0.f)
		return false;

	sf::Vector2f calcPos = newPos;
	bool detectedCollision = false;
	if (deltaPos.x != 0.f)
	{
		if (deltaPos.x > 0.f)
			calcPos.x += getSize().x;

		auto indStart = getBlockIndices(blocks, { calcPos.x, calcPos.y + getSize().y });
		auto indEnd = getBlockIndices(blocks, calcPos);
		for (auto y = indStart.y; y <= indEnd.y; y++)
			if (indStart.x < (*blocks).size() && y < (*blocks)[indStart.x].size() && (*blocks)[indStart.x][y])
				detectedCollision = detectedCollision || (*blocks)[indStart.x][y]->isCollidable();
	}
	else
	{
		if (deltaPos.y > 0.f)
			calcPos.y += getSize().y;

		auto indStart = getBlockIndices(blocks, calcPos);
		auto indEnd = getBlockIndices(blocks, { calcPos.x + getSize().x, calcPos.y });
		for (auto x = indStart.x; x <= indEnd.x; x++)
			if (x < (*blocks).size() && indStart.y < (*blocks)[x].size() && (*blocks)[x][indStart.y])
				detectedCollision = detectedCollision || (*blocks)[x][indStart.y]->isCollidable();
	}

	if (!detectedCollision)
	{
		setPosition(newPos);
		return true;
	}
	return false;
}

sf::Vector2u Character::getSize()
{
	return (*spriteTextures)[0].getSize();
}

void Character::handlePhysics(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks)
{
	try {
		if (move(blocks, { 0.f, speed * deltaTime / 1000.f }))
			speed += 9.81f * deltaTime;
		else
			speed = 0.f;

		if (speed > MAX_CHARACTER_SPEED)
			speed = MAX_CHARACTER_SPEED;
	} catch (std::out_of_range) {
		alive = false;
	}
}

sf::Vector2u Character::getBlockIndices(std::unique_ptr< std::vector < std::vector< std::unique_ptr <Block> > > >& blocks, sf::Vector2f pos)
{
	float x, y;
	auto& block = *(*blocks)[0][0];
	x = pos.x / block.getSize().x;
	y = (block.getPosition().y - pos.y) / block.getSize().y + 1;
	if (x <= -1.f || y <= -1.f)
		throw std::out_of_range("The gives position does not match any map coordinates");
	return{ unsigned(x), unsigned(y) };
}

bool Character::isAlive()
{
	return alive;
}
