#include "Engine.h"
#include "Module.h"
#include "ModuleWindow.h"

Engine::Engine()
{
	ModuleWindow* window = new ModuleWindow();
	modules.push_back(window);
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
	PreUpdate();

	CurrUpdate();

	PostUpdate();

	return ENGINE_STATUS::FINISHED;
}

ENGINE_STATUS Engine::CleanUp()
{
	return IterateModules([](Module* mod) { return mod->CleanUp(); });
}

ENGINE_STATUS Engine::PreUpdate()
{
	return IterateModules([](Module* mod) { return mod->PreUpdate(); });
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

		if (engine_status == ENGINE_STATUS::FAIL)
			return engine_status;
	}

	return engine_status;
}