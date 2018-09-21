#ifndef HARDWARE_FACTORY_H_
#define HARDWARE_FACTORY_H_

#include <Hardware.h>

Hardware HardwareFactory();

void isrArmSwitchChange();
void isrTriggerSwitchChange();

#endif