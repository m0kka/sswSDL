#include "SpriteAnimated.h"
#include "..\Game\Game.h"


using namespace tinyxml2;
#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

void SpriteAnimated::load()
{
	m_Frames.clear();

	loadXML();
	loadTexture();
}

tinyxml2::XMLError SpriteAnimated::loadXML()
{
	XMLDocument animDoc;
	XMLError eResult = animDoc.LoadFile(m_AnimPath.c_str());
	XMLCheckResult(eResult);

	XMLNode* pRoot = animDoc.FirstChild();
	if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;

	XMLElement* pElement = animDoc.FirstChildElement("atlas");
	if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

	const char* filePath = nullptr;
	filePath = pElement->Attribute("imagePath");
	if (filePath == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
	m_Path = GameSettings::GAME_RESOURCEPATH + filePath;

	XMLElement* pFrameElement = pElement->FirstChildElement("frame");


	while (pFrameElement != nullptr) {

		int x, y, w, h, d;
		const char* attribName = nullptr;
		attribName = pFrameElement->Attribute("n");
		if (attribName == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;


		eResult = pFrameElement->QueryIntAttribute("x", &x);
		XMLCheckResult(eResult);

		eResult = pFrameElement->QueryIntAttribute("y", &y);
		XMLCheckResult(eResult);

		eResult = pFrameElement->QueryIntAttribute("w", &w);
		XMLCheckResult(eResult);

		eResult = pFrameElement->QueryIntAttribute("h", &h);
		XMLCheckResult(eResult);

		eResult = pFrameElement->QueryIntAttribute("d", &d);
		XMLCheckResult(eResult);


		SDL_Rect rect = {x, y, w, h};

		m_Frames.push_back(Frame(attribName, rect, d));

		pFrameElement = pFrameElement->NextSiblingElement("frame");
	}

	return XML_SUCCESS;
}

void SpriteAnimated::structHelper(const std::vector<SDL_Rect>& rectvec)
{
	for (int i = 0; i < rectvec.size(); i++) {
		m_Frames.at(i) = Frame("gen_" + i, rectvec.at(i), 0);
	}
}

void SpriteAnimated::init()
{
	Sprite::init();

	m_AmountFrames = m_Frames.size();
	m_currentFrame = 0;
	m_Timer = 0;
	m_Clip = (m_Frames.at(m_currentFrame).getClip());
}

void SpriteAnimated::parseAnchor()
{
	gmtl::Vec2i screen_dim;
	Game::getWindowSize(screen_dim);

	gmtl::Vec2i clipDim(m_Frames.at(m_currentFrame).getClip()->w, m_Frames.at(m_currentFrame).getClip()->h);

	switch (m_Anchor) {

	case TOP_LEFT:
		m_Position = gmtl::Vec2i(0, 0);
		break;

	case TOP_CENTRE:
		m_Position = gmtl::Vec2i(
			(screen_dim[0] / 2) - (clipDim[0] / 2), 0
		);
		break;

	case TOP_RIGHT:
		m_Position = gmtl::Vec2i(
			screen_dim[0] - clipDim[0], 0
		);
		break;

	case CENTRE_LEFT:
		m_Position = gmtl::Vec2i(
			0, (screen_dim[1] / 2) - (clipDim[1] / 2)
		);
		break;

	case CENTRE:
		m_Position = gmtl::Vec2i(
			(screen_dim[0] / 2) - (clipDim[0] / 2),
			(screen_dim[1] / 2) - (clipDim[1] / 2)
		);
		break;

	case CENTRE_RIGHT:
		m_Position = gmtl::Vec2i(
			screen_dim[0] - clipDim[0],
			(screen_dim[1] / 2) - (clipDim[1] / 2)
		);
		break;

	case BOTTOM_LEFT:
		m_Position = gmtl::Vec2i(
			0, screen_dim[1] - clipDim[1]
		);
		break;

	case BOTTOM_CENTRE:
		m_Position = gmtl::Vec2i(
			(screen_dim[0] / 2) - (clipDim[0] / 2),
			screen_dim[1] - clipDim[1]
		);
		break;

	case BOTTOM_RIGHT:
		m_Position = gmtl::Vec2i(
			screen_dim[0] - clipDim[0],
			screen_dim[1] - clipDim[1]
		);
		break;

	case NONE:
	default:
		break;
	}
}

SpriteAnimated::SpriteAnimated()
{
}

SpriteAnimated::SpriteAnimated(SDL_Renderer * renderer, const std::string & animPath)
	: m_AnimPath(animPath)
{
	m_Renderer = renderer;

	load();
	init();
}

SpriteAnimated::SpriteAnimated(SDL_Renderer * renderer, gmtl::Vec2i pos, const std::string & animPath)
	: m_AnimPath(animPath)
{
	m_Renderer = renderer;
	m_Position = pos;

	load();
	init();
}



SpriteAnimated::SpriteAnimated(SDL_Renderer * renderer, const std::string & texturePath, const std::vector<SDL_Rect>& clips)
{
	m_Renderer = renderer;
	m_Path = texturePath;

	structHelper(clips);
	loadTexture();
	init();
}

SpriteAnimated::SpriteAnimated(SDL_Renderer * renderer, SDL_Texture * texture, const std::vector<SDL_Rect>& clips)
{
	m_Renderer = renderer;
	m_Texture = texture;

	structHelper(clips);
	init();
}

SpriteAnimated::SpriteAnimated(SDL_Renderer * renderer, const std::string & texturePath, gmtl::Vec2i pos, const std::vector<SDL_Rect>& clips)
{
	m_Renderer = renderer;
	m_Path = texturePath;
	m_Position = pos;

	structHelper(clips);
	loadTexture();
	init();
}

SpriteAnimated::SpriteAnimated(SDL_Renderer * renderer, SDL_Texture * texture, gmtl::Vec2i pos, const std::vector<SDL_Rect>& clips)
{
	m_Renderer = renderer;
	m_Texture = texture;
	m_Position = pos;

	structHelper(clips);
	init();
}


SpriteAnimated::~SpriteAnimated()
{
}

void SpriteAnimated::draw()
{
	Uint64 now = SDL_GetPerformanceCounter();
	double deltaTime = ((now - m_Timer) * 1000 / (double) SDL_GetPerformanceFrequency());

	if (deltaTime > (double)m_Frames.at(m_currentFrame).getDelay()) {

		if (m_currentFrame < (m_AmountFrames - 1))
			m_currentFrame++;
		else
			m_currentFrame = 0;
		m_Timer = SDL_GetPerformanceCounter();
	}

	///////// Draw
	m_Clip = (m_Frames.at(m_currentFrame).getClip());
	Sprite::draw();
}

void SpriteAnimated::setAnimation(const std::string & path)
{
	m_AnimPath = path;

	load();
	init();
}
