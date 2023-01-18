#ifndef _INPUT_HANDLER__H
#define _INPUT_HANDLER__H

#include "SDL2/SDL.h"
#include <vector>

enum mouseButtons {
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
	InputHandler();
	void MouseButtonDown(SDL_Event& q_event);
	void MouseButtonUp(SDL_Event& q_event);

	const Uint8* keyStates;
	std::vector<bool> mouseStates;
public:
	~InputHandler();
	static InputHandler* getInstance();
	void EventUpdater();

	bool getMouseButtonState(int button);
	bool isKeyDown(SDL_Scancode key);
	bool isKeyUp(SDL_Scancode key);

};

#endif
