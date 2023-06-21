	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD11_02258238
MOD11_02258238: ; 0x02258238
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	ldr r0, [r5, #4]
	bl MOD11_02230078
	str r0, [sp, #0x20]
	ldr r0, [r5, #4]
	bl MOD11_02230080
	add r7, r0, #0
	ldr r0, [r5, #4]
	bl MOD11_02230C68
	add r6, r0, #0
	ldrb r0, [r5, #8]
	cmp r0, #0
	ldrb r0, [r5, #9]
	bne _02258274
	lsl r1, r0, #1
	ldr r0, _02258320 ; =MOD11_0225F5C0
	ldrh r3, [r0, r1]
	ldr r0, _02258324 ; =0x00004E2D
	mov r1, #0x58
	str r1, [sp, #0x1c]
	add r4, r0, #0
	mov r1, #0x59
	sub r4, #8
	str r1, [sp, #0x18]
	b _02258288
_02258274:
	lsl r1, r0, #1
	ldr r0, _02258328 ; =MOD11_0225F5A8
	ldrh r3, [r0, r1]
	ldr r0, _0225832C ; =0x00004E2E
	mov r1, #0x5b
	str r1, [sp, #0x1c]
	add r4, r0, #0
	mov r1, #0x5c
	sub r4, #8
	str r1, [sp, #0x18]
_02258288:
	mov r1, #1
	str r1, [sp]
	str r1, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [sp, #0x20]
	add r1, r7, #0
	mov r2, #0x1b
	bl sub_0200C00C
	ldr r0, [r5, #4]
	bl MOD11_022300CC
	mov r1, #0x1b
	str r1, [sp]
	ldrb r1, [r5, #9]
	mov r2, #6
	add r3, r1, #0
	mul r3, r2
	ldr r2, _02258330 ; =MOD11_0225F5D8
	lsl r1, r6, #1
	add r2, r2, r3
	ldrh r1, [r1, r2]
	ldr r2, [sp, #0x20]
	add r3, r7, #0
	str r1, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	mov r1, #1
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	ldr r1, _02258334 ; =0x00004E29
	str r1, [sp, #0x14]
	mov r1, #2
	bl sub_0200C0DC
	ldr r0, [r5, #4]
	bl MOD11_022300CC
	mov r1, #0
	str r1, [sp]
	mov r1, #0x20
	str r1, [sp, #4]
	mov r1, #0x70
	str r1, [sp, #8]
	ldrb r2, [r5, #9]
	mov r3, #6
	lsl r5, r6, #1
	mul r3, r2
	ldr r2, _02258330 ; =MOD11_0225F5D8
	mov r1, #0x1b
	add r2, r2, r3
	ldrh r2, [r5, r2]
	mov r3, #5
	bl PaletteData_LoadNarc
	mov r0, #1
	str r0, [sp]
	ldr r0, [sp, #0x20]
	ldr r3, [sp, #0x1c]
	add r1, r7, #0
	mov r2, #0x1b
	str r4, [sp, #4]
	bl sub_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, [sp, #0x20]
	ldr r3, [sp, #0x18]
	add r1, r7, #0
	mov r2, #0x1b
	str r4, [sp, #4]
	bl sub_0200C13C
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_02258320: .word MOD11_0225F5C0
_02258324: .word 0x00004E2D
_02258328: .word MOD11_0225F5A8
_0225832C: .word 0x00004E2E
_02258330: .word MOD11_0225F5D8
_02258334: .word 0x00004E29

	thumb_func_start MOD11_02258338
MOD11_02258338: ; 0x02258338
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl MOD11_02230078
	add r5, r0, #0
	ldr r0, [r4, #4]
	bl MOD11_02230080
	add r1, r0, #0
	add r0, r5, #0
	ldrb r3, [r4, #8]
	mov r2, #0x34
	ldr r5, _02258368 ; =MOD11_0225F61C
	mul r2, r3
	add r2, r5, r2
	bl sub_0200C154
	str r0, [r4]
	ldr r0, [r0]
	bl sub_0200C59C
	pop {r3, r4, r5, pc}
	nop
_02258368: .word MOD11_0225F61C

	thumb_func_start MOD11_0225836C
MOD11_0225836C: ; 0x0225836C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _0225837E
	bl sub_0200C3DC
	mov r0, #0
	str r0, [r4]
_0225837E:
	pop {r4, pc}

	thumb_func_start MOD11_02258380
MOD11_02258380: ; 0x02258380
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #4]
	bl MOD11_02230080
	add r4, r0, #0
	ldrb r0, [r5, #8]
	cmp r0, #0
	bne _02258396
	ldr r1, _022583BC ; =0x00004E2D
	b _02258398
_02258396:
	ldr r1, _022583C0 ; =0x00004E2E
_02258398:
	add r5, r1, #0
	add r0, r4, #0
	sub r5, #8
	bl sub_0200C358
	ldr r1, _022583C4 ; =0x00004E29
	add r0, r4, #0
	bl sub_0200C368
	add r0, r4, #0
	add r1, r5, #0
	bl sub_0200C378
	add r0, r4, #0
	add r1, r5, #0
	bl sub_0200C388
	pop {r3, r4, r5, pc}
	.align 2, 0
_022583BC: .word 0x00004E2D
_022583C0: .word 0x00004E2E
_022583C4: .word 0x00004E29

	thumb_func_start MOD11_022583C8
MOD11_022583C8: ; 0x022583C8
	push {r3, lr}
	ldr r0, [r0]
	cmp r0, #0
	beq _022583D4
	bl sub_0200C644
_022583D4:
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD11_022583D8
MOD11_022583D8: ; 0x022583D8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	mov r0, #0
	add r1, r5, #0
	mov r2, #0x10
	add r7, r3, #0
	bl MIi_CpuClearFast
	str r4, [r5, #4]
	strb r6, [r5, #8]
	strb r7, [r5, #9]
	cmp r7, #0xc
	blt _022583FE
	bl GF_AssertFail
	mov r0, #0
	strb r0, [r5, #9]
_022583FE:
	add r0, r5, #0
	bl MOD11_02258238
	add r0, r5, #0
	bl MOD11_02258338
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD11_0225840C
MOD11_0225840C: ; 0x0225840C
	push {r4, lr}
	add r4, r0, #0
	bl MOD11_0225836C
	add r0, r4, #0
	bl MOD11_02258380
	mov r0, #0
	add r1, r4, #0
	mov r2, #0x10
	bl MIi_CpuClearFast
	pop {r4, pc}
	.align 2, 0

	.section .rodata

	.global MOD11_0225F5A8
MOD11_0225F5A8: ; 0x0225F5A8
	.byte 0x60, 0x00, 0x6A, 0x00, 0x5A, 0x00, 0x70, 0x00, 0x64, 0x00, 0x6E, 0x00, 0x66, 0x00, 0x5E, 0x00
	.byte 0x62, 0x00, 0x68, 0x00, 0x6C, 0x00, 0x00, 0x00

	.global MOD11_0225F5C0
MOD11_0225F5C0: ; 0x0225F5C0
	.byte 0x5F, 0x00, 0x69, 0x00, 0x57, 0x00, 0x6F, 0x00
	.byte 0x63, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x5D, 0x00, 0x61, 0x00, 0x67, 0x00, 0x6B, 0x00, 0x00, 0x00

	.global MOD11_0225F5D8
MOD11_0225F5D8: ; 0x0225F5D8
	.byte 0x07, 0x00, 0x08, 0x00, 0x09, 0x00, 0x16, 0x00, 0x17, 0x00, 0x18, 0x00, 0x01, 0x00, 0x02, 0x00
	.byte 0x03, 0x00, 0x1F, 0x00, 0x20, 0x00, 0x21, 0x00, 0x0D, 0x00, 0x0E, 0x00, 0x0F, 0x00, 0x1C, 0x00
	.byte 0x1D, 0x00, 0x1E, 0x00, 0x10, 0x00, 0x11, 0x00, 0x12, 0x00, 0x04, 0x00, 0x05, 0x00, 0x06, 0x00
	.byte 0x0A, 0x00, 0x0B, 0x00, 0x0C, 0x00, 0x13, 0x00, 0x14, 0x00, 0x15, 0x00, 0x19, 0x00, 0x1A, 0x00
	.byte 0x1B, 0x00, 0x00, 0x00

	.global MOD11_0225F61C
MOD11_0225F61C: ; 0x0225F61C
	.byte 0x50, 0x01, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x03, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2D, 0x4E, 0x00, 0x00, 0x29, 0x4E, 0x00, 0x00
	.byte 0x25, 0x4E, 0x00, 0x00, 0x25, 0x4E, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xFF, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xE8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2E, 0x4E, 0x00, 0x00
	.byte 0x29, 0x4E, 0x00, 0x00, 0x26, 0x4E, 0x00, 0x00, 0x26, 0x4E, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
