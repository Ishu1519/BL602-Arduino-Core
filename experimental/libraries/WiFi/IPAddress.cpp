#include "IPAddress.h"
#include "Print.h"
#include <stdio.h>

IPAddress::IPAddress()
{
    _address.dword = 0;
}

IPAddress::IPAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet)
{
    _address.bytes[0] = first_octet;
    _address.bytes[1] = second_octet;
    _address.bytes[2] = third_octet;
    _address.bytes[3] = fourth_octet;
}

IPAddress::IPAddress(uint32_t address)
{
    _address.dword = address;
}

bool IPAddress::operator==(const uint8_t* addr) const
{
    return (_address.bytes[0] == addr[0]) &&
           (_address.bytes[1] == addr[1]) &&
           (_address.bytes[2] == addr[2]) &&
           (_address.bytes[3] == addr[3]);
}

size_t IPAddress::printTo(Print& p) const
{
    size_t n = 0;
    for (int i = 0; i < 3; i++) {
        n += p.print(_address.bytes[i], DEC);
        n += p.print('.');
    }
    n += p.print(_address.bytes[3], DEC);
    return n;
}

String IPAddress::toString() const
{
    char buf[16];
    sprintf(buf, "%u.%u.%u.%u", _address.bytes[0], _address.bytes[1], _address.bytes[2], _address.bytes[3]);
    return String(buf);
}
