#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	virtual ~Player();

public:
	virtual void update(const float& DeltaTime);

public:
	float speed;
};