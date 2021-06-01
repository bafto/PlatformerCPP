#include "../../include/LevelRelated/Level.h"
#include "../../include/Utility.h"
#include "../../include/Game.h"
#include "../../include/Debug.h"

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
	for (unsigned int i = 0; i < Enemies.size(); i++)
	{
		delete Enemies[i];
	}
	Enemies.clear();
}

void Level::Initialize(std::string file)
{
	Debug::Println("Initializing Level");

	gravity = 25.f;
	FilePath = file;
	for (unsigned int i = 0; i < Enemies.size(); i++)
	{
		delete Enemies[i];
	}
	Enemies.clear();
	//EventTriggers.clear();

	fileLine.clear();
	counter = 0;

	std::ifstream ifs(file);
	if (ifs.is_open())
	{
		//read the file
		//maybe we have to seekg(3) but we'll see
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
		//player.health = player.maxHealth;

		InitializeEvents();
		InitializeEnemies();
		InitializeTilemap();
	}
	else
	{
		throw ""; //Exception will follow
	}

	Debug::Println("Done initializing Level");
}

void Level::InitializeEvents()
{
	for (counter = 2; fileLine[counter] != "enemies:"; counter++)
	{
		std::vector<std::string> evtLine = util::split(fileLine[counter], ' ');

		/*EventTriggers.emplace_back(
			(EventID)std::stoi(evtLine[0]),
			sf::FloatRect(std::stoi(evtLine[1]), std::stoi(evtLine[2]), std::stoi(evtLine[3]), std::stoi(evtLine[4]))
		);*/

		/*if (EventTriggers[EventTriggers.size() - 1].eventType == EventID::LevelLoader)
		{
			EventTriggers[EventTriggers.size() - 1].nextLevel = evtLine[5];
			EventTriggers[EventTriggers.size() - 1].OnPlayerInside += []() { Game::GetInstance().ResetGame(EventTriggers[EventTriggers.size() - 1].nextLevel); };
		}*/
	}
}

void Level::InitializeEnemies()
{
	for (++counter; fileLine[counter] != "map:"; counter++)
	{
		std::vector<std::string> enemyLine = util::split(fileLine[counter], ' ');
		sf::Vector2f pos = { (float)std::stoi(enemyLine[1]), (float)std::stoi(enemyLine[2]) };
		switch (std::stoi(enemyLine[0]))
		{
		case (int)Enemy::EnemyID::Default:
		{
			Enemies.push_back(new Enemy(pos));
			break;
		}
		/*case (int)EnemyID::Path:
		{
			int start = std::stoi(enemyLine[3]), stop = std::stoi(enemyLine[4]);
			float speed = std::stof(enemyLine[5]);
			Enemies.push_back(new PathEnemy(pos, start, stop, speed));
			break;
		}
		case (int)EnemyID::Track:
		{
			sf::Vector2f area = sf::Vector2f(std::stoi(enemyLine[3]), std::stoi(enemyLine[4]));
			float speed = std::stof(enemyLine[5]);
			Enemies.push_back(new TrackEnemy(pos, area, speed));
			break;
		}
		case (int)EnemyID::Copy:
		{
			Enemies.push_back(new CopyEnemy(pos, std::stof(enemyLine[3])));
			break;
		}
		case (int)EnemyID::Spin:
		{
			Enemies.push_back(new SpinEnemy(pos, std::stof(enemyLine[3]), std::stof(enemyLine[4])));
			break;
		}*/
		default:
			break;
		}
	}
}

void Level::InitializeTilemap()
{
	std::vector<std::string> mapLines;
	mapLines.reserve(fileLine.size());

	for (; counter < fileLine.size(); counter++)
		mapLines.push_back(fileLine[counter]);

	tilemap.Initialize(mapLines);
}

void Level::update(const float& DeltaTime)
{
	/*for (auto& eventTrigger : EventTriggers)
	{
		eventTrigger.update(DeltaTime);
	}*/
	for (Enemy* enemy : Enemies)
	{
		enemy->update(DeltaTime);
	}
}

void Level::render(sf::RenderTarget& target)
{
	tilemap.render(target);
#ifdef _DEBUG
	/*for (auto& eventTrigger : EventTriggers)
	{
		eventTrigger.render(target);
	}*/
#endif
	for (Enemy* enemy : Enemies)
	{
		enemy->render(target);
	}
}

void Level::Reset()
{
	Game::GetInstance().player = Player();
	Initialize(FilePath);
	//Game::GetInstance().globalTimer = 0;
}

std::string Level::GetFilePath()
{
	return FilePath;
}