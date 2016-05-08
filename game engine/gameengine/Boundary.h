#pragma once
#include "Cube.h"
#include "Sphere.h"
class Boundary :
	public Cube
{
public:
	Boundary(GLfloat width);
	~Boundary();

	virtual void Render();
	bool Contains(Sphere* Node);

	virtual float GetX(){ return GameObjectNode::GetX() - (GetWidth()/2); }
	virtual float GetY(){ return GameObjectNode::GetY() - (GetWidth()/2); }
};

