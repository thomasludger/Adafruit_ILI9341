/*
  This example shows the use of a Adafruit_GFX custom font with the Japanese
  Hiragana characters in the Unicode code point range of 12353 - 12435.

  The custom font files in different point sizes is attached to this sketch
  as a header file. The font data has been created following the instructions here:
  https://www.youtube.com/watch?v=L8MmTISmwZ8

  The command line used is in the form:
  fontconvert C:\Windows\Fonts\sourceFont.ttf 12 12353 12435 > hiragana12.h

  Make sure the sourceFont contains the character range that is being extracted.

  Note that online converters for Adafruit_GFX compatible fonts are
  available but these typically only use characters in the range 32-127,
  and thus do not include the extended character sets available.

  The Arduino IDE uses UTF8 encoding for character strings.to be UTF-8
  encoded. See link here for details:

  https://playground.arduino.cc/Code/UTF-8

  Created by Bodmer 08/02/19

*/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// The custom font file attached to this sketch must be included
#include "hiragana10.h"
#include "hiragana12.h"
#include "hiragana16.h"

// Easily remembered names for the fonts
#define HIRAGANA10 &hiragana10pt8b
#define HIRAGANA12 &hiragana12pt8b
#define HIRAGANA16 &hiragana16pt8b

#ifdef ESP8266
   #define STMPE_CS 16 // D0
   #define TFT_CS   0  // D3
   #define TFT_DC   15 // D8
   #define SD_CS    2  // D4
#endif
#ifdef ESP32
   #define STMPE_CS 32
   #define TFT_CS   15
   #define TFT_DC   26
   #define SD_CS    14
#endif
#ifdef TEENSYDUINO
   #define TFT_DC   10
   #define TFT_CS   4
   #define STMPE_CS 3
   #define SD_CS    8
#endif
#ifdef ARDUINO_STM32_FEATHER
   #define TFT_DC   PB4
   #define TFT_CS   PA15
   #define STMPE_CS PC7
   #define SD_CS    PC5
#endif
#ifdef ARDUINO_NRF52832_FEATHER /* BSP 0.6.5 and higher! */
   #define TFT_DC   11
   #define TFT_CS   31
   #define STMPE_CS 30
   #define SD_CS    27
#endif
#if defined(ARDUINO_MAX32620FTHR) || defined(ARDUINO_MAX32630FTHR)
   #define TFT_DC   P5_4
   #define TFT_CS   P5_3
   #define STMPE_CS P3_3
   #define SD_CS    P3_2
#endif

// Anything else!
#if defined (__AVR_ATmega32U4__) || defined(ARDUINO_SAMD_FEATHER_M0) || defined (__AVR_ATmega328P__) || \
    defined(ARDUINO_SAMD_ZERO) || defined(__SAMD51__) || defined(__SAM3X8E__) || defined(ARDUINO_NRF52840_FEATHER)
   #define STMPE_CS 6
   #define TFT_CS   9
   #define TFT_DC   10
   #define SD_CS    5
#endif


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


void setup(void) {

  Serial.begin(115200);
  
  tft.begin();

  tft.setRotation(1);

}

void loop() {

  tft.fillScreen(ILI9341_BLACK);    // Clear screen

  tft.setFont(HIRAGANA12);          // Select the font
  tft.setCursor(0, 0);              // Set cursor to top left
  tft.println();                    // Drop cursor 1 text line

  String konnichiwa = "こんにちは";  // Define a string using hiragana script

  tft.println(konnichiwa);          // Print string

  tft.println("さようなら");         // Print Sayonara

  delay(2000);

}
