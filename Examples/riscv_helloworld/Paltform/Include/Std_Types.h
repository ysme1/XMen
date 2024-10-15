#ifndef STD_TYPES_H
#define STD_TYPES_H

#include "Platform_Types.h"
#include "Compiler.h"

#define E_NOT_OK 0x01u
#define E_OK 0x00u

typedef unsigned char StatusType;

typedef uint8 Std_ReturnType;

typedef struct {
    uint16  vendorID;               /* vendor ID */
    uint16  moduleID;               /* module ID */
    uint8   instanceID;
    uint8   sw_major_version;       /* software major version */
    uint8   sw_minor_version;       /* software minor version */
    uint8   sw_patch_version;       /* software patch version */
} Std_VersionInfoType;

#endif /* #ifndef STD_TYPES_H */
