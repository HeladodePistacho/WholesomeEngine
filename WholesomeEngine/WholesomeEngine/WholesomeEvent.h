#ifndef _WHOLESOME_EVENT_H_
#define _WHOLESOME_EVENT_H_

#include <tuple>

enum class W_EVENT_TIME
{
	WE_INIT,
	WE_START,
	WE_UPDATE,
	WE_CLEANUP
};

enum class W_EVENT_TYPE
{
	WE_SURFACE_CREATION,
	WE_TEST				
};

class WholesomeEvent
{
public:
	template<typename... Params>
	WholesomeEvent(W_EVENT_TIME time, W_EVENT_TYPE type, Params&&... args) : throw_time(time), event_type(type), event_values(std::make_tuple(std::forward<Params>(args)...))
	{

	}

	~WholesomeEvent() {};

private:
	W_EVENT_TIME throw_time;
	W_EVENT_TYPE event_type;
	std::tuple<> event_values;
};

#endif // !_WHOLESOME_EVENT_H_

