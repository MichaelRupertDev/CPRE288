/*
 * lab09.c
 *
 * Created: 3/25/2015 12:31:42 PM
 *  Author: be1
 */ 


#include <avr/io.h>
#include "lcd.h"
#include "util.h"
#include <string.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
//#include "open_interface.h"
#include "math.h"
#include "methods.h"

// #define CLOCK_COUNT 15625
// #define CHECK_COUNT 3125
// #define TOP 43000

volatile char button = 0;
volatile char prev = 0;

volatile unsigned redge = 0;
volatile unsigned fedge = 0;
volatile enum {LOW,HIGH,DONE} state;
volatile int numOvf = 0;

unsigned pulse_width;

ISR (TIMER3_COMPA_vect) {

	// Insert interrupt handler code for checking push buttons here
	
	button = read_push_buttons();
	if(button == prev){
		button = 0;
	}
	
	//prev = button;
	char msg[40];
	//char prev = 0;
	int i;
	
	switch(button){
		
		case 6:
		strcpy(msg,"Yes\r");
		break;
		
		case 5:
		strcpy(msg, "No\r");
		break;
		
		case 4:
		strcpy(msg,"Blue, no green, Ahhhhh!!!\r");
		break;
		
		case 3:
		strcpy(msg,"CYCLONE STATE\r");
		break;
		
		case 2:
		strcpy(msg,"Everything is awesomeeeeeee\r");
		break;
		
		case 1:
		strcpy(msg,"Making my way downtown walking fast\r");
		break;
		
		case 0:
		msg[0] = '\0';
		break;
		
	}
	if(button!=0){
		lprintf(msg);
		for(i=0; i<strlen(msg); i++) {
			serial_putc(msg[i]);
		}
		serial_putc(10);
		prev = button;
	}

}

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


int main(void)
{
	//timer_init();
	serial_init();
	ADC_init();
	lcd_init();
	TC_init();
	timer3_init();

	float irDistance;
	int value = 0;

	unsigned int distance = 0;
	int distInCM = 0;
	int pulseWidthTC= 0;
	double pulseWidthMS = 0;

	float angle = 0;

	while (1) {

		//Pulse the shit out of the sensor

		cli();
		state = LOW;
		send_pulse();
		sei();
		while(state != DONE);
		
		distance = time2dist((fedge-redge)/2);
		distInCM = 0.1059*distance - 69.639;
		pulseWidthTC = (fedge-redge);
		pulseWidthMS = (double) distInCM/26.923;


		//Read the shit out of the IR

		for(int i=0;i<5;i++){
			value += ADC_read();
		}
		
		value = value / 5;

		irDistance = (float) 36469*pow(value,-1.17); //1.156


		//Rotate the head
		move_servo(angle);
		angle += 5;
		if (angle > 180) {
			angle = 0;
			wait_ms(50);
		}
		
		//wait_ms(2225);
		
		//lprintf("Angle is: %f", angle);
		
		lprintf("Distance S: %d\nDistance IR: %f\nAngle: %f ms\nTime: %d", distInCM, irDistance, angle, pulseWidthMS);
		
		wait_ms(200);

		//Reject or take in that shit

		//if (distance < 2 || distance > 4) then it must be the same object (arbitrary values warning)
		//Basically, if it falls within a range, maybe 10% error or something
	}

}


