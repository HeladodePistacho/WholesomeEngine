#ifndef _EVENT_LISTENER_H_
#define _EVENT_LISTENER_H_

#include<optional>

template<typename EVENT_DATA>
class EventListener
{
public:
	EventListener() {}
	virtual ~EventListener() {}

	virtual void OnEventRecieved(const EVENT_DATA& event_recieved) {}

protected:
	std::optional<EVENT_DATA> event_recieved;
};

#endif // !_EVENT_LISTENER_H_



