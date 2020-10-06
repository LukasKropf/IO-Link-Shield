
#include "IoLinkMaster.h"		// Do not remove

//----------------------------------------------------
//------------- Defines  ----------------------
//----------------------------------------------------
#define DEBUG 				1		// Use to debug the programm.

//----------------------------------------------------
//------------- Global variables ----------------------
//----------------------------------------------------


MAX14824 master0,master1,master2,master3;

void setup()
{

	int IoLinkMasterStatus[4] = {-1,-1,-1,-1};
	int IoLinkMasterCqconfig[4]= {-1,-1,-1,-1};
	int IoLinkMasterDioconfig[4]= {-1,-1,-1,-1};
	int IoLinkMasterMode[4]= {-1,-1,-1,-1};
	String buf;

	Serial.begin(9600);
	while (!Serial)
	{
		// wait for serial port to connect
	}


	Serial.print("\nBeginne mit dem Senden\n");

	master0.begin(master0Address,master0to3Spics,master0Irq,master0Serialnr,master0Txen,master0Wuen,master0Li,master0Uv,master0Txc);
	master1.begin(master1Address,master0to3Spics,master1Irq,master1Serialnr,master1Txen,master1Wuen,master1Li,master1Uv,master1Txc);
	master2.begin(master2Address,master0to3Spics,master2Irq,master2Serialnr,master2Txen,master2Wuen,master2Li,master2Uv,master2Txc);
	master3.begin(master3Address,master0to3Spics,master3Irq,master3Serialnr,master3Txen,master3Wuen,master3Li,master3Uv,master3Txc);



	IoLinkMasterStatus[0] = master0.readStatus();
	IoLinkMasterStatus[1] = master1.readStatus();
	IoLinkMasterStatus[2] = master2.readStatus();
	IoLinkMasterStatus[3] = master3.readStatus();

	IoLinkMasterMode[1] = master3.readMode();
	IoLinkMasterDioconfig[1] = master3.readDioconfig();
	IoLinkMasterCqconfig[1] = master3.readCqconfig();

	//master0.readDigital();
	master3.readDigital();
	//master2.readDigital();
	//master3.readDigital();



    buf = IoLinkMasterStatus[0];
    buf += "  ";
    buf += IoLinkMasterStatus[1];
    buf += "  ";
    buf += IoLinkMasterStatus[2];
    buf += "  ";
    buf += IoLinkMasterStatus[3];
    buf += " --- ";

    buf += IoLinkMasterMode[1];
    buf += "  ";
    buf += IoLinkMasterDioconfig[1];
    buf += "  ";
    buf += IoLinkMasterCqconfig[1];
    buf += "\n";

    Serial.print(buf);

    Serial.print("test ioConnect");
    master3.ioConnect();
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
}
