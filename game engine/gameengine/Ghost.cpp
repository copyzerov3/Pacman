#include "Ghost.h"
#include "Map.h"

Ghost::Ghost() :GameObjectNode("Ghost"), m_width(30), m_height(30), Speed(0.5), NodesTravelled(0), Chasing(true), Frightened(false), ChaseTime(10000), ScatterTime(0)
{
	m_shouldUpdate = false;
	ScatterTargetFour.x = 1;
	ScatterTargetFour.y = 19;
	ScatterTargetThree.x = 17;
	ScatterTargetThree.y = 19;
	ScatterTargetOne.x = 1;
	ScatterTargetOne.y = 1;
	ScatterTargetTwo.x = 17;
	ScatterTargetTwo.y = 1;

}


Ghost::~Ghost()
{
}
void Ghost::PlayerAtePellet()
{
	if (!m_shouldUpdate)
		return;
	Chasing = false;
	Frightened = true;
	ChaseTime = 0;
	NodesTravelled = 0;
	ScatterTime = 4000;
	GetPath();
}
bool Ghost::Contains(Player* player)
{
	if ((GetX() + GetWidth()) >= player->GetX() && GetX() <= (player->GetX() + player->GetWidth()))
	{
		if ((GetY() + GetWidth()) >= player->GetY() && GetY() <= (player->GetY() + player->GetWidth()))
		{
			return true;
		}
	}
	return false;
}

void Ghost::Render()
{
	if (Frightened)
	{
		glColor3f(1, 1, 1);
	}
	glBegin(GL_POLYGON);
	glVertex3f(GetX(), GetY(), 0);
	glVertex3f(GetX() + GetWidth(), GetY(), 0);
	glVertex3f(GetX() + GetWidth(), GetY() + GetHeight(), 0);
	glVertex3f(GetX(), GetY() + GetHeight() , 0);
	glEnd();
}
void Ghost::GetPath()
{
	Map* map = (Map*)GetParent();
	if (map)
	{
		int x = round(GetX() / 30);
		int y = round((600 - GetY() - (GetHeight()/2)) / 30);
		SetTarget();
		NodesTravelled = 0;
		if (Target.y != -1)
			Path = map->GetNodeMap()->GetPath(map->GetNodeMap()->GetNode(x,y),map->GetNodeMap()->GetNode(Target.x,Target.y));
	}
}
void Ghost::Update()
{
	if (!m_shouldUpdate)
		return;

	if (Chasing && ChaseTime > 20000)
	{
		//printf("Stopping CHase\n");
		Frightened = false;
		Chasing = false;
		GetPath();
		NodesTravelled = 0;
		ChaseTime = 0;
	}
	else if (!Chasing && ScatterTime> 7000)
	{
		//printf("Starting Chase\n");
		Frightened = false;
		Chasing = true;
		GetPath();
		NodesTravelled = 0;
		ScatterTime = 0;
	}
	Map* map = (Map*)GetParent();
	if (map)
	{
		if (Contains(map->GetPlayer()))
		{
			if (!Frightened)
			{
				map->GetPlayer()->LooseLife();
				map->ResetActors();
			}
			else
			{
				SetPosition(30 * 9 - (GetWidth() / 2), 600 - 30 * 9 - (GetHeight() / 2), 0);
				map->GetPlayer()->AddToScore(500);
				Frightened = false;
				GetPath();
				map->GetSoundEngine()->play2D("pacman_eatghost.wav");
				
			}
			
		}
	}
	if (Path.empty() || NodesTravelled == 2)
	{
		if (Chasing)
		{
			GetPath();
		}
		else
		{
			NodesTravelled = 0;
			if (Path.empty())
			{
				GetPath();
			}
		}
		
		

	}
	else
	{
		Point point = (*Path.begin());
		
		int x = GetX() + (GetWidth() /2);
		int y = 600-GetY() - (GetHeight()/2);
		if (x == point.y* 30 && y == point.x* 30)//this fires because of stupid int
		{
			Path.pop_front();
			NodesTravelled++;
			return;
		}
		if (point.y* 30 > x)
		{
			SetX(GetX() + Speed);
		}
		else if (point.y*30 < x)
		{
			SetX(GetX() - Speed);
		}
		else if (point.x*30 < y)
		{
			SetY(GetY() + Speed);
		}
		else if (point.x*30 > y)
		{
			SetY(GetY() - Speed);
		}
	}
}