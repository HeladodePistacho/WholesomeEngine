#ifndef _WHOLESOME_EVENT_H_
#define _WHOLESOME_EVENT_H_

#include "SDL2/SDL.h"
#include "vulkan/vulkan.hpp"

struct WESurfaceCreation
{
	WESurfaceCreation(const SDL_Window& win) : sdl_window(&win) {}
	~WESurfaceCreation() { sdl_window = nullptr; }
	const SDL_Window* sdl_window;
};

#endif // !_WHOLESOME_EVENT_H_

