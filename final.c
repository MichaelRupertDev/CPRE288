

#include <avr/io.h>
#include "util.h"


unsigned char str_receive[20]={0};


int main(void) {
	lcd_init();
	TCCR_init();
	timer3_init();
	USART_init(16);
	oi_t *sensor_data_pointer = oi_alloc();
	oi_init(sensor_data_pointer);
	
	
	while(1) {
		int i = 0,n=0;
		oi_update(sensor_data_pointer);
		
		
		while (i < 20) {
			str_receive[i] = USART_receive();
			if (str_receive[i] == 13) {
				break;
			}
			i++;
		}
		
		str_receive[i] = 0;
		
	
		


		
		lprintf("%s",str_receive);
		
		int command=command_analyze(str_receive);
		lprintf("%d",command);
	
		switch(command)
		{   case 1:  command_initial(sensor_data_pointer);
			break;
			case 2:  command_move_forward(sensor_data_pointer);
			break;
			case 3:  command_move_backward(sensor_data_pointer);
			break;
			case 4:  command_turn_letf(sensor_data_pointer);
			break;
			case 5:  command_sweep();
			break;
			case 6:  command_move_servo();
			break;
			case 7:  command_turn_right(sensor_data_pointer);
			break;
			
		}

	}

	return 1;
}