#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

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
    return (int)(m_hardware->read(address));
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}