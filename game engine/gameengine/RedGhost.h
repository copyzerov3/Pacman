#pragma once
#include "Ghost.h"
class RedGhost:public Ghost
{
public:
	RedGhost();
	~RedGhost();
	virtual void Render();
	virtual void SetTarget();
};

