#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#include <Adafruit_GFX.h>           // Core graphics library
#include <Adafruit_TFTLCD.h>        // Hardware-specific library
#include <Fonts/FreeMonoBold9pt7b.h>

#define color_primary           0x70F3
#define color_dark              0x400D
#define color_light             0xAA99
#define color_bg                0xDEFB
#define color_bg_l              0xEF9D
#define color_warning           0xF8A8
#define color_pass              0x66c2
#define color_fail              0xF8A8

/* in the format of arduino pin:D2/3/4/5/6/7/8/9 -> hc154:U1/U2/U3/U4/A0/A1/A2/A3 */
#define RT1                     0b01110000
#define RT2                     0b01111000
#define RT3                     0b01110100
#define RT4                     0b01111100
#define RT5                     0b01110010
#define RT6                     0b01111010
#define RT7                     0b01110110
#define RT8                     0b01111110

// #define RT2_ON                  pinMode(34, OUTPUT);digitalWrite(34, HIGH);
// #define RT2_OFF                 pinMode(34, OUTPUT);digitalWrite(34, LOW);
#define DUT_ON                  pinMode(36, OUTPUT);digitalWrite(36, LOW);delay(500);
#define DUT_OFF                 pinMode(36, OUTPUT);digitalWrite(36, HIGH);delay(500);
#define ENA_ON                  pinMode(37, OUTPUT);digitalWrite(37, LOW);delay(1000);
#define ENA_OFF                 pinMode(37, OUTPUT);digitalWrite(37, HIGH);delay(500);

/* simulate a button press on boost converter to output on/off */
#define BOOST_OUTPUT_PRESS      pinMode(32, OUTPUT);pinMode(33, OUTPUT);digitalWrite(33, HIGH);delay(500);digitalWrite(33, LOW);delay(1600);

#define BOOST_OUTPUT_ON         pinMode(42, OUTPUT);digitalWrite(42, LOW);delay(500);
#define BOOST_OUTPUT_OFF        pinMode(42, OUTPUT);digitalWrite(42, HIGH);delay(500);

#define L1_ON                   pinMode(43, OUTPUT);digitalWrite(43, LOW);delay(500);
#define L1_OFF                  pinMode(43, OUTPUT);digitalWrite(43, HIGH);delay(500);
#define L2_ON                   pinMode(46, OUTPUT);digitalWrite(46, LOW);delay(500);
#define L2_OFF                  pinMode(46, OUTPUT);digitalWrite(46, HIGH);delay(500);
#define L3_ON                   pinMode(47, OUTPUT);digitalWrite(47, LOW);delay(500);
#define L3_OFF                  pinMode(47, OUTPUT);digitalWrite(47, HIGH);delay(500);

/* relays which control two waveform generators */
#define wave1                   DDRG|=(1<<PG0)|(1<<PG1)|(1<<PG2);PORTG&=!((1<<PG0)|(1<<PG1)|(1<<PG2));PORTG|=(1<<PG1);
#define wave2                   DDRG|=(1<<PG0)|(1<<PG1)|(1<<PG2);PORTG&=!((1<<PG0)|(1<<PG1)|(1<<PG2));PORTG|=(1<<PG2);
#define wave_off                DDRG|=(1<<PG0)|(1<<PG1)|(1<<PG2);PORTG&=!((1<<PG0)|(1<<PG1)|(1<<PG2));

// char* test_names[] = {"Voltage Measurement", "Contact Open & Close", "Key Press Test", "LED Test", "RS485 Test", "USB Test", "SD Test", "Display Test"};

#endif