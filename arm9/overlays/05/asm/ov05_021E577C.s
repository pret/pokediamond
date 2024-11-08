	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021E577C
ov05_021E577C: ; 0x021E577C
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x6c
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4, #8]
	bl ov05_021E57A8
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021E5798
ov05_021E5798: ; 0x021E5798
	push {r4, lr}
	add r4, r0, #0
	bl ov05_021E57C8
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov05_021E57A8
ov05_021E57A8: ; 0x021E57A8
	push {r3, lr}
	sub sp, #8
	add r3, r0, #0
	add r0, #0x60
	str r0, [sp]
	add r0, r3, #0
	add r0, #0x64
	str r0, [sp, #4]
	ldr r0, [r3, #8]
	mov r1, #0x17
	mov r2, #0
	add r3, #0xc
	bl ov05_021E51EC
	add sp, #8
	pop {r3, pc}

	thumb_func_start ov05_021E57C8
ov05_021E57C8: ; 0x021E57C8
	ldr r3, _021E57D0 ; =ov05_021E4C00
	ldr r0, [r0, #0x64]
	bx r3
	nop
_021E57D0: .word ov05_021E4C00

	thumb_func_start ov05_021E57D4
ov05_021E57D4: ; 0x021E57D4
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r0, #0
	bl ov05_021E4C24
	add r4, r0, #0
	mov r1, #6
	str r4, [sp, #0x14]
	bl ov05_021E4C08
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, sp, #8
	str r5, [sp, #0x1c]
	bl MapObject_GetPositionVec
	add r0, sp, #0x14
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r1, _021E580C ; =ov05_021F7604
	add r0, r4, #0
	add r2, sp, #8
	mov r3, #0
	bl ov05_021E4DC4
	add sp, #0x20
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021E580C: .word ov05_021F7604

	thumb_func_start ov05_021E5810
ov05_021E5810: ; 0x021E5810
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
	bl MapObject_GetPositionVec
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021E5858
ov05_021E5858: ; 0x021E5858
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021E585C
ov05_021E585C: ; 0x021E585C
	push {r4, r5, lr}
	sub sp, #0xc
	add r2, r1, #0
	ldr r5, [r2, #0x38]
	ldr r1, [r2, #8]
	add r4, r0, #0
	ldr r2, [r2, #0xc]
	add r0, r5, #0
	bl sub_020582A8
	cmp r0, #0
	bne _021E5878
	bl GF_AssertFail
_021E5878:
	add r0, r5, #0
	add r1, sp, #0
	bl MapObject_GetPositionVec
	mov r0, #0xa
	ldr r1, [sp, #8]
	lsl r0, r0, #0xc
	sub r0, r1, r0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, sp, #0
	bl sub_0206476C
	add sp, #0xc
	pop {r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021E5898
ov05_021E5898: ; 0x021E5898
	push {r4, r5, r6, lr}
	sub sp, #0x60
	ldr r5, _021E5910 ; =ov05_021F75F8
	add r2, r0, #0
	add r4, r1, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x48
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	ldr r6, _021E5914 ; =ov05_021F7618
	str r0, [r3]
	add r5, sp, #0x24
	mov r3, #4
_021E58B2:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r3, r3, #1
	bne _021E58B2
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
_021E5910: .word ov05_021F75F8
_021E5914: .word ov05_021F7618

	.section .rodata

	.global ov05_021F75F8
ov05_021F75F8: ; 0x021F75F8
	.word 0x00001000, 0x00001000, 0x00001000

	.global ov05_021F7604
ov05_021F7604: ; 0x021F7604
	.word 0x0000003C, ov05_021E5810, ov05_021E5858, ov05_021E585C
	.word ov05_021E5898

	.global ov05_021F7618
ov05_021F7618: ; 0x021F7618
	.word 0x00001000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00001000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00001000
