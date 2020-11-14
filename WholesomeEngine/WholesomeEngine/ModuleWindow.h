#ifndef _MODULE_WINDOW_H_
#define _MODULE_WINDOW_H_

#include "Module.h"
#include <memory>

class SDL_Window;
class ModuleWindow : public Module
{
public:
	ModuleWindow();
	~ModuleWindow();

	ENGINE_STATUS Init();
private:
	uint width{1280};
	uint height{720};

	std::unique_ptr<SDL_Window> window;
};

#endif
