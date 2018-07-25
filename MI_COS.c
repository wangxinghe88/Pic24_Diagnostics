/************************************************************************/
/*                                                                      */
/*              DEVELOPED BY:   SLTF CONSULTING                         */
/*                              6316 DISTANT ROCK PATH                  */
/*                              COLUMBIA, MARYLAND USA  21045           */
/*                              410.799.3915                            */
/*                                                                      */
/************************************************************************/

/*************************************************************************
*   $MODULE
*   micos.c
*
*   This is the code for MicOS, SimpleSofts's Cooperative Operating System.
*   Check micos.doc for an explanation of the architecture.
*
*************************************************************************/

/*************************************************************************
*   $INCLUDES
*************************************************************************/
#include <stdio.h>
#include "mi_cos.h"
#include "mi_app.h"
#include "mi_queue.h"

/*************************************************************************
*   $DEFINES
*************************************************************************/

/*************************************************************************
*   $LOCAL PROTOTYPES
*************************************************************************/
static void initialize_micos(void);
static void task_manager(void);
static void state_manager(void);
static void ChangeCurrentState( TMiResult );
static void event_manager(void);

void _enable(void);
void _disable(void);

/*************************************************************************
*   $GLOBAL VARIABLES
*************************************************************************/
MICOS_EVENT MiCurrentEvent = EV_IDLE;
TMiFatalErrorFlag MiFatalError; /* MiCOS fatal error flags */

/*************************************************************************
*   $LOCAL VARIABLES
*************************************************************************/
static TMiStatePtr CurrentState = NULL;


/************************************************************************/


/***************************************************************************

  Routine Name: MiCos

  Date Created: May 6, 1996

        Author: SBR

   Description: This is the call an application makes to start the MiCOS
                operating system.  The call to MiCOS never returns.

         Input: None

        Output: None

                    Changes
   Number       Date        Initials    Description

**************************************************************************/
void MiCos(void) {

    initialize_micos();

    for (;;) {
        task_manager();
        state_manager();
        event_manager();
    }

}

/***************************************************************************

  Routine Name: initialize_micos

  Date Created: May 6, 1996

        Author: SBR

   Description: Initializes the EventQueue.
                Sets the CurrentState to the first entry in the MiStateTable.
                Sets the MiCurrentEvent to EV_INIT.

         Input: None

        Output: None

                    Changes
   Number       Date        Initials    Description

**************************************************************************/
static void initialize_micos(void) {

    /*
     * Set the CurrentState and MiCurrentEvent
     */

    CurrentState = MiStateTable[0].StatePtr;

    MiCurrentEvent = EV_INIT;
}

/***************************************************************************

  Routine Name: task_manager

  Date Created: May 6, 1996

        Author: SBR

   Description: Runs MiTasksRun().


         Input: None

        Output: None

                    Changes
   Number       Date        Initials    Description

**************************************************************************/
static void task_manager(void)
{
    MiTasksRun();
}

/***************************************************************************

  Routine Name: MiTasksRun

  Date Created: May 7, 1996

        Author: SBR

   Description: MiTasksRun loops through the list of tasks and
                looks for non-null entries.  If it finds any, it calls
                them with the MiCurrentEvent.

                Note, that while it is the intention that a task could
                run MiTasksRun in order to give the other tasks some
                more time to run, if the task is not careful it could
                end up in recursive calls to MiTasksRun.

         Input: None

        Output: None

                    Changes
   Number       Date        Initials    Description

**************************************************************************/
void MiTasksRun( void )
{
    TMiWord index;
    /*
     * Loop through the task list and if you find any valid (non-NULL)
     * entries, run them.
     */
     for (index = 0; index < MI_MAX_TASKS; index++) {
        if (MiTaskList[index] != NULL) {
            (*MiTaskList[index])();
        }
     }
}

#ifdef DYNAMIC_TASKS
/***************************************************************************

  Routine Name: MiTaskCreate

  Date Created: May 7, 1996

        Author: SBR

   Description: Creates a task by placing a pointer to the function
                specified in the task list.

         Input: a task (a pointer to a function) you want to run

        Output: A TMiResult with these possible values:
                RES_OK - the task was created successfully
                RES_TASK_LIST_FULL - task creation failed because
                    the task list was already full

                    Changes
   Number       Date        Initials    Description

**************************************************************************/
TMiResult MiTaskCreate( TMiTask * TaskPtr )
{
    TMiWord index;
    TMiResult ResultCode = RES_TASK_LIST_FULL;

    /*
     * Loop through the task list, looking for a NULL
     * entry.  If we find one, we set that entry to the
     * TaskPtr we were passed, and exit the loop.
     * If we reach the end of the table, we exit the loop.
     */
    for ( index = 0; index < MI_MAX_TASKS; index++) {

        if (MiTaskList[index] == NULL) {
            MiTaskList[index] = TaskPtr;
            ResultCode = RES_OK;
            break;
        }
    }
    return ResultCode;
}

/***************************************************************************

  Routine Name: MiTaskDestroy

  Date Created: May 7, 1996

        Author: SBR

   Description: Destroys the task you specify by removing it from the task
                list.

         Input: a task (a pointer to a function you want to destroy)

        Output: a TMiResult with these possible values
                    RES_OK - if the task was found and destroyed
                    RES_INVALID_TASK - if the task could not be found

                    Changes
   Number       Date        Initials    Description

**************************************************************************/
TMiResult MiTaskDestroy( TMiTask * TaskPtr )
{
    TMiWord index;
    TMiResult ResultCode = RES_INVALID_TASK;

    /*
     * Loop through the task list, looking for the specified
     * entry.  If we find it, we set that entry to
     * NULL and return RES_OK.
     */
    for ( index = 0; index < MI_MAX_TASKS; index++) {

        if (MiTaskList[index] == TaskPtr) {
            MiTaskList[index] = NULL;
            ResultCode = RES_OK;
            break;
        }
    }

    return ResultCode;
}
#endif  /* DYNAMIC_TASKS */

/***************************************************************************

  Routine Name: state_manager

  Date Created: May 6, 1996

        Author: SBR

   Description: The state_manager is responsible for all state processing
                in MiCOS, which makes it the most complex of the MiCOS
                functions.  Here is what the state manager does, step
                by step.

                1.  Calls the CurrentState with MiCurrentEvent.  Checks the
                    Result to see if a transition is necessary.  If it
                    isn't, the state manager exits.

                2.  If a state transition is necessary,

                    a. Calls the current state, passing it EV_EXIT.
                       Ignore any Result returned.

                    b. Change the state.

                    c. Call the current state (i.e. the new state)
                    with EV_INIT.  Check the result, and go back
                    to 2. if necessary.   Otherwise Exit.

         Input: None

        Output: None

                    Changes
   Number       Date        Initials    Description

**************************************************************************/
static void state_manager(void)
{
    TMiResult StateResult;

    /* Run the CurrentState, passing it the MiCurrentEvent */
    StateResult = (*CurrentState)();

    /* State Transistion Loop */
    while (StateResult != RES_SAME_STATE ) {

        /*
         * When called with EV_EXIT, the return value is ignored.
         */
        MiCurrentEvent = EV_EXIT;
        (void) (*CurrentState)();

        ChangeCurrentState(StateResult);

        /*
         * Call the new state with EV_INIT, do we need to transition
         * again?
         */
        MiCurrentEvent = EV_INIT;
        StateResult = (*CurrentState)();
    }

    return;

}

/***************************************************************************

  Routine Name: ChangeCurrentState

  Date Created: May 6, 1996

        Author: SBR

   Description: This function is used exclusively from within the
                state_manager.  Its purpose is to take the
                present state and result, and find the new state.

                This function does that by starting at the top
                of the loop and checking each entry.  If a matching
                isn't found, no error is returned.

         Input: The result when the state was called.

        Output: None

                    Changes
   Number       Date        Initials    Description

**************************************************************************/
static void ChangeCurrentState( TMiResult Result)
{
    TMiWord index;

    /* Loop through the State table... */
    for ( index = 0; index < MI_MAX_STATE_TRANS_ENTRIES; index++) {

        /* ...looking for an entry that matches the CurrentState
         * and what it returned.
         */
        if ( ( MiStateTable[index].StatePtr == CurrentState )&&
             (MiStateTable[index].Result   == Result ) ) {

            CurrentState = MiStateTable[index].NextStatePtr;
            break;
        }
     }

    /* If we finish the loop above without hitting the break then
     * we couldn't find an entry that matched the current situation.
     * That shouldn't happen.
     */

    return;
}
#ifdef MI_GET_CURRENT_STATE
/***************************************************************************

  Routine Name: MiGetCurrentState

  Date Created: May 6, 1996

        Author: SBR

   Description: returns the CurrentState

         Input: None

        Output: the CurrentState

                    Changes
   Number       Date        Initials    Description

**************************************************************************/
TMiStatePtr MiGetCurrentState( void ) {

    return CurrentState;

}
#endif /* MiGetCurrentState */

/***************************************************************************

  Routine Name: event_manager

  Date Created: May 6, 1996

        Author: SBR

   Description: The event_manager removes an event from the EventQueue
                and makes it the new MiCurrentEvent, unless the EventQueue
                is empty, in which case, it just sets the MiCurrentEvent
                to be EV_IDLE.

                Interrupts are disabled during this function because we
                don't want the ISR timer to run while we are doing fifo
                actions.

         Input: None

        Output: None

                    Changes
   Number       Date        Initials    Description

**************************************************************************/
static void event_manager(void)
{
    TMiWord status;
    MI_BYTE event;

    _disable();
    status = queue_read(&event);

    if ( status == MI_SUCCESS) {

        MiCurrentEvent = (MICOS_EVENT) event;
    } else {

        MiCurrentEvent = EV_IDLE;
    }
    _enable();
    return;
}


/***************************************************************************

  Routine Name: MiEventWrite

  Date Created: May 6, 1996

        Author: SBR

   Description: adds an event to the end of the EventQueue.

                Interrupts are disabled during this function because we
                don't want the ISR timer to run while we are doing fifo
                actions.

         Input: an Event

        Output: a TMiResult with the following possible values:
                    RES_OK - if the Event was written
                    RES_EVENT_QUEUE_FULL - if it couldn't be written.

                    Changes
   Number       Date        Initials    Description

**************************************************************************/
void MiEventWrite( MICOS_EVENT Event )
{
    TMiWord status;

    status = queue_write( (MI_BYTE) Event);

    if (status != MI_SUCCESS ) {
        MiFatalError.Bit.EventQueueOverflow = 1;
    }

}
