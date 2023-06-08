#include "nitro/types.h"
#include "main.h"
#include "fx.h"
#include "code32.h"

void MTX_ScaleApply22(struct Mtx22 *mtx, struct Mtx22 *dst, fx32 x, fx32 y){
    dst->_[0] = (fx32)(((fx64)x * mtx->_[0]) >> FX32_INT_SHIFT);
    dst->_[1] = (fx32)(((fx64)x * mtx->_[1]) >> FX32_INT_SHIFT);
    dst->_[2] = (fx32)(((fx64)y * mtx->_[2]) >> FX32_INT_SHIFT);
    dst->_[3] = (fx32)(((fx64)y * mtx->_[3]) >> FX32_INT_SHIFT);
}

asm void MTX_Identity22_(struct Mtx22 *mtx){
    mov r1, #0x0
    mov r2, #0x1000
    mov r3, #0x0
    stmia r0!, {r2-r3}
    stmia r0!, {r1-r2}
    bx lr
}

#include "code16.h" //following func is thumb

asm void MTX_Rot22_(struct Mtx22 *mtx, fx32 sinphi, fx32 cosphi){
    str r2, [r0, #0x0]
	str r1, [r0, #0x4]
	neg r1, r1
	str r1, [r0, #0x8]
	str r2, [r0, #0xc]
	bx lr
}
