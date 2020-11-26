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

template<typename DATA>
class WholesomeEvent
{
public:

	WholesomeEvent(W_EVENT_TIME time, W_EVENT_TYPE type, const DATA& data) : throw_time(time), event_type(type), data_structure(data)
	{

	}

	~WholesomeEvent() {};

private:
	W_EVENT_TIME throw_time;
	W_EVENT_TYPE event_type;
	DATA data_structure;
};

#endif // !_WHOLESOME_EVENT_H_

