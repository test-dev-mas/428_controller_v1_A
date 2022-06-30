#include "essentials.hpp"
#include "voltmeter.hpp"

#define CS 20                               //Selection Pin
#define DOUT 51                              //MOSI // SDI of Multimeter click is connected to here
#define DIN  50                              //MISO // SDO of Multimeter click is connected to here
#define SCK    PB1                            //Clock

void voltmeter_init() {
    pinMode(2, OUTPUT);                         // E1/E2 ON U1/U2
    pinMode(6, OUTPUT);                         // A0 ON U1/U2
    pinMode(7, OUTPUT);                         // A1 ON U1/U2
    pinMode(8, OUTPUT);                         // A2 ON U1/U2
    pinMode(9, OUTPUT);                         // A3 ON U1/U2
    pinMode(34, OUTPUT);                        // COIL ON RT2
    pinMode(35, OUTPUT);                        // COIL ON RT2

    digitalWrite(34, HIGH);                     // TURN ON RT2 (energize coil, 34 high, 35 low)

    pinMode(CS, OUTPUT);                        // set up multimeter click
    pinMode(DOUT, OUTPUT);
    pinMode(DIN, INPUT);
    DDRB |= (1<<SCK);
    digitalWrite(CS,HIGH);
    digitalWrite(DOUT,LOW);
    PORTB &= ~(1<<SCK);
}

uint16_t voltmeter_read(){
    int adcvalue3 = -2045;
    byte commandbits3 = B11000000;          //command bits - start, mode, chn (3), dont care (3)
    
    int channel3 = 1;                       //allow channel selection
    commandbits3|=((channel3-0)<<3);
    digitalWrite(CS,LOW);                   //Select adc
    
    for (int i=7; i>=3; i--){
    digitalWrite(DOUT,commandbits3&1<<i);   // setup bits to be written
    
    PORTB |= (1<<SCK);                      //cycle clock
    PORTB &= ~(1<<SCK);    
    }
    PORTB |= (1<<SCK);                      //ignores 2 null bits
    PORTB &= ~(1<<SCK);
    PORTB |= (1<<SCK);  
    PORTB &= ~(1<<SCK);
    
    for (int i=11; i>=0; i--){              //read bits from adc
    adcvalue3+=digitalRead(DIN)<<i;
    
    PORTB |= (1<<SCK);                      //cycle clock
    PORTB &= ~(1<<SCK);
    }
    digitalWrite(CS, HIGH);                 //turn off device
    // Serial.println(adcvalue3, BIN);
    return adcvalue3;
}

void relay_call(uint8_t pins) {
    digitalWrite(2, (pins>>7));                 // U1/U2  
    // digitalWrite(3, (pins&0x40)>>6);            // 
    // digitalWrite(4, (pins&0x20)>>5);            // 
    // digitalWrite(5, (pins&0x10)>>4);            // 
    digitalWrite(6, (pins&0x08)>>3);            // A0 on Un
    digitalWrite(7, (pins&0x04)>>2);            // A1 on Un
    digitalWrite(8, (pins&0x02)>>1);            // A2 on Un
    digitalWrite(9, (pins&0x01));               // A3 on Un
    delay(500);                                 // allow some time for voltage to stablize
}