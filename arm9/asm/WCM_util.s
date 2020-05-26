	.include "asm/macros.inc"
	.include "global.inc"

	.bss

	.global wcmRssiIndex
wcmRssiIndex: ; 0x021CA89C
	.space 0x4

	.global wcmRssi
wcmRssi: ; 0x021CA8A0
	.space 0x10

	.text

	arm_func_start WCMi_ShelterRssi
WCMi_ShelterRssi: ; 0x020A89D0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020A8A48 ; =wcmRssiIndex
	ands r1, r0, #0x2
	ldrb r12, [r2, #0x0]
	movne r0, r0, asr #0x2
	andne lr, r0, #0xff
	moveq r0, r0, asr #0x2
	addeq r0, r0, #0x19
	andeq lr, r0, #0xff
	mov r1, r12, lsr #0x1f
	rsb r0, r1, r12, lsl #0x1c
	cmp r12, #0x10
	ldr r3, _020A8A4C ; =wcmRssi
	add r0, r1, r0, ror #0x1c
	strb lr, [r3, r0]
	addcc r0, r12, #0x1
	strccb r0, [r2, #0x0]
	addcc sp, sp, #0x4
	ldmccia sp!, {lr}
	bxcc lr
	add r0, r12, #0x1
	mov r1, r0, lsr #0x1f
	rsb r0, r1, r0, lsl #0x1c
	add r0, r1, r0, ror #0x1c
	add r0, r0, #0x10
	strb r0, [r2, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A8A48: .word wcmRssiIndex
_020A8A4C: .word wcmRssi

	arm_func_start WcmGetLinkLevel
WcmGetLinkLevel: ; 0x020A8A50
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl WCMi_GetRssiAverage
	mov r1, #0x0
	cmp r0, #0x1c
	movcs r1, #0x3
	bhs _020A8A80
	cmp r0, #0x16
	movcs r1, #0x2
	bhs _020A8A80
	cmp r0, #0x10
	movcs r1, #0x1
_020A8A80:
	mov r0, r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start WCMi_GetRssiAverage
WCMi_GetRssiAverage: ; 0x020A8A90
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020A8B20 ; =wcmRssiIndex
	mov r0, #0x0
	ldrb r1, [r1, #0x0]
	cmp r1, #0x10
	bls _020A8ADC
	ldr r2, _020A8B24 ; =wcmRssi
	mov r3, r0
_020A8AB4:
	ldrb r1, [r2, #0x0]
	add r3, r3, #0x1
	cmp r3, #0x10
	add r0, r0, r1
	add r2, r2, #0x1
	blt _020A8AB4
	mov r1, r0, asr #0x3
	add r0, r0, r1, lsr #0x1c
	mov r0, r0, asr #0x4
	b _020A8B10
_020A8ADC:
	cmp r1, #0x0
	beq _020A8B10
	mov r3, r0
	cmp r1, #0x0
	ble _020A8B0C
	ldr ip, _020A8B24 ; =wcmRssi
_020A8AF4:
	ldrb r2, [r12, #0x0]
	add r3, r3, #0x1
	cmp r3, r1
	add r0, r0, r2
	add r12, r12, #0x1
	blt _020A8AF4
_020A8B0C:
	bl _s32_div_f
_020A8B10:
	and r0, r0, #0xff
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A8B20: .word wcmRssiIndex
_020A8B24: .word wcmRssi

	arm_func_start WCM_GetLinkLevel
WCM_GetLinkLevel: ; 0x020A8B28
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	mov r5, r0
	bl WCMi_GetSystemWork
	cmp r0, #0x0
	mov r4, #0x0
	beq _020A8B60
	add r0, r0, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0x9
	bne _020A8B60
	bl WcmGetLinkLevel
	mov r4, r0
_020A8B60:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start WCM_CompareBssID
WCM_CompareBssID:
	mov r12, #0x0
_020A8B7C:
	ldrb r3, [r0, r12]
	ldrb r2, [r1, r12]
	cmp r3, r2
	movne r0, #0x0
	bxne lr
	add r12, r12, #0x1
	cmp r12, #0x6
	blt _020A8B7C
	mov r0, #0x1
	bx lr
