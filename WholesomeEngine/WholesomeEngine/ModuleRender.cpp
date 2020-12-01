#include "ModuleRender.h"
#include "VulkanLogicalDevice.h"
#include <SDL2/SDL_vulkan.h>

ModuleRender::ModuleRender() : Module(), vulkan_logic_device(std::make_unique<VulkanLogicalDevice>())
{
	DEBUG::LOG("CREATING MODULE RENDER", nullptr);
}


ModuleRender::~ModuleRender()
{
}

ENGINE_STATUS ModuleRender::Init()
{
	ENGINE_STATUS ret = ENGINE_STATUS::SUCCESS;
	VkResult result = VkResult::VK_SUCCESS;
	
	//Create Vulkan Instance
	if (event_recieved.has_value())
	{
		if (result = vulkan_instance.CreateInstance(event_recieved.value().sdl_window); result == VK_ERROR_INCOMPATIBLE_DRIVER)
		{
			DEBUG::LOG("[ERROR] Creating Vulkan Instance Failure: COMPATIBLE DRIVER NOT FOUND", nullptr);
			ret = ENGINE_STATUS::FAIL;
		}
		else if (result != VkResult::VK_SUCCESS)
		{
			//Vicente ftw
			DEBUG::LOG("[ERROR] Creating Vulkan Instance Failure: unknown error", nullptr);
			ret = ENGINE_STATUS::FAIL;
		}
	}
	DEBUG::LOG("[SUCCESS] Creating Vulkan Instance Success", nullptr);

	//Optional event will have value if we have recieved the Surface creation event
	if (event_recieved.has_value())
	{
		//Create Vulkan Surface Instance
		if (SDL_Vulkan_CreateSurface(const_cast<SDL_Window*>(event_recieved.value().sdl_window), vulkan_instance.GetInstance(), &vulkan_surface) != SDL_TRUE)
		{
			DEBUG::LOG("[ERROR] VULKAN SURFACE CREATION FAILURE: %", SDL_GetError());
		}
		else DEBUG::LOG("[SUCCESS] SDL_Vulkan_CreateSurface successfully", nullptr);
	}

	//Init Physical Devices
	if (result = vulkan_instance.GetPhysicalDevices(); result != VK_SUCCESS)
	{
		DEBUG::LOG("[ERROR] Getting Physical Device Failure", nullptr);
		ret = ENGINE_STATUS::FAIL;
	}

	//Select physiscal Device
	if (result = vulkan_instance.SelectPhysicalDevice(vulkan_surface); result != VK_SUCCESS)
	{
		DEBUG::LOG("[ERROR] Selecting Physical Device Failure", nullptr);
		ret = ENGINE_STATUS::FAIL;
	}

	//Create Logical Device
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

	//Destroy Surface
	vkDestroySurfaceKHR(vulkan_instance.GetInstance(), vulkan_surface, nullptr);

	//Destroy device
	vulkan_logic_device->DestroyDevice();

	//Destroy instance
	vulkan_instance.DestroyInstance();
	 
	

	return ENGINE_STATUS::SUCCESS;
}

void ModuleRender::OnEventRecieved(const WESurfaceCreation& event_recieved)
{
	//As I'm not gonna use the info of this event right now I store it
	this->event_recieved = event_recieved;
}
