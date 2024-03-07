	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021F1CB8
ov05_021F1CB8: ; 0x021F1CB8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r1, #0
	mov r1, #1
	add r5, r0, #0
	add r6, r2, #0
	add r7, r3, #0
	bl sub_02058390
	cmp r0, #0
	beq _021F1CD2
	bl GF_AssertFail
_021F1CD2:
	add r0, r5, #0
	bl ov05_021F1D68
	add r0, r5, #0
	bl MapObjectManager_GetObjectCount
	str r0, [sp, #0x10]
	add r0, r5, #0
	bl sub_0205839C
	sub r0, r0, #1
	str r0, [sp, #0xc]
	add r0, r5, #0
	bl sub_020583A0
	str r4, [sp]
	str r6, [sp, #4]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	add r1, r5, #0
	str r7, [sp, #8]
	bl ov05_021F1F04
	add r0, r5, #0
	mov r1, #4
	bl ov05_021F3780
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl sub_020583A4
	ldr r1, _021F1D28 ; =ov05_021F8B84
	add r0, r4, #0
	ldr r1, [r1]
	bl ov05_021F3810
	add r0, r5, #0
	mov r1, #1
	bl sub_0205837C
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021F1D28: .word ov05_021F8B84

	thumb_func_start ov05_021F1D2C
ov05_021F1D2C: ; 0x021F1D2C
	push {r4, lr}
	add r4, r0, #0
	bl sub_020587E0
	cmp r0, #1
	beq _021F1D3C
	bl GF_AssertFail
_021F1D3C:
	add r0, r4, #0
	bl sub_020583A0
	bl ov05_021F1F58
	add r0, r4, #0
	bl sub_020583AC
	bl ov05_021F379C
	add r0, r4, #0
	mov r1, #0
	bl sub_020583A4
	add r0, r4, #0
	mov r1, #1
	bl sub_02058384
	add r0, r4, #0
	bl ov05_021F1D80
	pop {r4, pc}

	thumb_func_start ov05_021F1D68
ov05_021F1D68: ; 0x021F1D68
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x51
	mov r1, #4
	bl NARC_New
	add r1, r0, #0
	add r0, r4, #0
	bl sub_020583F0
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021F1D80
ov05_021F1D80: ; 0x021F1D80
	push {r3, lr}
	bl sub_020583F4
	bl NARC_Delete
	pop {r3, pc}

	thumb_func_start ov05_021F1D8C
ov05_021F1D8C: ; 0x021F1D8C
	push {r4, lr}
	add r4, r0, #0
	bl MapObject_GetManager
	mov r1, #4
	bl sub_02058390
	cmp r0, #0
	bne _021F1DC6
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xe
	bl MapObject_GetFlagsBits
	cmp r0, #0
	beq _021F1DC6
	add r0, r4, #0
	bl sub_02058920
	cmp r0, #0
	beq _021F1DC0
	add r0, r4, #0
	bl sub_02058AB4
	cmp r0, #0
	beq _021F1DC6
_021F1DC0:
	add r0, r4, #0
	bl sub_020586A0
_021F1DC6:
	pop {r4, pc}

	thumb_func_start ov05_021F1DC8
ov05_021F1DC8: ; 0x021F1DC8
	push {r3, lr}
	bl sub_02058458
	bl ov05_021F1DD4
	pop {r3, pc}

	thumb_func_start ov05_021F1DD4
ov05_021F1DD4: ; 0x021F1DD4
	push {r3, lr}
	ldr r3, _021F1DF4 ; =ov05_021F9A9C
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
_021F1DF4: .word ov05_021F9A9C
_021F1DF8: .word 0x0000FFFF

	thumb_func_start ov05_021F1DFC
ov05_021F1DFC: ; 0x021F1DFC
	push {r4, lr}
	add r4, r0, #0
	bl sub_02058920
	cmp r0, #1
	bne _021F1E16
	add r0, r4, #0
	bl sub_02058AB4
	cmp r0, #0
	bne _021F1E16
	mov r0, #1
	pop {r4, pc}
_021F1E16:
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #8
	bl MapObject_GetFlagsBits
	cmp r0, #0
	beq _021F1E28
	mov r0, #1
	pop {r4, pc}
_021F1E28:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start ov05_021F1E2C
ov05_021F1E2C: ; 0x021F1E2C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r2, #0
	bl sub_020583F4
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

	thumb_func_start ov05_021F1E64
ov05_021F1E64: ; 0x021F1E64
	push {r3, r4, r5, lr}
	sub sp, #0x30
	add r4, r1, #0
	add r5, r0, #0
	add r1, sp, #0x24
	bl sub_02058B5C
	add r0, r5, #0
	add r1, sp, #0x18
	bl sub_02058B84
	add r0, r5, #0
	add r1, sp, #0xc
	bl sub_02058BA4
	add r0, r5, #0
	add r1, sp, #0
	bl sub_02058BC4
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

	thumb_func_start ov05_021F1EC0
ov05_021F1EC0: ; 0x021F1EC0
	push {r4, lr}
	add r4, r0, #0
	bl sub_020584AC
	add r0, r4, #0
	bl sub_02058884
	cmp r0, #1
	bne _021F1ED8
	add r0, r4, #0
	bl sub_020586A0
_021F1ED8:
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021F1EDC
ov05_021F1EDC: ; 0x021F1EDC
	push {r4, lr}
	mov r1, #1
	add r4, r0, #0
	bl MapObject_SetVisible
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0x14
	bl MapObject_SetFlagsBits
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021F1EF4
ov05_021F1EF4: ; 0x021F1EF4
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F1EF8
ov05_021F1EF8: ; 0x021F1EF8
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F1EFC
ov05_021F1EFC: ; 0x021F1EFC
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F1F00
ov05_021F1F00: ; 0x021F1F00
	bx lr
	.balign 4, 0
