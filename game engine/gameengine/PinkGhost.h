#pragma once
#include "Ghost.h"
class PinkGhost :
	public Ghost
{
public:
	PinkGhost();
	~PinkGhost();
	virtual void Render();
	virtual void SetTarget();
};

