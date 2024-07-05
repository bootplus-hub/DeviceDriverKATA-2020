#include <iostream>
#include "Application.h"

using namespace std;

Application::Application() : _driver{ nullptr }
{
}

Application::Application(DeviceDriver* driver) : _driver{ driver }
{
}

void Application::readAndPrint(long startAddr, long endAddr)
{
	for (long addr = startAddr; addr <= endAddr; ++addr)
		cout << _driver->read(addr) << " ";
	cout << endl;
}
