/*
 * Lab_3.c
 *
 * Created: 2/16/2015 5:56:59 PM
 *  Author: be1
 */ 


#include "lcd.h"
#include "util.h"

void main() {
	lcd_init();
	init_push_buttons();
	shaft_encoder_init();
	stepper_init();

	while(1) { // loop indefinitely
		int button = read_shaft_encoder();
		
		char t = move_stepper_motor_by_step(20, button);
		lprintf("Button: %x", t);
		//wait_ms(100);
	}

}