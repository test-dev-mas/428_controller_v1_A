#include <avr/interrupt.h>
#include "frequency.hpp"

volatile bool read = false;
volatile bool triggered = false;
extern volatile bool rms_run = true;
volatile uint16_t adc_temp = 0;
volatile uint16_t adc_last = 0;
volatile uint16_t count1 = 0;
volatile uint16_t count2 = 0;
volatile uint16_t t_s = 0;
volatile uint32_t period = 0;
volatile uint32_t period_sum = 0;
volatile uint16_t buffer[BUFFER_LENGTH] = {0};
volatile uint16_t average[10] = {0};
volatile uint16_t average_count = 0;
volatile uint16_t adc_sum = 0;
volatile uint16_t adc_average = 0;
volatile uint16_t adc_average_last = 0;
volatile uint32_t rms_sum = 0;
volatile uint32_t rms_temp = 0;
volatile uint16_t adc_rms_temp = 0;

void init_adc() {
    ADMUX = 0;
    ADCSRA = 0;
    ADCSRB = 0;

    ADMUX |= (1<<REFS0);                                        // select AVCC as ADC reference
                                       
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1);                            // ADC clock prescaler: 128
    ADCSRA |= (1 << ADATE);                                     // enable auto trigger
    ADCSRA |= (1 << ADIE);                                      // enable interrupts when measurement complete
}

void select_adc_13() {
    ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3)|(1<<MUX4)|(1<<MUX5));
    ADMUX |= (1<<MUX0);                              
    ADMUX |= (1<<MUX2);
    ADCSRB |= (1<<MUX5);
}

void select_adc_14() {
    ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3)|(1<<MUX4)|(1<<MUX5));
    ADMUX |= (1<<MUX1);                                    
    ADMUX |= (1<<MUX2);
    ADCSRB |= (1<<MUX5);
}

void select_adc_15() {
    ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3)|(1<<MUX4)|(1<<MUX5));
    ADMUX |= (1<<MUX0);                                     
    ADMUX |= (1<<MUX1);
    ADMUX |= (1<<MUX2);
    ADCSRB |= (1<<MUX5);
}

void init_timer1() {
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= (1 << CS11);                                      // clk/8
    TCNT1 = 0;                                                  // initialize         
}

void start_adc() {
    ADCSRA |= (1<<ADEN);                                        // enable ADC
    ADCSRA |= (1<<ADSC);
}

void stop_adc() {
    ADCSRA &= ~(1<<ADEN); 
}

ISR(ADC_vect) {
    adc_temp = ADCL;
    adc_temp += (ADCH<<8);

    // Serial.println(adc_temp);

    average[average_count++]= adc_temp;
    if (average_count >= 10) {
        average_count = 0;
    }
    for (auto i=0;i<10;i++) {
        adc_sum += average[i];
    }
    adc_average = adc_sum/10;
    adc_sum = 0;

    if (adc_average > (TRIGGER_POINT-TRIGGER_RANGE) && adc_average < (TRIGGER_POINT+TRIGGER_RANGE) && adc_average >= adc_average_last) {
        if (triggered) {
            period = TCNT1 - t_s;
            if (period > 200) {
                period_sum += period;
                buffer[count1++] = period;
                // count1++;
            }
            triggered = false;
            
            if (count1 >= TRIGGER_HITS) {
                stop_adc();
                triggered = false;
                read = true;
            }
        }
        else {
            t_s = TCNT1;
            triggered = true;
        }
    }
    adc_average_last = adc_average;

    if (rms_run) {
        rms_temp = adc_temp;
        // buffer[count2] = adc_temp;
        rms_sum += rms_temp * rms_temp;
        if (++count2>=1000) {
            rms_run = false;
        }
    }
    // count2++;
}