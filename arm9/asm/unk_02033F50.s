	.include "asm/macros.inc"
    .include "global.inc"

	.extern gMain

	.section .rodata

	.global UNK_020EEC9C
UNK_020EEC9C: ; 0x020EEC9C
	.byte 0x00, 0x03, 0x03, 0x1A, 0x12, 0x01, 0x23, 0x00

	.global UNK_020EECA4
UNK_020EECA4: ; 0x020EECA4
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020EECB4
UNK_020EECB4: ; 0x020EECB4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020EECD0
UNK_020EECD0: ; 0x020EECD0
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_02033F50
FUN_02033F50: ; 0x02033F50
	ldr r3, _02033F64 ; =0x027E0000
	ldr r1, _02033F68 ; =0x00003FF8
	mov r0, #0x1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	ldr r3, _02033F6C ; =MI_WaitDma
	mov r0, #0x3
	bx r3
	nop
_02033F64: .word 0x027E0000
_02033F68: .word 0x00003FF8
_02033F6C: .word MI_WaitDma

	thumb_func_start FUN_02033F70
FUN_02033F70: ; 0x02033F70
	push {r3-r7, lr}
	sub sp, #0x28
	add r4, r0, #0x0
	str r2, [sp, #0xc]
	cmp r1, #0x4
	bhi _02033F92
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02033F88: ; jump table (using 16-bit offset)
	.short _02033F92 - _02033F88 - 2; case 0
	.short _02033F96 - _02033F88 - 2; case 1
	.short _02033F9A - _02033F88 - 2; case 2
	.short _02033F9E - _02033F88 - 2; case 3
	.short _02033FA2 - _02033F88 - 2; case 4
_02033F92:
	mov r5, #0x1
	b _02033FA4
_02033F96:
	mov r5, #0x2
	b _02033FA4
_02033F9A:
	mov r5, #0x3
	b _02033FA4
_02033F9E:
	mov r5, #0x4
	b _02033FA4
_02033FA2:
	mov r5, #0x5
_02033FA4:
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	bl OS_DisableIrqMask
	ldr r1, _02034154 ; =FUN_02033F50
	mov r0, #0x1
	bl OS_SetIrqFunction
	mov r0, #0x1
	bl OS_EnableIrqMask
	mov r0, #0x0
	add r1, r0, #0x0
	bl Main_SetVBlankIntrCB
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F34
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r2, #0x0]
	ldr r0, _02034158 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _0203415C ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl FUN_0201669C
	ldr r0, _02034160 ; =gMain + 0x60
	mov r1, #0x0
	strb r1, [r0, #0x5]
	bl GX_SwapDisplay
	ldr r3, _02034164 ; =0x04000050
	mov r1, #0x0
	strh r1, [r3, #0x0]
	ldr r0, _02034168 ; =0x04001050
	sub r3, #0x50
	strh r1, [r0, #0x0]
	ldr r2, [r3, #0x0]
	ldr r1, _0203416C ; =0xFFFF1FFF
	sub r0, #0x50
	and r2, r1
	str r2, [r3, #0x0]
	ldr r2, [r0, #0x0]
	and r1, r2
	str r1, [r0, #0x0]
	ldr r0, _02034170 ; =UNK_020EECD0
	bl GX_SetBanks
	add r0, r4, #0x0
	bl FUN_02016B94
	add r6, r0, #0x0
	ldr r0, _02034174 ; =UNK_020EECA4
	bl FUN_02016BBC
	mov r1, #0x0
	ldr r2, _02034178 ; =UNK_020EECB4
	add r0, r6, #0x0
	add r3, r1, #0x0
	bl FUN_02016C18
	add r0, r6, #0x0
	mov r1, #0x0
	bl FUN_02018744
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r2, _0203417C ; =0x000001F7
	add r0, r6, #0x0
	mov r3, #0x2
	str r4, [sp, #0x4]
	bl FUN_0200CB00
	mov r0, #0x0
	mov r1, #0x20
	add r2, r4, #0x0
	bl FUN_02002ED0
	mov r0, #0x0
	mov r1, #0x20
	add r2, r0, #0x0
	add r3, r4, #0x0
	bl FUN_02017F18
	ldr r1, _02034180 ; =0x00006C21
	mov r0, #0x0
	bl FUN_02017FE4
	ldr r1, _02034180 ; =0x00006C21
	mov r0, #0x4
	bl FUN_02017FE4
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0xc8
	add r3, r4, #0x0
	bl NewMsgDataFromNarc
	str r0, [sp, #0x10]
	mov r0, #0x6
	lsl r0, r0, #0x6
	add r1, r4, #0x0
	bl String_ctor
	add r7, r0, #0x0
	mov r0, #0x6
	lsl r0, r0, #0x6
	add r1, r4, #0x0
	bl String_ctor
	str r0, [sp, #0x14]
	bl FUN_0201BD5C
	add r0, r4, #0x0
	bl ScrStrBufs_new
	add r4, r0, #0x0
	ldr r2, _02034184 ; =UNK_020EEC9C
	add r0, r6, #0x0
	add r1, sp, #0x18
	bl FUN_02019150
	mov r0, #0xd0
	str r0, [sp, #0x0]
	mov r0, #0x90
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0x18
	mov r1, #0xf
	add r3, r2, #0x0
	bl FillWindowPixelRect
	ldr r2, _0203417C ; =0x000001F7
	add r0, sp, #0x18
	mov r1, #0x0
	mov r3, #0x2
	bl FUN_0200CCA4
	mov r0, #0x2
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r2, [sp, #0xc]
	add r0, r4, #0x0
	mov r1, #0x0
	mov r3, #0x5
	bl BufferIntegerAsString
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x14]
	add r1, r5, #0x0
	bl ReadMsgDataIntoString
	ldr r2, [sp, #0x14]
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl StringExpandPlaceholders
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	add r0, sp, #0x18
	add r2, r7, #0x0
	add r3, r1, #0x0
	str r1, [sp, #0x8]
	bl AddTextPrinterParameterized
	add r0, r7, #0x0
	bl String_dtor
	bl GX_BothDispOn
	mov r0, #0x0
	bl FUN_0200E394
	mov r0, #0x1
	bl FUN_0200E394
	mov r0, #0x0
	mov r1, #0x3f
	mov r2, #0x3
	bl FUN_0200A274
	add r0, sp, #0x18
	bl FUN_02019178
	ldr r0, [sp, #0x10]
	bl DestroyMsgData
	add r0, r4, #0x0
	bl ScrStrBufs_delete
	add r0, r6, #0x0
	bl FreeToHeap
	add sp, #0x28
	pop {r3-r7, pc}
	nop
_02034154: .word FUN_02033F50
_02034158: .word 0xFFFFE0FF
_0203415C: .word 0x04001000
_02034160: .word gMain + 0x60
_02034164: .word 0x04000050
_02034168: .word 0x04001050
_0203416C: .word 0xFFFF1FFF
_02034170: .word UNK_020EECD0
_02034174: .word UNK_020EECA4
_02034178: .word UNK_020EECB4
_0203417C: .word 0x000001F7
_02034180: .word 0x00006C21
_02034184: .word UNK_020EEC9C
