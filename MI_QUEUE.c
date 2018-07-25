/************************************************************************/
/*                                                                      */
/*              DEVELOPED BY:   SLTF CONSULTING                         */
/*                              6316 DISTANT ROCK PATH                  */
/*                              COLUMBIA, MARYLAND USA  21045           */
/*                              410.799.3915                            */
/*                                                                      */
/************************************************************************/

/****************************************************************************
*   $MODULE
*   mi_queue.c -- Queue used by MiCOS.
*
****************************************************************************/

/********************************************************************
*   $INCLUDES
*********************************************************************/
#include "mi_cos.h"
#include "mi_queue.h"
#include "mi_app.h"

/********************************************************************
*   $DEFINES
*********************************************************************/
#define MI_TRUE   1
#define MI_FALSE  0

/*********************************************************************
*   $LOCAL PROTOTYPES
*********************************************************************/
typedef struct {
  MI_BYTE start[MI_EVENT_QUEUE_LENGTH];   /* fifo data storage start location */
  TMiWord head;                     /* index to where new data goes */
  TMiWord tail;                 /* index to where oldest data comes from */
  TMiWord full;
} TMiQueue;


/*********************************************************************
*   $GLOBAL VARIABLES
*********************************************************************/
static TMiQueue queue;

/*****************************************************************
*   $LOCAL VARIABLES
*******************************************************************/


/***************************************************************************

  Routine Name: queue_write

  Date Created: May 24, 1996

        Author: SBR

   Description: This will write data to the fifo data array if there's
                room.  If the array is full, an error is returned.

         Input: an Event

        Output: An TMiWord with the following possible values:

                MI_SUCCESS:    The event was written to the queue.

                MI_FULL:       The event queue was full so the event could not
                            be written.

                    Changes
   Number       Date        Initials    Description

**************************************************************************/
TMiWord queue_write(MI_BYTE Event )
{
    if ( queue.full ) {
        return MI_FULL;
    }

    /* Place the data at the head of the queue. */
    queue.start[queue.head] = Event;

    /* Increment the head. */
    queue.head++;

    /* Account for wrap-around. */
    queue.head %= MI_EVENT_QUEUE_LENGTH;

    /* Finally, if the queue is now full, set the flag. */
    if ( queue.head == queue.tail) {
        queue.full = MI_TRUE;
    }

    return MI_SUCCESS;
}

/***************************************************************************

  Routine Name: queue_read

  Date Created: May 24, 1996

        Author: SBR

   Description: This will read data from the queue. If the queue is empty,
                EMPTY is returned.

         Input: a pointer to a variable where the event should be placed.

        Output: An TMiWord with the following possible values:

                MI_SUCCESS:    An event was read from the queue.

                MI_EMPTY:      The event queue was empty so an event could not
                            be read.

                    Changes
   Number       Date        Initials    Description

**************************************************************************/
TMiWord queue_read(MI_BYTE *pEvent)
{
    if (queue.full == MI_FALSE && queue.tail == queue.head) {
        return MI_EMPTY;     /* nothing in buffer to return */
    }

    /* Place the oldest data in the passed in variable */
    (*pEvent) = queue.start[queue.tail];

    /* Increment the tail. */
    queue.tail++;

    /* Take wrap-around into account */
    queue.tail %= MI_EVENT_QUEUE_LENGTH;

    /* If we removed an event, the queue can't be full. */
    queue.full = MI_FALSE;

    return MI_SUCCESS;               /* return a pointer to the data */
}
