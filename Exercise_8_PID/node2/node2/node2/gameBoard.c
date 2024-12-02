#include "gameboard.h"

#include <stdio.h>
#include <stdint.h>
#include "sam.h"

uint16_t joystckPosToTicks(uint8_t x_pos_joystick){
	//printf(x_pos_joystick);
	if (x_pos_joystick <= 165 && x_pos_joystick >= 155)// neutral
	{
		//printf("neutral");
		return 1968; // 1968 ticks == neutral pos = 1,5 ms 
	}
	else if( x_pos_joystick < 155){ // left
		int diff = x_pos_joystick - 155;
		float prosentage = ((float)diff / 1.55)/100;
		int ticks_subtracted = 786 * prosentage;
		int ticks = 1968 + ticks_subtracted;
		//printf("low");
		return ticks;
		
	}
	else { // right
	//else if( x_pos_joystick > 155){ // right	
		int diff = x_pos_joystick - 165; // pos - neutral
		float prosentage = ((float)diff / 0.9)/100; // precentage aboove neuytral
		int ticks_added = 786 * prosentage; //786 is max ticks you can add 
		int ticks = 1968 + ticks_added; // 1968 = neutral nubmer of ticks 
		//printf("high");
		return ticks;
		//convert to binary
		
	}
}

uint16_t joystckPosToTicks_speed(uint8_t y_pos_joystick){
		if (y_pos_joystick <= 170 && y_pos_joystick >= 160)// neutral
		{
			//printf("neutral");
			return 0; // 0 = no speed
		}
		else if( y_pos_joystick < 160){ // left
			//printf("low");
			PIOC->PIO_SODR |= PIO_SODR_P23;
			return 0b10000;
			
		}
		else {//right
			PIOC->PIO_CODR |= PIO_CODR_P23;
			return 0b10000;
		}
	
}

void switch_solinod_controller(uint8_t button_joystick){
	if (button_joystick == 255){// Default
		PIOB->PIO_CODR |= PIO_CODR_P16;
	}
	else{
		PIOB->PIO_SODR |= PIO_SODR_P16;
	}
}


uint16_t decimalToBinary(uint16_t n) {
	uint16_t binary = 0;  // This will hold the binary representation
	uint16_t place = 1;    // Used to place the bits in the correct position

	for (int i = 0; i < 16; i++) {
		// Extract the least significant bit and place it in the binary result
		if (n & 1) {
			binary |= place;  // Set the bit at the current place
		}
		n >>= 1;  // Shift n to the right by 1
		place <<= 1;  // Move the place to the next position (left shift)
	}
	
	return binary;
}

