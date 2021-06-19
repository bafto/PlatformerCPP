#pragma once

#include "Enemy.h"

//An enemy that spins around a point, ignoring gravity
class SpinEnemy : public Enemy
{
public:
	SpinEnemy(sf::Vector2f pos, float distToAnchor, float rotationSpeed);
	virtual ~SpinEnemy();

protected:
	virtual void AI(const float& DeltaTime) override;
	virtual void HandleCollision();

private:
	float distanceToAnchor;
	float timer;

};