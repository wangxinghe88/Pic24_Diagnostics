#ifndef __MI_APP_H
#define __MI_APP_H

/*************************************************************************
*   $MODULE
*   mi_app.h
*
*************************************************************************/

/*************************************************************************
*   $INCLUDES
*************************************************************************/
#include "mi_cos.h"


/*************************************************************************
*   $DEFINES
*************************************************************************/

/*
 * Uncomment this line if you want dynamic tasks.  (It compiles in
 * the code for MiTaskCreate and MiTaskDestroy.)
 *
 * #define DYNAMIC_TASKS
 */
//#define DYNAMIC_TASKS 1


/* Uncomment this line if you want to use GetCurrentState.
 *
 * #define GET_CURRENT_STATE
 */
#define GET_CURRENT_STATE 1

/* If you want dynamic task creation and destruction, set MI_MAX_TASKS to
 * the maximum number of tasks you will have running at any time. */
#ifdef DYNAMIC_TASKS
#define MI_MAX_TASKS 10
#endif

/*
 * This is /not/ the number of states. It is the number of entries
 * in the state transition table.
 */
#define MI_MAX_STATE_TRANS_ENTRIES 10

/*
 * This is the number of entries in the Event Queue.
 */
#define MI_EVENT_QUEUE_LENGTH 20

/*************************************************************************
*   $GLOBAL PROTOTYPES
*************************************************************************/
TMiResult state_one(void);
TMiResult state_two(void);

void task_one(void);
void task_two(void);

/*
 * These are application defined results.  As with the events above,
 * they must not overlap MiCOS defined results.
 */
enum {
    RES_TIMER = MI_STATE_OFFSET,
    RES_NANO = RES_TIMER+2,
    RES_SCPI = RES_NANO+1
};  /* TMiResult */

/*
 * These are application defined events.  The only restriction is that
 * they do not overlap with MiCOS-defined events.
 */
typedef enum TIMER_EVENT {
    EV_TICK_500_MSEC = MI_EVENT_OFFSET,
	EV_TICK_1_SECOND
} TIMER_EVENT;

typedef enum NANO_EVENT {
 	EV_PROCESS_NANO = RES_NANO
} NANO_EVENT;

typedef enum SCPI_EVENT {
 	EV_PROCESS_SCPI = RES_SCPI
} SCPI_EVENT;


/*************************************************************************
*   $GLOBAL VARIABLES
*************************************************************************/
extern void _enable(void);
extern void _disable(void);

/*
 * The system task list
 */
extern TMiTask *MiTaskList[];
extern TMiWord MI_MAX_TASKS;

/*
 * The system state transition table
 */
extern TMiStateTransEntry MiStateTable[];

/************************************************************************/

#endif

