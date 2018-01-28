#include "TiledSprite.h"
#include "../Game/Game.h"

void TiledSprite::init()
{
	SDL_QueryTexture(m_Texture, &m_Format, nullptr, &m_Dimensions[0], &m_Dimensions[1]);

	m_BlendMode = SDL_BLENDMODE_NONE;
	m_Alpha = 1;
	m_FlipMode = SDL_FLIP_NONE;
	m_Angle = 0;
}

void TiledSprite::load()
{
	loadXML();
	loadTexture();
}

using namespace tinyxml2;
#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

tinyxml2::XMLError TiledSprite::loadXML()
{
	XMLDocument tileDoc;
	XMLError eResult = tileDoc.LoadFile(m_XMLPath.c_str());
	XMLCheckResult(eResult);

	XMLNode* pRoot = tileDoc.FirstChild();
	if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;

	XMLElement* pElement = tileDoc.FirstChildElement("tilesheet");
	if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

	const char* filePath = nullptr;
	filePath = pElement->Attribute("imagePath");
	if (filePath == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
	m_Path = GameSettings::GAME_RESOURCEPATH + filePath;

	XMLElement* pClipElement = pElement->FirstChildElement("clip");

	while (pClipElement != nullptr) {

		int ID, x, y, w, h;

		eResult = pClipElement->QueryIntAttribute("ID", &ID);
		XMLCheckResult(eResult);

		eResult = pClipElement->QueryIntAttribute("x", &x);
		XMLCheckResult(eResult);

		eResult = pClipElement->QueryIntAttribute("y", &y);
		XMLCheckResult(eResult);

		eResult = pClipElement->QueryIntAttribute("w", &w);
		XMLCheckResult(eResult);

		eResult = pClipElement->QueryIntAttribute("h", &h);
		XMLCheckResult(eResult);

		SDL_Rect* rect = new SDL_Rect{ x, y, w, h };
		m_Tiles.push_back(new Tile(rect, ID));

		pClipElement = pClipElement->NextSiblingElement("clip");

	}

	return XML_SUCCESS;
}

TiledSprite::TiledSprite()
{
}

TiledSprite::Tile * TiledSprite::findTileByID(int id)
{
	// Iterate through the vector
	for (unsigned int i = 0; i < m_Tiles.size(); i++) {

		// If entry at current index has the wanted ID, return it
		if (m_Tiles.at(i)->p_ID == id)
			return m_Tiles.at(i);
	}

	// If nothing found, return the nullptr
	return nullptr;
}

void TiledSprite::setTileVector(int at)
{
	m_Clip = m_Tiles.at(at)->p_Clip;
}


TiledSprite::~TiledSprite()
{
}


TiledSprite::TiledSprite(const std::string & XMLpath)
	: m_XMLPath(XMLpath)
{
	m_Renderer = Game::getRenderer();
	m_XMLPath = XMLpath;
	load();
	init();
	setTileVector(0);
}

void TiledSprite::setTile(int id)
{
	m_Clip = findTileByID(id)->p_Clip;
}
