/*
 * lab4.c
 *
 * Created: 9/26/2014 12:36:10 PM
 *  Author: jsalinas
 */ 

/*
#include <avr/io.h>
#include "lcd.h"
#include "util.h"

int hours = 5;
int mins = 30;
int secs = 0;


int main() {
	lcd_init();

	// Display the time as: 05:30:00
	lprintf("%02d:%02d:%02d", hours, mins, secs);
	
	while(1){
		
		switch(read_push_buttons()){
			case 0:
			break;
			case 1:
			secs--;
			break;
			case 2:
			secs++;
			break;
			case 3:
			mins--;
			break;
			case 4:
			mins++;
			break;
			case 5:
			hours--;
			break;
			case 6:
			hours++;
			break;
		}
		if(secs >= 60){
			secs = 0;
			mins++;
		}
		if(secs < 0){
			secs = 59;
			mins--;
		}
		if(mins >= 60){
			mins = 0;
			hours++;
		}
		if(mins < 0){
			mins = 59;
			hours--;
		}
		if(hours > 12){
			hours = 1;
		}
		if(hours < 1){
			hours = 12;
		}
		
		
		lprintf("%02d:%02d:%02d", hours, mins, secs);
		wait_ms(200);
	}
	
	return 0;

}*/