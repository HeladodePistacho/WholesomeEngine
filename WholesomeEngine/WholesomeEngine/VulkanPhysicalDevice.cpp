#include "VulkanPhysicalDevice.h"
#include <assert.h>


VulkanPhysicalDevice::VulkanPhysicalDevice() : physical_device(VK_NULL_HANDLE)
{
}

VulkanPhysicalDevice::VulkanPhysicalDevice(const VkPhysicalDevice& device) : physical_device(device)
{

}

VulkanPhysicalDevice::VulkanPhysicalDevice(const VulkanPhysicalDevice& device) : physical_device(device.physical_device), queue_properties(device.queue_properties), valid_family_index(device.valid_family_index)
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

	valid_family_index = device.valid_family_index;

	return *this;
}

const VkPhysicalDevice& VulkanPhysicalDevice::PhysicalDevice() const
{
	return physical_device;
}

bool VulkanPhysicalDevice::IsValid() const
{
	return valid_family_index.has_value();
}

uint32 VulkanPhysicalDevice::GetFamilyIndex() const
{
	assert(valid_family_index.has_value() == true, "No Index Family for this Device");
	return valid_family_index.value();
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

	if (family_count == 0)
	{
		DEBUG::LOG("[ERROR] Physical device no queue families found", nullptr);
		ret = VkResult::VK_ERROR_UNKNOWN;
		return ret;
	}

	//Get Family Queues
	queue_properties = std::vector<VkQueueFamilyProperties>(family_count);
	vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &family_count, queue_properties.data());
	
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
