#pragma once

#include "Tilemap.h"
#include "Enemies/Enemy.h"
#include "EventTrigger.h"

//manages a level consisting of a tilemap, enemies and eventtriggers
class Level
{
public:
	Level();
	Level(std::string file); //calls Initialize with file
	~Level();

	//calls the other Initialize methods using fileLines from file
	void Initialize(std::string file);

	void update(const float& DeltaTime);
	void render(sf::RenderTarget& target);

	//returns the path the level was loaded from
	std::string GetFilePath();

private:
	void InitializeEvents();
	void InitializeEnemies();
	void InitializeTilemap();

public:
	sf::Vector2f spawnPoint; //player spawnpoint
	std::vector<EventTrigger> EventTriggers;
	std::vector<Enemy*> Enemies;
	Tilemap tilemap;
	float gravity;

private:
	std::string FilePath;

	//used for initialization
	std::vector<std::string> fileLine;
	unsigned int counter;

};