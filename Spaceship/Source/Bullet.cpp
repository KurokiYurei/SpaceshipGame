#include "Bullet.h"

Bullet::Bullet(int y, int x, int h, int w) : height(h), width(w)
{
	bulletY = y;
	bulletX = x + 2;
}

Bullet::~Bullet()
{
}

void Bullet::BeginPlay()
{
	bulletChar = BULLET_CHAR;
	bulletSpeed = 100;
	bulletCollision = false;
	bulletCoords.push_back({ bulletY, bulletX });
}

void Bullet::Update(float dt, int y, int x)
{
	for (int i = 0; i < bulletCoords.size(); i++)
	{
		bulletX = bulletCoords.at(i).x += (bulletSpeed * dt);
	}
}
void Bullet::OnCollision()
{
	bulletCollision = true;
}

bool Bullet::HasCollided()
{
	return bulletCollision;
}

int Bullet::GetY()
{
	return bulletY;
}

int Bullet::GetX()
{
	return bulletX;
}

int Bullet::GetCoordSize()
{
	return bulletCoords.size();
}

char Bullet::GetActorChar()
{
	return bulletChar;
}

Actor* Bullet::GetActorInstance()
{
	return this;
}

