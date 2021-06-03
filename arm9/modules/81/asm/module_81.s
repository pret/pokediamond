	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD81_02237E40
MOD81_02237E40: ; 0x02237E40
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	bl FUN_0200E308
	cmp r0, #0
	bne _02237E50
	b _02237FC8
_02237E50:
	mov r0, #3
	mov r1, #0x39
	lsl r2, r0, #0xf
	bl CreateHeap
	mov r0, #3
	mov r1, #0x3a
	lsl r2, r0, #0xf
	bl CreateHeap
	bl MOD81_02238858
	ldr r1, _02237FD0 ; =0x00000492
	mov r0, #3
	mov r2, #1
	bl FUN_0200433C
	mov r1, #0x55
	add r0, r5, #0
	lsl r1, r1, #2
	mov r2, #0x39
	bl OverlayManager_CreateAndGetData
	add r4, r0, #0
	bne _02237E84
	b _02237FC2
_02237E84:
	add r0, r5, #0
	bl OverlayManager_GetField18
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #4]
	mov r0, #0x39
	bl FUN_02016B94
	str r0, [r4, #8]
	mov r0, #0x19
	lsl r0, r0, #4
	mov r1, #0x39
	bl String_ctor
	str r0, [r4, #0x14]
	ldr r2, _02237FD4 ; =0x00000137
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x39
	bl NewMsgDataFromNarc
	str r0, [r4, #0x10]
	mov r0, #0x39
	bl ScrStrBufs_new
	str r0, [r4, #0xc]
	ldr r2, [r4]
	ldr r0, [r2, #0x10]
	cmp r0, #1
	beq _02237ECC
	cmp r0, #2
	beq _02237EFE
	cmp r0, #4
	beq _02237F0A
	b _02237F22
_02237ECC:
	ldr r0, [r4, #0xc]
	ldr r2, [r2]
	mov r1, #0
	bl BufferBoxMonNickname
	ldr r2, [r4]
	ldr r0, [r4, #0xc]
	ldr r2, [r2, #4]
	mov r1, #1
	bl BufferBoxMonNickname
	ldr r2, [r4]
	ldr r0, [r4, #0xc]
	ldr r2, [r2, #8]
	mov r1, #2
	bl BufferPlayersName
	ldr r0, [r4]
	ldr r0, [r0, #4]
	bl MOD81_02237FE8
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r4, r1]
	b _02237F22
_02237EFE:
	ldr r0, [r4, #0xc]
	ldr r2, [r2]
	mov r1, #0
	bl BufferBoxMonNickname
	b _02237F22
_02237F0A:
	ldr r0, [r4, #0xc]
	ldr r2, [r2, #4]
	mov r1, #1
	bl BufferBoxMonNickname
	ldr r0, [r4]
	ldr r0, [r0, #4]
	bl MOD81_02237FE8
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r4, r1]
_02237F22:
	bl NNS_G2dInitOamManagerModule
	mov r0, #1
	str r0, [sp]
	mov r0, #0x7f
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r1, #0x39
	str r1, [sp, #0x10]
	mov r1, #0x80
	add r2, r0, #0
	bl FUN_02009EAC
	add r1, r4, #0
	mov r0, #0x40
	add r1, #0x1c
	mov r2, #0x39
	bl FUN_02008C9C
	str r0, [r4, #0x18]
	add r0, r4, #0
	mov r2, #0x3a
	add r0, #0x1c
	mov r1, #0
	lsl r2, r2, #0xe
	bl FUN_02008D24
	ldr r0, [r4]
	mov r1, #5
	ldr r0, [r0]
	mov r2, #0
	bl GetBoxMonData
	mov r1, #0x53
	lsl r1, r1, #2
	strh r0, [r4, r1]
	ldr r0, [r4]
	mov r1, #5
	ldr r0, [r0, #4]
	mov r2, #0
	bl GetBoxMonData
	ldr r1, _02237FD8 ; =0x0000014E
	strh r0, [r4, r1]
	mov r0, #0
	add r1, r1, #2
	str r0, [r4, r1]
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _02237FDC ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _02237FE0 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	ldr r0, _02237FE4 ; =MOD81_022380F4
	add r1, r4, #0
	mov r2, #1
	bl FUN_0200CA7C
	mov r1, #0x51
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0
	add r1, #0xc
	str r0, [r4, r1]
_02237FC2:
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, pc}
_02237FC8:
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_02237FD0: .word 0x00000492
_02237FD4: .word 0x00000137
_02237FD8: .word 0x0000014E
_02237FDC: .word 0xFFFFE0FF
_02237FE0: .word 0x04001000
_02237FE4: .word MOD81_022380F4
	thumb_func_end MOD81_02237E40

	thumb_func_start MOD81_02237FE8
MOD81_02237FE8: ; 0x02237FE8
	push {r3, lr}
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	mov r1, #0x1c ; BASE_FLIP
	bl GetMonBaseStat
	cmp r0, #0
	bne _02238000
	mov r0, #1
	pop {r3, pc}
_02238000:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD81_02237FE8

	thumb_func_start MOD81_02238004
MOD81_02238004: ; 0x02238004
	push {r4, r5, r6, lr}
	add r5, r0, #0
	bl OS_DisableInterrupts
	add r6, r0, #0
	add r0, r5, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200CAB4
	bl FUN_02033ED0
	ldr r0, [r4, #0xc]
	bl ScrStrBufs_delete
	ldr r0, [r4, #0x10]
	bl DestroyMsgData
	ldr r0, [r4, #0x14]
	bl String_dtor
	ldr r0, [r4, #8]
	bl FreeToHeap
	ldr r0, [r4, #0x18]
	bl FUN_0201FD58
	bl FUN_02009FA0
	add r0, r5, #0
	bl OverlayManager_FreeData
	mov r0, #0x39
	bl DestroyHeap
	mov r0, #0x3a
	bl DestroyHeap
	add r0, r6, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD81_02238004

	thumb_func_start MOD81_02238064
MOD81_02238064: ; 0x02238064
	push {r4, r5, r6, lr}
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r3, [r4, #4]
	cmp r3, #7
	bhs _022380E0
	ldr r1, [r4]
	ldr r6, _022380E4 ; =0x0223CF90
	lsl r2, r3, #4
	ldr r1, [r1, #0x10]
	ldr r6, [r6, r2]
	tst r1, r6
	beq _022380D0
	mov r1, #0x15
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	cmp r1, #0
	bne _02238098
	ldr r1, _022380E8 ; =0x0223CF84
	ldr r1, [r1, r2]
	blx r1
	mov r1, #0x15
	lsl r1, r1, #4
	str r0, [r4, r1]
_02238098:
	ldr r2, [r4, #4]
	mov r0, #0x15
	lsl r3, r2, #4
	ldr r2, _022380EC ; =0x0223CF88
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	ldr r2, [r2, r3]
	add r1, r5, #0
	blx r2
	cmp r0, #0
	beq _022380D8
	ldr r1, [r4, #4]
	mov r0, #0x15
	lsl r2, r1, #4
	ldr r1, _022380F0 ; =0x0223CF8C
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	ldr r1, [r1, r2]
	blx r1
	mov r0, #0x15
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	str r1, [r5]
	b _022380D8
_022380D0:
	add r0, r3, #1
	str r0, [r4, #4]
	mov r0, #0
	str r0, [r5]
_022380D8:
	bl MOD81_02238864
	mov r0, #0
	pop {r4, r5, r6, pc}
_022380E0:
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
_022380E4: .word MOD81_0223CF84 + 0xC
_022380E8: .word MOD81_0223CF84
_022380EC: .word MOD81_0223CF84 + 4
_022380F0: .word MOD81_0223CF84 + 8
	thumb_func_end MOD81_02238064

	thumb_func_start MOD81_022380F4
MOD81_022380F4: ; 0x022380F4
	push {r3, lr}
	ldr r0, [r1, #0x18]
	bl FUN_0201FDEC
	bl FUN_02009F80
	ldr r3, _02238110 ; =0x027E0000
	ldr r1, _02238114 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r3, pc}
	nop
_02238110: .word 0x027E0000
_02238114: .word 0x00003FF8
	thumb_func_end MOD81_022380F4

	thumb_func_start MOD81_02238118
MOD81_02238118: ; 0x02238118
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0x39
	add r6, r1, #0
	add r1, r0, #0
	add r1, #0xc7
	bl AllocFromHeap
	add r4, r0, #0
	ldr r0, _022381DC ; =0x00000000
	str r0, [r5]
	beq _022381D4
	mov r0, #0x5d
	mov r1, #6
	add r2, sp, #4
	mov r3, #0x39
	bl GfGfxLoader_GetPlttData
	add r7, r0, #0
	beq _02238152
	mov r0, #0
	add r1, r4, #0
	mov r2, #0x60
	bl MIi_CpuClear16
	add r0, r7, #0
	bl FreeToHeap
_02238152:
	add r1, r4, #0
	mov r0, #0
	add r1, #0xec
	str r0, [r1]
	add r1, r4, #0
	add r1, #0xe8
	str r0, [r1]
	add r1, r4, #0
	add r1, #0xf0
	str r0, [r1]
	add r1, r4, #0
	add r1, #0xf4
	str r0, [r1]
	add r1, r4, #0
	add r1, #0xe4
	str r5, [r1]
	add r1, r4, #0
	add r1, #0xf8
	str r0, [r1]
	add r1, r4, #0
	add r1, #0xfc
	str r6, [r1]
	add r3, r4, #0
	add r2, r0, #0
_02238182:
	add r1, r3, #0
	add r1, #0xc4
	add r0, r0, #1
	add r3, r3, #4
	str r2, [r1]
	cmp r0, #8
	blt _02238182
	mov r0, #8
	str r0, [sp]
	ldr r0, _022381E0 ; =0x04000050
	mov r1, #4
	mov r2, #0xc
	mov r3, #0x10
	bl G2x_SetBlendAlpha_
	mov r0, #8
	str r0, [sp]
	ldr r0, _022381E4 ; =0x04001050
	mov r1, #4
	mov r2, #0xc
	mov r3, #0x10
	bl G2x_SetBlendAlpha_
	ldr r0, _022381E8 ; =MOD81_02238248
	add r1, r4, #0
	mov r2, #0x14
	bl FUN_0200CA44
	add r1, r4, #0
	add r1, #0xc0
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	cmp r0, #0
	beq _022381D4
	add r0, r4, #0
	add r0, #0xe4
	ldr r0, [r0]
	mov r1, #1
	str r1, [r0]
_022381D4:
	add r0, r4, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022381DC: .word 0x00000000
_022381E0: .word 0x04000050
_022381E4: .word 0x04001050
_022381E8: .word MOD81_02238248
	thumb_func_end MOD81_02238118

	thumb_func_start MOD81_022381EC
MOD81_022381EC: ; 0x022381EC
	add r1, r0, #0
	add r1, #0xe4
	ldr r1, [r1]
	ldr r1, [r1]
	cmp r1, #1
	bne _022381FE
	mov r1, #1
	add r0, #0xe8
	str r1, [r0]
_022381FE:
	bx lr
	thumb_func_end MOD81_022381EC

	thumb_func_start MOD81_02238200
MOD81_02238200: ; 0x02238200
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r0, #0xe4
	ldr r0, [r0]
	ldr r0, [r0]
	cmp r0, #1
	bne _02238246
	mov r4, #0
	add r5, r6, #0
_02238212:
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #0
	beq _02238224
	add r0, r6, #0
	add r1, r4, #0
	bl MOD81_0223840C
_02238224:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #8
	blt _02238212
	add r0, r6, #0
	add r0, #0xe4
	ldr r0, [r0]
	mov r1, #0
	str r1, [r0]
	add r0, r6, #0
	add r0, #0xc0
	ldr r0, [r0]
	bl FUN_0200CAB4
	add r0, r6, #0
	bl FreeToHeap
_02238246:
	pop {r4, r5, r6, pc}
	thumb_func_end MOD81_02238200

	thumb_func_start MOD81_02238248
MOD81_02238248: ; 0x02238248
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0xe8
	ldr r0, [r0]
	cmp r0, #0
	bne _022382C6
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xf0
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	cmp r0, #0
	bgt _02238284
	ldr r0, _0223832C ; =0x000006AE
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0x1e
	add r0, #0xf0
	str r1, [r0]
	add r0, r4, #0
	bl MOD81_02238358
_02238284:
	add r0, r4, #0
	add r0, #0xec
	ldr r0, [r0]
	cmp r0, #0
	beq _02238328
	bl GX_BeginLoadBGExtPltt
	bl GXS_BeginLoadBGExtPltt
	add r0, r4, #0
	mov r1, #0x60
	bl DC_FlushRange
	mov r1, #6
	add r0, r4, #0
	lsl r1, r1, #0xc
	mov r2, #0x60
	bl GX_LoadBGExtPltt
	mov r1, #6
	add r0, r4, #0
	lsl r1, r1, #0xc
	mov r2, #0x60
	bl GXS_LoadBGExtPltt
	bl GX_EndLoadBGExtPltt
	bl GXS_EndLoadBGExtPltt
	mov r0, #0
	add r4, #0xec
	str r0, [r4]
	pop {r3, r4, r5, pc}
_022382C6:
	add r0, r4, #0
	add r0, #0xec
	ldr r0, [r0]
	cmp r0, #0
	beq _02238308
	bl GX_BeginLoadBGExtPltt
	bl GXS_BeginLoadBGExtPltt
	add r0, r4, #0
	mov r1, #0x60
	bl DC_FlushRange
	mov r1, #6
	add r0, r4, #0
	lsl r1, r1, #0xc
	mov r2, #0x60
	bl GX_LoadBGExtPltt
	mov r1, #6
	add r0, r4, #0
	lsl r1, r1, #0xc
	mov r2, #0x60
	bl GXS_LoadBGExtPltt
	bl GX_EndLoadBGExtPltt
	bl GXS_EndLoadBGExtPltt
	add r0, r4, #0
	mov r1, #0
	add r0, #0xec
	str r1, [r0]
_02238308:
	add r0, r4, #0
	add r0, #0xf4
	ldr r0, [r0]
	cmp r0, #0
	bne _02238328
	add r0, r4, #0
	add r0, #0xe4
	ldr r0, [r0]
	mov r1, #0
	str r1, [r0]
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02238328:
	pop {r3, r4, r5, pc}
	nop
_0223832C: .word 0x000006AE
	thumb_func_end MOD81_02238248

	thumb_func_start MOD81_02238330
MOD81_02238330: ; 0x02238330
	push {r3, r4}
	cmp r1, #0
	blt _02238340
	cmp r1, #0x60
	bge _02238340
	mov r4, #0
	lsl r1, r1, #1
	strh r4, [r0, r1]
_02238340:
	cmp r2, #0
	blt _0223834C
	cmp r2, #0x60
	bge _0223834C
	lsl r1, r2, #1
	strh r3, [r0, r1]
_0223834C:
	mov r1, #1
	add r0, #0xec
	str r1, [r0]
	pop {r3, r4}
	bx lr
	.align 2, 0
	thumb_func_end MOD81_02238330

	thumb_func_start MOD81_02238358
MOD81_02238358: ; 0x02238358
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0xf8
	ldr r0, [r0]
	lsl r0, r0, #2
	add r0, r5, r0
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #0
	bne _02238404
	mov r0, #0x39
	mov r1, #0x18
	bl AllocFromHeap
	add r4, r0, #0
	beq _02238404
	add r0, r5, #0
	str r5, [r4]
	add r0, #0xfc
	ldr r0, [r0]
	cmp r0, #1
	bne _0223838A
	mov r0, #0
	mvn r0, r0
	b _0223838C
_0223838A:
	mov r0, #0xf
_0223838C:
	str r0, [r4, #4]
	mov r0, #0
	str r0, [r4, #0xc]
	mov r0, #2
	str r0, [r4, #8]
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	add r1, r4, #0
	str r0, [r4, #0x10]
	add r0, r5, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r2, #0xa
	str r0, [r4, #0x14]
	ldr r0, _02238408 ; =MOD81_0223843C
	bl FUN_0200CA44
	add r1, r5, #0
	add r1, #0xf8
	ldr r1, [r1]
	lsl r1, r1, #2
	add r1, r5, r1
	add r1, #0xc4
	str r0, [r1]
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	lsl r0, r0, #2
	add r0, r5, r0
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #0
	beq _022383FE
	add r0, r5, #0
	add r0, #0xf4
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0xf4
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0xf8
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	cmp r0, #8
	blt _02238404
	mov r0, #0
	add r5, #0xf8
	str r0, [r5]
	pop {r3, r4, r5, pc}
_022383FE:
	add r0, r4, #0
	bl FreeToHeap
_02238404:
	pop {r3, r4, r5, pc}
	nop
_02238408: .word MOD81_0223843C
	thumb_func_end MOD81_02238358

	thumb_func_start MOD81_0223840C
MOD81_0223840C: ; 0x0223840C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r5, #0
	lsl r4, r1, #2
	add r6, #0xc4
	ldr r0, [r6, r4]
	cmp r0, #0
	beq _0223843A
	bl FUN_0201B6C8
	bl FreeToHeap
	ldr r0, [r6, r4]
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r6, r4]
	add r0, r5, #0
	add r0, #0xf4
	ldr r0, [r0]
	add r5, #0xf4
	sub r0, r0, #1
	str r0, [r5]
_0223843A:
	pop {r4, r5, r6, pc}
	thumb_func_end MOD81_0223840C

	thumb_func_start MOD81_0223843C
MOD81_0223843C: ; 0x0223843C
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0xc]
	add r1, r0, #1
	str r1, [r4, #0xc]
	ldr r0, [r4, #8]
	cmp r1, r0
	blt _022384A4
	mov r3, #0
	str r3, [r4, #0xc]
	ldr r0, [r4, #0x14]
	cmp r0, #1
	bne _0223847C
	ldr r1, [r4, #4]
	ldr r0, [r4]
	add r2, r1, #1
	cmp r2, #0xf
	blt _0223846E
	bl MOD81_02238330
	ldr r0, [r4]
	ldr r1, [r4, #0x10]
	bl MOD81_0223840C
	pop {r4, pc}
_0223846E:
	ldr r3, _022384A8 ; =0x00007FFF
	bl MOD81_02238330
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, pc}
_0223847C:
	ldr r2, [r4, #4]
	ldr r0, [r4]
	cmp r2, #0
	bge _02238496
	add r1, r2, #0
	add r2, r2, #1
	bl MOD81_02238330
	ldr r0, [r4]
	ldr r1, [r4, #0x10]
	bl MOD81_0223840C
	pop {r4, pc}
_02238496:
	ldr r3, _022384A8 ; =0x00007FFF
	add r1, r2, #1
	bl MOD81_02238330
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
_022384A4:
	pop {r4, pc}
	nop
_022384A8: .word 0x00007FFF
	thumb_func_end MOD81_0223843C

	thumb_func_start MOD81_022384AC
MOD81_022384AC: ; 0x022384AC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp]
	add r6, r1, #0
	mov r0, #0x39
	mov r1, #0x24
	add r7, r2, #0
	str r3, [sp, #4]
	ldr r5, [sp, #0x28]
	bl AllocFromHeap
	add r4, r0, #0
	ldr r0, _0223850C ; =0x00000001
	str r0, [r5]
	beq _02238504
	ldr r1, [sp]
	str r1, [r4]
	str r6, [r4, #8]
	ldr r1, [sp, #4]
	str r7, [r4, #0xc]
	str r1, [r4, #0x10]
	ldr r1, [sp, #0x20]
	str r1, [r4, #0x14]
	cmp r6, r7
	bge _022384E0
	mov r0, #0
_022384E0:
	str r0, [r4, #0x18]
	ldr r0, [sp, #0x24]
	mov r2, #0
	str r0, [r4, #0x1c]
	str r5, [r4, #4]
	ldr r0, _02238510 ; =MOD81_02238514
	add r1, r4, #0
	str r2, [r5]
	bl FUN_0200CA60
	str r0, [r4, #0x20]
	cmp r0, #0
	bne _02238504
	mov r0, #1
	str r0, [r5]
	add r0, r4, #0
	bl FreeToHeap
_02238504:
	add r0, r4, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223850C: .word 0x00000001
_02238510: .word MOD81_02238514
	thumb_func_end MOD81_022384AC

	thumb_func_start MOD81_02238514
MOD81_02238514: ; 0x02238514
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #8]
	ldr r1, [r4, #0x10]
	mul r1, r0
	asr r2, r1, #0xc
	asr r1, r2, #4
	lsr r1, r1, #0x1b
	add r1, r2, r1
	asr r2, r1, #5
	ldr r1, [r4, #0x18]
	cmp r1, #0
	beq _02238536
	cmp r1, #1
	beq _0223854C
	b _02238560
_02238536:
	ldr r1, [r4, #0xc]
	add r0, r0, r2
	cmp r0, r1
	bge _02238542
	str r0, [r4, #8]
	b _02238560
_02238542:
	str r1, [r4, #8]
	ldr r0, [r4, #4]
	mov r1, #1
	str r1, [r0]
	b _02238560
_0223854C:
	ldr r1, [r4, #0xc]
	sub r0, r0, r2
	cmp r0, r1
	ble _02238558
	str r0, [r4, #8]
	b _02238560
_02238558:
	str r1, [r4, #8]
	ldr r0, [r4, #4]
	mov r1, #1
	str r1, [r0]
_02238560:
	add r0, r4, #0
	bl MOD81_02238588
	ldr r0, [r4, #4]
	ldr r0, [r0]
	cmp r0, #0
	beq _0223857C
	add r0, r4, #0
	bl MOD81_02238898
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
_0223857C:
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x14]
	add r0, r1, r0
	str r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD81_02238514

	thumb_func_start MOD81_02238588
MOD81_02238588: ; 0x02238588
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r0, [r4, #8]
	add r2, sp, #4
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, [r4, #8]
	mov r3, #0x80
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x1c]
	lsl r1, r0, #2
	ldr r0, _022385CC ; =0x0223CF6C
	ldr r0, [r0, r1]
	mov r1, #2
	str r0, [sp]
	ldr r0, [r4]
	bl FUN_02017BD0
	ldr r0, [r4, #0x1c]
	add r2, sp, #4
	lsl r1, r0, #2
	ldr r0, _022385CC ; =0x0223CF6C
	mov r3, #0x80
	ldr r0, [r0, r1]
	mov r1, #6
	str r0, [sp]
	ldr r0, [r4]
	bl FUN_02017BD0
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0
_022385CC: .word MOD81_0223CF6C
	thumb_func_end MOD81_02238588

	thumb_func_start MOD81_022385D0
MOD81_022385D0: ; 0x022385D0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	add r5, r0, #0
	ldr r0, [sp, #0x58]
	add r4, r1, #0
	str r2, [sp, #0x14]
	str r3, [sp, #0x18]
	cmp r0, #0
	beq _022385E8
	mov r6, #0x19
	lsl r6, r6, #8
	b _022385EC
_022385E8:
	mov r6, #0x32
	lsl r6, r6, #6
_022385EC:
	mov r0, #0x39
	add r1, r6, #0
	bl AllocFromHeapAtEnd
	add r7, r0, #0
	beq _02238690
	ldr r3, _022386B8 ; =0x0223CF74
	add r2, sp, #0x24
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	cmp r4, #0
	ldr r0, [r5]
	bne _0223860E
	ldr r4, [r0]
	b _02238610
_0223860E:
	ldr r4, [r0, #4]
_02238610:
	add r0, r4, #0
	bl AcquireBoxMonLock
	str r0, [sp, #0x20]
	add r0, sp, #0x34
	add r1, r4, #0
	mov r2, #2
	bl FUN_02068B70
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl GetBoxMonData
	str r0, [sp, #0x1c]
	add r0, r4, #0
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	lsl r0, r0, #0x10
	ldr r1, [sp, #0x58]
	lsr r0, r0, #0x10
	cmp r1, #0
	beq _02238648
	ldr r1, [sp, #0x2c]
	lsl r1, r1, #1
	str r1, [sp, #0x2c]
_02238648:
	ldr r1, [sp, #0x1c]
	str r7, [sp]
	str r1, [sp, #4]
	ldr r1, [sp, #0x58]
	mov r2, #0x39
	str r1, [sp, #8]
	mov r1, #2
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	add r1, sp, #0x24
	ldrh r0, [r1, #0x10]
	ldrh r1, [r1, #0x12]
	add r3, sp, #0x24
	bl FUN_02012530
	add r0, r7, #0
	add r1, r6, #0
	bl DC_FlushRange
	ldr r1, [sp, #0x14]
	mov r0, #0
	str r0, [sp]
	lsl r1, r1, #0x18
	ldr r0, [r5, #8]
	lsr r1, r1, #0x18
	add r2, r7, #0
	add r3, r6, #0
	bl FUN_02017E14
	ldr r1, [sp, #0x20]
	add r0, r4, #0
	bl ReleaseBoxMonLock
	add r0, r7, #0
	bl FreeToHeap
_02238690:
	ldr r0, [sp, #0x14]
	cmp r0, #4
	blo _0223869A
	mov r2, #4
	b _0223869C
_0223869A:
	mov r2, #0
_0223869C:
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x39
	ldr r3, [sp, #0x18]
	str r0, [sp, #4]
	add r1, sp, #0x24
	ldrh r0, [r1, #0x10]
	ldrh r1, [r1, #0x14]
	lsl r3, r3, #5
	bl GfGfxLoader_GXLoadPal
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	nop
_022386B8: .word MOD81_0223CF74
	thumb_func_end MOD81_022385D0

	thumb_func_start MOD81_022386BC
MOD81_022386BC: ; 0x022386BC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	add r4, r2, #0
	add r6, r3, #0
	cmp r1, #0
	bne _022386CE
	mov r1, #0xc6
	b _022386DE
_022386CE:
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _022386DC
	mov r1, #0xc7
	b _022386DE
_022386DC:
	mov r1, #0xc6
_022386DE:
	mov r0, #0x39
	str r0, [sp]
	mov r0, #7
	mov r2, #0
	add r3, sp, #0x1c
	bl GfGfxLoader_GetScrnData
	add r7, r0, #0
	beq _02238746
	mov r0, #0xa
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [sp, #0x1c]
	ldr r2, [sp, #0x38]
	add r0, #0xc
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #0x20
	ldr r3, [sp, #0x3c]
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	lsl r1, r4, #0x18
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r5, #8]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02018170
	mov r0, #0xa
	str r0, [sp]
	str r0, [sp, #4]
	lsl r0, r6, #0x18
	ldr r2, [sp, #0x38]
	ldr r3, [sp, #0x3c]
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	lsl r1, r4, #0x18
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r5, #8]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_020186B4
	add r0, r7, #0
	bl FreeToHeap
_02238746:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD81_022386BC

	thumb_func_start MOD81_0223874C
MOD81_0223874C: ; 0x0223874C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	add r4, r1, #0
	add r6, r3, #0
	mov r0, #0x3a
	add r3, r5, #0
	str r0, [sp]
	add r1, r2, #0
	add r0, r4, #0
	mov r2, #1
	add r3, #8
	bl GfGfxLoader_GetCellBank
	str r0, [r5]
	mov r0, #0x3a
	add r3, r5, #0
	str r0, [sp]
	add r0, r4, #0
	add r1, r6, #0
	mov r2, #1
	add r3, #0xc
	bl GfGfxLoader_GetAnimBank
	str r0, [r5, #4]
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD81_0223874C

	thumb_func_start MOD81_02238784
MOD81_02238784: ; 0x02238784
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _02238796
	bl FreeToHeap
	mov r0, #0
	str r0, [r4]
_02238796:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _022387A4
	bl FreeToHeap
	mov r0, #0
	str r0, [r4, #4]
_022387A4:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_02238784

	thumb_func_start MOD81_022387A8
MOD81_022387A8: ; 0x022387A8
	str r2, [r0]
	str r3, [r0, #8]
	ldr r2, [r1, #8]
	str r2, [r0, #0xc]
	ldr r1, [r1, #0xc]
	ldr r2, [sp]
	str r1, [r0, #0x10]
	add r1, r0, #0
	add r1, #0x20
	strb r2, [r1]
	mov r1, #0
	str r1, [r0, #4]
	str r1, [r0, #0x14]
	str r1, [r0, #0x18]
	str r1, [r0, #0x1c]
	bx lr
	thumb_func_end MOD81_022387A8

	thumb_func_start MOD81_022387C8
MOD81_022387C8: ; 0x022387C8
	push {r4, lr}
	sub sp, #0x20
	ldr r0, [r0, #0x18]
	str r0, [sp]
	lsl r0, r2, #0xc
	str r0, [sp, #8]
	lsl r0, r3, #0xc
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x28]
	str r1, [sp, #4]
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x2c]
	str r0, [sp, #0x18]
	mov r0, #0x39
	str r0, [sp, #0x1c]
	add r0, sp, #0
	bl FUN_0201FF84
	add r4, r0, #0
	beq _02238804
	mov r1, #1
	bl FUN_020200BC
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_020200D8
_02238804:
	add r0, r4, #0
	add sp, #0x20
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_022387C8

	thumb_func_start MOD81_0223880C
MOD81_0223880C: ; 0x0223880C
	ldr r0, [r0, #8]
	bx lr
	thumb_func_end MOD81_0223880C

	thumb_func_start MOD81_02238810
MOD81_02238810: ; 0x02238810
	ldr r0, [r0, #0xc]
	bx lr
	thumb_func_end MOD81_02238810

	thumb_func_start MOD81_02238814
MOD81_02238814: ; 0x02238814
	ldr r0, [r0, #0x10]
	bx lr
	thumb_func_end MOD81_02238814

	thumb_func_start MOD81_02238818
MOD81_02238818: ; 0x02238818
	ldr r0, [r0]
	ldr r0, [r0]
	bx lr
	.align 2, 0
	thumb_func_end MOD81_02238818

	thumb_func_start MOD81_02238820
MOD81_02238820: ; 0x02238820
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bx lr
	.align 2, 0
	thumb_func_end MOD81_02238820

	thumb_func_start MOD81_02238828
MOD81_02238828: ; 0x02238828
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bx lr
	.align 2, 0
	thumb_func_end MOD81_02238828

	thumb_func_start MOD81_02238830
MOD81_02238830: ; 0x02238830
	mov r1, #0x53
	lsl r1, r1, #2
	ldrh r0, [r0, r1]
	bx lr
	thumb_func_end MOD81_02238830

	thumb_func_start MOD81_02238838
MOD81_02238838: ; 0x02238838
	ldr r1, _02238840 ; =0x0000014E
	ldrh r0, [r0, r1]
	bx lr
	nop
_02238840: .word 0x0000014E
	thumb_func_end MOD81_02238838

	thumb_func_start MOD81_02238844
MOD81_02238844: ; 0x02238844
	ldr r0, [r0]
	ldr r3, _0223884C ; =Options_GetFrame
	ldr r0, [r0, #0x14]
	bx r3
	.align 2, 0
_0223884C: .word Options_GetFrame
	thumb_func_end MOD81_02238844

	thumb_func_start MOD81_02238850
MOD81_02238850: ; 0x02238850
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	bx lr
	.align 2, 0
	thumb_func_end MOD81_02238850

	thumb_func_start MOD81_02238858
MOD81_02238858: ; 0x02238858
	ldr r0, _02238860 ; =0x0223D3C0
	mov r1, #0
	str r1, [r0]
	bx lr
	.align 2, 0
_02238860: .word MOD81_0223D3C0
	thumb_func_end MOD81_02238858

	thumb_func_start MOD81_02238864
MOD81_02238864: ; 0x02238864
	push {r4, r5, r6, lr}
	ldr r6, _02238890 ; =0x0223D3C0
	ldr r0, [r6]
	cmp r0, #0
	beq _0223888C
	mov r4, #0
	cmp r0, #0
	ble _02238886
	ldr r5, _02238894 ; =0x0223D3C4
_02238876:
	ldr r0, [r5]
	bl FreeToHeap
	ldr r0, [r6]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blt _02238876
_02238886:
	ldr r0, _02238890 ; =0x0223D3C0
	mov r1, #0
	str r1, [r0]
_0223888C:
	pop {r4, r5, r6, pc}
	nop
_02238890: .word MOD81_0223D3C0
_02238894: .word MOD81_0223D3C4
	thumb_func_end MOD81_02238864

	thumb_func_start MOD81_02238898
MOD81_02238898: ; 0x02238898
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _022388B8 ; =0x0223D3C0
	ldr r0, [r0]
	cmp r0, #0x20
	blt _022388A8
	bl GF_AssertFail
_022388A8:
	ldr r0, _022388B8 ; =0x0223D3C0
	ldr r2, [r0]
	add r1, r2, #1
	str r1, [r0]
	ldr r0, _022388BC ; =0x0223D3C4
	lsl r1, r2, #2
	str r4, [r0, r1]
	pop {r4, pc}
	.align 2, 0
_022388B8: .word MOD81_0223D3C0
_022388BC: .word MOD81_0223D3C4
	thumb_func_end MOD81_02238898

	thumb_func_start MOD81_022388C0
MOD81_022388C0: ; 0x022388C0
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r4, r1, #0
	mov r0, #0x3a
	mov r1, #0x20
	add r5, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r6, r0, #0
	beq _02238906
	ldr r3, [sp]
	add r1, r4, #0
	add r2, r5, #0
	bl MOD81_02238CA0
	mov r1, #0x8c
	mov r0, #0x3a
	mul r1, r7
	bl AllocFromHeap
	str r0, [r6, #0x18]
	mov r4, #0
	str r7, [r6, #0x1c]
	cmp r7, #0
	bls _02238906
	add r5, r4, #0
_022388F6:
	ldr r0, [r6, #0x18]
	add r0, r0, r5
	bl MOD81_02238A38
	add r4, r4, #1
	add r5, #0x8c
	cmp r4, r7
	blo _022388F6
_02238906:
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD81_022388C0

	thumb_func_start MOD81_0223890C
MOD81_0223890C: ; 0x0223890C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x1c]
	mov r6, #0
	cmp r0, #0
	bls _0223892C
	add r4, r6, #0
_0223891A:
	ldr r0, [r5, #0x18]
	add r0, r0, r4
	bl MOD81_02238A6C
	ldr r0, [r5, #0x1c]
	add r6, r6, #1
	add r4, #0x8c
	cmp r6, r0
	blo _0223891A
_0223892C:
	ldr r0, [r5, #0x18]
	bl FreeToHeap
	add r0, r5, #0
	bl MOD81_02238D0C
	add r0, r5, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
	thumb_func_end MOD81_0223890C

	thumb_func_start MOD81_02238940
MOD81_02238940: ; 0x02238940
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	mov r1, #0
	add r5, r0, #0
	mov r0, #0x11
	add r2, r1, #0
	bl NNS_G3dGeBufferOP_N
	bl FUN_0201EBA4
	ldr r0, [r5, #0x1c]
	mov r6, #0
	cmp r0, #0
	bls _02238976
	add r4, r6, #0
_0223895E:
	ldr r0, [r5, #0x18]
	add r0, r0, r4
	ldr r1, [r0, #0x64]
	cmp r1, #0
	beq _0223896C
	bl MOD81_02238988
_0223896C:
	ldr r0, [r5, #0x1c]
	add r6, r6, #1
	add r4, #0x8c
	cmp r6, r0
	blo _0223895E
_02238976:
	mov r2, #1
	mov r0, #0x12
	add r1, sp, #0
	str r2, [sp]
	bl NNS_G3dGeBufferOP_N
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD81_02238940

	thumb_func_start MOD81_02238988
MOD81_02238988: ; 0x02238988
	push {r4, lr}
	sub sp, #0x50
	add r4, r0, #0
	add r0, sp, #0x2c
	bl MTX_Identity33_
	add r0, r4, #0
	add r0, #0x80
	ldrh r0, [r0]
	ldr r3, _02238A34 ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #8
	bl MTX_RotX33_
	add r1, sp, #0x2c
	add r0, sp, #8
	add r2, r1, #0
	bl MTX_Concat33
	add r0, r4, #0
	add r0, #0x82
	ldrh r0, [r0]
	ldr r3, _02238A34 ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #8
	bl MTX_RotY33_
	add r1, sp, #0x2c
	add r0, sp, #8
	add r2, r1, #0
	bl MTX_Concat33
	add r0, r4, #0
	add r0, #0x84
	ldrh r0, [r0]
	ldr r3, _02238A34 ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #8
	bl MTX_RotZ33_
	add r1, sp, #0x2c
	add r0, sp, #8
	add r2, r1, #0
	bl MTX_Concat33
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #0x1f
	beq _02238A20
	str r0, [sp]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	str r0, [sp, #4]
	bl NNS_G3dGlbPolygonAttr
_02238A20:
	add r1, r4, #0
	add r0, r4, #4
	add r4, #0x74
	add r1, #0x68
	add r2, sp, #0x2c
	add r3, r4, #0
	bl FUN_0201B26C
	add sp, #0x50
	pop {r4, pc}
	.align 2, 0
_02238A34: .word FX_SinCosTable_
	thumb_func_end MOD81_02238988

	thumb_func_start MOD81_02238A38
MOD81_02238A38: ; 0x02238A38
	mov r1, #0
	str r1, [r0, #0x64]
	add r2, r0, #0
	str r1, [r0]
	add r2, #0x84
	strh r1, [r2]
	mov r2, #0x84
	ldrsh r3, [r0, r2]
	add r2, r0, #0
	add r2, #0x82
	strh r3, [r2]
	mov r2, #0x82
	ldrsh r3, [r0, r2]
	add r2, r0, #0
	add r2, #0x80
	strh r3, [r2]
	mov r2, #1
	lsl r2, r2, #0xc
	str r2, [r0, #0x7c]
	str r2, [r0, #0x78]
	str r2, [r0, #0x74]
	str r1, [r0, #0x70]
	str r1, [r0, #0x6c]
	str r1, [r0, #0x68]
	bx lr
	.align 2, 0
	thumb_func_end MOD81_02238A38

	thumb_func_start MOD81_02238A6C
MOD81_02238A6C: ; 0x02238A6C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _02238A80
	bl FreeToHeap
	mov r0, #0
	str r0, [r4]
	str r0, [r4, #0x64]
_02238A80:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_02238A6C

	thumb_func_start MOD81_02238A84
MOD81_02238A84: ; 0x02238A84
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	ldr r4, [r0, #0x18]
	add r6, r1, #0
	mov r0, #0x8c
	mul r6, r0
	add r7, r2, #0
	mov r0, #1
	str r0, [sp]
	str r3, [sp, #4]
	add r1, r3, #0
	add r0, r7, #0
	mov r2, #0
	mov r3, #0x3a
	add r5, r4, r6
	bl GfGfxLoader_LoadFromNarc
	str r0, [r4, r6]
	ldr r1, [sp, #4]
	add r0, r7, #0
	bl GetNarcMemberSizeByIdPair
	add r1, r0, #0
	ldr r0, [r4, r6]
	bl DC_FlushRange
	ldr r0, [r4, r6]
	cmp r0, #0
	beq _02238B02
	bl NNS_G3dGetMdlSet
	str r0, [r5, #0x58]
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r0, r0, r1
	str r0, [r5, #0x5c]
	ldr r0, [r5]
	bl NNS_G3dGetTex
	str r0, [r5, #0x60]
	bl FUN_0201B3C4
	ldr r0, [r5]
	ldr r1, [r5, #0x60]
	bl FUN_0201B3A8
	ldr r1, [r5, #0x5c]
	add r0, r5, #4
	bl NNS_G3dRenderObjInit
	ldr r0, [sp, #0x20]
	mov r1, #0x1f
	str r0, [r5, #0x68]
	ldr r0, [sp, #0x24]
	str r0, [r5, #0x6c]
	ldr r0, [sp, #0x28]
	str r0, [r5, #0x70]
	add r0, r5, #0
	add r0, #0x88
	str r1, [r0]
	ldr r0, [sp, #0x2c]
	str r0, [r5, #0x64]
_02238B02:
	add r0, r5, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD81_02238A84

	thumb_func_start MOD81_02238B08
MOD81_02238B08: ; 0x02238B08
	add r2, r0, #0
	add r2, #0x68
	add r3, r1, #0
	ldmia r2!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r2]
	str r0, [r3]
	bx lr
	thumb_func_end MOD81_02238B08

	thumb_func_start MOD81_02238B18
MOD81_02238B18: ; 0x02238B18
	add r3, r1, #0
	add r2, r0, #0
	ldmia r3!, {r0, r1}
	add r2, #0x68
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	bx lr
	thumb_func_end MOD81_02238B18

	thumb_func_start MOD81_02238B28
MOD81_02238B28: ; 0x02238B28
	add r2, r0, #0
	add r2, #0x80
	ldrh r2, [r2]
	strh r2, [r1]
	add r2, r0, #0
	add r2, #0x82
	ldrh r2, [r2]
	add r0, #0x84
	strh r2, [r1, #2]
	ldrh r0, [r0]
	strh r0, [r1, #4]
	bx lr
	thumb_func_end MOD81_02238B28

	thumb_func_start MOD81_02238B40
MOD81_02238B40: ; 0x02238B40
	ldrh r3, [r1]
	add r2, r0, #0
	add r2, #0x80
	strh r3, [r2]
	add r2, r0, #0
	ldrh r3, [r1, #2]
	add r2, #0x82
	add r0, #0x84
	strh r3, [r2]
	ldrh r1, [r1, #4]
	strh r1, [r0]
	bx lr
	thumb_func_end MOD81_02238B40

	thumb_func_start MOD81_02238B58
MOD81_02238B58: ; 0x02238B58
	str r1, [r0, #0x64]
	bx lr
	thumb_func_end MOD81_02238B58

	thumb_func_start MOD81_02238B5C
MOD81_02238B5C: ; 0x02238B5C
	push {r3, lr}
	add r2, r0, #0
	add r2, #0x88
	str r1, [r2]
	cmp r1, #0x1f
	ldr r0, [r0, #0x5c]
	beq _02238B76
	mov r2, #0x1f
	mov r1, #0
	lsl r2, r2, #0x10
	bl NNSi_G3dModifyPolygonAttrMask
	pop {r3, pc}
_02238B76:
	mov r2, #0x1f
	mov r1, #1
	lsl r2, r2, #0x10
	bl NNSi_G3dModifyPolygonAttrMask
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD81_02238B5C

	thumb_func_start MOD81_02238B84
MOD81_02238B84: ; 0x02238B84
	str r1, [r0, #0x74]
	str r1, [r0, #0x78]
	str r1, [r0, #0x7c]
	bx lr
	thumb_func_end MOD81_02238B84

	thumb_func_start MOD81_02238B8C
MOD81_02238B8C: ; 0x02238B8C
	push {r3, r4, lr}
	sub sp, #0x4c
	add r4, r0, #0
	add r0, sp, #0x28
	bl MTX_Identity33_
	add r0, r4, #0
	add r0, #0x80
	ldrh r0, [r0]
	ldr r3, _02238C3C ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #4
	bl MTX_RotX33_
	add r1, sp, #0x28
	add r0, sp, #4
	add r2, r1, #0
	bl MTX_Concat33
	add r0, r4, #0
	add r0, #0x82
	ldrh r0, [r0]
	ldr r3, _02238C3C ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #4
	bl MTX_RotY33_
	add r1, sp, #0x28
	add r0, sp, #4
	add r2, r1, #0
	bl MTX_Concat33
	add r0, r4, #0
	add r0, #0x84
	ldrh r0, [r0]
	ldr r3, _02238C3C ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #4
	bl MTX_RotZ33_
	add r1, sp, #0x28
	add r0, sp, #4
	add r2, r1, #0
	bl MTX_Concat33
	mov r1, #0
	mov r0, #0x11
	add r2, r1, #0
	bl NNS_G3dGeBufferOP_N
	bl FUN_0201EBA4
	add r1, r4, #0
	ldr r0, [r4, #0x5c]
	add r4, #0x74
	add r1, #0x68
	add r2, sp, #0x28
	add r3, r4, #0
	bl FUN_0201B6D0
	add r4, r0, #0
	mov r2, #1
	mov r0, #0x12
	add r1, sp, #0
	str r2, [sp]
	bl NNS_G3dGeBufferOP_N
	add r0, r4, #0
	add sp, #0x4c
	pop {r3, r4, pc}
	.align 2, 0
_02238C3C: .word FX_SinCosTable_
	thumb_func_end MOD81_02238B8C

	thumb_func_start MOD81_02238C40
MOD81_02238C40: ; 0x02238C40
	push {r3, r4, lr}
	sub sp, #0xc
	add r2, r0, #0
	add r4, r1, #0
	ldr r1, [r2]
	add r0, sp, #0
	bl FUN_0201F03C
	add r2, sp, #0
	ldmia r2!, {r0, r1}
	stmia r4!, {r0, r1}
	ldr r0, [r2]
	str r0, [r4]
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD81_02238C40

	thumb_func_start MOD81_02238C60
MOD81_02238C60: ; 0x02238C60
	ldr r3, _02238C6C ; =FUN_0201EF90
	add r2, r0, #0
	add r0, r1, #0
	ldr r1, [r2]
	bx r3
	nop
_02238C6C: .word FUN_0201EF90
	thumb_func_end MOD81_02238C60

	thumb_func_start MOD81_02238C70
MOD81_02238C70: ; 0x02238C70
	ldr r3, _02238C7C ; =FUN_0201EFB4
	add r2, r0, #0
	add r0, r1, #0
	ldr r1, [r2]
	bx r3
	nop
_02238C7C: .word FUN_0201EFB4
	thumb_func_end MOD81_02238C70

	thumb_func_start MOD81_02238C80
MOD81_02238C80: ; 0x02238C80
	ldr r3, _02238C8C ; =FUN_0201EE2C
	add r2, r0, #0
	add r0, r1, #0
	ldr r1, [r2]
	bx r3
	nop
_02238C8C: .word FUN_0201EE2C
	thumb_func_end MOD81_02238C80

	thumb_func_start MOD81_02238C90
MOD81_02238C90: ; 0x02238C90
	ldr r3, _02238C9C ; =FUN_0201EEF0
	add r2, r0, #0
	add r0, r1, #0
	ldr r1, [r2]
	bx r3
	nop
_02238C9C: .word FUN_0201EEF0
	thumb_func_end MOD81_02238C90

	thumb_func_start MOD81_02238CA0
MOD81_02238CA0: ; 0x02238CA0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	mov r0, #0x3a
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl FUN_0201EB64
	str r0, [r5]
	str r4, [r5, #4]
	str r6, [r5, #8]
	mov r1, #0x4b
	add r2, r5, #0
	str r7, [r5, #0xc]
	mov r0, #0
	strh r0, [r5, #0x10]
	strh r0, [r5, #0x12]
	strh r0, [r5, #0x14]
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5]
	ldr r3, _02238D08 ; =0x00000FA4
	str r0, [sp, #8]
	add r0, r5, #4
	lsl r1, r1, #0xe
	add r2, #0x10
	bl FUN_0201ECA8
	mov r1, #0
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #0x10]
	str r1, [sp, #0xc]
	str r1, [sp, #0x14]
	ldr r1, [r5]
	add r0, sp, #0xc
	bl FUN_0201EC58
	ldr r0, [r5]
	bl FUN_0201EB8C
	mov r1, #0xfa
	ldr r2, [r5]
	mov r0, #0
	lsl r1, r1, #0xe
	bl FUN_0201EC94
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02238D08: .word 0x00000FA4
	thumb_func_end MOD81_02238CA0

	thumb_func_start MOD81_02238D0C
MOD81_02238D0C: ; 0x02238D0C
	ldr r3, _02238D14 ; =FUN_0201EB70
	ldr r0, [r0]
	bx r3
	nop
_02238D14: .word FUN_0201EB70
	thumb_func_end MOD81_02238D0C

	thumb_func_start MOD81_02238D18
MOD81_02238D18: ; 0x02238D18
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x3a
	mov r1, #0x6c
	bl AllocFromHeap
	add r4, r0, #0
	beq _02238D60
	str r5, [r4]
	mov r0, #0
	str r0, [r4, #4]
	add r0, r5, #0
	bl MOD81_0223880C
	str r0, [r4, #0x40]
	mov r0, #0x3a
	bl FUN_02006D98
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4, #0x10]
	mov r0, #0x4b
	lsl r0, r0, #2
	mov r1, #0x3a
	bl String_ctor
	str r0, [r4, #0x54]
	mov r0, #0x4b
	lsl r0, r0, #2
	mov r1, #0x3a
	bl String_ctor
	str r0, [r4, #0x58]
	mov r0, #0
	str r0, [r4, #0x64]
	str r0, [r4, #0x68]
_02238D60:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD81_02238D18

	thumb_func_start MOD81_02238D64
MOD81_02238D64: ; 0x02238D64
	push {r4, lr}
	add r4, r0, #0
	beq _02238DC2
	bl MOD81_0223951C
	add r0, r4, #0
	bl MOD81_022395E8
	add r0, r4, #0
	bl MOD81_02239498
	ldr r0, [r4, #0x54]
	bl String_dtor
	ldr r0, [r4, #0x58]
	bl String_dtor
	ldr r0, [r4, #0x5c]
	bl MOD81_0223890C
	ldr r0, [r4, #0x40]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #0x40]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #0x40]
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	add r0, #0x44
	bl RemoveWindow
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _02238DB6
	bl FUN_02007534
_02238DB6:
	ldr r0, [r4, #0xc]
	bl FUN_020072E8
	add r0, r4, #0
	bl FreeToHeap
_02238DC2:
	pop {r4, pc}
	thumb_func_end MOD81_02238D64

	thumb_func_start MOD81_02238DC4
MOD81_02238DC4: ; 0x02238DC4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r2, [r4]
	add r5, r0, #0
	cmp r2, #4
	bhs _02238DF2
	lsl r3, r2, #2
	ldr r2, _02238DF8 ; =0x0223CFFC
	add r1, r5, #4
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #0
	beq _02238DE8
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	str r0, [r5, #4]
_02238DE8:
	add r0, r5, #0
	bl MOD81_02238DFC
	mov r0, #0
	pop {r3, r4, r5, pc}
_02238DF2:
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_02238DF8: .word MOD81_0223CFFC
	thumb_func_end MOD81_02238DC4

	thumb_func_start MOD81_02238DFC
MOD81_02238DFC: ; 0x02238DFC
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	bl G3X_ResetMtxStack
	mov r1, #0
	mov r0, #0x11
	add r2, r1, #0
	bl NNS_G3dGeBufferOP_N
	bl NNS_G3dGeFlushBuffer
	bl NNS_G2dSetupSoftwareSpriteCamera
	ldr r0, [r4, #0xc]
	bl FUN_020081C4
	ldr r0, [r4, #0xc]
	bl FUN_02006ED4
	mov r2, #1
	str r2, [sp]
	mov r0, #0x12
	add r1, sp, #0
	bl NNS_G3dGeBufferOP_N
	ldr r0, [r4, #0x5c]
	bl MOD81_02238940
	mov r0, #0
	add r1, r0, #0
	bl FUN_020222B4
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD81_02238DFC

	thumb_func_start MOD81_02238E44
MOD81_02238E44: ; 0x02238E44
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	ldr r0, _02239040 ; =0x0223D054
	bl GX_SetBanks
	ldr r2, _02239044 ; =0x04000304
	ldr r0, _02239048 ; =0xFFFF7FFF
	ldrh r1, [r2]
	and r0, r1
	strh r0, [r2]
	ldr r0, _0223904C ; =0x0223D00C
	bl FUN_02016BBC
	ldr r0, [r4, #0x40]
	ldr r2, _02239050 ; =0x0223D01C
	mov r1, #1
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x40]
	ldr r2, _02239054 ; =0x0223D038
	mov r1, #2
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x40]
	ldr r2, _02239054 ; =0x0223D038
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r2, _02239058 ; =0x04000008
	mov r0, #3
	ldrh r3, [r2]
	mov r1, #1
	bic r3, r0
	add r0, r3, #0
	orr r0, r1
	strh r0, [r2]
	mov r2, #0
	str r2, [sp]
	ldr r0, [r4, #0x40]
	add r3, r1, #0
	bl FUN_02017F48
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	ldr r0, [r4, #0x40]
	mov r1, #1
	add r3, r2, #0
	bl FUN_02018540
	ldr r0, [r4]
	bl MOD81_02238844
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x3a
	str r0, [sp, #4]
	ldr r0, [r4, #0x40]
	mov r1, #1
	mov r2, #0x6d
	mov r3, #2
	bl FUN_0200CD68
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	add r1, r4, #0
	str r0, [sp, #8]
	mov r2, #1
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	ldr r0, [r4, #0x40]
	add r1, #0x44
	mov r3, #2
	bl AddWindowParameterized
	add r0, r4, #0
	add r0, #0x44
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r3, #0x20
	str r3, [sp]
	mov r0, #0x3a
	str r0, [sp, #4]
	mov r0, #0xe
	mov r1, #7
	mov r2, #0
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x40]
	mov r0, #0x5d
	mov r1, #0x16
	mov r3, #2
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x40]
	mov r0, #0x5d
	mov r1, #0x15
	mov r3, #2
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x3a
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x5d
	mov r1, #0x17
	add r3, r2, #0
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x40]
	mov r0, #0x5d
	mov r1, #0x16
	mov r3, #6
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x40]
	mov r0, #0x5d
	mov r1, #0x15
	mov r3, #6
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x3a
	str r0, [sp, #4]
	mov r0, #0x5d
	mov r1, #0x17
	mov r2, #4
	mov r3, #0
	bl GfGfxLoader_GXLoadPal
	ldr r0, [r4, #0x40]
	mov r1, #1
	bl FUN_02017CD0
	add r0, r4, #0
	bl MOD81_022392D8
	mov r1, #0
	mov r0, #1
	add r2, r1, #0
	add r3, r1, #0
	bl MOD81_022388C0
	str r0, [r4, #0x5c]
	add r0, r4, #0
	bl MOD81_022393A4
	str r0, [r4, #0x10]
	mov r1, #0
	mov r0, #0x6a
	str r1, [sp]
	lsl r0, r0, #0xa
	str r0, [sp, #4]
	ldr r0, _0223905C ; =0x00073800
	mov r2, #0x5d
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r4, #0x5c]
	mov r3, #0x1b
	bl MOD81_02238A84
	ldr r2, _02239060 ; =0x0223CFF4
	str r0, [r4, #0x60]
	ldrh r3, [r2]
	add r0, sp, #0x14
	add r1, sp, #0x14
	strh r3, [r0]
	ldrh r3, [r2, #2]
	ldrh r2, [r2, #4]
	strh r3, [r0, #2]
	strh r2, [r0, #4]
	ldr r0, [r4, #0x60]
	bl MOD81_02238B40
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	add r0, r4, #0
	bl MOD81_022393F4
	ldr r0, _02239064 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	bl FUN_02033E74
	mov r0, #1
	mov r1, #0x39
	bl FUN_02033F04
	mov r0, #0x10
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #1
	add sp, #0x1c
	pop {r3, r4, pc}
	.align 2, 0
_02239040: .word MOD81_0223D054
_02239044: .word 0x04000304
_02239048: .word 0xFFFF7FFF
_0223904C: .word MOD81_0223D00C
_02239050: .word MOD81_0223D01C
_02239054: .word MOD81_0223D038
_02239058: .word 0x04000008
_0223905C: .word 0x00073800
_02239060: .word MOD81_0223CFF4
_02239064: .word 0x04000050
	thumb_func_end MOD81_02238E44

	thumb_func_start MOD81_02239068
MOD81_02239068: ; 0x02239068
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1]
	cmp r0, #0
	bne _0223908E
	bl FUN_0200E308
	cmp r0, #0
	beq _0223908E
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl FUN_02020130
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #1
	pop {r4, pc}
_0223908E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_02239068

	thumb_func_start MOD81_02239094
MOD81_02239094: ; 0x02239094
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r4, r0, #0
	ldr r0, [r5]
	cmp r0, #4
	bhi _022390CE
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022390AE: ; jump table
	.short _022390B8 - _022390AE - 2 ; case 0
	.short _022390C4 - _022390AE - 2 ; case 1
	.short _02239138 - _022390AE - 2 ; case 2
	.short _022391BE - _022390AE - 2 ; case 3
	.short _022391DE - _022390AE - 2 ; case 4
_022390B8:
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _022391EE
_022390C4:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0xa
	bgt _022390D0
_022390CE:
	b _022391EE
_022390D0:
	ldr r0, [r4]
	bl MOD81_02238814
	str r0, [sp, #0xc]
	ldr r0, [r4]
	bl MOD81_02238810
	add r7, r0, #0
	ldr r0, [r4]
	bl MOD81_02238850
	cmp r0, #1
	bne _022390F0
	mov r1, #0
	mov r6, #2
	b _022390F4
_022390F0:
	mov r1, #4
	mov r6, #3
_022390F4:
	ldr r0, [sp, #0xc]
	ldr r2, [r4, #0x54]
	bl ReadMsgDataIntoString
	ldr r1, [r4, #0x58]
	ldr r2, [r4, #0x54]
	add r0, r7, #0
	bl StringExpandPlaceholders
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r3, [sp, #8]
	add r0, r4, #0
	ldr r2, [r4, #0x58]
	add r0, #0x44
	mov r1, #1
	bl AddTextPrinterParameterized
	add r0, r4, #0
	add r0, #0x44
	mov r1, #0x6d
	mov r2, #2
	bl FUN_0200D06C
	add r0, r4, #0
	add r0, #0x44
	bl CopyWindowToVram
	mov r0, #0
	str r0, [r4, #8]
	str r6, [r5]
	b _022391EE
_02239138:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0x3c
	ble _022391EE
	ldr r0, [r4]
	bl MOD81_02238814
	add r6, r0, #0
	ldr r0, [r4]
	bl MOD81_02238810
	add r7, r0, #0
	ldr r2, [r4, #0x54]
	add r0, r6, #0
	mov r1, #1
	bl ReadMsgDataIntoString
	ldr r1, [r4, #0x58]
	ldr r2, [r4, #0x54]
	add r0, r7, #0
	bl StringExpandPlaceholders
	ldr r0, [r4]
	bl MOD81_02238818
	mov r1, #0x4c
	mov r2, #0
	bl GetBoxMonData
	cmp r0, #0
	bne _0223918A
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_02007314
	ldr r0, [r4]
	bl MOD81_02238830
	bl FUN_02005578
_0223918A:
	add r0, r4, #0
	add r0, #0x44
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r3, [sp, #8]
	add r0, r4, #0
	ldr r2, [r4, #0x58]
	add r0, #0x44
	mov r1, #1
	bl AddTextPrinterParameterized
	add r0, r4, #0
	add r0, #0x44
	bl FUN_02019548
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _022391EE
_022391BE:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0x3c
	ble _022391EE
	add r0, r4, #0
	add r0, #0x44
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _022391EE
_022391DE:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0x14
	ble _022391EE
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022391EE:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD81_02239094

	thumb_func_start MOD81_022391F4
MOD81_022391F4: ; 0x022391F4
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldr r1, [r4]
	add r5, r0, #0
	cmp r1, #4
	bhi _022392CE
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223920E: ; jump table
	.short _02239218 - _0223920E - 2 ; case 0
	.short _02239232 - _0223920E - 2 ; case 1
	.short _02239258 - _0223920E - 2 ; case 2
	.short _02239284 - _0223920E - 2 ; case 3
	.short _022392B6 - _0223920E - 2 ; case 4
_02239218:
	ldr r0, _022392D4 ; =0x000006A8
	bl FUN_020054C8
	add r0, r5, #0
	mov r1, #0
	mov r2, #0x10
	mov r3, #0xc
	bl MOD81_022394BC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _022392CE
_02239232:
	bl MOD81_0223950C
	cmp r0, #0
	beq _022392CE
	ldr r0, [r5, #0x10]
	bl FUN_02007534
	ldr r0, [r5, #0x2c]
	mov r1, #0
	bl FUN_02020130
	ldr r0, [r5, #0x2c]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _022392CE
_02239258:
	ldr r0, [r5, #0x2c]
	bl FUN_02020388
	cmp r0, #0
	bne _022392CE
	ldr r0, [r5, #0x60]
	mov r1, #1
	bl MOD81_02238B58
	mov r1, #0x10
	add r0, r5, #0
	mov r2, #0
	add r3, r1, #0
	bl MOD81_022394BC
	add r0, r5, #0
	bl MOD81_02239578
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _022392CE
_02239284:
	bl MOD81_022395D4
	cmp r0, #2
	bge _02239296
	add r0, r5, #0
	bl MOD81_022395C4
	cmp r0, #1
	bne _022392CE
_02239296:
	mov r0, #0x18
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _022392CE
_022392B6:
	bl FUN_0200E308
	cmp r0, #0
	beq _022392CE
	add r0, r5, #0
	bl MOD81_022395C4
	cmp r0, #0
	beq _022392CE
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_022392CE:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_022392D4: .word 0x000006A8
	thumb_func_end MOD81_022391F4

	thumb_func_start MOD81_022392D8
MOD81_022392D8: ; 0x022392D8
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	bl NNS_G3dInit
	bl G3X_InitMtxStack
	ldr r0, _02239380 ; =0x04000060
	ldr r2, _02239384 ; =0xFFFFCFFD
	ldrh r1, [r0]
	and r1, r2
	strh r1, [r0]
	ldrh r3, [r0]
	add r1, r2, #2
	and r3, r1
	mov r1, #0x10
	orr r1, r3
	strh r1, [r0]
	ldrh r3, [r0]
	ldr r1, _02239388 ; =0x0000CFFB
	and r1, r3
	strh r1, [r0]
	add r1, r2, #2
	ldrh r3, [r0]
	lsr r2, r2, #0x11
	and r3, r1
	mov r1, #8
	orr r1, r3
	strh r1, [r0]
	mov r0, #0
	add r1, r0, #0
	mov r3, #0x3f
	str r0, [sp]
	bl G3X_SetClearColor
	ldr r1, _0223938C ; =0x04000540
	mov r0, #2
	str r0, [r1]
	ldr r0, _02239390 ; =0xBFFF0000
	str r0, [r1, #0x40]
	mov r0, #1
	add r1, r0, #0
	bl NNS_GfdInitFrmTexVramManager
	mov r0, #1
	lsl r0, r0, #0xe
	mov r1, #1
	bl NNS_GfdInitFrmPlttVramManager
	ldr r3, _02239394 ; =NNS_GfdDefaultFuncAllocTexVram
	mov r0, #1
	mov r1, #0
	ldr r3, [r3]
	lsl r0, r0, #0xe
	add r2, r1, #0
	blx r3
	ldr r3, _02239398 ; =NNS_GfdDefaultFuncAllocPlttVram
	add r4, r0, #0
	ldr r3, [r3]
	mov r0, #0x80
	mov r1, #0
	mov r2, #1
	blx r3
	ldr r2, _0223939C ; =0x7FFF0000
	add r6, r0, #0
	and r2, r4
	lsl r1, r4, #0x10
	lsr r2, r2, #0x10
	ldr r0, [r5, #0xc]
	lsr r1, r1, #0xd
	lsl r2, r2, #4
	bl FUN_020081A8
	ldr r2, _022393A0 ; =0xFFFF0000
	lsl r1, r6, #0x10
	and r2, r6
	lsr r2, r2, #0x10
	ldr r0, [r5, #0xc]
	lsr r1, r1, #0xd
	lsl r2, r2, #3
	bl FUN_020081B4
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02239380: .word 0x04000060
_02239384: .word 0xFFFFCFFD
_02239388: .word 0x0000CFFB
_0223938C: .word 0x04000540
_02239390: .word 0xBFFF0000
_02239394: .word NNS_GfdDefaultFuncAllocTexVram
_02239398: .word NNS_GfdDefaultFuncAllocPlttVram
_0223939C: .word 0x7FFF0000
_022393A0: .word 0xFFFF0000
	thumb_func_end MOD81_022392D8

	thumb_func_start MOD81_022393A4
MOD81_022393A4: ; 0x022393A4
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r4, r0, #0
	ldr r0, [r4]
	bl MOD81_02238818
	add r5, r0, #0
	add r0, sp, #0x10
	add r1, r5, #0
	mov r2, #2
	bl FUN_02068B70
	ldr r0, [r4]
	bl MOD81_02238830
	add r1, r0, #0
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02069010
	add r0, r5, #0
	mov r1, #2
	bl FUN_02068E1C
	add r3, r0, #0
	mov r1, #0
	str r1, [sp]
	add r0, r4, #0
	str r1, [sp, #4]
	add r0, #0x14
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r4, #0xc]
	add r3, #0x50
	add r1, sp, #0x10
	mov r2, #0x80
	bl FUN_020073A0
	add sp, #0x20
	pop {r3, r4, r5, pc}
	thumb_func_end MOD81_022393A4

	thumb_func_start MOD81_022393F4
MOD81_022393F4: ; 0x022393F4
	push {r4, lr}
	sub sp, #0x70
	add r4, r0, #0
	add r0, #0x30
	mov r1, #0x5d
	mov r2, #7
	mov r3, #8
	bl MOD81_0223874C
	add r0, sp, #0x5c
	bl NNS_G2dInitImagePaletteProxy
	add r0, sp, #0x38
	bl NNS_G2dInitImageProxy
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	add r0, sp, #0x38
	str r0, [sp, #0x10]
	mov r0, #0x5d
	mov r1, #9
	bl GfGfxLoader_LoadImageMapping
	mov r0, #0x3a
	str r0, [sp]
	add r0, sp, #0x5c
	str r0, [sp, #4]
	mov r0, #0x5d
	mov r1, #0xa
	mov r2, #1
	mov r3, #0
	bl GfGfxLoader_PartiallyLoadPalette
	mov r0, #2
	add r1, r4, #0
	str r0, [sp]
	add r0, sp, #0x14
	add r1, #0x30
	add r2, sp, #0x38
	add r3, sp, #0x5c
	bl MOD81_022387A8
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #0x14
	mov r2, #0x80
	mov r3, #0x64
	bl MOD81_022387C8
	str r0, [r4, #0x28]
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #0x14
	mov r2, #0x80
	mov r3, #0x5a
	bl MOD81_022387C8
	str r0, [r4, #0x2c]
	mov r1, #1
	bl FUN_02020238
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r4, #0x2c]
	mov r1, #0
	bl FUN_020200A0
	add sp, #0x70
	pop {r4, pc}
	thumb_func_end MOD81_022393F4

	thumb_func_start MOD81_02239498
MOD81_02239498: ; 0x02239498
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_022394A0:
	ldr r0, [r5, #0x28]
	cmp r0, #0
	beq _022394AA
	bl FUN_0201FFC8
_022394AA:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blt _022394A0
	add r6, #0x30
	add r0, r6, #0
	bl MOD81_02238784
	pop {r4, r5, r6, pc}
	thumb_func_end MOD81_02239498

	thumb_func_start MOD81_022394BC
MOD81_022394BC: ; 0x022394BC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x3a
	mov r1, #0x14
	str r2, [sp]
	add r7, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	beq _02239502
	str r5, [r4]
	lsl r0, r6, #0xc
	str r0, [r4, #4]
	ldr r0, [sp]
	lsl r1, r0, #0xc
	str r1, [r4, #8]
	ldr r0, [r4, #4]
	sub r0, r1, r0
	add r1, r7, #0
	bl _s32_div_f
	str r0, [r4, #0xc]
	ldr r0, _02239504 ; =MOD81_0223953C
	str r7, [r4, #0x10]
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA60
	str r0, [r5, #0x64]
	ldr r0, _02239508 ; =0x04000050
	mov r1, #1
	add r2, r6, #0
	bl G2x_SetBlendBrightness_
_02239502:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02239504: .word MOD81_0223953C
_02239508: .word 0x04000050
	thumb_func_end MOD81_022394BC

	thumb_func_start MOD81_0223950C
MOD81_0223950C: ; 0x0223950C
	ldr r0, [r0, #0x64]
	cmp r0, #0
	bne _02239516
	mov r0, #1
	bx lr
_02239516:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD81_0223950C

	thumb_func_start MOD81_0223951C
MOD81_0223951C: ; 0x0223951C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x64]
	cmp r0, #0
	beq _02239538
	bl FUN_0201B6C8
	bl MOD81_02238898
	ldr r0, [r4, #0x64]
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #0x64]
_02239538:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223951C

	thumb_func_start MOD81_0223953C
MOD81_0223953C: ; 0x0223953C
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x10]
	sub r0, r0, #1
	str r0, [r4, #0x10]
	cmp r0, #0
	ble _0223955E
	ldr r1, [r4, #4]
	ldr r0, [r4, #0xc]
	add r2, r1, r0
	str r2, [r4, #4]
	ldr r0, _02239574 ; =0x04000050
	mov r1, #1
	asr r2, r2, #0xc
	bl G2x_SetBlendBrightness_
	pop {r4, pc}
_0223955E:
	ldr r2, [r4, #8]
	ldr r0, _02239574 ; =0x04000050
	mov r1, #1
	asr r2, r2, #0xc
	bl G2x_SetBlendBrightness_
	ldr r0, [r4]
	bl MOD81_0223951C
	pop {r4, pc}
	nop
_02239574: .word 0x04000050
	thumb_func_end MOD81_0223953C

	thumb_func_start MOD81_02239578
MOD81_02239578: ; 0x02239578
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x3a
	mov r1, #0x30
	bl AllocFromHeap
	add r4, r0, #0
	beq _022395B8
	str r5, [r4]
	ldr r0, [r5, #0x60]
	add r1, r4, #0
	str r0, [r4, #4]
	add r1, #8
	bl MOD81_02238B08
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x14
	bl MOD81_02238B28
	ldr r0, _022395BC ; =0x00002F60
	mov r2, #0
	str r0, [r4, #0x1c]
	str r2, [r4, #0x20]
	strh r2, [r4, #0x2c]
	str r2, [r4, #0x24]
	ldr r0, _022395C0 ; =MOD81_02239608
	add r1, r4, #0
	str r2, [r4, #0x28]
	bl FUN_0200CA44
	str r0, [r5, #0x68]
_022395B8:
	pop {r3, r4, r5, pc}
	nop
_022395BC: .word 0x00002F60
_022395C0: .word MOD81_02239608
	thumb_func_end MOD81_02239578

	thumb_func_start MOD81_022395C4
MOD81_022395C4: ; 0x022395C4
	ldr r0, [r0, #0x68]
	cmp r0, #0
	bne _022395CE
	mov r0, #1
	bx lr
_022395CE:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD81_022395C4

	thumb_func_start MOD81_022395D4
MOD81_022395D4: ; 0x022395D4
	push {r3, lr}
	ldr r0, [r0, #0x68]
	cmp r0, #0
	beq _022395E4
	bl FUN_0201B6C8
	ldr r0, [r0, #0x20]
	pop {r3, pc}
_022395E4:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD81_022395D4

	thumb_func_start MOD81_022395E8
MOD81_022395E8: ; 0x022395E8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x68]
	cmp r0, #0
	beq _02239604
	bl FUN_0201B6C8
	bl FreeToHeap
	ldr r0, [r4, #0x68]
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #0x68]
_02239604:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_022395E8

	thumb_func_start MOD81_02239608
MOD81_02239608: ; 0x02239608
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x24]
	cmp r0, #0
	bne _0223967C
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x1c]
	add r0, r1, r0
	str r0, [r4, #0xc]
	ldr r1, [r4, #0x1c]
	cmp r1, #0
	blt _0223962A
	mov r0, #0x1e
	lsl r0, r0, #6
	sub r0, r1, r0
	str r0, [r4, #0x1c]
	b _0223967C
_0223962A:
	mov r0, #0x1e
	lsl r0, r0, #6
	sub r0, r1, r0
	str r0, [r4, #0x1c]
	ldr r1, [r4, #0xc]
	ldr r0, _022396E0 ; =0xFFFFC000
	cmp r1, r0
	bgt _0223967C
	str r0, [r4, #0xc]
	ldr r1, [r4, #0x1c]
	mov r0, #0x2c
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	neg r1, r0
	mov r0, #0xfa
	lsl r0, r0, #4
	str r1, [r4, #0x1c]
	cmp r1, r0
	bge _02239658
	mov r0, #1
	str r0, [r4, #0x24]
_02239658:
	ldr r0, _022396E4 ; =0x000005E6
	bl FUN_020054C8
	ldr r0, [r4, #0x20]
	add r0, r0, #1
	str r0, [r4, #0x20]
	cmp r0, #1
	beq _0223966E
	cmp r0, #3
	beq _02239674
	b _0223967C
_0223966E:
	mov r0, #0xb0
	strh r0, [r4, #0x2c]
	b _0223967C
_02239674:
	mov r0, #0x2c
	ldrsh r0, [r4, r0]
	add r0, #0x50
	strh r0, [r4, #0x2c]
_0223967C:
	mov r0, #0x14
	mov r2, #0x2c
	ldrsh r3, [r4, r0]
	ldrsh r0, [r4, r2]
	add r1, r4, #0
	add r1, #0x14
	add r0, r3, r0
	strh r0, [r4, #0x14]
	mov r0, #0x18
	ldrsh r3, [r4, r0]
	ldrsh r0, [r4, r2]
	sub r0, r3, r0
	strh r0, [r4, #0x18]
	ldr r0, [r4, #4]
	bl MOD81_02238B40
	mov r2, #0x2c
	ldrsh r3, [r4, r2]
	ldr r5, [r4, #8]
	add r1, r4, #0
	lsl r0, r3, #2
	add r0, r3, r0
	add r0, r5, r0
	str r0, [r4, #8]
	ldrsh r2, [r4, r2]
	ldr r3, [r4, #0x10]
	add r1, #8
	lsl r0, r2, #2
	add r0, r2, r0
	add r0, r3, r0
	str r0, [r4, #0x10]
	ldr r0, [r4, #4]
	bl MOD81_02238B18
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _022396DE
	mov r0, #0x2c
	ldrsh r0, [r4, r0]
	sub r0, #0xe
	strh r0, [r4, #0x2c]
	ldr r0, [r4, #0x28]
	add r0, r0, #1
	str r0, [r4, #0x28]
	cmp r0, #0x1e
	ble _022396DE
	ldr r0, [r4]
	bl MOD81_022395E8
_022396DE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022396E0: .word 0xFFFFC000
_022396E4: .word 0x000005E6
	thumb_func_end MOD81_02239608

	thumb_func_start MOD81_022396E8
MOD81_022396E8: ; 0x022396E8
	push {r3, r4, r5, lr}
	mov r1, #0x5b
	add r5, r0, #0
	mov r0, #0x3a
	lsl r1, r1, #2
	bl AllocFromHeap
	add r4, r0, #0
	beq _0223974A
	str r5, [r4]
	mov r0, #0
	str r0, [r4, #4]
	add r0, r5, #0
	bl MOD81_0223880C
	add r1, r4, #0
	add r1, #0xc0
	str r0, [r1]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xd4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xcc
	str r1, [r0]
	mov r0, #0x16
	lsl r0, r0, #4
	str r1, [r4, r0]
	add r0, r0, #4
	str r1, [r4, r0]
	bl MTRandom
	add r1, r4, #0
	add r1, #0xbc
	str r0, [r1]
	add r0, r4, #0
	mov r2, #0
	add r0, #0xd0
	str r2, [r0]
	mov r0, #0x5a
	lsl r0, r0, #2
	str r2, [r4, r0]
	ldr r0, _02239750 ; =MOD81_02239F58
	add r1, r4, #0
	bl FUN_0200CA98
_0223974A:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_02239750: .word MOD81_02239F58
	thumb_func_end MOD81_022396E8

	thumb_func_start MOD81_02239754
MOD81_02239754: ; 0x02239754
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OS_DisableInterrupts
	add r4, r0, #0
	cmp r5, #0
	beq _022397A0
	add r0, r5, #0
	bl MOD81_02239C94
	add r0, r5, #0
	bl MOD81_02239DF0
	add r0, r5, #0
	bl MOD81_02239F1C
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02239782
	bl FUN_0200CAB4
_02239782:
	mov r0, #0x59
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02239790
	bl MOD81_0223A1FC
_02239790:
	add r0, r5, #0
	add r0, #0xbc
	ldr r0, [r0]
	bl SetMTRNGSeed
	add r0, r5, #0
	bl FreeToHeap
_022397A0:
	add r0, r4, #0
	bl OS_RestoreInterrupts
	pop {r3, r4, r5, pc}
	thumb_func_end MOD81_02239754

	thumb_func_start MOD81_022397A8
MOD81_022397A8: ; 0x022397A8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r2, [r4]
	add r5, r0, #0
	cmp r2, #4
	bhs _022397D6
	lsl r3, r2, #2
	ldr r2, _022397DC ; =0x0223D094
	add r1, r5, #4
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #0
	beq _022397CC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	str r0, [r5, #4]
_022397CC:
	add r0, r5, #0
	bl MOD81_022397E0
	mov r0, #0
	pop {r3, r4, r5, pc}
_022397D6:
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_022397DC: .word MOD81_0223D094
	thumb_func_end MOD81_022397A8

	thumb_func_start MOD81_022397E0
MOD81_022397E0: ; 0x022397E0
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xd4
	ldr r0, [r0]
	cmp r0, #0
	beq _02239800
	bl G3X_ResetMtxStack
	add r4, #0xd4
	ldr r0, [r4]
	bl MOD81_02238940
	mov r0, #0
	add r1, r0, #0
	bl FUN_020222B4
_02239800:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_022397E0

	thumb_func_start MOD81_02239804
MOD81_02239804: ; 0x02239804
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD81_022399FC
	add r0, r4, #0
	bl MOD81_02239CDC
	add r0, r4, #0
	bl MOD81_02239E00
	mov r0, #8
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD81_02239804

	thumb_func_start MOD81_02239838
MOD81_02239838: ; 0x02239838
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4]
	cmp r1, #0
	beq _02239848
	cmp r1, #1
	beq _0223985E
	b _02239876
_02239848:
	bl FUN_0200E308
	cmp r0, #0
	beq _02239876
	ldr r0, _0223987C ; =0x0223D444
	mov r1, #0
	str r1, [r0]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02239876
_0223985E:
	ldr r1, _0223987C ; =0x0223D444
	ldr r2, [r1]
	cmp r2, #0x1e
	bge _0223986A
	add r2, r2, #1
	str r2, [r1]
_0223986A:
	add r0, #0xd0
	ldr r0, [r0]
	cmp r0, #0
	beq _02239876
	mov r0, #1
	pop {r4, pc}
_02239876:
	mov r0, #0
	pop {r4, pc}
	nop
_0223987C: .word MOD81_0223D444
	thumb_func_end MOD81_02239838

	thumb_func_start MOD81_02239880
MOD81_02239880: ; 0x02239880
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #4
	bhi _02239926
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02239898: ; jump table
	.short _022398A2 - _02239898 - 2 ; case 0
	.short _022398AE - _02239898 - 2 ; case 1
	.short _022398F2 - _02239898 - 2 ; case 2
	.short _02239908 - _02239898 - 2 ; case 3
	.short _0223991E - _02239898 - 2 ; case 4
_022398A2:
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _02239926
_022398AE:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #8
	ble _02239926
	add r0, r4, #0
	add r0, #0xd8
	ldr r0, [r0]
	mov r1, #0
	mov r2, #0x1f
	mov r3, #0x18
	bl MOD81_0223A228
	add r0, r4, #0
	bl MOD81_0223A2AC
	mov r1, #0x16
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r4, #0
	add r0, #0xd8
	ldr r0, [r0]
	mov r1, #0
	bl MOD81_02238B5C
	add r4, #0xd8
	ldr r0, [r4]
	mov r1, #1
	bl MOD81_02238B58
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _02239926
_022398F2:
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD81_0223A658
	cmp r0, #0
	beq _02239926
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _02239926
_02239908:
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD81_0223A64C
	cmp r0, #0
	beq _02239926
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _02239926
_0223991E:
	bl MOD81_02239F4C
	mov r0, #1
	pop {r3, r4, r5, pc}
_02239926:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD81_02239880

	thumb_func_start MOD81_0223992C
MOD81_0223992C: ; 0x0223992C
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #4
	bhi _022399F2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02239946: ; jump table
	.short _02239950 - _02239946 - 2 ; case 0
	.short _02239966 - _02239946 - 2 ; case 1
	.short _02239984 - _02239946 - 2 ; case 2
	.short _022399A0 - _02239946 - 2 ; case 3
	.short _022399E4 - _02239946 - 2 ; case 4
_02239950:
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD81_0223A664
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _022399F2
_02239966:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #2
	ble _022399F2
	mov r0, #0
	str r0, [r4, #8]
	add r4, #0xc4
	ldr r0, [r4]
	bl MOD81_022381EC
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _022399F2
_02239984:
	add r1, r4, #0
	add r1, #0xc8
	ldr r1, [r1]
	cmp r1, #0
	bne _022399F2
	mov r1, #0x59
	lsl r1, r1, #2
	add r1, r4, r1
	bl MOD81_0223A104
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _022399F2
_022399A0:
	ldr r0, [r4, #8]
	cmp r0, #0x28
	bge _022399B6
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0x28
	bne _022399B6
	mov r0, #0x6b
	lsl r0, r0, #4
	bl FUN_020054C8
_022399B6:
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD81_0223A64C
	cmp r0, #0
	beq _022399F2
	mov r0, #4
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0
	ldr r3, _022399F8 ; =0x00007FFF
	add r1, r0, #0
	add r2, r0, #0
	bl FUN_0200E1D0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _022399F2
_022399E4:
	bl FUN_0200E308
	cmp r0, #0
	beq _022399F2
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_022399F2:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_022399F8: .word 0x00007FFF
	thumb_func_end MOD81_0223992C

	thumb_func_start MOD81_022399FC
MOD81_022399FC: ; 0x022399FC
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, _02239C78 ; =0x0223D0EC
	bl GX_SetBanks
	ldr r2, _02239C7C ; =0x04000304
	ldr r0, _02239C80 ; =0xFFFF7FFF
	ldrh r1, [r2]
	and r0, r1
	strh r0, [r2]
	ldr r0, _02239C84 ; =0x0223D084
	bl FUN_02016BBC
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r2, _02239C88 ; =0x0223D0B4
	mov r1, #2
	mov r3, #1
	bl FUN_02016C18
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r2, _02239C88 ; =0x0223D0B4
	mov r1, #6
	mov r3, #1
	bl FUN_02016C18
	bl OS_DisableInterrupts
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r2, _02239C8C ; =0x0223D0D0
	mov r1, #3
	mov r3, #2
	bl FUN_02016C18
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r2, _02239C8C ; =0x0223D0D0
	mov r1, #7
	mov r3, #2
	bl FUN_02016C18
	add r0, r5, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	add r2, r4, #0
	str r0, [sp, #0xc]
	add r2, #0xc0
	mov r1, #2
	ldr r2, [r2]
	mov r0, #0x5d
	add r3, r1, #0
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	add r2, r4, #0
	str r0, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	mov r0, #0x5d
	mov r1, #2
	mov r3, #6
	bl GfGfxLoader_LoadCharData
	mov r1, #0
	str r1, [sp]
	add r2, r4, #0
	str r1, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	mov r0, #0x5d
	mov r3, #2
	bl GfGfxLoader_LoadScrnData
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	add r2, r4, #0
	str r0, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	mov r0, #0x5d
	mov r3, #6
	bl GfGfxLoader_LoadScrnData
	ldr r0, [r4]
	bl MOD81_02238828
	add r5, r0, #0
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x3a
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x5d
	mov r1, #3
	add r3, r2, #0
	bl GfGfxLoader_GXLoadPal
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x3a
	str r0, [sp, #4]
	mov r0, #0x5d
	mov r1, #3
	mov r2, #4
	mov r3, #0
	bl GfGfxLoader_GXLoadPal
	ldr r0, _02239C90 ; =0x0223D07C
	lsl r1, r5, #1
	ldrh r5, [r0, r1]
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x40
	str r0, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0x5d
	mov r1, #3
	mov r2, #0
	add r3, r5, #0
	bl GfGfxLoader_GXLoadPalWithSrcOffset
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x40
	str r0, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0x5d
	mov r1, #3
	mov r2, #4
	add r3, r5, #0
	bl GfGfxLoader_GXLoadPalWithSrcOffset
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	add r2, r4, #0
	str r0, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	mov r0, #0x5d
	mov r1, #5
	mov r3, #3
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	add r2, r4, #0
	str r0, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	mov r0, #0x5d
	mov r1, #5
	mov r3, #7
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	add r2, r4, #0
	str r0, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	mov r0, #0x5d
	mov r1, #4
	mov r3, #3
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	add r2, r4, #0
	str r0, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	mov r0, #0x5d
	mov r1, #4
	mov r3, #7
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x3a
	mov r1, #0x60
	bl AllocFromHeap
	add r5, r0, #0
	beq _02239C02
	mov r0, #0
	add r1, r5, #0
	mov r2, #0x60
	bl MIi_CpuClear32
	add r0, r5, #0
	mov r1, #0x60
	bl DC_FlushRange
	bl GX_BeginLoadBGExtPltt
	bl GXS_BeginLoadBGExtPltt
	mov r1, #6
	add r0, r5, #0
	lsl r1, r1, #0xc
	mov r2, #0x60
	bl GX_LoadBGExtPltt
	mov r1, #6
	add r0, r5, #0
	lsl r1, r1, #0xc
	mov r2, #0x60
	bl GXS_LoadBGExtPltt
	bl GX_EndLoadBGExtPltt
	bl GXS_EndLoadBGExtPltt
	add r0, r5, #0
	bl FreeToHeap
_02239C02:
	add r0, r4, #0
	add r0, #0xc0
	mov r3, #0xff
	ldr r0, [r0]
	mov r1, #6
	mov r2, #3
	mvn r3, r3
	bl FUN_020179E0
	mov r0, #7
	mov r1, #0
	bl FUN_0201797C
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	add r0, r4, #0
	add r0, #0xc0
	mov r1, #3
	ldr r0, [r0]
	add r2, r1, #0
	mov r3, #0
	bl FUN_020179E0
	add r0, r4, #0
	add r0, #0xc8
	mov r1, #1
	bl MOD81_02238118
	add r1, r4, #0
	add r1, #0xc4
	str r0, [r1]
	mov r0, #0x4a
	lsl r0, r0, #2
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0xd0
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0xc0
	mov r1, #0x12
	mov r2, #1
	ldr r0, [r0]
	lsl r1, r1, #6
	lsl r2, r2, #0xc
	mov r3, #1
	bl MOD81_022384AC
	add r4, #0xcc
	str r0, [r4]
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_02239C78: .word MOD81_0223D0EC
_02239C7C: .word 0x04000304
_02239C80: .word 0xFFFF7FFF
_02239C84: .word MOD81_0223D084
_02239C88: .word MOD81_0223D0B4
_02239C8C: .word MOD81_0223D0D0
_02239C90: .word MOD81_0223D07C
	thumb_func_end MOD81_022399FC

	thumb_func_start MOD81_02239C94
MOD81_02239C94: ; 0x02239C94
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xc8
	ldr r0, [r0]
	cmp r0, #0
	beq _02239CAA
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	bl MOD81_02238200
_02239CAA:
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	mov r1, #3
	bl FUN_020178A0
	add r4, #0xc0
	ldr r0, [r4]
	mov r1, #7
	bl FUN_020178A0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_02239C94

	thumb_func_start MOD81_02239CDC
MOD81_02239CDC: ; 0x02239CDC
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	bl NNS_G3dInit
	bl G3X_InitMtxStack
	ldr r0, _02239DBC ; =0x04000060
	ldr r1, _02239DC0 ; =0xFFFFCFFD
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
	ldr r2, _02239DC4 ; =0x0000CFFB
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
	ldr r0, _02239DC8 ; =0x0223D0A4
	bl G3X_SetEdgeColorTable
	mov r1, #0
	ldr r0, _02239DCC ; =0x000043FF
	ldr r2, _02239DD0 ; =0x00007FFF
	mov r3, #0x3f
	str r1, [sp]
	bl G3X_SetClearColor
	ldr r1, _02239DD4 ; =0x04000540
	mov r0, #2
	str r0, [r1]
	ldr r0, _02239DD8 ; =0xBFFF0000
	str r0, [r1, #0x40]
	mov r0, #1
	add r1, r0, #0
	bl NNS_GfdInitFrmTexVramManager
	mov r0, #1
	lsl r0, r0, #0xe
	mov r1, #1
	bl NNS_GfdInitFrmPlttVramManager
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r1, _02239DDC ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	strh r2, [r1]
	mov r1, #0
	mov r0, #1
	add r2, r1, #0
	add r3, r1, #0
	bl MOD81_022388C0
	add r1, r4, #0
	add r1, #0xd4
	str r0, [r1]
	mov r1, #0
	ldr r0, _02239DE0 ; =0xFFFC8800
	str r1, [sp]
	str r0, [sp, #4]
	str r1, [sp, #8]
	add r0, r4, #0
	str r1, [sp, #0xc]
	add r0, #0xd4
	ldr r0, [r0]
	mov r2, #0x5d
	mov r3, #0x1b
	bl MOD81_02238A84
	add r1, r4, #0
	add r1, #0xd8
	str r0, [r1]
	ldr r1, _02239DE4 ; =0x0000EBE0
	ldr r0, _02239DE8 ; =0x0223D444
	strh r1, [r0, #4]
	mov r1, #0
	strh r1, [r0, #6]
	strh r1, [r0, #8]
	add r0, r4, #0
	add r0, #0xd4
	ldr r0, [r0]
	ldr r1, _02239DEC ; =0x0223D448
	bl MOD81_02238C60
	add r4, #0xd8
	mov r1, #7
	ldr r0, [r4]
	lsl r1, r1, #0xa
	bl MOD81_02238B84
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_02239DBC: .word 0x04000060
_02239DC0: .word 0xFFFFCFFD
_02239DC4: .word 0x0000CFFB
_02239DC8: .word MOD81_0223D0A4
_02239DCC: .word 0x000043FF
_02239DD0: .word 0x00007FFF
_02239DD4: .word 0x04000540
_02239DD8: .word 0xBFFF0000
_02239DDC: .word 0x04000008
_02239DE0: .word 0xFFFC8800
_02239DE4: .word 0x0000EBE0
_02239DE8: .word MOD81_0223D444
_02239DEC: .word MOD81_0223D448
	thumb_func_end MOD81_02239CDC

	thumb_func_start MOD81_02239DF0
MOD81_02239DF0: ; 0x02239DF0
	push {r3, lr}
	add r0, #0xd4
	ldr r0, [r0]
	cmp r0, #0
	beq _02239DFE
	bl MOD81_0223890C
_02239DFE:
	pop {r3, pc}
	thumb_func_end MOD81_02239DF0

	thumb_func_start MOD81_02239E00
MOD81_02239E00: ; 0x02239E00
	push {r4, r5, r6, r7, lr}
	sub sp, #0x74
	add r7, r0, #0
	add r0, #0xc
	mov r1, #0x5d
	mov r2, #0xb
	mov r3, #0xc
	bl MOD81_0223874C
	add r0, sp, #0x60
	bl NNS_G2dInitImagePaletteProxy
	add r0, sp, #0x3c
	bl NNS_G2dInitImageProxy
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	add r0, sp, #0x3c
	str r0, [sp, #0x10]
	mov r0, #0x5d
	mov r1, #0xd
	bl GfGfxLoader_LoadImageMapping
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	add r0, sp, #0x3c
	str r0, [sp, #0x10]
	mov r0, #0x5d
	mov r1, #0xd
	mov r2, #1
	bl GfGfxLoader_LoadImageMapping
	mov r0, #0x3a
	str r0, [sp]
	add r0, sp, #0x60
	str r0, [sp, #4]
	mov r0, #0x5d
	mov r1, #0xe
	mov r2, #1
	mov r3, #0
	bl GfGfxLoader_PartiallyLoadPalette
	mov r0, #0x3a
	str r0, [sp]
	add r0, sp, #0x60
	str r0, [sp, #4]
	mov r0, #0x5d
	mov r1, #0xe
	mov r2, #2
	mov r3, #0
	bl GfGfxLoader_PartiallyLoadPalette
	mov r0, #1
	add r1, r7, #0
	str r0, [sp]
	add r0, sp, #0x18
	add r1, #0xc
	add r2, sp, #0x3c
	add r3, sp, #0x60
	bl MOD81_022387A8
	ldr r0, _02239F18 ; =0x035947D1
	bl SetMTRNGSeed
	mov r0, #0
	str r0, [sp, #0x14]
	add r4, r7, #0
_02239E9A:
	bl MTRandom
	mov r1, #0xe8
	bl _u32_div_f
	add r6, r1, #0
	add r6, #0xc
	bl MTRandom
	mov r1, #0x71
	lsl r1, r1, #2
	bl _u32_div_f
	add r5, r1, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	sub r5, #0x1c
	str r0, [sp, #4]
	ldr r0, [r7]
	add r1, sp, #0x18
	add r2, r6, #0
	add r3, r5, #0
	bl MOD81_022387C8
	str r0, [r4, #0x1c]
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r5, #0x38
	ldr r0, [r7]
	add r1, sp, #0x18
	add r2, r6, #0
	add r3, r5, #0
	bl MOD81_022387C8
	str r0, [r4, #0x20]
	ldr r0, [r4, #0x1c]
	mov r1, #0
	bl FUN_02020130
	ldr r0, [r4, #0x20]
	mov r1, #1
	bl FUN_02020130
	ldr r0, [r4, #0x1c]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r4, #0x20]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [sp, #0x14]
	add r4, #8
	add r0, r0, #1
	str r0, [sp, #0x14]
	cmp r0, #0x14
	blt _02239E9A
	add sp, #0x74
	pop {r4, r5, r6, r7, pc}
	nop
_02239F18: .word 0x035947D1
	thumb_func_end MOD81_02239E00

	thumb_func_start MOD81_02239F1C
MOD81_02239F1C: ; 0x02239F1C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_02239F24:
	ldr r0, [r5, #0x1c]
	cmp r0, #0
	beq _02239F2E
	bl FUN_0201FFC8
_02239F2E:
	ldr r0, [r5, #0x20]
	cmp r0, #0
	beq _02239F38
	bl FUN_0201FFC8
_02239F38:
	add r4, r4, #1
	add r5, #8
	cmp r4, #0x14
	blt _02239F24
	add r6, #0xc
	add r0, r6, #0
	bl MOD81_02238784
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD81_02239F1C

	thumb_func_start MOD81_02239F4C
MOD81_02239F4C: ; 0x02239F4C
	mov r1, #0x5a
	mov r2, #1
	lsl r1, r1, #2
	str r2, [r0, r1]
	bx lr
	.align 2, 0
	thumb_func_end MOD81_02239F4C

	thumb_func_start MOD81_02239F58
MOD81_02239F58: ; 0x02239F58
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x5a
	add r4, r1, #0
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _02239FAC
	mov r1, #0
	str r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xc0
	mov r3, #0xff
	ldr r0, [r0]
	mov r1, #2
	mov r2, #3
	mvn r3, r3
	bl FUN_020179E0
	add r4, #0xc0
	ldr r0, [r4]
	mov r1, #6
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	mov r0, #3
	mov r1, #0
	bl FUN_0201797C
	mov r0, #7
	mov r1, #1
	bl FUN_0201797C
	ldr r2, _02239FB0 ; =0x04000304
	ldrh r1, [r2]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2]
	add r0, r5, #0
	bl FUN_0200CAB4
_02239FAC:
	pop {r3, r4, r5, pc}
	nop
_02239FB0: .word 0x04000304
	thumb_func_end MOD81_02239F58

	thumb_func_start MOD81_02239FB4
MOD81_02239FB4: ; 0x02239FB4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	str r5, [r2, #4]
	add r0, r2, #0
	str r1, [r0]
	mov r1, #0x52
	mov r7, #0
	lsl r1, r1, #2
	str r7, [r0, r1]
	add r1, r1, #4
	str r2, [sp]
	str r7, [r0, r1]
	add r4, r2, #0
	add r6, r2, #0
_02239FD0:
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r5, #0x1c]
	bl FUN_0202011C
	add r2, r6, #0
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, #0x58
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r7, r7, #1
	str r0, [r2]
	add r4, r4, #4
	add r5, #8
	add r6, #0xc
	cmp r7, #0x14
	blt _02239FD0
	ldr r0, _0223A018 ; =MOD81_0223A01C
	ldr r1, [sp]
	mov r2, #0
	bl FUN_0200CA44
	ldr r1, [sp]
	ldr r1, [r1]
	str r0, [r1]
	ldr r0, [sp]
	ldr r0, [r0]
	ldr r0, [r0]
	cmp r0, #0
	bne _0223A014
	ldr r0, [sp]
	bl FreeToHeap
_0223A014:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223A018: .word MOD81_0223A01C
	thumb_func_end MOD81_02239FB4

	thumb_func_start MOD81_0223A01C
MOD81_0223A01C: ; 0x0223A01C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r1, #0
	mov r1, #0x52
	lsl r1, r1, #2
	ldr r0, [r6, r1]
	add r0, r0, #1
	str r0, [r6, r1]
	ldr r0, [r6, r1]
	cmp r0, #0xc
	ble _0223A050
	mov r0, #0
	str r0, [r6, r1]
	add r0, r1, #4
	ldr r0, [r6, r0]
	cmp r0, #0x14
	bge _0223A050
	lsl r0, r0, #2
	mov r2, #1
	add r0, r6, r0
	str r2, [r0, #8]
	add r0, r1, #4
	ldr r0, [r6, r0]
	add r2, r0, #1
	add r0, r1, #4
	str r2, [r6, r0]
_0223A050:
	mov r0, #0
	add r7, r6, #0
	str r0, [sp, #4]
	add r5, r6, #0
	str r6, [sp]
	add r4, r0, #0
	add r7, #0x58
_0223A05E:
	mov r1, #0x21
	ldr r2, [r5, #0x5c]
	lsl r1, r1, #0xc
	add r2, r2, r1
	mov r1, #0x6a
	add r0, r5, #0
	lsl r1, r1, #0xe
	add r0, #0x5c
	str r2, [r5, #0x5c]
	cmp r2, r1
	blt _0223A09E
	mov r1, #0x71
	ldr r2, [r0]
	lsl r1, r1, #0xe
	sub r1, r2, r1
	str r1, [r0]
	ldr r0, [sp]
	ldr r0, [r0, #8]
	cmp r0, #0
	beq _0223A09E
	ldr r0, [r6, #4]
	mov r1, #1
	add r0, r0, r4
	ldr r0, [r0, #0x1c]
	bl FUN_020200A0
	ldr r0, [r6, #4]
	mov r1, #1
	add r0, r0, r4
	ldr r0, [r0, #0x20]
	bl FUN_020200A0
_0223A09E:
	ldr r0, [r6, #4]
	add r1, r7, #0
	add r0, r0, r4
	ldr r0, [r0, #0x1c]
	bl FUN_02020044
	add r2, r5, #0
	add r2, #0x58
	add r3, sp, #8
	ldmia r2!, {r0, r1}
	mov ip, r3
	stmia r3!, {r0, r1}
	ldr r0, [r2]
	str r0, [r3]
	mov r0, #0xe
	ldr r1, [sp, #0xc]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r0, [r6, #4]
	mov r1, ip
	add r0, r0, r4
	ldr r0, [r0, #0x20]
	bl FUN_02020044
	ldr r0, [sp]
	add r5, #0xc
	add r0, r0, #4
	str r0, [sp]
	ldr r0, [sp, #4]
	add r4, #8
	add r0, r0, #1
	add r7, #0xc
	str r0, [sp, #4]
	cmp r0, #0x14
	blt _0223A05E
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD81_0223A01C

	thumb_func_start MOD81_0223A0EC
MOD81_0223A0EC: ; 0x0223A0EC
	push {r4, lr}
	add r4, r0, #0
	beq _0223A102
	bl FUN_0201B6C8
	ldr r0, [r0]
	mov r1, #0
	str r1, [r0]
	add r0, r4, #0
	bl FUN_0200CAB4
_0223A102:
	pop {r4, pc}
	thumb_func_end MOD81_0223A0EC

	thumb_func_start MOD81_0223A104
MOD81_0223A104: ; 0x0223A104
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r1, #0x17
	add r6, r0, #0
	mov r0, #0x3a
	lsl r1, r1, #4
	bl AllocFromHeap
	add r4, r0, #0
	beq _0223A170
	str r6, [r4]
	add r6, #0xc0
	mov r0, #0x55
	ldr r1, [r6]
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_02017B54
	lsl r1, r0, #0xc
	mov r0, #0x56
	lsl r0, r0, #2
	str r1, [r4, r0]
	sub r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #6
	bl FUN_02017B54
	mov r1, #0x57
	lsl r0, r0, #0xc
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r2, #0
	add r0, r1, #4
	str r2, [r4, r0]
	add r0, r1, #0
	add r0, #8
	str r2, [r4, r0]
	add r0, r1, #0
	add r0, #0xc
	str r5, [r4, r0]
	add r1, #0x10
	str r2, [r4, r1]
	ldr r0, _0223A174 ; =MOD81_0223A178
	add r1, r4, #0
	bl FUN_0200CA60
	str r0, [r5]
	cmp r0, #0
	bne _0223A170
	add r0, r4, #0
	bl FreeToHeap
_0223A170:
	pop {r4, r5, r6, pc}
	nop
_0223A174: .word MOD81_0223A178
	thumb_func_end MOD81_0223A104

	thumb_func_start MOD81_0223A178
MOD81_0223A178: ; 0x0223A178
	push {r4, r5, r6, lr}
	mov r3, #0x59
	add r4, r1, #0
	lsl r3, r3, #2
	mov r0, #2
	ldr r1, [r4, r3]
	lsl r0, r0, #0x14
	cmp r1, r0
	bge _0223A1FA
	sub r0, r3, #4
	ldr r1, [r4, r0]
	add r0, r3, #0
	sub r0, #0x44
	add r1, r1, r0
	sub r0, r3, #4
	str r1, [r4, r0]
	add r5, r3, #0
	ldr r1, [r4, r3]
	ldr r0, [r4, r0]
	sub r5, #0xc
	add r0, r1, r0
	str r0, [r4, r3]
	add r0, r3, #0
	sub r0, #0x10
	ldr r5, [r4, r5]
	ldr r3, [r4, r3]
	ldr r0, [r4, r0]
	sub r3, r5, r3
	mov r1, #2
	mov r2, #3
	asr r3, r3, #0xc
	bl FUN_020179E0
	mov r5, #0x55
	lsl r5, r5, #2
	add r3, r5, #0
	ldr r0, [r4, r5]
	add r3, #8
	add r5, #0x10
	ldr r6, [r4, r3]
	ldr r3, [r4, r5]
	mov r1, #6
	sub r3, r6, r3
	mov r2, #3
	asr r3, r3, #0xc
	bl FUN_020179E0
	mov r1, #0x59
	lsl r1, r1, #2
	mov r0, #2
	ldr r2, [r4, r1]
	lsl r0, r0, #0x12
	cmp r2, r0
	blt _0223A1FA
	add r0, r1, #0
	add r0, #8
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0223A1FA
	add r1, #8
	ldr r0, [r4]
	add r1, r4, r1
	add r2, r4, #4
	bl MOD81_02239FB4
_0223A1FA:
	pop {r4, r5, r6, pc}
	thumb_func_end MOD81_0223A178

	thumb_func_start MOD81_0223A1FC
MOD81_0223A1FC: ; 0x0223A1FC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	beq _0223A226
	bl FUN_0201B6C8
	add r4, r0, #0
	mov r0, #0x5a
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	mov r2, #0
	str r2, [r1]
	add r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD81_0223A0EC
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_0223A226:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD81_0223A1FC

	thumb_func_start MOD81_0223A228
MOD81_0223A228: ; 0x0223A228
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	add r5, r1, #0
	mov r0, #0x3a
	mov r1, #0x14
	add r7, r2, #0
	add r6, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	beq _0223A268
	lsl r0, r5, #0xc
	str r0, [r4]
	lsl r1, r7, #0xc
	str r1, [r4, #8]
	ldr r0, [r4]
	sub r0, r1, r0
	add r1, r6, #0
	bl _s32_div_f
	str r0, [r4, #4]
	ldr r0, [sp]
	str r6, [r4, #0xc]
	add r1, r5, #0
	str r0, [r4, #0x10]
	bl MOD81_02238B5C
	ldr r0, _0223A26C ; =MOD81_0223A270
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
_0223A268:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223A26C: .word MOD81_0223A270
	thumb_func_end MOD81_0223A228

	thumb_func_start MOD81_0223A270
MOD81_0223A270: ; 0x0223A270
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	sub r0, r0, #1
	str r0, [r4, #0xc]
	cmp r0, #0
	ble _0223A292
	ldr r1, [r4]
	ldr r0, [r4, #4]
	add r1, r1, r0
	str r1, [r4]
	ldr r0, [r4, #0x10]
	asr r1, r1, #0xc
	bl MOD81_02238B5C
	pop {r3, r4, r5, pc}
_0223A292:
	ldr r1, [r4, #8]
	ldr r0, [r4, #0x10]
	asr r1, r1, #0xc
	bl MOD81_02238B5C
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD81_0223A270

	thumb_func_start MOD81_0223A2AC
MOD81_0223A2AC: ; 0x0223A2AC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r5, #0
	add r4, #0xdc
	add r0, #0xd8
	add r1, r4, #0
	ldr r0, [r0]
	add r1, #8
	bl MOD81_02238B08
	add r0, r5, #0
	add r0, #0xd8
	add r1, r4, #0
	ldr r0, [r0]
	add r1, #0x20
	bl MOD81_02238B28
	add r3, r4, #0
	add r3, #8
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	add r2, #0x14
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, r5, #0
	add r0, #0xd4
	ldr r0, [r0]
	str r0, [r4, #4]
	add r0, r5, #0
	add r0, #0xd8
	ldr r0, [r0]
	add r5, #0xdc
	str r0, [r5]
	ldr r0, [r4, #0xc]
	str r0, [r4, #0x28]
	ldr r1, [r4, #0xc]
	ldr r0, _0223A37C ; =0xFFFF8000
	sub r0, r0, r1
	mov r1, #0x1e
	bl _s32_div_f
	str r0, [r4, #0x2c]
	add r0, r4, #0
	mov r2, #1
	mov r1, #0x1e
	add r0, #0x80
	str r1, [r0]
	mov r1, #0
	str r1, [r4, #0x38]
	str r1, [r4, #0x3c]
	str r1, [r4, #0x40]
	add r0, r4, #0
	str r1, [r4, #0x44]
	add r0, #0x54
	strh r1, [r0]
	add r0, r4, #0
	lsl r2, r2, #0xe
	add r0, #0x56
	strh r2, [r0]
	add r0, r4, #0
	add r0, #0x5a
	strh r1, [r0]
	str r1, [r4, #0x7c]
	add r2, r4, #0
	add r0, r1, #0
_0223A330:
	add r3, r2, #0
	add r3, #0x5c
	strh r0, [r3]
	add r3, r2, #0
	add r3, #0x5e
	strh r0, [r3]
	add r3, r2, #0
	add r3, #0x60
	strh r0, [r3]
	add r3, r2, #0
	add r3, #0x62
	add r1, r1, #1
	add r2, #8
	strh r0, [r3]
	cmp r1, #3
	blt _0223A330
	mov r1, #0xd
	str r0, [r4, #0x78]
	add r0, r4, #0
	lsl r1, r1, #8
	mov r2, #0x1e
	bl MOD81_0223A384
	mov r1, #0x29
	mov r2, #5
	add r0, r4, #0
	lsl r1, r1, #0xc
	lsl r2, r2, #0xe
	mov r3, #0x1e
	bl MOD81_0223A3C0
	ldr r0, _0223A380 ; =MOD81_0223A57C
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, pc}
	nop
_0223A37C: .word 0xFFFF8000
_0223A380: .word MOD81_0223A57C
	thumb_func_end MOD81_0223A2AC

	thumb_func_start MOD81_0223A384
MOD81_0223A384: ; 0x0223A384
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	beq _0223A3B2
	mov r0, #0x56
	ldrsh r0, [r5, r0]
	add r1, r6, #0
	sub r0, r4, r0
	bl _s32_div_f
	add r1, r5, #0
	add r1, #0x5a
	strh r0, [r1]
	mov r0, #0x56
	ldrsh r1, [r5, r0]
	mov r0, #0x5a
	ldrsh r0, [r5, r0]
	add r1, r1, r0
	add r0, r5, #0
	add r0, #0x56
	strh r1, [r0]
	b _0223A3B6
_0223A3B2:
	add r0, #0x56
	strh r4, [r0]
_0223A3B6:
	add r0, r5, #0
	add r0, #0x58
	strh r4, [r0]
	str r6, [r5, #0x74]
	pop {r4, r5, r6, pc}
	thumb_func_end MOD81_0223A384

	thumb_func_start MOD81_0223A3C0
MOD81_0223A3C0: ; 0x0223A3C0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	beq _0223A3F8
	ldr r0, [r5, #0x38]
	add r1, r7, #0
	sub r0, r4, r0
	bl _s32_div_f
	str r0, [r5, #0x40]
	ldr r0, [r5, #0x3c]
	add r1, r7, #0
	sub r0, r6, r0
	bl _s32_div_f
	str r0, [r5, #0x44]
	ldr r1, [r5, #0x38]
	ldr r0, [r5, #0x40]
	add r0, r1, r0
	str r0, [r5, #0x38]
	ldr r1, [r5, #0x3c]
	ldr r0, [r5, #0x44]
	add r0, r1, r0
	str r0, [r5, #0x3c]
	str r4, [r5, #0x48]
	str r6, [r5, #0x4c]
_0223A3F8:
	str r7, [r5, #0x50]
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD81_0223A3C0

	thumb_func_start MOD81_0223A3FC
MOD81_0223A3FC: ; 0x0223A3FC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	beq _0223A422
	lsl r0, r4, #3
	str r0, [sp]
	add r1, r5, r0
	mov r0, #0x5c
	ldrsh r0, [r1, r0]
	add r1, r7, #0
	sub r0, r6, r0
	bl _s32_div_f
	ldr r1, [sp]
	add r1, r5, r1
	add r1, #0x5e
	strh r0, [r1]
_0223A422:
	lsl r1, r4, #3
	add r0, r5, r1
	add r0, #0x60
	strh r6, [r0]
	add r0, r5, r1
	add r0, #0x62
	strh r7, [r0]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD81_0223A3FC

	thumb_func_start MOD81_0223A434
MOD81_0223A434: ; 0x0223A434
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x74]
	cmp r0, #0
	beq _0223A460
	sub r0, r0, #1
	str r0, [r5, #0x74]
	beq _0223A456
	mov r0, #0x56
	ldrsh r1, [r5, r0]
	mov r0, #0x5a
	ldrsh r0, [r5, r0]
	add r1, r1, r0
	add r0, r5, #0
	add r0, #0x56
	strh r1, [r0]
	b _0223A460
_0223A456:
	mov r0, #0x58
	ldrsh r1, [r5, r0]
	add r0, r5, #0
	add r0, #0x56
	strh r1, [r0]
_0223A460:
	mov r0, #0x54
	ldrsh r1, [r5, r0]
	mov r0, #0x56
	ldrsh r0, [r5, r0]
	add r1, r1, r0
	add r0, r5, #0
	add r0, #0x54
	strh r1, [r0]
	add r0, r5, #0
	add r0, #0x54
	ldrh r0, [r0]
	mov r1, #0xb6
	bl _s32_div_f
	add r4, r0, #0
	mov r0, #0x5a
	lsl r0, r0, #2
	cmp r4, r0
	blt _0223A488
	sub r4, r4, r0
_0223A488:
	ldr r0, [r5, #0x50]
	cmp r0, #0
	beq _0223A4AE
	ldr r1, [r5, #0x38]
	ldr r0, [r5, #0x40]
	add r0, r1, r0
	str r0, [r5, #0x38]
	ldr r1, [r5, #0x3c]
	ldr r0, [r5, #0x44]
	add r0, r1, r0
	str r0, [r5, #0x3c]
	ldr r0, [r5, #0x50]
	sub r0, r0, #1
	str r0, [r5, #0x50]
	bne _0223A4AE
	ldr r0, [r5, #0x48]
	str r0, [r5, #0x38]
	ldr r0, [r5, #0x4c]
	str r0, [r5, #0x3c]
_0223A4AE:
	add r0, r4, #0
	add r0, #0x5a
	lsl r1, r0, #2
	ldr r0, _0223A578 ; =gSineTable
	ldr r2, [r5, #0x38]
	ldr r0, [r0, r1]
	asr r3, r2, #0x1f
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r3, #2
	mov r6, #0
	lsl r3, r3, #0xa
	add r3, r0, r3
	adc r1, r6
	lsl r0, r1, #0x14
	lsr r1, r3, #0xc
	ldr r2, [r5, #8]
	orr r1, r0
	add r0, r2, r1
	str r0, [r5, #0x14]
	ldr r2, [r5, #0x3c]
	ldr r0, _0223A578 ; =gSineTable
	lsl r1, r4, #2
	ldr r0, [r0, r1]
	asr r3, r2, #0x1f
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r4, #2
	add r3, r6, #0
	lsl r4, r4, #0xa
	add r4, r0, r4
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r4, #0xc
	ldr r2, [r5, #0x10]
	orr r1, r0
	add r0, r2, r1
	str r0, [r5, #0x1c]
	mov r0, #0x22
	ldrsh r1, [r5, r0]
	mov r0, #0x56
	ldrsh r0, [r5, r0]
	mov r2, #0x5e
	mov r6, #0x60
	add r0, r1, r0
	strh r0, [r5, #0x22]
	add r0, r5, #0
	mov r1, #0x5c
_0223A512:
	add r4, r0, #0
	add r4, #0x62
	ldrh r4, [r4]
	cmp r4, #0
	beq _0223A54A
	add r4, r0, #0
	add r4, #0x62
	ldrh r4, [r4]
	sub r7, r4, #1
	add r4, r0, #0
	add r4, #0x62
	strh r7, [r4]
	add r4, r0, #0
	add r4, #0x62
	ldrh r4, [r4]
	cmp r4, #0
	bne _0223A53E
	ldrsh r7, [r0, r6]
	add r4, r0, #0
	add r4, #0x5c
	strh r7, [r4]
	b _0223A54A
_0223A53E:
	ldrsh r7, [r0, r1]
	ldrsh r4, [r0, r2]
	add r7, r7, r4
	add r4, r0, #0
	add r4, #0x5c
	strh r7, [r4]
_0223A54A:
	add r3, r3, #1
	add r0, #8
	cmp r3, #3
	blt _0223A512
	mov r0, #0x20
	ldrsh r1, [r5, r0]
	mov r0, #0x5c
	ldrsh r0, [r5, r0]
	add r0, r1, r0
	strh r0, [r5, #0x20]
	mov r0, #0x22
	ldrsh r1, [r5, r0]
	mov r0, #0x64
	ldrsh r0, [r5, r0]
	add r0, r1, r0
	strh r0, [r5, #0x22]
	mov r0, #0x24
	ldrsh r1, [r5, r0]
	mov r0, #0x6c
	ldrsh r0, [r5, r0]
	add r0, r1, r0
	strh r0, [r5, #0x24]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223A578: .word gSineTable
	thumb_func_end MOD81_0223A434

	thumb_func_start MOD81_0223A57C
MOD81_0223A57C: ; 0x0223A57C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #0
	beq _0223A5DC
	ldr r1, [r4, #0x28]
	ldr r0, [r4, #0x2c]
	add r0, r1, r0
	str r0, [r4, #0x28]
	str r0, [r4, #0x18]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #0
	bgt _0223A5DC
	mov r1, #2
	lsl r1, r1, #8
	str r1, [r4, #0x30]
	mov r0, #0
	lsl r1, r1, #5
	str r0, [r4, #0x2c]
	add r0, r4, #0
	add r2, r1, #0
	mov r3, #0x3c
	bl MOD81_0223A3C0
	ldr r2, _0223A5F8 ; =0xFFFFF800
	add r0, r4, #0
	mov r1, #0
	mov r3, #0x1e
	bl MOD81_0223A3FC
	mov r0, #1
	str r0, [r4, #0x7c]
	ldr r1, _0223A5FC ; =MOD81_0223A600
	add r0, r5, #0
	bl FUN_0201B6C4
_0223A5DC:
	add r0, r4, #0
	bl MOD81_0223A434
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x14
	bl MOD81_02238B18
	ldr r0, [r4]
	add r4, #0x20
	add r1, r4, #0
	bl MOD81_02238B40
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223A5F8: .word 0xFFFFF800
_0223A5FC: .word MOD81_0223A600
	thumb_func_end MOD81_0223A57C

	thumb_func_start MOD81_0223A600
MOD81_0223A600: ; 0x0223A600
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x78]
	cmp r0, #0
	bne _0223A64A
	ldr r1, [r4, #0x2c]
	ldr r0, [r4, #0x30]
	add r1, r1, r0
	str r1, [r4, #0x2c]
	ldr r0, [r4, #0x28]
	add r0, r0, r1
	str r0, [r4, #0x28]
	str r0, [r4, #0x18]
	add r0, r4, #0
	bl MOD81_0223A434
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x14
	bl MOD81_02238B18
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x20
	bl MOD81_02238B40
	ldr r0, [r4]
	bl MOD81_02238B8C
	cmp r0, #0
	bne _0223A64A
	ldr r0, [r4]
	mov r1, #0
	bl MOD81_02238B58
	mov r0, #1
	str r0, [r4, #0x78]
_0223A64A:
	pop {r4, pc}
	thumb_func_end MOD81_0223A600

	thumb_func_start MOD81_0223A64C
MOD81_0223A64C: ; 0x0223A64C
	push {r3, lr}
	bl FUN_0201B6C8
	ldr r0, [r0, #0x78]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD81_0223A64C

	thumb_func_start MOD81_0223A658
MOD81_0223A658: ; 0x0223A658
	push {r3, lr}
	bl FUN_0201B6C8
	ldr r0, [r0, #0x7c]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD81_0223A658

	thumb_func_start MOD81_0223A664
MOD81_0223A664: ; 0x0223A664
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	bl FUN_0201B6C8
	add r4, r0, #0
	mov r1, #0
	str r1, [r4, #0x78]
	add r0, sp, #0
	strh r1, [r0, #4]
	ldrh r1, [r0, #4]
	strh r1, [r0, #2]
	strh r1, [r0]
	ldr r0, [r4, #4]
	mov r1, #1
	bl MOD81_02238C80
	ldr r0, [r4, #4]
	add r1, sp, #0
	bl MOD81_02238C60
	ldr r1, _0223A6EC ; =0x000058CC
	mov r0, #2
	lsl r0, r0, #0x12
	str r1, [r4, #0x2c]
	sub r0, r1, r0
	str r0, [r4, #0x28]
	add r0, r4, #0
	mov r1, #0
	mov r3, #0x14
	add r0, #0x80
	str r3, [r0]
	ldr r0, [r4, #0x28]
	add r2, r1, #0
	str r0, [r4, #0x18]
	add r0, r4, #0
	bl MOD81_0223A3C0
	mov r2, #0x56
	ldrsh r2, [r4, r2]
	add r0, r4, #0
	mov r1, #1
	neg r2, r2
	mov r3, #0x1e
	bl MOD81_0223A3FC
	mov r1, #2
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xfe
	mov r3, #0x32
	bl MOD81_0223A3FC
	mov r1, #2
	ldr r0, [r4]
	lsl r1, r1, #0xc
	bl MOD81_02238B84
	ldr r0, [r4]
	mov r1, #1
	bl MOD81_02238B58
	ldr r1, _0223A6F0 ; =MOD81_0223A6F4
	add r0, r5, #0
	bl FUN_0201B6C4
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223A6EC: .word 0x000058CC
_0223A6F0: .word MOD81_0223A6F4
	thumb_func_end MOD81_0223A664

	thumb_func_start MOD81_0223A6F4
MOD81_0223A6F4: ; 0x0223A6F4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl MOD81_0223A434
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #0
	beq _0223A734
	ldr r1, [r4, #0x28]
	ldr r0, [r4, #0x2c]
	add r0, r1, r0
	str r0, [r4, #0x28]
	str r0, [r4, #0x18]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #0
	bne _0223A734
	ldr r1, _0223A74C ; =MOD81_0223A750
	add r0, r5, #0
	bl FUN_0201B6C4
_0223A734:
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x14
	bl MOD81_02238B18
	ldr r0, [r4]
	add r4, #0x20
	add r1, r4, #0
	bl MOD81_02238B40
	pop {r3, r4, r5, pc}
	nop
_0223A74C: .word MOD81_0223A750
	thumb_func_end MOD81_0223A6F4

	thumb_func_start MOD81_0223A750
MOD81_0223A750: ; 0x0223A750
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl MOD81_0223A434
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #0x6e
	ble _0223A792
	ldr r1, [r4, #0x28]
	ldr r0, _0223A7A8 ; =0xFFFC5800
	sub r0, r0, r1
	mov r1, #0x35
	bl _s32_div_f
	str r0, [r4, #0x2c]
	add r0, r4, #0
	mov r1, #0x35
	add r0, #0x80
	str r1, [r0]
	ldr r1, _0223A7AC ; =MOD81_0223A7B0
	add r0, r5, #0
	bl FUN_0201B6C4
_0223A792:
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x14
	bl MOD81_02238B18
	ldr r0, [r4]
	add r4, #0x20
	add r1, r4, #0
	bl MOD81_02238B40
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223A7A8: .word 0xFFFC5800
_0223A7AC: .word MOD81_0223A7B0
	thumb_func_end MOD81_0223A750

	thumb_func_start MOD81_0223A7B0
MOD81_0223A7B0: ; 0x0223A7B0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl MOD81_0223A434
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #0
	beq _0223A7F0
	ldr r1, [r4, #0x28]
	ldr r0, [r4, #0x2c]
	add r0, r1, r0
	str r0, [r4, #0x28]
	str r0, [r4, #0x18]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #0
	bne _0223A7F0
	ldr r1, _0223A808 ; =MOD81_0223A80C
	add r0, r5, #0
	bl FUN_0201B6C4
_0223A7F0:
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x14
	bl MOD81_02238B18
	ldr r0, [r4]
	add r4, #0x20
	add r1, r4, #0
	bl MOD81_02238B40
	pop {r3, r4, r5, pc}
	nop
_0223A808: .word MOD81_0223A80C
	thumb_func_end MOD81_0223A7B0

	thumb_func_start MOD81_0223A80C
MOD81_0223A80C: ; 0x0223A80C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl MOD81_0223A434
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #1
	ble _0223A83E
	mov r0, #2
	lsl r0, r0, #0x10
	str r0, [r4, #0x2c]
	ldr r1, _0223A854 ; =MOD81_0223A858
	add r0, r5, #0
	bl FUN_0201B6C4
_0223A83E:
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x14
	bl MOD81_02238B18
	ldr r0, [r4]
	add r4, #0x20
	add r1, r4, #0
	bl MOD81_02238B40
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223A854: .word MOD81_0223A858
	thumb_func_end MOD81_0223A80C

	thumb_func_start MOD81_0223A858
MOD81_0223A858: ; 0x0223A858
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x78]
	cmp r0, #0
	bne _0223A894
	add r0, r4, #0
	bl MOD81_0223A434
	ldr r1, [r4, #0x28]
	ldr r0, [r4, #0x2c]
	add r0, r1, r0
	str r0, [r4, #0x28]
	str r0, [r4, #0x18]
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x14
	bl MOD81_02238B18
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x20
	bl MOD81_02238B40
	ldr r0, [r4]
	bl MOD81_02238B8C
	cmp r0, #0
	bne _0223A894
	mov r0, #1
	str r0, [r4, #0x78]
_0223A894:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223A858

	thumb_func_start MOD81_0223A898
MOD81_0223A898: ; 0x0223A898
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x3a
	mov r1, #0xa4
	bl AllocFromHeap
	add r4, r0, #0
	beq _0223A8C2
	str r5, [r4]
	mov r0, #0
	str r0, [r4, #4]
	add r0, r5, #0
	bl MOD81_0223880C
	str r0, [r4, #0x24]
	mov r0, #0
	str r0, [r4, #0x28]
	add r0, r4, #0
	add r0, #0x34
	bl MOD81_0223AD80
_0223A8C2:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD81_0223A898

	thumb_func_start MOD81_0223A8C8
MOD81_0223A8C8: ; 0x0223A8C8
	push {r4, lr}
	add r4, r0, #0
	beq _0223A8F6
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	add r0, r4, #0
	bl MOD81_0223ABC0
	add r0, r4, #0
	bl MOD81_0223ACD8
	add r0, r4, #0
	bl MOD81_0223AD68
	add r0, r4, #0
	add r0, #0x34
	bl MOD81_0223AD88
	add r0, r4, #0
	bl FreeToHeap
_0223A8F6:
	pop {r4, pc}
	thumb_func_end MOD81_0223A8C8

	thumb_func_start MOD81_0223A8F8
MOD81_0223A8F8: ; 0x0223A8F8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r2, [r4]
	add r5, r0, #0
	cmp r2, #2
	bhs _0223A926
	lsl r3, r2, #2
	ldr r2, _0223A92C ; =0x0223D114
	add r1, r5, #4
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #0
	beq _0223A91C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	str r0, [r5, #4]
_0223A91C:
	add r0, r5, #0
	bl MOD81_0223A930
	mov r0, #0
	pop {r3, r4, r5, pc}
_0223A926:
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_0223A92C: .word MOD81_0223D114
	thumb_func_end MOD81_0223A8F8

	thumb_func_start MOD81_0223A930
MOD81_0223A930: ; 0x0223A930
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _0223A94C
	bl G3X_ResetMtxStack
	ldr r0, [r4, #0x28]
	bl MOD81_02238940
	mov r0, #0
	add r1, r0, #0
	bl FUN_020222B4
_0223A94C:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223A930

	thumb_func_start MOD81_0223A950
MOD81_0223A950: ; 0x0223A950
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD81_0223AA68
	add r0, r4, #0
	bl MOD81_0223ABD8
	add r0, r4, #0
	bl MOD81_0223ACE8
	mov r2, #0
	ldr r0, _0223A990 ; =MOD81_0223B090
	add r1, r4, #0
	str r2, [r4, #0xc]
	bl FUN_0200CA98
	mov r0, #3
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	ldr r3, _0223A994 ; =0x00007FFF
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200E1D0
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0223A990: .word MOD81_0223B090
_0223A994: .word 0x00007FFF
	thumb_func_end MOD81_0223A950

	thumb_func_start MOD81_0223A998
MOD81_0223A998: ; 0x0223A998
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #4
	bhi _0223AA54
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223A9B2: ; jump table
	.short _0223A9BC - _0223A9B2 - 2 ; case 0
	.short _0223A9C8 - _0223A9B2 - 2 ; case 1
	.short _0223A9F2 - _0223A9B2 - 2 ; case 2
	.short _0223AA1C - _0223A9B2 - 2 ; case 3
	.short _0223AA46 - _0223A9B2 - 2 ; case 4
_0223A9BC:
	mov r0, #0
	str r0, [r5, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0223AA54
_0223A9C8:
	ldr r0, [r5, #8]
	add r0, r0, #1
	str r0, [r5, #8]
	cmp r0, #0xa
	ble _0223AA54
	ldr r0, _0223AA5C ; =0x000006AC
	bl FUN_020054C8
	add r1, r5, #0
	add r0, r5, #0
	add r1, #0x34
	bl MOD81_0223AD9C
	ldr r0, [r5, #0x2c]
	mov r1, #1
	bl MOD81_02238B58
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0223AA54
_0223A9F2:
	add r0, r5, #0
	add r0, #0x34
	bl MOD81_0223AE48
	cmp r0, #0
	beq _0223AA54
	ldr r0, _0223AA60 ; =0x000006AD
	bl FUN_020054C8
	ldr r0, [r5, #0x20]
	mov r1, #3
	bl FUN_02020130
	ldr r0, [r5, #0x20]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0223AA54
_0223AA1C:
	ldr r0, [r5, #0x20]
	bl FUN_02020388
	cmp r0, #0
	bne _0223AA54
	mov r0, #0x10
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0
	ldr r3, _0223AA64 ; =0x00007FFF
	add r1, r0, #0
	add r2, r0, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0223AA54
_0223AA46:
	bl FUN_0200E308
	cmp r0, #0
	beq _0223AA54
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_0223AA54:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0223AA5C: .word 0x000006AC
_0223AA60: .word 0x000006AD
_0223AA64: .word 0x00007FFF
	thumb_func_end MOD81_0223A998

	thumb_func_start MOD81_0223AA68
MOD81_0223AA68: ; 0x0223AA68
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r0, _0223ABAC ; =0x0223D158
	bl GX_SetBanks
	ldr r2, _0223ABB0 ; =0x04000304
	ldr r0, _0223ABB4 ; =0xFFFF7FFF
	ldrh r1, [r2]
	and r0, r1
	strh r0, [r2]
	ldr r0, _0223ABB8 ; =0x0223D11C
	bl FUN_02016BBC
	ldr r0, [r4, #0x24]
	ldr r2, _0223ABBC ; =0x0223D13C
	mov r1, #3
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x24]
	ldr r2, _0223ABBC ; =0x0223D13C
	mov r1, #7
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4]
	bl MOD81_02238828
	cmp r0, #3
	bhi _0223AABA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223AAB2: ; jump table
	.short _0223AABA - _0223AAB2 - 2 ; case 0
	.short _0223AAC6 - _0223AAB2 - 2 ; case 1
	.short _0223AAD2 - _0223AAB2 - 2 ; case 2
	.short _0223AADE - _0223AAB2 - 2 ; case 3
_0223AABA:
	mov r0, #0xf
	str r0, [sp, #0x10]
	mov r7, #0x10
	mov r6, #0x11
	mov r5, #0
	b _0223AAE8
_0223AAC6:
	mov r0, #0xf
	str r0, [sp, #0x10]
	mov r7, #0x10
	mov r6, #0x11
	mov r5, #0x20
	b _0223AAE8
_0223AAD2:
	mov r0, #0xf
	str r0, [sp, #0x10]
	mov r7, #0x10
	mov r6, #0x11
	mov r5, #0x40
	b _0223AAE8
_0223AADE:
	mov r0, #0x18
	str r0, [sp, #0x10]
	mov r7, #0x19
	mov r6, #0x1a
	mov r5, #0
_0223AAE8:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x24]
	mov r0, #0x5d
	add r1, r7, #0
	mov r3, #3
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x24]
	mov r0, #0x5d
	add r1, r7, #0
	mov r3, #7
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r2, [r4, #0x24]
	mov r0, #0x5d
	mov r3, #3
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r2, [r4, #0x24]
	mov r0, #0x5d
	mov r3, #7
	bl GfGfxLoader_LoadScrnData
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0x5d
	add r1, r6, #0
	add r3, r5, #0
	bl GfGfxLoader_GXLoadPalWithSrcOffset
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0x5d
	add r1, r6, #0
	mov r2, #4
	add r3, r5, #0
	bl GfGfxLoader_GXLoadPalWithSrcOffset
	mov r1, #3
	add r3, r1, #0
	ldr r0, [r4, #0x24]
	add r2, r1, #0
	add r3, #0xfd
	bl FUN_020179E0
	ldr r0, [r4, #0x24]
	mov r1, #7
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223ABAC: .word MOD81_0223D158
_0223ABB0: .word 0x04000304
_0223ABB4: .word 0xFFFF7FFF
_0223ABB8: .word MOD81_0223D11C
_0223ABBC: .word MOD81_0223D13C
	thumb_func_end MOD81_0223AA68

	thumb_func_start MOD81_0223ABC0
MOD81_0223ABC0: ; 0x0223ABC0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x24]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #0x24]
	mov r1, #7
	bl FUN_020178A0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223ABC0

	thumb_func_start MOD81_0223ABD8
MOD81_0223ABD8: ; 0x0223ABD8
	push {r3, r4, lr}
	sub sp, #0x24
	add r4, r0, #0
	bl NNS_G3dInit
	bl G3X_InitMtxStack
	ldr r0, _0223ACAC ; =0x04000060
	ldr r1, _0223ACB0 ; =0xFFFFCFFD
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
	ldr r2, _0223ACB4 ; =0x0000CFFB
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
	ldr r0, _0223ACB8 ; =0x0223D12C
	bl G3X_SetEdgeColorTable
	mov r1, #0
	ldr r0, _0223ACBC ; =0x000043FF
	ldr r2, _0223ACC0 ; =0x00007FFF
	mov r3, #0x3f
	str r1, [sp]
	bl G3X_SetClearColor
	ldr r1, _0223ACC4 ; =0x04000540
	mov r0, #2
	str r0, [r1]
	ldr r0, _0223ACC8 ; =0xBFFF0000
	str r0, [r1, #0x40]
	mov r0, #1
	add r1, r0, #0
	bl NNS_GfdInitFrmTexVramManager
	mov r0, #1
	lsl r0, r0, #0xe
	mov r1, #1
	bl NNS_GfdInitFrmPlttVramManager
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r1, _0223ACCC ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	strh r2, [r1]
	mov r1, #0
	mov r0, #1
	add r2, r1, #0
	add r3, r1, #0
	bl MOD81_022388C0
	str r0, [r4, #0x28]
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r4, #0x28]
	mov r2, #0x5d
	mov r3, #0x1b
	bl MOD81_02238A84
	ldr r1, _0223ACD0 ; =0x000018E3
	str r0, [r4, #0x2c]
	add r0, sp, #0x10
	strh r1, [r0]
	mov r1, #0
	strh r1, [r0, #2]
	strh r1, [r0, #4]
	ldr r0, [r4, #0x28]
	add r1, sp, #0x10
	bl MOD81_02238C60
	ldr r0, [r4, #0x28]
	ldr r1, _0223ACD4 ; =0x000007D2
	bl MOD81_02238C90
	ldr r0, [r4, #0x28]
	add r1, sp, #0x18
	bl MOD81_02238C40
	add sp, #0x24
	pop {r3, r4, pc}
	nop
_0223ACAC: .word 0x04000060
_0223ACB0: .word 0xFFFFCFFD
_0223ACB4: .word 0x0000CFFB
_0223ACB8: .word MOD81_0223D12C
_0223ACBC: .word 0x000043FF
_0223ACC0: .word 0x00007FFF
_0223ACC4: .word 0x04000540
_0223ACC8: .word 0xBFFF0000
_0223ACCC: .word 0x04000008
_0223ACD0: .word 0x000018E3
_0223ACD4: .word 0x000007D2
	thumb_func_end MOD81_0223ABD8

	thumb_func_start MOD81_0223ACD8
MOD81_0223ACD8: ; 0x0223ACD8
	push {r3, lr}
	ldr r0, [r0, #0x28]
	cmp r0, #0
	beq _0223ACE4
	bl MOD81_0223890C
_0223ACE4:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD81_0223ACD8

	thumb_func_start MOD81_0223ACE8
MOD81_0223ACE8: ; 0x0223ACE8
	push {r4, lr}
	sub sp, #0x70
	add r4, r0, #0
	add r0, #0x10
	mov r1, #0x5d
	mov r2, #7
	mov r3, #8
	bl MOD81_0223874C
	add r0, sp, #0x5c
	bl NNS_G2dInitImagePaletteProxy
	add r0, sp, #0x38
	bl NNS_G2dInitImageProxy
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	add r0, sp, #0x38
	str r0, [sp, #0x10]
	mov r0, #0x5d
	mov r1, #9
	bl GfGfxLoader_LoadImageMapping
	mov r0, #0x3a
	str r0, [sp]
	add r0, sp, #0x5c
	str r0, [sp, #4]
	mov r0, #0x5d
	mov r1, #0xa
	mov r2, #1
	mov r3, #0
	bl GfGfxLoader_PartiallyLoadPalette
	mov r0, #0
	add r1, r4, #0
	str r0, [sp]
	add r0, sp, #0x14
	add r1, #0x10
	add r2, sp, #0x38
	add r3, sp, #0x5c
	bl MOD81_022387A8
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #0x14
	mov r2, #0x80
	mov r3, #0x60
	bl MOD81_022387C8
	mov r1, #0
	str r0, [r4, #0x20]
	bl FUN_020200A0
	add sp, #0x70
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223ACE8

	thumb_func_start MOD81_0223AD68
MOD81_0223AD68: ; 0x0223AD68
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _0223AD76
	bl FUN_0201FFC8
_0223AD76:
	add r4, #0x10
	add r0, r4, #0
	bl MOD81_02238784
	pop {r4, pc}
	thumb_func_end MOD81_0223AD68

	thumb_func_start MOD81_0223AD80
MOD81_0223AD80: ; 0x0223AD80
	mov r1, #0
	str r1, [r0, #4]
	bx lr
	.align 2, 0
	thumb_func_end MOD81_0223AD80

	thumb_func_start MOD81_0223AD88
MOD81_0223AD88: ; 0x0223AD88
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _0223AD9A
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #4]
_0223AD9A:
	pop {r4, pc}
	thumb_func_end MOD81_0223AD88

	thumb_func_start MOD81_0223AD9C
MOD81_0223AD9C: ; 0x0223AD9C
	push {r4, lr}
	add r4, r1, #0
	str r0, [r4]
	ldr r1, [r0, #0x2c]
	ldr r2, _0223AE2C ; =0xFFFFD870
	str r1, [r4, #0xc]
	ldr r0, [r0, #0x28]
	ldr r1, _0223AE30 ; =0xFFF50E00
	str r0, [r4, #8]
	mov r0, #0
	str r0, [r4, #0x10]
	str r1, [r4, #0x14]
	mov r1, #0xe2
	lsl r1, r1, #0xc
	str r1, [r4, #0x18]
	add r1, r4, #0
	add r1, #0x6c
	strh r2, [r1]
	add r1, r4, #0
	ldr r2, _0223AE34 ; =0xFFFFF550
	add r1, #0x6e
	strh r2, [r1]
	ldr r1, _0223AE38 ; =0x000134C4
	str r1, [r4, #0x3c]
	ldr r1, _0223AE3C ; =0xFFFF4D56
	str r1, [r4, #0x40]
	str r0, [r4, #0x60]
	str r0, [r4, #0x64]
	mov r1, #2
	str r0, [r4, #0x68]
	lsl r1, r1, #0xc
	strh r1, [r4, #0x34]
	ldr r1, _0223AE40 ; =0xFFFFE000
	strh r1, [r4, #0x36]
	strh r0, [r4, #0x38]
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x34
	bl MOD81_02238B40
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [r4, #0x54]
	mov r0, #0x4a
	lsl r0, r0, #0xa
	str r0, [r4, #0x44]
	mov r0, #0x63
	lsl r0, r0, #0xa
	str r0, [r4, #0x48]
	mov r0, #0
	str r0, [r4, #0x5c]
	add r0, r4, #0
	bl MOD81_0223AE90
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x28
	bl MOD81_02238B18
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x34
	bl MOD81_02238B28
	ldr r0, _0223AE44 ; =MOD81_0223AF5C
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	str r0, [r4, #4]
	pop {r4, pc}
	nop
_0223AE2C: .word 0xFFFFD870
_0223AE30: .word 0xFFF50E00
_0223AE34: .word 0xFFFFF550
_0223AE38: .word 0x000134C4
_0223AE3C: .word 0xFFFF4D56
_0223AE40: .word 0xFFFFE000
_0223AE44: .word MOD81_0223AF5C
	thumb_func_end MOD81_0223AD9C

	thumb_func_start MOD81_0223AE48
MOD81_0223AE48: ; 0x0223AE48
	ldr r0, [r0, #4]
	cmp r0, #0
	bne _0223AE52
	mov r0, #1
	bx lr
_0223AE52:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD81_0223AE48

	thumb_func_start MOD81_0223AE58
MOD81_0223AE58: ; 0x0223AE58
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, [sp, #0x18]
	add r5, r0, #0
	add r6, r2, #0
	add r7, r3, #0
	cmp r4, #0
	beq _0223AE8E
	ldr r0, [r5, #0x44]
	sub r0, r1, r0
	add r1, r4, #0
	bl _s32_div_f
	str r0, [r5, #0x4c]
	ldr r0, [r5, #0x48]
	add r1, r4, #0
	sub r0, r6, r0
	bl _s32_div_f
	str r0, [r5, #0x50]
	ldr r0, [r5, #0x54]
	add r1, r4, #0
	sub r0, r7, r0
	bl _s32_div_f
	str r0, [r5, #0x58]
	ldr r0, [sp, #0x18]
	str r0, [r5, #0x5c]
_0223AE8E:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD81_0223AE58

	thumb_func_start MOD81_0223AE90
MOD81_0223AE90: ; 0x0223AE90
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0x6c
	ldrh r0, [r0]
	mov r1, #0xb6
	bl _s32_div_f
	add r4, r0, #0
	mov r0, #0x5a
	lsl r0, r0, #2
	cmp r4, r0
	blt _0223AEAA
	sub r4, r4, r0
_0223AEAA:
	mov r0, #0x6c
	ldrsh r1, [r5, r0]
	mov r0, #0x6e
	ldrsh r0, [r5, r0]
	add r1, r1, r0
	add r0, r5, #0
	add r0, #0x6c
	strh r1, [r0]
	ldr r0, [r5, #0x5c]
	cmp r0, #0
	beq _0223AEE4
	ldr r1, [r5, #0x44]
	ldr r0, [r5, #0x4c]
	add r0, r1, r0
	str r0, [r5, #0x44]
	ldr r1, [r5, #0x48]
	ldr r0, [r5, #0x50]
	add r0, r1, r0
	str r0, [r5, #0x48]
	ldr r1, [r5, #0x54]
	ldr r0, [r5, #0x58]
	add r1, r1, r0
	str r1, [r5, #0x54]
	ldr r0, [r5, #0xc]
	bl MOD81_02238B84
	ldr r0, [r5, #0x5c]
	sub r0, r0, #1
	str r0, [r5, #0x5c]
_0223AEE4:
	add r0, r4, #0
	add r0, #0x5a
	lsl r1, r0, #2
	ldr r0, _0223AF58 ; =gSineTable
	ldr r2, [r5, #0x44]
	ldr r0, [r0, r1]
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
	str r1, [r5, #0x1c]
	ldr r2, [r5, #0x48]
	ldr r0, _0223AF58 ; =gSineTable
	lsl r1, r4, #2
	ldr r0, [r0, r1]
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
	str r1, [r5, #0x20]
	add r1, r5, #0
	str r3, [r5, #0x24]
	mov r0, #0x34
	ldrsh r2, [r5, r0]
	mov r0, #3
	lsl r0, r0, #8
	add r0, r2, r0
	strh r0, [r5, #0x34]
	ldr r0, [r5, #0xc]
	add r1, #0x34
	bl MOD81_02238B40
	add r0, r5, #0
	add r1, r5, #0
	add r5, #0x28
	add r0, #0x1c
	add r1, #0x10
	add r2, r5, #0
	bl VEC_Add
	pop {r3, r4, r5, pc}
	nop
_0223AF58: .word gSineTable
	thumb_func_end MOD81_0223AE90

	thumb_func_start MOD81_0223AF5C
MOD81_0223AF5C: ; 0x0223AF5C
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldr r1, [r4, #0x68]
	cmp r1, #0x3c
	bge _0223AF6C
	add r1, r1, #1
	str r1, [r4, #0x68]
_0223AF6C:
	ldr r1, [r4, #0x60]
	cmp r1, #4
	bls _0223AF74
	b _0223B084
_0223AF74:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223AF80: ; jump table
	.short _0223AF8A - _0223AF80 - 2 ; case 0
	.short _0223AFBE - _0223AF80 - 2 ; case 1
	.short _0223AFFC - _0223AF80 - 2 ; case 2
	.short _0223B042 - _0223AF80 - 2 ; case 3
	.short _0223B072 - _0223AF80 - 2 ; case 4
_0223AF8A:
	ldr r1, [r4, #0x14]
	ldr r0, [r4, #0x3c]
	add r0, r1, r0
	str r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	ldr r0, [r4, #0x40]
	add r0, r1, r0
	str r0, [r4, #0x18]
	add r0, r4, #0
	bl MOD81_0223AE90
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x28
	bl MOD81_02238B18
	ldr r0, [r4, #0xc]
	bl MOD81_02238B8C
	cmp r0, #0
	beq _0223B084
	ldr r0, [r4, #0x60]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0x60]
	pop {r3, r4, pc}
_0223AFBE:
	ldr r0, [r4, #0xc]
	bl MOD81_02238B8C
	cmp r0, #0
	bne _0223AFD8
	ldr r0, [r4]
	bl MOD81_0223B088
	ldr r0, [r4, #0x60]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0x60]
	pop {r3, r4, pc}
_0223AFD8:
	ldr r1, [r4, #0x14]
	ldr r0, [r4, #0x3c]
	add r0, r1, r0
	str r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	ldr r0, [r4, #0x40]
	add r0, r1, r0
	str r0, [r4, #0x18]
	add r0, r4, #0
	bl MOD81_0223AE90
	ldr r0, [r4, #0xc]
	add r4, #0x28
	add r1, r4, #0
	bl MOD81_02238B18
	add sp, #4
	pop {r3, r4, pc}
_0223AFFC:
	ldr r1, [r4, #0x14]
	ldr r0, [r4, #0x3c]
	add r0, r1, r0
	str r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	ldr r0, [r4, #0x40]
	add r0, r1, r0
	str r0, [r4, #0x18]
	add r0, r4, #0
	bl MOD81_0223AE90
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x28
	bl MOD81_02238B18
	ldr r0, [r4, #0x68]
	cmp r0, #0x3c
	blt _0223B084
	mov r1, #2
	lsl r1, r1, #0xa
	mov r0, #0xc
	str r0, [sp]
	add r0, r4, #0
	add r2, r1, #0
	lsr r3, r1, #2
	bl MOD81_0223AE58
	mov r0, #0
	str r0, [r4, #0x64]
	ldr r0, [r4, #0x60]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0x60]
	pop {r3, r4, pc}
_0223B042:
	add r0, r4, #0
	bl MOD81_0223AE90
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x28
	bl MOD81_02238B18
	ldr r0, [r4, #0x64]
	add r0, r0, #1
	str r0, [r4, #0x64]
	cmp r0, #0xc
	blt _0223B084
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl MOD81_02238B58
	mov r0, #0
	str r0, [r4, #0x64]
	ldr r0, [r4, #0x60]
	add sp, #4
	add r0, r0, #1
	str r0, [r4, #0x60]
	pop {r3, r4, pc}
_0223B072:
	ldr r1, [r4, #0x64]
	add r1, r1, #1
	str r1, [r4, #0x64]
	cmp r1, #8
	ble _0223B084
	mov r1, #0
	str r1, [r4, #4]
	bl FUN_0200CAB4
_0223B084:
	add sp, #4
	pop {r3, r4, pc}
	thumb_func_end MOD81_0223AF5C

	thumb_func_start MOD81_0223B088
MOD81_0223B088: ; 0x0223B088
	mov r1, #1
	str r1, [r0, #0xc]
	bx lr
	.align 2, 0
	thumb_func_end MOD81_0223B088

	thumb_func_start MOD81_0223B090
MOD81_0223B090: ; 0x0223B090
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _0223B0DC
	mov r3, #0
	ldr r1, _0223B0E0 ; =0x00001150
	str r3, [r4, #0xc]
	add r0, sp, #0
	strh r1, [r0]
	strh r3, [r0, #2]
	strh r3, [r0, #4]
	mov r1, #3
	ldr r0, [r4, #0x24]
	add r2, r1, #0
	bl FUN_020179E0
	mov r2, #3
	add r3, r2, #0
	ldr r0, [r4, #0x24]
	mov r1, #7
	add r3, #0xfd
	bl FUN_020179E0
	ldr r0, [r4, #0x28]
	add r1, sp, #0
	bl MOD81_02238C70
	ldr r2, _0223B0E4 ; =0x04000304
	ldrh r1, [r2]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2]
	add r0, r5, #0
	bl FUN_0200CAB4
_0223B0DC:
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223B0E0: .word 0x00001150
_0223B0E4: .word 0x04000304
	thumb_func_end MOD81_0223B090

	thumb_func_start MOD81_0223B0E8
MOD81_0223B0E8: ; 0x0223B0E8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x3a
	mov r1, #0x24
	bl AllocFromHeap
	add r4, r0, #0
	beq _0223B106
	str r5, [r4]
	mov r0, #0
	str r0, [r4, #4]
	add r0, r5, #0
	bl MOD81_0223880C
	str r0, [r4, #0xc]
_0223B106:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD81_0223B0E8

	thumb_func_start MOD81_0223B10C
MOD81_0223B10C: ; 0x0223B10C
	push {r4, lr}
	add r4, r0, #0
	beq _0223B11C
	bl MOD81_0223B478
	add r0, r4, #0
	bl FreeToHeap
_0223B11C:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223B10C

	thumb_func_start MOD81_0223B120
MOD81_0223B120: ; 0x0223B120
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r2, [r4]
	add r5, r0, #0
	cmp r2, #2
	bhs _0223B148
	lsl r3, r2, #2
	ldr r2, _0223B14C ; =0x0223D180
	add r1, r5, #4
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #0
	beq _0223B144
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	str r0, [r5, #4]
_0223B144:
	mov r0, #0
	pop {r3, r4, r5, pc}
_0223B148:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223B14C: .word MOD81_0223D180
	thumb_func_end MOD81_0223B120

	thumb_func_start MOD81_0223B150
MOD81_0223B150: ; 0x0223B150
	push {lr}
	sub sp, #0xc
	bl MOD81_0223B264
	mov r0, #8
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	ldr r3, _0223B174 ; =0x00007FFF
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200E1D0
	mov r0, #1
	add sp, #0xc
	pop {pc}
	.align 2, 0
_0223B174: .word 0x00007FFF
	thumb_func_end MOD81_0223B150

	thumb_func_start MOD81_0223B178
MOD81_0223B178: ; 0x0223B178
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _0223B190
	cmp r0, #1
	beq _0223B1C2
	cmp r0, #2
	beq _0223B1EE
	b _0223B1FC
_0223B190:
	bl FUN_0200E308
	cmp r0, #0
	beq _0223B1FC
	ldr r0, _0223B204 ; =0xFFE80000
	mov r2, #0
	str r0, [r5, #0x10]
	mov r0, #5
	lsl r0, r0, #0x10
	str r0, [r5, #0x14]
	ldr r0, _0223B208 ; =0x00005999
	add r1, r5, #0
	str r0, [r5, #0x18]
	ldr r0, _0223B20C ; =0xFFFFDDDE
	str r0, [r5, #0x1c]
	mov r0, #0x3c
	str r0, [r5, #8]
	ldr r0, _0223B210 ; =MOD81_0223B21C
	str r2, [r5, #0x20]
	bl FUN_0200CA60
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0223B1FC
_0223B1C2:
	ldr r0, [r5, #0x20]
	cmp r0, #0
	beq _0223B1FC
	ldr r0, _0223B214 ; =0x000006A9
	bl FUN_020054C8
	mov r0, #0x10
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0
	ldr r3, _0223B218 ; =0x00007FFF
	add r1, r0, #0
	add r2, r0, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0223B1FC
_0223B1EE:
	bl FUN_0200E308
	cmp r0, #0
	beq _0223B1FC
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_0223B1FC:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0223B204: .word 0xFFE80000
_0223B208: .word 0x00005999
_0223B20C: .word 0xFFFFDDDE
_0223B210: .word MOD81_0223B21C
_0223B214: .word 0x000006A9
_0223B218: .word 0x00007FFF
	thumb_func_end MOD81_0223B178

	thumb_func_start MOD81_0223B21C
MOD81_0223B21C: ; 0x0223B21C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _0223B24A
	sub r0, r0, #1
	str r0, [r4, #8]
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x18]
	add r0, r1, r0
	str r0, [r4, #0x10]
	ldr r1, [r4, #0x14]
	ldr r0, [r4, #0x1c]
	add r2, r1, r0
	str r2, [r4, #0x14]
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0xc]
	asr r1, r1, #0xc
	asr r2, r2, #0xc
	bl MOD81_0223B4B0
	pop {r3, r4, r5, pc}
_0223B24A:
	mov r1, #0x2f
	mvn r1, r1
	ldr r0, [r4, #0xc]
	add r2, r1, #0
	bl MOD81_0223B4B0
	mov r0, #1
	str r0, [r4, #0x20]
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD81_0223B21C

	thumb_func_start MOD81_0223B264
MOD81_0223B264: ; 0x0223B264
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, _0223B45C ; =0x0223D1EC
	bl GX_SetBanks
	ldr r2, _0223B460 ; =0x04000304
	ldrh r1, [r2]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2]
	ldr r0, _0223B464 ; =0x0223D188
	bl FUN_02016BBC
	ldr r0, [r4, #0xc]
	ldr r2, _0223B468 ; =0x0223D198
	mov r1, #1
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0xc]
	ldr r2, _0223B468 ; =0x0223D198
	mov r1, #5
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0xc]
	ldr r2, _0223B46C ; =0x0223D1B4
	mov r1, #2
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0xc]
	ldr r2, _0223B470 ; =0x0223D1D0
	mov r1, #3
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0xc]
	ldr r2, _0223B470 ; =0x0223D1D0
	mov r1, #7
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x5d
	mov r1, #0x13
	mov r3, #3
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x5d
	mov r1, #0x13
	mov r3, #7
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x5d
	mov r1, #0x12
	mov r3, #3
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x5d
	mov r1, #0x12
	mov r3, #7
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x3a
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x5d
	mov r1, #0x14
	add r3, r2, #0
	bl GfGfxLoader_GXLoadPal
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x3a
	str r0, [sp, #4]
	mov r0, #0x5d
	mov r1, #0x14
	mov r2, #4
	mov r3, #0
	bl GfGfxLoader_GXLoadPal
	mov r0, #0xc8
	str r0, [sp]
	mov r1, #1
	ldr r0, [r4, #0xc]
	mov r2, #0
	add r3, r1, #0
	bl FUN_02017F48
	mov r0, #0xc8
	str r0, [sp]
	ldr r0, [r4, #0xc]
	mov r1, #5
	mov r2, #0
	mov r3, #1
	bl FUN_02017F48
	mov r0, #0xc8
	str r0, [sp]
	ldr r0, [r4, #0xc]
	mov r1, #2
	mov r2, #0
	mov r3, #1
	bl FUN_02017F48
	mov r1, #0
	str r1, [sp]
	ldr r0, [r4]
	mov r2, #1
	mov r3, #0xe
	bl MOD81_022385D0
	mov r1, #0
	str r1, [sp]
	ldr r0, [r4]
	mov r2, #5
	mov r3, #0xe
	bl MOD81_022385D0
	mov r0, #0
	str r0, [sp]
	ldr r0, [r4]
	mov r1, #1
	mov r2, #2
	mov r3, #0xf
	bl MOD81_022385D0
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x40
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r0, [r4, #0xc]
	mov r1, #1
	mov r2, #0xc8
	bl FUN_02018540
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x40
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r0, [r4, #0xc]
	mov r1, #5
	mov r2, #0xc8
	bl FUN_02018540
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x40
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r0, [r4, #0xc]
	mov r1, #2
	mov r2, #0xc8
	bl FUN_02018540
	mov r0, #0x14
	str r0, [sp]
	mov r1, #0
	str r1, [sp, #4]
	ldr r0, [r4]
	mov r2, #1
	mov r3, #0xe
	bl MOD81_022386BC
	mov r0, #0x14
	str r0, [sp]
	mov r1, #0
	str r1, [sp, #4]
	ldr r0, [r4]
	mov r2, #5
	mov r3, #0xe
	bl MOD81_022386BC
	mov r2, #2
	str r2, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, [r4]
	mov r1, #1
	mov r3, #0xf
	bl MOD81_022386BC
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_02017CD0
	ldr r0, [r4, #0xc]
	mov r1, #5
	bl FUN_02017CD0
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl FUN_02017CD0
	ldr r0, [r4, #0xc]
	ldr r2, _0223B474 ; =0xFFFFFE80
	mov r1, #0x50
	bl MOD81_0223B4B0
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_0223B45C: .word MOD81_0223D1EC
_0223B460: .word 0x04000304
_0223B464: .word MOD81_0223D188
_0223B468: .word MOD81_0223D198
_0223B46C: .word MOD81_0223D1B4
_0223B470: .word MOD81_0223D1D0
_0223B474: .word 0xFFFFFE80
	thumb_func_end MOD81_0223B264

	thumb_func_start MOD81_0223B478
MOD81_0223B478: ; 0x0223B478
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #7
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #6
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #5
	bl FUN_020178A0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223B478

	thumb_func_start MOD81_0223B4B0
MOD81_0223B4B0: ; 0x0223B4B0
	push {r4, r5, r6, lr}
	ldr r3, _0223B4E4 ; =0x000001FF
	add r4, r1, #0
	add r6, r2, #0
	and r4, r3
	add r5, r0, #0
	mov r1, #2
	mov r2, #3
	and r3, r6
	bl FUN_020179E0
	add r0, r5, #0
	mov r1, #1
	mov r2, #3
	add r3, r4, #0
	bl FUN_020179E0
	add r4, #0xc0
	add r0, r5, #0
	mov r1, #5
	mov r2, #3
	add r3, r4, #0
	bl FUN_020179E0
	pop {r4, r5, r6, pc}
	nop
_0223B4E4: .word 0x000001FF
	thumb_func_end MOD81_0223B4B0

	thumb_func_start MOD81_0223B4E8
MOD81_0223B4E8: ; 0x0223B4E8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x3a
	mov r1, #0xb0
	bl AllocFromHeap
	add r4, r0, #0
	beq _0223B51C
	str r5, [r4]
	mov r0, #0
	str r0, [r4, #4]
	add r0, r5, #0
	bl MOD81_0223880C
	str r0, [r4, #0x24]
	mov r0, #0
	str r0, [r4, #0x28]
	str r0, [r4, #0xc]
	add r0, r4, #0
	add r0, #0x34
	bl MOD81_0223B9A0
	ldr r0, _0223B520 ; =MOD81_0223BCA8
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
_0223B51C:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223B520: .word MOD81_0223BCA8
	thumb_func_end MOD81_0223B4E8

	thumb_func_start MOD81_0223B524
MOD81_0223B524: ; 0x0223B524
	push {r4, lr}
	add r4, r0, #0
	beq _0223B552
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	add r0, r4, #0
	bl MOD81_0223B7D0
	add r0, r4, #0
	bl MOD81_0223B8F8
	add r0, r4, #0
	bl MOD81_0223B988
	add r0, r4, #0
	add r0, #0x34
	bl MOD81_0223B9A8
	add r0, r4, #0
	bl FreeToHeap
_0223B552:
	pop {r4, pc}
	thumb_func_end MOD81_0223B524

	thumb_func_start MOD81_0223B554
MOD81_0223B554: ; 0x0223B554
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r2, [r4]
	add r5, r0, #0
	cmp r2, #2
	bhs _0223B57C
	lsl r3, r2, #2
	ldr r2, _0223B580 ; =0x0223D214
	add r1, r5, #4
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #0
	beq _0223B578
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	str r0, [r5, #4]
_0223B578:
	mov r0, #0
	pop {r3, r4, r5, pc}
_0223B57C:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223B580: .word MOD81_0223D214
	thumb_func_end MOD81_0223B554

	thumb_func_start MOD81_0223B584
MOD81_0223B584: ; 0x0223B584
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD81_0223B670
	add r0, r4, #0
	bl MOD81_0223B7E8
	add r0, r4, #0
	bl MOD81_0223B908
	mov r0, #8
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	ldr r3, _0223B5B8 ; =0x00007FFF
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200E1D0
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0223B5B8: .word 0x00007FFF
	thumb_func_end MOD81_0223B584

	thumb_func_start MOD81_0223B5BC
MOD81_0223B5BC: ; 0x0223B5BC
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #3
	bhi _0223B662
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223B5D6: ; jump table
	.short _0223B5DE - _0223B5D6 - 2 ; case 0
	.short _0223B5FE - _0223B5D6 - 2 ; case 1
	.short _0223B628 - _0223B5D6 - 2 ; case 2
	.short _0223B654 - _0223B5D6 - 2 ; case 3
_0223B5DE:
	bl FUN_0200E308
	cmp r0, #0
	beq _0223B662
	ldr r0, [r5, #0x20]
	mov r1, #3
	bl FUN_02020130
	ldr r0, [r5, #0x20]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0223B662
_0223B5FE:
	ldr r0, [r5, #0x20]
	bl FUN_02020388
	cmp r0, #0
	bne _0223B662
	ldr r0, _0223B668 ; =0x000006AB
	bl FUN_020054C8
	add r1, r5, #0
	add r0, r5, #0
	add r1, #0x34
	bl MOD81_0223B9BC
	ldr r0, [r5, #0x2c]
	mov r1, #1
	bl MOD81_02238B58
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0223B662
_0223B628:
	add r5, #0x34
	add r0, r5, #0
	bl MOD81_0223BA7C
	cmp r0, #0
	beq _0223B662
	mov r0, #0x10
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0
	ldr r3, _0223B66C ; =0x00007FFF
	add r1, r0, #0
	add r2, r0, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0223B662
_0223B654:
	bl FUN_0200E308
	cmp r0, #0
	beq _0223B662
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_0223B662:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_0223B668: .word 0x000006AB
_0223B66C: .word 0x00007FFF
	thumb_func_end MOD81_0223B5BC

	thumb_func_start MOD81_0223B670
MOD81_0223B670: ; 0x0223B670
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r0, _0223B7C0 ; =0x0223D258
	bl GX_SetBanks
	ldr r2, _0223B7C4 ; =0x04000304
	ldrh r1, [r2]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2]
	ldr r0, _0223B7C8 ; =0x0223D21C
	bl FUN_02016BBC
	ldr r0, [r4, #0x24]
	ldr r2, _0223B7CC ; =0x0223D23C
	mov r1, #3
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x24]
	ldr r2, _0223B7CC ; =0x0223D23C
	mov r1, #7
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4]
	bl MOD81_02238828
	cmp r0, #3
	bhi _0223B6C2
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223B6BA: ; jump table
	.short _0223B6C2 - _0223B6BA - 2 ; case 0
	.short _0223B6CE - _0223B6BA - 2 ; case 1
	.short _0223B6DA - _0223B6BA - 2 ; case 2
	.short _0223B6E6 - _0223B6BA - 2 ; case 3
_0223B6C2:
	mov r0, #0xf
	str r0, [sp, #0x10]
	mov r7, #0x10
	mov r6, #0x11
	mov r5, #0
	b _0223B6F0
_0223B6CE:
	mov r0, #0xf
	str r0, [sp, #0x10]
	mov r7, #0x10
	mov r6, #0x11
	mov r5, #0x20
	b _0223B6F0
_0223B6DA:
	mov r0, #0xf
	str r0, [sp, #0x10]
	mov r7, #0x10
	mov r6, #0x11
	mov r5, #0x40
	b _0223B6F0
_0223B6E6:
	mov r0, #0x18
	str r0, [sp, #0x10]
	mov r7, #0x19
	mov r6, #0x1a
	mov r5, #0
_0223B6F0:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x24]
	mov r0, #0x5d
	add r1, r7, #0
	mov r3, #3
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x24]
	mov r0, #0x5d
	add r1, r7, #0
	mov r3, #7
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r2, [r4, #0x24]
	mov r0, #0x5d
	mov r3, #3
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r2, [r4, #0x24]
	mov r0, #0x5d
	mov r3, #7
	bl GfGfxLoader_LoadScrnData
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0x5d
	add r1, r6, #0
	add r3, r5, #0
	bl GfGfxLoader_GXLoadPalWithSrcOffset
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0x5d
	add r1, r6, #0
	mov r2, #4
	add r3, r5, #0
	bl GfGfxLoader_GXLoadPalWithSrcOffset
	mov r1, #3
	ldr r0, [r4, #0x24]
	add r2, r1, #0
	mov r3, #0
	bl FUN_020179E0
	mov r2, #3
	add r3, r2, #0
	ldr r0, [r4, #0x24]
	mov r1, #7
	add r3, #0xfd
	bl FUN_020179E0
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	bl FUN_02033E74
	mov r0, #1
	mov r1, #0x39
	bl FUN_02033F04
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223B7C0: .word MOD81_0223D258
_0223B7C4: .word 0x04000304
_0223B7C8: .word MOD81_0223D21C
_0223B7CC: .word MOD81_0223D23C
	thumb_func_end MOD81_0223B670

	thumb_func_start MOD81_0223B7D0
MOD81_0223B7D0: ; 0x0223B7D0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x24]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #0x24]
	mov r1, #7
	bl FUN_020178A0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223B7D0

	thumb_func_start MOD81_0223B7E8
MOD81_0223B7E8: ; 0x0223B7E8
	push {r3, r4, lr}
	sub sp, #0x24
	add r4, r0, #0
	bl NNS_G3dInit
	bl G3X_InitMtxStack
	ldr r0, _0223B8C8 ; =0x04000060
	ldr r1, _0223B8CC ; =0xFFFFCFFD
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
	ldr r2, _0223B8D0 ; =0x0000CFFB
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
	ldr r0, _0223B8D4 ; =0x0223D22C
	bl G3X_SetEdgeColorTable
	mov r1, #0
	ldr r0, _0223B8D8 ; =0x000043FF
	ldr r2, _0223B8DC ; =0x00007FFF
	mov r3, #0x3f
	str r1, [sp]
	bl G3X_SetClearColor
	ldr r1, _0223B8E0 ; =0x04000540
	mov r0, #2
	str r0, [r1]
	ldr r0, _0223B8E4 ; =0xBFFF0000
	str r0, [r1, #0x40]
	mov r0, #1
	add r1, r0, #0
	bl NNS_GfdInitFrmTexVramManager
	mov r0, #1
	lsl r0, r0, #0xe
	mov r1, #1
	bl NNS_GfdInitFrmPlttVramManager
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r1, _0223B8E8 ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	strh r2, [r1]
	mov r1, #0
	mov r0, #1
	add r2, r1, #0
	add r3, r1, #0
	bl MOD81_022388C0
	str r0, [r4, #0x28]
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r4, #0x28]
	mov r2, #0x5d
	mov r3, #0x1b
	bl MOD81_02238A84
	ldr r1, _0223B8EC ; =0x000018E3
	str r0, [r4, #0x2c]
	add r0, sp, #0x10
	strh r1, [r0]
	mov r1, #0
	strh r1, [r0, #2]
	strh r1, [r0, #4]
	ldr r0, [r4, #0x28]
	add r1, sp, #0x10
	bl MOD81_02238C60
	ldr r1, _0223B8F0 ; =0x00001150
	add r0, sp, #0x10
	strh r1, [r0]
	ldr r0, [r4, #0x28]
	add r1, sp, #0x10
	bl MOD81_02238C70
	ldr r0, [r4, #0x28]
	ldr r1, _0223B8F4 ; =0x000007D2
	bl MOD81_02238C90
	ldr r0, [r4, #0x28]
	add r1, sp, #0x18
	bl MOD81_02238C40
	add sp, #0x24
	pop {r3, r4, pc}
	.align 2, 0
_0223B8C8: .word 0x04000060
_0223B8CC: .word 0xFFFFCFFD
_0223B8D0: .word 0x0000CFFB
_0223B8D4: .word MOD81_0223D22C
_0223B8D8: .word 0x000043FF
_0223B8DC: .word 0x00007FFF
_0223B8E0: .word 0x04000540
_0223B8E4: .word 0xBFFF0000
_0223B8E8: .word 0x04000008
_0223B8EC: .word 0x000018E3
_0223B8F0: .word 0x00001150
_0223B8F4: .word 0x000007D2
	thumb_func_end MOD81_0223B7E8

	thumb_func_start MOD81_0223B8F8
MOD81_0223B8F8: ; 0x0223B8F8
	push {r3, lr}
	ldr r0, [r0, #0x28]
	cmp r0, #0
	beq _0223B904
	bl MOD81_0223890C
_0223B904:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD81_0223B8F8

	thumb_func_start MOD81_0223B908
MOD81_0223B908: ; 0x0223B908
	push {r4, lr}
	sub sp, #0x70
	add r4, r0, #0
	add r0, #0x10
	mov r1, #0x5d
	mov r2, #7
	mov r3, #8
	bl MOD81_0223874C
	add r0, sp, #0x5c
	bl NNS_G2dInitImagePaletteProxy
	add r0, sp, #0x38
	bl NNS_G2dInitImageProxy
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	add r0, sp, #0x38
	str r0, [sp, #0x10]
	mov r0, #0x5d
	mov r1, #9
	bl GfGfxLoader_LoadImageMapping
	mov r0, #0x3a
	str r0, [sp]
	add r0, sp, #0x5c
	str r0, [sp, #4]
	mov r0, #0x5d
	mov r1, #0xa
	mov r2, #1
	mov r3, #0
	bl GfGfxLoader_PartiallyLoadPalette
	mov r0, #1
	add r1, r4, #0
	str r0, [sp]
	add r0, sp, #0x14
	add r1, #0x10
	add r2, sp, #0x38
	add r3, sp, #0x5c
	bl MOD81_022387A8
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #0x14
	mov r2, #0x80
	mov r3, #0x60
	bl MOD81_022387C8
	mov r1, #0
	str r0, [r4, #0x20]
	bl FUN_020200A0
	add sp, #0x70
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223B908

	thumb_func_start MOD81_0223B988
MOD81_0223B988: ; 0x0223B988
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _0223B996
	bl FUN_0201FFC8
_0223B996:
	add r4, #0x10
	add r0, r4, #0
	bl MOD81_02238784
	pop {r4, pc}
	thumb_func_end MOD81_0223B988

	thumb_func_start MOD81_0223B9A0
MOD81_0223B9A0: ; 0x0223B9A0
	mov r1, #0
	str r1, [r0, #4]
	bx lr
	.align 2, 0
	thumb_func_end MOD81_0223B9A0

	thumb_func_start MOD81_0223B9A8
MOD81_0223B9A8: ; 0x0223B9A8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _0223B9BA
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #4]
_0223B9BA:
	pop {r4, pc}
	thumb_func_end MOD81_0223B9A8

	thumb_func_start MOD81_0223B9BC
MOD81_0223B9BC: ; 0x0223B9BC
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	str r0, [r4]
	ldr r1, [r0, #0x2c]
	ldr r2, _0223BA5C ; =0xFFFFD870
	str r1, [r4, #0xc]
	ldr r0, [r0, #0x28]
	ldr r1, _0223BA60 ; =0x003D6C00
	str r0, [r4, #8]
	mov r0, #0
	str r0, [r4, #0x10]
	str r1, [r4, #0x14]
	ldr r1, _0223BA64 ; =0xFFE44000
	str r1, [r4, #0x18]
	add r1, r4, #0
	add r1, #0x78
	strh r2, [r1]
	add r1, r4, #0
	ldr r2, _0223BA68 ; =0xFFFFF550
	add r1, #0x7a
	strh r2, [r1]
	ldr r1, _0223BA6C ; =0xFFFEF2C6
	str r1, [r4, #0x3c]
	ldr r1, _0223BA70 ; =0x0000936D
	str r1, [r4, #0x40]
	str r0, [r4, #0x6c]
	str r0, [r4, #0x70]
	mov r1, #2
	str r0, [r4, #0x74]
	lsl r1, r1, #0xc
	strh r1, [r4, #0x34]
	ldr r1, _0223BA74 ; =0xFFFFE000
	strh r1, [r4, #0x36]
	strh r0, [r4, #0x38]
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x34
	bl MOD81_02238B40
	mov r3, #2
	lsl r3, r3, #8
	mov r1, #0x4a
	mov r2, #0x63
	str r3, [r4, #0x5c]
	lsl r0, r3, #2
	str r0, [r4, #0x44]
	str r0, [r4, #0x48]
	mov r0, #0
	str r0, [r4, #0x68]
	mov r0, #0xc
	str r0, [sp]
	add r0, r4, #0
	lsl r1, r1, #0xa
	lsl r2, r2, #0xa
	lsl r3, r3, #3
	bl MOD81_0223BA8C
	add r0, r4, #0
	bl MOD81_0223BAD0
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x28
	bl MOD81_02238B18
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x34
	bl MOD81_02238B28
	ldr r0, _0223BA78 ; =MOD81_0223BBC8
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	str r0, [r4, #4]
	add sp, #4
	pop {r3, r4, pc}
	nop
_0223BA5C: .word 0xFFFFD870
_0223BA60: .word 0x003D6C00
_0223BA64: .word 0xFFE44000
_0223BA68: .word 0xFFFFF550
_0223BA6C: .word 0xFFFEF2C6
_0223BA70: .word 0x0000936D
_0223BA74: .word 0xFFFFE000
_0223BA78: .word MOD81_0223BBC8
	thumb_func_end MOD81_0223B9BC

	thumb_func_start MOD81_0223BA7C
MOD81_0223BA7C: ; 0x0223BA7C
	ldr r0, [r0, #4]
	cmp r0, #0
	bne _0223BA86
	mov r0, #1
	bx lr
_0223BA86:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD81_0223BA7C

	thumb_func_start MOD81_0223BA8C
MOD81_0223BA8C: ; 0x0223BA8C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [sp, #0x18]
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	str r0, [sp]
	cmp r0, #0
	beq _0223BACC
	ldr r0, [r5, #0x44]
	ldr r1, [sp]
	sub r0, r4, r0
	bl _s32_div_f
	str r0, [r5, #0x4c]
	ldr r0, [r5, #0x48]
	ldr r1, [sp]
	sub r0, r6, r0
	bl _s32_div_f
	str r0, [r5, #0x50]
	ldr r0, [r5, #0x5c]
	ldr r1, [sp]
	sub r0, r7, r0
	bl _s32_div_f
	str r0, [r5, #0x60]
	str r4, [r5, #0x54]
	str r6, [r5, #0x58]
	ldr r0, [sp, #0x18]
	str r7, [r5, #0x64]
	str r0, [r5, #0x68]
_0223BACC:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD81_0223BA8C

	thumb_func_start MOD81_0223BAD0
MOD81_0223BAD0: ; 0x0223BAD0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _0223BBC0 ; =0x0223D3A0
	ldr r0, [r0]
	cmp r0, #0
	beq _0223BBAE
	add r0, r5, #0
	add r0, #0x78
	ldrh r0, [r0]
	mov r1, #0xb6
	bl _s32_div_f
	add r4, r0, #0
	mov r0, #0x5a
	lsl r0, r0, #2
	cmp r4, r0
	blt _0223BAF4
	sub r4, r4, r0
_0223BAF4:
	mov r0, #0x78
	ldrsh r1, [r5, r0]
	mov r0, #0x7a
	ldrsh r0, [r5, r0]
	sub r1, r1, r0
	add r0, r5, #0
	add r0, #0x78
	strh r1, [r0]
	ldr r0, [r5, #0x68]
	cmp r0, #0
	beq _0223BB3C
	sub r0, r0, #1
	str r0, [r5, #0x68]
	beq _0223BB28
	ldr r1, [r5, #0x44]
	ldr r0, [r5, #0x4c]
	add r0, r1, r0
	str r0, [r5, #0x44]
	ldr r1, [r5, #0x48]
	ldr r0, [r5, #0x50]
	add r0, r1, r0
	str r0, [r5, #0x48]
	ldr r1, [r5, #0x5c]
	ldr r0, [r5, #0x60]
	add r0, r1, r0
	b _0223BB32
_0223BB28:
	ldr r0, [r5, #0x54]
	str r0, [r5, #0x44]
	ldr r0, [r5, #0x58]
	str r0, [r5, #0x48]
	ldr r0, [r5, #0x64]
_0223BB32:
	str r0, [r5, #0x5c]
	ldr r0, [r5, #0xc]
	ldr r1, [r5, #0x5c]
	bl MOD81_02238B84
_0223BB3C:
	add r0, r4, #0
	add r0, #0x5a
	lsl r1, r0, #2
	ldr r0, _0223BBC4 ; =gSineTable
	ldr r2, [r5, #0x44]
	ldr r0, [r0, r1]
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
	str r1, [r5, #0x1c]
	ldr r2, [r5, #0x48]
	ldr r0, _0223BBC4 ; =gSineTable
	lsl r1, r4, #2
	ldr r0, [r0, r1]
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
	str r1, [r5, #0x20]
	add r1, r5, #0
	str r3, [r5, #0x24]
	mov r0, #0x34
	ldrsh r2, [r5, r0]
	mov r0, #3
	lsl r0, r0, #8
	sub r0, r2, r0
	strh r0, [r5, #0x34]
	ldr r0, [r5, #0xc]
	add r1, #0x34
	bl MOD81_02238B40
	add r0, r5, #0
	add r1, r5, #0
	add r5, #0x28
	add r0, #0x1c
	add r1, #0x10
	add r2, r5, #0
	bl VEC_Add
	pop {r3, r4, r5, pc}
_0223BBAE:
	add r2, r5, #0
	add r2, #0x10
	ldmia r2!, {r0, r1}
	add r5, #0x28
	stmia r5!, {r0, r1}
	ldr r0, [r2]
	str r0, [r5]
	pop {r3, r4, r5, pc}
	nop
_0223BBC0: .word MOD81_0223D3A0
_0223BBC4: .word gSineTable
	thumb_func_end MOD81_0223BAD0

	thumb_func_start MOD81_0223BBC8
MOD81_0223BBC8: ; 0x0223BBC8
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4, #0x74]
	cmp r1, #0x46
	bge _0223BBD6
	add r1, r1, #1
	str r1, [r4, #0x74]
_0223BBD6:
	ldr r1, [r4, #0x6c]
	cmp r1, #3
	bhi _0223BC9C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223BBE8: ; jump table
	.short _0223BBF0 - _0223BBE8 - 2 ; case 0
	.short _0223BC16 - _0223BBE8 - 2 ; case 1
	.short _0223BC50 - _0223BBE8 - 2 ; case 2
	.short _0223BC8A - _0223BBE8 - 2 ; case 3
_0223BBF0:
	add r0, r4, #0
	bl MOD81_0223BAD0
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x28
	bl MOD81_02238B18
	ldr r0, [r4, #0x74]
	add r0, r0, #1
	str r0, [r4, #0x74]
	cmp r0, #0xc
	blt _0223BC9C
	mov r0, #0
	str r0, [r4, #0x74]
	ldr r0, [r4, #0x6c]
	add r0, r0, #1
	str r0, [r4, #0x6c]
	pop {r4, pc}
_0223BC16:
	ldr r0, [r4, #0xc]
	bl MOD81_02238B8C
	cmp r0, #0
	bne _0223BC2E
	ldr r0, [r4]
	bl MOD81_0223BCA0
	ldr r0, [r4, #0x6c]
	add r0, r0, #1
	str r0, [r4, #0x6c]
	pop {r4, pc}
_0223BC2E:
	ldr r1, [r4, #0x14]
	ldr r0, [r4, #0x3c]
	add r0, r1, r0
	str r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	ldr r0, [r4, #0x40]
	add r0, r1, r0
	str r0, [r4, #0x18]
	add r0, r4, #0
	bl MOD81_0223BAD0
	ldr r0, [r4, #0xc]
	add r4, #0x28
	add r1, r4, #0
	bl MOD81_02238B18
	pop {r4, pc}
_0223BC50:
	ldr r1, [r4, #0x14]
	ldr r0, [r4, #0x3c]
	add r0, r1, r0
	str r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	ldr r0, [r4, #0x40]
	add r0, r1, r0
	str r0, [r4, #0x18]
	add r0, r4, #0
	bl MOD81_0223BAD0
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x28
	bl MOD81_02238B18
	ldr r0, [r4, #0x74]
	cmp r0, #0x46
	blt _0223BC9C
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl MOD81_02238B58
	mov r0, #0
	str r0, [r4, #0x70]
	ldr r0, [r4, #0x6c]
	add r0, r0, #1
	str r0, [r4, #0x6c]
	pop {r4, pc}
_0223BC8A:
	ldr r1, [r4, #0x70]
	add r1, r1, #1
	str r1, [r4, #0x70]
	cmp r1, #8
	ble _0223BC9C
	mov r1, #0
	str r1, [r4, #4]
	bl FUN_0200CAB4
_0223BC9C:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223BBC8

	thumb_func_start MOD81_0223BCA0
MOD81_0223BCA0: ; 0x0223BCA0
	mov r1, #1
	str r1, [r0, #0xc]
	bx lr
	.align 2, 0
	thumb_func_end MOD81_0223BCA0

	thumb_func_start MOD81_0223BCA8
MOD81_0223BCA8: ; 0x0223BCA8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _0223BCC6
	bl G3X_ResetMtxStack
	ldr r0, [r4, #0x28]
	bl MOD81_02238940
	mov r0, #0
	add r1, r0, #0
	bl FUN_020222B4
_0223BCC6:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _0223BD08
	ldr r1, _0223BD0C ; =0x0000EEB0
	add r0, sp, #0
	strh r1, [r0]
	mov r1, #0
	strh r1, [r0, #2]
	strh r1, [r0, #4]
	mov r1, #3
	add r3, r1, #0
	ldr r0, [r4, #0x24]
	add r2, r1, #0
	add r3, #0xfd
	bl FUN_020179E0
	ldr r0, [r4, #0x24]
	mov r1, #7
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	ldr r0, [r4, #0x28]
	add r1, sp, #0
	bl MOD81_02238C70
	ldr r2, _0223BD10 ; =0x04000304
	ldr r0, _0223BD14 ; =0xFFFF7FFF
	ldrh r1, [r2]
	and r0, r1
	strh r0, [r2]
	mov r0, #0
	str r0, [r4, #0xc]
_0223BD08:
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_0223BD0C: .word 0x0000EEB0
_0223BD10: .word 0x04000304
_0223BD14: .word 0xFFFF7FFF
	thumb_func_end MOD81_0223BCA8

	thumb_func_start MOD81_0223BD18
MOD81_0223BD18: ; 0x0223BD18
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x3a
	mov r1, #0x3c
	bl AllocFromHeap
	add r4, r0, #0
	beq _0223BD46
	str r5, [r4]
	mov r0, #0
	str r0, [r4, #4]
	add r0, r5, #0
	bl MOD81_0223880C
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4, #0x20]
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	str r0, [r4, #0x30]
	str r0, [r4, #0x34]
	str r0, [r4, #0x38]
_0223BD46:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD81_0223BD18

	thumb_func_start MOD81_0223BD4C
MOD81_0223BD4C: ; 0x0223BD4C
	push {r4, lr}
	add r4, r0, #0
	beq _0223BD80
	bl MOD81_0223C1A8
	add r0, r4, #0
	bl MOD81_0223C2EC
	ldr r0, [r4, #0x30]
	cmp r0, #0
	beq _0223BD66
	bl MOD81_0223C460
_0223BD66:
	ldr r0, [r4, #0x34]
	cmp r0, #0
	beq _0223BD70
	bl MOD81_0223C3B0
_0223BD70:
	ldr r0, [r4, #0x38]
	cmp r0, #0
	beq _0223BD7A
	bl MOD81_0223C514
_0223BD7A:
	add r0, r4, #0
	bl FreeToHeap
_0223BD80:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223BD4C

	thumb_func_start MOD81_0223BD84
MOD81_0223BD84: ; 0x0223BD84
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r2, [r4]
	add r5, r0, #0
	cmp r2, #3
	bhs _0223BDB2
	lsl r3, r2, #2
	ldr r2, _0223BDB8 ; =0x0223D288
	add r1, r5, #4
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #0
	beq _0223BDA8
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	str r0, [r5, #4]
_0223BDA8:
	add r0, r5, #0
	bl MOD81_0223BDBC
	mov r0, #0
	pop {r3, r4, r5, pc}
_0223BDB2:
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_0223BDB8: .word MOD81_0223D288
	thumb_func_end MOD81_0223BD84

	thumb_func_start MOD81_0223BDBC
MOD81_0223BDBC: ; 0x0223BDBC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _0223BDEE
	mov r0, #0x2a
	ldrsh r1, [r4, r0]
	mov r0, #1
	lsl r0, r0, #0xc
	add r0, r1, r0
	strh r0, [r4, #0x2a]
	add r1, r4, #0
	ldr r0, [r4, #0x24]
	add r1, #0x28
	bl MOD81_02238B40
	bl G3X_ResetMtxStack
	ldr r0, [r4, #0x20]
	bl MOD81_02238940
	mov r0, #0
	add r1, r0, #0
	bl FUN_020222B4
_0223BDEE:
	pop {r4, pc}
	thumb_func_end MOD81_0223BDBC

	thumb_func_start MOD81_0223BDF0
MOD81_0223BDF0: ; 0x0223BDF0
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD81_0223BF74
	add r0, r4, #0
	bl MOD81_0223C1DC
	mov r0, #8
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	ldr r3, _0223BE1C ; =0x00007FFF
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200E1D0
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_0223BE1C: .word 0x00007FFF
	thumb_func_end MOD81_0223BDF0

	thumb_func_start MOD81_0223BE20
MOD81_0223BE20: ; 0x0223BE20
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #6
	bhi _0223BEEA
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0223BE38: ; jump table
	.short _0223BE46 - _0223BE38 - 2 ; case 0
	.short _0223BE64 - _0223BE38 - 2 ; case 1
	.short _0223BE7E - _0223BE38 - 2 ; case 2
	.short _0223BE90 - _0223BE38 - 2 ; case 3
	.short _0223BEA8 - _0223BE38 - 2 ; case 4
	.short _0223BECC - _0223BE38 - 2 ; case 5
	.short _0223BEE0 - _0223BE38 - 2 ; case 6
_0223BE46:
	bl FUN_0200E308
	cmp r0, #0
	beq _0223BEEA
	mov r0, #0
	str r0, [r4, #8]
	add r0, r4, #0
	add r4, #0x30
	add r1, r4, #0
	bl MOD81_0223C3CC
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0223BEEA
_0223BE64:
	ldr r1, [r4, #8]
	add r1, r1, #1
	str r1, [r4, #8]
	cmp r1, #8
	ble _0223BEEA
	add r4, #0x34
	add r1, r4, #0
	bl MOD81_0223C300
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0223BEEA
_0223BE7E:
	ldr r0, [r4, #0x34]
	cmp r0, #0
	bne _0223BEEA
	ldr r0, [r4, #0x30]
	cmp r0, #0
	bne _0223BEEA
	add r0, r1, #1
	str r0, [r5]
	b _0223BEEA
_0223BE90:
	mov r1, #0
	add r0, #0x14
	mvn r1, r1
	bl MOD81_02238118
	str r0, [r4, #0x10]
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0223BEEA
_0223BEA8:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0x1e
	ble _0223BEEA
	add r0, r4, #0
	add r0, #0x38
	str r0, [sp]
	ldr r0, [r4, #0x24]
	mov r1, #0x1f
	mov r2, #0
	mov r3, #0x28
	bl MOD81_0223C47C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0223BEEA
_0223BECC:
	ldr r0, [r4, #0x38]
	cmp r0, #0
	bne _0223BEEA
	ldr r0, [r4, #0x10]
	bl MOD81_022381EC
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0223BEEA
_0223BEE0:
	ldr r0, [r4, #0x14]
	cmp r0, #0
	bne _0223BEEA
	mov r0, #1
	pop {r3, r4, r5, pc}
_0223BEEA:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD81_0223BE20

	thumb_func_start MOD81_0223BEF0
MOD81_0223BEF0: ; 0x0223BEF0
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _0223BF08
	cmp r0, #1
	beq _0223BF30
	cmp r0, #2
	beq _0223BF5A
	b _0223BF6E
_0223BF08:
	mov r0, #0x4a
	lsl r0, r0, #2
	mov r3, #1
	str r0, [sp]
	add r0, r5, #0
	str r3, [sp, #4]
	add r0, #0x1c
	str r0, [sp, #8]
	ldr r0, [r5, #0xc]
	lsl r1, r3, #0xc
	lsl r2, r3, #0xa
	bl MOD81_022384AC
	str r0, [r5, #0x18]
	mov r0, #0
	str r0, [r5, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0223BF6E
_0223BF30:
	ldr r0, [r5, #8]
	add r0, r0, #1
	str r0, [r5, #8]
	cmp r0, #0xd
	ble _0223BF6E
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0223BF6E
_0223BF5A:
	bl FUN_0200E308
	cmp r0, #0
	beq _0223BF6E
	ldr r0, [r5, #0x1c]
	cmp r0, #0
	beq _0223BF6E
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_0223BF6E:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	thumb_func_end MOD81_0223BEF0

	thumb_func_start MOD81_0223BF74
MOD81_0223BF74: ; 0x0223BF74
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, _0223C18C ; =0x0223D2EC
	bl GX_SetBanks
	ldr r2, _0223C190 ; =0x04000304
	ldrh r1, [r2]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2]
	ldr r0, _0223C194 ; =0x0223D294
	bl FUN_02016BBC
	ldr r0, [r4, #0xc]
	ldr r2, _0223C198 ; =0x0223D2B4
	mov r1, #2
	mov r3, #1
	bl FUN_02016C18
	ldr r0, [r4, #0xc]
	ldr r2, _0223C198 ; =0x0223D2B4
	mov r1, #6
	mov r3, #1
	bl FUN_02016C18
	bl OS_DisableInterrupts
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	ldr r2, _0223C19C ; =0x0223D2D0
	mov r1, #3
	mov r3, #2
	bl FUN_02016C18
	ldr r0, [r4, #0xc]
	ldr r2, _0223C19C ; =0x0223D2D0
	mov r1, #7
	mov r3, #2
	bl FUN_02016C18
	add r0, r5, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	mov r1, #2
	ldr r2, [r4, #0xc]
	mov r0, #0x5d
	add r3, r1, #0
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x5d
	mov r1, #2
	mov r3, #6
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x5d
	mov r3, #2
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x5d
	mov r3, #6
	bl GfGfxLoader_LoadScrnData
	ldr r0, [r4]
	bl MOD81_02238828
	add r5, r0, #0
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x3a
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x5d
	mov r1, #3
	add r3, r2, #0
	bl GfGfxLoader_GXLoadPal
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x3a
	str r0, [sp, #4]
	mov r0, #0x5d
	mov r1, #3
	mov r2, #4
	mov r3, #0
	bl GfGfxLoader_GXLoadPal
	ldr r0, _0223C1A0 ; =0x0223D280
	lsl r1, r5, #1
	ldrh r5, [r0, r1]
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x40
	str r0, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0x5d
	mov r1, #3
	mov r2, #0
	add r3, r5, #0
	bl GfGfxLoader_GXLoadPalWithSrcOffset
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x40
	str r0, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #0x5d
	mov r1, #3
	mov r2, #4
	add r3, r5, #0
	bl GfGfxLoader_GXLoadPalWithSrcOffset
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x5d
	mov r1, #5
	mov r3, #3
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x5d
	mov r1, #5
	mov r3, #7
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x5d
	mov r1, #4
	mov r3, #3
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x5d
	mov r1, #4
	mov r3, #7
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x3a
	mov r1, #0x60
	bl AllocFromHeap
	add r5, r0, #0
	beq _0223C14A
	mov r0, #0
	add r1, r5, #0
	mov r2, #0x60
	bl MIi_CpuClear32
	add r0, r5, #0
	mov r1, #0x60
	bl DC_FlushRange
	bl GX_BeginLoadBGExtPltt
	bl GXS_BeginLoadBGExtPltt
	mov r1, #6
	add r0, r5, #0
	lsl r1, r1, #0xc
	mov r2, #0x60
	bl GX_LoadBGExtPltt
	mov r1, #6
	add r0, r5, #0
	lsl r1, r1, #0xc
	mov r2, #0x60
	bl GXS_LoadBGExtPltt
	bl GX_EndLoadBGExtPltt
	bl GXS_EndLoadBGExtPltt
	add r0, r5, #0
	bl FreeToHeap
_0223C14A:
	ldr r0, [r4, #0xc]
	ldr r3, _0223C1A4 ; =0xFFFFFE80
	mov r1, #2
	mov r2, #3
	bl FUN_020179E0
	mov r2, #3
	add r3, r2, #0
	ldr r0, [r4, #0xc]
	mov r1, #6
	sub r3, #0xc3
	bl FUN_020179E0
	mov r1, #3
	ldr r0, [r4, #0xc]
	add r2, r1, #0
	mov r3, #0x43
	bl FUN_020179E0
	mov r0, #7
	mov r1, #0
	bl FUN_0201797C
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223C18C: .word MOD81_0223D2EC
_0223C190: .word 0x04000304
_0223C194: .word MOD81_0223D294
_0223C198: .word MOD81_0223D2B4
_0223C19C: .word MOD81_0223D2D0
_0223C1A0: .word MOD81_0223D280
_0223C1A4: .word 0xFFFFFE80
	thumb_func_end MOD81_0223BF74

	thumb_func_start MOD81_0223C1A8
MOD81_0223C1A8: ; 0x0223C1A8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _0223C1B8
	ldr r0, [r4, #0x10]
	bl MOD81_02238200
_0223C1B8:
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
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223C1A8

	thumb_func_start MOD81_0223C1DC
MOD81_0223C1DC: ; 0x0223C1DC
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	bl NNS_G3dInit
	bl G3X_InitMtxStack
	ldr r0, _0223C2C0 ; =0x04000060
	ldr r1, _0223C2C4 ; =0xFFFFCFFD
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
	ldr r2, _0223C2C8 ; =0x0000CFFB
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
	ldr r0, _0223C2CC ; =0x0223D2A4
	bl G3X_SetEdgeColorTable
	mov r1, #0
	ldr r0, _0223C2D0 ; =0x000043FF
	ldr r2, _0223C2D4 ; =0x00007FFF
	mov r3, #0x3f
	str r1, [sp]
	bl G3X_SetClearColor
	ldr r1, _0223C2D8 ; =0x04000540
	mov r0, #2
	str r0, [r1]
	ldr r0, _0223C2DC ; =0xBFFF0000
	str r0, [r1, #0x40]
	mov r0, #1
	add r1, r0, #0
	bl NNS_GfdInitFrmTexVramManager
	mov r0, #1
	lsl r0, r0, #0xe
	mov r1, #1
	bl NNS_GfdInitFrmPlttVramManager
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r1, _0223C2E0 ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	strh r2, [r1]
	mov r1, #0
	mov r0, #1
	add r2, r1, #0
	add r3, r1, #0
	bl MOD81_022388C0
	str r0, [r4, #0x20]
	mov r1, #0
	mov r0, #0x23
	str r1, [sp]
	lsl r0, r0, #0xe
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x20]
	mov r2, #0x5d
	mov r3, #0x1b
	bl MOD81_02238A84
	str r0, [r4, #0x24]
	ldr r0, _0223C2E4 ; =0x0223D450
	mov r1, #0
	strh r1, [r0]
	strh r1, [r0, #2]
	strh r1, [r0, #4]
	ldr r0, [r4, #0x20]
	ldr r1, _0223C2E8 ; =0x0223D450
	bl MOD81_02238C60
	ldr r0, [r4, #0x20]
	mov r1, #1
	bl MOD81_02238C80
	mov r1, #2
	ldr r0, [r4, #0x24]
	lsl r1, r1, #0xc
	bl MOD81_02238B84
	ldr r0, [r4, #0x24]
	add r4, #0x28
	add r1, r4, #0
	bl MOD81_02238B28
	add sp, #0x10
	pop {r4, pc}
	nop
_0223C2C0: .word 0x04000060
_0223C2C4: .word 0xFFFFCFFD
_0223C2C8: .word 0x0000CFFB
_0223C2CC: .word MOD81_0223D2A4
_0223C2D0: .word 0x000043FF
_0223C2D4: .word 0x00007FFF
_0223C2D8: .word 0x04000540
_0223C2DC: .word 0xBFFF0000
_0223C2E0: .word 0x04000008
_0223C2E4: .word MOD81_0223D450
_0223C2E8: .word MOD81_0223D450
	thumb_func_end MOD81_0223C1DC

	thumb_func_start MOD81_0223C2EC
MOD81_0223C2EC: ; 0x0223C2EC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _0223C2FE
	bl MOD81_0223890C
	mov r0, #0
	str r0, [r4, #0x20]
_0223C2FE:
	pop {r4, pc}
	thumb_func_end MOD81_0223C2EC

	thumb_func_start MOD81_0223C300
MOD81_0223C300: ; 0x0223C300
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #0x3a
	mov r1, #0x24
	bl AllocFromHeap
	add r4, r0, #0
	beq _0223C340
	str r6, [r4]
	ldr r0, [r6, #0xc]
	add r1, r4, #0
	str r0, [r4, #4]
	ldr r0, _0223C344 ; =0xFFE80000
	mov r2, #0
	str r0, [r4, #0xc]
	asr r0, r0, #1
	str r0, [r4, #0x10]
	ldr r0, _0223C348 ; =0x00009999
	str r0, [r4, #0x14]
	mov r0, #0x28
	str r0, [r4, #8]
	ldr r0, _0223C34C ; =MOD81_0223C350
	str r5, [r4, #0x1c]
	bl FUN_0200CA60
	str r0, [r5]
	cmp r0, #0
	bne _0223C340
	add r0, r4, #0
	bl FreeToHeap
_0223C340:
	pop {r4, r5, r6, pc}
	nop
_0223C344: .word 0xFFE80000
_0223C348: .word 0x00009999
_0223C34C: .word MOD81_0223C350
	thumb_func_end MOD81_0223C300

	thumb_func_start MOD81_0223C350
MOD81_0223C350: ; 0x0223C350
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _0223C390
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x14]
	mov r2, #3
	add r0, r1, r0
	str r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x14]
	add r0, r1, r0
	str r0, [r4, #0x10]
	ldr r3, [r4, #0xc]
	ldr r0, [r4, #4]
	mov r1, #2
	asr r3, r3, #0xc
	bl FUN_020179E0
	ldr r3, [r4, #0x10]
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #3
	asr r3, r3, #0xc
	bl FUN_020179E0
	ldr r0, [r4, #8]
	sub r0, r0, #1
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
_0223C390:
	ldr r0, [r4, #4]
	mov r1, #2
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #3
	mov r3, #0xc0
	bl FUN_020179E0
	add r0, r5, #0
	bl MOD81_0223C3B0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD81_0223C350

	thumb_func_start MOD81_0223C3B0
MOD81_0223C3B0: ; 0x0223C3B0
	push {r4, lr}
	add r4, r0, #0
	beq _0223C3CA
	bl FUN_0201B6C8
	ldr r1, [r0, #0x1c]
	mov r2, #0
	str r2, [r1]
	bl MOD81_02238898
	add r0, r4, #0
	bl FUN_0200CAB4
_0223C3CA:
	pop {r4, pc}
	thumb_func_end MOD81_0223C3B0

	thumb_func_start MOD81_0223C3CC
MOD81_0223C3CC: ; 0x0223C3CC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #0x3a
	mov r1, #0x1c
	bl AllocFromHeap
	add r4, r0, #0
	beq _0223C418
	str r5, [r4]
	ldr r0, [r6, #0x24]
	add r1, r4, #0
	str r0, [r4, #8]
	add r1, #0xc
	bl MOD81_02238B08
	mov r0, #0x32
	ldr r1, [r4, #0x10]
	lsl r0, r0, #0xc
	sub r1, r0, r1
	asr r0, r1, #3
	lsr r0, r0, #0x1c
	add r0, r1, r0
	asr r0, r0, #4
	str r0, [r4, #0x18]
	mov r0, #0x10
	str r0, [r4, #4]
	ldr r0, _0223C41C ; =MOD81_0223C420
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	str r0, [r5]
	cmp r0, #0
	bne _0223C418
	add r0, r4, #0
	bl FreeToHeap
_0223C418:
	pop {r4, r5, r6, pc}
	nop
_0223C41C: .word MOD81_0223C420
	thumb_func_end MOD81_0223C3CC

	thumb_func_start MOD81_0223C420
MOD81_0223C420: ; 0x0223C420
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _0223C446
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x18]
	add r0, r1, r0
	str r0, [r4, #0x10]
	add r1, r4, #0
	ldr r0, [r4, #8]
	add r1, #0xc
	bl MOD81_02238B18
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_0223C446:
	mov r0, #0x32
	lsl r0, r0, #0xc
	str r0, [r4, #0x10]
	ldr r0, [r4, #8]
	add r4, #0xc
	add r1, r4, #0
	bl MOD81_02238B18
	add r0, r5, #0
	bl MOD81_0223C460
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD81_0223C420

	thumb_func_start MOD81_0223C460
MOD81_0223C460: ; 0x0223C460
	push {r4, lr}
	add r4, r0, #0
	beq _0223C47A
	bl FUN_0201B6C8
	ldr r1, [r0]
	mov r2, #0
	str r2, [r1]
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_0223C47A:
	pop {r4, pc}
	thumb_func_end MOD81_0223C460

	thumb_func_start MOD81_0223C47C
MOD81_0223C47C: ; 0x0223C47C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp]
	add r6, r1, #0
	mov r0, #0x3a
	mov r1, #0x18
	str r2, [sp, #4]
	add r7, r3, #0
	ldr r5, [sp, #0x20]
	bl AllocFromHeap
	add r4, r0, #0
	beq _0223C4D4
	str r5, [r4]
	lsl r0, r6, #0xc
	str r0, [r4, #4]
	ldr r0, [sp, #4]
	lsl r1, r0, #0xc
	str r1, [r4, #0xc]
	ldr r0, [r4, #4]
	sub r0, r1, r0
	add r1, r7, #0
	bl _s32_div_f
	str r0, [r4, #8]
	ldr r0, [sp]
	str r7, [r4, #0x10]
	add r1, r6, #0
	str r0, [r4, #0x14]
	bl MOD81_02238B5C
	ldr r0, _0223C4DC ; =MOD81_0223C4E0
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	str r0, [r5]
	cmp r0, #0
	bne _0223C4D8
	add r0, r4, #0
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_0223C4D4:
	mov r0, #0
	str r0, [r5]
_0223C4D8:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223C4DC: .word MOD81_0223C4E0
	thumb_func_end MOD81_0223C47C

	thumb_func_start MOD81_0223C4E0
MOD81_0223C4E0: ; 0x0223C4E0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1, #0x10]
	sub r0, r0, #1
	str r0, [r1, #0x10]
	cmp r0, #0
	ble _0223C500
	ldr r2, [r1, #4]
	ldr r0, [r1, #8]
	add r2, r2, r0
	str r2, [r1, #4]
	ldr r0, [r1, #0x14]
	asr r1, r2, #0xc
	bl MOD81_02238B5C
	pop {r4, pc}
_0223C500:
	ldr r0, [r1, #0x14]
	ldr r1, [r1, #0xc]
	asr r1, r1, #0xc
	bl MOD81_02238B5C
	add r0, r4, #0
	bl MOD81_0223C514
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223C4E0

	thumb_func_start MOD81_0223C514
MOD81_0223C514: ; 0x0223C514
	push {r4, lr}
	add r4, r0, #0
	beq _0223C52E
	bl FUN_0201B6C8
	ldr r1, [r0]
	mov r2, #0
	str r2, [r1]
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_0223C52E:
	pop {r4, pc}
	thumb_func_end MOD81_0223C514

	thumb_func_start MOD81_0223C530
MOD81_0223C530: ; 0x0223C530
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x3a
	mov r1, #0x70
	bl AllocFromHeap
	add r4, r0, #0
	beq _0223C57A
	str r5, [r4]
	mov r0, #0
	str r0, [r4, #4]
	add r0, r5, #0
	bl MOD81_0223880C
	str r0, [r4, #0x44]
	mov r0, #0x3a
	bl FUN_02006D98
	str r0, [r4, #0x10]
	mov r0, #0
	str r0, [r4, #0x14]
	mov r0, #0x4b
	lsl r0, r0, #2
	mov r1, #0x3a
	bl String_ctor
	str r0, [r4, #0x58]
	mov r0, #0x4b
	lsl r0, r0, #2
	mov r1, #0x3a
	bl String_ctor
	str r0, [r4, #0x5c]
	mov r0, #0
	str r0, [r4, #0x68]
	str r0, [r4, #0x6c]
	str r0, [r4, #0x60]
_0223C57A:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD81_0223C530

	thumb_func_start MOD81_0223C580
MOD81_0223C580: ; 0x0223C580
	push {r4, lr}
	add r4, r0, #0
	beq _0223C5D2
	bl MOD81_0223CD08
	add r0, r4, #0
	bl MOD81_0223CC84
	ldr r0, [r4, #0x6c]
	bl MOD81_0223CDE0
	ldr r0, [r4, #0x58]
	bl String_dtor
	ldr r0, [r4, #0x5c]
	bl String_dtor
	ldr r0, [r4, #0x60]
	cmp r0, #0
	beq _0223C5AC
	bl MOD81_0223890C
_0223C5AC:
	ldr r0, [r4, #0x44]
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	add r0, #0x48
	bl RemoveWindow
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _0223C5C6
	bl FUN_02007534
_0223C5C6:
	ldr r0, [r4, #0x10]
	bl FUN_020072E8
	add r0, r4, #0
	bl FreeToHeap
_0223C5D2:
	pop {r4, pc}
	thumb_func_end MOD81_0223C580

	thumb_func_start MOD81_0223C5D4
MOD81_0223C5D4: ; 0x0223C5D4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r2, [r4]
	add r5, r0, #0
	cmp r2, #4
	bhs _0223C602
	lsl r3, r2, #2
	ldr r2, _0223C608 ; =0x0223D31C
	add r1, r5, #4
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #0
	beq _0223C5F8
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	str r0, [r5, #4]
_0223C5F8:
	add r0, r5, #0
	bl MOD81_0223C60C
	mov r0, #0
	pop {r3, r4, r5, pc}
_0223C602:
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_0223C608: .word MOD81_0223D31C
	thumb_func_end MOD81_0223C5D4

	thumb_func_start MOD81_0223C60C
MOD81_0223C60C: ; 0x0223C60C
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	bl G3X_ResetMtxStack
	mov r1, #0
	mov r0, #0x11
	add r2, r1, #0
	bl NNS_G3dGeBufferOP_N
	bl NNS_G3dGeFlushBuffer
	bl NNS_G2dSetupSoftwareSpriteCamera
	ldr r0, [r4, #0x10]
	bl FUN_020081C4
	ldr r0, [r4, #0x10]
	bl FUN_02006ED4
	mov r2, #1
	str r2, [sp]
	mov r0, #0x12
	add r1, sp, #0
	bl NNS_G3dGeBufferOP_N
	ldr r0, [r4, #0x60]
	cmp r0, #0
	beq _0223C64A
	bl MOD81_02238940
_0223C64A:
	mov r0, #0
	add r1, r0, #0
	bl FUN_020222B4
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223C60C

	thumb_func_start MOD81_0223C658
MOD81_0223C658: ; 0x0223C658
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	ldr r0, _0223C808 ; =0x0223D374
	bl GX_SetBanks
	ldr r2, _0223C80C ; =0x04000304
	ldrh r1, [r2]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2]
	ldr r0, _0223C810 ; =0x0223D32C
	bl FUN_02016BBC
	ldr r0, [r4, #0x44]
	ldr r2, _0223C814 ; =0x0223D33C
	mov r1, #1
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x44]
	ldr r2, _0223C818 ; =0x0223D358
	mov r1, #2
	mov r3, #0
	bl FUN_02016C18
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r2, _0223C81C ; =0x04000008
	mov r0, #3
	ldrh r3, [r2]
	mov r1, #1
	bic r3, r0
	add r0, r3, #0
	orr r0, r1
	strh r0, [r2]
	mov r2, #0
	str r2, [sp]
	ldr r0, [r4, #0x44]
	add r3, r1, #0
	bl FUN_02017F48
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	ldr r0, [r4, #0x44]
	mov r1, #1
	add r3, r2, #0
	bl FUN_02018540
	ldr r0, [r4]
	bl MOD81_02238844
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x3a
	str r0, [sp, #4]
	ldr r0, [r4, #0x44]
	mov r1, #1
	mov r2, #0x6d
	mov r3, #2
	bl FUN_0200CD68
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	add r1, r4, #0
	str r0, [sp, #8]
	mov r2, #1
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	ldr r0, [r4, #0x44]
	add r1, #0x48
	mov r3, #2
	bl AddWindowParameterized
	add r0, r4, #0
	add r0, #0x48
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r3, #0x20
	str r3, [sp]
	mov r0, #0x3a
	str r0, [sp, #4]
	mov r0, #0xe
	mov r1, #7
	mov r2, #0
	bl GfGfxLoader_GXLoadPal
	ldr r0, [r4, #0x44]
	mov r1, #1
	bl FUN_02017CD0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x44]
	mov r0, #0x5d
	mov r1, #0x16
	mov r3, #2
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x44]
	mov r0, #0x5d
	mov r1, #0x15
	mov r3, #2
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x3a
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x5d
	mov r1, #0x17
	add r3, r2, #0
	bl GfGfxLoader_GXLoadPal
	add r0, r4, #0
	bl MOD81_0223CAC4
	mov r1, #0
	mov r0, #1
	add r2, r1, #0
	add r3, r1, #0
	bl MOD81_022388C0
	str r0, [r4, #0x60]
	add r0, r4, #0
	bl MOD81_0223CB90
	mov r1, #6
	mov r2, #1
	str r0, [r4, #0x14]
	bl FUN_02007558
	mov r1, #0
	mov r0, #0x13
	str r1, [sp]
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #0x1e
	lsl r0, r0, #0xe
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r4, #0x60]
	mov r2, #0x5d
	mov r3, #0x1b
	bl MOD81_02238A84
	ldr r2, _0223C820 ; =0x0223D314
	str r0, [r4, #0x64]
	ldrh r3, [r2]
	add r0, sp, #0x14
	add r1, sp, #0x14
	strh r3, [r0]
	ldrh r3, [r2, #2]
	ldrh r2, [r2, #4]
	strh r3, [r0, #2]
	strh r2, [r0, #4]
	ldr r0, [r4, #0x64]
	bl MOD81_02238B40
	add r0, r4, #0
	bl MOD81_0223CBE0
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	mov r0, #0
	str r0, [sp]
	ldr r0, _0223C824 ; =0x04000050
	mov r1, #1
	mov r2, #4
	mov r3, #0x10
	bl G2x_SetBlendAlpha_
	mov r0, #0x10
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	mov r0, #1
	add sp, #0x1c
	pop {r3, r4, pc}
	.align 2, 0
_0223C808: .word MOD81_0223D374
_0223C80C: .word 0x04000304
_0223C810: .word MOD81_0223D32C
_0223C814: .word MOD81_0223D33C
_0223C818: .word MOD81_0223D358
_0223C81C: .word 0x04000008
_0223C820: .word MOD81_0223D314
_0223C824: .word 0x04000050
	thumb_func_end MOD81_0223C658

	thumb_func_start MOD81_0223C828
MOD81_0223C828: ; 0x0223C828
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1]
	cmp r0, #0
	bne _0223C84E
	bl FUN_0200E308
	cmp r0, #0
	beq _0223C84E
	ldr r0, [r4, #0x2c]
	mov r1, #1
	bl FUN_02020130
	ldr r0, [r4, #0x2c]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #1
	pop {r4, pc}
_0223C84E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223C828

	thumb_func_start MOD81_0223C854
MOD81_0223C854: ; 0x0223C854
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #4
	bhi _0223C91C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223C86C: ; jump table
	.short _0223C876 - _0223C86C - 2 ; case 0
	.short _0223C884 - _0223C86C - 2 ; case 1
	.short _0223C8AE - _0223C86C - 2 ; case 2
	.short _0223C8D6 - _0223C86C - 2 ; case 3
	.short _0223C90E - _0223C86C - 2 ; case 4
_0223C876:
	add r1, r4, #0
	add r1, #0x6c
	bl MOD81_0223CD64
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
_0223C884:
	ldr r0, [r4, #0x6c]
	cmp r0, #0
	bne _0223C91C
	ldr r0, [r4, #0x30]
	mov r1, #2
	bl FUN_02020130
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [r4, #0x64]
	mov r1, #0
	bl MOD81_02238B58
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0223C91C
_0223C8AE:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0xa
	ble _0223C91C
	ldr r0, [r4, #0x14]
	mov r1, #6
	mov r2, #0
	bl FUN_02007558
	add r0, r4, #0
	mov r1, #0x10
	mov r2, #0
	mov r3, #0xc
	bl MOD81_0223CCA8
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	b _0223C91C
_0223C8D6:
	bl MOD81_0223CCF8
	cmp r0, #0
	beq _0223C91C
	ldr r0, [r4]
	bl MOD81_02238820
	mov r1, #0x4c
	mov r2, #0
	bl GetBoxMonData
	cmp r0, #0
	bne _0223C902
	ldr r0, [r4]
	bl MOD81_02238838
	bl FUN_02005578
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl FUN_02007314
_0223C902:
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0223C91C
_0223C90E:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0x1e
	ble _0223C91C
	mov r0, #1
	pop {r3, r4, r5, pc}
_0223C91C:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD81_0223C854

	thumb_func_start MOD81_0223C920
MOD81_0223C920: ; 0x0223C920
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #5
	bhi _0223C95C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223C93A: ; jump table
	.short _0223C946 - _0223C93A - 2 ; case 0
	.short _0223C952 - _0223C93A - 2 ; case 1
	.short _0223C9D0 - _0223C93A - 2 ; case 2
	.short _0223CA32 - _0223C93A - 2 ; case 3
	.short _0223CA52 - _0223C93A - 2 ; case 4
	.short _0223CA7C - _0223C93A - 2 ; case 5
_0223C946:
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0223CA8A
_0223C952:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0xa
	bgt _0223C95E
_0223C95C:
	b _0223CA8A
_0223C95E:
	ldr r0, [r4]
	bl MOD81_02238814
	str r0, [sp, #0xc]
	ldr r0, [r4]
	bl MOD81_02238810
	add r7, r0, #0
	ldr r0, [r4]
	bl MOD81_02238850
	cmp r0, #1
	bne _0223C97E
	mov r1, #2
	add r6, r1, #0
	b _0223C982
_0223C97E:
	mov r1, #5
	mov r6, #3
_0223C982:
	ldr r0, [sp, #0xc]
	ldr r2, [r4, #0x58]
	bl ReadMsgDataIntoString
	ldr r1, [r4, #0x5c]
	ldr r2, [r4, #0x58]
	add r0, r7, #0
	bl StringExpandPlaceholders
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r3, [sp, #8]
	add r0, r4, #0
	ldr r2, [r4, #0x5c]
	add r0, #0x48
	mov r1, #1
	bl AddTextPrinterParameterized
	add r0, r4, #0
	add r0, #0x48
	mov r1, #0x6d
	mov r2, #2
	bl FUN_0200D06C
	add r0, r4, #0
	add r0, #0x48
	bl CopyWindowToVram
	ldr r0, _0223CA90 ; =0x00000484
	bl PlaySound
	mov r0, #0
	str r0, [r4, #8]
	mov r0, #1
	str r0, [r4, #0xc]
	str r6, [r5]
	b _0223CA8A
_0223C9D0:
	mov r1, #0x3c
	bl MOD81_0223CA94
	cmp r0, #0
	beq _0223CA8A
	ldr r0, [r4]
	bl MOD81_02238814
	add r6, r0, #0
	ldr r0, [r4]
	bl MOD81_02238810
	add r7, r0, #0
	ldr r2, [r4, #0x58]
	add r0, r6, #0
	mov r1, #3
	bl ReadMsgDataIntoString
	ldr r1, [r4, #0x5c]
	ldr r2, [r4, #0x58]
	add r0, r7, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	add r0, #0x48
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r3, [sp, #8]
	add r0, r4, #0
	ldr r2, [r4, #0x5c]
	add r0, #0x48
	mov r1, #1
	bl AddTextPrinterParameterized
	add r0, r4, #0
	add r0, #0x48
	bl FUN_02019548
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0223CA8A
_0223CA32:
	mov r1, #0x3c
	bl MOD81_0223CA94
	cmp r0, #0
	beq _0223CA8A
	add r0, r4, #0
	add r0, #0x48
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0223CA8A
_0223CA52:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0xa
	ble _0223CA8A
	mov r0, #0x10
	str r0, [sp]
	mov r1, #0
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3a
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0223CA8A
_0223CA7C:
	bl FUN_0200E308
	cmp r0, #0
	beq _0223CA8A
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223CA8A:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223CA90: .word 0x00000484
	thumb_func_end MOD81_0223C920

	thumb_func_start MOD81_0223CA94
MOD81_0223CA94: ; 0x0223CA94
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	add r4, r1, #0
	cmp r0, #0
	beq _0223CAA6
	bl FUN_02005CBC
	str r0, [r5, #0xc]
_0223CAA6:
	ldr r0, [r5, #8]
	cmp r0, r4
	bge _0223CAB4
	add r0, r0, #1
	str r0, [r5, #8]
	mov r0, #0
	pop {r3, r4, r5, pc}
_0223CAB4:
	ldr r0, [r5, #0xc]
	cmp r0, #0
	bne _0223CABE
	mov r0, #1
	pop {r3, r4, r5, pc}
_0223CABE:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD81_0223CA94

	thumb_func_start MOD81_0223CAC4
MOD81_0223CAC4: ; 0x0223CAC4
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	bl NNS_G3dInit
	bl G3X_InitMtxStack
	ldr r0, _0223CB6C ; =0x04000060
	ldr r2, _0223CB70 ; =0xFFFFCFFD
	ldrh r1, [r0]
	and r1, r2
	strh r1, [r0]
	ldrh r3, [r0]
	add r1, r2, #2
	and r3, r1
	mov r1, #0x10
	orr r1, r3
	strh r1, [r0]
	ldrh r3, [r0]
	ldr r1, _0223CB74 ; =0x0000CFFB
	and r1, r3
	strh r1, [r0]
	add r1, r2, #2
	ldrh r3, [r0]
	lsr r2, r2, #0x11
	and r3, r1
	mov r1, #8
	orr r1, r3
	strh r1, [r0]
	mov r0, #0
	add r1, r0, #0
	mov r3, #0x3f
	str r0, [sp]
	bl G3X_SetClearColor
	ldr r1, _0223CB78 ; =0x04000540
	mov r0, #2
	str r0, [r1]
	ldr r0, _0223CB7C ; =0xBFFF0000
	str r0, [r1, #0x40]
	mov r0, #1
	add r1, r0, #0
	bl NNS_GfdInitFrmTexVramManager
	mov r0, #1
	lsl r0, r0, #0xe
	mov r1, #1
	bl NNS_GfdInitFrmPlttVramManager
	ldr r3, _0223CB80 ; =NNS_GfdDefaultFuncAllocTexVram
	mov r0, #1
	mov r1, #0
	ldr r3, [r3]
	lsl r0, r0, #0xe
	add r2, r1, #0
	blx r3
	ldr r3, _0223CB84 ; =NNS_GfdDefaultFuncAllocPlttVram
	add r4, r0, #0
	ldr r3, [r3]
	mov r0, #0x80
	mov r1, #0
	mov r2, #1
	blx r3
	ldr r2, _0223CB88 ; =0x7FFF0000
	add r6, r0, #0
	and r2, r4
	lsl r1, r4, #0x10
	lsr r2, r2, #0x10
	ldr r0, [r5, #0x10]
	lsr r1, r1, #0xd
	lsl r2, r2, #4
	bl FUN_020081A8
	ldr r2, _0223CB8C ; =0xFFFF0000
	lsl r1, r6, #0x10
	and r2, r6
	lsr r2, r2, #0x10
	ldr r0, [r5, #0x10]
	lsr r1, r1, #0xd
	lsl r2, r2, #3
	bl FUN_020081B4
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0223CB6C: .word 0x04000060
_0223CB70: .word 0xFFFFCFFD
_0223CB74: .word 0x0000CFFB
_0223CB78: .word 0x04000540
_0223CB7C: .word 0xBFFF0000
_0223CB80: .word NNS_GfdDefaultFuncAllocTexVram
_0223CB84: .word NNS_GfdDefaultFuncAllocPlttVram
_0223CB88: .word 0x7FFF0000
_0223CB8C: .word 0xFFFF0000
	thumb_func_end MOD81_0223CAC4

	thumb_func_start MOD81_0223CB90
MOD81_0223CB90: ; 0x0223CB90
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r4, r0, #0
	ldr r0, [r4]
	bl MOD81_02238820
	add r5, r0, #0
	add r0, sp, #0x10
	add r1, r5, #0
	mov r2, #2
	bl FUN_02068B70
	ldr r0, [r4]
	bl MOD81_02238838
	add r1, r0, #0
	add r0, r4, #0
	add r0, #0x18
	bl FUN_02069010
	add r0, r5, #0
	mov r1, #2
	bl FUN_02068E1C
	add r3, r0, #0
	mov r1, #0
	str r1, [sp]
	add r0, r4, #0
	str r1, [sp, #4]
	add r0, #0x18
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r4, #0x10]
	add r3, #0x50
	add r1, sp, #0x10
	mov r2, #0x80
	bl FUN_020073A0
	add sp, #0x20
	pop {r3, r4, r5, pc}
	thumb_func_end MOD81_0223CB90

	thumb_func_start MOD81_0223CBE0
MOD81_0223CBE0: ; 0x0223CBE0
	push {r4, lr}
	sub sp, #0x70
	add r4, r0, #0
	add r0, #0x34
	mov r1, #0x5d
	mov r2, #7
	mov r3, #8
	bl MOD81_0223874C
	add r0, sp, #0x5c
	bl NNS_G2dInitImagePaletteProxy
	add r0, sp, #0x38
	bl NNS_G2dInitImageProxy
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x3a
	str r0, [sp, #0xc]
	add r0, sp, #0x38
	str r0, [sp, #0x10]
	mov r0, #0x5d
	mov r1, #9
	bl GfGfxLoader_LoadImageMapping
	mov r0, #0x3a
	str r0, [sp]
	add r0, sp, #0x5c
	str r0, [sp, #4]
	mov r0, #0x5d
	mov r1, #0xa
	mov r2, #1
	mov r3, #0
	bl GfGfxLoader_PartiallyLoadPalette
	mov r0, #2
	add r1, r4, #0
	str r0, [sp]
	add r0, sp, #0x14
	add r1, #0x34
	add r2, sp, #0x38
	add r3, sp, #0x5c
	bl MOD81_022387A8
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #0x14
	mov r2, #0x80
	mov r3, #0x64
	bl MOD81_022387C8
	str r0, [r4, #0x2c]
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #0x14
	mov r2, #0x80
	mov r3, #0x5a
	bl MOD81_022387C8
	str r0, [r4, #0x30]
	mov r1, #1
	bl FUN_02020238
	ldr r0, [r4, #0x2c]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r4, #0x30]
	mov r1, #0
	bl FUN_020200A0
	add sp, #0x70
	pop {r4, pc}
	thumb_func_end MOD81_0223CBE0

	thumb_func_start MOD81_0223CC84
MOD81_0223CC84: ; 0x0223CC84
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_0223CC8C:
	ldr r0, [r5, #0x2c]
	cmp r0, #0
	beq _0223CC96
	bl FUN_0201FFC8
_0223CC96:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blt _0223CC8C
	add r6, #0x34
	add r0, r6, #0
	bl MOD81_02238784
	pop {r4, r5, r6, pc}
	thumb_func_end MOD81_0223CC84

	thumb_func_start MOD81_0223CCA8
MOD81_0223CCA8: ; 0x0223CCA8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x3a
	mov r1, #0x14
	str r2, [sp]
	add r7, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	beq _0223CCEE
	str r5, [r4]
	lsl r0, r6, #0xc
	str r0, [r4, #4]
	ldr r0, [sp]
	lsl r1, r0, #0xc
	str r1, [r4, #8]
	ldr r0, [r4, #4]
	sub r0, r1, r0
	add r1, r7, #0
	bl _s32_div_f
	str r0, [r4, #0xc]
	ldr r0, _0223CCF0 ; =MOD81_0223CD28
	str r7, [r4, #0x10]
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA60
	str r0, [r5, #0x68]
	ldr r0, _0223CCF4 ; =0x04000050
	mov r1, #1
	add r2, r6, #0
	bl G2x_SetBlendBrightness_
_0223CCEE:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223CCF0: .word MOD81_0223CD28
_0223CCF4: .word 0x04000050
	thumb_func_end MOD81_0223CCA8

	thumb_func_start MOD81_0223CCF8
MOD81_0223CCF8: ; 0x0223CCF8
	ldr r0, [r0, #0x68]
	cmp r0, #0
	bne _0223CD02
	mov r0, #1
	bx lr
_0223CD02:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD81_0223CCF8

	thumb_func_start MOD81_0223CD08
MOD81_0223CD08: ; 0x0223CD08
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x68]
	cmp r0, #0
	beq _0223CD24
	bl FUN_0201B6C8
	bl MOD81_02238898
	ldr r0, [r4, #0x68]
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #0x68]
_0223CD24:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD81_0223CD08

	thumb_func_start MOD81_0223CD28
MOD81_0223CD28: ; 0x0223CD28
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x10]
	sub r0, r0, #1
	str r0, [r4, #0x10]
	cmp r0, #0
	ble _0223CD4A
	ldr r1, [r4, #4]
	ldr r0, [r4, #0xc]
	add r2, r1, r0
	str r2, [r4, #4]
	ldr r0, _0223CD60 ; =0x04000050
	mov r1, #1
	asr r2, r2, #0xc
	bl G2x_SetBlendBrightness_
	pop {r4, pc}
_0223CD4A:
	ldr r2, [r4, #8]
	ldr r0, _0223CD60 ; =0x04000050
	mov r1, #1
	asr r2, r2, #0xc
	bl G2x_SetBlendBrightness_
	ldr r0, [r4]
	bl MOD81_0223CD08
	pop {r4, pc}
	nop
_0223CD60: .word 0x04000050
	thumb_func_end MOD81_0223CD28

	thumb_func_start MOD81_0223CD64
MOD81_0223CD64: ; 0x0223CD64
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x3a
	mov r1, #0x44
	bl AllocFromHeap
	add r4, r0, #0
	beq _0223CDD2
	mov r1, #0
	str r1, [r4, #4]
	str r6, [r4]
	ldr r0, [r5, #0x60]
	str r0, [r4, #0x10]
	ldr r0, [r5, #0x64]
	str r0, [r4, #0x14]
	str r5, [r4, #8]
	ldr r0, _0223CDD8 ; =0x000018CC
	str r1, [r4, #0x18]
	str r0, [r4, #0x1c]
	mov r0, #0x14
	str r0, [r4, #0x20]
	mov r0, #1
	lsl r0, r0, #0xc
	strh r0, [r4, #0x3a]
	str r1, [r4, #0x40]
	ldr r0, [r4, #0x14]
	bl MOD81_02238B5C
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl MOD81_02238B58
	add r1, r4, #0
	ldr r0, [r4, #0x14]
	add r1, #0x24
	bl MOD81_02238B08
	add r1, r4, #0
	ldr r0, [r4, #0x14]
	add r1, #0x34
	bl MOD81_02238B28
	ldr r0, _0223CDDC ; =MOD81_0223CE54
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	str r0, [r6]
	cmp r0, #0
	bne _0223CDD6
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
_0223CDD2:
	mov r0, #0
	str r0, [r6]
_0223CDD6:
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223CDD8: .word 0x000018CC
_0223CDDC: .word MOD81_0223CE54
	thumb_func_end MOD81_0223CD64

	thumb_func_start MOD81_0223CDE0
MOD81_0223CDE0: ; 0x0223CDE0
	push {r4, lr}
	add r4, r0, #0
	beq _0223CDFA
	bl FUN_0201B6C8
	ldr r1, [r0]
	mov r2, #0
	str r2, [r1]
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_0223CDFA:
	pop {r4, pc}
	thumb_func_end MOD81_0223CDE0

	thumb_func_start MOD81_0223CDFC
MOD81_0223CDFC: ; 0x0223CDFC
	add r1, r0, #0
	ldr r0, [r1, #0x40]
	cmp r0, #0
	beq _0223CE1E
	mov r0, #0x3a
	ldrsh r2, [r1, r0]
	mov r0, #0x3c
	ldrsh r0, [r1, r0]
	add r0, r2, r0
	strh r0, [r1, #0x3a]
	ldr r0, [r1, #0x40]
	sub r0, r0, #1
	str r0, [r1, #0x40]
	bne _0223CE1E
	mov r0, #0x3e
	ldrsh r0, [r1, r0]
	strh r0, [r1, #0x3a]
_0223CE1E:
	mov r0, #0x36
	ldrsh r2, [r1, r0]
	mov r0, #0x3a
	ldrsh r0, [r1, r0]
	ldr r3, _0223CE34 ; =MOD81_02238B40
	add r0, r2, r0
	strh r0, [r1, #0x36]
	ldr r0, [r1, #0x14]
	add r1, #0x34
	bx r3
	nop
_0223CE34: .word MOD81_02238B40
	thumb_func_end MOD81_0223CDFC

	thumb_func_start MOD81_0223CE38
MOD81_0223CE38: ; 0x0223CE38
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r2, #0
	beq _0223CE50
	mov r0, #0x3a
	ldrsh r0, [r5, r0]
	sub r0, r1, r0
	add r1, r4, #0
	bl _s32_div_f
	strh r0, [r5, #0x3c]
	str r4, [r5, #0x40]
_0223CE50:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD81_0223CE38

	thumb_func_start MOD81_0223CE54
MOD81_0223CE54: ; 0x0223CE54
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl MOD81_0223CDFC
	ldr r0, [r4, #4]
	cmp r0, #5
	bhi _0223CF62
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223CE72: ; jump table
	.short _0223CE7E - _0223CE72 - 2 ; case 0
	.short _0223CEAE - _0223CE72 - 2 ; case 1
	.short _0223CEC6 - _0223CE72 - 2 ; case 2
	.short _0223CEDC - _0223CE72 - 2 ; case 3
	.short _0223CF24 - _0223CE72 - 2 ; case 4
	.short _0223CF52 - _0223CE72 - 2 ; case 5
_0223CE7E:
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _0223CE9E
	ldr r1, [r4, #0x18]
	ldr r0, [r4, #0x1c]
	add r0, r1, r0
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x20]
	sub r0, r0, #1
	str r0, [r4, #0x20]
	ldr r1, [r4, #0x18]
	ldr r0, [r4, #0x14]
	asr r1, r1, #0xc
	bl MOD81_02238B5C
	pop {r3, r4, r5, pc}
_0223CE9E:
	ldr r0, [r4, #0x14]
	mov r1, #0x1f
	bl MOD81_02238B5C
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_0223CEAE:
	mov r1, #6
	add r0, r4, #0
	lsl r1, r1, #6
	mov r2, #0x1e
	bl MOD81_0223CE38
	mov r0, #0
	str r0, [r4, #0xc]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_0223CEC6:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	cmp r0, #0xa
	ble _0223CF62
	mov r0, #0
	str r0, [r4, #0x30]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_0223CEDC:
	ldr r1, [r4, #0x28]
	ldr r0, [r4, #0x30]
	add r0, r1, r0
	str r0, [r4, #0x28]
	mov r0, #0x1e
	ldr r1, [r4, #0x30]
	lsl r0, r0, #6
	sub r0, r1, r0
	str r0, [r4, #0x30]
	add r1, r4, #0
	ldr r0, [r4, #0x14]
	add r1, #0x24
	bl MOD81_02238B18
	ldr r1, [r4, #0x28]
	ldr r0, _0223CF64 ; =0xFFFF5000
	cmp r1, r0
	bge _0223CF62
	ldr r0, _0223CF68 ; =0x000005E6
	bl FUN_020054C8
	mov r0, #0
	ldr r1, [r4, #0x30]
	mvn r0, r0
	mul r0, r1
	str r0, [r4, #0x30]
	ldr r0, [r4, #8]
	mov r1, #0
	mov r2, #0x10
	mov r3, #8
	bl MOD81_0223CCA8
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_0223CF24:
	ldr r1, [r4, #0x28]
	ldr r0, [r4, #0x30]
	add r1, r1, r0
	mov r0, #0x13
	lsl r0, r0, #0xc
	str r1, [r4, #0x28]
	cmp r1, r0
	blt _0223CF36
	str r0, [r4, #0x28]
_0223CF36:
	add r1, r4, #0
	ldr r0, [r4, #0x14]
	add r1, #0x24
	bl MOD81_02238B18
	mov r0, #0x13
	ldr r1, [r4, #0x28]
	lsl r0, r0, #0xc
	cmp r1, r0
	bne _0223CF62
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_0223CF52:
	ldr r0, [r4, #8]
	bl MOD81_0223CCF8
	cmp r0, #0
	beq _0223CF62
	add r0, r5, #0
	bl MOD81_0223CDE0
_0223CF62:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223CF64: .word 0xFFFF5000
_0223CF68: .word 0x000005E6
	thumb_func_end MOD81_0223CE54

	.rodata
	.global MOD81_0223CF6C
MOD81_0223CF6C: ; 0x0223CF6C
	.byte 0x90, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00

	.global MOD81_0223CF74
MOD81_0223CF74: ; 0x0223CF74
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00

	.global MOD81_0223CF84
MOD81_0223CF84: ; 0x0223CF84
	.word MOD81_02238D18, MOD81_02238DC4, MOD81_02238D64, 0x00000003
	.word MOD81_022396E8, MOD81_022397A8, MOD81_02239754, 0x00000003
	.word MOD81_0223A898, MOD81_0223A8F8, MOD81_0223A8C8, 0x00000003
	.word MOD81_0223B0E8, MOD81_0223B120, MOD81_0223B10C, 0x00000001
	.word MOD81_0223B4E8, MOD81_0223B554, MOD81_0223B524, 0x00000005
	.word MOD81_0223BD18, MOD81_0223BD84, MOD81_0223BD4C, 0x00000005
	.word MOD81_0223C530, MOD81_0223C5D4, MOD81_0223C580, 0x00000005

	.global MOD81_0223CFF4
MOD81_0223CFF4: ; 0x0223CFF4
	.byte 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00

	.global MOD81_0223CFFC
MOD81_0223CFFC: ; 0x0223CFFC
	.word MOD81_02238E44, MOD81_02239068, MOD81_02239094, MOD81_022391F4

	.global MOD81_0223D00C
MOD81_0223D00C: ; 0x0223D00C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD81_0223D01C
MOD81_0223D01C: ; 0x0223D01C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD81_0223D038
MOD81_0223D038: ; 0x0223D038
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD81_0223D054
MOD81_0223D054: ; 0x0223D054
	.byte 0x02, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD81_0223D07C
MOD81_0223D07C: ; 0x0223D07C
	.byte 0x20, 0x00, 0x60, 0x00, 0xA0, 0x00, 0xE0, 0x00

	.global MOD81_0223D084
MOD81_0223D084: ; 0x0223D084
	.byte 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD81_0223D094
MOD81_0223D094: ; 0x0223D094
	.word MOD81_02239804, MOD81_02239838, MOD81_02239880, MOD81_0223992C

	.global MOD81_0223D0A4
MOD81_0223D0A4: ; 0x0223D0A4
	.byte 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10

	.global MOD81_0223D0B4
MOD81_0223D0B4: ; 0x0223D0B4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x05, 0x01, 0x16, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD81_0223D0D0
MOD81_0223D0D0: ; 0x0223D0D0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x1E, 0x04, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD81_0223D0EC
MOD81_0223D0EC: ; 0x0223D0EC
	.byte 0x02, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD81_0223D114
MOD81_0223D114: ; 0x0223D114
	.word MOD81_0223A950, MOD81_0223A998

	.global MOD81_0223D11C
MOD81_0223D11C: ; 0x0223D11C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD81_0223D12C
MOD81_0223D12C: ; 0x0223D12C
	.byte 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10

	.global MOD81_0223D13C
MOD81_0223D13C: ; 0x0223D13C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x1E, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD81_0223D158
MOD81_0223D158: ; 0x0223D158
	.byte 0x02, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD81_0223D180
MOD81_0223D180: ; 0x0223D180
	.word MOD81_0223B150, MOD81_0223B178

	.global MOD81_0223D188
MOD81_0223D188: ; 0x0223D188
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD81_0223D198
MOD81_0223D198: ; 0x0223D198
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x1A, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD81_0223D1B4
MOD81_0223D1B4: ; 0x0223D1B4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x1C, 0x04, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD81_0223D1D0
MOD81_0223D1D0: ; 0x0223D1D0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x01, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD81_0223D1EC
MOD81_0223D1EC: ; 0x0223D1EC
	.byte 0x02, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD81_0223D214
MOD81_0223D214: ; 0x0223D214
	.word MOD81_0223B584, MOD81_0223B5BC

	.global MOD81_0223D21C
MOD81_0223D21C: ; 0x0223D21C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD81_0223D22C
MOD81_0223D22C: ; 0x0223D22C
	.byte 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10

	.global MOD81_0223D23C
MOD81_0223D23C: ; 0x0223D23C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x1E, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD81_0223D258
MOD81_0223D258: ; 0x0223D258
	.byte 0x02, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD81_0223D280
MOD81_0223D280: ; 0x0223D280
	.byte 0x20, 0x00, 0x60, 0x00, 0xA0, 0x00, 0xE0, 0x00

	.global MOD81_0223D288
MOD81_0223D288: ; 0x0223D288
	.word MOD81_0223BDF0, MOD81_0223BE20, MOD81_0223BEF0

	.global MOD81_0223D294
MOD81_0223D294: ; 0x0223D294
	.byte 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD81_0223D2A4
MOD81_0223D2A4: ; 0x0223D2A4
	.byte 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10

	.global MOD81_0223D2B4
MOD81_0223D2B4: ; 0x0223D2B4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x05, 0x01, 0x16, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD81_0223D2D0
MOD81_0223D2D0: ; 0x0223D2D0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x1E, 0x04, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD81_0223D2EC
MOD81_0223D2EC: ; 0x0223D2EC
	.byte 0x02, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD81_0223D314
MOD81_0223D314: ; 0x0223D314
	.byte 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00

	.global MOD81_0223D31C
MOD81_0223D31C: ; 0x0223D31C
	.word MOD81_0223C658, MOD81_0223C828, MOD81_0223C854, MOD81_0223C920

	.global MOD81_0223D32C
MOD81_0223D32C: ; 0x0223D32C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD81_0223D33C
MOD81_0223D33C: ; 0x0223D33C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD81_0223D358
MOD81_0223D358: ; 0x0223D358
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD81_0223D374
MOD81_0223D374: ; 0x0223D374
	.byte 0x02, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.data
	.global MOD81_0223D3A0
MOD81_0223D3A0: ; 0x0223D3A0
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.bss
	.global MOD81_0223D3C0
MOD81_0223D3C0: ; 0x0223D3C0
	.space 0x4

	.global MOD81_0223D3C4
MOD81_0223D3C4: ; 0x0223D3C4
	.space 0x80

	.global MOD81_0223D444
MOD81_0223D444: ; 0x0223D444
	.space 0x4

	.global MOD81_0223D448
MOD81_0223D448: ; 0x0223D448
	.space 0x8

	.global MOD81_0223D450
MOD81_0223D450: ; 0x0223D450
	.space 0x10

