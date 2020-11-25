#include "Module.h"



Module::Module()
{
	DEBUG::LOG("CREATING MODULE", nullptr);
}


Module::~Module()
{
}

const std::optional<std::vector<W_EVENT_TYPE>>& Module::GetSubscription() const
{
	return subscription_to_events;
}

//
//EventManager& Module::GetEventManager() const
//{
//	if (!event_manager.expired())
//	{
//		auto shared_event_manager = event_manager.lock();
//		return *shared_event_manager;
//	}
//}
