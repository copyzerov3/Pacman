#pragma once
#include "Ghost.h"
class BlueGhost :
	public Ghost
{
public:
	BlueGhost();
	~BlueGhost();
	virtual void Render();
	virtual void SetTarget();
};

