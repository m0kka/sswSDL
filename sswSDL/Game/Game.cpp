#include "Game.h"

Game* Game::m_Instance = nullptr;
GameStates Game::m_StateID = GAMESTATE_NULL;
GameStates Game::m_NextState = GAMESTATE_NULL;
GameState* Game::m_CurrentState = nullptr;

Timer *Game::m_Timer = new Timer();

SDL_Window* Game::m_Window = nullptr;
SDL_Renderer* Game::m_Renderer = nullptr;



Game::Game()
{
	// TODO:: proper init
	if (!initSDL()) {
		Util::logSDLError(std::cout, "Error Initializing SDL!");
		system("PAUSE");
		exit(1);
	}

	if (!initWindow()) {
		Util::logSDLError(std::cout, "Error Initializing SDL Window!");
		system("PAUSE");
		exit(1);
	}


	m_Instance = this;
	m_AverageFPS = 0;
	m_Frames = 0;
	m_CapTimer = new Timer();

	if (!m_Timer->isStarted())
		m_Timer->start();

	m_CurrentState = new Test();
	play();
}


Game::~Game()
{
	Util::cleanup(m_Window, m_Renderer);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	m_Instance = nullptr;
}

void Game::play()
{
	while (m_StateID != GAMESTATE_EXIT) {

		m_CapTimer->start();

		m_CurrentState->handleEvents();

		m_AverageFPS = m_Frames / (m_Timer->getTicks() / 1000.f);
		if (m_AverageFPS > 2000000)
			m_AverageFPS = 0;

		std::cout << m_AverageFPS << std::endl;
		
		m_CurrentState->logic();
		changeState();
		m_CurrentState->render();

		m_Frames++;

		int frameTicks = m_CapTimer->getTicks();
		if (frameTicks < GameSettings::WINDOW_TICKS_PER_FRAME)
			SDL_Delay(GameSettings::WINDOW_TICKS_PER_FRAME - frameTicks);
	}
}

bool Game::initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {

		Util::logSDLError(std::cout, "SDL_Init");
		return false;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		Util::logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return false;
	}

	if (TTF_Init() != 0) {
		Util::logSDLError(std::cout, "TTF_Init");
		IMG_Quit();
		SDL_Quit();
		return false;
	}

	return true;
}

bool Game::initWindow()
{
	m_Window = SDL_CreateWindow(GameSettings::WINDOW_NAME.c_str(), GameSettings::WINDOW_POS[0], GameSettings::WINDOW_POS[1], GameSettings::WINDOW_DIM[0], GameSettings::WINDOW_DIM[1], SDL_WINDOW_SHOWN);

	if (m_Window == nullptr) {
		Util::logSDLError(std::cout, "CreateWindow");
		IMG_Quit();
		SDL_Quit();
		system("PAUSE");
		return false;
	}


	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

	if (m_Renderer == nullptr) {
		Util::logSDLError(std::cout, "CreateRenderer");
		Util::cleanup(m_Window);
		IMG_Quit();
		SDL_Quit();

		system("PAUSE");
		return false;
	}
	return true;
}

void Game::changeState()
{
	if (m_NextState != GAMESTATE_NULL) {
		if (m_NextState != GAMESTATE_EXIT) {
			delete m_CurrentState;
		}

		switch (m_NextState) {
			// TODO
		GAMESTATE_EXIT:
			m_StateID = GAMESTATE_EXIT;
			break;
		}
	}
}

Game* Game::getInstance()
{
	if (m_Instance == nullptr) {
		m_Instance = new Game();
	}

	return m_Instance;
}

void Game::setNextState(GameStates newState)
{
	if (m_NextState != GAMESTATE_EXIT) {
		m_NextState = newState;
	} else {
		m_StateID = newState;
	}
}

void Game::getWindowSize(gmtl::Vec2i & size)
{
	SDL_GetWindowSize(m_Window, &size[0], &size[1]);
}

void Game::getWindowPos(gmtl::Vec2i & pos)
{
	SDL_GetWindowPosition(m_Window, &pos[0], &pos[1]);
}
