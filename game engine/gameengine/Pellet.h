#pragma once
#include "Sphere.h"
class Pellet :
	public Sphere
{
public:
	Pellet(GLdouble radius = 5);
	~Pellet();
	int GetScore(){ return Score; }
	virtual void Render();
protected:
	int Score;
};

