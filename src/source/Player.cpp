#include "../include/Player.h"
#include "../include/Game.h"
#include "../include/Debug.h"
#include "../include/Utility.h"
#include "../include/GameException.h"

Player::Player()
	:
	Entity(),
	lastPosition(0.f, 0.f),
	speed(10.f),
	maxWalkSpeed(7.5f),
	maxJumpSpeed(10.f),
	maxFallSpeed(15.f),
	acceleration(0.5f),
	drag(15.f),
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
	rect.setFillColor(color);

	healthbar.setFillColor(sf::Color::Red);

	healthbaroutline.setFillColor(sf::Color::Transparent);
	healthbaroutline.setOutlineColor(sf::Color::White);
	healthbaroutline.setOutlineThickness(1);
	healthbaroutline.setSize(sf::Vector2f(maxHealth * 50.f, 30.f));

	Debug::Println("Player constructed");
}

Player::~Player()
{}

void Player::Initialize()
{
	Debug::Println("Initializing Player");

	if (!hitBuff.loadFromFile("assets\\sounds\\explosion.wav"))
		throw FILEEXCEPTION(std::string("assets\\sounds\\explosion.wav"));
	if (!jumpBuff.loadFromFile("assets\\sounds\\jump.wav"))
		throw FILEEXCEPTION(std::string("assets\\sounds\\jump.wav"));
	if (!deathBuff.loadFromFile("assets\\sounds\\death.wav"))
		throw FILEEXCEPTION(std::string("assets\\sounds\\death.wav"));

	hitSound.setBuffer(hitBuff);
	jumpSound.setBuffer(jumpBuff);
	deathSound.setBuffer(deathBuff);

	Debug::Println("Done initializing Player");
}

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
		color = vulnerable ? sf::Color::Blue : sf::Color(255, 127, 80);
		lastPosition = rect.getPosition();

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
					hitSound.play();
				}
			}
		}

#ifdef _DEBUG
		Game::GetInstance().AddToHUDText(ToString());
#endif
	}
}

void Player::HandleCollision()
{
	if (util::IsVecClamp(rect.getPosition(), { 0.f, 0.f }, Game::GetInstance().level.tilemap.GetPixelSize()))
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
		velocity.x -= speed * std::abs(velocity.x) * DeltaTime + acceleration;
	if (Game::GetInstance().input.KeyboardState(sf::Keyboard::D).down)
		velocity.x += speed * std::abs(velocity.x) * DeltaTime + acceleration;
	if (!grounded)
		velocity.y += Game::GetInstance().level.gravity * DeltaTime;
	if (grounded && Game::GetInstance().input.KeyboardState(sf::Keyboard::W).pressed)
	{
		velocity.y -= jumpspeed;
		jumpSound.play();
	}

	velocity.x -= velocity.x / drag;

	velocity = util::VecClamp(velocity, { -maxWalkSpeed, -maxJumpSpeed }, { maxWalkSpeed, maxFallSpeed });

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

	target.setView(Game::GetInstance().GetGameView());

#ifdef _DEBUG
	sf::CircleShape point;
	point.setRadius(2);

	point.setPosition(lastPosition);
	point.setFillColor(sf::Color::Green);
	target.draw(point);

	point.setPosition(rect.getPosition() + velocity);
	point.setFillColor(sf::Color::Blue);
	target.draw(point);

	for (unsigned int i = 0; i < trail.size(); i++)
	{
		point.setPosition(trail[i] + (rect.getSize() / 2.f));
		point.setFillColor(sf::Color::Red);
		target.draw(point);
	}

	sf::RectangleShape groundCheck;
	groundCheck.setPosition(rect.getPosition() + sf::Vector2f(0.f, 2.f));
	groundCheck.setSize(rect.getSize());
	groundCheck.setFillColor(sf::Color(255, 255, 0, 127));
	target.draw(groundCheck);
#endif
}

void Player::Kill()
{
	if (deathtimer == 0)
	{
		dead = true;
		deathSound.play();
	}
	if (deathtimer == 50)
	{
		//Game::GetInstance().gameMode = Game::GameMode::DeathScreen;
		Game::GetInstance().Reset(Game::GetInstance().level.GetFilePath());
		deathtimer = 0;
	}
}

std::string Player::ToString()
{
	return "Position: " + util::VecToString(sf::Vector2i(rect.getPosition())) + " Velocity: " + util::VecToString(velocity);
}