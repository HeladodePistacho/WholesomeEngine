#include "Engine.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "EventManager.h"

Engine::Engine() : event_manager(std::make_shared<EventManager>())
{
	modules.emplace_back(std::make_shared<ModuleWindow>(event_manager));
	modules.emplace_back(std::make_shared<ModuleInput>(event_manager));
	modules.emplace_back(std::make_shared<ModuleRender>(event_manager));
}


Engine::~Engine()
{
	
}

ENGINE_STATUS Engine::Init()
{
	SubscribeModules();
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

void Engine::SubscribeModules()
{
	for (auto mod : modules)
	{
		event_manager->SubscribeModule(mod);
	}
}

template<typename FUNC>
ENGINE_STATUS Engine::IterateModules(FUNC function)
{
	for (auto mod : modules)
	{
		engine_status = function(*mod);

		if (engine_status != ENGINE_STATUS::SUCCESS)
			return engine_status;
	}

	return engine_status;
}