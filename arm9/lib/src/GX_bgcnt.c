#include "global.h"
#include "gx.h"

ARM_FUNC void *G2_GetBG0ScrPtr(){
    u32 temp = (u32)(((reg_G2_BG0CNT & 0x1F00) >> 0x8) << 0xB);
    return (void *)(0x6000000 + (((reg_GX_DISPCNT & 0x38000000) >> 0x1B) << 0x10) + temp);
}

ARM_FUNC void *G2S_GetBG0ScrPtr(){
    return (void *)(0x6200000 + (((reg_G2S_DB_BG0CNT & 0x1F00) >> 0x8) << 0xB));
}

ARM_FUNC void *G2_GetBG1ScrPtr(){
    u32 temp = (u32)(((reg_G2_BG1CNT & 0x1F00) >> 0x8) << 0xB);
    return (void *)(0x6000000 + (((reg_GX_DISPCNT & 0x38000000) >> 0x1B) << 0x10) + temp);
}

ARM_FUNC void *G2S_GetBG1ScrPtr(){
    return (void *)(0x6200000 + (((reg_G2S_DB_BG1CNT & 0x1F00) >> 0x8) << 0xB));
}

ARM_FUNC void *G2_GetBG2ScrPtr(){
    u32 temp12 = (reg_GX_DISPCNT & 0x7);
    u32 temp3 = reg_G2_BG2CNT;
    u32 temp2 = (((reg_GX_DISPCNT & 0x38000000) >> 0x1B) << 0x10);
    u32 temp1 = ((temp3 & 0x1F00) >> 0x8);
    switch (temp12)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            return (void *)(0x6000000 + temp2 + (temp1 << 0xB));
        case 5:
            if (temp3 & 0x80)
                return (void *)(0x6000000 + (temp1 << 0xE));
            else
                return (void *)(0x6000000 + temp2 + (temp1 << 0xB));
        case 6:
            return (void *)0x6000000;
        default:
            return NULL;
    }
}

ARM_FUNC void *G2S_GetBG2ScrPtr(){
    u32 temp12 = (reg_GXS_DB_DISPCNT & 0x7);
    u32 temp3 = reg_G2S_DB_BG2CNT;
    u32 temp1 = ((temp3 & 0x1F00) >> 0x8);
    switch (temp12)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            return (void *)(0x6200000 + (temp1 << 0xB));
        case 5:
            if (temp3 & 0x80)
                return (void *)(0x6200000 + (temp1 << 0xE));
            else
                return (void *)(0x6200000 + (temp1 << 0xB));
        case 6:
            return NULL;
        default:
            return NULL;
    }
}

ARM_FUNC void *G2_GetBG3ScrPtr(){
    u32 temp12 = (reg_GX_DISPCNT & 0x7);
    u32 temp3 = reg_G2_BG3CNT;
    u32 temp2 = (((reg_GX_DISPCNT & 0x38000000) >> 0x1B) << 0x10);
    u32 temp1 = ((temp3 & 0x1F00) >> 0x8);
    switch (temp12)
    {
        case 0:
        case 1:
        case 2:
            return (void *)(0x6000000 + temp2 + (temp1 << 0xB));
        case 3:
        case 4:
        case 5:
            if (temp3 & 0x80)
                return (void *)(0x6000000 + (temp1 << 0xE));
            else
                return (void *)(0x6000000 + temp2 + (temp1 << 0xB));
        case 6:
            return NULL;
        default:
            return NULL;
    }
}

ARM_FUNC void *G2S_GetBG3ScrPtr(){
    u32 temp12 = (reg_GXS_DB_DISPCNT & 0x7);
    u32 temp3 = reg_G2S_DB_BG3CNT;
    u32 temp1 = ((temp3 & 0x1F00) >> 0x8);
    switch (temp12)
    {
        case 0:
        case 1:
        case 2:
            return (void *)(0x6200000 + (temp1 << 0xB));
        case 3:
        case 4:
        case 5:
            if (temp3 & 0x80)
                return (void *)(0x6200000 + (temp1 << 0xE));
            else
                return (void *)(0x6200000 + (temp1 << 0xB));
        case 6:
            return NULL;
        default:
            return NULL;
    }
}

ARM_FUNC void *G2_GetBG0CharPtr(){
    u32 temp = (u32)(((reg_G2_BG0CNT & 0x3C) >> 0x2) << 0xE);
    return (void *)(0x6000000 + (((reg_GX_DISPCNT & 0x7000000) >> 0x18) << 0x10) + temp);
}

ARM_FUNC void *G2S_GetBG0CharPtr(){
    return (void *)(0x6200000 + (((reg_G2S_DB_BG0CNT & 0x3C) >> 0x2) << 0xE));
}

ARM_FUNC void *G2_GetBG1CharPtr(){
    u32 temp = (u32)(((reg_G2_BG1CNT & 0x3C) >> 0x2) << 0xE);
    return (void *)(0x6000000 + (((reg_GX_DISPCNT & 0x7000000) >> 0x18) << 0x10) + temp);
}

ARM_FUNC void *G2S_GetBG1CharPtr(){
    return (void *)(0x6200000 + (((reg_G2S_DB_BG1CNT & 0x3C) >> 0x2) << 0xE));
}

ARM_FUNC void *G2_GetBG2CharPtr(){
    s32 temp1 = (s32)(reg_GX_DISPCNT & 0x7);
    u32 temp = reg_G2_BG2CNT;
    if (temp1 < 5 || !(temp & 0x80))
    {
        u32 temp1 = (((reg_GX_DISPCNT & 0x7000000) >> 0x18) << 0x10);
        u32 temp2 = (temp & 0x3C) >> 2;
        return (void *)(0x6000000 + temp1 + (temp2 << 0xE));
    }
    else
    {
        return NULL;
    }
}

ARM_FUNC void *G2S_GetBG2CharPtr(){
    s32 temp1 = (s32)(reg_GXS_DB_DISPCNT & 0x7);
    u32 temp = reg_G2S_DB_BG2CNT;
    if (temp1 < 5 || !(temp & 0x80))
    {
        u32 temp2 = ((temp & 0x3C) >> 2) << 0xE;
        return (void *)(0x6200000 + temp2);
    }
    else
    {
        return NULL;
    }
}

ARM_FUNC void *G2_GetBG3CharPtr(){
    s32 temp1 = (s32)(reg_GX_DISPCNT & 0x7);
    u32 temp = reg_G2_BG3CNT;
    if (temp1 < 3 || (temp1 < 6 && !(temp & 0x80)))
    {
        u32 temp1 = (((reg_GX_DISPCNT & 0x7000000) >> 0x18) << 0x10);
        u32 temp2 = (temp & 0x3C) >> 2;
        return (void *)(0x6000000 + temp1 + (temp2 << 0xE));
    }
    else
    {
        return NULL;
    }
}

ARM_FUNC void *G2S_GetBG3CharPtr(){
    s32 temp1 = (s32)(reg_GXS_DB_DISPCNT & 0x7);
    u32 temp = reg_G2S_DB_BG3CNT;
    if (temp1 < 3 || (temp1 < 6 && !(temp & 0x80)))
    {
        u32 temp2 = ((temp & 0x3C) >> 2) << 0xE;
        return (void *)(0x6200000 + temp2);
    }
    else
    {
        return NULL;
    }
}
