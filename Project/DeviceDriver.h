#pragma once
#include <stdexcept>
#include "FlashMemoryDevice.h"

using std::exception;

class ReadFailException : public exception {
public:
    ReadFailException()
        : exception() {

    }
    explicit ReadFailException(const char* what)
        : exception{ what } {
    }
};

class WriteFailException : public exception {
public:
    WriteFailException()
        : exception() {

    }
    explicit WriteFailException(const char* what)
        : exception{ what } {
    }
};

class DeviceDriver
{
public:
    DeviceDriver();
    DeviceDriver(FlashMemoryDevice* hardware);

    void injectDevice(FlashMemoryDevice* hardware);
    int read(long address);
    int deviceRead(long address);
    void write(long address, int data);

    bool isNotEmptyMemory(long address);

protected:
    FlashMemoryDevice* m_hardware;

private:
    static constexpr int DEVICE_READ_CNT = 5;
    static constexpr int MEMORY_EMPTY = 0xFF;
};