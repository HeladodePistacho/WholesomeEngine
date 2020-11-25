#ifndef _MODULE_INPUT_H_
#define _MODULE_INPUT_H_

#include "Module.h"
class ModuleInput : public Module
{
public:
	ModuleInput(std::shared_ptr<EventManager> manager);
	~ModuleInput();

	ENGINE_STATUS PreUpdate();
};

#endif

