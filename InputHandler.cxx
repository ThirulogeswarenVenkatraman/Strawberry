#include "InputHandler.h"

#include "Game.h" /* for setting the state */

InputHandler* InputHandler::getInstance()
{
	static InputHandler s_InputHandlerInst; // stack
	return &s_InputHandlerInst;
}

InputHandler::InputHandler()
{
	keyStates = 0;
	for (int i = 0; i < 3; i++)
	{
		mouseStates.push_back(false);
	}
}

InputHandler::~InputHandler() {
	fprintf(stdout, "Destroyed InputHandler\n");
}

bool InputHandler::getMouseButtonState(int buttton)
{
	return mouseStates[buttton];
}

void InputHandler::EventUpdater()
{
	static SDL_Event evnt;
	while(SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case SDL_QUIT: {
				Game::getInstance()->setState(false);
				break;
			}
			case SDL_MOUSEBUTTONDOWN: {
				MouseButtonDown(evnt);
				break;
			}
			case SDL_MOUSEBUTTONUP: {
				MouseButtonUp(evnt);
				break;
			}
			case SDL_KEYDOWN: {
				keyStates = SDL_GetKeyboardState(0);
				break;
			}
			case SDL_KEYUP: {
				keyStates = SDL_GetKeyboardState(0);
				break;
			}
			default: {
				break;
			}
		}
	}
	
}


void InputHandler::MouseButtonDown(SDL_Event& q_event)
{
	if (q_event.button.button == SDL_BUTTON_LEFT)
	{
		mouseStates[LEFT] = true;
	}
	if (q_event.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseStates[MIDDLE] = true;
	}
	if (q_event.button.button == SDL_BUTTON_RIGHT)
	{
		mouseStates[RIGHT] = true;
	}
}

void InputHandler::MouseButtonUp(SDL_Event& q_event)
{
	if (q_event.button.button == SDL_BUTTON_LEFT)
	{
		mouseStates[LEFT] = false;
	}
	if (q_event.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseStates[MIDDLE] = false;
	}
	if (q_event.button.button == SDL_BUTTON_RIGHT)
	{
		mouseStates[RIGHT] = false;
	}
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (keyStates != 0)
	{
		if (keyStates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool InputHandler::isKeyUp(SDL_Scancode key)
{
	if (keyStates != 0)
	{
		if (keyStates[key] == 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	return true;
}

