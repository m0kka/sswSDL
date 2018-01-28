#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "..\Util\Utility.h"
#include "..\Sprite\Sprite.h"
#include "..\Sprite\TiledSprite.h"
#include "..\Sprite\SpriteAnimated.h"
#include "..\Text\Text.h"
#include "..\Renderable.h"
#include "..\Object\Player\Player.h"
#include "..\UI\UI.h"
#include "..\Time\Timer.h"
#include <tinyxml2.h>


enum GameStates {
	GAMESTATE_NULL = -1,
	GAMESTATE_TEST,
	GAMESTATE_EXIT
};

class GameState
{
protected:
	SDL_Event m_Event;

	std::vector <Sprite*> m_Sprites;
	std::vector <Text*> m_Texts;
	std::vector <Renderable*> m_Renderables;
	std::vector <Player*> m_Players;
	std::vector <UI*> m_UIs;

	Timer* m_Timer;



public:
	virtual void handleEvents() = 0;
	virtual void logic() = 0;
	virtual void render() = 0;

	GameState() {}
	virtual ~GameState() {}
public:
};


