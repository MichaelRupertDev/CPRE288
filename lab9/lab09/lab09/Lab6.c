/*
 * Lab6.c
 *
 * Created: 3/2/2015 11:31:19 PM
 *  Author: be1
 */ 


#include <avr/io.h>
#include "lcd.h"
#include "util.h"
#include <math.h>

void ADC_init();
int ADC_read();

int main(void)
{
	float distance;
	int value = 0;
	
	ADC_init();
	lcd_init();
	int i;
    while(1){
		for(i=0;i<5;i++){
			value += ADC_read();	
		}
		
		value = value / 5;

		distance = (float) 36469*pow(value,-1.17); //1.156

		lprintf("Sensor: %d\nDistance: %fcm", value, distance);
		wait_ms(100);
	}
}


void ADC_init() {
	
	ADMUX = 0b11000010;// Set up refevcence voltage and channel
	ADCSRA = 0b10000111;// Enable
}
int ADC_read() {
	
	ADMUX = 0b11000010; // Select 
	ADCSRA |= 0b01000000; // Start sensor
	while (ADCSRA & 0b01000000)	{}
	return ADC; 
}