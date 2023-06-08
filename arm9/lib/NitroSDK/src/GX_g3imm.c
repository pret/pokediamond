#include "nitro/types.h"
#include "gx.h"
#include "code32.h"

void G3_LoadMtx43(struct Mtx43 *mtx){
    reg_G3X_GXFIFO = 0x17;
    GX_SendFifo48B(mtx, (void *)&reg_G3X_GXFIFO);
}

void G3_MultMtx43(struct Mtx43 *mtx){
    reg_G3X_GXFIFO = 0x19;
    GX_SendFifo48B(mtx, (void *)&reg_G3X_GXFIFO);
}

void G3_MultMtx33(struct Mtx33 *mtx){
    reg_G3X_GXFIFO = 0x1A;
    MI_Copy36B(mtx, (void *)&reg_G3X_GXFIFO);
}
