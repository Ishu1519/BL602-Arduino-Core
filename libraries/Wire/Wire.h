#ifndef TwoWire_h
#define TwoWire_h

#include "Arduino.h"
#include "Stream.h"

#define WIRE_BUFFER_SIZE 32

class TwoWire : public Stream {
private:
    uint8_t _txAddress;
    uint8_t _txBuffer[WIRE_BUFFER_SIZE];
    uint8_t _txLength;

    uint8_t _rxBuffer[WIRE_BUFFER_SIZE];
    uint8_t _rxIndex;
    uint8_t _rxLength;

    bool _initialized;
    uint8_t _sdaPin;
    uint8_t _sclPin;
    uint32_t _clock;

public:
    TwoWire();

    void begin();
    void begin(uint8_t sda, uint8_t scl);
    void begin(int sda, int scl) { begin((uint8_t)sda, (uint8_t)scl); }
    void setClock(uint32_t freq);

    void beginTransmission(uint8_t address);
    void beginTransmission(int address) { beginTransmission((uint8_t)address); }

    uint8_t endTransmission(bool sendStop);
    uint8_t endTransmission(void) { return endTransmission(true); }

    uint8_t requestFrom(uint8_t address, uint8_t quantity, bool sendStop);
    uint8_t requestFrom(uint8_t address, uint8_t quantity) { return requestFrom(address, quantity, true); }
    uint8_t requestFrom(int address, int quantity) { return requestFrom((uint8_t)address, (uint8_t)quantity, true); }

    virtual size_t write(uint8_t data);
    virtual size_t write(const uint8_t *data, size_t quantity);
    virtual int available();
    virtual int read();
    virtual int peek();
    virtual void flush();

    using Print::write;
};

extern TwoWire Wire;

#endif
