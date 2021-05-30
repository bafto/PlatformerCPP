#include "../include/Entity.h"
#include "../include/Game.h"
#include "../include/Utility.h"

Entity::Entity()
	:
	noGravity(false)
{
	rect.setPosition({ 0, 0 });
	rect.setSize({ 50, 50 });
}

Entity::~Entity()
{}

void Entity::update(const float DeltaTime)
{
	/*if (!noGravity)
		velocity.y += Game::GetInstance().level.gravity * DeltaTime;*/ //uncomment when levels are added
	HandleCollision();
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(rect);
}

void Entity::HandleCollision()
{
    /*
    // Handle collision by checking X first then Y then both and resolving it accordingly
    sf::FloatRect nextRect = sf::FloatRect(nextPosition, rect.getSize());
    for (int i = 0; i < Game::GetInstance().level.tilemap.hitboxes.Count; i++)
    {
        sf::FloatRect& hitbox = Game::GetInstance().level.tilemap.hitboxes[i];
        if (util::RectIntersect(nextRect, hitbox)
        {
            // try only x intersection
            nextRect.left -= velocity.x;
            // still intersects?
            if (util::RectIntersect(nextRect, hitbox)
            {
                nextRect.left += velocity.x;
                // try only y intersection
                nextRect.top -= velocity.y;
                // still intersects?
                if (util::RectIntersect(nextRect, hitbox)
                {
                    // revert it cause it must be X and Y
                    nextRect.top += velocity.y;
                }
                else // no? set the position accordingly
                {
                    if (nextRect.top > sf::Vector2f(hitbox.left + hitbox.width, hitbox.top + hitbox.height))
                    {
                        nextRect.top = sf::Vector2f(hitbox.left + hitbox.width, hitbox.top + hitbox.height);
                        velocity.y = 0;
                    }
                    else if (nextRect.top + nextRect.height < hitbox.top)
                    {
                        nextRect.top = hitbox.top - nextRect.height;
                        velocity.Y = 0;
                    }
                    else
                    {
                        velocity.Y = 0;
                    }
                }
            }
            else // no? set the position accordingly
            {
                if (nextRect.left > sf::Vector2f(hitbox.left + hitbox.width))
                {
                    nextRect.Position.X = sf::Vector2f(hitbox.left + hitbox.width);
                    velocity.X = 0;
                }
                else if (nextRect.left + nextRect.width < hitbox.left)
                {
                    nextRect.x = hitbox.left - nextRect.width;
                    velocity.X = 0;
                }
                else
                {
                    velocity.X = 0;
                }
            }
        }

        // Set the new position
        rect.setPosition({ nextRect.left, nextRect.top});
    }*/
}