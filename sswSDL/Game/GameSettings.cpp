#include "GameSettings.h"

const std::string GameSettings::WINDOW_NAME = "Wake Up";
const gmtl::Vec2i GameSettings::WINDOW_POS = gmtl::Vec2i(100, 100);
const gmtl::Vec2i GameSettings::WINDOW_DIM = gmtl::Vec2i(640, 480);

const std::string GameSettings::GAME_RESOURCEPATH = Util::getResourcePath();

const int GameSettings::WINDOW_FPS = 60;
const int GameSettings::WINDOW_TICKS_PER_FRAME = 1000 / WINDOW_FPS;


GameSettings::GameSettings()
{
}


GameSettings::~GameSettings()
{
}
