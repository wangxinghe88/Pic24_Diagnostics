/* Scpi Interface Source

		Created 		Sun Jun 27 14:06:33 2010

		Using F:\Guildline\6622a\Remote Testing Templates\Pic24 Diagnostics.stf
			Device Pic24 Diagnostics

*/

#include "Scpi.h"

/* Scpi Structure Definitions */
struct scpi_struct const scpi[32] = 
		{{0,0,0,0},{5,0,0,0},{19,0,0,0},{24,0,0,0},{30,1,0,0},
		 {41,0,0,0},{47,0,0,0},{53,0,0,0},{59,0,0,0},{64,0,0,0},
		 {70,0,0,0},{76,1,0,0},{87,0,0,0},{93,0,0,0},{99,0,0,0},
		 {104,0,0,0},{117,3,0,0},{150,0,0,0},{163,3,0,0},{200,0,0,0},
		 {209,1,0,0},{232,0,0,0},{264,1,0,0},{318,0,0,0},{324,0,0,0},
		 {338,1,0,0},{366,0,0,0},{378,0,0,0},{393,0,0,0},{409,0,0,0},
		 {424,0,0,0},{437,0,0,0}};

unsigned char const ScpiCount = 32;

/* Def Structure Definitions */
struct scpi_struct const def[8] = 
		{{0,1,0,0},{12,4,0,0},{70,1,0,0},{82,1,0,0},{94,1,0,0},
		 {117,1,0,0},{140,1,0,0},{167,1,0,0}};

unsigned char const DefCount = 8;

/* Enumerated Array Definitions */
 int enumeratedArray[1] =
		{0};

/* Scpi Definitions */
char const scpiCommands[450] = 
		"*RST\0"
		"SYSTem:REMOTE\0"
		"*CLS\0"
		"*ESE?\0"
		"*ESE <ese>\0"
		"*ESR?\0"
		"*IDN?\0"
		"*OPC?\0"
		"*OPC\0"
		"*OPT?\0"
		"*SRE?\0"
		"*SRE <sre>\0"
		"*STB?\0"
		"*TST?\0"
		"*WAI\0"
		"SYSTem:DATE?\0"
		"SYSTem:DATE <year>,<month>,<day>\0"
		"SYSTem:TIME?\0"
		"SYSTem:TIME <hour>,<minute>,<second>\0"
		"MEASure?\0"
		"MEASure <measureState>\0"
		"Configure:Displayfrequencyrate?\0"
		"Configure:Displayfrequencyrate <displayFrequencyRate>\0"
		"RESET\0"
		"SerialNumber?\0"
		"SerialNumber <serialNumber>\0"
		"SYSTem:KEY?\0"
		"SYSTem:LOCKOUT\0"
		"SYSTem:VERSion?\0"
		"SYSTem:VERBose\0"
		"SYSTem:TERSe\0"
		"SYSTem:LOCAL\0";

/* Def Definitions */
char const defCommands[185] = 
		"*ESR? <esr>\0"
		"*IDN? <manufacturer>,<deviceid>,<serialNumber>,<revision>\0"
		"*OPC? <opc>\0"
		"*OPT? <opt>\0"
		"*STB? <StatusRegister>\0"
		"*TST? <StatusRegister>\0"
		"SYSTem:VERSion? <revision>\0"
		"SYSTem:KEY? <key>\0";

/* Variable Structure Definitions */
struct variable_struct const variable[19] = 
		{{0,5,50,0,0,17},{13,5,35,0,51,20},{22,3,1,7,0,23},{35,5,5,0,87,27},{44,0,1,0,0,7},
		 {59,0,1,0,1,7},{63,0,1,0,2,7},{67,0,1,0,3,7},{71,0,1,0,4,7},{75,0,1,0,5,7},
		 {79,4,1,0,0,11},{91,0,1,7,6,7},{104,2,1,7,0,0},{125,2,1,7,4,30},{130,0,1,7,10,7},
		 {136,0,1,7,14,7},{140,0,1,7,18,7},{145,0,1,7,22,7},{152,0,1,7,26,7}};

unsigned char const SetCount = 19;

/* Variable Names Definitions */
char const variableName[159] = 
		"manufacturer\0"
		"deviceid\0"
		"serialNumber\0"
		"revision\0"
		"StatusRegister\0"
		"ese\0"
		"esr\0"
		"sre\0"
		"opc\0"
		"opt\0"
		"temperature\0"
		"measureState\0"
		"displayFrequencyRate\0"
		"year\0"
		"month\0"
		"day\0"
		"hour\0"
		"minute\0"
		"second\0";

/* Format Definitions */
char const format[34] = 
		"%d\0"
		"%ld\0"
		"%hu\0"
		"%f\0"
		"%s\0"
		"%s\0"
		"%s\0"
		"%li\0"
		"%s\0"
		"%4i\0";

/* char Array Definitions */
char charArray[93] = 
		"Guildline Instruments\0" "............................"
		"\0"
		"Pic24 Diagnostics\0" "................."
		"\0"
		"A\0" "...";

/* Unsigned Char Array Definitions */
unsigned char unsignedCharArray[30] =
		{5,0,0,0,0,0,0,0,0,1,1,1,1,12,1,1,1,31,0,1
		,1,23,0,0,0,59,0,0,0,59};

/* Int Array Definitions */
 int intArray[8] =
		{1,1,1,3600,2010,2010,1999,2100};

/* Long Int Array Definitions */
long int longIntArray[4] =
		{0,0,0,200000};

/* Double Array Definitions */
double doubleArray[1] =
		{0.0};

/* esr Index value */
unsigned char const esrIndex = 6;
unsigned char ScpiExit;
/* Scpi variables	*/
unsigned char ScpiIndex;
unsigned char DefIndex;




/* Scpi User Exits	*/
void UserExits(void) {
	switch (ScpiExit) {

		case 16:
/*	SYSTem:DATE <year>,<month>,<day>	*/
			setDate(intArray[4],unsignedCharArray[10+enumLimit],unsignedCharArray[14+enumLimit]);
			break;

		case 18:
/*	SYSTem:TIME <hour>,<minute>,<second>	*/
			setTime(unsignedCharArray[18+enumLimit],unsignedCharArray[22+enumLimit],unsignedCharArray[26+enumLimit]);
			break;

		case 20:
/*	MEASure <measureState>	*/
			measureStateChange(unsignedCharArray[6+enumLimit]);
			break;

		case 25:
/*	SerialNumber <serialNumber>	*/
			setSerialNumber(longIntArray[0]);
			break;

	}
}

