//#define DEBUG_NANO 1
/* Event_Status_Register */
#define	ESR_PON		(1<<7)		/* Power On */
#define	ESR_URG		(1<<6)		/* User Request */
#define	ESR_CME		(1<<5)		/* Command error */
#define	ESR_EXE		(1<<4)		/* Execution Error */
#define	ESR_DDE		(1<<3)		/* Device Dependant Error */
#define	ESR_QYE		(1<<2)		/* Query Error */
#define	ESR_RQC		(1<<1)		/* Request Control */
#define	ESR_OPC		(1<<0)		/* Operation Complete */

extern volatile long tickCounter;
extern long int turns;
extern int esr;
extern char EchoOn;
extern int temperature, prevTemperature;
extern char temperatureSensorEnabled;
extern volatile int nanoState;
extern long nanoData;
#define NANO_MAX 20
extern long nanoArray[NANO_MAX];
extern volatile int nanoIndex1;
extern volatile int nanoIndex2;
extern void InitHardware(void);
extern char checkPC(void);
extern char getPCKey(void);
extern void PCputc(char c);
extern void PCputs(char *);
extern char checkSW1(void);
extern void OutputPort(char port, char bitNumber, char bitValue);
extern void ReadMCP9801(void);
extern void InitMCP9801(void);
