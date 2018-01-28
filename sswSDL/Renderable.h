#pragma once
class Renderable
{

public:
	Renderable();
	~Renderable();
	virtual void draw() = 0;
	virtual void destroy() = 0;
};

