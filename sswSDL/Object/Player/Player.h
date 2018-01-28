#pragma once
#include "..\Object.h"
#include "..\..\Sprite\SpriteAnimated.h"


class Player :
	public Object
{

enum State {
	STATE_IDLE,
	STATE_WALKING,
	STATE_NULL
};


private:
	SpriteAnimated* m_SpriteAnimated;
	State m_NextState;
	State m_CurrentState;

	void changeState();
public:
	Player();
	~Player();

	void setNextState(State stage);
	void step() override;
	void handleInput(const SDL_Event& event);
};

