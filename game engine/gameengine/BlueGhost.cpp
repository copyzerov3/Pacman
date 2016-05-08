#include "BlueGhost.h"
#include "Map.h"

BlueGhost::BlueGhost()
{
}


BlueGhost::~BlueGhost()
{
}
void BlueGhost::Render()
{
	glColor3f(0, 1, 1);
	Ghost::Render();
}
void BlueGhost::SetTarget()
{

	if (!Chasing)
	{
		if (Target.x == (int)(GetX() + GetWidth() / 2) / 30 && Target.y == (int)(600 - GetY() - (GetHeight() / 2)) / 30)
		{
			Target = ScatterTargetOne;
			return;
		}
		Target = ScatterTargetThree;
		return;
	}
	//printf("Getting Target\n");
	Map* map = (Map*)GetParent();
	if (map)
	{
		int playerX = round(map->GetPlayer()->GetCenterX() / 30);
		int playerY = round((600 - map->GetPlayer()->GetCenterY()) / 30);
		
		int RedGhostX = round(map->GetRedGhost()->GetX() / 30);
		int RedGhostY = round((600 - map->GetRedGhost()->GetY()) / 30);
		int  i = 0;
		int j = 0;
		if (RedGhostX < playerX)
		{
			i = 18;
		}
		else
		{
			i = 1;
		}
		do
		{
			
			Target.x = i;
			if (RedGhostY < playerY)
			{
				Target.y = playerY - 1 + j;
			}
			else if (RedGhostY < playerY)
			{
				Target.y = playerY + 1 +j;
			}
			else
			{
				Target.y = playerY + j;
			}
			if (map->GetNodeMap()->GetNode(Target.x, Target.y).x != -1)
			{
				return;
			}
			if (RedGhostX < playerX)
			{
				i--;
			}
			else
			{
				i++;
			}
			if (i == 0 || i == 20)
			{
				if (RedGhostY < playerY)
				{
					j--;
				}
				else if (RedGhostY > playerY)
				{
					j++;
				}
				else
				{
					Target = ScatterTargetThree;
					return;
				}
			}
		} while (true);
	}
		
}