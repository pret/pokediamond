	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start MATH_CountPopulation
MATH_CountPopulation: ; 0x020DDC5C
	ldr r1, _020DDC94 ; =0x55555555
	ldr r2, _020DDC98 ; =0x33333333
	and r1, r1, r0, lsr #0x1
	sub r0, r0, r1
	and r1, r0, r2
	and r0, r2, r0, lsr #0x2
	add r1, r1, r0
	ldr r0, _020DDC9C ; =0x0F0F0F0F
	add r1, r1, r1, lsr #0x4
	and r0, r1, r0
	add r0, r0, r0, lsr #0x8
	add r0, r0, r0, lsr #0x10
	and r0, r0, #0xff
	bx lr
	.balign 4
_020DDC94: .word 0x55555555
_020DDC98: .word 0x33333333
_020DDC9C: .word 0x0F0F0F0F

	arm_func_start MATH_CalcSHA1
MATH_CalcSHA1: ; 0x020DDCA0
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x68
	mov r6, r0
	add r0, sp, #0x0
	mov r5, r1
	mov r4, r2
	bl MATH_SHA1Init
_020DDCBC: ; 0x020DDCBC
	add r0, sp, #0x0
	mov r1, r5
	mov r2, r4
	bl MATH_SHA1Update
_020DDCCC: ; 0x020DDCCC
	add r0, sp, #0x0
	mov r1, r6
	bl MATH_SHA1GetHash
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

	arm_func_start MATH_CalcCRC32
MATH_CalcCRC32: ; 0x020DDD28
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mvn r12, #0x0
	mov r3, r2
	add r1, sp, #0x0
	mov r2, lr
	str r12, [sp, #0x0]
	bl MATHi_CRC32UpdateRev
_020DDD4C: ; 0x020DDD4C
	ldr r0, [sp, #0x0]
	mvn r0, r0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start MATH_CalcCRC16CCITT
MATH_CalcCRC16CCITT: ; 0x020DDD60
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr ip, _020DDD94 ; =0x0000FFFF
	mov lr, r1
	mov r3, r2
	add r1, sp, #0x0
	mov r2, lr
	strh r12, [sp, #0x0]
	bl MATHi_CRC16Update
	ldrh r0, [sp, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DDD94: .word 0x0000FFFF

	arm_func_start MATH_CalcCRC16
MATH_CalcCRC16: ; 0x020DDD98
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r12, #0x0
	mov r3, r2
	add r1, sp, #0x0
	mov r2, lr
	strh r12, [sp, #0x0]
	bl MATHi_CRC16UpdateRev
	ldrh r0, [sp, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start MATH_CalcCRC8
MATH_CalcCRC8: ; 0x020DDDCC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r12, #0x0
	mov r3, r2
	add r1, sp, #0x0
	mov r2, lr
	strb r12, [sp, #0x0]
	bl MATHi_CRC8Update
_020DDDF0: ; 0x020DDDF0
	ldrb r0, [sp, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start MATHi_CRC32UpdateRev
MATHi_CRC32UpdateRev:
	stmdb sp!, {r4,lr}
	cmp r3, #0x0
	ldr r4, [r1, #0x0]
	mov lr, #0x0
	bls _020DDE38
_020DDE14:
	ldrb r12, [r2, #0x0]
	add lr, lr, #0x1
	cmp lr, r3
	eor r12, r4, r12
	and r12, r12, #0xff
	ldr r12, [r0, r12, lsl #0x2]
	add r2, r2, #0x1
	eor r4, r12, r4, lsr #0x8
	blo _020DDE14
_020DDE38:
	str r4, [r1, #0x0]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start MATHi_CRC32InitTableRev
MATHi_CRC32InitTableRev: ; 0x020DDE44
	stmdb sp!, {r4,lr}
	mov lr, #0x0
	mov r3, lr
_020DDE50:
	mov r4, lr
	mov r12, r3
_020DDE58:
	ands r2, r4, #0x1
	eorne r4, r1, r4, lsr #0x1
	add r12, r12, #0x1
	moveq r4, r4, lsr #0x1
	cmp r12, #0x8
	blo _020DDE58
	str r4, [r0, lr, lsl #0x2]
	add lr, lr, #0x1
	cmp lr, #0x100
	blo _020DDE50
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start MATHi_CRC16UpdateRev
MATHi_CRC16UpdateRev: ; 0x020DDE88
	stmdb sp!, {r4,lr}
	cmp r3, #0x0
	ldrh r4, [r1, #0x0]
	mov lr, #0x0
	bls _020DDEC4
_020DDE9C:
	ldrb r12, [r2, #0x0]
	add lr, lr, #0x1
	cmp lr, r3
	eor r12, r4, r12
	and r12, r12, #0xff
	mov r12, r12, lsl #0x1
	ldrh r12, [r0, r12]
	add r2, r2, #0x1
	eor r4, r12, r4, lsr #0x8
	blo _020DDE9C
_020DDEC4:
	strh r4, [r1, #0x0]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start MATHi_CRC16Update
MATHi_CRC16Update: ; 0x020DDED0
	stmdb sp!, {r4,lr}
	cmp r3, #0x0
	ldrh r4, [r1, #0x0]
	mov lr, #0x0
	bls _020DDF0C
_020DDEE4:
	ldrb r12, [r2, #0x0]
	add lr, lr, #0x1
	cmp lr, r3
	eor r12, r12, r4, lsr #0x8
	and r12, r12, #0xff
	mov r12, r12, lsl #0x1
	ldrh r12, [r0, r12]
	add r2, r2, #0x1
	eor r4, r12, r4, lsl #0x8
	blo _020DDEE4
_020DDF0C:
	strh r4, [r1, #0x0]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start MATHi_CRC16InitTableRev
MATHi_CRC16InitTableRev: ; 0x020DDF18
	stmdb sp!, {r4,lr}
	mov lr, #0x0
	mov r3, lr
_020DDF24:
	mov r4, lr
	mov r12, r3
_020DDF2C:
	ands r2, r4, #0x1
	eorne r4, r1, r4, lsr #0x1
	add r12, r12, #0x1
	moveq r4, r4, lsr #0x1
	cmp r12, #0x8
	blo _020DDF2C
	mov r2, lr, lsl #0x1
	add lr, lr, #0x1
	strh r4, [r0, r2]
	cmp lr, #0x100
	blo _020DDF24
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start MATHi_CRC16InitTable
MATHi_CRC16InitTable: ; 0x020DDF60
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, #0x0
	mov r12, r4
	mov r3, r4
_020DDF74:
	mov r5, r12
	mov lr, r3
_020DDF7C:
	ands r2, r5, #0x8000
	eorne r5, r1, r5, lsl #0x1
	add lr, lr, #0x1
	moveq r5, r5, lsl #0x1
	cmp lr, #0x8
	blo _020DDF7C
	mov r2, r4, lsl #0x1
	add r4, r4, #0x1
	strh r5, [r0, r2]
	cmp r4, #0x100
	add r12, r12, #0x100
	blo _020DDF74
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start MATHi_CRC8Update
MATHi_CRC8Update:
	stmdb sp!, {r4,lr}
	cmp r3, #0x0
	ldrb r4, [r1, #0x0]
	mov lr, #0x0
	bls _020DDFEC
_020DDFCC:
	ldrb r12, [r2, #0x0]
	add lr, lr, #0x1
	cmp lr, r3
	eor r12, r4, r12
	and r12, r12, #0xff
	add r2, r2, #0x1
	ldrb r4, [r0, r12]
	blo _020DDFCC
_020DDFEC:
	strb r4, [r1, #0x0]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start MATHi_CRC8InitTable
MATHi_CRC8InitTable: ; 0x020DDFF8
	stmdb sp!, {r4,lr}
	mov lr, #0x0
	mov r3, lr
_020DE004:
	mov r4, lr
	mov r12, r3
_020DE00C:
	ands r2, r4, #0x80
	eorne r4, r1, r4, lsl #0x1
	add r12, r12, #0x1
	moveq r4, r4, lsl #0x1
	cmp r12, #0x8
	blo _020DE00C
	strb r4, [r0, lr]
	add lr, lr, #0x1
	cmp lr, #0x100
	blo _020DE004
	ldmia sp!, {r4,lr}
	bx lr
