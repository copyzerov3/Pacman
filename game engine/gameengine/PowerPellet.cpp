#include "PowerPellet.h"


PowerPellet::PowerPellet() :Pellet(5)
{
	Score *= 2;
}


PowerPellet::~PowerPellet()
{
}
void PowerPellet::Render()
{
	glPushMatrix();
	glColor3f(1, 1, 0);
	glPointSize(12);
	glBegin(GL_POINTS);
	glVertex2f(GetX() + 3, GetY()+ 3 );
	glEnd();
	glPopMatrix();
}
