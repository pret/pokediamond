	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start FUN_0204A368
FUN_0204A368: ; 0x0204A368
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x54]
	add r4, r1, #0x0
	cmp r0, #0x0
	bne _0204A388
	ldr r1, _0204A38C ; =0x000080E2
	mov r0, #0xb
	bl AllocFromHeap
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x54]
	add r2, r4, #0x0
	bl FUN_0204A3B0
_0204A388:
	pop {r3-r5, pc}
	nop
_0204A38C: .word 0x000080E2

	thumb_func_start FUN_0204A390
FUN_0204A390: ; 0x0204A390
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x54]
	cmp r0, #0x0
	beq _0204A3A2
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x54]
_0204A3A2:
	pop {r4, pc}

	thumb_func_start FUN_0204A3A4
FUN_0204A3A4: ; 0x0204A3A4
	ldrb r0, [r1, r0]
	add r2, r1, #0x0
	add r2, #0xe2
	lsl r0, r0, #0xb
	add r0, r2, r0
	bx lr

	thumb_func_start FUN_0204A3B0
FUN_0204A3B0: ; 0x0204A3B0
	push {r4-r7, lr}
	sub sp, #0x3c
	str r1, [sp, #0x8]
	str r2, [sp, #0xc]
	str r0, [sp, #0x4]
	mov r2, #0x0
	add r1, sp, #0x18
	strb r2, [r1, #0x0]
	bl MapMatrix_GetWidth
	add r6, r0, #0x0
	ldr r0, [sp, #0x4]
	bl MapMatrix_GetHeight
	str r0, [sp, #0x10]
	mov r0, #0x0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	ble _0204A410
	ldr r7, [sp, #0x14]
_0204A3DA:
	mov r5, #0x0
	cmp r6, #0x0
	ble _0204A402
_0204A3E0:
	add r0, r5, r7
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r1, [sp, #0x4]
	add r0, r4, #0x0
	bl MapMatrix_GetMapData
	add r1, sp, #0x18
	add r1, #0x2
	add r2, sp, #0x18
	bl FUN_0204A45C
	ldr r1, [sp, #0x8]
	add r5, r5, #0x1
	strb r0, [r1, r4]
	cmp r5, r6
	blt _0204A3E0
_0204A402:
	ldr r0, [sp, #0x14]
	add r7, r7, r6
	add r1, r0, #0x1
	ldr r0, [sp, #0x10]
	str r1, [sp, #0x14]
	cmp r1, r0
	blt _0204A3DA
_0204A410:
	mov r0, #0x43
	mov r1, #0xb
	bl NARC_New
	add r7, r0, #0x0
	ldr r0, [sp, #0xc]
	mov r6, #0x0
	cmp r0, #0x0
	ble _0204A452
	ldr r0, [sp, #0x8]
	add r4, sp, #0x18
	add r0, #0xe2
	add r4, #0x2
	add r5, r6, #0x0
	str r0, [sp, #0x8]
_0204A42E:
	ldr r0, [sp, #0x8]
	lsl r1, r5, #0x1
	add r0, r0, r1
	str r0, [sp, #0x0]
	ldrh r1, [r4, #0x0]
	mov r2, #0x10
	add r0, r7, #0x0
	lsl r3, r2, #0x7
	bl NARC_ReadFromMember
	mov r0, #0x1
	lsl r0, r0, #0xa
	add r5, r5, r0
	ldr r0, [sp, #0xc]
	add r6, r6, #0x1
	add r4, r4, #0x2
	cmp r6, r0
	blt _0204A42E
_0204A452:
	add r0, r7, #0x0
	bl NARC_Delete
	add sp, #0x3c
	pop {r4-r7, pc}

	thumb_func_start FUN_0204A45C
FUN_0204A45C: ; 0x0204A45C
	push {r3-r7, lr}
	add r7, r2, #0x0
	add r5, r0, #0x0
	ldrb r0, [r7, #0x0]
	add r6, r1, #0x0
	mov r4, #0x0
	cmp r0, #0x0
	bls _0204A482
_0204A46C:
	lsl r1, r4, #0x1
	ldrh r1, [r6, r1]
	cmp r5, r1
	bne _0204A478
	add r0, r4, #0x0
	pop {r3-r7, pc}
_0204A478:
	add r1, r4, #0x1
	lsl r1, r1, #0x18
	lsr r4, r1, #0x18
	cmp r4, r0
	blo _0204A46C
_0204A482:
	cmp r4, #0x10
	blo _0204A48A
	bl GF_AssertFail
_0204A48A:
	lsl r0, r4, #0x1
	strh r5, [r6, r0]
	ldrb r0, [r7, #0x0]
	add r0, r0, #0x1
	strb r0, [r7, #0x0]
	add r0, r4, #0x0
	pop {r3-r7, pc}
