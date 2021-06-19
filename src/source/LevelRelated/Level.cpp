#include "../../include/LevelRelated/Level.h"
#include "../../include/Utility.h"
#include "../../include/Game.h"
#include "../../include/Debug.h"
#include "../../include/GameException.h"

#include "../../include/LevelRelated/Enemies/CopyEnemy.h"
#include "../../include/LevelRelated/Enemies/SpinEnemy.h"
#include "../../include/LevelRelated/Enemies/TrackEnemy.h"
#include "../../include/LevelRelated/Enemies/PathEnemy.h"

#pragma warning (disable : 26812)

Level::Level()
	:
	gravity(25.f),
	spawnPoint(0, 0),
	counter(0),
	FilePath("")
{
	Debug::Println("Instanciated Level");
}

Level::Level(std::string file)
{
	Initialize(file);
	Debug::Println("Instanciated Level");
}

Level::~Level()
{
	//clear enemies
	for (unsigned int i = 0; i < Enemies.size(); i++)
	{
		delete Enemies[i];
	}
	Enemies.clear();
}

void Level::Initialize(std::string file)
{
	Debug::Println("Initializing Level");

	gravity = 25.f; //reset gravity if it was changed
	FilePath = file; //set the file path
	//clear enemies
	for (unsigned int i = 0; i < Enemies.size(); i++)
	{
		delete Enemies[i];
	}
	Enemies.clear();
	EventTriggers.clear();

	fileLine.clear();
	counter = 0;

	//load the file
	std::ifstream ifs(file);
	if (ifs.is_open())
	{
		//read the file line by line
		for (std::string line; std::getline(ifs, line);)
		{
			fileLine.push_back(line);
		}

		//set spawnpoint
		std::vector<std::string> spLine = util::split(fileLine[0], ' ');
		spawnPoint = sf::Vector2f((float)std::stoi(spLine[0]), (float)std::stoi(spLine[1]));

		//reset Player
		Player& player = Game::GetInstance().player;
		player.rect.setPosition(spawnPoint);
		player.velocity = { 0.f, 0.f };

		InitializeEvents();
		InitializeEnemies();
		InitializeTilemap();
	}
	else
	{
		throw FILEEXCEPTION(file); 
	}

	Debug::Println("Done initializing Level");
}

void Level::InitializeEvents()
{
	//loop until all events are initialized
	for (counter = 2; fileLine[counter] != "enemies:"; counter++)
	{
		//split the current line into the different parameters
		std::vector<std::string> evtLine = util::split(fileLine[counter], ' ');

		//create a new EventTrigger with the parameters from the line
		EventTriggers.emplace_back(
			(EventTrigger::EventID)std::stoi(evtLine[0]),
			sf::FloatRect((float)std::stoi(evtLine[1]), (float)std::stoi(evtLine[2]), (float)std::stoi(evtLine[3]), (float)std::stoi(evtLine[4]))
		);

		//set the events actions depending on its ID
		EventTrigger& lastTrigger = EventTriggers[EventTriggers.size() - 1];
		switch (lastTrigger.eventType)
		{
		case EventTrigger::EventID::LevelLoader:
			lastTrigger.nextLevel = "assets\\Levels\\" + evtLine[5];
			lastTrigger.OnPlayerInside += [&](EventTrigger& evt, Player&)
			{ 
				Game::GetInstance().Reset(evt.nextLevel);
			};
			break;
		case EventTrigger::EventID::GravityFlip:
			lastTrigger.OnPlayerEnter += [&](EventTrigger&, Player& player) { player.gravityIndicator = -player.gravityIndicator; };
			lastTrigger.OnPlayerExit += [&](EventTrigger&, Player& player) { player.gravityIndicator = -player.gravityIndicator; };
			break;
		default:
			break;
		}
	}
}

void Level::InitializeEnemies()
{
	//loop until all enemies are initialized
	for (++counter; fileLine[counter] != "map:"; counter++)
	{
		//split the line into the different parameters
		std::vector<std::string> enemyLine = util::split(fileLine[counter], ' ');
		sf::Vector2f pos = { (float)std::stoi(enemyLine[1]), (float)std::stoi(enemyLine[2]) }; //position of the new enemy
		//construct a new enemy depending on the ID
		switch (std::stoi(enemyLine[0]))
		{
		case (int)Enemy::EnemyID::Default:
		{
			Enemies.push_back(new Enemy(pos));
			break;
		}
		case (int)Enemy::EnemyID::Path:
		{
			int start = std::stoi(enemyLine[3]), stop = std::stoi(enemyLine[4]);
			float speed = std::stof(enemyLine[5]);
			Enemies.push_back(new PathEnemy(pos, start, stop, speed));
			break;
		}
		case (int)Enemy::EnemyID::Track:
		{
			sf::Vector2f area = sf::Vector2f((float)std::stoi(enemyLine[3]), (float)std::stoi(enemyLine[4]));
			float speed = std::stof(enemyLine[5]);
			Enemies.push_back(new TrackEnemy(pos, area, speed));
			break;
		}
		case (int)Enemy::EnemyID::Copy:
		{
			Enemies.push_back(new CopyEnemy(pos, std::stof(enemyLine[3])));
			break;
		}
		case (int)Enemy::EnemyID::Spin:
		{
			Enemies.push_back(new SpinEnemy(pos, std::stof(enemyLine[3]), std::stof(enemyLine[4])));
			break;
		}
		default:
			break;
		}
	}
}

void Level::InitializeTilemap()
{
	std::vector<std::string> mapLines;
	mapLines.reserve(fileLine.size());

	//get mapLines from the rest of the file
	for (; counter < fileLine.size(); counter++)
		mapLines.push_back(fileLine[counter]);

	//initialize the tilemap with the lines
	tilemap.Initialize(mapLines);
}

void Level::update(const float& DeltaTime)
{
	for (auto& eventTrigger : EventTriggers)
	{
		eventTrigger.update(DeltaTime);
	}
	for (Enemy* enemy : Enemies)
	{
		enemy->update(DeltaTime);
	}
}

void Level::render(sf::RenderTarget& target)
{
	tilemap.render(target);
	for (auto& eventTrigger : EventTriggers)
	{
		eventTrigger.render(target);
	}
	for (Enemy* enemy : Enemies)
	{
		enemy->render(target);
	}
}

std::string Level::GetFilePath()
{
	return FilePath;
}