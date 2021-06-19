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

	std::string ToString(); //a string containing position, velocity etc.

protected:
	virtual void HandleCollision() override;

private:
	//Handle movement input
	void HandleInput(const float& DeltaTime);

	void Kill(); //called when the player should die

public:
	sf::Vector2f lastPosition; //not really in use, just for Debug drawing
	int health;
	bool vulnerable, dead;
	float lastDeath, gravityIndicator; //gravity indicator is set to -1 if the gravity shall be upside down and 1 for normal gravity
	std::vector<sf::Vector2f> trail; //for the copy enemy to follow

private:
	float speed, drag, acceleration, maxJumpSpeed, maxFallSpeed, maxWalkSpeed, jumpspeed; //movement variables (set in the constructor)
	bool grounded; //for jumping and collision. checks if the player is standing on ground
	float hitTimer;
	int deathtimer;
	int maxHealth = 5;
	sf::RectangleShape healthbar, healthbaroutline;
	//sound stuff
	sf::SoundBuffer hitBuff, jumpBuff, deathBuff;
	sf::Sound hitSound, jumpSound, deathSound;

};