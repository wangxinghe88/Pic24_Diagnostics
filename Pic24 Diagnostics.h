/* Scpi Interface Header

		Created 		Sun Jun 27 14:06:33 2010

		Using F:\Guildline\6622a\Remote Testing Templates\Pic24 Diagnostics.stf
			Device Pic24 Diagnostics

*/

/* #define statements    */
#define COMMAND_MAX 200
#define MIN_DEFINED 1
#define MAX_DEFINED 2
#define DEFAULT_DEFINED 4
#define INDEX_ENUMERATED_DEFINED 8
#define DEVICEID_DEFINED 16
#define VALUE 0
#define DEFAULT 1
#define MIN 2
#define MAX 3
#define unsignedCharDef 0
#define shortIntDef 1
#define intDef 2
#define longIntDef 3
#define doubleDef 4
#define charDef 5

/* scpi_struct statements */
struct scpi_struct{
	short int commandIndex;
	unsigned char argumentCount;
	unsigned char enumeratedCount;
	unsigned char enumeratedIndex;
};

/* variable_struct statements */
struct variable_struct{
	unsigned char variableIndex;
	unsigned char type;
	unsigned char arrayMax;
	 unsigned char modes;
	unsigned char valueIndex;
	unsigned char  formatIndex;
};

/* Scpi Structure Definitions */
extern struct scpi_struct const scpi[32];

extern unsigned char const ScpiCount;

/* Def Structure Definitions */
extern struct scpi_struct const def[8];

extern unsigned char const DefCount;

/* Enumerated Array Definitions */
extern  int enumeratedArray[1];

/* Scpi Definitions */
extern char const scpiCommands[450];

/* Def Definitions */
extern char const defCommands[185];

/* Variable Structure Definitions */
extern struct variable_struct const variable[19];

extern unsigned char const SetCount;

/* Variable Names Definitions */
extern char const variableName[159];

/* Format Definitions */
extern char const format[34];

/* char Array Definitions */
extern char charArray[93];

/* Unsigned Char Array Definitions */
extern unsigned char unsignedCharArray[30];

/* Int Array Definitions */
extern  int intArray[8];

/* Long Int Array Definitions */
extern long int longIntArray[4];

/* Double Array Definitions */
extern double doubleArray[1];

/* esr Index value */
extern unsigned char const esrIndex;
extern unsigned char ScpiExit;
extern unsigned char ProcessScpi(char* ScpiCommandLine);

/* Scpi variables	*/
extern unsigned char ScpiIndex;
extern unsigned char DefIndex;
/* Scpi Variable defines	*/
#define eseIndex 1
#define eseType 0
#define eseModes 0
#define sreIndex 3
#define sreType 0
#define sreModes 0
#define yearIndex 4
#define yearType 2
#define yearModes 7
#define monthIndex 10
#define monthType 0
#define monthModes 7
#define dayIndex 14
#define dayType 0
#define dayModes 7
#define hourIndex 18
#define hourType 0
#define hourModes 7
#define minuteIndex 22
#define minuteType 0
#define minuteModes 7
#define secondIndex 26
#define secondType 0
#define secondModes 7
#define measureStateIndex 6
#define measureStateType 0
#define measureStateModes 7
#define displayFrequencyRateIndex 0
#define displayFrequencyRateType 2
#define displayFrequencyRateModes 7
#define serialNumberIndex 0
#define serialNumberType 3
#define serialNumberModes 7


/* Scpi User Exits	*/
extern void setDate(int year,unsigned char month,unsigned char day);
extern void setTime(unsigned char hour,unsigned char minute,unsigned char second);
extern void measureStateChange(unsigned char measureState);
extern void setSerialNumber(long int serialNumber);


