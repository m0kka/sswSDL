#pragma once
#include <iostream>
#include <string>

#include <gmtl\Vec.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "..\Util\Utility.h"
#include "..\Time\Timer.h"

#include "GameState.h"
#include "GameStates/Test.h"
#include "GameSettings.h"




class Game
{
private:
	static Game* m_Instance;
	Game();
	~Game();

	static SDL_Window* m_Window;
	static SDL_Renderer* m_Renderer;

	static Timer* m_Timer;
	Timer* m_CapTimer;
	float m_AverageFPS;
	Uint32 m_Frames;


	void play();
	bool initSDL();
	bool initWindow();

	static GameState* m_CurrentState;
	static GameStates m_StateID;
	static GameStates m_NextState;

	void changeState();

public:
	static Game* getInstance();
	static void setNextState(GameStates newState);
	inline static SDL_Window* getWindow() { return m_Window; }
	inline static SDL_Renderer* getRenderer() { return m_Renderer; }
	inline static Timer* getTimer() { return m_Timer; }

	static void getWindowSize(gmtl::Vec2i& size);
	static void getWindowPos(gmtl::Vec2i& pos);
};

