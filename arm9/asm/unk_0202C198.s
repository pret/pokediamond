	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.balign 4, 0
	.global UNK_02105D54
UNK_02105D54: ; 0x02105D54
	.asciz "DP"

	.section .bss

	.global UNK_021C59D8
UNK_021C59D8: ; 0x021C59D8
	.space 0x8

	.text

	thumb_func_start FUN_0202C198
FUN_0202C198: ; 0x0202C198
	ldr r1, _0202C1A4 ; =UNK_021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202C1A8 ; =0x00001310
	str r0, [r2, r1]
	bx lr
	nop
_0202C1A4: .word UNK_021C59D8
_0202C1A8: .word 0x00001310

	thumb_func_start FUN_0202C1AC
FUN_0202C1AC: ; 0x0202C1AC
	ldr r1, _0202C1C0 ; =UNK_021C59D8
	ldr r3, [r1, #0x4]
	ldr r1, _0202C1C4 ; =0x00001310
	ldr r2, [r3, r1]
	sub r2, #0x9
	cmp r2, #0x1
	bls _0202C1BE
	add r1, #0x20
	str r0, [r3, r1]
_0202C1BE:
	bx lr
	.balign 4
_0202C1C0: .word UNK_021C59D8
_0202C1C4: .word 0x00001310

	thumb_func_start FUN_0202C1C8
FUN_0202C1C8: ; 0x0202C1C8
	push {r3, lr}
	mov r0, #0x3
	bl FUN_0202C198
	ldr r1, _0202C1F0 ; =UNK_021C59D8
	ldr r0, _0202C1F4 ; =FUN_0202C1F8
	ldr r1, [r1, #0x4]
	bl WM_SetParentParameter
	cmp r0, #0x2
	beq _0202C1EC
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x0
	pop {r3, pc}
_0202C1EC:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202C1F0: .word UNK_021C59D8
_0202C1F4: .word FUN_0202C1F8

	thumb_func_start FUN_0202C1F8
FUN_0202C1F8: ; 0x0202C1F8
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202C20C
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r3, pc}
_0202C20C:
	bl FUN_0202C21C
	cmp r0, #0x0
	bne _0202C21A
	mov r0, #0x9
	bl FUN_0202C198
_0202C21A:
	pop {r3, pc}

	thumb_func_start FUN_0202C21C
FUN_0202C21C: ; 0x0202C21C
	push {r4, lr}
	ldr r0, _0202C278 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C27C ; =0x00001310
	ldr r0, [r1, r0]
	sub r0, r0, #0x4
	cmp r0, #0x2
	bhi _0202C230
	mov r0, #0x1
	pop {r4, pc}
_0202C230:
	bl WMi_GetStatusAddress
	add r4, r0, #0x0
	mov r0, #0x66
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x4
	bl DC_InvalidateRange
	mov r0, #0x66
	mov r1, #0x0
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, r4, r0
	mov r1, #0x4
	bl DC_FlushRange
	ldr r0, _0202C280 ; =FUN_0202C288
	bl WM_StartParent
	cmp r0, #0x2
	beq _0202C264
	bl FUN_0202C1AC
	mov r0, #0x0
	pop {r4, pc}
_0202C264:
	ldr r2, _0202C278 ; =UNK_021C59D8
	ldr r1, _0202C284 ; =0x0000132C
	ldr r0, [r2, #0x4]
	mov r3, #0x0
	strh r3, [r0, r1]
	ldr r2, [r2, #0x4]
	mov r0, #0x1
	add r1, r1, #0x2
	strh r0, [r2, r1]
	pop {r4, pc}
	.balign 4
_0202C278: .word UNK_021C59D8
_0202C27C: .word 0x00001310
_0202C280: .word FUN_0202C288
_0202C284: .word 0x0000132C

	thumb_func_start FUN_0202C288
FUN_0202C288: ; 0x0202C288
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldrh r0, [r5, #0x10]
	mov r1, #0x1
	lsl r1, r0
	lsl r0, r1, #0x10
	lsr r4, r0, #0x10
	ldrh r0, [r5, #0x2]
	cmp r0, #0x0
	beq _0202C2A8
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4-r6, pc}
_0202C2A8:
	ldrh r0, [r5, #0x8]
	cmp r0, #0x7
	bgt _0202C2C0
	bge _0202C2DA
	cmp r0, #0x2
	bgt _0202C378
	cmp r0, #0x0
	blt _0202C378
	beq _0202C36A
	cmp r0, #0x2
	beq _0202C2CC
	pop {r4-r6, pc}
_0202C2C0:
	cmp r0, #0x9
	bgt _0202C2C8
	beq _0202C34C
	pop {r4-r6, pc}
_0202C2C8:
	cmp r0, #0x1a
	pop {r4-r6, pc}
_0202C2CC:
	ldr r0, _0202C37C ; =UNK_021C59D8
	ldr r2, [r0, #0x4]
	ldr r0, _0202C380 ; =0x00001345
	ldrb r1, [r2, r0]
	add r1, r1, #0x1
	strb r1, [r2, r0]
	pop {r4-r6, pc}
_0202C2DA:
	ldr r0, _0202C37C ; =UNK_021C59D8
	ldr r2, [r0, #0x4]
	ldr r0, _0202C384 ; =0x00001343
	ldrb r1, [r2, r0]
	cmp r1, #0x1
	beq _0202C318
	sub r0, r0, #0x1
	ldrb r0, [r2, r0]
	cmp r0, #0x1
	beq _0202C318
	bl FUN_0202CBA0
	ldr r1, _0202C37C ; =UNK_021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202C388 ; =0x00001334
	ldrb r1, [r2, r1]
	cmp r0, r1
	bge _0202C318
	bl FUN_02033534
	ldrb r1, [r5, #0x14]
	cmp r1, r0
	bne _0202C318
	add r1, r5, #0x0
	ldr r0, _0202C38C ; =UNK_02105D54
	add r1, #0x15
	mov r2, #0x3
	bl memcmp
	cmp r0, #0x0
	beq _0202C330
_0202C318:
	ldrh r1, [r5, #0x10]
	mov r0, #0x0
	bl WM_Disconnect
	cmp r0, #0x2
	beq _0202C378
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4-r6, pc}
_0202C330:
	ldr r1, _0202C37C ; =UNK_021C59D8
	ldr r0, _0202C390 ; =0x0000132E
	ldr r3, [r1, #0x4]
	ldrh r2, [r3, r0]
	orr r2, r4
	strh r2, [r3, r0]
	ldr r1, [r1, #0x4]
	sub r0, r0, #0x6
	ldr r1, [r1, r0]
	cmp r1, #0x0
	beq _0202C378
	ldrh r0, [r5, #0x10]
	blx r1
	pop {r4-r6, pc}
_0202C34C:
	ldr r2, _0202C37C ; =UNK_021C59D8
	ldr r1, _0202C390 ; =0x0000132E
	ldr r0, [r2, #0x4]
	mvn r3, r4
	ldrh r6, [r0, r1]
	and r3, r6
	strh r3, [r0, r1]
	ldr r0, [r2, #0x4]
	sub r1, #0xa
	ldr r1, [r0, r1]
	cmp r1, #0x0
	beq _0202C378
	ldrh r0, [r5, #0x10]
	blx r1
	pop {r4-r6, pc}
_0202C36A:
	bl FUN_0202C394
	cmp r0, #0x0
	bne _0202C378
	mov r0, #0x9
	bl FUN_0202C198
_0202C378:
	pop {r4-r6, pc}
	nop
_0202C37C: .word UNK_021C59D8
_0202C380: .word 0x00001345
_0202C384: .word 0x00001343
_0202C388: .word 0x00001334
_0202C38C: .word UNK_02105D54
_0202C390: .word 0x0000132E

	thumb_func_start FUN_0202C394
FUN_0202C394: ; 0x0202C394
	push {r4, lr}
	sub sp, #0x8
	ldr r0, _0202C3F0 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C3F4 ; =0x00001310
	ldr r0, [r1, r0]
	sub r0, r0, #0x4
	cmp r0, #0x2
	bhi _0202C3AC
	add sp, #0x8
	mov r0, #0x1
	pop {r4, pc}
_0202C3AC:
	mov r0, #0x4
	bl FUN_0202C198
	ldr r0, _0202C3F0 ; =UNK_021C59D8
	ldr r2, _0202C3F8 ; =0x00001304
	ldr r4, [r0, #0x4]
	ldr r3, _0202C3FC ; =0x00001020
	ldr r0, [r4, r2]
	add r2, r2, #0x4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r2, [r4, r2]
	add r1, r4, r3
	lsl r2, r2, #0x10
	sub r3, #0xe0
	ldr r0, _0202C400 ; =FUN_0202C404
	lsr r2, r2, #0x10
	add r3, r4, r3
	bl WM_StartMP
	cmp r0, #0x2
	beq _0202C3E8
	bl FUN_0202C1AC
	add sp, #0x8
	mov r0, #0x0
	pop {r4, pc}
_0202C3E8:
	mov r0, #0x1
	add sp, #0x8
	pop {r4, pc}
	nop
_0202C3F0: .word UNK_021C59D8
_0202C3F4: .word 0x00001310
_0202C3F8: .word 0x00001304
_0202C3FC: .word 0x00001020
_0202C400: .word FUN_0202C404

	thumb_func_start FUN_0202C404
FUN_0202C404: ; 0x0202C404
	push {r3, lr}
	ldrh r1, [r0, #0x2]
	cmp r1, #0x0
	beq _0202C41A
	add r0, r1, #0x0
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r3, pc}
_0202C41A:
	ldrh r0, [r0, #0x4]
	sub r0, #0xa
	cmp r0, #0x3
	bhi _0202C454
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202C42E: ; jump table (using 16-bit offset)
	.short _0202C436 - _0202C42E - 2; case 0
	.short _0202C454 - _0202C42E - 2; case 1
	.short _0202C454 - _0202C42E - 2; case 2
	.short _0202C454 - _0202C42E - 2; case 3
_0202C436:
	ldr r0, _0202C458 ; =UNK_021C59D8
	ldr r2, [r0, #0x4]
	ldr r0, _0202C45C ; =0x00001314
	ldr r1, [r2, r0]
	cmp r1, #0x2
	bne _0202C44E
	sub r0, r0, #0x4
	ldr r0, [r2, r0]
	cmp r0, #0x4
	beq _0202C44E
	cmp r0, #0x6
	beq _0202C454
_0202C44E:
	mov r0, #0x4
	bl FUN_0202C198
_0202C454:
	pop {r3, pc}
	nop
_0202C458: .word UNK_021C59D8
_0202C45C: .word 0x00001314

	thumb_func_start FUN_0202C460
FUN_0202C460: ; 0x0202C460
	push {r3, lr}
	mov r0, #0x3
	bl FUN_0202C198
	ldr r0, _0202C480 ; =FUN_0202C484
	bl WM_EndMP
	cmp r0, #0x2
	beq _0202C47A
	bl FUN_0202C1AC
	mov r0, #0x0
	pop {r3, pc}
_0202C47A:
	mov r0, #0x1
	pop {r3, pc}
	nop
_0202C480: .word FUN_0202C484

	thumb_func_start FUN_0202C484
FUN_0202C484: ; 0x0202C484
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202C496
	bl FUN_0202C1AC
	bl FUN_0202D0D8
	pop {r3, pc}
_0202C496:
	bl FUN_0202C4A4
	cmp r0, #0x0
	bne _0202C4A2
	bl FUN_0202D0D8
_0202C4A2:
	pop {r3, pc}

	thumb_func_start FUN_0202C4A4
FUN_0202C4A4: ; 0x0202C4A4
	push {r3, lr}
	ldr r0, _0202C4BC ; =FUN_0202C4C0
	bl WM_EndParent
	cmp r0, #0x2
	beq _0202C4B8
	bl FUN_0202C1AC
	mov r0, #0x0
	pop {r3, pc}
_0202C4B8:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202C4BC: .word FUN_0202C4C0

	thumb_func_start FUN_0202C4C0
FUN_0202C4C0: ; 0x0202C4C0
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202C4CE
	bl FUN_0202C1AC
	pop {r3, pc}
_0202C4CE:
	mov r0, #0x1
	bl FUN_0202C198
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202C4D8
FUN_0202C4D8: ; 0x0202C4D8
	push {r3-r7, lr}
	add r6, r2, #0x0
	ldr r2, _0202C564 ; =UNK_021C59D8
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r3, #0x2
	ldr r0, [r2, #0x4]
	ldr r1, _0202C568 ; =0x00001308
	lsl r3, r3, #0x8
	str r3, [r0, r1]
	ldr r2, [r2, #0x4]
	mov r0, #0x40
	sub r1, r1, #0x4
	str r0, [r2, r1]
	mov r0, #0x2
	bl FUN_0202C198
	ldr r1, _0202C564 ; =UNK_021C59D8
	ldr r0, _0202C56C ; =0x00001256
	ldr r3, [r1, #0x4]
	mov r2, #0x1
	strh r2, [r3, r0]
	add r7, r0, #0x0
	ldrh r3, [r4, #0x4]
	ldr r2, [r1, #0x4]
	add r7, #0x96
	strh r3, [r2, r7]
	add r7, r0, #0x0
	ldrh r3, [r4, #0x2]
	ldr r2, [r1, #0x4]
	add r7, #0x94
	strh r3, [r2, r7]
	add r2, r0, #0x0
	ldrh r4, [r4, #0x0]
	ldr r3, [r1, #0x4]
	add r2, #0x92
	strh r4, [r3, r2]
	add r2, r0, #0x0
	ldr r3, [r1, #0x4]
	add r2, #0xbe
	str r5, [r3, r2]
	add r3, r0, #0x0
	ldr r4, [r1, #0x4]
	mov r2, #0x0
	add r3, #0xaa
	str r2, [r4, r3]
	add r3, r0, #0x0
	ldr r4, [r1, #0x4]
	add r3, #0xb6
	strh r6, [r4, r3]
	add r3, r0, #0x0
	ldr r4, [r1, #0x4]
	add r3, #0x8e
	strh r2, [r4, r3]
	ldr r2, [r1, #0x4]
	add r0, #0xb8
	mov r1, #0x1
	strh r1, [r2, r0]
	bl FUN_0202C5D8
	cmp r0, #0x0
	bne _0202C55E
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x0
	pop {r3-r7, pc}
_0202C55E:
	mov r0, #0x1
	pop {r3-r7, pc}
	nop
_0202C564: .word UNK_021C59D8
_0202C568: .word 0x00001308
_0202C56C: .word 0x00001256

	thumb_func_start FUN_0202C570
FUN_0202C570: ; 0x0202C570
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r0, #0x2
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_0202C198
	ldr r1, _0202C5D4 ; =UNK_021C59D8
	mov r0, #0x13
	ldr r2, [r1, #0x4]
	lsl r0, r0, #0x8
	str r5, [r2, r0]
	add r2, r0, #0x0
	ldr r3, [r1, #0x4]
	add r2, #0xc
	strh r6, [r3, r2]
	add r3, r0, #0x0
	ldr r5, [r1, #0x4]
	mov r2, #0x0
	sub r3, #0x1c
	strh r2, [r5, r3]
	add r3, r0, #0x0
	ldr r5, [r1, #0x4]
	add r3, #0xe
	strh r2, [r5, r3]
	add r2, r0, #0x0
	ldrh r5, [r4, #0x4]
	ldr r3, [r1, #0x4]
	sub r2, #0x14
	strh r5, [r3, r2]
	add r2, r0, #0x0
	ldrh r5, [r4, #0x2]
	ldr r3, [r1, #0x4]
	sub r2, #0x16
	strh r5, [r3, r2]
	ldrh r2, [r4, #0x0]
	ldr r1, [r1, #0x4]
	sub r0, #0x18
	strh r2, [r1, r0]
	bl FUN_0202C5D8
	cmp r0, #0x0
	bne _0202C5D0
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x0
	pop {r4-r6, pc}
_0202C5D0:
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0202C5D4: .word UNK_021C59D8

	thumb_func_start FUN_0202C5D8
FUN_0202C5D8: ; 0x0202C5D8
	push {r3-r7, lr}
	bl WM_GetAllowedChannel
	add r5, r0, #0x0
	mov r0, #0x2
	lsl r0, r0, #0xe
	cmp r5, r0
	bne _0202C5F8
	mov r0, #0x3
	bl FUN_0202C1AC
	mov r0, #0x1
	bl FUN_020336A0
	mov r0, #0x0
	pop {r3-r7, pc}
_0202C5F8:
	cmp r5, #0x0
	bne _0202C60C
	mov r0, #0x16
	bl FUN_0202C1AC
	mov r0, #0x1
	bl FUN_020336A0
	mov r0, #0x0
	pop {r3-r7, pc}
_0202C60C:
	ldr r1, _0202C684 ; =UNK_021C59D8
	ldr r0, _0202C688 ; =0x0000130C
	ldr r3, [r1, #0x4]
	ldrh r2, [r3, r0]
	cmp r2, #0x0
	bne _0202C64C
	add r7, r0, #0x0
	mov r3, #0x1
	add r2, r3, #0x0
	sub r7, #0x28
	sub r0, #0x28
_0202C622:
	ldr r4, [r1, #0x4]
	ldr r6, _0202C68C ; =0x000012E4
	ldrh r6, [r4, r6]
	add r6, r6, #0x1
	strh r6, [r4, r7]
	ldr r4, [r1, #0x4]
	ldrh r6, [r4, r0]
	cmp r6, #0x10
	bls _0202C638
	ldr r6, _0202C68C ; =0x000012E4
	strh r3, [r4, r6]
_0202C638:
	ldr r6, [r1, #0x4]
	ldr r4, _0202C68C ; =0x000012E4
	ldrh r4, [r6, r4]
	add r6, r2, #0x0
	sub r4, r4, #0x1
	lsl r6, r4
	add r4, r5, #0x0
	tst r4, r6
	bne _0202C650
	b _0202C622
_0202C64C:
	sub r0, #0x28
	strh r2, [r3, r0]
_0202C650:
	bl WM_GetDispersionScanPeriod
	ldr r2, _0202C684 ; =UNK_021C59D8
	ldr r1, _0202C690 ; =0x000012E6
	ldr r3, [r2, #0x4]
	strh r0, [r3, r1]
	add r0, r1, #0x0
	ldr r3, [r2, #0x4]
	sub r0, #0xc6
	add r4, r3, r0
	sub r0, r1, #0x6
	str r4, [r3, r0]
	ldr r2, [r2, #0x4]
	sub r1, r1, #0x6
	ldr r0, _0202C694 ; =FUN_0202C698
	add r1, r2, r1
	bl WM_StartScan
	cmp r0, #0x2
	beq _0202C680
	bl FUN_0202C1AC
	mov r0, #0x0
	pop {r3-r7, pc}
_0202C680:
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0202C684: .word UNK_021C59D8
_0202C688: .word 0x0000130C
_0202C68C: .word 0x000012E4
_0202C690: .word 0x000012E6
_0202C694: .word FUN_0202C698

	thumb_func_start FUN_0202C698
FUN_0202C698: ; 0x0202C698
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r0, [r4, #0x2]
	cmp r0, #0x0
	beq _0202C6AE
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C6AE:
	ldr r0, _0202C760 ; =UNK_021C59D8
	ldr r2, [r0, #0x4]
	ldr r0, _0202C764 ; =0x00001310
	ldr r1, [r2, r0]
	cmp r1, #0x2
	beq _0202C6D0
	mov r1, #0x0
	sub r0, r0, #0x2
	strh r1, [r2, r0]
	bl FUN_0202C794
	cmp r0, #0x0
	bne _0202C75C
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C6D0:
	ldrh r1, [r4, #0x8]
	cmp r1, #0x3
	beq _0202C75C
	cmp r1, #0x4
	beq _0202C74E
	cmp r1, #0x5
	bne _0202C74E
	sub r0, #0xf0
	add r0, r2, r0
	mov r1, #0xc0
	bl DC_InvalidateRange
	ldr r0, _0202C760 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C768 ; =0x00001320
	ldr r2, [r1, r0]
	cmp r2, #0x0
	beq _0202C704
	ldrh r0, [r4, #0x36]
	cmp r0, #0x8
	blo _0202C704
	add r1, r4, #0x0
	add r1, #0x48
	ldrb r1, [r1, #0x4]
	ldr r0, [r4, #0x3c]
	blx r2
_0202C704:
	ldrh r0, [r4, #0x36]
	cmp r0, #0x8
	blo _0202C74E
	ldr r0, _0202C760 ; =UNK_021C59D8
	ldr r2, [r4, #0x3c]
	ldr r0, [r0, #0x4]
	ldr r1, [r0, #0x8]
	cmp r2, r1
	bne _0202C74E
	add r4, #0x43
	ldrb r2, [r4, #0x0]
	mov r1, #0x3
	and r1, r2
	cmp r1, #0x1
	bne _0202C74E
	mov r1, #0x13
	lsl r1, r1, #0x8
	ldr r2, [r0, r1]
	cmp r2, #0x0
	beq _0202C732
	sub r1, #0xe0
	add r0, r0, r1
	blx r2
_0202C732:
	ldr r0, _0202C760 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C76C ; =0x0000130E
	ldrh r0, [r1, r0]
	cmp r0, #0x0
	beq _0202C74E
	bl FUN_0202C794
	cmp r0, #0x0
	bne _0202C75C
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C74E:
	bl FUN_0202C5D8
	cmp r0, #0x0
	bne _0202C75C
	mov r0, #0x9
	bl FUN_0202C198
_0202C75C:
	pop {r4, pc}
	nop
_0202C760: .word UNK_021C59D8
_0202C764: .word 0x00001310
_0202C768: .word 0x00001320
_0202C76C: .word 0x0000130E

	thumb_func_start FUN_0202C770
FUN_0202C770: ; 0x0202C770
	push {r3, lr}
	ldr r0, _0202C78C ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C790 ; =0x00001310
	ldr r0, [r1, r0]
	cmp r0, #0x2
	beq _0202C782
	mov r0, #0x0
	pop {r3, pc}
_0202C782:
	mov r0, #0x3
	bl FUN_0202C198
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202C78C: .word UNK_021C59D8
_0202C790: .word 0x00001310

	thumb_func_start FUN_0202C794
FUN_0202C794: ; 0x0202C794
	push {r3, lr}
	ldr r0, _0202C7AC ; =FUN_0202C7B0
	bl WM_EndScan
	cmp r0, #0x2
	beq _0202C7A8
	bl FUN_0202C1AC
	mov r0, #0x0
	pop {r3, pc}
_0202C7A8:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202C7AC: .word FUN_0202C7B0

	thumb_func_start FUN_0202C7B0
FUN_0202C7B0: ; 0x0202C7B0
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202C7BE
	bl FUN_0202C1AC
	pop {r3, pc}
_0202C7BE:
	mov r0, #0x1
	bl FUN_0202C198
	ldr r0, _0202C7E0 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C7E4 ; =0x0000130E
	ldrh r0, [r1, r0]
	cmp r0, #0x0
	beq _0202C7DE
	bl FUN_0202C7E8
	cmp r0, #0x0
	bne _0202C7DE
	mov r0, #0x9
	bl FUN_0202C198
_0202C7DE:
	pop {r3, pc}
	.balign 4
_0202C7E0: .word UNK_021C59D8
_0202C7E4: .word 0x0000130E

	thumb_func_start FUN_0202C7E8
FUN_0202C7E8: ; 0x0202C7E8
	push {lr}
	sub sp, #0x24
	ldr r0, _0202C844 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C848 ; =0x00001310
	ldr r0, [r1, r0]
	sub r0, r0, #0x4
	cmp r0, #0x2
	bhi _0202C800
	add sp, #0x24
	mov r0, #0x1
	pop {pc}
_0202C800:
	mov r0, #0x3
	bl FUN_0202C198
	add r1, sp, #0x4
	ldr r0, _0202C84C ; =UNK_02105D54
	add r1, #0x1
	mov r2, #0x3
	bl MI_CpuCopy8
	bl FUN_02033534
	add r1, sp, #0x4
	strb r0, [r1, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, _0202C844 ; =UNK_021C59D8
	ldr r0, _0202C850 ; =FUN_0202C858
	ldr r2, [r1, #0x4]
	ldr r1, _0202C854 ; =0x00001220
	mov r3, #0x1
	add r1, r2, r1
	add r2, sp, #0x4
	bl WM_StartConnectEx
	cmp r0, #0x2
	beq _0202C83E
	bl FUN_0202C1AC
	add sp, #0x24
	mov r0, #0x0
	pop {pc}
_0202C83E:
	mov r0, #0x1
	add sp, #0x24
	pop {pc}
	.balign 4
_0202C844: .word UNK_021C59D8
_0202C848: .word 0x00001310
_0202C84C: .word UNK_02105D54
_0202C850: .word FUN_0202C858
_0202C854: .word 0x00001220

	thumb_func_start FUN_0202C858
FUN_0202C858: ; 0x0202C858
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r0, [r4, #0x2]
	cmp r0, #0x0
	beq _0202C894
	bl FUN_0202C1AC
	ldrh r0, [r4, #0x2]
	cmp r0, #0xc
	bne _0202C874
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C874:
	cmp r0, #0xb
	bne _0202C880
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C880:
	cmp r0, #0x1
	bne _0202C88C
	mov r0, #0x8
	bl FUN_0202C198
	pop {r4, pc}
_0202C88C:
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C894:
	ldrh r0, [r4, #0x8]
	cmp r0, #0x8
	beq _0202C8FA
	cmp r0, #0x7
	bne _0202C8DA
	ldr r0, _0202C8FC ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C900 ; =0x00001335
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0202C8B8
	mov r0, #0x14
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C8B8:
	mov r0, #0x4
	bl FUN_0202C198
	bl FUN_0202C908
	cmp r0, #0x0
	bne _0202C8CE
	mov r0, #0x3
	bl FUN_0202C198
	pop {r4, pc}
_0202C8CE:
	ldr r0, _0202C8FC ; =UNK_021C59D8
	ldrh r2, [r4, #0xa]
	ldr r1, [r0, #0x4]
	ldr r0, _0202C904 ; =0x0000132C
	strh r2, [r1, r0]
	pop {r4, pc}
_0202C8DA:
	cmp r0, #0x6
	beq _0202C8FA
	cmp r0, #0x9
	bne _0202C8F0
	mov r0, #0x14
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C8F0:
	cmp r0, #0x1a
	beq _0202C8FA
	mov r0, #0x9
	bl FUN_0202C198
_0202C8FA:
	pop {r4, pc}
	.balign 4
_0202C8FC: .word UNK_021C59D8
_0202C900: .word 0x00001335
_0202C904: .word 0x0000132C

	thumb_func_start FUN_0202C908
FUN_0202C908: ; 0x0202C908
	push {r4, lr}
	sub sp, #0x8
	ldr r0, _0202C948 ; =UNK_021C59D8
	ldr r2, _0202C94C ; =0x00001304
	ldr r4, [r0, #0x4]
	ldr r3, _0202C950 ; =0x00001020
	ldr r0, [r4, r2]
	add r1, r4, r3
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r2, r2, #0x4
	ldr r2, [r4, r2]
	sub r3, #0xe0
	lsl r2, r2, #0x10
	ldr r0, _0202C954 ; =FUN_0202C958
	lsr r2, r2, #0x10
	add r3, r4, r3
	bl WM_StartMP
	cmp r0, #0x2
	beq _0202C942
	bl FUN_0202C1AC
	add sp, #0x8
	mov r0, #0x0
	pop {r4, pc}
_0202C942:
	mov r0, #0x1
	add sp, #0x8
	pop {r4, pc}
	.balign 4
_0202C948: .word UNK_021C59D8
_0202C94C: .word 0x00001304
_0202C950: .word 0x00001020
_0202C954: .word FUN_0202C958

	thumb_func_start FUN_0202C958
FUN_0202C958: ; 0x0202C958
	push {r3, lr}
	ldrh r1, [r0, #0x2]
	cmp r1, #0x0
	beq _0202C97A
	cmp r1, #0xf
	beq _0202C9B0
	cmp r1, #0x9
	beq _0202C9B0
	cmp r1, #0xd
	beq _0202C9B0
	add r0, r1, #0x0
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r3, pc}
_0202C97A:
	ldrh r0, [r0, #0x4]
	sub r0, #0xa
	cmp r0, #0x3
	bhi _0202C9B0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202C98E: ; jump table (using 16-bit offset)
	.short _0202C996 - _0202C98E - 2; case 0
	.short _0202C9B0 - _0202C98E - 2; case 1
	.short _0202C9B0 - _0202C98E - 2; case 2
	.short _0202C9B0 - _0202C98E - 2; case 3
_0202C996:
	ldr r0, _0202C9B4 ; =UNK_021C59D8
	ldr r2, [r0, #0x4]
	ldr r0, _0202C9B8 ; =0x00001314
	ldr r1, [r2, r0]
	cmp r1, #0x3
	bne _0202C9AA
	sub r0, r0, #0x4
	ldr r0, [r2, r0]
	cmp r0, #0x6
	beq _0202C9B0
_0202C9AA:
	mov r0, #0x4
	bl FUN_0202C198
_0202C9B0:
	pop {r3, pc}
	nop
_0202C9B4: .word UNK_021C59D8
_0202C9B8: .word 0x00001314

	thumb_func_start FUN_0202C9BC
FUN_0202C9BC: ; 0x0202C9BC
	push {r3, lr}
	mov r0, #0x3
	bl FUN_0202C198
	ldr r0, _0202C9DC ; =FUN_0202C9E0
	bl WM_EndMP
	cmp r0, #0x2
	beq _0202C9D6
	bl FUN_0202C1AC
	mov r0, #0x0
	pop {r3, pc}
_0202C9D6:
	mov r0, #0x1
	pop {r3, pc}
	nop
_0202C9DC: .word FUN_0202C9E0

	thumb_func_start FUN_0202C9E0
FUN_0202C9E0: ; 0x0202C9E0
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202C9F2
	bl FUN_0202C1AC
	bl FUN_0202D100
	pop {r3, pc}
_0202C9F2:
	bl FUN_0202CA04
	cmp r0, #0x0
	bne _0202CA00
	mov r0, #0x9
	bl FUN_0202C198
_0202CA00:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202CA04
FUN_0202CA04: ; 0x0202CA04
	push {r3, lr}
	mov r0, #0x3
	bl FUN_0202C198
	ldr r0, _0202CA28 ; =FUN_0202CA2C
	mov r1, #0x0
	bl WM_Disconnect
	cmp r0, #0x2
	beq _0202CA24
	bl FUN_0202C1AC
	bl FUN_0202D0D8
	mov r0, #0x0
	pop {r3, pc}
_0202CA24:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202CA28: .word FUN_0202CA2C

	thumb_func_start FUN_0202CA2C
FUN_0202CA2C: ; 0x0202CA2C
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202CA3A
	bl FUN_0202C1AC
	pop {r3, pc}
_0202CA3A:
	mov r0, #0x1
	bl FUN_0202C198
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202CA44
FUN_0202CA44: ; 0x0202CA44
	push {r3, lr}
	mov r0, #0x3
	bl FUN_0202C198
	ldr r0, _0202CA64 ; =FUN_0202CA68
	bl WM_Reset
	cmp r0, #0x2
	beq _0202CA5E
	bl FUN_0202C1AC
	mov r0, #0x0
	pop {r3, pc}
_0202CA5E:
	mov r0, #0x1
	pop {r3, pc}
	nop
_0202CA64: .word FUN_0202CA68

	thumb_func_start FUN_0202CA68
FUN_0202CA68: ; 0x0202CA68
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r0, [r4, #0x2]
	cmp r0, #0x0
	beq _0202CA80
	mov r0, #0x9
	bl FUN_0202C198
	ldrh r0, [r4, #0x2]
	bl FUN_0202C1AC
	pop {r4, pc}
_0202CA80:
	mov r0, #0x1
	bl FUN_0202C198
	pop {r4, pc}

	thumb_func_start FUN_0202CA88
FUN_0202CA88: ; 0x0202CA88
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	ldr r0, _0202CAD0 ; =UNK_021C59D8
	add r6, r1, #0x0
	add r4, r2, #0x0
	ldr r1, [r0, #0x4]
	mov r0, #0x3d
	lsl r0, r0, #0x6
	ldr r2, _0202CAD4 ; =0x00001304
	add r0, r1, r0
	ldr r1, [r1, r2]
	add r7, r3, #0x0
	bl DC_FlushRange
	ldr r0, _0202CAD8 ; =0x0000FFFF
	add r1, r7, #0x0
	str r0, [sp, #0x0]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	mov r0, #0x2
	str r0, [sp, #0x8]
	ldr r0, _0202CADC ; =FUN_0202CAE0
	add r2, r5, #0x0
	add r3, r6, #0x0
	bl WM_SetMPDataToPortEx
	cmp r0, #0x2
	bne _0202CACA
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0202CACA:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_0202CAD0: .word UNK_021C59D8
_0202CAD4: .word 0x00001304
_0202CAD8: .word 0x0000FFFF
_0202CADC: .word FUN_0202CAE0

	thumb_func_start FUN_0202CAE0
FUN_0202CAE0: ; 0x0202CAE0
	push {r3, lr}
	ldrh r1, [r0, #0x2]
	cmp r1, #0x0
	beq _0202CAF4
	cmp r1, #0xf
	beq _0202CAF4
	add r0, r1, #0x0
	bl FUN_0202C1AC
	pop {r3, pc}
_0202CAF4:
	ldr r2, [r0, #0x20]
	cmp r2, #0x0
	beq _0202CB06
	cmp r1, #0x0
	bne _0202CB02
	mov r0, #0x1
	b _0202CB04
_0202CB02:
	mov r0, #0x0
_0202CB04:
	blx r2
_0202CB06:
	pop {r3, pc}

	thumb_func_start FUN_0202CB08
FUN_0202CB08: ; 0x0202CB08
	push {r3, lr}
	add r2, r0, #0x0
	ldrh r0, [r2, #0x2]
	cmp r0, #0x0
	beq _0202CB18
	bl FUN_0202C1AC
	pop {r3, pc}
_0202CB18:
	ldr r0, _0202CB48 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202CB4C ; =0x00001318
	ldr r3, [r1, r0]
	cmp r3, #0x0
	beq _0202CB44
	ldrh r0, [r2, #0x4]
	cmp r0, #0x19
	beq _0202CB44
	cmp r0, #0x15
	bne _0202CB38
	ldrh r0, [r2, #0x12]
	ldr r1, [r2, #0xc]
	ldrh r2, [r2, #0x10]
	blx r3
	pop {r3, pc}
_0202CB38:
	cmp r0, #0x9
	bne _0202CB44
	ldrh r0, [r2, #0x12]
	mov r1, #0x0
	add r2, r1, #0x0
	blx r3
_0202CB44:
	pop {r3, pc}
	nop
_0202CB48: .word UNK_021C59D8
_0202CB4C: .word 0x00001318

	thumb_func_start FUN_0202CB50
FUN_0202CB50: ; 0x0202CB50
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202CB60
	mov r0, #0xa
	bl FUN_0202C198
	pop {r3, pc}
_0202CB60:
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02090CC8
	mov r0, #0x0
	bl FUN_0202C198
	pop {r3, pc}

	thumb_func_start FUN_0202CB70
FUN_0202CB70: ; 0x0202CB70
	ldr r1, _0202CB78 ; =UNK_021C59D8
	ldr r1, [r1, #0x4]
	str r0, [r1, #0x8]
	bx lr
	.balign 4
_0202CB78: .word UNK_021C59D8

	thumb_func_start FUN_0202CB7C
FUN_0202CB7C: ; 0x0202CB7C
	ldr r2, _0202CB88 ; =UNK_021C59D8
	ldr r3, [r2, #0x4]
	str r0, [r3, #0x0]
	ldr r0, [r2, #0x4]
	strh r1, [r0, #0x4]
	bx lr
	.balign 4
_0202CB88: .word UNK_021C59D8

	thumb_func_start FUN_0202CB8C
FUN_0202CB8C: ; 0x0202CB8C
	ldr r0, _0202CB98 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202CB9C ; =0x0000132E
	ldrh r0, [r1, r0]
	bx lr
	nop
_0202CB98: .word UNK_021C59D8
_0202CB9C: .word 0x0000132E

	thumb_func_start FUN_0202CBA0
FUN_0202CBA0: ; 0x0202CBA0
	push {r3-r4}
	ldr r0, _0202CBCC ; =UNK_021C59D8
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _0202CBD0 ; =0x0000132E
	add r3, r2, #0x0
	ldrh r4, [r1, r0]
	mov r1, #0x1
_0202CBB0:
	add r0, r4, #0x0
	tst r0, r1
	beq _0202CBB8
	add r2, r2, #0x1
_0202CBB8:
	lsl r0, r4, #0xf
	add r3, r3, #0x1
	lsr r4, r0, #0x10
	cmp r3, #0x10
	blt _0202CBB0
	lsl r0, r2, #0x10
	lsr r0, r0, #0x10
	pop {r3-r4}
	bx lr
	nop
_0202CBCC: .word UNK_021C59D8
_0202CBD0: .word 0x0000132E

	thumb_func_start FUN_0202CBD4
FUN_0202CBD4: ; 0x0202CBD4
	ldr r0, _0202CBE0 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202CBE4 ; =0x00001310
	ldr r0, [r1, r0]
	bx lr
	nop
_0202CBE0: .word UNK_021C59D8
_0202CBE4: .word 0x00001310

	thumb_func_start FUN_0202CBE8
FUN_0202CBE8: ; 0x0202CBE8
	ldr r0, _0202CBF4 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202CBF8 ; =0x00001330
	ldr r0, [r1, r0]
	bx lr
	nop
_0202CBF4: .word UNK_021C59D8
_0202CBF8: .word 0x00001330

	thumb_func_start FUN_0202CBFC
FUN_0202CBFC: ; 0x0202CBFC
	push {r3-r5, lr}
	sub sp, #0x8
	add r0, sp, #0x0
	bl OS_GetMacAddress
	ldr r0, _0202CC84 ; =0x027FFC3C
	ldr r3, [r0, #0x0]
	add r0, sp, #0x0
	ldrh r2, [r0, #0x4]
	ldrh r1, [r0, #0x2]
	ldrh r0, [r0, #0x0]
	add r0, r0, r3
	add r0, r1, r0
	add r1, r2, r0
	ldr r3, _0202CC88 ; =UNK_021C59D8
	ldr r2, _0202CC8C ; =0x00001338
	ldr r0, [r3, #0x4]
	str r1, [r0, r2]
	ldr r0, [r3, #0x4]
	ldr r1, _0202CC90 ; =0x00010DCD
	ldr r4, [r0, r2]
	add r5, r4, #0x0
	mul r5, r1
	ldr r1, _0202CC94 ; =0x00003039
	mov r4, #0x0
	add r1, r5, r1
	str r1, [r0, r2]
	ldr r1, [r3, #0x4]
	add r0, r2, #0x4
	strh r4, [r1, r0]
	ldr r1, [r3, #0x4]
	mov r4, #0x65
	add r0, r2, #0x6
	strh r4, [r1, r0]
	mov r0, #0x3
	bl FUN_0202C198
	mov r0, #0x1
	bl FUN_0202CC98
	cmp r0, #0x18
	bne _0202CC68
	mov r0, #0x18
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x1
	bl FUN_020336A0
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r5, pc}
_0202CC68:
	cmp r0, #0x2
	beq _0202CC7C
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r5, pc}
_0202CC7C:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r5, pc}
	nop
_0202CC84: .word 0x027FFC3C
_0202CC88: .word UNK_021C59D8
_0202CC8C: .word 0x00001338
_0202CC90: .word 0x00010DCD
_0202CC94: .word 0x00003039

	thumb_func_start FUN_0202CC98
FUN_0202CC98: ; 0x0202CC98
	push {r4, lr}
	add r4, r0, #0x0
	bl WM_GetAllowedChannel
	mov r1, #0x2
	lsl r1, r1, #0xe
	cmp r0, r1
	bne _0202CCBE
	mov r0, #0x3
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x1
	bl FUN_020336A0
	mov r0, #0x3
	pop {r4, pc}
_0202CCBE:
	cmp r0, #0x0
	bne _0202CCD8
	mov r0, #0x16
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x1
	bl FUN_020336A0
	mov r0, #0x18
	pop {r4, pc}
_0202CCD8:
	mov r2, #0x1
	sub r1, r4, #0x1
	lsl r2, r1
	add r1, r2, #0x0
	tst r1, r0
	bne _0202CD00
	mov r2, #0x1
_0202CCE6:
	add r1, r4, #0x1
	lsl r1, r1, #0x10
	lsr r4, r1, #0x10
	cmp r4, #0x10
	bls _0202CCF4
	mov r0, #0x18
	pop {r4, pc}
_0202CCF4:
	sub r1, r4, #0x1
	add r3, r2, #0x0
	lsl r3, r1
	add r1, r3, #0x0
	tst r1, r0
	beq _0202CCE6
_0202CD00:
	ldr r0, _0202CD10 ; =FUN_0202CD14
	add r1, r4, #0x0
	bl FUN_0202CD90
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r4, pc}
	nop
_0202CD10: .word FUN_0202CD14

	thumb_func_start FUN_0202CD14
FUN_0202CD14: ; 0x0202CD14
	push {r3-r5, lr}
	ldrh r1, [r0, #0x2]
	cmp r1, #0x0
	beq _0202CD30
	add r0, r1, #0x0
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x1
	bl FUN_020336A0
	pop {r3-r5, pc}
_0202CD30:
	ldr r2, _0202CD88 ; =UNK_021C59D8
	ldrh r1, [r0, #0x8]
	ldrh r5, [r0, #0xa]
	ldr r0, [r2, #0x4]
	ldr r3, _0202CD8C ; =0x0000133E
	ldrh r4, [r0, r3]
	cmp r4, r5
	bls _0202CD50
	strh r5, [r0, r3]
	mov r4, #0x1
	sub r0, r1, #0x1
	lsl r4, r0
	ldr r2, [r2, #0x4]
	add r0, r3, #0x2
	strh r4, [r2, r0]
	b _0202CD64
_0202CD50:
	cmp r4, r5
	bne _0202CD64
	add r2, r3, #0x2
	ldrh r5, [r0, r2]
	mov r4, #0x1
	sub r2, r1, #0x1
	lsl r4, r2
	orr r4, r5
	add r2, r3, #0x2
	strh r4, [r0, r2]
_0202CD64:
	add r0, r1, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202CC98
	cmp r0, #0x18
	bne _0202CD7A
	mov r0, #0x7
	bl FUN_0202C198
	pop {r3-r5, pc}
_0202CD7A:
	cmp r0, #0x2
	beq _0202CD84
	mov r0, #0x9
	bl FUN_0202C198
_0202CD84:
	pop {r3-r5, pc}
	nop
_0202CD88: .word UNK_021C59D8
_0202CD8C: .word 0x0000133E

	thumb_func_start FUN_0202CD90
FUN_0202CD90: ; 0x0202CD90
	push {r3, lr}
	add r3, r1, #0x0
	mov r1, #0x1e
	str r1, [sp, #0x0]
	mov r1, #0x3
	mov r2, #0x11
	bl WM_MeasureChannel
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202CDA4
FUN_0202CDA4: ; 0x0202CDA4
	push {r3, lr}
	mov r0, #0x1
	bl FUN_0202C198
	ldr r0, _0202CDC8 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	mov r0, #0x4d
	lsl r0, r0, #0x6
	ldrh r0, [r1, r0]
	bl FUN_0202CDD0
	ldr r2, _0202CDC8 ; =UNK_021C59D8
	ldr r1, _0202CDCC ; =0x0000133C
	ldr r3, [r2, #0x4]
	strh r0, [r3, r1]
	ldr r0, [r2, #0x4]
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_0202CDC8: .word UNK_021C59D8
_0202CDCC: .word 0x0000133C

	thumb_func_start FUN_0202CDD0
FUN_0202CDD0: ; 0x0202CDD0
	push {r4-r7}
	add r4, r0, #0x0
	mov r0, #0x0
	add r3, r0, #0x0
	add r2, r0, #0x0
	mov r1, #0x1
_0202CDDC:
	add r5, r1, #0x0
	lsl r5, r2
	tst r5, r4
	beq _0202CDF0
	add r0, r2, #0x1
	add r3, r3, #0x1
	lsl r0, r0, #0x10
	lsl r3, r3, #0x10
	asr r0, r0, #0x10
	lsr r3, r3, #0x10
_0202CDF0:
	add r2, r2, #0x1
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	cmp r2, #0x10
	blt _0202CDDC
	cmp r3, #0x1
	bls _0202CE4E
	ldr r5, _0202CE54 ; =UNK_021C59D8
	ldr r2, _0202CE58 ; =0x00001338
	ldr r0, [r5, #0x4]
	ldr r1, _0202CE5C ; =0x00010DCD
	ldr r6, [r0, r2]
	add r7, r6, #0x0
	mul r7, r1
	ldr r1, _0202CE60 ; =0x00003039
	add r1, r7, r1
	str r1, [r0, r2]
	ldr r0, [r5, #0x4]
	mov r1, #0x1
	ldr r0, [r0, r2]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mul r0, r3
	lsl r0, r0, #0x8
	lsr r2, r0, #0x10
	mov r3, #0x0
_0202CE24:
	add r0, r4, #0x0
	tst r0, r1
	beq _0202CE3E
	cmp r2, #0x0
	bne _0202CE38
	add r0, r3, #0x1
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	pop {r4-r7}
	bx lr
_0202CE38:
	sub r0, r2, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
_0202CE3E:
	lsl r0, r4, #0xf
	lsr r4, r0, #0x10
	add r0, r3, #0x1
	lsl r0, r0, #0x10
	asr r3, r0, #0x10
	cmp r3, #0x10
	blt _0202CE24
	mov r0, #0x0
_0202CE4E:
	pop {r4-r7}
	bx lr
	nop
_0202CE54: .word UNK_021C59D8
_0202CE58: .word 0x00001338
_0202CE5C: .word 0x00010DCD
_0202CE60: .word 0x00003039

	thumb_func_start FUN_0202CE64
FUN_0202CE64: ; 0x0202CE64
	push {r3-r5, lr}
	lsl r1, r0, #0x1b
	lsr r2, r1, #0x1b
	beq _0202CE72
	mov r1, #0x20
	sub r1, r1, r2
	add r0, r0, r1
_0202CE72:
	ldr r2, _0202CEE4 ; =UNK_021C59D8
	ldr r1, _0202CEE8 ; =0x00001308
	str r0, [r2, #0x4]
	mov r3, #0x0
	str r3, [r0, r1]
	ldr r4, [r2, #0x4]
	sub r0, r1, #0x4
	str r3, [r4, r0]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	add r0, #0x10
	str r3, [r4, r0]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	add r0, #0x24
	strh r3, [r4, r0]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	mov r5, #0x1
	add r0, #0x26
	strh r5, [r4, r0]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	add r0, #0x28
	str r3, [r4, r0]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	add r0, #0x8
	str r3, [r4, r0]
	ldr r0, [r2, #0x4]
	mov r5, #0x8
	str r3, [r0, #0x0]
	ldr r0, [r2, #0x4]
	strh r3, [r0, #0x4]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	add r0, #0x14
	str r3, [r4, r0]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	add r0, #0x2c
	strb r5, [r4, r0]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	add r0, #0x2d
	strb r3, [r4, r0]
	ldr r0, [r2, #0x4]
	add r1, #0x3a
	strb r3, [r0, r1]
	bl FUN_0202CF0C
	cmp r0, #0x0
	bne _0202CEE0
	mov r0, #0x0
	pop {r3-r5, pc}
_0202CEE0:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0202CEE4: .word UNK_021C59D8
_0202CEE8: .word 0x00001308

	thumb_func_start FUN_0202CEEC
FUN_0202CEEC: ; 0x0202CEEC
	mov r0, #0x4e
	lsl r0, r0, #0x6
	bx lr
	.balign 4

	thumb_func_start FUN_0202CEF4
FUN_0202CEF4: ; 0x0202CEF4
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x8
	bne _0202CF08
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x19
	bl FUN_0202C1AC
_0202CF08:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202CF0C
FUN_0202CF0C: ; 0x0202CF0C
	push {r3, lr}
	mov r0, #0x3
	bl FUN_0202C198
	ldr r0, _0202CF38 ; =UNK_021C59D8
	ldr r1, _0202CF3C ; =FUN_0202CF40
	ldr r0, [r0, #0x4]
	mov r2, #0x2
	add r0, #0x40
	bl WM_Initialize
	cmp r0, #0x2
	beq _0202CF34
	bl FUN_0202C1AC
	mov r0, #0xa
	bl FUN_0202C198
	mov r0, #0x0
	pop {r3, pc}
_0202CF34:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202CF38: .word UNK_021C59D8
_0202CF3C: .word FUN_0202CF40

	thumb_func_start FUN_0202CF40
FUN_0202CF40: ; 0x0202CF40
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202CF5A
	bl FUN_0202C1AC
	mov r0, #0xa
	bl FUN_0202C198
	mov r0, #0x1
	bl FUN_020336A0
	pop {r3, pc}
_0202CF5A:
	ldr r0, _0202CF80 ; =FUN_0202CEF4
	bl WM_SetIndCallback
	cmp r0, #0x0
	beq _0202CF76
	bl FUN_0202C1AC
	mov r0, #0xa
	bl FUN_0202C198
	mov r0, #0x1
	bl FUN_020336A0
	pop {r3, pc}
_0202CF76:
	mov r0, #0x1
	bl FUN_0202C198
	pop {r3, pc}
	nop
_0202CF80: .word FUN_0202CEF4

	thumb_func_start FUN_0202CF84
FUN_0202CF84: ; 0x0202CF84
	push {r3-r7, lr}
	add r6, r1, #0x0
	ldr r1, _0202D02C ; =UNK_021C59D8
	add r5, r0, #0x0
	add r7, r2, #0x0
	mov r0, #0x7
	ldr r2, [r1, #0x4]
	ldr r1, _0202D030 ; =0x00001308
	lsl r0, r0, #0x6
	str r0, [r2, r1]
	ldr r0, _0202D02C ; =UNK_021C59D8
	add r4, r3, #0x0
	ldr r2, [r0, #0x4]
	sub r0, r1, #0x4
	mov r3, #0xe0
	str r3, [r2, r0]
	ldr r0, _0202D02C ; =UNK_021C59D8
	add r1, #0xc
	ldr r0, [r0, #0x4]
	str r5, [r0, r1]
	mov r0, #0x3
	bl FUN_0202C198
	ldr r1, _0202D02C ; =UNK_021C59D8
	cmp r5, #0x0
	ldr r0, [r1, #0x4]
	strh r6, [r0, #0xc]
	ldr r0, [r1, #0x4]
	strh r7, [r0, #0x32]
	add r0, sp, #0x8
	ldrh r2, [r0, #0x10]
	ldr r0, [r1, #0x4]
	strh r2, [r0, #0x18]
	beq _0202CFCE
	cmp r5, #0x4
	beq _0202CFE8
	b _0202CFF4
_0202CFCE:
	ldr r0, [r1, #0x4]
	mov r2, #0xc0
	strh r2, [r0, #0x34]
	cmp r4, #0x5
	blo _0202CFE0
	ldr r0, [r1, #0x4]
	mov r2, #0xc
	strh r2, [r0, #0x36]
	b _0202CFF4
_0202CFE0:
	ldr r0, [r1, #0x4]
	mov r2, #0x26
	strh r2, [r0, #0x36]
	b _0202CFF4
_0202CFE8:
	ldr r0, [r1, #0x4]
	mov r2, #0x64
	strh r2, [r0, #0x34]
	ldr r0, [r1, #0x4]
	mov r2, #0xc
	strh r2, [r0, #0x36]
_0202CFF4:
	ldr r1, _0202D02C ; =UNK_021C59D8
	ldr r0, [r1, #0x4]
	strh r4, [r0, #0x10]
	ldr r2, [r1, #0x4]
	mov r0, #0x0
	strh r0, [r2, #0x16]
	ldr r2, [r1, #0x4]
	cmp r5, #0x2
	strh r0, [r2, #0x12]
	ldr r2, [sp, #0x1c]
	ldr r1, [r1, #0x4]
	strh r2, [r1, #0xe]
	bne _0202D010
	mov r0, #0x1
_0202D010:
	ldr r1, _0202D02C ; =UNK_021C59D8
	cmp r5, #0x0
	ldr r1, [r1, #0x4]
	strh r0, [r1, #0x14]
	beq _0202D022
	cmp r5, #0x2
	beq _0202D022
	cmp r5, #0x4
	bne _0202D028
_0202D022:
	bl FUN_0202C1C8
	pop {r3-r7, pc}
_0202D028:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0202D02C: .word UNK_021C59D8
_0202D030: .word 0x00001308

	thumb_func_start FUN_0202D034
FUN_0202D034: ; 0x0202D034
	push {r4-r6, lr}
	ldr r2, _0202D094 ; =UNK_021C59D8
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r3, #0x2
	ldr r0, [r2, #0x4]
	ldr r1, _0202D098 ; =0x00001308
	lsl r3, r3, #0x8
	str r3, [r0, r1]
	sub r0, r1, #0x4
	ldr r3, [r2, #0x4]
	mov r6, #0x40
	str r6, [r3, r0]
	ldr r0, [r2, #0x4]
	add r1, #0xc
	str r5, [r0, r1]
	mov r0, #0x3
	bl FUN_0202C198
	cmp r5, #0x1
	beq _0202D066
	cmp r5, #0x3
	beq _0202D066
	cmp r5, #0x5
	bne _0202D08E
_0202D066:
	ldr r1, _0202D094 ; =UNK_021C59D8
	add r0, r4, #0x0
	ldr r2, [r1, #0x4]
	ldr r1, _0202D09C ; =0x00001220
	add r1, r2, r1
	mov r2, #0xc0
	bl MI_CpuCopy8
	ldr r0, _0202D094 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D09C ; =0x00001220
	add r0, r1, r0
	mov r1, #0xc0
	bl DC_FlushRange
	bl DC_WaitWriteBufferEmpty
	bl FUN_0202C7E8
	pop {r4-r6, pc}
_0202D08E:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_0202D094: .word UNK_021C59D8
_0202D098: .word 0x00001308
_0202D09C: .word 0x00001220

	thumb_func_start FUN_0202D0A0
FUN_0202D0A0: ; 0x0202D0A0
	push {r3, lr}
	ldr r2, _0202D0C4 ; =UNK_021C59D8
	ldr r3, [r2, #0x4]
	ldr r2, _0202D0C8 ; =0x00001318
	str r0, [r3, r2]
	lsl r0, r1, #0x10
	ldr r1, _0202D0CC ; =FUN_0202CB08
	lsr r0, r0, #0x10
	mov r2, #0x0
	bl WM_SetPortCallback
	cmp r0, #0x0
	beq _0202D0C2
	mov r0, #0x9
	bl FUN_0202C198
_0202D0C0:
	b _0202D0C0
_0202D0C2:
	pop {r3, pc}
	.balign 4
_0202D0C4: .word UNK_021C59D8
_0202D0C8: .word 0x00001318
_0202D0CC: .word FUN_0202CB08

	thumb_func_start FUN_0202D0D0
FUN_0202D0D0: ; 0x0202D0D0
	push {r3, lr}
	bl FUN_0202CA88
	pop {r3, pc}

	thumb_func_start FUN_0202D0D8
FUN_0202D0D8: ; 0x0202D0D8
	push {r3, lr}
	ldr r0, _0202D0F8 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D0FC ; =0x00001310
	ldr r0, [r1, r0]
	cmp r0, #0x2
	bne _0202D0E8
_0202D0E6:
	b _0202D0E6
_0202D0E8:
	bl FUN_0202CA44
	cmp r0, #0x0
	bne _0202D0F6
	mov r0, #0xa
	bl FUN_0202C198
_0202D0F6:
	pop {r3, pc}
	.balign 4
_0202D0F8: .word UNK_021C59D8
_0202D0FC: .word 0x00001310

	thumb_func_start FUN_0202D100
FUN_0202D100: ; 0x0202D100
	push {r3, lr}
	ldr r0, _0202D16C ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D170 ; =0x00001310
	ldr r0, [r1, r0]
	cmp r0, #0x1
	beq _0202D16A
	cmp r0, #0x6
	beq _0202D126
	cmp r0, #0x5
	beq _0202D126
	cmp r0, #0x4
	beq _0202D126
	mov r0, #0x3
	bl FUN_0202C198
	bl FUN_0202D0D8
	pop {r3, pc}
_0202D126:
	mov r0, #0x3
	bl FUN_0202C198
	ldr r0, _0202D16C ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D174 ; =0x00001314
	ldr r0, [r1, r0]
	cmp r0, #0x5
	bhi _0202D16A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202D144: ; jump table (using 16-bit offset)
	.short _0202D15E - _0202D144 - 2; case 0
	.short _0202D150 - _0202D144 - 2; case 1
	.short _0202D16A - _0202D144 - 2; case 2
	.short _0202D16A - _0202D144 - 2; case 3
	.short _0202D15E - _0202D144 - 2; case 4
	.short _0202D150 - _0202D144 - 2; case 5
_0202D150:
	bl FUN_0202C9BC
	cmp r0, #0x0
	bne _0202D16A
	bl FUN_0202D0D8
	pop {r3, pc}
_0202D15E:
	bl FUN_0202C460
	cmp r0, #0x0
	bne _0202D16A
	bl FUN_0202D0D8
_0202D16A:
	pop {r3, pc}
	.balign 4
_0202D16C: .word UNK_021C59D8
_0202D170: .word 0x00001310
_0202D174: .word 0x00001314

	thumb_func_start FUN_0202D178
FUN_0202D178: ; 0x0202D178
	push {r3, lr}
	mov r0, #0x3
	bl FUN_0202C198
	ldr r0, _0202D198 ; =FUN_0202CB50
	bl WM_End
	cmp r0, #0x2
	beq _0202D194
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x0
	pop {r3, pc}
_0202D194:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202D198: .word FUN_0202CB50

	thumb_func_start FUN_0202D19C
FUN_0202D19C: ; 0x0202D19C
	ldr r0, _0202D1A8 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D1AC ; =0x0000132C
	ldrh r0, [r1, r0]
	bx lr
	nop
_0202D1A8: .word UNK_021C59D8
_0202D1AC: .word 0x0000132C

	thumb_func_start FUN_0202D1B0
FUN_0202D1B0: ; 0x0202D1B0
	ldr r1, _0202D1C0 ; =UNK_021C59D8
	ldr r2, [r1, #0x4]
	cmp r2, #0x0
	beq _0202D1BC
	ldr r1, _0202D1C4 ; =0x00001334
	strb r0, [r2, r1]
_0202D1BC:
	bx lr
	nop
_0202D1C0: .word UNK_021C59D8
_0202D1C4: .word 0x00001334

	thumb_func_start FUN_0202D1C8
FUN_0202D1C8: ; 0x0202D1C8
	ldr r0, _0202D1DC ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D1E0 ; =0x00001310
	ldr r0, [r1, r0]
	cmp r0, #0x1
	bne _0202D1D8
	mov r0, #0x1
	bx lr
_0202D1D8:
	mov r0, #0x0
	bx lr
	.balign 4
_0202D1DC: .word UNK_021C59D8
_0202D1E0: .word 0x00001310

	thumb_func_start FUN_0202D1E4
FUN_0202D1E4: ; 0x0202D1E4
	ldr r0, _0202D1F8 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D1FC ; =0x00001310
	ldr r0, [r1, r0]
	cmp r0, #0x3
	bne _0202D1F4
	mov r0, #0x1
	bx lr
_0202D1F4:
	mov r0, #0x0
	bx lr
	.balign 4
_0202D1F8: .word UNK_021C59D8
_0202D1FC: .word 0x00001310

	thumb_func_start FUN_0202D200
FUN_0202D200: ; 0x0202D200
	ldr r0, _0202D214 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D218 ; =0x00001310
	ldr r0, [r1, r0]
	cmp r0, #0x9
	bne _0202D210
	mov r0, #0x1
	bx lr
_0202D210:
	mov r0, #0x0
	bx lr
	.balign 4
_0202D214: .word UNK_021C59D8
_0202D218: .word 0x00001310

	thumb_func_start FUN_0202D21C
FUN_0202D21C: ; 0x0202D21C
	ldr r0, _0202D238 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _0202D234
	ldr r0, _0202D23C ; =0x00001310
	ldr r0, [r1, r0]
	cmp r0, #0x2
	bne _0202D230
	mov r0, #0x1
	bx lr
_0202D230:
	mov r0, #0x0
	bx lr
_0202D234:
	mov r0, #0x0
	bx lr
	.balign 4
_0202D238: .word UNK_021C59D8
_0202D23C: .word 0x00001310

	thumb_func_start FUN_0202D240
FUN_0202D240: ; 0x0202D240
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r0, #0x0
	ldr r0, _0202D274 ; =UNK_021C59D8
	add r5, r1, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _0202D278 ; =0x00001310
	add r4, r2, #0x0
	ldr r0, [r1, r0]
	cmp r0, #0x4
	bne _0202D26E
	lsl r0, r3, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x1
	lsl r2, r5, #0x10
	str r0, [sp, #0x4]
	mov r0, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x10
	add r3, r4, #0x0
	bl WM_SetGameInfo
_0202D26E:
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_0202D274: .word UNK_021C59D8
_0202D278: .word 0x00001310

	thumb_func_start FUN_0202D27C
FUN_0202D27C: ; 0x0202D27C
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	bne _0202D28C
	ldr r0, _0202D290 ; =UNK_021C59D8
	mov r2, #0x1
	ldr r1, [r0, #0x4]
	ldr r0, _0202D294 ; =0x00001344
	strb r2, [r1, r0]
_0202D28C:
	bx lr
	nop
_0202D290: .word UNK_021C59D8
_0202D294: .word 0x00001344

	thumb_func_start FUN_0202D298
FUN_0202D298: ; 0x0202D298
	push {r4, lr}
	ldr r2, _0202D2C4 ; =UNK_021C59D8
	add r1, r0, #0x0
	ldr r3, [r2, #0x4]
	ldr r0, _0202D2C8 ; =0x00001344
	mov r4, #0x0
	strb r4, [r3, r0]
	ldr r2, [r2, #0x4]
	sub r0, #0x34
	ldr r0, [r2, r0]
	cmp r0, #0x4
	bne _0202D2BE
	ldr r0, _0202D2CC ; =FUN_0202D27C
	bl WM_SetEntry
	cmp r0, #0x2
	bne _0202D2BE
	mov r0, #0x1
	pop {r4, pc}
_0202D2BE:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0202D2C4: .word UNK_021C59D8
_0202D2C8: .word 0x00001344
_0202D2CC: .word FUN_0202D27C

	thumb_func_start FUN_0202D2D0
FUN_0202D2D0: ; 0x0202D2D0
	ldr r0, _0202D2EC ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _0202D2E8
	ldr r0, _0202D2F0 ; =0x00001345
	ldrb r0, [r1, r0]
	cmp r0, #0x6
	blo _0202D2E4
	mov r0, #0x1
	bx lr
_0202D2E4:
	mov r0, #0x0
	bx lr
_0202D2E8:
	mov r0, #0x0
	bx lr
	.balign 4
_0202D2EC: .word UNK_021C59D8
_0202D2F0: .word 0x00001345

	thumb_func_start FUN_0202D2F4
FUN_0202D2F4: ; 0x0202D2F4
	ldr r0, _0202D300 ; =UNK_021C59D8
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _0202D304 ; =0x00001345
	strb r2, [r1, r0]
	bx lr
	.balign 4
_0202D300: .word UNK_021C59D8
_0202D304: .word 0x00001345

	thumb_func_start FUN_0202D308
FUN_0202D308: ; 0x0202D308
	ldr r1, _0202D314 ; =UNK_021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202D318 ; =0x00001320
	str r0, [r2, r1]
	bx lr
	nop
_0202D314: .word UNK_021C59D8
_0202D318: .word 0x00001320

	thumb_func_start FUN_0202D31C
FUN_0202D31C: ; 0x0202D31C
	ldr r1, _0202D328 ; =UNK_021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202D32C ; =0x00001324
	str r0, [r2, r1]
	bx lr
	nop
_0202D328: .word UNK_021C59D8
_0202D32C: .word 0x00001324

	thumb_func_start FUN_0202D330
FUN_0202D330: ; 0x0202D330
	ldr r1, _0202D33C ; =UNK_021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202D340 ; =0x00001328
	str r0, [r2, r1]
	bx lr
	nop
_0202D33C: .word UNK_021C59D8
_0202D340: .word 0x00001328

	thumb_func_start FUN_0202D344
FUN_0202D344: ; 0x0202D344
	ldr r1, _0202D350 ; =UNK_021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202D354 ; =0x00001342
	strb r0, [r2, r1]
	bx lr
	nop
_0202D350: .word UNK_021C59D8
_0202D354: .word 0x00001342

	thumb_func_start FUN_0202D358
FUN_0202D358: ; 0x0202D358
	ldr r0, _0202D364 ; =UNK_021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D368 ; =0x00001342
	ldrb r0, [r1, r0]
	bx lr
	nop
_0202D364: .word UNK_021C59D8
_0202D368: .word 0x00001342

	thumb_func_start FUN_0202D36C
FUN_0202D36C: ; 0x0202D36C
	ldr r1, _0202D378 ; =UNK_021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202D37C ; =0x00001343
	strb r0, [r2, r1]
	bx lr
	nop
_0202D378: .word UNK_021C59D8
_0202D37C: .word 0x00001343

	thumb_func_start FUN_0202D380
FUN_0202D380: ; 0x0202D380
	ldr r1, _0202D38C ; =UNK_021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202D390 ; =0x00001335
	strb r0, [r2, r1]
	bx lr
	nop
_0202D38C: .word UNK_021C59D8
_0202D390: .word 0x00001335
