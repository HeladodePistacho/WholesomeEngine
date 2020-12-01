#ifndef _VULKAN_PHYSICAL_DEVICE_H_
#define _VULKAN_PHYSICAL_DEVICE_H_

#include "Globals.h"
#include "vulkan/vulkan.hpp"
#include <vector>
#include <optional>

//Device Extensions needed
inline std::array<const char*, 1> device_desired_extensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

enum class PHYSICAL_FAMILY_INDEX : uint8
{
	GRAPHICS = 0,
	PRESENTATION
};

struct PhysicalDeviceQueuesIndices
{
	std::optional<uint32> graphics_family;
	std::optional<uint32> presentation_family;

	PhysicalDeviceQueuesIndices& operator=(const PhysicalDeviceQueuesIndices& other)
	{
		if (HasValue(other.graphics_family))
			graphics_family = other.graphics_family.value();

		if (HasValue(other.presentation_family))
			presentation_family = other.presentation_family.value();

		return (*this);
	}

	bool IsValid() const
	{
		return HasValue(graphics_family) && HasValue(presentation_family);
	}

	const std::optional<uint32>& GetQueue(PHYSICAL_FAMILY_INDEX index) const
	{
		switch (index)
		{
		case PHYSICAL_FAMILY_INDEX::GRAPHICS:
			if (HasValue(graphics_family))
				return graphics_family;
			break;
		case PHYSICAL_FAMILY_INDEX::PRESENTATION:
			if (HasValue(presentation_family))
				return presentation_family;
			break;
		}
		return std::nullopt;
	}
	void SetQueueValue(PHYSICAL_FAMILY_INDEX index, uint32 value)
	{
		switch (index)
		{
		case PHYSICAL_FAMILY_INDEX::GRAPHICS:
			graphics_family = value;
			break;
		case PHYSICAL_FAMILY_INDEX::PRESENTATION:
			presentation_family = value;
			break;
		}
	}
	std::vector<uint32> GetQueueIndices() const
	{
		assert(IsValid(), "DEVICE NOT VALID");
		return std::vector<uint32>{graphics_family.value(), presentation_family.value()};
	}
private:
	inline bool HasValue(const std::optional<uint32>& index_family) const
	{
		return index_family.has_value();
	}
};

class VulkanPhysicalDevice
{
public:
	VulkanPhysicalDevice();
	VulkanPhysicalDevice(const VkPhysicalDevice& device);
	VulkanPhysicalDevice(const VulkanPhysicalDevice& device);
	~VulkanPhysicalDevice();

	VulkanPhysicalDevice& operator=(const VkPhysicalDevice& device);
	VulkanPhysicalDevice& operator=(const VulkanPhysicalDevice& device);

	VkPhysicalDevice PhysicalDevice() const;
	VkResult InitDevice(VkSurfaceKHR);

	//Device Suitability
	bool IsValid() const;
	uint32 GetFamilyIndex(PHYSICAL_FAMILY_INDEX) const;
	std::vector<uint32> GetFamilyIndices() const;

	void PrintInformation() const;
private:
	VkPhysicalDevice physical_device;
	std::vector<VkQueueFamilyProperties> queue_properties;

	//Temporary check for device validation
	bool CheckDeviceExtensions() const;
	PhysicalDeviceQueuesIndices family_index;
};

#endif // !

