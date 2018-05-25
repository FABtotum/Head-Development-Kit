/**
 * File: wire.cpp
 * 
 * Wire control
 */
#include "Tester.ino"
#include "tester.h"
#include "wire.h"

#include <Wire.h>

bool wire_enabled = false;
byte wire_registers[8] = {
	0x01,
	0x00,
	0x00,
	0x00,
	0x00,
	0xb0,
	0xfa,
	0x00
};
byte wire_req_register = 0;
byte wire_req_value    = 0;

void wire_begin (uint8_t address);
void wire_end (void);
void wire_register_setup (byte reg, byte value);
void wire_dump_registers (void);

inline void wire_start () { TWCR |= _BV(TWEN); }

/**
 * Function: wire_parse
 *
 * 	Parse input commands for the Wire interface
 */
bool wire_parse (char *command, long int pin, char *arg)
{
	switch (command[1])
	{
		case 's':
			wire_start();
			if (INFO) {
				wait(serial_lock);
				Serial.println("// Enable TWI");
				release(serial_lock);
			}
		case 'b': {
			// Begin Wire
			uint8_t address = pin & 0x7f;
			wire_begin(address);
			if (INFO) {
				wait(serial_lock);
				Serial.print("// Begin Wire @ ");
				Serial.println(address, DEC);
				release(serial_lock);
			}
			return true;
		}
		case 'r': {
			byte reg = pin & 0xff;
			byte value = strtol(arg, 0, 16);
			wire_register_setup (reg, value);
			if (INFO) wire_dump_registers();
			return true;
		}
		case 'e': {
			// End Wire
			wire_end();
			if (INFO) Serial.println("// Stopped Wire");
			return true;
		}
	}

	errmsg = ERR_UNRECOGNIZED_COMMAND;
	return false;
}

/**
 * Function: wire_receive
 * 
 * Receive bytes on the TWI
 * 
 * Description:
 *	The last byte received is stored as a request register and
 * used in any subsequent response request by the master
 */
void wire_receive (int bytes)
{
	while (Wire.available()) {
		wire_req_register = Wire.read();
		wait(serial_lock);
		Serial.print("// wire >> ");
		Serial.println(wire_req_register, HEX);
		release(serial_lock);
	}
}

void wire_request ()
{
	if (wire_req_register < 8) {
		wire_req_value = wire_registers[wire_req_register];
	}

	Wire.write(wire_req_value);
	wait(serial_lock);
	Serial.print("// wire << ");
	Serial.println(wire_req_value, HEX);
	release(serial_lock);
}

void wire_dump_registers ()
{
	wait(serial_lock);
	for (byte i = 0; i < sizeof wire_registers; i++) {
		wire_registers[7] = (wire_registers[7] + wire_registers[i]) & 0xff;
		Serial.print("// Conf");
		Serial.print(i);
		Serial.print(" = ");
		Serial.println(wire_registers[i], HEX);
	}
	release(serial_lock);
}

void wire_register_setup (byte reg, byte value)
{
	wire_registers[reg] = value;
}

void wire_begin (uint8_t address)
{
    Wire.begin(address);
    Wire.onReceive(wire_receive);
    Wire.onRequest(wire_request);
    wire_enabled = true;
}

void wire_end ()
{
    wire_enabled = false;
    TWCR &= ~_BV(TWEN);
}
