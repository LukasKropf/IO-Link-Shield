/* MAX14824 Library
	Copyright (C) 2018, BFH-TI Burgdorf

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

#include "max14824.h"

#include "SPI.h"


#define DEBUG 				1		// Use to debug the programm.


// ---------------------------------------------------------------
// --------- internal functions, not in the max14824.h --------------------------
// ---------------------------------------------------------------

boolean setRegister(int Register, int Address, int chipSelectPin, uint8_t valueWrite)
{
	// | Bit 7       | Bit 6 | Bit 5 |Bit 4  |Bit 3  |Bit 2  |Bit 1  |Bit 0  |
	// | ----------- | ----  |------ |-----  |-----  |-----  |-----  |-----  |
	// | W = 0, R = 1| 0     | Ad. 3 | Ad. 2 | Ad. 1 | Ad. 0 | Reg.1 | Reg.0 |

	uint16_t 		writeAdressRegister 		= 0;	// Preparation for writing
	const uint16_t  write						= 0<<7;	// Bit 7 for writing a value.

	SPISettings settingsA (200000, MSBFIRST, SPI_MODE0);  //slow SPI settings, specific for the Arduino Due



	writeAdressRegister = Address << 2;
	writeAdressRegister |= Register;
	writeAdressRegister |= write;
	writeAdressRegister = writeAdressRegister << 8;
	writeAdressRegister |= valueWrite;

	SPI.beginTransaction(settingsA);
	digitalWrite(chipSelectPin, LOW);

	#ifdef DEBUG
		Serial.print("CS Low\n");
	#endif

	// send a value of 0 to read the first byte returned:
	SPI.transfer16(writeAdressRegister);

	digitalWrite(chipSelectPin, HIGH);
	SPI.endTransaction();


	#ifdef DEBUG
		Serial.print("CS HIGH\n");
		Serial.print("\n");
		Serial.print(writeAdressRegister);
		Serial.print("\n");
		Serial.print("\n");

	#endif
	return true;
}

uint8_t readRegister(int Register, int Address, int chipSelectPin) {


	// | Bit 7       | Bit 6 | Bit 5 |Bit 4  |Bit 3  |Bit 2  |Bit 1  |Bit 0  |
	// | ----------- | ----  |------ |-----  |-----  |-----  |-----  |-----  |
	// | W = 0, R = 1| 0     | Ad. 3 | Ad. 2 | Ad. 1 | Ad. 0 | Reg.1 | Reg.0 |

	uint16_t 	inByte 						= 0;    // incoming from  the SPI read
	uint16_t 	readAdressRegister 			= 0;	// Preparation of the ReadAdress
	uint16_t  read						= 1<<7;	// Bit 1 for reading a value.
	unsigned int result 					= 0;   	// result to rimmkmölkjhnk.jb ,n
	SPISettings settingsA (200000, MSBFIRST, SPI_MODE0);



	readAdressRegister = Address << 2;
	readAdressRegister |= Register;
	readAdressRegister |= read;

	readAdressRegister = readAdressRegister << 8;

	SPI.beginTransaction(settingsA);
	digitalWrite(chipSelectPin, LOW);

	#ifdef DEBUG
		Serial.print("CS Low\n");
	#endif

	// send a value of 0 to read the first byte returned:
	inByte = SPI.transfer16(readAdressRegister,SPI_CONTINUE);
	//inByte = SPI.transfer(0x0);

	digitalWrite(chipSelectPin, HIGH);
	SPI.endTransaction();

	result = inByte;

	#ifdef DEBUG
		Serial.print("CS HIGH\n");
		Serial.print("\n");
		Serial.print(readAdressRegister);
		Serial.print("\n");
		Serial.print(result);
		Serial.print("\n");
	#endif

  return (result);
}




// ---------------------------------------------------------------
// --------- implementation of MAX14824 --------------------------
// ---------------------------------------------------------------


void MAX14824::begin(int address, int chipselect, int irq, int serialNr, int txen, int wuen, int li, int uv, int txc)
{
	//TODO check inputs if they are correct.
	this->address = address;
	this->chipselect = chipselect;
	this->irq = irq;
	this->serialNr = serialNr;
	this->txen = txen;
	this->wuen = wuen;
	this->li = li;
	this->uv = uv;
	this->txc = txc;


	pinMode(chipselect, OUTPUT);
	pinMode(irq, INPUT_PULLUP);
	pinMode(txen, OUTPUT);
	pinMode(wuen,OUTPUT);
	pinMode(li,INPUT);
	pinMode(uv, INPUT_PULLUP);

	pinMode(53,INPUT);
	pinMode(52,INPUT);
	pinMode(50,INPUT);



	SPI.begin(chipselect);
	digitalWrite(chipselect, HIGH);
	#ifdef DEBUG
		Serial.print("SPI.begin von CS \n");
	#endif
}


uint8_t MAX14824::readStatus(void)
{
	//	  128		64		32		16			8			 4			2			1
	// | Bit 7 | Bit 6  | Bit 5   | Bit 4  | Bit 3        | Bit 2   | Bit 1   | Bit 0    |
	// | ------| ----   |------   |-----   |-----------   |-----    |-----    |-----     |
	// | x     | x      | DiLvl   | ~QLvl  | C/QFaultInt  | UV33Int | UV24Int | OTempInt |

	// X = unused
	uint8_t resultat = 0;
	resultat = readRegister(max14824SpiRegisterStatus, this->address, this->chipselect);

	#ifdef DEBUG
		Serial.print("\nclass MAX14824::readStatus\n");
	#endif

	return resultat;
}

uint8_t MAX14824::readCqconfig(void)
{
	uint8_t resultat = 0;
	resultat = readRegister(max14824SpiRegisterCqconfig, this->address, this->chipselect);

	#ifdef DEBUG
		Serial.print("\nclass MAX14824::readCqconfig\n");
	#endif

	return resultat;
}

uint8_t MAX14824::readDioconfig(void)
{
	uint8_t resultat = 0;
	resultat = readRegister(max14824SpiRegisterDioconfig, this->address, this->chipselect);

	#ifdef DEBUG
		Serial.print("\nclass MAX14824::readDioconfig\n");
	#endif

	return resultat;
}

uint8_t MAX14824::readMode(void)
{
	// | Bit 7       | Bit 6  | Bit 5   | Bit 4  | Bit 3  | Bit 2 | Bit 1 | Bit 0   |
	// | ----------- | ----   |------   |-----   |-----   |-----  |-----  |-----    |
	// | RST         | WuEnBit| X       |C/QFault| UV24   | OTemp | UV33En| LDO33Dis|
	// | R/W         | R/W    | R/W     | R      | R      | R     | R/W   | R/W     |
	// X = unused
	uint8_t resultat = 0;
	resultat = readRegister(max14824SpiRegisterMode, this->address, this->chipselect);

	#ifdef DEBUG
		Serial.print("\nclass MAX14824::readMode\n");
	#endif

	return resultat;
}

void MAX14824::writeCqconfig(uint8_t valueCqconfig)
{
	// | Bit 7       | Bit 6  | Bit 5   | Bit 4  | Bit 3  | Bit 2 | Bit 1 | Bit 0   |
	// | ----------- | ----   |------   |-----   |-----   |-----  |-----  |-----    |
	// | RxFilter    | HiSlew | C/Q_N/P | C/Q_PP | C/QDEn | Q     | RxDis | C/QLoad |
	// All bits are R / W
	setRegister(max14824SpiRegisterCqconfig, this->address, this->chipselect, valueCqconfig);
}
void MAX14824::writeDioconfig(uint8_t valueDiconfig)
{
	// | Bit 7       | Bit 6  | Bit 5   | Bit 4  | Bit 3  | Bit 2 | Bit 1 | Bit 0   |
	// | ----------- | ----   |------   |-----   |-----   |-----  |-----  |-----    |
	// | X           | x      | x       | x      | x      | x     | LiDis | DiLoad  |
	// All bits are R / W
	// X = unused
	setRegister(max14824SpiRegisterDioconfig, this->address, this->chipselect, valueDiconfig);
}
void MAX14824::writeMode(uint8_t valueMode)
{
	// | Bit 7       | Bit 6  | Bit 5   | Bit 4  | Bit 3  | Bit 2 | Bit 1 | Bit 0   |
	// | ----------- | ----   |------   |-----   |-----   |-----  |-----  |-----    |
	// | RST         | WuEnBit| X       |C/QFault| UV24   | OTemp | UV33En| LDO33Dis|
	// | R/W         | R/W    | R/W     | R      | R      | R     | R/W   | R/W     |
	// X = unused
	setRegister(max14824SpiRegisterMode, this->address, this->chipselect, valueMode);

}


void MAX14824::readDigital(void)
{
	//TODO Implement Interrupt from the irq-pin of the IO-Link Master.
	#ifdef DEBUG
		Serial.print("UnderVoltage: ");
		Serial.print(digitalRead(uv));
		Serial.print("\nIO-Link Digital In: ");
		Serial.print(digitalRead(li));
		Serial.print("\nInterruptInput form IO-Master: ");
		Serial.print(digitalRead(irq));
		Serial.print("\n");
	#endif

}


// ---------------------------------------------------------------
// --------- implementation of IO-Link functions------------------
// ---------------------------------------------------------------

boolean MAX14824::ioConnect(void)
{
	//ToDo Connect to the IO-Link Node, Handshake.
	// http://www.io-link.com/share/Downloads/Spec-Interface/IOL-Interface-Spec_10002_V112_Jul13.pdf#page=71
	// https://datasheets.maximintegrated.com/en/ds/MAX14824.pdf#page=10

	//The MAX14824 features automatic wake-up polarity generation
	//functionality that can be initiated through hardware
	//or software. The following conditions must be met
	//prior to automatic wake-up polarity generation to ensure
	//proper functionality:
	//•	 WUEN is low
	//•	 TXEN is low and C/QDEn = 0
	//•	 Q = 0
	//•	 TXC and TXQ are both high
	//Drive WUEN high to enable the automatic wake-up
	//polarity generation circuitry in the device. When WUEN
	//is high, apply an external pulse to TXC or TXQ from
	//high-to-low for 80Fs (typ) to generate a valid wake-up
	//pulse. The applied pulse is independent of the logic
	//state that the IO-Link sensor was forcing on the C/Q level
	//(Figure 5). Drive WuEN low after the wake-up has been
	//generated


	// 	  				_________________________________
	// TXEN			____|								|______________
	//                    twuen,s                 twuen,h
	//			   _____|________|			     |______|_____
	// TXC and TXQ    			|______80µs______|
	//						      _________________
	// C/Q			______________| wake-up Pulse |_________________

	// twuen,s = twuen,h = 30ns

	digitalWrite(wuen,LOW);
	digitalWrite(txen, LOW);
	digitalWrite(txc, HIGH);
	delayMicroseconds(1000);; // Let everything settle

	digitalWrite(wuen,HIGH);
	delayMicroseconds(1);
	digitalWrite(txc,LOW);
	digitalWrite(txc,LOW);
	delayMicroseconds(80); // wait for 80µs,  is defined in Datasheet MAX14824, figure 5: Wake-Up Generation;
	digitalWrite(txc,HIGH);
	digitalWrite(wuen,LOW);
	delayMicroseconds(5);		// 5µs wait. then Start communication.

	//TODO: Selectable Serial Port
	Serial3.begin(IOLINKCOM2, SERIAL_8E1);		// http://www.io-link.com/share/Downloads/Spec-Interface/IOL-Interface-Spec_10002_V111_Oct11.pdf#page=47
	while(!Serial1); 	// Wait vor SerialPort 1,

	digitalWrite(txen,HIGH);
	Serial3.write(255);
	digitalWrite(txen,LOW);
	delay(2);
	Serial1.write(25);








return true;
}
