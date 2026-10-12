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
#include "control_task.h"
#include "sensor_task.h"

#include "definitions.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "app/hvac_state.h"

#define DEFAULT_SETPOINT_C   22.0f
#define HYSTERESIS_C    0.5f

static void ControlTask(void *pvParameters)
{
    SensorData_t sensorData;
    HVAC_Config_t config;

    bool heating = false;

    (void)pvParameters;

    for (;;)
    {
        if (xQueueReceive(
                g_SensorQueue,
                &sensorData,
                portMAX_DELAY) == pdPASS)
        {
            if (!HVAC_GetConfig(&config))
            {
                heating = false;
            }
            else if (!config.heating_enabled)
            {
                heating = false;
            }
            else if (!sensorData.valid)
            {
                heating = false;
            }
            else if (!heating &&
                     sensorData.temperature_c <=
                     (config.setpoint_c - HYSTERESIS_C))
            {
                heating = true;
            }
            else if (heating &&
                     sensorData.temperature_c >=
                     (config.setpoint_c + HYSTERESIS_C))
            {
                heating = false;
            }

            if (heating)
            {
                HEAT_CALL_Set();
            }
            else
            {
                HEAT_CALL_Clear();
            }

            HVAC_UpdateStatus(
                sensorData.temperature_c,
                sensorData.valid,
                heating
            );
        }
    }
}

bool ControlTask_Create(void)
{
    if (xTaskCreate(
            ControlTask,
            "Control",
            256,
            NULL,
            3,
            NULL) != pdPASS)
    {
        return false;
    }

    return true;
}

/* *****************************************************************************
 End of File
 */
