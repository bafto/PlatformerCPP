#include "../include/Entity.h"
#include "../include/Game.h"
#include "../include/Utility.h"

Entity::Entity()
	:
	noGravity(false),
    color(sf::Color::Magenta),
    nextPosition(0.f, 0.f),
    velocity(0.f, 0.f)
{
	rect.setPosition({ 0, 0 });
	rect.setSize({ 50, 50 }); //every entity gets the base size (50, 50)
}

Entity::~Entity()
{}

void Entity::update(const float& DeltaTime)
{
    //update position based on gravity
	if (!noGravity)
		velocity.y += Game::GetInstance().level.gravity * DeltaTime;
    //resolve collision
	HandleCollision();
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(rect);
}

void Entity::HandleCollision()
{
    // Handle collision by checking X first then Y then both and resolving it accordingly
    sf::FloatRect nextRect = sf::FloatRect(nextPosition, rect.getSize());
    for (unsigned int i = 0; i < Game::GetInstance().level.tilemap.hitboxes.size(); i++)
    {
        sf::FloatRect& hitbox = Game::GetInstance().level.tilemap.hitboxes[i];
        if (util::RectIntersect(nextRect, hitbox))
        {
            // try only x intersection
            nextRect.left -= velocity.x;
            // still intersects?
            if (util::RectIntersect(nextRect, hitbox))
            {
                nextRect.left += velocity.x;
                // try only y intersection
                nextRect.top -= velocity.y;
                // still intersects?
                if (util::RectIntersect(nextRect, hitbox))
                {
                    // revert it cause it must be X and Y
                    nextRect.top += velocity.y;
                }
                else // no? set the position accordingly
                {
                    if (nextRect.top > hitbox.top + hitbox.height)
                    {
                        nextRect.top =  hitbox.top + hitbox.height;
                        velocity.y = 0;
                    }
                    else if (nextRect.top + nextRect.height < hitbox.top)
                    {
                        nextRect.top = hitbox.top - nextRect.height;
                        velocity.y = 0;
                    }
                    else
                    {
                        velocity.y = 0;
                    }
                }
            }
            else // no? set the position accordingly
            {
                if (nextRect.left > hitbox.left + hitbox.width)
                {
                    nextRect.left = hitbox.left + hitbox.width;
                    velocity.x = 0;
                }
                else if (nextRect.left + nextRect.width < hitbox.left)
                {
                    nextRect.left = hitbox.left - nextRect.width;
                    velocity.x = 0;
                }
                else
                {
                    velocity.x = 0;
                }
            }
        }

        // Set the new position
        rect.setPosition({ nextRect.left, nextRect.top});
    }
}