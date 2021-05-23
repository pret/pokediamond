	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	; transFunc$7934
	.global UNK_020FF7D4
UNK_020FF7D4: ; 0x020FF7D4
	.word FUN_020AF2B4
	.word FUN_020AF288
	.word FUN_020AF25C
	.word FUN_020AF230
	.word GX_LoadBG0Char_2
	.word GX_LoadBG1Char_2
	.word GX_LoadBG2Char_2
	.word GX_LoadBG3Char_2
	.word GX_LoadBG0Scr_2
	.word GX_LoadBG1Scr_2
	.word GX_LoadBG2Scr_2
	.word GX_LoadBG3Scr_2
	.word GX_LoadBG2Scr_3
	.word GX_LoadBG3Scr_3
	.word GX_LoadOBJPltt_2
	.word GX_LoadBGPltt_2
	.word FUN_020AF174
	.word FUN_020AF148
	.word GX_LoadOAM_2
	.word GX_LoadOBJ_2
	.word GXS_LoadBG0Char_2
	.word GXS_LoadBG1Char_2
	.word GXS_LoadBG2Char_2
	.word GXS_LoadBG3Char_2
	.word GXS_LoadBG0Scr_2
	.word GXS_LoadBG1Scr_2
	.word GXS_LoadBG2Scr_2
	.word GXS_LoadBG3Scr_2
	.word GXS_LoadBG2Scr_3
	.word GXS_LoadBG3Scr_3
	.word GXS_LoadOBJPltt_2
	.word GXS_LoadBGPltt_2
	.word FUN_020AF074
	.word FUN_020AF048
	.word GXS_LoadOAM_2
	.word GXS_LoadOBJ_2

	; const initializer
	.section .bss

	; s_VramTransferManager
	.global UNK_021CCD58
UNK_021CCD58: ; 0x021CCD58
	.space 0x14

	.section .text

	; NNS_GfdRegisterNewVramTransferTask
	arm_func_start FUN_020AEE40
FUN_020AEE40: ; 0x020AEE40
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r5, _020AEEB4 ; =UNK_021CCD58
	mov r9, r0
	mov r0, r5
	mov r8, r1
	mov r7, r2
	mov r6, r3
	bl FUN_020AF2F4
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r9,pc}
	mov r0, r5
	bl FUN_020AEF78
	mov r4, r0
	str r9, [r4, #0x0]
	str r7, [r4, #0x4]
	str r8, [r4, #0x8]
	mov r0, r5
	str r6, [r4, #0xc]
	bl FUN_020AEF98
	ldr r2, [r5, #0x10]
	ldr r1, [r4, #0xc]
	mov r0, #0x1
	add r1, r2, r1
	str r1, [r5, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020AEEB4: .word UNK_021CCD58
	arm_func_end FUN_020AEE40

	; NNS_GfdDoVramTransfer
	arm_func_start FUN_020AEEB8
FUN_020AEEB8: ; 0x020AEEB8
	stmdb sp!, {r4-r6,lr}
	ldr r6, _020AEF18 ; =UNK_021CCD58
	mov r0, r6
	bl FUN_020AEF88
	mov r5, r0
	mov r0, r6
	bl FUN_020AEF3C
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	add r4, r6, #0x10
_020AEEE0:
	mov r0, r5
	bl FUN_020AEFF0
	ldr r2, [r4, #0x0]
	ldr r1, [r5, #0xc]
	mov r0, r6
	sub r1, r2, r1
	str r1, [r4, #0x0]
	bl FUN_020AEF88
	mov r5, r0
	mov r0, r6
	bl FUN_020AEF3C
	cmp r0, #0x0
	bne _020AEEE0
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020AEF18: .word UNK_021CCD58
	arm_func_end FUN_020AEEB8

	; NNS_GfdInitVramTransferManager
	arm_func_start FUN_020AEF1C
FUN_020AEF1C: ; 0x020AEF1C
	ldr r2, _020AEF34 ; =UNK_021CCD58
	ldr ip, _020AEF38 ; =FUN_020AEFD4
	str r0, [r2, #0x0]
	mov r0, r2
	str r1, [r2, #0x4]
	bx r12
	.balign 4
_020AEF34: .word UNK_021CCD58
_020AEF38: .word FUN_020AEFD4
	arm_func_end FUN_020AEF1C

	; _end
	arm_func_start FUN_020AEF3C
FUN_020AEF3C: ; 0x020AEF3C
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020AF2E0
	cmp r0, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
	ldrh r1, [r4, #0x8]
	mov r0, r4
	bl FUN_020AF30C
	strh r0, [r4, #0x8]
	ldrh r1, [r4, #0xc]
	mov r0, #0x1
	sub r1, r1, #0x1
	strh r1, [r4, #0xc]
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020AEF3C

	; _end
	arm_func_start FUN_020AEF78
FUN_020AEF78: ; 0x020AEF78
	ldrh r1, [r0, #0xa]
	ldr r0, [r0, #0x0]
	add r0, r0, r1, lsl #0x4
	bx lr
	arm_func_end FUN_020AEF78

	; _end
	arm_func_start FUN_020AEF88
FUN_020AEF88: ; 0x020AEF88
	ldrh r1, [r0, #0x8]
	ldr r0, [r0, #0x0]
	add r0, r0, r1, lsl #0x4
	bx lr
	arm_func_end FUN_020AEF88

	; _end
	arm_func_start FUN_020AEF98
FUN_020AEF98: ; 0x020AEF98
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020AF2F4
	cmp r0, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
	ldrh r1, [r4, #0xa]
	mov r0, r4
	bl FUN_020AF30C
	strh r0, [r4, #0xa]
	ldrh r1, [r4, #0xc]
	mov r0, #0x1
	add r1, r1, #0x1
	strh r1, [r4, #0xc]
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020AEF98

	; _end
	arm_func_start FUN_020AEFD4
FUN_020AEFD4: ; 0x020AEFD4
	mov r2, #0x0
	strh r2, [r0, #0xa]
	ldrh r1, [r0, #0xa]
	strh r1, [r0, #0x8]
	strh r2, [r0, #0xc]
	str r2, [r0, #0x10]
	bx lr
	arm_func_end FUN_020AEFD4

	; DoTransfer_
	arm_func_start FUN_020AEFF0
FUN_020AEFF0: ; 0x020AEFF0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r3, [r5, #0x0]
	ldr r2, _020AF02C ; =UNK_020FF7D4
	ldr r0, [r5, #0x4]
	ldr r1, [r5, #0xc]
	ldr r4, [r2, r3, lsl #0x2]
	bl DC_FlushRange
	ldr r0, [r5, #0x4]
	ldr r1, [r5, #0x8]
	ldr r2, [r5, #0xc]
	blx r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AF02C: .word UNK_020FF7D4
	arm_func_end FUN_020AEFF0

GXS_LoadOBJ_2:
	ldr ip, _020AF038 ; =GXS_LoadOBJ
	bx r12
	.balign 4
_020AF038: .word GXS_LoadOBJ
	arm_func_end GXS_LoadOBJ_2

	; DoTransfer2dObjOamSub
	arm_func_start GXS_LoadOAM_2
GXS_LoadOAM_2: ; 0x020AF03C
	ldr ip, _020AF044 ; =GXS_LoadOAM
	bx r12
	.balign 4
_020AF044: .word GXS_LoadOAM
	arm_func_end GXS_LoadOAM_2

	; _end
	arm_func_start FUN_020AF048
FUN_020AF048: ; 0x020AF048
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl GXS_BeginLoadBGExtPltt
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl GXS_LoadBGExtPltt
	bl GXS_EndLoadBGExtPltt
	ldmia sp!, {r4-r6,pc}
	arm_func_end FUN_020AF048

	; _end
	arm_func_start FUN_020AF074
FUN_020AF074: ; 0x020AF074
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl GXS_BeginLoadOBJExtPltt
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl GXS_LoadOBJExtPltt
	bl GXS_EndLoadOBJExtPltt
	ldmia sp!, {r4-r6,pc}
	arm_func_end FUN_020AF074

	; DoTransfer2dBGPlttSub
	arm_func_start GXS_LoadBGPltt_2
GXS_LoadBGPltt_2: ; 0x020AF0A0
	ldr ip, _020AF0A8 ; =GXS_LoadBGPltt
	bx r12
	.balign 4
_020AF0A8: .word GXS_LoadBGPltt
	arm_func_end GXS_LoadBGPltt_2

	; DoTransfer2dObjPlttSub
	arm_func_start GXS_LoadOBJPltt_2
GXS_LoadOBJPltt_2: ; 0x020AF0AC
	ldr ip, _020AF0B4 ; =GXS_LoadOBJPltt
	bx r12
	.balign 4
_020AF0B4: .word GXS_LoadOBJPltt
	arm_func_end GXS_LoadOBJPltt_2

	; DoTransfer2dBG3BmpSub
	arm_func_start GXS_LoadBG3Scr_3
GXS_LoadBG3Scr_3: ; 0x020AF0B8
	ldr ip, _020AF0C0 ; =GXS_LoadBG3Scr
	bx r12
	.balign 4
_020AF0C0: .word GXS_LoadBG3Scr
	arm_func_end GXS_LoadBG3Scr_3

	; DoTransfer2dBG2BmpSub
	arm_func_start GXS_LoadBG2Scr_3
GXS_LoadBG2Scr_3: ; 0x020AF0C4
	ldr ip, _020AF0CC ; =GXS_LoadBG2Scr
	bx r12
	.balign 4
_020AF0CC: .word GXS_LoadBG2Scr
	arm_func_end GXS_LoadBG2Scr_3

	; DoTransfer2dBG3ScrSub
	arm_func_start GXS_LoadBG3Scr_2
GXS_LoadBG3Scr_2: ; 0x020AF0D0
	ldr ip, _020AF0D8 ; =GXS_LoadBG3Scr
	bx r12
	.balign 4
_020AF0D8: .word GXS_LoadBG3Scr
	arm_func_end GXS_LoadBG3Scr_2

	; DoTransfer2dBG2ScrSub
	arm_func_start GXS_LoadBG2Scr_2
GXS_LoadBG2Scr_2: ; 0x020AF0DC
	ldr ip, _020AF0E4 ; =GXS_LoadBG2Scr
	bx r12
	.balign 4
_020AF0E4: .word GXS_LoadBG2Scr
	arm_func_end GXS_LoadBG2Scr_2

	; DoTransfer2dBG1ScrSub
	arm_func_start GXS_LoadBG1Scr_2
GXS_LoadBG1Scr_2: ; 0x020AF0E8
	ldr ip, _020AF0F0 ; =GXS_LoadBG1Scr
	bx r12
	.balign 4
_020AF0F0: .word GXS_LoadBG1Scr
	arm_func_end GXS_LoadBG1Scr_2

	; DoTransfer2dBG0ScrSub
	arm_func_start GXS_LoadBG0Scr_2
GXS_LoadBG0Scr_2: ; 0x020AF0F4
	ldr ip, _020AF0FC ; =GXS_LoadBG0Scr
	bx r12
	.balign 4
_020AF0FC: .word GXS_LoadBG0Scr
	arm_func_end GXS_LoadBG0Scr_2

	; DoTransfer2dBG3CharSub
	arm_func_start GXS_LoadBG3Char_2
GXS_LoadBG3Char_2: ; 0x020AF100
	ldr ip, _020AF108 ; =GXS_LoadBG3Char
	bx r12
	.balign 4
_020AF108: .word GXS_LoadBG3Char
	arm_func_end GXS_LoadBG3Char_2

	; DoTransfer2dBG2CharSub
	arm_func_start GXS_LoadBG2Char_2
GXS_LoadBG2Char_2: ; 0x020AF10C
	ldr ip, _020AF114 ; =GXS_LoadBG2Char
	bx r12
	.balign 4
_020AF114: .word GXS_LoadBG2Char
	arm_func_end GXS_LoadBG2Char_2

	; DoTransfer2dBG1CharSub
	arm_func_start GXS_LoadBG1Char_2
GXS_LoadBG1Char_2: ; 0x020AF118
	ldr ip, _020AF120 ; =GXS_LoadBG1Char
	bx r12
	.balign 4
_020AF120: .word GXS_LoadBG1Char
	arm_func_end GXS_LoadBG1Char_2

	; DoTransfer2dBG0CharSub
	arm_func_start GXS_LoadBG0Char_2
GXS_LoadBG0Char_2: ; 0x020AF124
	ldr ip, _020AF12C ; =GXS_LoadBG0Char
	bx r12
	.balign 4
_020AF12C: .word GXS_LoadBG0Char
	arm_func_end GXS_LoadBG0Char_2

	; DoTransfer2dObjCharMain
	arm_func_start GX_LoadOBJ_2
GX_LoadOBJ_2: ; 0x020AF130
	ldr ip, _020AF138 ; =GX_LoadOBJ
	bx r12
	.balign 4
_020AF138: .word GX_LoadOBJ
	arm_func_end GX_LoadOBJ_2

	; DoTransfer2dObjOamMain
	arm_func_start GX_LoadOAM_2
GX_LoadOAM_2: ; 0x020AF13C
	ldr ip, _020AF144 ; =GX_LoadOAM
	bx r12
	.balign 4
_020AF144: .word GX_LoadOAM
	arm_func_end GX_LoadOAM_2

	; _end
	arm_func_start FUN_020AF148
FUN_020AF148: ; 0x020AF148
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl GX_BeginLoadBGExtPltt
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl GX_LoadBGExtPltt
	bl GX_EndLoadBGExtPltt
	ldmia sp!, {r4-r6,pc}
	arm_func_end FUN_020AF148

	; _end
	arm_func_start FUN_020AF174
FUN_020AF174: ; 0x020AF174
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl GX_BeginLoadOBJExtPltt
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl GX_LoadOBJExtPltt
	bl GX_EndLoadOBJExtPltt
	ldmia sp!, {r4-r6,pc}
	arm_func_end FUN_020AF174

	; DoTransfer2dBGPlttMain
	arm_func_start GX_LoadBGPltt_2
GX_LoadBGPltt_2: ; 0x020AF1A0
	ldr ip, _020AF1A8 ; =GX_LoadBGPltt
	bx r12
	.balign 4
_020AF1A8: .word GX_LoadBGPltt
	arm_func_end GX_LoadBGPltt_2

	; DoTransfer2dObjPlttMain
	arm_func_start GX_LoadOBJPltt_2
GX_LoadOBJPltt_2: ; 0x020AF1AC
	ldr ip, _020AF1B4 ; =GX_LoadOBJPltt
	bx r12
	.balign 4
_020AF1B4: .word GX_LoadOBJPltt
	arm_func_end GX_LoadOBJPltt_2

	; DoTransfer2dBG3BmpMain
	arm_func_start GX_LoadBG3Scr_3
GX_LoadBG3Scr_3: ; 0x020AF1B8
	ldr ip, _020AF1C0 ; =GX_LoadBG3Scr
	bx r12
	.balign 4
_020AF1C0: .word GX_LoadBG3Scr
	arm_func_end GX_LoadBG3Scr_3

	; DoTransfer2dBG2BmpMain
	arm_func_start GX_LoadBG2Scr_3
GX_LoadBG2Scr_3: ; 0x020AF1C4
	ldr ip, _020AF1CC ; =GX_LoadBG2Scr
	bx r12
	.balign 4
_020AF1CC: .word GX_LoadBG2Scr
	arm_func_end GX_LoadBG2Scr_3

	; DoTransfer2dBG3ScrMain
	arm_func_start GX_LoadBG3Scr_2
GX_LoadBG3Scr_2: ; 0x020AF1D0
	ldr ip, _020AF1D8 ; =GX_LoadBG3Scr
	bx r12
	.balign 4
_020AF1D8: .word GX_LoadBG3Scr
	arm_func_end GX_LoadBG3Scr_2

	; DoTransfer2dBG2ScrMain
	arm_func_start GX_LoadBG2Scr_2
GX_LoadBG2Scr_2: ; 0x020AF1DC
	ldr ip, _020AF1E4 ; =GX_LoadBG2Scr
	bx r12
	.balign 4
_020AF1E4: .word GX_LoadBG2Scr
	arm_func_end GX_LoadBG2Scr_2

	; DoTransfer2dBG1ScrMain
	arm_func_start GX_LoadBG1Scr_2
GX_LoadBG1Scr_2: ; 0x020AF1E8
	ldr ip, _020AF1F0 ; =GX_LoadBG1Scr
	bx r12
	.balign 4
_020AF1F0: .word GX_LoadBG1Scr
	arm_func_end GX_LoadBG1Scr_2

	; DoTransfer2dBG0ScrMain
	arm_func_start GX_LoadBG0Scr_2
GX_LoadBG0Scr_2: ; 0x020AF1F4
	ldr ip, _020AF1FC ; =GX_LoadBG0Scr
	bx r12
	.balign 4
_020AF1FC: .word GX_LoadBG0Scr
	arm_func_end GX_LoadBG0Scr_2

	; DoTransfer2dBG3CharMain
	arm_func_start GX_LoadBG3Char_2
GX_LoadBG3Char_2: ; 0x020AF200
	ldr ip, _020AF208 ; =GX_LoadBG3Char
	bx r12
	.balign 4
_020AF208: .word GX_LoadBG3Char
	arm_func_end GX_LoadBG3Char_2

	; DoTransfer2dBG2CharMain
	arm_func_start GX_LoadBG2Char_2
GX_LoadBG2Char_2: ; 0x020AF20C
	ldr ip, _020AF214 ; =GX_LoadBG2Char
	bx r12
	.balign 4
_020AF214: .word GX_LoadBG2Char
	arm_func_end GX_LoadBG2Char_2

	; DoTransfer2dBG1CharMain
	arm_func_start GX_LoadBG1Char_2
GX_LoadBG1Char_2: ; 0x020AF218
	ldr ip, _020AF220 ; =GX_LoadBG1Char
	bx r12
	.balign 4
_020AF220: .word GX_LoadBG1Char
	arm_func_end GX_LoadBG1Char_2

	; DoTransfer2dBG0CharMain
	arm_func_start GX_LoadBG0Char_2
GX_LoadBG0Char_2: ; 0x020AF224
	ldr ip, _020AF22C ; =GX_LoadBG0Char
	bx r12
	.balign 4
_020AF22C: .word GX_LoadBG0Char
	arm_func_end GX_LoadBG0Char_2

	; _end
	arm_func_start FUN_020AF230
FUN_020AF230: ; 0x020AF230
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r2
	bl GX_BeginLoadClearImage
	mov r0, r5
	mov r1, r4
	bl GX_LoadClearImageDepth
	bl GX_EndLoadClearImage
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	arm_func_end FUN_020AF230

	; _end
	arm_func_start FUN_020AF25C
FUN_020AF25C: ; 0x020AF25C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r2
	bl GX_BeginLoadClearImage
	mov r0, r5
	mov r1, r4
	bl GX_LoadClearImageColor
	bl GX_EndLoadClearImage
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	arm_func_end FUN_020AF25C

	; _end
	arm_func_start FUN_020AF288
FUN_020AF288: ; 0x020AF288
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl GX_BeginLoadTexPltt
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl GX_LoadTexPltt
	bl GX_EndLoadTexPltt
	ldmia sp!, {r4-r6,pc}
	arm_func_end FUN_020AF288

	; _end
	arm_func_start FUN_020AF2B4
FUN_020AF2B4: ; 0x020AF2B4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl GX_BeginLoadTex
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl GX_LoadTex
	bl GX_EndLoadTex
	ldmia sp!, {r4-r6,pc}
	arm_func_end FUN_020AF2B4

	; _end
	arm_func_start FUN_020AF2E0
FUN_020AF2E0: ; 0x020AF2E0
	ldrh r0, [r0, #0xc]
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	bx lr
	arm_func_end FUN_020AF2E0

	; _end
	arm_func_start FUN_020AF2F4
FUN_020AF2F4: ; 0x020AF2F4
	ldrh r1, [r0, #0xc]
	ldr r0, [r0, #0x4]
	cmp r1, r0
	moveq r0, #0x1
	movne r0, #0x0
	bx lr
	arm_func_end FUN_020AF2F4

	; _end
	arm_func_start FUN_020AF30C
FUN_020AF30C: ; 0x020AF30C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r0
	add r0, r1, #0x1
	ldr r1, [r2, #0x4]
	bl _u32_div_f
	mov r0, r1, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end FUN_020AF30C

