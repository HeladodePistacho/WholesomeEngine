#include "ModuleWindow.h"
#include "WholesomeEvent.h"
#include <SDL2/SDL_vulkan.h>


ModuleWindow::ModuleWindow() : Module(), window(nullptr, SDL_DestroyWindow)
{
	DEBUG::LOG("CREATING MODULE WINDOW", nullptr);
	
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

void ModuleWindow::OnEventRecieved(const WESurfaceCreation& event_recieved)
{
	if (SDL_Vulkan_CreateSurface(window.get(), event_recieved.vulkan_instance, &c_surface) != SDL_TRUE)
	{
		DEBUG::LOG("[ERROR] VULKAN SURFACE CREATION FAILURE: %", SDL_GetError());
	}
	else DEBUG::LOG("[SUCCESS] SDL_Vulkan_CreateSurface successfully", nullptr);
	
	
}


