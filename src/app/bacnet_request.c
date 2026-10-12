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

/* TODO:  Include other files here if needed. */
#include "bacnet_request.h"

#include <stddef.h>

void BACnetRequest_Handle(
    const BACnetRequest_t *request,
    BACnetResponse_t *response)
{
    if ((request == NULL) || (response == NULL))
    {
        return;
    }

    response->code = BACNET_RESPONSE_INTERNAL_ERROR;
    response->value.type = BACNET_VALUE_NONE;

    switch (request->request_type)
    {
        case BACNET_REQUEST_READ_PROPERTY:

            if (BACnetProperty_Read(
                    request->object_type,
                    request->instance,
                    request->property,
                    &response->value))
            {
                response->code = BACNET_RESPONSE_OK;
            }
            else
            {
                response->code = BACNET_RESPONSE_PROPERTY_NOT_FOUND;
            }

            break;

        case BACNET_REQUEST_WRITE_PROPERTY:

            if (BACnetProperty_Write(
                    request->object_type,
                    request->instance,
                    request->property,
                    &request->value))
            {
                response->code = BACNET_RESPONSE_OK;
            }
            else
            {
                response->code = BACNET_RESPONSE_WRITE_DENIED;
            }

            break;

        default:
            response->code = BACNET_RESPONSE_INTERNAL_ERROR;
            break;
    }
}