#pragma once
#include "Screen.h"
#include "Button.h"
class GameOverScreen :
	public Screen
{
public:
	GameOverScreen(int ScreenWidth, int ScreenHeight, int Score, int HighScore, irrklang::ISoundEngine* EngineRef);
	~GameOverScreen();
	virtual bool Load(int width, int height);
	virtual void Draw(int width, int height);
	virtual void Update(int width, int height,int DeltaTime);
private:
	int NewScore;
	Button *PlayAgainButton, *ExitButton;
};

