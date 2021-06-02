#pragma once

#include "Enemy.h"

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