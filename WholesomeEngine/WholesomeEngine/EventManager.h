#ifndef _EVENT_MANAGER_H_
#define _EVENT_MANAGER_H_

#include <queue>
#include <vector>
#include <map>
#include <memory>

enum class W_EVENT_TYPE;
class Module;

class EventManager
{
public:
	EventManager();
	~EventManager();

	void SubscribeModule(std::shared_ptr<Module> mod_to_subscrive);

	//void BroadcastInitEvents();
	//void ThrowEvent(std::shared_ptr<WholesomeEvent> w_event);
private:
	
	
	

	std::map<W_EVENT_TYPE, std::vector<std::weak_ptr<Module>>> module_subscriptions;
};

#endif
