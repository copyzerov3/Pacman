#include "Player.h"
#include "Map.h"

Player::Player() :Sphere(10), UP(false), DOWN(false), LEFT(false), RIGHT(false), MoveSpeed(.5), Score(0), lives(3), LastMove(-1)
{
}


Player::~Player()
{
}

void Player::Render()
{
	glPushMatrix();
	glColor3f(1, 1, 0);
	Sphere::Render();
	glPopMatrix();

	/*glLineWidth(2);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(GetX(),GetY(),0);
	glVertex3f(GetX() + GetWidth(), GetY(), 0);
	glEnd();
	glColor3f(0, 1.0,0);
	glBegin(GL_LINES);
	glVertex3f(GetX(), GetY(), 0);
	glVertex3f(GetX(), GetY() + GetWidth(), 0);
	glEnd();*/
}
void Player::Update()
{
	Sphere::Update();

	Map* map = (Map*)GetParent();
	if (map)
	{	
		int x,y; 
		if (DOWN)
		{
			x = round(GetCenterX() / GetWidth());
			y = (round((map->GetScreenHeight() - GetCenterY()) / GetWidth())) + 1;
			if ((x == 9) && (y == 8))
			{
				
			}
			else
			{
				if (!map->IsBoundary(x, y) || !map->GetBoundary(x, y)->Contains(this))
				{
					Score += map->CheckPlayerEatPellet();
					m_transformation[1][3] -= MoveSpeed;
					LastMove = 2;
				}
			}
		}
		if (UP)
		{
			x = round(GetCenterX() / GetWidth());
			y = round((map->GetScreenHeight() - GetCenterY()) / GetWidth()) - 1;
			if (!map->IsBoundary(x, y) || !map->GetBoundary(x, y)->Contains(this))
			{
				Score += map->CheckPlayerEatPellet();
				m_transformation[1][3] += MoveSpeed;
				LastMove = 0;
			}
		}
		if (LEFT)
		{
			x = round(GetCenterX() / GetWidth()) - 1;
			y = round((map->GetScreenHeight() - GetCenterY()) / GetWidth());
			if (!map->IsBoundary(x, y) || !map->GetBoundary(x, y)->Contains(this))
			{
				Score += map->CheckPlayerEatPellet();
				m_transformation[0][3] -= MoveSpeed;
				LastMove = 3;
				if (m_transformation[0][3] <=0)
				{
					
					m_transformation[0][3] = map->GetWidth();
					LastMove = 1;
				}
			}
		}
		if (RIGHT)
		{
			x = round(GetCenterX() / GetWidth()) + 1;
			y = round((map->GetScreenHeight() - GetCenterY()) / GetWidth());
			if (!map->IsBoundary(x, y) || !map->GetBoundary(x, y)->Contains(this))
			{
				Score += map->CheckPlayerEatPellet();
				m_transformation[0][3] += MoveSpeed;
				LastMove = 2;
				if (m_transformation[0][3] > map->GetWidth() - GetRadius())
				{
					
					m_transformation[0][3] = 0;
					LastMove = 3;
				}
			}
			
		}
	}
	
	
}
bool Player::IsPointWithin(int x, int y)
{
	return (x > (GetX()) && GetX() + GetWidth()  > x) && (y > GetY()  && GetY() + GetWidth() > y);
}