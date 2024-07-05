#pragma once
#include "DeviceDriver.h"

class Application {
public:
	Application();
	Application(DeviceDriver* driver);

	void injectDriver(DeviceDriver* driver);
	void readAndPrint(long startAddr, long endAddr);
	void writeAll(int data);

private:
	DeviceDriver* _driver;
};