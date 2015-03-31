#include "lcd.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Simple 'Hello, world' program
/**
* This program prints "Hello, world" to the LCD screen
* @author Chad Nelson
* @date 06/26/2012
*/
int main (void) {
	// Initialize the the LCD.  This also clears the screen.
	lcd_init();

	// Clear the LCD screen and print "Hello, world" on the LCD
	//lprintf("Hello, world");
	//lcd_puts("Hello world!");
	int count = 0;
	char myString[] = "Microcontrollers are lots of fun! ";
	int j = 1;
	int i;
	int d = 0;
	int spaces;
	int s;
	
	char tempString[21];
	tempString[20] = '\0';
	while(j){
		
		if(count > (strlen(myString)+19)) {
			count = 0;
		}
		spaces = 19 - count;
		if(spaces<0) {
			spaces = 0;
		}
		
		
		for(s=0; s<spaces; s++){
			tempString[s] = ' ';
		}
		i = s;
		if(count < 21){
			d = 0;
		}
		else {
			d = count - 20;
		}
		while(i < 20){
			
			/*if(count>20){
				d = d + (i-20);
			}
			else {
				d = i;
			}*/
			
			
			tempString[i] = myString[d];
			
			d++;
			i++;
			
		}
		//tempString[i+1] = '\0';	
		lcd_clear();
		lcd_puts(tempString);
		wait_ms(300);
		i = 0;
		d = 0;
		
		
		count++;
		
		
		
	}
	// Notes: Open util.h to see what functions are available for you to use.
	// You will need to use these functions in future labs.
	
	// It is recommended that you use only lcd_init() and lprintf() from lcd.h.
	
	return 0;
}
