//
//
//void test_looppback_can(){
		//enable_external_memory();
		//init_oled(); // OLED initialization
		//timer1_init(); //change this name
		//uart_init(MYUBRR);
		//adc_init();
//
		//_delay_us(200);
		//
		//CanMessage  message;
		//message.id_h = 0b10101010;
		//message.id_l = 0b01010101;
		//message.length = 1;
		//message.data[0] = 0b10110011; //179 decimal
		////message.data[1] = 0b11001100;
		//
		//
		////test :=0
//
		//// Initialiserer SPI og MCP:
		////spi_master_init(); //Ta med denne hvis ikke spi_master_init() ligger inni mcp_init()
		//mcp_init(); // also whats needed to initialize can, inside MCP is initialized
//
		//// Setter MCP i loopbackmodus og sjekker CANSTAT:
		////mcp_write(MCP_CANCTRL, 0b01000000);
		////while(1){
		//mcp_set_mode(MODE_LOOPBACK);
		////spi_ss_low();
		////_delay_ms(100);
		////spi_ss_high();
		////}
		//
		//printf("mode: %d\r\n", mcp_read(MCP_CANSTAT));
		//// Når MCP står i loopbackmodus skal CANSTAT være 0b01000000 aka 0x40
//
		//// Skriver en tilfeldig byte (0xA7) til MCP-sendebuffer0 og leser fra mottaksbuffer0
		//// Her bør man lese det samme som man sender så lenge MCPen står i loopbackmodus.
		//CAN_send_message(MCP_TXB0SIDH, message); // Skriver 0xA7 til sende-buffer nr. 0
		//_delay_ms(1000);
		//CanMessage message_rec = CAN_recive_message();
		//printf("recived maessage: %d \n ---------- \n\r", message_rec.id_h);
		////print_can_message(&message);
		////mcp_request_to_send(0); // Sender 0xA7 fra bufferen ut på CAN-bussen
		////CanMessage byte = mcp_read(MCP_RXB0SIDH); // Leser fra mottaksbuffer nr. 0
		////printf( message); //Skal være samme som man sender, altså 0xA7
//}




//-------------------------------------------------------------excersice 6 ---------------------------------------------------------

// sending joystick pos between node1 and node2
//int main(void) {
	////printf("jeg kjorer");
	//enable_external_memory();
	//init_oled(); // OLED initialization
	//timer1_init(); //change this name, gjør masse setter outouts og ++
	//uart_init_made(MYUBRR);
	//adc_init();
	////Can Bus timing
	//mcp_init();
	//
	//mcp_set_mode(MODE_CONFIG);
	//
	//CanMessage  message;
	//message.id = 0b11100000; // Only the three MSB that matter, for more explanation translate this: kun de tre første bitsene (MSB / til venstre) som styrer id, noe rart med koden her // endret utdelt kode til å motta unit16.
	////message.id_l = 0b01010101;
	//message.length = 2;
	//message.data[0] = get_joystick_pos().x_value; //179 decimal
	//message.data[1] = get_joystick_pos().y_value;
	//
	//
	//
	//// MCP2515 Controller setting for CAN Bus bit timings, check page 43 of MCP Controller data sheet
	//// TQ = (2(3+1))/16Mz = 500 ns
	//// Assuming CAN Baud Rate = 125 kHz (Check page 43 on MCP2515 datasheet) - To obtain this we need to set Bit Time to 16 TQs
	//mcp_write(MCP_CNF1, 0b00000011); // SJW=0 (1) BRP=3
	//mcp_write(MCP_CNF2, 0b10110000); // BTLMODE=1, SAM=0, PS1=6 (7), PRSEG=0 (1)
	//mcp_write(MCP_CNF3, 0b00000101); // PS2=5 (6)
	////another way of the same as above, this below is not tested
	////mcp_write(MCP_CNF1, 0b); //sjw = 00, brp= 000100 = 3hex !!
	////mcp_write(MCP_CNF2, (1 << SHIFT_BTL | 0 << SHIFT_SAM | 6 << SHIFT_PS1 | 1 << SHIFT_PSEG)); // bitmode = 1, sam = 0, phseg1 = 6, prseg = 1
	////mcp_write(MCP_CNF3, (5 << SHIFT_PS2)); // SOF = 0, wakfil = 0, phseg2 = 5
	//
	//mcp_set_mode(MODE_NORMAL);
	//
	//printf("hello");
	//
	//while (1)
	//{
		//message.data[0] = get_joystick_pos().x_value;
		//message.data[1] = get_joystick_pos().y_value;
		//CAN_send_message(MCP_TXB0SIDH, message);
		//printf("x: %d", get_joystick_pos().x_value);
		//printf("y: %d\r\n", get_joystick_pos().y_value);
		//_delay_us(200);
	//}
	//
	//
//}
/// --------------------------------------------------end ex.6------------------------------------------------------------------------------------------------------------
