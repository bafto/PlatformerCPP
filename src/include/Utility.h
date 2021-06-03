#pragma once

#include "GeneralIncludes.h"

namespace util
{
	bool RectIntersect(const sf::FloatRect& rect, const sf::FloatRect& other);
	bool ShapeIntersect(const sf::RectangleShape& rect, const sf::RectangleShape& other);
	bool ShapeRectIntersect(const sf::RectangleShape& rect, const sf::FloatRect& other);

	template<typename T>
	T Clamp(T val, T min, T max)
	{
		if (val < min)
			val = min;
		else if (val > max)
			val = max;
		return val;
	}
	template<typename T>
	sf::Vector2<T> VecClamp(sf::Vector2<T> val, sf::Vector2<T> min, sf::Vector2<T> max)
	{
		if (val.x < min.x)
			val.x = min.x;
		else if (val.x > max.x)
			val.x = max.x;
		if (val.y < min.y)
			val.y = min.y;
		else if (val.y > max.y)
			val.y = max.y;
		return val;
	}
	template<typename T>
	bool IsClamp(T val, T min, T max)
	{
		return ((val < min) || (val > max)) ? true : false;
	}
	template<typename T>
	bool IsVecClamp(sf::Vector2<T> val, sf::Vector2<T> min, sf::Vector2<T> max)
	{
		return (val.x < min.x || val.y < min.y) || (val.x > max.x || val.y > max.y) ? true : false;
	}

	sf::Vector2f RotateBy(sf::Vector2f spinningPoint, double radians, sf::Vector2f center = sf::Vector2f(0.f, 0.f));

	template<typename T>
	float VecLength(sf::Vector2<T> vec)
	{
		return (float)std::sqrt((((float)vec.x * (float)vec.x) + ((float)vec.y * (float)vec.y)));
	}
	template<typename T>
	sf::Vector2<T> VecNormalize(sf::Vector2<T> vec)
	{
		return vec / (T)VecLength(vec);
	}

	template<typename T>
	std::string VecToString(sf::Vector2<T> vec)
	{
		return "x: " + std::to_string(vec.x) + ",y:" + std::to_string(vec.y);
	}

	std::vector<std::string> split(const std::string& txt, char ch);
}