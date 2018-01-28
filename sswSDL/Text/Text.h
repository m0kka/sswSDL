#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <gmtl\Vec.h>

#include "../Util/Utility.h"
#include "../Sprite/Sprite.h"
#include "../Renderable.h"



class Text
	: public Renderable
{
protected:
	const int m_DefaultFontSize = 30;
	const SDL_Color m_DefaultColor = { 255, 255, 255 };

protected:
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_Texture;
	Sprite* m_Sprite;

	bool m_Wrapped = false;
	Uint32 m_WrapLength = 50;

	TTF_Font* m_Font;
	std::string m_FontFile;


	SDL_Color m_Color;
	
	std::string m_Text;
	int m_FontSize;

	bool m_externalFont;

	

	void init();
	void makeTexture();
	void makeSprite();

	Text();
public:
	Text(SDL_Renderer* renderer, const std::string& fontFile);
	Text(SDL_Renderer* renderer, const std::string& fontFile, int fontSize);
	Text(SDL_Renderer* renderer, const std::string& fontFile, SDL_Color color);
	Text(SDL_Renderer* renderer, const std::string& fontFile, SDL_Color color, int fontSize);
	Text(SDL_Renderer* renderer, const std::string& fontFile, const std::string& message);
	Text(SDL_Renderer* renderer, const std::string& fontFile, const std::string& message, int fontSize);
	Text(SDL_Renderer* renderer, const std::string& fontFile, const std::string& message, SDL_Color color);
	Text(SDL_Renderer* renderer, const std::string& fontFile, const std::string& message, SDL_Color color, int fontSize);
	
	Text(SDL_Renderer* renderer, TTF_Font* font);
	Text(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color);
	Text(SDL_Renderer* renderer, TTF_Font* font, const std::string& message);
	Text(SDL_Renderer* renderer, TTF_Font* font, const std::string& message, SDL_Color color);

	~Text();

	////// Getter and Setter functions //////
	inline gmtl::Vec2i getPos() const { return m_Sprite->getPos(); }
	inline SDL_Color getColor() const { return m_Color; }
	inline std::string getText() const { return m_Text; }
	inline Sprite* getSprite() const { return m_Sprite; }

	void setText(const std::string& text) { m_Text = text; init(); }
	void setPos(const gmtl::Vec2i& pos) { m_Sprite->setPos(pos); }
	void setWrap(bool enableWrap, Uint32 wrapLength = 50);

	void draw();
	void destroy();
};

