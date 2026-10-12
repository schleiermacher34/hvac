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

#ifndef BACNET_DEVICE_H
#define BACNET_DEVICE_H

#include <stddef.h>
#include <stdint.h>

#include "bacnet_objects.h"

typedef struct
{
    uint32_t device_instance;
    const char *object_name;
    const char *model_name;
    const char *vendor_name;
    uint16_t vendor_id;
} BACnetDeviceInfo_t;

const BACnetDeviceInfo_t *BACnetDevice_GetInfo(void);

size_t BACnetDevice_GetObjectCount(void);

const BACnetObjectInfo_t *BACnetDevice_GetObjectByIndex(size_t index);


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
