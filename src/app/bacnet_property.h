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

#ifndef BACNET_PROPERTY_H
#define BACNET_PROPERTY_H

#include <stdbool.h>
#include <stdint.h>

#include "bacnet_objects.h"

typedef enum
{
    BACNET_PROPERTY_PRESENT_VALUE,
    BACNET_PROPERTY_OBJECT_NAME,
    BACNET_PROPERTY_DESCRIPTION,
    BACNET_PROPERTY_UNITS
} BACnetProperty_t;

typedef enum
{
    BACNET_VALUE_NONE,
    BACNET_VALUE_FLOAT,
    BACNET_VALUE_BOOL,
    BACNET_VALUE_STRING,
    BACNET_VALUE_UINT32
} BACnetValueType_t;

typedef struct
{
    BACnetValueType_t type;

    union
    {
        float float_value;
        bool bool_value;
        const char *string_value;
        uint32_t uint32_value;
    } data;

} BACnetValue_t;

bool BACnetProperty_Read(
    BACnetObjectType_t object_type,
    uint32_t instance,
    BACnetProperty_t property,
    BACnetValue_t *value
);

bool BACnetProperty_Write(
    BACnetObjectType_t object_type,
    uint32_t instance,
    BACnetProperty_t property,
    const BACnetValue_t *value
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
