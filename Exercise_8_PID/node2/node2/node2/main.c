
#include "sam.h"
#include "can.h"
#include "time.h"
#include "uart.h"
#include "test.h"
#include "gameBoard.h"
#include "motors.h"

//look at figure 31-3 I/) Line control Locic in atmel SAM3X8E
//pin 21, D21/SCL
int main(void)
{
    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer in Atsem which is by default enabled that periodically reset
	
	/* Initialize the SAM system */
    SystemInit();
	uart_init(84000000,9600); // cpu frequency and baudrate
	
	// Node 2 - CAN_BR Register setting on ATSEM
	//CAN_BR_BRP(41); //TQ = (41+1)/(84Mhz) = 500 ns
	CanMsg recMssage;
	CanInit initValues;
	
	initValues.brp = 41;
	initValues.phase1 = 6;
	initValues.phase2 = 5;
	initValues.propag = 0;
	initValues.sjw = 0;
	initValues.smp = 0;
	
	can_init(initValues,0);
	ADC_init();
	PWM_init();
	timer_counter_encoder_init(); 
	encoder_init();
	solinoid_init();
	 
	//int historical_error = 0;
 

	while (1)
	{
		can_rx(&recMssage);
		can_printmsg(recMssage);
		
		int joystick_x_Servo = recMssage.byte[0];
		int joystick_y_Motor = recMssage.byte[1];
		int switch_Solenoid = recMssage.byte[2];
		
		//if (joystick_y_Motor < 170 && joystick_y_Motor > 125)
		//{
			//joystick_y_Motor = 125;
		//}
		
		//int error = get_position_error(scaled_encoder, recMssage.byte[1]);
		uint16_t ticks =  joystckPosToTicks(joystick_x_Servo);
		//printf("\n \r Joystick Ticks from Node 1: %d \r\n", ticks);
		uint16_t bin = decimalToBinary(ticks);
		PWM->PWM_CH_NUM[1].PWM_CDTY=bin;  // 2 756 ticks setting duty cycle to control servo position
		
		//uint16_t speed  = joystckPosToTicks_speed(recMssage.byte[1]);//motor speed and direction
		
		int scaled_encoder = get_scaled_encoder_pos();
		int scaled_joystick_y = scale_joystick_y(joystick_y_Motor);
		//int decimal_controller_output, error_sum = position_controller(scaled_encoder, joystick_y_Motor, historical_error);
		int decimal_controller_output = position_controller(scaled_encoder, scaled_joystick_y);
		//printf("\r  output of controller in decimal (speed): %d \r \n",  decimal_controller_output);
		//printf("\r  error sum from function: %d \r \n",  error_sum);
		//historical_error = error_sum;
		uint16_t binary_controll_output = decimalToBinary(decimal_controller_output);
		
		
		//if(scaled_encoder > scaled_joystick_y){
			//PIOC->PIO_SODR |= PIO_SODR_P23; //go left
			//printf("\r  go left \n ");
			//PWM->PWM_CH_NUM[0].PWM_CDTY=binary_controll_output;				
		//}
		//else if (scaled_encoder < scaled_joystick_y){
		////if (scaled_encoder < scaled_joystick_y){
			//PIOC->PIO_CODR |= PIO_CODR_P23; //go right
			//printf("\r  go right \n ");
			//PWM->PWM_CH_NUM[0].PWM_CDTY=binary_controll_output;
		//}
		//else {
		//PWM->PWM_CH_NUM[0].PWM_CDTY=0;
		//}
		
		PWM->PWM_CH_NUM[0].PWM_CDTY=binary_controll_output; //to control the motor speed
		
		printf("\r  Scaled encoder position = current position: %d \r \n",  scaled_encoder);
		printf("\r  Scaled joystick position : %d \r \n",  scaled_joystick_y);
		printf("\r joystick pos not scaled: %d \r \n",  joystick_y_Motor);
		
		printf(" \n");
		
		
		
		// Control solenoid based on joystick button value
		joystick_solinod_controller(switch_Solenoid);
		
		//****
		// Read the converted data from the ADC's Last Converted Data Register (ADC_LCDR)
		// The result is available even if the conversion is still running
		uint32_t adc_value = ADC->ADC_CDR[10];  // Read the last conversion result
		uint16_t result = adc_value ;//& ADC_LCDR_LDATA_Msk; // Mask out the data
		//printf("IR Sensor Value on Node 2: %d\r\n", result); // Output the ADC result via UART
		
		///*** Encoder
		//int Encoder_Value = TC2->TC_CHANNEL[0].TC_CV;  // Read the last conversion result
		//printf("\r Encoder Position: %d \r \n",  Encoder_Value);
		

		//printf("\r  error: %d \r \n",  error);
		
		// For servo to work you must remove the following delay
		//for (int j = 0; j < 10500000; j++);
		time_spinFor(msecs(200));
	}
}

// registers that may need to be sltered 
//TC_CV Counter value register 
//TC_BMR block mode register
//TC_CMR channel mode register
//TC_CCR channel control register 


