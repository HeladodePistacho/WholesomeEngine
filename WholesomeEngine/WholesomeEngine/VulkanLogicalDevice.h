#ifndef _VULKAN_LOGICAL_DEVICE_H_
#define _VULKAN_LOGICAL_DEVICE_H_

#include <memory>
#include <vulkan/vulkan.hpp>

class VulkanLogicalDevice
{
public:
	VulkanLogicalDevice();
	~VulkanLogicalDevice();

private:
	std::unique_ptr<VkDevice> logic_device;
};

#endif

