#ifndef POKEDIAMOND_OS_PROTECTIONREGION_H
#define POKEDIAMOND_OS_PROTECTIONREGION_H

#include "nitro/types.h"
#include "consts.h"

void OS_SetDPermissionsForProtectionRegion(register u32 setMask, register u32 flags);
void OS_SetProtectionRegion1(u32 param);
void OS_SetProtectionRegion2(u32 param);

typedef enum
{
    OSi_PR_BASE_MASK_4KB = 0xfffff000,
    OSi_PR_BASE_MASK_8KB = 0xffffe000,
    OSi_PR_BASE_MASK_16KB = 0xffffc000,
    OSi_PR_BASE_MASK_32KB = 0xffff8000,
    OSi_PR_BASE_MASK_64KB = 0xffff0000,
    OSi_PR_BASE_MASK_128KB = 0xfffe0000,
    OSi_PR_BASE_MASK_256KB = 0xfffc0000,
    OSi_PR_BASE_MASK_512KB = 0xfff80000,
    OSi_PR_BASE_MASK_1MB = 0xfff00000,
    OSi_PR_BASE_MASK_2MB = 0xffe00000,
    OSi_PR_BASE_MASK_4MB = 0xffc00000,
    OSi_PR_BASE_MASK_8MB = 0xff800000,
    OSi_PR_BASE_MASK_16MB = 0xff000000,
    OSi_PR_BASE_MASK_32MB = 0xfe000000,
    OSi_PR_BASE_MASK_64MB = 0xfc000000,
    OSi_PR_BASE_MASK_128MB = 0xf8000000,
    OSi_PR_BASE_MASK_256MB = 0xf0000000,
    OSi_PR_BASE_MASK_512MB = 0xe0000000,
    OSi_PR_BASE_MASK_1GB = 0xc0000000,
    OSi_PR_BASE_MASK_2GB = 0x80000000,
    OSi_PR_BASE_MASK_4GB = 0x00000000
} OSiProtectionRegionBaseMask;

static inline u32 OSi_CalcPRParam(u32 address, u32 size, OSiProtectionRegionBaseMask mask) {
    return ((address & mask) | size);
}

#define OS_SetProtectionRegion(regionNo, address, sizeStr)  \
  OS_SetProtectionRegion##regionNo(OSi_CalcPRParam(address, HW_C6_PR_##sizeStr, OSi_PR_BASE_MASK_##sizeStr) \
                                   | 1)

#define OS_PR3_ACCESS_MASK   (HW_C5_PERMIT_MASK << HW_C5_PR3_SFT)
#define OS_PR3_ACCESS_RW     (HW_C5_PERMIT_RW   << HW_C5_PR3_SFT)
#define OS_PR3_ACCESS_RO     (HW_C5_PERMIT_RO   << HW_C5_PR3_SFT)

#endif //POKEDIAMOND_OS_PROTECTIONREGION_H
