#ifndef TEST_3_H
#define TEST_3_H

#include <Adafruit_GFX.h>       // Core graphics library
#include <Adafruit_TFTLCD.h>    // Hardware-specific library

bool test_3(Adafruit_TFTLCD &tft, char* test_name);
void phase_test(Adafruit_TFTLCD &tft, uint16_t line, float limit1, float limit2);
void confirm_led(Adafruit_TFTLCD &tft, char* led_state);
#endif