#include <stdio.h>
#include <stdlib.h>
#include "open_interface.h"

void move(oi_t *sensor, int millimeters) {
		int sum = 0;
		if(millimeters < 0) {
			oi_set_wheels(-300, -300);
			while (sum > millimeters) {
				oi_update(sensor);
				sum += sensor->distance;
			}
				
			oi_set_wheels(0, 0);
			}
		else {
			oi_set_wheels(300,300);
			while (sum < millimeters){//minus 5 degree for calibration {
				oi_update(sensor);
				sum += sensor->distance;
			}
				
			oi_set_wheels(0, 0);
			}
}

void turn(oi_t *sensor, int degrees) {
	int sum = 0;
	if(degrees < 0) {
		oi_set_wheels(-100, 100);
		while (sum > (degrees+6)) {
			oi_update(sensor);
			sum += sensor->angle;
		}
			
		oi_set_wheels(0, 0);
	}
	else {
		oi_set_wheels(100,-100);
		while (sum < (degrees-6)){//minus 5 degree for calibration {
			oi_update(sensor);
			sum += sensor->angle;
		}
		
		oi_set_wheels(0, 0);
	}
}

void bump(oi_t* sensor, int direction) {
	oi_set_wheels(0,0);
	if(direction == 1){
		move(sensor, -15);
		turn(sensor,-90);
		move(sensor, 100);
		turn(sensor,90);
		
	}
	else if(direction ==2){
		move(sensor, -15);
		turn(sensor,90);
		move(sensor, 100);
		turn(sensor,-90);
	}
	oi_update(sensor);
		
}

