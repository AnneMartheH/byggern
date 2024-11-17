#define F_CPU 4915200

#include "mcp2515.h"
#include "SPI.h"

#include "util/delay.h"


void mcp_init() {
	SPI_MasterInit();
	mcp_reset(); //Se kode for denne lenger ned

	_delay_ms(10); //Viktig!

	// Sjøltesting
	uint8_t value = mcp_read(MCP_CANSTAT); //Se kode for denne lenger ned
	printf("status register %d", value);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf("MCP2515 er ikke i konfigurasjonsmodus etter reset. CANSTAT: %x \r\n", value);
	}
}

void mcp_reset() {
	spi_ss_low(); // "selecting the device by pulling CS low,"
	spi_write(MCP_RESET); // "... sending the instruction byte"
	spi_ss_high(); // "... and then raising CS"
}

uint8_t mcp_read(uint8_t address) {
	spi_ss_low();
	spi_write(MCP_READ);
	spi_write(address); //Adressen (på MCP2515) som vi vil lese fra
	uint8_t data = spi_read();
	spi_ss_high();

	return data;
}

void mcp_write(uint8_t address, uint8_t data) {
	spi_ss_low();
	spi_write(MCP_WRITE);
	spi_write(address); //Adressen vi vil skrive til
	spi_write(data);
	spi_ss_high();
}

//void mcp_write_message(uint8_t address, CanMessage message) {
	//spi_ss_low();
	//spi_write(MCP_WRITE);
	//spi_write(address); //Adressen vi vil skrive til
	//spi_write(message.data);
	//spi_ss_high();
//}

char mcp_read_status() {
	spi_ss_low();
	spi_write(MCP_READ_STATUS);
	char data = spi_read();
	spi_ss_high();

	return data;
}

void mcp_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
	spi_ss_low();
	spi_write(MCP_BITMOD);
	spi_write(address); //Adressen der vi vil endre en eller flere bit
	spi_write(mask); //Maskeringsbyte, se forklaring nedenfor
	spi_write(data); //Verdiene som biten(e) skal endres til
	spi_ss_high();
	//_delay_ms(10);
}

void mcp_request_to_send(int buffer_number) {
	spi_ss_low();
	buffer_number = buffer_number % 3; // Mapper buffernummer til 0, 1, 2
	char data = MCP_RTS_TX0;
	if (buffer_number == 0) {
		data = MCP_RTS_TX0;
		} else if (buffer_number == 1) {
		data = MCP_RTS_TX1;
		} else if (buffer_number == 2) {
		data = MCP_RTS_TX2;
	}
	spi_write(data);
	spi_ss_high();
}

void mcp_set_mode(uint8_t mode) {
	mcp_bit_modify(MCP_CANCTRL, 0b11100000, mode);
}


//uint8_t CAN_read_message(uint8_t address) {
	//spi_ss_low();
	//
	//for (int i = 0; i < message.length; i++)
	//{
		//spi_write(MCP_READ);
	//}
	//
	//spi_write(address); //Adressen (på MCP2515) som vi vil lese fra
	//uint8_t data = spi_read();
	//spi_ss_high();
//
	//return data;
//}