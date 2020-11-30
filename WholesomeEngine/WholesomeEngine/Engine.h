#ifndef _ENGINE_H_
#define _ENGINE_H_
#include "Globals.h"
#include <vector>
#include <memory>

class Module;

class ModuleWindow;
class ModuleRender;
class ModuleInput;

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

	//Modules
	std::shared_ptr<ModuleWindow> module_window;
	std::shared_ptr<ModuleRender> module_render;
	std::shared_ptr<ModuleInput>  module_input;

	std::vector<std::weak_ptr<Module>> modules;
	ENGINE_STATUS engine_status{};

	template<typename FUNC>
	ENGINE_STATUS IterateModules(FUNC);
};

#endif // !_ENGINE_H_


