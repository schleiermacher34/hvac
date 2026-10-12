/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef BACNET_OBJECTS_H
#define BACNET_OBJECTS_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/*
 * BACnet object instances used by this controller.
 *
 * AI 0 - Room Temperature
 * AV 0 - Temperature Setpoint
 * BO 0 - Heating Enable
 * BO 1 - Heat Call
 * BI 0 - Sensor Fault
 */

#define BACNET_AI_ROOM_TEMPERATURE_INSTANCE     0U
#define BACNET_AV_SETPOINT_INSTANCE             0U
#define BACNET_BO_HEATING_ENABLE_INSTANCE       0U
#define BACNET_BO_HEAT_CALL_INSTANCE            1U
#define BACNET_BI_SENSOR_FAULT_INSTANCE         0U



typedef enum
{
    BACNET_OBJECT_AI,
    BACNET_OBJECT_AV,
    BACNET_OBJECT_BI,
    BACNET_OBJECT_BO
} BACnetObjectType_t;

typedef enum
{
    BACNET_UNITS_NONE,
    BACNET_UNITS_DEGREES_CELSIUS
} BACnetUnits_t;

typedef struct
{
    BACnetObjectType_t type;
    uint32_t instance;
    const char *name;
    const char *description;
    BACnetUnits_t units;
    bool writable;
} BACnetObjectInfo_t;

extern const BACnetObjectInfo_t g_bacnetObjects[];
extern const size_t g_bacnetObjectCount;

const BACnetObjectInfo_t *BACnetObjects_Find(
    BACnetObjectType_t type,
    uint32_t instance);

/* Analog Input */
bool BACnetObjects_GetRoomTemperature(float *temperature_c);

/* Analog Value */
bool BACnetObjects_GetSetpoint(float *setpoint_c);
bool BACnetObjects_SetSetpoint(float setpoint_c);

/* Binary Output - configuration/command */
bool BACnetObjects_GetHeatingEnable(bool *enabled);
bool BACnetObjects_SetHeatingEnable(bool enabled);

/* Binary Output - controller status */
bool BACnetObjects_GetHeatCall(bool *active);

/* Binary Input */
bool BACnetObjects_GetSensorFault(bool *fault);
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
