	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021E55BC
ov05_021E55BC: ; 0x021E55BC
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x6c
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4, #8]
	bl ov05_021E55E8
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021E55D8
ov05_021E55D8: ; 0x021E55D8
	push {r4, lr}
	add r4, r0, #0
	bl ov05_021E5608
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov05_021E55E8
ov05_021E55E8: ; 0x021E55E8
	push {r3, lr}
	sub sp, #8
	add r3, r0, #0
	add r0, #0x60
	str r0, [sp]
	add r0, r3, #0
	add r0, #0x64
	str r0, [sp, #4]
	ldr r0, [r3, #8]
	mov r1, #0x16
	mov r2, #0
	add r3, #0xc
	bl ov05_021E51EC
	add sp, #8
	pop {r3, pc}

	thumb_func_start ov05_021E5608
ov05_021E5608: ; 0x021E5608
	ldr r3, _021E5610 ; =ov05_021E4C00
	ldr r0, [r0, #0x64]
	bx r3
	nop
_021E5610: .word ov05_021E4C00

	thumb_func_start ov05_021E5614
ov05_021E5614: ; 0x021E5614
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r0, #0
	bl ov05_021E4C24
	add r4, r0, #0
	mov r1, #5
	str r4, [sp, #0x14]
	bl ov05_021E4C08
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, sp, #8
	str r5, [sp, #0x1c]
	bl MapObject_CopyPositionVector
	add r0, sp, #0x14
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r1, _021E564C ; =ov05_021F75C0
	add r0, r4, #0
	add r2, sp, #8
	mov r3, #0
	bl ov05_021E4DC4
	add sp, #0x20
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021E564C: .word ov05_021F75C0

	thumb_func_start ov05_021E5650
ov05_021E5650: ; 0x021E5650
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	bl sub_0206475C
	add r3, r0, #0
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	add r2, #0x30
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #0x38]
	bl MapObject_GetID
	str r0, [r4, #8]
	ldr r0, [r4, #0x38]
	bl MapObject_GetMapID
	str r0, [r4, #0xc]
	mov r0, #6
	lsl r0, r0, #0xc
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x38]
	add r1, sp, #0
	bl MapObject_CopyPositionVector
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021E5698
ov05_021E5698: ; 0x021E5698
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021E569C
ov05_021E569C: ; 0x021E569C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldr r6, [r4, #0x38]
	ldr r1, [r4, #8]
	add r5, r0, #0
	ldr r2, [r4, #0xc]
	add r0, r6, #0
	bl sub_020582A8
	cmp r0, #0
	bne _021E56B8
	bl GF_AssertFail
_021E56B8:
	ldr r0, [r4]
	cmp r0, #0
	beq _021E56C8
	cmp r0, #1
	beq _021E56E6
	add sp, #0xc
	cmp r0, #2
	pop {r3, r4, r5, r6, pc}
_021E56C8:
	add r0, r6, #0
	add r1, sp, #0
	bl MapObject_CopyPositionVector
	mov r0, #0xa
	ldr r1, [sp, #8]
	lsl r0, r0, #0xc
	sub r0, r1, r0
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_021E56E6:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	cmp r0, #0x1e
	blt _021E56F6
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021E56F6:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021E56FC
ov05_021E56FC: ; 0x021E56FC
	push {r4, r5, r6, lr}
	sub sp, #0x60
	ldr r5, _021E5774 ; =ov05_021F75B4
	add r2, r0, #0
	add r4, r1, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x48
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	ldr r6, _021E5778 ; =ov05_021F75D4
	str r0, [r3]
	add r5, sp, #0x24
	mov r3, #4
_021E5716:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r3, r3, #1
	bne _021E5716
	ldr r0, [r6]
	add r1, sp, #0x54
	str r0, [r5]
	add r0, r2, #0
	bl sub_0206477C
	mov r0, #0x19
	ldr r1, [sp, #0x58]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x58]
	mov r0, #5
	ldr r1, [sp, #0x5c]
	lsl r0, r0, #0xc
	sub r0, r1, r0
	str r0, [sp, #0x5c]
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
	ldr r0, [r4, #0x34]
	add r1, sp, #0x54
	add r0, #0xc
	add r2, sp, #0x24
	add r3, sp, #0x48
	bl sub_0201B2A8
	add sp, #0x60
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021E5774: .word ov05_021F75B4
_021E5778: .word ov05_021F75D4

	.section .rodata

	.global ov05_021F75B4
ov05_021F75B4: ; 0x021F75B4
	.word 0x00001000, 0x00001000, 0x00001000

	.global ov05_021F75C0
ov05_021F75C0: ; 0x021F75C0
	.word 0x0000003C, ov05_021E5650, ov05_021E5698, ov05_021E569C
	.word ov05_021E56FC

	.global ov05_021F75D4
ov05_021F75D4: ; 0x021F75D4
	.word 0x00001000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00001000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00001000
