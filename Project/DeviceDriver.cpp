#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int rst = (int)(m_hardware->read(address));
    for (int cnt = 1; cnt < 5; ++cnt) {
        if (rst == (int)(m_hardware->read(address))) continue;
        throw ReadFailException("read failed");
    }
    return rst;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}