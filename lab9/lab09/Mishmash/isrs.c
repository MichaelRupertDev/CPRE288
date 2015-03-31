ISR FILE


Lab 5:

ISR (TIMER3_COMPA_vect) {

	// Insert interrupt handler code for checking push buttons here
	
	button = read_push_buttons();
	if(button == prev){
		button = 0;
	}
	
	//prev = button;
	char msg[40];
	//char prev = 0;
	int i;
	
	switch(button){
			
				case 6:
				strcpy(msg,"Yes\r");
				break;
				
				case 5:
				strcpy(msg, "No\r");
				break;
				
				case 4:
				strcpy(msg,"Blue, no green, Ahhhhh!!!\r");
				break;
				
				case 3:
				strcpy(msg,"CYCLONE STATE\r");
				break;
				
				case 2:
				strcpy(msg,"Everything is awesomeeeeeee\r");
				break;
				
				case 1:
				strcpy(msg,"Making my way downtown walking fast\r");
				break;
				
				case 0:
				msg[0] = '\0';
				break;
				
	}
	if(button!=0){
	lprintf(msg);
	for(i=0; i<strlen(msg); i++) {
		serial_putc(msg[i]);
	}
	serial_putc(10);
	prev = button;
	}

}




Lab 7:


ISR (TIMER1_CAPT_vect){
	if (state == LOW){
			redge = ICR1;
			state = HIGH;
			TCCR1B &= 0b10111111;
	}
	
	else if(state == HIGH){
		fedge = ICR1;
		state = DONE;
		TCCR1B |= 0b01000000;
	}
	
}

ISR (TIMER1_OVF_vect) {
	numOvf++;
}


