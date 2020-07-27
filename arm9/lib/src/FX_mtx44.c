#include "global.h"
#include "main.h"
#include "fx.h"

void MI_Copy48B(void *src, void *dst);


ARM_FUNC void MTX_TransApply44(struct Mtx44 *mtx, struct Mtx44 *dst, fx32 x, fx32 y, fx32 z){
    if(mtx != dst)
        MI_Copy48B(mtx, dst);
    dst->_[12] = mtx->_[12] + (fx32)(((fx64)x * mtx->_[0] + (fx64)y * mtx->_[4] + (fx64)z * mtx->_[8] ) >> FX32_INT_SHIFT);
    dst->_[13] = mtx->_[13] + (fx32)(((fx64)x * mtx->_[1] + (fx64)y * mtx->_[5] + (fx64)z * mtx->_[9] ) >> FX32_INT_SHIFT);
    dst->_[14] = mtx->_[14] + (fx32)(((fx64)x * mtx->_[2] + (fx64)y * mtx->_[6] + (fx64)z * mtx->_[10]) >> FX32_INT_SHIFT);
    dst->_[15] = mtx->_[15] + (fx32)(((fx64)x * mtx->_[3] + (fx64)y * mtx->_[7] + (fx64)z * mtx->_[11]) >> FX32_INT_SHIFT);
}

ARM_FUNC void MTX_Concat44(struct Mtx44 *a, struct Mtx44 *b, struct Mtx44 *c){
    struct Mtx44 temp;
    struct Mtx44 *dst;
    fx32 a0, a1, a2, a3;
    fx32 b0, b1, b2, b3;

    if (c == b)
        dst = &temp;
    else
        dst = c;

    a0 = a->_[0];
    a1 = a->_[1];
    a2 = a->_[2];
    a3 = a->_[3];
    dst->_[0] =  (fx32)(((fx64)a0  * b->_[0] + (fx64)a1  * b->_[4] + (fx64)a2  * b->_[8]  + (fx64)a3  * b->_[12]) >> FX32_INT_SHIFT);
    dst->_[1] =  (fx32)(((fx64)a0  * b->_[1] + (fx64)a1  * b->_[5] + (fx64)a2  * b->_[9]  + (fx64)a3  * b->_[13]) >> FX32_INT_SHIFT);
    dst->_[3] =  (fx32)(((fx64)a0  * b->_[3] + (fx64)a1  * b->_[7] + (fx64)a2  * b->_[11] + (fx64)a3  * b->_[15]) >> FX32_INT_SHIFT);
    b0 = b->_[2];
    b1 = b->_[6];
    b2 = b->_[10];
    b3 = b->_[14];
    dst->_[2] =  (fx32)(((fx64)a0  * b0 + (fx64)a1  * b1 + (fx64)a2  * b2 + (fx64)a3  * b3) >> FX32_INT_SHIFT);
    a0 = a->_[4];
    a1 = a->_[5];
    a2 = a->_[6];
    a3 = a->_[7];
    dst->_[6] =  (fx32)(((fx64)a0  * b0 + (fx64)a1  * b1 + (fx64)a2  * b2 + (fx64)a3  * b3) >> FX32_INT_SHIFT);
    dst->_[5] =  (fx32)(((fx64)a0  * b->_[1] + (fx64)a1  * b->_[5] + (fx64)a2  * b->_[9]  + (fx64)a3  * b->_[13]) >> FX32_INT_SHIFT);
    dst->_[7] =  (fx32)(((fx64)a0  * b->_[3] + (fx64)a1  * b->_[7] + (fx64)a2  * b->_[11] + (fx64)a3  * b->_[15]) >> FX32_INT_SHIFT);
    b0 = b->_[0];
    b1 = b->_[4];
    b2 = b->_[8];
    b3 = b->_[12];
    dst->_[4] =  (fx32)(((fx64)a0  * b0 + (fx64)a1  * b1 + (fx64)a2  * b2  + (fx64)a3  * b3) >> FX32_INT_SHIFT);
    a0 = a->_[8];
    a1 = a->_[9];
    a2 = a->_[10];
    a3 = a->_[11];
    dst->_[8] =  (fx32)(((fx64)a0  * b0 + (fx64)a1  * b1 + (fx64)a2 * b2  + (fx64)a3 * b3) >> FX32_INT_SHIFT);
    dst->_[9] =  (fx32)(((fx64)a0  * b->_[1] + (fx64)a1  * b->_[5] + (fx64)a2 * b->_[9]  + (fx64)a3 * b->_[13]) >> FX32_INT_SHIFT);
    dst->_[11] = (fx32)(((fx64)a0  * b->_[3] + (fx64)a1  * b->_[7] + (fx64)a2 * b->_[11] + (fx64)a3 * b->_[15]) >> FX32_INT_SHIFT);
    b0 = b->_[2];
    b1 = b->_[6];
    b2 = b->_[10];
    b3 = b->_[14];
    dst->_[10] = (fx32)(((fx64)a0  * b0 + (fx64)a1  * b1 + (fx64)a2 * b2 + (fx64)a3 * b3) >> FX32_INT_SHIFT);
    a0 = a->_[12];
    a1 = a->_[13];
    a2 = a->_[14];
    a3 = a->_[15];
    dst->_[14] = (fx32)(((fx64)a0 * b0 + (fx64)a1 * b1 + (fx64)a2 * b2 + (fx64)a3 * b3) >> FX32_INT_SHIFT);
    dst->_[13] = (fx32)(((fx64)a0 * b->_[1] + (fx64)a1 * b->_[5] + (fx64)a2 * b->_[9]  + (fx64)a3 * b->_[13]) >> FX32_INT_SHIFT);
    dst->_[12] = (fx32)(((fx64)a0 * b->_[0] + (fx64)a1 * b->_[4] + (fx64)a2 * b->_[8]  + (fx64)a3 * b->_[12]) >> FX32_INT_SHIFT);
    dst->_[15] = (fx32)(((fx64)a0 * b->_[3] + (fx64)a1 * b->_[7] + (fx64)a2 * b->_[11] + (fx64)a3 * b->_[15]) >> FX32_INT_SHIFT);
    if (dst == &temp)
        *c = temp;
}

ARM_FUNC asm void MTX_Identity44_(struct Mtx44 *dst){
    mov r2, #0x1000
    mov r3, #0x0
    stmia r0!, {r2-r3}
    mov r1, #0x0
    stmia r0!, {r1,r3}
    stmia r0!, {r1-r3}
    stmia r0!, {r1,r3}
    stmia r0!, {r1-r3}
    stmia r0!, {r1,r3}
    stmia r0!, {r1-r2}
    bx lr
}

ARM_FUNC asm void MTX_Copy44To43_(struct Mtx44 *src, struct Mtx43 *dst){
    ldmia r0!, {r2-r3,r12}
    add r0, r0, #0x4
    stmia r1!, {r2-r3,r12}
    ldmia r0!, {r2-r3,r12}
    add r0, r0, #0x4
    stmia r1!, {r2-r3,r12}
    ldmia r0!, {r2-r3,r12}
    add r0, r0, #0x4
    stmia r1!, {r2-r3,r12}
    ldmia r0!, {r2-r3,r12}
    add r0, r0, #0x4
    stmia r1!, {r2-r3,r12}
    bx lr
}

THUMB_FUNC asm void MTX_RotX44_(struct Mtx44 *mtx, fx32 sinphi, fx32 cosphi){
    str r2, [r0, #0x14]
	str r2, [r0, #0x28]
	str r1, [r0, #0x18]
	neg r1, r1
	str r1, [r0, #0x24]
	mov r1, #0x1
	mov r2, #0x0
	lsl r1, r1, #0xc
	mov r3, #0x0
	stmia r0!, {r1-r3}
	stmia r0!, {r2-r3}
	add r0, #0x8
	stmia r0!, {r2-r3}
	add r0, #0x8
	stmia r0!, {r2-r3}
	stmia r0!, {r2-r3}
	str r1, [r0, #0x0]
	bx lr
}

THUMB_FUNC asm void MTX_RotY44_(struct Mtx44 *mtx, fx32 sinphi, fx32 cosphi){
    str r2, [r0, #0x0]
	str r2, [r0, #0x28]
	str r1, [r0, #0x20]
	neg r1, r1
	str r1, [r0, #0x8]
	mov r3, #0x1
	mov r1, #0x0
	lsl r3, r3, #0xc
	mov r2, #0x0
	str r2, [r0, #0x4]
	add r0, #0xc
	stmia r0!, {r1-r3}
	stmia r0!, {r1-r2}
	str r2, [r0, #0x4]
	add r0, #0xc
	stmia r0!, {r1-r2}
	stmia r0!, {r1-r3}
	bx lr
}

THUMB_FUNC asm void MTX_RotZ44_(struct Mtx44 *mtx, fx32 sinphi, fx32 cosphi){
    str r2, [r0, #0x0]
    str r2, [r0, #0x14]
    str r1, [r0, #0x4]
    neg r1, r1
    str r1, [r0, #0x10]
    mov r3, #0x1
    mov r1, #0x0
    lsl r3, r3, #0xc
    mov r2, #0x0
    add r0, #0x8
    stmia r0!, {r1-r2}
    add r0, #0x8
    stmia r0!, {r1-r2}
    stmia r0!, {r1-r3}
    stmia r0!, {r1-r2}
    stmia r0!, {r1-r3}
    bx lr
}
