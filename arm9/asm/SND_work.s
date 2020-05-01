	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start SNDi_InitSharedWork
SNDi_InitSharedWork: ; 0x020CF590
	stmdb sp!, {r4,lr}
	mov r4, #0x0
	str r4, [r0, #0x4]
	strh r4, [r0, #0x8]
	strh r4, [r0, #0xa]
	mov r12, r0
	str r4, [r0, #0x0]
	mov r3, r4
	mvn r2, #0x0
_020CF5B4:
	mov lr, r3
	str r3, [r12, #0x40]
_020CF5BC:
	add r1, r12, lr, lsl #0x1
	add lr, lr, #0x1
	strh r2, [r1, #0x20]
	cmp lr, #0x10
	blt _020CF5BC
	add r4, r4, #0x1
	cmp r4, #0x10
	add r12, r12, #0x24
	blt _020CF5B4
	mov r3, #0x0
	mvn r2, #0x0
_020CF5E8:
	add r1, r0, r3, lsl #0x1
	add r1, r1, #0x200
	add r3, r3, #0x1
	strh r2, [r1, #0x60]
	cmp r3, #0x10
	blt _020CF5E8
	mov r1, #0x280
	bl DC_FlushRange
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SNDi_GetFinishedCommandTag
SNDi_GetFinishedCommandTag: ; 0x020CF610
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020CF640 ; =0x021D5360
	mov r1, #0x4
	ldr r0, [r0, #0x0]
	bl DC_InvalidateRange
	ldr r0, _020CF640 ; =0x021D5360
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CF640: .word 0x021D5360

	arm_func_start SND_GetPlayerTickCounter
SND_GetPlayerTickCounter: ; 0x020CF644
	stmdb sp!, {r4,lr}
	mov r1, #0x24
	mul r4, r0, r1
	ldr r0, _020CF680 ; =0x021D5360
	mov r1, #0x4
	ldr r0, [r0, #0x0]
	add r0, r0, #0x40
	add r0, r0, r4
	bl DC_InvalidateRange
	ldr r0, _020CF680 ; =0x021D5360
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	ldr r0, [r0, #0x40]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CF680: .word 0x021D5360

	arm_func_start SND_GetChannelStatus
SND_GetChannelStatus: ; 0x020CF684
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020CF6B8 ; =0x021D5360
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	add r0, r0, #0x8
	bl DC_InvalidateRange
	ldr r0, _020CF6B8 ; =0x021D5360
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x8]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CF6B8: .word 0x021D5360

	arm_func_start SND_GetPlayerStatus
SND_GetPlayerStatus: ; 0x020CF6BC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020CF6F0 ; =0x021D5360
	mov r1, #0x4
	ldr r0, [r0, #0x0]
	add r0, r0, #0x4
	bl DC_InvalidateRange
	ldr r0, _020CF6F0 ; =0x021D5360
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CF6F0: .word 0x021D5360
