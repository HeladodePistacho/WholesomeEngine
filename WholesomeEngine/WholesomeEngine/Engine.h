#ifndef _ENGINE_H_
#define _ENGINE_H_
#include "Globals.h"

class Engine
{
public:
	Engine();
	~Engine();

	ENGINE_STATUS Init();
	ENGINE_STATUS Start();
	ENGINE_STATUS Update();
	ENGINE_STATUS CleanUp();

private:
	ENGINE_STATUS PreUpdate();
	ENGINE_STATUS CurrUpdate();
	ENGINE_STATUS PostUpdate();

};

#endif // !_ENGINE_H_




