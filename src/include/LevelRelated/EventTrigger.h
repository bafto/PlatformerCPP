#pragma once

#include "../Player.h"
#include "../Delegate.h"

//triggers an event (a delegate) if the player collides with a specified area
class EventTrigger
{
public:
	//used to assign the correct actions in level
	enum class EventID
	{
		LevelLoader = 0,
		GravityFlip
	};

public:
	//construct it as an area
	EventTrigger(EventID id, sf::FloatRect bounds);

	//update its state, and perform the delegates if the conditions are met
	void update(const float& DeltaTime);
	//draw the rectangle if in Debug mode
	void render(sf::RenderTarget& target);
	
public:
	sf::FloatRect bounds; //rect bounds
	EventID eventType;
	std::string nextLevel; //for LevelLoader Trigger

	Delegate<void(EventTrigger& evt, Player& player)> OnPlayerInside; //triggered while the player is inside the bounds
	Delegate<void(EventTrigger& evt, Player& player)> OnPlayerEnter; //triggered when the player enters the bounds
	Delegate<void(EventTrigger& evt, Player& player)> OnPlayerExit; //triggered when the player exits the bounds
};