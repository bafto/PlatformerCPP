#pragma once

#include "Enemy.h"

//An enemy that copys the players movement
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