	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021E8648
MOD05_021E8648: ; 0x021E8648
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _021E8690 ; =MOD05_021E8728
	ldr r3, [r5, #0x28]
	mov r1, #0x38
	mov r2, #5
	bl FUN_020061E8
	add r6, r0, #0
	bl FUN_0201B6C8
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
	bl MOD05_021E87C8
	ldr r0, _021E8694 ; =MOD05_021E8768
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA98
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021E8690: .word MOD05_021E8728
_021E8694: .word MOD05_021E8768

	thumb_func_start MOD05_021E8698
MOD05_021E8698: ; 0x021E8698
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
	bl FUN_0200621C
	mov r0, #0
	str r0, [r4]
	pop {r4, pc}
	.balign 4, 0
_021E871C: .word 0x06820000
_021E8720: .word 0x06840000
_021E8724: .word 0x06860000

	thumb_func_start MOD05_021E8728
MOD05_021E8728: ; 0x021E8728
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

	thumb_func_start MOD05_021E8768
MOD05_021E8768: ; 0x021E8768
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
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021E87C8
MOD05_021E87C8: ; 0x021E87C8
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

	thumb_func_start MOD05_021E8860
MOD05_021E8860: ; 0x021E8860
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #8
	mov r1, #0
	bl GX_EngineAToggleLayers
	bl GX_ResetBankForBG
	mov r0, #4
	add r1, r0, #0
	bl AllocFromHeap
	add r7, r0, #0
	mov r0, #0
	add r1, r7, #0
	mov r2, #4
	bl MIi_CpuClear32
	ldr r6, _021E88BC ; =UNK05_021F78E4
	add r3, sp, #0
	mov r2, #5
_021E889E:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021E889E
	ldr r0, [r6]
	str r0, [r3]
	add r0, sp, #0
	str r5, [sp, #0x20]
	str r4, [sp, #0x24]
	bl MOD05_021E8648
	str r0, [r7]
	add r0, r7, #0
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021E88BC: .word UNK05_021F78E4

	thumb_func_start MOD05_021E88C0
MOD05_021E88C0: ; 0x021E88C0
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	ldr r0, [r4]
	mov r2, #0
	add r3, r1, #0
	bl MOD05_021E8698
	mov r0, #4
	bl GX_SetBankForBG
	mov r0, #0xe
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r1, [r4]
	mov r0, #4
	bl FreeToHeapExplicit
	pop {r4, pc}

	thumb_func_start MOD05_021E88E8
MOD05_021E88E8: ; 0x021E88E8
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #5
	bls _021E88FA
	b _021E8A56
_021E88FA:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E8906: ; jump table
	.short _021E8912 - _021E8906 - 2 ; case 0
	.short _021E8936 - _021E8906 - 2 ; case 1
	.short _021E8952 - _021E8906 - 2 ; case 2
	.short _021E899C - _021E8906 - 2 ; case 3
	.short _021E89F4 - _021E8906 - 2 ; case 4
	.short _021E8A1C - _021E8906 - 2 ; case 5
_021E8912:
	mov r0, #4
	mov r1, #0x20
	bl AllocFromHeap
	str r0, [r4, #0xc]
	mov r1, #0
	mov r2, #0x20
	bl memset
	ldr r5, [r4, #0xc]
	bl MOD05_021E3768
	str r0, [r5, #0x1c]
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8936:
	mov r1, #0x10
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r4, #4
	bl MOD05_021E3474
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8952:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021E8A56
	mov r1, #0
	str r1, [r4, #4]
	ldr r0, [r4]
	mov r2, #2
	add r0, r0, #1
	str r0, [r4]
	ldr r0, _021E8A5C ; =0xFFFFD000
	str r1, [sp]
	str r0, [sp, #4]
	lsl r0, r0, #2
	str r0, [sp, #8]
	ldr r1, [r5, #0x1c]
	add r0, r4, #0
	mov r3, #7
	bl MOD05_021E37CC
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	str r0, [r5]
	bl FUN_0201F010
	mov r2, #0x32
	add r1, r0, #0
	mov r0, #6
	lsl r2, r2, #0xc
	mov r3, #0x1e
	str r0, [sp]
	add r0, r5, #4
	add r2, r1, r2
	lsl r3, r3, #0xc
	bl MOD05_021E3644
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_021E899C:
	add r0, r5, #4
	bl MOD05_021E36A4
	add r6, r0, #0
	ldr r0, [r5, #4]
	ldr r1, [r5]
	bl FUN_0201EFE0
	cmp r6, #1
	bne _021E8A56
	ldr r0, [r4]
	mov r2, #2
	add r0, r0, #1
	str r0, [r4]
	ldr r0, _021E8A5C ; =0xFFFFD000
	mov r3, #6
	str r0, [sp]
	mov r0, #0xff
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #0x1e
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r1, [r5, #0x1c]
	add r0, r4, #0
	bl MOD05_021E3888
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	str r0, [r5]
	bl FUN_0201F010
	mov r2, #0x32
	add r1, r0, #0
	mov r0, #6
	lsl r2, r2, #0xc
	str r0, [sp]
	ldr r3, _021E8A60 ; =0xFFF01000
	add r0, r5, #4
	sub r2, r1, r2
	bl MOD05_021E3644
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_021E89F4:
	add r0, r5, #4
	bl MOD05_021E36A4
	add r6, r0, #0
	ldr r0, [r5, #4]
	ldr r1, [r5]
	bl FUN_0201EFE0
	cmp r6, #1
	bne _021E8A56
	add r0, r4, #0
	bl MOD05_021E35AC
	cmp r0, #1
	bne _021E8A56
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8A1C:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, _021E8A64 ; =0x04000010
	mov r1, #0
	str r1, [r0]
	str r1, [r0, #4]
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021E8A42
	mov r0, #1
	str r0, [r1]
_021E8A42:
	ldr r0, [r5, #0x1c]
	bl MOD05_021E37A4
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
_021E8A56:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021E8A5C: .word 0xFFFFD000
_021E8A60: .word 0xFFF01000
_021E8A64: .word 0x04000010

	thumb_func_start MOD05_021E8A68
MOD05_021E8A68: ; 0x021E8A68
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #5
	bls _021E8A7A
	b _021E8BD6
_021E8A7A:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E8A86: ; jump table
	.short _021E8A92 - _021E8A86 - 2 ; case 0
	.short _021E8AB6 - _021E8A86 - 2 ; case 1
	.short _021E8AD2 - _021E8A86 - 2 ; case 2
	.short _021E8B1C - _021E8A86 - 2 ; case 3
	.short _021E8B74 - _021E8A86 - 2 ; case 4
	.short _021E8B9C - _021E8A86 - 2 ; case 5
_021E8A92:
	mov r0, #4
	mov r1, #0x20
	bl AllocFromHeap
	str r0, [r4, #0xc]
	mov r1, #0
	mov r2, #0x20
	bl memset
	ldr r5, [r4, #0xc]
	bl MOD05_021E3768
	str r0, [r5, #0x1c]
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8AB6:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	add r1, r0, #0
	sub r1, #0x11
	add r2, r1, #0
	add r3, r4, #4
	bl MOD05_021E3474
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8AD2:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021E8BD6
	mov r1, #0
	str r1, [r4, #4]
	ldr r0, [r4]
	mov r2, #5
	add r0, r0, #1
	str r0, [r4]
	ldr r0, _021E8BDC ; =0xFFFFE000
	str r1, [sp]
	str r0, [sp, #4]
	ldr r0, _021E8BE0 ; =0xFFFF4000
	mov r3, #7
	str r0, [sp, #8]
	ldr r1, [r5, #0x1c]
	add r0, r4, #0
	bl MOD05_021E37CC
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	str r0, [r5]
	bl FUN_0201F010
	mov r2, #0x32
	add r1, r0, #0
	mov r0, #6
	lsl r2, r2, #0xc
	mov r3, #0x1e
	str r0, [sp]
	add r0, r5, #4
	add r2, r1, r2
	lsl r3, r3, #0xc
	bl MOD05_021E3644
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_021E8B1C:
	add r0, r5, #4
	bl MOD05_021E36A4
	add r6, r0, #0
	ldr r0, [r5, #4]
	ldr r1, [r5]
	bl FUN_0201EFE0
	cmp r6, #1
	bne _021E8BD6
	ldr r0, [r4]
	mov r2, #5
	add r0, r0, #1
	str r0, [r4]
	ldr r0, _021E8BDC ; =0xFFFFE000
	mov r3, #6
	str r0, [sp]
	mov r0, #0xff
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #0x1e
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r1, [r5, #0x1c]
	add r0, r4, #0
	bl MOD05_021E3888
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	str r0, [r5]
	bl FUN_0201F010
	mov r2, #0x1e
	add r1, r0, #0
	mov r0, #6
	lsl r2, r2, #0xc
	str r0, [sp]
	ldr r3, _021E8BE4 ; =0xFFF9C000
	add r0, r5, #4
	sub r2, r1, r2
	bl MOD05_021E3644
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_021E8B74:
	add r0, r5, #4
	bl MOD05_021E36A4
	add r6, r0, #0
	ldr r0, [r5, #4]
	ldr r1, [r5]
	bl FUN_0201EFE0
	cmp r6, #1
	bne _021E8BD6
	add r0, r4, #0
	bl MOD05_021E35AC
	cmp r0, #1
	bne _021E8BD6
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8B9C:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, _021E8BE8 ; =0x04000010
	mov r1, #0
	str r1, [r0]
	str r1, [r0, #4]
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021E8BC2
	mov r0, #1
	str r0, [r1]
_021E8BC2:
	ldr r0, [r5, #0x1c]
	bl MOD05_021E37A4
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
_021E8BD6:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021E8BDC: .word 0xFFFFE000
_021E8BE0: .word 0xFFFF4000
_021E8BE4: .word 0xFFF9C000
_021E8BE8: .word 0x04000010

	thumb_func_start MOD05_021E8BEC
MOD05_021E8BEC: ; 0x021E8BEC
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #6
	bls _021E8BFE
	b _021E8D16
_021E8BFE:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E8C0A: ; jump table
	.short _021E8C18 - _021E8C0A - 2 ; case 0
	.short _021E8C4A - _021E8C0A - 2 ; case 1
	.short _021E8C6A - _021E8C0A - 2 ; case 2
	.short _021E8CA0 - _021E8C0A - 2 ; case 3
	.short _021E8CB2 - _021E8C0A - 2 ; case 4
	.short _021E8CD4 - _021E8C0A - 2 ; case 5
	.short _021E8CE6 - _021E8C0A - 2 ; case 6
_021E8C18:
	mov r0, #4
	mov r1, #0x10
	bl AllocFromHeap
	str r0, [r4, #0xc]
	mov r2, #0x10
	mov r1, #0
_021E8C26:
	strb r1, [r0]
	add r0, r0, #1
	sub r2, r2, #1
	bne _021E8C26
	ldr r0, [r4, #0xc]
	mov r1, #4
	bl MOD05_021E8E8C
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8C4A:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	add r1, r0, #0
	sub r1, #0x11
	add r2, r1, #0
	add r3, r4, #4
	bl MOD05_021E3474
	mov r0, #0xa
	str r0, [r5, #0xc]
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8C6A:
	ldr r0, [r5, #0xc]
	sub r0, r0, #1
	str r0, [r5, #0xc]
	bpl _021E8D16
	ldr r0, [r4]
	mov r3, #0x32
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0xc
	str r0, [r5, #0xc]
	lsl r0, r0, #0xc
	str r0, [sp]
	lsl r3, r3, #4
	str r3, [sp, #4]
	ldr r0, _021E8D1C ; =0x04000010
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #4
	str r0, [sp, #0x10]
	add r0, r5, #0
	mov r2, #0xbf
	sub r3, #0x76
	bl MOD05_021E8EC0
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
_021E8CA0:
	ldr r0, [r5, #0xc]
	sub r0, r0, #1
	str r0, [r5, #0xc]
	bpl _021E8D16
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8CB2:
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r2, #0
	str r0, [sp, #8]
	mov r0, #3
	mov r1, #0x1e
	add r3, r2, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8CD4:
	bl FUN_0200E308
	cmp r0, #0
	beq _021E8D16
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8CE6:
	add r0, r5, #0
	bl MOD05_021E8EA8
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021E8D00
	mov r0, #1
	str r0, [r1]
_021E8D00:
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
_021E8D16:
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	nop
_021E8D1C: .word 0x04000010

	thumb_func_start MOD05_021E8D20
MOD05_021E8D20: ; 0x021E8D20
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #6
	bls _021E8D32
	b _021E8E4C
_021E8D32:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E8D3E: ; jump table
	.short _021E8D4C - _021E8D3E - 2 ; case 0
	.short _021E8D7E - _021E8D3E - 2 ; case 1
	.short _021E8D9E - _021E8D3E - 2 ; case 2
	.short _021E8DD6 - _021E8D3E - 2 ; case 3
	.short _021E8DE8 - _021E8D3E - 2 ; case 4
	.short _021E8E0A - _021E8D3E - 2 ; case 5
	.short _021E8E1C - _021E8D3E - 2 ; case 6
_021E8D4C:
	mov r0, #4
	mov r1, #0x10
	bl AllocFromHeap
	str r0, [r4, #0xc]
	mov r2, #0x10
	mov r1, #0
_021E8D5A:
	strb r1, [r0]
	add r0, r0, #1
	sub r2, r2, #1
	bne _021E8D5A
	ldr r0, [r4, #0xc]
	mov r1, #4
	bl MOD05_021E8E8C
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8D7E:
	mov r1, #0x10
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r4, #4
	bl MOD05_021E3474
	mov r0, #0xa
	str r0, [r5, #0xc]
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8D9E:
	ldr r0, [r5, #0xc]
	sub r0, r0, #1
	str r0, [r5, #0xc]
	bpl _021E8E4C
	ldr r0, [r4]
	mov r3, #0x32
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0xc
	str r0, [r5, #0xc]
	mov r0, #0xf
	lsl r0, r0, #0xc
	str r0, [sp]
	lsl r3, r3, #4
	str r3, [sp, #4]
	ldr r0, _021E8E50 ; =0x04000010
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #4
	str r0, [sp, #0x10]
	add r0, r5, #0
	mov r2, #0xbf
	add r3, #0xdf
	bl MOD05_021E8EC0
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
_021E8DD6:
	ldr r0, [r5, #0xc]
	sub r0, r0, #1
	str r0, [r5, #0xc]
	bpl _021E8E4C
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8DE8:
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r2, #0
	str r0, [sp, #8]
	mov r0, #3
	mov r1, #0x1e
	add r3, r2, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8E0A:
	bl FUN_0200E308
	cmp r0, #0
	beq _021E8E4C
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8E1C:
	add r0, r5, #0
	bl MOD05_021E8EA8
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021E8E36
	mov r0, #1
	str r0, [r1]
_021E8E36:
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
_021E8E4C:
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0
_021E8E50: .word 0x04000010

	thumb_func_start MOD05_021E8E54
MOD05_021E8E54: ; 0x021E8E54
	ldr r3, _021E8E60 ; =FUN_0200CA60
	mov r2, #1
	add r1, r0, #0
	ldr r0, _021E8E64 ; =MOD05_021E8E68
	lsl r2, r2, #0xa
	bx r3
	.balign 4, 0
_021E8E60: .word FUN_0200CA60
_021E8E64: .word MOD05_021E8E68

	thumb_func_start MOD05_021E8E68
MOD05_021E8E68: ; 0x021E8E68
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #8]
	cmp r0, #2
	blo _021E8E7C
	ldr r0, [r4]
	bl FUN_02012B30
	mov r0, #0
	str r0, [r4, #8]
_021E8E7C:
	ldr r0, [r4]
	bl FUN_02012B68
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E8E8C
MOD05_021E8E8C: ; 0x021E8E8C
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	bl FUN_02012A00
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #8]
	add r0, r4, #0
	bl MOD05_021E8E54
	str r0, [r4, #4]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E8EA8
MOD05_021E8EA8: ; 0x021E8EA8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FUN_0200CAB4
	ldr r0, [r4]
	bl FUN_02012AC4
	ldr r0, [r4]
	bl FUN_02012B00
	pop {r4, pc}

	thumb_func_start MOD05_021E8EC0
MOD05_021E8EC0: ; 0x021E8EC0
	push {r4, r5, lr}
	sub sp, #0x14
	ldr r4, [sp, #0x20]
	add r5, sp, #0x10
	str r4, [sp]
	mov r4, #0x14
	ldrsh r4, [r5, r4]
	str r4, [sp, #4]
	ldr r4, [sp, #0x28]
	str r4, [sp, #8]
	ldr r4, [sp, #0x2c]
	str r4, [sp, #0xc]
	ldr r4, [sp, #0x30]
	str r4, [sp, #0x10]
	ldr r0, [r0]
	bl FUN_02012A30
	add sp, #0x14
	pop {r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E8EE8
MOD05_021E8EE8: ; 0x021E8EE8
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, [r0]
	add r7, r1, #0
	bl FUN_02012B20
	add r5, r0, #0
	mov r6, #0
_021E8EF6:
	ldr r0, [r5]
	add r1, r7, #0
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	add r0, r6, #0
	bl _u32_div_f
	mov r1, #1
	tst r0, r1
	bne _021E8F0E
	lsl r0, r4, #0x10
	b _021E8F12
_021E8F0E:
	neg r0, r4
	lsl r0, r0, #0x10
_021E8F12:
	lsr r0, r0, #0x10
	str r0, [r5]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #0xc0
	blt _021E8EF6
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021E8F20
MOD05_021E8F20: ; 0x021E8F20
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #5
	bhi _021E9026
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E8F3C: ; jump table
	.short _021E8F48 - _021E8F3C - 2 ; case 0
	.short _021E8F68 - _021E8F3C - 2 ; case 1
	.short _021E8F84 - _021E8F3C - 2 ; case 2
	.short _021E8F92 - _021E8F3C - 2 ; case 3
	.short _021E8FDC - _021E8F3C - 2 ; case 4
	.short _021E8FFC - _021E8F3C - 2 ; case 5
_021E8F48:
	mov r0, #4
	mov r1, #0x1c
	bl AllocFromHeap
	str r0, [r4, #0xc]
	mov r2, #0x1c
	mov r1, #0
_021E8F56:
	strb r1, [r0]
	add r0, r0, #1
	sub r2, r2, #1
	bne _021E8F56
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8F68:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	add r1, r0, #0
	sub r1, #0x11
	add r2, r1, #0
	add r3, r4, #4
	bl MOD05_021E3474
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8F84:
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _021E9026
	add r0, r0, #1
	add sp, #0xc
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8F92:
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	mov r0, #0xc
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r1, #0x10
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	str r0, [r5]
	bl FUN_0201F010
	mov r2, #0x19
	add r1, r0, #0
	mov r0, #0xc
	lsl r2, r2, #0x10
	str r0, [sp]
	ldr r3, _021E902C ; =0xFFFFE000
	add r0, r5, #4
	sub r2, r1, r2
	bl MOD05_021E3644
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8FDC:
	add r0, r5, #4
	bl MOD05_021E36A4
	ldr r0, [r5, #4]
	ldr r1, [r5]
	bl FUN_0201EFE0
	bl FUN_0200E308
	cmp r0, #0
	beq _021E9026
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8FFC:
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021E9010
	mov r0, #1
	str r0, [r1]
_021E9010:
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
_021E9026:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021E902C: .word 0xFFFFE000

	thumb_func_start MOD05_021E9030
MOD05_021E9030: ; 0x021E9030
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #5
	bhi _021E9136
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E904C: ; jump table
	.short _021E9058 - _021E904C - 2 ; case 0
	.short _021E9078 - _021E904C - 2 ; case 1
	.short _021E9094 - _021E904C - 2 ; case 2
	.short _021E90A2 - _021E904C - 2 ; case 3
	.short _021E90EC - _021E904C - 2 ; case 4
	.short _021E910C - _021E904C - 2 ; case 5
_021E9058:
	mov r0, #4
	mov r1, #0x1c
	bl AllocFromHeap
	str r0, [r4, #0xc]
	mov r2, #0x1c
	mov r1, #0
_021E9066:
	strb r1, [r0]
	add r0, r0, #1
	sub r2, r2, #1
	bne _021E9066
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E9078:
	mov r1, #0x10
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r4, #4
	bl MOD05_021E3474
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E9094:
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _021E9136
	add r0, r0, #1
	add sp, #0xc
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E90A2:
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	mov r0, #0xc
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r1, #0x10
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	str r0, [r5]
	bl FUN_0201F010
	mov r2, #0x32
	add r1, r0, #0
	mov r0, #0xc
	lsl r2, r2, #0x10
	str r0, [sp]
	ldr r3, _021E913C ; =0xFFFFB000
	add r0, r5, #4
	sub r2, r1, r2
	bl MOD05_021E3644
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E90EC:
	add r0, r5, #4
	bl MOD05_021E36A4
	ldr r0, [r5, #4]
	ldr r1, [r5]
	bl FUN_0201EFE0
	bl FUN_0200E308
	cmp r0, #0
	beq _021E9136
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E910C:
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021E9120
	mov r0, #1
	str r0, [r1]
_021E9120:
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
_021E9136:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021E913C: .word 0xFFFFB000

	thumb_func_start MOD05_021E9140
MOD05_021E9140: ; 0x021E9140
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	add r7, r1, #0
	str r0, [sp, #0x10]
	ldr r0, [r7]
	ldr r4, [r7, #0xc]
	cmp r0, #7
	bls _021E9152
	b _021E948A
_021E9152:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E915E: ; jump table
	.short _021E916E - _021E915E - 2 ; case 0
	.short _021E9228 - _021E915E - 2 ; case 1
	.short _021E9242 - _021E915E - 2 ; case 2
	.short _021E924E - _021E915E - 2 ; case 3
	.short _021E92B2 - _021E915E - 2 ; case 4
	.short _021E931A - _021E915E - 2 ; case 5
	.short _021E93A6 - _021E915E - 2 ; case 6
	.short _021E9430 - _021E915E - 2 ; case 7
_021E916E:
	mov r1, #0x1e
	mov r0, #4
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r2, #0x1e
	str r0, [r7, #0xc]
	mov r1, #0
	lsl r2, r2, #4
	bl memset
	ldr r0, [r7, #0x10]
	ldr r4, [r7, #0xc]
	ldr r1, [r0, #0x20]
	mov r0, #7
	lsl r0, r0, #6
	str r1, [r4, r0]
	bl MOD05_021E3768
	str r0, [r4, #0x44]
	add r0, r4, #0
	add r0, #0x48
	mov r1, #2
	mov r2, #1
	bl MOD05_021E3E14
	mov r0, #5
	str r0, [sp]
	mov r0, #7
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	ldr r0, _021E949C ; =0x000927C0
	mov r1, #0x61
	str r0, [sp, #0xc]
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x48
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	mov r0, #0
	str r0, [sp, #0x14]
	add r6, r0, #0
	add r0, r4, #0
	str r0, [sp, #0x1c]
	add r0, #0x48
	add r5, r4, #0
	str r0, [sp, #0x1c]
_021E91D4:
	mov r0, #0
	str r0, [sp]
	mov r1, #0x61
	str r0, [sp, #4]
	lsl r1, r1, #2
	mov r2, #2
	mov r3, #6
	ldr r0, [sp, #0x1c]
	add r1, r4, r1
	lsl r2, r2, #0x12
	lsl r3, r3, #0x10
	bl MOD05_021E3FC4
	mov r1, #0x6e
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl FUN_02020310
	ldr r0, [sp, #0x14]
	add r5, r5, #4
	add r0, r0, #1
	add r6, r6, #2
	str r0, [sp, #0x14]
	cmp r0, #2
	blt _021E91D4
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E948A
_021E9228:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	add r1, r0, #0
	sub r1, #0x11
	add r2, r1, #0
	add r3, r7, #4
	bl MOD05_021E3474
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E948A
_021E9242:
	ldr r1, [r7, #4]
	cmp r1, #0
	beq _021E9310
	add r0, r0, #1
	str r0, [r7]
	b _021E948A
_021E924E:
	mov r0, #0xa
	mov r2, #1
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0x29
	lsl r2, r2, #0xc
	mov r3, #2
	bl MOD05_021E3644
	ldr r1, [r4]
	add r0, sp, #0x50
	add r2, r1, #0
	add r3, r1, #0
	bl MOD05_021E3FF8
	mov r6, #0
	add r5, r4, #0
_021E9270:
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, sp, #0x50
	bl FUN_02020064
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E9270
	add r0, r4, #0
	ldr r2, _021E94A0 ; =0x0000FFFF
	add r0, #0x18
	mov r1, #0
	mov r3, #0xa
	bl MOD05_021E35B0
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E948A
_021E92B2:
	add r0, r4, #0
	bl MOD05_021E36A4
	ldr r1, [r4]
	str r0, [sp, #0x18]
	add r0, sp, #0x50
	add r2, r1, #0
	add r3, r1, #0
	bl MOD05_021E3FF8
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E35C0
	mov r6, #0
	add r5, r4, #0
_021E92D2:
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, sp, #0x50
	bl FUN_02020064
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E92D2
	mov r0, #0x6e
	ldr r1, [r4, #0x18]
	lsl r0, r0, #2
	lsl r1, r1, #0x10
	ldr r0, [r4, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
	mov r1, #0x6f
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	ldr r2, [r4, #0x18]
	sub r1, #0xbc
	sub r1, r2, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02020088
	ldr r0, [sp, #0x18]
	cmp r0, #1
	beq _021E9312
_021E9310:
	b _021E948A
_021E9312:
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E948A
_021E931A:
	mov r0, #0
	str r0, [sp]
	mov r0, #0xff
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #0xa
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r1, [r4, #0x44]
	add r0, r7, #0
	mov r2, #0x60
	mov r3, #6
	bl MOD05_021E37CC
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_02020130
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_02020130
	mov r0, #6
	str r0, [sp]
	add r0, r4, #0
	mov r2, #0xff
	mov r3, #0xa
	add r0, #0x2c
	mov r1, #0
	lsl r2, r2, #0xc
	lsl r3, r3, #0xc
	bl MOD05_021E3644
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	bl FUN_0201F010
	add r1, r0, #0
	mov r0, #6
	str r0, [sp]
	mov r0, #0x71
	mov r2, #0x7d
	lsl r0, r0, #2
	lsl r2, r2, #0xe
	ldr r3, _021E94A4 ; =0xFFFF6000
	add r0, r4, r0
	sub r2, r1, r2
	bl MOD05_021E3644
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02020088
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02020088
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E948A
_021E93A6:
	add r0, r4, #0
	add r0, #0x2c
	bl MOD05_021E36A4
	mov r1, #2
	ldr r2, [r4, #0x2c]
	lsl r1, r1, #0x12
	sub r1, r1, r2
	mov r2, #6
	add r0, sp, #0x2c
	lsl r2, r2, #0x10
	mov r3, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x2c
	ldmia r3!, {r0, r1}
	add r2, sp, #0x44
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, #2
	str r0, [r2]
	ldr r2, [r4, #0x2c]
	lsl r1, r1, #0x12
	add r1, r2, r1
	mov r2, #6
	add r0, sp, #0x20
	lsl r2, r2, #0x10
	mov r3, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x20
	ldmia r3!, {r0, r1}
	add r2, sp, #0x38
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, sp, #0x44
	str r0, [r2]
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02020044
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x38
	bl FUN_02020044
	mov r0, #0x71
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD05_021E36A4
	mov r1, #0x71
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	sub r1, r1, #4
	ldr r1, [r4, r1]
	bl FUN_0201EFE0
	add r0, r7, #0
	bl MOD05_021E35AC
	cmp r0, #0
	beq _021E948A
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E948A
_021E9430:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r1, [r7, #0x14]
	cmp r1, #0
	beq _021E944A
	mov r0, #1
	str r0, [r1]
_021E944A:
	mov r6, #0
	add r5, r4, #0
_021E944E:
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0201FFC8
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E944E
	mov r1, #0x61
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x48
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	add r0, #0x48
	bl MOD05_021E3E44
	ldr r0, [r4, #0x44]
	bl MOD05_021E37A4
	ldr r1, [r7, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	ldr r0, [sp, #0x10]
	bl FUN_0200621C
_021E948A:
	ldr r0, [r7]
	cmp r0, #7
	beq _021E9496
	ldr r0, [r4, #0x48]
	bl FUN_0201FDEC
_021E9496:
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	nop
_021E949C: .word 0x000927C0
_021E94A0: .word 0x0000FFFF
_021E94A4: .word 0xFFFF6000

	thumb_func_start MOD05_021E94A8
MOD05_021E94A8: ; 0x021E94A8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x78
	add r6, r1, #0
	str r0, [sp, #0x10]
	ldr r0, [r6]
	ldr r4, [r6, #0xc]
	cmp r0, #7
	bhi _021E95A2
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E94C4: ; jump table
	.short _021E94D4 - _021E94C4 - 2 ; case 0
	.short _021E9582 - _021E94C4 - 2 ; case 1
	.short _021E959C - _021E94C4 - 2 ; case 2
	.short _021E95AA - _021E94C4 - 2 ; case 3
	.short _021E9638 - _021E94C4 - 2 ; case 4
	.short _021E96C8 - _021E94C4 - 2 ; case 5
	.short _021E9702 - _021E94C4 - 2 ; case 6
	.short _021E972C - _021E94C4 - 2 ; case 7
_021E94D4:
	mov r1, #0x71
	mov r0, #4
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x71
	str r0, [r6, #0xc]
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	ldr r0, [r6, #0x10]
	ldr r4, [r6, #0xc]
	ldr r1, [r0, #0x20]
	mov r0, #0x69
	lsl r0, r0, #2
	str r1, [r4, r0]
	bl MOD05_021E39FC
	str r0, [r4, #0x28]
	add r0, r4, #0
	add r0, #0x2c
	mov r1, #2
	mov r2, #1
	bl MOD05_021E3E14
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, _021E9798 ; =0x000927C0
	mov r1, #0x5a
	str r0, [sp, #0xc]
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x2c
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	add r0, r4, #0
	str r0, [sp, #0x14]
	add r0, #0x2c
	mov r7, #0
	add r5, r4, #0
	str r0, [sp, #0x14]
_021E9536:
	mov r0, #0
	str r0, [sp]
	mov r1, #0x5a
	str r0, [sp, #4]
	lsl r1, r1, #2
	mov r2, #2
	ldr r0, [sp, #0x14]
	add r1, r4, r1
	lsl r2, r2, #0x12
	mov r3, #0
	bl MOD05_021E3FC4
	mov r1, #0x67
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #2
	bl FUN_020200EC
	add r7, r7, #1
	add r5, r5, #4
	cmp r7, #2
	blt _021E9536
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021E9786
_021E9582:
	mov r1, #0x10
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r6, #4
	bl MOD05_021E3474
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021E9786
_021E959C:
	ldr r1, [r6, #4]
	cmp r1, #0
	bne _021E95A4
_021E95A2:
	b _021E9786
_021E95A4:
	add r0, r0, #1
	str r0, [r6]
	b _021E9786
_021E95AA:
	mov r2, #3
	ldr r1, _021E979C ; =0xFFF40000
	add r0, r4, #0
	lsl r2, r2, #0x12
	mov r3, #8
	bl MOD05_021E35EC
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r2, #2
	ldr r1, [r4]
	lsl r2, r2, #0x12
	sub r1, r2, r1
	add r0, sp, #0x3c
	lsr r2, r2, #1
	mov r3, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x3c
	ldmia r3!, {r0, r1}
	add r2, sp, #0x6c
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r3, #0
	str r0, [r2]
	mov r2, #2
	ldr r1, [r4]
	lsl r2, r2, #0x12
	add r0, sp, #0x30
	add r1, r1, r2
	bl MOD05_021E3FF8
	add r3, sp, #0x30
	ldmia r3!, {r0, r1}
	add r2, sp, #0x60
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, sp, #0x6c
	str r0, [r2]
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02020044
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x60
	bl FUN_02020044
	add r0, r4, #0
	ldr r2, _021E97A0 ; =0x0001FFFE
	add r0, #0x14
	mov r1, #0
	mov r3, #8
	bl MOD05_021E35B0
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021E9786
_021E9638:
	add r0, r4, #0
	bl MOD05_021E35FC
	mov r2, #2
	add r5, r0, #0
	ldr r1, [r4]
	lsl r2, r2, #0x12
	sub r1, r2, r1
	add r0, sp, #0x24
	lsr r2, r2, #1
	mov r3, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x24
	ldmia r3!, {r0, r1}
	add r2, sp, #0x54
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r3, #0
	str r0, [r2]
	mov r2, #2
	ldr r1, [r4]
	lsl r2, r2, #0x12
	add r0, sp, #0x18
	add r1, r1, r2
	bl MOD05_021E3FF8
	add r3, sp, #0x18
	ldmia r3!, {r0, r1}
	add r2, sp, #0x48
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, sp, #0x54
	str r0, [r2]
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02020044
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x48
	bl FUN_02020044
	add r0, r4, #0
	add r0, #0x14
	bl MOD05_021E35C0
	mov r0, #0x67
	ldr r1, [r4, #0x14]
	lsl r0, r0, #2
	lsl r1, r1, #0x10
	ldr r0, [r4, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
	ldr r1, [r4, #0x14]
	mov r0, #0x1a
	lsl r0, r0, #4
	neg r1, r1
	lsl r1, r1, #0x10
	ldr r0, [r4, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
	cmp r5, #1
	bne _021E9786
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021E9786
_021E96C8:
	mov r3, #1
	lsl r3, r3, #0xc
	str r3, [sp]
	ldr r1, [r4, #0x28]
	add r0, r6, #0
	mov r2, #8
	bl MOD05_021E3A70
	mov r0, #0x69
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201F010
	add r1, r0, #0
	mov r0, #8
	str r0, [sp]
	mov r0, #0x6a
	mov r2, #0x7d
	lsl r0, r0, #2
	lsl r2, r2, #0xe
	ldr r3, _021E97A4 ; =0xFFFF6000
	add r0, r4, r0
	sub r2, r1, r2
	bl MOD05_021E3644
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021E9786
_021E9702:
	mov r0, #0x6a
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD05_021E36A4
	mov r1, #0x6a
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	sub r1, r1, #4
	ldr r1, [r4, r1]
	bl FUN_0201EFE0
	add r0, r6, #0
	bl MOD05_021E35AC
	cmp r0, #1
	bne _021E9786
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021E9786
_021E972C:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r1, [r6, #0x14]
	cmp r1, #0
	beq _021E9746
	mov r0, #1
	str r0, [r1]
_021E9746:
	mov r7, #0
	add r5, r4, #0
_021E974A:
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0201FFC8
	add r7, r7, #1
	add r5, r5, #4
	cmp r7, #2
	blt _021E974A
	mov r1, #0x5a
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x2c
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	add r0, #0x2c
	bl MOD05_021E3E44
	ldr r0, [r4, #0x28]
	bl MOD05_021E3A48
	ldr r1, [r6, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	ldr r0, [sp, #0x10]
	bl FUN_0200621C
_021E9786:
	ldr r0, [r6]
	cmp r0, #7
	beq _021E9792
	ldr r0, [r4, #0x2c]
	bl FUN_0201FDEC
_021E9792:
	add sp, #0x78
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E9798: .word 0x000927C0
_021E979C: .word 0xFFF40000
_021E97A0: .word 0x0001FFFE
_021E97A4: .word 0xFFFF6000

	thumb_func_start MOD05_021E97A8
MOD05_021E97A8: ; 0x021E97A8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x58
	add r7, r1, #0
	str r0, [sp, #0x14]
	ldr r0, [r7]
	ldr r4, [r7, #0xc]
	cmp r0, #7
	bls _021E97BA
	b _021E9B2A
_021E97BA:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E97C6: ; jump table
	.short _021E97D6 - _021E97C6 - 2 ; case 0
	.short _021E9892 - _021E97C6 - 2 ; case 1
	.short _021E98AC - _021E97C6 - 2 ; case 2
	.short _021E98F2 - _021E97C6 - 2 ; case 3
	.short _021E9958 - _021E97C6 - 2 ; case 4
	.short _021E99E4 - _021E97C6 - 2 ; case 5
	.short _021E9A68 - _021E97C6 - 2 ; case 6
	.short _021E9AD0 - _021E97C6 - 2 ; case 7
_021E97D6:
	mov r1, #0x7a
	mov r0, #4
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x7a
	str r0, [r7, #0xc]
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	ldr r0, [r7, #0x10]
	ldr r4, [r7, #0xc]
	ldr r1, [r0, #0x20]
	mov r0, #0x72
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	add r0, #0x40
	mov r1, #4
	bl MOD05_021E8E8C
	mov r0, #0x79
	mov r1, #0xc
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	add r0, #0x50
	mov r1, #2
	mov r2, #1
	bl MOD05_021E3E14
	mov r0, #5
	str r0, [sp]
	mov r0, #7
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	ldr r0, _021E9B4C ; =0x000927C0
	mov r1, #0x63
	str r0, [sp, #0xc]
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x50
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	add r0, r4, #0
	str r0, [sp, #0x1c]
	add r0, #0x50
	mov r6, #0
	add r5, r4, #0
	str r0, [sp, #0x1c]
_021E9844:
	mov r0, #0
	str r0, [sp]
	mov r1, #0x63
	str r0, [sp, #4]
	lsl r1, r1, #2
	mov r2, #2
	mov r3, #6
	ldr r0, [sp, #0x1c]
	add r1, r4, r1
	lsl r2, r2, #0x12
	lsl r3, r3, #0x10
	bl MOD05_021E3FC4
	mov r1, #7
	lsl r1, r1, #6
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl FUN_02020310
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E9844
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E9B2A
_021E9892:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	add r1, r0, #0
	sub r1, #0x11
	add r2, r1, #0
	add r3, r7, #4
	bl MOD05_021E3474
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E9B2A
_021E98AC:
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021E98E4
	mov r0, #3
	lsl r0, r0, #0xe
	mov r3, #0x32
	str r0, [sp]
	lsl r3, r3, #4
	str r3, [sp, #4]
	ldr r0, _021E9B50 ; =0x04000010
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #4
	str r0, [sp, #0x10]
	add r0, r4, #0
	add r0, #0x40
	mov r2, #0xbf
	sub r3, #0x76
	bl MOD05_021E8EC0
	mov r0, #1
	str r0, [r4, #0x4c]
_021E98E4:
	ldr r0, [r7, #4]
	cmp r0, #0
	beq _021E99BE
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E9B2A
_021E98F2:
	add r0, r4, #0
	add r0, #0x18
	mov r1, #0
	mov r2, #0x10
	mov r3, #8
	bl MOD05_021E35B0
	ldr r3, [r4, #0x18]
	mov r0, #0x10
	sub r0, r0, r3
	str r0, [sp]
	ldr r0, _021E9B54 ; =0x04000050
	mov r1, #0
	mov r2, #0xf
	bl G2x_SetBlendAlpha_
	mov r6, #0
	add r5, r4, #0
_021E9916:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_02020398
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E9916
	add r0, r4, #0
	ldr r2, _021E9B58 ; =0x0000FFFF
	add r0, #0x2c
	mov r1, #0
	mov r3, #8
	bl MOD05_021E35B0
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E9B2A
_021E9958:
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E35C0
	add r6, r0, #0
	ldr r1, [r4, #0x18]
	mov r0, #0x10
	sub r0, r0, r1
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _021E9B5C ; =0x04000052
	strh r1, [r0]
	ldr r0, [r4, #0x2c]
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r4, #0
	add r0, #0x2c
	bl MOD05_021E35C0
	cmp r0, #0
	bne _021E99A2
	mov r0, #7
	ldr r1, [r4, #0x2c]
	lsl r0, r0, #6
	lsl r1, r1, #0x10
	ldr r0, [r4, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
	mov r0, #0x71
	lsl r0, r0, #2
	lsl r1, r5, #0x10
	ldr r0, [r4, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
	b _021E99BA
_021E99A2:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02020088
	mov r0, #0x71
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02020088
_021E99BA:
	cmp r6, #1
	beq _021E99C0
_021E99BE:
	b _021E9B2A
_021E99C0:
	ldr r0, _021E9B54 ; =0x04000050
	mov r6, #0
	strh r6, [r0]
	add r5, r4, #0
_021E99C8:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02020398
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E99C8
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E9B2A
_021E99E4:
	mov r1, #8
	str r1, [sp]
	ldr r3, _021E9B60 ; =0x0000019A
	add r0, r4, #0
	lsl r1, r1, #9
	mov r2, #0x29
	bl MOD05_021E3644
	ldr r1, [r4]
	add r0, sp, #0x34
	add r2, r1, #0
	add r3, r1, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x34
	add r2, sp, #0x4c
	ldmia r3!, {r0, r1}
	str r2, [sp, #0x20]
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r6, #0
	str r0, [r2]
	add r5, r4, #0
_021E9A12:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	ldr r1, [sp, #0x20]
	bl FUN_02020064
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E9A12
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201F010
	add r1, r0, #0
	mov r0, #8
	str r0, [sp]
	mov r0, #0x73
	mov r2, #0x7d
	lsl r0, r0, #2
	lsl r2, r2, #0xe
	ldr r3, _021E9B64 ; =0xFFFF6000
	add r0, r4, r0
	sub r2, r1, r2
	bl MOD05_021E3644
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r2, #0
	str r0, [sp, #8]
	mov r0, #3
	mov r1, #0x18
	add r3, r2, #0
	bl FUN_0200E1D0
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E9B2A
_021E9A68:
	add r0, r4, #0
	bl MOD05_021E36A4
	ldr r1, [r4]
	str r0, [sp, #0x18]
	add r0, sp, #0x28
	add r2, r1, #0
	add r3, r1, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x28
	add r2, sp, #0x40
	ldmia r3!, {r0, r1}
	str r2, [sp, #0x24]
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r6, #0
	str r0, [r2]
	add r5, r4, #0
_021E9A8E:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	ldr r1, [sp, #0x24]
	bl FUN_02020064
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E9A8E
	mov r0, #0x73
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD05_021E36A4
	mov r1, #0x73
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	sub r1, r1, #4
	ldr r1, [r4, r1]
	bl FUN_0201EFE0
	ldr r0, [sp, #0x18]
	cmp r0, #1
	bne _021E9B2A
	bl FUN_0200E308
	cmp r0, #1
	bne _021E9B2A
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E9B2A
_021E9AD0:
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r1, [r7, #0x14]
	cmp r1, #0
	beq _021E9AE2
	mov r0, #1
	str r0, [r1]
_021E9AE2:
	add r0, r4, #0
	add r0, #0x40
	bl MOD05_021E8EA8
	mov r6, #0
	str r6, [r4, #0x4c]
	add r5, r4, #0
_021E9AF0:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	bl FUN_0201FFC8
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E9AF0
	mov r1, #0x63
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x50
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r4, #0x50
	add r0, r4, #0
	bl MOD05_021E3E44
	ldr r1, [r7, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	ldr r0, [sp, #0x14]
	bl FUN_0200621C
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
_021E9B2A:
	ldr r0, [r4, #0x4c]
	cmp r0, #1
	bne _021E9B3A
	add r0, r4, #0
	add r0, #0x40
	mov r1, #2
	bl MOD05_021E8EE8
_021E9B3A:
	ldr r0, [r7]
	cmp r0, #7
	beq _021E9B46
	ldr r0, [r4, #0x50]
	bl FUN_0201FDEC
_021E9B46:
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E9B4C: .word 0x000927C0
_021E9B50: .word 0x04000010
_021E9B54: .word 0x04000050
_021E9B58: .word 0x0000FFFF
_021E9B5C: .word 0x04000052
_021E9B60: .word 0x0000019A
_021E9B64: .word 0xFFFF6000

	thumb_func_start MOD05_021E9B68
MOD05_021E9B68: ; 0x021E9B68
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	str r0, [sp, #0x18]
	add r0, r1, #0
	ldr r0, [r0]
	str r1, [sp, #0x1c]
	ldr r4, [r1, #0xc]
	cmp r0, #7
	bls _021E9B7C
	b _021EA01A
_021E9B7C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E9B88: ; jump table
	.short _021E9B98 - _021E9B88 - 2 ; case 0
	.short _021E9CAA - _021E9B88 - 2 ; case 1
	.short _021E9CCA - _021E9B88 - 2 ; case 2
	.short _021E9D24 - _021E9B88 - 2 ; case 3
	.short _021E9DE4 - _021E9B88 - 2 ; case 4
	.short _021E9E82 - _021E9B88 - 2 ; case 5
	.short _021E9F1C - _021E9B88 - 2 ; case 6
	.short _021E9F70 - _021E9B88 - 2 ; case 7
_021E9B98:
	mov r1, #9
	mov r0, #4
	lsl r1, r1, #6
	bl AllocFromHeap
	ldr r1, [sp, #0x1c]
	mov r2, #9
	str r0, [r1, #0xc]
	mov r1, #0
	lsl r2, r2, #6
	bl memset
	ldr r0, [sp, #0x1c]
	ldr r4, [r0, #0xc]
	ldr r0, [r0, #0x10]
	ldr r1, [r0, #0x20]
	mov r0, #0x22
	lsl r0, r0, #4
	str r1, [r4, r0]
	sub r0, #0x10
	add r0, r4, r0
	mov r1, #4
	bl MOD05_021E8E8C
	mov r0, #0x8f
	mov r1, #0xe
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #3
	mov r2, #1
	bl MOD05_021E3E14
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, _021E9F5C ; =0x000927C0
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	mov r7, #0x4f
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #2
_021E9C02:
	mov r0, #0
	str r0, [sp]
	mov r2, #0
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r4, r7
	add r3, r2, #0
	bl MOD05_021E3FC4
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r0, #4
	bl MOD05_021E4140
	mov r1, #0x7d
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _021E9C02
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #1
	bl AllocWindows
	mov r1, #0x83
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r0, [sp, #0x1c]
	ldr r1, [r4, r1]
	ldr r0, [r0, #0x10]
	mov r2, #3
	ldr r0, [r0, #8]
	bl FUN_02019064
	mov r1, #0
	add r0, sp, #0x28
	strh r1, [r0]
	mov r0, #3
	add r1, sp, #0x28
	mov r2, #2
	mov r3, #0x1e
	bl FUN_02017FB4
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02019220
	ldr r0, [sp, #0x1c]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x1c]
	str r1, [r0]
	b _021EA01A
_021E9CAA:
	mov r1, #0x10
	ldr r3, [sp, #0x1c]
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r3, #4
	bl MOD05_021E3474
	ldr r0, [sp, #0x1c]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x1c]
	str r1, [r0]
	b _021EA01A
_021E9CCA:
	mov r3, #0x8f
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	sub r0, r0, #1
	str r0, [r4, r3]
	ldr r0, [r4, r3]
	cmp r0, #0
	bne _021E9D08
	mov r0, #3
	lsl r0, r0, #0xe
	str r0, [sp]
	add r0, r3, #0
	add r0, #0xe4
	str r0, [sp, #4]
	ldr r0, _021E9F60 ; =0x04000010
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #4
	str r0, [sp, #0x10]
	add r0, r3, #0
	sub r0, #0x2c
	add r0, r4, r0
	mov r2, #0xbf
	add r3, #0x6e
	bl MOD05_021E8EC0
	mov r0, #0x87
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
_021E9D08:
	ldr r0, [sp, #0x1c]
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021E9D34
	mov r0, #0x8f
	mov r1, #6
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, [sp, #0x1c]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x1c]
	str r1, [r0]
	b _021EA01A
_021E9D24:
	mov r0, #0x8f
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0
	blt _021E9D36
_021E9D34:
	b _021EA01A
_021E9D36:
	sub r0, #0x1c
	ldr r0, [r4, r0]
	bl FUN_0201F010
	add r1, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0x89
	mov r2, #0x7d
	lsl r0, r0, #2
	lsl r2, r2, #0xe
	ldr r3, _021E9F64 ; =0xFFFF6000
	add r0, r4, r0
	sub r2, r1, r2
	bl MOD05_021E3644
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r2, _021E9F68 ; =0x0000FFFF
	add r0, r4, r0
	mov r1, #0
	mov r3, #6
	bl MOD05_021E35B0
	mov r0, #0x5f
	lsl r0, r0, #2
	mov r2, #0x1f
	add r0, r4, r0
	mov r1, #0xe7
	mvn r2, r2
	mov r3, #6
	bl MOD05_021E35B0
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	mov r3, #0x40
	str r1, [sp, #8]
	mov r1, #0x56
	str r1, [sp, #0xc]
	str r3, [sp, #0x10]
	mov r1, #0xf
	str r1, [sp, #0x14]
	sub r0, #0x18
	mov r1, #0x2b
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, #0xf8
	bl MOD05_021E4160
	mov r1, #0x2b
	mov r2, #0xe7
	add r0, sp, #0x38
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x38
	bl FUN_02020044
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r1, #1
	lsl r0, r1, #9
	str r1, [r4, r0]
	ldr r0, [sp, #0x1c]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x1c]
	str r1, [r0]
	mov r0, #0x8f
	mov r1, #4
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021EA01A
_021E9DE4:
	mov r0, #0x8f
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0
	bge _021E9E92
	sub r0, #0xac
	mov r2, #0x1f
	add r0, r4, r0
	mov r1, #0xe7
	mvn r2, r2
	mov r3, #6
	bl MOD05_021E35B0
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r2, _021E9F6C ; =0xFFFF0001
	add r0, r4, r0
	mov r1, #0
	mov r3, #6
	bl MOD05_021E35B0
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r0, #0x14
	str r1, [sp, #8]
	mov r1, #0x56
	str r1, [sp, #0xc]
	mov r1, #0x40
	str r1, [sp, #0x10]
	mov r1, #0xf
	str r1, [sp, #0x14]
	mov r1, #0xd7
	add r3, r1, #0
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, #0x61
	bl MOD05_021E4160
	mov r1, #0xd7
	mov r2, #0xe7
	add r0, sp, #0x38
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	mov r3, #1
	bl MOD05_021E3FF8
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x38
	bl FUN_02020044
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r1, #0x81
	mov r0, #1
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [sp, #0x1c]
	add r1, #0x38
	ldr r0, [r0]
	add r2, r0, #1
	ldr r0, [sp, #0x1c]
	str r2, [r0]
	mov r0, #2
	str r0, [r4, r1]
	b _021EA01A
_021E9E82:
	mov r0, #0x8f
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0
	blt _021E9E94
_021E9E92:
	b _021EA01A
_021E9E94:
	sub r0, #0x98
	mov r2, #0x1f
	add r0, r4, r0
	mov r1, #0xe7
	mvn r2, r2
	mov r3, #6
	bl MOD05_021E35B0
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r2, _021E9F68 ; =0x0000FFFF
	add r0, r4, r0
	mov r1, #0
	mov r3, #6
	bl MOD05_021E35B0
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r0, #0x10
	str r1, [sp, #8]
	mov r1, #0x56
	str r1, [sp, #0xc]
	mov r1, #0x40
	str r1, [sp, #0x10]
	mov r1, #0xf
	str r1, [sp, #0x14]
	mov r1, #0x81
	add r3, r1, #0
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, #0xb7
	bl MOD05_021E4160
	mov r1, #0x81
	mov r2, #0xe7
	add r0, sp, #0x38
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	mov r3, #2
	bl MOD05_021E3FF8
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x38
	bl FUN_02020044
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x82
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, [sp, #0x1c]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x1c]
	str r1, [r0]
	b _021EA01A
_021E9F1C:
	mov r0, #0x89
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD05_021E36A4
	mov r1, #0x89
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	sub r1, r1, #4
	ldr r1, [r4, r1]
	bl FUN_0201EFE0
	mov r1, #2
	lsl r1, r1, #8
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _021EA01A
	add r0, r1, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021EA01A
	add r1, #8
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _021EA01A
	ldr r0, [sp, #0x1c]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x1c]
	str r1, [r0]
	b _021EA01A
	nop
_021E9F5C: .word 0x000927C0
_021E9F60: .word 0x04000010
_021E9F64: .word 0xFFFF6000
_021E9F68: .word 0x0000FFFF
_021E9F6C: .word 0xFFFF0001
_021E9F70:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, [sp, #0x1c]
	ldr r1, [r0, #0x14]
	cmp r1, #0
	beq _021E9F8C
	mov r0, #1
	str r0, [r1]
_021E9F8C:
	mov r0, #0x21
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD05_021E8EA8
	mov r0, #0x87
	lsl r0, r0, #2
	mov r6, #0
	add r7, r0, #0
	str r6, [r4, r0]
	add r5, r4, #0
	sub r7, #0x28
_021E9FA4:
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_0201FFC8
	ldr r0, [r5, r7]
	bl MOD05_021E4158
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _021E9FA4
	mov r1, #0x4f
	lsl r1, r1, #2
	add r0, r4, #0
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	bl MOD05_021E3E44
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02019570
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02019178
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020191A4
	mov r0, #3
	mov r1, #0x20
	mov r2, #0
	mov r3, #4
	bl FUN_02017F18
	ldr r0, [sp, #0x1c]
	mov r1, #3
	ldr r0, [r0, #0x10]
	ldr r0, [r0, #8]
	bl FUN_02018744
	ldr r1, [sp, #0x1c]
	mov r0, #4
	ldr r1, [r1, #0xc]
	bl FreeToHeapExplicit
	ldr r0, [sp, #0x18]
	bl FUN_0200621C
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
_021EA01A:
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #1
	bne _021EA02E
	sub r0, #0xc
	add r0, r4, r0
	mov r1, #2
	bl MOD05_021E8EE8
_021EA02E:
	mov r1, #0x5f
	mov r0, #0
	lsl r1, r1, #2
	str r0, [sp, #0x20]
	add r0, r4, r1
	add r1, #0x3c
	add r5, r4, #0
	str r0, [sp, #0x24]
	add r7, r4, r1
	add r6, r4, #0
_021EA042:
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r5, r0]
	cmp r0, #1
	bne _021EA0B0
	mov r0, #0x7d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl MOD05_021E41B8
	cmp r0, #0
	beq _021EA062
	mov r0, #2
	mov r1, #0
	lsl r0, r0, #8
	str r1, [r5, r0]
_021EA062:
	ldr r0, [sp, #0x24]
	bl MOD05_021E35C0
	add r0, r7, #0
	bl MOD05_021E35C0
	mov r1, #0x6e
	lsl r1, r1, #2
	mov r0, #0x17
	ldr r1, [r6, r1]
	lsl r0, r0, #4
	lsl r1, r1, #0x10
	ldr r0, [r5, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_0202011C
	add r3, r0, #0
	add r2, sp, #0x2c
	ldmia r3!, {r0, r1}
	mov ip, r2
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, ip
	str r0, [r2]
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	lsl r0, r0, #0xc
	str r0, [sp, #0x30]
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02020044
_021EA0B0:
	ldr r0, [sp, #0x24]
	add r5, r5, #4
	add r0, #0x14
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x20]
	add r7, #0x14
	add r0, r0, #1
	add r6, #0x14
	str r0, [sp, #0x20]
	cmp r0, #3
	blt _021EA042
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02019220
	ldr r0, [sp, #0x1c]
	ldr r0, [r0]
	cmp r0, #7
	beq _021EA0DE
	ldr r0, [r4]
	bl FUN_0201FDEC
_021EA0DE:
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EA0E4
MOD05_021EA0E4: ; 0x021EA0E4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5]
	ldr r4, [r5, #0xc]
	cmp r0, #7
	bhi _021EA1B8
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EA100: ; jump table
	.short _021EA110 - _021EA100 - 2 ; case 0
	.short _021EA198 - _021EA100 - 2 ; case 1
	.short _021EA1B2 - _021EA100 - 2 ; case 2
	.short _021EA1C0 - _021EA100 - 2 ; case 3
	.short _021EA236 - _021EA100 - 2 ; case 4
	.short _021EA2C2 - _021EA100 - 2 ; case 5
	.short _021EA310 - _021EA100 - 2 ; case 6
	.short _021EA338 - _021EA100 - 2 ; case 7
_021EA110:
	mov r1, #0x1f
	mov r0, #4
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r2, #0x1f
	str r0, [r5, #0xc]
	mov r1, #0
	lsl r2, r2, #4
	bl memset
	ldr r0, [r5, #0x10]
	ldr r4, [r5, #0xc]
	ldr r1, [r0, #0x20]
	mov r0, #0x1d
	lsl r0, r0, #4
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	add r0, #0x5c
	add r2, r1, #0
	bl MOD05_021E3E14
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, _021EA394 ; =0x000927C0
	mov r1, #0x66
	str r0, [sp, #0xc]
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x5c
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	mov r0, #0
	str r0, [sp]
	mov r1, #0x66
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r1, r1, #2
	mov r2, #2
	ldr r3, _021EA398 ; =0xFFFE0000
	add r0, #0x5c
	add r1, r4, r1
	lsl r2, r2, #0x12
	bl MOD05_021E3FC4
	mov r1, #0x73
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EA382
_021EA198:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	add r1, r0, #0
	sub r1, #0x11
	add r2, r1, #0
	add r3, r5, #4
	bl MOD05_021E3474
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EA382
_021EA1B2:
	ldr r1, [r5, #4]
	cmp r1, #0
	bne _021EA1BA
_021EA1B8:
	b _021EA382
_021EA1BA:
	add r0, r0, #1
	str r0, [r5]
	b _021EA382
_021EA1C0:
	mov r2, #1
	mov r0, #0xc
	lsl r2, r2, #0x14
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0
	lsr r3, r2, #7
	bl MOD05_021E3644
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xc
	str r0, [sp]
	add r0, r4, #0
	mov r2, #2
	ldr r1, _021EA39C ; =0x0000019A
	add r0, #0x18
	lsl r2, r2, #0xc
	mov r3, #0
	bl MOD05_021E3644
	mov r0, #0xc
	str r0, [sp]
	add r0, r4, #0
	mov r2, #2
	ldr r1, _021EA39C ; =0x0000019A
	add r0, #0x30
	lsl r2, r2, #0xc
	mov r3, #0
	bl MOD05_021E3644
	ldr r1, [r4, #0x18]
	ldr r2, [r4, #0x30]
	add r0, sp, #0x28
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x28
	mov r2, #2
	bl FUN_02020074
	add r0, r4, #0
	ldr r2, _021EA3A0 ; =0x0000FFFF
	add r0, #0x48
	mov r1, #0
	mov r3, #0xc
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EA382
_021EA236:
	add r0, r4, #0
	bl MOD05_021E36A4
	mov r1, #2
	lsl r1, r1, #0x12
	add r6, r0, #0
	ldr r3, [r4]
	lsr r2, r1, #2
	sub r2, r3, r2
	add r0, sp, #0x10
	mov r3, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x10
	add r2, sp, #0x1c
	ldmia r3!, {r0, r1}
	add r7, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r7, #0
	str r0, [r2]
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02020044
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E36A4
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E36A4
	ldr r1, [r4, #0x18]
	ldr r2, [r4, #0x30]
	add r0, sp, #0x28
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x28
	bl FUN_02020064
	add r0, r4, #0
	add r0, #0x48
	bl MOD05_021E35C0
	mov r0, #0x73
	ldr r1, [r4, #0x48]
	lsl r0, r0, #2
	lsl r1, r1, #0x10
	ldr r0, [r4, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
	cmp r6, #1
	bne _021EA382
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EA382
_021EA2C2:
	ldr r0, [r5, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	mov r0, #0x1d
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_0201F010
	add r1, r0, #0
	mov r0, #8
	str r0, [sp]
	mov r0, #0x75
	mov r2, #0xfa
	lsl r0, r0, #2
	lsl r2, r2, #0xe
	mov r3, #0xa
	add r0, r4, r0
	sub r2, r1, r2
	lsl r3, r3, #0xc
	bl MOD05_021E3644
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r2, #0
	str r0, [sp, #8]
	mov r0, #3
	mov r1, #0x12
	add r3, r2, #0
	bl FUN_0200E1D0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EA382
_021EA310:
	mov r0, #0x75
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD05_021E36A4
	mov r1, #0x75
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	sub r1, r1, #4
	ldr r1, [r4, r1]
	bl FUN_0201EFE0
	bl FUN_0200E308
	cmp r0, #0
	beq _021EA382
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EA382
_021EA338:
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, [r5, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r1, [r5, #0x14]
	cmp r1, #0
	beq _021EA354
	mov r0, #1
	str r0, [r1]
_021EA354:
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201FFC8
	mov r1, #0x66
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x5c
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	add r0, #0x5c
	bl MOD05_021E3E44
	ldr r1, [r5, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
_021EA382:
	ldr r0, [r5]
	cmp r0, #7
	beq _021EA38E
	ldr r0, [r4, #0x5c]
	bl FUN_0201FDEC
_021EA38E:
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	nop
_021EA394: .word 0x000927C0
_021EA398: .word 0xFFFE0000
_021EA39C: .word 0x0000019A
_021EA3A0: .word 0x0000FFFF

	thumb_func_start MOD05_021EA3A4
MOD05_021EA3A4: ; 0x021EA3A4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	str r0, [sp, #0x14]
	add r0, r1, #0
	ldr r0, [r0]
	str r1, [sp, #0x18]
	ldr r4, [r1, #0xc]
	cmp r0, #9
	bls _021EA3B8
	b _021EA7DE
_021EA3B8:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EA3C4: ; jump table
	.short _021EA3D8 - _021EA3C4 - 2 ; case 0
	.short _021EA4CE - _021EA3C4 - 2 ; case 1
	.short _021EA4EE - _021EA3C4 - 2 ; case 2
	.short _021EA506 - _021EA3C4 - 2 ; case 3
	.short _021EA582 - _021EA3C4 - 2 ; case 4
	.short _021EA5FE - _021EA3C4 - 2 ; case 5
	.short _021EA674 - _021EA3C4 - 2 ; case 6
	.short _021EA6B4 - _021EA3C4 - 2 ; case 7
	.short _021EA6FA - _021EA3C4 - 2 ; case 8
	.short _021EA748 - _021EA3C4 - 2 ; case 9
_021EA3D8:
	mov r1, #0x8a
	mov r0, #4
	lsl r1, r1, #2
	bl AllocFromHeap
	ldr r1, [sp, #0x18]
	mov r2, #0x8a
	str r0, [r1, #0xc]
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	ldr r0, [sp, #0x18]
	mov r2, #1
	ldr r4, [r0, #0xc]
	ldr r0, [r0, #0x10]
	ldr r1, [r0, #0x20]
	mov r0, #0x82
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #3
	bl MOD05_021E3E14
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, _021EA738 ; =0x000927C0
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	mov r7, #0x4f
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #2
_021EA430:
	mov r0, #0
	mov r2, #0
	str r0, [sp]
	add r3, r2, #0
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r4, r7
	sub r3, #0x20
	bl MOD05_021E3FC4
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _021EA430
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #1
	bl AllocWindows
	mov r1, #2
	lsl r1, r1, #8
	str r0, [r4, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r0, [sp, #0x18]
	ldr r1, [r4, r1]
	ldr r0, [r0, #0x10]
	mov r2, #3
	ldr r0, [r0, #8]
	bl FUN_02019064
	mov r1, #0
	add r0, sp, #0x28
	strh r1, [r0]
	mov r0, #3
	add r1, sp, #0x28
	mov r2, #2
	mov r3, #0x1e
	bl FUN_02017FB4
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	bl FUN_02019220
	mov r0, #4
	bl MOD05_021E4394
	mov r1, #0x81
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [r0]
	b _021EA7DE
_021EA4CE:
	mov r1, #0x10
	ldr r3, [sp, #0x18]
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r3, #4
	bl MOD05_021E3474
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [r0]
	b _021EA7DE
_021EA4EE:
	ldr r1, [sp, #0x18]
	ldr r1, [r1, #4]
	cmp r1, #0
	beq _021EA516
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [r0]
	mov r0, #0x89
	mov r1, #0
	lsl r0, r0, #2
	strh r1, [r4, r0]
	b _021EA7DE
_021EA506:
	mov r0, #0x89
	lsl r0, r0, #2
	ldrsh r1, [r4, r0]
	sub r1, r1, #1
	strh r1, [r4, r0]
	ldrsh r1, [r4, r0]
	cmp r1, #0
	ble _021EA518
_021EA516:
	b _021EA7DE
_021EA518:
	sub r0, #0xa8
	mov r1, #0x1f
	add r0, r4, r0
	mvn r1, r1
	mov r2, #0xe0
	mov r3, #5
	bl MOD05_021E35B0
	mov r1, #2
	ldr r2, _021EA73C ; =0xFFFE0000
	add r0, sp, #0x38
	lsl r1, r1, #0x12
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x38
	bl FUN_02020044
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r2, _021EA740 ; =0x0000FFFF
	add r0, r4, r0
	mov r1, #0
	mov r3, #5
	bl MOD05_021E35B0
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r1, #0x7d
	mov r3, #1
	lsl r1, r1, #2
	str r3, [r4, r1]
	ldr r0, [sp, #0x18]
	add r1, #0x30
	ldr r0, [r0]
	add r2, r0, #1
	ldr r0, [sp, #0x18]
	str r2, [r0]
	strh r3, [r4, r1]
	b _021EA7DE
_021EA582:
	mov r0, #0x89
	lsl r0, r0, #2
	ldrsh r1, [r4, r0]
	sub r1, r1, #1
	strh r1, [r4, r0]
	ldrsh r1, [r4, r0]
	cmp r1, #0
	bgt _021EA68E
	sub r0, #0x94
	mov r1, #0x1f
	add r0, r4, r0
	mvn r1, r1
	mov r2, #0xe0
	mov r3, #5
	bl MOD05_021E35B0
	mov r1, #0xd
	ldr r2, _021EA73C ; =0xFFFE0000
	add r0, sp, #0x38
	lsl r1, r1, #0x10
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x38
	bl FUN_02020044
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r2, _021EA744 ; =0xFFFF0001
	add r0, r4, r0
	mov r1, #0
	mov r3, #5
	bl MOD05_021E35B0
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r1, #0x7e
	mov r0, #1
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [sp, #0x18]
	add r1, #0x2c
	ldr r0, [r0]
	add r2, r0, #1
	ldr r0, [sp, #0x18]
	str r2, [r0]
	mov r0, #3
	strh r0, [r4, r1]
	b _021EA7DE
_021EA5FE:
	mov r0, #0x89
	lsl r0, r0, #2
	ldrsh r1, [r4, r0]
	sub r1, r1, #1
	strh r1, [r4, r0]
	ldrsh r1, [r4, r0]
	cmp r1, #0
	bgt _021EA68E
	sub r0, #0x80
	mov r1, #0x1f
	add r0, r4, r0
	mvn r1, r1
	mov r2, #0xe0
	mov r3, #5
	bl MOD05_021E35B0
	mov r1, #3
	ldr r2, _021EA73C ; =0xFFFE0000
	add r0, sp, #0x38
	lsl r1, r1, #0x10
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x38
	bl FUN_02020044
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r2, _021EA740 ; =0x0000FFFF
	add r0, r4, r0
	mov r1, #0
	mov r3, #5
	bl MOD05_021E35B0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r0, #0x7f
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [r0]
	b _021EA7DE
_021EA674:
	mov r1, #0x7d
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _021EA68E
	add r0, r1, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021EA68E
	add r1, #8
	ldr r0, [r4, r1]
	cmp r0, #0
	beq _021EA690
_021EA68E:
	b _021EA7DE
_021EA690:
	mov r7, #0x17
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #4
_021EA698:
	ldr r0, [r5, r7]
	mov r1, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _021EA698
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [r0]
	b _021EA7DE
_021EA6B4:
	mov r0, #0xf
	mov r1, #1
	str r0, [sp]
	mov r0, #0x81
	lsl r0, r0, #2
	lsl r3, r1, #9
	ldr r0, [r4, r0]
	ldr r3, [r4, r3]
	add r2, r1, #0
	bl MOD05_021E43E4
	mov r0, #0x82
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201F010
	add r1, r0, #0
	mov r0, #0x40
	str r0, [sp]
	mov r0, #0x83
	mov r2, #0xfa
	lsl r0, r0, #2
	lsl r2, r2, #0xe
	mov r3, #0xa
	add r0, r4, r0
	sub r2, r1, r2
	lsl r3, r3, #0xc
	bl MOD05_021E3644
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [r0]
	b _021EA7DE
_021EA6FA:
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD05_021E4424
	add r5, r0, #0
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	bl FUN_02019220
	mov r0, #0x83
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD05_021E36A4
	mov r1, #0x83
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	sub r1, r1, #4
	ldr r1, [r4, r1]
	bl FUN_0201EFE0
	cmp r5, #1
	bne _021EA7DE
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [r0]
	b _021EA7DE
	.balign 4, 0
_021EA738: .word 0x000927C0
_021EA73C: .word 0xFFFE0000
_021EA740: .word 0x0000FFFF
_021EA744: .word 0xFFFF0001
_021EA748:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, [sp, #0x18]
	ldr r1, [r0, #0x14]
	cmp r1, #0
	beq _021EA764
	mov r0, #1
	str r0, [r1]
_021EA764:
	mov r7, #0x17
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #4
_021EA76C:
	ldr r0, [r5, r7]
	bl FUN_0201FFC8
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _021EA76C
	mov r1, #0x4f
	lsl r1, r1, #2
	add r0, r4, #0
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	bl MOD05_021E3E44
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD05_021E43C4
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	bl FUN_02019570
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	bl FUN_02019178
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020191A4
	mov r0, #3
	mov r1, #0x20
	mov r2, #0
	mov r3, #4
	bl FUN_02017F18
	ldr r0, [sp, #0x18]
	mov r1, #3
	ldr r0, [r0, #0x10]
	ldr r0, [r0, #8]
	bl FUN_02018744
	ldr r1, [sp, #0x18]
	mov r0, #4
	ldr r1, [r1, #0xc]
	bl FreeToHeapExplicit
	ldr r0, [sp, #0x14]
	bl FUN_0200621C
_021EA7DE:
	mov r1, #0x5f
	mov r0, #0
	lsl r1, r1, #2
	str r0, [sp, #0x1c]
	add r0, r4, r1
	add r1, #0x3c
	add r5, r4, #0
	str r0, [sp, #0x20]
	add r7, r4, r1
	add r6, r4, #0
_021EA7F2:
	mov r0, #0x7d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #1
	bne _021EA85A
	ldr r0, [sp, #0x20]
	bl MOD05_021E35C0
	str r0, [sp, #0x24]
	add r0, r7, #0
	bl MOD05_021E35C0
	ldr r0, [sp, #0x24]
	cmp r0, #0
	beq _021EA818
	mov r0, #0x7d
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
_021EA818:
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_0202011C
	add r3, r0, #0
	add r2, sp, #0x2c
	ldmia r3!, {r0, r1}
	mov ip, r2
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, ip
	str r0, [r2]
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	lsl r0, r0, #0xc
	str r0, [sp, #0x30]
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02020044
	mov r1, #0x6e
	lsl r1, r1, #2
	mov r0, #0x17
	ldr r1, [r6, r1]
	lsl r0, r0, #4
	lsl r1, r1, #0x10
	ldr r0, [r5, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
_021EA85A:
	ldr r0, [sp, #0x20]
	add r5, r5, #4
	add r0, #0x14
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r7, #0x14
	add r0, r0, #1
	add r6, #0x14
	str r0, [sp, #0x1c]
	cmp r0, #3
	blt _021EA7F2
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	cmp r0, #9
	beq _021EA87E
	ldr r0, [r4]
	bl FUN_0201FDEC
_021EA87E:
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EA884
MOD05_021EA884: ; 0x021EA884
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #7
	bls _021EA896
	b _021EAAC6
_021EA896:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EA8A2: ; jump table
	.short _021EA8B2 - _021EA8A2 - 2 ; case 0
	.short _021EA93E - _021EA8A2 - 2 ; case 1
	.short _021EA958 - _021EA8A2 - 2 ; case 2
	.short _021EA964 - _021EA8A2 - 2 ; case 3
	.short _021EA996 - _021EA8A2 - 2 ; case 4
	.short _021EA9C8 - _021EA8A2 - 2 ; case 5
	.short _021EAA38 - _021EA8A2 - 2 ; case 6
	.short _021EAA7C - _021EA8A2 - 2 ; case 7
_021EA8B2:
	mov r1, #0x69
	mov r0, #4
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x69
	str r0, [r4, #0xc]
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	ldr r5, [r4, #0xc]
	mov r1, #1
	add r0, r5, #0
	add r0, #0x2c
	add r2, r1, #0
	bl MOD05_021E3E14
	mov r0, #5
	str r0, [sp]
	mov r0, #7
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	ldr r0, _021EAAD8 ; =0x000927C0
	mov r1, #0x5a
	str r0, [sp, #0xc]
	add r0, r5, #0
	lsl r1, r1, #2
	add r0, #0x2c
	add r1, r5, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	mov r0, #0
	str r0, [sp]
	mov r1, #0x5a
	str r0, [sp, #4]
	add r0, r5, #0
	lsl r1, r1, #2
	mov r2, #2
	mov r3, #6
	add r0, #0x2c
	add r1, r5, r1
	lsl r2, r2, #0x12
	lsl r3, r3, #0x10
	bl MOD05_021E3FC4
	mov r1, #0x67
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_02020398
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021EAAC6
_021EA93E:
	mov r1, #0x10
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r4, #4
	bl MOD05_021E3474
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021EAAC6
_021EA958:
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _021EA9AE
	add r0, r0, #1
	str r0, [r4]
	b _021EAAC6
_021EA964:
	add r0, r5, #0
	mov r1, #0
	mov r2, #0x10
	mov r3, #0xc
	bl MOD05_021E35B0
	ldr r3, [r5]
	mov r0, #0x10
	sub r0, r0, r3
	str r0, [sp]
	ldr r0, _021EAADC ; =0x04000050
	mov r1, #0
	mov r2, #0xf
	bl G2x_SetBlendAlpha_
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021EAAC6
_021EA996:
	add r0, r5, #0
	bl MOD05_021E35C0
	ldr r2, [r5]
	mov r1, #0x10
	sub r1, r1, r2
	lsl r1, r1, #8
	orr r1, r2
	ldr r2, _021EAAE0 ; =0x04000052
	cmp r0, #1
	strh r1, [r2]
	beq _021EA9B0
_021EA9AE:
	b _021EAAC6
_021EA9B0:
	mov r1, #0
	sub r0, r2, #2
	strh r1, [r0]
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02020398
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021EAAC6
_021EA9C8:
	mov r0, #6
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	ldr r2, _021EAAE4 ; =0x0000019A
	add r0, #0x14
	lsl r1, r1, #0xc
	mov r3, #1
	bl MOD05_021E3644
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #2
	bl FUN_020200EC
	ldr r1, [r5, #0x14]
	add r0, sp, #0x1c
	add r2, r1, #0
	add r3, r1, #0
	bl MOD05_021E3FF8
	add r6, sp, #0x1c
	add r3, sp, #0x34
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	add r1, r2, #0
	str r0, [r3]
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02020064
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r2, #0
	str r0, [sp, #8]
	mov r0, #3
	mov r1, #0x10
	add r3, r2, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021EAAC6
_021EAA38:
	add r0, r5, #0
	add r0, #0x14
	bl MOD05_021E36A4
	ldr r1, [r5, #0x14]
	add r6, r0, #0
	add r0, sp, #0x10
	add r2, r1, #0
	add r3, r1, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x10
	add r2, sp, #0x28
	ldmia r3!, {r0, r1}
	add r7, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r7, #0
	str r0, [r2]
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02020064
	cmp r6, #1
	bne _021EAAC6
	bl FUN_0200E308
	cmp r0, #1
	bne _021EAAC6
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021EAAC6
_021EAA7C:
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021EAA98
	mov r0, #1
	str r0, [r1]
_021EAA98:
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0201FFC8
	mov r1, #0x5a
	add r0, r5, #0
	lsl r1, r1, #2
	add r0, #0x2c
	add r1, r5, r1
	bl MOD05_021E3F3C
	add r0, r5, #0
	add r0, #0x2c
	bl MOD05_021E3E44
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
_021EAAC6:
	ldr r0, [r4]
	cmp r0, #7
	beq _021EAAD2
	ldr r0, [r5, #0x2c]
	bl FUN_0201FDEC
_021EAAD2:
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021EAAD8: .word 0x000927C0
_021EAADC: .word 0x04000050
_021EAAE0: .word 0x04000052
_021EAAE4: .word 0x0000019A

	thumb_func_start MOD05_021EAAE8
MOD05_021EAAE8: ; 0x021EAAE8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r6, r1, #0
	str r0, [sp, #0x10]
	ldr r0, [r6]
	ldr r4, [r6, #0xc]
	cmp r0, #7
	bhi _021EABBC
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EAB04: ; jump table
	.short _021EAB14 - _021EAB04 - 2 ; case 0
	.short _021EAB9C - _021EAB04 - 2 ; case 1
	.short _021EABB6 - _021EAB04 - 2 ; case 2
	.short _021EABC4 - _021EAB04 - 2 ; case 3
	.short _021EAC0E - _021EAB04 - 2 ; case 4
	.short _021EACC0 - _021EAB04 - 2 ; case 5
	.short _021EACEA - _021EAB04 - 2 ; case 6
	.short _021EACFA - _021EAB04 - 2 ; case 7
_021EAB14:
	mov r1, #0x1b
	mov r0, #4
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r2, #0x1b
	str r0, [r6, #0xc]
	mov r1, #0
	lsl r2, r2, #4
	bl memset
	ldr r4, [r6, #0xc]
	mov r1, #4
	add r0, r4, #0
	mov r2, #1
	bl MOD05_021E3E14
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, _021EAD5C ; =0x000927C0
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	mov r7, #0
	add r5, r4, #0
_021EAB5A:
	mov r0, #0
	mov r1, #0x4f
	str r0, [sp]
	lsl r1, r1, #2
	mov r2, #2
	mov r3, #6
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r4, r1
	lsl r2, r2, #0x12
	lsl r3, r3, #0x10
	bl MOD05_021E3FC4
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add r7, r7, #1
	add r5, r5, #4
	cmp r7, #4
	blt _021EAB5A
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021EAD4C
_021EAB9C:
	mov r1, #0x10
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r6, #4
	bl MOD05_021E3474
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021EAD4C
_021EABB6:
	ldr r1, [r6, #4]
	cmp r1, #0
	bne _021EABBE
_021EABBC:
	b _021EAD4C
_021EABBE:
	add r0, r0, #1
	str r0, [r6]
	b _021EAD4C
_021EABC4:
	mov r3, #6
	mov r2, #4
	lsl r3, r3, #6
	str r2, [sp]
	add r0, r4, r3
	mov r1, #0
	lsl r2, r2, #0x11
	add r3, #0x1a
	bl MOD05_021E3644
	mov r3, #0x66
	mov r0, #4
	mov r2, #0xa
	lsl r3, r3, #2
	str r0, [sp]
	add r0, r4, r3
	mov r1, #0
	lsl r2, r2, #0x10
	add r3, r3, #2
	bl MOD05_021E3644
	mov r7, #0
	add r5, r4, #0
_021EABF2:
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	add r7, r7, #1
	add r5, r5, #4
	cmp r7, #4
	blt _021EABF2
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021EAD4C
_021EAC0E:
	mov r0, #6
	lsl r0, r0, #6
	mov r7, #0
	add r5, r4, r0
_021EAC16:
	add r0, r5, #0
	bl MOD05_021E36A4
	add r7, r7, #1
	add r5, #0x18
	str r0, [sp, #0x14]
	cmp r7, #2
	blt _021EAC16
	mov r2, #6
	lsl r2, r2, #6
	ldr r3, [r4, r2]
	mov r1, #2
	lsl r2, r2, #0xa
	sub r2, r2, r3
	add r0, sp, #0x18
	lsl r1, r1, #0x12
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x18
	bl FUN_02020044
	mov r2, #6
	lsl r2, r2, #6
	ldr r3, [r4, r2]
	mov r1, #2
	lsl r2, r2, #0xa
	add r2, r3, r2
	add r0, sp, #0x18
	lsl r1, r1, #0x12
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x18
	bl FUN_02020044
	mov r1, #0x66
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	mov r1, #2
	lsl r1, r1, #0x12
	sub r1, r1, r2
	mov r2, #6
	add r0, sp, #0x18
	lsl r2, r2, #0x10
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x18
	bl FUN_02020044
	mov r1, #0x66
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	mov r1, #2
	lsl r1, r1, #0x12
	add r1, r2, r1
	mov r2, #6
	add r0, sp, #0x18
	lsl r2, r2, #0x10
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x18
	bl FUN_02020044
	ldr r0, [sp, #0x14]
	cmp r0, #1
	bne _021EAD4C
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021EAD4C
_021EACC0:
	ldr r0, [r6, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r2, #0
	str r0, [sp, #8]
	mov r0, #3
	mov r1, #0x22
	add r3, r2, #0
	bl FUN_0200E1D0
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021EAD4C
_021EACEA:
	bl FUN_0200E308
	cmp r0, #1
	bne _021EAD4C
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021EAD4C
_021EACFA:
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, [r6, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r1, [r6, #0x14]
	cmp r1, #0
	beq _021EAD16
	mov r0, #1
	str r0, [r1]
_021EAD16:
	mov r7, #0
	add r5, r4, #0
_021EAD1A:
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_0201FFC8
	add r7, r7, #1
	add r5, r5, #4
	cmp r7, #4
	blt _021EAD1A
	mov r1, #0x4f
	lsl r1, r1, #2
	add r0, r4, #0
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	bl MOD05_021E3E44
	ldr r1, [r6, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	ldr r0, [sp, #0x10]
	bl FUN_0200621C
_021EAD4C:
	ldr r0, [r6]
	cmp r0, #7
	beq _021EAD58
	ldr r0, [r4]
	bl FUN_0201FDEC
_021EAD58:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021EAD5C: .word 0x000927C0

	thumb_func_start MOD05_021EAD60
MOD05_021EAD60: ; 0x021EAD60
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x48
	str r0, [sp, #0x10]
	add r0, r1, #0
	ldr r0, [r0]
	str r1, [sp, #0x14]
	ldr r4, [r1, #0xc]
	cmp r0, #7
	bhi _021EAE6E
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EAD7E: ; jump table
	.short _021EAD8E - _021EAD7E - 2 ; case 0
	.short _021EAE1A - _021EAD7E - 2 ; case 1
	.short _021EAE3A - _021EAD7E - 2 ; case 2
	.short _021EAE5E - _021EAD7E - 2 ; case 3
	.short _021EAF9C - _021EAD7E - 2 ; case 4
	.short _021EAFAE - _021EAD7E - 2 ; case 5
	.short _021EAFDE - _021EAD7E - 2 ; case 6
	.short _021EAFF2 - _021EAD7E - 2 ; case 7
_021EAD8E:
	mov r1, #0x3d
	mov r0, #4
	lsl r1, r1, #4
	bl AllocFromHeap
	ldr r1, [sp, #0x14]
	mov r2, #0x3d
	str r0, [r1, #0xc]
	mov r1, #0
	lsl r2, r2, #4
	bl memset
	ldr r0, [sp, #0x14]
	mov r1, #6
	ldr r4, [r0, #0xc]
	mov r2, #1
	add r0, r4, #0
	bl MOD05_021E3E14
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, _021EB138 ; =0x000927C0
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	mov r7, #0x4f
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #2
_021EADDC:
	mov r0, #0
	str r0, [sp]
	mov r2, #0
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r4, r7
	add r3, r2, #0
	bl MOD05_021E3FC4
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #6
	blt _021EADDC
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021EB04A
_021EAE1A:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	add r1, r0, #0
	ldr r3, [sp, #0x14]
	sub r1, #0x11
	add r2, r1, #0
	add r3, r3, #4
	bl MOD05_021E3474
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021EB04A
_021EAE3A:
	ldr r1, [sp, #0x14]
	ldr r1, [r1, #4]
	cmp r1, #0
	beq _021EAE6E
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	mov r0, #0xf2
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	add r0, r0, #4
	lsl r2, r1, #5
	ldr r1, _021EB13C ; =UNK05_021F7A50
	ldr r1, [r1, r2]
	str r1, [r4, r0]
	b _021EB04A
_021EAE5E:
	mov r0, #0xf3
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0
	blt _021EAE70
_021EAE6E:
	b _021EB04A
_021EAE70:
	sub r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #8
	str r1, [sp]
	mov r1, #0x86
	lsl r1, r1, #2
	add r2, r4, r1
	mov r1, #0x18
	mul r1, r0
	lsl r3, r0, #5
	add r0, r2, r1
	ldr r1, _021EB140 ; =UNK05_021F7A38
	ldr r2, _021EB144 ; =UNK05_021F7A3C
	ldr r5, _021EB148 ; =UNK05_021F7A40
	ldr r1, [r1, r3]
	ldr r2, [r2, r3]
	ldr r3, [r5, r3]
	bl MOD05_021E3644
	mov r0, #0xf2
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #8
	str r1, [sp]
	mov r1, #0xaa
	lsl r1, r1, #2
	add r2, r4, r1
	mov r1, #0x18
	mul r1, r0
	lsl r3, r0, #5
	add r0, r2, r1
	ldr r1, _021EB14C ; =UNK05_021F7A44
	ldr r2, _021EB150 ; =UNK05_021F7A48
	ldr r5, _021EB154 ; =UNK05_021F7A4C
	ldr r1, [r1, r3]
	ldr r2, [r2, r3]
	ldr r3, [r5, r3]
	bl MOD05_021E3644
	mov r0, #0x62
	lsl r0, r0, #2
	mov r1, #8
	add r3, r4, r0
	mov r0, #0xf2
	str r1, [sp]
	lsl r0, r0, #2
	ldr r2, [r4, r0]
	mov r0, #0x18
	mul r0, r2
	add r0, r3, r0
	ldr r3, _021EB158 ; =0xFFFFF99A
	lsl r1, r1, #0xa
	mov r2, #0x29
	bl MOD05_021E3644
	mov r0, #0xf2
	lsl r0, r0, #2
	ldr r2, [r4, r0]
	sub r0, #0x90
	add r1, r4, r0
	mov r0, #0x14
	mul r0, r2
	lsl r3, r2, #5
	ldr r2, _021EB15C ; =UNK05_021F7A54
	add r0, r1, r0
	ldr r2, [r2, r3]
	mov r1, #0
	mov r3, #8
	bl MOD05_021E35B0
	mov r0, #0xf2
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	lsl r0, r0, #2
	add r1, r4, r0
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xf2
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r1, _021EB140 ; =UNK05_021F7A38
	lsl r3, r0, #5
	ldr r2, _021EB14C ; =UNK05_021F7A44
	ldr r1, [r1, r3]
	ldr r2, [r2, r3]
	add r0, sp, #0x3c
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0xf2
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	lsl r0, r0, #2
	add r1, r4, r0
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, sp, #0x3c
	bl FUN_02020044
	mov r1, #2
	lsl r1, r1, #0xc
	add r0, sp, #0x30
	add r2, r1, #0
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0xf2
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r2, #2
	lsl r0, r0, #2
	add r1, r4, r0
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, sp, #0x30
	bl FUN_02020074
	mov r1, #0xf2
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	mov r3, #1
	lsl r0, r0, #2
	add r2, r4, r0
	add r0, r1, #0
	sub r0, #0x18
	str r3, [r2, r0]
	ldr r0, [r4, r1]
	add r0, r0, #1
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	cmp r0, #6
	blt _021EAF90
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021EB04A
_021EAF90:
	lsl r2, r0, #5
	ldr r0, _021EB13C ; =UNK05_021F7A50
	ldr r2, [r0, r2]
	add r0, r1, #4
	str r2, [r4, r0]
	b _021EB04A
_021EAF9C:
	mov r1, #0xf1
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	cmp r1, #0
	bne _021EB04A
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021EB04A
_021EAFAE:
	ldr r0, [sp, #0x14]
	ldr r0, [r0, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	mov r0, #0xc
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r2, #0
	str r0, [sp, #8]
	mov r0, #3
	mov r1, #0x22
	add r3, r2, #0
	bl FUN_0200E1D0
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021EB04A
_021EAFDE:
	bl FUN_0200E308
	cmp r0, #0
	beq _021EB04A
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021EB04A
_021EAFF2:
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, [sp, #0x14]
	ldr r0, [r0, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r0, [sp, #0x14]
	ldr r1, [r0, #0x14]
	cmp r1, #0
	beq _021EB012
	mov r0, #1
	str r0, [r1]
_021EB012:
	mov r7, #0x17
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #4
_021EB01A:
	ldr r0, [r5, r7]
	bl FUN_0201FFC8
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #6
	blt _021EB01A
	mov r1, #0x4f
	lsl r1, r1, #2
	add r0, r4, #0
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	bl MOD05_021E3E44
	ldr r1, [sp, #0x14]
	mov r0, #4
	ldr r1, [r1, #0xc]
	bl FreeToHeapExplicit
	ldr r0, [sp, #0x10]
	bl FUN_0200621C
_021EB04A:
	mov r1, #0x86
	mov r0, #0
	lsl r1, r1, #2
	str r0, [sp, #0x18]
	add r0, r4, r1
	str r0, [sp, #0x28]
	add r0, r1, #0
	add r0, #0x90
	add r0, r4, r0
	sub r1, #0x90
	str r0, [sp, #0x24]
	add r0, r4, r1
	str r0, [sp, #0x20]
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r4, r0
	add r5, r4, #0
	str r0, [sp, #0x1c]
	add r6, r4, #0
	add r7, r4, #0
_021EB072:
	mov r0, #0x3b
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	cmp r0, #1
	bne _021EB0FE
	ldr r0, [sp, #0x28]
	bl MOD05_021E36A4
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x24]
	bl MOD05_021E36A4
	ldr r0, [sp, #0x20]
	bl MOD05_021E36A4
	ldr r0, [sp, #0x1c]
	bl MOD05_021E35C0
	ldr r0, [sp, #0x2c]
	cmp r0, #0
	beq _021EB0AE
	mov r0, #0x3b
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r5, r0]
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_020200A0
_021EB0AE:
	mov r1, #0x86
	mov r2, #0xaa
	lsl r1, r1, #2
	lsl r2, r2, #2
	ldr r1, [r6, r1]
	ldr r2, [r6, r2]
	add r0, sp, #0x3c
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, sp, #0x3c
	bl FUN_02020044
	mov r0, #0x62
	lsl r0, r0, #2
	ldr r1, [r6, r0]
	add r0, sp, #0x30
	add r2, r1, #0
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, sp, #0x30
	bl FUN_02020064
	mov r1, #0xce
	lsl r1, r1, #2
	mov r0, #0x17
	ldr r1, [r7, r1]
	lsl r0, r0, #4
	lsl r1, r1, #0x10
	ldr r0, [r5, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
_021EB0FE:
	ldr r0, [sp, #0x28]
	add r5, r5, #4
	add r0, #0x18
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x24]
	add r6, #0x18
	add r0, #0x18
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x20]
	add r7, #0x14
	add r0, #0x18
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r0, #0x14
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, #6
	blt _021EB072
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	cmp r0, #7
	beq _021EB134
	ldr r0, [r4]
	bl FUN_0201FDEC
_021EB134:
	add sp, #0x48
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EB138: .word 0x000927C0
_021EB13C: .word UNK05_021F7A50
_021EB140: .word UNK05_021F7A38
_021EB144: .word UNK05_021F7A3C
_021EB148: .word UNK05_021F7A40
_021EB14C: .word UNK05_021F7A44
_021EB150: .word UNK05_021F7A48
_021EB154: .word UNK05_021F7A4C
_021EB158: .word 0xFFFFF99A
_021EB15C: .word UNK05_021F7A54

	thumb_func_start MOD05_021EB160
MOD05_021EB160: ; 0x021EB160
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5]
	ldr r4, [r5, #0xc]
	cmp r0, #7
	bls _021EB172
	b _021EB3F2
_021EB172:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EB17E: ; jump table
	.short _021EB18E - _021EB17E - 2 ; case 0
	.short _021EB272 - _021EB17E - 2 ; case 1
	.short _021EB28C - _021EB17E - 2 ; case 2
	.short _021EB29A - _021EB17E - 2 ; case 3
	.short _021EB2D4 - _021EB17E - 2 ; case 4
	.short _021EB312 - _021EB17E - 2 ; case 5
	.short _021EB344 - _021EB17E - 2 ; case 6
	.short _021EB374 - _021EB17E - 2 ; case 7
_021EB18E:
	mov r1, #0x6f
	mov r0, #4
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x6f
	str r0, [r5, #0xc]
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	ldr r4, [r5, #0xc]
	mov r1, #1
	add r0, r4, #0
	add r0, #8
	add r2, r1, #0
	bl MOD05_021E3E14
	mov r0, #8
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #9
	str r0, [sp, #8]
	ldr r0, _021EB404 ; =0x000927C0
	mov r1, #0x51
	str r0, [sp, #0xc]
	add r0, r4, #0
	lsl r1, r1, #2
	mov r2, #1
	add r0, #8
	add r1, r4, r1
	add r3, r2, #0
	bl MOD05_021E3E64
	mov r0, #0
	str r0, [sp]
	mov r1, #0x51
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r1, r1, #2
	mov r2, #2
	mov r3, #6
	add r0, #8
	add r1, r4, r1
	lsl r2, r2, #0x12
	lsl r3, r3, #0x10
	bl MOD05_021E3FC4
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_02020398
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_02020238
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #4
	bl MOD05_021E4688
	str r0, [r4, #4]
	mov r0, #4
	mov r1, #1
	bl AllocWindows
	str r0, [r4]
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r0, [r5, #0x10]
	ldr r1, [r4]
	ldr r0, [r0, #8]
	mov r2, #3
	bl FUN_02019064
	mov r1, #0
	add r0, sp, #0x14
	strh r1, [r0]
	mov r0, #3
	add r1, sp, #0x14
	mov r2, #2
	mov r3, #0x1e
	bl FUN_02017FB4
	ldr r0, [r4]
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, [r4]
	bl FUN_02019220
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EB3F2
_021EB272:
	mov r1, #0x10
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r5, #4
	bl MOD05_021E3474
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EB3F2
_021EB28C:
	ldr r1, [r5, #4]
	cmp r1, #0
	bne _021EB294
	b _021EB3F2
_021EB294:
	add r0, r0, #1
	str r0, [r5]
	b _021EB3F2
_021EB29A:
	mov r0, #0x19
	lsl r0, r0, #4
	add r0, r4, r0
	mov r1, #0
	mov r2, #0x10
	mov r3, #0xf
	bl MOD05_021E35B0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r3, [r4, r0]
	mov r0, #0x10
	sub r0, r0, r3
	str r0, [sp]
	ldr r0, _021EB408 ; =0x04000050
	mov r1, #0
	mov r2, #0xf
	bl G2x_SetBlendAlpha_
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EB3F2
_021EB2D4:
	mov r0, #0x19
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD05_021E35C0
	mov r2, #0x19
	lsl r2, r2, #4
	ldr r1, [r4, r2]
	mov r3, #0x10
	sub r3, r3, r1
	lsl r3, r3, #8
	orr r1, r3
	ldr r3, _021EB40C ; =0x04000052
	cmp r0, #1
	strh r1, [r3]
	bne _021EB3F2
	mov r1, #0
	sub r0, r3, #2
	sub r2, #0x18
	strh r1, [r0]
	ldr r0, [r4, r2]
	bl FUN_02020398
	ldr r0, [r5]
	mov r1, #0x10
	add r0, r0, #1
	str r0, [r5]
	mov r0, #0x6e
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021EB3F2
_021EB312:
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0
	bgt _021EB3F2
	sub r0, #0x3c
	add r0, r4, r0
	mov r1, #0
	mov r2, #0xe
	mov r3, #0x10
	bl MOD05_021E35B0
	ldr r0, [r4, #4]
	ldr r2, [r4]
	mov r1, #0x10
	mov r3, #0xf
	bl MOD05_021E46D4
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EB3F2
_021EB344:
	mov r0, #0x5f
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD05_021E35C0
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	lsl r0, r1, #4
	orr r1, r0
	ldr r0, _021EB410 ; =0x0400004D
	strb r1, [r0]
	ldr r0, [r4, #4]
	bl MOD05_021E4754
	cmp r0, #0
	beq _021EB36C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
_021EB36C:
	ldr r0, [r4]
	bl FUN_02019220
	b _021EB3F2
_021EB374:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, [r4, #4]
	bl MOD05_021E46B4
	ldr r1, [r5, #0x14]
	cmp r1, #0
	beq _021EB394
	mov r0, #1
	str r0, [r1]
_021EB394:
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201FFC8
	mov r1, #0x51
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #8
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	add r0, #8
	bl MOD05_021E3E44
	ldr r0, [r4]
	bl FUN_02019570
	ldr r0, [r4]
	bl FUN_02019178
	ldr r0, [r4]
	mov r1, #1
	bl FUN_020191A4
	mov r0, #3
	mov r1, #0x20
	mov r2, #0
	mov r3, #4
	bl FUN_02017F18
	ldr r0, [r5, #0x10]
	mov r1, #3
	ldr r0, [r0, #8]
	bl FUN_02018744
	ldr r0, _021EB410 ; =0x0400004D
	mov r1, #0
	strb r1, [r0]
	ldr r1, [r5, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
_021EB3F2:
	ldr r0, [r5]
	cmp r0, #7
	beq _021EB3FE
	ldr r0, [r4, #8]
	bl FUN_0201FDEC
_021EB3FE:
	add sp, #0x18
	pop {r4, r5, r6, pc}
	nop
_021EB404: .word 0x000927C0
_021EB408: .word 0x04000050
_021EB40C: .word 0x04000052
_021EB410: .word 0x0400004D

	thumb_func_start MOD05_021EB414
MOD05_021EB414: ; 0x021EB414
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4, #8]
	ldr r1, [r5, #0x20]
	bl FUN_0201EEF0
	ldr r0, [r4]
	ldr r1, [r5, #0x20]
	bl FUN_0201EFE0
	ldrh r1, [r4, #4]
	add r0, sp, #0
	strh r1, [r0]
	ldrh r1, [r4, #6]
	strh r1, [r0, #2]
	mov r1, #0
	strh r1, [r0, #4]
	ldr r1, [r5, #0x20]
	add r0, sp, #0
	bl FUN_0201EF90
	add sp, #8
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EB448
MOD05_021EB448: ; 0x021EB448
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #7
	bls _021EB45A
	b _021EB5A0
_021EB45A:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EB466: ; jump table
	.short _021EB476 - _021EB466 - 2 ; case 0
	.short _021EB4AE - _021EB466 - 2 ; case 1
	.short _021EB4C6 - _021EB466 - 2 ; case 2
	.short _021EB4D4 - _021EB466 - 2 ; case 3
	.short _021EB4F8 - _021EB466 - 2 ; case 4
	.short _021EB534 - _021EB466 - 2 ; case 5
	.short _021EB556 - _021EB466 - 2 ; case 6
	.short _021EB56C - _021EB466 - 2 ; case 7
_021EB476:
	mov r0, #4
	mov r1, #0x10
	bl AllocFromHeap
	str r0, [r4, #0xc]
	mov r2, #0x10
	mov r1, #0
_021EB484:
	strb r1, [r0]
	add r0, r0, #1
	sub r2, r2, #1
	bne _021EB484
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #8
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB4AE:
	mov r0, #1
	mov r1, #0x10
	str r0, [sp]
	add r2, r1, #0
	add r3, r4, #4
	bl MOD05_021E3474
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB4C6:
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _021EB5A0
	add r0, r0, #1
	add sp, #0xc
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB4D4:
	mov r0, #3
	mov r1, #0xf
	bl MOD05_021E8860
	mov r2, #0
	str r0, [r5]
	mov r0, #0xc
	add r1, r2, #0
	mul r1, r0
	ldr r0, _021EB5A4 ; =UNK05_021F7982
	str r2, [r5, #8]
	ldrh r0, [r0, r1]
	add sp, #0xc
	str r0, [r5, #0xc]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB4F8:
	ldr r0, [r5, #0xc]
	sub r0, r0, #1
	str r0, [r5, #0xc]
	bpl _021EB5A0
	ldr r2, [r5, #8]
	mov r1, #0xc
	ldr r3, _021EB5A8 ; =UNK05_021F7978
	mul r1, r2
	ldr r0, [r4, #0x10]
	add r1, r3, r1
	bl MOD05_021EB414
	ldr r0, [r5, #8]
	add r2, r0, #1
	str r2, [r5, #8]
	cmp r2, #0x10
	blo _021EB524
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB524:
	mov r0, #0xc
	add r1, r2, #0
	mul r1, r0
	ldr r0, _021EB5A4 ; =UNK05_021F7982
	add sp, #0xc
	ldrh r0, [r0, r1]
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, pc}
_021EB534:
	mov r0, #0xa
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r1, #0
	str r0, [sp, #8]
	ldr r3, _021EB5AC ; =0x00007FFF
	mov r0, #3
	add r2, r1, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB556:
	bl FUN_0200E308
	cmp r0, #0
	beq _021EB5A0
	mov r0, #0
	str r0, [r4, #4]
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB56C:
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	add r0, r5, #0
	bl MOD05_021E88C0
	ldr r0, _021EB5B0 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021EB58A
	mov r0, #1
	str r0, [r1]
_021EB58A:
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
_021EB5A0:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0
_021EB5A4: .word UNK05_021F7982
_021EB5A8: .word UNK05_021F7978
_021EB5AC: .word 0x00007FFF
_021EB5B0: .word 0x04000050

	thumb_func_start MOD05_021EB5B4
MOD05_021EB5B4: ; 0x021EB5B4
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #9
	bhi _021EB636
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EB5D0: ; jump table
	.short _021EB5E4 - _021EB5D0 - 2 ; case 0
	.short _021EB618 - _021EB5D0 - 2 ; case 1
	.short _021EB630 - _021EB5D0 - 2 ; case 2
	.short _021EB640 - _021EB5D0 - 2 ; case 3
	.short _021EB66E - _021EB5D0 - 2 ; case 4
	.short _021EB698 - _021EB5D0 - 2 ; case 5
	.short _021EB6C6 - _021EB5D0 - 2 ; case 6
	.short _021EB6E8 - _021EB5D0 - 2 ; case 7
	.short _021EB70A - _021EB5D0 - 2 ; case 8
	.short _021EB720 - _021EB5D0 - 2 ; case 9
_021EB5E4:
	mov r0, #4
	mov r1, #0x38
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x38
	str r0, [r4, #0xc]
	bl memset
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #8
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB618:
	mov r0, #1
	mov r1, #0x10
	str r0, [sp]
	add r2, r1, #0
	add r3, r4, #4
	bl MOD05_021E3474
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB630:
	ldr r1, [r4, #4]
	cmp r1, #0
	bne _021EB638
_021EB636:
	b _021EB754
_021EB638:
	add r0, r0, #1
	add sp, #0xc
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB640:
	mov r0, #5
	mov r1, #0xd
	bl MOD05_021E8860
	str r0, [r5]
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	bl FUN_0201F008
	mov r2, #1
	add r1, r0, #0
	add r5, #8
	lsl r2, r2, #8
	add r0, r5, #0
	add r2, r1, r2
	mov r3, #0x28
	bl MOD05_021E35B0
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB66E:
	add r0, r5, #0
	add r0, #8
	bl MOD05_021E35C0
	add r6, r0, #0
	ldr r0, [r5, #8]
	ldr r1, [r4, #0x10]
	lsl r0, r0, #0x10
	ldr r1, [r1, #0x20]
	lsr r0, r0, #0x10
	bl FUN_0201EEF0
	cmp r6, #1
	bne _021EB754
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	mov r0, #5
	str r0, [r5, #0x34]
	pop {r3, r4, r5, r6, pc}
_021EB698:
	ldr r0, [r5, #0x34]
	sub r0, r0, #1
	str r0, [r5, #0x34]
	bpl _021EB754
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	bl FUN_0201F010
	mov r3, #8
	str r3, [sp]
	ldr r2, _021EB758 ; =0x0092E000
	add r1, r0, #0
	add r5, #0x1c
	add r0, r5, #0
	sub r2, r1, r2
	lsl r3, r3, #8
	bl MOD05_021E3644
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB6C6:
	add r0, r5, #0
	add r0, #0x1c
	bl MOD05_021E36A4
	ldr r1, [r4, #0x10]
	add r6, r0, #0
	ldr r0, [r5, #0x1c]
	ldr r1, [r1, #0x20]
	bl FUN_0201EFE0
	cmp r6, #1
	bne _021EB754
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB6E8:
	mov r0, #0x3c
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r1, #0
	str r0, [sp, #8]
	ldr r3, _021EB75C ; =0x00007FFF
	mov r0, #3
	add r2, r1, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB70A:
	bl FUN_0200E308
	cmp r0, #0
	beq _021EB754
	mov r0, #0
	str r0, [r4, #4]
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB720:
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	add r0, r5, #0
	bl MOD05_021E88C0
	ldr r0, _021EB760 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021EB73E
	mov r0, #1
	str r0, [r1]
_021EB73E:
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
_021EB754:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0
_021EB758: .word 0x0092E000
_021EB75C: .word 0x00007FFF
_021EB760: .word 0x04000050

	thumb_func_start MOD05_021EB764
MOD05_021EB764: ; 0x021EB764
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r5, r0, #0
	str r1, [sp, #0x14]
	ldr r1, [r5]
	add r6, r2, #0
	ldr r4, [r5, #0xc]
	cmp r1, #0xe
	bls _021EB778
	b _021EBB72
_021EB778:
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021EB784: ; jump table
	.short _021EB7A2 - _021EB784 - 2 ; case 0
	.short _021EB848 - _021EB784 - 2 ; case 1
	.short _021EB85E - _021EB784 - 2 ; case 2
	.short _021EB86A - _021EB784 - 2 ; case 3
	.short _021EB8B8 - _021EB784 - 2 ; case 4
	.short _021EB8D6 - _021EB784 - 2 ; case 5
	.short _021EB99C - _021EB784 - 2 ; case 6
	.short _021EB9EE - _021EB784 - 2 ; case 7
	.short _021EBA04 - _021EB784 - 2 ; case 8
	.short _021EBA34 - _021EB784 - 2 ; case 9
	.short _021EBA4A - _021EB784 - 2 ; case 10
	.short _021EBA72 - _021EB784 - 2 ; case 11
	.short _021EBA8A - _021EB784 - 2 ; case 12
	.short _021EBAAA - _021EB784 - 2 ; case 13
	.short _021EBB0E - _021EB784 - 2 ; case 14
_021EB7A2:
	mov r1, #0x1f
	ldr r0, [sp, #0x14]
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r2, #0x1f
	str r0, [r5, #0xc]
	mov r1, #0
	lsl r2, r2, #4
	bl memset
	ldr r4, [r5, #0xc]
	mov r1, #1
	add r0, r4, #0
	add r0, #0x44
	add r2, r1, #0
	bl MOD05_021E3E14
	mov r0, #0x17
	str r0, [sp]
	mov r1, #0x18
	str r1, [sp, #4]
	mov r0, #0x19
	str r0, [sp, #8]
	ldr r0, _021EBB4C ; =0x000927C0
	lsl r1, r1, #4
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0x44
	add r1, r4, r1
	mov r2, #0x16
	mov r3, #1
	bl MOD05_021E3E64
	mov r0, #0
	str r0, [sp]
	mov r1, #6
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r1, r1, #6
	mov r3, #0x11
	ldr r2, _021EBB50 ; =0xFFFE0000
	add r0, #0x44
	add r1, r4, r1
	lsl r3, r3, #0xe
	bl MOD05_021E3FC4
	mov r1, #0x6d
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r0, #0
	str r0, [sp]
	ldrh r0, [r6, #6]
	ldr r1, [sp, #0x14]
	mov r3, #0xa
	str r0, [sp, #4]
	mov r0, #0x6d
	lsl r0, r0, #2
	ldrh r2, [r6, #4]
	ldr r0, [r4, r0]
	bl MOD05_021E4014
	ldr r0, [r5, #0x10]
	ldr r0, [r0, #8]
	bl MOD05_021E3C00
	bl MOD05_021E4788
	str r0, [r4, #0x40]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EB848:
	mov r0, #1
	mov r1, #0x10
	str r0, [sp]
	add r2, r1, #0
	add r3, r5, #4
	bl MOD05_021E3474
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EB85E:
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _021EB8E6
	add r0, r1, #1
	str r0, [r5]
	b _021EBB72
_021EB86A:
	ldr r3, [r5, #0x10]
	mov r0, #0xd
	ldr r3, [r3, #8]
	mov r1, #0xc
	mov r2, #0xb
	bl MOD05_021E3D20
	mov r0, #0x79
	mov r2, #8
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0x1f
	str r0, [sp, #4]
	mov r0, #0x17
	str r0, [sp, #8]
	ldr r1, [r4, #0x40]
	add r0, r5, #0
	add r3, r2, #0
	bl MOD05_021E47BC
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r0, #0x2c
	add r2, r1, #0
	mov r3, #0xf
	bl MOD05_021E35EC
	mov r0, #8
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EB8B8:
	bl MOD05_021E35AC
	cmp r0, #0
	beq _021EB8E6
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	ldr r0, [r4, #0x40]
	bl MOD05_021E47A0
	mov r0, #0x7b
	mov r1, #0xa
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021EBB72
_021EB8D6:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	blt _021EB8E8
_021EB8E6:
	b _021EBB72
_021EB8E8:
	mov r1, #2
	lsl r1, r1, #0xc
	add r0, sp, #0x18
	add r2, r1, #0
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x18
	bl FUN_02020064
	mov r0, #0
	str r0, [sp]
	mov r0, #0x6e
	lsl r0, r0, #2
	add r0, r4, r0
	str r0, [sp, #4]
	mov r0, #0x11
	mov r2, #2
	lsl r0, r0, #0xe
	mov r1, #0x62
	lsl r2, r2, #0xc
	mov r3, #0x40
	bl MOD05_021E49F0
	ldr r3, _021EBB54 ; =0x04000048
	mov r0, #0x3f
	ldrh r2, [r3]
	mov r1, #0x1f
	bic r2, r0
	orr r2, r1
	mov r1, #0x20
	orr r2, r1
	strh r2, [r3]
	ldrh r2, [r3, #2]
	bic r2, r0
	mov r0, #0xf
	orr r0, r2
	orr r0, r1
	strh r0, [r3, #2]
	lsl r0, r1, #0x15
	ldr r3, [r0]
	ldr r2, _021EBB58 ; =0xFFFF1FFF
	lsl r1, r1, #8
	and r2, r3
	orr r1, r2
	str r1, [r0]
	mov r3, #4
	str r3, [sp]
	ldr r1, _021EBB50 ; =0xFFFE0000
	ldr r2, [r6]
	add r0, r4, #0
	lsl r3, r3, #0x10
	bl MOD05_021E3644
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02020238
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r2, #0x11
	ldr r1, [r4]
	add r0, sp, #0x24
	lsl r2, r2, #0xe
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x24
	bl FUN_02020044
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EB99C:
	add r0, r4, #0
	bl MOD05_021E36A4
	mov r2, #0x11
	add r6, r0, #0
	ldr r1, [r4]
	add r0, sp, #0x24
	lsl r2, r2, #0xe
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x24
	bl FUN_02020044
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0202011C
	mov r1, #0
	str r1, [sp]
	mov r1, #0x6e
	lsl r1, r1, #2
	add r1, r4, r1
	str r1, [sp, #4]
	mov r2, #2
	ldr r0, [r0, #4]
	mov r1, #0x62
	lsl r2, r2, #0xc
	mov r3, #0x40
	bl MOD05_021E49F0
	cmp r6, #1
	bne _021EBA60
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EB9EE:
	add r0, r4, #0
	add r0, #0x18
	mov r1, #0
	mov r2, #0x10
	mov r3, #3
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EBA04:
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E35C0
	add r7, r0, #0
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E4AD0
	cmp r7, #1
	bne _021EBA60
	mov r3, #0
	str r3, [sp]
	mov r0, #0x6d
	lsl r0, r0, #2
	ldrh r2, [r6, #4]
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x14]
	bl MOD05_021E3F68
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EBA34:
	add r0, r4, #0
	add r0, #0x18
	mov r1, #0x10
	mov r2, #0
	mov r3, #3
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EBA4A:
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E35C0
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E4AD0
	cmp r6, #1
	beq _021EBA62
_021EBA60:
	b _021EBB72
_021EBA62:
	ldr r0, [r5]
	mov r1, #0x1a
	add r0, r0, #1
	str r0, [r5]
	mov r0, #0x7b
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021EBB72
_021EBA72:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bge _021EBB72
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EBA8A:
	mov r0, #0xf
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r1, #0
	str r0, [sp, #8]
	ldr r3, _021EBB5C ; =0x00007FFF
	mov r0, #3
	add r2, r1, #0
	bl FUN_0200E1D0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EBAAA:
	add r0, r4, #0
	add r0, #0x2c
	bl MOD05_021E35FC
	mov r2, #1
	ldr r3, [r4, #0x2c]
	lsl r2, r2, #0xc
	add r1, r3, r2
	add r2, r3, r2
	add r0, sp, #0x18
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x18
	bl FUN_02020064
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0202011C
	add r6, r0, #0
	ldr r0, [r4, #0x2c]
	mov r1, #0x44
	mov r2, #0x1e
	bl MOD05_021E4A3C
	add r1, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x6e
	lsl r0, r0, #2
	add r0, r4, r0
	str r0, [sp, #4]
	ldr r0, [r6, #4]
	ldr r2, [sp, #0x1c]
	mov r3, #0x40
	bl MOD05_021E49F0
	bl FUN_0200E308
	cmp r0, #0
	beq _021EBB72
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EBB0E:
	ldr r1, _021EBB5C ; =0x00007FFF
	mov r0, #1
	bl FUN_0200E3A0
	ldr r1, [r5, #0x14]
	cmp r1, #0
	beq _021EBB20
	mov r0, #1
	str r0, [r1]
_021EBB20:
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201FFC8
	mov r1, #6
	add r0, r4, #0
	lsl r1, r1, #6
	add r0, #0x44
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r4, #0x44
	add r0, r4, #0
	bl MOD05_021E3E44
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021EBB58 ; =0xFFFF1FFF
	b _021EBB60
	nop
_021EBB4C: .word 0x000927C0
_021EBB50: .word 0xFFFE0000
_021EBB54: .word 0x04000048
_021EBB58: .word 0xFFFF1FFF
_021EBB5C: .word 0x00007FFF
_021EBB60:
	and r0, r1
	str r0, [r2]
	ldr r1, [r5, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add sp, #0x30
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021EBB72:
	mov r1, #0x79
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	cmp r0, #1
	bne _021EBBB6
	ldr r3, [r4, #0x2c]
	mov r0, #0
	str r3, [sp]
	str r0, [sp, #4]
	mov r0, #0x80
	str r0, [sp, #8]
	mov r0, #0x44
	str r0, [sp, #0xc]
	add r0, r1, #4
	ldr r0, [r4, r0]
	sub r1, #0x24
	str r0, [sp, #0x10]
	add r0, r4, r1
	ldr r1, [r5, #0x10]
	mov r2, #3
	ldr r1, [r1, #8]
	bl MOD05_021E3DA0
	mov r3, #0x7a
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	sub r0, #0xf
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x17
	sub r1, r1, r2
	mov r0, #0x17
	ror r1, r0
	add r0, r2, r1
	str r0, [r4, r3]
_021EBBB6:
	ldr r0, [r5]
	cmp r0, #0xe
	beq _021EBBC2
	ldr r0, [r4, #0x44]
	bl FUN_0201FDEC
_021EBBC2:
	mov r0, #0
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021EBBC8
MOD05_021EBBC8: ; 0x021EBBC8
	push {r4, lr}
	ldr r2, _021EBBE4 ; =UNK05_021F7938
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBBE0
	add r0, r4, #0
	bl FUN_0200621C
_021EBBE0:
	pop {r4, pc}
	nop
_021EBBE4: .word UNK05_021F7938

	thumb_func_start MOD05_021EBBE8
MOD05_021EBBE8: ; 0x021EBBE8
	push {r4, lr}
	ldr r2, _021EBC04 ; =UNK05_021F7940
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBC00
	add r0, r4, #0
	bl FUN_0200621C
_021EBC00:
	pop {r4, pc}
	nop
_021EBC04: .word UNK05_021F7940

	thumb_func_start MOD05_021EBC08
MOD05_021EBC08: ; 0x021EBC08
	push {r4, lr}
	ldr r2, _021EBC24 ; =UNK05_021F7948
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBC20
	add r0, r4, #0
	bl FUN_0200621C
_021EBC20:
	pop {r4, pc}
	nop
_021EBC24: .word UNK05_021F7948

	thumb_func_start MOD05_021EBC28
MOD05_021EBC28: ; 0x021EBC28
	push {r4, lr}
	ldr r2, _021EBC44 ; =UNK05_021F7950
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBC40
	add r0, r4, #0
	bl FUN_0200621C
_021EBC40:
	pop {r4, pc}
	nop
_021EBC44: .word UNK05_021F7950

	thumb_func_start MOD05_021EBC48
MOD05_021EBC48: ; 0x021EBC48
	push {r4, lr}
	ldr r2, _021EBC64 ; =UNK05_021F7958
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBC60
	add r0, r4, #0
	bl FUN_0200621C
_021EBC60:
	pop {r4, pc}
	nop
_021EBC64: .word UNK05_021F7958

	thumb_func_start MOD05_021EBC68
MOD05_021EBC68: ; 0x021EBC68
	push {r4, lr}
	ldr r2, _021EBC84 ; =UNK05_021F7960
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBC80
	add r0, r4, #0
	bl FUN_0200621C
_021EBC80:
	pop {r4, pc}
	nop
_021EBC84: .word UNK05_021F7960

	thumb_func_start MOD05_021EBC88
MOD05_021EBC88: ; 0x021EBC88
	push {r4, lr}
	ldr r2, _021EBCA4 ; =UNK05_021F7968
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBCA0
	add r0, r4, #0
	bl FUN_0200621C
_021EBCA0:
	pop {r4, pc}
	nop
_021EBCA4: .word UNK05_021F7968

	thumb_func_start MOD05_021EBCA8
MOD05_021EBCA8: ; 0x021EBCA8
	push {r4, lr}
	ldr r2, _021EBCC4 ; =UNK05_021F7970
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBCC0
	add r0, r4, #0
	bl FUN_0200621C
_021EBCC0:
	pop {r4, pc}
	nop
_021EBCC4: .word UNK05_021F7970

	thumb_func_start MOD05_021EBCC8
MOD05_021EBCC8: ; 0x021EBCC8
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	bl PlayerProfile_GetTrainerGender
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EBCD8
MOD05_021EBCD8: ; 0x021EBCD8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	add r5, r0, #0
	ldr r0, [r5]
	str r1, [sp, #0x10]
	str r2, [sp, #0x14]
	ldr r4, [r5, #0xc]
	cmp r0, #0x13
	bls _021EBCEC
	b _021EC3A0
_021EBCEC:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EBCF8: ; jump table
	.short _021EBD20 - _021EBCF8 - 2 ; case 0
	.short _021EBEC0 - _021EBCF8 - 2 ; case 1
	.short _021EBED6 - _021EBCF8 - 2 ; case 2
	.short _021EBEE4 - _021EBCF8 - 2 ; case 3
	.short _021EBF6C - _021EBCF8 - 2 ; case 4
	.short _021EBFBA - _021EBCF8 - 2 ; case 5
	.short _021EBFD0 - _021EBCF8 - 2 ; case 6
	.short _021EC002 - _021EBCF8 - 2 ; case 7
	.short _021EC018 - _021EBCF8 - 2 ; case 8
	.short _021EC038 - _021EBCF8 - 2 ; case 9
	.short _021EC0D4 - _021EBCF8 - 2 ; case 10
	.short _021EC122 - _021EBCF8 - 2 ; case 11
	.short _021EC138 - _021EBCF8 - 2 ; case 12
	.short _021EC16A - _021EBCF8 - 2 ; case 13
	.short _021EC180 - _021EBCF8 - 2 ; case 14
	.short _021EC19E - _021EBCF8 - 2 ; case 15
	.short _021EC1E8 - _021EBCF8 - 2 ; case 16
	.short _021EC21C - _021EBCF8 - 2 ; case 17
	.short _021EC284 - _021EBCF8 - 2 ; case 18
	.short _021EC342 - _021EBCF8 - 2 ; case 19
_021EBD20:
	mov r1, #0x9b
	ldr r0, [sp, #0x10]
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x9b
	str r0, [r5, #0xc]
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	ldr r4, [r5, #0xc]
	mov r1, #4
	add r0, r4, #0
	add r0, #0x44
	mov r2, #3
	bl MOD05_021E3E14
	mov r0, #0x17
	str r0, [sp]
	mov r1, #0x18
	str r1, [sp, #4]
	mov r0, #0x19
	str r0, [sp, #8]
	ldr r0, _021EC0C0 ; =0x000927C0
	lsl r1, r1, #4
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0x44
	add r1, r4, r1
	mov r2, #0x16
	mov r3, #1
	bl MOD05_021E3E64
	mov r0, #0x17
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #0x19
	str r0, [sp, #8]
	ldr r0, _021EC0C4 ; =0x000927C1
	mov r1, #0x6d
	str r0, [sp, #0xc]
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x44
	add r1, r4, r1
	mov r2, #0x16
	mov r3, #1
	bl MOD05_021E3E64
	mov r0, #0xf
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	mov r0, #0x11
	str r0, [sp, #8]
	ldr r0, _021EC0C8 ; =0x000927C2
	mov r1, #0x7a
	str r0, [sp, #0xc]
	ldr r2, [sp, #0x14]
	add r0, r4, #0
	lsl r1, r1, #2
	ldrb r2, [r2, #6]
	add r0, #0x44
	add r1, r4, r1
	mov r3, #0xc
	bl MOD05_021E3E64
	mov r1, #2
	lsl r1, r1, #0xc
	add r0, sp, #0x34
	add r2, r1, #0
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #6
	lsl r0, r0, #6
	add r0, r4, r0
	str r0, [sp, #0x18]
	str r0, [sp, #0x20]
	add r0, r4, #0
	str r0, [sp, #0x24]
	add r0, #0x44
	mov r7, #0
	add r6, r4, #0
	str r0, [sp, #0x24]
_021EBDCE:
	cmp r7, #3
	bge _021EBDDA
	mov r0, #0
	ldr r1, [sp, #0x18]
	str r0, [sp, #0x1c]
	b _021EBDEA
_021EBDDA:
	sub r1, r7, #1
	mov r0, #0x34
	add r2, r1, #0
	mul r2, r0
	ldr r0, [sp, #0x20]
	add r1, r0, r2
	mov r0, #1
	str r0, [sp, #0x1c]
_021EBDEA:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r2, #0
	ldr r0, [sp, #0x24]
	add r3, r2, #0
	bl MOD05_021E3FC4
	mov r1, #0x87
	lsl r1, r1, #2
	str r0, [r6, r1]
	add r0, r1, #0
	ldr r0, [r6, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	ldr r1, [sp, #0x1c]
	bl FUN_02020130
	ldr r0, [sp, #0x18]
	add r7, r7, #1
	add r0, #0x34
	add r6, r6, #4
	str r0, [sp, #0x18]
	cmp r7, #4
	blt _021EBDCE
	ldr r0, [r5, #0x10]
	bl MOD05_021EBCC8
	cmp r0, #0
	bne _021EBE48
	mov r2, #0
	str r2, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x10]
	mov r3, #0xa
	bl MOD05_021E4014
	mov r1, #0
	b _021EBE60
_021EBE48:
	mov r0, #0
	str r0, [sp]
	mov r2, #1
	mov r0, #0x87
	str r2, [sp, #4]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x10]
	mov r3, #0xa
	bl MOD05_021E4014
	mov r1, #1
_021EBE60:
	mov r0, #0x99
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x34
	bl FUN_02020064
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, [sp, #0x14]
	mov r0, #0x22
	lsl r0, r0, #4
	ldrb r2, [r2, #5]
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x10]
	mov r3, #0xa
	bl MOD05_021E4014
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x34
	bl FUN_02020064
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EBEC0:
	mov r0, #1
	mov r1, #0x10
	str r0, [sp]
	add r2, r1, #0
	add r3, r5, #4
	bl MOD05_021E3474
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EBED6:
	ldr r1, [r5, #4]
	cmp r1, #0
	bne _021EBEDE
	b _021EC3A0
_021EBEDE:
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EBEE4:
	mov r0, #6
	mov r2, #0x2e
	mov r3, #1
	str r0, [sp]
	ldr r1, _021EC0CC ; =0xFFFB0000
	add r0, r4, #0
	lsl r2, r2, #0xc
	lsl r3, r3, #0x12
	bl MOD05_021E3644
	mov r2, #0x72
	ldr r1, [r4]
	add r0, sp, #0x40
	lsl r2, r2, #0xc
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #9
	ldr r1, [sp, #0x44]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x44]
	mov r0, #1
	ldr r1, [sp, #0x40]
	lsl r0, r0, #0x10
	add r0, r1, r0
	str r0, [sp, #0x40]
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x89
	lsl r0, r0, #2
	mov r1, #1
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl FUN_020200D8
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EBF6C:
	add r0, r4, #0
	bl MOD05_021E36A4
	mov r2, #0x72
	add r6, r0, #0
	ldr r1, [r4]
	add r0, sp, #0x40
	lsl r2, r2, #0xc
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #9
	ldr r1, [sp, #0x44]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x44]
	mov r0, #1
	ldr r1, [sp, #0x40]
	lsl r0, r0, #0x10
	add r0, r1, r0
	str r0, [sp, #0x40]
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	cmp r6, #1
	bne _021EC02E
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EBFBA:
	add r0, r4, #0
	add r0, #0x30
	mov r1, #0
	mov r2, #0x10
	mov r3, #3
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EBFD0:
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E35C0
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E4AD0
	cmp r6, #1
	bne _021EC02E
	mov r3, #0
	mov r2, #0x87
	str r3, [sp]
	lsl r2, r2, #2
	ldr r0, [r4, r2]
	add r2, #0x48
	ldr r1, [sp, #0x10]
	ldr r2, [r4, r2]
	bl MOD05_021E3F68
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC002:
	add r0, r4, #0
	add r0, #0x30
	mov r1, #0x10
	mov r2, #0
	mov r3, #3
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC018:
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E35C0
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E4AD0
	cmp r6, #1
	beq _021EC030
_021EC02E:
	b _021EC3A0
_021EC030:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC038:
	mov r0, #6
	mov r1, #0x15
	mov r2, #0xd
	str r0, [sp]
	ldr r3, _021EC0D0 ; =0xFFFC0000
	add r0, r4, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	bl MOD05_021E3644
	mov r2, #0x11
	ldr r1, [r4]
	add r0, sp, #0x40
	lsl r2, r2, #0xe
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #9
	ldr r1, [sp, #0x44]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x44]
	mov r0, #1
	ldr r1, [sp, #0x40]
	lsl r0, r0, #0x10
	sub r0, r1, r0
	str r0, [sp, #0x40]
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x8a
	lsl r0, r0, #2
	mov r1, #1
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl FUN_020200D8
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
	.balign 4, 0
_021EC0C0: .word 0x000927C0
_021EC0C4: .word 0x000927C1
_021EC0C8: .word 0x000927C2
_021EC0CC: .word 0xFFFB0000
_021EC0D0: .word 0xFFFC0000
_021EC0D4:
	add r0, r4, #0
	bl MOD05_021E36A4
	mov r2, #0x11
	add r6, r0, #0
	ldr r1, [r4]
	add r0, sp, #0x40
	lsl r2, r2, #0xe
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #9
	ldr r1, [sp, #0x44]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x44]
	mov r0, #1
	ldr r1, [sp, #0x40]
	lsl r0, r0, #0x10
	sub r0, r1, r0
	str r0, [sp, #0x40]
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	cmp r6, #1
	bne _021EC212
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC122:
	add r0, r4, #0
	add r0, #0x30
	mov r1, #0
	mov r2, #0x10
	mov r3, #3
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC138:
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E35C0
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E4AD0
	cmp r6, #1
	bne _021EC212
	mov r3, #0
	mov r0, #0x22
	ldr r2, [sp, #0x14]
	str r3, [sp]
	lsl r0, r0, #4
	ldrb r2, [r2, #5]
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x10]
	bl MOD05_021E3F68
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC16A:
	add r0, r4, #0
	add r0, #0x30
	mov r1, #0x10
	mov r2, #0
	mov r3, #3
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC180:
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E35C0
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E4AD0
	cmp r6, #1
	bne _021EC212
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC19E:
	ldr r0, [r5, #0x10]
	mov r1, #0x8b
	ldr r0, [r0, #0x20]
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r1, [r4, r1]
	add r0, sp, #0x2c
	bl FUN_0201F014
	add r1, sp, #0x2c
	mov r2, #0x92
	ldrh r0, [r1]
	lsl r2, r2, #2
	strh r0, [r4, r2]
	ldrh r3, [r1, #2]
	add r0, r2, #2
	strh r3, [r4, r0]
	ldrh r3, [r1, #4]
	add r0, r2, #4
	strh r3, [r4, r0]
	ldrh r1, [r1, #6]
	add r0, r2, #6
	ldr r3, [sp, #0x14]
	strh r1, [r4, r0]
	ldrh r1, [r4, r2]
	add r2, #8
	add r0, r4, r2
	ldr r2, [sp, #0x14]
	ldrb r3, [r3, #4]
	ldr r2, [r2]
	add r2, r1, r2
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC1E8:
	mov r0, #0x25
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD05_021E35C0
	mov r1, #0x25
	lsl r1, r1, #4
	add r6, r0, #0
	add r0, r1, #0
	ldr r2, [r4, r1]
	sub r0, #8
	strh r2, [r4, r0]
	add r0, r1, #0
	sub r1, #0x24
	sub r0, #8
	ldr r1, [r4, r1]
	add r0, r4, r0
	bl FUN_0201EF90
	cmp r6, #1
	beq _021EC214
_021EC212:
	b _021EC3A0
_021EC214:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC21C:
	mov r0, #0x8b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201F010
	add r1, r0, #0
	mov r0, #0x1e
	str r0, [sp]
	mov r0, #0x23
	mov r2, #0xfa
	lsl r0, r0, #4
	lsl r2, r2, #0xc
	add r0, r4, r0
	sub r2, r1, r2
	mov r3, #0
	bl MOD05_021E3644
	mov r0, #0x1e
	mov r1, #0
	mov r2, #6
	str r0, [sp]
	add r0, r4, #0
	lsl r2, r2, #0x10
	add r3, r1, #0
	bl MOD05_021E3644
	mov r0, #0x1e
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0
	mov r2, #6
	add r0, #0x18
	lsl r2, r2, #0x10
	add r3, r1, #0
	bl MOD05_021E3644
	mov r0, #0x1e
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r1, #0
	str r0, [sp, #8]
	ldr r3, _021EC3B4 ; =0x00007FFF
	mov r0, #3
	add r2, r1, #0
	bl FUN_0200E1D0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC284:
	mov r0, #0x23
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD05_021E36A4
	add r0, r4, #0
	bl MOD05_021E36A4
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E36A4
	mov r1, #0x23
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, r1, #4
	ldr r1, [r4, r1]
	bl FUN_0201EFE0
	mov r1, #0x2e
	ldr r2, [r4]
	lsl r1, r1, #0xc
	sub r1, r1, r2
	mov r2, #0x72
	ldr r3, [r4, #0x18]
	lsl r2, r2, #0xc
	add r2, r3, r2
	add r0, sp, #0x40
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #9
	ldr r1, [sp, #0x44]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x44]
	mov r0, #1
	ldr r1, [sp, #0x40]
	lsl r0, r0, #0x10
	add r0, r1, r0
	str r0, [sp, #0x40]
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r1, #0xd
	ldr r2, [r4]
	lsl r1, r1, #0x10
	add r1, r2, r1
	mov r2, #0x11
	ldr r3, [r4, #0x18]
	lsl r2, r2, #0xe
	sub r2, r2, r3
	add r0, sp, #0x40
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #9
	ldr r1, [sp, #0x44]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x44]
	mov r0, #1
	ldr r1, [sp, #0x40]
	lsl r0, r0, #0x10
	sub r0, r1, r0
	str r0, [sp, #0x40]
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	bl FUN_0200E308
	cmp r0, #0
	beq _021EC3A0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC342:
	ldr r1, _021EC3B4 ; =0x00007FFF
	mov r0, #1
	bl FUN_0200E3A0
	ldr r1, [r5, #0x14]
	cmp r1, #0
	beq _021EC354
	mov r0, #1
	str r0, [r1]
_021EC354:
	mov r7, #0
	add r6, r4, #0
_021EC358:
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_0201FFC8
	add r7, r7, #1
	add r6, r6, #4
	cmp r7, #4
	blt _021EC358
	mov r0, #6
	lsl r0, r0, #6
	add r6, r4, r0
	add r0, r4, #0
	str r0, [sp, #0x28]
	add r0, #0x44
	mov r7, #0
	str r0, [sp, #0x28]
_021EC37A:
	ldr r0, [sp, #0x28]
	add r1, r6, #0
	bl MOD05_021E3F3C
	add r7, r7, #1
	add r6, #0x34
	cmp r7, #3
	blt _021EC37A
	add r4, #0x44
	add r0, r4, #0
	bl MOD05_021E3E44
	ldr r1, [r5, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add sp, #0x4c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021EC3A0:
	ldr r0, [r5]
	cmp r0, #0x13
	beq _021EC3AC
	ldr r0, [r4, #0x44]
	bl FUN_0201FDEC
_021EC3AC:
	mov r0, #0
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
	nop
_021EC3B4: .word 0x00007FFF

	thumb_func_start MOD05_021EC3B8
MOD05_021EC3B8: ; 0x021EC3B8
	push {r4, lr}
	ldr r2, _021EC3D4 ; =UNK05_021F7910
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EBCD8
	cmp r0, #1
	bne _021EC3D0
	add r0, r4, #0
	bl FUN_0200621C
_021EC3D0:
	pop {r4, pc}
	nop
_021EC3D4: .word UNK05_021F7910

	thumb_func_start MOD05_021EC3D8
MOD05_021EC3D8: ; 0x021EC3D8
	push {r4, lr}
	ldr r2, _021EC3F4 ; =UNK05_021F7918
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EBCD8
	cmp r0, #1
	bne _021EC3F0
	add r0, r4, #0
	bl FUN_0200621C
_021EC3F0:
	pop {r4, pc}
	nop
_021EC3F4: .word UNK05_021F7918

	thumb_func_start MOD05_021EC3F8
MOD05_021EC3F8: ; 0x021EC3F8
	push {r4, lr}
	ldr r2, _021EC414 ; =UNK05_021F7920
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EBCD8
	cmp r0, #1
	bne _021EC410
	add r0, r4, #0
	bl FUN_0200621C
_021EC410:
	pop {r4, pc}
	nop
_021EC414: .word UNK05_021F7920

	thumb_func_start MOD05_021EC418
MOD05_021EC418: ; 0x021EC418
	push {r4, lr}
	ldr r2, _021EC434 ; =UNK05_021F7928
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EBCD8
	cmp r0, #1
	bne _021EC430
	add r0, r4, #0
	bl FUN_0200621C
_021EC430:
	pop {r4, pc}
	nop
_021EC434: .word UNK05_021F7928

	thumb_func_start MOD05_021EC438
MOD05_021EC438: ; 0x021EC438
	push {r4, lr}
	ldr r2, _021EC454 ; =UNK05_021F7930
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EBCD8
	cmp r0, #1
	bne _021EC450
	add r0, r4, #0
	bl FUN_0200621C
_021EC450:
	pop {r4, pc}
	nop
_021EC454: .word UNK05_021F7930

	thumb_func_start MOD05_021EC458
MOD05_021EC458: ; 0x021EC458
	push {r3, lr}
	bl Sav2_DayCare_GetMonX
	bl DayCareMon_GetBoxMon
	pop {r3, pc}

	thumb_func_start MOD05_021EC464
MOD05_021EC464: ; 0x021EC464
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	add r6, r0, #0
	add r5, r4, #0
	mov r7, #5
_021EC46E:
	add r0, r6, #0
	add r1, r5, #0
	bl Sav2_DayCare_GetMonX
	bl DayCareMon_GetBoxMon
	add r1, r7, #0
	mov r2, #0
	bl GetBoxMonData
	cmp r0, #0
	beq _021EC48C
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_021EC48C:
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #2
	blo _021EC46E
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EC49C
MOD05_021EC49C: ; 0x021EC49C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _021EC4D8 ; =UNK05_021FD680
	mov r4, #0
	str r5, [r0]
	mov r6, #5
	add r7, r4, #0
_021EC4AA:
	add r0, r5, #0
	add r1, r4, #0
	bl Sav2_DayCare_GetMonX
	bl DayCareMon_GetBoxMon
	add r1, r6, #0
	add r2, r7, #0
	bl GetBoxMonData
	cmp r0, #0
	bne _021EC4C6
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
_021EC4C6:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #2
	blo _021EC4AA
	mov r0, #0
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021EC4D8: .word UNK05_021FD680

	thumb_func_start MOD05_021EC4DC
MOD05_021EC4DC: ; 0x021EC4DC
	push {r3, lr}
	mov r1, #6
	mov r2, #0
	bl GetBoxMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl ItemIdIsMail
	pop {r3, pc}

	thumb_func_start MOD05_021EC4F0
MOD05_021EC4F0: ; 0x021EC4F0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r2, #0
	add r6, r0, #0
	str r1, [sp]
	add r7, r3, #0
	bl GetPartyMonByIndex
	add r4, r0, #0
	add r0, r5, #0
	bl DayCareMon_GetExtras
	str r0, [sp, #8]
	add r0, r5, #0
	bl DayCareMon_GetBoxMon
	str r0, [sp, #4]
	add r0, r7, #0
	bl Sav2_PlayerData_GetProfileAddr
	bl PlayerProfile_GetNamePtr
	add r0, r4, #0
	mov r1, #0x74
	add r2, sp, #0xc
	bl GetMonData
	add r0, r4, #0
	bl FUN_020690E4
	bl MOD05_021EC4DC
	cmp r0, #0
	beq _021EC544
	ldr r0, [sp, #8]
	bl DayCareMail_GetCapsule
	add r2, r0, #0
	add r0, r4, #0
	mov r1, #0xa9
	bl GetMonData
_021EC544:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl CopyBoxPokemonToBoxPokemon
	add r0, r5, #0
	mov r1, #0
	bl DayCareMon_SetSteps
	ldr r1, [sp]
	add r0, r6, #0
	bl RemoveMonFromParty
	ldr r1, _021EC578 ; =0x000001B9
	add r0, r6, #0
	bl PartyHasMon
	cmp r0, #0
	bne _021EC572
	add r0, r7, #0
	bl Sav2_Chatot_get
	bl Chatot_invalidate
_021EC572:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_021EC578: .word 0x000001B9

	thumb_func_start MOD05_021EC57C
MOD05_021EC57C: ; 0x021EC57C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r3, #0
	add r5, r0, #0
	add r0, r7, #0
	add r6, r1, #0
	add r4, r2, #0
	bl FUN_02029FC8
	mov r1, #0x28
	bl FUN_0202A0E8
	add r0, r4, #0
	bl MOD05_021EC49C
	add r1, r0, #0
	add r0, r4, #0
	bl Sav2_DayCare_GetMonX
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	add r3, r7, #0
	bl MOD05_021EC4F0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EC5B0
MOD05_021EC5B0: ; 0x021EC5B0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	mov r1, #0
	bl Sav2_DayCare_GetMonX
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl Sav2_DayCare_GetMonX
	add r4, r0, #0
	add r0, r5, #0
	bl DayCareMon_GetBoxMon
	add r6, r0, #0
	add r0, r4, #0
	bl DayCareMon_GetBoxMon
	add r7, r0, #0
	add r0, r6, #0
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	cmp r0, #0
	bne _021EC600
	add r0, r7, #0
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	cmp r0, #0
	beq _021EC600
	add r0, r5, #0
	add r1, r4, #0
	bl DayCareMon_Copy
	add r0, r4, #0
	bl DayCareMon_Init
_021EC600:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EC604
MOD05_021EC604: ; 0x021EC604
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #8]
	add r4, sp, #8
	add r6, sp, #4
	add r7, sp, #4
_021EC616:
	add r0, r5, #0
	bl FUN_020690E8
	cmp r0, #0
	beq _021EC658
	mov r0, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_02069818
	cmp r0, #0
	beq _021EC64E
_021EC632:
	ldr r1, _021EC664 ; =0x0000FFFF
	cmp r0, r1
	bne _021EC640
	ldrh r1, [r7]
	add r0, r5, #0
	bl FUN_02069708
_021EC640:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_02069818
	cmp r0, #0
	bne _021EC632
_021EC64E:
	ldr r0, [sp]
	add r0, r0, #1
	str r0, [sp]
	cmp r0, #0x64
	blt _021EC616
_021EC658:
	add r0, r5, #0
	bl CalcMonLevelAndStats
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_021EC664: .word 0x0000FFFF

	thumb_func_start MOD05_021EC668
MOD05_021EC668: ; 0x021EC668
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r0, [sp]
	add r6, r1, #0
	mov r0, #4
	add r7, r2, #0
	bl AllocMonZeroed
	add r4, r0, #0
	add r0, r6, #0
	bl DayCareMon_GetBoxMon
	add r5, r0, #0
	add r0, r6, #0
	bl DayCareMon_GetExtras
	str r0, [sp, #4]
	add r0, r7, #0
	mov r1, #0
	add r2, r5, #0
	bl BufferBoxMonNickname
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	add r0, r5, #0
	add r1, r4, #0
	bl CopyBoxPokemonToPokemon
	add r0, r4, #0
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	cmp r0, #0x64
	beq _021EC6E0
	add r0, r4, #0
	mov r1, #8
	mov r2, #0
	bl GetMonData
	str r0, [sp, #8]
	add r0, r6, #0
	bl DayCareMon_GetSteps
	ldr r1, [sp, #8]
	add r2, sp, #8
	add r0, r1, r0
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #8
	bl SetMonData
	add r0, r4, #0
	bl MOD05_021EC604
_021EC6E0:
	add r0, r5, #0
	bl MOD05_021EC4DC
	cmp r0, #0
	beq _021EC6FA
	ldr r0, [sp, #4]
	bl DayCareMail_GetCapsule
	add r2, r0, #0
	add r0, r4, #0
	mov r1, #0xa9
	bl SetMonData
_021EC6FA:
	ldr r0, [sp]
	add r1, r4, #0
	bl AddMonToParty
	add r0, r5, #0
	bl ZeroBoxMonData
	add r0, r6, #0
	mov r1, #0
	bl DayCareMon_SetSteps
	add r0, r4, #0
	bl FreeToHeap
	add r0, r7, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021EC71C
MOD05_021EC71C: ; 0x021EC71C
	push {r4, r5, r6, lr}
	add r6, r2, #0
	add r5, r0, #0
	add r4, r1, #0
	add r0, r6, #0
	add r1, r3, #0
	bl Sav2_DayCare_GetMonX
	add r1, r0, #0
	add r0, r5, #0
	add r2, r4, #0
	bl MOD05_021EC668
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r6, #0
	bl MOD05_021EC5B0
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021EC744
MOD05_021EC744: ; 0x021EC744
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #4
	add r5, r1, #0
	bl AllocMonZeroed
	add r7, r0, #0
	bl FUN_020690E4
	add r4, r0, #0
	add r0, r6, #0
	add r1, r4, #0
	bl CopyPokemonToBoxPokemon
	add r0, r4, #0
	mov r1, #8
	mov r2, #0
	bl GetBoxMonData
	str r0, [sp]
	add r0, r0, r5
	str r0, [sp]
	add r0, r4, #0
	mov r1, #8
	add r2, sp, #0
	bl SetBoxMonData
	add r0, r4, #0
	bl CalcBoxMonLevel
	add r4, r0, #0
	add r0, r7, #0
	bl FreeToHeap
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021EC78C
MOD05_021EC78C: ; 0x021EC78C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	bl DayCareMon_GetBoxMon
	add r6, r0, #0
	bl CalcBoxMonLevel
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	add r0, r5, #0
	bl DayCareMon_GetSteps
	add r1, r0, #0
	add r0, r6, #0
	bl MOD05_021EC744
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	sub r0, r0, r4
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021EC7B4
MOD05_021EC7B4: ; 0x021EC7B4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl DayCareMon_GetBoxMon
	add r4, r0, #0
	add r0, r5, #0
	bl DayCareMon_GetSteps
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021EC744
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EC7D4
MOD05_021EC7D4: ; 0x021EC7D4
	push {r4, r5, r6, lr}
	sub sp, #8
	add r4, r0, #0
	add r5, r1, #0
	bl DayCareMon_GetBoxMon
	add r6, r0, #0
	add r0, r4, #0
	bl MOD05_021EC78C
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r1, #1
	add r0, r5, #0
	add r2, r4, #0
	mov r3, #3
	str r1, [sp, #4]
	bl BufferIntegerAsString
	add r0, r5, #0
	mov r1, #0
	add r2, r6, #0
	bl BufferBoxMonNickname
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	add sp, #8
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EC810
MOD05_021EC810: ; 0x021EC810
	push {r4, r5, r6, lr}
	sub sp, #8
	add r4, r0, #0
	add r5, r1, #0
	bl DayCareMon_GetBoxMon
	add r6, r0, #0
	add r0, r4, #0
	bl MOD05_021EC78C
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r5, #0
	mov r1, #0
	add r2, r6, #0
	bl BufferBoxMonNickname
	add r1, r4, #1
	mov r0, #0x64
	mul r0, r1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	mov r0, #0
	str r0, [sp]
	mov r1, #1
	add r0, r5, #0
	add r2, r4, #0
	mov r3, #5
	str r1, [sp, #4]
	bl BufferIntegerAsString
	add r0, r4, #0
	add sp, #8
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021EC854
MOD05_021EC854: ; 0x021EC854
	push {r4, lr}
	add r4, r2, #0
	bl Sav2_DayCare_GetMonX
	add r1, r4, #0
	bl MOD05_021EC810
	pop {r4, pc}

	thumb_func_start MOD05_021EC864
MOD05_021EC864: ; 0x021EC864
	push {r3, r4, r5, lr}
	add r5, r2, #0
	bl Sav2_DayCare_GetMonX
	add r4, r0, #0
	bl DayCareMon_GetBoxMon
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	cmp r0, #0
	beq _021EC888
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021EC7D4
	pop {r3, r4, r5, pc}
_021EC888:
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021EC88C
MOD05_021EC88C: ; 0x021EC88C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	mov r1, #0
	bl MOD05_021EC458
	str r0, [r4]
	add r0, r5, #0
	mov r1, #1
	bl MOD05_021EC458
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EC8A8
MOD05_021EC8A8: ; 0x021EC8A8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r1, #0
	mvn r1, r1
	str r1, [sp]
	add r1, sp, #4
	bl MOD05_021EC88C
	mov r4, #0
	add r5, sp, #4
_021EC8BC:
	ldr r0, [r5]
	bl GetBoxMonGender
	cmp r0, #1
	bne _021EC8C8
	str r4, [sp]
_021EC8C8:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blt _021EC8BC
	mov r7, #0
	add r6, r7, #0
	add r4, sp, #4
	add r5, sp, #0xc
_021EC8D8:
	ldr r0, [r4]
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	str r0, [r5]
	cmp r0, #0x84
	bne _021EC8EC
	add r7, r7, #1
	str r6, [sp]
_021EC8EC:
	add r6, r6, #1
	add r4, r4, #4
	add r5, r5, #4
	cmp r6, #2
	blt _021EC8D8
	cmp r7, #2
	bne _021EC90E
	bl LCRandom
	ldr r1, _021EC940 ; =0x00007FFF
	cmp r0, r1
	blo _021EC90A
	mov r0, #0
	str r0, [sp]
	b _021EC90E
_021EC90A:
	mov r0, #1
	str r0, [sp]
_021EC90E:
	ldr r0, [sp]
	mov r2, #0
	lsl r1, r0, #2
	add r0, sp, #4
	ldr r0, [r0, r1]
	mov r1, #6
	bl GetBoxMonData
	cmp r0, #0xe5
	bne _021EC938
	bl LCRandom
	ldr r1, _021EC940 ; =0x00007FFF
	cmp r0, r1
	blo _021EC932
	mov r0, #0
	mvn r0, r0
	str r0, [sp]
_021EC932:
	ldr r0, [sp]
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_021EC938:
	mov r0, #0
	mvn r0, r0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021EC940: .word 0x00007FFF

	thumb_func_start MOD05_021EC944
MOD05_021EC944: ; 0x021EC944
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	mov r5, #0
	bl MOD05_021EC8A8
	add r1, r0, #0
	bpl _021EC960
	bl MTRandom
	add r1, r0, #0
	ldr r0, [sp]
	bl Sav2_DayCare_SetEggPID
	pop {r3, r4, r5, r6, r7, pc}
_021EC960:
	ldr r0, [sp]
	bl MOD05_021EC458
	add r1, r5, #0
	add r2, r1, #0
	bl GetBoxMonData
	bl GetNatureFromPersonality
	mov r7, #0x96
	add r6, r0, #0
	lsl r7, r7, #4
_021EC978:
	bl MTRandom
	add r4, r0, #0
	bl GetNatureFromPersonality
	cmp r6, r0
	bne _021EC98A
	cmp r4, #0
	bne _021EC990
_021EC98A:
	add r5, r5, #1
	cmp r5, r7
	ble _021EC978
_021EC990:
	ldr r0, [sp]
	add r1, r4, #0
	bl Sav2_DayCare_SetEggPID
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EC99C
MOD05_021EC99C: ; 0x021EC99C
	push {r3, r4}
	sub sp, #8
	mov r2, #0xff
	strb r2, [r0, r1]
	mov r2, #0
	add r3, sp, #0
_021EC9A8:
	ldrb r1, [r0, r2]
	add r2, r2, #1
	strb r1, [r3]
	add r3, r3, #1
	cmp r2, #6
	blt _021EC9A8
	mov r2, #0
	add r4, r2, #0
	add r3, sp, #0
_021EC9BA:
	ldrb r1, [r3]
	cmp r1, #0xff
	beq _021EC9C4
	strb r1, [r0, r2]
	add r2, r2, #1
_021EC9C4:
	add r4, r4, #1
	add r3, r3, #1
	cmp r4, #6
	blt _021EC9BA
	add sp, #8
	pop {r3, r4}
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021EC9D4
MOD05_021EC9D4: ; 0x021EC9D4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r0, #0
	str r1, [sp]
	mov r0, #0
	add r1, sp, #8
_021EC9E0:
	strb r0, [r1, r0]
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #6
	blo _021EC9E0
	add r7, sp, #0xc
	mov r5, #0
	add r6, sp, #8
	add r7, #2
_021EC9F4:
	bl LCRandom
	mov r1, #6
	sub r1, r1, r5
	bl _s32_div_f
	ldrb r0, [r6, r1]
	add r1, r5, #0
	strb r0, [r7, r5]
	add r0, r6, #0
	bl MOD05_021EC99C
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #3
	blo _021EC9F4
	add r6, sp, #4
	mov r5, #0
	add r6, #1
	mov r7, #0x1f
_021ECA1E:
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r0, r0, #0x1f
	sub r0, r0, r1
	ror r0, r7
	add r0, r1, r0
	strb r0, [r6, r5]
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #3
	blo _021ECA1E
	mov r5, #0
	add r7, sp, #4
	add r6, sp, #4
_021ECA3E:
	add r1, sp, #4
	add r1, #1
	ldrb r1, [r1, r5]
	ldr r0, [sp]
	bl MOD05_021EC458
	add r1, sp, #0xc
	add r1, #2
	ldrb r1, [r1, r5]
	cmp r1, #5
	bhi _021ECAEE
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021ECA60: ; jump table
	.short _021ECA6C - _021ECA60 - 2 ; case 0
	.short _021ECA82 - _021ECA60 - 2 ; case 1
	.short _021ECA98 - _021ECA60 - 2 ; case 2
	.short _021ECAAE - _021ECA60 - 2 ; case 3
	.short _021ECAC4 - _021ECA60 - 2 ; case 4
	.short _021ECADA - _021ECA60 - 2 ; case 5
_021ECA6C:
	mov r1, #0x46
	mov r2, #0
	bl GetBoxMonData
	strb r0, [r6]
	add r0, r4, #0
	mov r1, #0x46
	add r2, r7, #0
	bl SetMonData
	b _021ECAEE
_021ECA82:
	mov r1, #0x47
	mov r2, #0
	bl GetBoxMonData
	strb r0, [r6]
	add r0, r4, #0
	mov r1, #0x47
	add r2, r7, #0
	bl SetMonData
	b _021ECAEE
_021ECA98:
	mov r1, #0x48
	mov r2, #0
	bl GetBoxMonData
	strb r0, [r6]
	add r0, r4, #0
	mov r1, #0x48
	add r2, r7, #0
	bl SetMonData
	b _021ECAEE
_021ECAAE:
	mov r1, #0x49
	mov r2, #0
	bl GetBoxMonData
	strb r0, [r6]
	add r0, r4, #0
	mov r1, #0x49
	add r2, r7, #0
	bl SetMonData
	b _021ECAEE
_021ECAC4:
	mov r1, #0x4a
	mov r2, #0
	bl GetBoxMonData
	strb r0, [r6]
	add r0, r4, #0
	mov r1, #0x4a
	add r2, r7, #0
	bl SetMonData
	b _021ECAEE
_021ECADA:
	mov r1, #0x4b
	mov r2, #0
	bl GetBoxMonData
	strb r0, [r6]
	add r0, r4, #0
	mov r1, #0x4b
	add r2, r7, #0
	bl SetMonData
_021ECAEE:
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #3
	blo _021ECA3E
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021ECAFC
MOD05_021ECAFC: ; 0x021ECAFC
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	add r5, r1, #0
	mov r1, #5
	add r2, r4, #0
	add r6, r4, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	ldr r0, _021ECB60 ; =0x00004E20
	ldr r3, _021ECB64 ; =0x00000775
	add r2, r2, r0
	ldr r0, _021ECB68 ; =UNK05_021F7B48
	add r1, r4, #0
_021ECB1A:
	lsl r7, r1, #1
	ldrh r7, [r0, r7]
	cmp r2, r7
	bne _021ECB2A
	add r0, r1, #1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	b _021ECB34
_021ECB2A:
	add r1, r1, #1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	cmp r1, r3
	blo _021ECB1A
_021ECB34:
	ldr r2, _021ECB68 ; =UNK05_021F7B48
	lsl r0, r6, #1
	ldr r3, _021ECB60 ; =0x00004E20
	mov r1, #0
	add r0, r2, r0
_021ECB3E:
	lsl r6, r1, #1
	ldrh r2, [r0, r6]
	cmp r2, r3
	bhi _021ECB58
	add r1, r1, #1
	strh r2, [r5, r6]
	add r2, r4, #1
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	lsr r1, r1, #0x10
	lsr r4, r2, #0x10
	cmp r1, #0x10
	blo _021ECB3E
_021ECB58:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021ECB60: .word 0x00004E20
_021ECB64: .word 0x00000775
_021ECB68: .word UNK05_021F7B48

	thumb_func_start MOD05_021ECB6C
MOD05_021ECB6C: ; 0x021ECB6C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r7, r0, #0
	str r1, [sp]
	mov r0, #4
	mov r1, #0xb4
	str r2, [sp, #4]
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0
	add r1, r4, #0
	mov r2, #0xb4
	str r0, [sp, #0x1c]
	bl MIi_CpuClearFast
	add r0, r7, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x18]
	add r0, r7, #0
	mov r1, #0x70
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0xc]
	add r2, r4, #0
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0xc]
	add r2, #0x30
	bl Species_LoadLearnsetTable
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x14]
	mov r5, #0
_021ECBC0:
	lsl r0, r5, #2
	add r6, r5, #0
	str r0, [sp, #0x20]
	add r0, r4, r0
	add r6, #0x36
	str r0, [sp, #0x10]
	ldr r0, [sp]
	add r1, r6, #0
	mov r2, #0
	bl GetBoxMonData
	ldr r1, [sp, #0x20]
	mov r2, #0
	str r0, [r4, r1]
	ldr r0, [sp, #4]
	add r1, r6, #0
	bl GetBoxMonData
	ldr r1, [sp, #0x10]
	str r0, [r1, #0x20]
	add r0, r5, #1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #4
	blo _021ECBC0
	add r1, r4, #0
	add r0, r7, #0
	add r1, #0x94
	bl MOD05_021ECAFC
	add r5, r0, #0
	mov r6, #0
_021ECC00:
	lsl r0, r6, #2
	ldr r1, [r4, r0]
	str r0, [sp, #0x24]
	cmp r1, #0
	beq _021ECC50
	mov r0, #0
	cmp r5, #0
	bls _021ECC46
_021ECC10:
	lsl r2, r0, #1
	add r2, r4, r2
	add r2, #0x94
	ldrh r2, [r2]
	cmp r1, r2
	bne _021ECC3C
	lsl r1, r1, #0x10
	add r0, r7, #0
	lsr r1, r1, #0x10
	bl FUN_02069698
	ldr r1, _021ECD60 ; =0x0000FFFF
	cmp r0, r1
	bne _021ECC46
	ldr r1, [sp, #0x24]
	add r0, r7, #0
	ldr r1, [r4, r1]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02069708
	b _021ECC46
_021ECC3C:
	add r0, r0, #1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, r5
	blo _021ECC10
_021ECC46:
	add r0, r6, #1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, #4
	blo _021ECC00
_021ECC50:
	mov r0, #0
	str r0, [sp, #8]
_021ECC54:
	ldr r0, [sp, #8]
	lsl r6, r0, #2
	ldr r0, [r4, r6]
	cmp r0, #0
	beq _021ECCAC
	mov r5, #0
_021ECC60:
	mov r0, #0x52
	lsl r0, r0, #2
	add r0, r5, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl TMHMGetMove
	ldr r1, [r4, r6]
	cmp r1, r0
	bne _021ECCA2
	lsl r2, r5, #0x18
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0xc]
	lsr r2, r2, #0x18
	bl FUN_0206A16C
	cmp r0, #0
	beq _021ECCA2
	ldr r1, [r4, r6]
	add r0, r7, #0
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02069698
	ldr r1, _021ECD60 ; =0x0000FFFF
	cmp r0, r1
	bne _021ECCA2
	ldr r1, [r4, r6]
	add r0, r7, #0
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02069708
_021ECCA2:
	add r0, r5, #1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x64
	blo _021ECC60
_021ECCAC:
	ldr r0, [sp, #8]
	add r0, r0, #1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	cmp r0, #4
	blo _021ECC54
	mov r6, #0
_021ECCBC:
	lsl r1, r6, #2
	ldr r0, [r4, r1]
	cmp r0, #0
	beq _021ECCFC
	mov r3, #0
_021ECCC6:
	lsl r2, r3, #2
	add r2, r4, r2
	ldr r0, [r4, r1]
	ldr r2, [r2, #0x20]
	cmp r0, r2
	bne _021ECCE8
	cmp r0, #0
	beq _021ECCE8
	ldr r2, [sp, #0x1c]
	add r5, r2, #0
	add r5, r5, #1
	lsl r5, r5, #0x10
	lsr r5, r5, #0x10
	lsl r2, r2, #2
	str r5, [sp, #0x1c]
	add r2, r4, r2
	str r0, [r2, #0x10]
_021ECCE8:
	add r0, r3, #1
	lsl r0, r0, #0x10
	lsr r3, r0, #0x10
	cmp r3, #4
	blo _021ECCC6
	add r0, r6, #1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, #4
	blo _021ECCBC
_021ECCFC:
	mov r6, #0
_021ECCFE:
	lsl r0, r6, #2
	add r5, r4, r0
	ldr r3, [r5, #0x10]
	cmp r3, #0
	beq _021ECD54
	ldr r0, [sp, #0x14]
	mov r2, #0
	cmp r0, #0
	bls _021ECD4A
_021ECD10:
	lsl r0, r2, #1
	add r0, r4, r0
	ldrh r1, [r0, #0x30]
	cmp r1, #0
	beq _021ECD3E
	ldr r0, [r5, #0x10]
	cmp r0, r1
	bne _021ECD3E
	lsl r1, r3, #0x10
	add r0, r7, #0
	lsr r1, r1, #0x10
	bl FUN_02069698
	ldr r1, _021ECD60 ; =0x0000FFFF
	cmp r0, r1
	bne _021ECD4A
	ldr r1, [r5, #0x10]
	add r0, r7, #0
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02069708
	b _021ECD4A
_021ECD3E:
	add r0, r2, #1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	ldr r0, [sp, #0x14]
	cmp r2, r0
	blo _021ECD10
_021ECD4A:
	add r0, r6, #1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, #4
	blo _021ECCFE
_021ECD54:
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021ECD60: .word 0x0000FFFF

	thumb_func_start MOD05_021ECD64
MOD05_021ECD64: ; 0x021ECD64
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	bl Sav2_DayCare_SetEggPID
	add r0, r4, #0
	mov r1, #0
	bl Sav2_DayCare_SetEggCycleCounter
	pop {r4, pc}

	thumb_func_start MOD05_021ECD78
MOD05_021ECD78: ; 0x021ECD78
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	add r0, r1, #0
	add r1, sp, #0
	bl MOD05_021EC88C
	ldr r2, _021ECDE8 ; =UNK05_021F7B12
	mov r3, #0
	mov r1, #6
_021ECD8C:
	add r0, r3, #0
	mul r0, r1
	ldrh r0, [r2, r0]
	cmp r5, r0
	bne _021ECD9A
	add r6, r3, #0
	b _021ECDA4
_021ECD9A:
	add r0, r3, #1
	lsl r0, r0, #0x10
	lsr r3, r0, #0x10
	cmp r3, #9
	blo _021ECD8C
_021ECDA4:
	cmp r3, #9
	bne _021ECDAE
	add sp, #8
	add r0, r5, #0
	pop {r4, r5, r6, pc}
_021ECDAE:
	ldr r0, [sp]
	mov r1, #6
	mov r2, #0
	bl GetBoxMonData
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [sp, #4]
	mov r1, #6
	mov r2, #0
	bl GetBoxMonData
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	mov r0, #6
	add r1, r6, #0
	mul r1, r0
	ldr r0, _021ECDEC ; =UNK05_021F7B14
	ldrh r0, [r0, r1]
	cmp r4, r0
	beq _021ECDE0
	cmp r2, r0
	beq _021ECDE0
	ldr r0, _021ECDF0 ; =UNK05_021F7B16
	ldrh r5, [r0, r1]
_021ECDE0:
	add r0, r5, #0
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_021ECDE8: .word UNK05_021F7B12
_021ECDEC: .word UNK05_021F7B14
_021ECDF0: .word UNK05_021F7B16

	thumb_func_start MOD05_021ECDF4
MOD05_021ECDF4: ; 0x021ECDF4
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r0, #0
	add r0, r1, #0
	add r1, sp, #0
	bl MOD05_021EC88C
	ldr r0, [sp]
	mov r1, #6
	mov r2, #0
	bl GetBoxMonData
	add r5, r0, #0
	ldr r0, [sp, #4]
	mov r1, #6
	mov r2, #0
	bl GetBoxMonData
	cmp r5, #0xec
	beq _021ECE20
	cmp r0, #0xec
	bne _021ECE3A
_021ECE20:
	mov r1, #0x56
	add r0, r4, #0
	lsl r1, r1, #2
	bl FUN_02069698
	ldr r1, _021ECE40 ; =0x0000FFFF
	cmp r0, r1
	bne _021ECE3A
	mov r1, #0x56
	add r0, r4, #0
	lsl r1, r1, #2
	bl FUN_02069708
_021ECE3A:
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_021ECE40: .word 0x0000FFFF

	thumb_func_start MOD05_021ECE44
MOD05_021ECE44: ; 0x021ECE44
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r1, sp, #4
	str r0, [sp]
	bl MOD05_021EC88C
	mov r4, #0
	add r7, sp, #4
_021ECE56:
	lsl r6, r4, #2
	ldr r0, [r7, r6]
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	lsl r1, r4, #1
	add r2, sp, #0xc
	strh r0, [r2, r1]
	add r0, r2, #0
	ldrh r0, [r0, r1]
	cmp r0, #0x84
	bne _021ECE7A
	mov r0, #1
	eor r0, r4
	strb r0, [r5]
	strb r4, [r5, #1]
	b _021ECE8C
_021ECE7A:
	ldr r0, [r7, r6]
	bl GetBoxMonGender
	cmp r0, #1
	bne _021ECE8C
	mov r0, #1
	strb r4, [r5]
	eor r0, r4
	strb r0, [r5, #1]
_021ECE8C:
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #2
	blo _021ECE56
	ldrb r0, [r5]
	lsl r1, r0, #1
	add r0, sp, #0xc
	ldrh r0, [r0, r1]
	bl ReadFromPersonalPmsNarc
	add r4, r0, #0
	cmp r4, #0x1d
	bne _021ECEBC
	ldr r0, [sp]
	bl Sav2_DayCare_GetEggPID
	mov r1, #2
	lsl r1, r1, #0xe
	tst r0, r1
	beq _021ECEBA
	mov r4, #0x20
	b _021ECEBC
_021ECEBA:
	mov r4, #0x1d
_021ECEBC:
	ldr r0, _021ECF08 ; =0x0000013A
	cmp r4, r0
	bne _021ECED6
	ldr r0, [sp]
	bl Sav2_DayCare_GetEggPID
	mov r1, #2
	lsl r1, r1, #0xe
	tst r0, r1
	beq _021ECED4
	ldr r4, _021ECF0C ; =0x00000139
	b _021ECED6
_021ECED4:
	ldr r4, _021ECF08 ; =0x0000013A
_021ECED6:
	ldr r0, _021ECF10 ; =0x000001EA
	cmp r4, r0
	bne _021ECEDE
	sub r4, r0, #1
_021ECEDE:
	ldrb r0, [r5, #1]
	lsl r1, r0, #1
	add r0, sp, #0xc
	ldrh r0, [r0, r1]
	cmp r0, #0x84
	bne _021ECF02
	ldrb r0, [r5]
	lsl r1, r0, #2
	add r0, sp, #4
	ldr r0, [r0, r1]
	bl GetBoxMonGender
	cmp r0, #1
	beq _021ECF02
	ldrb r1, [r5, #1]
	ldrb r0, [r5]
	strb r0, [r5, #1]
	strb r1, [r5]
_021ECF02:
	add r0, r4, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021ECF08: .word 0x0000013A
_021ECF0C: .word 0x00000139
_021ECF10: .word 0x000001EA

	thumb_func_start MOD05_SetEggStats
MOD05_SetEggStats: ; 0x021ECF14
	push {r0, r1, r2, r3}
	push {r4, r5, r6, lr}
	sub sp, #0x20
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	mov r1, #0x13 ; BASE_EGG_CYCLES
	add r4, r3, #0
	bl GetMonBaseStat
	add r1, sp, #0x10
	strb r0, [r1]
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #1
	mov r3, #0x20
	bl CreateMon
	mov r1, #0
	add r0, sp, #0x10
	strb r1, [r0, #2]
	mov r1, #4
	strh r1, [r0, #4]
	add r0, r5, #0
	mov r1, #0x9a
	add r2, sp, #0x14
	bl SetMonData
	add r0, r5, #0
	mov r1, #9
	add r2, sp, #0x10
	bl SetMonData
	add r2, sp, #0x10
	add r0, r5, #0
	mov r1, #0x9b
	add r2, #2
	bl SetMonData
	add r0, sp, #0x30
	ldrb r0, [r0, #8]
	cmp r0, #0
	beq _021ECF7E
	add r0, r5, #0
	mov r1, #0x97
	add r2, sp, #0x38
	bl SetMonData
_021ECF7E:
	add r2, sp, #0x10
	mov r1, #1
	add r0, sp, #0x10
	strb r1, [r0, #1]
	add r0, r5, #0
	mov r1, #0x4c
	add r2, #1
	bl SetMonData
	ldr r0, _021ED008 ; =0x000001EE
	mov r1, #4
	bl GetSpeciesName
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #0x76
	add r2, r6, #0
	bl SetMonData
	add r0, r6, #0
	bl String_dtor
	ldr r0, [sp, #0x40]
	cmp r0, #4
	bne _021ECFEE
	add r0, r4, #0
	bl PlayerProfile_GetTrainerID
	str r0, [sp, #0x1c]
	add r0, r4, #0
	bl PlayerProfile_GetTrainerGender
	str r0, [sp, #0x18]
	add r0, r4, #0
	mov r1, #0x20
	bl PlayerProfile_GetPlayerName_NewString
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #0x90
	add r2, r6, #0
	bl SetMonData
	add r0, r5, #0
	mov r1, #7
	add r2, sp, #0x1c
	bl SetMonData
	add r0, r5, #0
	mov r1, #0x9c
	add r2, sp, #0x18
	bl SetMonData
	add r0, r6, #0
	bl String_dtor
_021ECFEE:
	mov r0, #0
	str r0, [sp]
	ldr r2, [sp, #0x40]
	ldr r3, [sp, #0x44]
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0208089C
	add sp, #0x20
	pop {r4, r5, r6}
	pop {r3}
	add sp, #0x10
	bx r3
	.balign 4, 0
_021ED008: .word 0x000001EE

	thumb_func_start MOD05_DayCare_CreateEgg
MOD05_DayCare_CreateEgg: ; 0x021ED00C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r1, [sp, #0x10]
	add r7, r0, #0
	ldr r0, [sp, #0x10]
	mov r1, #0x13 ; BASE_EGG_CYCLES
	add r5, r2, #0
	add r6, r3, #0
	bl GetMonBaseStat
	add r1, sp, #0x14
	strb r0, [r1]
	add r0, r5, #0
	bl Sav2_DayCare_GetEggPID
	add r4, r0, #0
	add r0, r5, #0
	bl Sav2_DayCare_MasudaCheck
	cmp r0, #0
	beq _021ED05E
	add r0, r6, #0
	add r1, r4, #0
	bl CalcShininessByOtIdAndPersonality
	cmp r0, #0
	bne _021ED05E
	mov r5, #0
_021ED044:
	add r0, r4, #0
	bl PRandom
	add r4, r0, #0
	add r0, r6, #0
	add r1, r4, #0
	bl CalcShininessByOtIdAndPersonality
	cmp r0, #0
	bne _021ED05E
	add r5, r5, #1
	cmp r5, #4
	blt _021ED044
_021ED05E:
	mov r2, #1
	str r2, [sp]
	str r4, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	add r0, r7, #0
	mov r3, #0x20
	bl CreateMon
	add r2, sp, #0x14
	mov r1, #0
	add r0, sp, #0x14
	strb r1, [r0, #1]
	mov r1, #4
	strh r1, [r0, #2]
	add r0, r7, #0
	mov r1, #0x9a
	add r2, #2
	bl SetMonData
	add r0, r7, #0
	mov r1, #9
	add r2, sp, #0x14
	bl SetMonData
	add r2, sp, #0x14
	add r0, r7, #0
	mov r1, #0x9b
	add r2, #1
	bl SetMonData
	add r0, r7, #0
	mov r1, #0x70
	add r2, sp, #0x30
	bl SetMonData
	ldr r0, _021ED0C8 ; =0x000001EE
	mov r1, #4
	bl GetSpeciesName
	add r4, r0, #0
	add r0, r7, #0
	mov r1, #0x76
	add r2, r4, #0
	bl SetMonData
	add r0, r4, #0
	bl String_dtor
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021ED0C8: .word 0x000001EE

	thumb_func_start MOD05_DayCare_GiveEggToPlayer
MOD05_DayCare_GiveEggToPlayer: ; 0x021ED0CC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	mov r0, #4
	str r1, [sp, #4]
	add r7, r2, #0
	bl AllocMonZeroed
	add r1, sp, #0x10
	add r4, r0, #0
	add r0, r5, #0
	add r1, #1
	bl MOD05_021ECE44
	add r1, r5, #0
	bl MOD05_021ECD78
	add r6, r0, #0
	add r0, r7, #0
	bl PlayerProfile_GetTrainerID
	add r1, sp, #0x10
	str r0, [sp, #8]
	ldrb r1, [r1, #1]
	add r0, r5, #0
	bl MOD05_021EC458
	mov r1, #0x70
	mov r2, #0
	bl GetBoxMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r3, [sp, #8]
	add r0, r4, #0
	add r1, r6, #0
	add r2, r5, #0
	bl MOD05_DayCare_CreateEgg
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021EC9D4
	add r1, sp, #0x10
	ldrb r1, [r1, #2]
	add r0, r5, #0
	bl MOD05_021EC458
	add r1, sp, #0x10
	str r0, [sp, #0xc]
	ldrb r1, [r1, #1]
	add r0, r5, #0
	bl MOD05_021EC458
	add r2, r0, #0
	ldr r1, [sp, #0xc]
	add r0, r4, #0
	bl MOD05_021ECB6C
	mov r0, #1
	mov r1, #0
	bl FUN_02015CF8
	add r3, r0, #0
	mov r0, #4
	str r0, [sp]
	add r0, r4, #0
	add r1, r7, #0
	mov r2, #3
	bl FUN_0208089C
	cmp r6, #0xac
	bne _021ED168
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021ECDF4
_021ED168:
	mov r1, #1
	add r0, sp, #0x10
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #0x4c
	add r2, sp, #0x10
	bl SetMonData
	ldr r0, [sp, #4]
	add r1, r4, #0
	bl AddMonToParty
	add r0, r5, #0
	bl MOD05_021ECD64
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021ED190
MOD05_021ED190: ; 0x021ED190
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl GetPartyCount
	add r6, r0, #0
	mov r4, #0
	cmp r6, #0
	ble _021ED1E0
	mov r7, #0xac
_021ED1A2:
	add r0, r5, #0
	add r1, r4, #0
	bl GetPartyMonByIndex
	add r1, r7, #0
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _021ED1D6
	add r0, r5, #0
	add r1, r4, #0
	bl GetPartyMonByIndex
	mov r1, #0xa
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x28
	beq _021ED1D2
	cmp r0, #0x31
	bne _021ED1D6
_021ED1D2:
	mov r0, #2
	pop {r3, r4, r5, r6, r7, pc}
_021ED1D6:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, r6
	blt _021ED1A2
_021ED1E0:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021ED1E4
MOD05_021ED1E4: ; 0x021ED1E4
	push {r4, r5, r6, r7}
	mov r4, #0
	add r3, r4, #0
_021ED1EA:
	ldrh r7, [r0]
	add r5, r3, #0
	add r6, r1, #0
_021ED1F0:
	ldrh r2, [r6]
	cmp r7, r2
	bne _021ED1FC
	mov r0, #1
	pop {r4, r5, r6, r7}
	bx lr
_021ED1FC:
	add r5, r5, #1
	add r6, r6, #2
	cmp r5, #2
	blt _021ED1F0
	add r4, r4, #1
	add r0, r0, #2
	cmp r4, #2
	blt _021ED1EA
	mov r0, #0
	pop {r4, r5, r6, r7}
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021ED214
MOD05_021ED214: ; 0x021ED214
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	mov r0, #0
	str r0, [sp, #4]
	add r0, sp, #0x10
	add r4, sp, #0x18
	str r0, [sp]
	add r7, sp, #8
	add r6, sp, #0x1c
_021ED228:
	ldr r0, [r5]
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	strh r0, [r4]
	ldr r0, [r5]
	mov r1, #7
	mov r2, #0
	bl GetBoxMonData
	ldr r1, [sp]
	str r0, [r1]
	mov r1, #0
	ldr r0, [r5]
	add r2, r1, #0
	bl GetBoxMonData
	add r1, r0, #0
	ldrh r0, [r4]
	bl GetGenderBySpeciesAndPersonality
	stmia r7!, {r0}
	ldrh r0, [r4]
	mov r1, #0x16 ; BASE_EGG_GROUP_1
	bl GetMonBaseStat
	strh r0, [r6]
	ldrh r0, [r4]
	mov r1, #0x17 ; GASE_EGG_GROUP_2
	bl GetMonBaseStat
	strh r0, [r6, #2]
	ldr r0, [sp]
	add r5, r5, #4
	add r0, r0, #4
	str r0, [sp]
	ldr r0, [sp, #4]
	add r4, r4, #2
	add r0, r0, #1
	add r6, r6, #4
	str r0, [sp, #4]
	cmp r0, #2
	blo _021ED228
	add r0, sp, #8
	ldrh r1, [r0, #0x14]
	cmp r1, #0xf
	beq _021ED28E
	ldrh r0, [r0, #0x18]
	cmp r0, #0xf
	bne _021ED294
_021ED28E:
	add sp, #0x24
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021ED294:
	cmp r1, #0xd
	bne _021ED2A2
	cmp r0, #0xd
	bne _021ED2A2
	add sp, #0x24
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021ED2A2:
	cmp r1, #0xd
	beq _021ED2AA
	cmp r0, #0xd
	bne _021ED2BE
_021ED2AA:
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bne _021ED2B8
	add sp, #0x24
	mov r0, #0x14
	pop {r4, r5, r6, r7, pc}
_021ED2B8:
	add sp, #0x24
	mov r0, #0x32
	pop {r4, r5, r6, r7, pc}
_021ED2BE:
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #8]
	cmp r0, r1
	bne _021ED2CC
	add sp, #0x24
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021ED2CC:
	cmp r0, #2
	beq _021ED2D4
	cmp r1, #2
	bne _021ED2DA
_021ED2D4:
	add sp, #0x24
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021ED2DA:
	add r0, sp, #0x1c
	add r1, sp, #0x20
	bl MOD05_021ED1E4
	cmp r0, #0
	bne _021ED2EC
	add sp, #0x24
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021ED2EC:
	add r0, sp, #8
	ldrh r1, [r0, #0x10]
	ldrh r0, [r0, #0x12]
	cmp r1, r0
	bne _021ED30A
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	beq _021ED304
	add sp, #0x24
	mov r0, #0x46
	pop {r4, r5, r6, r7, pc}
_021ED304:
	add sp, #0x24
	mov r0, #0x32
	pop {r4, r5, r6, r7, pc}
_021ED30A:
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	beq _021ED318
	add sp, #0x24
	mov r0, #0x32
	pop {r4, r5, r6, r7, pc}
_021ED318:
	mov r0, #0x14
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021ED320
MOD05_021ED320: ; 0x021ED320
	push {r3, lr}
	sub sp, #8
	add r1, sp, #0
	bl MOD05_021EC88C
	add r0, sp, #0
	bl MOD05_021ED214
	add sp, #8
	pop {r3, pc}

	thumb_func_start MOD05_021ED334
MOD05_021ED334: ; 0x021ED334
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl Script_GetDay
	add r5, r0, #0
	add r0, r4, #0
	bl Script_GetMonth
	mov r1, #0x64
	mul r1, r0
	add r0, r4, #0
	add r5, r5, r1
	bl FUN_0204B33C
	cmp r0, #0
	beq _021ED358
	mov r0, #0xff
	pop {r3, r4, r5, pc}
_021ED358:
	ldr r2, _021ED374 ; =UNK05_021F7AF8
	mov r1, #0
_021ED35C:
	ldrh r0, [r2]
	cmp r5, r0
	bne _021ED366
	mov r0, #0xe6
	pop {r3, r4, r5, pc}
_021ED366:
	add r1, r1, #1
	add r2, r2, #2
	cmp r1, #0xd
	blo _021ED35C
	mov r0, #0xff
	pop {r3, r4, r5, pc}
	nop
_021ED374: .word UNK05_021F7AF8

	thumb_func_start MOD05_021ED378
MOD05_021ED378: ; 0x021ED378
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r1, #0
	add r1, sp, #8
	str r0, [sp]
	str r2, [sp, #4]
	bl MOD05_021EC88C
	mov r6, #0
	add r4, r6, #0
	add r5, sp, #8
_021ED38E:
	ldr r0, [r5]
	mov r1, #0xab
	mov r2, #0
	bl GetBoxMonData
	cmp r0, #0
	beq _021ED3AC
	ldr r0, [sp]
	add r1, r4, #0
	bl Sav2_DayCare_GetMonX
	mov r1, #1
	bl DayCareMon_AddSteps
	add r6, r6, #1
_021ED3AC:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blo _021ED38E
	ldr r0, [sp]
	bl Sav2_DayCare_GetEggPID
	cmp r0, #0
	bne _021ED3F8
	cmp r6, #2
	bne _021ED3F8
	ldr r0, [sp]
	mov r1, #1
	bl Sav2_DayCare_GetMonX
	bl DayCareMon_GetSteps
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0xff
	bne _021ED3F8
	ldr r0, [sp]
	bl MOD05_021ED320
	add r4, r0, #0
	bl LCRandom
	mov r1, #0x64
	mul r1, r0
	add r0, r1, #0
	ldr r1, _021ED498 ; =0x0000FFFF
	bl _u32_div_f
	cmp r4, r0
	bls _021ED3F8
	ldr r0, [sp]
	bl MOD05_021EC944
_021ED3F8:
	ldr r0, [sp]
	bl Sav2_DayCare_GetEggCycleCounter
	add r4, r0, #0
	ldr r0, [sp]
	add r1, r4, #1
	bl Sav2_DayCare_SetEggCycleCounter
	ldr r0, [sp, #4]
	bl MOD05_021ED334
	add r1, r4, #1
	cmp r1, r0
	bne _021ED490
	ldr r0, [sp]
	mov r1, #0
	bl Sav2_DayCare_SetEggCycleCounter
	add r0, r7, #0
	bl MOD05_021ED190
	add r6, r0, #0
	add r0, r7, #0
	mov r5, #0
	bl GetPartyCount
	cmp r0, #0
	bls _021ED490
_021ED430:
	add r0, r7, #0
	add r1, r5, #0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0
	add r4, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _021ED484
	add r0, r4, #0
	mov r1, #3
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _021ED484
	add r0, r4, #0
	mov r1, #9
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0x10]
	cmp r0, #0
	beq _021ED47E
	cmp r0, r6
	blo _021ED46E
	sub r0, r0, r6
	str r0, [sp, #0x10]
	b _021ED472
_021ED46E:
	sub r0, r0, #1
	str r0, [sp, #0x10]
_021ED472:
	add r0, r4, #0
	mov r1, #9
	add r2, sp, #0x10
	bl SetMonData
	b _021ED484
_021ED47E:
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021ED484:
	add r0, r7, #0
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blo _021ED430
_021ED490:
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021ED498: .word 0x0000FFFF

	thumb_func_start MOD05_021ED49C
MOD05_021ED49C: ; 0x021ED49C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	bl GetPartyCount
	add r6, r0, #0
	mov r5, #0
	cmp r6, #0
	ble _021ED4DA
_021ED4AC:
	add r0, r7, #0
	add r1, r5, #0
	bl GetPartyMonByIndex
	mov r1, #0x4c
	mov r2, #0
	add r4, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _021ED4D4
	add r0, r4, #0
	mov r1, #9
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _021ED4D4
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
_021ED4D4:
	add r5, r5, #1
	cmp r5, r6
	blt _021ED4AC
_021ED4DA:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021ED4E0
MOD05_021ED4E0: ; 0x021ED4E0
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	add r1, sp, #0
	bl MOD05_021EC88C
	ldr r0, [sp]
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	cmp r0, #0
	beq _021ED50E
	ldr r2, [sp]
	add r0, r4, #0
	mov r1, #0
	bl BufferBoxMonNickname
	ldr r2, [sp]
	add r0, r4, #0
	mov r1, #2
	bl BufferBoxMonOTName
_021ED50E:
	ldr r0, [sp, #4]
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	cmp r0, #0
	beq _021ED526
	ldr r2, [sp, #4]
	add r0, r4, #0
	mov r1, #1
	bl BufferBoxMonNickname
_021ED526:
	add sp, #8
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021ED52C
MOD05_021ED52C: ; 0x021ED52C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r1, sp, #0x18
	ldrb r6, [r1, #0x10]
	add r5, r0, #0
	add r7, r2, #0
	add r1, r6, #0
	str r3, [sp, #8]
	bl Sav2_DayCare_GetMonX
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD05_021EC458
	add r5, r0, #0
	ldr r0, [sp, #0x2c]
	add r1, r4, #0
	add r2, r5, #0
	bl BufferBoxMonNickname
	ldr r0, [sp, #0xc]
	bl DayCareMon_GetSteps
	add r1, r0, #0
	add r0, r5, #0
	bl MOD05_021EC744
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [sp, #0x2c]
	add r1, r7, #0
	mov r3, #3
	bl BufferIntegerAsString
	add r0, r5, #0
	mov r1, #0x6f
	mov r2, #0
	bl GetBoxMonData
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #2
	beq _021ED5B4
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #0x1d
	beq _021ED5A4
	cmp r0, #0x20
	bne _021ED5B4
_021ED5A4:
	add r0, r5, #0
	mov r1, #0x4d
	mov r2, #0
	bl GetBoxMonData
	cmp r0, #0
	bne _021ED5B4
	mov r4, #2
_021ED5B4:
	ldr r0, [sp, #0x2c]
	ldr r1, [sp, #8]
	add r2, r4, #0
	bl BufferGenderSymbol
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021ED5C4
MOD05_021ED5C4: ; 0x021ED5C4
	push {r3, r4, r5, lr}
	add r5, r2, #0
	bl GetPartyMonByIndex
	add r4, r0, #0
	bl FUN_020690E4
	add r2, r0, #0
	add r0, r5, #0
	mov r1, #0
	bl BufferBoxMonNickname
	add r0, r4, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021ED5EC
MOD05_021ED5EC: ; 0x021ED5EC
	push {r4, lr}
	add r4, r0, #0
	bl Sav2_DayCare_GetEggPID
	cmp r0, #0
	beq _021ED5FC
	mov r0, #1
	pop {r4, pc}
_021ED5FC:
	add r0, r4, #0
	bl MOD05_021EC464
	cmp r0, #0
	beq _021ED60E
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r4, pc}
_021ED60E:
	mov r0, #0
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021ED614
MOD05_021ED614: ; 0x021ED614
	cmp r0, #0x14
	bhi _021ED620
	bhs _021ED632
	cmp r0, #0
	beq _021ED62E
	b _021ED63E
_021ED620:
	cmp r0, #0x32
	bhi _021ED628
	beq _021ED636
	b _021ED63E
_021ED628:
	cmp r0, #0x46
	beq _021ED63A
	b _021ED63E
_021ED62E:
	mov r0, #3
	bx lr
_021ED632:
	mov r0, #2
	bx lr
_021ED636:
	mov r0, #1
	bx lr
_021ED63A:
	mov r0, #0
	bx lr
_021ED63E:
	mov r0, #0
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021ED644
MOD05_021ED644: ; 0x021ED644
	push {r3, lr}
	bl MOD05_021ED320
	bl MOD05_021ED614
	pop {r3, pc}

	thumb_func_start MOD05_021ED650
MOD05_021ED650: ; 0x021ED650
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	add r4, r0, #0
	add r5, r1, #0
	mov r0, #8
	bl String_ctor
	str r0, [sp, #0x10]
	add r0, r5, #0
	bl AllocMonZeroed
	add r6, r0, #0
	add r0, r4, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x14]
	mov r5, #0
	add r7, sp, #0x34
_021ED67C:
	add r1, r5, #0
	add r0, r4, #0
	add r1, #0x36
	mov r2, #0
	bl GetMonData
	lsl r1, r5, #1
	strh r0, [r7, r1]
	add r1, r5, #0
	add r0, r4, #0
	add r1, #0x3a
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x30
	strb r0, [r1, r5]
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #4
	blo _021ED67C
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl GetMonData
	add r7, r0, #0
	mov r5, #0
_021ED6B4:
	add r1, r5, #0
	add r0, r4, #0
	add r1, #0x46
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x24
	add r1, #2
	strb r0, [r1, r5]
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #6
	blo _021ED6B4
	add r0, r4, #0
	mov r1, #0xc
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x18
	strb r0, [r1, #9]
	add r0, r4, #0
	mov r1, #0x79
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x18
	strb r0, [r1, #8]
	add r0, r4, #0
	mov r1, #0xb
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x18
	strb r0, [r1, #7]
	add r0, r4, #0
	mov r1, #0x99
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x18
	strb r0, [r1, #0xa]
	add r0, r4, #0
	mov r1, #0x6e
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x18
	strb r0, [r1, #5]
	ldr r2, [sp, #0x10]
	add r0, r4, #0
	mov r1, #0x90
	bl GetMonData
	add r0, r4, #0
	mov r1, #0x9c
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x18
	strb r0, [r1, #3]
	add r0, r4, #0
	mov r1, #7
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0x2c]
	add r0, r4, #0
	mov r1, #0x70
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x18
	strb r0, [r1, #4]
	ldr r1, _021ED93C ; =0x000001EA
	ldr r0, [sp, #0x14]
	cmp r0, r1
	bne _021ED788
	add r0, r4, #0
	mov r1, #0x97
	mov r2, #0
	bl GetMonData
	add r5, r0, #0
	mov r0, #2
	mov r1, #1
	bl FUN_02015CF8
	cmp r5, r0
	bne _021ED788
	ldr r0, [sp, #0x2c]
	add r1, r7, #0
	bl CalcShininessByOtIdAndPersonality
	cmp r0, #0
	beq _021ED788
_021ED774:
	add r0, r7, #0
	bl PRandom
	add r7, r0, #0
	ldr r0, [sp, #0x2c]
	add r1, r7, #0
	bl CalcShininessByOtIdAndPersonality
	cmp r0, #0
	bne _021ED774
_021ED788:
	mov r2, #1
	str r2, [sp]
	str r7, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x14]
	add r0, r6, #0
	mov r3, #0x20
	bl CreateMon
	mov r5, #0
	add r7, sp, #0x34
_021ED7A2:
	add r1, r5, #0
	lsl r2, r5, #1
	add r0, r6, #0
	add r1, #0x36
	add r2, r7, r2
	bl SetMonData
	add r1, r5, #0
	add r2, sp, #0x30
	add r0, r6, #0
	add r1, #0x3a
	add r2, r2, r5
	bl SetMonData
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #4
	blo _021ED7A2
	add r7, sp, #0x24
	mov r5, #0
	add r7, #2
_021ED7CE:
	add r1, r5, #0
	add r0, r6, #0
	add r1, #0x46
	add r2, r7, r5
	bl SetMonData
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #6
	blo _021ED7CE
	add r2, sp, #0x20
	add r0, r6, #0
	mov r1, #0xc
	add r2, #1
	bl SetMonData
	add r0, r6, #0
	mov r1, #0x79
	add r2, sp, #0x20
	bl SetMonData
	add r2, sp, #0x1c
	add r0, r6, #0
	mov r1, #0xb
	add r2, #3
	bl SetMonData
	add r2, sp, #0x1c
	mov r1, #0x78
	add r0, sp, #0x18
	strb r1, [r0, #6]
	add r0, r6, #0
	mov r1, #9
	add r2, #2
	bl SetMonData
	add r2, sp, #0x20
	add r0, r6, #0
	mov r1, #0x99
	add r2, #2
	bl SetMonData
	add r2, sp, #0x1c
	add r0, r6, #0
	mov r1, #0x6e
	add r2, #1
	bl SetMonData
	ldr r2, [sp, #0x10]
	add r0, r6, #0
	mov r1, #0x90
	bl SetMonData
	add r2, sp, #0x18
	add r0, r6, #0
	mov r1, #0x9c
	add r2, #3
	bl SetMonData
	add r0, r6, #0
	mov r1, #7
	add r2, sp, #0x2c
	bl SetMonData
	add r0, r6, #0
	mov r1, #0x70
	add r2, sp, #0x1c
	bl SetMonData
	add r0, r4, #0
	mov r1, #0x97
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x18
	strh r0, [r1, #0xc]
	add r0, r4, #0
	mov r1, #0x91
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x18
	strb r0, [r1, #2]
	add r0, r4, #0
	mov r1, #0x92
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x18
	strb r0, [r1, #1]
	add r0, r4, #0
	mov r1, #0x93
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x18
	strb r0, [r1]
	add r0, r6, #0
	mov r1, #0x97
	add r2, sp, #0x24
	bl SetMonData
	add r2, sp, #0x18
	add r0, r6, #0
	mov r1, #0x91
	add r2, #2
	bl SetMonData
	add r2, sp, #0x18
	add r0, r6, #0
	mov r1, #0x92
	add r2, #1
	bl SetMonData
	add r0, r6, #0
	mov r1, #0x93
	add r2, sp, #0x18
	bl SetMonData
	add r0, r4, #0
	mov r1, #0x98
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x18
	strh r0, [r1, #0xc]
	add r0, r4, #0
	mov r1, #0x94
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x18
	strb r0, [r1, #2]
	add r0, r4, #0
	mov r1, #0x95
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x18
	strb r0, [r1, #1]
	add r0, r4, #0
	mov r1, #0x96
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x18
	strb r0, [r1]
	add r0, r6, #0
	mov r1, #0x98
	add r2, sp, #0x24
	bl SetMonData
	add r2, sp, #0x18
	add r0, r6, #0
	mov r1, #0x94
	add r2, #2
	bl SetMonData
	add r2, sp, #0x18
	add r0, r6, #0
	mov r1, #0x95
	add r2, #1
	bl SetMonData
	add r0, r6, #0
	mov r1, #0x96
	add r2, sp, #0x18
	bl SetMonData
	add r0, r6, #0
	add r1, r4, #0
	bl CopyPokemonToPokemon
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r6, #0
	bl FreeToHeap
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	nop
_021ED93C: .word 0x000001EA

	thumb_func_start MOD05_021ED940
MOD05_021ED940: ; 0x021ED940
	push {r4, r5, lr}
	sub sp, #0x1c
	mov r3, #0x46
	add r2, sp, #0
	strb r3, [r2, #3]
	mov r5, #0
	strb r5, [r2, #2]
	mov r3, #4
	strb r3, [r2, #1]
	add r4, r0, #0
	strb r5, [r2]
	bl MOD05_021ED650
	add r2, sp, #0
	add r0, r4, #0
	mov r1, #0x4c
	add r2, #3
	bl SetMonData
	add r0, r4, #0
	mov r1, #5
	add r2, r5, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r1, r5, #0
	add r2, sp, #4
	bl GetSpeciesNameIntoArray
	add r0, r4, #0
	mov r1, #0x74
	add r2, sp, #4
	bl SetMonData
	add r2, sp, #0
	add r0, r4, #0
	mov r1, #0x4d
	add r2, #2
	bl SetMonData
	add r2, sp, #0
	add r0, r4, #0
	mov r1, #0x9a
	add r2, #1
	bl SetMonData
	add r0, r4, #0
	mov r1, #0x9b
	add r2, sp, #0
	bl SetMonData
	add r0, r4, #0
	bl CalcMonLevelAndStats
	add sp, #0x1c
	pop {r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021ED9B4
MOD05_021ED9B4: ; 0x021ED9B4
	push {r3, lr}
	bl MOD05_021ED214
	bl MOD05_021ED614
	pop {r3, pc}

	thumb_func_start MOD05_021ED9C0
MOD05_021ED9C0: ; 0x021ED9C0
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #4
	add r3, r2, #0
	add r5, r0, #0
	bl MOD05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl MOD05_021ED9EC
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021ED9DC
MOD05_021ED9DC: ; 0x021ED9DC
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021EDA28
	add r0, r4, #0
	bl MOD05_021E4C00
	pop {r4, pc}

	thumb_func_start MOD05_021ED9EC
MOD05_021ED9EC: ; 0x021ED9EC
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #4
	mov r2, #0x57
	bl MOD05_021E5078
	ldr r0, [r4]
	mov r1, #3
	mov r2, #6
	mov r3, #1
	bl MOD05_021E50D4
	mov r0, #3
	str r0, [sp]
	mov r3, #0
	mov r1, #4
	ldr r0, _021EDA24 ; =UNK05_021F8A48
	str r3, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	add r2, r1, #0
	bl MOD05_021E4EFC
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_021EDA24: .word UNK05_021F8A48

	thumb_func_start MOD05_021EDA28
MOD05_021EDA28: ; 0x021EDA28
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #4
	bl MOD05_021E50A0
	ldr r0, [r4]
	mov r1, #3
	bl MOD05_021E5114
	ldr r0, [r4]
	mov r1, #4
	bl MOD05_021E506C
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EDA48
MOD05_021EDA48: ; 0x021EDA48
	push {r4, r5, lr}
	sub sp, #0x24
	add r5, r0, #0
	bl MOD05_021E4C24
	add r4, r0, #0
	add r0, r5, #0
	bl FUN_02058738
	str r0, [sp, #0x14]
	add r0, r4, #0
	mov r1, #0x18
	str r4, [sp, #0x18]
	bl MOD05_021E4C08
	str r0, [sp, #0x1c]
	add r1, sp, #8
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r0, r5, #0
	mov r1, #2
	str r5, [sp, #0x20]
	bl FUN_0205829C
	add r1, sp, #0x14
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _021EDA94 ; =UNK05_021F8A34
	add r0, r4, #0
	add r2, sp, #8
	mov r3, #0
	bl MOD05_021E4DC4
	add sp, #0x24
	pop {r4, r5, pc}
	nop
_021EDA94: .word UNK05_021F8A34

	thumb_func_start MOD05_021EDA98
MOD05_021EDA98: ; 0x021EDA98
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r2, sp, #0
	mov r1, #0
	str r1, [r2]
	str r1, [r2, #4]
	add r5, r0, #0
	str r1, [r2, #8]
	bl FUN_0206475C
	add r2, r4, #0
	add r3, r0, #0
	add r2, #0x10
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4, #0x1c]
	bl FUN_02058448
	str r0, [r4, #4]
	ldr r0, [r4, #0x1c]
	bl FUN_02058450
	str r0, [r4, #8]
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_0206476C
	ldr r0, [r4, #0x14]
	mov r1, #4
	add r2, sp, #0
	bl MOD05_021E4EE4
	str r0, [r4, #0x20]
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EDAE8
MOD05_021EDAE8: ; 0x021EDAE8
	ldr r3, _021EDAF0 ; =FUN_0201F744
	ldr r0, [r1, #0x20]
	bx r3
	nop
_021EDAF0: .word FUN_0201F744

	thumb_func_start MOD05_021EDAF4
MOD05_021EDAF4: ; 0x021EDAF4
	push {r4, lr}
	add r2, r1, #0
	add r4, r0, #0
	ldr r0, [r2, #0x1c]
	ldr r1, [r2, #4]
	ldr r2, [r2, #8]
	bl FUN_020582A8
	cmp r0, #0
	bne _021EDB0E
	add r0, r4, #0
	bl MOD05_021E4DE4
_021EDB0E:
	pop {r4, pc}

	thumb_func_start MOD05_021EDB10
MOD05_021EDB10: ; 0x021EDB10
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r5, r1, #0
	ldr r4, [r5, #0x1c]
	ldr r1, [r5, #4]
	add r6, r0, #0
	ldr r2, [r5, #8]
	add r0, r4, #0
	bl FUN_020582A8
	cmp r0, #0
	bne _021EDB32
	add r0, r6, #0
	bl MOD05_021E4DE4
	add sp, #0x18
	pop {r4, r5, r6, pc}
_021EDB32:
	add r0, r4, #0
	add r1, sp, #0xc
	bl FUN_02058B5C
	add r0, r4, #0
	add r1, sp, #0
	bl FUN_02058B84
	ldr r1, [sp, #0xc]
	ldr r0, [sp]
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #4]
	add r0, r1, r0
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #8]
	add r1, r1, r0
	mov r0, #3
	lsl r0, r0, #0xe
	str r1, [sp, #0x14]
	add r0, r1, r0
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x20]
	add r1, sp, #0xc
	bl FUN_0201F7C8
	add sp, #0x18
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EDB70
MOD05_021EDB70: ; 0x021EDB70
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x60
	add r3, r2, #0
	add r5, r0, #0
	bl MOD05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl MOD05_021EDB9C
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EDB8C
MOD05_021EDB8C: ; 0x021EDB8C
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021EDBBC
	add r0, r4, #0
	bl MOD05_021E4C00
	pop {r4, pc}

	thumb_func_start MOD05_021EDB9C
MOD05_021EDB9C: ; 0x021EDB9C
	push {r3, lr}
	sub sp, #8
	add r3, r0, #0
	add r0, #0x58
	str r0, [sp]
	add r0, r3, #0
	add r0, #0x5c
	str r0, [sp, #4]
	ldr r0, [r3]
	mov r1, #0x50
	mov r2, #0
	add r3, r3, #4
	bl MOD05_021E51EC
	add sp, #8
	pop {r3, pc}

	thumb_func_start MOD05_021EDBBC
MOD05_021EDBBC: ; 0x021EDBBC
	ldr r3, _021EDBC4 ; =MOD05_021E4C00
	ldr r0, [r0, #0x5c]
	bx r3
	nop
_021EDBC4: .word MOD05_021E4C00

	thumb_func_start MOD05_021EDBC8
MOD05_021EDBC8: ; 0x021EDBC8
	push {r4, r5, r6, lr}
	sub sp, #0x20
	add r2, sp, #8
	mov r1, #0
	str r1, [r2]
	str r1, [r2, #4]
	add r5, r0, #0
	str r1, [r2, #8]
	bl FUN_020553A0
	add r4, r0, #0
	bl MOD05_021E4C24
	add r6, r0, #0
	mov r1, #0x10
	str r6, [sp, #0x14]
	bl MOD05_021E4C08
	str r0, [sp, #0x18]
	add r0, r4, #0
	mov r1, #2
	str r5, [sp, #0x1c]
	bl FUN_0205829C
	add r1, sp, #0x14
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _021EDC10 ; =UNK05_021F8A6C
	add r0, r6, #0
	add r2, sp, #8
	mov r3, #0
	bl MOD05_021E4DC4
	add sp, #0x20
	pop {r4, r5, r6, pc}
	nop
_021EDC10: .word UNK05_021F8A6C

	thumb_func_start MOD05_021EDC14
MOD05_021EDC14: ; 0x021EDC14
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl FUN_0206475C
	add r4, r0, #0
	add r3, r4, #0
	add r2, r5, #0
	ldmia r3!, {r0, r1}
	add r2, #0x24
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #8]
	bl FUN_020553A0
	mov r1, #0
	mvn r1, r1
	add r4, r0, #0
	str r1, [r5, #4]
	bl FUN_02058448
	str r0, [r5, #0x14]
	add r0, r4, #0
	bl FUN_02058450
	str r0, [r5, #0x18]
	mov r0, #1
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021EDC4C
MOD05_021EDC4C: ; 0x021EDC4C
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021EDC50
MOD05_021EDC50: ; 0x021EDC50
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r1, #0
	str r0, [sp]
	ldr r0, [r5, #0x2c]
	str r0, [sp, #4]
	bl FUN_020553A0
	ldr r1, [r5, #0x14]
	ldr r2, [r5, #0x18]
	add r6, r0, #0
	bl FUN_020582A8
	cmp r0, #0
	bne _021EDC78
	ldr r0, [sp]
	bl MOD05_021E4DE4
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
_021EDC78:
	ldr r7, [r5, #4]
	add r0, r6, #0
	bl FUN_02058720
	strb r0, [r5, #8]
	ldrb r0, [r5, #8]
	bl MOD05_021EDDF4
	str r0, [r5, #4]
	mov r0, #0
	str r0, [r5]
	ldr r4, [r5, #4]
	sub r0, r0, #1
	cmp r4, r0
	beq _021EDCA0
	ldr r0, [sp, #4]
	bl FUN_020552F8
	cmp r4, r0
	beq _021EDCAE
_021EDCA0:
	mov r0, #0
	str r0, [r5, #0x1c]
	str r0, [r5, #0x20]
	mov r0, #1
	add sp, #0x24
	str r0, [r5]
	pop {r4, r5, r6, r7, pc}
_021EDCAE:
	cmp r7, r4
	beq _021EDCB8
	mov r0, #0
	str r0, [r5, #0x1c]
	str r0, [r5, #0x20]
_021EDCB8:
	add r0, r6, #0
	bl FUN_02058B2C
	add r4, r0, #0
	ldr r0, [r5, #4]
	bl FUN_02059BF4
	add r7, r0, #0
	add r0, r6, #0
	bl FUN_02058B4C
	str r0, [sp, #8]
	ldr r0, [r5, #4]
	bl FUN_02059C00
	add r2, r0, #0
	ldr r1, [sp, #8]
	add r0, r4, r7
	add r1, r1, r2
	add r2, sp, #0xc
	bl FUN_02059E60
	add r0, r6, #0
	add r1, sp, #0x18
	bl FUN_02058B5C
	ldr r0, [sp, #0x1c]
	add r1, sp, #0xc
	str r0, [sp, #0x10]
	ldr r0, [sp]
	bl FUN_0206476C
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021EDCFC
MOD05_021EDCFC: ; 0x021EDCFC
	push {r3, r4, r5, r6, lr}
	sub sp, #0x3c
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	cmp r0, #1
	beq _021EDDE2
	mov r0, #0
	ldr r1, [r4, #4]
	mvn r0, r0
	cmp r1, r0
	beq _021EDDE2
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
	cmp r0, #0xf
	ble _021EDD34
	mov r0, #0
	str r0, [r4, #0x1c]
	ldr r0, [r4, #0x20]
	add r0, r0, #1
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	str r0, [r4, #0x20]
_021EDD34:
	ldr r3, _021EDDE8 ; =UNK05_021F8A60
	add r2, sp, #0x24
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _021EDDEC ; =UNK05_021F8A80
	str r0, [r2]
	add r3, sp, #0
	mov r2, #4
_021EDD46:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021EDD46
	ldr r0, [r5]
	mov r2, #0x18
	str r0, [r3]
	ldr r1, [r4, #4]
	ldr r3, _021EDDF0 ; =UNK05_021F8AA4
	add r0, r1, #0
	mul r0, r2
	add r0, r3, r0
	ldr r5, [r4, #0x20]
	mov r3, #0xc
	mul r3, r5
	add r5, r0, r3
	cmp r1, #3
	bhi _021EDDB4
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EDD76: ; jump table
	.short _021EDD7E - _021EDD76 - 2 ; case 0
	.short _021EDD8C - _021EDD76 - 2 ; case 1
	.short _021EDD9A - _021EDD76 - 2 ; case 2
	.short _021EDDA8 - _021EDD76 - 2 ; case 3
_021EDD7E:
	mov r1, #0
	add r0, sp, #0
	mov r2, #0xb4
	add r3, r1, #0
	bl FUN_0201CB20
	b _021EDDB4
_021EDD8C:
	mov r1, #0
	add r0, sp, #0
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0201CB20
	b _021EDDB4
_021EDD9A:
	mov r1, #0
	add r0, sp, #0
	add r2, #0xf6
	add r3, r1, #0
	bl FUN_0201CB20
	b _021EDDB4
_021EDDA8:
	mov r1, #0
	add r0, sp, #0
	mov r2, #0x5a
	add r3, r1, #0
	bl FUN_0201CB20
_021EDDB4:
	add r0, r6, #0
	add r1, sp, #0x30
	bl FUN_0206477C
	ldr r1, [sp, #0x30]
	ldr r0, [r5]
	add r2, sp, #0
	add r0, r1, r0
	str r0, [sp, #0x30]
	ldr r1, [sp, #0x34]
	ldr r0, [r5, #4]
	add r3, sp, #0x24
	add r0, r1, r0
	str r0, [sp, #0x34]
	ldr r1, [sp, #0x38]
	ldr r0, [r5, #8]
	add r0, r1, r0
	str r0, [sp, #0x38]
	ldr r0, [r4, #0x28]
	add r1, sp, #0x30
	add r0, r0, #4
	bl FUN_0201B26C
_021EDDE2:
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
	nop
_021EDDE8: .word UNK05_021F8A60
_021EDDEC: .word UNK05_021F8A80
_021EDDF0: .word UNK05_021F8AA4

	thumb_func_start MOD05_021EDDF4
MOD05_021EDDF4: ; 0x021EDDF4
	push {r4, lr}
	add r4, r0, #0
	bl FUN_020547D4
	cmp r0, #0
	beq _021EDE04
	mov r0, #0
	pop {r4, pc}
_021EDE04:
	add r0, r4, #0
	bl FUN_020547E0
	cmp r0, #0
	beq _021EDE12
	mov r0, #1
	pop {r4, pc}
_021EDE12:
	add r0, r4, #0
	bl FUN_020547C8
	cmp r0, #0
	beq _021EDE20
	mov r0, #2
	pop {r4, pc}
_021EDE20:
	add r0, r4, #0
	bl FUN_020547BC
	cmp r0, #0
	beq _021EDE2E
	mov r0, #3
	pop {r4, pc}
_021EDE2E:
	mov r0, #0
	mvn r0, r0
	pop {r4, pc}

	thumb_func_start MOD05_021EDE34
MOD05_021EDE34: ; 0x021EDE34
	push {r4, r5, r6, lr}
	add r6, r2, #0
	add r5, r1, #0
	add r1, r6, #0
	bl _s32_div_f
	add r4, r1, #0
	add r0, r5, #0
	add r1, r6, #0
	bl _s32_div_f
	cmp r4, r1
	bne _021EDE52
	mov r0, #1
	pop {r4, r5, r6, pc}
_021EDE52:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EDE58
MOD05_021EDE58: ; 0x021EDE58
	push {r4, r5, r6, lr}
	add r6, r2, #0
	add r5, r1, #0
	add r1, r6, #0
	bl _s32_div_f
	add r4, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl _s32_div_f
	cmp r4, r0
	bne _021EDE76
	mov r0, #1
	pop {r4, r5, r6, pc}
_021EDE76:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EDE7C
MOD05_021EDE7C: ; 0x021EDE7C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x30
	add r4, r1, #0
	mul r4, r0
	add r1, r5, r4
	ldr r0, [r1, #0x14]
	cmp r0, #0
	beq _021EDE94
	ldr r0, [r1, #0xc]
	bl MOD05_021EF8F8
_021EDE94:
	add r1, r5, r4
	ldr r0, [r1, #0x18]
	cmp r0, #0
	beq _021EDEA2
	ldr r0, [r1, #0x10]
	bl MOD05_021F4444
_021EDEA2:
	mov r1, #1
	add r0, r5, r4
	str r1, [r0, #0x28]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EDEAC
MOD05_021EDEAC: ; 0x021EDEAC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _021EDEBC
	ldr r0, [r4, #8]
	bl MOD05_021EF8F8
_021EDEBC:
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021EDEC8
	ldr r0, [r4, #0xc]
	bl MOD05_021F4444
_021EDEC8:
	mov r0, #0
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	pop {r4, pc}

	thumb_func_start MOD05_021EDED0
MOD05_021EDED0: ; 0x021EDED0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r2, #0
	asr r2, r0, #4
	lsr r2, r2, #0x1b
	add r2, r0, r2
	asr r7, r2, #5
	asr r2, r1, #4
	lsr r2, r2, #0x1b
	add r2, r1, r2
	asr r6, r2, #5
	ldr r2, [sp, #0x18]
	str r3, [sp]
	ldr r4, [sp, #0x1c]
	bl MOD05_021EEE08
	ldr r1, [sp, #0x18]
	bl MOD05_021EF620
	add r1, r6, #0
	mul r1, r5
	add r1, r7, r1
	cmp r0, #3
	bhi _021EDFB6
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EDF0A: ; jump table
	.short _021EDF12 - _021EDF0A - 2 ; case 0
	.short _021EDF38 - _021EDF0A - 2 ; case 1
	.short _021EDF60 - _021EDF0A - 2 ; case 2
	.short _021EDF8A - _021EDF0A - 2 ; case 3
_021EDF12:
	sub r2, r1, r5
	str r1, [r4, #0xc]
	sub r0, r2, #1
	str r0, [r4]
	str r2, [r4, #4]
	sub r0, r1, #1
	str r0, [r4, #8]
	sub r0, r7, #1
	bpl _021EDF2C
	mov r0, #0
	mvn r0, r0
	str r0, [r4]
	str r0, [r4, #8]
_021EDF2C:
	sub r0, r6, #1
	bpl _021EDFBA
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #4]
	pop {r3, r4, r5, r6, r7, pc}
_021EDF38:
	str r1, [r4, #8]
	sub r0, r1, r5
	str r0, [r4]
	add r0, r0, #1
	str r0, [r4, #4]
	add r0, r1, #1
	str r0, [r4, #0xc]
	add r0, r7, #1
	cmp r0, r5
	blt _021EDF54
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #4]
	str r0, [r4, #0xc]
_021EDF54:
	sub r0, r6, #1
	bpl _021EDFBA
	mov r0, #0
	mvn r0, r0
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_021EDF60:
	str r1, [r4, #4]
	sub r0, r1, #1
	add r1, r1, r5
	str r0, [r4]
	sub r0, r1, #1
	str r0, [r4, #8]
	str r1, [r4, #0xc]
	sub r0, r7, #1
	bpl _021EDF7A
	mov r0, #0
	mvn r0, r0
	str r0, [r4]
	str r0, [r4, #8]
_021EDF7A:
	ldr r0, [sp]
	add r1, r6, #1
	cmp r1, r0
	ble _021EDFBA
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_021EDF8A:
	str r1, [r4]
	add r0, r1, #1
	str r0, [r4, #4]
	add r0, r1, r5
	str r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #0xc]
	add r0, r7, #1
	cmp r0, r5
	blt _021EDFA6
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #4]
	str r0, [r4, #0xc]
_021EDFA6:
	ldr r0, [sp]
	add r1, r6, #1
	cmp r1, r0
	ble _021EDFBA
	mov r0, #0
	mvn r0, r0
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_021EDFB6:
	bl GF_AssertFail
_021EDFBA:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021EDFBC
MOD05_021EDFBC: ; 0x021EDFBC
	push {r3, r4, r5, r6, r7, lr}
	mov r6, #0
	add r5, r0, #0
	sub r7, r6, #1
_021EDFC4:
	ldr r1, _021EE03C ; =0x0000086C
	mov r0, #4
	bl AllocFromHeap
	lsl r4, r6, #2
	add r1, r5, r4
	add r1, #0x90
	str r0, [r1]
	add r0, r5, r4
	add r0, #0x90
	ldr r2, [r0]
	ldr r0, _021EE040 ; =0x00000864
	mov r1, #0
	str r1, [r2, r0]
	add r2, r5, r4
	add r2, #0x90
	ldr r3, [r2]
	ldr r2, _021EE044 ; =0x00000854
	ldr r1, [r5]
	add r0, r6, #0
	add r2, r3, r2
	bl MOD05_021F3C60
	add r2, r5, r4
	add r2, #0x90
	ldr r3, [r2]
	ldr r2, _021EE048 ; =0x00000858
	ldr r1, [r5]
	add r0, r6, #0
	add r2, r3, r2
	bl MOD05_021F3C68
	mov r0, #4
	bl MOD05_021E7C00
	add r1, r5, r4
	add r1, #0x90
	ldr r2, [r1]
	ldr r1, _021EE04C ; =0x00000868
	str r0, [r2, r1]
	add r0, r5, r4
	add r0, #0x90
	ldr r1, [r0]
	mov r0, #0x86
	lsl r0, r0, #4
	str r7, [r1, r0]
	add r1, r5, r4
	add r1, #0x90
	mov r2, #2
	ldr r1, [r1]
	add r0, r7, #0
	lsl r2, r2, #0xa
	bl MIi_CpuClearFast
	add r0, r6, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #4
	blo _021EDFC4
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EE03C: .word 0x0000086C
_021EE040: .word 0x00000864
_021EE044: .word 0x00000854
_021EE048: .word 0x00000858
_021EE04C: .word 0x00000868

	thumb_func_start MOD05_021EE050
MOD05_021EE050: ; 0x021EE050
	push {r3, r4, r5, r6, r7, lr}
	mov r6, #0
	add r5, r0, #0
	add r7, r6, #0
_021EE058:
	ldr r1, _021EE0B0 ; =0x0000086C
	mov r0, #4
	bl AllocFromHeap
	lsl r4, r6, #2
	add r1, r5, r4
	add r1, #0x90
	str r0, [r1]
	add r0, r5, r4
	add r0, #0x90
	ldr r1, [r0]
	ldr r0, _021EE0B4 ; =0x00000864
	add r2, r5, r4
	str r7, [r1, r0]
	add r2, #0x90
	ldr r3, [r2]
	ldr r2, _021EE0B8 ; =0x00000854
	ldr r1, [r5]
	add r0, r6, #0
	add r2, r3, r2
	bl MOD05_021F3C60
	mov r0, #4
	bl MOD05_021E7C00
	add r1, r5, r4
	add r1, #0x90
	ldr r2, [r1]
	ldr r1, _021EE0BC ; =0x00000868
	str r0, [r2, r1]
	add r0, r5, r4
	add r0, #0x90
	ldr r2, [r0]
	mov r1, #0
	mov r0, #0x86
	mvn r1, r1
	lsl r0, r0, #4
	str r1, [r2, r0]
	add r0, r6, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #4
	blo _021EE058
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EE0B0: .word 0x0000086C
_021EE0B4: .word 0x00000864
_021EE0B8: .word 0x00000854
_021EE0BC: .word 0x00000868

	thumb_func_start MOD05_021EE0C0
MOD05_021EE0C0: ; 0x021EE0C0
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	add r5, r2, #0
	cmp r6, #0
	beq _021EE0E6
	mov r0, #4
	mov r1, #0x10
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	add r0, r6, #0
	add r1, r7, #0
	mov r2, #0
	mov r3, #0x10
	str r4, [sp]
	bl NARC_ReadFromMember
	b _021EE0FC
_021EE0E6:
	bl GF_AssertFail
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0x43
	add r1, r7, #0
	mov r2, #4
	mov r3, #0
	bl AllocAtEndAndReadFromNarcMemberByIdPair
	add r4, r0, #0
_021EE0FC:
	ldr r0, [r4]
	str r0, [r5]
	ldr r0, [r4, #4]
	str r0, [r5, #0xc]
	ldr r0, [r4, #8]
	str r0, [r5, #4]
	ldr r0, [r4, #0xc]
	str r0, [r5, #8]
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021EE114
MOD05_021EE114: ; 0x021EE114
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	ldr r4, [sp, #0x40]
	lsl r7, r0, #2
	add r0, r4, r7
	ldr r0, [r0, #0x18]
	str r1, [sp, #0xc]
	ldr r5, [sp, #0x3c]
	cmp r0, #0
	blt _021EE1D0
	ldr r1, [sp, #0x38]
	mul r1, r3
	cmp r0, r1
	bge _021EE1D0
	add r1, r2, #0
	bl FUN_02034660
	add r1, r0, #0
	ldr r0, _021EE1D4 ; =0x0000FFFF
	cmp r1, r0
	beq _021EE1D0
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	add r2, sp, #0x10
	bl MOD05_021EE0C0
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	ldr r1, [sp, #0x10]
	ldr r2, [r4, r7]
	bl NARC_ReadFile
	add r0, r5, #0
	add r0, #0xf0
	ldr r0, [r0]
	ldr r3, _021EE1D8 ; =0x00000868
	str r0, [sp]
	add r0, r5, #0
	ldr r6, [r4, r7]
	add r0, #0xf8
	ldr r0, [r0]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0xc]
	ldr r3, [r6, r3]
	bl MOD05_021E7CD8
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	ldr r0, [sp, #0xc]
	ldr r6, [r4, r7]
	bl MOD05_021F4C74
	ldr r3, _021EE1DC ; =0x00000864
	str r0, [sp]
	add r0, r6, r3
	add r2, r3, #0
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x10
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xf8
	sub r2, #0x64
	sub r3, #0x10
	ldr r0, [r0]
	ldr r1, [sp, #0x14]
	add r2, r6, r2
	add r3, r6, r3
	bl MOD05_021EFA00
	str r0, [r4, #8]
	ldr r0, [r4, #0x14]
	add r3, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x14]
	ldr r2, [r4, r7]
	ldr r6, _021EE1E0 ; =0x00000858
	add r5, #0xf8
	add r0, r2, r6
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x10
	str r0, [sp, #4]
	ldr r0, [r5]
	add r5, r6, #4
	ldr r1, [sp, #0x18]
	ldr r2, [r2, r5]
	add r3, #0x14
	bl MOD05_021F43E4
	str r0, [r4, #0xc]
_021EE1D0:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EE1D4: .word 0x0000FFFF
_021EE1D8: .word 0x00000868
_021EE1DC: .word 0x00000864
_021EE1E0: .word 0x00000858

	thumb_func_start MOD05_021EE1E4
MOD05_021EE1E4: ; 0x021EE1E4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x30
	str r1, [sp, #0xc]
	add r1, r2, #0
	add r2, r3, #0
	ldr r3, _021EE294 ; =0x00000828
	lsl r7, r0, #2
	add r3, sp
	ldr r4, [r3, #0x18]
	ldr r5, [r3, #0x14]
	add r0, r4, r7
	ldr r0, [r0, #0x18]
	cmp r0, #0
	blt _021EE286
	ldr r3, [r3, #0x10]
	mul r3, r2
	cmp r0, r3
	bge _021EE286
	bl FUN_02034660
	add r1, r0, #0
	ldr r0, _021EE298 ; =0x0000FFFF
	cmp r1, r0
	beq _021EE286
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	add r2, sp, #0x10
	bl MOD05_021EE0C0
	add r0, r5, #0
	add r0, #0xf8
	mov r1, #2
	ldr r0, [r0]
	lsl r1, r1, #0xa
	add r2, sp, #0x20
	bl NARC_ReadFile
	add r0, r5, #0
	add r0, #0xf0
	ldr r0, [r0]
	ldr r3, _021EE29C ; =0x00000868
	str r0, [sp]
	add r0, r5, #0
	ldr r6, [r4, r7]
	add r0, #0xf8
	ldr r0, [r0]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0xc]
	ldr r3, [r6, r3]
	bl MOD05_021E7CD8
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	ldr r0, [sp, #0xc]
	ldr r6, [r4, r7]
	bl MOD05_021F4C74
	ldr r3, _021EE2A0 ; =0x00000864
	str r0, [sp]
	add r0, r6, r3
	add r2, r3, #0
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x10
	str r0, [sp, #8]
	add r5, #0xf8
	sub r2, #0x64
	sub r3, #0x10
	ldr r0, [r5]
	ldr r1, [sp, #0x14]
	add r2, r6, r2
	add r3, r6, r3
	bl MOD05_021EFA00
	str r0, [r4, #8]
_021EE286:
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021EE294: .word 0x00000828
_021EE298: .word 0x0000FFFF
_021EE29C: .word 0x00000868
_021EE2A0: .word 0x00000864

	thumb_func_start MOD05_021EE2A4
MOD05_021EE2A4: ; 0x021EE2A4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r1, #0
	str r0, [sp, #4]
	str r2, [sp, #8]
	ldr r7, [sp, #0x3c]
	add r1, r0, #0
	bmi _021EE37A
	ldr r2, [sp, #0x30]
	ldr r1, [sp, #0x34]
	add r5, r2, #0
	mul r5, r1
	add r1, r0, #0
	cmp r1, r5
	bge _021EE37A
	add r1, r3, #0
	bl FUN_02034660
	add r1, r0, #0
	ldr r0, _021EE380 ; =0x0000FFFF
	cmp r1, r0
	beq _021EE37A
	add r0, r7, #0
	add r0, #0xf8
	ldr r0, [r0]
	add r2, sp, #0xc
	bl MOD05_021EE0C0
	lsl r5, r4, #2
	add r4, r7, #0
	add r0, r7, #0
	add r4, #0x90
	add r0, #0xf8
	ldr r0, [r0]
	ldr r1, [sp, #0xc]
	ldr r2, [r4, r5]
	bl NARC_ReadFile
	add r0, r7, #0
	add r0, #0xf0
	ldr r0, [r0]
	ldr r3, _021EE384 ; =0x00000868
	str r0, [sp]
	add r0, r7, #0
	ldr r6, [r4, r5]
	add r0, #0xf8
	ldr r0, [r0]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #8]
	ldr r3, [r6, r3]
	bl MOD05_021E7CD8
	ldr r6, [r4, r5]
	ldr r0, [sp, #8]
	bl MOD05_021F4C74
	str r0, [sp]
	add r0, r7, #0
	mov r3, #2
	add r0, #0xf8
	lsl r3, r3, #0xa
	add r2, r6, r3
	add r3, #0x54
	ldr r0, [r0]
	ldr r1, [sp, #0x10]
	add r3, r6, r3
	bl MOD05_021EFA40
	ldr r1, [sp, #0x38]
	cmp r1, #1
	bne _021EE336
	bl MOD05_021DB5EC
_021EE336:
	ldr r6, _021EE388 ; =0x00000864
	ldr r0, [r4, r5]
	mov r1, #1
	str r1, [r0, r6]
	add r2, r6, #0
	add r0, r7, #0
	add r0, #0xf8
	ldr r3, [r4, r5]
	sub r2, #8
	sub r6, #0xc
	ldr r2, [r3, r2]
	ldr r0, [r0]
	ldr r1, [sp, #0x14]
	ldr r3, [r3, r6]
	bl MOD05_021F4344
	mov r2, #0x86
	ldr r1, [r4, r5]
	ldr r0, [sp, #4]
	lsl r2, r2, #4
	str r0, [r1, r2]
	add r0, r7, #0
	add r0, #0xfc
	ldr r3, [r0]
	cmp r3, #0
	beq _021EE37A
	mov r0, #1
	lsl r0, r0, #8
	ldr r4, [r4, r5]
	add r2, #8
	ldr r0, [r7, r0]
	ldr r1, [sp, #4]
	ldr r2, [r4, r2]
	blx r3
_021EE37A:
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021EE380: .word 0x0000FFFF
_021EE384: .word 0x00000868
_021EE388: .word 0x00000864

	thumb_func_start MOD05_021EE38C
MOD05_021EE38C: ; 0x021EE38C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x2c
	str r2, [sp, #8]
	ldr r2, _021EE44C ; =0x00000820
	add r4, r1, #0
	add r2, sp
	str r0, [sp, #4]
	ldr r5, [r2, #0x1c]
	add r1, r0, #0
	bmi _021EE43E
	ldr r6, [r2, #0x10]
	ldr r1, [r2, #0x14]
	add r2, r6, #0
	mul r2, r1
	add r1, r0, #0
	cmp r1, r2
	bge _021EE43E
	add r1, r3, #0
	bl FUN_02034660
	add r1, r0, #0
	ldr r0, _021EE450 ; =0x0000FFFF
	cmp r1, r0
	beq _021EE43E
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	add r2, sp, #0xc
	bl MOD05_021EE0C0
	add r0, r5, #0
	add r0, #0xf8
	mov r1, #2
	ldr r0, [r0]
	lsl r1, r1, #0xa
	add r2, sp, #0x1c
	bl NARC_ReadFile
	add r0, r5, #0
	add r0, #0xf0
	ldr r0, [r0]
	add r7, r5, #0
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xf8
	lsl r4, r4, #2
	add r7, #0x90
	ldr r6, [r7, r4]
	ldr r3, _021EE454 ; =0x00000868
	ldr r0, [r0]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #8]
	ldr r3, [r6, r3]
	bl MOD05_021E7CD8
	ldr r0, [sp, #8]
	ldr r6, [r7, r4]
	bl MOD05_021F4C74
	mov r3, #2
	str r0, [sp]
	add r5, #0xf8
	lsl r3, r3, #0xa
	add r2, r6, r3
	add r3, #0x54
	ldr r0, [r5]
	ldr r1, [sp, #0x10]
	add r3, r6, r3
	bl MOD05_021EFA40
	ldr r1, _021EE44C ; =0x00000820
	add r1, sp
	ldr r1, [r1, #0x18]
	cmp r1, #1
	bne _021EE42E
	bl MOD05_021DB5EC
_021EE42E:
	ldr r1, [r7, r4]
	ldr r0, _021EE458 ; =0x00000864
	mov r2, #1
	str r2, [r1, r0]
	sub r1, r0, #4
	ldr r2, [r7, r4]
	ldr r0, [sp, #4]
	str r0, [r2, r1]
_021EE43E:
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_021EE44C: .word 0x00000820
_021EE450: .word 0x0000FFFF
_021EE454: .word 0x00000868
_021EE458: .word 0x00000864

	thumb_func_start MOD05_021EE45C
MOD05_021EE45C: ; 0x021EE45C
	ldr r1, [r0]
	cmp r1, #0
	bne _021EE46C
	ldr r0, [r0, #4]
	cmp r0, #0
	bne _021EE46C
	mov r0, #1
	bx lr
_021EE46C:
	mov r0, #0
	bx lr

	thumb_func_start MOD05_021EE470
MOD05_021EE470: ; 0x021EE470
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	str r3, [sp]
	add r0, sp, #0x10
	add r7, r1, #0
	ldrb r1, [r0, #0x14]
	mov r0, #0x30
	str r2, [sp, #8]
	add r5, r1, #0
	mul r5, r0
	add r0, r4, #0
	str r0, [sp, #4]
	add r0, #0x2c
	str r0, [sp, #4]
	ldr r0, [r0, r5]
	cmp r0, #0
	beq _021EE498
	bl GF_AssertFail
_021EE498:
	ldr r0, [sp, #4]
	mov r1, #1
	str r1, [r0, r5]
	add r0, sp, #0x10
	add r5, r4, r5
	add r1, r5, #0
	ldrb r2, [r0, #0x18]
	add r1, #0x30
	add r3, r4, #0
	strb r2, [r1]
	add r2, r5, #0
	ldr r1, [sp, #8]
	str r7, [r5, #0x1c]
	str r1, [r5, #0x20]
	ldr r1, [sp]
	add r2, #0x24
	strb r1, [r2]
	add r1, r5, #0
	ldrb r0, [r0, #0x10]
	add r1, #0x25
	add r3, #0x90
	strb r0, [r1]
	ldr r1, [sp]
	mov r6, #0
	lsl r2, r1, #2
	ldr r1, [r3, r2]
	str r1, [r5, #4]
	lsl r1, r0, #2
	ldr r0, [r3, r1]
	str r0, [r5, #8]
	add r0, r5, #0
	add r0, #0x26
	strb r6, [r0]
	add r0, r6, #0
	str r0, [r5, #0x28]
	add r0, r4, #0
	add r0, #0xa0
	ldrb r0, [r0]
	cmp r0, #0
	bne _021EE4F0
	add r5, r4, #0
	add r5, #0xb4
	add r0, r6, #0
	str r0, [r5]
_021EE4F0:
	ldr r0, [r3, r2]
	mov r2, #0x86
	lsl r2, r2, #4
	str r7, [r0, r2]
	ldr r1, [r3, r1]
	ldr r0, [sp, #8]
	str r0, [r1, r2]
	add r0, r4, #0
	add r0, #0xa0
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xa0
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0xa1
	ldrb r0, [r0]
	add r4, #0xa1
	add r0, r0, #1
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	strb r0, [r4]
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EE52C
MOD05_021EE52C: ; 0x021EE52C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r1, #0
	add r0, r5, #0
	add r0, #0xa2
	ldrb r1, [r0]
	mov r0, #0x30
	add r4, r5, #0
	add r2, r5, #4
	mul r0, r1
	add r4, #0xcc
	add r6, r2, r0
	ldr r0, [r4, #0x20]
	cmp r0, #1
	bne _021EE572
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _021EE5D0
	ldr r0, [r4, #0x14]
	ldr r1, [r0]
	ldr r0, [r4, #0x10]
	ldr r0, [r0]
	cmp r1, r0
	ble _021EE560
	bl GF_AssertFail
_021EE560:
	ldr r0, [r4, #0x10]
	ldr r1, [r0]
	ldr r0, [r4, #0x14]
	ldr r0, [r0]
	sub r1, r1, r0
	mov r0, #1
	lsl r0, r0, #0x10
	cmp r1, r0
	bge _021EE574
_021EE572:
	b _021EE6B0
_021EE574:
	ldr r1, [r4, #0xc]
	add r2, sp, #0x10
	ldr r0, [r1]
	ldr r1, [r1, #8]
	add r3, sp, #0xc
	bl MOD05_021EF4F8
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0xc]
	add r2, r5, #0
	bl MOD05_021EF2AC
	ldr r3, [r4, #0xc]
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #8]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x11
	sub r1, r1, r2
	mov r0, #0x11
	ror r1, r0
	add r0, r2, r1
	beq _021EE5B2
	mov r0, #1
	bl FUN_020336A0
	cmp r0, #0
	bne _021EE692
_021EE5B2:
	ldr r0, [r4, #8]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x11
	sub r1, r1, r2
	mov r0, #0x11
	ror r1, r0
	add r0, r2, r1
	beq _021EE5C6
	bl GF_AssertFail
_021EE5C6:
	mov r0, #0
	str r0, [r4, #0x18]
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	b _021EE6B0
_021EE5D0:
	ldr r2, [r4, #0xc]
	ldr r3, [r4]
	ldr r7, [r2]
	cmp r3, r7
	beq _021EE5E8
	ldr r1, [r4, #8]
	ldr r0, [r2, #8]
	cmp r1, r0
	beq _021EE5E8
	bl GF_AssertFail
	b _021EE6B0
_021EE5E8:
	cmp r3, r7
	bne _021EE5F4
	ldr r1, [r4, #8]
	ldr r0, [r2, #8]
	cmp r1, r0
	beq _021EE6B0
_021EE5F4:
	mov r3, #1
	str r3, [r4, #0x18]
	ldr r2, [r4, #0xc]
	ldr r0, [r4]
	ldr r1, [r2]
	cmp r0, r1
	beq _021EE648
	cmp r0, r1
	ble _021EE612
	str r4, [r4, #0x10]
	ldr r0, [r4, #0xc]
	str r0, [r4, #0x14]
	mov r0, #3
	strb r0, [r4, #0x1c]
	b _021EE618
_021EE612:
	str r2, [r4, #0x10]
	str r4, [r4, #0x14]
	strb r3, [r4, #0x1c]
_021EE618:
	ldr r0, [r4]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x11
	sub r1, r1, r2
	mov r0, #0x11
	ror r1, r0
	add r0, r2, r1
	beq _021EE632
	mov r0, #1
	bl FUN_020336A0
	cmp r0, #0
	bne _021EE692
_021EE632:
	ldr r0, [r4]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x11
	sub r1, r1, r2
	mov r0, #0x11
	ror r1, r0
	add r0, r2, r1
	beq _021EE6A8
	bl GF_AssertFail
	b _021EE6A8
_021EE648:
	add r1, r5, #0
	add r1, #0xd8
	add r0, r5, #0
	ldr r1, [r1]
	add r0, #0xd4
	ldr r0, [r0]
	ldr r1, [r1, #8]
	cmp r0, r1
	ble _021EE66A
	add r0, r4, #0
	add r0, #8
	str r0, [r4, #0x10]
	ldr r0, [r4, #0xc]
	add r0, #8
	str r0, [r4, #0x14]
	mov r0, #4
	b _021EE676
_021EE66A:
	add r2, #8
	add r0, r4, #0
	str r2, [r4, #0x10]
	add r0, #8
	str r0, [r4, #0x14]
	mov r0, #2
_021EE676:
	strb r0, [r4, #0x1c]
	ldr r0, [r4, #8]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x11
	sub r1, r1, r2
	mov r0, #0x11
	ror r1, r0
	add r0, r2, r1
	beq _021EE694
	mov r0, #1
	bl FUN_020336A0
	cmp r0, #0
	beq _021EE694
_021EE692:
	b _021EE8C2
_021EE694:
	ldr r0, [r4, #8]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x11
	sub r1, r1, r2
	mov r0, #0x11
	ror r1, r0
	add r0, r2, r1
	beq _021EE6A8
	bl GF_AssertFail
_021EE6A8:
	ldrb r0, [r4, #0x1c]
	add r1, r5, #0
	bl MOD05_021EF458
_021EE6B0:
	add r0, r5, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #3
	bls _021EE6BC
	b _021EE818
_021EE6BC:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EE6C8: ; jump table
	.short _021EE6D0 - _021EE6C8 - 2 ; case 0
	.short _021EE726 - _021EE6C8 - 2 ; case 1
	.short _021EE818 - _021EE6C8 - 2 ; case 2
	.short _021EE804 - _021EE6C8 - 2 ; case 3
_021EE6D0:
	add r0, r6, #0
	add r0, #0x22
	ldrb r0, [r0]
	add r1, r6, r0
	add r1, #0x20
	ldrb r1, [r1]
	lsl r1, r1, #2
	add r1, r5, r1
	add r1, #0x80
	ldr r1, [r1]
	cmp r1, #1
	beq _021EE710
	add r1, r5, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r4, r5, #0
	str r1, [sp]
	str r5, [sp, #4]
	str r6, [sp, #8]
	add r4, #0xf4
	add r1, r5, #0
	add r2, r5, #0
	add r3, r5, #0
	ldr r4, [r4]
	add r1, #0xb8
	add r2, #0xbc
	add r3, #0xc0
	ldr r1, [r1]
	ldr r2, [r2]
	ldr r3, [r3]
	ldr r4, [r4, #4]
	blx r4
_021EE710:
	add r0, r6, #0
	add r0, #0x22
	ldrb r0, [r0]
	add r6, #0x22
	mov r1, #1
	add r0, r0, #1
	strb r0, [r6]
	add r0, r5, #0
	add r0, #0xb4
	str r1, [r0]
	b _021EE818
_021EE726:
	add r0, r6, #0
	add r0, #0x22
	ldrb r0, [r0]
	sub r0, r0, #1
	add r0, r6, r0
	add r0, #0x20
	ldrb r0, [r0]
	lsl r0, r0, #2
	add r0, r5, r0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #1
	bne _021EE75E
	add r0, r6, #0
	bl MOD05_021EDEAC
	add r1, r6, #0
	add r1, #0x22
	ldrb r1, [r1]
	mov r0, #0
	sub r1, r1, #1
	add r1, r6, r1
	add r1, #0x20
	ldrb r1, [r1]
	lsl r1, r1, #2
	add r1, r5, r1
	add r1, #0x80
	str r0, [r1]
_021EE75E:
	add r0, r6, #0
	add r0, #0x22
	ldrb r0, [r0]
	cmp r0, #2
	bhi _021EE818
	add r0, r6, #0
	add r0, #0x10
	bl MOD05_021EE45C
	cmp r0, #1
	bne _021EE818
	add r0, r6, #0
	add r0, #0x22
	ldrb r0, [r0]
	cmp r0, #2
	blo _021EE784
	mov r0, #1
	str r0, [r6, #0x24]
	b _021EE78C
_021EE784:
	add r0, r5, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
_021EE78C:
	add r0, r6, #0
	add r0, #0x22
	ldrb r0, [r0]
	sub r0, r0, #1
	lsl r0, r0, #2
	ldr r2, [r6, r0]
	ldr r0, _021EE8C8 ; =0x00000864
	ldr r1, [r2, r0]
	cmp r1, #1
	bne _021EE7C4
	sub r0, #0x10
	ldr r0, [r2, r0]
	bl NNS_G3dGetMdlSet
	add r7, r0, #0
	ldrh r0, [r7, #0xe]
	add r0, r7, r0
	ldr r4, [r0, #0xc]
	add r0, r5, #0
	add r0, #0xb8
	ldr r0, [r0]
	bl MOD05_021F4CA8
	cmp r0, #1
	bne _021EE7C4
	add r0, r7, r4
	bl MOD05_021DB5EC
_021EE7C4:
	add r0, r5, #0
	add r0, #0xfc
	ldr r3, [r0]
	cmp r3, #0
	beq _021EE818
	add r0, r6, #0
	add r0, #0x22
	ldrb r0, [r0]
	mov r2, #0x86
	lsl r2, r2, #4
	sub r0, r0, #1
	lsl r0, r0, #2
	ldr r4, [r6, r0]
	ldr r1, [r4, r2]
	cmp r1, #0
	blt _021EE818
	add r0, r5, #0
	add r6, r5, #0
	add r0, #0xc0
	add r6, #0xc4
	ldr r0, [r0]
	ldr r6, [r6]
	mul r6, r0
	cmp r1, r6
	bge _021EE818
	mov r0, #1
	lsl r0, r0, #8
	add r2, #8
	ldr r0, [r5, r0]
	ldr r2, [r4, r2]
	blx r3
	b _021EE818
_021EE804:
	add r6, #0x10
	add r0, r6, #0
	bl MOD05_021EE45C
	cmp r0, #1
	bne _021EE818
	add r0, r5, #0
	mov r1, #0
	add r0, #0xa0
	strb r1, [r0]
_021EE818:
	add r0, r5, #0
	add r0, #0xa0
	ldrb r0, [r0]
	cmp r0, #0
	bne _021EE83A
	add r0, r5, #0
	mov r1, #0
	add r0, #0xa2
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0xa1
	strb r1, [r0]
	mov r0, #2
	add r5, #0xb4
	add sp, #0x14
	str r0, [r5]
	pop {r4, r5, r6, r7, pc}
_021EE83A:
	add r0, r5, #0
	bl MOD05_021EF0F0
	cmp r0, #1
	bne _021EE8C2
	add r0, r5, #0
	add r0, #0xa2
	ldrb r1, [r0]
	mov r0, #0x30
	mov r2, #0
	mul r0, r1
	add r0, r5, r0
	str r2, [r0, #0x2c]
	add r0, r5, #0
	bl MOD05_021EF100
	add r0, r5, #0
	add r0, #0xa0
	ldrb r0, [r0]
	sub r1, r0, #1
	add r0, r5, #0
	add r0, #0xa0
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0xa2
	ldrb r0, [r0]
	add r0, r0, #1
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r5, #0
	add r1, r2, r1
	add r0, #0xa2
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0xa0
	ldrb r0, [r0]
	cmp r0, #0
	beq _021EE890
	mov r1, #0
	b _021EE8A0
_021EE890:
	add r0, r5, #0
	mov r1, #0
	add r0, #0xa2
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0xa1
	strb r1, [r0]
	mov r1, #2
_021EE8A0:
	add r0, r5, #0
	add r0, #0xb4
	str r1, [r0]
	ldr r0, [r5, #0x6c]
	cmp r0, #1
	bne _021EE8C2
	mov r0, #0
	str r0, [r5, #0x6c]
	add r0, r5, #0
	add r0, #0x70
	ldrb r0, [r0]
	add r1, r5, #0
	bl MOD05_021EF118
	add r0, r5, #0
	bl MOD05_021EF094
_021EE8C2:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021EE8C8: .word 0x00000864

	thumb_func_start MOD05_021EE8CC
MOD05_021EE8CC: ; 0x021EE8CC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	ldr r4, [sp, #0x34]
	str r2, [sp, #0x10]
	add r7, r0, #0
	ldr r0, [r4, #0x6c]
	add r5, r3, #0
	str r1, [sp, #0xc]
	ldr r6, [sp, #0x30]
	cmp r0, #1
	bne _021EE8E6
	bl GF_AssertFail
_021EE8E6:
	add r0, r6, #0
	add r1, r4, #0
	add r2, sp, #0x14
	bl MOD05_021EEF9C
	cmp r0, #1
	bne _021EE964
	add r1, sp, #0x14
	ldrb r1, [r1]
	add r0, r4, #0
	bl MOD05_021EDE7C
	add r0, r4, #0
	add r0, #0xa0
	ldrb r0, [r0]
	cmp r0, #2
	blo _021EE948
	mov r0, #1
	str r0, [r4, #0x6c]
	ldr r0, [sp, #0xc]
	str r7, [r4, #0x74]
	str r0, [r4, #0x78]
	add r1, r4, #0
	ldr r0, [sp, #0x10]
	add r1, #0x7c
	strb r0, [r1]
	add r0, r4, #0
	add r0, #0x7d
	strb r5, [r0]
	ldr r0, [sp, #0x10]
	add r2, r4, #0
	add r2, #0x90
	lsl r1, r0, #2
	ldr r0, [r2, r1]
	str r0, [r4, #0x64]
	lsl r0, r5, #2
	ldr r3, [r2, r0]
	str r3, [r4, #0x68]
	add r4, #0x70
	strb r6, [r4]
	ldr r3, [r2, r1]
	mov r1, #0x86
	lsl r1, r1, #4
	str r7, [r3, r1]
	ldr r2, [r2, r0]
	ldr r0, [sp, #0xc]
	add sp, #0x18
	str r0, [r2, r1]
	pop {r3, r4, r5, r6, r7, pc}
_021EE948:
	add r0, r4, #0
	str r5, [sp]
	add r0, #0xa1
	ldrb r0, [r0]
	ldr r2, [sp, #0xc]
	add r1, r7, #0
	str r0, [sp, #4]
	str r6, [sp, #8]
	ldr r3, [sp, #0x10]
	add r0, r4, #0
	bl MOD05_021EE470
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_021EE964:
	add r0, r4, #0
	str r5, [sp]
	add r0, #0xa1
	ldrb r0, [r0]
	ldr r2, [sp, #0xc]
	add r1, r7, #0
	str r0, [sp, #4]
	str r6, [sp, #8]
	ldr r3, [sp, #0x10]
	add r0, r4, #0
	bl MOD05_021EE470
	cmp r0, #1
	beq _021EE984
	bl GF_AssertFail
_021EE984:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021EE988
MOD05_021EE988: ; 0x021EE988
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r4, r6, #0
	lsl r5, r0, #2
	add r4, #0x90
	ldr r1, [r4, r5]
	ldr r0, _021EE9CC ; =0x00000864
	mov r2, #0
	str r2, [r1, r0]
	ldr r1, [r4, r5]
	sub r0, #8
	ldr r0, [r1, r0]
	bl MOD05_021F43CC
	ldr r1, [r4, r5]
	ldr r0, _021EE9D0 ; =0x00000868
	ldr r0, [r1, r0]
	bl MOD05_021E7C1C
	mov r0, #0
	mov r2, #0x86
	ldr r1, [r4, r5]
	mvn r0, r0
	lsl r2, r2, #4
	str r0, [r1, r2]
	ldr r1, [r4, r5]
	sub r2, #0x60
	bl MIi_CpuClearFast
	add r0, r6, r5
	mov r1, #1
	add r0, #0x80
	str r1, [r0]
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021EE9CC: .word 0x00000864
_021EE9D0: .word 0x00000868

	thumb_func_start MOD05_021EE9D4
MOD05_021EE9D4: ; 0x021EE9D4
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, [sp, #0x18]
	add r5, r1, #0
	add r1, r4, #0
	add r6, r0, #0
	add r7, r2, #0
	str r3, [sp]
	bl MOD05_021EE988
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021EE988
	add r4, #0x90
	lsl r1, r6, #2
	lsl r5, r5, #2
	lsl r2, r7, #2
	ldr r0, [r4, r1]
	ldr r3, [r4, r5]
	ldr r6, [r4, r2]
	str r6, [r4, r1]
	ldr r1, [sp]
	lsl r6, r1, #2
	ldr r1, [r4, r6]
	str r1, [r4, r5]
	str r0, [r4, r2]
	str r3, [r4, r6]
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021EEA0C
MOD05_021EEA0C: ; 0x021EEA0C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r1, [sp, #8]
	add r7, r0, #0
	ldr r0, [sp, #8]
	add r6, r2, #0
	cmp r0, #4
	bls _021EEA1E
	b _021EED32
_021EEA1E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EEA2A: ; jump table
	.short _021EED32 - _021EEA2A - 2 ; case 0
	.short _021EEBA4 - _021EEA2A - 2 ; case 1
	.short _021EEC80 - _021EEA2A - 2 ; case 2
	.short _021EEAD2 - _021EEA2A - 2 ; case 3
	.short _021EEA34 - _021EEA2A - 2 ; case 4
_021EEA34:
	mov r0, #2
	mov r1, #3
	mov r2, #0
	mov r3, #1
	str r6, [sp]
	bl MOD05_021EE9D4
	add r0, r6, #0
	add r0, #0xad
	ldrb r0, [r0]
	cmp r0, #2
	bne _021EEA7E
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	mov r0, #1
	sub r5, r7, r2
	str r0, [sp, #0x10]
	mov r0, #0
	sub r4, r5, #1
	str r0, [sp, #0xc]
	cmp r5, #0
	bge _021EEA68
	sub r5, r0, #1
	add r4, r5, #0
	b _021EEAB4
_021EEA68:
	cmp r4, #0
	blt _021EEA78
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021EDE58
	cmp r0, #0
	bne _021EEAB4
_021EEA78:
	mov r4, #0
	mvn r4, r4
	b _021EEAB4
_021EEA7E:
	cmp r0, #3
	bne _021EEAB0
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	mov r0, #0
	sub r5, r7, r2
	str r0, [sp, #0x10]
	mov r0, #1
	add r4, r5, #1
	str r0, [sp, #0xc]
	cmp r5, #0
	bge _021EEA9E
	sub r5, r0, #2
	add r4, r5, #0
	b _021EEAB4
_021EEA9E:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021EDE58
	cmp r0, #0
	bne _021EEAB4
	mov r4, #0
	mvn r4, r4
	b _021EEAB4
_021EEAB0:
	bl GF_AssertFail
_021EEAB4:
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	ldr r0, [sp, #8]
	lsl r2, r2, #0x18
	str r0, [sp]
	lsl r3, r3, #0x18
	add r0, r5, #0
	add r1, r4, #0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	str r6, [sp, #4]
	bl MOD05_021EE8CC
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_021EEAD2:
	mov r0, #1
	mov r1, #3
	mov r2, #0
	mov r3, #2
	str r6, [sp]
	bl MOD05_021EE9D4
	add r0, r6, #0
	add r0, #0xad
	ldrb r0, [r0]
	cmp r0, #1
	bne _021EEB30
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	sub r5, r7, #1
	sub r0, r7, r2
	sub r4, r0, #1
	mov r0, #2
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0xc]
	cmp r5, #0
	blt _021EEB0E
	add r0, r5, #0
	add r1, r7, #0
	bl MOD05_021EDE58
	cmp r0, #0
	bne _021EEB14
_021EEB0E:
	mov r5, #0
	mvn r5, r5
	add r4, r5, #0
_021EEB14:
	cmp r4, #0
	blt _021EEB2A
	add r2, r6, #0
	add r2, #0xc0
	ldr r2, [r2]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021EDE34
	cmp r0, #0
	bne _021EEB86
_021EEB2A:
	mov r4, #0
	mvn r4, r4
	b _021EEB86
_021EEB30:
	cmp r0, #3
	bne _021EEB82
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	sub r5, r7, #1
	add r0, r7, r2
	sub r4, r0, #1
	mov r0, #0
	str r0, [sp, #0x10]
	mov r0, #2
	str r0, [sp, #0xc]
	cmp r5, #0
	blt _021EEB58
	add r0, r5, #0
	add r1, r7, #0
	bl MOD05_021EDE58
	cmp r0, #0
	bne _021EEB5E
_021EEB58:
	mov r5, #0
	mvn r5, r5
	add r4, r5, #0
_021EEB5E:
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	add r0, r6, #0
	add r0, #0xc4
	ldr r0, [r0]
	mul r0, r2
	cmp r0, r4
	ble _021EEB7C
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021EDE34
	cmp r0, #0
	bne _021EEB86
_021EEB7C:
	mov r4, #0
	mvn r4, r4
	b _021EEB86
_021EEB82:
	bl GF_AssertFail
_021EEB86:
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	ldr r0, [sp, #8]
	lsl r2, r2, #0x18
	str r0, [sp]
	lsl r3, r3, #0x18
	add r0, r5, #0
	add r1, r4, #0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	str r6, [sp, #4]
	bl MOD05_021EE8CC
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_021EEBA4:
	mov r0, #0
	mov r1, #2
	mov r2, #1
	mov r3, #3
	str r6, [sp]
	bl MOD05_021EE9D4
	add r0, r6, #0
	add r0, #0xad
	ldrb r0, [r0]
	cmp r0, #0
	bne _021EEC12
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	add r5, r7, #1
	sub r0, r7, r2
	add r4, r0, #1
	mov r0, #3
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0xc]
	add r0, r6, #0
	add r0, #0xc4
	ldr r0, [r0]
	mul r0, r2
	cmp r0, r5
	ble _021EEBE8
	add r0, r5, #0
	add r1, r7, #0
	bl MOD05_021EDE58
	cmp r0, #0
	bne _021EEBEE
_021EEBE8:
	mov r5, #0
	mvn r5, r5
	add r4, r5, #0
_021EEBEE:
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	add r0, r6, #0
	add r0, #0xc4
	ldr r0, [r0]
	mul r0, r2
	cmp r0, r4
	ble _021EEC0C
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021EDE34
	cmp r0, #0
	bne _021EEC62
_021EEC0C:
	mov r4, #0
	mvn r4, r4
	b _021EEC62
_021EEC12:
	cmp r0, #2
	bne _021EEC62
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	add r5, r7, #1
	add r0, r7, r2
	add r4, r0, #1
	mov r0, #1
	str r0, [sp, #0x10]
	mov r0, #3
	str r0, [sp, #0xc]
	add r0, r6, #0
	add r0, #0xc4
	ldr r0, [r0]
	mul r0, r2
	cmp r0, r5
	ble _021EEC42
	add r0, r5, #0
	add r1, r7, #0
	bl MOD05_021EDE58
	cmp r0, #0
	bne _021EEC48
_021EEC42:
	mov r5, #0
	mvn r5, r5
	add r4, r5, #0
_021EEC48:
	cmp r4, #0
	blt _021EEC5E
	add r2, r6, #0
	add r2, #0xc0
	ldr r2, [r2]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021EDE34
	cmp r0, #0
	bne _021EEC62
_021EEC5E:
	mov r4, #0
	mvn r4, r4
_021EEC62:
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	ldr r0, [sp, #8]
	lsl r2, r2, #0x18
	str r0, [sp]
	lsl r3, r3, #0x18
	add r0, r5, #0
	add r1, r4, #0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	str r6, [sp, #4]
	bl MOD05_021EE8CC
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_021EEC80:
	mov r0, #0
	mov r1, #1
	mov r2, #2
	mov r3, #3
	str r6, [sp]
	bl MOD05_021EE9D4
	add r0, r6, #0
	add r0, #0xad
	ldrb r0, [r0]
	cmp r0, #0
	bne _021EECD0
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	mov r0, #3
	str r0, [sp, #0x10]
	mov r0, #2
	str r0, [sp, #0xc]
	add r0, r6, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r5, r7, r2
	mul r0, r2
	sub r4, r5, #1
	cmp r0, r5
	bgt _021EECBE
	ldr r0, [sp, #0xc]
	sub r5, r0, #3
	add r4, r5, #0
	b _021EED14
_021EECBE:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021EDE58
	cmp r0, #0
	bne _021EED14
	mov r4, #0
	mvn r4, r4
	b _021EED14
_021EECD0:
	cmp r0, #1
	bne _021EED10
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	mov r0, #2
	str r0, [sp, #0x10]
	mov r0, #3
	str r0, [sp, #0xc]
	add r0, r6, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r5, r7, r2
	mul r0, r2
	add r4, r5, #1
	cmp r0, r5
	bgt _021EECFA
	ldr r0, [sp, #0xc]
	sub r5, r0, #4
	add r4, r5, #0
	b _021EED14
_021EECFA:
	cmp r0, r4
	ble _021EED0A
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021EDE58
	cmp r0, #0
	bne _021EED14
_021EED0A:
	mov r4, #0
	mvn r4, r4
	b _021EED14
_021EED10:
	bl GF_AssertFail
_021EED14:
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	ldr r0, [sp, #8]
	lsl r2, r2, #0x18
	str r0, [sp]
	lsl r3, r3, #0x18
	add r0, r5, #0
	add r1, r4, #0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	str r6, [sp, #4]
	bl MOD05_021EE8CC
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_021EED32:
	bl GF_AssertFail
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EED3C
MOD05_021EED3C: ; 0x021EED3C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	add r5, r1, #0
	add r4, r5, #0
	lsl r6, r0, #2
	mov r0, #0x86
	add r3, sp, #0x38
	mov r1, #0
	str r1, [r3]
	str r1, [r3, #4]
	str r2, [sp, #4]
	add r2, r5, #0
	add r4, #0x90
	str r1, [r3, #8]
	add r2, #0xbc
	ldr r1, [r4, r6]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r5, #0
	add r1, #0xc0
	ldr r1, [r1]
	ldr r2, [r2]
	bl MOD05_021EF300
	ldr r1, [r4, r6]
	ldr r0, _021EEDD4 ; =0x00000864
	ldr r0, [r1, r0]
	cmp r0, #1
	bne _021EEDA6
	ldr r3, _021EEDD8 ; =UNK05_021F8B14
	add r2, sp, #0x2c
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r3, _021EEDDC ; =UNK05_021F8B20
	str r0, [r2]
	add r2, sp, #8
	mov r7, #4
_021EED88:
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	sub r7, r7, #1
	bne _021EED88
	ldr r0, [r3]
	add r3, sp, #0x2c
	str r0, [r2]
	mov r0, #2
	ldr r1, [r4, r6]
	lsl r0, r0, #0xa
	add r0, r1, r0
	add r1, sp, #0x38
	add r2, sp, #8
	bl FUN_0201B26C
_021EEDA6:
	ldr r4, [r4, r6]
	ldr r0, _021EEDD4 ; =0x00000864
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _021EEDCE
	add r0, r5, #0
	add r0, #0xb8
	ldr r0, [r0]
	bl MOD05_021F4CA8
	add r2, r0, #0
	ldr r0, _021EEDE0 ; =0x00000868
	add r5, #0xb8
	ldr r0, [r4, r0]
	ldr r3, [sp, #4]
	str r0, [sp]
	ldr r1, [r5]
	add r0, sp, #0x38
	bl MOD05_021E7DD8
_021EEDCE:
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	nop
_021EEDD4: .word 0x00000864
_021EEDD8: .word UNK05_021F8B14
_021EEDDC: .word UNK05_021F8B20
_021EEDE0: .word 0x00000868

	thumb_func_start MOD05_021EEDE4
MOD05_021EEDE4: ; 0x021EEDE4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r2, #0
	add r5, r1, #0
	add r6, r0, #0
	add r1, r7, #0
	bl _u32_div_f
	add r4, r1, #0
	add r0, r6, #0
	add r1, r7, #0
	bl _u32_div_f
	lsr r0, r0, #5
	add r1, r0, #0
	lsr r2, r4, #5
	mul r1, r5
	add r0, r2, r1
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021EEE08
MOD05_021EEE08: ; 0x021EEE08
	mul r2, r1
	add r0, r0, r2
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021EEE10
MOD05_021EEE10: ; 0x021EEE10
	push {r3, r4, r5, r6, r7, lr}
	add r7, r2, #0
	add r5, r1, #0
	add r6, r0, #0
	add r1, r7, #0
	bl _u32_div_f
	add r4, r1, #0
	add r0, r6, #0
	add r1, r7, #0
	bl _u32_div_f
	lsr r0, r0, #5
	add r1, r0, #0
	lsr r2, r4, #5
	mul r1, r5
	add r0, r2, r1
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021EEE34
MOD05_021EEE34: ; 0x021EEE34
	push {r3, lr}
	cmp r0, #0
	bne _021EEE3E
	mov r0, #3
	pop {r3, pc}
_021EEE3E:
	cmp r0, #1
	bne _021EEE46
	mov r0, #2
	pop {r3, pc}
_021EEE46:
	cmp r0, #2
	bne _021EEE4E
	mov r0, #1
	pop {r3, pc}
_021EEE4E:
	cmp r0, #3
	bne _021EEE56
	mov r0, #0
	pop {r3, pc}
_021EEE56:
	bl GF_AssertFail
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EEE60
MOD05_021EEE60: ; 0x021EEE60
	push {r3, r4, r5, lr}
	add r5, r2, #0
	add r4, r3, #0
	cmp r0, #4
	bhi _021EEEC0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EEE76: ; jump table
	.short _021EEEC0 - _021EEE76 - 2 ; case 0
	.short _021EEE80 - _021EEE76 - 2 ; case 1
	.short _021EEE96 - _021EEE76 - 2 ; case 2
	.short _021EEEA4 - _021EEE76 - 2 ; case 3
	.short _021EEEB8 - _021EEE76 - 2 ; case 4
_021EEE80:
	add r0, r4, #0
	add r1, r5, #0
	bl _s32_div_f
	add r0, r1, #1
	cmp r0, r5
	blt _021EEE92
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_021EEE92:
	add r0, r4, #1
	pop {r3, r4, r5, pc}
_021EEE96:
	lsl r1, r1, #5
	add r0, r4, r5
	mul r1, r5
	cmp r0, r1
	blt _021EEEC6
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_021EEEA4:
	add r0, r4, #0
	add r1, r5, #0
	bl _s32_div_f
	sub r0, r1, #1
	bpl _021EEEB4
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_021EEEB4:
	sub r0, r4, #1
	pop {r3, r4, r5, pc}
_021EEEB8:
	sub r0, r4, r5
	bpl _021EEEC6
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_021EEEC0:
	bl GF_AssertFail
	mov r0, #0
_021EEEC6:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021EEEC8
MOD05_021EEEC8: ; 0x021EEEC8
	cmp r0, #4
	bhi _021EEF00
	add r2, r0, r0
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021EEED8: ; jump table
	.short _021EEF00 - _021EEED8 - 2 ; case 0
	.short _021EEEFA - _021EEED8 - 2 ; case 1
	.short _021EEEEA - _021EEED8 - 2 ; case 2
	.short _021EEEF2 - _021EEED8 - 2 ; case 3
	.short _021EEEE2 - _021EEED8 - 2 ; case 4
_021EEEE2:
	sub r0, r1, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_021EEEEA:
	add r0, r1, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_021EEEF2:
	sub r0, r1, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_021EEEFA:
	add r0, r1, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
_021EEF00:
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021EEF04
MOD05_021EEF04: ; 0x021EEF04
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	bl MOD05_021EEEC8
	cmp r5, r0
	bge _021EEF36
	sub r0, r0, r5
	cmp r0, #1
	bne _021EEF22
	ldrb r0, [r4]
	sub r0, r0, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	b _021EEF62
_021EEF22:
	cmp r0, #2
	bne _021EEF30
	ldrb r0, [r4]
	sub r0, r0, #2
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	b _021EEF62
_021EEF30:
	bl GF_AssertFail
	b _021EEF62
_021EEF36:
	cmp r5, r0
	ble _021EEF5E
	sub r0, r5, r0
	cmp r0, #1
	bne _021EEF4A
	ldrb r0, [r4]
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	b _021EEF62
_021EEF4A:
	cmp r0, #2
	bne _021EEF58
	ldrb r0, [r4]
	add r0, r0, #2
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	b _021EEF62
_021EEF58:
	bl GF_AssertFail
	b _021EEF62
_021EEF5E:
	bl GF_AssertFail
_021EEF62:
	strb r6, [r4]
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EEF68
MOD05_021EEF68: ; 0x021EEF68
	push {r3, lr}
	cmp r0, #4
	bhi _021EEF94
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EEF7A: ; jump table
	.short _021EEF94 - _021EEF7A - 2 ; case 0
	.short _021EEF8C - _021EEF7A - 2 ; case 1
	.short _021EEF88 - _021EEF7A - 2 ; case 2
	.short _021EEF90 - _021EEF7A - 2 ; case 3
	.short _021EEF84 - _021EEF7A - 2 ; case 4
_021EEF84:
	mov r0, #2
	pop {r3, pc}
_021EEF88:
	mov r0, #4
	pop {r3, pc}
_021EEF8C:
	mov r0, #3
	pop {r3, pc}
_021EEF90:
	mov r0, #1
	pop {r3, pc}
_021EEF94:
	bl GF_AssertFail
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD05_021EEF9C
MOD05_021EEF9C: ; 0x021EEF9C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r5, r1, #0
	add r7, r2, #0
	mov r4, #0
_021EEFA6:
	ldr r0, [r5, #0x2c]
	cmp r0, #1
	bne _021EEFC2
	add r0, r6, #0
	bl MOD05_021EEF68
	add r1, r5, #0
	add r1, #0x30
	ldrb r1, [r1]
	cmp r1, r0
	bne _021EEFC2
	strb r4, [r7]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021EEFC2:
	add r4, r4, #1
	add r5, #0x30
	cmp r4, #2
	blt _021EEFA6
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EEFD0
MOD05_021EEFD0: ; 0x021EEFD0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, #0xa1
	ldrb r1, [r0]
	mov r0, #0x30
	add r4, r5, #0
	mul r0, r1
	add r0, r5, r0
	ldr r0, [r0, #0x2c]
	add r4, #0x64
	cmp r0, #0
	beq _021EEFEC
	bl GF_AssertFail
_021EEFEC:
	add r1, r5, #0
	add r1, #0xa1
	ldrb r2, [r1]
	mov r1, #0x30
	mov r0, #1
	add r3, r2, #0
	mul r3, r1
	add r2, r5, r3
	add r3, r5, #0
	str r0, [r2, #0x2c]
	add r3, #0xa1
	ldrb r3, [r3]
	ldrb r2, [r4, #0xc]
	add r6, r3, #0
	mul r6, r1
	add r3, r5, r6
	add r3, #0x30
	strb r2, [r3]
	add r3, r5, #0
	add r3, #0xa1
	ldrb r3, [r3]
	ldr r2, [r4, #0x10]
	add r6, r3, #0
	mul r6, r1
	add r3, r5, r6
	str r2, [r3, #0x1c]
	add r3, r5, #0
	add r3, #0xa1
	ldrb r3, [r3]
	ldr r2, [r4, #0x14]
	add r6, r3, #0
	mul r6, r1
	add r3, r5, r6
	str r2, [r3, #0x20]
	add r3, r5, #0
	add r3, #0xa1
	ldrb r3, [r3]
	ldrb r2, [r4, #0x18]
	add r6, r3, #0
	mul r6, r1
	add r3, r5, r6
	add r3, #0x24
	strb r2, [r3]
	add r3, r5, #0
	add r3, #0xa1
	ldrb r3, [r3]
	ldrb r2, [r4, #0x19]
	add r6, r3, #0
	mul r6, r1
	add r3, r5, r6
	add r3, #0x25
	strb r2, [r3]
	add r3, r5, #0
	add r3, #0xa1
	ldrb r3, [r3]
	ldr r2, [r4]
	add r6, r3, #0
	mul r6, r1
	add r3, r5, r6
	str r2, [r3, #4]
	add r2, r5, #0
	add r2, #0xa1
	ldrb r2, [r2]
	ldr r4, [r4, #4]
	add r3, r2, #0
	mul r3, r1
	add r2, r5, r3
	add r3, r5, #0
	str r4, [r2, #8]
	add r3, #0xa1
	ldrb r3, [r3]
	mov r2, #0
	add r4, r3, #0
	mul r4, r1
	add r3, r5, r4
	add r3, #0x26
	strb r2, [r3]
	add r3, r5, #0
	add r3, #0xa1
	ldrb r3, [r3]
	mul r1, r3
	add r1, r5, r1
	str r2, [r1, #0x28]
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021EF094
MOD05_021EF094: ; 0x021EF094
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0xa0
	ldrb r0, [r0]
	add r4, r5, #0
	add r4, #0x64
	cmp r0, #2
	blo _021EF0A8
	bl GF_AssertFail
_021EF0A8:
	add r0, r5, #0
	bl MOD05_021EEFD0
	cmp r0, #1
	beq _021EF0B6
	bl GF_AssertFail
_021EF0B6:
	mov r0, #0x86
	ldr r2, [r4, #0x10]
	ldr r1, [r4]
	lsl r0, r0, #4
	str r2, [r1, r0]
	ldr r2, [r4, #0x14]
	ldr r1, [r4, #4]
	str r2, [r1, r0]
	add r0, r5, #0
	add r0, #0xa0
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0xa0
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0xa1
	ldrb r0, [r0]
	add r5, #0xa1
	add r0, r0, #1
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	strb r0, [r5]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EF0F0
MOD05_021EF0F0: ; 0x021EF0F0
	add r1, r0, #0
	add r1, #0xa2
	ldrb r2, [r1]
	mov r1, #0x30
	mul r1, r2
	add r0, r0, r1
	ldr r0, [r0, #0x28]
	bx lr

	thumb_func_start MOD05_021EF100
MOD05_021EF100: ; 0x021EF100
	mov r3, #0
	add r2, r3, #0
_021EF104:
	lsl r1, r3, #2
	add r1, r0, r1
	add r1, #0x80
	str r2, [r1]
	add r1, r3, #1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, #4
	blo _021EF104
	bx lr

	thumb_func_start MOD05_021EF118
MOD05_021EF118: ; 0x021EF118
	cmp r0, #4
	bhi _021EF168
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EF128: ; jump table
	.short _021EF168 - _021EF128 - 2 ; case 0
	.short _021EF140 - _021EF128 - 2 ; case 1
	.short _021EF14E - _021EF128 - 2 ; case 2
	.short _021EF15C - _021EF128 - 2 ; case 3
	.short _021EF132 - _021EF128 - 2 ; case 4
_021EF132:
	add r0, r1, #0
	mov r2, #1
	add r0, #0x88
	str r2, [r0]
	add r1, #0x8c
	str r2, [r1]
	bx lr
_021EF140:
	add r0, r1, #0
	mov r2, #1
	add r0, #0x80
	str r2, [r0]
	add r1, #0x88
	str r2, [r1]
	bx lr
_021EF14E:
	add r0, r1, #0
	mov r2, #1
	add r0, #0x80
	str r2, [r0]
	add r1, #0x84
	str r2, [r1]
	bx lr
_021EF15C:
	add r0, r1, #0
	mov r2, #1
	add r0, #0x84
	str r2, [r0]
	add r1, #0x8c
	str r2, [r1]
_021EF168:
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021EF16C
MOD05_021EF16C: ; 0x021EF16C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	add r4, r3, #0
	add r6, r1, #0
	add r7, r2, #0
	bl MOD05_021EDFBC
	add r2, r5, #0
	add r3, r5, #0
	str r4, [sp]
	add r0, sp, #0x10
	str r0, [sp, #4]
	add r2, #0xc0
	add r3, #0xc4
	ldr r2, [r2]
	ldr r3, [r3]
	add r0, r6, #0
	add r1, r7, #0
	bl MOD05_021EDED0
	mov r6, #0
	add r7, sp, #0x10
_021EF19A:
	lsl r4, r6, #2
	bl MOD05_021F4328
	add r1, r5, r4
	add r1, #0x90
	ldr r2, [r1]
	ldr r1, _021EF1F8 ; =0x0000085C
	str r0, [r2, r1]
	add r0, r5, r4
	add r0, #0x90
	ldr r1, [r0]
	ldr r0, _021EF1F8 ; =0x0000085C
	ldr r0, [r1, r0]
	bl MOD05_021F4454
	add r0, r5, #0
	add r0, #0xb8
	ldr r0, [r0]
	bl MOD05_021F4CA8
	add r1, r5, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r2, r5, #0
	str r1, [sp]
	add r1, r5, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r3, r5, #0
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r5, [sp, #0xc]
	add r2, #0xb8
	add r3, #0xbc
	ldr r0, [r7, r4]
	ldr r2, [r2]
	ldr r3, [r3]
	add r1, r6, #0
	bl MOD05_021EE2A4
	add r0, r6, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #4
	blo _021EF19A
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EF1F8: .word 0x0000085C

	thumb_func_start MOD05_021EF1FC
MOD05_021EF1FC: ; 0x021EF1FC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	add r4, r3, #0
	add r6, r1, #0
	add r7, r2, #0
	bl MOD05_021EE050
	add r2, r5, #0
	add r3, r5, #0
	str r4, [sp]
	add r0, sp, #0x10
	str r0, [sp, #4]
	add r2, #0xc0
	add r3, #0xc4
	ldr r2, [r2]
	ldr r3, [r3]
	add r0, r6, #0
	add r1, r7, #0
	bl MOD05_021EDED0
	mov r4, #0
	add r7, r4, #0
_021EF22A:
	lsl r6, r4, #2
	add r0, r5, r6
	add r0, #0x90
	ldr r1, [r0]
	ldr r0, _021EF278 ; =0x0000085C
	str r7, [r1, r0]
	add r0, r5, #0
	add r0, #0xb8
	ldr r0, [r0]
	bl MOD05_021F4CA8
	add r1, r5, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r2, r5, #0
	str r1, [sp]
	add r1, r5, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r3, r5, #0
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r5, [sp, #0xc]
	add r0, sp, #0x10
	add r2, #0xb8
	add r3, #0xbc
	ldr r0, [r0, r6]
	ldr r2, [r2]
	ldr r3, [r3]
	add r1, r4, #0
	bl MOD05_021EE38C
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021EF22A
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EF278: .word 0x0000085C

	thumb_func_start MOD05_021EF27C
MOD05_021EF27C: ; 0x021EF27C
	push {r4, lr}
	add r1, r0, #0
	mov r3, #0
	add r1, #0xa2
	strb r3, [r1]
	add r1, r0, #0
	add r1, #0xa1
	strb r3, [r1]
	add r1, r0, #0
	add r1, #0xa0
	strb r3, [r1]
	add r4, r0, #0
	add r2, r3, #0
	mov r1, #1
_021EF298:
	str r2, [r4, #0x2c]
	str r1, [r4, #0x28]
	add r3, r3, #1
	add r4, #0x30
	cmp r3, #2
	blt _021EF298
	bl MOD05_021EF100
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EF2AC
MOD05_021EF2AC: ; 0x021EF2AC
	push {r4, lr}
	add r4, r2, #0
	add r2, #0xc8
	ldr r2, [r2]
	bl MOD05_021EEE08
	add r1, r4, #0
	add r1, #0xa8
	str r0, [r1]
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0xc8
	ldr r0, [r0]
	ldr r1, [r1]
	bl MOD05_021EF620
	add r1, r4, #0
	add r1, #0xad
	strb r0, [r1]
	add r0, r4, #0
	add r0, #0xad
	ldrb r0, [r0]
	bl MOD05_021EEE34
	add r1, r4, #0
	add r1, #0xac
	strb r0, [r1]
	add r0, r4, #0
	add r1, r4, #0
	add r2, r4, #0
	add r0, #0xa8
	add r1, #0xc0
	add r2, #0xc8
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, [r2]
	bl MOD05_021EEE10
	add r4, #0xa4
	str r0, [r4]
	pop {r4, pc}

	thumb_func_start MOD05_021EF300
MOD05_021EF300: ; 0x021EF300
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r2, #0
	mov r2, #1
	add r5, r3, #0
	lsl r2, r2, #0x14
	str r2, [r5]
	str r2, [r5, #8]
	mov r2, #0
	add r4, r0, #0
	mvn r2, r2
	str r1, [sp, #4]
	cmp r4, r2
	beq _021EF362
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r6, r0, #0x10
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r7, #0
	bl FUN_020344FC
	str r0, [sp, #8]
	add r0, r7, #0
	bl FUN_02034574
	add r1, r0, #0
	ldr r0, [sp, #8]
	add r2, r6, #0
	str r0, [sp]
	add r0, r7, #0
	add r3, r4, #0
	bl FUN_02034578
	lsl r0, r0, #0xf
	str r0, [r5, #4]
	ldr r1, [r5]
	lsl r0, r6, #0x15
	add r0, r1, r0
	str r0, [r5]
	ldr r1, [r5, #8]
	lsl r0, r4, #0x15
	add r0, r1, r0
	str r0, [r5, #8]
_021EF362:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EF368
MOD05_021EF368: ; 0x021EF368
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r1, [sp]
	mov r1, #0x41
	add r5, r0, #0
	mov r0, #4
	lsl r1, r1, #2
	str r2, [sp, #4]
	add r6, r3, #0
	bl AllocFromHeap
	mov r2, #0x41
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl MI_CpuFill8
	cmp r6, #0
	bne _021EF39A
	add r0, r4, #0
	ldr r1, _021EF42C ; =UNK05_021F8B04
	add r0, #0xf4
	str r1, [r0]
	mov r7, #1
	b _021EF3AE
_021EF39A:
	cmp r6, #1
	bne _021EF3AA
	add r0, r4, #0
	ldr r1, _021EF430 ; =UNK05_021F8B0C
	add r0, #0xf4
	str r1, [r0]
	mov r7, #0
	b _021EF3AE
_021EF3AA:
	bl GF_AssertFail
_021EF3AE:
	add r0, r7, #0
	bl MOD05_021F3BC0
	str r0, [r4]
	add r1, r4, #0
	ldr r0, [sp]
	add r1, #0xb8
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xbc
	str r5, [r0]
	add r0, r5, #0
	bl FUN_020344FC
	add r1, r4, #0
	add r1, #0xc0
	str r0, [r1]
	add r0, r5, #0
	bl FUN_0203450C
	add r1, r4, #0
	add r1, #0xc4
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	lsl r1, r0, #5
	add r0, r4, #0
	add r0, #0xc8
	str r1, [r0]
	add r1, r4, #0
	ldr r0, [sp, #4]
	add r1, #0xf0
	str r0, [r1]
	add r0, r4, #0
	mov r1, #1
	add r0, #0xec
	str r1, [r0]
	add r0, r4, #0
	bl MOD05_021EF27C
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb0
	str r1, [r0]
	add r0, r4, #0
	mov r1, #2
	add r0, #0xb4
	str r1, [r0]
	mov r0, #0x43
	mov r1, #4
	bl NARC_ctor
	add r1, r4, #0
	add r1, #0xf8
	str r0, [r1]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xfc
	str r1, [r0]
	add r0, r4, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EF42C: .word UNK05_021F8B04
_021EF430: .word UNK05_021F8B0C

	thumb_func_start MOD05_021EF434
MOD05_021EF434: ; 0x021EF434
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r5, #0
	add r6, #0xf4
	add r3, r5, #0
	ldr r6, [r6]
	add r3, #0xc8
	ldr r3, [r3]
	ldr r6, [r6]
	add r4, r1, #0
	add r7, r2, #0
	blx r6
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	bl MOD05_021EF2AC
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021EF458
MOD05_021EF458: ; 0x021EF458
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r2, r5, #0
	add r3, r5, #0
	add r1, #0xc4
	add r2, #0xc8
	add r3, #0xa8
	ldr r1, [r1]
	ldr r2, [r2]
	ldr r3, [r3]
	add r6, r0, #0
	bl MOD05_021EEE60
	add r1, r5, #0
	add r2, r5, #0
	add r1, #0xc0
	add r2, #0xc8
	ldr r1, [r1]
	ldr r2, [r2]
	add r7, r0, #0
	bl MOD05_021EEDE4
	add r1, r5, #0
	add r1, #0xc8
	add r4, r0, #0
	ldr r1, [r1]
	add r0, r7, #0
	bl MOD05_021EF620
	add r1, r5, #0
	add r1, #0xa4
	ldr r1, [r1]
	cmp r1, r4
	bne _021EF4C0
	add r1, r5, #0
	add r1, #0xad
	ldrb r1, [r1]
	cmp r1, r0
	beq _021EF4C0
	add r0, r4, #0
	add r1, r6, #0
	add r2, r5, #0
	bl MOD05_021EEA0C
	add r1, r5, #0
	add r1, #0xad
	add r5, #0xac
	ldrb r1, [r1]
	add r0, r6, #0
	add r2, r5, #0
	bl MOD05_021EEF04
_021EF4C0:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EF4C4
MOD05_021EF4C4: ; 0x021EF4C4
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r1, #0
	sub r7, r4, #1
_021EF4CE:
	lsl r0, r4, #2
	add r0, r5, r0
	add r0, #0x90
	ldr r1, [r0]
	mov r0, #0x86
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, r7
	beq _021EF4EA
	add r0, r4, #0
	add r1, r5, #0
	add r2, r6, #0
	bl MOD05_021EED3C
_021EF4EA:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021EF4CE
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EF4F8
MOD05_021EF4F8: ; 0x021EF4F8
	push {r3, r4}
	asr r4, r0, #0xf
	lsr r4, r4, #0x10
	add r4, r0, r4
	asr r0, r4, #0x10
	str r0, [r2]
	asr r0, r1, #0xf
	lsr r0, r0, #0x10
	add r0, r1, r0
	asr r0, r0, #0x10
	str r0, [r3]
	pop {r3, r4}
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021EF514
MOD05_021EF514: ; 0x021EF514
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl FUN_020162FC
	bl NNS_GfdResetLnkTexVramState
	bl NNS_GfdResetLnkPlttVramState
	mov r4, #0
	add r6, r5, #4
	mov r7, #0x30
_021EF52A:
	add r0, r4, #0
	mul r0, r7
	add r0, r6, r0
	bl MOD05_021EDEAC
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #2
	blo _021EF52A
	mov r6, #0
	add r7, r6, #0
_021EF542:
	lsl r4, r6, #2
	add r0, r5, r4
	add r0, #0x90
	ldr r2, [r0]
	ldr r0, _021EF59C ; =0x00000864
	mov r1, #0
	str r1, [r2, r0]
	add r0, r5, r4
	add r0, #0x90
	ldr r1, [r0]
	ldr r0, _021EF5A0 ; =0x0000085C
	ldr r0, [r1, r0]
	bl MOD05_021F43C0
	add r0, r5, r4
	add r0, #0x90
	ldr r1, [r0]
	ldr r0, _021EF5A4 ; =0x00000868
	ldr r0, [r1, r0]
	bl MOD05_021E7C14
	add r0, r5, r4
	add r0, #0x90
	ldr r0, [r0]
	bl FreeToHeap
	add r0, r5, r4
	add r0, #0x90
	str r7, [r0]
	add r0, r6, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #4
	blo _021EF542
	add r0, r5, #0
	mov r1, #3
	add r0, #0xb4
	str r1, [r0]
	add r0, r5, #0
	mov r1, #1
	add r0, #0xb0
	str r1, [r0]
	add r5, #0xec
	str r7, [r5]
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EF59C: .word 0x00000864
_021EF5A0: .word 0x0000085C
_021EF5A4: .word 0x00000868

	thumb_func_start MOD05_021EF5A8
MOD05_021EF5A8: ; 0x021EF5A8
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xf8
	ldr r0, [r0]
	bl NARC_dtor
	ldr r0, [r4]
	bl MOD05_021F3C30
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EF5C4
MOD05_021EF5C4: ; 0x021EF5C4
	add r1, r0, #0
	add r1, #0xb0
	ldr r1, [r1]
	cmp r1, #1
	bne _021EF5DA
	add r0, #0xa0
	ldrb r0, [r0]
	cmp r0, #0
	bne _021EF5DA
	mov r0, #1
	bx lr
_021EF5DA:
	mov r0, #0
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021EF5E0
MOD05_021EF5E0: ; 0x021EF5E0
	push {r4, r5}
	add r5, r0, #0
	add r4, r1, #0
	add r2, r4, #0
	add r3, r5, #0
	ldmia r3!, {r0, r1}
	add r2, #0xcc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r4, #0xd8
	str r0, [r2]
	str r5, [r4]
	pop {r4, r5}
	bx lr

	thumb_func_start MOD05_021EF5FC
MOD05_021EF5FC: ; 0x021EF5FC
	mov r1, #0
	add r0, #0xd8
	str r1, [r0]
	bx lr

	thumb_func_start MOD05_021EF604
MOD05_021EF604: ; 0x021EF604
	lsl r0, r0, #2
	add r0, r1, r0
	add r0, #0x90
	ldr r1, [r0]
	ldr r0, _021EF614 ; =0x00000868
	ldr r0, [r1, r0]
	str r0, [r2]
	bx lr
	.balign 4, 0
_021EF614: .word 0x00000868

	thumb_func_start MOD05_021EF618
MOD05_021EF618: ; 0x021EF618
	add r0, #0xac
	ldrb r0, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021EF620
MOD05_021EF620: ; 0x021EF620
	push {r4, lr}
	add r4, r0, #0
	bl _u32_div_f
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1b
	sub r1, r1, r2
	mov r0, #0x1b
	ror r1, r0
	mov r0, #0x1f
	and r0, r4
	add r1, r2, r1
	cmp r0, #0x10
	bge _021EF648
	cmp r1, #0x10
	bge _021EF644
	mov r0, #0
	pop {r4, pc}
_021EF644:
	mov r0, #2
	pop {r4, pc}
_021EF648:
	cmp r1, #0x10
	bge _021EF650
	mov r0, #1
	pop {r4, pc}
_021EF650:
	mov r0, #3
	pop {r4, pc}

	thumb_func_start MOD05_021EF654
MOD05_021EF654: ; 0x021EF654
	push {r3, r4, r5, lr}
	add r4, r2, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	cmp r0, r5
	bne _021EF66A
	add r4, #0xac
	ldrb r0, [r4]
	pop {r3, r4, r5, pc}
_021EF66A:
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	bne _021EF676
	bl GF_AssertFail
_021EF676:
	add r0, r4, #0
	add r0, #0xac
	ldrb r1, [r0]
	cmp r1, #3
	bls _021EF682
	b _021EF820
_021EF682:
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EF68E: ; jump table
	.short _021EF696 - _021EF68E - 2 ; case 0
	.short _021EF6F8 - _021EF68E - 2 ; case 1
	.short _021EF75C - _021EF68E - 2 ; case 2
	.short _021EF7BE - _021EF68E - 2 ; case 3
_021EF696:
	add r0, r4, #0
	add r0, #0xa4
	add r2, r4, #0
	ldr r0, [r0]
	add r2, #0xc0
	ldr r2, [r2]
	sub r3, r5, r0
	cmp r2, r3
	bne _021EF6B0
	add r0, r1, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF6B0:
	cmp r3, #1
	bne _021EF6CA
	add r1, r5, #0
	bl MOD05_021EDE58
	cmp r0, #0
	beq _021EF6CA
	add r4, #0xac
	ldrb r0, [r4]
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF6CA:
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa4
	add r1, #0xc0
	ldr r2, [r1]
	ldr r0, [r0]
	add r3, r2, #1
	sub r1, r5, r0
	cmp r3, r1
	bne _021EF6F4
	add r1, r5, #0
	bl MOD05_021EDE58
	cmp r0, #0
	bne _021EF6F4
	add r4, #0xac
	ldrb r0, [r4]
	add r0, r0, #3
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF6F4:
	mov r0, #4
	pop {r3, r4, r5, pc}
_021EF6F8:
	add r0, r4, #0
	add r0, #0xa4
	add r2, r4, #0
	ldr r0, [r0]
	add r2, #0xc0
	ldr r2, [r2]
	sub r3, r5, r0
	cmp r2, r3
	bne _021EF712
	add r0, r1, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF712:
	sub r1, r0, r5
	cmp r1, #1
	bne _021EF72E
	add r1, r5, #0
	bl MOD05_021EDE58
	cmp r0, #0
	beq _021EF72E
	add r4, #0xac
	ldrb r0, [r4]
	sub r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF72E:
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa4
	add r1, #0xc0
	ldr r2, [r1]
	ldr r0, [r0]
	sub r3, r2, #1
	sub r1, r5, r0
	cmp r3, r1
	bne _021EF758
	add r1, r5, #0
	bl MOD05_021EDE58
	cmp r0, #0
	bne _021EF758
	add r4, #0xac
	ldrb r0, [r4]
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF758:
	mov r0, #4
	pop {r3, r4, r5, pc}
_021EF75C:
	add r0, r4, #0
	add r0, #0xa4
	add r2, r4, #0
	ldr r0, [r0]
	add r2, #0xc0
	ldr r2, [r2]
	sub r3, r0, r5
	cmp r2, r3
	bne _021EF776
	sub r0, r1, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF776:
	sub r1, r2, #1
	cmp r1, r3
	bne _021EF792
	add r1, r5, #0
	bl MOD05_021EDE58
	cmp r0, #0
	bne _021EF792
	add r4, #0xac
	ldrb r0, [r4]
	sub r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF792:
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	sub r1, r5, r0
	cmp r1, #1
	bne _021EF7BA
	add r2, r4, #0
	add r2, #0xc0
	ldr r2, [r2]
	add r1, r5, #0
	bl MOD05_021EDE58
	cmp r0, #0
	beq _021EF7BA
	add r4, #0xac
	ldrb r0, [r4]
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF7BA:
	mov r0, #4
	pop {r3, r4, r5, pc}
_021EF7BE:
	add r0, r4, #0
	add r0, #0xa4
	add r2, r4, #0
	ldr r0, [r0]
	add r2, #0xc0
	ldr r2, [r2]
	sub r3, r0, r5
	cmp r2, r3
	bne _021EF7D8
	sub r0, r1, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF7D8:
	add r1, r2, #1
	cmp r1, r3
	bne _021EF7F4
	add r1, r5, #0
	bl MOD05_021EDE58
	cmp r0, #0
	bne _021EF7F4
	add r4, #0xac
	ldrb r0, [r4]
	sub r0, r0, #3
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF7F4:
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	sub r1, r0, r5
	cmp r1, #1
	bne _021EF81C
	add r2, r4, #0
	add r2, #0xc0
	ldr r2, [r2]
	add r1, r5, #0
	bl MOD05_021EDE58
	cmp r0, #0
	beq _021EF81C
	add r4, #0xac
	ldrb r0, [r4]
	sub r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF81C:
	mov r0, #4
	pop {r3, r4, r5, pc}
_021EF820:
	mov r0, #4
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021EF824
MOD05_021EF824: ; 0x021EF824
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #4
	blo _021EF832
	bl GF_AssertFail
_021EF832:
	lsl r0, r5, #2
	add r0, r4, r0
	add r0, #0x90
	ldr r1, [r0]
	mov r0, #0x86
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EF844
MOD05_021EF844: ; 0x021EF844
	push {r3, r4, r5, r6, r7, lr}
	add r6, r2, #0
	asr r2, r6, #4
	add r5, r0, #0
	lsr r2, r2, #0x1b
	add r2, r6, r2
	add r4, r1, #0
	add r0, #0xc0
	ldr r1, [r0]
	asr r0, r4, #4
	lsr r0, r0, #0x1b
	add r0, r4, r0
	asr r2, r2, #5
	str r3, [sp]
	add r3, r2, #0
	asr r0, r0, #5
	mul r3, r1
	add r7, r0, r3
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	mul r0, r1
	cmp r7, r0
	blo _021EF882
	mov r0, #1
	bl FUN_020336A0
	cmp r0, #0
	beq _021EF882
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021EF882:
	add r0, r5, #0
	add r0, #0xc0
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	mul r0, r1
	cmp r7, r0
	blo _021EF898
	bl GF_AssertFail
_021EF898:
	add r0, r5, #0
	add r0, #0xc8
	ldr r1, [r0]
	add r0, r6, #0
	mul r0, r1
	add r0, r4, r0
	bl MOD05_021EF620
	add r1, r0, #0
	add r0, r7, #0
	add r2, r5, #0
	bl MOD05_021EF654
	ldr r1, [sp]
	cmp r1, #0
	beq _021EF8BA
	strb r0, [r1]
_021EF8BA:
	cmp r0, #3
	bls _021EF8C2
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021EF8C2:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EF8C8
MOD05_021EF8C8: ; 0x021EF8C8
	lsl r1, r1, #2
	add r0, r0, r1
	add r0, #0x90
	ldr r1, [r0]
	ldr r0, _021EF8D8 ; =0x0000085C
	ldr r0, [r1, r0]
	bx lr
	nop
_021EF8D8: .word 0x0000085C

	thumb_func_start MOD05_021EF8DC
MOD05_021EF8DC: ; 0x021EF8DC
	lsl r1, r1, #2
	add r0, r0, r1
	add r0, #0x90
	ldr r0, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021EF8E8
MOD05_021EF8E8: ; 0x021EF8E8
	add r3, r0, #0
	add r3, #0xfc
	str r1, [r3]
	mov r1, #1
	lsl r1, r1, #8
	str r2, [r0, r1]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021EF8F8
MOD05_021EF8F8: ; 0x021EF8F8
	push {r3, lr}
	bl FUN_0201B6C8
	mov r1, #1
	str r1, [r0, #0x1c]
	pop {r3, pc}

	thumb_func_start MOD05_021EF904
MOD05_021EF904: ; 0x021EF904
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x1c]
	cmp r0, #1
	bne _021EF914
	mov r0, #5
	strb r0, [r4, #0x14]
_021EF914:
	ldrb r0, [r4, #0x14]
	cmp r0, #5
	bhi _021EF9FE
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EF926: ; jump table
	.short _021EF932 - _021EF926 - 2 ; case 0
	.short _021EF962 - _021EF926 - 2 ; case 1
	.short _021EF998 - _021EF926 - 2 ; case 2
	.short _021EF9B6 - _021EF926 - 2 ; case 3
	.short _021EF9FE - _021EF926 - 2 ; case 4
	.short _021EF9EC - _021EF926 - 2 ; case 5
_021EF932:
	mov r0, #0
	str r0, [r4, #0x24]
	mov r0, #0xe
	ldr r5, [r4, #4]
	lsl r0, r0, #0xc
	cmp r5, r0
	bgt _021EF944
	mov r0, #2
	b _021EF948
_021EF944:
	add r5, r0, #0
	mov r0, #1
_021EF948:
	strb r0, [r4, #0x14]
	ldr r2, [r4, #0xc]
	ldr r0, [r4]
	ldr r3, [r2]
	ldr r2, [r4, #0x24]
	add r1, r5, #0
	add r2, r3, r2
	bl NARC_ReadFile
	ldr r0, [r4, #0x24]
	add r0, r0, r5
	str r0, [r4, #0x24]
	pop {r4, r5, r6, pc}
_021EF962:
	ldr r2, [r4, #0x24]
	ldr r0, [r4, #4]
	sub r5, r0, r2
	mov r0, #0xe
	lsl r0, r0, #0xc
	cmp r5, r0
	ble _021EF976
	add r5, r0, #0
	mov r6, #0
	b _021EF978
_021EF976:
	mov r6, #1
_021EF978:
	ldr r3, [r4, #0xc]
	ldr r0, [r4]
	ldr r3, [r3]
	add r1, r5, #0
	add r2, r3, r2
	bl NARC_ReadFile
	cmp r6, #0
	beq _021EF990
	mov r0, #2
	strb r0, [r4, #0x14]
	pop {r4, r5, r6, pc}
_021EF990:
	ldr r0, [r4, #0x24]
	add r0, r0, r5
	str r0, [r4, #0x24]
	pop {r4, r5, r6, pc}
_021EF998:
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _021EF9B0
	bl FUN_0201B254
	cmp r0, #1
	bne _021EF9B0
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	ldr r0, [r0]
	bl FUN_0201B3A8
_021EF9B0:
	mov r0, #3
	strb r0, [r4, #0x14]
	pop {r4, r5, r6, pc}
_021EF9B6:
	ldr r0, [r4, #0xc]
	ldr r0, [r0]
	bl NNS_G3dGetMdlSet
	add r5, r0, #0
	ldrb r0, [r5, #9]
	cmp r0, #1
	beq _021EF9CA
	bl GF_AssertFail
_021EF9CA:
	ldrh r0, [r5, #0xe]
	add r0, r5, r0
	ldr r0, [r0, #0xc]
	add r5, r5, r0
	bne _021EF9D8
	bl GF_AssertFail
_021EF9D8:
	ldr r0, [r4, #8]
	add r1, r5, #0
	bl NNS_G3dRenderObjInit
	ldr r0, [r4, #0x18]
	mov r1, #1
	str r1, [r0]
	mov r0, #5
	strb r0, [r4, #0x14]
	pop {r4, r5, r6, pc}
_021EF9EC:
	ldr r0, [r4, #0x20]
	mov r1, #0
	str r1, [r0]
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_021EF9FE:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021EFA00
MOD05_021EFA00: ; 0x021EFA00
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #4

	thumb_func_start MOD05_021EFA08
MOD05_021EFA08: ; 0x021EFA08
	mov r1, #0x28
	add r6, r2, #0
	add r7, r3, #0
	bl AllocFromHeapAtEnd
	add r1, r0, #0
	str r5, [r1]
	str r4, [r1, #4]
	str r6, [r1, #8]
	ldr r0, [sp, #0x18]
	str r7, [r1, #0xc]
	str r0, [r1, #0x10]
	mov r2, #0
	ldr r0, [sp, #0x1c]
	strb r2, [r1, #0x14]
	str r0, [r1, #0x18]
	str r2, [r0]
	ldr r0, [sp, #0x20]
	str r0, [r1, #0x20]
	str r2, [r1, #0x1c]
	ldr r0, _021EFA3C ; =MOD05_021EF904
	mov r2, #1
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021EFA3C: .word MOD05_021EF904

	thumb_func_start MOD05_021EFA40
MOD05_021EFA40: ; 0x021EFA40
	push {r3, r4, r5, lr}
	add r4, r3, #0
	add r5, r2, #0
	ldr r2, [r4]
	bl NARC_ReadFile
	ldr r0, [sp, #0x10]
	cmp r0, #0
	beq _021EFA6A
	bl FUN_0201B254
	cmp r0, #1
	bne _021EFA6A
	ldr r0, [r4]
	ldr r1, [sp, #0x10]
	bl FUN_0201B3A8
	cmp r0, #0
	bne _021EFA6A
	bl GF_AssertFail
_021EFA6A:
	ldr r0, [r4]
	bl NNS_G3dGetMdlSet
	ldrb r0, [r0, #9]
	cmp r0, #1
	beq _021EFA7A
	bl GF_AssertFail
_021EFA7A:
	ldr r0, [r4]
	bl NNS_G3dGetMdlSet
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r4, r0, r1
	bne _021EFA8E
	bl GF_AssertFail
_021EFA8E:
	add r0, r5, #0
	add r1, r4, #0
	bl NNS_G3dRenderObjInit
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EFA9C
MOD05_021EFA9C: ; 0x021EFA9C
	push {r3, lr}
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x14]
	cmp r0, #0
	beq _021EFAAA
	bl MOD20_022524DC
_021EFAAA:
	pop {r3, pc}

	thumb_func_start MOD05_021EFAAC
MOD05_021EFAAC: ; 0x021EFAAC
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	bl Sav2_Poketch_get
	add r4, r0, #0
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	add r6, r0, #0
	add r0, r4, #0
	bl Sav2_Poketch_IsGiven
	cmp r0, #0
	beq _021EFAF8
	add r0, r6, #0
	bl FUN_0205F1E4
	cmp r0, #0
	bne _021EFAF8
	ldr r0, _021EFB0C ; =SDK_OVERLAY_MODULE_20_ID
	mov r1, #2
	bl HandleLoadOverlay
	mov r0, #1
	bl FUN_0200A03C
	str r0, [sp]
	ldr r1, [r5, #4]
	ldr r2, [r5, #0xc]
	ldr r3, [r5, #8]
	add r0, r5, #0
	add r1, #0x14
	bl MOD20_02252448
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_021EFAF8:
	ldr r0, _021EFB10 ; =SDK_OVERLAY_MODULE_19_ID
	mov r1, #2
	bl HandleLoadOverlay
	ldr r0, [r5, #8]
	bl MOD19_02252440
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_021EFB0C: .word SDK_OVERLAY_MODULE_20_ID
_021EFB10: .word SDK_OVERLAY_MODULE_19_ID

	thumb_func_start MOD05_021EFB14
MOD05_021EFB14: ; 0x021EFB14
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	bl Sav2_Poketch_get
	add r4, r0, #0
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	add r6, r0, #0
	add r0, r4, #0
	bl Sav2_Poketch_IsGiven
	cmp r0, #0
	beq _021EFB46
	add r0, r6, #0
	bl FUN_0205F1E4
	cmp r0, #0
	bne _021EFB46
	ldr r0, [r5, #4]
	ldr r0, [r0, #0x14]
	bl MOD20_022524BC
	pop {r4, r5, r6, pc}
_021EFB46:
	ldr r0, [r5, #8]
	bl MOD19_022524F4
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EFB50
MOD05_021EFB50: ; 0x021EFB50
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	bl Sav2_Poketch_get
	add r4, r0, #0
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	add r6, r0, #0
	add r0, r4, #0
	bl Sav2_Poketch_IsGiven
	cmp r0, #0
	beq _021EFB94
	add r0, r6, #0
	bl FUN_0205F1E4
	cmp r0, #0
	bne _021EFB94
	ldr r0, [r5, #4]
	ldr r0, [r0, #0x14]
	bl MOD20_022524D0
	cmp r0, #0
	beq _021EFBA8
	ldr r0, [r5, #4]
	mov r1, #0
	str r1, [r0, #0x14]
	ldr r0, _021EFBAC ; =SDK_OVERLAY_MODULE_20_ID
	bl UnloadOverlayByID
	mov r0, #1
	pop {r4, r5, r6, pc}
_021EFB94:
	ldr r0, [r5, #8]
	bl MOD19_02252504
	cmp r0, #0
	beq _021EFBA8
	ldr r0, _021EFBB0 ; =SDK_OVERLAY_MODULE_19_ID
	bl UnloadOverlayByID
	mov r0, #1
	pop {r4, r5, r6, pc}
_021EFBA8:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021EFBAC: .word SDK_OVERLAY_MODULE_20_ID
_021EFBB0: .word SDK_OVERLAY_MODULE_19_ID

	thumb_func_start MOD05_021EFBB4
MOD05_021EFBB4: ; 0x021EFBB4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021EFBC8 ; =SDK_OVERLAY_MODULE_19_ID
	mov r1, #2
	bl HandleLoadOverlay
	ldr r0, [r4, #8]
	bl MOD19_02252440
	pop {r4, pc}
	.balign 4, 0
_021EFBC8: .word SDK_OVERLAY_MODULE_19_ID

	thumb_func_start MOD05_021EFBCC
MOD05_021EFBCC: ; 0x021EFBCC
	ldr r3, _021EFBD4 ; =MOD19_022524F4
	ldr r0, [r0, #8]
	bx r3
	nop
_021EFBD4: .word MOD19_022524F4

	thumb_func_start MOD05_021EFBD8
MOD05_021EFBD8: ; 0x021EFBD8
	push {r3, lr}
	ldr r0, [r0, #8]
	bl MOD19_02252504
	cmp r0, #0
	beq _021EFBEE
	ldr r0, _021EFBF4 ; =SDK_OVERLAY_MODULE_19_ID
	bl UnloadOverlayByID
	mov r0, #1
	pop {r3, pc}
_021EFBEE:
	mov r0, #0
	pop {r3, pc}
	nop
_021EFBF4: .word SDK_OVERLAY_MODULE_19_ID

	thumb_func_start MOD05_021EFBF8
MOD05_021EFBF8: ; 0x021EFBF8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0x34]
	bl FUN_020286EC
	mov r1, #0
	bl FUN_0202838C
	add r1, r4, #0
	ldr r0, [r4, #0x34]
	add r1, #0x4c
	mov r2, #4
	bl FUN_020339B4
	cmp r0, #0
	bne _021EFC20
	add sp, #8
	mov r0, #1
	pop {r4, pc}
_021EFC20:
	add r0, r4, #0
	mov r1, #0
	add r0, #0x8c
	str r1, [r0]
	ldr r0, [r4, #0x34]
	bl Sav2_PlayerData_GetOptionsAddr
	bl Options_GetFrame
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r4, #0x30]
	ldr r2, _021EFC6C ; =0x000001E2
	ldr r0, [r0, #8]
	mov r1, #3
	mov r3, #0xa
	bl FUN_0200CD68
	mov r0, #0
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r4, #0x30]
	ldr r2, _021EFC70 ; =0x000003D9
	ldr r0, [r0, #8]
	mov r1, #3
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #1
	str r0, [r4, #0x48]
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	nop
_021EFC6C: .word 0x000001E2
_021EFC70: .word 0x000003D9

	thumb_func_start MOD05_021EFC74
MOD05_021EFC74: ; 0x021EFC74
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	mov r1, #0
	add r6, r0, #0
	mvn r1, r1
	add r0, #0x8c
	str r1, [r0]
	mov r4, #0
	bl FUN_02030F20
	cmp r0, #0
	ble _021EFCB0
	add r5, r6, #0
_021EFC8E:
	ldr r0, [r5, #0x4c]
	cmp r0, #2
	bne _021EFCA4
	add r0, r6, #0
	add r0, #0x8c
	str r4, [r0]
	lsl r0, r4, #2
	mov r1, #0
	add r0, r6, r0
	str r1, [r0, #0x4c]
	b _021EFCB0
_021EFCA4:
	add r5, r5, #4
	add r4, r4, #1
	bl FUN_02030F20
	cmp r4, r0
	blt _021EFC8E
_021EFCB0:
	add r0, r6, #0
	add r0, #0x8c
	ldr r1, [r0]
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	bne _021EFCC4
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021EFCC4:
	ldr r0, [r6, #0x34]
	bl Sav2_Bag_get
	ldr r1, _021EFD3C ; =0x000001B5
	mov r2, #1
	mov r3, #4
	bl Bag_HasItem
	cmp r0, #1
	bne _021EFCFE
	add r0, r6, #0
	add r0, #0x8c
	ldr r0, [r0]
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r6, #0x38]
	mov r1, #0
	bl BufferPlayersName
	add r0, r6, #0
	mov r1, #0x21
	bl MOD05_021F01EC
	mov r0, #2
	str r0, [r6, #0x48]
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_021EFCFE:
	ldr r0, [r6, #0x34]
	bl FUN_020286EC
	add r4, r0, #0
	mov r5, #0
_021EFD08:
	add r0, r4, #0
	add r1, r5, #0
	bl FUN_0202842C
	cmp r0, #0
	bne _021EFD2A
	mov r0, #0
	add r1, r6, #0
	str r0, [sp]
	add r1, #0x8c
	ldr r0, [r6, #0x34]
	ldr r1, [r1]
	add r2, r5, #0
	mov r3, #4
	bl FUN_02033A70
	b _021EFD30
_021EFD2A:
	add r5, r5, #1
	cmp r5, #0x20
	blt _021EFD08
_021EFD30:
	mov r0, #1
	str r0, [r6, #0x48]
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_021EFD3C: .word 0x000001B5

	thumb_func_start MOD05_021EFD40
MOD05_021EFD40: ; 0x021EFD40
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021EFD6C
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4, #0x30]
	ldr r1, _021EFD74 ; =UNK05_021F8B44
	ldr r0, [r0, #8]
	ldr r2, _021EFD78 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x44]
	mov r0, #3
	str r0, [r4, #0x48]
_021EFD6C:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	nop
_021EFD74: .word UNK05_021F8B44
_021EFD78: .word 0x000003D9

	thumb_func_start MOD05_021EFD7C
MOD05_021EFD7C: ; 0x021EFD7C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r6, r0, #0
	ldr r0, [r6, #0x44]
	mov r1, #4
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _021EFD98
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_021EFD98:
	cmp r0, #0
	bne _021EFDE4
	ldr r0, [r6, #0x34]
	bl FUN_020286EC
	add r5, r0, #0
	mov r4, #0
_021EFDA6:
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0202842C
	cmp r0, #0
	bne _021EFDC8
	mov r0, #0
	add r1, r6, #0
	str r0, [sp]
	add r1, #0x8c
	ldr r0, [r6, #0x34]
	ldr r1, [r1]
	add r2, r4, #0
	mov r3, #4
	bl FUN_02033A70
	b _021EFDCE
_021EFDC8:
	add r4, r4, #1
	cmp r4, #0x20
	blt _021EFDA6
_021EFDCE:
	cmp r4, #0x20
	bne _021EFDE4
	add r0, r6, #0
	mov r1, #0x22
	bl MOD05_021F01EC
	mov r0, #4
	str r0, [r6, #0x48]
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_021EFDE4:
	mov r0, #1
	str r0, [r6, #0x48]
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EFDF0
MOD05_021EFDF0: ; 0x021EFDF0
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021EFE1C
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4, #0x30]
	ldr r1, _021EFE24 ; =UNK05_021F8B44
	ldr r0, [r0, #8]
	ldr r2, _021EFE28 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x44]
	mov r0, #5
	str r0, [r4, #0x48]
_021EFE1C:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	nop
_021EFE24: .word UNK05_021F8B44
_021EFE28: .word 0x000003D9

	thumb_func_start MOD05_021EFE2C
MOD05_021EFE2C: ; 0x021EFE2C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x44]
	mov r1, #4
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _021EFE44
	mov r0, #0
	pop {r4, pc}
_021EFE44:
	cmp r0, #0
	bne _021EFE4C
	mov r0, #8
	b _021EFE6A
_021EFE4C:
	add r0, r4, #0
	add r0, #0x8c
	ldr r0, [r0]
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r4, #0x38]
	mov r1, #0
	bl BufferPlayersName
	add r0, r4, #0
	mov r1, #0x23
	bl MOD05_021F01EC
	mov r0, #6
_021EFE6A:
	str r0, [r4, #0x48]
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD05_021EFE70
MOD05_021EFE70: ; 0x021EFE70
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021EFE9C
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4, #0x30]
	ldr r1, _021EFEA4 ; =UNK05_021F8B44
	ldr r0, [r0, #8]
	ldr r2, _021EFEA8 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x44]
	mov r0, #7
	str r0, [r4, #0x48]
_021EFE9C:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	nop
_021EFEA4: .word UNK05_021F8B44
_021EFEA8: .word 0x000003D9

	thumb_func_start MOD05_021EFEAC
MOD05_021EFEAC: ; 0x021EFEAC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x44]
	mov r1, #4
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _021EFEC4
	mov r0, #0
	pop {r4, pc}
_021EFEC4:
	cmp r0, #0
	bne _021EFECC
	mov r0, #0xc
	b _021EFED6
_021EFECC:
	add r0, r4, #0
	mov r1, #0x22
	bl MOD05_021F01EC
	mov r0, #4
_021EFED6:
	str r0, [r4, #0x48]
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD05_021EFEDC
MOD05_021EFEDC: ; 0x021EFEDC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r0, #0
	ldr r0, [r5, #0x34]
	bl FUN_020286EC
	add r6, r0, #0
	bl FUN_02028448
	add r7, r0, #0
	add r0, r7, #1
	mov r1, #4
	bl ListMenuItems_ctor
	str r0, [r5]
	mov r0, #1
	str r0, [sp]
	mov r0, #0xc
	str r0, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _021EFFB8 ; =0x000002A1
	add r1, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x30]
	add r1, #0x20
	ldr r0, [r0, #8]
	mov r2, #3
	mov r3, #0x13
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _021EFFBC ; =0x000003D9
	add r0, #0x20
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	mov r4, #0
_021EFF2E:
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_0202842C
	cmp r0, #0
	beq _021EFF54
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_020283A4
	add r1, r0, #0
	ldr r0, [r5, #8]
	bl CopyU16ArrayToString
	ldr r0, [r5]
	ldr r1, [r5, #8]
	add r2, r4, #0
	bl ListMenuItems_AddItem
_021EFF54:
	add r4, r4, #1
	cmp r4, #0x20
	blt _021EFF2E
	mov r2, #0xb
	add r3, r2, #0
	ldr r0, [r5]
	ldr r1, [r5, #0x3c]
	sub r3, #0xd
	bl ListMenuItems_AppendFromMsgData
	ldr r4, _021EFFC0 ; =UNK05_021F8B4C
	add r3, sp, #0x14
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r1, r7, #1
	add r0, sp, #0x14
	strh r1, [r0, #0x10]
	mov r1, #5
	strh r1, [r0, #0x12]
	ldr r0, [r5]
	mov r1, #0
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r0, #0x20
	str r0, [sp, #0x20]
	ldr r0, _021EFFC4 ; =MOD05_021F0304
	str r5, [sp, #0x30]
	str r0, [sp, #0x18]
	add r0, r2, #0
	add r2, r1, #0
	mov r3, #4
	bl ListMenuInit
	str r0, [r5, #4]
	add r0, r5, #0
	add r0, #0x20
	bl CopyWindowToVram
	mov r0, #9
	str r0, [r5, #0x48]
	mov r0, #0
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021EFFB8: .word 0x000002A1
_021EFFBC: .word 0x000003D9
_021EFFC0: .word UNK05_021F8B4C
_021EFFC4: .word MOD05_021F0304

	thumb_func_start MOD05_021EFFC8
MOD05_021EFFC8: ; 0x021EFFC8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #4]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _021EFFE6
	add r0, r0, #1
	cmp r4, r0
	bne _021F000E
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021EFFE6:
	ldr r0, _021F007C ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r5, #0x38]
	mov r1, #0
	bl BufferPlayersName
	add r0, r5, #0
	mov r1, #0x23
	bl MOD05_021F01EC
	mov r0, #6
	str r0, [r5, #0x48]
	b _021F0056
_021F000E:
	ldr r0, _021F007C ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	add r0, #0x90
	str r4, [r0]
	ldr r0, [r5, #0x34]
	bl FUN_020286EC
	add r7, r0, #0
	mov r0, #4
	bl PlayerProfile_new
	add r6, r0, #0
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_020283A4
	add r1, r0, #0
	add r0, r6, #0
	bl CopyPlayerName
	ldr r0, [r5, #0x38]
	mov r1, #0
	add r2, r6, #0
	bl BufferPlayersName
	add r0, r6, #0
	bl FreeToHeap
	add r0, r5, #0
	mov r1, #0x24
	bl MOD05_021F01EC
	mov r0, #0xa
	str r0, [r5, #0x48]
_021F0056:
	add r0, r5, #0
	add r0, #0x20
	mov r1, #0
	bl FUN_0200CCF8
	add r0, r5, #0
	add r0, #0x20
	bl FUN_02019178
	mov r1, #0
	ldr r0, [r5, #4]
	add r2, r1, #0
	bl DestroyListMenu
	ldr r0, [r5]
	bl ListMenuItems_dtor
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F007C: .word 0x000005DC

	thumb_func_start MOD05_021F0080
MOD05_021F0080: ; 0x021F0080
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021F00AC
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4, #0x30]
	ldr r1, _021F00B4 ; =UNK05_021F8B44
	ldr r0, [r0, #8]
	ldr r2, _021F00B8 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x44]
	mov r0, #0xb
	str r0, [r4, #0x48]
_021F00AC:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	nop
_021F00B4: .word UNK05_021F8B44
_021F00B8: .word 0x000003D9

	thumb_func_start MOD05_021F00BC
MOD05_021F00BC: ; 0x021F00BC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x34]
	bl FUN_020286EC
	add r4, r0, #0
	ldr r0, [r5, #0x44]
	mov r1, #4
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _021F00DC
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F00DC:
	cmp r0, #0
	bne _021F0104
	add r1, r5, #0
	add r1, #0x90
	ldr r1, [r1]
	add r0, r4, #0
	bl FUN_02028468
	mov r0, #0
	add r1, r5, #0
	str r0, [sp]
	add r1, #0x8c
	ldr r0, [r5, #0x34]
	ldr r1, [r1]
	mov r2, #0x1f
	mov r3, #4
	bl FUN_02033A70
	mov r0, #1
	b _021F0122
_021F0104:
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r5, #0x38]
	mov r1, #0
	bl BufferPlayersName
	add r0, r5, #0
	mov r1, #0x23
	bl MOD05_021F01EC
	mov r0, #6
_021F0122:
	str r0, [r5, #0x48]
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F0128
MOD05_021F0128: ; 0x021F0128
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_0204652C

	thumb_func_start MOD05_021F0130
MOD05_021F0130: ; 0x021F0130
	add r4, r0, #0
	add r0, r5, #0
	bl FUN_02046528
	ldr r0, [r4, #0x48]
	cmp r0, #0xc
	bhi _021F01E8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021F014A: ; jump table
	.short _021F0164 - _021F014A - 2 ; case 0
	.short _021F0174 - _021F014A - 2 ; case 1
	.short _021F0184 - _021F014A - 2 ; case 2
	.short _021F018C - _021F014A - 2 ; case 3
	.short _021F0194 - _021F014A - 2 ; case 4
	.short _021F019C - _021F014A - 2 ; case 5
	.short _021F01A4 - _021F014A - 2 ; case 6
	.short _021F01AC - _021F014A - 2 ; case 7
	.short _021F01B4 - _021F014A - 2 ; case 8
	.short _021F01BC - _021F014A - 2 ; case 9
	.short _021F01C4 - _021F014A - 2 ; case 10
	.short _021F01CC - _021F014A - 2 ; case 11
	.short _021F01D4 - _021F014A - 2 ; case 12
_021F0164:
	add r0, r4, #0
	bl MOD05_021EFBF8
	cmp r0, #0
	beq _021F01E8
	mov r0, #0xc
	str r0, [r4, #0x48]
	b _021F01E8
_021F0174:
	add r0, r4, #0
	bl MOD05_021EFC74
	cmp r0, #0
	beq _021F01E8
	mov r0, #0xc
	str r0, [r4, #0x48]
	b _021F01E8
_021F0184:
	add r0, r4, #0
	bl MOD05_021EFD40
	b _021F01E8
_021F018C:
	add r0, r4, #0
	bl MOD05_021EFD7C
	b _021F01E8
_021F0194:
	add r0, r4, #0
	bl MOD05_021EFDF0
	b _021F01E8
_021F019C:
	add r0, r4, #0
	bl MOD05_021EFE2C
	b _021F01E8
_021F01A4:
	add r0, r4, #0
	bl MOD05_021EFE70
	b _021F01E8
_021F01AC:
	add r0, r4, #0
	bl MOD05_021EFEAC
	b _021F01E8
_021F01B4:
	add r0, r4, #0
	bl MOD05_021EFEDC
	b _021F01E8
_021F01BC:
	add r0, r4, #0
	bl MOD05_021EFFC8
	b _021F01E8
_021F01C4:
	add r0, r4, #0
	bl MOD05_021F0080
	b _021F01E8
_021F01CC:
	add r0, r4, #0
	bl MOD05_021F00BC
	b _021F01E8
_021F01D4:
	add r0, r4, #0
	bl MOD05_021F0290
	add r0, r4, #0
	bl FreeToHeap
	bl FUN_02037778
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F01E8:
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F01EC
MOD05_021F01EC: ; 0x021F01EC
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r0, #0x10
	add r5, r1, #0
	bl FUN_02019048
	cmp r0, #0
	beq _021F0204
	add r0, r4, #0
	add r0, #0x10
	bl FUN_02019178
_021F0204:
	ldr r0, [r4, #0x3c]
	ldr r2, [r4, #8]
	add r1, r5, #0
	bl ReadMsgDataIntoString
	ldr r0, [r4, #0x38]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #8]
	bl StringExpandPlaceholders
	ldr r0, [r4, #0x30]
	add r1, r4, #0
	ldr r0, [r0, #8]
	add r1, #0x10
	mov r2, #3
	bl FUN_020545B8
	ldr r0, [r4, #0x30]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r1, r0, #0
	add r0, r4, #0
	add r0, #0x10
	bl FUN_02054608
	ldr r0, [r4, #0x30]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r2, r0, #0
	add r0, r4, #0
	ldr r1, [r4, #0xc]
	add r0, #0x10
	mov r3, #1
	bl FUN_02054658
	str r0, [r4, #0x40]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F0254
MOD05_021F0254: ; 0x021F0254
	push {r4, lr}
	mov r1, #0
	mov r2, #0x94
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #4
	bl ScrStrBufs_new
	str r0, [r4, #0x38]
	ldr r2, _021F028C ; =0x00000251
	mov r0, #0
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	str r0, [r4, #0x3c]
	mov r0, #0x6e
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0xc]
	mov r0, #0x6e
	mov r1, #4
	bl String_ctor
	str r0, [r4, #8]
	pop {r4, pc}
	.balign 4, 0
_021F028C: .word 0x00000251

	thumb_func_start MOD05_021F0290
MOD05_021F0290: ; 0x021F0290
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x3c]
	bl DestroyMsgData
	ldr r0, [r4, #0x38]
	bl ScrStrBufs_delete
	ldr r0, [r4, #0xc]
	bl String_dtor
	ldr r0, [r4, #8]
	bl String_dtor
	add r0, r4, #0
	add r0, #0x10
	bl FUN_02019048
	cmp r0, #0
	beq _021F02C0
	add r4, #0x10
	add r0, r4, #0
	bl FUN_02019178
_021F02C0:
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F02C4
MOD05_021F02C4: ; 0x021F02C4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r5, [r6, #0x10]
	mov r0, #0xb
	mov r1, #0x94
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	bl MOD05_021F0254
	str r6, [r4, #0x30]
	ldr r0, [r6, #0xc]
	str r0, [r4, #0x34]
	mov r0, #0
	str r0, [r4, #0x48]
	cmp r5, #0
	bne _021F02F2
	ldr r1, _021F0300 ; =MOD05_021F0128
	add r0, r6, #0
	add r2, r4, #0
	bl FUN_020463CC
	pop {r4, r5, r6, pc}
_021F02F2:
	ldr r1, _021F0300 ; =MOD05_021F0128
	add r0, r5, #0
	add r2, r4, #0
	bl FUN_0204640C
	pop {r4, r5, r6, pc}
	nop
_021F0300: .word MOD05_021F0128

	thumb_func_start MOD05_021F0304
MOD05_021F0304: ; 0x021F0304
	push {r3, lr}
	cmp r2, #0
	bne _021F0310
	ldr r0, _021F0314 ; =0x000005DC
	bl FUN_020054C8
_021F0310:
	pop {r3, pc}
	nop
_021F0314: .word 0x000005DC

	thumb_func_start MOD05_021F0318
MOD05_021F0318: ; 0x021F0318
	push {r4, r5, r6, r7, lr}
	sub sp, #0x6c
	add r4, r3, #0
	add r7, r0, #0
	add r5, r1, #0
	mov r0, #0
	str r0, [sp, #0x58]
	ldr r1, [r4, #0x50]
	add r0, sp, #0x60
	add r6, r2, #0
	bl FUN_0201F02C
	ldr r3, _021F0434 ; =UNK05_021F8B6C
	add r2, sp, #0xc
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	cmp r6, #0x60
	str r0, [r2]
	bhs _021F0352
	mov r1, #0x60
	sub r0, r1, r6
	lsl r0, r0, #0x18
	ldrh r2, [r4]
	lsr r0, r0, #0x18
	mul r0, r2
	bl _s32_div_f
	b _021F036C
_021F0352:
	sub r6, #0x60
	lsl r0, r6, #0x18
	ldrh r1, [r4]
	lsr r0, r0, #0x18
	mul r0, r1
	mov r1, #0x60
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	mov r0, #0
	mvn r0, r0
	mul r0, r1
_021F036C:
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	cmp r5, #0x80
	bhs _021F038A
	mov r2, #0x80
	sub r2, r2, r5
	lsl r2, r2, #0x18
	ldrh r0, [r4, #2]
	lsr r2, r2, #0x18
	mul r2, r0
	asr r0, r2, #6
	lsr r0, r0, #0x19
	add r0, r2, r0
	lsl r0, r0, #9
	b _021F03A8
_021F038A:
	ldrh r2, [r4, #2]
	sub r5, #0x80
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	add r3, r2, #0
	mul r3, r0
	asr r0, r3, #6
	lsr r0, r0, #0x19
	add r0, r3, r0
	lsl r0, r0, #9
	lsr r2, r0, #0x10
	mov r0, #0
	mvn r0, r0
	mul r0, r2
	lsl r0, r0, #0x10
_021F03A8:
	lsr r5, r0, #0x10
	asr r0, r1, #4
	lsl r3, r0, #1
	lsl r1, r3, #1
	ldr r2, _021F0438 ; =FX_SinCosTable_
	add r3, r3, #1
	lsl r3, r3, #1
	ldrsh r1, [r2, r1]
	ldrsh r2, [r2, r3]
	add r0, sp, #0x24
	bl MTX_RotX43_
	add r0, sp, #0xc
	add r1, sp, #0x24
	add r2, sp, #0x18
	bl MTX_MultVec43
	asr r0, r5, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	ldr r3, _021F0438 ; =FX_SinCosTable_
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0x24
	bl MTX_RotY43_
	add r0, sp, #0x18
	add r1, sp, #0x24
	add r2, r0, #0
	bl MTX_MultVec43
	add r0, sp, #0x18
	add r1, r4, #0
	add r1, #0x20
	add r2, r0, #0
	bl MTX_MultVec43
	add r0, r4, #0
	add r0, #0x10
	add r1, sp, #0x18
	bl VEC_DotProduct
	add r1, r0, #0
	ldr r0, [r4, #0x1c]
	bl FX_Div
	neg r0, r0
	add r1, sp, #0x18
	add r2, r4, #4
	add r3, sp, #0
	bl VEC_MultAdd
	ldr r1, [sp, #0x60]
	ldr r0, [sp]
	add r2, sp, #0x54
	add r0, r1, r0
	str r0, [sp, #0x54]
	ldr r1, [sp, #0x68]
	ldr r0, [sp, #8]
	add r0, r1, r0
	str r0, [sp, #0x5c]
	ldmia r2!, {r0, r1}
	stmia r7!, {r0, r1}
	ldr r0, [r2]
	str r0, [r7]
	add sp, #0x6c
	pop {r4, r5, r6, r7, pc}
	nop
_021F0434: .word UNK05_021F8B6C
_021F0438: .word FX_SinCosTable_

	thumb_func_start MOD05_021F043C
MOD05_021F043C: ; 0x021F043C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #4
	mov r1, #0x60
	bl AllocFromHeap
	add r1, r5, #0
	add r4, r0, #0
	bl MOD05_021F0454
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F0454
MOD05_021F0454: ; 0x021F0454
	push {r4, r5, lr}
	sub sp, #0x2c
	add r5, r0, #0
	add r4, r1, #0
	add r0, sp, #0
	bl FUN_0201F014
	add r0, r4, #0
	bl FUN_0201F008
	strh r0, [r5]
	ldrh r0, [r5]
	ldr r2, _021F04F0 ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r1, r0, #1
	lsl r0, r1, #1
	add r1, r1, #1
	lsl r1, r1, #1
	ldrsh r0, [r2, r0]
	ldrsh r1, [r2, r1]
	bl FX_Div
	lsl r0, r0, #2
	mov r1, #3
	bl _s32_div_f
	bl FX_Atan
	ldr r3, _021F04F4 ; =UNK05_021F8B78
	strh r0, [r5, #2]
	ldmia r3!, {r0, r1}
	add r2, sp, #0x20
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r4, #0
	str r0, [r2]
	add r0, sp, #0x14
	bl FUN_0201F03C
	add r0, sp, #8
	add r1, r4, #0
	bl FUN_0201F02C
	add r0, sp, #0x14
	add r1, sp, #8
	add r2, r5, #4
	bl VEC_Subtract
	add r3, sp, #0x20
	add r2, r5, #0
	ldmia r3!, {r0, r1}
	add r2, #0x10
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r5, #4
	str r0, [r2]
	add r0, sp, #0x20
	bl VEC_DotProduct
	str r0, [r5, #0x1c]
	add r0, sp, #0
	ldrh r0, [r0]
	ldr r3, _021F04F0 ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	add r0, r5, #0
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, #0x20
	bl MTX_RotX43_
	str r4, [r5, #0x50]
	add sp, #0x2c
	pop {r4, r5, pc}
	nop
_021F04F0: .word FX_SinCosTable_
_021F04F4: .word UNK05_021F8B78

	thumb_func_start MOD05_021F04F8
MOD05_021F04F8: ; 0x021F04F8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F0512
	bne _021F0508
	bl GF_AssertFail
_021F0508:
	ldr r0, [r4]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4]
_021F0512:
	pop {r4, pc}

	thumb_func_start MOD05_021F0514
MOD05_021F0514: ; 0x021F0514
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02058458
	cmp r0, #0x97
	bgt _021F053E
	bge _021F05B2
	cmp r0, #0x15
	bgt _021F052E
	bge _021F059E
	cmp r0, #0
	beq _021F059E
	b _021F05BA
_021F052E:
	cmp r0, #0x62
	bgt _021F05BA
	cmp r0, #0x61
	blt _021F05BA
	beq _021F059E
	cmp r0, #0x62
	beq _021F059E
	b _021F05BA
_021F053E:
	cmp r0, #0xb0
	bgt _021F0554
	bge _021F059E
	cmp r0, #0x99
	bgt _021F05BA
	cmp r0, #0x98
	blt _021F05BA
	beq _021F05B2
	cmp r0, #0x99
	beq _021F05B2
	b _021F05BA
_021F0554:
	cmp r0, #0xb1
	bgt _021F055C
	beq _021F059E
	b _021F05BA
_021F055C:
	sub r0, #0xb2
	cmp r0, #0x17
	bhi _021F05BA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021F056E: ; jump table
	.short _021F059E - _021F056E - 2 ; case 0
	.short _021F059E - _021F056E - 2 ; case 1
	.short _021F059E - _021F056E - 2 ; case 2
	.short _021F059E - _021F056E - 2 ; case 3
	.short _021F05BA - _021F056E - 2 ; case 4
	.short _021F05BA - _021F056E - 2 ; case 5
	.short _021F05BA - _021F056E - 2 ; case 6
	.short _021F05BA - _021F056E - 2 ; case 7
	.short _021F059E - _021F056E - 2 ; case 8
	.short _021F059E - _021F056E - 2 ; case 9
	.short _021F059E - _021F056E - 2 ; case 10
	.short _021F059E - _021F056E - 2 ; case 11
	.short _021F05BA - _021F056E - 2 ; case 12
	.short _021F05BA - _021F056E - 2 ; case 13
	.short _021F05BA - _021F056E - 2 ; case 14
	.short _021F05BA - _021F056E - 2 ; case 15
	.short _021F05BA - _021F056E - 2 ; case 16
	.short _021F05A8 - _021F056E - 2 ; case 17
	.short _021F059E - _021F056E - 2 ; case 18
	.short _021F059E - _021F056E - 2 ; case 19
	.short _021F059E - _021F056E - 2 ; case 20
	.short _021F059E - _021F056E - 2 ; case 21
	.short _021F059E - _021F056E - 2 ; case 22
	.short _021F059E - _021F056E - 2 ; case 23
_021F059E:
	add r0, r4, #0
	bl FUN_02058628
	ldr r0, [r0, #4]
	pop {r4, pc}
_021F05A8:
	add r0, r4, #0
	bl FUN_02058628
	ldr r0, [r0, #4]
	pop {r4, pc}
_021F05B2:
	add r0, r4, #0
	bl MOD05_021F1C24
	pop {r4, pc}
_021F05BA:
	add r0, r4, #0
	bl FUN_02058628
	ldr r0, [r0, #8]
	pop {r4, pc}

	thumb_func_start MOD05_021F05C4
MOD05_021F05C4: ; 0x021F05C4
	push {r3, r4, r5, lr}
	mov r1, #0x18
	add r5, r0, #0
	bl FUN_02058604
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	add r1, r4, #0
	strh r0, [r4]
	add r0, r5, #0
	add r1, #8
	bl MOD05_021F1FC8
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021F05EC
	add r0, r5, #0
	bl FUN_020586A0
_021F05EC:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F05F0
MOD05_021F05F0: ; 0x021F05F0
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02058628
	add r1, r0, #0
	add r0, r4, #0
	add r1, #8
	bl MOD05_021F2060
	pop {r4, pc}

	thumb_func_start MOD05_021F0604
MOD05_021F0604: ; 0x021F0604
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02058628
	add r4, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021F061C
	add r1, r4, #0
	add r1, #0xc
	bl MOD05_021F20D8
_021F061C:
	add r4, #8
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2060
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0x14
	bl FUN_02058410
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F0634
MOD05_021F0634: ; 0x021F0634
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02058628
	add r4, r0, #0
	add r0, r5, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F0678
	ldr r0, [r4, #8]
	cmp r0, #0
	bne _021F0658
	add r1, r4, #0
	add r0, r5, #0
	add r1, #8
	bl MOD05_021F1FC8
_021F0658:
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021F0678
	add r1, r4, #0
	add r1, #0xc
	bl MOD05_021F20F8
	ldr r1, [r4, #8]
	add r0, r5, #0
	bl MOD05_021F2F48
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0x14
	bl FUN_02058418
_021F0678:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F067C
MOD05_021F067C: ; 0x021F067C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r0, #0
	bl FUN_02058628
	ldr r7, [r0, #8]
	add r0, r4, #0
	bl FUN_02058628
	str r0, [sp]
	add r0, r4, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F06E6
	cmp r7, #0
	beq _021F06E6
	add r0, r4, #0
	bl FUN_020584C4
	str r0, [sp, #4]
	add r0, r4, #0
	bl FUN_0205854C
	add r5, r0, #0
	cmp r5, #9
	blt _021F06B6
	bl GF_AssertFail
_021F06B6:
	lsl r6, r5, #2
	ldr r5, _021F06EC ; UNK05_021FC4B4
	ldr r2, [sp]
	ldr r3, [sp, #4]
	ldr r5, [r5, r6]
	add r0, r4, #0
	add r1, r7, #0
	blx r5
	ldr r1, [sp, #4]
	ldr r0, [sp]
	strh r1, [r0]
	add r0, r4, #0
	bl FUN_0205854C
	ldr r1, [sp]
	str r0, [r1, #4]
	add r0, r4, #0
	add r1, r7, #0
	bl MOD05_021F2F48
	add r0, r4, #0
	add r1, r7, #0
	bl MOD05_021F19A4
_021F06E6:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F06EC: .word UNK05_021FC4B4

	thumb_func_start MOD05_021F06F0
MOD05_021F06F0: ; 0x021F06F0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl FUN_02058628
	add r5, r0, #0
	add r0, r4, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F071A
	ldr r5, [r5, #8]
	cmp r5, #0
	beq _021F071A
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021F2F48
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021F19A4
_021F071A:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F071C
MOD05_021F071C: ; 0x021F071C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl FUN_02058628
	add r5, r0, #0
	add r0, r4, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F075A
	ldr r5, [r5, #8]
	cmp r5, #0
	beq _021F075A
	add r0, r4, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F074A
	mov r1, #1
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
_021F074A:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021F2F48
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021F19A4
_021F075A:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F075C
MOD05_021F075C: ; 0x021F075C
	push {r4, lr}
	mov r0, #0
	ldrsh r0, [r2, r0]
	add r4, r1, #0
	cmp r3, r0
	beq _021F0780
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
	b _021F0786
_021F0780:
	add r0, r4, #0
	bl MOD05_021F194C
_021F0786:
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F854
	pop {r4, pc}

	thumb_func_start MOD05_021F0790
MOD05_021F0790: ; 0x021F0790
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0
	ldrsh r0, [r2, r0]
	add r4, r1, #0
	cmp r3, r0
	beq _021F07B4
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
_021F07B4:
	add r0, r5, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F07C8
	mov r1, #2
	add r0, r4, #0
	lsl r1, r1, #0xa
	bl FUN_0201F854
_021F07C8:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F07CC
MOD05_021F07CC: ; 0x021F07CC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0
	ldrsh r0, [r2, r0]
	add r4, r1, #0
	cmp r3, r0
	beq _021F07F0
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
_021F07F0:
	add r0, r5, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F0804
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
_021F0804:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F0808
MOD05_021F0808: ; 0x021F0808
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0
	ldrsh r0, [r2, r0]
	add r4, r1, #0
	cmp r3, r0
	beq _021F082C
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
_021F082C:
	add r0, r5, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F0840
	mov r1, #2
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
_021F0840:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F0844
MOD05_021F0844: ; 0x021F0844
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0
	ldrsh r0, [r2, r0]
	add r4, r1, #0
	cmp r3, r0
	beq _021F0868
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
_021F0868:
	add r0, r5, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F087C
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xe
	bl FUN_0201F854
_021F087C:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F0880
MOD05_021F0880: ; 0x021F0880
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r6, r0, #0
	add r4, r2, #0
	mov r0, #0
	ldrsh r0, [r4, r0]
	add r5, r1, #0
	cmp r3, r0
	beq _021F08AC
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
	mov r0, #0
	strh r0, [r4, #2]
_021F08AC:
	ldr r0, [r4, #4]
	cmp r0, #6
	beq _021F08B6
	mov r0, #0
	strh r0, [r4, #2]
_021F08B6:
	add r0, r6, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F08FC
	ldr r6, _021F0900 ; =UNK05_021FC43C
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	mov r1, #2
	str r0, [r3]
	ldrsh r1, [r4, r1]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	bl FUN_0201F854
	mov r0, #2
	ldrsh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, #2]
	ldrsh r0, [r4, r0]
	lsl r1, r0, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _021F08FC
	mov r0, #0
	strh r0, [r4, #2]
_021F08FC:
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0
_021F0900: .word UNK05_021FC43C

	thumb_func_start MOD05_021F0904
MOD05_021F0904: ; 0x021F0904
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r6, r0, #0
	add r4, r2, #0
	mov r0, #0
	ldrsh r0, [r4, r0]
	add r5, r1, #0
	cmp r3, r0
	beq _021F0930
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
	mov r0, #0
	strh r0, [r4, #2]
_021F0930:
	ldr r0, [r4, #4]
	cmp r0, #7
	beq _021F093A
	mov r0, #0
	strh r0, [r4, #2]
_021F093A:
	add r0, r6, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F0978
	ldr r6, _021F097C ; =UNK05_021FC42C
	add r3, sp, #0
	add r2, r3, #0
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	mov r1, #2
	ldrsh r1, [r4, r1]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	bl FUN_0201F854
	mov r0, #2
	ldrsh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, #2]
	ldrsh r0, [r4, r0]
	lsl r1, r0, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _021F0978
	mov r0, #0
	strh r0, [r4, #2]
_021F0978:
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F097C: .word UNK05_021FC42C

	thumb_func_start MOD05_021F0980
MOD05_021F0980: ; 0x021F0980
	push {r4, r5, r6, lr}
	sub sp, #0x20
	add r6, r0, #0
	add r4, r2, #0
	mov r0, #0
	ldrsh r0, [r4, r0]
	add r5, r1, #0
	cmp r3, r0
	beq _021F09AC
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
	mov r0, #0
	strh r0, [r4, #2]
_021F09AC:
	ldr r0, [r4, #4]
	cmp r0, #8
	beq _021F09B6
	mov r0, #0
	strh r0, [r4, #2]
_021F09B6:
	add r0, r6, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F09FC
	ldr r6, _021F0A00 ; =UNK05_021FC494
	add r3, sp, #0
	add r2, r3, #0
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	mov r1, #2
	ldrsh r1, [r4, r1]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	bl FUN_0201F854
	mov r0, #2
	ldrsh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, #2]
	ldrsh r0, [r4, r0]
	lsl r1, r0, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _021F09FC
	mov r0, #0
	strh r0, [r4, #2]
_021F09FC:
	add sp, #0x20
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F0A00: .word UNK05_021FC494

	thumb_func_start MOD05_021F0A04
MOD05_021F0A04: ; 0x021F0A04
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r0, #0
	bl FUN_02058628
	ldr r7, [r0, #8]
	add r0, r4, #0
	bl FUN_02058628
	str r0, [sp]
	add r0, r4, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F0A6E
	cmp r7, #0
	beq _021F0A6E
	add r0, r4, #0

	thumb_func_start MOD05_021F0A28
MOD05_021F0A28: ; 0x021F0A28
	bl FUN_020584C4
	str r0, [sp, #4]
	add r0, r4, #0
	bl FUN_0205854C
	add r5, r0, #0
	cmp r5, #0xa
	blt _021F0A3E
	bl GF_AssertFail
_021F0A3E:
	lsl r6, r5, #2
	ldr r5, _021F0A74 ; =UNK05_021FC528
	ldr r2, [sp]
	ldr r3, [sp, #4]
	ldr r5, [r5, r6]
	add r0, r4, #0
	add r1, r7, #0
	blx r5
	ldr r1, [sp, #4]
	ldr r0, [sp]
	strh r1, [r0]
	add r0, r4, #0
	bl FUN_0205854C
	ldr r1, [sp]
	str r0, [r1, #4]
	add r0, r4, #0
	add r1, r7, #0
	bl MOD05_021F2F48
	add r0, r4, #0
	add r1, r7, #0
	bl MOD05_021F19A4
_021F0A6E:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F0A74: .word UNK05_021FC528

	thumb_func_start MOD05_021F0A78
MOD05_021F0A78: ; 0x021F0A78
	push {r4, lr}
	mov r0, #0
	ldrsh r0, [r2, r0]
	add r4, r1, #0
	cmp r3, r0
	bne _021F0A8A
	ldr r0, [r2, #4]
	cmp r0, #9
	bne _021F0AA2
_021F0A8A:
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
	b _021F0AA8
_021F0AA2:
	add r0, r4, #0
	bl MOD05_021F194C
_021F0AA8:
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F854
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F0AB4
MOD05_021F0AB4: ; 0x021F0AB4
	push {r4, lr}
	ldr r0, [r2, #4]
	add r4, r1, #0
	cmp r0, #9
	beq _021F0ACE
	add r0, r4, #0
	mov r1, #4
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
_021F0ACE:
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F0ADC
MOD05_021F0ADC: ; 0x021F0ADC
	push {r3, r4, r5, lr}
	mov r1, #0x14
	add r5, r0, #0
	bl FUN_02058604
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	strb r0, [r4]
	bl LCRandom
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1c
	sub r1, r1, r2
	mov r0, #0x1c
	ror r1, r0
	add r0, r2, r1
	strb r0, [r4, #2]
	add r0, r5, #0
	add r1, r4, #4
	bl MOD05_021F1FC8
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021F0B14
	add r0, r5, #0
	bl FUN_020586A0
_021F0B14:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F0B18
MOD05_021F0B18: ; 0x021F0B18
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02058628
	add r1, r0, #0
	add r0, r4, #0
	add r1, r1, #4
	bl MOD05_021F2060
	pop {r4, pc}

	thumb_func_start MOD05_021F0B2C
MOD05_021F0B2C: ; 0x021F0B2C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02058628
	add r4, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021F0B44
	add r1, r4, #0
	add r1, #8
	bl MOD05_021F20D8
_021F0B44:
	add r0, r5, #0
	add r1, r4, #4
	bl MOD05_021F2060
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0x14
	bl FUN_02058410
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F0B58
MOD05_021F0B58: ; 0x021F0B58
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02058628
	add r4, r0, #0
	add r0, r5, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F0B9A
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021F0B7A
	add r0, r5, #0
	add r1, r4, #4
	bl MOD05_021F1FC8
_021F0B7A:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021F0B9A
	add r1, r4, #0
	add r1, #8
	bl MOD05_021F20F8
	ldr r1, [r4, #4]
	add r0, r5, #0
	bl MOD05_021F2F48
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0x14
	bl FUN_02058418
_021F0B9A:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F0B9C
MOD05_021F0B9C: ; 0x021F0B9C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl FUN_02058628
	ldr r6, [r0, #4]
	add r0, r5, #0
	bl FUN_02058628
	add r4, r0, #0
	add r0, r5, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F0C26
	cmp r6, #0
	beq _021F0C26
	add r0, r5, #0
	bl FUN_020584C4
	add r7, r0, #0
	add r0, r5, #0
	bl FUN_0205854C
	mov r1, #2
	ldrsb r0, [r4, r1]
	cmp r0, #0
	beq _021F0BE0
	sub r0, r0, #1
	strb r0, [r4, #2]
	add r0, r6, #0
	mov r1, #0
	bl FUN_0201F854
	b _021F0C0C
_021F0BE0:
	add r0, r6, #0
	lsl r1, r1, #0xb
	bl FUN_0201F854
	mov r0, #1
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #1]
	ldrsb r0, [r4, r0]
	cmp r0, #0x20
	blt _021F0C0C
	mov r0, #0
	strb r0, [r4, #1]
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r2, r0, #0x1c
	sub r2, r2, r1
	mov r0, #0x1c
	ror r2, r0
	add r0, r1, r2
	strb r0, [r4, #2]
_021F0C0C:
	strb r7, [r4]
	add r0, r5, #0
	bl FUN_0205854C
	strb r0, [r4, #3]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD05_021F2F48
	add r0, r5, #0
	add r1, r6, #0
	bl MOD05_021F19A4
_021F0C26:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F0C28
MOD05_021F0C28: ; 0x021F0C28
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	bl FUN_02058628
	ldr r4, [r0, #8]
	add r0, r5, #0
	bl FUN_02058628
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F0CEA
	cmp r4, #0
	beq _021F0CEA
	add r0, r5, #0
	bl FUN_020584C4
	add r7, r0, #0
	add r0, r5, #0
	bl FUN_0205854C
	cmp r0, #0
	bne _021F0C9E
	cmp r7, #1
	bls _021F0C66
	mov r0, #1
	str r0, [sp, #4]
	b _021F0C6A
_021F0C66:
	mov r0, #0
	str r0, [sp, #4]
_021F0C6A:
	add r0, r4, #0
	bl FUN_0201F844
	ldr r1, [sp, #4]
	cmp r1, r0
	bne _021F0C7C
	ldr r0, [r6, #4]
	cmp r0, #0
	bne _021F0C94
_021F0C7C:
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F854
_021F0C94:
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F854
	b _021F0CD0
_021F0C9E:
	cmp r7, #1
	bls _021F0CA8
	mov r0, #1
	str r0, [sp]
	b _021F0CAC
_021F0CA8:
	mov r0, #0
	str r0, [sp]
_021F0CAC:
	add r0, r4, #0
	bl FUN_0201F844
	ldr r1, [sp]
	cmp r1, r0
	beq _021F0CC6
	add r0, r4, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
_021F0CC6:
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
_021F0CD0:
	strh r7, [r6]
	add r0, r5, #0
	bl FUN_0205854C
	str r0, [r6, #4]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2F48
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F19A4
_021F0CEA:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F0CF0
MOD05_021F0CF0: ; 0x021F0CF0
	push {r3, r4, r5, lr}
	mov r1, #0x14
	add r5, r0, #0
	bl FUN_02058604
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	strb r0, [r4]
	add r0, r5, #0
	add r1, r4, #4
	bl MOD05_021F1FC8
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021F0D16
	add r0, r5, #0
	bl FUN_020586A0
_021F0D16:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F0D18
MOD05_021F0D18: ; 0x021F0D18
	push {r3, r4, lr}
	sub sp, #0xc
	add r2, sp, #0
	mov r1, #0
	str r1, [r2]
	str r1, [r2, #4]
	add r4, r0, #0
	str r1, [r2, #8]
	bl FUN_02058628
	add r1, r0, #0
	add r0, r4, #0
	add r1, r1, #4
	bl MOD05_021F2060
	add r0, r4, #0
	add r1, sp, #0
	bl FUN_02058B94
	add sp, #0xc
	pop {r3, r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F0D44
MOD05_021F0D44: ; 0x021F0D44
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02058628
	add r4, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021F0D5C
	add r1, r4, #0
	add r1, #8
	bl MOD05_021F20D8
_021F0D5C:
	add r0, r5, #0
	add r1, r4, #4
	bl MOD05_021F2060
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0x14
	bl FUN_02058410
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F0D70
MOD05_021F0D70: ; 0x021F0D70
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02058628
	add r4, r0, #0
	add r0, r5, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F0DB2
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021F0D92
	add r0, r5, #0
	add r1, r4, #4
	bl MOD05_021F1FC8
_021F0D92:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021F0DB2
	add r1, r4, #0
	add r1, #8
	bl MOD05_021F20F8
	ldr r1, [r4, #4]
	add r0, r5, #0
	bl MOD05_021F2F48
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0x14
	bl FUN_02058418
_021F0DB2:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F0DB4
MOD05_021F0DB4: ; 0x021F0DB4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r0, #0
	bl FUN_02058628
	ldr r7, [r0, #4]
	add r0, r4, #0
	bl FUN_02058628
	str r0, [sp]
	add r0, r4, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F0E1E
	cmp r7, #0
	beq _021F0E1E
	add r0, r4, #0
	bl FUN_020584C4
	str r0, [sp, #4]
	add r0, r4, #0
	bl FUN_0205854C
	add r5, r0, #0
	cmp r5, #0xa
	blt _021F0DEE
	bl GF_AssertFail
_021F0DEE:
	lsl r6, r5, #2
	ldr r5, _021F0E24 ; =UNK05_021FC500
	ldr r2, [sp]
	ldr r3, [sp, #4]
	ldr r5, [r5, r6]
	add r0, r4, #0
	add r1, r7, #0
	blx r5
	ldr r1, [sp, #4]
	ldr r0, [sp]
	strb r1, [r0]
	add r0, r4, #0
	bl FUN_0205854C
	ldr r1, [sp]
	strb r0, [r1, #2]
	add r0, r4, #0
	add r1, r7, #0
	bl MOD05_021F2F48
	add r0, r4, #0
	add r1, r7, #0
	bl MOD05_021F19A4
_021F0E1E:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F0E24: .word UNK05_021FC500

	thumb_func_start MOD05_021F0E28
MOD05_021F0E28: ; 0x021F0E28
	push {r3, r4, r5, lr}
	add r4, r2, #0
	mov r0, #0
	ldrsb r0, [r4, r0]
	add r5, r1, #0
	cmp r3, r0
	beq _021F0E56
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
	ldrb r1, [r4, #3]
	mov r0, #1
	bic r1, r0
	strb r1, [r4, #3]
	pop {r3, r4, r5, pc}
_021F0E56:
	mov r0, #2
	ldrsb r0, [r4, r0]
	cmp r0, #9
	bne _021F0E6C
	ldrb r1, [r4, #3]
	mov r0, #1
	bic r1, r0
	mov r0, #1
	orr r0, r1
	strb r0, [r4, #3]
	pop {r3, r4, r5, pc}
_021F0E6C:
	ldrb r0, [r4, #3]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _021F0E8E
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r5, #0
	bl MOD05_021F1980
	ldrb r1, [r4, #3]
	mov r0, #1
	bic r1, r0
	strb r1, [r4, #3]
	pop {r3, r4, r5, pc}
_021F0E8E:
	add r0, r5, #0
	bl MOD05_021F194C
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F0E98
MOD05_021F0E98: ; 0x021F0E98
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r4, r2, #0
	mov r0, #0
	ldrsb r0, [r4, r0]
	add r5, r1, #0
	cmp r3, r0
	beq _021F0EC0
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
	b _021F0EF6
_021F0EC0:
	mov r0, #2
	ldrsb r0, [r4, r0]
	cmp r0, #9
	bne _021F0ED6
	ldrb r1, [r4, #3]
	mov r0, #1
	bic r1, r0
	mov r0, #1
	orr r0, r1
	strb r0, [r4, #3]
	pop {r4, r5, r6, pc}
_021F0ED6:
	ldrb r0, [r4, #3]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _021F0EF6
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r5, #0
	bl MOD05_021F1980
	ldrb r1, [r4, #3]
	mov r0, #1
	bic r1, r0
	strb r1, [r4, #3]
_021F0EF6:
	add r0, r6, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F0F0A
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0xa
	bl FUN_0201F854
_021F0F0A:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F0F0C
MOD05_021F0F0C: ; 0x021F0F0C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0
	ldrsb r0, [r2, r0]
	add r4, r1, #0
	cmp r3, r0
	beq _021F0F32
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
	b _021F0F48
_021F0F32:
	mov r0, #2
	ldrsb r0, [r2, r0]
	cmp r0, #9
	bne _021F0F48
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021F1980
_021F0F48:
	add r0, r5, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F0F5C
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
_021F0F5C:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F0F60
MOD05_021F0F60: ; 0x021F0F60
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0
	ldrsb r0, [r2, r0]
	add r4, r1, #0
	cmp r3, r0
	beq _021F0F86
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
	b _021F0F9C
_021F0F86:
	mov r0, #2
	ldrsb r0, [r2, r0]
	cmp r0, #9
	bne _021F0F9C
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021F1980
_021F0F9C:
	add r0, r5, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F0FB0
	mov r1, #2
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
_021F0FB0:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F0FB4
MOD05_021F0FB4: ; 0x021F0FB4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0
	ldrsb r0, [r2, r0]
	add r4, r1, #0
	cmp r3, r0
	beq _021F0FDA
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
	b _021F0FF0
_021F0FDA:
	mov r0, #2
	ldrsb r0, [r2, r0]
	cmp r0, #9
	bne _021F0FF0
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021F1980
_021F0FF0:
	add r0, r5, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F1004
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xe
	bl FUN_0201F854
_021F1004:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1008
MOD05_021F1008: ; 0x021F1008
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r6, r0, #0
	add r4, r2, #0
	mov r0, #0
	ldrsb r0, [r4, r0]
	add r5, r1, #0
	cmp r3, r0
	beq _021F1036
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
	mov r0, #0
	strb r0, [r4, #1]
	b _021F104C
_021F1036:
	mov r0, #2
	ldrsb r0, [r4, r0]
	cmp r0, #9
	bne _021F104C
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r5, #0
	bl MOD05_021F1980
_021F104C:
	mov r0, #2
	ldrsb r0, [r4, r0]
	cmp r0, #6
	beq _021F1058
	mov r0, #0
	strb r0, [r4, #1]
_021F1058:
	add r0, r6, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F109E
	ldr r6, _021F10A4 ; =UNK05_021FC458
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	mov r1, #1
	str r0, [r3]
	ldrsb r1, [r4, r1]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	bl FUN_0201F854
	mov r0, #1
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #1]
	ldrsb r0, [r4, r0]
	lsl r1, r0, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _021F109E
	mov r0, #0
	strb r0, [r4, #1]
_021F109E:
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	nop
_021F10A4: .word UNK05_021FC458

	thumb_func_start MOD05_021F10A8
MOD05_021F10A8: ; 0x021F10A8
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r6, r0, #0
	add r4, r2, #0
	mov r0, #0
	ldrsb r0, [r4, r0]
	add r5, r1, #0
	cmp r3, r0
	beq _021F10D6
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
	mov r0, #0
	strb r0, [r4, #1]
	b _021F10EC
_021F10D6:
	mov r0, #2
	ldrsb r0, [r4, r0]
	cmp r0, #9
	bne _021F10EC
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r5, #0
	bl MOD05_021F1980
_021F10EC:
	mov r0, #2
	ldrsb r0, [r4, r0]
	cmp r0, #7
	beq _021F10F8
	mov r0, #0
	strb r0, [r4, #1]
_021F10F8:
	add r0, r6, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F1136
	ldr r6, _021F113C ; =UNK05_021FC3EC
	add r3, sp, #0
	add r2, r3, #0
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	mov r1, #1
	ldrsb r1, [r4, r1]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	bl FUN_0201F854
	mov r0, #1
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #1]
	ldrsb r0, [r4, r0]
	lsl r1, r0, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _021F1136
	mov r0, #0
	strb r0, [r4, #1]
_021F1136:
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_021F113C: .word UNK05_021FC3EC

	thumb_func_start MOD05_021F1140
MOD05_021F1140: ; 0x021F1140
	push {r4, r5, r6, lr}
	sub sp, #0x20
	add r6, r0, #0
	add r4, r2, #0
	mov r0, #0
	ldrsb r0, [r4, r0]
	add r5, r1, #0
	cmp r3, r0
	beq _021F116E
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
	mov r0, #0
	strb r0, [r4, #1]
	b _021F1184
_021F116E:
	mov r0, #2
	ldrsb r0, [r4, r0]
	cmp r0, #9
	bne _021F1184
	add r0, r3, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r5, #0
	bl MOD05_021F1980
_021F1184:
	mov r0, #2
	ldrsb r0, [r4, r0]
	cmp r0, #8
	beq _021F1190
	mov r0, #0
	strb r0, [r4, #1]
_021F1190:
	add r0, r6, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F11D6
	ldr r6, _021F11DC ; =UNK05_021FC474
	add r3, sp, #0
	add r2, r3, #0
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	mov r1, #1
	ldrsb r1, [r4, r1]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	bl FUN_0201F854
	mov r0, #1
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #1]
	ldrsb r0, [r4, r0]
	lsl r1, r0, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _021F11D6
	mov r0, #0
	strb r0, [r4, #1]
_021F11D6:
	add sp, #0x20
	pop {r4, r5, r6, pc}
	nop
_021F11DC: .word UNK05_021FC474

	thumb_func_start MOD05_021F11E0
MOD05_021F11E0: ; 0x021F11E0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0
	ldrsb r0, [r2, r0]
	add r4, r1, #0
	cmp r3, r0
	beq _021F1206
	add r0, r3, #0
	bl MOD05_021F2FB8
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
	b _021F121E
_021F1206:
	mov r0, #2
	ldrsb r0, [r2, r0]
	cmp r0, #9
	beq _021F121E
	add r0, r3, #0
	bl MOD05_021F2FB8
	add r1, r0, #0
	add r0, r4, #0
	mov r2, #4
	bl MOD05_021F1958
_021F121E:
	add r0, r5, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F1232
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
_021F1232:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F1234
MOD05_021F1234: ; 0x021F1234
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r0, #0
	bl FUN_02058628
	ldr r0, [r0, #4]
	str r0, [sp]
	add r0, r7, #0
	bl FUN_02058628
	add r4, r0, #0
	add r0, r7, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F12B6
	ldr r0, [sp]
	cmp r0, #0
	beq _021F12B6
	add r0, r7, #0
	bl FUN_020584C4
	str r0, [sp, #8]
	add r0, r7, #0
	bl FUN_0205854C
	str r0, [sp, #4]
	cmp r0, #0xc
	blt _021F1272
	bl GF_AssertFail
_021F1272:
	mov r1, #2
	ldrsb r2, [r4, r1]
	cmp r2, #0
	bne _021F128C
	ldr r0, [sp, #4]
	cmp r0, r2
	beq _021F128C
	ldrb r0, [r4, #3]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bne _021F128C
	sub r0, r1, #3
	strb r0, [r4]
_021F128C:
	ldr r5, [sp, #4]
	ldr r1, [sp]
	lsl r6, r5, #2
	ldr r5, _021F12BC ; =UNK05_021FC4D8
	ldr r3, [sp, #8]
	ldr r5, [r5, r6]
	add r0, r7, #0
	add r2, r4, #0
	blx r5
	ldr r0, [sp, #8]
	ldr r1, [sp]
	strb r0, [r4]
	ldr r0, [sp, #4]
	strb r0, [r4, #2]
	add r0, r7, #0
	bl MOD05_021F2F48
	ldr r1, [sp]
	add r0, r7, #0
	bl MOD05_021F19A4
_021F12B6:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_021F12BC: .word UNK05_021FC4D8

	thumb_func_start MOD05_021F12C0
MOD05_021F12C0: ; 0x021F12C0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r3, #0
	add r4, r2, #0
	add r2, sp, #0
	ldr r3, _021F1348 ; =UNK05_021FC3FC
	add r5, r1, #0
	add r7, r2, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	lsl r0, r6, #2
	ldr r1, [r7, r0]
	mov r0, #0
	ldrsb r0, [r4, r0]
	cmp r6, r0
	beq _021F12FE
	add r0, r5, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
	ldrb r1, [r4, #3]
	mov r0, #1
	add sp, #0x10
	bic r1, r0
	strb r1, [r4, #3]
	pop {r3, r4, r5, r6, r7, pc}
_021F12FE:
	mov r2, #2
	ldrsb r0, [r4, r2]
	cmp r0, #0
	beq _021F1316
	ldrb r1, [r4, #3]
	mov r0, #1
	add sp, #0x10
	bic r1, r0
	mov r0, #1
	orr r0, r1
	strb r0, [r4, #3]
	pop {r3, r4, r5, r6, r7, pc}
_021F1316:
	ldrb r0, [r4, #3]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _021F133A
	add r0, r5, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
	ldrb r1, [r4, #3]
	mov r0, #1
	add sp, #0x10
	bic r1, r0
	strb r1, [r4, #3]
	pop {r3, r4, r5, r6, r7, pc}
_021F133A:
	add r0, r5, #0
	lsl r1, r2, #0xb
	bl FUN_0201F854
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F1348: .word UNK05_021FC3FC

	thumb_func_start MOD05_021F134C
MOD05_021F134C: ; 0x021F134C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r0, r3, #0
	add r5, r1, #0
	add r6, r2, #0
	str r3, [sp]
	bl MOD05_021F2FC4
	add r4, r0, #0
	mov r0, #0
	ldrsb r1, [r6, r0]
	ldr r0, [sp]
	cmp r0, r1
	bne _021F1370
	mov r0, #2
	ldrsb r0, [r6, r0]
	cmp r0, #0
	beq _021F1382
_021F1370:
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
	b _021F13B2
_021F1382:
	cmp r0, #0xa
	beq _021F1398
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
	b _021F13B2
_021F1398:
	add r0, r5, #0
	bl FUN_0201F844
	cmp r4, r0
	beq _021F13B2
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
_021F13B2:
	add r0, r7, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F13C6
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0xa
	bl FUN_0201F854
_021F13C6:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F13C8
MOD05_021F13C8: ; 0x021F13C8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r0, r3, #0
	add r5, r1, #0
	add r6, r2, #0
	str r3, [sp]
	bl MOD05_021F2FC4
	add r4, r0, #0
	mov r0, #0
	ldrsb r1, [r6, r0]
	ldr r0, [sp]
	cmp r0, r1
	beq _021F13F6
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
	b _021F142A
_021F13F6:
	mov r0, #2
	ldrsb r0, [r6, r0]
	cmp r0, #0xb
	beq _021F1410
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
	b _021F142A
_021F1410:
	add r0, r5, #0
	bl FUN_0201F844
	cmp r4, r0
	beq _021F142A
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0201F830
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F890
_021F142A:
	add r0, r7, #0
	bl MOD05_021F1DFC
	cmp r0, #0
	bne _021F143E
	mov r1, #1
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
_021F143E:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F1440
MOD05_021F1440: ; 0x021F1440
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r0, #0
	bl FUN_02058628
	ldr r7, [r0, #4]
	add r0, r4, #0
	bl FUN_02058628
	str r0, [sp]
	cmp r7, #0
	beq _021F14B4
	add r0, r4, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F14B4
	add r0, r4, #0
	bl FUN_020584C4
	str r0, [sp, #4]
	add r0, r4, #0
	bl FUN_0205854C
	add r5, r0, #0
	cmp r5, #4
	blt _021F147A
	bl GF_AssertFail
_021F147A:
	lsl r6, r5, #2
	ldr r5, _021F14B8 ; =UNK05_021FC40C
	ldr r2, [sp]
	ldr r3, [sp, #4]
	ldr r5, [r5, r6]
	add r0, r4, #0
	add r1, r7, #0
	blx r5
	ldr r2, [sp, #4]
	add r0, r4, #0
	add r1, r7, #0
	bl MOD05_021F1658
	ldr r1, [sp, #4]
	ldr r0, [sp]
	strb r1, [r0]
	add r0, r4, #0
	bl FUN_0205854C
	ldr r1, [sp]
	strb r0, [r1, #2]
	add r0, r4, #0
	add r1, r7, #0
	bl MOD05_021F2F48
	add r0, r4, #0
	add r1, r7, #0
	bl MOD05_021F19A4
_021F14B4:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F14B8: .word UNK05_021FC40C

	thumb_func_start MOD05_021F14BC
MOD05_021F14BC: ; 0x021F14BC
	push {r4, lr}
	mov r0, #0
	ldrsb r0, [r2, r0]
	add r4, r1, #0
	cmp r3, r0
	bne _021F14D0
	mov r0, #2
	ldrsb r0, [r2, r0]
	cmp r0, #0
	beq _021F14E6
_021F14D0:
	ldr r1, _021F1508 ; =UNK05_021FC41C
	lsl r2, r3, #2
	ldr r1, [r1, r2]
	add r0, r4, #0
	bl FUN_0201F830
	mov r1, #0xf
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F890
_021F14E6:
	add r0, r4, #0
	bl FUN_0201F8C0
	mov r1, #1
	lsl r1, r1, #0xc
	sub r1, r0, r1
	bpl _021F14F6
	mov r1, #0
_021F14F6:
	add r0, r4, #0
	bl FUN_0201F890
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F854
	pop {r4, pc}
	nop
_021F1508: .word UNK05_021FC41C

	thumb_func_start MOD05_021F150C
MOD05_021F150C: ; 0x021F150C
	push {r4, lr}
	mov r0, #0
	ldrsb r0, [r2, r0]
	add r4, r1, #0
	cmp r3, r0
	bne _021F1520
	mov r0, #2
	ldrsb r0, [r2, r0]
	cmp r0, #1
	beq _021F1534
_021F1520:
	ldr r1, _021F1540 ; =UNK05_021FC41C
	lsl r2, r3, #2
	ldr r1, [r1, r2]
	add r0, r4, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
_021F1534:
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
	pop {r4, pc}
	.balign 4, 0
_021F1540: .word UNK05_021FC41C

	thumb_func_start MOD05_021F1544
MOD05_021F1544: ; 0x021F1544
	push {r3, r4, r5, lr}
	add r4, r2, #0
	mov r0, #0
	ldrsb r0, [r4, r0]
	add r5, r1, #0
	cmp r3, r0
	bne _021F155A
	mov r0, #2
	ldrsb r0, [r4, r0]
	cmp r0, #2
	beq _021F1578
_021F155A:
	ldr r1, _021F1604 ; =UNK05_021FC41C
	lsl r2, r3, #2
	ldr r1, [r1, r2]
	add r0, r5, #0
	bl FUN_0201F830
	mov r1, #0xf
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl FUN_0201F890
	ldrb r1, [r4, #3]
	mov r0, #0xfe
	bic r1, r0
	strb r1, [r4, #3]
_021F1578:
	add r0, r5, #0
	bl FUN_0201F8C0
	add r1, r0, #0
	ldrb r0, [r4, #3]
	lsl r2, r0, #0x18
	lsr r2, r2, #0x19
	beq _021F1592
	cmp r2, #1
	beq _021F15B4
	cmp r2, #2
	beq _021F15DA
	b _021F15F4
_021F1592:
	mov r3, #1
	lsl r3, r3, #0xc
	sub r1, r1, r3
	mov r3, #0xa
	lsl r3, r3, #0xc
	cmp r1, r3
	bgt _021F15F4
	add r2, r2, #1
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	mov r3, #0xfe
	lsl r2, r2, #0x19
	bic r0, r3
	lsr r2, r2, #0x18
	orr r0, r2
	strb r0, [r4, #3]
	b _021F15F4
_021F15B4:
	mov r3, #1
	lsl r3, r3, #0xc
	add r1, r1, r3
	mov r3, #0xf
	lsl r3, r3, #0xc
	cmp r1, r3
	blt _021F15F4
	add r2, r2, #1
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	mov r3, #0xfe
	lsl r2, r2, #0x19
	bic r0, r3
	lsr r2, r2, #0x18
	orr r0, r2
	strb r0, [r4, #3]
	mov r0, #0
	strb r0, [r4, #1]
	b _021F15F4
_021F15DA:
	mov r0, #1
	ldrsb r2, [r4, r0]
	add r2, r2, #1
	strb r2, [r4, #1]
	ldrsb r0, [r4, r0]
	cmp r0, #0x1e
	blt _021F15F4
	mov r0, #0
	strb r0, [r4, #1]
	ldrb r2, [r4, #3]
	mov r0, #0xfe
	bic r2, r0
	strb r2, [r4, #3]
_021F15F4:
	add r0, r5, #0
	bl FUN_0201F890
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F854
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021F1604: .word UNK05_021FC41C

	thumb_func_start MOD05_021F1608
MOD05_021F1608: ; 0x021F1608
	push {r4, lr}
	mov r0, #0
	ldrsb r0, [r2, r0]
	add r4, r1, #0
	cmp r3, r0
	bne _021F161C
	mov r0, #2
	ldrsb r0, [r2, r0]
	cmp r0, #3
	beq _021F1632
_021F161C:
	ldr r1, _021F1654 ; =UNK05_021FC41C
	lsl r2, r3, #2
	ldr r1, [r1, r2]
	add r0, r4, #0
	bl FUN_0201F830
	mov r1, #0xf
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F890
_021F1632:
	add r0, r4, #0
	bl FUN_0201F8C0
	mov r1, #1
	lsl r1, r1, #0xc
	sub r1, r0, r1
	bpl _021F1642
	mov r1, #0
_021F1642:
	add r0, r4, #0
	bl FUN_0201F890
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F854
	pop {r4, pc}
	nop
_021F1654: .word UNK05_021FC41C

	thumb_func_start MOD05_021F1658
MOD05_021F1658: ; 0x021F1658
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r2, #0
	add r2, sp, #0
	mov r0, #0
	str r0, [r2]
	str r0, [r2, #4]
	str r0, [r2, #8]
	add r0, r1, #0
	bl FUN_0201F880
	asr r1, r0, #0xb
	lsr r1, r1, #0x14
	add r1, r0, r1
	asr r0, r1, #0xc
	cmp r4, #3
	bhi _021F16BE
	add r1, r4, r4
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021F1688: ; jump table
	.short _021F16BE - _021F1688 - 2 ; case 0
	.short _021F1690 - _021F1688 - 2 ; case 1
	.short _021F169C - _021F1688 - 2 ; case 2
	.short _021F16AE - _021F1688 - 2 ; case 3
_021F1690:
	cmp r0, #0x18
	blt _021F16BE
	mov r0, #6
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	b _021F16BE
_021F169C:
	cmp r0, #0x28
	bge _021F16A8
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp]
	b _021F16BE
_021F16A8:
	ldr r0, _021F16CC ; =0xFFFFB000
	str r0, [sp]
	b _021F16BE
_021F16AE:
	cmp r0, #0x38
	bge _021F16B8
	ldr r0, _021F16D0 ; =0xFFFFF000
	str r0, [sp]
	b _021F16BE
_021F16B8:
	mov r0, #5
	lsl r0, r0, #0xc
	str r0, [sp]
_021F16BE:
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_02058B94
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021F16CC: .word 0xFFFFB000
_021F16D0: .word 0xFFFFF000

	thumb_func_start MOD05_021F16D4
MOD05_021F16D4: ; 0x021F16D4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl FUN_02058628
	ldr r4, [r0, #4]
	add r0, r5, #0
	bl FUN_02058628
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F1734
	cmp r4, #0
	beq _021F1734
	add r0, r5, #0
	bl FUN_020584C4
	add r7, r0, #0
	strb r7, [r6]
	add r0, r5, #0
	bl FUN_0205854C
	strb r0, [r6, #2]
	add r0, r7, #0
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F854
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2F48
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F19A4
_021F1734:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1738
MOD05_021F1738: ; 0x021F1738
	push {r4, r5, r6, lr}
	add r5, r0, #0
	bl FUN_02058628
	ldr r4, [r0, #4]
	add r0, r5, #0
	bl FUN_02058628
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F179C
	cmp r4, #0
	beq _021F179C
	add r0, r5, #0
	bl FUN_020584C4
	strb r0, [r6]
	add r0, r5, #0
	bl FUN_0205854C
	strb r0, [r6, #2]
	add r0, r4, #0
	bl FUN_0201F844
	cmp r0, #0
	beq _021F1782
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
_021F1782:
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2F48
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F19A4
_021F179C:
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F17A0
MOD05_021F17A0: ; 0x021F17A0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl FUN_02058628
	ldr r4, [r0, #4]
	add r0, r5, #0
	bl FUN_02058628
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F1836
	cmp r4, #0
	beq _021F1836
	add r0, r5, #0
	bl FUN_020584C4
	add r7, r0, #0
	add r0, r5, #0
	bl FUN_0205854C
	cmp r0, #0
	bne _021F17F8
	add r0, r4, #0
	bl FUN_0201F844
	cmp r0, #1
	beq _021F17EC
	add r0, r4, #0
	mov r1, #1
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
_021F17EC:
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
	b _021F181C
_021F17F8:
	add r0, r4, #0
	bl FUN_0201F844
	cmp r0, #0
	beq _021F1812
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
_021F1812:
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
_021F181C:
	strb r7, [r6]
	add r0, r5, #0
	bl FUN_0205854C
	strb r0, [r6, #2]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2F48
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F19A4
_021F1836:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F1838
MOD05_021F1838: ; 0x021F1838
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl FUN_02058628
	ldr r4, [r0, #4]
	add r0, r5, #0
	bl FUN_02058628
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F18A0
	cmp r4, #0
	beq _021F18A0
	add r0, r5, #0
	bl FUN_020584C4
	mov r1, #0
	ldrsb r1, [r6, r1]
	add r7, r0, #0
	cmp r7, r1
	beq _021F187C
	bl MOD05_021F2FAC
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
_021F187C:
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2F48
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F19A4
	add r0, r5, #0
	strb r7, [r6]
	bl FUN_0205854C
	strb r0, [r6, #2]
_021F18A0:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F18A4
MOD05_021F18A4: ; 0x021F18A4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl FUN_02058628
	ldr r4, [r0, #4]
	add r0, r5, #0
	bl FUN_02058628
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F191A
	cmp r4, #0
	beq _021F191A
	add r0, r5, #0
	bl FUN_020584C4
	str r0, [sp]
	add r0, r5, #0
	bl FUN_0205854C
	add r7, r0, #0
	mov r0, #2
	ldrsb r0, [r6, r0]
	cmp r7, r0
	beq _021F18FA
	cmp r7, #0
	bne _021F18EA
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F830
	b _021F18F2
_021F18EA:
	add r0, r4, #0
	mov r1, #1
	bl FUN_0201F830
_021F18F2:
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
_021F18FA:
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
	ldr r0, [sp]
	add r1, r4, #0
	strb r0, [r6]
	add r0, r5, #0
	strb r7, [r6, #2]
	bl MOD05_021F2F48
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F19A4
_021F191A:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F191C
MOD05_021F191C: ; 0x021F191C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	bl FUN_0201F8C0
	asr r1, r0, #0xb
	lsr r1, r1, #0x14
	add r1, r0, r1
	asr r4, r1, #0xc
	add r0, r4, #0
	add r1, r6, #0
	bl _s32_div_f
	sub r1, r4, r1
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl FUN_0201F890
	add r0, r5, #0
	mov r1, #0
	bl FUN_0201F854
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F194C
MOD05_021F194C: ; 0x021F194C
	ldr r3, _021F1954 ; =MOD05_021F191C
	mov r1, #8
	bx r3
	nop
_021F1954: .word MOD05_021F191C

	thumb_func_start MOD05_021F1958
MOD05_021F1958: ; 0x021F1958
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r1, r2, #0
	bl MOD05_021F191C
	add r0, r5, #0
	bl FUN_0201F8C0
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0201F830
	add r0, r5, #0
	add r1, r6, #0
	bl FUN_0201F890
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1980
MOD05_021F1980: ; 0x021F1980
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F194C
	add r0, r5, #0
	bl FUN_0201F8C0
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0201F830
	add r0, r5, #0
	add r1, r6, #0
	bl FUN_0201F890
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F19A4
MOD05_021F19A4: ; 0x021F19A4
	push {r4, r5, r6, lr}
	mov r4, #1
	add r6, r1, #0
	lsl r1, r4, #9
	add r5, r0, #0
	bl FUN_0205842C
	cmp r0, #1
	bne _021F19B8
	mov r4, #0
_021F19B8:
	mov r1, #1
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl FUN_0205842C
	cmp r0, #1
	bne _021F19D6
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl FUN_0205842C
	cmp r0, #0
	bne _021F19D6
	mov r4, #0
_021F19D6:
	lsl r1, r4, #0x18
	add r0, r6, #0
	lsr r1, r1, #0x18
	bl FUN_0201F80C
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F19E4
MOD05_021F19E4: ; 0x021F19E4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r1, #4
	bl FUN_02058604
	add r4, r0, #0
	add r0, r5, #0
	bl MOD06_0224A130
	str r0, [r4]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F19FC
MOD05_021F19FC: ; 0x021F19FC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r1, #4
	bl FUN_02058604
	add r4, r0, #0
	add r0, r5, #0
	bl MOD06_0224A6B8
	str r0, [r4]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1A14
MOD05_021F1A14: ; 0x021F1A14
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r1, #4
	bl FUN_02058604
	add r4, r0, #0
	add r0, r5, #0
	bl MOD06_0224A8D4
	str r0, [r4]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1A2C
MOD05_021F1A2C: ; 0x021F1A2C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r1, #4
	bl FUN_02058604
	add r4, r0, #0
	add r0, r5, #0
	bl MOD06_0224AA40
	str r0, [r4]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1A44
MOD05_021F1A44: ; 0x021F1A44
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F1A48
MOD05_021F1A48: ; 0x021F1A48
	push {r4, lr}
	bl FUN_02058628
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F1A5E
	bl MOD05_021E4DE4
	mov r0, #0
	str r0, [r4]
_021F1A5E:
	pop {r4, pc}

	thumb_func_start MOD05_021F1A60
MOD05_021F1A60: ; 0x021F1A60
	push {r4, lr}
	bl FUN_02058628
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F1A76
	bl MOD05_021E4DE4
	mov r0, #0
	str r0, [r4]
_021F1A76:
	pop {r4, pc}

	thumb_func_start MOD05_021F1A78
MOD05_021F1A78: ; 0x021F1A78
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02058628
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F1A8C
	bl GF_AssertFail
_021F1A8C:
	add r0, r5, #0
	bl MOD06_0224A130
	str r0, [r4]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1A98
MOD05_021F1A98: ; 0x021F1A98
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02058628
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F1AAC
	bl GF_AssertFail
_021F1AAC:
	add r0, r5, #0
	bl MOD06_0224A6B8
	str r0, [r4]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1AB8
MOD05_021F1AB8: ; 0x021F1AB8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02058628
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F1ACC
	bl GF_AssertFail
_021F1ACC:
	add r0, r5, #0
	bl MOD06_0224A8D4
	str r0, [r4]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1AD8
MOD05_021F1AD8: ; 0x021F1AD8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02058628
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F1AEC
	bl GF_AssertFail
_021F1AEC:
	add r0, r5, #0
	bl MOD06_0224AA40
	str r0, [r4]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1AF8
MOD05_021F1AF8: ; 0x021F1AF8
	push {r4, lr}
	bl FUN_02058628
	add r4, r0, #0
	ldr r0, [r4]
	bl MOD06_0224A6FC
	mov r0, #0
	str r0, [r4]
	pop {r4, pc}

	thumb_func_start MOD05_021F1B0C
MOD05_021F1B0C: ; 0x021F1B0C
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD05_021F1C34
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, sp, #0
	bl FUN_02058BB4
	add sp, #0xc
	pop {r3, r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1B2C
MOD05_021F1B2C: ; 0x021F1B2C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02058628
	ldr r4, [r0]
	add r0, r5, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F1B54
	cmp r4, #0
	beq _021F1B54
	add r0, r5, #0
	bl MOD05_021F1C48
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_0201F854
_021F1B54:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1B58
MOD05_021F1B58: ; 0x021F1B58
	ldr r3, _021F1B5C ; =MOD05_021F1CA4
	bx r3
	.balign 4, 0
_021F1B5C: .word MOD05_021F1CA4

	thumb_func_start MOD05_021F1B60
MOD05_021F1B60: ; 0x021F1B60
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02058628
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F1B76
	add r1, r4, #4
	bl MOD05_021F20D8
_021F1B76:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2060
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0x14
	bl FUN_02058410
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1B8C
MOD05_021F1B8C: ; 0x021F1B8C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02058628
	add r4, r0, #0
	add r0, r5, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F1BCC
	ldr r0, [r4]
	cmp r0, #0
	bne _021F1BAE
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F1FC8
_021F1BAE:
	ldr r0, [r4]
	cmp r0, #0
	beq _021F1BCC
	add r1, r4, #4
	bl MOD05_021F20F8
	ldr r1, [r4]
	add r0, r5, #0
	bl MOD05_021F2F48
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0x14
	bl FUN_02058418
_021F1BCC:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1BD0
MOD05_021F1BD0: ; 0x021F1BD0
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD05_021F1C34
	mov r1, #0
	mov r0, #6
	lsl r0, r0, #0xe
	str r0, [sp, #4]
	str r1, [sp]
	str r1, [sp, #8]
	add r0, r4, #0
	add r1, sp, #0
	bl FUN_02058BB4
	add sp, #0xc
	pop {r3, r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1BF4
MOD05_021F1BF4: ; 0x021F1BF4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02058628
	ldr r4, [r0]
	add r0, r5, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F1C12
	cmp r4, #0
	beq _021F1C12
	add r0, r5, #0
	bl MOD05_021F1C48
_021F1C12:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F1C14
MOD05_021F1C14: ; 0x021F1C14
	ldr r3, _021F1C18 ; =MOD05_021F1CA4
	bx r3
	.balign 4, 0
_021F1C18: .word MOD05_021F1CA4

	thumb_func_start MOD05_021F1C1C
MOD05_021F1C1C: ; 0x021F1C1C
	ldr r3, _021F1C20 ; =FUN_02058628
	bx r3
	.balign 4, 0
_021F1C20: .word FUN_02058628

	thumb_func_start MOD05_021F1C24
MOD05_021F1C24: ; 0x021F1C24
	push {r3, lr}
	bl FUN_02058628
	bl MOD05_021F1C30
	pop {r3, pc}

	thumb_func_start MOD05_021F1C30
MOD05_021F1C30: ; 0x021F1C30
	ldr r0, [r0]
	bx lr

	thumb_func_start MOD05_021F1C34
MOD05_021F1C34: ; 0x021F1C34
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0x10
	bl FUN_02058604
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021F1FC8
	pop {r4, pc}

	thumb_func_start MOD05_021F1C48
MOD05_021F1C48: ; 0x021F1C48
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02058628
	ldr r4, [r0]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2F48
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F1C64
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F1C64
MOD05_021F1C64: ; 0x021F1C64
	push {r4, r5, r6, lr}
	mov r4, #1
	add r6, r1, #0
	lsl r1, r4, #9
	add r5, r0, #0
	bl FUN_0205842C
	cmp r0, #1
	bne _021F1C78
	mov r4, #0
_021F1C78:
	mov r1, #1
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl FUN_0205842C
	cmp r0, #1
	bne _021F1C96
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl FUN_0205842C
	cmp r0, #0
	bne _021F1C96
	mov r4, #0
_021F1C96:
	lsl r1, r4, #0x18
	add r0, r6, #0
	lsr r1, r1, #0x18
	bl FUN_0201F80C
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1CA4
MOD05_021F1CA4: ; 0x021F1CA4
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02058628
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021F2060
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1CB8
MOD05_021F1CB8: ; 0x021F1CB8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r1, #0
	mov r1, #1
	add r5, r0, #0
	add r6, r2, #0
	add r7, r3, #0
	bl FUN_02058390
	cmp r0, #0
	beq _021F1CD2
	bl GF_AssertFail
_021F1CD2:
	add r0, r5, #0
	bl MOD05_021F1D68
	add r0, r5, #0
	bl FUN_02058368
	str r0, [sp, #0x10]
	add r0, r5, #0
	bl FUN_0205839C
	sub r0, r0, #1
	str r0, [sp, #0xc]
	add r0, r5, #0
	bl FUN_020583A0
	str r4, [sp]
	str r6, [sp, #4]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	add r1, r5, #0
	str r7, [sp, #8]
	bl MOD05_021F1F04
	add r0, r5, #0
	mov r1, #4
	bl MOD05_021F3780
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_020583A4
	ldr r1, _021F1D28 ; =UNK05_021F8B84
	add r0, r4, #0
	ldr r1, [r1]
	bl MOD05_021F3810
	add r0, r5, #0
	mov r1, #1
	bl FUN_0205837C
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021F1D28: .word UNK05_021F8B84

	thumb_func_start MOD05_021F1D2C
MOD05_021F1D2C: ; 0x021F1D2C
	push {r4, lr}
	add r4, r0, #0
	bl FUN_020587E0
	cmp r0, #1
	beq _021F1D3C
	bl GF_AssertFail
_021F1D3C:
	add r0, r4, #0
	bl FUN_020583A0
	bl MOD05_021F1F58
	add r0, r4, #0
	bl FUN_020583AC
	bl MOD05_021F379C
	add r0, r4, #0
	mov r1, #0
	bl FUN_020583A4
	add r0, r4, #0
	mov r1, #1
	bl FUN_02058384
	add r0, r4, #0
	bl MOD05_021F1D80
	pop {r4, pc}

	thumb_func_start MOD05_021F1D68
MOD05_021F1D68: ; 0x021F1D68
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x51
	mov r1, #4
	bl NARC_ctor
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_020583F0
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1D80
MOD05_021F1D80: ; 0x021F1D80
	push {r3, lr}
	bl FUN_020583F4
	bl NARC_dtor
	pop {r3, pc}

	thumb_func_start MOD05_021F1D8C
MOD05_021F1D8C: ; 0x021F1D8C
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02058578
	mov r1, #4
	bl FUN_02058390
	cmp r0, #0
	bne _021F1DC6
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xe
	bl FUN_02058424
	cmp r0, #0
	beq _021F1DC6
	add r0, r4, #0
	bl FUN_02058920
	cmp r0, #0
	beq _021F1DC0
	add r0, r4, #0
	bl FUN_02058AB4
	cmp r0, #0
	beq _021F1DC6
_021F1DC0:
	add r0, r4, #0
	bl FUN_020586A0
_021F1DC6:
	pop {r4, pc}

	thumb_func_start MOD05_021F1DC8
MOD05_021F1DC8: ; 0x021F1DC8
	push {r3, lr}
	bl FUN_02058458
	bl MOD05_021F1DD4
	pop {r3, pc}

	thumb_func_start MOD05_021F1DD4
MOD05_021F1DD4: ; 0x021F1DD4
	push {r3, lr}
	ldr r3, _021F1DF4 ; =UNK05_021F9A9C
	ldr r1, _021F1DF8 ; =0x0000FFFF
_021F1DDA:
	ldr r2, [r3]
	cmp r2, r0
	bne _021F1DE4
	add r0, r3, #0
	pop {r3, pc}
_021F1DE4:
	add r3, #8
	ldr r2, [r3]
	cmp r2, r1
	bne _021F1DDA
	bl GF_AssertFail
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0
_021F1DF4: .word UNK05_021F9A9C
_021F1DF8: .word 0x0000FFFF

	thumb_func_start MOD05_021F1DFC
MOD05_021F1DFC: ; 0x021F1DFC
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02058920
	cmp r0, #1
	bne _021F1E16
	add r0, r4, #0
	bl FUN_02058AB4
	cmp r0, #0
	bne _021F1E16
	mov r0, #1
	pop {r4, pc}
_021F1E16:
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #8
	bl FUN_02058424
	cmp r0, #0
	beq _021F1E28
	mov r0, #1
	pop {r4, pc}
_021F1E28:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD05_021F1E2C
MOD05_021F1E2C: ; 0x021F1E2C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r2, #0
	bl FUN_020583F4
	add r1, r4, #0
	add r6, r0, #0
	bl NARC_GetMemberSize
	add r1, r0, #0
	cmp r5, #1
	bne _021F1E4C
	mov r0, #4
	bl AllocFromHeap
	b _021F1E52
_021F1E4C:
	mov r0, #4
	bl AllocFromHeapAtEnd
_021F1E52:
	add r5, r0, #0
	add r0, r6, #0
	add r1, r4, #0
	add r2, r5, #0
	bl NARC_ReadWholeMember
	add r0, r5, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1E64
MOD05_021F1E64: ; 0x021F1E64
	push {r3, r4, r5, lr}
	sub sp, #0x30
	add r4, r1, #0
	add r5, r0, #0
	add r1, sp, #0x24
	bl FUN_02058B5C
	add r0, r5, #0
	add r1, sp, #0x18
	bl FUN_02058B84
	add r0, r5, #0
	add r1, sp, #0xc
	bl FUN_02058BA4
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_02058BC4
	ldr r1, [sp, #0x24]
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #0xc]
	add r0, r1, r0
	ldr r3, [sp]
	add r0, r2, r0
	add r0, r3, r0
	str r0, [r4]
	ldr r1, [sp, #0x28]
	ldr r0, [sp, #0x1c]
	ldr r2, [sp, #0x10]
	add r0, r1, r0
	ldr r3, [sp, #4]
	add r0, r2, r0
	add r0, r3, r0
	str r0, [r4, #4]
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #0x20]
	ldr r2, [sp, #0x14]
	add r0, r1, r0
	ldr r3, [sp, #8]
	add r0, r2, r0
	add r0, r3, r0
	str r0, [r4, #8]
	add sp, #0x30
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1EC0
MOD05_021F1EC0: ; 0x021F1EC0
	push {r4, lr}
	add r4, r0, #0
	bl FUN_020584AC
	add r0, r4, #0
	bl FUN_02058884
	cmp r0, #1
	bne _021F1ED8
	add r0, r4, #0
	bl FUN_020586A0
_021F1ED8:
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1EDC
MOD05_021F1EDC: ; 0x021F1EDC
	push {r4, lr}
	mov r1, #1
	add r4, r0, #0
	bl FUN_0205889C
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0x14
	bl FUN_02058410
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1EF4
MOD05_021F1EF4: ; 0x021F1EF4
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F1EF8
MOD05_021F1EF8: ; 0x021F1EF8
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F1EFC
MOD05_021F1EFC: ; 0x021F1EFC
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F1F00
MOD05_021F1F00: ; 0x021F1F00
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F1F04
MOD05_021F1F04: ; 0x021F1F04
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r2, #0
	mov r2, #0x41
	add r5, r0, #0
	lsl r2, r2, #2
	str r1, [r5, r2]
	add r1, r4, #0
	bl MOD05_021F2E40
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0xa
	bl MOD05_021F33B4
	mov r2, #4
	mov r1, #8
	ldr r0, [sp, #0x18]
	str r2, [sp]
	str r0, [sp, #4]
	ldr r0, [sp, #0x1c]
	add r3, r1, #0
	str r0, [sp, #8]
	add r0, r5, #0
	bl MOD05_021F22E0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2160
	ldr r1, [sp, #0x20]
	ldr r2, _021F1F50 ; =UNK05_021F8B90
	ldr r3, _021F1F54 ; =UNK05_021F8B88
	add r0, r5, #0
	bl MOD05_021F25A0
	add sp, #0xc
	pop {r4, r5, pc}
	.balign 4, 0
_021F1F50: .word UNK05_021F8B90
_021F1F54: .word UNK05_021F8B88

	thumb_func_start MOD05_021F1F58
MOD05_021F1F58: ; 0x021F1F58
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021F3458
	add r0, r4, #0
	bl MOD05_021F21AC
	add r0, r4, #0
	bl MOD05_021F2D48
	bl MOD05_021F2E68
	add r0, r4, #0
	bl MOD05_021F2368
	pop {r4, pc}

	thumb_func_start MOD05_021F1F78
MOD05_021F1F78: ; 0x021F1F78
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	mov r1, #0
	add r6, r2, #0
	add r7, r0, #0
	str r1, [r5]
	bl MOD05_021F2F3C
	add r1, r6, #0
	str r0, [sp]
	bl MOD05_021F28E8
	add r4, r0, #0
	bne _021F1FA2
	add r0, r7, #0
	add r1, r5, #0
	add r2, r6, #0
	bl MOD05_021F211C
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F1FA2:
	sub r0, r4, #3
	cmp r0, #1
	bhi _021F1FB8
	ldr r0, [sp]
	add r1, r7, #0
	add r2, r5, #0
	add r3, r6, #0
	bl MOD05_021F32BC
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F1FB8:
	add r0, r7, #0
	add r1, r6, #0
	bl MOD05_021F1FE0
	str r0, [r5]
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1FC8
MOD05_021F1FC8: ; 0x021F1FC8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02058458
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F1F78
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F1FE0
MOD05_021F1FE0: ; 0x021F1FE0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r0, #0
	add r5, r1, #0
	bl MOD05_021F2F3C
	add r4, r0, #0
	bl MOD05_021F2D48
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021F2AC8
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021F21CC
	add r4, r0, #0
	bne _021F200C
	bl GF_AssertFail
_021F200C:
	add r0, r6, #0
	add r1, sp, #0
	bl MOD05_021F1E64
	add r0, r7, #0
	add r1, r4, #0
	add r2, sp, #0
	bl MOD05_021F2E70
	add r4, r0, #0
	bne _021F2026
	bl GF_AssertFail
_021F2026:
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F202C
MOD05_021F202C: ; 0x021F202C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	add r6, r2, #0
	bl FUN_0201F744
	mov r0, #0
	str r0, [r4]
	add r0, r5, #0
	bl FUN_02058578
	add r1, r5, #0
	add r2, r6, #0
	bl MOD05_021F2284
	cmp r0, #0
	bne _021F205C
	add r0, r5, #0
	bl MOD05_021F2F3C
	add r1, r6, #0
	bl MOD05_021F2240
_021F205C:
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F2060
MOD05_021F2060: ; 0x021F2060
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	bl MOD05_021F2150
	ldr r0, [r4]
	cmp r0, #0
	beq _021F2092
	add r0, r5, #0
	bl FUN_02058458
	add r6, r0, #0
	bl FUN_0205C334
	cmp r0, #1
	bne _021F2088
	add r0, r5, #0
	bl FUN_0205C340
	add r6, r0, #0
_021F2088:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD05_021F202C
_021F2092:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F2094
MOD05_021F2094: ; 0x021F2094
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r4, r2, #0
	bl MOD05_021F2150
	ldr r0, [r5]
	cmp r0, #0
	beq _021F20AE
	bl FUN_0201F744
	mov r0, #0
	str r0, [r5]
_021F20AE:
	ldr r0, _021F20D4 ; =0x0000FFFF
	cmp r4, r0
	beq _021F20D2
	add r0, r6, #0
	bl FUN_02058578
	add r1, r6, #0
	add r2, r4, #0
	bl MOD05_021F2284
	cmp r0, #0
	bne _021F20D2
	add r0, r6, #0
	bl MOD05_021F2F3C
	add r1, r4, #0
	bl MOD05_021F2240
_021F20D2:
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F20D4: .word 0x0000FFFF

	thumb_func_start MOD05_021F20D8
MOD05_021F20D8: ; 0x021F20D8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0201F820
	str r0, [r4]
	add r0, r5, #0
	bl FUN_0201F844
	strh r0, [r4, #6]
	add r0, r5, #0
	bl FUN_0201F880
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F20F8
MOD05_021F20F8: ; 0x021F20F8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4]
	add r5, r0, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_0201F80C
	ldrh r1, [r4, #6]
	add r0, r5, #0
	bl FUN_0201F830
	ldr r1, [r4, #8]
	add r0, r5, #0
	bl FUN_0201F86C
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F211C
MOD05_021F211C: ; 0x021F211C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r2, #0
	add r6, r0, #0
	add r5, r1, #0
	bl MOD05_021F2F3C
	add r1, r4, #0
	add r7, r0, #0
	bl MOD05_021F2460
	cmp r0, #0
	bne _021F2140
	add r0, r6, #0
	add r1, r4, #0
	bl MOD05_021F1FE0
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021F2140:
	add r0, r7, #0
	add r1, r6, #0
	add r2, r5, #0
	add r3, r4, #0
	bl MOD05_021F32BC
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F2150
MOD05_021F2150: ; 0x021F2150
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021F2F3C
	add r1, r4, #0
	bl MOD05_021F32F8
	pop {r4, pc}

	thumb_func_start MOD05_021F2160
MOD05_021F2160: ; 0x021F2160
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	mov r1, #0x28
	add r7, r0, #0
	mov r0, #4
	mul r1, r6
	bl AllocFromHeap
	add r4, r0, #0
	add r0, r7, #0
	add r0, #0xe4
	str r4, [r0]
	cmp r4, #0
	bne _021F2180
	bl GF_AssertFail
_021F2180:
	mov r0, #4
	lsl r1, r6, #3
	bl AllocFromHeap
	add r5, r0, #0
	add r7, #0xf4
	str r5, [r7]
	cmp r5, #0
	bne _021F2196
	bl GF_AssertFail
_021F2196:
	ldr r0, _021F21A8 ; =0x0000FFFF
_021F2198:
	str r0, [r5]
	str r4, [r5, #4]
	add r5, #8
	add r4, #0x28
	sub r6, r6, #1
	bne _021F2198
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F21A8: .word 0x0000FFFF

	thumb_func_start MOD05_021F21AC
MOD05_021F21AC: ; 0x021F21AC
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021F2260
	add r1, r4, #0
	add r1, #0xe4
	ldr r1, [r1]
	mov r0, #4
	bl FreeToHeapExplicit
	add r4, #0xf4
	ldr r1, [r4]
	mov r0, #4
	bl FreeToHeapExplicit
	pop {r4, pc}

	thumb_func_start MOD05_021F21CC
MOD05_021F21CC: ; 0x021F21CC
	push {r4, r5, r6, lr}
	add r2, r0, #0
	add r2, #0xf4
	ldr r4, [r2]
	ldr r2, [r0, #4]
	add r6, r4, #0
	add r5, r2, #0
_021F21DA:
	ldr r3, [r6]
	cmp r3, r1
	bne _021F21E4
	ldr r0, [r6, #4]
	pop {r4, r5, r6, pc}
_021F21E4:
	add r6, #8
	sub r5, r5, #1
	bne _021F21DA
	ldr r3, _021F2208 ; =0x0000FFFF
_021F21EC:
	ldr r5, [r4]
	cmp r5, r3
	bne _021F21FE
	str r1, [r4]
	ldr r2, [r4, #4]
	bl MOD05_021F2ED0
	ldr r0, [r4, #4]
	pop {r4, r5, r6, pc}
_021F21FE:
	add r4, #8
	sub r2, r2, #1
	bne _021F21EC
	mov r0, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F2208: .word 0x0000FFFF

	thumb_func_start MOD05_021F220C
MOD05_021F220C: ; 0x021F220C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r2, #0
	bl FUN_020583A0
	add r1, r0, #0
	add r1, #0xf4
	ldr r2, [r1]
	ldr r1, [r0, #4]
_021F221E:
	ldr r0, [r2]
	cmp r0, r5
	bne _021F2234
	ldr r3, [r2, #4]
	mov r2, #5
_021F2228:
	ldmia r3!, {r0, r1}
	stmia r4!, {r0, r1}
	sub r2, r2, #1
	bne _021F2228
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F2234:
	add r2, #8
	sub r1, r1, #1
	bne _021F221E
	mov r0, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F2240
MOD05_021F2240: ; 0x021F2240
	add r2, r0, #0
	add r2, #0xf4
	ldr r3, [r2]
	ldr r2, [r0, #4]
_021F2248:
	ldr r0, [r3]
	cmp r0, r1
	bne _021F2254
	ldr r0, _021F225C ; =0x0000FFFF
	str r0, [r3]
	bx lr
_021F2254:
	add r3, #8
	sub r2, r2, #1
	bne _021F2248
	bx lr
	.balign 4, 0
_021F225C: .word 0x0000FFFF

	thumb_func_start MOD05_021F2260
MOD05_021F2260: ; 0x021F2260
	push {r3, r4}
	add r1, r0, #0
	add r1, #0xf4
	ldr r4, [r1]
	ldr r1, _021F2280 ; =0x0000FFFF
	ldr r3, [r0, #4]
	add r0, r1, #0
_021F226E:
	ldr r2, [r4]
	cmp r2, r0
	beq _021F2276
	str r1, [r4]
_021F2276:
	add r4, #8
	sub r3, r3, #1
	bne _021F226E
	pop {r3, r4}
	bx lr
	.balign 4, 0
_021F2280: .word 0x0000FFFF

	thumb_func_start MOD05_021F2284
MOD05_021F2284: ; 0x021F2284
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	bl FUN_02058368
	add r4, r0, #0
	add r0, r5, #0
	bl FUN_020583BC
	str r0, [sp]
_021F229A:
	ldr r0, [sp]
	cmp r0, r6
	beq _021F22CE
	bl FUN_02058830
	cmp r0, #1
	bne _021F22CE
	ldr r0, [sp]
	bl FUN_02058458
	add r5, r0, #0
	bl FUN_0205C334
	cmp r0, #1
	bne _021F22C0
	ldr r0, [sp]
	bl FUN_0205C340
	add r5, r0, #0
_021F22C0:
	ldr r0, _021F22DC ; =0x0000FFFF
	cmp r5, r0
	beq _021F22CE
	cmp r5, r7
	bne _021F22CE
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F22CE:
	add r0, sp, #0
	bl FUN_020583D4
	sub r4, r4, #1
	bne _021F229A
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F22DC: .word 0x0000FFFF

	thumb_func_start MOD05_021F22E0
MOD05_021F22E0: ; 0x021F22E0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	add r7, r3, #0
	mov r0, #4
	mov r1, #0x40
	lsl r2, r4, #0xc
	add r3, r4, #0
	bl MOD05_021F5990
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	add r0, r5, #0
	bl MOD05_021F2614
	add r0, r5, #0
	add r1, r6, #0
	bl MOD05_021F2D80
	add r0, r5, #0
	sub r1, r4, r6
	bl MOD05_021F2D88
	mov r0, #4
	mov r1, #0x41
	lsl r2, r7, #7
	add r3, r7, #0
	bl MOD05_021F5990
	add r1, r5, #0
	add r1, #0xfc
	str r0, [r1]
	add r0, r5, #0
	bl MOD05_021F2750
	ldr r1, [sp, #0x18]
	add r0, r5, #0
	bl MOD05_021F2D90
	ldr r1, [sp, #0x18]
	add r0, r5, #0
	sub r1, r7, r1
	bl MOD05_021F2D98
	ldr r0, [sp, #0x1c]
	mov r1, #4
	bl FUN_02020E90
	add r1, r0, #0
	add r0, r5, #0
	bl MOD05_021F2D64
	add r0, r5, #0
	bl MOD05_021F288C
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	bl MOD05_021F2DA0
	ldr r2, [sp, #0x1c]
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	sub r1, r2, r1
	bl MOD05_021F2DA8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F2368
MOD05_021F2368: ; 0x021F2368
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xf8
	ldr r0, [r0]
	bl MOD05_021F59EC
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	bl MOD05_021F59EC
	add r0, r4, #0
	bl MOD05_021F2D6C
	bl FUN_02020ED4
	pop {r4, pc}
	.balign 4, 0
_021F238C:
	ldr r3, [r2]
	cmp r3, r0
	bne _021F2396
	add r0, r2, #0
	bx lr
_021F2396:
	add r2, #8
	ldr r3, [r2]
	cmp r3, r1
	bne _021F238C
	mov r0, #0
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F23A4
MOD05_021F23A4: ; 0x021F23A4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r4, r2, #0
	add r5, r0, #0
	add r0, r6, #0
	add r1, r4, #0
	add r7, r3, #0
	bl MOD05_021F5AA4
	cmp r0, #1
	bne _021F23BE
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F23BE:
	ldr r2, [sp, #0x18]
	add r0, r4, #0
	add r1, r7, #0
	bl _021F238C
	add r7, r0, #0
	bne _021F23D0
	bl GF_AssertFail
_021F23D0:
	mov r0, #0x41
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_020583F4
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r3, [r7, #4]
	add r0, r6, #0
	add r1, r4, #0
	bl MOD05_021F5AE4
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F23F0
MOD05_021F23F0: ; 0x021F23F0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, #0xf0
	add r4, r2, #0
	add r6, r1, #0
	ldr r0, [r0]
	add r1, r4, #0
	add r7, r3, #0
	bl FUN_02020EF8
	cmp r0, #0
	bne _021F240C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F240C:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F3084
	cmp r0, #0
	beq _021F241C
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F241C:
	ldr r1, _021F2448 ; =0x0000FFFF
	add r0, r4, #0
	add r2, r7, #0
	bl _021F238C
	add r2, r0, #0
	bne _021F242E
	mov r0, #2
	pop {r3, r4, r5, r6, r7, pc}
_021F242E:
	ldr r2, [r2, #4]
	add r0, r5, #0
	add r1, r4, #0
	add r3, r6, #0
	bl MOD05_021F2FD0
	cmp r0, #1
	bne _021F2442
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F2442:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F2448: .word 0x0000FFFF

	thumb_func_start MOD05_021F244C
MOD05_021F244C: ; 0x021F244C
	push {r3, lr}
	ldr r3, _021F245C ; =UNK05_021FA0AC
	add r2, r1, #0
	mov r1, #0
	bl MOD05_021F23F0
	pop {r3, pc}
	nop
_021F245C: .word UNK05_021FA0AC

	thumb_func_start MOD05_021F2460
MOD05_021F2460: ; 0x021F2460
	push {r3, lr}
	ldr r3, _021F2470 ; =UNK05_021FA0AC
	add r2, r1, #0
	mov r1, #1
	bl MOD05_021F23F0
	pop {r3, pc}
	nop
_021F2470: .word UNK05_021FA0AC

	thumb_func_start MOD05_021F2474
MOD05_021F2474: ; 0x021F2474
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r1, [r4]
	ldr r0, _021F2494 ; =0x0000FFFF
	cmp r1, r0
	beq _021F2492
	add r6, r0, #0
_021F2484:
	add r0, r5, #0
	bl MOD05_021F244C
	add r4, r4, #4
	ldr r1, [r4]
	cmp r1, r6
	bne _021F2484
_021F2492:
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F2494: .word 0x0000FFFF

	thumb_func_start MOD05_021F2498
MOD05_021F2498: ; 0x021F2498
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F2D54
	ldr r0, _021F24C0 ; =UNK05_021F9094
	add r1, r5, #0
	str r0, [sp]
	add r1, #0xf8
	ldr r1, [r1]
	ldr r3, _021F24C4 ; =0x0000FFFF
	add r0, r5, #0
	add r2, r4, #0
	bl MOD05_021F23A4
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2628
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021F24C0: .word UNK05_021F9094
_021F24C4: .word 0x0000FFFF

	thumb_func_start MOD05_021F24C8
MOD05_021F24C8: ; 0x021F24C8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F2D54
	ldr r0, _021F24F0 ; =UNK05_021F9094
	add r1, r5, #0
	str r0, [sp]
	add r1, #0xf8
	ldr r1, [r1]
	ldr r3, _021F24F4 ; =0x0000FFFF
	add r0, r5, #0
	add r2, r4, #0
	bl MOD05_021F23A4
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2670
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021F24F0: .word UNK05_021F9094
_021F24F4: .word 0x0000FFFF

	thumb_func_start MOD05_021F24F8
MOD05_021F24F8: ; 0x021F24F8
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r1, [r4]
	ldr r0, _021F2518 ; =0x0000FFFF
	cmp r1, r0
	beq _021F2516
	add r6, r0, #0
_021F2508:
	add r0, r5, #0
	bl MOD05_021F2498
	add r4, r4, #4
	ldr r1, [r4]
	cmp r1, r6
	bne _021F2508
_021F2516:
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F2518: .word 0x0000FFFF

	thumb_func_start MOD05_021F251C
MOD05_021F251C: ; 0x021F251C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F2D5C
	ldr r0, _021F2544 ; =UNK05_021F90E4
	add r1, r5, #0
	str r0, [sp]
	add r1, #0xfc
	ldr r1, [r1]
	ldr r3, _021F2548 ; =0x0000FFFF
	add r0, r5, #0
	add r2, r4, #0
	bl MOD05_021F23A4
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2764
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021F2544: .word UNK05_021F90E4
_021F2548: .word 0x0000FFFF

	thumb_func_start MOD05_021F254C
MOD05_021F254C: ; 0x021F254C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F2D5C
	ldr r0, _021F2574 ; =UNK05_021F90E4
	add r1, r5, #0
	str r0, [sp]
	add r1, #0xfc
	ldr r1, [r1]
	ldr r3, _021F2578 ; =0x0000FFFF
	add r0, r5, #0
	add r2, r4, #0
	bl MOD05_021F23A4
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F27AC
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021F2574: .word UNK05_021F90E4
_021F2578: .word 0x0000FFFF

	thumb_func_start MOD05_021F257C
MOD05_021F257C: ; 0x021F257C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r1, [r4]
	ldr r0, _021F259C ; =0x0000FFFF
	cmp r1, r0
	beq _021F259A
	add r6, r0, #0
_021F258C:
	add r0, r5, #0
	bl MOD05_021F251C
	add r4, r4, #4
	ldr r1, [r4]
	cmp r1, r6
	bne _021F258C
_021F259A:
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F259C: .word 0x0000FFFF

	thumb_func_start MOD05_021F25A0
MOD05_021F25A0: ; 0x021F25A0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r2, #0
	add r6, r3, #0
	bl MOD05_021F2474
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F24F8
	add r0, r5, #0
	add r1, r6, #0
	bl MOD05_021F257C
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F25C0:
	stmia r0!, {r1}
	sub r2, r2, #1
	bne _021F25C0
	bx lr

	thumb_func_start MOD05_021F25C8
MOD05_021F25C8: ; 0x021F25C8
	push {r3, r4}
_021F25CA:
	ldr r4, [r0]
	cmp r4, r2
	bne _021F25D8
	str r1, [r0]
	mov r0, #1
	pop {r3, r4}
	bx lr
_021F25D8:
	add r0, r0, #4
	sub r3, r3, #1
	bne _021F25CA
	mov r0, #0
	pop {r3, r4}
	bx lr
_021F25E4:
	ldr r3, [r0]
	cmp r3, r1
	bne _021F25EE
	mov r0, #1
	bx lr
_021F25EE:
	add r0, r0, #4
	sub r2, r2, #1
	bne _021F25E4
	mov r0, #0
	bx lr

	thumb_func_start MOD05_021F25F8
MOD05_021F25F8: ; 0x021F25F8
	push {r3, r4}
_021F25FA:
	ldr r4, [r0]
	cmp r4, r1
	bne _021F2608
	str r2, [r0]
	mov r0, #1
	pop {r3, r4}
	bx lr
_021F2608:
	add r0, r0, #4
	sub r3, r3, #1
	bne _021F25FA
	mov r0, #0
	pop {r3, r4}
	bx lr

	thumb_func_start MOD05_021F2614
MOD05_021F2614: ; 0x021F2614
	push {r3, lr}
	bl MOD05_021F2D78
	ldr r1, _021F2624 ; =0x0000FFFF
	mov r2, #8
	bl _021F25C0
	pop {r3, pc}
	.balign 4, 0
_021F2624: .word 0x0000FFFF

	thumb_func_start MOD05_021F2628
MOD05_021F2628: ; 0x021F2628
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F2D84
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2D78
	ldr r2, _021F2650 ; =0x0000FFFF
	add r1, r4, #0
	add r3, r6, #0
	bl MOD05_021F25C8
	cmp r0, #0
	bne _021F264C
	bl GF_AssertFail
_021F264C:
	pop {r4, r5, r6, pc}
	nop
_021F2650: .word 0x0000FFFF

	thumb_func_start MOD05_021F2654
MOD05_021F2654: ; 0x021F2654
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F2D84
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2D78
	add r1, r4, #0
	add r2, r6, #0
	bl _021F25E4
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F2670
MOD05_021F2670: ; 0x021F2670
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl MOD05_021F2D78
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2D84
	lsl r4, r0, #2
	add r0, r5, #0
	bl MOD05_021F2D8C
	add r3, r0, #0
	ldr r2, _021F26A0 ; =0x0000FFFF
	add r0, r6, r4
	add r1, r7, #0
	bl MOD05_021F25C8
	cmp r0, #0
	bne _021F269E
	bl GF_AssertFail
_021F269E:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F26A0: .word 0x0000FFFF

	thumb_func_start MOD05_021F26A4
MOD05_021F26A4: ; 0x021F26A4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl MOD05_021F2D78
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2D84
	lsl r4, r0, #2
	add r0, r5, #0
	bl MOD05_021F2D8C
	add r2, r0, #0
	add r0, r6, r4
	add r1, r7, #0
	bl _021F25E4
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F26CC
MOD05_021F26CC: ; 0x021F26CC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl MOD05_021F2D78
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2D84
	lsl r4, r0, #2
	add r0, r5, #0
	bl MOD05_021F2D8C
	add r3, r0, #0
	ldr r2, _021F26F4 ; =0x0000FFFF
	add r0, r6, r4
	add r1, r7, #0
	bl MOD05_021F25F8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F26F4: .word 0x0000FFFF

	thumb_func_start MOD05_021F26F8
MOD05_021F26F8: ; 0x021F26F8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r7, r0, #0
	add r0, r6, #0
	bl MOD05_021F2D54
	add r0, r6, #0
	bl MOD05_021F2D78
	add r4, r0, #0
	add r0, r6, #0
	bl MOD05_021F2D84
	lsl r0, r0, #2
	add r5, r4, r0
	add r0, r6, #0
	bl MOD05_021F2D8C
	add r4, r0, #0
_021F271E:
	ldr r1, [r5]
	ldr r0, _021F274C ; =0x0000FFFF
	cmp r1, r0
	beq _021F2742
	add r0, r7, #0
	mov r2, #0
	bl MOD05_021F2B70
	cmp r0, #0
	bne _021F2742
	add r0, r6, #0
	add r0, #0xf8
	ldr r0, [r0]
	ldr r1, [r5]
	bl MOD05_021F5A74
	ldr r0, _021F274C ; =0x0000FFFF
	str r0, [r5]
_021F2742:
	add r5, r5, #4
	sub r4, r4, #1
	bne _021F271E
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F274C: .word 0x0000FFFF

	thumb_func_start MOD05_021F2750
MOD05_021F2750: ; 0x021F2750
	push {r3, lr}
	bl MOD05_021F2D7C
	ldr r1, _021F2760 ; =0x0000FFFF
	mov r2, #8
	bl _021F25C0
	pop {r3, pc}
	.balign 4, 0
_021F2760: .word 0x0000FFFF

	thumb_func_start MOD05_021F2764
MOD05_021F2764: ; 0x021F2764
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F2D94
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2D7C
	ldr r2, _021F278C ; =0x0000FFFF
	add r1, r4, #0
	add r3, r6, #0
	bl MOD05_021F25C8
	cmp r0, #0
	bne _021F2788
	bl GF_AssertFail
_021F2788:
	pop {r4, r5, r6, pc}
	nop
_021F278C: .word 0x0000FFFF

	thumb_func_start MOD05_021F2790
MOD05_021F2790: ; 0x021F2790
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F2D94
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2D7C
	add r1, r4, #0
	add r2, r6, #0
	bl _021F25E4
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F27AC
MOD05_021F27AC: ; 0x021F27AC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl MOD05_021F2D7C
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2D94
	lsl r4, r0, #2
	add r0, r5, #0
	bl MOD05_021F2D9C
	add r3, r0, #0
	ldr r2, _021F27DC ; =0x0000FFFF
	add r0, r6, r4
	add r1, r7, #0
	bl MOD05_021F25C8
	cmp r0, #0
	bne _021F27DA
	bl GF_AssertFail
_021F27DA:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F27DC: .word 0x0000FFFF

	thumb_func_start MOD05_021F27E0
MOD05_021F27E0: ; 0x021F27E0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl MOD05_021F2D7C
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2D94
	lsl r4, r0, #2
	add r0, r5, #0
	bl MOD05_021F2D9C
	add r2, r0, #0
	add r0, r6, r4
	add r1, r7, #0
	bl _021F25E4
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F2808
MOD05_021F2808: ; 0x021F2808
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl MOD05_021F2D7C
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2D94
	lsl r4, r0, #2
	add r0, r5, #0
	bl MOD05_021F2D9C
	add r3, r0, #0
	ldr r2, _021F2830 ; =0x0000FFFF
	add r0, r6, r4
	add r1, r7, #0
	bl MOD05_021F25F8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F2830: .word 0x0000FFFF

	thumb_func_start MOD05_021F2834
MOD05_021F2834: ; 0x021F2834
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r7, r0, #0
	add r0, r6, #0
	bl MOD05_021F2D5C
	add r0, r6, #0
	bl MOD05_021F2D7C
	add r4, r0, #0
	add r0, r6, #0
	bl MOD05_021F2D94
	lsl r0, r0, #2
	add r5, r4, r0
	add r0, r6, #0
	bl MOD05_021F2D9C
	add r4, r0, #0
_021F285A:
	ldr r1, [r5]
	ldr r0, _021F2888 ; =0x0000FFFF
	cmp r1, r0
	beq _021F287E
	add r0, r7, #0
	mov r2, #0
	bl MOD05_021F2BF8
	cmp r0, #0
	bne _021F287E
	add r0, r6, #0
	add r0, #0xfc
	ldr r0, [r0]
	ldr r1, [r5]
	bl MOD05_021F5A74
	ldr r0, _021F2888 ; =0x0000FFFF
	str r0, [r5]
_021F287E:
	add r5, r5, #4
	sub r4, r4, #1
	bne _021F285A
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F2888: .word 0x0000FFFF

	thumb_func_start MOD05_021F288C
MOD05_021F288C: ; 0x021F288C
	push {r3, lr}
	bl MOD05_021F2D74
	ldr r1, _021F289C ; =0x0000FFFF
	mov r2, #0x20
	bl _021F25C0
	pop {r3, pc}
	.balign 4, 0
_021F289C: .word 0x0000FFFF

	thumb_func_start MOD05_021F28A0
MOD05_021F28A0: ; 0x021F28A0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F2DA4
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2D74
	ldr r2, _021F28C8 ; =0x0000FFFF
	add r1, r4, #0
	add r3, r6, #0
	bl MOD05_021F25C8
	cmp r0, #0
	bne _021F28C4
	bl GF_AssertFail
_021F28C4:
	pop {r4, r5, r6, pc}
	nop
_021F28C8: .word 0x0000FFFF

	thumb_func_start MOD05_021F28CC
MOD05_021F28CC: ; 0x021F28CC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F2DA4
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2D74
	add r1, r4, #0
	add r2, r6, #0
	bl _021F25E4
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F28E8
MOD05_021F28E8: ; 0x021F28E8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F28CC
	cmp r0, #1
	bne _021F28FA
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F28FA:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F29E0
	cmp r0, #1
	bne _021F290A
	mov r0, #2
	pop {r3, r4, r5, pc}
_021F290A:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F3084
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F2914
MOD05_021F2914: ; 0x021F2914
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl MOD05_021F2D74
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2DA4
	lsl r4, r0, #2
	add r0, r5, #0
	bl MOD05_021F2DAC
	add r3, r0, #0
	ldr r2, _021F2944 ; =0x0000FFFF
	add r0, r6, r4
	add r1, r7, #0
	bl MOD05_021F25C8
	cmp r0, #0
	bne _021F2942
	bl GF_AssertFail
_021F2942:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F2944: .word 0x0000FFFF

	thumb_func_start MOD05_021F2948
MOD05_021F2948: ; 0x021F2948
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl MOD05_021F2D74
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2DA4
	lsl r4, r0, #2
	add r0, r5, #0
	bl MOD05_021F2DAC
	add r3, r0, #0
	ldr r2, _021F2970 ; =0x0000FFFF
	add r0, r6, r4
	add r1, r7, #0
	bl MOD05_021F25F8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F2970: .word 0x0000FFFF

	thumb_func_start MOD05_021F2974
MOD05_021F2974: ; 0x021F2974
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	str r0, [sp]
	add r0, r6, #0
	bl MOD05_021F2D6C
	str r0, [sp, #4]
	add r0, r6, #0
	bl MOD05_021F2D74
	add r4, r0, #0
	add r0, r6, #0
	bl MOD05_021F2DA4
	lsl r0, r0, #2
	add r5, r4, r0
	add r0, r6, #0
	bl MOD05_021F2DAC
	add r7, r0, #0
_021F299E:
	ldr r4, [r5]
	ldr r0, _021F29DC ; =0x0000FFFF
	cmp r4, r0
	beq _021F29D0
	ldr r0, [sp]
	add r1, r4, #0
	mov r2, #0
	bl MOD05_021F2B10
	cmp r0, #0
	bne _021F29D0
	ldr r0, [sp, #4]
	add r1, r4, #0
	bl FUN_02020FF0
	add r0, r6, #0
	add r1, r4, #0
	bl MOD05_021F3050
	add r0, r6, #0
	add r1, r4, #0
	bl MOD05_021F3204
	ldr r0, _021F29DC ; =0x0000FFFF
	str r0, [r5]
_021F29D0:
	add r5, r5, #4
	sub r7, r7, #1
	bne _021F299E
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F29DC: .word 0x0000FFFF

	thumb_func_start MOD05_021F29E0
MOD05_021F29E0: ; 0x021F29E0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl MOD05_021F2D74
	add r6, r0, #0
	add r0, r5, #0
	bl MOD05_021F2DA4
	lsl r4, r0, #2
	add r0, r5, #0
	bl MOD05_021F2DAC
	add r2, r0, #0
	add r0, r6, r4
	add r1, r7, #0
	bl _021F25E4
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F2A08
MOD05_021F2A08: ; 0x021F2A08
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F28CC
	cmp r0, #1
	bne _021F2A1A
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F2A1A:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F29E0
	cmp r0, #1
	bne _021F2A2A
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F2A2A:
	mov r0, #2
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F2A30
MOD05_021F2A30: ; 0x021F2A30
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F2654
	cmp r0, #1
	bne _021F2A42
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F2A42:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F26A4
	cmp r0, #1
	bne _021F2A52
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F2A52:
	mov r0, #2
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F2A58
MOD05_021F2A58: ; 0x021F2A58
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F2790
	cmp r0, #1
	bne _021F2A6A
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F2A6A:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F27E0
	cmp r0, #1
	bne _021F2A7A
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F2A7A:
	mov r0, #2
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F2A80
MOD05_021F2A80: ; 0x021F2A80
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F28E8
	cmp r0, #0
	bne _021F2A96
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2460
_021F2A96:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F2A98
MOD05_021F2A98: ; 0x021F2A98
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F2A30
	cmp r0, #2
	bne _021F2AAE
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F24C8
_021F2AAE:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F2AB0
MOD05_021F2AB0: ; 0x021F2AB0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F2A58
	cmp r0, #2
	bne _021F2AC6
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F254C
_021F2AC6:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F2AC8
MOD05_021F2AC8: ; 0x021F2AC8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl MOD05_021F2DE8
	add r1, r0, #0
	add r0, r5, #0
	bl MOD05_021F2A98
	add r0, r4, #0
	bl MOD05_021F2DF4
	add r1, r0, #0
	add r0, r5, #0
	bl MOD05_021F2AB0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2A80
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F2AF4
MOD05_021F2AF4: ; 0x021F2AF4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F26F8
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2834
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2974
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F2B10
MOD05_021F2B10: ; 0x021F2B10
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	mov r1, #0
	add r5, r2, #0
	str r1, [sp, #4]
	str r1, [sp]
	add r1, sp, #0
	add r2, sp, #4
	mov r3, #1
	add r7, r0, #0
	bl FUN_020580F4
	cmp r0, #1
	bne _021F2B6A
_021F2B2E:
	cmp r5, #0
	beq _021F2B38
	ldr r0, [sp]
	cmp r5, r0
	beq _021F2B5A
_021F2B38:
	ldr r0, [sp]
	bl FUN_02058458
	add r4, r0, #0
	bl FUN_0205C334
	cmp r0, #1
	bne _021F2B50
	ldr r0, [sp]
	bl FUN_0205C340
	add r4, r0, #0
_021F2B50:
	cmp r4, r6
	bne _021F2B5A
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F2B5A:
	add r0, r7, #0
	add r1, sp, #0
	add r2, sp, #4
	mov r3, #1
	bl FUN_020580F4
	cmp r0, #1
	beq _021F2B2E
_021F2B6A:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F2B70
MOD05_021F2B70: ; 0x021F2B70
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	mov r1, #0
	add r5, r2, #0
	str r1, [sp, #4]
	str r1, [sp]
	add r1, sp, #0
	add r2, sp, #4
	mov r3, #1
	add r7, r0, #0
	bl FUN_020580F4
	cmp r0, #1
	bne _021F2BEE
_021F2B8E:
	cmp r5, #0
	beq _021F2B98
	ldr r0, [sp]
	cmp r5, r0
	beq _021F2BDE
_021F2B98:
	ldr r0, [sp]
	bl FUN_02058458
	add r4, r0, #0
	ldr r0, _021F2BF4 ; =0x0000FFFF
	cmp r4, r0
	beq _021F2BDE
	ldr r0, [sp]
	bl MOD05_021F1DC8
	ldr r0, [r0, #4]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #1
	bne _021F2BDE
	add r0, r4, #0
	bl FUN_0205C334
	cmp r0, #1
	bne _021F2BC8
	ldr r0, [sp]
	bl FUN_0205C340
	add r4, r0, #0
_021F2BC8:
	ldr r0, _021F2BF4 ; =0x0000FFFF
	cmp r4, r0
	beq _021F2BDE
	add r0, r4, #0
	bl MOD05_021F2DE8
	cmp r6, r0
	bne _021F2BDE
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F2BDE:
	add r0, r7, #0
	add r1, sp, #0
	add r2, sp, #4
	mov r3, #1
	bl FUN_020580F4
	cmp r0, #1
	beq _021F2B8E
_021F2BEE:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F2BF4: .word 0x0000FFFF

	thumb_func_start MOD05_021F2BF8
MOD05_021F2BF8: ; 0x021F2BF8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	mov r1, #0
	add r5, r2, #0
	str r1, [sp, #4]
	str r1, [sp]
	add r1, sp, #0
	add r2, sp, #4
	mov r3, #1
	add r7, r0, #0
	bl FUN_020580F4
	cmp r0, #1
	bne _021F2C74
_021F2C16:
	cmp r5, #0
	beq _021F2C20
	ldr r0, [sp]
	cmp r0, r5
	beq _021F2C64
_021F2C20:
	ldr r0, _021F2C7C ; =0x0000FFFF
	cmp r4, r0
	beq _021F2C64
	ldr r0, [sp]
	bl MOD05_021F1DC8
	ldr r0, [r0, #4]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #1
	bne _021F2C64
	ldr r0, [sp]
	bl FUN_02058458
	add r4, r0, #0
	bl FUN_0205C334
	cmp r0, #1
	bne _021F2C4E
	ldr r0, [sp]
	bl FUN_0205C340
	add r4, r0, #0
_021F2C4E:
	ldr r0, _021F2C7C ; =0x0000FFFF
	cmp r4, r0
	beq _021F2C64
	add r0, r4, #0
	bl MOD05_021F2DF4
	cmp r6, r0
	bne _021F2C64
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F2C64:
	add r0, r7, #0
	add r1, sp, #0
	add r2, sp, #4
	mov r3, #1
	bl FUN_020580F4
	cmp r0, #1
	beq _021F2C16
_021F2C74:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F2C7C: .word 0x0000FFFF

	thumb_func_start MOD05_021F2C80
MOD05_021F2C80: ; 0x021F2C80
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	add r6, r0, #0
	add r7, r2, #0
	bl FUN_020583A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD05_021F2DE8
	str r0, [sp]
	ldr r1, [sp]
	add r0, r4, #0
	bl MOD05_021F2A30
	cmp r0, #1
	bne _021F2CC6
	ldr r1, [sp]
	add r0, r6, #0
	add r2, r7, #0
	bl MOD05_021F2B70
	cmp r0, #0
	bne _021F2CC6
	add r0, r4, #0
	add r0, #0xf8
	ldr r0, [r0]
	ldr r1, [sp]
	bl MOD05_021F5A74
	ldr r1, [sp]
	add r0, r4, #0
	bl MOD05_021F26CC
_021F2CC6:
	add r0, r5, #0
	bl MOD05_021F2DF4
	str r0, [sp, #4]
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD05_021F2A58
	cmp r0, #1
	bne _021F2CFC
	ldr r1, [sp, #4]
	add r0, r6, #0
	add r2, r7, #0
	bl MOD05_021F2BF8
	cmp r0, #0
	bne _021F2CFC
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	ldr r1, [sp, #4]
	bl MOD05_021F5A74
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl MOD05_021F2808
_021F2CFC:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021F2A08
	cmp r0, #1
	bne _021F2D3A
	add r0, r6, #0
	add r1, r5, #0
	add r2, r7, #0
	bl MOD05_021F2B10
	cmp r0, #0
	bne _021F2D3A
	add r0, r4, #0
	bl MOD05_021F2D6C
	add r1, r5, #0
	bl FUN_02020FF0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021F2948
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021F3050
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021F3204
_021F2D3A:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F2D40
MOD05_021F2D40: ; 0x021F2D40
	add r0, #0xe0
	str r1, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F2D48
MOD05_021F2D48: ; 0x021F2D48
	add r0, #0xe0
	ldr r0, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F2D50
MOD05_021F2D50: ; 0x021F2D50
	str r1, [r0, #4]
	bx lr

	thumb_func_start MOD05_021F2D54
MOD05_021F2D54: ; 0x021F2D54
	add r0, #0xe8
	ldr r0, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F2D5C
MOD05_021F2D5C: ; 0x021F2D5C
	add r0, #0xec
	ldr r0, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F2D64
MOD05_021F2D64: ; 0x021F2D64
	add r0, #0xf0
	str r1, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F2D6C
MOD05_021F2D6C: ; 0x021F2D6C
	add r0, #0xf0
	ldr r0, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F2D74
MOD05_021F2D74: ; 0x021F2D74
	add r0, #0x60
	bx lr

	thumb_func_start MOD05_021F2D78
MOD05_021F2D78: ; 0x021F2D78
	add r0, #0x20
	bx lr

	thumb_func_start MOD05_021F2D7C
MOD05_021F2D7C: ; 0x021F2D7C
	add r0, #0x40
	bx lr

	thumb_func_start MOD05_021F2D80
MOD05_021F2D80: ; 0x021F2D80
	str r1, [r0, #8]
	bx lr

	thumb_func_start MOD05_021F2D84
MOD05_021F2D84: ; 0x021F2D84
	ldr r0, [r0, #8]
	bx lr

	thumb_func_start MOD05_021F2D88
MOD05_021F2D88: ; 0x021F2D88
	str r1, [r0, #0xc]
	bx lr

	thumb_func_start MOD05_021F2D8C
MOD05_021F2D8C: ; 0x021F2D8C
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start MOD05_021F2D90
MOD05_021F2D90: ; 0x021F2D90
	str r1, [r0, #0x10]
	bx lr

	thumb_func_start MOD05_021F2D94
MOD05_021F2D94: ; 0x021F2D94
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start MOD05_021F2D98
MOD05_021F2D98: ; 0x021F2D98
	str r1, [r0, #0x14]
	bx lr

	thumb_func_start MOD05_021F2D9C
MOD05_021F2D9C: ; 0x021F2D9C
	ldr r0, [r0, #0x14]
	bx lr

	thumb_func_start MOD05_021F2DA0
MOD05_021F2DA0: ; 0x021F2DA0
	str r1, [r0, #0x18]
	bx lr

	thumb_func_start MOD05_021F2DA4
MOD05_021F2DA4: ; 0x021F2DA4
	ldr r0, [r0, #0x18]
	bx lr

	thumb_func_start MOD05_021F2DA8
MOD05_021F2DA8: ; 0x021F2DA8
	str r1, [r0, #0x1c]
	bx lr

	thumb_func_start MOD05_021F2DAC
MOD05_021F2DAC: ; 0x021F2DAC
	ldr r0, [r0, #0x1c]
	bx lr

	thumb_func_start MOD05_021F2DB0
MOD05_021F2DB0: ; 0x021F2DB0
	mov r3, #0x41
	lsl r3, r3, #2
	ldr r0, [r0, r3]
	ldr r3, _021F2DBC ; =MOD05_021F1E2C
	bx r3
	nop
_021F2DBC: .word MOD05_021F1E2C

	thumb_func_start MOD05_021F2DC0
MOD05_021F2DC0: ; 0x021F2DC0
	push {r3, lr}
	ldr r3, _021F2DE0 ; =UNK05_021FAC6C
	ldr r1, _021F2DE4 ; =0x0000FFFF
_021F2DC6:
	ldr r2, [r3]
	cmp r2, r0
	bne _021F2DD0
	add r0, r3, #0
	pop {r3, pc}
_021F2DD0:
	add r3, #0x10
	ldr r2, [r3]
	cmp r2, r1
	bne _021F2DC6
	bl GF_AssertFail
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0
_021F2DE0: .word UNK05_021FAC6C
_021F2DE4: .word 0x0000FFFF

	thumb_func_start MOD05_021F2DE8
MOD05_021F2DE8: ; 0x021F2DE8
	push {r3, lr}
	bl MOD05_021F2DC0
	ldr r0, [r0, #4]
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F2DF4
MOD05_021F2DF4: ; 0x021F2DF4
	push {r3, lr}
	bl MOD05_021F2DC0
	ldr r0, [r0, #8]
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F2E00
MOD05_021F2E00: ; 0x021F2E00
	push {r3, lr}
	bl MOD05_021F2DC0
	ldr r0, [r0, #0xc]
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F2E0C
MOD05_021F2E0C: ; 0x021F2E0C
	push {r3, lr}
	cmp r1, #1
	bne _021F2E1C
	mov r1, #1
	lsl r1, r1, #0x16
	bl FUN_02058410
	pop {r3, pc}
_021F2E1C:
	mov r1, #1
	lsl r1, r1, #0x16
	bl FUN_02058418
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F2E28
MOD05_021F2E28: ; 0x021F2E28
	push {r3, lr}
	mov r1, #1
	lsl r1, r1, #0x16
	bl FUN_02058424
	cmp r0, #0
	beq _021F2E3A
	mov r0, #1
	pop {r3, pc}
_021F2E3A:
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F2E40
MOD05_021F2E40: ; 0x021F2E40
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #4
	add r4, r1, #0
	str r0, [sp, #4]
	add r0, sp, #0
	str r4, [sp]
	bl FUN_0201F1B4
	add r1, r0, #0
	add r0, r5, #0
	bl MOD05_021F2D40
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2D50
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F2E68
MOD05_021F2E68: ; 0x021F2E68
	ldr r3, _021F2E6C ; =FUN_0201F23C
	bx r3
	.balign 4, 0
_021F2E6C: .word FUN_0201F23C

	thumb_func_start MOD05_021F2E70
MOD05_021F2E70: ; 0x021F2E70
	push {r4, lr}
	sub sp, #0x20
	str r0, [sp]
	str r1, [sp, #4]
	ldmia r2!, {r0, r1}
	add r3, sp, #8
	stmia r3!, {r0, r1}
	ldr r0, [r2]
	add r2, sp, #0x14
	str r0, [r3]
	ldr r3, _021F2ECC ; =0UNK05_021FC550
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, sp, #0
	bl FUN_0201F6E8
	add r4, r0, #0
	beq _021F2EC4
	mov r1, #0
	bl FUN_0201F80C
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F830
	add r0, r4, #0
	mov r1, #0
	bl FUN_0201F890
	add r0, r4, #0
	bl FUN_0201F8E0
	mov r1, #1
	bl NNS_G3dMdlSetMdlFogEnableFlagAll
	add r0, r4, #0
	bl FUN_0201F8E0
	bl MOD05_021DB5EC
_021F2EC4:
	add r0, r4, #0
	add sp, #0x20
	pop {r4, pc}
	nop
_021F2ECC: .word UNK05_021FC550

	thumb_func_start MOD05_021F2ED0
MOD05_021F2ED0: ; 0x021F2ED0
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	add r4, r2, #0
	bl MOD05_021F2DE8
	add r1, r0, #0
	add r0, r6, #0
	add r0, #0xf8
	ldr r0, [r0]
	bl MOD05_021F5A90
	str r0, [r4]
	add r0, r5, #0
	bl MOD05_021F2DF4
	add r1, r0, #0
	add r0, r6, #0
	add r0, #0xfc
	ldr r0, [r0]
	bl MOD05_021F5A90
	add r1, r4, #0
	add r1, #0xc
	bl FUN_0202227C
	add r0, r6, #0
	bl MOD05_021F2D6C
	add r1, r5, #0
	bl FUN_02021050
	add r6, r0, #0
	bl FUN_020210AC
	str r0, [r4, #4]
	add r0, r6, #0
	bl FUN_020211AC
	str r0, [r4, #0x1c]
	add r0, r6, #0
	bl FUN_020211BC
	str r0, [r4, #0x20]
	add r0, r6, #0
	bl FUN_020211CC
	str r0, [r4, #0x24]
	add r0, r5, #0
	bl MOD05_021F2E00
	str r0, [r4, #8]
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F2F3C
MOD05_021F2F3C: ; 0x021F2F3C
	push {r3, lr}
	bl FUN_02058578
	bl FUN_020583A0
	pop {r3, pc}

	thumb_func_start MOD05_021F2F48
MOD05_021F2F48: ; 0x021F2F48
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r1, sp, #0
	bl MOD05_021F1E64
	mov r0, #6
	ldr r1, [sp, #8]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, sp, #0
	bl FUN_0201F7C8
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start MOD05_021F2F6C
MOD05_021F2F6C: ; 0x021F2F6C
	push {r4, r5, r6, lr}
	mov r4, #1
	add r6, r1, #0
	lsl r1, r4, #9
	add r5, r0, #0
	bl FUN_0205842C
	cmp r0, #1
	bne _021F2F80
	mov r4, #0
_021F2F80:
	mov r1, #1
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl FUN_0205842C
	cmp r0, #1
	bne _021F2F9E
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl FUN_0205842C
	cmp r0, #0
	bne _021F2F9E
	mov r4, #0
_021F2F9E:
	lsl r1, r4, #0x18
	add r0, r6, #0
	lsr r1, r1, #0x18
	bl FUN_0201F80C
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F2FAC
MOD05_021F2FAC: ; 0x021F2FAC
	lsl r1, r0, #2
	ldr r0, _021F2FB4 ; =UNK05_021FC55C
	ldr r0, [r0, r1]
	bx lr
	.balign 4, 0
_021F2FB4: .word UNK05_021FC55C

	thumb_func_start MOD05_021F2FB8
MOD05_021F2FB8: ; 0x021F2FB8
	lsl r1, r0, #2
	ldr r0, _021F2FC0 ; =UNK05_021FC56C
	ldr r0, [r0, r1]
	bx lr
	.balign 4, 0
_021F2FC0: .word UNK05_021FC56C

	thumb_func_start MOD05_021F2FC4
MOD05_021F2FC4: ; 0x021F2FC4
	lsl r1, r0, #2
	ldr r0, _021F2FCC ; =UNK05_021FC57C
	ldr r0, [r0, r1]
	bx lr
	.balign 4, 0
_021F2FCC: .word UNK05_021FC57C

	thumb_func_start MOD05_021F2FD0
MOD05_021F2FD0: ; 0x021F2FD0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #1
	lsl r0, r0, #8
	ldr r4, [r5, r0]
	mov r0, #4
	add r6, r1, #0
	ldrsh r1, [r4, r0]
	mov r0, #2
	ldrsh r0, [r4, r0]
	add r7, r2, #0
	str r3, [sp]
	cmp r1, r0
	bge _021F2FFA
	add r0, r5, #0
	add r0, #0xe0
	ldr r0, [r0]
	bl FUN_0201F2C0
	cmp r0, #1
	bne _021F302C
_021F2FFA:
	mov r2, #0
	ldrsh r3, [r4, r2]
	ldr r0, [r4, #0xc]
	cmp r3, #0
	ble _021F3024
_021F3004:
	ldr r1, [r0, #0xc]
	cmp r1, #0
	bne _021F301C
	add r5, #0xf0
	ldr r1, [r5]
	str r1, [r0, #0xc]
	ldr r1, [sp]
	str r1, [r0, #8]
	str r6, [r0, #4]
	str r7, [r0]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F301C:
	add r2, r2, #1
	add r0, #0x10
	cmp r2, r3
	blt _021F3004
_021F3024:
	bl GF_AssertFail
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F302C:
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #0
	bl MOD05_021F2DB0
	add r2, r0, #0
	ldr r3, [sp]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD05_021F317C
	mov r0, #4
	ldrsh r0, [r4, r0]
	add r0, r0, #1
	strh r0, [r4, #4]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F3050
MOD05_021F3050: ; 0x021F3050
	push {r3, r4}
	mov r2, #1
	lsl r2, r2, #8
	ldr r0, [r0, r2]
	mov r3, #0
	ldrsh r4, [r0, r3]
	ldr r2, [r0, #0xc]
	cmp r4, #0
	ble _021F307E
_021F3062:
	ldr r0, [r2, #4]
	cmp r0, r1
	bne _021F3076
	ldr r0, [r2, #0xc]
	cmp r0, #0
	beq _021F3076
	mov r0, #0
	str r0, [r2, #0xc]
	pop {r3, r4}
	bx lr
_021F3076:
	add r3, r3, #1
	add r2, #0x10
	cmp r3, r4
	blt _021F3062
_021F307E:
	pop {r3, r4}
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F3084
MOD05_021F3084: ; 0x021F3084
	push {r3, r4}
	mov r2, #1
	lsl r2, r2, #8
	ldr r0, [r0, r2]
	mov r3, #0
	ldrsh r4, [r0, r3]
	ldr r2, [r0, #0xc]
	cmp r4, #0
	ble _021F30BC
_021F3096:
	ldr r0, [r2, #4]
	cmp r0, r1
	bne _021F30B4
	ldr r0, [r2, #0xc]
	cmp r0, #0
	beq _021F30B4
	ldr r0, [r2, #8]
	cmp r0, #0
	bne _021F30AE
	mov r0, #3
	pop {r3, r4}
	bx lr
_021F30AE:
	mov r0, #4
	pop {r3, r4}
	bx lr
_021F30B4:
	add r3, r3, #1
	add r2, #0x10
	cmp r3, r4
	blt _021F3096
_021F30BC:
	mov r0, #0
	pop {r3, r4}
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F30C4
MOD05_021F30C4: ; 0x021F30C4
	push {r3, r4, r5, r6, r7, lr}
	str r1, [sp]
	mov r1, #1
	ldr r0, [sp]
	lsl r1, r1, #8
	ldr r4, [r0, r1]
	add r0, #0xe0
	ldr r0, [r0]
	mov r6, #0
	ldr r5, [r4, #0xc]
	bl FUN_0201F2C0
	cmp r0, #1
	beq _021F3178
	add r7, r4, #4
	b _021F310E
_021F30E4:
	ldr r0, [r5, #0xc]
	cmp r0, #0
	beq _021F310A
	ldr r0, [sp]
	ldr r1, [r5]
	mov r2, #0
	bl MOD05_021F2DB0
	add r2, r0, #0
	ldr r0, [sp]
	ldr r1, [r5, #4]
	ldr r3, [r5, #8]
	bl MOD05_021F317C
	mov r0, #0
	str r0, [r5, #0xc]
	ldrsh r0, [r7, r0]
	add r0, r0, #1
	strh r0, [r7]
_021F310A:
	add r5, #0x10
	add r6, r6, #1
_021F310E:
	mov r0, #4
	ldrsh r1, [r4, r0]
	mov r0, #2
	ldrsh r0, [r4, r0]
	cmp r1, r0
	bge _021F3122
	mov r0, #0
	ldrsh r0, [r4, r0]
	cmp r6, r0
	blt _021F30E4
_021F3122:
	mov r6, #0
	ldrsh r0, [r4, r6]
	ldr r7, [r4, #0xc]
	sub r1, r0, #1
	cmp r1, #0
	ble _021F3174
	add r5, r7, #0
_021F3130:
	ldr r1, [r5, #0xc]
	cmp r1, #0
	bne _021F3166
	add r2, r6, #1
	cmp r2, r0
	bge _021F3166
	lsl r1, r2, #4
	add r3, r7, r1
_021F3140:
	ldr r1, [r3, #0xc]
	cmp r1, #0
	beq _021F315E
	lsl r0, r2, #4
	add r3, r7, r0
	mov ip, r3
	add r2, r5, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	mov r1, #0
	mov r0, ip
	str r1, [r0, #0xc]
	b _021F3166
_021F315E:
	add r2, r2, #1
	add r3, #0x10
	cmp r2, r0
	blt _021F3140
_021F3166:
	mov r0, #0
	ldrsh r0, [r4, r0]
	add r6, r6, #1
	add r5, #0x10
	sub r1, r0, #1
	cmp r6, r1
	blt _021F3130
_021F3174:
	mov r0, #0
	strh r0, [r4, #4]
_021F3178:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F317C
MOD05_021F317C: ; 0x021F317C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	mov r0, #4
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xf0
	add r4, r1, #0
	add r6, r3, #0
	add r1, r2, #0
	ldr r0, [r0]
	add r2, r4, #0
	mov r3, #1
	bl FUN_02020F54
	cmp r0, #0
	bne _021F31A2
	bl GF_AssertFail
_021F31A2:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F31C8
	cmp r6, #0
	bne _021F31BA
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F28A0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_021F31BA:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F2914
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F31C8
MOD05_021F31C8: ; 0x021F31C8
	push {r4, r5, r6, lr}
	mov r3, #1
	lsl r3, r3, #8
	ldr r3, [r0, r3]
	mov r5, #1
	ldr r4, [r3, #0x10]
	mov r2, #0
	strh r5, [r3, #6]
	ldrsh r6, [r3, r2]
	cmp r6, #0
	ble _021F31FC
_021F31DE:
	ldr r5, [r4, #8]
	cmp r5, #0
	bne _021F31F4
	add r0, #0xf0
	ldr r0, [r0]
	str r0, [r4, #8]
	str r1, [r4, #4]
	mov r0, #0
	str r0, [r4]
	strh r0, [r3, #6]
	pop {r4, r5, r6, pc}
_021F31F4:
	add r2, r2, #1
	add r4, #0xc
	cmp r2, r6
	blt _021F31DE
_021F31FC:
	bl GF_AssertFail
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F3204
MOD05_021F3204: ; 0x021F3204
	push {r4, r5}
	mov r2, #1
	lsl r2, r2, #8
	ldr r2, [r0, r2]
	mov r0, #1
	ldr r4, [r2, #0x10]
	mov r3, #0
	strh r0, [r2, #6]
	ldrsh r5, [r2, r3]
	cmp r5, #0
	ble _021F3236
_021F321A:
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021F322E
	ldr r0, [r4, #4]
	cmp r0, r1
	bne _021F322E
	mov r0, #0
	str r0, [r4, #8]
	str r0, [r4]
	b _021F3236
_021F322E:
	add r3, r3, #1
	add r4, #0xc
	cmp r3, r5
	blt _021F321A
_021F3236:
	mov r0, #0
	strh r0, [r2, #6]
	pop {r4, r5}
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F3240
MOD05_021F3240: ; 0x021F3240
	push {r3, r4, r5, r6, r7, lr}
	mov r0, #1
	lsl r0, r0, #8
	ldr r6, [r1, r0]
	ldrh r0, [r6, #6]
	cmp r0, #1
	beq _021F327A
	mov r4, #0
	ldrsh r0, [r6, r4]
	ldr r5, [r6, #0x10]
	cmp r0, #0
	ble _021F327A
	mov r7, #1
_021F325A:
	ldr r0, [r5]
	cmp r0, #0
	bne _021F326E
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _021F326E
	ldr r1, [r5, #4]
	bl FUN_020210F0
	str r7, [r5]
_021F326E:
	mov r0, #0
	ldrsh r0, [r6, r0]
	add r4, r4, #1
	add r5, #0xc
	cmp r4, r0
	blt _021F325A
_021F327A:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F327C
MOD05_021F327C: ; 0x021F327C
	push {r3, r4, r5, r6, r7, lr}
	mov r0, #1
	lsl r0, r0, #8
	ldr r6, [r1, r0]
	mov r4, #0
	ldr r5, [r6, #0x10]
	mov r0, #1
	strh r0, [r6, #6]
	ldrsh r0, [r6, r4]
	cmp r0, #0
	ble _021F32B6
	add r7, r4, #0
_021F3294:
	ldr r0, [r5]
	cmp r0, #1
	bne _021F32AA
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _021F32AA
	ldr r1, [r5, #4]
	bl FUN_02021158
	str r7, [r5]
	str r7, [r5, #8]
_021F32AA:
	mov r0, #0
	ldrsh r0, [r6, r0]
	add r4, r4, #1
	add r5, #0xc
	cmp r4, r0
	blt _021F3294
_021F32B6:
	mov r0, #0
	strh r0, [r6, #6]
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F32BC
MOD05_021F32BC: ; 0x021F32BC
	push {r4, r5, r6, lr}
	mov r5, #1
	lsl r5, r5, #8
	ldr r5, [r0, r5]
	mov r4, #0
	ldrsh r6, [r5, r4]
	ldr r0, [r5, #8]
	cmp r6, #0
	ble _021F32F2
_021F32CE:
	ldr r5, [r0, #4]
	cmp r5, #0
	bne _021F32EA
	str r1, [r0, #4]
	str r2, [r0, #8]
	str r3, [r0]
	ldr r0, [r0, #8]
	mov r2, #0
	str r2, [r0]
	add r0, r1, #0
	mov r1, #1
	bl MOD05_021F2E0C
	pop {r4, r5, r6, pc}
_021F32EA:
	add r4, r4, #1
	add r0, #0xc
	cmp r4, r6
	blt _021F32CE
_021F32F2:
	bl GF_AssertFail
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F32F8
MOD05_021F32F8: ; 0x021F32F8
	push {r3, r4}
	mov r2, #1
	lsl r2, r2, #8
	ldr r0, [r0, r2]
	mov r3, #0
	ldrsh r4, [r0, r3]
	ldr r2, [r0, #8]
	cmp r4, #0
	ble _021F3322
_021F330A:
	ldr r0, [r2, #4]
	cmp r0, r1
	bne _021F331A
	mov r0, #0
	str r0, [r2, #4]
	str r0, [r2, #8]
	pop {r3, r4}
	bx lr
_021F331A:
	add r3, r3, #1
	add r2, #0xc
	cmp r3, r4
	blt _021F330A
_021F3322:
	pop {r3, r4}
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F3328
MOD05_021F3328: ; 0x021F3328
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r0, #1
	lsl r0, r0, #8
	ldr r6, [r7, r0]
	mov r4, #0
	ldrsh r0, [r6, r4]
	ldr r5, [r6, #8]
	cmp r0, #0
	ble _021F3356
_021F333C:
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _021F334A
	add r0, r7, #0
	add r1, r5, #0
	bl MOD05_021F3364
_021F334A:
	mov r0, #0
	ldrsh r0, [r6, r0]
	add r4, r4, #1
	add r5, #0xc
	cmp r4, r0
	blt _021F333C
_021F3356:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F3358
MOD05_021F3358: ; 0x021F3358
	ldr r3, _021F3360 ; =MOD05_021F3328
	add r0, r1, #0
	bx r3
	nop
_021F3360: .word MOD05_021F3328

	thumb_func_start MOD05_021F3364
MOD05_021F3364: ; 0x021F3364
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4]
	bl MOD05_021F2A08
	cmp r0, #2
	beq _021F33B2
	ldr r0, [r4, #4]
	ldr r1, [r4]
	bl MOD05_021F1FE0
	ldr r1, [r4, #8]
	str r0, [r1]
	ldr r0, [r4, #8]
	ldr r0, [r0]
	cmp r0, #0
	bne _021F338A
	bl GF_AssertFail
_021F338A:
	ldr r0, [r4, #4]
	mov r1, #0
	bl MOD05_021F2E0C
	mov r1, #2
	ldr r0, [r4, #4]
	lsl r1, r1, #0x14
	bl FUN_0205842C
	cmp r0, #1
	ldr r0, [r4, #4]
	bne _021F33A8
	bl FUN_020586DC
	b _021F33AC
_021F33A8:
	bl FUN_020586A0
_021F33AC:
	mov r0, #0
	str r0, [r4, #4]
	str r0, [r4, #8]
_021F33B2:
	pop {r4, pc}

	thumb_func_start MOD05_021F33B4
MOD05_021F33B4: ; 0x021F33B4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r1, #0
	add r5, r0, #0
	mov r0, #0xc
	add r7, r6, #0
	mul r7, r0
	lsl r0, r6, #4
	lsl r1, r7, #1
	str r0, [sp, #4]
	add r0, r1, r0
	str r0, [sp, #8]
	add r0, #0x28
	str r0, [sp, #8]
	ldr r1, [sp, #8]
	mov r0, #4
	str r2, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	bne _021F33E2
	bl GF_AssertFail
_021F33E2:
	ldr r2, [sp, #8]
	add r0, r4, #0
	mov r1, #0
	bl memset
	ldr r0, [sp]
	strh r6, [r4]
	strh r0, [r4, #2]
	add r0, r4, #0
	add r0, #0x28
	str r0, [r4, #8]
	add r1, r0, r7
	ldr r0, [sp, #4]
	str r1, [r4, #0xc]
	add r0, r1, r0
	str r0, [r4, #0x10]
	mov r0, #1
	lsl r0, r0, #8
	str r4, [r5, r0]
	add r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_0205839C
	add r6, r0, #0
	ldr r0, _021F3448 ; =MOD05_021F30C4
	add r1, r5, #0
	add r2, r6, #1
	bl FUN_0200CA44
	str r0, [r4, #0x18]
	ldr r0, _021F344C ; =MOD05_021F3358
	add r1, r5, #0
	add r2, r6, #2
	bl FUN_0200CA44
	str r0, [r4, #0x1c]
	ldr r0, _021F3450 ; =MOD05_021F3240
	add r1, r5, #0
	mov r2, #0xff
	bl FUN_0200CA60
	str r0, [r4, #0x20]
	ldr r0, _021F3454 ; =MOD05_021F327C
	add r1, r5, #0
	mov r2, #0xff
	bl FUN_0200CA98
	str r0, [r4, #0x24]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_021F3448: .word MOD05_021F30C4
_021F344C: .word MOD05_021F3358
_021F3450: .word MOD05_021F3240
_021F3454: .word MOD05_021F327C

	thumb_func_start MOD05_021F3458
MOD05_021F3458: ; 0x021F3458
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #1
	lsl r0, r0, #8
	ldr r4, [r5, r0]
	mov r0, #1
	strh r0, [r4, #6]
	ldr r0, [r4, #0x18]
	bl FUN_0200CAB4
	ldr r0, [r4, #0x1c]
	bl FUN_0200CAB4
	ldr r0, [r4, #0x20]
	bl FUN_0200CAB4
	ldr r0, [r4, #0x24]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	mov r1, #0
	lsl r0, r0, #8
	str r1, [r5, r0]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F3490
MOD05_021F3490: ; 0x021F3490
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021F2E28
	cmp r0, #1
	beq _021F34A8
	add r0, r5, #0
	bl MOD05_021F0514
	cmp r0, #0
	bne _021F34D2
_021F34A8:
	add r0, r5, #0
	bl FUN_02058458
	add r6, r0, #0
	add r0, r5, #0
	bl FUN_02058578
	add r7, r0, #0
	add r0, r5, #0
	bl FUN_020576A8
	add r0, r7, #0
	add r1, r6, #0
	add r2, r5, #0
	bl MOD05_021F2C80
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02057614
	pop {r3, r4, r5, r6, r7, pc}
_021F34D2:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F34DC
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F34DC
MOD05_021F34DC: ; 0x021F34DC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r7, r0, #0
	str r1, [sp, #8]
	bl MOD05_021F2F3C
	str r0, [sp, #0x18]
	bl MOD05_021F2D48
	str r0, [sp, #0x14]
	add r0, r7, #0
	bl MOD05_021F0514
	str r0, [sp, #0x10]
	mov r0, #4
	mov r1, #0x58
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #0x58
	add r5, r0, #0
	bl memset
	ldr r0, [sp, #8]
	str r0, [r5]
	add r0, r7, #0
	str r7, [r5, #0x50]
	bl FUN_02058458
	add r6, r0, #0
	bl MOD05_021F2DE8
	ldr r4, _021F36C4 ; =UNK05_021F9094
	ldr r2, _021F36C8 ; =0x0000FFFF
_021F3520:
	ldr r1, [r4]
	cmp r1, r0
	beq _021F352E
	add r4, #8
	ldr r1, [r4]
	cmp r1, r2
	bne _021F3520
_021F352E:
	ldr r0, _021F36C8 ; =0x0000FFFF
	cmp r1, r0
	bne _021F3538
	bl GF_AssertFail
_021F3538:
	ldr r0, [sp, #0x18]
	ldr r1, [r4, #4]
	mov r2, #0
	bl MOD05_021F2DB0
	str r0, [r5, #8]
	add r0, r6, #0
	bl MOD05_021F2DF4
	ldr r4, _021F36CC ; =UNK05_021F90E4
	ldr r2, _021F36C8 ; =0x0000FFFF
_021F354E:
	ldr r1, [r4]
	cmp r1, r0
	beq _021F355C
	add r4, #8
	ldr r1, [r4]
	cmp r1, r2
	bne _021F354E
_021F355C:
	ldr r0, _021F36C8 ; =0x0000FFFF
	cmp r1, r0
	bne _021F3566
	bl GF_AssertFail
_021F3566:
	ldr r0, [sp, #0x18]
	ldr r1, [r4, #4]
	mov r2, #0
	bl MOD05_021F2DB0
	add r1, r5, #0
	add r1, #0x14
	str r0, [r5, #0xc]
	bl FUN_0202227C
	ldr r4, _021F36D0 ; =UNK05_021FA0AC
	ldr r0, _021F36C8 ; =0x0000FFFF
_021F357E:
	ldr r1, [r4]
	cmp r1, r6
	beq _021F358C
	add r4, #8
	ldr r1, [r4]
	cmp r1, r0
	bne _021F357E
_021F358C:
	ldr r0, _021F36C8 ; =0x0000FFFF
	cmp r1, r0
	bne _021F3596
	bl GF_AssertFail
_021F3596:
	ldr r0, [sp, #0x18]
	ldr r1, [r4, #4]
	mov r2, #0
	bl MOD05_021F2DB0
	str r0, [r5, #0x10]
	bl NNS_G3dGetTex
	add r4, r0, #0
	add r0, r6, #0
	bl MOD05_021F2E00
	add r3, r0, #0
	add r0, r5, #0
	add r0, #0x14
	str r0, [sp]
	add r0, r5, #0
	ldr r1, [r5, #8]
	add r0, #0x28
	add r2, r4, #0
	bl FUN_0201F7A4
	ldr r0, [sp, #0x10]
	bl FUN_0201F7E0
	add r3, r0, #0
	add r2, sp, #0x28
	ldmia r3!, {r0, r1}
	add r4, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r5, #0
	str r0, [r2]
	ldr r0, [sp, #0x14]
	add r1, #0x28
	add r2, r4, #0
	bl MOD05_021F2E70
	str r0, [r5, #0x24]
	cmp r0, #0
	bne _021F35EC
	bl GF_AssertFail
_021F35EC:
	ldr r0, [sp, #0x10]
	bl FUN_0201F844
	add r1, r0, #0
	ldr r0, [r5, #0x24]
	bl FUN_0201F830
	ldr r0, [sp, #0x10]
	bl FUN_0201F8C0
	add r1, r0, #0
	ldr r0, [r5, #0x24]
	bl FUN_0201F890
	ldr r0, [sp, #0x10]
	bl FUN_0201F880
	add r1, r0, #0
	ldr r0, [r5, #0x24]
	bl FUN_0201F86C
	ldr r0, [r5, #0x24]
	mov r1, #0
	bl FUN_0201F854
	ldr r0, [r5, #0x24]
	mov r1, #1
	bl FUN_0201F80C
	ldr r0, [r5, #0x24]
	bl FUN_0201F8F0
	add r0, r7, #0
	bl FUN_02058A9C
	cmp r0, #1
	bne _021F367A
	add r0, r7, #0
	mov r1, #2
	bl FUN_0205829C
	str r0, [sp, #0xc]
	add r0, r7, #0
	mov r1, #1
	bl FUN_02059C90
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r4, #0
	bl FUN_02054AF0
	cmp r0, #0
	bne _021F3658
	mov r4, #1
_021F3658:
	add r0, r7, #0
	add r1, sp, #0x1c
	bl FUN_02058B5C
	add r0, r7, #0
	bl MOD05_021E4C24
	ldr r1, [sp, #0xc]
	str r4, [sp]
	str r1, [sp, #4]
	add r1, r5, #0
	ldr r2, [r5, #0x24]
	add r1, #0x28
	add r3, sp, #0x1c
	bl MOD06_02249B7C
	str r0, [r5, #0x54]
_021F367A:
	add r0, r7, #0
	bl FUN_020576A8
	mov r1, #0x41
	ldr r0, [sp, #0x18]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD05_021F2C80
	ldr r1, [sp, #8]
	add r0, r7, #0
	bl FUN_02057614
	mov r1, #0x41
	ldr r0, [sp, #0x18]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bl FUN_0205839C
	ldr r0, _021F36D4 ; =MOD05_021F36D8
	add r1, r5, #0
	mov r2, #0xff
	bl FUN_0200CA98
	add r4, r0, #0
	bne _021F36B6
	bl GF_AssertFail
_021F36B6:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021F36D8
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	nop
_021F36C4: .word UNK05_021F9094
_021F36C8: .word 0x0000FFFF
_021F36CC: .word UNK05_021F90E4
_021F36D0: .word UNK05_021FA0AC
_021F36D4: .word MOD05_021F36D8

	thumb_func_start MOD05_021F36D8
MOD05_021F36D8: ; 0x021F36D8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5, #4]
	ldr r4, [r5, #0x50]
	cmp r0, #0
	beq _021F36EC
	cmp r0, #1
	beq _021F3744
	pop {r4, r5, r6, pc}
_021F36EC:
	add r0, r4, #0
	bl FUN_02058830
	cmp r0, #0
	beq _021F3700
	add r0, r4, #0
	bl MOD05_021F2E28
	cmp r0, #0
	bne _021F3730
_021F3700:
	ldr r0, [r5, #0x54]
	cmp r0, #0
	beq _021F370A
	bl FUN_02064520
_021F370A:
	ldr r0, [r5, #0x24]
	bl FUN_0201F744
	ldr r0, [r5, #8]
	bl FreeToHeap
	ldr r0, [r5, #0xc]
	bl FreeToHeap
	ldr r0, [r5, #0x10]
	bl FreeToHeap
	add r0, r5, #0
	bl FreeToHeap
	add r0, r6, #0
	bl FUN_0200CAB4
	pop {r4, r5, r6, pc}
_021F3730:
	add r0, r4, #0
	bl FUN_02058458
	ldr r1, [r5]
	cmp r1, r0
	beq _021F377C
	ldr r0, [r5, #4]
	add r0, r0, #1
	str r0, [r5, #4]
	pop {r4, r5, r6, pc}
_021F3744:
	add r0, r4, #0
	bl MOD05_021F2E28
	cmp r0, #0
	bne _021F377C
	ldr r0, [r5, #0x54]
	cmp r0, #0
	beq _021F3758
	bl FUN_02064520
_021F3758:
	ldr r0, [r5, #0x24]
	bl FUN_0201F744
	ldr r0, [r5, #8]
	bl FreeToHeap
	ldr r0, [r5, #0xc]
	bl FreeToHeap
	ldr r0, [r5, #0x10]
	bl FreeToHeap
	add r0, r5, #0
	bl FreeToHeap
	add r0, r6, #0
	bl FUN_0200CAB4
_021F377C:
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F3780
MOD05_021F3780: ; 0x021F3780
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	bl MOD05_021F37AC
	add r4, r0, #0
	str r6, [r4]
	str r5, [r4, #8]
	bl MOD05_021F37DC
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F379C
MOD05_021F379C: ; 0x021F379C
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021F37E0
	add r0, r4, #0
	bl MOD05_021F37D0
	pop {r4, pc}

	thumb_func_start MOD05_021F37AC
MOD05_021F37AC: ; 0x021F37AC
	push {r4, lr}
	mov r1, #0x10
	bl AllocFromHeap
	add r4, r0, #0
	bne _021F37BC
	bl GF_AssertFail
_021F37BC:
	add r2, r4, #0
	mov r1, #0x10
	mov r0, #0
_021F37C2:
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _021F37C2
	add r0, r4, #0
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F37D0
MOD05_021F37D0: ; 0x021F37D0
	ldr r3, _021F37D8 ; =FreeToHeapExplicit
	add r1, r0, #0
	ldr r0, [r1]
	bx r3
	.balign 4, 0
_021F37D8: .word FreeToHeapExplicit

	thumb_func_start MOD05_021F37DC
MOD05_021F37DC: ; 0x021F37DC
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F37E0
MOD05_021F37E0: ; 0x021F37E0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _021F380E
	ldr r4, [r5, #0xc]
	cmp r4, #0
	beq _021F380E
_021F37F0:
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	beq _021F37FC
	add r0, r4, #0
	bl MOD05_021F383C
_021F37FC:
	ldr r0, [r5, #4]
	add r4, #0x60
	sub r0, r0, #1
	str r0, [r5, #4]
	bne _021F37F0
	ldr r0, [r5]
	ldr r1, [r5, #0xc]
	bl FreeToHeapExplicit
_021F380E:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F3810
MOD05_021F3810: ; 0x021F3810
	push {r3, r4, r5, lr}
	add r4, r0, #0
	str r1, [r4, #4]
	mov r0, #0x60
	add r5, r1, #0
	mul r5, r0
	ldr r0, [r4]
	add r1, r5, #0
	bl AllocFromHeap
	str r0, [r4, #0xc]
	cmp r0, #0
	bne _021F382E
	bl GF_AssertFail
_021F382E:
	ldr r0, [r4, #0xc]
	mov r1, #0
	add r2, r5, #0
	bl memset
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F383C
MOD05_021F383C: ; 0x021F383C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x5c]
	bl FreeToHeap
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x60
	bl memset
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F3854
MOD05_021F3854: ; 0x021F3854
	mov r0, #0
	str r0, [r2]
	str r0, [r2, #4]
	bx lr

	thumb_func_start MOD05_021F385C
MOD05_021F385C: ; 0x021F385C
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F3860
MOD05_021F3860: ; 0x021F3860
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x38]
	add r4, r2, #0
	bl FUN_02055320
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl FUN_0205532C
	add r7, r0, #0
	ldr r0, [r4]
	cmp r0, r6
	bne _021F3882
	ldr r0, [r4, #4]
	cmp r0, r7
	beq _021F38B4
_021F3882:
	str r6, [r4]
	add r0, r5, #0
	add r1, r6, #0
	add r2, r7, #0
	str r7, [r4, #4]
	bl FUN_0204A6E0
	add r4, r0, #0
	bl FUN_02054A18
	cmp r0, #0
	beq _021F389E
	mov r2, #0
	b _021F38AA
_021F389E:
	add r0, r4, #0
	bl FUN_02054A0C
	cmp r0, #0
	beq _021F38B4
	mov r2, #1
_021F38AA:
	add r0, r6, #0
	add r1, r7, #0
	add r3, r5, #0
	bl MOD05_021DAFA8
_021F38B4:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F38B8
MOD05_021F38B8: ; 0x021F38B8
	ldr r0, [r0, #4]
	ldr r3, _021F38C4 ; =MOD05_021D8024
	ldr r0, [r0, #4]
	ldr r1, _021F38C8 ; =UNK05_021FC58C
	bx r3
	nop
_021F38C4: .word MOD05_021D8024
_021F38C8: .word UNK05_021FC58C

	thumb_func_start MOD05_021F38CC
MOD05_021F38CC: ; 0x021F38CC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	mov r1, #0
	add r2, r1, #0
	add r5, r0, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r5, #0
	mov r1, #0x46
	mov r2, #0
	bl GetMonData
	mov r1, #0xf
	and r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	add r0, r5, #0
	mov r1, #0x47
	mov r2, #0
	bl GetMonData
	mov r1, #0xf
	and r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #0x48
	mov r2, #0
	bl GetMonData
	mov r1, #0xf
	and r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0x49
	mov r2, #0
	bl GetMonData
	mov r1, #0xf
	and r0, r1
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	add r0, r5, #0
	mov r1, #0x4a
	mov r2, #0
	bl GetMonData
	mov r1, #0xf
	and r0, r1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r5, #0
	mov r1, #0x4b
	mov r2, #0
	bl GetMonData
	mov r1, #0xf
	and r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	eor r0, r6
	asr r1, r4, #8
	mul r0, r7
	eor r0, r1
	lsl r1, r4, #0x18
	lsr r3, r1, #0x18
	lsl r0, r0, #0x10
	ldr r2, [sp, #4]
	ldr r1, [sp]
	lsr r0, r0, #0x10
	eor r2, r1
	ldr r1, [sp, #8]
	mul r2, r1
	add r1, r3, #0
	eor r1, r2
	lsl r1, r1, #0x10
	lsr r1, r1, #8
	add r0, r0, r1
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F3978
MOD05_021F3978: ; 0x021F3978
	ldr r2, _021F399C ; =UNK05_021FC5A4
	mov r3, #1
_021F397C:
	lsl r1, r3, #3
	add r1, r2, r1
	ldrh r1, [r1, #4]
	cmp r0, r1
	bhs _021F398E
	sub r0, r3, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_021F398E:
	add r1, r3, #1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, #0xf
	blo _021F397C
	add r0, r3, #0
	bx lr
	.balign 4, 0
_021F399C: .word UNK05_021FC5A4

	thumb_func_start MOD05_021F39A0
MOD05_021F39A0: ; 0x021F39A0
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r0, #4
	add r5, r1, #0
	bl FUN_02087A6C
	add r4, r0, #0
	bl FUN_02087A84
	add r0, r4, #0
	mov r1, #0
	mov r2, #4
	bl FUN_02087A98
	add r0, r4, #0
	add r1, r6, #0
	bl FUN_02087B58
	add r6, r0, #0
	add r0, r4, #0
	bl FUN_02087B0C
	add r0, r5, #0
	bl MOD05_021F3978
	lsl r4, r0, #3
	ldr r0, _021F3A0C ; =UNK05_021FC5A8
	ldr r2, _021F3A10 ; =UNK05_021FC5A6
	ldrh r0, [r0, r4]
	ldrh r2, [r2, r4]
	asr r1, r5, #0x1f
	mov r3, #0
	sub r0, r5, r0
	sbc r1, r3
	bl _ll_udiv
	add r2, r0, #0
	add r0, r6, #0
	ldr r6, _021F3A14 ; =UNK05_021FC5A4
	add r3, r1, #0
	mov r5, #0
	ldrh r4, [r6, r4]
	add r1, r5, #0
	add r2, r4, r2
	adc r5, r3
	add r3, r5, #0
	bl _ll_mul
	mov r2, #0xa
	mov r3, #0
	bl _ll_udiv
	pop {r4, r5, r6, pc}
	nop
_021F3A0C: .word UNK05_021FC5A8
_021F3A10: .word UNK05_021FC5A6
_021F3A14: .word UNK05_021FC5A4

	thumb_func_start MOD05_021F3A18
MOD05_021F3A18: ; 0x021F3A18
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	add r5, r1, #0
	bl SavArray_PlayerParty_get
	add r1, r5, #0
	bl GetPartyMonByIndex
	mov r1, #5
	mov r2, #0
	str r0, [sp]
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	ldr r0, [sp]
	bl MOD05_021F38CC
	add r1, sp, #4
	strh r0, [r1, #2]
	ldrh r1, [r1, #2]
	add r0, r5, #0
	bl MOD05_021F39A0
	add r6, r0, #0
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F3E8
	add r1, sp, #4
	strh r0, [r1]
	ldrh r1, [r1]
	add r0, r5, #0
	bl MOD05_021F39A0
	add r7, r0, #0
	mov r0, #0xfa
	lsl r0, r0, #2
	mul r0, r6
	mov r1, #0xfe
	bl _u32_div_f
	add r0, r0, #5
	mov r1, #0xa
	bl _u32_div_f
	add r5, r0, #0
	mov r0, #0xfa
	lsl r0, r0, #2
	mul r0, r7
	mov r1, #0xfe
	bl _u32_div_f
	add r0, r0, #5
	mov r1, #0xa
	bl _u32_div_f
	cmp r5, r0
	bne _021F3A9A
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F3A9A:
	cmp r5, r0
	bls _021F3AAE
	ldr r2, [sp]
	add r0, r4, #0
	add r1, r6, #0
	bl FUN_020619C0
	add sp, #8
	mov r0, #2
	pop {r3, r4, r5, r6, r7, pc}
_021F3AAE:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F3AB4
MOD05_021F3AB4: ; 0x021F3AB4
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	add r5, r1, #0
	bl SavArray_PlayerParty_get
	add r1, r5, #0
	bl GetPartyMonByIndex
	bl MOD05_021F38CC
	add r1, sp, #0
	strh r0, [r1]
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	add r1, sp, #0
	ldrh r1, [r1]
	bl FUN_0205F3F8
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F3AE0
MOD05_021F3AE0: ; 0x021F3AE0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	mov r1, #0xf
	add r7, r2, #0
	add r4, r3, #0
	bl FUN_02039438
	add r1, sp, #0x10
	add r5, r0, #0
	ldrh r1, [r1, #0x10]
	add r0, r4, #0
	bl MOD05_021F39A0
	mov r1, #0xfa
	lsl r1, r1, #2
	mul r1, r0
	add r0, r1, #0
	mov r1, #0xfe
	bl _u32_div_f
	add r0, r0, #5
	mov r1, #0xa
	bl _u32_div_f
	mov r1, #0xa
	add r4, r0, #0
	bl _u32_div_f
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5]
	add r1, r6, #0
	mov r3, #3
	bl BufferIntegerAsString
	add r0, r4, #0
	mov r1, #0xa
	bl _u32_div_f
	mov r0, #0
	add r2, r1, #0
	str r0, [sp]
	mov r3, #1
	str r3, [sp, #4]
	ldr r0, [r5]
	add r1, r7, #0
	bl BufferIntegerAsString
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F3B4C
MOD05_021F3B4C: ; 0x021F3B4C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl SavArray_Flags_get
	bl FUN_0205F3E8
	add r1, sp, #4
	strh r0, [r1]
	ldrh r0, [r1]
	add r1, r4, #0
	add r2, r6, #0
	str r0, [sp]
	add r0, r5, #0
	add r3, r7, #0
	bl MOD05_021F3AE0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F3B7C
MOD05_021F3B7C: ; 0x021F3B7C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	str r2, [sp, #4]
	ldr r0, [r5, #0xc]
	add r4, r3, #0
	add r7, r1, #0
	bl SavArray_PlayerParty_get
	add r1, r4, #0
	bl GetPartyMonByIndex
	mov r1, #5
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r6, #0
	bl MOD05_021F38CC
	add r1, sp, #8
	strh r0, [r1]
	ldrh r0, [r1]
	add r1, r7, #0
	add r3, r4, #0
	str r0, [sp]
	ldr r2, [sp, #4]
	add r0, r5, #0
	bl MOD05_021F3AE0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F3BC0
MOD05_021F3BC0: ; 0x021F3BC0
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r0, #4
	mov r1, #0x20
	bl AllocFromHeap
	add r5, r0, #0
	mov r4, #0
_021F3BD0:
	mov r1, #0xf
	lsl r1, r1, #0xc
	add r2, r4, #0
	mul r2, r1
	ldr r1, _021F3C2C ; =UNK05_021FD684
	lsl r0, r4, #2
	add r1, r1, r2
	add r6, r5, r0
	str r1, [r5, r0]
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _021F3BEC
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F3BEC:
	cmp r7, #0
	beq _021F3C0A
	mov r1, #9
	mov r0, #4
	lsl r1, r1, #0xc
	bl AllocFromHeap
	str r0, [r6, #0x10]
	cmp r0, #0
	bne _021F3C04
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F3C04:
	mov r2, #9
	lsl r2, r2, #0xc
	b _021F3C10
_021F3C0A:
	mov r0, #0
	str r0, [r6, #0x10]
	add r2, r0, #0
_021F3C10:
	mov r1, #0xf
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r3, r5, #0
	bl MOD05_021F3C74
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021F3BD0
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F3C2C: .word UNK05_021FD684

	thumb_func_start MOD05_021F3C30
MOD05_021F3C30: ; 0x021F3C30
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	add r6, r0, #0
	add r7, r4, #0
_021F3C38:
	lsl r0, r4, #2
	add r5, r6, r0
	str r7, [r6, r0]
	ldr r0, [r5, #0x10]
	cmp r0, #0
	beq _021F3C4C
	bl FreeToHeap
	mov r0, #0
	str r0, [r5, #0x10]
_021F3C4C:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021F3C38
	add r0, r6, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F3C60
MOD05_021F3C60: ; 0x021F3C60
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	str r0, [r2]
	bx lr

	thumb_func_start MOD05_021F3C68
MOD05_021F3C68: ; 0x021F3C68
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #0x10]
	str r0, [r2]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F3C74
MOD05_021F3C74: ; 0x021F3C74
	push {r3, r4, r5, r6, r7, lr}
	add r5, r3, #0
	lsl r4, r0, #2
	add r6, r1, #0
	add r7, r2, #0
	ldr r0, [r5, r4]
	mov r1, #0
	add r2, r6, #0
	bl MI_CpuFill8
	add r0, r5, r4
	ldr r0, [r0, #0x10]
	mov r1, #0
	add r2, r7, #0
	bl MI_CpuFill8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F3C98
MOD05_021F3C98: ; 0x021F3C98
	push {r4, r5, r6, r7}
	add r4, r0, #0
	add r3, r2, #0
	mov r5, #0xc
	add r2, r1, #0
	ldr r0, [r4, #4]
	mul r2, r5
	ldrh r0, [r0, r2]
	ldr r6, [r4, #0x10]
	add r1, r0, #0
	mul r1, r5
	add r7, r6, r1
	ldmia r7!, {r0, r1}
	add r6, r3, #0
	stmia r6!, {r0, r1}
	ldr r0, [r7]
	str r0, [r6]
	ldr r1, [r4, #4]
	ldr r0, [r4, #0x10]
	add r1, r1, r2
	ldrh r1, [r1, #2]
	add r6, r1, #0
	mul r6, r5
	add r7, r0, r6
	add r6, r3, #0
	ldmia r7!, {r0, r1}
	add r6, #0xc
	stmia r6!, {r0, r1}
	ldr r0, [r7]
	add r3, #0x18
	str r0, [r6]
	ldr r1, [r4, #4]
	ldr r0, [r4, #0x10]
	add r1, r1, r2
	ldrh r1, [r1, #4]
	add r2, r1, #0
	mul r2, r5
	add r2, r0, r2
	ldmia r2!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r2]
	str r0, [r3]
	pop {r4, r5, r6, r7}
	bx lr

	thumb_func_start MOD05_021F3CF0
MOD05_021F3CF0: ; 0x021F3CF0
	push {r4, r5}
	ldr r3, [r0, #0x14]
	ldr r5, [r0, #4]
	mov r0, #0xc
	add r4, r1, #0
	mul r4, r0
	add r1, r5, r4
	ldrh r1, [r1, #6]
	mul r0, r1
	add r3, r3, r0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	pop {r4, r5}
	bx lr

	thumb_func_start MOD05_021F3D10
MOD05_021F3D10: ; 0x021F3D10
	mov r3, #0
	add r2, r3, #0
	sub r1, r3, #1
_021F3D16:
	str r2, [r0]
	str r1, [r0, #4]
	str r1, [r0, #8]
	add r3, r3, #1
	add r0, #0xc
	cmp r3, #0xa
	blt _021F3D16
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F3D28
MOD05_021F3D28: ; 0x021F3D28
	push {r4, r5, r6, r7}
	add r4, r0, #0
	add r0, r2, #0
	mov ip, r3
	cmp r1, #0
	bne _021F3D3A
	mov r0, #0
	pop {r4, r5, r6, r7}
	bx lr
_021F3D3A:
	cmp r1, #1
	bne _021F3D4A
	mov r1, #0
	mov r0, ip
	strh r1, [r0]
	mov r0, #1
	pop {r4, r5, r6, r7}
	bx lr
_021F3D4A:
	sub r5, r1, #1
	lsr r1, r5, #0x1f
	add r1, r5, r1
	mov r3, #0
	asr r6, r1, #1
	mov r7, #0xa
_021F3D56:
	add r1, r6, #0
	mul r1, r7
	add r2, r4, r1
	ldrh r1, [r2, #4]
	ldrh r2, [r2, #2]
	lsl r1, r1, #0x10
	orr r1, r2
	cmp r1, r0
	ble _021F3D84
	sub r1, r5, #1
	cmp r1, r3
	ble _021F3D7A
	add r2, r3, r6
	lsr r1, r2, #0x1f
	add r1, r2, r1
	add r5, r6, #0
	asr r6, r1, #1
	b _021F3D56
_021F3D7A:
	mov r0, ip
	strh r6, [r0]
	mov r0, #1
	pop {r4, r5, r6, r7}
	bx lr
_021F3D84:
	add r1, r3, #1
	cmp r1, r5
	bge _021F3D96
	add r2, r6, r5
	lsr r1, r2, #0x1f
	add r1, r2, r1
	add r3, r6, #0
	asr r6, r1, #1
	b _021F3D56
_021F3D96:
	add r1, r6, #1
	mov r0, ip
	strh r1, [r0]
	mov r0, #1
	pop {r4, r5, r6, r7}
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F3DA4
MOD05_021F3DA4: ; 0x021F3DA4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x110
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x128]
	add r4, r3, #0
	str r0, [sp, #0x128]
	ldr r0, [r4, #0x1c]
	add r6, r1, #0
	add r7, r2, #0
	cmp r0, #0
	bne _021F3DC0
	add sp, #0x110
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F3DC0:
	mov r5, #0
	add r0, sp, #0x98
	str r6, [sp, #0x68]
	str r5, [sp, #0x6c]
	str r7, [sp, #0x70]
	bl MOD05_021F3D10
	ldr r1, [r4]
	ldr r0, [r1, #4]
	sub r0, r6, r0
	bpl _021F3DD8
	add r0, r5, #0
_021F3DD8:
	ldr r2, [r1, #8]
	sub r7, r7, r2
	bpl _021F3DE0
	mov r7, #0
_021F3DE0:
	ldr r1, [r1, #0x14]
	bl FX_Div
	ldr r1, [r4]
	asr r6, r0, #0xc
	ldrh r0, [r1]
	cmp r6, r0
	blo _021F3DF2
	sub r6, r0, #1
_021F3DF2:
	ldr r1, [r1, #0x18]
	add r0, r7, #0
	bl FX_Div
	asr r1, r0, #0xc
	ldr r0, [r4]
	ldrh r0, [r0, #2]
	cmp r1, r0
	blo _021F3E06
	sub r1, r0, #1
_021F3E06:
	mul r0, r1
	add r0, r6, r0
	lsl r2, r0, #2
	ldr r1, [r4, #8]
	ldr r0, [r4, #0xc]
	add r3, r1, r2
	ldrh r6, [r3, #2]
	ldrh r1, [r1, r2]
	lsl r3, r6, #2
	add r3, r6, r3
	lsl r3, r3, #1
	add r6, r0, r3
	ldr r0, [sp, #0x70]
	add r3, sp, #0x58
	str r0, [sp, #0x28]
	ldr r2, [sp, #0x28]
	add r0, r6, #0
	bl MOD05_021F3D28
	cmp r0, #0
	bne _021F3E36
	add sp, #0x110
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F3E36:
	add r0, sp, #0x58
	ldrh r1, [r0]
	lsl r0, r1, #2
	add r1, r1, r0
	lsl r0, r1, #1
	ldrh r0, [r6, r0]
	str r0, [sp, #0x44]
	add r0, r1, #4
	lsl r0, r0, #1
	add r1, r1, #3
	ldrh r0, [r6, r0]
	lsl r1, r1, #1
	ldrh r1, [r6, r1]
	lsl r0, r0, #0x10
	orr r1, r0
	mov r0, #0
	str r0, [sp, #0x48]
	ldr r0, [sp, #0x44]
	cmp r0, #0
	bls _021F3F50
	add r0, sp, #0x98
	str r0, [sp, #0x40]
	lsl r0, r1, #1
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x28]
	asr r0, r0, #0x1f
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x68]
	str r0, [sp, #0x2c]
	asr r0, r0, #0x1f
	str r0, [sp, #0x30]
	mov r0, sp
	str r0, [sp, #0x4c]
	sub r0, r0, #4
	str r0, [sp, #0x4c]
_021F3E7C:
	ldr r0, [sp, #0x48]
	ldr r2, [r4, #0x18]
	lsl r1, r0, #1
	ldr r0, [sp, #0x3c]
	add r0, r0, r2
	ldrh r7, [r1, r0]
	add r0, r4, #0
	add r2, sp, #0x74
	add r1, r7, #0
	bl MOD05_021F3C98
	mov r0, #0
	add r3, sp, #0x80
	str r0, [sp, #0x78]
	str r0, [sp, #0x84]
	str r0, [sp, #0x90]
	ldmia r3!, {r0, r1}
	add r2, sp, #8
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r3, sp, #0x8c
	str r0, [r2]
	ldmia r3!, {r0, r1}
	add r2, sp, #0x14
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r3, sp, #0x74
	str r0, [r2]
	ldr r2, [sp, #0x4c]
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r6, sp, #0x68
	str r0, [r2]
	ldr r0, [sp, #0x4c]
	ldr r3, [r0]
	ldmia r6!, {r0, r1, r2}
	bl FUN_0201C878
	cmp r0, #1
	bne _021F3F40
	add r0, r4, #0
	add r1, r7, #0
	add r2, sp, #0x5c
	bl MOD05_021F3CF0
	ldr r0, [sp, #0x5c]
	ldr r2, [sp, #0x2c]
	ldr r3, [sp, #0x30]
	asr r1, r0, #0x1f
	bl _ll_mul
	str r0, [sp, #0x50]
	ldr r0, [sp, #0x64]
	add r6, r1, #0
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x38]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov ip, r0
	mov r2, #0xc
	ldr r0, [r4, #4]
	mul r2, r7
	add r0, r0, r2
	mov r2, #2
	ldr r3, [sp, #0x50]
	lsl r2, r2, #0xa
	add r3, r3, r2
	ldr r2, _021F3FDC ; =0x00000000
	ldr r0, [r0, #8]
	adc r6, r2
	lsl r2, r6, #0x14
	lsr r3, r3, #0xc
	orr r3, r2
	mov r2, #2
	lsl r2, r2, #0xa
	mov r6, ip
	add r2, r6, r2
	ldr r6, _021F3FDC ; =0x00000000
	adc r1, r6
	lsl r1, r1, #0x14
	lsr r2, r2, #0xc
	orr r2, r1
	add r1, r3, r2
	add r0, r0, r1
	ldr r1, [sp, #0x60]
	neg r0, r0
	bl FX_Div
	ldr r1, [sp, #0x40]
	add r5, r5, #1
	str r0, [r1]
	add r0, r1, #0
	add r0, #0xc
	str r0, [sp, #0x40]
	cmp r5, #0xa
	bge _021F3F50
_021F3F40:
	ldr r0, [sp, #0x48]
	add r0, r0, #1
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	str r1, [sp, #0x48]
	ldr r0, [sp, #0x44]
	cmp r1, r0
	blo _021F3E7C
_021F3F50:
	cmp r5, #1
	ble _021F3FB8
	mov r0, #0
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x98]
	bl FUN_0201C7A8
	add r4, r0, #0
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x98]
	bl FUN_0201C7A0
	sub r6, r4, r0
	mov r4, #1
	cmp r5, #1
	ble _021F3FA4
_021F3F72:
	mov r0, #0xc
	add r7, r4, #0
	mul r7, r0
	add r1, sp, #0x98
	ldr r0, [sp, #0x20]
	ldr r1, [r1, r7]
	bl FUN_0201C7A8
	add r1, sp, #0x98
	str r0, [sp, #0x54]
	ldr r0, [sp, #0x20]
	ldr r1, [r1, r7]
	bl FUN_0201C7A0
	ldr r1, [sp, #0x54]
	sub r0, r1, r0
	cmp r6, r0
	ble _021F3F9A
	add r6, r0, #0
	str r4, [sp, #0x24]
_021F3F9A:
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r5
	blt _021F3F72
_021F3FA4:
	ldr r0, [sp, #0x24]
	mov r1, #0xc
	mul r1, r0
	add r0, sp, #0x98
	ldr r1, [r0, r1]
	ldr r0, [sp, #0x128]
	add sp, #0x110
	str r1, [r0]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F3FB8:
	bne _021F3FC6
	ldr r1, [sp, #0x98]
	ldr r0, [sp, #0x128]
	add sp, #0x110
	str r1, [r0]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F3FC6:
	cmp r5, #0
	beq _021F3FD6
	ldr r1, [sp, #0x98]
	ldr r0, [sp, #0x128]
	add sp, #0x110
	str r1, [r0]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F3FD6:
	mov r0, #0
	add sp, #0x110
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F3FDC: .word 0x00000000

	thumb_func_start MOD05_021F3FE0
MOD05_021F3FE0: ; 0x021F3FE0
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0
	mov r2, #0x1c
	add r4, r1, #0
	bl MIi_CpuClear32
	add r0, r5, #0
	mov r1, #8
	add r2, sp, #0
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, sp, #0
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, r4, #0
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, sp, #0
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, r4, #4
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, sp, #0
	bl NARC_ReadFile
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #2
	add r2, #8
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, sp, #0
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, sp, #0
	bl NARC_ReadFile
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #2
	add r2, #0xc
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, sp, #0
	bl NARC_ReadFile
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #2
	add r2, #0x18
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, sp, #0
	bl NARC_ReadFile
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #4
	add r2, #0x14
	bl NARC_ReadFile
	add r4, #0x10
	add r0, r5, #0
	mov r1, #4
	add r2, r4, #0
	bl NARC_ReadFile
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F4094
MOD05_021F4094: ; 0x021F4094
	push {r4, r5, r6, lr}
	ldr r4, [r2]
	mov r3, #0
	str r4, [r1, #0x10]
	ldr r5, [r0]
	mov r4, #0xc
	mul r4, r5
	add r3, r3, r4
	lsr r6, r3, #0x1f
	lsl r5, r3, #0x1e
	sub r5, r5, r6
	mov r4, #0x1e
	ror r5, r4
	add r4, r6, r5
	lsl r4, r4, #0x18
	lsr r4, r4, #0x18
	beq _021F40B8
	add r3, r3, r4
_021F40B8:
	ldr r4, [r2]
	add r4, r4, r3
	str r4, [r1, #0x14]
	ldr r5, [r0, #4]
	mov r4, #0xc
	mul r4, r5
	add r3, r3, r4
	lsr r6, r3, #0x1f
	lsl r5, r3, #0x1e
	sub r5, r5, r6
	mov r4, #0x1e
	ror r5, r4
	add r4, r6, r5
	lsl r4, r4, #0x18
	lsr r4, r4, #0x18
	beq _021F40DA
	add r3, r3, r4
_021F40DA:
	ldr r4, [r2]
	add r4, r4, r3
	str r4, [r1, #4]
	ldr r5, [r0, #8]
	mov r4, #0xc
	mul r4, r5
	add r3, r3, r4
	lsr r6, r3, #0x1f
	lsl r5, r3, #0x1e
	sub r5, r5, r6
	mov r4, #0x1e
	ror r5, r4
	add r4, r6, r5
	lsl r4, r4, #0x18
	lsr r4, r4, #0x18
	beq _021F40FC
	add r3, r3, r4
_021F40FC:
	ldr r4, [r2]
	add r4, r4, r3
	add r3, #0x1c
	str r4, [r1]
	lsr r6, r3, #0x1f
	lsl r5, r3, #0x1e
	sub r5, r5, r6
	mov r4, #0x1e
	ror r5, r4
	add r4, r6, r5
	lsl r4, r4, #0x18
	lsr r4, r4, #0x18
	beq _021F4118
	add r3, r3, r4
_021F4118:
	ldr r4, [r2]
	add r4, r4, r3
	str r4, [r1, #8]
	ldr r4, [r0, #0xc]
	lsl r4, r4, #2
	add r3, r3, r4
	lsr r6, r3, #0x1f
	lsl r5, r3, #0x1e
	sub r5, r5, r6
	mov r4, #0x1e
	ror r5, r4
	add r4, r6, r5
	lsl r4, r4, #0x18
	lsr r4, r4, #0x18
	beq _021F4138
	add r3, r3, r4
_021F4138:
	ldr r4, [r2]
	add r4, r4, r3
	str r4, [r1, #0xc]
	ldr r4, [r0, #0x14]
	add r3, r3, r4
	lsr r6, r3, #0x1f
	lsl r5, r3, #0x1e
	sub r5, r5, r6
	mov r4, #0x1e
	ror r5, r4
	add r4, r6, r5
	lsl r4, r4, #0x18
	lsr r4, r4, #0x18
	beq _021F4156
	add r3, r3, r4
_021F4156:
	ldr r2, [r2]
	add r2, r2, r3
	str r2, [r1, #0x18]
	ldr r0, [r0, #0x10]
	add r3, r3, r0
	lsr r2, r3, #0x1f
	lsl r1, r3, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	beq _021F4174
	add r3, r3, r0
_021F4174:
	mov r0, #9
	lsl r0, r0, #0xc
	cmp r3, r0
	ble _021F4180
	bl GF_AssertFail
_021F4180:
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4184
MOD05_021F4184: ; 0x021F4184
	ldr r3, _021F4190 ; =NARC_ReadFile
	add r2, r1, #0
	mov r1, #0x1c
	ldr r2, [r2]
	bx r3
	nop
_021F4190: .word NARC_ReadFile

	thumb_func_start MOD05_021F4194
MOD05_021F4194: ; 0x021F4194
	ldr r2, [r2]
	add r3, r1, #0
	mov r1, #0xc
	mul r1, r2
	ldr r2, [r3, #0x10]
	ldr r3, _021F41A4 ; =NARC_ReadFile
	bx r3
	nop
_021F41A4: .word NARC_ReadFile

	thumb_func_start MOD05_021F41A8
MOD05_021F41A8: ; 0x021F41A8
	ldr r2, [r2, #4]
	add r3, r1, #0
	mov r1, #0xc
	mul r1, r2
	ldr r2, [r3, #0x14]
	ldr r3, _021F41B8 ; =NARC_ReadFile
	bx r3
	nop
_021F41B8: .word NARC_ReadFile

	thumb_func_start MOD05_021F41BC
MOD05_021F41BC: ; 0x021F41BC
	ldr r2, [r2, #8]
	add r3, r1, #0
	mov r1, #0xc
	mul r1, r2
	ldr r2, [r3, #4]
	ldr r3, _021F41CC ; =NARC_ReadFile
	bx r3
	nop
_021F41CC: .word NARC_ReadFile

	thumb_func_start MOD05_021F41D0
MOD05_021F41D0: ; 0x021F41D0
	add r3, r1, #0
	ldr r1, [r2, #0xc]
	ldr r2, [r3, #8]
	ldr r3, _021F41DC ; =NARC_ReadFile
	lsl r1, r1, #2
	bx r3
	.balign 4, 0
_021F41DC: .word NARC_ReadFile

	thumb_func_start MOD05_021F41E0
MOD05_021F41E0: ; 0x021F41E0
	add r3, r1, #0
	ldr r1, [r2, #0x14]
	ldr r2, [r3, #0xc]
	ldr r3, _021F41EC ; =NARC_ReadFile
	bx r3
	nop
_021F41EC: .word NARC_ReadFile

	thumb_func_start MOD05_021F41F0
MOD05_021F41F0: ; 0x021F41F0
	add r3, r1, #0
	ldr r1, [r2, #0x10]
	ldr r2, [r3, #0x18]
	ldr r3, _021F41FC ; =NARC_ReadFile
	bx r3
	nop
_021F41FC: .word NARC_ReadFile

	thumb_func_start MOD05_021F4200
MOD05_021F4200: ; 0x021F4200
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r1, #0xa0
	ldr r1, [r1]
	add r5, r0, #0
	cmp r1, #1
	bne _021F4216
	add r1, r4, #0
	mov r2, #2
	add r1, #0x6c
	strb r2, [r1]
_021F4216:
	add r1, r4, #0
	add r1, #0x6c
	ldrb r1, [r1]
	cmp r1, #0
	beq _021F422A
	cmp r1, #1
	beq _021F425E
	cmp r1, #2
	beq _021F42EA
	b _021F4302
_021F422A:
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	ldr r0, [r0]
	cmp r0, #0
	beq _021F423A
	mov r0, #0
	b _021F4302
_021F423A:
	add r0, r4, #0
	add r0, #0xa8
	add r1, r4, #0
	ldr r0, [r0]
	add r1, #0x4c
	bl MOD05_021F3FE0
	add r1, r4, #0
	add r1, #0x9c
	add r0, r4, #0
	add r2, r4, #0
	ldr r1, [r1]
	add r0, #0x4c
	add r2, #0x98
	bl MOD05_021F4094
	mov r0, #1
	b _021F4302
_021F425E:
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0x9c
	ldr r0, [r0]
	ldr r1, [r1]
	bl MOD05_021F4184
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0x9c
	add r2, r4, #0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, #0x4c
	bl MOD05_021F4194
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0x9c
	add r2, r4, #0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, #0x4c
	bl MOD05_021F41A8
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0x9c
	add r2, r4, #0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, #0x4c
	bl MOD05_021F41BC
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0x9c
	add r2, r4, #0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, #0x4c
	bl MOD05_021F41D0
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0x9c
	add r2, r4, #0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, #0x4c
	bl MOD05_021F41E0
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0x9c
	add r2, r4, #0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, #0x4c
	bl MOD05_021F41F0
	mov r0, #1
	b _021F4302
_021F42EA:
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	mov r1, #0
	str r1, [r0]
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
_021F4302:
	cmp r0, #1
	bne _021F4326
	add r0, r4, #0
	add r0, #0x6c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x6c
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x6c
	ldrb r0, [r0]
	cmp r0, #2
	bne _021F4326
	add r4, #0x9c
	ldr r0, [r4]
	mov r1, #1
	str r1, [r0, #0x1c]
_021F4326:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F4328
MOD05_021F4328: ; 0x021F4328
	push {r3, lr}
	mov r0, #4
	mov r1, #0x20
	bl AllocFromHeap
	mov r1, #0
	str r1, [r0, #0x10]
	str r1, [r0, #0x14]
	str r1, [r0, #4]
	str r1, [r0]
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	str r1, [r0, #0x18]
	pop {r3, pc}

	thumb_func_start MOD05_021F4344
MOD05_021F4344: ; 0x021F4344
	push {r0, r1, r2, r3}
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #4
	mov r1, #0x1c
	add r4, r2, #0
	bl AllocFromHeapAtEnd
	add r6, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD05_021F3FE0
	add r0, r6, #0
	add r1, r4, #0
	add r2, sp, #0x1c
	bl MOD05_021F4094
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F4184
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD05_021F4194
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD05_021F41A8
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD05_021F41BC
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD05_021F41D0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD05_021F41E0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD05_021F41F0
	add r0, r6, #0
	bl FreeToHeap
	mov r0, #1
	str r0, [r4, #0x1c]
	pop {r4, r5, r6}
	pop {r3}
	add sp, #0x10
	bx r3
	.balign 4, 0

	thumb_func_start MOD05_021F43C0
MOD05_021F43C0: ; 0x021F43C0
	push {r3, lr}
	cmp r0, #0
	beq _021F43CA
	bl FreeToHeap
_021F43CA:
	pop {r3, pc}

	thumb_func_start MOD05_021F43CC
MOD05_021F43CC: ; 0x021F43CC
	cmp r0, #0
	beq _021F43E2
	mov r1, #0
	str r1, [r0, #0x1c]
	str r1, [r0, #0x10]
	str r1, [r0, #0x14]
	str r1, [r0, #4]
	str r1, [r0]
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	str r1, [r0, #0x18]
_021F43E2:
	bx lr

	thumb_func_start MOD05_021F43E4
MOD05_021F43E4: ; 0x021F43E4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #4
	mov r1, #0xb4
	add r6, r2, #0
	add r7, r3, #0
	bl AllocFromHeapAtEnd
	add r1, r0, #0
	add r2, r1, #0
	mov r0, #0
	add r2, #0x6c
	strb r0, [r2]
	add r2, r1, #0
	add r2, #0xa8
	str r5, [r2]
	add r2, r1, #0
	add r2, #0xac
	str r4, [r2]
	add r2, r1, #0
	add r2, #0x9c
	str r6, [r2]
	add r2, r1, #0
	add r2, #0xa4
	str r7, [r2]
	add r2, r1, #0
	add r2, #0xa0
	str r0, [r2]
	str r0, [r1, #0x68]
	str r0, [r1, #0x48]
	ldr r0, [sp, #0x18]
	ldr r2, [r0]
	add r0, r1, #0
	add r0, #0x98
	str r2, [r0]
	add r0, r1, #0
	ldr r2, [sp, #0x1c]
	add r0, #0xb0
	str r2, [r0]
	ldr r0, _021F4440 ; =MOD05_021F4200
	mov r2, #1
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F4440: .word MOD05_021F4200

	thumb_func_start MOD05_021F4444
MOD05_021F4444: ; 0x021F4444
	push {r3, lr}
	bl FUN_0201B6C8
	mov r1, #1
	add r0, #0xa0
	str r1, [r0]
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4454
MOD05_021F4454: ; 0x021F4454
	mov r1, #0
	str r1, [r0, #0x1c]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F445C
MOD05_021F445C: ; 0x021F445C
	push {r4, r5}
	ldr r3, [r2, #0x14]
	cmp r3, #0
	bne _021F446A
	mov r0, #0
	pop {r4, r5}
	bx lr
_021F446A:
	ldr r5, [r2]
	ldr r3, [r2, #8]
	ldr r4, [r2, #4]
	ldr r2, [r2, #0xc]
	add r3, r5, r3
	add r2, r4, r2
	sub r3, r3, #1
	sub r2, r2, #1
	cmp r5, r0
	bgt _021F4490
	cmp r0, r3
	bgt _021F4490
	cmp r4, r1
	bgt _021F4490
	cmp r1, r2
	bgt _021F4490
	mov r0, #1
	pop {r4, r5}
	bx lr
_021F4490:
	mov r0, #0
	pop {r4, r5}
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F4498
MOD05_021F4498: ; 0x021F4498
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	mov r1, #8
	bl AllocFromHeap
	mov r1, #0x18
	add r4, r0, #0
	add r0, r6, #0
	mul r1, r5
	bl AllocFromHeap
	str r0, [r4, #4]
	mov r6, #0
	str r5, [r4]
	cmp r5, #0
	bls _021F44D4
	add r0, r6, #0
	mov r1, #0x18
_021F44C0:
	add r2, r6, #0
	ldr r3, [r4, #4]
	mul r2, r1
	add r2, r3, r2
	str r0, [r2, #0x14]
	add r2, r6, #1
	lsl r2, r2, #0x18
	lsr r6, r2, #0x18
	cmp r6, r5
	blo _021F44C0
_021F44D4:
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F44D8
MOD05_021F44D8: ; 0x021F44D8
	push {r4, r5}
	ldr r5, [sp, #0x10]
	mov r4, #0x18
	mul r4, r0
	ldr r0, [r5, #4]
	str r1, [r0, r4]
	ldr r0, [r5, #4]
	ldr r1, [sp, #8]
	add r0, r0, r4
	str r2, [r0, #4]
	ldr r0, [r5, #4]
	add r0, r0, r4
	str r3, [r0, #8]
	ldr r0, [r5, #4]
	add r0, r0, r4
	str r1, [r0, #0xc]
	ldr r0, [r5, #4]
	ldr r1, [sp, #0xc]
	add r0, r0, r4
	str r1, [r0, #0x10]
	ldr r0, [r5, #4]
	mov r1, #1
	add r0, r0, r4
	str r1, [r0, #0x14]
	pop {r4, r5}
	bx lr

	thumb_func_start MOD05_021F450C
MOD05_021F450C: ; 0x021F450C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4520
MOD05_021F4520: ; 0x021F4520
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	add r5, r2, #0
	str r3, [sp]
	cmp r3, #0
	bne _021F4532
	bl GF_AssertFail
_021F4532:
	ldr r0, [r5]
	mov r4, #0
	cmp r0, #0
	ble _021F4562
_021F453A:
	mov r3, #0x18
	ldr r2, [r5, #4]
	mul r3, r4
	add r0, r6, #0
	add r1, r7, #0
	add r2, r2, r3
	bl MOD05_021F445C
	cmp r0, #0
	beq _021F4556
	ldr r0, [sp]
	strb r4, [r0]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F4556:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, [r5]
	cmp r4, r0
	blt _021F453A
_021F4562:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4568
MOD05_021F4568: ; 0x021F4568
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r5, r0
	blt _021F4578
	bl GF_AssertFail
_021F4578:
	mov r0, #0x18
	add r6, r5, #0
	mul r6, r0
	ldr r0, [r4, #4]
	add r0, r0, r6
	ldr r0, [r0, #0x14]
	cmp r0, #0
	bne _021F458C
	bl GF_AssertFail
_021F458C:
	ldr r0, [r4, #4]
	add r0, r0, r6
	ldr r0, [r0, #0x10]
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F4594
MOD05_021F4594: ; 0x021F4594
	push {r4, r5, r6, lr}
	add r6, r2, #0
	add r5, r0, #0
	ldr r0, [r6]
	add r4, r1, #0
	cmp r5, r0
	blt _021F45A6
	bl GF_AssertFail
_021F45A6:
	mov r0, #0x18
	ldr r1, [r6, #4]
	mul r0, r5
	add r0, r1, r0
	str r4, [r0, #0x10]
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F45B4
MOD05_021F45B4: ; 0x021F45B4
	push {r4, lr}
	mov r1, #0x1c
	bl AllocFromHeap
	add r4, r0, #0
	bl MOD05_021F4650
	add r0, r4, #0
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F45C8
MOD05_021F45C8: ; 0x021F45C8
	push {r4, lr}
	add r4, r0, #0
	beq _021F45E4
	ldr r1, [r4]
	cmp r1, #1
	bne _021F45D8
	bl MOD05_021F4608
_021F45D8:
	add r0, r4, #0
	bl MOD05_021F4650
	add r0, r4, #0
	bl FreeToHeap
_021F45E4:
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F45E8
MOD05_021F45E8: ; 0x021F45E8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021F4604 ; =MOD05_021F4688
	add r1, r4, #0
	bl FUN_02015F34
	cmp r0, #1
	beq _021F45FC
	bl GF_AssertFail
_021F45FC:
	mov r0, #1
	str r0, [r4]
	pop {r4, pc}
	nop
_021F4604: .word MOD05_021F4688

	thumb_func_start MOD05_021F4608
MOD05_021F4608: ; 0x021F4608
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F34
	cmp r0, #1
	beq _021F461C
	bl GF_AssertFail
_021F461C:
	mov r0, #0
	str r0, [r4]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4624
MOD05_021F4624: ; 0x021F4624
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r2, #0
	bl MOD05_021F46A8
	add r4, r0, #0
	bne _021F4636
	bl GF_AssertFail
_021F4636:
	cmp r4, #0
	beq _021F4642
	str r6, [r4, #4]
	str r5, [r4, #8]
	mov r0, #1
	str r0, [r4]
_021F4642:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4648
MOD05_021F4648: ; 0x021F4648
	ldr r3, _021F464C ; =MOD05_021F4678
	bx r3
	.balign 4, 0
_021F464C: .word MOD05_021F4678

	thumb_func_start MOD05_021F4650
MOD05_021F4650: ; 0x021F4650
	push {r3, r4, r5, lr}
	add r3, r0, #0
	mov r2, #0x1c
	mov r1, #0
_021F4658:
	strb r1, [r3]
	add r3, r3, #1
	sub r2, r2, #1
	bne _021F4658
	mov r4, #0
	str r4, [r0]
	add r5, r0, #4
_021F4666:
	add r0, r5, #0
	bl MOD05_021F4678
	add r4, r4, #1
	add r5, #0xc
	cmp r4, #2
	blt _021F4666
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4678
MOD05_021F4678: ; 0x021F4678
	mov r2, #0
	ldr r1, _021F4684 ; =MOD05_021F46A4
	str r2, [r0]
	str r1, [r0, #8]
	str r2, [r0, #4]
	bx lr
	.balign 4, 0
_021F4684: .word MOD05_021F46A4

	thumb_func_start MOD05_021F4688
MOD05_021F4688: ; 0x021F4688
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r6, #0
	add r4, r5, #4
_021F4690:
	ldr r1, [r5, #8]
	ldr r2, [r5, #0xc]
	add r0, r4, #0
	blx r2
	add r6, r6, #1
	add r5, #0xc
	add r4, #0xc
	cmp r6, #2
	blt _021F4690
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F46A4
MOD05_021F46A4: ; 0x021F46A4
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F46A8
MOD05_021F46A8: ; 0x021F46A8
	mov r2, #0
	add r3, r0, #0
_021F46AC:
	ldr r1, [r3, #4]
	cmp r1, #0
	bne _021F46BC
	add r1, r0, #4
	mov r0, #0xc
	mul r0, r2
	add r0, r1, r0
	bx lr
_021F46BC:
	add r2, r2, #1
	add r3, #0xc
	cmp r2, #2
	blt _021F46AC
	mov r0, #0
	bx lr

	thumb_func_start MOD05_021F46C8
MOD05_021F46C8: ; 0x021F46C8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r1, #0xca
	lsl r1, r1, #2
	add r6, r0, #0
	bl AllocFromHeap
	mov r2, #0xca
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl memset
	mov r2, #0x63
	mov r0, #0
	add r1, r4, #0
	lsl r2, r2, #2
	str r0, [r4]
	add r0, r6, #0
	add r1, #0xc
	add r2, r4, r2
	bl FUN_02012944
	mov r1, #0xc3
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #4
	str r5, [r4, r0]
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F4704
MOD05_021F4704: ; 0x021F4704
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	cmp r1, #1
	bne _021F4712
	bl MOD05_021F491C
_021F4712:
	mov r0, #0xc3
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02012974
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD05_021F4724
MOD05_021F4724: ; 0x021F4724
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F4732
	bl GF_AssertFail
_021F4732:
	mov r0, #0x31
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	ldr r1, _021F47A4 ; =MOD05_021F48CC
	add r2, r4, #0
	bl MOD05_021F4624
	mov r2, #0xc5
	lsl r2, r2, #2
	str r0, [r4, r2]
	ldr r0, _021F47A8 ; =MOD05_021F47B4
	add r1, r4, #0
	add r2, #0xec
	bl FUN_0200CA44
	mov r2, #0xc7
	lsl r2, r2, #2
	str r0, [r4, r2]
	ldr r0, _021F47AC ; =MOD05_021F48BC
	add r1, r4, #0
	add r2, #0xe4
	bl FUN_0200CA60
	mov r2, #0x32
	lsl r2, r2, #4
	str r0, [r4, r2]
	ldr r0, _021F47B0 ; =MOD05_021F48F0
	add r1, r4, #0
	add r2, #0xe0
	bl FUN_0200CA60
	mov r1, #0xc9
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	mov r2, #6
	add r0, #0xc
	mov r1, #0
	lsl r2, r2, #6
	bl memset
	mov r2, #0x63
	lsl r2, r2, #2
	add r0, r4, r2
	mov r1, #0
	sub r2, #0xc
	bl memset
	mov r0, #1
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #8]
	mov r0, #0x61
	lsl r0, r0, #4
	bl FUN_020054C8
	pop {r4, pc}
	.balign 4, 0
_021F47A4: .word MOD05_021F48CC
_021F47A8: .word MOD05_021F47B4
_021F47AC: .word MOD05_021F48BC
_021F47B0: .word MOD05_021F48F0

	thumb_func_start MOD05_021F47B4
MOD05_021F47B4: ; 0x021F47B4
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #8]
	cmp r0, #3
	bhi _021F483C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021F47CA: ; jump table
	.short _021F47D2 - _021F47CA - 2 ; case 0
	.short _021F47DE - _021F47CA - 2 ; case 1
	.short _021F480A - _021F47CA - 2 ; case 2
	.short _021F4830 - _021F47CA - 2 ; case 3
_021F47D2:
	mov r0, #3
	str r0, [r4, #4]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	pop {r4, pc}
_021F47DE:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0xc3
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02012988
	ldr r1, [r4, #4]
	mov r2, #3
	sub r1, r2, r1
	bl MOD05_021F4878
	ldr r0, [r4, #4]
	cmp r0, #0
	bgt _021F483C
	mov r0, #3
	str r0, [r4, #4]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	pop {r4, pc}
_021F480A:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0xc3
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02012988
	ldr r1, [r4, #4]
	mov r2, #3
	bl MOD05_021F4878
	ldr r0, [r4, #4]
	cmp r0, #0
	bgt _021F483C
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	pop {r4, pc}
_021F4830:
	add r0, r4, #0
	bl MOD05_021F491C
	mov r0, #0
	bl G3X_SetHOffset
_021F483C:
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4840
MOD05_021F4840: ; 0x021F4840
	push {r4, lr}
	ldr r1, _021F4870 ; =0x04000006
	ldrh r4, [r1]
	mov r1, #0xc3
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bl FUN_0201299C
	cmp r4, #0xc0
	bge _021F486E
	add r3, r4, #1
	cmp r3, #0xc0
	blt _021F485C
	sub r3, #0xc0
_021F485C:
	ldr r1, _021F4874 ; =0x04000004
	ldrh r2, [r1]
	mov r1, #2
	tst r1, r2
	beq _021F486E
	lsl r1, r3, #1
	ldrh r0, [r0, r1]
	bl G3X_SetHOffset
_021F486E:
	pop {r4, pc}
	.balign 4, 0
_021F4870: .word 0x04000006
_021F4874: .word 0x04000004

	thumb_func_start MOD05_021F4878
MOD05_021F4878: ; 0x021F4878
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	lsl r0, r1, #1
	add r0, r1, r0
	add r1, r2, #0
	mov r4, #1
	bl _s32_div_f
	neg r1, r0
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	lsl r0, r0, #0x10
	mov r6, #0
	str r1, [sp]
	lsr r7, r0, #0x10
_021F4896:
	add r0, r6, #0
	mov r1, #0xa
	bl _s32_div_f
	cmp r1, #0
	bne _021F48A6
	mov r0, #1
	eor r4, r0
_021F48A6:
	cmp r4, #0
	beq _021F48AE
	strh r7, [r5]
	b _021F48B2
_021F48AE:
	ldr r0, [sp]
	strh r0, [r5]
_021F48B2:
	add r6, r6, #1
	add r5, r5, #2
	cmp r6, #0xc0
	blt _021F4896
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F48BC
MOD05_021F48BC: ; 0x021F48BC
	mov r2, #0xc6
	ldr r3, _021F48C8 ; =G3X_SetHOffset
	mov r0, #0
	lsl r2, r2, #2
	str r0, [r1, r2]
	bx r3
	.balign 4, 0
_021F48C8: .word G3X_SetHOffset

	thumb_func_start MOD05_021F48CC
MOD05_021F48CC: ; 0x021F48CC
	ldr r3, _021F48D4 ; =MOD05_021F48D8
	add r0, r1, #0
	bx r3
	nop
_021F48D4: .word MOD05_021F48D8

	thumb_func_start MOD05_021F48D8
MOD05_021F48D8: ; 0x021F48D8
	push {r3, lr}
	ldr r1, [r0]
	cmp r1, #1
	bne _021F48EE
	mov r1, #0xc6
	lsl r1, r1, #2
	ldr r1, [r0, r1]
	cmp r1, #1
	bne _021F48EE
	bl MOD05_021F4840
_021F48EE:
	pop {r3, pc}

	thumb_func_start MOD05_021F48F0
MOD05_021F48F0: ; 0x021F48F0
	ldr r3, _021F48F8 ; =MOD05_021F48FC
	add r0, r1, #0
	bx r3
	nop
_021F48F8: .word MOD05_021F48FC

	thumb_func_start MOD05_021F48FC
MOD05_021F48FC: ; 0x021F48FC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #1
	bne _021F4918
	mov r0, #0xc3
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_020129B4
	mov r0, #0xc6
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
_021F4918:
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F491C
MOD05_021F491C: ; 0x021F491C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xc5
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD05_021F4648
	mov r0, #0xc5
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, #8
	ldr r0, [r4, r0]
	bl FUN_0200CAB4
	mov r0, #0xc7
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_0200CAB4
	mov r0, #0x32
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	add r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_0200CAB4
	mov r0, #0xc9
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	str r1, [r4]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4968
MOD05_021F4968: ; 0x021F4968
	ldr r2, [r1, #0x14]
	ldr r3, _021F4974 ; =FUN_02016B44
	add r1, r1, r2
	sub r1, r1, r0
	bx r3
	nop
_021F4974: .word FUN_02016B44

	thumb_func_start MOD05_021F4978
MOD05_021F4978: ; 0x021F4978
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r1, #0x23
	add r5, r0, #0
	mov r0, #4
	lsl r1, r1, #6
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #4
	mov r1, #0x10
	bl AllocFromHeapAtEnd
	ldr r1, _021F49A8 ; =0x000008B8
	mov r2, #0
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	str r5, [r0]
	ldr r0, [r4, r1]
	str r6, [r0, #4]
	ldr r0, [r4, r1]
	str r2, [r0, #0xc]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F49A8: .word 0x000008B8

	thumb_func_start MOD05_021F49AC
MOD05_021F49AC: ; 0x021F49AC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x110
	add r5, r0, #0
	ldr r0, _021F4B9C ; =0x000008B8
	mov r1, #0x2a
	ldr r7, [r5, r0]
	sub r0, #8
	ldr r2, [r7]
	add r0, r5, r0
	bl ReadWholeNarcMemberByIdPair
	mov r1, #0x8b
	lsl r1, r1, #4
	ldrh r1, [r5, r1]
	mov r0, #0x2b
	mov r2, #4
	bl AllocAndReadWholeNarcMemberByIdPair
	ldr r1, _021F4BA0 ; =0x000008BC
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	ldrh r1, [r0]
	ldr r0, _021F4BA4 ; =0x00000226
	strh r1, [r7, #8]
	cmp r1, r0
	blo _021F49E4
	bl GF_AssertFail
_021F49E4:
	ldr r1, _021F4BA8 ; =0x000008A4
	mov r0, #0
	str r0, [r5, r1]
	add r1, #0xe
	ldrh r1, [r5, r1]
	mov r0, #0x2c
	mov r2, #4
	bl AllocAndReadWholeNarcMemberByIdPair
	ldr r1, _021F4BAC ; =0x0000089C
	mov r2, #4
	str r0, [r5, r1]
	add r1, #0x14
	ldrh r1, [r5, r1]
	mov r0, #0x47
	bl AllocAndReadWholeNarcMemberByIdPair
	mov r1, #0x8a
	lsl r1, r1, #4
	str r0, [r5, r1]
	sub r0, r1, #4
	ldr r0, [r5, r0]
	bl NNS_G3dGetTex
	ldr r1, _021F4BA8 ; =0x000008A4
	str r0, [r5, r1]
	ldrh r0, [r7, #8]
	cmp r0, #0
	beq _021F4A2C
	sub r0, r1, #4
	ldr r0, [r5, r0]
	bl NNS_G3dGetTex
	ldr r1, _021F4BB0 ; =0x000008A8
	str r0, [r5, r1]
	b _021F4A32
_021F4A2C:
	mov r2, #0
	add r0, r1, #4
	str r2, [r5, r0]
_021F4A32:
	ldr r0, _021F4BA8 ; =0x000008A4
	ldr r0, [r5, r0]
	bl FUN_0201B3C4
	cmp r0, #0
	bne _021F4A42
	bl GF_AssertFail
_021F4A42:
	ldr r1, _021F4BAC ; =0x0000089C
	ldr r0, [r5, r1]
	add r1, #8
	ldr r1, [r5, r1]
	bl MOD05_021F4968
	ldr r0, _021F4BB0 ; =0x000008A8
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021F4A70
	bl FUN_0201B3C4
	cmp r0, #0
	bne _021F4A62
	bl GF_AssertFail
_021F4A62:
	mov r1, #0x8a
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	add r1, #8
	ldr r1, [r5, r1]
	bl MOD05_021F4968
_021F4A70:
	mov r2, #0
	ldr r0, _021F4BA4 ; =0x00000226
	add r3, r5, #0
	add r1, r2, #0
_021F4A78:
	add r2, r2, #1
	str r1, [r3, #4]
	add r3, r3, #4
	cmp r2, r0
	blt _021F4A78
	ldr r0, _021F4BB4 ; =0x000008AC
	str r1, [r5, r0]
	mov r0, #0x28
	mov r1, #4
	bl NARC_ctor
	str r0, [sp, #0xc]
	ldr r0, [r7, #4]
	bl MOD05_021DA220
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldrh r0, [r7, #8]
	cmp r0, #0
	ble _021F4B10
	ldr r0, [sp, #8]
	str r0, [sp]
_021F4AA6:
	ldr r0, _021F4BA0 ; =0x000008BC
	ldr r1, [r5, r0]
	ldr r0, [sp]
	add r0, r1, r0
	ldrh r6, [r0, #2]
	lsl r0, r6, #2
	add r4, r5, r0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021F4ABE
	bl GF_AssertFail
_021F4ABE:
	ldr r0, [sp, #0xc]
	add r1, r6, #0
	mov r2, #4
	bl NARC_AllocAndReadWholeMember
	str r0, [r4, #4]
	ldr r0, [sp, #4]
	cmp r6, r0
	bge _021F4AEC
	ldr r0, [r4, #4]
	bl NNS_G3dGetMdlSet
	add r1, r0, #0
	ldrh r2, [r1, #0xe]
	ldr r3, [r7, #4]
	add r0, r6, #0
	add r2, r1, r2
	ldr r2, [r2, #0xc]
	add r1, r1, r2
	ldr r2, _021F4BB0 ; =0x000008A8
	ldr r2, [r5, r2]
	bl MOD05_021D9CEC
_021F4AEC:
	ldr r1, _021F4BB0 ; =0x000008A8
	ldr r0, [r4, #4]
	ldr r1, [r5, r1]
	bl FUN_0201B3A8
	cmp r0, #0
	bne _021F4AFE
	bl GF_AssertFail
_021F4AFE:
	ldr r0, [sp]
	ldrh r1, [r7, #8]
	add r0, r0, #2
	str r0, [sp]
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
	cmp r0, r1
	blt _021F4AA6
_021F4B10:
	ldr r0, [r5, #4]
	cmp r0, #0
	bne _021F4B46
	ldr r0, [sp, #0xc]
	mov r1, #0
	mov r2, #4
	bl NARC_AllocAndReadWholeMember
	str r0, [r5, #4]
	bl NNS_G3dGetTex
	add r4, r0, #0
	beq _021F4B46
	bl FUN_0201B3C4
	cmp r0, #0
	bne _021F4B36
	bl GF_AssertFail
_021F4B36:
	ldr r0, [r5, #4]
	add r1, r4, #0
	bl FUN_0201B3A8
	cmp r0, #0
	bne _021F4B46
	bl GF_AssertFail
_021F4B46:
	ldr r0, [sp, #0xc]
	bl NARC_dtor
	ldr r2, _021F4BB8 ; =0x04000060
	ldr r0, _021F4BBC ; =0xFFFFCFFF
	ldrh r1, [r2]
	and r1, r0
	mov r0, #0x20
	orr r0, r1
	strh r0, [r2]
	ldr r0, _021F4BC0 ; =0x000008B6
	ldrh r0, [r5, r0]
	cmp r0, #0
	bne _021F4B6A
	ldr r0, _021F4BC4 ; =UNK05_021FC624
	bl G3X_SetEdgeColorTable
	b _021F4B70
_021F4B6A:
	ldr r0, _021F4BC8 ; =UNK05_021FC634
	bl G3X_SetEdgeColorTable
_021F4B70:
	bl MOD05_021DB900
	ldr r1, _021F4BB4 ; =0x000008AC
	str r0, [r5, r1]
	ldr r1, _021F4BCC ; =UNK05_021FD648
	add r0, sp, #0x10
	bl sprintf
	ldr r1, _021F4BB4 ; =0x000008AC
	add r0, sp, #0x10
	ldr r1, [r5, r1]
	bl MOD05_021DB918
	ldr r0, _021F4B9C ; =0x000008B8
	ldr r0, [r5, r0]
	bl FreeToHeap
	ldr r0, _021F4B9C ; =0x000008B8
	mov r1, #0
	str r1, [r5, r0]
	add sp, #0x110
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F4B9C: .word 0x000008B8
_021F4BA0: .word 0x000008BC
_021F4BA4: .word 0x00000226
_021F4BA8: .word 0x000008A4
_021F4BAC: .word 0x0000089C
_021F4BB0: .word 0x000008A8
_021F4BB4: .word 0x000008AC
_021F4BB8: .word 0x04000060
_021F4BBC: .word 0xFFFFCFFF
_021F4BC0: .word 0x000008B6
_021F4BC4: .word UNK05_021FC624
_021F4BC8: .word UNK05_021FC634
_021F4BCC: .word UNK05_021FD648

	thumb_func_start MOD05_021F4BD0
MOD05_021F4BD0: ; 0x021F4BD0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bne _021F4BDC
	bl GF_AssertFail
_021F4BDC:
	add r2, r4, #4
	lsl r1, r5, #2
	ldr r0, [r2, r1]
	cmp r0, #0
	bne _021F4BF4
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021F4BF0
	bl GF_AssertFail
_021F4BF0:
	add r0, r4, #4
	pop {r3, r4, r5, pc}
_021F4BF4:
	add r0, r2, r1
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F4BF8
MOD05_021F4BF8: ; 0x021F4BF8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r1, [r5]
	ldr r0, _021F4C64 ; =0x000008AC
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _021F4C0A
	bl MOD05_021DB9BC
_021F4C0A:
	mov r6, #0
	ldr r7, _021F4C68 ; =0x00000226
	add r4, r6, #0
_021F4C10:
	ldr r0, [r5]
	add r0, r0, r4
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021F4C1E
	bl FreeToHeap
_021F4C1E:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, r7
	blt _021F4C10
	ldr r1, [r5]
	ldr r0, _021F4C6C ; =0x000008BC
	ldr r0, [r1, r0]
	bl FreeToHeap
	ldr r1, [r5]
	ldr r0, _021F4C70 ; =0x0000089C
	ldr r0, [r1, r0]
	bl FreeToHeap
	ldr r1, [r5]
	ldr r0, _021F4C70 ; =0x0000089C
	mov r2, #0
	str r2, [r1, r0]
	ldr r1, [r5]
	add r0, r0, #4
	ldr r0, [r1, r0]
	bl FreeToHeap
	mov r0, #0x8a
	ldr r1, [r5]
	mov r2, #0
	lsl r0, r0, #4
	str r2, [r1, r0]
	ldr r0, [r5]
	bl FreeToHeap
	mov r0, #0
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F4C64: .word 0x000008AC
_021F4C68: .word 0x00000226
_021F4C6C: .word 0x000008BC
_021F4C70: .word 0x0000089C

	thumb_func_start MOD05_021F4C74
MOD05_021F4C74: ; 0x021F4C74
	push {r4, lr}
	add r4, r0, #0
	bne _021F4C7E
	bl GF_AssertFail
_021F4C7E:
	ldr r0, _021F4C84 ; =0x000008A4
	ldr r0, [r4, r0]
	pop {r4, pc}
	.balign 4, 0
_021F4C84: .word 0x000008A4

	thumb_func_start MOD05_021F4C88
MOD05_021F4C88: ; 0x021F4C88
	push {r4, lr}
	add r4, r0, #0
	bne _021F4C92
	bl GF_AssertFail
_021F4C92:
	ldr r0, _021F4C98 ; =0x000008A8
	ldr r0, [r4, r0]
	pop {r4, pc}
	.balign 4, 0
_021F4C98: .word 0x000008A8

	thumb_func_start MOD05_021F4C9C
MOD05_021F4C9C: ; 0x021F4C9C
	ldr r1, _021F4CA4 ; =0x000008AC
	ldr r0, [r0, r1]
	bx lr
	nop
_021F4CA4: .word 0x000008AC

	thumb_func_start MOD05_021F4CA8
MOD05_021F4CA8: ; 0x021F4CA8
	ldr r1, _021F4CB8 ; =0x000008B6
	ldrh r0, [r0, r1]
	cmp r0, #0
	beq _021F4CB4
	mov r0, #1
	bx lr
_021F4CB4:
	mov r0, #0
	bx lr
	.balign 4, 0
_021F4CB8: .word 0x000008B6

	thumb_func_start MOD05_021F4CBC
MOD05_021F4CBC: ; 0x021F4CBC
	ldr r1, _021F4CD0 ; =0x000008B6
	ldrh r0, [r0, r1]
	cmp r0, #0
	bne _021F4CC8
	mov r0, #1
	b _021F4CCA
_021F4CC8:
	mov r0, #0
_021F4CCA:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
	.balign 4, 0
_021F4CD0: .word 0x000008B6

	thumb_func_start MOD05_021F4CD4
MOD05_021F4CD4: ; 0x021F4CD4
	ldr r2, _021F4CE0 ; =0x000008BC
	ldr r2, [r0, r2]
	lsl r0, r1, #1
	ldrh r0, [r2, r0]
	bx lr
	nop
_021F4CE0: .word 0x000008BC

	thumb_func_start MOD05_021F4CE4
MOD05_021F4CE4: ; 0x021F4CE4
	lsl r1, r1, #2
	add r0, r0, r1
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021F4CF2
	mov r0, #1
	bx lr
_021F4CF2:
	mov r0, #0
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F4CF8
MOD05_021F4CF8: ; 0x021F4CF8
	push {r4, lr}
	mov r0, #4
	mov r1, #0xfc
	bl AllocFromHeap
	mov r4, #0
	add r2, r4, #0
_021F4D06:
	lsl r1, r4, #3
	add r3, r0, r1
	strb r2, [r0, r1]
	add r1, r4, #1
	lsl r1, r1, #0x18
	lsr r4, r1, #0x18
	str r2, [r3, #4]
	cmp r4, #0x15
	blo _021F4D06
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4D1C
MOD05_021F4D1C: ; 0x021F4D1C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4]
	pop {r4, pc}

	thumb_func_start MOD05_021F4D2C
MOD05_021F4D2C: ; 0x021F4D2C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldr r0, _021F4D7C ; =0x000007D8
	str r0, [r1]
	ldr r0, [r5, #0x38]
	bl FUN_02055320
	add r4, r0, #0
	ldr r0, [r5, #0x38]
	bl FUN_0205532C
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl FUN_020552F8
	cmp r0, #0
	bne _021F4D76
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, sp, #0xc
	mov r2, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, r6, #0
	sub r3, r2, #1
	bl FUN_0204A840
	add r0, r5, #0
	mov r1, #0x1a
	add r2, sp, #0xc
	mov r3, #0
	bl FUN_0204A8C4
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
_021F4D76:
	mov r0, #0
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0
_021F4D7C: .word 0x000007D8

	thumb_func_start MOD05_021F4D80
MOD05_021F4D80: ; 0x021F4D80
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x1c]
	ldr r0, [r0]
	bl MOD05_021F50FC
	add r5, r0, #0
	cmp r5, #0x15
	bne _021F4D96
	bl GF_AssertFail
_021F4D96:
	ldr r0, [r4, #0xc]
	bl FUN_0202A9B0
	bl FUN_0202A9BC
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_0202A9C8
	add r4, r0, #0
	ldr r0, [r4]
	bl MOD05_021F5120
	cmp r0, #0
	beq _021F4DB8
	mov r0, #3
	pop {r3, r4, r5, pc}
_021F4DB8:
	ldr r0, [r4]
	cmp r0, #0
	beq _021F4DC2
	mov r0, #2
	pop {r3, r4, r5, pc}
_021F4DC2:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4DC8
MOD05_021F4DC8: ; 0x021F4DC8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x1c]
	ldr r0, [r0]
	bl MOD05_021F50FC
	add r5, r0, #0
	cmp r5, #0x15
	bne _021F4DDE
	bl GF_AssertFail
_021F4DDE:
	ldr r0, [r6, #0xc]
	bl FUN_0202A9B0
	bl FUN_0202A9BC
	str r0, [sp]
	ldr r1, [sp]
	add r0, r5, #0
	bl FUN_0202A9C8
	add r4, r0, #0
	mov r0, #0x5a
	lsl r0, r0, #4
	str r0, [r4]
	ldr r0, [r6, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	bl PlayerProfile_GetTrainerID
	add r1, r5, #0
	bl MOD05_021F5138
	add r7, r0, #0
	ldr r0, [sp]
	bl FUN_0202A9C0
	cmp r5, r0
	bne _021F4E42
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, #0x64
	blo _021F4E2E
	bl GF_AssertFail
_021F4E2E:
	cmp r6, #0x5a
	bhs _021F4E42
	add r0, r4, #4
	bl MOD05_021F4F44
	ldrb r0, [r4, #6]
	bl MOD05_021F4FAC
	strb r0, [r4, #7]
	pop {r3, r4, r5, r6, r7, pc}
_021F4E42:
	add r0, r7, #0
	add r1, r4, #6
	bl MOD05_021F4EE4
	ldrb r0, [r4, #6]
	cmp r0, #0
	beq _021F4E60
	add r0, r4, #4
	bl MOD05_021F4F44
	ldrb r0, [r4, #6]
	bl MOD05_021F4F98
	strb r0, [r4, #5]
	b _021F4E68
_021F4E60:
	mov r0, #0
	strb r0, [r4, #5]
	strb r0, [r4, #4]
	str r0, [r4]
_021F4E68:
	ldrb r0, [r4, #6]
	bl MOD05_021F4FAC
	strb r0, [r4, #7]
	ldr r1, [sp]
	add r0, r5, #0
	bl FUN_0202A9C4
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4E7C
MOD05_021F4E7C: ; 0x021F4E7C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	bl MOD05_021F50FC
	add r4, r0, #0
	cmp r4, #0x15
	bne _021F4E94
	bl GF_AssertFail
_021F4E94:
	add r0, r5, #0
	add r0, #0xa4
	ldr r0, [r0]
	lsl r4, r4, #3
	add r0, r0, r4
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021F4EE0
	ldr r0, [r5, #0x24]
	bl MOD05_021EF618
	ldr r1, [r5, #0x24]
	add r2, sp, #0
	bl MOD05_021EF604
	ldr r0, [sp]
	mov r1, #0x1a
	bl MOD05_021E7ED8
	add r6, r0, #0
	bl MOD05_021E7EC8
	add r1, r0, #0
	cmp r6, #0
	beq _021F4ED6
	add r3, r5, #0
	add r3, #0xa4
	ldr r3, [r3]
	ldr r0, [r5, #0x4c]
	ldrb r3, [r3, r4]
	mov r2, #0x1a
	bl MOD05_021D9FB4
_021F4ED6:
	add r5, #0xa4
	ldr r0, [r5]
	mov r1, #0
	add r0, r0, r4
	str r1, [r0, #4]
_021F4EE0:
	add sp, #4
	pop {r3, r4, r5, r6, pc}

	thumb_func_start MOD05_021F4EE4
MOD05_021F4EE4: ; 0x021F4EE4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x64
	blo _021F4F02
	bl GF_AssertFail
_021F4F02:
	cmp r6, #0
	beq _021F4F2A
	cmp r4, #1
	bge _021F4F10
	mov r0, #3
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_021F4F10:
	cmp r4, #0xa
	bge _021F4F1A
	mov r0, #0
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_021F4F1A:
	cmp r4, #0x1e
	bge _021F4F24
	mov r0, #1
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_021F4F24:
	mov r0, #2
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_021F4F2A:
	cmp r4, #0xa
	bge _021F4F34
	mov r0, #0
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_021F4F34:
	cmp r4, #0x1e
	bge _021F4F3E
	mov r0, #2
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_021F4F3E:
	mov r0, #1
	strb r0, [r5]
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F4F44
MOD05_021F4F44: ; 0x021F4F44
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x64
	blo _021F4F60
	bl GF_AssertFail
_021F4F60:
	cmp r5, #5
	bge _021F4F6A
	mov r0, #5
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_021F4F6A:
	cmp r5, #0xa
	bge _021F4F74
	mov r0, #4
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_021F4F74:
	cmp r5, #0x14
	bge _021F4F7E
	mov r0, #3
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_021F4F7E:
	cmp r5, #0x28
	bge _021F4F88
	mov r0, #2
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_021F4F88:
	cmp r5, #0x3c
	bge _021F4F92
	mov r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_021F4F92:
	mov r0, #0
	strb r0, [r4]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F4F98
MOD05_021F4F98: ; 0x021F4F98
	cmp r0, #3
	bne _021F4FA0
	mov r0, #2
	bx lr
_021F4FA0:
	cmp r0, #2
	bne _021F4FA8
	mov r0, #1
	bx lr
_021F4FA8:
	mov r0, #0
	bx lr

	thumb_func_start MOD05_021F4FAC
MOD05_021F4FAC: ; 0x021F4FAC
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x64
	blo _021F4FC8
	bl GF_AssertFail
_021F4FC8:
	cmp r4, #3
	bne _021F4FE8
	cmp r5, #5
	bge _021F4FD4
	mov r0, #2
	pop {r3, r4, r5, pc}
_021F4FD4:
	cmp r5, #6
	bge _021F4FDC
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F4FDC:
	cmp r5, #7
	bge _021F4FE4
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F4FE4:
	mov r0, #3
	pop {r3, r4, r5, pc}
_021F4FE8:
	cmp r4, #2
	bne _021F5008
	cmp r5, #0x4b
	bge _021F4FF4
	mov r0, #2
	pop {r3, r4, r5, pc}
_021F4FF4:
	cmp r5, #0x5f
	bge _021F4FFC
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F4FFC:
	cmp r5, #0x60
	bge _021F5004
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F5004:
	mov r0, #3
	pop {r3, r4, r5, pc}
_021F5008:
	cmp r4, #1
	bne _021F5028
	cmp r5, #0x13
	bge _021F5014
	mov r0, #2
	pop {r3, r4, r5, pc}
_021F5014:
	cmp r5, #0x4f
	bge _021F501C
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F501C:
	cmp r5, #0x63
	bge _021F5024
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F5024:
	mov r0, #3
	pop {r3, r4, r5, pc}
_021F5028:
	cmp r5, #1
	bge _021F5030
	mov r0, #2
	pop {r3, r4, r5, pc}
_021F5030:
	cmp r5, #0x13
	bge _021F5038
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F5038:
	cmp r5, #0x63
	bge _021F5040
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F5040:
	mov r0, #3
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F5044
MOD05_021F5044: ; 0x021F5044
	mov r2, #1
	cmp r0, #3
	bne _021F5050
	mov r0, #2
	strb r0, [r1]
	b _021F5064
_021F5050:
	cmp r0, #2
	bne _021F5058
	strb r2, [r1]
	b _021F5064
_021F5058:
	cmp r0, #1
	bne _021F5062
	mov r0, #0
	strb r0, [r1]
	b _021F5064
_021F5062:
	mov r2, #0
_021F5064:
	add r0, r2, #0
	bx lr

	thumb_func_start MOD05_021F5068
MOD05_021F5068: ; 0x021F5068
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5, #0x28]
	add r7, r1, #0
	add r1, r2, #0
	bl FUN_02034554
	bl MOD05_021F50FC
	add r4, r0, #0
	cmp r4, #0x15
	beq _021F50F8
	ldr r0, [r5, #0xc]
	bl FUN_0202A9B0
	bl FUN_0202A9BC
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0202A9C8
	add r6, r0, #0
	ldr r0, [r6]
	bl MOD05_021F5120
	cmp r0, #0
	beq _021F50F8
	ldrb r0, [r6, #7]
	add r1, sp, #4
	bl MOD05_021F5044
	add r6, r0, #0
	beq _021F50F8
	add r0, r7, #0
	mov r1, #0x1a
	bl MOD05_021E7ED8
	cmp r0, #0
	beq _021F50F8
	bl MOD05_021E7EC8
	add r3, r5, #0
	add r7, r0, #0
	add r3, #0xa4
	ldr r3, [r3]
	lsl r4, r4, #3
	ldrb r3, [r3, r4]
	ldr r0, [r5, #0x4c]
	add r1, r7, #0
	mov r2, #0x1a
	bl MOD05_021D9FB4
	add r1, sp, #4
	add r2, r5, #0
	add r2, #0xa4
	ldrb r0, [r1]
	ldr r2, [r2]
	add r3, r7, #0
	strb r0, [r2, r4]
	add r0, r5, #0
	add r0, #0xa4
	ldr r0, [r0]
	mov r2, #1
	add r0, r0, r4
	str r6, [r0, #4]
	ldr r0, [r5, #0x4c]
	str r0, [sp]
	ldrb r1, [r1]
	mov r0, #0x1a
	bl MOD05_021D9DC0
_021F50F8:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F50FC
MOD05_021F50FC: ; 0x021F50FC
	ldr r2, _021F511C ; =UNK05_021FC650
	mov r3, #0
_021F5100:
	lsl r1, r3, #2
	ldr r1, [r2, r1]
	cmp r0, r1
	bne _021F510C
	add r0, r3, #0
	bx lr
_021F510C:
	add r1, r3, #1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, #0x15
	blo _021F5100
	add r0, r3, #0
	bx lr
	nop
_021F511C: .word UNK05_021FC650

	thumb_func_start MOD05_021F5120
MOD05_021F5120: ; 0x021F5120
	cmp r0, #0
	ble _021F512E
	ldr r1, _021F5134 ; =0x00000438
	cmp r0, r1
	bgt _021F512E
	mov r0, #1
	bx lr
_021F512E:
	mov r0, #0
	bx lr
	nop
_021F5134: .word 0x00000438

	thumb_func_start MOD05_021F5138
MOD05_021F5138: ; 0x021F5138
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	lsr r2, r0, #0x18
	add r1, sp, #0
	strb r2, [r1]
	lsr r2, r0, #0x10
	strb r2, [r1, #1]
	lsr r2, r0, #8
	strb r2, [r1, #2]
	strb r0, [r1, #3]
	ldrb r0, [r1]
	mov r1, #0x15
	bl _s32_div_f
	add r0, sp, #0
	strb r1, [r0]
	ldrb r0, [r0, #1]
	mov r1, #0x15
	bl _s32_div_f
	add r0, sp, #0
	strb r1, [r0, #1]
	ldrb r0, [r0, #2]
	mov r1, #0x15
	bl _s32_div_f
	add r0, sp, #0
	strb r1, [r0, #2]
	ldrb r0, [r0, #3]
	mov r1, #0x15
	bl _s32_div_f
	add r0, sp, #0
	strb r1, [r0, #3]
	mov r0, #0
	mov r3, #1
	add r1, sp, #0
	add r2, r0, #0
_021F5184:
	add r5, r2, #0
	cmp r3, #0
	bls _021F51A8
_021F518A:
	ldrb r7, [r1, r5]
	ldrb r6, [r1, r3]
	cmp r7, r6
	bne _021F519E
	add r6, r6, #1
	strb r6, [r1, r3]
	ldrb r6, [r1, r3]
	cmp r6, #0x15
	blo _021F519E
	strb r0, [r1, r3]
_021F519E:
	add r5, r5, #1
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	cmp r5, r3
	blo _021F518A
_021F51A8:
	add r3, r3, #1
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	cmp r3, #4
	blo _021F5184
	mov r2, #0
	add r1, sp, #0
_021F51B6:
	ldrb r0, [r1, r2]
	cmp r4, r0
	bne _021F51C0
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F51C0:
	add r0, r2, #1
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	cmp r2, #4
	blo _021F51B6
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F51D0
MOD05_021F51D0: ; 0x021F51D0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x1c]
	ldr r0, [r0]
	bl MOD05_021F50FC
	add r5, r0, #0
	cmp r5, #0x15
	bne _021F51E6
	bl GF_AssertFail
_021F51E6:
	ldr r0, [r4, #0xc]
	bl FUN_0202A9B0
	bl FUN_0202A9BC
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_0202A9C8
	add r4, r0, #0
	ldrb r1, [r4, #5]
	mov r0, #0x6a
	lsl r2, r1, #2
	ldr r1, _021F5218 ; =UNK05_021FC644
	ldr r1, [r1, r2]
	mov r2, #4
	bl AllocAtEndAndReadWholeNarcMemberByIdPair
	ldrb r1, [r4, #4]
	lsl r1, r1, #2
	ldr r4, [r0, r1]
	bl FreeToHeap
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021F5218: .word UNK05_021FC644

	thumb_func_start MOD05_021F521C
MOD05_021F521C: ; 0x021F521C
	push {r3, lr}
	add r3, r1, #0
	bmi _021F522A
	add r1, r2, #0
	add r2, r3, #0
	bl MOD05_021F5068
_021F522A:
	pop {r3, pc}

	thumb_func_start MOD05_021F522C
MOD05_021F522C: ; 0x021F522C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	bl MOD05_021F50FC
	add r4, r0, #0
	cmp r4, #0x15
	bne _021F5242
	bl GF_AssertFail
_021F5242:
	add r0, r5, #0
	add r0, #0xa4
	ldr r1, [r0]
	lsl r0, r4, #3
	mov r2, #0
	add r0, r1, r0
	str r2, [r0, #4]
	ldr r0, [r5, #0xc]
	bl FUN_0202A9B0
	bl FUN_0202A9BC
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0202A9C8
	mov r1, #0
	str r1, [r0]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F5268
MOD05_021F5268: ; 0x021F5268
	push {r3, r4, r5, lr}
	mov r5, #0
	add r4, r0, #0
	add r0, r1, #0
	add r1, r2, #0
	str r5, [sp]
	add r2, r5, #0
	bl UncompressFromNarc
	str r0, [r4]
	bl NNS_G3dGetMdlSet
	str r0, [r4, #4]
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r0, r0, r1
	str r0, [r4, #8]
	ldr r0, [r4]
	bl NNS_G3dGetTex
	str r0, [r4, #0xc]
	cmp r0, #0
	beq _021F52A4
	mov r2, #1
	ldr r0, _021F52A8 ; =MOD05_021F52AC
	add r1, r4, #0
	lsl r2, r2, #0xa
	bl FUN_0200CA98
_021F52A4:
	pop {r3, r4, r5, pc}
	nop
_021F52A8: .word MOD05_021F52AC

	thumb_func_start MOD05_021F52AC
MOD05_021F52AC: ; 0x021F52AC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	bl FUN_0201B3C4
	ldr r0, [r4]
	ldr r1, [r4, #0xc]
	bl FUN_0201B3A8
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F52C8
MOD05_021F52C8: ; 0x021F52C8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021F52F8
	add r1, sp, #4
	add r2, sp, #0
	bl NNS_G3dTexReleaseTexKey
	ldr r1, _021F5314 ; =NNS_GfdDefaultFuncFreeTexVram
	ldr r0, [sp, #4]
	ldr r1, [r1]
	blx r1
	ldr r1, _021F5314 ; =NNS_GfdDefaultFuncFreeTexVram
	ldr r0, [sp]
	ldr r1, [r1]
	blx r1
	ldr r0, [r4, #0xc]
	bl NNS_G3dPlttReleasePlttKey
	ldr r1, _021F5318 ; =NNS_GfdDefaultFuncFreePlttVram
	ldr r1, [r1]
	blx r1
_021F52F8:
	ldr r0, [r4]
	cmp r0, #0
	beq _021F5302
	bl FreeToHeap
_021F5302:
	mov r1, #0x10
	mov r0, #0
_021F5306:
	strb r0, [r4]
	add r4, r4, #1
	sub r1, r1, #1
	bne _021F5306
	add sp, #8
	pop {r4, pc}
	nop
_021F5314: .word NNS_GfdDefaultFuncFreeTexVram
_021F5318: .word NNS_GfdDefaultFuncFreePlttVram

	thumb_func_start MOD05_021F531C
MOD05_021F531C: ; 0x021F531C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	mov r6, #0
	add r1, r3, #0
	add r5, r0, #0
	add r0, r2, #0
	ldr r3, [sp, #0x18]
	add r2, r6, #0
	str r6, [sp]
	bl UncompressFromNarc
	add r2, r0, #0
	ldr r3, [sp, #0x1c]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F54EC
	add r0, r6, #0
	str r0, [r5, #0x10]
	add sp, #4
	pop {r3, r4, r5, r6, pc}

	thumb_func_start MOD05_021F5348
MOD05_021F5348: ; 0x021F5348
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021F54EC
	mov r0, #1
	str r0, [r4, #0x10]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F5358
MOD05_021F5358: ; 0x021F5358
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F5376
	add r0, r1, #0
	ldr r1, [r4, #8]
	bl NNS_G3dFreeAnmObj
	ldr r0, [r4, #0x10]
	cmp r0, #0
	bne _021F5376
	ldr r0, [r4]
	bl FreeToHeap
_021F5376:
	mov r1, #0x14
	mov r0, #0
_021F537A:
	strb r0, [r4]
	add r4, r4, #1
	sub r1, r1, #1
	bne _021F537A
	pop {r4, pc}

	thumb_func_start MOD05_021F5384
MOD05_021F5384: ; 0x021F5384
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	ldr r0, [r0, #8]
	ldrh r0, [r0, #4]
	lsl r2, r0, #0xc
	cmp r1, #0
	ble _021F53A2
	ldr r0, [r4, #0xc]
	add r0, r0, r1
	add r1, r2, #0
	bl _s32_div_f
	str r1, [r4, #0xc]
	b _021F53B4
_021F53A2:
	ldr r0, [r4, #0xc]
	add r3, r4, #0
	add r3, #0xc
	add r0, r0, r1
	str r0, [r4, #0xc]
	bpl _021F53B4
	ldr r0, [r3]
	add r0, r0, r2
	str r0, [r3]
_021F53B4:
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #8]
	str r1, [r0]
	pop {r4, pc}

	thumb_func_start MOD05_021F53BC
MOD05_021F53BC: ; 0x021F53BC
	push {r3, r4}
	ldr r2, [r0, #8]
	ldr r3, [r0, #0xc]
	ldr r2, [r2, #8]
	ldrh r2, [r2, #4]
	lsl r4, r2, #0xc
	mov r2, #0
	cmp r1, #0
	ble _021F53DE
	add r1, r3, r1
	cmp r1, r4
	bge _021F53D8
	str r1, [r0, #0xc]
	b _021F53EA
_021F53D8:
	str r4, [r0, #0xc]
	mov r2, #1
	b _021F53EA
_021F53DE:
	add r1, r3, r1
	bmi _021F53E6
	str r1, [r0, #0xc]
	b _021F53EA
_021F53E6:
	str r2, [r0, #0xc]
	mov r2, #1
_021F53EA:
	ldr r1, [r0, #0xc]
	ldr r0, [r0, #8]
	str r1, [r0]
	add r0, r2, #0
	pop {r3, r4}
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F53F8
MOD05_021F53F8: ; 0x021F53F8
	str r1, [r0, #0xc]
	ldr r0, [r0, #8]
	str r1, [r0]
	bx lr

	thumb_func_start MOD05_021F5400
MOD05_021F5400: ; 0x021F5400
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r1, #0
	mov r2, #0x78
	add r4, r0, #0
	bl memset
	ldr r1, [r5, #8]
	add r0, r4, #0
	bl NNS_G3dRenderObjInit
	mov r0, #1
	str r0, [r4, #0x6c]
	lsl r0, r0, #0xc
	str r0, [r4, #0x60]
	str r0, [r4, #0x64]
	str r0, [r4, #0x68]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F5424
MOD05_021F5424: ; 0x021F5424
	ldr r3, _021F542C ; =NNS_G3dRenderObjAddAnmObj
	ldr r1, [r1, #8]
	bx r3
	nop
_021F542C: .word NNS_G3dRenderObjAddAnmObj

	thumb_func_start MOD05_021F5430
MOD05_021F5430: ; 0x021F5430
	push {r4, lr}
	sub sp, #0x48
	add r4, r0, #0
	ldr r0, [r4, #0x6c]
	cmp r0, #0
	beq _021F54C4
	add r0, sp, #0x24
	bl MTX_Identity33_
	add r0, r4, #0
	add r0, #0x70
	ldrh r0, [r0]
	ldr r3, _021F54C8 ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0
	bl MTX_RotX33_
	add r1, sp, #0x24
	add r0, sp, #0
	add r2, r1, #0
	bl MTX_Concat33
	add r0, r4, #0
	add r0, #0x74
	ldrh r0, [r0]
	ldr r3, _021F54C8 ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0
	bl MTX_RotZ33_
	add r1, sp, #0x24
	add r0, sp, #0
	add r2, r1, #0
	bl MTX_Concat33
	add r0, r4, #0
	add r0, #0x72
	ldrh r0, [r0]
	ldr r3, _021F54C8 ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0
	bl MTX_RotY33_
	add r1, sp, #0x24
	add r0, sp, #0
	add r2, r1, #0
	bl MTX_Concat33
	add r1, r4, #0
	add r0, r4, #0
	add r4, #0x60
	add r1, #0x54
	add r2, sp, #0x24
	add r3, r4, #0
	bl FUN_0201B26C
_021F54C4:
	add sp, #0x48
	pop {r4, pc}
	.balign 4, 0
_021F54C8: .word FX_SinCosTable_

	thumb_func_start MOD05_021F54CC
MOD05_021F54CC: ; 0x021F54CC
	str r1, [r0, #0x6c]
	bx lr

	thumb_func_start MOD05_021F54D0
MOD05_021F54D0: ; 0x021F54D0
	str r1, [r0, #0x54]
	str r2, [r0, #0x58]
	str r3, [r0, #0x5c]
	bx lr

	thumb_func_start MOD05_021F54D8
MOD05_021F54D8: ; 0x021F54D8
	str r1, [r0, #0x60]
	str r2, [r0, #0x64]
	str r3, [r0, #0x68]
	bx lr

	thumb_func_start MOD05_021F54E0
MOD05_021F54E0: ; 0x021F54E0
	lsl r2, r2, #1
	add r0, r0, r2
	add r0, #0x70
	strh r1, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F54EC
MOD05_021F54EC: ; 0x021F54EC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	str r2, [r5]
	add r0, r2, #0
	mov r1, #0
	add r6, r3, #0
	bl NNS_G3dGetAnmByIdx
	str r0, [r5, #4]
	ldr r1, [r5, #4]
	ldr r2, [r4, #8]
	add r0, r6, #0
	bl NNS_G3dAllocAnmObj
	str r0, [r5, #8]
	ldr r1, [r5, #4]
	ldr r2, [r4, #8]
	ldr r3, [r4, #0xc]
	bl NNS_G3dAnmObjInit
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F5518
MOD05_021F5518: ; 0x021F5518
	push {r3, r4, lr}
	sub sp, #4
	ldr r0, [r1, #8]
	add r4, r2, #0
	bl MOD05_021F5608
	add r0, r4, #0
	mov r1, #0
	mov r2, #0xa
	mov r3, #0x13
	bl MOD05_021F5660
	mov r3, #0
	str r3, [r4, #0x14]
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _021F555C ; =0x04000050
	mov r1, #4
	mov r2, #0x29
	bl G2x_SetBlendAlpha_
	mov r0, #2
	mov r1, #0
	bl FUN_020178BC
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, _021F5560 ; =0x00000648
	bl FUN_020054C8
	add sp, #4
	pop {r3, r4, pc}
	.balign 4, 0
_021F555C: .word 0x04000050
_021F5560: .word 0x00000648

	thumb_func_start MOD05_021F5564
MOD05_021F5564: ; 0x021F5564
	push {r3, r4, lr}
	sub sp, #4
	ldr r0, [r1, #8]
	add r4, r2, #0
	bl MOD05_021F5608
	add r0, r4, #0
	mov r1, #0xa
	mov r2, #0
	mov r3, #0xf
	bl MOD05_021F5660
	mov r0, #0
	str r0, [r4, #0x14]
	mov r0, #6
	str r0, [sp]
	ldr r0, _021F5594 ; =0x04000050
	mov r1, #4
	mov r2, #0x21
	mov r3, #0xa
	bl G2x_SetBlendAlpha_
	add sp, #4
	pop {r3, r4, pc}
	.balign 4, 0
_021F5594: .word 0x04000050

	thumb_func_start MOD05_021F5598
MOD05_021F5598: ; 0x021F5598
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F559C
MOD05_021F559C: ; 0x021F559C
	push {r4, lr}
	add r4, r2, #0
	ldr r0, [r4, #0x14]
	cmp r0, #1
	beq _021F55C2
	add r0, r4, #0
	bl MOD05_021F5670
	cmp r0, #0
	beq _021F55B4
	mov r0, #1
	str r0, [r4, #0x14]
_021F55B4:
	ldr r1, [r4]
	mov r0, #0x10
	sub r0, r0, r1
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _021F55C4 ; =0x04000052
	strh r1, [r0]
_021F55C2:
	pop {r4, pc}
	.balign 4, 0
_021F55C4: .word 0x04000052

	thumb_func_start MOD05_021F55C8
MOD05_021F55C8: ; 0x021F55C8
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F55CC
MOD05_021F55CC: ; 0x021F55CC
	ldr r0, [r0, #4]
	ldr r3, _021F55D8 ; =MOD05_021D8024
	ldr r0, [r0, #4]
	ldr r1, _021F55DC ; =UNK05_021FC6C0
	bx r3
	nop
_021F55D8: .word MOD05_021D8024
_021F55DC: .word UNK05_021FC6C0

	thumb_func_start MOD05_021F55E0
MOD05_021F55E0: ; 0x021F55E0
	ldr r3, _021F55E4 ; =MOD05_021D80A4
	bx r3
	.balign 4, 0
_021F55E4: .word MOD05_021D80A4

	thumb_func_start MOD05_021F55E8
MOD05_021F55E8: ; 0x021F55E8
	push {r3, lr}
	bl MOD05_021D80E4
	ldr r0, [r0, #0x14]
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F55F4
MOD05_021F55F4: ; 0x021F55F4
	ldr r0, [r0, #4]
	ldr r3, _021F5600 ; =MOD05_021D8024
	ldr r0, [r0, #4]
	ldr r1, _021F5604 ; =UNK05_021FC6A8
	bx r3
	nop
_021F5600: .word MOD05_021D8024
_021F5604: .word UNK05_021FC6A8

	thumb_func_start MOD05_021F5608
MOD05_021F5608: ; 0x021F5608
	push {r3, r4, r5, lr}
	sub sp, #8
	ldr r1, _021F5658 ; =0x00005D5F
	add r5, r0, #0
	add r0, sp, #4
	strh r1, [r0]
	mov r0, #2
	add r1, sp, #4
	add r2, r0, #0
	mov r3, #0xc2
	bl FUN_02017FB4
	mov r0, #4
	mov r1, #0x20
	bl AllocFromHeap
	mov r1, #0x11
	mov r2, #0x20
	add r4, r0, #0
	bl memset
	mov r0, #1
	str r0, [sp]
	add r0, r5, #0
	mov r1, #2
	add r2, r4, #0
	mov r3, #0x20
	bl FUN_02017E14
	add r0, r4, #0
	bl FreeToHeap
	ldr r2, _021F565C ; =0x00006001
	add r0, r5, #0
	mov r1, #2
	bl FUN_02018768
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_021F5658: .word 0x00005D5F
_021F565C: .word 0x00006001

	thumb_func_start MOD05_021F5660
MOD05_021F5660: ; 0x021F5660
	str r1, [r0]
	str r1, [r0, #4]
	sub r1, r2, r1
	str r1, [r0, #8]
	str r3, [r0, #0x10]
	mov r1, #0
	str r1, [r0, #0xc]
	bx lr

	thumb_func_start MOD05_021F5670
MOD05_021F5670: ; 0x021F5670
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #8]
	ldr r0, [r4, #0xc]
	mul r0, r1
	ldr r1, [r4, #0x10]
	bl _s32_div_f
	ldr r1, [r4, #4]
	add r0, r0, r1
	str r0, [r4]
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	add r0, r0, #1
	cmp r0, r1
	bgt _021F5696
	str r0, [r4, #0xc]
	mov r0, #0
	pop {r4, pc}
_021F5696:
	str r1, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD05_021F569C
MOD05_021F569C: ; 0x021F569C
	ldr r3, _021F56A4 ; =FUN_02017FE4
	mov r0, #2
	mov r1, #0
	bx r3
	.balign 4, 0
_021F56A4: .word FUN_02017FE4

	thumb_func_start MOD05_021F56A8
MOD05_021F56A8: ; 0x021F56A8
	ldr r3, _021F56B0 ; =FUN_02017FE4
	mov r0, #2
	ldr r1, _021F56B4 ; =0x00007FFF
	bx r3
	.balign 4, 0
_021F56B0: .word FUN_02017FE4
_021F56B4: .word 0x00007FFF

	thumb_func_start MOD05_021F56B8
MOD05_021F56B8: ; 0x021F56B8
	push {r4, lr}
	sub sp, #8
	ldr r1, _021F5710 ; =0x00007FFF
	add r4, r0, #0
	add r0, sp, #4
	strh r1, [r0]
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r1, _021F5714 ; =0x0400000C
	mov r0, #3
	ldrh r2, [r1]
	mov r3, #0xc4
	bic r2, r0
	mov r0, #3
	orr r0, r2
	strh r0, [r1]
	mov r0, #2
	add r1, sp, #4
	add r2, r0, #0
	bl FUN_02017FB4
	mov r1, #2
	str r1, [sp]
	ldr r0, [r4, #8]
	add r2, r1, #0
	mov r3, #1
	bl FUN_02017F48
	ldr r0, [r4, #8]
	ldr r2, _021F5718 ; =0x00006002
	mov r1, #2
	bl FUN_02018768
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	add r0, r4, #0
	bl MOD05_021F569C
	add sp, #8
	pop {r4, pc}
	.balign 4, 0
_021F5710: .word 0x00007FFF
_021F5714: .word 0x0400000C
_021F5718: .word 0x00006002

	thumb_func_start MOD05_021F571C
MOD05_021F571C: ; 0x021F571C
	push {r4, lr}
	sub sp, #8
	ldr r1, _021F5774 ; =0x00007FFF
	add r4, r0, #0
	add r0, sp, #4
	strh r1, [r0]
	mov r0, #8
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r1, _021F5778 ; =0x0400000E
	mov r0, #3
	ldrh r2, [r1]
	mov r3, #0xc4
	bic r2, r0
	mov r0, #3
	orr r2, r0
	strh r2, [r1]
	add r1, sp, #4
	mov r2, #2
	bl FUN_02017FB4
	mov r2, #2
	str r2, [sp]
	ldr r0, [r4, #8]
	mov r1, #3
	mov r3, #1
	bl FUN_02017F48
	ldr r0, [r4, #8]
	ldr r2, _021F577C ; =0x00006002
	mov r1, #3
	bl FUN_02018768
	mov r0, #8
	mov r1, #1
	bl GX_EngineAToggleLayers
	add r0, r4, #0
	bl MOD05_021F569C
	add sp, #8
	pop {r4, pc}
	nop
_021F5774: .word 0x00007FFF
_021F5778: .word 0x0400000E
_021F577C: .word 0x00006002

	thumb_func_start MOD05_021F5780
MOD05_021F5780: ; 0x021F5780
	push {r3, lr}
	ldr r0, [r0, #4]
	ldr r0, [r0, #0xc]
	bl MOD05_021DC1D0
	ldr r3, _021F57A4 ; =UNK05_021FC6A4
	mov r2, #0
_021F578E:
	ldr r1, [r3]
	cmp r0, r1
	bne _021F5798
	mov r0, #1
	pop {r3, pc}
_021F5798:
	add r2, r2, #1
	add r3, r3, #4
	cmp r2, #1
	blt _021F578E
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0
_021F57A4: .word UNK05_021FC6A4

	thumb_func_start MOD05_021F57A8
MOD05_021F57A8: ; 0x021F57A8
	push {r3, lr}
	ldr r0, [r0, #4]
	ldr r0, [r0, #0xc]
	bl MOD05_021DC1D0
	ldr r3, _021F57CC ; =UNK05_021FC6D8
	mov r2, #0
_021F57B6:
	ldr r1, [r3]
	cmp r0, r1
	bne _021F57C0
	mov r0, #0
	pop {r3, pc}
_021F57C0:
	add r2, r2, #1
	add r3, r3, #4
	cmp r2, #0x10
	blt _021F57B6
	mov r0, #1
	pop {r3, pc}
	.balign 4, 0
_021F57CC: .word UNK05_021FC6D8

	thumb_func_start MOD05_021F57D0
MOD05_021F57D0: ; 0x021F57D0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F57E2
	bl MOD05_021F55E0
	mov r0, #0
	str r0, [r4]
_021F57E2:
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F57EC
MOD05_021F57EC: ; 0x021F57EC
	mov r0, #0xc
	bx lr

	thumb_func_start MOD05_021F57F0
MOD05_021F57F0: ; 0x021F57F0
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl FUN_02046528
	add r5, r0, #0
	add r0, r6, #0
	bl FUN_0204652C
	add r4, r0, #0
	ldrh r1, [r4, #8]
	cmp r1, #9
	bls _021F580A
	b _021F597C
_021F580A:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021F5816: ; jump table
	.short _021F582A - _021F5816 - 2 ; case 0
	.short _021F5856 - _021F5816 - 2 ; case 1
	.short _021F5872 - _021F5816 - 2 ; case 2
	.short _021F5888 - _021F5816 - 2 ; case 3
	.short _021F58DA - _021F5816 - 2 ; case 4
	.short _021F58EE - _021F5816 - 2 ; case 5
	.short _021F5914 - _021F5816 - 2 ; case 6
	.short _021F5936 - _021F5816 - 2 ; case 7
	.short _021F5956 - _021F5816 - 2 ; case 8
	.short _021F5968 - _021F5816 - 2 ; case 9
_021F582A:
	add r0, r5, #0
	bl MOD05_021F57A8
	cmp r0, #1
	bne _021F584C
	mov r0, #1
	strh r0, [r4, #8]
	add r0, r5, #0
	bl MOD05_021F5780
	str r0, [r4, #4]
	cmp r0, #0
	beq _021F587C
	add r0, r5, #0
	bl MOD05_021F56A8
	b _021F5980
_021F584C:
	mov r0, #7
	strh r0, [r4, #8]
	mov r0, #0x14
	strh r0, [r4, #0xa]
	b _021F5980
_021F5856:
	add r0, r5, #0
	bl MOD05_021F55CC
	str r0, [r4]
	mov r0, #2
	mov r1, #0
	strh r0, [r4, #8]
	bl FUN_020178BC
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	b _021F5980
_021F5872:
	ldr r0, [r4]
	bl MOD05_021F55E8
	cmp r0, #0
	bne _021F587E
_021F587C:
	b _021F5980
_021F587E:
	mov r0, #0x16
	strh r0, [r4, #0xa]
	mov r0, #3
	strh r0, [r4, #8]
	b _021F5980
_021F5888:
	mov r0, #0xa
	ldrsh r0, [r4, r0]
	sub r0, r0, #1
	strh r0, [r4, #0xa]
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	bl MapHeader_HasWildEncounters
	cmp r0, #0
	beq _021F58D4
	mov r0, #0xa
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bge _021F5980
	ldr r0, [r5, #0x38]
	bl FUN_02055320
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl FUN_0205532C
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl FUN_0204A6E0
	add r1, r0, #0
	add r0, r5, #0
	bl MOD06_0223CDB8
	cmp r0, #0
	beq _021F58CE
	mov r0, #6
	strh r0, [r4, #8]
	b _021F5980
_021F58CE:
	mov r0, #4
	strh r0, [r4, #8]
	b _021F5980
_021F58D4:
	mov r0, #4
	strh r0, [r4, #8]
	b _021F5980
_021F58DA:
	ldr r0, [r4]
	bl MOD05_021F55E0
	add r0, r5, #0
	bl MOD05_021F55F4
	str r0, [r4]
	mov r0, #5
	strh r0, [r4, #8]
	b _021F5980
_021F58EE:
	ldr r0, [r4]
	bl MOD05_021F55E8
	cmp r0, #0
	beq _021F5980
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, _021F5984 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	mov r0, #2
	mov r1, #3
	bl FUN_020178BC
	mov r0, #8
	strh r0, [r4, #8]
	b _021F5980
_021F5914:
	bl MOD05_021F57D0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021F5924
	add r0, r5, #0
	bl MOD05_021F571C
_021F5924:
	add r0, r5, #0
	add r1, r6, #0
	bl MOD06_0223BE70
	cmp r0, #0
	bne _021F5980
	bl GF_AssertFail
	b _021F5980
_021F5936:
	mov r0, #0xa
	ldrsh r1, [r4, r0]
	sub r1, r1, #1
	strh r1, [r4, #0xa]
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bge _021F5980
	mov r2, #0
	ldr r1, _021F5988 ; =0x000007ED
	add r0, r6, #0
	add r3, r2, #0
	bl FUN_02038CD8
	mov r0, #9
	strh r0, [r4, #8]
	b _021F5980
_021F5956:
	mov r2, #0
	ldr r1, _021F598C ; =0x000007EC
	add r0, r6, #0
	add r3, r2, #0
	bl FUN_02038CD8
	mov r0, #9
	strh r0, [r4, #8]
	b _021F5980
_021F5968:
	bl MOD05_021F57D0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021F5978
	add r0, r5, #0
	bl MOD05_021F56B8
_021F5978:
	mov r0, #1
	pop {r4, r5, r6, pc}
_021F597C:
	bl GF_AssertFail
_021F5980:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F5984: .word 0x04000050
_021F5988: .word 0x000007ED
_021F598C: .word 0x000007EC

	thumb_func_start MOD05_021F5990
MOD05_021F5990: ; 0x021F5990
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r2, #0
	lsl r2, r3, #3
	add r6, r5, r2
	add r6, #0x18
	str r2, [sp, #8]
	add r2, r6, #0
	str r0, [sp]
	add r7, r1, #0
	str r3, [sp, #4]
	bl FUN_0201681C
	cmp r0, #1
	beq _021F59B2
	bl GF_AssertFail
_021F59B2:
	sub r5, r6, r5
	add r0, r7, #0
	add r1, r5, #0
	bl AllocFromHeap
	add r4, r0, #0
	bne _021F59C4
	bl GF_AssertFail
_021F59C4:
	add r0, r4, #0
	mov r1, #0
	add r2, r5, #0
	bl memset
	ldr r0, [sp]
	str r0, [r4]
	ldr r0, [sp, #4]
	str r7, [r4, #4]
	str r0, [r4, #8]
	ldr r0, [sp, #8]
	str r6, [r4, #0xc]
	str r0, [r4, #0x10]
	add r0, r4, #0
	add r0, #0x18
	str r0, [r4, #0x14]
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F59EC
MOD05_021F59EC: ; 0x021F59EC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r4, [r6, #8]
	ldr r5, [r6, #0x14]
	cmp r4, #0
	beq _021F5A0E
_021F59F8:
	ldr r0, [r5]
	cmp r0, #0
	beq _021F5A06
	ldr r1, [r5, #4]
	add r0, r6, #0
	bl MOD05_021F5A74
_021F5A06:
	sub r4, r4, #1
	add r5, #8
	cmp r4, #0
	bne _021F59F8
_021F5A0E:
	ldr r4, [r6, #4]
	add r0, r6, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_020168D0
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F5A20
MOD05_021F5A20: ; 0x021F5A20
	ldr r3, _021F5A24 ; =MOD05_021F5B14
	bx r3
	.balign 4, 0
_021F5A24: .word MOD05_021F5B14

	thumb_func_start MOD05_021F5A28
MOD05_021F5A28: ; 0x021F5A28
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MOD05_021F5B5C
	str r0, [sp]
	cmp r0, #0
	bne _021F5A40
	bl GF_AssertFail
_021F5A40:
	add r0, r5, #0
	add r1, r6, #0
	add r2, r7, #0
	bl MOD05_021F5B14
	add r5, r0, #0
	ldr r0, [sp]
	add r1, r4, #0
	add r2, r5, #0
	bl MOD05_021F5B8C
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F5A5C
MOD05_021F5A5C: ; 0x021F5A5C
	push {r4, lr}
	add r4, r1, #0
	bl MOD05_021F5B74
	cmp r0, #0
	beq _021F5A6C
	bl MOD05_021F5B94
_021F5A6C:
	add r0, r4, #0
	bl MOD05_021F5B34
	pop {r4, pc}

	thumb_func_start MOD05_021F5A74
MOD05_021F5A74: ; 0x021F5A74
	push {r4, lr}
	bl MOD05_021F5B3C
	add r4, r0, #0
	bne _021F5A82
	bl GF_AssertFail
_021F5A82:
	ldr r0, [r4]
	bl MOD05_021F5B34
	add r0, r4, #0
	bl MOD05_021F5B94
	pop {r4, pc}

	thumb_func_start MOD05_021F5A90
MOD05_021F5A90: ; 0x021F5A90
	push {r4, lr}
	bl MOD05_021F5B3C
	add r4, r0, #0
	bne _021F5A9E
	bl GF_AssertFail
_021F5A9E:
	ldr r0, [r4]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F5AA4
MOD05_021F5AA4: ; 0x021F5AA4
	push {r3, lr}
	bl MOD05_021F5B3C
	cmp r0, #0
	beq _021F5AB2
	mov r0, #1
	pop {r3, pc}
_021F5AB2:
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F5AB8
MOD05_021F5AB8: ; 0x021F5AB8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r4, r2, #0
	add r6, r0, #0
	add r7, r3, #0
	add r0, r5, #0
	add r1, r4, #0
	bl NARC_GetMemberSize
	add r1, r0, #0
	add r0, r6, #0
	add r2, r7, #0
	bl MOD05_021F5A20
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl NARC_ReadWholeMember
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F5AE4
MOD05_021F5AE4: ; 0x021F5AE4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r2, #0
	add r5, r0, #0
	add r7, r3, #0
	add r6, r1, #0
	add r0, r4, #0
	add r1, r7, #0
	bl NARC_GetMemberSize
	add r2, r0, #0
	ldr r3, [sp, #0x18]
	add r0, r5, #0
	add r1, r6, #0
	bl MOD05_021F5A28
	add r5, r0, #0
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	bl NARC_ReadWholeMember
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F5B14
MOD05_021F5B14: ; 0x021F5B14
	push {r4, lr}
	cmp r2, #0
	ldr r0, [r0, #4]
	bne _021F5B22
	bl AllocFromHeap
	b _021F5B26
_021F5B22:
	bl AllocFromHeapAtEnd
_021F5B26:
	add r4, r0, #0
	cmp r4, #0
	bne _021F5B30
	bl GF_AssertFail
_021F5B30:
	add r0, r4, #0
	pop {r4, pc}

	thumb_func_start MOD05_021F5B34
MOD05_021F5B34: ; 0x021F5B34
	ldr r3, _021F5B38 ; =FreeToHeap
	bx r3
	.balign 4, 0
_021F5B38: .word FreeToHeap

	thumb_func_start MOD05_021F5B3C
MOD05_021F5B3C: ; 0x021F5B3C
	ldr r3, [r0, #8]
	ldr r0, [r0, #0x14]
	cmp r3, #0
	beq _021F5B56
_021F5B44:
	ldr r2, [r0]
	cmp r2, #0
	beq _021F5B50
	ldr r2, [r0, #4]
	cmp r2, r1
	beq _021F5B58
_021F5B50:
	add r0, #8
	sub r3, r3, #1
	bne _021F5B44
_021F5B56:
	mov r0, #0
_021F5B58:
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F5B5C
MOD05_021F5B5C: ; 0x021F5B5C
	ldr r2, [r0, #8]
	ldr r0, [r0, #0x14]
	cmp r2, #0
	beq _021F5B70
_021F5B64:
	ldr r1, [r0]
	cmp r1, #0
	beq _021F5B72
	add r0, #8
	sub r2, r2, #1
	bne _021F5B64
_021F5B70:
	mov r0, #0
_021F5B72:
	bx lr

	thumb_func_start MOD05_021F5B74
MOD05_021F5B74: ; 0x021F5B74
	ldr r3, [r0, #8]
	ldr r0, [r0, #0x14]
	cmp r3, #0
	beq _021F5B88
_021F5B7C:
	ldr r2, [r0]
	cmp r2, r1
	beq _021F5B8A
	add r0, #8
	sub r3, r3, #1
	bne _021F5B7C
_021F5B88:
	mov r0, #0
_021F5B8A:
	bx lr

	thumb_func_start MOD05_021F5B8C
MOD05_021F5B8C: ; 0x021F5B8C
	str r2, [r0]
	str r1, [r0, #4]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F5B94
MOD05_021F5B94: ; 0x021F5B94
	mov r1, #0
	str r1, [r0]
	str r1, [r0, #4]
	bx lr

	thumb_func_start MOD05_021F5B9C
MOD05_021F5B9C: ; 0x021F5B9C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	bl FUN_02050DF0
	add r7, r0, #0
	beq _021F5C40
	bl MOD18_0223E2C4
	add r6, r0, #0
	bl MOD18_0223E2DC
	lsl r1, r6, #0x15
	lsl r0, r0, #0x15
	mov r4, #0
	str r1, [sp, #0xc]
	str r0, [sp, #8]
_021F5BC0:
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_020267C4
	add r6, r0, #0
	bl FUN_0204CA80
	str r0, [sp, #0x10]
	add r0, r6, #0
	bl FUN_0204CA90
	str r0, [sp, #0x14]
	cmp r6, #0
	beq _021F5C3A
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_02026810
	str r0, [sp, #0x18]
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_02026840
	mov r2, #1
	ldr r1, [sp, #0x18]
	lsl r2, r2, #0xc
	str r2, [sp, #0x20]
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	ldr r2, [sp, #0xc]
	str r1, [sp, #0x1c]
	add r1, r1, r2
	ldr r2, [sp, #8]
	str r0, [sp, #0x24]
	add r0, r0, r2
	ldr r2, [sp, #0x10]
	str r1, [sp, #0x1c]
	lsl r2, r2, #0xf
	add r1, r1, r2
	str r1, [sp, #0x1c]
	ldr r1, [sp, #0x14]
	str r0, [sp, #0x24]
	lsl r1, r1, #0xf
	add r0, r0, r1
	str r0, [sp, #0x24]
	ldr r0, [r5, #0x2c]
	add r1, r6, #0
	bl MOD05_021F4CD4
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, [r5, #0x4c]
	add r3, sp, #0x1c
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r5, #0x2c]
	bl MOD05_021E7FBC
_021F5C3A:
	add r4, r4, #1
	cmp r4, #0x20
	blt _021F5BC0
_021F5C40:
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}


	thumb_func_start MOD05_021F5C44
MOD05_021F5C44: ; 0x021F5C44
	push {r3, r4, r5, lr}
	add r0, r1, #0
	mov r1, #0x18
	add r5, r2, #0
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	add r2, r4, #0
	mov r1, #0x18
	mov r0, #0
_021F5C58:
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _021F5C58
	add r0, r5, #0
	str r5, [r4, #0xc]
	bl MOD05_021F61B0
	str r0, [r4, #4]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5C70
MOD05_021F5C70: ; 0x021F5C70
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	bl FUN_02046528
	add r4, r0, #0
	add r0, r6, #0
	bl FUN_0204652C
	add r5, r0, #0
	ldr r0, [r5]
	cmp r0, #0
	beq _021F5C8E
	cmp r0, #1
	beq _021F5CBA
	b _021F5D28
_021F5C8E:
	ldr r0, [r4, #0x34]
	bl FUN_02058780
	mov r0, #0
	str r0, [r5, #0x10]
	add r2, r5, #0
	ldr r1, [r5, #0xc]
	add r0, r4, #0
	add r2, #0x10
	bl MOD06_0223BD14
	str r0, [r5, #8]
	ldr r1, [r5, #0xc]
	ldr r2, [r5, #8]
	add r0, r4, #0
	bl MOD05_021F5D2C
	str r0, [r5, #0x14]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021F5D28
_021F5CBA:
	ldr r0, [r5, #0x14]
	bl MOD05_021F5D50
	cmp r0, #1
	bne _021F5D28
	ldr r0, [r5, #0x14]
	bl MOD05_021F5D5C
	add r7, r0, #0
	ldr r0, [r5, #0x14]
	bl MOD05_021F5D68
	cmp r7, #1
	ldr r0, [r5, #0x10]
	bne _021F5D10
	ldr r0, [r0, #8]
	mov r1, #0
	bl GetPartyMonByIndex
	ldr r2, [r5, #4]
	add r3, r0, #0
	lsl r2, r2, #0x10
	add r0, r4, #0
	mov r1, #1
	lsr r2, r2, #0x10
	bl FUN_02061208
	ldr r0, [r4, #0xc]
	bl FUN_02029FC8
	mov r1, #0xa
	bl FUN_0202A0E8
	ldr r2, [r5, #0x10]
	add r0, r4, #0
	add r1, r6, #0
	bl FUN_02046A20
	add r0, r5, #0
	bl FreeToHeap
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F5D10:
	cmp r0, #0
	beq _021F5D18
	bl FUN_02047964
_021F5D18:
	ldr r0, [r4, #0x34]
	bl FUN_020587B0
	add r0, r5, #0
	bl FreeToHeap
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F5D28:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021F5D2C
MOD05_021F5D2C: ; 0x021F5D2C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x4c
	add r4, r1, #0
	add r6, r2, #0
	bl MOD05_021F6074
	add r1, r0, #0
	str r5, [r1, #0x20]
	str r4, [r1, #0x1c]
	ldr r0, _021F5D4C ; =MOD05_021F5D7C
	mov r2, #0x80
	str r6, [r1]
	bl FUN_0200CA44
	pop {r4, r5, r6, pc}
	.align 2, 0
_021F5D4C: .word MOD05_021F5D7C

	thumb_func_start MOD05_021F5D50
MOD05_021F5D50: ; 0x021F5D50
	push {r3, lr}
	bl FUN_0201B6C8
	ldr r0, [r0, #4]
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5D5C
MOD05_021F5D5C: ; 0x021F5D5C
	push {r3, lr}
	bl FUN_0201B6C8
	ldr r0, [r0, #8]
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5D68
MOD05_021F5D68: ; 0x021F5D68
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0201B6C8
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
	pop {r4, pc}

	thumb_func_start MOD05_021F5D7C
MOD05_021F5D7C: ; 0x021F5D7C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x20]
	ldr r6, [r0, #0x38]
	add r0, r6, #0
	bl FUN_020553A0
	ldr r7, _021F5DA4 ; =UNK05_021FC9B8
	add r4, r0, #0
_021F5D8E:
	ldr r3, [r5, #0xc]
	add r0, r5, #0
	lsl r3, r3, #2
	ldr r3, [r7, r3]
	add r1, r6, #0
	add r2, r4, #0
	blx r3
	cmp r0, #0
	bne _021F5D8E
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F5DA4: .word UNK05_021FC9B8

	thumb_func_start MOD05_021F5DA8
MOD05_021F5DA8: ; 0x021F5DA8
	push {r3, r4, r5, lr}
	add r4, r2, #0
	add r5, r0, #0
	bl MOD05_021F60C4
	add r0, r4, #0
	bl FUN_02058914
	mov r0, #1
	str r0, [r5, #0xc]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5DC0
MOD05_021F5DC0: ; 0x021F5DC0
	push {r4, r5, r6, lr}
	add r6, r2, #0
	add r5, r0, #0
	add r0, r6, #0
	add r4, r1, #0
	bl FUN_0205AD98
	cmp r0, #1
	bne _021F5DF2
	add r0, r6, #0
	bl FUN_0205AE50
	add r0, r4, #0
	mov r1, #0x20
	bl MOD05_021E5FD8
	add r0, r4, #0
	bl MOD05_021E5FE0
	add r0, r6, #0
	mov r1, #1
	bl FUN_02058544
	mov r0, #2
	str r0, [r5, #0xc]
_021F5DF2:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5DF8
MOD05_021F5DF8: ; 0x021F5DF8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	cmp r0, #0xa
	bne _021F5E0E
	mov r0, #0x65
	lsl r0, r0, #4
	bl FUN_020054C8
_021F5E0E:
	ldr r0, [r4, #0x10]
	cmp r0, #0x22
	bge _021F5E18
	mov r0, #0
	pop {r4, pc}
_021F5E18:
	ldr r0, [r4]
	cmp r0, #1
	bne _021F5E22
	mov r0, #3
	b _021F5E24
_021F5E22:
	mov r0, #0xc
_021F5E24:
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4, #0x10]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5E30
MOD05_021F5E30: ; 0x021F5E30
	push {r4, lr}
	add r4, r0, #0
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r0, r0, #0x1e
	sub r0, r0, r1
	mov r2, #0x1e
	ror r0, r2
	add r0, r1, r0
	add r0, r0, #1
	add r1, r0, #0
	mul r1, r2
	str r1, [r4, #0x14]
	ldr r0, [r4, #0x1c]
	lsl r1, r0, #2
	ldr r0, _021F5E60 ; =UNK05_021FC9AC
	ldr r0, [r0, r1]
	str r0, [r4, #0x18]
	mov r0, #4
	str r0, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}
	nop
_021F5E60: .word UNK05_021FC9AC

	thumb_func_start MOD05_021F5E64
MOD05_021F5E64: ; 0x021F5E64
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x14]
	add r4, r2, #0
	sub r0, r0, #1
	str r0, [r5, #0x14]
	bl MOD05_021F6098
	cmp r0, #1
	bne _021F5E80
	mov r0, #0xa
	str r0, [r5, #0xc]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F5E80:
	ldr r0, [r5, #0x14]
	cmp r0, #0
	ble _021F5E8A
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F5E8A:
	add r0, r4, #0
	mov r1, #2
	bl FUN_02058544
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl MOD05_021E7AC0
	str r0, [r5, #0x24]
	mov r0, #5
	str r0, [r5, #0xc]
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5EA8
MOD05_021F5EA8: ; 0x021F5EA8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	sub r0, r0, #1
	str r0, [r4, #0x18]
	bl MOD05_021F6098
	cmp r0, #1
	bne _021F5EC2
	mov r0, #6
	str r0, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}
_021F5EC2:
	ldr r0, [r4, #0x18]
	cmp r0, #0
	ble _021F5ECC
	mov r0, #0
	pop {r4, pc}
_021F5ECC:
	mov r0, #0xb
	str r0, [r4, #0xc]
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD05_021F5ED4
MOD05_021F5ED4: ; 0x021F5ED4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x24]
	add r4, r2, #0
	bl FUN_02064520
	mov r0, #0
	str r0, [r5, #0x24]
	add r0, r4, #0
	mov r1, #3
	bl FUN_02058544
	mov r0, #0
	str r0, [r5, #0x10]
	mov r1, #7
	str r1, [r5, #0xc]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5EF8
MOD05_021F5EF8: ; 0x021F5EF8
	push {r3, lr}
	ldr r1, [r0, #0x10]
	add r1, r1, #1
	str r1, [r0, #0x10]
	cmp r1, #0xf
	ble _021F5F12
	mov r1, #0
	str r1, [r0, #0x10]
	mov r1, #8
	str r1, [r0, #0xc]
	mov r1, #0x39
	bl MOD05_021F6140
_021F5F12:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5F18
MOD05_021F5F18: ; 0x021F5F18
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021F617C
	cmp r0, #0
	bne _021F5F28
	mov r0, #0
	pop {r4, pc}
_021F5F28:
	mov r0, #9
	str r0, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD05_021F5F30
MOD05_021F5F30: ; 0x021F5F30
	mov r2, #1
	str r2, [r0, #8]
	mov r1, #0xf
	str r1, [r0, #0xc]
	add r0, r2, #0
	bx lr

	thumb_func_start MOD05_021F5F3C
MOD05_021F5F3C: ; 0x021F5F3C
	push {r4, lr}
	add r4, r0, #0
	add r0, r2, #0
	mov r1, #0
	bl FUN_02058544
	add r0, r4, #0
	mov r1, #0x38
	bl MOD05_021F6140
	mov r0, #0x10
	str r0, [r4, #0x10]
	mov r0, #0xe
	str r0, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD05_021F5F5C
MOD05_021F5F5C: ; 0x021F5F5C
	push {r4, lr}
	add r4, r0, #0
	add r0, r2, #0
	mov r1, #0
	bl FUN_02058544
	add r0, r4, #0
	mov r1, #0x37
	bl MOD05_021F6140
	mov r0, #0x10
	str r0, [r4, #0x10]
	mov r0, #0xe
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x20]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	mov r1, #0x49
	bl FUN_0202A0E8
	ldr r0, [r4, #0x1c]
	bl MOD05_021F61B0
	add r2, r0, #0
	mov r1, #0
	ldr r0, [r4, #0x20]
	add r3, r1, #0
	bl FUN_02061208
	mov r0, #1
	pop {r4, pc}

	thumb_func_start MOD05_021F5F9C
MOD05_021F5F9C: ; 0x021F5F9C
	mov r1, #0x78
	str r1, [r0, #0x10]
	mov r1, #0xd
	str r1, [r0, #0xc]
	mov r0, #1
	bx lr

	thumb_func_start MOD05_021F5FA8
MOD05_021F5FA8: ; 0x021F5FA8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x10]
	add r4, r2, #0
	sub r0, r0, #1
	str r0, [r5, #0x10]
	bl MOD05_021F6098
	cmp r0, #1
	bne _021F5FC4
	mov r0, #0xa
	str r0, [r5, #0xc]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F5FC4:
	ldr r0, [r5, #0x10]
	cmp r0, #0
	beq _021F5FCE
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F5FCE:
	add r0, r4, #0
	mov r1, #0
	bl FUN_02058544
	add r0, r5, #0
	mov r1, #0x36
	bl MOD05_021F6140
	mov r0, #0x10
	str r0, [r5, #0x10]
	mov r0, #0xe
	str r0, [r5, #0xc]
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD05_021F5FEC
MOD05_021F5FEC: ; 0x021F5FEC
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x10]
	add r1, r1, #1
	str r1, [r4, #0x10]
	cmp r1, #0x10
	bge _021F5FFE
	mov r0, #0
	pop {r4, pc}
_021F5FFE:
	mov r1, #0x10
	str r1, [r4, #0x10]
	bl MOD05_021F617C
	cmp r0, #0
	bne _021F600E
	mov r0, #0
	pop {r4, pc}
_021F600E:
	mov r0, #0xf
	str r0, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD05_021F6018
MOD05_021F6018: ; 0x021F6018
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x24]
	add r4, r1, #0
	cmp r0, #0
	beq _021F602C
	bl FUN_02064520
	mov r0, #0
	str r0, [r5, #0x24]
_021F602C:
	add r0, r5, #0
	bl MOD05_021F60FC
	add r0, r4, #0
	bl FUN_020553C4
	bl FUN_02055648
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021E5FD8
	add r0, r4, #0
	bl MOD05_021E5FE0
	mov r0, #0
	str r0, [r5, #0x10]
	mov r0, #0x10
	str r0, [r5, #0xc]
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD05_021F6058
MOD05_021F6058: ; 0x021F6058
	ldr r1, [r0, #0x10]
	add r1, r1, #1
	str r1, [r0, #0x10]
	cmp r1, #2
	ble _021F6066
	mov r1, #0x11
	str r1, [r0, #0xc]
_021F6066:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD05_021F606C
MOD05_021F606C: ; 0x021F606C
	mov r1, #1
	str r1, [r0, #4]
	mov r0, #0
	bx lr

	thumb_func_start MOD05_021F6074
MOD05_021F6074: ; 0x021F6074
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #4
	add r1, r5, #0
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	bne _021F6088
	bl GF_AssertFail
_021F6088:
	add r0, r4, #0
	mov r1, #0
	add r2, r5, #0
	bl memset
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD05_021F6098
MOD05_021F6098: ; 0x021F6098
	ldr r0, _021F60A8 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r1, r0
	bne _021F60A4
	mov r0, #0
_021F60A4:
	bx lr
	nop
_021F60A8: .word gMain

	thumb_func_start MOD05_021F60AC
MOD05_021F60AC: ; 0x021F60AC
	ldr r0, _021F60C0 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021F60BA
	mov r0, #1
	bx lr
_021F60BA:
	mov r0, #0
	bx lr
	nop
_021F60C0: .word gMain

	thumb_func_start MOD05_021F60C4
MOD05_021F60C4: ; 0x021F60C4
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	mov r1, #0x1a
	mov r2, #0xc7
	mov r3, #4
	bl NewMsgDataFromNarc
	str r0, [r4, #0x48]
	mov r0, #1
	lsl r0, r0, #0xa
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0x2c]
	mov r0, #1
	lsl r0, r0, #0xa
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0x30]
	mov r0, #8
	mov r1, #0x40
	mov r2, #4
	bl ScrStrBufs_new_custom
	str r0, [r4, #0x34]
	pop {r4, pc}

	thumb_func_start MOD05_021F60FC
MOD05_021F60FC: ; 0x021F60FC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x34]
	bl ScrStrBufs_delete
	ldr r0, [r4, #0x2c]
	bl String_dtor
	ldr r0, [r4, #0x30]
	bl String_dtor
	ldr r0, [r4, #0x48]
	bl DestroyMsgData
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD05_021F611C
MOD05_021F611C: ; 0x021F611C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r4, [r5, #0x20]
	add r1, r5, #0
	ldr r0, [r4, #8]
	add r1, #0x38
	mov r2, #3
	bl FUN_020545B8
	ldr r0, [r4, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r5, #0x38
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_02054608
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F6140
MOD05_021F6140: ; 0x021F6140
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	bl MOD05_021F611C
	ldr r0, [r5, #0x48]
	ldr r2, [r5, #0x30]
	add r1, r6, #0
	ldr r4, [r5, #0x20]
	bl ReadMsgDataIntoString
	ldr r0, [r5, #0x34]
	ldr r1, [r5, #0x2c]
	ldr r2, [r5, #0x30]
	bl StringExpandPlaceholders
	ldr r0, [r4, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r2, r0, #0
	add r0, r5, #0
	ldr r1, [r5, #0x2c]
	add r0, #0x38
	mov r3, #1
	bl FUN_02054658
	add r5, #0x28
	strb r0, [r5]
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD05_021F617C
MOD05_021F617C: ; 0x021F617C
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x28
	ldrb r0, [r0]
	bl FUN_020546C8
	cmp r0, #1
	bne _021F61AA
	bl MOD05_021F60AC
	cmp r0, #1
	bne _021F61AA
	add r0, r4, #0
	add r0, #0x38
	mov r1, #0
	bl FUN_0200D0E0
	add r4, #0x38
	add r0, r4, #0
	bl FUN_02019178
	mov r0, #1
	pop {r4, pc}
_021F61AA:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD05_021F61B0
MOD05_021F61B0: ; 0x021F61B0
	push {r3, lr}
	cmp r0, #0
	beq _021F61C2
	cmp r0, #1
	beq _021F61C6
	cmp r0, #2
	beq _021F61CA
	bl GF_AssertFail
_021F61C2:
	ldr r0, _021F61D0 ; =0x000001BD
	pop {r3, pc}
_021F61C6:
	ldr r0, _021F61D4 ; =0x000001BE
	pop {r3, pc}
_021F61CA:
	ldr r0, _021F61D8 ; =0x000001BF
	pop {r3, pc}
	nop
_021F61D0: .word 0x000001BD
_021F61D4: .word 0x000001BE
_021F61D8: .word 0x000001BF

	thumb_func_start MOD05_021F61DC
MOD05_021F61DC: ; 0x021F61DC
	lsl r1, r0, #2
	ldr r0, _021F61E4 ; =UNK05_021FCA00
	ldrh r0, [r0, r1]
	bx lr
	.align 2, 0
_021F61E4: .word UNK05_021FCA00

	thumb_func_start MOD05_021F61E8
MOD05_021F61E8: ; 0x021F61E8
	lsl r1, r0, #2
	ldr r0, _021F61F0 ; =UNK05_021FCA00 + 2
	ldrh r0, [r0, r1]
	bx lr
	.align 2, 0
_021F61F0: .word UNK05_021FCA00 + 2

	thumb_func_start MOD05_021F61F4
MOD05_021F61F4: ; 0x021F61F4
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	mov r1, #0x34
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x34
	bl memset
	str r6, [r4]
	mov r0, #0
	str r0, [r4, #0xc]
	str r5, [r4, #0x2c]
	ldr r0, [r5, #0x20]
	str r0, [r4, #0x30]
	bl FUN_0201F010
	str r0, [r4, #0x10]
	str r0, [r4, #0x20]
	ldr r0, _021F622C ; =MOD05_021F6270
	ldr r2, _021F6230 ; =0x0000FFFF
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r4, r5, r6, pc}
	.align 2, 0
_021F622C: .word MOD05_021F6270
_021F6230: .word 0x0000FFFF

	thumb_func_start MOD05_021F6234
MOD05_021F6234: ; 0x021F6234
	push {r3, lr}
	bl FUN_0201B6C8
	ldr r0, [r0, #8]
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD05_021F6240
MOD05_021F6240: ; 0x021F6240
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0201B6C8
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
	pop {r4, pc}

	thumb_func_start MOD05_021F6254
MOD05_021F6254: ; 0x021F6254
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	add r6, r3, #0
	bl FUN_0201B6C8
	mov r1, #0
	str r1, [r0, #4]
	str r1, [r0, #8]
	str r5, [r0, #0xc]
	str r4, [r0, #0x14]
	str r6, [r0, #0x1c]
	str r1, [r0, #0x24]
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021F6270
MOD05_021F6270: ; 0x021F6270
	push {r3, lr}
	add r0, r1, #0
	ldr r1, [r1, #0xc]
	lsl r2, r1, #2
	ldr r1, _021F6280 ; =UNK05_021FD1B8
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	.align 2, 0
_021F6280: .word UNK05_021FD1B8

	thumb_func_start MOD05_021F6284
MOD05_021F6284: ; 0x021F6284
	mov r1, #1
	str r1, [r0, #8]
	bx lr
	.align 2, 0

	thumb_func_start MOD05_021F628C
MOD05_021F628C: ; 0x021F628C
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _021F629C
	cmp r1, #1
	beq _021F62A6
	pop {r4, pc}
_021F629C:
	bl MOD05_021F630C
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021F62A6:
	add r0, r4, #0
	bl MOD05_021F633C
	cmp r0, #1
	bne _021F62BA
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #1
	str r0, [r4, #8]
_021F62BA:
	add r0, r4, #0
	bl MOD05_021F62FC
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD05_021F62C4
MOD05_021F62C4: ; 0x021F62C4
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _021F62D4
	cmp r1, #1
	beq _021F62DE
	pop {r4, pc}
_021F62D4:
	bl MOD05_021F6324
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021F62DE:
	add r0, r4, #0
	bl MOD05_021F633C
	cmp r0, #1
	bne _021F62F2
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #1
	str r0, [r4, #8]
_021F62F2:
	add r0, r4, #0
	bl MOD05_021F62FC
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD05_021F62FC
MOD05_021F62FC: ; 0x021F62FC
	ldr r3, _021F6308 ; =FUN_0201EFE0
	add r1, r0, #0
	ldr r0, [r1, #0x20]
	ldr r1, [r1, #0x30]
	bx r3
	nop
_021F6308: .word FUN_0201EFE0

	thumb_func_start MOD05_021F630C
MOD05_021F630C: ; 0x021F630C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #0x1c]
	bl _s32_div_f
	str r0, [r4, #0x28]
	ldr r1, [r4, #0x20]
	ldr r0, [r4, #0x14]
	add r0, r1, r0
	str r0, [r4, #0x18]
	pop {r4, pc}

	thumb_func_start MOD05_021F6324
MOD05_021F6324: ; 0x021F6324
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x20]
	sub r0, r1, r0
	ldr r1, [r4, #0x1c]
	bl _s32_div_f
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x10]
	str r0, [r4, #0x18]
	pop {r4, pc}

	thumb_func_start MOD05_021F633C
MOD05_021F633C: ; 0x021F633C
	ldr r2, [r0, #0x20]
	ldr r1, [r0, #0x28]
	add r1, r2, r1
	str r1, [r0, #0x20]
	ldr r1, [r0, #0x24]
	add r2, r1, #1
	str r2, [r0, #0x24]
	ldr r1, [r0, #0x1c]
	cmp r2, r1
	blo _021F635A
	str r1, [r0, #0x24]
	ldr r1, [r0, #0x18]
	str r1, [r0, #0x20]
	mov r0, #1
	bx lr
_021F635A:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD05_021F6360
MOD05_021F6360: ; 0x021F6360
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	bl FUN_02046528
	str r0, [sp]
	add r0, r7, #0
	bl FUN_0204652C
	add r6, r0, #0
	add r0, r7, #0
	bl FUN_02046530
	add r4, r0, #0
	ldr r0, [r4]
	ldr r5, [r6, #4]
	cmp r0, #5
	bhi _021F6424
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021F638E: ; jump table
	.short _021F639A - _021F638E - 2 ; case 0
	.short _021F63AC - _021F638E - 2 ; case 1
	.short _021F63CC - _021F638E - 2 ; case 2
	.short _021F63EA - _021F638E - 2 ; case 3
	.short _021F6402 - _021F638E - 2 ; case 4
	.short _021F6414 - _021F638E - 2 ; case 5
_021F639A:
	mov r0, #0xb
	mov r1, #8
	bl AllocFromHeapAtEnd
	str r0, [r6, #4]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021F6424
_021F63AC:
	bl MOD05_021F57EC
	add r6, r0, #0
	mov r0, #0xb
	add r1, r6, #0
	bl AllocFromHeapAtEnd
	str r0, [r5, #4]
	mov r1, #0
	add r2, r6, #0
	bl memset
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021F6424
_021F63CC:
	ldr r0, [sp]
	ldr r0, [r0, #0x38]
	bl FUN_020553E8
	add r3, r0, #0
	ldr r0, [sp]
	ldr r2, [r6]
	mov r1, #0
	bl MOD06_0224666C
	str r0, [r5]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021F6424
_021F63EA:
	ldr r0, [r5]
	bl MOD06_022466A0
	cmp r0, #0
	beq _021F6424
	ldr r0, [r5]
	bl MOD06_022466AC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021F6424
_021F6402:
	ldr r1, _021F6428 ; =MOD05_021F57F0
	ldr r2, [r5, #4]
	add r0, r7, #0
	bl FUN_0204640C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021F6424
_021F6414:
	add r0, r5, #0
	bl FreeToHeap
	add r0, r6, #0
	bl FreeToHeap
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F6424:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021F6428: .word MOD05_021F57F0

	.section .rodata

	.global UNK05_021F78E4
UNK05_021F78E4: ; 0x021F78E4
	.byte 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00

	.global UNK05_021F7910
UNK05_021F7910: ; 0x021F7910
	.byte 0xDC, 0x05, 0x00, 0x00, 0x0F, 0x41, 0x0E, 0x00

	.global UNK05_021F7918
UNK05_021F7918: ; 0x021F7918
	.byte 0xDC, 0x05, 0x00, 0x00
	.byte 0x0F, 0x42, 0x12, 0x00

	.global UNK05_021F7920
UNK05_021F7920: ; 0x021F7920
	.byte 0xDC, 0x05, 0x00, 0x00, 0x0F, 0x43, 0x13, 0x00

	.global UNK05_021F7928
UNK05_021F7928: ; 0x021F7928
	.byte 0xDC, 0x05, 0x00, 0x00
	.byte 0x0F, 0x44, 0x14, 0x00

	.global UNK05_021F7930
UNK05_021F7930: ; 0x021F7930
	.byte 0xB8, 0x0B, 0x00, 0x00, 0x1E, 0x45, 0x15, 0x00

	.global UNK05_021F7938
UNK05_021F7938: ; 0x021F7938
	.byte 0x00, 0x00, 0x0B, 0x00
	.byte 0x3E, 0x00, 0x01, 0x00

	.global UNK05_021F7940
UNK05_021F7940: ; 0x021F7940
	.byte 0x00, 0x00, 0x0B, 0x00, 0x4A, 0x00, 0x01, 0x00

	.global UNK05_021F7948
UNK05_021F7948: ; 0x021F7948
	.byte 0x00, 0x00, 0x0C, 0x00
	.byte 0x4B, 0x00, 0x00, 0x00

	.global UNK05_021F7950
UNK05_021F7950: ; 0x021F7950
	.byte 0x00, 0x00, 0x0B, 0x00, 0x4C, 0x00, 0x01, 0x00

	.global UNK05_021F7958
UNK05_021F7958: ; 0x021F7958
	.byte 0x00, 0x00, 0x0C, 0x00
	.byte 0x4D, 0x00, 0x01, 0x00

	.global UNK05_021F7960
UNK05_021F7960: ; 0x021F7960
	.byte 0x00, 0x00, 0x0B, 0x00, 0x4E, 0x00, 0x01, 0x00

	.global UNK05_021F7968
UNK05_021F7968: ; 0x021F7968
	.byte 0x00, 0x00, 0x0B, 0x00
	.byte 0x40, 0x00, 0x01, 0x00

	.global UNK05_021F7970
UNK05_021F7970: ; 0x021F7970
	.byte 0x00, 0x00, 0x0B, 0x00, 0x4F, 0x00, 0x01, 0x00

	.global UNK05_021F7978
UNK05_021F7978: ; 0x021F7978
	.byte 0xC1, 0xAE, 0x29, 0x00
	.byte 0x02, 0xD6, 0x00, 0x00, 0xC1, 0x05

	.global UNK05_021F7982
UNK05_021F7982: ; 0x021F7982
	.byte 0x04, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xCF, 0x00, 0xFF
	.byte 0x01, 0x06, 0x04, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xE6, 0x00, 0x10, 0x91, 0x06, 0x04, 0x00
	.byte 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xD6, 0x00, 0x0A, 0x11, 0x07, 0x03, 0x00, 0xC1, 0xAE, 0x29, 0x00
	.byte 0x02, 0xE1, 0x00, 0xF0, 0x80, 0x07, 0x03, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xC6, 0x00, 0x00
	.byte 0x51, 0x07, 0x03, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xE0, 0x00, 0xF0, 0x00, 0x08, 0x03, 0x00
	.byte 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xD6, 0x00, 0x00, 0x02, 0x08, 0x03, 0x00, 0xC1, 0xAE, 0x29, 0x00
	.byte 0x02, 0xD0, 0x00, 0x10, 0x00, 0x08, 0x03, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xD9, 0x00, 0xF5
	.byte 0x51, 0x07, 0x03, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xD0, 0x00, 0x0A, 0xC1, 0x04, 0x02, 0x00
	.byte 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xE0, 0x00, 0xF0, 0xC1, 0x03, 0x02, 0x00, 0xC1, 0xAE, 0x29, 0x00
	.byte 0x02, 0xD0, 0x00, 0xF0, 0x50, 0x06, 0x01, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xE0, 0x00, 0xA0
	.byte 0x41, 0x02, 0x01, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0xA2, 0xE1, 0x00, 0x05, 0x00, 0x05, 0x01, 0x00
	.byte 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xD6, 0x00, 0x00, 0x41, 0x02, 0x01, 0x00

	.global UNK05_021F7A38
UNK05_021F7A38: ; 0x021F7A38
	.byte 0x00, 0x40, 0x10, 0x00

	.global UNK05_021F7A3C
UNK05_021F7A3C: ; 0x021F7A3C
	.byte 0x00, 0x00, 0x08, 0x00

	.global UNK05_021F7A40
UNK05_021F7A40: ; 0x021F7A40
	.byte 0x00, 0x20, 0xFE, 0xFF

	.global UNK05_021F7A44
UNK05_021F7A44: ; 0x021F7A44
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK05_021F7A48
UNK05_021F7A48: ; 0x021F7A48
	.byte 0x00, 0x40, 0x06, 0x00

	.global UNK05_021F7A4C
UNK05_021F7A4C: ; 0x021F7A4C
	.byte 0x00, 0x40, 0x01, 0x00

	.global UNK05_021F7A50
UNK05_021F7A50: ; 0x021F7A50
	.byte 0x04, 0x00, 0x00, 0x00

	.global UNK05_021F7A54
UNK05_021F7A54: ; 0x021F7A54
	.byte 0xFE, 0xFF, 0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0xE0, 0x01, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x40, 0x06, 0x00
	.byte 0x00, 0xC0, 0xFE, 0xFF, 0x03, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0xE0, 0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x40, 0x06, 0x00
	.byte 0x00, 0x40, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0xFD, 0xFF, 0x00, 0xC0, 0x08, 0x00
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x60, 0xFF, 0xFF, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x40, 0x06, 0x00
	.byte 0x00, 0xC0, 0xFE, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0xFE, 0xFF, 0x00, 0x40, 0x10, 0x00
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x20, 0xFE, 0xFF, 0x00, 0x00, 0x05, 0x00, 0x00, 0x40, 0x06, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0xFD, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0xE0, 0x01, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x40, 0x06, 0x00
	.byte 0x00, 0xC0, 0xFE, 0xFF, 0x03, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00

	.global UNK05_021F7AF8
UNK05_021F7AF8: ; 0x021F7AF8
	.byte 0x70, 0x00, 0xD6, 0x00
	.byte 0x2F, 0x01, 0x91, 0x01, 0xF5, 0x01, 0x63, 0x02, 0xC3, 0x02, 0x35, 0x03, 0xA0, 0x03, 0x07, 0x04
	.byte 0x61, 0x04, 0xC8, 0x04, 0xC9, 0x04

	.global UNK05_021F7B12
UNK05_021F7B12: ; 0x021F7B12
	.byte 0x68, 0x01

	.global UNK05_021F7B14
UNK05_021F7B14: ; 0x021F7B14
	.byte 0xFF, 0x00

	.global UNK05_021F7B16
UNK05_021F7B16: ; 0x021F7B16
	.byte 0xCA, 0x00, 0x2A, 0x01, 0xFE, 0x00
	.byte 0xB7, 0x00, 0xB7, 0x01, 0x3A, 0x01, 0x7A, 0x00, 0xB6, 0x01, 0x3B, 0x01, 0xB9, 0x00, 0xBE, 0x01
	.byte 0x3C, 0x01, 0x8F, 0x00, 0xCA, 0x01, 0x3D, 0x01, 0xE2, 0x00, 0x96, 0x01, 0x3E, 0x01, 0x3B, 0x01
	.byte 0xB8, 0x01, 0x3F, 0x01, 0x71, 0x00, 0xB1, 0x01, 0x40, 0x01, 0x66, 0x01

	.global UNK05_021F7B48
UNK05_021F7B48: ; 0x021F7B48
	.byte 0x21, 0x4E, 0x71, 0x00
	.byte 0x82, 0x00, 0xDB, 0x00, 0xCC, 0x00, 0x50, 0x00, 0x59, 0x01, 0x40, 0x01, 0xAE, 0x00, 0x13, 0x01
	.byte 0x0B, 0x01, 0x85, 0x00, 0xB5, 0x01, 0x24, 0x4E, 0xBB, 0x00, 0xF6, 0x00, 0x9D, 0x00, 0x2C, 0x00
	.byte 0xC8, 0x00, 0xFB, 0x00, 0x0E, 0x00, 0x5D, 0x01, 0xF2, 0x00, 0x97, 0x01, 0xE8, 0x00, 0x8A, 0x01
	.byte 0x27, 0x4E, 0xF3, 0x00, 0x72, 0x00, 0x36, 0x00, 0xC1, 0x00, 0xAF, 0x00, 0x1F, 0x01, 0x2C, 0x01
	.byte 0x19, 0x01, 0x4A, 0x01, 0xFC, 0x00, 0x88, 0x01, 0xC5, 0x01, 0x30, 0x4E, 0xE4, 0x00, 0xB9, 0x00
	.byte 0xC1, 0x00, 0xD3, 0x00, 0x3A, 0x01, 0x93, 0x01, 0x9D, 0x01, 0xFD, 0x00, 0x33, 0x4E, 0x67, 0x00
	.byte 0xAC, 0x00, 0x9A, 0x00, 0x2C, 0x00, 0x44, 0x00, 0xB3, 0x00, 0xFD, 0x00, 0xCF, 0x00, 0x83, 0x01
	.byte 0x7E, 0x01, 0x35, 0x4E, 0xB9, 0x00, 0xCE, 0x00, 0xB8, 0x00, 0x62, 0x00, 0xA1, 0x00, 0x36, 0x01
	.byte 0x8F, 0x00, 0x12, 0x00, 0xFD, 0x00, 0x37, 0x4E, 0xE4, 0x00, 0x15, 0x00, 0xB4, 0x00, 0xFB, 0x00
	.byte 0x31, 0x01, 0xB8, 0x00, 0x56, 0x01, 0x32, 0x00, 0x3B, 0x4E, 0xAF, 0x00, 0xDB, 0x00, 0x44, 0x00
	.byte 0xE5, 0x00, 0x9D, 0x00, 0xE8, 0x00, 0x0E, 0x00, 0x32, 0x01, 0x90, 0x01, 0x3D, 0x4E, 0x30, 0x00
	.byte 0x32, 0x00, 0x24, 0x00, 0x74, 0x00, 0xCC, 0x00, 0x44, 0x00, 0xFB, 0x00, 0xE4, 0x00, 0x40, 0x4E
	.byte 0x44, 0x00, 0x32, 0x00, 0x30, 0x00, 0x24, 0x00, 0x85, 0x00, 0x5D, 0x00, 0xFB, 0x00, 0x85, 0x01
	.byte 0x45, 0x4E, 0xB9, 0x00, 0x5F, 0x00, 0xAF, 0x00, 0xB4, 0x00, 0x32, 0x00, 0x50, 0x01, 0xF4, 0x00
	.byte 0x01, 0x01, 0x8A, 0x01, 0x46, 0x01, 0x9C, 0x01, 0x49, 0x4E, 0x62, 0x00, 0xE4, 0x00, 0xB9, 0x00
	.byte 0x10, 0x00, 0x12, 0x00, 0xAE, 0x00, 0xA1, 0x01, 0x5F, 0x00, 0xAC, 0x01, 0x9D, 0x01, 0x4B, 0x4E
	.byte 0x0E, 0x00, 0x4B, 0x00, 0xAF, 0x00, 0xEB, 0x00, 0xCC, 0x00, 0x13, 0x01, 0x41, 0x01, 0x4E, 0x4E
	.byte 0xCE, 0x00, 0x67, 0x00, 0x44, 0x00, 0x3C, 0x00, 0xAF, 0x00, 0xE6, 0x00, 0x71, 0x00, 0xE4, 0x00
	.byte 0xE8, 0x00, 0xC2, 0x01, 0xB8, 0x01, 0x50, 0x4E, 0xE2, 0x00, 0x67, 0x00, 0xCA, 0x00, 0x44, 0x01
	.byte 0x61, 0x00, 0xEA, 0x00, 0x86, 0x01, 0xC2, 0x01, 0x52, 0x4E, 0xB9, 0x00, 0x67, 0x00, 0xF6, 0x00
	.byte 0xE4, 0x00, 0xFB, 0x00, 0xFD, 0x00, 0x9D, 0x00, 0xAA, 0x01, 0x36, 0x01, 0x54, 0x4E, 0xB4, 0x00
	.byte 0xCC, 0x00, 0x5F, 0x00, 0x85, 0x00, 0xF4, 0x00, 0x12, 0x01, 0x3C, 0x01, 0xAF, 0x00, 0x83, 0x01
	.byte 0x82, 0x01, 0x56, 0x4E, 0x5F, 0x00, 0x3C, 0x00, 0xC1, 0x00, 0x71, 0x00, 0xF8, 0x00, 0x5E, 0x00
	.byte 0xEE, 0x00, 0x1F, 0x01, 0x6D, 0x00, 0x19, 0x01, 0xAA, 0x01, 0x58, 0x4E, 0x9D, 0x00, 0xC1, 0x00
	.byte 0x60, 0x00, 0x44, 0x00, 0xB3, 0x00, 0xFB, 0x00, 0x17, 0x01, 0x09, 0x01, 0x72, 0x01, 0x5A, 0x4E
	.byte 0x22, 0x00, 0xDB, 0x00, 0xF2, 0x00, 0x25, 0x00, 0x53, 0x00, 0x50, 0x01, 0x01, 0x01, 0x26, 0x00
	.byte 0x8A, 0x01, 0x5C, 0x4E, 0x36, 0x00, 0x96, 0x00, 0x3D, 0x00, 0x72, 0x00, 0xAA, 0x00, 0x5A, 0x01
	.byte 0x2D, 0x01, 0x55, 0x01, 0x1F, 0x01, 0x1B, 0x01, 0x5F, 0x4E, 0xE3, 0x00, 0x70, 0x00, 0x1A, 0x01
	.byte 0x07, 0x00, 0x09, 0x00, 0x08, 0x00, 0x7B, 0x01, 0x81, 0x01, 0x62, 0x4E, 0x71, 0x00, 0x60, 0x00
	.byte 0x1B, 0x00, 0xE3, 0x00, 0x09, 0x01, 0x44, 0x00, 0x9D, 0x00, 0x72, 0x01, 0x07, 0x00, 0x09, 0x00
	.byte 0x08, 0x00, 0xA2, 0x01, 0x65, 0x4E, 0x0E, 0x00, 0xE3, 0x00, 0x73, 0x00, 0xEB, 0x00, 0x8D, 0x00
	.byte 0x13, 0x01, 0x59, 0x01, 0x84, 0x01, 0x41, 0x01, 0x68, 0x4E, 0x3E, 0x00, 0xF3, 0x00, 0xE5, 0x00
	.byte 0x72, 0x00, 0xDB, 0x00, 0x6D, 0x00, 0x1A, 0x01, 0x6F, 0x01, 0x6A, 0x4E, 0x05, 0x00, 0x9D, 0x00
	.byte 0x4F, 0x01, 0x67, 0x01, 0xAF, 0x00, 0x6D, 0x4E, 0xAC, 0x00, 0x25, 0x00, 0x18, 0x00, 0x5F, 0x00
	.byte 0xCC, 0x00, 0x26, 0x00, 0x20, 0x00, 0x6F, 0x4E, 0xDB, 0x00, 0xBB, 0x00, 0xF8, 0x00, 0x17, 0x00
	.byte 0x2C, 0x01, 0xD6, 0x00, 0xAD, 0x00, 0x7E, 0x01, 0x4F, 0x01, 0xAC, 0x01, 0x73, 0x4E, 0xD3, 0x00
	.byte 0xC1, 0x00, 0x77, 0x00, 0x10, 0x00, 0x62, 0x00, 0xAF, 0x00, 0x29, 0x01, 0xAE, 0x00, 0x57, 0x01
	.byte 0xBD, 0x00, 0x90, 0x01, 0x74, 0x4E, 0x62, 0x00, 0x30, 0x00, 0x72, 0x00, 0xB9, 0x00, 0xAF, 0x00
	.byte 0x1B, 0x01, 0x77, 0x00, 0x9D, 0x01, 0x76, 0x4E, 0x7A, 0x00, 0xC3, 0x00, 0x32, 0x00, 0x20, 0x00
	.byte 0x15, 0x00, 0xE3, 0x00, 0xFC, 0x00, 0x4D, 0x01, 0x44, 0x01, 0x78, 0x4E, 0x72, 0x00, 0xD4, 0x00
	.byte 0x7A, 0x00, 0x1E, 0x01, 0xAE, 0x00, 0x45, 0x01, 0x99, 0x00, 0xA9, 0x01, 0xFE, 0x00, 0x00, 0x01
	.byte 0xFF, 0x00, 0x7A, 0x4E, 0x3D, 0x00, 0x24, 0x00, 0x70, 0x00, 0xE5, 0x00, 0x67, 0x00, 0x4D, 0x01
	.byte 0x55, 0x01, 0x7C, 0x4E, 0x95, 0x00, 0xC3, 0x00, 0x72, 0x00, 0x36, 0x01, 0x05, 0x01, 0x20, 0x01
	.byte 0x99, 0x00, 0x07, 0x00, 0x08, 0x00, 0x09, 0x00, 0x7F, 0x4E, 0x9D, 0x00, 0xAF, 0x00, 0x99, 0x00
	.byte 0x4F, 0x01, 0x6F, 0x00, 0xCD, 0x00, 0x5E, 0x01, 0x80, 0x4E, 0x70, 0x00, 0x12, 0x01, 0x10, 0x01
	.byte 0x07, 0x00, 0x09, 0x00, 0x08, 0x00, 0xA1, 0x01, 0x04, 0x01, 0xAB, 0x01, 0x82, 0x4E, 0x5B, 0x00
	.byte 0x72, 0x00, 0x85, 0x00, 0xAF, 0x00, 0x15, 0x00, 0x1A, 0x01, 0x0E, 0x00, 0x41, 0x01, 0xF6, 0x00
	.byte 0x86, 0x4E, 0xEB, 0x00, 0xEC, 0x00, 0x73, 0x00, 0xF6, 0x00, 0xF4, 0x00, 0x13, 0x01, 0xAE, 0x00
	.byte 0x0B, 0x01, 0x7D, 0x01, 0xB5, 0x01, 0x88, 0x4E, 0x9D, 0x00, 0xF6, 0x00, 0xBB, 0x00, 0x67, 0x00
	.byte 0x82, 0x00, 0xC3, 0x00, 0x0E, 0x00, 0x18, 0x00, 0xBA, 0x01, 0x8C, 0x4E, 0xBB, 0x00, 0xDE, 0x00
	.byte 0x22, 0x00, 0xAE, 0x00, 0x09, 0x01, 0xD6, 0x00, 0xAD, 0x00, 0xA4, 0x00, 0x85, 0x00, 0x67, 0x01
	.byte 0x8D, 0x4E, 0x67, 0x00, 0x95, 0x00, 0x3C, 0x00, 0xC2, 0x00, 0xDC, 0x00, 0x05, 0x01, 0x20, 0x01
	.byte 0xB4, 0x00, 0xAE, 0x00, 0x8F, 0x4E, 0xF2, 0x00, 0xB3, 0x00, 0x9D, 0x00, 0x44, 0x00, 0xDE, 0x00
	.byte 0x0E, 0x00, 0xAE, 0x00, 0x32, 0x01, 0x97, 0x01, 0xA7, 0x01, 0xA8, 0x01, 0xA6, 0x01, 0x91, 0x4E
	.byte 0xD9, 0x00, 0x76, 0x00, 0xD7, 0x00, 0x38, 0x01, 0xA4, 0x00, 0x44, 0x00, 0x0E, 0x01, 0x64, 0x01
	.byte 0x92, 0x4E, 0xAF, 0x00, 0x5D, 0x00, 0x48, 0x00, 0x73, 0x00, 0x85, 0x00, 0x49, 0x00, 0x0B, 0x01
	.byte 0x1B, 0x01, 0xB5, 0x01, 0x93, 0x4E, 0x17, 0x00, 0xC1, 0x00, 0x74, 0x00, 0xDB, 0x00, 0x32, 0x00
	.byte 0x44, 0x00, 0x32, 0x01, 0xA4, 0x00, 0x26, 0x00, 0x1B, 0x01, 0x67, 0x01, 0x94, 0x4E, 0xAF, 0x00
	.byte 0x3E, 0x00, 0xBE, 0x00, 0x32, 0x00, 0x96, 0x00, 0x52, 0x00, 0xE1, 0x00, 0x44, 0x01, 0x96, 0x4E
	.byte 0x3C, 0x00, 0x72, 0x00, 0x38, 0x00, 0xD6, 0x00, 0x2C, 0x01, 0xBD, 0x00, 0x91, 0x01, 0x9A, 0x4E
	.byte 0xF8, 0x00, 0x5F, 0x00, 0x66, 0x00, 0xF4, 0x00, 0xFC, 0x00, 0x0F, 0x01, 0x6D, 0x00, 0x66, 0x01
	.byte 0x2A, 0x01, 0x9B, 0x4E, 0x44, 0x00, 0xDB, 0x00, 0xE2, 0x00, 0x0D, 0x00, 0xB3, 0x00, 0x71, 0x00
	.byte 0xCB, 0x00, 0x3E, 0x01, 0x95, 0x01, 0x90, 0x01, 0x9F, 0x4E, 0x1F, 0x00, 0xAF, 0x00, 0xCE, 0x00
	.byte 0xB9, 0x00, 0x62, 0x00, 0x72, 0x01, 0x6C, 0x01, 0xA3, 0x4E, 0xC1, 0x00, 0xA4, 0x00, 0x41, 0x01
	.byte 0x1F, 0x01, 0x5D, 0x01, 0xAE, 0x00, 0xD6, 0x00, 0x20, 0x00, 0xF6, 0x00, 0xFA, 0x00, 0x5A, 0x00
	.byte 0xA5, 0x4E, 0xCC, 0x00, 0xAF, 0x00, 0xCB, 0x00, 0xAE, 0x00, 0x41, 0x01, 0x11, 0x01, 0x19, 0x01
	.byte 0x39, 0x01, 0x57, 0x01, 0xAA, 0x4E, 0x3D, 0x00, 0x3E, 0x00, 0x15, 0x00, 0x30, 0x00, 0x72, 0x00
	.byte 0x9D, 0x00, 0xBF, 0x00, 0x1A, 0x01, 0x7A, 0x01, 0x86, 0x01, 0xAC, 0x4E, 0x3D, 0x00, 0x3E, 0x00
	.byte 0xE5, 0x00, 0x5B, 0x00, 0xAF, 0x00, 0x1A, 0x01, 0x6D, 0x00, 0x55, 0x01, 0xC4, 0x00, 0x67, 0x00
	.byte 0xAE, 0x4E, 0x12, 0x00, 0xE4, 0x00, 0xC1, 0x00, 0xD3, 0x00, 0xE1, 0x00, 0xAE, 0x00, 0x74, 0x01
	.byte 0xAF, 0x4E, 0x7A, 0x00, 0xCC, 0x00, 0x26, 0x00, 0xAE, 0x00, 0x5A, 0x00, 0xA4, 0x00, 0x12, 0x00
	.byte 0xE4, 0x00, 0xB3, 0x4E, 0x71, 0x00, 0x36, 0x00, 0x72, 0x00, 0x30, 0x00, 0xE1, 0x00, 0x5D, 0x01
	.byte 0x97, 0x01, 0xB8, 0x4E, 0x16, 0x00, 0x49, 0x00, 0x44, 0x00, 0xF6, 0x00, 0xAF, 0x00, 0x0B, 0x01
	.byte 0x13, 0x01, 0x40, 0x01, 0xB5, 0x01, 0x38, 0x01, 0x7A, 0x01, 0xBB, 0x4E, 0x9A, 0x00, 0x62, 0x00
	.byte 0xB3, 0x00, 0x25, 0x00, 0xC1, 0x00, 0x57, 0x01, 0x50, 0x01, 0x32, 0x01, 0x26, 0x00, 0x18, 0x00
	.byte 0x8A, 0x01, 0xBE, 0x4E, 0xF2, 0x00, 0x25, 0x00, 0x38, 0x00, 0xF6, 0x00, 0x9D, 0x00, 0x2C, 0x01
	.byte 0x5A, 0x01, 0x51, 0x01, 0x08, 0x00, 0xE8, 0x00, 0x5D, 0x01, 0xC1, 0x4E, 0x26, 0x00, 0xE4, 0x00
	.byte 0xA3, 0x00, 0x74, 0x00, 0xB3, 0x00, 0xA4, 0x00, 0x0F, 0x01, 0x12, 0x01, 0x83, 0x01, 0xCC, 0x00
	.byte 0x57, 0x01, 0xC3, 0x4E, 0x77, 0x00, 0x30, 0x00, 0xB9, 0x00, 0x11, 0x00, 0x12, 0x00, 0x8F, 0x00
	.byte 0x29, 0x01, 0x61, 0x00, 0x65, 0x00, 0xC5, 0x4E, 0x3C, 0x00, 0x75, 0x00, 0x3E, 0x01, 0x95, 0x01
	.byte 0x67, 0x00, 0xE3, 0x00, 0x1A, 0x01, 0xC2, 0x01, 0xC7, 0x4E, 0x3C, 0x00, 0x32, 0x00, 0x31, 0x00
	.byte 0xE2, 0x00, 0xE4, 0x00, 0x44, 0x01, 0x86, 0x01, 0x8E, 0x01, 0xCA, 0x4E, 0xAF, 0x00, 0x67, 0x00
	.byte 0x85, 0x00, 0x3C, 0x00, 0xFA, 0x00, 0x61, 0x00, 0x36, 0x00, 0xCC, 0x4E, 0xB3, 0x00, 0x75, 0x00
	.byte 0xD9, 0x00, 0xE3, 0x00, 0x03, 0x00, 0x11, 0x01, 0x0C, 0x01, 0xFC, 0x00, 0x09, 0x00, 0x41, 0x01
	.byte 0xCD, 0x4E, 0xD9, 0x00, 0x76, 0x00, 0x85, 0x00, 0xBB, 0x00, 0x96, 0x00, 0x66, 0x00, 0x11, 0x01
	.byte 0xA4, 0x00, 0x39, 0x01, 0x57, 0x01, 0xCE, 0x4E, 0xC3, 0x00, 0xD9, 0x00, 0xB9, 0x00, 0x11, 0x01
	.byte 0x39, 0x01, 0x83, 0x01, 0x57, 0x01, 0x64, 0x01, 0xCF, 0x4E, 0xD9, 0x00, 0x77, 0x00, 0x40, 0x00
	.byte 0xC1, 0x00, 0xF8, 0x00, 0xA4, 0x00, 0xF4, 0x00, 0xA1, 0x01, 0x77, 0x01, 0x7D, 0x01, 0xD1, 0x4E
	.byte 0x72, 0x00, 0x41, 0x00, 0x62, 0x00, 0xB9, 0x00, 0xD3, 0x00, 0xF4, 0x00, 0x29, 0x01, 0x1F, 0x01
	.byte 0xAC, 0x01, 0x85, 0x01, 0xD3, 0x4E, 0x24, 0x00, 0x22, 0x00, 0xDB, 0x00, 0x67, 0x00, 0x73, 0x00
	.byte 0x3C, 0x01, 0x0C, 0x01, 0x04, 0x01, 0x1C, 0x00, 0xD7, 0x4E, 0x71, 0x00, 0xD9, 0x00, 0x85, 0x00
	.byte 0xF8, 0x00, 0xBB, 0x00, 0xC3, 0x00, 0x30, 0x00, 0xA4, 0x00, 0xC5, 0x01, 0x14, 0x01, 0x1F, 0x01
	.byte 0xD9, 0x4E, 0x78, 0x00, 0x1D, 0x00, 0x6A, 0x00, 0x6F, 0x00, 0xCD, 0x00, 0x48, 0x01, 0xDB, 0x4E
	.byte 0x5D, 0x00, 0xE3, 0x00, 0x26, 0x00, 0x73, 0x00, 0x85, 0x00, 0x0E, 0x01, 0xF4, 0x00, 0x38, 0x01
	.byte 0x84, 0x01, 0xDE, 0x4E, 0x44, 0x00, 0x67, 0x00, 0xE4, 0x00, 0x61, 0x00, 0xB4, 0x00, 0x15, 0x00
	.byte 0x03, 0x00, 0xFB, 0x00, 0xFC, 0x00, 0x57, 0x01, 0x54, 0x01, 0xDF, 0x4E, 0x40, 0x01, 0xE3, 0x00
	.byte 0x49, 0x00, 0x0B, 0x01, 0xAE, 0x00, 0x0E, 0x01, 0x13, 0x01, 0xE6, 0x00, 0xE1, 0x4E, 0x12, 0x00
	.byte 0xB3, 0x00, 0x8D, 0x00, 0x44, 0x01, 0x3E, 0x01, 0x6C, 0x01, 0xB9, 0x00, 0xE4, 0x00, 0xE2, 0x4E
	.byte 0x22, 0x00, 0xF6, 0x00, 0xDB, 0x00, 0xAE, 0x00, 0x2C, 0x01, 0xFE, 0x00, 0x00, 0x01, 0xFF, 0x00
	.byte 0x44, 0x00, 0xE3, 0x00, 0x18, 0x00, 0xE6, 0x4E, 0x12, 0x00, 0x41, 0x00, 0x77, 0x00, 0x11, 0x00
	.byte 0x8F, 0x00, 0x6D, 0x00, 0x29, 0x01, 0xC3, 0x00, 0x77, 0x01, 0x67, 0x00, 0xB9, 0x00, 0xE8, 0x4E
	.byte 0x67, 0x00, 0xC2, 0x00, 0xF4, 0x00, 0x1E, 0x01, 0x06, 0x01, 0x85, 0x01, 0xA9, 0x01, 0xAE, 0x00
	.byte 0xB4, 0x00, 0xD2, 0x01, 0xEB, 0x4E, 0x24, 0x00, 0x85, 0x00, 0xC1, 0x00, 0xF8, 0x00, 0xFB, 0x00
	.byte 0xF4, 0x00, 0x11, 0x01, 0x15, 0x01, 0x18, 0x00, 0xF3, 0x00, 0xEC, 0x4E, 0x73, 0x00, 0x2A, 0x00
	.byte 0xAF, 0x00, 0x81, 0x00, 0x44, 0x00, 0x48, 0x01, 0x17, 0x01, 0x26, 0x00, 0x86, 0x01, 0xEE, 0x4E
	.byte 0x75, 0x00, 0xF6, 0x00, 0x9D, 0x00, 0x2C, 0x00, 0x1D, 0x00, 0x36, 0x01, 0xAE, 0x00, 0x78, 0x01
	.byte 0x15, 0x01, 0xAD, 0x00, 0xEF, 0x4E, 0xE8, 0x00, 0x11, 0x00, 0x0D, 0x00, 0x44, 0x00, 0x48, 0x01
	.byte 0x61, 0x00, 0xE2, 0x00, 0x26, 0x00, 0x6C, 0x01, 0x90, 0x01, 0xB8, 0x01, 0xF1, 0x4E, 0x76, 0x00
	.byte 0xB9, 0x00, 0x73, 0x00, 0xD9, 0x00, 0xF2, 0x00, 0xD7, 0x00, 0xAD, 0x00, 0x09, 0x01, 0x72, 0x01
	.byte 0xA7, 0x01, 0xA8, 0x01, 0xA6, 0x01, 0xF3, 0x4E, 0xAF, 0x00, 0x72, 0x00, 0x3D, 0x00, 0x30, 0x00
	.byte 0x36, 0x01, 0x44, 0x01, 0x8E, 0x01, 0xF5, 0x4E, 0xE6, 0x00, 0x1A, 0x01, 0x0E, 0x01, 0x6F, 0x01
	.byte 0x48, 0x01, 0xBD, 0x00, 0xF6, 0x4E, 0x6A, 0x00, 0x75, 0x00, 0xAF, 0x00, 0xCE, 0x00, 0x17, 0x01
	.byte 0xE4, 0x00, 0x26, 0x00, 0xF7, 0x4E, 0x44, 0x00, 0xB4, 0x00, 0xC1, 0x00, 0x73, 0x00, 0x2C, 0x00
	.byte 0x32, 0x01, 0xFC, 0x00, 0xCA, 0x01, 0x82, 0x01, 0xE4, 0x00, 0xA4, 0x01, 0x08, 0x00, 0xF8, 0x4E
	.byte 0xF2, 0x00, 0x24, 0x00, 0x45, 0x00, 0x44, 0x00, 0xE8, 0x00, 0x39, 0x01, 0x19, 0x01, 0xD6, 0x00
	.byte 0xEE, 0x00, 0x26, 0x00, 0x72, 0x01, 0x90, 0x01, 0xFA, 0x4E, 0x97, 0x00, 0x01, 0x01, 0xAE, 0x00
	.byte 0x6C, 0x00, 0x06, 0x01, 0xFE, 0x00, 0xFF, 0x00, 0x00, 0x01, 0xFC, 0x4E, 0x24, 0x00, 0x2C, 0x00
	.byte 0x22, 0x00, 0x9D, 0x00, 0xF6, 0x00, 0x55, 0x01, 0x4D, 0x01, 0x26, 0x00, 0x5A, 0x00, 0xAE, 0x00
	.byte 0xFE, 0x4E, 0x9D, 0x00, 0x67, 0x00, 0x36, 0x00, 0x85, 0x00, 0x70, 0x00, 0x13, 0x01, 0x6D, 0x00
	.byte 0x4D, 0x01, 0x0B, 0x01, 0x88, 0x01, 0xFF, 0x4E, 0x3E, 0x00, 0xBE, 0x00, 0x30, 0x00, 0x72, 0x00
	.byte 0x67, 0x00, 0x56, 0x00, 0x5E, 0x01, 0xAD, 0x00, 0xAF, 0x00, 0x01, 0x4F, 0x3E, 0x00, 0x62, 0x00
	.byte 0xF8, 0x00, 0x96, 0x00, 0xE5, 0x00, 0x2D, 0x01, 0xA4, 0x01, 0x08, 0x00, 0x02, 0x4F, 0xEF, 0x00
	.byte 0x38, 0x00, 0x72, 0x00, 0x15, 0x00, 0x2C, 0x01, 0x9D, 0x00, 0xF3, 0x00, 0x5A, 0x01, 0x96, 0x00
	.byte 0x03, 0x4F, 0x41, 0x00, 0xE4, 0x00, 0x12, 0x00, 0x8F, 0x00, 0xAE, 0x00, 0x9D, 0x01, 0x74, 0x01
	.byte 0x04, 0x4F, 0x53, 0x00, 0x63, 0x00, 0xE4, 0x00, 0x44, 0x00, 0xB4, 0x00, 0xB3, 0x00, 0xFB, 0x00
	.byte 0x05, 0x01, 0xA8, 0x01, 0xA6, 0x01, 0xA1, 0x01, 0x82, 0x01, 0x07, 0x4F, 0x74, 0x00, 0x22, 0x00
	.byte 0xF6, 0x00, 0xAD, 0x00, 0x44, 0x00, 0x5A, 0x00, 0x1B, 0x01, 0xA4, 0x01, 0x0A, 0x4F, 0xB4, 0x00
	.byte 0x32, 0x00, 0x2C, 0x00, 0xCF, 0x00, 0xF4, 0x00, 0x46, 0x01, 0x25, 0x00, 0x18, 0x00, 0xAC, 0x01
	.byte 0x0C, 0x4F, 0xE5, 0x00, 0x88, 0x00, 0xB7, 0x00, 0xAA, 0x00, 0x0E, 0x01, 0x44, 0x00, 0x9A, 0x01
	.byte 0xA2, 0x01, 0x0E, 0x4F, 0x60, 0x00, 0xF4, 0x00, 0xFC, 0x00, 0x11, 0x01, 0x08, 0x00, 0x65, 0x01
	.byte 0x0F, 0x4F, 0x02, 0x00, 0x70, 0x00, 0x1B, 0x00, 0x60, 0x00, 0xEE, 0x00, 0x07, 0x00, 0x08, 0x00
	.byte 0xDF, 0x00, 0x10, 0x4F, 0x02, 0x00, 0x05, 0x00, 0x70, 0x00, 0x67, 0x00, 0xEE, 0x00, 0x09, 0x00
	.byte 0xB7, 0x00, 0xDF, 0x00, 0x8A, 0x01, 0x11, 0x4F, 0xD9, 0x00, 0xB3, 0x00, 0x45, 0x00, 0xCB, 0x00
	.byte 0xF4, 0x00, 0xAE, 0x00, 0x0E, 0x01, 0xD6, 0x00, 0x92, 0x00, 0x67, 0x01, 0x26, 0x00, 0x82, 0x01
	.byte 0x16, 0x4F, 0xE4, 0x00, 0x17, 0x00, 0xC8, 0x00, 0x74, 0x00, 0xF6, 0x00, 0x5D, 0x01, 0xAE, 0x00
	.byte 0x4E, 0x01, 0x74, 0x01, 0xBA, 0x01, 0x1C, 0x4F, 0xF2, 0x00, 0x2C, 0x01, 0x1B, 0x01, 0x49, 0x00
	.byte 0xE1, 0x00, 0x32, 0x01, 0x84, 0x01, 0x18, 0x00, 0x40, 0x01, 0xEB, 0x00, 0x59, 0x01, 0xB5, 0x01
	.byte 0x1F, 0x4F, 0x44, 0x00, 0xB3, 0x00, 0xCB, 0x00, 0xCF, 0x00, 0x9D, 0x00, 0x09, 0x01, 0x32, 0x01
	.byte 0xE2, 0x00, 0x61, 0x00, 0x90, 0x01, 0x83, 0x01, 0x6C, 0x01, 0x22, 0x4F, 0x1F, 0x01, 0xFD, 0x00
	.byte 0xAE, 0x00, 0x17, 0x00, 0x2D, 0x01, 0xF3, 0x00, 0x44, 0x00, 0xF6, 0x00, 0xFA, 0x00, 0x2C, 0x00
	.byte 0x26, 0x00, 0xAA, 0x01, 0x25, 0x4F, 0x36, 0x01, 0x31, 0x01, 0x57, 0x01, 0x2B, 0x00, 0x19, 0x01
	.byte 0x85, 0x01, 0xA7, 0x01, 0xA8, 0x01, 0xA6, 0x01, 0x7E, 0x01, 0x27, 0x4F, 0xCC, 0x00, 0xE4, 0x00
	.byte 0xA4, 0x00, 0x41, 0x01, 0x0F, 0x01, 0x0E, 0x01, 0xBD, 0x00, 0x2E, 0x4F, 0xEB, 0x00, 0x4B, 0x00
	.byte 0xE6, 0x00, 0x49, 0x00, 0xAF, 0x00, 0x37, 0x00, 0x41, 0x01, 0x31, 0x4F, 0x49, 0x00, 0x85, 0x00
	.byte 0x62, 0x00, 0x0D, 0x00, 0x24, 0x00, 0xCE, 0x00, 0x84, 0x01, 0xA1, 0x01, 0x34, 0x4F, 0xE4, 0x00
	.byte 0x30, 0x00, 0x1F, 0x01, 0x77, 0x00, 0x63, 0x00, 0x8F, 0x00, 0x12, 0x00, 0x9D, 0x01, 0x36, 0x4F
	.byte 0x36, 0x00, 0xEF, 0x00, 0x61, 0x00, 0x10, 0x00, 0x5A, 0x01, 0x88, 0x01, 0x1A, 0x01, 0x38, 0x4F
	.byte 0x32, 0x00, 0x05, 0x01, 0xD4, 0x00, 0x06, 0x01, 0xC2, 0x00, 0x20, 0x01, 0xA9, 0x01, 0x6D, 0x00
	.byte 0x3B, 0x4F, 0xC1, 0x00, 0x55, 0x01, 0x3C, 0x00, 0x38, 0x00, 0xAA, 0x00, 0x44, 0x01, 0xC2, 0x01
	.byte 0x3D, 0x4F, 0x39, 0x01, 0xCF, 0x00, 0xCC, 0x00, 0xCE, 0x00, 0x0E, 0x01, 0x84, 0x01, 0x66, 0x01
	.byte 0x92, 0x01, 0x3F, 0x4F, 0xE4, 0x00, 0xA3, 0x00, 0x22, 0x00, 0xAD, 0x00, 0x32, 0x01, 0xAE, 0x00
	.byte 0xD6, 0x00, 0x67, 0x01, 0x90, 0x01, 0x42, 0x4F, 0xCB, 0x00, 0xB9, 0x00, 0x10, 0x00, 0x3E, 0x01
	.byte 0x95, 0x01, 0x90, 0x01, 0xC2, 0x01, 0x45, 0x4F, 0x24, 0x00, 0xAD, 0x00, 0xCF, 0x00, 0x46, 0x01
	.byte 0x09, 0x01, 0x6C, 0x00, 0x1B, 0x01, 0x48, 0x4F, 0xB9, 0x00, 0xC5, 0x00, 0xC1, 0x00, 0x0E, 0x01
	.byte 0xEE, 0x00, 0x17, 0x01, 0xDF, 0x00, 0x44, 0x00, 0x66, 0x01, 0xA2, 0x01, 0x4A, 0x4F, 0xE3, 0x00
	.byte 0x2F, 0x00, 0x1F, 0x01, 0x15, 0x00, 0x41, 0x01, 0x39, 0x01, 0x4B, 0x4F, 0xDE, 0x00, 0xCD, 0x00
	.byte 0x99, 0x00, 0x26, 0x00, 0x4F, 0x01, 0x4C, 0x4F, 0x0E, 0x01, 0xF4, 0x00, 0xFD, 0x00, 0x39, 0x01
	.byte 0x11, 0x01, 0xE2, 0x00, 0xA4, 0x00, 0x41, 0x01, 0x83, 0x01, 0xFC, 0x00, 0xAC, 0x01, 0x85, 0x01
	.byte 0x4E, 0x4F, 0xF4, 0x00, 0x69, 0x00, 0xEC, 0x00, 0xA1, 0x01, 0x04, 0x01, 0x4F, 0x4F, 0x0E, 0x00
	.byte 0xCE, 0x00, 0x31, 0x01, 0xF4, 0x00, 0xF6, 0x00, 0x41, 0x01, 0x85, 0x01, 0xA7, 0x01, 0xA8, 0x01
	.byte 0xA6, 0x01, 0x82, 0x01, 0x50, 0x4F, 0x1B, 0x01, 0x22, 0x00, 0x17, 0x00, 0x09, 0x01, 0xAE, 0x00
	.byte 0x67, 0x00, 0xBA, 0x01, 0x97, 0x01, 0x53, 0x4F, 0x07, 0x00, 0x09, 0x00, 0x08, 0x00, 0xC1, 0x00
	.byte 0xFC, 0x00, 0xE2, 0x00, 0xDF, 0x00, 0x80, 0x01, 0x81, 0x01, 0xAB, 0x01, 0xA2, 0x01, 0x55, 0x4F
	.byte 0xF2, 0x00, 0x1D, 0x00, 0xFD, 0x00, 0xAE, 0x00, 0x81, 0x00, 0xB3, 0x01, 0xA7, 0x01, 0xA8, 0x01
	.byte 0xA6, 0x01, 0x57, 0x4F, 0xA4, 0x00, 0x11, 0x01, 0x2F, 0x00, 0xBA, 0x00, 0x58, 0x4F, 0xA4, 0x00
	.byte 0x11, 0x01, 0x2F, 0x00, 0xBA, 0x00, 0x59, 0x4F, 0xE2, 0x00, 0x3E, 0x01, 0x0F, 0x01, 0xE3, 0x00
	.byte 0x95, 0x01, 0x5A, 0x4F, 0xE2, 0x00, 0x3E, 0x01, 0x4A, 0x00, 0xE3, 0x00, 0x95, 0x01, 0x5B, 0x4F
	.byte 0xBF, 0x00, 0xEB, 0x00, 0x2A, 0x00, 0xB2, 0x00, 0x4F, 0x00, 0x4B, 0x00, 0xAA, 0x00, 0xB5, 0x01
	.byte 0x5C, 0x4F, 0x8A, 0x00, 0x97, 0x00, 0x7B, 0x00, 0xDC, 0x00, 0xAE, 0x00, 0xC2, 0x00, 0x5E, 0x4F
	.byte 0x38, 0x00, 0x26, 0x00, 0x25, 0x00, 0xF6, 0x00, 0x60, 0x4F, 0x26, 0x00, 0x25, 0x00, 0xCF, 0x00
	.byte 0xAD, 0x00, 0xD6, 0x00, 0xAE, 0x00, 0x5A, 0x00, 0x41, 0x01, 0x6F, 0x00, 0x22, 0x00, 0x62, 0x4F
	.byte 0x50, 0x01, 0xB8, 0x00, 0x22, 0x00, 0xCD, 0x00, 0x6F, 0x00, 0x17, 0x00, 0x19, 0x01, 0xF6, 0x00
	.byte 0xAA, 0x01, 0x01, 0x01, 0x64, 0x4F, 0x1C, 0x01, 0xCB, 0x00, 0xD6, 0x00, 0x19, 0x01, 0x59, 0x00
	.byte 0x5A, 0x00, 0x65, 0x4F, 0xF8, 0x00, 0x46, 0x01, 0xA4, 0x00, 0x0F, 0x01, 0xAC, 0x01, 0x85, 0x00
	.byte 0xF3, 0x00, 0x67, 0x4F, 0xE3, 0x00, 0x9D, 0x00, 0x12, 0x01, 0x32, 0x00, 0xE2, 0x00, 0x11, 0x01
	.byte 0x0F, 0x01, 0x09, 0x01, 0xFC, 0x00, 0x10, 0x01, 0xAB, 0x01, 0x68, 0x4F, 0x74, 0x00, 0x62, 0x00
	.byte 0x10, 0x00, 0xAF, 0x00, 0xD2, 0x00, 0x6B, 0x4F, 0x40, 0x01, 0x33, 0x00, 0x2A, 0x01, 0xDF, 0x00
	.byte 0x44, 0x00, 0x43, 0x00, 0x09, 0x01, 0x59, 0x01, 0x92, 0x01, 0x6D, 0x4F, 0x61, 0x00, 0x72, 0x00
	.byte 0xE4, 0x00, 0x63, 0x00, 0x29, 0x01, 0x97, 0x01, 0x6F, 0x4F, 0xAF, 0x00, 0x18, 0x00, 0x0D, 0x00
	.byte 0x44, 0x00, 0x2E, 0x00, 0xAE, 0x00, 0x9A, 0x00, 0x90, 0x01, 0xE8, 0x00, 0xCA, 0x01, 0x70, 0x4F
	.byte 0xFE, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x22, 0x00, 0xB8, 0x00, 0x74, 0x01, 0x90, 0x01, 0x73, 0x4F
	.byte 0x25, 0x00, 0xFA, 0x00, 0xD1, 0x00, 0x38, 0x00, 0xAF, 0x00, 0x24, 0x00, 0x75, 0x4F, 0x2C, 0x01
	.byte 0x1B, 0x01, 0x22, 0x00, 0xF6, 0x00, 0x1A, 0x01, 0x14, 0x01, 0xE8, 0x00, 0x79, 0x4F, 0x70, 0x00
	.byte 0x69, 0x00, 0xF3, 0x00, 0x9D, 0x00, 0x7A, 0x01, 0x41, 0x01, 0x7B, 0x4F, 0xE5, 0x00, 0x1A, 0x01
	.byte 0x0E, 0x00, 0x9D, 0x00, 0x67, 0x00, 0x1C, 0x00, 0xB8, 0x01, 0x7D, 0x4F, 0xF3, 0x00, 0xE1, 0x00
	.byte 0x2C, 0x01, 0x5F, 0x00, 0x71, 0x00, 0x6D, 0x00, 0x36, 0x00, 0x72, 0x00, 0x41, 0x01, 0x7F, 0x4F
	.byte 0xF8, 0x00, 0xF4, 0x00, 0x7D, 0x01, 0x32, 0x00, 0x85, 0x00, 0xD2, 0x01, 0x80, 0x4F, 0x32, 0x00
	.byte 0x15, 0x01, 0x0F, 0x01, 0xFC, 0x00, 0xA1, 0x01, 0x92, 0x00, 0x81, 0x4F, 0x32, 0x00, 0xC2, 0x00
	.byte 0xC1, 0x00, 0x36, 0x01, 0x1E, 0x01, 0xE4, 0x00, 0xA9, 0x01, 0x73, 0x01, 0x6D, 0x00, 0x83, 0x4F
	.byte 0x1E, 0x01, 0xC2, 0x00, 0xDC, 0x00, 0x20, 0x01, 0x06, 0x01, 0xB9, 0x00, 0xD2, 0x01, 0x85, 0x4F
	.byte 0x1D, 0x00, 0x15, 0x00, 0x0D, 0x00, 0x49, 0x00, 0x0B, 0x01, 0xB5, 0x01, 0xEB, 0x00, 0xAE, 0x00
	.byte 0x5C, 0x01, 0x86, 0x4F, 0x32, 0x00, 0xAE, 0x00, 0x5F, 0x00, 0x8A, 0x00, 0x11, 0x01, 0xF8, 0x00
	.byte 0x87, 0x4F, 0xE2, 0x00, 0xB9, 0x00, 0x26, 0x00, 0x15, 0x01, 0xAE, 0x00, 0xA4, 0x00, 0xD4, 0x00
	.byte 0xAC, 0x01, 0x82, 0x01, 0x85, 0x01, 0x74, 0x01, 0x7E, 0x01, 0x89, 0x4F, 0x4F, 0x01, 0xBF, 0x00
	.byte 0xCD, 0x00, 0x32, 0x00, 0x75, 0x00, 0x8B, 0x4F, 0x5A, 0x01, 0xFE, 0x00, 0x00, 0x01, 0xFF, 0x00
	.byte 0x19, 0x01, 0x9D, 0x00, 0xAE, 0x00, 0x5A, 0x00, 0x44, 0x01, 0x8E, 0x4F, 0x1F, 0x01, 0x2C, 0x01
	.byte 0x22, 0x00, 0x30, 0x00, 0x70, 0x00, 0x6D, 0x00, 0x88, 0x01, 0x91, 0x4F, 0xDE, 0x00, 0x82, 0x00
	.byte 0x5A, 0x01, 0x85, 0x00, 0xD6, 0x00, 0x9D, 0x00, 0x91, 0x01, 0xAD, 0x00, 0xBD, 0x00, 0x92, 0x4F
	.byte 0x96, 0x00, 0x30, 0x00, 0x5A, 0x01, 0x2C, 0x01, 0xBD, 0x01, 0x88, 0x01, 0x93, 0x4F, 0x38, 0x00
	.byte 0x25, 0x00, 0x52, 0x00, 0xEF, 0x00, 0x5D, 0x01, 0xA8, 0x01, 0xA5, 0x01, 0x97, 0x01, 0xA3, 0x4F
	.byte 0x84, 0x01, 0x4A, 0x00, 0x41, 0x01, 0x22, 0x00, 0x26, 0x00, 0x48, 0x01, 0x92, 0x01, 0x25, 0x00
	.byte 0x85, 0x00, 0x14, 0x01, 0xA6, 0x4F, 0x07, 0x00, 0x09, 0x00, 0x18, 0x00, 0xE3, 0x00, 0x01, 0x01
	.byte 0x74, 0x00, 0x0E, 0x01, 0xFC, 0x00, 0x2B, 0x01, 0x44, 0x00, 0xA9, 0x4F, 0xCA, 0x01, 0x30, 0x00
	.byte 0x19, 0x01, 0x2C, 0x01, 0xBD, 0x00, 0xAD, 0x00, 0xAF, 0x00, 0x61, 0x00, 0x88, 0x01, 0x38, 0x00
	.byte 0xAC, 0x4F, 0x29, 0x01, 0x1F, 0x00, 0xE4, 0x00, 0x36, 0x01, 0x1C, 0x00, 0xC1, 0x00, 0x26, 0x00
	.byte 0xAF, 0x4F, 0x62, 0x00, 0x5A, 0x01, 0x26, 0x00, 0x9A, 0x00, 0x6F, 0x00, 0xCD, 0x00, 0x3C, 0x01
	.byte 0x91, 0x01, 0xB3, 0x4F, 0xA7, 0x01, 0xA8, 0x01, 0xA6, 0x01, 0x62, 0x00, 0x50, 0x01, 0x24, 0x00
	.byte 0xB6, 0x4F, 0xBF, 0x00, 0xEB, 0x00, 0x2A, 0x00, 0xB2, 0x00, 0x4F, 0x00, 0x4B, 0x00, 0xAA, 0x00
	.byte 0xB5, 0x01, 0x46, 0x01, 0xB8, 0x4F, 0xF2, 0x00, 0x25, 0x00, 0x26, 0x00, 0x2B, 0x00, 0x15, 0x00
	.byte 0x17, 0x00, 0x12, 0x00, 0x67, 0x01, 0xBA, 0x4F, 0x1D, 0x00, 0xB8, 0x00, 0x74, 0x00, 0x26, 0x00
	.byte 0x5E, 0x01, 0x22, 0x00, 0x67, 0x00, 0xAE, 0x00, 0x5A, 0x00, 0xC1, 0x4F, 0x57, 0x01, 0x2C, 0x00
	.byte 0x39, 0x01, 0x6F, 0x00, 0xCD, 0x00, 0x04, 0x01, 0xAF, 0x00, 0xC2, 0x4F, 0xBD, 0x00, 0x1D, 0x00
	.byte 0x9A, 0x00, 0xA3, 0x00, 0x3C, 0x01, 0x03, 0x00, 0xD2, 0x00, 0xE2, 0x00, 0xC4, 0x4F, 0x4B, 0x00
	.byte 0xE6, 0x00, 0x41, 0x01, 0x0B, 0x01, 0x40, 0x01, 0x38, 0x01, 0xC6, 0x4F, 0x44, 0x00, 0xF3, 0x00
	.byte 0xFE, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x19, 0x01, 0x06, 0x01, 0xAE, 0x00, 0x85, 0x00, 0x5A, 0x00
	.byte 0xC9, 0x4F, 0x06, 0x01, 0x22, 0x00, 0xC2, 0x00, 0x32, 0x00, 0x72, 0x00, 0x5F, 0x00, 0xCB, 0x4F
	.byte 0x39, 0x01, 0xFC, 0x00, 0xE3, 0x00, 0xBA, 0x00, 0xCA, 0x01, 0xD5, 0x00, 0x43, 0x00, 0x47, 0x01
	.byte 0x9F, 0x01, 0x09, 0x00, 0x08, 0x00, 0x07, 0x00, 0xCF, 0x4F, 0x2C, 0x00, 0x27, 0x00, 0x62, 0x00
	.byte 0x1C, 0x00, 0x39, 0x01, 0x74, 0x01, 0xD1, 0x4F, 0x32, 0x00, 0xAE, 0x00, 0x5F, 0x00, 0x8A, 0x00
	.byte 0x11, 0x01, 0xF8, 0x00, 0x69, 0x00, 0xD2, 0x4F, 0xE4, 0x00, 0x2B, 0x00, 0x7B, 0x00, 0x26, 0x00
	.byte 0xF2, 0x00, 0xB8, 0x00, 0x36, 0x01, 0x82, 0x01, 0xD6, 0x4F, 0x78, 0x00, 0x1D, 0x00, 0x6A, 0x00
	.byte 0x6F, 0x00, 0xCD, 0x00, 0x48, 0x01, 0xD7, 0x4F, 0xF8, 0x00, 0x5F, 0x00, 0x66, 0x00, 0xF4, 0x00
	.byte 0xFC, 0x00, 0x0F, 0x01, 0x6D, 0x00, 0x66, 0x01, 0x2A, 0x01, 0x69, 0x01, 0xCC, 0x00, 0xD8, 0x4F
	.byte 0xD9, 0x00, 0x76, 0x00, 0xD7, 0x00, 0x38, 0x01, 0xA4, 0x00, 0x44, 0x00, 0x0E, 0x01, 0x64, 0x01
	.byte 0x83, 0x01, 0xD9, 0x4F, 0xE3, 0x00, 0x65, 0x00, 0x61, 0x00, 0xA1, 0x01, 0x30, 0x00, 0xDA, 0x4F
	.byte 0xC2, 0x00, 0xDC, 0x00, 0x6C, 0x00, 0x1E, 0x01, 0x20, 0x01, 0xA9, 0x01, 0xDB, 0x4F, 0xE1, 0x00
	.byte 0xC8, 0x00, 0xEF, 0x00, 0xB8, 0x00, 0x26, 0x00, 0x25, 0x00, 0xE8, 0x00, 0x48, 0x01, 0x22, 0x00
	.byte 0xBA, 0x01, 0xDE, 0x4F, 0x7A, 0x00, 0xCC, 0x00, 0x26, 0x00, 0xAE, 0x00, 0xA4, 0x00, 0x12, 0x00
	.byte 0xE4, 0x00, 0xAC, 0x01, 0xDF, 0x4F, 0xEE, 0x00, 0xC5, 0x00, 0x2C, 0x00, 0xAA, 0x00, 0x47, 0x01
	.byte 0x88, 0x00, 0x61, 0x00, 0x9A, 0x01, 0xF2, 0x00, 0x43, 0x00, 0x4E, 0x01, 0x2B, 0x01, 0xA2, 0x01
	.byte 0xE1, 0x4F, 0xFE, 0x00, 0x00, 0x01, 0xFF, 0x00, 0xAE, 0x00, 0x2F, 0x01, 0x22, 0x00, 0x48, 0x01
	.byte 0xE3, 0x4F, 0xB9, 0x00, 0x67, 0x00, 0x1C, 0x00, 0xA3, 0x00, 0x6D, 0x00, 0x12, 0x00, 0x61, 0x00
	.byte 0xE4, 0x00, 0x90, 0x01, 0xE5, 0x4F, 0x7E, 0x01, 0x6C, 0x01, 0xDF, 0x00, 0x1D, 0x00, 0x9A, 0x01
	.byte 0x60, 0x00, 0xFC, 0x00, 0x66, 0x01, 0x09, 0x01, 0xEE, 0x00, 0xA2, 0x01, 0xE7, 0x4F, 0x4F, 0x00
	.byte 0x4E, 0x00, 0x4B, 0x00, 0x15, 0x00, 0xEB, 0x00, 0x59, 0x01, 0x49, 0x00, 0x84, 0x01, 0xE8, 0x4F
	.byte 0xBA, 0x00, 0xCC, 0x00, 0xAF, 0x00, 0x91, 0x01, 0x96, 0x00, 0x3C, 0x00, 0x41, 0x01, 0x61, 0x00
	.byte 0xEA, 0x4F, 0xEF, 0x00, 0x38, 0x00, 0x72, 0x00, 0x15, 0x00, 0x2C, 0x01, 0x9D, 0x00, 0xF3, 0x00
	.byte 0x5A, 0x01, 0x96, 0x00, 0x44, 0x01, 0xEB, 0x4F, 0x49, 0x00, 0x59, 0x01, 0x92, 0x01, 0x4A, 0x00
	.byte 0x26, 0x00, 0x36, 0x00, 0x17, 0x00, 0xFF, 0xFF

	.global UNK05_021F8A34
UNK05_021F8A34: ; 0x021F8A34
	.word 0x00000024, MOD05_021EDA98, MOD05_021EDAE8, MOD05_021EDAF4
	.word MOD05_021EDB10

	.global UNK05_021F8A48
UNK05_021F8A48: ; 0x021F8A48
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8A60
UNK05_021F8A60: ; 0x021F8A60
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global UNK05_021F8A6C
UNK05_021F8A6C: ; 0x021F8A6C
	.word 0x00000030, MOD05_021EDC14, MOD05_021EDC4C, MOD05_021EDC50
	.word MOD05_021EDCFC

	.global UNK05_021F8A80
UNK05_021F8A80: ; 0x021F8A80
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global UNK05_021F8AA4
UNK05_021F8AA4: ; 0x021F8AA4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021F8B04
UNK05_021F8B04: ; 0x021F8B04
	.word MOD05_021EF16C, MOD05_021EE114

	.global UNK05_021F8B0C
UNK05_021F8B0C: ; 0x021F8B0C
	.word MOD05_021EF1FC, MOD05_021EE1E4

	.global UNK05_021F8B14
UNK05_021F8B14: ; 0x021F8B14
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global UNK05_021F8B20
UNK05_021F8B20: ; 0x021F8B20
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global UNK05_021F8B44
UNK05_021F8B44: ; 0x021F8B44
	.byte 0x03, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0x15, 0x03

	.global UNK05_021F8B4C
UNK05_021F8B4C: ; 0x021F8B4C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x20, 0x00, 0x20, 0x00, 0x00, 0x08, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021F8B6C
UNK05_021F8B6C: ; 0x021F8B6C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF

	.global UNK05_021F8B78
UNK05_021F8B78: ; 0x021F8B78
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021F8B84
UNK05_021F8B84: ; 0x021F8B84
	.byte 0x07, 0x00, 0x00, 0x00

	.global UNK05_021F8B88
UNK05_021F8B88: ; 0x021F8B88
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0x00, 0x00

	.global UNK05_021F8B90
UNK05_021F8B90: ; 0x021F8B90
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0x00, 0x00

	.global UNK05_021F8BA0
UNK05_021F8BA0: ; 0x021F8BA0
	.word MOD05_021F0CF0, MOD05_021F18A4, MOD05_021F0D18, MOD05_021F0D44
	.word MOD05_021F0D70

	.global UNK05_021F8BB4
UNK05_021F8BB4: ; 0x021F8BB4
	.word MOD05_021F0CF0, MOD05_021F17A0, MOD05_021F0D18, MOD05_021F0D44
	.word MOD05_021F0D70

	.global UNK05_021F8BC8
UNK05_021F8BC8: ; 0x021F8BC8
	.word MOD05_021F0CF0, MOD05_021F0DB4, MOD05_021F0D18, MOD05_021F0D44
	.word MOD05_021F0D70

	.global UNK05_021F8BDC
UNK05_021F8BDC: ; 0x021F8BDC
	.word MOD05_021F1B0C, MOD05_021F1B2C, MOD05_021F1B58, MOD05_021F1B60
	.word MOD05_021F1B8C

	.global UNK05_021F8BF0
UNK05_021F8BF0: ; 0x021F8BF0
	.word MOD05_021F19FC, MOD05_021F1A44, MOD05_021F1A48, MOD05_021F1A60
	.word MOD05_021F1A98

	.global UNK05_021F8C04
UNK05_021F8C04: ; 0x021F8C04
	.word MOD05_021F0ADC, MOD05_021F0B9C, MOD05_021F0B18, MOD05_021F0B2C
	.word MOD05_021F0B58

	.global UNK05_021F8C18
UNK05_021F8C18: ; 0x021F8C18
	.word MOD05_021F0CF0, MOD05_021F1234, MOD05_021F0D18, MOD05_021F0D44
	.word MOD05_021F0D70

	.global UNK05_021F8C2C
UNK05_021F8C2C: ; 0x021F8C2C
	.word MOD05_021F0CF0, MOD05_021F16D4, MOD05_021F0D18, MOD05_021F0D44
	.word MOD05_021F0D70

	.global UNK05_021F8C40
UNK05_021F8C40: ; 0x021F8C40
	.word MOD05_021F05C4, MOD05_021F071C, MOD05_021F05F0, MOD05_021F0604
	.word MOD05_021F0634

	.global UNK05_021F8C54
UNK05_021F8C54: ; 0x021F8C54
	.word FUN_0205C3B0, FUN_0205C3D0, FUN_0205C490, FUN_0205C4A8
	.word FUN_0205C4D8

	.global UNK05_021F8C68
UNK05_021F8C68: ; 0x021F8C68
	.word MOD05_021F05C4, MOD05_021F067C, MOD05_021F05F0, MOD05_021F0604
	.word MOD05_021F0634

	.global UNK05_021F8C7C
UNK05_021F8C7C: ; 0x021F8C7C
	.word MOD05_021F1A14, MOD05_021F1A44, MOD05_021F1A48, MOD05_021F1A60
	.word MOD05_021F1AB8

	.global UNK05_021F8C90
UNK05_021F8C90: ; 0x021F8C90
	.word MOD05_021F19E4, MOD05_021F1A44, MOD05_021F1A48, MOD05_021F1A60
	.word MOD05_021F1A78

	.global UNK05_021F8CA4
UNK05_021F8CA4: ; 0x021F8CA4
	.word MOD05_021F0CF0, MOD05_021F1838, MOD05_021F0D18, MOD05_021F0D44
	.word MOD05_021F0D70

	.global UNK05_021F8CB8
UNK05_021F8CB8: ; 0x021F8CB8
	.word MOD05_021F05C4, MOD05_021F0A04, MOD05_021F05F0, MOD05_021F0604
	.word MOD05_021F0634

	.global UNK05_021F8CCC
UNK05_021F8CCC: ; 0x021F8CCC
	.word MOD05_021F05C4, MOD05_021F06F0, MOD05_021F05F0, MOD05_021F0604
	.word MOD05_021F0634

	.global UNK05_021F8CE0
UNK05_021F8CE0: ; 0x021F8CE0
	.word MOD05_021F05C4, MOD05_021F0C28, MOD05_021F05F0, MOD05_021F0604
	.word MOD05_021F0634

	.global UNK05_021F8CF4
UNK05_021F8CF4: ; 0x021F8CF4
	.word MOD05_021F0CF0, MOD05_021F1440, MOD05_021F0D18, MOD05_021F0D44
	.word MOD05_021F0D70

	.global UNK05_021F8D08
UNK05_021F8D08: ; 0x021F8D08
	.word MOD05_021F1A2C, MOD05_021F1A44, MOD05_021F1A48, MOD05_021F1A60
	.word MOD05_021F1AD8

	.global UNK05_021F8D1C
UNK05_021F8D1C: ; 0x021F8D1C
	.word MOD05_021F1BD0, MOD05_021F1BF4, MOD05_021F1C14, MOD05_021F1B60
	.word MOD05_021F1B8C

	.global UNK05_021F8D30
UNK05_021F8D30: ; 0x021F8D30
	.word MOD05_021F0CF0, MOD05_021F1738, MOD05_021F0D18, MOD05_021F0D44
	.word MOD05_021F0D70

	.global UNK05_021F8D44
UNK05_021F8D44: ; 0x021F8D44
	.byte 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8D5C
UNK05_021F8D5C: ; 0x021F8D5C
	.byte 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8D74
UNK05_021F8D74: ; 0x021F8D74
	.byte 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8D8C
UNK05_021F8D8C: ; 0x021F8D8C
	.byte 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8DA4
UNK05_021F8DA4: ; 0x021F8DA4
	.byte 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8DBC
UNK05_021F8DBC: ; 0x021F8DBC
	.byte 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8DD4
UNK05_021F8DD4: ; 0x021F8DD4
	.byte 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8DEC
UNK05_021F8DEC: ; 0x021F8DEC
	.byte 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8E10
UNK05_021F8E10: ; 0x021F8E10
	.byte 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8E34
UNK05_021F8E34: ; 0x021F8E34
	.byte 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8E58
UNK05_021F8E58: ; 0x021F8E58
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x30, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8E94
UNK05_021F8E94: ; 0x021F8E94
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8ED0
UNK05_021F8ED0: ; 0x021F8ED0
	.byte 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00
	.byte 0x23, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8F0C
UNK05_021F8F0C: ; 0x021F8F0C
	.byte 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8F48
UNK05_021F8F48: ; 0x021F8F48
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x30, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00
	.byte 0x44, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8F90
UNK05_021F8F90: ; 0x021F8F90
	.byte 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00
	.byte 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x50, 0x00, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00
	.byte 0x6F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F8FFC
UNK05_021F8FFC: ; 0x021F8FFC
	.byte 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x40, 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00
	.byte 0x4F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x53, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x58, 0x00, 0x00, 0x00, 0x5B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x5C, 0x00, 0x00, 0x00
	.byte 0x5F, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00

	.global UNK05_021F9080
UNK05_021F9080: ; 0x021F9080
	.word MOD05_021F1EDC
	.word MOD05_021F1EF4
	.word MOD05_021F1EF8
	.word MOD05_021F1EFC
	.word MOD05_021F1F00

	.global UNK05_021F9094
UNK05_021F9094: ; 0x021F9094
	.word 0x00000000
	.byte 0x78, 0x01, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x79, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x7A, 0x01, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x7B, 0x01, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x7C, 0x01, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x7F, 0x01, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x86, 0x01, 0x00, 0x00
	.byte 0x07, 0x00, 0x00, 0x00, 0x87, 0x01, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x88, 0x01, 0x00, 0x00
	.byte 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021F90E4
UNK05_021F90E4: ; 0x021F90E4
	.byte 0x00, 0x00, 0x00, 0x00, 0x89, 0x01, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x8A, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x8B, 0x01, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x8C, 0x01, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x8D, 0x01, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x8E, 0x01, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x8F, 0x01, 0x00, 0x00
	.byte 0x07, 0x00, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x91, 0x01, 0x00, 0x00
	.byte 0x09, 0x00, 0x00, 0x00, 0x92, 0x01, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x93, 0x01, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x94, 0x01, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x95, 0x01, 0x00, 0x00
	.byte 0x0D, 0x00, 0x00, 0x00, 0x96, 0x01, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x97, 0x01, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x98, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x99, 0x01, 0x00, 0x00
	.byte 0x11, 0x00, 0x00, 0x00, 0x9A, 0x01, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x9B, 0x01, 0x00, 0x00
	.byte 0x13, 0x00, 0x00, 0x00, 0x9C, 0x01, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x9D, 0x01, 0x00, 0x00
	.byte 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021F9194
UNK05_021F9194: ; 0x021F9194
	.word 0x00001001
	.word 0x00001002
	.word 0x00001003
	.word 0x00001004
	.word 0x00001005
	.word 0x00001006
	.word 0x00001007
	.word 0x00001008
	.word 0x00001009
	.word 0x0000100A
	.word 0x0000100B
	.word 0x0000100C
	.word 0x0000100D
	.word 0x0000100E
	.word 0x0000100F
	.word 0x00001010
	.word 0x00001011
	.word 0x00001012
	.word 0x00001013
	.word 0x00001014
	.word 0x00001015
	.word 0x00001016
	.word 0x00001017
	.word 0x00001018
	.word 0x00001019
	.word 0x0000101A
	.word 0x0000101B
	.word 0x0000101C
	.word 0x0000101D
	.word 0x0000101E
	.word 0x0000101F
	.word 0x00001020
	.word 0x00001021
	.word 0x00001022
	.word 0x00001023
	.word 0x00001024
	.word 0x00001025
	.word 0x00001026
	.word 0x00001027
	.word 0x00001028
	.word 0x00001029
	.word 0x0000102A
	.word 0x0000102B
	.word 0x0000102C
	.word 0x0000102D
	.word 0x0000102E
	.word 0x0000102F
	.word 0x00001030
	.word 0x00001031
	.word 0x00001032
	.word 0x00001033
	.word 0x00001034
	.word 0x00001035
	.word 0x00001036
	.word 0x00001037
	.word 0x00001038
	.word 0x00001039
	.word 0x0000103A
	.word 0x0000103B
	.word 0x0000103C
	.word 0x0000103D
	.word 0x0000103E
	.word 0x0000103F
	.word 0x00001040
	.word 0x00001041
	.word 0x00001042
	.word 0x00001043
	.word 0x00001044
	.word 0x00001045
	.word 0x00001046
	.word 0x00001047
	.word 0x00001048
	.word 0x00001049
	.word 0x0000104A
	.word 0x0000104B
	.word 0x0000104C
	.word 0x0000104D
	.word 0x0000104E
	.word 0x0000104F
	.word 0x00001050
	.word 0x00001051
	.word 0x00001052
	.word 0x00001053
	.word 0x00001054
	.word 0x00001055
	.word 0x00001056
	.word 0x00001057
	.word 0x00001058
	.word 0x00001059
	.word 0x0000105A
	.word 0x0000105B
	.word 0x0000105C
	.word 0x0000105D
	.word 0x0000105E
	.word 0x0000105F
	.word 0x00001060
	.word 0x00001061
	.word 0x00001062
	.word 0x00001063
	.word 0x00001064
	.word 0x00001065
	.word 0x00001066
	.word 0x00001067
	.word 0x00001068
	.word 0x00001069
	.word 0x0000106A
	.word 0x0000106B
	.word 0x0000106C
	.word 0x0000106D
	.word 0x0000106E
	.word 0x0000106F
	.word 0x00001070
	.word 0x00001071
	.word 0x00001072
	.word 0x00001073
	.word 0x00001074
	.word 0x00001075
	.word 0x00001076
	.word 0x00001077
	.word 0x00001078
	.word 0x00001079
	.word 0x0000107A
	.word 0x0000107B
	.word 0x0000107C
	.word 0x0000107D
	.word 0x0000107E
	.word 0x0000107F
	.word 0x00001080
	.word 0x00001081
	.word 0x00001082
	.word 0x00001083
	.word 0x00001084
	.word 0x00001085
	.word 0x00001086
	.word 0x00001087
	.word 0x00001088
	.word 0x00001089
	.word 0x0000108A
	.word 0x0000108B
	.word 0x0000108C
	.word 0x0000108D
	.word 0x0000108E
	.word 0x0000108F
	.word 0x00001090
	.word 0x00001091
	.word 0x00001092
	.word 0x00001093
	.word 0x00001094
	.word 0x00001095
	.word 0x00001096
	.word 0x00001097
	.word 0x00001098
	.word 0x00001099
	.word 0x0000109A
	.word 0x0000109B
	.word 0x0000109C
	.word 0x0000109D
	.word 0x0000109E
	.word 0x0000109F
	.word 0x000010A0
	.word 0x000010A1
	.word 0x000010A2
	.word 0x000010A3
	.word 0x000010A4
	.word 0x000010A5
	.word 0x000010A6
	.word 0x000010A7
	.word 0x000010A8
	.word 0x000010A9
	.word 0x000010AA
	.word 0x000010AB
	.word 0x000010AC
	.word 0x000010AD
	.word 0x000010AE
	.word 0x000010AF
	.word 0x000010B0
	.word 0x000010B1
	.word 0x000010B2
	.word 0x000010B3
	.word 0x000010B4
	.word 0x000010B5
	.word 0x000010B6
	.word 0x000010B7
	.word 0x000010B8
	.word 0x000010B9
	.word 0x000010BA
	.word 0x000010BB
	.word 0x000010BC
	.word 0x000010BD
	.word 0x000010BE
	.word 0x000010BF
	.word 0x000010C0

	.global UNK05_021F9494
UNK05_021F9494: ; 0x021F9494
	.word 0x00, UNK05_021F8BC8
	.word 0x01, UNK05_021F8C68
	.word 0x02, UNK05_021F8C68
	.word 0x03, UNK05_021F8C68
	.word 0x04, UNK05_021F8C68
	.word 0x05, UNK05_021F8C68
	.word 0x06, UNK05_021F8C68
	.word 0x07, UNK05_021F8C68
	.word 0x08, UNK05_021F8C68
	.word 0x09, UNK05_021F8C68
	.word 0x0A, UNK05_021F8C68
	.word 0x0B, UNK05_021F8C68
	.word 0x0C, UNK05_021F8C68
	.word 0x0D, UNK05_021F8C68
	.word 0x0E, UNK05_021F8C68
	.word 0x0F, UNK05_021F8C68
	.word 0x10, UNK05_021F8C68
	.word 0x11, UNK05_021F8C68
	.word 0x12, UNK05_021F8C68
	.word 0x13, UNK05_021F8C68
	.word 0x14, UNK05_021F8C68
	.word 0x15, UNK05_021F8C18
	.word 0x16, UNK05_021F8C68
	.word 0x17, UNK05_021F8C68
	.word 0x18, UNK05_021F8C68
	.word 0x19, UNK05_021F8C68
	.word 0x1A, UNK05_021F8CB8
	.word 0x1B, UNK05_021F8C68
	.word 0x1C, UNK05_021F8C68
	.word 0x1D, UNK05_021F8C68
	.word 0x1E, UNK05_021F8C68
	.word 0x1F, UNK05_021F8C68
	.word 0x20, UNK05_021F8C68
	.word 0x21, UNK05_021F8C68
	.word 0x22, UNK05_021F8C68
	.word 0x23, UNK05_021F8C68
	.word 0x24, UNK05_021F8C68
	.word 0x25, UNK05_021F8C68
	.word 0x26, UNK05_021F8C68
	.word 0x27, UNK05_021F8C68
	.word 0x28, UNK05_021F8C68
	.word 0x29, UNK05_021F8C68
	.word 0x2A, UNK05_021F8C68
	.word 0x2B, UNK05_021F8C68
	.word 0x2C, UNK05_021F8C68
	.word 0x2D, UNK05_021F8C68
	.word 0x2E, UNK05_021F8C68
	.word 0x2F, UNK05_021F8C68
	.word 0x30, UNK05_021F8C68
	.word 0x31, UNK05_021F8C68
	.word 0x32, UNK05_021F8C68
	.word 0x33, UNK05_021F8C68
	.word 0x34, UNK05_021F8C68
	.word 0x35, UNK05_021F8C68
	.word 0x36, UNK05_021F8C68
	.word 0x37, UNK05_021F8C68
	.word 0x38, UNK05_021F8C68
	.word 0x39, UNK05_021F8C68
	.word 0x3A, UNK05_021F8C68
	.word 0x3B, UNK05_021F8C68
	.word 0x3C, UNK05_021F8C68
	.word 0x3D, UNK05_021F8C68
	.word 0x3E, UNK05_021F8C68
	.word 0x3F, UNK05_021F8C68
	.word 0x40, UNK05_021F8C68
	.word 0x41, UNK05_021F8C68
	.word 0x42, UNK05_021F8C68
	.word 0x43, UNK05_021F8C68
	.word 0x44, UNK05_021F8C68
	.word 0x45, UNK05_021F8C68
	.word 0x46, UNK05_021F8C68
	.word 0x47, UNK05_021F8C68
	.word 0x48, UNK05_021F8C68
	.word 0x49, UNK05_021F8C68
	.word 0x4A, UNK05_021F8C68
	.word 0x4B, UNK05_021F8C68
	.word 0x4C, UNK05_021F8C68
	.word 0x4D, UNK05_021F8C68
	.word 0x4E, UNK05_021F8C68
	.word 0x4F, UNK05_021F8C68
	.word 0x50, UNK05_021F8C68
	.word 0x51, UNK05_021F8C68
	.word 0x52, UNK05_021F8C68
	.word 0x53, UNK05_021F8C68
	.word 0x54, UNK05_021F8CCC
	.word 0x55, UNK05_021F8CCC
	.word 0x56, UNK05_021F8CCC
	.word 0x57, UNK05_021F8CCC
	.word 0x58, UNK05_021F8C68
	.word 0x59, UNK05_021F8C68
	.word 0x5A, UNK05_021F8C68
	.word 0x5B, UNK05_021F8C90
	.word 0x5C, UNK05_021F8C90
	.word 0x5D, UNK05_021F8C90
	.word 0x5E, UNK05_021F8C90
	.word 0x5F, UNK05_021F8C90
	.word 0x60, UNK05_021F8C90
	.word 0x61, UNK05_021F8BC8
	.word 0x62, UNK05_021F8C18
	.word 0x63, UNK05_021F8C68
	.word 0x64, UNK05_021F8C54
	.word 0x76, UNK05_021F8BF0
	.word 0x78, UNK05_021F8C68
	.word 0x79, UNK05_021F8C68
	.word 0x7A, UNK05_021F8C68
	.word 0x7B, UNK05_021F8C68
	.word 0x7C, UNK05_021F8C68
	.word 0x7D, UNK05_021F8C68
	.word 0x7E, UNK05_021F8C68
	.word 0x7F, UNK05_021F8C68
	.word 0x80, UNK05_021F8C68
	.word 0x81, UNK05_021F8C68
	.word 0x82, UNK05_021F8C68
	.word 0x83, UNK05_021F8C68
	.word 0x84, UNK05_021F8C68
	.word 0x85, UNK05_021F8C68
	.word 0x86, UNK05_021F8C68
	.word 0x87, UNK05_021F8C68
	.word 0x88, UNK05_021F8C68
	.word 0x89, UNK05_021F8C68
	.word 0x8A, UNK05_021F8C68
	.word 0x8B, UNK05_021F8C68
	.word 0x8C, UNK05_021F8C68
	.word 0x8D, UNK05_021F8C68
	.word 0x8E, UNK05_021F8C68
	.word 0x8F, UNK05_021F8C68
	.word 0x90, UNK05_021F8C68
	.word 0x91, UNK05_021F8C68
	.word 0x92, UNK05_021F8C68
	.word 0x93, UNK05_021F8C68
	.word 0x94, UNK05_021F8C68
	.word 0x95, UNK05_021F8C68
	.word 0x96, UNK05_021F8C68
	.word 0x97, UNK05_021F8D1C
	.word 0x98, UNK05_021F8D1C
	.word 0x99, UNK05_021F8D1C
	.word 0x9A, UNK05_021F8BDC
	.word 0x9B, UNK05_021F8BDC
	.word 0x9C, UNK05_021F8C40
	.word 0x9D, UNK05_021F8C40
	.word 0x9E, UNK05_021F8C68
	.word 0x9F, UNK05_021F8C40
	.word 0xA0, UNK05_021F8C40
	.word 0xA1, UNK05_021F8C40
	.word 0xA2, UNK05_021F8C68
	.word 0xA3, UNK05_021F8C68
	.word 0xA4, UNK05_021F8C68
	.word 0xA5, UNK05_021F8C68
	.word 0xA6, UNK05_021F8C68
	.word 0xA7, UNK05_021F8C68
	.word 0xA8, UNK05_021F8C68
	.word 0xA9, UNK05_021F8C68
	.word 0xAA, UNK05_021F8C68
	.word 0xAB, UNK05_021F8C68
	.word 0xAC, UNK05_021F8C68
	.word 0xAD, UNK05_021F8CE0
	.word 0xAE, UNK05_021F8C68
	.word 0xAF, UNK05_021F8C68
	.word 0xB0, UNK05_021F8D30
	.word 0xB1, UNK05_021F8D30
	.word 0xB4, UNK05_021F8BB4
	.word 0xB5, UNK05_021F8BB4
	.word 0xB2, UNK05_021F8C2C
	.word 0xB3, UNK05_021F8C2C
	.word 0xB6, UNK05_021F8CCC
	.word 0xB7, UNK05_021F8C7C
	.word 0xB8, UNK05_021F8CCC
	.word 0xB9, UNK05_021F8C68
	.word 0xBA, UNK05_021F8BC8
	.word 0xBB, UNK05_021F8BC8
	.word 0xBC, UNK05_021F8CF4
	.word 0xBD, UNK05_021F8CF4
	.word 0xBE, UNK05_021F8C68
	.word 0xBF, UNK05_021F8C68
	.word 0xC0, UNK05_021F8C68
	.word 0xC1, UNK05_021F8C68
	.word 0xC2, UNK05_021F8C68
	.word 0xC3, UNK05_021F8C04
	.word 0xC4, UNK05_021F8CA4
	.word 0xC5, UNK05_021F8CA4
	.word 0xC6, UNK05_021F8D30
	.word 0xC7, UNK05_021F8D30
	.word 0xC8, UNK05_021F8BA0
	.word 0xC9, UNK05_021F8BA0
	.word 0xCA, UNK05_021F8CCC
	.word 0xCB, UNK05_021F8CCC
	.word 0xCC, UNK05_021F8C68
	.word 0xCD, UNK05_021F8C68
	.word 0xCE, UNK05_021F8C68
	.word 0xCF, UNK05_021F8C68
	.word 0xD0, UNK05_021F8C68
	.word 0xD1, UNK05_021F8D08

; 0x021F9A94
	.byte 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.global UNK05_021F9A9C
UNK05_021F9A9C: ; 0x021F9A9C
	.byte 0x00, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x0E, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x12, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x91, 0x04, 0x00, 0x00
	.byte 0x16, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x1A, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x1C, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x1E, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x22, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x24, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x26, 0x00, 0x00, 0x00, 0x91, 0x04, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x91, 0x04, 0x00, 0x00
	.byte 0x28, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x2A, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x2B, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x2C, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x2E, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x30, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x32, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x34, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x36, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x38, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x3A, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x3C, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x3D, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x3E, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x40, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x42, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x44, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x46, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x48, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x4A, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x4B, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x4C, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x4D, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x4E, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x50, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x52, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x53, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x54, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x56, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x58, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x59, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x5A, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x5B, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x5C, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x5D, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x5E, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x60, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x61, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x62, 0x00, 0x00, 0x00, 0x91, 0x04, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x64, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00
	.byte 0x78, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x79, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x7A, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x7B, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x7C, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x7E, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x82, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x84, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x85, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x86, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x87, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x88, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x89, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x8A, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x8B, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x8C, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x8D, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x8E, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x8F, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x90, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x91, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x92, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x93, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x94, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x95, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x96, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x97, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x98, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x99, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x9A, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x9B, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x9C, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x9D, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x9E, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0x9F, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xA0, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xA1, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xA2, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xA3, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xA4, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xA5, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xA6, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xA7, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xA8, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xA9, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xAA, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xAB, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xAC, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xAD, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xAE, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xAF, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xB0, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xB1, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xB2, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xB3, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xB4, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xB5, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xB6, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xB7, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00
	.byte 0xB8, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xB9, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xBA, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xBB, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xBC, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xBD, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xBE, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xBF, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xC0, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xC1, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xC2, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xC3, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC4, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xC5, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xC6, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xC7, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00
	.byte 0xC9, 0x00, 0x00, 0x00, 0x51, 0x04, 0x00, 0x00, 0xCA, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0xCB, 0x00, 0x00, 0x00, 0x11, 0x04, 0x00, 0x00, 0xCC, 0x00, 0x00, 0x00, 0x91, 0x04, 0x00, 0x00
	.byte 0xCD, 0x00, 0x00, 0x00, 0x91, 0x04, 0x00, 0x00, 0xCE, 0x00, 0x00, 0x00, 0x91, 0x04, 0x00, 0x00
	.byte 0xCF, 0x00, 0x00, 0x00, 0x91, 0x04, 0x00, 0x00, 0xD0, 0x00, 0x00, 0x00, 0x91, 0x04, 0x00, 0x00
	.byte 0xD1, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021FA0AC
UNK05_021FA0AC: ; 0x021FA0AC
	.byte 0x00, 0x00, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x0E, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x12, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x5C, 0x00, 0x00, 0x00
	.byte 0x16, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00
	.byte 0x1A, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00
	.byte 0x1C, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00
	.byte 0x1E, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00
	.byte 0x22, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00
	.byte 0x24, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00
	.byte 0x26, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00
	.byte 0x28, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00
	.byte 0x2A, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x2B, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00
	.byte 0x2C, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00, 0x2B, 0x00, 0x00, 0x00
	.byte 0x2E, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00
	.byte 0x30, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00
	.byte 0x32, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00
	.byte 0x34, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00
	.byte 0x36, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00
	.byte 0x38, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00
	.byte 0x3A, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00
	.byte 0x3C, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0x3D, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00
	.byte 0x3E, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3D, 0x00, 0x00, 0x00
	.byte 0x40, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00
	.byte 0x42, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00
	.byte 0x44, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00
	.byte 0x46, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00
	.byte 0x48, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00
	.byte 0x4A, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x4B, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00
	.byte 0x4C, 0x00, 0x00, 0x00, 0x4A, 0x00, 0x00, 0x00, 0x4D, 0x00, 0x00, 0x00, 0x4B, 0x00, 0x00, 0x00
	.byte 0x4E, 0x00, 0x00, 0x00, 0x4C, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00, 0x4D, 0x00, 0x00, 0x00
	.byte 0x50, 0x00, 0x00, 0x00, 0x4E, 0x00, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00
	.byte 0x52, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x53, 0x00, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00
	.byte 0x54, 0x00, 0x00, 0x00, 0x52, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x53, 0x00, 0x00, 0x00
	.byte 0x56, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00
	.byte 0x58, 0x00, 0x00, 0x00, 0x56, 0x00, 0x00, 0x00, 0x59, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00
	.byte 0x5A, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x61, 0x00, 0x00, 0x00, 0x5B, 0x00, 0x00, 0x00
	.byte 0x62, 0x00, 0x00, 0x00, 0x5D, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 0x5E, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00
	.byte 0x02, 0x10, 0x00, 0x00, 0x61, 0x00, 0x00, 0x00, 0x03, 0x10, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00
	.byte 0x78, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 0x79, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00
	.byte 0x7A, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x7B, 0x00, 0x00, 0x00, 0x66, 0x00, 0x00, 0x00
	.byte 0x7C, 0x00, 0x00, 0x00, 0x67, 0x00, 0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00
	.byte 0x7E, 0x00, 0x00, 0x00, 0x69, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x6A, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x6B, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x6C, 0x00, 0x00, 0x00
	.byte 0x82, 0x00, 0x00, 0x00, 0x6D, 0x00, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x00, 0x00
	.byte 0x84, 0x00, 0x00, 0x00, 0x6F, 0x00, 0x00, 0x00, 0x85, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00
	.byte 0x86, 0x00, 0x00, 0x00, 0x71, 0x00, 0x00, 0x00, 0x87, 0x00, 0x00, 0x00, 0x72, 0x00, 0x00, 0x00
	.byte 0x88, 0x00, 0x00, 0x00, 0x73, 0x00, 0x00, 0x00, 0x89, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00
	.byte 0x8A, 0x00, 0x00, 0x00, 0x75, 0x00, 0x00, 0x00, 0x8B, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00
	.byte 0x8C, 0x00, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00, 0x8D, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
	.byte 0x8E, 0x00, 0x00, 0x00, 0x79, 0x00, 0x00, 0x00, 0x8F, 0x00, 0x00, 0x00, 0x7A, 0x00, 0x00, 0x00
	.byte 0x90, 0x00, 0x00, 0x00, 0x7B, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00
	.byte 0x92, 0x00, 0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0x93, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00
	.byte 0x94, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x95, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x96, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x97, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00
	.byte 0x98, 0x00, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0x99, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00
	.byte 0x9A, 0x00, 0x00, 0x00, 0x85, 0x00, 0x00, 0x00, 0x9B, 0x00, 0x00, 0x00, 0x86, 0x00, 0x00, 0x00
	.byte 0x9C, 0x00, 0x00, 0x00, 0x87, 0x00, 0x00, 0x00, 0x9D, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00
	.byte 0x9E, 0x00, 0x00, 0x00, 0x89, 0x00, 0x00, 0x00, 0x9F, 0x00, 0x00, 0x00, 0x8A, 0x00, 0x00, 0x00
	.byte 0xA0, 0x00, 0x00, 0x00, 0x8B, 0x00, 0x00, 0x00, 0xA1, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00
	.byte 0xA2, 0x00, 0x00, 0x00, 0x8D, 0x00, 0x00, 0x00, 0xA3, 0x00, 0x00, 0x00, 0x8E, 0x00, 0x00, 0x00
	.byte 0xA4, 0x00, 0x00, 0x00, 0x8F, 0x00, 0x00, 0x00, 0xA5, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00
	.byte 0xA6, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x00, 0xA7, 0x00, 0x00, 0x00, 0x92, 0x00, 0x00, 0x00
	.byte 0xA8, 0x00, 0x00, 0x00, 0x93, 0x00, 0x00, 0x00, 0xA9, 0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00
	.byte 0xAA, 0x00, 0x00, 0x00, 0x95, 0x00, 0x00, 0x00, 0xAB, 0x00, 0x00, 0x00, 0x96, 0x00, 0x00, 0x00
	.byte 0xAC, 0x00, 0x00, 0x00, 0x97, 0x00, 0x00, 0x00, 0xAD, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00
	.byte 0xAE, 0x00, 0x00, 0x00, 0x99, 0x00, 0x00, 0x00, 0xAF, 0x00, 0x00, 0x00, 0x9A, 0x00, 0x00, 0x00
	.byte 0xB0, 0x00, 0x00, 0x00, 0x9B, 0x00, 0x00, 0x00, 0xB1, 0x00, 0x00, 0x00, 0x9C, 0x00, 0x00, 0x00
	.byte 0xB4, 0x00, 0x00, 0x00, 0x9D, 0x00, 0x00, 0x00, 0xB5, 0x00, 0x00, 0x00, 0x9E, 0x00, 0x00, 0x00
	.byte 0xB2, 0x00, 0x00, 0x00, 0x9F, 0x00, 0x00, 0x00, 0xB3, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00
	.byte 0xB6, 0x00, 0x00, 0x00, 0xA1, 0x00, 0x00, 0x00, 0xB8, 0x00, 0x00, 0x00, 0xA2, 0x00, 0x00, 0x00
	.byte 0xB9, 0x00, 0x00, 0x00, 0xA3, 0x00, 0x00, 0x00, 0xBA, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x00
	.byte 0xBB, 0x00, 0x00, 0x00, 0xA5, 0x00, 0x00, 0x00, 0xBC, 0x00, 0x00, 0x00, 0xA6, 0x00, 0x00, 0x00
	.byte 0xBD, 0x00, 0x00, 0x00, 0xA7, 0x00, 0x00, 0x00, 0xBE, 0x00, 0x00, 0x00, 0xA8, 0x00, 0x00, 0x00
	.byte 0xBF, 0x00, 0x00, 0x00, 0xA9, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0xAA, 0x00, 0x00, 0x00
	.byte 0x04, 0x10, 0x00, 0x00, 0xAB, 0x00, 0x00, 0x00, 0x05, 0x10, 0x00, 0x00, 0xAC, 0x00, 0x00, 0x00
	.byte 0x06, 0x10, 0x00, 0x00, 0xAD, 0x00, 0x00, 0x00, 0x07, 0x10, 0x00, 0x00, 0xAE, 0x00, 0x00, 0x00
	.byte 0x08, 0x10, 0x00, 0x00, 0xAF, 0x00, 0x00, 0x00, 0x09, 0x10, 0x00, 0x00, 0xB0, 0x00, 0x00, 0x00
	.byte 0x0A, 0x10, 0x00, 0x00, 0xB1, 0x00, 0x00, 0x00, 0x0B, 0x10, 0x00, 0x00, 0xB2, 0x00, 0x00, 0x00
	.byte 0x0C, 0x10, 0x00, 0x00, 0xB3, 0x00, 0x00, 0x00, 0x0D, 0x10, 0x00, 0x00, 0xB4, 0x00, 0x00, 0x00
	.byte 0x0E, 0x10, 0x00, 0x00, 0xB5, 0x00, 0x00, 0x00, 0x0F, 0x10, 0x00, 0x00, 0xB6, 0x00, 0x00, 0x00
	.byte 0x10, 0x10, 0x00, 0x00, 0xB7, 0x00, 0x00, 0x00, 0x11, 0x10, 0x00, 0x00, 0xB8, 0x00, 0x00, 0x00
	.byte 0x12, 0x10, 0x00, 0x00, 0xB9, 0x00, 0x00, 0x00, 0x13, 0x10, 0x00, 0x00, 0xBA, 0x00, 0x00, 0x00
	.byte 0x14, 0x10, 0x00, 0x00, 0xBB, 0x00, 0x00, 0x00, 0x15, 0x10, 0x00, 0x00, 0xBC, 0x00, 0x00, 0x00
	.byte 0x16, 0x10, 0x00, 0x00, 0xBD, 0x00, 0x00, 0x00, 0x17, 0x10, 0x00, 0x00, 0xBE, 0x00, 0x00, 0x00
	.byte 0x18, 0x10, 0x00, 0x00, 0xBF, 0x00, 0x00, 0x00, 0x19, 0x10, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x1A, 0x10, 0x00, 0x00, 0xC1, 0x00, 0x00, 0x00, 0x1B, 0x10, 0x00, 0x00, 0xC2, 0x00, 0x00, 0x00
	.byte 0x1C, 0x10, 0x00, 0x00, 0xC3, 0x00, 0x00, 0x00, 0x1D, 0x10, 0x00, 0x00, 0xC4, 0x00, 0x00, 0x00
	.byte 0x1E, 0x10, 0x00, 0x00, 0xC5, 0x00, 0x00, 0x00, 0x1F, 0x10, 0x00, 0x00, 0xC6, 0x00, 0x00, 0x00
	.byte 0x20, 0x10, 0x00, 0x00, 0xC7, 0x00, 0x00, 0x00, 0x21, 0x10, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00
	.byte 0x22, 0x10, 0x00, 0x00, 0xC9, 0x00, 0x00, 0x00, 0x23, 0x10, 0x00, 0x00, 0xCA, 0x00, 0x00, 0x00
	.byte 0x24, 0x10, 0x00, 0x00, 0xCB, 0x00, 0x00, 0x00, 0x25, 0x10, 0x00, 0x00, 0xCC, 0x00, 0x00, 0x00
	.byte 0x26, 0x10, 0x00, 0x00, 0xCD, 0x00, 0x00, 0x00, 0x27, 0x10, 0x00, 0x00, 0xCE, 0x00, 0x00, 0x00
	.byte 0x28, 0x10, 0x00, 0x00, 0xCF, 0x00, 0x00, 0x00, 0x29, 0x10, 0x00, 0x00, 0xD0, 0x00, 0x00, 0x00
	.byte 0x2A, 0x10, 0x00, 0x00, 0xD1, 0x00, 0x00, 0x00, 0x2B, 0x10, 0x00, 0x00, 0xD2, 0x00, 0x00, 0x00
	.byte 0x2C, 0x10, 0x00, 0x00, 0xD3, 0x00, 0x00, 0x00, 0x2D, 0x10, 0x00, 0x00, 0xD4, 0x00, 0x00, 0x00
	.byte 0x2E, 0x10, 0x00, 0x00, 0xD5, 0x00, 0x00, 0x00, 0x2F, 0x10, 0x00, 0x00, 0xD6, 0x00, 0x00, 0x00
	.byte 0x30, 0x10, 0x00, 0x00, 0xD7, 0x00, 0x00, 0x00, 0x31, 0x10, 0x00, 0x00, 0xD8, 0x00, 0x00, 0x00
	.byte 0x32, 0x10, 0x00, 0x00, 0xD9, 0x00, 0x00, 0x00, 0x33, 0x10, 0x00, 0x00, 0xDA, 0x00, 0x00, 0x00
	.byte 0x34, 0x10, 0x00, 0x00, 0xDB, 0x00, 0x00, 0x00, 0x35, 0x10, 0x00, 0x00, 0xDC, 0x00, 0x00, 0x00
	.byte 0x36, 0x10, 0x00, 0x00, 0xDD, 0x00, 0x00, 0x00, 0x37, 0x10, 0x00, 0x00, 0xDE, 0x00, 0x00, 0x00
	.byte 0x38, 0x10, 0x00, 0x00, 0xDF, 0x00, 0x00, 0x00, 0x39, 0x10, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00
	.byte 0x3A, 0x10, 0x00, 0x00, 0xE1, 0x00, 0x00, 0x00, 0x3B, 0x10, 0x00, 0x00, 0xE2, 0x00, 0x00, 0x00
	.byte 0x3C, 0x10, 0x00, 0x00, 0xE3, 0x00, 0x00, 0x00, 0x3D, 0x10, 0x00, 0x00, 0xE4, 0x00, 0x00, 0x00
	.byte 0x3E, 0x10, 0x00, 0x00, 0xE5, 0x00, 0x00, 0x00, 0x3F, 0x10, 0x00, 0x00, 0xE6, 0x00, 0x00, 0x00
	.byte 0x40, 0x10, 0x00, 0x00, 0xE7, 0x00, 0x00, 0x00, 0x41, 0x10, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00
	.byte 0x42, 0x10, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x43, 0x10, 0x00, 0x00, 0xEA, 0x00, 0x00, 0x00
	.byte 0x44, 0x10, 0x00, 0x00, 0xEB, 0x00, 0x00, 0x00, 0x45, 0x10, 0x00, 0x00, 0xEC, 0x00, 0x00, 0x00
	.byte 0x46, 0x10, 0x00, 0x00, 0xED, 0x00, 0x00, 0x00, 0x47, 0x10, 0x00, 0x00, 0xEE, 0x00, 0x00, 0x00
	.byte 0x48, 0x10, 0x00, 0x00, 0xEF, 0x00, 0x00, 0x00, 0x49, 0x10, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00
	.byte 0x4A, 0x10, 0x00, 0x00, 0xF1, 0x00, 0x00, 0x00, 0x4B, 0x10, 0x00, 0x00, 0xF2, 0x00, 0x00, 0x00
	.byte 0x4C, 0x10, 0x00, 0x00, 0xF3, 0x00, 0x00, 0x00, 0x4D, 0x10, 0x00, 0x00, 0xF4, 0x00, 0x00, 0x00
	.byte 0x4E, 0x10, 0x00, 0x00, 0xF5, 0x00, 0x00, 0x00, 0x4F, 0x10, 0x00, 0x00, 0xF6, 0x00, 0x00, 0x00
	.byte 0x50, 0x10, 0x00, 0x00, 0xF7, 0x00, 0x00, 0x00, 0x51, 0x10, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00
	.byte 0x52, 0x10, 0x00, 0x00, 0xF9, 0x00, 0x00, 0x00, 0x53, 0x10, 0x00, 0x00, 0xFA, 0x00, 0x00, 0x00
	.byte 0x54, 0x10, 0x00, 0x00, 0xFB, 0x00, 0x00, 0x00, 0x55, 0x10, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00
	.byte 0x56, 0x10, 0x00, 0x00, 0xFD, 0x00, 0x00, 0x00, 0x57, 0x10, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00
	.byte 0x58, 0x10, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x59, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00
	.byte 0x5A, 0x10, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x5B, 0x10, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00
	.byte 0x5C, 0x10, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x5D, 0x10, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00
	.byte 0x5E, 0x10, 0x00, 0x00, 0x05, 0x01, 0x00, 0x00, 0x5F, 0x10, 0x00, 0x00, 0x06, 0x01, 0x00, 0x00
	.byte 0x60, 0x10, 0x00, 0x00, 0x07, 0x01, 0x00, 0x00, 0x61, 0x10, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00
	.byte 0x62, 0x10, 0x00, 0x00, 0x09, 0x01, 0x00, 0x00, 0x63, 0x10, 0x00, 0x00, 0x0A, 0x01, 0x00, 0x00
	.byte 0x64, 0x10, 0x00, 0x00, 0x0B, 0x01, 0x00, 0x00, 0x65, 0x10, 0x00, 0x00, 0x0C, 0x01, 0x00, 0x00
	.byte 0x66, 0x10, 0x00, 0x00, 0x0D, 0x01, 0x00, 0x00, 0x67, 0x10, 0x00, 0x00, 0x0E, 0x01, 0x00, 0x00
	.byte 0x68, 0x10, 0x00, 0x00, 0x0F, 0x01, 0x00, 0x00, 0x69, 0x10, 0x00, 0x00, 0x10, 0x01, 0x00, 0x00
	.byte 0x6A, 0x10, 0x00, 0x00, 0x11, 0x01, 0x00, 0x00, 0x6B, 0x10, 0x00, 0x00, 0x12, 0x01, 0x00, 0x00
	.byte 0x6C, 0x10, 0x00, 0x00, 0x13, 0x01, 0x00, 0x00, 0x6D, 0x10, 0x00, 0x00, 0x14, 0x01, 0x00, 0x00
	.byte 0x6E, 0x10, 0x00, 0x00, 0x15, 0x01, 0x00, 0x00, 0x6F, 0x10, 0x00, 0x00, 0x16, 0x01, 0x00, 0x00
	.byte 0x70, 0x10, 0x00, 0x00, 0x17, 0x01, 0x00, 0x00, 0x71, 0x10, 0x00, 0x00, 0x18, 0x01, 0x00, 0x00
	.byte 0x72, 0x10, 0x00, 0x00, 0x19, 0x01, 0x00, 0x00, 0x73, 0x10, 0x00, 0x00, 0x1A, 0x01, 0x00, 0x00
	.byte 0x74, 0x10, 0x00, 0x00, 0x1B, 0x01, 0x00, 0x00, 0x75, 0x10, 0x00, 0x00, 0x1C, 0x01, 0x00, 0x00
	.byte 0x76, 0x10, 0x00, 0x00, 0x1D, 0x01, 0x00, 0x00, 0x77, 0x10, 0x00, 0x00, 0x1E, 0x01, 0x00, 0x00
	.byte 0x78, 0x10, 0x00, 0x00, 0x1F, 0x01, 0x00, 0x00, 0x79, 0x10, 0x00, 0x00, 0x20, 0x01, 0x00, 0x00
	.byte 0x7A, 0x10, 0x00, 0x00, 0x21, 0x01, 0x00, 0x00, 0x7B, 0x10, 0x00, 0x00, 0x22, 0x01, 0x00, 0x00
	.byte 0x7C, 0x10, 0x00, 0x00, 0x23, 0x01, 0x00, 0x00, 0x7D, 0x10, 0x00, 0x00, 0x24, 0x01, 0x00, 0x00
	.byte 0x7E, 0x10, 0x00, 0x00, 0x25, 0x01, 0x00, 0x00, 0x7F, 0x10, 0x00, 0x00, 0x26, 0x01, 0x00, 0x00
	.byte 0x80, 0x10, 0x00, 0x00, 0x27, 0x01, 0x00, 0x00, 0x81, 0x10, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00
	.byte 0x82, 0x10, 0x00, 0x00, 0x29, 0x01, 0x00, 0x00, 0x83, 0x10, 0x00, 0x00, 0x2A, 0x01, 0x00, 0x00
	.byte 0x84, 0x10, 0x00, 0x00, 0x2B, 0x01, 0x00, 0x00, 0x85, 0x10, 0x00, 0x00, 0x2C, 0x01, 0x00, 0x00
	.byte 0x86, 0x10, 0x00, 0x00, 0x2D, 0x01, 0x00, 0x00, 0x87, 0x10, 0x00, 0x00, 0x2E, 0x01, 0x00, 0x00
	.byte 0x88, 0x10, 0x00, 0x00, 0x2F, 0x01, 0x00, 0x00, 0x89, 0x10, 0x00, 0x00, 0x30, 0x01, 0x00, 0x00
	.byte 0x8A, 0x10, 0x00, 0x00, 0x31, 0x01, 0x00, 0x00, 0x8B, 0x10, 0x00, 0x00, 0x32, 0x01, 0x00, 0x00
	.byte 0x8C, 0x10, 0x00, 0x00, 0x33, 0x01, 0x00, 0x00, 0x8D, 0x10, 0x00, 0x00, 0x34, 0x01, 0x00, 0x00
	.byte 0x8E, 0x10, 0x00, 0x00, 0x35, 0x01, 0x00, 0x00, 0x8F, 0x10, 0x00, 0x00, 0x36, 0x01, 0x00, 0x00
	.byte 0x90, 0x10, 0x00, 0x00, 0x37, 0x01, 0x00, 0x00, 0x91, 0x10, 0x00, 0x00, 0x38, 0x01, 0x00, 0x00
	.byte 0x92, 0x10, 0x00, 0x00, 0x39, 0x01, 0x00, 0x00, 0x93, 0x10, 0x00, 0x00, 0x3A, 0x01, 0x00, 0x00
	.byte 0x94, 0x10, 0x00, 0x00, 0x3B, 0x01, 0x00, 0x00, 0x95, 0x10, 0x00, 0x00, 0x3C, 0x01, 0x00, 0x00
	.byte 0x96, 0x10, 0x00, 0x00, 0x3D, 0x01, 0x00, 0x00, 0x97, 0x10, 0x00, 0x00, 0x3E, 0x01, 0x00, 0x00
	.byte 0x98, 0x10, 0x00, 0x00, 0x3F, 0x01, 0x00, 0x00, 0x99, 0x10, 0x00, 0x00, 0x40, 0x01, 0x00, 0x00
	.byte 0x9A, 0x10, 0x00, 0x00, 0x41, 0x01, 0x00, 0x00, 0x9B, 0x10, 0x00, 0x00, 0x42, 0x01, 0x00, 0x00
	.byte 0x9C, 0x10, 0x00, 0x00, 0x43, 0x01, 0x00, 0x00, 0x9D, 0x10, 0x00, 0x00, 0x44, 0x01, 0x00, 0x00
	.byte 0x9E, 0x10, 0x00, 0x00, 0x45, 0x01, 0x00, 0x00, 0x9F, 0x10, 0x00, 0x00, 0x46, 0x01, 0x00, 0x00
	.byte 0xA0, 0x10, 0x00, 0x00, 0x47, 0x01, 0x00, 0x00, 0xA1, 0x10, 0x00, 0x00, 0x48, 0x01, 0x00, 0x00
	.byte 0xA2, 0x10, 0x00, 0x00, 0x49, 0x01, 0x00, 0x00, 0xA3, 0x10, 0x00, 0x00, 0x4A, 0x01, 0x00, 0x00
	.byte 0xA4, 0x10, 0x00, 0x00, 0x4B, 0x01, 0x00, 0x00, 0xA5, 0x10, 0x00, 0x00, 0x4C, 0x01, 0x00, 0x00
	.byte 0xA6, 0x10, 0x00, 0x00, 0x4D, 0x01, 0x00, 0x00, 0xA7, 0x10, 0x00, 0x00, 0x4E, 0x01, 0x00, 0x00
	.byte 0xA8, 0x10, 0x00, 0x00, 0x4F, 0x01, 0x00, 0x00, 0xA9, 0x10, 0x00, 0x00, 0x50, 0x01, 0x00, 0x00
	.byte 0xAA, 0x10, 0x00, 0x00, 0x51, 0x01, 0x00, 0x00, 0xAB, 0x10, 0x00, 0x00, 0x52, 0x01, 0x00, 0x00
	.byte 0xAC, 0x10, 0x00, 0x00, 0x53, 0x01, 0x00, 0x00, 0xAD, 0x10, 0x00, 0x00, 0x54, 0x01, 0x00, 0x00
	.byte 0xAE, 0x10, 0x00, 0x00, 0x55, 0x01, 0x00, 0x00, 0xAF, 0x10, 0x00, 0x00, 0x56, 0x01, 0x00, 0x00
	.byte 0xB0, 0x10, 0x00, 0x00, 0x57, 0x01, 0x00, 0x00, 0xB1, 0x10, 0x00, 0x00, 0x58, 0x01, 0x00, 0x00
	.byte 0xB2, 0x10, 0x00, 0x00, 0x59, 0x01, 0x00, 0x00, 0xB3, 0x10, 0x00, 0x00, 0x5A, 0x01, 0x00, 0x00
	.byte 0xB4, 0x10, 0x00, 0x00, 0x5B, 0x01, 0x00, 0x00, 0xB5, 0x10, 0x00, 0x00, 0x5C, 0x01, 0x00, 0x00
	.byte 0xB6, 0x10, 0x00, 0x00, 0x5D, 0x01, 0x00, 0x00, 0xB7, 0x10, 0x00, 0x00, 0x5E, 0x01, 0x00, 0x00
	.byte 0xB8, 0x10, 0x00, 0x00, 0x5F, 0x01, 0x00, 0x00, 0xB9, 0x10, 0x00, 0x00, 0x60, 0x01, 0x00, 0x00
	.byte 0xBA, 0x10, 0x00, 0x00, 0x61, 0x01, 0x00, 0x00, 0xBB, 0x10, 0x00, 0x00, 0x62, 0x01, 0x00, 0x00
	.byte 0xBC, 0x10, 0x00, 0x00, 0x63, 0x01, 0x00, 0x00, 0xBD, 0x10, 0x00, 0x00, 0x64, 0x01, 0x00, 0x00
	.byte 0xBE, 0x10, 0x00, 0x00, 0x65, 0x01, 0x00, 0x00, 0xBF, 0x10, 0x00, 0x00, 0x66, 0x01, 0x00, 0x00
	.byte 0xC0, 0x10, 0x00, 0x00, 0x67, 0x01, 0x00, 0x00, 0xC1, 0x00, 0x00, 0x00, 0x69, 0x01, 0x00, 0x00
	.byte 0xC2, 0x00, 0x00, 0x00, 0x68, 0x01, 0x00, 0x00, 0xC3, 0x00, 0x00, 0x00, 0x6A, 0x01, 0x00, 0x00
	.byte 0xC4, 0x00, 0x00, 0x00, 0x6B, 0x01, 0x00, 0x00, 0xC5, 0x00, 0x00, 0x00, 0x6C, 0x01, 0x00, 0x00
	.byte 0xC6, 0x00, 0x00, 0x00, 0x6D, 0x01, 0x00, 0x00, 0xC7, 0x00, 0x00, 0x00, 0x6E, 0x01, 0x00, 0x00
	.byte 0xC8, 0x00, 0x00, 0x00, 0x6F, 0x01, 0x00, 0x00, 0xC9, 0x00, 0x00, 0x00, 0x70, 0x01, 0x00, 0x00
	.byte 0xCA, 0x00, 0x00, 0x00, 0x71, 0x01, 0x00, 0x00, 0xCB, 0x00, 0x00, 0x00, 0x72, 0x01, 0x00, 0x00
	.byte 0xCC, 0x00, 0x00, 0x00, 0x73, 0x01, 0x00, 0x00, 0xCD, 0x00, 0x00, 0x00, 0x74, 0x01, 0x00, 0x00
	.byte 0xCE, 0x00, 0x00, 0x00, 0x75, 0x01, 0x00, 0x00, 0xCF, 0x00, 0x00, 0x00, 0x76, 0x01, 0x00, 0x00
	.byte 0xD0, 0x00, 0x00, 0x00, 0x77, 0x01, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021FAC6C
UNK05_021FAC6C: ; 0x021FAC6C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.word UNK05_021F8F90
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.word UNK05_021F8FFC
	.byte 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00
	.word UNK05_021F8F48
	.byte 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x2B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x2D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x4B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x4D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x4E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x4F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x54, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x55, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x57, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x59, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x5A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.word UNK05_021F8F90
	.byte 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.word UNK05_021F8FFC
	.byte 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x00, 0x10, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x01, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x02, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x03, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x7A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x7B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x7D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x89, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x8C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x8D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x91, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x93, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x95, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x96, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x97, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.word UNK05_021F8D74
	.byte 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.word UNK05_021F8D74
	.byte 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.word UNK05_021F8D74
	.byte 0x9A, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.word UNK05_021F8D44
	.byte 0x9B, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.word UNK05_021F8D44
	.byte 0x9C, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.word UNK05_021F8D5C
	.byte 0x9D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00
	.word UNK05_021F8D5C
	.byte 0x9E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x9F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00
	.word UNK05_021F8D5C
	.byte 0xA0, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00
	.word UNK05_021F8D5C
	.byte 0xA1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.word UNK05_021F8D5C
	.byte 0xA2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xA3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xA4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xA5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xA6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xA7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xA9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xAB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xAC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xAD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00
	.word UNK05_021F8DEC
	.byte 0xAE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xAF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.word UNK05_021F8DA4
	.byte 0xB1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.word UNK05_021F8DA4
	.byte 0xB2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.word UNK05_021F8E94
	.byte 0xB3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.word UNK05_021F8E94
	.byte 0xB4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.word UNK05_021F8E10
	.byte 0xB5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.word UNK05_021F8E10
	.byte 0xB6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xB8, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00
	.word UNK05_021F8F90
	.byte 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00
	.word UNK05_021F8F90
	.byte 0xBC, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.word UNK05_021F8E58
	.byte 0xBD, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.word UNK05_021F8E58
	.byte 0xBE, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xBF, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0x04, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x05, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x06, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x07, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x08, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x09, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x0A, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x0B, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x0C, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x0D, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x0E, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x0F, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x10, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x11, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x12, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x13, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x14, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x15, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x16, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x17, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x18, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x19, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x1A, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x1B, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x1C, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x1D, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x1E, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x1F, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x20, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x21, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x22, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x23, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x24, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x25, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x26, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x27, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x28, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x29, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x2A, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x2B, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x2C, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x2D, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x2E, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x2F, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x30, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x31, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x32, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x33, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x34, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x35, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x36, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x37, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x38, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x39, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x3A, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x3B, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x3C, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x3D, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x3E, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x3F, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x40, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x41, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x42, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x43, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x44, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x45, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x46, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x47, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x48, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x49, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x4A, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x4B, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x4C, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x4D, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x4E, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x4F, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x50, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x51, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x52, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x53, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x54, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x55, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x56, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x57, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x58, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x59, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x5A, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x5B, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x5C, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x5D, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x5E, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x5F, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x60, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x61, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x62, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x63, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x64, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x65, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x66, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x67, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x68, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x69, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x6A, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x6B, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x6C, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x6D, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x6E, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x6F, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x70, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x71, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x72, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x73, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x74, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x75, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x76, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x77, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x78, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x79, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x7A, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x7B, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x7C, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x7D, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x7E, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x7F, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x80, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x81, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x82, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x83, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x84, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x85, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x86, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x87, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x88, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x89, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x8A, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x8B, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x8C, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x8D, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x8E, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x8F, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x90, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x91, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x92, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x93, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x94, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x95, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x96, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x97, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x98, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x99, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x9A, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x9B, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x9C, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x9D, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x9E, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0x9F, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xA0, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xA1, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xA2, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xA3, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xA4, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xA5, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xA6, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xA7, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xA8, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xA9, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xAA, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xAB, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xAC, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xAD, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xAE, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xAF, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xB0, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xB1, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xB2, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xB3, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xB4, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xB5, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xB6, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xB7, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xB8, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xB9, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xBA, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xBB, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xBC, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xBD, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xBE, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xBF, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xC0, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.word UNK05_021F8DD4
	.byte 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xC2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.word UNK05_021F8D8C
	.byte 0xC4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00
	.word UNK05_021F8ED0
	.byte 0xC5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00
	.word UNK05_021F8ED0
	.byte 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00
	.word UNK05_021F8DBC
	.byte 0xC7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00
	.word UNK05_021F8DBC
	.byte 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
	.word UNK05_021F8E34
	.byte 0xC9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
	.word UNK05_021F8E34
	.byte 0xCA, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xCB, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xCD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xCE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xCF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xD0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word UNK05_021F8F0C
	.byte 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021FC3EC
UNK05_021FC3EC: ; 0x021FC3EC
	.byte 0x00, 0x30, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021FC3FC
UNK05_021FC3FC: ; 0x021FC3FC
	.byte 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00

	.global UNK05_021FC40C
UNK05_021FC40C: ; 0x021FC40C
	.word MOD05_021F14BC, MOD05_021F150C, MOD05_021F1544, MOD05_021F1608

	.global UNK05_021FC41C
UNK05_021FC41C: ; 0x021FC41C
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00

	.global UNK05_021FC42C
UNK05_021FC42C: ; 0x021FC42C
	.byte 0x00, 0x30, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021FC43C
UNK05_021FC43C: ; 0x021FC43C
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021FC458
UNK05_021FC458: ; 0x021FC458
	.byte 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021FC474
UNK05_021FC474: ; 0x021FC474
	.byte 0x00, 0x20, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021FC494
UNK05_021FC494: ; 0x021FC494
	.byte 0x00, 0x20, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021FC4B4
UNK05_021FC4B4: ; 0x021FC4B4
	.word MOD05_021F075C, MOD05_021F0790, MOD05_021F0790, MOD05_021F07CC
	.word MOD05_021F0808, MOD05_021F0844, MOD05_021F0880, MOD05_021F0904
	.word MOD05_021F0980

	.global UNK05_021FC4D8
UNK05_021FC4D8: ; 0x021FC4D8
	.word MOD05_021F12C0, MOD05_021F0E98, MOD05_021F0E98, MOD05_021F0F0C
	.word MOD05_021F0F60, MOD05_021F1008, MOD05_021F1008, MOD05_021F1008
	.word MOD05_021F134C, MOD05_021F13C8

	.global UNK05_021FC500
UNK05_021FC500: ; 0x021FC500
	.word MOD05_021F0E28, MOD05_021F0E98, MOD05_021F0E98, MOD05_021F0F0C
	.word MOD05_021F0F60, MOD05_021F0FB4, MOD05_021F1008, MOD05_021F10A8
	.word MOD05_021F1140, MOD05_021F11E0

	.global UNK05_021FC528
UNK05_021FC528: ; 0x021FC528
	.word MOD05_021F0A78, MOD05_021F0790, MOD05_021F0790, MOD05_021F07CC
	.word MOD05_021F0808, MOD05_021F0844, MOD05_021F0880, MOD05_021F0904
	.word MOD05_021F0980, MOD05_021F0AB4

	.global UNK05_021FC550
UNK05_021FC550: ; 0x021FC550
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global UNK05_021FC55C
UNK05_021FC55C: ; 0x021FC55C
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00

	.global UNK05_021FC56C
UNK05_021FC56C: ; 0x021FC56C
	.byte 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00

	.global UNK05_021FC57C
UNK05_021FC57C: ; 0x021FC57C
	.byte 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00

	.global UNK05_021FC58C
UNK05_021FC58C: ; 0x021FC58C
	.word 0x00000002, 0x00000008, MOD05_021F3854, MOD05_021F385C
	.word MOD05_021F3860, 0x00000000

	.global UNK05_021FC5A4
UNK05_021FC5A4: ; 0x021FC5A4
	.byte 0x22, 0x01

	.global UNK05_021FC5A6
UNK05_021FC5A6: ; 0x021FC5A6
	.byte 0x01, 0x00

	.global UNK05_021FC5A8
UNK05_021FC5A8: ; 0x021FC5A8
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x2C, 0x01, 0x01, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x90, 0x01, 0x02, 0x00, 0x6E, 0x00, 0x00, 0x00
	.byte 0xF4, 0x01, 0x04, 0x00, 0x36, 0x01, 0x00, 0x00, 0x58, 0x02, 0x14, 0x00, 0xC6, 0x02, 0x00, 0x00
	.byte 0xBC, 0x02, 0x32, 0x00, 0x96, 0x0A, 0x00, 0x00, 0x20, 0x03, 0x64, 0x00, 0x1E, 0x1E, 0x00, 0x00
	.byte 0x84, 0x03, 0x96, 0x00, 0x2E, 0x45, 0x00, 0x00, 0xE8, 0x03, 0x96, 0x00, 0xC6, 0x7F, 0x00, 0x00
	.byte 0x4C, 0x04, 0x64, 0x00, 0x5E, 0xBA, 0x00, 0x00, 0xB0, 0x04, 0x32, 0x00, 0x6E, 0xE1, 0x00, 0x00
	.byte 0x14, 0x05, 0x14, 0x00, 0xF6, 0xF4, 0x00, 0x00, 0x78, 0x05, 0x05, 0x00, 0xC6, 0xFC, 0x00, 0x00
	.byte 0xDC, 0x05, 0x02, 0x00, 0xBA, 0xFE, 0x00, 0x00, 0x40, 0x06, 0x01, 0x00, 0x82, 0xFF, 0x00, 0x00
	.byte 0xA4, 0x06, 0x01, 0x00, 0xE6, 0xFF, 0x00, 0x00

	.global UNK05_021FC624
UNK05_021FC624: ; 0x021FC624
	.byte 0x00, 0x00, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10
	.byte 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10

	.global UNK05_021FC634
UNK05_021FC634: ; 0x021FC634
	.byte 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10
	.byte 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10

	.global UNK05_021FC644
UNK05_021FC644: ; 0x021FC644
.ifdef DIAMOND
	.word 2, 3, 4
.else
	.word 5, 6, 7
.endif

	.global UNK05_021FC650
UNK05_021FC650: ; 0x021FC650
	.byte 0x5B, 0x01, 0x00, 0x00, 0x5D, 0x01, 0x00, 0x00, 0x5E, 0x01, 0x00, 0x00
	.byte 0x61, 0x01, 0x00, 0x00, 0x62, 0x01, 0x00, 0x00, 0x64, 0x01, 0x00, 0x00, 0x6A, 0x01, 0x00, 0x00
	.byte 0x6B, 0x01, 0x00, 0x00, 0x6E, 0x01, 0x00, 0x00, 0x6F, 0x01, 0x00, 0x00, 0x73, 0x01, 0x00, 0x00
	.byte 0x75, 0x01, 0x00, 0x00, 0x7C, 0x01, 0x00, 0x00, 0x7E, 0x01, 0x00, 0x00, 0x84, 0x01, 0x00, 0x00
	.byte 0x88, 0x01, 0x00, 0x00, 0x8B, 0x01, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 0xCA, 0x00, 0x00, 0x00
	.byte 0xCC, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00

	.global UNK05_021FC6A4
UNK05_021FC6A4: ; 0x021FC6A4
	.byte 0x08, 0x00, 0x00, 0x00

	.global UNK05_021FC6A8
UNK05_021FC6A8: ; 0x021FC6A8
	.word 0x00000400, 0x00000018, MOD05_021F5564, MOD05_021F5598
	.word MOD05_021F559C, MOD05_021F55C8

	.global UNK05_021FC6C0
UNK05_021FC6C0: ; 0x021FC6C0
	.word 0x00000400, 0x00000018, MOD05_021F5518, MOD05_021F5598
	.word MOD05_021F559C, MOD05_021F55C8

	.global UNK05_021FC6D8
UNK05_021FC6D8: ; 0x021FC6D8
	.byte 0x02, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x07, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00
	.byte 0x0E, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x09, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00

	.global UNK05_021FC718
UNK05_021FC718: ; 0x021FC718
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00
	.byte 0x1F, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x15, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00
	.byte 0x19, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK05_021FC79C
UNK05_021FC79C: ; 0x021FC79C
	.byte 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.byte 0x09, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK05_021FC820
UNK05_021FC820: ; 0x021FC820
	.word 0x00, MOD06_022492B0, MOD06_022492D4
	.word 0x01, MOD06_022497A0, MOD06_022497BC
	.word 0x02, MOD05_021E52A8, MOD05_021E52C4
	.word 0x03, MOD05_021E5300, MOD05_021E531C
	.word 0x04, MOD05_021E5564, MOD05_021E5580
	.word 0x05, MOD05_021E55BC, MOD05_021E55D8
	.word 0x06, MOD05_021E577C, MOD05_021E5798
	.word 0x07, MOD05_021E5918, MOD05_021E5934
	.word 0x08, MOD05_021E5AB4, MOD05_021E5AD0
	.word 0x09, MOD05_021E5C8C, MOD05_021E5CA8
	.word 0x0A, MOD05_021E5E10, MOD05_021E5E2C
	.word 0x0B, MOD06_02249C98, MOD06_02249CB8
	.word 0x0C, MOD06_0224A040, MOD06_0224A05C
	.word 0x0D, MOD06_0224A280, MOD06_0224A29C
	.word 0x0E, MOD06_0224A63C, MOD06_0224A658
	.word 0x0F, MOD06_0224A87C, MOD06_0224A898
	.word 0x10, MOD05_021EDB70, MOD05_021EDB8C
	.word 0x11, MOD06_0224AB54, MOD06_0224AB70
	.word 0x12, MOD06_0224AE10, MOD06_0224AE24
	.word 0x13, MOD06_0224B0A8, MOD06_0224B0C4
	.word 0x14, MOD06_0224B248, MOD06_0224B264
	.word 0x15, MOD06_0224B3E4, MOD06_0224B400
	.word 0x16, MOD05_021E779C, MOD05_021E77B0
	.word 0x17, MOD06_0224B948, MOD06_0224B964
	.word 0x18, MOD05_021ED9C0, MOD05_021ED9DC
	.word 0x19, MOD06_0224BB50, MOD06_0224BB6C
	.word 0x1A, MOD06_0224BCF4, MOD06_0224BD10
	.word 0x1B, MOD06_0224BF9C, MOD06_0224BFB8
	.word 0x1C, MOD06_0224CE30, MOD06_0224CE4C
	.word 0x1D, MOD06_0224D244, MOD06_0224D260
	.word 0x1E, MOD06_0224A44C, MOD06_0224A460
	.word 0x1F, MOD06_0224A9E8, MOD06_0224AA04
	.word 0x20, 0x00000000, 0x00000000

	.global UNK05_021FC9AC
UNK05_021FC9AC: ; 0x021FC9AC
	.word 45, 30, 15

	.global UNK05_021FC9B8
UNK05_021FC9B8: ; 0x021FC9B8
	.word MOD05_021F5DA8, MOD05_021F5DC0, MOD05_021F5DF8, MOD05_021F5E30
	.word MOD05_021F5E64, MOD05_021F5EA8, MOD05_021F5ED4, MOD05_021F5EF8
	.word MOD05_021F5F18, MOD05_021F5F30, MOD05_021F5F3C, MOD05_021F5F5C
	.word MOD05_021F5F9C, MOD05_021F5FA8, MOD05_021F5FEC, MOD05_021F6018
	.word MOD05_021F6058, MOD05_021F606C

	.global UNK05_021FCA00
UNK05_021FCA00: ; 0x021FCA00
	.short 0x0000, 0x0000 ; SPECIES_NONE
	.short 0x0001, 0x0001 ; SPECIES_BULBASAUR
	.short 0x0001, 0x0001 ; SPECIES_IVYSAUR
	.short 0x0002, 0x0001 ; SPECIES_VENUSAUR
	.short 0x0001, 0x0001 ; SPECIES_CHARMANDER
	.short 0x0002, 0x0001 ; SPECIES_CHARMELEON
	.short 0x0002, 0x0001 ; SPECIES_CHARIZARD
	.short 0x0001, 0x0001 ; SPECIES_SQUIRTLE
	.short 0x0001, 0x0001 ; SPECIES_WARTORTLE
	.short 0x0002, 0x0001 ; SPECIES_BLASTOISE
	.short 0x0001, 0x0001 ; SPECIES_CATERPIE
	.short 0x0005, 0x0000 ; SPECIES_METAPOD
	.short 0x0001, 0x0001 ; SPECIES_BUTTERFREE
	.short 0x0001, 0x0001 ; SPECIES_WEEDLE
	.short 0x0005, 0x0000 ; SPECIES_KAKUNA
	.short 0x0002, 0x0001 ; SPECIES_BEEDRILL
	.short 0x0001, 0x0001 ; SPECIES_PIDGEY
	.short 0x0001, 0x0001 ; SPECIES_PIDGEOTTO
	.short 0x0002, 0x0001 ; SPECIES_PIDGEOT
	.short 0x0001, 0x0001 ; SPECIES_RATTATA
	.short 0x0002, 0x0001 ; SPECIES_RATICATE
	.short 0x0002, 0x0001 ; SPECIES_SPEAROW
	.short 0x0002, 0x0001 ; SPECIES_FEAROW
	.short 0x0003, 0x0000 ; SPECIES_EKANS
	.short 0x0003, 0x0000 ; SPECIES_ARBOK
	.short 0x0001, 0x0001 ; SPECIES_PIKACHU
	.short 0x0001, 0x0001 ; SPECIES_RAICHU
	.short 0x0001, 0x0001 ; SPECIES_SANDSHREW
	.short 0x0001, 0x0001 ; SPECIES_SANDSLASH
	.short 0x0001, 0x0001 ; SPECIES_NIDORAN_F
	.short 0x0001, 0x0001 ; SPECIES_NIDORINA
	.short 0x0002, 0x0001 ; SPECIES_NIDOQUEEN
	.short 0x0001, 0x0001 ; SPECIES_NIDORAN_M
	.short 0x0002, 0x0001 ; SPECIES_NIDORINO
	.short 0x0002, 0x0001 ; SPECIES_NIDOKING
	.short 0x0001, 0x0001 ; SPECIES_CLEFAIRY
	.short 0x0001, 0x0001 ; SPECIES_CLEFABLE
	.short 0x0001, 0x0001 ; SPECIES_VULPIX
	.short 0x0002, 0x0001 ; SPECIES_NINETALES
	.short 0x0001, 0x0001 ; SPECIES_JIGGLYPUFF
	.short 0x0001, 0x0001 ; SPECIES_WIGGLYTUFF
	.short 0x0003, 0x0000 ; SPECIES_ZUBAT
	.short 0x0003, 0x0001 ; SPECIES_GOLBAT
	.short 0x0001, 0x0001 ; SPECIES_ODDISH
	.short 0x0001, 0x0001 ; SPECIES_GLOOM
	.short 0x0001, 0x0001 ; SPECIES_VILEPLUME
	.short 0x0005, 0x0001 ; SPECIES_PARAS
	.short 0x0005, 0x0001 ; SPECIES_PARASECT
	.short 0x0001, 0x0001 ; SPECIES_VENONAT
	.short 0x0005, 0x0001 ; SPECIES_VENOMOTH
	.short 0x0001, 0x0000 ; SPECIES_DIGLETT
	.short 0x0001, 0x0000 ; SPECIES_DUGTRIO
	.short 0x0001, 0x0001 ; SPECIES_MEOWTH
	.short 0x0002, 0x0001 ; SPECIES_PERSIAN
	.short 0x0004, 0x0001 ; SPECIES_PSYDUCK
	.short 0x0002, 0x0001 ; SPECIES_GOLDUCK
	.short 0x0002, 0x0001 ; SPECIES_MANKEY
	.short 0x0002, 0x0001 ; SPECIES_PRIMEAPE
	.short 0x0001, 0x0001 ; SPECIES_GROWLITHE
	.short 0x0002, 0x0001 ; SPECIES_ARCANINE
	.short 0x0001, 0x0001 ; SPECIES_POLIWAG
	.short 0x0001, 0x0001 ; SPECIES_POLIWHIRL
	.short 0x0002, 0x0001 ; SPECIES_POLIWRATH
	.short 0x0001, 0x0001 ; SPECIES_ABRA
	.short 0x0002, 0x0001 ; SPECIES_KADABRA
	.short 0x0002, 0x0001 ; SPECIES_ALAKAZAM
	.short 0x0001, 0x0001 ; SPECIES_MACHOP
	.short 0x0002, 0x0001 ; SPECIES_MACHOKE
	.short 0x0002, 0x0001 ; SPECIES_MACHAMP
	.short 0x0001, 0x0001 ; SPECIES_BELLSPROUT
	.short 0x0004, 0x0000 ; SPECIES_WEEPINBELL
	.short 0x0004, 0x0000 ; SPECIES_VICTREEBEL
	.short 0x0002, 0x0000 ; SPECIES_TENTACOOL
	.short 0x0002, 0x0000 ; SPECIES_TENTACRUEL
	.short 0x0001, 0x0000 ; SPECIES_GEODUDE
	.short 0x0002, 0x0001 ; SPECIES_GRAVELER
	.short 0x0002, 0x0001 ; SPECIES_GOLEM
	.short 0x0001, 0x0001 ; SPECIES_PONYTA
	.short 0x0002, 0x0001 ; SPECIES_RAPIDASH
	.short 0x0004, 0x0001 ; SPECIES_SLOWPOKE
	.short 0x0004, 0x0001 ; SPECIES_SLOWBRO
	.short 0x0005, 0x0001 ; SPECIES_MAGNEMITE
	.short 0x0005, 0x0001 ; SPECIES_MAGNETON
	.short 0x0002, 0x0001 ; SPECIES_FARFETCHD
	.short 0x0001, 0x0001 ; SPECIES_DODUO
	.short 0x0002, 0x0001 ; SPECIES_DODRIO
	.short 0x0004, 0x0000 ; SPECIES_SEEL
	.short 0x0004, 0x0000 ; SPECIES_DEWGONG
	.short 0x0003, 0x0000 ; SPECIES_GRIMER
	.short 0x0003, 0x0000 ; SPECIES_MUK
	.short 0x0004, 0x0000 ; SPECIES_SHELLDER
	.short 0x0002, 0x0000 ; SPECIES_CLOYSTER
	.short 0x0003, 0x0000 ; SPECIES_GASTLY
	.short 0x0003, 0x0000 ; SPECIES_HAUNTER
	.short 0x0003, 0x0001 ; SPECIES_GENGAR
	.short 0x0002, 0x0000 ; SPECIES_ONIX
	.short 0x0003, 0x0001 ; SPECIES_DROWZEE
	.short 0x0003, 0x0001 ; SPECIES_HYPNO
	.short 0x0001, 0x0001 ; SPECIES_KRABBY
	.short 0x0002, 0x0001 ; SPECIES_KINGLER
	.short 0x0002, 0x0000 ; SPECIES_VOLTORB
	.short 0x0002, 0x0000 ; SPECIES_ELECTRODE
	.short 0x0001, 0x0000 ; SPECIES_EXEGGCUTE
	.short 0x0004, 0x0001 ; SPECIES_EXEGGUTOR
	.short 0x0001, 0x0001 ; SPECIES_CUBONE
	.short 0x0002, 0x0001 ; SPECIES_MAROWAK
	.short 0x0002, 0x0001 ; SPECIES_HITMONLEE
	.short 0x0002, 0x0001 ; SPECIES_HITMONCHAN
	.short 0x0004, 0x0001 ; SPECIES_LICKITUNG
	.short 0x0003, 0x0000 ; SPECIES_KOFFING
	.short 0x0003, 0x0000 ; SPECIES_WEEZING
	.short 0x0002, 0x0001 ; SPECIES_RHYHORN
	.short 0x0002, 0x0001 ; SPECIES_RHYDON
	.short 0x0001, 0x0001 ; SPECIES_CHANSEY
	.short 0x0001, 0x0001 ; SPECIES_TANGELA
	.short 0x0002, 0x0001 ; SPECIES_KANGASKHAN
	.short 0x0001, 0x0000 ; SPECIES_HORSEA
	.short 0x0002, 0x0000 ; SPECIES_SEADRA
	.short 0x0001, 0x0000 ; SPECIES_GOLDEEN
	.short 0x0002, 0x0000 ; SPECIES_SEAKING
	.short 0x0005, 0x0001 ; SPECIES_STARYU
	.short 0x0005, 0x0001 ; SPECIES_STARMIE
	.short 0x0001, 0x0001 ; SPECIES_MR_MIME
	.short 0x0002, 0x0001 ; SPECIES_SCYTHER
	.short 0x0001, 0x0000 ; SPECIES_JYNX
	.short 0x0002, 0x0001 ; SPECIES_ELECTABUZZ
	.short 0x0002, 0x0001 ; SPECIES_MAGMAR
	.short 0x0002, 0x0001 ; SPECIES_PINSIR
	.short 0x0002, 0x0001 ; SPECIES_TAUROS
	.short 0x0004, 0x0000 ; SPECIES_MAGIKARP
	.short 0x0003, 0x0000 ; SPECIES_GYARADOS
	.short 0x0001, 0x0000 ; SPECIES_LAPRAS
	.short 0x0004, 0x0000 ; SPECIES_DITTO
	.short 0x0001, 0x0001 ; SPECIES_EEVEE
	.short 0x0002, 0x0001 ; SPECIES_VAPOREON
	.short 0x0002, 0x0001 ; SPECIES_JOLTEON
	.short 0x0002, 0x0001 ; SPECIES_FLAREON
	.short 0x0005, 0x0001 ; SPECIES_PORYGON
	.short 0x0001, 0x0001 ; SPECIES_OMANYTE
	.short 0x0002, 0x0001 ; SPECIES_OMASTAR
	.short 0x0005, 0x0001 ; SPECIES_KABUTO
	.short 0x0002, 0x0001 ; SPECIES_KABUTOPS
	.short 0x0002, 0x0001 ; SPECIES_AERODACTYL
	.short 0x0004, 0x0001 ; SPECIES_SNORLAX
	.short 0x0002, 0x0001 ; SPECIES_ARTICUNO
	.short 0x0002, 0x0001 ; SPECIES_ZAPDOS
	.short 0x0002, 0x0001 ; SPECIES_MOLTRES
	.short 0x0001, 0x0000 ; SPECIES_DRATINI
	.short 0x0002, 0x0000 ; SPECIES_DRAGONAIR
	.short 0x0002, 0x0001 ; SPECIES_DRAGONITE
	.short 0x0002, 0x0001 ; SPECIES_MEWTWO
	.short 0x0001, 0x0001 ; SPECIES_MEW
	.short 0x0001, 0x0001 ; SPECIES_CHIKORITA
	.short 0x0001, 0x0001 ; SPECIES_BAYLEEF
	.short 0x0002, 0x0001 ; SPECIES_MEGANIUM
	.short 0x0001, 0x0001 ; SPECIES_CYNDAQUIL
	.short 0x0002, 0x0001 ; SPECIES_QUILAVA
	.short 0x0002, 0x0001 ; SPECIES_TYPHLOSION
	.short 0x0001, 0x0001 ; SPECIES_TOTODILE
	.short 0x0002, 0x0001 ; SPECIES_CROCONAW
	.short 0x0002, 0x0001 ; SPECIES_FERALIGATR
	.short 0x0001, 0x0001 ; SPECIES_SENTRET
	.short 0x0001, 0x0001 ; SPECIES_FURRET
	.short 0x0001, 0x0001 ; SPECIES_HOOTHOOT
	.short 0x0002, 0x0001 ; SPECIES_NOCTOWL
	.short 0x0001, 0x0001 ; SPECIES_LEDYBA
	.short 0x0002, 0x0001 ; SPECIES_LEDIAN
	.short 0x0003, 0x0001 ; SPECIES_SPINARAK
	.short 0x0003, 0x0001 ; SPECIES_ARIADOS
	.short 0x0003, 0x0000 ; SPECIES_CROBAT
	.short 0x0004, 0x0000 ; SPECIES_CHINCHOU
	.short 0x0002, 0x0000 ; SPECIES_LANTURN
	.short 0x0001, 0x0001 ; SPECIES_PICHU
	.short 0x0001, 0x0001 ; SPECIES_CLEFFA
	.short 0x0001, 0x0001 ; SPECIES_IGGLYBUFF
	.short 0x0001, 0x0001 ; SPECIES_TOGEPI
	.short 0x0001, 0x0001 ; SPECIES_TOGETIC
	.short 0x0001, 0x0001 ; SPECIES_NATU
	.short 0x0005, 0x0001 ; SPECIES_XATU
	.short 0x0001, 0x0001 ; SPECIES_MAREEP
	.short 0x0001, 0x0001 ; SPECIES_FLAAFFY
	.short 0x0001, 0x0001 ; SPECIES_AMPHAROS
	.short 0x0001, 0x0000 ; SPECIES_BELLOSSOM
	.short 0x0001, 0x0001 ; SPECIES_MARILL
	.short 0x0001, 0x0001 ; SPECIES_AZUMARILL
	.short 0x0004, 0x0001 ; SPECIES_SUDOWOODO
	.short 0x0001, 0x0001 ; SPECIES_POLITOED
	.short 0x0001, 0x0001 ; SPECIES_HOPPIP
	.short 0x0001, 0x0001 ; SPECIES_SKIPLOOM
	.short 0x0001, 0x0001 ; SPECIES_JUMPLUFF
	.short 0x0001, 0x0001 ; SPECIES_AIPOM
	.short 0x0001, 0x0000 ; SPECIES_SUNKERN
	.short 0x0001, 0x0001 ; SPECIES_SUNFLORA
	.short 0x0001, 0x0001 ; SPECIES_YANMA
	.short 0x0001, 0x0001 ; SPECIES_WOOPER
	.short 0x0004, 0x0001 ; SPECIES_QUAGSIRE
	.short 0x0002, 0x0001 ; SPECIES_ESPEON
	.short 0x0002, 0x0001 ; SPECIES_UMBREON
	.short 0x0003, 0x0001 ; SPECIES_MURKROW
	.short 0x0004, 0x0001 ; SPECIES_SLOWKING
	.short 0x0003, 0x0000 ; SPECIES_MISDREAVUS
	.short 0x0005, 0x0000 ; SPECIES_UNOWN
	.short 0x0004, 0x0001 ; SPECIES_WOBBUFFET
	.short 0x0001, 0x0001 ; SPECIES_GIRAFARIG
	.short 0x0005, 0x0000 ; SPECIES_PINECO
	.short 0x0005, 0x0000 ; SPECIES_FORRETRESS
	.short 0x0004, 0x0000 ; SPECIES_DUNSPARCE
	.short 0x0004, 0x0001 ; SPECIES_GLIGAR
	.short 0x0002, 0x0000 ; SPECIES_STEELIX
	.short 0x0001, 0x0001 ; SPECIES_SNUBBULL
	.short 0x0001, 0x0001 ; SPECIES_GRANBULL
	.short 0x0002, 0x0000 ; SPECIES_QWILFISH
	.short 0x0002, 0x0001 ; SPECIES_SCIZOR
	.short 0x0001, 0x0001 ; SPECIES_SHUCKLE
	.short 0x0002, 0x0001 ; SPECIES_HERACROSS
	.short 0x0002, 0x0001 ; SPECIES_SNEASEL
	.short 0x0001, 0x0001 ; SPECIES_TEDDIURSA
	.short 0x0002, 0x0001 ; SPECIES_URSARING
	.short 0x0004, 0x0000 ; SPECIES_SLUGMA
	.short 0x0004, 0x0000 ; SPECIES_MAGCARGO
	.short 0x0001, 0x0001 ; SPECIES_SWINUB
	.short 0x0004, 0x0001 ; SPECIES_PILOSWINE
	.short 0x0001, 0x0001 ; SPECIES_CORSOLA
	.short 0x0005, 0x0000 ; SPECIES_REMORAID
	.short 0x0004, 0x0001 ; SPECIES_OCTILLERY
	.short 0x0001, 0x0001 ; SPECIES_DELIBIRD
	.short 0x0002, 0x0000 ; SPECIES_MANTINE
	.short 0x0002, 0x0001 ; SPECIES_SKARMORY
	.short 0x0003, 0x0001 ; SPECIES_HOUNDOUR
	.short 0x0003, 0x0001 ; SPECIES_HOUNDOOM
	.short 0x0002, 0x0000 ; SPECIES_KINGDRA
	.short 0x0001, 0x0001 ; SPECIES_PHANPY
	.short 0x0002, 0x0001 ; SPECIES_DONPHAN
	.short 0x0005, 0x0001 ; SPECIES_PORYGON2
	.short 0x0002, 0x0001 ; SPECIES_STANTLER
	.short 0x0004, 0x0001 ; SPECIES_SMEARGLE
	.short 0x0001, 0x0001 ; SPECIES_TYROGUE
	.short 0x0002, 0x0001 ; SPECIES_HITMONTOP
	.short 0x0001, 0x0001 ; SPECIES_SMOOCHUM
	.short 0x0001, 0x0001 ; SPECIES_ELEKID
	.short 0x0001, 0x0001 ; SPECIES_MAGBY
	.short 0x0001, 0x0001 ; SPECIES_MILTANK
	.short 0x0001, 0x0001 ; SPECIES_BLISSEY
	.short 0x0002, 0x0001 ; SPECIES_RAIKOU
	.short 0x0002, 0x0001 ; SPECIES_ENTEI
	.short 0x0002, 0x0001 ; SPECIES_SUICUNE
	.short 0x0001, 0x0001 ; SPECIES_LARVITAR
	.short 0x0005, 0x0000 ; SPECIES_PUPITAR
	.short 0x0003, 0x0001 ; SPECIES_TYRANITAR
	.short 0x0002, 0x0001 ; SPECIES_LUGIA
	.short 0x0002, 0x0001 ; SPECIES_HO_OH
	.short 0x0001, 0x0001 ; SPECIES_CELEBI
	.short 0x0001, 0x0001 ; SPECIES_TREECKO
	.short 0x0002, 0x0001 ; SPECIES_GROVYLE
	.short 0x0002, 0x0001 ; SPECIES_SCEPTILE
	.short 0x0001, 0x0001 ; SPECIES_TORCHIC
	.short 0x0002, 0x0001 ; SPECIES_COMBUSKEN
	.short 0x0002, 0x0001 ; SPECIES_BLAZIKEN
	.short 0x0001, 0x0001 ; SPECIES_MUDKIP
	.short 0x0001, 0x0001 ; SPECIES_MARSHTOMP
	.short 0x0002, 0x0001 ; SPECIES_SWAMPERT
	.short 0x0001, 0x0001 ; SPECIES_POOCHYENA
	.short 0x0002, 0x0001 ; SPECIES_MIGHTYENA
	.short 0x0004, 0x0001 ; SPECIES_ZIGZAGOON
	.short 0x0004, 0x0001 ; SPECIES_LINOONE
	.short 0x0001, 0x0001 ; SPECIES_WURMPLE
	.short 0x0005, 0x0000 ; SPECIES_SILCOON
	.short 0x0001, 0x0001 ; SPECIES_BEAUTIFLY
	.short 0x0005, 0x0000 ; SPECIES_CASCOON
	.short 0x0002, 0x0001 ; SPECIES_DUSTOX
	.short 0x0001, 0x0001 ; SPECIES_LOTAD
	.short 0x0004, 0x0001 ; SPECIES_LOMBRE
	.short 0x0004, 0x0001 ; SPECIES_LUDICOLO
	.short 0x0005, 0x0001 ; SPECIES_SEEDOT
	.short 0x0002, 0x0001 ; SPECIES_NUZLEAF
	.short 0x0003, 0x0001 ; SPECIES_SHIFTRY
	.short 0x0001, 0x0001 ; SPECIES_TAILLOW
	.short 0x0002, 0x0001 ; SPECIES_SWELLOW
	.short 0x0001, 0x0001 ; SPECIES_WINGULL
	.short 0x0001, 0x0001 ; SPECIES_PELIPPER
	.short 0x0001, 0x0001 ; SPECIES_RALTS
	.short 0x0001, 0x0001 ; SPECIES_KIRLIA
	.short 0x0001, 0x0001 ; SPECIES_GARDEVOIR
	.short 0x0001, 0x0001 ; SPECIES_SURSKIT
	.short 0x0002, 0x0000 ; SPECIES_MASQUERAIN
	.short 0x0001, 0x0001 ; SPECIES_SHROOMISH
	.short 0x0002, 0x0001 ; SPECIES_BRELOOM
	.short 0x0004, 0x0001 ; SPECIES_SLAKOTH
	.short 0x0002, 0x0001 ; SPECIES_VIGOROTH
	.short 0x0004, 0x0001 ; SPECIES_SLAKING
	.short 0x0005, 0x0001 ; SPECIES_NINCADA
	.short 0x0002, 0x0001 ; SPECIES_NINJASK
	.short 0x0004, 0x0001 ; SPECIES_SHEDINJA
	.short 0x0004, 0x0001 ; SPECIES_WHISMUR
	.short 0x0004, 0x0001 ; SPECIES_LOUDRED
	.short 0x0002, 0x0001 ; SPECIES_EXPLOUD
	.short 0x0001, 0x0001 ; SPECIES_MAKUHITA
	.short 0x0002, 0x0001 ; SPECIES_HARIYAMA
	.short 0x0001, 0x0001 ; SPECIES_AZURILL
	.short 0x0005, 0x0001 ; SPECIES_NOSEPASS
	.short 0x0001, 0x0001 ; SPECIES_SKITTY
	.short 0x0001, 0x0001 ; SPECIES_DELCATTY
	.short 0x0003, 0x0001 ; SPECIES_SABLEYE
	.short 0x0001, 0x0001 ; SPECIES_MAWILE
	.short 0x0001, 0x0001 ; SPECIES_ARON
	.short 0x0002, 0x0001 ; SPECIES_LAIRON
	.short 0x0002, 0x0001 ; SPECIES_AGGRON
	.short 0x0001, 0x0001 ; SPECIES_MEDITITE
	.short 0x0002, 0x0001 ; SPECIES_MEDICHAM
	.short 0x0001, 0x0001 ; SPECIES_ELECTRIKE
	.short 0x0002, 0x0001 ; SPECIES_MANECTRIC
	.short 0x0001, 0x0001 ; SPECIES_PLUSLE
	.short 0x0001, 0x0001 ; SPECIES_MINUN
	.short 0x0002, 0x0001 ; SPECIES_VOLBEAT
	.short 0x0001, 0x0001 ; SPECIES_ILLUMISE
	.short 0x0001, 0x0001 ; SPECIES_ROSELIA
	.short 0x0004, 0x0000 ; SPECIES_GULPIN
	.short 0x0004, 0x0000 ; SPECIES_SWALOT
	.short 0x0003, 0x0000 ; SPECIES_CARVANHA
	.short 0x0003, 0x0000 ; SPECIES_SHARPEDO
	.short 0x0001, 0x0000 ; SPECIES_WAILMER
	.short 0x0002, 0x0000 ; SPECIES_WAILORD
	.short 0x0004, 0x0001 ; SPECIES_NUMEL
	.short 0x0004, 0x0001 ; SPECIES_CAMERUPT
	.short 0x0004, 0x0001 ; SPECIES_TORKOAL
	.short 0x0001, 0x0000 ; SPECIES_SPOINK
	.short 0x0002, 0x0001 ; SPECIES_GRUMPIG
	.short 0x0004, 0x0001 ; SPECIES_SPINDA
	.short 0x0004, 0x0001 ; SPECIES_TRAPINCH
	.short 0x0002, 0x0001 ; SPECIES_VIBRAVA
	.short 0x0002, 0x0001 ; SPECIES_FLYGON
	.short 0x0001, 0x0001 ; SPECIES_CACNEA
	.short 0x0003, 0x0001 ; SPECIES_CACTURNE
	.short 0x0001, 0x0001 ; SPECIES_SWABLU
	.short 0x0001, 0x0001 ; SPECIES_ALTARIA
	.short 0x0002, 0x0001 ; SPECIES_ZANGOOSE
	.short 0x0003, 0x0000 ; SPECIES_SEVIPER
	.short 0x0005, 0x0000 ; SPECIES_LUNATONE
	.short 0x0005, 0x0000 ; SPECIES_SOLROCK
	.short 0x0001, 0x0000 ; SPECIES_BARBOACH
	.short 0x0004, 0x0000 ; SPECIES_WHISCASH
	.short 0x0002, 0x0001 ; SPECIES_CORPHISH
	.short 0x0003, 0x0001 ; SPECIES_CRAWDAUNT
	.short 0x0005, 0x0001 ; SPECIES_BALTOY
	.short 0x0005, 0x0001 ; SPECIES_CLAYDOL
	.short 0x0005, 0x0001 ; SPECIES_LILEEP
	.short 0x0005, 0x0001 ; SPECIES_CRADILY
	.short 0x0005, 0x0000 ; SPECIES_ANORITH
	.short 0x0002, 0x0001 ; SPECIES_ARMALDO
	.short 0x0004, 0x0000 ; SPECIES_FEEBAS
	.short 0x0002, 0x0000 ; SPECIES_MILOTIC
	.short 0x0001, 0x0000 ; SPECIES_CASTFORM
	.short 0x0001, 0x0001 ; SPECIES_KECLEON
	.short 0x0003, 0x0000 ; SPECIES_SHUPPET
	.short 0x0003, 0x0001 ; SPECIES_BANETTE
	.short 0x0003, 0x0000 ; SPECIES_DUSKULL
	.short 0x0003, 0x0001 ; SPECIES_DUSCLOPS
	.short 0x0002, 0x0001 ; SPECIES_TROPIUS
	.short 0x0001, 0x0000 ; SPECIES_CHIMECHO
	.short 0x0003, 0x0001 ; SPECIES_ABSOL
	.short 0x0004, 0x0001 ; SPECIES_WYNAUT
	.short 0x0001, 0x0001 ; SPECIES_SNORUNT
	.short 0x0002, 0x0000 ; SPECIES_GLALIE
	.short 0x0001, 0x0000 ; SPECIES_SPHEAL
	.short 0x0002, 0x0000 ; SPECIES_SEALEO
	.short 0x0002, 0x0000 ; SPECIES_WALREIN
	.short 0x0001, 0x0000 ; SPECIES_CLAMPERL
	.short 0x0002, 0x0000 ; SPECIES_HUNTAIL
	.short 0x0001, 0x0000 ; SPECIES_GOREBYSS
	.short 0x0004, 0x0000 ; SPECIES_RELICANTH
	.short 0x0001, 0x0000 ; SPECIES_LUVDISC
	.short 0x0001, 0x0001 ; SPECIES_BAGON
	.short 0x0005, 0x0001 ; SPECIES_SHELGON
	.short 0x0002, 0x0001 ; SPECIES_SALAMENCE
	.short 0x0005, 0x0001 ; SPECIES_BELDUM
	.short 0x0005, 0x0001 ; SPECIES_METANG
	.short 0x0002, 0x0001 ; SPECIES_METAGROSS
	.short 0x0005, 0x0001 ; SPECIES_REGIROCK
	.short 0x0005, 0x0001 ; SPECIES_REGICE
	.short 0x0005, 0x0001 ; SPECIES_REGISTEEL
	.short 0x0001, 0x0001 ; SPECIES_LATIAS
	.short 0x0002, 0x0001 ; SPECIES_LATIOS
	.short 0x0002, 0x0001 ; SPECIES_KYOGRE
	.short 0x0002, 0x0001 ; SPECIES_GROUDON
	.short 0x0002, 0x0000 ; SPECIES_RAYQUAZA
	.short 0x0001, 0x0001 ; SPECIES_JIRACHI
	.short 0x0002, 0x0001 ; SPECIES_DEOXYS
	.short 0x0001, 0x0001 ; SPECIES_TURTWIG
	.short 0x0001, 0x0001 ; SPECIES_GROTLE
	.short 0x0002, 0x0001 ; SPECIES_TORTERRA
	.short 0x0001, 0x0001 ; SPECIES_CHIMCHAR
	.short 0x0002, 0x0001 ; SPECIES_MONFERNO
	.short 0x0002, 0x0001 ; SPECIES_INFERNAPE
	.short 0x0001, 0x0001 ; SPECIES_PIPLUP
	.short 0x0002, 0x0001 ; SPECIES_PRINPLUP
	.short 0x0002, 0x0001 ; SPECIES_EMPOLEON
	.short 0x0001, 0x0001 ; SPECIES_STARLY
	.short 0x0001, 0x0001 ; SPECIES_STARAVIA
	.short 0x0002, 0x0001 ; SPECIES_STARAPTOR
	.short 0x0004, 0x0001 ; SPECIES_BIDOOF
	.short 0x0004, 0x0001 ; SPECIES_BIBAREL
	.short 0x0001, 0x0001 ; SPECIES_KRICKETOT
	.short 0x0002, 0x0001 ; SPECIES_KRICKETUNE
	.short 0x0001, 0x0001 ; SPECIES_SHINX
	.short 0x0001, 0x0001 ; SPECIES_LUXIO
	.short 0x0002, 0x0001 ; SPECIES_LUXRAY
	.short 0x0001, 0x0001 ; SPECIES_BUDEW
	.short 0x0002, 0x0001 ; SPECIES_ROSERADE
	.short 0x0002, 0x0001 ; SPECIES_CRANIDOS
	.short 0x0002, 0x0001 ; SPECIES_RAMPARDOS
	.short 0x0002, 0x0001 ; SPECIES_SHIELDON
	.short 0x0002, 0x0001 ; SPECIES_BASTIODON
	.short 0x0001, 0x0000 ; SPECIES_BURMY
	.short 0x0001, 0x0000 ; SPECIES_WORMADAM
	.short 0x0002, 0x0001 ; SPECIES_MOTHIM
	.short 0x0001, 0x0000 ; SPECIES_COMBEE
	.short 0x0001, 0x0000 ; SPECIES_VESPIQUEN
	.short 0x0001, 0x0001 ; SPECIES_PACHIRISU
	.short 0x0001, 0x0001 ; SPECIES_BUIZEL
	.short 0x0002, 0x0001 ; SPECIES_FLOATZEL
	.short 0x0001, 0x0001 ; SPECIES_CHERUBI
	.short 0x0001, 0x0001 ; SPECIES_CHERRIM
	.short 0x0001, 0x0001 ; SPECIES_SHELLOS
	.short 0x0003, 0x0001 ; SPECIES_GASTRODON
	.short 0x0001, 0x0001 ; SPECIES_AMBIPOM
	.short 0x0003, 0x0000 ; SPECIES_DRIFLOON
	.short 0x0003, 0x0000 ; SPECIES_DRIFBLIM
	.short 0x0001, 0x0001 ; SPECIES_BUNEARY
	.short 0x0001, 0x0001 ; SPECIES_LOPUNNY
	.short 0x0003, 0x0000 ; SPECIES_MISMAGIUS
	.short 0x0003, 0x0001 ; SPECIES_HONCHKROW
	.short 0x0001, 0x0001 ; SPECIES_GLAMEOW
	.short 0x0001, 0x0001 ; SPECIES_PURUGLY
	.short 0x0001, 0x0001 ; SPECIES_CHINGLING
	.short 0x0003, 0x0001 ; SPECIES_STUNKY
	.short 0x0003, 0x0001 ; SPECIES_SKUNTANK
	.short 0x0005, 0x0000 ; SPECIES_BRONZOR
	.short 0x0005, 0x0000 ; SPECIES_BRONZONG
	.short 0x0004, 0x0001 ; SPECIES_BONSLY
	.short 0x0001, 0x0001 ; SPECIES_MIME_JR
	.short 0x0001, 0x0001 ; SPECIES_HAPPINY
	.short 0x0004, 0x0001 ; SPECIES_CHATOT
	.short 0x0003, 0x0001 ; SPECIES_SPIRITOMB
	.short 0x0001, 0x0001 ; SPECIES_GIBLE
	.short 0x0002, 0x0001 ; SPECIES_GABITE
	.short 0x0002, 0x0001 ; SPECIES_GARCHOMP
	.short 0x0004, 0x0001 ; SPECIES_MUNCHLAX
	.short 0x0001, 0x0001 ; SPECIES_RIOLU
	.short 0x0002, 0x0001 ; SPECIES_LUCARIO
	.short 0x0004, 0x0001 ; SPECIES_HIPPOPOTAS
	.short 0x0002, 0x0001 ; SPECIES_HIPPOWDON
	.short 0x0003, 0x0001 ; SPECIES_SKORUPI
	.short 0x0003, 0x0001 ; SPECIES_DRAPION
	.short 0x0003, 0x0001 ; SPECIES_CROAGUNK
	.short 0x0003, 0x0001 ; SPECIES_TOXICROAK
	.short 0x0004, 0x0000 ; SPECIES_CARNIVINE
	.short 0x0001, 0x0000 ; SPECIES_FINNEON
	.short 0x0002, 0x0000 ; SPECIES_LUMINEON
	.short 0x0001, 0x0000 ; SPECIES_MANTYKE
	.short 0x0001, 0x0001 ; SPECIES_SNOVER
	.short 0x0002, 0x0001 ; SPECIES_ABOMASNOW
	.short 0x0002, 0x0001 ; SPECIES_WEAVILE
	.short 0x0005, 0x0000 ; SPECIES_MAGNEZONE
	.short 0x0004, 0x0001 ; SPECIES_LICKILICKY
	.short 0x0002, 0x0001 ; SPECIES_RHYPERIOR
	.short 0x0004, 0x0001 ; SPECIES_TANGROWTH
	.short 0x0002, 0x0001 ; SPECIES_ELECTIVIRE
	.short 0x0002, 0x0001 ; SPECIES_MAGMORTAR
	.short 0x0002, 0x0001 ; SPECIES_TOGEKISS
	.short 0x0002, 0x0001 ; SPECIES_YANMEGA
	.short 0x0002, 0x0001 ; SPECIES_LEAFEON
	.short 0x0002, 0x0001 ; SPECIES_GLACEON
	.short 0x0002, 0x0001 ; SPECIES_GLISCOR
	.short 0x0004, 0x0001 ; SPECIES_MAMOSWINE
	.short 0x0005, 0x0001 ; SPECIES_PORYGON_Z
	.short 0x0002, 0x0001 ; SPECIES_GALLADE
	.short 0x0005, 0x0001 ; SPECIES_PROBOPASS
	.short 0x0003, 0x0000 ; SPECIES_DUSKNOIR
	.short 0x0001, 0x0000 ; SPECIES_FROSLASS
	.short 0x0002, 0x0000 ; SPECIES_ROTOM
	.short 0x0001, 0x0001 ; SPECIES_UXIE
	.short 0x0001, 0x0001 ; SPECIES_MESPRIT
	.short 0x0001, 0x0001 ; SPECIES_AZELF
	.short 0x0002, 0x0001 ; SPECIES_DIALGA
	.short 0x0002, 0x0001 ; SPECIES_PALKIA
	.short 0x0002, 0x0001 ; SPECIES_HEATRAN
	.short 0x0005, 0x0001 ; SPECIES_REGIGIGAS
	.short 0x0002, 0x0001 ; SPECIES_GIRATINA
	.short 0x0002, 0x0000 ; SPECIES_CRESSELIA
	.short 0x0001, 0x0000 ; SPECIES_PHIONE
	.short 0x0001, 0x0000 ; SPECIES_MANAPHY
	.short 0x0003, 0x0001 ; SPECIES_DARKRAI
	.short 0x0001, 0x0001 ; SPECIES_SHAYMIN
	.short 0x0002, 0x0001 ; SPECIES_ARCEUS

	.global UNK05_021FD1B8
UNK05_021FD1B8: ; 0x021FD1B8
	.word MOD05_021F6284, MOD05_021F628C, MOD05_021F62C4, 0x00000000

	.section .data

	.balign 4
	.global UNK05_021FD648
UNK05_021FD648: ; 0x021FD648
	.asciz "fielddata/build_model/build_model_matshp.dat"

	.section .bss

	.global UNK05_021FD680
UNK05_021FD680: ; 0x021FD680
	.space 0x4

	.global UNK05_021FD684
UNK05_021FD684: ; 0x021FD684
	.space 0x3C01C
