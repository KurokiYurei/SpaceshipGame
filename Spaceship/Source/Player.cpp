#include "Player.h"
#include "Bullet.h"

Player::Player()
{

};

Player::Player(int h, int w) : height(h), width(w)
{
}

Player::~Player()
{
	delete this;
}

void Player::BeginPlay()
{
	l_y = height / 2;
	l_x = width / 8;
	playerCoords.push_back({ l_y, l_x });

	playerChar = PLAYER_CHAR;

	playerCollision = false;

	speed = 2.5;
}

void Player::Update(float dt, int dirY, int dirX)
{
	Move(dt, dirY, dirX);
}

void Player::OnCollision()
{
	playerCollision = true;
}

bool Player::HasCollided()
{
	return playerCollision;
}

void Player::Move(float dt, int dirY, int dirX)
{
	for (int i = 0; i < playerCoords.size(); i++)
	{
		if (i == 0)
		{
			if (((l_y > 4) && (dirY == -1)) || ((l_y < height - 2) && (dirY == 1)))
				l_y = playerCoords[i].y += dirY;

			if (((l_x > 2) && (dirX == -1)) || ((l_x < width / 4) && (dirX == 1)))
				l_x = playerCoords[i].x += dirX;
		}
	}
}

int Player::GetY()
{
	return l_y;
}
int Player::GetX()
{
	return l_x;
}

int Player::GetCoordSize()
{
	return playerCoords.size();
}

char Player::GetActorChar()
{
	return playerChar;
}


Actor* Player::GetActorInstance()
{
	return this;
}