#pragma once

class ConsoleDrawer
{
	int height = 0;
	int initHeight = 3;
	int width = 0;
	char* screen = nullptr;

	bool isGameOver = false;

	ConsoleDrawer();

public:
	void ResetScreen(char character);
	ConsoleDrawer(int height, int width);
	~ConsoleDrawer();

	void Start();
	void Draw();
	void UpdateDraw(int n);

	void DrawAtPos(char character, int h, int w);
	void DrawAtPos(const char* string, int h, int w);

	void DrawBoard(int n);
	void DrawPoints(int headerHeight, int points, int record);

	void DrawGameOver();

	int GetInitHeight();

	void DrawBullet(int y, int x, int s);
	void DrawEmpty(int y, int x, int s);
	void DrawExplosion(int y, int x, int s);

	void SetGameOver(bool b);
};