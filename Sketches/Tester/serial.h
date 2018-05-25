#ifndef _TEST_SERIAL_
#define _TEST_SERIAL_

#include <Arduino.h>
#include <SoftwareSerial.h>

extern bool serial_enabled;

bool serial_parse (const char * command, long pin, const char * arg);

#endif