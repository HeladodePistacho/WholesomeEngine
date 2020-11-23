#include "ModuleRender.h"
#include "VulkanLogicalDevice.h"
#include <SDL2/SDL_vulkan.h>

ModuleRender::ModuleRender() : logic_device(std::make_unique<VulkanLogicalDevice>())
{
}


ModuleRender::~ModuleRender()
{
}

ENGINE_STATUS ModuleRender::Init()
{
	ENGINE_STATUS ret = ENGINE_STATUS::SUCCESS;
	VkResult result = VkResult::VK_SUCCESS;
	
	if (result = vulkan_instance.CreateInstance(); result == VK_ERROR_INCOMPATIBLE_DRIVER)
	{
		DEBUG::LOG("[ERROR] Creating Vulkan Instance Failure: COMPATIBLE DRIVER NOT FOUND", nullptr);
		ret =  ENGINE_STATUS::FAIL;
	}
	else if (result != VkResult::VK_SUCCESS)
	{
		//Vicente for the win
		DEBUG::LOG("[ERROR] Creating Vulkan Instance Failure: unknown error", nullptr);
		ret = ENGINE_STATUS::FAIL;
	}
	DEBUG::LOG("[SUCCESS] Creating Vulkan Instance Success", nullptr);

	if (result = vulkan_instance.SelectPhysicalDevice(); result != VK_SUCCESS)
	{
		DEBUG::LOG("[ERROR] Selecting Physical Device Failure", nullptr);
		ret = ENGINE_STATUS::FAIL;
	}

	if (result = vulkan_logic_device->InitDevice(vulkan_instance); result != VK_SUCCESS)
	{
		DEBUG::LOG("[ERROR] Creating Logical Device Failure", nullptr);
		ret = ENGINE_STATUS::FAIL;
	}

	return ret;
}

ENGINE_STATUS ModuleRender::CleanUp()
{
	DEBUG::LOG("...Cleaning Render...", nullptr);

	vulkan_instance.DestroyInstance();
	vulkan_logic_device->DestroyDevice();

	return ENGINE_STATUS::SUCCESS;
}
