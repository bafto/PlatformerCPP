#pragma once

#include "Tilemap.h"
#include "Enemies/Enemy.h"

class Level
{
public:
	Level();
	Level(std::string file);
	~Level();

	void Initialize(std::string file);
	void Reset();

	void update(const float& DeltaTime);
	void render(sf::RenderTarget& target);

	std::string GetFilePath();

private:
	void InitializeEvents();
	void InitializeEnemies();
	void InitializeTilemap();

public:
	sf::Vector2f spawnPoint;
	//std::vector<EventTrigger> EventTriggers;
	std::vector<Enemy*> Enemies;
	Tilemap tilemap;
	float gravity;

private:
	std::string FilePath;

	//used for initialization
	std::vector<std::string> fileLine;
	unsigned int counter;

};