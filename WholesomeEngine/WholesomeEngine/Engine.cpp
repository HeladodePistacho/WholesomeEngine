#include "Engine.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "EventManager.h"

Engine::Engine() : 
	module_window(std::make_shared<ModuleWindow>()), 
	module_render(std::make_shared<ModuleRender>()),
	module_input(std::make_shared<ModuleInput>())
{
	//Add modules to loop vector
	modules.push_back(module_window);
	modules.push_back(module_input);

	modules.push_back(module_render);

	//Set modules Event system
	module_window->AddListener(module_render);
}


Engine::~Engine()
{
	
}

ENGINE_STATUS Engine::Init()
{
	return IterateModules([](Module& mod) { return mod.Init(); });
}

ENGINE_STATUS Engine::Start()
{
	return IterateModules([](Module& mod) { return mod.Start(); });
}

ENGINE_STATUS Engine::Update()
{
	if (PreUpdate() != ENGINE_STATUS::SUCCESS)
		return engine_status;

	if (CurrUpdate() != ENGINE_STATUS::SUCCESS)
		return engine_status;

	if (PostUpdate() != ENGINE_STATUS::SUCCESS)
		return engine_status;

	return ENGINE_STATUS::SUCCESS;
}

ENGINE_STATUS Engine::CleanUp()
{
	return IterateModules([](Module& mod) { return mod.CleanUp(); });
}

ENGINE_STATUS Engine::PreUpdate()
{
	IterateModules([](Module& mod) { return mod.PreUpdate(); });
	return engine_status;
}

ENGINE_STATUS Engine::CurrUpdate()
{
	return IterateModules([](Module& mod) { return mod.Update(); });
}

ENGINE_STATUS Engine::PostUpdate()
{
	return IterateModules([](Module& mod) { return mod.PostUpdate(); });
}

template<typename FUNC>
ENGINE_STATUS Engine::IterateModules(FUNC function)
{
	for (auto mod : modules)
	{
		engine_status = function(*(mod.lock()));

		if (engine_status != ENGINE_STATUS::SUCCESS)
			return engine_status;
	}

	return engine_status;
}