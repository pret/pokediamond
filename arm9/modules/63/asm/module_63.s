	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD63_021D74E0
MOD63_021D74E0: ; 0x021D74E0
	push {r4, lr}
	ldr r1, _021D7584 ; =0x00007FFF
	add r4, r0, #0
	mov r0, #0
	bl FUN_0200E3A0
	ldr r1, _021D7584 ; =0x00007FFF
	mov r0, #1
	bl FUN_0200E3A0
	ldr r1, _021D7588 ; =0x04001050
	mov r0, #0
	strh r0, [r1]
	ldr r1, _021D758C ; =0x04000050
	strh r0, [r1]
	add r1, r0, #0
	bl FUN_02015F10
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F34
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D7590 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D7594 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	mov r2, #1
	mov r0, #3
	mov r1, #0x1e
	lsl r2, r2, #0x12
	bl FUN_0201681C
	mov r1, #0x79
	add r0, r4, #0
	lsl r1, r1, #2
	mov r2, #0x1e
	bl FUN_02006268
	mov r2, #0x79
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl memset
	mov r0, #0x1e
	str r0, [r4]
	mov r0, #0x1d
	mov r1, #0
	lsl r0, r0, #4
	strh r1, [r4, r0]
	add r0, #0x10
	str r1, [r4, r0]
	bl MOD63_021D7838
	add r0, r4, #0
	bl MOD63_021D7A48
	add r0, r4, #0
	bl MOD63_021D7880
	ldr r0, _021D7598 ; =MOD63_021D782C
	add r1, r4, #0
	bl FUN_02015F10
	bl FUN_0201E788
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_021D7584: .word 0x00007FFF
_021D7588: .word 0x04001050
_021D758C: .word 0x04000050
_021D7590: .word 0xFFFFE0FF
_021D7594: .word 0x04001000
_021D7598: .word MOD63_021D782C
	thumb_func_end MOD63_021D74E0

	thumb_func_start MOD63_021D759C
MOD63_021D759C: ; 0x021D759C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	bl FUN_02006278
	add r4, r0, #0
	ldr r0, [r5]
	cmp r0, #6
	bhi _021D7614
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D75BA: ; jump table
	.short _021D75C8 - _021D75BA - 2 ; case 0
	.short _021D7604 - _021D75BA - 2 ; case 1
	.short _021D7622 - _021D75BA - 2 ; case 2
	.short _021D7638 - _021D75BA - 2 ; case 3
	.short _021D76FA - _021D75BA - 2 ; case 4
	.short _021D773C - _021D75BA - 2 ; case 5
	.short _021D777E - _021D75BA - 2 ; case 6
_021D75C8:
	add r0, r4, #0
	ldr r1, [r4, #4]
	ldr r2, [r4]
	add r0, #0xb4
	bl MOD63_021D7C18
	cmp r0, #1
	bne _021D7614
	add r0, r4, #0
	ldr r1, _021D77A4 ; =gUnknown21C48B8
	mov r2, #0
	add r0, #0xb4
	str r2, [r0]
	ldr r0, [r1, #0x6c]
	cmp r0, #0
	bne _021D75F6
	mov r0, #0x75
	mov r1, #0x1e
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #2
	str r0, [r5]
	b _021D779C
_021D75F6:
	mov r0, #0x75
	lsl r0, r0, #2
	str r2, [r4, r0]
	str r2, [r1, #0x6c]
	mov r0, #1
	str r0, [r5]
	b _021D779C
_021D7604:
	add r0, r4, #0
	ldr r1, [r4, #4]
	ldr r2, [r4]
	add r0, #0xb4
	bl MOD63_021D7D74
	cmp r0, #1
	beq _021D7616
_021D7614:
	b _021D779C
_021D7616:
	mov r0, #0
	add r4, #0xb4
	str r0, [r4]
	mov r0, #2
	str r0, [r5]
	b _021D779C
_021D7622:
	mov r0, #0
	bl FUN_0200415C
	mov r0, #1
	ldr r1, _021D77A8 ; =0x00000495
	add r2, r0, #0
	bl FUN_0200433C
	mov r0, #3
	str r0, [r5]
	b _021D779C
_021D7638:
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _021D765A
	sub r1, r1, #1
	str r1, [r4, r0]
	mov r1, #0
	sub r0, #0x4c
	str r1, [r4, r0]
	add r0, r4, #0
	ldr r1, [r4, #4]
	ldr r2, [r4]
	add r0, #0xb4
	bl MOD63_021D8260
	b _021D779C
_021D765A:
	mov r1, #1
	sub r0, #0x4c
	str r1, [r4, r0]
	add r0, r4, #0
	ldr r1, [r4, #4]
	ldr r2, [r4]
	add r0, #0xb4
	bl MOD63_021D8260
	mov r1, #0x1e
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	ldr r2, _021D77A4 ; =gUnknown21C48B8
	add r0, r0, #1
	str r0, [r4, r1]
	ldr r3, [r2, #0x48]
	mov r0, #1
	add r6, r3, #0
	and r6, r0
	cmp r6, #1
	beq _021D768C
	mov r6, #8
	and r3, r6
	cmp r3, #8
	bne _021D76A8
_021D768C:
	mov r0, #0x1d
	mov r1, #1
	lsl r0, r0, #4
	strh r1, [r4, r0]
	mov r0, #0
	mov r1, #0x3c
	bl FUN_020053CC
	ldr r0, _021D77AC ; =0x000005F4
	bl FUN_020054C8
	mov r0, #4
	str r0, [r5]
	b _021D779C
_021D76A8:
	ldr r6, [r2, #0x44]
	mov r3, #0x46
	and r3, r6
	cmp r3, #0x46
	bne _021D76D4
	mov r2, #2
	sub r1, #0x10
	strh r2, [r4, r1]
	mov r1, #6
	str r1, [sp]
	str r0, [sp, #4]
	ldr r0, [r4]
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #6
	str r0, [r5]
	b _021D779C
_021D76D4:
	mov r3, #0xe1
	ldr r6, [r4, r1]
	lsl r3, r3, #2
	cmp r6, r3
	ble _021D779C
	mov r3, #3
	sub r1, #0x10
	strh r3, [r4, r1]
	mov r1, #0
	str r0, [r2, #0x6c]
	bl FUN_0201E74C
	mov r0, #0
	mov r1, #0x3c
	bl FUN_020053CC
	mov r0, #5
	str r0, [r5]
	b _021D779C
_021D76FA:
	mov r0, #0x62
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	ldr r1, [r4, #4]
	ldr r2, [r4]
	add r0, #0xb4
	bl MOD63_021D8260
	bl FUN_02005404
	cmp r0, #0
	bne _021D779C
	ldr r0, _021D77A8 ; =0x00000495
	mov r1, #0
	bl FUN_02005350
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #6
	str r0, [r5]
	b _021D779C
_021D773C:
	mov r0, #0x62
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	ldr r1, [r4, #4]
	ldr r2, [r4]
	add r0, #0xb4
	bl MOD63_021D8260
	bl FUN_02005404
	cmp r0, #0
	bne _021D779C
	ldr r0, _021D77A8 ; =0x00000495
	mov r1, #0
	bl FUN_02005350
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	ldr r3, _021D77B0 ; =0x00007FFF
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	bl FUN_0200E1D0
	mov r0, #6
	str r0, [r5]
	b _021D779C
_021D777E:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D779C
	add r0, r4, #0
	ldr r1, [r4, #4]
	ldr r2, [r4]
	add r0, #0xb4
	bl MOD63_021D8360
	cmp r0, #1
	bne _021D779C
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D779C:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021D77A4: .word gUnknown21C48B8
_021D77A8: .word 0x00000495
_021D77AC: .word 0x000005F4
_021D77B0: .word 0x00007FFF
	thumb_func_end MOD63_021D759C

	thumb_func_start MOD63_021D77B4
MOD63_021D77B4: ; 0x021D77B4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	bl FUN_02006278
	add r6, r0, #0
	mov r0, #0x1d
	lsl r0, r0, #4
	ldrh r5, [r6, r0]
	mov r0, #0
	add r1, r0, #0
	ldr r4, [r6]
	bl FUN_02015F10
	add r0, r6, #0
	bl MOD63_021D78B0
	add r0, r6, #0
	bl MOD63_021D7B9C
	add r0, r7, #0
	bl FUN_0200627C
	add r0, r4, #0
	bl FUN_020168D0
	cmp r5, #1
	beq _021D77F2
	cmp r5, #2
	beq _021D77FE
	cmp r5, #3
	beq _021D780A
_021D77F2:
	mov r0, #0
	ldr r1, _021D781C ; =UNK_020FF3D4
	mvn r0, r0
	bl FUN_02000E7C
	b _021D7818
_021D77FE:
	mov r0, #0
	ldr r1, _021D7820 ; =UNK_020FF368
	mvn r0, r0
	bl FUN_02000E7C
	b _021D7818
_021D780A:
	mov r0, #0
	bl FUN_0200415C
	ldr r0, _021D7824 ; =SDK_OVERLAY_MODULE_63_ID
	ldr r1, _021D7828 ; =MOD63_UNK_021DBE18
	bl FUN_02000E7C
_021D7818:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D781C: .word UNK_020FF3D4
_021D7820: .word UNK_020FF368
_021D7824: .word SDK_OVERLAY_MODULE_63_ID
_021D7828: .word MOD63_UNK_021DBE18
	thumb_func_end MOD63_021D77B4

	thumb_func_start MOD63_021D782C
MOD63_021D782C: ; 0x021D782C
	ldr r3, _021D7834 ; =FUN_0201AB60
	ldr r0, [r0, #4]
	bx r3
	nop
_021D7834: .word FUN_0201AB60
	thumb_func_end MOD63_021D782C

	thumb_func_start MOD63_021D7838
MOD63_021D7838: ; 0x021D7838
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D7854 ; =MOD63_021DBA90
	add r3, sp, #0
	mov r2, #5
_021D7842:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7842
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D7854: .word MOD63_021DBA90
	thumb_func_end MOD63_021D7838

	thumb_func_start MOD63_021D7858
MOD63_021D7858: ; 0x021D7858
	ldr r0, _021D787C ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #1
	and r0, r1
	cmp r0, #1
	beq _021D7874
	mov r0, #8
	and r0, r1
	cmp r0, #8
	beq _021D7874
	mov r0, #4
	and r0, r1
	cmp r0, #4
	bne _021D7878
_021D7874:
	mov r0, #1
	bx lr
_021D7878:
	mov r0, #0
	bx lr
	.align 2, 0
_021D787C: .word gUnknown21C48B8
	thumb_func_end MOD63_021D7858

	thumb_func_start MOD63_021D7880
MOD63_021D7880: ; 0x021D7880
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #4
	mov r1, #0
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r4]
	mov r2, #1
	add r3, r1, #0
	bl FUN_02022318
	str r0, [r4, #8]
	ldr r1, _021D78AC ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #1
	orr r0, r2
	strh r0, [r1]
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_021D78AC: .word 0x04000008
	thumb_func_end MOD63_021D7880

	thumb_func_start MOD63_021D78B0
MOD63_021D78B0: ; 0x021D78B0
	ldr r3, _021D78B8 ; =FUN_020223BC
	ldr r0, [r0, #8]
	bx r3
	nop
_021D78B8: .word FUN_020223BC
	thumb_func_end MOD63_021D78B0

	thumb_func_start MOD63_021D78BC
MOD63_021D78BC: ; 0x021D78BC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r3, #0
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	add r0, #0x68
	add r1, r4, #0
	mov r2, #4
	bl FUN_02016B20
	mov r0, #0x30
	add r1, r6, #0
	add r2, r4, #0
	bl AllocAndReadWholeNarcMemberByIdPair
	str r0, [r5, #0x5c]
	mov r0, #0x30
	add r1, r7, #0
	add r2, r4, #0
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, r5, #0
	add r2, r5, #0
	str r0, [r5, #0x60]
	add r0, r5, #4
	add r1, #0x58
	add r2, #0x5c
	bl FUN_0201B234
	ldr r0, [r5, #0x60]
	mov r1, #0
	bl FUN_020BC4C8
	add r4, r0, #0
	add r0, r5, #0
	ldr r2, [r5, #0x58]
	add r0, #0x68
	add r1, r4, #0
	bl FUN_020BB8D0
	str r0, [r5, #0x64]
	ldr r0, [r5, #0x5c]
	bl FUN_020BC0FC
	add r3, r0, #0
	ldr r0, [r5, #0x64]
	ldr r2, [r5, #0x58]
	add r1, r4, #0
	bl FUN_020B8110
	ldr r1, [r5, #0x64]
	add r0, r5, #4
	bl FUN_020B7EFC
	add r4, r5, #0
	add r6, sp, #0xc
	mov r3, #0
	str r3, [r6]
	add r2, sp, #0
	str r3, [r6, #4]
	str r3, [r2]
	str r3, [r6, #8]
	str r3, [r2, #4]
	ldmia r6!, {r0, r1}
	str r3, [r2, #8]
	add r4, #0x78
	stmia r4!, {r0, r1}
	ldr r0, [r6]
	ldr r6, _021D796C ; =MOD63_021DB9A8
	str r0, [r4]
	add r4, r5, #0
	ldmia r6!, {r0, r1}
	add r4, #0x84
	stmia r4!, {r0, r1}
	ldr r0, [r6]
	str r0, [r4]
	add r4, r5, #0
	ldmia r2!, {r0, r1}
	add r4, #0x90
	stmia r4!, {r0, r1}
	ldr r0, [r2]
	add r5, #0xa0
	str r0, [r4]
	str r3, [r5]
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D796C: .word MOD63_021DB9A8
	thumb_func_end MOD63_021D78BC

	thumb_func_start MOD63_021D7970
MOD63_021D7970: ; 0x021D7970
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x64]
	add r0, #0x68
	bl thunk_FUN_020ae84c
	ldr r0, [r4, #0x60]
	bl FreeToHeap
	ldr r0, [r4, #0x5c]
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD63_021D7970

	thumb_func_start MOD63_021D798C
MOD63_021D798C: ; 0x021D798C
	push {r4, r5, lr}
	sub sp, #0x24
	ldr r5, _021D7A44 ; =MOD63_021DBA6C
	add r4, r0, #0
	add r3, sp, #0
	mov r2, #4
_021D7998:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7998
	ldr r0, [r5]
	str r0, [r3]
	ldr r0, [r4]
	cmp r0, #0
	beq _021D7A3E
	cmp r0, #1
	beq _021D79B6
	cmp r0, #2
	beq _021D79CA
	add sp, #0x24
	pop {r4, r5, pc}
_021D79B6:
	bl FUN_020222AC
	mov r0, #0
	mov r1, #1
	bl FUN_020222B4
	mov r0, #0
	add sp, #0x24
	str r0, [r4]
	pop {r4, r5, pc}
_021D79CA:
	bl FUN_020222AC
	bl FUN_0201EBA4
	add r1, r4, #0
	add r0, sp, #0
	add r1, #0x90
	bl FUN_0201CAA8
	add r1, r4, #0
	add r3, r4, #0
	add r0, r4, #4
	add r1, #0x78
	add r2, sp, #0
	add r3, #0x84
	bl FUN_0201B26C
	add r0, r4, #0
	add r0, #0xa0
	ldr r0, [r0]
	cmp r0, #0
	beq _021D7A00
	cmp r0, #1
	beq _021D7A08
	cmp r0, #2
	beq _021D7A18
	b _021D7A36
_021D7A00:
	ldr r0, [r4, #0x64]
	mov r1, #0
	str r1, [r0]
	b _021D7A36
_021D7A08:
	ldr r0, [r4, #0x64]
	ldr r0, [r0]
	cmp r0, #0
	bne _021D7A18
	mov r0, #0
	add r4, #0xa0
	str r0, [r4]
	b _021D7A36
_021D7A18:
	ldr r2, [r4, #0x64]
	mov r0, #1
	ldr r1, [r2]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [r2]
	ldr r2, [r4, #0x64]
	ldr r0, [r2, #8]
	ldr r1, [r2]
	ldrh r0, [r0, #4]
	lsl r0, r0, #0xc
	cmp r1, r0
	bne _021D7A36
	mov r0, #0
	str r0, [r2]
_021D7A36:
	mov r0, #0
	mov r1, #1
	bl FUN_020222B4
_021D7A3E:
	add sp, #0x24
	pop {r4, r5, pc}
	nop
_021D7A44: .word MOD63_021DBA6C
	thumb_func_end MOD63_021D798C

	thumb_func_start MOD63_021D7A48
MOD63_021D7A48: ; 0x021D7A48
	push {r3, r4, r5, lr}
	sub sp, #0xb8
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_02016B94
	add r3, sp, #0xa8
	ldr r5, _021D7B80 ; =MOD63_021DB9B4
	str r0, [r4, #4]
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _021D7B84 ; =MOD63_021DB9E0
	add r3, sp, #0x8c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #4
	str r0, [r3]
	ldr r0, [r4, #4]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D7B88 ; =MOD63_021DB9C4
	add r3, sp, #0x70
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #5
	str r0, [r3]
	ldr r0, [r4, #4]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D7B8C ; =MOD63_021DBA50
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #6
	str r0, [r3]
	ldr r0, [r4, #4]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D7B90 ; =MOD63_021DBA34
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	ldr r0, [r4, #4]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D7B94 ; =MOD63_021DB9FC
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	ldr r0, [r4, #4]
	mov r1, #3
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D7B98 ; =MOD63_021DBA18
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #7
	str r0, [r3]
	ldr r0, [r4, #4]
	mov r3, #0
	bl FUN_02016C18
	mov r0, #1
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #2
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #4
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #8
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #1
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #2
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #4
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #8
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #0
	add r1, r0, #0
	bl FUN_02017FE4
	mov r0, #4
	mov r1, #0
	bl FUN_02017FE4
	add sp, #0xb8
	pop {r3, r4, r5, pc}
	nop
_021D7B80: .word MOD63_021DB9B4
_021D7B84: .word MOD63_021DB9E0
_021D7B88: .word MOD63_021DB9C4
_021D7B8C: .word MOD63_021DBA50
_021D7B90: .word MOD63_021DBA34
_021D7B94: .word MOD63_021DB9FC
_021D7B98: .word MOD63_021DBA18
	thumb_func_end MOD63_021D7A48

	thumb_func_start MOD63_021D7B9C
MOD63_021D7B9C: ; 0x021D7B9C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #2
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #4
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #8
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #1
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #2
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #4
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #8
	mov r1, #0
	bl FUN_0201E74C
	ldr r0, [r4, #4]
	mov r1, #4
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #5
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #7
	bl FUN_020178A0
	ldr r0, [r4, #4]
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD63_021D7B9C

	thumb_func_start MOD63_021D7C18
MOD63_021D7C18: ; 0x021D7C18
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	bl MOD63_021D86E0
	add r0, r6, #0
	add r1, r4, #0
	add r2, r5, #0
	bl MOD63_021D83A8
	ldr r0, _021D7D5C ; =gGameVersion
	ldrb r0, [r0]
	cmp r0, #0xa
	bne _021D7C46
	add r0, r5, #4
	mov r1, #6
	mov r2, #0x13
	add r3, r4, #0
	bl MOD63_021D78BC
	b _021D7C52
_021D7C46:
	add r0, r5, #4
	mov r1, #5
	mov r2, #0x12
	add r3, r4, #0
	bl MOD63_021D78BC
_021D7C52:
	ldr r0, _021D7D60 ; =0x04000060
	ldr r2, _021D7D64 ; =0xFFFFCFFF
	ldrh r1, [r0]
	add r3, r1, #0
	and r3, r2
	mov r1, #0x10
	orr r1, r3
	strh r1, [r0]
	ldrh r1, [r0]
	and r2, r1
	mov r1, #8
	orr r1, r2
	strh r1, [r0]
	add r0, r5, #0
	add r0, #0xf0
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xbc
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xf4
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xc0
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xf8
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xc4
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xd8
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xc8
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xdc
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xcc
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xe0
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xd0
	str r1, [r0]
	add r0, r4, #0
	bl FUN_0201EB64
	add r1, r5, #0
	add r1, #0xa0
	str r0, [r1]
	mov r3, #0
	add r0, r5, #0
	add r1, r5, #0
	mov r2, #0xb6
	str r3, [sp]
	add r0, #0xa0
	ldr r0, [r0]
	add r1, #0xc8
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xbc
	lsl r2, r2, #4
	bl FUN_0201ED5C
	add r2, r5, #0
	add r2, #0xa0
	mov r1, #0x19
	ldr r2, [r2]
	mov r0, #0
	lsl r1, r1, #0xe
	bl FUN_0201EC94
	add r1, r5, #0
	add r1, #0xa0
	ldr r1, [r1]
	mov r0, #0
	bl FUN_0201EE2C
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	bl FUN_0201EB8C
	mov r3, #0x42
	lsl r3, r3, #2
	add r2, r3, #2
	ldrsh r1, [r5, r3]
	add r3, r3, #4
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	mov r0, #0
	bl FUN_020B8418
	ldr r1, _021D7D68 ; =0x00007FFF
	mov r0, #0
	bl FUN_020B8404
	ldr r3, _021D7D6C ; =0x0000010E
	mov r0, #1
	add r2, r3, #2
	ldrsh r1, [r5, r3]
	add r3, r3, #4
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	bl FUN_020B8418
	ldr r1, _021D7D68 ; =0x00007FFF
	mov r0, #1
	bl FUN_020B8404
	ldr r2, _021D7D60 ; =0x04000060
	ldr r0, _021D7D64 ; =0xFFFFCFFF
	ldrh r1, [r2]
	and r1, r0
	mov r0, #0x10
	orr r0, r1
	strh r0, [r2]
	ldr r0, _021D7D70 ; =gUnk021C4918
	mov r1, #1
	strb r1, [r0, #5]
	bl FUN_0201E7A0
	mov r0, #2
	str r0, [r5, #4]
	mov r0, #1
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_021D7D5C: .word gGameVersion
_021D7D60: .word 0x04000060
_021D7D64: .word 0xFFFFCFFF
_021D7D68: .word 0x00007FFF
_021D7D6C: .word 0x0000010E
_021D7D70: .word gUnk021C4918
	thumb_func_end MOD63_021D7C18

	thumb_func_start MOD63_021D7D74
MOD63_021D7D74: ; 0x021D7D74
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r7, r1, #0
	add r5, r2, #0
	mov r6, #0
	bl MOD63_021D7858
	cmp r0, #1
	bne _021D7D92
	bl FUN_0200E31C
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021D7D92:
	ldr r0, [r4]
	cmp r0, #9
	bhi _021D7E38
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D7DA4: ; jump table
	.short _021D7DB8 - _021D7DA4 - 2 ; case 0
	.short _021D7DF6 - _021D7DA4 - 2 ; case 1
	.short _021D7E24 - _021D7DA4 - 2 ; case 2
	.short _021D7E8C - _021D7DA4 - 2 ; case 3
	.short _021D7ECC - _021D7DA4 - 2 ; case 4
	.short _021D7EF4 - _021D7DA4 - 2 ; case 5
	.short _021D7F44 - _021D7DA4 - 2 ; case 6
	.short _021D7F72 - _021D7DA4 - 2 ; case 7
	.short _021D7FA6 - _021D7DA4 - 2 ; case 8
	.short _021D8232 - _021D7DA4 - 2 ; case 9
_021D7DB8:
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	mov r0, #8
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #2
	mov r1, #1
	bl FUN_0201E74C
	ldr r1, _021D80F0 ; =0x00000116
	add r0, r6, #0
	strh r0, [r4, r1]
	add r1, r4, #0
	mov r2, #0xf
	add r1, #0xa8
	strh r2, [r1]
	str r2, [sp]
	mov r1, #3
	str r1, [sp, #4]
	mov r1, #1
	ldr r3, _021D80F4 ; =0x00007FFF
	add r2, r1, #0
	str r5, [sp, #8]
	bl FUN_0200E1D0
	mov r0, #1
	str r0, [r4]
	b _021D824E
_021D7DF6:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D7E38
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0
	beq _021D7E18
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xa8
	strh r1, [r0]
	b _021D824E
_021D7E18:
	add r0, r4, #0
	mov r1, #2
	add r0, #0xa8
	strh r1, [r0]
	str r1, [r4]
	b _021D824E
_021D7E24:
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #1
	bne _021D7E38
	mov r0, #2
	bl FUN_0200A344
	cmp r0, #1
	beq _021D7E3A
_021D7E38:
	b _021D824E
_021D7E3A:
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0
	beq _021D7E7E
	mov r0, #1
	str r0, [sp]
	mov r0, #0xa
	mov r1, #0x10
	add r2, r6, #0
	mov r3, #6
	bl FUN_0200A208
	mov r0, #2
	str r0, [sp]
	mov r0, #0xa
	mov r1, #0x10
	add r2, r6, #0
	mov r3, #7
	bl FUN_0200A208
	ldr r0, _021D80F0 ; =0x00000116
	mov r1, #2
	strh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xa8
	strh r1, [r0]
	mov r0, #3
	str r0, [r4]
	b _021D824E
_021D7E7E:
	add r0, r4, #0
	add r1, r6, #0
	add r0, #0xa8
	strh r1, [r0]
	mov r0, #4
	str r0, [r4]
	b _021D824E
_021D7E8C:
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #1
	bne _021D7F94
	mov r0, #2
	bl FUN_0200A344
	cmp r0, #1
	bne _021D7F94
	mov r0, #1
	str r0, [sp]
	mov r0, #0xa
	add r1, r6, #0
	mov r2, #0x10
	mov r3, #6
	bl FUN_0200A208
	mov r0, #2
	str r0, [sp]
	mov r0, #0xa
	add r1, r6, #0
	mov r2, #0x10
	mov r3, #7
	bl FUN_0200A208
	ldr r0, _021D80F0 ; =0x00000116
	mov r1, #3
	strh r1, [r4, r0]
	mov r0, #2
	str r0, [r4]
	b _021D824E
_021D7ECC:
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0
	beq _021D7EE6
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xa8
	strh r1, [r0]
	b _021D824E
_021D7EE6:
	add r0, r4, #0
	mov r1, #1
	add r0, #0xa8
	strh r1, [r0]
	mov r0, #5
	str r0, [r4]
	b _021D824E
_021D7EF4:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D7F94
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0
	beq _021D7F36
	mov r0, #5
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	add r0, r6, #0
	ldr r3, _021D80F4 ; =0x00007FFF
	add r1, r0, #0
	add r2, r0, #0
	str r5, [sp, #8]
	bl FUN_0200E1D0
	ldr r0, _021D80F0 ; =0x00000116
	mov r1, #2
	strh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xa8
	strh r1, [r0]
	mov r0, #6
	str r0, [r4]
	b _021D824E
_021D7F36:
	add r0, r4, #0
	mov r1, #0x28
	add r0, #0xa8
	strh r1, [r0]
	mov r0, #7
	str r0, [r4]
	b _021D824E
_021D7F44:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D7F94
	add r0, r7, #0
	add r1, r5, #0
	add r2, r4, #0
	bl MOD63_021D85D8
	mov r0, #0x10
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r1, #1
	ldr r3, _021D80F4 ; =0x00007FFF
	add r0, r6, #0
	add r2, r1, #0
	str r5, [sp, #8]
	bl FUN_0200E1D0
	mov r0, #5
	str r0, [r4]
	b _021D824E
_021D7F72:
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0
	beq _021D7FA0
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xa8
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0xf
	beq _021D7F96
_021D7F94:
	b _021D824E
_021D7F96:
	add r0, r4, #0
	mov r1, #2
	add r0, #0xa4
	str r1, [r0]
	b _021D824E
_021D7FA0:
	mov r0, #8
	str r0, [r4]
	b _021D824E
_021D7FA6:
	add r0, r4, #0
	add r0, #0xfc
	ldr r2, [r0]
	add r0, r4, #0
	add r0, #0xbc
	ldr r1, [r0]
	mov r5, #1
	cmp r1, r2
	ble _021D7FDE
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r1, r2
	cmp r1, r0
	ble _021D7FD4
	add r1, r4, #0
	add r1, #0xbc
	ldr r1, [r1]
	sub r1, r1, r0
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	b _021D7FDA
_021D7FD4:
	add r0, r4, #0
	add r0, #0xbc
	str r2, [r0]
_021D7FDA:
	mov r5, #0
	b _021D8006
_021D7FDE:
	cmp r1, r2
	bge _021D8006
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r2, r1
	cmp r1, r0
	ble _021D7FFE
	add r1, r4, #0
	add r1, #0xbc
	ldr r1, [r1]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	b _021D8004
_021D7FFE:
	add r0, r4, #0
	add r0, #0xbc
	str r2, [r0]
_021D8004:
	mov r5, #0
_021D8006:
	mov r0, #1
	add r1, r4, #0
	lsl r0, r0, #8
	add r1, #0xc0
	ldr r2, [r4, r0]
	ldr r1, [r1]
	cmp r1, r2
	ble _021D803A
	add r0, #0x18
	ldr r0, [r4, r0]
	sub r1, r1, r2
	cmp r1, r0
	ble _021D8030
	add r1, r4, #0
	add r1, #0xc0
	ldr r1, [r1]
	sub r1, r1, r0
	add r0, r4, #0
	add r0, #0xc0
	str r1, [r0]
	b _021D8036
_021D8030:
	add r0, r4, #0
	add r0, #0xc0
	str r2, [r0]
_021D8036:
	mov r5, #0
	b _021D8060
_021D803A:
	cmp r1, r2
	bge _021D8060
	add r0, #0x18
	ldr r0, [r4, r0]
	sub r1, r2, r1
	cmp r1, r0
	ble _021D8058
	add r1, r4, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0xc0
	str r1, [r0]
	b _021D805E
_021D8058:
	add r0, r4, #0
	add r0, #0xc0
	str r2, [r0]
_021D805E:
	mov r5, #0
_021D8060:
	mov r0, #0x41
	add r1, r4, #0
	lsl r0, r0, #2
	add r1, #0xc4
	ldr r2, [r4, r0]
	ldr r1, [r1]
	cmp r1, r2
	ble _021D8094
	add r0, #0x14
	ldr r0, [r4, r0]
	sub r1, r1, r2
	cmp r1, r0
	ble _021D808A
	add r1, r4, #0
	add r1, #0xc4
	ldr r1, [r1]
	sub r1, r1, r0
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	b _021D8090
_021D808A:
	add r0, r4, #0
	add r0, #0xc4
	str r2, [r0]
_021D8090:
	mov r5, #0
	b _021D80BA
_021D8094:
	cmp r1, r2
	bge _021D80BA
	add r0, #0x14
	ldr r0, [r4, r0]
	sub r1, r2, r1
	cmp r1, r0
	ble _021D80B2
	add r1, r4, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	b _021D80B8
_021D80B2:
	add r0, r4, #0
	add r0, #0xc4
	str r2, [r0]
_021D80B8:
	mov r5, #0
_021D80BA:
	add r0, r4, #0
	add r0, #0xe4
	ldr r2, [r0]
	add r0, r4, #0
	add r0, #0xc8
	ldr r1, [r0]
	cmp r1, r2
	ble _021D80F8
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r1, r2
	cmp r1, r0
	ble _021D80E6
	add r1, r4, #0
	add r1, #0xc8
	ldr r1, [r1]
	sub r1, r1, r0
	add r0, r4, #0
	add r0, #0xc8
	str r1, [r0]
	b _021D80EC
_021D80E6:
	add r0, r4, #0
	add r0, #0xc8
	str r2, [r0]
_021D80EC:
	mov r5, #0
	b _021D8120
	.align 2, 0
_021D80F0: .word 0x00000116
_021D80F4: .word 0x00007FFF
_021D80F8:
	cmp r1, r2
	bge _021D8120
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r2, r1
	cmp r1, r0
	ble _021D8118
	add r1, r4, #0
	add r1, #0xc8
	ldr r1, [r1]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0xc8
	str r1, [r0]
	b _021D811E
_021D8118:
	add r0, r4, #0
	add r0, #0xc8
	str r2, [r0]
_021D811E:
	mov r5, #0
_021D8120:
	add r0, r4, #0
	add r0, #0xe8
	ldr r2, [r0]
	add r0, r4, #0
	add r0, #0xcc
	ldr r1, [r0]
	cmp r1, r2
	ble _021D8156
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r1, r2
	cmp r1, r0
	ble _021D814C
	add r1, r4, #0
	add r1, #0xcc
	ldr r1, [r1]
	sub r1, r1, r0
	add r0, r4, #0
	add r0, #0xcc
	str r1, [r0]
	b _021D8152
_021D814C:
	add r0, r4, #0
	add r0, #0xcc
	str r2, [r0]
_021D8152:
	mov r5, #0
	b _021D817E
_021D8156:
	cmp r1, r2
	bge _021D817E
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r2, r1
	cmp r1, r0
	ble _021D8176
	add r1, r4, #0
	add r1, #0xcc
	ldr r1, [r1]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0xcc
	str r1, [r0]
	b _021D817C
_021D8176:
	add r0, r4, #0
	add r0, #0xcc
	str r2, [r0]
_021D817C:
	mov r5, #0
_021D817E:
	add r0, r4, #0
	add r0, #0xec
	ldr r2, [r0]
	add r0, r4, #0
	add r0, #0xd0
	ldr r1, [r0]
	cmp r1, r2
	ble _021D81B4
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r1, r2
	cmp r1, r0
	ble _021D81AA
	add r1, r4, #0
	add r1, #0xd0
	ldr r1, [r1]
	sub r1, r1, r0
	add r0, r4, #0
	add r0, #0xd0
	str r1, [r0]
	b _021D81B0
_021D81AA:
	add r0, r4, #0
	add r0, #0xd0
	str r2, [r0]
_021D81B0:
	mov r5, #0
	b _021D81DC
_021D81B4:
	cmp r1, r2
	bge _021D81DC
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r2, r1
	cmp r1, r0
	ble _021D81D4
	add r1, r4, #0
	add r1, #0xd0
	ldr r1, [r1]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0xd0
	str r1, [r0]
	b _021D81DA
_021D81D4:
	add r0, r4, #0
	add r0, #0xd0
	str r2, [r0]
_021D81DA:
	mov r5, #0
_021D81DC:
	add r1, r4, #0
	add r1, #0xa0
	add r0, r4, #0
	ldr r1, [r1]
	add r0, #0xbc
	bl FUN_0201F04C
	add r1, r4, #0
	add r1, #0xa0
	add r0, r4, #0
	ldr r1, [r1]
	add r0, #0xc8
	bl FUN_0201F05C
	cmp r5, #1
	bne _021D824E
	mov r0, #4
	mov r1, #1
	bl FUN_0201E74C
	mov r0, #2
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #2
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #8
	mov r1, #1
	bl FUN_0201E74C
	add r0, r4, #0
	mov r1, #0x5a
	add r0, #0xa8
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #1
	add r0, #0xa4
	str r1, [r0]
	mov r0, #9
	str r0, [r4]
	b _021D824E
_021D8232:
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0
	beq _021D824C
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xa8
	strh r1, [r0]
	b _021D824E
_021D824C:
	mov r6, #1
_021D824E:
	add r0, r4, #0
	bl MOD63_021D8650
	add r0, r4, #4
	bl MOD63_021D798C
	add r0, r6, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD63_021D7D74

	thumb_func_start MOD63_021D8260
MOD63_021D8260: ; 0x021D8260
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	mov r4, #0
	cmp r0, #0
	beq _021D8272
	cmp r0, #1
	beq _021D82FC
	b _021D8350
_021D8272:
	add r1, r5, #0
	add r1, #0xa0
	add r0, r5, #0
	ldr r1, [r1]
	add r0, #0xfc
	bl FUN_0201F04C
	add r1, r5, #0
	add r1, #0xa0
	add r0, r5, #0
	ldr r1, [r1]
	add r0, #0xe4
	bl FUN_0201F05C
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	mov r0, #8
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #8
	mov r1, #1
	bl FUN_0201E74C
	mov r0, #4
	mov r1, #1
	bl FUN_0201E74C
	mov r0, #2
	add r1, r4, #0
	bl FUN_0201E74C
	mov r0, #2
	mov r1, #1
	bl FUN_0201E6E4
	add r0, r4, #0
	bl FUN_0200E394
	mov r0, #1
	bl FUN_0200E394
	add r0, r4, #0
	mov r1, #6
	mov r2, #1
	bl FUN_0200A274
	add r0, r4, #0
	mov r1, #7
	mov r2, #2
	bl FUN_0200A274
	add r0, r5, #0
	mov r1, #2
	add r0, #0xa4
	str r1, [r0]
	ldr r1, _021D835C ; =0x00007FFF
	mov r0, #1
	bl FUN_020B8404
	add r0, r5, #0
	add r1, r4, #0
	add r0, #0xa8
	strh r1, [r0]
	mov r0, #1
	str r0, [r5]
	b _021D8350
_021D82FC:
	add r0, r5, #0
	add r0, #0xd4
	ldr r0, [r0]
	cmp r0, #1
	bne _021D8328
	add r0, r5, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0
	bne _021D831A
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E74C
	b _021D8330
_021D831A:
	cmp r0, #0x10
	bne _021D8330
	mov r0, #1
	add r1, r4, #0
	bl FUN_0201E74C
	b _021D8330
_021D8328:
	mov r0, #1
	add r1, r4, #0
	bl FUN_0201E74C
_021D8330:
	add r0, r5, #0
	add r0, #0xa8
	ldrh r0, [r0]
	mov r4, #1
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0xa8
	strh r1, [r0]
	add r0, r5, #0
	add r0, #0xa8
	ldrh r1, [r0]
	mov r0, #0x1f
	and r1, r0
	add r0, r5, #0
	add r0, #0xa8
	strh r1, [r0]
_021D8350:
	add r0, r5, #4
	bl MOD63_021D798C
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D835C: .word 0x00007FFF
	thumb_func_end MOD63_021D8260

	thumb_func_start MOD63_021D8360
MOD63_021D8360: ; 0x021D8360
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, #0xa0
	ldr r0, [r0]
	add r4, r1, #0
	add r6, r2, #0
	bl FUN_0201EB70
	add r0, r5, #4
	bl MOD63_021D7970
	add r0, r4, #0
	add r1, r6, #0
	add r2, r5, #0
	bl MOD63_021D8644
	ldr r2, _021D839C ; =0x04000050
	mov r3, #0
	strh r3, [r2]
	add r2, #0x10
	ldrh r1, [r2]
	ldr r0, _021D83A0 ; =0x0000CFDF
	and r0, r1
	strh r0, [r2]
	ldr r0, _021D83A4 ; =gUnk021C4918
	strb r3, [r0, #5]
	bl FUN_0201E7A0
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D839C: .word 0x04000050
_021D83A0: .word 0x0000CFDF
_021D83A4: .word gUnk021C4918
	thumb_func_end MOD63_021D8360

	thumb_func_start MOD63_021D83A8
MOD63_021D83A8: ; 0x021D83A8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	add r4, r1, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r1, #7
	add r6, r2, #0
	mov r0, #0x30
	add r2, r5, #0
	add r3, r1, #0
	str r4, [sp, #0xc]
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x30
	mov r1, #0xb
	add r2, r5, #0
	mov r3, #3
	str r4, [sp, #0xc]
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x30
	mov r1, #8
	add r2, r5, #0
	mov r3, #7
	str r4, [sp, #0xc]
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x30
	mov r1, #0xc
	add r2, r5, #0
	mov r3, #3
	str r4, [sp, #0xc]
	bl FUN_020068C8
	ldr r0, _021D85C8 ; =gGameVersion
	ldrb r7, [r0]
	cmp r7, #0xa
	bne _021D841A
	mov r0, #0xd
	mov r1, #9
	str r0, [sp, #0x18]
	b _021D8420
_021D841A:
	mov r0, #0xe
	mov r1, #0xa
	str r0, [sp, #0x18]
_021D8420:
	mov r3, #0
	str r3, [sp]
	mov r0, #0x30
	mov r2, #4
	str r4, [sp, #4]
	bl FUN_02006930
	mov r2, #0
	str r2, [sp]
	ldr r1, [sp, #0x18]
	mov r0, #0x30
	add r3, r2, #0
	str r4, [sp, #4]
	bl FUN_02006930
	cmp r7, #0xa
	bne _021D8448
	mov r1, #1
	mov r7, #2
	b _021D844C
_021D8448:
	mov r1, #3
	mov r7, #4
_021D844C:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x30
	add r2, r5, #0
	mov r3, #6
	str r4, [sp, #0xc]
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r3, #1
	mov r0, #0x30
	add r1, r7, #0
	mov r2, #6
	lsl r3, r3, #0xe
	str r4, [sp, #4]
	bl FUN_02006930
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x30
	add r2, r5, #0
	mov r3, #6
	str r4, [sp, #0xc]
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	mov r1, #0x11
	add r2, r5, #0
	mov r3, #5
	str r4, [sp, #0xc]
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r1, #0x10
	mov r0, #0x80
	mov r2, #6
	lsl r3, r1, #9
	str r4, [sp, #4]
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	mov r1, #0xf
	add r2, r5, #0
	mov r3, #5
	str r4, [sp, #0xc]
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x30
	mov r1, #0xf
	add r2, r5, #0
	mov r3, #1
	str r4, [sp, #0xc]
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x30
	mov r1, #0x11
	add r2, r5, #0
	mov r3, #1
	str r4, [sp, #0xc]
	bl FUN_020068C8
	mov r0, #0x60
	str r0, [sp]
	mov r0, #0x30
	mov r1, #0x10
	mov r2, #0
	mov r3, #0x20
	str r4, [sp, #4]
	bl FUN_02006930
	mov r0, #0
	add r1, r0, #0
	bl FUN_02017FE4
	mov r0, #4
	mov r1, #0
	bl FUN_02017FE4
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	add r3, r4, #0
	bl FUN_02017F18
	ldr r2, _021D85CC ; =0x00000227
	mov r0, #1
	mov r1, #0x1a
	add r3, r4, #0
	bl NewMsgDataFromNarc
	add r7, r0, #0
	mov r0, #0x40
	add r1, r4, #0
	bl String_ctor
	add r1, r6, #0
	add r4, r0, #0
	ldr r2, _021D85D0 ; =MOD63_021DB9A0
	add r0, r5, #0
	add r1, #0xac
	bl FUN_02019150
	mov r1, #0
	mov r0, #0xe0
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r6, #0
	add r0, #0xac
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020196F4
	add r0, r7, #0
	mov r1, #0
	add r2, r4, #0
	bl ReadMsgDataIntoString
	add r3, r6, #0
	add r3, #0xb3
	ldrb r3, [r3]
	mov r0, #0
	add r1, r4, #0
	mov r2, #1
	lsl r3, r3, #3
	bl FUN_02002F40
	mov r1, #0
	add r3, r0, #0
	str r1, [sp]
	ldr r0, _021D85D4 ; =0x00010100
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	add r6, #0xac
	str r1, [sp, #0x10]
	add r0, r6, #0
	add r2, r4, #0
	str r1, [sp, #0x14]
	bl FUN_0201BE3C
	add r0, r4, #0
	bl String_dtor
	add r0, r7, #0
	bl DestroyMsgData
	mov r1, #0x15
	add r0, sp, #0x1c
	strh r1, [r0, #2]
	strh r1, [r0]
	add r1, sp, #0x1c
	mov r0, #4
	add r1, #2
	mov r2, #2
	mov r3, #0x42
	bl FUN_02017FB4
	mov r0, #4
	add r1, sp, #0x1c
	mov r2, #2
	mov r3, #0x44
	bl FUN_02017FB4
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D85C8: .word gGameVersion
_021D85CC: .word 0x00000227
_021D85D0: .word MOD63_021DB9A0
_021D85D4: .word 0x00010100
	thumb_func_end MOD63_021D83A8

	thumb_func_start MOD63_021D85D8
MOD63_021D85D8: ; 0x021D85D8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r2, #0xa8
	add r7, r0, #0
	ldrh r0, [r2]
	add r5, r1, #0
	cmp r0, #0
	bne _021D863A
	ldr r0, _021D8640 ; =gGameVersion
	ldrb r0, [r0]
	cmp r0, #0xa
	bne _021D85F8
	mov r1, #0xb
	mov r6, #0xa
	mov r4, #0xc
	b _021D85FE
_021D85F8:
	mov r1, #8
	mov r6, #7
	mov r4, #9
_021D85FE:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	add r2, r7, #0
	mov r3, #5
	str r5, [sp, #0xc]
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r0, #0x80
	add r1, r6, #0
	mov r2, #6
	lsl r3, r0, #6
	str r5, [sp, #4]
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	add r1, r4, #0
	add r2, r7, #0
	mov r3, #5
	str r5, [sp, #0xc]
	bl FUN_020068C8
_021D863A:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8640: .word gGameVersion
	thumb_func_end MOD63_021D85D8

	thumb_func_start MOD63_021D8644
MOD63_021D8644: ; 0x021D8644
	ldr r3, _021D864C ; =FUN_02019178
	add r2, #0xac
	add r0, r2, #0
	bx r3
	.align 2, 0
_021D864C: .word FUN_02019178
	thumb_func_end MOD63_021D8644

	thumb_func_start MOD63_021D8650
MOD63_021D8650: ; 0x021D8650
	push {r4, lr}
	ldr r1, _021D86DC ; =0x00000116
	ldrh r2, [r0, r1]
	cmp r2, #3
	bhi _021D86B2
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021D8666: ; jump table
	.short _021D866E - _021D8666 - 2 ; case 0
	.short _021D86B2 - _021D8666 - 2 ; case 1
	.short _021D867A - _021D8666 - 2 ; case 2
	.short _021D8698 - _021D8666 - 2 ; case 3
_021D866E:
	mov r3, #5
	sub r2, r1, #2
	strh r3, [r0, r2]
	mov r2, #1
	strh r2, [r0, r1]
	b _021D86B2
_021D867A:
	sub r2, r1, #2
	ldrh r2, [r0, r2]
	add r3, r2, #2
	sub r2, r1, #2
	strh r3, [r0, r2]
	ldrh r2, [r0, r2]
	cmp r2, #0x1f
	blo _021D86B2
	mov r3, #0x1f
	add r2, r3, #0
	add r2, #0xf5
	strh r3, [r0, r2]
	mov r2, #1
	strh r2, [r0, r1]
	b _021D86B2
_021D8698:
	sub r2, r1, #2
	ldrh r2, [r0, r2]
	sub r3, r2, #2
	sub r2, r1, #2
	strh r3, [r0, r2]
	ldrh r2, [r0, r2]
	cmp r2, #5
	bhi _021D86B2
	mov r3, #5
	sub r2, r1, #2
	strh r3, [r0, r2]
	mov r2, #1
	strh r2, [r0, r1]
_021D86B2:
	mov r1, #0x45
	lsl r1, r1, #2
	ldrh r3, [r0, r1]
	mov r1, #0x1f
	lsl r1, r1, #0xa
	lsl r2, r3, #0xa
	and r1, r2
	add r4, r3, #0
	mov r2, #0x1f
	and r4, r2
	lsl r3, r3, #5
	lsl r2, r2, #5
	and r2, r3
	orr r2, r4
	orr r1, r2
	lsl r1, r1, #0x10
	mov r0, #1
	lsr r1, r1, #0x10
	bl FUN_020B8404
	pop {r4, pc}
	.align 2, 0
_021D86DC: .word 0x00000116
	thumb_func_end MOD63_021D8650

	thumb_func_start MOD63_021D86E0
MOD63_021D86E0: ; 0x021D86E0
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r4, r0, #0
	ldr r0, _021D8858 ; =gGameVersion
	ldrb r0, [r0]
	cmp r0, #0xa
	bne _021D8788
	add r0, r4, #0
	mov r2, #0
	add r0, #0xd8
	str r2, [r0]
	mov r1, #0x41
	add r0, r4, #0
	mov r3, #0x12
	lsl r1, r1, #0xc
	add r0, #0xdc
	str r1, [r0]
	add r0, r4, #0
	mov r5, #0xf6
	lsl r3, r3, #0xe
	add r0, #0xe0
	str r3, [r0]
	mov r3, #0xc3
	add r0, r4, #0
	lsl r3, r3, #0xc
	add r0, #0xe4
	str r3, [r0]
	mov r0, #2
	add r3, r4, #0
	lsl r0, r0, #0x10
	add r3, #0xe8
	str r0, [r3]
	add r3, r4, #0
	lsl r5, r5, #0xc
	add r3, #0xec
	str r5, [r3]
	add r3, r4, #0
	add r3, #0xf0
	str r2, [r3]
	mov r5, #0x5a
	add r3, r4, #0
	lsl r5, r5, #0xc
	add r3, #0xf4
	str r5, [r3]
	add r3, r4, #0
	add r3, #0xf8
	str r2, [r3]
	add r2, r4, #0
	ldr r3, _021D885C ; =0xFFFFE000
	add r2, #0xfc
	str r3, [r2]
	mov r2, #0x1f
	lsl r2, r2, #0xe
	lsr r0, r0, #9
	str r2, [r4, r0]
	lsr r0, r1, #0xa
	ldr r2, _021D8860 ; =0xFFFDA000
	ldr r1, _021D8864 ; =0xFFFFF6E3
	str r2, [r4, r0]
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r3, _021D8868 ; =0x00000A2B
	strh r1, [r4, r0]
	add r2, r0, #2
	strh r3, [r4, r2]
	add r3, r1, #0
	add r3, #0xc6
	add r2, r0, #4
	strh r3, [r4, r2]
	add r1, #0x42
	add r2, r0, #6
	strh r1, [r4, r2]
	add r1, r0, #0
	ldr r2, _021D886C ; =0x000007A1
	add r1, #8
	strh r2, [r4, r1]
	add r1, r0, #0
	ldr r2, _021D8870 ; =0xFFFFF513
	add r1, #0xa
	strh r2, [r4, r1]
	mov r1, #3
	lsl r1, r1, #0xc
	add r0, #0x10
	b _021D8828
_021D8788:
	add r0, r4, #0
	ldr r1, _021D8874 ; =0xFFFBF000
	add r0, #0xd8
	str r1, [r0]
	mov r1, #0x29
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r0, #0xdc
	str r1, [r0]
	mov r1, #0x13
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r0, #0xe0
	str r1, [r0]
	add r0, r4, #0
	ldr r1, _021D8878 ; =0xFFF6C000
	add r0, #0xe4
	str r1, [r0]
	mov r1, #0x3a
	add r0, r4, #0
	mov r2, #2
	lsl r1, r1, #0xc
	add r0, #0xe8
	str r1, [r0]
	mov r1, #0xbe
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r0, #0xec
	str r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xf0
	str r1, [r0]
	mov r1, #0xb
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r0, #0xf4
	str r1, [r0]
	mov r1, #0x12
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r0, #0xf8
	str r1, [r0]
	add r0, r4, #0
	lsl r2, r2, #0xe
	add r0, #0xfc
	str r2, [r0]
	ldr r1, _021D887C ; =0xFFFFB000
	lsr r0, r2, #7
	str r1, [r4, r0]
	mov r0, #0x41
	lsr r1, r2, #3
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r2, _021D8880 ; =0x00000653
	add r1, r0, #4
	strh r2, [r4, r1]
	ldr r2, _021D8884 ; =0xFFFFF71C
	add r1, r0, #6
	strh r2, [r4, r1]
	add r1, r0, #0
	sub r2, #0x14
	add r1, #8
	strh r2, [r4, r1]
	add r1, r0, #0
	ldr r2, _021D8888 ; =0x0000091B
	add r1, #0xa
	strh r2, [r4, r1]
	add r1, r0, #0
	ldr r2, _021D888C ; =0xFFFFFB61
	add r1, #0xc
	strh r2, [r4, r1]
	add r1, r0, #0
	mov r2, #0xc5
	lsl r2, r2, #4
	add r1, #0xe
	strh r2, [r4, r1]
	mov r1, #3
	lsl r1, r1, #0xc
	add r0, #0x14
_021D8828:
	str r1, [r4, r0]
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xfc
	add r1, #0xe4
	add r2, sp, #0xc
	bl VEC_Subtract
	add r0, sp, #0xc
	add r1, sp, #0
	bl VEC_Normalize
	mov r0, #0x42
	ldr r1, [sp]
	lsl r0, r0, #2
	strh r1, [r4, r0]
	add r1, r0, #2
	ldr r2, [sp, #4]
	add r0, r0, #4
	strh r2, [r4, r1]
	ldr r1, [sp, #8]
	strh r1, [r4, r0]
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8858: .word gGameVersion
_021D885C: .word 0xFFFFE000
_021D8860: .word 0xFFFDA000
_021D8864: .word 0xFFFFF6E3
_021D8868: .word 0x00000A2B
_021D886C: .word 0x000007A1
_021D8870: .word 0xFFFFF513
_021D8874: .word 0xFFFBF000
_021D8878: .word 0xFFF6C000
_021D887C: .word 0xFFFFB000
_021D8880: .word 0x00000653
_021D8884: .word 0xFFFFF71C
_021D8888: .word 0x0000091B
_021D888C: .word 0xFFFFFB61
	thumb_func_end MOD63_021D86E0

	thumb_func_start MOD63_021D8890
MOD63_021D8890: ; 0x021D8890
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D88AC ; =MOD63_021DBD70
	add r3, sp, #0
	mov r2, #5
_021D889A:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D889A
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D88AC: .word MOD63_021DBD70
	thumb_func_end MOD63_021D8890

	thumb_func_start MOD63_021D88B0
MOD63_021D88B0: ; 0x021D88B0
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D88CC ; =MOD63_021DBD98
	add r3, sp, #0
	mov r2, #5
_021D88BA:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D88BA
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D88CC: .word MOD63_021DBD98
	thumb_func_end MOD63_021D88B0

	thumb_func_start MOD63_021D88D0
MOD63_021D88D0: ; 0x021D88D0
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D88EC ; =MOD63_021DBDC0
	add r3, sp, #0
	mov r2, #5
_021D88DA:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D88DA
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D88EC: .word MOD63_021DBDC0
	thumb_func_end MOD63_021D88D0

	thumb_func_start MOD63_021D88F0
MOD63_021D88F0: ; 0x021D88F0
	push {r3, r4, r5, lr}
	sub sp, #0xb8
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_02016B94
	add r3, sp, #0xa8
	ldr r5, _021D89E8 ; =MOD63_021DBB4C
	str r0, [r4, #0xc]
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _021D89EC ; =MOD63_021DBC88
	add r3, sp, #0x8c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D89F0 ; =MOD63_021DBC6C
	add r3, sp, #0x70
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D89F4 ; =MOD63_021DBBC4
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #3
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D89F8 ; =MOD63_021DBBFC
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #5
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D89FC ; =MOD63_021DBC18
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D8A00 ; =MOD63_021DBC34
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #7
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	add r1, r0, #0
	bl FUN_02017FE4
	mov r0, #4
	mov r1, #0
	bl FUN_02017FE4
	add sp, #0xb8
	pop {r3, r4, r5, pc}
	nop
_021D89E8: .word MOD63_021DBB4C
_021D89EC: .word MOD63_021DBC88
_021D89F0: .word MOD63_021DBC6C
_021D89F4: .word MOD63_021DBBC4
_021D89F8: .word MOD63_021DBBFC
_021D89FC: .word MOD63_021DBC18
_021D8A00: .word MOD63_021DBC34
	thumb_func_end MOD63_021D88F0

	thumb_func_start MOD63_021D8A04
MOD63_021D8A04: ; 0x021D8A04
	push {r3, r4, r5, lr}
	sub sp, #0x80
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_02016B94
	add r3, sp, #0x70
	ldr r5, _021D8AC4 ; =MOD63_021DBB3C
	str r0, [r4, #0xc]
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D8AC8 ; =0xC7FFFFFF
	ldr r5, _021D8ACC ; =MOD63_021DBC50
	and r1, r0
	lsl r0, r2, #1
	orr r0, r1
	str r0, [r2]
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #3
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D8AD0 ; =MOD63_021DBCA4
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D8AD4 ; =MOD63_021DBCC0
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D8AD8 ; =MOD63_021DBCDC
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #4
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	mov r0, #4
	mov r1, #0
	bl FUN_02017FE4
	add sp, #0x80
	pop {r3, r4, r5, pc}
	nop
_021D8AC4: .word MOD63_021DBB3C
_021D8AC8: .word 0xC7FFFFFF
_021D8ACC: .word MOD63_021DBC50
_021D8AD0: .word MOD63_021DBCA4
_021D8AD4: .word MOD63_021DBCC0
_021D8AD8: .word MOD63_021DBCDC
	thumb_func_end MOD63_021D8A04

	thumb_func_start MOD63_021D8ADC
MOD63_021D8ADC: ; 0x021D8ADC
	push {r4, r5, lr}
	sub sp, #0x9c
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_02016B94
	add r3, sp, #0x8c
	ldr r5, _021D8BBC ; =0x021DBB6C
	str r0, [r4, #0xc]
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D8BC0 ; =0xC7FFFFFF
	ldr r5, _021D8BC4 ; =0x021DBCF8
	and r1, r0
	lsl r0, r2, #1
	orr r0, r1
	str r0, [r2]
	add r3, sp, #0x70
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D8BC8 ; =0x021DBD14
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #1
	bl FUN_02016C18
	ldr r5, _021D8BCC ; =0x021DBD30
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #3
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #1
	bl FUN_02016C18
	ldr r5, _021D8BD0 ; =0x021DBBA8
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0
	str r0, [r3]
	ldr r0, [r4, #0xc]
	add r3, r1, #0
	bl FUN_02016C18
	ldr r5, _021D8BD4 ; =0x021DBBE0
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #5
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	mov r0, #4
	mov r1, #0
	bl FUN_02017FE4
	add sp, #0x9c
	pop {r4, r5, pc}
	nop
_021D8BBC: .word 0x021DBB6C
_021D8BC0: .word 0xC7FFFFFF
_021D8BC4: .word 0x021DBCF8
_021D8BC8: .word 0x021DBD14
_021D8BCC: .word 0x021DBD30
_021D8BD0: .word 0x021DBBA8
_021D8BD4: .word 0x021DBBE0
	thumb_func_end MOD63_021D8ADC

	thumb_func_start MOD63_021D8BD8
MOD63_021D8BD8: ; 0x021D8BD8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #4
	str r0, [sp]
	ldr r0, _021D8C14 ; =MOD63_021D8C20
	mov r1, #0
	str r0, [sp, #4]
	ldr r0, [r4]
	mov r2, #1
	add r3, r1, #0
	bl FUN_02022318
	str r0, [r4, #0x10]
	ldr r3, _021D8C18 ; =0x021064B8
	mov r0, #2
	mov r1, #0
	ldr r3, [r3]
	lsl r0, r0, #0xe
	add r2, r1, #0
	blx r3
	ldr r3, _021D8C1C ; =UNK_021064C0
	mov r0, #0x80
	ldr r3, [r3]
	mov r1, #0
	mov r2, #1
	blx r3
	add sp, #8
	pop {r4, pc}
	nop
_021D8C14: .word MOD63_021D8C20
_021D8C18: .word 0x021064B8
_021D8C1C: .word UNK_021064C0
	thumb_func_end MOD63_021D8BD8

	thumb_func_start MOD63_021D8C20
MOD63_021D8C20: ; 0x021D8C20
	push {r3, lr}
	ldr r0, _021D8C8C ; =0x04000008
	mov r1, #3
	ldrh r2, [r0]
	bic r2, r1
	strh r2, [r0]
	add r0, #0x58
	ldrh r2, [r0]
	ldr r1, _021D8C90 ; =0xFFFFCFFD
	and r2, r1
	strh r2, [r0]
	ldrh r3, [r0]
	add r2, r1, #2
	and r3, r2
	mov r2, #0x10
	orr r2, r3
	strh r2, [r0]
	ldrh r3, [r0]
	ldr r2, _021D8C94 ; =0x0000CFFB
	and r2, r3
	strh r2, [r0]
	add r2, r1, #2
	ldrh r3, [r0]
	add r1, r1, #2
	and r3, r2
	mov r2, #8
	orr r2, r3
	strh r2, [r0]
	ldrh r2, [r0]
	and r2, r1
	mov r1, #0x20
	orr r1, r2
	strh r1, [r0]
	ldr r0, _021D8C98 ; =0x021DBB5C
	bl G3X_SetEdgeColorTable
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl G3X_SetFog
	mov r0, #0
	ldr r2, _021D8C9C ; =0x00007FFF
	add r1, r0, #0
	mov r3, #0x3f
	str r0, [sp]
	bl G3X_SetClearColor
	ldr r1, _021D8CA0 ; =0xBFFF0000
	ldr r0, _021D8CA4 ; =0x04000580
	str r1, [r0]
	pop {r3, pc}
	nop
_021D8C8C: .word 0x04000008
_021D8C90: .word 0xFFFFCFFD
_021D8C94: .word 0x0000CFFB
_021D8C98: .word 0x021DBB5C
_021D8C9C: .word 0x00007FFF
_021D8CA0: .word 0xBFFF0000
_021D8CA4: .word 0x04000580
	thumb_func_end MOD63_021D8C20

	thumb_func_start MOD63_021D8CA8
MOD63_021D8CA8: ; 0x021D8CA8
	ldr r3, _021D8CAC ; =FUN_02009F80
	bx r3
	.align 2, 0
_021D8CAC: .word FUN_02009F80
	thumb_func_end MOD63_021D8CA8

	thumb_func_start MOD63_021D8CB0
MOD63_021D8CB0: ; 0x021D8CB0
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02009F80
	ldr r0, [r4, #0x4c]
	bl MOD63_021DB598
	pop {r4, pc}
	thumb_func_end MOD63_021D8CB0

	thumb_func_start MOD63_021D8CC0
MOD63_021D8CC0: ; 0x021D8CC0
	push {r4, r5}
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r2, [r0]
	ldr r1, _021D8D08 ; =0xFFFF1FFF
	add r4, r0, #0
	and r2, r1
	lsr r1, r0, #0xd
	orr r1, r2
	str r1, [r0]
	add r4, #0x48
	ldrh r3, [r4]
	mov r2, #0x3f
	mov r1, #0x1f
	bic r3, r2
	orr r1, r3
	mov r3, #0x20
	orr r1, r3
	strh r1, [r4]
	add r4, r0, #0
	add r4, #0x4a
	ldrh r5, [r4]
	mov r1, #0x11
	bic r5, r2
	orr r1, r5
	orr r1, r3
	strh r1, [r4]
	add r1, r0, #0
	mov r2, #0xff
	add r1, #0x40
	strh r2, [r1]
	ldr r1, _021D8D0C ; =0x0000209F
	add r0, #0x44
	strh r1, [r0]
	pop {r4, r5}
	bx lr
	.align 2, 0
_021D8D08: .word 0xFFFF1FFF
_021D8D0C: .word 0x0000209F
	thumb_func_end MOD63_021D8CC0

	thumb_func_start MOD63_021D8D10
MOD63_021D8D10: ; 0x021D8D10
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0200A2AC
	ldr r1, _021D8D90 ; =0x00007FFF
	mov r0, #0
	bl FUN_0200E3A0
	ldr r1, _021D8D90 ; =0x00007FFF
	mov r0, #1
	bl FUN_0200E3A0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F34
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	mov r0, #3
	mov r1, #0x4c
	lsl r2, r0, #0x11
	bl FUN_0201681C
	mov r1, #0xab
	add r0, r4, #0
	lsl r1, r1, #2
	mov r2, #0x4c
	bl FUN_02006268
	mov r2, #0xab
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl memset
	mov r0, #0x4c
	str r0, [r4]
	mov r1, #0
	mov r0, #0xaa
	str r1, [r4, #8]
	lsl r0, r0, #2
	strb r1, [r4, r0]
	ldr r0, _021D8D94 ; =gUnk021C4918
	strb r1, [r0, #5]
	bl FUN_0201E7A0
	bl GetLCRNGSeed
	str r0, [r4, #0x14]
	mov r0, #0
	bl SetLCRNGSeed
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_021D8D90: .word 0x00007FFF
_021D8D94: .word gUnk021C4918
	thumb_func_end MOD63_021D8D10

	thumb_func_start MOD63_021D8D98
MOD63_021D8D98: ; 0x021D8D98
	push {r3, r4, r5, lr}
	add r4, r1, #0
	bl FUN_02006278
	add r5, r0, #0
	mov r0, #0xaa
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	cmp r0, #0
	beq _021D8DD4
	ldr r0, _021D8E5C ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	bne _021D8DBC
	mov r0, #8
	tst r0, r1
	beq _021D8DD4
_021D8DBC:
	mov r0, #1
	str r0, [r5, #8]
	ldr r1, _021D8E5C ; =gUnknown21C48B8
	mov r0, #0
	str r0, [r1, #0x6c]
	ldr r1, _021D8E60 ; =0x00007FFF
	bl FUN_0200E3A0
	ldr r1, _021D8E60 ; =0x00007FFF
	mov r0, #1
	bl FUN_0200E3A0
_021D8DD4:
	ldr r0, [r4]
	cmp r0, #4
	bhi _021D8E42
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8DE6: ; jump table
	.short _021D8DF0 - _021D8DE6 - 2 ; case 0
	.short _021D8E00 - _021D8DE6 - 2 ; case 1
	.short _021D8E12 - _021D8DE6 - 2 ; case 2
	.short _021D8E24 - _021D8DE6 - 2 ; case 3
	.short _021D8E36 - _021D8DE6 - 2 ; case 4
_021D8DF0:
	mov r0, #0xaa
	lsl r0, r0, #2
	add r0, r5, r0
	str r0, [r5, #0x30]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8E46
_021D8E00:
	add r0, r5, #0
	bl MOD63_021D8E9C
	cmp r0, #0
	beq _021D8E46
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8E46
_021D8E12:
	add r0, r5, #0
	bl MOD63_021D93F0
	cmp r0, #0
	beq _021D8E46
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8E46
_021D8E24:
	add r0, r5, #0
	bl MOD63_021DA0A8
	cmp r0, #0
	beq _021D8E46
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8E46
_021D8E36:
	ldr r1, [r5, #4]
	ldr r0, _021D8E64 ; =0x00000A8C
	cmp r1, r0
	blt _021D8E46
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8E42:
	bl ErrorHandling
_021D8E46:
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _021D8E50
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8E50:
	ldr r0, [r5, #4]
	add r0, r0, #1
	str r0, [r5, #4]
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D8E5C: .word gUnknown21C48B8
_021D8E60: .word 0x00007FFF
_021D8E64: .word 0x00000A8C
	thumb_func_end MOD63_021D8D98

	thumb_func_start MOD63_021D8E68
MOD63_021D8E68: ; 0x021D8E68
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_02006278
	add r4, r0, #0
	bl FUN_0200E31C
	ldr r0, [r4, #0x14]
	bl SetLCRNGSeed
	add r0, r5, #0
	bl FUN_0200627C
	mov r0, #0x4c
	bl FUN_020168D0
	ldr r0, _021D8E94 ; =SDK_OVERLAY_MODULE_63_ID
	ldr r1, _021D8E98 ; =UNK63_021DBAB8
	bl FUN_02000E7C
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8E94: .word SDK_OVERLAY_MODULE_63_ID
_021D8E98: .word UNK63_021DBAB8
	thumb_func_end MOD63_021D8E68

	thumb_func_start MOD63_021D8E9C
MOD63_021D8E9C: ; 0x021D8E9C
	push {r4, lr}
	add r1, r0, #0
	ldr r0, [r1, #8]
	add r4, r1, #0
	add r4, #0x18
	cmp r0, #0
	beq _021D8EAE
	mov r0, #3
	strb r0, [r4]
_021D8EAE:
	ldrb r0, [r4]
	cmp r0, #3
	bhi _021D8F06
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8EC0: ; jump table
	.short _021D8EC8 - _021D8EC0 - 2 ; case 0
	.short _021D8ED6 - _021D8EC0 - 2 ; case 1
	.short _021D8EE6 - _021D8EC0 - 2 ; case 2
	.short _021D8EFC - _021D8EC0 - 2 ; case 3
_021D8EC8:
	add r0, r1, #0
	bl MOD63_021D8F0C
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _021D8F06
_021D8ED6:
	add r1, #0x18
	add r0, r1, #0
	bl MOD63_021D8F38
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _021D8F06
_021D8EE6:
	add r0, r1, #0
	ldr r1, [r1, #4]
	add r0, #0x18
	bl MOD63_021D90D0
	cmp r0, #0
	beq _021D8F06
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _021D8F06
_021D8EFC:
	add r0, r1, #0
	bl MOD63_021D9234
	mov r0, #1
	pop {r4, pc}
_021D8F06:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD63_021D8E9C

	thumb_func_start MOD63_021D8F0C
MOD63_021D8F0C: ; 0x021D8F0C
	push {r4, lr}
	add r4, r0, #0
	bl MOD63_021D8890
	add r0, r4, #0
	bl MOD63_021D88F0
	ldr r0, [r4, #0xc]
	str r0, [r4, #0x24]
	bl MOD63_021DAEF8
	str r0, [r4, #0x2c]
	ldr r0, _021D8F34 ; =MOD63_021D8CA8
	add r1, r4, #0
	bl FUN_02015F10
	mov r0, #1
	strb r0, [r4, #0x1a]
	pop {r4, pc}
	nop
_021D8F34: .word MOD63_021D8CA8
	thumb_func_end MOD63_021D8F0C

	thumb_func_start MOD63_021D8F38
MOD63_021D8F38: ; 0x021D8F38
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x13
	mov r3, #2
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x13
	mov r3, #6
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x14
	mov r3, #2
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x15
	mov r3, #6
	bl FUN_020068C8
	mov r2, #0
	str r2, [sp]
	mov r0, #0x4c
	str r0, [sp, #4]
	mov r0, #0x80
	mov r1, #0x12
	add r3, r2, #0
	bl FUN_02006930
	mov r3, #0
	str r3, [sp]
	mov r0, #0x4c
	str r0, [sp, #4]
	mov r0, #0x80
	mov r1, #0x12
	mov r2, #4
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	mov r1, #1
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	add r3, r1, #0
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #2
	mov r3, #1
	bl FUN_020068C8
	mov r1, #0
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x4c
	str r0, [sp, #4]
	mov r0, #0x80
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x16
	mov r3, #3
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x16
	mov r3, #7
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x48
	mov r3, #5
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x49
	mov r3, #5
	bl FUN_020068C8
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x4c
	str r0, [sp, #4]
	mov r0, #0x80
	mov r1, #0x47
	mov r2, #4
	mov r3, #0
	bl FUN_02006930
	mov r0, #4
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #4
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _021D90C8 ; =0x04000050
	mov r1, #2
	mov r2, #8
	mov r3, #0
	bl G2x_SetBlendAlpha_
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _021D90CC ; =0x04001050
	mov r1, #2
	mov r2, #8
	mov r3, #0
	bl G2x_SetBlendAlpha_
	mov r0, #1
	add r1, r0, #0
	bl OS_WaitIrq
	mov r0, #0
	bl FUN_0200E394
	mov r0, #1
	bl FUN_0200E394
	bl FUN_0201E788
	add sp, #0x10
	pop {r4, pc}
	nop
_021D90C8: .word 0x04000050
_021D90CC: .word 0x04001050
	thumb_func_end MOD63_021D8F38

	thumb_func_start MOD63_021D90D0
MOD63_021D90D0: ; 0x021D90D0
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	add r5, r1, #0
	bl MOD63_021DB1AC
	ldrb r0, [r4, #1]
	cmp r0, #5
	bls _021D90E6
	b _021D9208
_021D90E6:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D90F2: ; jump table
	.short _021D90FE - _021D90F2 - 2 ; case 0
	.short _021D9122 - _021D90F2 - 2 ; case 1
	.short _021D9148 - _021D90F2 - 2 ; case 2
	.short _021D91AE - _021D90F2 - 2 ; case 3
	.short _021D91CE - _021D90F2 - 2 ; case 4
	.short _021D91FA - _021D90F2 - 2 ; case 5
_021D90FE:
	mov r2, #0
	strb r2, [r4, #7]
	strb r2, [r4, #6]
	ldr r0, _021D9210 ; =MOD63_021D92A4
	strb r2, [r4, #8]
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #0x10]
	mov r0, #1
	ldr r1, _021D9214 ; =0x00000494
	add r2, r0, #0
	bl FUN_0200433C
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9208
_021D9122:
	ldrb r0, [r4, #8]
	cmp r0, #0
	beq _021D9208
	cmp r5, #0x73
	blt _021D9208
	mov r2, #0
	strb r2, [r4, #7]
	mov r0, #0x10
	strb r0, [r4, #6]
	ldr r0, _021D9218 ; =MOD63_021D9300
	strb r2, [r4, #8]
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #0x10]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9208
_021D9148:
	ldrb r0, [r4, #8]
	cmp r0, #0
	beq _021D9208
	ldr r0, _021D921C ; =0x00000109
	cmp r5, r0
	blt _021D9208
	mov r0, #2
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #2
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _021D9220 ; =0x04000050
	mov r1, #4
	mov r2, #8
	mov r3, #0
	bl G2x_SetBlendAlpha_
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _021D9224 ; =0x04001050
	mov r1, #4
	mov r2, #8
	mov r3, #0
	bl G2x_SetBlendAlpha_
	mov r0, #4
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #4
	mov r1, #1
	bl FUN_0201E74C
	mov r2, #0
	strb r2, [r4, #7]
	strb r2, [r4, #6]
	ldr r0, _021D9228 ; =MOD63_021D9360
	strb r2, [r4, #8]
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #0x10]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9208
_021D91AE:
	ldrb r0, [r4, #8]
	cmp r0, #0
	beq _021D9208
	mov r2, #0
	strb r2, [r4, #7]
	strb r2, [r4, #6]
	ldr r0, _021D922C ; =MOD63_021D93A8
	strb r2, [r4, #8]
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #0x10]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9208
_021D91CE:
	ldrb r0, [r4, #8]
	cmp r0, #0
	beq _021D9208
	ldr r0, _021D9230 ; =0x000001EA
	cmp r5, r0
	blt _021D9208
	mov r0, #0x12
	str r0, [sp]
	mov r1, #0
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	mov r0, #2
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9208
_021D91FA:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9208
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_021D9208:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021D9210: .word MOD63_021D92A4
_021D9214: .word 0x00000494
_021D9218: .word MOD63_021D9300
_021D921C: .word 0x00000109
_021D9220: .word 0x04000050
_021D9224: .word 0x04001050
_021D9228: .word MOD63_021D9360
_021D922C: .word MOD63_021D93A8
_021D9230: .word 0x000001EA
	thumb_func_end MOD63_021D90D0

	thumb_func_start MOD63_021D9234
MOD63_021D9234: ; 0x021D9234
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	ldrb r0, [r4, #0x1a]
	cmp r0, #0
	beq _021D9286
	ldr r0, [r4, #0x2c]
	bl MOD63_021DAF9C
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #6
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #7
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #5
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	bl FreeToHeap
	mov r0, #0
	strb r0, [r4, #0x1a]
_021D9286:
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _021D92A0
	ldr r0, [r4, #8]
	cmp r0, #0
	bne _021D9296
	bl ErrorHandling
_021D9296:
	ldr r0, [r4, #0x28]
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #0x28]
_021D92A0:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD63_021D9234

	thumb_func_start MOD63_021D92A4
MOD63_021D92A4: ; 0x021D92A4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldrb r1, [r4, #7]
	add r1, r1, #1
	strb r1, [r4, #7]
	ldrb r1, [r4, #7]
	cmp r1, #6
	blo _021D92C0
	mov r1, #0
	strb r1, [r4, #7]
	ldrb r1, [r4, #6]
	add r1, r1, #1
	strb r1, [r4, #6]
_021D92C0:
	ldrb r1, [r4, #6]
	cmp r1, #0x10
	blo _021D92D2
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #0x10]
	mov r0, #1
	strb r0, [r4, #8]
_021D92D2:
	mov r0, #0x10
	str r0, [sp]
	ldrb r3, [r4, #6]
	ldr r0, _021D92F8 ; =0x04000050
	mov r1, #2
	mov r2, #8
	bl G2x_SetBlendAlpha_
	mov r0, #0x10
	str r0, [sp]
	ldrb r3, [r4, #6]
	ldr r0, _021D92FC ; =0x04001050
	mov r1, #2
	mov r2, #8
	bl G2x_SetBlendAlpha_
	add sp, #4
	pop {r3, r4, pc}
	nop
_021D92F8: .word 0x04000050
_021D92FC: .word 0x04001050
	thumb_func_end MOD63_021D92A4

	thumb_func_start MOD63_021D9300
MOD63_021D9300: ; 0x021D9300
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldrb r1, [r4, #7]
	add r1, r1, #1
	strb r1, [r4, #7]
	ldrb r1, [r4, #7]
	cmp r1, #4
	blo _021D931C
	mov r1, #0
	strb r1, [r4, #7]
	ldrb r1, [r4, #6]
	sub r1, r1, #1
	strb r1, [r4, #6]
_021D931C:
	ldrb r1, [r4, #6]
	cmp r1, #0
	bne _021D9332
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #0x10]
	mov r1, #1
	strb r1, [r4, #8]
	ldr r0, [r4, #0x18]
	strb r1, [r0]
_021D9332:
	mov r0, #0x10
	str r0, [sp]
	ldrb r3, [r4, #6]
	ldr r0, _021D9358 ; =0x04000050
	mov r1, #2
	mov r2, #8
	bl G2x_SetBlendAlpha_
	mov r0, #0x10
	str r0, [sp]
	ldrb r3, [r4, #6]
	ldr r0, _021D935C ; =0x04001050
	mov r1, #2
	mov r2, #8
	bl G2x_SetBlendAlpha_
	add sp, #4
	pop {r3, r4, pc}
	nop
_021D9358: .word 0x04000050
_021D935C: .word 0x04001050
	thumb_func_end MOD63_021D9300

	thumb_func_start MOD63_021D9360
MOD63_021D9360: ; 0x021D9360
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldrb r1, [r4, #7]
	add r1, r1, #1
	strb r1, [r4, #7]
	ldrb r1, [r4, #7]
	cmp r1, #4
	blo _021D937C
	mov r1, #0
	strb r1, [r4, #7]
	ldrb r1, [r4, #6]
	add r1, r1, #1
	strb r1, [r4, #6]
_021D937C:
	ldrb r1, [r4, #6]
	cmp r1, #0x10
	blo _021D938E
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #0x10]
	mov r0, #1
	strb r0, [r4, #8]
_021D938E:
	mov r0, #0x10
	str r0, [sp]
	ldrb r3, [r4, #6]
	ldr r0, _021D93A4 ; =0x04000050
	mov r1, #4
	mov r2, #8
	bl G2x_SetBlendAlpha_
	add sp, #4
	pop {r3, r4, pc}
	nop
_021D93A4: .word 0x04000050
	thumb_func_end MOD63_021D9360

	thumb_func_start MOD63_021D93A8
MOD63_021D93A8: ; 0x021D93A8
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldrb r1, [r4, #7]
	add r1, r1, #1
	strb r1, [r4, #7]
	ldrb r1, [r4, #7]
	cmp r1, #4
	blo _021D93C4
	mov r1, #0
	strb r1, [r4, #7]
	ldrb r1, [r4, #6]
	add r1, r1, #1
	strb r1, [r4, #6]
_021D93C4:
	ldrb r1, [r4, #6]
	cmp r1, #0x10
	blo _021D93D6
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #0x10]
	mov r0, #1
	strb r0, [r4, #8]
_021D93D6:
	mov r0, #0x10
	str r0, [sp]
	ldrb r3, [r4, #6]
	ldr r0, _021D93EC ; =0x04001050
	mov r1, #4
	mov r2, #8
	bl G2x_SetBlendAlpha_
	add sp, #4
	pop {r3, r4, pc}
	nop
_021D93EC: .word 0x04001050
	thumb_func_end MOD63_021D93A8

	thumb_func_start MOD63_021D93F0
MOD63_021D93F0: ; 0x021D93F0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #8]
	add r4, r5, #0
	add r4, #0x34
	cmp r0, #0
	beq _021D9402
	mov r0, #4
	strb r0, [r4]
_021D9402:
	ldrb r0, [r4]
	cmp r0, #4
	bhi _021D9492
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9414: ; jump table
	.short _021D941E - _021D9414 - 2 ; case 0
	.short _021D942C - _021D9414 - 2 ; case 1
	.short _021D943C - _021D9414 - 2 ; case 2
	.short _021D9452 - _021D9414 - 2 ; case 3
	.short _021D9488 - _021D9414 - 2 ; case 4
_021D941E:
	add r0, r5, #0
	bl MOD63_021D9498
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _021D9492
_021D942C:
	add r5, #0x34
	add r0, r5, #0
	bl MOD63_021D96A0
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _021D9492
_021D943C:
	add r0, r5, #0
	add r0, #0x34
	bl MOD63_021D9810
	mov r0, #1
	add r5, #0x39
	strb r0, [r5]
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	b _021D9492
_021D9452:
	add r0, r5, #0
	ldr r1, [r5, #4]
	add r0, #0x34
	bl MOD63_021D99EC
	cmp r0, #0
	beq _021D9466
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_021D9466:
	ldr r0, [r5, #0x44]
	bl MOD63_021DAC18
	add r0, r5, #0
	add r0, #0x39
	ldrb r0, [r0]
	cmp r0, #0
	beq _021D9480
	add r5, #0x34
	add r0, r5, #0
	bl MOD63_021D9980
	b _021D9492
_021D9480:
	ldr r0, [r5, #0x4c]
	bl MOD63_021DB5A8
	b _021D9492
_021D9488:
	add r0, r5, #0
	bl MOD63_021D95A8
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D9492:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021D93F0

	thumb_func_start MOD63_021D9498
MOD63_021D9498: ; 0x021D9498
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	bl MOD63_021D88B0
	add r0, r5, #0
	bl MOD63_021D8A04
	add r0, r5, #0
	bl MOD63_021D8BD8
	bl MOD63_021DA6E0
	add r4, r0, #0
	bl MOD63_021DB498
	add r6, r0, #0
	mov r0, #0x4c
	add r1, r4, #0
	bl AllocFromHeap
	str r0, [r5, #0x44]
	mov r0, #0x10
	bl MOD63_021DAF20
	str r0, [r5, #0x48]
	mov r0, #0x4c
	add r1, r6, #0
	bl AllocFromHeap
	str r0, [r5, #0x4c]
	ldr r0, [r5, #0x44]
	mov r1, #0
	add r2, r4, #0
	bl memset
	ldr r0, [r5, #0x4c]
	mov r1, #0
	add r2, r6, #0
	bl memset
	add r0, r5, #0
	mov r1, #4
	add r0, #0x3b
	strb r1, [r0]
	ldr r0, [r5, #0x4c]
	bl MOD63_021DB49C
	ldr r0, [r5, #0xc]
	mov r1, #1
	str r0, [r5, #0x40]
	ldr r0, _021D9588 ; =gUnk021C4918
	strb r1, [r0, #5]
	bl FUN_0201E7A0
	ldr r6, _021D958C ; =0x021DBDE8
	ldr r7, _021D9590 ; =0x021DBAD0
	mov r4, #0
_021D950C:
	mov r0, #0xc
	add r1, r4, #0
	mul r1, r0
	add r3, r6, r1
	ldr r2, [r3, #4]
	ldr r1, [r6, r1]
	ldr r3, [r3, #8]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	add r0, r4, #0
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl FUN_020B8418
	lsl r1, r4, #1
	ldrh r1, [r7, r1]
	add r0, r4, #0
	bl FUN_020B8404
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021D950C
	ldr r0, _021D9594 ; =0x00004210
	ldr r1, _021D9598 ; =0x0000318A
	mov r2, #0
	bl FUN_020B83E0
	ldr r0, _021D959C ; =0x00004A52
	ldr r1, _021D95A0 ; =0x000039CE
	mov r2, #0
	bl FUN_020B83BC
	mov r0, #0x1f
	str r0, [sp]
	mov r0, #2
	lsl r0, r0, #0xe
	mov r1, #0
	str r0, [sp, #4]
	mov r0, #0xd
	mov r2, #2
	add r3, r1, #0
	bl FUN_020B8390
	ldr r0, _021D95A4 ; =MOD63_021D8CB0
	add r1, r5, #0
	bl FUN_02015F10
	mov r0, #0x10
	mov r1, #1
	mov r2, #2
	bl FUN_0200A274
	mov r0, #1
	add r5, #0x36
	strb r0, [r5]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9588: .word gUnk021C4918
_021D958C: .word 0x021DBDE8
_021D9590: .word 0x021DBAD0
_021D9594: .word 0x00004210
_021D9598: .word 0x0000318A
_021D959C: .word 0x00004A52
_021D95A0: .word 0x000039CE
_021D95A4: .word MOD63_021D8CB0
	thumb_func_end MOD63_021D9498

	thumb_func_start MOD63_021D95A8
MOD63_021D95A8: ; 0x021D95A8
	push {r4, r5, r6, lr}
	mov r2, #1
	lsl r2, r2, #0x1a
	add r5, r0, #0
	ldr r1, [r2]
	ldr r0, _021D969C ; =0xFFFF1FFF
	and r0, r1
	str r0, [r2]
	add r0, r5, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #0
	beq _021D95F6
	bl FUN_0201EB98
	ldr r0, [r5, #0x78]
	bl FUN_0201EB70
	mov r4, #0
	mov r6, #0x58
_021D95D0:
	add r0, r4, #0
	mul r0, r6
	add r0, r5, r0
	add r0, #0xd0
	ldr r0, [r0]
	bl FreeToHeap
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #6
	blo _021D95D0
	ldr r0, [r5, #0x70]
	bl FreeToHeap
	add r0, r5, #0
	mov r1, #0
	add r0, #0x38
	strb r1, [r0]
_021D95F6:
	add r0, r5, #0
	add r0, #0x37
	ldrb r0, [r0]
	cmp r0, #0
	beq _021D9624
	ldr r0, [r5, #0x44]
	bl MOD63_021DAA04
	mov r4, #0
_021D9608:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x50]
	bl FreeToHeap
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021D9608
	add r0, r5, #0
	mov r1, #0
	add r0, #0x37
	strb r1, [r0]
_021D9624:
	add r0, r5, #0
	add r0, #0x36
	ldrb r0, [r0]
	cmp r0, #0
	beq _021D9690
	ldr r0, [r5, #0x48]
	cmp r0, #0
	beq _021D963C
	bl MOD63_021DAF4C
	mov r0, #0
	str r0, [r5, #0x48]
_021D963C:
	ldr r0, [r5, #0x44]
	cmp r0, #0
	beq _021D964A
	bl FreeToHeap
	mov r0, #0
	str r0, [r5, #0x44]
_021D964A:
	ldr r0, [r5, #0x4c]
	cmp r0, #0
	beq _021D965E
	bl MOD63_021DB580
	ldr r0, [r5, #0x4c]
	bl FreeToHeap
	mov r0, #0
	str r0, [r5, #0x4c]
_021D965E:
	ldr r0, [r5, #0xc]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r5, #0xc]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r5, #0xc]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r5, #0xc]
	mov r1, #4
	bl FUN_020178A0
	ldr r0, [r5, #0xc]
	bl FreeToHeap
	ldr r0, [r5, #0x10]
	bl FUN_020223BC
	mov r0, #0
	add r5, #0x36
	strb r0, [r5]
_021D9690:
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	pop {r4, r5, r6, pc}
	nop
_021D969C: .word 0xFFFF1FFF
	thumb_func_end MOD63_021D95A8

	thumb_func_start MOD63_021D96A0
MOD63_021D96A0: ; 0x021D96A0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	ldr r3, _021D980C ; =0x021DBB2C
	add r2, sp, #0x18
	add r5, r0, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	mov r0, #0x80
	mov r1, #0x4c
	bl NARC_ctor
	str r0, [sp, #0x10]
	add r0, r5, #0
	str r0, [sp, #0x14]
	add r0, #0x2c
	mov r4, #0
	str r0, [sp, #0x14]
_021D96C6:
	lsl r7, r4, #2
	add r1, sp, #0x18
	ldr r0, [sp, #0x10]
	ldr r1, [r1, r7]
	mov r2, #0x4c
	add r6, r5, r7
	bl NARC_AllocAndReadWholeMember
	str r0, [r6, #0x1c]
	cmp r0, #0
	beq _021D96F4
	ldr r1, [sp, #0x14]
	add r1, r1, r7
	bl FUN_020B0138
	cmp r0, #0
	bne _021D96F8
	ldr r0, [r6, #0x2c]
	bl FreeToHeap
	bl ErrorHandling
	b _021D96F8
_021D96F4:
	bl ErrorHandling
_021D96F8:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021D96C6
	ldr r0, [sp, #0x10]
	bl NARC_dtor
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r5, #0xc]
	mov r0, #0x80
	mov r1, #0x1c
	mov r3, #3
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r5, #0xc]
	mov r0, #0x80
	mov r1, #0x1a
	mov r3, #3
	bl FUN_020068C8
	mov r1, #0
	str r1, [sp]
	ldr r0, [r5, #0x2c]
	mov r2, #0xa
	add r3, r1, #0
	bl MOD63_021D9EA8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r5, #0xc]
	mov r0, #0x80
	mov r1, #0x11
	mov r3, #4
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r5, #0xc]
	mov r0, #0x80
	mov r1, #0xf
	mov r3, #4
	bl FUN_020068C8
	mov r0, #1
	lsl r0, r0, #8
	str r0, [sp]
	mov r0, #0x4c
	str r0, [sp, #4]
	mov r0, #0x80
	mov r1, #0x10
	mov r2, #4
	mov r3, #0
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r5, #0xc]
	mov r0, #0x80
	mov r1, #0x1b
	mov r3, #1
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r5, #0xc]
	mov r0, #0x80
	mov r1, #0x19
	mov r3, #1
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r5, #0xc]
	mov r0, #0x80
	mov r1, #0x18
	mov r3, #2
	bl FUN_020068C8
	ldr r0, [r5, #0x10]
	bl MOD63_021DA6E8
	ldr r0, [r5, #0x10]
	bl MOD63_021DAA5C
	ldr r0, [r5, #0x10]
	ldr r1, [r5, #0x14]
	bl MOD63_021DABCC
	mov r0, #0xe
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #1
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #0
	bl FUN_0200E394
	mov r0, #1
	bl FUN_0200E394
	mov r0, #1
	strb r0, [r5, #3]
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D980C: .word 0x021DBB2C
	thumb_func_end MOD63_021D96A0

	thumb_func_start MOD63_021D9810
MOD63_021D9810: ; 0x021D9810
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r5, r0, #0
	mov r0, #0x80
	mov r1, #0x46
	mov r2, #0x4c
	bl AllocAndReadWholeNarcMemberByIdPair
	str r0, [r5, #0x3c]
	bl FUN_020BC0FC
	str r0, [r5, #0x40]
	bl FUN_0201B3C4
	cmp r0, #0
	bne _021D9834
	bl ErrorHandling
_021D9834:
	ldr r0, [r5, #0x40]
	ldr r0, [r0, #0x14]
	cmp r0, #0
	bne _021D9840
	bl ErrorHandling
_021D9840:
	ldr r2, [r5, #0x40]
	ldr r0, [r5, #0x3c]
	ldr r1, [r2, #0x14]
	add r1, r2, r1
	sub r1, r1, r0
	bl FUN_02016B44
	mov r0, #0x80
	mov r1, #0x4c
	bl NARC_ctor
	str r0, [sp, #0xc]
	add r0, r5, #0
	str r0, [sp, #0x10]
	add r0, #0x48
	mov r7, #0
	str r0, [sp, #0x10]
_021D9862:
	ldr r1, _021D9964 ; =0x021DBB90
	lsl r2, r7, #2
	ldr r1, [r1, r2]
	mov r0, #0x58
	add r6, r7, #0
	mul r6, r0
	ldr r0, [sp, #0xc]
	mov r2, #0x4c
	bl NARC_AllocAndReadWholeMember
	add r1, r5, r6
	add r1, #0x9c
	str r0, [r1]
	add r0, r5, r6
	add r0, #0x9c
	ldr r0, [r0]
	ldr r1, [r5, #0x40]
	bl FUN_0201B3A8
	cmp r0, #0
	bne _021D9890
	bl ErrorHandling
_021D9890:
	add r0, r5, r6
	add r0, #0x9c
	ldr r0, [r0]
	bl FUN_020BC13C
	ldrb r0, [r0, #9]
	cmp r0, #1
	beq _021D98A4
	bl ErrorHandling
_021D98A4:
	add r0, r5, r6
	add r0, #0x9c
	ldr r0, [r0]
	bl FUN_020BC13C
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r4, r0, r1
	bne _021D98BC
	bl ErrorHandling
_021D98BC:
	ldr r0, [sp, #0x10]
	add r1, r4, #0
	add r0, r0, r6
	bl FUN_020B80B4
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x40
	bl FUN_020BC094
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x80
	bl FUN_020BC094
	mov r2, #2
	add r0, r4, #0
	mov r1, #0
	lsl r2, r2, #8
	bl FUN_020BC094
	mov r2, #1
	add r0, r4, #0
	mov r1, #0
	lsl r2, r2, #0xa
	bl FUN_020BC094
	add r0, r4, #0
	mov r1, #0
	mov r2, #0xf
	bl FUN_020BC02C
	add r0, r7, #1
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	cmp r7, #6
	blo _021D9862
	ldr r0, [sp, #0xc]
	bl NARC_dtor
	mov r0, #0x4c
	bl FUN_0201EB64
	add r3, sp, #0x20
	ldr r4, _021D9968 ; =0x021DBAE4
	str r0, [r5, #0x44]
	ldmia r4!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	ldr r1, _021D996C ; =0x0029AEC1
	str r0, [r3]
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [r5, #0x44]
	ldr r3, _021D9970 ; =0x000005C1
	str r0, [sp, #8]
	add r0, r2, #0
	ldr r2, _021D9974 ; =0x021DBB80
	bl FUN_0201ECA8
	ldr r0, _021D9978 ; =0x00000981
	ldr r1, [r5, #0x44]
	bl FUN_0201EEF0
	ldr r4, _021D997C ; =0x021DBB08
	add r3, sp, #0x14
	ldmia r4!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	str r0, [r3]
	ldr r1, [r5, #0x44]
	add r0, r2, #0
	bl FUN_0201EF70
	ldr r0, [r5, #0x44]
	bl FUN_0201EB8C
	mov r0, #1
	strb r0, [r5, #4]
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D9964: .word 0x021DBB90
_021D9968: .word 0x021DBAE4
_021D996C: .word 0x0029AEC1
_021D9970: .word 0x000005C1
_021D9974: .word 0x021DBB80
_021D9978: .word 0x00000981
_021D997C: .word 0x021DBB08
	thumb_func_end MOD63_021D9810

	thumb_func_start MOD63_021D9980
MOD63_021D9980: ; 0x021D9980
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	ldr r4, _021D99E4 ; =0x021DBD4C
	add r5, r0, #0
	add r3, sp, #0x18
	mov r2, #4
_021D998C:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D998C
	ldr r0, [r4]
	add r2, sp, #0xc
	str r0, [r3]
	ldr r3, _021D99E8 ; =0x021DBAFC
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, sp, #0
	str r0, [r2]
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	bl FUN_020222AC
	bl FUN_0201EBA4
	mov r4, #0
	add r5, #0x48
	add r7, sp, #0
	mov r6, #0x58
_021D99BE:
	add r0, r4, #0
	mul r0, r6
	add r0, r5, r0
	add r1, r7, #0
	add r2, sp, #0x18
	add r3, sp, #0xc
	bl FUN_0201B26C
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #6
	blo _021D99BE
	mov r0, #0
	mov r1, #1
	bl FUN_020222B4
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D99E4: .word 0x021DBD4C
_021D99E8: .word 0x021DBAFC
	thumb_func_end MOD63_021D9980

	thumb_func_start MOD63_021D99EC
MOD63_021D99EC: ; 0x021D99EC
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldrb r0, [r4, #6]
	add r5, r1, #0
	cmp r0, #0
	bne _021D9A00
	ldr r0, [r4, #0x14]
	bl MOD63_021DB38C
_021D9A00:
	ldrb r0, [r4, #6]
	ldrb r1, [r4, #7]
	add r0, r0, #1
	bl _s32_div_f
	strb r1, [r4, #6]
	ldrb r0, [r4, #1]
	cmp r0, #0x11
	bhi _021D9B0C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9A1E: ; jump table
	.short _021D9A42 - _021D9A1E - 2 ; case 0
	.short _021D9A6A - _021D9A1E - 2 ; case 1
	.short _021D9A7A - _021D9A1E - 2 ; case 2
	.short _021D9AB8 - _021D9A1E - 2 ; case 3
	.short _021D9AEE - _021D9A1E - 2 ; case 4
	.short _021D9B3E - _021D9A1E - 2 ; case 5
	.short _021D9B72 - _021D9A1E - 2 ; case 6
	.short _021D9BC8 - _021D9A1E - 2 ; case 7
	.short _021D9C04 - _021D9A1E - 2 ; case 8
	.short _021D9C70 - _021D9A1E - 2 ; case 9
	.short _021D9CB4 - _021D9A1E - 2 ; case 10
	.short _021D9CFC - _021D9A1E - 2 ; case 11
	.short _021D9D38 - _021D9A1E - 2 ; case 12
	.short _021D9D94 - _021D9A1E - 2 ; case 13
	.short _021D9DF8 - _021D9A1E - 2 ; case 14
	.short _021D9E48 - _021D9A1E - 2 ; case 15
	.short _021D9E84 - _021D9A1E - 2 ; case 16
	.short _021D9E9A - _021D9A1E - 2 ; case 17
_021D9A42:
	mov r0, #0xa
	lsl r0, r0, #6
	cmp r5, r0
	blt _021D9B0C
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E74C
	mov r0, #2
	str r0, [sp]
	mov r0, #8
	mov r1, #0
	mov r2, #0x10
	mov r3, #1
	bl FUN_0200A208
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9A6A:
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl MOD63_021DACA0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9A7A:
	ldr r0, _021D9DCC ; =0x000002E9
	cmp r5, r0
	bne _021D9A88
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
_021D9A88:
	ldr r0, _021D9DD0 ; =0x000003C5
	cmp r5, r0
	blt _021D9B0C
	mov r0, #7
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x12
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	ldr r3, _021D9DD4 ; =0x00007FFF
	mov r0, #3
	add r2, r1, #0
	bl FUN_0200E1D0
	mov r0, #0x10
	strb r0, [r4, #7]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9AB8:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD63_021D9F38
	ldr r0, [r4, #0x10]
	add r1, r5, #0
	bl MOD63_021DAD6C
	ldr r0, _021D9DD8 ; =0x00000631
	cmp r5, r0
	blt _021D9B0C
	mov r0, #0x12
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4c
	mov r1, #0
	str r0, [sp, #8]
	ldr r3, _021D9DD4 ; =0x00007FFF
	mov r0, #3
	add r2, r1, #0
	bl FUN_0200E1D0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9AEE:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD63_021D9F38
	ldr r0, [r4, #0x10]
	add r1, r5, #0
	bl MOD63_021DAD6C
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9B0C
	ldr r0, _021D9DDC ; =0x0000064A
	cmp r5, r0
	bge _021D9B0E
_021D9B0C:
	b _021D9EA0
_021D9B0E:
	ldr r0, [r4, #0x10]
	mov r1, #0
	mov r2, #1
	bl MOD63_021DAC24
	bl MOD63_021D8CC0
	mov r0, #0
	strb r0, [r4, #5]
	mov r0, #0x12
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	ldr r3, _021D9DD4 ; =0x00007FFF
	mov r0, #3
	add r2, r1, #0
	bl FUN_0200E1D0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9B3E:
	add r0, r4, #0
	bl MOD63_021D9EE0
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9C12
	ldr r0, _021D9DE0 ; =0x000006B3
	cmp r5, r0
	blt _021D9C12
	mov r0, #4
	str r0, [sp]
	mov r1, #0
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9B72:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9C12
	mov r1, #0
	ldr r0, _021D9DE4 ; =0x04000050
	mov r2, #0x38
	add r3, r1, #0
	str r1, [sp]
	bl G2x_SetBlendAlpha_
	mov r0, #6
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #8
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	mov r1, #0
	ldr r0, [r4, #0x10]
	add r2, r1, #0
	bl MOD63_021DAD18
	mov r0, #4
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9BC8:
	add r0, r4, #0
	bl MOD63_021D9F20
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9C12
	ldr r0, [r4, #0x18]
	mov r1, #0
	add r2, r5, #0
	bl MOD63_021DB5CC
	cmp r0, #0
	beq _021D9C12
	mov r0, #4
	str r0, [sp]
	mov r1, #0
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9C04:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9C12
	ldr r0, _021D9DE8 ; =0x00000721
	cmp r5, r0
	bge _021D9C14
_021D9C12:
	b _021D9EA0
_021D9C14:
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl MOD63_021DACA0
	mov r1, #0
	ldr r0, [r4, #0x10]
	add r2, r1, #0
	bl MOD63_021DAC24
	mov r1, #1
	ldr r0, [r4, #0x10]
	add r2, r1, #0
	bl MOD63_021DAC24
	ldr r0, [r4, #0x10]
	mov r1, #0
	mov r2, #1
	bl MOD63_021DAD18
	mov r1, #0
	str r1, [sp]
	ldr r0, [r4, #0x38]
	mov r2, #7
	add r3, r1, #0
	bl MOD63_021D9EA8
	ldr r0, [r4, #0x10]
	mov r1, #2
	mov r2, #1
	bl MOD63_021DAC24
	mov r0, #4
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9C70:
	add r0, r4, #0
	bl MOD63_021D9F20
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9D46
	ldr r0, _021D9DE8 ; =0x00000721
	cmp r5, r0
	blt _021D9D46
	ldr r0, [r4, #0x10]
	bl MOD63_021DACC0
	cmp r0, #0
	beq _021D9D46
	ldr r0, _021D9DEC ; =0x00000785
	cmp r5, r0
	blt _021D9D46
	mov r0, #4
	str r0, [sp]
	mov r1, #0
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9CB4:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9D46
	ldr r0, [r4, #0x10]
	mov r1, #1
	mov r2, #0
	bl MOD63_021DAD18
	mov r1, #0
	str r1, [sp]
	ldr r0, [r4, #0x30]
	mov r2, #7
	add r3, r1, #0
	bl MOD63_021D9EA8
	ldr r0, [r4, #0x10]
	mov r1, #2
	mov r2, #0
	bl MOD63_021DAC24
	mov r0, #4
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9CFC:
	add r0, r4, #0
	bl MOD63_021D9F20
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9D46
	ldr r0, [r4, #0x18]
	mov r1, #1
	add r2, r5, #0
	bl MOD63_021DB5CC
	cmp r0, #0
	beq _021D9D46
	mov r0, #4
	str r0, [sp]
	mov r1, #0
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9D38:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9D46
	ldr r0, _021D9DF0 ; =0x000007F8
	cmp r5, r0
	bgt _021D9D48
_021D9D46:
	b _021D9EA0
_021D9D48:
	mov r1, #1
	ldr r0, [r4, #0x10]
	add r2, r1, #0
	bl MOD63_021DAD18
	mov r0, #4
	mov r1, #1
	bl FUN_0201E6E4
	ldr r0, [r4, #0x10]
	mov r1, #0
	mov r2, #1
	bl MOD63_021DAC24
	ldr r0, [r4, #0x10]
	bl MOD63_021DAC6C
	ldr r0, [r4, #0x10]
	mov r1, #4
	bl MOD63_021DAC80
	mov r0, #4
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	mov r0, #0
	str r0, [r4, #8]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9D94:
	add r0, r4, #0
	bl MOD63_021D9F00
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9EA0
	ldr r0, _021D9DF4 ; =0x00000861
	cmp r5, r0
	ble _021D9EA0
	mov r0, #4
	str r0, [sp]
	mov r1, #0
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	mov r0, #0
	str r0, [r4, #8]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
	.align 2, 0
_021D9DCC: .word 0x000002E9
_021D9DD0: .word 0x000003C5
_021D9DD4: .word 0x00007FFF
_021D9DD8: .word 0x00000631
_021D9DDC: .word 0x0000064A
_021D9DE0: .word 0x000006B3
_021D9DE4: .word 0x04000050
_021D9DE8: .word 0x00000721
_021D9DEC: .word 0x00000785
_021D9DF0: .word 0x000007F8
_021D9DF4: .word 0x00000861
_021D9DF8:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9EA0
	mov r1, #0
	ldr r0, [r4, #0x10]
	add r2, r1, #0
	bl MOD63_021DAD18
	ldr r0, [r4, #0x10]
	mov r1, #1
	mov r2, #0
	bl MOD63_021DAD18
	mov r1, #0
	str r1, [sp]
	ldr r0, [r4, #0x34]
	mov r2, #7
	add r3, r1, #0
	bl MOD63_021D9EA8
	mov r0, #4
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #4
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9E48:
	add r0, r4, #0
	bl MOD63_021D9F20
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9EA0
	ldr r0, [r4, #0x18]
	mov r1, #2
	add r2, r5, #0
	bl MOD63_021DB5CC
	cmp r0, #0
	beq _021D9EA0
	mov r0, #0x12
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9E84:
	add r0, r4, #0
	bl MOD63_021D9F20
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9EA0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021D9EA0
_021D9E9A:
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_021D9EA0:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021D99EC

	thumb_func_start MOD63_021D9EA8
MOD63_021D9EA8: ; 0x021D9EA8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	lsl r7, r2, #5
	add r6, r1, #0
	ldr r0, [r5, #0xc]
	add r1, r7, #0
	add r4, r3, #0
	bl DC_FlushRange
	ldr r1, [r5, #0xc]
	cmp r6, #0
	bne _021D9ED0
	lsl r0, r4, #1
	add r0, r1, r0
	add r1, sp, #8
	ldrb r1, [r1, #0x10]
	add r2, r7, #0
	bl GX_LoadBGPltt
	pop {r3, r4, r5, r6, r7, pc}
_021D9ED0:
	lsl r0, r4, #1
	add r0, r1, r0
	add r1, sp, #8
	ldrb r1, [r1, #0x10]
	add r2, r7, #0
	bl GXS_LoadBGPltt
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD63_021D9EA8

	thumb_func_start MOD63_021D9EE0
MOD63_021D9EE0: ; 0x021D9EE0
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #8]
	add r0, r1, #1
	str r0, [r4, #8]
	cmp r1, #0x18
	ble _021D9EFE
	mov r2, #4
	ldr r0, [r4, #0xc]
	mov r1, #1
	sub r3, r2, #5
	bl FUN_020179E0
	mov r0, #0
	str r0, [r4, #8]
_021D9EFE:
	pop {r4, pc}
	thumb_func_end MOD63_021D9EE0

	thumb_func_start MOD63_021D9F00
MOD63_021D9F00: ; 0x021D9F00
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #8]
	add r0, r1, #1
	str r0, [r4, #8]
	cmp r1, #3
	ble _021D9F1E
	mov r2, #1
	ldr r0, [r4, #0xc]
	mov r1, #2
	add r3, r2, #0
	bl FUN_020179E0
	mov r0, #0
	str r0, [r4, #8]
_021D9F1E:
	pop {r4, pc}
	thumb_func_end MOD63_021D9F00

	thumb_func_start MOD63_021D9F20
MOD63_021D9F20: ; 0x021D9F20
	push {r4, lr}
	add r4, r0, #0
	mov r2, #1
	add r3, r2, #0
	ldr r0, [r4, #0xc]
	mov r1, #3
	sub r3, #0x11
	bl FUN_020179E0
	mov r0, #0
	str r0, [r4, #8]
	pop {r4, pc}
	thumb_func_end MOD63_021D9F20

	thumb_func_start MOD63_021D9F38
MOD63_021D9F38: ; 0x021D9F38
	push {r4, r5, r6, lr}
	sub sp, #0x50
	add r4, r0, #0
	add r5, r1, #0
	add r0, sp, #0x44
	mov r1, #0
	str r1, [r0]
	str r1, [r0, #4]
	str r1, [r0, #8]
	ldr r1, _021DA078 ; =0x000004AB
	cmp r5, r1
	bgt _021D9FE2
	ldr r0, [r4, #0x44]
	bl FUN_0201F008
	ldr r1, _021DA07C ; =0x000005C1
	sub r0, #0x20
	cmp r0, r1
	ble _021D9F68
	ldr r0, _021DA080 ; =0x0000FFE0
	ldr r1, [r4, #0x44]
	bl FUN_0201EF2C
	b _021D9F70
_021D9F68:
	add r0, r1, #0
	ldr r1, [r4, #0x44]
	bl FUN_0201EEF0
_021D9F70:
	mov r0, #2
	ldr r1, [sp, #0x4c]
	lsl r0, r0, #0xc
	sub r0, r1, r0
	str r0, [sp, #0x4c]
	ldr r1, [r4, #0x44]
	add r0, sp, #0x44
	bl FUN_0201EF70
	ldr r0, _021DA078 ; =0x000004AB
	cmp r5, r0
	bne _021DA074
	ldr r5, _021DA084 ; =0x021DBAD8
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	ldr r1, _021DA088 ; =0x0029AEC1
	str r0, [r3]
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [r4, #0x44]
	ldr r3, _021DA07C ; =0x000005C1
	str r0, [sp, #8]
	add r0, r2, #0
	ldr r2, _021DA08C ; =0x021DBB80
	bl FUN_0201ECA8
	ldr r5, _021DA090 ; =0x021DBB20
	add r3, sp, #0x2c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	ldr r1, [r4, #0x44]
	add r0, r2, #0
	bl FUN_0201EF70
	ldr r2, _021DA094 ; =0x021DBAC8
	add r1, sp, #0xc
	ldrh r3, [r2]
	add r0, sp, #0xc
	strh r3, [r1]
	ldrh r3, [r2, #2]
	strh r3, [r1, #2]
	ldrh r3, [r2, #4]
	ldrh r2, [r2, #6]
	strh r3, [r1, #4]
	strh r2, [r1, #6]
	ldr r1, [r4, #0x44]
	bl FUN_0201EFB4
	add sp, #0x50
	pop {r4, r5, r6, pc}
_021D9FE2:
	add r1, #0xd2
	cmp r5, r1
	bgt _021DA044
	mov r1, #1
	ldr r2, [sp, #0x44]
	lsl r1, r1, #0xc
	add r1, r2, r1
	str r1, [sp, #0x44]
	ldr r1, [r4, #0x44]
	bl FUN_0201EF70
	ldr r3, _021DA098 ; =0x0000057D
	cmp r5, r3
	bne _021DA074
	ldr r6, _021DA09C ; =0x021DBB14
	add r5, sp, #0x20
	ldmia r6!, {r0, r1}
	add r2, r5, #0
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	ldr r1, _021DA088 ; =0x0029AEC1
	str r0, [r5]
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [r4, #0x44]
	add r3, #0x44
	str r0, [sp, #8]
	add r0, r2, #0
	ldr r2, _021DA08C ; =0x021DBB80
	bl FUN_0201ECA8
	ldr r0, _021DA07C ; =0x000005C1
	ldr r1, [r4, #0x44]
	bl FUN_0201EEF0
	ldr r5, _021DA0A0 ; =0x021DBAF0
	add r3, sp, #0x14
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	ldr r1, [r4, #0x44]
	add r0, r2, #0
	bl FUN_0201EF70
	add sp, #0x50
	pop {r4, r5, r6, pc}
_021DA044:
	ldr r0, _021DA0A4 ; =0x00000618
	cmp r5, r0
	blt _021DA062
	ldr r0, [r4, #0x44]
	bl FUN_0201F008
	mov r1, #1
	add r0, #0x20
	lsl r1, r1, #0xe
	cmp r0, r1
	bge _021DA062
	ldr r1, [r4, #0x44]
	mov r0, #0x20
	bl FUN_0201EF2C
_021DA062:
	mov r0, #1
	ldr r1, [sp, #0x4c]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x4c]
	ldr r1, [r4, #0x44]
	add r0, sp, #0x44
	bl FUN_0201EF70
_021DA074:
	add sp, #0x50
	pop {r4, r5, r6, pc}
	.align 2, 0
_021DA078: .word 0x000004AB
_021DA07C: .word 0x000005C1
_021DA080: .word 0x0000FFE0
_021DA084: .word 0x021DBAD8
_021DA088: .word 0x0029AEC1
_021DA08C: .word 0x021DBB80
_021DA090: .word 0x021DBB20
_021DA094: .word 0x021DBAC8
_021DA098: .word 0x0000057D
_021DA09C: .word 0x021DBB14
_021DA0A0: .word 0x021DBAF0
_021DA0A4: .word 0x00000618
	thumb_func_end MOD63_021D9F38

	thumb_func_start MOD63_021DA0A8
MOD63_021DA0A8: ; 0x021DA0A8
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	mov r5, #0xa3
	lsl r5, r5, #2
	cmp r0, #0
	beq _021DA0BA
	mov r0, #3
	strb r0, [r4, r5]
_021DA0BA:
	ldrb r0, [r4, r5]
	cmp r0, #3
	bhi _021DA116
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DA0CC: ; jump table
	.short _021DA0D4 - _021DA0CC - 2 ; case 0
	.short _021DA0E2 - _021DA0CC - 2 ; case 1
	.short _021DA0F4 - _021DA0CC - 2 ; case 2
	.short _021DA10C - _021DA0CC - 2 ; case 3
_021DA0D4:
	add r0, r4, #0
	bl MOD63_021DA11C
	ldrb r0, [r4, r5]
	add r0, r0, #1
	strb r0, [r4, r5]
	b _021DA116
_021DA0E2:
	mov r0, #0xa3
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD63_021DA158
	ldrb r0, [r4, r5]
	add r0, r0, #1
	strb r0, [r4, r5]
	b _021DA116
_021DA0F4:
	mov r0, #0xa3
	lsl r0, r0, #2
	ldr r1, [r4, #4]
	add r0, r4, r0
	bl MOD63_021DA30C
	cmp r0, #0
	beq _021DA116
	ldrb r0, [r4, r5]
	add r0, r0, #1
	strb r0, [r4, r5]
	b _021DA116
_021DA10C:
	add r0, r4, #0
	bl MOD63_021DA418
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DA116:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021DA0A8

	thumb_func_start MOD63_021DA11C
MOD63_021DA11C: ; 0x021DA11C
	push {r4, lr}
	add r4, r0, #0
	bl MOD63_021D88D0
	add r0, r4, #0
	bl MOD63_021D8ADC
	mov r0, #0xa6
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, _021DA150 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	ldr r0, _021DA154 ; =0x0000028E
	mov r1, #1
	strb r1, [r4, r0]
	pop {r4, pc}
	.align 2, 0
_021DA150: .word 0x04000050
_021DA154: .word 0x0000028E
	thumb_func_end MOD63_021DA11C

	thumb_func_start MOD63_021DA158
MOD63_021DA158: ; 0x021DA158
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r4, r0, #0
	mov r0, #0x80
	mov r1, #0x4c
	bl NARC_ctor
	mov r1, #0x35
	mov r2, #0x4c
	add r5, r0, #0
	bl NARC_AllocAndReadWholeMember
	str r0, [r4, #0x10]
	cmp r0, #0
	beq _021DA18E
	add r1, r4, #0
	add r1, #0x14
	bl FUN_020B0138
	cmp r0, #0
	bne _021DA192
	ldr r0, [r4, #0x14]
	bl FreeToHeap
	bl ErrorHandling
	b _021DA192
_021DA18E:
	bl ErrorHandling
_021DA192:
	add r0, r5, #0
	bl NARC_dtor
	mov r1, #0
	str r1, [sp]
	ldr r0, [r4, #0x14]
	mov r2, #9
	add r3, r1, #0
	bl MOD63_021D9EA8
	mov r3, #0
	str r3, [sp]
	ldr r0, [r4, #0x14]
	mov r1, #1
	mov r2, #9
	bl MOD63_021D9EA8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x36
	mov r3, #1
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x3b
	mov r3, #1
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x38
	mov r3, #2
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x3d
	mov r3, #2
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x39
	mov r3, #3
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x3e
	mov r3, #3
	bl FUN_020068C8
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x3a
	bl FUN_0200687C
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x3f
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x37
	mov r3, #5
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x3c
	mov r3, #5
	bl FUN_020068C8
	mov r0, #0xe
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #1
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #2
	mov r1, #1
	bl FUN_0201E74C
	ldr r0, [r4, #0xc]
	mov r1, #3
	mov r2, #1
	mov r3, #0x40
	bl FUN_020179E0
	mov r0, #1
	lsl r0, r0, #0xc
	bl FX_Inv
	add r5, r0, #0
	mov r0, #1
	lsl r0, r0, #0xc
	bl FX_Inv
	mov r1, #0
	str r5, [sp, #0x10]
	str r1, [sp, #0x14]
	str r1, [sp, #0x18]
	str r0, [sp, #0x1c]
	bl OS_WaitVBlankIntr
	mov r0, #0x60
	str r0, [sp]
	ldr r0, [r4, #0xc]
	mov r1, #2
	add r2, sp, #0x10
	mov r3, #0x80
	bl FUN_02017BD0
	mov r0, #0x60
	str r0, [sp]
	ldr r0, [r4, #0xc]
	mov r1, #3
	add r2, sp, #0x10
	mov r3, #0xc0
	bl FUN_02017BD0
	mov r0, #1
	strb r0, [r4, #3]
	add sp, #0x20
	pop {r3, r4, r5, pc}
	thumb_func_end MOD63_021DA158

	thumb_func_start MOD63_021DA30C
MOD63_021DA30C: ; 0x021DA30C
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r5, r1, #0
	ldrb r1, [r4, #1]
	cmp r1, #3
	bhi _021DA3EC
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DA326: ; jump table
	.short _021DA32E - _021DA326 - 2 ; case 0
	.short _021DA352 - _021DA326 - 2 ; case 1
	.short _021DA36A - _021DA326 - 2 ; case 2
	.short _021DA3DA - _021DA326 - 2 ; case 3
_021DA32E:
	ldr r0, _021DA3F8 ; =0x000008E3
	cmp r5, r0
	blt _021DA3EC
	mov r0, #0x78
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021DA3EC
_021DA352:
	bl FUN_0200E308
	cmp r0, #0
	beq _021DA3EC
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [r4, #4]
	str r0, [r4, #8]
	b _021DA3EC
_021DA36A:
	ldr r0, _021DA3FC ; =0x0000097E
	cmp r5, r0
	bne _021DA378
	add r0, r4, #0
	add r0, #0x18
	bl MOD63_021DA588
_021DA378:
	ldr r0, _021DA400 ; =0x000009D3
	cmp r5, r0
	bne _021DA386
	add r0, r4, #0
	add r0, #0x18
	bl MOD63_021DA588
_021DA386:
	ldr r0, _021DA404 ; =0x000009F1
	cmp r5, r0
	bne _021DA394
	add r0, r4, #0
	add r0, #0x18
	bl MOD63_021DA588
_021DA394:
	ldr r0, _021DA408 ; =0x00000A1E
	cmp r5, r0
	bne _021DA3A2
	add r0, r4, #0
	add r0, #0x18
	bl MOD63_021DA588
_021DA3A2:
	ldr r0, _021DA40C ; =0x00000A64
	cmp r5, r0
	blt _021DA3AE
	add r0, r4, #0
	bl MOD63_021DA478
_021DA3AE:
	ldr r0, _021DA410 ; =0x00000A78
	cmp r5, r0
	blt _021DA3EC
	mov r0, #0x12
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	mov r0, #0
	ldr r3, _021DA414 ; =0x00007FFF
	add r1, r0, #0
	add r2, r0, #0
	bl FUN_0200E1D0
	add r0, r4, #0
	bl MOD63_021DA504
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _021DA3EC
_021DA3DA:
	bl MOD63_021DA504
	bl FUN_0200E308
	cmp r0, #0
	beq _021DA3EC
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_021DA3EC:
	add r0, r4, #0
	bl MOD63_021DA5A0
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_021DA3F8: .word 0x000008E3
_021DA3FC: .word 0x0000097E
_021DA400: .word 0x000009D3
_021DA404: .word 0x000009F1
_021DA408: .word 0x00000A1E
_021DA40C: .word 0x00000A64
_021DA410: .word 0x00000A78
_021DA414: .word 0x00007FFF
	thumb_func_end MOD63_021DA30C

	thumb_func_start MOD63_021DA418
MOD63_021DA418: ; 0x021DA418
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021DA470 ; =0x0000028E
	ldrb r0, [r4, r0]
	cmp r0, #0
	beq _021DA458
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #5
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	bl FreeToHeap
	ldr r0, _021DA470 ; =0x0000028E
	mov r1, #0
	strb r1, [r4, r0]
_021DA458:
	ldr r0, _021DA474 ; =0x0000028F
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _021DA46E
	add r0, #0xd
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r0, _021DA474 ; =0x0000028F
	mov r1, #0
	strb r1, [r4, r0]
_021DA46E:
	pop {r4, pc}
	.align 2, 0
_021DA470: .word 0x0000028E
_021DA474: .word 0x0000028F
	thumb_func_end MOD63_021DA418

	thumb_func_start MOD63_021DA478
MOD63_021DA478: ; 0x021DA478
	push {r4, r5, lr}
	sub sp, #0x2c
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FX_Inv
	add r5, r0, #0
	ldr r0, [r4, #4]
	bl FX_Inv
	mov r1, #0
	str r5, [sp, #0x1c]
	str r1, [sp, #0x20]
	str r1, [sp, #0x24]
	str r0, [sp, #0x28]
	ldr r0, [r4, #8]
	bl FX_Inv
	add r5, r0, #0
	ldr r0, [r4, #8]
	bl FX_Inv
	mov r1, #0
	str r5, [sp, #0xc]
	str r1, [sp, #0x10]
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	bl OS_WaitVBlankIntr
	mov r0, #1
	ldr r1, [r4, #4]
	lsl r0, r0, #0xa
	add r1, r1, r0
	mov r0, #3
	lsl r0, r0, #0xc
	cmp r1, r0
	bgt _021DA4FE
	str r1, [r4, #4]
	add r0, sp, #0x1c
	str r0, [sp]
	mov r0, #0x80
	str r0, [sp, #4]
	mov r0, #0x5a
	str r0, [sp, #8]
	ldr r0, [r4, #0xc]
	mov r1, #2
	mov r2, #4
	mov r3, #1
	bl FUN_02017B60
	mov r0, #1
	ldr r1, [r4, #8]
	lsl r0, r0, #0xa
	add r0, r1, r0
	str r0, [r4, #8]
	add r0, sp, #0xc
	str r0, [sp]
	mov r0, #0xc0
	str r0, [sp, #4]
	mov r0, #0x5a
	str r0, [sp, #8]
	ldr r0, [r4, #0xc]
	mov r1, #3
	mov r2, #4
	mov r3, #1
	bl FUN_02017B60
_021DA4FE:
	add sp, #0x2c
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021DA478

	thumb_func_start MOD63_021DA504
MOD63_021DA504: ; 0x021DA504
	push {r4, r5, lr}
	sub sp, #0x2c
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FX_Inv
	add r5, r0, #0
	ldr r0, [r4, #4]
	bl FX_Inv
	mov r1, #0
	str r5, [sp, #0x1c]
	str r1, [sp, #0x20]
	str r1, [sp, #0x24]
	str r0, [sp, #0x28]
	ldr r0, [r4, #8]
	bl FX_Inv
	add r5, r0, #0
	ldr r0, [r4, #8]
	bl FX_Inv
	mov r1, #0
	str r5, [sp, #0xc]
	str r1, [sp, #0x10]
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	bl OS_WaitVBlankIntr
	mov r0, #2
	ldr r1, [r4, #4]
	lsl r0, r0, #0xa
	add r0, r1, r0
	str r0, [r4, #4]
	add r0, sp, #0x1c
	str r0, [sp]
	mov r0, #0x80
	str r0, [sp, #4]
	mov r0, #0x5a
	str r0, [sp, #8]
	ldr r0, [r4, #0xc]
	mov r1, #2
	mov r2, #4
	mov r3, #1
	bl FUN_02017B60
	mov r0, #2
	ldr r1, [r4, #8]
	lsl r0, r0, #0xa
	add r0, r1, r0
	str r0, [r4, #8]
	add r0, sp, #0xc
	str r0, [sp]
	mov r0, #0xc0
	str r0, [sp, #4]
	mov r0, #0x5a
	str r0, [sp, #8]
	ldr r0, [r4, #0xc]
	mov r1, #3
	mov r2, #4
	mov r3, #1
	bl FUN_02017B60
	add sp, #0x2c
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021DA504

	thumb_func_start MOD63_021DA588
MOD63_021DA588: ; 0x021DA588
	mov r1, #1
	strb r1, [r0]
	mov r2, #6
	strb r2, [r0, #3]
	mov r2, #0
	strb r2, [r0, #1]
	ldr r3, _021DA59C ; =FUN_0201E6E4
	add r0, r1, #0
	bx r3
	nop
_021DA59C: .word FUN_0201E6E4
	thumb_func_end MOD63_021DA588

	thumb_func_start MOD63_021DA5A0
MOD63_021DA5A0: ; 0x021DA5A0
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	ldrb r0, [r5, #0x18]
	add r4, r5, #0
	add r4, #0x18
	cmp r0, #0
	beq _021DA630
	ldrb r3, [r4, #1]
	ldr r0, _021DA634 ; =0x021DBF40
	ldrb r1, [r4, #3]
	ldrb r0, [r0, r3]
	cmp r1, r0
	blo _021DA614
	mov r1, #0
	str r1, [sp]
	ldr r6, _021DA638 ; =0x021DBF48
	ldr r0, [r5, #0x14]
	ldrb r3, [r6, r3]
	mov r2, #1
	lsl r3, r3, #0x1c
	lsr r3, r3, #0x18
	bl MOD63_021D9EA8
	mov r0, #0x20
	str r0, [sp]
	ldrb r6, [r4, #1]
	ldr r3, _021DA63C ; =0x021DBF44
	ldr r0, [r5, #0x14]
	ldrb r3, [r3, r6]
	mov r1, #0
	mov r2, #1
	lsl r3, r3, #0x1c
	lsr r3, r3, #0x18
	bl MOD63_021D9EA8
	mov r0, #0x20
	str r0, [sp]
	ldr r0, [r5, #0x14]
	mov r1, #1
	ldrb r5, [r4, #1]
	ldr r3, _021DA63C ; =0x021DBF44
	add r2, r1, #0
	ldrb r3, [r3, r5]
	lsl r3, r3, #0x1c
	lsr r3, r3, #0x18
	bl MOD63_021D9EA8
	mov r1, #0
	strb r1, [r4, #3]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	ldrb r0, [r4, #1]
	cmp r0, #4
	blo _021DA618
	strb r1, [r4]
	b _021DA618
_021DA614:
	add r0, r1, #1
	strb r0, [r4, #3]
_021DA618:
	ldrb r0, [r4, #1]
	cmp r0, #0
	bne _021DA630
	ldr r0, _021DA634 ; =0x021DBF40
	ldrb r1, [r4, #3]
	ldrb r0, [r0]
	cmp r1, r0
	blo _021DA630
	mov r0, #1
	mov r1, #0
	bl FUN_0201E6E4
_021DA630:
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021DA634: .word 0x021DBF40
_021DA638: .word 0x021DBF48
_021DA63C: .word 0x021DBF44
	thumb_func_end MOD63_021DA5A0

	thumb_func_start MOD63_021DA640
MOD63_021DA640: ; 0x021DA640
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _021DA66C ; =0x021DBE4C
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_0201D040
	mov r0, #5
	mov r1, #0x4c
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021DA66C: .word 0x021DBE4C
	thumb_func_end MOD63_021DA640

	thumb_func_start MOD63_021DA670
MOD63_021DA670: ; 0x021DA670
	push {r3, r4, r5, r6, lr}
	sub sp, #0x2c
	add r6, r0, #0
	mov r0, #0
	str r6, [sp]
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r2, [sp, #0x10]
	mov r2, #0x4b
	add r5, r1, #0
	lsl r2, r2, #2
	ldr r1, [r5, r2]
	add r4, r3, #0
	str r1, [sp, #0x14]
	add r1, r2, #4
	ldr r1, [r5, r1]
	add r3, r6, #0
	str r1, [sp, #0x18]
	add r1, r2, #0
	add r1, #8
	ldr r1, [r5, r1]
	add r2, #0xc
	str r1, [sp, #0x1c]
	ldr r1, [r5, r2]
	add r2, r6, #0
	str r1, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x40]
	add r1, r6, #0
	bl FUN_02008AA4
	ldr r0, [r5]
	mov r1, #0
	str r0, [r4]
	ldr r0, [sp, #0x40]
	str r0, [r4, #4]
	str r1, [r4, #8]
	str r1, [r4, #0xc]
	mov r0, #1
	str r1, [r4, #0x10]
	lsl r0, r0, #0xc
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	strh r1, [r4, #0x20]
	mov r0, #1
	str r0, [r4, #0x24]
	str r0, [r4, #0x28]
	mov r0, #0x4c
	str r0, [r4, #0x2c]
	add sp, #0x2c
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD63_021DA670

	thumb_func_start MOD63_021DA6E0
MOD63_021DA6E0: ; 0x021DA6E0
	mov r0, #0x1b
	lsl r0, r0, #4
	bx lr
	.align 2, 0
	thumb_func_end MOD63_021DA6E0

	thumb_func_start MOD63_021DA6E8
MOD63_021DA6E8: ; 0x021DA6E8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r2, #1
	lsl r2, r2, #0x1a
	add r5, r0, #0
	ldr r1, [r2]
	ldr r0, _021DA9FC ; =0xFFCFFFEF
	and r1, r0
	mov r0, #0x10
	orr r0, r1
	str r0, [r2]
	bl MOD63_021DA640
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x80
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x4c
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	mov r0, #0x19
	add r1, r5, #4
	mov r2, #0x4c
	bl FUN_02008C9C
	mov r2, #1
	str r0, [r5]
	add r0, r5, #4
	mov r1, #0
	lsl r2, r2, #0x14
	bl FUN_02008D24
	ldr r4, _021DAA00 ; =0x021DBE28
	mov r7, #0
	add r6, r5, #0
_021DA73C:
	ldrb r0, [r4]
	add r1, r7, #0
	mov r2, #0x4c
	bl FUN_02008DEC
	mov r1, #0x4b
	lsl r1, r1, #2
	str r0, [r6, r1]
	add r7, r7, #1
	add r4, r4, #1
	add r6, r6, #4
	cmp r7, #4
	blt _021DA73C
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe0
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x26
	bl FUN_02008F34
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe0
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x27
	mov r3, #0
	bl FUN_02008F34
	mov r1, #0x53
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe0
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x28
	mov r3, #0
	bl FUN_02008F34
	mov r1, #0x57
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #3
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe0
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x29
	mov r3, #0
	bl FUN_02008F34
	mov r1, #0x5b
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #4
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe0
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x2a
	mov r3, #0
	bl FUN_02008F34
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	add r0, #0xe4
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x21
	bl FUN_02008FEC
	mov r1, #5
	lsl r1, r1, #6
	str r0, [r5, r1]
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	add r0, #0xe4
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x22
	mov r3, #0
	bl FUN_02008FEC
	mov r1, #0x15
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	add r0, #0xe4
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x23
	mov r3, #0
	bl FUN_02008FEC
	mov r1, #0x16
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #3
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	add r0, #0xe4
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x24
	mov r3, #0
	bl FUN_02008FEC
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #4
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	add r0, #0xe4
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x25
	mov r3, #0
	bl FUN_02008FEC
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r5, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe8
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x2b
	bl FUN_020090AC
	mov r1, #0x51
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe8
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x2c
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x55
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #2
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe8
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x2d
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x59
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #3
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe8
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x2e
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x5d
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #4
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe8
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x2f
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x61
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xec
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x30
	bl FUN_020090AC
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #1
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xec
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x31
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x56
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #2
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xec
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x32
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x5a
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #3
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xec
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x33
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #4
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xec
	ldr r0, [r5, r0]
	mov r1, #0x80
	mov r2, #0x34
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x62
	lsl r1, r1, #2
	add r7, r1, #0
	add r6, r1, #0
	str r0, [r5, r1]
	mov r4, #0
	sub r7, #0x4c
	sub r6, #0x48
_021DA9DC:
	ldr r0, [r5, r7]
	bl FUN_02009A50
	ldr r0, [r5, r6]
	bl FUN_02009CF0
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #5
	blt _021DA9DC
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021DA9FC: .word 0xFFCFFFEF
_021DAA00: .word 0x021DBE28
	thumb_func_end MOD63_021DA6E8

	thumb_func_start MOD63_021DAA04
MOD63_021DAA04: ; 0x021DAA04
	push {r3, r4, r5, r6, r7, lr}
	mov r7, #5
	add r5, r0, #0
	mov r4, #0
	lsl r7, r7, #6
_021DAA0E:
	lsl r0, r4, #4
	add r6, r5, r0
	mov r0, #0x4f
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	ldr r0, [r6, r7]
	bl FUN_02009E04
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #5
	blo _021DAA0E
	mov r6, #0x4b
	mov r4, #0
	lsl r6, r6, #2
_021DAA32:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, r6]
	bl FUN_02008E2C
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021DAA32
	ldr r0, [r5]
	bl FUN_0201FD58
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD63_021DAA04

	thumb_func_start MOD63_021DAA5C
MOD63_021DAA5C: ; 0x021DAA5C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xa4
	ldr r3, _021DABC0 ; =0x021DBE5C
	add r5, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0x38
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r3, _021DABC4 ; =0x021DBE74
	add r2, sp, #0x20
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r3, _021DABC8 ; =0x021DBE8C
	add r2, sp, #8
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, sp, #0x80
	str r0, [sp]
	mov r0, #0
	add r1, r5, #0
	mov r2, #1
	add r3, sp, #0x50
	bl MOD63_021DA670
	mov r0, #5
	lsl r0, r0, #0x10
	str r0, [sp, #0x58]
	mov r0, #7
	lsl r0, r0, #0x10
	str r0, [sp, #0x5c]
	add r0, sp, #0x50
	bl FUN_0201FE94
	mov r1, #0x63
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #0
	bl FUN_020200BC
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add r0, sp, #0x80
	str r0, [sp]
	mov r0, #1
	add r1, r5, #0
	add r2, r0, #0
	add r3, sp, #0x50
	bl MOD63_021DA670
	mov r0, #5
	lsl r0, r0, #0x10
	str r0, [sp, #0x58]
	mov r0, #7
	lsl r0, r0, #0x10
	str r0, [sp, #0x5c]
	add r0, sp, #0x50
	bl FUN_0201FE94
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #0
	bl FUN_020200BC
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add r0, r5, #0
	mov r1, #3
	bl MOD63_021DAC80
	add r0, sp, #0x80
	str r0, [sp]
	mov r0, #2
	add r1, r5, #0
	mov r2, #1
	add r3, sp, #0x50
	bl MOD63_021DA670
	mov r0, #5
	lsl r0, r0, #0x12
	str r0, [sp, #0x58]
	mov r0, #7
	lsl r0, r0, #0x10
	str r0, [sp, #0x5c]
	add r0, sp, #0x50
	bl FUN_0201FE94
	mov r1, #0x65
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0
	str r0, [sp, #4]
	add r7, sp, #0x20
	add r6, sp, #8
	add r4, sp, #0x38
_021DAB58:
	add r0, sp, #0x80
	str r0, [sp]
	mov r0, #3
	add r1, r5, #0
	mov r2, #0
	add r3, sp, #0x50
	bl MOD63_021DA670
	ldr r0, [r7]
	lsl r0, r0, #0xc
	str r0, [sp, #0x58]
	ldr r0, [r6]
	lsl r0, r0, #0xc
	str r0, [sp, #0x5c]
	add r0, sp, #0x50
	bl FUN_0201FE94
	ldr r1, [r4]
	lsl r1, r1, #2
	add r2, r5, r1
	mov r1, #0x63
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	lsl r0, r0, #2
	add r1, r5, r0
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r4]
	lsl r0, r0, #2
	add r1, r5, r0
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [sp, #4]
	add r7, r7, #4
	add r0, r0, #1
	add r6, r6, #4
	add r4, r4, #4
	str r0, [sp, #4]
	cmp r0, #6
	blt _021DAB58
	add sp, #0xa4
	pop {r4, r5, r6, r7, pc}
	nop
_021DABC0: .word 0x021DBE5C
_021DABC4: .word 0x021DBE74
_021DABC8: .word 0x021DBE8C
	thumb_func_end MOD63_021DAA5C

	thumb_func_start MOD63_021DABCC
MOD63_021DABCC: ; 0x021DABCC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x58
	add r2, r0, #0
	add r0, sp, #0x34
	add r6, r1, #0
	str r0, [sp]
	add r1, r2, #0
	mov r0, #4
	mov r2, #0
	add r3, sp, #4
	bl MOD63_021DA670
	mov r0, #2
	str r0, [sp, #0x2c]
	mov r5, #0
	add r7, sp, #4
_021DABEC:
	add r0, r6, #0
	add r1, r5, #0
	bl MOD63_021DAF80
	add r4, r0, #0
	add r0, r7, #0
	bl FUN_0201FE94
	str r0, [r4]
	mov r1, #0
	bl FUN_020200BC
	ldr r0, [r4]
	mov r1, #0
	bl FUN_020200A0
	add r5, r5, #1
	cmp r5, #0x10
	blt _021DABEC
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD63_021DABCC

	thumb_func_start MOD63_021DAC18
MOD63_021DAC18: ; 0x021DAC18
	ldr r3, _021DAC20 ; =FUN_0201FDEC
	ldr r0, [r0]
	bx r3
	nop
_021DAC20: .word FUN_0201FDEC
	thumb_func_end MOD63_021DAC18

	thumb_func_start MOD63_021DAC24
MOD63_021DAC24: ; 0x021DAC24
	lsl r1, r1, #2
	add r1, r0, r1
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r3, _021DAC34 ; =FUN_020200A0
	add r1, r2, #0
	bx r3
	.align 2, 0
_021DAC34: .word FUN_020200A0
	thumb_func_end MOD63_021DAC24

	thumb_func_start MOD63_021DAC38
MOD63_021DAC38: ; 0x021DAC38
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r2, #0
	mov r2, #0x63
	lsl r2, r2, #2
	add r4, r0, r2
	lsl r5, r1, #2
	ldr r0, [r4, r5]
	add r7, r3, #0
	bl FUN_0202011C
	add r3, r0, #0
	add r2, sp, #0
	ldmia r3!, {r0, r1}
	mov ip, r2
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, ip
	str r0, [r2]
	str r6, [sp]
	str r7, [sp, #4]
	ldr r0, [r4, r5]
	bl FUN_02020044
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD63_021DAC38

	thumb_func_start MOD63_021DAC6C
MOD63_021DAC6C: ; 0x021DAC6C
	push {r3, lr}
	mov r2, #0xb
	mov r3, #7
	mov r1, #1
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	bl MOD63_021DAC38
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD63_021DAC6C

	thumb_func_start MOD63_021DAC80
MOD63_021DAC80: ; 0x021DAC80
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	bl FUN_02020130
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_02020130
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021DAC80

	thumb_func_start MOD63_021DACA0
MOD63_021DACA0: ; 0x021DACA0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	bl FUN_020200BC
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_020200BC
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021DACA0

	thumb_func_start MOD63_021DACC0
MOD63_021DACC0: ; 0x021DACC0
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0202011C
	add r5, r0, #0
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	mov r0, #0xe
	ldr r1, [sp]
	lsl r0, r0, #0xc
	sub r1, r1, r0
	mov r0, #0xb
	lsl r0, r0, #0x10
	str r1, [sp]
	cmp r1, r0
	bgt _021DAD04
	str r0, [sp]
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r2, #0
	bl FUN_02020044
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_021DAD04:
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r2, #0
	bl FUN_02020044
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021DACC0

	thumb_func_start MOD63_021DAD18
MOD63_021DAD18: ; 0x021DAD18
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	lsl r4, r1, #2
	mov r0, #0x63
	add r1, r5, r4
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r6, r2, #0
	bl FUN_02020354
	mov r1, #1
	bl FUN_020B19C4
	add r7, r0, #0
	cmp r6, #0
	bne _021DAD44
	ldr r0, _021DAD64 ; =0x021DBFA0
	add r1, r7, #0
	mov r2, #0x20
	bl GX_LoadOBJPltt
	pop {r3, r4, r5, r6, r7, pc}
_021DAD44:
	ldr r0, _021DAD68 ; =0x021DBF64
	ldr r0, [r0, r4]
	lsl r0, r0, #4
	add r1, r5, r0
	mov r0, #5
	lsl r0, r0, #6
	ldr r0, [r1, r0]
	bl FUN_0200955C
	ldr r0, [r0, #0xc]
	add r1, r7, #0
	mov r2, #0x20
	bl GX_LoadOBJPltt
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DAD64: .word 0x021DBFA0
_021DAD68: .word 0x021DBF64
	thumb_func_end MOD63_021DAD18

	thumb_func_start MOD63_021DAD6C
MOD63_021DAD6C: ; 0x021DAD6C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	ldr r3, _021DAE44 ; =0x021DBE40
	add r2, sp, #0x18
	str r0, [sp]
	str r1, [sp, #4]
	ldmia r3!, {r0, r1}
	str r2, [sp, #8]
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r3, _021DAE48 ; =0x021DBE34
	str r0, [r2]
	ldmia r3!, {r0, r1}
	add r2, sp, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r1, _021DAE4C ; =0x000005C8
	str r0, [r2]
	ldr r0, [sp, #4]
	cmp r0, r1
	blt _021DADE6
	mov r4, #0
_021DAD98:
	ldr r0, [sp, #8]
	lsl r7, r4, #2
	ldr r0, [r0, r7]
	lsl r1, r0, #2
	ldr r0, [sp]
	add r5, r0, r1
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0x24
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	str r0, [r3]
	ldr r0, _021DAE50 ; =0x021DBF4C
	ldr r1, [sp, #0x24]
	ldr r0, [r0, r7]
	sub r0, r1, r0
	str r0, [sp, #0x24]
	mov r0, #1
	ldr r1, [sp, #0x28]
	lsl r0, r0, #0xe
	sub r0, r1, r0
	str r0, [sp, #0x28]
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r2, #0
	bl FUN_02020044
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #3
	blo _021DAD98
_021DADE6:
	ldr r1, _021DAE54 ; =0x000005E6
	ldr r0, [sp, #4]
	cmp r0, r1
	blt _021DAE3E
	mov r5, #0
_021DADF0:
	lsl r7, r5, #2
	add r0, sp, #0xc
	ldr r0, [r0, r7]
	lsl r1, r0, #2
	ldr r0, [sp]
	add r4, r0, r1
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0x24
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	str r0, [r3]
	ldr r0, _021DAE58 ; =0x021DBF58
	ldr r1, [sp, #0x24]
	ldr r0, [r0, r7]
	sub r0, r1, r0
	str r0, [sp, #0x24]
	mov r0, #1
	ldr r1, [sp, #0x28]
	lsl r0, r0, #0xe
	sub r0, r1, r0
	str r0, [sp, #0x28]
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r2, #0
	bl FUN_02020044
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #3
	blo _021DADF0
_021DAE3E:
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DAE44: .word 0x021DBE40
_021DAE48: .word 0x021DBE34
_021DAE4C: .word 0x000005C8
_021DAE50: .word 0x021DBF4C
_021DAE54: .word 0x000005E6
_021DAE58: .word 0x021DBF58
	thumb_func_end MOD63_021DAD6C

	thumb_func_start MOD63_021DAE5C
MOD63_021DAE5C: ; 0x021DAE5C
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _021DAE88 ; =0x021DBEAC
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_0201D040
	mov r0, #1
	mov r1, #0x4c
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021DAE88: .word 0x021DBEAC
	thumb_func_end MOD63_021DAE5C

	thumb_func_start MOD63_021DAE8C
MOD63_021DAE8C: ; 0x021DAE8C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x2c
	add r4, r1, #0
	mov r1, #0
	add r5, r0, #0
	str r1, [sp]
	sub r0, r1, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r6, r2, #0
	str r1, [sp, #0xc]
	mov r2, #0x4b
	str r1, [sp, #0x10]
	lsl r2, r2, #2
	ldr r0, [r5, r2]
	add r3, r1, #0
	str r0, [sp, #0x14]
	add r0, r2, #4
	ldr r0, [r5, r0]
	str r0, [sp, #0x18]
	add r0, r2, #0
	add r0, #8
	ldr r0, [r5, r0]
	add r2, #0xc
	str r0, [sp, #0x1c]
	ldr r0, [r5, r2]
	add r2, r1, #0
	str r0, [sp, #0x20]
	str r1, [sp, #0x24]
	str r1, [sp, #0x28]
	add r0, r6, #0
	bl FUN_02008AA4
	ldr r0, [r5]
	mov r1, #0
	str r0, [r4]
	str r6, [r4, #4]
	str r1, [r4, #8]
	str r1, [r4, #0xc]
	mov r0, #1
	str r1, [r4, #0x10]
	lsl r0, r0, #0xc
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	strh r1, [r4, #0x20]
	mov r0, #1
	str r0, [r4, #0x24]
	str r0, [r4, #0x28]
	mov r0, #0x4c
	str r0, [r4, #0x2c]
	add sp, #0x2c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD63_021DAE8C

	thumb_func_start MOD63_021DAEF8
MOD63_021DAEF8: ; 0x021DAEF8
	push {r4, lr}
	mov r1, #0x7d
	mov r0, #0x4c
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x7d
	add r4, r0, #0
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	add r0, r4, #0
	bl MOD63_021DAFEC
	add r0, r4, #0
	bl MOD63_021DB150
	add r0, r4, #0
	pop {r4, pc}
	thumb_func_end MOD63_021DAEF8

	thumb_func_start MOD63_021DAF20
MOD63_021DAF20: ; 0x021DAF20
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x4c
	mov r1, #8
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0xc
	add r6, r5, #0
	mul r6, r0
	mov r0, #0x4c
	add r1, r6, #0
	bl AllocFromHeap
	mov r1, #0
	add r2, r6, #0
	str r0, [r4, #4]
	bl memset
	str r5, [r4]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD63_021DAF20

	thumb_func_start MOD63_021DAF4C
MOD63_021DAF4C: ; 0x021DAF4C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5]
	mov r6, #0
	cmp r0, #0
	ble _021DAF72
	add r4, r6, #0
_021DAF5A:
	ldr r0, [r5, #4]
	add r0, r0, r4
	ldr r0, [r0, #8]
	cmp r0, #0
	beq _021DAF68
	bl FUN_0200CAB4
_021DAF68:
	ldr r0, [r5]
	add r6, r6, #1
	add r4, #0xc
	cmp r6, r0
	blt _021DAF5A
_021DAF72:
	ldr r0, [r5, #4]
	bl FreeToHeap
	add r0, r5, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
	thumb_func_end MOD63_021DAF4C

	thumb_func_start MOD63_021DAF80
MOD63_021DAF80: ; 0x021DAF80
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	cmp r4, r0
	blt _021DAF90
	bl ErrorHandling
_021DAF90:
	mov r0, #0xc
	ldr r1, [r5, #4]
	mul r0, r4
	add r0, r1, r0
	add r0, r0, #4
	pop {r3, r4, r5, pc}
	thumb_func_end MOD63_021DAF80

	thumb_func_start MOD63_021DAF9C
MOD63_021DAF9C: ; 0x021DAF9C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl MOD63_021DB108
	mov r6, #0x73
	mov r4, #0
	lsl r6, r6, #2
_021DAFAA:
	lsl r0, r4, #4
	add r0, r5, r0
	ldr r0, [r0, r6]
	cmp r0, #0
	beq _021DAFB8
	bl FUN_0200CAB4
_021DAFB8:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #3
	blo _021DAFAA
	mov r6, #0x55
	mov r4, #0
	mov r7, #0xc
	lsl r6, r6, #2
_021DAFCA:
	add r0, r4, #0
	mul r0, r7
	add r0, r5, r0
	ldr r0, [r0, r6]
	cmp r0, #0
	beq _021DAFDA
	bl FUN_0200CAB4
_021DAFDA:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0xa
	blo _021DAFCA
	add r0, r5, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD63_021DAF9C

	thumb_func_start MOD63_021DAFEC
MOD63_021DAFEC: ; 0x021DAFEC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	add r7, r0, #0
	add r3, r1, #0
	ldr r0, _021DB0FC ; =0xFFCFFFEF
	mov r1, #0x10
	and r3, r0
	orr r3, r1
	str r3, [r2]
	ldr r3, _021DB100 ; =0x04001000
	ldr r2, [r3]
	and r0, r2
	orr r0, r1
	str r0, [r3]
	bl MOD63_021DAE5C
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x80
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x4c
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	mov r0, #0xa
	add r1, r7, #4
	mov r2, #0x4c
	bl FUN_02008C9C
	ldr r4, _021DB104 ; =0x021DBEBC
	str r0, [r7]
	mov r6, #0
	add r5, r7, #0
_021DB040:
	ldrb r0, [r4]
	add r1, r6, #0
	mov r2, #0x4c
	bl FUN_02008DEC
	mov r1, #0x4b
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r6, r6, #1
	add r4, r4, #1
	add r5, r5, #4
	cmp r6, #4
	blt _021DB040
	mov r3, #0
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe0
	ldr r0, [r7, r0]
	mov r1, #0x80
	mov r2, #4
	bl FUN_02008F34
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [r7, r1]
	mov r3, #0
	str r3, [sp]
	mov r2, #3
	str r2, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	add r0, #0xe4
	ldr r0, [r7, r0]
	mov r1, #0x80
	bl FUN_02008FEC
	mov r1, #5
	lsl r1, r1, #6
	str r0, [r7, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe8
	ldr r0, [r7, r0]
	mov r1, #0x80
	mov r2, #5
	bl FUN_020090AC
	mov r1, #0x51
	lsl r1, r1, #2
	str r0, [r7, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xec
	ldr r0, [r7, r0]
	mov r1, #0x80
	mov r2, #6
	bl FUN_020090AC
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r7, r1]
	sub r1, #0xc
	ldr r0, [r7, r1]
	bl FUN_02009A50
	mov r0, #5
	lsl r0, r0, #6
	ldr r0, [r7, r0]
	bl FUN_02009CF0
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021DB0FC: .word 0xFFCFFFEF
_021DB100: .word 0x04001000
_021DB104: .word 0x021DBEBC
	thumb_func_end MOD63_021DAFEC

	thumb_func_start MOD63_021DB108
MOD63_021DB108: ; 0x021DB108
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x4f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009C0C
	mov r0, #5
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	bl FUN_02009E04
	mov r6, #0x4b
	mov r4, #0
	lsl r6, r6, #2
_021DB126:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, r6]
	bl FUN_02008E2C
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021DB126
	ldr r0, [r5]
	bl FUN_0201FD58
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD63_021DB108

	thumb_func_start MOD63_021DB150
MOD63_021DB150: ; 0x021DB150
	push {r4, r5, r6, r7, lr}
	sub sp, #0x54
	add r7, r0, #0
	mov r6, #0
	add r4, r6, #0
	add r5, r7, #0
_021DB15C:
	add r0, r7, #0
	add r1, sp, #0
	add r2, sp, #0x30
	bl MOD63_021DAE8C
	add r0, sp, #0
	str r4, [sp, #8]
	str r4, [sp, #0xc]
	bl FUN_0201FE94
	mov r1, #0x15
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200BC
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #2
	lsl r0, r0, #0xc
	add r6, r6, #1
	add r4, r4, r0
	add r5, #0xc
	cmp r6, #0xa
	blt _021DB15C
	add sp, #0x54
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD63_021DB150

	thumb_func_start MOD63_021DB1A0
MOD63_021DB1A0: ; 0x021DB1A0
	ldr r3, _021DB1A8 ; =FUN_0201FDEC
	ldr r0, [r0]
	bx r3
	nop
_021DB1A8: .word FUN_0201FDEC
	thumb_func_end MOD63_021DB1A0

	thumb_func_start MOD63_021DB1AC
MOD63_021DB1AC: ; 0x021DB1AC
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	cmp r1, #0xb4
	bne _021DB1CE
	mov r2, #3
	str r2, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #0x71
	lsl r0, r0, #2
	add r0, r4, r0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD63_021DB1F8
	b _021DB1E8
_021DB1CE:
	ldr r0, _021DB1F4 ; =0x0000011D
	cmp r1, r0
	bne _021DB1E8
	mov r2, #3
	add r0, #0xb7
	str r2, [sp]
	mov r1, #1
	str r1, [sp, #4]
	add r0, r4, r0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD63_021DB1F8
_021DB1E8:
	add r0, r4, #0
	bl MOD63_021DB1A0
	add sp, #8
	pop {r4, pc}
	nop
_021DB1F4: .word 0x0000011D
	thumb_func_end MOD63_021DB1AC

	thumb_func_start MOD63_021DB1F8
MOD63_021DB1F8: ; 0x021DB1F8
	push {r4, lr}
	add r4, r0, #0
	strb r2, [r4]
	ldr r2, _021DB228 ; =0xFFFFFFF8
	strb r3, [r4, #1]
	add r2, sp
	ldrb r0, [r2, #0x10]
	strb r0, [r4, #2]
	mov r0, #0
	strb r0, [r4, #4]
	strb r0, [r4, #3]
	mov r0, #0x53
	lsl r0, r0, #2
	add r0, r1, r0
	str r0, [r4, #0xc]
	ldrb r0, [r2, #0x14]
	add r1, r4, #0
	mov r2, #0xa
	strb r0, [r4, #5]
	ldr r0, _021DB22C ; =MOD63_021DB2F8
	bl FUN_0200CA44
	str r0, [r4, #8]
	pop {r4, pc}
	.align 2, 0
_021DB228: .word 0xFFFFFFF8
_021DB22C: .word MOD63_021DB2F8
	thumb_func_end MOD63_021DB1F8

	thumb_func_start MOD63_021DB230
MOD63_021DB230: ; 0x021DB230
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r1, #0
	str r0, [sp]
	cmp r2, #0
	bne _021DB240
	mov r7, #0x40
	b _021DB242
_021DB240:
	mov r7, #0x20
_021DB242:
	mov r5, #0
	cmp r6, #0
	bls _021DB2BE
_021DB248:
	ldr r0, [sp]
	mov r1, #0xa
	bl MOD63_021DB2C8
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FUN_0202011C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #4
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r2, r0, #0x19
	sub r2, r2, r1
	mov r0, #0x19
	ror r2, r0
	add r0, r1, r2
	add r0, #0x40
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r2, r0, #0x1a
	sub r2, r2, r1
	mov r0, #0x1a
	ror r2, r0
	add r0, r1, r2
	add r0, r7, r0
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	add r1, sp, #4
	bl FUN_02020044
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, _021DB2C4 ; =MOD63_021DB334
	add r1, r4, #0
	mov r2, #0x14
	bl FUN_0200CA44
	str r0, [r4, #8]
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, r6
	blo _021DB248
_021DB2BE:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DB2C4: .word MOD63_021DB334
	thumb_func_end MOD63_021DB230

	thumb_func_start MOD63_021DB2C8
MOD63_021DB2C8: ; 0x021DB2C8
	push {r4, lr}
	mov r4, #0
	mov r2, #0xc
_021DB2CE:
	add r1, r4, #0
	mul r1, r2
	add r3, r0, r1
	ldrb r1, [r0, r1]
	cmp r1, #0
	bne _021DB2E6
	mov r0, #1
	strb r0, [r3]
	mov r0, #0
	strb r0, [r3, #1]
	add r0, r3, #0
	pop {r4, pc}
_021DB2E6:
	add r1, r4, #1
	lsl r1, r1, #0x18
	lsr r4, r1, #0x18
	cmp r4, #0xa
	blo _021DB2CE
	bl ErrorHandling
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD63_021DB2C8

	thumb_func_start MOD63_021DB2F8
MOD63_021DB2F8: ; 0x021DB2F8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4, #4]
	add r5, r0, #0
	add r0, r1, #1
	strb r0, [r4, #4]
	ldrb r0, [r4, #1]
	cmp r1, r0
	blo _021DB330
	ldrb r1, [r4]
	ldrb r2, [r4, #5]
	ldr r0, [r4, #0xc]
	bl MOD63_021DB230
	mov r0, #0
	strb r0, [r4, #4]
	ldrb r0, [r4, #3]
	add r0, r0, #1
	strb r0, [r4, #3]
	ldrb r1, [r4, #3]
	ldrb r0, [r4, #2]
	cmp r1, r0
	blo _021DB330
	add r0, r5, #0
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #8]
_021DB330:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021DB2F8

	thumb_func_start MOD63_021DB334
MOD63_021DB334: ; 0x021DB334
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	str r0, [r3]
	mov r0, #3
	ldr r1, [sp, #4]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #4]
	ldr r0, [r4, #4]
	add r1, r2, #0
	bl FUN_02020044
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	ldrb r0, [r4, #1]
	cmp r0, #0x50
	blo _021DB388
	add r0, r5, #0
	bl FUN_0200CAB4
	mov r1, #0
	str r1, [r4, #8]
	strb r1, [r4]
	ldr r0, [r4, #4]
	bl FUN_020200BC
	ldr r0, [r4, #4]
	mov r1, #0
	bl FUN_020200A0
_021DB388:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD63_021DB334

	thumb_func_start MOD63_021DB38C
MOD63_021DB38C: ; 0x021DB38C
	ldr r3, _021DB394 ; =MOD63_021DB398
	mov r1, #2
	bx r3
	nop
_021DB394: .word MOD63_021DB398
	thumb_func_end MOD63_021DB38C

	thumb_func_start MOD63_021DB398
MOD63_021DB398: ; 0x021DB398
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r0, #0
	ldr r0, [r6, #4]
	add r7, r1, #0
	str r0, [sp]
	ldr r5, _021DB418 ; =0x00000000
	beq _021DB414
_021DB3A8:
	ldr r0, [sp]
	ldr r1, [r6]
	bl MOD63_021DB2C8
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FUN_0202011C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #4
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	bl LCRandom
	mov r1, #0xe0
	bl _s32_div_f
	add r1, #0xa
	lsl r0, r1, #0xc
	str r0, [sp, #4]
	bl LCRandom
	mov r1, #0x38
	bl _s32_div_f
	ldr r0, _021DB41C ; =0x0000013A
	add r0, r1, r0
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	add r1, sp, #4
	bl FUN_02020044
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, _021DB420 ; =MOD63_021DB424
	add r1, r4, #0
	mov r2, #0x14
	bl FUN_0200CA44
	str r0, [r4, #8]
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, r7
	blo _021DB3A8
_021DB414:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DB418: .word 0x00000000
_021DB41C: .word 0x0000013A
_021DB420: .word MOD63_021DB424
	thumb_func_end MOD63_021DB398

	thumb_func_start MOD63_021DB424
MOD63_021DB424: ; 0x021DB424
	push {r4, lr}
	add r4, r1, #0
	ldrb r1, [r4, #1]
	add r1, r1, #1
	strb r1, [r4, #1]
	ldrb r1, [r4, #1]
	cmp r1, #8
	blo _021DB44C
	bl FUN_0200CAB4
	mov r1, #0
	str r1, [r4, #8]
	strb r1, [r4]
	ldr r0, [r4, #4]
	bl FUN_020200BC
	ldr r0, [r4, #4]
	mov r1, #0
	bl FUN_020200A0
_021DB44C:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD63_021DB424

	thumb_func_start MOD63_021DB450
MOD63_021DB450: ; 0x021DB450
	push {r4, lr}
	ldr r3, _021DB470 ; =0x021064B8
	mov r2, #0
	ldr r3, [r3]
	blx r3
	add r4, r0, #0
	bl FUN_0201327C
	cmp r4, #0
	bne _021DB468
	bl ErrorHandling
_021DB468:
	lsl r0, r4, #0x10
	lsr r0, r0, #0xd
	pop {r4, pc}
	nop
_021DB470: .word 0x021064B8
	thumb_func_end MOD63_021DB450

	thumb_func_start MOD63_021DB474
MOD63_021DB474: ; 0x021DB474
	push {r4, lr}
	ldr r3, _021DB494 ; =UNK_021064C0
	mov r2, #1
	ldr r3, [r3]
	blx r3
	add r4, r0, #0
	bne _021DB486
	bl ErrorHandling
_021DB486:
	add r0, r4, #0
	bl FUN_020132BC
	lsl r0, r4, #0x10
	lsr r0, r0, #0xd
	pop {r4, pc}
	nop
_021DB494: .word UNK_021064C0
	thumb_func_end MOD63_021DB474

	thumb_func_start MOD63_021DB498
MOD63_021DB498: ; 0x021DB498
	mov r0, #0x20
	bx lr
	thumb_func_end MOD63_021DB498

	thumb_func_start MOD63_021DB49C
MOD63_021DB49C: ; 0x021DB49C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	ldr r3, _021DB56C ; =0x021DBECC
	add r5, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0x10
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	mov r0, #0x4c
	bl FUN_02006D98
	ldr r7, _021DB570 ; =0x021DBEF0
	str r0, [r5]
	mov r4, #0
_021DB4BA:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	lsl r6, r4, #2
	add r1, sp, #0x10
	ldr r1, [r1, r6]
	add r0, sp, #0x1c
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	mov r2, #0
	mov r3, #2
	bl FUN_02068C00
	ldr r0, _021DB574 ; =0x000003FF
	lsl r2, r4, #3
	str r0, [sp]
	str r4, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	add r3, r7, r2
	ldr r0, [r5]
	ldr r2, [r7, r2]
	ldr r3, [r3, #4]
	add r1, sp, #0x1c
	add r6, r5, r6
	bl FUN_020073A0
	mov r1, #6
	mov r2, #1
	str r0, [r6, #4]
	bl FUN_02007558
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #3
	blo _021DB4BA
	ldr r0, [r5, #8]
	mov r1, #0x23
	mov r2, #1
	bl FUN_02007558
	mov r0, #1
	str r0, [r5, #0x10]
	bl FUN_02012CC8
	mov r1, #0x12
	mov r0, #0x4c
	lsl r1, r1, #0xa
	bl AllocFromHeap
	str r0, [r5, #0x14]
	mov r0, #1
	str r0, [sp]
	mov r0, #0x4c
	str r0, [sp, #4]
	mov r3, #0x12
	ldr r0, _021DB578 ; =MOD63_021DB450
	ldr r1, _021DB57C ; =MOD63_021DB474
	ldr r2, [r5, #0x14]
	lsl r3, r3, #0xa
	bl FUN_02012CDC
	str r0, [r5, #0x18]
	bl FUN_0201343C
	add r2, r0, #0
	mov r0, #1
	mov r1, #0xe1
	lsl r0, r0, #0xc
	lsl r1, r1, #0xe
	bl FUN_0201EC94
	mov r0, #0x3d
	mov r1, #4
	mov r2, #0x4c
	bl FUN_0201318C
	add r1, r0, #0
	ldr r0, [r5, #0x18]
	mov r2, #0xa
	mov r3, #1
	bl FUN_02013194
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_021DB56C: .word 0x021DBECC
_021DB570: .word 0x021DBEF0
_021DB574: .word 0x000003FF
_021DB578: .word MOD63_021DB450
_021DB57C: .word MOD63_021DB474
	thumb_func_end MOD63_021DB49C

	thumb_func_start MOD63_021DB580
MOD63_021DB580: ; 0x021DB580
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	bl FUN_02012DE4
	ldr r0, [r4, #0x14]
	bl FreeToHeap
	ldr r0, [r4]
	bl FUN_020072E8
	pop {r4, pc}
	thumb_func_end MOD63_021DB580

	thumb_func_start MOD63_021DB598
MOD63_021DB598: ; 0x021DB598
	push {r3, lr}
	cmp r0, #0
	beq _021DB5A4
	ldr r0, [r0]
	bl FUN_020081C4
_021DB5A4:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD63_021DB598

	thumb_func_start MOD63_021DB5A8
MOD63_021DB5A8: ; 0x021DB5A8
	push {r4, lr}
	add r4, r0, #0
	beq _021DB5C8
	bl FUN_020222AC
	bl FUN_020B02C8
	ldr r0, [r4]
	bl FUN_02006ED4
	bl MOD63_021DB934
	mov r0, #1
	mov r1, #0
	bl FUN_020222B4
_021DB5C8:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD63_021DB5A8

	thumb_func_start MOD63_021DB5CC
MOD63_021DB5CC: ; 0x021DB5CC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r0, #0
	add r7, r2, #0
	ldrb r2, [r4, #0x1c]
	add r5, r4, #0
	add r6, r1, #0
	add r5, #0x1c
	cmp r2, #5
	bls _021DB5E2
	b _021DB6FC
_021DB5E2:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021DB5EE: ; jump table
	.short _021DB5FA - _021DB5EE - 2 ; case 0
	.short _021DB63C - _021DB5EE - 2 ; case 1
	.short _021DB658 - _021DB5EE - 2 ; case 2
	.short _021DB690 - _021DB5EE - 2 ; case 3
	.short _021DB6BE - _021DB5EE - 2 ; case 4
	.short _021DB6E4 - _021DB5EE - 2 ; case 5
_021DB5FA:
	ldr r0, _021DB704 ; =0x0400004A
	mov r1, #0x3f
	ldrh r2, [r0]
	add r7, r4, #4
	bic r2, r1
	mov r1, #0x11
	orr r1, r2
	mov r2, #0x20
	orr r1, r2
	strh r1, [r0]
	lsl r0, r6, #2
	str r0, [sp]
	ldr r0, [r7, r0]
	mov r1, #0xc
	lsl r2, r2, #5
	bl FUN_02007558
	ldr r0, [sp]
	mov r2, #1
	ldr r0, [r7, r0]
	mov r1, #0xd
	lsl r2, r2, #0xa
	bl FUN_02007558
	ldr r0, [sp]
	mov r1, #6
	ldr r0, [r7, r0]
	mov r2, #0
	bl FUN_02007558
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
_021DB63C:
	ldr r2, _021DB708 ; =0x021DBED8
	lsl r3, r6, #3
	ldr r2, [r2, r3]
	add r0, r4, #0
	add r1, r6, #0
	blx r2
	cmp r0, #0
	beq _021DB6FC
	mov r0, #0
	strb r0, [r4, #0x1d]
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
	b _021DB6FC
_021DB658:
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_02013440
	lsl r0, r6, #2
	str r0, [sp, #4]
	ldr r1, _021DB70C ; =0x021DBF08
	lsl r6, r6, #3
	ldr r3, [sp, #4]
	add r7, r4, #4
	ldr r0, [r4, #0x18]
	ldr r1, [r1, r6]
	ldr r2, _021DB710 ; =MOD63_021DB940
	ldr r3, [r7, r3]
	bl FUN_020133AC
	ldr r1, _021DB714 ; =0x021DBF0C
	ldr r3, [sp, #4]
	ldr r0, [r4, #0x18]
	ldr r1, [r1, r6]
	ldr r2, _021DB710 ; =MOD63_021DB940
	ldr r3, [r7, r3]
	bl FUN_020133AC
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
	b _021DB6FC
_021DB690:
	ldr r0, [r4, #0x18]
	bl FUN_020133C8
	cmp r0, #0
	bne _021DB6FC
	ldr r0, _021DB718 ; =0x021DBEC0
	lsl r1, r6, #2
	ldr r0, [r0, r1]
	cmp r7, r0
	blt _021DB6FC
	ldr r1, _021DB704 ; =0x0400004A
	mov r0, #0x3f
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #0x10
	orr r2, r0
	mov r0, #0x20
	orr r0, r2
	strh r0, [r1]
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
	b _021DB6FC
_021DB6BE:
	ldr r2, _021DB71C ; =0x021DBEDC
	lsl r3, r6, #3
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #0
	beq _021DB6FC
	lsl r0, r6, #2
	add r0, r4, r0
	ldr r0, [r0, #4]
	mov r1, #6
	mov r2, #1
	bl FUN_02007558
	mov r0, #0
	strb r0, [r4, #0x1d]
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
	b _021DB6FC
_021DB6E4:
	ldrb r0, [r4, #0x1d]
	add r0, r0, #1
	strb r0, [r4, #0x1d]
	ldrb r0, [r4, #0x1d]
	cmp r0, #0x14
	blo _021DB6FC
	mov r0, #0
	strb r0, [r4, #0x1d]
	strb r0, [r5]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DB6FC:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DB704: .word 0x0400004A
_021DB708: .word 0x021DBED8
_021DB70C: .word 0x021DBF08
_021DB710: .word MOD63_021DB940
_021DB714: .word 0x021DBF0C
_021DB718: .word 0x021DBEC0
_021DB71C: .word 0x021DBEDC
	thumb_func_end MOD63_021DB5CC

	thumb_func_start MOD63_021DB720
MOD63_021DB720: ; 0x021DB720
	push {r3, r4, r5, lr}
	add r5, r0, #0
	lsl r0, r1, #2
	add r0, r5, r0
	ldr r4, [r0, #4]
	mov r1, #0
	add r0, r4, #0
	mov r2, #6
	bl FUN_020079E0
	mov r1, #1
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x11
	bl FUN_020079E0
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x8c
	bl FUN_020079E0
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x8d
	bl FUN_020079E0
	ldrb r0, [r5, #0x1d]
	add r0, r0, #1
	strb r0, [r5, #0x1d]
	ldrb r0, [r5, #0x1d]
	cmp r0, #6
	blo _021DB780
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf3
	bl FUN_02007558
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DB780:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD63_021DB720

	thumb_func_start MOD63_021DB784
MOD63_021DB784: ; 0x021DB784
	push {r3, r4, r5, lr}
	add r5, r0, #0
	lsl r0, r1, #2
	add r0, r5, r0
	ldr r4, [r0, #4]
	mov r1, #0
	add r0, r4, #0
	sub r2, r1, #3
	bl FUN_020079E0
	mov r1, #1
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x13
	bl FUN_020079E0
	ldrb r0, [r5, #0x1d]
	add r0, r0, #1
	strb r0, [r5, #0x1d]
	ldrb r0, [r5, #0x1d]
	cmp r0, #6
	blo _021DB7CC
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf3
	bl FUN_02007558
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DB7CC:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD63_021DB784

	thumb_func_start MOD63_021DB7D0
MOD63_021DB7D0: ; 0x021DB7D0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	lsl r0, r1, #2
	add r0, r5, r0
	ldr r4, [r0, #4]
	mov r1, #0
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x10
	bl FUN_020079E0
	mov r1, #1
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x11
	bl FUN_020079E0
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x8c
	bl FUN_020079E0
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x8d
	bl FUN_020079E0
	ldrb r0, [r5, #0x1d]
	add r0, r0, #1
	strb r0, [r5, #0x1d]
	ldrb r0, [r5, #0x1d]
	cmp r0, #6
	blo _021DB832
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf3
	bl FUN_02007558
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DB832:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021DB7D0

	thumb_func_start MOD63_021DB838
MOD63_021DB838: ; 0x021DB838
	push {r3, r4, r5, lr}
	add r5, r0, #0
	lsl r0, r1, #2
	add r0, r5, r0
	ldr r4, [r0, #4]
	mov r1, #0
	add r0, r4, #0
	sub r2, r1, #6
	bl FUN_020079E0
	mov r1, #1
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x11
	bl FUN_020079E0
	ldrb r0, [r5, #0x1d]
	add r0, r0, #1
	strb r0, [r5, #0x1d]
	ldrb r0, [r5, #0x1d]
	cmp r0, #6
	blo _021DB880
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf3
	bl FUN_02007558
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DB880:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD63_021DB838

	thumb_func_start MOD63_021DB884
MOD63_021DB884: ; 0x021DB884
	push {r3, r4, r5, lr}
	add r5, r0, #0
	lsl r0, r1, #2
	add r0, r5, r0
	ldr r4, [r0, #4]
	mov r1, #0
	add r0, r4, #0
	mov r2, #8
	bl FUN_020079E0
	mov r1, #1
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x11
	bl FUN_020079E0
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x8c
	bl FUN_020079E0
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x8d
	bl FUN_020079E0
	ldrb r0, [r5, #0x1d]
	add r0, r0, #1
	strb r0, [r5, #0x1d]
	ldrb r0, [r5, #0x1d]
	cmp r0, #6
	blo _021DB8E4
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf3
	bl FUN_02007558
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DB8E4:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD63_021DB884

	thumb_func_start MOD63_021DB8E8
MOD63_021DB8E8: ; 0x021DB8E8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	lsl r0, r1, #2
	add r0, r5, r0
	ldr r4, [r0, #4]
	mov r1, #0
	add r0, r4, #0
	mov r2, #6
	bl FUN_020079E0
	mov r1, #1
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x15
	bl FUN_020079E0
	ldrb r0, [r5, #0x1d]
	add r0, r0, #1
	strb r0, [r5, #0x1d]
	ldrb r0, [r5, #0x1d]
	cmp r0, #6
	blo _021DB930
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf3
	bl FUN_02007558
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DB930:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD63_021DB8E8

	thumb_func_start MOD63_021DB934
MOD63_021DB934: ; 0x021DB934
	push {r3, lr}
	bl FUN_02013364
	bl FUN_02013388
	pop {r3, pc}
	thumb_func_end MOD63_021DB934

	thumb_func_start MOD63_021DB940
MOD63_021DB940: ; 0x021DB940
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	bl FUN_0201341C
	add r2, sp, #0
	mov r1, #0
	str r1, [r2]
	str r1, [r2, #4]
	add r4, r0, #0
	str r1, [r2, #8]
	bl FUN_0200782C
	sub r0, #0x80
	mov r1, #0xac
	mul r1, r0
	str r1, [sp]
	add r0, r4, #0
	mov r1, #1
	bl FUN_0200782C
	sub r0, #0x60
	mov r1, #0xac
	mul r1, r0
	str r1, [sp, #4]
	mov r0, #0x40
	str r0, [sp, #8]
	ldr r0, [r5, #0x20]
	ldr r1, [sp]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	add r0, r1, r0
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r1, r0
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #8]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	add r0, r1, r0
	str r0, [r5, #0x30]
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021DB940

	.section .rodata

	.global MOD63_021DB9A0
MOD63_021DB9A0: ; 0x021DB9A0
	.byte 0x04, 0x02, 0x13, 0x1C, 0x02, 0x02, 0x01, 0x00

	.global MOD63_021DB9A8
MOD63_021DB9A8: ; 0x021DB9A8
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global MOD63_021DB9B4
MOD63_021DB9B4: ; 0x021DB9B4
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00

	.global MOD63_021DB9C4
MOD63_021DB9C4: ; 0x021DB9C4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DB9E0
MOD63_021DB9E0: ; 0x021DB9E0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x05, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DB9FC
MOD63_021DB9FC: ; 0x021DB9FC
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00
	.byte 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DB9A18
MOD63_021DBA18: ; 0x021DBA18
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x03, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBA34
MOD63_021DBA34: ; 0x021DBA34
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBA50
MOD63_021DBA50: ; 0x021DBA50
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x07, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBA6C
MOD63_021DBA6C: ; 0x021DBA6C
	.byte 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global MOD63_021DBA90
MOD63_021DBA90: ; 0x021DBA90
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00

	.global UNK63_021DBAB8
UNK63_021DBAB8: ; 0x021DBAB8
	.word MOD63_021D74E0, MOD63_021D759C, MOD63_021D77B4, 0xFFFFFFFF

	; 0x021DBAC8
	.byte 0x00, 0x00, 0x80, 0xF6, 0x00, 0x00, 0x00, 0x00
	.byte 0x18, 0x4B, 0x00, 0x00, 0x42, 0x30, 0xFF, 0x7F, 0x00, 0x00, 0xF8, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0xE4, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00
	.byte 0x1E, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00

	.global MOD63_021DBB3C
MOD63_021DBB3C: ; 0x021DBB3C
	.byte 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD63_021DBB4C
MOD63_021DBB4C: ; 0x021DBB4C
	.byte 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x10
	.byte 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x01, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC1, 0xAE, 0x29, 0x00
	.byte 0x02, 0xD6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x05, 0x00, 0x00, 0x00, 0x00
	.byte 0x40, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00
	.byte 0x44, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x17, 0x03, 0x00, 0x02, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBBC4
MOD63_021DBBC4: ; 0x021DBBC4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBBFC
MOD63_021DBBFC: ; 0x021DBBFC
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBC18
MOD63_021DBC18: ; 0x021DBC18
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBC34
MOD63_021DBC34: ; 0x021DBC34
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBC50
MOD63_021DBC50: ; 0x021DBC50
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBC6C
MOD63_021DBC6C: ; 0x021DBC6C
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x02
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBC88
MOD63_021DBC88: ; 0x021DBC88
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBCA4
MOD63_021DBCA4: ; 0x021DBCA4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBCC0
MOD63_021DBCC0: ; 0x021DBCC0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x03, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBCDC
MOD63_021DBCDC: ; 0x021DBCDC
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x03, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x19, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x01, 0x1B, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global MOD63_021DBD70
MOD63_021DBD70: ; 0x021DBD70
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00

	.global MOD63_021DBD98
MOD63_021DBD98: ; 0x021DBD98
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD63_021DBDC0
MOD63_021DBDC0: ; 0x021DBDC0
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xF8, 0xFF, 0xFF, 0x24, 0xF2, 0xFF, 0xFF
	.byte 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global MOD63_UNK_021DBE18
MOD63_UNK_021DBE18: ; 0x021DBE18
	.word MOD63_021D8D10, MOD63_021D8D98, MOD63_021D8E68, 0xFFFFFFFF
	.byte 0x05, 0x05, 0x05, 0x05, 0x4C, 0x00, 0x00, 0x00, 0x4C, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x4C, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00
	.byte 0x20, 0x01, 0x00, 0x00, 0x20, 0x01, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00
	.byte 0xE0, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00
	.byte 0xE0, 0x00, 0x00, 0x00, 0xD0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x4C, 0x00, 0x00, 0x00
	.byte 0x4C, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x4C, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x03, 0x07, 0x00, 0x00, 0xCE, 0x07, 0x00, 0x00
	.byte 0xA8, 0x08, 0x00, 0x00, 0x83, 0x01, 0x00, 0x00, 0x86, 0x01, 0x00, 0x00, 0x89, 0x01, 0x00, 0x00
	.byte 0x21, 0xB7, 0x1D, 0x02, 0x85, 0xB7, 0x1D, 0x02, 0xD1, 0xB7, 0x1D, 0x02, 0x39, 0xB8, 0x1D, 0x02
	.byte 0x85, 0xB8, 0x1D, 0x02, 0xE9, 0xB8, 0x1D, 0x02, 0x80, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.section .data
	; 0x021DBF40
	.byte 0x08, 0x06, 0x06, 0x04, 0x05, 0x04, 0x03, 0x01, 0x08, 0x07, 0x06, 0x00, 0x00, 0x60, 0x00, 0x00
	.byte 0x00, 0x58, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00
	.byte 0x00, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.section .bss
	; 0x021DBFA0
	.space 0x20

