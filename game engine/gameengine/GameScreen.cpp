#include "GameScreen.h"
#include"GameOverScreen.h"

GameScreen::GameScreen(int HighScore, irrklang::ISoundEngine* EngineRef) :Screen(HighScore,EngineRef)
{
}


GameScreen::~GameScreen()
{
}

bool GameScreen::Load(int width, int height)
{
	map = new Map(SoundEngine);
	if (!map->Load(width, height))
	{
		return false;
	}
	Graph.AddSceneNode(map);
	map->SetPosition(15, height,0);
	return true;
}
void GameScreen::Draw(int width, int height)
{
	Screen::Draw(width, height);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(map->GetX() + map->GetWidth() - 30, 0, 0);
	glVertex3f(width, 0, 0);
	glVertex3f(width, height, 0);
	glVertex3f(map->GetX() + map->GetWidth() - 30, height, 0);
	glEnd();

	glColor3f(0, 0, 1);


	glRasterPos2f(map->GetX() + map->GetWidth(), height - 100);
	std::string HighScoreText = "High Score : " + std::to_string(HighScore);
	for (int i = 0; i < HighScoreText.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, HighScoreText[i]);
	}
	glRasterPos2f(map->GetX() + map->GetWidth(),height - 150);
	std::string score = "Score : " + std::to_string(map->GetPlayer()->GetScore());
	for (int i = 0; i < score.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[i]);
	}
	glRasterPos2f(map->GetX() + map->GetWidth(), height - 200);
	std::string lives = "Lives : " + std::to_string(map->GetPlayer()->GetLives());

	for (int i = 0; i < lives.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, lives[i]);
	}
}
void GameScreen::Update(int width, int height, int DeltaTime)
{
	Screen::Update(width, height,DeltaTime);
	map->AddTime(DeltaTime);
	for (std::vector<InputEvent>::iterator it = InputEvents.begin(); it != InputEvents.end(); ++it)
	{
		switch (it->Event)
		{
		case DOWN:
			map->GetPlayer()->SetDown(it->Down);
			break;
		case UP:
			map->GetPlayer()->SetUp(it->Down);
			break;
		case LEFT:
			map->GetPlayer()->SetLeft(it->Down);
			break;
		case RIGHT:
			map->GetPlayer()->SetRight(it->Down);
			break;
		case ENTER:
			map->DrawScene();
		}
	}
	InputEvents.clear();
	if (map->GetPlayer()->GetLives() == -1)
	{
		NextScreen = new GameOverScreen(width,height,map->GetPlayer()->GetScore(),HighScore,SoundEngine);
	}
}