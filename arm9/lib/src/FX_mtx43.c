#include "global.h"
#include "main.h"
#include "fx.h"


ARM_FUNC void MTX_ScaleApply43(struct Mtx43 *mtx, struct Mtx43 *dst, fx32 x, fx32 y, fx32 z){
    //this works because matrices are indexed columns first
    MTX_ScaleApply33((struct Mtx33 *)mtx, (struct Mtx33 *)dst, x, y, z);
    dst->_[9] = mtx->_[9];
    dst->_[10] = mtx->_[10];
    dst->_[11] = mtx->_[11];
}

ARM_FUNC fx32 MTX_Inverse43(struct Mtx43 *mtx, struct Mtx43 *inv){
    struct Mtx43 tempmat;
    struct Mtx43 *dst;
    fx32 det0, det1, det2, det;
    fx32 var0, var1, var2, var3;
    if (mtx == inv)
        dst = &tempmat;
    else
        dst = inv;
    //subdeterminants
    det0 = ((fx64)mtx->_[4] * mtx->_[8] - (fx64)mtx->_[5] * mtx->_[7] + (fx64)(1 << (FX32_INT_SHIFT - 1))) >> FX32_INT_SHIFT;
    det1 = ((fx64)mtx->_[3] * mtx->_[8] - (fx64)mtx->_[5] * mtx->_[6] + (fx64)(1 << (FX32_INT_SHIFT - 1))) >> FX32_INT_SHIFT;
    det2 = ((fx64)mtx->_[3] * mtx->_[7] - (fx64)mtx->_[4] * mtx->_[6] + (fx64)(1 << (FX32_INT_SHIFT - 1))) >> FX32_INT_SHIFT;
    //matrix determinant
    det = ((fx64)mtx->_[0] * det0 - (fx64)mtx->_[1] * det1 + (fx64)mtx->_[2] * det2 + (fx64)(1 << (FX32_INT_SHIFT - 1))) >> FX32_INT_SHIFT;

    if (det == 0)
        return -1; //not invertible

    FX_InvAsync(det);

    var0 = ((fx64)mtx->_[1] * mtx->_[8] - (fx64)mtx->_[7] * mtx->_[2]) >> FX32_INT_SHIFT;
    var1 = ((fx64)mtx->_[1] * mtx->_[5] - (fx64)mtx->_[4] * mtx->_[2]) >> FX32_INT_SHIFT;
    var2 = ((fx64)mtx->_[0] * mtx->_[8] - (fx64)mtx->_[6] * mtx->_[2]) >> FX32_INT_SHIFT;
    var3 = ((fx64)mtx->_[0] * mtx->_[5] - (fx64)mtx->_[3] * mtx->_[2]) >> FX32_INT_SHIFT;

    fx32 ret = FX_GetDivResult();
    dst->_[0] =  (fx32)(((fx64)ret * det0) >> FX32_INT_SHIFT);
    dst->_[1] = -(fx32)(((fx64)ret * var0) >> FX32_INT_SHIFT);
    dst->_[2] =  (fx32)(((fx64)ret * var1) >> FX32_INT_SHIFT);
    dst->_[3] = -(fx32)(((fx64)ret * det1) >> FX32_INT_SHIFT);
    dst->_[4] =  (fx32)(((fx64)ret * var2) >> FX32_INT_SHIFT);
    dst->_[5] = -(fx32)(((fx64)ret * var3) >> FX32_INT_SHIFT);

    dst->_[6] = (fx32)(((fx64)ret * det2) >> FX32_INT_SHIFT);
    fx32 temp = (fx32)(((fx64)mtx->_[0] * mtx->_[7] - (fx64)mtx->_[6] * mtx->_[1]) >> FX32_INT_SHIFT);
    dst->_[7] = -(fx32)(((fx64)ret * temp) >> FX32_INT_SHIFT);
    fx32 temp1 = (fx32)(((fx64)mtx->_[0] * mtx->_[4] - (fx64)mtx->_[3] * mtx->_[1]) >> FX32_INT_SHIFT);
    dst->_[8] = (fx32)(((fx64)ret * temp1) >> FX32_INT_SHIFT);
    dst->_[9] =  -(fx32)(((fx64)dst->_[0] * mtx->_[9] + (fx64)dst->_[3] * mtx->_[10] + (fx64)dst->_[6] * mtx->_[11]) >> FX32_INT_SHIFT);
    dst->_[10] = -(fx32)(((fx64)dst->_[1] * mtx->_[9] + (fx64)dst->_[4] * mtx->_[10] + (fx64)dst->_[7] * mtx->_[11]) >> FX32_INT_SHIFT);
    dst->_[11] = -(fx32)(((fx64)dst->_[2] * mtx->_[9] + (fx64)dst->_[5] * mtx->_[10] + (fx64)dst->_[8] * mtx->_[11]) >> FX32_INT_SHIFT);

    if (dst == &tempmat)
        MI_Copy48B(&tempmat, inv);
    return 0;
}

ARM_FUNC void MTX_Concat43(struct Mtx43 *a, struct Mtx43 *b, struct Mtx43 *c){
    struct Mtx43 temp;
    struct Mtx43 *dst;
    fx32 a0, a1, a2;
    fx32 b0, b1, b2;

    if (c == b)
        dst = &temp;
    else
        dst = c;

    a0 = a->_[0];
    a1 = a->_[1];
    a2 = a->_[2];
    dst->_[0] =  (((fx64)a0  * b->_[0] + (fx64)a1  * b->_[3] + (fx64)a2  * b->_[6] ) >> FX32_INT_SHIFT);
    dst->_[1] =  (((fx64)a0  * b->_[1] + (fx64)a1  * b->_[4] + (fx64)a2  * b->_[7] ) >> FX32_INT_SHIFT);
    b0 = b->_[2];
    b1 = b->_[5];
    b2 = b->_[8];
    dst->_[2] =  (((fx64)a0  * b0 + (fx64)a1  * b1 + (fx64)a2  * b2) >> FX32_INT_SHIFT);
    a0 = a->_[3];
    a1 = a->_[4];
    a2 = a->_[5];
    dst->_[5] =  (((fx64)a0  * b0 + (fx64)a1  * b1 + (fx64)a2  * b2) >> FX32_INT_SHIFT);
    dst->_[4] =  (((fx64)a0  * b->_[1] + (fx64)a1  * b->_[4] + (fx64)a2  * b->_[7] ) >> FX32_INT_SHIFT);
    b0 = b->_[0];
    b1 = b->_[3];
    b2 = b->_[6];
    dst->_[3] =  (((fx64)a0  * b0 + (fx64)a1  * b1 + (fx64)a2  * b2) >> FX32_INT_SHIFT);
    a0 = a->_[6];
    a1 = a->_[7];
    a2 = a->_[8];
    dst->_[6] =  (((fx64)a0  * b0 + (fx64)a1  * b1 + (fx64)a2 * b2) >> FX32_INT_SHIFT);
    dst->_[7] =  (((fx64)a0  * b->_[1] + (fx64)a1  * b->_[4] + (fx64)a2 * b->_[7] ) >> FX32_INT_SHIFT);
    b0 = b->_[2];
    b1 = b->_[5];
    b2 = b->_[8];
    dst->_[8] = (((fx64)a0  * b0 + (fx64)a1  * b1 + (fx64)a2 * b2) >> FX32_INT_SHIFT);
    a0 = a->_[9];
    a1 = a->_[10];
    a2 = a->_[11];
    dst->_[11] = ((((fx64)a0 * b0 + (fx64)a1 * b1 + (fx64)a2 * b2) >> FX32_INT_SHIFT) + b->_[11]);
    dst->_[10] = ((((fx64)a0 * b->_[1] + (fx64)a1 * b->_[4] + (fx64)a2 * b->_[7]) >> FX32_INT_SHIFT) + b->_[10]);
    dst->_[9] = ((((fx64)a0 * b->_[0] + (fx64)a1 * b->_[3] + (fx64)a2 * b->_[6]) >> FX32_INT_SHIFT) + b->_[9]);
    if (dst == &temp)
        *c = temp;
}

ARM_FUNC void MTX_MultVec43(struct Vecx32 *vec, struct Mtx43 *mtx, struct Vecx32 *dst){
    fx32 x, y, z;
    x = vec->x;
    y = vec->y;
    z = vec->z;
    dst->x = ((fx64)x * mtx->_[0] + (fx64)y * mtx->_[3] + (fx64)z * mtx->_[6]) >> FX32_INT_SHIFT;
    dst->x += mtx->_[9];
    dst->y = ((fx64)x * mtx->_[1] + (fx64)y * mtx->_[4] + (fx64)z * mtx->_[7]) >> FX32_INT_SHIFT;
    dst->y += mtx->_[10];
    dst->z = ((fx64)x * mtx->_[2] + (fx64)y * mtx->_[5] + (fx64)z * mtx->_[8]) >> FX32_INT_SHIFT;
    dst->z += mtx->_[11];
}

ARM_FUNC asm void MTX_Identity43_(struct Mtx43 *mtx){
    mov r2, #0x1000
    mov r3, #0x0
    stmia r0!, {r2-r3}
    mov r1, #0x0
    stmia r0!, {r1,r3}
    stmia r0!, {r2-r3}
    stmia r0!, {r1,r3}
    stmia r0!, {r2-r3}
    stmia r0!, {r1,r3}
    bx lr
}

ARM_FUNC asm void MTX_Copy43To44_(struct Mtx43 *src, struct Mtx44 *dst){
    stmdb sp!, {r4}
    mov r12, #0x0
    ldmia r0!, {r2-r4}
    stmia r1!, {r2-r4,r12}
    ldmia r0!, {r2-r4}
    stmia r1!, {r2-r4,r12}
    ldmia r0!, {r2-r4}
    stmia r1!, {r2-r4,r12}
    mov r12, #0x1000
    ldmia r0!, {r2-r4}
    stmia r1!, {r2-r4,r12}
    ldmia sp!, {r4}
    bx lr
}

THUMB_FUNC asm void MTX_Scale43_(struct Mtx43 *dst, fx32 x, fx32 y, fx32 z){
    stmia r0!, {r1}
    mov r1, #0x0
    str r3, [r0, #0x1c]
    mov r3, #0x0
    stmia r0!, {r1,r3}
    stmia r0!, {r1-r3}
    mov r2, #0x0
    stmia r0!, {r1,r3}
    add r0, #0x4
    stmia r0!, {r1-r3}
    bx lr
}

THUMB_FUNC asm void MTX_RotX43_(struct Mtx43 *mtx, fx32 sinphi, fx32 cosphi){
    str r1, [r0, #0x14]
	neg r1, r1
	str r1, [r0, #0x1c]
	mov r1, #0x1
	lsl r1, r1, #0xc
	stmia r0!, {r1}
	mov r3, #0x0
	mov r1, #0x0
	stmia r0!, {r1,r3}
	stmia r0!, {r1-r2}
	str r1, [r0, #0x4]
	add r0, #0xc
	stmia r0!, {r2-r3}
	stmia r0!, {r1,r3}
	bx lr
}

THUMB_FUNC asm void MTX_RotY43_(struct Mtx43 *mtx, fx32 sinphi, fx32 cosphi){
    str r1, [r0, #0x18]
	mov r3, #0x0
	stmia r0!, {r2-r3}
	neg r1, r1
	stmia r0!, {r1,r3}
	mov r1, #0x1
	lsl r1, r1, #0xc
	stmia r0!, {r1,r3}
	add r0, #0x4
	mov r1, #0x0
	stmia r0!, {r1-r3}
	stmia r0!, {r1,r3}
	bx lr
}
