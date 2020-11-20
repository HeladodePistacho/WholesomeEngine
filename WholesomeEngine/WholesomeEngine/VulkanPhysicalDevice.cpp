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

VulkanPhysicalDevice& VulkanPhysicalDevice::operator=(const VulkanPhysicalDevice& device)
{
	physical_device = device.physical_device;

	for (const auto& family : device.queue_properties)
	{
		queue_properties.push_back(family);
	}

	return *this;
}

const VkPhysicalDevice& VulkanPhysicalDevice::GetPhysicalDevice() const
{
	return physical_device;
}

bool VulkanPhysicalDevice::IsValid() const
{
	return valid_family_index.has_value();
}

void VulkanPhysicalDevice::PrintInformation() const
{
	VkPhysicalDeviceProperties device_properties;
	vkGetPhysicalDeviceProperties(physical_device, &device_properties);

	DEBUG::LOG("Device: %", device_properties.deviceName);
	DEBUG::LOG("\t ID: %", device_properties.deviceID);

	switch (device_properties.deviceType)
	{
	case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_CPU:
		DEBUG::LOG("\t TYPE: CPU", nullptr);
		break;
	case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
		DEBUG::LOG("\t TYPE: DISCRETE GPU", nullptr);
		break;
	case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
		DEBUG::LOG("\t TYPE: INTEGRATED GPU", nullptr);
		break;
	case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
		DEBUG::LOG("\t TYPE: VIRTUAL GPU", nullptr);
		break;
	case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_OTHER:
		DEBUG::LOG("\t TYPE: UNKNOWN TYPE", nullptr);
		break;
	}
}

VkResult VulkanPhysicalDevice::InitDevice()
{
	VkResult ret = VkResult::VK_SUCCESS;

	if (physical_device == VK_NULL_HANDLE)
		return ret;

	//Look for family queues available
	uint32 family_count;
	vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &family_count, nullptr);

	//Get Family Queues
	std::vector<VkQueueFamilyProperties> properties(family_count);
	vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &family_count, properties.data());

	queue_properties = properties;
	
	uint32 i = 0;
	for (const auto& property : queue_properties)
	{
		//Select One Family that has this flag enabled
		if (property.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			valid_family_index = i;
			break;
		}

		++i;
	}

	return ret;
}
