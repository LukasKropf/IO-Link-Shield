// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _IoLinkMaster_H_
#define _IoLinkMaster_H_

#include "Arduino.h"
#include <SPI.h>
#include "libraries/max14824/src/max14824.h"


const int master0to3Spics	= 11;

const int master0Address	= 0;
const int master0Wuen 		= 9;
const int master0Li			= 8;
const int master0Uv			= 7;
const int master0Irq		= 5;
const int master0Serialnr	= 0;
const int master0Txc		= 1;
const int master0Txen		= 6;

const int master1Address	= 1;
const int master1Wuen 		= 30;
const int master1Li			= 31;
const int master1Uv			= 32;
const int master1Irq		= 4;
const int master1Serialnr	= 1;
const int master1Txc		= 18;
const int master1Txen		= 33;

const int master2Address	= 2;
const int master2Wuen 		= 26;
const int master2Li			= 27;
const int master2Uv			= 28;
const int master2Irq		= 3;
const int master2Serialnr	= 2;
const int master2Txc		= 16;
const int master2Txen		= 29;

const int master3Address	= 3;
const int master3Wuen 		= 22;
const int master3Li			= 23;
const int master3Uv			= 24;
const int master3Irq		= 2;
const int master3Serialnr	= 3;
const int master3Txc		= 14;
const int master3Txen		= 25;











#endif /* _IoLinkMaster_H_ */
