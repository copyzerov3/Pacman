#pragma once
#include "GameObjectNode.h"
#include "Boundary.h"
#include "GhostNodeMap.h"
#include "Player.h"
#include "Pellet.h"
#include "RedGhost.h"
#include "BlueGhost.h"
#include "OrangeGhost.h"
#include "PinkGhost.h"
#include <irrKlang.h>
#define ROWS 21
#define COLUMNS 19
class Map :public GameObjectNode
{
public:
	Map(irrklang::ISoundEngine* Engine);
	~Map();
	bool Load(int ScreenWidth, int ScreenHeight);
	Player* GetPlayer() { return player; }
	bool IsBoundary(int x, int y)
	{
		return NumberMap[y][x] == 1 ? true : false;
	}
	float GetWidth(){ return COLUMNS * 30; }
	Boundary* GetBoundary(int x, int y)
	{
		return BoundaryMap[y][x];
	}
	void DrawScene();
	int GetScreenHeight(){ return height; }

	int CheckPlayerEatPellet();
	GhostNodeMap* GetNodeMap(){ return NodeMap; }
	void SetBoard();
	void ResetActors();
	RedGhost* GetRedGhost(){ return redGhost; }
	virtual void Update();

	void AddTime(int value);
	

	irrklang::ISoundEngine* GetSoundEngine(){ return EngineRef; }
private:


	int NumberMap[ROWS][COLUMNS];
	int height;
	Boundary* BoundaryMap[ROWS][COLUMNS];
	Player* player;
	GhostNodeMap* NodeMap;
	std::list<Pellet*> pellets;
	RedGhost* redGhost;
	BlueGhost* blueGhost;
	OrangeGhost* orangeGhost;
	PinkGhost* pinkGhost;
	irrklang::ISoundEngine* EngineRef;

	int MaxPellets;
	int EatenPellets;

};

