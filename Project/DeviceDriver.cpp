#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int rst = 0;
    for (int cnt = 0; cnt < 5; ++cnt) {
        rst = (int)(m_hardware->read(address));
    }
    return rst;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}