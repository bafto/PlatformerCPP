#pragma once

#include "GeneralIncludes.h"

namespace util
{
	bool RectIntersect(const sf::FloatRect& rect, const sf::FloatRect& other);
	bool ShapeIntersect(const sf::RectangleShape& rect, const sf::RectangleShape& other);
	bool ShapeRectIntersect(const sf::RectangleShape& rect, const sf::FloatRect& other);

	float Clamp(float val, float min, float max);
	sf::Vector2f Clamp(sf::Vector2f val, sf::Vector2f min, sf::Vector2f max);
	bool IsClamp(sf::Vector2f val, sf::Vector2f min, sf::Vector2f max);

	sf::Vector2f RotateBy(sf::Vector2f spinningPoint, double radians, sf::Vector2f center = sf::Vector2f(0.f, 0.f));

	std::vector<std::string> split(const std::string& txt, char ch);
}