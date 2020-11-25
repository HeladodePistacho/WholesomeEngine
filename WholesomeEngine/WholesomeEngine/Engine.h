#ifndef _ENGINE_H_
#define _ENGINE_H_
#include "Globals.h"
#include <vector>
#include <memory>

class Module;
class EventManager;

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

	std::vector<std::shared_ptr<Module>> modules;
	ENGINE_STATUS engine_status{};

	template<typename FUNC>
	ENGINE_STATUS IterateModules(FUNC);

	//Even System
	void SubscribeModules();
	std::shared_ptr<EventManager> event_manager;
};

#endif // !_ENGINE_H_


