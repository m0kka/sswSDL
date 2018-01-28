#pragma once
#include "../GameState.h"
#include "../Game.h"

#include <vector>
#include <math.h>

class Test :
	public GameState
{
private:

	int m_TSTest = 0;
	TiledSprite* TSR;

	int m_Angle;

	Uint64 m_TextTimer;
	short m_TextIndex;
	const std::string m_TextEntries[2] = {
		"This is the tale of Ghart The Old, a wizard and wanderer that has ventured the world for many years seeking to multiply the good and diminish the evil.",
		"Mistakes he had done many on his travels and errands, often leading to others suffering the consequences of his erring."
	};

public:
	void handleEvents();
	void logic();
	void render();
	Test();
	~Test();
};

