#include <iostream>
#include "Application.h"

using namespace std;

Application::Application() : _driver{ nullptr }
{
}

Application::Application(DeviceDriver* driver) : _driver{ driver }
{
}

void Application::injectDriver(DeviceDriver* driver)
{
	_driver = driver;
}

void Application::readAndPrint(long startAddr, long endAddr)
{
	for (long addr = startAddr; addr <= endAddr; ++addr)
		cout << _driver->read(addr) << " ";
	cout << endl;
}

void Application::writeAll(int data)
{
	for (long addr = 0x00; addr < 0x05; ++addr) {
		_driver->write(addr, data);
	}
}
