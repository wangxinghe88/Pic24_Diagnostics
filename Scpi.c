#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include <ctype.h>
#include <math.h>
#include "mi_app.h"
#include "Hardware.h"
#include "Scpi.h"
char CommandLine[COMMAND_MAX];
unsigned char defIndex, setIndex;
int enumValueIndex;
unsigned char enumIndex, enumLoop,enumLimit;
int valuesIndex;
unsigned char argumentCount, argumentActive, argumentCurrent;
unsigned char type;
unsigned char ProcessState;
char ReadResults[READ_MAX];
//char codes[100][2];
int CommandIndex;
int arrayMax;
int SetMode;
char* cmdptr;
char* typeptr;
char const* setPtr;
char* charValuesPtr;
char* charPtr;
/* public variables */
char const* scpiPtr;
char const* fromPtr;


/* Global Variables */

void setESR(unsigned char esr) {
	unsignedCharArray[variable[esrIndex].valueIndex] |= esr;
}
int arrayIndex;
unsigned char conditionalMode;
unsigned char conditionalIndex, conditionalMax;
void calcGetArrayIndex(unsigned char type) {
	if (type == VALUE) {
		if (argumentCurrent > 0 && ((variable[setIndex].modes & INDEX_ENUMERATED_DEFINED) ||
				scpi[ScpiIndex].enumeratedCount != 0))
			arrayIndex = variable[setIndex].valueIndex+enumLimit;
		else
			arrayIndex = variable[setIndex].valueIndex+valuesIndex;
	}
	else if (type == DEFAULT) {
			arrayIndex = variable[setIndex].valueIndex + variable[setIndex].arrayMax;
	}
	else if (type == MIN) {
		if (variable[setIndex].modes & DEFAULT_DEFINED)
			arrayIndex = variable[setIndex].valueIndex +
				variable[setIndex].arrayMax + 1;
		else
			arrayIndex = variable[setIndex].valueIndex +
				variable[setIndex].arrayMax;
	}
	else if (type == MAX) {
		if ((variable[setIndex].modes & DEFAULT_DEFINED) &&
			(variable[setIndex].modes & MIN_DEFINED))
			arrayIndex =  variable[setIndex].valueIndex +
				variable[setIndex].arrayMax + 2;
		else if ((variable[setIndex].modes & DEFAULT_DEFINED) ||
			(variable[setIndex].modes & MIN_DEFINED))
			arrayIndex = variable[setIndex].valueIndex +
				variable[setIndex].arrayMax + 1;
		else
			arrayIndex = variable[setIndex].valueIndex +
				variable[setIndex].arrayMax;
	}
}
void calcPutArrayIndex(void) {
	if (argumentCurrent > 0 && ((variable[setIndex].modes & INDEX_ENUMERATED_DEFINED) ||
			scpi[ScpiIndex].enumeratedCount != 0))
		arrayIndex = variable[setIndex].valueIndex+enumLimit;
	else
		arrayIndex = variable[setIndex].valueIndex+valuesIndex;
}
void putDouble(double val) {
	calcPutArrayIndex();
	doubleArray[arrayIndex] = val;
}
double getDouble(unsigned char type) {
	calcGetArrayIndex(type);
	return doubleArray[arrayIndex];
}

void putInt(int val) {
	calcPutArrayIndex();
	intArray[arrayIndex] = val;
}
int getInt(unsigned char type) {
	calcGetArrayIndex(type);
	return intArray[arrayIndex];
}
void putLongInt(long int val) {
	calcPutArrayIndex();
	longIntArray[arrayIndex] = val;
}
long int getLongInt(unsigned char type) {
	calcGetArrayIndex(type);
	return longIntArray[arrayIndex];
}
void putUnsignedChar(unsigned char val) {
	calcPutArrayIndex();
	unsignedCharArray[arrayIndex] = val;
}
unsigned char getUnsignedChar(unsigned char type) {
	calcGetArrayIndex(type);
	return unsignedCharArray[arrayIndex];
}

int findScpi (char* charPtr,unsigned char type) {
char* fromPtr1;
char* decodePtr;
int index1;
int count1;
	index1 = 0;
	if (type == SCPI)
		count1 = ScpiCount;
	else
		count1 = DefCount;
	decodePtr = charPtr;
	while (index1 < count1) {
		if (type == SCPI)
			scpiPtr = &scpiCommands[scpi[index1].commandIndex];
		else
			scpiPtr = &defCommands[def[index1].commandIndex];
		fromPtr1 = decodePtr;
		while (*fromPtr1 != '\0' && *fromPtr1 != ' ') {
			if ( *fromPtr1 != '?' && (toupper(*fromPtr1) == *scpiPtr)) {
				fromPtr1++;
				scpiPtr++;
			}
			else if (*fromPtr1 == '?') {
				if (islower(*scpiPtr)) 
					while (*scpiPtr != ':' && *scpiPtr != '?' && *scpiPtr != ' ')
						scpiPtr++;
				if (*scpiPtr == '?') {
					scpiPtr++;
					fromPtr1++;
					if (type == SCPI)
						argumentCount = scpi[index1].argumentCount;
					else
						argumentCount = def[index1].argumentCount;
					while (*scpiPtr == ' ')
						scpiPtr++;
					if (type == SCPI)
						ScpiIndex = index1;
					else
						DefIndex = index1;
					if (*fromPtr1 == ' ' && (*scpiPtr == '<' || *scpiPtr == '{'))
						return 3;
					else
						return 2;
				}
				else
					break;
			}
			else if (tolower(*fromPtr1) == *scpiPtr) {
				fromPtr1++;
				scpiPtr++;
			}
			else if (*fromPtr1 == ':') {
				fromPtr1++;
				while (*scpiPtr != ':' && *scpiPtr != ' ')
					scpiPtr++;
				if (*scpiPtr == ':')
					scpiPtr++;
				else
					break;
			}
			else if (islower(*scpiPtr)) {
				while (islower(*scpiPtr))
					scpiPtr++;
			}
			else
				break;
		}
		if (*fromPtr1 == '\0') {
			while (islower(*scpiPtr))
				scpiPtr++;
			while (*scpiPtr == ' ')
				scpiPtr++;
		}
		if (*fromPtr1 == '\0' && *scpiPtr == '\0') {
			if (type == SCPI)
				argumentCount = scpi[index1].argumentCount;
			else
				argumentCount = def[index1].argumentCount;
			if (type == SCPI)
				ScpiIndex = index1;
			else
				DefIndex = index1;
			return 1;
		}
		if (*fromPtr1 == ' ') {
			while (islower(*scpiPtr))
				scpiPtr++;
			while (*scpiPtr == ' ')
				scpiPtr++;
		}
		if (*fromPtr1 == ' ' && (*scpiPtr == '<' || *scpiPtr == '{')) {
			if (type == SCPI)
				argumentCount = scpi[index1].argumentCount;
			else
				argumentCount = def[index1].argumentCount;
			if (type == SCPI)
				ScpiIndex = index1;
			else
				DefIndex = index1;
				return 0;
		}
		index1++;
	}
	return -1;
}
unsigned char getScpiVariable(char *varPtr) {
	scpiPtr = varPtr;
	if (findVariable()) {
		return getUnsignedChar(VALUE);
	}
	else
		return 0;
}
void putScpiVariable(char *varPtr, unsigned char val) {
	scpiPtr = varPtr;
	if (findVariable()) {
		putUnsignedChar(val);
	}
}

unsigned char findVariable(void) {
	if (*scpiPtr == '<')
		scpiPtr++;
	setIndex = 0;
	while (setIndex < SetCount) {
		setPtr = &variableName[variable[setIndex].variableIndex];
		fromPtr = scpiPtr;
		while (*setPtr != '\0' && *fromPtr != '>' && *fromPtr != '\0' &&
			*fromPtr == *setPtr) {
			*fromPtr++;
			*setPtr++;
		}
		if (*fromPtr == '>' || *fromPtr == '\0') 
			return 1;
		setIndex++;
	}
	return 0;
}

void removeComments(char* charPtr) {
char* p1;
char* p2;
char* p3;
/* remove comments spaces */
	p1 = charPtr;
	while (*p1 != '\0') {
		while (*p1 != '/' && *p1 != '\0')
		p1++;
		if (*p1 == '/') {
			p2 = p1+1;
			if (*p2 == '/' || *p2 == '*') {
				if (*p2 == '/')
					while (*p2 != '\0')
						p2++;
				else
					while (*p2 != '/' && *p2 != '\0')
						p2++;
				if (*p2 == '/')
					p2++;
				p3 = p1;
				while (*p2 != '\0')
					*p3++ = *p2++;
				*p3 = '\0';
			}
			else
				p1++;
		}
	}
/* remove leading spaces */
	while (*charPtr == ' ')
		charPtr++;
/* remove trailing carriage returns, line feeds and spaces */
	p1 = charPtr+strlen(charPtr)-1;
	while (*p1 == ' ' || *p1 == '\n' || *p1 == '\r')
		*p1-- = '\0';
}

int readScpi(char* charPtr,unsigned char type) {
char* decodePtr;
char* readResultsPtr;
double tempData;
short unsigned int tempIsData;
int tempIdata;
long int tempIlData;
int findScpiReturn;
int findScpiQueryReturn;
int saveScpiQueryIndex;
int saveScpiWriteIndex;
char tempCommandLine[COMMAND_MAX];
char string1[200];

	saveScpiWriteIndex = 0;
	findScpiQueryReturn = 0;

	if (type == SCPI) {
/* Try to find the write(Set) Value(s) version of the SCPI Command 
	replace the ? with a space to locate the set value command */
		argumentCurrent = 0;
		readResultsPtr = ReadResults;
		strcpy(tempCommandLine,charPtr);
		decodePtr = tempCommandLine;
	/* Check to see if the query has any arguments */
		findScpiQueryReturn = findScpi(decodePtr,SCPI);
		saveScpiQueryIndex = ScpiIndex;

		while(*decodePtr != '?')
			decodePtr++;

		*decodePtr = ' ';
		decodePtr = tempCommandLine;
		findScpiReturn = findScpi(decodePtr,SCPI);
		if (findScpiReturn > 0)
			return 0;

		if (findScpiReturn < 0) {
			setESR(ESR_CME);
			return 0;
		}

		scpiPtr = &scpiCommands[scpi[ScpiIndex].commandIndex];

		if (findScpiQueryReturn == 3) {
			saveScpiWriteIndex = ScpiIndex;
			ScpiIndex = saveScpiQueryIndex;
		}
		enumIndex = 0;
		if (scpi[ScpiIndex].enumeratedCount > 0) {
			enumIndex = scpi[ScpiIndex].enumeratedIndex - 1;
		}
	}
	else {
/* Try to find the Def version of the SCPI Command */
		decodePtr = charPtr;
		findScpiReturn = findScpi(decodePtr,DEF);

		if (findScpiReturn < 0) {
			return 0;
		}

		enumIndex = 0;
		if (def[DefIndex].enumeratedCount > 0) {
			enumIndex = def[DefIndex].enumeratedIndex - 1;
		}
		argumentCurrent = 0;
		readResultsPtr = ReadResults;
		scpiPtr = &defCommands[def[DefIndex].commandIndex];
	}
	conditionalMode = 0;
	while (*scpiPtr++ != ' ');
	while (*scpiPtr == ' ')
		scpiPtr++;
	while (*scpiPtr == '{' || *scpiPtr == '<') {
		if (*scpiPtr == '^') {
			scpiPtr++;
			if (findVariable()) {
				arrayIndex = variable[setIndex].valueIndex;
				conditionalMax = unsignedCharArray[arrayIndex];
				conditionalMode = 1;
				for (conditionalIndex = 0; conditionalIndex < conditionalMax; conditionalIndex++) {
					while (*scpiPtr != '|' && *scpiPtr != '^')
						scpiPtr++;
					if (*scpiPtr == '|') {
						scpiPtr++;
					}
					else
						conditionalMode = 0;
				}
			}
			if (conditionalMode == 0) {
				setESR(ESR_EXE);
				return 0;
			}
		}
		if (*scpiPtr == '{') {
			enumIndex++;
			scpiPtr++;
			if (strlen(ReadResults))
				strcat(ReadResults,",");
			readResultsPtr = ReadResults + strlen(ReadResults);
			enumLimit = enumeratedArray[enumIndex];
			argumentCurrent++;
			for (enumLoop = 0;
				enumLoop < enumLimit;
				enumLoop++) {
					while (*scpiPtr++ != '|');					
			}
			while (*scpiPtr != '|' && *scpiPtr != '}')
				*readResultsPtr++ = *scpiPtr++;
			*readResultsPtr = '\0';
			while (*scpiPtr++ != '}');
			if (*scpiPtr == ',')
				scpiPtr++;
			if (findScpiQueryReturn == 3 && scpi[ScpiIndex].enumeratedCount == argumentCurrent)
				ScpiIndex = saveScpiWriteIndex;
		}
		while (*scpiPtr == '<') {
			if (findVariable()) {
				scpiPtr = fromPtr + 1;
				if (*scpiPtr == ',')
					scpiPtr++;
				argumentCurrent++;
				type = variable[setIndex].type;
				for (valuesIndex = 0; valuesIndex < 
						variable[setIndex].arrayMax;valuesIndex++) {
					if (strlen(ReadResults))
							strcat(ReadResults,",");
					switch (type) {
						case unsignedCharDef:
							tempIsData = getUnsignedChar(VALUE);
							sprintf(string1,&format[variable[setIndex].formatIndex],
								tempIsData);
					/* reading of esr clears the register */
							if (type == DEF && setIndex == esrIndex)
								unsignedCharArray[variable[setIndex].valueIndex] = 0;
							break;
						case intDef:
							tempIdata = getInt(VALUE);
							sprintf(string1,&format[variable[setIndex].formatIndex],
								tempIdata);
							break;
						case longIntDef:
							tempIlData = getLongInt(VALUE);
							sprintf(string1,&format[variable[setIndex].formatIndex],
								tempIlData);
							break;
						case doubleDef:
							tempData = getDouble(VALUE);
							sprintf(string1,&format[variable[setIndex].formatIndex],
							tempData);
							break;
						case charDef:
							strcpy(string1,&charArray[variable[setIndex].valueIndex]);
							valuesIndex = variable[setIndex].arrayMax;
							break;
					}
					strcat(ReadResults,string1);
/*		
			if (argumentCurrent > 1 && 
							(variable[setIndex].modes & INDEX_ENUMERATED_DEFINED))
						break;
*/
				}
			}
			else {
				setESR(ESR_CME);
				return 0;
			}
		if (conditionalMode == 1) {
			while (*scpiPtr != '\0' && *scpiPtr != '^')
				scpiPtr++;
			if (*scpiPtr == '^')
				scpiPtr++;
			if (*scpiPtr == ',')
				scpiPtr++;
			conditionalMode = 0;
		}
		}
	}
	return 1;
}

int decodeCommand(char* charPtr) {
char* decodePtr;
double tempData;
int findScpiReturn;
unsigned char tempIsData;
int tempIdata;
long int tempIlData;
char tempChar[500];
	removeComments(charPtr);
	decodePtr = charPtr;
	findScpiReturn = findScpi(charPtr,SCPI);
	if (findScpiReturn == 2)
		return findScpiReturn;
	if (findScpiReturn == 1)
		return findScpiReturn;

	if (findScpiReturn < 0) {
		setESR(ESR_CME);
		return 0;
	}
	
	while (*decodePtr++ != ' ');
	while (*decodePtr == ' ')
		decodePtr++;
	scpiPtr = &scpiCommands[scpi[ScpiIndex].commandIndex];
	while (*scpiPtr++ != ' ');
	while (*scpiPtr == ' ')
		scpiPtr++;
	argumentCurrent = 0;
	enumIndex = 0;
	enumValueIndex = 0;
	enumLimit = 0;
	valuesIndex = 0;
	conditionalMode = 0;
	if (scpi[ScpiIndex].enumeratedCount > 0) {
		enumIndex = scpi[ScpiIndex].enumeratedIndex - 1;
		enumValueIndex = scpi[ScpiIndex].enumeratedIndex;
	}
	if (scpi[ScpiIndex].enumeratedCount > 0) {
		enumIndex = scpi[ScpiIndex].enumeratedIndex - 1;
	}
	while (*scpiPtr == '<' || *scpiPtr == '{' ||*scpiPtr == '^') {
		if (*scpiPtr == '^') {
			scpiPtr++;
			if (findVariable()) {
				arrayIndex = variable[setIndex].valueIndex;
				conditionalMax = unsignedCharArray[arrayIndex];
				conditionalMode = 1;
				for (conditionalIndex = 0; conditionalIndex < conditionalMax; conditionalIndex++) {
					while (*scpiPtr != '|' && *scpiPtr != '^')
						scpiPtr++;
					if (*scpiPtr == '|') {
						scpiPtr++;
					}
					else
						conditionalMode = 0;
				}
			}
			if (conditionalMode == 0) {
				setESR(ESR_EXE);
				return 0;
			}
		}
		if (*scpiPtr == '{') {
			scpiPtr++;
			enumIndex++;
			argumentCurrent++;
			enumeratedArray[enumIndex] = 0;
			enumLimit = 0;
			while (*scpiPtr != '}' && *scpiPtr != ',' && scpiPtr != '\0') {
				fromPtr = decodePtr;
				while (*scpiPtr == *fromPtr || *scpiPtr == toupper(*fromPtr)) {
					scpiPtr++;
					fromPtr++;
					if (*fromPtr == ',' || *fromPtr == '\0')
						while (islower(*scpiPtr))
							scpiPtr++;
				}
				if (*scpiPtr == '|' || *scpiPtr == '}')
					break;
				while (*scpiPtr != '|' && *scpiPtr!= '}' && *scpiPtr!= '\0')
					scpiPtr++;
				if (*scpiPtr != '|')
					break;
				enumLimit++;
				enumeratedArray[enumIndex]++;
				scpiPtr++;
			}
			while (*scpiPtr != ',' && *scpiPtr != '\0' && *scpiPtr++ != '}');
			if (*fromPtr != ',' && *fromPtr != '\0') {
				setESR(ESR_EXE);
			return 0;
			}
			while (*decodePtr != '\0' && *decodePtr++ != ',');
			if (*scpiPtr != '\0')
				scpiPtr++;
		}
		while (*scpiPtr == '<') {
			if (findVariable()) {
				scpiPtr = fromPtr + 1;
				if (*scpiPtr == ',')
					scpiPtr++;
				argumentCurrent++;
				type = variable[setIndex].type;
				if (scpi[ScpiIndex].enumeratedCount > 0) {
					enumLimit = enumeratedArray[enumValueIndex];
					if (enumValueIndex < (scpi[ScpiIndex].enumeratedCount + scpi[ScpiIndex].enumeratedIndex))
						enumValueIndex++;
				}
				arrayMax = variable[setIndex].arrayMax;
				if (type == charDef || (variable[setIndex].modes & INDEX_ENUMERATED_DEFINED))
					arrayMax = 1;
				for (valuesIndex = 0; valuesIndex < 
				arrayMax;valuesIndex++) {
				switch (type) {
					case unsignedCharDef:
						tempIsData = (unsigned char)atoi(decodePtr);
						if ((variable[setIndex].modes & MIN_DEFINED) &&
							tempIsData < getUnsignedChar(MIN)) {
							tempIsData =	getUnsignedChar(VALUE);
							setESR(ESR_EXE);
						}
						if ((variable[setIndex].modes & MAX_DEFINED) &&
							tempIsData > getUnsignedChar(MAX)) {
							setESR(ESR_EXE);
							tempIsData =	getUnsignedChar(VALUE);
						}
						putUnsignedChar(tempIsData);
						break;
					case intDef:
						tempIdata = atoi(decodePtr);
						if ((variable[setIndex].modes & MIN_DEFINED) &&
							tempIdata < getInt(MIN)) {
							tempIdata =	getInt(VALUE);
							setESR(ESR_EXE);
						}
						if ((variable[setIndex].modes & MAX_DEFINED) &&
							tempIdata > getInt(MAX)) {
							setESR(ESR_EXE);
							tempIdata =	getInt(VALUE);
						}
						putInt(tempIdata);
						break;
					case longIntDef:
						tempIlData = atol(decodePtr);
						if ((variable[setIndex].modes & MIN_DEFINED) &&
							tempIlData < getLongInt(MIN)) {
							tempIlData =	getLongInt(VALUE);
							setESR(ESR_EXE);
						}
						if ((variable[setIndex].modes & MAX_DEFINED) &&
							tempIlData > getLongInt(MAX)) {
							setESR(ESR_EXE);
							tempIlData =	getLongInt(VALUE);
						}
						putLongInt(tempIlData);
						break;
					case doubleDef:
						tempData = atof(decodePtr);
						if ((variable[setIndex].modes & MIN_DEFINED) &&
							tempData < getDouble(MIN)) {
							tempData =	getDouble(VALUE);
							setESR(ESR_EXE);
						}
						if ((variable[setIndex].modes & MAX_DEFINED) &&
							tempData > getDouble(MAX)) {
							tempData =	getDouble(VALUE);
							setESR(ESR_EXE);
						}
						putDouble(tempData);
						break;
					case charDef:
						charPtr = tempChar;
						while (*decodePtr != ',' && *decodePtr != '\0')
							*charPtr++ = *decodePtr++;
						*charPtr = '\0';
						strcpy(&charArray[variable[setIndex].valueIndex],tempChar);
						break;
				}
				while (*decodePtr != ',' && *decodePtr != '\0')
					decodePtr++;
				if (*decodePtr == ',')
					decodePtr++;
				else {
					break;
				}
			  }			      
			  break;
			}
			else {
			setESR(ESR_CME);
			return 0;
			}
		}
		if (conditionalMode == 1) {
			while (*scpiPtr != '\0' && *scpiPtr != '^')
				scpiPtr++;
			if (*scpiPtr == '^')
				scpiPtr++;
			if (*scpiPtr == ',')
				scpiPtr++;
			conditionalMode = 0;
		}
	}
	if (findScpiReturn == 3)
		return 2;
	else
		return 1;
}

unsigned char ProcessScpi(char* ScpiCommandLine) {
	cmdptr = ScpiCommandLine;
	ReadResults[0] = '\0';
	ProcessState = decodeCommand(cmdptr);
	ScpiExit = ScpiIndex;
	if (ProcessState == 2) {
		if ((ProcessState = readScpi(cmdptr,DEF)));
		else if ((ProcessState = readScpi(cmdptr,SCPI)));
		else
			return 0;
		if (ReadResults[0] == '\0' ||
			(ReadResults[strlen(ReadResults)-1] != '\n' &&
				ReadResults[strlen(ReadResults)-2] != '\n'))
			strcat(ReadResults,"\n");
#ifdef DEBUG_UTILS
    	DBPUTS(ReadResults);
#else
		PCputs(ReadResults);
#endif
	}
	if (ProcessState > 0)
		UserExits();
	return 1;
}

