	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD54_021D74E0
MOD54_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r1, [r5]
	add r6, r0, #0
	cmp r1, #0
	beq _021D74F6
	cmp r1, #1
	bne _021D74F4
	b _021D761A
_021D74F4:
	b _021D7628
_021D74F6:
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	bl FUN_02015F1C
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D7630 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D7634 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r2, #0x41
	mov r0, #3
	mov r1, #0x33
	lsl r2, r2, #0xc
	bl FUN_0201681C
	ldr r1, _021D7638 ; =0x00004A60
	add r0, r6, #0
	mov r2, #0x33
	bl OverlayManager_CreateAndGetData
	ldr r2, _021D7638 ; =0x00004A60
	mov r1, #0
	add r4, r0, #0
	bl memset
	mov r0, #0x33
	bl FUN_02016B94
	str r0, [r4]
	add r0, r6, #0
	bl OverlayManager_GetField18
	str r0, [r4, #8]
	ldr r1, [r0]
	ldr r0, _021D763C ; =0x00004A38
	str r1, [r4, r0]
	mov r0, #0x33
	bl FUN_0200AA80
	str r0, [r4, #0x24]
	ldr r2, _021D7640 ; =0x000001E2
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x33
	bl NewMsgDataFromNarc
	str r0, [r4, #0x28]
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	bl MOD54_021D7874
	ldr r0, [r4]
	bl MOD54_021D7894
	mov r0, #0
	bl FUN_0200E394
	mov r0, #1
	bl FUN_0200E394
	mov r0, #0x10
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x33
	str r0, [sp, #8]
	mov r0, #0
	mov r1, #0x11
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	add r0, r4, #0
	bl MOD54_021D7AA0
	ldr r0, _021D7644 ; =MOD54_021D784C
	add r1, r4, #0
	bl FUN_02015F10
	add r0, r4, #0
	bl MOD54_021D799C
	bl MOD54_021D7B8C
	add r0, r4, #0
	bl MOD54_021D7BBC
	add r0, r4, #0
	bl MOD54_021D7CAC
	add r0, r4, #0
	add r1, r6, #0
	bl MOD54_021D7DB4
	mov r1, #0
	mov r0, #0x34
	add r2, r1, #0
	bl FUN_0200433C
	add r0, r4, #0
	bl FUN_02084098
	bl FUN_020328E4
	mov r0, #3
	bl FUN_02032B6C
	bl FUN_02031190
	cmp r0, #0
	bne _021D75F4
	mov r0, #2
	bl FUN_02052B74
_021D75F4:
	bl FUN_02033E74
	ldr r0, _021D763C ; =0x00004A38
	mov r1, #0xed
	lsl r1, r1, #2
	ldr r0, [r4, r0]
	add r1, r4, r1
	bl MOD54_021D9570
	ldr r0, _021D7648 ; =MOD54_021D77E8
	add r1, r4, #0
	mov r2, #5
	bl FUN_0200CA60
	str r0, [r4, #0x20]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D7628
_021D761A:
	bl OverlayManager_GetData
	mov r0, #0
	str r0, [r5]
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D7628:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021D7630: .word 0xFFFFE0FF
_021D7634: .word 0x04001000
_021D7638: .word 0x00004A60
_021D763C: .word 0x00004A38
_021D7640: .word 0x000001E2
_021D7644: .word MOD54_021D784C
_021D7648: .word MOD54_021D77E8
	thumb_func_end MOD54_021D74E0

	thumb_func_start MOD54_021D764C
MOD54_021D764C: ; 0x021D764C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	bl FUN_02031190
	cmp r0, #0
	bne _021D7672
	ldr r0, _021D7730 ; =0x00004A50
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D7672
	bl FUN_0202CB8C
	ldr r1, _021D7730 ; =0x00004A50
	ldr r2, [r4, r1]
	and r0, r2
	str r0, [r4, r1]
_021D7672:
	ldr r1, [r5]
	cmp r1, #3
	bhi _021D7726
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D7684: ; jump table
	.short _021D768C - _021D7684 - 2 ; case 0
	.short _021D76B4 - _021D7684 - 2 ; case 1
	.short _021D7702 - _021D7684 - 2 ; case 2
	.short _021D771A - _021D7684 - 2 ; case 3
_021D768C:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D7726
	mov r0, #1
	str r0, [r5]
	bl FUN_02031190
	cmp r0, #0
	beq _021D7726
	bl MOD54_021D8C08
	cmp r0, #2
	ble _021D7726
	mov r1, #0
	mov r0, #0x72
	add r2, r1, #0
	bl FUN_02030ADC
	b _021D7726
_021D76B4:
	mov r0, #0xd1
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	lsl r2, r0, #2
	ldr r0, _021D7734 ; =0x021D97E0
	ldr r2, [r0, r2]
	cmp r2, #0
	beq _021D76CA
	add r0, r4, #0
	blx r2
	str r0, [r5]
_021D76CA:
	ldr r0, _021D7738 ; =0x00004A40
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _021D76E2
	mov r0, #0xa6
	lsl r0, r0, #2
	ldr r2, _021D773C ; =0x00010300
	add r0, r4, r0
	mov r1, #0
	add r3, r4, #0
	bl MOD54_021D8AF8
_021D76E2:
	add r0, r4, #0
	bl MOD54_021D8D50
	bl FUN_02031190
	cmp r0, #0
	bne _021D7726
	add r0, r4, #0
	mov r1, #1
	bl MOD54_021D8F94
	ldr r1, [r5]
	cmp r1, #1
	bne _021D7726
	str r0, [r5]
	b _021D7726
_021D7702:
	mov r0, #0xd1
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	lsl r2, r0, #2
	ldr r0, _021D7734 ; =0x021D97E0
	ldr r2, [r0, r2]
	cmp r2, #0
	beq _021D7726
	add r0, r4, #0
	blx r2
	str r0, [r5]
	b _021D7726
_021D771A:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D7726
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D7726:
	ldr r0, [r4, #0x50]
	bl FUN_0201FDEC
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7730: .word 0x00004A50
_021D7734: .word MOD54_021D97E0
_021D7738: .word 0x00004A40
_021D773C: .word 0x00010300
	thumb_func_end MOD54_021D764C

	thumb_func_start MOD54_021D7740
MOD54_021D7740: ; 0x021D7740
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	bl OverlayManager_GetData
	add r6, r0, #0
	ldr r0, [r6, #0x20]
	bl FUN_0200CAB4
	mov r0, #0x6b
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	mov r0, #0x1b
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	bl FUN_02009E04
	mov r7, #0x5f
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_021D776C:
	ldr r0, [r5, r7]
	bl FUN_02008E2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021D776C
	ldr r0, [r6, #0x50]
	bl FUN_0201FD58
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	add r0, r6, #0
	bl MOD54_021D7EDC
	ldr r0, [r6]
	bl MOD54_021D7A6C
	mov r0, #2
	bl FUN_02032B6C
	bl FUN_02031B50
	ldr r0, [r6, #8]
	ldr r0, [r0, #4]
	bl FUN_02052F8C
	ldr r0, [r6, #0x28]
	bl DestroyMsgData
	ldr r0, [r6, #0x24]
	bl FUN_0200AB18
	add r0, r6, #0
	bl MOD54_021D7A34
	ldr r0, [sp]
	bl OverlayManager_FreeData
	ldr r2, _021D77E4 ; =0x04000304
	ldrh r1, [r2]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2]
	mov r0, #0
	bl FUN_02052B74
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	mov r0, #0x33
	bl FUN_020168D0
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D77E4: .word 0x04000304
	thumb_func_end MOD54_021D7740

	thumb_func_start MOD54_021D77E8
MOD54_021D77E8: ; 0x021D77E8
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0xc]
	add r1, #0xc
	cmp r0, #0
	beq _021D7842
	ldr r0, [r1, #4]
	ldr r3, [r1, #8]
	lsl r2, r0, #1
	ldr r0, _021D7844 ; =0x021D968A
	ldrb r0, [r0, r2]
	cmp r3, r0
	ble _021D7832
	mov r0, #0
	str r0, [r1, #8]
	ldr r2, [r1, #4]
	add r2, r2, #1
	str r2, [r1, #4]
	lsl r3, r2, #1
	ldr r2, _021D7848 ; =0x021D968B
	ldrb r2, [r2, r3]
	cmp r2, #0xff
	bne _021D7818
	str r0, [r1, #4]
_021D7818:
	ldr r0, [r1, #0x10]
	ldr r1, [r1, #4]
	ldr r0, [r0, #0xc]
	lsl r2, r1, #1
	ldr r1, _021D7848 ; =0x021D968B
	ldrb r1, [r1, r2]
	mov r2, #0x20
	lsl r1, r1, #5
	add r0, r0, r1
	mov r1, #0
	bl GX_LoadOBJPltt
	b _021D7838
_021D7832:
	ldr r0, [r4, #0x14]
	add r0, r0, #1
	str r0, [r4, #0x14]
_021D7838:
	mov r0, #0xe9
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD54_021D8A90
_021D7842:
	pop {r4, pc}
	.align 2, 0
_021D7844: .word MOD54_021D968A
_021D7848: .word MOD54_021D968B
	thumb_func_end MOD54_021D77E8

	thumb_func_start MOD54_021D784C
MOD54_021D784C: ; 0x021D784C
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0201C30C
	bl FUN_02009F80
	add r0, r4, #0
	bl FUN_0201AB60
	ldr r3, _021D786C ; =0x027E0000
	ldr r1, _021D7870 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	.align 2, 0
_021D786C: .word 0x027E0000
_021D7870: .word 0x00003FF8
	thumb_func_end MOD54_021D784C

	thumb_func_start MOD54_021D7874
MOD54_021D7874: ; 0x021D7874
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D7890 ; =0x021D9758
	add r3, sp, #0
	mov r2, #5
_021D787E:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D787E
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D7890: .word MOD54_021D9758
	thumb_func_end MOD54_021D7874

	thumb_func_start MOD54_021D7894
MOD54_021D7894: ; 0x021D7894
	push {r4, r5, lr}
	sub sp, #0x9c
	ldr r5, _021D7984 ; =0x021D9694
	add r3, sp, #0x8c
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _021D7988 ; =0x021D9720
	add r3, sp, #0x70
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
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	ldr r5, _021D798C ; =0x021D973C
	add r3, sp, #0x54
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
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #5
	bl FUN_02018744
	ldr r5, _021D7990 ; =0x021D96CC
	add r3, sp, #0x38
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
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D7994 ; =0x021D96E8
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
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _021D7998 ; =0x021D9704
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	add r0, r4, #0
	mov r1, #1
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x33
	bl FUN_02017F18
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x33
	bl FUN_02017F18
	add sp, #0x9c
	pop {r4, r5, pc}
	nop
_021D7984: .word MOD54_021D9694
_021D7988: .word MOD54_021D9720
_021D798C: .word MOD54_021D973C
_021D7990: .word MOD54_021D96CC
_021D7994: .word MOD54_021D96E8
_021D7998: .word MOD54_021D9704
	thumb_func_end MOD54_021D7894

	thumb_func_start MOD54_021D799C
MOD54_021D799C: ; 0x021D799C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r6, #0
	add r4, r7, #0
	add r5, r7, #0
_021D79A6:
	mov r0, #8
	mov r1, #0x33
	bl String_ctor
	str r0, [r4, #0x2c]
	mov r0, #0xd9
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
	add r0, r0, #4
	str r1, [r5, r0]
	mov r0, #0xe3
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r6, r6, #1
	add r4, r4, #4
	add r5, #8
	cmp r6, #5
	blt _021D79A6
	mov r0, #0xb4
	mov r1, #0x33
	bl String_ctor
	str r0, [r7, #0x44]
	mov r0, #0x28
	mov r1, #0x33
	bl String_ctor
	str r0, [r7, #0x48]
	mov r0, #0xd1
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r7, r0]
	ldr r0, [r7, #0x28]
	ldr r2, [r7, #0x48]
	mov r1, #0x11
	bl ReadMsgDataIntoString
	add r0, r7, #0
	bl MOD54_021D8E64
	mov r0, #0x33
	bl FUN_02053708
	mov r1, #0xea
	lsl r1, r1, #2
	str r0, [r7, r1]
	mov r0, #0
	str r0, [r7, #0xc]
	str r0, [r7, #0x14]
	add r2, r7, #0
	str r0, [r7, #0x10]
	mov r0, #0x56
	mov r1, #1
	add r2, #0x1c
	mov r3, #0x33
	bl FUN_02006C08
	str r0, [r7, #0x18]
	mov r1, #0x32
	ldr r0, _021D7A30 ; =0x00004A44
	mov r2, #0
	str r2, [r7, r0]
	lsl r1, r1, #4
	str r2, [r7, r1]
	mov r1, #2
	add r0, r0, #4
	str r1, [r7, r0]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D7A30: .word 0x00004A44
	thumb_func_end MOD54_021D799C

	thumb_func_start MOD54_021D7A34
MOD54_021D7A34: ; 0x021D7A34
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl MOD54_021D8F0C
	ldr r0, [r6, #0x18]
	bl FreeToHeap
	mov r0, #0xea
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FreeToHeap
	mov r4, #0
	add r5, r6, #0
_021D7A50:
	ldr r0, [r5, #0x2c]
	bl String_dtor
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _021D7A50
	ldr r0, [r6, #0x48]
	bl String_dtor
	ldr r0, [r6, #0x44]
	bl String_dtor
	pop {r4, r5, r6, pc}
	thumb_func_end MOD54_021D7A34

	thumb_func_start MOD54_021D7A6C
MOD54_021D7A6C: ; 0x021D7A6C
	push {r4, lr}
	add r4, r0, #0
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #4
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #0
	bl FUN_020178A0
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD54_021D7A6C

	thumb_func_start MOD54_021D7AA0
MOD54_021D7AA0: ; 0x021D7AA0
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #2
	ldr r4, [r5]
	mov r1, #0
	lsl r0, r0, #8
	str r0, [sp]
	mov r0, #0x33
	str r0, [sp, #4]
	mov r0, #0x56
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02006930
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x33
	str r0, [sp, #4]
	mov r0, #0xc
	add r1, r0, #0
	mov r2, #4
	mov r3, #0
	bl FUN_02006930
	mov r1, #0x1a
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x33
	bl FUN_02002EEC
	mov r1, #0x1a
	mov r0, #4
	lsl r1, r1, #4
	mov r2, #0x33
	bl FUN_02002EEC
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x33
	str r0, [sp, #0xc]
	mov r0, #0xc
	mov r1, #0xa
	add r2, r4, #0
	mov r3, #6
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x33
	str r0, [sp, #0xc]
	mov r0, #0xc
	mov r1, #0xb
	add r2, r4, #0
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x33
	str r0, [sp, #0xc]
	mov r0, #0x56
	mov r1, #2
	add r2, r4, #0
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x33
	str r0, [sp, #0xc]
	mov r0, #0x56
	mov r1, #3
	add r2, r4, #0
	bl FUN_020068C8
	ldr r0, [r5, #8]
	ldr r0, [r0, #8]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x33
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200CD68
	mov r1, #0
	str r1, [sp]
	mov r0, #0x33
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_0200CB00
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD54_021D7AA0

	thumb_func_start MOD54_021D7B8C
MOD54_021D7B8C: ; 0x021D7B8C
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _021D7BB8 ; =0x021D96A4
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_0201D040
	mov r0, #0x14
	mov r1, #0x33
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021D7BB8: .word MOD54_021D96A4
	thumb_func_end MOD54_021D7B8C

	thumb_func_start MOD54_021D7BBC
MOD54_021D7BBC: ; 0x021D7BBC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x7e
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x33
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	add r1, r6, #0
	mov r0, #0x1e
	add r1, #0x54
	mov r2, #0x33
	bl FUN_02008C9C
	str r0, [r6, #0x50]
	add r0, r6, #0
	mov r2, #1
	add r0, #0x54
	mov r1, #0
	lsl r2, r2, #0x14
	bl FUN_02008D24
	mov r7, #0x5f
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_021D7C02:
	mov r0, #3
	add r1, r4, #0
	mov r2, #0x33
	bl FUN_02008DEC
	str r0, [r5, r7]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021D7C02
	mov r0, #2
	str r0, [sp]
	mov r3, #1
	str r3, [sp, #4]
	mov r0, #0x33
	str r0, [sp, #8]
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	mov r1, #0x56
	mov r2, #0xc
	bl FUN_02008F34
	mov r1, #0x6b
	lsl r1, r1, #2
	str r0, [r6, r1]
	mov r0, #2
	str r0, [sp]
	mov r2, #1
	str r2, [sp, #4]
	mov r0, #0xf
	str r0, [sp, #8]
	mov r0, #0x33
	sub r1, #0x2c
	str r0, [sp, #0xc]
	ldr r0, [r6, r1]
	mov r1, #0x56
	mov r3, #0
	bl FUN_02008FEC
	mov r1, #0x1b
	lsl r1, r1, #4
	str r0, [r6, r1]
	mov r0, #2
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x33
	sub r1, #0x2c
	str r0, [sp, #8]
	ldr r0, [r6, r1]
	mov r1, #0x56
	mov r2, #0xd
	mov r3, #1
	bl FUN_020090AC
	mov r1, #0x6d
	lsl r1, r1, #2
	str r0, [r6, r1]
	mov r0, #2
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x33
	sub r1, #0x2c
	str r0, [sp, #8]
	ldr r0, [r6, r1]
	mov r1, #0x56
	mov r2, #0xe
	mov r3, #1
	bl FUN_020090AC
	mov r1, #0x6e
	lsl r1, r1, #2
	str r0, [r6, r1]
	sub r1, #0xc
	ldr r0, [r6, r1]
	bl FUN_02009A50
	mov r0, #0x1b
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	bl FUN_02009CF0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD54_021D7BBC

	thumb_func_start MOD54_021D7CAC
MOD54_021D7CAC: ; 0x021D7CAC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	mov r1, #2
	add r5, r0, #0
	str r1, [sp]
	sub r0, r1, #3
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	mov r3, #0x5f
	str r0, [sp, #0xc]
	mov r2, #1
	lsl r3, r3, #2
	str r2, [sp, #0x10]
	ldr r2, [r5, r3]
	str r2, [sp, #0x14]
	add r2, r3, #4
	ldr r2, [r5, r2]
	str r2, [sp, #0x18]
	add r2, r3, #0
	add r2, #8
	ldr r2, [r5, r2]
	str r2, [sp, #0x1c]
	add r2, r3, #0
	add r2, #0xc
	ldr r2, [r5, r2]
	add r3, #0x88
	str r2, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r0, r5, r3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02008AA4
	ldr r0, [r5, #0x50]
	mov r1, #0
	str r0, [sp, #0x2c]
	mov r0, #0x81
	lsl r0, r0, #2
	add r0, r5, r0
	str r0, [sp, #0x30]
	mov r0, #1
	lsl r0, r0, #0xc
	str r1, [sp, #0x3c]
	str r0, [sp, #0x40]
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	add r0, sp, #0x2c
	strh r1, [r0, #0x20]
	mov r0, #1
	str r0, [sp, #0x50]
	str r0, [sp, #0x54]
	mov r0, #0x33
	str r0, [sp, #0x58]
	lsl r0, r0, #0xe
	str r0, [sp, #0x34]
	mov r0, #0x15
	lsl r0, r0, #0xe
	str r0, [sp, #0x38]
	add r0, sp, #0x2c
	bl FUN_0201FE94
	mov r1, #0x8a
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r7, #0x8b
	ldr r4, _021D7DB0 ; =0x021D96B4
	mov r6, #0
	lsl r7, r7, #2
_021D7D4C:
	ldrh r0, [r4, #4]
	lsl r0, r0, #0xc
	str r0, [sp, #0x34]
	ldrh r0, [r4, #6]
	lsl r0, r0, #0xc
	str r0, [sp, #0x38]
	add r0, sp, #0x2c
	bl FUN_0201FE94
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x8b
	lsl r0, r0, #2
	sub r1, r6, #1
	lsl r1, r1, #1
	ldr r0, [r5, r0]
	add r1, #0x1b
	bl FUN_02020130
	ldr r0, [r5, r7]
	mov r1, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r4, r4, #4
	add r5, r5, #4
	cmp r6, #5
	blt _021D7D4C
	mov r0, #6
	lsl r0, r0, #0xe
	str r0, [sp, #0x34]
	mov r0, #0x1a
	lsl r0, r0, #0x10
	str r0, [sp, #0x38]
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D7DB0: .word MOD54_021D96B4
	thumb_func_end MOD54_021D7CAC

	thumb_func_start MOD54_021D7DB4
MOD54_021D7DB4: ; 0x021D7DB4
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0x14
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _021D7E90 ; =0x000001C3
	mov r1, #0xbe
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	ldr r0, [r4]
	add r1, r4, r1
	mov r2, #5
	mov r3, #0x1a
	bl FUN_02019064
	mov r0, #0xbe
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x28
	mov r1, #0xba
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	ldr r0, [r4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #2
	bl FUN_02019064
	mov r0, #0xba
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #1
	str r0, [sp]
	mov r0, #0x1a
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	mov r0, #0x94
	mov r1, #0xc2
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	ldr r0, [r4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #3
	bl FUN_02019064
	mov r0, #0xc2
	lsl r0, r0, #2
	ldr r1, [r4, #0x48]
	add r0, r4, r0
	mov r2, #0
	bl MOD54_021D7E98
	mov r0, #6
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	mov r0, #0xb
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	mov r0, #0xc8
	mov r1, #0xa6
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	ldr r0, [r4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #2
	bl FUN_02019064
	mov r0, #0xa6
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl FUN_02019620
	mov r0, #0xa6
	lsl r0, r0, #2
	ldr r2, _021D7E94 ; =0x00010300
	add r0, r4, r0
	mov r1, #0
	add r3, r4, #0
	bl MOD54_021D8AF8
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0
_021D7E90: .word 0x000001C3
_021D7E94: .word 0x00010300
	thumb_func_end MOD54_021D7DB4

	thumb_func_start MOD54_021D7E98
MOD54_021D7E98: ; 0x021D7E98
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r4, r2, #0
	mov r0, #1
	mov r2, #0
	add r7, r1, #0
	bl FUN_02002E14
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	mov r1, #1
	str r1, [sp]
	mov r0, #0x41
	mov r3, #0xd0
	str r4, [sp, #4]
	sub r4, r3, r6
	lsl r0, r0, #0xa
	lsr r3, r4, #0x1f
	str r0, [sp, #8]
	mov r0, #0
	add r3, r4, r3
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r2, r7, #0
	asr r3, r3, #1
	bl AddTextPrinterParameterized2
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD54_021D7E98

	thumb_func_start MOD54_021D7EDC
MOD54_021D7EDC: ; 0x021D7EDC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xa6
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
	mov r0, #0xc2
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
	mov r0, #0xbe
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
	mov r0, #0xba
	lsl r0, r0, #2
	add r0, r4, r0
	bl FUN_02019178
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD54_021D7EDC

	thumb_func_start MOD54_021D7F0C
MOD54_021D7F0C: ; 0x021D7F0C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0
	mov r1, #1
	bl FUN_020334E8
	bl FUN_02031190
	cmp r0, #0
	bne _021D7F2E
	add r0, r5, #0
	mov r1, #2
	mov r2, #0
	bl MOD54_021D8C90
	b _021D7F38
_021D7F2E:
	add r0, r5, #0
	mov r1, #8
	mov r2, #0
	bl MOD54_021D8C90
_021D7F38:
	add r0, r5, #0
	mov r1, #3
	bl MOD54_021D80BC
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD54_021D7F0C

	thumb_func_start MOD54_021D7F44
MOD54_021D7F44: ; 0x021D7F44
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD54_021D7F70
	bl FUN_02031190
	cmp r0, #0
	bne _021D7F66
	bl MOD54_021D8ADC
	cmp r0, #1
	beq _021D7F6C
	add r0, r5, #0
	bl MOD54_021D8C04
	b _021D7F6C
_021D7F66:
	add r0, r5, #0
	bl MOD54_021D8C04
_021D7F6C:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD54_021D7F44

	thumb_func_start MOD54_021D7F70
MOD54_021D7F70: ; 0x021D7F70
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, _021D808C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _021D7FD6
	bl FUN_02031190
	cmp r0, #0
	bne _021D8086
	bl MOD54_021D8C08
	ldr r1, _021D8090 ; =0x00004A48
	ldr r2, [r4, r1]
	cmp r2, r0
	bne _021D7FCC
	add r1, #8
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _021D7FCC
	mov r1, #1
	add r0, sp, #0
	strb r1, [r0, #2]
	add r0, r4, #0
	mov r1, #3
	mov r2, #0
	bl MOD54_021D8C90
	add r0, r4, #0
	mov r1, #0x16
	bl MOD54_021D80BC
	add r1, sp, #0
	mov r0, #0x75
	add r1, #2
	mov r2, #1
	bl FUN_02030ADC
	add r0, r4, #0
	mov r1, #0
	bl MOD54_021D8F40
	add sp, #4
	pop {r3, r4, pc}
_021D7FCC:
	ldr r0, _021D8094 ; =0x000005F2
	bl FUN_020054C8
	add sp, #4
	pop {r3, r4, pc}
_021D7FD6:
	mov r0, #2
	tst r0, r1
	beq _021D805A
	bl FUN_02031190
	cmp r0, #0
	beq _021D800C
	ldr r0, _021D8098 ; =0x00004A3C
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021D8002
	add r0, r4, #0
	mov r1, #4
	mov r2, #0
	bl MOD54_021D8C90
	add r0, r4, #0
	mov r1, #4
	bl MOD54_021D80BC
	add sp, #4
	pop {r3, r4, pc}
_021D8002:
	ldr r0, _021D8094 ; =0x000005F2
	bl FUN_020054C8
	add sp, #4
	pop {r3, r4, pc}
_021D800C:
	bl FUN_02030F20
	ldr r1, _021D8090 ; =0x00004A48
	ldr r2, [r4, r1]
	cmp r2, r0
	bne _021D8050
	add r1, #8
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _021D8050
	mov r1, #1
	add r0, sp, #0
	strb r1, [r0, #1]
	add r0, r4, #0
	mov r1, #4
	mov r2, #0
	bl MOD54_021D8C90
	add r0, r4, #0
	mov r1, #4
	bl MOD54_021D80BC
	add r1, sp, #0
	mov r0, #0x75
	add r1, #1
	mov r2, #1
	bl FUN_02030ADC
	add r0, r4, #0
	mov r1, #0
	bl MOD54_021D8F40
	add sp, #4
	pop {r3, r4, pc}
_021D8050:
	ldr r0, _021D8094 ; =0x000005F2
	bl FUN_020054C8
	add sp, #4
	pop {r3, r4, pc}
_021D805A:
	ldr r0, _021D809C ; =0x00004A4C
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021D8086
	bl FUN_02031190
	cmp r0, #0
	bne _021D8086
	bl FUN_02030F20
	ldr r1, _021D8090 ; =0x00004A48
	ldr r1, [r4, r1]
	cmp r1, r0
	bne _021D8086
	mov r1, #0
	add r0, sp, #0
	strb r1, [r0]
	mov r0, #0x75
	add r1, sp, #0
	mov r2, #1
	bl FUN_02030ADC
_021D8086:
	add sp, #4
	pop {r3, r4, pc}
	nop
_021D808C: .word gMain
_021D8090: .word 0x00004A48
_021D8094: .word 0x000005F2
_021D8098: .word 0x00004A3C
_021D809C: .word 0x00004A4C
	thumb_func_end MOD54_021D7F70

	thumb_func_start MOD54_021D80A0
MOD54_021D80A0: ; 0x021D80A0
	bx lr
	.align 2, 0
	thumb_func_end MOD54_021D80A0

	thumb_func_start MOD54_021D80A4
MOD54_021D80A4: ; 0x021D80A4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	mov r1, #2
	bl MOD54_021D80BC
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD54_021D80A4

	thumb_func_start MOD54_021D80BC
MOD54_021D80BC: ; 0x021D80BC
	mov r2, #0xd1
	mov r3, #0x1e
	lsl r2, r2, #2
	str r3, [r0, r2]
	add r2, r2, #4
	str r1, [r0, r2]
	bx lr
	.align 2, 0
	thumb_func_end MOD54_021D80BC

	thumb_func_start MOD54_021D80CC
MOD54_021D80CC: ; 0x021D80CC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x4c]
	add r4, r1, #0
	bl MOD54_021D8D20
	cmp r0, #0
	beq _021D80E6
	mov r0, #0xd2
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	sub r0, r0, #4
	str r1, [r5, r0]
_021D80E6:
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD54_021D80CC

	thumb_func_start MOD54_021D80F0
MOD54_021D80F0: ; 0x021D80F0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02031190
	cmp r0, #0
	bne _021D810C
	mov r0, #0
	str r0, [sp]
	mov r0, #0x75
	add r1, sp, #0
	mov r2, #1
	bl FUN_02030ADC
_021D810C:
	mov r0, #0xd1
	mov r1, #3
	lsl r0, r0, #2
	str r1, [r5, r0]
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD54_021D80F0

	thumb_func_start MOD54_021D8120
MOD54_021D8120: ; 0x021D8120
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x33
	add r4, r1, #0
	str r0, [sp]
	ldr r0, [r5]
	ldr r1, _021D814C ; =0x021D9678
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x32
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #5
	add r1, #0x24
	str r0, [r5, r1]
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D814C: .word MOD54_021D9678
	thumb_func_end MOD54_021D8120

	thumb_func_start MOD54_021D8150
MOD54_021D8150: ; 0x021D8150
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02031190
	cmp r0, #0
	beq _021D8184
	ldr r0, _021D826C ; =0x00004A3C
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D81A8
	ldr r0, _021D8270 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0xc3
	tst r0, r1
	beq _021D8178
	ldr r0, _021D8274 ; =0x000005F2
	bl FUN_020054C8
_021D8178:
	add r0, r5, #0
	bl MOD54_021D80A0
	add sp, #8
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_021D8184:
	ldr r0, _021D8278 ; =0x00004A50
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D81A8
	ldr r0, _021D8270 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0xc3
	tst r0, r1
	beq _021D819C
	ldr r0, _021D8274 ; =0x000005F2
	bl FUN_020054C8
_021D819C:
	add r0, r5, #0
	bl MOD54_021D80A0
	add sp, #8
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_021D81A8:
	bl MOD54_021D8C08
	add r6, r0, #0
	bl FUN_02030F20
	cmp r6, r0
	beq _021D81C2
	add r0, r5, #0
	bl MOD54_021D80A0
	add sp, #8
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_021D81C2:
	mov r0, #0x32
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x33
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _021D825E
	sub r1, r1, #1
	cmp r0, r1
	bne _021D8204
	bl FUN_02031190
	cmp r0, #0
	bne _021D81FA
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #0x75
	add r1, sp, #4
	mov r2, #1
	bl FUN_02030ADC
	add r0, r5, #0
	mov r1, #1
	bl MOD54_021D8F40
_021D81FA:
	add r0, r5, #0
	mov r1, #0
	bl MOD54_021D80BC
	b _021D8256
_021D8204:
	bl FUN_02031190
	cmp r0, #0
	bne _021D8220
	add r0, r5, #0
	mov r1, #0xb
	bl MOD54_021D80BC
	add r0, r5, #0
	mov r1, #0xe
	mov r2, #0
	bl MOD54_021D8C90
	b _021D8256
_021D8220:
	add r0, sp, #0
	mov r1, #0
	mov r2, #4
	bl MI_CpuFill8
	mov r1, #0
	add r0, sp, #0
	strb r1, [r0, #2]
	bl FUN_02031190
	add r1, sp, #0
	strb r0, [r1]
	ldr r0, _021D827C ; =0x00004A54
	mov r1, #1
	strb r1, [r5, r0]
	mov r1, #0
	add r0, #0xa
	strh r1, [r5, r0]
	mov r0, #0xd1
	mov r1, #6
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r0, #0x70
	add r1, sp, #0
	mov r2, #4
	bl FUN_02030ADC
_021D8256:
	mov r0, #0x32
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r5, r0]
_021D825E:
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_021D826C: .word 0x00004A3C
_021D8270: .word gMain
_021D8274: .word 0x000005F2
_021D8278: .word 0x00004A50
_021D827C: .word 0x00004A54
	thumb_func_end MOD54_021D8150

	thumb_func_start MOD54_021D8280
MOD54_021D8280: ; 0x021D8280
	push {r4, lr}
	add r4, r1, #0
	ldr r1, _021D8294 ; =0x00004A5E
	mov r2, #0
	strh r2, [r0, r1]
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r4, pc}
	nop
_021D8294: .word 0x00004A5E
	thumb_func_end MOD54_021D8280

	thumb_func_start MOD54_021D8298
MOD54_021D8298: ; 0x021D8298
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02030F20
	ldr r1, _021D8318 ; =0x00004A5C
	ldrh r1, [r5, r1]
	cmp r1, r0
	bne _021D82B6
	bl MOD54_021D8C08
	ldr r1, _021D8318 ; =0x00004A5C
	ldrh r2, [r5, r1]
	cmp r2, r0
	beq _021D82CE
_021D82B6:
	ldr r0, _021D831C ; =0x00004A5E
	mov r1, #0
	strh r1, [r5, r0]
	mov r0, #0xd1
	mov r1, #8
	lsl r0, r0, #2
	str r1, [r5, r0]
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_021D82CE:
	add r0, r1, #2
	ldrsh r0, [r5, r0]
	add r2, r0, #1
	add r0, r1, #2
	strh r2, [r5, r0]
	ldrsh r0, [r5, r0]
	cmp r0, #0x1e
	ble _021D830E
	add r0, sp, #0
	mov r1, #0
	mov r2, #4
	bl MI_CpuFill8
	mov r1, #1
	add r0, sp, #0
	strb r1, [r0, #2]
	bl FUN_02031190
	add r1, sp, #0
	strb r0, [r1]
	mov r0, #0x70
	add r1, sp, #0
	mov r2, #4
	bl FUN_02030ADC
	ldr r0, _021D831C ; =0x00004A5E
	mov r1, #0
	strh r1, [r5, r0]
	mov r0, #0xd1
	mov r1, #9
	lsl r0, r0, #2
	str r1, [r5, r0]
_021D830E:
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8318: .word 0x00004A5C
_021D831C: .word 0x00004A5E
	thumb_func_end MOD54_021D8298

	thumb_func_start MOD54_021D8320
MOD54_021D8320: ; 0x021D8320
	push {r3, r4, r5, lr}
	ldr r2, _021D833C ; =0x00004A54
	add r4, r1, #0
	add r5, r0, #0
	mov r1, #0
	strb r1, [r5, r2]
	bl MOD54_021D80BC
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D833C: .word 0x00004A54
	thumb_func_end MOD54_021D8320

	thumb_func_start MOD54_021D8340
MOD54_021D8340: ; 0x021D8340
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x33
	add r4, r1, #0
	str r0, [sp]
	ldr r0, [r5]
	ldr r1, _021D836C ; =0x021D9678
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x32
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #0x17
	add r1, #0x24
	str r0, [r5, r1]
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D836C: .word MOD54_021D9678
	thumb_func_end MOD54_021D8340

	thumb_func_start MOD54_021D8370
MOD54_021D8370: ; 0x021D8370
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD54_021D8C08
	ldr r1, _021D8410 ; =0x00004A48
	ldr r2, [r5, r1]
	cmp r2, r0
	bne _021D838A
	add r1, #8
	ldr r0, [r5, r1]
	cmp r0, #0
	beq _021D83A4
_021D838A:
	ldr r0, _021D8414 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0xc3
	tst r0, r1
	beq _021D839A
	ldr r0, _021D8418 ; =0x000005F2
	bl FUN_020054C8
_021D839A:
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_021D83A4:
	mov r0, #0x32
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x33
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _021D8404
	sub r1, r1, #1
	cmp r0, r1
	bne _021D83DE
	mov r0, #0
	str r0, [sp]
	mov r0, #0x75
	add r1, sp, #0
	mov r2, #1
	bl FUN_02030ADC
	add r0, r5, #0
	mov r1, #1
	bl MOD54_021D8F40
	add r0, r5, #0
	mov r1, #0
	bl MOD54_021D80BC
	b _021D83FC
_021D83DE:
	bl FUN_02031190
	cmp r0, #0
	bne _021D83F8
	mov r0, #0xd1
	mov r1, #0x18
	lsl r0, r0, #2
	str r1, [r5, r0]
	bl MOD54_021D8C08
	ldr r1, _021D841C ; =0x00004A56
	strb r0, [r5, r1]
	b _021D83FC
_021D83F8:
	bl ErrorHandling
_021D83FC:
	mov r0, #0x32
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r5, r0]
_021D8404:
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D8410: .word 0x00004A48
_021D8414: .word gMain
_021D8418: .word 0x000005F2
_021D841C: .word 0x00004A56
	thumb_func_end MOD54_021D8370

	thumb_func_start MOD54_021D8420
MOD54_021D8420: ; 0x021D8420
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021D8448 ; =0x00004A57
	add r4, r1, #0
	ldrb r0, [r5, r0]
	cmp r0, #0
	bne _021D8442
	mov r1, #0
	mov r0, #0x73
	add r2, r1, #0
	bl FUN_02030ADC
	cmp r0, #1
	bne _021D8442
	ldr r0, _021D8448 ; =0x00004A57
	mov r1, #1
	strb r1, [r5, r0]
_021D8442:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D8448: .word 0x00004A57
	thumb_func_end MOD54_021D8420

	thumb_func_start MOD54_021D844C
MOD54_021D844C: ; 0x021D844C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	ldr r2, [r4, #0x48]
	mov r1, #0x12
	bl ReadMsgDataIntoString
	mov r0, #0xc2
	lsl r0, r0, #2
	ldr r1, [r4, #0x48]
	add r0, r4, r0
	mov r2, #0
	bl MOD54_021D7E98
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x25
	bl FUN_02020130
	mov r0, #1
	str r0, [r4, #0xc]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD54_021D844C

	thumb_func_start MOD54_021D847C
MOD54_021D847C: ; 0x021D847C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02031190
	cmp r0, #0
	bne _021D848E
	bl FUN_02030F20
_021D848E:
	bl FUN_02030F20
	ldr r1, _021D84A8 ; =0x00004A34
	ldr r1, [r5, r1]
	cmp r1, r0
	bne _021D84A2
	mov r0, #0xd1
	mov r1, #0x1a
	lsl r0, r0, #2
	str r1, [r5, r0]
_021D84A2:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D84A8: .word 0x00004A34
	thumb_func_end MOD54_021D847C

	thumb_func_start MOD54_021D84AC
MOD54_021D84AC: ; 0x021D84AC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021D84CC ; =0x00004A38
	add r4, r1, #0
	ldr r1, _021D84D0 ; =0x00000F74
	ldr r0, [r5, r0]
	add r1, r5, r1
	bl MOD54_021D95CC
	mov r0, #0xd1
	mov r1, #0x1b
	lsl r0, r0, #2
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D84CC: .word 0x00004A38
_021D84D0: .word 0x00000F74
	thumb_func_end MOD54_021D84AC

	thumb_func_start MOD54_021D84D4
MOD54_021D84D4: ; 0x021D84D4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r0, _021D8514 ; =gUnk021C4918
	mov r1, #1
	strb r1, [r0, #8]
	mov r0, #0x33
	bl FUN_020294F4
	add r1, r0, #0
	ldr r0, [r5, #8]
	mov r2, #4
	ldr r0, [r0, #0x10]
	bl FUN_02028AD4
	ldr r0, [r5, #8]
	mov r1, #0x14
	ldr r0, [r0, #0xc]
	bl FUN_0202A170
	mov r0, #0x3a
	lsl r0, r0, #4
	add r0, r5, r0
	bl FUN_020336C0
	mov r0, #0xd1
	mov r1, #0x1c
	lsl r0, r0, #2
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D8514: .word gUnk021C4918
	thumb_func_end MOD54_021D84D4

	thumb_func_start MOD54_021D8518
MOD54_021D8518: ; 0x021D8518
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02031190
	cmp r0, #0
	bne _021D852A
	bl FUN_02030F20
_021D852A:
	ldr r0, [r5, #8]
	mov r2, #0x3a
	lsl r2, r2, #4
	ldr r0, [r0]
	mov r1, #2
	add r2, r5, r2
	bl FUN_020336C8
	cmp r0, #0
	beq _021D8576
	ldr r0, _021D857C ; =0x00000658
	mov r1, #8
	bl FUN_020054F0
	add r0, r5, #0
	mov r1, #0xd
	mov r2, #0
	bl MOD54_021D8C90
	add r0, r5, #0
	mov r1, #0x1d
	bl MOD54_021D80BC
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02020130
	mov r1, #0
	mov r0, #0x35
	str r1, [r5, #0xc]
	lsl r0, r0, #4
	str r1, [r5, r0]
	ldr r0, _021D8580 ; =gUnk021C4918
	strb r1, [r0, #8]
	ldr r0, _021D8584 ; =0x00004A40
	strb r1, [r5, r0]
_021D8576:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D857C: .word 0x00000658
_021D8580: .word gUnk021C4918
_021D8584: .word 0x00004A40
	thumb_func_end MOD54_021D8518

	thumb_func_start MOD54_021D8588
MOD54_021D8588: ; 0x021D8588
	push {r3, r4}
	mov r2, #0x35
	lsl r2, r2, #4
	ldr r4, [r0, r2]
	add r3, r4, #1
	str r3, [r0, r2]
	cmp r4, #0x3c
	ble _021D859E
	mov r3, #0xf
	sub r2, #0xc
	str r3, [r0, r2]
_021D859E:
	add r0, r1, #0
	pop {r3, r4}
	bx lr
	thumb_func_end MOD54_021D8588

	thumb_func_start MOD54_021D85A4
MOD54_021D85A4: ; 0x021D85A4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	mov r1, #5
	mov r2, #0
	bl MOD54_021D8C90
	add r0, r5, #0
	mov r1, #0xa
	bl MOD54_021D80BC
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD54_021D85A4

	thumb_func_start MOD54_021D85C4
MOD54_021D85C4: ; 0x021D85C4
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0x35
	lsl r0, r0, #4
	add r4, r1, #0
	ldr r1, [r5, r0]
	add r1, r1, #1
	str r1, [r5, r0]
	ldr r0, [r5, r0]
	cmp r0, #0x3c
	ble _021D85F4
	mov r1, #0x10
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x33
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r4, #3
_021D85F4:
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, pc}
	thumb_func_end MOD54_021D85C4

	thumb_func_start MOD54_021D8600
MOD54_021D8600: ; 0x021D8600
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x33
	add r4, r1, #0
	str r0, [sp]
	ldr r0, [r5]
	ldr r1, _021D862C ; =0x021D9678
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_02002198
	mov r1, #0x32
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #0xc
	add r1, #0x24
	str r0, [r5, r1]
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D862C: .word MOD54_021D9678
	thumb_func_end MOD54_021D8600

	thumb_func_start MOD54_021D8630
MOD54_021D8630: ; 0x021D8630
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD54_021D8C08
	ldr r1, _021D86D0 ; =0x00004A48
	ldr r2, [r5, r1]
	cmp r2, r0
	bne _021D864A
	add r1, #8
	ldr r0, [r5, r1]
	cmp r0, #0
	beq _021D8664
_021D864A:
	ldr r0, _021D86D4 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0xc3
	tst r0, r1
	beq _021D865A
	ldr r0, _021D86D8 ; =0x000005F2
	bl FUN_020054C8
_021D865A:
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_021D8664:
	mov r0, #0x32
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x33
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _021D86C6
	sub r1, r1, #1
	cmp r0, r1
	bne _021D869C
	mov r1, #0
	mov r0, #0xd1
	str r1, [sp]
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r0, #0x75
	add r1, sp, #0
	mov r2, #1
	bl FUN_02030ADC
	add r0, r5, #0
	mov r1, #1
	bl MOD54_021D8F40
	b _021D86BE
_021D869C:
	mov r0, #0xd1
	mov r1, #0xd
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0
	mov r0, #0x71
	add r2, r1, #0
	bl FUN_02030ADC
	mov r0, #0
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r5, #0x24]
	mov r1, #0
	bl FUN_0200ABC0
_021D86BE:
	mov r0, #0x32
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r5, r0]
_021D86C6:
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D86D0: .word 0x00004A48
_021D86D4: .word gMain
_021D86D8: .word 0x000005F2
	thumb_func_end MOD54_021D8630

	thumb_func_start MOD54_021D86DC
MOD54_021D86DC: ; 0x021D86DC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02031190
	cmp r0, #0
	bne _021D86F6
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl MOD54_021D8C90
	b _021D8710
_021D86F6:
	mov r0, #0
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r5, #0x24]
	mov r1, #0
	bl FUN_0200ABC0
	add r0, r5, #0
	mov r1, #0x10
	mov r2, #0
	bl MOD54_021D8C90
_021D8710:
	add r0, r5, #0
	mov r1, #0xe
	bl MOD54_021D80BC
	mov r0, #0x35
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD54_021D86DC

	thumb_func_start MOD54_021D872C
MOD54_021D872C: ; 0x021D872C
	push {r4, lr}
	add r4, r1, #0
	mov r1, #0x35
	lsl r1, r1, #4
	ldr r2, [r0, r1]
	add r2, r2, #1
	str r2, [r0, r1]
	ldr r2, [r0, r1]
	cmp r2, #0x2d
	ble _021D8746
	mov r2, #0xf
	sub r1, #0xc
	str r2, [r0, r1]
_021D8746:
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD54_021D872C

	thumb_func_start MOD54_021D8750
MOD54_021D8750: ; 0x021D8750
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0xc9
	add r4, r1, #0
	bl FUN_02031588
	mov r0, #0xd1
	mov r1, #0x10
	lsl r0, r0, #2
	str r1, [r5, r0]
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD54_021D8750

	thumb_func_start MOD54_021D8770
MOD54_021D8770: ; 0x021D8770
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0xc9
	add r5, r1, #0
	bl FUN_020315D8
	cmp r0, #0
	beq _021D87A2
	mov r0, #0
	add r1, r0, #0
	bl FUN_020334E8
	mov r1, #0x10
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x33
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r5, #3
_021D87A2:
	add r0, r4, #0
	bl MOD54_021D80A0
	add r0, r5, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD54_021D8770

	thumb_func_start MOD54_021D87B0
MOD54_021D87B0: ; 0x021D87B0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #9
	mov r2, #0
	add r5, r0, #0
	bl MOD54_021D8C90
	mov r0, #0xd1
	mov r1, #0x12
	lsl r0, r0, #2
	str r1, [r5, r0]
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD54_021D87B0

	thumb_func_start MOD54_021D87D0
MOD54_021D87D0: ; 0x021D87D0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x4c]
	add r4, r1, #0
	bl MOD54_021D8D20
	cmp r0, #0
	beq _021D87E8
	mov r0, #0xd1
	mov r1, #0xa
	lsl r0, r0, #2
	str r1, [r5, r0]
_021D87E8:
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD54_021D87D0

	thumb_func_start MOD54_021D87F4
MOD54_021D87F4: ; 0x021D87F4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x4c]
	add r4, r1, #0
	cmp r0, #0xff
	beq _021D8812
	bl MOD54_021D8D20
	cmp r0, #0
	bne _021D8812
	ldr r0, [r5, #0x4c]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD7C
_021D8812:
	add r0, r5, #0
	mov r1, #0xf
	mov r2, #1
	bl MOD54_021D8C90
	mov r0, #0xd1
	mov r1, #0x14
	lsl r0, r0, #2
	str r1, [r5, r0]
	bl FUN_02031190
	cmp r0, #0
	bne _021D8834
	add r0, r5, #0
	mov r1, #0
	bl MOD54_021D8F40
_021D8834:
	bl FUN_02030F20
	ldr r1, _021D8848 ; =0x00004A58
	str r0, [r5, r1]
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D8848: .word 0x00004A58
	thumb_func_end MOD54_021D87F4

	thumb_func_start MOD54_021D884C
MOD54_021D884C: ; 0x021D884C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021D8884 ; =0x00004A58
	add r4, r1, #0
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D886A
	bl FUN_02030F20
	ldr r1, _021D8884 ; =0x00004A58
	ldr r2, [r5, r1]
	cmp r2, r0
	beq _021D886A
	mov r0, #0
	str r0, [r5, r1]
_021D886A:
	mov r0, #0xd1
	mov r1, #0x15
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0
	add r0, #0xc
	str r1, [r5, r0]
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D8884: .word 0x00004A58
	thumb_func_end MOD54_021D884C

	thumb_func_start MOD54_021D8888
MOD54_021D8888: ; 0x021D8888
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021D88E0 ; =0x00004A58
	add r4, r1, #0
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D88A6
	bl FUN_02030F20
	ldr r1, _021D88E0 ; =0x00004A58
	ldr r2, [r5, r1]
	cmp r2, r0
	beq _021D88A6
	mov r0, #0
	str r0, [r5, r1]
_021D88A6:
	mov r1, #0x35
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	add r0, r0, #1
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	cmp r0, #0x3c
	ble _021D88D4
	ldr r0, _021D88E0 ; =0x00004A58
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _021D88D4
	mov r0, #0
	sub r1, #0xc
	str r0, [r5, r1]
	bl FUN_02031190
	cmp r0, #0
	bne _021D88D4
	add r0, r5, #0
	mov r1, #1
	bl MOD54_021D8F40
_021D88D4:
	add r0, r5, #0
	bl MOD54_021D80A0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D88E0: .word 0x00004A58
	thumb_func_end MOD54_021D8888

	thumb_func_start MOD54_021D88E4
MOD54_021D88E4: ; 0x021D88E4
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	cmp r4, #0xd
	bgt _021D8906
	bge _021D891A
	cmp r4, #8
	bgt _021D89BE
	cmp r4, #2
	blt _021D89BE
	beq _021D8914
	cmp r4, #7
	beq _021D89B8
	cmp r4, #8
	beq _021D89B8
	pop {r4, r5, r6, pc}
_021D8906:
	cmp r4, #0x13
	bgt _021D890E
	beq _021D896C
	pop {r4, r5, r6, pc}
_021D890E:
	cmp r4, #0x19
	beq _021D8934
	pop {r4, r5, r6, pc}
_021D8914:
	bl MOD54_021D8D40
	b _021D89B8
_021D891A:
	mov r0, #0x32
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D89B8
	mov r1, #0x33
	bl FUN_020021EC
	mov r0, #0x32
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _021D89B8
_021D8934:
	ldr r0, [r5, #0x4c]
	bl MOD54_021D8D20
	cmp r0, #0
	bne _021D8948
	ldr r0, [r5, #0x4c]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD7C
_021D8948:
	add r0, r5, #0
	mov r1, #0xc
	mov r2, #0
	bl MOD54_021D8C90
	mov r0, #0x32
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D89B8
	mov r1, #0x33
	bl FUN_020021EC
	mov r0, #0x32
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _021D89B8
_021D896C:
	ldr r0, _021D89C0 ; =0x00004A54
	ldrb r0, [r5, r0]
	cmp r0, #1
	beq _021D89BE
	add r0, r6, #0
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r5, #0x24]
	mov r1, #0
	bl FUN_0200ABC0
	bl FUN_02031190
	cmp r6, r0
	beq _021D89BE
	mov r0, #0x32
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D89A4
	mov r1, #0x33
	bl FUN_020021EC
	mov r0, #0x32
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r5, r0]
_021D89A4:
	bl FUN_02031190
	cmp r0, #0
	bne _021D89B8
	ldr r1, _021D89C4 ; =0x00004A50
	ldr r0, _021D89C8 ; =0x0000FFFF
	ldr r2, [r5, r1]
	eor r0, r6
	and r0, r2
	str r0, [r5, r1]
_021D89B8:
	mov r0, #0xd1
	lsl r0, r0, #2
	str r4, [r5, r0]
_021D89BE:
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D89C0: .word 0x00004A54
_021D89C4: .word 0x00004A50
_021D89C8: .word 0x0000FFFF
	thumb_func_end MOD54_021D88E4

	thumb_func_start MOD54_021D89CC
MOD54_021D89CC: ; 0x021D89CC
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	mov r0, #0xd1
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	add r6, r2, #0
	cmp r0, #3
	bne _021D8A6C
	cmp r4, #1
	beq _021D89EA
	cmp r4, #0x13
	beq _021D8A2E
	b _021D8A64
_021D89EA:
	add r0, r6, #0
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r5, #0x24]
	mov r1, #0
	bl FUN_0200ABC0
	add r0, r5, #0
	mov r1, #1
	bl MOD54_021D8F40
	mov r0, #0xd1
	lsl r0, r0, #2
	str r4, [r5, r0]
	bl FUN_02030F20
	ldr r1, _021D8A84 ; =0x00004A48
	str r0, [r5, r1]
	mov r0, #0
	add r1, #8
	str r0, [r5, r1]
	bl FUN_02031190
	cmp r0, #0
	bne _021D8A7E
	mov r2, #1
	mov r0, #0x75
	add r1, sp, #0
	str r2, [sp]
	bl FUN_02030ADC
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_021D8A2E:
	add r0, r6, #0
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r5, #0x24]
	mov r1, #0
	bl FUN_0200ABC0
	bl FUN_02031190
	cmp r6, r0
	beq _021D8A7E
	bl FUN_02031190
	cmp r0, #0
	bne _021D8A5A
	ldr r1, _021D8A88 ; =0x00004A50
	ldr r0, _021D8A8C ; =0x0000FFFF
	ldr r2, [r5, r1]
	eor r0, r6
	and r0, r2
	str r0, [r5, r1]
_021D8A5A:
	mov r0, #0xd1
	lsl r0, r0, #2
	add sp, #4
	str r4, [r5, r0]
	pop {r3, r4, r5, r6, pc}
_021D8A64:
	bl ErrorHandling
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_021D8A6C:
	cmp r4, #1
	bne _021D8A7E
	ldr r0, _021D8A88 ; =0x00004A50
	mov r1, #0
	str r1, [r5, r0]
	bl FUN_02030F20
	ldr r1, _021D8A84 ; =0x00004A48
	str r0, [r5, r1]
_021D8A7E:
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_021D8A84: .word 0x00004A48
_021D8A88: .word 0x00004A50
_021D8A8C: .word 0x0000FFFF
	thumb_func_end MOD54_021D89CC

	thumb_func_start MOD54_021D8A90
MOD54_021D8A90: ; 0x021D8A90
	push {r3, lr}
	ldrh r1, [r0]
	add r1, #0xa
	strh r1, [r0]
	ldrh r2, [r0]
	mov r1, #0x5a
	lsl r1, r1, #2
	cmp r2, r1
	bls _021D8AA6
	mov r1, #0
	strh r1, [r0]
_021D8AA6:
	ldrh r0, [r0]
	bl Sin_Wrap
	mov r1, #0xa
	add r2, r0, #0
	mul r2, r1
	asr r0, r2, #0xb
	lsr r0, r0, #0x14
	add r0, r2, r0
	asr r0, r0, #0xc
	add r0, #0xf
	lsl r2, r0, #5
	mov r0, #0x1d
	orr r2, r0
	add r0, sp, #0
	strh r2, [r0]
	add r0, sp, #0
	mov r2, #2
	bl GX_LoadOBJPltt
	add r0, sp, #0
	mov r1, #0x2a
	mov r2, #2
	bl GX_LoadOBJPltt
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD54_021D8A90

	thumb_func_start MOD54_021D8ADC
MOD54_021D8ADC: ; 0x021D8ADC
	push {r3, r4, r5, lr}
	mov r5, #0
	add r4, r5, #0
_021D8AE2:
	add r0, r4, #0
	bl FUN_0202DFA4
	cmp r0, #0
	beq _021D8AEE
	add r5, r5, #1
_021D8AEE:
	add r4, r4, #1
	cmp r4, #5
	blt _021D8AE2
	add r0, r5, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD54_021D8ADC

	thumb_func_start MOD54_021D8AF8
MOD54_021D8AF8: ; 0x021D8AF8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r3, [sp, #0x14]
	add r6, r0, #0
	str r2, [sp, #0x10]
	bl FUN_02031190
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x14]
	bl MOD54_021D8C2C
	cmp r0, #0
	bne _021D8B18
	add sp, #0x28
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D8B18:
	add r0, r6, #0
	mov r1, #0
	bl FUN_02019620
	ldr r7, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x20]
	add r4, r7, #0
	mov r5, #1
_021D8B2A:
	mov r0, #0xd9
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	cmp r0, #0
	beq _021D8BE4
	bl PlayerProfile_GetTrainerID_VisibleHalf
	str r0, [sp, #0x24]
	mov r0, #0xd9
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	ldr r1, [r4, #0x2c]
	bl PlayerName_FlatToString
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x24]
	ldr r0, [r0, #0x24]
	mov r1, #0
	mov r3, #5
	bl FUN_0200AD38
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x14]
	ldr r0, [r0, #0x24]
	ldr r1, [r1, #0x28]
	mov r2, #1
	mov r3, #0x33
	bl ReadMsgData_ExpandPlaceholders
	str r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x20]
	cmp r1, r0
	str r5, [sp]
	bne _021D8BAC
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8C00 ; =0x00020300
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x2c]
	add r0, r6, #0
	mov r3, #5
	bl AddTextPrinterParameterized2
	str r5, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8C00 ; =0x00020300
	ldr r2, [sp, #0x18]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, r6, #0
	mov r1, #0
	mov r3, #0x46
	bl AddTextPrinterParameterized2
	b _021D8BDE
_021D8BAC:
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x10]
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x2c]
	add r0, r6, #0
	mov r3, #5
	bl AddTextPrinterParameterized2
	str r5, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x18]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, r6, #0
	mov r1, #0
	mov r3, #0x46
	bl AddTextPrinterParameterized2
_021D8BDE:
	ldr r0, [sp, #0x18]
	bl String_dtor
_021D8BE4:
	ldr r0, [sp, #0x20]
	add r7, #8
	add r0, r0, #1
	add r4, r4, #4
	add r5, #0x12
	str r0, [sp, #0x20]
	cmp r0, #5
	blt _021D8B2A
	add r0, r6, #0
	bl FUN_020191D0
	mov r0, #1
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8C00: .word 0x00020300
	thumb_func_end MOD54_021D8AF8

	thumb_func_start MOD54_021D8C04
MOD54_021D8C04: ; 0x021D8C04
	bx lr
	.align 2, 0
	thumb_func_end MOD54_021D8C04

	thumb_func_start MOD54_021D8C08
MOD54_021D8C08: ; 0x021D8C08
	push {r3, r4, r5, lr}
	mov r5, #0
	add r4, r5, #0
_021D8C0E:
	add r0, r4, #0
	bl FUN_0202DFA4
	cmp r0, #0
	beq _021D8C1A
	add r5, r5, #1
_021D8C1A:
	add r4, r4, #1
	cmp r4, #5
	blt _021D8C0E
	add r0, r5, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD54_021D8C08

	thumb_func_start MOD54_021D8C24
MOD54_021D8C24: ; 0x021D8C24
	ldr r3, _021D8C28 ; =MOD54_021D8C08
	bx r3
	.align 2, 0
_021D8C28: .word MOD54_021D8C08
	thumb_func_end MOD54_021D8C24

	thumb_func_start MOD54_021D8C2C
MOD54_021D8C2C: ; 0x021D8C2C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r4, #0
	mov r7, #0xd9
	str r4, [sp]
	add r5, r6, #0
	lsl r7, r7, #2
_021D8C3A:
	mov r0, #0xd9
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	add r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	bl FUN_0202DFA4
	str r0, [r5, r7]
	add r4, r4, #1
	add r5, #8
	cmp r4, #5
	blt _021D8C3A
	mov r7, #0xda
	mov r5, #0
	add r4, r6, #0
	mov r1, #1
	mov r0, #3
	lsl r7, r7, #2
_021D8C60:
	mov r2, #0xd9
	lsl r2, r2, #2
	ldr r3, [r6, r2]
	ldr r2, [r6, r7]
	cmp r2, r3
	beq _021D8C80
	str r1, [sp]
	cmp r3, #0
	bne _021D8C7A
	mov r2, #0xe3
	lsl r2, r2, #2
	str r0, [r4, r2]
	b _021D8C80
_021D8C7A:
	mov r2, #0xe3
	lsl r2, r2, #2
	str r1, [r4, r2]
_021D8C80:
	add r5, r5, #1
	add r6, #8
	add r4, r4, #4
	cmp r5, #5
	blt _021D8C60
	ldr r0, [sp]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD54_021D8C2C

	thumb_func_start MOD54_021D8C90
MOD54_021D8C90: ; 0x021D8C90
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r7, r1, #0
	mov r0, #0xb4
	mov r1, #0x33
	add r6, r2, #0
	bl String_ctor
	add r4, r0, #0
	ldr r0, [r5, #0x28]
	add r1, r7, #0
	add r2, r4, #0
	bl ReadMsgDataIntoString
	ldr r0, [r5, #0x24]
	ldr r1, [r5, #0x44]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	mov r0, #0xba
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0xba
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200D0BC
	cmp r6, #0
	bne _021D8D00
	add r0, r5, #0
	bl MOD54_021D8F3C
	mov r3, #0
	str r3, [sp]
	str r0, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0xba
	lsl r0, r0, #2
	ldr r2, [r5, #0x44]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized
	add sp, #0xc
	str r0, [r5, #0x4c]
	pop {r4, r5, r6, r7, pc}
_021D8D00:
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0xba
	lsl r0, r0, #2
	ldr r2, [r5, #0x44]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized
	mov r0, #0xff
	str r0, [r5, #0x4c]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD54_021D8C90

	thumb_func_start MOD54_021D8D20
MOD54_021D8D20: ; 0x021D8D20
	push {r3, lr}
	cmp r0, #0xff
	bne _021D8D2A
	mov r0, #1
	pop {r3, pc}
_021D8D2A:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021D8D3A
	mov r0, #1
	pop {r3, pc}
_021D8D3A:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD54_021D8D20

	thumb_func_start MOD54_021D8D40
MOD54_021D8D40: ; 0x021D8D40
	mov r1, #0xba
	lsl r1, r1, #2
	add r0, r0, r1
	ldr r3, _021D8D4C ; =FUN_0200D0E0
	mov r1, #0
	bx r3
	.align 2, 0
_021D8D4C: .word FUN_0200D0E0
	thumb_func_end MOD54_021D8D40

	thumb_func_start MOD54_021D8D50
MOD54_021D8D50: ; 0x021D8D50
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #0xcb
	lsl r0, r0, #2
	add r0, r5, r0
	str r0, [sp, #0x14]
	mov r0, #0xcf
	lsl r0, r0, #2
	mov r4, #0
	add r0, r5, r0
	str r4, [sp, #8]
	add r6, r5, #0
	mov r7, #0x1c
	str r0, [sp, #0x18]
_021D8D72:
	mov r0, #0xe3
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #3
	bhi _021D8E3E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8D88: ; jump table
	.short _021D8E3E - _021D8D88 - 2 ; case 0
	.short _021D8D90 - _021D8D88 - 2 ; case 1
	.short _021D8E3E - _021D8D88 - 2 ; case 2
	.short _021D8E06 - _021D8D88 - 2 ; case 3
_021D8D90:
	mov r0, #0xd9
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	cmp r0, #0
	bne _021D8D9E
	bl ErrorHandling
_021D8D9E:
	mov r0, #0xd9
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl PlayerProfile_GetTrainerGender
	str r0, [sp, #0xc]
	mov r0, #0xd9
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02023A28
	str r0, [sp, #0x10]
	bl FUN_02031190
	cmp r4, r0
	bne _021D8DD0
	mov r0, #0x8b
	ldr r1, [sp, #0xc]
	lsl r0, r0, #2
	lsl r1, r1, #1
	ldr r0, [r5, r0]
	add r1, #0x26
	bl FUN_02020130
	b _021D8DEC
_021D8DD0:
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x18]
	str r0, [sp]
	ldr r0, [sp, #0x14]
	ldr r3, [sp, #0x10]
	add r2, r4, #0
	bl MOD54_021D8EC8
	mov r0, #0x8b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r1, [sp, #4]
	bl FUN_02020130
_021D8DEC:
	mov r0, #0x8b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xe3
	mov r1, #2
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r0, #1
	str r0, [sp, #8]
	b _021D8E3E
_021D8E06:
	bl FUN_02031190
	cmp r4, r0
	bne _021D8E2A
	mov r0, #0xd9
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl PlayerProfile_GetTrainerGender
	add r1, r0, #0
	mov r0, #0x8b
	lsl r0, r0, #2
	lsl r1, r1, #1
	ldr r0, [r5, r0]
	add r1, #0x27
	bl FUN_02020130
	b _021D8E36
_021D8E2A:
	mov r0, #0x8b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r7, #0
	bl FUN_02020130
_021D8E36:
	mov r0, #0xe3
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
_021D8E3E:
	ldr r0, [sp, #4]
	add r4, r4, #1
	add r0, r0, #2
	add r5, r5, #4
	add r6, #8
	add r7, r7, #2
	str r0, [sp, #4]
	cmp r4, #5
	blt _021D8D72
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _021D8E5C
	ldr r0, _021D8E60 ; =0x0000064F
	bl FUN_020054C8
_021D8E5C:
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D8E60: .word 0x0000064F
	thumb_func_end MOD54_021D8D50

	thumb_func_start MOD54_021D8E64
MOD54_021D8E64: ; 0x021D8E64
	push {r3, r4, lr}
	sub sp, #4
	mov r2, #0xcf
	add r4, r0, #0
	lsl r2, r2, #2
	mov r0, #0x68
	mov r1, #8
	add r2, r4, r2
	mov r3, #0x33
	bl FUN_02006C08
	mov r2, #0xcd
	lsl r2, r2, #2
	str r0, [r4, r2]
	add r2, #0xc
	mov r0, #0x56
	mov r1, #7
	add r2, r4, r2
	mov r3, #0x33
	bl FUN_02006C08
	mov r3, #0xce
	lsl r3, r3, #2
	str r0, [r4, r3]
	mov r0, #0x33
	sub r3, #0xc
	str r0, [sp]
	mov r0, #0x68
	mov r1, #0x20
	mov r2, #1
	add r3, r4, r3
	bl FUN_02006BB0
	mov r1, #0xc9
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r3, #0x33
	str r3, [sp]
	lsl r3, r3, #4
	mov r0, #0x56
	mov r1, #9
	mov r2, #1
	add r3, r4, r3
	bl FUN_02006BB0
	mov r1, #0xca
	lsl r1, r1, #2
	str r0, [r4, r1]
	add sp, #4
	pop {r3, r4, pc}
	thumb_func_end MOD54_021D8E64

	thumb_func_start MOD54_021D8EC8
MOD54_021D8EC8: ; 0x021D8EC8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r6, r1, #0
	ldr r0, [sp, #0x18]
	add r1, r3, #0
	add r5, r2, #0
	bl FUN_020536C8
	add r4, r0, #0
	ldr r0, [r6, #4]
	mov r2, #6
	ldr r6, [r0, #0xc]
	ldr r0, [r7, #4]
	lsl r2, r2, #8
	ldr r1, [r0, #0x14]
	add r0, r4, #0
	mul r0, r2
	add r0, r1, r0
	ldr r1, _021D8F08 ; =0x021D9680
	lsl r3, r5, #1
	ldrh r1, [r1, r3]
	bl GX_LoadOBJ
	lsl r0, r4, #5
	add r1, r5, #7
	add r0, r6, r0
	lsl r1, r1, #5
	mov r2, #0x20
	bl GX_LoadOBJPltt
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8F08: .word MOD54_021D9680
	thumb_func_end MOD54_021D8EC8

	thumb_func_start MOD54_021D8F0C
MOD54_021D8F0C: ; 0x021D8F0C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xcd
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0xce
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0xc9
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0xca
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD54_021D8F0C

	thumb_func_start MOD54_021D8F3C
MOD54_021D8F3C: ; 0x021D8F3C
	mov r0, #1
	bx lr
	thumb_func_end MOD54_021D8F3C

	thumb_func_start MOD54_021D8F40
MOD54_021D8F40: ; 0x021D8F40
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02031190
	cmp r0, #0
	bne _021D8F8C
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _021D8F5E
	mov r0, #1
	bl FUN_02032B6C
	b _021D8F6E
_021D8F5E:
	bl FUN_02030F20
	add r0, r4, r0
	cmp r0, #5
	ble _021D8F6A
	mov r0, #5
_021D8F6A:
	bl FUN_02032B6C
_021D8F6E:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	ldr r0, _021D8F90 ; =0x00004A55
	bne _021D8F7E
	mov r1, #2
	strb r1, [r5, r0]
	pop {r3, r4, r5, pc}
_021D8F7E:
	cmp r4, #0
	bne _021D8F88
	mov r1, #1
	strb r1, [r5, r0]
	pop {r3, r4, r5, pc}
_021D8F88:
	mov r1, #0
	strb r1, [r5, r0]
_021D8F8C:
	pop {r3, r4, r5, pc}
	nop
_021D8F90: .word 0x00004A55
	thumb_func_end MOD54_021D8F40

	thumb_func_start MOD54_021D8F94
MOD54_021D8F94: ; 0x021D8F94
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r0, #0
	add r6, r1, #0
	bl MOD54_021D8C08
	add r5, r0, #0
	ldr r0, _021D9088 ; =0x00004A48
	ldr r1, [r4, r0]
	cmp r5, r1
	ble _021D8FBE
	mov r2, #1
	add r0, sp, #0
	strb r2, [r0]
	mov r0, #0x75
	add r1, sp, #0
	bl FUN_02030ADC
	mov r1, #1
	ldr r0, _021D908C ; =0x00004A4C
	b _021D8FC2
_021D8FBE:
	mov r1, #0
	add r0, r0, #4
_021D8FC2:
	str r1, [r4, r0]
	ldr r0, _021D9090 ; =0x00004A44
	ldr r0, [r4, r0]
	cmp r5, r0
	bne _021D8FD2
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D8FD2:
	cmp r5, #5
	bhi _021D9078
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8FE2: ; jump table
	.short _021D9078 - _021D8FE2 - 2 ; case 0
	.short _021D8FEE - _021D8FE2 - 2 ; case 1
	.short _021D9032 - _021D8FE2 - 2 ; case 2
	.short _021D9032 - _021D8FE2 - 2 ; case 3
	.short _021D9032 - _021D8FE2 - 2 ; case 4
	.short _021D906A - _021D8FE2 - 2 ; case 5
_021D8FEE:
	bl FUN_02030F20
	cmp r0, #1
	bgt _021D8FFE
	bl FUN_0202CB8C
	cmp r0, #1
	bls _021D9004
_021D8FFE:
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D9004:
	mov r0, #0xd1
	mov r1, #0x11
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	sub r1, #0x12
	bl MOD54_021D8F40
	mov r0, #0x32
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D902C
	mov r1, #0x33
	bl FUN_020021EC
	mov r0, #0x32
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
_021D902C:
	add sp, #4
	mov r0, #2
	pop {r3, r4, r5, r6, pc}
_021D9032:
	mov r0, #2
	bl FUN_02052B74
	ldr r0, _021D9090 ; =0x00004A44
	ldr r1, [r4, r0]
	cmp r5, r1
	bge _021D9078
	add r0, #0x11
	ldrsb r0, [r4, r0]
	cmp r0, #0
	beq _021D904E
	cmp r0, #1
	beq _021D9058
	b _021D9060
_021D904E:
	add r0, r4, #0
	add r1, r6, #0
	bl MOD54_021D8F40
	b _021D9060
_021D9058:
	add r0, r4, #0
	mov r1, #0
	bl MOD54_021D8F40
_021D9060:
	bl FUN_02030F20
	ldr r1, _021D9088 ; =0x00004A48
	str r0, [r4, r1]
	b _021D9078
_021D906A:
	mov r0, #9
	bl FUN_02052B74
	add r0, r4, #0
	add r1, r6, #0
	bl MOD54_021D8F40
_021D9078:
	bl MOD54_021D8C08
	ldr r1, _021D9090 ; =0x00004A44
	str r0, [r4, r1]
	mov r0, #1
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_021D9088: .word 0x00004A48
_021D908C: .word 0x00004A4C
_021D9090: .word 0x00004A44
	thumb_func_end MOD54_021D8F94

	thumb_func_start MOD54_021D9094
MOD54_021D9094: ; 0x021D9094
	mov r0, #0x2c
	bx lr
	thumb_func_end MOD54_021D9094

	thumb_func_start MOD54_021D9098
MOD54_021D9098: ; 0x021D9098
	add r0, #0x2c
	bx lr
	thumb_func_end MOD54_021D9098

	thumb_func_start MOD54_021D909C
MOD54_021D909C: ; 0x021D909C
	push {r4, r5, r6, r7}
	add r7, r0, #0
	add r6, r7, #0
	mov ip, r1
	mov r5, #5
	add r6, #0xdc
_021D90A8:
	add r4, r6, #0
	sub r4, #0x2c
	add r3, r6, #0
	mov r2, #5
_021D90B0:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D90B0
	ldr r0, [r4]
	sub r5, r5, #1
	sub r6, #0x2c
	str r0, [r3]
	cmp r5, #2
	bgt _021D90A8
	add r7, #0x58
	mov r3, #5
_021D90C8:
	mov r2, ip
	ldmia r2!, {r0, r1}
	mov ip, r2
	stmia r7!, {r0, r1}
	sub r3, r3, #1
	bne _021D90C8
	mov r0, ip
	ldr r0, [r0]
	str r0, [r7]
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
	thumb_func_end MOD54_021D909C

	thumb_func_start MOD54_021D90E0
MOD54_021D90E0: ; 0x021D90E0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #2
	blt _021D90EE
	cmp r5, #5
	ble _021D90F2
_021D90EE:
	bl ErrorHandling
_021D90F2:
	add r2, r5, #1
	cmp r2, #5
	bgt _021D911A
	mov r0, #0x2c
	mul r0, r2
	add r3, r4, r0
_021D90FE:
	add r6, r3, #0
	add r7, r3, #0
	sub r6, #0x2c
	mov r5, #5
_021D9106:
	ldmia r7!, {r0, r1}
	stmia r6!, {r0, r1}
	sub r5, r5, #1
	bne _021D9106
	ldr r0, [r7]
	add r2, r2, #1
	add r3, #0x2c
	str r0, [r6]
	cmp r2, #5
	ble _021D90FE
_021D911A:
	ldr r0, _021D9128 ; =0x0000FFFF
	add r1, r4, #0
	add r4, #0xdc
	add r1, #0xdc
	strh r0, [r4]
	strh r0, [r1, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D9128: .word 0x0000FFFF
	thumb_func_end MOD54_021D90E0

	thumb_func_start MOD54_021D912C
MOD54_021D912C: ; 0x021D912C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp]
	add r5, r2, #0
	str r1, [sp, #4]
	str r3, [sp, #8]
	cmp r0, #0
	ble _021D91A6
	mov r7, #0x2c
_021D9144:
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	ldr r6, [r0]
	ldr r0, [sp, #4]
	cmp r1, r0
	beq _021D9194
	cmp r6, #0
	beq _021D9194
	add r0, r6, #0
	bl FUN_0202888C
	cmp r0, #1
	beq _021D9194
	add r0, r6, #0
	add r1, r5, #0
	bl FUN_020288AC
	cmp r0, #0
	bne _021D9194
	mov r4, #0
_021D916C:
	add r1, r4, #2
	add r2, r1, #0
	mul r2, r7
	add r0, r6, #0
	add r1, r5, r2
	bl FUN_020288AC
	cmp r0, #0
	beq _021D9186
	add r0, r5, #0
	add r1, r4, #2
	bl MOD54_021D90E0
_021D9186:
	add r4, r4, #1
	cmp r4, #4
	blt _021D916C
	add r0, r5, #0
	add r1, r6, #0
	bl MOD54_021D909C
_021D9194:
	ldr r0, [sp, #8]
	add r0, r0, #4
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	add r1, r0, #1
	ldr r0, [sp]
	str r1, [sp, #0xc]
	cmp r1, r0
	blt _021D9144
_021D91A6:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD54_021D912C

	thumb_func_start MOD54_021D91AC
MOD54_021D91AC: ; 0x021D91AC
	mov r0, #0x12
	lsl r0, r0, #4
	bx lr
	.align 2, 0
	thumb_func_end MOD54_021D91AC

	thumb_func_start MOD54_021D91B4
MOD54_021D91B4: ; 0x021D91B4
	mov r0, #0x12
	lsl r0, r0, #4
	bx lr
	.align 2, 0
	thumb_func_end MOD54_021D91B4

	thumb_func_start MOD54_021D91BC
MOD54_021D91BC: ; 0x021D91BC
	mov r0, #0x12
	lsl r0, r0, #4
	bx lr
	.align 2, 0
	thumb_func_end MOD54_021D91BC

	thumb_func_start MOD54_021D91C4
MOD54_021D91C4: ; 0x021D91C4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r3, [sp, #4]
	add r5, r1, #0
	str r2, [sp]
	bl Sav2_PlayerData_GetProfileAddr
	add r4, r0, #0
	ldr r0, [sp, #4]
	mov r7, #0
	cmp r0, #0
	ble _021D9234
_021D91DC:
	mov r0, #0
	add r1, r5, #0
	mov r2, #0x48
	bl MIi_CpuClearFast
	add r0, r4, #0
	bl PlayerProfile_GetTrainerID
	str r0, [r5]
	add r0, r4, #0
	bl PlayerProfile_GetTrainerGender
	strb r0, [r5, #4]
	mov r0, #GAME_VERSION
	strb r0, [r5, #5]
	mov r0, #2
	strb r0, [r5, #6]
	add r0, r4, #0
	bl PlayerProfile_GetNamePtr
	add r1, r0, #0
	add r0, r5, #0
	add r0, #8
	mov r2, #8
	bl CopyU16StringArrayN
	add r3, r5, #0
	ldr r6, [sp]
	add r3, #0x18
	mov r2, #6
_021D9218:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D9218
	mov r0, #0
	strb r0, [r5, #0x19]
	ldr r0, [sp]
	add r7, r7, #1
	add r0, #0x30
	str r0, [sp]
	ldr r0, [sp, #4]
	add r5, #0x48
	cmp r7, r0
	blt _021D91DC
_021D9234:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD54_021D91C4

	thumb_func_start MOD54_021D9238
MOD54_021D9238: ; 0x021D9238
	push {r3, r4, r5, r6, r7, lr}
	add r4, r2, #0
	add r5, r0, #0
	add r0, r1, #0
	add r1, r4, #0
	bl AllocFromHeapAtEnd
	add r7, r0, #0
	add r0, r5, #0
	bl FUN_02022504
	add r6, r0, #0
	add r0, r5, #0
	bl MOD54_021D91AC
	cmp r4, r0
	beq _021D925E
	bl ErrorHandling
_021D925E:
	mov r2, #0x63
	lsl r2, r2, #2
	add r0, r5, #0
	add r1, r7, #0
	add r2, r6, r2
	mov r3, #4
	bl MOD54_021D91C4
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD54_021D9238

	thumb_func_start MOD54_021D9274
MOD54_021D9274: ; 0x021D9274
	push {r3, r4, r5, r6, r7, lr}
	add r4, r2, #0
	add r5, r0, #0
	add r0, r1, #0
	add r1, r4, #0
	bl AllocFromHeapAtEnd
	add r7, r0, #0
	add r0, r5, #0
	bl FUN_02022504
	add r6, r0, #0
	add r0, r5, #0
	bl MOD54_021D91B4
	cmp r4, r0
	beq _021D929A
	bl ErrorHandling
_021D929A:
	add r6, #0xc
	add r0, r5, #0
	add r1, r7, #0
	add r2, r6, #0
	mov r3, #4
	bl MOD54_021D91C4
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD54_021D9274

	thumb_func_start MOD54_021D92AC
MOD54_021D92AC: ; 0x021D92AC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r2, #0
	add r5, r0, #0
	add r0, r1, #0
	add r1, r4, #0
	bl AllocFromHeapAtEnd
	add r7, r0, #0
	add r0, r5, #0
	bl FUN_02022504
	add r6, r0, #0
	add r0, r5, #0
	bl MOD54_021D91BC
	cmp r4, r0
	beq _021D92D2
	bl ErrorHandling
_021D92D2:
	add r6, #0xcc
	add r0, r5, #0
	add r1, r7, #0
	add r2, r6, #0
	mov r3, #4
	bl MOD54_021D91C4
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD54_021D92AC

	thumb_func_start MOD54_021D92E4
MOD54_021D92E4: ; 0x021D92E4
	push {r4, r5}
	ldrb r3, [r2, #0x18]
	cmp r3, #0
	bne _021D92F2
	mov r0, #0
	pop {r4, r5}
	bx lr
_021D92F2:
	mov r4, #0
	cmp r1, #0
	ble _021D931E
	add r5, r0, #0
_021D92FA:
	ldrb r3, [r5, #0x18]
	cmp r3, #0
	bne _021D9316
	mov r1, #0x48
	mul r1, r4
	add r4, r0, r1
	mov r3, #9
_021D9308:
	ldmia r2!, {r0, r1}
	stmia r4!, {r0, r1}
	sub r3, r3, #1
	bne _021D9308
	mov r0, #1
	pop {r4, r5}
	bx lr
_021D9316:
	add r4, r4, #1
	add r5, #0x48
	cmp r4, r1
	blt _021D92FA
_021D931E:
	mov r5, #0
	cmp r1, #0
	ble _021D934A
	add r4, r0, #0
_021D9326:
	ldrb r3, [r4, #0x19]
	cmp r3, #3
	blo _021D9342
	mov r1, #0x48
	mul r1, r5
	add r4, r0, r1
	mov r3, #9
_021D9334:
	ldmia r2!, {r0, r1}
	stmia r4!, {r0, r1}
	sub r3, r3, #1
	bne _021D9334
	mov r0, #1
	pop {r4, r5}
	bx lr
_021D9342:
	add r5, r5, #1
	add r4, #0x48
	cmp r5, r1
	blt _021D9326
_021D934A:
	mov r0, #0
	pop {r4, r5}
	bx lr
	thumb_func_end MOD54_021D92E4

	thumb_func_start MOD54_021D9350
MOD54_021D9350: ; 0x021D9350
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r0, [sp]
	str r1, [sp, #4]
	add r7, r2, #0
	add r0, sp, #0x18
	mov r1, #0
	mov r2, #0x10
	str r3, [sp, #8]
	ldr r5, [sp, #0x40]
	bl MI_CpuFill8
	mov r4, #0
	add r6, r4, #0
	cmp r7, #0
	ble _021D93D8
	str r5, [sp, #0x10]
_021D9372:
	ldr r0, [sp, #0x10]
	ldr r0, [r0]
	cmp r0, #0
	beq _021D93CC
	mov r0, #0
	str r0, [sp, #0x14]
	str r0, [sp, #0xc]
	b _021D93C6
_021D9382:
	add r0, r4, #1
	add r1, r7, #0
	bl _s32_div_f
	add r4, r1, #0
_021D938C:
	lsl r2, r4, #2
	ldr r0, [r5, r2]
	cmp r0, #0
	beq _021D9382
	cmp r4, r6
	beq _021D9382
	add r0, sp, #0x18
	ldrb r0, [r0, r4]
	cmp r0, #4
	beq _021D9382
	add r1, r0, #1
	add r0, sp, #0x18
	strb r1, [r0, r4]
	ldr r0, [sp, #8]
	cmp r4, r0
	beq _021D93BA
	ldr r3, [r5, r2]
	ldr r2, [sp, #0xc]
	ldr r0, [sp]
	ldr r1, [sp, #4]
	add r2, r3, r2
	bl MOD54_021D92E4
_021D93BA:
	ldr r0, [sp, #0xc]
	add r0, #0x48
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x14]
	add r0, r0, #1
	str r0, [sp, #0x14]
_021D93C6:
	ldr r0, [sp, #0x14]
	cmp r0, #4
	blt _021D938C
_021D93CC:
	ldr r0, [sp, #0x10]
	add r6, r6, #1
	add r0, r0, #4
	str r0, [sp, #0x10]
	cmp r6, r7
	blt _021D9372
_021D93D8:
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD54_021D9350

	thumb_func_start MOD54_021D93DC
MOD54_021D93DC: ; 0x021D93DC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r1, #0x93
	add r4, r2, #0
	lsl r1, r1, #2
	str r3, [sp]
	add r0, r0, r1
	mov r1, #0x10
	add r2, r5, #0
	add r3, r4, #0
	bl MOD54_021D9350
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD54_021D93DC

	thumb_func_start MOD54_021D93F8
MOD54_021D93F8: ; 0x021D93F8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, _021D9410 ; =0x000006CC
	add r4, r2, #0
	str r3, [sp]
	add r0, r0, r1
	mov r1, #8
	add r2, r5, #0
	add r3, r4, #0
	bl MOD54_021D9350
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D9410: .word 0x000006CC
	thumb_func_end MOD54_021D93F8

	thumb_func_start MOD54_021D9414
MOD54_021D9414: ; 0x021D9414
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, _021D942C ; =0x0000090C
	add r4, r2, #0
	str r3, [sp]
	add r0, r0, r1
	mov r1, #8
	add r2, r5, #0
	add r3, r4, #0
	bl MOD54_021D9350
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D942C: .word 0x0000090C
	thumb_func_end MOD54_021D9414

	thumb_func_start MOD54_021D9430
MOD54_021D9430: ; 0x021D9430
	push {r3, lr}
	bl FUN_0202881C
	bl MOD54_021D9094
	pop {r3, pc}
	thumb_func_end MOD54_021D9430

	thumb_func_start MOD54_021D943C
MOD54_021D943C: ; 0x021D943C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r2, #0
	bl FUN_0202881C
	add r6, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	add r0, r6, #0
	bl MOD54_021D9098
	add r1, r4, #0
	add r2, r5, #0
	bl MIi_CpuCopyFast
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD54_021D943C

	thumb_func_start MOD54_021D9464
MOD54_021D9464: ; 0x021D9464
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FUN_0202881C
	add r2, r0, #0
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	ldr r3, [r4, #0x10]
	bl MOD54_021D912C
	pop {r4, pc}
	thumb_func_end MOD54_021D9464

	thumb_func_start MOD54_021D947C
MOD54_021D947C: ; 0x021D947C
	push {r3, lr}
	bl FUN_02027E24
	bl FUN_02026FE0
	pop {r3, pc}
	thumb_func_end MOD54_021D947C

	thumb_func_start MOD54_021D9488
MOD54_021D9488: ; 0x021D9488
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r2, #0
	bl FUN_02027E24
	add r6, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	add r0, r6, #0
	mov r1, #0
	bl FUN_02027008
	add r1, r4, #0
	add r2, r5, #0
	bl MIi_CpuCopyFast
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD54_021D9488

	thumb_func_start MOD54_021D94B4
MOD54_021D94B4: ; 0x021D94B4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FUN_02027E24
	add r2, r0, #0
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #0x18
	ldr r3, [r4, #0x10]
	lsr r0, r0, #0x18
	bl FUN_02027D7C
	pop {r4, pc}
	thumb_func_end MOD54_021D94B4

	thumb_func_start MOD54_021D94D0
MOD54_021D94D0: ; 0x021D94D0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FUN_02022504
	ldr r1, [r4, #8]
	ldr r2, [r4, #0xc]
	ldr r3, [r4, #0x10]
	bl MOD54_021D93DC
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD54_021D94D0

	thumb_func_start MOD54_021D94E8
MOD54_021D94E8: ; 0x021D94E8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FUN_02022504
	ldr r1, [r4, #8]
	ldr r2, [r4, #0xc]
	ldr r3, [r4, #0x10]
	bl MOD54_021D93F8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD54_021D94E8

	thumb_func_start MOD54_021D9500
MOD54_021D9500: ; 0x021D9500
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FUN_02022504
	ldr r1, [r4, #8]
	ldr r2, [r4, #0xc]
	ldr r3, [r4, #0x10]
	bl MOD54_021D9414
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD54_021D9500

	thumb_func_start MOD54_021D9518
MOD54_021D9518: ; 0x021D9518
	ldr r3, _021D951C ; =FUN_0202B9EC
	bx r3
	.align 2, 0
_021D951C: .word FUN_0202B9EC
	thumb_func_end MOD54_021D9518

	thumb_func_start MOD54_021D9520
MOD54_021D9520: ; 0x021D9520
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FUN_0202B8E4
	ldr r0, [r4]
	str r0, [sp]
	ldr r2, [r4, #8]
	ldr r0, [r4, #4]
	lsl r2, r2, #0x18
	ldr r1, [r4, #0xc]
	ldr r3, [r4, #0x10]
	lsr r2, r2, #0x18
	bl FUN_0202BCF4
	add sp, #4
	pop {r3, r4, pc}
	thumb_func_end MOD54_021D9520

	thumb_func_start MOD54_021D9544
MOD54_021D9544: ; 0x021D9544
	push {r4, r5, r6, lr}
	add r5, r2, #0
	add r6, r0, #0
	add r0, r1, #0
	add r1, r5, #0
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	mov r1, #0
	add r2, r5, #0
	bl MI_CpuFill8
	add r0, r6, #0
	mov r1, #0
	add r2, r4, #0
	bl FUN_02066840
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD54_021D9544

	thumb_func_start MOD54_021D956C
MOD54_021D956C: ; 0x021D956C
	bx lr
	.align 2, 0
	thumb_func_end MOD54_021D956C

	thumb_func_start MOD54_021D9570
MOD54_021D9570: ; 0x021D9570
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r0, [sp]
	mov r0, #0
	ldr r6, _021D95C4 ; =0x00000BB8
	ldr r5, _021D95C8 ; =0x021D9780
	str r1, [sp, #4]
	str r0, [sp, #8]
_021D9580:
	ldr r0, [sp]
	ldr r1, [r5]
	blx r1
	add r4, r0, #0
	ldr r0, [sp]
	ldr r3, [r5, #4]
	mov r1, #0x33
	add r2, r4, #0
	blx r3
	add r7, r0, #0
	cmp r6, r4
	bhi _021D959C
	bl ErrorHandling
_021D959C:
	ldr r1, [sp, #4]
	add r0, r7, #0
	add r2, r4, #0
	bl MIi_CpuCopyFast
	add r0, r7, #0
	bl FreeToHeap
	ldr r0, [sp, #4]
	sub r6, r6, r4
	add r0, r0, r4
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	add r5, #0xc
	add r0, r0, #1
	str r0, [sp, #8]
	cmp r0, #7
	blt _021D9580
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D95C4: .word 0x00000BB8
_021D95C8: .word MOD54_021D9780
	thumb_func_end MOD54_021D9570

	thumb_func_start MOD54_021D95CC
MOD54_021D95CC: ; 0x021D95CC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	str r0, [sp]
	ldr r0, _021D9670 ; =0x00000BB8
	str r1, [sp, #4]
	str r0, [sp, #0x10]
	mov r0, #0x33
	str r0, [sp, #0x2c]
	ldr r0, [sp]
	mov r7, #0
	str r0, [sp, #0x30]
	bl FUN_02031190
	str r0, [sp, #0x38]
	mov r0, #5
	str r0, [sp, #0x34]
	add r0, sp, #0x18
	str r0, [sp, #0x3c]
	add r0, r7, #0
	str r0, [sp, #0xc]
	ldr r0, _021D9674 ; =0x021D9780
	str r0, [sp, #8]
_021D95F8:
	ldr r1, [sp, #8]
	ldr r0, [sp]
	ldr r1, [r1]
	blx r1
	ldr r1, [sp, #0x10]
	str r0, [sp, #0x14]
	cmp r1, r0
	bhi _021D960C
	bl ErrorHandling
_021D960C:
	mov r6, #0
	ldr r4, [sp, #4]
	add r5, r6, #0
_021D9612:
	add r0, r6, #0
	bl FUN_0202DFA4
	cmp r0, #0
	beq _021D9624
	ldr r0, [sp, #0x3c]
	add r1, r4, r7
	str r1, [r0, r5]
	b _021D962A
_021D9624:
	ldr r1, [sp, #0x3c]
	mov r0, #0
	str r0, [r1, r5]
_021D962A:
	mov r0, #0x2f
	lsl r0, r0, #6
	add r6, r6, #1
	add r4, r4, r0
	add r5, r5, #4
	cmp r6, #5
	blt _021D9612
	ldr r1, [sp, #8]
	add r0, sp, #0x2c
	ldr r1, [r1, #8]
	blx r1
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x10]
	add r7, r7, r0
	sub r0, r1, r0
	str r0, [sp, #0x10]
	ldr r0, [sp, #8]
	add r0, #0xc
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	add r0, r0, #1
	str r0, [sp, #0xc]
	cmp r0, #7
	blo _021D95F8
	ldr r0, [sp]
	bl FUN_02022504
	add r4, r0, #0
	bl FUN_0202B390
	add r0, r4, #0
	bl FUN_0202B3F8
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D9670: .word 0x00000BB8
_021D9674: .word MOD54_021D9780
	thumb_func_end MOD54_021D95CC

	.rodata
	.global MOD54_021D9678
MOD54_021D9678: ; 0x021D9678
	.byte 0x00, 0x17, 0x0D, 0x07, 0x04, 0x0D, 0x78, 0x01

	.global MOD54_021D9680
MOD54_021D9680: ; 0x021D9680
	.byte 0xA0, 0x01, 0xA0, 0x07, 0xA0, 0x0D, 0xA0, 0x13, 0xA0, 0x19

	.global MOD54_021D968A
MOD54_021D968A: ; 0x021D968A
	.byte 0x08

	.global MOD54_021D968B
MOD54_021D968B: ; 0x021D968B
	.byte 0x02, 0x08, 0x03, 0x08, 0x04, 0x18, 0x00, 0x00, 0xFF

	.global MOD54_021D9694
MOD54_021D9694: ; 0x021D9694
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD54_021D96A4
MOD54_021D96A4: ; 0x021D96A4
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00

	.global MOD54_021D96B4
MOD54_021D96B4: ; 0x021D96B4
	.byte 0xCC, 0x00, 0x54, 0x00, 0xCC, 0x00, 0x35, 0x00, 0xE9, 0x00, 0x48, 0x00, 0xDF, 0x00, 0x67, 0x00
	.byte 0xB8, 0x00, 0x67, 0x00, 0xAE, 0x00, 0x48, 0x00

	.global MOD54_021D96CC
MOD54_021D96CC: ; 0x021D96CC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1B, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD54_021D96E8
MOD54_021D96E8: ; 0x021D96E8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD54_021D9704
MOD54_021D9704: ; 0x021D9704
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD54_021D9720
MOD54_021D9720: ; 0x021D9720
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD54_021D973C
MOD54_021D973C: ; 0x021D973C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD54_021D9758
MOD54_021D9758: ; 0x021D9758
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD54_021D9780
MOD54_021D9780: ; 0x021D9780
	.word MOD54_021D9430, MOD54_021D943C, MOD54_021D9464, MOD54_021D947C
	.word MOD54_021D9488, MOD54_021D94B4, MOD54_021D91B4, MOD54_021D9274
	.word MOD54_021D94D0, MOD54_021D91BC, MOD54_021D92AC, MOD54_021D94E8
	.word MOD54_021D91AC, MOD54_021D9238, MOD54_021D9500, FUN_0202B934
	.word MOD54_021D9518, MOD54_021D9520, FUN_0202A1E0, MOD54_021D9544
	.word MOD54_021D956C

	.data
	.global MOD54_021D97E0
MOD54_021D97E0: ; 0x021D97E0
	.word MOD54_021D7F0C, MOD54_021D80A4, MOD54_021D80F0, MOD54_021D7F44
	.word MOD54_021D8120, MOD54_021D8150, MOD54_021D8280, MOD54_021D8298
	.word MOD54_021D8320, MOD54_021D85A4, MOD54_021D85C4, MOD54_021D8600
	.word MOD54_021D8630, MOD54_021D86DC, MOD54_021D872C, MOD54_021D8750
	.word MOD54_021D8770, MOD54_021D87B0, MOD54_021D87D0, MOD54_021D87F4
	.word MOD54_021D884C, MOD54_021D8888, MOD54_021D8340, MOD54_021D8370
	.word MOD54_021D8420, MOD54_021D847C, MOD54_021D84AC, MOD54_021D84D4
	.word MOD54_021D8518, MOD54_021D8588, MOD54_021D80CC, 0x00000000

	.bss
