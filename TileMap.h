#ifndef _TILEMAP__H
#define _TILEMAP__H

#include "SDL2/SDL.h"
#include <string>
#include <vector>
#include <map>

class TileMap {
	int MAP_SIZE;
	struct MapSize {
		int x, y;
		int mWidth, mHeight;
	};
	struct source_from {
		std::string tileset_id;
		SDL_Rect src_rects;
	};
	MapSize m_size;
	size_t no_of_layers;
	std::vector<int> m_gid;
	/* contains id and src rectangle */
	std::map<int, source_from> t_source;
	std::vector<SDL_Rect> t_destination;
	
	void load_map(const char* fname);
	void calculate_destination_rects();
public:
	TileMap(std::string filename);
	~TileMap();
	
	void SetMapSize(int map_size) { MAP_SIZE = map_size; }
	void draw_map();
};

#endif