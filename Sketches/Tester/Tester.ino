/*
 * Sketch: Tester.cpp
 *
 *  Development Head for FABtotum
 *
 * Description:
 * 
 * 	This sketch can dynamically control IO pins, manage a Two-Wire connection
 * and a SoftwareSerial instance on an arbitraty pair of pins. Control
 * commands and responses can be given through the main serial interface.
 * 
 *  The Two-Wire module can be setup to automatically respond to requests.
 * 
 *  This can also be useful to debug the connected electronics or the
 * firmware.
 * 
 *  The control language is schematic enough to be processed by a higher-level
 * controlling program but not so much that it can't be used by hand for
 * quick operations. All commands are two-letter and the output format is
 * reminiscent of the reprap guidelines
 * (as in http://reprap.org/wiki/G-code#Replies_from_the_RepRap_machine_to_the_host_computer).
 * 
 * 
 * Commands:
 *
 *  pm N i - Set pin N as input
 *  pm N o - Set pin N as output
 *
 *  dw N V - Set pin N to value V (0-1)
 *  dr N   - Read digital value on pin N
 *
 *  aw N V - Write analog value V (0-1023) to pin N
 *  ar N   - Read analog value from pin N
 * 
 *  ss RX TX - Setup a SoftwareSerial port on RX pin and TX pin
 *  sb B     - Start the SoftwareSerial port at baudrate B
 *  sr C B   - Read at most C bytes from software serial and print them in base B
 *  sw B STR - Write at STR to software serial parsed  in base B
 *  se       - Disable software serial interface
 *
 *  ws A   - Initialize Two-Wire interface with slave address A
 *  wr R V - Setup Wire register R with value V
 *           Register 7 is automatically filled with the other registers' CRC
 *  we     - Disable Two-Wire interface
 */
#ifndef _TESTER_INO_
#define _TESTER_INO_

// Section: Configuration
//
// The rest of this file contains hard-wired configuration

/**
 * Define: SERIAL_BAUDRATE
 * 
 *  Baud-rate for the main (control) serial
 */
#define SERIAL_BAUDRATE 9600

/**
 * Macros: logging level
 * 
 *  Set to false to disable corresponding log level
 * 
 *	DEBUG - true
 *	INFO  - true
 */
#define DEBUG true
#define INFO  true

#endif
