#ifndef _VULKAN_PHYSICAL_DEVICE_H_
#define _VULKAN_PHYSICAL_DEVICE_H_

#include "Globals.h"
#include "vulkan/vulkan.hpp"
#include <vector>
#include <optional>

class VulkanPhysicalDevice
{
public:
	VulkanPhysicalDevice();
	VulkanPhysicalDevice(const VkPhysicalDevice& device);
	~VulkanPhysicalDevice();

	VulkanPhysicalDevice& operator=(const VkPhysicalDevice& device);
	VulkanPhysicalDevice& operator=(const VulkanPhysicalDevice& device);

	const VkPhysicalDevice& GetPhysicalDevice() const;
	VkResult InitDevice();
	bool IsValid() const;

	void PrintInformation() const;
private:
	VkPhysicalDevice physical_device;
	std::vector<VkQueueFamilyProperties> queue_properties;

	//Temporary check for device validation
	std::optional<uint32> valid_family_index;
};

#endif // !

