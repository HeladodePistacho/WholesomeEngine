#include "Engine.h"



Engine::Engine()
{
	
}


Engine::~Engine()
{
}

ENGINE_STATUS Engine::Init()
{
	return ENGINE_STATUS::SUCCESS;
}

ENGINE_STATUS Engine::Start()
{
	return ENGINE_STATUS::SUCCESS;
}

ENGINE_STATUS Engine::Update()
{
	return ENGINE_STATUS::FINISHED;
}

ENGINE_STATUS Engine::CleanUp()
{
	return ENGINE_STATUS::SUCCESS;
}
