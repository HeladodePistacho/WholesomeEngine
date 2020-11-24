#ifndef _EVENT_MANAGER_H_
#define _EVENT_MANAGER_H_

#include <queue>
#include <vector>
#include <map>
#include <memory>

class WholesomeEvent;
enum class W_EVENT_TYPE;
class Module;

class EventManager
{
public:
	EventManager();
	~EventManager();

	//void BroadcastInitEvents();
	//void ThrowEvent(std::shared_ptr<WholesomeEvent> w_event);
private:
	std::queue<std::shared_ptr<WholesomeEvent>> init_events;
	std::queue<std::shared_ptr<WholesomeEvent>> start_events;
	std::queue<std::shared_ptr<WholesomeEvent>> update_events;

	std::map<W_EVENT_TYPE, std::vector<std::weak_ptr<Module>>> module_subscriptions;
};

#endif
