/**
 * HDB Dimmer
 * 
 * Implements a simple dimmer for Nano's onboard led (pin 13).
 * Light intensity can be commanded from the FABtotum user interface.
 * 
 * 
 * Steps to run:
 * 
 * Set a custom head id for your head:
 * 
 *   M793 S100
 * 
 * with any number equal or above 100.
 * 
 * Enable communication for the current head:
 * 
 *   M563 P0 S1
 * 
 * Configure communication parameters
 * 
 *   M575 P4 R<rx_pin> T<tx_pin> B<BAUDRATE>
 * 
 * where:
 * 
 *   <rx_pin>, <tx_pin> depend on HDB-Nano wiring
 * 
 *   <BAUDRATE> is as #define's later in this sketch
 *  
 * Send a command:
 * 
 *   M790 P4 "<cmd>"
 * 
 * where <cmd> is any of:
 * 
 *   0-9 to set led's intensity
 *   +/- to increment/decrement led's intensity
 */ 

/**
 * Configuration
 */

#define sRX   0
#define sTX   1
#define BAUDRATE 9600

#define LED 13

/**
 * Sketch
 */

#include <Arduino.h>

#if (sRX != 0) || (sTX != 1)
   #include <SoftwareSerial.h>
   #define Serial softSerial

   SoftwareSerial softSerial(sRX, sTX);
#endif

void setup ()
{
   pinMode(LED, OUTPUT);

   Serial.begin(BAUDRATE);
}

void loop ()
{
   static uint8_t counter = 0;
   static uint8_t power   = 0;
   static char req[256] = "";
   static uint8_t q_i = 0;

   static uint8_t state = 1;

   if (counter == 0 && power > 0) {
      digitalWrite(LED,1);
   }

   if (counter++ > power) {
      digitalWrite(LED,0);
   }

   while (Serial.available())
   {
      register unsigned char chin = Serial.read();
      switch (chin)
      {
         case '+':
            digitalWrite(LED,1);
            if (power < 240) {
               power += 16;
            } else {
               power = 255;
            } break;
         case '-':
            if (power >= 16) {
               power -= 16;
            } else {
               power = 0;
            } break;
         default:
            if (chin >= '0' && chin <= '9') {
               power = 28 * (chin - '0');
            }
      }
   }
}
