#pragma once
#include "Actor.h"

#define PLAYER_CHAR char(16)

class Player : public Actor
{
	int height = 0;
	int initHeight = 0;
	int width = 0;

	std::vector<Transform> playerCoords;
	char playerChar;

	int l_y;
	int l_x;

	int speed;

	bool playerCollision;

	Player();
public:
	Player(int h, int w);
	~Player();

	void BeginPlay() override;
	void Update(float dt, int y, int x) override;
	void OnCollision() override;
	bool HasCollided() override;

	void Move(float dt, int y, int x);

	int GetY() override;
	int GetX() override;
	int GetCoordSize() override;
	char GetActorChar() override;

	Actor* GetActorInstance() override;
};