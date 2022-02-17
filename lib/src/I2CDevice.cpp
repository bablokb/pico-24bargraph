// --------------------------------------------------------------------------
// i2c-wrapper class for the Raspberry Pi Pico
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pico-24bargraph
// --------------------------------------------------------------------------

#include "I2CDevice.h"

// --------------------------------------------------------------------------

I2CDevice::I2CDevice(i2c_inst_t* i2c, uint8_t addr, uint8_t sda, uint8_t scl,
                                                uint speed, bool setPullup) {
  _i2c  = i2c;
  _addr = addr;
  i2c_init(i2c,speed*1000);
  gpio_set_function(sda,GPIO_FUNC_I2C);
  gpio_set_function(scl,GPIO_FUNC_I2C);
  if (setPullup) {
    gpio_pull_up(sda);
    gpio_pull_up(scl);
  }
}

// --------------------------------------------------------------------------

void I2CDevice::write(const uint8_t* buf, uint8_t n) {
  i2c_write_blocking(_i2c,_addr,buf,n,false);
}
