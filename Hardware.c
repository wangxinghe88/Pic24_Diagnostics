#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "mi_app.h"
#include "Hardware.h"
#include "Scpi.h"
#include <p24FJ64GA002.h>
#include "DEE Emulation 16-bit.h"
#define EXTERNAL_OSCILLATOR 1
	_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & FWDTEN_OFF & ICS_PGx1) 
#ifdef EXTERNAL_OSCILLATOR
	_CONFIG2( FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_XT & FNOSC_PRIPLL & I2C1SEL_SEC & IOL1WAY_ON)
#else
	_CONFIG2( FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_NONE & FNOSC_FRCPLL & I2C1SEL_SEC & IOL1WAY_ON)
#endif

#ifdef EXTERNAL_OSCILLATOR
#define XTFREQ          7372800         		//On-board Crystal frequency
#define PLLMODE         2               		//On-chip PLL setting
#define FCY             XTFREQ*PLLMODE        //Instruction Cycle Frequency
#else
#define XTFREQ          8300000         		//On-board Crystal frequency
#define PLLMODE         4               		//On-chip PLL setting
#define FCY             XTFREQ*PLLMODE/2        //Instruction Cycle Frequency
#endif
#define BAUDRATE1         115200       
#define BRGVAL1          ((FCY/BAUDRATE1)/16)-1 

#define BAUDRATE2         19200       
#define BRGVAL2          ((FCY/BAUDRATE2)/16)-1 
#define I2C_TIMEOUT_VALUE 2500
#define U1RX_BUFFER_SIZE 512
#define U1TX_BUFFER_SIZE 512
#define U2RX_BUFFER_SIZE 2048
#define U2TX_BUFFER_SIZE 512

#define I2CBRGVAL		((FCY/(2*100000)))-1;


volatile unsigned char U1RxBuffer[U1RX_BUFFER_SIZE];
volatile int U1RxIntPointer, U1RxCurrentPointer;
volatile unsigned char U1TxBuffer[U1TX_BUFFER_SIZE];
volatile int U1TxIntPointer, U1TxCurrentPointer;
volatile unsigned char U2RxBuffer[U2RX_BUFFER_SIZE];
volatile int U2RxIntPointer, U2RxCurrentPointer;
volatile unsigned char U2TxBuffer[U2TX_BUFFER_SIZE];
volatile int U2TxIntPointer, U2TxCurrentPointer;
volatile int timerCounter;
volatile int timer250msCounter;
volatile int timerSecondCounter;
volatile long tickCounter;
int U1baudRate;
int U2baudRate;
long int turns;
char EchoOn;
int nanoIndex;
volatile int nanoIndex1;
volatile int nanoIndex2;
volatile int nanoState;
long nanoData;
long nanoArray[NANO_MAX];
long nanoDataTemp;
void InitHardware(void)
{
	CLKDIVbits.RCDIV = 0;
	OSCTUN = 10;

	RPINR18bits.U1RXR = 9;	// Make Pin RP9 U1RX
	RPOR4bits.RP8R = 3;		// Make Pin RP8 U1TX

	RPINR19bits.U2RXR = 7;	// Make Pin RP7 U2RX
	RPOR3bits.RP6R = 5;		// Make Pin RP6 U2TX
//	PADCFG1 = 0xFF;			// Make analog pins digital 

	TMR1 = 0;				// Clear timer 1
	PR1 = FCY/256/2;		// Interrupt every 500ms
	IFS0bits.T1IF = 0;		// Clear interrupt flag


/* I2C Initialize */

// Configre SCA/SDA pin as open-drain
	ODCBbits.ODB2=1;
	ODCBbits.ODB3=1;

	LATB = 0x0;
	TRISB = 0x06B3;

	U1BRG  = BRGVAL1;
	U1MODE = 0x8000; 		// Reset UART to 8-n-1, alt pins, and enable 
	U1STA  = 0x0440; 		// Reset status register and enable TX & RX
	_U1RXIF=0;					// Clear UART RX Interrupt Flag

	U2BRG  = BRGVAL2;
	U2MODE = 0x8000; 		// Reset UART to 8-n-1, alt pins, and enable 
	U2STA  = 0x0440; 		// Reset status register and enable TX & RX
	_U2RXIF=0;					// Clear UART RX Interrupt Flag

	I2C2BRG = I2CBRGVAL;
	I2C2ADD = 0;
	I2C2MSK = 0;
	I2C2CON = 0x9300;
	_MI2C2IF = 0;

	unsigned int value;
    DataEEInit();
    dataEEFlags.val = 0;
    value = DataEERead(0);
	if (value == 0x0FFFF) {
/*
		memcpy(&values[0],&doubleArray[currentIndex],4);
    	DataEEWrite(values[0],8);
    	DataEEWrite(values[1],10);
    	DataEEWrite(values[2],12);
    	DataEEWrite(values[3],14);
		memcpy(&values[0],&doubleArray[maxCurrentIndex],4);
    	DataEEWrite(values[0],16);
    	DataEEWrite(values[1],18);
    	DataEEWrite(values[2],20);
    	DataEEWrite(values[3],22);
*/
		DataEEWrite(longIntArray[serialNumberIndex] >> 16,0);
		DataEEWrite(longIntArray[serialNumberIndex] & 0x0FFFF,2);
	}
/*
	values[0] = DataEERead(8);
	values[1] = DataEERead(10);
	values[2] = DataEERead(12);
	values[3] = DataEERead(14);
	memcpy(&doubleArray[currentIndex],&values[0],4);
*/
    longIntArray[serialNumberIndex] = (long)(DataEERead(0)) << 16;
    longIntArray[serialNumberIndex] |= (long)DataEERead(2);

/* startup with measureState off */
	unsignedCharArray[measureStateIndex] = 0;

	nanoState = 0;
	nanoIndex = 0;
	tickCounter = 0;
	nanoDataTemp = 0;
	nanoData = 0;
	nanoIndex1 = 0;
	nanoIndex2 = 0;
	U1RxIntPointer = U1RxCurrentPointer = 0;	
	U1TxIntPointer = U1TxCurrentPointer = 0;	
	U2RxIntPointer = U2RxCurrentPointer = 0;	
	U2TxIntPointer = U2TxCurrentPointer = 0;	
	timerCounter = 0;
	timer250msCounter = 0;
	timerSecondCounter = 0;
	turns = 0;
	LATBbits.LATB13 = 1;
	LATBbits.LATB14 = 1;
	LATBbits.LATB15 = 1;
   _enable();
	T1CON = 0x8030;			// Fosc/4, 1:256 prescale, start TMR1
}
void _enable(void)
{
//	if (interruptStatus == 1) {
		IEC0bits.T1IE = 1;		// Set interrupt enable bit
//		IEC0bits.T1IE = 0;		// Set interrupt enable bit
		IEC0bits.U1RXIE = 1;
		IEC0bits.U1TXIE = 1;
		IEC1bits.U2RXIE = 1;
		IEC1bits.U2TXIE = 1;
//	}
}

void _disable(void)
{
	IEC0bits.T1IE = 0;		// clear interrupt enable bit
	IEC0bits.U1RXIE = 0;
	IEC0bits.U1TXIE = 0;
	IEC1bits.U2RXIE = 0;
	IEC1bits.U2TXIE = 0;
}

char checkPC(void) {
	if (U1RxIntPointer == U1RxCurrentPointer)
		return 0;
	else
		return 1;
}
char debounce = 0;
char checkSW1(void) {
	if (PORTBbits.RB5 == 1) {
		debounce = 0;
		return 0;
	}
	else {
		if (debounce == 0) {
			debounce = 1;
		return 1;
		}
		else
			return 0;
	}
}
void setSerialNumber(long int serialNumber) {
	DataEEWrite(longIntArray[serialNumberIndex] >> 16,0);
	DataEEWrite(longIntArray[serialNumberIndex] & 0x0FFFF,2);
}

void measureStateChange(unsigned char measureState) {
	OutputPort('B',2,measureState ^ 1);
}

void setDate(int year,unsigned char month,unsigned char day) {
}

void setTime(unsigned char hour,unsigned char minute,unsigned char second) {
}

char getPCKey(void) {
char a;
	while (checkPC() == 0);		// wait for data
	a = U1RxBuffer[U1RxCurrentPointer++];
	if (U1RxCurrentPointer > U1RX_BUFFER_SIZE -1)
		U1RxCurrentPointer = 0;
	if (EchoOn)
		PCputc(a);
	return a;
}
void OutputPort(char port, char bitNumber, char bitValue)
{
	if (port == 'B') {
		if (bitNumber == 1) {
			LATBbits.LATB12 ^= 1;
		}
		else if (bitNumber == 2) {
			LATBbits.LATB13 = bitValue;
		}
		else if (bitNumber == 3) {
			LATBbits.LATB14 = bitValue;
		}
		else if (bitNumber == 4) {
			LATBbits.LATB15 = bitValue;
		}
	}
}
void setTurns(long int turns) {
}

void setRelays(unsigned char enumIndex,unsigned char relays) {
}

int temperature, prevTemperature;
char temperatureSensorEnabled;

void ReadMCP9801(void) {
	I2C2CONbits.SEN = 1;
	while (_MI2C2IF == 0);
	_MI2C2IF = 0;
	I2C2CONbits.RSEN = 1;
	while (_MI2C2IF == 0);
	_MI2C2IF = 0;
	I2C2TRN = 0x091;
	while (_MI2C2IF == 0);
	_MI2C2IF = 0;
 	I2C2CONbits.RCEN = 1;
	while (_MI2C2IF == 0);
	_MI2C2IF = 0;
	temperature = I2C2RCV * 16;
	I2C2CONbits.ACKDT = 0;
	I2C2CONbits.ACKEN = 1;
	while (_MI2C2IF == 0);
	_MI2C2IF = 0;
	I2C2CONbits.RCEN = 1;
	while (_MI2C2IF == 0);
	_MI2C2IF = 0;
	temperature += I2C2RCV>>4;
	I2C2CONbits.ACKDT = 1;
	I2C2CONbits.ACKEN = 1;
	while (_MI2C2IF == 0);
	_MI2C2IF = 0;
	I2C2CONbits.PEN = 1;
	while (_MI2C2IF == 0);
	_MI2C2IF = 0;
}

void InitMCP9801(void) {
int status1,status2;
int I2C2Timeout;
	temperatureSensorEnabled = 1;
	I2C2CONbits.SEN = 1;
	I2C2Timeout = I2C_TIMEOUT_VALUE;
	while (_MI2C2IF == 0 && --I2C2Timeout > 0);
	if (I2C2Timeout == 0) {
		temperatureSensorEnabled = 0;
		return;
	}
	status1 = I2C2STAT;
	while (_MI2C2IF == 0);
	_MI2C2IF = 0;
	I2C2TRN = 0x090;
	I2C2Timeout = I2C_TIMEOUT_VALUE;
	while (_MI2C2IF == 0 && --I2C2Timeout > 0);
	if (I2C2Timeout == 0) {
	status2 = I2C2STAT;
		temperatureSensorEnabled = 0;
		return;
	}
	_MI2C2IF = 0;
	I2C2TRN = 1;		/* configuration address pointer */
	I2C2Timeout = I2C_TIMEOUT_VALUE;
	while (_MI2C2IF == 0 && --I2C2Timeout > 0);
	if (I2C2Timeout == 0) {
		temperatureSensorEnabled = 0;
		return;
	}
	_MI2C2IF = 0;
	I2C2TRN = 0x60;		/* configuration register 12 bit resolution */
	I2C2Timeout = I2C_TIMEOUT_VALUE;
	while (_MI2C2IF == 0 && --I2C2Timeout > 0);
	if (I2C2Timeout == 0) {
		temperatureSensorEnabled = 0;
		return;
	}
	_MI2C2IF = 0;
	I2C2CONbits.PEN = 1;
	I2C2Timeout = I2C_TIMEOUT_VALUE;
	while (_MI2C2IF == 0 && --I2C2Timeout > 0);
	if (I2C2Timeout == 0) {
		temperatureSensorEnabled = 0;
		return;
	}
	_MI2C2IF = 0;
	I2C2CONbits.SEN = 1;
	I2C2Timeout = I2C_TIMEOUT_VALUE;
	while (_MI2C2IF == 0 && --I2C2Timeout > 0);
	if (I2C2Timeout == 0) {
		temperatureSensorEnabled = 0;
		return;
	}
	_MI2C2IF = 0;
	I2C2TRN = 0x090;
	I2C2Timeout = I2C_TIMEOUT_VALUE;
	while (_MI2C2IF == 0 && --I2C2Timeout > 0);
	if (I2C2Timeout == 0) {
		temperatureSensorEnabled = 0;
		return;
	}
	_MI2C2IF = 0;
	I2C2TRN = 0;		/* temperature address pointer */
	I2C2Timeout = I2C_TIMEOUT_VALUE;
	while (_MI2C2IF == 0 && --I2C2Timeout > 0);
	if (I2C2Timeout == 0) {
		temperatureSensorEnabled = 0;
		return;
	}
	_MI2C2IF = 0;
	I2C2CONbits.PEN = 1;
	I2C2Timeout = I2C_TIMEOUT_VALUE;
	while (_MI2C2IF == 0 && --I2C2Timeout > 0);
	if (I2C2Timeout == 0) {
		temperatureSensorEnabled = 0;
		return;
	}
	_MI2C2IF = 0;
}

void PCputs (char * PCdata){
int index1;
	index1 = 0;
	while (PCdata[index1] != 0)
		PCputc((char)PCdata[index1++]);		
}

void PCputc(char c) {
   _disable();
	if (U1TxIntPointer == U1TxCurrentPointer && U1STAbits.UTXBF == 0) {
		U1TXREG = c;
	}
	else {
		U1TxBuffer[U1TxCurrentPointer++] = c;
		if (U1TxCurrentPointer > U1TX_BUFFER_SIZE -1)
			U1TxCurrentPointer = 0;		
	}
    _enable();
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
char a;
int status1;
	status1 = U1STA;
	if (status1 &1) {
//	if ((status1 & 4) == 0 && (status1 &1)) {
		a = U1RXREG;
		if (a >= '\x10' && a <= '\x19')
			nanoState = a & '\x0f';
		else {
			U1RxBuffer[U1RxIntPointer++] = a;

/* Trigger a Scpi event if end of line detected */
			if (a == '\n' || a == '\r')
				MiEventWrite(EV_PROCESS_SCPI);	

			if (U1RxIntPointer > U1RX_BUFFER_SIZE-1)
				U1RxIntPointer = 0;
		}
	}
	_U1RXIF = 0;					// Clear UART RX Interrupt Flag
}
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void)
{
	_U1TXIF = 0;					// Clear UART TX Interrupt Flag
	while (U1STAbits.UTXBF == 0 && U1TxIntPointer != U1TxCurrentPointer) {
		U1TXREG = U1TxBuffer[U1TxIntPointer++];
		if (U1TxIntPointer > U1TX_BUFFER_SIZE -1)
			U1TxIntPointer = 0;
	}
}

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{
unsigned char a;
int status1;
	status1 = U2STA;
/*
	if (status1 & 0x06) {
		a = U2RXREG;
		_U2RXIF = 0;					// Clear UART RX Interrupt Flag
		return;
	}
*/
	if (status1 &1) {
//	if ((status1 & 4) == 0 && (status1 &1)) {
		a = U2RXREG;
		nanoDataTemp |= a;
		if (nanoIndex++ < 3)
			nanoDataTemp = nanoDataTemp<<8;
		else {
			nanoData = nanoDataTemp;
			nanoArray[nanoIndex2] = nanoData;
			if (unsignedCharArray[measureStateIndex])
				MiEventWrite(EV_PROCESS_NANO);
			else
				nanoIndex1 = nanoIndex2;
			nanoIndex = 0;
			if (++nanoIndex2 >= NANO_MAX) {
				nanoIndex2 = 0;
			}
			nanoDataTemp = 0;
		}
	} 	
	_U2RXIF = 0;					// Clear UART RX Interrupt Flag
}
void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void)
{
	_U2TXIF = 0;					// Clear UART TX Interrupt Flag
	while (U2STAbits.UTXBF == 0 && U2TxIntPointer != U2TxCurrentPointer) {
		U2TXREG = U2TxBuffer[U2TxIntPointer++];
		if (U2TxIntPointer > U2TX_BUFFER_SIZE -1)
			U2TxIntPointer = 0;
	}
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
	IFS0bits.T1IF = 0;		// clear interrupt flag

	tickCounter++;
	if (++timerCounter > 0) {
		timerCounter = 0;
		MiEventWrite(EV_TICK_500_MSEC);
		if (++timerSecondCounter > 1) {
			MiEventWrite(EV_TICK_1_SECOND);
			timerSecondCounter = 0;
		}
	}
}
