#include "DeviceDriver.h"

DeviceDriver::DeviceDriver() : m_hardware(nullptr)
{
}

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

void DeviceDriver::injectDevice(FlashMemoryDevice* hardware)
{
    m_hardware = hardware;
}

int DeviceDriver::read(long address)
{
    int rst = deviceRead(address);
    for (int cnt = 1; cnt < DEVICE_READ_CNT; ++cnt) {
        if (rst == deviceRead(address)) continue;
        throw ReadFailException("read failed");
    }
    return rst;
}

int DeviceDriver::deviceRead(long address)
{
    verifyDevice();
    return (int)(m_hardware->read(address));
}

void DeviceDriver::write(long address, int data)
{
    verifyDevice();
    if (isNotEmptyMemory(address)) throw WriteFailException("write failed");
    m_hardware->write(address, (unsigned char)data);
}

bool DeviceDriver::isNotEmptyMemory(long address)
{
    return read(address) != MEMORY_EMPTY;
}

void DeviceDriver::verifyDevice()
{
    if (m_hardware == nullptr) throw std::runtime_error{ "device is nullptr" };
}
