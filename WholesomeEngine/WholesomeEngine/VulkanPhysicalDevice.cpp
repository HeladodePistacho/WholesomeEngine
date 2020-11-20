#include "VulkanPhysicalDevice.h"



VulkanPhysicalDevice::VulkanPhysicalDevice() : physical_device(VK_NULL_HANDLE)
{
}

VulkanPhysicalDevice::VulkanPhysicalDevice(const VkPhysicalDevice& device) : physical_device(device)
{
}


VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
}

VulkanPhysicalDevice& VulkanPhysicalDevice::operator=(const VkPhysicalDevice& device)
{
	physical_device = device;
	return *this;
}

const VkPhysicalDevice & VulkanPhysicalDevice::GetPhysicalDevice() const
{
	return physical_device;
}

VkResult VulkanPhysicalDevice::InitDevice(const VkInstance& instance)
{
	VkResult ret = VkResult::VK_SUCCESS;



	return ret;
}
