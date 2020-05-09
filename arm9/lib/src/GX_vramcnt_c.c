#include "global.h"
#include "main.h"
#include "gx.h"

void GX_VRAMCNT_SetLCDC_(u32 r0){
    if (r0 & (0x1 << 0))
        SETREG8(HW_REG_VRAMCNT_A, 0x80);
    if (r0 & (0x1 << 1))
        SETREG8(HW_REG_VRAMCNT_B, 0x80);
    if (r0 & (0x1 << 2))
        SETREG8(HW_REG_VRAMCNT_C, 0x80);
    if (r0 & (0x1 << 3))
        SETREG8(HW_REG_VRAMCNT_D, 0x80);
    if (r0 & (0x1 << 4))
        SETREG8(HW_REG_VRAMCNT_E, 0x80);
    if (r0 & (0x1 << 5))
        SETREG8(HW_REG_VRAMCNT_F, 0x80);
    if (r0 & (0x1 << 6))
        SETREG8(HW_REG_VRAMCNT_G, 0x80);
    if (r0 & (0x1 << 7))
        SETREG8(HW_REG_VRAMCNT_H, 0x80);
    if (r0 & (0x1 << 8))
        SETREG8(HW_REG_VRAMCNT_I, 0x80);
}
