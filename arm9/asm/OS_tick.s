    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_GetTickLo
OS_GetTickLo: ; 0x020CCC0C
	ldr r0, _020CCC18 ; =0x04000100
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4
_020CCC18: .word 0x04000100

	arm_func_start OS_GetTick
OS_GetTick: ; 0x020CCC1C
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	bl OS_DisableInterrupts
	ldr r1, _020CCCBC ; =0x04000100
	ldr r3, _020CCCC0 ; =OSi_TickCounter
	ldrh r12, [r1, #0x0]
	ldr r2, _020CCCC4 ; =0x0000FFFF
	mvn r1, #0x0
	strh r12, [sp, #0x0]
	ldr r12, [r3, #0x0]
	ldr r3, [r3, #0x4]
	and r1, r12, r1
	and r2, r3, r2
	str r1, [sp, #0x4]
	ldr r1, _020CCCC8 ; =0x04000214
	str r2, [sp, #0x8]
	ldr r1, [r1, #0x0]
	ands r1, r1, #0x8
	beq _020CCC90
	ldrh r1, [sp, #0x0]
	ands r1, r1, #0x8000
	bne _020CCC90
	ldr r3, [sp, #0x4]
	mov r1, #0x1
	ldr r2, [sp, #0x8]
	adds r3, r3, r1
	adc r1, r2, #0x0
	str r3, [sp, #0x4]
	str r1, [sp, #0x8]
_020CCC90:
	bl OS_RestoreInterrupts
	ldr r2, [sp, #0x4]
	ldr r1, [sp, #0x8]
	ldrh r0, [sp, #0x0]
	mov r1, r1, lsl #0x10
	orr r1, r1, r2, lsr #0x10
	orr r1, r1, r0, asr #0x1f
	orr r0, r0, r2, lsl #0x10
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CCCBC: .word 0x04000100
_020CCCC0: .word OSi_TickCounter
_020CCCC4: .word 0x0000FFFF
_020CCCC8: .word 0x04000214

	arm_func_start OSi_CountUpTick
OSi_CountUpTick: ; 0x020CCCCC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020CCD40 ; =OSi_TickCounter
	ldr r1, _020CCD44 ; =OSi_NeedResetTimer
	ldr r12, [r2, #0x0]
	mov r0, #0x1
	ldr r3, [r2, #0x4]
	adds r12, r12, r0
	ldr r0, [r1, #0x0]
	adc r3, r3, #0x0
	str r12, [r2, #0x0]
	str r3, [r2, #0x4]
	cmp r0, #0x0
	mov r3, #0x0
	beq _020CCD24
	ldr r2, _020CCD48 ; =0x04000102
	ldr r0, _020CCD4C ; =0x04000100
	strh r3, [r2, #0x0]
	strh r3, [r0, #0x0]
	mov r0, #0xc1
	strh r0, [r2, #0x0]
	str r3, [r1, #0x0]
_020CCD24:
	mov r0, #0x0
	ldr r1, _020CCD50 ; =OSi_CountUpTick
	mov r2, r0
	bl OSi_EnterTimerCallback
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CCD40: .word OSi_TickCounter
_020CCD44: .word OSi_NeedResetTimer
_020CCD48: .word 0x04000102
_020CCD4C: .word 0x04000100
_020CCD50: .word OSi_CountUpTick

	arm_func_start OS_IsTickAvailable
OS_IsTickAvailable: ; 0x020CCD54
	ldr r0, _020CCD60 ; =OSi_UseTick
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4
_020CCD60: .word OSi_UseTick

	arm_func_start OS_InitTick
OS_InitTick: ; 0x020CCD64
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020CCDE8 ; =OSi_UseTick
	ldrh r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	mov r2, #0x1
	mov r0, #0x0
	strh r2, [r1, #0x0]
	bl OSi_SetTimerReserved
	ldr r0, _020CCDEC ; =OSi_TickCounter
	mov r2, #0x0
	str r2, [r0, #0x0]
	ldr r3, _020CCDF0 ; =0x04000102
	str r2, [r0, #0x4]
	ldr r0, _020CCDF4 ; =0x04000100
	strh r2, [r3, #0x0]
	ldr r1, _020CCDF8 ; =OSi_CountUpTick
	strh r2, [r0, #0x0]
	mov r2, #0xc1
	mov r0, #0x8
	strh r2, [r3, #0x0]
	bl OS_SetIrqFunction
	mov r0, #0x8
	bl OS_EnableIrqMask
	ldr r0, _020CCDFC ; =OSi_NeedResetTimer
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CCDE8: .word OSi_UseTick
_020CCDEC: .word OSi_TickCounter
_020CCDF0: .word 0x04000102
_020CCDF4: .word 0x04000100
_020CCDF8: .word OSi_CountUpTick
_020CCDFC: .word OSi_NeedResetTimer
