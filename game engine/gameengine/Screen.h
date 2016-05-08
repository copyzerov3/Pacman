#pragma once
#include "SceneGraph.h"
#include <vector>
#include <irrKlang.h>
class Screen
{
public:
	Screen(int HighScore,irrklang::ISoundEngine* SoundEngine);
	~Screen();
	enum INPUT_EVENTS
	{
		LEFT,RIGHT,UP,DOWN,ENTER
	};
	struct InputEvent
	{
		INPUT_EVENTS Event;
		bool Down;
	};
	


	virtual void Update(int ScreenWidth, int ScreenHeight,int DeltaTime);
	virtual void Draw(int ScreenWidth, int ScreenHeight);
	virtual bool Load(int ScreenWidth, int ScreenHeight);
	Screen* SwitchScreen(){ return NextScreen; }
	void AddInputEvent(InputEvent Event){ InputEvents.push_back(Event); }
protected:
	Screen* NextScreen;
	irrklang::ISoundEngine* SoundEngine;
	std::vector<InputEvent> InputEvents;
	SceneGraph Graph;
	int HighScore;

};

