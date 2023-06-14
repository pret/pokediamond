	.include "asm/macros.inc"
	.include "global.inc"

	.extern gSystem

	.section .rodata

	.global UNK_020F4850
UNK_020F4850: ; 0x020F4850
	.byte 0x0A, 0x00, 0x01, 0x00, 0xFE, 0x00, 0x00, 0x00

	.global UNK_020F4858
UNK_020F4858: ; 0x020F4858
	.byte 0x0B, 0x00, 0x01, 0x00, 0xFE, 0x00, 0x00, 0x00

	.global UNK_020F4860
UNK_020F4860: ; 0x020F4860
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.text

	thumb_func_start FUN_0204B34C
FUN_0204B34C: ; 0x0204B34C
	cmp r0, #0x0
	bne _0204B354
	mov r0, #0x0
	bx lr
_0204B354:
	add r0, #0x94
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr

	thumb_func_start FUN_0204B35C
FUN_0204B35C: ; 0x0204B35C
	cmp r0, #0x0
	bne _0204B364
	mov r0, #0x0
	bx lr
_0204B364:
	sub r0, #0x94
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr

	thumb_func_start FUN_0204B36C
FUN_0204B36C: ; 0x0204B36C
	cmp r0, #0x0
	bne _0204B374
	mov r0, #0x0
	bx lr
_0204B374:
	add r0, #0x5e
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr

	thumb_func_start FUN_0204B37C
FUN_0204B37C: ; 0x0204B37C
	cmp r0, #0x0
	bne _0204B384
	mov r0, #0x0
	bx lr
_0204B384:
	sub r0, #0x5e
	bx lr

	thumb_func_start FUN_0204B388
FUN_0204B388: ; 0x0204B388
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x64
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0x64
	bl MI_CpuFill8
	str r6, [r4, #0x0]
	add r0, r6, #0x0
	bl FUN_02025128
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0204B410
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204B3B8
FUN_0204B3B8: ; 0x0204B3B8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0204B444
	ldr r0, [r4, #0x4]
	bl FreeToHeap
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0204B3D0
FUN_0204B3D0: ; 0x0204B3D0
	push {r4-r6, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	add r6, r1, #0x0
	cmp r0, #0x0
	bne _0204B3FA
	mov r0, #0xb
	bl FUN_02025128
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_02024ECC
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl FUN_020253E0
	add r0, r5, #0x0
	bl FreeToHeap
	pop {r4-r6, pc}
_0204B3FA:
	ldr r0, [r0, #0x18]
	ldr r5, [r0, #0x4]
	ldr r0, [r4, #0xc]
	bl FUN_02024ECC
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl FUN_020253E0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204B410
FUN_0204B410: ; 0x0204B410
	push {r3-r5, lr}
	ldr r4, [r0, #0x3c]
	add r5, r1, #0x0
	add r0, r4, #0x0
	mov r1, #0x11
	bl MOD05_021E4C54
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl AllocFromHeap
	str r0, [r5, #0x60]
	ldr r2, [r5, #0x60]
	add r0, r4, #0x0
	mov r1, #0x11
	bl MOD05_021E4C60
	add r0, r5, #0x0
	add r1, r5, #0x0
	add r5, #0x60
	add r0, #0x8
	add r1, #0x5c
	add r2, r5, #0x0
	bl FUN_0201B234
	pop {r3-r5, pc}

	thumb_func_start FUN_0204B444
FUN_0204B444: ; 0x0204B444
	ldr r3, _0204B44C ; =MOD05_021E4C00
	ldr r0, [r0, #0x60]
	bx r3
	nop
_0204B44C: .word MOD05_021E4C00

	thumb_func_start FUN_0204B450
FUN_0204B450: ; 0x0204B450
	push {r3-r5, lr}
	sub sp, #0x30
	ldr r3, _0204B48C ; =UNK_020F4860
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldmia r3!, {r0-r1}
	add r2, sp, #0x24
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	add r0, sp, #0x0
	bl MTX_Identity33_
	ldr r0, [r5, #0x4]
	add r1, r4, #0x0
	ldr r0, [r0, #0x18]
	add r2, sp, #0x0
	ldr r0, [r0, #0x5c]
	add r3, sp, #0x24
	bl FUN_0201B6D0
	cmp r0, #0x0
	beq _0204B484
	add sp, #0x30
	mov r0, #0x1
	pop {r3-r5, pc}
_0204B484:
	mov r0, #0x0
	add sp, #0x30
	pop {r3-r5, pc}
	nop
_0204B48C: .word UNK_020F4860

	thumb_func_start FUN_0204B490
FUN_0204B490: ; 0x0204B490
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r0, [r5, #0xc]
	bl FUN_02024ECC
	add r4, r0, #0x0
	ldr r0, [r5, #0x34]
	add r1, sp, #0x0
	add r2, sp, #0x4
	mov r3, #0x1
	bl FUN_020580F4
	cmp r0, #0x1
	bne _0204B4F8
	mov r6, #0x0
	mov r7, #0x1
_0204B4B6:
	ldr r0, [sp, #0x0]
	bl FUN_02058458
	bl FUN_0205C334
	cmp r0, #0x1
	bne _0204B4E8
	ldr r0, [sp, #0x0]
	bl FUN_02058B7C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204B450
	cmp r0, #0x0
	beq _0204B4E8
	ldr r0, [sp, #0x0]
	add r1, r6, #0x0
	bl FUN_02058510
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r2, r7, #0x0
	bl FUN_020252C4
_0204B4E8:
	ldr r0, [r5, #0x34]
	add r1, sp, #0x0
	add r2, sp, #0x4
	mov r3, #0x1
	bl FUN_020580F4
	cmp r0, #0x1
	beq _0204B4B6
_0204B4F8:
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0204B4FC
FUN_0204B4FC: ; 0x0204B4FC
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r7, r1, #0x0
	bl FUN_02024ECC
	add r4, r0, #0x0
	add r0, r7, #0x0
	mov r1, #0x0
	bl FUN_02058510
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_02025244
	str r0, [sp, #0x4]
	ldr r1, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_020252E8
	add r6, r0, #0x0
	ldr r0, [sp, #0x4]
	bl FUN_0204B34C
	str r0, [sp, #0x8]
	ldr r1, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_02025268
	add r2, r0, #0x0
	lsl r2, r2, #0x18
	lsl r3, r6, #0x10
	ldr r1, [sp, #0x8]
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x10
	bl FUN_020616A4
	ldr r1, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_020252F4
	add r0, r7, #0x0
	bl FUN_0205C374
	ldr r0, [r5, #0xc]
	bl Save_Bag_Get
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	bl FUN_0204B34C
	lsl r2, r6, #0x10
	add r1, r0, #0x0
	add r0, r4, #0x0
	lsr r2, r2, #0x10
	mov r3, #0x4
	bl Bag_AddItem
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0204B57C
FUN_0204B57C: ; 0x0204B57C
	push {r4-r6, lr}
	ldr r0, [r0, #0xc]
	add r4, r1, #0x0
	add r5, r2, #0x0
	bl FUN_02024ECC
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02058510
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204B37C
	add r2, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_020252DC
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204B5A8
FUN_0204B5A8: ; 0x0204B5A8
	push {r3-r7, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02024ECC
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058510
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204B35C
	ldr r2, [r4, #0x4]
	add r3, r0, #0x0
	ldr r2, [r2, #0x18]
	add r0, r7, #0x0
	ldr r2, [r2, #0x4]
	add r1, r5, #0x0
	bl FUN_02025274
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0204B5DC
FUN_0204B5DC: ; 0x0204B5DC
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	bl FUN_02024ECC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058510
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020252AC
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204B5FC
FUN_0204B5FC: ; 0x0204B5FC
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	bl FUN_02024ECC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058510
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02025238
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204B61C
FUN_0204B61C: ; 0x0204B61C
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	bl FUN_02024ECC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058510
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02025244
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204B63C
FUN_0204B63C: ; 0x0204B63C
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	bl FUN_02024ECC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058510
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02025244
	bl FUN_0204B34C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204B660
FUN_0204B660: ; 0x0204B660
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	bl FUN_02024ECC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058510
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020252D0
	bl FUN_0204B36C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204B684
FUN_0204B684: ; 0x0204B684
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	bl FUN_02024ECC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058510
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0202524C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204B6A4
FUN_0204B6A4: ; 0x0204B6A4
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	bl FUN_02024ECC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058510
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020252E8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204B6C4
FUN_0204B6C4: ; 0x0204B6C4
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	ldr r4, _0204B708 ; =0x00000000
	beq _0204B6D8
	add r0, r5, #0x0
	bl FUN_02058458
	cmp r0, #0x64
	beq _0204B6DC
_0204B6D8:
	mov r0, #0x0
	pop {r4-r6, pc}
_0204B6DC:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0204B5FC
	cmp r0, #0x0
	bne _0204B6FE
	mov r0, #0x1
	orr r4, r0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0204B660
	cmp r0, #0x0
	bne _0204B702
	mov r0, #0x2
	orr r4, r0
	b _0204B702
_0204B6FE:
	mov r0, #0x4
	orr r4, r0
_0204B702:
	add r0, r4, #0x0
	pop {r4-r6, pc}
	nop
_0204B708: .word 0x00000000

	thumb_func_start FUN_0204B70C
FUN_0204B70C: ; 0x0204B70C
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, [r7, #0x38]
	add r5, r2, #0x0
	bl GetPlayerXCoord
	add r6, r0, #0x0
	ldr r0, [r7, #0x38]
	bl GetPlayerYCoord
	add r4, r0, #0x0
	cmp r5, #0x2
	bne _0204B72A
	sub r6, r6, #0x1
	b _0204B746
_0204B72A:
	cmp r5, #0x3
	bne _0204B732
	add r6, r6, #0x1
	b _0204B746
_0204B732:
	cmp r5, #0x0
	bne _0204B73A
	sub r4, r4, #0x1
	b _0204B746
_0204B73A:
	cmp r5, #0x1
	bne _0204B742
	add r4, r4, #0x1
	b _0204B746
_0204B742:
	bl GF_AssertFail
_0204B746:
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0204A6B4
	cmp r0, #0x0
	beq _0204B758
	mov r0, #0x1
	pop {r3-r7, pc}
_0204B758:
	ldr r0, [r7, #0x34]
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02058D74
	cmp r0, #0x0
	beq _0204B76A
	mov r0, #0x1
	pop {r3-r7, pc}
_0204B76A:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0204B770
FUN_0204B770: ; 0x0204B770
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x38]
	add r6, r1, #0x0
	bl GetPlayerXCoord
	add r4, r0, #0x0
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	add r2, r0, #0x0
	cmp r6, #0x2
	bne _0204B78E
	sub r4, r4, #0x1
	b _0204B794
_0204B78E:
	cmp r6, #0x3
	bne _0204B794
	add r4, r4, #0x1
_0204B794:
	ldr r0, [r5, #0x34]
	add r1, r4, #0x0
	sub r2, r2, #0x1
	bl FUN_02058D74
	pop {r4-r6, pc}

	thumb_func_start FUN_0204B7A0
FUN_0204B7A0: ; 0x0204B7A0
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x38]
	add r6, r1, #0x0
	bl GetPlayerXCoord
	add r7, r0, #0x0
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	add r4, r0, #0x0
	ldr r0, [r6, #0x4]
	cmp r0, #0x0
	bne _0204B7C0
	sub r4, r4, #0x1
	b _0204B7CC
_0204B7C0:
	cmp r0, #0x1
	bne _0204B7C8
	add r4, r4, #0x1
	b _0204B7CC
_0204B7C8:
	bl GF_AssertFail
_0204B7CC:
	ldr r0, [r5, #0x34]
	add r1, r7, #0x0
	add r2, r4, #0x0
	bl FUN_02058D74
	pop {r3-r7, pc}

	thumb_func_start FUN_0204B7D8
FUN_0204B7D8: ; 0x0204B7D8
	push {r3, lr}
	bl FUN_02058458
	cmp r0, #0x64
	bne _0204B7E6
	mov r0, #0x1
	pop {r3, pc}
_0204B7E6:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0204B7EC
FUN_0204B7EC: ; 0x0204B7EC
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0204B7A0
	add r1, r0, #0x0
	beq _0204B7FE
	add r0, r4, #0x0
	bl FUN_0204B5DC
_0204B7FE:
	pop {r4, pc}

	thumb_func_start FUN_0204B800
FUN_0204B800: ; 0x0204B800
	push {r3-r5, lr}
	ldr r0, [r0, #0x38]
	add r4, r2, #0x0
	add r5, r1, #0x0
	bl FUN_020553A0
	add r1, r4, #0x0
	bl FUN_0205AEA4
	str r0, [r5, #0xc]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204B818
FUN_0204B818: ; 0x0204B818
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x4
	bls _0204B832
	b _0204B98E
_0204B832:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0204B83E: ; jump table (using 16-bit offset)
	.short _0204B848 - _0204B83E - 2; case 0
	.short _0204B866 - _0204B83E - 2; case 1
	.short _0204B876 - _0204B83E - 2; case 2
	.short _0204B93A - _0204B83E - 2; case 3
	.short _0204B972 - _0204B83E - 2; case 4
_0204B848:
	ldr r0, [r5, #0x38]
	mov r1, #0x10
	bl MOD05_021E5FD8
	ldr r0, [r5, #0x38]
	bl MOD05_021E5FE0
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	bl FUN_02058914
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _0204B98E
_0204B866:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0204B7EC
	mov r0, #0x0
	str r0, [r4, #0x8]
	mov r0, #0x2
	str r0, [r4, #0x0]
_0204B876:
	ldr r0, _0204B994 ; =gSystem
	mov r1, #0x20
	ldr r0, [r0, #0x44]
	tst r1, r0
	beq _0204B8B8
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0204B770
	cmp r0, #0x0
	beq _0204B894
	bl FUN_0204B7D8
	cmp r0, #0x0
	bne _0204B89A
_0204B894:
	mov r0, #0x4
	str r0, [r4, #0x0]
	b _0204B98E
_0204B89A:
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x2
	bl FUN_0204B70C
	cmp r0, #0x0
	bne _0204B922
	ldr r2, _0204B998 ; =UNK_020F4850
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0204B800
	mov r0, #0x3
	str r0, [r4, #0x0]
	b _0204B98E
_0204B8B8:
	mov r1, #0x10
	tst r1, r0
	beq _0204B8F6
	add r0, r5, #0x0
	mov r1, #0x3
	bl FUN_0204B770
	cmp r0, #0x0
	beq _0204B8D2
	bl FUN_0204B7D8
	cmp r0, #0x0
	bne _0204B8D8
_0204B8D2:
	mov r0, #0x4
	str r0, [r4, #0x0]
	b _0204B98E
_0204B8D8:
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x3
	bl FUN_0204B70C
	cmp r0, #0x0
	bne _0204B922
	ldr r2, _0204B99C ; =UNK_020F4858
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0204B800
	mov r0, #0x3
	str r0, [r4, #0x0]
	b _0204B98E
_0204B8F6:
	mov r1, #0x40
	tst r1, r0
	beq _0204B910
	ldr r1, [r4, #0x4]
	cmp r1, #0x1
	bne _0204B910
	ldr r0, [r5, #0x38]
	mov r1, #0x0
	bl FUN_02055304
	mov r0, #0x4
	str r0, [r4, #0x0]
	b _0204B98E
_0204B910:
	mov r1, #0x80
	tst r0, r1
	beq _0204B922
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	bne _0204B922
	mov r0, #0x4
	str r0, [r4, #0x0]
	b _0204B98E
_0204B922:
	ldr r0, [r4, #0x8]
	add r0, r0, #0x1
	str r0, [r4, #0x8]
	cmp r0, #0x5a
	ble _0204B98E
	ldr r0, [r5, #0x38]
	ldr r1, [r4, #0x4]
	bl FUN_02055304
	mov r0, #0x4
	str r0, [r4, #0x0]
	b _0204B98E
_0204B93A:
	ldr r0, [r4, #0xc]
	bl FUN_0205AEF0
	cmp r0, #0x0
	beq _0204B98E
	ldr r0, [r4, #0xc]
	bl FUN_0205AEFC
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0204B7A0
	cmp r0, #0x0
	beq _0204B964
	bl FUN_0204B7D8
	cmp r0, #0x0
	beq _0204B964
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _0204B98E
_0204B964:
	ldr r0, [r5, #0x38]
	ldr r1, [r4, #0x4]
	bl FUN_02055304
	mov r0, #0x4
	str r0, [r4, #0x0]
	b _0204B98E
_0204B972:
	ldr r0, [r5, #0x38]
	ldr r1, [r4, #0x4]
	bl FUN_02055304
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	bl FUN_02058908
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0204B98E:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0204B994: .word gSystem
_0204B998: .word UNK_020F4850
_0204B99C: .word UNK_020F4858

	thumb_func_start FUN_0204B9A0
FUN_0204B9A0: ; 0x0204B9A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x20
	mov r1, #0x10
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r0, #0x0
	str r0, [r4, #0x0]
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetFacingDirection
	str r0, [r4, #0x4]
	ldr r0, [r5, #0x10]
	ldr r1, _0204B9C8 ; =FUN_0204B818
	add r2, r4, #0x0
	bl FUN_0204640C
	pop {r3-r5, pc}
	.balign 4
_0204B9C8: .word FUN_0204B818

	thumb_func_start FUN_0204B9CC
FUN_0204B9CC: ; 0x0204B9CC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetState
	bl FUN_02055648
	add r1, r0, #0x0
	ldr r0, [r4, #0x38]
	bl MOD05_021E5FD8
	ldr r0, [r4, #0x38]
	bl MOD05_021E5FE0
	pop {r4, pc}
	.balign 4
