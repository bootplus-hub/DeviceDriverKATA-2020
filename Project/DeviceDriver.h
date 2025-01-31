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
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;

private:
    int deviceRead(long address);
    bool isNotEmptyMemory(long address);
    void verifyDevice();

    static constexpr int DEVICE_READ_CNT = 5;
    static constexpr int MEMORY_EMPTY = 0xFF;
};