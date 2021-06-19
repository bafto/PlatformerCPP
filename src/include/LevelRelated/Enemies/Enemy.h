#pragma once

#include "../../Entity.h"

//base class for all enemies
class Enemy : public Entity
{
public:
	//IDs mainly used for constructing the correct enemy type in level
	enum class EnemyID
	{
		Default = 0,
		Path,
		Track,
		Copy,
		Spin
	};
public:
	Enemy(sf::Vector2f pos);
	virtual ~Enemy();

	void update(const float& DeltaTime) override;

	int GetDamage() { return Damage; }

protected:
	virtual void HandleCollision() override;
	virtual void AI(const float& DeltaTime); //children override this method for their own AI movement

public:
	float speed;
	sf::Vector2f startPosition;
protected:
	int Damage;

};