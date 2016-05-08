#include "Boundary.h"


Boundary::Boundary(GLfloat width) :Cube(width, "Boundary", "Boundary in pacman")
{
}


Boundary::~Boundary()
{
}

void Boundary::Render()
{
	glPushMatrix();
	glColor3f(0, 0, 1);
	Cube::Render();
	glPopMatrix();

	/*glLineWidth(2);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(GetX(), GetY(), 0);
	glVertex3f(GetX() + GetWidth(), GetY(), 0);
	glEnd();
	glColor3f(0, 1.0, 0);
	glBegin(GL_LINES);
	glVertex3f(GetX(), GetY(), 0);
	glVertex3f(GetX(), GetY() + GetWidth(), 0);
	glEnd();*/
}

bool Boundary::Contains(Sphere* sphere)
{
	if ((GetX() + GetWidth()) >= sphere->GetX() && GetX() <= (sphere->GetX() + sphere->GetWidth()))
	{
		if ((GetY() + GetWidth()) >= sphere->GetY() && GetY() <= (sphere->GetY() + sphere->GetWidth()))
		{
			return true;
		}
	}
	//printf("Passing Variables Box X: %f\nBox Y: %f\nBox Width %f\nSphere X %d\n Sphere Y%d\nSphere Width %f\n", GetX(), GetY(), GetWidth(), sphere->GetX(), sphere->GetY(), sphere->GetWidth());
	
	return false;
}
