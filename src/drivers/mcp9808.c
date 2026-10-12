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
/* Section: Included Files   
 * 
 * 
 * 
 * 
                                                 */
/* ************************************************************************** */
/* ************************************************************************** */
#include <stddef.h>
#include <stdint.h>
#include "mcp9808.h"

#include "definitions.h"

static bool MCP9808_ReadRegister16(uint8_t reg, uint16_t *value)
{
    uint8_t rxData[2];

    if (value == NULL)
    {
        return false;
    }

    if (!SERCOM0_I2C_WriteRead(
            MCP9808_I2C_ADDRESS,
            &reg,
            1U,
            rxData,
            2U))
    {
        return false;
    }

    while (SERCOM0_I2C_IsBusy())
    {
        /* Wait for transaction to complete */
    }

    if (SERCOM0_I2C_ErrorGet() != SERCOM_I2C_ERROR_NONE)
    {
        return false;
    }

    *value = ((uint16_t)rxData[0] << 8) | rxData[1];

    return true;
}

bool MCP9808_Init(void)
{
    uint16_t manufacturerId;

    if (!MCP9808_ReadRegister16(
            MCP9808_REG_MANUFACTURER_ID,
            &manufacturerId))
    {
        return false;
    }

    return (manufacturerId == 0x0054U);
}

bool MCP9808_ReadTemperature(float *temperature_c)
{
    uint16_t raw;

    if (temperature_c == NULL)
    {
        return false;
    }

    if (!MCP9808_ReadRegister16(
            MCP9808_REG_AMBIENT_TEMP,
            &raw))
    {
        return false;
    }

    /*
     * Bits 15:13 are status flags.
     * Bit 12 is the sign bit.
     * Bits 11:0 contain temperature magnitude
     * with 0.0625°C resolution.
     */
    raw &= 0x1FFFU;

    if ((raw & 0x1000U) != 0U)
    {
        raw &= 0x0FFFU;
        *temperature_c = ((float)raw * 0.0625f) - 256.0f;
    }
    else
    {
        *temperature_c = (float)raw * 0.0625f;
    }

    return true;
}
