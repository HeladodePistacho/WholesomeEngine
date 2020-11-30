#ifndef _MODULE_H_
#define _MODULE_H_

#include "Globals.h"
#include <memory>
#include <optional>
#include <vector>

enum class W_EVENT_TYPE;
class EventManager;

class Module
{
public:
	Module();
	virtual ~Module();

	virtual ENGINE_STATUS Init()       { return ENGINE_STATUS::SUCCESS; };
	virtual ENGINE_STATUS Start()      { return ENGINE_STATUS::SUCCESS; };
	virtual ENGINE_STATUS PreUpdate()  { return ENGINE_STATUS::SUCCESS; };
	virtual ENGINE_STATUS Update()     { return ENGINE_STATUS::SUCCESS; };
	virtual ENGINE_STATUS PostUpdate() { return ENGINE_STATUS::SUCCESS; };
	virtual ENGINE_STATUS CleanUp()    { return ENGINE_STATUS::SUCCESS; };
};


#endif // !_MODULE_H_


