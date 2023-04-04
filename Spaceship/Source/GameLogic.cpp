#include "GameLogic.h"
#include "Bullet.h"
#include "Enemy.h"


GameLogic::GameLogic(int height, int width, ConsoleDrawer* draw, InputManager* input) : height(height), width(width)
{
	logicDrawManager = draw;
	logicInputManager = input;
		
}

GameLogic::~GameLogic()
{
	delete logicInputManager;
	delete logicDrawManager;
	delete player;
}

void GameLogic::Start()
{
	initHeight = logicDrawManager->GetInitHeight();

	points = 0;

	std::ifstream recordFile;
	recordFile.open("Resources/Record.txt");
	recordFile >> record;
	recordFile.close();

	waveFile.LoadFile("Resources/Waves.xml");
	start = waveFile.FirstChildElement("START");

	player = new Player(height, width);
	AddActor(player);
	player->BeginPlay();

	gameOver = false;
}

void GameLogic::Update(float deltaTime)
{
	if (!gameOver)
	{
		std::srand(std::time(nullptr));

		EnemySpawner(deltaTime);
		Shoot(deltaTime);

		GetInput();
		UpdateActors(deltaTime);

		Draw();

		CheckCollision();
	}
}

void GameLogic::UpdateActors(float deltaTime)
{
	for (Actor* actor : actorList)
		actor->Update(deltaTime, dirY, dirX);

	dirX = 0;
	dirY = 0;
}

void GameLogic::Draw()
{
	DrawPoints();
	DrawActors();
}

void GameLogic::DrawPoints()
{
	logicDrawManager->DrawPoints(initHeight, points, record);
}

void GameLogic::DrawActors()
{
	for (Actor* actor : actorList)
		logicDrawManager->DrawAtPos(actor->GetActorChar(), actor->GetY(), actor->GetX());
}

void GameLogic::GetInput()
{
	if (logicInputManager->ReturnInput() == UP_KEY)
	{
		dirY = -1;
		dirX = 0;
	}
	if (logicInputManager->ReturnInput() == DOWN_KEY)
	{
		dirY = 1;
		dirX = 0;
	}
	if (logicInputManager->ReturnInput() == LEFT_KEY)
	{
		dirY = 0;
		dirX = -1;
	}
	if (logicInputManager->ReturnInput() == RIGHT_KEY)
	{
		dirY = 0;
		dirX = 1;
	}

	if (logicInputManager->ReturnInput() == TEST_KEY)
	{
		//DestroyActor(player);
	}
}

void GameLogic::CheckCollision()
{
	for (Actor* actor : actorList)
	{
		for (std::list<Actor*>::iterator iterator = actorList.begin(); iterator != actorList.end(); iterator++)
		{
			if (actor->GetX() == (*iterator)->GetX() && actor->GetY() == (*iterator)->GetY())
			{
				if (actor->GetActorChar() != (*iterator)->GetActorChar())
				{
					actor->OnCollision();
					(*iterator)->OnCollision();
					logicDrawManager->DrawExplosion(actor->GetY(), actor->GetX(), actor->GetCoordSize());

					if (actor == player)
					{
						gameOver = true;
						SetRecordFile(points);
						logicDrawManager->ResetScreen(' ');
						logicDrawManager->SetGameOver(gameOver);
					}
					else
					{
						IncreaseScore(100);
					}
				}
			}
		}
		if (actor->GetX() >= width - 2 || actor->GetX() <= 0)
			actor->OnCollision();
	}
	DestroyActor();
}

void GameLogic::Shoot(float dt)
{
	if (counter > (timeToShoot * dt))
	{
		Bullet* b = new Bullet(player->GetY(), player->GetX(), height, width);
		b->BeginPlay();
		AddActor(b);
		counter = 0;
	}
	counter++;
}

void GameLogic::EnemySpawner(float dt)
{
	if (enemyCounter > timeToGenerateEnemy)
	{
		if (start)
		{
			XMLElement* rounds = start->FirstChildElement("ROUNDS");
			if (rounds)
			{
				if (!wave)
				{
					wave = rounds->FirstChildElement("WAVE");
				}
				else
				{
					XMLElement* enemy = wave->FirstChildElement("ENEMY");
					if (enemy)
					{
						while (enemy)
						{
							XMLElement* coordY = enemy->FirstChildElement("coordY");
							if (coordY)
							{
								const char* string = coordY->Attribute("posY");
								std::stringstream value;
								value << string;
								value >> valueY;
							}
							GenerateEnemeies();
							enemyCounter = 0;
							enemy = enemy->NextSiblingElement("ENEMY");
						}
					}
					wave = wave->NextSiblingElement("WAVE");
				}
			}
		}
		//for (int i = 0; i < 3; i++)
		//{
		//	Enemy* e = new Enemy(height, width);
		//	AddActor(e);
		//	e->BeginPlay();
		//}
		//enemyCounter = 0;
	}
	enemyCounter += dt;
}

bool GameLogic::GetGameOver()
{
	return gameOver;
}

void GameLogic::SetGameOver(bool b)
{
	gameOver = b;
}

void GameLogic::AddActor(Actor* newActor)
{
	actorList.push_back(newActor);
}

void GameLogic::DestroyActor()
{
	for (std::list<Actor*>::iterator iterator = actorList.begin(); iterator != actorList.end(); iterator++)
	{
		if ((*iterator)->HasCollided())
		{
			actorList.remove(*iterator);
			iterator = actorList.begin();
		}
	}
}

GameLogic* GameLogic::GetGameLogic()
{
	return this;
}

void GameLogic::IncreaseScore(int p)
{
	points += (p / 2);
}

void GameLogic::SetRecordFile(int pointsToWrite)
{
	if (pointsToWrite > record)
	{
		std::ofstream tempFile;
		tempFile.open("Resources/Record.txt");
		tempFile << pointsToWrite;
		tempFile.close();
	}
}

void GameLogic::GenerateEnemeies()
{
	Enemy* e = new Enemy(valueY, width - 2);
	e->BeginPlay();
	AddActor(e);
}