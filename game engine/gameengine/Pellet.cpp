#include "Pellet.h"


Pellet::Pellet(GLdouble radius) :Sphere(radius, "Pellet"), Score(100)
{
	m_shouldUpdate = false;

}


Pellet::~Pellet()
{
	
}

void Pellet::Render()
{
	glPushMatrix();
	glColor3f(1, 1, 0);
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2f(GetX()+3, GetY()+3);
	glEnd();
	glPopMatrix();
}
