// --------------------------------------------------------------------------
// Example program for the driver library for the 24-LED bargraph.
//
// This project uses a modified and simplified version of the original from
// https://github.com/adafruit/Adafruit_LED_Backpack
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pico-24bargraph
// --------------------------------------------------------------------------

#include <stdio.h>
#include <hardware/i2c.h>
#include "I2CDevice.h"
#include "Adafruit_24bargraph.h"

int main() {
    stdio_init_all();

    // create i2c-device and bargraph-object
    I2CDevice* i2cdev = new I2CDevice(BAR_I2C,BAR_ADDR,BAR_SDA,BAR_SCL,BAR_SPEED);
    Adafruit_24bargraph* bar = new Adafruit_24bargraph(i2cdev);

    // fill graph with three colors, 8 bars each
    for (int i=0; i<8;++i) {
      bar->setBar(i,LED_GREEN);
    }
    bar->writeDisplay();
    sleep_ms(1000);

    for (int i=8; i<16;++i) {
      bar->setBar(i,LED_YELLOW);
    }
    bar->writeDisplay();
    sleep_ms(1000);

    for (int i=16; i<23;++i) {
      bar->setBar(i,LED_RED);
    }
    bar->writeDisplay();
    sleep_ms(1000);

    // test brightness-levels
    bar->blinkRate(HT16K33_BLINK_1HZ);
    for (int i=0; i<16; ++i) {
      bar->setBrightness(i);
      bar->writeDisplay();
      sleep_ms(2000);
    }

    // cleanup
    bar->blinkRate(HT16K33_BLINK_OFF);
    bar->clear();
    bar->writeDisplay();
    return 0;
}
