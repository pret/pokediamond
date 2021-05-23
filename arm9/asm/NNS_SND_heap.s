	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020C2774
FUN_020C2774: ; 0x020C2774
	stmdb sp!, {r4,lr}
	bl SND_GetCurrentCommandTag
	mov r4, r0
	mov r0, #0x1
	bl SND_FlushCommand
	mov r0, r4
	bl SND_WaitForCommandProc
	ldmia sp!, {r4,pc}

	; _end
	arm_func_start FUN_020C2794
FUN_020C2794: ; 0x020C2794
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, [r5, #0x0]
	mov r1, #0x14
	mov r2, #0x4
	bl FUN_020AE638
	movs r4, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	bl FUN_020C2818
	mov r1, r4
	add r0, r5, #0x4
	bl FUN_020ADBE8
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	; _end
	arm_func_start FUN_020C27DC
FUN_020C27DC: ; 0x020C27DC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	add r0, r5, #0x4
	mov r1, #0xc
	bl FUN_020ADC74
	mov r0, r5
	str r4, [r5, #0x0]
	bl FUN_020C2794
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	; InitHeapSection
	arm_func_start FUN_020C2818
FUN_020C2818: ; 0x020C2818
	ldr ip, _020C2824 ; =FUN_020ADC74
	mov r1, #0x0
	bx r12
	.balign 4
_020C2824: .word FUN_020ADC74

	; _end
	arm_func_start FUN_020C2828
FUN_020C2828: ; 0x020C2828
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r7, #0x0
	movs r9, r1
	mov r10, r0
	mov r6, r7
	bne _020C2850
	bl FUN_020C29C0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
_020C2850:
	ldrh r0, [r10, #0xc]
	cmp r9, r0
	bge _020C28D8
	mov r11, r7
	add r5, r10, #0x4
	mov r4, #0x1
_020C2868:
	mov r0, r5
	mov r1, r11
	bl FUN_020ADA84
	mov r1, r7
	mov r8, r0
	bl FUN_020ADA84
	movs r7, r0
	beq _020C28C0
_020C2888:
	ldr r12, [r7, #0xc]
	cmp r12, #0x0
	beq _020C28AC
	ldr r1, [r7, #0x8]
	ldr r2, [r7, #0x10]
	ldr r3, [r7, #0x14]
	add r0, r7, #0x20
	blx r12
	mov r6, r4
_020C28AC:
	mov r0, r8
	mov r1, r7
	bl FUN_020ADA84
	movs r7, r0
	bne _020C2888
_020C28C0:
	mov r0, r5
	mov r1, r8
	bl FUN_020ADAB0
	ldrh r0, [r10, #0xc]
	cmp r9, r0
	blt _020C2868
_020C28D8:
	ldr r0, [r10, #0x0]
	mov r1, r9
	bl FUN_020AE554
	cmp r6, #0x0
	beq _020C28F0
	bl FUN_020C2774
_020C28F0:
	ldrh r1, [r10, #0xc]
	ldr r0, [r10, #0x0]
	bl FUN_020AE5B0
	mov r0, r10
	bl FUN_020C2794
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}

	; _end
	arm_func_start FUN_020C290C
FUN_020C290C: ; 0x020C290C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldrh r1, [r4, #0xc]
	ldr r0, [r4, #0x0]
	bl FUN_020AE5B0
	cmp r0, #0x0
	mvneq r0, #0x0
	ldmeqia sp!, {r4,pc}
	mov r0, r4
	bl FUN_020C2794
	cmp r0, #0x0
	ldrneh r0, [r4, #0xc]
	subne r0, r0, #0x1
	ldmneia sp!, {r4,pc}
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl FUN_020AE554
	mvn r0, #0x0
	ldmia sp!, {r4,pc}

	; _end
	arm_func_start SDATi_AllocAndInitChunk
SDATi_AllocAndInitChunk: ; 0x020C2958
	stmdb sp!, {r4-r8,lr}
	mov r7, r1
	mov r8, r0
	add r0, r7, #0x1f
	bic r1, r0, #0x1f
	mov r6, r2
	ldr r0, [r8, #0x0]
	add r1, r1, #0x20
	mov r2, #0x20
	mov r5, r3
	bl FUN_020AE638 // some allocator?
	movs r4, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	add r0, r8, #0x4
	mov r1, #0x0
	bl FUN_020ADA84
	str r7, [r4, #0x8]
	str r6, [r4, #0xc]
	ldr r2, [sp, #0x18]
	str r5, [r4, #0x10]
	mov r1, r4
	str r2, [r4, #0x14]
	bl FUN_020ADBE8
	add r0, r4, #0x20
	ldmia sp!, {r4-r8,pc}

	; _end
	arm_func_start FUN_020C29C0
FUN_020C29C0: ; 0x020C29C0
	stmdb sp!, {r4-r10,lr}
	mov r8, r0
	mov r5, #0x0
	mov r1, r5
	add r0, r8, #0x4
	bl FUN_020ADA84
	movs r7, r0
	beq _020C2A58
	add r9, r8, #0x4
	mov r10, #0x1
	mov r4, r5
_020C29EC:
	mov r0, r7
	mov r1, r4
	bl FUN_020ADA84
	movs r6, r0
	beq _020C2A38
_020C2A00:
	ldr r12, [r6, #0xc]
	cmp r12, #0x0
	beq _020C2A24
	ldr r1, [r6, #0x8]
	ldr r2, [r6, #0x10]
	ldr r3, [r6, #0x14]
	add r0, r6, #0x20
	blx r12
	mov r5, r10
_020C2A24:
	mov r0, r7
	mov r1, r6
	bl FUN_020ADA84
	movs r6, r0
	bne _020C2A00
_020C2A38:
	mov r0, r9
	mov r1, r7
	bl FUN_020ADAB0
	mov r0, r9
	mov r1, r4
	bl FUN_020ADA84
	movs r7, r0
	bne _020C29EC
_020C2A58:
	ldr r0, [r8, #0x0]
	mov r1, #0x3
	bl FUN_020AE600
	cmp r5, #0x0
	beq _020C2A70
	bl FUN_020C2774
_020C2A70:
	mov r0, r8
	bl FUN_020C2794
	ldmia sp!, {r4-r10,pc}

	; _end
	arm_func_start FUN_020C2A7C
FUN_020C2A7C: ; 0x020C2A7C
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020C29C0
	ldr r0, [r4, #0x0]
	bl thunk_FUN_020adc8c_2
	ldmia sp!, {r4,pc}

	; _end
	arm_func_start FUN_020C2A94
FUN_020C2A94: ; 0x020C2A94
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	add r2, r0, #0x3
	add r0, r0, r1
	bic r5, r2, #0x3
	cmp r5, r0
	addhi sp, sp, #0x4
	movhi r0, #0x0
	ldmhiia sp!, {r4-r5,pc}
	sub r1, r0, r5
	cmp r1, #0x10
	addcc sp, sp, #0x4
	movcc r0, #0x0
	ldmccia sp!, {r4-r5,pc}
	add r0, r5, #0x10
	sub r1, r1, #0x10
	mov r2, #0x0
	bl FUN_020AE684
	movs r4, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	mov r0, r5
	mov r1, r4
	bl FUN_020C27DC
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, r5
	ldmneia sp!, {r4-r5,pc}
	mov r0, r4
	bl thunk_FUN_020adc8c_2
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

