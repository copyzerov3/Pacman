#include "RedGhost.h"
#include "Map.h"

RedGhost::RedGhost()
{
	m_shouldUpdate = true;
}


RedGhost::~RedGhost()
{
}
void RedGhost::SetTarget()
{
	if (!Chasing)
	{
		if (Target.x == (int)(GetX() + GetWidth()/2) / 30 && Target.y == (int)(600 - GetY() - (GetHeight() /2)) / 30)
		{
			Target = ScatterTargetThree;
			return;
		}
		Target = ScatterTargetOne;
		return;
	}
	Map* map = (Map*)(GetParent());
	if (map)
	{
		int playerX = round(map->GetPlayer()->GetCenterX() / 30);
		int playerY = round((600 - map->GetPlayer()->GetCenterY()) / 30);
		Target.x = playerX;
		Target.y = playerY;
	}
	
}
void RedGhost::Render()
{
	glColor3f(1, 0, 0);
	Ghost::Render();
}