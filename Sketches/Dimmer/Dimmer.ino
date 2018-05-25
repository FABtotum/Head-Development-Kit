/**
 * HDB Dimmer
 *
 * Implements a simple dimmer for the onboard led. Light intensity can be
 * commanded from the FABtotum Jog page.
 *
 * Compatible with:
 *
 *  Arduino Nano-like boards sporting an ATmega 168/328 microcontroller
 */

/**
 * Wiring
 *
 * See wiring.png for wiring diagram to an Arduino Nano v3
 *
 * Possible wirings (Nano <-> HDB <-> TOTUMduino) and corresponding
 * FABlin serial configuration parameters:
 *
 *  Nano    HDB
 * -------------
 *  +5V <-> ARDUINO +
 *  GND <-> ARDUINO GND
 *  RX0 <-> SDA <---.
 *  TX1 <-> PWM <-   \
 *                |   |
 *                v   v
 *      M575  P4 R11 T20 B...
 *
 *  Nano    HDB
 * -------------
 *  +5V <-> ARDUINO +
 *  GND <-> ARDUINO GND
 *  RX0 <-> SCL <---.
 *  TX1 <-> PWM <-   \
 *                |   |
 *                v   v
 *      M575  P4 R11 T21 B...
 */

/**
 * Steps to run:
 *
 * - Flash this sketch to your board and wire it to your HDB according to
 *   the diagrams above.
 *
 * - In FAB-UI's jog page enter the following commands:
 *
 *     M793 S0
 *
 *   These will disable the current head and temperature management
 *   for the default tool configuration
 *
 * - You can now physically uninstall the current head and swap it with
 *   the HDB in a safe way
 *
 * - Set a custom head id for your head, e.g.:
 *
 *     M793 S100
 *
 * - Enable communication for the default tool:
 *
 *     M563 P0 S1
 *
 * - Configure communication parameters
 *
 *     M575 P4 R<rx_pin> T<tx_pin> B<BAUDRATE>
 *
 *   where:
 *
 *     <rx_pin>, <tx_pin> depend on the Nano-HDB wiring (refer to Wiring)
 *     <BAUDRATE> is as #define'd later in this sketch (refer to Configuration)
 *
 * - Send a command:
 *
 *     M790 P4 "<cmd>"
 *
 *   where <cmd> is any of:
 *
 *     0-9 to set led's intensity
 *     +/- to increment/decrement led's intensity
 *
 *
 * Pro tip:
 *
 * In FAB-UI/Colibri, you can automate the above procedure by defining a custom head.
 */

/**
 * Configuration
 *
 * You can change the desired communication baudrate and customize your
 * led's pin number.
 *
 * Available baud rates:
 *
 *  300 600 1200 2400 4800 9600 14400 19200 28800 31250 38400 57600
 *
 * Suggested rates fall between 9600 and 38400.
 */

#define BAUDRATE 38400

#define LED 13


/*
 * You should not need to change the following, but if you do, it will switch from
 * the predefined hardware serial interface to the software serial library.
 */

#define sRX   0
#define sTX   1


/*
 * Sketch
 */

#include <Arduino.h>

#if (sRX != 0) || (sTX != 1)
   #include <SoftwareSerial.h>
   #define Main    softSerial
   #define Monitor Serial

   SoftwareSerial Main(sRX, sTX);
#else
   #define Main Serial
#endif

void setup ()
{
   pinMode(LED, OUTPUT);

   Main.begin(BAUDRATE);
#ifdef Monitor
   Monitor.begin(9600);
   Monitor.println("start");
#endif
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

   while (Main.available())
   {
      register unsigned char chin = Main.read();
#ifdef Monitor
      Monitor.write("rx ");
      Monitor.write(chin);
      Monitor.println("");
#endif
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

      Main.println(power);
   }
}
