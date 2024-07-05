#pragma once
#include "DeviceDriver.h"

class Application {
public:
	Application();

private:
	DeviceDriver* _driver;
};