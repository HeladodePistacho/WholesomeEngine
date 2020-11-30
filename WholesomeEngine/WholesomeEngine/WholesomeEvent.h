#ifndef _WHOLESOME_EVENT_H_
#define _WHOLESOME_EVENT_H_

#include "vulkan/vulkan.hpp"

struct WESurfaceCreation
{
	WESurfaceCreation(VkInstance inst) : vulkan_instance(inst) {}
	VkInstance vulkan_instance;
};

#endif // !_WHOLESOME_EVENT_H_

