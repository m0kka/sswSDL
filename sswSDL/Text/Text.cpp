#include "Text.h"

void Text::init()
{
	if (m_Sprite != nullptr) {

		delete m_Sprite;
	}
		

	makeTexture();
	makeSprite();
}

void Text::makeTexture()
{
	if (m_externalFont) {
		m_Font = TTF_OpenFont(m_FontFile.c_str(), m_FontSize);

		if (m_Font == nullptr) {
			Util::logSDLError(std::cout, "TTF_OpenFont");
			m_Texture = nullptr;
			return;
		}
	}

	SDL_Surface* temp;

	if (m_Wrapped)
		temp = TTF_RenderText_Blended_Wrapped(m_Font, m_Text.c_str(), m_Color, m_WrapLength);
	else
		temp = TTF_RenderText_Blended(m_Font, m_Text.c_str(), m_Color);

	if (temp == nullptr) {
		if (m_externalFont)
			TTF_CloseFont(m_Font);

		Util::logSDLError(std::cout, "Text_init()");
		m_Texture = nullptr;
		return;
	}

	m_Texture = SDL_CreateTextureFromSurface(m_Renderer, temp);

	if (m_Texture == nullptr) {
		Util::logSDLError(std::cout, "CreateTextureFromSurface");
	}

	SDL_FreeSurface(temp);
	if (m_externalFont)
		TTF_CloseFont(m_Font);
}

void Text::makeSprite()
{
	m_Sprite = new Sprite(m_Renderer, m_Texture);
}

Text::Text()
{
}

Text::Text(SDL_Renderer * renderer, const std::string & fontFile)
	: m_Renderer(renderer), m_FontFile(fontFile), m_FontSize(m_DefaultFontSize), m_Color(m_DefaultColor), m_externalFont(true)
{
	init();
}

Text::Text(SDL_Renderer * renderer, const std::string & fontFile, int fontSize)
	: m_Renderer(renderer), m_FontFile(fontFile), m_FontSize(fontSize), m_Color(m_DefaultColor), m_externalFont(true)
{
	init();
}

Text::Text(SDL_Renderer * renderer, const std::string & fontFile, SDL_Color color)
	: m_Renderer(renderer), m_FontFile(fontFile), m_Color(color), m_FontSize(m_DefaultFontSize), m_externalFont(true)
{
	init();
}

Text::Text(SDL_Renderer * renderer, const std::string & fontFile, SDL_Color color, int fontSize)
	: m_Renderer(renderer), m_FontFile(fontFile), m_Color(color), m_FontSize(fontSize), m_externalFont(true)
{
	init();
}

Text::Text(SDL_Renderer * renderer, const std::string & fontFile, const std::string & message)
	: m_Renderer(renderer), m_FontFile(fontFile), m_Text(message), m_FontSize(m_DefaultFontSize), m_Color(m_DefaultColor), m_externalFont(true)
{
	init();
}

Text::Text(SDL_Renderer * renderer, const std::string & fontFile, const std::string & message, int fontSize)
	: m_Renderer(renderer), m_FontFile(fontFile), m_Text(message), m_FontSize(fontSize), m_Color(m_DefaultColor), m_externalFont(true)
{
	init();
}

Text::Text(SDL_Renderer * renderer, const std::string & fontFile, const std::string & message, SDL_Color color)
	: m_Renderer(renderer), m_FontFile(fontFile), m_Text(message), m_Color(color), m_FontSize(m_DefaultFontSize), m_externalFont(true)
{
	init();
}

Text::Text(SDL_Renderer * renderer, const std::string & fontFile, const std::string & message, SDL_Color color, int fontSize)
	: m_Renderer(renderer), m_FontFile(fontFile), m_Text(message), m_FontSize(fontSize), m_Color(color), m_externalFont(true)
{
	init();
}




Text::Text(SDL_Renderer * renderer, TTF_Font * font)
	: m_Renderer(renderer), m_Font(font), m_Color(m_DefaultColor), m_externalFont(false)
{
	init();
}

Text::Text(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color)
	: m_Renderer(renderer), m_Font(font),  m_Color(color), m_externalFont(false)
{
	init();
}

Text::Text(SDL_Renderer * renderer, TTF_Font * font, const std::string & message)
	: m_Renderer(renderer), m_Font(font), m_Text(message), m_Color(m_DefaultColor), m_externalFont(false)
{
	init();
}

Text::Text(SDL_Renderer * renderer, TTF_Font * font, const std::string & message, SDL_Color color)
	: m_Renderer(renderer), m_Font(font), m_Text(message), m_Color(color), m_externalFont(false)
{
	init();
}


Text::~Text()
{
	SDL_DestroyTexture(m_Texture);
	
}

void Text::setWrap(bool enableWrap, Uint32 wrapLength)
{
	m_Wrapped = enableWrap;
	m_WrapLength = wrapLength;
	init();
}

void Text::draw()
{
	m_Sprite->draw();
}

void Text::destroy()
{
	
	delete m_Sprite;

	if (!m_externalFont) {
		TTF_CloseFont(m_Font);
	}

	delete this;
}
