#ifndef FREQUENCY_H
#define FREQUENCY_H

#include <stdint.h>

#define BUFFER_LENGTH           100
#define TRIGGER_HITS            50
#define TRIGGER_RANGE           50
#define TRIGGER_POINT           311
#define FREQUENCY_SCALAR_L      1971383.1
#define FREQUENCY_SCALAR_H      2000000.1
#define RMS_SCALAR              66.17

extern volatile bool read;
extern volatile bool triggered;
extern volatile bool rms_run;
extern volatile uint16_t adc_temp;
extern volatile uint16_t adc_last;
extern volatile uint16_t count1;
extern volatile uint16_t count2;
extern volatile uint16_t t_s;
extern volatile uint32_t period;
extern volatile uint32_t period_sum;
extern volatile uint16_t buffer[BUFFER_LENGTH];
extern volatile uint16_t average[10];
extern volatile uint16_t average_count;
extern volatile uint16_t adc_sum;
extern volatile uint16_t adc_average;
extern volatile uint16_t adc_average_last;
extern volatile uint32_t rms_sum;
extern volatile uint32_t rms_temp;
extern volatile uint16_t adc_rms_temp;

void init_adc();
void select_adc_13();
void select_adc_14();
void select_adc_15();
void init_timer1();
void start_adc();
void stop_adc();

#endif