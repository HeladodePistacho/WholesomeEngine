#include "ModuleInput.h"
#include "SDL2/SDL.h"


ModuleInput::ModuleInput()
{
}


ModuleInput::~ModuleInput()
{
}

ENGINE_STATUS ModuleInput::PreUpdate()
{
	static SDL_Event current_event{};
	while (SDL_PollEvent(&current_event))
	{
		switch (current_event.type)
		{
		case SDL_QUIT:
			return ENGINE_STATUS::FINISHED;
		}
	}

	return ENGINE_STATUS::SUCCESS;
}
