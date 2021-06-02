#pragma once

#include "Enemy.h"

class CopyEnemy : public Enemy
{
public:
	CopyEnemy(sf::Vector2f pos, float dist);
	virtual ~CopyEnemy();

protected:
	virtual void AI(const float& DeltaTime) override;

private:
	float distanceToPlayer;
};