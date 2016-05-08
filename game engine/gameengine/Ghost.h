#pragma once
#include "GameObjectNode.h"
#include "Player.h"
#include <list>
class Ghost :public GameObjectNode
{public:

	struct Point
	{
		int x = 0;
		int y = 0;
	};
	Ghost();
	~Ghost();
	virtual void Render();
	virtual void Update();
	virtual void SetTarget() = 0;
	bool Contains(Player* player);
	float GetWidth(){ return m_width; }
	float GetHeight(){ return m_height; }
	void GetPath();
	void StartMoving() {m_shouldUpdate = true;}
	void StopMoving(){ m_shouldUpdate = false; }
	bool IsMoving(){ return m_shouldUpdate; }
	void UpdateTime(int value){ if (!m_shouldUpdate)return; if (Chasing)ChaseTime += value; else{ ScatterTime += value; } }
	void PlayerAtePellet();
protected:
	Point Target;
	Point ScatterTargetOne;
	Point ScatterTargetTwo;
	Point ScatterTargetThree;
	Point ScatterTargetFour;
	float Speed;

	bool Chasing;
	bool Frightened;
	int ChaseTime;
	int ScatterTime;
private:
	float m_width,m_height;
	std::list<Point> Path;
	int NodesTravelled;
	

};

