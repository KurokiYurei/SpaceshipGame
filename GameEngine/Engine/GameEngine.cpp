#include "GameEngine.h"


GameEngine::GameEngine(int frameRate, int height, int width)
{
	timeManager = new TimeManager(frameRate);
	drawManager = new ConsoleDrawer(height, width);
	inputManager = new InputManager();
	logicManager = new GameLogic(height, width, drawManager, inputManager);
}

GameEngine::~GameEngine()
{
	delete timeManager;
	delete drawManager;
	delete inputManager;
	delete logicManager;
}

void GameEngine::Start()
{
	logicManager->Start();
	drawManager->Start();
	inputManager->Start();
	MainLoop();
}

void GameEngine::MainLoop()
{
	bool shouldStayAtMainLoop = true;

	while (shouldStayAtMainLoop)
	{
		timeManager->Update();

		if (timeManager->ShouldExecuteNextFrame()) //passa un frame
		{
			Update(timeManager->GetElapsedTime());
			Draw();
			timeManager->NextFrameExecuted();
		}
	}
}

void GameEngine::Update(float deltaTime)
{
	logicManager->Update(deltaTime);
	//logicManager->Draw(deltaTime);

}

void GameEngine::Draw()
{
	//drawManager->Draw();
	drawManager->UpdateDraw(drawManager->GetInitHeight());
}

void GameEngine::AddActor(Actor* a)
{
	logicManager->AddActor(a);
}

GameLogic* GameEngine::GetLogic()
{
	return logicManager;
}

GameEngine* GameEngine::GetGameEngine()
{
	return this;
}
