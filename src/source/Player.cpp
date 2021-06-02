#include "../include/Player.h"
#include "../include/Game.h"
#include "../include/Debug.h"
#include "../include/Utility.h"

Player::Player()
	:
	Entity(),
	lastPosition(0.f, 0.f),
	speed(10.f),
	maxWalkSpeed(10.f),
	maxJumpSpeed(10.f),
	maxFallSpeed(15.f),
	acceleration(0.5f),
	drag(5.f),
	jumpspeed(13.f),
	health(5),
	vulnerable(true),
	hitTimer(0.f),
	deathtimer(0),
	dead(false),
	grounded(false),
	lastDeath(0)
{
	//override stuff from entity
	color = sf::Color::Blue;
	rect.setFillColor(sf::Color::Red);

	healthbar.setFillColor(sf::Color::Red);

	healthbaroutline.setFillColor(sf::Color::Transparent);
	healthbaroutline.setOutlineColor(sf::Color::White);
	healthbaroutline.setOutlineThickness(1);
	healthbaroutline.setSize(sf::Vector2f(maxHealth * 50.f, 30.f));

	Debug::Println("Player constructed");
}

Player::~Player()
{}

void Player::update(const float& DeltaTime)
{
	if (health <= 0 || dead == true)
	{
		Kill();
		deathtimer++;
	}
	else
	{
		lastDeath += DeltaTime;
		hitTimer += DeltaTime;
		vulnerable = hitTimer >= 1.f / Game::GetInstance().GetDifficulty();
		color = vulnerable ? sf::Color::Red : sf::Color(255, 127, 80);
		lastPosition = rect.getPosition();

		if (!grounded)
			velocity.y += Game::GetInstance().level.gravity * DeltaTime;

		grounded = Game::GetInstance().level.tilemap.Collides(sf::FloatRect(rect.getPosition() + sf::Vector2f(0.f, 2.f), rect.getSize()));

		HandleInput(DeltaTime);

		HandleCollision();

		if (vulnerable)
		{
			for (Enemy* e : Game::GetInstance().level.Enemies)
			{
				if (util::ShapeIntersect(e->rect, rect) && vulnerable)
				{
					health -= e->GetDamage();
					hitTimer = 0.f;
					vulnerable = false;
					//onHit.Play();
				}
			}
		}
	}
}

void Player::HandleCollision()
{
	if (util::IsClamp(rect.getPosition(), { 0.f, 0.f }, Game::GetInstance().level.tilemap.GetPixelSize()))
		dead = true;
	else
		Entity::HandleCollision();
}

void Player::HandleInput(const float& DeltaTime)
{
#ifdef _DEBUG
	if (Game::GetInstance().input.MouseState(sf::Mouse::Left).pressed)
		rect.setPosition(Game::GetInstance().input.MousePosWorld() - rect.getSize() / 2.f);
#endif
	if (Game::GetInstance().input.KeyboardState(sf::Keyboard::A).down)
		velocity.x -= 10 * std::abs(velocity.x) * DeltaTime + acceleration;
	if (Game::GetInstance().input.KeyboardState(sf::Keyboard::D).down)
		velocity.x += 10 * std::abs(velocity.x) * DeltaTime + acceleration;
	if (grounded && Game::GetInstance().input.KeyboardState(sf::Keyboard::W).down)
	{
		velocity.y -= jumpspeed;
		//onJump.play();
	}

	velocity.x -= velocity.x / 15.f;

	velocity = util::Clamp(velocity, { -maxWalkSpeed, -maxJumpSpeed }, { maxWalkSpeed, maxFallSpeed });

	trail.push_back(rect.getPosition());
	if (trail.size() > 60)
		trail.erase(trail.begin());

	nextPosition = rect.getPosition() + velocity;
}

void Player::render(sf::RenderTarget& target)
{
	rect.setFillColor(color);
	Entity::render(target);

	sf::View HUDView = Game::GetInstance().GetHUDView();
	target.setView(HUDView);

	healthbar.setSize({ health * 50.f, 30.f });
	healthbar.setPosition(sf::Vector2f(HUDView.getSize().x / 2.f - (maxHealth * 50) / 2, 30));
	target.draw(healthbar);

	healthbaroutline.setPosition(healthbar.getPosition());
	target.draw(healthbaroutline);

	target.setView(Game::GetInstance().GetNormalView());
}

void Player::Kill()
{
	if (deathtimer == 0)
	{
		dead = true;
		//onDeath.Play();
	}
	if (deathtimer == 50)
	{
		//Game::GetInstance().gameMode = Game::GameMode::DeathScreen;
		deathtimer = 0;
	}
}