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
#include "app/hvac_state.h"

#include "FreeRTOS.h"
#include "semphr.h"

#include <stddef.h>

#define HVAC_DEFAULT_SETPOINT_C    22.0f
#define HVAC_MIN_SETPOINT_C         5.0f
#define HVAC_MAX_SETPOINT_C        35.0f

static HVAC_Config_t g_config =
{
    .setpoint_c = HVAC_DEFAULT_SETPOINT_C,
    .heating_enabled = true
};

static HVAC_Status_t g_status =
{
    .room_temperature_c = 0.0f,
    .sensor_valid = false,
    .heat_call = false
};

static SemaphoreHandle_t g_stateMutex = NULL;

bool HVAC_State_Init(void)
{
    g_stateMutex = xSemaphoreCreateMutex();

    return (g_stateMutex != NULL);
}

bool HVAC_GetConfig(HVAC_Config_t *config)
{
    if ((config == NULL) || (g_stateMutex == NULL))
    {
        return false;
    }

    if (xSemaphoreTake(g_stateMutex, portMAX_DELAY) != pdTRUE)
    {
        return false;
    }

    *config = g_config;

    xSemaphoreGive(g_stateMutex);

    return true;
}

bool HVAC_SetSetpoint(float setpoint_c)
{
    if (g_stateMutex == NULL)
    {
        return false;
    }

    if ((setpoint_c < HVAC_MIN_SETPOINT_C) ||
        (setpoint_c > HVAC_MAX_SETPOINT_C))
    {
        return false;
    }

    if (xSemaphoreTake(g_stateMutex, portMAX_DELAY) != pdTRUE)
    {
        return false;
    }

    g_config.setpoint_c = setpoint_c;

    xSemaphoreGive(g_stateMutex);

    return true;
}

bool HVAC_SetHeatingEnabled(bool enabled)
{
    if (g_stateMutex == NULL)
    {
        return false;
    }

    if (xSemaphoreTake(g_stateMutex, portMAX_DELAY) != pdTRUE)
    {
        return false;
    }

    g_config.heating_enabled = enabled;

    xSemaphoreGive(g_stateMutex);

    return true;
}

bool HVAC_GetStatus(HVAC_Status_t *status)
{
    if ((status == NULL) || (g_stateMutex == NULL))
    {
        return false;
    }

    if (xSemaphoreTake(g_stateMutex, portMAX_DELAY) != pdTRUE)
    {
        return false;
    }

    *status = g_status;

    xSemaphoreGive(g_stateMutex);

    return true;
}

bool HVAC_UpdateStatus(
    float temperature_c,
    bool sensor_valid,
    bool heat_call)
{
    if (g_stateMutex == NULL)
    {
        return false;
    }

    if (xSemaphoreTake(g_stateMutex, portMAX_DELAY) != pdTRUE)
    {
        return false;
    }

    g_status.room_temperature_c = temperature_c;
    g_status.sensor_valid = sensor_valid;
    g_status.heat_call = heat_call;

    xSemaphoreGive(g_stateMutex);

    return true;
}
/* *****************************************************************************
 End of File
 */
