#pragma once

#include "Enemy.h"

class PathEnemy : public Enemy
{
public:
	PathEnemy(sf::Vector2f pos, int Start, int Stop, float speed);
	virtual ~PathEnemy();

protected:
	virtual void AI(const float& DeltaTime) override;

private:
	int start, stop;
	bool turn = true;

};