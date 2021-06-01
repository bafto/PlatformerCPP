#pragma once

#include "../Player.h"
#include "../Delegate.h"

class EventTrigger
{
public:
	enum class EventID
	{
		LevelLoader = 0
	};

public:
	EventTrigger(EventID id, sf::FloatRect bounds);

	void update(const float& DeltaTime);
	void render(sf::RenderTarget& target);
	
public:
	sf::FloatRect bounds;
	EventID eventType;
	std::string nextLevel;

	Delegate<void(Player& player)> OnPlayerInside;
	Delegate<void(Player& player)> OnPlayerEnter;
	Delegate<void(Player& player)> OnPlayerExit;
};