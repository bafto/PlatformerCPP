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