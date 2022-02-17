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
 * @file Adafruit_LEDBackpack.h
 *
 * Part of Adafruit's Arduino library for our I2C LED Backpacks:
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
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 *
 * MIT license, all text above must be included in any redistribution
 */

#ifndef Pico_24bargraph_h
#define Pico_24bargraph_h

#include "I2CDevice.h"

#define LED_ON 1  ///< GFX color of lit LED segments (single-color displays)
#define LED_OFF 0 ///< GFX color of unlit LED segments (single-color displays)

#define LED_RED 1    ///< GFX color for red LED segments (bi-color displays)
#define LED_YELLOW 2 ///< GFX color for yellow LED segments (bi-color displays)
#define LED_GREEN 3  ///< GFX color for green LED segments (bi-color displays)

#define HT16K33_BLINK_CMD 0x80       ///< I2C register for BLINK setting
#define HT16K33_BLINK_DISPLAYON 0x01 ///< I2C value for steady on
#define HT16K33_BLINK_OFF 0          ///< I2C value for steady off
#define HT16K33_BLINK_2HZ 1          ///< I2C value for 2 Hz blink
#define HT16K33_BLINK_1HZ 2          ///< I2C value for 1 Hz blink
#define HT16K33_BLINK_HALFHZ 3       ///< I2C value for 0.5 Hz blink

#define HT16K33_CMD_BRIGHTNESS 0xE0 ///< I2C register for BRIGHTNESS setting

#define SEVENSEG_DIGITS 5 ///< # Digits in 7-seg displays, plus NUL end

/*!
    @brief  Class encapsulating the raw HT16K33 controller device.
*/
class Pico_LEDBackpack {
public:
  /*!
    @brief  Constructor for HT16K33 devices.
  */
  Pico_LEDBackpack(I2CDevice* device);

  /*!
    @brief  Set display brightness.
    @param  b  Brightness: 0 (min) to 15 (max).
  */
  void setBrightness(uint8_t b);

  /*!
    @brief  Set display blink rate.
    @param  b  One of:
               HT16K33_BLINK_DISPLAYON = steady on
               HT16K33_BLINK_OFF       = steady off
               HT16K33_BLINK_2HZ       = 2 Hz blink
               HT16K33_BLINK_1HZ       = 1 Hz blink
               HT16K33_BLINK_HALFHZ    = 0.5 Hz blink
  */
  void blinkRate(uint8_t b);

  /*!
    @brief  Issue buffered data in RAM to display.
  */
  void writeDisplay(void);

  /*!
    @brief  Clear display.
  */
  void clear(void);

  uint16_t displaybuffer[8]; ///< Raw display data

protected:
  I2CDevice *_i2c_dev = NULL; ///< Pointer to I2C bus interface
};

/*!
    @brief  Class for 24-element bargraph displays.
*/
class Pico_24bargraph : public Pico_LEDBackpack {
public:
  /*!
    @brief  Constructor for 24-element bargraph displays.
  */
  Pico_24bargraph(I2CDevice* i2cdev);

  /*!
    @brief  Set color a single bar (dot).
    @param  bar    Bar index (0 to 23).
    @param  color  Bar color: LED_OFF, LED_GREEN, LED_YELLOW or LED_RED.
  */
  void setBar(uint8_t bar, uint8_t color);
};

#endif // Pico_24bargraph_h
