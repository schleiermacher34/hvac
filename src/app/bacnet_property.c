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

/* This section lists the other files that are included in this file.
 */

#include "bacnet_property.h"

#include <stddef.h>

bool BACnetProperty_Read(
    BACnetObjectType_t object_type,
    uint32_t instance,
    BACnetProperty_t property,
    BACnetValue_t *value)
{
    const BACnetObjectInfo_t *object;

    if (value == NULL)
    {
        return false;
    }

    object = BACnetObjects_Find(object_type, instance);

    if (object == NULL)
    {
        return false;
    }

    switch (property)
    {
        case BACNET_PROPERTY_OBJECT_NAME:
            value->type = BACNET_VALUE_STRING;
            value->data.string_value = object->name;
            return true;

        case BACNET_PROPERTY_DESCRIPTION:
            value->type = BACNET_VALUE_STRING;
            value->data.string_value = object->description;
            return true;

        case BACNET_PROPERTY_UNITS:
            value->type = BACNET_VALUE_UINT32;
            value->data.uint32_value = (uint32_t)object->units;
            return true;

        case BACNET_PROPERTY_PRESENT_VALUE:
            break;

        default:
            return false;
    }

    switch (object_type)
    {
        case BACNET_OBJECT_AI:
        {
            float temperature;

            if (instance != BACNET_AI_ROOM_TEMPERATURE_INSTANCE)
            {
                return false;
            }

            if (!BACnetObjects_GetRoomTemperature(&temperature))
            {
                return false;
            }

            value->type = BACNET_VALUE_FLOAT;
            value->data.float_value = temperature;

            return true;
        }

        case BACNET_OBJECT_AV:
        {
            float setpoint;

            if (instance != BACNET_AV_SETPOINT_INSTANCE)
            {
                return false;
            }

            if (!BACnetObjects_GetSetpoint(&setpoint))
            {
                return false;
            }

            value->type = BACNET_VALUE_FLOAT;
            value->data.float_value = setpoint;

            return true;
        }

        case BACNET_OBJECT_BO:
        {
            bool state;

            if (instance == BACNET_BO_HEATING_ENABLE_INSTANCE)
            {
                if (!BACnetObjects_GetHeatingEnable(&state))
                {
                    return false;
                }
            }
            else if (instance == BACNET_BO_HEAT_CALL_INSTANCE)
            {
                if (!BACnetObjects_GetHeatCall(&state))
                {
                    return false;
                }
            }
            else
            {
                return false;
            }

            value->type = BACNET_VALUE_BOOL;
            value->data.bool_value = state;

            return true;
        }

        case BACNET_OBJECT_BI:
        {
            bool fault;

            if (instance != BACNET_BI_SENSOR_FAULT_INSTANCE)
            {
                return false;
            }

            if (!BACnetObjects_GetSensorFault(&fault))
            {
                return false;
            }

            value->type = BACNET_VALUE_BOOL;
            value->data.bool_value = fault;

            return true;
        }

        default:
            return false;
    }
}

bool BACnetProperty_Write(
    BACnetObjectType_t object_type,
    uint32_t instance,
    BACnetProperty_t property,
    const BACnetValue_t *value)
{
    const BACnetObjectInfo_t *object;

    if (value == NULL)
    {
        return false;
    }

    object = BACnetObjects_Find(object_type, instance);

    if (object == NULL)
    {
        return false;
    }

    if (!object->writable)
    {
        return false;
    }

    if (property != BACNET_PROPERTY_PRESENT_VALUE)
    {
        return false;
    }

    switch (object_type)
    {
        case BACNET_OBJECT_AV:

            if (instance != BACNET_AV_SETPOINT_INSTANCE)
            {
                return false;
            }

            if (value->type != BACNET_VALUE_FLOAT)
            {
                return false;
            }

            return BACnetObjects_SetSetpoint(
                value->data.float_value
            );

        case BACNET_OBJECT_BO:

            if (instance != BACNET_BO_HEATING_ENABLE_INSTANCE)
            {
                return false;
            }

            if (value->type != BACNET_VALUE_BOOL)
            {
                return false;
            }

            return BACnetObjects_SetHeatingEnable(
                value->data.bool_value
            );

        default:
            return false;
    }
}

/* *****************************************************************************
 End of File
 */
