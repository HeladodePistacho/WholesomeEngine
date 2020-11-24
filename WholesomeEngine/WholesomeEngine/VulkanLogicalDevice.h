#ifndef _VULKAN_LOGICAL_DEVICE_H_
#define _VULKAN_LOGICAL_DEVICE_H_

#include <memory>
#include "Globals.h"
#include <vulkan/vulkan.hpp>

class VulkanInstance;

class VulkanLogicalDevice
{
public:
	VulkanLogicalDevice();
	~VulkanLogicalDevice();

	VkResult InitDevice(const VulkanInstance& vulkan_instance);
	void DestroyDevice();

	const VkDevice& GetDevice() const;
private:
	VkDevice logic_device;

	//The queue is created with the logic device but we need the handle to interact with it
	VkQueue	 queue_handle;
};

#endif

