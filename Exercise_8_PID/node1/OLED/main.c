#define FOSC 4915200
#include <avr/io.h>
#include <util/delay.h>

#include "oled.h"
#include "joystick.h"
#include "uart_made.h"
//#include "SPI.h"
#include "mcp2515.h"
#include "CAN_comm.h"
//#include "can.h"
//#include "time.h"
//#include "uart.h"

#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1 // UBRR value calculation (Page 169 of ATmega162 datasheet)

///... prøver å legge inn det som ikke er def 
//#define MODE_LOOPBACK   0x40
//#define MCP_CANSTAT		0x0E
//#define MCP_TXB0SIDH 0x31 // aka 0b0011 0001
//#define MCP_RXB0SIDH	0x61

///...

 // Clock speed of ATmega162

// OLED works in such a way that you write one byte (8 bits) to it at a time.

//volatile char *ext_oled_command = (char *) 0x1000; // OLED Command starting Address
//volatile char *ext_oled_data = (char *) 0x1200; // OLED Data starting Address
//volatile char *adc = (char *) 0x1400; // Start address of ADC

//from ex.3 joystick code

void adc_init() {
	MCUCR = (1 << SRE);  // Enable external memory interface
	SFIOR = (1 << XMM2); // Mask PC4-PC7 to avoid JTAG conflict
}
void timer1_init() {
	TCCR1B |= (1 << WGM12);   // Set CTC mode (Clear Timer on Compare Match)
	OCR1A = 0;                // Set Compare Match value
	TCCR1B |= (1 << CS10);    // Set prescaler to 1 (no prescaling)
	TCCR1A |= (1 << COM1A0);  // Toggle OC1A on compare match
	DDRD |= (1 << PD5);       // Set PD5 as output for OC1A
}

int menu_position = 0; // global variable, upsi


int main(void) {
	//printf("jeg kjorer");
	enable_external_memory();
	init_oled(); // OLED initialization
	timer1_init(); //change this name, gjør masse setter outouts og ++
	uart_init_made(MYUBRR);
	adc_init();	
	//Can Bus timing
	mcp_init();
	
	mcp_set_mode(MODE_CONFIG);
	
	CanMessage  message;
	message.id = 0b11100000; // Only the three MSB that matter, for more explanation translate this: kun de tre første bitsene (MSB / til venstre) som styrer id, noe rart med koden her // endret utdelt kode til å motta unit16.
	//message.id_l = 0b01010101;
	message.length = 3;
	message.data[0] = get_joystick_pos().x_value; //179 decimal
	message.data[1] = get_joystick_pos().y_value;
	message.data[2] = get_joystick_pos().joy_buttom;
	
	// MCP2515 Controller setting for CAN Bus bit timings, check page 43 of MCP Controller data sheet
	// TQ = (2(3+1))/16Mz = 500 ns
	// Assuming CAN Baud Rate = 125 kHz (Check page 43 on MCP2515 datasheet) - To obtain this we need to set Bit Time to 16 TQs
	mcp_write(MCP_CNF1, 0b00000011); // SJW=0 (1) BRP=3
	mcp_write(MCP_CNF2, 0b10110000); // BTLMODE=1, SAM=0, PS1=6 (7), PRSEG=0 (1)
	mcp_write(MCP_CNF3, 0b00000101); // PS2=5 (6)
	//another way of the same as above, this below is not tested
	//mcp_write(MCP_CNF1, 0b); //sjw = 00, brp= 000100 = 3hex !!
	//mcp_write(MCP_CNF2, (1 << SHIFT_BTL | 0 << SHIFT_SAM | 6 << SHIFT_PS1 | 1 << SHIFT_PSEG)); // bitmode = 1, sam = 0, phseg1 = 6, prseg = 1
	//mcp_write(MCP_CNF3, (5 << SHIFT_PS2)); // SOF = 0, wakfil = 0, phseg2 = 5
	
	mcp_set_mode(MODE_NORMAL);
	
	printf("hello");
	
	while (1)
	{
		JoystickPos joystick =  get_joystick_pos();
		message.data[0] = joystick.x_value;
		message.data[1] = joystick.y_value;
		message.data[2] = joystick.joy_buttom;
		CAN_send_message(MCP_TXB0SIDH, message);
		//printf("x: %d",message.data[0]);
		//printf("y: %d\r\n", message.data[1]);
		//printf("joy_buttom: %d\r\n", message.data[2]);
		_delay_ms(20);	
	}
	
		
} 