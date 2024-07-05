#pragma once
#include <stdexcept>
#include "FlashMemoryDevice.h"

using std::exception;

class ReadFailException : public std::exception {
public:
    ReadFailException()
        : exception() {

    }
    explicit ReadFailException(const char* what)
        : exception{ what } {
    }
};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};