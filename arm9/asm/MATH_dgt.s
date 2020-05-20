	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start MATH_CalcSHA1
MATH_CalcSHA1: ; 0x020DDCA0
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x68
	mov r6, r0
	add r0, sp, #0x0
	mov r5, r1
	mov r4, r2
	bl DGT_Hash2Reset
_020DDCBC: ; 0x020DDCBC
	add r0, sp, #0x0
	mov r1, r5
	mov r2, r4
	bl DGT_Hash2SetSource
_020DDCCC: ; 0x020DDCCC
	add r0, sp, #0x0
	mov r1, r6
	bl DGT_Hash2GetDigest
	add sp, sp, #0x68
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start MATH_CalcMD5
MATH_CalcMD5: ; 0x020DDCE4
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x58
	mov r6, r0
	add r0, sp, #0x0
	mov r5, r1
	mov r4, r2
	bl DGT_Hash1Reset
_020DDD00: ; 0x020DDD00
	add r0, sp, #0x0
	mov r1, r5
	mov r2, r4
	bl DGT_Hash1SetSource
	add r1, sp, #0x0
	mov r0, r6
	bl DGT_Hash1GetDigest_R
	add sp, sp, #0x58
	ldmia sp!, {r4-r6,lr}
	bx lr
