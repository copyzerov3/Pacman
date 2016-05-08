#include "GameOverScreen.h"
#include <fstream>
#include "GameScreen.h"
GameOverScreen::GameOverScreen(int ScreenWidth, int ScreenHeight, int Score, int HighScore, irrklang::ISoundEngine* EngineRef) :Screen(HighScore,EngineRef), NewScore(Score)
{
	PlayAgainButton = new Button(100, "Play");
	ExitButton = new Button(100, "Exit");
	PlayAgainButton->SetPosition((ScreenWidth + (PlayAgainButton->GetWidth() / 2)) / 2, (ScreenHeight - PlayAgainButton->GetWidth()) / 2, 0);
	ExitButton->SetPosition(PlayAgainButton->GetX(), PlayAgainButton->GetY() - (ExitButton->GetWidth()) - 10, 0);
	Graph.AddSceneNode(PlayAgainButton);
	Graph.AddSceneNode(ExitButton);
	PlayAgainButton->SetSelected(true);
}


GameOverScreen::~GameOverScreen()
{
}

bool GameOverScreen::Load(int width, int height)
{
	if (NewScore> HighScore)
	{
		std::ofstream ScoreFile("Scores.dat");
		if (ScoreFile.is_open())
		{
			ScoreFile << NewScore;
			ScoreFile.close();
		}
		else
		{
			
			printf("Failed opening file to write to\n");
			return false;
		}
	}
	return true;
}

void GameOverScreen::Update(int width, int height,int DeltaTime)
{
	Screen::Update(width, height, DeltaTime);
	for (std::vector<InputEvent>::iterator it = InputEvents.begin(); it != InputEvents.end(); ++it)
	{
		if (!it->Down)
		{
			if (it->Event == UP || it->Event == DOWN)
			{
				PlayAgainButton->SetSelected(!PlayAgainButton->IsSelected());
				ExitButton->SetSelected(!ExitButton->IsSelected());
			}
			else if (it->Event == ENTER)
			{
				if (PlayAgainButton->IsSelected())
				{
					int num = HighScore;
					if (NewScore > HighScore);
					NextScreen = new GameScreen(num,SoundEngine);
					break;
				}
				else
				{
					exit(0);
				}
			}
		}
	}
	InputEvents.clear();
}
void GameOverScreen::Draw(int width, int height)
{
	Screen::Draw(width, height);
	std::string GameOver = "Game Over";
	std::string ScoreString;

	if (NewScore > HighScore)
	{
		ScoreString = "NEW HIGH SCORE OF " + std::to_string(NewScore);
	}
	else
	{
		ScoreString = " SCORE OF " + std::to_string(NewScore);
	}

	
	glColor3f(1, 1, 0);
	glRasterPos2f((width / 2) - (ScoreString.size()*2), height - 100);
	for (int i = 0; i < GameOver.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, GameOver[i]);
	}
	glRasterPos2f((width / 2) - (ScoreString.size()*3 ), height - 150);
	for (int i = 0; i < ScoreString.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ScoreString[i]);
	}
}
