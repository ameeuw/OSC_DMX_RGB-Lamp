Open Sound Control DMX translator for an RGB light
================

This project translates incoming OSC messages over UDP to DMX signals. Similar products can be found on the chinese market but are still far off of the cost for the individual parts used for this build:

1 x Arduino Nano
1 x Micro ethernet-shield (Wiznet W5100)
1 x SN75176 level-shifter

The channels can be changed in the source, IP configuration and a debug and test mode are triggered by a menu that is available via the serial port. 
____________________

The light is a PAR-153-RGB lamp with 51 Red, 51 Green and 51 blue LEDs.
It is normally configured using DMX but in my case I built in an Arduino Nano
and a micro ethernet-shield.
This Handles incoming UDP-Packets which transfer OSC-messages from the webserver.