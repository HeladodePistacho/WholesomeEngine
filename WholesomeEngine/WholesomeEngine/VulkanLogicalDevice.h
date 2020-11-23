#ifndef _VULKAN_LOGICAL_DEVICE_H_
#define _VULKAN_LOGICAL_DEVICE_H_

#include <memory>
#include <vulkan/vulkan.hpp>

class VulkanInstance;
class VulkanLogicalDevice
{
public:
	VulkanLogicalDevice();
	~VulkanLogicalDevice();

	VkResult InitDevice(const VulkanInstance& vulkan_instance);
	const VkDevice& GetDevice() const;
private:
	std::unique_ptr<VkDevice> logic_device;
};

#endif

