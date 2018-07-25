#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Pic24_Diagnostics.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Pic24_Diagnostics.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED="../DEE Emulation 16-bit.c" "../Flash Operations.s" ../Hardware.c ../Main.c ../MI_COS.c ../MI_QUEUE.c "../Pic24 Diagnostics.c" ../Scpi.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED="${OBJECTDIR}/_ext/1472/DEE Emulation 16-bit.o" "${OBJECTDIR}/_ext/1472/Flash Operations.o" ${OBJECTDIR}/_ext/1472/Hardware.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/MI_COS.o ${OBJECTDIR}/_ext/1472/MI_QUEUE.o "${OBJECTDIR}/_ext/1472/Pic24 Diagnostics.o" ${OBJECTDIR}/_ext/1472/Scpi.o
POSSIBLE_DEPFILES="${OBJECTDIR}/_ext/1472/DEE Emulation 16-bit.o.d" "${OBJECTDIR}/_ext/1472/Flash Operations.o.d" ${OBJECTDIR}/_ext/1472/Hardware.o.d ${OBJECTDIR}/_ext/1472/Main.o.d ${OBJECTDIR}/_ext/1472/MI_COS.o.d ${OBJECTDIR}/_ext/1472/MI_QUEUE.o.d "${OBJECTDIR}/_ext/1472/Pic24 Diagnostics.o.d" ${OBJECTDIR}/_ext/1472/Scpi.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/DEE\ Emulation\ 16-bit.o ${OBJECTDIR}/_ext/1472/Flash\ Operations.o ${OBJECTDIR}/_ext/1472/Hardware.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/MI_COS.o ${OBJECTDIR}/_ext/1472/MI_QUEUE.o ${OBJECTDIR}/_ext/1472/Pic24\ Diagnostics.o ${OBJECTDIR}/_ext/1472/Scpi.o

# Source Files
SOURCEFILES=../DEE Emulation 16-bit.c ../Flash Operations.s ../Hardware.c ../Main.c ../MI_COS.c ../MI_QUEUE.c ../Pic24 Diagnostics.c ../Scpi.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Pic24_Diagnostics.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GA002
MP_LINKER_FILE_OPTION=,--script=p24FJ64GA002.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/DEE\ Emulation\ 16-bit.o: ../DEE\ Emulation\ 16-bit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} "${OBJECTDIR}/_ext/1472/DEE Emulation 16-bit.o".d 
	@${RM} "${OBJECTDIR}/_ext/1472/DEE Emulation 16-bit.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../DEE Emulation 16-bit.c"  -o "${OBJECTDIR}/_ext/1472/DEE Emulation 16-bit.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/DEE Emulation 16-bit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -I"../../../Program Files (x86)/Microchip/MPLAB C30/support/PIC24F/h" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/DEE Emulation 16-bit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Hardware.o: ../Hardware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Hardware.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Hardware.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Hardware.c  -o ${OBJECTDIR}/_ext/1472/Hardware.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Hardware.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -I"../../../Program Files (x86)/Microchip/MPLAB C30/support/PIC24F/h" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Hardware.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Main.o: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Main.c  -o ${OBJECTDIR}/_ext/1472/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -I"../../../Program Files (x86)/Microchip/MPLAB C30/support/PIC24F/h" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/MI_COS.o: ../MI_COS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MI_COS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MI_COS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../MI_COS.c  -o ${OBJECTDIR}/_ext/1472/MI_COS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/MI_COS.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -I"../../../Program Files (x86)/Microchip/MPLAB C30/support/PIC24F/h" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MI_COS.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/MI_QUEUE.o: ../MI_QUEUE.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MI_QUEUE.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MI_QUEUE.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../MI_QUEUE.c  -o ${OBJECTDIR}/_ext/1472/MI_QUEUE.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/MI_QUEUE.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -I"../../../Program Files (x86)/Microchip/MPLAB C30/support/PIC24F/h" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MI_QUEUE.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Pic24\ Diagnostics.o: ../Pic24\ Diagnostics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} "${OBJECTDIR}/_ext/1472/Pic24 Diagnostics.o".d 
	@${RM} "${OBJECTDIR}/_ext/1472/Pic24 Diagnostics.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../Pic24 Diagnostics.c"  -o "${OBJECTDIR}/_ext/1472/Pic24 Diagnostics.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Pic24 Diagnostics.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -I"../../../Program Files (x86)/Microchip/MPLAB C30/support/PIC24F/h" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Pic24 Diagnostics.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Scpi.o: ../Scpi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Scpi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Scpi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Scpi.c  -o ${OBJECTDIR}/_ext/1472/Scpi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Scpi.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -I"../../../Program Files (x86)/Microchip/MPLAB C30/support/PIC24F/h" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Scpi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1472/DEE\ Emulation\ 16-bit.o: ../DEE\ Emulation\ 16-bit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} "${OBJECTDIR}/_ext/1472/DEE Emulation 16-bit.o".d 
	@${RM} "${OBJECTDIR}/_ext/1472/DEE Emulation 16-bit.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../DEE Emulation 16-bit.c"  -o "${OBJECTDIR}/_ext/1472/DEE Emulation 16-bit.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/DEE Emulation 16-bit.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -I"../../../Program Files (x86)/Microchip/MPLAB C30/support/PIC24F/h" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/DEE Emulation 16-bit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Hardware.o: ../Hardware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Hardware.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Hardware.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Hardware.c  -o ${OBJECTDIR}/_ext/1472/Hardware.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Hardware.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -I"../../../Program Files (x86)/Microchip/MPLAB C30/support/PIC24F/h" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Hardware.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Main.o: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Main.c  -o ${OBJECTDIR}/_ext/1472/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -I"../../../Program Files (x86)/Microchip/MPLAB C30/support/PIC24F/h" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/MI_COS.o: ../MI_COS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MI_COS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MI_COS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../MI_COS.c  -o ${OBJECTDIR}/_ext/1472/MI_COS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/MI_COS.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -I"../../../Program Files (x86)/Microchip/MPLAB C30/support/PIC24F/h" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MI_COS.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/MI_QUEUE.o: ../MI_QUEUE.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MI_QUEUE.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MI_QUEUE.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../MI_QUEUE.c  -o ${OBJECTDIR}/_ext/1472/MI_QUEUE.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/MI_QUEUE.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -I"../../../Program Files (x86)/Microchip/MPLAB C30/support/PIC24F/h" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MI_QUEUE.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Pic24\ Diagnostics.o: ../Pic24\ Diagnostics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} "${OBJECTDIR}/_ext/1472/Pic24 Diagnostics.o".d 
	@${RM} "${OBJECTDIR}/_ext/1472/Pic24 Diagnostics.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../Pic24 Diagnostics.c"  -o "${OBJECTDIR}/_ext/1472/Pic24 Diagnostics.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Pic24 Diagnostics.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -I"../../../Program Files (x86)/Microchip/MPLAB C30/support/PIC24F/h" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Pic24 Diagnostics.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Scpi.o: ../Scpi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Scpi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Scpi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Scpi.c  -o ${OBJECTDIR}/_ext/1472/Scpi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Scpi.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -I"../../../Program Files (x86)/Microchip/MPLAB C30/support/PIC24F/h" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Scpi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/Flash\ Operations.o: ../Flash\ Operations.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} "${OBJECTDIR}/_ext/1472/Flash Operations.o".d 
	@${RM} "${OBJECTDIR}/_ext/1472/Flash Operations.o" 
	${MP_CC} $(MP_EXTRA_AS_PRE)  "../Flash Operations.s"  -o "${OBJECTDIR}/_ext/1472/Flash Operations.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -I"." -Wa,-MD,"${OBJECTDIR}/_ext/1472/Flash Operations.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Flash Operations.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1472/Flash\ Operations.o: ../Flash\ Operations.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} "${OBJECTDIR}/_ext/1472/Flash Operations.o".d 
	@${RM} "${OBJECTDIR}/_ext/1472/Flash Operations.o" 
	${MP_CC} $(MP_EXTRA_AS_PRE)  "../Flash Operations.s"  -o "${OBJECTDIR}/_ext/1472/Flash Operations.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -I"." -Wa,-MD,"${OBJECTDIR}/_ext/1472/Flash Operations.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Flash Operations.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Pic24_Diagnostics.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Pic24_Diagnostics.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="..",--library-path=".",--no-force-link,--smart-io,-Map="${DISTDIR}/Pic24_Diagnostics.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Pic24_Diagnostics.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Pic24_Diagnostics.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="..",--library-path=".",--no-force-link,--smart-io,-Map="${DISTDIR}/Pic24_Diagnostics.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Pic24_Diagnostics.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
