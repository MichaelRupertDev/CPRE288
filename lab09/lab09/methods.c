#include <avr/io.h>
#include <avr/interrupt.h>
#include "methods.h"

#define CLOCK_COUNT 15625
#define CHECK_COUNT 3125

#define TOP 43000

unsigned pulse_width;

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

void ADC_init() {
	
	ADMUX = 0b11000010;// Set up refevcence voltage and channel
	ADCSRA = 0b10000111;// Enable
}

int ADC_read() {
	
//	ADMUX = 0b11000010; // Select 
	ADCSRA |= 0b01000000; // Start sensor
	while (ADCSRA & 0b01000000)	{}
	return ADC; 
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

void timer3_init()
{	
TCCR3A = 0b00100011;
TCCR3B = 0b00011010;
OCR3A = 43000;
//OCR3B = 0b101110111000;
DDRE |= _BV(4);
}

void move_servo(unsigned degree)
{
	unsigned pd;
	//unsigned pulse_width; // pulse width in cycles
	pd = 18.511*degree + 700; // calculate pulse width in cycles
	OCR3B = pd;// set pulse width
	wait_ms(25);             // you need to call wait_ms() here to enforce a delay for the servo to
	                      // move to the position
}