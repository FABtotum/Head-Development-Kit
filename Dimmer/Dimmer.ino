/********** Conf **********/

#define hdb_BAUD 1200
#define LED 13

/**************************/

#include <Arduino.h>

void setup ()
{
   pinMode(LED, OUTPUT);

   Serial.begin(hdb_BAUD);
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
