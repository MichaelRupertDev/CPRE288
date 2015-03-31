MAIN METHODS:

Lab 5:

int main(void)
{
	timer_init();
	lcd_init();
	//lprintf("Hello world");
	serial_init();
	
	int count = 0;
	char arr[20];
	
	while(1)
	{
		char lastValue = 0;
		while((count < 20)&&(lastValue!=13)){
			
			arr[count] = serial_getc();
			lastValue = arr[count]; 
			arr[count + 1] = '\0';
			lprintf("%c", arr[count]);
			
			if(arr[count]==13){
				serial_putc(10);
			}
			
			serial_putc(arr[count]);
			count++;
			
			
			

			
		}
		if(lastValue == 13){
			arr[count-1] = '\0';}
		else {arr[count] = '\0';}
		lprintf(arr);
		count = 0;
		
	}
}


Lab 6:

int main(void)
{
	float distance;
	int value = 0;
	
	ADC_init();
	lcd_init();
	int i;
    while(1){
		for(i=0;i<5;i++){
			value += ADC_read();	
		}
		
		value = value / 5;

		distance = (float) 36469*pow(value,-1.17); //1.156

		lprintf("Sensor: %d\nDistance: %fcm", value, distance);
		wait_ms(100);
	}
}

Lab 7:

int main(void)
{
	unsigned int distance = 0;
	int distInCM = 0;
	int pulseWidthTC= 0;
	double pulseWidthMS = 0;
    lcd_init();
	TC_init();
	while(1){
		cli();
		state = LOW;
		send_pulse();
		sei();
		while(state != DONE);
		
		distance = time2dist((fedge-redge)/2);
		distInCM = 0.1059*distance - 69.639;
		pulseWidthTC = (fedge-redge);
		pulseWidthMS = (double) distInCM/26.923;
		lprintf("Distance: %u\nPulse Width: %d\nPulse Width: %0.1f ms\nOverflows: %d", distInCM, pulseWidthTC, pulseWidthMS, numOvf);
		wait_ms(200);
		
	}
	
}


Lab 8:

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
		
		if (angle > 180) {
			angle = 180;
		}
		
		if (angle < 0) {
			angle = 0;
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