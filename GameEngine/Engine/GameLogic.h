#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <list>
#include <fstream> 
#include "External\tinyxml2.h"
#include <sstream>
#include "ConsoleDrawer.h"
#include "InputManager.h"
#include "Actor.h"
#include "Player.h"

using namespace tinyxml2;

class GameLogic
{
	int height = 0;
	int initHeight = 0;
	int width = 0;

	ConsoleDrawer* logicDrawManager;
	InputManager* logicInputManager;

	int points = 0;
	int record = 0;

	int randHeight = 0;
	int randWidth = 0;

	int l_y;
	int l_x;

	int dirX = 1;
	int dirY = 0;

	int counter = 0;
	int timeToShoot = 5;

	float enemyCounter = 0;
	float timeToGenerateEnemy = 0.20;

	int valueY = 0;

	std::list<Actor*> actorList;

	Player* player;

	bool gameOver;

	TinyXMLDocument waveFile;
	XMLElement* start;
	XMLElement* wave;

	GameLogic();
public:
	GameLogic(int height, int width, ConsoleDrawer* d, InputManager* i);
	~GameLogic();

	void Start();

	void Update(float deltaTime);
	void UpdateActors(float deltaTime);

	void Draw();
	void DrawPoints();
	void DrawActors();

	void GetInput();

	void CheckCollision();

	void Shoot(float dt);
	void EnemySpawner(float dt);

	bool GetGameOver();
	void SetGameOver(bool b);

	void AddActor(Actor* a);
	void DestroyActor();

	GameLogic* GetGameLogic();

	void IncreaseScore(int p);
	void SetRecordFile(int p);

	void GenerateEnemeies();
};

