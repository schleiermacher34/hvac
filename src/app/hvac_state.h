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

#ifndef HVAC_STATE_H
#define HVAC_STATE_H

#include <stdbool.h>

typedef struct
{
    float setpoint_c;
    bool heating_enabled;
} HVAC_Config_t;

typedef struct
{
    float room_temperature_c;
    bool sensor_valid;
    bool heat_call;
} HVAC_Status_t;

bool HVAC_State_Init(void);

bool HVAC_GetConfig(HVAC_Config_t *config);
bool HVAC_SetSetpoint(float setpoint_c);
bool HVAC_SetHeatingEnabled(bool enabled);

bool HVAC_GetStatus(HVAC_Status_t *status);
bool HVAC_UpdateStatus(
    float temperature_c,
    bool sensor_valid,
    bool heat_call
);

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
