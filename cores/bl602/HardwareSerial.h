#ifndef HardwareSerial_h
#define HardwareSerial_h

#include "Stream.h"

class HardwareSerial : public Stream {
private:
    uint8_t _uart_id;

public:
    HardwareSerial(uint8_t uart_id);

    void begin(unsigned long baud);
    void end();
    virtual int available();
    virtual int peek();
    virtual int read();
    virtual void flush();
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buffer, size_t size);
    using Print::write;
    operator bool() { return true; }
};

extern HardwareSerial Serial;

#endif
