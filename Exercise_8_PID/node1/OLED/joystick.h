#pragma once

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include <stdbool.h>

bool joystick_moved_right(uint8_t x_value);
bool joystick_moved_left(uint8_t x_value);
bool joystick_moved_up(uint8_t y_value);
bool joystick_moved_down(uint8_t y_value);

typedef struct{
	uint8_t x_value;
	uint8_t y_value;
	uint8_t left_slider;
	uint8_t joy_buttom;
	}JoystickPos;

JoystickPos get_joystick_pos();

//volatile char *adc = (char *) 0x1400; // Start address of ADC
//make into one function?? so it can return a value ... ex mapping numbers to UO, DOWN... as in elev. 

//menu 
#define MAX_SUBMENUS 10 // max number of meny elements
typedef struct Menu 
{
	char * title;
	void (*function)(); //pointer to function, if theres no suv menu
	struct Menu * parent; //paretn menu
	struct Menu * subMenu[MAX_SUBMENUS]; //subMenu, array of pointers to menu elements 
} menu_t, *menu_ptr;

menu_ptr menu_add(menu_ptr parent, char * text, void (*function)()); // add sub menus 