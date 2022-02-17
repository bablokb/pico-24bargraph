/*!
 * This is a subset and simplified version of Adafruit's
 * "LED Backpack library for Arduino" adapted for the
 * Raspberry Pi Pico.
 *
 * Author: Bernhard Bablok
 *
 * https://github.com/bablokb/pico-24bargraph
 *
 * Original source: https://github.com/adafruit/Adafruit_LED_Backpack
 *
 * @file Adafruit_LEDBackpack.cpp
 *
 * @mainpage Adafruit LED Backpack library for Arduino.
 *
 * @section intro_sec Introduction
 *
 * This is an Arduino library for our I2C LED Backpacks:
 * ----> http://www.adafruit.com/products/
 * ----> http://www.adafruit.com/products/
 *
 * These displays use I2C to communicate, 2 pins are required to
 * interface. There are multiple selectable I2C addresses. For backpacks
 * with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
 * with 3 Address Select pins: 0x70 thru 0x77
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * @section author Author
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 *
 * @section license License
 *
 * MIT license, all text above must be included in any redistribution
 *
 */

#include "Pico_24bargraph.h"
#include "I2CDevice.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) ///< Bit-value if not defined by Arduino
#endif

void Pico_LEDBackpack::setBrightness(uint8_t b) {
  if (b > 15)
    b = 15; // limit to max brightness
  uint8_t buffer = HT16K33_CMD_BRIGHTNESS | b;
  _i2c_dev->write(&buffer, 1);
}

void Pico_LEDBackpack::blinkRate(uint8_t b) {
  if (b > 3)
    b = 0; // turn off if not sure
  uint8_t buffer = HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1);
  _i2c_dev->write(&buffer, 1);
}

Pico_LEDBackpack::Pico_LEDBackpack(I2CDevice* device) {
  _i2c_dev = device;

  // turn on oscillator
  uint8_t buffer[1] = {0x21};
  _i2c_dev->write(buffer, 1);

  // internal RAM powers up with garbage/random values.
  // ensure internal RAM is cleared before turning on display
  // this ensures that no garbage pixels show up on the display
  // when it is turned on.

  clear();
  writeDisplay();
  blinkRate(HT16K33_BLINK_OFF);
  setBrightness(15); // max brightness
}

void Pico_LEDBackpack::writeDisplay(void) {
  uint8_t buffer[17];

  buffer[0] = 0x00; // start at address $00

  for (uint8_t i = 0; i < 8; i++) {
    buffer[1 + 2 * i] = displaybuffer[i] & 0xFF;
    buffer[2 + 2 * i] = displaybuffer[i] >> 8;
  }
  _i2c_dev->write(buffer, 17);
}

void Pico_LEDBackpack::clear(void) {
  for (uint8_t i = 0; i < 8; i++) {
    displaybuffer[i] = 0;
  }
}

/******************************* 24 BARGRAPH OBJECT */

Pico_24bargraph::Pico_24bargraph(I2CDevice* i2cdev): Pico_LEDBackpack(i2cdev) {}

void Pico_24bargraph::setBar(uint8_t bar, uint8_t color) {
  uint16_t a, c;

  if (bar < 12)
    c = bar / 4;
  else
    c = (bar - 12) / 4;

  a = bar % 4;
  if (bar >= 12)
    a += 4;

  if (color == LED_RED) {
    // Turn on red LED.
    displaybuffer[c] |= _BV(a);
    // Turn off green LED.
    displaybuffer[c] &= ~_BV(a + 8);
  } else if (color == LED_YELLOW) {
    // Turn on red and green LED.
    displaybuffer[c] |= _BV(a) | _BV(a + 8);
  } else if (color == LED_OFF) {
    // Turn off red and green LED.
    displaybuffer[c] &= ~_BV(a) & ~_BV(a + 8);
  } else if (color == LED_GREEN) {
    // Turn on green LED.
    displaybuffer[c] |= _BV(a + 8);
    // Turn off red LED.
    displaybuffer[c] &= ~_BV(a);
  }
}
