	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global transFunc$7934
transFunc$7934: ; 0x020FF7D4
	.word DoTransfer3dTex
	.word DoTransfer3dTexPltt
	.word DoTransfer3dClearImageColor
	.word DoTransfer3dClearImageDepth
	.word DoTransfer2dBG0CharMain
	.word DoTransfer2dBG1CharMain
	.word DoTransfer2dBG2CharMain
	.word DoTransfer2dBG3CharMain
	.word DoTransfer2dBG0ScrMain
	.word DoTransfer2dBG1ScrMain
	.word DoTransfer2dBG2ScrMain
	.word DoTransfer2dBG3ScrMain
	.word DoTransfer2dBG2BmpMain
	.word DoTransfer2dBG3BmpMain
	.word DoTransfer2dObjPlttMain
	.word DoTransfer2dBGPlttMain
	.word DoTransfer2dObjExtPlttMain
	.word DoTransfer2dBGExtPlttMain
	.word DoTransfer2dObjOamMain
	.word DoTransfer2dObjCharMain
	.word DoTransfer2dBG0CharSub
	.word DoTransfer2dBG1CharSub
	.word DoTransfer2dBG2CharSub
	.word DoTransfer2dBG3CharSub
	.word DoTransfer2dBG0ScrSub
	.word DoTransfer2dBG1ScrSub
	.word DoTransfer2dBG2ScrSub
	.word DoTransfer2dBG3ScrSub
	.word DoTransfer2dBG2BmpSub
	.word DoTransfer2dBG3BmpSub
	.word DoTransfer2dObjPlttSub
	.word DoTransfer2dBGPlttSub
	.word DoTransfer2dObjExtPlttSub
	.word DoTransfer2dBGExtPlttSub
	.word DoTransfer2dObjOamSub
	.word DoTransfer2dObjCharSub
	; const initializer

	.section .bss

	.global s_VramTransferManager
s_VramTransferManager: ; 0x021CCD58
	.space 0x14

	.section .text

	arm_func_start NNS_GfdRegisterNewVramTransferTask
NNS_GfdRegisterNewVramTransferTask: ; 0x020AEE40
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r5, _020AEEB4 ; =s_VramTransferManager
	mov r9, r0
	mov r0, r5
	mov r8, r1
	mov r7, r2
	mov r6, r3
	bl IsVramTransferTaskQueueFull_
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r9,pc}
	mov r0, r5
	bl NNSi_GfdGetEndVramTransferTaskQueue
	mov r4, r0
	str r9, [r4, #0x0]
	str r7, [r4, #0x4]
	str r8, [r4, #0x8]
	mov r0, r5
	str r6, [r4, #0xc]
	bl NNSi_GfdPushVramTransferTaskQueue
	ldr r2, [r5, #0x10]
	ldr r1, [r4, #0xc]
	mov r0, #0x1
	add r1, r2, r1
	str r1, [r5, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020AEEB4: .word s_VramTransferManager
	arm_func_end NNS_GfdRegisterNewVramTransferTask

	arm_func_start NNS_GfdDoVramTransfer
NNS_GfdDoVramTransfer: ; 0x020AEEB8
	stmdb sp!, {r4-r6,lr}
	ldr r6, _020AEF18 ; =s_VramTransferManager
	mov r0, r6
	bl NNSi_GfdGetFrontVramTransferTaskQueue
	mov r5, r0
	mov r0, r6
	bl NNSi_GfdPopVramTransferTaskQueue
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	add r4, r6, #0x10
_020AEEE0:
	mov r0, r5
	bl DoTransfer_
	ldr r2, [r4, #0x0]
	ldr r1, [r5, #0xc]
	mov r0, r6
	sub r1, r2, r1
	str r1, [r4, #0x0]
	bl NNSi_GfdGetFrontVramTransferTaskQueue
	mov r5, r0
	mov r0, r6
	bl NNSi_GfdPopVramTransferTaskQueue
	cmp r0, #0x0
	bne _020AEEE0
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020AEF18: .word s_VramTransferManager
	arm_func_end NNS_GfdDoVramTransfer

	arm_func_start NNS_GfdInitVramTransferManager
NNS_GfdInitVramTransferManager: ; 0x020AEF1C
	ldr r2, _020AEF34 ; =s_VramTransferManager
	ldr ip, _020AEF38 ; =ResetTaskQueue_
	str r0, [r2, #0x0]
	mov r0, r2
	str r1, [r2, #0x4]
	bx r12
	.balign 4
_020AEF34: .word s_VramTransferManager
_020AEF38: .word ResetTaskQueue_
	arm_func_end NNS_GfdInitVramTransferManager

	arm_func_start NNSi_GfdPopVramTransferTaskQueue
NNSi_GfdPopVramTransferTaskQueue: ; 0x020AEF3C
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl IsVramTransferTaskQueueEmpty_
	cmp r0, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
	ldrh r1, [r4, #0x8]
	mov r0, r4
	bl GetNextIndex_
	strh r0, [r4, #0x8]
	ldrh r1, [r4, #0xc]
	mov r0, #0x1
	sub r1, r1, #0x1
	strh r1, [r4, #0xc]
	ldmia sp!, {r4,pc}
	arm_func_end NNSi_GfdPopVramTransferTaskQueue

	arm_func_start NNSi_GfdGetEndVramTransferTaskQueue
NNSi_GfdGetEndVramTransferTaskQueue: ; 0x020AEF78
	ldrh r1, [r0, #0xa]
	ldr r0, [r0, #0x0]
	add r0, r0, r1, lsl #0x4
	bx lr
	arm_func_end NNSi_GfdGetEndVramTransferTaskQueue

	arm_func_start NNSi_GfdGetFrontVramTransferTaskQueue
NNSi_GfdGetFrontVramTransferTaskQueue: ; 0x020AEF88
	ldrh r1, [r0, #0x8]
	ldr r0, [r0, #0x0]
	add r0, r0, r1, lsl #0x4
	bx lr
	arm_func_end NNSi_GfdGetFrontVramTransferTaskQueue

	arm_func_start NNSi_GfdPushVramTransferTaskQueue
NNSi_GfdPushVramTransferTaskQueue: ; 0x020AEF98
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl IsVramTransferTaskQueueFull_
	cmp r0, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
	ldrh r1, [r4, #0xa]
	mov r0, r4
	bl GetNextIndex_
	strh r0, [r4, #0xa]
	ldrh r1, [r4, #0xc]
	mov r0, #0x1
	add r1, r1, #0x1
	strh r1, [r4, #0xc]
	ldmia sp!, {r4,pc}
	arm_func_end NNSi_GfdPushVramTransferTaskQueue

	arm_func_start ResetTaskQueue_
ResetTaskQueue_: ; 0x020AEFD4
	mov r2, #0x0
	strh r2, [r0, #0xa]
	ldrh r1, [r0, #0xa]
	strh r1, [r0, #0x8]
	strh r2, [r0, #0xc]
	str r2, [r0, #0x10]
	bx lr
	arm_func_end ResetTaskQueue_

	arm_func_start DoTransfer_
DoTransfer_: ; 0x020AEFF0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r3, [r5, #0x0]
	ldr r2, _020AF02C ; =transFunc$7934
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
_020AF02C: .word transFunc$7934
	arm_func_end DoTransfer_
DoTransfer2dObjCharSub:
	ldr ip, _020AF038 ; =GXS_LoadOBJ
	bx r12
	.balign 4
_020AF038: .word GXS_LoadOBJ
	arm_func_end DoTransfer2dObjCharSub

	arm_func_start DoTransfer2dObjOamSub
DoTransfer2dObjOamSub: ; 0x020AF03C
	ldr ip, _020AF044 ; =GXS_LoadOAM
	bx r12
	.balign 4
_020AF044: .word GXS_LoadOAM
	arm_func_end DoTransfer2dObjOamSub

	arm_func_start DoTransfer2dBGExtPlttSub
DoTransfer2dBGExtPlttSub: ; 0x020AF048
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
	arm_func_end DoTransfer2dBGExtPlttSub

	arm_func_start DoTransfer2dObjExtPlttSub
DoTransfer2dObjExtPlttSub: ; 0x020AF074
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
	arm_func_end DoTransfer2dObjExtPlttSub

	arm_func_start DoTransfer2dBGPlttSub
DoTransfer2dBGPlttSub: ; 0x020AF0A0
	ldr ip, _020AF0A8 ; =GXS_LoadBGPltt
	bx r12
	.balign 4
_020AF0A8: .word GXS_LoadBGPltt
	arm_func_end DoTransfer2dBGPlttSub

	arm_func_start DoTransfer2dObjPlttSub
DoTransfer2dObjPlttSub: ; 0x020AF0AC
	ldr ip, _020AF0B4 ; =GXS_LoadOBJPltt
	bx r12
	.balign 4
_020AF0B4: .word GXS_LoadOBJPltt
	arm_func_end DoTransfer2dObjPlttSub

	arm_func_start DoTransfer2dBG3BmpSub
DoTransfer2dBG3BmpSub: ; 0x020AF0B8
	ldr ip, _020AF0C0 ; =GXS_LoadBG3Scr
	bx r12
	.balign 4
_020AF0C0: .word GXS_LoadBG3Scr
	arm_func_end DoTransfer2dBG3BmpSub

	arm_func_start DoTransfer2dBG2BmpSub
DoTransfer2dBG2BmpSub: ; 0x020AF0C4
	ldr ip, _020AF0CC ; =GXS_LoadBG2Scr
	bx r12
	.balign 4
_020AF0CC: .word GXS_LoadBG2Scr
	arm_func_end DoTransfer2dBG2BmpSub

	arm_func_start DoTransfer2dBG3ScrSub
DoTransfer2dBG3ScrSub: ; 0x020AF0D0
	ldr ip, _020AF0D8 ; =GXS_LoadBG3Scr
	bx r12
	.balign 4
_020AF0D8: .word GXS_LoadBG3Scr
	arm_func_end DoTransfer2dBG3ScrSub

	arm_func_start DoTransfer2dBG2ScrSub
DoTransfer2dBG2ScrSub: ; 0x020AF0DC
	ldr ip, _020AF0E4 ; =GXS_LoadBG2Scr
	bx r12
	.balign 4
_020AF0E4: .word GXS_LoadBG2Scr
	arm_func_end DoTransfer2dBG2ScrSub

	arm_func_start DoTransfer2dBG1ScrSub
DoTransfer2dBG1ScrSub: ; 0x020AF0E8
	ldr ip, _020AF0F0 ; =GXS_LoadBG1Scr
	bx r12
	.balign 4
_020AF0F0: .word GXS_LoadBG1Scr
	arm_func_end DoTransfer2dBG1ScrSub

	arm_func_start DoTransfer2dBG0ScrSub
DoTransfer2dBG0ScrSub: ; 0x020AF0F4
	ldr ip, _020AF0FC ; =GXS_LoadBG0Scr
	bx r12
	.balign 4
_020AF0FC: .word GXS_LoadBG0Scr
	arm_func_end DoTransfer2dBG0ScrSub

	arm_func_start DoTransfer2dBG3CharSub
DoTransfer2dBG3CharSub: ; 0x020AF100
	ldr ip, _020AF108 ; =GXS_LoadBG3Char
	bx r12
	.balign 4
_020AF108: .word GXS_LoadBG3Char
	arm_func_end DoTransfer2dBG3CharSub

	arm_func_start DoTransfer2dBG2CharSub
DoTransfer2dBG2CharSub: ; 0x020AF10C
	ldr ip, _020AF114 ; =GXS_LoadBG2Char
	bx r12
	.balign 4
_020AF114: .word GXS_LoadBG2Char
	arm_func_end DoTransfer2dBG2CharSub

	arm_func_start DoTransfer2dBG1CharSub
DoTransfer2dBG1CharSub: ; 0x020AF118
	ldr ip, _020AF120 ; =GXS_LoadBG1Char
	bx r12
	.balign 4
_020AF120: .word GXS_LoadBG1Char
	arm_func_end DoTransfer2dBG1CharSub

	arm_func_start DoTransfer2dBG0CharSub
DoTransfer2dBG0CharSub: ; 0x020AF124
	ldr ip, _020AF12C ; =GXS_LoadBG0Char
	bx r12
	.balign 4
_020AF12C: .word GXS_LoadBG0Char
	arm_func_end DoTransfer2dBG0CharSub

	arm_func_start DoTransfer2dObjCharMain
DoTransfer2dObjCharMain: ; 0x020AF130
	ldr ip, _020AF138 ; =GX_LoadOBJ
	bx r12
	.balign 4
_020AF138: .word GX_LoadOBJ
	arm_func_end DoTransfer2dObjCharMain

	arm_func_start DoTransfer2dObjOamMain
DoTransfer2dObjOamMain: ; 0x020AF13C
	ldr ip, _020AF144 ; =GX_LoadOAM
	bx r12
	.balign 4
_020AF144: .word GX_LoadOAM
	arm_func_end DoTransfer2dObjOamMain

	arm_func_start DoTransfer2dBGExtPlttMain
DoTransfer2dBGExtPlttMain: ; 0x020AF148
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
	arm_func_end DoTransfer2dBGExtPlttMain

	arm_func_start DoTransfer2dObjExtPlttMain
DoTransfer2dObjExtPlttMain: ; 0x020AF174
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
	arm_func_end DoTransfer2dObjExtPlttMain

	arm_func_start DoTransfer2dBGPlttMain
DoTransfer2dBGPlttMain: ; 0x020AF1A0
	ldr ip, _020AF1A8 ; =GX_LoadBGPltt
	bx r12
	.balign 4
_020AF1A8: .word GX_LoadBGPltt
	arm_func_end DoTransfer2dBGPlttMain

	arm_func_start DoTransfer2dObjPlttMain
DoTransfer2dObjPlttMain: ; 0x020AF1AC
	ldr ip, _020AF1B4 ; =GX_LoadOBJPltt
	bx r12
	.balign 4
_020AF1B4: .word GX_LoadOBJPltt
	arm_func_end DoTransfer2dObjPlttMain

	arm_func_start DoTransfer2dBG3BmpMain
DoTransfer2dBG3BmpMain: ; 0x020AF1B8
	ldr ip, _020AF1C0 ; =GX_LoadBG3Scr
	bx r12
	.balign 4
_020AF1C0: .word GX_LoadBG3Scr
	arm_func_end DoTransfer2dBG3BmpMain

	arm_func_start DoTransfer2dBG2BmpMain
DoTransfer2dBG2BmpMain: ; 0x020AF1C4
	ldr ip, _020AF1CC ; =GX_LoadBG2Scr
	bx r12
	.balign 4
_020AF1CC: .word GX_LoadBG2Scr
	arm_func_end DoTransfer2dBG2BmpMain

	arm_func_start DoTransfer2dBG3ScrMain
DoTransfer2dBG3ScrMain: ; 0x020AF1D0
	ldr ip, _020AF1D8 ; =GX_LoadBG3Scr
	bx r12
	.balign 4
_020AF1D8: .word GX_LoadBG3Scr
	arm_func_end DoTransfer2dBG3ScrMain

	arm_func_start DoTransfer2dBG2ScrMain
DoTransfer2dBG2ScrMain: ; 0x020AF1DC
	ldr ip, _020AF1E4 ; =GX_LoadBG2Scr
	bx r12
	.balign 4
_020AF1E4: .word GX_LoadBG2Scr
	arm_func_end DoTransfer2dBG2ScrMain

	arm_func_start DoTransfer2dBG1ScrMain
DoTransfer2dBG1ScrMain: ; 0x020AF1E8
	ldr ip, _020AF1F0 ; =GX_LoadBG1Scr
	bx r12
	.balign 4
_020AF1F0: .word GX_LoadBG1Scr
	arm_func_end DoTransfer2dBG1ScrMain

	arm_func_start DoTransfer2dBG0ScrMain
DoTransfer2dBG0ScrMain: ; 0x020AF1F4
	ldr ip, _020AF1FC ; =GX_LoadBG0Scr
	bx r12
	.balign 4
_020AF1FC: .word GX_LoadBG0Scr
	arm_func_end DoTransfer2dBG0ScrMain

	arm_func_start DoTransfer2dBG3CharMain
DoTransfer2dBG3CharMain: ; 0x020AF200
	ldr ip, _020AF208 ; =GX_LoadBG3Char
	bx r12
	.balign 4
_020AF208: .word GX_LoadBG3Char
	arm_func_end DoTransfer2dBG3CharMain

	arm_func_start DoTransfer2dBG2CharMain
DoTransfer2dBG2CharMain: ; 0x020AF20C
	ldr ip, _020AF214 ; =GX_LoadBG2Char
	bx r12
	.balign 4
_020AF214: .word GX_LoadBG2Char
	arm_func_end DoTransfer2dBG2CharMain

	arm_func_start DoTransfer2dBG1CharMain
DoTransfer2dBG1CharMain: ; 0x020AF218
	ldr ip, _020AF220 ; =GX_LoadBG1Char
	bx r12
	.balign 4
_020AF220: .word GX_LoadBG1Char
	arm_func_end DoTransfer2dBG1CharMain

	arm_func_start DoTransfer2dBG0CharMain
DoTransfer2dBG0CharMain: ; 0x020AF224
	ldr ip, _020AF22C ; =GX_LoadBG0Char
	bx r12
	.balign 4
_020AF22C: .word GX_LoadBG0Char
	arm_func_end DoTransfer2dBG0CharMain

	arm_func_start DoTransfer3dClearImageDepth
DoTransfer3dClearImageDepth: ; 0x020AF230
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
	arm_func_end DoTransfer3dClearImageDepth

	arm_func_start DoTransfer3dClearImageColor
DoTransfer3dClearImageColor: ; 0x020AF25C
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
	arm_func_end DoTransfer3dClearImageColor

	arm_func_start DoTransfer3dTexPltt
DoTransfer3dTexPltt: ; 0x020AF288
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
	arm_func_end DoTransfer3dTexPltt

	arm_func_start DoTransfer3dTex
DoTransfer3dTex: ; 0x020AF2B4
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
	arm_func_end DoTransfer3dTex

	arm_func_start IsVramTransferTaskQueueEmpty_
IsVramTransferTaskQueueEmpty_: ; 0x020AF2E0
	ldrh r0, [r0, #0xc]
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	bx lr
	arm_func_end IsVramTransferTaskQueueEmpty_

	arm_func_start IsVramTransferTaskQueueFull_
IsVramTransferTaskQueueFull_: ; 0x020AF2F4
	ldrh r1, [r0, #0xc]
	ldr r0, [r0, #0x4]
	cmp r1, r0
	moveq r0, #0x1
	movne r0, #0x0
	bx lr
	arm_func_end IsVramTransferTaskQueueFull_

	arm_func_start GetNextIndex_
GetNextIndex_: ; 0x020AF30C
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
	arm_func_end GetNextIndex_
