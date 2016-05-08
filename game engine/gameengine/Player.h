#pragma once

#include "Sphere.h"

class Player :public Sphere
{
public:
	Player();
	~Player();
	virtual void Render();
	virtual void Update();
	
	void SetLeft(bool value){ LEFT = value; }
	void SetRight(bool value){ RIGHT = value; }
	void SetUp(bool value){ UP = value; }
	int GetScore(){ return Score; }
	void SetDown(bool value){ DOWN = value; }
	bool IsPointWithin(int x, int y);
	//Returns the last direction that resolved successfully 0 is UP 1 is Right, 2 is Down and 3 is left
	int GetLastMove(){ return LastMove; }
	int GetLives(){ return lives; }
	void AddToScore(int value){ Score += value; }
	void LooseLife(){ lives--; }
private:
	bool LEFT, RIGHT, UP, DOWN;
	float MoveSpeed;
	int Score;
	int lives;
	//the last direction that resolved successfully 0 is UP 1 is Right, 2 is Down and 3 is left
	int LastMove;
};