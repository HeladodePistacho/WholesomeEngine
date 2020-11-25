#include "Module.h"



Module::Module(std::shared_ptr<EventManager> manager) : event_manager(manager)
{
	
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
