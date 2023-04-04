#include "Enemy.h"

Enemy::Enemy(int h, int w) : height(h), width(w)
{
}

void Enemy::BeginPlay()
{
	std::srand(std::time(nullptr));
	SetRandomEnemyType();
	//enemyY = GetRandomEnemyHeight();
	enemyY = height;
	enemyX = width - 2;
	enemyCoords.push_back({ enemyY, enemyX });
	enemySpeed = 200;

	enemyCollision = false;
}

void Enemy::Update(float dt, int y, int x)
{
	for (int i = 0; i < enemyCoords.size(); i++)
	{
		enemyX = enemyCoords.at(i).x -= (enemySpeed * dt);
	}
}

void Enemy::OnCollision()
{
	enemyCollision = true;
}

bool Enemy::HasCollided()
{
	return enemyCollision;
}

void Enemy::SetRandomEnemyType()
{
	std::srand(std::time(nullptr));

	randType = rand() % 4;

	switch (randType)
	{
	case enemyA:
		enemyChar = TYPE_A;
		break;
	case enemyB:
		enemyChar = TYPE_B;
		break;
	case enemyC:
		enemyChar = TYPE_C;
		break;
	case enemyD:
		enemyChar = TYPE_D;
		break;
	default:
		enemyChar = '0';
		break;
	}
}

int Enemy::GetRandomEnemyHeight()
{
	return (4 + rand() % (height - 5));
}

int Enemy::GetY()
{
	return enemyY;
}

int Enemy::GetX()
{
	return enemyX;
}

int Enemy::GetCoordSize()
{
	return enemyCoords.size();
}

char Enemy::GetActorChar()
{
	return enemyChar;
}

Actor* Enemy::GetActorInstance()
{
	return this;
}