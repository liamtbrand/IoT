# Schematics

The files .sch are schematics for the design of the wall switch.

The upper left part of the design is the switch input control.
This pulls PinX LOW when the switch is closed, and HIGH when open.
WallSwitch.h contains the code to get this input.

The lower right part of the design is the controlled switch.
This will connect the mains power supply when the pin is pulled LOW,
and will disconnect the power when the pin is pulled HIGH.
PowerSwitch.h contains the code to control this switch.

On powerup the esp should be checking to see the last known status of the switch from the server, and restoring this.
