	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 2, 0

	thumb_func_start MOD20_022536F4
MOD20_022536F4: ; 0x022536F4
	ldr r2, _02253710 ; =0x12345678
	str r1, [r0]
	mov r3, #0
	str r2, [r0, #4]
	cmp r1, #0
	bls _0225370C
	sub r2, r3, #1
_02253702:
	add r3, r3, #1
	str r2, [r0, #8]
	add r0, r0, #4
	cmp r3, r1
	blo _02253702
_0225370C:
	bx lr
	nop
_02253710: .word 0x12345678
	thumb_func_end MOD20_022536F4

	thumb_func_start MOD20_02253714
MOD20_02253714: ; 0x02253714
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, [r5, #4]
	ldr r0, _02253750 ; =0x12345678
	cmp r1, r0
	beq _02253726
	bl GF_AssertFail
_02253726:
	ldr r6, [r5]
	mov r2, #0
	cmp r6, #0
	bls _0225374A
	add r3, r5, #0
	sub r0, r2, #1
_02253732:
	ldr r1, [r3, #8]
	cmp r1, r0
	bne _02253742
	lsl r0, r2, #2
	add r0, r5, r0
	str r4, [r0, #8]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02253742:
	add r2, r2, #1
	add r3, r3, #4
	cmp r2, r6
	blo _02253732
_0225374A:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_02253750: .word 0x12345678
	thumb_func_end MOD20_02253714

	thumb_func_start MOD20_02253754
MOD20_02253754: ; 0x02253754
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, [r5, #4]
	ldr r0, _02253790 ; =0x12345678
	cmp r1, r0
	beq _02253766
	bl GF_AssertFail
_02253766:
	ldr r3, [r5]
	mov r2, #0
	cmp r3, #0
	bls _0225378A
	add r1, r5, #0
_02253770:
	ldr r0, [r1, #8]
	cmp r4, r0
	bne _02253782
	mov r1, #0
	lsl r0, r2, #2
	mvn r1, r1
	add r0, r5, r0
	str r1, [r0, #8]
	pop {r3, r4, r5, pc}
_02253782:
	add r2, r2, #1
	add r1, r1, #4
	cmp r2, r3
	blo _02253770
_0225378A:
	bl GF_AssertFail
	pop {r3, r4, r5, pc}
	.align 2, 0
_02253790: .word 0x12345678
	thumb_func_end MOD20_02253754

	thumb_func_start MOD20_02253794
MOD20_02253794: ; 0x02253794
	push {r3, r4}
	ldr r4, [r0]
	mov r3, #0
	cmp r4, #0
	bls _022537B2
_0225379E:
	ldr r2, [r0, #8]
	cmp r1, r2
	bne _022537AA
	mov r0, #0
	pop {r3, r4}
	bx lr
_022537AA:
	add r3, r3, #1
	add r0, r0, #4
	cmp r3, r4
	blo _0225379E
_022537B2:
	mov r0, #1
	pop {r3, r4}
	bx lr
	thumb_func_end MOD20_02253794

	thumb_func_start MOD20_022537B8
MOD20_022537B8: ; 0x022537B8
	push {r3, r4}
	ldr r4, [r0]
	mov r3, #0
	cmp r4, #0
	bls _022537D8
	sub r1, r3, #1
_022537C4:
	ldr r2, [r0, #8]
	cmp r2, r1
	beq _022537D0
	mov r0, #0
	pop {r3, r4}
	bx lr
_022537D0:
	add r3, r3, #1
	add r0, r0, #4
	cmp r3, r4
	blo _022537C4
_022537D8:
	mov r0, #1
	pop {r3, r4}
	bx lr
	.align 2, 0
	thumb_func_end MOD20_022537B8

	thumb_func_start MOD20_022537E0
MOD20_022537E0: ; 0x022537E0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r0, #0
	str r2, [sp]
	mov r0, #0
	add r5, r1, #0
	ldr r2, [r7]
	sub r1, r0, #1
	str r3, [sp, #4]
	cmp r2, r1
	beq _02253880
	add r3, r7, #0
	sub r1, r0, #1
_022537FA:
	ldr r2, [r3]
	cmp r5, r2
	bne _02253876
	add r6, r0, #0
	add r0, r7, #0
	str r0, [sp, #8]
	add r0, #8
	mov r1, #0xc
	str r0, [sp, #8]
	mul r6, r1
	ldr r1, [sp, #8]
	ldr r0, [sp, #0x28]
	ldr r1, [r1, r6]
	add r1, #0x18
	bl AllocFromHeap
	add r4, r0, #0
	beq _02253870
	ldr r0, [sp, #8]
	ldr r0, [r0, r6]
	cmp r0, #0
	beq _0225382C
	add r0, r4, #0
	add r0, #0x18
	b _0225382E
_0225382C:
	mov r0, #0
_0225382E:
	str r0, [r4, #0xc]
	ldr r0, [sp, #0x20]
	add r1, r5, #0
	bl MOD20_02253714
	cmp r0, #0
	beq _02253866
	ldr r0, [sp]
	ldr r2, [sp, #0x24]
	str r0, [r4, #8]
	mov r0, #0
	str r0, [r4, #4]
	str r5, [r4]
	ldr r0, [sp, #4]
	add r5, r7, #4
	str r0, [r4, #0x10]
	ldr r0, [r5, r6]
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #0x14]
	cmp r0, #0
	beq _02253884
	ldr r2, [r5, r6]
	add r1, r4, #0
	blx r2
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_02253866:
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_02253870:
	bl GF_AssertFail
	b _02253880
_02253876:
	add r3, #0xc
	ldr r2, [r3]
	add r0, r0, #1
	cmp r2, r1
	bne _022537FA
_02253880:
	bl GF_AssertFail
_02253884:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD20_022537E0

	thumb_func_start MOD20_02253888
MOD20_02253888: ; 0x02253888
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4]
	bl MOD20_02253754
	ldr r0, [r4, #0x14]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD20_02253888

	thumb_func_start MOD20_022538A0
MOD20_022538A0: ; 0x022538A0
	ldr r0, [r0, #8]
	bx lr
	thumb_func_end MOD20_022538A0

	thumb_func_start MOD20_022538A4
MOD20_022538A4: ; 0x022538A4
	ldr r0, [r0, #0x10]
	bx lr
	thumb_func_end MOD20_022538A4

	thumb_func_start MOD20_022538A8
MOD20_022538A8: ; 0x022538A8
	ldr r0, [r0, #0xc]
	bx lr
	thumb_func_end MOD20_022538A8

	thumb_func_start MOD20_022538AC
MOD20_022538AC: ; 0x022538AC
	ldr r0, [r0, #4]
	bx lr
	thumb_func_end MOD20_022538AC

	thumb_func_start MOD20_022538B0
MOD20_022538B0: ; 0x022538B0
	ldr r1, [r0, #4]
	add r1, r1, #1
	str r1, [r0, #4]
	bx lr
	thumb_func_end MOD20_022538B0

	thumb_func_start MOD20_022538B8
MOD20_022538B8: ; 0x022538B8
	str r1, [r0, #4]
	bx lr
	thumb_func_end MOD20_022538B8

	thumb_func_start MOD20_022538BC
MOD20_022538BC: ; 0x022538BC
	push {r3, r4, r5, r6}
	mul r2, r3
	ldr r4, [sp, #0x18]
	add r1, r1, r2
	lsl r6, r1, #1
	lsl r4, r4, #0xc
	ldr r1, [sp, #0x10]
	add r5, r4, #0
	orr r5, r1
	add r2, r0, r6
	strh r5, [r0, r6]
	add r0, r1, #1
	orr r0, r4
	strh r0, [r2, #2]
	ldr r0, [sp, #0x14]
	lsl r3, r3, #1
	add r1, r1, r0
	add r0, r4, #0
	orr r0, r1
	strh r0, [r2, r3]
	add r0, r1, #1
	add r1, r4, #0
	orr r1, r0
	add r0, r2, r3
	strh r1, [r0, #2]
	pop {r3, r4, r5, r6}
	bx lr
	.align 2, 0
	thumb_func_end MOD20_022538BC

	thumb_func_start MOD20_022538F4
MOD20_022538F4: ; 0x022538F4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x20
	bl AllocFromHeap
	add r7, r0, #0
	beq _02253960
	bl MOD20_02252DEC
	mov r4, #0
	cmp r6, #0
	bls _0225395A
_02253910:
	ldrh r3, [r5]
	mov r0, #0x1f
	lsl r0, r0, #0xa
	and r0, r3
	asr r0, r0, #0xa
	add r2, r0, #0
	mov r1, #0x72
	mov r0, #0x1f
	mul r2, r1
	and r0, r3
	add r1, #0xb9
	mul r1, r0
	mov r0, #0x3e
	lsl r0, r0, #4
	and r0, r3
	asr r3, r0, #5
	ldr r0, _02253964 ; =0x0000024B
	mul r0, r3
	add r0, r1, r0
	mov r1, #0xfa
	add r0, r2, r0
	lsl r1, r1, #2
	bl _u32_div_f
	lsr r1, r0, #3
	cmp r1, #3
	bls _02253948
	mov r1, #3
_02253948:
	ldr r0, _02253968 ; =MOD20_0225470C
	add r4, r4, #1
	ldrb r0, [r0, r1]
	lsl r0, r0, #1
	ldrh r0, [r7, r0]
	strh r0, [r5]
	add r5, r5, #2
	cmp r4, r6
	blo _02253910
_0225395A:
	add r0, r7, #0
	bl FreeToHeap
_02253960:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02253964: .word 0x0000024B
_02253968: .word MOD20_0225470C
	thumb_func_end MOD20_022538F4

	thumb_func_start MOD20_0225396C
MOD20_0225396C: ; 0x0225396C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #8
	mov r1, #0x20
	bl AllocFromHeap
	add r4, r0, #0
	beq _022539C2
	mov r0, #8
	mov r1, #0x20
	bl AllocFromHeap
	add r5, r0, #0
	add r0, r4, #0
	bl MOD20_02252DEC
	cmp r5, #0
	beq _022539BC
	mov r0, #0
	add r1, r5, #0
	lsl r3, r6, #1
_02253998:
	ldrh r2, [r4, r3]
	add r0, r0, #1
	strh r2, [r1]
	add r1, r1, #2
	cmp r0, #0x10
	blt _02253998
	add r0, r5, #0
	mov r1, #0x20
	bl DC_FlushRange
	add r0, r5, #0
	lsl r1, r7, #5
	mov r2, #0x20
	bl GXS_LoadOBJPltt
	add r0, r5, #0
	bl FreeToHeap
_022539BC:
	add r0, r4, #0
	bl FreeToHeap
_022539C2:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD20_0225396C

	thumb_func_start MOD20_022539C4
MOD20_022539C4: ; 0x022539C4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_0206B888
	add r1, r0, #0
	mov r0, #0x13
	add r2, sp, #0
	mov r3, #8
	bl GfGfxLoader_GetPlttData
	add r4, r0, #0
	beq _02253A02
	ldr r0, [sp]
	mov r1, #0x40
	ldr r0, [r0, #0xc]
	bl MOD20_022538F4
	ldr r0, [sp]
	mov r1, #0x80
	ldr r0, [r0, #0xc]
	bl DC_FlushRange
	ldr r0, [sp]
	lsl r1, r5, #5
	ldr r0, [r0, #0xc]
	mov r2, #0x80
	bl GXS_LoadOBJPltt
	add r0, r4, #0
	bl FreeToHeap
_02253A02:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD20_022539C4

	thumb_func_start MOD20_02253A04
MOD20_02253A04: ; 0x02253A04
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r0, [sp, #4]
	lsl r0, r3, #1
	str r0, [sp, #0xc]
	add r6, r1, #0
	str r2, [sp, #8]
	ldr r2, _02253A9C ; =MOD20_02254708
	ldr r1, [sp, #0xc]
	mov r0, #8
	ldrh r1, [r2, r1]
	bl AllocFromHeap
	add r7, r0, #0
	beq _02253A98
	mov r0, #0x13
	mov r1, #8
	bl NARC_ctor
	str r0, [sp, #0x1c]
	cmp r0, #0
	beq _02253A92
	mov r0, #0
	str r0, [sp, #0x18]
	ldr r0, [sp, #8]
	cmp r0, #0
	bls _02253A8C
	ldr r1, _02253AA0 ; =MOD20_02254704
	ldr r0, [sp, #0xc]
	ldr r4, [sp, #0x18]
	ldrh r5, [r1, r0]
	ldr r1, _02253A9C ; =MOD20_02254708
	ldrh r0, [r1, r0]
	str r0, [sp, #0x14]
	ldr r0, [sp, #4]
	lsl r0, r0, #5
	str r0, [sp, #0x10]
_02253A4E:
	str r7, [sp]
	ldr r0, [sp, #0x1c]
	ldr r1, [r6]
	ldr r3, [sp, #0x14]
	mov r2, #0
	bl NARC_ReadFromMember
	add r0, r7, #0
	add r1, sp, #0x20
	bl NNS_G2dGetUnpackedCharacterData
	ldr r0, [sp, #0x20]
	add r1, r5, #0
	ldr r0, [r0, #0x14]
	bl DC_FlushRange
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x10]
	ldr r0, [r0, #0x14]
	add r1, r1, r4
	add r2, r5, #0
	bl GXS_LoadOBJ
	ldr r0, [sp, #0x18]
	add r6, r6, #4
	add r1, r0, #1
	ldr r0, [sp, #8]
	add r4, r4, r5
	str r1, [sp, #0x18]
	cmp r1, r0
	blo _02253A4E
_02253A8C:
	ldr r0, [sp, #0x1c]
	bl NARC_dtor
_02253A92:
	add r0, r7, #0
	bl FreeToHeap
_02253A98:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02253A9C: .word MOD20_02254708
_02253AA0: .word MOD20_02254704
	thumb_func_end MOD20_02253A04

	thumb_func_start MOD20_02253AA4
MOD20_02253AA4: ; 0x02253AA4
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r5, r1, #0
	add r4, r2, #0
	mov r1, #2
	add r2, sp, #0xc
	strh r1, [r2]
	mov r3, #3
	strh r3, [r2, #2]
	mov r3, #0xa
	strh r3, [r2, #4]
	mov r3, #0xb
	strh r3, [r2, #6]
	str r3, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	lsl r1, r4, #0x18
	lsr r1, r1, #0x18
	add r2, sp, #0xc
	mov r3, #9
	add r6, r0, #0
	bl LoadRectToBgTilemapRect
	mov r1, #4
	add r0, sp, #0xc
	strh r1, [r0]
	mov r1, #5
	strh r1, [r0, #2]
	mov r1, #0xc
	strh r1, [r0, #4]
	mov r1, #0xd
	strh r1, [r0, #6]
	mov r3, #0xb
	lsl r1, r4, #0x18
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r6, #0
	lsr r1, r1, #0x18
	add r2, sp, #0xc
	bl LoadRectToBgTilemapRect
	mov r1, #6
	add r0, sp, #0xc
	strh r1, [r0]
	mov r1, #7
	strh r1, [r0, #2]
	mov r1, #0xe
	strh r1, [r0, #4]
	mov r1, #0xf
	strh r1, [r0, #6]
	mov r0, #0xb
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	lsl r1, r4, #0x18
	str r0, [sp, #8]
	add r0, r6, #0
	lsr r1, r1, #0x18
	add r2, sp, #0xc
	mov r3, #0xd
	bl LoadRectToBgTilemapRect
	add r0, r5, #0
	mov r1, #0xa
	bl _u32_div_f
	mov r1, #0xa
	mul r1, r0
	add r0, r0, #4
	sub r5, r5, r1
	lsr r1, r0, #2
	lsl r0, r0, #0x1e
	lsl r1, r1, #4
	lsr r0, r0, #0x1d
	add r2, r1, r0
	add r0, sp, #0xc
	strh r2, [r0]
	add r1, r2, #1
	strh r1, [r0, #2]
	add r1, r2, #0
	add r1, #8
	strh r1, [r0, #4]
	add r2, #9
	strh r2, [r0, #6]
	mov r0, #0xb
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	lsl r1, r4, #0x18
	str r0, [sp, #8]
	add r0, r6, #0
	lsr r1, r1, #0x18
	add r2, sp, #0xc
	mov r3, #0xf
	bl LoadRectToBgTilemapRect
	add r0, r5, #4
	lsr r1, r0, #2
	lsl r0, r0, #0x1e
	lsl r1, r1, #4
	lsr r0, r0, #0x1d
	add r2, r1, r0
	add r0, sp, #0xc
	strh r2, [r0]
	add r1, r2, #1
	strh r1, [r0, #2]
	add r1, r2, #0
	add r1, #8
	strh r1, [r0, #4]
	add r2, #9
	strh r2, [r0, #6]
	mov r0, #0xb
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	lsl r1, r4, #0x18
	str r0, [sp, #8]
	add r0, r6, #0
	lsr r1, r1, #0x18
	add r2, sp, #0xc
	mov r3, #0x11
	bl LoadRectToBgTilemapRect
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD20_02253AA4

    .section .rodata

    .global MOD20_02254704
MOD20_02254704: ; 0x02254704
	.byte 0x00, 0x02, 0x00, 0x04

	.global MOD20_02254708
MOD20_02254708: ; 0x02254708
	.byte 0x80, 0x02, 0x80, 0x04

	.global MOD20_0225470C
MOD20_0225470C: ; 0x0225470C
	.byte 0x01, 0x08, 0x0F, 0x04
