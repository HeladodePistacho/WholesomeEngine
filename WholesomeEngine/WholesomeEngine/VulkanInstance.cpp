#include "VulkanInstance.h"


VulkanInstance::VulkanInstance() : instance(std::make_unique<VkInstance>()), current_gpu(VK_NULL_HANDLE)
{
}

VkResult VulkanInstance::CreateInstance()
{
	VkApplicationInfo application_info{
		VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO, //StructureType
		nullptr,											 //Next pointer
		"Wholesome Engine",									 //Application Name
		VK_MAKE_VERSION(0, 0, 1),													 //Application Version
		"Wholesome Engine",									 //Engine Name
		VK_MAKE_VERSION(0, 0, 1),													 //Engine Version
		VK_API_VERSION_1_2									 //Vulkan Api Version
	};

	VkInstanceCreateInfo instance_info{
		VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, //StructureType
		nullptr,												 //Next pointer
		0,														 //Flags
		&application_info,										 //Application info pointer
		0,														 //Layer Count		 ]
		nullptr,												 //Layer Names       ]---->Not using Layers nor extensions de momento                 
		0,														 //Extension Count	 ]
		nullptr													 //Extension Names   ]
	};

	auto result = vkCreateInstance(&instance_info, nullptr, instance.get());
	return result;
}

void VulkanInstance::DestroyInstance()
{
	if (instance != nullptr)
	{
		vkDestroyInstance(*instance, nullptr);
		instance.reset(nullptr);
	}
	else DEBUG::LOG("[ERROR] Instance was Nullptr ", nullptr);
}

VkInstance& VulkanInstance::GetInstance() const
{
	return (*instance);
}

VkResult VulkanInstance::SelectPhysicalDevice()
{
	uint device_count = 0;
	VkResult ret = VkResult::VK_SUCCESS;

	//Get Num of Devices
	ret = vkEnumeratePhysicalDevices(*instance, &device_count, nullptr);

	if (device_count == 0)
	{
		DEBUG::LOG("[ERROR] NO DEVICE FOUNDED", nullptr);
		ret = VkResult::VK_ERROR_UNKNOWN;
		return ret;
	}

	if (ret != VkResult::VK_SUCCESS)
	{
		DEBUG::LOG("[ERROR] ENUMERATE PHYSICAL DEVICES ERROR", nullptr);
		return ret;
	}

	std::vector<VkPhysicalDevice> devices(device_count);

	//Fill the Vector with all the devices
	ret = vkEnumeratePhysicalDevices(*instance, &device_count, devices.data());

	DEBUG::LOG("Num Devices: %", device_count);

	//Look for the most apropiate device
	//By now It Will be the first one finded
	for (const auto& device : devices)
	{
		gpus.emplace_back(device);
		PrintDeviceInformation(device);
	}
	current_gpu = gpus[0];
	
}

void VulkanInstance::PrintDeviceInformation(uint index) const
{
	if (index >= gpus.size())
	{
		DEBUG::LOG("[ERROR] Device index out of range", nullptr);
		return;
	}

	PrintDeviceInformation(gpus[index]);
}

void VulkanInstance::PrintDeviceInformation(const VkPhysicalDevice& device) const
{
	VkPhysicalDeviceProperties device_properties;
	vkGetPhysicalDeviceProperties(device, &device_properties);

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
