#include "../../include/LevelRelated/EventTrigger.h"
#include "../../include/Game.h"
#include "../../include/Utility.h"

EventTrigger::EventTrigger(EventID id, sf::FloatRect bounds)
	:
	bounds(bounds),
	eventType(id),
	nextLevel("")
{

}

void EventTrigger::update(const float& DeltaTime)
{
	sf::FloatRect lastPlayerRect = sf::FloatRect(Game::GetInstance().player.lastPosition, { 50.f, 50.f });
    if (util::ShapeRectIntersect(Game::GetInstance().player.rect, bounds))
    {
        OnPlayerInside(*this, Game::GetInstance().player);
    }
    if (util::ShapeRectIntersect(Game::GetInstance().player.rect, bounds) && !lastPlayerRect.intersects(bounds))
    {
        OnPlayerEnter(*this, Game::GetInstance().player);
    }
    if (!util::ShapeRectIntersect(Game::GetInstance().player.rect, bounds) && lastPlayerRect.intersects(bounds))
    {
        OnPlayerExit(*this, Game::GetInstance().player);
    }
}

void EventTrigger::render(sf::RenderTarget& target)
{
#ifdef _DEBUG
    sf::RectangleShape shape;
    shape.setFillColor(sf::Color(255, 0, 0, 128));
    shape.setSize(sf::Vector2f(bounds.width, bounds.height));
    shape.setPosition(sf::Vector2f(bounds.left, bounds.top));
    target.draw(shape);
#endif
}