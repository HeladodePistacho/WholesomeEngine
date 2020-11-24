#include "VulkanLogicalDevice.h"
#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"


VulkanLogicalDevice::VulkanLogicalDevice() : logic_device(VK_NULL_HANDLE)
{
}


VulkanLogicalDevice::~VulkanLogicalDevice()
{
	
}

VkResult VulkanLogicalDevice::InitDevice(const VulkanInstance& vulkan_instance)
{
	//Start specifying the number of queues for a single queue family
	float queue_priority{ 1.0f };
	uint32 family_index = vulkan_instance.GetPhysicalDevice().GetFamilyIndex();

	VkDeviceQueueCreateInfo queue_info{
		VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,				//Type of struct
		nullptr,												//Pointer to next
		0,														//Flags
		family_index,											//Family index to send queue
		1,														//Queue Count
		&queue_priority											//Queue Priority from 0.0f to 1.0f
	};

	//Set the device features that we will be using -> for now it is all set to VK_FALSE
	VkPhysicalDeviceFeatures device_features{};
	
	//Create the logical device 
	//Set the logical device info
	VkDeviceCreateInfo logic_device_info{
		VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,	//Type of struct
		nullptr,								//Pointer to Next
		0,										//Flags
		1,										//Queue Create Info count
		&queue_info,							//VkDeviceQueueCreateInfo
		0,										//Enabled layer count -> deprecated
		nullptr,								//Enabled layer names -> deprecated and ignored
		0,										//Enabled extension count -> device specific, ignored for now
		nullptr,								//Enabled extension names -> device specific, ignored for now
		&device_features						//VkPhysicalDeviceFeatures
	};

	//Create the device
	if (auto result = vkCreateDevice(vulkan_instance.GetPhysicalDevice().PhysicalDevice(), &logic_device_info, nullptr, &logic_device); result != VK_SUCCESS)
	{
		DEBUG::LOG("[ERROR] vkCreateDevice FAILURE", nullptr);
		return result;
	}

	//Get the Queue Handle
	//We can have a queue handle for each family but as long as we use one family we are having only one queue
	vkGetDeviceQueue(logic_device, family_index, 0, &queue_handle);

	return VkResult::VK_SUCCESS;

}

void VulkanLogicalDevice::DestroyDevice()
{
	if (logic_device != VK_NULL_HANDLE)
	{
		DEBUG::LOG("DESTROYING Logic Device ", nullptr);
		vkDestroyDevice(logic_device, nullptr);
		logic_device = VK_NULL_HANDLE;
	}
	else DEBUG::LOG("[ERROR] Device was Nullptr ", nullptr);
}
