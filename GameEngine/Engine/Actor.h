#pragma once
#include "GameObject.h"
class Actor abstract : public GameObject
{
public:
	virtual void BeginPlay() = 0;
	virtual void Update(float dt, int y, int x) = 0;
	virtual void OnCollision() {};
	virtual bool HasCollided() { return false; };
	virtual int GetX() = 0;
	virtual int GetY() = 0;
	virtual int GetCoordSize() = 0;
	virtual char GetActorChar() = 0;
	virtual Actor* GetActorInstance() = 0;
};