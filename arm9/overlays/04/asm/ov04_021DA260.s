	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start ov04_021DA260
ov04_021DA260: ; 0x021DA260
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #4
	add r0, r0, #0x1000
	mov sb, r2
	cmp sb, #0
	ldr r8, [r0, #0x14]
	mov sl, r1
	mov r7, #0
	addle sp, sp, #4
	ldmleia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	mov r6, r7
	mov r5, r7
	mov fp, r7
	mov r4, r7
_021DA298:
	ldr r1, [sl, r7, lsl #3]
	cmp r1, #0
	beq _021DA2B4
	ldr r0, _021DA2EC ; =ov04_0220C110
	mov r2, r6
	blx r8
	str r5, [sl, r7, lsl #3]
_021DA2B4:
	add r0, sl, r7, lsl #3
	ldr r1, [r0, #4]
	cmp r1, #0
	beq _021DA2D8
	ldr r0, _021DA2F0 ; =ov04_0220C12C
	mov r2, fp
	blx r8
	add r0, sl, r7, lsl #3
	str r4, [r0, #4]
_021DA2D8:
	add r7, r7, #1
	cmp r7, sb
	blt _021DA298
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021DA2EC: .word ov04_0220C110
_021DA2F0: .word ov04_0220C12C
	arm_func_end ov04_021DA260

	arm_func_start ov04_021DA2F4
ov04_021DA2F4: ; 0x021DA2F4
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r2
	mov r5, r3
	bl ov04_021DA388
	movs r4, r0
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	bl strlen
	cmp r0, r5
	movge r0, #0
	ldmgeia sp!, {r4, r5, r6, pc}
	mov r0, r6
	mov r1, r4
	bl strcpy
	mov r0, #1
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end ov04_021DA2F4

	arm_func_start ov04_021DA334
ov04_021DA334: ; 0x021DA334
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r2
	mov r5, r3
	bl ov04_021DA388
	movs r4, r0
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	bl strlen
	mov r1, r0
	mov r0, r4
	mov r2, r6
	mov r3, r5
	bl ov04_021DD36C
	mvn r1, #0
	cmp r0, r1
	ldmeqia sp!, {r4, r5, r6, pc}
	cmp r0, r5
	ldmhsia sp!, {r4, r5, r6, pc}
	mov r1, #0
	strb r1, [r6, r0]
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end ov04_021DA334

	arm_func_start ov04_021DA388
ov04_021DA388: ; 0x021DA388
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	mov r5, r1
	mov r4, #0
_021DA398:
	add r0, r6, r4, lsl #3
	add r0, r0, #0x1000
	ldr r1, [r0, #0xa34]
	cmp r1, #0
	beq _021DA3D4
	mov r0, r5
	bl strcmp
	cmp r0, #0
	addeq r0, r6, r4, lsl #3
	addeq r0, r0, #0x1000
	ldreq r0, [r0, #0xa38]
	ldmeqia sp!, {r4, r5, r6, pc}
	add r4, r4, #1
	cmp r4, #0x20
	blt _021DA398
_021DA3D4:
	mov r0, #0
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end ov04_021DA388

	arm_func_start ov04_021DA3DC
ov04_021DA3DC: ; 0x021DA3DC
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x14
	ldr r2, _021DA668 ; =0x00001A34
	mov fp, r0
	add r0, fp, r2
	mov r6, r1
	mov r3, #0x20
	mov r1, #0
	mov r2, #0x100
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	str r1, [sp, #0x10]
	bl MI_CpuFill8
	add r0, fp, #0x1000
	ldr r5, [r0, #0xa04]
	ldr r1, _021DA66C ; =ov04_0220C148
	mov r0, r5
	bl strstr
	str r0, [sp]
	cmp r0, #0
	addeq sp, sp, #0x14
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	add r0, r0, #4
	bl strlen
	ldr r1, [sp]
	add r1, r1, #4
	add r0, r1, r0
	str r0, [sp, #4]
	ldr r1, _021DA670 ; =ov04_0220C150
	mov r0, r5
	bl strstr
	cmp r0, #0
	addeq sp, sp, #0x14
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	add r8, r0, #1
	ldrsb r7, [r8, #3]
	ldr r2, _021DA674 ; =ov04_0220C154
	mov r5, #0
	add r1, sp, #8
	mov r0, fp
	mov r3, r8
	strb r5, [r8, #3]
	bl ov04_021DA68C
	cmp r0, #1
	addne sp, sp, #0x14
	strneb r7, [r8, #3]
	movne r0, r5
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	strb r7, [r8, #3]
	cmp r6, #1
	beq _021DA4C8
	ldr r1, _021DA678 ; =ov04_0220C160
	mov r0, r8
	mov r2, #3
	bl strncmp
	cmp r0, #0
	beq _021DA4D4
_021DA4C8:
	add sp, sp, #0x14
	mov r0, #1
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021DA4D4:
	ldr r1, _021DA67C ; =ov04_0220C164
	add r0, r8, #4
	bl strstr
	cmp r0, #0
	addeq sp, sp, #0x14
	moveq r0, r5
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	add sb, r0, #2
	mov r6, r5
	b _021DA580
_021DA4FC:
	ldr r1, _021DA680 ; =ov04_0220C168
	mov r0, sb
	bl strstr
	movs r7, r0
	beq _021DA598
	ldrsb sl, [r7]
	add r8, r7, #2
	ldr r1, _021DA67C ; =ov04_0220C164
	mov r0, r8
	strb r6, [r7]
	bl strstr
	movs r5, r0
	streqb sl, [r7]
	beq _021DA598
	ldrsb r4, [r5]
	mov r0, fp
	mov r2, sb
	strb r6, [r5]
	add r1, sp, #8
	mov r3, r8
	bl ov04_021DA68C
	cmp r0, #1
	strneb sl, [r7]
	addne sp, sp, #0x14
	strneb r4, [r5]
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	mov r0, r8
	bl strlen
	strb sl, [r7]
	add r0, r8, r0
	strb r4, [r5]
	add sb, r0, #2
_021DA580:
	ldrsb r0, [sb]
	cmp r0, #0xd
	beq _021DA598
	ldrsb r0, [sb, #1]
	cmp r0, #0xa
	bne _021DA4FC
_021DA598:
	ldr r0, [sp]
	add r8, r0, #4
	ldr r0, [sp, #4]
	cmp r8, r0
	bhs _021DA65C
	mov r5, #0
_021DA5B0:
	ldr r1, _021DA684 ; =ov04_0220C16C
	mov r0, r8
	bl strstr
	movs sl, r0
	beq _021DA65C
	ldrsb r7, [sl]
	add sb, sl, #1
	ldr r1, _021DA688 ; =ov04_0220C170
	mov r0, sb
	strb r5, [sl]
	bl strstr
	movs r6, r0
	bne _021DA5F4
	ldr r1, _021DA67C ; =ov04_0220C164
	mov r0, sb
	bl strstr
	mov r6, r0
_021DA5F4:
	cmp r6, #0
	ldrnesb r4, [r6]
	mov r0, fp
	mov r2, r8
	add r1, sp, #8
	mov r3, sb
	strneb r5, [r6]
	bl ov04_021DA68C
	cmp r0, #1
	beq _021DA634
	strb r7, [sl]
	cmp r6, #0
	add sp, sp, #0x14
	strneb r4, [r6]
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021DA634:
	mov r0, sb
	bl strlen
	add r0, sb, r0
	add r8, r0, #1
	ldr r0, [sp, #4]
	strb r7, [sl]
	cmp r6, #0
	strneb r4, [r6]
	cmp r8, r0
	blo _021DA5B0
_021DA65C:
	mov r0, #1
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021DA668: .word 0x00001A34
_021DA66C: .word ov04_0220C148
_021DA670: .word ov04_0220C150
_021DA674: .word ov04_0220C154
_021DA678: .word ov04_0220C160
_021DA67C: .word ov04_0220C164
_021DA680: .word ov04_0220C168
_021DA684: .word ov04_0220C16C
_021DA688: .word ov04_0220C170
	arm_func_end ov04_021DA3DC

	arm_func_start ov04_021DA68C
ov04_021DA68C: ; 0x021DA68C
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	mov r8, r1
	ldr r4, [r8, #8]
	ldr r1, [r8, #4]
	add r0, r0, #0x1000
	cmp r4, r1
	ldr r5, [r0, #0x10]
	ldr r4, [r0, #0x14]
	mov r7, r2
	mov r6, r3
	movgt r0, #0
	ldmgtia sp!, {r4, r5, r6, r7, r8, pc}
	mov r0, r7
	bl strlen
	mov r1, r0
	ldr r0, _021DA7D8 ; =ov04_0220C174
	add r1, r1, #1
	blx r5
	ldr r2, [r8]
	ldr r1, [r8, #8]
	str r0, [r2, r1, lsl #3]
	ldr r3, [r8, #8]
	ldr r2, [r8]
	ldr r0, [r2, r3, lsl #3]
	cmp r0, #0
	beq _021DA770
	mov r0, r6
	bl strlen
	mov r1, r0
	ldr r0, _021DA7DC ; =ov04_0220C194
	add r1, r1, #1
	blx r5
	ldr r2, [r8]
	ldr r1, [r8, #8]
	add r1, r2, r1, lsl #3
	str r0, [r1, #4]
	ldr r3, [r8, #8]
	ldr r2, [r8]
	mov r1, r3, lsl #3
	add r0, r2, r3, lsl #3
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021DA770
	ldr r0, [r2, r1]
	mov r1, r7
	bl strcpy
	ldr r2, [r8]
	ldr r0, [r8, #8]
	mov r1, r6
	add r0, r2, r0, lsl #3
	ldr r0, [r0, #4]
	bl strcpy
	ldr r1, [r8, #8]
	mov r0, #1
	add r1, r1, #1
	str r1, [r8, #8]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_021DA770:
	ldr r1, [r2, r3, lsl #3]
	cmp r1, #0
	beq _021DA798
	ldr r0, _021DA7E0 ; =ov04_0220C1B4
	mov r2, #0
	blx r4
	ldr r1, [r8]
	ldr r0, [r8, #8]
	mov r2, #0
	str r2, [r1, r0, lsl #3]
_021DA798:
	ldr r1, [r8]
	ldr r0, [r8, #8]
	add r0, r1, r0, lsl #3
	ldr r1, [r0, #4]
	cmp r1, #0
	beq _021DA7D0
	ldr r0, _021DA7E4 ; =ov04_0220C1D0
	mov r2, #0
	blx r4
	ldr r1, [r8]
	ldr r0, [r8, #8]
	mov r2, #0
	add r0, r1, r0, lsl #3
	str r2, [r0, #4]
_021DA7D0:
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_021DA7D8: .word ov04_0220C174
_021DA7DC: .word ov04_0220C194
_021DA7E0: .word ov04_0220C1B4
_021DA7E4: .word ov04_0220C1D0
	arm_func_end ov04_021DA68C

	arm_func_start ov04_021DA7E8
ov04_021DA7E8: ; 0x021DA7E8
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r1
	mov r5, r0
	mov r0, r6
	mov r4, #0
	bl strlen
	cmp r0, #0x100
	movhs r0, r4
	ldmhsia sp!, {r4, r5, r6, pc}
	ldr r0, _021DA934 ; =0x00001024
	mov r1, r6
	add r0, r5, r0
	mov r2, #0x100
	bl strncpy
	mov r0, r6
	bl strlen
	ldr r1, _021DA934 ; =0x00001024
	mov r6, r0
	add r0, r5, r1
	bl strlen
	cmp r6, r0
	movne r0, r4
	ldmneia sp!, {r4, r5, r6, pc}
	ldr r0, _021DA934 ; =0x00001024
	ldr r1, _021DA938 ; =ov04_0220C1EC
	add r0, r5, r0
	bl strstr
	cmp r0, #0
	beq _021DA884
	ldr r0, _021DA93C ; =0x0000102B
	add r1, r5, #0x1000
	add r0, r5, r0
	str r0, [r1, #0x124]
	mov r0, r4
	str r0, [r1, #0x12c]
	add r0, r5, #0x1100
	mov r1, #0x50
	strh r1, [r0, #0x30]
	b _021DA8C0
_021DA884:
	ldr r0, _021DA934 ; =0x00001024
	ldr r1, _021DA940 ; =ov04_0220C1F4
	add r0, r5, r0
	bl strstr
	cmp r0, #0
	moveq r0, r4
	ldmeqia sp!, {r4, r5, r6, pc}
	add r1, r0, #8
	add r0, r5, #0x1000
	str r1, [r0, #0x124]
	mov r2, #1
	ldr r1, _021DA944 ; =0x000001BB
	str r2, [r0, #0x12c]
	add r0, r5, #0x1100
	strh r1, [r0, #0x30]
_021DA8C0:
	add r0, r5, #0x1000
	ldr r0, [r0, #0x124]
	ldr r1, _021DA948 ; =ov04_0220C200
	bl strstr
	cmp r0, #0
	movne r1, #0
	strneb r1, [r0]
	addne r4, r0, #1
	add r0, r5, #0x1000
	ldr r0, [r0, #0x124]
	ldr r1, _021DA94C ; =ov04_0220C204
	bl strstr
	cmp r0, #0
	addeq r0, r5, #0x1000
	moveq r1, #0
	streq r1, [r0, #0x128]
	movne r1, #0
	strneb r1, [r0]
	addne r1, r0, #1
	addne r0, r5, #0x1000
	strne r1, [r0, #0x128]
	cmp r4, #0
	beq _021DA92C
	mov r0, r4
	bl atol
	add r1, r5, #0x1100
	strh r0, [r1, #0x30]
_021DA92C:
	mov r0, #1
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021DA934: .word 0x00001024
_021DA938: .word ov04_0220C1EC
_021DA93C: .word 0x0000102B
_021DA940: .word ov04_0220C1F4
_021DA944: .word 0x000001BB
_021DA948: .word ov04_0220C200
_021DA94C: .word ov04_0220C204
	arm_func_end ov04_021DA7E8

	arm_func_start ov04_021DA950
ov04_021DA950: ; 0x021DA950
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	add r0, r0, #0x1000
	mov r5, r2
	cmp r5, #0
	ldr r7, [r0, #0x14]
	ldr r2, [r0, #0x10]
	mov r6, r1
	addle sp, sp, #4
	movle r0, #0
	ldmleia sp!, {r4, r5, r6, r7, pc}
	ldr r1, [r6, #0xc]
	ldr r0, _021DAA08 ; =ov04_0220C208
	add r1, r1, r5
	blx r2
	movs r4, r0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r0, [r6]
	ldr r2, [r6, #0xc]
	mov r1, r4
	bl MI_CpuCopy8
	ldr r1, [r6]
	ldr r0, _021DAA0C ; =ov04_0220C218
	mov r2, #0
	blx r7
	cmp r4, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r0, [r6]
	ldr r1, [r6, #4]
	sub r0, r4, r0
	add r0, r1, r0
	str r0, [r6, #4]
	ldr r1, [r6, #0xc]
	mov r0, #1
	add r1, r1, r5
	str r1, [r6, #0xc]
	str r4, [r6]
	ldr r1, [r6, #0xc]
	add r1, r4, r1
	str r1, [r6, #8]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021DAA08: .word ov04_0220C208
_021DAA0C: .word ov04_0220C218
	arm_func_end ov04_021DA950

	arm_func_start ov04_021DAA10
ov04_021DAA10: ; 0x021DAA10
	stmdb sp!, {r4, lr}
	mov r4, r1
	ldr r1, [r4]
	add r0, r0, #0x1000
	cmp r1, #0
	ldr r3, [r0, #0x14]
	beq _021DAA38
	ldr r0, _021DAA4C ; =ov04_0220C218
	mov r2, #0
	blx r3
_021DAA38:
	mov r0, r4
	mov r1, #0
	mov r2, #0x10
	bl MI_CpuFill8
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DAA4C: .word ov04_0220C218
	arm_func_end ov04_021DAA10

	arm_func_start ov04_021DAA50
ov04_021DAA50: ; 0x021DAA50
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	movs r5, r2
	add r0, r0, #0x1000
	ldr r2, [r0, #0x10]
	mov r4, r1
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, pc}
	ldr r0, _021DAABC ; =ov04_0220C22C
	mov r1, r5
	blx r2
	str r0, [r4]
	ldr r0, [r4]
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, pc}
	str r0, [r4, #4]
	str r5, [r4, #0xc]
	ldr r2, [r4]
	ldr r1, [r4, #0xc]
	mov r0, #1
	add r1, r2, r1
	str r1, [r4, #8]
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021DAABC: .word ov04_0220C22C
	arm_func_end ov04_021DAA50

	arm_func_start ov04_021DAAC0
ov04_021DAAC0: ; 0x021DAAC0
	ands r1, r0, #0x8000
	bicne r0, r0, #0x8000
	bx lr
	arm_func_end ov04_021DAAC0

	arm_func_start ov04_021DAACC
ov04_021DAACC: ; 0x021DAACC
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	ldr r2, _021DAB60 ; =0x000019F4
	mov r7, r0
	mov r6, r1
	mov r0, r6
	add r4, r7, r2
	bl strlen
	mov r5, r0
	ldr r0, [r4, #4]
	ldr r1, [r4, #8]
	sub r1, r1, r0
	cmp r5, r1
	ble _021DAB34
	sub r2, r5, r1
	mov r0, r7
	mov r1, r4
	add r2, r2, #1
	bl ov04_021DA950
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r0, [r4, #4]
	ldr r1, [r4, #8]
	sub r1, r1, r0
_021DAB34:
	ldr r2, _021DAB64 ; =ov04_0220C240
	mov r3, r6
	bl OS_SNPrintf
	cmp r0, r5
	ldreq r1, [r4, #4]
	movne r0, #1
	addeq r0, r1, r0
	streq r0, [r4, #4]
	moveq r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021DAB60: .word 0x000019F4
_021DAB64: .word ov04_0220C240
	arm_func_end ov04_021DAACC

	arm_func_start ov04_021DAB68
ov04_021DAB68: ; 0x021DAB68
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #4
	mov sl, r0
	add r0, sl, #0x1000
	ldr r4, [r0, #0x9f0]
	ldr r0, _021DAC8C ; =0x000019F4
	cmp r4, #0
	ldreq r6, _021DAC90 ; =ov04_0220C244
	mov r8, r2
	add r5, sl, #0x1000
	add r4, sl, r0
	ldr r0, [r5, #0x9f0]
	mov r7, r3
	add fp, r0, #1
	mov r2, #0
	mov sb, r1
	ldrne r6, _021DAC94 ; =ov04_0220C248
	mov r0, r8
	mov r1, r7
	mov r3, r2
	str fp, [r5, #0x9f0]
	bl ov04_021DD4FC
	mov r5, r0
	mov r0, r6
	bl strlen
	mov fp, r0
	mov r0, sb
	bl strlen
	sub r1, fp, #2
	add r2, r1, r0
	ldr r0, [r4, #4]
	ldr r1, [r4, #8]
	add r2, r5, r2
	sub r1, r1, r0
	cmp r2, r1
	ble _021DAC28
	sub r2, r2, r1
	mov r0, sl
	mov r1, r4
	add r2, r2, #1
	bl ov04_021DA950
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r0, [r4, #4]
	ldr r1, [r4, #8]
	sub r1, r1, r0
_021DAC28:
	mov r2, r6
	mov r3, sb
	bl OS_SNPrintf
	ldr r2, [r4, #4]
	mov r1, r7
	add r0, r2, r0
	str r0, [r4, #4]
	ldr r2, [r4, #4]
	ldr r3, [r4, #8]
	mov r0, r8
	sub r3, r3, r2
	sub r3, r3, #1
	bl ov04_021DD4FC
	cmp r0, #0
	addlt sp, sp, #4
	movlt r0, #1
	ldmltia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r1, [r4, #4]
	mov r0, #0
	add r1, r1, r5
	str r1, [r4, #4]
	ldr r1, [r4, #4]
	strb r0, [r1]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021DAC8C: .word 0x000019F4
_021DAC90: .word ov04_0220C244
_021DAC94: .word ov04_0220C248
	arm_func_end ov04_021DAB68

	arm_func_start ov04_021DAC98
ov04_021DAC98: ; 0x021DAC98
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	mov r6, r2
	mov r8, r0
	ldr r2, _021DAD7C ; =0x000019F4
	mov r0, r6
	mov r7, r1
	add r5, r8, r2
	bl strlen
	mov r4, r0
	ldr r0, _021DAD80 ; =ov04_0220C250
	bl strlen
	mov sb, r0
	mov r0, r7
	bl strlen
	sub r1, sb, #4
	add r0, r1, r0
	add r4, r4, r0
	ldr r2, [r5, #8]
	ldr r1, [r5, #4]
	add r0, r4, #1
	sub r1, r2, r1
	cmp r0, r1
	ble _021DAD1C
	sub r2, r4, r1
	mov r0, r8
	mov r1, r5
	add r2, r2, #1
	bl ov04_021DA950
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, pc}
_021DAD1C:
	ldr r0, [r5]
	ldr r1, _021DAD84 ; =ov04_0220C148
	bl strstr
	add r8, r0, #2
	ldrsb sb, [r0, #2]
	mov r0, r8
	bl strlen
	add r2, r0, #1
	add r0, r8, r4
	mov r1, r8
	bl memmove
	ldr r2, _021DAD80 ; =ov04_0220C250
	str r6, [sp]
	mov r3, r7
	mov r0, r8
	add r1, r4, #1
	bl OS_SNPrintf
	strb sb, [r8, r0]
	ldr r1, [r5, #4]
	mov r0, #0
	add r1, r1, r4
	str r1, [r5, #4]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	.align 2, 0
_021DAD7C: .word 0x000019F4
_021DAD80: .word ov04_0220C250
_021DAD84: .word ov04_0220C148
	arm_func_end ov04_021DAC98

	arm_func_start ov04_021DAD88
ov04_021DAD88: ; 0x021DAD88
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	mov r7, r0
	add r0, r7, #0x1000
	ldr r1, [r0, #8]
	ldr r0, _021DAE40 ; =0x000019F4
	cmp r1, #0
	ldreq r6, _021DAE44 ; =ov04_0220C25C
	add r5, r7, r0
	add r0, r7, #0x1000
	ldrne r6, _021DAE48 ; =ov04_0220C2B0
	ldr r0, [r0, #0x124]
	bl strlen
	mov r4, r0
	mov r0, r6
	bl strlen
	add r1, r7, #0x1000
	mov r8, r0
	ldr r0, [r1, #0x128]
	bl strlen
	sub r1, r8, #4
	add r0, r1, r0
	add r1, r4, r0
	ldr r0, _021DAE40 ; =0x000019F4
	add r2, r1, #0x400
	add r1, r7, r0
	mov r0, r7
	bl ov04_021DAA50
	cmp r0, #1
	addne sp, sp, #8
	movne r0, #1
	ldmneia sp!, {r4, r5, r6, r7, r8, pc}
	add r3, r7, #0x1000
	ldr r0, [r3, #0x124]
	mov r2, r6
	str r0, [sp]
	ldr r0, [r5, #4]
	ldr r1, [r5, #0xc]
	ldr r3, [r3, #0x128]
	bl OS_SNPrintf
	ldr r1, [r5, #4]
	add r0, r1, r0
	str r0, [r5, #4]
	mov r0, #0
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_021DAE40: .word 0x000019F4
_021DAE44: .word ov04_0220C25C
_021DAE48: .word ov04_0220C2B0
	arm_func_end ov04_021DAD88

	arm_func_start ov04_021DAE4C
ov04_021DAE4C: ; 0x021DAE4C
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	movs r5, r0
	add r1, r5, #0x1000
	ldr r4, [r1, #0x14]
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	ldr r1, _021DAF00 ; =0x00001A34
	mov r2, #0x20
	add r1, r5, r1
	bl ov04_021DA260
	ldr r1, _021DAF04 ; =0x00001A04
	mov r0, r5
	add r1, r5, r1
	bl ov04_021DAA10
	ldr r1, _021DAF08 ; =0x000019F4
	mov r0, r5
	add r1, r5, r1
	bl ov04_021DAA10
	add r0, r5, #0x1000
	ldr r1, [r0, #0x9c8]
	cmp r1, #0
	beq _021DAEC0
	ldr r0, _021DAF0C ; =ov04_0220C2D0
	mov r2, #0
	blx r4
	add r0, r5, #0x1000
	mov r1, #0
	str r1, [r0, #0x9c8]
_021DAEC0:
	add r0, r5, #0x1000
	ldr r1, [r0, #0x9cc]
	cmp r1, #0
	beq _021DAEE8
	ldr r0, _021DAF10 ; =ov04_0220C2E8
	mov r2, #0
	blx r4
	add r0, r5, #0x1000
	mov r1, #0
	str r1, [r0, #0x9cc]
_021DAEE8:
	ldr r2, _021DAF14 ; =0x00001C10
	mov r0, r5
	mov r1, #0
	bl MI_CpuFill8
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021DAF00: .word 0x00001A34
_021DAF04: .word 0x00001A04
_021DAF08: .word 0x000019F4
_021DAF0C: .word ov04_0220C2D0
_021DAF10: .word ov04_0220C2E8
_021DAF14: .word 0x00001C10
	arm_func_end ov04_021DAE4C

	arm_func_start ov04_021DAF18
ov04_021DAF18: ; 0x021DAF18
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0xc
	mov sl, r0
	add r0, sl, #0x1000
	ldr fp, [r0, #0x1c]
	ldr r0, _021DB224 ; =0x00001134
	ldr r1, _021DB228 ; =0x00001198
	ldr r2, _021DB22C ; =0x00001A04
	add r8, sl, r0
	cmp fp, #0
	mov r0, sl
	add r6, sl, r1
	add r7, sl, r2
	mov r5, #0
	ldrle fp, _021DB230 ; =0x0000EA60
	bl ov04_021DB35C
	mov r0, sl
	bl ov04_021DB348
	movs r4, r0
	addeq r0, sl, #0x1000
	moveq r1, #2
	streq r1, [r0, #0x20]
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	bl CPS_SocUse
	add r0, sl, #0x1000
	ldr r0, [r0, #0x12c]
	cmp r0, #1
	bne _021DAFC8
	mov r0, r6
	mov r1, #0
	mov r2, #0x830
	bl MI_CpuFill8
	ldr r1, _021DB234 ; =ov04_021DAAC0
	add r0, sl, #0x1000
	str r1, [r6, #0x810]
	ldr r1, [r0, #0x124]
	ldr r0, _021DB238 ; =ov04_0220C0E4
	str r1, [r6, #0x800]
	mov r1, #0xb
	str r6, [r8, #0xc]
	bl CPS_SetRootCa
	mov r0, #1
	bl CPS_SetSsl
_021DAFC8:
	add r0, sl, #0x1100
	ldrh r1, [r0, #0x30]
	mov r2, r4
	mov r0, #0
	bl CPS_SocPingMode
	bl CPS_TcpConnect
	cmp r0, #0
	beq _021DB004
	add r0, sl, #0x1000
	mov r1, #3
	str r1, [r0, #0x20]
	bl CPS_SocRelease
	bl CPS_SocUnRegister
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021DB004:
	add r0, sl, #0x1000
	ldr r4, [r0, #0x9f4]
	mov r0, r4
	bl strlen
	mov r1, r0
	mov r0, r4
	bl CPS_SocWrite
	cmp r0, #0
	str r0, [sp, #8]
	addle r0, sl, #0x1000
	movle r1, #5
	strle r1, [r0, #0x20]
	ble _021DB20C
	bl CPS_SocGetChar
	mov r0, sl
	bl ov04_021DB3B8
	cmp r0, #0
	addeq r0, sl, #0x1000
	moveq r1, #7
	streq r1, [r0, #0x20]
	beq _021DB20C
	ldr r0, [r7]
	str r0, [r7, #4]
	ldr r1, [r7]
	ldr r0, [r7, #0xc]
	add r0, r1, r0
	str r0, [r7, #8]
	bl OS_GetTick
	mov r6, r0
	mov r0, fp, asr #0x1f
	mov r8, r1
	str r0, [sp, #4]
	mov r4, #0
_021DB088:
	ldr r0, _021DB23C ; =CPSMyIp
	ldr r0, [r0]
	cmp r0, #0
	addeq r0, sl, #0x1000
	moveq r1, #5
	streq r1, [r0, #0x20]
	beq _021DB20C
	bl CPS_SocGetLength
	str r0, [sp, #8]
	cmp r0, #0
	blt _021DB1E8
	cmp r0, #0
	ble _021DB16C
	bl OS_GetTick
	mov r6, r0
	add r0, sp, #8
	mov r8, r1
	bl CPS_SocRead
	cmp r0, #0
	beq _021DB1E8
	ldr r2, [r7, #8]
	ldr r1, [r7, #4]
	sub r2, r2, #1
	ldr sb, [sp, #8]
	sub r2, r2, r1
	cmp sb, r2
	movge sb, r2
	mov r2, sb
	bl MI_CpuCopy8
	ldr r0, [r7, #4]
	cmp r5, #1
	add r0, r0, sb
	str r0, [r7, #4]
	ldr r0, [r7, #4]
	strb r4, [r0]
	bne _021DB144
	ldr r0, _021DB240 ; =0x00001A14
	add r0, sl, r0
	bl OS_LockMutex
	add r1, sl, #0x1000
	ldr r2, [r1, #0xa30]
	ldr r0, _021DB240 ; =0x00001A14
	add r2, r2, sb
	add r0, sl, r0
	str r2, [r1, #0xa30]
	bl OS_UnlockMutex
	b _021DB150
_021DB144:
	mov r0, sl
	bl ov04_021DB248
	mov r5, r0
_021DB150:
	ldr r0, [sp, #8]
	cmp r0, sb
	bls _021DB164
	bl CPS_SocConsume
	b _021DB1E8
_021DB164:
	mov r0, sb
	bl CPS_SocConsume
_021DB16C:
	add r0, sl, #0x1000
	ldr r1, [r0, #0xa2c]
	cmp r1, #0
	blt _021DB188
	ldr r0, [r0, #0xa30]
	cmp r0, r1
	bge _021DB1E8
_021DB188:
	bl OS_GetTick
	subs r2, r0, r6
	sbc r0, r1, r8
	mov r1, r0, lsl #6
	orr r1, r1, r2, lsr #26
	mov r0, r2, lsl #6
	ldr r2, _021DB244 ; =0x000082EA
	mov r3, r4
	bl _ll_udiv
	ldr r2, [sp, #4]
	cmp r1, r2
	cmpeq r0, fp
	addhi r0, sl, #0x1000
	movhi r1, #6
	strhi r1, [r0, #0x20]
	bhi _021DB20C
	mov r0, sl
	bl ov04_021DB3B8
	cmp r0, #0
	bne _021DB088
	add r0, sl, #0x1000
	mov r1, #7
	str r1, [r0, #0x20]
	b _021DB20C
_021DB1E8:
	bl CPS_TcpShutdown
	bl CPS_TcpClose
	bl CPS_SocRelease
	bl CPS_SocUnRegister
	add r0, sl, #0x1000
	mov r1, #8
	str r1, [r0, #0x20]
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021DB20C:
	bl CPS_TcpShutdown
	bl CPS_TcpClose
	bl CPS_SocRelease
	bl CPS_SocUnRegister
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021DB224: .word 0x00001134
_021DB228: .word 0x00001198
_021DB22C: .word 0x00001A04
_021DB230: .word 0x0000EA60
_021DB234: .word ov04_021DAAC0
_021DB238: .word ov04_0220C0E4
_021DB23C: .word CPSMyIp
_021DB240: .word 0x00001A14
_021DB244: .word 0x000082EA
	arm_func_end ov04_021DAF18

	arm_func_start ov04_021DB248
ov04_021DB248: ; 0x021DB248
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r5, r0
	add r0, r5, #0x1000
	ldr r6, [r0, #0xa04]
	ldr r2, _021DB334 ; =0x00001A04
	ldr r1, _021DB338 ; =ov04_0220C148
	mov r0, r6
	add r4, r5, r2
	bl strstr
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r1, _021DB338 ; =ov04_0220C148
	mov r0, r6
	bl strstr
	ldr r1, _021DB33C ; =0x00001A14
	add r6, r0, #4
	add r0, r5, r1
	bl OS_LockMutex
	ldr r0, [r4, #4]
	ldr r1, _021DB33C ; =0x00001A14
	sub r2, r0, r6
	add r0, r5, #0x1000
	str r2, [r0, #0xa30]
	add r0, r5, r1
	bl OS_UnlockMutex
	ldr r0, [r4]
	ldr r1, _021DB340 ; =ov04_0220C300
	bl strstr
	movs r4, r0
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r0, _021DB340 ; =ov04_0220C300
	bl strlen
	add r7, r4, r0
	ldr r1, _021DB344 ; =ov04_0220C164
	mov r0, r7
	bl strstr
	mov r4, r0
	ldr r0, _021DB33C ; =0x00001A14
	ldrsb r6, [r4]
	mov r1, #0
	add r0, r5, r0
	strb r1, [r4]
	bl OS_LockMutex
	mov r0, r7
	bl atol
	add r1, r5, #0x1000
	ldr r2, _021DB33C ; =0x00001A14
	str r0, [r1, #0xa2c]
	add r0, r5, r2
	bl OS_UnlockMutex
	strb r6, [r4]
	mov r0, #1
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021DB334: .word 0x00001A04
_021DB338: .word ov04_0220C148
_021DB33C: .word 0x00001A14
_021DB340: .word ov04_0220C300
_021DB344: .word ov04_0220C164
	arm_func_end ov04_021DB248

	arm_func_start ov04_021DB348
ov04_021DB348: ; 0x021DB348
	ldr ip, _021DB358 ; =CPS_Resolve
	add r0, r0, #0x1000
	ldr r0, [r0, #0x124]
	bx ip
	.align 2, 0
_021DB358: .word CPS_Resolve
	arm_func_end ov04_021DB348

	arm_func_start ov04_021DB35C
ov04_021DB35C: ; 0x021DB35C
	stmdb sp!, {r4, lr}
	ldr r1, _021DB3AC ; =0x00001134
	mov r4, r0
	add r0, r4, r1
	mov r1, #0
	mov r2, #0x64
	bl MI_CpuFill8
	ldr r0, _021DB3B0 ; =0x00000B68
	add r1, r4, #0x1000
	str r0, [r1, #0x170]
	ldr r3, [r1, #0x9c8]
	ldr r0, _021DB3AC ; =0x00001134
	ldr r2, _021DB3B4 ; =0x000005EA
	str r3, [r1, #0x174]
	str r2, [r1, #0x17c]
	ldr r2, [r1, #0x9cc]
	add r0, r4, r0
	str r2, [r1, #0x180]
	bl CPS_SocRegister
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DB3AC: .word 0x00001134
_021DB3B0: .word 0x00000B68
_021DB3B4: .word 0x000005EA
	arm_func_end ov04_021DB35C

	arm_func_start ov04_021DB3B8
ov04_021DB3B8: ; 0x021DB3B8
	stmdb sp!, {r4, lr}
	mov r4, r0
	add r0, r4, #0x1000
	ldr r0, [r0, #0x12c]
	cmp r0, #1
	bne _021DB3EC
	ldr r0, _021DB438 ; =0x000019D0
	add r0, r4, r0
	bl OS_GetLowEntropyData
	ldr r0, _021DB438 ; =0x000019D0
	mov r1, #0x20
	add r0, r4, r0
	bl CPS_SslAddRandomSeed
_021DB3EC:
	ldr r0, _021DB43C ; =0x00001BF4
	add r0, r4, r0
	bl OS_LockMutex
	add r0, r4, #0x1000
	ldr r0, [r0, #0xc0c]
	cmp r0, #1
	bne _021DB41C
	ldr r0, _021DB43C ; =0x00001BF4
	add r0, r4, r0
	bl OS_UnlockMutex
	mov r0, #0
	ldmia sp!, {r4, pc}
_021DB41C:
	ldr r0, _021DB43C ; =0x00001BF4
	add r0, r4, r0
	bl OS_UnlockMutex
	mov r0, #0xa
	bl OS_Sleep
	mov r0, #1
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DB438: .word 0x000019D0
_021DB43C: .word 0x00001BF4
	arm_func_end ov04_021DB3B8

	arm_func_start ov04_021DB440
ov04_021DB440: ; 0x021DB440
	stmdb sp!, {r4, lr}
	mov r4, r0
	add r0, r4, #0x1000
	ldrb r0, [r0]
	cmp r0, #0xff
	ldmneia sp!, {r4, pc}
	ldr r0, _021DB49C ; =0x00001BF4
	add r0, r4, r0
	bl OS_LockMutex
	ldr r0, _021DB49C ; =0x00001BF4
	add r1, r4, #0x1000
	mov r2, #1
	add r0, r4, r0
	str r2, [r1, #0xc0c]
	bl OS_UnlockMutex
	add r0, r4, #0x1000
	ldr r0, [r0, #0xba0]
	cmp r0, #0
	ldmeqia sp!, {r4, pc}
	ldr r0, _021DB4A0 ; =0x00001B34
	add r0, r4, r0
	bl OS_JoinThread
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DB49C: .word 0x00001BF4
_021DB4A0: .word 0x00001B34
	arm_func_end ov04_021DB440

	arm_func_start ov04_021DB4A4
ov04_021DB4A4: ; 0x021DB4A4
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0xc
	ldr r3, _021DB55C ; =0x00001BF4
	mov r5, r0
	add r2, r5, #0x1000
	mov ip, #0
	add r0, r5, r3
	mov r4, r1
	str ip, [r2, #0xc0c]
	bl OS_InitMutex
	ldr r0, _021DB560 ; =0x00001A14
	add r0, r5, r0
	bl OS_InitMutex
	add r0, r5, #0x1000
	ldr r0, [r0, #0x18]
	cmp r0, #1
	ldreq r0, _021DB564 ; =ov04_02210480
	moveq r1, #1
	streq r1, [r0]
	ldrne r0, _021DB564 ; =ov04_02210480
	movne r1, #0
	strne r1, [r0]
	add r0, r5, #0x1000
	ldr r0, [r0, #0xba0]
	cmp r0, #0
	beq _021DB524
	ldr r0, _021DB568 ; =0x00001B34
	add r0, r5, r0
	bl OS_IsThreadTerminated
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, pc}
_021DB524:
	ldr r0, _021DB568 ; =0x00001B34
	mov r1, #0x1000
	str r1, [sp]
	ldr r1, _021DB56C ; =ov04_021DAF18
	mov r2, r5
	add r0, r5, r0
	add r3, r5, #0x1000
	str r4, [sp, #4]
	bl OS_CreateThread
	ldr r0, _021DB568 ; =0x00001B34
	add r0, r5, r0
	bl OS_WakeupThreadDirect
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021DB55C: .word 0x00001BF4
_021DB560: .word 0x00001A14
_021DB564: .word ov04_02210480
_021DB568: .word 0x00001B34
_021DB56C: .word ov04_021DAF18
	arm_func_end ov04_021DB4A4

	arm_func_start ov04_021DB570
ov04_021DB570: ; 0x021DB570
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _021DB5F4 ; =ov04_0220C314
	ldr r2, _021DB5F8 ; =ov04_0220C320
	mov r4, r0
	bl ov04_021DAC98
	cmp r0, #0
	addne sp, sp, #8
	movne r0, #1
	ldmneia sp!, {r4, pc}
	add r0, r4, #0x1000
	ldr r0, [r0, #0x9f4]
	ldr r1, _021DB5FC ; =ov04_0220C148
	bl strstr
	add r0, r0, #4
	bl strlen
	movs r3, r0
	beq _021DB5E8
	ldr r2, _021DB600 ; =ov04_0220C328
	add r0, sp, #0
	mov r1, #7
	bl OS_SNPrintf
	ldr r1, _021DB604 ; =ov04_0220C32C
	add r2, sp, #0
	mov r0, r4
	bl ov04_021DAC98
	cmp r0, #0
	addne sp, sp, #8
	movne r0, #1
	ldmneia sp!, {r4, pc}
_021DB5E8:
	mov r0, #0
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DB5F4: .word ov04_0220C314
_021DB5F8: .word ov04_0220C320
_021DB5FC: .word ov04_0220C148
_021DB600: .word ov04_0220C328
_021DB604: .word ov04_0220C32C
	arm_func_end ov04_021DB570

	arm_func_start ov04_021DB608
ov04_021DB608: ; 0x021DB608
	stmdb sp!, {r4, r5, r6, lr}
	mov r5, r1
	ldr r2, _021DB714 ; =0x00001C10
	mov r6, r0
	ldr r4, [r5, #0xc]
	mov r1, #0
	bl MI_CpuFill8
	ldr r1, _021DB718 ; =0x00001004
	add r0, r6, #0x1000
	mvn r2, #0
	str r2, [r0, #0xa2c]
	mov lr, r5
	str r2, [r0, #0xa30]
	add ip, r6, r1
	ldmia lr!, {r0, r1, r2, r3}
	stmia ip!, {r0, r1, r2, r3}
	ldmia lr, {r0, r1, r2}
	stmia ip, {r0, r1, r2}
	ldr r0, _021DB71C ; =ov04_0220C33C
	ldr r1, _021DB720 ; =0x00000B68
	blx r4
	add r1, r6, #0x1000
	str r0, [r1, #0x9c8]
	ldr r0, [r1, #0x9c8]
	cmp r0, #0
	moveq r0, #1
	streq r0, [r1, #0x20]
	ldmeqia sp!, {r4, r5, r6, pc}
	ldr r0, _021DB724 ; =ov04_0220C354
	ldr r1, _021DB728 ; =0x000005EA
	blx r4
	add r2, r6, #0x1000
	str r0, [r2, #0x9cc]
	ldr r0, [r2, #0x9cc]
	cmp r0, #0
	moveq r0, #1
	streq r0, [r2, #0x20]
	ldmeqia sp!, {r4, r5, r6, pc}
	ldr r1, _021DB72C ; =0x00001A04
	ldr r2, [r2, #0xc]
	mov r0, r6
	add r1, r6, r1
	bl ov04_021DAA50
	cmp r0, #0
	addeq r1, r6, #0x1000
	moveq r0, #1
	streq r0, [r1, #0x20]
	ldmeqia sp!, {r4, r5, r6, pc}
	ldr r1, [r5]
	mov r0, r6
	bl ov04_021DA7E8
	cmp r0, #0
	addeq r1, r6, #0x1000
	moveq r0, #1
	streq r0, [r1, #0x20]
	ldmeqia sp!, {r4, r5, r6, pc}
	mov r0, r6
	bl ov04_021DAD88
	add r1, r6, #0x1000
	str r0, [r1, #0x20]
	ldr r0, [r1, #0x20]
	cmp r0, #0
	moveq r0, #0xff
	streqb r0, [r1]
	add r0, r6, #0x1000
	ldr r0, [r0, #0x20]
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021DB714: .word 0x00001C10
_021DB718: .word 0x00001004
_021DB71C: .word ov04_0220C33C
_021DB720: .word 0x00000B68
_021DB724: .word ov04_0220C354
_021DB728: .word 0x000005EA
_021DB72C: .word 0x00001A04
	arm_func_end ov04_021DB608

	.section .data

	.global ov04_0220C0E4 ; I really don't know about this table, I'm gonna assume it's extern for now because it's weird
ov04_0220C0E4: ; 0x0220C0E4
	.word ov04_0220CF18, ov04_0220CDEC, ov04_0220D0CC, ov04_0220D1A8
	.word ov04_0220C684, ov04_0220C920, ov04_0220CA08, ov04_0220C7D0
	.word ov04_0220CCD4, ov04_0220CBB4, ov04_0220CACC

	.global ov04_0220C110
ov04_0220C110: ; 0x0220C110
	.asciz "FREE array_entry[i].label"

	.balign 4, 0
	.global ov04_0220C12C
ov04_0220C12C: ; 0x0220C12C
	.asciz "FREE array_entry[i].value"

	.balign 4, 0
	.global ov04_0220C148
ov04_0220C148: ; 0x0220C148
	.asciz "\r\n\r\n"

	.balign 4, 0
	.global ov04_0220C150
ov04_0220C150: ; 0x0220C150
	.asciz " "

	.balign 4, 0
	.global ov04_0220C154
ov04_0220C154: ; 0x0220C154
	.asciz "httpresult"

	.balign 4, 0
	.global ov04_0220C160
ov04_0220C160: ; 0x0220C160
	.asciz "200"

	.balign 4, 0
	.global ov04_0220C164
ov04_0220C164: ; 0x0220C164
	.asciz "\r\n"

	.balign 4, 0
	.global ov04_0220C168
ov04_0220C168: ; 0x0220C168
	.asciz ": "

	.balign 4, 0
	.global ov04_0220C16C
ov04_0220C16C: ; 0x0220C16C
	.asciz "="

	.balign 4, 0
	.global ov04_0220C170
ov04_0220C170: ; 0x0220C170
	.asciz "&"

	.balign 4, 0
	.global ov04_0220C174
ov04_0220C174: ; 0x0220C174
	.asciz "ALLOC result->entry[i].label"

	.balign 4, 0
	.global ov04_0220C194
ov04_0220C194: ; 0x0220C194
	.asciz "ALLOC result->entry[i].value"

	.balign 4, 0
	.global ov04_0220C1B4
ov04_0220C1B4: ; 0x0220C1B4
	.asciz "FREE result->entry[i].label"

	.balign 4, 0
	.global ov04_0220C1D0
ov04_0220C1D0: ; 0x0220C1D0
	.asciz "FREE result->entry[i].value"

	.balign 4, 0
	.global ov04_0220C1EC
ov04_0220C1EC: ; 0x0220C1EC
	.asciz "http://"

	.balign 4, 0
	.global ov04_0220C1F4
ov04_0220C1F4: ; 0x0220C1F4
	.asciz "https://"

	.balign 4, 0
	.global ov04_0220C200
ov04_0220C200: ; 0x0220C200
	.asciz ":"

	.balign 4, 0
	.global ov04_0220C204
ov04_0220C204: ; 0x0220C204
	.asciz "/"

	.balign 4, 0
	.global ov04_0220C208
ov04_0220C208: ; 0x0220C208
	.asciz "ALLOC newptr"

	.balign 4, 0
	.global ov04_0220C218
ov04_0220C218: ; 0x0220C218
	.asciz "FREE buf->buffer"

	.balign 4, 0
	.global ov04_0220C22C
ov04_0220C22C: ; 0x0220C22C
	.asciz "ALLOC buf->buffer"

	.balign 4, 0
	.global ov04_0220C240
ov04_0220C240: ; 0x0220C240
	.asciz "%s"

	.balign 4, 0
	.global ov04_0220C244
ov04_0220C244: ; 0x0220C244
	.asciz "%s="

	.balign 4, 0
	.global ov04_0220C248
ov04_0220C248: ; 0x0220C248
	.asciz "&%s="

	.balign 4, 0
	.global ov04_0220C250
ov04_0220C250: ; 0x0220C250
	.asciz "%s: %s\r\n"

	.balign 4, 0
	.global ov04_0220C25C
ov04_0220C25C: ; 0x0220C25C
	.ascii "POST /%s HTTP/1.0\r\n"
	.ascii "Content-type: application/x-www-form-urlencoded\r\n"
	.asciz "Host: %s\r\n\r\n"

	.balign 4, 0
	.global ov04_0220C2B0
ov04_0220C2B0: ; 0x0220C2B0
	.ascii "GET /%s HTTP/1.0\r\n"
	.asciz "Host: %s\r\n\r\n"

	.balign 4, 0
	.global ov04_0220C2D0
ov04_0220C2D0: ; 0x0220C2D0
	.asciz "FREE http->lowrecvbuf"

	.balign 4, 0
	.global ov04_0220C2E8
ov04_0220C2E8: ; 0x0220C2E8
	.asciz "FREE http->lowsendbuf"

	.balign 4, 0
	.global ov04_0220C300
ov04_0220C300: ; 0x0220C300
	.asciz "Content-Length: "

	.balign 4, 0
	.global ov04_0220C314
ov04_0220C314: ; 0x0220C314
	.asciz "Connection"

	.balign 4, 0
	.global ov04_0220C320
ov04_0220C320: ; 0x0220C320
	.asciz "close"

	.balign 4, 0
	.global ov04_0220C328
ov04_0220C328: ; 0x0220C328
	.asciz "%d"

	.balign 4, 0
	.global ov04_0220C32C
ov04_0220C32C: ; 0x0220C32C
	.asciz "Content-Length"

	.balign 4, 0
	.global ov04_0220C33C
ov04_0220C33C: ; 0x0220C33C
	.asciz "ALLOC http->lowrecvbuf"

	.balign 4, 0
	.global ov04_0220C354
ov04_0220C354: ; 0x0220C354
	.asciz "ALLOC http->lowsendbuf"

	.balign 4, 0
