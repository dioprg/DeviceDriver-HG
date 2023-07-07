#include "DeviceDriver.h"
#include <exception>

using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

class ReadFailException : public exception {
public:
    const char* what() const noexcept override
    {
        return "Read Fail";
    }
};

int DeviceDriver::read(long address)
{
    int readNow = (int)(m_hardware->read(address));
    int readPrev = readNow;
    for (auto i = 1; i < 5; i++) {
        readNow = (int)(m_hardware->read(address));
        if (readNow != readPrev) {
            throw ReadFailException();
        }
    }
    return readNow;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}