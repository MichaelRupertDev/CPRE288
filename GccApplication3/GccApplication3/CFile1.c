/*
 * CFile1.c
 *
 * Created: 2/3/2015 8:12:57 PM
 *  Author: mbrupert
 */ 
#include "lcd.h"
#include "util.h"

void main() {
	lcd_init();
	//init_push_buttons();
	shaft_encoder_init();

	while(1) { // loop indefinitely
		char button = read_shaft_encoder();
		lprintf("Button: %d", button);
		move_stepper_motor_by_step(100, button);
	}

}