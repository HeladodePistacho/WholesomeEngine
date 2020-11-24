#ifndef _MODULE_RENDER_H_
#define _MODULE_RENDER_H_

#include "Module.h"
#include "VulkanInstance.h"

class VulkanLogicalDevice;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	ENGINE_STATUS Init();
	ENGINE_STATUS CleanUp();

private:
	VulkanInstance vulkan_instance;
	std::unique_ptr<VulkanLogicalDevice> vulkan_logic_device;
};

#endif
