/*  V1.A
    minor changes
*/

#include <Adafruit_GFX.h>       // Core graphics library
#include <Adafruit_TFTLCD.h>    // Hardware-specific library
#include <avr/wdt.h>

#include "src/essentials.hpp"
#include "src/voltmeter.hpp"
#include "src/start.hpp"
#include "src/end.hpp"
#include "src/test_1.hpp"
#include "src/test_2.hpp"
#include "src/test_3.hpp"

#define LCD_CS              21               // Chip Select
#define LCD_CD              19               // Command/Data
#define LCD_WR              18               // LCD Write
#define LCD_RD              17               // LCD Read
#define LCD_RESET           16            //

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

char* version_number = "Ver. 1.A";

void setup() {
    voltmeter_init();
    Serial.begin(115200);

    tft.reset();
    uint16_t identifier = tft.readID();
    tft.begin(identifier);

    start(tft, version_number);

    if (!(test_1(tft, "Input Voltage Test"))) {
        reset_controller();
    }
    if (!(test_2(tft, "Output (J2) Test"))) {
        reset_controller();
    }
    if (!(test_3(tft, "Missing Phase Test"))) {
        reset_controller();
    }

    end(tft);
    reset_controller();

}

void loop() {
}

void reset_controller() {
    wdt_enable(WDTO_15MS);
    while (1) {
        //
    }
}

