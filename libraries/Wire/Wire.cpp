#include "Wire.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "hosal_i2c.h"
#ifdef __cplusplus
}
#endif

TwoWire Wire;

static hosal_i2c_dev_t s_i2c_dev;

TwoWire::TwoWire() :
    _txAddress(0),
    _txLength(0),
    _rxIndex(0),
    _rxLength(0),
    _initialized(false),
    _sdaPin(4),
    _sclPin(3),
    _clock(100000)
{
}

void TwoWire::begin()
{
    begin(_sdaPin, _sclPin);
}

void TwoWire::begin(uint8_t sda, uint8_t scl)
{
    _sdaPin = sda;
    _sclPin = scl;

    s_i2c_dev.port = 0;
    s_i2c_dev.config.address_width = HOSAL_I2C_ADDRESS_WIDTH_7BIT;
    s_i2c_dev.config.freq = _clock;
    s_i2c_dev.config.sda = _sdaPin;
    s_i2c_dev.config.scl = _sclPin;
    s_i2c_dev.config.mode = HOSAL_I2C_MODE_MASTER;

    hosal_i2c_init(&s_i2c_dev);
    _initialized = true;
}

void TwoWire::setClock(uint32_t freq)
{
    _clock = freq;
    if (_initialized) {
        begin(_sdaPin, _sclPin);
    }
}

void TwoWire::beginTransmission(uint8_t address)
{
    _txAddress = address;
    _txLength = 0;
}

uint8_t TwoWire::endTransmission(bool sendStop)
{
    (void)sendStop;
    if (!_initialized) {
        begin();
    }

    int ret;
    if (_txLength == 0) {
        /* Probe address with 0 byte transfer */
        uint8_t dummy = 0;
        ret = hosal_i2c_master_send(&s_i2c_dev, _txAddress, &dummy, 0, 100);
    } else {
        ret = hosal_i2c_master_send(&s_i2c_dev, _txAddress, _txBuffer, _txLength, 100);
    }

    _txLength = 0;
    return (ret == 0) ? 0 : 2; /* 0: success, 2: NACK */
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, bool sendStop)
{
    (void)sendStop;
    if (!_initialized) {
        begin();
    }

    if (quantity > WIRE_BUFFER_SIZE) {
        quantity = WIRE_BUFFER_SIZE;
    }

    int ret = hosal_i2c_master_recv(&s_i2c_dev, address, _rxBuffer, quantity, 100);
    if (ret == 0) {
        _rxLength = quantity;
        _rxIndex = 0;
        return _rxLength;
    }

    _rxLength = 0;
    _rxIndex = 0;
    return 0;
}

size_t TwoWire::write(uint8_t data)
{
    if (_txLength >= WIRE_BUFFER_SIZE) {
        return 0;
    }
    _txBuffer[_txLength++] = data;
    return 1;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
    size_t count = 0;
    for (size_t i = 0; i < quantity; i++) {
        count += write(data[i]);
    }
    return count;
}

int TwoWire::available()
{
    return _rxLength - _rxIndex;
}

int TwoWire::read()
{
    if (_rxIndex < _rxLength) {
        return _rxBuffer[_rxIndex++];
    }
    return -1;
}

int TwoWire::peek()
{
    if (_rxIndex < _rxLength) {
        return _rxBuffer[_rxIndex];
    }
    return -1;
}

void TwoWire::flush()
{
}
