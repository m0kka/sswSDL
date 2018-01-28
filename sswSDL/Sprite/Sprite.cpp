#include "Sprite.h"
#include "..\Game\Game.h"

void Sprite::parseAnchor()
{

	gmtl::Vec2i screen_dim;
	Game::getWindowSize(screen_dim);

	switch (m_Anchor) {

	case TOP_LEFT:
		m_Position = gmtl::Vec2i(0, 0);
		break;

	case TOP_CENTRE:
		m_Position = gmtl::Vec2i(
			(screen_dim[0] / 2) - (m_Dimensions[0] / 2), 0
		);
		break;

	case TOP_RIGHT:
		m_Position = gmtl::Vec2i(
			screen_dim[0] - m_Dimensions[0], 0
		);
		break;

	case CENTRE_LEFT:
		m_Position = gmtl::Vec2i(
			0, (screen_dim[1] / 2) - (m_Dimensions[1] / 2)
		);
		break;

	case CENTRE:
		m_Position = gmtl::Vec2i(
			(screen_dim[0] / 2) - (m_Dimensions[0] / 2),
			(screen_dim[1] / 2) - (m_Dimensions[1] / 2)
		);
		break;

	case CENTRE_RIGHT:
		m_Position = gmtl::Vec2i(
			screen_dim[0] - m_Dimensions[0],
			(screen_dim[1] / 2) - (m_Dimensions[1] / 2)
		);
		break;

	case BOTTOM_LEFT:
		m_Position = gmtl::Vec2i(
			0, screen_dim[1] - m_Dimensions[1]
		);
		break;

	case BOTTOM_CENTRE:
		m_Position = gmtl::Vec2i(
			(screen_dim[0] / 2) - (m_Dimensions[0] / 2),
			screen_dim[1] - m_Dimensions[1]
		);
		break;

	case BOTTOM_RIGHT:
		m_Position = gmtl::Vec2i(
			screen_dim[0] - m_Dimensions[0],
			screen_dim[1] - m_Dimensions[1]
		);
		break;

	case NONE:
	default:
		break;
	}
}

void Sprite::init()
{
	SDL_QueryTexture(m_Texture, &m_Format, nullptr, &m_Dimensions[0], &m_Dimensions[1]);

	m_BlendMode = SDL_BLENDMODE_NONE;
	m_Alpha = 1;
	m_FlipMode = SDL_FLIP_NONE;
	m_Angle = 0;
}

void Sprite::loadTexture()
{
	m_Texture = IMG_LoadTexture(m_Renderer, m_Path.c_str());
	if (m_Texture == nullptr) {
		Util::logSDLError(std::cout, "LoadTexture");
	}
}

void Sprite::setColor()
{
	SDL_SetTextureColorMod(m_Texture, m_Color.red, m_Color.green, m_Color.blue);
}

void Sprite::setBlendMode()
{
	SDL_SetTextureBlendMode(m_Texture, m_BlendMode);
}

void Sprite::setAlpha()
{
	SDL_SetTextureAlphaMod(m_Texture, m_Alpha);
}

Sprite::Sprite(SDL_Renderer * renderer, const std::string & path)
	: m_Renderer(renderer), m_Path(path)
{
	loadTexture();
	init();
}

Sprite::Sprite(SDL_Renderer * renderer, SDL_Texture * texture)
	: m_Renderer(renderer), m_Texture(texture)
{
	init();
}

Sprite::Sprite(SDL_Renderer * renderer, const std::string & path, gmtl::Vec2i pos)
	: m_Renderer(renderer), m_Path(path), m_Position(pos)
{
	loadTexture();
	init();
}

Sprite::Sprite(SDL_Renderer * renderer, SDL_Texture * texture, gmtl::Vec2i pos)
	: m_Renderer(renderer), m_Texture(texture), m_Position(pos)
{
	init();
}

Sprite::Sprite(SDL_Renderer * renderer, const std::string & path, gmtl::Vec2i pos, SDL_Rect* clip)
	: m_Renderer(renderer), m_Path(path), m_Position(pos), m_Clip(clip)
{
	loadTexture();
	init();
}

Sprite::Sprite(SDL_Renderer * renderer, SDL_Texture * texture, gmtl::Vec2i pos, SDL_Rect* clip)
	: m_Renderer(renderer), m_Texture(texture), m_Position(pos), m_Clip(clip)
{
	init();
}

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(m_Texture);
}

void Sprite::draw()
{
	SDL_Rect dst = MathsUtil::vec2iToRect(m_Position);

	if (m_Destination == nullptr) {

		if (m_Clip != nullptr) {
			dst.w = m_Clip->w;
			dst.h = m_Clip->h;
		}
		else {
			dst.w = m_Dimensions[0];
			dst.h = m_Dimensions[1];
		}

		SDL_RenderCopyEx(m_Renderer, m_Texture, m_Clip, &dst, m_Angle, &m_Center, m_FlipMode);
	}
	else {
		if (m_UsePosForDestXY) {
			dst.w = m_Destination->w;
			dst.h = m_Destination->h;
			SDL_RenderCopyEx(m_Renderer, m_Texture, m_Clip, &dst, m_Angle, &m_Center, m_FlipMode);
		}
		else
		SDL_RenderCopyEx(m_Renderer, m_Texture, m_Clip, m_Destination, m_Angle, &m_Center, m_FlipMode);
	}

}

void Sprite::destroy()
{
	SDL_DestroyTexture(m_Texture);
	delete this;
}

void Sprite::setPos(int x, int y)
{
	m_Position[0] = x;
	m_Position[1] = y;
}

void Sprite::move(gmtl::Vec2i pos)
{
	m_Position[0] += pos[0];
	m_Position[1] += pos[1];
}

void Sprite::move(int x, int y)
{
	move(gmtl::Vec2i(x, y));
}

void Sprite::setColor(wuColor color)
{
	m_Color = color;
	setColor();
}

void Sprite::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	m_Color = wuColor(red, green, blue);
	setColor();
}

void Sprite::setBlendMode(SDL_BlendMode blendmode)
{
	m_BlendMode = blendmode;
	setBlendMode();
}

void Sprite::setAlpha(Uint8 alpha)
{
	m_Alpha = alpha;
	setAlpha();
}

void Sprite::setScale(const gmtl::Vec2i & scale)
{

	if (m_Destination == nullptr)
		m_Destination = new SDL_Rect;

	if (m_Clip == nullptr) {
		m_Destination->w = m_Dimensions[0] * scale[0];
		m_Destination->h = m_Dimensions[1] * scale[1];
	}
	else {
		m_Destination->w = m_Clip->w * scale[0];
		m_Destination->h = m_Clip->h * scale[1];
	}

	m_Destination->x = m_Position[0];
	m_Destination->y = m_Position[1];
}

void Sprite::setCenter(int x, int y)
{
	m_Center.x = x;
	m_Center.y = y;
}
