#include "global.h"
#include "main.h"
#include "gx.h"

void G3_LoadMtx43(struct Mtx43 *mtx){
    SETREG32(HW_REG_GXFIFO, 0x17);
    GX_SendFifo48B(mtx, (void *)HW_REG_GXFIFO);
}

void G3_MultMtx43(struct Mtx43 *mtx){
    SETREG32(HW_REG_GXFIFO, 0x19);
    GX_SendFifo48B(mtx, (void *)HW_REG_GXFIFO);
}

void G3_MultMtx33(struct Mtx33 *mtx){
    SETREG32(HW_REG_GXFIFO, 0x1A);
    MI_Copy36B(mtx, (void *)HW_REG_GXFIFO);
}
