#ifndef _TEST_WIRE_
#define _TEST_WIRE_

#include <Arduino.h>

extern bool wire_enabled;

bool wire_parse (char command[3], long int pin, char *arg);

#endif