#pragma once
#include "Actor.h"

#define BULLET_CHAR char(250)
class Bullet : public Actor
{
	int height;
	int width;

	std::vector<Transform> bulletCoords;
	char bulletChar;

	int bulletY;
	int bulletX;

	int bulletSpeed;

	bool bulletCollision;

	Bullet();
public:
	Bullet(int y, int x, int h, int w);
	~Bullet();

	void BeginPlay() override;
	void Update(float dt, int y, int x) override;
	void OnCollision() override;
	bool HasCollided() override;

	int GetX() override;
	int GetY() override;
	int GetCoordSize() override;
	char GetActorChar() override;

	Actor* GetActorInstance();
};

