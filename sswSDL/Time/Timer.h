#pragma once

#include <SDL.h>

class Timer
{
private:
	Uint32 m_StartTicks;
	Uint32 m_PausedTicks;

	bool m_Started;
	bool m_Paused;


public:
	Timer();
	~Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks() const;

	inline bool isStarted() const { return m_Started; }
	inline bool isPaused() const { return m_Started && m_Paused; }
};

