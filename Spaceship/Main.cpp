#include <iostream>
#include "GameEngine.h"

int main()
{
	GameEngine* gameEngine = new GameEngine(100, 25, 110);

	gameEngine->Start();
}