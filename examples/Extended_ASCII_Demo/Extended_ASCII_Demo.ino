/*
  This example shows the use of a Adafruit_GFX custom font with a
  character code range of 32 - 255, this means accented characters
  (amongst others) are available.

  The custom font files are attached to this sketch as a header file. The
  font data has been created following the instructions here:
  https://www.youtube.com/watch?v=L8MmTISmwZ8

  Note that online converters for Adafruit_GFX compatible fonts are
  available but these typically only use characters in the range 32-127,
  and thus do not include the accented characters. These online converters
  can however still be used with this sketch but the example characters
  used must be changed.

  The Arduino IDE uses UTF8 encoding for characters in the range
  128 to 255. See link here for details:

  https://playground.arduino.cc/Code/UTF-8

  To sumarise, UTF-8 encoded characters occupy more than 1 byte so care must
  be taken:

     char c = 'µ';          // Wrong
     char bad[4] = "5µA";   // Wrong
     char good[] = "5µA";   // Good
     String okay = "5µA";   // Good

  Created by Bodmer 08/02/19

*/

#define TEST_TEXT "ßäöü ñâàå"   // Text that will be printed on screen in the font

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// The custom font files attached to this sketch must be included
// They only occupy memory if the sketch uses them.
#include "MyFont09.h"
#include "MyFont10.h"
#include "MyFont12.h"

// Easily remembered names for the fonts
#define MYFONT9  &myFont9pt8b
#define MYFONT10 &myFont10pt8b
#define MYFONT12 &myFont12pt8b

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

  Serial.begin(250000);
  
  tft.begin();

  tft.setRotation(1);

  tft.setAttribute(UTF8_ENABLE , true);
  tft.setAttribute(CP437_ENABLE, true);
}

void loop() {

  tft.setTextColor(ILI9341_WHITE); // white characters

  tft.fillScreen(ILI9341_BLUE);    // Clear screen

  //tft.setFont(MYFONT9);          // Select the font
  tft.setFont(MYFONT10);           // Select the font
  //tft.setFont(MYFONT12);         // Select the font

  tft.setCursor(0,0);
  tft.println();                   // Drop cursor 1 line

  tft.println("ÿâäàå¡");           // Print test characters
  tft.println(TEST_TEXT);
  tft.println(12345);

  tft.println("Śś abc ŜŝŞ");  // Test with some out-of-range characters
                              // (only " abc " will be printed)

  tft.println("Hello");

  delay(2000);
}
