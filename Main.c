/************************************************************************/
/*                                                                      */
/*              DEVELOPED BY:   Iain Page					            */
/*                              1763 Heron Road		                    */
/*                              Ottawa, Ontario Canada K1V6A2           */
/*                              613.737.3986                            */
/*                              IainPage@IGS.NET                        */
/*                                                                      */
/*              Copyright 2009 Iain Page. All rights reserved.          */
/*                                                                      */
/************************************************************************/

/*************************************************************************
*   $MODULE
*   This is a simple example of using MiCOS. This program uses two states
*	and three tasks. It is a simple program that watches the keyboard and
*	responds appropriately to the key press.
*
*************************************************************************/

/*************************************************************************
*   $INCLUDES
*************************************************************************/
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include <ctype.h>
#include "mi_app.h"
#include "Hardware.h"
#include "Scpi.h"
/*************************************************************************
*   $DEFINES
*************************************************************************/

/*************************************************************************
*   $LOCAL PROTOTYPES
*************************************************************************/
void taskMain(void);            
void taskProcessScpi(void);

TMiResult stateTest(void);
TMiResult stateExit(void);

/*************************************************************************
*   $GLOBAL VARIABLES
*************************************************************************/
TMiTask *MiTaskList[] = {
	&taskMain,
	&taskProcessScpi,
};

/* you MUST define MI_MAX_TASKS for the number of tasks in your task list */
TMiWord MI_MAX_TASKS = sizeof(MiTaskList) / sizeof(MiTaskList[0]);

/* the state transition table for the system */
TMiStateTransEntry MiStateTable[MI_MAX_STATE_TRANS_ENTRIES] = {
  {&stateTest, RES_SAME_STATE, &stateTest},
  {&stateExit, RES_SAME_STATE, &stateExit},
};

/*************************************************************************
*   $LOCAL VARIABLES
*************************************************************************/


/************************************************************************/


/***************************************************************************

  Routine Name: main

  Date Created: May 23, 2009

        Author: Iain Page

   Description: The main function for the example. This just launches MiCOS.

         Input:

        Output:

                    Changes
   Number       Date        Initials    Description

**************************************************************************/

int main(void)

{
	InitHardware();
	MiCos();                                                                   
	return 0;
}
   


/***************************************************************************

  Routine Name: stateTest

  Date Created: May 23, 2009

        Author: Iain Page

   Description: A simple state function that just stays alive.

         Input: None

        Output: State results

                    Changes
   Number       Date        Initials    Description

**************************************************************************/

TMiResult stateTest(void)

{
	TMiResult result;
	switch (MiCurrentEvent) {
//		case EV_KEY_EXIT:
//			result = RES_DONE;				/* Esc was pressed, change state */
//			break;

		default:
			result = RES_SAME_STATE;     	/* any other events, keep chugging along */
			break;
	}		
	return result;
}




/***************************************************************************

  Routine Name: stateExit

  Date Created: May 23, 2009

        Author: Iain Page

   Description: A simple state function that just exists the code.

         Input: None

        Output: State results

                    Changes
   Number       Date        Initials    Description

**************************************************************************/

TMiResult stateExit(void)

{
	exit(0);
	return RES_SAME_STATE;
}


/***************************************************************************

  Routine Name: taskMain

  Date Created: May 20, 2009

        Author: Iain Page

   Description: This task will check for Scpi processing. If active 
			this will write an event to the queue.

         Input: None

        Output: None

                    Changes
   Number       Date        Initials    Description

**************************************************************************/
char startupFlag;
char tempBuff[250];
double displayTemperature;

#define MAX_TEMPERATURE_COUNT 20
double temperatureArray[MAX_TEMPERATURE_COUNT];
int temperatureIndex = 0;
int temperatureCount = 0;
double temperatureTotal;
int DisplayFrequencyRate = 1;	
int loop;
void taskMain(void)
{

	if (MiCurrentEvent == EV_INIT) {
		startupFlag = 1;
		EchoOn = 0;
	}
	if (MiCurrentEvent == EV_TICK_500_MSEC) {
		if (temperatureSensorEnabled == 1) {
				ReadMCP9801();
				temperatureTotal = 0.0;
				temperatureArray[temperatureIndex++] = (double) temperature / 16.0;
				if (temperatureCount < MAX_TEMPERATURE_COUNT)
					temperatureCount++;
				if (temperatureIndex >= MAX_TEMPERATURE_COUNT)
					temperatureIndex = 0;
				for (loop = 0; loop < temperatureCount; loop++)
					temperatureTotal += temperatureArray[loop];
				displayTemperature = temperatureTotal/temperatureCount;
		}
		if (startupFlag) {
			InitMCP9801();
			startupFlag = 0;
		}	
		OutputPort('B',1,1);
	}
	if (MiCurrentEvent == EV_TICK_1_SECOND) {
		if (temperatureSensorEnabled == 0) {
			InitMCP9801();
		}
		if (++DisplayFrequencyRate > intArray[displayFrequencyRateIndex]) {
			DisplayFrequencyRate = 1;
			if (unsignedCharArray[measureStateIndex]) {
				if (temperatureSensorEnabled == 1) {
					sprintf (tempBuff, "\x02,%3.2f\r\n",displayTemperature);
					PCputs((char *)tempBuff);
				}
				else {
					sprintf (tempBuff, "\x02,%3.2f\r\n",0.0);
					PCputs((char *)tempBuff);
				}
			}
		}
	}

	if (MiCurrentEvent == EV_PROCESS_NANO) {
		if (unsignedCharArray[measureStateIndex]) {
			for (loop = 0; loop <= nanoState; loop++)
				PCputc (',');
			sprintf (tempBuff, ",,%ld\r\n", nanoArray[nanoIndex1]);		
			PCputs((char *)tempBuff);
			if (++nanoIndex1 >= NANO_MAX)
				nanoIndex1 = 0;
		}
	}

	if (MiCurrentEvent == EV_IDLE) {
		if ((checkSW1())) { 			/* switch activated? */
			unsignedCharArray[measureStateIndex] ^= 1;
			OutputPort('B',2,unsignedCharArray[measureStateIndex] ^ 1);
		}
			
	}
}
                                             


/***************************************************************************

  Routine Name: taskProcessScpi

  Date Created: May 20, 2009

        Author: Iain Page

   Description: This task will respond to the event of a key being in the buffer.
   				If there is this event, this will read the key and generate the
   				appropriate new event for processing by another task.		

         Input: None

        Output: None

                    Changes
   Number       Date        Initials    Description

**************************************************************************/

void taskProcessScpi(void)
{       
	int c;
	int index1;
	char ScpiCommandLine[200];	
	if (MiCurrentEvent == EV_PROCESS_SCPI) {
/* read the command line from the buffer */
		index1 = 0;
		c = getPCKey();
/* ignore leading (CR) (LF) */
		if (c == '\n' || c == '\r')
			return;
		while (c != '\r' && c != '\n') {
			ScpiCommandLine[index1++] = c;
			c = getPCKey();
		}
		ScpiCommandLine[index1] = '\0';
		ProcessScpi(ScpiCommandLine);
	}
}
			

