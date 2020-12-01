#include "VulkanLogicalDevice.h"
#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"


VulkanLogicalDevice::VulkanLogicalDevice() : logic_device(VK_NULL_HANDLE), graphic_handle(VK_NULL_HANDLE), presentation_handle(VK_NULL_HANDLE)
{
}


VulkanLogicalDevice::~VulkanLogicalDevice()
{
	
}

VkResult VulkanLogicalDevice::InitDevice(const VulkanInstance& vulkan_instance)
{
	//Start specifying the number of queues for a single queue family
	float queue_priority{ 1.0f };
	
	//Create a QueueInfo struct foreach family queue index in the physical device
	std::vector<uint32> queue_families_indices = vulkan_instance.GetPhysicalDevice().GetFamilyIndices();
	std::vector<VkDeviceQueueCreateInfo> queues_info;

	for (const uint32& index : queue_families_indices)
	{
		VkDeviceQueueCreateInfo queue_info{
			VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,				//Type of struct
			nullptr,												//Pointer to next
			0,														//Flags
			index,													//Family index to send queue
			1,														//Queue Count
			&queue_priority											//Queue Priority from 0.0f to 1.0f
		};

		queues_info.push_back(queue_info);
	}

	//Set the device features that we will be using -> for now it is all set to VK_FALSE
	VkPhysicalDeviceFeatures device_features{};
	
	//Create the logical device 
	//Set the logical device info
	VkDeviceCreateInfo logic_device_info{
		VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,	//Type of struct
		nullptr,								//Pointer to Next
		0,										//Flags
		queues_info.size(),										//Queue Create Info count
		queues_info.data(),							//VkDeviceQueueCreateInfo
		0,										//Enabled layer count -> deprecated
		nullptr,								//Enabled layer names -> deprecated and ignored
		device_desired_extensions.size(),		//Enabled extension count -> device specific, ignored for now
		device_desired_extensions.data(),		//Enabled extension names -> device specific, ignored for now
		&device_features						//VkPhysicalDeviceFeatures
	};

	//Create the device
	if (auto result = vkCreateDevice(vulkan_instance.GetPhysicalDevice().PhysicalDevice(), &logic_device_info, nullptr, &logic_device); result != VK_SUCCESS)
	{
		DEBUG::LOG("[ERROR] vkCreateDevice FAILURE", nullptr);
		return result;
	}

	//Get the Queue Handle
	//We can have a queue handle for each family
	vkGetDeviceQueue(logic_device, vulkan_instance.GetPhysicalDevice().GetFamilyIndex(PHYSICAL_FAMILY_INDEX::GRAPHICS), 0, &graphic_handle);
	vkGetDeviceQueue(logic_device, vulkan_instance.GetPhysicalDevice().GetFamilyIndex(PHYSICAL_FAMILY_INDEX::PRESENTATION), 0, &presentation_handle);

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

const VkDevice VulkanLogicalDevice::GetDevice() const
{
	return logic_device;
}
