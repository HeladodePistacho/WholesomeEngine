#ifndef _MODULE_RENDER_H_
#define _MODULE_RENDER_H_

#include "Module.h"
#include "EventListener.h"
#include "VulkanInstance.h"
#include "WholesomeEvent.h"

class VulkanLogicalDevice;

class ModuleRender : public Module, public EventListener<WEWindowCreation>
{
public:
	ModuleRender();
	~ModuleRender();

	ENGINE_STATUS Init();
	ENGINE_STATUS CleanUp();

	void OnEventRecieved(const WEWindowCreation& event_recieved) override;
private:
	VulkanInstance vulkan_instance;
	std::unique_ptr<VulkanLogicalDevice> vulkan_logic_device;
	VkSurfaceKHR vulkan_surface;
};


#endif
