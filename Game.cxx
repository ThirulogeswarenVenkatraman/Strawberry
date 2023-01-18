#include "Game.h"

#include "TextureManager.h"
#include "InputHandler.h"

extern int window_size_x;
extern int window_size_y;

int main(int argc, char* argv[]) {
	Game::getInstance()->RunTheGame();
	return 0;
}

Game* Game::getInstance() {	
	static Game GameInst(window_size_x, window_size_y);
	return &GameInst;
}

Game::Game(const int win_pos_x, const int win_pos_y) : state{ false } {
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "%s", SDL_GetError());
		exit(-1);
	}
	window = SDL_CreateWindow("strad", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, win_pos_x, win_pos_y, 0);

	if (!window) {
		fprintf(stderr, "%s", SDL_GetError());
		exit(-1);
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer) {
		fprintf(stderr, "%s", SDL_GetError());
		exit(-1);
	}

	/* if everything went ok */
	this->state = true;
}

Game::~Game() {
	this->FreeResrc();
	if (renderer != NULL) {
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}
	if (window != NULL) {
		SDL_DestroyWindow(window);
		window = NULL;
	}
	SDL_Quit();
	fprintf(stdout, "subsystems cleaned up!\n");
}

void Game::RunTheGame() {
	fprintf(stdout, "RefreshRate: %d\n", getRefreshRate());
	fprintf(stdout, "sec_per_update = %f\n", (1.0f / (float)getRefreshRate()));
	static const float FixedDeltaTime = 1.0f / (float)getRefreshRate();
	float previousTime = 0.0f;
	float lag = 0.0f;
	float max = 0.0f;
	this->Start();
	while (this->isRunnning())
	{
		float DeltaTime = (SDL_GetTicks() / 1000.0f) - previousTime;
		previousTime = (SDL_GetTicks() / 1000.0f);
		lag += DeltaTime;
		InputHandler::getInstance()->EventUpdater();
		while (lag >= FixedDeltaTime)
		{
			if (InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
				this->setState(false);
			}
			this->Update(FixedDeltaTime);
			lag -= FixedDeltaTime;
		}
		SDL_RenderClear(renderer);
		this->Render();
		SDL_RenderPresent(renderer);
	}
}

int Game::getRefreshRate() {
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);
	return mode.refresh_rate;
}

SDL_Renderer* Game::getRenderer()
{
	return this->renderer;
}

bool Game::isRunnning()
{
	return this->state;
}

void Game::setState(bool state)
{
	this->state = state;
}
