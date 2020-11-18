#include "ModuleRender.h"
#include <SDL2/SDL_vulkan.h>



ModuleRender::ModuleRender()
{
}


ModuleRender::~ModuleRender()
{
}

ENGINE_STATUS ModuleRender::Init()
{
	ENGINE_STATUS ret = ENGINE_STATUS::SUCCESS;
	
	
	if (auto result = vulkan_instance.CreateInstance(); result == VK_ERROR_INCOMPATIBLE_DRIVER)
	{
		DEBUG::LOG("[ERROR] Creating Vulkan Instance Failure: COMPATIBLE DRIVER NOT FOUND", nullptr);
		ret =  ENGINE_STATUS::FAIL;
	}
	else if (result)
	{
		//Vicente for the win
		DEBUG::LOG("[ERROR] Creating Vulkan Instance Failure: unknown error", nullptr);
		ret = ENGINE_STATUS::FAIL;
	}
	DEBUG::LOG("[SUCCESS] Creating Vulkan Instance Success", nullptr);

	vulkan_instance.SelectPhysicalDevice();

	return ret;
}

ENGINE_STATUS ModuleRender::CleanUp()
{
	DEBUG::LOG("...Cleaning Render...", nullptr);
	vulkan_instance.DestroyInstance();

	return ENGINE_STATUS::SUCCESS;
}
