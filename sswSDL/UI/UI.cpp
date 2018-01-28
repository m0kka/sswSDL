#include "UI.h"
#include "../Game/Game.h"


void UI::parseAnchor()
{
	m_Dimensions = m_Text->getSprite()->getDim();

	gmtl::Vec2i screen_dim;
	Game::getWindowSize(screen_dim);

	switch (m_Anchor) {
	case TOP_FULL:
		m_Dimensions = gmtl::Vec2i(screen_dim[0], 100);

		m_Position = gmtl::Vec2i(0, 0);
		break;

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

	case CENTRE_FULL:
		m_Dimensions = gmtl::Vec2i(screen_dim[0], 100);

		m_Position = gmtl::Vec2i(
			0,
			(screen_dim[1] / 2) - (m_Dimensions[1] / 2)
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

	case BOTTOM_FULL:
		m_Dimensions = gmtl::Vec2i(screen_dim[0], 100);

		m_Position = gmtl::Vec2i(
			0, screen_dim[1] - m_Dimensions[1]
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

	case FULL:
		m_Dimensions = screen_dim;
		m_Position = gmtl::Vec2i(0, 0);
		break;

	case NONE:
	default:
		break;
	}

	m_Text->setWrap(true, screen_dim[0] - (screen_dim[0])/10);

	posUpdate();
}

void UI::posUpdate()
{
	m_Text->setPos(m_Position);
}

void UI::load()
{
}

UI::UI()
{
}

using namespace tinyxml2;
#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

tinyxml2::XMLError UI::loadXML()
{
	XMLDocument textDoc;
	XMLError eResult = textDoc.LoadFile(m_DataPath.c_str());
	XMLCheckResult(eResult);

	XMLNode* pRoot = textDoc.FirstChild();
	if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;

	XMLElement* pElement = textDoc.FirstChildElement("entries");
	if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

	const char* font = nullptr;
	int size;
	int red, green, blue;

	// XML root attributes

	font = pElement->Attribute("font");
	if (font == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;

	eResult = pElement->QueryIntAttribute("size", &size);
	XMLCheckResult(eResult);

	eResult = pElement->QueryIntAttribute("cRed", &red);
	XMLCheckResult(eResult);

	eResult = pElement->QueryIntAttribute("cGreen", &green);
	XMLCheckResult(eResult);

	eResult = pElement->QueryIntAttribute("cBlue", &blue);
	XMLCheckResult(eResult);


	// Iterate through the entries
	XMLElement* pEntryElement = pElement->FirstChildElement("entry");

	while (pEntryElement != nullptr) {

		Entry* entry = new Entry();
		const char* entryID = nullptr;
		const char* entryMsg = nullptr;


		entryID = pEntryElement->Attribute("id");
		if (entryID == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;


		XMLText* textNode = pEntryElement->FirstChild()->ToText();
		entryMsg = textNode->Value();
		if (entryMsg == nullptr) return XML_ERROR_PARSING_TEXT;

		// Compile into Entry struct and push_back to the entries list
		entry->p_ID = entryID;
		entry->p_Text = entryMsg;

		m_TextEntries.push_back(entry);

		pEntryElement = pEntryElement->NextSiblingElement("entry");
	}

	pElement = pElement->NextSiblingElement("background");
	if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

	const char* tilesheetChar = nullptr;
	int type = -1;

	tilesheetChar = pElement->Attribute("tilesheet");
	if (tilesheetChar == nullptr) return XML_ERROR_PARSING_ELEMENT;

	eResult = pElement->QueryIntAttribute("type", &type);
	XMLCheckResult(eResult);


	// Compose fontpath string
	std::string fontPath = GameSettings::GAME_RESOURCEPATH + font;

	// Compose SDL_Color
	SDL_Color color = { red, green, blue };

	// Create instance of Text with right properties
	m_Text = new Text(Game::getRenderer(), fontPath, DEFAULT_TEXT, color, size);
	if (m_Text == nullptr) return XML_ERROR_PARSING;

	// Compose tilesheetPath string
	std::string tilesheetPath = GameSettings::GAME_RESOURCEPATH + tilesheetChar;

	// Instantiate according TiledSprite
	m_Background = new TiledSprite(tilesheetPath);
	if (m_Background == nullptr) return XML_ERROR_PARSING;

	m_BackgroundStyle = BackgroundStyle(type);


	return XML_SUCCESS;
}

UI::Entry * UI::findEntryByID(const std::string & id)
{
	// Iterate through the vector
	for (unsigned int i = 0; i < m_TextEntries.size(); i++) {
		
		// If entry at current index has the wanted ID, return it
		if (m_TextEntries.at(i)->p_ID == id)
			return m_TextEntries.at(i);
	}

	// If nothing found, return the nullptr
	return nullptr;
}

//todo: proper contructors!
UI::UI(UIAnchor anchor, const std::string& path)
	: m_Anchor(anchor), m_DataPath(path)
{
	m_Text = new Text(Game::getRenderer(), GameSettings::GAME_RESOURCEPATH + "alagard.ttf", DEFAULT_TEXT);
	loadXML();
	parseAnchor();
	m_Shown = false;
	setEntry(0);
	show();
}

UI::~UI()
{
}

void UI::handleInput(const SDL_Event & event)
{
}

void UI::step()
{
}

void UI::draw()
{
	if (m_Shown)
		m_Text->draw();
}

void UI::addEntry(Entry entry)
{
	m_TextEntries.push_back(&entry);
}

void UI::setEntry(int id)
{
	m_Text->setText(m_TextEntries.at(id)->p_Text);
	parseAnchor();
}

void UI::setEntry(const std::string & id)
{
	m_Text->setText(findEntryByID(id)->p_Text);
	parseAnchor();
}

void UI::show()
{
	m_Shown = true;
}

void UI::hide()
{
	m_Shown = false;
}
