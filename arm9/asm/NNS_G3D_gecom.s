	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	; NNS_G3dGeBuffer
	.global UNK_021D1C80
UNK_021D1C80: ; 0x021D1C80
	.space 0x4

	; NNS_G3dFlagGXDmaAsync
	.global UNK_021D1C84
UNK_021D1C84: ; 0x021D1C84
	.space 0x4

	; NNS_G3dFlagUseFastDma
	.global UNK_021D1C88
UNK_021D1C88: ; 0x021D1C88
	.space 0x4

	.section .text

	; NNS_G3dGeBufferOP_N
	arm_func_start FUN_020BB1C0
FUN_020BB1C0: ; 0x020BB1C0
	stmdb sp!, {r4-r6,lr}
	ldr r3, _020BB2A4 ; =UNK_021D1C80
	mov r6, r0
	ldr r12, [r3, #0x0]
	mov r5, r1
	mov r4, r2
	cmp r12, #0x0
	beq _020BB278
	ldr r0, _020BB2A8 ; =UNK_021D1C84
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020BB24C
	ldr r2, [r12, #0x0]
	add r0, r2, #0x1
	add r1, r0, r4
	cmp r1, #0xc0
	bhi _020BB24C
	str r0, [r12, #0x0]
	ldr r0, [r3, #0x0]
	cmp r4, #0x0
	add r0, r0, r2, lsl #0x2
	str r6, [r0, #0x4]
	ldmeqia sp!, {r4-r6,pc}
	ldr r2, [r3, #0x0]
	mov r0, r5
	ldr r1, [r2], #0x4
	add r1, r2, r1, lsl #0x2
	mov r2, r4, lsl #0x2
	bl MIi_CpuCopyFast
	ldr r0, _020BB2A4 ; =UNK_021D1C80
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x0]
	add r0, r0, r4
	str r0, [r1, #0x0]
	ldmia sp!, {r4-r6,pc}
_020BB24C:
	ldr r0, [r12, #0x0]
	cmp r0, #0x0
	beq _020BB260
	bl FUN_020BB394
	b _020BB28C
_020BB260:
	ldr r0, _020BB2A8 ; =UNK_021D1C84
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020BB28C
	bl FUN_020BB37C
	b _020BB28C
_020BB278:
	ldr r0, _020BB2A8 ; =UNK_021D1C84
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020BB28C
	bl FUN_020BB37C
_020BB28C:
	ldr r1, _020BB2AC ; =0x04000400
	mov r0, r5
	mov r2, r4, lsl #0x2
	str r6, [r1, #0x0]
	bl MIi_CpuSend32
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020BB2A4: .word UNK_021D1C80
_020BB2A8: .word UNK_021D1C84
_020BB2AC: .word 0x04000400
	arm_func_end FUN_020BB1C0

	; NNS_G3dGeSendDL
	arm_func_start FUN_020BB2B0
FUN_020BB2B0: ; 0x020BB2B0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r5, r0
	cmp r4, #0x100
	blo _020BB2DC
	ldr r1, _020BB360 ; =GXi_DmaId
	mvn r0, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, r0
	bne _020BB2F8
_020BB2DC:
	mov r2, r4, lsr #0x2
	ldr r0, [r5, #0x0]
	add r1, r5, #0x4
	sub r2, r2, #0x1
	bl FUN_020BB1C0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020BB2F8:
	bl FUN_020BB394
	ldr r0, _020BB364 ; =UNK_021D1C88
	ldr r1, _020BB368 ; =UNK_021D1C84
	ldr r0, [r0, #0x0]
	mov r2, #0x1
	str r2, [r1, #0x0]
	cmp r0, #0x0
	beq _020BB33C
	ldr r0, _020BB360 ; =GXi_DmaId
	str r1, [sp, #0x0]
	ldr r0, [r0, #0x0]
	ldr r3, _020BB36C ; =FUN_020BB370
	mov r1, r5
	mov r2, r4
	bl MI_SendGXCommandAsyncFast
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020BB33C:
	ldr r0, _020BB360 ; =GXi_DmaId
	str r1, [sp, #0x0]
	ldr r0, [r0, #0x0]
	ldr r3, _020BB36C ; =FUN_020BB370
	mov r1, r5
	mov r2, r4
	bl MI_SendGXCommandAsync
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020BB360: .word GXi_DmaId
_020BB364: .word UNK_021D1C88
_020BB368: .word UNK_021D1C84
_020BB36C: .word FUN_020BB370
	arm_func_end FUN_020BB2B0

	; _end
	arm_func_start FUN_020BB370
FUN_020BB370: ; 0x020BB370
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	arm_func_end FUN_020BB370

	; NNS_G3dGeWaitSendDL
	arm_func_start FUN_020BB37C
FUN_020BB37C: ; 0x020BB37C
	ldr r0, _020BB390 ; =UNK_021D1C84
_020BB380:
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	bne _020BB380
	bx lr
	.balign 4
_020BB390: .word UNK_021D1C84
	arm_func_end FUN_020BB37C

	; NNS_G3dGeFlushBuffer
	arm_func_start FUN_020BB394
FUN_020BB394: ; 0x020BB394
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020BB3FC ; =UNK_021D1C84
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020BB3B0
	bl FUN_020BB37C
_020BB3B0:
	ldr r0, _020BB400 ; =UNK_021D1C80
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r1, _020BB404 ; =0x04000400
	add r0, r0, #0x4
	mov r2, r2, lsl #0x2
	bl MIi_CpuSend32
	ldr r0, _020BB400 ; =UNK_021D1C80
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020BB3FC: .word UNK_021D1C84
_020BB400: .word UNK_021D1C80
_020BB404: .word 0x04000400
	arm_func_end FUN_020BB394

