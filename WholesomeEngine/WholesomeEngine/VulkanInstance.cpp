#include "VulkanInstance.h"
#include "SDL2/SDL_vulkan.h"

VulkanInstance::VulkanInstance() : instance(std::make_unique<VkInstance>()), current_gpu(VK_NULL_HANDLE)
{
}

VkResult VulkanInstance::CreateInstance(const SDL_Window* window)
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

	const char* extensions[1] = { "VK_KHR_win32_surface" };

	uint32 num_extensions;
	SDL_Vulkan_GetInstanceExtensions(const_cast<SDL_Window*>(window), &num_extensions, nullptr);
	std::vector<const char*> sdl_extensions{ num_extensions };
	SDL_Vulkan_GetInstanceExtensions(const_cast<SDL_Window*>(window), &num_extensions, sdl_extensions.data());


	VkInstanceCreateInfo instance_info{
		VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, //StructureType
		nullptr,												 //Next pointer
		0,														 //Flags
		&application_info,										 //Application info pointer
		0,														 //Layer Count		 ]
		nullptr,												 //Layer Names       ]---->Not using Layers nor extensions de momento                 
		num_extensions,											 //Extension Count	 ]
		sdl_extensions.data()									 //Extension Names   ]
	};

	auto result = vkCreateInstance(&instance_info, nullptr, instance.get());
	return result;
}

void VulkanInstance::DestroyInstance()
{
	if (instance != nullptr)
	{
		DEBUG::LOG("DESTROYING Instance ", nullptr);
		vkDestroyInstance(*instance, nullptr);
		instance.reset(nullptr);
	}
	else DEBUG::LOG("[ERROR] Instance was Nullptr ", nullptr);
}

VkInstance VulkanInstance::GetInstance() const
{
	return (*instance);
}

VkResult VulkanInstance::SelectPhysicalDevice(VkSurfaceKHR surface)
{
	VkResult ret{ VkResult::VK_SUCCESS };

	for (auto& device : gpus)
	{
		device.InitDevice(surface);

		if (device.IsValid())
		{
			current_gpu = device;
			DEBUG::LOG("Using GPU: ", nullptr);
			current_gpu.PrintInformation();
			break;
		}
	}
	
	return ret;
}

VkResult VulkanInstance::GetPhysicalDevices()
{
	uint32 device_count = 0;
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
		gpus.push_back(device);
	}

	return ret;
}

void VulkanInstance::PrintDeviceInformation(uint8 index) const
{
	if (index >= gpus.size())
	{
		DEBUG::LOG("[ERROR] Device index out of range", nullptr);
		return;
	}

	gpus[index].PrintInformation();
}

const VulkanPhysicalDevice& VulkanInstance::GetPhysicalDevice() const
{
	return current_gpu;
}

