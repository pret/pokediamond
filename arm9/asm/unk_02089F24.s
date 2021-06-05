	.include "asm/macros.inc"
	.include "global.inc"

	.extern gMain
	.extern UNK_020FF3E4
	.extern UNK_020FF3EC
	.extern UNK_020FF3FC
	.extern UNK_020FF418

	.section .rodata

	.global UNK_020FF440
UNK_020FF440: ; 0x020FF440
	.byte 0x00, 0x03, 0x03, 0x1A, 0x12, 0x01, 0x23, 0x00

	.global UNK_020FF448
UNK_020FF448: ; 0x020FF448
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FF458
UNK_020FF458: ; 0x020FF458
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FF474
UNK_020FF474: ; 0x020FF474
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_02089F24
FUN_02089F24: ; 0x02089F24
	push {r3-r6, lr}
	sub sp, #0x1c
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0200E3A0
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
	ldr r0, _0208A088 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _0208A08C ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl SetKeyRepeatTimers
	ldr r0, _0208A090 ; =gMain + 0x60
	mov r1, #0x0
	strb r1, [r0, #0x5]
	bl GX_SwapDisplay
	ldr r3, _0208A094 ; =0x04000050
	mov r0, #0x0
	strh r0, [r3, #0x0]
	ldr r2, _0208A098 ; =0x04001050
	sub r3, #0x50
	strh r0, [r2, #0x0]
	ldr r1, [r3, #0x0]
	ldr r0, _0208A09C ; =0xFFFF1FFF
	sub r2, #0x50
	and r1, r0
	str r1, [r3, #0x0]
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	ldr r0, _0208A0A0 ; =UNK_020FF418
	bl GX_SetBanks
	add r0, r4, #0x0
	bl FUN_02016B94
	add r5, r0, #0x0
	ldr r0, _0208A0A4 ; =UNK_020FF3EC
	bl FUN_02016BBC
	mov r1, #0x0
	ldr r2, _0208A0A8 ; =UNK_020FF3FC
	add r0, r5, #0x0
	add r3, r1, #0x0
	bl FUN_02016C18
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02018744
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r2, _0208A0AC ; =0x000001F7
	add r0, r5, #0x0
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
	bl BG_ClearCharDataRange
	ldr r1, _0208A0B0 ; =0x00006C21
	mov r0, #0x0
	bl BG_SetMaskColor
	ldr r1, _0208A0B0 ; =0x00006C21
	mov r0, #0x4
	bl BG_SetMaskColor
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0x5
	add r3, r4, #0x0
	bl NewMsgDataFromNarc
	add r6, r0, #0x0
	mov r0, #0x6
	lsl r0, r0, #0x6
	add r1, r4, #0x0
	bl String_ctor
	add r4, r0, #0x0
	bl FUN_0201BD5C
	ldr r2, _0208A0B4 ; =UNK_020FF3E4
	add r0, r5, #0x0
	add r1, sp, #0xc
	bl AddWindow
	mov r0, #0xd0
	str r0, [sp, #0x0]
	mov r0, #0x90
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0xc
	mov r1, #0xf
	add r3, r2, #0x0
	bl FillWindowPixelRect
	ldr r2, _0208A0AC ; =0x000001F7
	add r0, sp, #0xc
	mov r1, #0x0
	mov r3, #0x2
	bl FUN_0200CCA4
	add r0, r6, #0x0
	mov r1, #0x1
	add r2, r4, #0x0
	bl ReadMsgDataIntoString
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	add r0, sp, #0xc
	add r2, r4, #0x0
	add r3, r1, #0x0
	str r1, [sp, #0x8]
	bl AddTextPrinterParameterized
	add r0, r4, #0x0
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
	mov r4, #0x1
_0208A078:
	bl HandleDSLidAction
	add r0, r4, #0x0
	add r1, r4, #0x0
	bl OS_WaitIrq
	b _0208A078
	nop
_0208A088: .word 0xFFFFE0FF
_0208A08C: .word 0x04001000
_0208A090: .word gMain + 0x60
_0208A094: .word 0x04000050
_0208A098: .word 0x04001050
_0208A09C: .word 0xFFFF1FFF
_0208A0A0: .word UNK_020FF418
_0208A0A4: .word UNK_020FF3EC
_0208A0A8: .word UNK_020FF3FC
_0208A0AC: .word 0x000001F7
_0208A0B0: .word 0x00006C21
_0208A0B4: .word UNK_020FF3E4

	thumb_func_start FUN_0208A0B8
FUN_0208A0B8: ; 0x0208A0B8
	push {r4-r7, lr}
	sub sp, #0x1c
	add r4, r0, #0x0
	cmp r1, #0x0
	bne _0208A0C6
	mov r6, #0x1
	b _0208A0C8
_0208A0C6:
	mov r6, #0x0
_0208A0C8:
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0200E3A0
	bl FUN_02015EF4
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
	ldr r0, _0208A228 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _0208A22C ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl SetKeyRepeatTimers
	ldr r0, _0208A230 ; =gMain + 0x60
	mov r1, #0x0
	strb r1, [r0, #0x5]
	bl GX_SwapDisplay
	ldr r3, _0208A234 ; =0x04000050
	mov r1, #0x0
	strh r1, [r3, #0x0]
	ldr r0, _0208A238 ; =0x04001050
	sub r3, #0x50
	strh r1, [r0, #0x0]
	ldr r2, [r3, #0x0]
	ldr r1, _0208A23C ; =0xFFFF1FFF
	sub r0, #0x50
	and r2, r1
	str r2, [r3, #0x0]
	ldr r2, [r0, #0x0]
	and r1, r2
	str r1, [r0, #0x0]
	ldr r0, _0208A240 ; =UNK_020FF474
	bl GX_SetBanks
	add r0, r4, #0x0
	bl FUN_02016B94
	add r5, r0, #0x0
	ldr r0, _0208A244 ; =UNK_020FF448
	bl FUN_02016BBC
	mov r1, #0x0
	ldr r2, _0208A248 ; =UNK_020FF458
	add r0, r5, #0x0
	add r3, r1, #0x0
	bl FUN_02016C18
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02018744
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r2, _0208A24C ; =0x000001F7
	add r0, r5, #0x0
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
	bl BG_ClearCharDataRange
	ldr r1, _0208A250 ; =0x00006C21
	mov r0, #0x0
	bl BG_SetMaskColor
	ldr r1, _0208A250 ; =0x00006C21
	mov r0, #0x4
	bl BG_SetMaskColor
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0x6
	add r3, r4, #0x0
	bl NewMsgDataFromNarc
	add r7, r0, #0x0
	mov r0, #0x6
	lsl r0, r0, #0x6
	add r1, r4, #0x0
	bl String_ctor
	add r4, r0, #0x0
	bl FUN_0201BD5C
	ldr r2, _0208A254 ; =UNK_020FF440
	add r0, r5, #0x0
	add r1, sp, #0xc
	bl AddWindow
	mov r0, #0xd0
	str r0, [sp, #0x0]
	mov r0, #0x90
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0xc
	mov r1, #0xf
	add r3, r2, #0x0
	bl FillWindowPixelRect
	ldr r2, _0208A24C ; =0x000001F7
	add r0, sp, #0xc
	mov r1, #0x0
	mov r3, #0x2
	bl FUN_0200CCA4
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl ReadMsgDataIntoString
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	add r0, sp, #0xc
	add r2, r4, #0x0
	add r3, r1, #0x0
	str r1, [sp, #0x8]
	bl AddTextPrinterParameterized
	add r0, r4, #0x0
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
	mov r4, #0x1
	; Battery-saver trap
_0208A21A:
	bl HandleDSLidAction
	add r0, r4, #0x0
	add r1, r4, #0x0
	bl OS_WaitIrq
	b _0208A21A
	.balign 4
_0208A228: .word 0xFFFFE0FF
_0208A22C: .word 0x04001000
_0208A230: .word gMain + 0x60
_0208A234: .word 0x04000050
_0208A238: .word 0x04001050
_0208A23C: .word 0xFFFF1FFF
_0208A240: .word UNK_020FF474
_0208A244: .word UNK_020FF448
_0208A248: .word UNK_020FF458
_0208A24C: .word 0x000001F7
_0208A250: .word 0x00006C21
_0208A254: .word UNK_020FF440
