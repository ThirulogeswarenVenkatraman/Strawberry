#include "TileMap.h"
#include "TextureManager.h"
#include <tinyxml2.h>

using namespace tinyxml2;

TileMap::TileMap(std::string filename)
{
	this->load_map(filename.c_str());
}

TileMap::~TileMap()
{
	m_gid.clear();
	t_source.clear();
	t_destination.clear();
}

void TileMap::draw_map()
{
	static int gid_counter{ 0 };
	static size_t i, l;
	for (i = { 0 }, l = { 0 }; i < ((m_size.x * m_size.y) * no_of_layers); i++, l++, gid_counter++) {
		if (l >= m_size.x * m_size.y) { l = 0; }
		TextureManager::getInstance()->DrawTile(t_source[m_gid[gid_counter]].tileset_id,
			&t_source[m_gid[gid_counter]].src_rects,
			&t_destination[l]);
	}
	gid_counter = { 0 };
}

void TileMap::load_map(const char* fname)
{
	XMLDocument doc;
	XMLError errn = doc.LoadFile(fname);
	if (errn != XML_SUCCESS) {
		doc.PrintError();
		return;
	}

	XMLElement* mNode = doc.FirstChildElement("map");

	mNode->QueryIntAttribute("width", &m_size.x);
	mNode->QueryIntAttribute("height", &m_size.y);
	mNode->QueryIntAttribute("tilewidth", &m_size.mWidth);
	mNode->QueryIntAttribute("tileheight", &m_size.mHeight);

	calculate_destination_rects();
	XMLElement* mTileset = mNode->FirstChildElement("tileset");
	if (mTileset != nullptr) {
		while (mTileset) {
			static int i;
			std::string tileset_id(mTileset->Attribute("name"));
			std::string srcname(mTileset->FirstChildElement("image")->Attribute("source"));
			std::string fullpath("assets/");
			fullpath.append(srcname);
			int tilewidth{ 0 }, tileheight{ 0 }, tileCount{ 0 };
			int w_size{ 0 }, h_size{ 0 };
			TextureManager::getInstance()->Load(fullpath, tileset_id);
			/* getting specific tileset properties */
			mTileset->QueryIntAttribute("tilewidth", &tilewidth);
			mTileset->QueryIntAttribute("tileheight", &tileheight);
			mTileset->QueryIntAttribute("tilecount", &tileCount);
			mTileset->FirstChildElement("image")->QueryIntAttribute("width", &w_size);
			mTileset->FirstChildElement("image")->QueryIntAttribute("height", &h_size);

			SDL_Rect temp_src{ 0, 0, 0, 0 };
			for (int t { 0 }; t < tileCount; t++, i++) {
				temp_src.x = (t * tilewidth) % w_size;
				temp_src.w = tilewidth;
				temp_src.h = tileheight;

				t_source[i + 1].tileset_id = tileset_id;
				t_source[i + 1].src_rects = temp_src;
				if (temp_src.x == (w_size - tilewidth)) {
					temp_src.y += tileheight;
				}

			}
			mTileset = mTileset->NextSiblingElement("tileset");
		}
	}
	size_t nfL{ 0 }; int temp_gid{ 0 };
	XMLElement* mLayer = mNode->FirstChildElement("layer");
	if (mLayer != nullptr) {
		while (mLayer) {
			XMLElement* mData = mLayer->FirstChildElement("data");
			if (mData != nullptr) {
				while (mData) {
					XMLElement* mTile = mData->FirstChildElement("tile");
					if (mTile != nullptr) {
						while (mTile) {
							if (mTile->IntAttribute("gid") == 0) {
								m_gid.push_back(0);
							}
							else {
								mTile->QueryIntAttribute("gid", &temp_gid);
								m_gid.push_back(temp_gid);
							}

							/* next tile node */
							mTile = mTile->NextSiblingElement("tile");
						}
					}
					mData = mData->NextSiblingElement("data");
				}
			}
			nfL++;
			this->no_of_layers = nfL;
			mLayer = mLayer->NextSiblingElement("layer");
		}
	}
}

void TileMap::calculate_destination_rects()
{
	SDL_Rect temp_dst_rect;
	for (int yy{ 0 }; yy < m_size.y; yy++) {
		for (int xx{ 0 }; xx < m_size.x; xx++) {
			temp_dst_rect.x = xx * m_size.mWidth * MAP_SIZE;
			temp_dst_rect.y = yy * m_size.mHeight * MAP_SIZE;
			temp_dst_rect.w = m_size.mWidth * MAP_SIZE;
			temp_dst_rect.h = m_size.mHeight * MAP_SIZE;
			
			this->t_destination.push_back(temp_dst_rect);
		}
	}
}
