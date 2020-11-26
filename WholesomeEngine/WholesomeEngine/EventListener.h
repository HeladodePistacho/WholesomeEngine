#ifndef _EVENT_LISTENER_H_
#define _EVENT_LISTENER_H_

class WholesomeEvent;

class EventListener
{
public:
	virtual ~EventListener() {}

	virtual void OnEventRecieved(const WholesomeEvent& wevent) = 0;
};

#endif // !_EVENT_LISTENER_H_



