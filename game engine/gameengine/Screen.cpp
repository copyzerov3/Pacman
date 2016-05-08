#include "Screen.h"


Screen::Screen(int HighScore, irrklang::ISoundEngine* EngineRef) :HighScore(HighScore), SoundEngine(EngineRef)
{
}


Screen::~Screen()
{
}
void Screen::Draw(int width, int height)
{
	Graph.Traverse();
}

void Screen::Update(int width, int height,int DeltaTime)
{
	Graph.Update();
}
bool Screen::Load(int width, int height)
{
	return true;
}