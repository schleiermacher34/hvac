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

#ifndef RS485_H
#define RS485_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool RS485_Write(const uint8_t *data, size_t length);
bool RS485_Read(uint8_t *data, size_t length);

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
