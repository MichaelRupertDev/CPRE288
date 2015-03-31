/*
 * Lab_3.c
 *
 * Created: 9/19/2014 12:38:32 PM
 *  Author: jsalinas
 */ 


#include <avr/io.h>
#include "lcd.h"
#include "util.h"

int main() {
	lcd_init();
	lcd_clear();
	init_push_buttons();
	shaft_encoder_init();
	stepper_init();
	
	signed char sum = 0;
	int temp = 0;
	
	while(1) { // loop indefinitely
		char button = read_push_buttons();
		int shaft = read_shaft_encoder();
		sum += shaft;
		temp += shaft;
		lprintf("Button: %d\nSum: %d\nBinary: %d\nTemp: %d", button, sum, PORTE, temp);
		move_stepper_motor_by_step(4,shaft);
		
		
	}
	return 0;
}