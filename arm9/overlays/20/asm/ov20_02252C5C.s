	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 2, 0

	thumb_func_start ov20_02252C5C
ov20_02252C5C: ; 0x02252C5C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	mov r1, #0xea
	add r5, r0, #0
	mov r0, #7
	lsl r1, r1, #2
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	str r0, [r5]
	add r4, r0, #0
	beq _02252D0A
	mov r0, #0x15
	lsl r0, r0, #4
	str r7, [r4, r0]
	ldr r0, [r4, r0]
	bl NNS_G2dResetOamManagerBuffer
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #7
	bl ov20_02253BA4
	mov r1, #0x55
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _02252CA6
	ldr r0, [r5]
	bl FreeToHeap
	mov r0, #0
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_02252CA6:
	mov r0, #7
	str r6, [r4]
	bl BgConfig_Alloc
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r4, r1]
	ldr r0, [sp]
	add r1, r1, #4
	str r0, [r4, r1]
	add r0, r4, #0
	bl ov20_02252D44
	mov r1, #0x57
	lsl r1, r1, #2
	add r0, r4, r1
	sub r1, #8
	ldr r1, [r4, r1]
	bl ov20_02253428
	ldr r0, [r5]
	mov r1, #8
	add r0, r0, #4
	bl ov20_022536F4
	ldr r0, [r5]
	mov r1, #0x88
	add r0, #0x2c
	bl ov20_02252E5C
	ldr r0, [r5]
	mov r1, #0x8c
	add r0, #0x84
	bl ov20_02252E5C
	ldr r0, [r5]
	mov r1, #0x90
	add r0, #0xdc
	bl ov20_02252E5C
	ldr r0, _02252D10 ; =ov20_02252D14
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA98
	mov r1, #0x56
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02252D0A:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02252D10: .word ov20_02252D14
	thumb_func_end ov20_02252C5C

	thumb_func_start ov20_02252D14
ov20_02252D14: ; 0x02252D14
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r3, _02252D20 ; =ov20_02253C78
	ldr r0, [r1, r0]
	bx r3
	nop
_02252D20: .word ov20_02253C78
	thumb_func_end ov20_02252D14

	thumb_func_start ov20_02252D24
ov20_02252D24: ; 0x02252D24
	push {r3, lr}
	bl ov20_02252B1C
	mov r1, #0x55
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end ov20_02252D24

	thumb_func_start ov20_02252D34
ov20_02252D34: ; 0x02252D34
	push {r3, lr}
	bl ov20_02252B1C
	mov r1, #6
	lsl r1, r1, #6
	ldr r0, [r0, r1]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end ov20_02252D34

	thumb_func_start ov20_02252D44
ov20_02252D44: ; 0x02252D44
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0xc
	mov r1, #0
	add r2, sp, #0
	mov r3, #7
	bl GfGfxLoader_GetPlttData
	add r4, r0, #0
	beq _02252D7A
	ldr r0, [sp]
	mov r2, #0x62
	lsl r2, r2, #2
	add r1, r5, r2
	ldr r0, [r0, #0xc]
	add r2, #0x78
	bl MIi_CpuCopy32
	mov r1, #0x62
	lsl r1, r1, #2
	add r0, r5, r1
	add r1, #0x78
	bl DC_FlushRange
	add r0, r4, #0
	bl FreeToHeap
_02252D7A:
	pop {r3, r4, r5, pc}
	thumb_func_end ov20_02252D44

	thumb_func_start ov20_02252D7C
ov20_02252D7C: ; 0x02252D7C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	bl ov20_02252B1C
	add r4, r0, #0
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov20_02252C3C
	bl Save_Poketch_GetScreenTint
	mov r1, #0x62
	lsl r1, r1, #2
	add r5, r4, r1
	lsl r4, r0, #6
	add r0, r5, r4
	lsl r1, r6, #5
	mov r2, #0x20
	bl GXS_LoadBGPltt
	add r0, r5, r4
	add r1, r7, #0
	mov r2, #0x20
	bl GXS_LoadOBJPltt
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end ov20_02252D7C

	thumb_func_start ov20_02252DB4
ov20_02252DB4: ; 0x02252DB4
	push {r3, r4, r5, lr}
	bl ov20_02252B1C
	add r4, r0, #0
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov20_02252C3C
	bl Save_Poketch_GetScreenTint
	mov r1, #0x62
	lsl r0, r0, #5
	lsl r1, r1, #2
	add r0, #0x10
	add r4, r4, r1
	lsl r5, r0, #1
	add r0, r4, r5
	mov r1, #0
	mov r2, #0x20
	bl GXS_LoadBGPltt
	add r0, r4, r5
	mov r1, #0
	mov r2, #0x20
	bl GXS_LoadOBJPltt
	pop {r3, r4, r5, pc}
	thumb_func_end ov20_02252DB4

	thumb_func_start ov20_02252DEC
ov20_02252DEC: ; 0x02252DEC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl ov20_02252B1C
	add r4, r0, #0
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov20_02252C3C
	bl Save_Poketch_GetScreenTint
	mov r1, #0x62
	lsl r1, r1, #2
	add r1, r4, r1
	lsl r0, r0, #6
	add r0, r1, r0
	add r1, r5, #0
	mov r2, #0x20
	bl MIi_CpuCopy16
	pop {r3, r4, r5, pc}
	thumb_func_end ov20_02252DEC

	thumb_func_start ov20_02252E18
ov20_02252E18: ; 0x02252E18
	push {r4, lr}
	add r4, r0, #0
	beq _02252E58
	mov r0, #0x57
	lsl r0, r0, #2
	add r0, r4, r0
	bl ov20_022535A4
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02252E36
	bl ov20_02253C4C
_02252E36:
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02252E44
	bl FreeToHeap
_02252E44:
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02252E52
	bl sub_0200CAB4
_02252E52:
	add r0, r4, #0
	bl FreeToHeap
_02252E58:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov20_02252E18

	thumb_func_start ov20_02252E5C
ov20_02252E5C: ; 0x02252E5C
	push {r4, r5}
	mov r2, #0xf
	ldr r5, _02252E7C ; =ov20_022545EC
	mov r4, #0
	lsl r2, r2, #0xc
_02252E66:
	ldrh r3, [r5]
	add r4, r4, #1
	add r5, r5, #2
	add r3, r1, r3
	orr r3, r2
	strh r3, [r0]
	add r0, r0, #2
	cmp r4, #0x2c
	blo _02252E66
	pop {r4, r5}
	bx lr
	.align 2, 0
_02252E7C: .word ov20_022545EC
	thumb_func_end ov20_02252E5C

	thumb_func_start ov20_02252E80
ov20_02252E80: ; 0x02252E80
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, r2, #4
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #7
	str r0, [sp, #8]
	ldr r0, _02252EA0 ; =ov20_02254644
	ldr r3, [r2]
	bl ov20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02252EA0: .word ov20_02254644
	thumb_func_end ov20_02252E80

	thumb_func_start ov20_02252EA4
ov20_02252EA4: ; 0x02252EA4
	ldr r3, _02252EAC ; =ov20_02253794
	add r0, r0, #4
	bx r3
	nop
_02252EAC: .word ov20_02253794
	thumb_func_end ov20_02252EA4

	thumb_func_start ov20_02252EB0
ov20_02252EB0: ; 0x02252EB0
	ldr r3, _02252EB8 ; =ov20_022537B8
	add r0, r0, #4
	bx r3
	nop
_02252EB8: .word ov20_022537B8
	thumb_func_end ov20_02252EB0

	thumb_func_start ov20_02252EBC
ov20_02252EBC: ; 0x02252EBC
	push {r4, lr}
	add r4, r0, #0
	bl ov20_022538A0
	add r0, r0, #4
	add r1, r4, #0
	bl ov20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov20_02252EBC

	thumb_func_start ov20_02252ED0
ov20_02252ED0: ; 0x02252ED0
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	mov r0, #0
	bl GXS_SetGraphicsMode
	mov r0, #0x80
	bl GX_SetBankForSubBG
	mov r0, #1
	lsl r0, r0, #8
	bl GX_SetBankForSubOBJ
	ldr r2, _02252FD8 ; =0x04001000
	ldr r0, _02252FDC ; =0xFFCFFFEF
	ldr r1, [r2]
	and r1, r0
	mov r0, #0x10
	orr r0, r1
	str r0, [r2]
	bl GfGfx_DisableEngineBPlanes
	mov r0, #0x10
	mov r1, #1
	bl GfGfx_EngineBTogglePlanes
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	ldr r2, _02252FE0 ; =ov20_022545B4
	mov r1, #4
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	ldr r2, _02252FE4 ; =ov20_022545D0
	mov r1, #5
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #0x40
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #7
	str r0, [sp, #0xc]
	mov r0, #0xc
	lsl r2, r0, #5
	ldr r2, [r4, r2]
	mov r1, #0xe
	mov r3, #4
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #7
	str r0, [sp, #0xc]
	mov r0, #0xc
	lsl r2, r0, #5
	ldr r2, [r4, r2]
	mov r1, #0xf
	mov r3, #4
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov20_02252C44
	add r3, r0, #0
	mov r0, #0x1e
	lsl r0, r0, #4
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #7
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0xd
	mov r2, #4
	lsl r3, r3, #5
	bl GfGfxLoader_GXLoadPalWithSrcOffset
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r1, #0x18
	str r1, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r4, r0]
	mov r1, #5
	mov r2, #0xd8
	bl FillBgTilemapRect
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #5
	bl BgCommitTilemapBufferToVram
	ldr r0, _02252FD8 ; =0x04001000
	ldr r1, _02252FE8 ; =0xFFFFE0FF
	ldr r2, [r0]
	and r2, r1
	mov r1, #0x13
	lsl r1, r1, #8
	orr r1, r2
	str r1, [r0]
	ldr r2, [r0]
	ldr r1, _02252FEC ; =0xFFFF1FFF
	and r1, r2
	str r1, [r0]
	add r0, r5, #0
	bl ov20_02252EBC
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_02252FD8: .word 0x04001000
_02252FDC: .word 0xFFCFFFEF
_02252FE0: .word ov20_022545B4
_02252FE4: .word ov20_022545D0
_02252FE8: .word 0xFFFFE0FF
_02252FEC: .word 0xFFFF1FFF
	thumb_func_end ov20_02252ED0

	thumb_func_start ov20_02252FF0
ov20_02252FF0: ; 0x02252FF0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r1, [sp, #0x10]
	add r0, r1, #0
	bl ov20_022538A8
	add r4, r0, #0
	ldr r0, [sp, #0x10]
	bl ov20_022538A0
	add r5, r0, #0
	ldr r0, [sp, #0x10]
	bl ov20_022538AC
	cmp r0, #0
	beq _0225301C
	cmp r0, #1
	beq _02253028
	cmp r0, #2
	beq _022530F6
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0225301C:
	mov r0, #0
	strh r0, [r4]
	strh r0, [r4, #2]
	ldr r0, [sp, #0x10]
	bl ov20_022538B0
_02253028:
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	ldrh r0, [r4]
	cmp r0, #0
	beq _022530FC
	mov r0, #0
	strh r0, [r4]
	ldrh r0, [r4, #2]
	add r0, #0xc
	strh r0, [r4, #2]
	ldrh r0, [r4, #2]
	cmp r0, #0x28
	bls _02253048
	mov r0, #0x28
	strh r0, [r4, #2]
_02253048:
	ldrh r1, [r4, #2]
	lsr r3, r1, #0x1f
	lsl r2, r1, #0x1e
	lsr r0, r1, #2
	sub r2, r2, r3
	mov r1, #0x1e
	ror r2, r1
	mov r1, #0xc
	sub r6, r1, r0
	lsl r0, r0, #1
	str r0, [sp, #0x14]
	lsl r0, r6, #0x18
	ldr r1, [sp, #0x14]
	add r7, r3, r2
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x18
	lsl r1, r1, #0x18
	str r0, [sp, #4]
	lsr r1, r1, #0x18
	str r1, [sp, #8]
	mov r1, #0xf
	str r1, [sp, #0xc]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #5
	mov r2, #0x40
	mov r3, #2
	bl FillBgTilemapRect
	cmp r7, #0
	beq _022530DA
	sub r0, r6, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r1, #0x18
	add r2, r7, #0
	add r2, #0xd8
	lsl r2, r2, #0x10
	str r1, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r5, r0]
	mov r1, #5
	lsr r2, r2, #0x10
	mov r3, #2
	bl FillBgTilemapRect
	ldr r0, [sp, #0x14]
	mov r2, #0xd8
	add r0, r6, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r1, #0x18
	sub r2, r2, r7
	lsl r2, r2, #0x10
	str r1, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r5, r0]
	mov r1, #5
	lsr r2, r2, #0x10
	mov r3, #2
	bl FillBgTilemapRect
_022530DA:
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #5
	bl BgCommitTilemapBufferToVram
	ldrh r0, [r4, #2]
	cmp r0, #0x28
	bne _022530FC
	ldr r0, [sp, #0x10]
	bl ov20_022538B0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_022530F6:
	ldr r0, [sp, #0x10]
	bl ov20_02252EBC
_022530FC:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end ov20_02252FF0

	thumb_func_start ov20_02253100
ov20_02253100: ; 0x02253100
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r1, [sp, #0x10]
	add r0, r1, #0
	bl ov20_022538A8
	add r4, r0, #0
	ldr r0, [sp, #0x10]
	bl ov20_022538A0
	add r5, r0, #0
	ldr r0, [sp, #0x10]
	bl ov20_022538AC
	cmp r0, #0
	beq _0225312C
	cmp r0, #1
	beq _02253138
	cmp r0, #2
	beq _0225321E
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0225312C:
	mov r0, #0
	strh r0, [r4]
	strh r0, [r4, #2]
	ldr r0, [sp, #0x10]
	bl ov20_022538B0
_02253138:
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	ldrh r0, [r4]
	cmp r0, #0
	beq _02253224
	mov r0, #0
	strh r0, [r4]
	ldrh r0, [r4, #2]
	add r0, #8
	strh r0, [r4, #2]
	ldrh r0, [r4, #2]
	cmp r0, #0x28
	bls _02253158
	mov r0, #0x28
	strh r0, [r4, #2]
_02253158:
	ldrh r0, [r4, #2]
	mov r3, #2
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1e
	lsr r7, r0, #2
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r6, r2, r1
	mov r0, #0x16
	sub r0, r0, r7
	str r0, [sp, #0x14]
	lsl r1, r7, #0x18
	str r3, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	lsr r1, r1, #0x18
	str r1, [sp, #8]
	mov r1, #0xf
	str r1, [sp, #0xc]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #5
	mov r2, #0xd8
	bl FillBgTilemapRect
	ldr r0, [sp, #0x14]
	lsl r1, r7, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	lsr r1, r1, #0x18
	str r1, [sp, #8]
	mov r1, #0xf
	str r1, [sp, #0xc]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #5
	mov r2, #0xd8
	mov r3, #2
	bl FillBgTilemapRect
	cmp r6, #0
	beq _02253202
	mov r0, #0
	str r0, [sp]
	mov r1, #0x18
	str r1, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	sub r3, r6, #1
	mov r2, #0xdb
	sub r2, r2, r3
	lsl r2, r2, #0x10
	ldr r0, [r5, r0]
	mov r1, #5
	lsr r2, r2, #0x10
	mov r3, #2
	bl FillBgTilemapRect
	ldr r0, [sp, #0x14]
	add r6, #0xd4
	sub r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r1, #0x18
	lsl r2, r6, #0x10
	str r1, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r5, r0]
	mov r1, #5
	lsr r2, r2, #0x10
	mov r3, #2
	bl FillBgTilemapRect
_02253202:
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #5
	bl BgCommitTilemapBufferToVram
	ldrh r0, [r4, #2]
	cmp r0, #0x28
	bne _02253224
	ldr r0, [sp, #0x10]
	bl ov20_022538B0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0225321E:
	ldr r0, [sp, #0x10]
	bl ov20_02252EBC
_02253224:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end ov20_02253100

	thumb_func_start ov20_02253228
ov20_02253228: ; 0x02253228
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A8
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538AC
	add r2, r0, #0
	cmp r2, #4
	bhs _02253280
	mov r3, #2
	str r3, [sp]
	mov r1, #0x18
	mov r6, #0xd7
	sub r2, r6, r2
	lsl r2, r2, #0x10
	str r1, [sp, #4]
	mov r0, #0x14
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r4, r0]
	mov r1, #5
	lsr r2, r2, #0x10
	bl FillBgTilemapRect
	add r0, r6, #0
	add r0, #0xa9
	ldr r0, [r4, r0]
	mov r1, #5
	bl BgCommitTilemapBufferToVram
	add r0, r5, #0
	bl ov20_022538B0
	add sp, #0x10
	pop {r4, r5, r6, pc}
_02253280:
	add r0, r5, #0
	bl ov20_02252EBC
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov20_02253228

	thumb_func_start ov20_0225328C
ov20_0225328C: ; 0x0225328C
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A8
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538AC
	add r2, r0, #0
	cmp r2, #4
	bhs _022532E4
	mov r3, #2
	str r3, [sp]
	mov r1, #0x18
	mov r6, #0xdb
	sub r2, r6, r2
	lsl r2, r2, #0x10
	str r1, [sp, #4]
	mov r0, #0x14
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r4, r0]
	mov r1, #5
	lsr r2, r2, #0x10
	bl FillBgTilemapRect
	add r0, r6, #0
	add r0, #0xa5
	ldr r0, [r4, r0]
	mov r1, #5
	bl BgCommitTilemapBufferToVram
	add r0, r5, #0
	bl ov20_022538B0
	add sp, #0x10
	pop {r4, r5, r6, pc}
_022532E4:
	add r0, r5, #0
	bl ov20_02252EBC
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov20_0225328C

	thumb_func_start ov20_022532F0
ov20_022532F0: ; 0x022532F0
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	mov r0, #0xb
	add r2, r4, #0
	str r0, [sp]
	mov r1, #4
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	add r2, #0x84
	mov r3, #0x1b
	bl LoadRectToBgTilemapRect
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #4
	bl BgCommitTilemapBufferToVram
	ldr r0, _02253334 ; =0x00000671
	bl PlaySE
	add r0, r5, #0
	bl ov20_02252EBC
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02253334: .word 0x00000671
	thumb_func_end ov20_022532F0

	thumb_func_start ov20_02253338
ov20_02253338: ; 0x02253338
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	mov r0, #0xb
	add r2, r4, #0
	str r0, [sp]
	mov r1, #4
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	add r2, #0x2c
	mov r3, #0x1b
	bl LoadRectToBgTilemapRect
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #4
	bl BgCommitTilemapBufferToVram
	add r0, r5, #0
	bl ov20_02252EBC
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end ov20_02253338

	thumb_func_start ov20_02253378
ov20_02253378: ; 0x02253378
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	mov r0, #0xb
	add r2, r4, #0
	str r0, [sp]
	mov r1, #4
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	add r2, #0xdc
	mov r3, #0x1b
	bl LoadRectToBgTilemapRect
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #4
	bl BgCommitTilemapBufferToVram
	ldr r0, _022533BC ; =0x0000066F
	bl PlaySE
	add r0, r5, #0
	bl ov20_02252EBC
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_022533BC: .word 0x0000066F
	thumb_func_end ov20_02253378

	thumb_func_start ov20_022533C0
ov20_022533C0: ; 0x022533C0
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	mov r1, #0x57
	add r4, r0, #0
	lsl r1, r1, #2
	add r1, r4, r1
	bl ov20_02253430
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r1, [r4]
	add r0, r4, r0
	bl ov20_0225354C
	add r0, r5, #0
	bl ov20_02252EBC
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end ov20_022533C0

	thumb_func_start ov20_022533EC
ov20_022533EC: ; 0x022533EC
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl ov20_022538A0
	add r1, r0, #0
	mov r0, #0x57
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r1, [r1]
	bl ov20_0225354C
	add r0, r4, #0
	bl ov20_02252EBC
	pop {r4, pc}
	thumb_func_end ov20_022533EC

	thumb_func_start ov20_0225340C
ov20_0225340C: ; 0x0225340C
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl ov20_022538A0
	mov r1, #0x57
	lsl r1, r1, #2
	add r0, r0, r1
	bl ov20_022535A4
	add r0, r4, #0
	bl ov20_02252EBC
	pop {r4, pc}
	thumb_func_end ov20_0225340C

	thumb_func_start ov20_02253428
ov20_02253428: ; 0x02253428
	mov r2, #0
	str r2, [r0]
	str r1, [r0, #4]
	bx lr
	thumb_func_end ov20_02253428

	thumb_func_start ov20_02253430
ov20_02253430: ; 0x02253430
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #7
	str r0, [sp]
	add r0, r4, #0
	add r0, #8
	mov r1, #0xc
	mov r2, #3
	mov r3, #4
	bl ov20_02253FBC
	cmp r0, #0
	beq _022534CC
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	mov r0, #7
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #2
	bl GfGfxLoader_LoadWholePalette
	mov r0, #0x60
	str r0, [sp]
	mov r0, #7
	mov r1, #0
	str r0, [sp, #4]
	mov r0, #0xc
	mov r2, #5
	add r3, r1, #0
	bl GfGfxLoader_GXLoadPal
	add r0, r5, #0
	mov r1, #0xf
	bl ov20_022534D4
	add r2, r4, #0
	ldr r0, [r4, #4]
	ldr r1, _022534D0 ; =ov20_022545A4
	add r2, #8
	bl ov20_02253E74
	str r0, [r4, #0x1c]
	cmp r0, #0
	beq _022534CC
	add r2, r4, #0
	ldr r0, [r4, #4]
	ldr r1, _022534D0 ; =ov20_022545A4
	add r2, #8
	bl ov20_02253E74
	str r0, [r4, #0x20]
	cmp r0, #0
	bne _022534AE
	ldr r0, [r4, #4]
	ldr r1, [r4, #0x1c]
	bl ov20_02253F14
	add sp, #0xc
	pop {r4, r5, pc}
_022534AE:
	mov r1, #1
	lsl r1, r1, #0x10
	mov r2, #0
	bl ov20_02253F54
	ldr r0, [r4, #0x1c]
	mov r1, #0xf
	bl ov20_02253F9C
	ldr r0, [r4, #0x20]
	mov r1, #0xf
	bl ov20_02253F9C
	mov r0, #1
	str r0, [r4]
_022534CC:
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_022534D0: .word ov20_022545A4
	thumb_func_end ov20_02253430

	thumb_func_start ov20_022534D4
ov20_022534D4: ; 0x022534D4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	bl ov20_02252C3C
	bl Save_Poketch_GetScreenTint
	mov r1, #0x62
	lsl r0, r0, #5
	lsl r1, r1, #2
	add r0, r0, #1
	add r2, r5, r1
	lsl r0, r0, #1
	add r0, r2, r0
	add r1, #0x5a
	mov r2, #2
	bl GXS_LoadBGPltt
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r5, r0
	bl ov20_02252DEC
	ldr r1, _02253548 ; =0x0000038A
	add r0, r1, #6
	ldrh r2, [r5, r1]
	ldrh r0, [r5, r0]
	strh r0, [r5, r1]
	add r0, r1, #6
	strh r2, [r5, r0]
	add r0, r1, #0
	add r2, r1, #0
	add r0, #0xe
	add r2, #0x1c
	ldrh r3, [r5, r2]
	add r2, r1, #0
	ldrh r0, [r5, r0]
	add r2, #0xe
	strh r3, [r5, r2]
	add r2, r1, #0
	add r2, #0x1c
	strh r0, [r5, r2]
	sub r0, r1, #2
	add r0, r5, r0
	mov r1, #0x20
	bl DC_FlushRange
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r5, r0
	lsl r1, r4, #5
	mov r2, #0x20
	bl GXS_LoadOBJPltt
	pop {r3, r4, r5, pc}
	.align 2, 0
_02253548: .word 0x0000038A
	thumb_func_end ov20_022534D4

	thumb_func_start ov20_0225354C
ov20_0225354C: ; 0x0225354C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _02253596
	ldr r0, [r1]
	ldr r2, _02253598 ; =0x04000280
	mov r3, #0
	add r0, r0, #1
	strh r3, [r2]
	str r0, [r2, #0x10]
	add r0, r2, #0
	mov r1, #0xa
	add r0, #0x18
	str r1, [r0]
	str r3, [r0, #4]
	lsr r0, r2, #0xb
_0225356E:
	ldrh r1, [r2]
	tst r1, r0
	bne _0225356E
	ldr r0, _0225359C ; =0x040002A0
	add r3, r0, #0
	ldr r1, [r0]
	sub r3, #0x20
	lsr r0, r0, #0xb
_0225357E:
	ldrh r2, [r3]
	tst r2, r0
	bne _0225357E
	ldr r0, _022535A0 ; =0x040002A8
	ldr r5, [r0]
	ldr r0, [r4, #0x1c]
	bl ov20_02253F28
	ldr r0, [r4, #0x20]
	add r1, r5, #0
	bl ov20_02253F28
_02253596:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02253598: .word 0x04000280
_0225359C: .word 0x040002A0
_022535A0: .word 0x040002A8
	thumb_func_end ov20_0225354C

	thumb_func_start ov20_022535A4
ov20_022535A4: ; 0x022535A4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _022535CA
	ldr r0, [r4, #4]
	ldr r1, [r4, #0x1c]
	bl ov20_02253F14
	ldr r0, [r4, #4]
	ldr r1, [r4, #0x20]
	bl ov20_02253F14
	add r0, r4, #0
	add r0, #8
	bl ov20_02254014
	mov r0, #0
	str r0, [r4]
_022535CA:
	pop {r4, pc}
	thumb_func_end ov20_022535A4

	thumb_func_start ov20_022535CC
ov20_022535CC: ; 0x022535CC
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r6, r1, #0
	add r0, r6, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r6, #0
	bl ov20_022538A8
	add r0, r6, #0
	bl ov20_022538AC
	add r5, r0, #0
	cmp r5, #3
	bhi _0225365E
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022535F8: ; jump table
	.short _02253600 - _022535F8 - 2 ; case 0
	.short _0225361C - _022535F8 - 2 ; case 1
	.short _0225361C - _022535F8 - 2 ; case 2
	.short _0225361C - _022535F8 - 2 ; case 3
_02253600:
	mov r0, #6
	str r0, [sp]
	ldr r0, _02253664 ; =0x04001050
	mov r1, #2
	mov r2, #0x1c
	mov r3, #0x1a
	bl G2x_SetBlendAlpha_
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #4
	bl BgCommitTilemapBufferToVram
_0225361C:
	mov r3, #2
	str r3, [sp]
	mov r1, #0x18
	mov r2, #0xdb
	sub r2, r2, r5
	lsl r2, r2, #0x10
	str r1, [sp, #4]
	mov r0, #0x14
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r4, r0]
	mov r1, #5
	lsr r2, r2, #0x10
	bl FillBgTilemapRect
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #5
	bl BgCommitTilemapBufferToVram
	cmp r5, #3
	bne _02253658
	add r0, r6, #0
	bl ov20_02252EBC
	add sp, #0x10
	pop {r4, r5, r6, pc}
_02253658:
	add r0, r6, #0
	bl ov20_022538B0
_0225365E:
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_02253664: .word 0x04001050
	thumb_func_end ov20_022535CC

	thumb_func_start ov20_02253668
ov20_02253668: ; 0x02253668
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	mov r3, #2
	add r4, r0, #0
	str r3, [sp]
	mov r1, #0x18
	str r1, [sp, #4]
	mov r0, #0x14
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r4, r0]
	mov r1, #5
	mov r2, #0x40
	bl FillBgTilemapRect
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #4
	bl BgCommitTilemapBufferToVram
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #5
	bl BgCommitTilemapBufferToVram
	mov r1, #0
	ldr r0, _022536C4 ; =0x04001050
	add r2, r1, #0
	mov r3, #0x1f
	str r1, [sp]
	bl G2x_SetBlendAlpha_
	add r0, r5, #0
	bl ov20_02252EBC
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_022536C4: .word 0x04001050
	thumb_func_end ov20_02253668

	thumb_func_start ov20_022536C8
ov20_022536C8: ; 0x022536C8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #4
	bl FreeBgTilemapBuffer
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #5
	bl FreeBgTilemapBuffer
	add r0, r5, #0
	bl ov20_02252EBC
	pop {r3, r4, r5, pc}
	thumb_func_end ov20_022536C8

    .section .rodata

	.global ov20_022545A4
ov20_022545A4: ; 0x022545A4
	.byte 0x00, 0x00, 0x0B, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov20_022545B4
ov20_022545B4: ; 0x022545B4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov20_022545D0
ov20_022545D0: ; 0x022545D0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0D, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov20_022545EC
ov20_022545EC: ; 0x022545EC
	.short 0x0000, 0x0001, 0x0002, 0x0003, 0x0015, 0x0016, 0x0017, 0x0018
	.short 0x002A, 0x002B, 0x002C, 0x002D, 0x002A, 0x002B, 0x002C, 0x002D
	.short 0x002A, 0x002B, 0x002C, 0x002D, 0x002A, 0x002B, 0x002C, 0x002D
	.short 0x002A, 0x002B, 0x002C, 0x002D, 0x002A, 0x002B, 0x002C, 0x002D
	.short 0x002A, 0x002B, 0x002C, 0x002D, 0x003F, 0x0040, 0x0041, 0x0042
	.short 0x0054, 0x0055, 0x0056, 0x0057

	.global ov20_02254644
ov20_02254644: ; 0x02254644
	.word 0x00000000, ov20_02252ED0, 0x00000000
	.word 0x00000001, ov20_02252FF0, 0x00000004
	.word 0x00000002, ov20_02252FF0, 0x00000004
	.word 0x00000003, ov20_02253228, 0x00000004
	.word 0x00000004, ov20_02253100, 0x00000004
	.word 0x00000005, ov20_0225328C, 0x00000004
	.word 0x00000006, ov20_022532F0, 0x00000000
	.word 0x00000008, ov20_02253338, 0x00000000
	.word 0x00000007, ov20_02253378, 0x00000000
	.word 0x00000009, ov20_022533C0, 0x00000000
	.word 0x0000000A, ov20_022533EC, 0x00000000
	.word 0x0000000B, ov20_0225340C, 0x00000000
	.word 0x0000000C, ov20_022535CC, 0x00000000
	.word 0x0000000D, ov20_02253668, 0x00000000
	.word 0x0000000E, ov20_022536C8, 0x00000000
	.word 0xFFFFFFFF, 0x00000000, 0x00000000
