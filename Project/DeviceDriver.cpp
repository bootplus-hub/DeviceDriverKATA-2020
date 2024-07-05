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
    for (int cnt = 1; cnt < 5; ++cnt) {
        if (rst == deviceRead(address)) continue;
        throw ReadFailException("read failed");
    }
    return rst;
}

int DeviceDriver::deviceRead(long address)
{
    return (int)(m_hardware->read(address));
}

void DeviceDriver::write(long address, int data)
{
    if (deviceRead(address) != 0xFF) throw WriteFailException("write failed");
    m_hardware->write(address, (unsigned char)data);
}