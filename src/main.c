/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include "definitions.h"

#include "app/hvac_state.h"
#include "app/sensor_task.h"
#include "app/control_task.h"
#include "app/bacnet_task.h"

int main(void)
{
    SYS_Initialize(NULL);

    /* Fail-safe state during startup */
    HEAT_CALL_Clear();
    RS485_DIR_Clear();

    if (!HVAC_State_Init())
    {
        while (true)
        {
            HEAT_CALL_Clear();
        }
    }

    if (!SensorTask_Create())
    {
        while (true)
        {
            HEAT_CALL_Clear();
        }
    }

    if (!ControlTask_Create())
    {
        while (true)
        {
            HEAT_CALL_Clear();
        }
    }

    if (!BACnetTask_Create())
    {
        while (true)
        {
            HEAT_CALL_Clear();
        }
    }

    while (true)
    {
        SYS_Tasks();
    }

    return EXIT_FAILURE;
}

/*******************************************************************************
 End of File
*/

