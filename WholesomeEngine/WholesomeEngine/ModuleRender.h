#ifndef _MODULE_RENDER_H_
#define _MODULE_RENDER_H_

#include "Module.h"
#include <memory>
#include "vulkan/vulkan.hpp"

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	ENGINE_STATUS Init();
	ENGINE_STATUS CleanUp();

private:
	std::unique_ptr<VkInstance> vulkan_instance;

};

#endif
