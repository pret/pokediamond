	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021E5918
MOD05_021E5918: ; 0x021E5918
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x6c
	add r3, r2, #0
	add r5, r0, #0
	bl MOD05_021E4BE8
	add r4, r0, #0
	str r5, [r4, #8]
	bl MOD05_021E5944
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E5934
MOD05_021E5934: ; 0x021E5934
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021E5964
	add r0, r4, #0
	bl MOD05_021E4C00
	pop {r4, pc}

	thumb_func_start MOD05_021E5944
MOD05_021E5944: ; 0x021E5944
	push {r3, lr}
	sub sp, #8
	add r3, r0, #0
	add r0, #0x60
	str r0, [sp]
	add r0, r3, #0
	add r0, #0x64
	str r0, [sp, #4]
	ldr r0, [r3, #8]
	mov r1, #0x18
	mov r2, #0
	add r3, #0xc
	bl MOD05_021E51EC
	add sp, #8
	pop {r3, pc}

	thumb_func_start MOD05_021E5964
MOD05_021E5964: ; 0x021E5964
	ldr r3, _021E596C ; =MOD05_021E4C00
	ldr r0, [r0, #0x64]
	bx r3
	nop
_021E596C: .word MOD05_021E4C00

	thumb_func_start MOD05_021E5970
MOD05_021E5970: ; 0x021E5970
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r0, #0
	bl MOD05_021E4C24
	add r4, r0, #0
	mov r1, #7
	str r4, [sp, #0x14]
	bl MOD05_021E4C08
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, sp, #8
	str r5, [sp, #0x1c]
	bl sub_02058B5C
	add r0, sp, #0x14
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r1, _021E59A8 ; =UNK05_021F7648
	add r0, r4, #0
	add r2, sp, #8
	mov r3, #0
	bl MOD05_021E4DC4
	add sp, #0x20
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021E59A8: .word UNK05_021F7648

	thumb_func_start MOD05_021E59AC
MOD05_021E59AC: ; 0x021E59AC
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	bl sub_0206475C
	add r3, r0, #0
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	add r2, #0x34
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #0x3c]
	bl MapObject_GetID
	str r0, [r4, #8]
	ldr r0, [r4, #0x3c]
	bl sub_02058450
	str r0, [r4, #0xc]
	mov r0, #6
	lsl r0, r0, #0xc
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x3c]
	add r1, sp, #0
	bl sub_02058B5C
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	mov r0, #0x3c
	str r0, [r4, #0x30]
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E59F8
MOD05_021E59F8: ; 0x021E59F8
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021E59FC
MOD05_021E59FC: ; 0x021E59FC
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r2, [r1, #0x30]
	add r4, r0, #0
	cmp r2, #0
	beq _021E5A0E
	sub r0, r2, #1
	str r0, [r1, #0x30]
	b _021E5A16
_021E5A0E:
	bl MOD05_021E4DE4
	add sp, #0xc
	pop {r3, r4, pc}
_021E5A16:
	ldr r0, [r1, #0x3c]
	add r1, sp, #0
	bl sub_02058B5C
	mov r0, #0xa
	ldr r1, [sp, #8]
	lsl r0, r0, #0xc
	sub r0, r1, r0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, sp, #0
	bl sub_0206476C
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start MOD05_021E5A34
MOD05_021E5A34: ; 0x021E5A34
	push {r4, r5, r6, lr}
	sub sp, #0x60
	ldr r5, _021E5AAC ; =UNK05_021F763C
	add r2, r0, #0
	add r4, r1, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x48
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	ldr r6, _021E5AB0 ; =UNK05_021F765C
	str r0, [r3]
	add r5, sp, #0x24
	mov r3, #4
_021E5A4E:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r3, r3, #1
	bne _021E5A4E
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
	ldr r0, [r4, #0x38]
	add r1, sp, #0x54
	add r0, #0xc
	add r2, sp, #0x24
	add r3, sp, #0x48
	bl sub_0201B2A8
	add sp, #0x60
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021E5AAC: .word UNK05_021F763C
_021E5AB0: .word UNK05_021F765C

	.section .rodata

	.global UNK05_021F763C
UNK05_021F763C: ; 0x021F763C
	.word 0x00001000, 0x00001000, 0x00001000

	.global UNK05_021F7648
UNK05_021F7648: ; 0x021F7648
	.word 0x00000040, MOD05_021E59AC, MOD05_021E59F8, MOD05_021E59FC
	.word MOD05_021E5A34

	.global UNK05_021F765C
UNK05_021F765C: ; 0x021F765C
	.word 0x00001000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00001000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00001000, 0x00001000, 0x00001000, 0x00001000
