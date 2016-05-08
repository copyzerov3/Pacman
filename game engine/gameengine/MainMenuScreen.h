#pragma once
#include "Screen.h"
#include "Button.h"
class MainMenuScreen :
	public Screen
{
public:
	MainMenuScreen(int ScreenWidth, int ScreenHeight, int HighScore, irrklang::ISoundEngine* EngineRef);
	~MainMenuScreen();
	virtual void Update(int ScreenWidth, int ScreenHeight,int DeltaTime);
	virtual void Draw(int ScreenWidth, int ScreenHeight);
private:
	Button *PlayButton, *ExitButton;
};

