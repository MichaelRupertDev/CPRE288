/*
 * GccApplication1.c
 *
 * Created: 9/12/2014 12:29:37 PM
 *  Author: jsalinas
 */ 


#include <avr/io.h>
#include "open_interface.h"
#include "lcd.h"
#include "movement.h"

int main(void)
{
	lcd_init();
	lcd_puts("AYYYY TONY");
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    /*int sum = 0;
    oi_set_wheels(500, 500); // move forward; full speed
    while (sum < 1000) {
	    oi_update(sensor_data);
	    sum += sensor_data->distance;
    }
    oi_set_wheels(0, 0); // stop

    oi_free(sensor_data);*/
	//int i = 0;
	int dist = 0;
	while(dist < 2000) {
		oi_set_wheels(300, 300);
		oi_update(sensor_data);
		dist += sensor_data->distance;
		
		if(sensor_data->bumper_left){
			oi_update(sensor_data);
			dist += sensor_data->distance;
			dist += -15;
			
			bump(sensor_data, 1);
		}
		else if(sensor_data->bumper_right){
			oi_update(sensor_data);
			dist += sensor_data->distance;
			dist += -15;
			bump(sensor_data, 2);
		}
	}
	oi_set_wheels(0,0);
}