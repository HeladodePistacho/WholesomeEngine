#include "Engine.h"
#include <memory>
#include "Globals.h"


int main()
{
	//std::unique_ptr<Engine> app;

	LOG("TMP % lololol % xs % ", 1, 2.8f, 3.1);
	LOG("--------------- TEST -------------", nullptr);

	LOG("Hola soy: % y tengo % sidas", "Eric", 12, nullptr);

	std::string omega_lol{ "OMEEEGA LOOOOL" };
	LOG(omega_lol, nullptr);

	getchar();

	return 0;
}