#pragma once

#include "GeneralIncludes.h"

namespace util
{
	bool RectIntersect(const sf::FloatRect& rect, const sf::FloatRect& other);
	bool ShapeIntersect(const sf::RectangleShape& rect, const sf::RectangleShape& other);

	std::vector<std::string> split(const std::string& txt, char ch);
}