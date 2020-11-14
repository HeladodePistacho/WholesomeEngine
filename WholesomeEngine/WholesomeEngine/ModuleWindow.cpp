#include "ModuleWindow.h"



ModuleWindow::ModuleWindow() : window(nullptr, SDL_DestroyWindow)
{
}


ModuleWindow::~ModuleWindow()
{
}

ENGINE_STATUS ModuleWindow::Init()
{
	ENGINE_STATUS ret = ENGINE_STATUS::SUCCESS;
	std::string_view name{ "Wholesome Engine" };

	//Create Window
	window.reset(SDL_CreateWindow(name.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_VULKAN));

	if (window == nullptr)
	{
		DEBUG::LOG("[ERROR] Could not Create Window", nullptr);
		return ENGINE_STATUS::FAIL;
	}

	return ret;
}

ENGINE_STATUS ModuleWindow::CleanUp()
{
	DEBUG::LOG("...Cleaning Window...", nullptr);
	window.reset(nullptr);
	SDL_Quit();
	return ENGINE_STATUS::SUCCESS;
}


