#pragma once

#include "../../Entity.h"

class Enemy : public Entity
{
public:
	Enemy(sf::Vector2f pos);

	void update(const float& DeltaTime) override;

	int GetDamage() { return Damage; }

protected:
	virtual void HandleCollision() override;
	virtual void AI();

public:
	float speed;
	sf::Vector2f startPosition;
protected:
	int Damage;

};