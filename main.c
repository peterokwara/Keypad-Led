
#define F_CPU 16000000UL

#define KeypadDirectionRegister DDRD
#define KeypadPortControl PORTD
#define KeypadPortValue PIND

#define LEDDirectionRegister DDRB
#define LEDPort PORTB

#include <avr/io.h>

void KeypadScan();

int main(void){

    // Initialize LED
    LEDDirectionRegister = (1<<0);
    LEDPort = (1<<0);

    while(1){

    }

}

void KeypadScan(){

}