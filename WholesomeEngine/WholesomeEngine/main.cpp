#include "Engine.h"
#include <memory>
#include "Globals.h"
#include "Timer.h"

int main()
{
	//std::unique_ptr<Engine> app;
	Timer timer{};
	DEBUG::LOG("TMP % lololol % xs % ", 1, 2.8f, 3.1);
	double lol = timer.GetElapsedTime<microseconds>().count();
	DEBUG::LOG("--------------- TEST -------------", nullptr);

	DEBUG::LOG("Hola soy: % y tengo % sidas", "Eric", 12, nullptr);

	std::string omega_lol{ "OMEEEGA LOOOOL" };
	DEBUG::LOG(omega_lol, nullptr);
	
	//getchar();

	
	
	DEBUG::LOG("%", lol);

	return 0;
}