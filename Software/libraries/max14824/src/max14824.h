/* MAX14824 Library
	Copyright (C) 2018, lukas.kropf#

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MAX14824_H_INCLUDED
#define _MAX14824_H_INCLUDED

#include <Arduino.h>
#include <stdio.h>



// Basic settings for the MAX14824
#define MAX14824SPISPEED 	12000000			//Maximum SPI clock speed
#define MAX14824SPIMODE 	SPI_MODE0
#define MAX14824SPIORDER 	MSBFIRST

#define IOLINKCOM1			4800
#define IOLINKCOM2			38400
#define IOLINKCOM3			230400




const uint8_t max14824SpiRegisterStatus 	= 0;
const uint8_t max14824SpiRegisterCqconfig 	= 1;
const uint8_t max14824SpiRegisterDioconfig 	= 2;
const uint8_t max14824SpiRegisterMode		= 3;


class MAX14824 {
public:
     void begin(	int address,
      				int chipselect,
  					int irq,
 					int serialNr,
 					int txen,
 					int wuen,
 					int li,
 					int uv,
					int txc);
    uint8_t 	readStatus		(void);
    uint8_t 	readCqconfig	(void);
    uint8_t 	readDioconfig	(void);
    uint8_t 	readMode		(void);
    void 		writeCqconfig	(uint8_t valueCqconfig);
    void 		writeDioconfig	(uint8_t valueDiconfig);
    void 		writeMode		(uint8_t valueMode);
    boolean 	ioConnect		(void);
    void		readDigital		(void);
private:
    // https://datasheets.maximintegrated.com/en/ds/MAX14824.pdf#page=14 MAX14824 pin Description
    int address;			// Hardware Address of the IO-Link Master IC. See schematic.
    int chipselect;			// Hardware Chipselect Pin
    int irq;				// Hardware Interrupt Request Pin from MAX14824
    int serialNr;			// Which serial Interface on the Arduiono DUE is used for communication the IO-Link Node (Values from 0 to 3 )
    int txen;				// Transmitter Enable. Driving TXEN high enables the C/Q transmitter
    int wuen;				// Wake-Up Enable Output to the MAX14824;
    int li;					// Logic Output of 24V DI Logic Input. LI is the inverse logic of DI
    int uv;					// Open-Drain Undervoltage Indicator Output. UV is active high. Page 2 and
    int txc;				// Transmit Communication Input. TXC is ANDed with TXQ. Drive TXC high if not in use.


};




#endif //  _MAX14824_H_INCLUDED
