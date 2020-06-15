	.include "asm/macros.inc"
	.include "global.inc"
	.include "constants/species.h"

	.extern sLegendaryMonsList

	.text

	thumb_func_start FUN_0206A9AC
FUN_0206A9AC: ; 0x0206A9AC
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r6, r2, #0x0
	bl FUN_020239BC
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl GetBoxMonData
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl FUN_020239CC
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x9c
	mov r2, #0x0
	bl GetBoxMonData
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_020239A0
	add r7, r0, #0x0
	mov r0, #0x8
	add r1, r6, #0x0
	bl FUN_020219F4
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x90
	add r2, r6, #0x0
	mov r4, #0x0
	bl GetBoxMonData
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	cmp r1, r0
	bne _0206AA1C
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	cmp r1, r0
	bne _0206AA1C
	add r0, r7, #0x0
	add r1, r6, #0x0
	bl FUN_02021CE0
	cmp r0, #0x0
	bne _0206AA1C
	mov r4, #0x1
_0206AA1C:
	add r0, r6, #0x0
	bl FUN_02021A20
	add r0, r7, #0x0
	bl FUN_02021A20
	add r0, r4, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0206AA30
FUN_0206AA30: ; 0x0206AA30
	push {r3, lr}
	cmp r0, #0x3f
	bgt _0206AA48
	bge _0206AA6C
	cmp r0, #0x1
	bgt _0206AA74
	cmp r0, #0x0
	blt _0206AA74
	beq _0206AA82
	cmp r0, #0x1
	beq _0206AA82
	b _0206AA74
_0206AA48:
	cmp r0, #0x5a
	bgt _0206AA50
	beq _0206AA70
	b _0206AA74
_0206AA50:
	add r1, r0, #0x0
	sub r1, #0x5b
	cmp r1, #0x3
	bhi _0206AA74
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0206AA64: ; jump table (using 16-bit offset)
	.short _0206AA70 - _0206AA64 - 2; case 0
	.short _0206AA70 - _0206AA64 - 2; case 1
	.short _0206AA70 - _0206AA64 - 2; case 2
	.short _0206AA70 - _0206AA64 - 2; case 3
_0206AA6C:
	mov r0, #0x2
	pop {r3, pc}
_0206AA70:
	sub r0, #0x57
	pop {r3, pc}
_0206AA74:
	bl FUN_0206AE00
	cmp r0, #0x1
	bne _0206AA80
	mov r0, #0x1
	pop {r3, pc}
_0206AA80:
	mov r0, #0x0
_0206AA82:
	pop {r3, pc}

	thumb_func_start FUN_0206AA84
FUN_0206AA84: ; 0x0206AA84
	push {r3-r4, lr}
	sub sp, #0x1c
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, sp, #0x0
	strb r0, [r1, #0x0]
	add r1, sp, #0x0
	add r1, #0x1
	mov r2, #0x18
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	mov r1, #0xa1
	add r2, sp, #0x0
	bl SetMonData
	add r2, sp, #0x0
	add r0, r4, #0x0
	mov r1, #0xaa
	add r2, #0x1
	bl SetMonData
	add sp, #0x1c
	pop {r3-r4, pc}

	thumb_func_start FUN_0206AAB4
FUN_0206AAB4: ; 0x0206AAB4
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl AcquireBoxMonLock
	mov r4, #0x0
	str r0, [sp, #0x0]
	add r7, r4, #0x0
	add r6, sp, #0x4
_0206AAC6:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x36
	add r2, r7, #0x0
	bl GetBoxMonData
	cmp r0, #0x0
	beq _0206AAF0
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x42
	mov r2, #0x0
	bl GetBoxMonData
	add r1, r4, #0x0
	strb r0, [r6, #0x0]
	add r0, r5, #0x0
	add r1, #0x3a
	add r2, sp, #0x4
	bl SetBoxMonData
_0206AAF0:
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _0206AAC6
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	bl ReleaseBoxMonLock
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
