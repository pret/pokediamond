#include "global.h"
#include "main.h"
#include "gx.h"

void *G2_GetBG0ScrPtr(){
    u32 temp = (((READREG16(HW_REG_BG0CNT_A) & 0x1F00) >> 0x8) << 0xB);
    return (void *)(0x6000000 + (((READREG32(HW_REG_DISPCNT_A) & 0x38000000) >> 0x1B) << 0x10) + temp);
}

void *G2S_GetBG0ScrPtr(){
    return (void *)(0x6200000 + (((READREG16(HW_REG_BG0CNT_B) & 0x1F00) >> 0x8) << 0xB));
}

void *G2_GetBG1ScrPtr(){
    u32 temp = (((READREG16(HW_REG_BG1CNT_A) & 0x1F00) >> 0x8) << 0xB);
    return (void *)(0x6000000 + (((READREG32(HW_REG_DISPCNT_A) & 0x38000000) >> 0x1B) << 0x10) + temp);
}

void *G2S_GetBG1ScrPtr(){
    return (void *)(0x6200000 + (((READREG16(HW_REG_BG1CNT_B) & 0x1F00) >> 0x8) << 0xB));
}

void *G2_GetBG2ScrPtr(){
    u32 temp12 = (READREG32(HW_REG_DISPCNT_A) & 0x7);
    u32 temp3 = READREG16(HW_REG_BG2CNT_A);
    u32 temp2 = (((READREG32(HW_REG_DISPCNT_A) & 0x38000000) >> 0x1B) << 0x10);
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

void *G2S_GetBG2ScrPtr(){
    u32 temp12 = (READREG32(HW_REG_DISPCNT_B) & 0x7);
    u32 temp3 = READREG16(HW_REG_BG2CNT_B);
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

void *G2_GetBG3ScrPtr(){
    u32 temp12 = (READREG32(HW_REG_DISPCNT_A) & 0x7);
    u32 temp3 = READREG16(HW_REG_BG3CNT_A);
    u32 temp2 = (((READREG32(HW_REG_DISPCNT_A) & 0x38000000) >> 0x1B) << 0x10);
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

void *G2S_GetBG3ScrPtr(){
    u32 temp12 = (READREG32(HW_REG_DISPCNT_B) & 0x7);
    u32 temp3 = READREG16(HW_REG_BG3CNT_B);
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

void *G2_GetBG0CharPtr(){
    u32 temp = (((READREG16(HW_REG_BG0CNT_A) & 0x3C) >> 0x2) << 0xE);
    return (void *)(0x6000000 + (((READREG32(HW_REG_DISPCNT_A) & 0x7000000) >> 0x18) << 0x10) + temp);
}

void *G2S_GetBG0CharPtr(){
    return (void *)(0x6200000 + (((READREG16(HW_REG_BG0CNT_B) & 0x3C) >> 0x2) << 0xE));
}

void *G2_GetBG1CharPtr(){
    u32 temp = (((READREG16(HW_REG_BG1CNT_A) & 0x3C) >> 0x2) << 0xE);
    return (void *)(0x6000000 + (((READREG32(HW_REG_DISPCNT_A) & 0x7000000) >> 0x18) << 0x10) + temp);
}

void *G2S_GetBG1CharPtr(){
    return (void *)(0x6200000 + (((READREG16(HW_REG_BG1CNT_B) & 0x3C) >> 0x2) << 0xE));
}

void *G2_GetBG2CharPtr(){
    s32 temp1 = (READREG32(HW_REG_DISPCNT_A) & 0x7);
    u32 temp = READREG16(HW_REG_BG2CNT_A);
    if (temp1 < 5 || !(temp & 0x80))
    {
        u32 temp1 = (((READREG32(HW_REG_DISPCNT_A) & 0x7000000) >> 0x18) << 0x10);
        u32 temp2 = (temp & 0x3C) >> 2;
        return (void *)(0x6000000 + temp1 + (temp2 << 0xE));
    }
    else
    {
        return NULL;
    }
}

void *G2S_GetBG2CharPtr(){
    s32 temp1 = (READREG32(HW_REG_DISPCNT_B) & 0x7);
    u32 temp = READREG16(HW_REG_BG2CNT_B);
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

void *G2_GetBG3CharPtr(){
    s32 temp1 = (READREG32(HW_REG_DISPCNT_A) & 0x7);
    u32 temp = READREG16(HW_REG_BG3CNT_A);
    if (temp1 < 3 || (temp1 < 6 && !(temp & 0x80)))
    {
        u32 temp1 = (((READREG32(HW_REG_DISPCNT_A) & 0x7000000) >> 0x18) << 0x10);
        u32 temp2 = (temp & 0x3C) >> 2;
        return (void *)(0x6000000 + temp1 + (temp2 << 0xE));
    }
    else
    {
        return NULL;
    }
}

void *G2S_GetBG3CharPtr(){
    s32 temp1 = (READREG32(HW_REG_DISPCNT_B) & 0x7);
    u32 temp = READREG16(HW_REG_BG3CNT_B);
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
