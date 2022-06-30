#ifndef TEST_2_H
#define TEST_2_H

#include <Adafruit_GFX.h>       // Core graphics library
#include <Adafruit_TFTLCD.h>    // Hardware-specific library

bool test_2(Adafruit_TFTLCD &tft, char* test_name);
void init_adc();
void select_adc_13();
void select_adc_14();
void select_adc_15();
void init_timer1();
void start_adc();
void stop_adc();

#endif