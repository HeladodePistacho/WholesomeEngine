#include "Engine.h"
#include <memory>
#include "Globals.h"
#include "Timer.h"

enum class MAIN_STATE
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

int main()
{
	DEBUG::LOG("--------------- ENGINE -------------", nullptr);
	MAIN_STATE main_state = MAIN_STATE::MAIN_CREATION;
	std::unique_ptr<Engine> application;

	while (main_state != MAIN_STATE::MAIN_EXIT)
	{
		switch (main_state)
		{
		case MAIN_STATE::MAIN_CREATION:
			DEBUG::LOG("--------------- CREATING ENGINE -------------", nullptr);
			application.reset(new Engine);
			main_state = MAIN_STATE::MAIN_START;
			break;

		case MAIN_STATE::MAIN_START:
			DEBUG::LOG("--------------- INITIALIZING ENGINE -------------", nullptr);

			main_state = MAIN_STATE::MAIN_UPDATE;
			if (application->Init() == ENGINE_STATUS::FAIL)
			{
				DEBUG::LOG("[ERROR] Application Fail Init", nullptr);
				main_state = MAIN_STATE::MAIN_EXIT;
			}

			DEBUG::LOG("--------------- STARTING ENGINE -------------", nullptr);
			if(application->Start() == ENGINE_STATUS::FAIL)
			{
				DEBUG::LOG("[ERROR] Application Fail Start", nullptr);
				main_state = MAIN_STATE::MAIN_EXIT;
			}	
			break;

		case MAIN_STATE::MAIN_UPDATE:

			switch (ENGINE_STATUS application_stat = application->Update(); application_stat)
			{
			case ENGINE_STATUS::FAIL:
				DEBUG::LOG("[ERROR] Application Fail Update", nullptr);
				main_state = MAIN_STATE::MAIN_EXIT;
				break;

			case  ENGINE_STATUS::FINISHED:
				DEBUG::LOG("--------------- ENGINE FINISHED -------------", nullptr);
				main_state = MAIN_STATE::MAIN_FINISH;
				break;
			}

			break;

		case MAIN_STATE::MAIN_FINISH:
			DEBUG::LOG("--------------- CLOSING ENGINE -------------", nullptr);
			if (application->CleanUp() == ENGINE_STATUS::FAIL)
			{
				DEBUG::LOG("[ERROR] Application Fail Cleaning Up", nullptr);
				
			}
			main_state = MAIN_STATE::MAIN_EXIT;
			break;
		}
	}
	DEBUG::LOG("--------------- SHUT DOWN ENGINE -------------", nullptr);
	return 0;
}