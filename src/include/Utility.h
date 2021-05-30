#pragma once

#include "GeneralIncludes.h"

namespace util
{
	bool RectIntersect(const sf::FloatRect& rect, const sf::FloatRect& other)
	{
		return rect.left + rect.width > other.left && rect.left < other.left + other.width &&
			rect.top + rect.height > other.top && rect.top < other.top + other.height;
	}

	bool ShapeIntersect(const sf::RectangleShape& rect, const sf::RectangleShape& other)
	{
		sf::Vector2f rectPosition = rect.getPosition();
		sf::Vector2f rectSize = rect.getSize();
		sf::Vector2f otherPosition = other.getPosition();
		sf::Vector2f otherSize = other.getSize();
		return rectPosition.x + rectSize.x > otherPosition.x && rectPosition.x < otherPosition.x + otherSize.x &&
			rectPosition.y + rectSize.y > otherPosition.y && rectPosition.y < otherPosition.y + otherSize.y;
	}
}