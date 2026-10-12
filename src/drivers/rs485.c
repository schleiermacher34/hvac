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

#include "drivers/rs485.h"
#include "definitions.h"

static void RS485_SetTransmitMode(void)
{
    RS485_DIR_Set();
}

static void RS485_SetReceiveMode(void)
{
    RS485_DIR_Clear();
}

bool RS485_Write(const uint8_t *data, size_t length)
{
    if ((data == NULL) || (length == 0U))
    {
        return false;
    }

    if (SERCOM1_USART_WriteIsBusy())
    {
        return false;
    }

    RS485_SetTransmitMode();

    if (!SERCOM1_USART_Write((void *)data, length))
    {
        RS485_SetReceiveMode();
        return false;
    }

    while (SERCOM1_USART_WriteIsBusy())
    {
        /* Wait until PLIB finishes sending buffer */
    }

    /*
          * wait until the final byte has actually left
     * the USART shift register before disabling DE.
     */
    while (!SERCOM1_USART_TransmitComplete())
    {
        /* Wait for final stop bit */
    }

    RS485_SetReceiveMode();

    return true;
}

bool RS485_Read(uint8_t *data, size_t length)
{
    if ((data == NULL) || (length == 0U))
    {
        return false;
    }

    if (SERCOM1_USART_ReadIsBusy())
    {
        return false;
    }

    RS485_SetReceiveMode();

    return SERCOM1_USART_Read(data, length);
}
/* *****************************************************************************
 End of File
 */
