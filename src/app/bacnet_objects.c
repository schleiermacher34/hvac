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
#include "bacnet_objects.h"
#include "app/hvac_state.h"

#include <stddef.h>




bool BACnetObjects_GetRoomTemperature(float *temperature_c)
{
    HVAC_Status_t status;

    if (temperature_c == NULL)
    {
        return false;
    }

    if (!HVAC_GetStatus(&status))
    {
        return false;
    }

    *temperature_c = status.room_temperature_c;

    return true;
}


bool BACnetObjects_GetSetpoint(float *setpoint_c)
{
    HVAC_Config_t config;

    if (setpoint_c == NULL)
    {
        return false;
    }

    if (!HVAC_GetConfig(&config))
    {
        return false;
    }

    *setpoint_c = config.setpoint_c;

    return true;
}


bool BACnetObjects_SetSetpoint(float setpoint_c)
{
    return HVAC_SetSetpoint(setpoint_c);
}


bool BACnetObjects_GetHeatingEnable(bool *enabled)
{
    HVAC_Config_t config;

    if (enabled == NULL)
    {
        return false;
    }

    if (!HVAC_GetConfig(&config))
    {
        return false;
    }

    *enabled = config.heating_enabled;

    return true;
}


bool BACnetObjects_SetHeatingEnable(bool enabled)
{
    return HVAC_SetHeatingEnabled(enabled);
}


bool BACnetObjects_GetHeatCall(bool *active)
{
    HVAC_Status_t status;

    if (active == NULL)
    {
        return false;
    }

    if (!HVAC_GetStatus(&status))
    {
        return false;
    }

    *active = status.heat_call;

    return true;
}


bool BACnetObjects_GetSensorFault(bool *fault)
{
    HVAC_Status_t status;

    if (fault == NULL)
    {
        return false;
    }

    if (!HVAC_GetStatus(&status))
    {
        return false;
    }

    *fault = !status.sensor_valid;

    return true;
}


const BACnetObjectInfo_t g_bacnetObjects[] =
{
    {
        .type = BACNET_OBJECT_AI,
        .instance = BACNET_AI_ROOM_TEMPERATURE_INSTANCE,
        .name = "Room Temperature",
        .description = "Measured room temperature",
        .units = BACNET_UNITS_DEGREES_CELSIUS,
        .writable = false
    },

    {
        .type = BACNET_OBJECT_AV,
        .instance = BACNET_AV_SETPOINT_INSTANCE,
        .name = "Temperature Setpoint",
        .description = "Requested room temperature",
        .units = BACNET_UNITS_DEGREES_CELSIUS,
        .writable = true
    },

    {
        .type = BACNET_OBJECT_BO,
        .instance = BACNET_BO_HEATING_ENABLE_INSTANCE,
        .name = "Heating Enable",
        .description = "Enables or disables heating control",
        .units = BACNET_UNITS_NONE,
        .writable = true
    },

    {
        .type = BACNET_OBJECT_BO,
        .instance = BACNET_BO_HEAT_CALL_INSTANCE,
        .name = "Heat Call",
        .description = "Current heating demand state",
        .units = BACNET_UNITS_NONE,
        .writable = false
    },

    {
        .type = BACNET_OBJECT_BI,
        .instance = BACNET_BI_SENSOR_FAULT_INSTANCE,
        .name = "Sensor Fault",
        .description = "Temperature sensor fault state",
        .units = BACNET_UNITS_NONE,
        .writable = false
    }
};

const size_t g_bacnetObjectCount =
    sizeof(g_bacnetObjects) / sizeof(g_bacnetObjects[0]);

const BACnetObjectInfo_t *BACnetObjects_Find(
    BACnetObjectType_t type,
    uint32_t instance)
{
    for (size_t i = 0; i < g_bacnetObjectCount; i++)
    {
        if ((g_bacnetObjects[i].type == type) &&
            (g_bacnetObjects[i].instance == instance))
        {
            return &g_bacnetObjects[i];
        }
    }

    return NULL;
}
/* *****************************************************************************
 End of File
 */
