#pragma once

#include "GeneralIncludes.h"

namespace util
{
	bool RectIntersect(const sf::FloatRect& rect, const sf::FloatRect& other);
	bool ShapeIntersect(const sf::RectangleShape& rect, const sf::RectangleShape& other);

	float Clamp(float val, float min, float max);
	sf::Vector2f Clamp(sf::Vector2f val, sf::Vector2f min, sf::Vector2f max);
	bool IsClamp(sf::Vector2f val, sf::Vector2f min, sf::Vector2f max);

	std::vector<std::string> split(const std::string& txt, char ch);
}