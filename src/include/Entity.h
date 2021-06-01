#pragma once

#include "GeneralIncludes.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update(const float& DeltaTime);
	virtual void render(sf::RenderTarget& target);

protected:
	virtual void HandleCollision();

public:
	sf::RectangleShape rect;
	sf::Vector2f nextPosition;
	sf::Vector2f velocity;
	sf::Color color;
	bool noGravity;
};