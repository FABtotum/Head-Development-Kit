#include "tester.h"
#include "gpio.h"
#include "serial.h"
#include "wire.h"

#include "Tester.ino"

#include <stdlib.h>     /* strtol */
#include <Arduino.h>

char* errmsg = 0;

lock_t serial_lock = 0;

bool acquire (lock_t &lock)
{
	lock_t pre = lock;
	lock++;
	pre++;
	if (pre == lock) {
		if (lock == 1) {
			return true;
		}
	}

	lock--;
	return false;
}

/*void release (lock_t &lock)
{
	lock--;
}*/

bool parse (const char *buffer)
{
	//Serial.print("Buffer: "); Serial.println(buffer);

	// Command prefix on the line
	char command[3] = "";
	// First argument (usually an IO pin)
	long int pin = 0;
	bool analog = false;
	// Remaining command string
	char *arg;

	// Next char is command (m: mode, r: read, w: write)
	strncpy(command, buffer, 2);

	// Then follows the pin number
	arg = buffer + 2;
	pin = strtol(arg, &arg, 10);

	// pin type is given by first char
	analog = (arg[0] == 'a')? true : false;

	arg++;

	if (analog) {
		pin = analogInputToDigitalPin(pin);
	}

	switch (command[0])
	{
		case 'a':
		case 'd':
		case 'p':
			return gpio_parse(command, pin, arg);

		case 's': return serial_parse(command, pin, arg);

		case 'w': return wire_parse(command, pin, arg);
	}
}

void setup ()
{
	Serial.begin(SERIAL_BAUDRATE);
	wait(serial_lock);
	Serial.println("start");
	release(serial_lock);
}

void loop ()
{
	static char buffer[15];
	static unsigned char bidx = 0;
	static unsigned value = 0;

	/*byte serial_bytes = 0;
	static char serial_buffer[16] = "";
	while (serial_available()) {
		serial_read();
		serial_bytes++;
	}
	if (serial_bytes) {
		wait(serial_lock);
		Serial.print("// Serial >> ");

		Serial.println(, HEX);
		release(serial_lock);
	}*/

	while (Serial.available())
	{
		char incr = Serial.read();
		if (bidx >= 14) bidx = 14;
		if (incr == '\n')
		{
			buffer[bidx++] = 0;
			bool ok = parse(buffer);
			bidx = 0;
			
			wait(serial_lock);
			if (ok) {
				Serial.println("ok");
			} else {
				Serial.print("!! ");
				if (errmsg) {
					Serial.println(errmsg);
					errmsg = 0;
				} else {
					Serial.println("");
				}
			}
			release(serial_lock);
		}
		else
		{
			buffer[bidx++] = incr;
		}
	}
}
