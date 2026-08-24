#ifndef IPAddress_h
#define IPAddress_h

#include <stdint.h>
#include "Printable.h"
#include "WString.h"

class IPAddress : public Printable {
private:
    union {
        uint8_t bytes[4];
        uint32_t dword;
    } _address;

public:
    IPAddress();
    IPAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet);
    IPAddress(uint32_t address);

    operator uint32_t() const { return _address.dword; }
    bool operator==(const IPAddress& addr) const { return _address.dword == addr._address.dword; }
    bool operator==(const uint8_t* addr) const;

    uint8_t operator[](int index) const { return _address.bytes[index]; }
    uint8_t& operator[](int index) { return _address.bytes[index]; }

    virtual size_t printTo(Print& p) const;
    String toString() const;

    friend class WiFiClass;
};

#endif
