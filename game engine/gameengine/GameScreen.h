#pragma once
#include "Screen.h"
#include "Map.h"
class GameScreen :
	public Screen
{
public:
	GameScreen(int HighScore,irrklang::ISoundEngine* EngineRef);
	~GameScreen();

	virtual bool Load(int ScreenWidth, int ScreenHeight);
	virtual void Update(int ScreenWidth, int ScreenHeight,int DeltaTime);
	virtual void Draw(int ScreenWidth, int ScreenHeight);
	void AddTime(int value);
private:
	Map* map;
};

