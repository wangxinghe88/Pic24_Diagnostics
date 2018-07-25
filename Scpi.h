#include "Pic24 Diagnostics.h"

/* Event_Status_Register */
#define	ESR_PON		(1<<7)		/* Power On */
#define	ESR_URG		(1<<6)		/* User Request */
#define	ESR_CME		(1<<5)		/* Command error */
#define	ESR_EXE		(1<<4)		/* Execution Error */
#define	ESR_DDE		(1<<3)		/* Device Dependant Error */
#define	ESR_QYE		(1<<2)		/* Query Error */
#define	ESR_RQC		(1<<1)		/* Request Control */
#define	ESR_OPC		(1<<0)		/* Operation Complete */

/* public  procedures */
#define READ_MAX 100
#define COMMAND_MAX 200
#define DEF 0
#define SCPI 1
extern void removeComments(char* charPtr);
extern int decodeCommand(char* charPtr);
extern int readScpi(char* charPtr,unsigned char type);
extern unsigned char findVariable(void);
extern unsigned char getScpiVariable(char* varPtr);
extern void putScpiVariable(char* varPtr, unsigned char val);
extern unsigned char getUnsignedChar(unsigned char type);
extern int getInt(unsigned char type);
extern long int getLongInt(unsigned char type);
extern void putUnsignedChar(unsigned char val);
extern void setESR(unsigned char esr);
extern void putInt(int val);
extern void UserExits(void);
extern void putLongInt(long val);
extern double getDouble(unsigned char type);
extern void putDouble(double val);
extern char CommandLine[COMMAND_MAX];
extern char* cmdptr;
extern char ReadResults[READ_MAX];
extern unsigned char ProcessState;
extern unsigned char ProcessScpi(char* ScpiCommandLine);
extern unsigned char enumIndex, enumLoop,enumLimit;
