#pragma once
#include "Actor.h"

#define TYPE_A ']'
#define TYPE_B '<'
#define TYPE_C char(21)
#define TYPE_D char(15)

enum EnemyType
{
	enemyA,
	enemyB,
	enemyC,
	enemyD
};

class Enemy : public Actor
{
	int height;
	int initHeight;
	int width;

	std::vector<Transform> enemyCoords;
	char enemyChar;

	int enemyY;
	int enemyX;
	int enemySpeed;

	int randType;
	int randHeight;

	bool enemyCollision;

	Enemy();
public:
	Enemy(int h, int w);

	void BeginPlay() override;
	void Update(float dt, int y, int x) override;
	void OnCollision() override;
	bool HasCollided() override;

	int GetY() override;
	int GetX() override;
	int GetCoordSize() override;
	char GetActorChar() override;

	void SetRandomEnemyType();
	int GetRandomEnemyHeight();
	Actor* GetActorInstance();
};

