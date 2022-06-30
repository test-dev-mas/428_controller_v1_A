#ifndef VOLTMETER_H
#define VOLTMETER_H

#include <stdint.h>

void voltmeter_init();
uint16_t voltmeter_read();
void relay_call(uint8_t pins);
#endif