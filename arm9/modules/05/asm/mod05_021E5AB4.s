	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021E5AB4
MOD05_021E5AB4: ; 0x021E5AB4
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x38
	add r3, r2, #0
	add r5, r0, #0
	bl MOD05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl MOD05_021E5AE0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E5AD0
MOD05_021E5AD0: ; 0x021E5AD0
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021E5B18
	add r0, r4, #0
	bl MOD05_021E4C00
	pop {r4, pc}

	thumb_func_start MOD05_021E5AE0
MOD05_021E5AE0: ; 0x021E5AE0
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x28
	bl MOD05_021E5294
	ldr r0, [r4]
	add r1, r4, #4
	mov r2, #0x3a
	mov r3, #0
	bl MOD05_021E5224
	mov r0, #0x71
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	add r1, r4, #0
	ldr r0, [r4]
	add r2, r4, #4
	add r4, #0x28
	add r1, #0x14
	add r3, r4, #0
	bl MOD05_021E5260
	add sp, #8
	pop {r4, pc}

	thumb_func_start MOD05_021E5B18
MOD05_021E5B18: ; 0x021E5B18
	push {r4, lr}
	add r4, r0, #0
	add r0, r4, #4
	bl MOD05_021F52C8
	add r0, r4, #0
	add r4, #0x28
	add r0, #0x14
	add r1, r4, #0
	bl MOD05_021F5358
	pop {r4, pc}

	thumb_func_start MOD05_021E5B30
MOD05_021E5B30: ; 0x021E5B30
	push {r4, r5, lr}
	sub sp, #0x1c
	ldr r0, [r0, #0x3c]
	add r5, r1, #0
	mov r1, #8
	add r4, r3, #0
	str r0, [sp, #8]
	bl MOD05_021E4C08
	str r0, [sp, #0xc]
	mov r0, #2
	lsl r1, r5, #0x10
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x10]
	mov r0, #0xa
	lsl r0, r0, #0xc
	str r0, [sp, #0x14]
	lsl r0, r4, #0x10
	str r0, [sp, #0x18]
	add r0, sp, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, _021E5B78 ; =UNK05_021F768C
	add r2, sp, #0x10
	mov r3, #0
	bl MOD05_021E4DC4
	ldr r0, _021E5B7C ; =0x00000609
	bl PlaySE
	add sp, #0x1c
	pop {r4, r5, pc}
	nop
_021E5B78: .word UNK05_021F768C
_021E5B7C: .word 0x00000609

	thumb_func_start MOD05_021E5B80
MOD05_021E5B80: ; 0x021E5B80
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r6, r0, #0
	add r5, r1, #0
	bl sub_0206475C
	ldr r1, [r0]
	ldr r0, [r0, #4]
	mov r2, #1
	str r1, [r5, #4]
	str r0, [r5, #8]
	ldr r0, [r5, #4]
	mov r1, #0x90
	mov r3, #0
	bl MOD05_021E4BE8
	add r4, r0, #0
	str r4, [r5]
	ldr r0, [r5, #4]
	add r1, r4, #4
	bl MOD05_021E5294
	ldr r2, [r5, #8]
	add r0, r4, #4
	ldr r1, [r2, #0x18]
	ldr r2, [r2, #0xc]
	bl NNS_G3dAllocAnmObj
	str r0, [r4]
	ldr r3, [r5, #8]
	ldr r1, [r3, #0x18]
	ldr r2, [r3, #0xc]
	ldr r3, [r3, #0x10]
	bl NNS_G3dAnmObjInit
	ldr r1, [r5, #8]
	add r0, r4, #0
	add r0, #0x18
	add r1, r1, #4
	bl MOD05_021F5400
	add r0, r4, #0
	ldr r1, [r4]
	add r0, #0x18
	bl NNS_G3dRenderObjAddAnmObj
	add r0, r6, #0
	add r1, sp, #0
	bl sub_0206477C
	add r4, #0x18
	ldr r1, [sp]
	ldr r2, [sp, #4]
	ldr r3, [sp, #8]
	add r0, r4, #0
	bl MOD05_021F54D0
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}

	thumb_func_start MOD05_021E5BF8
MOD05_021E5BF8: ; 0x021E5BF8
	push {r4, lr}
	ldr r4, [r1]
	ldr r1, [r4]
	add r0, r4, #4
	bl NNS_G3dFreeAnmObj
	add r0, r4, #0
	bl MOD05_021E4C00
	pop {r4, pc}

	thumb_func_start MOD05_021E5C0C
MOD05_021E5C0C: ; 0x021E5C0C
	push {r4, lr}
	ldr r1, [r1]
	ldr r2, [r1]
	ldr r3, [r1, #0x14]
	ldr r2, [r2, #8]
	ldrh r2, [r2, #4]
	lsl r4, r2, #0xc
	mov r2, #1
	lsl r2, r2, #0xc
	add r2, r3, r2
	str r2, [r1, #0x14]
	cmp r2, r4
	ble _021E5C2C
	bl MOD05_021E4DE4
	pop {r4, pc}
_021E5C2C:
	ldr r0, [r1]
	str r2, [r0]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E5C34
MOD05_021E5C34: ; 0x021E5C34
	push {r3, r4, r5, lr}
	sub sp, #0x48
	ldr r4, [r1]
	ldr r5, _021E5C88 ; =UNK05_021F76A0
	add r3, sp, #0x24
	mov r2, #4
_021E5C40:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021E5C40
	ldr r0, [r5]
	str r0, [r3]
	bl NNS_G3dGlbGetInvV
	mov r2, #0
	add r5, r0, #0
	add r0, sp, #0x24
	mov r1, #0x5a
	add r3, r2, #0
	bl sub_0201CB20
	add r0, r5, #0
	add r1, sp, #0
	bl MI_Copy36B
	add r0, sp, #0x24
	add r1, sp, #0
	add r2, r0, #0
	bl MTX_Concat33
	add r0, r4, #0
	add r1, r4, #0
	add r4, #0x78
	add r0, #0x18
	add r1, #0x6c
	add r2, sp, #0x24
	add r3, r4, #0
	bl sub_0201B26C
	add sp, #0x48
	pop {r3, r4, r5, pc}
	nop
_021E5C88: .word UNK05_021F76A0

	.section .rodata

	.global UNK05_021F768C
UNK05_021F768C: ; 0x021F768C
	.word 0x0000000C, MOD05_021E5B80, MOD05_021E5BF8, MOD05_021E5C0C
	.word MOD05_021E5C34

	.global UNK05_021F76A0
UNK05_021F76A0: ; 0x021F76A0
	.word 0x00001000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00001000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00001000
