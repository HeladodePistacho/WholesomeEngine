#ifndef _MODULE_WINDOW_H_
#define _MODULE_WINDOW_H_

#include "Module.h"
#include "EventThrower.h"
#include <memory>
#include <SDL2/SDL.h>
#include "vulkan/vulkan.hpp"

struct WESurfaceCreation;

class ModuleWindow : public Module, public EventThrower<WEWindowCreation>
{
public:
	ModuleWindow();
	~ModuleWindow();

	ENGINE_STATUS Init();
	ENGINE_STATUS CleanUp();


private:
	uint16 width{1280};
	uint16 height{720};

	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
};

#endif
