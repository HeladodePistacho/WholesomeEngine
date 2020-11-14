#ifndef _MODULE_H_
#define _MODULE_H_
#include "Globals.h"

class Module
{
public:
	Module();
	virtual ~Module();

	virtual ENGINE_STATUS Init()       {};
	virtual ENGINE_STATUS Start()      {};
	virtual ENGINE_STATUS PreUpdate()  {};
	virtual ENGINE_STATUS Update()     {};
	virtual ENGINE_STATUS PostUpdate() {};
	virtual ENGINE_STATUS CleanUp()    {};
};


#endif // !_MODULE_H_


