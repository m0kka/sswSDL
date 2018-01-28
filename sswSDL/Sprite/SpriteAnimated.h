#pragma once
#include "Sprite.h"
#include "../Util/Utility.h"
#include <vector>
#include <iostream>

#include <tinyxml2.h>

struct Frame {
private:
	std::string m_Name;
	SDL_Rect m_Rect;
	int m_Delay;
public :
	Frame(const std::string& name, const SDL_Rect& rect, const Uint32& delay)
		: m_Name(name), m_Rect(rect), m_Delay(delay) { }
	inline SDL_Rect* getClip() { return &m_Rect; }
	inline std::string getName() const { return m_Name; }
	inline int getDelay() const { return m_Delay; }
};

class SpriteAnimated :
	public Sprite
{
protected:
	std::vector<Frame> m_Frames;
	int m_Speed;
	int m_AmountFrames;
	std::string m_AnimPath;
	int m_currentFrame;

	Uint64 m_Timer;

	void load();
	tinyxml2::XMLError loadXML();
	void structHelper(const std::vector<SDL_Rect>& rectvec);
	void init() override;

	void parseAnchor() override;

public:
	SpriteAnimated();
	SpriteAnimated(SDL_Renderer* renderer, const std::string& animPath);
	SpriteAnimated(SDL_Renderer* renderer, gmtl::Vec2i pos, const std::string& animPath);


	SpriteAnimated(SDL_Renderer* renderer, const std::string& texturePath, const std::vector<SDL_Rect>& clips);
	SpriteAnimated(SDL_Renderer* renderer, SDL_Texture* texture, const std::vector<SDL_Rect>& clips);

	SpriteAnimated(SDL_Renderer* renderer, const std::string& texturePath, gmtl::Vec2i pos, const std::vector<SDL_Rect>& clips);
	SpriteAnimated(SDL_Renderer* renderer, SDL_Texture* texture, gmtl::Vec2i pos, const std::vector<SDL_Rect>& clips);


	~SpriteAnimated();

	void draw() override;



	////// Getters and Setters
	inline Frame getCurrentFrame() const { return m_Frames.at(m_currentFrame); }
	inline int getFramesAmount() const { return m_AmountFrames; }
	inline int getSpeed() const { return m_Speed; }

	void setSpeed(int speed) { m_Speed = speed; }

	void setAnimation(const std::string& path);
};

