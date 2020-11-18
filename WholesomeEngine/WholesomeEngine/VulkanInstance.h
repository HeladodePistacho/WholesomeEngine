#ifndef _VULKAN_INSTANCE_H_
#define _VULKAN_INSTANCE_H_

#include <memory>
#include "Globals.h"
#include <vector>
#include "vulkan/vulkan.hpp"

class VulkanInstance
{
private:
	std::unique_ptr<VkInstance> instance;
	std::vector<VkPhysicalDevice> gpus;
	VkPhysicalDevice current_gpu;

	void PrintDeviceInformation(const VkPhysicalDevice& device) const;
public:
	VulkanInstance();
	VulkanInstance(const VulkanInstance&) = delete;
	
	//Instance functions
	VkResult CreateInstance();
	void DestroyInstance();
	VkInstance& GetInstance() const;

	//Devices
	VkResult SelectPhysicalDevice();
	void PrintDeviceInformation(uint index) const;
};

#endif
