// --------------------------------------------------------------------------
// i2c-wrapper class for the Raspberry Pi Pico
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pico-24bargraph
// --------------------------------------------------------------------------

#ifndef I2CDEVICE_H
#define I2CDEVICE_H

#include "hardware/i2c.h"
#include "pico/stdlib.h"

class I2CDevice {
  private:
    i2c_inst_t* _i2c;
    uint8_t     _addr;
  public:
    I2CDevice(i2c_inst_t* i2c, uint8_t addr, uint8_t sda, uint8_t scl, uint speed=400,
                                                    bool setPullup = true);
    void write(const uint8_t* buf, uint8_t n);
};
#endif
