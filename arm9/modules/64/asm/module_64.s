	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD64_021D74E0
MOD64_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, lr}
	sub sp, #0x10
	mov r2, #1
	add r4, r0, #0
	mov r0, #3
	mov r1, #0x2f
	lsl r2, r2, #0x12
	bl FUN_0201681C
	ldr r1, _021D7630 ; =0x000006B4
	add r0, r4, #0
	mov r2, #0x2f
	bl OverlayManager_CreateAndGetData
	add r5, r0, #0
	bne _021D7504
	bl ErrorHandling
_021D7504:
	ldr r2, _021D7630 ; =0x000006B4
	add r0, r5, #0
	mov r1, #0
	bl memset
	mov r0, #0x25
	lsl r0, r0, #4
	add r0, r5, r0
	mov r1, #0x2f
	mov r2, #0x20
	bl FUN_02016B20
	add r0, r4, #0
	bl OverlayManager_GetField18
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FUN_02025084
	ldr r1, _021D7634 ; =0x000006A8
	str r0, [r5, r1]
	ldr r0, [r4, #4]
	bl FUN_02024FF4
	ldr r1, _021D7638 ; =0x000006AC
	str r0, [r5, r1]
	mov r0, #8
	mov r1, #0x2f
	bl FUN_0201C24C
	ldr r0, _021D763C ; =MOD64_021D77A4
	add r1, r5, #0
	bl FUN_02015F10
	bl FUN_02015F1C
	bl FUN_0201CC08
	mov r0, #4
	bl FUN_0201CC24
	cmp r0, #1
	beq _021D755E
	bl ErrorHandling
_021D755E:
	add r0, r5, #0
	mov r1, #0x2f
	bl MOD64_021D7810
	mov r0, #0x2f
	bl FUN_02016B94
	add r1, r5, #0
	add r1, #0x94
	str r0, [r1]
	mov r1, #1
	mov r0, #0
	str r0, [sp, #4]
	add r0, sp, #0
	str r1, [sp]
	str r1, [sp, #8]
	str r1, [sp, #0xc]
	bl FUN_02016BBC
	add r0, r5, #0
	add r0, #0x94
	ldr r0, [r0]
	mov r1, #0x2f
	bl MOD64_021D7970
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	mov r0, #2
	mov r1, #0
	bl FUN_0201E6E4
	add r0, r5, #0
	mov r1, #0x2f
	bl MOD64_021D7A54
	add r0, r5, #0
	mov r1, #0x2f
	bl MOD64_021D87CC
	add r0, r5, #0
	mov r1, #0x2f
	bl MOD64_021D8EF4
	add r0, r5, #0
	mov r1, #0x2f
	bl MOD64_021D7B04
	add r0, r5, #0
	mov r1, #0x2f
	bl MOD64_021D7C34
	add r0, r5, #0
	mov r1, #0x2f
	bl MOD64_021D7C74
	add r0, r5, #0
	mov r1, #0x2f
	bl MOD64_021D7F60
	add r0, r5, #0
	mov r1, #0x2f
	bl MOD64_021D824C
	add r0, r5, #0
	bl MOD64_021D82CC
	add r0, r5, #0
	bl MOD64_021D8354
	mov r1, #6
	lsl r1, r1, #8
	add r0, r5, #0
	add r1, r5, r1
	mov r2, #0x2f
	bl MOD64_021D892C
	mov r1, #6
	lsl r1, r1, #8
	add r0, r5, #0
	add r1, r5, r1
	mov r2, #0x2f
	bl MOD64_021D89FC
	mov r0, #6
	lsl r0, r0, #8
	add r0, r5, r0
	bl MOD64_021D8AE0
	mov r0, #0x65
	lsl r0, r0, #4
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #0x2f
	bl MOD64_021D8B70
	mov r1, #0
	mov r0, #0x3c
	add r2, r1, #0
	bl FUN_0200433C
	mov r0, #1
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7630: .word 0x000006B4
_021D7634: .word 0x000006A8
_021D7638: .word 0x000006AC
_021D763C: .word MOD64_021D77A4
	thumb_func_end MOD64_021D74E0

	thumb_func_start MOD64_021D7640
MOD64_021D7640: ; 0x021D7640
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	bl OverlayManager_GetData
	ldr r2, _021D76F0 ; =0x000008C3
	add r1, sp, #0
	strh r2, [r1]
	ldr r1, [r4]
	add r6, r0, #0
	cmp r1, #4
	bhi _021D76E2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D7664: ; jump table
	.short _021D766E - _021D7664 - 2 ; case 0
	.short _021D7684 - _021D7664 - 2 ; case 1
	.short _021D76A0 - _021D7664 - 2 ; case 2
	.short _021D76BC - _021D7664 - 2 ; case 3
	.short _021D76C8 - _021D7664 - 2 ; case 4
_021D766E:
	bl MOD64_021D77C8
	add r0, sp, #0
	mov r1, #0
	mov r2, #2
	bl GX_LoadBGPltt
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D76E2
_021D7684:
	bl MOD64_021D7808
	cmp r0, #0
	beq _021D76E2
	mov r0, #0
	bl FUN_0200E388
	mov r0, #1
	bl FUN_0200E388
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D76E2
_021D76A0:
	mov r1, #0x2f
	bl MOD64_021D80A4
	add r5, r0, #0
	add r0, r6, #0
	mov r1, #0x2f
	bl MOD64_021D8100
	cmp r5, #1
	bne _021D76E2
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D76E2
_021D76BC:
	bl MOD64_021D77E8
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D76E2
_021D76C8:
	bl MOD64_021D7808
	cmp r0, #0
	beq _021D76E2
	mov r0, #0
	bl FUN_0200E388
	mov r0, #1
	bl FUN_0200E388
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D76E2:
	add r0, r6, #0
	bl MOD64_021D81D8
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_021D76F0: .word 0x000008C3
	thumb_func_end MOD64_021D7640

	thumb_func_start MOD64_021D76F4
MOD64_021D76F4: ; 0x021D76F4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r0, r5, #0
	bl OverlayManager_GetField18
	add r6, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	ldr r0, [r4, #0x54]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl MOD64_021D9044
	str r0, [r6]
	bl FUN_0201CD04
	cmp r0, #1
	beq _021D7726
	bl ErrorHandling
_021D7726:
	mov r0, #0x65
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD64_021D8C0C
	mov r0, #6
	lsl r0, r0, #8
	add r0, r4, r0
	bl MOD64_021D8A78
	mov r1, #6
	lsl r1, r1, #8
	add r0, r4, #0
	add r1, r4, r1
	bl MOD64_021D89B8
	mov r0, #6
	lsl r0, r0, #8
	add r0, r4, r0
	bl MOD64_021D8B44
	add r0, r4, #0
	bl MOD64_021D82BC
	add r0, r4, #0
	bl MOD64_021D8034
	add r0, r4, #0
	bl MOD64_021D7CE0
	add r0, r4, #0
	bl MOD64_021D7C08
	add r0, r4, #0
	bl MOD64_021D7C64
	add r0, r4, #0
	bl MOD64_021D7AEC
	add r0, r4, #0
	bl MOD64_021D8FAC
	add r0, r4, #0
	add r0, #0x94
	ldr r0, [r0]
	bl MOD64_021D7A38
	add r4, #0x94
	ldr r0, [r4]
	bl FreeToHeap
	bl MOD64_021D7828
	bl FUN_0201C29C
	add r0, r5, #0
	bl OverlayManager_FreeData
	mov r0, #0x2f
	bl FUN_020168D0
	mov r0, #1
	pop {r4, r5, r6, pc}
	thumb_func_end MOD64_021D76F4

	thumb_func_start MOD64_021D77A4
MOD64_021D77A4: ; 0x021D77A4
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02009F80
	add r0, r4, #0
	add r0, #0x94
	ldr r0, [r0]
	bl FUN_0201AB60
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	bl FUN_020081C4
	bl FUN_0201C30C
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD64_021D77A4

	thumb_func_start MOD64_021D77C8
MOD64_021D77C8: ; 0x021D77C8
	push {lr}
	sub sp, #0xc
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x2f
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	add sp, #0xc
	pop {pc}
	.align 2, 0
	thumb_func_end MOD64_021D77C8

	thumb_func_start MOD64_021D77E8
MOD64_021D77E8: ; 0x021D77E8
	push {lr}
	sub sp, #0xc
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x2f
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	add sp, #0xc
	pop {pc}
	thumb_func_end MOD64_021D77E8

	thumb_func_start MOD64_021D7808
MOD64_021D7808: ; 0x021D7808
	ldr r3, _021D780C ; =FUN_0200E308
	bx r3
	.align 2, 0
_021D780C: .word FUN_0200E308
	thumb_func_end MOD64_021D7808

	thumb_func_start MOD64_021D7810
MOD64_021D7810: ; 0x021D7810
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	bl MOD64_021D783C
	add r0, r4, #0
	bl MOD64_021D785C
	add r0, r5, #0
	bl MOD64_021D78B4
	pop {r3, r4, r5, pc}
	thumb_func_end MOD64_021D7810

	thumb_func_start MOD64_021D7828
MOD64_021D7828: ; 0x021D7828
	push {r3, lr}
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	bl MOD64_021D7964
	pop {r3, pc}
	thumb_func_end MOD64_021D7828

	thumb_func_start MOD64_021D783C
MOD64_021D783C: ; 0x021D783C
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D7858 ; =0x021D90E8
	add r3, sp, #0
	mov r2, #5
_021D7846:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7846
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D7858: .word MOD64_021D90E8
	thumb_func_end MOD64_021D783C

	thumb_func_start MOD64_021D785C
MOD64_021D785C: ; 0x021D785C
	push {r4, r5, lr}
	sub sp, #0x24
	add r4, r0, #0
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x80
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	add r2, r0, #0
	str r4, [sp, #0x10]
	bl FUN_02009EAC
	ldr r5, _021D78AC ; =0x021D9074
	add r3, sp, #0x14
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	ldr r1, _021D78B0 ; =0x00200010
	mov r2, #0x10
	str r4, [sp, #0x20]
	bl FUN_0201D060
	mov r0, #0x20
	add r1, r4, #0
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x24
	pop {r4, r5, pc}
	nop
_021D78AC: .word MOD64_021D9074
_021D78B0: .word 0x00200010
	thumb_func_end MOD64_021D785C

	thumb_func_start MOD64_021D78B4
MOD64_021D78B4: ; 0x021D78B4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	bl FUN_020BB7F4
	bl G3X_InitMtxStack
	ldr r0, _021D7940 ; =0x04000060
	ldr r1, _021D7944 ; =0xFFFFCFFD
	ldrh r2, [r0]
	and r2, r1
	strh r2, [r0]
	ldrh r3, [r0]
	add r2, r1, #2
	and r3, r2
	mov r2, #0x10
	orr r2, r3
	strh r2, [r0]
	ldrh r3, [r0]
	ldr r2, _021D7948 ; =0x0000CFFB
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
	add r3, r4, #0
	and r2, r1
	mov r1, #0x20
	orr r1, r2
	strh r1, [r0]
	ldr r1, _021D794C ; =0x00001084
	ldr r0, _021D7950 ; =0x0000063C
	mov r2, #0
_021D7900:
	add r2, r2, #1
	strh r1, [r3, r0]
	add r3, r3, #2
	cmp r2, #8
	blt _021D7900
	ldr r0, _021D7950 ; =0x0000063C
	add r0, r4, r0
	bl G3X_SetEdgeColorTable
	mov r1, #0
	ldr r0, _021D7954 ; =0x000043FF
	ldr r2, _021D7958 ; =0x00007FFF
	mov r3, #0x3f
	str r1, [sp]
	bl G3X_SetClearColor
	ldr r1, _021D795C ; =0x04000540
	mov r0, #2
	str r0, [r1]
	ldr r0, _021D7960 ; =0xBFFF0000
	str r0, [r1, #0x40]
	mov r0, #1
	add r1, r0, #0
	bl FUN_020AEB70
	mov r0, #1
	lsl r0, r0, #0xe
	mov r1, #1
	bl FUN_020AEDF4
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021D7940: .word 0x04000060
_021D7944: .word 0xFFFFCFFD
_021D7948: .word 0x0000CFFB
_021D794C: .word 0x00001084
_021D7950: .word 0x0000063C
_021D7954: .word 0x000043FF
_021D7958: .word 0x00007FFF
_021D795C: .word 0x04000540
_021D7960: .word 0xBFFF0000
	thumb_func_end MOD64_021D78B4

	thumb_func_start MOD64_021D7964
MOD64_021D7964: ; 0x021D7964
	push {r3, lr}
	bl FUN_020AEAF4
	bl FUN_020AEC60
	pop {r3, pc}
	thumb_func_end MOD64_021D7964

	thumb_func_start MOD64_021D7970
MOD64_021D7970: ; 0x021D7970
	push {r4, r5, r6, r7, lr}
	sub sp, #0x54
	add r4, r1, #0
	ldr r1, _021D7A28 ; =0x04000008
	add r5, r0, #0
	ldrh r2, [r1]
	mov r0, #3
	mov r7, #1
	bic r2, r0
	add r0, r2, #0
	orr r0, r7
	add r3, sp, #0x38
	ldr r6, _021D7A2C ; =0x021D90B0
	strh r0, [r1]
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	add r1, r7, #0
	str r0, [r3]
	add r0, r5, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r7, #0
	mov r1, #0x20
	mov r2, #0
	add r3, r4, #0
	bl FUN_02017F18
	add r0, r5, #0
	add r1, r7, #0
	bl FUN_02018744
	ldr r6, _021D7A30 ; =0x021D9094
	add r3, sp, #0x1c
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	mov r1, #2
	str r0, [r3]
	add r0, r5, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	add r3, r4, #0
	bl FUN_02017F18
	add r0, r5, #0
	mov r1, #2
	bl FUN_02018744
	ldr r6, _021D7A34 ; =0x021D90CC
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	mov r1, #3
	str r0, [r3]
	add r0, r5, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #3
	mov r1, #0x20
	mov r2, #0
	add r3, r4, #0
	bl FUN_02017F18
	add r0, r5, #0
	mov r1, #3
	bl FUN_02018744
	add sp, #0x54
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D7A28: .word 0x04000008
_021D7A2C: .word MOD64_021D90B0
_021D7A30: .word MOD64_021D9094
_021D7A34: .word MOD64_021D90CC
	thumb_func_end MOD64_021D7970

	thumb_func_start MOD64_021D7A38
MOD64_021D7A38: ; 0x021D7A38
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #3
	bl FUN_020178A0
	pop {r4, pc}
	thumb_func_end MOD64_021D7A38

	thumb_func_start MOD64_021D7A54
MOD64_021D7A54: ; 0x021D7A54
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018FF4
	add r1, r5, #0
	add r1, #0x98
	str r0, [r1]
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	bl FUN_0201901C
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x17
	str r0, [sp, #4]
	mov r3, #4
	add r1, r5, #0
	str r3, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	mov r0, #0x1f
	str r0, [sp, #0x10]
	add r0, r5, #0
	add r0, #0x94
	add r1, #0x98
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #1
	bl FUN_02019064
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	mov r1, #0xf
	bl FUN_02019620
	ldr r0, _021D7AE8 ; =0x000006A8
	mov r1, #1
	ldr r0, [r5, r0]
	lsl r2, r1, #9
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	add r0, r5, #0
	str r4, [sp, #4]
	add r0, #0x94
	ldr r0, [r0]
	mov r3, #0
	bl FUN_0200CD68
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x52
	mov r1, #0x10
	mov r2, #0
	mov r3, #0x40
	str r4, [sp, #4]
	bl FUN_02006930
	add r5, #0x98
	mov r1, #0
	mov r2, #2
	ldr r0, [r5]
	lsl r2, r2, #8
	add r3, r1, #0
	bl FUN_0200D0BC
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_021D7AE8: .word 0x000006A8
	thumb_func_end MOD64_021D7A54

	thumb_func_start MOD64_021D7AEC
MOD64_021D7AEC: ; 0x021D7AEC
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x98
	ldr r0, [r0]
	bl FUN_02019178
	add r4, #0x98
	ldr r0, [r4]
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD64_021D7AEC

	thumb_func_start MOD64_021D7B04
MOD64_021D7B04: ; 0x021D7B04
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, r1, #0
	bl FUN_02006D98
	mov r1, #2
	lsl r1, r1, #8
	str r0, [r5, r1]
	ldr r3, _021D7BA4 ; =UNK_021064B8
	lsl r0, r1, #6
	mov r1, #0
	ldr r3, [r3]
	add r2, r1, #0
	blx r3
	ldr r3, _021D7BA8 ; =UNK_021064C0
	add r4, r0, #0
	ldr r3, [r3]
	mov r0, #0x80
	mov r1, #0
	mov r2, #1
	blx r3
	ldr r2, _021D7BAC ; =0x7FFF0000
	add r6, r0, #0
	mov r0, #2
	lsl r0, r0, #8
	and r2, r4
	lsl r1, r4, #0x10
	lsr r2, r2, #0x10
	ldr r0, [r5, r0]
	lsr r1, r1, #0xd
	lsl r2, r2, #4
	bl FUN_020081A8
	ldr r2, _021D7BB0 ; =0xFFFF0000
	mov r0, #2
	lsl r0, r0, #8
	and r2, r6
	lsl r1, r6, #0x10
	lsr r2, r2, #0x10
	ldr r0, [r5, r0]
	lsr r1, r1, #0xd
	lsl r2, r2, #3
	bl FUN_020081B4
	mov r2, #0x81
	lsl r2, r2, #2
	add r0, r5, r2
	add r1, r5, #0
	sub r2, #0x81
	bl MOD64_021D7BB4
	mov r2, #0x82
	lsl r2, r2, #2
	add r0, r5, r2
	add r1, r5, #0
	sub r2, #0x82
	bl MOD64_021D7BB4
	mov r2, #0x83
	lsl r2, r2, #2
	add r0, r5, r2
	add r1, r5, #0
	sub r2, #0x83
	bl MOD64_021D7BB4
	mov r6, #0x81
	mov r4, #0
	mov r7, #6
	lsl r6, r6, #2
_021D7B8E:
	ldr r0, [r5, r6]
	add r1, r7, #0
	mov r2, #1
	bl FUN_02007558
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _021D7B8E
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D7BA4: .word UNK_021064B8
_021D7BA8: .word UNK_021064C0
_021D7BAC: .word 0x7FFF0000
_021D7BB0: .word 0xFFFF0000
	thumb_func_end MOD64_021D7B04

	thumb_func_start MOD64_021D7BB4
MOD64_021D7BB4: ; 0x021D7BB4
	push {r4, r5, r6, lr}
	sub sp, #0x20
	add r6, r2, #0
	add r5, r0, #0
	lsl r0, r6, #0x10
	add r4, r1, #0
	lsr r0, r0, #0x10
	mov r1, #0
	bl GetGenderBySpeciesAndPersonality
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	lsl r1, r6, #0x10
	lsl r2, r2, #0x18
	str r0, [sp, #8]
	add r0, sp, #0x10
	lsr r1, r1, #0x10
	lsr r2, r2, #0x18
	mov r3, #2
	bl FUN_02068C00
	ldr r0, _021D7C04 ; =0x000003FF
	add r1, sp, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	mov r2, #0x80
	mov r3, #0x60
	bl FUN_020073A0
	str r0, [r5]
	add sp, #0x20
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D7C04: .word 0x000003FF
	thumb_func_end MOD64_021D7BB4

	thumb_func_start MOD64_021D7C08
MOD64_021D7C08: ; 0x021D7C08
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r6, #0x81
	mov r4, #0
	add r5, r7, #0
	lsl r6, r6, #2
_021D7C14:
	ldr r0, [r5, r6]
	cmp r0, #0
	beq _021D7C1E
	bl FUN_02007534
_021D7C1E:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _021D7C14
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r7, r0]
	bl FUN_020072E8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD64_021D7C08

	thumb_func_start MOD64_021D7C34
MOD64_021D7C34: ; 0x021D7C34
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r5, _021D7C5C ; =0x021D9084
	add r3, sp, #0
	add r4, r0, #0
	add r6, r1, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	str r6, [sp, #0xc]
	bl FUN_02013CD4
	ldr r1, _021D7C60 ; =0x0000064C
	str r0, [r4, r1]
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_021D7C5C: .word MOD64_021D9084
_021D7C60: .word 0x0000064C
	thumb_func_end MOD64_021D7C34

	thumb_func_start MOD64_021D7C64
MOD64_021D7C64: ; 0x021D7C64
	ldr r1, _021D7C6C ; =0x0000064C
	ldr r3, _021D7C70 ; =FUN_02013D18
	ldr r0, [r0, r1]
	bx r3
	.align 2, 0
_021D7C6C: .word 0x0000064C
_021D7C70: .word FUN_02013D18
	thumb_func_end MOD64_021D7C64

	thumb_func_start MOD64_021D7C74
MOD64_021D7C74: ; 0x021D7C74
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r1, r5, #0
	mov r0, #2
	add r1, #0xbc
	add r2, r4, #0
	bl FUN_02008C9C
	mov r1, #0x79
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #2
	mov r1, #0
	add r2, r4, #0
	bl FUN_02008DEC
	mov r1, #0x7a
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #2
	mov r1, #1
	add r2, r4, #0
	bl FUN_02008DEC
	mov r1, #0x7b
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #2
	add r1, r0, #0
	add r2, r4, #0
	bl FUN_02008DEC
	mov r1, #0x1f
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #2
	mov r1, #3
	add r2, r4, #0
	bl FUN_02008DEC
	mov r1, #0x7d
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD64_021D7C74

	thumb_func_start MOD64_021D7CE0
MOD64_021D7CE0: ; 0x021D7CE0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201FD58
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02008E2C
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02008E2C
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02008E2C
	mov r0, #0x7d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02008E2C
	pop {r4, pc}
	thumb_func_end MOD64_021D7CE0

	thumb_func_start MOD64_021D7D18
MOD64_021D7D18: ; 0x021D7D18
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r7, r2, #0
	add r5, r0, #0
	add r4, r3, #0
	mov r1, #0
	mov r2, #0x98
	bl memset
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD64_021D7D7C
	ldr r3, [sp, #0x18]
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	bl MOD64_021D7DC0
	mov r1, #1
	lsl r1, r1, #0xc
	add r0, r5, #0
	add r2, r1, #0
	add r3, r1, #0
	bl MOD64_021D7EE0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD64_021D7D18

	thumb_func_start MOD64_021D7D50
MOD64_021D7D50: ; 0x021D7D50
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r2, #0
	add r5, r0, #0
	mov r1, #0
	mov r2, #0x98
	bl memset
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD64_021D7D7C
	mov r1, #1
	lsl r1, r1, #0xc
	add r0, r5, #0
	add r2, r1, #0
	add r3, r1, #0
	bl MOD64_021D7EE0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD64_021D7D50

	thumb_func_start MOD64_021D7D7C
MOD64_021D7D7C: ; 0x021D7D7C
	push {r3, r4, lr}
	sub sp, #4
	add r3, r2, #0
	mov r2, #0
	add r4, r0, #0
	str r2, [sp]
	mov r0, #0x52
	bl FUN_02006C98
	str r0, [r4, #0x54]
	bl FUN_020BC13C
	str r0, [r4, #0x58]
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r0, r0, r1
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x54]
	bl FUN_020BC0FC
	str r0, [r4, #0x60]
	bl FUN_0201B3C4
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x60]
	bl FUN_0201B3A8
	ldr r1, [r4, #0x5c]
	add r0, r4, #0
	bl FUN_020B80B4
	add sp, #4
	pop {r3, r4, pc}
	thumb_func_end MOD64_021D7D7C

	thumb_func_start MOD64_021D7DC0
MOD64_021D7DC0: ; 0x021D7DC0
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r6, r2, #0
	mov r2, #0
	add r4, r0, #0
	add r5, r3, #0
	str r2, [sp]
	mov r0, #0x52
	add r3, r6, #0
	bl FUN_02006C98
	str r0, [r4, #0x64]
	mov r1, #0
	bl FUN_020BC4C8
	str r0, [r4, #0x68]
	ldr r1, [r4, #0x68]
	ldr r2, [r4, #0x5c]
	add r0, r5, #0
	bl FUN_020BB8D0
	str r0, [r4, #0x6c]
	ldr r1, [r4, #0x68]
	ldr r2, [r4, #0x5c]
	ldr r3, [r4, #0x60]
	bl FUN_020B8110
	ldr r1, [r4, #0x6c]
	add r0, r4, #0
	bl FUN_020B7EFC
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD64_021D7DC0

	thumb_func_start MOD64_021D7E04
MOD64_021D7E04: ; 0x021D7E04
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x54]
	add r4, r1, #0
	cmp r0, #0
	beq _021D7E14
	bl FreeToHeap
_021D7E14:
	ldr r0, [r5, #0x64]
	cmp r0, #0
	beq _021D7E28
	ldr r1, [r5, #0x6c]
	add r0, r4, #0
	bl thunk_FUN_020ae84c
	ldr r0, [r5, #0x64]
	bl FreeToHeap
_021D7E28:
	add r0, r5, #0
	mov r1, #0
	mov r2, #0x98
	bl memset
	pop {r3, r4, r5, pc}
	thumb_func_end MOD64_021D7E04

	thumb_func_start MOD64_021D7E34
MOD64_021D7E34: ; 0x021D7E34
	push {r4, lr}
	sub sp, #0x48
	add r4, r0, #0
	add r0, sp, #0x24
	bl MTX_Identity33_
	add r0, r4, #0
	add r0, #0x90
	ldrh r0, [r0]
	ldr r3, _021D7ECC ; =UNK_020FFA38
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0
	bl MTX_RotX33_
	add r1, sp, #0x24
	add r0, sp, #0
	add r2, r1, #0
	bl MTX_Concat33
	add r0, r4, #0
	add r0, #0x92
	ldrh r0, [r0]
	ldr r3, _021D7ECC ; =UNK_020FFA38
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0
	bl MTX_RotY33_
	add r1, sp, #0x24
	add r0, sp, #0
	add r2, r1, #0
	bl MTX_Concat33
	add r0, r4, #0
	add r0, #0x94
	ldrh r0, [r0]
	ldr r3, _021D7ECC ; =UNK_020FFA38
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0
	bl MTX_RotZ33_
	add r1, sp, #0x24
	add r0, sp, #0
	add r2, r1, #0
	bl MTX_Concat33
	ldr r0, [r4, #0x74]
	cmp r0, #0
	beq _021D7EC8
	add r1, r4, #0
	add r0, r4, #0
	add r4, #0x84
	add r1, #0x78
	add r2, sp, #0x24
	add r3, r4, #0
	bl FUN_0201B26C
_021D7EC8:
	add sp, #0x48
	pop {r4, pc}
	.align 2, 0
_021D7ECC: .word UNK_020FFA38
	thumb_func_end MOD64_021D7E34

	thumb_func_start MOD64_021D7ED0
MOD64_021D7ED0: ; 0x021D7ED0
	str r1, [r0, #0x74]
	bx lr
	thumb_func_end MOD64_021D7ED0

	thumb_func_start MOD64_021D7ED4
MOD64_021D7ED4: ; 0x021D7ED4
	str r1, [r0, #0x78]
	str r2, [r0, #0x7c]
	add r0, #0x80
	str r3, [r0]
	bx lr
	.align 2, 0
	thumb_func_end MOD64_021D7ED4

	thumb_func_start MOD64_021D7EE0
MOD64_021D7EE0: ; 0x021D7EE0
	push {r3, r4}
	add r4, r0, #0
	add r4, #0x84
	str r1, [r4]
	add r1, r0, #0
	add r1, #0x88
	str r2, [r1]
	add r0, #0x8c
	str r3, [r0]
	pop {r3, r4}
	bx lr
	.align 2, 0
	thumb_func_end MOD64_021D7EE0

	thumb_func_start MOD64_021D7EF8
MOD64_021D7EF8: ; 0x021D7EF8
	push {r3, r4}
	add r4, r0, #0
	add r4, #0x90
	strh r1, [r4]
	add r1, r0, #0
	add r1, #0x92
	strh r2, [r1]
	add r0, #0x94
	strh r3, [r0]
	pop {r3, r4}
	bx lr
	.align 2, 0
	thumb_func_end MOD64_021D7EF8

	thumb_func_start MOD64_021D7F10
MOD64_021D7F10: ; 0x021D7F10
	ldr r1, [r0, #0x6c]
	ldr r2, [r0, #0x70]
	ldr r1, [r1, #8]
	ldrh r1, [r1, #4]
	lsl r3, r1, #0xc
	mov r1, #1
	lsl r1, r1, #0xc
	add r1, r2, r1
	cmp r1, r3
	bge _021D7F2A
	str r1, [r0, #0x70]
	mov r2, #0
	b _021D7F2E
_021D7F2A:
	str r3, [r0, #0x70]
	mov r2, #1
_021D7F2E:
	ldr r1, [r0, #0x70]
	ldr r0, [r0, #0x6c]
	str r1, [r0]
	add r0, r2, #0
	bx lr
	thumb_func_end MOD64_021D7F10

	thumb_func_start MOD64_021D7F38
MOD64_021D7F38: ; 0x021D7F38
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	ldr r1, [r4, #0x70]
	lsl r0, r0, #0xc
	add r0, r1, r0
	ldr r1, [r4, #0x6c]
	ldr r1, [r1, #8]
	ldrh r1, [r1, #4]
	lsl r1, r1, #0xc
	bl _s32_div_f
	str r1, [r4, #0x70]
	ldr r0, [r4, #0x6c]
	str r1, [r0]
	pop {r4, pc}
	thumb_func_end MOD64_021D7F38

	thumb_func_start MOD64_021D7F58
MOD64_021D7F58: ; 0x021D7F58
	str r1, [r0, #0x70]
	ldr r0, [r0, #0x6c]
	str r1, [r0]
	bx lr
	thumb_func_end MOD64_021D7F58

	thumb_func_start MOD64_021D7F60
MOD64_021D7F60: ; 0x021D7F60
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	mov r0, #0x25
	add r7, r1, #0
	lsl r0, r0, #4
	add r1, r6, r0
	add r0, #0x10
	str r1, [sp]
	add r0, r6, r0
	mov r1, #1
	mov r2, #0
	add r3, r7, #0
	bl MOD64_021D7D18
	mov r0, #0x26
	lsl r0, r0, #4
	add r0, r6, r0
	mov r1, #1
	bl MOD64_021D7ED0
	mov r0, #0xbe
	lsl r0, r0, #2
	add r0, r6, r0
	mov r1, #8
	add r2, r7, #0
	bl MOD64_021D7D50
	mov r0, #0xbe
	lsl r0, r0, #2
	add r0, r6, r0
	mov r1, #0
	bl MOD64_021D7ED0
	mov r0, #0x26
	lsl r0, r0, #4
	add r1, r6, r0
	lsr r0, r0, #1
	add r5, r1, r0
	mov r0, #0x25
	lsl r0, r0, #4
	add r0, r6, r0
	mov r4, #2
	str r0, [sp, #4]
_021D7FB8:
	sub r0, r4, #2
	lsl r2, r0, #1
	ldr r0, [sp, #4]
	add r1, r2, #3
	str r0, [sp]
	add r0, r5, #0
	add r2, r2, #2
	add r3, r7, #0
	bl MOD64_021D7D18
	add r0, r5, #0
	mov r1, #0
	bl MOD64_021D7ED0
	add r4, r4, #1
	add r5, #0x98
	cmp r4, #4
	ble _021D7FB8
	ldr r0, _021D8028 ; =0x00000558
	mov r1, #9
	add r0, r6, r0
	add r2, r7, #0
	bl MOD64_021D7D50
	ldr r0, _021D8028 ; =0x00000558
	mov r1, #1
	add r0, r6, r0
	bl MOD64_021D7ED0
	ldr r0, _021D8028 ; =0x00000558
	mov r3, #0xa
	ldr r2, _021D802C ; =0xFFFE4000
	add r0, r6, r0
	mov r1, #0
	lsl r3, r3, #0xe
	bl MOD64_021D7ED4
	ldr r0, _021D8028 ; =0x00000558
	mov r1, #0xe
	lsl r1, r1, #0xa
	mov r2, #1
	add r0, r6, r0
	lsl r2, r2, #0xc
	add r3, r1, #0
	bl MOD64_021D7EE0
	ldr r0, _021D8028 ; =0x00000558
	mov r1, #0
	ldr r2, _021D8030 ; =0x00007FFF
	add r0, r6, r0
	add r3, r1, #0
	bl MOD64_021D7EF8
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8028: .word 0x00000558
_021D802C: .word 0xFFFE4000
_021D8030: .word 0x00007FFF
	thumb_func_end MOD64_021D7F60

	thumb_func_start MOD64_021D8034
MOD64_021D8034: ; 0x021D8034
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x26
	lsl r0, r0, #4
	add r7, r0, #0
	mov r4, #0
	add r5, r6, r0
	sub r7, #0x10
_021D8044:
	add r0, r5, #0
	add r1, r6, r7
	bl MOD64_021D7E04
	add r4, r4, #1
	add r5, #0x98
	cmp r4, #6
	blt _021D8044
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD64_021D8034

	thumb_func_start MOD64_021D8058
MOD64_021D8058: ; 0x021D8058
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0
	ldr r2, _021D809C ; =0xFFFFF000
	add r1, r0, #0
	add r3, r0, #0
	bl FUN_020B8418
	ldr r1, _021D80A0 ; =0x00007FFF
	mov r0, #0
	bl FUN_020B8404
	ldr r0, _021D80A0 ; =0x00007FFF
	mov r2, #0
	add r1, r0, #0
	bl FUN_020B83E0
	ldr r0, _021D80A0 ; =0x00007FFF
	mov r2, #0
	add r1, r0, #0
	bl FUN_020B83BC
	mov r0, #0x26
	lsl r0, r0, #4
	mov r4, #0
	add r5, r5, r0
_021D808C:
	add r0, r5, #0
	bl MOD64_021D7E34
	add r4, r4, #1
	add r5, #0x98
	cmp r4, #6
	blt _021D808C
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D809C: .word 0xFFFFF000
_021D80A0: .word 0x00007FFF
	thumb_func_end MOD64_021D8058

	thumb_func_start MOD64_021D80A4
MOD64_021D80A4: ; 0x021D80A4
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #8]
	cmp r1, #1
	bne _021D80B2
	mov r0, #0
	pop {r4, pc}
_021D80B2:
	bl MOD64_021D83D0
	cmp r0, #5
	bhi _021D80F4
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D80C6: ; jump table
	.short _021D80F4 - _021D80C6 - 2 ; case 0
	.short _021D80F4 - _021D80C6 - 2 ; case 1
	.short _021D80F4 - _021D80C6 - 2 ; case 2
	.short _021D80D2 - _021D80C6 - 2 ; case 3
	.short _021D80F4 - _021D80C6 - 2 ; case 4
	.short _021D80F0 - _021D80C6 - 2 ; case 5
_021D80D2:
	add r0, r4, #0
	bl MOD64_021D8384
	ldr r0, _021D80F8 ; =gMain
	mov r1, #1
	ldr r0, [r0, #0x48]
	tst r0, r1
	beq _021D80F4
	add r0, r4, #0
	bl MOD64_021D83C4
	ldr r0, _021D80FC ; =0x000005DC
	bl FUN_020054C8
	b _021D80F4
_021D80F0:
	mov r0, #1
	pop {r4, pc}
_021D80F4:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D80F8: .word gMain
_021D80FC: .word 0x000005DC
	thumb_func_end MOD64_021D80A4

	thumb_func_start MOD64_021D8100
MOD64_021D8100: ; 0x021D8100
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r5, r1, #0
	bl MOD64_021D83D0
	cmp r0, #5
	bhi _021D81CA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D811A: ; jump table
	.short _021D8126 - _021D811A - 2 ; case 0
	.short _021D8146 - _021D811A - 2 ; case 1
	.short _021D815E - _021D811A - 2 ; case 2
	.short _021D81B0 - _021D811A - 2 ; case 3
	.short _021D81BA - _021D811A - 2 ; case 4
	.short _021D81C4 - _021D811A - 2 ; case 5
_021D8126:
	mov r1, #1
	str r1, [r4, #8]
	mov r0, #0x24
	str r0, [r4, #0xc]
	add r0, r4, #0
	bl MOD64_021D83C4
	mov r0, #6
	str r0, [sp]
	ldr r0, _021D81CC ; =0x04000050
	mov r1, #8
	mov r2, #0x15
	mov r3, #0xa
	bl G2x_SetBlendAlpha_
	pop {r3, r4, r5, pc}
_021D8146:
	ldr r0, [r4, #0xc]
	sub r0, r0, #1
	str r0, [r4, #0xc]
	bpl _021D81CA
	add r0, r4, #0
	mov r1, #1
	bl MOD64_021D83C4
	ldr r0, _021D81D0 ; =0x000006CA
	bl FUN_020054C8
	pop {r3, r4, r5, pc}
_021D815E:
	mov r0, #0x26
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD64_021D7F10
	cmp r0, #0
	beq _021D81CA
	mov r0, #0x26
	lsl r0, r0, #4
	add r0, r4, r0
	mov r1, #0
	bl MOD64_021D7ED0
	mov r0, #0xbe
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #1
	bl MOD64_021D7ED0
	mov r0, #0x39
	lsl r0, r0, #4
	add r0, r4, r0
	mov r1, #1
	bl MOD64_021D7ED0
	ldr r0, _021D81D4 ; =0x00000428
	mov r1, #1
	add r0, r4, r0
	bl MOD64_021D7ED0
	mov r0, #0x13
	lsl r0, r0, #6
	add r0, r4, r0
	mov r1, #1
	bl MOD64_021D7ED0
	add r0, r4, #0
	mov r1, #1
	bl MOD64_021D83C4
	pop {r3, r4, r5, pc}
_021D81B0:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD64_021D83D4
	pop {r3, r4, r5, pc}
_021D81BA:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD64_021D8570
	pop {r3, r4, r5, pc}
_021D81C4:
	ldr r0, _021D81CC ; =0x04000050
	mov r1, #0
	strh r1, [r0]
_021D81CA:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D81CC: .word 0x04000050
_021D81D0: .word 0x000006CA
_021D81D4: .word 0x00000428
	thumb_func_end MOD64_021D8100

	thumb_func_start MOD64_021D81D8
MOD64_021D81D8: ; 0x021D81D8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	bl FUN_020222AC
	mov r1, #0
	mov r0, #0x11
	add r2, r1, #0
	bl FUN_020BB1C0
	bl FUN_020BB394
	bl FUN_020B02C8
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	bl FUN_02006ED4
	ldr r0, _021D8248 ; =0x0000064C
	ldr r0, [r4, r0]
	bl FUN_02013D5C
	mov r2, #1
	mov r0, #0x12
	add r1, sp, #4
	str r2, [sp, #4]
	bl FUN_020BB1C0
	mov r1, #0
	mov r0, #0x11
	add r2, r1, #0
	bl FUN_020BB1C0
	bl FUN_0201EBA4
	add r0, r4, #0
	bl MOD64_021D8058
	mov r2, #1
	mov r0, #0x12
	add r1, sp, #0
	str r2, [sp]
	bl FUN_020BB1C0
	mov r0, #0
	add r1, r0, #0
	bl FUN_020222B4
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201FDEC
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_021D8248: .word 0x0000064C
	thumb_func_end MOD64_021D81D8

	thumb_func_start MOD64_021D824C
MOD64_021D824C: ; 0x021D824C
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	bl FUN_0201EB64
	mov r1, #0x5f
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	add r1, r1, #4
	add r1, r4, r1
	bl MOD64_021D8268
	pop {r4, pc}
	thumb_func_end MOD64_021D824C

	thumb_func_start MOD64_021D8268
MOD64_021D8268: ; 0x021D8268
	push {r4, lr}
	sub sp, #0x20
	mov r3, #0
	str r3, [r1]
	str r3, [r1, #4]
	add r4, r0, #0
	ldr r2, _021D82B4 ; =0x0000EAAB
	str r3, [r1, #8]
	add r0, sp, #0xc
	strh r2, [r0]
	strh r3, [r0, #2]
	strh r3, [r0, #4]
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r1, #0
	mov r1, #0x4b
	ldr r3, _021D82B8 ; =0x00000FA4
	lsl r1, r1, #0xe
	add r2, sp, #0xc
	str r4, [sp, #8]
	bl FUN_0201ECA8
	mov r1, #0
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #0x18]
	str r1, [sp, #0x14]
	str r1, [sp, #0x1c]
	add r0, sp, #0x14
	add r1, r4, #0
	bl FUN_0201EC58
	add r0, r4, #0
	bl FUN_0201EB8C
	add sp, #0x20
	pop {r4, pc}
	.align 2, 0
_021D82B4: .word 0x0000EAAB
_021D82B8: .word 0x00000FA4
	thumb_func_end MOD64_021D8268

	thumb_func_start MOD64_021D82BC
MOD64_021D82BC: ; 0x021D82BC
	mov r1, #0x5f
	lsl r1, r1, #4
	ldr r3, _021D82C8 ; =FUN_0201EB70
	ldr r0, [r0, r1]
	bx r3
	nop
_021D82C8: .word FUN_0201EB70
	thumb_func_end MOD64_021D82BC

	thumb_func_start MOD64_021D82CC
MOD64_021D82CC: ; 0x021D82CC
	push {r4, r5, r6, r7}
	mov r5, #0
	add r4, r5, #0
	add r6, r0, #0
	sub r3, r5, #4
	add r1, r5, #0
	sub r4, #0x2c
	mov r2, #0x20
_021D82DC:
	cmp r5, #0
	beq _021D82EA
	cmp r5, #1
	beq _021D82F2
	cmp r5, #2
	beq _021D82FC
	b _021D8306
_021D82EA:
	str r4, [r6, #0x58]
	str r3, [r6, #0x5c]
	str r2, [r6, #0x60]
	b _021D8306
_021D82F2:
	str r1, [r6, #0x58]
	str r3, [r6, #0x5c]
	mov r7, #0x3e
	str r7, [r6, #0x60]
	b _021D8306
_021D82FC:
	mov r7, #0x26
	str r7, [r6, #0x58]
	str r3, [r6, #0x5c]
	mov r7, #0x1a
	str r7, [r6, #0x60]
_021D8306:
	add r5, r5, #1
	add r6, #0xc
	cmp r5, #3
	blt _021D82DC
	mov r5, #0
	mov r2, #0x82
	mov r1, #0x52
	mov r4, #0x4e
	mov r3, #0x37
_021D8318:
	cmp r5, #0
	beq _021D8326
	cmp r5, #1
	beq _021D8330
	cmp r5, #2
	beq _021D833A
	b _021D8346
_021D8326:
	add r6, r0, #0
	str r4, [r0, #0x7c]
	add r6, #0x80
	str r3, [r6]
	b _021D8346
_021D8330:
	add r6, r0, #0
	str r2, [r0, #0x7c]
	add r6, #0x80
	str r1, [r6]
	b _021D8346
_021D833A:
	mov r6, #0xac
	add r7, r0, #0
	str r6, [r0, #0x7c]
	add r7, #0x80
	mov r6, #0x32
	str r6, [r7]
_021D8346:
	add r5, r5, #1
	add r0, #8
	cmp r5, #3
	blt _021D8318
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
	thumb_func_end MOD64_021D82CC

	thumb_func_start MOD64_021D8354
MOD64_021D8354: ; 0x021D8354
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0x26
	lsl r0, r0, #4
	mov r4, #0
	add r6, r5, r0
	mov r7, #0x98
_021D8362:
	add r0, r4, #2
	add r1, r0, #0
	mul r1, r7
	add r0, r6, r1
	ldr r1, [r5, #0x58]
	ldr r2, [r5, #0x5c]
	ldr r3, [r5, #0x60]
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	lsl r3, r3, #0xc
	bl MOD64_021D7ED4
	add r4, r4, #1
	add r5, #0xc
	cmp r4, #3
	blt _021D8362
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD64_021D8354

	thumb_func_start MOD64_021D8384
MOD64_021D8384: ; 0x021D8384
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D83BC ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x20
	tst r0, r1
	beq _021D83A0
	ldr r0, [r4, #0x54]
	sub r0, r0, #1
	bmi _021D83A0
	str r0, [r4, #0x54]
	ldr r0, _021D83C0 ; =0x000005DC
	bl FUN_020054C8
_021D83A0:
	ldr r0, _021D83BC ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x10
	tst r0, r1
	beq _021D83BA
	ldr r0, [r4, #0x54]
	add r0, r0, #1
	cmp r0, #3
	bge _021D83BA
	str r0, [r4, #0x54]
	ldr r0, _021D83C0 ; =0x000005DC
	bl FUN_020054C8
_021D83BA:
	pop {r4, pc}
	.align 2, 0
_021D83BC: .word gMain
_021D83C0: .word 0x000005DC
	thumb_func_end MOD64_021D8384

	thumb_func_start MOD64_021D83C4
MOD64_021D83C4: ; 0x021D83C4
	ldr r2, [r0]
	add r1, r2, r1
	str r1, [r0]
	mov r1, #0
	str r1, [r0, #4]
	bx lr
	thumb_func_end MOD64_021D83C4

	thumb_func_start MOD64_021D83D0
MOD64_021D83D0: ; 0x021D83D0
	ldr r0, [r0]
	bx lr
	thumb_func_end MOD64_021D83D0

	thumb_func_start MOD64_021D83D4
MOD64_021D83D4: ; 0x021D83D4
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r2, [r4, #4]
	cmp r2, #8
	bls _021D83E2
	b _021D8510
_021D83E2:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021D83EE: ; jump table
	.short _021D8400 - _021D83EE - 2 ; case 0
	.short _021D8422 - _021D83EE - 2 ; case 1
	.short _021D843A - _021D83EE - 2 ; case 2
	.short _021D8450 - _021D83EE - 2 ; case 3
	.short _021D8480 - _021D83EE - 2 ; case 4
	.short _021D849E - _021D83EE - 2 ; case 5
	.short _021D84CE - _021D83EE - 2 ; case 6
	.short _021D84EC - _021D83EE - 2 ; case 7
	.short _021D8506 - _021D83EE - 2 ; case 8
_021D8400:
	mov r2, #0x5f
	lsl r2, r2, #4
	ldr r1, [r4, r2]
	add r2, r2, #4
	add r0, #0x10
	add r2, r4, r2
	bl MOD64_021D8864
	mov r0, #2
	mov r1, #1
	bl FUN_0201E6E4
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, pc}
_021D8422:
	add r0, #0x10
	bl MOD64_021D8928
	cmp r0, #0
	beq _021D8510
	mov r0, #6
	str r0, [r4, #0xc]
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, pc}
_021D843A:
	ldr r1, [r4, #0xc]
	sub r1, r1, #1
	str r1, [r4, #0xc]
	bpl _021D8510
	bl MOD64_021D8554
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, pc}
_021D8450:
	ldr r0, _021D8514 ; =0x0001020F
	mov r2, #5
	str r0, [sp]
	ldr r0, _021D8518 ; =0x000006AC
	lsl r2, r2, #6
	ldr r0, [r4, r0]
	mov r3, #0
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0xac
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x98
	ldr r0, [r0]
	bl MOD64_021D8744
	mov r1, #0x6b
	lsl r1, r1, #4
	strb r0, [r4, r1]
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, pc}
_021D8480:
	mov r0, #0x6b
	lsl r0, r0, #4
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0
	bne _021D8510
	add r0, r4, #0
	bl MOD64_021D87B8
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, pc}
_021D849E:
	ldr r0, _021D8514 ; =0x0001020F
	mov r2, #5
	str r0, [sp]
	ldr r0, _021D8518 ; =0x000006AC
	lsl r2, r2, #6
	ldr r0, [r4, r0]
	mov r3, #7
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0xac
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x98
	ldr r0, [r0]
	bl MOD64_021D8744
	mov r1, #0x6b
	lsl r1, r1, #4
	strb r0, [r4, r1]
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, pc}
_021D84CE:
	mov r0, #0x6b
	lsl r0, r0, #4
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0
	bne _021D8510
	add r0, r4, #0
	bl MOD64_021D87B8
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, pc}
_021D84EC:
	mov r0, #6
	lsl r0, r0, #8
	add r0, r4, r0
	mov r1, #1
	bl MOD64_021D8B58
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, pc}
_021D8506:
	bl MOD64_021D851C
	add r0, r4, #0
	bl MOD64_021D8554
_021D8510:
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_021D8514: .word 0x0001020F
_021D8518: .word 0x000006AC
	thumb_func_end MOD64_021D83D4

	thumb_func_start MOD64_021D851C
MOD64_021D851C: ; 0x021D851C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x26
	lsl r0, r0, #4
	mov r5, #0
	add r4, r6, r0
	mov r7, #0x98
_021D852A:
	ldr r0, [r6, #0x54]
	cmp r0, r5
	bne _021D853E
	add r0, r5, #2
	add r1, r0, #0
	mul r1, r7
	add r0, r4, r1
	bl MOD64_021D7F38
	b _021D854C
_021D853E:
	add r1, r5, #2
	mov r0, #0x98
	mul r0, r1
	add r0, r4, r0
	mov r1, #0
	bl MOD64_021D7F58
_021D854C:
	add r5, r5, #1
	cmp r5, #3
	blt _021D852A
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD64_021D851C

	thumb_func_start MOD64_021D8554
MOD64_021D8554: ; 0x021D8554
	add r2, r0, #0
	ldr r0, [r2, #0x54]
	ldr r3, _021D856C ; =MOD64_021D8B64
	lsl r1, r0, #3
	mov r0, #6
	lsl r0, r0, #8
	add r0, r2, r0
	add r2, r2, r1
	ldr r1, [r2, #0x7c]
	add r2, #0x80
	ldr r2, [r2]
	bx r3
	.align 2, 0
_021D856C: .word MOD64_021D8B64
	thumb_func_end MOD64_021D8554

	thumb_func_start MOD64_021D8570
MOD64_021D8570: ; 0x021D8570
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r2, [r4, #4]
	add r5, r1, #0
	cmp r2, #4
	bls _021D8580
	b _021D86D0
_021D8580:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021D858C: ; jump table
	.short _021D8596 - _021D858C - 2 ; case 0
	.short _021D85C2 - _021D858C - 2 ; case 1
	.short _021D8604 - _021D858C - 2 ; case 2
	.short _021D8644 - _021D858C - 2 ; case 3
	.short _021D867C - _021D858C - 2 ; case 4
_021D8596:
	mov r0, #6
	lsl r0, r0, #8
	add r0, r4, r0
	mov r1, #0
	bl MOD64_021D8B58
	add r0, r4, #0
	bl MOD64_021D8554
	add r0, r4, #0
	bl MOD64_021D902C
	add r0, r4, #0
	bl MOD64_021D8D40
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #1
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
_021D85C2:
	mov r0, #0x65
	lsl r0, r0, #4
	add r0, r4, r0
	mov r1, #1
	bl MOD64_021D8C30
	ldr r0, [r4, #0x54]
	mov r2, #0
	lsl r0, r0, #2
	add r1, r4, r0
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #6
	bl FUN_02007558
	add r0, r4, #0
	bl MOD64_021D8DCC
	cmp r0, #0
	beq _021D86D0
	ldr r0, [r4, #0x54]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl MOD64_021D9044
	bl FUN_02005578
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_021D8604:
	ldr r0, _021D86D4 ; =0x0001020F
	mov r2, #0xff
	str r0, [sp]
	str r2, [sp, #4]
	add r0, r4, #0
	add r0, #0x98
	ldr r3, [r4, #0x54]
	ldr r0, [r0]
	add r2, #0x41
	add r3, r3, #1
	bl MOD64_021D86DC
	add r0, r4, #0
	add r1, r4, #0
	str r5, [sp]
	add r0, #0x94
	ldr r0, [r0]
	ldr r2, _021D86D8 ; =0x0000029E
	add r1, #0xb0
	mov r3, #1
	bl FUN_02002198
	add r1, r4, #0
	add r1, #0xb8
	str r0, [r1]
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_021D8644:
	add r0, #0xb8
	ldr r0, [r0]
	bl FUN_020021AC
	cmp r0, #0
	beq _021D8660
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _021D866C
	add r1, r1, #1
	add sp, #8
	cmp r0, r1
	pop {r3, r4, r5, pc}
_021D8660:
	add r0, r4, #0
	mov r1, #1
	bl MOD64_021D83C4
	add sp, #8
	pop {r3, r4, r5, pc}
_021D866C:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	add r0, r4, #0
	bl MOD64_021D8DB0
	add sp, #8
	pop {r3, r4, r5, pc}
_021D867C:
	bl MOD64_021D8DCC
	cmp r0, #0
	beq _021D86D0
	mov r1, #0
	add r0, r4, #0
	mvn r1, r1
	bl MOD64_021D83C4
	mov r0, #7
	str r0, [r4, #4]
	mov r0, #0x65
	lsl r0, r0, #4
	add r0, r4, r0
	mov r1, #0
	bl MOD64_021D8C30
	ldr r0, [r4, #0x54]
	mov r2, #1
	lsl r0, r0, #2
	add r1, r4, r0
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #6
	bl FUN_02007558
	ldr r0, _021D86D4 ; =0x0001020F
	mov r2, #0xff
	str r0, [sp]
	add r0, r4, #0
	str r2, [sp, #4]
	add r0, #0x98
	ldr r0, [r0]
	add r1, r5, #0
	add r2, #0x41
	mov r3, #7
	bl MOD64_021D86DC
	mov r1, #0x6b
	lsl r1, r1, #4
	strb r0, [r4, r1]
_021D86D0:
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D86D4: .word 0x0001020F
_021D86D8: .word 0x0000029E
	thumb_func_end MOD64_021D8570

	thumb_func_start MOD64_021D86DC
MOD64_021D86DC: ; 0x021D86DC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	add r6, r3, #0
	mov r0, #0
	mov r1, #0x1a
	add r3, r4, #0
	bl NewMsgDataFromNarc
	add r4, r0, #0
	bne _021D86F8
	bl ErrorHandling
_021D86F8:
	add r0, r4, #0
	add r1, r6, #0
	bl NewString_ReadMsgData
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #0xf
	bl FUN_02019620
	mov r3, #0
	ldr r0, [sp, #0x2c]
	str r3, [sp]
	str r0, [sp, #4]
	ldr r0, [sp, #0x28]
	mov r1, #1
	str r0, [sp, #8]
	add r0, r5, #0
	add r2, r6, #0
	str r3, [sp, #0xc]
	bl AddTextPrinterParameterized2
	mov r1, #0
	mov r2, #2
	add r7, r0, #0
	add r0, r5, #0
	lsl r2, r2, #8
	add r3, r1, #0
	bl FUN_0200D0BC
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	bl DestroyMsgData
	add r0, r7, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD64_021D86DC

	thumb_func_start MOD64_021D8744
MOD64_021D8744: ; 0x021D8744
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	ldr r4, [sp, #0x30]
	add r5, r0, #0
	ldr r0, [r4]
	add r6, r1, #0
	add r7, r2, #0
	str r3, [sp, #0x10]
	cmp r0, #0
	beq _021D875C
	bl ErrorHandling
_021D875C:
	mov r0, #0
	mov r1, #0x1a
	add r2, r7, #0
	add r3, r6, #0
	bl NewMsgDataFromNarc
	add r6, r0, #0
	bne _021D8770
	bl ErrorHandling
_021D8770:
	ldr r1, [sp, #0x10]
	add r0, r6, #0
	bl NewString_ReadMsgData
	str r0, [r4]
	add r0, r5, #0
	mov r1, #0xf
	bl FUN_02019620
	mov r3, #0
	ldr r0, [sp, #0x2c]
	str r3, [sp]
	str r0, [sp, #4]
	ldr r0, [sp, #0x28]
	mov r1, #1
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r2, [r4]
	add r0, r5, #0
	bl AddTextPrinterParameterized2
	mov r1, #0
	mov r2, #2
	add r4, r0, #0
	add r0, r5, #0
	lsl r2, r2, #8
	add r3, r1, #0
	bl FUN_0200D0BC
	add r0, r6, #0
	bl DestroyMsgData
	add r0, r4, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD64_021D8744

	thumb_func_start MOD64_021D87B8
MOD64_021D87B8: ; 0x021D87B8
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xac
	ldr r0, [r0]
	bl String_dtor
	mov r0, #0
	add r4, #0xac
	str r0, [r4]
	pop {r4, pc}
	thumb_func_end MOD64_021D87B8

	thumb_func_start MOD64_021D87CC
MOD64_021D87CC: ; 0x021D87CC
	push {r4, lr}
	sub sp, #8
	add r2, r0, #0
	add r4, r1, #0
	mov r1, #1
	add r2, #0xb0
	strb r1, [r2]
	add r2, r0, #0
	mov r3, #0x17
	add r2, #0xb1
	strb r3, [r2]
	add r2, r0, #0
	mov r3, #0xc
	add r2, #0xb2
	strb r3, [r2]
	add r2, r0, #0
	mov r3, #5
	add r2, #0xb3
	strb r3, [r2]
	add r2, r0, #0
	mov r3, #4
	add r2, #0xb4
	strb r3, [r2]
	add r2, r0, #0
	mov r3, #3
	add r2, #0xb5
	strb r3, [r2]
	add r2, r0, #0
	mov r3, #0xa7
	add r2, #0xb6
	strh r3, [r2]
	mov r2, #0
	str r2, [sp]
	str r4, [sp, #4]
	add r0, #0x94
	ldr r0, [r0]
	ldr r2, _021D882C ; =0x0000029E
	add r3, r1, #0
	bl FUN_0200CB00
	mov r0, #0
	mov r1, #0x60
	add r2, r4, #0
	bl FUN_02002ED0
	add sp, #8
	pop {r4, pc}
	nop
_021D882C: .word 0x0000029E
	thumb_func_end MOD64_021D87CC

	thumb_func_start MOD64_021D8830
MOD64_021D8830: ; 0x021D8830
	str r1, [r0]
	str r1, [r0, #4]
	sub r1, r2, r1
	str r1, [r0, #8]
	str r3, [r0, #0xc]
	bx lr
	thumb_func_end MOD64_021D8830

	thumb_func_start MOD64_021D883C
MOD64_021D883C: ; 0x021D883C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r3, [r5, #0xc]
	cmp r1, r3
	blt _021D884A
	mov r4, #1
	b _021D884C
_021D884A:
	mov r4, #0
_021D884C:
	ldr r2, [r5, #8]
	add r0, r2, #0
	mul r0, r1
	add r1, r3, #0
	bl _s32_div_f
	ldr r1, [r5, #4]
	add r0, r0, r1
	str r0, [r5]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD64_021D883C

	thumb_func_start MOD64_021D8864
MOD64_021D8864: ; 0x021D8864
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x40]
	add r4, r1, #0
	add r6, r2, #0
	cmp r0, #0
	beq _021D8876
	bl ErrorHandling
_021D8876:
	ldr r1, _021D88B8 ; =0xFFFFEAAB
	ldr r2, _021D88BC ; =0xFFFFDC72
	add r0, r5, #0
	mov r3, #6
	bl MOD64_021D8830
	add r0, r5, #0
	mov r1, #0x4b
	mov r2, #0x32
	add r0, #0x10
	lsl r1, r1, #0xe
	lsl r2, r2, #0xe
	mov r3, #6
	bl MOD64_021D8830
	add r0, r5, #0
	mov r2, #9
	add r0, #0x20
	mov r1, #0
	lsl r2, r2, #0xe
	mov r3, #6
	bl MOD64_021D8830
	mov r2, #0
	str r2, [r5, #0x3c]
	str r4, [r5, #0x30]
	str r6, [r5, #0x34]
	ldr r0, _021D88C0 ; =MOD64_021D88C4
	add r1, r5, #0
	str r2, [r5, #0x38]
	bl FUN_0200CA44
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D88B8: .word 0xFFFFEAAB
_021D88BC: .word 0xFFFFDC72
_021D88C0: .word MOD64_021D88C4
	thumb_func_end MOD64_021D8864

	thumb_func_start MOD64_021D88C4
MOD64_021D88C4: ; 0x021D88C4
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r1, #0
	ldr r1, [r5, #0x38]
	add r6, r0, #0
	add r0, r5, #0
	bl MOD64_021D883C
	add r4, r0, #0
	add r0, r5, #0
	ldr r1, [r5, #0x38]
	add r0, #0x10
	bl MOD64_021D883C
	add r0, r5, #0
	ldr r1, [r5, #0x38]
	add r0, #0x20
	bl MOD64_021D883C
	ldr r1, [r5]
	add r0, sp, #0
	strh r1, [r0]
	mov r1, #0
	strh r1, [r0, #2]
	strh r1, [r0, #4]
	ldr r1, [r5, #0x30]
	add r0, sp, #0
	bl FUN_0201EF90
	ldr r0, [r5, #0x10]
	ldr r1, [r5, #0x30]
	bl FUN_0201EFE0
	ldr r1, [r5, #0x20]
	ldr r0, [r5, #0x34]
	str r1, [r0, #8]
	ldr r0, [r5, #0x38]
	add r0, r0, #1
	str r0, [r5, #0x38]
	cmp r4, #1
	bne _021D8924
	add r0, r6, #0
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r5, #0x40]
	mov r0, #1
	str r0, [r5, #0x3c]
_021D8924:
	add sp, #8
	pop {r4, r5, r6, pc}
	thumb_func_end MOD64_021D88C4

	thumb_func_start MOD64_021D8928
MOD64_021D8928: ; 0x021D8928
	ldr r0, [r0, #0x3c]
	bx lr
	thumb_func_end MOD64_021D8928

	thumb_func_start MOD64_021D892C
MOD64_021D892C: ; 0x021D892C
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r6, r2, #0
	mov r2, #0xa
	add r5, r0, #0
	str r2, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x7a
	add r4, r1, #0
	str r6, [sp, #8]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x52
	mov r3, #0
	bl FUN_02008F34
	str r0, [r4, #4]
	bl FUN_02009B04
	ldr r0, [r4, #4]
	bl FUN_02009474
	mov r2, #0xb
	str r2, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x7b
	str r6, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x52
	mov r3, #0
	bl FUN_02008FEC
	str r0, [r4, #8]
	bl FUN_02009D68
	ldr r0, [r4, #8]
	bl FUN_02009474
	mov r2, #0xc
	str r2, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x1f
	str r6, [sp, #8]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x52
	mov r3, #0
	bl FUN_020090AC
	str r0, [r4, #0xc]
	mov r2, #0xd
	str r2, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x7d
	str r6, [sp, #8]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x52
	mov r3, #0
	bl FUN_020090AC
	str r0, [r4, #0x10]
	add sp, #0x10
	pop {r4, r5, r6, pc}
	thumb_func_end MOD64_021D892C

	thumb_func_start MOD64_021D89B8
MOD64_021D89B8: ; 0x021D89B8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	bl FUN_02009C0C
	ldr r0, [r4, #8]
	bl FUN_02009E04
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r1, [r4, #4]
	bl FUN_02009490
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r1, [r4, #8]
	bl FUN_02009490
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	ldr r1, [r4, #0xc]
	bl FUN_02009490
	mov r0, #0x7d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r1, [r4, #0x10]
	bl FUN_02009490
	pop {r3, r4, r5, pc}
	thumb_func_end MOD64_021D89B8

	thumb_func_start MOD64_021D89FC
MOD64_021D89FC: ; 0x021D89FC
	push {r4, r5, r6, lr}
	sub sp, #0x70
	add r5, r0, #0
	mov r0, #0xd
	str r0, [sp]
	sub r0, #0xe
	str r0, [sp, #4]
	add r6, r2, #0
	str r0, [sp, #8]
	mov r0, #0
	mov r2, #0x7a
	add r4, r1, #0
	str r0, [sp, #0xc]
	mov r1, #1
	lsl r2, r2, #2
	str r1, [sp, #0x10]
	ldr r1, [r5, r2]
	mov r3, #0xc
	str r1, [sp, #0x14]
	add r1, r2, #4
	ldr r1, [r5, r1]
	str r1, [sp, #0x18]
	add r1, r2, #0
	add r1, #8
	ldr r1, [r5, r1]
	add r2, #0xc
	str r1, [sp, #0x1c]
	ldr r1, [r5, r2]
	mov r2, #0xb
	str r1, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r0, sp, #0x4c
	mov r1, #0xa
	bl FUN_02008AA4
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	str r0, [sp, #0x2c]
	add r0, sp, #0x4c
	str r0, [sp, #0x30]
	mov r0, #0x20
	str r0, [sp, #0x40]
	mov r0, #1
	str r0, [sp, #0x44]
	mov r0, #0
	str r0, [sp, #0x34]
	str r0, [sp, #0x38]
	add r0, sp, #0x2c
	str r6, [sp, #0x48]
	bl FUN_0201FF84
	mov r1, #0
	str r0, [r4]
	bl FUN_020200A0
	mov r0, #0
	str r0, [r4, #0x1c]
	str r0, [r4, #0x20]
	add sp, #0x70
	pop {r4, r5, r6, pc}
	thumb_func_end MOD64_021D89FC

	thumb_func_start MOD64_021D8A78
MOD64_021D8A78: ; 0x021D8A78
	ldr r3, _021D8A80 ; =FUN_0201FFC8
	ldr r0, [r0]
	bx r3
	nop
_021D8A80: .word FUN_0201FFC8
	thumb_func_end MOD64_021D8A78

	thumb_func_start MOD64_021D8A84
MOD64_021D8A84: ; 0x021D8A84
	mov r3, #0
	str r3, [r0]
	str r1, [r0, #4]
	str r2, [r0, #8]
	str r3, [r0, #0xc]
	bx lr
	thumb_func_end MOD64_021D8A84

	thumb_func_start MOD64_021D8A90
MOD64_021D8A90: ; 0x021D8A90
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0xc]
	ldr r0, _021D8AD8 ; =0x0000FFFF
	mul r0, r1
	ldr r1, [r4, #8]
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #4
	lsl r1, r0, #2
	ldr r0, _021D8ADC ; =UNK_020FFA38
	ldr r2, [r4, #4]
	ldrsh r0, [r0, r1]
	asr r3, r2, #0x1f
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	str r1, [r4]
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #8]
	add r0, r0, #1
	bl _s32_div_f
	str r1, [r4, #0xc]
	pop {r4, pc}
	nop
_021D8AD8: .word 0x0000FFFF
_021D8ADC: .word UNK_020FFA38
	thumb_func_end MOD64_021D8A90

	thumb_func_start MOD64_021D8AE0
MOD64_021D8AE0: ; 0x021D8AE0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _021D8AEE
	bl ErrorHandling
_021D8AEE:
	add r0, r4, #0
	mov r1, #2
	add r0, #0x2c
	lsl r1, r1, #0xe
	mov r2, #0x20
	bl MOD64_021D8A84
	ldr r0, _021D8B0C ; =MOD64_021D8B10
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	str r0, [r4, #0x28]
	pop {r4, pc}
	nop
_021D8B0C: .word MOD64_021D8B10
	thumb_func_end MOD64_021D8AE0

	thumb_func_start MOD64_021D8B10
MOD64_021D8B10: ; 0x021D8B10
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r0, r4, #0
	add r0, #0x2c
	bl MOD64_021D8A90
	add r5, r4, #0
	add r5, #0x1c
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	ldr r1, [sp, #4]
	ldr r0, [r4, #0x2c]
	add r0, r1, r0
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, r2, #0
	bl FUN_02020044
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD64_021D8B10

	thumb_func_start MOD64_021D8B44
MOD64_021D8B44: ; 0x021D8B44
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _021D8B56
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #0x28]
_021D8B56:
	pop {r4, pc}
	thumb_func_end MOD64_021D8B44

	thumb_func_start MOD64_021D8B58
MOD64_021D8B58: ; 0x021D8B58
	ldr r3, _021D8B60 ; =FUN_020200A0
	ldr r0, [r0]
	bx r3
	nop
_021D8B60: .word FUN_020200A0
	thumb_func_end MOD64_021D8B58

	thumb_func_start MOD64_021D8B64
MOD64_021D8B64: ; 0x021D8B64
	lsl r1, r1, #0xc
	str r1, [r0, #0x1c]
	lsl r1, r2, #0xc
	str r1, [r0, #0x20]
	bx lr
	.align 2, 0
	thumb_func_end MOD64_021D8B64

	thumb_func_start MOD64_021D8B70
MOD64_021D8B70: ; 0x021D8B70
	push {r4, r5, r6, lr}
	sub sp, #0x38
	add r5, r0, #0
	add r3, r5, #0
	add r6, r2, #0
	add r4, r1, #0
	mov r0, #0x52
	mov r1, #0xe
	mov r2, #0
	add r3, #0x14
	str r6, [sp]
	bl FUN_02006BB0
	add r2, r5, #0
	str r0, [r5, #0xc]
	mov r0, #0x52
	mov r1, #0xf
	add r2, #0x18
	add r3, r6, #0
	bl FUN_02006C08
	str r0, [r5, #0x10]
	ldr r0, _021D8C04 ; =0x0000064C
	ldr r0, [r4, r0]
	str r0, [sp, #4]
	ldr r0, [r5, #0x14]
	str r0, [sp, #8]
	add r0, sp, #4
	bl FUN_02013D98
	str r0, [r5]
	ldr r0, _021D8C04 ; =0x0000064C
	ldr r0, [r4, r0]
	str r0, [sp, #0x2c]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x30]
	mov r0, #1
	str r0, [sp, #0x34]
	add r0, sp, #0x2c
	bl FUN_02013E14
	str r0, [r5, #4]
	ldr r0, _021D8C04 ; =0x0000064C
	mov r2, #0
	ldr r0, [r4, r0]
	mov r1, #0x1f
	str r0, [sp, #0xc]
	ldr r0, [r5]
	str r0, [sp, #0x10]
	ldr r0, [r5, #4]
	str r0, [sp, #0x14]
	add r0, sp, #4
	strh r2, [r0, #0x14]
	strh r2, [r0, #0x16]
	strh r2, [r0, #0x18]
	str r1, [sp, #0x20]
	ldr r1, _021D8C08 ; =0x000003FE
	str r1, [sp, #0x24]
	strh r2, [r0, #0x24]
	add r0, sp, #0xc
	bl FUN_02013E84
	str r0, [r5, #8]
	mov r1, #0
	bl FUN_02013EB0
	mov r1, #0x40
	ldr r0, [r5, #8]
	add r2, r1, #0
	bl FUN_02013ED8
	add sp, #0x38
	pop {r4, r5, r6, pc}
	nop
_021D8C04: .word 0x0000064C
_021D8C08: .word 0x000003FE
	thumb_func_end MOD64_021D8B70

	thumb_func_start MOD64_021D8C0C
MOD64_021D8C0C: ; 0x021D8C0C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	bl FUN_02013EA8
	ldr r0, [r4]
	bl FUN_02013DD4
	ldr r0, [r4, #4]
	bl FUN_02013E44
	ldr r0, [r4, #0xc]
	bl FreeToHeap
	ldr r0, [r4, #0x10]
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD64_021D8C0C

	thumb_func_start MOD64_021D8C30
MOD64_021D8C30: ; 0x021D8C30
	ldr r3, _021D8C38 ; =FUN_02013EB0
	ldr r0, [r0, #8]
	bx r3
	nop
_021D8C38: .word FUN_02013EB0
	thumb_func_end MOD64_021D8C30

	thumb_func_start MOD64_021D8C3C
MOD64_021D8C3C: ; 0x021D8C3C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x54]
	add r6, r1, #0
	add r7, r2, #0
	str r3, [sp]
	cmp r0, #0
	beq _021D8C50
	bl ErrorHandling
_021D8C50:
	ldr r4, [sp, #0x24]
	add r0, r5, #0
	add r0, #0x1c
	add r1, r6, #0
	add r2, r7, #0
	add r3, r4, #0
	bl MOD64_021D8830
	add r0, r5, #0
	ldr r1, [sp]
	ldr r2, [sp, #0x18]
	add r0, #0x2c
	add r3, r4, #0
	bl MOD64_021D8830
	add r0, r5, #0
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x20]
	add r0, #0x3c
	add r3, r4, #0
	bl MOD64_021D8830
	mov r2, #0
	str r2, [r5, #0x4c]
	mov r0, #1
	str r0, [r5, #0x50]
	ldr r0, _021D8C90 ; =MOD64_021D8CC8
	add r1, r5, #0
	bl FUN_0200CA44
	str r0, [r5, #0x54]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8C90: .word MOD64_021D8CC8
	thumb_func_end MOD64_021D8C3C

	thumb_func_start MOD64_021D8C94
MOD64_021D8C94: ; 0x021D8C94
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x54]
	cmp r0, #0
	beq _021D8CA2
	bl ErrorHandling
_021D8CA2:
	mov r0, #1
	mvn r0, r0
	str r0, [r4, #0x50]
	ldr r1, [r4, #0x28]
	ldr r0, [r4, #0x4c]
	cmp r0, r1
	blt _021D8CB6
	ldr r0, [r4, #0x50]
	add r0, r1, r0
	str r0, [r4, #0x4c]
_021D8CB6:
	ldr r0, _021D8CC4 ; =MOD64_021D8CC8
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	str r0, [r4, #0x54]
	pop {r4, pc}
	.align 2, 0
_021D8CC4: .word MOD64_021D8CC8
	thumb_func_end MOD64_021D8C94

	thumb_func_start MOD64_021D8CC8
MOD64_021D8CC8: ; 0x021D8CC8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	ldr r1, [r5, #0x4c]
	add r0, #0x1c
	bl MOD64_021D883C
	add r4, r0, #0
	add r0, r5, #0
	ldr r1, [r5, #0x4c]
	add r0, #0x2c
	bl MOD64_021D883C
	add r0, r5, #0
	ldr r1, [r5, #0x4c]
	add r0, #0x3c
	bl MOD64_021D883C
	mov r2, #1
	ldr r1, [r5, #0x1c]
	lsl r2, r2, #0x12
	sub r1, r1, r2
	ldr r3, [r5, #0x2c]
	lsl r1, r1, #4
	sub r2, r3, r2
	lsl r2, r2, #4
	ldr r0, [r5, #8]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_02013EC4
	ldr r1, [r5, #0x3c]
	ldr r0, [r5, #8]
	add r2, r1, #0
	bl FUN_02013EE0
	cmp r4, #1
	beq _021D8D1C
	ldr r0, [r5, #0x4c]
	cmp r0, #0
	bge _021D8D26
_021D8D1C:
	add r0, r6, #0
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r5, #0x54]
_021D8D26:
	ldr r1, [r5, #0x4c]
	ldr r0, [r5, #0x50]
	add r0, r1, r0
	str r0, [r5, #0x4c]
	pop {r4, r5, r6, pc}
	thumb_func_end MOD64_021D8CC8

	thumb_func_start MOD64_021D8D30
MOD64_021D8D30: ; 0x021D8D30
	ldr r0, [r0, #0x54]
	cmp r0, #0
	bne _021D8D3A
	mov r0, #1
	bx lr
_021D8D3A:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD64_021D8D30

	thumb_func_start MOD64_021D8D40
MOD64_021D8D40: ; 0x021D8D40
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x54]
	mov r2, #1
	lsl r0, r0, #3
	add r1, r5, r0
	ldr r0, [r1, #0x7c]
	add r1, #0x80
	lsl r6, r0, #0xc
	ldr r0, [r1]
	ldr r1, _021D8DAC ; =0x00000666
	add r0, #0x30
	lsl r4, r0, #0xc
	mov r0, #6
	lsl r0, r0, #0x10
	str r0, [sp]
	str r1, [sp, #4]
	lsl r2, r2, #0xc
	str r2, [sp, #8]
	mov r0, #6
	sub r1, #0x16
	str r0, [sp, #0xc]
	add r0, r5, r1
	add r1, r6, #0
	lsl r2, r2, #7
	add r3, r4, #0
	bl MOD64_021D8C3C
	mov r0, #6
	mov r3, #1
	mov r1, #0x21
	str r4, [sp]
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, _021D8DAC ; =0x00000666
	lsl r3, r3, #0xc
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	mov r0, #6
	str r0, [sp, #0x10]
	ldr r2, [r5, #0x54]
	lsl r1, r1, #4
	lsl r2, r2, #2
	add r0, r5, r1
	add r2, r5, r2
	sub r1, #0xc
	ldr r1, [r2, r1]
	add r2, r6, #0
	lsl r3, r3, #7
	bl MOD64_021D8DDC
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021D8DAC: .word 0x00000666
	thumb_func_end MOD64_021D8D40

	thumb_func_start MOD64_021D8DB0
MOD64_021D8DB0: ; 0x021D8DB0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x65
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD64_021D8C94
	mov r0, #0x21
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD64_021D8E34
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD64_021D8DB0

	thumb_func_start MOD64_021D8DCC
MOD64_021D8DCC: ; 0x021D8DCC
	mov r1, #0x65
	lsl r1, r1, #4
	ldr r3, _021D8DD8 ; =MOD64_021D8D30
	add r0, r0, r1
	bx r3
	nop
_021D8DD8: .word MOD64_021D8D30
	thumb_func_end MOD64_021D8DCC

	thumb_func_start MOD64_021D8DDC
MOD64_021D8DDC: ; 0x021D8DDC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x3c]
	add r6, r1, #0
	add r7, r2, #0
	str r3, [sp]
	cmp r0, #0
	beq _021D8DF0
	bl ErrorHandling
_021D8DF0:
	ldr r4, [sp, #0x28]
	ldr r2, [sp]
	add r0, r5, #4
	add r1, r7, #0
	add r3, r4, #0
	bl MOD64_021D8830
	add r0, r5, #0
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x1c]
	add r0, #0x14
	add r3, r4, #0
	bl MOD64_021D8830
	add r0, r5, #0
	ldr r1, [sp, #0x20]
	ldr r2, [sp, #0x24]
	add r0, #0x24
	add r3, r4, #0
	bl MOD64_021D8830
	str r6, [r5]
	mov r2, #0
	str r2, [r5, #0x34]
	mov r0, #1
	str r0, [r5, #0x38]
	ldr r0, _021D8E30 ; =MOD64_021D8E68
	add r1, r5, #0
	bl FUN_0200CA44
	str r0, [r5, #0x3c]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8E30: .word MOD64_021D8E68
	thumb_func_end MOD64_021D8DDC

	thumb_func_start MOD64_021D8E34
MOD64_021D8E34: ; 0x021D8E34
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x3c]
	cmp r0, #0
	beq _021D8E42
	bl ErrorHandling
_021D8E42:
	mov r0, #1
	mvn r0, r0
	str r0, [r4, #0x38]
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x34]
	cmp r0, r1
	blt _021D8E56
	ldr r0, [r4, #0x38]
	add r0, r1, r0
	str r0, [r4, #0x34]
_021D8E56:
	ldr r0, _021D8E64 ; =MOD64_021D8E68
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	str r0, [r4, #0x3c]
	pop {r4, pc}
	.align 2, 0
_021D8E64: .word MOD64_021D8E68
	thumb_func_end MOD64_021D8E34

	thumb_func_start MOD64_021D8E68
MOD64_021D8E68: ; 0x021D8E68
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r1, [r5, #0x34]
	add r7, r0, #0
	add r0, r5, #4
	bl MOD64_021D883C
	add r6, r0, #0
	add r0, r5, #0
	ldr r1, [r5, #0x34]
	add r0, #0x14
	bl MOD64_021D883C
	add r0, r5, #0
	ldr r1, [r5, #0x34]
	add r0, #0x24
	bl MOD64_021D883C
	ldr r2, [r5, #0x24]
	asr r0, r2, #0x1f
	lsr r1, r2, #0xc
	lsl r0, r0, #0x14
	lsl r3, r2, #0x14
	mov r2, #2
	orr r0, r1
	mov r1, #0
	lsl r2, r2, #0xa
	add r2, r3, r2
	adc r0, r1
	lsl r0, r0, #0x14
	lsr r2, r2, #0xc
	orr r2, r0
	asr r4, r2, #0xc
	ldr r2, [r5, #4]
	ldr r0, [r5]
	asr r2, r2, #0xc
	bl FUN_02007558
	ldr r2, [r5, #0x14]
	ldr r0, [r5]
	mov r1, #1
	asr r2, r2, #0xc
	bl FUN_02007558
	ldr r0, [r5]
	mov r1, #0xc
	add r2, r4, #0
	bl FUN_02007558
	ldr r0, [r5]
	mov r1, #0xd
	add r2, r4, #0
	bl FUN_02007558
	cmp r6, #1
	beq _021D8EDE
	ldr r0, [r5, #0x34]
	cmp r0, #0
	bge _021D8EE8
_021D8EDE:
	add r0, r7, #0
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r5, #0x3c]
_021D8EE8:
	ldr r1, [r5, #0x34]
	ldr r0, [r5, #0x38]
	add r0, r1, r0
	str r0, [r5, #0x34]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD64_021D8E68

	thumb_func_start MOD64_021D8EF4
MOD64_021D8EF4: ; 0x021D8EF4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r0, [sp, #0x14]
	mov r0, #0x20
	str r0, [sp]
	add r0, r1, #0
	str r1, [sp, #0x18]
	str r0, [sp, #4]
	mov r0, #0x52
	mov r1, #0x11
	mov r2, #0
	mov r3, #0xa0
	bl FUN_02006930
	ldr r5, [sp, #0x14]
	mov r4, #0
	mov r6, #1
_021D8F16:
	ldr r0, [sp, #0x18]
	mov r1, #1
	bl FUN_02018FF4
	add r1, r5, #0
	add r1, #0x9c
	str r0, [r1]
	add r0, r5, #0
	add r0, #0x9c
	ldr r0, [r0]
	bl FUN_0201901C
	cmp r4, #0
	beq _021D8F3C
	cmp r4, #1
	beq _021D8F44
	cmp r4, #2
	beq _021D8F4C
	b _021D8F52
_021D8F3C:
	mov r0, #0xc
	str r0, [sp, #0x1c]
	mov r7, #4
	b _021D8F52
_021D8F44:
	mov r0, #4
	str r0, [sp, #0x1c]
	mov r7, #0xe
	b _021D8F52
_021D8F4C:
	mov r0, #0x14
	str r0, [sp, #0x1c]
	mov r7, #0xd
_021D8F52:
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0xb
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #5
	str r0, [sp, #0xc]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	add r1, r5, #0
	ldr r3, [sp, #0x1c]
	add r0, #0x94
	add r1, #0x9c
	lsl r3, r3, #0x18
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #3
	lsr r3, r3, #0x18
	bl FUN_02019064
	ldr r0, _021D8FA8 ; =0x0001020A
	mov r2, #5
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x9c
	ldr r0, [r0]
	ldr r1, [sp, #0x18]
	lsl r2, r2, #6
	add r3, r4, #4
	bl MOD64_021D8FD0
	add r4, r4, #1
	add r5, r5, #4
	add r6, #0x40
	cmp r4, #3
	blt _021D8F16
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8FA8: .word 0x0001020A
	thumb_func_end MOD64_021D8EF4

	thumb_func_start MOD64_021D8FAC
MOD64_021D8FAC: ; 0x021D8FAC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_021D8FB2:
	add r0, r5, #0
	add r0, #0x9c
	ldr r0, [r0]
	bl FUN_02019178
	add r0, r5, #0
	add r0, #0x9c
	ldr r0, [r0]
	bl FreeToHeap
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _021D8FB2
	pop {r3, r4, r5, pc}
	thumb_func_end MOD64_021D8FAC

	thumb_func_start MOD64_021D8FD0
MOD64_021D8FD0: ; 0x021D8FD0
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	add r6, r3, #0
	mov r0, #0
	mov r1, #0x1a
	add r3, r4, #0
	bl NewMsgDataFromNarc
	add r4, r0, #0
	bne _021D8FEC
	bl ErrorHandling
_021D8FEC:
	add r0, r4, #0
	add r1, r6, #0
	bl NewString_ReadMsgData
	ldr r1, [sp, #0x20]
	add r6, r0, #0
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	bl FUN_02019620
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x20]
	add r2, r6, #0
	str r0, [sp, #8]
	add r0, r5, #0
	mov r3, #1
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	bl DestroyMsgData
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD64_021D8FD0

	thumb_func_start MOD64_021D902C
MOD64_021D902C: ; 0x021D902C
	add r1, r0, #0
	add r1, #0xa8
	ldr r1, [r1]
	ldr r3, _021D9040 ; =FUN_02019570
	lsl r1, r1, #2
	add r0, r0, r1
	add r0, #0x9c
	ldr r0, [r0]
	bx r3
	nop
_021D9040: .word FUN_02019570
	thumb_func_end MOD64_021D902C

	thumb_func_start MOD64_021D9044
MOD64_021D9044: ; 0x021D9044
	push {r3, lr}
	cmp r0, #0
	beq _021D9054
	cmp r0, #1
	beq _021D9058
	cmp r0, #2
	beq _021D905C
	b _021D9060
_021D9054:
	ldr r0, _021D9068 ; =0x00000183
	pop {r3, pc}
_021D9058:
	ldr r0, _021D906C ; =0x00000186
	pop {r3, pc}
_021D905C:
	ldr r0, _021D9070 ; =0x00000189
	pop {r3, pc}
_021D9060:
	bl ErrorHandling
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_021D9068: .word 0x00000183
_021D906C: .word 0x00000186
_021D9070: .word 0x00000189
	thumb_func_end MOD64_021D9044

	.rodata
	.global MOD64_021D9074
MOD64_021D9074: ; 0x021D9074
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD64_021D9084
MOD64_021D9084: ; 0x021D9084
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD64_021D9094
MOD64_021D9094: ; 0x021D9094
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x01, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD64_021D90B0
MOD64_021D90B0: ; 0x021D90B0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD64_021D90CC
MOD64_021D90CC: ; 0x021D90CC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x02, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD64_021D90E8
MOD64_021D90E8: ; 0x021D90E8
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00

	.data
	.bss
