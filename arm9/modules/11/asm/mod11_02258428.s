	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD11_02258428
MOD11_02258428: ; 0x02258428
	push {r4, lr}
	mov r1, #7
	mov r0, #5
	lsl r1, r1, #8
	bl AllocFromHeap
	mov r2, #7
	mov r1, #0
	lsl r2, r2, #8
	add r4, r0, #0
	bl MI_CpuFill8
	mov r1, #0
	ldr r0, _0225844C ; =0x0000069F
	mvn r1, r1
	strb r1, [r4, r0]
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0
_0225844C: .word 0x0000069F

	thumb_func_start MOD11_02258450
MOD11_02258450: ; 0x02258450
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	ldr r6, _022584A4 ; =MOD11_0225F97C
	add r5, r0, #0
	add r7, r4, #0
_0225845A:
	add r1, r4, #4
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	add r2, r6, #0
	add r3, r7, #0
	bl InitBgFromTemplate
	add r1, r4, #4
	lsl r1, r1, #0x18
	ldr r2, _022584A8 ; =0x000002FF
	add r0, r5, #0
	lsr r1, r1, #0x18
	bl BgFillTilemapBufferAndCommit
	add r1, r4, #4
	lsl r1, r1, #0x18
	mov r2, #0
	add r0, r5, #0
	lsr r1, r1, #0x18
	add r3, r2, #0
	bl BgSetPosTextAndCommit
	add r1, r4, #4
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	mov r2, #3
	mov r3, #0
	bl BgSetPosTextAndCommit
	add r4, r4, #1
	add r6, #0x1c
	cmp r4, #4
	blo _0225845A
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022584A4: .word MOD11_0225F97C
_022584A8: .word 0x000002FF

	thumb_func_start MOD11_022584AC
MOD11_022584AC: ; 0x022584AC
	push {r4, r5, r6, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r4, #0
_022584B4:
	add r0, r4, #4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, r6, #0
	bl ToggleBgLayer
	add r1, r4, #4
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	bl FreeBgTilemapBuffer
	add r4, r4, #1
	cmp r4, #4
	blo _022584B4
	pop {r4, r5, r6, pc}

	thumb_func_start MOD11_022584D4
MOD11_022584D4: ; 0x022584D4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r0, #0
	add r5, r1, #0
	bl MOD11_02258428
	add r6, r0, #0
	ldr r0, _0225863C ; =0x000006A1
	str r4, [r6]
	strb r5, [r6, r0]
	add r0, r4, #0
	bl MOD11_022300CC
	str r0, [sp, #0x10]
	mov r0, #0xd
	mov r1, #5
	bl FUN_02011744
	ldr r2, _02258640 ; =0x000004C8
	add r1, r6, #0
	str r0, [r6, r2]
	ldr r0, _02258644 ; =MOD11_0225B794
	add r2, #0x56
	bl FUN_0200CA44
	ldr r1, _02258648 ; =0x000006AC
	mov r7, #2
	str r0, [r6, r1]
	mov r4, #0
	lsl r7, r7, #0xa
	b _0225854E
_02258512:
	mov r0, #5
	add r1, r7, #0
	bl AllocFromHeap
	lsl r1, r4, #2
	add r1, r6, r1
	str r0, [r1, #0x3c]
	mov r0, #5
	str r0, [sp]
	ldr r1, _0225864C ; =MOD11_0225F6FC
	lsl r2, r4, #1
	ldrh r1, [r1, r2]
	mov r0, #7
	mov r2, #1
	add r3, sp, #0x18
	bl GfGfxLoader_GetScrnData
	add r5, r0, #0
	lsl r0, r4, #2
	add r0, r6, r0
	ldr r1, [r0, #0x3c]
	ldr r0, [sp, #0x18]
	add r2, r7, #0
	add r0, #0xc
	bl MIi_CpuCopy32
	add r0, r5, #0
	bl FreeToHeap
	add r4, r4, #1
_0225854E:
	cmp r4, #7
	blt _02258512
	mov r1, #2
	mov r0, #5
	lsl r1, r1, #8
	bl AllocFromHeap
	str r0, [r6, #0x58]
	mov r0, #1
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [sp, #0x10]
	mov r1, #7
	mov r2, #0xc3
	mov r3, #5
	bl PaletteData_LoadNarc
	ldr r0, [sp, #0x10]
	mov r1, #1
	bl PaletteData_GetUnfadedBuf
	mov r2, #2
	ldr r1, [r6, #0x58]
	lsl r2, r2, #8
	bl MIi_CpuCopy16
	add r5, r6, #0
	mov r7, #0x46
	mov r4, #0
	add r5, #0x68
	lsl r7, r7, #2
	b _022585A2
_02258592:
	add r0, r4, #0
	mul r0, r7
	add r0, r5, r0
	mov r1, #0xff
	mov r2, #0x18
	bl MI_CpuFill8
	add r4, r4, #1
_022585A2:
	cmp r4, #4
	blt _02258592
	mov r0, #0
	str r0, [sp, #0xc]
	mov r7, #6
	b _022585DE
_022585AE:
	mov r0, #0x46
	ldr r1, [sp, #0xc]
	lsl r0, r0, #2
	mul r0, r1
	mov r5, #0
	add r4, r6, r0
	b _022585D4
_022585BC:
	add r0, r7, #0
	bl FUN_020799E8
	add r1, r0, #0
	mov r0, #5
	bl AllocFromHeap
	lsl r1, r5, #2
	add r1, r4, r1
	add r1, #0x80
	str r0, [r1]
	add r5, r5, #1
_022585D4:
	cmp r5, #4
	blt _022585BC
	ldr r0, [sp, #0xc]
	add r0, r0, #1
	str r0, [sp, #0xc]
_022585DE:
	ldr r0, [sp, #0xc]
	cmp r0, #4
	blt _022585AE
	mov r0, #5
	mov r1, #0x20
	bl AllocFromHeap
	str r0, [r6, #0x5c]
	mov r0, #5
	mov r1, #0x20
	bl AllocFromHeap
	str r0, [r6, #0x60]
	ldr r1, [r6, #0x5c]
	ldr r0, [r6, #0x58]
	mov r2, #0x20
	bl MIi_CpuCopy16
	mov r0, #7
	mov r1, #0xca
	add r2, sp, #0x14
	mov r3, #5
	bl GfGfxLoader_GetPlttData
	add r4, r0, #0
	ldr r0, [sp, #0x14]
	ldr r1, [r6, #0x60]
	ldr r0, [r0, #0xc]
	mov r2, #0x20
	bl MIi_CpuCopy16
	add r0, r4, #0
	bl FreeToHeap
	bl FUN_02002BE4
	bl FUN_02002C04
	ldr r0, _02258650 ; =MOD11_0225B824
	ldr r2, _02258654 ; =0x0000D6D8
	add r1, r6, #0
	bl FUN_0200CA44
	str r0, [r6, #0x64]
	add r0, r6, #0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0225863C: .word 0x000006A1
_02258640: .word 0x000004C8
_02258644: .word MOD11_0225B794
_02258648: .word 0x000006AC
_0225864C: .word MOD11_0225F6FC
_02258650: .word MOD11_0225B824
_02258654: .word 0x0000D6D8

	thumb_func_start MOD11_02258658
MOD11_02258658: ; 0x02258658
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl MOD11_0225ACB0
	add r0, r6, #0
	bl MOD11_02258B10
	add r0, r6, #0
	bl MOD11_022587A8
	ldr r0, _022586B4 ; =0x000004C8
	ldr r0, [r6, r0]
	bl FUN_020117BC
	ldr r0, _022586B8 ; =0x000006AC
	ldr r0, [r6, r0]
	bl FUN_0200CAB4
	mov r4, #0
	add r5, r6, #0
_02258680:
	ldr r0, [r5, #0x3c]
	bl FreeToHeap
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #7
	blt _02258680
	ldr r0, [r6, #0x58]
	bl FreeToHeap
	add r0, r6, #0
	bl MOD11_0225A6B0
	ldr r0, [r6, #0x5c]
	bl FreeToHeap
	ldr r0, [r6, #0x60]
	bl FreeToHeap
	ldr r0, [r6, #0x64]
	bl FUN_0200CAB4
	add r0, r6, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
	.align 2, 0
_022586B4: .word 0x000004C8
_022586B8: .word 0x000006AC

	thumb_func_start MOD11_022586BC
MOD11_022586BC: ; 0x022586BC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r7, r0, #0
	ldr r0, [r7]
	bl MOD11_02230078
	add r6, r0, #0
	ldr r0, [r7]
	bl MOD11_02230080
	add r4, r0, #0
	ldr r0, [r7]
	bl MOD11_0222FF68
	add r5, r0, #0
	ldr r0, [r7]
	bl MOD11_022300CC
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #5
	str r0, [sp, #0xc]
	mov r0, #7
	mov r1, #0x11
	add r2, r5, #0
	mov r3, #4
	bl GfGfxLoader_LoadCharData
	ldr r2, _02258790 ; =0x00004E2D
	add r0, r6, #0
	add r1, r4, #0
	add r3, r2, #0
	bl FUN_0206E1D4
	ldr r0, [r7]
	bl MOD11_022300CC
	mov r1, #2
	str r1, [sp]
	ldr r1, _02258794 ; =0x00004E30
	add r2, r6, #0
	str r1, [sp, #4]
	mov r1, #3
	add r3, r4, #0
	bl FUN_0206E198
	mov r5, #0
_02258726:
	ldr r0, _02258798 ; =0x00004E35
	add r1, r4, #0
	add r0, r5, r0
	str r0, [sp]
	add r0, r6, #0
	mov r2, #2
	mov r3, #0
	bl FUN_0206E130
	add r5, r5, #1
	cmp r5, #4
	blt _02258726
	ldr r0, [r7]
	bl MOD11_0222FF74
	mov r1, #1
	lsl r1, r1, #0xa
	tst r0, r1
	beq _0225878C
	ldr r0, _0225879C ; =0x00004E40
	ldr r3, _022587A0 ; =0x00004FB2
	str r0, [sp]
	add r0, r3, #0
	str r3, [sp, #4]
	sub r0, #0xb
	str r0, [sp, #8]
	ldr r2, [sp, #0x14]
	add r0, r6, #0
	add r1, r4, #0
	add r3, r3, #6
	bl MOD11_0225D6A4
	ldr r0, _0225879C ; =0x00004E40
	ldr r3, _022587A0 ; =0x00004FB2
	str r0, [sp]
	add r0, r3, #0
	str r3, [sp, #4]
	sub r0, #0xb
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	add r0, r6, #0
	add r1, r4, #0
	mov r2, #5
	add r3, r3, #6
	bl MOD11_0225D73C
	ldr r1, _022587A4 ; =0x000006F8
	str r0, [r7, r1]
_0225878C:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02258790: .word 0x00004E2D
_02258794: .word 0x00004E30
_02258798: .word 0x00004E35
_0225879C: .word 0x00004E40
_022587A0: .word 0x00004FB2
_022587A4: .word 0x000006F8

	thumb_func_start MOD11_022587A8
MOD11_022587A8: ; 0x022587A8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r0, [r7]
	bl MOD11_02230078
	ldr r0, [r7]
	bl MOD11_02230080
	ldr r6, _02258808 ; =0x00004E35
	add r5, r0, #0
	mov r4, #0
_022587BE:
	add r0, r5, #0
	add r1, r4, r6
	bl FUN_0206E21C
	add r4, r4, #1
	cmp r4, #4
	blt _022587BE
	ldr r1, _0225880C ; =0x00004E30
	add r0, r5, #0
	bl FUN_0206E224
	ldr r1, _02258810 ; =0x00004E2D
	add r0, r5, #0
	add r2, r1, #0
	bl FUN_0206E22C
	ldr r0, [r7]
	bl MOD11_0222FF74
	mov r1, #1
	lsl r1, r1, #0xa
	tst r0, r1
	beq _02258806
	ldr r0, _02258814 ; =0x000006F8
	ldr r0, [r7, r0]
	bl MOD11_0225D7B8
	ldr r3, _02258818 ; =0x00004FA7
	ldr r2, _0225881C ; =0x00004E40
	add r1, r3, #0
	str r3, [sp]
	add r0, r5, #0
	add r1, #0x11
	add r3, #0xb
	bl MOD11_0225D714
_02258806:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02258808: .word 0x00004E35
_0225880C: .word 0x00004E30
_02258810: .word 0x00004E2D
_02258814: .word 0x000006F8
_02258818: .word 0x00004FA7
_0225881C: .word 0x00004E40

	thumb_func_start MOD11_02258820
MOD11_02258820: ; 0x02258820
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r7, r0, #0
	str r1, [sp, #0x18]
	str r2, [sp, #0x1c]
	cmp r3, #0
	beq _0225883A
	add r1, r7, #0
	add r0, r3, #0
	add r1, #0x18
	mov r2, #0x22
	bl MI_CpuCopy8
_0225883A:
	ldr r0, _0225893C ; =0x000006A2
	mov r1, #0
	strb r1, [r7, r0]
	ldr r0, [r7]
	bl MOD11_0222FF68
	str r0, [sp, #0x28]
	ldr r0, [r7]
	bl MOD11_02230078
	str r0, [sp, #0x24]
	ldr r0, [r7]
	bl MOD11_02230080
	str r0, [sp, #0x20]
	ldr r0, _02258940 ; =0x0000069F
	ldrsb r2, [r7, r0]
	mov r0, #0
	mvn r0, r0
	cmp r2, r0
	bne _0225886C
	mov r0, #1
	str r0, [sp, #0x1c]
	mov r5, #0
	b _02258874
_0225886C:
	mov r0, #0x30
	ldr r1, _02258944 ; =MOD11_0225FAAC
	mul r0, r2
	add r5, r1, r0
_02258874:
	ldr r0, [sp, #0x18]
	mov r1, #0x30
	ldr r2, _02258944 ; =MOD11_0225FAAC
	mul r1, r0
	add r0, r2, r1
	str r0, [sp, #0x2c]
	ldr r0, [r7]
	bl MOD11_022300CC
	mov r1, #2
	lsl r1, r1, #8
	str r1, [sp]
	ldr r1, [r7, #0x58]
	mov r2, #1
	mov r3, #0
	bl PaletteData_LoadPalette
	ldr r6, [sp, #0x2c]
	mov r4, #0
_0225889A:
	ldrh r2, [r6, #4]
	ldr r0, _02258948 ; =0x0000FFFF
	cmp r2, r0
	beq _022588D0
	ldr r0, [sp, #0x1c]
	cmp r0, #1
	beq _022588AE
	ldrh r0, [r5, #4]
	cmp r2, r0
	beq _022588D0
_022588AE:
	lsl r2, r2, #2
	add r1, r4, #4
	add r2, r7, r2
	lsl r1, r1, #0x18
	mov r3, #2
	ldr r0, [sp, #0x28]
	ldr r2, [r2, #0x3c]
	lsr r1, r1, #0x18
	lsl r3, r3, #0xa
	bl BG_LoadScreenTilemapData
	add r1, r4, #4
	lsl r1, r1, #0x18
	ldr r0, [sp, #0x28]
	lsr r1, r1, #0x18
	bl ScheduleBgTilemapBufferTransfer
_022588D0:
	add r4, r4, #1
	add r6, r6, #2
	add r5, r5, #2
	cmp r4, #4
	blt _0225889A
	ldr r0, [r7]
	bl MOD11_022300CC
	mov r1, #0x1b
	str r1, [sp]
	mov r1, #0x24
	str r1, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	mov r1, #7
	str r1, [sp, #0xc]
	mov r1, #2
	str r1, [sp, #0x10]
	ldr r1, _0225894C ; =0x00004E33
	ldr r2, [sp, #0x24]
	str r1, [sp, #0x14]
	ldr r3, [sp, #0x20]
	mov r1, #3
	bl FUN_0200C0DC
	ldr r1, _02258940 ; =0x0000069F
	ldr r0, [sp, #0x18]
	mov r2, #0xf
	strb r0, [r7, r1]
	mov r0, #4
	str r0, [sp]
	ldr r0, _02258950 ; =0x04001050
	mov r1, #2
	mov r3, #0x1b
	bl G2x_SetBlendAlpha_
	add r0, r7, #0
	bl MOD11_0225ACB0
	ldr r0, [sp, #0x2c]
	ldr r3, [r0, #0x28]
	cmp r3, #0
	beq _0225892E
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x1c]
	add r0, r7, #0
	blx r3
_0225892E:
	ldr r0, _02258954 ; =MOD11_0225B700
	add r1, r7, #0
	mov r2, #0xa
	bl FUN_0200CA98
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225893C: .word 0x000006A2
_02258940: .word 0x0000069F
_02258944: .word MOD11_0225FAAC
_02258948: .word 0x0000FFFF
_0225894C: .word 0x00004E33
_02258950: .word 0x04001050
_02258954: .word MOD11_0225B700

	thumb_func_start MOD11_02258958
MOD11_02258958: ; 0x02258958
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	ldr r1, _02258ADC ; =0x000005D4
	str r0, [sp, #0x14]
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _02258970
	ldr r0, [sp, #0x14]
	add r1, #0x18
	ldr r0, [r0, r1]
	cmp r0, #0
	beq _02258974
_02258970:
	bl GF_AssertFail
_02258974:
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	bl MOD11_02230078
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	bl MOD11_02230080
	add r7, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _02258AE0 ; =0x00004E33
	add r1, r7, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x18]
	mov r2, #0x1b
	mov r3, #0x90
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _02258AE4 ; =0x00004E2B
	add r1, r7, #0
	str r0, [sp, #4]
	ldr r0, [sp, #0x18]
	mov r2, #0x1b
	mov r3, #0x8f
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _02258AE4 ; =0x00004E2B
	add r1, r7, #0
	str r0, [sp, #4]
	ldr r0, [sp, #0x18]
	mov r2, #0x1b
	mov r3, #0x91
	bl FUN_0200C13C
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _02258AE8 ; =0x00004E34
	add r1, r7, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x18]
	mov r2, #0x1b
	mov r3, #0x8d
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _02258AEC ; =0x00004E2C
	add r1, r7, #0
	str r0, [sp, #4]
	ldr r0, [sp, #0x18]
	mov r2, #0x1b
	mov r3, #0x8c
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _02258AEC ; =0x00004E2C
	add r1, r7, #0
	str r0, [sp, #4]
	ldr r0, [sp, #0x18]
	mov r2, #0x1b
	mov r3, #0x8e
	bl FUN_0200C13C
	mov r0, #0
	ldr r4, [sp, #0x14]
	str r0, [sp, #0x1c]
	mov r6, #0xc
	mov r5, #0xf6
_02258A12:
	ldr r0, [sp, #0x18]
	ldr r2, _02258AF0 ; =MOD11_0225F8AC
	add r1, r7, #0
	bl FUN_0200C154
	ldr r1, _02258ADC ; =0x000005D4
	mov r3, #0x11
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	lsl r1, r6, #0x10
	ldr r0, [r0]
	asr r1, r1, #0x10
	mov r2, #0xd
	lsl r3, r3, #0x10
	bl FUN_0200C720
	ldr r0, _02258ADC ; =0x000005D4
	mov r1, #1
	ldr r0, [r4, r0]
	bl FUN_0200C840
	ldr r0, [sp, #0x18]
	ldr r2, _02258AF4 ; =MOD11_0225F8E0
	add r1, r7, #0
	bl FUN_0200C154
	ldr r1, _02258AF8 ; =0x000005EC
	mov r3, #0x11
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	lsl r1, r5, #0x10
	ldr r0, [r0]
	asr r1, r1, #0x10
	mov r2, #9
	lsl r3, r3, #0x10
	bl FUN_0200C720
	ldr r0, [sp, #0x1c]
	add r4, r4, #4
	add r0, r0, #1
	add r6, #0x13
	sub r5, #0xc
	str r0, [sp, #0x1c]
	cmp r0, #6
	blt _02258A12
	ldr r0, [sp, #0x14]
	bl MOD11_02258E30
	ldr r0, [sp, #0x14]
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _02258A82
	bl GF_AssertFail
_02258A82:
	ldr r0, _02258AFC ; =MOD11_02258BE0
	ldr r1, [sp, #0x14]
	ldr r2, _02258B00 ; =0x00000514
	bl FUN_0200CA44
	ldr r1, [sp, #0x14]
	str r0, [r1, #4]
	add r0, r1, #0
	ldr r0, [r0]
	bl MOD11_022300CC
	add r2, r0, #0
	ldr r0, _02258B04 ; =0x00004E3F
	ldr r3, _02258B08 ; =0x00004FB1
	str r0, [sp]
	add r0, r3, #0
	str r3, [sp, #4]
	sub r0, #0xb
	str r0, [sp, #8]
	ldr r0, [sp, #0x18]
	add r1, r7, #0
	add r3, r3, #6
	bl MOD11_0225D3EC
	ldr r0, _02258B04 ; =0x00004E3F
	ldr r3, _02258B08 ; =0x00004FB1
	str r0, [sp]
	add r0, r3, #0
	str r3, [sp, #4]
	sub r0, #0xb
	str r0, [sp, #8]
	mov r2, #5
	str r2, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x18]
	add r1, r7, #0
	add r3, r3, #6
	bl MOD11_0225D484
	ldr r2, _02258B0C ; =0x000006EC
	ldr r1, [sp, #0x14]
	str r0, [r1, r2]
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02258ADC: .word 0x000005D4
_02258AE0: .word 0x00004E33
_02258AE4: .word 0x00004E2B
_02258AE8: .word 0x00004E34
_02258AEC: .word 0x00004E2C
_02258AF0: .word MOD11_0225F8AC
_02258AF4: .word MOD11_0225F8E0
_02258AF8: .word 0x000005EC
_02258AFC: .word MOD11_02258BE0
_02258B00: .word 0x00000514
_02258B04: .word 0x00004E3F
_02258B08: .word 0x00004FB1
_02258B0C: .word 0x000006EC

	thumb_func_start MOD11_02258B10
MOD11_02258B10: ; 0x02258B10
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, _02258BBC ; =0x000005D4
	ldr r1, [r6, r0]
	cmp r1, #0
	beq _02258B24
	add r0, #0x18
	ldr r0, [r6, r0]
	cmp r0, #0
	bne _02258B28
_02258B24:
	bl GF_AssertFail
_02258B28:
	ldr r0, [r6]
	bl MOD11_02230078
	ldr r0, [r6]
	bl MOD11_02230080
	ldr r1, _02258BC0 ; =0x00004E33
	add r7, r0, #0
	bl FUN_0200C358
	ldr r1, _02258BC4 ; =0x00004E2B
	add r0, r7, #0
	bl FUN_0200C378
	ldr r1, _02258BC4 ; =0x00004E2B
	add r0, r7, #0
	bl FUN_0200C388
	ldr r1, _02258BC8 ; =0x00004E34
	add r0, r7, #0
	bl FUN_0200C358
	ldr r1, _02258BCC ; =0x00004E2C
	add r0, r7, #0
	bl FUN_0200C378
	ldr r1, _02258BCC ; =0x00004E2C
	add r0, r7, #0
	bl FUN_0200C388
	ldr r1, _02258BC0 ; =0x00004E33
	add r0, r7, #0
	bl FUN_0200C368
	mov r4, #0
	add r5, r6, #0
_02258B70:
	ldr r0, _02258BBC ; =0x000005D4
	ldr r0, [r5, r0]
	bl FUN_0200C3DC
	ldr r0, _02258BBC ; =0x000005D4
	mov r1, #0
	str r1, [r5, r0]
	add r0, #0x18
	ldr r0, [r5, r0]
	bl FUN_0200C3DC
	ldr r0, _02258BD0 ; =0x000005EC
	mov r1, #0
	str r1, [r5, r0]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _02258B70
	ldr r0, [r6, #4]
	bl FUN_0200CAB4
	ldr r3, _02258BD4 ; =0x00004FA6
	mov r0, #0
	str r0, [r6, #4]
	add r1, r3, #0
	str r3, [sp]
	ldr r2, _02258BD8 ; =0x00004E3F
	add r0, r7, #0
	add r1, #0x11
	add r3, #0xb
	bl MOD11_0225D45C
	ldr r0, _02258BDC ; =0x000006EC
	ldr r0, [r6, r0]
	bl MOD11_0225D508
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02258BBC: .word 0x000005D4
_02258BC0: .word 0x00004E33
_02258BC4: .word 0x00004E2B
_02258BC8: .word 0x00004E34
_02258BCC: .word 0x00004E2C
_02258BD0: .word 0x000005EC
_02258BD4: .word 0x00004FA6
_02258BD8: .word 0x00004E3F
_02258BDC: .word 0x000006EC

	thumb_func_start MOD11_02258BE0
MOD11_02258BE0: ; 0x02258BE0
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, _02258D54 ; =0x00000644
	add r5, r1, #0
	mov r7, #0
	add r4, r5, r0
	mov r6, #0xc
_02258BEC:
	ldrb r0, [r4, #3]
	cmp r0, #4
	bhi _02258C08
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02258BFE: ; jump table
	.short _02258C08 - _02258BFE - 2 ; case 0
	.short _02258C48 - _02258BFE - 2 ; case 1
	.short _02258C5A - _02258BFE - 2 ; case 2
	.short _02258CF2 - _02258BFE - 2 ; case 3
	.short _02258C5A - _02258BFE - 2 ; case 4
_02258C08:
	ldr r0, _02258D58 ; =0x000005D4
	ldr r0, [r5, r0]
	ldr r0, [r0]
	bl FUN_0200C650
	cmp r0, #0
	beq _02258C1C
	ldrb r0, [r4, #2]
	cmp r0, #0x57
	bhs _02258C1E
_02258C1C:
	b _02258D42
_02258C1E:
	mov r0, #0
	strb r0, [r4, #4]
	mov r0, #0xa
	strb r0, [r4, #5]
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r3, r0, #0x1d
	ldrb r2, [r4, #5]
	sub r3, r3, r1
	mov r0, #0x1d
	ror r3, r0
	add r0, r1, r3
	add r0, r2, r0
	strb r0, [r4, #5]
	mov r0, #2
	strb r0, [r4, #7]
	ldrb r0, [r4, #3]
	add r0, r0, #1
	strb r0, [r4, #3]
	b _02258D42
_02258C48:
	ldrb r1, [r4, #5]
	cmp r1, #0
	beq _02258C54
	sub r0, r1, #1
	strb r0, [r4, #5]
	b _02258D42
_02258C54:
	add r0, r0, #1
	strb r0, [r4, #3]
	b _02258D42
_02258C5A:
	ldr r0, _02258D58 ; =0x000005D4
	mov r1, #2
	ldr r0, [r5, r0]
	lsl r1, r1, #0xa
	bl FUN_0200C8BC
	mov r0, #0
	ldrsh r1, [r4, r0]
	mov r0, #6
	lsl r0, r0, #6
	add r0, r1, r0
	strh r0, [r4]
	mov r1, #0
	ldrsh r1, [r4, r1]
	ldr r0, _02258D58 ; =0x000005D4
	mov r3, #0x11
	asr r2, r1, #7
	lsr r2, r2, #0x18
	add r2, r1, r2
	asr r1, r2, #8
	add r1, r1, r6
	lsl r1, r1, #0x10
	ldr r0, [r5, r0]
	asr r1, r1, #0x10
	mov r2, #0xd
	lsl r3, r3, #0x10
	bl FUN_0200C750
	ldrb r0, [r4, #6]
	add r0, r0, #1
	strb r0, [r4, #6]
	ldrb r1, [r4, #6]
	ldrb r0, [r4, #7]
	cmp r1, r0
	blo _02258D42
	mov r0, #0
	strb r0, [r4, #6]
	ldrb r0, [r4, #3]
	cmp r0, #2
	bne _02258CB0
	add r0, r0, #1
	strb r0, [r4, #3]
	b _02258D42
_02258CB0:
	ldr r0, _02258D58 ; =0x000005D4
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_0200C898
	ldr r0, _02258D58 ; =0x000005D4
	lsl r1, r6, #0x10
	mov r3, #0x11
	ldr r0, [r5, r0]
	asr r1, r1, #0x10
	mov r2, #0xd
	lsl r3, r3, #0x10
	bl FUN_0200C750
	mov r0, #0
	strh r0, [r4]
	ldrb r0, [r4, #8]
	cmp r0, #1
	bhs _02258CEA
	add r0, r0, #1
	strb r0, [r4, #8]
	ldrb r0, [r4, #7]
	cmp r0, #1
	bls _02258CE4
	sub r0, r0, #1
	strb r0, [r4, #7]
_02258CE4:
	mov r0, #2
	strb r0, [r4, #3]
	b _02258D42
_02258CEA:
	mov r0, #0
	strb r0, [r4, #8]
	strb r0, [r4, #3]
	b _02258D42
_02258CF2:
	ldr r0, _02258D58 ; =0x000005D4
	ldr r1, _02258D5C ; =0xFFFFF800
	ldr r0, [r5, r0]
	bl FUN_0200C8BC
	mov r0, #0
	ldrsh r1, [r4, r0]
	mov r0, #6
	lsl r0, r0, #6
	sub r0, r1, r0
	strh r0, [r4]
	mov r1, #0
	ldrsh r1, [r4, r1]
	ldr r0, _02258D58 ; =0x000005D4
	mov r3, #0x11
	asr r2, r1, #7
	lsr r2, r2, #0x18
	add r2, r1, r2
	asr r1, r2, #8
	add r1, r1, r6
	lsl r1, r1, #0x10
	ldr r0, [r5, r0]
	asr r1, r1, #0x10
	mov r2, #0xd
	lsl r3, r3, #0x10
	bl FUN_0200C750
	ldrb r0, [r4, #6]
	add r0, r0, #1
	strb r0, [r4, #6]
	ldrb r1, [r4, #7]
	ldrb r0, [r4, #6]
	lsl r1, r1, #1
	cmp r0, r1
	blt _02258D42
	mov r0, #0
	strb r0, [r4, #6]
	ldrb r0, [r4, #3]
	add r0, r0, #1
	strb r0, [r4, #3]
_02258D42:
	add r7, r7, #1
	add r4, #0xa
	add r5, r5, #4
	add r6, #0x13
	cmp r7, #6
	bge _02258D50
	b _02258BEC
_02258D50:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02258D54: .word 0x00000644
_02258D58: .word 0x000005D4
_02258D5C: .word 0xFFFFF800

	thumb_func_start MOD11_02258D60
MOD11_02258D60: ; 0x02258D60
	push {r3, r4}
	ldr r2, _02258D78 ; =0x00000646
	mov r4, #0
_02258D66:
	ldrb r3, [r1, r4]
	add r4, r4, #1
	strb r3, [r0, r2]
	add r0, #0xa
	cmp r4, #6
	blt _02258D66
	pop {r3, r4}
	bx lr
	nop
_02258D78: .word 0x00000646

	thumb_func_start MOD11_02258D7C
MOD11_02258D7C: ; 0x02258D7C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	mov r4, #0
_02258D86:
	ldrb r0, [r6, r4]
	bl MOD11_0225A400
	add r1, r0, #0
	ldr r0, _02258DC8 ; =0x000005D4
	ldr r0, [r5, r0]
	ldr r0, [r0]
	bl FUN_02020130
	ldr r0, _02258DC8 ; =0x000005D4
	ldr r0, [r5, r0]
	ldr r0, [r0]
	bl FUN_0200C59C
	ldrb r0, [r7, r4]
	bl MOD11_0225A400
	add r1, r0, #0
	ldr r0, _02258DCC ; =0x000005EC
	ldr r0, [r5, r0]
	ldr r0, [r0]
	bl FUN_02020130
	ldr r0, _02258DCC ; =0x000005EC
	ldr r0, [r5, r0]
	ldr r0, [r0]
	bl FUN_0200C59C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _02258D86
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02258DC8: .word 0x000005D4
_02258DCC: .word 0x000005EC

	thumb_func_start MOD11_02258DD0
MOD11_02258DD0: ; 0x02258DD0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _02258E28 ; =0x000005D4
	ldr r1, [r5, r0]
	cmp r1, #0
	beq _02258DE4
	add r0, #0x18
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _02258DE8
_02258DE4:
	bl GF_AssertFail
_02258DE8:
	ldr r7, _02258E28 ; =0x000005D4
	mov r6, #0
	add r4, r5, #0
_02258DEE:
	ldr r0, [r4, r7]
	mov r1, #1
	ldr r0, [r0]
	bl FUN_0200C63C
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #6
	blt _02258DEE
	ldr r0, [r5]
	bl MOD11_0222FF74
	mov r1, #1
	tst r0, r1
	beq _02258E24
	ldr r6, _02258E2C ; =0x000005EC
	mov r4, #0
	add r7, r1, #0
_02258E12:
	ldr r0, [r5, r6]
	add r1, r7, #0
	ldr r0, [r0]
	bl FUN_0200C63C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _02258E12
_02258E24:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02258E28: .word 0x000005D4
_02258E2C: .word 0x000005EC

	thumb_func_start MOD11_02258E30
MOD11_02258E30: ; 0x02258E30
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _02258E70 ; =0x000005D4
	ldr r1, [r5, r0]
	cmp r1, #0
	beq _02258E44
	add r0, #0x18
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _02258E48
_02258E44:
	bl GF_AssertFail
_02258E48:
	ldr r7, _02258E70 ; =0x000005D4
	mov r4, #0
	add r6, r7, #0
	add r6, #0x18
_02258E50:
	ldr r0, [r5, r7]
	mov r1, #0
	ldr r0, [r0]
	bl FUN_0200C63C
	ldr r0, [r5, r6]
	mov r1, #0
	ldr r0, [r0]
	bl FUN_0200C63C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _02258E50
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02258E70: .word 0x000005D4

	thumb_func_start MOD11_02258E74
MOD11_02258E74: ; 0x02258E74
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _02258F4C ; =0x0000069F
	mov r6, #0
	ldrsb r1, [r5, r0]
	sub r0, r6, #1
	cmp r1, r0
	bne _02258E88
	bl GF_AssertFail
_02258E88:
	ldr r0, _02258F4C ; =0x0000069F
	ldr r3, _02258F50 ; =MOD11_0225FAAC
	ldrsb r2, [r5, r0]
	mov r1, #0x30
	mul r1, r2
	add r4, r3, r1
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _02258EA2
	add r0, r0, #3
	ldrb r0, [r5, r0]
	cmp r0, #1
	bne _02258EA8
_02258EA2:
	mov r0, #0
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_02258EA8:
	ldr r0, [r4, #0x18]
	cmp r0, #0
	bne _02258EB2
	bl GF_AssertFail
_02258EB2:
	ldr r0, [r5]
	bl MOD11_0222FF74
	mov r1, #1
	lsl r1, r1, #0xa
	tst r0, r1
	beq _02258ECA
	add r0, r5, #0
	bl MOD11_0225C784
	add r7, r0, #0
	b _02258EE4
_02258ECA:
	ldr r0, [r4, #0x14]
	bl FUN_02020988
	add r7, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r7, r0
	bne _02258EE4
	add r0, r5, #0
	bl MOD11_0225B8B0
	add r7, r0, #0
	add r6, r6, #1
_02258EE4:
	mov r0, #0
	mvn r0, r0
	str r0, [sp]
	cmp r7, r0
	bne _02258EF2
	mov r2, #0xff
	b _02258EFE
_02258EF2:
	ldr r1, [r4, #0x18]
	lsl r0, r7, #2
	ldr r0, [r1, r0]
	str r0, [sp]
	ldr r0, [r4, #0x1c]
	ldrb r2, [r0, r7]
_02258EFE:
	ldr r3, [r4, #0x2c]
	cmp r3, #0
	beq _02258F46
	ldr r1, [sp]
	add r0, r5, #0
	blx r3
	mov r1, #0
	mvn r1, r1
	str r0, [sp]
	cmp r0, r1
	beq _02258F46
	ldr r2, [r4, #0x24]
	cmp r2, #0
	beq _02258F20
	add r0, r5, #0
	add r1, r7, #0
	blx r2
_02258F20:
	mov r0, #0x6f
	lsl r0, r0, #4
	add r0, r5, r0
	mov r1, #0
	mov r2, #4
	bl MI_CpuFill8
	ldr r0, _02258F54 ; =0x000006EC
	ldr r0, [r5, r0]
	bl MOD11_0225D648
	cmp r6, #0
	ldr r0, _02258F58 ; =0x000006F4
	ble _02258F42
	mov r1, #1
	strb r1, [r5, r0]
	b _02258F46
_02258F42:
	mov r1, #0
	strb r1, [r5, r0]
_02258F46:
	ldr r0, [sp]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02258F4C: .word 0x0000069F
_02258F50: .word MOD11_0225FAAC
_02258F54: .word 0x000006EC
_02258F58: .word 0x000006F4

	thumb_func_start MOD11_02258F5C
MOD11_02258F5C: ; 0x02258F5C
	push {r3, lr}
	ldr r1, [r0, #8]
	cmp r1, #0
	bne _02258F7E
	ldr r1, [r0, #0xc]
	cmp r1, #0
	bne _02258F7E
	ldr r1, _02258F84 ; =0x00000684
	ldr r1, [r0, r1]
	cmp r1, #0
	bne _02258F7E
	bl MOD11_0225B780
	cmp r0, #1
	bne _02258F7E
	mov r0, #1
	pop {r3, pc}
_02258F7E:
	mov r0, #0
	pop {r3, pc}
	nop
_02258F84: .word 0x00000684

	thumb_func_start MOD11_02258F88
MOD11_02258F88: ; 0x02258F88
	push {r3, lr}
	cmp r0, #0x40
	bgt _02258FBE
	bge _02259014
	cmp r0, #0x10
	bgt _02258FB8
	bge _02258FEC
	cmp r0, #8
	bhi _02259024
	add r2, r0, r0
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02258FA6: ; jump table
	.short _02258FE0 - _02258FA6 - 2 ; case 0
	.short _02258FEC - _02258FA6 - 2 ; case 1
	.short _02258FEC - _02258FA6 - 2 ; case 2
	.short _02259024 - _02258FA6 - 2 ; case 3
	.short _02258FF8 - _02258FA6 - 2 ; case 4
	.short _02259024 - _02258FA6 - 2 ; case 5
	.short _02259024 - _02258FA6 - 2 ; case 6
	.short _02259024 - _02258FA6 - 2 ; case 7
	.short _02258FFC - _02258FA6 - 2 ; case 8
_02258FB8:
	cmp r0, #0x20
	beq _0225901C
	b _02259024
_02258FBE:
	mov r2, #1
	lsl r2, r2, #8
	cmp r0, r2
	bgt _02258FCE
	bge _02259008
	cmp r0, #0x80
	beq _02258FF8
	b _02259024
_02258FCE:
	lsl r1, r2, #1
	cmp r0, r1
	bgt _02258FD8
	beq _02259018
	b _02259024
_02258FD8:
	lsl r1, r2, #2
	cmp r0, r1
	beq _02259020
	b _02259024
_02258FE0:
	cmp r1, #4
	bne _02258FE8
	mov r0, #9
	pop {r3, pc}
_02258FE8:
	mov r0, #8
	pop {r3, pc}
_02258FEC:
	cmp r1, #4
	bne _02258FF4
	mov r0, #6
	pop {r3, pc}
_02258FF4:
	mov r0, #4
	pop {r3, pc}
_02258FF8:
	mov r0, #1
	pop {r3, pc}
_02258FFC:
	cmp r1, #4
	bne _02259004
	mov r0, #7
	pop {r3, pc}
_02259004:
	mov r0, #2
	pop {r3, pc}
_02259008:
	cmp r1, #4
	bne _02259010
	mov r0, #4
	pop {r3, pc}
_02259010:
	mov r0, #6
	pop {r3, pc}
_02259014:
	mov r0, #3
	pop {r3, pc}
_02259018:
	mov r0, #0xa
	pop {r3, pc}
_0225901C:
	mov r0, #5
	pop {r3, pc}
_02259020:
	mov r0, #0xb
	pop {r3, pc}
_02259024:
	bl GF_AssertFail
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD11_0225902C
MOD11_0225902C: ; 0x0225902C
	push {r4, r5}
	ldr r1, _0225908C ; =0x04001000
	ldr r2, _02259090 ; =0xFFFF1FFF
	ldr r3, [r1]
	add r5, r1, #0
	and r3, r2
	lsr r2, r1, #0xd
	orr r2, r3
	str r2, [r1]
	add r5, #0x4a
	ldrh r4, [r5]
	mov r3, #0x3f
	mov r2, #0x1f
	bic r4, r3
	orr r2, r4
	mov r4, #0x20
	orr r2, r4
	strh r2, [r5]
	add r1, #0x48
	ldrh r5, [r1]
	mov r2, #0x1b
	bic r5, r3
	orr r2, r5
	orr r2, r4
	strh r2, [r1]
	mov r1, #0x6e
	lsl r1, r1, #4
	ldr r1, [r0, r1]
	asr r0, r1, #7
	lsr r0, r0, #0x18
	add r0, r1, r0
	asr r1, r0, #8
	mov r0, #0xff
	sub r0, r0, r1
	bpl _02259074
	mov r0, #0
_02259074:
	lsl r1, r0, #8
	mov r0, #0xff
	lsl r0, r0, #8
	and r1, r0
	mov r0, #0xff
	orr r0, r1
	ldr r1, _02259094 ; =0x04001040
	strh r0, [r1]
	mov r0, #0xc0
	strh r0, [r1, #4]
	pop {r4, r5}
	bx lr
	.align 2, 0
_0225908C: .word 0x04001000
_02259090: .word 0xFFFF1FFF
_02259094: .word 0x04001040

	thumb_func_start MOD11_02259098
MOD11_02259098: ; 0x02259098
	push {r4, lr}
	lsl r4, r2, #8
	mov r2, #0x6e
	add r3, r0, #0
	lsl r2, r2, #4
	ldr r0, [r3, r2]
	cmp r0, r4
	beq _022590BC
	add r0, r2, #4
	str r1, [r3, r0]
	add r2, #8
	str r4, [r3, r2]
	mov r2, #0x4b
	ldr r0, _022590C0 ; =MOD11_022590C4
	add r1, r3, #0
	lsl r2, r2, #4
	bl FUN_0200CA44
_022590BC:
	pop {r4, pc}
	nop
_022590C0: .word MOD11_022590C4

	thumb_func_start MOD11_022590C4
MOD11_022590C4: ; 0x022590C4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	str r0, [sp]
	ldr r0, [r5]
	mov r4, #0
	bl MOD11_0222FF68
	add r7, r0, #0
	mov r0, #0x6e
	lsl r0, r0, #4
	add r1, r0, #4
	ldr r2, [r5, r0]
	ldr r1, [r5, r1]
	add r1, r2, r1
	str r1, [r5, r0]
	add r1, r0, #4
	ldr r1, [r5, r1]
	cmp r1, #0
	bgt _022590F6
	add r2, r0, #0
	add r2, #8
	ldr r2, [r5, r2]
	ldr r0, [r5, r0]
	cmp r0, r2
	ble _02259106
_022590F6:
	cmp r1, #0
	ble _0225910E
	ldr r0, _0225915C ; =0x000006E8
	ldr r2, [r5, r0]
	sub r0, #8
	ldr r0, [r5, r0]
	cmp r0, r2
	blt _0225910E
_02259106:
	mov r0, #0x6e
	lsl r0, r0, #4
	str r2, [r5, r0]
	mov r4, #1
_0225910E:
	mov r3, #0x6e
	lsl r3, r3, #4
	ldr r3, [r5, r3]
	add r0, r7, #0
	asr r6, r3, #7
	lsr r6, r6, #0x18
	add r6, r3, r6
	mov r1, #6
	mov r2, #0
	asr r3, r6, #8
	bl BgSetPosTextAndCommit
	add r0, r5, #0
	bl MOD11_0225902C
	cmp r4, #1
	bne _0225915A
	ldr r2, _02259160 ; =0x000002FF
	add r0, r7, #0
	mov r1, #7
	bl BgFillTilemapBufferAndCommit
	mov r0, #7
	mov r1, #0
	bl ToggleBgLayer
	mov r0, #7
	mov r1, #0
	bl SetBgPriority
	ldr r2, _02259164 ; =0x04001000
	ldr r0, _02259168 ; =0xFFFF1FFF
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	ldr r0, [sp]
	bl FUN_0200CAB4
_0225915A:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225915C: .word 0x000006E8
_02259160: .word 0x000002FF
_02259164: .word 0x04001000
_02259168: .word 0xFFFF1FFF

	thumb_func_start MOD11_0225916C
MOD11_0225916C: ; 0x0225916C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	ldr r0, _02259240 ; =0x000006A2
	mov r1, #1
	strb r1, [r5, r0]
	ldr r1, _02259244 ; =0x0400104A
	mov r4, #0x3f
	ldrh r2, [r1]
	mov r0, #0xf
	mov r7, #0xc
	bic r2, r4
	orr r0, r2
	mov r2, #0x20
	orr r0, r2
	strh r0, [r1]
	sub r0, r1, #2
	ldrh r3, [r0]
	bic r3, r4
	orr r3, r7
	orr r3, r2
	strh r3, [r0]
	ldrh r4, [r0]
	ldr r3, _02259248 ; =0xFFFFC0FF
	lsl r2, r2, #8
	and r4, r3
	lsl r3, r7, #8
	orr r3, r4
	orr r2, r3
	strh r2, [r0]
	add r2, r1, #0
	mov r0, #0xff
	sub r2, #0xa
	strh r0, [r2]
	mov r3, #0x90
	sub r2, r1, #6
	strh r3, [r2]
	add r2, r1, #0
	sub r2, #8
	strh r0, [r2]
	sub r0, r1, #4
	ldr r2, _0225924C ; =0x000090C0
	sub r1, #0x4a
	strh r2, [r0]
	ldr r2, [r1]
	ldr r0, _02259250 ; =0xFFFF1FFF
	and r2, r0
	lsl r0, r7, #0xb
	orr r0, r2
	str r0, [r1]
	mov r0, #5
	mov r1, #0x14
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x14
	bl MI_CpuFill8
	str r5, [r4]
	ldr r0, _02259254 ; =0xFFFF9C64
	strb r6, [r4, #0x12]
	strh r0, [r4, #8]
	mov r0, #0xfa
	lsl r0, r0, #4
	strh r0, [r4, #0xa]
	mov r0, #8
	ldrsh r1, [r4, r0]
	ldr r0, _02259258 ; =0x0000639C
	sub r0, r0, r1
	mov r1, #0x64
	bl _s32_div_f
	strh r0, [r4, #0xc]
	mov r0, #0xa
	ldrsh r1, [r4, r0]
	mov r0, #0xfa
	lsl r0, r0, #4
	sub r0, r0, r1
	mov r1, #0x64
	bl _s32_div_f
	strh r0, [r4, #0xe]
	ldr r0, _0225925C ; =0x0000070E
	bl PlaySE
	ldr r0, _02259260 ; =MOD11_0225B438
	ldr r2, _02259264 ; =0x000004BA
	add r1, r4, #0
	bl FUN_0200CA44
	ldr r0, _02259268 ; =MOD11_0225B644
	add r1, r4, #0
	bl Main_SetHBlankIntrCB
	cmp r0, #1
	beq _02259232
	bl GF_AssertFail
_02259232:
	ldr r0, _0225926C ; =MOD11_0225B538
	add r1, r4, #0
	mov r2, #0xa
	bl FUN_0200CA60
	str r0, [r4, #4]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02259240: .word 0x000006A2
_02259244: .word 0x0400104A
_02259248: .word 0xFFFFC0FF
_0225924C: .word 0x000090C0
_02259250: .word 0xFFFF1FFF
_02259254: .word 0xFFFF9C64
_02259258: .word 0x0000639C
_0225925C: .word 0x0000070E
_02259260: .word MOD11_0225B438
_02259264: .word 0x000004BA
_02259268: .word MOD11_0225B644
_0225926C: .word MOD11_0225B538

	thumb_func_start MOD11_02259270
MOD11_02259270: ; 0x02259270
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldrb r4, [r5, #0x18]
	bl MOD11_02259284
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_0225916C
	pop {r3, r4, r5, pc}

	thumb_func_start MOD11_02259284
MOD11_02259284: ; 0x02259284
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r5, r0, #0
	ldr r0, [r5]
	add r6, r5, #0
	ldrb r7, [r5, #0x18]
	add r6, #0x18
	bl MOD11_022300C4
	add r4, r0, #0
	ldr r0, _02259484 ; =0x0000069E
	strb r7, [r5, r0]
	ldr r0, [r5]
	bl MOD11_0222FF74
	mov r1, #0x20
	tst r0, r1
	beq _022592CA
	ldr r1, _02259488 ; =0x000003A3
	add r0, r4, #0
	bl NewString_ReadMsgData
	mov r1, #0xe9
	str r0, [sp, #0x24]
	add r0, r4, #0
	lsl r1, r1, #2
	bl NewString_ReadMsgData
	str r0, [sp, #0x20]
	ldr r1, _0225948C ; =0x000003A5
	add r0, r4, #0
	bl NewString_ReadMsgData
	str r0, [sp, #0x1c]
	b _0225931A
_022592CA:
	ldr r0, [r5]
	bl MOD11_0222FF74
	mov r1, #2
	lsl r1, r1, #8
	tst r0, r1
	beq _022592FA
	ldr r1, _02259490 ; =0x000004C7
	add r0, r4, #0
	bl NewString_ReadMsgData
	mov r1, #0xe9
	str r0, [sp, #0x24]
	add r0, r4, #0
	lsl r1, r1, #2
	bl NewString_ReadMsgData
	str r0, [sp, #0x20]
	ldr r1, _0225948C ; =0x000003A5
	add r0, r4, #0
	bl NewString_ReadMsgData
	str r0, [sp, #0x1c]
	b _0225931A
_022592FA:
	mov r1, #0xe7
	add r0, r4, #0
	lsl r1, r1, #2
	bl NewString_ReadMsgData
	str r0, [sp, #0x24]
	ldr r1, _02259494 ; =0x0000039D
	add r0, r4, #0
	bl NewString_ReadMsgData
	str r0, [sp, #0x20]
	ldr r1, _02259498 ; =0x0000039E
	add r0, r4, #0
	bl NewString_ReadMsgData
	str r0, [sp, #0x1c]
_0225931A:
	ldr r0, [r5]
	add r1, r7, #0
	bl MOD11_0223022C
	add r1, r0, #0
	ldr r0, [r5]
	bl MOD11_02230CB8
	cmp r0, #1
	bne _0225933E
	mov r1, #0x3a
	add r0, r4, #0
	lsl r1, r1, #4
	bl NewString_ReadMsgData
	add r4, r0, #0
	mov r1, #1
	b _0225934A
_0225933E:
	ldr r1, _0225949C ; =0x0000039F
	add r0, r4, #0
	bl NewString_ReadMsgData
	add r4, r0, #0
	mov r1, #0
_0225934A:
	ldr r0, _022594A0 ; =0x000006A3
	mov r3, #2
	strb r1, [r5, r0]
	ldr r0, _022594A4 ; =0x00010203
	ldr r1, _022594A8 ; =0x000004CC
	str r0, [sp]
	ldr r0, _022594AC ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x54
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	ldr r2, [sp, #0x24]
	add r0, r5, #0
	add r1, r5, r1
	bl MOD11_0225A458
	ldr r0, _022594B0 ; =0x00040506
	mov r1, #0x4e
	str r0, [sp]
	mov r3, #2
	lsl r1, r1, #4
	ldr r0, _022594AC ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x28
	str r0, [sp, #0xc]
	mov r0, #0xaa
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	ldr r2, [sp, #0x20]
	add r0, r5, #0
	add r1, r5, r1
	bl MOD11_0225A458
	ldr r0, _022594B4 ; =0x00070809
	ldr r1, _022594B8 ; =0x000004F4
	str r0, [sp]
	mov r3, #2
	ldr r0, _022594AC ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0xd8
	str r0, [sp, #0xc]
	mov r0, #0xaa
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	ldr r2, [sp, #0x1c]
	add r0, r5, #0
	add r1, r5, r1
	bl MOD11_0225A458
	ldr r0, _022594BC ; =0x000A0B0C
	ldr r1, _022594C0 ; =0x00000508
	str r0, [sp]
	mov r3, #2
	ldr r0, _022594AC ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0xb2
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r5, r1
	add r2, r4, #0
	bl MOD11_0225A458
	ldr r0, [sp, #0x24]
	bl String_dtor
	ldr r0, [sp, #0x20]
	bl String_dtor
	ldr r0, [sp, #0x1c]
	bl String_dtor
	add r0, r4, #0
	bl String_dtor
	ldr r0, [r5]
	bl MOD11_0222FF74
	mov r1, #0x22
	lsl r1, r1, #4
	tst r0, r1
	bne _0225947E
	ldrb r1, [r6, #1]
	ldrb r2, [r6, #2]
	ldr r0, [r5]
	bl MOD11_02230014
	add r4, r0, #0
	add r0, r5, #0
	bl MOD11_0225A164
	ldrh r0, [r6, #6]
	mov r3, #4
	add r1, r4, #0
	str r0, [sp]
	ldrb r0, [r6, #3]
	add r2, r7, #0
	str r0, [sp, #4]
	ldrsh r3, [r6, r3]
	add r0, r5, #0
	bl MOD11_0225A270
	add r4, r0, #0
	ldr r0, _022594A8 ; =0x000004CC
	add r1, sp, #0x2c
	ldr r0, [r5, r0]
	add r2, sp, #0x28
	bl FUN_020119A4
	cmp r7, #4
	bne _0225945E
	ldr r0, _022594C4 ; =0x000004DC
	ldr r1, [sp, #0x2c]
	ldrh r0, [r5, r0]
	add r0, #0x10
	add r0, r1, r0
	str r0, [sp, #0x2c]
	b _02259464
_0225945E:
	ldr r0, [sp, #0x2c]
	sub r0, #0x10
	str r0, [sp, #0x2c]
_02259464:
	mov r3, #0x11
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x28]
	lsl r3, r3, #4
	sub r2, r2, r3
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, r4, #0
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	lsl r3, r3, #0xc
	bl FUN_0200C750
_0225947E:
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02259484: .word 0x0000069E
_02259488: .word 0x000003A3
_0225948C: .word 0x000003A5
_02259490: .word 0x000004C7
_02259494: .word 0x0000039D
_02259498: .word 0x0000039E
_0225949C: .word 0x0000039F
_022594A0: .word 0x000006A3
_022594A4: .word 0x00010203
_022594A8: .word 0x000004CC
_022594AC: .word 0x00004E33
_022594B0: .word 0x00040506
_022594B4: .word 0x00070809
_022594B8: .word 0x000004F4
_022594BC: .word 0x000A0B0C
_022594C0: .word 0x00000508
_022594C4: .word 0x000004DC

	thumb_func_start MOD11_022594C8
MOD11_022594C8: ; 0x022594C8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldrb r4, [r5, #0x18]
	bl MOD11_022594DC
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_0225916C
	pop {r3, r4, r5, pc}

	thumb_func_start MOD11_022594DC
MOD11_022594DC: ; 0x022594DC
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	bl MOD11_02259284
	ldr r0, [r5]
	bl MOD11_0222FF68
	mov r1, #0x10
	str r1, [sp]
	mov r1, #0x20
	str r1, [sp, #4]
	mov r1, #8
	str r1, [sp, #8]
	mov r1, #0x11
	str r1, [sp, #0xc]
	ldr r2, _02259534 ; =0x000002FF
	add r4, r0, #0
	mov r1, #4
	mov r3, #0
	bl FillBgTilemapRect
	add r0, r4, #0
	mov r1, #5
	bl ScheduleBgTilemapBufferTransfer
	mov r0, #0x4e
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020119D0
	ldr r0, _02259538 ; =0x000004F4
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020119D0
	ldr r0, _0225953C ; =0x00000508
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020119D0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_02259534: .word 0x000002FF
_02259538: .word 0x000004F4
_0225953C: .word 0x00000508

	thumb_func_start MOD11_02259540
MOD11_02259540: ; 0x02259540
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldrb r4, [r5, #0x18]
	bl MOD11_02259554
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_0225916C
	pop {r3, r4, r5, pc}

	thumb_func_start MOD11_02259554
MOD11_02259554: ; 0x02259554
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	bl MOD11_02259284
	ldr r0, [r5]
	bl MOD11_0222FF68
	mov r1, #0x10
	str r1, [sp]
	mov r1, #0xa
	str r1, [sp, #4]
	mov r1, #8
	str r1, [sp, #8]
	mov r1, #0x11
	str r1, [sp, #0xc]
	ldr r2, _022595C0 ; =0x000002FF
	mov r1, #4
	mov r3, #0
	add r4, r0, #0
	bl FillBgTilemapRect
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r2, _022595C0 ; =0x000002FF
	add r0, r4, #0
	mov r1, #4
	mov r3, #0x16
	bl FillBgTilemapRect
	add r0, r4, #0
	mov r1, #5
	bl ScheduleBgTilemapBufferTransfer
	mov r0, #0x4e
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020119D0
	ldr r0, _022595C4 ; =0x000004F4
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020119D0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_022595C0: .word 0x000002FF
_022595C4: .word 0x000004F4

	thumb_func_start MOD11_022595C8
MOD11_022595C8: ; 0x022595C8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r5, r0, #0
	add r6, r5, #0
	add r6, #0x18
	bne _022595D8
	bl GF_AssertFail
_022595D8:
	ldrb r1, [r6, #0x10]
	ldr r0, _02259854 ; =0x0000069E
	strb r1, [r5, r0]
	ldr r0, [r5]
	bl MOD11_022300C4
	str r0, [sp, #0x1c]
	ldrb r1, [r6, #0x10]
	add r0, r5, #0
	bl MOD11_0225A69C
	str r0, [sp, #0x20]
	add r0, r5, #0
	bl MOD11_0225A9D4
	ldr r0, _02259858 ; =0x00070809
	ldr r1, _0225985C ; =0x000004CC
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	ldr r0, _02259860 ; =0x00004E33
	add r1, r5, r1
	str r0, [sp, #8]
	mov r0, #0x40
	str r0, [sp, #0xc]
	mov r0, #0x2e
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x20]
	mov r2, #0
	add r0, #0x28
	str r0, [sp, #0x18]
	add r0, r5, #0
	mov r3, #2
	bl MOD11_0225A458
	ldr r0, _02259858 ; =0x00070809
	mov r1, #0x4e
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	ldr r0, _02259860 ; =0x00004E33
	lsl r1, r1, #4
	str r0, [sp, #8]
	mov r0, #0xc0
	str r0, [sp, #0xc]
	mov r0, #0x2e
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x20]
	add r1, r5, r1
	add r0, #0x3c
	str r0, [sp, #0x18]
	add r0, r5, #0
	mov r2, #0
	mov r3, #2
	bl MOD11_0225A458
	ldr r0, _02259858 ; =0x00070809
	ldr r1, _02259864 ; =0x000004F4
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	ldr r0, _02259860 ; =0x00004E33
	add r1, r5, r1
	str r0, [sp, #8]
	mov r0, #0x40
	str r0, [sp, #0xc]
	mov r0, #0x6e
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x20]
	mov r2, #0
	add r0, #0x50
	str r0, [sp, #0x18]
	add r0, r5, #0
	mov r3, #2
	bl MOD11_0225A458
	ldr r0, _02259858 ; =0x00070809
	ldr r1, _02259868 ; =0x00000508
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	ldr r0, _02259860 ; =0x00004E33
	add r1, r5, r1
	str r0, [sp, #8]
	mov r0, #0xc0
	str r0, [sp, #0xc]
	mov r0, #0x6e
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x20]
	mov r2, #0
	add r0, #0x64
	str r0, [sp, #0x18]
	add r0, r5, #0
	mov r3, #2
	bl MOD11_0225A458
	ldr r0, [sp, #0x20]
	mov r4, #0
	str r0, [sp, #0x28]
	add r0, #0x78
	str r0, [sp, #0x28]
	ldr r0, _0225985C ; =0x000004CC
	add r7, r5, r0
	ldr r0, [sp, #0x20]
	add r0, #0xc8
	str r0, [sp, #0x20]
	b _02259748
_022596BE:
	add r1, r6, r4
	ldrb r0, [r1, #8]
	ldrb r1, [r1, #0xc]
	bl MOD11_0225B3D4
	str r0, [sp, #0x24]
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, _02259860 ; =0x00004E33
	ldr r1, _0225986C ; =MOD11_0225F73C
	str r0, [sp, #8]
	lsl r0, r4, #2
	ldrh r1, [r1, r0]
	add r2, r4, #0
	add r2, #9
	str r1, [sp, #0xc]
	ldr r1, _0225986C ; =MOD11_0225F73C
	add r0, r1, r0
	ldrh r0, [r0, #2]
	add r1, r4, #0
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x14]
	mov r0, #0x14
	mul r1, r0
	ldr r0, [sp, #0x28]
	add r0, r0, r1
	mov r1, #0x14
	mul r1, r2
	mov r2, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r7, r1
	add r3, r2, #0
	bl MOD11_0225A458
	ldr r0, [sp, #0x24]
	ldr r1, _02259870 ; =MOD11_0225F78C
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, _02259860 ; =0x00004E33
	add r2, r4, #5
	str r0, [sp, #8]
	lsl r0, r4, #2
	ldrh r1, [r1, r0]
	str r1, [sp, #0xc]
	ldr r1, _02259870 ; =MOD11_0225F78C
	add r0, r1, r0
	ldrh r0, [r0, #2]
	add r1, r4, #0
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x14]
	mov r0, #0x14
	mul r1, r0
	ldr r0, [sp, #0x20]
	add r0, r0, r1
	mov r1, #0x14
	mul r1, r2
	mov r2, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r7, r1
	add r3, r2, #0
	bl MOD11_0225A458
	add r4, r4, #1
_02259748:
	cmp r4, #4
	blt _022596BE
	ldr r0, [sp, #0x1c]
	ldr r1, _02259874 ; =0x000003A1
	bl NewString_ReadMsgData
	add r4, r0, #0
	ldr r0, _02259878 ; =0x000A0B0C
	ldr r1, _0225987C ; =0x0000051C
	str r0, [sp]
	mov r3, #2
	ldr r0, _02259860 ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0xb2
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r5, r1
	add r2, r4, #0
	bl MOD11_0225A458
	add r0, r4, #0
	bl String_dtor
	mov r4, #0
	mov r7, #3
	b _022597B0
_0225978A:
	lsl r0, r4, #1
	ldrh r0, [r6, r0]
	cmp r0, #0
	beq _022597A4
	add r1, r7, #0
	bl GetWazaAttr
	add r1, r0, #0
	add r0, r5, #0
	add r2, r4, #0
	bl MOD11_0225AB34
	b _022597AE
_022597A4:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_0225AB50
	b _022597B4
_022597AE:
	add r4, r4, #1
_022597B0:
	cmp r4, #4
	blt _0225978A
_022597B4:
	ldr r0, [r5]
	bl MOD11_0222FF68
	ldrh r0, [r6]
	cmp r0, #0
	bne _022597E2
	ldr r0, _0225985C ; =0x000004CC
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020119D0
	mov r0, #0x53
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020119D0
	mov r0, #0x16
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020119D0
_022597E2:
	ldrh r0, [r6, #2]
	cmp r0, #0
	bne _02259808
	mov r0, #0x4e
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020119D0
	ldr r0, _02259880 ; =0x00000544
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020119D0
	ldr r0, _02259884 ; =0x00000594
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020119D0
_02259808:
	ldrh r0, [r6, #4]
	cmp r0, #0
	bne _0225982C
	ldr r0, _02259864 ; =0x000004F4
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020119D0
	ldr r0, _02259888 ; =0x00000558
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020119D0
	ldr r0, _0225988C ; =0x000005A8
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020119D0
_0225982C:
	ldrh r0, [r6, #6]
	cmp r0, #0
	bne _02259850
	ldr r0, _02259868 ; =0x00000508
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020119D0
	ldr r0, _02259890 ; =0x0000056C
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020119D0
	ldr r0, _02259894 ; =0x000005BC
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020119D0
_02259850:
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02259854: .word 0x0000069E
_02259858: .word 0x00070809
_0225985C: .word 0x000004CC
_02259860: .word 0x00004E33
_02259864: .word 0x000004F4
_02259868: .word 0x00000508
_0225986C: .word MOD11_0225F73C
_02259870: .word MOD11_0225F78C
_02259874: .word 0x000003A1
_02259878: .word 0x000A0B0C
_0225987C: .word 0x0000051C
_02259880: .word 0x00000544
_02259884: .word 0x00000594
_02259888: .word 0x00000558
_0225988C: .word 0x000005A8
_02259890: .word 0x0000056C
_02259894: .word 0x000005BC

	thumb_func_start MOD11_02259898
MOD11_02259898: ; 0x02259898
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldr r0, [r5]
	bl MOD11_022300C4
	mov r1, #0xeb
	lsl r1, r1, #2
	add r6, r0, #0
	bl NewString_ReadMsgData
	add r4, r0, #0
	ldr r1, _0225991C ; =0x000003AD
	add r0, r6, #0
	bl NewString_ReadMsgData
	add r6, r0, #0
	ldr r0, _02259920 ; =0x00010203
	ldr r1, _02259924 ; =0x000004CC
	str r0, [sp]
	mov r3, #2
	ldr r0, _02259928 ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x44
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r5, r1
	add r2, r4, #0
	bl MOD11_0225A458
	ldr r0, _0225992C ; =0x000A0B0C
	mov r1, #0x4e
	str r0, [sp]
	mov r3, #2
	lsl r1, r1, #4
	ldr r0, _02259928 ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x8c
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r5, r1
	add r2, r6, #0
	bl MOD11_0225A458
	add r0, r4, #0
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0225991C: .word 0x000003AD
_02259920: .word 0x00010203
_02259924: .word 0x000004CC
_02259928: .word 0x00004E33
_0225992C: .word 0x000A0B0C

	thumb_func_start MOD11_02259930
MOD11_02259930: ; 0x02259930
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldr r0, [r5]
	bl MOD11_022300C4
	ldr r1, _022599B4 ; =0x0000049D
	add r6, r0, #0
	bl NewString_ReadMsgData
	add r4, r0, #0
	ldr r1, _022599B8 ; =0x0000049E
	add r0, r6, #0
	bl NewString_ReadMsgData
	add r6, r0, #0
	ldr r0, _022599BC ; =0x00010203
	ldr r1, _022599C0 ; =0x000004CC
	str r0, [sp]
	mov r3, #2
	ldr r0, _022599C4 ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x44
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r5, r1
	add r2, r4, #0
	bl MOD11_0225A458
	ldr r0, _022599C8 ; =0x000A0B0C
	mov r1, #0x4e
	str r0, [sp]
	mov r3, #2
	lsl r1, r1, #4
	ldr r0, _022599C4 ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x8c
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r5, r1
	add r2, r6, #0
	bl MOD11_0225A458
	add r0, r4, #0
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	nop
_022599B4: .word 0x0000049D
_022599B8: .word 0x0000049E
_022599BC: .word 0x00010203
_022599C0: .word 0x000004CC
_022599C4: .word 0x00004E33
_022599C8: .word 0x000A0B0C

	thumb_func_start MOD11_022599CC
MOD11_022599CC: ; 0x022599CC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	ldr r0, [r5]
	bl MOD11_022300C4
	add r6, r0, #0
	ldr r0, [r5]
	bl MOD11_02230138
	add r4, r0, #0
	ldr r1, _02259A98 ; =0x000004A2
	add r0, r6, #0
	bl NewString_ReadMsgData
	str r0, [sp, #0x1c]
	ldr r1, _02259A9C ; =0x000004A3
	add r0, r6, #0
	bl NewString_ReadMsgData
	str r0, [sp, #0x20]
	mov r0, #0x64
	mov r1, #5
	bl String_ctor
	add r6, r0, #0
	mov r0, #0x64
	mov r1, #5
	bl String_ctor
	add r7, r0, #0
	ldrh r2, [r5, #0x18]
	add r0, r4, #0
	mov r1, #0
	bl BufferMoveName
	ldr r2, [sp, #0x1c]
	add r0, r4, #0
	add r1, r6, #0
	bl StringExpandPlaceholders
	ldr r2, [sp, #0x20]
	add r0, r4, #0
	add r1, r7, #0
	bl StringExpandPlaceholders
	ldr r0, _02259AA0 ; =0x00010203
	ldr r1, _02259AA4 ; =0x000004CC
	str r0, [sp]
	mov r3, #2
	ldr r0, _02259AA8 ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x44
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r5, r1
	add r2, r6, #0
	bl MOD11_0225A458
	ldr r0, _02259AAC ; =0x000A0B0C
	mov r1, #0x4e
	str r0, [sp]
	mov r3, #2
	lsl r1, r1, #4
	ldr r0, _02259AA8 ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x8c
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r5, r1
	add r2, r7, #0
	bl MOD11_0225A458
	ldr r0, [sp, #0x1c]
	bl String_dtor
	ldr r0, [sp, #0x20]
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	add r0, r7, #0
	bl String_dtor
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_02259A98: .word 0x000004A2
_02259A9C: .word 0x000004A3
_02259AA0: .word 0x00010203
_02259AA4: .word 0x000004CC
_02259AA8: .word 0x00004E33
_02259AAC: .word 0x000A0B0C

	thumb_func_start MOD11_02259AB0
MOD11_02259AB0: ; 0x02259AB0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	ldr r0, [r5]
	bl MOD11_022300C4
	add r6, r0, #0
	ldr r0, [r5]
	bl MOD11_02230138
	add r4, r0, #0
	ldr r1, _02259B7C ; =0x000004C1
	add r0, r6, #0
	bl NewString_ReadMsgData
	str r0, [sp, #0x1c]
	ldr r1, _02259B80 ; =0x000004C2
	add r0, r6, #0
	bl NewString_ReadMsgData
	str r0, [sp, #0x20]
	mov r0, #0x64
	mov r1, #5
	bl String_ctor
	add r6, r0, #0
	mov r0, #0x64
	mov r1, #5
	bl String_ctor
	add r7, r0, #0
	ldrh r2, [r5, #0x18]
	add r0, r4, #0
	mov r1, #0
	bl BufferMoveName
	ldr r2, [sp, #0x1c]
	add r0, r4, #0
	add r1, r6, #0
	bl StringExpandPlaceholders
	ldr r2, [sp, #0x20]
	add r0, r4, #0
	add r1, r7, #0
	bl StringExpandPlaceholders
	ldr r0, _02259B84 ; =0x00010203
	ldr r1, _02259B88 ; =0x000004CC
	str r0, [sp]
	mov r3, #2
	ldr r0, _02259B8C ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x44
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r5, r1
	add r2, r6, #0
	bl MOD11_0225A458
	ldr r0, _02259B90 ; =0x000A0B0C
	mov r1, #0x4e
	str r0, [sp]
	mov r3, #2
	lsl r1, r1, #4
	ldr r0, _02259B8C ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x8c
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r5, r1
	add r2, r7, #0
	bl MOD11_0225A458
	ldr r0, [sp, #0x1c]
	bl String_dtor
	ldr r0, [sp, #0x20]
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	add r0, r7, #0
	bl String_dtor
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_02259B7C: .word 0x000004C1
_02259B80: .word 0x000004C2
_02259B84: .word 0x00010203
_02259B88: .word 0x000004CC
_02259B8C: .word 0x00004E33
_02259B90: .word 0x000A0B0C

	thumb_func_start MOD11_02259B94
MOD11_02259B94: ; 0x02259B94
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	ldr r0, [r5]
	bl MOD11_022300C4
	add r6, r0, #0
	ldr r0, [r5]
	bl MOD11_02230138
	add r4, r0, #0
	ldr r1, _02259C60 ; =0x000004BF
	add r0, r6, #0
	bl NewString_ReadMsgData
	mov r1, #0x13
	str r0, [sp, #0x1c]
	add r0, r6, #0
	lsl r1, r1, #6
	bl NewString_ReadMsgData
	str r0, [sp, #0x20]
	mov r0, #0x64
	mov r1, #5
	bl String_ctor
	add r6, r0, #0
	mov r0, #0x64
	mov r1, #5
	bl String_ctor
	add r7, r0, #0
	ldrh r2, [r5, #0x18]
	add r0, r4, #0
	mov r1, #0
	bl BufferMoveName
	ldr r2, [sp, #0x1c]
	add r0, r4, #0
	add r1, r6, #0
	bl StringExpandPlaceholders
	ldr r2, [sp, #0x20]
	add r0, r4, #0
	add r1, r7, #0
	bl StringExpandPlaceholders
	ldr r0, _02259C64 ; =0x00010203
	ldr r1, _02259C68 ; =0x000004CC
	str r0, [sp]
	mov r3, #2
	ldr r0, _02259C6C ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x44
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r5, r1
	add r2, r6, #0
	bl MOD11_0225A458
	ldr r0, _02259C70 ; =0x000A0B0C
	mov r1, #0x4e
	str r0, [sp]
	mov r3, #2
	lsl r1, r1, #4
	ldr r0, _02259C6C ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x8c
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r5, r1
	add r2, r7, #0
	bl MOD11_0225A458
	ldr r0, [sp, #0x1c]
	bl String_dtor
	ldr r0, [sp, #0x20]
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	add r0, r7, #0
	bl String_dtor
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02259C60: .word 0x000004BF
_02259C64: .word 0x00010203
_02259C68: .word 0x000004CC
_02259C6C: .word 0x00004E33
_02259C70: .word 0x000A0B0C

	thumb_func_start MOD11_02259C74
MOD11_02259C74: ; 0x02259C74
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	add r5, r0, #0
	add r7, r5, #0
	add r7, #0x18
	add r0, r7, #0
	add r0, #0x21
	ldrb r1, [r0]
	mov r0, #0x6a
	lsl r0, r0, #4
	strb r1, [r5, r0]
	add r1, r7, #0
	add r1, #0x20
	ldrb r1, [r1]
	sub r0, r0, #2
	strb r1, [r5, r0]
	ldr r0, [r5]
	bl MOD11_022300C4
	str r0, [sp, #0x2c]
	ldr r0, [r5]
	bl MOD11_02230138
	str r0, [sp, #0x1c]
	add r0, r5, #0
	add r1, sp, #0x40
	mov r2, #0
	bl MOD11_0225ACD4
	add r0, r5, #0
	bl MOD11_0225A164
	add r0, r5, #0
	bl MOD11_0225A5C0
	add r1, sp, #0x38
	ldr r0, [r5]
	add r1, #2
	bl MOD11_02231504
	ldr r0, [r5]
	add r1, sp, #0x34
	bl MOD11_022314E0
	mov r0, #0x18
	mov r1, #5
	bl String_ctor
	str r0, [sp, #0x28]
	ldr r0, _02259E38 ; =0x000004CC
	mov r4, #0
	add r0, r5, r0
	str r0, [sp, #0x30]
	b _02259DEC
_02259CE0:
	add r1, r4, #2
	add r0, sp, #0x34
	ldrb r6, [r0, r1]
	lsl r0, r6, #3
	add r0, r7, r0
	ldrb r1, [r0, #1]
	lsl r0, r1, #0x1d
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _02259DDA
	add r0, sp, #0x40
	ldrb r0, [r0, r4]
	cmp r0, #1
	bne _02259DDA
	lsl r0, r1, #0x1e
	lsr r0, r0, #0x1e
	bne _02259D0E
	ldr r0, [sp, #0x2c]
	ldr r1, _02259E3C ; =0x000003C2
	bl NewString_ReadMsgData
	str r0, [sp, #0x24]
	b _02259D2A
_02259D0E:
	cmp r0, #1
	bne _02259D1E
	ldr r0, [sp, #0x2c]
	ldr r1, _02259E40 ; =0x000003C3
	bl NewString_ReadMsgData
	str r0, [sp, #0x24]
	b _02259D2A
_02259D1E:
	mov r1, #0xf1
	ldr r0, [sp, #0x2c]
	lsl r1, r1, #2
	bl NewString_ReadMsgData
	str r0, [sp, #0x24]
_02259D2A:
	lsl r2, r6, #3
	ldrb r2, [r7, r2]
	ldr r0, [r5]
	add r1, r6, #0
	bl MOD11_02230014
	str r0, [sp, #0x20]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [sp, #0x1c]
	mov r1, #0
	bl BufferBoxMonNickname
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x24]
	bl StringExpandPlaceholders
	mov r0, #1
	tst r0, r4
	beq _02259D5A
	ldr r0, _02259E44 ; =0x00010203
	b _02259D5C
_02259D5A:
	ldr r0, _02259E48 ; =0x00040506
_02259D5C:
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	ldr r0, _02259E4C ; =0x00004E33
	ldr r1, _02259E50 ; =MOD11_0225F7D4
	str r0, [sp, #8]
	lsl r0, r4, #2
	ldrh r1, [r1, r0]
	add r2, r4, #0
	mov r3, #2
	str r1, [sp, #0xc]
	ldr r1, _02259E50 ; =MOD11_0225F7D4
	add r0, r1, r0
	ldrh r0, [r0, #2]
	mov r1, #0x14
	mul r2, r1
	ldr r1, [sp, #0x30]
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	add r1, r1, r2
	str r0, [sp, #0x18]
	ldr r2, [sp, #0x28]
	add r0, r5, #0
	bl MOD11_0225A458
	ldr r0, [sp, #0x24]
	bl String_dtor
	cmp r4, #1
	beq _02259DA2
	cmp r4, #3
	beq _02259DBE
	b _02259DEA
_02259DA2:
	lsl r0, r6, #3
	add r6, r7, r0
	ldrh r0, [r6, #6]
	mov r3, #4
	ldr r1, [sp, #0x20]
	str r0, [sp]
	ldrb r0, [r6, #2]
	mov r2, #3
	str r0, [sp, #4]
	ldrsh r3, [r6, r3]
	add r0, r5, #0
	bl MOD11_0225A270
	b _02259DEA
_02259DBE:
	lsl r0, r6, #3
	add r6, r7, r0
	ldrh r0, [r6, #6]
	mov r3, #4
	ldr r1, [sp, #0x20]
	str r0, [sp]
	ldrb r0, [r6, #2]
	mov r2, #5
	str r0, [sp, #4]
	ldrsh r3, [r6, r3]
	add r0, r5, #0
	bl MOD11_0225A270
	b _02259DEA
_02259DDA:
	add r0, sp, #0x40
	ldrb r0, [r0, r4]
	cmp r0, #0
	bne _02259DEA
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_0225ABA4
_02259DEA:
	add r4, r4, #1
_02259DEC:
	cmp r4, #4
	bge _02259DF2
	b _02259CE0
_02259DF2:
	ldr r0, [sp, #0x28]
	bl String_dtor
	ldr r0, [sp, #0x2c]
	ldr r1, _02259E54 ; =0x000003A2
	bl NewString_ReadMsgData
	add r4, r0, #0
	ldr r0, _02259E58 ; =0x000A0B0C
	mov r3, #2
	str r0, [sp]
	ldr r0, _02259E4C ; =0x00004E33
	str r3, [sp, #4]
	str r0, [sp, #8]
	ldr r0, _02259E5C ; =MOD11_0225F7C4
	add r2, r4, #0
	ldrh r1, [r0, #0x20]
	str r1, [sp, #0xc]
	ldrh r0, [r0, #0x22]
	ldr r1, _02259E60 ; =0x0000051C
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r5, r1
	bl MOD11_0225A458
	add r0, r4, #0
	bl String_dtor
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	nop
_02259E38: .word 0x000004CC
_02259E3C: .word 0x000003C2
_02259E40: .word 0x000003C3
_02259E44: .word 0x00010203
_02259E48: .word 0x00040506
_02259E4C: .word 0x00004E33
_02259E50: .word MOD11_0225F7D4
_02259E54: .word 0x000003A2
_02259E58: .word 0x000A0B0C
_02259E5C: .word MOD11_0225F7C4
_02259E60: .word 0x0000051C

	thumb_func_start MOD11_02259E64
MOD11_02259E64: ; 0x02259E64
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	mov r0, #0xff
	add r5, r1, #0
	str r0, [sp]
	add r0, r5, #1
	cmp r0, #5
	bhi _02259E8C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02259E80: ; jump table
	.short _02259E8C - _02259E80 - 2 ; case 0
	.short _02259E8C - _02259E80 - 2 ; case 1
	.short _02259E90 - _02259E80 - 2 ; case 2
	.short _02259EB4 - _02259E80 - 2 ; case 3
	.short _02259EBA - _02259E80 - 2 ; case 4
	.short _02259EC0 - _02259E80 - 2 ; case 5
_02259E8C:
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
_02259E90:
	ldr r0, _02259F24 ; =0x0000069E
	mov r7, #0
	ldrb r0, [r4, r0]
	add r6, r7, #0
	cmp r0, #0
	beq _02259EA6
	cmp r0, #2
	beq _02259EAA
	cmp r0, #4
	beq _02259EAA
	b _02259EC4
_02259EA6:
	str r0, [sp]
	b _02259EC4
_02259EAA:
	ldr r0, _02259F24 ; =0x0000069E
	ldrb r0, [r4, r0]
	sub r0, r0, #2
	str r0, [sp]
	b _02259EC4
_02259EB4:
	mov r7, #1
	add r6, r7, #0
	b _02259EC4
_02259EBA:
	mov r7, #2
	mov r6, #1
	b _02259EC4
_02259EC0:
	mov r7, #3
	mov r6, #1
_02259EC4:
	add r0, r4, #0
	add r1, r2, #0
	bl MOD11_0225ADD4
	ldr r0, _02259F28 ; =MOD11_0225AE4C
	add r1, r4, #0
	bl MOD11_0225AD80
	ldr r0, _02259F2C ; =MOD11_0225F854
	sub r2, r5, #1
	mov r1, #6
	mul r1, r2
	add r0, r0, r1
	ldr r1, _02259F30 ; =0x000006B4
	lsl r2, r2, #2
	str r0, [r4, r1]
	ldr r0, _02259F34 ; =MOD11_0225F70C
	add r3, r0, r2
	add r0, r1, #4
	str r3, [r4, r0]
	add r0, r1, #0
	mov r3, #1
	add r0, #0xc
	strb r3, [r4, r0]
	add r0, r1, #0
	add r0, #8
	str r5, [r4, r0]
	add r0, r1, #0
	add r0, #0xd
	strb r7, [r4, r0]
	add r3, r1, #0
	ldr r0, [sp]
	add r3, #0xe
	strb r0, [r4, r3]
	add r0, r1, #0
	add r0, #0xf
	strb r6, [r4, r0]
	ldr r0, _02259F38 ; =MOD11_0225F79C
	add r3, r0, r2
	ldrh r2, [r0, r2]
	add r0, r1, #0
	add r0, #0x10
	strh r2, [r4, r0]
	ldrh r0, [r3, #2]
	add r1, #0x12
	strh r0, [r4, r1]
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02259F24: .word 0x0000069E
_02259F28: .word MOD11_0225AE4C
_02259F2C: .word MOD11_0225F854
_02259F30: .word 0x000006B4
_02259F34: .word MOD11_0225F70C
_02259F38: .word MOD11_0225F79C

	thumb_func_start MOD11_02259F3C
MOD11_02259F3C: ; 0x02259F3C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0
	add r4, r1, #0
	mvn r0, r0
	add r1, r2, #0
	cmp r4, r0
	bne _02259F50
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
_02259F50:
	add r2, r5, #0
	add r2, #0x18
	cmp r4, #1
	blt _02259F66
	cmp r4, #4
	bgt _02259F66
	sub r3, r4, #1
	lsl r3, r3, #1
	ldrh r2, [r2, r3]
	cmp r2, #0
	beq _02259FCA
_02259F66:
	sub r0, r4, #1
	cmp r4, #4
	bgt _02259F88
	add r2, r4, #1
	bmi _02259F8C
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02259F7C: ; jump table
	.short _02259F8C - _02259F7C - 2 ; case 0
	.short _02259F8C - _02259F7C - 2 ; case 1
	.short _02259F92 - _02259F7C - 2 ; case 2
	.short _02259F92 - _02259F7C - 2 ; case 3
	.short _02259F92 - _02259F7C - 2 ; case 4
	.short _02259F92 - _02259F7C - 2 ; case 5
_02259F88:
	cmp r4, #0xff
	beq _02259FA2
_02259F8C:
	mov r0, #0
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_02259F92:
	mov r2, #6
	mul r2, r0
	ldr r3, _02259FCC ; =MOD11_0225F86C
	lsl r0, r0, #2
	add r7, r3, r2
	ldr r2, _02259FD0 ; =MOD11_0225F7AC
	add r6, r2, r0
	b _02259FA6
_02259FA2:
	ldr r7, _02259FD4 ; =MOD11_0225F884
	ldr r6, _02259FD8 ; =MOD11_0225F7BC
_02259FA6:
	add r0, r5, #0
	bl MOD11_0225ADD4
	ldr r0, _02259FDC ; =MOD11_0225AF9C
	add r1, r5, #0
	bl MOD11_0225AD80
	ldr r1, _02259FE0 ; =0x000006B4
	mov r2, #3
	str r7, [r5, r1]
	add r0, r1, #4
	str r6, [r5, r0]
	add r0, r1, #0
	add r0, #0xc
	strb r2, [r5, r0]
	add r1, #8
	str r4, [r5, r1]
	add r0, r4, #0
_02259FCA:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02259FCC: .word MOD11_0225F86C
_02259FD0: .word MOD11_0225F7AC
_02259FD4: .word MOD11_0225F884
_02259FD8: .word MOD11_0225F7BC
_02259FDC: .word MOD11_0225AF9C
_02259FE0: .word 0x000006B4

	thumb_func_start MOD11_02259FE4
MOD11_02259FE4: ; 0x02259FE4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0
	add r4, r1, #0
	mvn r0, r0
	cmp r4, r0
	beq _02259FFA
	cmp r4, #1
	beq _02259FFE
	cmp r4, #0xff
	beq _0225A002
_02259FFA:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02259FFE:
	mov r6, #0
	b _0225A004
_0225A002:
	mov r6, #1
_0225A004:
	add r0, r5, #0
	add r1, r2, #0
	bl MOD11_0225ADD4
	ldr r0, _0225A048 ; =MOD11_0225AE4C
	add r1, r5, #0
	bl MOD11_0225AD80
	cmp r4, #1
	ldr r0, _0225A04C ; =0x000006B4
	bne _0225A022
	ldr r1, _0225A050 ; =MOD11_0225F6F6
	str r1, [r5, r0]
	ldr r1, _0225A054 ; =MOD11_0225F6CC
	b _0225A028
_0225A022:
	ldr r1, _0225A058 ; =MOD11_0225F6F0
	str r1, [r5, r0]
	ldr r1, _0225A05C ; =MOD11_0225F6C8
_0225A028:
	add r0, r0, #4
	str r1, [r5, r0]
	mov r0, #0x1b
	mov r1, #6
	lsl r0, r0, #6
	strb r1, [r5, r0]
	sub r1, r0, #4
	str r4, [r5, r1]
	add r1, r0, #1
	strb r6, [r5, r1]
	mov r1, #3
	add r0, r0, #3
	strb r1, [r5, r0]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	nop
_0225A048: .word MOD11_0225AE4C
_0225A04C: .word 0x000006B4
_0225A050: .word MOD11_0225F6F6
_0225A054: .word MOD11_0225F6CC
_0225A058: .word MOD11_0225F6F0
_0225A05C: .word MOD11_0225F6C8

	thumb_func_start MOD11_0225A060
MOD11_0225A060: ; 0x0225A060
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r1, #0
	add r1, sp, #0
	mov r2, #1
	add r4, r0, #0
	bl MOD11_0225ACD4
	cmp r5, #4
	bgt _0225A090
	add r0, r5, #1
	bmi _0225A094
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0225A084: ; jump table
	.short _0225A094 - _0225A084 - 2 ; case 0
	.short _0225A094 - _0225A084 - 2 ; case 1
	.short _0225A09A - _0225A084 - 2 ; case 2
	.short _0225A0AA - _0225A084 - 2 ; case 3
	.short _0225A0BA - _0225A084 - 2 ; case 4
	.short _0225A0CA - _0225A084 - 2 ; case 5
_0225A090:
	cmp r5, #0xff
	beq _0225A0DA
_0225A094:
	add sp, #4
	add r0, r5, #0
	pop {r3, r4, r5, r6, pc}
_0225A09A:
	add r0, sp, #0
	ldrb r0, [r0]
	cmp r0, #0
	bne _0225A116
	mov r0, #0
	add sp, #4
	mvn r0, r0
	pop {r3, r4, r5, r6, pc}
_0225A0AA:
	add r0, sp, #0
	ldrb r0, [r0, #1]
	cmp r0, #0
	bne _0225A116
	mov r0, #0
	add sp, #4
	mvn r0, r0
	pop {r3, r4, r5, r6, pc}
_0225A0BA:
	add r0, sp, #0
	ldrb r0, [r0, #2]
	cmp r0, #0
	bne _0225A116
	mov r0, #0
	add sp, #4
	mvn r0, r0
	pop {r3, r4, r5, r6, pc}
_0225A0CA:
	add r0, sp, #0
	ldrb r0, [r0, #3]
	cmp r0, #0
	bne _0225A116
	mov r0, #0
	add sp, #4
	mvn r0, r0
	pop {r3, r4, r5, r6, pc}
_0225A0DA:
	add r0, r4, #0
	mov r1, #4
	bl MOD11_0225ADD4
	ldr r0, _0225A14C ; =MOD11_0225AE4C
	add r1, r4, #0
	bl MOD11_0225AD80
	ldr r0, _0225A150 ; =MOD11_0225F8A4
	ldr r1, _0225A154 ; =0x000006B4
	ldr r2, _0225A158 ; =MOD11_0225F80C
	str r0, [r4, r1]
	add r0, r1, #4
	str r2, [r4, r0]
	add r0, r1, #0
	mov r2, #4
	add r0, #0xc
	strb r2, [r4, r0]
	add r0, r1, #0
	add r0, #8
	str r5, [r4, r0]
	add r0, r1, #0
	add r0, #0xd
	strb r2, [r4, r0]
	mov r0, #3
	add r1, #0xf
	strb r0, [r4, r1]
	add sp, #4
	add r0, r5, #0
	pop {r3, r4, r5, r6, pc}
_0225A116:
	ldr r0, [r4]
	bl MOD11_0222FF68
	ldr r2, _0225A15C ; =0x000002FF
	add r6, r0, #0
	mov r1, #5
	bl BgFillTilemapBufferAndCommit
	add r0, r6, #0
	mov r1, #5
	bl ScheduleBgTilemapBufferTransfer
	add r0, r4, #0
	add r1, r5, #0
	bl MOD11_0225ADD0
	ldr r0, _0225A160 ; =MOD11_0225B234
	add r1, r4, #0
	bl MOD11_0225AD80
	mov r0, #0x6d
	lsl r0, r0, #4
	str r5, [r4, r0]
	add r0, r5, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_0225A14C: .word MOD11_0225AE4C
_0225A150: .word MOD11_0225F8A4
_0225A154: .word 0x000006B4
_0225A158: .word MOD11_0225F80C
_0225A15C: .word 0x000002FF
_0225A160: .word MOD11_0225B234

	thumb_func_start MOD11_0225A164
MOD11_0225A164: ; 0x0225A164
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r0, [r5]
	bl MOD11_02230078
	add r4, r0, #0
	ldr r0, [r5]
	bl MOD11_02230080
	add r6, r0, #0
	ldr r0, [r5]
	bl MOD11_022300CC
	add r5, r0, #0
	bl FUN_0206B888
	mov r1, #0x13
	str r1, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r1, #3
	str r1, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _0225A1DC ; =0x00004E32
	add r2, r4, #0
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r3, r6, #0
	bl FUN_0200C0DC
	bl FUN_0206B890
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _0225A1E0 ; =0x00004E31
	add r1, r6, #0
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x13
	bl FUN_0200C124
	bl FUN_0206B89C
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _0225A1E0 ; =0x00004E31
	add r1, r6, #0
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x13
	bl FUN_0200C13C
	add sp, #0x18
	pop {r4, r5, r6, pc}
	nop
_0225A1DC: .word 0x00004E32
_0225A1E0: .word 0x00004E31

	thumb_func_start MOD11_0225A1E4
MOD11_0225A1E4: ; 0x0225A1E4
	push {r4, lr}
	ldr r0, [r0]
	bl MOD11_02230080
	ldr r1, _0225A220 ; =0x00004E40
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _0225A224 ; =0x00004E41
	add r0, r4, #0
	bl FUN_0200C358
	ldr r1, _0225A228 ; =0x00004E42
	add r0, r4, #0
	bl FUN_0200C358
	ldr r1, _0225A22C ; =0x00004E31
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _0225A22C ; =0x00004E31
	add r0, r4, #0
	bl FUN_0200C388
	ldr r1, _0225A230 ; =0x00004E32
	add r0, r4, #0
	bl FUN_0200C368
	pop {r4, pc}
	nop
_0225A220: .word 0x00004E40
_0225A224: .word 0x00004E41
_0225A228: .word 0x00004E42
_0225A22C: .word 0x00004E31
_0225A230: .word 0x00004E32

	thumb_func_start MOD11_0225A234
MOD11_0225A234: ; 0x0225A234
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r4, #0
	add r7, r4, #0
_0225A23E:
	ldr r0, _0225A268 ; =0x00000624
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _0225A24E
	bl FUN_0200C3DC
	ldr r0, _0225A268 ; =0x00000624
	str r6, [r5, r0]
_0225A24E:
	ldr r0, _0225A26C ; =0x00000634
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _0225A25E
	bl FUN_0200CAB4
	ldr r0, _0225A26C ; =0x00000634
	str r7, [r5, r0]
_0225A25E:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0225A23E
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225A268: .word 0x00000624
_0225A26C: .word 0x00000634

	thumb_func_start MOD11_0225A270
MOD11_0225A270: ; 0x0225A270
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x50
	add r6, r2, #0
	add r4, r0, #0
	str r1, [sp, #0xc]
	str r3, [sp, #0x10]
	cmp r6, #2
	blt _0225A284
	sub r5, r6, #2
	b _0225A286
_0225A284:
	add r5, r6, #0
_0225A286:
	lsl r0, r5, #2
	add r1, r4, r0
	ldr r0, _0225A3D0 ; =0x00000624
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0225A296
	bl GF_AssertFail
_0225A296:
	lsl r0, r5, #2
	add r1, r4, r0
	ldr r0, _0225A3D4 ; =0x00000634
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0225A2A6
	bl GF_AssertFail
_0225A2A6:
	cmp r6, #5
	bhi _0225A2CE
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0225A2B6: ; jump table
	.short _0225A2C2 - _0225A2B6 - 2 ; case 0
	.short _0225A2CE - _0225A2B6 - 2 ; case 1
	.short _0225A2C2 - _0225A2B6 - 2 ; case 2
	.short _0225A2C6 - _0225A2B6 - 2 ; case 3
	.short _0225A2C2 - _0225A2B6 - 2 ; case 4
	.short _0225A2CA - _0225A2B6 - 2 ; case 5
_0225A2C2:
	ldr r6, _0225A3D8 ; =0x00004E40
	b _0225A2D8
_0225A2C6:
	ldr r6, _0225A3DC ; =0x00004E41
	b _0225A2D8
_0225A2CA:
	ldr r6, _0225A3E0 ; =0x00004E42
	b _0225A2D8
_0225A2CE:
	bl GF_AssertFail
	add sp, #0x50
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0225A2D8:
	ldr r0, [r4]
	bl MOD11_02230078
	str r0, [sp, #0x18]
	ldr r0, [r4]
	bl MOD11_02230080
	str r0, [sp, #0x14]
	ldr r0, [sp, #0xc]
	bl FUN_0206B6C8
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x14]
	mov r2, #0x13
	str r6, [sp, #8]
	bl FUN_0200C00C
	ldr r3, _0225A3E4 ; =MOD11_0225F948
	add r2, sp, #0x1c
	mov r7, #6
_0225A30A:
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	sub r7, r7, #1
	bne _0225A30A
	ldr r0, [r3]
	lsl r3, r5, #2
	str r0, [r2]
	ldr r2, _0225A3E8 ; =MOD11_0225F76C
	str r6, [sp, #0x30]
	ldrh r1, [r2, r3]
	add r0, sp, #0x1c
	strh r1, [r0]
	add r1, r2, r3
	ldrh r1, [r1, #2]
	add r2, sp, #0x1c
	strh r1, [r0, #2]
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x14]
	bl FUN_0200C154
	add r3, sp, #0x1c
	mov r1, #0
	mov r2, #2
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	mov r3, #0x11
	lsl r3, r3, #0x10
	add r6, r0, #0
	bl FUN_0200C750
	ldr r0, [sp, #0xc]
	bl FUN_0206B87C
	add r1, r0, #0
	ldr r0, [r6]
	bl FUN_020202DC
	ldr r0, [sp, #0x10]
	mov r7, #0
	cmp r0, #0
	beq _0225A3A8
	ldr r0, [sp, #0x6c]
	cmp r0, #2
	beq _0225A3A8
	cmp r0, #3
	beq _0225A3A8
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x68]
	lsl r0, r0, #0x10
	lsl r1, r1, #0x10
	lsr r0, r0, #0x10
	lsr r1, r1, #0x10
	mov r2, #0x30
	bl FUN_02079A54
	cmp r0, #4
	bhi _0225A3A0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0225A388: ; jump table
	.short _0225A3A0 - _0225A388 - 2 ; case 0
	.short _0225A39E - _0225A388 - 2 ; case 1
	.short _0225A39A - _0225A388 - 2 ; case 2
	.short _0225A396 - _0225A388 - 2 ; case 3
	.short _0225A392 - _0225A388 - 2 ; case 4
_0225A392:
	mov r7, #1
	b _0225A3A0
_0225A396:
	mov r7, #2
	b _0225A3A0
_0225A39A:
	mov r7, #3
	b _0225A3A0
_0225A39E:
	mov r7, #4
_0225A3A0:
	add r0, r6, #0
	add r1, r7, #0
	bl FUN_0200C5C0
_0225A3A8:
	add r0, r6, #0
	bl FUN_0200C5A8
	lsl r0, r5, #2
	add r1, r4, r0
	ldr r0, _0225A3D0 ; =0x00000624
	ldr r2, _0225A3EC ; =0x00000514
	str r6, [r1, r0]
	ldr r0, _0225A3F0 ; =MOD11_0225A3F4
	add r1, r6, #0
	bl FUN_0200CA44
	lsl r1, r5, #2
	add r2, r4, r1
	ldr r1, _0225A3D4 ; =0x00000634
	str r0, [r2, r1]
	add r0, r6, #0
	add sp, #0x50
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225A3D0: .word 0x00000624
_0225A3D4: .word 0x00000634
_0225A3D8: .word 0x00004E40
_0225A3DC: .word 0x00004E41
_0225A3E0: .word 0x00004E42
_0225A3E4: .word MOD11_0225F948
_0225A3E8: .word MOD11_0225F76C
_0225A3EC: .word 0x00000514
_0225A3F0: .word MOD11_0225A3F4

	thumb_func_start MOD11_0225A3F4
MOD11_0225A3F4: ; 0x0225A3F4
	ldr r3, _0225A3FC ; =FUN_0200C5A8
	add r0, r1, #0
	bx r3
	nop
_0225A3FC: .word FUN_0200C5A8

	thumb_func_start MOD11_0225A400
MOD11_0225A400: ; 0x0225A400
	cmp r0, #3
	bhi _0225A418
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0225A410: ; jump table
	.short _0225A418 - _0225A410 - 2 ; case 0
	.short _0225A41C - _0225A410 - 2 ; case 1
	.short _0225A420 - _0225A410 - 2 ; case 2
	.short _0225A424 - _0225A410 - 2 ; case 3
_0225A418:
	mov r0, #0
	bx lr
_0225A41C:
	mov r0, #1
	bx lr
_0225A420:
	mov r0, #3
	bx lr
_0225A424:
	mov r0, #2
	bx lr

	thumb_func_start MOD11_0225A428
MOD11_0225A428: ; 0x0225A428
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r6, r2, #0
	add r0, r1, #0
	add r1, r4, #0
	mov r2, #0
	add r7, r3, #0
	bl FUN_02002E14
	add r4, r0, #0
	asr r1, r4, #2
	lsr r1, r1, #0x1d
	add r1, r4, r1
	asr r5, r1, #3
	mov r1, #8
	bl FX_ModS32
	cmp r0, #0
	beq _0225A450
	add r5, r5, #1
_0225A450:
	str r4, [r6]
	str r5, [r7]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD11_0225A458
MOD11_0225A458: ; 0x0225A458
	push {r4, r5, r6, r7, lr}
	sub sp, #0x7c
	add r5, r1, #0
	add r7, r0, #0
	ldr r0, [r5]
	str r2, [sp, #0x18]
	str r3, [sp, #0x1c]
	ldr r6, [sp, #0x9c]
	ldr r4, [sp, #0xa8]
	cmp r0, #0
	beq _0225A472
	bl GF_AssertFail
_0225A472:
	ldr r0, [r7]
	bl MOD11_02230080
	str r0, [sp, #0x20]
	ldr r0, [r7]
	bl MOD11_0222FF68
	str r0, [sp, #0x24]
	cmp r4, #0
	bne _0225A494
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	add r2, sp, #0x2c
	add r3, sp, #0x28
	bl MOD11_0225A428
	b _0225A49C
_0225A494:
	ldrh r0, [r4, #0x12]
	str r0, [sp, #0x2c]
	ldrh r0, [r4, #0x10]
	str r0, [sp, #0x28]
_0225A49C:
	cmp r4, #0
	bne _0225A4DA
	add r0, sp, #0x3c
	bl InitWindow
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r2, [sp, #0x28]
	ldr r0, [sp, #0x24]
	lsl r2, r2, #0x18
	add r1, sp, #0x3c
	lsr r2, r2, #0x18
	mov r3, #2
	bl AddTextWindowTopLeftCorner
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x90]
	ldr r1, [sp, #0x1c]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r2, [sp, #0x18]
	add r0, sp, #0x3c
	str r3, [sp, #0x14]
	bl AddTextPrinterParameterized3
	b _0225A4E6
_0225A4DA:
	add r3, r4, #0
	add r2, sp, #0x3c
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
_0225A4E6:
	add r0, sp, #0x3c
	mov r1, #2
	mov r2, #5
	bl FUN_02011898
	mov r1, #1
	mov r2, #2
	add r3, sp, #0x30
	bl FUN_0201D568
	ldr r0, [sp, #0xa4]
	cmp r0, #1
	bne _0225A50A
	ldr r1, [sp, #0x2c]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	sub r6, r6, r0
_0225A50A:
	ldr r0, _0225A588 ; =0x000004C8
	ldr r0, [r7, r0]
	str r0, [sp, #0x4c]
	add r0, sp, #0x3c
	str r0, [sp, #0x50]
	ldr r0, [sp, #0x20]
	bl FUN_0200CA40
	str r0, [sp, #0x54]
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x98]
	bl FUN_0200C334
	str r0, [sp, #0x58]
	mov r0, #0
	ldr r1, [sp, #0x34]
	str r0, [sp, #0x5c]
	str r0, [sp, #0x6c]
	mov r0, #0x64
	str r1, [sp, #0x60]
	mov r1, #0x42
	str r0, [sp, #0x70]
	mov r0, #2
	str r0, [sp, #0x74]
	mov r0, #5
	str r0, [sp, #0x78]
	ldr r2, [sp, #0xa0]
	lsl r1, r1, #2
	add r1, r2, r1
	add r0, sp, #0x4c
	str r6, [sp, #0x64]
	str r1, [sp, #0x68]
	bl FUN_020117E8
	ldr r1, [sp, #0x94]
	add r7, r0, #0
	bl FUN_02011AC0
	mov r2, #0x42
	ldr r3, [sp, #0xa0]
	lsl r2, r2, #2
	add r0, r7, #0
	add r1, r6, #0
	add r2, r3, r2
	bl FUN_020118C4
	cmp r4, #0
	bne _0225A570
	add r0, sp, #0x3c
	bl RemoveWindow
_0225A570:
	str r7, [r5]
	add r3, sp, #0x30
	ldmia r3!, {r0, r1}
	add r2, r5, #4
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [sp, #0x2c]
	strh r0, [r5, #0x10]
	add sp, #0x7c
	pop {r4, r5, r6, r7, pc}
	nop
_0225A588: .word 0x000004C8

	thumb_func_start MOD11_0225A58C
MOD11_0225A58C: ; 0x0225A58C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0x4d
	mov r6, #0
	lsl r0, r0, #4
	add r4, r5, r0
	add r7, r6, #0
_0225A59A:
	ldr r0, _0225A5BC ; =0x000004CC
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _0225A5B0
	bl FUN_02011870
	add r0, r4, #0
	bl FUN_0201D5E8
	ldr r0, _0225A5BC ; =0x000004CC
	str r7, [r5, r0]
_0225A5B0:
	add r6, r6, #1
	add r5, #0x14
	add r4, #0x14
	cmp r6, #0xd
	blt _0225A59A
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225A5BC: .word 0x000004CC

	thumb_func_start MOD11_0225A5C0
MOD11_0225A5C0: ; 0x0225A5C0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r0, #0
	ldr r0, [r7]
	bl MOD11_0222FF68
	mov r1, #5
	bl GetBgTilemapBuffer
	add r4, r0, #0
	add r0, r7, #0
	add r1, sp, #4
	mov r2, #0
	bl MOD11_0225ACD4
	add r0, sp, #0
	ldrb r0, [r0, #4]
	cmp r0, #1
	bne _0225A63A
	add r0, r7, #0
	mov r1, #1
	add r2, sp, #0
	mov r3, #0
	bl MOD11_0225AD2C
	add r0, sp, #0
	ldrb r0, [r0, #2]
	cmp r0, #1
	bne _0225A61E
	mov r5, #0xc
	mov r0, #0xa9
	lsl r6, r5, #5
	lsl r0, r0, #2
	mov r2, #0xf
_0225A604:
	lsl r1, r6, #1
	add r1, r4, r1
	add r3, r2, #0
	add r1, #0x1e
_0225A60C:
	add r3, r3, #1
	strh r0, [r1]
	add r1, r1, #2
	cmp r3, #0x10
	ble _0225A60C
	add r5, r5, #1
	add r6, #0x20
	cmp r5, #0x10
	ble _0225A604
_0225A61E:
	add r0, sp, #0
	ldrb r0, [r0, #3]
	cmp r0, #1
	bne _0225A63A
	mov r0, #0xa1
	lsl r0, r0, #2
	add r1, r4, r0
	mov r2, #2
	add r0, #0x20
_0225A630:
	add r2, r2, #1
	strh r0, [r1]
	add r1, r1, #2
	cmp r2, #0xc
	ble _0225A630
_0225A63A:
	add r0, sp, #0
	ldrb r0, [r0, #5]
	cmp r0, #1
	bne _0225A694
	add r0, r7, #0
	mov r1, #2
	add r2, sp, #0
	mov r3, #0
	bl MOD11_0225AD2C
	add r0, sp, #0
	ldrb r0, [r0, #2]
	cmp r0, #1
	bne _0225A668
	ldr r0, _0225A698 ; =0x000002A6
	mov r2, #0x13
	add r1, r4, r0
	sub r0, r0, #2
_0225A65E:
	add r2, r2, #1
	strh r0, [r1]
	add r1, r1, #2
	cmp r2, #0x1d
	ble _0225A65E
_0225A668:
	add r0, sp, #0
	ldrb r0, [r0, #3]
	cmp r0, #1
	bne _0225A694
	mov r0, #0xa9
	mov r5, #3
	mov r3, #0x60
	lsl r0, r0, #2
	mov r2, #0xf
_0225A67A:
	lsl r1, r3, #1
	add r1, r4, r1
	add r6, r2, #0
	add r1, #0x1e
_0225A682:
	add r6, r6, #1
	strh r0, [r1]
	add r1, r1, #2
	cmp r6, #0x10
	ble _0225A682
	add r5, r5, #1
	add r3, #0x20
	cmp r5, #7
	ble _0225A67A
_0225A694:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225A698: .word 0x000002A6

	thumb_func_start MOD11_0225A69C
MOD11_0225A69C: ; 0x0225A69C
	cmp r1, #2
	blt _0225A6A2
	sub r1, r1, #2
_0225A6A2:
	mov r2, #0x46
	lsl r2, r2, #2
	add r0, #0x68
	mul r2, r1
	add r0, r0, r2
	bx lr
	.align 2, 0

	thumb_func_start MOD11_0225A6B0
MOD11_0225A6B0: ; 0x0225A6B0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [sp]
	mov r1, #0x13
	str r0, [sp, #0x10]
	add r0, #0x90
	str r0, [sp, #0x10]
	ldr r0, [sp]
	lsl r1, r1, #4
	str r0, [sp, #0xc]
	add r0, #0xe0
	str r0, [sp, #0xc]
	ldr r0, [sp]
	add r0, r0, r1
	str r0, [sp, #8]
_0225A6D4:
	mov r0, #0
	str r0, [sp, #0x18]
	ldr r0, [sp]
	ldr r7, [sp, #0x10]
	ldr r6, [sp, #0xc]
	ldr r5, [sp, #8]
	str r0, [sp, #4]
	add r4, r0, #0
_0225A6E4:
	ldr r0, [sp, #4]
	add r0, #0x80
	ldr r0, [r0]
	bl FreeToHeap
	add r0, r4, #0
	add r0, #0x9c
	ldr r0, [r0]
	cmp r0, #0
	beq _0225A6FE
	add r0, r7, #0
	bl RemoveWindow
_0225A6FE:
	add r0, r4, #0
	add r0, #0xec
	ldr r0, [r0]
	cmp r0, #0
	beq _0225A70E
	add r0, r6, #0
	bl RemoveWindow
_0225A70E:
	mov r0, #0x4f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0225A71E
	add r0, r5, #0
	bl RemoveWindow
_0225A71E:
	ldr r0, [sp, #4]
	add r4, #0x14
	add r0, r0, #4
	str r0, [sp, #4]
	ldr r0, [sp, #0x18]
	add r7, #0x14
	add r0, r0, #1
	add r6, #0x14
	add r5, #0x14
	str r0, [sp, #0x18]
	cmp r0, #4
	blt _0225A6E4
	mov r0, #0x46
	ldr r1, [sp]
	lsl r0, r0, #2
	add r1, r1, r0
	str r1, [sp]
	ldr r1, [sp, #0x10]
	add r1, r1, r0
	str r1, [sp, #0x10]
	ldr r1, [sp, #0xc]
	add r1, r1, r0
	str r1, [sp, #0xc]
	ldr r1, [sp, #8]
	add r0, r1, r0
	str r0, [sp, #8]
	ldr r0, [sp, #0x14]
	add r0, r0, #1
	str r0, [sp, #0x14]
	cmp r0, #4
	blt _0225A6D4
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD11_0225A760
MOD11_0225A760: ; 0x0225A760
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x50
	add r7, r0, #0
	ldr r0, [r7]
	add r5, r1, #0
	str r2, [sp, #8]
	bl MOD11_022300C4
	add r4, r0, #0
	add r0, r7, #0
	add r1, r5, #0
	bl MOD11_0225A69C
	str r0, [sp, #0x38]
	mov r0, #6
	bl FUN_020799E8
	str r0, [sp, #0xc]
	ldr r1, _0225A95C ; =0x000003AA
	add r0, r4, #0
	bl NewString_ReadMsgData
	str r0, [sp, #0x28]
	ldr r0, [r7]
	bl MOD11_02230138
	str r0, [sp, #0x24]
	mov r0, #0x10
	mov r1, #5
	bl String_ctor
	str r0, [sp, #0x30]
	ldr r1, _0225A960 ; =0x000003A9
	add r0, r4, #0
	bl NewString_ReadMsgData
	ldr r4, [sp, #0x38]
	str r0, [sp, #0x2c]
	mov r0, #0
	str r0, [sp, #0x34]
	add r0, r4, #0
	str r0, [sp, #0x1c]
	str r0, [sp, #0x18]
	add r0, #0x28
	str r0, [sp, #0x18]
	add r0, r4, #0
	str r0, [sp, #0x14]
	add r0, #0x78
	str r0, [sp, #0x14]
	add r0, r4, #0
	str r0, [sp, #0x10]
	add r0, #0xc8
	ldr r5, [sp, #8]
	add r6, r4, #0
	str r0, [sp, #0x10]
_0225A7CE:
	ldrh r0, [r5]
	ldrh r1, [r4]
	cmp r0, r1
	beq _0225A814
	cmp r0, #0
	beq _0225A814
	mov r1, #3
	bl GetWazaAttr
	str r0, [sp, #0x3c]
	bl FUN_0206E12C
	str r0, [sp, #0x40]
	ldr r0, [sp, #0x3c]
	bl FUN_0206E0F0
	add r1, r0, #0
	mov r0, #5
	str r0, [sp]
	ldr r0, [sp, #0x40]
	mov r2, #1
	add r3, sp, #0x4c
	bl GfGfxLoader_GetCharData
	str r0, [sp, #0x44]
	ldr r0, [sp, #0x4c]
	ldr r1, [sp, #0x1c]
	ldr r0, [r0, #0x14]
	ldr r1, [r1, #0x18]
	ldr r2, [sp, #0xc]
	bl MIi_CpuCopy32
	ldr r0, [sp, #0x44]
	bl FreeToHeap
_0225A814:
	ldr r0, [r6, #0x34]
	cmp r0, #0
	beq _0225A826
	ldrh r1, [r5]
	ldrh r0, [r4]
	cmp r1, r0
	beq _0225A846
	cmp r1, #0
	beq _0225A846
_0225A826:
	ldrh r0, [r5]
	mov r1, #5
	bl GetMoveName
	str r0, [sp, #0x48]
	ldr r0, _0225A964 ; =0x00070809
	ldr r1, [sp, #0x48]
	str r0, [sp]
	ldr r3, [sp, #0x18]
	add r0, r7, #0
	mov r2, #2
	bl MOD11_0225A968
	ldr r0, [sp, #0x48]
	bl String_dtor
_0225A846:
	add r0, r6, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	beq _0225A876
	add r0, r6, #0
	add r0, #0xd4
	ldr r0, [r0]
	cmp r0, #0
	beq _0225A876
	ldrh r1, [r5]
	cmp r1, #0
	bne _0225A876
	ldrh r0, [r4]
	cmp r1, r0
	bne _0225A876
	ldrh r1, [r5, #8]
	ldrh r0, [r4, #8]
	cmp r1, r0
	bne _0225A876
	ldrh r1, [r5, #0x10]
	ldrh r0, [r4, #0x10]
	cmp r1, r0
	beq _0225A906
_0225A876:
	mov r0, #1
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldrh r2, [r5, #8]
	ldr r0, [sp, #0x24]
	mov r1, #0
	mov r3, #2
	bl BufferIntegerAsString
	mov r0, #1
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldrh r2, [r5, #0x10]
	ldr r0, [sp, #0x24]
	mov r1, #1
	mov r3, #2
	bl BufferIntegerAsString
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x30]
	ldr r2, [sp, #0x2c]
	bl StringExpandPlaceholders
	ldrh r0, [r5, #8]
	ldrh r1, [r5, #0x10]
	bl MOD11_0225B3D4
	str r0, [sp, #0x20]
	add r0, r6, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	beq _0225A8CC
	ldrh r1, [r5]
	ldrh r0, [r4]
	cmp r1, r0
	bne _0225A8CC
	ldrh r1, [r5, #8]
	ldrh r0, [r4, #8]
	cmp r1, r0
	beq _0225A8DC
_0225A8CC:
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x30]
	str r0, [sp]
	ldr r3, [sp, #0x14]
	add r0, r7, #0
	mov r2, #0
	bl MOD11_0225A968
_0225A8DC:
	add r0, r6, #0
	add r0, #0xd4
	ldr r0, [r0]
	cmp r0, #0
	beq _0225A8F6
	ldrh r1, [r5]
	ldrh r0, [r4]
	cmp r1, r0
	bne _0225A8F6
	ldrh r1, [r5, #8]
	ldrh r0, [r4, #8]
	cmp r1, r0
	beq _0225A906
_0225A8F6:
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x28]
	str r0, [sp]
	ldr r3, [sp, #0x10]
	add r0, r7, #0
	mov r2, #0
	bl MOD11_0225A968
_0225A906:
	ldr r0, [sp, #0x1c]
	add r4, r4, #2
	add r0, r0, #4
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r5, r5, #2
	add r0, #0x14
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r6, #0x14
	add r0, #0x14
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	add r0, #0x14
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x34]
	add r0, r0, #1
	str r0, [sp, #0x34]
	cmp r0, #4
	bge _0225A930
	b _0225A7CE
_0225A930:
	ldr r0, [sp, #0x28]
	bl String_dtor
	ldr r0, [sp, #0x2c]
	bl String_dtor
	ldr r0, [sp, #0x30]
	bl String_dtor
	mov r0, #0xc
_0225A944:
	ldr r1, [sp, #8]
	ldrh r2, [r1]
	add r1, r1, #2
	str r1, [sp, #8]
	ldr r1, [sp, #0x38]
	strh r2, [r1]
	add r1, r1, #2
	str r1, [sp, #0x38]
	sub r0, r0, #1
	bne _0225A944
	add sp, #0x50
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225A95C: .word 0x000003AA
_0225A960: .word 0x000003A9
_0225A964: .word 0x00070809

	thumb_func_start MOD11_0225A968
MOD11_0225A968: ; 0x0225A968
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r7, r2, #0
	add r6, r1, #0
	add r5, r0, #0
	add r4, r3, #0
	add r0, r6, #0
	add r1, r7, #0
	add r2, sp, #0x1c
	add r3, sp, #0x18
	bl MOD11_0225A428
	ldr r0, [sp, #0x1c]
	strh r0, [r4, #0x12]
	ldr r0, [sp, #0x18]
	strh r0, [r4, #0x10]
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _0225A994
	add r0, r4, #0
	bl RemoveWindow
_0225A994:
	add r0, r4, #0
	bl InitWindow
	ldr r0, [r5]
	bl MOD11_0222FF68
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	ldr r2, [sp, #0x18]
	add r1, r4, #0
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	mov r3, #2
	bl AddTextWindowTopLeftCorner
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x38]
	add r1, r7, #0
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	add r0, r4, #0
	add r2, r6, #0
	str r3, [sp, #0x14]
	bl AddTextPrinterParameterized3
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD11_0225A9D4
MOD11_0225A9D4: ; 0x0225A9D4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	add r5, r0, #0
	str r0, [sp, #4]
	add r0, #0x18
	str r0, [sp, #4]
	ldr r0, [r5]
	bl MOD11_02230078
	str r0, [sp, #0xc]
	ldr r0, [r5]
	bl MOD11_02230080
	ldr r1, _0225AAA8 ; =0x0000069E
	str r0, [sp, #8]
	ldrb r1, [r5, r1]
	add r0, r5, #0
	bl MOD11_0225A69C
	ldr r4, _0225AAAC ; =MOD11_0225F914
	str r0, [sp]
	add r3, sp, #0x10
	mov r2, #6
_0225AA02:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0225AA02
	ldr r0, [r4]
	mov r4, #0
	str r0, [r3]
	add r6, sp, #0x10
	b _0225AAA0
_0225AA14:
	lsl r0, r4, #2
	add r1, r5, r0
	ldr r0, _0225AAB0 ; =0x00000604
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0225AA24
	bl GF_AssertFail
_0225AA24:
	ldr r0, [sp, #4]
	lsl r1, r4, #1
	ldrh r0, [r0, r1]
	cmp r0, #0
	beq _0225AA9E
	mov r1, #3
	bl GetWazaAttr
	add r2, r0, #0
	ldr r0, _0225AAB4 ; =0x00004E35
	ldr r1, _0225AAB8 ; =MOD11_0225F72C
	add r0, r4, r0
	str r0, [sp, #0x24]
	lsl r0, r4, #2
	ldrh r1, [r1, r0]
	add r3, sp, #0x10
	strh r1, [r6]
	ldr r1, _0225AAB8 ; =MOD11_0225F72C
	add r0, r1, r0
	ldrh r0, [r0, #2]
	ldr r1, [sp, #8]
	strh r0, [r6, #2]
	ldr r0, [sp, #0xc]
	bl FUN_0206E240
	lsl r1, r4, #2
	add r2, r5, r1
	ldr r1, _0225AAB0 ; =0x00000604
	mov r3, #0x11
	str r0, [r2, r1]
	add r0, r1, #0
	ldr r0, [r2, r0]
	mov r1, #0
	mov r2, #2
	ldrsh r1, [r6, r1]
	ldrsh r2, [r6, r2]
	lsl r3, r3, #0x10
	bl FUN_0200C750
	lsl r0, r4, #2
	add r1, r5, r0
	ldr r0, _0225AAB0 ; =0x00000604
	ldr r0, [r1, r0]
	ldr r0, [r0]
	bl FUN_02020350
	add r7, r0, #0
	mov r0, #6
	bl FUN_020799E8
	add r2, r0, #0
	ldr r0, [sp]
	lsl r3, r4, #2
	add r0, r0, r3
	mov r3, #0x66
	ldr r1, [r7, #8]
	lsl r3, r3, #0x14
	ldr r0, [r0, #0x18]
	add r1, r3, r1
	bl MIi_CpuCopy16
_0225AA9E:
	add r4, r4, #1
_0225AAA0:
	cmp r4, #4
	blt _0225AA14
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0225AAA8: .word 0x0000069E
_0225AAAC: .word MOD11_0225F914
_0225AAB0: .word 0x00000604
_0225AAB4: .word 0x00004E35
_0225AAB8: .word MOD11_0225F72C

	thumb_func_start MOD11_0225AABC
MOD11_0225AABC: ; 0x0225AABC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	bl MOD11_02230078
	ldr r0, [r5]
	bl MOD11_02230080
	mov r4, #0
	ldr r7, _0225AAEC ; =0x00000604
	add r6, r4, #0
_0225AAD2:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _0225AAE0
	bl FUN_0206E270
	ldr r0, _0225AAEC ; =0x00000604
	str r6, [r5, r0]
_0225AAE0:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0225AAD2
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225AAEC: .word 0x00000604

	thumb_func_start MOD11_0225AAF0
MOD11_0225AAF0: ; 0x0225AAF0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	bl MOD11_02230078
	ldr r0, [r5]
	bl MOD11_02230080
	mov r4, #0
	add r6, r0, #0
	add r7, r4, #0
_0225AB06:
	ldr r0, _0225AB2C ; =0x00000614
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _0225AB20
	bl FUN_0206E2E8
	ldr r1, _0225AB30 ; =0x00004E39
	add r0, r6, #0
	add r1, r4, r1
	bl FUN_0206E2E0
	ldr r0, _0225AB2C ; =0x00000614
	str r7, [r5, r0]
_0225AB20:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0225AB06
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225AB2C: .word 0x00000614
_0225AB30: .word 0x00004E39

	thumb_func_start MOD11_0225AB34
MOD11_0225AB34: ; 0x0225AB34
	push {r3, r4, r5, lr}
	ldr r0, [r0]
	add r5, r1, #0
	add r4, r2, #0
	bl MOD11_022300CC
	add r4, #8
	add r1, r5, #0
	mov r2, #5
	mov r3, #1
	str r4, [sp]
	bl MOD08_02211E7C
	pop {r3, r4, r5, pc}

	thumb_func_start MOD11_0225AB50
MOD11_0225AB50: ; 0x0225AB50
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	bl MOD11_022300CC
	add r6, r0, #0
	mov r7, #0
	b _0225AB96
_0225AB62:
	ldr r1, _0225AB9C ; =MOD11_0225F6A8
	lsl r2, r4, #1
	add r1, r1, r2
	ldr r2, _0225ABA0 ; =MOD11_0225F74C
	lsl r3, r4, #2
	add r2, r2, r3
	add r0, r5, #0
	mov r3, #3
	str r7, [sp]
	bl MOD11_0225ADD8
	mov r0, #0x20
	str r0, [sp]
	add r3, r4, #0
	mov r1, #7
	add r3, #8
	lsl r3, r3, #0x14
	ldr r2, [r5, #0x58]
	lsl r1, r1, #6
	add r1, r2, r1
	add r0, r6, #0
	mov r2, #1
	lsr r3, r3, #0x10
	bl PaletteData_LoadPalette
	add r4, r4, #1
_0225AB96:
	cmp r4, #4
	blt _0225AB62
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225AB9C: .word MOD11_0225F6A8
_0225ABA0: .word MOD11_0225F74C

	thumb_func_start MOD11_0225ABA4
MOD11_0225ABA4: ; 0x0225ABA4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r1, #0
	ldr r1, _0225AC50 ; =MOD11_0225F684
	add r5, r0, #0
	ldrb r2, [r1, #6]
	add r0, sp, #0x10
	strb r2, [r0]
	ldrb r2, [r1, #7]
	strb r2, [r0, #1]
	ldrb r2, [r1, #8]
	ldrb r1, [r1, #9]
	strb r2, [r0, #2]
	strb r1, [r0, #3]
	ldr r0, [r5]
	bl MOD11_0222FF68
	add r6, r0, #0
	ldr r0, [r5]
	bl MOD11_022300CC
	add r7, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r2, _0225AC54 ; =MOD11_0225F6C0
	lsl r1, r4, #1
	add r1, r2, r1
	ldr r3, _0225AC58 ; =MOD11_0225F71C
	lsl r2, r4, #2
	add r2, r3, r2
	add r0, r5, #0
	mov r3, #4
	bl MOD11_0225ADD8
	mov r0, #0x20
	str r0, [sp]
	add r3, sp, #0x10
	ldrb r3, [r3, r4]
	mov r1, #7
	ldr r2, [r5, #0x58]
	lsl r1, r1, #6
	lsl r3, r3, #0x14
	add r1, r2, r1
	add r0, r7, #0
	mov r2, #1
	lsr r3, r3, #0x10
	bl PaletteData_LoadPalette
	add r0, r6, #0
	mov r1, #4
	bl ScheduleBgTilemapBufferTransfer
	ldr r0, _0225AC58 ; =MOD11_0225F71C
	lsl r1, r4, #2
	ldrb r2, [r0, r1]
	add r3, r0, r1
	str r2, [sp]
	ldrb r4, [r3, #3]
	ldrb r2, [r3, #2]
	sub r2, r4, r2
	add r2, r2, #1
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	str r2, [sp, #4]
	ldrb r0, [r0, r1]
	ldrb r2, [r3, #1]
	mov r1, #5
	sub r0, r2, r0
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldrb r3, [r3, #2]
	ldr r2, _0225AC5C ; =0x000002FF
	add r0, r6, #0
	bl FillBgTilemapRect
	add r0, r6, #0
	mov r1, #5
	bl ScheduleBgTilemapBufferTransfer
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0225AC50: .word MOD11_0225F684
_0225AC54: .word MOD11_0225F6C0
_0225AC58: .word MOD11_0225F71C
_0225AC5C: .word 0x000002FF

	thumb_func_start MOD11_0225AC60
MOD11_0225AC60: ; 0x0225AC60
	push {r4, r5, r6, lr}
	mov r5, #0
	mov r6, #1
	add r4, r5, #0
_0225AC68:
	add r0, r5, #4
	cmp r0, #6
	beq _0225AC7A
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, r4, #0
	bl ToggleBgLayer
	b _0225AC84
_0225AC7A:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, r6, #0
	bl ToggleBgLayer
_0225AC84:
	add r5, r5, #1
	cmp r5, #4
	blt _0225AC68
	pop {r4, r5, r6, pc}

	thumb_func_start MOD11_0225AC8C
MOD11_0225AC8C: ; 0x0225AC8C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r2, #0
	cmp r1, #1
	bne _0225AC9A
	bl MOD11_0225ACB0
_0225AC9A:
	cmp r4, #1
	bne _0225ACA8
	ldr r0, _0225ACAC ; =MOD11_0225B76C
	add r1, r5, #0
	mov r2, #0xa
	bl FUN_0200CA98
_0225ACA8:
	pop {r3, r4, r5, pc}
	nop
_0225ACAC: .word MOD11_0225B76C

	thumb_func_start MOD11_0225ACB0
MOD11_0225ACB0: ; 0x0225ACB0
	push {r4, lr}
	add r4, r0, #0
	bl MOD11_0225AABC
	add r0, r4, #0
	bl MOD11_0225AAF0
	add r0, r4, #0
	bl MOD11_0225A58C
	add r0, r4, #0
	bl MOD11_0225A1E4
	add r0, r4, #0
	bl MOD11_0225A234
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD11_0225ACD4
MOD11_0225ACD4: ; 0x0225ACD4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	add r6, r5, #0
	add r1, sp, #0
	add r7, r2, #0
	add r6, #0x18
	bl MOD11_022314E0
	mov r0, #0
	b _0225AD1E
_0225ACEE:
	add r2, r0, #2
	add r1, sp, #0
	ldrb r1, [r1, r2]
	cmp r7, #1
	bne _0225AD0A
	lsl r1, r1, #3
	add r1, r6, r1
	ldrb r1, [r1, #1]
	lsl r1, r1, #0x1d
	lsr r1, r1, #0x1f
	bne _0225AD0A
	mov r1, #0
	strb r1, [r4, r0]
	b _0225AD1C
_0225AD0A:
	mov r1, #0x6a
	lsl r1, r1, #4
	ldrb r1, [r5, r1]
	lsl r2, r0, #2
	lsl r3, r1, #4
	ldr r1, _0225AD28 ; =MOD11_0225F9EC
	add r1, r1, r3
	ldr r1, [r2, r1]
	strb r1, [r4, r0]
_0225AD1C:
	add r0, r0, #1
_0225AD1E:
	cmp r0, #4
	blt _0225ACEE
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225AD28: .word MOD11_0225F9EC

	thumb_func_start MOD11_0225AD2C
MOD11_0225AD2C: ; 0x0225AD2C
	push {r4, lr}
	mov r4, #0x6a
	lsl r4, r4, #4
	ldrb r4, [r0, r4]
	cmp r4, #0xb
	bhi _0225AD76
	add r4, r4, r4
	add r4, pc
	ldrh r4, [r4, #6]
	lsl r4, r4, #0x10
	asr r4, r4, #0x10
	add pc, r4
_0225AD44: ; jump table
	.short _0225AD5C - _0225AD44 - 2 ; case 0
	.short _0225AD76 - _0225AD44 - 2 ; case 1
	.short _0225AD76 - _0225AD44 - 2 ; case 2
	.short _0225AD76 - _0225AD44 - 2 ; case 3
	.short _0225AD76 - _0225AD44 - 2 ; case 4
	.short _0225AD76 - _0225AD44 - 2 ; case 5
	.short _0225AD76 - _0225AD44 - 2 ; case 6
	.short _0225AD76 - _0225AD44 - 2 ; case 7
	.short _0225AD5C - _0225AD44 - 2 ; case 8
	.short _0225AD5C - _0225AD44 - 2 ; case 9
	.short _0225AD5C - _0225AD44 - 2 ; case 10
	.short _0225AD5C - _0225AD44 - 2 ; case 11
_0225AD5C:
	mov r4, #0
	add r0, r4, #0
	mov r3, #1
	sub r1, r1, #1
_0225AD64:
	cmp r4, r1
	bne _0225AD6C
	strb r3, [r2, r4]
	b _0225AD6E
_0225AD6C:
	strb r0, [r2, r4]
_0225AD6E:
	add r4, r4, #1
	cmp r4, #4
	blt _0225AD64
	pop {r4, pc}
_0225AD76:
	add r1, r2, #0
	add r2, r3, #0
	bl MOD11_0225ACD4
	pop {r4, pc}

	thumb_func_start MOD11_0225AD80
MOD11_0225AD80: ; 0x0225AD80
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _0225AD90
	bl GF_AssertFail
_0225AD90:
	mov r0, #0x6b
	lsl r0, r0, #4
	add r0, r4, r0
	mov r1, #0
	mov r2, #0x24
	bl MI_CpuFill8
	ldr r2, _0225ADAC ; =0x00000514
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
	.align 2, 0
_0225ADAC: .word 0x00000514

	thumb_func_start MOD11_0225ADB0
MOD11_0225ADB0: ; 0x0225ADB0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _0225ADCE
	bl FUN_0200CAB4
	mov r0, #0x6b
	lsl r0, r0, #4
	mov r1, #0
	add r0, r4, r0
	mov r2, #0x24
	str r1, [r4, #8]
	bl MI_CpuFill8
_0225ADCE:
	pop {r4, pc}

	thumb_func_start MOD11_0225ADD0
MOD11_0225ADD0: ; 0x0225ADD0
	bx lr
	.align 2, 0

	thumb_func_start MOD11_0225ADD4
MOD11_0225ADD4: ; 0x0225ADD4
	bx lr
	.align 2, 0

	thumb_func_start MOD11_0225ADD8
MOD11_0225ADD8: ; 0x0225ADD8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5]
	add r6, r1, #0
	add r4, r2, #0
	add r7, r3, #0
	bl MOD11_0222FF68
	mov r1, #4
	str r0, [sp, #4]
	bl GetBgTilemapBuffer
	mov ip, r0
	lsl r0, r7, #2
	add r0, r5, r0
	ldr r0, [r0, #0x3c]
	ldrb r7, [r4]
	str r0, [sp]
	ldr r0, [sp, #0x20]
	lsl r0, r0, #1
	ldrsh r1, [r6, r0]
	ldrb r0, [r4, #1]
	cmp r7, r0
	bgt _0225AE40
	lsl r6, r7, #5
_0225AE0C:
	lsl r2, r6, #1
	mov r0, ip
	add r5, r0, r2
	ldr r0, [sp]
	ldrb r3, [r4, #3]
	add r2, r0, r2
	ldrb r0, [r4, #2]
	cmp r0, r3
	bgt _0225AE36
	lsl r3, r0, #1
	add r2, r2, r3
	add r3, r5, r3
_0225AE24:
	ldrh r5, [r2]
	add r0, r0, #1
	add r2, r2, #2
	add r5, r1, r5
	strh r5, [r3]
	ldrb r5, [r4, #3]
	add r3, r3, #2
	cmp r0, r5
	ble _0225AE24
_0225AE36:
	ldrb r0, [r4, #1]
	add r7, r7, #1
	add r6, #0x20
	cmp r7, r0
	ble _0225AE0C
_0225AE40:
	ldr r0, [sp, #4]
	mov r1, #4
	bl ScheduleBgTilemapBufferTransfer
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD11_0225AE4C
MOD11_0225AE4C: ; 0x0225AE4C
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldr r0, [r4]
	bl MOD11_0222FF68
	mov r3, #0x6b
	lsl r3, r3, #4
	ldrsh r0, [r4, r3]
	cmp r0, #0
	beq _0225AE6C
	cmp r0, #1
	beq _0225AEDC
	cmp r0, #2
	beq _0225AEF8
	b _0225AF66
_0225AE6C:
	mov r0, #2
	str r0, [sp]
	add r1, r3, #4
	add r2, r3, #0
	add r3, #0x10
	add r2, #8
	ldrb r3, [r4, r3]
	ldr r1, [r4, r1]
	ldr r2, [r4, r2]
	add r0, r4, #0
	bl MOD11_0225ADD8
	ldr r0, _0225AF8C ; =0x000006C1
	add r2, sp, #4
	ldrb r1, [r4, r0]
	mov r0, #0x14
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0225AF90 ; =0x000004CC
	ldr r0, [r1, r0]
	add r1, sp, #8
	bl FUN_020119A4
	ldr r0, _0225AF8C ; =0x000006C1
	ldr r2, [sp, #4]
	ldrb r1, [r4, r0]
	mov r0, #0x14
	sub r2, r2, #2
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0225AF90 ; =0x000004CC
	ldr r0, [r1, r0]
	ldr r1, [sp, #8]
	bl FUN_020118C4
	ldr r0, _0225AF94 ; =0x000006C2
	ldrb r1, [r4, r0]
	cmp r1, #0xff
	beq _0225AECE
	lsl r1, r1, #2
	add r1, r4, r1
	sub r0, #0x9e
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0225AECE
	mov r1, #0
	sub r2, r1, #2
	bl FUN_0200C82C
_0225AECE:
	mov r0, #0x6b
	lsl r0, r0, #4
	ldrsh r1, [r4, r0]
	add sp, #0xc
	add r1, r1, #1
	strh r1, [r4, r0]
	pop {r3, r4, pc}
_0225AEDC:
	add r0, r3, #2
	ldrsh r0, [r4, r0]
	add r1, r0, #1
	add r0, r3, #2
	strh r1, [r4, r0]
	ldrsh r0, [r4, r0]
	cmp r0, #0
	ble _0225AF86
	mov r1, #0
	add r0, r3, #2
	strh r1, [r4, r0]
	ldrsh r0, [r4, r3]
	add r0, r0, #1
	strh r0, [r4, r3]
_0225AEF8:
	mov r0, #1
	ldr r3, _0225AF98 ; =0x000006B4
	str r0, [sp]
	add r2, r3, #4
	ldr r1, [r4, r3]
	add r3, #0xc
	ldrb r3, [r4, r3]
	ldr r2, [r4, r2]
	add r0, r4, #0
	bl MOD11_0225ADD8
	ldr r0, _0225AF8C ; =0x000006C1
	add r2, sp, #4
	ldrb r1, [r4, r0]
	mov r0, #0x14
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0225AF90 ; =0x000004CC
	ldr r0, [r1, r0]
	add r1, sp, #8
	bl FUN_020119A4
	ldr r0, _0225AF8C ; =0x000006C1
	ldr r2, [sp, #4]
	ldrb r1, [r4, r0]
	mov r0, #0x14
	add r2, r2, #1
	mul r0, r1
	add r1, r4, r0
	ldr r0, _0225AF90 ; =0x000004CC
	ldr r0, [r1, r0]
	ldr r1, [sp, #8]
	bl FUN_020118C4
	ldr r0, _0225AF94 ; =0x000006C2
	ldrb r1, [r4, r0]
	cmp r1, #0xff
	beq _0225AF58
	lsl r1, r1, #2
	add r1, r4, r1
	sub r0, #0x9e
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0225AF58
	mov r1, #0
	mov r2, #1
	bl FUN_0200C82C
_0225AF58:
	mov r0, #0x6b
	lsl r0, r0, #4
	ldrsh r1, [r4, r0]
	add sp, #0xc
	add r1, r1, #1
	strh r1, [r4, r0]
	pop {r3, r4, pc}
_0225AF66:
	add r0, r3, #2
	ldrsh r0, [r4, r0]
	add r1, r0, #1
	add r0, r3, #2
	strh r1, [r4, r0]
	ldrsh r0, [r4, r0]
	cmp r0, #0
	ble _0225AF86
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD11_0225AC8C
	add r0, r4, #0
	bl MOD11_0225ADB0
_0225AF86:
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0225AF8C: .word 0x000006C1
_0225AF90: .word 0x000004CC
_0225AF94: .word 0x000006C2
_0225AF98: .word 0x000006B4

	thumb_func_start MOD11_0225AF9C
MOD11_0225AF9C: ; 0x0225AF9C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r4, r1, #0
	ldr r0, [r4]
	bl MOD11_0222FF68
	ldr r0, _0225B21C ; =0x000006BC
	add r1, r4, #0
	ldr r0, [r4, r0]
	add r1, #0x18
	cmp r0, #4
	bgt _0225AFCE
	cmp r0, #0
	blt _0225B00A
	add r2, r0, r0
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0225AFC4: ; jump table
	.short _0225B00A - _0225AFC4 - 2 ; case 0
	.short _0225AFD2 - _0225AFC4 - 2 ; case 1
	.short _0225AFE0 - _0225AFC4 - 2 ; case 2
	.short _0225AFEE - _0225AFC4 - 2 ; case 3
	.short _0225AFFC - _0225AFC4 - 2 ; case 4
_0225AFCE:
	cmp r0, #0xff
	b _0225B00A
_0225AFD2:
	mov r0, #5
	str r0, [sp, #8]
	ldrh r0, [r1]
	mov r5, #0
	mov r6, #9
	str r0, [sp, #4]
	b _0225B012
_0225AFE0:
	mov r0, #6
	str r0, [sp, #8]
	ldrh r0, [r1, #2]
	mov r5, #1
	mov r6, #0xa
	str r0, [sp, #4]
	b _0225B012
_0225AFEE:
	mov r0, #7
	str r0, [sp, #8]
	ldrh r0, [r1, #4]
	mov r5, #2
	mov r6, #0xb
	str r0, [sp, #4]
	b _0225B012
_0225AFFC:
	mov r0, #8
	str r0, [sp, #8]
	ldrh r0, [r1, #6]
	mov r5, #3
	mov r6, #0xc
	str r0, [sp, #4]
	b _0225B012
_0225B00A:
	mov r5, #0
	add r6, r5, #0
	str r5, [sp, #8]
	str r5, [sp, #4]
_0225B012:
	mov r3, #0x6b
	lsl r3, r3, #4
	ldrsh r0, [r4, r3]
	cmp r0, #0
	beq _0225B026
	cmp r0, #1
	beq _0225B100
	cmp r0, #2
	beq _0225B11E
	b _0225B1F6
_0225B026:
	mov r0, #2
	str r0, [sp]
	add r1, r3, #4
	add r2, r3, #0
	add r3, #0x10
	add r2, #8
	ldrb r3, [r4, r3]
	ldr r1, [r4, r1]
	ldr r2, [r4, r2]
	add r0, r4, #0
	bl MOD11_0225ADD8
	ldr r0, _0225B21C ; =0x000006BC
	add r1, sp, #0x20
	ldr r0, [r4, r0]
	cmp r0, #0xff
	beq _0225B0DA
	ldr r0, _0225B220 ; =0x000004CC
	add r2, sp, #0x1c
	add r7, r4, r0
	mov r0, #0x14
	mul r0, r5
	str r0, [sp, #0xc]
	ldr r0, [r7, r0]
	bl FUN_020119A4
	ldr r0, [sp, #0xc]
	ldr r2, [sp, #0x1c]
	ldr r0, [r7, r0]
	ldr r1, [sp, #0x20]
	sub r2, r2, #2
	bl FUN_020118C4
	ldr r0, _0225B220 ; =0x000004CC
	add r1, sp, #0x20
	add r7, r4, r0
	mov r0, #0x14
	mul r0, r6
	str r0, [sp, #0x10]
	ldr r0, [r7, r0]
	add r2, sp, #0x1c
	bl FUN_020119A4
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x1c]
	ldr r0, [r7, r0]
	ldr r1, [sp, #0x20]
	sub r2, r2, #2
	bl FUN_020118C4
	ldr r0, _0225B220 ; =0x000004CC
	mov r1, #0x14
	add r6, r4, r0
	ldr r0, [sp, #8]
	add r2, sp, #0x1c
	add r7, r0, #0
	mul r7, r1
	ldr r0, [r6, r7]
	add r1, sp, #0x20
	bl FUN_020119A4
	ldr r2, [sp, #0x1c]
	ldr r0, [r6, r7]
	ldr r1, [sp, #0x20]
	sub r2, r2, #2
	bl FUN_020118C4
	ldr r0, [sp, #4]
	cmp r0, #0
	beq _0225B0F2
	lsl r5, r5, #2
	ldr r0, _0225B224 ; =0x00000604
	add r1, r4, r5
	ldr r0, [r1, r0]
	mov r1, #0
	ldr r0, [r0]
	sub r2, r1, #2
	bl FUN_0200C7FC
	ldr r0, _0225B228 ; =0x00000614
	add r1, r4, r5
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0225B0F2
	mov r1, #0
	ldr r0, [r0]
	sub r2, r1, #2
	bl FUN_0200C7FC
	b _0225B0F2
_0225B0DA:
	ldr r0, _0225B22C ; =0x0000051C
	add r2, sp, #0x1c
	ldr r0, [r4, r0]
	bl FUN_020119A4
	ldr r0, _0225B22C ; =0x0000051C
	ldr r2, [sp, #0x1c]
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x20]
	sub r2, r2, #2
	bl FUN_020118C4
_0225B0F2:
	mov r0, #0x6b
	lsl r0, r0, #4
	ldrsh r1, [r4, r0]
	add sp, #0x24
	add r1, r1, #1
	strh r1, [r4, r0]
	pop {r4, r5, r6, r7, pc}
_0225B100:
	add r0, r3, #2
	ldrsh r0, [r4, r0]
	add r1, r0, #1
	add r0, r3, #2
	strh r1, [r4, r0]
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bgt _0225B112
	b _0225B216
_0225B112:
	mov r1, #0
	add r0, r3, #2
	strh r1, [r4, r0]
	ldrsh r0, [r4, r3]
	add r0, r0, #1
	strh r0, [r4, r3]
_0225B11E:
	mov r0, #1
	ldr r3, _0225B230 ; =0x000006B4
	str r0, [sp]
	add r2, r3, #4
	ldr r1, [r4, r3]
	add r3, #0xc
	ldrb r3, [r4, r3]
	ldr r2, [r4, r2]
	add r0, r4, #0
	bl MOD11_0225ADD8
	ldr r0, _0225B21C ; =0x000006BC
	add r1, sp, #0x20
	ldr r0, [r4, r0]
	cmp r0, #0xff
	beq _0225B1D0
	ldr r0, _0225B220 ; =0x000004CC
	add r2, sp, #0x1c
	add r7, r4, r0
	mov r0, #0x14
	mul r0, r5
	str r0, [sp, #0x14]
	ldr r0, [r7, r0]
	bl FUN_020119A4
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x1c]
	ldr r0, [r7, r0]
	ldr r1, [sp, #0x20]
	add r2, r2, #1
	bl FUN_020118C4
	ldr r0, _0225B220 ; =0x000004CC
	add r1, sp, #0x20
	add r7, r4, r0
	mov r0, #0x14
	mul r0, r6
	str r0, [sp, #0x18]
	ldr r0, [r7, r0]
	add r2, sp, #0x1c
	bl FUN_020119A4
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #0x1c]
	ldr r0, [r7, r0]
	ldr r1, [sp, #0x20]
	add r2, r2, #1
	bl FUN_020118C4
	ldr r0, _0225B220 ; =0x000004CC
	mov r1, #0x14
	add r6, r4, r0
	ldr r0, [sp, #8]
	add r2, sp, #0x1c
	add r7, r0, #0
	mul r7, r1
	ldr r0, [r6, r7]
	add r1, sp, #0x20
	bl FUN_020119A4
	ldr r2, [sp, #0x1c]
	ldr r0, [r6, r7]
	ldr r1, [sp, #0x20]
	add r2, r2, #1
	bl FUN_020118C4
	ldr r0, [sp, #4]
	cmp r0, #0
	beq _0225B1E8
	lsl r5, r5, #2
	ldr r0, _0225B224 ; =0x00000604
	add r1, r4, r5
	ldr r0, [r1, r0]
	mov r1, #0
	ldr r0, [r0]
	mov r2, #1
	bl FUN_0200C7FC
	ldr r0, _0225B228 ; =0x00000614
	add r1, r4, r5
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0225B1E8
	ldr r0, [r0]
	mov r1, #0
	mov r2, #1
	bl FUN_0200C7FC
	b _0225B1E8
_0225B1D0:
	ldr r0, _0225B22C ; =0x0000051C
	add r2, sp, #0x1c
	ldr r0, [r4, r0]
	bl FUN_020119A4
	ldr r0, _0225B22C ; =0x0000051C
	ldr r2, [sp, #0x1c]
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x20]
	add r2, r2, #1
	bl FUN_020118C4
_0225B1E8:
	mov r0, #0x6b
	lsl r0, r0, #4
	ldrsh r1, [r4, r0]
	add sp, #0x24
	add r1, r1, #1
	strh r1, [r4, r0]
	pop {r4, r5, r6, r7, pc}
_0225B1F6:
	add r0, r3, #2
	ldrsh r0, [r4, r0]
	add r1, r0, #1
	add r0, r3, #2
	strh r1, [r4, r0]
	ldrsh r0, [r4, r0]
	cmp r0, #0
	ble _0225B216
	mov r1, #1
	add r0, r4, #0
	add r2, r1, #0
	bl MOD11_0225AC8C
	add r0, r4, #0
	bl MOD11_0225ADB0
_0225B216:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_0225B21C: .word 0x000006BC
_0225B220: .word 0x000004CC
_0225B224: .word 0x00000604
_0225B228: .word 0x00000614
_0225B22C: .word 0x0000051C
_0225B230: .word 0x000006B4

	thumb_func_start MOD11_0225B234
MOD11_0225B234: ; 0x0225B234
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	ldr r0, [r4]
	bl MOD11_0222FF68
	mov r1, #0x6b
	lsl r1, r1, #4
	ldrsh r0, [r4, r1]
	cmp r0, #3
	bls _0225B24C
	b _0225B3AE
_0225B24C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0225B258: ; jump table
	.short _0225B260 - _0225B258 - 2 ; case 0
	.short _0225B2E8 - _0225B258 - 2 ; case 1
	.short _0225B304 - _0225B258 - 2 ; case 2
	.short _0225B38E - _0225B258 - 2 ; case 3
_0225B260:
	add r1, #0x20
	ldr r1, [r4, r1]
	add r0, r4, #0
	add r2, sp, #4
	mov r3, #1
	bl MOD11_0225AD2C
	mov r5, #0
	mov r7, #2
	add r6, sp, #4
	b _0225B2D6
_0225B276:
	ldrb r0, [r6, r5]
	cmp r0, #1
	bne _0225B2D4
	mov r1, #6
	add r2, r5, #0
	mul r2, r1
	ldr r1, _0225B3C4 ; =MOD11_0225F88C
	lsl r3, r5, #2
	add r1, r1, r2
	ldr r2, _0225B3C8 ; =MOD11_0225F7FC
	add r0, r4, #0
	add r2, r2, r3
	mov r3, #4
	str r7, [sp]
	bl MOD11_0225ADD8
	mov r0, #0x14
	mul r0, r5
	add r1, r4, r0
	ldr r0, _0225B3CC ; =0x000004CC
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0225B2C0
	add r1, sp, #0xc
	add r2, sp, #8
	bl FUN_020119A4
	mov r0, #0x14
	mul r0, r5
	add r1, r4, r0
	ldr r0, _0225B3CC ; =0x000004CC
	ldr r2, [sp, #8]
	ldr r0, [r1, r0]
	ldr r1, [sp, #0xc]
	sub r2, r2, #2
	bl FUN_020118C4
_0225B2C0:
	lsl r0, r5, #2
	add r1, r4, r0
	ldr r0, _0225B3D0 ; =0x00000624
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0225B2D4
	mov r1, #0
	sub r2, r1, #2
	bl FUN_0200C82C
_0225B2D4:
	add r5, r5, #1
_0225B2D6:
	cmp r5, #4
	blt _0225B276
	mov r0, #0x6b
	lsl r0, r0, #4
	ldrsh r1, [r4, r0]
	add sp, #0x10
	add r1, r1, #1
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_0225B2E8:
	add r0, r1, #2
	ldrsh r0, [r4, r0]
	add r2, r0, #1
	add r0, r1, #2
	strh r2, [r4, r0]
	ldrsh r0, [r4, r0]
	cmp r0, #0
	ble _0225B3BE
	mov r2, #0
	add r0, r1, #2
	strh r2, [r4, r0]
	ldrsh r0, [r4, r1]
	add r0, r0, #1
	strh r0, [r4, r1]
_0225B304:
	mov r1, #0x6d
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	add r0, r4, #0
	add r2, sp, #4
	mov r3, #1
	bl MOD11_0225AD2C
	mov r5, #0
	mov r7, #1
	add r6, sp, #4
	b _0225B37C
_0225B31C:
	ldrb r0, [r6, r5]
	cmp r0, #1
	bne _0225B37A
	mov r1, #6
	add r2, r5, #0
	mul r2, r1
	ldr r1, _0225B3C4 ; =MOD11_0225F88C
	lsl r3, r5, #2
	add r1, r1, r2
	ldr r2, _0225B3C8 ; =MOD11_0225F7FC
	add r0, r4, #0
	add r2, r2, r3
	mov r3, #4
	str r7, [sp]
	bl MOD11_0225ADD8
	mov r0, #0x14
	mul r0, r5
	add r1, r4, r0
	ldr r0, _0225B3CC ; =0x000004CC
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0225B366
	add r1, sp, #0xc
	add r2, sp, #8
	bl FUN_020119A4
	mov r0, #0x14
	mul r0, r5
	add r1, r4, r0
	ldr r0, _0225B3CC ; =0x000004CC
	ldr r2, [sp, #8]
	ldr r0, [r1, r0]
	ldr r1, [sp, #0xc]
	add r2, r2, #1
	bl FUN_020118C4
_0225B366:
	lsl r0, r5, #2
	add r1, r4, r0
	ldr r0, _0225B3D0 ; =0x00000624
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0225B37A
	mov r1, #0
	mov r2, #1
	bl FUN_0200C82C
_0225B37A:
	add r5, r5, #1
_0225B37C:
	cmp r5, #4
	blt _0225B31C
	mov r0, #0x6b
	lsl r0, r0, #4
	ldrsh r1, [r4, r0]
	add sp, #0x10
	add r1, r1, #1
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_0225B38E:
	add r0, r1, #2
	ldrsh r0, [r4, r0]
	add r2, r0, #1
	add r0, r1, #2
	strh r2, [r4, r0]
	ldrsh r0, [r4, r0]
	cmp r0, #0
	ble _0225B3BE
	mov r2, #0
	add r0, r1, #2
	strh r2, [r4, r0]
	ldrsh r0, [r4, r1]
	add sp, #0x10
	add r0, r0, #1
	strh r0, [r4, r1]
	pop {r3, r4, r5, r6, r7, pc}
_0225B3AE:
	mov r1, #1
	add r0, r4, #0
	add r2, r1, #0
	bl MOD11_0225AC8C
	add r0, r4, #0
	bl MOD11_0225ADB0
_0225B3BE:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225B3C4: .word MOD11_0225F88C
_0225B3C8: .word MOD11_0225F7FC
_0225B3CC: .word 0x000004CC
_0225B3D0: .word 0x00000624

	thumb_func_start MOD11_0225B3D4
MOD11_0225B3D4: ; 0x0225B3D4
	cmp r0, #0
	bne _0225B3DC
	ldr r0, _0225B42C ; =0x00070800
	bx lr
_0225B3DC:
	cmp r1, r0
	bne _0225B3E4
	ldr r0, _0225B430 ; =0x00010200
	bx lr
_0225B3E4:
	cmp r1, #2
	bgt _0225B3F0
	cmp r0, #1
	bne _0225B428
	ldr r0, _0225B434 ; =0x00050600
	bx lr
_0225B3F0:
	cmp r1, #7
	bgt _0225B408
	cmp r0, #1
	beq _0225B3FE
	cmp r0, #2
	beq _0225B402
	b _0225B428
_0225B3FE:
	ldr r0, _0225B434 ; =0x00050600
	bx lr
_0225B402:
	mov r0, #0xc1
	lsl r0, r0, #0xa
	bx lr
_0225B408:
	asr r2, r1, #1
	lsr r2, r2, #0x1e
	add r2, r1, r2
	asr r2, r2, #2
	cmp r0, r2
	bgt _0225B418
	ldr r0, _0225B434 ; =0x00050600
	bx lr
_0225B418:
	lsr r2, r1, #0x1f
	add r2, r1, r2
	asr r1, r2, #1
	cmp r0, r1
	bgt _0225B428
	mov r0, #0xc1
	lsl r0, r0, #0xa
	bx lr
_0225B428:
	ldr r0, _0225B430 ; =0x00010200
	bx lr
	.align 2, 0
_0225B42C: .word 0x00070800
_0225B430: .word 0x00010200
_0225B434: .word 0x00050600

	thumb_func_start MOD11_0225B438
MOD11_0225B438: ; 0x0225B438
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5]
	ldr r0, [r0]
	bl MOD11_0222FF68
	add r4, r0, #0
	ldrb r0, [r5, #0x13]
	cmp r0, #0
	beq _0225B454
	cmp r0, #1
	beq _0225B4AA
	b _0225B4D6
_0225B454:
	mov r2, #8
	ldrsh r1, [r5, r2]
	ldr r0, _0225B528 ; =0x000018E7
	add r1, r1, r0
	strh r1, [r5, #8]
	mov r1, #0xa
	ldrsh r3, [r5, r1]
	mov r1, #0xfa
	lsl r1, r1, #2
	sub r1, r3, r1
	strh r1, [r5, #0xa]
	ldrsh r1, [r5, r2]
	lsl r0, r0, #2
	sub r0, r0, r1
	mov r1, #0x64
	bl _s32_div_f
	strh r0, [r5, #0xc]
	mov r0, #0xa
	ldrsh r0, [r5, r0]
	mov r1, #0x64
	neg r0, r0
	bl _s32_div_f
	strh r0, [r5, #0xe]
	mov r0, #8
	ldrsh r0, [r5, r0]
	cmp r0, #0
	bge _0225B496
	mov r0, #0xa
	ldrsh r0, [r5, r0]
	cmp r0, #0
	bgt _0225B526
_0225B496:
	mov r1, #0
	strh r1, [r5, #8]
	mov r0, #0x90
	strh r0, [r5, #0xa]
	strh r1, [r5, #0xc]
	strh r1, [r5, #0xe]
	ldrb r0, [r5, #0x13]
	add r0, r0, #1
	strb r0, [r5, #0x13]
	pop {r4, r5, r6, pc}
_0225B4AA:
	ldr r1, [r5]
	ldr r0, _0225B52C ; =0x000006A2
	mov r2, #0
	strb r2, [r1, r0]
	ldr r0, [r5, #4]
	bl FUN_0200CAB4
	bl FUN_02015F1C
	ldr r2, _0225B530 ; =0x04001000
	ldr r0, _0225B534 ; =0xFFFF1FFF
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	ldr r0, [r5]
	mov r1, #1
	bl MOD11_0225B77C
	ldrb r0, [r5, #0x13]
	add r0, r0, #1
	strb r0, [r5, #0x13]
	pop {r4, r5, r6, pc}
_0225B4D6:
	ldr r0, [r5]
	bl MOD11_0225B780
	cmp r0, #0
	beq _0225B526
	mov r2, #0
	add r0, r4, #0
	mov r1, #4
	add r3, r2, #0
	bl BgSetPosTextAndCommit
	add r0, r4, #0
	mov r1, #4
	mov r2, #3
	mov r3, #0
	bl BgSetPosTextAndCommit
	mov r2, #0
	add r0, r4, #0
	mov r1, #5
	add r3, r2, #0
	bl BgSetPosTextAndCommit
	add r0, r4, #0
	mov r1, #5
	mov r2, #3
	mov r3, #0
	bl BgSetPosTextAndCommit
	ldr r0, [r5]
	mov r1, #1
	ldr r0, [r0]
	bl MOD11_022312AC
	add r0, r5, #0
	bl FreeToHeap
	add r0, r6, #0
	bl FUN_0200CAB4
_0225B526:
	pop {r4, r5, r6, pc}
	.align 2, 0
_0225B528: .word 0x000018E7
_0225B52C: .word 0x000006A2
_0225B530: .word 0x04001000
_0225B534: .word 0xFFFF1FFF

	thumb_func_start MOD11_0225B538
MOD11_0225B538: ; 0x0225B538
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldr r0, [r5]
	ldr r0, [r0]
	bl MOD11_0222FF68
	add r6, r0, #0
	ldrb r0, [r5, #0x12]
	cmp r0, #4
	bne _0225B586
	mov r0, #0xc
	ldrsh r1, [r5, r0]
	mov r0, #0xff
	sub r3, r0, r1
	cmp r3, #0
	ble _0225B55A
	mov r3, #0
_0225B55A:
	add r0, r6, #0
	mov r1, #4
	mov r2, #0
	bl BgSetPosTextAndCommit
	mov r3, #0xc
	ldrsh r4, [r5, r3]
	mov r3, #0xff
	add r0, r6, #0
	mov r1, #5
	mov r2, #0
	sub r3, r3, r4
	bl BgSetPosTextAndCommit
	mov r0, #8
	ldrsh r0, [r5, r0]
	mov r1, #0x64
	neg r0, r0
	bl _s32_div_f
	add r4, r0, #0
	b _0225B5B6
_0225B586:
	mov r0, #0xc
	ldrsh r3, [r5, r0]
	cmp r3, #0
	bge _0225B590
	mov r3, #0
_0225B590:
	add r0, r6, #0
	mov r1, #4
	mov r2, #0
	bl BgSetPosTextAndCommit
	mov r3, #0xc
	ldrsh r3, [r5, r3]
	add r0, r6, #0
	mov r1, #5
	mov r2, #0
	bl BgSetPosTextAndCommit
	mov r0, #8
	ldrsh r0, [r5, r0]
	mov r1, #0x64
	bl _s32_div_f
	add r4, r0, #0
	add r4, #0xff
_0225B5B6:
	add r0, r6, #0
	mov r1, #4
	mov r2, #3
	mov r3, #0
	bl BgSetPosTextAndCommit
	add r0, r6, #0
	mov r1, #5
	mov r2, #3
	mov r3, #0
	bl BgSetPosTextAndCommit
	mov r0, #0xa
	ldrsh r0, [r5, r0]
	mov r1, #0x64
	bl _s32_div_f
	add r0, #0x90
	cmp r4, #0
	bge _0225B5E2
	mov r4, #0
	b _0225B5E8
_0225B5E2:
	cmp r4, #0xff
	ble _0225B5E8
	mov r4, #0xff
_0225B5E8:
	cmp r0, #0xc0
	ble _0225B5F0
	mov r0, #0xc0
	b _0225B5F6
_0225B5F0:
	cmp r0, #0
	bge _0225B5F6
	mov r0, #0
_0225B5F6:
	ldrb r1, [r5, #0x12]
	cmp r1, #4
	bne _0225B60A
	lsl r1, r4, #0x18
	ldr r2, _0225B63C ; =0x04001040
	lsr r1, r1, #0x18
	strh r1, [r2]
	mov r1, #0x90
	strh r1, [r2, #4]
	b _0225B620
_0225B60A:
	cmp r4, #0
	bne _0225B610
	mov r4, #1
_0225B610:
	mov r1, #0xff
	lsl r2, r4, #8
	lsl r1, r1, #8
	and r1, r2
	ldr r2, _0225B63C ; =0x04001040
	strh r1, [r2]
	mov r1, #0x90
	strh r1, [r2, #4]
_0225B620:
	ldr r2, _0225B640 ; =0x04001042
	mov r1, #0xff
	lsl r0, r0, #0x18
	strh r1, [r2]
	lsr r1, r0, #0x18
	mov r0, #9
	lsl r0, r0, #0xc
	orr r0, r1
	strh r0, [r2, #4]
	mov r0, #0xe
	ldrsh r0, [r5, r0]
	strh r0, [r5, #0x10]
	pop {r4, r5, r6, pc}
	nop
_0225B63C: .word 0x04001040
_0225B640: .word 0x04001042

	thumb_func_start MOD11_0225B644
MOD11_0225B644: ; 0x0225B644
	push {r4, r5, r6, lr}
	add r4, r0, #0
	ldr r0, _0225B6FC ; =0x04000006
	ldrh r0, [r0]
	cmp r0, #0x90
	bne _0225B68E
	ldr r0, [r4]
	ldr r0, [r0]
	bl MOD11_0222FF68
	mov r2, #0
	mov r1, #4
	add r3, r2, #0
	add r5, r0, #0
	bl BgSetPosTextAndCommit
	mov r3, #0x10
	ldrsh r3, [r4, r3]
	add r0, r5, #0
	mov r1, #4
	mov r2, #3
	bl BgSetPosTextAndCommit
	mov r2, #0
	add r0, r5, #0
	mov r1, #5
	add r3, r2, #0
	bl BgSetPosTextAndCommit
	mov r3, #0x10
	ldrsh r3, [r4, r3]
	add r0, r5, #0
	mov r1, #5
	mov r2, #3
	bl BgSetPosTextAndCommit
	pop {r4, r5, r6, pc}
_0225B68E:
	cmp r0, #0xc0
	ble _0225B6F8
	ldr r0, [r4]
	ldr r0, [r0]
	bl MOD11_0222FF68
	ldrb r1, [r4, #0x12]
	add r5, r0, #0
	cmp r1, #4
	bne _0225B6C6
	mov r3, #0xc
	ldrsh r6, [r4, r3]
	mov r3, #0xff
	mov r1, #4
	mov r2, #0
	sub r3, r3, r6
	bl BgSetPosTextAndCommit
	mov r3, #0xc
	ldrsh r4, [r4, r3]
	mov r3, #0xff
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	sub r3, r3, r4
	bl BgSetPosTextAndCommit
	b _0225B6E0
_0225B6C6:
	mov r3, #0xc
	ldrsh r3, [r4, r3]
	mov r1, #4
	mov r2, #0
	bl BgSetPosTextAndCommit
	mov r3, #0xc
	ldrsh r3, [r4, r3]
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl BgSetPosTextAndCommit
_0225B6E0:
	add r0, r5, #0
	mov r1, #4
	mov r2, #3
	mov r3, #0
	bl BgSetPosTextAndCommit
	add r0, r5, #0
	mov r1, #5
	mov r2, #3
	mov r3, #0
	bl BgSetPosTextAndCommit
_0225B6F8:
	pop {r4, r5, r6, pc}
	nop
_0225B6FC: .word 0x04000006

	thumb_func_start MOD11_0225B700
MOD11_0225B700: ; 0x0225B700
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	ldr r0, _0225B760 ; =0x0000069F
	ldr r2, _0225B764 ; =MOD11_0225FAAC
	ldrsb r1, [r1, r0]
	mov r0, #0x30
	ldr r7, _0225B768 ; =0x0000FFFF
	mul r0, r1
	add r6, r2, r0
	mov r4, #0
	add r5, r6, #0
_0225B716:
	ldrh r0, [r5, #4]
	cmp r0, r7
	bne _0225B72A
	add r0, r4, #4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r1, #0
	bl ToggleBgLayer
	b _0225B736
_0225B72A:
	add r0, r4, #4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r1, #1
	bl ToggleBgLayer
_0225B736:
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, #4
	blt _0225B716
	mov r4, #0
_0225B740:
	ldrh r1, [r6, #0xc]
	add r0, r4, #4
	lsl r0, r0, #0x18
	lsl r1, r1, #0x18
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl SetBgPriority
	add r4, r4, #1
	add r6, r6, #2
	cmp r4, #4
	blt _0225B740
	ldr r0, [sp]
	bl FUN_0200CAB4
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225B760: .word 0x0000069F
_0225B764: .word MOD11_0225FAAC
_0225B768: .word 0x0000FFFF

	thumb_func_start MOD11_0225B76C
MOD11_0225B76C: ; 0x0225B76C
	push {r4, lr}
	add r4, r0, #0
	bl MOD11_0225AC60
	add r0, r4, #0
	bl FUN_0200CAB4
	pop {r4, pc}

	thumb_func_start MOD11_0225B77C
MOD11_0225B77C: ; 0x0225B77C
	bx lr
	.align 2, 0

	thumb_func_start MOD11_0225B780
MOD11_0225B780: ; 0x0225B780
	ldr r1, _0225B790 ; =0x00000698
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _0225B78C
	mov r0, #1
	bx lr
_0225B78C:
	mov r0, #0
	bx lr
	.align 2, 0
_0225B790: .word 0x00000698

	thumb_func_start MOD11_0225B794
MOD11_0225B794: ; 0x0225B794
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r1, #0
	ldr r0, [r5]
	bl MOD11_022300CC
	add r4, r0, #0
	bl FUN_020038E4
	cmp r0, #0
	bne _0225B814
	ldr r0, _0225B818 ; =0x000006AA
	mov r1, #1
	ldrsh r0, [r5, r0]
	add r2, r1, #0
	add r3, r1, #0
	asr r0, r0, #8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, _0225B81C ; =0x00007FFF
	str r0, [sp, #4]
	add r0, r4, #0
	bl BlendPaletteUnfaded
	ldr r1, _0225B820 ; =0x000006A8
_0225B7C8:
	ldrb r0, [r5, r1]
	cmp r0, #0
	bne _0225B7DA
	add r0, r1, #2
	ldrsh r2, [r5, r0]
	mov r0, #2
	lsl r0, r0, #8
	add r2, r2, r0
	b _0225B7E4
_0225B7DA:
	add r0, r1, #2
	ldrsh r2, [r5, r0]
	mov r0, #2
	lsl r0, r0, #8
	sub r2, r2, r0
_0225B7E4:
	add r0, r1, #2
	strh r2, [r5, r0]
	ldr r0, _0225B818 ; =0x000006AA
	mov r1, #0x11
	ldrsh r2, [r5, r0]
	lsl r1, r1, #8
	cmp r2, r1
	blt _0225B804
	mov r1, #0xf
	lsl r1, r1, #8
	strh r1, [r5, r0]
	mov r1, #1
	sub r0, r0, #2
	add sp, #8
	strb r1, [r5, r0]
	pop {r3, r4, r5, pc}
_0225B804:
	cmp r2, #0
	bgt _0225B814
	mov r1, #1
	lsl r1, r1, #8
	strh r1, [r5, r0]
	mov r1, #0
	sub r0, r0, #2
	strb r1, [r5, r0]
_0225B814:
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_0225B818: .word 0x000006AA
_0225B81C: .word 0x00007FFF
_0225B820: .word 0x000006A8

	thumb_func_start MOD11_0225B824
MOD11_0225B824: ; 0x0225B824
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	bl FUN_02002BD4
	add r6, r0, #0
	bl FUN_02002BF4
	add r7, r0, #0
	bl FUN_02002BE4
	bl FUN_02002C04
	ldr r0, [r5]
	bl MOD11_022300CC
	add r4, r0, #0
	bl FUN_020038E4
	cmp r0, #0
	bne _0225B8A8
	add r0, r4, #0
	mov r1, #1
	bl PaletteData_GetFadedBuf
	add r4, r0, #0
	ldr r0, _0225B8AC ; =gMain + 0x40
	ldrh r0, [r0, #0x22]
	cmp r0, #0
	beq _0225B888
	cmp r6, #1
	beq _0225B866
	cmp r7, #1
	bne _0225B888
_0225B866:
	ldr r1, [r5, #0x5c]
	add r0, r4, #0
	add r0, #0x16
	add r1, #0x16
	mov r2, #0xa
	bl memcmp
	cmp r0, #0
	bne _0225B8A8
	ldr r0, [r5, #0x60]
	add r4, #0x16
	add r0, #0x16
	add r1, r4, #0
	mov r2, #0xa
	bl MIi_CpuCopy16
	pop {r3, r4, r5, r6, r7, pc}
_0225B888:
	ldr r1, [r5, #0x60]
	add r0, r4, #0
	add r0, #0x16
	add r1, #0x16
	mov r2, #0xa
	bl memcmp
	cmp r0, #0
	bne _0225B8A8
	ldr r0, [r5, #0x5c]
	add r4, #0x16
	add r0, #0x16
	add r1, r4, #0
	mov r2, #0xa
	bl MIi_CpuCopy16
_0225B8A8:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225B8AC: .word gMain + 0x40

	thumb_func_start MOD11_0225B8B0
MOD11_0225B8B0: ; 0x0225B8B0
	push {r4, r5, r6, lr}
	mov r6, #0x6f
	lsl r6, r6, #4
	add r2, r6, #0
	add r5, r0, #0
	sub r2, #0x51
	ldrsb r2, [r5, r2]
	ldr r1, _0225B914 ; =MOD11_0225FAAC
	mov r3, #0x30
	add r4, r2, #0
	mul r4, r3
	add r4, r1, r4
	ldr r2, [r4, #0x20]
	cmp r2, #0
	bne _0225B8D4
	sub r3, #0x31
	add r0, r3, #0
	pop {r4, r5, r6, pc}
_0225B8D4:
	ldrb r1, [r5, r6]
	cmp r1, #0
	bne _0225B90C
	add r0, r6, #4
	ldrb r0, [r5, r0]
	cmp r0, #1
	beq _0225B8EC
	ldr r1, _0225B918 ; =gMain
	ldr r2, [r1, #0x48]
	ldr r1, _0225B91C ; =0x00000CF3
	tst r1, r2
	beq _0225B906
_0225B8EC:
	cmp r0, #0
	bne _0225B8F6
	ldr r0, _0225B920 ; =0x000005DC
	bl PlaySE
_0225B8F6:
	mov r1, #1
	ldr r0, _0225B924 ; =0x000006F4
	strb r1, [r5, r6]
	mov r2, #0
	strb r2, [r5, r0]
	ldr r2, [r4, #0x20]
	add r0, r5, #0
	blx r2
_0225B906:
	mov r0, #0
	mvn r0, r0
	pop {r4, r5, r6, pc}
_0225B90C:
	mov r1, #0
	blx r2
	pop {r4, r5, r6, pc}
	nop
_0225B914: .word MOD11_0225FAAC
_0225B918: .word gMain
_0225B91C: .word 0x00000CF3
_0225B920: .word 0x000005DC
_0225B924: .word 0x000006F4

	thumb_func_start MOD11_0225B928
MOD11_0225B928: ; 0x0225B928
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r1, [sp, #8]
	mov r1, #0x6f
	lsl r1, r1, #4
	add r6, r0, #0
	add r2, r1, #0
	sub r2, #0x51
	ldrsb r3, [r6, r2]
	add r4, r6, r1
	mov r2, #0x30
	sub r1, #0x52
	ldr r0, _0225BAE8 ; =MOD11_0225FAAC
	mul r2, r3
	add r7, r0, r2
	ldrb r1, [r6, r1]
	ldr r0, [r6]
	bl MOD11_0223022C
	add r1, r0, #0
	ldr r0, [r6]
	bl MOD11_0222FF7C
	bl MOD11_02253A74
	ldr r1, [sp, #8]
	cmp r1, #1
	bne _0225B9AE
	mov r1, #0
	ldrsb r1, [r0, r1]
	ldr r2, _0225BAEC ; =MOD11_0225F698
	strb r1, [r4, #2]
	mov r1, #1
	ldrsb r0, [r0, r1]
	strb r0, [r4, #1]
	ldrsb r1, [r4, r1]
	lsl r0, r1, #1
	add r3, r1, r0
	mov r0, #2
	ldrsb r1, [r4, r0]
	add r0, r2, r3
	ldrb r1, [r1, r0]
	ldr r0, [r7, #0x14]
	lsl r3, r1, #2
	add r0, r0, r3
	ldrb r0, [r0, #1]
	sub r0, #8
	str r0, [sp]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r4, [r7, #0x14]
	ldr r0, _0225BAF0 ; =0x000006EC
	add r2, r4, r3
	ldrb r1, [r2, #2]
	ldrb r2, [r2, #3]
	ldrb r3, [r4, r3]
	ldr r0, [r6, r0]
	add r1, #8
	sub r2, #8
	add r3, #8
	bl MOD11_0225D5FC
	mov r0, #0
	add sp, #0x10
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_0225B9AE:
	ldr r0, _0225BAF4 ; =0x0000069F
	ldrsb r0, [r6, r0]
	cmp r0, #5
	beq _0225B9BA
	cmp r0, #6
	bne _0225B9CA
_0225B9BA:
	mov r1, #1
	ldr r3, _0225BAEC ; =MOD11_0225F698
	add r0, r4, #0
	add r2, r1, #0
	bl MOD11_0225C574
	add r5, r0, #0
	b _0225BA34
_0225B9CA:
	mov r0, #1
	ldrsb r1, [r4, r0]
	lsl r0, r1, #1
	add r2, r1, r0
	mov r0, #2
	ldr r1, _0225BAEC ; =MOD11_0225F698
	ldrsb r0, [r4, r0]
	add r1, r1, r2
	ldrb r0, [r0, r1]
	str r0, [sp, #0xc]
	cmp r0, #3
	bne _0225B9EC
	ldr r0, _0225BAF8 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x40
	tst r0, r1
	bne _0225BA34
_0225B9EC:
	ldr r3, _0225BAEC ; =MOD11_0225F698
	add r0, r4, #0
	mov r1, #3
	mov r2, #2
	bl MOD11_0225C574
	add r5, r0, #0
	bne _0225BA34
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bne _0225BA34
	ldr r0, _0225BAF8 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x20
	tst r0, r1
	beq _0225BA1E
	mov r0, #0
	strb r0, [r4, #2]
	mov r0, #1
	strb r0, [r4, #1]
	ldr r0, _0225BAFC ; =0x000005DC
	bl PlaySE
	mov r5, #0x20
	b _0225BA34
_0225BA1E:
	mov r0, #0x10
	tst r0, r1
	beq _0225BA34
	mov r0, #2
	strb r0, [r4, #2]
	mov r0, #1
	strb r0, [r4, #1]
	ldr r0, _0225BAFC ; =0x000005DC
	bl PlaySE
	mov r5, #0x10
_0225BA34:
	cmp r5, #0x20
	bhi _0225BA50
	bhs _0225BA5C
	cmp r5, #2
	bhi _0225BA4A
	cmp r5, #1
	blo _0225BAE0
	beq _0225BA9A
	cmp r5, #2
	beq _0225BAB0
	b _0225BAE0
_0225BA4A:
	cmp r5, #0x10
	beq _0225BA5C
	b _0225BAE0
_0225BA50:
	cmp r5, #0x40
	bhi _0225BA58
	beq _0225BA5C
	b _0225BAE0
_0225BA58:
	cmp r5, #0x80
	bne _0225BAE0
_0225BA5C:
	mov r0, #1
	ldrsb r1, [r4, r0]
	ldr r2, _0225BAEC ; =MOD11_0225F698
	lsl r0, r1, #1
	add r3, r1, r0
	mov r0, #2
	ldrsb r1, [r4, r0]
	add r0, r2, r3
	ldrb r1, [r1, r0]
	ldr r0, [r7, #0x14]
	lsl r3, r1, #2
	add r0, r0, r3
	ldrb r0, [r0, #1]
	sub r0, #8
	str r0, [sp]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r4, [r7, #0x14]
	ldr r0, _0225BAF0 ; =0x000006EC
	add r2, r4, r3
	ldrb r1, [r2, #2]
	ldrb r2, [r2, #3]
	ldrb r3, [r4, r3]
	ldr r0, [r6, r0]
	add r1, #8
	sub r2, #8
	add r3, #8
	bl MOD11_0225D5FC
	b _0225BAE0
_0225BA9A:
	mov r0, #1
	ldrsb r1, [r4, r0]
	ldr r2, _0225BAEC ; =MOD11_0225F698
	add sp, #0x10
	lsl r0, r1, #1
	add r3, r1, r0
	mov r0, #2
	ldrsb r1, [r4, r0]
	add r0, r2, r3
	ldrb r0, [r1, r0]
	pop {r3, r4, r5, r6, r7, pc}
_0225BAB0:
	ldr r0, _0225BB00 ; =0x000006A3
	ldrb r0, [r6, r0]
	cmp r0, #1
	bne _0225BAE0
	mov r0, #0
	add r2, r0, #0
	mov r3, #1
	ldr r1, [r7, #0x18]
	ldr r5, [r7, #0x14]
	b _0225BACE
_0225BAC4:
	lsl r4, r0, #2
	ldr r4, [r1, r4]
	cmp r4, #4
	beq _0225BAE4
	add r0, r0, #1
_0225BACE:
	lsl r4, r0, #2
	ldrb r4, [r5, r4]
	cmp r0, r4
	bge _0225BADA
	add r4, r3, #0
	b _0225BADC
_0225BADA:
	add r4, r2, #0
_0225BADC:
	cmp r4, #0xff
	bne _0225BAC4
_0225BAE0:
	mov r0, #0
	mvn r0, r0
_0225BAE4:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225BAE8: .word MOD11_0225FAAC
_0225BAEC: .word MOD11_0225F698
_0225BAF0: .word 0x000006EC
_0225BAF4: .word 0x0000069F
_0225BAF8: .word gMain
_0225BAFC: .word 0x000005DC
_0225BB00: .word 0x000006A3

	thumb_func_start MOD11_0225BB04
MOD11_0225BB04: ; 0x0225BB04
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r1, _0225BB60 ; =0x0000069E
	ldr r0, [r5]
	ldrb r1, [r5, r1]
	bl MOD11_0223022C
	add r6, r0, #0
	cmp r4, #3
	bne _0225BB26
	ldr r0, [r5]
	add r1, r6, #0
	bl MOD11_02230CB8
	cmp r0, #0
	bne _0225BB5C
_0225BB26:
	ldr r0, [r5]
	add r1, r6, #0
	bl MOD11_0222FF7C
	bl MOD11_02253A74
	mov r5, #0
	ldr r1, _0225BB64 ; =MOD11_0225F698
	add r2, r5, #0
	b _0225BB58
_0225BB3A:
	lsl r6, r5, #1
	add r6, r5, r6
	add r3, r2, #0
	add r7, r1, r6
	b _0225BB52
_0225BB44:
	ldrb r6, [r3, r7]
	cmp r4, r6
	bne _0225BB50
	strb r3, [r0]
	strb r5, [r0, #1]
	pop {r3, r4, r5, r6, r7, pc}
_0225BB50:
	add r3, r3, #1
_0225BB52:
	cmp r3, #3
	blt _0225BB44
	add r5, r5, #1
_0225BB58:
	cmp r5, #2
	blt _0225BB3A
_0225BB5C:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225BB60: .word 0x0000069E
_0225BB64: .word MOD11_0225F698

	thumb_func_start MOD11_0225BB68
MOD11_0225BB68: ; 0x0225BB68
	push {r4, r5, r6, lr}
	sub sp, #8
	add r6, r0, #0
	mov r0, #0x6f
	lsl r0, r0, #4
	add r3, r0, #0
	sub r3, #0x51
	ldrsb r5, [r6, r3]
	mov r3, #0x30
	ldr r2, _0225BC54 ; =MOD11_0225FAAC
	mul r3, r5
	add r4, r6, r0
	add r5, r2, r3
	cmp r1, #1
	bne _0225BBCC
	mov r1, #0
	strb r1, [r4, #2]
	strb r1, [r4, #1]
	mov r1, #1
	ldrsb r2, [r4, r1]
	mov r3, #2
	ldr r1, _0225BC58 ; =MOD11_0225F688
	ldrsb r3, [r4, r3]
	add r1, r1, r2
	sub r0, r0, #4
	ldrb r2, [r3, r1]
	ldr r1, [r5, #0x14]
	lsl r3, r2, #2
	add r1, r1, r3
	ldrb r1, [r1, #1]
	sub r1, #8
	str r1, [sp]
	mov r1, #0x11
	lsl r1, r1, #0x10
	str r1, [sp, #4]
	ldr r4, [r5, #0x14]
	ldr r0, [r6, r0]
	add r2, r4, r3
	ldrb r1, [r2, #2]
	ldrb r2, [r2, #3]
	ldrb r3, [r4, r3]
	add r1, #8
	sub r2, #8
	add r3, #8
	bl MOD11_0225D5FC
	mov r0, #0
	add sp, #8
	mvn r0, r0
	pop {r4, r5, r6, pc}
_0225BBCC:
	ldr r3, _0225BC58 ; =MOD11_0225F688
	add r0, r4, #0
	mov r1, #1
	mov r2, #2
	bl MOD11_0225C574
	cmp r0, #0x20
	bhi _0225BBF2
	bhs _0225BBFE
	cmp r0, #2
	bhi _0225BBEC
	cmp r0, #1
	blo _0225BC4A
	beq _0225BC38
	cmp r0, #2
	b _0225BC4A
_0225BBEC:
	cmp r0, #0x10
	beq _0225BBFE
	b _0225BC4A
_0225BBF2:
	cmp r0, #0x40
	bhi _0225BBFA
	beq _0225BBFE
	b _0225BC4A
_0225BBFA:
	cmp r0, #0x80
	bne _0225BC4A
_0225BBFE:
	mov r0, #1
	ldrsb r3, [r4, r0]
	mov r0, #2
	ldr r2, _0225BC58 ; =MOD11_0225F688
	ldrsb r1, [r4, r0]
	add r0, r2, r3
	ldrb r1, [r1, r0]
	ldr r0, [r5, #0x14]
	lsl r3, r1, #2
	add r0, r0, r3
	ldrb r0, [r0, #1]
	sub r0, #8
	str r0, [sp]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r4, [r5, #0x14]
	ldr r0, _0225BC5C ; =0x000006EC
	add r2, r4, r3
	ldrb r1, [r2, #2]
	ldrb r2, [r2, #3]
	ldrb r3, [r4, r3]
	ldr r0, [r6, r0]
	add r1, #8
	sub r2, #8
	add r3, #8
	bl MOD11_0225D5FC
	b _0225BC4A
_0225BC38:
	mov r0, #1
	ldrsb r3, [r4, r0]
	mov r0, #2
	ldr r2, _0225BC58 ; =MOD11_0225F688
	ldrsb r1, [r4, r0]
	add r0, r2, r3
	add sp, #8
	ldrb r0, [r1, r0]
	pop {r4, r5, r6, pc}
_0225BC4A:
	mov r0, #0
	mvn r0, r0
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_0225BC54: .word MOD11_0225FAAC
_0225BC58: .word MOD11_0225F688
_0225BC5C: .word 0x000006EC

	thumb_func_start MOD11_0225BC60
MOD11_0225BC60: ; 0x0225BC60
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r1, #0
	add r5, r0, #0
	ldr r1, _0225BDD0 ; =0x0000069E
	ldr r0, [r5]
	ldrb r1, [r5, r1]
	bl MOD11_0223022C
	add r1, r0, #0
	ldr r0, [r5]
	bl MOD11_0222FF7C
	bl MOD11_02253A74
	mov r1, #0x6f
	lsl r1, r1, #4
	add r4, r5, r1
	sub r1, #0x51
	ldrsb r2, [r5, r1]
	add r3, r0, #0
	mov r1, #0x30
	mul r1, r2
	ldr r0, _0225BDD4 ; =MOD11_0225FAAC
	add r2, r5, #0
	add r6, r0, r1
	add r2, #0x18
	cmp r7, #1
	bne _0225BD10
	mov r0, #2
	ldrsb r0, [r3, r0]
	strb r0, [r4, #2]
	mov r0, #3
	ldrsb r0, [r3, r0]
	strb r0, [r4, #1]
	mov r0, #1
	ldrsb r0, [r4, r0]
	lsl r1, r0, #1
	mov r0, #2
	ldrsb r7, [r4, r0]
	ldr r0, _0225BDD8 ; =MOD11_0225F6A0
	add r0, r0, r1
	ldrb r0, [r7, r0]
	cmp r0, #0
	beq _0225BCDE
	sub r1, r0, #1
	lsl r1, r1, #1
	ldrh r1, [r2, r1]
	cmp r1, #0
	bne _0225BCDE
	mov r0, #0
	strb r0, [r3, #2]
	strb r0, [r3, #3]
	strb r0, [r4, #2]
	strb r0, [r4, #1]
	mov r0, #1
	ldrsb r0, [r4, r0]
	lsl r2, r0, #1
	mov r0, #2
	ldrsb r1, [r4, r0]
	ldr r0, _0225BDD8 ; =MOD11_0225F6A0
	add r0, r0, r2
	ldrb r0, [r1, r0]
_0225BCDE:
	ldr r1, [r6, #0x14]
	lsl r3, r0, #2
	add r0, r1, r3
	ldrb r0, [r0, #1]
	sub r0, #8
	str r0, [sp]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r4, [r6, #0x14]
	ldr r0, _0225BDDC ; =0x000006EC
	add r2, r4, r3
	ldrb r1, [r2, #2]
	ldrb r2, [r2, #3]
	ldrb r3, [r4, r3]
	ldr r0, [r5, r0]
	add r1, #8
	sub r2, #8
	add r3, #8
	bl MOD11_0225D5FC
	mov r0, #0
	add sp, #0x10
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_0225BD10:
	ldr r0, _0225BDD8 ; =MOD11_0225F6A0
	add r1, sp, #8
	mov r2, #6
	bl MI_CpuCopy8
	add r0, r4, #0
	mov r1, #2
	mov r2, #3
	add r3, sp, #8
	bl MOD11_0225C574
	cmp r0, #0x20
	bhi _0225BD42
	bhs _0225BD4E
	cmp r0, #2
	bhi _0225BD3C
	cmp r0, #1
	blo _0225BDC6
	beq _0225BD8A
	cmp r0, #2
	beq _0225BD9E
	b _0225BDC6
_0225BD3C:
	cmp r0, #0x10
	beq _0225BD4E
	b _0225BDC6
_0225BD42:
	cmp r0, #0x40
	bhi _0225BD4A
	beq _0225BD4E
	b _0225BDC6
_0225BD4A:
	cmp r0, #0x80
	bne _0225BDC6
_0225BD4E:
	mov r0, #1
	ldrsb r0, [r4, r0]
	ldr r2, _0225BDD8 ; =MOD11_0225F6A0
	lsl r3, r0, #1
	mov r0, #2
	ldrsb r1, [r4, r0]
	add r0, r2, r3
	ldrb r1, [r1, r0]
	ldr r0, [r6, #0x14]
	lsl r3, r1, #2
	add r0, r0, r3
	ldrb r0, [r0, #1]
	sub r0, #8
	str r0, [sp]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r4, [r6, #0x14]
	ldr r0, _0225BDDC ; =0x000006EC
	add r2, r4, r3
	ldrb r1, [r2, #2]
	ldrb r2, [r2, #3]
	ldrb r3, [r4, r3]
	ldr r0, [r5, r0]
	add r1, #8
	sub r2, #8
	add r3, #8
	bl MOD11_0225D5FC
	b _0225BDC6
_0225BD8A:
	mov r0, #1
	ldrsb r0, [r4, r0]
	ldr r2, _0225BDD8 ; =MOD11_0225F6A0
	add sp, #0x10
	lsl r3, r0, #1
	mov r0, #2
	ldrsb r1, [r4, r0]
	add r0, r2, r3
	ldrb r0, [r1, r0]
	pop {r3, r4, r5, r6, r7, pc}
_0225BD9E:
	mov r0, #0
	add r2, r0, #0
	mov r3, #1
	ldr r1, [r6, #0x18]
	ldr r5, [r6, #0x14]
	b _0225BDB4
_0225BDAA:
	lsl r4, r0, #2
	ldr r4, [r1, r4]
	cmp r4, #0xff
	beq _0225BDCA
	add r0, r0, #1
_0225BDB4:
	lsl r4, r0, #2
	ldrb r4, [r5, r4]
	cmp r0, r4
	bge _0225BDC0
	add r4, r3, #0
	b _0225BDC2
_0225BDC0:
	add r4, r2, #0
_0225BDC2:
	cmp r4, #0xff
	bne _0225BDAA
_0225BDC6:
	mov r0, #0
	mvn r0, r0
_0225BDCA:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225BDD0: .word 0x0000069E
_0225BDD4: .word MOD11_0225FAAC
_0225BDD8: .word MOD11_0225F6A0
_0225BDDC: .word 0x000006EC

	thumb_func_start MOD11_0225BDE0
MOD11_0225BDE0: ; 0x0225BDE0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	beq _0225BE26
	ldr r1, _0225BE28 ; =0x0000069E
	ldr r0, [r5]
	ldrb r1, [r5, r1]
	bl MOD11_0223022C
	add r1, r0, #0
	ldr r0, [r5]
	bl MOD11_0222FF7C
	bl MOD11_02253A74
	mov r3, #0
	ldr r7, _0225BE2C ; =MOD11_0225F6A0
	add r1, r3, #0
	b _0225BE22
_0225BE06:
	lsl r5, r3, #1
	add r2, r1, #0
	add r6, r7, r5
	b _0225BE1C
_0225BE0E:
	ldrb r5, [r2, r6]
	cmp r4, r5
	bne _0225BE1A
	strb r2, [r0, #2]
	strb r3, [r0, #3]
	pop {r3, r4, r5, r6, r7, pc}
_0225BE1A:
	add r2, r2, #1
_0225BE1C:
	cmp r2, #2
	blt _0225BE0E
	add r3, r3, #1
_0225BE22:
	cmp r3, #3
	blt _0225BE06
_0225BE26:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225BE28: .word 0x0000069E
_0225BE2C: .word MOD11_0225F6A0

	thumb_func_start MOD11_0225BE30
MOD11_0225BE30: ; 0x0225BE30
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x60
	str r1, [sp, #0x18]
	add r6, r0, #0
	ldr r1, _0225C134 ; =0x0000069E
	mov r0, #0
	str r0, [sp, #0x44]
	ldrb r1, [r6, r1]
	ldr r0, [r6]
	bl MOD11_0223022C
	add r1, r0, #0
	ldr r0, [r6]
	bl MOD11_0222FF7C
	bl MOD11_02253A74
	mov r1, #0x6f
	lsl r1, r1, #4
	add r7, r6, r1
	sub r1, #0x51
	ldrsb r2, [r6, r1]
	str r0, [sp, #0x1c]
	mov r1, #0x30
	mul r1, r2
	ldr r0, _0225C138 ; =MOD11_0225FAAC
	mov r2, #6
	add r0, r0, r1
	str r0, [sp, #0x48]
	ldr r0, _0225C13C ; =MOD11_0225F690
	add r1, sp, #0x50
	bl MI_CpuCopy8
	add r1, sp, #0x58
	add r0, r6, #0
	add r1, #2
	mov r2, #1
	bl MOD11_0225ACD4
	add r1, sp, #0x54
	add r0, r6, #0
	add r1, #2
	mov r2, #0
	bl MOD11_0225ACD4
	add r0, sp, #0x54
	mov r2, #0
	mov r4, #0xff
	add r0, #2
	b _0225BEB0
_0225BE94:
	lsl r5, r2, #1
	add r1, sp, #0x50
	mov r3, #0
	add r1, r1, r5
	b _0225BEAA
_0225BE9E:
	ldrb r5, [r3, r1]
	ldrb r5, [r0, r5]
	cmp r5, #0
	bne _0225BEA8
	strb r4, [r3, r1]
_0225BEA8:
	add r3, r3, #1
_0225BEAA:
	cmp r3, #2
	blt _0225BE9E
	add r2, r2, #1
_0225BEB0:
	cmp r2, #2
	blt _0225BE94
	mov r0, #0x6a
	lsl r0, r0, #4
	ldrb r0, [r6, r0]
	cmp r0, #0xb
	bhi _0225BEE2
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0225BECA: ; jump table
	.short _0225BEE2 - _0225BECA - 2 ; case 0
	.short _0225BEEC - _0225BECA - 2 ; case 1
	.short _0225BEEC - _0225BECA - 2 ; case 2
	.short _0225BEEC - _0225BECA - 2 ; case 3
	.short _0225BEE2 - _0225BECA - 2 ; case 4
	.short _0225BEEC - _0225BECA - 2 ; case 5
	.short _0225BEE2 - _0225BECA - 2 ; case 6
	.short _0225BEEC - _0225BECA - 2 ; case 7
	.short _0225BEE2 - _0225BECA - 2 ; case 8
	.short _0225BEE2 - _0225BECA - 2 ; case 9
	.short _0225BEE2 - _0225BECA - 2 ; case 10
	.short _0225BEE2 - _0225BECA - 2 ; case 11
_0225BEE2:
	mov r0, #2
	mov ip, r0
	mov r0, #3
	str r0, [sp, #0x4c]
	b _0225C0C6
_0225BEEC:
	mov r0, #1
	str r0, [sp, #0x44]
	mov ip, r0
	mov r0, #2
	str r0, [sp, #0x4c]
	add r0, sp, #0x50
	ldrb r1, [r0, #9]
	cmp r1, #1
	bne _0225BF26
	ldrb r0, [r0, #7]
	cmp r0, #1
	bne _0225BF26
	ldr r0, [sp, #0x48]
	ldr r1, [r0, #0x14]
	ldrb r0, [r1, #0xe]
	ldrb r2, [r1, #0xd]
	str r0, [sp, #0x34]
	add r0, #8
	str r0, [sp, #0x34]
	ldrb r0, [r1, #7]
	sub r2, #8
	str r0, [sp, #0x30]
	sub r0, #8
	str r0, [sp, #0x30]
	ldrb r0, [r1, #0xc]
	str r0, [sp, #0x38]
	add r0, #8
	str r0, [sp, #0x38]
	b _0225BF92
_0225BF26:
	add r0, sp, #0x50
	ldrb r1, [r0, #9]
	cmp r1, #1
	bne _0225BF56
	ldrb r0, [r0, #7]
	cmp r0, #0
	bne _0225BF56
	ldr r0, [sp, #0x48]
	ldr r1, [r0, #0x14]
	ldrb r0, [r1, #0xe]
	ldrb r2, [r1, #0xd]
	str r0, [sp, #0x34]
	add r0, #8
	str r0, [sp, #0x34]
	ldrb r0, [r1, #0xf]
	sub r2, #8
	str r0, [sp, #0x30]
	sub r0, #8
	str r0, [sp, #0x30]
	ldrb r0, [r1, #0xc]
	str r0, [sp, #0x38]
	add r0, #8
	str r0, [sp, #0x38]
	b _0225BF92
_0225BF56:
	add r0, sp, #0x50
	ldrb r1, [r0, #9]
	cmp r1, #0
	bne _0225BF86
	ldrb r0, [r0, #7]
	cmp r0, #1
	bne _0225BF86
	ldr r0, [sp, #0x48]
	ldr r1, [r0, #0x14]
	ldrb r0, [r1, #6]
	ldrb r2, [r1, #5]
	str r0, [sp, #0x34]
	add r0, #8
	str r0, [sp, #0x34]
	ldrb r0, [r1, #7]
	sub r2, #8
	str r0, [sp, #0x30]
	sub r0, #8
	str r0, [sp, #0x30]
	ldrb r0, [r1, #4]
	str r0, [sp, #0x38]
	add r0, #8
	str r0, [sp, #0x38]
	b _0225BF92
_0225BF86:
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x34]
	str r0, [sp, #0x30]
	str r0, [sp, #0x38]
	add r2, r0, #0
_0225BF92:
	add r0, sp, #0x50
	ldrb r1, [r0, #6]
	cmp r1, #1
	bne _0225BFBA
	ldrb r0, [r0, #8]
	cmp r0, #1
	bne _0225BFBA
	ldr r0, [sp, #0x48]
	ldr r0, [r0, #0x14]
	ldrb r3, [r0, #2]
	ldrb r4, [r0, #0xb]
	ldrb r5, [r0]
	ldrb r0, [r0, #1]
	add r3, #8
	sub r4, #8
	str r0, [sp, #0x2c]
	sub r0, #8
	add r5, #8
	str r0, [sp, #0x2c]
	b _0225C014
_0225BFBA:
	add r0, sp, #0x50
	ldrb r1, [r0, #6]
	cmp r1, #1
	bne _0225BFE2
	ldrb r0, [r0, #8]
	cmp r0, #0
	bne _0225BFE2
	ldr r0, [sp, #0x48]
	ldr r0, [r0, #0x14]
	ldrb r3, [r0, #2]
	ldrb r4, [r0, #3]
	ldrb r5, [r0]
	ldrb r0, [r0, #1]
	add r3, #8
	sub r4, #8
	str r0, [sp, #0x2c]
	sub r0, #8
	add r5, #8
	str r0, [sp, #0x2c]
	b _0225C014
_0225BFE2:
	add r0, sp, #0x50
	ldrb r1, [r0, #6]
	cmp r1, #0
	bne _0225C00A
	ldrb r0, [r0, #8]
	cmp r0, #1
	bne _0225C00A
	ldr r0, [sp, #0x48]
	ldr r0, [r0, #0x14]
	ldrb r3, [r0, #0xa]
	ldrb r4, [r0, #0xb]
	ldrb r5, [r0, #8]
	ldrb r0, [r0, #9]
	add r3, #8
	sub r4, #8
	str r0, [sp, #0x2c]
	sub r0, #8
	add r5, #8
	str r0, [sp, #0x2c]
	b _0225C014
_0225C00A:
	mov r3, #0
	mvn r3, r3
	add r4, r3, #0
	add r5, r3, #0
	str r3, [sp, #0x2c]
_0225C014:
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x40]
	str r0, [sp, #0x3c]
	str r0, [sp, #0x28]
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x34]
	cmp r0, r3
	beq _0225C04A
	add r1, r0, #0
	ldr r0, [sp, #0x40]
	cmp r1, r0
	beq _0225C032
	cmp r3, r0
	beq _0225C04A
_0225C032:
	mov r1, #0
	ldr r0, [sp, #0x34]
	mvn r1, r1
	cmp r0, r1
	bne _0225C044
	cmp r3, r1
	beq _0225C044
	str r3, [sp, #0x34]
	b _0225C04A
_0225C044:
	mov r0, #2
	str r3, [sp, #0x40]
	str r0, [sp, #0x20]
_0225C04A:
	ldr r0, [sp, #0x30]
	cmp r0, r4
	beq _0225C074
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0225C05C
	cmp r4, r1
	beq _0225C074
_0225C05C:
	mov r1, #0
	ldr r0, [sp, #0x30]
	mvn r1, r1
	cmp r0, r1
	bne _0225C06E
	cmp r4, r1
	beq _0225C06E
	str r4, [sp, #0x30]
	b _0225C074
_0225C06E:
	mov r0, #3
	str r4, [sp, #0x40]
	str r0, [sp, #0x20]
_0225C074:
	mov r1, #0
	ldr r0, [sp, #0x38]
	mvn r1, r1
	cmp r0, r1
	beq _0225C082
	cmp r5, r1
	beq _0225C096
_0225C082:
	mov r1, #0
	ldr r0, [sp, #0x38]
	mvn r1, r1
	cmp r0, r1
	bne _0225C094
	cmp r5, r1
	beq _0225C094
	str r5, [sp, #0x38]
	b _0225C096
_0225C094:
	str r2, [sp, #0x3c]
_0225C096:
	mov r1, #0
	mvn r1, r1
	cmp r2, r1
	beq _0225C0A8
	ldr r0, [sp, #0x2c]
	cmp r0, r1
	bne _0225C0A8
	str r2, [sp, #0x2c]
	b _0225C0C6
_0225C0A8:
	mov r1, #0
	mvn r1, r1
	cmp r2, r1
	bne _0225C0B6
	ldr r0, [sp, #0x2c]
	cmp r0, r1
	bne _0225C0C6
_0225C0B6:
	ldr r0, [sp, #0x2c]
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x20]
	cmp r0, #2
	bne _0225C0C4
	str r2, [sp, #0x24]
	b _0225C0C6
_0225C0C4:
	str r2, [sp, #0x28]
_0225C0C6:
	ldr r0, [sp, #0x18]
	cmp r0, #1
	beq _0225C0CE
	b _0225C236
_0225C0CE:
	ldr r0, [sp, #0x44]
	cmp r0, #0
	bne _0225C17A
	ldr r0, [sp, #0x1c]
	mov r1, #6
	ldrsb r1, [r0, r1]
	mov r0, #0x6a
	lsl r0, r0, #4
	ldrb r0, [r6, r0]
	cmp r1, r0
	bne _0225C0F6
	ldr r0, [sp, #0x1c]
	mov r1, #4
	ldrsb r0, [r0, r1]
	mov r1, #5
	strb r0, [r7, #2]
	ldr r0, [sp, #0x1c]
	ldrsb r0, [r0, r1]
	strb r0, [r7, #1]
	b _0225C12C
_0225C0F6:
	add r0, sp, #0x50
	ldrb r1, [r0, #0xd]
	cmp r1, #1
	bne _0225C106
	mov r0, #0
	strb r0, [r7, #2]
	strb r0, [r7, #1]
	b _0225C12C
_0225C106:
	ldrb r1, [r0, #0xb]
	cmp r1, #1
	bne _0225C116
	mov r0, #1
	strb r0, [r7, #2]
	mov r0, #0
	strb r0, [r7, #1]
	b _0225C12C
_0225C116:
	ldrb r0, [r0, #0xa]
	cmp r0, #1
	bne _0225C126
	mov r0, #0
	strb r0, [r7, #2]
	mov r0, #1
	strb r0, [r7, #1]
	b _0225C12C
_0225C126:
	mov r0, #1
	strb r0, [r7, #2]
	strb r0, [r7, #1]
_0225C12C:
	mov r0, #1
	ldrsb r0, [r7, r0]
	ldr r2, _0225C13C ; =MOD11_0225F690
	b _0225C140
	.align 2, 0
_0225C134: .word 0x0000069E
_0225C138: .word MOD11_0225FAAC
_0225C13C: .word MOD11_0225F690
_0225C140:
	lsl r3, r0, #1
	mov r0, #2
	ldrsb r1, [r7, r0]
	add r0, r2, r3
	ldrb r1, [r1, r0]
	ldr r0, [sp, #0x48]
	lsl r3, r1, #2
	ldr r0, [r0, #0x14]
	ldr r1, [sp, #0x48]
	add r0, r0, r3
	ldrb r0, [r0, #1]
	sub r0, #8
	str r0, [sp]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r4, [r1, #0x14]
	ldr r0, _0225C418 ; =0x000006EC
	add r2, r4, r3
	ldrb r1, [r2, #2]
	ldrb r2, [r2, #3]
	ldrb r3, [r4, r3]
	ldr r0, [r6, r0]
	add r1, #8
	sub r2, #8
	add r3, #8
	bl MOD11_0225D5FC
	b _0225C22E
_0225C17A:
	mov r2, #0
	strb r2, [r7, #2]
	ldr r0, [sp, #0x24]
	sub r1, r2, #1
	strb r2, [r7, #1]
	cmp r0, r1
	bne _0225C18E
	ldr r0, [sp, #0x28]
	cmp r0, r1
	beq _0225C198
_0225C18E:
	mov r1, #0
	ldr r0, [sp, #0x40]
	mvn r1, r1
	cmp r0, r1
	bne _0225C1B2
_0225C198:
	ldr r0, [sp, #0x2c]
	ldr r1, [sp, #0x34]
	str r0, [sp]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, _0225C418 ; =0x000006EC
	ldr r2, [sp, #0x30]
	ldr r0, [r6, r0]
	ldr r3, [sp, #0x38]
	bl MOD11_0225D5FC
	b _0225C210
_0225C1B2:
	ldr r0, [sp, #0x24]
	cmp r0, r1
	beq _0225C1E8
	ldr r0, [sp, #0x28]
	cmp r0, r1
	bne _0225C1E8
	ldr r0, [sp, #0x38]
	ldr r1, [sp, #0x34]
	str r0, [sp]
	ldr r0, [sp, #0x34]
	ldr r2, [sp, #0x38]
	str r0, [sp, #4]
	ldr r0, [sp, #0x24]
	ldr r3, [sp, #0x30]
	str r0, [sp, #8]
	ldr r0, [sp, #0x30]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x2c]
	str r0, [sp, #0x10]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #0x14]
	ldr r0, _0225C418 ; =0x000006EC
	ldr r0, [r6, r0]
	bl MOD11_0225D52C
	b _0225C210
_0225C1E8:
	ldr r0, [sp, #0x38]
	ldr r1, [sp, #0x34]
	str r0, [sp]
	ldr r0, [sp, #0x34]
	ldr r2, [sp, #0x38]
	str r0, [sp, #4]
	ldr r0, [sp, #0x2c]
	ldr r3, [sp, #0x30]
	str r0, [sp, #8]
	ldr r0, [sp, #0x30]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x28]
	str r0, [sp, #0x10]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #0x14]
	ldr r0, _0225C418 ; =0x000006EC
	ldr r0, [r6, r0]
	bl MOD11_0225D52C
_0225C210:
	mov r1, #0
	ldr r0, [sp, #0x40]
	mvn r1, r1
	cmp r0, r1
	beq _0225C22E
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp]
	ldr r0, _0225C418 ; =0x000006EC
	ldr r1, [sp, #0x40]
	ldr r0, [r6, r0]
	ldr r2, [sp, #0x3c]
	ldr r3, [sp, #0x20]
	bl MOD11_0225D620
_0225C22E:
	mov r0, #0
	add sp, #0x60
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_0225C236:
	ldr r0, [sp, #0x44]
	cmp r0, #0
	bne _0225C24A
	ldr r2, [sp, #0x4c]
	add r0, r7, #0
	mov r1, ip
	add r3, sp, #0x50
	bl MOD11_0225C574
	b _0225C256
_0225C24A:
	ldr r2, [sp, #0x4c]
	add r0, r7, #0
	mov r1, ip
	mov r3, #0
	bl MOD11_0225C574
_0225C256:
	cmp r0, #0x20
	bhi _0225C276
	bhs _0225C284
	cmp r0, #2
	bhi _0225C270
	cmp r0, #1
	blo _0225C26E
	bne _0225C268
	b _0225C3BE
_0225C268:
	cmp r0, #2
	bne _0225C26E
	b _0225C40A
_0225C26E:
	b _0225C410
_0225C270:
	cmp r0, #0x10
	beq _0225C284
	b _0225C410
_0225C276:
	cmp r0, #0x40
	bhi _0225C27E
	beq _0225C284
	b _0225C410
_0225C27E:
	cmp r0, #0x80
	beq _0225C284
	b _0225C410
_0225C284:
	ldr r0, [sp, #0x44]
	cmp r0, #0
	bne _0225C2CA
	mov r0, #1
	ldrsb r0, [r7, r0]
	ldr r2, _0225C41C ; =MOD11_0225F690
	lsl r3, r0, #1
	mov r0, #2
	ldrsb r1, [r7, r0]
	add r0, r2, r3
	ldrb r1, [r1, r0]
	ldr r0, [sp, #0x48]
	lsl r3, r1, #2
	ldr r0, [r0, #0x14]
	ldr r1, [sp, #0x48]
	add r0, r0, r3
	ldrb r0, [r0, #1]
	sub r0, #8
	str r0, [sp]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r4, [r1, #0x14]
	ldr r0, _0225C418 ; =0x000006EC
	add r2, r4, r3
	ldrb r1, [r2, #2]
	ldrb r2, [r2, #3]
	ldrb r3, [r4, r3]
	ldr r0, [r6, r0]
	add r1, #8
	sub r2, #8
	add r3, #8
	bl MOD11_0225D5FC
	b _0225C410
_0225C2CA:
	mov r2, #1
	ldrsb r0, [r7, r2]
	cmp r0, #0
	bne _0225C38C
	ldr r0, [sp, #0x28]
	sub r1, r2, #2
	cmp r0, r1
	bne _0225C2E0
	ldr r0, [sp, #0x24]
	cmp r0, r1
	beq _0225C2EA
_0225C2E0:
	mov r1, #0
	ldr r0, [sp, #0x40]
	mvn r1, r1
	cmp r0, r1
	bne _0225C304
_0225C2EA:
	ldr r0, [sp, #0x2c]
	ldr r1, [sp, #0x34]
	str r0, [sp]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, _0225C418 ; =0x000006EC
	ldr r2, [sp, #0x30]
	ldr r0, [r6, r0]
	ldr r3, [sp, #0x38]
	bl MOD11_0225D5FC
	b _0225C362
_0225C304:
	ldr r0, [sp, #0x24]
	cmp r0, r1
	beq _0225C33A
	ldr r0, [sp, #0x28]
	cmp r0, r1
	bne _0225C33A
	ldr r0, [sp, #0x38]
	ldr r1, [sp, #0x34]
	str r0, [sp]
	ldr r0, [sp, #0x34]
	ldr r2, [sp, #0x38]
	str r0, [sp, #4]
	ldr r0, [sp, #0x24]
	ldr r3, [sp, #0x30]
	str r0, [sp, #8]
	ldr r0, [sp, #0x30]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x2c]
	str r0, [sp, #0x10]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #0x14]
	ldr r0, _0225C418 ; =0x000006EC
	ldr r0, [r6, r0]
	bl MOD11_0225D52C
	b _0225C362
_0225C33A:
	ldr r0, [sp, #0x38]
	ldr r1, [sp, #0x34]
	str r0, [sp]
	ldr r0, [sp, #0x34]
	ldr r2, [sp, #0x38]
	str r0, [sp, #4]
	ldr r0, [sp, #0x2c]
	ldr r3, [sp, #0x30]
	str r0, [sp, #8]
	ldr r0, [sp, #0x30]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x28]
	str r0, [sp, #0x10]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #0x14]
	ldr r0, _0225C418 ; =0x000006EC
	ldr r0, [r6, r0]
	bl MOD11_0225D52C
_0225C362:
	mov r1, #0
	ldr r0, [sp, #0x40]
	mvn r1, r1
	cmp r0, r1
	beq _0225C382
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp]
	ldr r0, _0225C418 ; =0x000006EC
	ldr r1, [sp, #0x40]
	ldr r0, [r6, r0]
	ldr r2, [sp, #0x3c]
	ldr r3, [sp, #0x20]
	bl MOD11_0225D620
	b _0225C410
_0225C382:
	ldr r0, _0225C418 ; =0x000006EC
	ldr r0, [r6, r0]
	bl MOD11_0225D664
	b _0225C410
_0225C38C:
	ldr r0, [sp, #0x48]
	ldr r1, [sp, #0x48]
	ldr r0, [r0, #0x14]
	ldrb r0, [r0, #0x11]
	sub r0, #8
	str r0, [sp]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r3, [r1, #0x14]
	ldr r0, _0225C418 ; =0x000006EC
	ldrb r1, [r3, #0x12]
	ldrb r2, [r3, #0x13]
	ldrb r3, [r3, #0x10]
	ldr r0, [r6, r0]
	add r1, #8
	sub r2, #8
	add r3, #8
	bl MOD11_0225D5FC
	ldr r0, _0225C418 ; =0x000006EC
	ldr r0, [r6, r0]
	bl MOD11_0225D664
	b _0225C410
_0225C3BE:
	ldr r0, [sp, #0x44]
	cmp r0, #1
	bne _0225C3E8
	mov r0, #1
	ldrsb r0, [r7, r0]
	cmp r0, #0
	ble _0225C3D2
	add sp, #0x60
	mov r0, #4
	pop {r3, r4, r5, r6, r7, pc}
_0225C3D2:
	add r2, sp, #0x58
	mov r0, #0
	add r2, #2
	b _0225C3E2
_0225C3DA:
	ldrb r1, [r2, r0]
	cmp r1, #1
	beq _0225C414
	add r0, r0, #1
_0225C3E2:
	cmp r0, #4
	blt _0225C3DA
	b _0225C410
_0225C3E8:
	mov r0, #1
	ldrsb r0, [r7, r0]
	ldr r2, _0225C41C ; =MOD11_0225F690
	lsl r3, r0, #1
	mov r0, #2
	ldrsb r1, [r7, r0]
	add r0, r2, r3
	ldrb r0, [r1, r0]
	cmp r0, #4
	beq _0225C414
	add r1, sp, #0x58
	add r1, #2
	ldrb r1, [r1, r0]
	cmp r1, #1
	bne _0225C410
	add sp, #0x60
	pop {r3, r4, r5, r6, r7, pc}
_0225C40A:
	add sp, #0x60
	mov r0, #4
	pop {r3, r4, r5, r6, r7, pc}
_0225C410:
	mov r0, #0
	mvn r0, r0
_0225C414:
	add sp, #0x60
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225C418: .word 0x000006EC
_0225C41C: .word MOD11_0225F690

	thumb_func_start MOD11_0225C420
MOD11_0225C420: ; 0x0225C420
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	cmp r4, #4
	beq _0225C470
	ldr r1, _0225C474 ; =0x0000069E
	ldr r0, [r5]
	ldrb r1, [r5, r1]
	bl MOD11_0223022C
	add r1, r0, #0
	ldr r0, [r5]
	bl MOD11_0222FF7C
	bl MOD11_02253A74
	mov r1, #0x6a
	lsl r1, r1, #4
	ldrb r1, [r5, r1]
	mov r3, #0
	ldr r7, _0225C478 ; =MOD11_0225F690
	strb r1, [r0, #6]
	add r1, r3, #0
	b _0225C46C
_0225C450:
	lsl r5, r3, #1
	add r2, r1, #0
	add r6, r7, r5
	b _0225C466
_0225C458:
	ldrb r5, [r2, r6]
	cmp r4, r5
	bne _0225C464
	strb r2, [r0, #4]
	strb r3, [r0, #5]
	pop {r3, r4, r5, r6, r7, pc}
_0225C464:
	add r2, r2, #1
_0225C466:
	cmp r2, #2
	blt _0225C458
	add r3, r3, #1
_0225C46C:
	cmp r3, #3
	blt _0225C450
_0225C470:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225C474: .word 0x0000069E
_0225C478: .word MOD11_0225F690

	thumb_func_start MOD11_0225C47C
MOD11_0225C47C: ; 0x0225C47C
	push {r4, r5, r6, lr}
	sub sp, #8
	add r6, r0, #0
	mov r0, #0x6f
	lsl r0, r0, #4
	add r3, r0, #0
	sub r3, #0x51
	ldrsb r5, [r6, r3]
	mov r3, #0x30
	ldr r2, _0225C568 ; =MOD11_0225FAAC
	mul r3, r5
	add r4, r6, r0
	add r5, r2, r3
	cmp r1, #1
	bne _0225C4DA
	mov r1, #1
	ldrsb r2, [r4, r1]
	mov r3, #2
	ldr r1, _0225C56C ; =MOD11_0225F684
	ldrsb r3, [r4, r3]
	add r1, r1, r2
	sub r0, r0, #4
	ldrb r2, [r3, r1]
	ldr r1, [r5, #0x14]
	lsl r3, r2, #2
	add r1, r1, r3
	ldrb r1, [r1, #1]
	sub r1, #8
	str r1, [sp]
	mov r1, #0x11
	lsl r1, r1, #0x10
	str r1, [sp, #4]
	ldr r4, [r5, #0x14]
	ldr r0, [r6, r0]
	add r2, r4, r3
	ldrb r1, [r2, #2]
	ldrb r2, [r2, #3]
	ldrb r3, [r4, r3]
	add r1, #8
	sub r2, #8
	add r3, #8
	bl MOD11_0225D5FC
	mov r0, #0
	add sp, #8
	mvn r0, r0
	pop {r4, r5, r6, pc}
_0225C4DA:
	ldr r3, _0225C56C ; =MOD11_0225F684
	add r0, r4, #0
	mov r1, #1
	mov r2, #2
	bl MOD11_0225C574
	cmp r0, #0x20
	bhi _0225C502
	bhs _0225C50E
	cmp r0, #2
	bhi _0225C4FC
	cmp r0, #1
	blo _0225C560
	beq _0225C548
	cmp r0, #2
	beq _0225C55A
	b _0225C560
_0225C4FC:
	cmp r0, #0x10
	beq _0225C50E
	b _0225C560
_0225C502:
	cmp r0, #0x40
	bhi _0225C50A
	beq _0225C50E
	b _0225C560
_0225C50A:
	cmp r0, #0x80
	bne _0225C560
_0225C50E:
	mov r0, #1
	ldrsb r3, [r4, r0]
	mov r0, #2
	ldr r2, _0225C56C ; =MOD11_0225F684
	ldrsb r1, [r4, r0]
	add r0, r2, r3
	ldrb r1, [r1, r0]
	ldr r0, [r5, #0x14]
	lsl r3, r1, #2
	add r0, r0, r3
	ldrb r0, [r0, #1]
	sub r0, #8
	str r0, [sp]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r4, [r5, #0x14]
	ldr r0, _0225C570 ; =0x000006EC
	add r2, r4, r3
	ldrb r1, [r2, #2]
	ldrb r2, [r2, #3]
	ldrb r3, [r4, r3]
	ldr r0, [r6, r0]
	add r1, #8
	sub r2, #8
	add r3, #8
	bl MOD11_0225D5FC
	b _0225C560
_0225C548:
	mov r0, #1
	ldrsb r3, [r4, r0]
	mov r0, #2
	ldr r2, _0225C56C ; =MOD11_0225F684
	ldrsb r1, [r4, r0]
	add r0, r2, r3
	add sp, #8
	ldrb r0, [r1, r0]
	pop {r4, r5, r6, pc}
_0225C55A:
	add sp, #8
	mov r0, #1
	pop {r4, r5, r6, pc}
_0225C560:
	mov r0, #0
	mvn r0, r0
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_0225C568: .word MOD11_0225FAAC
_0225C56C: .word MOD11_0225F684
_0225C570: .word 0x000006EC

	thumb_func_start MOD11_0225C574
MOD11_0225C574: ; 0x0225C574
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	mov r1, #2
	ldrsb r1, [r0, r1]
	add r6, r2, #0
	add r2, r3, #0
	cmp r1, r4
	blt _0225C588
	sub r1, r4, #1
	strb r1, [r0, #2]
_0225C588:
	mov r1, #1
	ldrsb r1, [r0, r1]
	cmp r1, r6
	blt _0225C594
	sub r1, r6, #1
	strb r1, [r0, #1]
_0225C594:
	mov r7, #2
	ldrsb r1, [r0, r7]
	mov r5, #1
	mov r3, #0x40
	str r1, [sp]
	ldrsb r1, [r0, r5]
	mov ip, r1
	ldr r1, _0225C764 ; =gMain
	ldr r1, [r1, #0x48]
	tst r3, r1
	beq _0225C5FA
	mov r1, ip
	sub r1, r1, #1
	strb r1, [r0, #1]
	ldrsb r1, [r0, r5]
	cmp r1, #0
	bge _0225C5BA
	mov r1, #0
	strb r1, [r0, #1]
_0225C5BA:
	cmp r2, #0
	beq _0225C5F6
	mov r3, #1
	mov r1, #2
	ldrsb r3, [r0, r3]
	ldrsb r1, [r0, r1]
	mul r3, r4
	add r1, r1, r3
	ldrb r1, [r2, r1]
	cmp r1, #0xff
	bne _0225C5F6
	add r1, r0, #1
	mov r7, #0
	mov r6, #1
_0225C5D6:
	ldrsb r3, [r1, r7]
	sub r3, r3, #1
	strb r3, [r1]
	ldrsb r3, [r0, r6]
	cmp r3, #0
	bge _0225C5E8
	mov r1, ip
	strb r1, [r0, #1]
	b _0225C5F6
_0225C5E8:
	mov r5, #2
	ldrsb r5, [r0, r5]
	mul r3, r4
	add r5, r2, r5
	ldrb r3, [r3, r5]
	cmp r3, #0xff
	beq _0225C5D6
_0225C5F6:
	mov r5, #0x40
	b _0225C70E
_0225C5FA:
	mov r3, #0x80
	tst r3, r1
	beq _0225C650
	mov r1, ip
	add r1, r1, #1
	strb r1, [r0, #1]
	ldrsb r1, [r0, r5]
	cmp r1, r6
	blt _0225C610
	sub r1, r6, #1
	strb r1, [r0, #1]
_0225C610:
	cmp r2, #0
	beq _0225C64C
	mov r3, #1
	mov r1, #2
	ldrsb r3, [r0, r3]
	ldrsb r1, [r0, r1]
	mul r3, r4
	add r1, r1, r3
	ldrb r1, [r2, r1]
	cmp r1, #0xff
	bne _0225C64C
	add r1, r0, #1
	mov r7, #1
_0225C62A:
	mov r3, #0
	ldrsb r3, [r1, r3]
	add r3, r3, #1
	strb r3, [r1]
	ldrsb r3, [r0, r7]
	cmp r3, r6
	blt _0225C63E
	mov r1, ip
	strb r1, [r0, #1]
	b _0225C64C
_0225C63E:
	mov r5, #2
	ldrsb r5, [r0, r5]
	mul r3, r4
	add r5, r2, r5
	ldrb r3, [r3, r5]
	cmp r3, #0xff
	beq _0225C62A
_0225C64C:
	mov r5, #0x80
	b _0225C70E
_0225C650:
	mov r3, #0x20
	tst r3, r1
	beq _0225C6A6
	ldr r1, [sp]
	sub r1, r1, #1
	strb r1, [r0, #2]
	ldrsb r1, [r0, r7]
	cmp r1, #0
	bge _0225C666
	mov r1, #0
	strb r1, [r0, #2]
_0225C666:
	cmp r2, #0
	beq _0225C6A2
	mov r3, #1
	mov r1, #2
	ldrsb r3, [r0, r3]
	ldrsb r1, [r0, r1]
	mul r3, r4
	add r1, r1, r3
	ldrb r1, [r2, r1]
	cmp r1, #0xff
	bne _0225C6A2
	add r5, r0, #2
	mov r7, #0
	mov r6, #2
_0225C682:
	ldrsb r1, [r5, r7]
	sub r1, r1, #1
	strb r1, [r5]
	ldrsb r3, [r0, r6]
	cmp r3, #0
	bge _0225C694
	ldr r1, [sp]
	strb r1, [r0, #2]
	b _0225C6A2
_0225C694:
	mov r1, #1
	ldrsb r1, [r0, r1]
	add r3, r2, r3
	mul r1, r4
	ldrb r1, [r1, r3]
	cmp r1, #0xff
	beq _0225C682
_0225C6A2:
	mov r5, #0x20
	b _0225C70E
_0225C6A6:
	mov r3, #0x10
	tst r3, r1
	beq _0225C6FC
	ldr r1, [sp]
	add r1, r1, #1
	strb r1, [r0, #2]
	ldrsb r1, [r0, r7]
	cmp r1, r4
	blt _0225C6BC
	sub r1, r4, #1
	strb r1, [r0, #2]
_0225C6BC:
	cmp r2, #0
	beq _0225C6F8
	mov r3, #1
	mov r1, #2
	ldrsb r3, [r0, r3]
	ldrsb r1, [r0, r1]
	mul r3, r4
	add r1, r1, r3
	ldrb r1, [r2, r1]
	cmp r1, #0xff
	bne _0225C6F8
	add r5, r0, #2
	mov r7, #0
	mov r6, #2
_0225C6D8:
	ldrsb r1, [r5, r7]
	add r1, r1, #1
	strb r1, [r5]
	ldrsb r3, [r0, r6]
	cmp r3, r4
	blt _0225C6EA
	ldr r1, [sp]
	strb r1, [r0, #2]
	b _0225C6F8
_0225C6EA:
	mov r1, #1
	ldrsb r1, [r0, r1]
	add r3, r2, r3
	mul r1, r4
	ldrb r1, [r1, r3]
	cmp r1, #0xff
	beq _0225C6D8
_0225C6F8:
	mov r5, #0x10
	b _0225C70E
_0225C6FC:
	add r3, r1, #0
	tst r3, r5
	bne _0225C70E
	tst r1, r7
	beq _0225C70A
	add r5, r7, #0
	b _0225C70E
_0225C70A:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0225C70E:
	cmp r2, #0
	beq _0225C738
	mov r1, ip
	add r3, r4, #0
	mul r3, r1
	ldr r1, [sp]
	add r1, r1, r3
	mov r3, #2
	ldrsb r6, [r0, r3]
	mov r3, #1
	ldrsb r3, [r0, r3]
	ldrb r1, [r2, r1]
	mul r3, r4
	add r3, r6, r3
	ldrb r2, [r2, r3]
	cmp r1, r2
	bne _0225C738
	ldr r1, [sp]
	strb r1, [r0, #2]
	mov r1, ip
	strb r1, [r0, #1]
_0225C738:
	mov r1, #2
	ldrsb r2, [r0, r1]
	ldr r1, [sp]
	cmp r2, r1
	bne _0225C74C
	mov r1, #1
	ldrsb r1, [r0, r1]
	mov r0, ip
	cmp r1, r0
	beq _0225C754
_0225C74C:
	ldr r0, _0225C768 ; =0x000005DC
	bl PlaySE
	b _0225C75E
_0225C754:
	mov r0, #0xf0
	tst r0, r5
	beq _0225C75E
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0225C75E:
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225C764: .word gMain
_0225C768: .word 0x000005DC

	thumb_func_start MOD11_0225C76C
MOD11_0225C76C: ; 0x0225C76C
	ldr r1, _0225C774 ; =0x000006F4
	ldrb r0, [r0, r1]
	bx lr
	nop
_0225C774: .word 0x000006F4

	thumb_func_start MOD11_0225C778
MOD11_0225C778: ; 0x0225C778
	ldr r2, _0225C780 ; =0x000006F4
	strb r1, [r0, r2]
	bx lr
	nop
_0225C780: .word 0x000006F4

	thumb_func_start MOD11_0225C784
MOD11_0225C784: ; 0x0225C784
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl MOD11_02230078
	ldr r0, [r4]
	bl MOD11_02230080
	ldr r0, [r4]
	bl MOD11_022300CC
	ldr r0, [r4]
	bl MOD11_02231268
	cmp r0, #0
	bne _0225C7C0
	ldr r0, _0225C7E4 ; =0x000006FC
	ldrb r0, [r4, r0]
	cmp r0, #2
	blo _0225C7B0
	bl GF_AssertFail
_0225C7B0:
	ldr r1, _0225C7E4 ; =0x000006FC
	add r0, r4, #0
	ldrb r1, [r4, r1]
	lsl r2, r1, #2
	ldr r1, _0225C7E8 ; =MOD11_0225F6B8
	ldr r1, [r1, r2]
	blx r1
	b _0225C7C6
_0225C7C0:
	add r0, r4, #0
	bl MOD11_0225C8A0
_0225C7C6:
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0225C7E2
	ldr r1, _0225C7EC ; =0x000006FD
	mov r3, #0
	strb r3, [r4, r1]
	add r2, r1, #1
	strb r3, [r4, r2]
	sub r2, r1, #1
	ldrb r2, [r4, r2]
	sub r1, r1, #1
	add r2, r2, #1
	strb r2, [r4, r1]
_0225C7E2:
	pop {r4, pc}
	.align 2, 0
_0225C7E4: .word 0x000006FC
_0225C7E8: .word MOD11_0225F6B8
_0225C7EC: .word 0x000006FD

	thumb_func_start MOD11_0225C7F0
MOD11_0225C7F0: ; 0x0225C7F0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0225C840 ; =0x000006FD
	ldrb r1, [r4, r0]
	cmp r1, #0
	bne _0225C820
	sub r0, r0, #5
	mov r3, #0x11
	ldr r0, [r4, r0]
	mov r1, #0x80
	mov r2, #0x3c
	lsl r3, r3, #0x10
	bl MOD11_0225D7D0
	ldr r0, _0225C844 ; =0x000006F8
	mov r1, #0x3c
	ldr r0, [r4, r0]
	bl MOD11_0225D820
	ldr r0, _0225C840 ; =0x000006FD
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0225C838
_0225C820:
	sub r0, r0, #5
	ldr r0, [r4, r0]
	bl MOD11_0225D824
	cmp r0, #1
	bne _0225C838
	ldr r0, _0225C840 ; =0x000006FD
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	mov r0, #0
	pop {r4, pc}
_0225C838:
	mov r0, #0
	mvn r0, r0
	pop {r4, pc}
	nop
_0225C840: .word 0x000006FD
_0225C844: .word 0x000006F8

	thumb_func_start MOD11_0225C848
MOD11_0225C848: ; 0x0225C848
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0225C898 ; =0x000006FD
	ldrb r1, [r4, r0]
	cmp r1, #0
	bne _0225C878
	sub r0, r0, #5
	mov r3, #0x11
	ldr r0, [r4, r0]
	mov r1, #0x40
	mov r2, #0x16
	lsl r3, r3, #0x10
	bl MOD11_0225D7D0
	ldr r0, _0225C89C ; =0x000006F8
	mov r1, #0x3c
	ldr r0, [r4, r0]
	bl MOD11_0225D820
	ldr r0, _0225C898 ; =0x000006FD
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0225C890
_0225C878:
	sub r0, r0, #5
	ldr r0, [r4, r0]
	bl MOD11_0225D824
	cmp r0, #1
	bne _0225C890
	ldr r0, _0225C898 ; =0x000006FD
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	mov r0, #1
	pop {r4, pc}
_0225C890:
	mov r0, #0
	mvn r0, r0
	pop {r4, pc}
	nop
_0225C898: .word 0x000006FD
_0225C89C: .word 0x000006F8

	thumb_func_start MOD11_0225C8A0
MOD11_0225C8A0: ; 0x0225C8A0
	push {r4, lr}
	ldr r1, _0225C914 ; =0x000006FD
	add r4, r0, #0
	ldrb r0, [r4, r1]
	cmp r0, #0
	beq _0225C8B2
	cmp r0, #1
	beq _0225C8D0
	b _0225C8F4
_0225C8B2:
	add r0, r1, #1
	ldrb r0, [r4, r0]
	add r2, r0, #1
	add r0, r1, #1
	strb r2, [r4, r0]
	ldrb r0, [r4, r0]
	cmp r0, #0x3c
	bls _0225C90C
	mov r2, #0
	add r0, r1, #1
	strb r2, [r4, r0]
	ldrb r0, [r4, r1]
	add r0, r0, #1
	strb r0, [r4, r1]
	b _0225C90C
_0225C8D0:
	sub r0, r1, #5
	mov r3, #0x11
	ldr r0, [r4, r0]
	mov r1, #0x28
	mov r2, #0x92
	lsl r3, r3, #0x10
	bl MOD11_0225D7D0
	ldr r0, _0225C918 ; =0x000006F8
	mov r1, #0x3c
	ldr r0, [r4, r0]
	bl MOD11_0225D820
	ldr r0, _0225C914 ; =0x000006FD
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _0225C90C
_0225C8F4:
	sub r0, r1, #5
	ldr r0, [r4, r0]
	bl MOD11_0225D824
	cmp r0, #1
	bne _0225C90C
	ldr r0, _0225C914 ; =0x000006FD
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	mov r0, #1
	pop {r4, pc}
_0225C90C:
	mov r0, #0
	mvn r0, r0
	pop {r4, pc}
	nop
_0225C914: .word 0x000006FD
_0225C918: .word 0x000006F8

	.section .rodata

	.global MOD11_0225F684
MOD11_0225F684: ; 0x0225F684
	.byte 0x00, 0x01, 0x00, 0x00

	.global MOD11_0225F688
MOD11_0225F688: ; 0x0225F688
	.byte 0x00, 0x01, 0x06, 0x0C, 0x0D, 0x05, 0x00, 0x00

	.global MOD11_0225F690
MOD11_0225F690: ; 0x0225F690
	.byte 0x03, 0x01, 0x00, 0x02, 0x04, 0x04, 0x00, 0x00

	.global MOD11_0225F698
MOD11_0225F698: ; 0x0225F698
	.byte 0x00, 0x00, 0x00, 0x01, 0x03, 0x02, 0x00, 0x00

	.global MOD11_0225F6A0
MOD11_0225F6A0: ; 0x0225F6A0
	.byte 0x01, 0x02, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00

	.global MOD11_0225F6A8
MOD11_0225F6A8: ; 0x0225F6A8
	.byte 0x2F, 0x02, 0x2C, 0x02, 0x29, 0x02, 0x26, 0x02

	.global MOD11_0225F6B0
MOD11_0225F6B0: ; 0x0225F6B0
	.byte 0x01, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00

	.global MOD11_0225F6B8
MOD11_0225F6B8: ; 0x0225F6B8
	.word MOD11_0225C7F0, MOD11_0225C848

	.global MOD11_0225F6C0
MOD11_0225F6C0: ; 0x0225F6C0
	.byte 0x38, 0x02, 0x35, 0x02, 0x32, 0x02, 0x3B, 0x02

	.global MOD11_0225F6C8
MOD11_0225F6C8: ; 0x0225F6C8
	.byte 0x0D, 0x14, 0x00, 0x1F

	.global MOD11_0225F6CC
MOD11_0225F6CC: ; 0x0225F6CC
	.byte 0x04, 0x0B, 0x00, 0x1F

	.global MOD11_0225F6D0
MOD11_0225F6D0: ; 0x0225F6D0
	.byte 0x18, 0x90, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00

	.global MOD11_0225F6D8
MOD11_0225F6D8: ; 0x0225F6D8
	.byte 0x28, 0x60, 0x08, 0xF8, 0x70, 0xA8, 0x08, 0xF8, 0xFF, 0x00, 0x00, 0x00

	.global MOD11_0225F6E4
MOD11_0225F6E4: ; 0x0225F6E4
	.byte 0x28, 0x80, 0x18, 0xE8
	.byte 0x98, 0xC0, 0x58, 0xA8, 0xFF, 0x00, 0x00, 0x00

	.global MOD11_0225F6F0
MOD11_0225F6F0: ; 0x0225F6F0
	.byte 0x00, 0x00, 0x05, 0x00, 0x0A, 0x00

	.global MOD11_0225F6F6
MOD11_0225F6F6: ; 0x0225F6F6
	.byte 0x00, 0x00
	.byte 0xC0, 0x00, 0x80, 0x01

	.global MOD11_0225F6FC
MOD11_0225F6FC: ; 0x0225F6FC
	.byte 0x25, 0x00, 0x1F, 0x00, 0x23, 0x00, 0x20, 0x00, 0x21, 0x00, 0x24, 0x00
	.byte 0x22, 0x00, 0x00, 0x00

	.global MOD11_0225F70C
MOD11_0225F70C: ; 0x0225F70C
	.byte 0x04, 0x0F, 0x02, 0x1D, 0x11, 0x17, 0x00, 0x09, 0x11, 0x17, 0x16, 0x1F
	.byte 0x12, 0x17, 0x0B, 0x14

	.global MOD11_0225F71C
MOD11_0225F71C: ; 0x0225F71C
	.byte 0x0B, 0x11, 0x00, 0x0E, 0x01, 0x09, 0x11, 0x1F, 0x0B, 0x11, 0x11, 0x1F
	.byte 0x01, 0x09, 0x00, 0x0E

	.global MOD11_0225F72C
MOD11_0225F72C: ; 0x0225F72C
	.byte 0x20, 0x00, 0x3E, 0x00, 0xA0, 0x00, 0x3E, 0x00, 0x20, 0x00, 0x7E, 0x00
	.byte 0xA0, 0x00, 0x7E, 0x00

	.global MOD11_0225F73C
MOD11_0225F73C: ; 0x0225F73C
	.byte 0x4C, 0x00, 0x3E, 0x00, 0xCC, 0x00, 0x3E, 0x00, 0x4C, 0x00, 0x7E, 0x00
	.byte 0xCC, 0x00, 0x7E, 0x00

	.global MOD11_0225F74C
MOD11_0225F74C: ; 0x0225F74C
	.byte 0x03, 0x09, 0x00, 0x0F, 0x03, 0x09, 0x10, 0x1F, 0x0B, 0x11, 0x00, 0x0F
	.byte 0x0B, 0x11, 0x10, 0x1F

	.global MOD11_0225F75C
MOD11_0225F75C: ; 0x0225F75C
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00

	.global MOD11_0225F76C
MOD11_0225F76C: ; 0x0225F76C
	.byte 0x3C, 0x00, 0x74, 0x00, 0xC4, 0x00, 0x38, 0x00, 0xC4, 0x00, 0x74, 0x00
	.byte 0x3C, 0x00, 0x38, 0x00

	.global MOD11_0225F77C
MOD11_0225F77C: ; 0x0225F77C
	.byte 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD11_0225F78C
MOD11_0225F78C: ; 0x0225F78C
	.byte 0x3B, 0x00, 0x3E, 0x00, 0xBB, 0x00, 0x3E, 0x00, 0x3B, 0x00, 0x7E, 0x00
	.byte 0xBB, 0x00, 0x7E, 0x00

	.global MOD11_0225F79C
MOD11_0225F79C: ; 0x0225F79C
	.byte 0x80, 0x00, 0x4C, 0x00, 0x28, 0x00, 0xA4, 0x00, 0xD8, 0x00, 0xA4, 0x00
	.byte 0x80, 0x00, 0xA8, 0x00

	.global MOD11_0225F7AC
MOD11_0225F7AC: ; 0x0225F7AC
	.byte 0x02, 0x09, 0x00, 0x0F, 0x02, 0x09, 0x10, 0x1F, 0x0A, 0x11, 0x00, 0x0F
	.byte 0x0A, 0x11, 0x10, 0x1F

	.global MOD11_0225F7BC
MOD11_0225F7BC: ; 0x0225F7BC
	.byte 0x12, 0x17, 0x01, 0x1E

	.global MOD11_0225F7C0
MOD11_0225F7C0: ; 0x0225F7C0
	.byte 0x01, 0x00, 0x00, 0x00

	.global MOD11_0225F7C4
MOD11_0225F7C4: ; 0x0225F7C4
	.byte 0x02, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00

	.global MOD11_0225F7D4
MOD11_0225F7D4: ; 0x0225F7D4
	.byte 0x3C, 0x00, 0x74, 0x00
	.byte 0xC4, 0x00, 0x20, 0x00, 0xC4, 0x00, 0x74, 0x00, 0x3C, 0x00, 0x20, 0x00, 0x80, 0x00, 0xB2, 0x00

	.global MOD11_0225F7E8
MOD11_0225F7E8: ; 0x0225F7E8
	.byte 0x18, 0x90, 0x00, 0xFF, 0x90, 0xC0, 0x00, 0x50, 0x90, 0xC0, 0xB0, 0xFF, 0x98, 0xC0, 0x58, 0xA8
	.byte 0xFF, 0x00, 0x00, 0x00

	.global MOD11_0225F7FC
MOD11_0225F7FC: ; 0x0225F7FC
	.byte 0x0A, 0x11, 0x00, 0x0E, 0x00, 0x09, 0x11, 0x1F, 0x0A, 0x11, 0x11, 0x1F
	.byte 0x00, 0x09, 0x00, 0x0E

	.global MOD11_0225F80C
MOD11_0225F80C: ; 0x0225F80C
	.byte 0x12, 0x17, 0x01, 0x1E

	.global MOD11_0225F810
MOD11_0225F810: ; 0x0225F810
	.byte 0xFF, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00

	.global MOD11_0225F824
MOD11_0225F824: ; 0x0225F824
	.byte 0x58, 0x90, 0x00, 0x78
	.byte 0x08, 0x50, 0x88, 0xFF, 0x58, 0x90, 0x88, 0xFF, 0x08, 0x50, 0x00, 0x78, 0x98, 0xC0, 0x08, 0xF8
	.byte 0xFF, 0x00, 0x00, 0x00

	.global MOD11_0225F83C
MOD11_0225F83C: ; 0x0225F83C
	.byte 0x98, 0xC0, 0x08, 0xF8, 0x18, 0x50, 0x00, 0x80, 0x18, 0x50, 0x80, 0xFF
	.byte 0x58, 0x90, 0x00, 0x80, 0x58, 0x90, 0x80, 0xFF, 0xFF, 0x00, 0x00, 0x00

	.global MOD11_0225F854
MOD11_0225F854: ; 0x0225F854
	.byte 0x00, 0x00, 0xC0, 0x00
	.byte 0x80, 0x01, 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01, 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01, 0x00, 0x00
	.byte 0xC0, 0x00, 0x80, 0x01

	.global MOD11_0225F86C
MOD11_0225F86C: ; 0x0225F86C
	.byte 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01, 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01
	.byte 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01, 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01

	.global MOD11_0225F884
MOD11_0225F884: ; 0x0225F884
	.byte 0x00, 0x00, 0xC0, 0x00
	.byte 0x80, 0x01, 0x00, 0x00

	.global MOD11_0225F88C
MOD11_0225F88C: ; 0x0225F88C
	.byte 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01, 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01
	.byte 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01, 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01

	.global MOD11_0225F8A4
MOD11_0225F8A4: ; 0x0225F8A4
	.byte 0x00, 0x00, 0xC0, 0x00
	.byte 0x80, 0x01, 0x00, 0x00

	.global MOD11_0225F8AC
MOD11_0225F8AC: ; 0x0225F8AC
	.byte 0x0C, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x33, 0x4E, 0x00, 0x00, 0x33, 0x4E, 0x00, 0x00
	.byte 0x2B, 0x4E, 0x00, 0x00, 0x2B, 0x4E, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD11_0225F8E0
MOD11_0225F8E0: ; 0x0225F8E0
	.byte 0xF6, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x34, 0x4E, 0x00, 0x00
	.byte 0x33, 0x4E, 0x00, 0x00, 0x2C, 0x4E, 0x00, 0x00, 0x2C, 0x4E, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD11_0225F914
MOD11_0225F914: ; 0x0225F914
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x35, 0x4E, 0x00, 0x00, 0x30, 0x4E, 0x00, 0x00, 0x2D, 0x4E, 0x00, 0x00, 0x2D, 0x4E, 0x00, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD11_0225F948
MOD11_0225F948: ; 0x0225F948
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x41, 0x4E, 0x00, 0x00, 0x32, 0x4E, 0x00, 0x00, 0x31, 0x4E, 0x00, 0x00
	.byte 0x31, 0x4E, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD11_0225F97C
MOD11_0225F97C: ; 0x0225F97C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD11_0225F9EC
MOD11_0225F9EC: ; 0x0225F9EC
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00

	.global MOD11_0225FAAC
MOD11_0225FAAC: ; 0x0225FAAC
	.byte 0x11, 0x00, 0xC3, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF
	.byte 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.short 0x0011, 0x00C3, 0x0001, 0x0002, 0x0000, 0xFFFF, 0x0002, 0x0003, 0x0003, 0x0000
	.word MOD11_0225F7E8, MOD11_0225F75C, MOD11_0225FE10, MOD11_0225B928, MOD11_0225BB04, MOD11_02259270, MOD11_02259E64

	.short 0x0011, 0x00C3, 0x0001, 0x0002, 0x0000, 0xFFFF, 0x0002, 0x0003, 0x0003, 0x0000
	.word MOD11_0225F7E8, MOD11_0225F75C, MOD11_0225FE10, MOD11_0225B928, MOD11_0225BB04, MOD11_02259270, MOD11_02259E64

	.short 0x0011, 0x00C3, 0x0001, 0x0002, 0x0000, 0xFFFF, 0x0002, 0x0003, 0x0003, 0x0000
	.word MOD11_0225F7E8, MOD11_0225F75C, MOD11_0225FE10, MOD11_0225B928, MOD11_0225BB04, MOD11_02259284, MOD11_02259E64

	.short 0x0011, 0x00C3, 0x0001, 0x0002, 0x0000, 0xFFFF, 0x0002, 0x0003, 0x0003, 0x0000
	.word MOD11_0225F7E8, MOD11_0225F75C, MOD11_0225FE10, MOD11_0225B928, MOD11_0225BB04, MOD11_02259284, MOD11_02259E64

	.short 0x0011, 0x00C3, 0x0001, 0x0002, 0x0000, 0xFFFF, 0x0002, 0x0003, 0x0003, 0x0000
	.word MOD11_0225F6D0, MOD11_0225F75C, MOD11_0225FE10, MOD11_0225B928, MOD11_0225BB04, MOD11_022594C8, MOD11_02259E64

	.short 0x0011, 0x00C3, 0x0001, 0x0002, 0x0000, 0xFFFF, 0x0002, 0x0003, 0x0003, 0x0000
	.word MOD11_0225F6D0, MOD11_0225F75C, MOD11_0225FE10, MOD11_0225B928, MOD11_0225BB04, MOD11_022594DC, MOD11_02259E64

	.short 0x0011, 0x00C3, 0x0001, 0xFFFF, 0x0000, 0xFFFF, 0x0002, 0x0001, 0x0003, 0x0000
	.word MOD11_0225F7E8, MOD11_0225F75C, MOD11_0225FE10, MOD11_0225B928, MOD11_0225BB04, MOD11_02259270, MOD11_02259E64

	.short 0x0011, 0x00C3, 0x0001, 0xFFFF, 0x0000, 0xFFFF, 0x0002, 0x0001, 0x0003, 0x0000
	.word MOD11_0225F7E8, MOD11_0225F75C, MOD11_0225FE10, MOD11_0225B928, MOD11_0225BB04, MOD11_02259284, MOD11_02259E64

	.short 0x0011, 0x00C3, 0x0001, 0xFFFF, 0x0000, 0xFFFF, 0x0002, 0x0003, 0x0003, 0x0000
	.word MOD11_0225F6E4, MOD11_0225F77C, MOD11_0225FE14, MOD11_0225BB68, 0x00000000, MOD11_02259540, MOD11_02259E64

	.short 0x0011, 0x00C3, 0x0001, 0xFFFF, 0x0000, 0xFFFF, 0x0002, 0x0003, 0x0003, 0x0000
	.word MOD11_0225F6E4, MOD11_0225F77C, MOD11_0225FE14, MOD11_0225BB68, 0x00000000, MOD11_02259554, MOD11_02259E64

	.short 0x0011, 0x00C3, 0x0003, 0xFFFF, 0x0000, 0xFFFF, 0x0002, 0x0001, 0x0003, 0x0000
	.word MOD11_0225F83C, MOD11_0225F810, MOD11_0225FE18, MOD11_0225BC60, MOD11_0225BDE0, MOD11_022595C8, MOD11_02259F3C

	.short 0x0011, 0x00C3, 0x0004, 0x0005, 0x0000, 0xFFFF, 0x0002, 0x0001, 0x0003, 0x0000
	.word MOD11_0225F824, MOD11_0225F7C0, MOD11_0225FE20, MOD11_0225BE30, MOD11_0225C420, MOD11_02259C74, MOD11_0225A060

	.short 0x0011, 0x00C3, 0x0006, 0xFFFF, 0x0000, 0xFFFF, 0x0002, 0x0001, 0x0003, 0x0000
	.word MOD11_0225F6D8, MOD11_0225F6B0, MOD11_0225FE0C, MOD11_0225C47C, 0x00000000, MOD11_02259898, MOD11_02259FE4

	.short 0x0011, 0x00C3, 0x0006, 0xFFFF, 0x0000, 0xFFFF, 0x0002, 0x0001, 0x0003, 0x0000
	.word MOD11_0225F6D8, MOD11_0225F6B0, MOD11_0225FE0C, MOD11_0225C47C, 0x00000000, MOD11_02259930, MOD11_02259FE4

	.short 0x0011, 0x00C3, 0x0006, 0xFFFF, 0x0000, 0xFFFF, 0x0002, 0x0001, 0x0003, 0x0000
	.word MOD11_0225F6D8, MOD11_0225F6B0, MOD11_0225FE0C, MOD11_0225C47C, 0x00000000, MOD11_022599CC, MOD11_02259FE4

	.short 0x0011, 0x00C3, 0x0006, 0xFFFF, 0x0000, 0xFFFF, 0x0002, 0x0001, 0x0003, 0x0000
	.word MOD11_0225F6D8, MOD11_0225F6B0, MOD11_0225FE0C, MOD11_0225C47C, 0x00000000, MOD11_02259AB0, MOD11_02259FE4

	.short 0x0011, 0x00C3, 0x0006, 0xFFFF, 0x0000, 0xFFFF, 0x0002, 0x0001, 0x0003, 0x0000
	.word MOD11_0225F6D8, MOD11_0225F6B0, MOD11_0225FE0C, MOD11_0225C47C, 0x00000000, MOD11_02259B94, MOD11_02259FE4

	.global MOD11_0225FE0C
MOD11_0225FE0C: ; 0x0225FE0C
	.byte 0x01, 0x04, 0x00, 0x00

	.global MOD11_0225FE10
MOD11_0225FE10: ; 0x0225FE10
	.byte 0x01, 0x02, 0x03, 0x04

	.global MOD11_0225FE14
MOD11_0225FE14: ; 0x0225FE14
	.byte 0x01, 0x04, 0x00, 0x00

	.global MOD11_0225FE18
MOD11_0225FE18: ; 0x0225FE18
	.byte 0x04, 0x08, 0x09, 0x0A, 0x0B, 0x00, 0x00, 0x00

	.global MOD11_0225FE20
MOD11_0225FE20: ; 0x0225FE20
	.byte 0x06, 0x0C, 0x0D, 0x05, 0x04, 0x00, 0x00, 0x00
