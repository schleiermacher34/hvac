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
#include "bacnet_device.h"

static const BACnetDeviceInfo_t g_deviceInfo =
{
    .device_instance = 1001U,
    .object_name = "HVAC Heating Controller",
    .model_name = "PIC32CM BACnet Heating Controller",
    .vendor_name = "Demo Controller",
    .vendor_id = 999U
};

const BACnetDeviceInfo_t *BACnetDevice_GetInfo(void)
{
    return &g_deviceInfo;
}

size_t BACnetDevice_GetObjectCount(void)
{
    return g_bacnetObjectCount;
}

const BACnetObjectInfo_t *BACnetDevice_GetObjectByIndex(size_t index)
{
    if (index >= g_bacnetObjectCount)
    {
        return NULL;
    }

    return &g_bacnetObjects[index];
}
/* *****************************************************************************
 End of File
 */
