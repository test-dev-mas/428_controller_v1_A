#include "essentials.hpp"

#include "ui.hpp"
#include "voltmeter.hpp"
#include "test_1.hpp"

static bool test_pass = true;

bool test_1(Adafruit_TFTLCD &tft, char* test_name) {
    tft.fillScreen(0x2104);

    tft.fillRect(0, 0, 320, 60, color_primary);
    tft.setCursor(30, 30);
    tft.setTextColor(0xffff);
    tft.println(test_name);
    
    DUT_ON

    relay_call(RT1);
    uint16_t adc_value = voltmeter_read();
    float adc_volt = adc_value * 0.083;

    if (adc_volt >= 23.0 && adc_volt <= 25) {
        tft.setTextColor(color_pass);
    }
    else {
        tft.setTextColor(color_fail);
        test_pass &= false;
    }

    tft.setCursor(10, 130);
    tft.println("J8.1");
    tft.setCursor(160, 130);
    tft.println(adc_volt);

    DUT_OFF

    if (test_pass) {
        /* draw an arrow */
        tft.fillCircle(160, 430, 25, color_primary);
        tft.drawLine(145, 430, 175, 430, 0xffff);
        tft.drawLine(160, 420, 175, 430, 0xffff);
        tft.drawLine(160, 440, 175, 430, 0xffff);

        /* 1 second timeout, test will proceed even without user input */
        touch(tft, 135, 185, 405, 455, 1000);
    }
    else {
        /* draw a cross */
        tft.fillCircle(160, 430, 25, color_warning);
        tft.drawLine(145, 415, 175, 445, 0xffff);
        tft.drawLine(145, 445, 175, 415, 0xffff);

        /* requires user input to proceed*/
        touch(tft, 135, 185, 405, 455);
    }
    
    return test_pass;
}