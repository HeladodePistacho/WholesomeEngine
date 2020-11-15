#include "Engine.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"

Engine::Engine()
{
	ModuleWindow* window = new ModuleWindow();
	ModuleInput* input = new ModuleInput();

	modules.push_back(window);
	modules.push_back(input);
}


Engine::~Engine()
{
	IterateModules([](Module* mod) { 
		delete mod;
		mod = nullptr;
		return ENGINE_STATUS::SUCCESS;
	 });
}

ENGINE_STATUS Engine::Init()
{
	return IterateModules([](Module* mod) { return mod->Init(); });
}

ENGINE_STATUS Engine::Start()
{
	return IterateModules([](Module* mod) { return mod->Start(); });
}

ENGINE_STATUS Engine::Update()
{
	if (PreUpdate() != ENGINE_STATUS::SUCCESS)
		return engine_status;

	CurrUpdate();

	PostUpdate();

	return ENGINE_STATUS::SUCCESS;
}

ENGINE_STATUS Engine::CleanUp()
{
	return IterateModules([](Module* mod) { return mod->CleanUp(); });
}

ENGINE_STATUS Engine::PreUpdate()
{
	IterateModules([](Module* mod) { return mod->PreUpdate(); });
	return engine_status;
}

ENGINE_STATUS Engine::CurrUpdate()
{
	return IterateModules([](Module* mod) { return mod->Update(); });
}

ENGINE_STATUS Engine::PostUpdate()
{
	return IterateModules([](Module* mod) { return mod->PostUpdate(); });
}

template<typename FUNC>
ENGINE_STATUS Engine::IterateModules(FUNC function)
{
	for (auto mod : modules)
	{
		engine_status = function(mod);

		if (engine_status != ENGINE_STATUS::SUCCESS)
			return engine_status;
	}

	return engine_status;
}