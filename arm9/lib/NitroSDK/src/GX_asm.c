#include "nitro/types.h"
#include "main.h"
#include "gx.h"
#include "code32.h"

//looks like asm and says asm on the tin...
asm void GX_SendFifo48B(void *src, void *dst) {
    ldmia r0!, {r2-r3,r12}
    stmia r1, {r2-r3,r12}
    ldmia r0!, {r2-r3,r12}
    stmia r1, {r2-r3,r12}
    ldmia r0!, {r2-r3,r12}
    stmia r1, {r2-r3,r12}
    ldmia r0!, {r2-r3,r12}
    stmia r1, {r2-r3,r12}
    bx lr
}
