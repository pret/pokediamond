	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

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
	bl GX_SetBanks
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
	bl GX_SetBanks
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
	bl GX_SetBanks
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
	ldr r5, _021D8BBC ; =MOD63_021DBB6C
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
	ldr r5, _021D8BC4 ; =MOD63_021DBCF8
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
	ldr r5, _021D8BC8 ; =MOD63_021DBD14
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
	ldr r5, _021D8BCC ; =MOD63_021DBD30
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
	ldr r5, _021D8BD0 ; =MOD63_021DBBA8
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
	ldr r5, _021D8BD4 ; =MOD63_021DBBE0
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
_021D8BBC: .word MOD63_021DBB6C
_021D8BC0: .word 0xC7FFFFFF
_021D8BC4: .word MOD63_021DBCF8
_021D8BC8: .word MOD63_021DBD14
_021D8BCC: .word MOD63_021DBD30
_021D8BD0: .word MOD63_021DBBA8
_021D8BD4: .word MOD63_021DBBE0
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
	ldr r3, _021D8C18 ; =NNS_GfdDefaultFuncAllocTexVram
	mov r0, #2
	mov r1, #0
	ldr r3, [r3]
	lsl r0, r0, #0xe
	add r2, r1, #0
	blx r3
	ldr r3, _021D8C1C ; =NNS_GfdDefaultFuncAllocPlttVram
	mov r0, #0x80
	ldr r3, [r3]
	mov r1, #0
	mov r2, #1
	blx r3
	add sp, #8
	pop {r4, pc}
	nop
_021D8C14: .word MOD63_021D8C20
_021D8C18: .word NNS_GfdDefaultFuncAllocTexVram
_021D8C1C: .word NNS_GfdDefaultFuncAllocPlttVram
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
	ldr r0, _021D8C98 ; =MOD63_021DBB5C
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
_021D8C98: .word MOD63_021DBB5C
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
	bl Main_SetVBlankIntrCB
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F34
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r0, #4
	mov r1, #8
	bl SetKeyRepeatTimers
	mov r0, #3
	mov r1, #0x4c
	lsl r2, r0, #0x11
	bl CreateHeap
	mov r1, #0xab
	add r0, r4, #0
	lsl r1, r1, #2
	mov r2, #0x4c
	bl OverlayManager_CreateAndGetData
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
	ldr r0, _021D8D94 ; =gMain + 0x60
	strb r1, [r0, #5]
	bl GX_SwapDisplay
	bl GetLCRNGSeed
	str r0, [r4, #0x14]
	mov r0, #0
	bl SetLCRNGSeed
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_021D8D90: .word 0x00007FFF
_021D8D94: .word gMain + 0x60
	thumb_func_end MOD63_021D8D10

	thumb_func_start MOD63_021D8D98
MOD63_021D8D98: ; 0x021D8D98
	push {r3, r4, r5, lr}
	add r4, r1, #0
	bl OverlayManager_GetData
	add r5, r0, #0
	mov r0, #0xaa
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	cmp r0, #0
	beq _021D8DD4
	ldr r0, _021D8E5C ; =gMain
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
	ldr r1, _021D8E5C ; =gMain
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
	bl GF_AssertFail
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
_021D8E5C: .word gMain
_021D8E60: .word 0x00007FFF
_021D8E64: .word 0x00000A8C
	thumb_func_end MOD63_021D8D98

	thumb_func_start MOD63_021D8E68
MOD63_021D8E68: ; 0x021D8E68
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	bl FUN_0200E31C
	ldr r0, [r4, #0x14]
	bl SetLCRNGSeed
	add r0, r5, #0
	bl OverlayManager_FreeData
	mov r0, #0x4c
	bl DestroyHeap
	ldr r0, _021D8E94 ; =SDK_OVERLAY_MODULE_63_ID
	ldr r1, _021D8E98 ; =MOD63_021DBAB8
	bl RegisterMainOverlay
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8E94: .word SDK_OVERLAY_MODULE_63_ID
_021D8E98: .word MOD63_021DBAB8
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
	bl Main_SetVBlankIntrCB
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
	bl GfGfxLoader_LoadCharData
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
	bl GfGfxLoader_LoadCharData
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
	bl GfGfxLoader_LoadScrnData
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
	bl GfGfxLoader_LoadScrnData
	mov r2, #0
	str r2, [sp]
	mov r0, #0x4c
	str r0, [sp, #4]
	mov r0, #0x80
	mov r1, #0x12
	add r3, r2, #0
	bl GfGfxLoader_GXLoadPal
	mov r3, #0
	str r3, [sp]
	mov r0, #0x4c
	str r0, [sp, #4]
	mov r0, #0x80
	mov r1, #0x12
	mov r2, #4
	bl GfGfxLoader_GXLoadPal
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
	bl GfGfxLoader_LoadCharData
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
	bl GfGfxLoader_LoadScrnData
	mov r1, #0
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x4c
	str r0, [sp, #4]
	mov r0, #0x80
	add r2, r1, #0
	add r3, r1, #0
	bl GfGfxLoader_GXLoadPal
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
	bl GfGfxLoader_LoadScrnData
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
	bl GfGfxLoader_LoadScrnData
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
	bl GfGfxLoader_LoadCharData
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
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x4c
	str r0, [sp, #4]
	mov r0, #0x80
	mov r1, #0x47
	mov r2, #4
	mov r3, #0
	bl GfGfxLoader_GXLoadPal
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #0
	bl GX_EngineBToggleLayers
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
	bl GX_BothDispOn
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
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineBToggleLayers
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
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #1
	bl GX_EngineBToggleLayers
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
	bl Main_SetVBlankIntrCB
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
	bl GF_AssertFail
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
	bl Title_SetupMonAnimationSprites
	ldr r0, [r5, #0xc]
	mov r1, #1
	str r0, [r5, #0x40]
	ldr r0, _021D9588 ; =gMain + 0x60
	strb r1, [r0, #5]
	bl GX_SwapDisplay
	ldr r6, _021D958C ; =MOD63_021DBDE8
	ldr r7, _021D9590 ; =MOD63_021DBAD0
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
	bl NNS_G3dGlbLightVector
	lsl r1, r4, #1
	ldrh r1, [r7, r1]
	add r0, r4, #0
	bl NNS_G3dGlbLightColor
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021D950C
	ldr r0, _021D9594 ; =0x00004210
	ldr r1, _021D9598 ; =0x0000318A
	mov r2, #0
	bl NNS_G3dGlbMaterialColorDiffAmb
	ldr r0, _021D959C ; =0x00004A52
	ldr r1, _021D95A0 ; =0x000039CE
	mov r2, #0
	bl NNS_G3dGlbMaterialColorSpecEmi
	mov r0, #0x1f
	str r0, [sp]
	mov r0, #2
	lsl r0, r0, #0xe
	mov r1, #0
	str r0, [sp, #4]
	mov r0, #0xd
	mov r2, #2
	add r3, r1, #0
	bl NNS_G3dGlbPolygonAttr
	ldr r0, _021D95A4 ; =MOD63_021D8CB0
	add r1, r5, #0
	bl Main_SetVBlankIntrCB
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
_021D9588: .word gMain + 0x60
_021D958C: .word MOD63_021DBDE8
_021D9590: .word MOD63_021DBAD0
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
	bl Main_SetVBlankIntrCB
	pop {r4, r5, r6, pc}
	nop
_021D969C: .word 0xFFFF1FFF
	thumb_func_end MOD63_021D95A8

	thumb_func_start MOD63_021D96A0
MOD63_021D96A0: ; 0x021D96A0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	ldr r3, _021D980C ; =MOD63_021DBB2C
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
	bl NNS_G2dGetUnpackedPaletteData
	cmp r0, #0
	bne _021D96F8
	ldr r0, [r6, #0x2c]
	bl FreeToHeap
	bl GF_AssertFail
	b _021D96F8
_021D96F4:
	bl GF_AssertFail
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
	bl GfGfxLoader_LoadCharData
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
	bl GfGfxLoader_LoadScrnData
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
	bl GfGfxLoader_LoadCharData
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
	bl GfGfxLoader_LoadScrnData
	mov r0, #1
	lsl r0, r0, #8
	str r0, [sp]
	mov r0, #0x4c
	str r0, [sp, #4]
	mov r0, #0x80
	mov r1, #0x10
	mov r2, #4
	mov r3, #0
	bl GfGfxLoader_GXLoadPal
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
	bl GfGfxLoader_LoadCharData
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
	bl GfGfxLoader_LoadScrnData
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
	bl GfGfxLoader_LoadScrnData
	ldr r0, [r5, #0x10]
	bl MOD63_021DA6E8
	ldr r0, [r5, #0x10]
	bl MOD63_021DAA5C
	ldr r0, [r5, #0x10]
	ldr r1, [r5, #0x14]
	bl MOD63_021DABCC
	mov r0, #0xe
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #1
	mov r1, #0
	bl GX_EngineBToggleLayers
	mov r0, #0
	bl FUN_0200E394
	mov r0, #1
	bl FUN_0200E394
	mov r0, #1
	strb r0, [r5, #3]
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D980C: .word MOD63_021DBB2C
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
	bl NNS_G3dGetTex
	str r0, [r5, #0x40]
	bl FUN_0201B3C4
	cmp r0, #0
	bne _021D9834
	bl GF_AssertFail
_021D9834:
	ldr r0, [r5, #0x40]
	ldr r0, [r0, #0x14]
	cmp r0, #0
	bne _021D9840
	bl GF_AssertFail
_021D9840:
	ldr r2, [r5, #0x40]
	ldr r0, [r5, #0x3c]
	ldr r1, [r2, #0x14]
	add r1, r2, r1
	sub r1, r1, r0
	bl ReallocFromHeap
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
	ldr r1, _021D9964 ; =MOD63_021DBB90
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
	bl GF_AssertFail
_021D9890:
	add r0, r5, r6
	add r0, #0x9c
	ldr r0, [r0]
	bl NNS_G3dGetMdlSet
	ldrb r0, [r0, #9]
	cmp r0, #1
	beq _021D98A4
	bl GF_AssertFail
_021D98A4:
	add r0, r5, r6
	add r0, #0x9c
	ldr r0, [r0]
	bl NNS_G3dGetMdlSet
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r4, r0, r1
	bne _021D98BC
	bl GF_AssertFail
_021D98BC:
	ldr r0, [sp, #0x10]
	add r1, r4, #0
	add r0, r0, r6
	bl NNS_G3dRenderObjInit
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x40
	bl NNSi_G3dModifyMatFlag
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x80
	bl NNSi_G3dModifyMatFlag
	mov r2, #2
	add r0, r4, #0
	mov r1, #0
	lsl r2, r2, #8
	bl NNSi_G3dModifyMatFlag
	mov r2, #1
	add r0, r4, #0
	mov r1, #0
	lsl r2, r2, #0xa
	bl NNSi_G3dModifyMatFlag
	add r0, r4, #0
	mov r1, #0
	mov r2, #0xf
	bl NNSi_G3dModifyPolygonAttrMask
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
	ldr r4, _021D9968 ; =MOD63_021DBAE4
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
	ldr r2, _021D9974 ; =MOD63_021DBB80
	bl FUN_0201ECA8
	ldr r0, _021D9978 ; =0x00000981
	ldr r1, [r5, #0x44]
	bl FUN_0201EEF0
	ldr r4, _021D997C ; =MOD63_021DBB08
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
_021D9964: .word MOD63_021DBB90
_021D9968: .word MOD63_021DBAE4
_021D996C: .word 0x0029AEC1
_021D9970: .word 0x000005C1
_021D9974: .word MOD63_021DBB80
_021D9978: .word 0x00000981
_021D997C: .word MOD63_021DBB08
	thumb_func_end MOD63_021D9810

	thumb_func_start MOD63_021D9980
MOD63_021D9980: ; 0x021D9980
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	ldr r4, _021D99E4 ; =MOD63_021DBD4C
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
	ldr r3, _021D99E8 ; =MOD63_021DBAFC
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
_021D99E4: .word MOD63_021DBD4C
_021D99E8: .word MOD63_021DBAFC
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
	bl GX_EngineBToggleLayers
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
	bl GX_EngineBToggleLayers
_021D9A88:
	ldr r0, _021D9DD0 ; =0x000003C5
	cmp r5, r0
	blt _021D9B0C
	mov r0, #7
	mov r1, #1
	bl GX_EngineAToggleLayers
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
	bl GX_EngineAToggleLayers
	mov r0, #8
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
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
	bl GX_EngineAToggleLayers
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
	bl GX_EngineAToggleLayers
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
	ldr r5, _021DA084 ; =MOD63_021DBAD8
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
	ldr r2, _021DA08C ; =MOD63_021DBB80
	bl FUN_0201ECA8
	ldr r5, _021DA090 ; =MOD63_021DBB20
	add r3, sp, #0x2c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	ldr r1, [r4, #0x44]
	add r0, r2, #0
	bl FUN_0201EF70
	ldr r2, _021DA094 ; =MOD63_021DBAC8
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
	ldr r6, _021DA09C ; =MOD63_021DBB14
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
	ldr r2, _021DA08C ; =MOD63_021DBB80
	bl FUN_0201ECA8
	ldr r0, _021DA07C ; =0x000005C1
	ldr r1, [r4, #0x44]
	bl FUN_0201EEF0
	ldr r5, _021DA0A0 ; =MOD63_021DBAF0
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
_021DA084: .word MOD63_021DBAD8
_021DA088: .word 0x0029AEC1
_021DA08C: .word MOD63_021DBB80
_021DA090: .word MOD63_021DBB20
_021DA094: .word MOD63_021DBAC8
_021DA098: .word 0x0000057D
_021DA09C: .word MOD63_021DBB14
_021DA0A0: .word MOD63_021DBAF0
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
	bl NNS_G2dGetUnpackedPaletteData
	cmp r0, #0
	bne _021DA192
	ldr r0, [r4, #0x14]
	bl FreeToHeap
	bl GF_AssertFail
	b _021DA192
_021DA18E:
	bl GF_AssertFail
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
	bl GfGfxLoader_LoadCharData
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
	bl GfGfxLoader_LoadScrnData
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
	bl GfGfxLoader_LoadCharData
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
	bl GfGfxLoader_LoadScrnData
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
	bl GfGfxLoader_LoadCharData
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
	bl GfGfxLoader_LoadScrnData
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x3a
	bl GfGfxLoader_LoadCharData
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x80
	mov r1, #0x3f
	bl GfGfxLoader_LoadScrnData
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
	bl GfGfxLoader_LoadCharData
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
	bl GfGfxLoader_LoadScrnData
	mov r0, #0xe
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #1
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #1
	bl GX_EngineBToggleLayers
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
	ldr r3, _021DA59C ; =GX_EngineAToggleLayers
	add r0, r1, #0
	bx r3
	nop
_021DA59C: .word GX_EngineAToggleLayers
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
	ldr r0, _021DA634 ; =MOD63_021DBF40
	ldrb r1, [r4, #3]
	ldrb r0, [r0, r3]
	cmp r1, r0
	blo _021DA614
	mov r1, #0
	str r1, [sp]
	ldr r6, _021DA638 ; =MOD63_021DBF48
	ldr r0, [r5, #0x14]
	ldrb r3, [r6, r3]
	mov r2, #1
	lsl r3, r3, #0x1c
	lsr r3, r3, #0x18
	bl MOD63_021D9EA8
	mov r0, #0x20
	str r0, [sp]
	ldrb r6, [r4, #1]
	ldr r3, _021DA63C ; =MOD63_021DBF44
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
	ldr r3, _021DA63C ; =MOD63_021DBF44
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
	ldr r0, _021DA634 ; =MOD63_021DBF40
	ldrb r1, [r4, #3]
	ldrb r0, [r0]
	cmp r1, r0
	blo _021DA630
	mov r0, #1
	mov r1, #0
	bl GX_EngineAToggleLayers
_021DA630:
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021DA634: .word MOD63_021DBF40
_021DA638: .word MOD63_021DBF48
_021DA63C: .word MOD63_021DBF44
	thumb_func_end MOD63_021DA5A0

	.section .rodata

	.global MOD63_021DBAB8
MOD63_021DBAB8: ; 0x021DBAB8
	.word MOD63_021D74E0, MOD63_021D759C, MOD63_021D77B4, 0xFFFFFFFF

	.global MOD63_021DBAC8
MOD63_021DBAC8: ; 0x021DBAC8
	.byte 0x00, 0x00, 0x80, 0xF6, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBAD0
MOD63_021DBAD0: ; 0x021DBAD0
	.byte 0x18, 0x4B, 0x00, 0x00, 0x42, 0x30, 0xFF, 0x7F

	.global MOD63_021DBAD8
MOD63_021DBAD8: ; 0x021DBAD8
	.byte 0x00, 0x00, 0xF8, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0xE4, 0xFF

	.global MOD63_021DBAE4
MOD63_021DBAE4: ; 0x021DBAE4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00

	.global MOD63_021DBAF0
MOD63_021DBAF0: ; 0x021DBAF0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBAFC
MOD63_021DBAFC: ; 0x021DBAFC
	.byte 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global MOD63_021DBB08
MOD63_021DBB08: ; 0x021DBB08
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBB14
MOD63_021DBB14: ; 0x021DBB14
	.byte 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0xFF

	.global MOD63_021DBB20
MOD63_021DBB20: ; 0x021DBB20
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBB2C
MOD63_021DBB2C: ; 0x021DBB2C
	.byte 0x1D, 0x00, 0x00, 0x00
	.byte 0x1E, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00

	.global MOD63_021DBB3C
MOD63_021DBB3C: ; 0x021DBB3C
	.byte 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD63_021DBB4C
MOD63_021DBB4C: ; 0x021DBB4C
	.byte 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBB5C
MOD63_021DBB5C: ; 0x021DBB5C
	.byte 0x00, 0x00, 0x84, 0x10
	.byte 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10

	.global MOD63_021DBB6C
MOD63_021DBB6C: ; 0x021DBB6C
	.byte 0x01, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC1, 0xAE, 0x29, 0x00

	.global MOD63_021DBB80
MOD63_021DBB80: ; 0x021DBB80
	.byte 0x02, 0xD6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x05, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBB90
MOD63_021DBB90: ; 0x021DBB90
	.byte 0x40, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00
	.byte 0x44, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00

	.global MOD63_021DBBA8
MOD63_021DBBA8: ; 0x021DBBA8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x17, 0x03, 0x00, 0x02, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBBC4
MOD63_021DBBC4: ; 0x021DBBC4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBBE0
MOD63_021DBBE0: ; 0x021DBBE0
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
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBCF8
MOD63_021DBCF8: ; 0x021DBCF8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x03, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBD14
MOD63_021DBD14: ; 0x021DBD14
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x19, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBD30
MOD63_021DBD30: ; 0x021DBD30
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x01, 0x1B, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBD4C
MOD63_021DBD4C: ; 0x021DBD4C
	.byte 0x00, 0x10, 0x00, 0x00
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
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBDE8
MOD63_021DBDE8: ; 0x021DBDE8
	.byte 0x05, 0xF8, 0xFF, 0xFF, 0x24, 0xF2, 0xFF, 0xFF
	.byte 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global MOD63_021DBE18
MOD63_021DBE18: ; 0x021DBE18
	.word MOD63_021D8D10, MOD63_021D8D98, MOD63_021D8E68, 0xFFFFFFFF

	.section .data

	.global MOD63_021DBF40
MOD63_021DBF40: ; 0x021DBF40
	.byte 0x08, 0x06, 0x06, 0x04

	.global MOD63_021DBF44
MOD63_021DBF44: ; 0x021DBF44
	.byte 0x05, 0x04, 0x03, 0x01

	.global MOD63_021DBF48
MOD63_021DBF48: ; 0x021DBF48
	.byte 0x08, 0x07, 0x06, 0x00
