#ifndef _MODULE_RENDER_H_
#define _MODULE_RENDER_H_

#include "Module.h"
#include "EventThrower.h"
#include "VulkanInstance.h"
#include "WholesomeEvent.h"

class VulkanLogicalDevice;

struct WESurfaceCreation;

class ModuleRender : public Module, public EventThrower<WESurfaceCreation>
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
