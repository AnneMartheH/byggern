#include "oled.h"
#include "fonts.h"

volatile char *ext_oled_command = (char *) 0x1000; // OLED Command starting Address
volatile char *ext_oled_data = (char *) 0x1200; // OLED Data starting Address

void write_c(uint8_t command) {
	ext_oled_command[0] = command;
}

// OLED Write Data Function
void oled_write_data(uint8_t data) {

	ext_oled_data[0] = data;
}

// Select a line between 0 to 7
void oled_goto_line(int line) {
	write_c(0xB0 + line); // To go to line 0, Line = 0
}

// Select a column between 0 and 127, e.g 97 = 0b 0110 0001
void oled_goto_column(int column) {
	write_c(0x00 + (column % 16)); // Lower nibble (4 LSBs = 0110)
	write_c(0x10 + (column / 16)); // Higher nibble (4 MSBs = 0001)
}

void oled_goto_pos(int line,int column){
	oled_goto_line(line);
	oled_goto_column(column);
}

void oled_print_char(char c) {
	c = c-32;
	for (int i = 0; i < 8; i++) {
		int byte = pgm_read_byte(&font8[c][i]);
		oled_write_data(byte);
	}
}

void oled_print(char c[]) {
	for (int i = 0; i < strlen(c); i++) {
		oled_print_char(c[i]);
	}
}


void clear_screen(){
	// set all pixels on the screen low
	for (int line = 0; line < 8; line++) {
		oled_goto_line(line);
		oled_goto_column(0);
		for (int i = 0; i < 128; i++) {
			oled_write_data(0x00);
		}
	}
		
}

void enable_external_memory(){
	MCUCR = (1 << SRE); // Writing SRE to one enables the External Memory Interface in ATmega162. Check page 30 of the ATmega162
	SFIOR &= ~(111<XMM0);
	SFIOR |= (1 << XMM2); // Masks PC4-PC7 on ATmega162. That is, we make sure that we don't mess with the JTAG pins. Check "Table 4", page 32 of the ATmega162
	
}


void init_oled()
{
	write_c(0xae); // display off
	write_c(0xa1); //segment remap
	write_c(0xda); //common pads hardware: alternative
	write_c(0x12);
	write_c(0xc8); //common output scan direction:com63~com0
	write_c(0xa8); //multiplex ration mode:63
	write_c(0x3f);
	write_c(0xd5); //display divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81); //contrast control
	write_c(0x50);
	write_c(0xd9); //set pre-charge period
	write_c(0x21);
	write_c(0x20); //Set Memory Addressing Mode
	write_c(0x02);
	write_c(0xdb); //VCOM deselect level mode
	write_c(0x30);
	write_c(0xad); //master configuration
	write_c(0x00);
	write_c(0xa4); //out follows RAM content
	write_c(0xa6); //set normal display
	
	//write_c(0x21);
	//write_c(0x00);
	//write_c(0x7F);
	//
	//write_c(0x22);
	//write_c(0x00);
	//write_c(0x07);
	//
	//write_c(0xD3);
	//write_c(0x00);
	//
	//write_c(0x40);
	//
	//
	write_c(0xaf); // display on
	//write_c(0xa5);
	
}

void print_menu_w_pos(int pos){
	if (pos == 0){
		clear_screen();
		oled_goto_line(1);
		oled_goto_column(0);
		//oled_print_char('G');  //use '' for printing char
		oled_print("MENU"); // use "" for printing strings
		oled_goto_pos(2,0);
		oled_print(" Highscores *");
		oled_goto_pos(3,0);
		oled_print(" Start game");
		oled_goto_pos(4,0);
		oled_print(" Settings  ");
	}
	if (pos == 1){
		clear_screen();
		oled_goto_line(1);
		oled_goto_column(0);			//oled_print_char('G');  //use '' for printing char
		oled_print("MENU"); // use "" for printing strings
		oled_goto_pos(2,0);
		oled_print(" Highscores ");
		oled_goto_pos(3,0);
		oled_print(" Start game *");
		oled_goto_pos(4,0);
		oled_print(" Settings  ");
	}
	if (pos == 2){
		clear_screen();
		oled_goto_line(1);
		oled_goto_column(0);
		//oled_print_char('G');  //use '' for printing char
		oled_print("MENU"); // use "" for printing strings
		oled_goto_pos(2,0);
		oled_print(" Highscores ");
		oled_goto_pos(3,0);
		oled_print(" Start game ");
		oled_goto_pos(4,0);
		oled_print(" Settings   *");
	}
	
}

