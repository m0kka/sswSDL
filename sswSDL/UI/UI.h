#pragma once

#include "..\Text\Text.h"
#include "..\Object\Object.h"
#include "..\Sprite\TiledSprite.h"
#include <tinyxml2.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>


class UI 
	: public Object
{
protected:
	const std::string DEFAULT_TEXT = "null";

public:
	struct Entry {
		std::string p_ID;
		std::string p_Text;

		Entry() { p_ID = "not set"; p_Text = ""; }
		Entry(std::string id, std::string text) : p_ID(id), p_Text(text) {}
	};

	enum UIAnchor {
		TOP_FULL,
		TOP_LEFT,
		TOP_CENTRE,
		TOP_RIGHT,
		CENTRE_FULL,
		CENTRE_LEFT,
		CENTRE,
		CENTRE_RIGHT,
		BOTTOM_FULL,
		BOTTOM_LEFT,
		BOTTOM_CENTRE,
		BOTTOM_RIGHT,
		FULL,
		NONE = -1
	};

	enum BackgroundStyle {
		NINE_SLICE,
		THREE_SLICE,
		UNKNOWN = -1
	};

protected:
	Text* m_Text;
	TiledSprite* m_Background;
	std::string m_DataPath;
	gmtl::Vec2i m_Dimensions;
	UIAnchor m_Anchor = NONE;
	BackgroundStyle m_BackgroundStyle;

	bool m_Shown;


	std::vector<Entry*> m_TextEntries;

	void parseAnchor();
	void posUpdate();
	void load();
	UI();

	tinyxml2::XMLError loadXML();

	Entry* findEntryByID(const std::string& id);

public:
	UI(UIAnchor anchor, const std::string& path);

	~UI();

	virtual void handleInput(const SDL_Event& event);
	virtual void step() override;
	virtual void draw();
	void addEntry(Entry entry);

	void setEntry(int id);
	void setEntry(const std::string& id);

	void show();
	void hide();

	inline Text* getText() const { return m_Text; }
};

