#pragma once
#include "Ghost.h"
class OrangeGhost :
	public Ghost
{
public:
	OrangeGhost();
	~OrangeGhost();
	virtual void Render();
	virtual void SetTarget();
};

