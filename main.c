
#define F_CPU 16000000UL

#define keypadDirectionRegisterR DDRB
#define keypadPortControlR PORTB
#define keypadPortValueR PINB

#define keypadDirectionRegisterC DDRC
#define keypadPortControlC PORTC
#define keypadPortValueC PINC

#define LEDDirectionRegister DDRD
#define LEDPort PORTD

#include <avr/io.h>
#include <util/delay.h>

void keypadScan();

int main(void){

    // Initialize LED
    LEDDirectionRegister = (1<<0);

    // Keypad initialization
    keypadDirectionRegisterR = (1<<0) | (1<<1) | (1<<2) | (1<<3);
    keypadDirectionRegisterC = (0<<0) | (0<<1) | (0<<2) | (0<<3);

    keypadPortControlR = (0<<0) | (0<<1) | (0<<2) | (0<<3);
    keypadPortControlC = (1<<0) | (1<<1) | (1<<2) | (1<<3);


    while(1){
        keypadScan();
    }

}

void keypadScan(){

    // Store value for column
    uint8_t keyPressCodeC = keypadPortValueC;

    keypadDirectionRegisterC ^= (1<<0) | (1<<1) | (1<<2) | (1<<3);
    keypadDirectionRegisterR ^= (1<<0) | (1<<1) | (1<<2) | (1<<3); 

    keypadPortControlC ^= (1<<0) | (1<<1) | (1<<2) | (1<<3);
    keypadPortControlR ^= (1<<0) | (1<<1) | (1<<2) | (1<<3);
    
    _delay_ms(5);

    // Store value for row
    int temp = keypadPortValueR;
    uint8_t keyPressCodeR = temp << 4;

    // Add value for column and row
    uint8_t keyPressCode = keyPressCodeC | keyPressCodeR;

    uint8_t blinkDuration = 0;

    // Comparison and resultant action

    // Column one
    if(keyPressCode == 0b11101110){
        blinkDuration = 1;
    }
    if(keyPressCode == 0b11011110){
        blinkDuration = 2;
    }
    if(keyPressCode == 0b10111110){
        blinkDuration = 3;
    }
    if(keyPressCode == 0b01111110){
        blinkDuration = 4;
    }

    // Column two
    if(keyPressCode == 0b11101101){
        blinkDuration = 5;
    }
    if(keyPressCode == 0b11011101){
        blinkDuration = 6;
    }
    if(keyPressCode == 0b10111101){
        blinkDuration = 7;
    }
    if(keyPressCode == 0b01111101){
        blinkDuration = 8;
    }

    // Column three
    if(keyPressCode == 0b11101011){
        blinkDuration = 9;
    }
    if(keyPressCode == 0b11011011){
        blinkDuration = 10;
    }
    if(keyPressCode == 0b10111011){
        blinkDuration = 11;
    }
    if(keyPressCode == 0b01111011){
        blinkDuration = 12;
    }

    // Column four
    if(keyPressCode == 0b11100111){
        blinkDuration = 13;
    }
    if(keyPressCode == 0b11010111){
        blinkDuration = 14;
    }
    if(keyPressCode == 0b10110111){
        blinkDuration = 15;
    }
    if(keyPressCode == 0b01110111){
        blinkDuration = 16;
    }

    // Toggles the led on and off
    if (keyPressCode < 0xFF){
        int i;
        for (i = 0; i < blinkDuration; i++){
            _delay_ms(50);
            LEDPort ^= (1<<0);
            _delay_ms(50);
            LEDPort ^= (1<<0);
        }
    }
}