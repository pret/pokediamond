    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_GetLowEntropyData
OS_GetLowEntropyData: ; 0x020CD754
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r1, _020CD82C ; =0x04000006
	ldr r2, _020CD830 ; =0x027FFC00
	ldrh r7, [r1, #0x0]
	add r4, r2, #0x80
	mov r6, r0
	add r5, r4, #0x74
	bl OS_GetTickLo
	orr r0, r0, r7, lsl #0x10
	str r0, [r6, #0x0]
	ldr r1, _020CD834 ; =OSi_TickCounter
	ldr r0, _020CD830 ; =0x027FFC00
	ldr r3, [r1, #0x0]
	ldrh r5, [r5, #0x4]
	ldr r2, [r1, #0x4]
	ldr r2, _020CD838 ; =0x04000600
	eor r3, r3, r5, lsl #0x10
	str r3, [r6, #0x4]
	ldr r3, [r1, #0x0]
	ldr r3, [r1, #0x4]
	ldr r1, [r4, #0x74]
	ldr r4, [r0, #0x3c]
	eor r1, r3, r1
	eor r1, r4, r1
	str r1, [r6, #0x8]
	ldr r3, [r6, #0x8]
	ldr r2, [r2, #0x0]
	add r1, r0, #0x300
	eor r2, r3, r2
	str r2, [r6, #0x8]
	ldr r2, [r0, #0x1e8]
	ldr r3, _020CD83C ; =0x04000130
	str r2, [r6, #0xc]
	ldr r4, [r0, #0x1ec]
	ldr r2, _020CD840 ; =0x027FFFA8
	str r4, [r6, #0x10]
	ldrh r4, [r1, #0x94]
	ldr r0, [r0, #0x390]
	eor r0, r0, r4, lsl #0x10
	str r0, [r6, #0x14]
	ldrh r4, [r1, #0xaa]
	ldrh r0, [r1, #0xac]
	orr r0, r0, r4, lsl #0x10
	str r0, [r6, #0x18]
	ldrh r3, [r3, #0x0]
	ldrh r0, [r2, #0x0]
	ldrh r1, [r1, #0x98]
	orr r0, r3, r0
	orr r0, r0, r1, lsl #0x10
	str r0, [r6, #0x1c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020CD82C: .word 0x04000006
_020CD830: .word 0x027FFC00
_020CD834: .word OSi_TickCounter
_020CD838: .word 0x04000600
_020CD83C: .word 0x04000130
_020CD840: .word 0x027FFFA8
