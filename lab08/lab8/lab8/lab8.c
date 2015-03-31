/*
 * lab8.c
 *
 * Created: 3/11/2015 12:25:47 PM
 *  Author: mbrupert
 */ 


#include <avr/io.h>
#include "lcd.h"
#include "open_interface.h"
#include "util.h"

unsigned pulse_width;

#define TOP 43000
//#define TOP 43000

void timer3_init()
{	
TCCR3A = 0b00100011;
TCCR3B = 0b00011010;
OCR3A = TOP;
//OCR3B = 0b101110111000;
DDRE |= _BV(4);
}

void move_servo(unsigned degree)
{
	//unsigned pulse_width; // pulse width in cycles
	pulse_width = 18.511*degree + 700; // calculate pulse width in cycles
	OCR3B = pulse_width;// set pulse width
	wait_ms(25);             // you need to call wait_ms() here to enforce a delay for the servo to
	                      // move to the position
}

int main(void)
{
	lcd_init();
	timer3_init();
	float angle = 90;
	char direction = 1;
	
    while(1)
    {
		
		int button = read_push_buttons();
		
		if (button == 1) {
			if (direction == 1) {
				angle++;
			} else {
				angle--;
			}
		} else if (button == 2) {
			if (direction == 1) {
				angle += 2.5;
			} else {
				angle -= 2.5;
			}			
		} else if (button == 3) {
			if (direction == 1) {
				angle += 5;
			} else {
				angle -= 5;
			}			
		} else if (button == 4) {
			if (direction == 1) {
				direction = 0;
			} else {
				direction = 1;
			}			
		}
		
		move_servo(angle);
		
		lprintf("Angle: %f\nPulse Width: %d\nDirection: %c", angle, pulse_width, direction+48);
		
//         move_servo(0);
// 		wait_ms(2000);
// 		move_servo(10);
// 		wait_ms(2000);
// 		move_servo(20);
// 		wait_ms(2000);
    }
}
