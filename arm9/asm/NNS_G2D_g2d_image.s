	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNSi_G2dGetVramLocation
NNSi_G2dGetVramLocation: ; 0x020B10BC
	ldr r0, [r0, r1, lsl #0x2]
	bx lr
	arm_func_end NNSi_G2dGetVramLocation

	arm_func_start NNSi_G2dSetVramLocation
NNSi_G2dSetVramLocation: ; 0x020B10C4
	str r2, [r0, r1, lsl #0x2]
	bx lr
	arm_func_end NNSi_G2dSetVramLocation

	arm_func_start NNSi_G2dInitializeVRamLocation
NNSi_G2dInitializeVRamLocation: ; 0x020B10CC
	mov r2, #0x0
	mvn r1, #0x0
_020B10D4:
	str r1, [r0, r2, lsl #0x2]
	add r2, r2, #0x1
	cmp r2, #0x3
	blt _020B10D4
	bx lr
	arm_func_end NNSi_G2dInitializeVRamLocation

	arm_func_start NNS_G2dLoadPaletteEx
NNS_G2dLoadPaletteEx: ; 0x020B10E8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r10, r0
	ldr r0, [r10, #0x0]
	mov r9, r1
	cmp r0, #0x3
	ldr r0, [sp, #0x28]
	moveq r7, #0x20
	str r0, [sp, #0x28]
	ldrh r0, [r9, #0x0]
	movne r7, #0x200
	mov r11, r2
	mov r8, r3
	str r0, [sp, #0x0]
	mov r6, #0x0
	cmp r0, #0x0
	bls _020B1210
_020B112C:
	ldr r1, [r9, #0x4]
	mov r0, r6, lsl #0x1
	ldrh r2, [r1, r0]
	ldr r0, [r10, #0xc]
	ldr r1, [r10, #0x8]
	mla r5, r7, r2, r11
	mla r4, r7, r6, r0
	bl DC_FlushRange
	cmp r8, #0x0
	beq _020B11E0
	cmp r8, #0x1
	beq _020B1168
	cmp r8, #0x2
	beq _020B11A4
	b _020B11F8
_020B1168:
	ldr r0, [r10, #0x4]
	cmp r0, #0x0
	beq _020B1190
	bl GX_BeginLoadOBJExtPltt
	mov r0, r4
	mov r1, r5
	mov r2, r7
	bl GX_LoadOBJExtPltt
	bl GX_EndLoadOBJExtPltt
	b _020B11F8
_020B1190:
	mov r0, r4
	mov r1, r5
	mov r2, r7
	bl GX_LoadOBJPltt
	b _020B11F8
_020B11A4:
	ldr r0, [r10, #0x4]
	cmp r0, #0x0
	beq _020B11CC
	bl GXS_BeginLoadOBJExtPltt
	mov r0, r4
	mov r1, r5
	mov r2, r7
	bl GXS_LoadOBJExtPltt
	bl GXS_EndLoadOBJExtPltt
	b _020B11F8
_020B11CC:
	mov r0, r4
	mov r1, r5
	mov r2, r7
	bl GXS_LoadOBJPltt
	b _020B11F8
_020B11E0:
	bl GX_BeginLoadTexPltt
	mov r0, r4
	mov r1, r5
	mov r2, r7
	bl GX_LoadTexPltt
	bl GX_EndLoadTexPltt
_020B11F8:
	add r0, r6, #0x1
	mov r0, r0, lsl #0x10
	mov r6, r0, lsr #0x10
	ldr r0, [sp, #0x0]
	cmp r6, r0
	blo _020B112C
_020B1210:
	ldr r0, [sp, #0x28]
	ldr r2, [r10, #0x0]
	mov r1, r0
	str r2, [r1, #0x0]
	ldr r4, [r10, #0x4]
	mov r3, r0
	mov r1, r8
	mov r2, r11
	str r4, [r3, #0x4]
	bl NNS_G2dSetImagePaletteLocation
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	arm_func_end NNS_G2dLoadPaletteEx

	arm_func_start NNS_G2dLoadPalette
NNS_G2dLoadPalette: ; 0x020B1240
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	ldr r5, [r9, #0xc]
	ldr r4, [r9, #0x8]
	mov r8, r1
	mov r7, r2
	mov r0, r5
	mov r1, r4
	mov r6, r3
	bl DC_FlushRange
	cmp r7, #0x0
	beq _020B1300
	cmp r7, #0x1
	beq _020B1288
	cmp r7, #0x2
	beq _020B12C4
	b _020B1318
_020B1288:
	ldr r0, [r9, #0x4]
	cmp r0, #0x0
	beq _020B12B0
	bl GX_BeginLoadOBJExtPltt
	mov r0, r5
	mov r1, r8
	mov r2, r4
	bl GX_LoadOBJExtPltt
	bl GX_EndLoadOBJExtPltt
	b _020B1318
_020B12B0:
	mov r0, r5
	mov r1, r8
	mov r2, r4
	bl GX_LoadOBJPltt
	b _020B1318
_020B12C4:
	ldr r0, [r9, #0x4]
	cmp r0, #0x0
	beq _020B12EC
	bl GXS_BeginLoadOBJExtPltt
	mov r0, r5
	mov r1, r8
	mov r2, r4
	bl GXS_LoadOBJExtPltt
	bl GXS_EndLoadOBJExtPltt
	b _020B1318
_020B12EC:
	mov r0, r5
	mov r1, r8
	mov r2, r4
	bl GXS_LoadOBJPltt
	b _020B1318
_020B1300:
	bl GX_BeginLoadTexPltt
	mov r0, r5
	mov r1, r8
	mov r2, r4
	bl GX_LoadTexPltt
	bl GX_EndLoadTexPltt
_020B1318:
	ldr r1, [r9, #0x0]
	mov r0, r6
	str r1, [r6, #0x0]
	ldr r3, [r9, #0x4]
	mov r1, r7
	mov r2, r8
	str r3, [r6, #0x4]
	bl NNS_G2dSetImagePaletteLocation
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	arm_func_end NNS_G2dLoadPalette

	arm_func_start NNS_G2dLoadImageVramTransfer
NNS_G2dLoadImageVramTransfer: ; 0x020B1340
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	ldr r0, [r7, #0x14]
	ldr r1, [r7, #0x10]
	mov r5, r2
	mov r4, r3
	bl DC_FlushRange
	cmp r5, #0x0
	ldr r0, [r7, #0x8]
	beq _020B13B8
	cmp r5, #0x1
	beq _020B1384
	cmp r5, #0x2
	beq _020B13A0
	b _020B13B8
_020B1384:
	mov r3, #0x4000000
	ldr r2, [r3, #0x0]
	ldr r1, _020B1520 ; =0xFFCFFFEF
	and r1, r2, r1
	orr r0, r1, r0
	str r0, [r3, #0x0]
	b _020B13B8
_020B13A0:
	ldr r3, _020B1524 ; =0x04001000
	ldr r1, _020B1520 ; =0xFFCFFFEF
	ldr r2, [r3, #0x0]
	and r1, r2, r1
	orr r0, r1, r0
	str r0, [r3, #0x0]
_020B13B8:
	ldr r0, [r7, #0x8]
	cmp r0, #0x0
	bne _020B14D8
	ldrh r0, [r7, #0x2]
	cmp r0, #0x10
	bgt _020B1408
	cmp r0, #0x10
	bge _020B1434
	cmp r0, #0x8
	addls pc, pc, r0, lsl #0x2
	b _020B1444
	; Jump table
	b _020B1444 ; case 0
	b _020B1414 ; case 1
	b _020B141C ; case 2
	b _020B1444 ; case 3
	b _020B1424 ; case 4
	b _020B1444 ; case 5
	b _020B1444 ; case 6
	b _020B1444 ; case 7
	b _020B142C ; case 8
_020B1408:
	cmp r0, #0x20
	beq _020B143C
	b _020B1444
_020B1414:
	mov r0, #0x0
	b _020B1448
_020B141C:
	mov r0, #0x1
	b _020B1448
_020B1424:
	mov r0, #0x2
	b _020B1448
_020B142C:
	mov r0, #0x3
	b _020B1448
_020B1434:
	mov r0, #0x4
	b _020B1448
_020B143C:
	mov r0, #0x5
	b _020B1448
_020B1444:
	mov r0, #0x0
_020B1448:
	str r0, [r4, #0xc]
	ldrh r0, [r7, #0x0]
	cmp r0, #0x10
	bgt _020B1490
	cmp r0, #0x10
	bge _020B14BC
	cmp r0, #0x8
	addls pc, pc, r0, lsl #0x2
	b _020B14CC
	; Jump table
	b _020B14CC ; case 0
	b _020B149C ; case 1
	b _020B14A4 ; case 2
	b _020B14CC ; case 3
	b _020B14AC ; case 4
	b _020B14CC ; case 5
	b _020B14CC ; case 6
	b _020B14CC ; case 7
	b _020B14B4 ; case 8
_020B1490:
	cmp r0, #0x20
	beq _020B14C4
	b _020B14CC
_020B149C:
	mov r0, #0x0
	b _020B14D0
_020B14A4:
	mov r0, #0x1
	b _020B14D0
_020B14AC:
	mov r0, #0x2
	b _020B14D0
_020B14B4:
	mov r0, #0x3
	b _020B14D0
_020B14BC:
	mov r0, #0x4
	b _020B14D0
_020B14C4:
	mov r0, #0x5
	b _020B14D0
_020B14CC:
	mov r0, #0x0
_020B14D0:
	str r0, [r4, #0x10]
	b _020B14E8
_020B14D8:
	ldrh r0, [r7, #0x2]
	str r0, [r4, #0xc]
	ldrh r0, [r7, #0x0]
	str r0, [r4, #0x10]
_020B14E8:
	ldr r1, [r7, #0x4]
	mov r0, #0x0
	str r1, [r4, #0x14]
	str r0, [r4, #0x18]
	mov r0, #0x1
	str r0, [r4, #0x1c]
	ldr r3, [r7, #0x8]
	mov r0, r4
	mov r1, r5
	mov r2, r6
	str r3, [r4, #0x20]
	bl NNS_G2dSetImageLocation
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B1520: .word 0xFFCFFFEF
_020B1524: .word 0x04001000
	arm_func_end NNS_G2dLoadImageVramTransfer

	arm_func_start NNS_G2dLoadImage2DMapping
NNS_G2dLoadImage2DMapping: ; 0x020B1528
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	movs r5, r2
	mov r6, r1
	mov r4, r3
	ldr r0, [r7, #0x8]
	beq _020B1590
	cmp r5, #0x1
	beq _020B155C
	cmp r5, #0x2
	beq _020B1578
	b _020B1590
_020B155C:
	mov r3, #0x4000000
	ldr r2, [r3, #0x0]
	ldr r1, _020B1760 ; =0xFFCFFFEF
	and r1, r2, r1
	orr r0, r1, r0
	str r0, [r3, #0x0]
	b _020B1590
_020B1578:
	ldr r3, _020B1764 ; =0x04001000
	ldr r1, _020B1760 ; =0xFFCFFFEF
	ldr r2, [r3, #0x0]
	and r1, r2, r1
	orr r0, r1, r0
	str r0, [r3, #0x0]
_020B1590:
	ldr r0, [r7, #0x14]
	ldr r1, [r7, #0x10]
	bl DC_FlushRange
	cmp r5, #0x0
	beq _020B15B8
	cmp r5, #0x1
	beq _020B15D4
	cmp r5, #0x2
	beq _020B15E8
	b _020B15F8
_020B15B8:
	bl GX_BeginLoadTex
	ldr r0, [r7, #0x14]
	ldr r2, [r7, #0x10]
	mov r1, r6
	bl GX_LoadTex
	bl GX_EndLoadTex
	b _020B15F8
_020B15D4:
	ldr r0, [r7, #0x14]
	ldr r2, [r7, #0x10]
	mov r1, r6
	bl GX_LoadOBJ
	b _020B15F8
_020B15E8:
	ldr r0, [r7, #0x14]
	ldr r2, [r7, #0x10]
	mov r1, r6
	bl GXS_LoadOBJ
_020B15F8:
	ldr r0, [r7, #0x8]
	cmp r0, #0x0
	bne _020B1718
	ldrh r0, [r7, #0x2]
	cmp r0, #0x10
	bgt _020B1648
	cmp r0, #0x10
	bge _020B1674
	cmp r0, #0x8
	addls pc, pc, r0, lsl #0x2
	b _020B1684
	; Jump table
	b _020B1684 ; case 0
	b _020B1654 ; case 1
	b _020B165C ; case 2
	b _020B1684 ; case 3
	b _020B1664 ; case 4
	b _020B1684 ; case 5
	b _020B1684 ; case 6
	b _020B1684 ; case 7
	b _020B166C ; case 8
_020B1648:
	cmp r0, #0x20
	beq _020B167C
	b _020B1684
_020B1654:
	mov r0, #0x0
	b _020B1688
_020B165C:
	mov r0, #0x1
	b _020B1688
_020B1664:
	mov r0, #0x2
	b _020B1688
_020B166C:
	mov r0, #0x3
	b _020B1688
_020B1674:
	mov r0, #0x4
	b _020B1688
_020B167C:
	mov r0, #0x5
	b _020B1688
_020B1684:
	mov r0, #0x0
_020B1688:
	str r0, [r4, #0xc]
	ldrh r0, [r7, #0x0]
	cmp r0, #0x10
	bgt _020B16D0
	cmp r0, #0x10
	bge _020B16FC
	cmp r0, #0x8
	addls pc, pc, r0, lsl #0x2
	b _020B170C
	; Jump table
	b _020B170C ; case 0
	b _020B16DC ; case 1
	b _020B16E4 ; case 2
	b _020B170C ; case 3
	b _020B16EC ; case 4
	b _020B170C ; case 5
	b _020B170C ; case 6
	b _020B170C ; case 7
	b _020B16F4 ; case 8
_020B16D0:
	cmp r0, #0x20
	beq _020B1704
	b _020B170C
_020B16DC:
	mov r0, #0x0
	b _020B1710
_020B16E4:
	mov r0, #0x1
	b _020B1710
_020B16EC:
	mov r0, #0x2
	b _020B1710
_020B16F4:
	mov r0, #0x3
	b _020B1710
_020B16FC:
	mov r0, #0x4
	b _020B1710
_020B1704:
	mov r0, #0x5
	b _020B1710
_020B170C:
	mov r0, #0x0
_020B1710:
	str r0, [r4, #0x10]
	b _020B1728
_020B1718:
	ldrh r0, [r7, #0x2]
	str r0, [r4, #0xc]
	ldrh r0, [r7, #0x0]
	str r0, [r4, #0x10]
_020B1728:
	ldr r1, [r7, #0x4]
	mov r0, #0x0
	str r1, [r4, #0x14]
	str r0, [r4, #0x18]
	mov r0, #0x1
	str r0, [r4, #0x1c]
	ldr r3, [r7, #0x8]
	mov r0, r4
	mov r1, r5
	mov r2, r6
	str r3, [r4, #0x20]
	bl NNS_G2dSetImageLocation
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B1760: .word 0xFFCFFFEF
_020B1764: .word 0x04001000
	arm_func_end NNS_G2dLoadImage2DMapping

	arm_func_start NNS_G2dLoadImage1DMapping
NNS_G2dLoadImage1DMapping: ; 0x020B1768
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	movs r5, r2
	mov r6, r1
	mov r4, r3
	ldr r0, [r7, #0x8]
	beq _020B17D0
	cmp r5, #0x1
	beq _020B179C
	cmp r5, #0x2
	beq _020B17B8
	b _020B17D0
_020B179C:
	mov r3, #0x4000000
	ldr r2, [r3, #0x0]
	ldr r1, _020B19A0 ; =0xFFCFFFEF
	and r1, r2, r1
	orr r0, r1, r0
	str r0, [r3, #0x0]
	b _020B17D0
_020B17B8:
	ldr r3, _020B19A4 ; =0x04001000
	ldr r1, _020B19A0 ; =0xFFCFFFEF
	ldr r2, [r3, #0x0]
	and r1, r2, r1
	orr r0, r1, r0
	str r0, [r3, #0x0]
_020B17D0:
	ldr r0, [r7, #0x14]
	ldr r1, [r7, #0x10]
	bl DC_FlushRange
	cmp r5, #0x0
	beq _020B17F8
	cmp r5, #0x1
	beq _020B1814
	cmp r5, #0x2
	beq _020B1828
	b _020B1838
_020B17F8:
	bl GX_BeginLoadTex
	ldr r0, [r7, #0x14]
	ldr r2, [r7, #0x10]
	mov r1, r6
	bl GX_LoadTex
	bl GX_EndLoadTex
	b _020B1838
_020B1814:
	ldr r0, [r7, #0x14]
	ldr r2, [r7, #0x10]
	mov r1, r6
	bl GX_LoadOBJ
	b _020B1838
_020B1828:
	ldr r0, [r7, #0x14]
	ldr r2, [r7, #0x10]
	mov r1, r6
	bl GXS_LoadOBJ
_020B1838:
	ldr r0, [r7, #0x8]
	cmp r0, #0x0
	bne _020B1958
	ldrh r0, [r7, #0x2]
	cmp r0, #0x10
	bgt _020B1888
	cmp r0, #0x10
	bge _020B18B4
	cmp r0, #0x8
	addls pc, pc, r0, lsl #0x2
	b _020B18C4
	; Jump table
	b _020B18C4 ; case 0
	b _020B1894 ; case 1
	b _020B189C ; case 2
	b _020B18C4 ; case 3
	b _020B18A4 ; case 4
	b _020B18C4 ; case 5
	b _020B18C4 ; case 6
	b _020B18C4 ; case 7
	b _020B18AC ; case 8
_020B1888:
	cmp r0, #0x20
	beq _020B18BC
	b _020B18C4
_020B1894:
	mov r0, #0x0
	b _020B18C8
_020B189C:
	mov r0, #0x1
	b _020B18C8
_020B18A4:
	mov r0, #0x2
	b _020B18C8
_020B18AC:
	mov r0, #0x3
	b _020B18C8
_020B18B4:
	mov r0, #0x4
	b _020B18C8
_020B18BC:
	mov r0, #0x5
	b _020B18C8
_020B18C4:
	mov r0, #0x0
_020B18C8:
	str r0, [r4, #0xc]
	ldrh r0, [r7, #0x0]
	cmp r0, #0x10
	bgt _020B1910
	cmp r0, #0x10
	bge _020B193C
	cmp r0, #0x8
	addls pc, pc, r0, lsl #0x2
	b _020B194C
	; Jump table
	b _020B194C ; case 0
	b _020B191C ; case 1
	b _020B1924 ; case 2
	b _020B194C ; case 3
	b _020B192C ; case 4
	b _020B194C ; case 5
	b _020B194C ; case 6
	b _020B194C ; case 7
	b _020B1934 ; case 8
_020B1910:
	cmp r0, #0x20
	beq _020B1944
	b _020B194C
_020B191C:
	mov r0, #0x0
	b _020B1950
_020B1924:
	mov r0, #0x1
	b _020B1950
_020B192C:
	mov r0, #0x2
	b _020B1950
_020B1934:
	mov r0, #0x3
	b _020B1950
_020B193C:
	mov r0, #0x4
	b _020B1950
_020B1944:
	mov r0, #0x5
	b _020B1950
_020B194C:
	mov r0, #0x0
_020B1950:
	str r0, [r4, #0x10]
	b _020B1968
_020B1958:
	ldrh r0, [r7, #0x2]
	str r0, [r4, #0xc]
	ldrh r0, [r7, #0x0]
	str r0, [r4, #0x10]
_020B1968:
	ldr r1, [r7, #0x4]
	mov r0, #0x0
	str r1, [r4, #0x14]
	str r0, [r4, #0x18]
	mov r0, #0x1
	str r0, [r4, #0x1c]
	ldr r3, [r7, #0x8]
	mov r0, r4
	mov r1, r5
	mov r2, r6
	str r3, [r4, #0x20]
	bl NNS_G2dSetImageLocation
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B19A0: .word 0xFFCFFFEF
_020B19A4: .word 0x04001000
	arm_func_end NNS_G2dLoadImage1DMapping

	arm_func_start NNS_G2dIsImagePaletteReadyToUse
NNS_G2dIsImagePaletteReadyToUse: ; 0x020B19A8
	add r0, r0, r1, lsl #0x2
	ldr r1, [r0, #0x8]
	mvn r0, #0x0
	cmp r1, r0
	movne r0, #0x1
	moveq r0, #0x0
	bx lr
	arm_func_end NNS_G2dIsImagePaletteReadyToUse

	arm_func_start NNS_G2dGetImagePaletteLocation
NNS_G2dGetImagePaletteLocation: ; 0x020B19C4
	add r0, r0, r1, lsl #0x2
	ldr r0, [r0, #0x8]
	bx lr
	arm_func_end NNS_G2dGetImagePaletteLocation

	arm_func_start NNS_G2dSetImagePaletteLocation
NNS_G2dSetImagePaletteLocation: ; 0x020B19D0
	add r0, r0, r1, lsl #0x2
	str r2, [r0, #0x8]
	bx lr
	arm_func_end NNS_G2dSetImagePaletteLocation

	arm_func_start NNS_G2dInitImagePaletteProxy
NNS_G2dInitImagePaletteProxy: ; 0x020B19DC
	mov r3, #0x0
	mvn r2, #0x0
_020B19E4:
	add r1, r0, r3, lsl #0x2
	add r3, r3, #0x1
	str r2, [r1, #0x8]
	cmp r3, #0x3
	blt _020B19E4
	bx lr
	arm_func_end NNS_G2dInitImagePaletteProxy

	arm_func_start NNS_G2dIsImageReadyToUse
NNS_G2dIsImageReadyToUse: ; 0x020B19FC
	ldr r1, [r0, r1, lsl #0x2]
	mvn r0, #0x0
	cmp r1, r0
	movne r0, #0x1
	moveq r0, #0x0
	bx lr
	arm_func_end NNS_G2dIsImageReadyToUse

	arm_func_start NNS_G2dGetImageLocation
NNS_G2dGetImageLocation: ; 0x020B1A14
	ldr r0, [r0, r1, lsl #0x2]
	bx lr
	arm_func_end NNS_G2dGetImageLocation

	arm_func_start NNS_G2dSetImageLocation
NNS_G2dSetImageLocation: ; 0x020B1A1C
	str r2, [r0, r1, lsl #0x2]
	bx lr
	arm_func_end NNS_G2dSetImageLocation

	arm_func_start NNS_G2dInitImageProxy
NNS_G2dInitImageProxy: ; 0x020B1A24
	mov r2, #0x0
	mvn r1, #0x0
_020B1A2C:
	str r1, [r0, r2, lsl #0x2]
	add r2, r2, #0x1
	cmp r2, #0x3
	blt _020B1A2C
	bx lr
	arm_func_end NNS_G2dInitImageProxy
