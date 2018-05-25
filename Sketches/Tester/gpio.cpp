#include "gpio.h"
#include <Arduino.h>

inline bool analog (const char * command, long pin, const char * arg)
{
    switch (command[1]) {
        case 'r': {
            Serial.println(analogRead(pin));
            return true;
        }
        case 'w': {
            long int value = strtol(arg, 0, 10);
            analogWrite(pin, value);
            return true;
        }
    }
}

inline bool digital (const char * command, long pin, const char * arg)
{
    switch (command[1])
    {
        case 'r': {
            Serial.println(digitalRead(pin));
            return true;
        }
        case 'w': {
            long int value = strtol(arg, 0, 10);
            digitalWrite(pin, value);
            return true;
        }
    }
}

inline bool pin_mode (const char * command, long pin, const char * arg)
{
    switch (command[1])
    {
        case 'm': switch (arg[0]) {
            case 'i': {
                pinMode(pin, INPUT);
                return true;
            }

            case 'o': {
                pinMode(pin, OUTPUT);
                return true;
            }
        }
    }
}

bool gpio_parse(const char * command, long pin, const char * arg)
{
    switch (command[0])
    {
        case 'a': return analog(command, pin, arg);

        case 'd': return digital(command, pin, arg);

        case 'p': return pin_mode(command, pin, arg);
    }  
}