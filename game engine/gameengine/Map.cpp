#include "Map.h"
#include <fstream>
#include <string>
#include"PowerPellet.h"
Map::Map(irrklang::ISoundEngine* Engine) :GameObjectNode("Map", "The Map"), height(0), MaxPellets(0), EatenPellets(0), EngineRef(Engine)
{
	player = new Player();
	NodeMap = new GhostNodeMap();
	m_ignoreChildUpdate = true;
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLUMNS; ++j)
		{
			BoundaryMap[i][j] = nullptr;
		}
	}
}


Map::~Map()
{
	delete NodeMap;
	NodeMap = nullptr;
}
void Map::ResetActors()
{
	EngineRef->play2D("pacman_death.wav");
	player->SetPosition(30 * 9, height - 30 * 11, 0);
	redGhost->SetPosition(30 * 9 - (redGhost->GetWidth() / 2), height - 30 * 7 - (redGhost->GetHeight() / 2), 0);
	pinkGhost->SetPosition(30 * 9 - (redGhost->GetWidth() / 2), height - 30 * 9 - (redGhost->GetHeight() / 2), 0);
	blueGhost->SetPosition(30 * 8 - (redGhost->GetWidth() / 2), height - 30 * 9 - (redGhost->GetHeight() / 2), 0);
	orangeGhost->SetPosition(30 * 10 - (redGhost->GetWidth() / 2), height - 30 * 9 - (redGhost->GetHeight() / 2), 0);
	redGhost->GetPath();
	pinkGhost->GetPath();
	blueGhost->GetPath();
	orangeGhost->GetPath();
}
bool Map::Load(int width, int height)
{
	this->height = height;
	std::ifstream file;
	file.open("Map.txt");
	if (file.is_open())
	{
		std::string line;
		int i = 0;
		int lineCounter = 0;
		while (std::getline(file, line))
		{
			/*printf(line.c_str());
			printf("\n");*/
			for (i = 0; i < line.length(); ++i)
			{
				NumberMap[lineCounter][i] = (int)line[i] - 48;
			}
			lineCounter++;
			
		}
		file.close();
		for (i = 0; i < ROWS; ++i)
		{
			for (int j = 0; j < COLUMNS; ++j)
			{
				if (NumberMap[i][j] == 1)
				{
					Boundary* cube = new Boundary(30);
					BoundaryMap[i][j] = cube;
					cube->SetPosition(j * 30,height - (i * 30), 0);
					AddChild(cube);
					printf("1");
				}
				else
				{

					GhostNodeMap::GhostNode* Node = new GhostNodeMap::GhostNode();

					Node->x = i;
					Node->y = j;
					NodeMap->AddNode(Node);

					printf("0");
					if ((i == 9) && ((j == 8) || (j == 9) || (j == 10)))
					{
						continue;
					}
					if ((i == 8) && (j == 9))
						continue;
					if (j == 1 && i == 2)
					{
						PowerPellet* pellet = new PowerPellet();
						pellet->SetPosition(j * 30, height - (i * 30), 0);
						AddChild(pellet);
						pellets.push_back(pellet);
						MaxPellets++;
						continue;
					}
					if (j == 17 && i == 2)
					{
						PowerPellet* pellet = new PowerPellet();
						pellet->SetPosition(j * 30, height - (i * 30), 0);
						AddChild(pellet);
						pellets.push_back(pellet);
						MaxPellets++;
						continue;
					}
					if (j == 1 && i == 15)
					{
						PowerPellet* pellet = new PowerPellet();
						pellet->SetPosition(j * 30, height - (i * 30), 0);
						AddChild(pellet);
						pellets.push_back(pellet);
						MaxPellets++;
						continue;
					}
					if (i == 15 && j == 17)
					{
						PowerPellet* pellet = new PowerPellet();
						pellet->SetPosition(j * 30, height - (i * 30), 0);
						AddChild(pellet);
						pellets.push_back(pellet);
						MaxPellets++;
						continue;
					}
					Pellet* pellet = new Pellet();
					pellet->SetPosition(j * 30, height - (i * 30), 0);
					AddChild(pellet);
					pellets.push_back(pellet);
					MaxPellets++;
				}
			}
			printf("\n");
		}

	}
	else
	{
		printf("Unable to open file");
		return false;
	}



	NodeMap->ConnectNodes(ROWS,COLUMNS);
	AddChild(player);
	player->SetPosition(30 * 9, height - 30 * 11, 0);
	redGhost = new RedGhost();
	redGhost->SetPosition(30 * 9 - (redGhost->GetWidth() / 2), height - 30 * 7 - (redGhost->GetHeight() /2 ), 0);
	pinkGhost = new PinkGhost();
	pinkGhost->SetPosition(30 * 9 - (redGhost->GetWidth() / 2), height - 30 * 9 - (redGhost->GetHeight() / 2), 0);
	blueGhost = new BlueGhost();
	blueGhost->SetPosition(30 * 8 - (redGhost->GetWidth() / 2), height - 30 * 9 - (redGhost->GetHeight() / 2), 0);
	orangeGhost = new OrangeGhost();
	orangeGhost->SetPosition(30 * 10 - (redGhost->GetWidth() / 2), height - 30 * 9 - (redGhost->GetHeight() / 2), 0);
	AddChild(redGhost);
	AddChild(pinkGhost);
	AddChild(blueGhost);
	AddChild(orangeGhost);
	return true;
}
void Map::SetBoard()
{
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLUMNS; ++j)
		{
			if (NumberMap[i][j] == 0)
			{
				if ((i == 9) && ((j == 8) || (j == 9) || (j == 10)))
				{
					continue;
				}
				if ((i == 8) && (j == 9))
					continue;
				Pellet* pellet = new Pellet();
				pellet->SetPosition(j * 30, height - (i * 30), 0);
				AddChild(pellet);
				pellets.push_back(pellet);
			}
		}
		printf("\n");
	}
	player->SetPosition(30 * 9, height - 30 * 11, 0);
	redGhost->SetPosition(30 * 9 - (redGhost->GetWidth() / 2), height - 30 * 7 - (redGhost->GetHeight() / 2), 0);
	pinkGhost->SetPosition(30 * 9 - (redGhost->GetWidth() / 2), height - 30 * 9 - (redGhost->GetHeight() / 2), 0);
	blueGhost->SetPosition(30 * 8 - (redGhost->GetWidth() / 2), height - 30 * 9 - (redGhost->GetHeight() / 2), 0);
	orangeGhost->SetPosition(30 * 10 - (redGhost->GetWidth() / 2), height - 30 * 9 - (redGhost->GetHeight() / 2), 0);
	redGhost->GetPath();
	pinkGhost->GetPath();
	blueGhost->GetPath();
}
void Map::DrawScene()
{
	/*for (int i = 0; i < ROWS; ++i)
	{
		printf("%d ", i);
		for (int j = 0; j < COLUMNS; ++j)
		{
			if (round(player->GetCenterX() / player->GetWidth()) == j &&  round(((height -player->GetCenterY()) / player->GetWidth())) == i)
			{
				printf("p");
			}
			else
			{
				printf("%d", NumberMap[i][j]);
			}
		}
		printf("\n");
	}*/
	
}
void Map::Update()
{
	GameObjectNode::Update();
	player->Update();
	redGhost->Update();
	pinkGhost->Update();
	blueGhost->Update();
	orangeGhost->Update();
	if (pellets.size() == 0)
	{
		SetBoard();
	}
	if (EatenPellets == 30 && !blueGhost->IsMoving())
	{
		blueGhost->StartMoving();
		blueGhost->GetPath();
	}
	if ((MaxPellets / 3) * 2 <= EatenPellets && !orangeGhost->IsMoving())
	{
		orangeGhost->StartMoving();
		orangeGhost->GetPath();
	}
}
void Map::AddTime(int value)
{
	redGhost->UpdateTime(value);
	pinkGhost->UpdateTime(value);
	orangeGhost->UpdateTime(value);
	blueGhost->UpdateTime(value);
}
int Map::CheckPlayerEatPellet()
{
	for (std::list<Pellet*>::iterator it = pellets.begin(); it != pellets.end(); ++it)
	{
		if (player->IsPointWithin((*it)->GetCenterX(), (*it)->GetCenterY()))
		{
			int Score = (*it)->GetScore();
			if (Score >100)
			{

				redGhost->PlayerAtePellet();
				blueGhost->PlayerAtePellet(); 
				pinkGhost->PlayerAtePellet();
				orangeGhost->PlayerAtePellet();
			}
			Pellet* temp = *it;
			RemoveChild(*it);
			pellets.remove((*it));
			delete temp;
			EatenPellets++;
			if (!EngineRef->isCurrentlyPlaying("pacman_chomp.wav"))
				EngineRef->play2D("pacman_chomp.wav");
			return Score;
		}
	}
	return 0;
}
