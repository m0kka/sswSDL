#pragma once
#include "Sprite.h"
#include <tinyxml2.h>
#include <stdio.h>

class TiledSprite :
	public Sprite
{
public:
	struct Tile {
		SDL_Rect* p_Clip;
		int p_ID;
		Tile() : p_Clip(nullptr), p_ID(-1) {}
		Tile(SDL_Rect* clip, int id) : p_Clip(clip), p_ID(id) {}
	};

protected:

	std::string m_XMLPath;
	std::vector<Tile*> m_Tiles;

	void init() override;
	void load();
	tinyxml2::XMLError loadXML();
	TiledSprite();
	Tile* findTileByID(int id);
	void setTileVector(int at);

public:
	TiledSprite(const std::string& XMLpath);

	void setTile(int id);
	int getAmountTiles() { return m_Tiles.size(); }

	~TiledSprite();
};

