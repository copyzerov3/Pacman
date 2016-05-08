
#include <stdio.h>
#include "MainMenuScreen.h"
#include <fstream>
#include <irrKlang.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define AXIS_THRESHOLD 500

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
Screen* screen;
irrklang::ISoundEngine* engine;

bool XPassThreshold = false;
bool yPassThreshold = false;

bool EnterPressedOnJoystick = false;
int previousTick = 0;
int Tick = 0;

int HighScore = 100;
void display(void)
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	screen->Draw(SCREEN_WIDTH,SCREEN_HEIGHT);
	glutSwapBuffers();
}

void idle()
{	
	if (screen->SwitchScreen())
	{
		Screen* temp = screen->SwitchScreen();
		delete screen;
		screen = temp;
		if (!screen->Load(SCREEN_WIDTH, SCREEN_HEIGHT))
			exit(1);
	}

	screen->Update(SCREEN_WIDTH,SCREEN_HEIGHT,Tick-previousTick);
	previousTick = Tick;
	glutPostRedisplay();
}
void init(void)
{
	/* select clearing (background) color       */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, -100.0, 100.0);
	

	std::string line;
	std::ifstream scoreFile("Scores.dat");
	if (scoreFile.is_open())
	{
		while (std::getline(scoreFile, line))
		{
			HighScore = atoi(line.c_str());
		}
		scoreFile.close();
	}
	else
	{
		printf("Failed to open for read trying to create and write\n");
		std::ofstream ScoreFile("Scores.dat");
		if (ScoreFile.is_open())
		{
			ScoreFile << "100";
			ScoreFile.close();
		}
		else
		{
			printf("Failed opening file to write to\n");
		}

	}
	engine = irrklang::createIrrKlangDevice();
	if (!engine)
	{
		printf("Could not start sound engine\n");
		exit(1);
	}

	screen = new MainMenuScreen(SCREEN_WIDTH,SCREEN_HEIGHT,HighScore,engine);
	if (!screen->Load(SCREEN_WIDTH, SCREEN_HEIGHT))
		exit(1);

	

	

}
void OnMouse(int button, int state, int x, int y)
{
	
}
void OnKeyDown(unsigned char key,int x, int y)
{
	Screen::InputEvent Event;
	Event.Down = true;
	switch (key)
	{
	case 'W':
	case 'w':
		Event.Event = Screen::UP;
		screen->AddInputEvent(Event);
		break;
	case 'S':
	case 's':
		Event.Event = Screen::DOWN;
		screen->AddInputEvent(Event);
		break;
	case 'a':
	case 'A':
		Event.Event = Screen::LEFT;
		screen->AddInputEvent(Event);
		break;
	case 'D':
	case 'd':
		Event.Event = Screen::RIGHT;
		screen->AddInputEvent(Event);
		break;
	case 13:
		Event.Event = Screen::ENTER;
		screen->AddInputEvent(Event);
		break;
	}
}
void OnKeyUp(unsigned char key, int x, int y)
{
	Screen::InputEvent Event;
	Event.Down = false;
	switch (key)
	{
	case 'W':
	case 'w':
		Event.Event = Screen::UP;
		screen->AddInputEvent(Event);
		break;
	case 'S':
	case 's':
		Event.Event = Screen::DOWN;
		screen->AddInputEvent(Event);
		break;
	case 'a':
	case 'A':
		Event.Event = Screen::LEFT;
		screen->AddInputEvent(Event);
		break;
	case 'D':
	case 'd':
		Event.Event = Screen::RIGHT;
		screen->AddInputEvent(Event);
		break;
	case 13:
		Event.Event = Screen::ENTER;
		screen->AddInputEvent(Event);
		break;
	case 27:
		delete screen;
		exit(0);
	}
}
void OnSpecialDown(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		OnKeyDown('W', x, y);
		break;
	case GLUT_KEY_DOWN:
		OnKeyDown('S', x, y);
		break;
	case GLUT_KEY_LEFT:
		OnKeyDown('A', x, y);
		break;
	case GLUT_KEY_RIGHT:
		OnKeyDown('D', x, y);
		break;
	}
}
void OnSpecialUp(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		OnKeyUp('W', x, y);
		break;
	case GLUT_KEY_DOWN:
		OnKeyUp('S', x, y);
		break;
	case GLUT_KEY_LEFT:
		OnKeyUp('A', x, y);
		break;
	case GLUT_KEY_RIGHT:
		OnKeyUp('D', x, y);
		break;
	}
}
void OnJoystick(unsigned int buttonMask, int x, int y, int z)
{
	if (x > AXIS_THRESHOLD)
	{
		XPassThreshold = true;
		OnKeyDown('D', 0, 0);
	}
	else if (x < -AXIS_THRESHOLD)
	{
		XPassThreshold = true;
		OnKeyDown('A', 0, 0);
	}
	else
	{
		if (XPassThreshold)
		{
			XPassThreshold = false; 
			OnKeyUp('A', 0, 0);
			OnKeyUp('D', 0, 0);
		}
	}
	if (y > AXIS_THRESHOLD)
	{
		yPassThreshold = true;
		OnKeyDown('S', 0, 0);
	}
	else if (y < -AXIS_THRESHOLD)
	{
		yPassThreshold = true;
		OnKeyDown('W', 0, 0);
	}
	else
	{
		if (yPassThreshold)
		{
			yPassThreshold = false;
			OnKeyUp('S', 0, 0);
			OnKeyUp('W', 0, 0);
		}
	}
	
	if (buttonMask & 0x01)
	{
		OnKeyDown(13,x,y);
		EnterPressedOnJoystick = true;
	}	
	else
	{
		
		if (EnterPressedOnJoystick)
		{
			OnKeyUp(13,x,y);
			EnterPressedOnJoystick = false;
		}
	}
		
	/*if (buttonMask & 0x02)
		printf("0x02 true\n");
	else
		printf("0x02 false\n");

	if (buttonMask & 0x04)
		printf("0x04 true\n");
	else 
		printf("0x04 false\n");

	if (buttonMask & 0x08)
		printf("0x08 true\n");
	else 
		printf("0x08 false\n");

	if (buttonMask & 0x10) 
		printf("0x10 true\n");
	else 
		printf("0x10 false\n");

	if (buttonMask & 0x20)
		printf("0x20 true\n");
	else 
		printf("0x20 false\n");

	if (buttonMask & 0x40) 
		printf("0x40 true\n");
	else
		printf("0x40 false\n");

	if (buttonMask & 0x80)
		printf("0x80 true\n");
	else 
		printf("0x80 false\n");
	printf("\n");
	//printf("x Axis :%d\ny Axis : %d\nz Axis :%d\n",x,y,z);*/
}
void OnTimer(int value)
{
	Tick += value;
	glutTimerFunc(10, OnTimer, 10);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(800, 100);
	glutCreateWindow("GL Pacman");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(OnMouse);
	glutKeyboardFunc(OnKeyDown);
	glutKeyboardUpFunc(OnKeyUp);
	glutSpecialFunc(OnSpecialDown);
	glutSpecialUpFunc(OnSpecialUp);
	glutJoystickFunc(OnJoystick,25);
	glutTimerFunc(10, OnTimer, 10);
	glutMainLoop();

	delete screen;
	return 0;   /* ISO C requires main to return int. */
}
