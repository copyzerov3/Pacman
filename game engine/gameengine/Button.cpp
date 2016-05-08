#include "Button.h"
#include <glut.h>

Button::Button(GLdouble Width, std::string TextOnButton, std::string name, std::string message) :Cube(Width, name, message), TextOnButton(TextOnButton), Selected(false)
{
}


Button::~Button()
{
}

void Button::Render()
{
	glPushMatrix();
	if (Selected)
	{
		glColor3f(0.46, 0.53, 0.6);
	}
	else
	{
		glColor3f(1, 1, 1);
	}
	Cube::Render();
	glPopMatrix();
	glColor3f(0, 0, 0 );
	glRasterPos2f(GetX()- (GetWidth()/8), GetY());

	for (int i = 0; i < TextOnButton.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, TextOnButton[i]);
	}
}
void Button::Update()
{

}
