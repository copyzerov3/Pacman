#pragma once
#include <list>
#include "Ghost.h"
class GhostNodeMap
{
	public:
	struct GhostNode
	{
		int x, y;
		std::list<GhostNode*> Connections;
		GhostNode* Parent = nullptr;
		int H;
		int G = 1;
	};

	GhostNodeMap();
	~GhostNodeMap();
	
	std::list<Ghost::Point> GetPath(GhostNode Start, GhostNode End);
	void AddNode(GhostNode* Node);
	void ConnectNodes(int MaxX, int MaxY);
	GhostNode GetNode(int x, int y);
private:
	std::list<GhostNode*> Nodes;
};

