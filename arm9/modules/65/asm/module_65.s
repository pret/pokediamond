	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD65_021D74E0
MOD65_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl OverlayManager_GetField18
	mov r2, #2
	add r5, r0, #0
	mov r0, #3
	mov r1, #0x2d
	lsl r2, r2, #0x10
	bl CreateHeap
	mov r1, #2
	add r0, r4, #0
	lsl r1, r1, #8
	mov r2, #0x2d
	bl OverlayManager_CreateAndGetData
	mov r2, #2
	mov r1, #0
	lsl r2, r2, #8
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0x2d
	str r0, [r4]
	str r5, [r4, #0x20]
	ldrb r0, [r5, #3]
	strb r0, [r4, #0x1b]
	ldr r0, _021D7520 ; =0x0000FFFF
	strh r0, [r4, #0x14]
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7520: .word 0x0000FFFF
	thumb_func_end MOD65_021D74E0

	thumb_func_start MOD65_021D7524
MOD65_021D7524: ; 0x021D7524
	push {r3, lr}
	bl OverlayManager_GetData
	bl MOD65_021D757C
	cmp r0, #0
	beq _021D7536
	mov r0, #1
	pop {r3, pc}
_021D7536:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD65_021D7524

	thumb_func_start MOD65_021D753C
MOD65_021D753C: ; 0x021D753C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldrb r1, [r4, #0x1a]
	ldr r0, [r4, #0x20]
	strb r1, [r0, #1]
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x20]
	strb r1, [r0, #2]
	ldrb r1, [r4, #0x1b]
	ldr r0, [r4, #0x20]
	strb r1, [r0, #3]
	add r0, r4, #0
	add r0, #0x80
	ldrh r1, [r0]
	ldr r0, [r4, #0x20]
	strh r1, [r0, #4]
	add r0, r4, #0
	add r0, #0x82
	ldrh r1, [r0]
	ldr r0, [r4, #0x20]
	strh r1, [r0, #6]
	add r0, r5, #0
	bl OverlayManager_FreeData
	ldr r0, [r4]
	bl DestroyHeap
	mov r0, #1
	pop {r3, r4, r5, pc}
	thumb_func_end MOD65_021D753C

	thumb_func_start MOD65_021D757C
MOD65_021D757C: ; 0x021D757C
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #6
	bls _021D758A
	b _021D76BE
_021D758A:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D7596: ; jump table
	.short _021D75A4 - _021D7596 - 2 ; case 0
	.short _021D75F4 - _021D7596 - 2 ; case 1
	.short _021D761C - _021D7596 - 2 ; case 2
	.short _021D762E - _021D7596 - 2 ; case 3
	.short _021D7664 - _021D7596 - 2 ; case 4
	.short _021D7676 - _021D7596 - 2 ; case 5
	.short _021D7684 - _021D7596 - 2 ; case 6
_021D75A4:
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D76D0 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D76D4 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	mov r0, #0
	bl FUN_0200E388
	mov r0, #1
	bl FUN_0200E388
	bl FUN_0201CC08
	mov r0, #4
	bl FUN_0201CC24
	b _021D76C4
_021D75F4:
	bl MOD65_021D798C
	cmp r0, #0
	bne _021D7602
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021D7602:
	mov r0, #0
	str r0, [r4, #0xc]
	mov r1, #6
	str r1, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r2, [r4]
	add r3, r0, #0
	str r2, [sp, #8]
	add r2, r1, #0
	bl FUN_0200E1D0
	b _021D76C4
_021D761C:
	bl MOD65_021D8954
	bl FUN_0200E308
	cmp r0, #0
	bne _021D76C4
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021D762E:
	bl MOD65_021D8954
	ldrh r1, [r4, #0x18]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _021D76D8 ; =0x021DA07C
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	bne _021D7648
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021D7648:
	mov r0, #0
	str r0, [r4, #0xc]
	mov r1, #6
	str r1, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r1, [r4]
	add r2, r0, #0
	str r1, [sp, #8]
	add r1, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	b _021D76C4
_021D7664:
	bl MOD65_021D8954
	bl FUN_0200E308
	cmp r0, #0
	bne _021D76C4
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021D7676:
	bl MOD65_021D7A00
	cmp r0, #0
	bne _021D76C4
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021D7684:
	bl FUN_0201CD04
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D76D0 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D76D4 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	b _021D76C4
_021D76BE:
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, pc}
_021D76C4:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_021D76D0: .word 0xFFFFE0FF
_021D76D4: .word 0x04001000
_021D76D8: .word MOD65_021DA07C
	thumb_func_end MOD65_021D757C

	thumb_func_start MOD65_021D76DC
MOD65_021D76DC: ; 0x021D76DC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D76EE
	bl FUN_0200BC30
_021D76EE:
	bl FUN_0201C30C
	ldr r0, [r4, #0x24]
	bl DoScheduledBgGpuUpdates
	ldr r3, _021D7708 ; =0x027E0000
	ldr r1, _021D770C ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	nop
_021D7708: .word 0x027E0000
_021D770C: .word 0x00003FF8
	thumb_func_end MOD65_021D76DC

	thumb_func_start MOD65_021D7710
MOD65_021D7710: ; 0x021D7710
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D7748 ; =0x021DA094
	bl FUN_02020988
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _021D7744
	ldr r0, _021D7748 ; =0x021DA094
	bl FUN_02020968
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _021D7740
	ldrh r0, [r4, #0x14]
	cmp r0, #1
	bne _021D7740
	ldrb r1, [r4, #0x1b]
	add r0, r4, #0
	mov r2, #2
	bl MOD65_021D8280
_021D7740:
	mov r0, #0
	mvn r0, r0
_021D7744:
	pop {r4, pc}
	nop
_021D7748: .word MOD65_021DA094
	thumb_func_end MOD65_021D7710

	thumb_func_start MOD65_021D774C
MOD65_021D774C: ; 0x021D774C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r1, r5, #0
	add r1, #0xc4
	ldr r1, [r1]
	mov r4, #0
	mvn r4, r4
	cmp r1, #0
	bne _021D7762
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D7762:
	bl MOD65_021D7710
	add r1, r0, #0
	ldr r0, _021D77F8 ; =gSystem
	ldr r0, [r0, #0x44]
	cmp r0, #0
	beq _021D7784
	ldrh r0, [r5, #0x14]
	cmp r0, #0
	bne _021D7796
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	b _021D7796
_021D7784:
	cmp r1, #0
	blt _021D7792
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	bl MOD65_021D83A0
_021D7792:
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D7796:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _021D77A2
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D77A2:
	ldr r0, _021D77F8 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #2
	tst r0, r1
	beq _021D77BE
	ldr r0, _021D77FC ; =0x000005DC
	bl PlaySE
	mov r0, #0xff
	strb r0, [r5, #0x1a]
	mov r0, #0
	str r0, [r5, #0x10]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D77BE:
	mov r0, #1
	tst r0, r1
	beq _021D77F2
	ldr r0, _021D77FC ; =0x000005DC
	bl PlaySE
	cmp r4, #0xff
	beq _021D77DC
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _021D77DC
	add r0, r0, #1
	cmp r4, r0
	bne _021D77E8
_021D77DC:
	mov r0, #0xff
	strb r0, [r5, #0x1a]
	mov r0, #0
	str r0, [r5, #0x10]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D77E8:
	strb r4, [r5, #0x1a]
	mov r0, #1
	strh r0, [r5, #0x18]
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D77F2:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D77F8: .word gSystem
_021D77FC: .word 0x000005DC
	thumb_func_end MOD65_021D774C

	thumb_func_start MOD65_021D7800
MOD65_021D7800: ; 0x021D7800
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	bl MOD65_021D8970
	add r0, r4, #0
	bl MOD65_021D8634
	mov r0, #2
	strh r0, [r4, #0x18]
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD65_021D7800

	thumb_func_start MOD65_021D7818
MOD65_021D7818: ; 0x021D7818
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0xc8
	ldr r0, [r0]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	ldr r0, _021D78A4 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #2
	tst r0, r1
	beq _021D784A
	ldr r0, _021D78A8 ; =0x000005DC
	bl PlaySE
	add r0, r5, #0
	bl MOD65_021D86BC
	add r0, r5, #0
	mov r1, #0
	bl MOD65_021D8970
	mov r0, #0
	strh r0, [r5, #0x18]
	pop {r3, r4, r5, pc}
_021D784A:
	mov r0, #1
	tst r0, r1
	beq _021D789E
	ldr r0, _021D78A8 ; =0x000005DC
	bl PlaySE
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bhi _021D786E
	bhs _021D788C
	cmp r4, #1
	bhi _021D788C
	cmp r4, #0
	beq _021D7874
	cmp r4, #1
	beq _021D787A
	b _021D788C
_021D786E:
	add r0, r0, #1
	cmp r4, r0
	b _021D788C
_021D7874:
	mov r0, #1
	str r0, [r5, #0x10]
	pop {r3, r4, r5, pc}
_021D787A:
	add r0, r5, #0
	bl MOD65_021D86BC
	add r0, r5, #0
	bl MOD65_021D8718
	mov r0, #3
	strh r0, [r5, #0x18]
	b _021D789E
_021D788C:
	add r0, r5, #0
	bl MOD65_021D86BC
	add r0, r5, #0
	mov r1, #0
	bl MOD65_021D8970
	mov r0, #0
	strh r0, [r5, #0x18]
_021D789E:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D78A4: .word gSystem
_021D78A8: .word 0x000005DC
	thumb_func_end MOD65_021D7818

	thumb_func_start MOD65_021D78AC
MOD65_021D78AC: ; 0x021D78AC
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #0x1f]
	bl FUN_0201BD70
	cmp r0, #0
	beq _021D78BE
	mov r0, #0
	pop {r4, pc}
_021D78BE:
	add r0, r4, #0
	bl MOD65_021D87B0
	mov r0, #4
	strh r0, [r4, #0x18]
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD65_021D78AC

	thumb_func_start MOD65_021D78CC
MOD65_021D78CC: ; 0x021D78CC
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xd4
	ldr r0, [r0]
	ldr r1, [r4]
	bl FUN_020021AC
	cmp r0, #0
	beq _021D78E8
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _021D78FC
	b _021D7916
_021D78E8:
	ldr r0, _021D791C ; =0x000005DC
	bl PlaySE
	add r0, r4, #0
	bl MOD65_021D8764
	mov r0, #5
	strh r0, [r4, #0x18]
	mov r0, #0
	pop {r4, pc}
_021D78FC:
	ldr r0, _021D791C ; =0x000005DC
	bl PlaySE
	mov r0, #0x42
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl ClearFrameAndWindow2
	mov r0, #1
	strh r0, [r4, #0x18]
	mov r0, #0
	pop {r4, pc}
_021D7916:
	mov r0, #0
	pop {r4, pc}
	nop
_021D791C: .word 0x000005DC
	thumb_func_end MOD65_021D78CC

	thumb_func_start MOD65_021D7920
MOD65_021D7920: ; 0x021D7920
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #0x1f]
	bl FUN_0201BD70
	cmp r0, #0
	beq _021D7932
	mov r0, #0
	pop {r4, pc}
_021D7932:
	ldr r0, _021D7988 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	bne _021D7940
	mov r0, #0
	pop {r4, pc}
_021D7940:
	mov r0, #0x42
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #1
	bl ClearFrameAndWindow2
	mov r0, #0x42
	lsl r0, r0, #2
	add r0, r4, r0
	bl ClearWindowTilemapAndCopyToVram
	ldrb r0, [r4, #0x1a]
	ldr r3, [r4, #0x20]
	lsl r2, r0, #3
	add r3, #0x20
	ldrb r1, [r3, r2]
	mov r0, #0x40
	orr r0, r1
	strb r0, [r3, r2]
	ldr r0, [r4, #0x20]
	mov r1, #1
	strb r1, [r0, #2]
	add r0, r4, #0
	mov r1, #0
	bl MOD65_021D8214
	add r0, r4, #0
	bl MOD65_021D80C8
	add r0, r4, #0
	mov r1, #0
	bl MOD65_021D8970
	mov r0, #0
	strh r0, [r4, #0x18]
	pop {r4, pc}
	.align 2, 0
_021D7988: .word gSystem
	thumb_func_end MOD65_021D7920

	thumb_func_start MOD65_021D798C
MOD65_021D798C: ; 0x021D798C
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #8]
	cmp r1, #5
	bhi _021D79F0
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D79A2: ; jump table
	.short _021D79AE - _021D79A2 - 2 ; case 0
	.short _021D79B4 - _021D79A2 - 2 ; case 1
	.short _021D79BA - _021D79A2 - 2 ; case 2
	.short _021D79C6 - _021D79A2 - 2 ; case 3
	.short _021D79CC - _021D79A2 - 2 ; case 4
	.short _021D79D2 - _021D79A2 - 2 ; case 5
_021D79AE:
	bl MOD65_021D7A8C
	b _021D79F0
_021D79B4:
	bl MOD65_021D7B24
	b _021D79F0
_021D79BA:
	bl MOD65_021D7CC8
	add r0, r4, #0
	bl MOD65_021D7C04
	b _021D79F0
_021D79C6:
	bl MOD65_021D8850
	b _021D79F0
_021D79CC:
	bl MOD65_021D7DD8
	b _021D79F0
_021D79D2:
	bl MOD65_021D80C8
	ldrb r1, [r4, #0x1b]
	add r0, r4, #0
	mov r2, #4
	bl MOD65_021D8280
	ldr r0, _021D79FC ; =MOD65_021D76DC
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0
	str r0, [r4, #8]
	mov r0, #1
	pop {r4, pc}
_021D79F0:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0
	pop {r4, pc}
	nop
_021D79FC: .word MOD65_021D76DC
	thumb_func_end MOD65_021D798C

	thumb_func_start MOD65_021D7A00
MOD65_021D7A00: ; 0x021D7A00
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #8]
	cmp r1, #5
	bhi _021D7A62
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D7A16: ; jump table
	.short _021D7A22 - _021D7A16 - 2 ; case 0
	.short _021D7A3A - _021D7A16 - 2 ; case 1
	.short _021D7A46 - _021D7A16 - 2 ; case 2
	.short _021D7A52 - _021D7A16 - 2 ; case 3
	.short _021D7A58 - _021D7A16 - 2 ; case 4
	.short _021D7A5E - _021D7A16 - 2 ; case 5
_021D7A22:
	add r1, r4, #0
	add r1, #0xd0
	ldr r1, [r1]
	cmp r1, #0
	beq _021D7A30
	bl MOD65_021D86BC
_021D7A30:
	add r0, r4, #0
	mov r1, #1
	bl MOD65_021D8214
	b _021D7A62
_021D7A3A:
	bl MOD65_021D7F44
	add r0, r4, #0
	bl MOD65_021D8928
	b _021D7A62
_021D7A46:
	bl MOD65_021D7CA8
	add r0, r4, #0
	bl MOD65_021D7D74
	b _021D7A62
_021D7A52:
	bl MOD65_021D7C00
	b _021D7A62
_021D7A58:
	bl MOD65_021D7B04
	b _021D7A62
_021D7A5E:
	mov r0, #1
	pop {r4, pc}
_021D7A62:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD65_021D7A00

	thumb_func_start MOD65_021D7A6C
MOD65_021D7A6C: ; 0x021D7A6C
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D7A88 ; =0x021DA0B0
	add r3, sp, #0
	mov r2, #5
_021D7A76:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7A76
	add r0, sp, #0
	bl GX_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D7A88: .word MOD65_021DA0B0
	thumb_func_end MOD65_021D7A6C

	thumb_func_start MOD65_021D7A8C
MOD65_021D7A8C: ; 0x021D7A8C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0xb8
	add r5, r0, #0
	bl MOD65_021D7A6C
	ldr r0, [r5]
	bl BgConfig_Alloc
	add r3, sp, #0
	ldr r4, _021D7AFC ; =0x021DA040
	str r0, [r5, #0x24]
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl SetBothScreensModesAndDisable
	ldr r4, _021D7B00 ; =0x021DA140
	add r3, sp, #0x10
	mov r2, #0x15
_021D7AB8:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7AB8
	mov r4, #0
	add r7, r4, #0
	add r6, sp, #0x10
_021D7AC6:
	lsl r1, r4, #0x18
	ldr r0, [r5, #0x24]
	lsr r1, r1, #0x18
	add r2, r6, #0
	mov r3, #0
	bl InitBgFromTemplate
	lsl r1, r4, #0x18
	ldr r0, [r5, #0x24]
	lsr r1, r1, #0x18
	bl BgClearTilemapBufferAndCommit
	lsl r0, r4, #0x18
	ldr r3, [r5]
	lsr r0, r0, #0x18
	mov r1, #0x20
	mov r2, #0
	bl BG_ClearCharDataRange
	add r7, r7, #1
	add r4, r4, #1
	add r6, #0x1c
	cmp r7, #6
	blt _021D7AC6
	add sp, #0xb8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D7AFC: .word MOD65_021DA040
_021D7B00: .word MOD65_021DA140
	thumb_func_end MOD65_021D7A8C

	thumb_func_start MOD65_021D7B04
MOD65_021D7B04: ; 0x021D7B04
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_021D7B0A:
	lsl r1, r4, #0x18
	ldr r0, [r5, #0x24]
	lsr r1, r1, #0x18
	bl FreeBgTilemapBuffer
	add r4, r4, #1
	cmp r4, #6
	blt _021D7B0A
	ldr r0, [r5, #0x24]
	bl FreeToHeap
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD65_021D7B04

	thumb_func_start MOD65_021D7B24
MOD65_021D7B24: ; 0x021D7B24
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r1, [r5]
	mov r0, #0x53
	bl NARC_ctor
	add r4, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x24]
	ldr r1, [r5]
	add r2, r4, #0
	mov r3, #0x53
	bl FUN_02079B60
	mov r0, #3
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x24]
	ldr r1, [r5]
	add r2, r4, #0
	mov r3, #0x53
	bl FUN_02079B60
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #6
	lsl r0, r0, #6
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
	ldr r0, [r5, #0x24]
	ldr r1, [r5]
	add r2, r4, #0
	mov r3, #0x53
	bl FUN_02079B60
	mov r1, #0
	str r1, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #6
	lsl r0, r0, #6
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
	ldr r0, [r5, #0x24]
	ldr r1, [r5]
	add r2, r4, #0
	mov r3, #0x53
	bl FUN_02079B60
	mov r0, #0xa
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x24]
	ldr r1, [r5]
	add r2, r4, #0
	mov r3, #0x53
	bl FUN_02079B60
	mov r0, #0xb
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x24]
	ldr r1, [r5]
	add r2, r4, #0
	mov r3, #0x53
	bl FUN_02079B60
	add r0, r4, #0
	bl NARC_dtor
	ldr r0, [r5, #0x24]
	mov r1, #3
	bl ScheduleBgTilemapBufferTransfer
	ldr r0, [r5, #0x24]
	mov r1, #5
	bl ScheduleBgTilemapBufferTransfer
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD65_021D7B24

	thumb_func_start MOD65_021D7C00
MOD65_021D7C00: ; 0x021D7C00
	bx lr
	.align 2, 0
	thumb_func_end MOD65_021D7C00

	thumb_func_start MOD65_021D7C04
MOD65_021D7C04: ; 0x021D7C04
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, [r6]
	mov r1, #1
	str r0, [sp, #4]
	ldr r0, [r6, #0x24]
	mov r2, #0x1f
	mov r3, #0xf
	bl LoadUserFrameGfx1
	ldr r0, [r6, #0x20]
	ldr r0, [r0, #0x18]
	bl Options_GetFrame
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [r6]
	mov r1, #1
	str r0, [sp, #4]
	ldr r0, [r6, #0x24]
	add r2, r1, #0
	mov r3, #0xe
	bl FUN_0200CD68
	mov r1, #0x1a
	ldr r2, [r6]
	mov r0, #0
	lsl r1, r1, #4
	bl LoadFontPal0
	mov r1, #6
	ldr r2, [r6]
	mov r0, #0
	lsl r1, r1, #6
	bl FUN_02002EEC
	mov r1, #0x1a
	ldr r2, [r6]
	mov r0, #4
	lsl r1, r1, #4
	bl LoadFontPal0
	add r5, r6, #0
	ldr r4, _021D7CA4 ; =0x021DA0D8
	mov r7, #0
	add r5, #0xe8
_021D7C68:
	ldrb r0, [r4, #2]
	add r1, r5, #0
	str r0, [sp]
	ldrb r0, [r4, #3]
	str r0, [sp, #4]
	ldrb r0, [r4, #4]
	str r0, [sp, #8]
	ldrb r0, [r4, #5]
	str r0, [sp, #0xc]
	ldrh r0, [r4, #6]
	str r0, [sp, #0x10]
	ldrb r2, [r4]
	ldrb r3, [r4, #1]
	ldr r0, [r6, #0x24]
	bl AddWindowParameterized
	add r0, r5, #0
	mov r1, #0
	bl FillWindowPixelBuffer
	add r7, r7, #1
	add r4, #8
	add r5, #0x10
	cmp r7, #0xd
	blt _021D7C68
	add r0, r6, #0
	bl MOD65_021D87D4
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D7CA4: .word MOD65_021DA0D8
	thumb_func_end MOD65_021D7C04

	thumb_func_start MOD65_021D7CA8
MOD65_021D7CA8: ; 0x021D7CA8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
	add r5, #0xe8
_021D7CB0:
	add r0, r5, #0
	bl ClearWindowTilemapAndCopyToVram
	add r0, r5, #0
	bl RemoveWindow
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #0xd
	blt _021D7CB0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD65_021D7CA8

	thumb_func_start MOD65_021D7CC8
MOD65_021D7CC8: ; 0x021D7CC8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r1, [r5]
	mov r0, #2
	bl FUN_02002C50
	mov r2, #0x67
	ldr r3, [r5]
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #2
	bl NewMsgDataFromNarc
	str r0, [r5, #0x2c]
	ldr r0, [r5]
	bl FUN_02014518
	str r0, [r5, #0x28]
	ldr r2, [r5]
	mov r0, #2
	mov r1, #0x40
	bl MessageFormat_new_custom
	str r0, [r5, #0x30]
	ldr r1, [r5]
	mov r0, #0x40
	bl String_ctor
	str r0, [r5, #0x34]
	ldr r0, [r5, #0x2c]
	mov r1, #6
	bl NewString_ReadMsgData
	str r0, [r5, #0x38]
	ldr r0, [r5, #0x2c]
	mov r1, #0x16
	bl NewString_ReadMsgData
	str r0, [r5, #0x3c]
	ldr r0, [r5, #0x2c]
	mov r1, #4
	bl NewString_ReadMsgData
	str r0, [r5, #0x40]
	ldr r0, [r5, #0x2c]
	mov r1, #7
	bl NewString_ReadMsgData
	str r0, [r5, #0x44]
	ldr r0, [r5, #0x2c]
	mov r1, #8
	bl NewString_ReadMsgData
	str r0, [r5, #0x48]
	ldr r0, [r5, #0x2c]
	mov r1, #0
	bl NewString_ReadMsgData
	str r0, [r5, #0x4c]
	mov r4, #0
	add r6, r5, #0
_021D7D42:
	add r1, r4, #0
	ldr r0, [r5, #0x2c]
	add r1, #0xb
	bl NewString_ReadMsgData
	str r0, [r6, #0x50]
	cmp r4, #5
	bge _021D7D66
	add r1, r4, #0
	ldr r0, [r5, #0x2c]
	add r1, #0x11
	bl NewString_ReadMsgData
	str r0, [r6, #0x68]
	add r4, r4, #1
	add r6, r6, #4
	cmp r4, #6
	blt _021D7D42
_021D7D66:
	ldr r0, [r5, #0x20]
	ldr r0, [r0, #0x18]
	bl Options_GetTextFrameDelay
	add r5, #0x7c
	strb r0, [r5]
	pop {r4, r5, r6, pc}
	thumb_func_end MOD65_021D7CC8

	thumb_func_start MOD65_021D7D74
MOD65_021D7D74: ; 0x021D7D74
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_021D7D7C:
	ldr r0, [r5, #0x50]
	bl String_dtor
	cmp r4, #5
	bge _021D7D94
	ldr r0, [r5, #0x68]
	bl String_dtor
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _021D7D7C
_021D7D94:
	ldr r0, [r6, #0x4c]
	bl String_dtor
	ldr r0, [r6, #0x48]
	bl String_dtor
	ldr r0, [r6, #0x44]
	bl String_dtor
	ldr r0, [r6, #0x40]
	bl String_dtor
	ldr r0, [r6, #0x3c]
	bl String_dtor
	ldr r0, [r6, #0x38]
	bl String_dtor
	ldr r0, [r6, #0x34]
	bl String_dtor
	ldr r0, [r6, #0x30]
	bl MessageFormat_delete
	ldr r0, [r6, #0x28]
	bl FUN_02014564
	ldr r0, [r6, #0x2c]
	bl DestroyMsgData
	mov r0, #2
	bl FUN_02002CF8
	pop {r4, r5, r6, pc}
	thumb_func_end MOD65_021D7D74

	thumb_func_start MOD65_021D7DD8
MOD65_021D7DD8: ; 0x021D7DD8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r6, _021D7F30 ; =0x021DA1E8
	mov r7, #0
	add r4, r5, #0
_021D7DE4:
	mov r0, #0x6e
	mov r1, #0x6f
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r6, #0
	bl FUN_0200BE38
	mov r1, #7
	lsl r1, r1, #6
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	add r7, r7, #1
	add r6, #0x28
	add r4, r4, #4
	cmp r7, #3
	blt _021D7DE4
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200BC
	mov r0, #0x71
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	ldr r6, _021D7F34 ; =0x021DA050
	mov r7, #0
	add r4, r5, #0
_021D7E3A:
	mov r0, #0x6e
	mov r1, #0x6f
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	ldr r2, _021D7F38 ; =0x021DA260
	bl FUN_0200BE38
	mov r1, #0x73
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r7, #3
	bl FUN_02020130
	mov r0, #0x73
	mov r1, #0
	mov r2, #2
	lsl r0, r0, #2
	ldrsh r1, [r6, r1]
	ldrsh r2, [r6, r2]
	ldr r0, [r4, r0]
	bl FUN_0200C6E4
	add r7, r7, #1
	add r4, r4, #4
	add r6, r6, #4
	cmp r7, #5
	blt _021D7E3A
	mov r7, #0
	ldr r6, _021D7F3C ; =0x021DA064
	add r4, r5, #0
	str r7, [sp, #0x10]
_021D7E8C:
	mov r0, #0x6e
	mov r1, #0x6f
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	ldr r2, _021D7F40 ; =0x021DA288
	bl FUN_0200BE38
	mov r1, #0x1e
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x10]
	bl FUN_02020130
	mov r0, #0x1e
	lsl r0, r0, #4
	mov r1, #2
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl FUN_020200D8
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, r7, #2
	bl FUN_02020248
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200BC
	mov r0, #0x1e
	mov r1, #0
	mov r2, #2
	lsl r0, r0, #4
	ldrsh r1, [r6, r1]
	ldrsh r2, [r6, r2]
	ldr r0, [r4, r0]
	bl FUN_0200C6E4
	ldr r0, [sp, #0x10]
	add r7, r7, #1
	add r0, r0, #3
	add r4, r4, #4
	add r6, r6, #4
	str r0, [sp, #0x10]
	cmp r7, #6
	blt _021D7E8C
	mov r1, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x7e
	str r1, [sp, #0xc]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r2, #0xe7
	mov r3, #0x4c
	bl FUN_02088490
	mov r1, #0x7f
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #0
	ldr r0, [r0, #4]
	bl FUN_0200C644
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D7F30: .word MOD65_021DA1E8
_021D7F34: .word MOD65_021DA050
_021D7F38: .word MOD65_021DA260
_021D7F3C: .word MOD65_021DA064
_021D7F40: .word MOD65_021DA288
	thumb_func_end MOD65_021D7DD8

	thumb_func_start MOD65_021D7F44
MOD65_021D7F44: ; 0x021D7F44
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0x7e
	add r5, r0, #0
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl FUN_02088694
	mov r7, #0x1e
	mov r6, #0
	add r4, r5, #0
	lsl r7, r7, #4
_021D7F5E:
	ldr r0, [r4, r7]
	bl FUN_0200BC14
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #6
	blt _021D7F5E
	mov r7, #0x73
	mov r6, #0
	add r4, r5, #0
	lsl r7, r7, #2
_021D7F74:
	ldr r0, [r4, r7]
	bl FUN_0200BC14
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #5
	blt _021D7F74
	mov r6, #7
	mov r4, #0
	lsl r6, r6, #6
_021D7F88:
	ldr r0, [r5, r6]
	bl FUN_0200BC14
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _021D7F88
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD65_021D7F44

	thumb_func_start MOD65_021D7F98
MOD65_021D7F98: ; 0x021D7F98
	ldrb r2, [r0, #4]
	mov r1, #0x20
	bic r2, r1
	strb r2, [r0, #4]
	mov r1, #0xff
	strb r1, [r0, #6]
	ldrb r1, [r0, #6]
	strb r1, [r0, #7]
	bx lr
	.align 2, 0
	thumb_func_end MOD65_021D7F98

	thumb_func_start MOD65_021D7FAC
MOD65_021D7FAC: ; 0x021D7FAC
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	cmp r3, #0
	beq _021D7FCA
	mov r0, #0x42
	lsl r0, r0, #2
	mov r1, #1
	add r0, r5, r0
	add r2, r1, #0
	mov r3, #0xe
	bl DrawFrameAndWindow2
_021D7FCA:
	mov r0, #0xd8
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	add r0, #0xe8
	mov r2, #0
	add r0, r5, r0
	mov r1, #0xff
	add r3, r2, #0
	bl FillWindowPixelRect
	mov r0, #1
	bl TextFlags_SetCanABSpeedUpPrint
	mov r0, #0
	bl FUN_02002B7C
	mov r3, #0
	str r3, [sp]
	ldr r0, _021D800C ; =0x0001020F
	str r4, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x42
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #1
	add r2, r6, #0
	str r3, [sp, #0xc]
	bl AddTextPrinterParameterized2
	strb r0, [r5, #0x1f]
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D800C: .word 0x0001020F
	thumb_func_end MOD65_021D7FAC

	thumb_func_start MOD65_021D8010
MOD65_021D8010: ; 0x021D8010
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	add r5, r1, #0
	mov r0, #0xff
	strb r0, [r5, #0x1e]
	ldrb r0, [r5, #0x1e]
	strb r0, [r5, #0x1d]
	ldrb r2, [r5, #0x1b]
	cmp r2, #5
	bne _021D802E
	mov r7, #0x1f
	b _021D8044
_021D802E:
	mov r7, #1
	ldr r1, [sp, #4]
	cmp r2, #0
	ble _021D8044
_021D8036:
	lsl r0, r7, #0x19
	lsr r7, r0, #0x18
	add r0, r1, #1
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	cmp r1, r2
	blt _021D8036
_021D8044:
	ldr r0, [sp]
	mov r6, #0
	ldrb r0, [r0]
	cmp r0, #0
	ble _021D80BA
	ldr r0, [sp]
	str r0, [sp, #8]
	add r0, #0x1c
	str r0, [sp, #8]
_021D8056:
	ldr r0, [sp, #8]
	lsl r1, r6, #3
	add r4, r0, r1
	add r0, r4, #0
	bl MOD65_021D7F98
	ldrb r0, [r4, #4]
	lsl r1, r0, #0x18
	lsr r1, r1, #0x1f
	beq _021D80AC
	lsl r1, r0, #0x19
	lsr r1, r1, #0x1f
	bne _021D80AC
	mov r1, #0x1f
	and r1, r0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	tst r1, r7
	beq _021D80AC
	mov r1, #0x20
	orr r0, r1
	strb r0, [r4, #4]
	ldrb r0, [r5, #0x1d]
	cmp r0, #0xff
	ldrb r0, [r4, #5]
	bne _021D808E
	strb r0, [r5, #0x1d]
	b _021D809A
_021D808E:
	ldrb r1, [r5, #0x1e]
	lsl r2, r1, #3
	ldr r1, [sp]
	add r1, r1, r2
	add r1, #0x23
	strb r0, [r1]
_021D809A:
	ldrb r0, [r5, #0x1e]
	strb r0, [r4, #6]
	ldrb r0, [r4, #5]
	strb r0, [r5, #0x1e]
	ldr r0, [sp, #4]
	add r0, r0, #1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
_021D80AC:
	add r0, r6, #1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r0, [sp]
	ldrb r0, [r0]
	cmp r6, r0
	blt _021D8056
_021D80BA:
	ldr r0, [sp, #4]
	add r0, r0, #1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD65_021D8010

	thumb_func_start MOD65_021D80C8
MOD65_021D80C8: ; 0x021D80C8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5, #0x20]
	add r1, r5, #0
	bl MOD65_021D8010
	strb r0, [r5, #0x1c]
	ldrb r0, [r5, #0x1c]
	ldr r1, [r5]
	bl ListMenuItems_ctor
	add r1, r5, #0
	add r1, #0xcc
	str r0, [r1]
	ldrb r4, [r5, #0x1e]
	cmp r4, #0xff
	beq _021D8142
	mov r7, #0
_021D80EE:
	ldr r1, [r5, #0x20]
	lsl r0, r4, #3
	add r1, #0x1c
	add r6, r1, r0
	ldrb r4, [r6, #6]
	ldrb r1, [r6, #2]
	ldr r0, [r5, #0x28]
	bl FUN_02014588
	add r2, r0, #0
	str r7, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, [r5, #0x30]
	add r1, r7, #0
	add r3, r7, #0
	bl BufferString
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldrb r2, [r6, #1]
	ldr r0, [r5, #0x30]
	mov r1, #1
	mov r3, #2
	bl BufferIntegerAsString
	ldr r0, [r5, #0x30]
	ldr r1, [r5, #0x34]
	ldr r2, [r5, #0x3c]
	bl StringExpandPlaceholders
	add r0, r5, #0
	add r0, #0xcc
	ldrb r2, [r6, #5]
	ldr r0, [r0]
	ldr r1, [r5, #0x34]
	bl ListMenuItems_AddItem
	cmp r4, #0xff
	bne _021D80EE
_021D8142:
	add r0, r5, #0
	add r0, #0xcc
	ldr r0, [r0]
	ldr r1, [r5, #0x38]
	mov r2, #0xff
	bl ListMenuItems_AddItem
	add r1, r5, #0
	ldr r0, _021D8210 ; =0x021DA2E0
	add r1, #0x84
	mov r2, #0x20
	bl MI_CpuCopy8
	ldr r0, [r5, #0x20]
	ldrh r1, [r0, #6]
	add r0, r5, #0
	add r0, #0x82
	strh r1, [r0]
	ldr r0, [r5, #0x20]
	ldrh r1, [r0, #4]
	add r0, r5, #0
	add r0, #0x80
	strh r1, [r0]
	ldr r0, [r5, #0x20]
	ldrb r0, [r0, #2]
	cmp r0, #0
	beq _021D81C0
	add r0, r5, #0
	add r0, #0x80
	ldrh r0, [r0]
	cmp r0, #0
	bne _021D81A4
	add r0, r5, #0
	add r0, #0x82
	ldrh r1, [r0]
	cmp r1, #0
	beq _021D81BA
	ldrb r0, [r5, #0x1c]
	sub r0, r0, #1
	cmp r1, r0
	blt _021D81BA
	add r0, r5, #0
	add r0, #0x82
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r5, #0
	add r0, #0x82
	strh r1, [r0]
	b _021D81BA
_021D81A4:
	add r1, r0, #6
	ldrb r0, [r5, #0x1c]
	cmp r1, r0
	blt _021D81BA
	add r0, r5, #0
	add r0, #0x80
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r5, #0
	add r0, #0x80
	strh r1, [r0]
_021D81BA:
	ldr r0, [r5, #0x20]
	mov r1, #0
	strb r1, [r0, #2]
_021D81C0:
	add r1, r5, #0
	add r0, r5, #0
	add r1, #0xe8
	add r0, #0x90
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xcc
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0x84
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xa0
	str r5, [r0]
	add r0, r5, #0
	add r2, r5, #0
	ldrb r1, [r5, #0x1c]
	add r0, #0x94
	add r2, #0x82
	strh r1, [r0]
	mov r0, #0
	strh r0, [r5, #0x16]
	add r1, r5, #0
	add r1, #0x80
	ldr r3, [r5]
	add r0, r5, #0
	lsl r3, r3, #0x18
	ldrh r1, [r1]
	ldrh r2, [r2]
	add r0, #0x84
	lsr r3, r3, #0x18
	bl ListMenuInit
	add r1, r5, #0
	add r1, #0xc4
	str r0, [r1]
	mov r0, #1
	strh r0, [r5, #0x16]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8210: .word MOD65_021DA2E0
	thumb_func_end MOD65_021D80C8

	thumb_func_start MOD65_021D8214
MOD65_021D8214: ; 0x021D8214
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0xb0
	str r0, [sp]
	mov r0, #0x60
	add r4, r1, #0
	mov r1, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xe8
	add r2, r1, #0
	add r3, r1, #0
	bl FillWindowPixelRect
	cmp r4, #0
	beq _021D823E
	add r0, r5, #0
	add r0, #0xe8
	bl ClearWindowTilemapAndCopyToVram
_021D823E:
	add r0, r5, #0
	add r0, #0xc4
	add r1, r5, #0
	add r2, r5, #0
	ldr r0, [r0]
	add r1, #0x80
	add r2, #0x82
	bl DestroyListMenu
	add r0, r5, #0
	add r0, #0xcc
	ldr r0, [r0]
	bl ListMenuItems_dtor
	add r0, r5, #0
	add r0, #0x80
	ldrh r1, [r0]
	ldr r0, [r5, #0x20]
	strh r1, [r0, #4]
	add r0, r5, #0
	add r0, #0x82
	ldrh r1, [r0]
	ldr r0, [r5, #0x20]
	strh r1, [r0, #6]
	add r0, r5, #0
	mov r1, #0
	add r0, #0xc4
	str r1, [r0]
	add r5, #0xcc
	str r1, [r5]
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD65_021D8214

	thumb_func_start MOD65_021D8280
MOD65_021D8280: ; 0x021D8280
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r1, #0
	cmp r2, #4
	bls _021D828C
	b _021D8392
_021D828C:
	add r0, r2, r2
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8298: ; jump table
	.short _021D82A2 - _021D8298 - 2 ; case 0
	.short _021D82D2 - _021D8298 - 2 ; case 1
	.short _021D8302 - _021D8298 - 2 ; case 2
	.short _021D8330 - _021D8298 - 2 ; case 3
	.short _021D835E - _021D8298 - 2 ; case 4
_021D82A2:
	mov r0, #0x1e
	lsl r0, r0, #4
	add r6, r4, r0
	lsl r7, r5, #2
	lsl r1, r5, #1
	ldr r0, [r6, r7]
	add r1, r5, r1
	bl FUN_02020130
	ldr r0, [r6, r7]
	mov r1, #0
	bl FUN_020200BC
	add r1, r4, #0
	add r0, r5, #7
	add r1, #0xe8
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #1
	mov r2, #2
	mov r3, #0
	bl ScrollWindow
	b _021D8392
_021D82D2:
	mov r0, #0x1e
	lsl r0, r0, #4
	add r6, r4, r0
	lsl r7, r5, #2
	ldr r0, [r6, r7]
	bl FUN_02020198
	ldr r0, [r6, r7]
	mov r1, #1
	bl FUN_020200BC
	add r1, r4, #0
	add r0, r5, #7
	add r1, #0xe8
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	mov r2, #4
	add r3, r1, #0
	bl ScrollWindow
	mov r0, #1
	strh r0, [r4, #0x14]
	b _021D8392
_021D8302:
	lsl r0, r5, #2
	add r1, r4, r0
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	lsl r1, r5, #1
	add r1, r5, r1
	add r1, r1, #1
	bl FUN_02020130
	add r1, r4, #0
	add r0, r5, #7
	add r1, #0xe8
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #1
	mov r2, #2
	mov r3, #0
	bl ScrollWindow
	mov r0, #0
	strh r0, [r4, #0x14]
	b _021D8392
_021D8330:
	lsl r0, r5, #2
	add r1, r4, r0
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	lsl r1, r5, #1
	add r1, r5, r1
	add r1, r1, #2
	bl FUN_02020130
	add r1, r4, #0
	add r0, r5, #7
	add r1, #0xe8
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	mov r2, #2
	add r3, r1, #0
	bl ScrollWindow
	mov r0, #1
	strh r0, [r4, #0x14]
	b _021D8392
_021D835E:
	mov r0, #0x1e
	lsl r0, r0, #4
	lsl r1, r5, #1
	add r1, r5, r1
	add r6, r4, r0
	lsl r7, r5, #2
	ldr r0, [r6, r7]
	add r1, r1, #1
	bl FUN_02020130
	ldr r0, [r6, r7]
	mov r1, #1
	bl FUN_020200BC
	add r1, r4, #0
	add r0, r5, #7
	add r1, #0xe8
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	mov r2, #2
	add r3, r1, #0
	bl ScrollWindow
	mov r0, #0
	strh r0, [r4, #0x14]
_021D8392:
	add r0, r5, #7
	add r4, #0xe8
	lsl r0, r0, #4
	add r0, r4, r0
	bl CopyWindowToVram
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD65_021D8280

	thumb_func_start MOD65_021D83A0
MOD65_021D83A0: ; 0x021D83A0
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, _021D8470 ; =0x000005E4
	add r5, r1, #0
	bl PlaySE
	ldrh r1, [r4, #0x14]
	ldr r0, _021D8474 ; =0x0000FFFF
	cmp r1, r0
	beq _021D83D2
	ldrb r1, [r4, #0x1b]
	cmp r5, r1
	bne _021D83CA
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #3
	bl MOD65_021D8280
	add sp, #0x10
	pop {r3, r4, r5, pc}
_021D83CA:
	add r0, r4, #0
	mov r2, #0
	bl MOD65_021D8280
_021D83D2:
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #1
	bl MOD65_021D8280
	add r0, r4, #0
	mov r1, #0
	strb r5, [r4, #0x1b]
	bl MOD65_021D8214
	add r0, r4, #0
	mov r2, #0
	add r0, #0x82
	strh r2, [r0]
	add r0, r4, #0
	add r0, #0x82
	ldrh r1, [r0]
	add r0, r4, #0
	add r0, #0x80
	strh r1, [r0]
	ldr r0, [r4, #0x20]
	strh r2, [r0, #6]
	ldr r1, [r4, #0x20]
	ldrh r0, [r1, #6]
	strh r0, [r1, #4]
	add r0, r4, #0
	bl MOD65_021D80C8
	mov r1, #0xa0
	str r1, [sp]
	mov r0, #0x18
	add r1, #0xa8
	str r0, [sp, #4]
	add r0, r4, r1
	mov r1, #0
	add r2, r1, #0
	add r3, r1, #0
	bl FillWindowPixelRect
	ldrb r1, [r4, #0x1b]
	cmp r1, #5
	bne _021D8434
	mov r0, #0x52
	lsl r0, r0, #2
	add r0, r4, r0
	bl CopyWindowToVram
	add sp, #0x10
	pop {r3, r4, r5, pc}
_021D8434:
	lsl r1, r1, #2
	add r1, r4, r1
	mov r0, #0
	ldr r1, [r1, #0x68]
	add r2, r0, #0
	bl FUN_02002E14
	mov r2, #0xa0
	sub r3, r2, r0
	mov r0, #3
	str r0, [sp]
	mov r1, #0
	ldr r0, _021D8478 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r2, #0xa8
	str r1, [sp, #0xc]
	add r0, r4, r2
	ldrb r2, [r4, #0x1b]
	lsl r2, r2, #2
	add r2, r4, r2
	lsr r4, r3, #0x1f
	add r4, r3, r4
	ldr r2, [r2, #0x68]
	asr r3, r4, #1
	bl AddTextPrinterParameterized2
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D8470: .word 0x000005E4
_021D8474: .word 0x0000FFFF
_021D8478: .word 0x00010200
	thumb_func_end MOD65_021D83A0

	thumb_func_start MOD65_021D847C
MOD65_021D847C: ; 0x021D847C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	ldr r6, _021D84E0 ; =0x00000001
	bne _021D84A6
	mov r4, #0
	mov r6, #0x73
	add r7, r4, #0
	lsl r6, r6, #2
_021D848E:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, r6]
	add r1, r7, #0
	bl FUN_020200A0
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #5
	blo _021D848E
	pop {r3, r4, r5, r6, r7, pc}
_021D84A6:
	mov r4, #0
_021D84A8:
	ldrb r0, [r7, #4]
	tst r0, r6
	beq _021D84C0
	lsl r0, r4, #2
	add r1, r5, r0
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
	b _021D84D0
_021D84C0:
	lsl r0, r4, #2
	add r1, r5, r0
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_020200A0
_021D84D0:
	lsl r0, r6, #0x19
	lsr r6, r0, #0x18
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #5
	blo _021D84A8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D84E0: .word 0x00000001
	thumb_func_end MOD65_021D847C

	thumb_func_start MOD65_021D84E4
MOD65_021D84E4: ; 0x021D84E4
	ldr r3, _021D84EC ; =ListMenuGetTemplateField
	mov r1, #0x13
	bx r3
	nop
_021D84EC: .word ListMenuGetTemplateField
	thumb_func_end MOD65_021D84E4

	thumb_func_start MOD65_021D84F0
MOD65_021D84F0: ; 0x021D84F0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r1, #0
	mov r1, #0x13
	add r7, r0, #0
	add r6, r2, #0
	bl ListMenuGetTemplateField
	add r4, r0, #0
	cmp r6, #0
	bne _021D850C
	ldr r0, _021D862C ; =0x000005DC
	bl PlaySE
_021D850C:
	add r1, sp, #0x10
	add r0, r7, #0
	add r1, #2
	add r2, sp, #0x10
	bl ListMenuGetScrollAndRow
	add r2, sp, #0x10
	ldrh r2, [r2]
	mov r0, #7
	lsl r0, r0, #6
	lsl r2, r2, #4
	add r2, #0x28
	lsl r2, r2, #0x10
	ldr r0, [r4, r0]
	mov r1, #0x69
	asr r2, r2, #0x10
	bl FUN_0200C6E4
	add r0, sp, #0x10
	ldrh r0, [r0, #2]
	cmp r0, #0
	bne _021D8546
	mov r0, #0x71
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	b _021D8552
_021D8546:
	mov r0, #0x71
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
_021D8552:
	add r0, sp, #0x10
	ldrh r1, [r0, #2]
	ldrb r0, [r4, #0x1c]
	sub r0, r0, #6
	cmp r1, r0
	bge _021D856C
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	b _021D8578
_021D856C:
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
_021D8578:
	mov r0, #0x50
	str r0, [sp]
	mov r1, #0
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0xf8
	add r2, r1, #0
	add r3, r1, #0
	bl FillWindowPixelRect
	cmp r5, #0xff
	bne _021D85B4
	add r0, r4, #0
	mov r1, #0
	bl MOD65_021D847C
	add r0, r4, #0
	add r0, #0xf8
	bl CopyWindowToVram
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	ldr r0, [r0, #4]
	bl FUN_0200C644
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_021D85B4:
	ldr r1, [r4, #0x20]
	lsl r5, r5, #3
	add r1, #0x1c
	add r0, r4, #0
	add r1, r1, r5
	bl MOD65_021D847C
	ldr r0, [r4, #0x34]
	bl StringSetEmpty
	ldr r0, [r4, #0x20]
	add r0, r0, r5
	ldrb r2, [r0, #0x1f]
	cmp r2, #0x63
	bls _021D85D4
	mov r2, #0x63
_021D85D4:
	mov r1, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4, #0x30]
	mov r3, #2
	bl BufferIntegerAsString
	ldr r0, [r4, #0x30]
	ldr r1, [r4, #0x34]
	ldr r2, [r4, #0x40]
	bl StringExpandPlaceholders
	mov r1, #0
	str r1, [sp]
	ldr r0, _021D8630 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x34]
	add r0, #0xf8
	mov r3, #8
	bl AddTextPrinterParameterized2
	ldr r2, [r4, #0x20]
	mov r1, #0x7e
	lsl r1, r1, #2
	add r2, r2, r5
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldrb r2, [r2, #0x1e]
	ldr r1, [r4, r1]
	bl FUN_02088660
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	ldr r0, [r0, #4]
	bl FUN_0200C644
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D862C: .word 0x000005DC
_021D8630: .word 0x00010200
	thumb_func_end MOD65_021D84F0

	thumb_func_start MOD65_021D8634
MOD65_021D8634: ; 0x021D8634
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r1, [r5]
	mov r0, #3
	bl ListMenuItems_ctor
	add r1, r5, #0
	add r1, #0xd0
	str r0, [r1]
	mov r4, #0
_021D8648:
	add r0, r5, #0
	add r0, #0xd0
	ldr r0, [r0]
	ldr r1, [r5, #0x2c]
	add r2, r4, #1
	add r3, r4, #0
	bl ListMenuItems_AppendFromMsgData
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #3
	blo _021D8648
	add r1, r5, #0
	ldr r0, _021D86B8 ; =0x021DA2C0
	add r1, #0xa4
	mov r2, #0x20
	bl MI_CpuCopy8
	mov r0, #0x46
	lsl r0, r0, #2
	add r1, r5, #0
	add r0, r5, r0
	add r1, #0xb0
	str r0, [r1]
	add r1, r5, #0
	add r1, #0xd0
	ldr r2, [r1]
	add r1, r5, #0
	add r1, #0xa4
	str r2, [r1]
	add r1, r5, #0
	add r1, #0xc0
	str r5, [r1]
	add r1, r5, #0
	mov r2, #3
	add r1, #0xb4
	strh r2, [r1]
	mov r1, #1
	mov r2, #0x1f
	mov r3, #0xf
	bl DrawFrameAndWindow1
	ldr r3, [r5]
	add r0, r5, #0
	mov r1, #0
	lsl r3, r3, #0x18
	add r0, #0xa4
	add r2, r1, #0
	lsr r3, r3, #0x18
	bl ListMenuInit
	add r5, #0xc8
	str r0, [r5]
	pop {r3, r4, r5, pc}
	nop
_021D86B8: .word MOD65_021DA2C0
	thumb_func_end MOD65_021D8634

	thumb_func_start MOD65_021D86BC
MOD65_021D86BC: ; 0x021D86BC
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #0x46
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl ClearFrameAndWindow1
	mov r0, #0x46
	lsl r0, r0, #2
	add r0, r4, r0
	bl ClearWindowTilemapAndCopyToVram
	add r0, r4, #0
	add r0, #0xc8
	add r2, sp, #0
	ldr r0, [r0]
	add r1, sp, #0
	add r2, #2
	bl DestroyListMenu
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl ListMenuItems_dtor
	add r0, r4, #0
	mov r1, #0
	add r0, #0xc8
	str r1, [r0]
	add r4, #0xd0
	str r1, [r4]
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD65_021D86BC

	thumb_func_start MOD65_021D8704
MOD65_021D8704: ; 0x021D8704
	push {r3, lr}
	cmp r2, #0
	bne _021D8710
	ldr r0, _021D8714 ; =0x000005DC
	bl PlaySE
_021D8710:
	pop {r3, pc}
	nop
_021D8714: .word 0x000005DC
	thumb_func_end MOD65_021D8704

	thumb_func_start MOD65_021D8718
MOD65_021D8718: ; 0x021D8718
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0x34]
	bl StringSetEmpty
	ldrb r1, [r4, #0x1a]
	ldr r2, [r4, #0x20]
	ldr r0, [r4, #0x28]
	lsl r1, r1, #3
	add r1, r2, r1
	ldrb r1, [r1, #0x1e]
	bl FUN_02014588
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r3, #2
	str r3, [sp, #4]
	ldr r0, [r4, #0x30]
	mov r1, #0
	bl BufferString
	ldr r0, [r4, #0x30]
	ldr r1, [r4, #0x34]
	ldr r2, [r4, #0x44]
	bl StringExpandPlaceholders
	add r0, r4, #0
	ldr r1, [r4, #0x34]
	add r4, #0x7c
	ldrb r2, [r4]
	mov r3, #1
	bl MOD65_021D7FAC
	add sp, #8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD65_021D8718

	thumb_func_start MOD65_021D8764
MOD65_021D8764: ; 0x021D8764
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0x34]
	bl StringSetEmpty
	ldrb r1, [r4, #0x1a]
	ldr r2, [r4, #0x20]
	ldr r0, [r4, #0x28]
	lsl r1, r1, #3
	add r1, r2, r1
	ldrb r1, [r1, #0x1e]
	bl FUN_02014588
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r3, #2
	str r3, [sp, #4]
	ldr r0, [r4, #0x30]
	mov r1, #0
	bl BufferString
	ldr r0, [r4, #0x30]
	ldr r1, [r4, #0x34]
	ldr r2, [r4, #0x48]
	bl StringExpandPlaceholders
	add r0, r4, #0
	ldr r1, [r4, #0x34]
	add r4, #0x7c
	ldrb r2, [r4]
	mov r3, #0
	bl MOD65_021D7FAC
	add sp, #8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD65_021D8764

	thumb_func_start MOD65_021D87B0
MOD65_021D87B0: ; 0x021D87B0
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4]
	ldr r1, _021D87D0 ; =0x021DA2B8
	str r0, [sp]
	ldr r0, [r4, #0x24]
	mov r2, #0x1f
	mov r3, #0xf
	bl Std_CreateYesNoMenu
	add r4, #0xd4
	str r0, [r4]
	add sp, #4
	pop {r3, r4, pc}
	nop
_021D87D0: .word MOD65_021DA2B8
	thumb_func_end MOD65_021D87B0

	thumb_func_start MOD65_021D87D4
MOD65_021D87D4: ; 0x021D87D4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r1, #0
	add r5, r0, #0
	str r1, [sp]
	ldr r0, _021D8844 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r2, [r5, #0x4c]
	add r0, r5, r0
	mov r3, #4
	bl AddTextPrinterParameterized2
	add r0, r5, #0
	str r0, [sp, #0x10]
	add r0, #0xe8
	ldr r4, _021D8848 ; =0x021DA2B0
	mov r6, #0
	str r0, [sp, #0x10]
_021D8800:
	ldr r1, [r5, #0x50]
	mov r0, #2
	mov r2, #0
	bl FUN_02002E14
	mov r1, #0x40
	sub r3, r1, r0
	ldrb r0, [r4]
	lsr r7, r3, #0x1f
	add r7, r3, r7
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _021D884C ; =0x00020301
	asr r3, r7, #1
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, r6, #7
	lsl r1, r0, #4
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0x50]
	add r0, r0, r1
	mov r1, #2
	bl AddTextPrinterParameterized2
	add r6, r6, #1
	add r5, r5, #4
	add r4, r4, #1
	cmp r6, #6
	blt _021D8800
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D8844: .word 0x00010200
_021D8848: .word MOD65_021DA2B0
_021D884C: .word 0x00020301
	thumb_func_end MOD65_021D87D4

	thumb_func_start MOD65_021D8850
MOD65_021D8850: ; 0x021D8850
	push {r4, r5, r6, r7, lr}
	sub sp, #0x54
	add r4, r0, #0
	ldr r1, [r4]
	mov r0, #0x20
	bl FUN_0201C24C
	ldr r0, [r4]
	bl FUN_0200BB14
	mov r1, #0x6e
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	bl FUN_0200BB34
	mov r7, #0x6f
	lsl r7, r7, #2
	add r2, sp, #0x34
	ldr r3, _021D891C ; =0x021DA330
	str r0, [r4, r7]
	ldmia r3!, {r0, r1}
	add r6, r2, #0
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	ldr r5, _021D8920 ; =0x021DA300
	stmia r2!, {r0, r1}
	add r3, sp, #0x20
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r6, #0
	str r0, [r3]
	sub r0, r7, #4
	ldr r0, [r4, r0]
	mov r3, #0x20
	bl FUN_0200BB6C
	sub r1, r7, #4
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0xe
	bl FUN_0200BBF0
	ldr r0, [r4]
	bl FUN_0200A064
	ldr r0, [r4]
	bl FUN_0200A06C
	ldr r5, _021D8924 ; =0x021DA314
	add r3, sp, #4
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	sub r1, r7, #4
	str r0, [r3]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	bl FUN_0200BD20
	mov r1, #1
	mov r0, #0
	str r0, [sp]
	ldr r0, [r4]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02088320
	add r1, r7, #0
	add r1, #0x3c
	str r0, [r4, r1]
	bl FUN_02030F40
	cmp r0, #0
	beq _021D8908
	bl FUN_02033E74
_021D8908:
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	add sp, #0x54
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D891C: .word MOD65_021DA330
_021D8920: .word MOD65_021DA300
_021D8924: .word MOD65_021DA314
	thumb_func_end MOD65_021D8850

	thumb_func_start MOD65_021D8928
MOD65_021D8928: ; 0x021D8928
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02088360
	mov r1, #0x6e
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	bl FUN_0200BCE0
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200BD04
	bl FUN_0201C29C
	pop {r4, pc}
	thumb_func_end MOD65_021D8928

	thumb_func_start MOD65_021D8954
MOD65_021D8954: ; 0x021D8954
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200BC1C
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02088484
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD65_021D8954

	thumb_func_start MOD65_021D8970
MOD65_021D8970: ; 0x021D8970
	push {r4, lr}
	add r4, r0, #0
	cmp r1, #0
	bne _021D899E
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02020248
	mov r0, #0x71
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200BC
	pop {r4, pc}
_021D899E:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #9
	bl FUN_02020248
	mov r0, #0x71
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200BC
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200BC
	pop {r4, pc}
	thumb_func_end MOD65_021D8970

	thumb_func_start MOD65_021D89C4
MOD65_021D89C4: ; 0x021D89C4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r0, #0
	add r5, r1, #0
	add r1, sp, #0
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	add r4, r2, #0
	str r0, [r1, #8]
	add r7, r3, #0
	ldr r0, [r4]
	add r1, r7, #0
	bl FX_Div
	str r0, [r5]
	ldr r0, [r4, #4]
	add r1, r7, #0
	bl FX_Div
	str r0, [r5, #4]
	ldr r0, [r4, #8]
	add r1, r7, #0
	bl FX_Div
	add r2, sp, #0
	str r0, [r5, #8]
	ldmia r2!, {r0, r1}
	stmia r6!, {r0, r1}
	ldr r0, [r2]
	str r0, [r6]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD65_021D89C4

	thumb_func_start MOD65_021D8A08
MOD65_021D8A08: ; 0x021D8A08
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl OverlayManager_GetField18
	mov r2, #1
	add r5, r0, #0
	mov r0, #3
	mov r1, #0x2e
	lsl r2, r2, #0x10
	bl CreateHeap
	mov r1, #0x6f
	add r0, r4, #0
	lsl r1, r1, #2
	mov r2, #0x2e
	bl OverlayManager_CreateAndGetData
	mov r2, #0x6f
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0x2e
	str r0, [r4]
	str r5, [r4, #0x10]
	mov r0, #1
	pop {r3, r4, r5, pc}
	thumb_func_end MOD65_021D8A08

	thumb_func_start MOD65_021D8A40
MOD65_021D8A40: ; 0x021D8A40
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, [r5]
	cmp r0, #2
	blt _021D8A64
	cmp r0, #5
	bgt _021D8A64
	add r0, r4, #0
	add r0, #0x40
	bl MOD65_021D9F50
	ldr r0, [r4, #0x5c]
	bl FUN_02088484
_021D8A64:
	ldr r0, [r5]
	cmp r0, #7
	bls _021D8A6C
	b _021D8B9E
_021D8A6C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8A78: ; jump table
	.short _021D8A88 - _021D8A78 - 2 ; case 0
	.short _021D8ACE - _021D8A78 - 2 ; case 1
	.short _021D8AE8 - _021D8A78 - 2 ; case 2
	.short _021D8B12 - _021D8A78 - 2 ; case 3
	.short _021D8B20 - _021D8A78 - 2 ; case 4
	.short _021D8B4A - _021D8A78 - 2 ; case 5
	.short _021D8B58 - _021D8A78 - 2 ; case 6
	.short _021D8B68 - _021D8A78 - 2 ; case 7
_021D8A88:
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D8BB0 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D8BB4 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	mov r0, #0
	bl FUN_0200E388
	mov r0, #1
	bl FUN_0200E388
	b _021D8BA4
_021D8ACE:
	add r0, r4, #0
	bl MOD65_021D8BD8
	cmp r0, #0
	bne _021D8ADE
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, pc}
_021D8ADE:
	ldr r0, _021D8BB8 ; =MOD65_021D8C88
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	b _021D8BA4
_021D8AE8:
	ldr r1, [r4, #4]
	add r0, r1, #1
	str r0, [r4, #4]
	cmp r1, #4
	bge _021D8AF8
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, pc}
_021D8AF8:
	mov r0, #0
	str r0, [r4, #4]
	mov r1, #6
	str r1, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r2, [r4]
	add r3, r0, #0
	str r2, [sp, #8]
	add r2, r1, #0
	bl FUN_0200E1D0
	b _021D8BA4
_021D8B12:
	bl FUN_0200E308
	cmp r0, #0
	bne _021D8BA4
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, pc}
_021D8B20:
	add r0, r4, #0
	bl MOD65_021D9074
	cmp r0, #0
	bne _021D8B30
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, pc}
_021D8B30:
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	b _021D8BA4
_021D8B4A:
	bl FUN_0200E308
	cmp r0, #0
	bne _021D8BA4
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, pc}
_021D8B58:
	add r0, r4, #0
	bl MOD65_021D8C30
	cmp r0, #0
	bne _021D8BA4
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, pc}
_021D8B68:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D8BB0 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D8BB4 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	b _021D8BA4
_021D8B9E:
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_021D8BA4:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_021D8BB0: .word 0xFFFFE0FF
_021D8BB4: .word 0x04001000
_021D8BB8: .word MOD65_021D8C88
	thumb_func_end MOD65_021D8A40

	thumb_func_start MOD65_021D8BBC
MOD65_021D8BBC: ; 0x021D8BBC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r0, r5, #0
	bl OverlayManager_FreeData
	ldr r0, [r4]
	bl DestroyHeap
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD65_021D8BBC

	thumb_func_start MOD65_021D8BD8
MOD65_021D8BD8: ; 0x021D8BD8
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _021D8BEC
	cmp r1, #1
	beq _021D8BF8
	cmp r1, #2
	beq _021D8C04
	b _021D8C24
_021D8BEC:
	bl MOD65_021D8CD8
	add r0, r4, #0
	bl MOD65_021D8D90
	b _021D8C24
_021D8BF8:
	bl MOD65_021D8EC4
	add r0, r4, #0
	bl MOD65_021D8E68
	b _021D8C24
_021D8C04:
	bl MOD65_021D8F34
	add r0, r4, #0
	add r1, r4, #0
	ldr r2, [r4]
	add r0, #0x40
	add r1, #0x30
	bl MOD65_021D9E98
	add r0, r4, #0
	bl MOD65_021D8FB0
	mov r0, #0
	str r0, [r4, #4]
	mov r0, #1
	pop {r4, pc}
_021D8C24:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD65_021D8BD8

	thumb_func_start MOD65_021D8C30
MOD65_021D8C30: ; 0x021D8C30
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #3
	bhi _021D8C7C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D8C46: ; jump table
	.short _021D8C4E - _021D8C46 - 2 ; case 0
	.short _021D8C62 - _021D8C46 - 2 ; case 1
	.short _021D8C6E - _021D8C46 - 2 ; case 2
	.short _021D8C74 - _021D8C46 - 2 ; case 3
_021D8C4E:
	bl MOD65_021D9054
	add r0, r4, #0
	add r0, #0x40
	bl MOD65_021D9F8C
	add r0, r4, #0
	bl MOD65_021D8FA4
	b _021D8C7C
_021D8C62:
	bl MOD65_021D8EB0
	add r0, r4, #0
	bl MOD65_021D8F08
	b _021D8C7C
_021D8C6E:
	bl MOD65_021D8D68
	b _021D8C7C
_021D8C74:
	mov r0, #0
	str r0, [r4, #4]
	mov r0, #1
	pop {r4, pc}
_021D8C7C:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD65_021D8C30

	thumb_func_start MOD65_021D8C88
MOD65_021D8C88: ; 0x021D8C88
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x68]
	bl DoScheduledBgGpuUpdates
	ldr r0, [r4, #0x44]
	bl FUN_020081C4
	bl FUN_0200BC30
	bl FUN_0201C30C
	ldr r3, _021D8CB0 ; =0x027E0000
	ldr r1, _021D8CB4 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	nop
_021D8CB0: .word 0x027E0000
_021D8CB4: .word 0x00003FF8
	thumb_func_end MOD65_021D8C88

	thumb_func_start MOD65_021D8CB8
MOD65_021D8CB8: ; 0x021D8CB8
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D8CD4 ; =0x021DA3A0
	add r3, sp, #0
	mov r2, #5
_021D8CC2:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D8CC2
	add r0, sp, #0
	bl GX_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D8CD4: .word MOD65_021DA3A0
	thumb_func_end MOD65_021D8CB8

	thumb_func_start MOD65_021D8CD8
MOD65_021D8CD8: ; 0x021D8CD8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x6c
	add r5, r0, #0
	bl MOD65_021D8CB8
	ldr r0, [r5]
	bl BgConfig_Alloc
	add r3, sp, #8
	ldr r4, _021D8D5C ; =0x021DA35C
	str r0, [r5, #0x68]
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl SetBothScreensModesAndDisable
	ldr r4, _021D8D60 ; =0x021DA3C8
	add r3, sp, #0x18
	mov r2, #0xa
_021D8D04:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D8D04
	ldr r1, _021D8D64 ; =0x021DA350
	ldr r0, [r4]
	ldrb r2, [r1]
	str r0, [r3]
	add r0, sp, #4
	strb r2, [r0]
	ldrb r2, [r1, #1]
	ldrb r1, [r1, #2]
	add r4, sp, #4
	strb r2, [r0, #1]
	strb r1, [r0, #2]
	mov r0, #0
	str r0, [sp]
	add r6, sp, #0x18
_021D8D28:
	ldrb r7, [r4]
	ldr r0, [r5, #0x68]
	add r2, r6, #0
	add r1, r7, #0
	mov r3, #0
	bl InitBgFromTemplate
	ldr r0, [r5, #0x68]
	add r1, r7, #0
	bl BgClearTilemapBufferAndCommit
	ldr r3, [r5]
	add r0, r7, #0
	mov r1, #0x20
	mov r2, #0
	bl BG_ClearCharDataRange
	ldr r0, [sp]
	add r4, r4, #1
	add r0, r0, #1
	add r6, #0x1c
	str r0, [sp]
	cmp r0, #3
	blt _021D8D28
	add sp, #0x6c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D8D5C: .word MOD65_021DA35C
_021D8D60: .word MOD65_021DA3C8
_021D8D64: .word MOD65_021DA350
	thumb_func_end MOD65_021D8CD8

	thumb_func_start MOD65_021D8D68
MOD65_021D8D68: ; 0x021D8D68
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #1
_021D8D6E:
	lsl r1, r4, #0x18
	ldr r0, [r5, #0x68]
	lsr r1, r1, #0x18
	bl FreeBgTilemapBuffer
	add r4, r4, #1
	cmp r4, #3
	blt _021D8D6E
	ldr r0, [r5, #0x68]
	mov r1, #4
	bl FreeBgTilemapBuffer
	ldr r0, [r5, #0x68]
	bl FreeToHeap
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD65_021D8D68

	thumb_func_start MOD65_021D8D90
MOD65_021D8D90: ; 0x021D8D90
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r1, [r5]
	mov r0, #0x57
	bl NARC_ctor
	add r4, r0, #0
	mov r0, #2
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x68]
	ldr r1, [r5]
	add r2, r4, #0
	mov r3, #0x57
	bl FUN_02079B60
	mov r0, #3
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x68]
	ldr r1, [r5]
	add r2, r4, #0
	mov r3, #0x57
	bl FUN_02079B60
	mov r1, #0
	str r1, [sp]
	mov r0, #2
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x20
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
	ldr r0, [r5, #0x68]
	ldr r1, [r5]
	add r2, r4, #0
	mov r3, #0x57
	bl FUN_02079B60
	mov r0, #1
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xa0
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x68]
	ldr r1, [r5]
	add r2, r4, #0
	mov r3, #0x57
	bl FUN_02079B60
	mov r0, #4
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x68]
	ldr r1, [r5]
	add r2, r4, #0
	mov r3, #0x57
	bl FUN_02079B60
	mov r0, #5
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x68]
	ldr r1, [r5]
	add r2, r4, #0
	mov r3, #0x57
	bl FUN_02079B60
	add r0, r4, #0
	bl NARC_dtor
	ldr r0, [r5, #0x68]
	mov r1, #2
	bl ScheduleBgTilemapBufferTransfer
	ldr r0, [r5, #0x68]
	mov r1, #4
	bl ScheduleBgTilemapBufferTransfer
	add sp, #0x14
	pop {r4, r5, pc}
	thumb_func_end MOD65_021D8D90

	thumb_func_start MOD65_021D8E68
MOD65_021D8E68: ; 0x021D8E68
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r4, #0x68]
	ldr r2, _021D8EAC ; =0x021DA354
	add r1, #0x6c
	bl AddWindow
	add r0, r4, #0
	add r0, #0x6c
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, [r4, #0x10]
	mov r1, #1
	ldrb r0, [r0, #0xb]
	add r2, r1, #0
	mov r3, #0xe
	str r0, [sp]
	ldr r0, [r4]
	str r0, [sp, #4]
	ldr r0, [r4, #0x68]
	bl FUN_0200CD68
	mov r1, #0x1e
	ldr r2, [r4]
	mov r0, #0
	lsl r1, r1, #4
	bl FUN_02002EEC
	add sp, #8
	pop {r4, pc}
	nop
_021D8EAC: .word MOD65_021DA354
	thumb_func_end MOD65_021D8E68

	thumb_func_start MOD65_021D8EB0
MOD65_021D8EB0: ; 0x021D8EB0
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x6c
	bl ClearWindowTilemapAndCopyToVram
	add r4, #0x6c
	add r0, r4, #0
	bl RemoveWindow
	pop {r4, pc}
	thumb_func_end MOD65_021D8EB0

	thumb_func_start MOD65_021D8EC4
MOD65_021D8EC4: ; 0x021D8EC4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r2, _021D8F04 ; =0x0000019B
	ldr r3, [r6]
	mov r0, #0
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	str r0, [r6, #0x18]
	ldr r2, [r6]
	mov r0, #1
	mov r1, #0x40
	bl MessageFormat_new_custom
	str r0, [r6, #0x1c]
	ldr r1, [r6]
	mov r0, #0x40
	bl String_ctor
	str r0, [r6, #0x20]
	mov r4, #0
	add r5, r6, #0
_021D8EF0:
	ldr r0, [r6, #0x18]
	add r1, r4, #0
	bl NewString_ReadMsgData
	str r0, [r5, #0x24]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _021D8EF0
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8F04: .word 0x0000019B
	thumb_func_end MOD65_021D8EC4

	thumb_func_start MOD65_021D8F08
MOD65_021D8F08: ; 0x021D8F08
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_021D8F10:
	ldr r0, [r5, #0x24]
	bl String_dtor
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _021D8F10
	ldr r0, [r6, #0x20]
	bl String_dtor
	ldr r0, [r6, #0x1c]
	bl MessageFormat_delete
	ldr r0, [r6, #0x18]
	bl DestroyMsgData
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD65_021D8F08

	thumb_func_start MOD65_021D8F34
MOD65_021D8F34: ; 0x021D8F34
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	mov r1, #5
	ldr r0, [r0]
	mov r2, #0
	str r0, [r4, #0x30]
	ldr r0, [r4, #0x10]
	ldr r0, [r0]
	bl GetMonData
	strh r0, [r4, #0x34]
	ldr r0, [r4, #0x10]
	ldr r0, [r0]
	bl GetMonGender
	add r1, r4, #0
	add r1, #0x37
	strb r0, [r1]
	ldr r0, [r4, #0x10]
	ldr r0, [r0]
	bl GetMonNature
	add r1, r4, #0
	add r1, #0x36
	strb r0, [r1]
	ldrh r0, [r4, #0x34]
	mov r1, #0x1c ; BASE_FLIP
	bl GetMonBaseStat
	mov r1, #1
	eor r1, r0
	add r0, r4, #0
	add r0, #0x38
	strb r1, [r0]
	ldr r1, [r4]
	mov r0, #0xc
	bl String_ctor
	str r0, [r4, #0x3c]
	ldr r0, [r4, #0x10]
	ldr r2, [r4, #0x3c]
	ldr r0, [r0]
	mov r1, #0x76
	bl GetMonData
	add r1, r4, #0
	ldr r0, [r4, #0x10]
	add r1, #0x36
	ldrb r1, [r1]
	ldr r0, [r0, #4]
	bl FUN_020881D0
	add r4, #0x39
	strb r0, [r4]
	pop {r4, pc}
	thumb_func_end MOD65_021D8F34

	thumb_func_start MOD65_021D8FA4
MOD65_021D8FA4: ; 0x021D8FA4
	ldr r3, _021D8FAC ; =String_dtor
	ldr r0, [r0, #0x3c]
	bx r3
	nop
_021D8FAC: .word String_dtor
	thumb_func_end MOD65_021D8FA4

	thumb_func_start MOD65_021D8FB0
MOD65_021D8FB0: ; 0x021D8FB0
	push {r3, r4, r5, r6, lr}
	sub sp, #0x44
	add r4, r0, #0
	ldr r1, [r4]
	mov r0, #0x20
	bl FUN_0201C24C
	ldr r0, [r4]
	bl FUN_0200BB14
	add r2, sp, #0x24
	ldr r5, _021D904C ; =0x021DA380
	str r0, [r4, #0x7c]
	ldmia r5!, {r0, r1}
	add r3, r2, #0
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	ldr r6, _021D9050 ; =0x021DA36C
	stmia r2!, {r0, r1}
	add r5, sp, #0x10
	ldmia r6!, {r0, r1}
	add r2, r5, #0
	stmia r5!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	add r1, r3, #0
	str r0, [r5]
	ldr r0, [r4, #0x7c]
	mov r3, #0x20
	bl FUN_0200BB6C
	ldr r0, [r4]
	bl FUN_0200A064
	mov r0, #0
	str r0, [sp]
	mov r1, #2
	ldr r0, [r4]
	add r2, r1, #0
	mov r3, #1
	bl FUN_02088320
	str r0, [r4, #0x5c]
	mov r1, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r1, [sp, #8]
	str r1, [sp, #0xc]
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x5c]
	ldrh r1, [r1, #8]
	mov r2, #0x64
	mov r3, #0x5a
	bl FUN_02088490
	str r0, [r4, #0x60]
	ldr r0, [r0, #4]
	mov r1, #0
	bl FUN_0200C644
	bl FUN_02030F40
	cmp r0, #0
	beq _021D9040
	bl FUN_02033E74
_021D9040:
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	add sp, #0x44
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021D904C: .word MOD65_021DA380
_021D9050: .word MOD65_021DA36C
	thumb_func_end MOD65_021D8FB0

	thumb_func_start MOD65_021D9054
MOD65_021D9054: ; 0x021D9054
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x5c]
	ldr r1, [r4, #0x60]
	bl FUN_02088694
	ldr r0, [r4, #0x5c]
	bl FUN_02088360
	ldr r0, [r4, #0x7c]
	bl FUN_0200BD04
	bl FUN_0201C29C
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD65_021D9054

	thumb_func_start MOD65_021D9074
MOD65_021D9074: ; 0x021D9074
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #8
	bhi _021D90F4
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D908A: ; jump table
	.short _021D909C - _021D908A - 2 ; case 0
	.short _021D90A8 - _021D908A - 2 ; case 1
	.short _021D90B4 - _021D908A - 2 ; case 2
	.short _021D90C0 - _021D908A - 2 ; case 3
	.short _021D90CC - _021D908A - 2 ; case 4
	.short _021D90D8 - _021D908A - 2 ; case 5
	.short _021D90E4 - _021D908A - 2 ; case 6
	.short _021D90EC - _021D908A - 2 ; case 7
	.short _021D90F4 - _021D908A - 2 ; case 8
_021D909C:
	add r1, r4, #0
	add r1, #0x80
	bl MOD65_021D9150
	str r0, [r4, #4]
	b _021D90FC
_021D90A8:
	add r1, r4, #0
	add r1, #0x80
	bl MOD65_021D922C
	str r0, [r4, #4]
	b _021D90FC
_021D90B4:
	add r1, r4, #0
	add r1, #0x80
	bl MOD65_021D923C
	str r0, [r4, #4]
	b _021D90FC
_021D90C0:
	add r1, r4, #0
	add r1, #0x80
	bl MOD65_021D926C
	str r0, [r4, #4]
	b _021D90FC
_021D90CC:
	add r1, r4, #0
	add r1, #0x80
	bl MOD65_021D9284
	str r0, [r4, #4]
	b _021D90FC
_021D90D8:
	add r1, r4, #0
	add r1, #0x80
	bl MOD65_021D92B4
	str r0, [r4, #4]
	b _021D90FC
_021D90E4:
	bl MOD65_021D92C4
	str r0, [r4, #4]
	b _021D90FC
_021D90EC:
	bl MOD65_021D9338
	str r0, [r4, #4]
	b _021D90FC
_021D90F4:
	mov r0, #0
	str r0, [r4, #4]
	mov r0, #1
	pop {r4, pc}
_021D90FC:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD65_021D9074

	thumb_func_start MOD65_021D9100
MOD65_021D9100: ; 0x021D9100
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r2, #0
	add r3, r5, #0
	add r0, r1, #0
	mov r2, #0x1c
	add r3, #0xcc
	mul r0, r2
	add r4, r3, r0
	add r0, r4, #0
	mov r1, #0
	bl MI_CpuFill8
	str r5, [r4, #0x14]
	add r0, r6, #0
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	str r0, [r4, #0x18]
	ldr r0, [r5, #4]
	add r0, r0, #1
	str r0, [r5, #4]
	pop {r4, r5, r6, pc}
	thumb_func_end MOD65_021D9100

	thumb_func_start MOD65_021D9130
MOD65_021D9130: ; 0x021D9130
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	bl FUN_0200CAB4
	ldr r1, [r4, #0x14]
	mov r2, #0x1c
	ldr r0, [r1, #4]
	sub r0, r0, #1
	str r0, [r1, #4]
	add r0, r4, #0
	mov r1, #0
	bl MI_CpuFill8
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD65_021D9130

	thumb_func_start MOD65_021D9150
MOD65_021D9150: ; 0x021D9150
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r4, r1, #0
	mov r2, #0x4f
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #0
	lsl r2, r2, #2
	bl MI_CpuFill8
	ldr r0, [r5, #0x60]
	mov r2, #0x18
	ldr r0, [r0, #4]
	ldr r1, [r0]
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	ldr r1, [r5, #0x58]
	add r0, r4, #0
	add r0, #0xc8
	str r1, [r0]
	add r5, #0x39
	ldrb r0, [r5]
	mov r1, #2
	lsl r1, r1, #0x12
	str r0, [r4, #8]
	str r2, [r4]
	mov r0, #0xe
	str r1, [r4, #0xc]
	lsl r0, r0, #0x10
	str r0, [r4, #0x10]
	str r1, [r4, #0x18]
	lsl r0, r2, #0xe
	str r0, [r4, #0x1c]
	lsr r0, r1, #7
	str r0, [r4, #0x30]
	str r0, [r4, #0x34]
	lsr r0, r1, #8
	str r0, [r4, #0x3c]
	str r0, [r4, #0x40]
	add r1, r4, #0
	str r2, [r4, #0x64]
	mov r0, #0
	str r0, [r4, #0x60]
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, #0xc
	bl FUN_02020044
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xc
	add r1, #0x18
	add r2, sp, #0xc
	bl VEC_Subtract
	add r1, r4, #0
	mov r3, #6
	add r0, sp, #0
	add r1, #0x48
	add r2, sp, #0xc
	lsl r3, r3, #0xe
	bl MOD65_021D89C4
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #1
	bl FUN_020200EC
	add r0, r4, #0
	add r0, #0xc4
	add r1, r4, #0
	ldr r0, [r0]
	add r1, #0x30
	bl FUN_02020064
	ldr r2, _021D921C ; =MOD65_021D9380
	add r0, r4, #0
	mov r1, #0
	bl MOD65_021D9100
	ldr r2, _021D9220 ; =MOD65_021D94AC
	add r0, r4, #0
	mov r1, #1
	bl MOD65_021D9100
	ldr r2, _021D9224 ; =MOD65_021D967C
	add r0, r4, #0
	mov r1, #2
	bl MOD65_021D9100
	ldr r2, _021D9228 ; =MOD65_021D97C4
	add r0, r4, #0
	mov r1, #3
	bl MOD65_021D9100
	mov r0, #1
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_021D921C: .word MOD65_021D9380
_021D9220: .word MOD65_021D94AC
_021D9224: .word MOD65_021D967C
_021D9228: .word MOD65_021D97C4
	thumb_func_end MOD65_021D9150

	thumb_func_start MOD65_021D922C
MOD65_021D922C: ; 0x021D922C
	ldr r0, [r1, #4]
	cmp r0, #0
	beq _021D9236
	mov r0, #1
	bx lr
_021D9236:
	mov r0, #2
	bx lr
	.align 2, 0
	thumb_func_end MOD65_021D922C

	thumb_func_start MOD65_021D923C
MOD65_021D923C: ; 0x021D923C
	push {r3, lr}
	add r1, r0, #0
	add r0, #0x39
	ldrb r0, [r0]
	cmp r0, #1
	ldr r0, [r1]
	bne _021D925A
	str r0, [sp]
	ldrh r1, [r1, #0x34]
	mov r0, #0xb
	mov r2, #0
	mov r3, #0x7f
	bl FUN_020056AC
	b _021D9268
_021D925A:
	str r0, [sp]
	ldrh r1, [r1, #0x34]
	mov r0, #0
	add r2, r0, #0
	mov r3, #0x7f
	bl FUN_020056AC
_021D9268:
	mov r0, #3
	pop {r3, pc}
	thumb_func_end MOD65_021D923C

	thumb_func_start MOD65_021D926C
MOD65_021D926C: ; 0x021D926C
	push {r3, lr}
	bl FUN_02005670
	cmp r0, #0
	beq _021D927A
	mov r0, #3
	pop {r3, pc}
_021D927A:
	mov r0, #0
	bl FUN_02005614
	mov r0, #4
	pop {r3, pc}
	thumb_func_end MOD65_021D926C

	thumb_func_start MOD65_021D9284
MOD65_021D9284: ; 0x021D9284
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	add r0, #0x68
	mov r1, #0
	mov r2, #0x5c
	bl MI_CpuFill8
	ldr r2, _021D92AC ; =MOD65_021D99C0
	add r0, r4, #0
	mov r1, #0
	bl MOD65_021D9100
	ldr r2, _021D92B0 ; =MOD65_021D9B0C
	add r0, r4, #0
	mov r1, #1
	bl MOD65_021D9100
	mov r0, #5
	pop {r4, pc}
	.align 2, 0
_021D92AC: .word MOD65_021D99C0
_021D92B0: .word MOD65_021D9B0C
	thumb_func_end MOD65_021D9284

	thumb_func_start MOD65_021D92B4
MOD65_021D92B4: ; 0x021D92B4
	ldr r0, [r1, #4]
	cmp r0, #0
	beq _021D92BE
	mov r0, #5
	bx lr
_021D92BE:
	mov r0, #6
	bx lr
	.align 2, 0
	thumb_func_end MOD65_021D92B4

	thumb_func_start MOD65_021D92C4
MOD65_021D92C4: ; 0x021D92C4
	push {r4, lr}
	sub sp, #0x10
	mov r1, #1
	add r4, r0, #0
	add r0, #0x6c
	add r2, r1, #0
	mov r3, #0xe
	bl DrawFrameAndWindow2
	add r0, r4, #0
	add r0, #0x6c
	mov r1, #0xff
	bl FillWindowPixelBuffer
	ldr r0, [r4, #0x20]
	bl StringSetEmpty
	mov r0, #1
	str r0, [sp]
	mov r3, #2
	str r3, [sp, #4]
	ldr r0, [r4, #0x1c]
	ldr r2, [r4, #0x3c]
	mov r1, #0
	bl BufferString
	add r2, r4, #0
	add r2, #0x39
	ldrb r2, [r2]
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x20]
	lsl r2, r2, #2
	add r2, r4, r2
	ldr r2, [r2, #0x24]
	bl StringExpandPlaceholders
	mov r3, #0
	str r3, [sp]
	ldr r0, [r4, #0x10]
	mov r1, #1
	ldrb r0, [r0, #0xa]
	str r0, [sp, #4]
	ldr r0, _021D9334 ; =0x0001020F
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x20]
	add r0, #0x6c
	bl AddTextPrinterParameterized2
	strh r0, [r4, #0xc]
	mov r0, #0
	strh r0, [r4, #0xe]
	mov r0, #7
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021D9334: .word 0x0001020F
	thumb_func_end MOD65_021D92C4

	thumb_func_start MOD65_021D9338
MOD65_021D9338: ; 0x021D9338
	push {r4, lr}
	add r4, r0, #0
	ldrh r0, [r4, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _021D934E
	mov r0, #7
	pop {r4, pc}
_021D934E:
	ldr r0, _021D937C ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	bne _021D9366
	ldrh r1, [r4, #0xe]
	add r0, r1, #1
	strh r0, [r4, #0xe]
	cmp r1, #0x5a
	bhs _021D9366
	mov r0, #7
	pop {r4, pc}
_021D9366:
	add r0, r4, #0
	add r0, #0x6c
	mov r1, #1
	bl ClearFrameAndWindow2
	add r4, #0x6c
	add r0, r4, #0
	bl ClearWindowTilemapAndCopyToVram
	mov r0, #8
	pop {r4, pc}
	.align 2, 0
_021D937C: .word gSystem
	thumb_func_end MOD65_021D9338

	thumb_func_start MOD65_021D9380
MOD65_021D9380: ; 0x021D9380
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r6, r1, #0
	ldr r4, [r6, #0x14]
	add r7, r0, #0
	mov r0, #0x18
	add r5, r4, #0
	str r0, [r6, #4]
	mov r0, #1
	add r5, #0xc
	lsl r0, r0, #0xc
	str r0, [r5, #0x24]
	str r0, [r5, #0x28]
	lsr r0, r0, #1
	str r0, [r5, #0x30]
	str r0, [r5, #0x34]
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0x24
	add r1, #0x30
	add r2, sp, #0xc
	bl VEC_Subtract
	ldr r0, [r6, #4]
	cmp r0, #0
	ble _021D93C6
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D93D4
_021D93C6:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D93D4:
	bl _ffix
	add r1, r5, #0
	add r3, r0, #0
	add r0, sp, #0
	add r1, #0x3c
	add r2, sp, #0xc
	bl MOD65_021D89C4
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #1
	bl FUN_020200A0
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	mov r1, #1
	bl FUN_020200EC
	add r4, #0xc4
	add r5, #0x24
	ldr r0, [r4]
	add r1, r5, #0
	bl FUN_02020064
	ldr r1, _021D9418 ; =MOD65_021D941C
	add r0, r7, #0
	bl FUN_0201B6C4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9418: .word MOD65_021D941C
	thumb_func_end MOD65_021D9380

	thumb_func_start MOD65_021D941C
MOD65_021D941C: ; 0x021D941C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r6, [r5, #0x14]
	add r1, sp, #0
	mov r0, #0
	str r0, [r1]
	add r4, r6, #0
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r4, #0xc
	ldr r0, [r4, #0x3c]
	ldr r2, [r5, #0xc]
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	add r2, r0, #0
	mov r0, #2
	add r3, r1, #0
	mov r7, #0
	lsl r0, r0, #0xa
	add r0, r2, r0
	adc r3, r7
	ldr r1, [r4, #0x24]
	lsl r2, r3, #0x14
	lsr r0, r0, #0xc
	orr r0, r2
	sub r0, r1, r0
	str r0, [sp]
	ldr r0, [r4, #0x40]
	ldr r2, [r5, #0xc]
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r3, #2
	ldr r2, [r4, #0x28]
	add r4, r7, #0
	lsl r3, r3, #0xa
	add r3, r0, r3
	adc r1, r4
	lsl r0, r1, #0x14
	lsr r1, r3, #0xc
	orr r1, r0
	sub r0, r2, r1
	str r0, [sp, #4]
	add r0, r6, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r1, sp, #0
	bl FUN_02020064
	mov r0, #1
	ldr r1, [r5, #0xc]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [r5, #0xc]
	ldr r0, [r5, #4]
	sub r0, r0, #1
	str r0, [r5, #4]
	bne _021D94A8
	add r6, #0xc4
	ldr r0, [r6]
	add r1, r7, #0
	bl FUN_020200A0
	add r0, r5, #0
	bl MOD65_021D9130
_021D94A8:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD65_021D941C

	thumb_func_start MOD65_021D94AC
MOD65_021D94AC: ; 0x021D94AC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r1, #0
	ldr r6, [r5, #0x14]
	add r7, r0, #0
	add r3, sp, #0xc
	mov r0, #0
	str r0, [r3]
	str r0, [r3, #4]
	str r0, [r3, #8]
	mov r2, #0x18
	mov r1, #2
	add r4, r6, #0
	mov r0, #0xe
	str r2, [r5, #4]
	lsl r1, r1, #0x12
	add r4, #0xc
	str r1, [r6, #0xc]
	lsl r0, r0, #0x10
	str r0, [r4, #4]
	str r1, [r4, #0xc]
	lsl r0, r2, #0xe
	str r0, [r4, #0x10]
	add r0, r4, #0
	add r0, #0xc
	add r1, r4, #0
	add r2, r3, #0
	bl VEC_Subtract
	ldr r0, [r5, #4]
	cmp r0, #0
	ble _021D94FE
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D950C
_021D94FE:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D950C:
	bl _ffix
	add r1, r4, #0
	add r3, r0, #0
	add r0, sp, #0
	add r1, #0x18
	add r2, sp, #0xc
	bl MOD65_021D89C4
	ldr r0, [r5, #4]
	cmp r0, #0
	ble _021D9536
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D9544
_021D9536:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D9544:
	bl _ffix
	add r1, r0, #0
	mov r0, #0x2d
	lsl r0, r0, #0xe
	bl FX_Div
	str r0, [r4, #0x48]
	ldr r0, [r5, #4]
	cmp r0, #0
	ble _021D956C
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D957A
_021D956C:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D957A:
	bl _ffix
	add r1, r0, #0
	mov r0, #1
	lsl r0, r0, #0xc
	bl FX_Div
	add r6, #0xc4
	str r0, [r4, #0x4c]
	ldr r0, [r6]
	add r1, r4, #0
	bl FUN_02020044
	ldr r1, _021D95A0 ; =MOD65_021D95A4
	add r0, r7, #0
	bl FUN_0201B6C4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D95A0: .word MOD65_021D95A4
	thumb_func_end MOD65_021D94AC

	thumb_func_start MOD65_021D95A4
MOD65_021D95A4: ; 0x021D95A4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r6, [r5, #0x14]
	ldr r2, [r5, #0xc]
	add r4, r6, #0
	add r4, #0xc
	ldr r0, [r4, #0x18]
	asr r3, r2, #0x1f
	asr r1, r0, #0x1f
	bl _ll_mul
	add r2, r0, #0
	mov r0, #2
	add r3, r1, #0
	mov r7, #0
	lsl r0, r0, #0xa
	add r0, r2, r0
	adc r3, r7
	ldr r1, [r6, #0xc]
	lsl r2, r3, #0x14
	lsr r0, r0, #0xc
	orr r0, r2
	add r0, r1, r0
	str r0, [sp]
	ldr r0, [r4, #0x1c]
	ldr r2, [r5, #0xc]
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	add r2, r0, #0
	mov r0, #2
	add r3, r1, #0
	lsl r0, r0, #0xa
	add r0, r2, r0
	adc r3, r7
	ldr r1, [r4, #4]
	lsl r2, r3, #0x14
	lsr r0, r0, #0xc
	orr r0, r2
	add r0, r1, r0
	str r0, [sp, #4]
	ldr r0, [r4, #0x48]
	ldr r2, [r5, #0xc]
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #2
	add r3, r7, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	lsl r0, r1, #4
	lsr r0, r0, #0x10
	bl Sin_Wrap
	ldr r2, _021D9678 ; =0xFFFC0000
	asr r1, r0, #0x1f
	asr r3, r2, #0x12
	bl _ll_mul
	add r3, r7, #0
	mov r7, #2
	add r2, r1, #0
	lsl r7, r7, #0xa
	add r0, r0, r7
	adc r2, r3
	lsl r2, r2, #0x14
	lsr r0, r0, #0xc
	orr r0, r2
	asr r4, r0, #0x1f
	lsr r2, r0, #0x14
	lsl r4, r4, #0xc
	orr r4, r2
	lsl r0, r0, #0xc
	add r2, r0, r7
	adc r4, r3
	ldr r1, [sp, #4]
	lsl r0, r4, #0x14
	lsr r2, r2, #0xc
	orr r2, r0
	add r0, r1, r2
	add r6, #0xc4
	str r0, [sp, #4]
	ldr r0, [r6]
	add r1, sp, #0
	bl FUN_02020044
	ldr r1, [r5, #0xc]
	lsl r0, r7, #1
	add r0, r1, r0
	str r0, [r5, #0xc]
	ldr r0, [r5, #4]
	sub r0, r0, #1
	str r0, [r5, #4]
	bne _021D9674
	add r0, r5, #0
	bl MOD65_021D9130
_021D9674:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D9678: .word 0xFFFC0000
	thumb_func_end MOD65_021D95A4

	thumb_func_start MOD65_021D967C
MOD65_021D967C: ; 0x021D967C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r1, #0
	ldr r6, [r5, #0x14]
	add r7, r0, #0
	add r4, r6, #0
	mov r1, #0x18
	mov r0, #1
	add r4, #0x68
	str r1, [r5, #4]
	lsl r0, r0, #0xc
	str r0, [r4, #0x24]
	str r0, [r4, #0x28]
	lsl r0, r1, #8
	str r0, [r4, #0x30]
	str r0, [r4, #0x34]
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0x30
	add r1, #0x24
	add r2, sp, #0xc
	bl VEC_Subtract
	ldr r0, [r5, #4]
	cmp r0, #0
	ble _021D96C2
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D96D0
_021D96C2:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D96D0:
	bl _ffix
	add r4, #0x3c
	add r3, r0, #0
	add r0, sp, #0
	add r1, r4, #0
	add r2, sp, #0xc
	bl MOD65_021D89C4
	add r0, r6, #0
	add r0, #0xc8
	mov r1, #0xc
	add r2, r1, #0
	ldr r0, [r0]
	add r2, #0xf4
	bl FUN_02007558
	add r6, #0xc8
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r6]
	add r2, #0xf3
	bl FUN_02007558
	ldr r1, _021D970C ; =MOD65_021D9710
	add r0, r7, #0
	bl FUN_0201B6C4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D970C: .word MOD65_021D9710
	thumb_func_end MOD65_021D967C

	thumb_func_start MOD65_021D9710
MOD65_021D9710: ; 0x021D9710
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	ldr r6, [r5, #0x14]
	ldr r0, [r5, #0xc]
	add r4, r6, #0
	add r4, #0x68
	str r0, [sp, #4]
	asr r7, r0, #0x1f
	ldr r0, [r4, #0x40]
	ldr r2, [sp, #4]
	asr r1, r0, #0x1f
	add r3, r7, #0
	bl _ll_mul
	mov r3, #2
	add r2, r0, #0
	lsl r3, r3, #0xa
	add r3, r2, r3
	ldr r2, _021D97C0 ; =0x00000000
	ldr r0, [r4, #0x28]
	adc r1, r2
	lsr r2, r3, #0xc
	lsl r1, r1, #0x14
	orr r2, r1
	add r0, r0, r2
	str r0, [sp]
	ldr r0, [r4, #0x3c]
	ldr r2, [sp, #4]
	asr r1, r0, #0x1f
	add r3, r7, #0
	bl _ll_mul
	mov r2, #2
	add r3, r0, #0
	add r0, r6, #0
	add r7, r1, #0
	add r0, #0xc8
	lsl r2, r2, #0xa
	mov r1, #0xc
	add r3, r3, r2
	ldr r2, _021D97C0 ; =0x00000000
	ldr r4, [r4, #0x24]
	adc r7, r2
	lsl r2, r7, #0x14
	lsr r3, r3, #0xc
	orr r3, r2
	add r2, r4, r3
	ldr r0, [r0]
	asr r2, r2, #4
	bl FUN_02007558
	add r0, r6, #0
	add r0, #0xc8
	ldr r2, [sp]
	ldr r0, [r0]
	mov r1, #0xd
	asr r2, r2, #4
	bl FUN_02007558
	mov r0, #1
	ldr r1, [r5, #0xc]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [r5, #0xc]
	ldr r0, [r5, #4]
	sub r0, r0, #1
	str r0, [r5, #4]
	bne _021D97BA
	add r0, r6, #0
	add r0, #0xc8
	ldr r0, [r0]
	mov r1, #0
	mov r2, #0x80
	bl FUN_02007558
	add r6, #0xc8
	ldr r0, [r6]
	mov r1, #1
	mov r2, #0x60
	bl FUN_02007558
	add r0, r5, #0
	bl MOD65_021D9130
_021D97BA:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D97C0: .word 0x00000000
	thumb_func_end MOD65_021D9710

	thumb_func_start MOD65_021D97C4
MOD65_021D97C4: ; 0x021D97C4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r6, r1, #0
	ldr r4, [r6, #0x14]
	add r7, r0, #0
	mov r0, #0x18
	mov r1, #2
	add r5, r4, #0
	str r0, [r6, #4]
	lsl r1, r1, #0x12
	add r5, #0x68
	str r1, [r4, #0x68]
	lsl r0, r0, #0xe
	str r0, [r5, #4]
	mov r0, #7
	str r1, [r5, #0xc]
	lsl r0, r0, #0x10
	str r0, [r5, #0x10]
	add r0, r5, #0
	add r0, #0xc
	add r1, r5, #0
	add r2, sp, #0xc
	bl VEC_Subtract
	ldr r0, [r6, #4]
	cmp r0, #0
	ble _021D980C
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D981A
_021D980C:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D981A:
	bl _ffix
	add r1, r5, #0
	add r3, r0, #0
	add r0, sp, #0
	add r1, #0x18
	add r2, sp, #0xc
	bl MOD65_021D89C4
	add r0, r4, #0
	add r0, #0xc8
	ldr r2, [r5]
	ldr r0, [r0]
	mov r1, #0
	asr r2, r2, #0xc
	bl FUN_02007558
	add r4, #0xc8
	ldr r2, [r5, #4]
	ldr r0, [r4]
	mov r1, #1
	asr r2, r2, #0xc
	bl FUN_02007558
	ldr r1, _021D9858 ; =MOD65_021D985C
	add r0, r7, #0
	bl FUN_0201B6C4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9858: .word MOD65_021D985C
	thumb_func_end MOD65_021D97C4

	thumb_func_start MOD65_021D985C
MOD65_021D985C: ; 0x021D985C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	ldr r6, [r5, #0x14]
	ldr r7, [r5, #0xc]
	add r4, r6, #0
	str r0, [sp]
	asr r0, r7, #0x1f
	str r0, [sp, #8]
	add r4, #0x68
	ldr r0, [r4, #0x1c]
	ldr r3, [sp, #8]
	asr r1, r0, #0x1f
	add r2, r7, #0
	bl _ll_mul
	mov r3, #2
	add r2, r0, #0
	lsl r3, r3, #0xa
	add r3, r2, r3
	ldr r2, _021D9990 ; =0x00000000
	ldr r0, [r4, #4]
	adc r1, r2
	lsr r2, r3, #0xc
	lsl r1, r1, #0x14
	orr r2, r1
	add r0, r0, r2
	str r0, [sp, #4]
	ldr r0, [r4, #0x18]
	ldr r3, [sp, #8]
	asr r1, r0, #0x1f
	add r2, r7, #0
	bl _ll_mul
	mov ip, r0
	ldr r2, [r6, #0x68]
	add r7, r1, #0
	str r2, [sp, #0xc]
	mov r2, #2
	add r0, r6, #0
	add r0, #0xc8
	mov r1, #0
	mov r3, ip
	lsl r2, r2, #0xa
	add r2, r3, r2
	adc r7, r1
	lsl r3, r7, #0x14
	lsr r2, r2, #0xc
	orr r2, r3
	ldr r3, [sp, #0xc]
	ldr r0, [r0]
	add r2, r3, r2
	asr r2, r2, #0xc
	bl FUN_02007558
	add r0, r6, #0
	add r0, #0xc8
	ldr r2, [sp, #4]
	ldr r0, [r0]
	mov r1, #1
	asr r2, r2, #0xc
	bl FUN_02007558
	add r0, r4, #0
	add r0, #0x50
	ldrh r0, [r0]
	sub r0, r0, #4
	add r1, r0, #0
	mul r1, r0
	mov r0, #0x10
	sub r0, r0, r1
	neg r0, r0
	cmp r0, #0
	ble _021D9902
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D9910
_021D9902:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D9910:
	bl _ffix
	ldr r2, _021D9994 ; =0x00001666
	asr r1, r0, #0x1f
	mov r3, #0
	bl _ll_mul
	add r3, r1, #0
	mov r1, #4
	add r7, r0, #0
	add r0, r6, #0
	add r0, #0xc8
	lsl r2, r1, #9
	add r7, r7, r2
	ldr r2, _021D9990 ; =0x00000000
	ldr r0, [r0]
	adc r3, r2
	lsl r2, r3, #0x14
	lsr r3, r7, #0xc
	orr r3, r2
	asr r2, r3, #0xc
	bl FUN_02007558
	add r0, r4, #0
	add r0, #0x50
	ldrh r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x50
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0x50
	ldrh r0, [r0]
	cmp r0, #8
	bls _021D995E
	add r0, r4, #0
	mov r1, #0
	add r0, #0x50
	strh r1, [r0]
_021D995E:
	mov r0, #1
	ldr r1, [r5, #0xc]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [r5, #0xc]
	ldr r1, [r5, #4]
	sub r0, r1, #1
	str r0, [r5, #4]
	cmp r1, #0
	bne _021D998C
	add r6, #0xc8
	ldr r0, [r6]
	mov r1, #4
	mov r2, #0
	bl FUN_02007558
	mov r0, #0
	add r4, #0x50
	strh r0, [r4]
	ldr r0, [sp]
	ldr r1, _021D9998 ; =MOD65_021D999C
	bl FUN_0201B6C4
_021D998C:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D9990: .word 0x00000000
_021D9994: .word 0x00001666
_021D9998: .word MOD65_021D999C
	thumb_func_end MOD65_021D985C

	thumb_func_start MOD65_021D999C
MOD65_021D999C: ; 0x021D999C
	push {r3, lr}
	ldr r3, [r1, #0x14]
	add r3, #0x68
	add r0, r3, #0
	add r0, #0x50
	ldrh r2, [r0]
	add r0, r3, #0
	add r0, #0x50
	ldrh r0, [r0]
	add r3, #0x50
	add r0, r0, #1
	strh r0, [r3]
	cmp r2, #4
	blo _021D99BE
	add r0, r1, #0
	bl MOD65_021D9130
_021D99BE:
	pop {r3, pc}
	thumb_func_end MOD65_021D999C

	thumb_func_start MOD65_021D99C0
MOD65_021D99C0: ; 0x021D99C0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r1, #0
	ldr r6, [r5, #0x14]
	add r7, r0, #0
	add r4, r6, #0
	mov r1, #8
	mov r0, #6
	add r4, #0x68
	str r1, [r5, #4]
	lsl r0, r0, #0xa
	str r0, [r4, #0x24]
	str r0, [r4, #0x28]
	lsl r0, r1, #9
	str r0, [r4, #0x30]
	str r0, [r4, #0x34]
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0x30
	add r1, #0x24
	add r2, sp, #0xc
	bl VEC_Subtract
	ldr r0, [r5, #4]
	cmp r0, #0
	ble _021D9A06
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D9A14
_021D9A06:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D9A14:
	bl _ffix
	add r4, #0x3c
	add r3, r0, #0
	add r0, sp, #0
	add r1, r4, #0
	add r2, sp, #0xc
	bl MOD65_021D89C4
	add r0, r6, #0
	add r0, #0xc8
	mov r1, #0xc
	ldr r0, [r0]
	lsl r2, r1, #5
	bl FUN_02007558
	add r6, #0xc8
	mov r2, #6
	ldr r0, [r6]
	mov r1, #0xd
	lsl r2, r2, #6
	bl FUN_02007558
	ldr r1, _021D9A50 ; =MOD65_021D9A54
	add r0, r7, #0
	bl FUN_0201B6C4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9A50: .word MOD65_021D9A54
	thumb_func_end MOD65_021D99C0

	thumb_func_start MOD65_021D9A54
MOD65_021D9A54: ; 0x021D9A54
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	ldr r6, [r5, #0x14]
	ldr r0, [r5, #0xc]
	add r4, r6, #0
	add r4, #0x68
	str r0, [sp, #4]
	asr r7, r0, #0x1f
	ldr r0, [r4, #0x40]
	ldr r2, [sp, #4]
	asr r1, r0, #0x1f
	add r3, r7, #0
	bl _ll_mul
	mov r3, #2
	add r2, r0, #0
	lsl r3, r3, #0xa
	add r3, r2, r3
	ldr r2, _021D9B08 ; =0x00000000
	ldr r0, [r4, #0x28]
	adc r1, r2
	lsr r2, r3, #0xc
	lsl r1, r1, #0x14
	orr r2, r1
	add r0, r0, r2
	str r0, [sp]
	ldr r0, [r4, #0x3c]
	ldr r2, [sp, #4]
	asr r1, r0, #0x1f
	add r3, r7, #0
	bl _ll_mul
	mov r2, #2
	add r3, r0, #0
	add r0, r6, #0
	add r7, r1, #0
	add r0, #0xc8
	lsl r2, r2, #0xa
	mov r1, #0xc
	add r3, r3, r2
	ldr r2, _021D9B08 ; =0x00000000
	ldr r4, [r4, #0x24]
	adc r7, r2
	lsl r2, r7, #0x14
	lsr r3, r3, #0xc
	orr r3, r2
	add r2, r4, r3
	ldr r0, [r0]
	asr r2, r2, #4
	bl FUN_02007558
	add r0, r6, #0
	add r0, #0xc8
	ldr r2, [sp]
	ldr r0, [r0]
	mov r1, #0xd
	asr r2, r2, #4
	bl FUN_02007558
	mov r0, #1
	ldr r1, [r5, #0xc]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [r5, #0xc]
	ldr r0, [r5, #4]
	sub r0, r0, #1
	str r0, [r5, #4]
	bne _021D9B02
	add r0, r6, #0
	add r0, #0xc8
	mov r1, #0xc
	add r2, r1, #0
	ldr r0, [r0]
	add r2, #0xf4
	bl FUN_02007558
	add r6, #0xc8
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r6]
	add r2, #0xf3
	bl FUN_02007558
	add r0, r5, #0
	bl MOD65_021D9130
_021D9B02:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9B08: .word 0x00000000
	thumb_func_end MOD65_021D9A54

	thumb_func_start MOD65_021D9B0C
MOD65_021D9B0C: ; 0x021D9B0C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r1, #0
	ldr r6, [r5, #0x14]
	add r7, r0, #0
	mov r0, #8
	add r4, r6, #0
	str r0, [r5, #4]
	lsl r1, r0, #0x10
	mov r0, #7
	add r4, #0x68
	str r1, [r6, #0x68]
	lsl r0, r0, #0x10
	str r0, [r4, #4]
	mov r0, #6
	str r1, [r4, #0xc]
	lsl r0, r0, #0x10
	str r0, [r4, #0x10]
	add r0, r4, #0
	add r0, #0xc
	add r1, r4, #0
	add r2, sp, #0xc
	bl VEC_Subtract
	ldr r0, [r5, #4]
	cmp r0, #0
	ble _021D9B54
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D9B62
_021D9B54:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D9B62:
	bl _ffix
	add r1, r4, #0
	add r3, r0, #0
	add r0, sp, #0
	add r1, #0x18
	add r2, sp, #0xc
	bl MOD65_021D89C4
	ldr r0, [r5, #4]
	cmp r0, #0
	ble _021D9B8C
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D9B9A
_021D9B8C:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D9B9A:
	bl _ffix
	add r1, r0, #0
	mov r0, #0x2d
	lsl r0, r0, #0xe
	bl FX_Div
	str r0, [r4, #0x48]
	add r0, r6, #0
	add r0, #0xc8
	ldr r2, [r4]
	ldr r0, [r0]
	mov r1, #0
	asr r2, r2, #0xc
	bl FUN_02007558
	add r6, #0xc8
	ldr r2, [r4, #4]
	ldr r0, [r6]
	mov r1, #1
	asr r2, r2, #0xc
	bl FUN_02007558
	ldr r1, _021D9BD4 ; =MOD65_021D9BD8
	add r0, r7, #0
	bl FUN_0201B6C4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D9BD4: .word MOD65_021D9BD8
	thumb_func_end MOD65_021D9B0C

	thumb_func_start MOD65_021D9BD8
MOD65_021D9BD8: ; 0x021D9BD8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	ldr r6, [r4, #0x14]
	ldr r7, [r4, #0xc]
	add r5, r6, #0
	str r0, [sp]
	asr r0, r7, #0x1f
	str r0, [sp, #8]
	add r5, #0x68
	ldr r0, [r5, #0x1c]
	ldr r3, [sp, #8]
	asr r1, r0, #0x1f
	add r2, r7, #0
	bl _ll_mul
	mov r3, #2
	add r2, r0, #0
	lsl r3, r3, #0xa
	add r3, r2, r3
	ldr r2, _021D9CD4 ; =0x00000000
	ldr r0, [r5, #4]
	adc r1, r2
	lsr r2, r3, #0xc
	lsl r1, r1, #0x14
	orr r2, r1
	add r0, r0, r2
	str r0, [sp, #4]
	ldr r0, [r5, #0x18]
	ldr r3, [sp, #8]
	asr r1, r0, #0x1f
	add r2, r7, #0
	bl _ll_mul
	mov ip, r0
	ldr r2, [r6, #0x68]
	add r7, r1, #0
	str r2, [sp, #0xc]
	mov r2, #2
	add r0, r6, #0
	add r0, #0xc8
	mov r1, #0
	mov r3, ip
	lsl r2, r2, #0xa
	add r2, r3, r2
	adc r7, r1
	lsl r3, r7, #0x14
	lsr r2, r2, #0xc
	orr r2, r3
	ldr r3, [sp, #0xc]
	ldr r0, [r0]
	add r2, r3, r2
	asr r2, r2, #0xc
	bl FUN_02007558
	add r0, r6, #0
	add r0, #0xc8
	ldr r2, [sp, #4]
	ldr r0, [r0]
	mov r1, #1
	asr r2, r2, #0xc
	bl FUN_02007558
	ldr r0, [r5, #0x48]
	ldr r2, [r4, #0xc]
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	lsl r0, r1, #4
	lsr r0, r0, #0x10
	bl Sin_Wrap
	ldr r2, _021D9CD8 ; =0xFFFFA000
	asr r1, r0, #0x1f
	asr r3, r2, #0xf
	bl _ll_mul
	add r5, r1, #0
	mov r1, #4
	add r3, r0, #0
	add r0, r6, #0
	add r0, #0xc8
	mov r7, #0
	lsl r2, r1, #9
	add r2, r3, r2
	adc r5, r7
	lsl r3, r5, #0x14
	lsr r2, r2, #0xc
	orr r2, r3
	ldr r0, [r0]
	asr r2, r2, #0xc
	bl FUN_02007558
	add r2, r4, #0
	add r2, #0xc
	mov r0, #1
	ldr r1, [r2]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [r2]
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	bne _021D9CCE
	add r6, #0xc8
	ldr r0, [r6]
	mov r1, #4
	add r2, r7, #0
	bl FUN_02007558
	ldr r0, [sp]
	ldr r1, _021D9CDC ; =MOD65_021D9CE0
	bl FUN_0201B6C4
_021D9CCE:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9CD4: .word 0x00000000
_021D9CD8: .word 0xFFFFA000
_021D9CDC: .word MOD65_021D9CE0
	thumb_func_end MOD65_021D9BD8

	thumb_func_start MOD65_021D9CE0
MOD65_021D9CE0: ; 0x021D9CE0
	push {r3, lr}
	ldr r3, [r1, #4]
	add r2, r3, #1
	str r2, [r1, #4]
	cmp r3, #4
	blt _021D9D10
	ldr r2, [r1, #0x14]
	ldr r2, [r2, #8]
	cmp r2, #0
	beq _021D9CFA
	cmp r2, #1
	beq _021D9D02
	b _021D9D0A
_021D9CFA:
	ldr r1, _021D9D14 ; =MOD65_021D9D1C
	bl FUN_0201B6C4
	pop {r3, pc}
_021D9D02:
	ldr r1, _021D9D18 ; =MOD65_021D9DFC
	bl FUN_0201B6C4
	pop {r3, pc}
_021D9D0A:
	add r0, r1, #0
	bl MOD65_021D9130
_021D9D10:
	pop {r3, pc}
	nop
_021D9D14: .word MOD65_021D9D1C
_021D9D18: .word MOD65_021D9DFC
	thumb_func_end MOD65_021D9CE0

	thumb_func_start MOD65_021D9D1C
MOD65_021D9D1C: ; 0x021D9D1C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x14]
	mov r1, #0
	add r0, #0x68
	mov r2, #0x5c
	bl MI_CpuFill8
	mov r0, #3
	str r0, [r4, #4]
	ldr r1, _021D9D3C ; =MOD65_021D9D40
	add r0, r5, #0
	bl FUN_0201B6C4
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D9D3C: .word MOD65_021D9D40
	thumb_func_end MOD65_021D9D1C

	thumb_func_start MOD65_021D9D40
MOD65_021D9D40: ; 0x021D9D40
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r7, [r5, #0x14]
	add r4, r7, #0
	add r4, #0x68
	add r0, r4, #0
	add r0, #0x50
	ldrh r0, [r0]
	sub r0, r0, #4
	add r1, r0, #0
	mul r1, r0
	mov r0, #0x10
	sub r0, r0, r1
	neg r0, r0
	cmp r0, #0
	ble _021D9D72
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D9D80
_021D9D72:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D9D80:
	bl _ffix
	ldr r2, _021D9DF4 ; =0x00001666
	asr r1, r0, #0x1f
	mov r3, #0
	bl _ll_mul
	add r6, r1, #0
	mov r1, #4
	add r3, r0, #0
	add r0, r7, #0
	add r0, #0xc8
	lsl r2, r1, #9
	add r3, r3, r2
	ldr r2, _021D9DF8 ; =0x00000000
	ldr r0, [r0]
	adc r6, r2
	lsl r2, r6, #0x14
	lsr r3, r3, #0xc
	orr r3, r2
	asr r2, r3, #0xc
	bl FUN_02007558
	add r1, r4, #0
	mov r0, #0
	add r1, #0x52
	strh r0, [r1]
	add r1, r4, #0
	add r1, #0x50
	ldrh r1, [r1]
	add r2, r1, #1
	add r1, r4, #0
	add r1, #0x50
	strh r2, [r1]
	add r1, r4, #0
	add r1, #0x50
	ldrh r1, [r1]
	cmp r1, #8
	bls _021D9DD8
	add r4, #0x50
	strh r0, [r4]
	ldr r0, [r5, #4]
	sub r0, r0, #1
	str r0, [r5, #4]
_021D9DD8:
	ldr r0, [r5, #4]
	cmp r0, #0
	bne _021D9DF0
	add r7, #0xc8
	ldr r0, [r7]
	mov r1, #4
	mov r2, #0
	bl FUN_02007558
	add r0, r5, #0
	bl MOD65_021D9130
_021D9DF0:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9DF4: .word 0x00001666
_021D9DF8: .word 0x00000000
	thumb_func_end MOD65_021D9D40

	thumb_func_start MOD65_021D9DFC
MOD65_021D9DFC: ; 0x021D9DFC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x14]
	mov r1, #0
	add r0, #0x68
	mov r2, #0x5c
	bl MI_CpuFill8
	mov r0, #0x20
	str r0, [r4, #4]
	ldr r1, _021D9E1C ; =MOD65_021D9E20
	add r0, r5, #0
	bl FUN_0201B6C4
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D9E1C: .word MOD65_021D9E20
	thumb_func_end MOD65_021D9DFC

	thumb_func_start MOD65_021D9E20
MOD65_021D9E20: ; 0x021D9E20
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldr r6, [r5, #0x14]
	add r4, r6, #0
	add r4, #0x68
	add r0, r4, #0
	add r0, #0x50
	ldrh r0, [r0]
	bl Sin_Wrap
	asr r1, r0, #0x1f
	lsr r2, r0, #0x13
	lsl r1, r1, #0xd
	orr r1, r2
	mov r2, #2
	lsl r3, r0, #0xd
	mov r0, #0
	lsl r2, r2, #0xa
	add r2, r3, r2
	adc r1, r0
	lsl r1, r1, #0x14
	lsr r2, r2, #0xc
	orr r2, r1
	add r1, r4, #0
	add r1, #0x50
	ldrh r3, [r1]
	ldr r1, _021D9E94 ; =0x00000167
	cmp r3, r1
	bls _021D9E5C
	b _021D9E64
_021D9E5C:
	add r0, r4, #0
	add r0, #0x50
	ldrh r0, [r0]
	add r0, #0x5a
_021D9E64:
	add r4, #0x50
	strh r0, [r4]
	add r0, r6, #0
	add r0, #0xc8
	ldr r0, [r0]
	mov r1, #3
	asr r2, r2, #0xc
	bl FUN_02007558
	ldr r0, [r5, #4]
	sub r0, r0, #1
	str r0, [r5, #4]
	bne _021D9E90
	add r6, #0xc8
	ldr r0, [r6]
	mov r1, #3
	mov r2, #0
	bl FUN_02007558
	add r0, r5, #0
	bl MOD65_021D9130
_021D9E90:
	pop {r4, r5, r6, pc}
	nop
_021D9E94: .word 0x00000167
	thumb_func_end MOD65_021D9E20

	thumb_func_start MOD65_021D9E98
MOD65_021D9E98: ; 0x021D9E98
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r4, r2, #0
	mov r1, #0
	mov r2, #0x1c
	add r5, r0, #0
	bl MI_CpuFill8
	bl NNS_G3dInit
	bl G3X_Init
	bl G3X_InitMtxStack
	ldr r0, _021D9F34 ; =0x04000060
	ldr r1, _021D9F38 ; =0xFFFFCFFD
	ldrh r2, [r0]
	ldr r3, _021D9F3C ; =0x0000CFFB
	and r2, r1
	strh r2, [r0]
	ldrh r2, [r0]
	and r2, r3
	strh r2, [r0]
	add r2, r1, #2
	ldrh r6, [r0]
	add r1, r1, #2
	sub r3, #0x1c
	and r6, r2
	mov r2, #8
	orr r2, r6
	strh r2, [r0]
	ldrh r2, [r0]
	and r2, r1
	mov r1, #0x10
	orr r1, r2
	strh r1, [r0]
	ldrh r1, [r0]
	and r1, r3
	strh r1, [r0]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl G3X_SetFog
	mov r0, #0
	ldr r2, _021D9F40 ; =0x00007FFF
	add r1, r0, #0
	mov r3, #0x3f
	str r0, [sp]
	bl G3X_SetClearColor
	ldr r1, _021D9F44 ; =0x04000540
	mov r0, #2
	str r0, [r1]
	ldr r0, _021D9F48 ; =0xBFFF0000
	str r0, [r1, #0x40]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD65_021D9FA0
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	bl MOD65_021DA000
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r1, _021D9F4C ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #1
	orr r0, r2
	strh r0, [r1]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D9F34: .word 0x04000060
_021D9F38: .word 0xFFFFCFFD
_021D9F3C: .word 0x0000CFFB
_021D9F40: .word 0x00007FFF
_021D9F44: .word 0x04000540
_021D9F48: .word 0xBFFF0000
_021D9F4C: .word 0x04000008
	thumb_func_end MOD65_021D9E98

	thumb_func_start MOD65_021D9F50
MOD65_021D9F50: ; 0x021D9F50
	push {r4, lr}
	add r4, r0, #0
	bl FUN_020222AC
	bl Camera_PushLookAtToNNSGlb
	ldr r2, _021D9F84 ; =0x04000440
	mov r3, #0
	add r1, r2, #0
	str r3, [r2]
	add r1, #0x14
	str r3, [r1]
	mov r0, #2
	str r0, [r2]
	str r3, [r1]
	bl NNS_G3dGlbFlushP
	bl NNS_G2dSetupSoftwareSpriteCamera
	ldr r0, [r4, #4]
	bl FUN_02006ED4
	ldr r0, _021D9F88 ; =0x04000540
	mov r1, #1
	str r1, [r0]
	pop {r4, pc}
	.align 2, 0
_021D9F84: .word 0x04000440
_021D9F88: .word 0x04000540
	thumb_func_end MOD65_021D9F50

	thumb_func_start MOD65_021D9F8C
MOD65_021D9F8C: ; 0x021D9F8C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl Camera_Free
	ldr r0, [r4, #4]
	bl FUN_020072E8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD65_021D9F8C

	thumb_func_start MOD65_021D9FA0
MOD65_021D9FA0: ; 0x021D9FA0
	push {r4, r5, lr}
	sub sp, #0x1c
	ldr r5, _021D9FF8 ; =0x021DA41C
	add r4, r0, #0
	add r2, r1, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x10
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, sp, #8
	str r0, [r3]
	mov r0, #0
	strh r0, [r1]
	strh r0, [r1, #2]
	strh r0, [r1, #4]
	strh r0, [r1, #6]
	add r0, r2, #0
	bl Camera_Alloc
	str r0, [r4]
	mov r1, #1
	str r1, [sp]
	ldr r0, [r4]
	ldr r3, _021D9FFC ; =0x000005C1
	str r0, [sp, #4]
	add r0, sp, #0x10
	lsl r1, r1, #0x10
	add r2, sp, #8
	bl Camera_InitWithPosAndAngle
	mov r1, #0x19
	ldr r2, [r4]
	mov r0, #0
	lsl r1, r1, #0xe
	bl Camera_SetPerspectiveClippingPlane
	ldr r0, [r4]
	bl Camera_ClearFixedTarget
	ldr r0, [r4]
	bl Camera_SetWorkPtr
	add sp, #0x1c
	pop {r4, r5, pc}
	.align 2, 0
_021D9FF8: .word MOD65_021DA41C
_021D9FFC: .word 0x000005C1
	thumb_func_end MOD65_021D9FA0

	thumb_func_start MOD65_021DA000
MOD65_021DA000: ; 0x021DA000
	push {r4, r5, r6, lr}
	sub sp, #0x20
	add r5, r0, #0
	add r0, r2, #0
	add r4, r1, #0
	bl FUN_02006D98
	str r0, [r5, #4]
	ldr r1, [r4]
	add r0, sp, #0x10
	mov r2, #2
	bl FUN_02068B68
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, [r5, #4]
	add r1, sp, #0x10
	mov r2, #0x80
	mov r3, #0x60
	bl FUN_020073A0
	ldrb r2, [r4, #8]
	mov r1, #0x23
	add r6, r0, #0
	bl FUN_02007558
	str r6, [r5, #0x18]
	add sp, #0x20
	pop {r4, r5, r6, pc}
	thumb_func_end MOD65_021DA000

	.rodata
	.global MOD65_021DA040
MOD65_021DA040: ; 0x021DA040
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD65_021DA050
MOD65_021DA050: ; 0x021DA050
	.byte 0x28, 0x00, 0x9C, 0x00, 0x36, 0x00, 0xA5, 0x00, 0x31, 0x00, 0xB4, 0x00, 0x1F, 0x00, 0xB4, 0x00
	.byte 0x1A, 0x00, 0xA5, 0x00

	.global MOD65_021DA064
MOD65_021DA064: ; 0x021DA064
	.byte 0x80, 0x00, 0x30, 0x00, 0xC0, 0x00, 0x60, 0x00, 0xA8, 0x00, 0xA2, 0x00, 0x58, 0x00, 0xA4, 0x00
	.byte 0x40, 0x00, 0x60, 0x00, 0x80, 0x00, 0x74, 0x00

	.global MOD65_021DA07C
MOD65_021DA07C: ; 0x021DA07C
	.word MOD65_021D774C, MOD65_021D7800, MOD65_021D7818, MOD65_021D78AC
	.word MOD65_021D78CC, MOD65_021D7920

	.global MOD65_021DA094
MOD65_021DA094: ; 0x021DA094
	.byte 0x22, 0x3E, 0x60, 0xA0, 0x52, 0x6E, 0xA0, 0xE0, 0x94, 0xB0, 0x88, 0xC8, 0x96, 0xB2, 0x38, 0x78
	.byte 0x52, 0x6E, 0x20, 0x60, 0x66, 0x82, 0x60, 0xA0, 0xFF, 0x00, 0x00, 0x00

	.global MOD65_021DA0B0
MOD65_021DA0B0: ; 0x021DA0B0
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD65_021DA0D8
MOD65_021DA0D8: ; 0x021DA0D8
	.byte 0x02, 0x02, 0x04, 0x16, 0x0C, 0x0D, 0x28, 0x00, 0x02, 0x0B, 0x14, 0x0A, 0x02, 0x0D, 0x31, 0x01
	.byte 0x01, 0x02, 0x13, 0x1B, 0x04, 0x0C, 0x45, 0x01, 0x01, 0x1A, 0x11, 0x05, 0x06, 0x0D, 0xB1, 0x01
	.byte 0x01, 0x1A, 0x0D, 0x05, 0x04, 0x0D, 0xCF, 0x01, 0x01, 0x00, 0x00, 0x10, 0x02, 0x0D, 0xE3, 0x01
	.byte 0x04, 0x06, 0x00, 0x14, 0x03, 0x0D, 0x01, 0x00, 0x04, 0x0C, 0x05, 0x08, 0x03, 0x05, 0x41, 0x00
	.byte 0x04, 0x14, 0x0B, 0x08, 0x03, 0x06, 0x59, 0x00, 0x04, 0x11, 0x13, 0x08, 0x03, 0x07, 0x71, 0x00
	.byte 0x04, 0x07, 0x13, 0x08, 0x03, 0x08, 0x89, 0x00, 0x04, 0x04, 0x0B, 0x08, 0x03, 0x09, 0xA1, 0x00
	.byte 0x04, 0x0C, 0x0D, 0x08, 0x03, 0x0A, 0xB9, 0x00

	.global MOD65_021DA140
MOD65_021DA140: ; 0x021DA140
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1E, 0x04
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1D, 0x04, 0x00, 0x03, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1C, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1E, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD65_021DA1E8
MOD65_021DA1E8: ; 0x021DA1E8
	.byte 0x00, 0x00, 0x00, 0x00, 0x69, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x12, 0x00
	.byte 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD65_021DA260
MOD65_021DA260: ; 0x021DA260
	.byte 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x64, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD65_021DA288
MOD65_021DA288: ; 0x021DA288
	.byte 0x01, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD65_021DA2B0
MOD65_021DA2B0: ; 0x021DA2B0
	.byte 0x02, 0x02, 0x04, 0x06, 0x02, 0x06, 0x00, 0x00

	.global MOD65_021DA2B8
MOD65_021DA2B8: ; 0x021DA2B8
	.byte 0x01, 0x1A, 0x0D, 0x05, 0x04, 0x0D, 0xCF, 0x01

	.global MOD65_021DA2C0
MOD65_021DA2C0: ; 0x021DA2C0
	.word 0x00000000, MOD65_021D8704, 0x00000000, 0x00000000
	.byte 0x00, 0x00, 0x03, 0x00, 0x00, 0x08, 0x00, 0x10, 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD65_021DA2E0
MOD65_021DA2E0: ; 0x021DA2E0
	.word 0x00000000, MOD65_021D84F0, MOD65_021D84E4, 0x00000000
	.byte 0x00, 0x00, 0x06, 0x00, 0x00, 0x08, 0x00, 0x10, 0x20, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00

	.global MOD65_021DA300
MOD65_021DA300: ; 0x021DA300
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00

	.global MOD65_021DA314
MOD65_021DA314: ; 0x021DA314
	.word MOD65_021DA45C, MOD65_021DA440, MOD65_021DA494, MOD65_021DA478
	.word 0x00000000, 0x00000000, MOD65_021DA4B0

	.global MOD65_021DA330
MOD65_021DA330: ; 0x021DA330
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00

	.global MOD65_021DA350
MOD65_021DA350: ; 0x021DA350
	.byte 0x01, 0x02, 0x04, 0x00

	.global MOD65_021DA354
MOD65_021DA354: ; 0x021DA354
	.byte 0x01, 0x02, 0x13, 0x1B, 0x04, 0x0F, 0x1F, 0x00

	.global MOD65_021DA35C
MOD65_021DA35C: ; 0x021DA35C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD65_021DA36C
MOD65_021DA36C: ; 0x021DA36C
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00

	.global MOD65_021DA380
MOD65_021DA380: ; 0x021DA380
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00

	.global MOD65_021DA3A0
MOD65_021DA3A0: ; 0x021DA3A0
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00

	.global MOD65_021DA3C8
MOD65_021DA3C8: ; 0x021DA3C8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1D, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD65_021DA41C
MOD65_021DA41C: ; 0x021DA41C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00

	.data
	.global MOD65_021DA440
MOD65_021DA440: ; 0x021DA440
	.asciz "data/porucase_pal.resdat"

	.balign 4, 0
	.global MOD65_021DA45C
MOD65_021DA45C: ; 0x021DA45C
	.asciz "data/porucase_chr.resdat"

	.balign 4, 0
	.global MOD65_021DA478
MOD65_021DA478: ; 0x021DA478
	.asciz "data/porucase_canm.resdat"

	.balign 4, 0
	.global MOD65_021DA494
MOD65_021DA494: ; 0x021DA494
	.asciz "data/porucase_cell.resdat"

	.balign 4, 0
	.global MOD65_021DA4B0
MOD65_021DA4B0: ; 0x021DA4B0
	.asciz "data/porucase_celact.cldat"

	.bss
