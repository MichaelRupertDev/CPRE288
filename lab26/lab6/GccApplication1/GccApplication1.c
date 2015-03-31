/*
 * GccApplication1.c
 *
 * Created: 2/25/2015 12:09:23 PM
 *  Author: mbrupert
 */ 


#include <avr/io.h>
#include "lcd.h"
#include "util.h"
#include "math.h"


void ADC_init() {
	//Enable, start conversion, one shot, no interrupts, disable interrupts, prescale to 128
	ADCSRA = 0b11000111;
	
	ADMUX = 0b01000010;
}



int main(void)
{
	lcd_init();
	ADC_init();
	//int i = 0;
    while(1)
    {
		
//lcd_puts(2);
		ADC_init();
		//If ADSC changed to a 0, execute loop
		while (ADCSRA & (1<<ADSC)) {};
		
		unsigned char x = ADC;
		
		float y = 2.705007719 * pow(2.718, ((-002.73272149) * x));

		lprintf("Quant Val %d\n Distance: %d", x, y);
		wait_ms(20);
    }
}