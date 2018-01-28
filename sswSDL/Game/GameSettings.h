#pragma once

#include <string>
#include <gmtl\Vec.h>
#include "..\Util\Utility.h"

class GameSettings
{
private:
	GameSettings();
	~GameSettings();
public:

	const static std::string WINDOW_NAME;
	const static gmtl::Vec2i WINDOW_POS;
	const static gmtl::Vec2i WINDOW_DIM;

	const static int WINDOW_FPS;
	const static int WINDOW_TICKS_PER_FRAME;


	const static std::string GAME_RESOURCEPATH;

	
};

