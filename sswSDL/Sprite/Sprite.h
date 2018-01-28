#pragma once
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <gmtl\Vec.h>

#include "../Renderable.h"
#include "../Util/Utility.h"

struct wuColor {
	Uint8 red;
	Uint8 green;
	Uint8 blue;
	wuColor(Uint8 red, Uint8 green, Uint8 blue) : red(red), green(green), blue(blue) {}
	wuColor() {}
};

class Sprite
	: public Renderable
{

public:
	enum Anchor {
		TOP_LEFT,
		TOP_CENTRE,
		TOP_RIGHT,
		CENTRE_LEFT,
		CENTRE,
		CENTRE_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_CENTRE,
		BOTTOM_RIGHT,
		NONE = -1
	};

protected:
	gmtl::Vec2i m_Position;
	int m_ZPos;			// TODO:: z-Buffering
	gmtl::Vec2i m_Dimensions;
	SDL_Rect* m_Clip;
	SDL_Rect* m_Destination;
	bool m_UsePosForDestXY = false;

	SDL_BlendMode m_BlendMode;
	wuColor m_Color;
	Uint8 m_Alpha;

	Anchor m_Anchor;

	double m_Angle;
	SDL_Point m_Center;
	SDL_RendererFlip m_FlipMode;

	Uint32 m_Format;

	SDL_Texture* m_Texture;
	SDL_Renderer* m_Renderer;
	std::string m_Path;

	virtual void init();
	void loadTexture();
	void setColor();
	void setBlendMode();
	void setAlpha();

	virtual void parseAnchor();


public:
	Sprite();
	Sprite(SDL_Renderer* renderer, const std::string& path);
	Sprite(SDL_Renderer* renderer, SDL_Texture* texture);

	Sprite(SDL_Renderer* renderer, const std::string& path, gmtl::Vec2i pos);
	Sprite(SDL_Renderer* renderer, SDL_Texture* texture, gmtl::Vec2i pos);

	Sprite(SDL_Renderer* renderer, const std::string& path, gmtl::Vec2i pos, SDL_Rect* clip);
	Sprite(SDL_Renderer* renderer, SDL_Texture* texture, gmtl::Vec2i pos, SDL_Rect* clip);

	 ~Sprite();

	virtual void draw();
	virtual void destroy();



	////// Lots of Getter and Setter Functions //////
	inline gmtl::Vec2i getPos() const { return m_Position; }
	inline int getZPos() const { return m_ZPos; }
	inline gmtl::Vec2i getDim() const { return m_Dimensions; }
	inline SDL_Rect* getClip() const { return m_Clip; }
	inline SDL_Rect getClipVal() const { return *m_Clip; }
	inline wuColor getColor() const { return m_Color; }
	inline SDL_BlendMode getBlendMode() const { return m_BlendMode; }
	inline Uint8 getAlpha() const { return m_Alpha; }

	inline SDL_RendererFlip getFlipMode() const { return m_FlipMode; }
	inline double getAngle() const { return m_Angle; }
	inline SDL_Point getCenter() const { return m_Center; }
	
	inline Uint32 getFormat() const { return m_Format; }
	inline SDL_Texture* getTexture() const { return m_Texture; }
	inline SDL_Renderer* getRenderer() const { return m_Renderer; }
	inline std::string getPath() const { return m_Path; }

	void setPos(gmtl::Vec2i pos) { m_Position = pos; }
	void setPos(int x, int y);
	void move(gmtl::Vec2i pos);
	void move(int x, int y);
	void setZPos(int z) { m_ZPos = z; }
	void setDim(gmtl::Vec2i dim) { m_Dimensions = dim; }
	void setClip(SDL_Rect* clip) { m_Clip = clip; }
	void setColor(wuColor color);
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blendmode);
	void setAlpha(Uint8 alpha);
	void setAnchor(Anchor anchor) { m_Anchor = anchor; parseAnchor(); }
	void setDestination(SDL_Rect* dest) { m_Destination = dest; }
	void setScale(const gmtl::Vec2i& scale);
	void setScale(const int& scale) { setScale(gmtl::Vec2i(scale, scale)); }
	void renderAtPos(bool state) { m_UsePosForDestXY = state; }

	void setFlipMode(const SDL_RendererFlip& flipmode) { m_FlipMode = flipmode; }
	void setCenter(const SDL_Point& center) { m_Center = center; }
	void setCenter(int x, int y);
	void setAngle(double angle) { m_Angle = angle; }

};

