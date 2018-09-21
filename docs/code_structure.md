# Code Structure


## Hardware

Hardware-related low-level interaction occurs in the `lib/Hardware` space.

Hardware is attached to the "Hardware" struct in `hardware.h`, providing collective access to all hardware devices.

Further abstraction is allowed in other units of code.

## Routines

`Routines` can account for actions (eg. play a tune) or for modes of operation (eg. standby mode).

### Routine Controller

The `RoutineController` manages the collection of routines, and the active routine, as well as routine selection.

Routines can elect transition to another routine using the RoutineController.


