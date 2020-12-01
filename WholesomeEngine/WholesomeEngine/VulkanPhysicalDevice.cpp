#include "VulkanPhysicalDevice.h"
#include <assert.h>
#include <array>

VulkanPhysicalDevice::VulkanPhysicalDevice() : physical_device(VK_NULL_HANDLE)
{
}

VulkanPhysicalDevice::VulkanPhysicalDevice(const VkPhysicalDevice& device) : physical_device(device)
{

}

VulkanPhysicalDevice::VulkanPhysicalDevice(const VulkanPhysicalDevice& device) : physical_device(device.physical_device), queue_properties(device.queue_properties), family_index(device.family_index)
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

	family_index = device.family_index;

	return *this;
}

VkPhysicalDevice VulkanPhysicalDevice::PhysicalDevice() const
{
	return physical_device;
}

bool VulkanPhysicalDevice::IsValid() const
{
	return family_index.IsValid() && CheckDeviceExtensions();
}

bool VulkanPhysicalDevice::CheckDeviceExtensions() const
{
	uint32 extension_count{};
	vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extension_count, nullptr);

	if (extension_count == 0)
	{
		DEBUG::LOG("[ERROR] Physical Device Doues Not Supported Extensions", nullptr);
		return false;
	}

	std::vector<VkExtensionProperties> extension_supported(extension_count);
	vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extension_count, extension_supported.data());

	//Check if the supported extensions match the desired extensions
	uint8 extension_match{};
	for (const auto& extension : extension_supported)
	{
		for (const auto& desired_extension : device_desired_extensions)
		{
			if (strcmp(extension.extensionName, desired_extension) == 0)
				++extension_match;
		}
	}

	return extension_match == device_desired_extensions.size() ? true : false;
}

uint32 VulkanPhysicalDevice::GetFamilyIndex(PHYSICAL_FAMILY_INDEX index) const
{
	const std::optional<uint32>& queue{ family_index.GetQueue(index) };
	assert(queue != std::nullopt, "No Index Family for this Device");
	return queue.value();
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

VkResult VulkanPhysicalDevice::InitDevice(VkSurfaceKHR surface)
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
		//Select One Family that has this flag enabled and can have a presentation queue
		if (property.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			family_index.SetQueueValue(PHYSICAL_FAMILY_INDEX::GRAPHICS, i);	
		}

		VkBool32 presentation_enable{ VK_FALSE };
		vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, surface, &presentation_enable);

		if (presentation_enable == VK_TRUE)
			family_index.SetQueueValue(PHYSICAL_FAMILY_INDEX::PRESENTATION, i);

		++i;
	}

	return ret;
}
