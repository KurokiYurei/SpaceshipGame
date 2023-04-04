#pragma once
#include <windows.h>

#define UP_KEY char(0x26)
#define DOWN_KEY char(0x28)
#define LEFT_KEY char(0x25)
#define RIGHT_KEY char(0x27)
#define TEST_KEY char(0x5A)

class InputManager
{
public:
	InputManager();
	~InputManager();

	void Start();
	void Update();

	char ReturnInput();
};

