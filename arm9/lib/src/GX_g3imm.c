#include "global.h"
#include "gx.h"

void MI_Copy36B(void *src, void *dst);

ARM_FUNC void G3_LoadMtx43(struct Mtx43 *mtx){
    reg_G3X_GXFIFO = 0x17;
    GX_SendFifo48B(mtx, (void *)&reg_G3X_GXFIFO);
}

ARM_FUNC void G3_MultMtx43(struct Mtx43 *mtx){
    reg_G3X_GXFIFO = 0x19;
    GX_SendFifo48B(mtx, (void *)&reg_G3X_GXFIFO);
}

ARM_FUNC void G3_MultMtx33(struct Mtx33 *mtx){
    reg_G3X_GXFIFO = 0x1A;
    MI_Copy36B(mtx, (void *)&reg_G3X_GXFIFO);
}
