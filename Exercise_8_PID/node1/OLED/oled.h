#pragma once

#include <avr/io.h>
#include <stdio.h>


//am made 
void clear_screen();
void enable_external_memory();

void write_c(uint8_t command);
void oled_write_data(uint8_t data);


//variables 
//volatile char *ext_oled_command = (char *) 0x1000; // OLED Command starting Address
//volatile char *ext_oled_data = (char *) 0x1200; // OLED Data starting Address

//prev made 
void init_oled();
void print_menu_w_pos(int pos);
void game_screen();


