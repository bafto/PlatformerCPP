#pragma once

#include "Enemy.h"

//An enemy that begins to follow the player on sight
class TrackEnemy : public Enemy
{
public:
	TrackEnemy(sf::Vector2f pos, sf::Vector2f size, float speed);
	virtual ~TrackEnemy();

protected:
	virtual void AI(const float& DeltaTime) override;

private:
	sf::Vector2f area;
	bool running = false;
};