#ifndef _WHOLESOME_EVENT_H_
#define _WHOLESOME_EVENT_H_

#include "SDL2/SDL.h"
#include "vulkan/vulkan.hpp"

struct WEWindowCreation
{
	WEWindowCreation(const SDL_Window& win) : sdl_window(&win) {}
	~WEWindowCreation() { sdl_window = nullptr; }
	const SDL_Window* sdl_window ) nullptr;
};

#endif // !_WHOLESOME_EVENT_H_

