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

#ifndef BACNET_REQUEST_H
#define BACNET_REQUEST_H

#include <stdbool.h>
#include <stdint.h>

#include "bacnet_property.h"

typedef enum
{
    BACNET_REQUEST_READ_PROPERTY,
    BACNET_REQUEST_WRITE_PROPERTY
} BACnetRequestType_t;

typedef struct
{
    BACnetRequestType_t request_type;

    BACnetObjectType_t object_type;
    uint32_t instance;
    BACnetProperty_t property;

    BACnetValue_t value;
} BACnetRequest_t;

typedef enum
{
    BACNET_RESPONSE_OK,
    BACNET_RESPONSE_OBJECT_NOT_FOUND,
    BACNET_RESPONSE_PROPERTY_NOT_FOUND,
    BACNET_RESPONSE_WRITE_DENIED,
    BACNET_RESPONSE_INVALID_VALUE,
    BACNET_RESPONSE_INTERNAL_ERROR
} BACnetResponseCode_t;

typedef struct
{
    BACnetResponseCode_t code;
    BACnetValue_t value;
} BACnetResponse_t;

void BACnetRequest_Handle(
    const BACnetRequest_t *request,
    BACnetResponse_t *response
);

#endif