#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Util\Utility.h"
#include "Sprite\Sprite.h"
#include "Sprite\SpriteAnimated.h"
#include "Text\Text.h"
#include "Game\Game.h"

#include <tinyxml2.h>

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH	= 1400;



int main(int, char**) {


	Game::getInstance();

	return 0;
}
