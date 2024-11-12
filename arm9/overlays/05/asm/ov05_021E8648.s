	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021E8648
ov05_021E8648: ; 0x021E8648
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _021E8690 ; =ov05_021E8728
	ldr r3, [r5, #0x28]
	mov r1, #0x38
	mov r2, #5
	bl sub_020061E8
	add r6, r0, #0
	bl sub_0201B6C8
	add r4, r0, #0
	add r2, r4, #4
	mov r3, #5
_021E8664:
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	sub r3, r3, #1
	bne _021E8664
	ldr r0, [r5]
	str r0, [r2]
	str r6, [r4, #0x34]
	mov r0, #0
	str r0, [r4, #0x30]
	bl GX_GetBankForLCDC
	str r0, [r4]
	add r0, r4, #4
	bl ov05_021E87C8
	ldr r0, _021E8694 ; =ov05_021E8768
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA98
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021E8690: .word ov05_021E8728
_021E8694: .word ov05_021E8768

	thumb_func_start ov05_021E8698
ov05_021E8698: ; 0x021E8698
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	add r1, r2, #0
	add r2, r3, #0
	bl GX_SetGraphicsMode
	ldr r0, [r4]
	ldr r0, [r0]
	bl GX_SetBankForLCDC
	ldr r0, [r4]
	ldr r0, [r0, #4]
	cmp r0, #0xa
	bgt _021E86C8
	bge _021E86EC
	cmp r0, #6
	bgt _021E8708
	cmp r0, #2
	blt _021E8708
	beq _021E86CE
	cmp r0, #6
	beq _021E86DE
	b _021E8708
_021E86C8:
	cmp r0, #0xe
	beq _021E86FA
	b _021E8708
_021E86CE:
	mov r1, #0x1a
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x16
	lsl r2, r2, #0x10
	bl MIi_CpuClearFast
	b _021E870E
_021E86DE:
	mov r2, #2
	ldr r1, _021E871C ; =0x06820000
	mov r0, #0
	lsl r2, r2, #0x10
	bl MIi_CpuClearFast
	b _021E870E
_021E86EC:
	mov r2, #2
	ldr r1, _021E8720 ; =0x06840000
	mov r0, #0
	lsl r2, r2, #0x10
	bl MIi_CpuClearFast
	b _021E870E
_021E86FA:
	mov r2, #2
	ldr r1, _021E8724 ; =0x06860000
	mov r0, #0
	lsl r2, r2, #0x10
	bl MIi_CpuClearFast
	b _021E870E
_021E8708:
	mov r0, #0
	bl GX_SetBankForLCDC
_021E870E:
	ldr r0, [r4]
	ldr r0, [r0, #0x34]
	bl sub_0200621C
	mov r0, #0
	str r0, [r4]
	pop {r4, pc}
	.balign 4, 0
_021E871C: .word 0x06820000
_021E8720: .word 0x06840000
_021E8724: .word 0x06860000

	thumb_func_start ov05_021E8728
ov05_021E8728: ; 0x021E8728
	push {r4, r5, r6, r7}
	ldr r0, [r1, #0x30]
	cmp r0, #0
	beq _021E8760
	ldr r6, [r1, #0x20]
	ldr r5, [r1, #0x10]
	ldr r4, [r1, #0x1c]
	ldr r3, [r1, #0x18]
	ldr r2, [r1, #0x14]
	ldr r0, [r1, #0x24]
	ldr r1, [r1, #0x28]
	lsl r5, r5, #0x14
	lsl r7, r1, #8
	lsl r1, r3, #0x18
	lsl r3, r2, #0x1d
	mov r2, #2
	lsl r2, r2, #0x1e
	orr r3, r2
	lsl r2, r4, #0x19
	orr r2, r3
	orr r1, r2
	lsl r6, r6, #0x10
	orr r1, r5
	orr r1, r6
	orr r1, r7
	orr r1, r0
	ldr r0, _021E8764 ; =0x04000064
	str r1, [r0]
_021E8760:
	pop {r4, r5, r6, r7}
	bx lr
	.balign 4, 0
_021E8764: .word 0x04000064

	thumb_func_start ov05_021E8768
ov05_021E8768: ; 0x021E8768
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0xa
	bgt _021E8786
	bge _021E879C
	cmp r0, #6
	bgt _021E87AC
	cmp r0, #2
	blt _021E87AC
	beq _021E878C
	cmp r0, #6
	beq _021E8794
	b _021E87AC
_021E8786:
	cmp r0, #0xe
	beq _021E87A4
	b _021E87AC
_021E878C:
	mov r0, #1
	bl GX_SetBankForLCDC
	b _021E87B2
_021E8794:
	mov r0, #2
	bl GX_SetBankForLCDC
	b _021E87B2
_021E879C:
	mov r0, #4
	bl GX_SetBankForLCDC
	b _021E87B2
_021E87A4:
	mov r0, #8
	bl GX_SetBankForLCDC
	b _021E87B2
_021E87AC:
	mov r0, #0
	bl GX_SetBankForLCDC
_021E87B2:
	ldr r0, [r4, #4]
	ldr r1, [r4, #8]
	ldr r2, [r4, #0xc]
	bl GX_SetGraphicsMode
	mov r0, #1
	str r0, [r4, #0x30]
	add r0, r5, #0
	bl SysTask_Destroy
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021E87C8
ov05_021E87C8: ; 0x021E87C8
	push {r4, r5, r6, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0xa
	bgt _021E87E4
	bge _021E8808
	cmp r0, #6
	bgt _021E8822
	cmp r0, #2
	blt _021E8822
	beq _021E87EA
	cmp r0, #6
	beq _021E87FA
	b _021E8822
_021E87E4:
	cmp r0, #0xe
	beq _021E8816
	b _021E8822
_021E87EA:
	mov r1, #0x1a
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x16
	lsl r2, r2, #0x10
	bl MIi_CpuClearFast
	b _021E8822
_021E87FA:
	mov r2, #2
	ldr r1, _021E8850 ; =0x06820000
	mov r0, #0
	lsl r2, r2, #0x10
	bl MIi_CpuClearFast
	b _021E8822
_021E8808:
	mov r2, #2
	ldr r1, _021E8854 ; =0x06840000
	mov r0, #0
	lsl r2, r2, #0x10
	bl MIi_CpuClearFast
	b _021E8822
_021E8816:
	mov r2, #2
	ldr r1, _021E8858 ; =0x06860000
	mov r0, #0
	lsl r2, r2, #0x10
	bl MIi_CpuClearFast
_021E8822:
	ldr r5, [r4, #0x10]
	ldr r1, [r4, #0x1c]
	ldr r3, [r4, #0x18]
	ldr r6, [r4, #0x14]
	ldr r0, [r4, #0xc]
	mov r4, #2
	lsl r2, r1, #0x10
	lsl r1, r0, #0x14
	lsl r5, r5, #0x1d
	lsl r4, r4, #0x1e
	orr r4, r5
	lsl r3, r3, #0x19
	lsl r0, r6, #0x18
	orr r3, r4
	orr r0, r3
	orr r0, r1
	add r1, r2, #0
	orr r1, r0
	mov r0, #0x10
	orr r1, r0
	ldr r0, _021E885C ; =0x04000064
	str r1, [r0]
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021E8850: .word 0x06820000
_021E8854: .word 0x06840000
_021E8858: .word 0x06860000
_021E885C: .word 0x04000064
