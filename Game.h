#ifndef _Game__H
#define _Game__H

#include "SDL2/SDL.h"

class Game
{
	bool state;
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool isRunnning();
	int getRefreshRate();

	Game(const int win_pos_x, const int win_pos_y);
	~Game();
	
	void Start();
	void Update(float dt);
	void Render();
	void FreeResrc();

public:

	SDL_Renderer* getRenderer();
	static Game* getInstance();
	
	void setState(bool state);
	void RunTheGame();
};

#endif 
