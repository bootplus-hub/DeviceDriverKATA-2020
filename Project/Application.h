#pragma once
#include "DeviceDriver.h"

class Application {
public:
	Application();
	Application(DeviceDriver* driver);

	void injectDriver(DeviceDriver* driver);
	void readAndPrint(long startAddr, long endAddr);

private:
	DeviceDriver* _driver;
};