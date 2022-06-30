#include "essentials.hpp"

#include "ui.hpp"
#include "frequency.hpp"
#include "voltmeter.hpp"
#include "test_3.hpp"

static bool test_pass = true;

bool test_3(Adafruit_TFTLCD &tft, char* test_name) {
    tft.fillScreen(0x2104);

    tft.fillRect(0, 0, 320, 60, color_primary);
    tft.setCursor(30, 30);
    tft.setTextColor(0xffff);
    tft.println(test_name);

    /* X1 TEST */
    tft.setCursor(10, 100);
    tft.println("X1 - X2");

    DUT_ON
    BOOST_OUTPUT_PRESS
    BOOST_OUTPUT_ON
    wave2
    delay(1500);

    init_timer1();
    init_adc();
    select_adc_13();
    start_adc();

    uint32_t t1 = millis();
    for (;;) {
        if (read) {
            read = false;

            float rms = sqrt(rms_sum/1000)*RMS_SCALAR/1024;
            if (rms >= 26.0 && rms <= 40.0) {
                tft.setTextColor(color_pass);
            }
            else {
                tft.setTextColor(color_fail);
                test_pass &= false;
            }
            tft.setCursor(160, 100);
            tft.println(rms);
            tft.setCursor(270, 100);
            tft.println("VAC");

            float frequency = FREQUENCY_SCALAR_H * TRIGGER_HITS / period_sum;
            if (frequency >= 480.0 && frequency <= 520.0) {
                tft.setTextColor(color_pass);
            }
            else {
                tft.setTextColor(color_fail);
                test_pass &= false;
            }
            tft.setCursor(160, 120);
            tft.println(frequency);
            tft.setCursor(270, 120);
            tft.println("Hz");

            for (auto i=0;i<BUFFER_LENGTH;i++) {
                Serial.print(i);
                Serial.print("\t");
                Serial.print(buffer[i]);
                Serial.print("\t"); 
                Serial.println();
            }
            Serial.print("count1:");
            Serial.print("\t");
            Serial.println(count1);
            Serial.print("count2:");
            Serial.print("\t");
            Serial.println(count2);
            Serial.print("rms:");
            Serial.print("\t");
            Serial.println(sqrt(rms_sum/1000));

            break;
        }
        if (millis()-t1>=5000) {
            comm_lost(tft);
            test_pass &= false;
            break;
        }
    }
    
    L1_ON
    L2_ON
    L3_ON
    ENA_ON

    tft.setTextColor(0xFFFF);
    tft.setCursor(10, 155);
    tft.println("ALL PHASES");
    phase_test(tft, 170, 21.0, 26.0);

    tft.setTextColor(0xFFFF);
    tft.setCursor(10, 225);
    tft.println("L1 MISSING");
    L1_OFF
    phase_test(tft, 240, 0.0, 1.0);
    L1_ON

    tft.setTextColor(0xFFFF);
    tft.setCursor(10, 295);
    tft.println("L2 MISSING");
    L2_OFF
    phase_test(tft, 310, 0.0, 1.0);
    L2_ON

    tft.setTextColor(0xFFFF);
    tft.setCursor(10, 365);
    tft.println("L3 MISSING");
    L3_OFF
    phase_test(tft, 380, 0.0, 1.0);
    L3_ON

    delay(500);

    L3_OFF
    L2_OFF
    L1_OFF
    BOOST_OUTPUT_OFF
    BOOST_OUTPUT_PRESS
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

void phase_test(Adafruit_TFTLCD &tft, uint16_t line, float limit1, float limit2) {
    relay_call(RT3);
    uint16_t adc_value = voltmeter_read();
    float adc_volt = adc_value / 12.047;

    if (adc_volt >= limit1 && adc_volt <= limit2) {
        tft.setTextColor(color_pass);
        tft.setCursor(160, line);
        tft.println("pass");
    }
    else {
        tft.setTextColor(color_fail);
        tft.setCursor(150, line);
        tft.println("fail");
        test_pass &= false;
    }


    // relay_call(RT5);
    // adc_value = voltmeter_read();
    // adc_volt = adc_value / 12.047;

    // if (adc_volt >= limit1 && adc_volt <= limit2) {
    //     tft.setTextColor(color_pass);
    // }
    // else {
    //     tft.setTextColor(color_fail);
    //     test_pass &= false;
    // }

    // tft.setCursor(10, line+20);
    // tft.println("J6.8");
    // tft.setCursor(160, line+20);
    // tft.println(adc_volt);

    // relay_call(RT6);
    // adc_value = voltmeter_read();
    // adc_volt = adc_value / 12.047;

    // if (adc_volt >= limit1 && adc_volt <= limit2) {
    //     tft.setTextColor(color_pass);
    // }
    // else {
    //     tft.setTextColor(color_fail);
    //     test_pass &= false;
    // }

    // tft.setCursor(10, line+40);
    // tft.println("J20.5");
    // tft.setCursor(160, line+40);
    // tft.println(adc_volt);
}