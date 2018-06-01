Head Development Kit
====================

This repository contains various resources for the development of
add-on heads for the FABtotum. For general pointers on custom heads
development, see: http://www.fabtotum.com/head-development-guidelines.

**WARNING**: Firmware support for custom add-ons is not yet stable,
therefore actual implementation may change with respect to these
information without notice. If you get stuck on something not working
do [post an issue](/FABtotum/Head-Development-Kit/issues/new) to let us
know, or file a pull-request if you have a possible fix.


Checklist
---------

- **Get** the complete [Head Development Kit](https://store.fabtotum.com/intl/head-development-kit.html)
- **Print** the simple [HDB support](http://www.thingiverse.com/thing:1832391)
- Get **inspired** by example [sketches](Sketches)
- **Learn** from the detailed [documentation](Documentation)


Some more detail
--------------

### HDB simple support

You can self-print and make use of this barebone support for the HDB to
hack on your custom heads: http://www.thingiverse.com/thing:1832391

Source CAD models are available inside [HDB Support](/FABtotum/Head-Development-Kit/tree/master/HDB+Support), in
Autodesk Inventor (.ipt) and STEP (.stp) formats.


### Sketches

The [Sketches](Sketches) folder contains Arduino sketches that can be
run on a Arduino Nano or similar development board mounted on the
FABtotum Personal Fabricator through a HDB.

All sketches are tested to work with
[FAB-UI/Colibri](/FABtotum/fabui-colibri) and a recent version of
[FABlin](/FABtotum/FABlin) (version 1.1.0 or later). You can compile it
yourself from the [sources](/FABtotum/FABlin/tree/master) or pick one
of the [released](/FABtotum/FABlin/releases) hex images.


#### Sketches available:

- [**Dimmer**](https://github.com/FABtotum/Head-Development-Kit/tree/master/Sketches/Dimmer):
  A simple example that shows how to command led luminosity on an
  Arduino Nano mounted on the head slot through the HDB.
- [**Tester**](https://github.com/FABtotum/Head-Development-Kit/tree/master/Sketches/Tester):
  A more complete example that let you interactively debug IO and communication on the HDB (beware of 24Vdc lines though ;)
  With this sketch you'll be able to dynamically set IO pins' modes and levels. It is also able to setup a serial interface or a Two Wire interface.
