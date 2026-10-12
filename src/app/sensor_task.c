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

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdbool.h>

#include "sensor_task.h"
#include "drivers/mcp9808.h"

#include "task.h"



QueueHandle_t g_SensorQueue = NULL;

static void SensorTask(void *pvParameters)
{
    SensorData_t data;

    (void)pvParameters;

    if (!MCP9808_Init())
    {
        data.temperature_c = 0.0f;
        data.valid = false;

        xQueueOverwrite(g_SensorQueue, &data);
    }

    for (;;)
    {
        data.valid = MCP9808_ReadTemperature(&data.temperature_c);

        xQueueOverwrite(g_SensorQueue, &data);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

bool SensorTask_Create(void)
{
    g_SensorQueue = xQueueCreate(1, sizeof(SensorData_t));

    if (g_SensorQueue == NULL)
    {
        return false;
    }

    if (xTaskCreate(
            SensorTask,
            "Sensor",
            256,
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
