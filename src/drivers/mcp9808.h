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

#ifndef _MCP9808_H    /* Guard against multiple inclusion */
#define _MCP9808_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    
#include <stdbool.h>
#include <stdint.h>
    
    
#define MCP9808_I2C_ADDRESS 0x18U  /* so, as I puted GND for all adress pins, I'm going to use typical adress */


#define MCP9808_REG_AMBIENT_TEMP     0x05U
#define MCP9808_REG_MANUFACTURER_ID  0x06U
#define MCP9808_REG_DEVICE_ID        0x07U
#define MCP9808_REG_RESOLUTION       0x08U    
    
    
    bool MCP9808_Init(void);
    bool MCP9808_ReadTemperature(float *temperature_c);
    
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
