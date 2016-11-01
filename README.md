Head Development Kit
====================

This repository contains various resources for the development of 
add-on heads for the FABtotum. For general pointers on custom heads 
development, see: http://www.fabtotum.com/head-development-guidelines.


Checklist
---------

- **Get** the complete [Head Development Kit](https://store.fabtotum.com/intl/head-development-kit.html)
- **Print** the simple [HDB support](http://www.thingiverse.com/thing:1832391)
- Get **inspired** by example [sketches](Sketches)
- **Learn** from the detailed [documentation](Documentation)


Some more detail
--------------

### HDB Support

You can self-print and make use of this barebone support for the HDB to
hack on your custom heads: http://www.thingiverse.com/thing:1832391

Source CAD models are available in [HDB Support](HDB Support), in
Autodesk Inventor (.ipt) and STEP (.stp) formats.


### Sketches

The [Sketches](Sketches) folder contains Arduino sketches that can be 
run on a Arduino Nano or similar development boards mounted on the 
FABtotum Personal Fabricator through a HDB.

All sketches require the latest development version of FABlin. You can 
compile it yourself from 
[source](https://github.com/FABtotum/FABlin/tree/development) or flash 
the precompiled [hex 
file](https://github.com/FABtotum/Head-Development-Kit/blob/master/Firmware/FABlin-1.0.0096.hex) 
present in this repository.

#### Sketches available:

- [**Dimmer**](https://github.com/FABtotum/Head-Development-Kit/tree/master/Sketches/Dimmer):
  A simple example that shows how to command led luminosity on an 
  Arduino Nano mounted on the head slot through the HDB.
