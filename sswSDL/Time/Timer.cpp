#include "Timer.h"



Timer::Timer()
{
	m_StartTicks = 0;
	m_PausedTicks = 0;

	m_Paused = false;
	m_Started = false;
}


Timer::~Timer()
{
}

void Timer::start()
{
	m_Started = true;
	m_Paused = false;

	m_StartTicks = SDL_GetTicks();
	m_PausedTicks = 0;
}

void Timer::stop()
{
	m_Started = false;
	m_Paused = false;

	m_StartTicks = 0;
	m_PausedTicks = 0;
}

void Timer::pause()
{
	if (m_Started && !m_Paused) {

		m_Paused = true;

		m_PausedTicks = SDL_GetTicks() - m_StartTicks;
		m_StartTicks = 0;
	}
}

void Timer::unpause()
{
	if (m_Started && m_Paused) {
		
		m_Paused = false;

		m_StartTicks = SDL_GetTicks() - m_PausedTicks;
		m_PausedTicks = 0;
	}
}

Uint32 Timer::getTicks() const
{
	if (m_Started)
		if (m_Paused)
			return m_PausedTicks;
		else
			return SDL_GetTicks() - m_StartTicks;
	else
		return 0;
}
