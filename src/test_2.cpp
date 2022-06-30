#include "essentials.hpp"
#include "ui.hpp"
#include "adc.hpp"
#include "frequency.hpp"
#include "voltmeter.hpp"
#include "test_2.hpp"


static bool test_pass = true;
uint32_t a14 = 0;
uint32_t a15 = 0;

bool test_2(Adafruit_TFTLCD &tft, char* test_name) {
    tft.fillScreen(0x2104);

    tft.fillRect(0, 0, 320, 60, color_primary);
    tft.setCursor(30, 30);
    tft.setTextColor(0xffff);
    tft.println(test_name);

    /* X1 Test */
    tft.setCursor(10, 100);
    tft.println("X1 - X2");

    DUT_ON
    BOOST_OUTPUT_PRESS
    BOOST_OUTPUT_ON
    wave1
    delay(1500);
    
    init_timer1();
    init_adc();
    select_adc_13();
    start_adc();

    uint32_t t1 = millis();
    for (;;) {
        if (read) {
            read = false;
            /*
                scalar 72.52 derived from empirical data
                (sqrt(rms_sum/1000))=495.95 -> 35 VAC
            */
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

            float frequency = FREQUENCY_SCALAR_L * TRIGGER_HITS / period_sum;
            if (frequency >= 57.0 && frequency <= 63.0) {
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

            // for (auto i=0;i<BUFFER_LENGTH;i++) {
            //     Serial.print(i);
            //     Serial.print("\t");
            //     Serial.print(buffer[i]);
            //     Serial.print("\t"); 
            //     Serial.println();
            // }
            // Serial.print("count1:");
            // Serial.print("\t");
            // Serial.println(count1);
            // Serial.print("count2:");
            // Serial.print("\t");
            // Serial.println(count2);
            // Serial.print("rms:");
            // Serial.print("\t");
            // Serial.println(sqrt(rms_sum/1000));

            rms_sum = 0;
            rms_run = true;
            count1 = 0;
            count2 = 0;
            average_count = 0;
            period_sum = 0;
            break;
        }
        if (millis()-t1>=5000) {
            test_pass &= false;
            comm_lost(tft);
            break;
        }
    }

    L1_ON
    L2_ON
    L3_ON
    ENA_ON

    tft.setTextColor(0xffff);
    tft.setCursor(130, 190);
    tft.println("J2 ON");

    /* T1 (J2.1) ON TEST */
    tft.setTextColor(0xffff);
    tft.setCursor(10, 220);
    tft.println("J2.1");

    select_adc_14();
    start_adc();

    t1 = millis();
    for (;;) {
        if (read) {
            read = false;

            float rms = sqrt(rms_sum/1000)*RMS_SCALAR/1024;
            if (rms >= 24.0 && rms <= 40.0) {
                tft.setTextColor(color_pass);
            }
            else {
                tft.setTextColor(color_fail);
                test_pass &= false;
            }
            tft.setCursor(160, 220);
            tft.println(rms);
            tft.setCursor(270, 220);
            tft.println("VAC");

            // float frequency = FREQUENCY_SCALAR_L * TRIGGER_HITS / period_sum;
            // if (frequency >= 57.0 && frequency <= 63.0) {
            //     tft.setTextColor(color_pass);
            // }
            // else {
            //     tft.setTextColor(color_fail);
            //     test_pass &= false;
            // }
            // tft.setCursor(160, 240);
            // tft.println(frequency);
            // tft.setCursor(270, 240);
            // tft.println("Hz");

            rms_sum = 0;
            rms_run = true;
            count1 = 0;
            count2 = 0;
            average_count = 0;
            period_sum = 0;

            // for (auto i=0;i<BUFFER_LENGTH;i++) {
            //     Serial.print(i);
            //     Serial.print("\t");
            //     Serial.print(buffer[i]);
            //     Serial.print("\t"); 
            //     Serial.println();
            // }
            // Serial.print("count1:");
            // Serial.print("\t");
            // Serial.println(count1);
            // Serial.print("count2:");
            // Serial.print("\t");
            // Serial.println(count2);
            // Serial.print("rms:");
            // Serial.print("\t");
            // Serial.println(sqrt(rms_sum/1000));

            break;
        }
        if (millis()-t1>=5000) {
            comm_lost(tft);
            test_pass &= false;
            break;
        }
    }
    
    /* T3 (J2.3) ON TEST */
    tft.setTextColor(0xffff);
    tft.setCursor(10, 260);
    tft.println("J2.3");

    select_adc_15();
    start_adc();

    t1 = millis();
    for (;;) {
        if (read) {
            read = false;

            float rms = sqrt(rms_sum/1000)*RMS_SCALAR/1024;
            if (rms >= 24.0 && rms <= 40.0) {
                tft.setTextColor(color_pass);
            }
            else {
                tft.setTextColor(color_fail);
                test_pass &= false;
            }
            tft.setCursor(160, 260);
            tft.println(rms);
            tft.setCursor(270, 260);
            tft.println("VAC");

            // float frequency = FREQUENCY_SCALAR_L * TRIGGER_HITS / period_sum;
            // if (frequency >= 57.0 && frequency <= 63.0) {
            //     tft.setTextColor(color_pass);
            // }
            // else {
            //     tft.setTextColor(color_fail);
            //     test_pass &= false;
            // }
            // tft.setCursor(160, 280);
            // tft.println(frequency);
            // tft.setCursor(270, 280);
            // tft.println("Hz");

            rms_sum = 0;
            rms_run = true;
            count1 = 0;
            count2 = 0;
            average_count = 0;
            period_sum = 0;

            // for (auto i=0;i<BUFFER_LENGTH;i++) {
            //     Serial.print(i);
            //     Serial.print("\t");
            //     Serial.print(buffer[i]);
            //     Serial.print("\t"); 
            //     Serial.println();
            // }
            // Serial.print("count1:");
            // Serial.print("\t");
            // Serial.println(count1);
            // Serial.print("count2:");
            // Serial.print("\t");
            // Serial.println(count2);
            // Serial.print("rms:");
            // Serial.print("\t");
            // Serial.println(sqrt(rms_sum/1000));

            break;
        }
        if (millis()-t1>=5000) {
            comm_lost(tft);
            test_pass &= false;
            break;
        }
    }

    ENA_OFF

    tft.setTextColor(0xffff);
    tft.setCursor(130, 310);
    tft.println("J2 OFF");

    /* T1 (J2.1) OFF TEST */
    tft.setTextColor(0xffff);
    tft.setCursor(10, 340);
    tft.println("J2.1");

    select_adc_14();
    start_adc();

    t1 = millis();
    for (;;) {
        if (!rms_run) {
            read = false;
            stop_adc();                                     // frequency code not triggered
            float rms = sqrt(rms_sum/1000)*RMS_SCALAR/1024;
            if (rms >= 0.0 && rms <= 2.0) {
                tft.setTextColor(color_pass);
            }
            else {
                tft.setTextColor(color_fail);
                test_pass &= false;
            }
            tft.setCursor(160, 340);
            tft.println(rms);
            tft.setCursor(270, 340);
            tft.println("VAC");

            // float frequency = FREQUENCY_SCALAR_L * TRIGGER_HITS / period_sum;
            // if (frequency >= 57.0 && frequency <= 63.0) {
            //     tft.setTextColor(color_pass);
            // }
            // else {
            //     tft.setTextColor(color_fail);
            //     test_pass &= false;
            // }
            // tft.setCursor(160, 360);
            // tft.println(frequency);
            // tft.setCursor(270, 360);
            // tft.println("Hz");

            rms_sum = 0;
            rms_run = true;
            count1 = 0;
            count2 = 0;
            average_count = 0;
            period_sum = 0;

            // for (auto i=0;i<BUFFER_LENGTH;i++) {
            //     Serial.print(i);
            //     Serial.print("\t");
            //     Serial.print(buffer[i]);
            //     Serial.print("\t"); 
            //     Serial.println();
            // }
            // Serial.print("count1:");
            // Serial.print("\t");
            // Serial.println(count1);
            // Serial.print("count2:");
            // Serial.print("\t");
            // Serial.println(count2);
            // Serial.print("rms:");
            // Serial.print("\t");
            // Serial.println(sqrt(rms_sum/1000));

            break;
        }
        if (millis()-t1>=5000) {
            comm_lost(tft);
            test_pass &= false;
            break;
        }
    }

    /* T3 (J2.3) OFF TEST */
    tft.setTextColor(0xffff);
    tft.setCursor(10, 380);
    tft.println("J2.3");

    select_adc_15();
    start_adc();

    t1 = millis();
    for (;;) {
        if (!rms_run) {
            read = false;
            stop_adc();                                     // frequency code not triggered
            float rms = sqrt(rms_sum/1000)*RMS_SCALAR/1024;
            if (rms >= 0.0 && rms <= 2.0) {
                tft.setTextColor(color_pass);
            }
            else {
                tft.setTextColor(color_fail);
                test_pass &= false;
            }
            tft.setCursor(160, 380);
            tft.println(rms);
            tft.setCursor(270, 380);
            tft.println("VAC");

            // float frequency = FREQUENCY_SCALAR_L * TRIGGER_HITS / period_sum;
            // if (frequency >= 57.0 && frequency <= 63.0) {
            //     tft.setTextColor(color_pass);
            // }
            // else {
            //     tft.setTextColor(color_fail);
            //     test_pass &= false;
            // }
            // tft.setCursor(160, 400);
            // tft.println(frequency);
            // tft.setCursor(270, 400);
            // tft.println("Hz");

            rms_sum = 0;
            rms_run = true;
            count1 = 0;
            count2 = 0;
            average_count = 0;
            period_sum = 0;

            // for (auto i=0;i<BUFFER_LENGTH;i++) {
            //     Serial.print(i);
            //     Serial.print("\t");
            //     Serial.print(buffer[i]);
            //     Serial.print("\t"); 
            //     Serial.println();
            // }
            // Serial.print("count1:");
            // Serial.print("\t");
            // Serial.println(count1);
            // Serial.print("count2:");
            // Serial.print("\t");
            // Serial.println(count2);
            // Serial.print("rms:");
            // Serial.print("\t");
            // Serial.println(sqrt(rms_sum/1000));

            break;
        }
        if (millis()-t1>=5000) {
            comm_lost(tft);
            test_pass &= false;
            break;
        }
    }

    L1_OFF
    L2_OFF
    L3_OFF
    BOOST_OUTPUT_OFF
    BOOST_OUTPUT_PRESS
    DUT_OFF;
    wave_off

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