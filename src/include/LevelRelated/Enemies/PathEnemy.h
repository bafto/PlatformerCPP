#pragma once

#include "Enemy.h"

//An enemy that follows a set path
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