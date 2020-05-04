#include "global.h"
#include "main.h"
#include "fx.h"

void MTX_ScaleApply33(struct Mtx33 *mtx, struct Mtx33 *dst, s32 x, s32 y, s32 z){
    dst->_[0] = ((s64)x * mtx->_[0]) >> FX32_INT_SHIFT;
    dst->_[1] = ((s64)x * mtx->_[1]) >> FX32_INT_SHIFT;
    dst->_[2] = ((s64)x * mtx->_[2]) >> FX32_INT_SHIFT;
    dst->_[3] = ((s64)y * mtx->_[3]) >> FX32_INT_SHIFT;
    dst->_[4] = ((s64)y * mtx->_[4]) >> FX32_INT_SHIFT;
    dst->_[5] = ((s64)y * mtx->_[5]) >> FX32_INT_SHIFT;
    dst->_[6] = ((s64)z * mtx->_[6]) >> FX32_INT_SHIFT;
    dst->_[7] = ((s64)z * mtx->_[7]) >> FX32_INT_SHIFT;
    dst->_[8] = ((s64)z * mtx->_[8]) >> FX32_INT_SHIFT;
}

void MTX_Concat33(struct Mtx33 *a, struct Mtx33 *b, struct Mtx33 *c){
    struct Mtx33 temp;
    struct Mtx33 *dst;
    s32 a0, a1, a2;
    s32 b0, b1, b2;

    if (c == b)
        dst = &temp;
    else
        dst = c;

    a0 = a->_[0];
    a1 = a->_[1];
    a2 = a->_[2];
    dst->_[0] =  (((s64)a0  * b->_[0] + (s64)a1  * b->_[3] + (s64)a2  * b->_[6] ) >> FX32_INT_SHIFT);
    dst->_[1] =  (((s64)a0  * b->_[1] + (s64)a1  * b->_[4] + (s64)a2  * b->_[7] ) >> FX32_INT_SHIFT);
    b0 = b->_[2];
    b1 = b->_[5];
    b2 = b->_[8];
    dst->_[2] =  (((s64)a0  * b0 + (s64)a1  * b1 + (s64)a2  * b2) >> FX32_INT_SHIFT);
    a0 = a->_[3];
    a1 = a->_[4];
    a2 = a->_[5];
    dst->_[5] =  (((s64)a0  * b0 + (s64)a1  * b1 + (s64)a2  * b2) >> FX32_INT_SHIFT);
    dst->_[4] =  (((s64)a0  * b->_[1] + (s64)a1  * b->_[4] + (s64)a2  * b->_[7] ) >> FX32_INT_SHIFT);
    b0 = b->_[0];
    b1 = b->_[3];
    b2 = b->_[6];
    dst->_[3] =  (((s64)a0  * b0 + (s64)a1  * b1 + (s64)a2  * b2) >> FX32_INT_SHIFT);
    a0 = a->_[6];
    a1 = a->_[7];
    a2 = a->_[8];
    dst->_[6] =  (((s64)a0  * b0 + (s64)a1  * b1 + (s64)a2 * b2) >> FX32_INT_SHIFT);
    dst->_[7] =  (((s64)a0  * b->_[1] + (s64)a1  * b->_[4] + (s64)a2 * b->_[7] ) >> FX32_INT_SHIFT);
    b0 = b->_[2];
    b1 = b->_[5];
    b2 = b->_[8];
    dst->_[8] = (((s64)a0  * b0 + (s64)a1  * b1 + (s64)a2 * b2) >> FX32_INT_SHIFT);

    if (dst == &temp)
        *c = temp;
}

void MTX_MultVec33(struct Vecx32 *vec, struct Mtx33 *mtx, struct Vecx32 *dst){
    s32 x, y, z;
    x = vec->x;
    y = vec->y;
    z = vec->z;
    dst->x = ((s64)x * mtx->_[0] + (s64)y * mtx->_[3] + (s64)z * mtx->_[6]) >> FX32_INT_SHIFT;
    dst->y = ((s64)x * mtx->_[1] + (s64)y * mtx->_[4] + (s64)z * mtx->_[7]) >> FX32_INT_SHIFT;
    dst->z = ((s64)x * mtx->_[2] + (s64)y * mtx->_[5] + (s64)z * mtx->_[8]) >> FX32_INT_SHIFT;
}

asm void MTX_Identity33_(struct Mtx33 *mtx){
    mov r2, #0x1000
    str r2, [r0, #0x20]
    mov r3, #0x0
    stmia r0!, {r2-r3}
    mov r1, #0x0
    stmia r0!, {r1,r3}
    stmia r0!, {r2-r3}
    stmia r0!, {r1,r3}
    bx lr
}

#pragma thumb on
asm void MTX_RotX33_(struct Mtx33 *mtx, s32 sinphi, s32 cosphi){
    mov r3, #0x1
	lsl r3, r3, #0xc
	str r3, [r0, #0x0]
	mov r3, #0x0
	str r3, [r0, #0x4]
	str r3, [r0, #0x8]
	str r3, [r0, #0xc]
	str r2, [r0, #0x10]
	str r1, [r0, #0x14]
	str r3, [r0, #0x18]
	neg r1, r1
	str r1, [r0, #0x1c]
	str r2, [r0, #0x20]
	bx lr
}
#pragma thumb off

#pragma thumb on
asm void MTX_RotY33_(struct Mtx33 *mtx, s32 sinphi, s32 cosphi){
    str r2, [r0, #0x0]
	str r2, [r0, #0x20]
	mov r3, #0x0
	str r3, [r0, #0x4]
	str r3, [r0, #0xc]
	str r3, [r0, #0x14]
	str r3, [r0, #0x1c]
	neg r2, r1
	mov r3, #0x1
	lsl r3, r3, #0xc
	str r1, [r0, #0x18]
	str r2, [r0, #0x8]
	str r3, [r0, #0x10]
	bx lr
}
#pragma thumb off

#pragma thumb on
asm void MTX_RotZ33_(struct Mtx33 *mtx, s32 sinphi, s32 cosphi){
    stmia r0!, {r2}
	mov r3, #0x0
	stmia r0!, {r1,r3}
	neg r1, r1
	stmia r0!, {r1-r2}
	mov r1, #0x1
	lsl r1, r1, #0xc
	str r3, [r0, #0x0]
	str r3, [r0, #0x4]
	str r3, [r0, #0x8]
	str r1, [r0, #0xc]
	bx lr
}
#pragma thumb off
