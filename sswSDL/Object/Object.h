#pragma once

#include <gmtl\gmtl.h>
#include <SDL.h>

class Object
{
protected:
	gmtl::Vec2i m_Position;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	Object();
	~Object();
	virtual void posUpdate() = 0;

public:

	virtual void step() = 0;

	void setPos(const gmtl::Vec2i& pos) { m_Position = pos; posUpdate(); }
	void setPos(const int& x, const int& y) { setPos(gmtl::Vec2i(x, y)); }
	void move(const gmtl::Vec2i& pos) { 
		m_Position[0] += pos[0];
		m_Position[1] += pos[1];
		posUpdate();
	}
	void move(const int& x, const int& y) { move(gmtl::Vec2i(x, y)); }
};

