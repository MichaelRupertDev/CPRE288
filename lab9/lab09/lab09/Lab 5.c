/*
* Lab_5.c
*
* Created: 10/3/2014 12:26:39 PM
*  Author: jsalinas
*/


#include <avr/io.h>
#include "lcd.h"
#include "util.h"
#include <string.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define CLOCK_COUNT 15625
#define CHECK_COUNT 3125

void serial_putc(char data);
char serial_getc();
void serial_init();

volatile char button = 0;
volatile char prev = 0;

void timer_init(void) {
	// set up timer 1: WGM1 bits = 0100, CS = 101, set OCR1A, set TIMSK
	/*TCCR1A = 0b00000000;		// WGM1[1:0]=00
	TCCR1B = 0b00001101;		// WGM1[3:2]=01, CS=101
	OCR1A = CLOCK_COUNT - 1; 	// counter threshold for clock
	TIMSK = _BV(OCIE1A);		// enable OC interrupt, timer 1, channel A*/

	// set up timer 3: WGM1 bits = 0100, CS = 101, set OCR3A, set TIMSK
	TCCR3A = 0b00000000;		// WGM1[1:0]=00
	TCCR3B = 0b00001101;		// WGM1[3:2]=01, CS=101
	OCR3A = CHECK_COUNT - 1; 	// counter threshold for checking push button
	ETIMSK = _BV(OCIE3A);		// enable OC interrupt, timer 3, channel A

	sei();
}

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

int main(void)
{
	timer_init();
	lcd_init();
	//lprintf("Hello world");
	serial_init();
	
	int count = 0;
	char arr[20];
	
	while(1)
	{
		char lastValue = 0;
		while((count < 20)&&(lastValue!=13)){
			
			arr[count] = serial_getc();
			lastValue = arr[count]; 
			arr[count + 1] = '\0';
			lprintf("%c", arr[count]);
			
			if(arr[count]==13){
				serial_putc(10);
			}
			
			serial_putc(arr[count]);
			count++;
			
			
			

			
		}
		if(lastValue == 13){
			arr[count-1] = '\0';}
		else {arr[count] = '\0';}
		lprintf(arr);
		count = 0;
		
	}
}


void serial_init(){
	//unsigned int baud = 51; // COM1
	unsigned int baud = 34; //COM4
	
	
	UBRR0H = (unsigned char) (baud >> 8);
	UBRR0L = (unsigned char)baud;
	UCSR0A = 0b00000010;
	UCSR0B = 0b00011000;
	UCSR0C = 0b00001110;
	
	
	
	
}

void serial_putc(char data) {
	
	while((UCSR0A & 0b00100000)==0);
	
	UDR0 = data;
}

char serial_getc() {
	
	while((UCSR0A & 0b10000000)==0);
	
	return UDR0;
}