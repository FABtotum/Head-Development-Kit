Head Development Kit
====================

This repository contains various resources for the development of add-on heads for the FABtotum. For general pointers on custom heads development, see: http://www.fabtotum.com/head-development-guidelines.

Contents
--------
Contents of the repository:

### Sketches
The *Sketches* folder contains Arduino sketches that can be run on a Arduino Nano or similar development boards mounted on the FABtotum Personal Fabricator through a HDB.

All sketches require the latest development version of FABlin. You can compile it yourself from [source](https://github.com/FABtotum/FABlin/tree/development) or flash the precompiled [hex file](https://github.com/FABtotum/Head-Development-Kit/blob/master/FABlin/Marlin.cpp.hex) given in this repository.

Sketches available:

#### [Dimmer](https://github.com/FABtotum/Head-Development-Kit/tree/master/Sketches/Dimmer)
A simple example that shows how to command led luminosity on an Arduino Nano mounted on the head slot through the HDB.
