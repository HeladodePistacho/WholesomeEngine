#ifndef _VULKAN_INSTANCE_H_
#define _VULKAN_INSTANCE_H_

#include <memory>
#include "VulkanPhysicalDevice.h"

class SDL_Window;

class VulkanInstance
{
private:
	std::unique_ptr<VkInstance> instance;
	std::vector<VulkanPhysicalDevice> gpus;
	VulkanPhysicalDevice current_gpu;

public:
	VulkanInstance();
	VulkanInstance(const VulkanInstance&) = delete;
	
	//Instance functions
	VkResult CreateInstance(const SDL_Window*);
	void DestroyInstance();
	VkInstance GetInstance() const;

	//Devices
	VkResult GetPhysicalDevices();
	VkResult SelectPhysicalDevice(VkSurfaceKHR);
	void PrintDeviceInformation(uint8 index) const;
	const VulkanPhysicalDevice& GetPhysicalDevice() const;
};

#endif
