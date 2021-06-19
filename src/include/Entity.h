#pragma once

#include "GeneralIncludes.h"

//base class for Player and enemies
class Entity
{
public:
	Entity();
	virtual ~Entity();

	//update position, resolve collision etc.
	virtual void update(const float& DeltaTime);
	virtual void render(sf::RenderTarget& target);

protected:
	virtual void HandleCollision(); //resolve collision

public:
	sf::RectangleShape rect; //the rectangle that manages position, size... and is drawn
	sf::Vector2f nextPosition; //the new position after position update (used in HandleCollision)
	sf::Vector2f velocity;
	sf::Color color;
	bool noGravity; //turn gravity on or off
};