#include "MainMenuScreen.h"
#include "GameScreen.h"

MainMenuScreen::MainMenuScreen(int ScreenWidth, int ScreenHeight, int HighScore, irrklang::ISoundEngine* EngineRef) :Screen(HighScore,EngineRef)
{
	PlayButton = new Button(100, "Play");
	ExitButton = new Button(100, "Exit");
	PlayButton->SetPosition((ScreenWidth + (PlayButton->GetWidth()/2))/2, (ScreenHeight - PlayButton->GetWidth())/2, 0);
	ExitButton->SetPosition(PlayButton->GetX(), PlayButton->GetY() - (ExitButton->GetWidth()) - 10, 0);
	Graph.AddSceneNode(PlayButton);
	Graph.AddSceneNode(ExitButton);
	PlayButton->SetSelected(true);
}


MainMenuScreen::~MainMenuScreen()
{
}

void MainMenuScreen::Update(int ScreenWidth, int ScreenHeight,int DeltaTime)
{
	Screen::Update(ScreenWidth, ScreenHeight,DeltaTime);
	for (std::vector<InputEvent>::iterator it = InputEvents.begin(); it != InputEvents.end(); ++it)
	{
		if (!it->Down)
		{
			if (it->Event == UP || it->Event == DOWN)
			{
				PlayButton->SetSelected(!PlayButton->IsSelected());
				ExitButton->SetSelected(!ExitButton->IsSelected());
			}
			else if (it->Event == ENTER)
			{
				if (PlayButton->IsSelected())
				{
					SoundEngine->play2D("pacman_beginning.wav");
					NextScreen = new GameScreen(HighScore,SoundEngine);
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

void MainMenuScreen::Draw(int ScreenWidth, int ScreenHeight)
{
	Screen::Draw(ScreenWidth, ScreenHeight);
	glColor3f(1, 1, 0);
	std::string Title = "PAC-MAN";
	glRasterPos2f(ScreenWidth / 2 - 48, ScreenHeight - 100);
	

	for (int i = 0; i < Title.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Title[i]);
	}

}
