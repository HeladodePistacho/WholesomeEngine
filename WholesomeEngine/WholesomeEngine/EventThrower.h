#ifndef _EVENT_THROWER_H_
#define _EVENT_THROWER_H_

#include <vector>
#include "WholesomeEvent.h"
#include "EventListener.h"

template<typename EVENT_DATA>
class EventThrower
{
public:
	EventThrower() {}
	virtual ~EventThrower() {}

	void AddListener(const std::shared_ptr<EventListener<EVENT_DATA>>& new_listener)
	{
		for (auto listener : listeners)
		{
			if (listener.lock() == new_listener)
				return;
		}

		listeners.push_back(new_listener);
	}

	void BroadcastEvent(const EVENT_DATA& event_data)
	{
		for (auto listener : listeners)
		{
			listener.lock()->OnEventRecieved(event_data);
		}
	}

private:
	std::vector<std::weak_ptr<EventListener<EVENT_DATA>>> listeners;
	
};

#endif // !_EVENT_THROWER_H_