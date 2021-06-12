#pragma once

#include "../Player.h"
#include "../Delegate.h"

class EventTrigger
{
public:
	enum class EventID
	{
		LevelLoader = 0,
		GravityFlip
	};

public:
	EventTrigger(EventID id, sf::FloatRect bounds);

	void update(const float& DeltaTime);
	void render(sf::RenderTarget& target);
	
public:
	sf::FloatRect bounds;
	EventID eventType;
	std::string nextLevel;

	Delegate<void(EventTrigger& evt, Player& player)> OnPlayerInside;
	Delegate<void(EventTrigger& evt, Player& player)> OnPlayerEnter;
	Delegate<void(EventTrigger& evt, Player& player)> OnPlayerExit;
};