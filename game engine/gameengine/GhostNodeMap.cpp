#include "GhostNodeMap.h"


GhostNodeMap::GhostNodeMap()
{
}


GhostNodeMap::~GhostNodeMap()
{
	for (std::list<GhostNode*>::iterator it = Nodes.begin(); it != Nodes.end(); ++it)
	{
		delete (*it);
	}
	Nodes.empty();
}
void GhostNodeMap::AddNode(GhostNode* Node)
{
	Nodes.push_back(Node);
}
void GhostNodeMap::ConnectNodes(int MaxX, int MaxY)
{
	for (std::list<GhostNode*>::iterator it = Nodes.begin(); it != Nodes.end(); ++it)
	{
		
		for (std::list<GhostNode*>::iterator i = Nodes.begin(); i != Nodes.end(); ++i)
		{
			
			if (((*i)->x - 1 == (*it)->x || (*i)->x + 1 == (*it)->x) && (*i)->y == (*it)->y)
			{
				(*it)->Connections.push_back((*i));
			}
			if ((((*i)->y + 1 == (*it)->y) || ((*i)->y - 1 == (*it)->y)) && (*i)->x == (*it)->x)
			{
				(*it)->Connections.push_back((*i));
			}
			if ((*it)->Connections.size() == 4)
			{
				break;
			}
		}
		/*printf("Node at Position X %d Y %d \nConnected to...\n", (*it)->x, (*it)->y);
		for (std::list<GhostNode*>::iterator i = (*it)->Connections.begin(); i != (*it)->Connections.end(); ++i)
		{
			printf("Node at Position X %d, Y %d\n", (*i)->x, (*i)->y);
		}
		printf("\n\n");*/
	}
}


GhostNodeMap::GhostNode GhostNodeMap::GetNode(int y, int x)
{
	for (std::list<GhostNode*>::iterator it = Nodes.begin(); it != Nodes.end(); ++it)
	{
		//printf("Node X : %d  Node Y : %d\n\n", (*it)->x, (*it)->y);
		if ((*it)->x == x && (*it)->y == y)
		{
			return *(*it);
		}
	}
	GhostNode node;
	node.x = -1;
	node.y = -1;
	return node;
}
std::list<Ghost::Point> GhostNodeMap::GetPath(GhostNode Start,GhostNode End)
{
	std::list<Ghost::Point> path;
	if (End.x == -1 || End.y == -1)
	{
		return path;
	}
	if (Start.x == -1 || End.y == -1)
	{
		return path;
	}
	bool found = false;
	std::list<GhostNode*> OpenList;
	std::list<GhostNode*> ClosedList;
	Start.Parent = nullptr;
	End.Parent = nullptr;
	OpenList.push_back(&Start);
	GhostNode* CurrentNode = &Start;
	CurrentNode->G = 10;
	CurrentNode->H = 0;
	bool Closed = false;

	
	
	for (std::list<GhostNode*>::iterator it = Nodes.begin(); it != Nodes.end(); ++it)
	{
		(*it)->Parent = nullptr;
	}
	
	
	
	do
	{
		OpenList.remove(CurrentNode);
		ClosedList.push_back(CurrentNode);
		
		for (std::list<GhostNode*>::iterator it = CurrentNode->Connections.begin(); it != CurrentNode->Connections.end(); ++it)
		{
			Closed = false;
			for (std::list<GhostNode*>::iterator i = ClosedList.begin(); i != ClosedList.end(); ++i)
			{
				if (*it == *i)
				{
					Closed = true;
				}
			}
			if (!Closed)
			{
				(*it)->Parent = CurrentNode;
				(*it)->G = CurrentNode->G + 10;
				(*it)->H = abs((*it)->x - End.x) + abs((*it)->y - End.y);
				OpenList.push_back(*it);
			}
		}
		if (OpenList.size() != 0)
			CurrentNode = *OpenList.begin();
		for (std::list<GhostNode*>::iterator it = OpenList.begin(); it != OpenList.end(); ++it)
		{
			int CurrentNodeF = CurrentNode->G + CurrentNode->H;
			int NodeF = (*it)->G + CurrentNode->H;

			if (CurrentNodeF > NodeF)
			{
				CurrentNode = *it;
			}
		}
		if (CurrentNode->H == 0)
		{
			found = true;
		}
	} while (!found);
	//printf("Path\n\n");
	do
	{
		Ghost::Point point;
		point.x = CurrentNode->x;
		point.y = CurrentNode->y;

		path.push_front(point);
		//printf("Node X : %d, Node Y : %d\n\n", point.x, point.y); 
		if (CurrentNode->Parent != nullptr)
		{
			CurrentNode = CurrentNode->Parent;
		}
		else
		{
			path.pop_front();
			for (std::list<Ghost::Point>::iterator it = path.begin(); it != path.end(); ++it)
			{
				//printf("Node X : %d, Node Y : %d\n\n", it->x, it->y);
			}
			return path;
		}
	} while (true);
	return path;
}