    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_GetOwnerRtcOffset
OS_GetOwnerRtcOffset: ; 0x020CD510
	ldr r1, _020CD520 ; =0x027FFC80
	ldr r0, [r1, #0x68]
	ldr r1, [r1, #0x6c]
	bx lr
	.balign 4
_020CD520: .word 0x027FFC80

	arm_func_start OS_GetOwnerInfo
OS_GetOwnerInfo: ; 0x020CD524
	stmdb sp!, {r4,lr}
	ldr ip, _020CD59C ; =0x027FFC80
	mov r4, r0
	ldrh r2, [r12, #0x64]
	add r0, r12, #0x6
	add r1, r4, #0x4
	mov r2, r2, lsl #0x1d
	mov r2, r2, lsr #0x1d
	strb r2, [r4, #0x0]
	ldrb r3, [r12, #0x2]
	mov r2, #0x14
	mov r3, r3, lsl #0x1c
	mov r3, r3, lsr #0x1c
	strb r3, [r4, #0x1]
	ldrb r3, [r12, #0x3]
	strb r3, [r4, #0x2]
	ldrb r3, [r12, #0x4]
	strb r3, [r4, #0x3]
	ldrb r3, [r12, #0x1a]
	strh r3, [r4, #0x18]
	ldrb r3, [r12, #0x50]
	strh r3, [r4, #0x4e]
	bl MIi_CpuCopy16
	ldr r0, _020CD59C ; =0x027FFC80
	add r1, r4, #0x1a
	add r0, r0, #0x1c
	mov r2, #0x34
	bl MIi_CpuCopy16
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CD59C: .word 0x027FFC80

	arm_func_start OS_GetMacAddress
OS_GetMacAddress: ; 0x020CD5A0
	ldr ip, _020CD5B4 ; =MI_CpuCopy8
	mov r1, r0
	ldr r0, _020CD5B8 ; =0x027FFCF4
	mov r2, #0x6
	bx r12
	.balign 4
_020CD5B4: .word MI_CpuCopy8
_020CD5B8: .word 0x027FFCF4
