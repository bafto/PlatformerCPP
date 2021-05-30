#pragma once

#include "GeneralIncludes.h"

class Player
{
public:
	Player();
	~Player();

public:
	void update(const float DeltaTime);
	void render(sf::RenderTarget& target);
private:
	sf::RectangleShape rect;
};