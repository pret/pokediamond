	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD51_02254840
MOD51_02254840: ; 0x02254840
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x14]
	ldr r1, [r1, #0x7c]
	cmp r1, #0
	beq _022548EE
	ldr r1, [r4]
	cmp r1, #3
	bhi _022548EE
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02254860: ; jump table
	.short _02254868 - _02254860 - 2 ; case 0
	.short _0225487A - _02254860 - 2 ; case 1
	.short _022548D0 - _02254860 - 2 ; case 2
	.short _022548EE - _02254860 - 2 ; case 3
_02254868:
	bl MOD51_02254B54
	add r0, r4, #0
	bl MOD51_022548F0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_0225487A:
	add r0, r4, #0
	bl MOD51_02254C80
	add r0, r4, #0
	bl MOD51_02254D50
	mov r0, #1
	mov r1, #4
	bl FUN_02002C84
	mov r1, #0x72
	lsl r1, r1, #2
	ldr r0, [r4, #0x14]
	add r1, r4, r1
	bl MOD51_02254944
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineBToggleLayers
	mov r0, #2
	mov r1, #1
	bl GX_EngineBToggleLayers
	mov r0, #4
	mov r1, #1
	bl GX_EngineBToggleLayers
	mov r0, #8
	mov r1, #1
	bl GX_EngineBToggleLayers
	add r0, r4, #0
	bl MOD51_0225571C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_022548D0:
	add r0, r4, #0
	bl MOD51_02255690
	add r0, r4, #0
	bl MOD51_02255030
	add r0, r4, #0
	bl MOD51_022552FC
	add r0, r4, #0
	bl MOD51_02254F30
	ldr r0, [r4, #0x28]
	bl FUN_0201FDEC
_022548EE:
	pop {r4, pc}
	thumb_func_end MOD51_02254840

	thumb_func_start MOD51_022548F0
MOD51_022548F0: ; 0x022548F0
	push {r3, r4, lr}
	sub sp, #4
	mov r1, #0xa1
	lsl r1, r1, #2
	add r4, r0, #0
	mov r2, #0
	add r0, r1, #0
	str r2, [r4, r1]
	sub r0, #0x10
	strh r2, [r4, r0]
	add r0, r1, #0
	sub r0, #0xe
	strh r2, [r4, r0]
	add r0, r1, #0
	sub r0, #0xc
	strh r2, [r4, r0]
	sub r1, #0xa
	mov r0, #4
	strh r2, [r4, r1]
	bl ScrStrBufs_new
	mov r2, #9
	str r0, [r4, #0x18]
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #6
	mov r3, #4
	bl NewMsgDataFromNarc
	str r0, [r4, #0x1c]
	mov r0, #4
	add r3, r4, #0
	str r0, [sp]
	mov r0, #0x4a
	mov r1, #3
	mov r2, #1
	add r3, #0x24
	bl FUN_02006BDC
	str r0, [r4, #0x20]
	add sp, #4
	pop {r3, r4, pc}
	thumb_func_end MOD51_022548F0

	thumb_func_start MOD51_02254944
MOD51_02254944: ; 0x02254944
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r7, r0, #0
	mov r0, #0xa0
	str r0, [sp, #0x20]
	mov r0, #0xd0
	str r0, [sp, #0x1c]
	mov r0, #3
	str r0, [sp, #0x18]
	ldr r0, _02254A3C ; =0x00000265
	add r5, r1, #0
	mov r4, #0
	mov r6, #1
	str r0, [sp, #0x14]
_02254960:
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x20]
	add r2, r4, #4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r2, r2, #0x18
	str r0, [sp, #0x10]
	add r0, r7, #0
	add r1, r5, #0
	lsr r2, r2, #0x18
	mov r3, #1
	bl FUN_02019064
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	add r0, r5, #0
	bl CopyWindowToVram
	ldr r0, [sp, #0x18]
	add r2, r4, #4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #5
	str r0, [sp, #8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x1c]
	add r1, r5, #0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r2, r2, #0x18
	str r0, [sp, #0x10]
	add r0, r7, #0
	add r1, #0x10
	lsr r2, r2, #0x18
	mov r3, #2
	bl FUN_02019064
	add r0, r5, #0
	add r0, #0x10
	mov r1, #0
	bl FUN_02019620
	add r0, r5, #0
	add r0, #0x10
	bl CopyWindowToVram
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0xf
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x14]
	add r2, r4, #4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r1, r5, #0
	lsl r2, r2, #0x18
	str r0, [sp, #0x10]
	add r0, r7, #0
	add r1, #0x20
	lsr r2, r2, #0x18
	mov r3, #0xc
	bl FUN_02019064
	add r0, r5, #0
	add r0, #0x20
	mov r1, #0
	bl FUN_02019620
	add r0, r5, #0
	add r0, #0x20
	bl CopyWindowToVram
	ldr r0, [sp, #0x20]
	add r4, r4, #1
	add r0, #0x10
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r6, #8
	add r0, #0x87
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r5, #0x38
	add r0, #8
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r0, #0x1e
	str r0, [sp, #0x14]
	cmp r4, #3
	blt _02254960
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02254A3C: .word 0x00000265
	thumb_func_end MOD51_02254944

	thumb_func_start MOD51_02254A40
MOD51_02254A40: ; 0x02254A40
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_02254A46:
	add r0, r5, #0
	add r0, #0x10
	bl FUN_02019178
	add r0, r5, #0
	bl FUN_02019178
	add r0, r5, #0
	add r0, #0x20
	bl FUN_02019178
	add r4, r4, #1
	add r5, #0x38
	cmp r4, #3
	blt _02254A46
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD51_02254A40

	thumb_func_start MOD51_02254A68
MOD51_02254A68: ; 0x02254A68
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r1, #0xa3
	mov r2, #4
	ldr r0, _02254AB0 ; =MOD51_02254840
	lsl r1, r1, #2
	add r3, r2, #0
	bl FUN_020061E8
	add r6, r0, #0
	bl FUN_0201B6C8
	add r4, r0, #0
	str r5, [r4, #0xc]
	ldr r0, [r5, #8]
	str r0, [r4, #0x14]
	ldr r0, [r5, #0x7c]
	str r0, [r4, #4]
	ldr r0, [r5, #0x78]
	str r0, [r4, #8]
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	str r0, [r4, #0x10]
	mov r0, #0
	mov r1, #0xa2
	str r0, [r4]
	lsl r1, r1, #2
	str r6, [r4, r1]
	ldr r2, [r5, #0x7c]
	ldr r0, _02254AB4 ; =0x000004DC
	sub r1, #0x18
	ldr r0, [r2, r0]
	str r0, [r4, r1]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_02254AB0: .word MOD51_02254840
_02254AB4: .word 0x000004DC
	thumb_func_end MOD51_02254A68

	thumb_func_start MOD51_02254AB8
MOD51_02254AB8: ; 0x02254AB8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6]
	cmp r0, #2
	bne _02254B2C
	ldr r0, [r6, #0x14]
	str r0, [sp]
	mov r0, #3
	str r0, [r6]
	mov r0, #1
	bl FUN_02002CC0
	mov r0, #0x59
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	mov r0, #0x5a
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009E04
	mov r7, #0x55
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_02254AEC:
	ldr r0, [r5, r7]
	bl FUN_02008E2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _02254AEC
	ldr r0, [r6, #0x28]
	bl FUN_0201FD58
	ldr r0, [r6, #0x1c]
	bl DestroyMsgData
	ldr r0, [r6, #0x18]
	bl ScrStrBufs_delete
	mov r0, #0x72
	lsl r0, r0, #2
	add r0, r6, r0
	bl MOD51_02254A40
	ldr r0, [sp]
	bl MOD51_02254B30
	ldr r0, [r6, #0x20]
	bl FreeToHeap
	mov r0, #0xa2
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_0200621C
_02254B2C:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD51_02254AB8

	thumb_func_start MOD51_02254B30
MOD51_02254B30: ; 0x02254B30
	push {r4, lr}
	add r4, r0, #0
	mov r1, #4
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #7
	bl FUN_020178A0
	pop {r4, pc}
	thumb_func_end MOD51_02254B30

	thumb_func_start MOD51_02254B54
MOD51_02254B54: ; 0x02254B54
	push {r3, r4, r5, lr}
	sub sp, #0x80
	add r4, r0, #0
	bl MOD51_02254B30
	ldr r5, _02254C70 ; =0x022557A8
	add r3, sp, #0x64
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
	mov r0, #1
	mov r1, #0
	bl GX_EngineBToggleLayers
	ldr r5, _02254C74 ; =0x0225578C
	add r3, sp, #0x48
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
	mov r0, #2
	mov r1, #0
	bl GX_EngineBToggleLayers
	ldr r5, _02254C78 ; =0x022557C4
	add r3, sp, #0x2c
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
	add r0, r4, #0
	mov r1, #6
	bl FUN_02018744
	mov r0, #4
	mov r1, #0
	bl GX_EngineBToggleLayers
	ldr r5, _02254C7C ; =0x02255754
	add r3, sp, #0x10
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
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #8
	mov r1, #0
	bl GX_EngineBToggleLayers
	mov r0, #0x60
	mov r1, #0
	str r0, [sp]
	mov r2, #4
	mov r0, #0x4a
	add r3, r1, #0
	str r2, [sp, #4]
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	mov r0, #5
	lsl r0, r0, #0xa
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	mov r0, #0x4a
	mov r1, #2
	add r2, r4, #0
	mov r3, #7
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r1, #4
	mov r0, #0x4a
	add r2, r4, #0
	mov r3, #7
	str r1, [sp, #0xc]
	bl FUN_020068C8
	mov r0, #4
	mov r1, #0
	bl FUN_02054590
	add sp, #0x80
	pop {r3, r4, r5, pc}
	nop
_02254C70: .word MOD51_022557A8
_02254C74: .word MOD51_0225578C
_02254C78: .word MOD51_022557C4
_02254C7C: .word MOD51_02255754
	thumb_func_end MOD51_02254B54

	thumb_func_start MOD51_02254C80
MOD51_02254C80: ; 0x02254C80
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r0, #0
	add r1, r6, #0
	mov r0, #0xa
	add r1, #0x2c
	mov r2, #4
	bl FUN_02008C9C
	mov r7, #0x55
	str r0, [r6, #0x28]
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_02254C9C:
	mov r0, #1
	add r1, r4, #0
	mov r2, #4
	bl FUN_02008DEC
	str r0, [r5, r7]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _02254C9C
	ldr r0, _02254D4C ; =0x000003E7
	mov r1, #0x4a
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	mov r2, #5
	mov r3, #1
	bl FUN_02008F34
	mov r1, #0x59
	lsl r1, r1, #2
	str r0, [r6, r1]
	ldr r0, _02254D4C ; =0x000003E7
	mov r2, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	str r2, [sp, #8]
	mov r0, #4
	sub r1, #0xc
	str r0, [sp, #0xc]
	ldr r0, [r6, r1]
	mov r1, #0x4a
	mov r3, #0
	bl FUN_02008FEC
	mov r1, #0x5a
	lsl r1, r1, #2
	str r0, [r6, r1]
	ldr r0, _02254D4C ; =0x000003E7
	sub r1, #0xc
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, [r6, r1]
	mov r1, #0x4a
	mov r2, #6
	mov r3, #1
	bl FUN_020090AC
	mov r1, #0x5b
	lsl r1, r1, #2
	str r0, [r6, r1]
	ldr r0, _02254D4C ; =0x000003E7
	sub r1, #0xc
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, [r6, r1]
	mov r1, #0x4a
	mov r2, #7
	mov r3, #1
	bl FUN_020090AC
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r6, r1]
	sub r1, #0xc
	ldr r0, [r6, r1]
	bl FUN_02009B04
	mov r0, #0x5a
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009D68
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254D4C: .word 0x000003E7
	thumb_func_end MOD51_02254C80

	thumb_func_start MOD51_02254D50
MOD51_02254D50: ; 0x02254D50
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	ldr r1, _02254E28 ; =0x000003E7
	add r5, r0, #0
	mov r0, #0
	str r1, [sp]
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r3, #0x55
	str r0, [sp, #0x10]
	lsl r3, r3, #2
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
	add r3, #0x20
	str r2, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r0, r5, r3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02008AA4
	ldr r0, [r5, #0x28]
	mov r4, #0
	str r0, [sp, #0x2c]
	mov r0, #0x5d
	lsl r0, r0, #2
	add r0, r5, r0
	str r0, [sp, #0x30]
	mov r0, #1
	lsl r0, r0, #0xc
	mov r7, #0x3f
	str r4, [sp, #0x3c]
	str r0, [sp, #0x40]
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	add r0, sp, #0x2c
	strh r4, [r0, #0x20]
	mov r0, #2
	str r0, [sp, #0x54]
	mov r0, #4
	ldr r6, _02254E2C ; =0x02255734
	str r4, [sp, #0x50]
	str r0, [sp, #0x58]
	lsl r7, r7, #0x18
_02254DC4:
	mov r0, #0x3a
	lsl r0, r0, #0xe
	str r0, [sp, #0x34]
	ldr r0, [r6]
	cmp r0, #0
	ble _02254DE0
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	add r0, r7, #0
	bl _fadd
	b _02254DEC
_02254DE0:
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r7, #0
	bl _fsub
_02254DEC:
	bl _ffix
	mov r1, #3
	lsl r1, r1, #0x12
	add r0, r0, r1
	str r0, [sp, #0x38]
	add r0, sp, #0x2c
	bl FUN_0201FE94
	mov r1, #0x66
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x66
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_02020130
	add r4, r4, #1
	add r6, r6, #4
	add r5, r5, #4
	cmp r4, #3
	blt _02254DC4
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02254E28: .word 0x000003E7
_02254E2C: .word MOD51_02255734
	thumb_func_end MOD51_02254D50

	thumb_func_start MOD51_02254E30
MOD51_02254E30: ; 0x02254E30
	add r1, r1, #1
	cmp r1, #0x1e
	bne _02254E38
	mov r1, #0
_02254E38:
	add r0, r1, #0
	bx lr
	thumb_func_end MOD51_02254E30

	thumb_func_start MOD51_02254E3C
MOD51_02254E3C: ; 0x02254E3C
	add r0, r0, r1
	cmp r0, #0x1e
	blt _02254E44
	sub r0, #0x1e
_02254E44:
	bx lr
	.align 2, 0
	thumb_func_end MOD51_02254E3C

	thumb_func_start MOD51_02254E48
MOD51_02254E48: ; 0x02254E48
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r3, r1, #0
	add r5, r0, #0
	add r4, r3, #0
	mov r0, #0x38
	mul r4, r0
	mov r0, #0x7e
	add r6, r2, #0
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, [r6, #0x10]
	mov r2, #8
	str r0, [r1, r4]
	mov r0, #0x20
	str r0, [sp]
	str r2, [sp, #4]
	ldr r2, [r5, #0x24]
	mov r7, #0
	add r2, #0xc
	str r2, [sp, #8]
	str r7, [sp, #0xc]
	ldr r2, [r1, r4]
	mov r1, #0x18
	mul r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	mov r0, #0x30
	str r0, [sp, #0x18]
	lsl r3, r3, #0x1b
	ldr r0, [r5, #0x14]
	mov r1, #7
	add r2, r7, #0
	lsr r3, r3, #0x18
	bl FUN_02018170
	mov r0, #0x72
	lsl r0, r0, #2
	add r7, r5, r0
	add r0, r7, r4
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x76
	lsl r0, r0, #2
	add r0, r5, r0
	str r0, [sp, #0x1c]
	add r0, r0, r4
	mov r1, #0
	bl FUN_02019620
	mov r0, #0x7a
	lsl r0, r0, #2
	add r5, r5, r0
	add r0, r5, r4
	mov r1, #0
	bl FUN_02019620
	mov r0, #2
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02254F2C ; =0x00010200
	mov r3, #0
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r2, [r6]
	add r0, r7, r4
	mov r1, #1
	bl AddTextPrinterParameterized2
	mov r0, #6
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02254F2C ; =0x00010200
	mov r3, #0
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r0, [sp, #0x1c]
	ldr r2, [r6, #4]
	add r0, r0, r4
	mov r1, #1
	bl AddTextPrinterParameterized2
	add r0, r7, r4
	bl FUN_02019220
	ldr r0, [sp, #0x1c]
	add r0, r0, r4
	bl FUN_02019220
	ldr r2, [r6, #8]
	cmp r2, #0
	beq _02254F22
	mov r0, #2
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02254F2C ; =0x00010200
	mov r3, #0
	str r0, [sp, #8]
	add r0, r5, r4
	mov r1, #1
	str r3, [sp, #0xc]
	bl AddTextPrinterParameterized2
_02254F22:
	add r0, r5, r4
	bl FUN_02019220
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254F2C: .word 0x00010200
	thumb_func_end MOD51_02254E48

	thumb_func_start MOD51_02254F30
MOD51_02254F30: ; 0x02254F30
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x27
	add r5, r0, #0
	lsl r1, r1, #4
	add r0, r1, #0
	ldr r2, [r5, r1]
	add r1, #8
	add r0, #0xdc
	ldrh r1, [r5, r1]
	ldr r0, [r2, r0]
	bl MOD51_02254E3C
	add r6, r0, #0
	mov r0, #0x27
	lsl r0, r0, #4
	ldr r1, [r5, r0]
	add r0, #0xd8
	ldr r7, [r1, r0]
	cmp r7, #3
	ble _02254F5A
	mov r7, #3
_02254F5A:
	mov r0, #0x9e
	lsl r0, r0, #2
	ldrh r1, [r5, r0]
	add r0, r0, #4
	ldr r0, [r5, r0]
	cmp r1, r0
	beq _02254F78
	add r0, r5, #0
	bl MOD51_0225571C
	mov r0, #0x9e
	lsl r0, r0, #2
	ldrh r1, [r5, r0]
	add r0, r0, #4
	str r1, [r5, r0]
_02254F78:
	mov r0, #0xa1
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #1
	bne _02254FE2
	mov r4, #0
	cmp r7, #0
	ble _02254FB0
_02254F88:
	mov r2, #0x27
	lsl r2, r2, #4
	mov r3, #0x1c
	ldr r2, [r5, r2]
	mul r3, r6
	add r0, r5, #0
	add r1, r4, #0
	add r2, r2, r3
	bl MOD51_02254E48
	mov r0, #0x27
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl MOD51_02254E30
	add r4, r4, #1
	add r6, r0, #0
	cmp r4, r7
	blt _02254F88
_02254FB0:
	ldr r0, [r5, #0x14]
	mov r1, #7
	bl FUN_0201886C
	mov r1, #6
	lsl r1, r1, #8
	bl DC_FlushRange
	ldr r0, [r5, #0x14]
	mov r1, #7
	bl FUN_0201886C
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r3, #6
	ldr r0, [r5, #0x14]
	mov r1, #7
	lsl r3, r3, #8
	bl FUN_02017CE8
	mov r0, #0xa1
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
_02254FE2:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD51_02254F30

	thumb_func_start MOD51_02254FE4
MOD51_02254FE4: ; 0x02254FE4
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0x3a
	lsl r0, r0, #0xe
	str r0, [sp]
	cmp r1, #0
	ble _02255006
	lsl r0, r1, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _02255014
_02255006:
	lsl r0, r1, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_02255014:
	bl _ffix
	mov r1, #3
	lsl r1, r1, #0x12
	add r0, r0, r1
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, sp, #0
	bl FUN_02020044
	add sp, #0xc
	pop {r3, r4, pc}
	thumb_func_end MOD51_02254FE4

	thumb_func_start MOD51_02255030
MOD51_02255030: ; 0x02255030
	push {r4, lr}
	mov r1, #0x27
	add r4, r0, #0
	lsl r1, r1, #4
	add r0, r1, #0
	ldr r2, [r4, r1]
	add r0, #0xd8
	ldr r2, [r2, r0]
	add r0, r1, #4
	strh r2, [r4, r0]
	ldrh r0, [r4, r0]
	cmp r0, #3
	bls _02255060
	add r0, r1, #6
	ldrh r0, [r4, r0]
	cmp r0, #3
	bhi _02255060
	add r0, r1, #0
	mov r2, #1
	add r0, #0xa
	strh r2, [r4, r0]
	mov r0, #0
	add r1, #8
	strh r0, [r4, r1]
_02255060:
	mov r1, #0x1a
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	add r1, #0xda
	ldrh r1, [r4, r1]
	bl FUN_020200A0
	ldr r0, _022550AC ; =0x0000027A
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _022550A0
	bl FUN_02020A98
	cmp r0, #0
	bne _022550A0
	mov r1, #0x9e
	lsl r1, r1, #2
	ldrh r2, [r4, r1]
	sub r1, r1, #4
	ldrh r1, [r4, r1]
	mov r0, #0x60
	mul r0, r2
	sub r1, r1, #3
	bl _s32_div_f
	add r1, r0, #0
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, #0x30
	bl MOD51_02254FE4
_022550A0:
	mov r0, #0x9d
	lsl r0, r0, #2
	ldrh r1, [r4, r0]
	add r0, r0, #2
	strh r1, [r4, r0]
	pop {r4, pc}
	.align 2, 0
_022550AC: .word 0x0000027A
	thumb_func_end MOD51_02255030

	thumb_func_start MOD51_022550B0
MOD51_022550B0: ; 0x022550B0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _022551D8 ; =0x02255770
	bl FUN_02020988
	add r7, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r7, r0
	bne _022550C6
	b _022551D2
_022550C6:
	cmp r7, #0
	beq _022550D4
	cmp r7, #1
	beq _02255100
	cmp r7, #5
	beq _022551CA
	b _02255132
_022550D4:
	lsl r0, r7, #2
	add r1, r5, r0
	mov r0, #0x66
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, r7, #4
	bl FUN_02020130
	mov r0, #0x9e
	lsl r0, r0, #2
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _022551CA
	ldr r0, _022551DC ; =0x000005E5
	bl FUN_020054C8
	mov r0, #0x9e
	lsl r0, r0, #2
	ldrh r1, [r5, r0]
	sub r1, r1, #1
	strh r1, [r5, r0]
	b _022551CA
_02255100:
	lsl r0, r7, #2
	add r1, r5, r0
	mov r0, #0x66
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, r7, #4
	bl FUN_02020130
	mov r0, #0x9e
	lsl r0, r0, #2
	ldrh r1, [r5, r0]
	sub r0, r0, #4
	ldrh r0, [r5, r0]
	sub r0, r0, #3
	cmp r1, r0
	bge _022551CA
	ldr r0, _022551DC ; =0x000005E5
	bl FUN_020054C8
	mov r0, #0x9e
	lsl r0, r0, #2
	ldrh r1, [r5, r0]
	add r1, r1, #1
	strh r1, [r5, r0]
	b _022551CA
_02255132:
	mov r2, #0x27
	lsl r2, r2, #4
	add r1, r2, #0
	ldr r0, [r5, r2]
	add r1, #0xd8
	ldr r3, [r0, r1]
	sub r1, r7, #1
	cmp r3, r1
	blt _022551CA
	add r1, r2, #0
	add r1, #0xdc
	add r2, #8
	ldr r0, [r0, r1]
	ldrh r1, [r5, r2]
	add r1, r1, r7
	sub r1, r1, #2
	bl MOD51_02254E3C
	mov r1, #0x1c
	mov r4, #0
	mul r1, r0
	add r6, r4, #0
	str r1, [sp]
_02255160:
	add r0, r4, #0
	bl FUN_0202EF18
	cmp r0, #0
	beq _0225519C
	ldr r1, [r5, #4]
	add r0, #0x50
	add r1, r1, r6
	ldrb r1, [r1, #0xd]
	cmp r1, #2
	bne _0225519C
	mov r1, #0x27
	lsl r1, r1, #4
	ldr r2, [r5, r1]
	ldr r1, [sp]
	ldr r0, [r0]
	add r1, r1, r2
	ldr r1, [r1, #0xc]
	cmp r0, r1
	bne _0225519C
	ldr r0, _022551DC ; =0x000005E5
	bl FUN_020054C8
	mov r1, #0x18
	ldr r2, [r5, #4]
	mul r1, r4
	mov r0, #1
	add r1, r2, r1
	strb r0, [r1, #0xf]
	b _022551A4
_0225519C:
	add r4, r4, #1
	add r6, #0x18
	cmp r4, #0xa
	blt _02255160
_022551A4:
	bl FUN_0202EF70
	bl PlayerProfile_GetTrainerID
	mov r1, #0x27
	lsl r1, r1, #4
	ldr r2, [r5, r1]
	ldr r1, [sp]
	add r1, r2, r1
	ldr r1, [r1, #0xc]
	cmp r1, r0
	bne _022551CA
	ldr r0, _022551DC ; =0x000005E5
	bl FUN_020054C8
	ldr r1, [r5, #4]
	ldr r0, _022551E0 ; =0x000004BF
	mov r2, #1
	strb r2, [r1, r0]
_022551CA:
	mov r0, #0x71
	sub r1, r7, #2
	lsl r0, r0, #2
	str r1, [r5, r0]
_022551D2:
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022551D8: .word MOD51_02255770
_022551DC: .word 0x000005E5
_022551E0: .word 0x000004BF
	thumb_func_end MOD51_022550B0

	thumb_func_start MOD51_022551E4
MOD51_022551E4: ; 0x022551E4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r0, #0
	ldr r0, _02255290 ; =0x02255740
	bl FUN_02020968
	mov r1, #0
	mvn r1, r1
	str r0, [sp]
	cmp r0, r1
	beq _0225528A
	cmp r0, #0
	bne _02255256
	add r0, sp, #8
	add r1, sp, #4
	bl FUN_02020AB0
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r7, r0]
	ldr r1, [sp, #4]
	bl MOD51_02254FE4
	mov r0, #0x9d
	lsl r0, r0, #2
	ldrh r0, [r7, r0]
	cmp r0, #3
	bls _0225528A
	sub r4, r0, #2
	mov r0, #0x60
	add r1, r4, #0
	bl _s32_div_f
	mov r1, #0
	cmp r4, #0
	ble _0225528A
	ldr r5, [sp, #4]
	add r2, r1, #0
	add r3, r1, #0
_02255232:
	add r6, r2, #0
	add r6, #0x30
	cmp r5, r6
	blo _0225524A
	add r6, r3, r0
	add r6, #0x30
	cmp r5, r6
	bhs _0225524A
	mov r0, #0x9e
	lsl r0, r0, #2
	strh r1, [r7, r0]
	b _0225528A
_0225524A:
	add r1, r1, #1
	add r2, r2, r0
	add r3, r3, r0
	cmp r1, r4
	blt _02255232
	b _0225528A
_02255256:
	mov r1, #0x27
	lsl r1, r1, #4
	add r0, r1, #0
	ldr r2, [r7, r1]
	add r0, #0xd8
	ldr r2, [r2, r0]
	ldr r0, [sp]
	cmp r2, r0
	blt _0225528A
	add r0, r1, #0
	sub r0, #0xac
	ldr r2, [r7, r0]
	ldr r0, [sp]
	sub r3, r0, #1
	cmp r2, r3
	bne _0225528A
	sub r1, #0x74
	add r2, r7, r1
	mov r0, #0x38
	add r1, r3, #0
	mul r1, r0
	ldr r0, [r2, r1]
	cmp r0, #5
	bge _0225528A
	add r0, r0, #1
	str r0, [r2, r1]
_0225528A:
	ldr r0, [sp]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02255290: .word MOD51_02255740
	thumb_func_end MOD51_022551E4

	thumb_func_start MOD51_02255294
MOD51_02255294: ; 0x02255294
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _022552F4 ; =gMain
	mov r1, #2
	ldr r2, [r0, #0x48]
	lsl r1, r1, #8
	add r0, r2, #0
	tst r0, r1
	beq _022552C6
	sub r1, #0x68
	ldr r0, [r4, r1]
	mov r1, #4
	bl FUN_02020130
	mov r0, #0x9e
	lsl r0, r0, #2
	ldrh r1, [r4, r0]
	cmp r1, #0
	beq _022552F0
	sub r1, r1, #1
	strh r1, [r4, r0]
	ldr r0, _022552F8 ; =0x000005E5
	bl FUN_020054C8
	pop {r4, pc}
_022552C6:
	lsr r0, r1, #1
	tst r0, r2
	beq _022552F0
	sub r1, #0x64
	ldr r0, [r4, r1]
	mov r1, #5
	bl FUN_02020130
	mov r0, #0x9e
	lsl r0, r0, #2
	sub r1, r0, #4
	ldrh r1, [r4, r1]
	ldrh r2, [r4, r0]
	sub r1, r1, #3
	cmp r2, r1
	bge _022552F0
	add r1, r2, #1
	strh r1, [r4, r0]
	ldr r0, _022552F8 ; =0x000005E5
	bl FUN_020054C8
_022552F0:
	pop {r4, pc}
	nop
_022552F4: .word gMain
_022552F8: .word 0x000005E5
	thumb_func_end MOD51_02255294

	thumb_func_start MOD51_022552FC
MOD51_022552FC: ; 0x022552FC
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	mov r4, #0
	mvn r4, r4
	bl FUN_0204646C
	cmp r0, #0
	bne _02255332
	add r0, r5, #0
	bl MOD51_022550B0
	add r6, r0, #0
	add r0, r5, #0
	bl MOD51_022551E4
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r6, r0
	bne _02255332
	cmp r4, r0
	bne _02255332
	add r0, r5, #0
	bl MOD51_02255294
_02255332:
	mov r2, #0x27
	lsl r2, r2, #4
	add r0, r2, #0
	ldr r1, [r5, r2]
	add r0, #0xd8
	ldr r0, [r1, r0]
	sub r3, r4, #1
	str r0, [sp]
	add r0, r2, #0
	add r0, #0x10
	add r0, r5, r0
	str r0, [sp, #4]
	sub r2, #0xa8
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x24]
	add r2, r5, r2
	bl MOD51_0225535C
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD51_022552FC

	thumb_func_start MOD51_0225535C
MOD51_0225535C: ; 0x0225535C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x40]
	str r1, [sp, #0x20]
	add r5, r2, #0
	mov r1, #0
	str r0, [sp, #0x40]
	ldr r4, [sp, #0x44]
	cmp r0, #3
	ble _02255376
	mov r0, #3
	str r0, [sp, #0x40]
_02255376:
	ldr r2, [sp, #0x40]
	mov r0, #0
	cmp r2, #0
	ble _0225539C
	add r2, r5, #0
_02255380:
	cmp r3, r0
	beq _0225538E
	ldr r6, [r2, #0x34]
	cmp r6, #0
	beq _0225538E
	sub r6, r6, #1
	str r6, [r2, #0x34]
_0225538E:
	ldr r6, [r2, #0x34]
	add r0, r0, #1
	add r1, r1, r6
	ldr r6, [sp, #0x40]
	add r2, #0x38
	cmp r0, r6
	blt _02255380
_0225539C:
	cmp r1, #0
	bne _022553AC
	ldr r0, [r4]
	cmp r0, #0
	bne _022553AC
	add sp, #0x28
	str r1, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_022553AC:
	ldr r0, [sp, #0x40]
	str r1, [r4]
	mov r4, #0
	cmp r0, #0
	ble _02255422
	ldr r0, [sp, #0x20]
	add r7, r4, #0
	add r0, #0xc
	str r0, [sp, #0x20]
_022553BE:
	ldr r1, [r5, #0x34]
	lsl r3, r7, #0x18
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	str r0, [sp, #0x24]
	mov r0, #0x20
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	ldr r0, [sp, #0x20]
	lsr r3, r3, #0x18
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x24]
	ldr r1, [r5, #0x30]
	lsl r2, r0, #3
	mov r0, #0x18
	mul r0, r1
	add r0, r2, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x10]
	mov r0, #0x20
	str r0, [sp, #0x14]
	mov r0, #0x30
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	mov r1, #7
	mov r2, #0
	bl FUN_02018170
	ldr r3, [sp, #0x24]
	add r1, r4, #4
	lsl r6, r3, #2
	ldr r3, _02255450 ; =0x02255728
	lsl r1, r1, #0x18
	ldr r0, [sp, #0x1c]
	ldr r3, [r3, r6]
	lsr r1, r1, #0x18
	mov r2, #3
	bl FUN_020179E0
	ldr r0, [sp, #0x40]
	add r4, r4, #1
	add r5, #0x38
	add r7, #8
	cmp r4, r0
	blt _022553BE
_02255422:
	ldr r0, [sp, #0x1c]
	mov r1, #7
	bl FUN_0201886C
	mov r1, #6
	lsl r1, r1, #8
	bl DC_FlushRange
	ldr r0, [sp, #0x1c]
	mov r1, #7
	bl FUN_0201886C
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r3, #6
	ldr r0, [sp, #0x1c]
	mov r1, #7
	lsl r3, r3, #8
	bl FUN_02017CE8
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02255450: .word MOD51_02255728
	thumb_func_end MOD51_0225535C

	thumb_func_start MOD51_02255454
MOD51_02255454: ; 0x02255454
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r0, #0
	mov r4, #0
	ldr r0, [sp, #0x28]
	add r5, r1, #0
	add r7, r2, #0
	str r3, [sp, #8]
	str r4, [sp, #0xc]
	bl PlayerProfile_GetTrainerID
	cmp r5, r0
	beq _02255478
	add r0, r6, #0
	add r1, r5, #0
	bl FUN_02025614
	add r4, r0, #0
_02255478:
	cmp r4, #0
	ble _022554D8
	cmp r4, #1
	bne _0225548C
	ldr r2, [sp, #0x28]
	add r0, r7, #0
	mov r1, #0
	bl BufferPlayersName
	b _022554CA
_0225548C:
	cmp r4, #2
	blt _022554CA
	sub r5, r4, #2
	mov r0, #0xa
	mov r1, #0x59
	bl String_ctor
	add r4, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	bl FUN_020254F0
	add r1, r0, #0
	add r0, r4, #0
	bl CopyU16ArrayToString
	add r0, r6, #0
	add r1, r5, #0
	bl FUN_020254F8
	mov r1, #0
	str r1, [sp]
	str r0, [sp, #4]
	add r0, r7, #0
	add r2, r4, #0
	add r3, r1, #0
	bl BufferString
	add r0, r4, #0
	bl String_dtor
_022554CA:
	ldr r1, [sp, #8]
	add r0, r7, #0
	mov r2, #0xce
	mov r3, #0x59
	bl ReadMsgData_ExpandPlaceholders
	str r0, [sp, #0xc]
_022554D8:
	ldr r0, [sp, #0xc]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD51_02255454

	thumb_func_start MOD51_022554E0
MOD51_022554E0: ; 0x022554E0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r0, #0
	add r6, r2, #0
	ldr r2, [r7, #4]
	ldr r0, _022555BC ; =0x000004D8
	str r1, [sp, #4]
	mov r1, #0x27
	ldr r0, [r2, r0]
	lsl r1, r1, #4
	str r0, [sp, #0xc]
	add r0, r1, #0
	ldr r4, [r7, r1]
	add r0, #0xd8
	ldr r0, [r4, r0]
	str r3, [sp, #8]
	cmp r0, #0x1e
	bne _02255508
	add r1, #0xdc
	b _0225550A
_02255508:
	add r1, #0xd8
_0225550A:
	add r5, r4, r1
	ldr r1, [r5]
	mov r0, #0x1c
	mul r0, r1
	add r0, r4, r0
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _0225551E
	bl String_dtor
_0225551E:
	ldr r1, [r5]
	mov r0, #0x1c
	mul r0, r1
	add r0, r4, r0
	ldr r0, [r0, #8]
	cmp r0, #0
	beq _02255530
	bl String_dtor
_02255530:
	ldr r0, [sp, #8]
	bl PlayerProfile_GetNamePtr
	add r1, r0, #0
	ldr r2, [r5]
	mov r0, #0x1c
	mul r0, r2
	ldr r0, [r4, r0]
	bl CopyU16ArrayToString
	ldr r0, [r5]
	mov r1, #0x1c
	add r2, r0, #0
	mul r2, r1
	add r0, r4, r2
	ldrh r2, [r6]
	strh r2, [r0, #0x14]
	ldrh r2, [r6, #2]
	strh r2, [r0, #0x16]
	ldrh r2, [r6, #4]
	strh r2, [r0, #0x18]
	ldrh r2, [r6, #6]
	strh r2, [r0, #0x1a]
	ldr r0, [r5]
	mul r1, r0
	ldr r0, [sp, #4]
	add r1, r4, r1
	str r0, [r1, #0xc]
	ldr r0, [sp, #8]
	bl PlayerProfile_GetTrainerGender
	ldr r2, [r5]
	mov r1, #0x1c
	mul r1, r2
	add r1, r4, r1
	str r0, [r1, #0x10]
	add r0, r6, #0
	mov r1, #0x59
	bl MailMsg_GetExpandedString
	ldr r2, [r5]
	mov r1, #0x1c
	mul r1, r2
	add r1, r4, r1
	str r0, [r1, #4]
	ldr r0, [r7, #0x10]
	ldr r1, [sp, #4]
	str r0, [sp]
	ldr r0, [sp, #0xc]
	ldr r2, [r7, #0x18]
	ldr r3, [r7, #0x1c]
	bl MOD51_02255454
	ldr r2, [r5]
	mov r1, #0x1c
	mul r1, r2
	add r1, r4, r1
	str r0, [r1, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	mov r0, #0xd3
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0x1e
	bne _022555B8
	mov r1, #0
	str r1, [r4, r0]
_022555B8:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022555BC: .word 0x000004D8
	thumb_func_end MOD51_022554E0

	thumb_func_start MOD51_022555C0
MOD51_022555C0: ; 0x022555C0
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r0, r1, #0
	str r1, [sp]
	add r7, r2, #0
	bl MailMsg_IsInit
	cmp r0, #0
	bne _022555D6
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_022555D6:
	mov r1, #0x27
	lsl r1, r1, #4
	ldr r0, [r6, r1]
	add r1, #0xd8
	ldr r1, [r0, r1]
	mov r4, #0
	cmp r1, #0
	ble _02255610
	add r5, r4, #0
_022555E8:
	add r1, r0, r5
	ldr r0, [r1, #0xc]
	cmp r7, r0
	bne _022555FC
	ldr r0, [sp]
	add r1, #0x14
	bl MailMsg_compare
	cmp r0, #0
	bne _02255610
_022555FC:
	mov r0, #0x27
	lsl r0, r0, #4
	mov r1, #0xd2
	ldr r0, [r6, r0]
	lsl r1, r1, #2
	ldr r1, [r0, r1]
	add r4, r4, #1
	add r5, #0x1c
	cmp r4, r1
	blt _022555E8
_02255610:
	mov r0, #0x27
	lsl r0, r0, #4
	ldr r1, [r6, r0]
	add r0, #0xd8
	ldr r0, [r1, r0]
	cmp r4, r0
	beq _02255626
	cmp r0, #0
	beq _02255626
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02255626:
	mov r0, #0x1c
	mul r0, r4
	add r1, r1, r0
	ldr r0, [r1, #0xc]
	cmp r7, r0
	beq _0225563A
	ldr r0, [sp]
	add r1, #0x14
	bl MailMsg_compare
_0225563A:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD51_022555C0

	thumb_func_start MOD51_02255640
MOD51_02255640: ; 0x02255640
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r1, #0x9e
	add r4, r0, #0
	lsl r1, r1, #2
	ldrh r0, [r4, r1]
	sub r1, r1, #4
	ldrh r1, [r4, r1]
	mov r5, #0
	sub r1, r1, #3
	cmp r0, r1
	bne _0225565A
	mov r5, #1
_0225565A:
	add r1, r3, #0
	add r0, r4, #0
	add r3, r6, #0
	bl MOD51_022554E0
	ldr r1, _0225568C ; =0x0000027A
	ldrh r0, [r4, r1]
	cmp r0, #0
	beq _02255682
	cmp r5, #0
	beq _02255682
	add r0, r1, #0
	sub r0, #0xa
	ldr r2, [r4, r0]
	add r0, r1, #0
	add r0, #0xce
	ldr r0, [r2, r0]
	sub r2, r0, #3
	sub r0, r1, #2
	strh r2, [r4, r0]
_02255682:
	add r0, r4, #0
	bl MOD51_0225571C
	pop {r4, r5, r6, pc}
	nop
_0225568C: .word 0x0000027A
	thumb_func_end MOD51_02255640

	thumb_func_start MOD51_02255690
MOD51_02255690: ; 0x02255690
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp]
	ldr r0, [r0, #0xc]
	bl FUN_0204646C
	cmp r0, #0
	bne _02255714
	mov r0, #4
	bl PlayerProfile_new
	str r0, [sp, #4]
	mov r6, #0
_022556AA:
	add r0, r6, #0
	bl FUN_0202EF18
	add r7, r0, #0
	beq _022556E6
	add r4, r7, #0
	add r4, #0x50
	ldr r0, _02255718 ; =0x02255800
	add r5, r4, #0
	add r5, #8
	str r4, [r0, #4]
	str r5, [r0]
	add r0, r4, #0
	ldr r1, [sp, #4]
	add r0, #0x10
	bl PlayerProfile_Copy
	ldr r0, [sp]
	ldr r2, [r7, #0x50]
	add r1, r5, #0
	bl MOD51_022555C0
	cmp r0, #0
	beq _022556E6
	ldr r0, [sp]
	ldr r1, [sp, #4]
	ldr r3, [r4]
	add r2, r5, #0
	bl MOD51_02255640
_022556E6:
	add r6, r6, #1
	cmp r6, #0x10
	blt _022556AA
	ldr r0, [sp]
	ldr r0, [r0, #8]
	bl FUN_02052CF0
	add r4, r0, #0
	beq _0225570E
	ldr r0, [sp]
	ldr r0, [r0, #0x10]
	bl PlayerProfile_GetTrainerID
	add r3, r0, #0
	ldr r0, [sp]
	add r2, r4, #0
	add r1, r0, #0
	ldr r1, [r1, #0x10]
	bl MOD51_02255640
_0225570E:
	ldr r0, [sp, #4]
	bl FreeToHeap
_02255714:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02255718: .word MOD51_02255800
	thumb_func_end MOD51_02255690

	thumb_func_start MOD51_0225571C
MOD51_0225571C: ; 0x0225571C
	mov r1, #0xa1
	mov r2, #1
	lsl r1, r1, #2
	str r2, [r0, r1]
	bx lr
	.align 2, 0
	thumb_func_end MOD51_0225571C

	.rodata
	.global MOD51_02255728
MOD51_02255728: ; 0x02255728
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00

	.global MOD51_02255734
MOD51_02255734: ; 0x02255734
	.byte 0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD51_02255740
MOD51_02255740: ; 0x02255740
	.byte 0x30, 0x90, 0xE8, 0x00, 0x00, 0x40, 0x00, 0xE8, 0x40, 0x80, 0x00, 0xE8, 0x80, 0xC0, 0x00, 0xE8
	.byte 0xFF, 0x00, 0x00, 0x00

	.global MOD51_02255754
MOD51_02255754: ; 0x02255754
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0F, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD51_02255770
MOD51_02255770: ; 0x02255770
	.byte 0x00, 0x20, 0xE8, 0xF8, 0xA0, 0x20, 0xE8, 0xF8, 0x00, 0x40, 0x00, 0xE8, 0x40, 0x80, 0x00, 0xE8
	.byte 0x80, 0xC0, 0x00, 0xE8, 0x30, 0x90, 0xE8, 0x00, 0xFF, 0x00, 0x00, 0x00

	.global MOD51_0225578C
MOD51_0225578C: ; 0x0225578C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0D, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD51_022557A8
MOD51_022557A8: ; 0x022557A8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0C, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD51_022557C4
MOD51_022557C4: ; 0x022557C4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.data
	.bss
	.global MOD51_02255800
MOD51_02255800: ; 0x02255800
	.space 0x4

