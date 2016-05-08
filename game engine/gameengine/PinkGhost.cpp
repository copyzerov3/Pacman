#include "PinkGhost.h"
#include "Map.h"

PinkGhost::PinkGhost()
{
	m_shouldUpdate = true;
}


PinkGhost::~PinkGhost()
{
}

void PinkGhost::Render()
{
	glColor3f(1, 0.6, 0.6);
	Ghost::Render();
}
void PinkGhost::SetTarget()
{
	if (!Chasing)
	{
		if (Target.x == (int)(GetX() + GetWidth() / 2) / 30 && Target.y == (int)(600 - GetY() - (GetHeight() / 2)) / 30)
		{
			Target = ScatterTargetFour;
			return;
		}
		Target = ScatterTargetTwo;
		return;
	}
	Map* map = (Map*)GetParent();
	if (map)
	{
		int playerX = round(map->GetPlayer()->GetCenterX() / 30);
		int playerY = round((600 - map->GetPlayer()->GetCenterY()) / 30);
		switch (map->GetPlayer()->GetLastMove())
		{
		case 0:
			playerY += 2;
			break;
		case 1:
			playerX += 2;
			break;
		case 2:
			playerY -= 2;
			break;
		case 3:
			playerX -= 2;
			break;
		}
		if (map->GetNodeMap()->GetNode(Target.x, Target.y).x == -1)
		{
			playerX = round(map->GetPlayer()->GetCenterX() / 30);
			playerY = round((600 - map->GetPlayer()->GetCenterY()) / 30);
		}
		else if (map->GetNodeMap()->GetNode(Target.x, Target.y).y == -1)
		{
			playerX = round(map->GetPlayer()->GetCenterX() / 30);
			playerY = round((600 - map->GetPlayer()->GetCenterY()) / 30);
		}

		Target.x = playerX;
		Target.y = playerY;
	}
	
}