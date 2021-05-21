	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD59_021D9868
MOD59_021D9868: ; 0x021D9868
	push {r4, lr}
	mov r2, #1
	add r4, r0, #0
	mov r0, #3
	mov r1, #0x53
	lsl r2, r2, #0x12
	bl FUN_0201681C
	add r0, r4, #0
	mov r1, #0x28
	mov r2, #0x53
	bl OverlayManager_CreateAndGetData
	mov r1, #0
	mov r2, #0x28
	add r4, r0, #0
	bl memset
	mov r0, #0x53
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #0x24]
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD59_021D9868

	thumb_func_start MOD59_021D9898
MOD59_021D9898: ; 0x021D9898
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	bl OverlayManager_GetData
	ldr r1, [r5]
	add r4, r0, #0
	mov r6, #0
	cmp r1, #5
	bls _021D98AE
	b _021D99E2
_021D98AE:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D98BA: ; jump table
	.short _021D98C6 - _021D98BA - 2 ; case 0
	.short _021D992C - _021D98BA - 2 ; case 1
	.short _021D9952 - _021D98BA - 2 ; case 2
	.short _021D997C - _021D98BA - 2 ; case 3
	.short _021D998E - _021D98BA - 2 ; case 4
	.short _021D99C0 - _021D98BA - 2 ; case 5
_021D98C6:
	add r0, r6, #0
	add r1, r6, #0
	bl FUN_0200E3A0
	mov r0, #1
	add r1, r6, #0
	bl FUN_0200E3A0
	add r0, r6, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	add r0, r6, #0
	add r1, r0, #0
	bl FUN_02015F34
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D99E8 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D99EC ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	add r0, r4, #0
	bl MOD59_021D9A20
	add r0, r4, #0
	bl MOD59_021D9C48
	ldr r0, _021D99F0 ; =MOD59_021D9A14
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	bl GX_BothDispOn
	mov r0, #0x3c
	str r0, [r4, #0x24]
	mov r0, #1
	str r0, [r5]
	b _021D99E2
_021D992C:
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _021D9938
	sub r0, r0, #1
	str r0, [r4, #0x24]
	b _021D99E2
_021D9938:
	ldr r0, _021D99F4 ; =0x00000406
	bl FUN_0200414C
	ldr r1, _021D99F4 ; =0x00000406
	mov r0, #4
	mov r2, #1
	bl FUN_0200433C
	mov r0, #0x5a
	str r0, [r4, #0x24]
	mov r0, #2
	str r0, [r5]
	b _021D99E2
_021D9952:
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _021D995E
	sub r0, r0, #1
	str r0, [r4, #0x24]
	b _021D99E2
_021D995E:
	str r6, [r4, #0x24]
	mov r0, #6
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	str r0, [sp, #8]
	add r0, r6, #0
	add r3, r6, #0
	bl FUN_0200E1D0
	mov r0, #3
	str r0, [r5]
	b _021D99E2
_021D997C:
	bl MOD59_021D9D78
	bl FUN_0200E308
	cmp r0, #1
	bne _021D99E2
	mov r0, #4
	str r0, [r5]
	b _021D99E2
_021D998E:
	bl MOD59_021D9D78
	add r0, r4, #0
	add r1, r6, #0
	mov r2, #0x28
	mov r3, #0x30
	bl MOD59_021D9C74
	cmp r0, #1
	bne _021D99E2
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	str r0, [sp, #8]
	add r0, r6, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #5
	str r0, [r5]
	b _021D99E2
_021D99C0:
	bl MOD59_021D9D78
	bl FUN_0200E308
	cmp r0, #1
	bne _021D99E2
	add r0, r4, #0
	bl MOD59_021D9C68
	add r0, r4, #0
	bl MOD59_021D9BD0
	add r0, r6, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r6, #1
_021D99E2:
	add r0, r6, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021D99E8: .word 0xFFFFE0FF
_021D99EC: .word 0x04001000
_021D99F0: .word MOD59_021D9A14
_021D99F4: .word 0x00000406
	thumb_func_end MOD59_021D9898

	thumb_func_start MOD59_021D99F8
MOD59_021D99F8: ; 0x021D99F8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	ldr r4, [r0]
	add r0, r5, #0
	bl OverlayManager_FreeData
	add r0, r4, #0
	bl FUN_020168D0
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD59_021D99F8

	thumb_func_start MOD59_021D9A14
MOD59_021D9A14: ; 0x021D9A14
	ldr r3, _021D9A1C ; =FUN_0201AB60
	ldr r0, [r0, #4]
	bx r3
	nop
_021D9A1C: .word FUN_0201AB60
	thumb_func_end MOD59_021D9A14

	thumb_func_start MOD59_021D9A20
MOD59_021D9A20: ; 0x021D9A20
	push {r3, r4, r5, lr}
	sub sp, #0xb8
	ldr r5, _021D9BB4 ; =0x021DA0D4
	add r4, r0, #0
	add r3, sp, #0x90
	mov r2, #5
_021D9A2C:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D9A2C
	add r0, sp, #0x90
	bl GX_SetBanks
	ldr r0, [r4]
	bl FUN_02016B94
	add r3, sp, #0x80
	ldr r5, _021D9BB8 ; =0x021DA054
	str r0, [r4, #4]
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _021D9BBC ; =0x021DA080
	add r3, sp, #0x64
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
	ldr r0, [r4, #4]
	mov r3, #0
	bl FUN_02016C18
	ldr r3, [r4]
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_02018744
	ldr r5, _021D9BC0 ; =0x021DA09C
	add r3, sp, #0x48
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
	ldr r0, [r4, #4]
	add r3, r1, #0
	bl FUN_02016C18
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	ldr r0, [r4]
	mov r1, #1
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x88
	bl FUN_0200687C
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	ldr r0, [r4]
	mov r1, #4
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x88
	bl FUN_020068C8
	ldr r5, _021D9BC4 ; =0x021DA064
	add r3, sp, #0x2c
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
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #2
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x88
	mov r3, #1
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #5
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x88
	mov r3, #1
	bl FUN_020068C8
	ldr r5, _021D9BC8 ; =0x021DA0B8
	add r3, sp, #0x10
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
	ldr r0, [r4, #4]
	mov r3, #0
	bl FUN_02016C18
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	ldr r0, [r4]
	mov r3, #3
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x88
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #3
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x88
	add r3, r1, #0
	bl FUN_020068C8
	mov r2, #0
	str r2, [sp]
	ldr r0, [r4]
	mov r1, #6
	str r0, [sp, #4]
	mov r0, #0x88
	add r3, r2, #0
	bl FUN_02006930
	ldr r2, [r4]
	mov r0, #0
	mov r1, #0x20
	bl FUN_02002ED0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02017FE4
	mov r0, #4
	mov r1, #0
	bl FUN_02017FE4
	mov r2, #0xc
	ldr r0, _021D9BCC ; =0x04000050
	mov r1, #2
	mov r3, #4
	str r2, [sp]
	bl G2x_SetBlendAlpha_
	add sp, #0xb8
	pop {r3, r4, r5, pc}
	nop
_021D9BB4: .word MOD59_021DA0D4
_021D9BB8: .word MOD59_021DA054
_021D9BBC: .word MOD59_021DA080
_021D9BC0: .word MOD59_021DA09C
_021D9BC4: .word MOD59_021DA064
_021D9BC8: .word MOD59_021DA0B8
_021D9BCC: .word 0x04000050
	thumb_func_end MOD59_021D9A20

	thumb_func_start MOD59_021D9BD0
MOD59_021D9BD0: ; 0x021D9BD0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_0201797C
	mov r0, #1
	mov r1, #0
	bl FUN_0201797C
	mov r0, #2
	mov r1, #0
	bl FUN_0201797C
	mov r0, #3
	mov r1, #0
	bl FUN_0201797C
	mov r0, #4
	mov r1, #0
	bl FUN_0201797C
	mov r0, #5
	mov r1, #0
	bl FUN_0201797C
	mov r0, #6
	mov r1, #0
	bl FUN_0201797C
	mov r0, #7
	mov r1, #0
	bl FUN_0201797C
	ldr r0, _021D9C44 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	ldr r0, [r4, #4]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #0
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #4]
	bl FreeToHeap
	pop {r4, pc}
	nop
_021D9C44: .word 0x04000050
	thumb_func_end MOD59_021D9BD0

	thumb_func_start MOD59_021D9C48
MOD59_021D9C48: ; 0x021D9C48
	push {r4, lr}
	add r4, r0, #0
	ldr r2, _021D9C64 ; =0x00000225
	ldr r3, [r4]
	mov r0, #1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	str r0, [r4, #8]
	bl FUN_0201BD5C
	mov r0, #0
	str r0, [r4, #0xc]
	pop {r4, pc}
	.align 2, 0
_021D9C64: .word 0x00000225
	thumb_func_end MOD59_021D9C48

	thumb_func_start MOD59_021D9C68
MOD59_021D9C68: ; 0x021D9C68
	ldr r3, _021D9C70 ; =DestroyMsgData
	ldr r0, [r0, #8]
	bx r3
	nop
_021D9C70: .word DestroyMsgData
	thumb_func_end MOD59_021D9C68

	thumb_func_start MOD59_021D9C74
MOD59_021D9C74: ; 0x021D9C74
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	str r1, [sp, #0x10]
	add r7, r3, #0
	mov r5, #0
	cmp r0, #3
	bhi _021D9D66
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9C92: ; jump table
	.short _021D9C9A - _021D9C92 - 2 ; case 0
	.short _021D9D24 - _021D9C92 - 2 ; case 1
	.short _021D9D36 - _021D9C92 - 2 ; case 2
	.short _021D9D50 - _021D9C92 - 2 ; case 3
_021D9C9A:
	mov r0, #2
	add r1, r5, #0
	bl FUN_0201797C
	mov r0, #1
	ldr r1, [r4]
	lsl r0, r0, #0xa
	bl String_ctor
	add r6, r0, #0
	ldr r0, [r4, #8]
	ldr r1, [sp, #0x10]
	add r2, r6, #0
	bl ReadMsgDataIntoString
	add r1, r4, #0
	ldr r0, [r4, #4]
	ldr r2, _021D9D6C ; =0x021DA04C
	add r1, #0x10
	bl FUN_02019150
	add r1, r5, #0
	mov r0, #1
	lsl r0, r0, #8
	str r0, [sp]
	mov r0, #0xc0
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x10
	add r2, r1, #0
	add r3, r1, #0
	bl FillWindowPixelRect
	add r0, r5, #0
	add r1, r6, #0
	add r2, r0, #0
	bl FUN_02002F08
	mov r1, #1
	lsl r1, r1, #8
	sub r0, r1, r0
	lsr r3, r0, #1
	str r7, [sp]
	add r1, r5, #0
	ldr r0, _021D9D70 ; =0x000F0200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x10
	add r2, r6, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	add r0, #0x10
	bl CopyWindowToVram
	mov r0, #2
	mov r1, #1
	bl FUN_0201797C
	mov r0, #0xf0
	str r0, [r4, #0x24]
	mov r0, #1
	str r0, [r4, #0xc]
	b _021D9D66
_021D9D24:
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _021D9D30
	sub r0, r0, #1
	str r0, [r4, #0x24]
	b _021D9D66
_021D9D30:
	mov r0, #2
	str r0, [r4, #0xc]
	b _021D9D66
_021D9D36:
	ldr r0, _021D9D74 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	and r0, r1
	cmp r0, #1
	beq _021D9D4A
	mov r0, #2
	and r0, r1
	cmp r0, #2
	bne _021D9D66
_021D9D4A:
	mov r0, #3
	str r0, [r4, #0xc]
	b _021D9D66
_021D9D50:
	add r0, r4, #0
	add r0, #0x10
	bl FUN_02019178
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_02018744
	add r0, r5, #0
	str r0, [r4, #0xc]
	mov r5, #1
_021D9D66:
	add r0, r5, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D9D6C: .word MOD59_021DA04C
_021D9D70: .word 0x000F0200
_021D9D74: .word gMain
	thumb_func_end MOD59_021D9C74

	thumb_func_start MOD59_021D9D78
MOD59_021D9D78: ; 0x021D9D78
	push {r3, lr}
	ldr r1, [r0, #0x20]
	mov r2, #3
	add r3, r1, #4
	str r3, [r0, #0x20]
	ldr r0, [r0, #4]
	mov r1, #1
	asr r3, r3, #4
	bl FUN_020179E0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD59_021D9D78

	.rodata

	.global MOD59_021DA04C
MOD59_021DA04C: ; 0x021DA04C
	.byte 0x02, 0x00, 0x00, 0x20, 0x18, 0x01, 0x01, 0x00

	.global MOD59_021DA054
MOD59_021DA054: ; 0x021DA054
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD59_021DA064
MOD59_021DA064: ; 0x021DA064
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x02, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD59_021DA080
MOD59_021DA080: ; 0x021DA080
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD59_021DA09C
MOD59_021DA09C: ; 0x021DA09C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x01, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD59_021DA0B8
MOD59_021DA0B8: ; 0x021DA0B8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x03, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD59_021DA0D4
MOD59_021DA0D4: ; 0x021DA0D4
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
