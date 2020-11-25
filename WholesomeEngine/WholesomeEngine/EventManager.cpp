#include "EventManager.h"
#include "Module.h"
#include "WholesomeEvent.h"



EventManager::EventManager()
{
}


EventManager::~EventManager()
{
}

void EventManager::SubscribeModule(std::shared_ptr<Module> mod_to_subscribe)
{
	auto module_subs = mod_to_subscribe->GetSubscription();

	if (module_subs == std::nullopt)
		return;
	
	for (auto event_type : module_subs.value())
	{
		if (auto finded = module_subscriptions.find(event_type); finded != module_subscriptions.end())
			(*finded).second.push_back(mod_to_subscribe);
		else module_subscriptions[event_type].push_back(mod_to_subscribe);
	}

	
}
