#include "ModuleWindow.h"
#include "EventManager.h"
#include "WholesomeEvent.h"


ModuleWindow::ModuleWindow() : window(nullptr, SDL_DestroyWindow)
{
	//subscription_to_events = W_EVENT_TYPE::WE_SURFACE_CREATION | W_EVENT_TYPE::WE_TEST;
}

ModuleWindow::~ModuleWindow()
{
}

ENGINE_STATUS ModuleWindow::Init()
{
	ENGINE_STATUS ret = ENGINE_STATUS::SUCCESS;
	std::string_view name{ "Wholesome Engine" };

	//Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		DEBUG::LOG("[ERROR] Could not Init SDL % ", SDL_GetError());
		return ENGINE_STATUS::FAIL;
	}
	DEBUG::LOG("[SUCCESS] SDL Init Successfully", nullptr);

	//Create Window
	window.reset(SDL_CreateWindow(name.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_VULKAN));

	if (window == nullptr)
	{
		DEBUG::LOG("[ERROR] Could not Create Window % ", SDL_GetError());
		return ENGINE_STATUS::FAIL;
	}
	DEBUG::LOG("[SUCCESS] SDL Window Created Successfully", nullptr);

	

	return ret;
}

ENGINE_STATUS ModuleWindow::CleanUp()
{
	DEBUG::LOG("...Cleaning Window...", nullptr);
	window.reset(nullptr);
	SDL_Quit();
	return ENGINE_STATUS::SUCCESS;
}


