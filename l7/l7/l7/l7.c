/*
 * l7.c
 *
 * Created: 10/27/2014 5:05:02 PM
 *  Author: be1
 */ 


#include <avr/io.h>
#include "util.h"
#include "lcd.h"
#include "open_interface.h"
#include "math.h"
#include <avr/interrupt.h>

volatile unsigned redge = 0;
volatile unsigned fedge = 0;
volatile enum {LOW,HIGH,DONE} state;
	volatile int numOvf = 0;


void TC_init();
void send_pulse();
unsigned int time2dist(unsigned int time);

ISR (TIMER1_CAPT_vect){
	if (state == LOW){
			redge = ICR1;
			state = HIGH;
			TCCR1B &= 0b10111111;
	}
	
	else if(state == HIGH){
		fedge = ICR1;
		state = DONE;
		TCCR1B |= 0b01000000;
	}
	
}

ISR (TIMER1_OVF_vect) {
	numOvf++;
}




int main(void)
{
	unsigned int distance = 0;
	int distInCM = 0;
	int pulseWidthTC= 0;
	double pulseWidthMS = 0;
    lcd_init();
	TC_init();
	while(1){
		cli();
		state = LOW;
		send_pulse();
		sei();
		while(state != DONE);
		
		distance = time2dist((fedge-redge)/2);
		distInCM = 0.1059*distance - 69.639;
		pulseWidthTC = (fedge-redge);
		pulseWidthMS = (double) distInCM/26.923;
		lprintf("Distance: %u\nPulse Width: %d\nPulse Width: %0.1f ms\nOverflows: %d", distInCM, pulseWidthTC, pulseWidthMS, numOvf);
		wait_ms(200);
		
	}
	
}

void TC_init() {
	TCCR1A = 0b00000000;
	TCCR1B = 0b11000100;
	TCCR1C = 0;
	TIMSK = 0b00100100;
}

void send_pulse()
{
	//TIMSK &= 0b11011111;
	DDRD |=	0x10; //	set	PD4	as	output
	PORTD |= 0x10; //	set	PD4	to	high
	wait_ms(3); //	wait
	PORTD &= 0xEF; //	set	PD4	to	low
	DDRD &=	0xEF; //	set	PD4	as	input
	TIFR |= 0b00111100;
	
}

unsigned int time2dist(unsigned time)
{
	int dist;
	dist = round(time*((256.0/16000000)*340000));
	return dist;
}