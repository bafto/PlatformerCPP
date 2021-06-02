#include "../include/Utility.h"

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

	bool ShapeRectIntersect(const sf::RectangleShape& rect, const sf::FloatRect& other)
	{
		return other.intersects({ rect.getPosition(), rect.getSize() });
	}

	float Clamp(float val, float min, float max)
	{
		if (val < min)
			val = min;
		else if (val > max)
			val = max;
		return val;
	}

	sf::Vector2f Clamp(sf::Vector2f val, sf::Vector2f min, sf::Vector2f max)
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

	bool IsClamp(sf::Vector2f val, sf::Vector2f min, sf::Vector2f max)
	{
		return (val.x < min.x || val.y < min.y) || (val.x > max.x || val.y > max.y) ? true : false;
	}


	sf::Vector2f RotateBy(sf::Vector2f spinningPoint, double radians, sf::Vector2f center)
	{
		float cos = (float)std::cos(radians);
		float sin = (float)std::sin(radians);
		sf::Vector2f vector = spinningPoint - center;
		sf::Vector2f result = center;
		result.x += vector.x * cos - vector.y * sin;
		result.y += vector.x * sin + vector.y * cos;
		return result;
	}


	std::vector<std::string> split(const std::string& txt, char ch)
	{
		std::vector<std::string> strs;
		size_t pos = txt.find(ch);
		size_t initialPos = 0;
		strs.clear();

		// Decompose statement
		while (pos != std::string::npos) {
			strs.push_back(txt.substr(initialPos, pos - initialPos));
			initialPos = pos + 1;

			pos = txt.find(ch, initialPos);
		}

		// Add the last one
		strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

		return strs;
	}
}