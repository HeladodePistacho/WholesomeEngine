#include "ModuleRender.h"
#include <SDL2/SDL_vulkan.h>



ModuleRender::ModuleRender() : vulkan_instance(std::make_unique<VkInstance>())
{
}


ModuleRender::~ModuleRender()
{
}

ENGINE_STATUS ModuleRender::Init()
{
	ENGINE_STATUS ret = ENGINE_STATUS::SUCCESS;

	VkApplicationInfo application_info{
		VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO, //StructureType
		nullptr,											 //Next pointer
		"Wholesome Engine",									 //Application Name
		0,													 //Application Version
		"Wholesome Engine",									 //Engine Name
		0,													 //Engine Version
		VK_API_VERSION_1_2									 //Vulkan Api Version
	};

	VkInstanceCreateInfo instance_info{
		VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, //StructureType
		nullptr,												 //Next pointer
		0,														 //Flags
		&application_info,										 //Application info pointer
		0,														 //Layer Count		 ]
		nullptr,												 //Layer Names       ]---->Not using Layers nor extensions de momento                 
		0,														 //Extension Count	 ]
		nullptr													 //Extension Names   ]
	};
	
	if (auto result = vkCreateInstance(&instance_info, nullptr, vulkan_instance.get()); result == VK_ERROR_INCOMPATIBLE_DRIVER)
	{
		DEBUG::LOG("[ERROR] Creating Vulkan Instance Failure: COMPATIBLE DRIVER NOT FOUND", nullptr);
		ret =  ENGINE_STATUS::FAIL;
	}
	else if (result)
	{
		DEBUG::LOG("[ERROR] Creating Vulkan Instance Failure: unknown error", nullptr);
		ret = ENGINE_STATUS::FAIL;
	}
	

	return ret;
}

ENGINE_STATUS ModuleRender::CleanUp()
{
	DEBUG::LOG("...Cleaning Render...", nullptr);
	vkDestroyInstance(*vulkan_instance, nullptr);

	return ENGINE_STATUS::SUCCESS;
}
