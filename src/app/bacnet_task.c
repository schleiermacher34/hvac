/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */


#include "app/bacnet_task.h"
#include "drivers/rs485.h"

#include "FreeRTOS.h"
#include "task.h"

#include <stdint.h>

#define BACNET_RX_BUFFER_SIZE    256U

static void BACnetTask(void *pvParameters)
{
    uint8_t rxBuffer[BACNET_RX_BUFFER_SIZE];

    (void)pvParameters;

    for (;;)
    {
        /*
         * Placeholder for BACnet MS/TP receive logic.
         *
         * Later:
         * 1. Receive frame from RS-485
         * 2. Validate BACnet MS/TP frame
         * 3. Decode BACnet NPDU/APDU
         * 4. Update HVAC objects / controller settings
         * 5. Send response if required
         */

        (void)rxBuffer;

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

bool BACnetTask_Create(void)
{
    if (xTaskCreate(
            BACnetTask,
            "BACnet",
            384,
            NULL,
            2,
            NULL) != pdPASS)
    {
        return false;
    }

    return true;
}

/* *****************************************************************************
 End of File
 */
