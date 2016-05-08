#pragma once
#include "GameObjectNode.h"
#include <glut.h>
#include <GL.H>
class Sphere :public GameObjectNode
{
public:
	Sphere(GLdouble Radius,std::string name = "Sphere", std::string message = "This is a Sphere Scene Node");
	~Sphere();

	virtual void Render();
	virtual void Update();
	GLdouble GetRadius(){ return m_radius; }
	float GetWidth(){ return 30; }
	virtual float GetX(){ return GameObjectNode::GetX() - m_radius; }
	virtual float GetY(){ return GameObjectNode::GetY() - m_radius; }
	float GetCenterX(){ return GameObjectNode::GetX(); }
	float GetCenterY(){ return GameObjectNode::GetY(); }
protected:
	GLint Slices,Stacks;
private:
	GLdouble m_radius;
};

