#ifndef TIMER_H
#define TIMER_H
#include "SDL2/SDL_timer.h"

namespace strad {
	class Timer {
		bool started;
		bool paused;

		Uint32 startTicks;
		Uint32 pausedTicks;
	public:
		Uint32 getTicks() {
			static Uint32 in_time{ 0 };
			if (started) {
				if (paused) {
					in_time = pausedTicks;
				}
				else {
					in_time = SDL_GetTicks() - startTicks;
				}
			}
			return in_time;
		}
		Timer() :started{ false }, paused{ false }, startTicks{ 0 }, pausedTicks{ 0 } {}

		bool isStarted() { return this->started; }
		bool isPaused() { return (this->started && this->paused); }

		void start() {
			this->started = true;
			this->paused = false;
			this->startTicks = SDL_GetTicks();
			this->pausedTicks = 0;
		}

		void stop() { // reset
			this->started = false;
			this->paused = false;
			this->startTicks = 0;
			this->pausedTicks = 0;
		}

		void pause() {
			if (started && !paused) {
				this->paused = true;
				this->pausedTicks = SDL_GetTicks() - startTicks;
				this->startTicks = 0;
			}
		}

		void unpause() {
			if (started && paused) {
				this->paused = false;
				this->startTicks = SDL_GetTicks() - pausedTicks;
				this->pausedTicks = 0;
			}
		}

	};
}

#endif