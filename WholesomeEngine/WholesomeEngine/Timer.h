#ifndef _TIMER_H_
#define _TIMER_H_

#include<chrono>
using namespace std::chrono;

using Clock = system_clock;


class Timer
{
private:
	Clock::time_point current_time;

public:
	Timer() : current_time(Clock::now()) {};
	~Timer() {};

	template<typename T>
	T GetElapsedTime() const
	{
		duration<float> delta_time = Clock::now() - current_time;
		return duration_cast<T>(delta_time);
	}

	template<typename T>
	T GetElapsedTimeReset()
	{
		duration<float> delta_time = Clock::now() - current_time;
		current_time = Clock::now();
		return duration_cast<T>(delta_time);
	}
};

#endif // !_TIMER_H_
