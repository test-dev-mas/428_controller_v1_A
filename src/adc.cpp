#include "adc.hpp"
#include <avr/io.h>

// void init_adc() {
//     ADCSRA = 0;
//     ADMUX |= (1<<REFS0);                                        // select AVCC as ADC reference
//     ADMUX |= (1<<MUX1);                                         // select ADC2 as ADC input
//     ADCSRA |= (1<<ADPS2)|(1<<ADPS1);                 // ADC clock prescaler: 128
//     ADCSRA |= (1 << ADATE);                                     // enable auto trigger
//     ADCSRA |= (1 << ADIE);                                      // enable interrupts when measurement complete
//     ADCSRA |= (1<<ADEN);                                        // enable ADC
// }

// void init_timer1() {
//     TCCR1A = 0;
//     TCCR1B = 0;
//     TCCR1B |= (1 << CS11);                                      // clk/8
//     TCNT1 = 0;                                                  // initialize         
// }

// void start_adc() {
//     ADCSRA |= (1<<ADSC);
// }

// void stop_adc() {
//     ADCSRA &= ~(1<<ADEN); 
// }