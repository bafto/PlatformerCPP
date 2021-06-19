#pragma once

#include "GeneralIncludes.h"

namespace util
{
	bool RectIntersect(const sf::FloatRect& rect, const sf::FloatRect& other); //check if two rects intersec
	bool ShapeIntersect(const sf::RectangleShape& rect, const sf::RectangleShape& other); //check if two Rectangelshapes intersect
	bool ShapeVecIntersect(const sf::RectangleShape& rect, const sf::Vector2f& vec); //check if a Rectangleshape contains a point
	bool ShapeRectIntersect(const sf::RectangleShape& rect, const sf::FloatRect& other); //check if a rect and a Rectangleshape intersect

	//lets be val >= min and val <= max
	template<typename T>
	T Clamp(T val, T min, T max)
	{
		if (val < min)
			val = min;
		else if (val > max)
			val = max;
		return val;
	}
	//same as Clamp but for x and y of the Vector2
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
	//checks if (val >= min && val <= max) is true
	template<typename T>
	bool IsClamp(T val, T min, T max)
	{
		return ((val < min) || (val > max)) ? true : false;
	}
	//same as IsClamp but for x and y of the Vector2
	template<typename T>
	bool IsVecClamp(sf::Vector2<T> val, sf::Vector2<T> min, sf::Vector2<T> max)
	{
		return (val.x < min.x || val.y < min.y) || (val.x > max.x || val.y > max.y) ? true : false;
	}

	//rotates a Vector2 around a point (copied from somewhere else)
	sf::Vector2f RotateBy(sf::Vector2f spinningPoint, double radians, sf::Vector2f center = sf::Vector2f(0.f, 0.f));

	//returns the length of a Vector2 by the formula sqrt(x² + y²)
	template<typename T>
	float VecLength(sf::Vector2<T> vec)
	{
		return (float)std::sqrt((((float)vec.x * (float)vec.x) + ((float)vec.y * (float)vec.y)));
	}
	//returns the normal of a vector by the formula vec / (sqrt(x² + y²))
	template<typename T>
	sf::Vector2<T> VecNormalize(sf::Vector2<T> vec)
	{
		return vec / (T)VecLength(vec);
	}

	//return the string representation of a Vector2, for example (1, 2) becomes x: 1,y: 2
	template<typename T>
	std::string VecToString(sf::Vector2<T> vec)
	{
		return "x: " + std::to_string(vec.x) + ",y: " + std::to_string(vec.y);
	}

	//splits a string into a std::vector<strings> by the delimiter ch
	std::vector<std::string> split(const std::string& txt, char ch);
}