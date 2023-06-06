	.include "asm/macros.inc"
	.include "global.inc"

	.extern FX_SinCosTable_
	.section .rodata

	.global UNK_020F5C04
UNK_020F5C04: ; 0x020F5C04
	.byte 0x01, 0x03, 0x03, 0x01

	.global UNK_020F5C08
UNK_020F5C08: ; 0x020F5C08
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.section .data

	.global UNK_02105EC8
UNK_02105EC8: ; 0x02105EC8
	.word UNK_02105EF4
	.word UNK_02105F2C

	.global UNK_02105ED0
UNK_02105ED0: ; 0x02105ED0
	.word UNK_02105ED8
	.word UNK_02105F10

	.balign 4, 0
	.global UNK_02105ED8
UNK_02105ED8: ; 0x02105ED8
	.asciz "data/uground_pltt.resdat"

	.balign 4, 0
	.global UNK_02105EF4
UNK_02105EF4: ; 0x02105EF4
	.asciz "data/uground_char.resdat"

	.balign 4, 0
	.global UNK_02105F10
UNK_02105F10: ; 0x02105F10
	.asciz "data/uground_pltt2.resdat"

	.balign 4, 0
	.global UNK_02105F2C
UNK_02105F2C: ; 0x02105F2C
	.asciz "data/uground_char2.resdat"

	.balign 4, 0
	.global UNK_02105F48
UNK_02105F48: ; 0x02105F48
	.asciz "data/uground_cell.resdat"

	.balign 4, 0
	.global UNK_02105F64
UNK_02105F64: ; 0x02105F64
	.asciz "data/uground_cellanm.resdat"

	.balign 4, 0
	.global UNK_02105F80
UNK_02105F80: ; 0x02105F80
	.asciz "data/uground_clact.cldat"

	.text

	thumb_func_start FUN_02053750
FUN_02053750: ; 0x02053750
	push {r3-r7, lr}
	sub sp, #0x18
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _02053762
	bl FUN_0201FDEC
_02053762:
	mov r1, #0x6
	lsl r1, r1, #0x6
	ldr r0, [r4, r1]
	cmp r0, #0x5
	bls _0205376E
	b _020538B2
_0205376E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205377A: ; jump table (using 16-bit offset)
	.short _02053786 - _0205377A - 2; case 0
	.short _020537AA - _0205377A - 2; case 1
	.short _020537DA - _0205377A - 2; case 2
	.short _0205385C - _0205377A - 2; case 3
	.short _02053872 - _0205377A - 2; case 4
	.short _020538A2 - _0205377A - 2; case 5
_02053786:
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553A0
	bl FUN_02058914
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	ldr r0, [r0, #0x38]
	bl FUN_0205537C
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r1, [r4, r0]
	add sp, #0x18
	add r1, r1, #0x1
	str r1, [r4, r0]
	pop {r3-r7, pc}
_020537AA:
	sub r1, #0x24
	add r0, r4, #0x0
	add r1, r4, r1
	mov r2, #0x0
	bl FUN_02053F38
	mov r1, #0x5b
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	mov r2, #0x1
	bl FUN_02053F38
	mov r0, #0x5f
	mov r1, #0x2
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r1, r0, #0x4
	ldr r1, [r4, r1]
	add r0, r0, #0x4
	add r1, r1, #0x1
	add sp, #0x18
	str r1, [r4, r0]
	pop {r3-r7, pc}
_020537DA:
	mov r0, #0x0
	str r0, [sp, #0xc]
	sub r0, r1, #0x4
	ldr r0, [r4, r0]
	cmp r0, #0x0
	ble _02053810
	sub r1, #0x24
	add r7, r4, r1
	add r6, r4, #0x0
	add r5, sp, #0x10
_020537EE:
	mov r1, #0x5a
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r0, r7, #0x0
	blx r1
	stmia r5!, {r0}
	ldr r0, [sp, #0xc]
	add r7, #0x10
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	mov r0, #0x5f
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	ldr r0, [sp, #0xc]
	add r6, #0x10
	cmp r0, r1
	blt _020537EE
_02053810:
	ldr r0, [sp, #0x10]
	cmp r0, #0x2
	bne _0205382E
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
_0205382E:
	mov r0, #0x5f
	lsl r0, r0, #0x2
	ldr r2, [r4, r0]
	mov r3, #0x0
	cmp r2, #0x0
	ble _0205384A
	add r1, sp, #0x10
_0205383C:
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	bne _0205384A
	add r3, r3, #0x1
	add r1, r1, #0x4
	cmp r3, r2
	blt _0205383C
_0205384A:
	cmp r3, r2
	bne _020538B2
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r1, [r4, r0]
	add sp, #0x18
	add r1, r1, #0x1
	str r1, [r4, r0]
	pop {r3-r7, pc}
_0205385C:
	bl FUN_0200E308
	cmp r0, #0x0
	beq _020538B2
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r1, [r4, r0]
	add sp, #0x18
	add r1, r1, #0x1
	str r1, [r4, r0]
	pop {r3-r7, pc}
_02053872:
	sub r0, r1, #0x4
	ldr r0, [r4, r0]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02053894
	sub r1, #0x24
	mov r7, #0x5f
	add r5, r4, r1
	lsl r7, r7, #0x2
_02053884:
	add r0, r5, #0x0
	bl FUN_02054070
	ldr r0, [r4, r7]
	add r6, r6, #0x1
	add r5, #0x10
	cmp r6, r0
	blt _02053884
_02053894:
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r1, [r4, r0]
	add sp, #0x18
	add r1, r1, #0x1
	str r1, [r4, r0]
	pop {r3-r7, pc}
_020538A2:
	add r1, #0x8
	ldr r0, [r4, r1]
	mov r2, #0x1
	str r2, [r0, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02053D3C
_020538B2:
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020538B8
FUN_020538B8: ; 0x020538B8
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r1, #0x0
	add r0, sp, #0xc
	strh r1, [r0, #0x0]
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	cmp r0, #0x5
	beq _020538D6
	ldr r0, [r4, #0x4]
	bl FUN_0201FDEC
_020538D6:
	mov r1, #0x6
	lsl r1, r1, #0x6
	ldr r0, [r4, r1]
	cmp r0, #0x5
	bls _020538E2
	b _020539EA
_020538E2:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020538EE: ; jump table (using 16-bit offset)
	.short _020538FA - _020538EE - 2; case 0
	.short _02053912 - _020538EE - 2; case 1
	.short _0205396E - _020538EE - 2; case 2
	.short _020539A2 - _020538EE - 2; case 3
	.short _020539C4 - _020538EE - 2; case 4
	.short _020539DA - _020538EE - 2; case 5
_020538FA:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	ldr r0, [r0, #0x38]
	bl FUN_0205537C
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r1, [r4, r0]
	add sp, #0x10
	add r1, r1, #0x1
	str r1, [r4, r0]
	pop {r3-r5, pc}
_02053912:
	mov r0, #0x4
	add r1, sp, #0xc
	mov r2, #0x2
	mov r3, #0x0
	bl BG_LoadPlttData
	mov r0, #0x1
	mov r1, #0x0
	bl GX_EngineBToggleLayers
	mov r0, #0x2
	mov r1, #0x0
	bl GX_EngineBToggleLayers
	mov r1, #0x57
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	mov r2, #0x2
	bl FUN_02053F38
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0x0
	add r2, r1, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	ldr r0, _020539F0 ; =0x0000062F
	bl PlaySE
	mov r0, #0x5f
	mov r1, #0x1
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r1, r0, #0x4
	ldr r1, [r4, r1]
	add r0, r0, #0x4
	add r1, r1, #0x1
	add sp, #0x10
	str r1, [r4, r0]
	pop {r3-r5, pc}
_0205396E:
	add r0, r1, #0x0
	sub r1, #0x18
	sub r0, #0x24
	ldr r1, [r4, r1]
	add r0, r4, r0
	blx r1
	cmp r0, #0x0
	bne _020539EA
	bl FUN_0200E308
	cmp r0, #0x0
	beq _020539EA
	ldr r0, _020539F4 ; =0x00000631
	bl PlaySE
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r1, [r4, r0]
	add sp, #0x10
	add r1, r1, #0x1
	str r1, [r4, r0]
	mov r1, #0xfe
	mvn r1, r1
	add r0, r0, #0x4
	str r1, [r4, r0]
	pop {r3-r5, pc}
_020539A2:
	add r0, r1, #0x4
	ldr r2, [r4, r0]
	add r2, #0x10
	str r2, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0x0
	ble _020539EA
	ldr r0, [r4, r1]
	add r0, r0, #0x1
	str r0, [r4, r1]
	ldr r0, [r4, #0x0]
	mov r1, #0x1
	ldr r0, [r0, #0x38]
	bl FUN_0205537C
	add sp, #0x10
	pop {r3-r5, pc}
_020539C4:
	sub r1, #0x24
	add r0, r4, r1
	bl FUN_02054070
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r1, [r4, r0]
	add sp, #0x10
	add r1, r1, #0x1
	str r1, [r4, r0]
	pop {r3-r5, pc}
_020539DA:
	add r1, #0x8
	ldr r0, [r4, r1]
	mov r2, #0x1
	str r2, [r0, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02053D3C
_020539EA:
	add sp, #0x10
	pop {r3-r5, pc}
	nop
_020539F0: .word 0x0000062F
_020539F4: .word 0x00000631

	thumb_func_start FUN_020539F8
FUN_020539F8: ; 0x020539F8
	push {r4-r5, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	mov r0, #0x6
	add r4, r1, #0x0
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	cmp r0, #0x6
	beq _02053A10
	ldr r0, [r4, #0x4]
	bl FUN_0201FDEC
_02053A10:
	mov r1, #0x6
	lsl r1, r1, #0x6
	ldr r0, [r4, r1]
	cmp r0, #0x6
	bls _02053A1C
	b _02053B30
_02053A1C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02053A28: ; jump table (using 16-bit offset)
	.short _02053A36 - _02053A28 - 2; case 0
	.short _02053A4E - _02053A28 - 2; case 1
	.short _02053A78 - _02053A28 - 2; case 2
	.short _02053AA0 - _02053A28 - 2; case 3
	.short _02053AE2 - _02053A28 - 2; case 4
	.short _02053B00 - _02053A28 - 2; case 5
	.short _02053B16 - _02053A28 - 2; case 6
_02053A36:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	ldr r0, [r0, #0x38]
	bl FUN_0205537C
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r1, [r4, r0]
	add sp, #0xc
	add r1, r1, #0x1
	str r1, [r4, r0]
	pop {r4-r5, pc}
_02053A4E:
	sub r1, #0x24
	add r0, r4, #0x0
	add r1, r4, r1
	mov r2, #0x3
	bl FUN_02053F38
	mov r0, #0x63
	lsl r0, r0, #0x4
	bl PlaySE
	mov r0, #0x5f
	mov r1, #0x1
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r1, r0, #0x4
	ldr r1, [r4, r1]
	add r0, r0, #0x4
	add r1, r1, #0x1
	add sp, #0xc
	str r1, [r4, r0]
	pop {r4-r5, pc}
_02053A78:
	add r0, r1, #0x4
	ldr r2, [r4, r0]
	sub r2, #0x20
	str r2, [r4, r0]
	ldr r1, [r4, r0]
	mov r0, #0xfe
	mvn r0, r0
	cmp r1, r0
	bge _02053B30
	mov r0, #0x1
	mov r1, #0x0
	bl GX_EngineBToggleLayers
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r1, [r4, r0]
	add sp, #0xc
	add r1, r1, #0x1
	str r1, [r4, r0]
	pop {r4-r5, pc}
_02053AA0:
	add r0, r1, #0x0
	sub r1, #0x18
	sub r0, #0x24
	ldr r1, [r4, r1]
	add r0, r4, r0
	blx r1
	add r5, r0, #0x0
	cmp r5, #0x2
	bne _02053AD0
	mov r1, #0x61
	mov r0, #0x0
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r1, #0x6
	str r1, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	mov r1, #0x4
	str r1, [sp, #0x8]
	ldr r3, _02053B34 ; =0x00007FFF
	add r1, r0, #0x0
	add r2, r0, #0x0
	bl FUN_0200E1D0
_02053AD0:
	cmp r5, #0x0
	bne _02053B30
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r1, [r4, r0]
	add sp, #0xc
	add r1, r1, #0x1
	str r1, [r4, r0]
	pop {r4-r5, pc}
_02053AE2:
	bl FUN_0200E308
	cmp r0, #0x0
	beq _02053B30
	mov r0, #0x61
	mov r1, #0x0
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	sub r1, r0, #0x4
	ldr r1, [r4, r1]
	sub r0, r0, #0x4
	add r1, r1, #0x1
	add sp, #0xc
	str r1, [r4, r0]
	pop {r4-r5, pc}
_02053B00:
	sub r1, #0x24
	add r0, r4, r1
	bl FUN_02054070
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r1, [r4, r0]
	add sp, #0xc
	add r1, r1, #0x1
	str r1, [r4, r0]
	pop {r4-r5, pc}
_02053B16:
	mov r0, #0x2
	mov r1, #0x0
	bl GX_EngineBToggleLayers
	mov r0, #0x62
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x1
	str r1, [r0, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02053D3C
_02053B30:
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4
_02053B34: .word 0x00007FFF

	thumb_func_start FUN_02053B38
FUN_02053B38: ; 0x02053B38
	push {r4-r5, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	mov r0, #0x6
	add r4, r1, #0x0
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	cmp r0, #0x6
	beq _02053B50
	ldr r0, [r4, #0x4]
	bl FUN_0201FDEC
_02053B50:
	mov r1, #0x6
	lsl r1, r1, #0x6
	ldr r0, [r4, r1]
	cmp r0, #0x6
	bls _02053B5C
	b _02053C8C
_02053B5C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02053B68: ; jump table (using 16-bit offset)
	.short _02053B76 - _02053B68 - 2; case 0
	.short _02053BB2 - _02053B68 - 2; case 1
	.short _02053BD6 - _02053B68 - 2; case 2
	.short _02053BF2 - _02053B68 - 2; case 3
	.short _02053C22 - _02053B68 - 2; case 4
	.short _02053C66 - _02053B68 - 2; case 5
	.short _02053C7C - _02053B68 - 2; case 6
_02053B76:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	ldr r0, [r0, #0x38]
	bl FUN_0205537C
	mov r1, #0x57
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	mov r2, #0x4
	bl FUN_02053F38
	mov r1, #0x5b
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	mov r2, #0x5
	bl FUN_02053F38
	mov r0, #0x5f
	mov r1, #0x2
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r1, r0, #0x4
	ldr r1, [r4, r1]
	add r0, r0, #0x4
	add r1, r1, #0x1
	add sp, #0xc
	str r1, [r4, r0]
	pop {r4-r5, pc}
_02053BB2:
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	ldr r3, _02053C90 ; =0x00007FFF
	mov r0, #0x0
	add r2, r1, #0x0
	bl FUN_0200E1D0
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r1, [r4, r0]
	add sp, #0xc
	add r1, r1, #0x1
	str r1, [r4, r0]
	pop {r4-r5, pc}
_02053BD6:
	bl FUN_0200E308
	cmp r0, #0x0
	beq _02053C8C
	ldr r0, _02053C94 ; =0x00000632
	bl PlaySE
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r1, [r4, r0]
	add sp, #0xc
	add r1, r1, #0x1
	str r1, [r4, r0]
	pop {r4-r5, pc}
_02053BF2:
	add r0, r1, #0x0
	sub r1, #0x18
	sub r0, #0x24
	ldr r1, [r4, r1]
	add r0, r4, r0
	blx r1
	cmp r0, #0x0
	bne _02053C8C
	ldr r0, [r4, #0x0]
	mov r1, #0x1
	ldr r0, [r0, #0x38]
	bl FUN_0205537C
	mov r0, #0x61
	mov r1, #0x6
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	sub r1, r0, #0x4
	ldr r1, [r4, r1]
	sub r0, r0, #0x4
	add r1, r1, #0x1
	add sp, #0xc
	str r1, [r4, r0]
	pop {r4-r5, pc}
_02053C22:
	add r0, r1, #0x0
	sub r1, #0x8
	sub r0, #0x14
	ldr r1, [r4, r1]
	add r0, r4, r0
	blx r1
	add r5, r0, #0x0
	mov r0, #0x61
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	cmp r1, #0x0
	bgt _02053C50
	bne _02053C54
	sub r0, #0x28
	add r0, r4, r0
	bl FUN_02054070
	mov r0, #0x61
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	sub r1, r1, #0x1
	str r1, [r4, r0]
	b _02053C54
_02053C50:
	sub r1, r1, #0x1
	str r1, [r4, r0]
_02053C54:
	cmp r5, #0x0
	bne _02053C8C
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r1, [r4, r0]
	add sp, #0xc
	add r1, r1, #0x1
	str r1, [r4, r0]
	pop {r4-r5, pc}
_02053C66:
	sub r1, #0x14
	add r0, r4, r1
	bl FUN_02054070
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r1, [r4, r0]
	add sp, #0xc
	add r1, r1, #0x1
	str r1, [r4, r0]
	pop {r4-r5, pc}
_02053C7C:
	add r1, #0x8
	ldr r0, [r4, r1]
	mov r2, #0x1
	str r2, [r0, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02053D3C
_02053C8C:
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4
_02053C90: .word 0x00007FFF
_02053C94: .word 0x00000632

	thumb_func_start FUN_02053C98
FUN_02053C98: ; 0x02053C98
	push {r3-r5, lr}
	add r3, r1, #0x0
	add r4, r0, #0x0
	add r5, r2, #0x0
	cmp r3, #0x3
	bhi _02053CEE
	add r1, r3, r3
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02053CB0: ; jump table (using 16-bit offset)
	.short _02053CB8 - _02053CB0 - 2; case 0
	.short _02053CC6 - _02053CB0 - 2; case 1
	.short _02053CD4 - _02053CB0 - 2; case 2
	.short _02053CE2 - _02053CB0 - 2; case 3
_02053CB8:
	ldr r2, _02053CF8 ; =UNK_020F5C04
	ldr r0, _02053CFC ; =FUN_02053750
	ldrb r2, [r2, r3]
	add r1, r4, #0x0
	bl FUN_02053D0C
	b _02053CEE
_02053CC6:
	ldr r2, _02053CF8 ; =UNK_020F5C04
	ldr r0, _02053D00 ; =FUN_020538B8
	ldrb r2, [r2, r3]
	add r1, r4, #0x0
	bl FUN_02053D0C
	b _02053CEE
_02053CD4:
	ldr r2, _02053CF8 ; =UNK_020F5C04
	ldr r0, _02053D04 ; =FUN_020539F8
	ldrb r2, [r2, r3]
	add r1, r4, #0x0
	bl FUN_02053D0C
	b _02053CEE
_02053CE2:
	ldr r2, _02053CF8 ; =UNK_020F5C04
	ldr r0, _02053D08 ; =FUN_02053B38
	ldrb r2, [r2, r3]
	add r1, r4, #0x0
	bl FUN_02053D0C
_02053CEE:
	mov r1, #0x62
	lsl r1, r1, #0x2
	str r5, [r0, r1]
	str r4, [r0, #0x0]
	pop {r3-r5, pc}
	.balign 4
_02053CF8: .word UNK_020F5C04
_02053CFC: .word FUN_02053750
_02053D00: .word FUN_020538B8
_02053D04: .word FUN_020539F8
_02053D08: .word FUN_02053B38

	thumb_func_start FUN_02053D0C
FUN_02053D0C: ; 0x02053D0C
	push {r4-r6, lr}
	add r5, r1, #0x0
	mov r1, #0x63
	add r6, r2, #0x0
	lsl r1, r1, #0x2
	mov r2, #0x5
	mov r3, #0x4
	bl FUN_020061E8
	bl FUN_0201B6C8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetProfileAddr
	bl PlayerProfile_GetTrainerGender
	add r1, r0, #0x0
	add r0, r4, #0x4
	add r2, r6, #0x0
	bl FUN_02053D50
	add r0, r4, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02053D3C
FUN_02053D3C: ; 0x02053D3C
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x4
	bl FUN_02053D68
	add r0, r4, #0x0
	bl FUN_0200621C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02053D50
FUN_02053D50: ; 0x02053D50
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02053D70
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02053D94
	pop {r4-r6, pc}

	thumb_func_start FUN_02053D68
FUN_02053D68: ; 0x02053D68
	ldr r3, _02053D6C ; =FUN_02053EF0
	bx r3
	.balign 4
_02053D6C: .word FUN_02053EF0

	thumb_func_start FUN_02053D70
FUN_02053D70: ; 0x02053D70
	push {r4, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	mov r0, #0x2
	add r1, #0x30
	mov r2, #0x4
	bl FUN_02008C9C
	str r0, [r4, #0x0]
	mov r0, #0x10
	mov r1, #0x1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #0x1
	bl GX_EngineBToggleLayers
	pop {r4, pc}

	thumb_func_start FUN_02053D94
FUN_02053D94: ; 0x02053D94
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	str r1, [sp, #0x10]
	add r7, r2, #0x0
	mov r6, #0x0
	add r4, r5, #0x0
_02053DA2:
	mov r0, #0x2
	add r1, r6, #0x0
	mov r2, #0x4
	bl FUN_02008DEC
	str r0, [r4, #0x8]
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, #0x4
	blt _02053DA2
	ldr r0, [sp, #0x10]
	add r1, r5, #0x0
	lsl r0, r0, #0x2
	str r0, [sp, #0x14]
	ldr r3, _02053E78 ; =UNK_02105EC8
	ldr r2, [sp, #0x14]
	ldr r0, [r5, #0x8]
	ldr r2, [r3, r2]
	add r1, #0x18
	bl FUN_02053E8C
	str r0, [r5, #0x20]
	ldr r1, [r5, #0x18]
	mov r6, #0x0
	ldr r0, [r1, #0x8]
	cmp r0, #0x0
	ble _02053DF0
	add r4, r6, #0x0
_02053DDA:
	ldr r0, [r1, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_02009630
	ldr r1, [r5, #0x18]
	add r6, r6, #0x1
	ldr r0, [r1, #0x8]
	add r4, r4, #0x4
	cmp r6, r0
	blt _02053DDA
_02053DF0:
	ldr r3, _02053E7C ; =UNK_02105ED0
	ldr r2, [sp, #0x14]
	add r1, r5, #0x0
	ldr r0, [r5, #0xc]
	ldr r2, [r3, r2]
	add r1, #0x1c
	bl FUN_02053E8C
	str r0, [r5, #0x24]
	ldr r1, [r5, #0x1c]
	mov r6, #0x0
	ldr r0, [r1, #0x8]
	cmp r0, #0x0
	ble _02053E24
	add r4, r6, #0x0
_02053E0E:
	ldr r0, [r1, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_02009630
	ldr r1, [r5, #0x1c]
	add r6, r6, #0x1
	ldr r0, [r1, #0x8]
	add r4, r4, #0x4
	cmp r6, r0
	blt _02053E0E
_02053E24:
	ldr r0, [r5, #0x10]
	ldr r2, _02053E80 ; =UNK_02105F48
	mov r1, #0x0
	bl FUN_02053E8C
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x14]
	ldr r2, _02053E84 ; =UNK_02105F64
	mov r1, #0x0
	bl FUN_02053E8C
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x18]
	bl FUN_02009B44
	ldr r0, [r5, #0x1c]
	bl FUN_02009DAC
	ldr r1, _02053E88 ; =UNK_02105F80
	mov r0, #0x4
	bl AllocAndReadFile
	ldr r1, [r5, #0x10]
	add r4, r0, #0x0
	str r1, [sp, #0x0]
	ldr r1, [r5, #0x14]
	str r1, [sp, #0x4]
	mov r1, #0x0
	str r1, [sp, #0x8]
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x8]
	ldr r3, [r5, #0xc]
	mov r1, #0x4
	bl FUN_02008BE0
	str r0, [r5, #0x4]
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	pop {r3-r7, pc}
	nop
_02053E78: .word UNK_02105EC8
_02053E7C: .word UNK_02105ED0
_02053E80: .word UNK_02105F48
_02053E84: .word UNK_02105F64
_02053E88: .word UNK_02105F80

	thumb_func_start FUN_02053E8C
FUN_02053E8C: ; 0x02053E8C
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_0200965C
	add r1, r0, #0x0
	mov r0, #0x4
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	mov r0, #0x4
	add r1, r6, #0x0
	bl AllocAndReadFile
	add r6, r0, #0x0
	add r1, r4, #0x0
	mov r2, #0x4
	bl FUN_02009668
	add r0, r6, #0x0
	bl FreeToHeap
	cmp r5, #0x0
	beq _02053ED0
	add r0, r4, #0x0
	bl FUN_020096CC
	mov r1, #0x4
	bl FUN_02009424
	str r0, [r5, #0x0]
	add r2, r0, #0x0
	b _02053ED2
_02053ED0:
	mov r2, #0x0
_02053ED2:
	add r0, r7, #0x0
	add r1, r4, #0x0
	mov r3, #0x4
	bl FUN_020093A8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020096B4
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02053EF0
FUN_02053EF0: ; 0x02053EF0
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_0201FD58
	mov r0, #0x0
	str r0, [r5, #0x0]
	ldr r0, [r5, #0x4]
	bl FUN_02008C80
	mov r0, #0x0
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x18]
	bl FUN_02009C30
	ldr r0, [r5, #0x1c]
	bl FUN_02009E28
	mov r6, #0x0
	add r4, r5, #0x0
_02053F18:
	ldr r0, [r4, #0x18]
	bl FUN_02009448
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, #0x2
	blt _02053F18
	mov r4, #0x0
_02053F28:
	ldr r0, [r5, #0x8]
	bl FUN_02008E2C
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x4
	blt _02053F28
	pop {r4-r6, pc}

	thumb_func_start FUN_02053F38
FUN_02053F38: ; 0x02053F38
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r4, #0x10
	mov r3, #0x0
_02053F40:
	strb r3, [r5, #0x0]
	add r5, r5, #0x1
	sub r4, r4, #0x1
	bne _02053F40
	cmp r2, #0x5
	bhi _02053FB6
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02053F58: ; jump table (using 16-bit offset)
	.short _02053F64 - _02053F58 - 2; case 0
	.short _02053F72 - _02053F58 - 2; case 1
	.short _02053F80 - _02053F58 - 2; case 2
	.short _02053F8E - _02053F58 - 2; case 3
	.short _02053F9C - _02053F58 - 2; case 4
	.short _02053FAA - _02053F58 - 2; case 5
_02053F64:
	ldr r2, _02053FC0 ; =FUN_02054088
	str r2, [r1, #0x4]
	ldr r2, _02053FC4 ; =FUN_020540C8
	str r2, [r1, #0x8]
	ldr r2, _02053FC8 ; =FUN_020540E8
	str r2, [r1, #0xc]
	b _02053FB6
_02053F72:
	ldr r2, _02053FCC ; =FUN_02054168
	str r2, [r1, #0x4]
	ldr r2, _02053FD0 ; =FUN_020541A4
	str r2, [r1, #0x8]
	ldr r2, _02053FD4 ; =FUN_020541C4
	str r2, [r1, #0xc]
	b _02053FB6
_02053F80:
	ldr r2, _02053FD8 ; =FUN_020541E8
	str r2, [r1, #0x4]
	ldr r2, _02053FDC ; =FUN_02054228
	str r2, [r1, #0x8]
	ldr r2, _02053FE0 ; =FUN_02054248
	str r2, [r1, #0xc]
	b _02053FB6
_02053F8E:
	ldr r2, _02053FE4 ; =FUN_020542A4
	str r2, [r1, #0x4]
	ldr r2, _02053FE8 ; =FUN_020542E8
	str r2, [r1, #0x8]
	ldr r2, _02053FEC ; =FUN_02054308
	str r2, [r1, #0xc]
	b _02053FB6
_02053F9C:
	ldr r2, _02053FF0 ; =FUN_020543D8
	str r2, [r1, #0x4]
	ldr r2, _02053FF4 ; =FUN_0205442C
	str r2, [r1, #0x8]
	ldr r2, _02053FF8 ; =FUN_0205444C
	str r2, [r1, #0xc]
	b _02053FB6
_02053FAA:
	ldr r2, _02053FFC ; =FUN_02054508
	str r2, [r1, #0x4]
	ldr r2, _02054000 ; =FUN_0205454C
	str r2, [r1, #0x8]
	ldr r2, _02054004 ; =FUN_0205456C
	str r2, [r1, #0xc]
_02053FB6:
	ldr r2, [r1, #0x4]
	add r0, r0, #0x4
	blx r2
	pop {r3-r5, pc}
	nop
_02053FC0: .word FUN_02054088
_02053FC4: .word FUN_020540C8
_02053FC8: .word FUN_020540E8
_02053FCC: .word FUN_02054168
_02053FD0: .word FUN_020541A4
_02053FD4: .word FUN_020541C4
_02053FD8: .word FUN_020541E8
_02053FDC: .word FUN_02054228
_02053FE0: .word FUN_02054248
_02053FE4: .word FUN_020542A4
_02053FE8: .word FUN_020542E8
_02053FEC: .word FUN_02054308
_02053FF0: .word FUN_020543D8
_02053FF4: .word FUN_0205442C
_02053FF8: .word FUN_0205444C
_02053FFC: .word FUN_02054508
_02054000: .word FUN_0205454C
_02054004: .word FUN_0205456C

	thumb_func_start FUN_02054008
FUN_02054008: ; 0x02054008
	push {r3-r7, lr}
	sub sp, #0x30
	add r5, r0, #0x0
	add r7, sp, #0x0
	add r6, r3, #0x0
	mov r0, #0x0
	add r4, r1, #0x0
	add r3, r7, #0x0
	add r1, r0, #0x0
	stmia r3!, {r0-r1}
	stmia r3!, {r0-r1}
	stmia r3!, {r0-r1}
	stmia r3!, {r0-r1}
	stmia r3!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	add r3, sp, #0x8
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x4]
	ldr r1, [r0, #0x0]
	mov r0, #0x24
	mul r0, r4
	add r0, r1, r0
	str r0, [sp, #0x4]
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	add r2, sp, #0x14
	str r0, [r3, #0x0]
	ldr r3, _0205406C ; =UNK_020F5C08
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldr r0, [sp, #0x48]
	str r6, [sp, #0x24]
	str r0, [sp, #0x28]
	mov r0, #0x4
	str r0, [sp, #0x2c]
	add r0, r7, #0x0
	bl FUN_0201FE94
	add r4, r0, #0x0
	bne _02054064
	bl GF_AssertFail
_02054064:
	add r0, r4, #0x0
	add sp, #0x30
	pop {r3-r7, pc}
	nop
_0205406C: .word UNK_020F5C08

	thumb_func_start FUN_02054070
FUN_02054070: ; 0x02054070
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x8]
	blx r1
	mov r1, #0x10
	mov r0, #0x0
_0205407C:
	strb r0, [r4, #0x0]
	add r4, r4, #0x1
	sub r1, r1, #0x1
	bne _0205407C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02054088
FUN_02054088: ; 0x02054088
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0x4
	mov r1, #0x14
	bl AllocFromHeap
	str r0, [r5, #0x0]
	mov r2, #0x14
	mov r1, #0x0
_0205409C:
	strb r1, [r0, #0x0]
	add r0, r0, #0x1
	sub r2, r2, #0x1
	bne _0205409C
	ldr r5, [r5, #0x0]
	mov r0, #0x7
	lsl r0, r0, #0x10
	str r0, [r5, #0x0]
	mov r0, #0x45
	lsl r0, r0, #0xc
	str r0, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r2, r5, #0x0
	add r3, r1, #0x0
	bl FUN_02054008
	str r0, [r5, #0xc]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020540C8
FUN_020540C8: ; 0x020540C8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020540E4
	ldr r0, [r0, #0xc]
	bl FUN_0201FFC8
	ldr r1, [r4, #0x0]
	mov r0, #0x4
	bl FreeToHeapExplicit
	mov r0, #0x0
	str r0, [r4, #0x0]
_020540E4:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020540E8
FUN_020540E8: ; 0x020540E8
	push {r3-r6, lr}
	sub sp, #0xc
	ldr r4, [r0, #0x0]
	mov r2, #0x2
	ldr r0, [r4, #0x10]
	lsl r2, r2, #0xe
	cmp r0, r2
	bgt _0205415E
	add r6, r4, #0x0
	ldmia r6!, {r0-r1}
	add r5, sp, #0x0
	add r3, r5, #0x0
	stmia r5!, {r0-r1}
	ldr r0, [r6, #0x0]
	lsr r2, r2, #0x4
	str r0, [r5, #0x0]
	ldr r0, [r4, #0x10]
	ldr r1, [sp, #0x4]
	asr r0, r0, #0x4
	lsl r5, r0, #0x2
	ldr r0, _02054164 ; =FX_SinCosTable_
	ldrsh r5, [r0, r5]
	asr r0, r5, #0x1f
	lsr r6, r5, #0x10
	lsl r0, r0, #0x10
	orr r0, r6
	lsl r6, r5, #0x10
	mov r5, #0x0
	add r2, r6, r2
	adc r0, r5
	lsl r0, r0, #0x14
	lsr r2, r2, #0xc
	orr r2, r0
	sub r0, r1, r2
	str r0, [sp, #0x4]
	ldr r0, [r4, #0xc]
	add r1, r3, #0x0
	bl FUN_02020044
	mov r1, #0x2
	ldr r0, [r4, #0x10]
	lsl r1, r1, #0xa
	add r0, r0, r1
	str r0, [r4, #0x10]
	ldr r0, [r4, #0xc]
	lsl r1, r1, #0x1
	bl FUN_020201E4
	mov r0, #0x2
	ldr r1, [r4, #0x10]
	lsl r0, r0, #0xe
	cmp r1, r0
	bne _02054158
	add sp, #0xc
	mov r0, #0x2
	pop {r3-r6, pc}
_02054158:
	add sp, #0xc
	mov r0, #0x1
	pop {r3-r6, pc}
_0205415E:
	mov r0, #0x0
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4
_02054164: .word FX_SinCosTable_

	thumb_func_start FUN_02054168
FUN_02054168: ; 0x02054168
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0x4
	mov r1, #0x14
	bl AllocFromHeap
	str r0, [r5, #0x0]
	mov r2, #0x14
	mov r1, #0x0
_0205417C:
	strb r1, [r0, #0x0]
	add r0, r0, #0x1
	sub r2, r2, #0x1
	bne _0205417C
	ldr r5, [r5, #0x0]
	mov r0, #0x7
	lsl r0, r0, #0x10
	str r0, [r5, #0x0]
	mov r0, #0x6
	lsl r0, r0, #0x10
	mov r1, #0x1
	str r0, [r5, #0x4]
	add r0, r4, #0x0
	add r2, r5, #0x0
	add r3, r1, #0x0
	str r1, [sp, #0x0]
	bl FUN_02054008
	str r0, [r5, #0xc]
	pop {r3-r5, pc}

	thumb_func_start FUN_020541A4
FUN_020541A4: ; 0x020541A4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020541C0
	ldr r0, [r0, #0xc]
	bl FUN_0201FFC8
	ldr r1, [r4, #0x0]
	mov r0, #0x4
	bl FreeToHeapExplicit
	mov r0, #0x0
	str r0, [r4, #0x0]
_020541C0:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020541C4
FUN_020541C4: ; 0x020541C4
	push {r4, lr}
	ldr r4, [r0, #0x0]
	ldr r0, [r4, #0x10]
	cmp r0, #0x7
	bge _020541E2
	mov r1, #0x1
	ldr r0, [r4, #0xc]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	ldr r0, [r4, #0x10]
	add r0, r0, #0x1
	str r0, [r4, #0x10]
	mov r0, #0x1
	pop {r4, pc}
_020541E2:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020541E8
FUN_020541E8: ; 0x020541E8
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0x4
	mov r1, #0x14
	bl AllocFromHeap
	str r0, [r5, #0x0]
	mov r2, #0x14
	mov r1, #0x0
_020541FC:
	strb r1, [r0, #0x0]
	add r0, r0, #0x1
	sub r2, r2, #0x1
	bne _020541FC
	ldr r5, [r5, #0x0]
	mov r0, #0x7
	lsl r0, r0, #0x10
	str r0, [r5, #0x0]
	mov r0, #0x3
	lsl r0, r0, #0x12
	str r0, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r2, r5, #0x0
	add r3, r1, #0x0
	bl FUN_02054008
	str r0, [r5, #0xc]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02054228
FUN_02054228: ; 0x02054228
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02054244
	ldr r0, [r0, #0xc]
	bl FUN_0201FFC8
	ldr r1, [r4, #0x0]
	mov r0, #0x4
	bl FreeToHeapExplicit
	mov r0, #0x0
	str r0, [r4, #0x0]
_02054244:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02054248
FUN_02054248: ; 0x02054248
	push {r4, lr}
	ldr r4, [r0, #0x0]
	mov r0, #0x2
	ldr r1, [r4, #0x4]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [r4, #0x4]
	ldr r0, [r4, #0xc]
	add r1, r4, #0x0
	bl FUN_02020044
	mov r1, #0x1
	ldr r0, [r4, #0xc]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	ldr r0, [r4, #0x10]
	ldr r1, [r4, #0x4]
	cmp r0, #0x0
	bne _02054284
	mov r0, #0x6
	lsl r0, r0, #0x12
	cmp r1, r0
	blt _0205429A
	ldr r0, _020542A0 ; =0xFFFE0000
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x10]
	add r0, r0, #0x1
	str r0, [r4, #0x10]
	b _0205429A
_02054284:
	mov r0, #0x45
	lsl r0, r0, #0xc
	cmp r1, r0
	blt _0205429A
	str r0, [r4, #0x4]
	ldr r0, [r4, #0xc]
	add r1, r4, #0x0
	bl FUN_02020044
	mov r0, #0x0
	pop {r4, pc}
_0205429A:
	mov r0, #0x1
	pop {r4, pc}
	nop
_020542A0: .word 0xFFFE0000

	thumb_func_start FUN_020542A4
FUN_020542A4: ; 0x020542A4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0x4
	mov r1, #0x18
	bl AllocFromHeap
	str r0, [r5, #0x0]
	mov r2, #0x18
	mov r1, #0x0
_020542B8:
	strb r1, [r0, #0x0]
	add r0, r0, #0x1
	sub r2, r2, #0x1
	bne _020542B8
	ldr r5, [r5, #0x0]
	mov r0, #0x7
	lsl r0, r0, #0x10
	str r0, [r5, #0x0]
	mov r0, #0x45
	lsl r0, r0, #0xc
	str r0, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r2, r5, #0x0
	add r3, r1, #0x0
	bl FUN_02054008
	mov r1, #0x1
	str r0, [r5, #0xc]
	bl FUN_02020130
	pop {r3-r5, pc}

	thumb_func_start FUN_020542E8
FUN_020542E8: ; 0x020542E8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02054304
	ldr r0, [r0, #0xc]
	bl FUN_0201FFC8
	ldr r1, [r4, #0x0]
	mov r0, #0x4
	bl FreeToHeapExplicit
	mov r0, #0x0
	str r0, [r4, #0x0]
_02054304:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02054308
FUN_02054308: ; 0x02054308
	push {r3-r5, lr}
	ldr r4, [r0, #0x0]
	mov r5, #0x1
	ldr r0, [r4, #0x10]
	cmp r0, #0x4
	bhi _020543CC
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02054320: ; jump table (using 16-bit offset)
	.short _0205432A - _02054320 - 2; case 0
	.short _02054348 - _02054320 - 2; case 1
	.short _02054376 - _02054320 - 2; case 2
	.short _020543A2 - _02054320 - 2; case 3
	.short _020543CA - _02054320 - 2; case 4
_0205432A:
	ldr r1, [r4, #0x14]
	ldr r0, _020543D0 ; =0x00000333
	add r1, r1, r0
	str r1, [r4, #0x14]
	ldr r0, [r4, #0xc]
	bl FUN_020201E4
	ldr r1, [r4, #0x14]
	lsl r0, r5, #0xd
	cmp r1, r0
	blt _020543CC
	ldr r0, [r4, #0x10]
	add r0, r0, #0x1
	str r0, [r4, #0x10]
	b _020543CC
_02054348:
	ldr r1, [r4, #0x4]
	ldr r0, _020543D4 ; =0xFFFE0000
	cmp r1, r0
	ble _02054368
	lsl r0, r5, #0xf
	sub r0, r1, r0
	str r0, [r4, #0x4]
	ldr r0, [r4, #0xc]
	add r1, r4, #0x0
	bl FUN_02020044
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x14]
	bl FUN_020201E4
	b _020543CC
_02054368:
	mov r0, #0x6
	lsl r0, r0, #0x12
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x10]
	add r0, r0, #0x1
	str r0, [r4, #0x10]
	b _020543CC
_02054376:
	ldr r1, [r4, #0x4]
	lsl r0, r5, #0xf
	sub r0, r1, r0
	str r0, [r4, #0x4]
	ldr r0, [r4, #0xc]
	add r1, r4, #0x0
	bl FUN_02020044
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x14]
	bl FUN_020201E4
	mov r0, #0x4b
	ldr r1, [r4, #0x4]
	lsl r0, r0, #0xe
	cmp r1, r0
	bge _020543CC
	ldr r0, [r4, #0x10]
	mov r5, #0x2
	add r0, r0, #0x1
	str r0, [r4, #0x10]
	b _020543CC
_020543A2:
	mov r1, #0x3
	ldr r2, [r4, #0x4]
	lsl r1, r1, #0x12
	cmp r2, r1
	ble _020543C4
	lsl r0, r5, #0xf
	sub r0, r2, r0
	str r0, [r4, #0x4]
	ldr r0, [r4, #0xc]
	add r1, r4, #0x0
	bl FUN_02020044
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x14]
	bl FUN_020201E4
	b _020543CC
_020543C4:
	add r0, r0, #0x1
	str r0, [r4, #0x10]
	b _020543CC
_020543CA:
	mov r5, #0x0
_020543CC:
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4
_020543D0: .word 0x00000333
_020543D4: .word 0xFFFE0000

	thumb_func_start FUN_020543D8
FUN_020543D8: ; 0x020543D8
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0x4
	mov r1, #0x18
	bl AllocFromHeap
	str r0, [r5, #0x0]
	mov r2, #0x18
	mov r1, #0x0
_020543EC:
	strb r1, [r0, #0x0]
	add r0, r0, #0x1
	sub r2, r2, #0x1
	bne _020543EC
	ldr r5, [r5, #0x0]
	mov r0, #0x7
	lsl r0, r0, #0x10
	str r0, [r5, #0x0]
	mov r0, #0x45
	lsl r0, r0, #0xc
	str r0, [r5, #0x4]
	mov r0, #0x1
	mov r1, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r2, r5, #0x0
	add r3, r1, #0x0
	bl FUN_02054008
	mov r1, #0x1
	str r0, [r5, #0xc]
	bl FUN_02020130
	mov r0, #0x2
	lsl r0, r0, #0xc
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r1, #0x0
	bl FUN_020200A0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205442C
FUN_0205442C: ; 0x0205442C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02054448
	ldr r0, [r0, #0xc]
	bl FUN_0201FFC8
	ldr r1, [r4, #0x0]
	mov r0, #0x4
	bl FreeToHeapExplicit
	mov r0, #0x0
	str r0, [r4, #0x0]
_02054448:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205444C
FUN_0205444C: ; 0x0205444C
	push {r4-r7, lr}
	sub sp, #0xc
	ldr r4, [r0, #0x0]
	mov r5, #0x1
	ldr r0, [r4, #0x10]
	cmp r0, #0x3
	bhi _020544F8
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02054466: ; jump table (using 16-bit offset)
	.short _0205446E - _02054466 - 2; case 0
	.short _0205447E - _02054466 - 2; case 1
	.short _020544DA - _02054466 - 2; case 2
	.short _020544F6 - _02054466 - 2; case 3
_0205446E:
	ldr r0, [r4, #0xc]
	add r1, r5, #0x0
	bl FUN_020200A0
	ldr r0, [r4, #0x10]
	add r0, r0, #0x1
	str r0, [r4, #0x10]
	b _020544F8
_0205447E:
	ldr r2, [r4, #0x14]
	lsl r1, r5, #0xf
	cmp r2, r1
	bgt _020544D4
	add r6, r4, #0x0
	ldmia r6!, {r0-r1}
	add r3, sp, #0x0
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r6, #0x0]
	mov r7, #0x0
	str r0, [r3, #0x0]
	ldr r0, [r4, #0x14]
	ldr r6, [sp, #0x4]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02054500 ; =FX_SinCosTable_
	ldrsh r0, [r0, r1]
	asr r3, r0, #0x1f
	lsr r1, r0, #0xf
	lsl r3, r3, #0x11
	orr r3, r1
	lsl r1, r0, #0x11
	lsl r0, r5, #0xb
	add r0, r1, r0
	adc r3, r7
	lsl r1, r3, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	sub r0, r6, r0
	str r0, [sp, #0x4]
	ldr r0, [r4, #0xc]
	add r1, r2, #0x0
	bl FUN_02020044
	ldr r0, [r4, #0x14]
	lsl r1, r5, #0xc
	add r0, r0, r1
	str r0, [r4, #0x14]
	ldr r0, [r4, #0xc]
	bl FUN_020201E4
	b _020544F8
_020544D4:
	add r0, r0, #0x1
	str r0, [r4, #0x10]
	b _020544F8
_020544DA:
	ldr r1, [r4, #0x14]
	ldr r0, _02054504 ; =0x00000666
	sub r1, r1, r0
	str r1, [r4, #0x14]
	ldr r0, [r4, #0xc]
	bl FUN_020201E4
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	bgt _020544F8
	ldr r0, [r4, #0x10]
	add r0, r0, #0x1
	str r0, [r4, #0x10]
	b _020544F8
_020544F6:
	mov r5, #0x0
_020544F8:
	add r0, r5, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02054500: .word FX_SinCosTable_
_02054504: .word 0x00000666

	thumb_func_start FUN_02054508
FUN_02054508: ; 0x02054508
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0x4
	mov r1, #0x14
	bl AllocFromHeap
	str r0, [r5, #0x0]
	mov r2, #0x14
	mov r1, #0x0
_0205451C:
	strb r1, [r0, #0x0]
	add r0, r0, #0x1
	sub r2, r2, #0x1
	bne _0205451C
	ldr r5, [r5, #0x0]
	mov r0, #0x7
	lsl r0, r0, #0x10
	str r0, [r5, #0x0]
	mov r0, #0x6
	lsl r0, r0, #0x10
	mov r1, #0x1
	str r0, [r5, #0x4]
	add r0, r4, #0x0
	add r2, r5, #0x0
	add r3, r1, #0x0
	str r1, [sp, #0x0]
	bl FUN_02054008
	mov r1, #0x1
	str r0, [r5, #0xc]
	bl FUN_02020130
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0205454C
FUN_0205454C: ; 0x0205454C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02054568
	ldr r0, [r0, #0xc]
	bl FUN_0201FFC8
	ldr r1, [r4, #0x0]
	mov r0, #0x4
	bl FreeToHeapExplicit
	mov r0, #0x0
	str r0, [r4, #0x0]
_02054568:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205456C
FUN_0205456C: ; 0x0205456C
	push {r4, lr}
	ldr r4, [r0, #0x0]
	ldr r0, [r4, #0x10]
	cmp r0, #0x8
	bge _0205458A
	mov r1, #0x1
	ldr r0, [r4, #0xc]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	ldr r0, [r4, #0x10]
	add r0, r0, #0x1
	str r0, [r4, #0x10]
	mov r0, #0x1
	pop {r4, pc}
_0205458A:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
