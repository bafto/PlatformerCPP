#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	virtual ~Player();

	void Initialize();

public:
	virtual void update(const float& DeltaTime);
	virtual void render(sf::RenderTarget& target) override;

	void Kill();

	std::string ToString();

protected:
	virtual void HandleCollision() override;

private:
	void HandleInput(const float& DeltaTime);

public:
	sf::Vector2f lastPosition;
	int health;
	bool vulnerable, dead;
	float lastDeath, gravityIndicator;
	std::vector<sf::Vector2f> trail;

private:
	float speed, drag, acceleration, maxJumpSpeed, maxFallSpeed, maxWalkSpeed, jumpspeed;
	bool grounded;
	float hitTimer;
	int deathtimer;
	int maxHealth = 5;
	sf::RectangleShape healthbar, healthbaroutline;
	sf::SoundBuffer hitBuff, jumpBuff, deathBuff;
	sf::Sound hitSound, jumpSound, deathSound;

};