#include "global.h"
#include "MI_memory.h"


extern void FUN_020250A4(void *param0);
extern void FUN_02025484(void* param0);

THUMB_FUNC u32 FUN_02024E64() {
    return 0x0000074C;
}


// 	thumb_func_start FUN_02024E6C
// FUN_02024E6C: ; 0x02024E6C
// 	push {r4, lr}
// 	add r4, r0, #0x0
// 	ldr r2, _02024EA4 ; =0x0000074C
// 	mov r0, #0x0
// 	add r1, r4, #0x0
// 	bl MIi_CpuClearFast
// 	add r0, r4, #0x0
// 	bl FUN_020250A4
// 	mov r0, #0x7
// 	lsl r0, r0, #0x8
// 	add r0, r4, r0
// 	bl FUN_02025484
// 	ldr r1, _02024EA8 ; =0x00000724
// 	ldr r0, _02024EAC ; =0x0000FFFF
// 	add r1, r4, r1
// 	mov r2, #0x8
// 	bl MIi_CpuClear16
// 	ldr r1, _02024EB0 ; =0x00000734
// 	ldr r0, _02024EAC ; =0x0000FFFF
// 	add r1, r4, r1
// 	mov r2, #0xb
// 	bl MIi_CpuClear16
// 	pop {r4, pc}
// 	.balign 4
// _02024EA4: .word 0x0000074C
// _02024EA8: .word 0x00000724
// _02024EAC: .word 0x0000FFFF
// _02024EB0: .word 0x00000734
THUMB_FUNC void FUN_02024E6C(void* param0) {
    MIi_CpuClearFast(0, param0, 0x0000074C);

    FUN_020250A4(param0);

    FUN_02025484(param0+(7<<8));

    MIi_CpuClear16(0x0000FFFF, param0 + 0x00000724, 8);
    MIi_CpuClear16(0x0000FFFF, param0 + 0x00000734, 0xb);
}
