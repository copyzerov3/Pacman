#include "OrangeGhost.h"
#include "Map.h"

OrangeGhost::OrangeGhost()
{
	m_shouldUpdate = false;
}


OrangeGhost::~OrangeGhost()
{
}

void OrangeGhost::Render()
{
	glColor3f(1, .5, 0);
	Ghost::Render();
}

void OrangeGhost::SetTarget()
{

	if (!Chasing)
	{
		if (Target.x == (int)(GetX() + GetWidth() / 2) / 30 && Target.y == (int)(600 - GetY() - (GetHeight() / 2)) / 30)
		{
			Target = ScatterTargetTwo;
			return;
		}
		Target = ScatterTargetFour;
		return;
	}
	//printf("Getting Target\n");
	Map* map = (Map*)GetParent();

	if (map)
	{
		int playerX = round(map->GetPlayer()->GetCenterX() / 30);
		int playerY = round((600 - map->GetPlayer()->GetCenterY()) / 30);
		int diffX = abs(playerX - (GetX() / 30));
		int diffY = abs(playerY - ((600 - GetY()) / 30));
		if ( diffX + diffY >= 8)
		{
			float num = ChaseTime/20000;
			if (num < 0.25)
			{
				Target = ScatterTargetOne;
			}
			else if (num < 0.5)
			{
				Target = ScatterTargetTwo;
			}
			else if (num < 0.75)
			{
				Target = ScatterTargetThree;
			}
			else
			{
				Target = ScatterTargetFour;
			}
		}
		else
		{
			Target.x = playerX;
			Target.y = playerY;
		}
	}
}