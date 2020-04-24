	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start GXS_LoadOBJ_2
GXS_LoadOBJ_2:
	ldr ip, _020AF038 ; =GXS_LoadOBJ
	bx r12
	.balign 4
_020AF038: .word GXS_LoadOBJ

	arm_func_start GXS_LoadOAM_2
GXS_LoadOAM_2: ; 0x020AF03C
	ldr ip, _020AF044 ; =GXS_LoadOAM
	bx r12
	.balign 4
_020AF044: .word GXS_LoadOAM

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

	arm_func_start GXS_LoadBGPltt_2
GXS_LoadBGPltt_2: ; 0x020AF0A0
	ldr ip, _020AF0A8 ; =GXS_LoadBGPltt
	bx r12
	.balign 4
_020AF0A8: .word GXS_LoadBGPltt

	arm_func_start GXS_LoadOBJPltt_2
GXS_LoadOBJPltt_2: ; 0x020AF0AC
	ldr ip, _020AF0B4 ; =GXS_LoadOBJPltt
	bx r12
	.balign 4
_020AF0B4: .word GXS_LoadOBJPltt

	arm_func_start GXS_LoadBG3Scr_3
GXS_LoadBG3Scr_3: ; 0x020AF0B8
	ldr ip, _020AF0C0 ; =GXS_LoadBG3Scr
	bx r12
	.balign 4
_020AF0C0: .word GXS_LoadBG3Scr

	arm_func_start GXS_LoadBG2Scr_3
GXS_LoadBG2Scr_3: ; 0x020AF0C4
	ldr ip, _020AF0CC ; =GXS_LoadBG2Scr
	bx r12
	.balign 4
_020AF0CC: .word GXS_LoadBG2Scr

	arm_func_start GXS_LoadBG3Scr_2
GXS_LoadBG3Scr_2: ; 0x020AF0D0
	ldr ip, _020AF0D8 ; =GXS_LoadBG3Scr
	bx r12
	.balign 4
_020AF0D8: .word GXS_LoadBG3Scr

	arm_func_start GXS_LoadBG2Scr_2
GXS_LoadBG2Scr_2: ; 0x020AF0DC
	ldr ip, _020AF0E4 ; =GXS_LoadBG2Scr
	bx r12
	.balign 4
_020AF0E4: .word GXS_LoadBG2Scr

	arm_func_start GXS_LoadBG1Scr_2
GXS_LoadBG1Scr_2: ; 0x020AF0E8
	ldr ip, _020AF0F0 ; =GXS_LoadBG1Scr
	bx r12
	.balign 4
_020AF0F0: .word GXS_LoadBG1Scr

	arm_func_start GXS_LoadBG0Scr_2
GXS_LoadBG0Scr_2: ; 0x020AF0F4
	ldr ip, _020AF0FC ; =GXS_LoadBG0Scr
	bx r12
	.balign 4
_020AF0FC: .word GXS_LoadBG0Scr

	arm_func_start GXS_LoadBG3Char_2
GXS_LoadBG3Char_2: ; 0x020AF100
	ldr ip, _020AF108 ; =GXS_LoadBG3Char
	bx r12
	.balign 4
_020AF108: .word GXS_LoadBG3Char

	arm_func_start GXS_LoadBG2Char_2
GXS_LoadBG2Char_2: ; 0x020AF10C
	ldr ip, _020AF114 ; =GXS_LoadBG2Char
	bx r12
	.balign 4
_020AF114: .word GXS_LoadBG2Char

	arm_func_start GXS_LoadBG1Char_2
GXS_LoadBG1Char_2: ; 0x020AF118
	ldr ip, _020AF120 ; =GXS_LoadBG1Char
	bx r12
	.balign 4
_020AF120: .word GXS_LoadBG1Char

	arm_func_start GXS_LoadBG0Char_2
GXS_LoadBG0Char_2: ; 0x020AF124
	ldr ip, _020AF12C ; =GXS_LoadBG0Char
	bx r12
	.balign 4
_020AF12C: .word GXS_LoadBG0Char

	arm_func_start GX_LoadOBJ_2
GX_LoadOBJ_2: ; 0x020AF130
	ldr ip, _020AF138 ; =GX_LoadOBJ
	bx r12
	.balign 4
_020AF138: .word GX_LoadOBJ

	arm_func_start GX_LoadOAM_2
GX_LoadOAM_2: ; 0x020AF13C
	ldr ip, _020AF144 ; =GX_LoadOAM
	bx r12
	.balign 4
_020AF144: .word GX_LoadOAM

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

	arm_func_start GX_LoadBGPltt_2
GX_LoadBGPltt_2: ; 0x020AF1A0
	ldr ip, _020AF1A8 ; =GX_LoadBGPltt
	bx r12
	.balign 4
_020AF1A8: .word GX_LoadBGPltt

	arm_func_start GX_LoadOBJPltt_2
GX_LoadOBJPltt_2: ; 0x020AF1AC
	ldr ip, _020AF1B4 ; =GX_LoadOBJPltt
	bx r12
	.balign 4
_020AF1B4: .word GX_LoadOBJPltt

	arm_func_start GX_LoadBG3Scr_3
GX_LoadBG3Scr_3: ; 0x020AF1B8
	ldr ip, _020AF1C0 ; =GX_LoadBG3Scr
	bx r12
	.balign 4
_020AF1C0: .word GX_LoadBG3Scr

	arm_func_start GX_LoadBG2Scr_3
GX_LoadBG2Scr_3: ; 0x020AF1C4
	ldr ip, _020AF1CC ; =GX_LoadBG2Scr
	bx r12
	.balign 4
_020AF1CC: .word GX_LoadBG2Scr

	arm_func_start GX_LoadBG3Scr_2
GX_LoadBG3Scr_2: ; 0x020AF1D0
	ldr ip, _020AF1D8 ; =GX_LoadBG3Scr
	bx r12
	.balign 4
_020AF1D8: .word GX_LoadBG3Scr

	arm_func_start GX_LoadBG2Scr_2
GX_LoadBG2Scr_2: ; 0x020AF1DC
	ldr ip, _020AF1E4 ; =GX_LoadBG2Scr
	bx r12
	.balign 4
_020AF1E4: .word GX_LoadBG2Scr

	arm_func_start GX_LoadBG1Scr_2
GX_LoadBG1Scr_2: ; 0x020AF1E8
	ldr ip, _020AF1F0 ; =GX_LoadBG1Scr
	bx r12
	.balign 4
_020AF1F0: .word GX_LoadBG1Scr

	arm_func_start GX_LoadBG0Scr_2
GX_LoadBG0Scr_2: ; 0x020AF1F4
	ldr ip, _020AF1FC ; =GX_LoadBG0Scr
	bx r12
	.balign 4
_020AF1FC: .word GX_LoadBG0Scr

	arm_func_start GX_LoadBG3Char_2
GX_LoadBG3Char_2: ; 0x020AF200
	ldr ip, _020AF208 ; =GX_LoadBG3Char
	bx r12
	.balign 4
_020AF208: .word GX_LoadBG3Char

	arm_func_start GX_LoadBG2Char_2
GX_LoadBG2Char_2: ; 0x020AF20C
	ldr ip, _020AF214 ; =GX_LoadBG2Char
	bx r12
	.balign 4
_020AF214: .word GX_LoadBG2Char

	arm_func_start GX_LoadBG1Char_2
GX_LoadBG1Char_2: ; 0x020AF218
	ldr ip, _020AF220 ; =GX_LoadBG1Char
	bx r12
	.balign 4
_020AF220: .word GX_LoadBG1Char

	arm_func_start GX_LoadBG0Char_2
GX_LoadBG0Char_2: ; 0x020AF224
	ldr ip, _020AF22C ; =GX_LoadBG0Char
	bx r12
	.balign 4
_020AF22C: .word GX_LoadBG0Char

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

	arm_func_start FUN_020AF2E0
FUN_020AF2E0: ; 0x020AF2E0
	ldrh r0, [r0, #0xc]
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	bx lr

	arm_func_start FUN_020AF2F4
FUN_020AF2F4: ; 0x020AF2F4
	ldrh r1, [r0, #0xc]
	ldr r0, [r0, #0x4]
	cmp r1, r0
	moveq r0, #0x1
	movne r0, #0x0
	bx lr

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

	arm_func_start FUN_020AF334
FUN_020AF334:
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x10
	add r3, r2, r3
	str r2, [sp, #0x0]
	str r2, [sp, #0x8]
	str r3, [sp, #0x4]
	str r3, [sp, #0xc]
	ldr r3, [r0, #0x0]
	add r12, sp, #0x0
	cmp r3, #0x0
	beq _020AF418
	mov r6, #0x0
_020AF364:
	ldr r5, [r3, #0x0]
	ldr r4, [r12, #0x4]
	ldr r2, [r3, #0xc]
	cmp r5, r4
	bne _020AF3B8
	ldr r4, [r3, #0x4]
	add r4, r5, r4
	str r4, [sp, #0xc]
	ldr r4, [r3, #0x8]
	cmp r4, #0x0
	strne r2, [r4, #0xc]
	streq r2, [r0, #0x0]
	cmp r2, #0x0
	strne r4, [r2, #0x8]
	ldr r4, [r1, #0x0]
	cmp r4, #0x0
	strne r3, [r4, #0x8]
	ldr r4, [r1, #0x0]
	str r4, [r3, #0xc]
	str r6, [r3, #0x8]
	str r3, [r1, #0x0]
_020AF3B8:
	ldr r5, [r3, #0x0]
	ldr lr, [r3, #0x4]
	ldr r4, [r12, #0x0]
	add lr, r5, lr
	cmp r4, lr
	bne _020AF40C
	str r5, [sp, #0x8]
	ldr r5, [r3, #0x8]
	ldr r4, [r3, #0xc]
	cmp r5, #0x0
	strne r4, [r5, #0xc]
	streq r4, [r0, #0x0]
	cmp r4, #0x0
	strne r5, [r4, #0x8]
	ldr lr, [r1, #0x0]
	cmp lr, #0x0
	strne r3, [lr, #0x8]
	ldr lr, [r1, #0x0]
	str lr, [r3, #0xc]
	str r6, [r3, #0x8]
	str r3, [r1, #0x0]
_020AF40C:
	mov r3, r2
	cmp r2, #0x0
	bne _020AF364
_020AF418:
	ldr r4, [r1, #0x0]
	cmp r4, #0x0
	ldrne r2, [r4, #0xc]
	strne r2, [r1, #0x0]
	cmp r4, #0x0
	addeq sp, sp, #0x10
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020AF438: ; 0x020AF438
	ldr r2, [sp, #0x8]
	mov r1, #0x0
	str r2, [r4, #0x0]
	ldr r3, [sp, #0xc]
	ldr r2, [sp, #0x8]
	sub r2, r3, r2
	str r2, [r4, #0x4]
	str r1, [r4, #0x8]
	str r1, [r4, #0xc]
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	strne r4, [r1, #0x8]
	ldr r2, [r0, #0x0]
	mov r1, #0x0
	str r2, [r4, #0xc]
	str r1, [r4, #0x8]
	str r4, [r0, #0x0]
	mov r0, #0x1
	add sp, sp, #0x10
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020AF488
FUN_020AF488:
	stmdb sp!, {r4-r10,lr}
	ldr r4, [r0, #0x0]
	ldr r9, [sp, #0x20]
	cmp r4, #0x0
	mov r5, #0x0
	beq _020AF4EC
	sub r12, r9, #0x1
	mvn lr, r12
_020AF4A8:
	cmp r9, #0x1
	ldrls r8, [r4, #0x0]
	movls r6, r5
	movls r7, r3
	bls _020AF4D0
	ldr r7, [r4, #0x0]
	add r6, r7, r12
	and r8, lr, r6
	sub r6, r8, r7
	add r7, r3, r6
_020AF4D0:
	ldr r10, [r4, #0x4]
	cmp r10, r7
	movcs r5, r4
	bhs _020AF4EC
	ldr r4, [r4, #0xc]
	cmp r4, #0x0
	bne _020AF4A8
_020AF4EC:
	cmp r5, #0x0
	beq _020AF5B8
	cmp r6, #0x0
	beq _020AF54C
	ldr r9, [r1, #0x0]
	cmp r9, #0x0
	ldrne r3, [r9, #0xc]
	strne r3, [r1, #0x0]
	cmp r9, #0x0
	beq _020AF5B8
	ldr r4, [r5, #0x0]
	mov r3, #0x0
	str r4, [r9, #0x0]
	str r6, [r9, #0x4]
	str r3, [r9, #0x8]
	str r3, [r9, #0xc]
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	strne r9, [r3, #0x8]
	ldr r4, [r0, #0x0]
	mov r3, #0x0
	str r4, [r9, #0xc]
	str r3, [r9, #0x8]
	str r9, [r0, #0x0]
_020AF54C:
	ldr r3, [r5, #0x4]
	sub r3, r3, r7
	str r3, [r5, #0x4]
	ldr r3, [r5, #0x0]
	add r3, r3, r7
	str r3, [r5, #0x0]
	ldr r3, [r5, #0x4]
	cmp r3, #0x0
	bne _020AF5AC
	ldr r4, [r5, #0x8]
	ldr r3, [r5, #0xc]
	cmp r4, #0x0
	strne r3, [r4, #0xc]
	streq r3, [r0, #0x0]
	cmp r3, #0x0
	strne r4, [r3, #0x8]
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	strne r5, [r0, #0x8]
	ldr r3, [r1, #0x0]
	mov r0, #0x0
	str r3, [r5, #0xc]
	str r0, [r5, #0x8]
	str r5, [r1, #0x0]
_020AF5AC:
	str r8, [r2, #0x0]
	mov r0, #0x1
	ldmia sp!, {r4-r10,pc}
_020AF5B8:
	mov r0, #0x0
	str r0, [r2, #0x0]
	ldmia sp!, {r4-r10,pc}

	arm_func_start FUN_020AF5C4
FUN_020AF5C4:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r12, #0x0
	str r12, [sp, #0x0]
	bl FUN_020AF488
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020AF5E0
FUN_020AF5E0: ; 0x020AF5E0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr lr, [r1, #0x0]
	cmp lr, #0x0
	ldrne r12, [lr, #0xc]
	strne r12, [r1, #0x0]
	cmp lr, #0x0
	beq _020AF640
	str r2, [lr, #0x0]
	str r3, [lr, #0x4]
	mov r1, #0x0
	str r1, [lr, #0x8]
	str r1, [lr, #0xc]
	ldr r1, [r0, #0x0]
	add sp, sp, #0x4
	cmp r1, #0x0
	strne lr, [r1, #0x8]
	ldr r2, [r0, #0x0]
	mov r1, #0x0
	str r2, [lr, #0xc]
	str r1, [lr, #0x8]
	str lr, [r0, #0x0]
	mov r0, #0x1
	ldmia sp!, {pc}
_020AF640:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020AF64C
FUN_020AF64C: ; 0x020AF64C
	stmdb sp!, {r4,lr}
	subs lr, r1, #0x1
	mov r2, #0x0
	beq _020AF684
	mov r4, r0
_020AF660:
	add r12, r2, #0x1
	add r2, r0, r2, lsl #0x4
	add r3, r0, r12, lsl #0x4
	str r3, [r2, #0xc]
	str r4, [r3, #0x8]
	mov r2, r12
	cmp r12, lr
	add r4, r4, #0x10
	blo _020AF660
_020AF684:
	mov r2, #0x0
	str r2, [r0, #0x8]
	add r1, r0, r1, lsl #0x4
	str r2, [r1, #-0x4]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020AF698
FUN_020AF698: ; 0x020AF698
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr

	arm_func_start FUN_020AF6A4
FUN_020AF6A4: ; 0x020AF6A4
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x30
	ldr r6, _020AF884 ; =0x020FF864
	add r5, sp, #0x0
	ldmia r6!, {r0-r3}
	mov r12, r5
	stmia r5!, {r0-r3}
	ldmia r6!, {r0-r3}
	stmia r5!, {r0-r3}
	ldr r4, _020AF888 ; =0x021CCD6C
	ldmia r6, {r0-r3}
	stmia r5, {r0-r3}
	ldr lr, [r4, #0x10]
	ldr r1, [r4, #0xc]
	add r0, lr, lr, lsr #0x1
	mov r4, lr, lsr #0x1
	sub r0, r1, r0
	mov r3, #0x0
_020AF6EC:
	cmp r3, #0x0
	beq _020AF6FC
	cmp r3, #0x2
	bne _020AF734
_020AF6FC:
	ldr r2, [r12, #0x0]
	cmp r2, #0x0
	beq _020AF734
	cmp lr, #0x0
	beq _020AF734
	ldr r1, [r12, #0x8]
	cmp r2, lr
	movhi r2, lr
	add r1, r1, r2
	str r1, [r12, #0x8]
	ldr r1, [r12, #0x0]
	sub lr, lr, r2
	sub r1, r1, r2
	str r1, [r12, #0x0]
_020AF734:
	add r3, r3, #0x1
	cmp r3, #0x4
	add r12, r12, #0xc
	blo _020AF6EC
	ldr r1, [sp, #0xc]
	add r5, sp, #0x0
	sub r1, r1, r4
	str r1, [sp, #0xc]
	mov r3, #0x0
_020AF758:
	ldr r2, [r5, #0x0]
	cmp r2, #0x0
	beq _020AF790
	cmp r0, #0x0
	beq _020AF790
	ldr r1, [r5, #0x4]
	cmp r2, r0
	movhi r2, r0
	add r1, r1, r2
	str r1, [r5, #0x4]
	ldr r1, [r5, #0x0]
	sub r0, r0, r2
	sub r1, r1, r2
	str r1, [r5, #0x0]
_020AF790:
	add r3, r3, #0x1
	cmp r3, #0x4
	add r5, r5, #0xc
	blo _020AF758
	ldr r0, _020AF888 ; =0x021CCD6C
	bl FUN_020AF698
	ldr r0, _020AF88C ; =0x021CCD70
	bl FUN_020AF698
	ldr r0, _020AF888 ; =0x021CCD6C
	ldr r1, [r0, #0x18]
	ldr r0, [r0, #0x14]
	mov r1, r1, lsr #0x4
	bl FUN_020AF64C
	ldr r3, [sp, #0x8]
	ldr r1, _020AF888 ; =0x021CCD6C
	cmp r3, #0x0
	str r0, [r1, #0x8]
	beq _020AF7E8
	ldr r0, _020AF88C ; =0x021CCD70
	ldr r1, _020AF890 ; =0x021CCD74
	mov r2, #0x0
	bl FUN_020AF5E0
_020AF7E8:
	ldr r3, [sp, #0x4]
	ldr r2, [sp, #0x8]
	cmp r3, #0x0
	beq _020AF804
	ldr r0, _020AF888 ; =0x021CCD6C
	ldr r1, _020AF890 ; =0x021CCD74
	bl FUN_020AF5E0
_020AF804:
	ldr r3, [sp, #0x20]
	cmp r3, #0x0
	beq _020AF820
	ldr r0, _020AF88C ; =0x021CCD70
	ldr r1, _020AF890 ; =0x021CCD74
	mov r2, #0x40000
	bl FUN_020AF5E0
_020AF820:
	ldr r3, [sp, #0x1c]
	ldr r0, [sp, #0x20]
	cmp r3, #0x0
	add r2, r0, #0x40000
	beq _020AF840
	ldr r0, _020AF888 ; =0x021CCD6C
	ldr r1, _020AF890 ; =0x021CCD74
	bl FUN_020AF5E0
_020AF840:
	ldr r3, [sp, #0x28]
	cmp r3, #0x0
	beq _020AF85C
	ldr r0, _020AF888 ; =0x021CCD6C
	ldr r1, _020AF890 ; =0x021CCD74
	mov r2, #0x60000
	bl FUN_020AF5E0
_020AF85C:
	ldr r3, [sp, #0x10]
	cmp r3, #0x0
	addeq sp, sp, #0x30
	ldmeqia sp!, {r4-r6,pc}
_020AF86C: ; 0x020AF86C
	ldr r0, _020AF888 ; =0x021CCD6C
	ldr r1, _020AF890 ; =0x021CCD74
	add r2, r4, #0x20000
	bl FUN_020AF5E0
	add sp, sp, #0x30
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020AF884: .word 0x020FF864
_020AF888: .word 0x021CCD6C
_020AF88C: .word 0x021CCD70
_020AF890: .word 0x021CCD74

	arm_func_start FUN_020AF894
FUN_020AF894: ; 0x020AF894
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020AF908 ; =0x7FFF0000
	ldr r1, _020AF90C ; =0x0000FFFF
	and r2, r0, r2
	and r3, r0, r1
	mov r1, r2, lsr #0x10
	and r0, r0, #0x80000000
	mov r2, r3, lsl #0x3
	movs r3, r1, lsl #0x4
	mov r0, r0, lsr #0x1f
	beq _020AF8FC
	cmp r0, #0x0
	beq _020AF8DC
	ldr r0, _020AF910 ; =0x021CCD70
	ldr r1, _020AF914 ; =0x021CCD74
	bl FUN_020AF334
	b _020AF8E8
_020AF8DC:
	ldr r0, _020AF918 ; =0x021CCD6C
	ldr r1, _020AF914 ; =0x021CCD74
	bl FUN_020AF334
_020AF8E8:
	cmp r0, #0x0
	movne r0, #0x0
	add sp, sp, #0x4
	moveq r0, #0x1
	ldmia sp!, {pc}
_020AF8FC:
	mov r0, #0x2
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AF908: .word 0x7FFF0000
_020AF90C: .word 0x0000FFFF
_020AF910: .word 0x021CCD70
_020AF914: .word 0x021CCD74
_020AF918: .word 0x021CCD6C

	arm_func_start FUN_020AF91C
FUN_020AF91C: ; 0x020AF91C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	moveq r5, #0x10
	addne r0, r0, #0xf
	bicne r5, r0, #0xf
	ldr r0, _020AF9B0 ; =0x0007FFF0
	mov r4, r1
	cmp r5, r0
	addcs sp, sp, #0x4
	movcs r0, #0x0
	ldmcsia sp!, {r4-r5,pc}
_020AF94C: ; 0x020AF94C
	cmp r4, #0x0
	beq _020AF96C
	ldr r0, _020AF9B4 ; =0x021CCD70
	ldr r1, _020AF9B8 ; =0x021CCD74
	add r2, sp, #0x0
	mov r3, r5
	bl FUN_020AF5C4
	b _020AF980
_020AF96C:
	ldr r0, _020AF9BC ; =0x021CCD6C
	ldr r1, _020AF9B8 ; =0x021CCD74
	add r2, sp, #0x0
	mov r3, r5
	bl FUN_020AF5C4
_020AF980:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
_020AF990: ; 0x020AF990
	ldr r1, [sp, #0x0]
	ldr r0, _020AF9C0 ; =0x0000FFFF
	mov r2, r5, lsr #0x4
	and r0, r0, r1, lsr #0x3
	orr r0, r0, r2, lsl #0x10
	orr r0, r0, r4, lsl #0x1f
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AF9B0: .word 0x0007FFF0
_020AF9B4: .word 0x021CCD70
_020AF9B8: .word 0x021CCD74
_020AF9BC: .word 0x021CCD6C
_020AF9C0: .word 0x0000FFFF

	arm_func_start FUN_020AF9C4
FUN_020AF9C4: ; 0x020AF9C4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr ip, _020AFA14 ; =0x021CCD6C
	str r0, [r12, #0xc]
	str r1, [r12, #0x10]
	str r2, [r12, #0x14]
	str r3, [r12, #0x18]
	bl FUN_020AF6A4
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r3, _020AFA18 ; =FUN_020AF91C
	ldr r1, _020AFA1C ; =0x021064B8
	ldr r2, _020AFA20 ; =FUN_020AF894
	ldr r0, _020AFA24 ; =0x021064BC
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AFA14: .word 0x021CCD6C
_020AFA18: .word FUN_020AF91C
_020AFA1C: .word 0x021064B8
_020AFA20: .word FUN_020AF894
_020AFA24: .word 0x021064BC

	arm_func_start FUN_020AFA28
FUN_020AFA28: ; 0x020AFA28
	mov r0, r0, lsl #0x4
	bx lr

	arm_func_start FUN_020AFA30
FUN_020AFA30:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020AFA78 ; =0x021CCD88
	ldr r1, [r0, #0x10]
	ldr r0, [r0, #0xc]
	mov r1, r1, lsr #0x4
	bl FUN_020AF64C
	ldr r1, _020AFA78 ; =0x021CCD88
	str r0, [r1, #0x4]
	mov r0, r1
	bl FUN_020AF698
	ldr r0, _020AFA78 ; =0x021CCD88
	ldr r1, _020AFA7C ; =0x021CCD8C
	ldr r3, [r0, #0x8]
	mov r2, #0x0
	bl FUN_020AF5E0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AFA78: .word 0x021CCD88
_020AFA7C: .word 0x021CCD8C

	arm_func_start FUN_020AFA80
FUN_020AFA80: ; 0x020AFA80
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r1, #0x10000
	rsb r2, r1, #0x0
	ldr r1, _020AFAC8 ; =0x0000FFFF
	and r2, r0, r2
	and r12, r0, r1
	mov r3, r2, lsr #0x10
	ldr r0, _020AFACC ; =0x021CCD88
	ldr r1, _020AFAD0 ; =0x021CCD8C
	mov r2, r12, lsl #0x3
	mov r3, r3, lsl #0x3
	bl FUN_020AF334
_020AFAB4: ; 0x020AFAB4
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AFAC8: .word 0x0000FFFF
_020AFACC: .word 0x021CCD88
_020AFAD0: .word 0x021CCD8C

	arm_func_start FUN_020AFAD4
FUN_020AFAD4: ; 0x020AFAD4
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	cmp r0, #0x0
	moveq r4, #0x8
	addne r0, r0, #0x7
	bicne r4, r0, #0x7
	ldr r0, _020AFB98 ; =0x0007FFF8
	cmp r4, r0
	addcs sp, sp, #0x8
	movcs r0, #0x0
	ldmcsia sp!, {r4,pc}
_020AFB00: ; 0x020AFB00
	cmp r1, #0x0
	beq _020AFB50
	mov r12, #0x8
	ldr r0, _020AFB9C ; =0x021CCD88
	ldr r1, _020AFBA0 ; =0x021CCD8C
	add r2, sp, #0x4
	mov r3, r4
	str r12, [sp, #0x0]
	bl FUN_020AF488
	ldr r2, [sp, #0x4]
	add r1, r2, r4
	cmp r1, #0x10000
	bls _020AFB6C
	ldr r0, _020AFB9C ; =0x021CCD88
	ldr r1, _020AFBA0 ; =0x021CCD8C
	mov r3, r4
	bl FUN_020AF334
	add sp, sp, #0x8
	mov r0, #0x0
	ldmia sp!, {r4,pc}
_020AFB50:
	ldr r0, _020AFB9C ; =0x021CCD88
	mov r12, #0x10
	ldr r1, _020AFBA0 ; =0x021CCD8C
	add r2, sp, #0x4
	mov r3, r4
	str r12, [sp, #0x0]
	bl FUN_020AF488
_020AFB6C:
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_020AFB7C: ; 0x020AFB7C
	ldr r1, [sp, #0x4]
	ldr r0, _020AFBA4 ; =0x0000FFFF
	mov r2, r4, lsr #0x3
	and r0, r0, r1, lsr #0x3
	orr r0, r0, r2, lsl #0x10
	add sp, sp, #0x8
	ldmia sp!, {r4,pc}
	.balign 4
_020AFB98: .word 0x0007FFF8
_020AFB9C: .word 0x021CCD88
_020AFBA0: .word 0x021CCD8C
_020AFBA4: .word 0x0000FFFF

	arm_func_start FUN_020AFBA8
FUN_020AFBA8: ; 0x020AFBA8
	stmdb sp!, {r4,lr}
	ldr ip, _020AFBE8 ; =0x021CCD88
	mov r4, r3
	str r0, [r12, #0x8]
	str r1, [r12, #0xc]
	str r2, [r12, #0x10]
	bl FUN_020AFA30
_020AFBC4: ; 0x020AFBC4
	cmp r4, #0x0
	ldmeqia sp!, {r4,pc}
_020AFBCC: ; 0x020AFBCC
	ldr r3, _020AFBEC ; =FUN_020AFAD4
	ldr r1, _020AFBF0 ; =0x021064C0
	ldr r2, _020AFBF4 ; =FUN_020AFA80
	ldr r0, _020AFBF8 ; =0x021064C4
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_020AFBE8: .word 0x021CCD88
_020AFBEC: .word FUN_020AFAD4
_020AFBF0: .word 0x021064C0
_020AFBF4: .word FUN_020AFA80
_020AFBF8: .word 0x021064C4

	arm_func_start FUN_020AFBFC
FUN_020AFBFC: ; 0x020AFBFC
	mov r0, r0, lsl #0x4
	bx lr

	arm_func_start FUN_020AFC04
FUN_020AFC04: ; 0x020AFC04
	ldrh r2, [r0, #0x0]
	cmp r2, r1
	ldrhi r0, [r0, #0x4]
	addhi r0, r0, r1, lsl #0x4
	movls r0, #0x0
	bx lr

	arm_func_start FUN_020AFC1C
FUN_020AFC1C: ; 0x020AFC1C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r1, [r0, #0x4]
	mov r6, #0x0
	add r1, r1, r0
	str r1, [r0, #0x4]
	ldr r1, [r0, #0x8]
	add r1, r1, r0
	str r1, [r0, #0x8]
	ldr r1, [r0, #0xc]
	add r1, r1, r0
	str r1, [r0, #0xc]
	ldrh r1, [r0, #0x0]
	ldr r4, [r0, #0x4]
	ldr lr, [r0, #0x8]
	cmp r1, #0x0
	ldr r12, [r0, #0xc]
	bls _020AFCCC
	mov r1, r6
_020AFC68:
	add r2, r4, r6, lsl #0x4
	ldr r5, [r2, #0xc]
	mov r3, r6, lsl #0x4
	add r5, lr, r5
	str r5, [r2, #0xc]
	ldrh r7, [r4, r3]
	mov r5, r1
	cmp r7, #0x0
	bls _020AFCB4
_020AFC8C:
	ldr r9, [r2, #0xc]
	add r7, r5, #0x1
	ldr r8, [r9, r5, lsl #0x3]
	mov r7, r7, lsl #0x10
	add r8, r12, r8
	str r8, [r9, r5, lsl #0x3]
	ldrh r8, [r4, r3]
	mov r5, r7, lsr #0x10
	cmp r5, r8
	blo _020AFC8C
_020AFCB4:
	add r2, r6, #0x1
	mov r2, r2, lsl #0x10
	ldrh r3, [r0, #0x0]
	mov r6, r2, lsr #0x10
	cmp r6, r3
	blo _020AFC68
_020AFCCC:
	ldr r1, [r0, #0x14]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r9,pc}
_020AFCDC: ; 0x020AFCDC
	add r1, r1, r0
	str r1, [r0, #0x14]
	ldr r1, [r0, #0x14]
	mov r12, #0x0
	add r2, r1, #0x8
	ldr r0, [r2, #0x4]
	add r0, r0, r2
	str r0, [r2, #0x4]
	ldrh r0, [r1, #0x8]
	cmp r0, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r9,pc}
_020AFD0C: ; 0x020AFD0C
	mov r0, r12
	mov r6, r12
_020AFD14:
	ldr r5, [r2, #0x4]
	mov r3, r6
	add r1, r5, r0
	ldr r4, [r1, #0x4]
	add r4, r4, r2
	str r4, [r1, #0x4]
	ldr r4, [r1, #0x8]
	add r4, r4, r2
	str r4, [r1, #0x8]
	ldrh r4, [r5, r0]
	cmp r4, #0x0
	bls _020AFD6C
	mov r7, r6
_020AFD48:
	ldr r5, [r1, #0x8]
	add r3, r3, #0x1
	ldr r4, [r5, r7]
	add r4, r4, r2
	str r4, [r5, r7]
	ldrh r4, [r1, #0x0]
	add r7, r7, #0x4
	cmp r3, r4
	blo _020AFD48
_020AFD6C:
	ldrh r1, [r2, #0x0]
	add r12, r12, #0x1
	add r0, r0, #0xc
	cmp r12, r1
	blo _020AFD14
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}

	arm_func_start thunk_FUN_020afda0
thunk_FUN_020afda0: ; 0x020AFD88
	ldr ip, _020AFD90 ; =FUN_020AFDA0
	bx r12
	.balign 4
_020AFD90: .word FUN_020AFDA0

	arm_func_start thunk_FUN_020afda0_2
thunk_FUN_020afda0_2: ; 0x020AFD94
	ldr ip, _020AFD9C ; =FUN_020AFDA0
	bx r12
	.balign 4
_020AFD9C: .word FUN_020AFDA0

	arm_func_start FUN_020AFDA0
FUN_020AFDA0: ; 0x020AFDA0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldr r1, _020AFDE4 ; =0x41424E4B
	bl FUN_020B01F8
	movs r4, r0
	moveq r0, #0x0
	addeq sp, sp, #0x4
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r5,pc}
_020AFDC8: ; 0x020AFDC8
	add r0, r4, #0x8
	bl FUN_020AFC1C
	add r0, r4, #0x8
	str r0, [r5, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AFDE4: .word 0x41424E4B

	arm_func_start FUN_020AFDE8
FUN_020AFDE8: ; 0x020AFDE8
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	ldr r1, [r5, #0x4]
	add r1, r1, r5
	str r1, [r5, #0x4]
	bl FUN_020AFF10
	ldrh r1, [r5, #0x0]
	mov r4, r0
	mov r6, #0x0
	cmp r1, #0x0
	bls _020AFE44
_020AFE14:
	mov r0, r5
	mov r1, r6
	bl FUN_020AFE8C
	ldr r2, [r0, #0x4]
	add r1, r6, #0x1
	add r2, r2, r4
	str r2, [r0, #0x4]
	mov r0, r1, lsl #0x10
	ldrh r1, [r5, #0x0]
	mov r6, r0, lsr #0x10
	cmp r6, r1
	blo _020AFE14
_020AFE44:
	ldr r0, [r5, #0xc]
	cmp r0, #0x0
	beq _020AFE6C
	add r0, r0, r5
	str r0, [r5, #0xc]
	ldr r1, [r5, #0xc]
	ldr r0, [r1, #0x4]
	add r0, r0, r1
	str r0, [r1, #0x4]
	str r1, [r5, #0xc]
_020AFE6C:
	ldr r0, [r5, #0x14]
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020AFE78: ; 0x020AFE78
	add r0, r0, r5
	str r0, [r5, #0x14]
	ldr r0, [r5, #0x14]
	bl FUN_020AFF00
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020AFE8C
FUN_020AFE8C: ; 0x020AFE8C
	ldrh r2, [r0, #0x0]
	cmp r1, r2
	movcs r0, #0x0
	bxcs lr
	ldrh r2, [r0, #0x2]
	ands r2, r2, #0x1
	ldrne r0, [r0, #0x4]
	addne r0, r0, r1, lsl #0x4
	ldreq r0, [r0, #0x4]
	addeq r0, r0, r1, lsl #0x3
	bx lr

	arm_func_start FUN_020AFEB8
FUN_020AFEB8: ; 0x020AFEB8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldr r1, _020AFEFC ; =0x4345424B
	bl FUN_020B01F8
	movs r4, r0
	moveq r0, #0x0
	addeq sp, sp, #0x4
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r5,pc}
_020AFEE0: ; 0x020AFEE0
	add r0, r4, #0x8
	bl FUN_020AFDE8
	add r0, r4, #0x8
	str r0, [r5, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AFEFC: .word 0x4345424B

	arm_func_start FUN_020AFF00
FUN_020AFF00: ; 0x020AFF00
	ldr ip, _020AFF0C ; =FUN_020B01B0
	add r0, r0, #0x8
	bx r12
	.balign 4
_020AFF0C: .word FUN_020B01B0

	arm_func_start FUN_020AFF10
FUN_020AFF10: ; 0x020AFF10
	ldrh r1, [r0, #0x2]
	ands r1, r1, #0x1
	ldrneh r1, [r0, #0x0]
	ldrne r0, [r0, #0x4]
	addne r0, r0, r1, lsl #0x4
	ldreqh r1, [r0, #0x0]
	ldreq r0, [r0, #0x4]
	addeq r0, r0, r1, lsl #0x3
	bx lr

	arm_func_start FUN_020AFF34
FUN_020AFF34: ; 0x020AFF34
	ldrh r2, [r0, #0x0]
	cmp r1, r2
	ldrcc r0, [r0, #0x4]
	addcc r0, r0, r1, lsl #0x3
	movcs r0, #0x0
	bx lr

	arm_func_start FUN_020AFF4C
FUN_020AFF4C: ; 0x020AFF4C
	stmdb sp!, {r4,lr}
	ldr r1, [r0, #0x4]
	mov r4, #0x0
	add r1, r1, r0
	str r1, [r0, #0x4]
	ldr r1, [r0, #0x8]
	add r1, r1, r0
	str r1, [r0, #0x8]
	ldrh r1, [r0, #0x0]
	ldr lr, [r0, #0x4]
	cmp r1, #0x0
	bls _020AFFA8
_020AFF7C:
	add r3, lr, r4, lsl #0x3
	ldr r12, [r0, #0x8]
	ldr r2, [r3, #0x4]
	add r1, r4, #0x1
	add r2, r12, r2
	str r2, [r3, #0x4]
	mov r1, r1, lsl #0x10
	ldrh r2, [r0, #0x0]
	mov r4, r1, lsr #0x10
	cmp r4, r2
	blo _020AFF7C
_020AFFA8:
	ldr r1, [r0, #0x10]
	cmp r1, #0x0
	ldmeqia sp!, {r4,pc}
_020AFFB4: ; 0x020AFFB4
	add r1, r1, r0
	str r1, [r0, #0x10]
	ldr r0, [r0, #0x10]
	bl FUN_020AFFC8
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020AFFC8
FUN_020AFFC8: ; 0x020AFFC8
	ldr ip, _020AFFD4 ; =FUN_020B01B0
	add r0, r0, #0x8
	bx r12
	.balign 4
_020AFFD4: .word FUN_020B01B0

	arm_func_start FUN_020AFFD8
FUN_020AFFD8: ; 0x020AFFD8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldr r1, _020B001C ; =0x4D43424B
	bl FUN_020B01F8
	movs r4, r0
	moveq r0, #0x0
	addeq sp, sp, #0x4
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r5,pc}
_020B0000: ; 0x020B0000
	add r0, r4, #0x8
	bl FUN_020AFF4C
	add r0, r4, #0x8
	str r0, [r5, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B001C: .word 0x4D43424B

	arm_func_start FUN_020B0020
FUN_020B0020: ; 0x020B0020
	ldr r1, [r0, #0x14]
	add r1, r1, r0
	str r1, [r0, #0x14]
	bx lr

	arm_func_start FUN_020B0030
FUN_020B0030: ; 0x020B0030
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldr r1, _020B0074 ; =0x43484152
	bl FUN_020B01F8
	movs r4, r0
	moveq r0, #0x0
	addeq sp, sp, #0x4
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r5,pc}
_020B0058: ; 0x020B0058
	add r0, r4, #0x8
	bl FUN_020B0020
	add r0, r4, #0x8
	str r0, [r5, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B0074: .word 0x43484152

	arm_func_start FUN_020B0078
FUN_020B0078: ; 0x020B0078
	ldr r1, [r0, #0x14]
	add r1, r1, r0
	str r1, [r0, #0x14]
	bx lr

	arm_func_start FUN_020B0088
FUN_020B0088: ; 0x020B0088
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldr r1, _020B00CC ; =0x43484152
	bl FUN_020B01F8
	movs r4, r0
	moveq r0, #0x0
	addeq sp, sp, #0x4
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r5,pc}
_020B00B0: ; 0x020B00B0
	add r0, r4, #0x8
	bl FUN_020B0078
	add r0, r4, #0x8
	str r0, [r5, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B00CC: .word 0x43484152

	arm_func_start FUN_020B00D0
FUN_020B00D0: ; 0x020B00D0
	ldr r1, [r0, #0xc]
	add r1, r1, r0
	str r1, [r0, #0xc]
	bx lr

	arm_func_start FUN_020B00E0
FUN_020B00E0: ; 0x020B00E0
	ldr r1, [r0, #0x4]
	add r1, r1, r0
	str r1, [r0, #0x4]
	bx lr

	arm_func_start FUN_020B00F0
FUN_020B00F0: ; 0x020B00F0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldr r1, _020B0134 ; =0x50434D50
	bl FUN_020B01F8
	movs r4, r0
	moveq r0, #0x0
	addeq sp, sp, #0x4
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r5,pc}
_020B0118: ; 0x020B0118
	add r0, r4, #0x8
	bl FUN_020B00E0
	add r0, r4, #0x8
	str r0, [r5, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B0134: .word 0x50434D50

	arm_func_start FUN_020B0138
FUN_020B0138: ; 0x020B0138
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldr r1, _020B017C ; =0x504C5454
	bl FUN_020B01F8
	movs r4, r0
	moveq r0, #0x0
	addeq sp, sp, #0x4
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r5,pc}
_020B0160: ; 0x020B0160
	add r0, r4, #0x8
	bl FUN_020B00D0
	add r0, r4, #0x8
	str r0, [r5, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B017C: .word 0x504C5454

	arm_func_start FUN_020B0180
FUN_020B0180: ; 0x020B0180
	stmdb sp!, {r4,lr}
	mov r4, r1
	ldr r1, _020B01AC ; =0x5343524E
	bl FUN_020B01F8
_020B0190: ; 0x020B0190
	cmp r0, #0x0
	addne r0, r0, #0x8
	strne r0, [r4, #0x0]
	movne r0, #0x1
	moveq r0, #0x0
	streq r0, [r4, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_020B01AC: .word 0x5343524E

	arm_func_start FUN_020B01B0
FUN_020B01B0: ; 0x020B01B0
	ldr r1, [r0, #0x4]
	mov r12, #0x0
	add r1, r1, r0
	str r1, [r0, #0x4]
	ldrh r1, [r0, #0x0]
	cmp r1, #0x0
	bxls lr
_020B01CC:
	ldr r3, [r0, #0x4]
	add r1, r12, #0x1
	ldr r2, [r3, r12, lsl #0x2]
	mov r1, r1, lsl #0x10
	add r2, r0, r2
	str r2, [r3, r12, lsl #0x2]
	ldrh r2, [r0, #0x0]
	mov r12, r1, lsr #0x10
	cmp r12, r2
	blo _020B01CC
	bx lr

	arm_func_start FUN_020B01F8
FUN_020B01F8:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r2, [r0, #0xc]
	ldrh r12, [r0, #0xe]
	mov lr, #0x0
	add r0, r0, r2
	cmp r12, #0x0
	bls _020B0244
_020B0218:
	ldr r2, [r0, #0x0]
	cmp r2, r1
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	add r2, lr, #0x1
	mov r2, r2, lsl #0x10
	ldr r3, [r0, #0x4]
	mov lr, r2, lsr #0x10
	cmp lr, r12
	add r0, r0, r3
	blo _020B0218
_020B0244:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020B0250
FUN_020B0250: ; 0x020B0250
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r5, _020B02C0 ; =0x04000470
	mov r0, r0, lsl #0xc
	str r0, [r5, #0x0]
	mov r4, r1, lsl #0xc
	ldr r12, [sp, #0x10]
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x1c]
	str r4, [r5, #0x0]
	mov r4, r2, lsl #0xc
	ldr r2, [sp, #0x18]
	ldr lr, _020B02C4 ; =0x0400046C
	str r4, [r5, #0x0]
	mov r4, r3, lsl #0xc
	ldr r3, [sp, #0x20]
	str r4, [lr, #0x0]
	mov r12, r12, lsl #0xc
	str r12, [lr, #0x0]
	mov r12, #0x1000
	mov r0, r0, lsl #0xc
	mov r1, r1, lsl #0xc
	mov r2, r2, lsl #0xc
	mov r3, r3, lsl #0xc
	str r12, [lr, #0x0]
	bl FUN_020B0340
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B02C0: .word 0x04000470
_020B02C4: .word 0x0400046C

	arm_func_start FUN_020B02C8
FUN_020B02C8: ; 0x020B02C8
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	ldr r2, _020B0330 ; =0xBFFF0000
	ldr r0, _020B0334 ; =0x04000580
	mov r1, #0x400000
	str r2, [r0, #0x0]
	rsb r0, r1, #0x0
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	mov r0, #0x0
	str r1, [sp, #0x8]
	mov r1, #0x1
	str r1, [sp, #0xc]
	mov r2, r0
	mov r1, #0xc0000
	mov r3, #0x100000
	str r0, [sp, #0x10]
	bl G3i_OrthoW_
	ldr r1, _020B0338 ; =0x0400044C
	mov r2, #0x0
	ldr r0, _020B033C ; =0x04000440
	str r2, [r1, #0x0]
	mov r1, #0x1
	str r1, [r0, #0x0]
	add sp, sp, #0x14
	ldmia sp!, {pc}
	.balign 4
_020B0330: .word 0xBFFF0000
_020B0334: .word 0x04000580
_020B0338: .word 0x0400044C
_020B033C: .word 0x04000440

	arm_func_start FUN_020B0340
FUN_020B0340: ; 0x020B0340
	stmdb sp!, {r4-r6,lr}
	mov r3, r3, lsl #0x8
	mov r0, r0, lsl #0x8
	mov r4, r3, asr #0x10
	mov r3, r0, asr #0x10
	mov r0, r4, lsl #0x10
	mov r3, r3, lsl #0x10
	mov r1, r1, lsl #0x8
	mov r1, r1, asr #0x10
	mov r1, r1, lsl #0x10
	mov r2, r2, lsl #0x8
	mov r2, r2, asr #0x10
	mov r2, r2, lsl #0x10
	ldr ip, _020B03F4 ; =0x04000500
	mov lr, #0x1
	mov r6, r0, lsr #0x10
	mov r5, r3, lsr #0x10
	mov r3, r1, lsr #0x10
	mov r1, r2, lsr #0x10
	ldr r4, _020B03F8 ; =0x04000488
	str lr, [r12, #0x0]
	orr r0, r5, r6, lsl #0x10
	ldr lr, _020B03FC ; =0x0400048C
	str r0, [r4, #0x0]
	mov r0, #0x10000000
	str r0, [lr, #0x0]
	mov r12, #0x0
	str r12, [lr, #0x0]
	orr r2, r3, r6, lsl #0x10
	ldr r0, _020B0400 ; =0x10001000
	str r2, [r4, #0x0]
	str r0, [lr, #0x0]
	str r12, [lr, #0x0]
	orr r0, r3, r1, lsl #0x10
	str r0, [r4, #0x0]
	mov r0, #0x1000
	str r0, [lr, #0x0]
	str r12, [lr, #0x0]
	orr r0, r5, r1, lsl #0x10
	str r0, [r4, #0x0]
	str r12, [lr, #0x0]
	ldr r0, _020B0404 ; =0x04000504
	str r12, [lr, #0x0]
	str r12, [r0, #0x0]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B03F4: .word 0x04000500
_020B03F8: .word 0x04000488
_020B03FC: .word 0x0400048C
_020B0400: .word 0x10001000
_020B0404: .word 0x04000504

	arm_func_start FUN_020B0408
FUN_020B0408:
	ldr r1, [r0, #0x14]
	cmp r1, #0x0
	ldreq r0, [r0, #0x18]
	ldreq r1, [r0, #0x8]
	cmp r1, #0x2
	beq _020B0428
	cmp r1, #0x4
	bne _020B0430
_020B0428:
	mov r0, #0x1
	bx lr
_020B0430:
	mov r0, #0x0
	bx lr

	arm_func_start FUN_020B0438
FUN_020B0438: ; 0x020B0438
	ldr ip, _020B0444 ; =FUN_020B0448
	str r1, [r0, #0x18]
	bx r12
	.balign 4
_020B0444: .word FUN_020B0448

	arm_func_start FUN_020B0448
FUN_020B0448: ; 0x020B0448
	ldr r1, [r0, #0x10]
	cmp r1, #0x0
	movgt r2, #0x1
	ldr r1, [r0, #0x4]
	movle r2, #0x0
	eors r1, r2, r1
	beq _020B047C
	ldr r2, [r0, #0x18]
	ldrh r1, [r2, #0x2]
	ldr r2, [r2, #0xc]
	add r1, r2, r1, lsl #0x3
	str r1, [r0, #0x0]
	b _020B0494
_020B047C:
	ldr r2, [r0, #0x18]
	ldrh r1, [r2, #0x0]
	ldr r2, [r2, #0xc]
	add r1, r2, r1, lsl #0x3
	sub r1, r1, #0x8
	str r1, [r0, #0x0]
_020B0494:
	ldr ip, _020B04A4 ; =FUN_020B0534
	mov r1, #0x0
	str r1, [r0, #0xc]
	bx r12
	.balign 4
_020B04A4: .word FUN_020B0534

	arm_func_start FUN_020B04A8
FUN_020B04A8: ; 0x020B04A8
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	str r1, [r0, #0x8]
	strh r1, [r0, #0xc]
	bx lr

	arm_func_start FUN_020B04C0
FUN_020B04C0:
	stmdb sp!, {r4,lr}
	mov r4, r0
	add r0, r4, #0x1c
	bl FUN_020B04A8
	mov r1, #0x0
	str r1, [r4, #0x0]
	str r1, [r4, #0x4]
	mov r0, #0x1
	str r0, [r4, #0x8]
	str r1, [r4, #0xc]
	mov r0, #0x1000
	str r0, [r4, #0x10]
	str r1, [r4, #0x14]
	str r1, [r4, #0x18]
	ldmia sp!, {r4,pc}
_020B04FC: ; 0x020B04FC
	ldr r1, [r0, #0x18]
	ldr r2, [r0, #0x0]
	ldr r0, [r1, #0xc]
	sub r0, r2, r0
	mov r0, r0, lsl #0xd
	mov r0, r0, lsr #0x10
	bx lr

	arm_func_start FUN_020B0518
FUN_020B0518:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020B06EC
_020B0524: ; 0x020B0524
	cmp r0, #0x0
	movne r1, #0x0
	strne r1, [r4, #0xc]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020B0534
FUN_020B0534:
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	ldr r0, [r8, #0x8]
	mov r7, #0x0
	cmp r0, #0x1
	movne r0, r7
	ldmneia sp!, {r4-r8,pc}
_020B0550: ; 0x020B0550
	ldr r2, [r8, #0x10]
	mov r0, #0x800
	smull r3, r1, r2, r1
	adds r0, r3, r0
	adc r1, r1, r7
	mov r0, r0, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	bl abs
	ldr r1, [r8, #0xc]
	add r6, r8, #0xc
	add r0, r1, r0
	str r0, [r8, #0xc]
	mov r4, r7
	mov r5, #0x1
	b _020B06A8
_020B058C:
	ldr r0, [r8, #0x0]
	ldr r1, [r6, #0x0]
	ldrh r0, [r0, #0x4]
	mov r7, r5
	sub r0, r1, r0, lsl #0xc
	str r0, [r6, #0x0]
	ldr r0, [r8, #0x10]
	cmp r0, #0x0
	movgt r1, r5
	ldr r0, [r8, #0x4]
	movle r1, r4
	eors r0, r1, r0
	ldrne r0, [r8, #0x0]
	addne r0, r0, #0x8
	strne r0, [r8, #0x0]
	ldreq r0, [r8, #0x0]
	subeq r0, r0, #0x8
	streq r0, [r8, #0x0]
	ldr r1, [r8, #0x10]
	ldr r0, [r8, #0x0]
	cmp r1, #0x0
	movgt r2, r5
	ldr r1, [r8, #0x4]
	movle r2, r4
	eors r1, r2, r1
	beq _020B0614
	ldr r2, [r8, #0x18]
	ldrh r1, [r2, #0x0]
	ldr r2, [r2, #0xc]
	add r1, r2, r1, lsl #0x3
	cmp r0, r1
	movcs r0, r5
	movcc r0, r4
	b _020B0634
_020B0614:
	ldr r2, [r8, #0x18]
	ldrh r1, [r2, #0x2]
	ldr r2, [r2, #0xc]
	add r1, r2, r1, lsl #0x3
	sub r1, r1, #0x8
	cmp r0, r1
	movls r0, r5
	movhi r0, r4
_020B0634:
	cmp r0, #0x0
	beq _020B0644
	mov r0, r8
	bl FUN_020B0710
_020B0644:
	ldr r0, [r8, #0x1c]
	cmp r0, #0x0
	beq _020B06A8
	ldr r0, [r8, #0x18]
	ldr r2, [r8, #0x1c]
	ldr r1, [r8, #0x0]
	ldr r0, [r0, #0xc]
	cmp r2, #0x2
	sub r0, r1, r0
	mov r0, r0, lsl #0xd
	mov r1, r0, lsr #0x10
	beq _020B0680
	cmp r2, #0x3
	beq _020B069C
	b _020B06A8
_020B0680:
	ldrh r0, [r8, #0x28]
	cmp r1, r0
	bne _020B06A8
	ldr r0, [r8, #0x20]
	ldr r2, [r8, #0x24]
	blx r2
	b _020B06A8
_020B069C:
	ldr r0, [r8, #0x20]
	ldr r2, [r8, #0x24]
	blx r2
_020B06A8:
	ldr r0, [r8, #0x8]
	cmp r0, #0x0
	beq _020B06CC
	ldr r0, [r8, #0x0]
	ldr r1, [r8, #0xc]
	ldrh r0, [r0, #0x4]
	cmp r1, r0, lsl #0xc
	movge r0, r5
	bge _020B06D0
_020B06CC:
	mov r0, r4
_020B06D0:
	cmp r0, #0x0
	bne _020B058C
	mov r0, r7
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020B06E0
FUN_020B06E0: ; 0x020B06E0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	bx lr

	arm_func_start FUN_020B06EC
FUN_020B06EC:
	ldr r3, [r0, #0x18]
	ldrh r2, [r3, #0x0]
	cmp r1, r2
	ldrcc r2, [r3, #0xc]
	addcc r1, r2, r1, lsl #0x3
	strcc r1, [r0, #0x0]
	movcc r0, #0x1
	movcs r0, #0x0
	bx lr

	arm_func_start FUN_020B0710
FUN_020B0710: ; 0x020B0710
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	ldreq r0, [r4, #0x18]
	ldreq r0, [r0, #0x8]
	cmp r0, #0x3
	beq _020B0738
	cmp r0, #0x4
	bne _020B07B4
_020B0738:
	ldr r0, [r4, #0x4]
	eor r0, r0, #0x1
	str r0, [r4, #0x4]
	ldr r1, [r4, #0x18]
	ldr r2, [r4, #0x0]
	ldrh r0, [r1, #0x2]
	ldr r1, [r1, #0xc]
	add r0, r1, r0, lsl #0x3
	sub r0, r0, #0x8
	cmp r2, r0
	bhi _020B0800
	ldr r0, [r4, #0x1c]
	cmp r0, #0x1
	bne _020B0780
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x24]
	blx r2
_020B0780:
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	ldreq r0, [r4, #0x18]
	ldreq r0, [r0, #0x8]
	cmp r0, #0x2
	beq _020B07A8
	cmp r0, #0x4
	movne r0, #0x0
	strne r0, [r4, #0x8]
	bne _020B0800
_020B07A8:
	mov r0, r4
	bl FUN_020B0448
	b _020B0800
_020B07B4:
	ldr r0, [r4, #0x1c]
	cmp r0, #0x1
	bne _020B07D0
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x24]
	blx r2
_020B07D0:
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	ldreq r0, [r4, #0x18]
	ldreq r0, [r0, #0x8]
	cmp r0, #0x2
	beq _020B07F8
	cmp r0, #0x4
	movne r0, #0x0
	strne r0, [r4, #0x8]
	bne _020B0800
_020B07F8:
	mov r0, r4
	bl FUN_020B0448
_020B0800:
	ldr r1, [r4, #0x18]
	ldr r2, [r4, #0x0]
	ldrh r0, [r1, #0x0]
	ldr r1, [r1, #0xc]
	add r0, r1, r0, lsl #0x3
	sub r0, r0, #0x8
	cmp r2, r0
	strhi r0, [r4, #0x0]
	ldmhiia sp!, {r4,pc}
_020B0824: ; 0x020B0824
	cmp r2, r1
	strcc r1, [r4, #0x0]
	ldmia sp!, {r4,pc}
_020B0830: ; 0x020B0830
	ldrh r3, [r0, #0x6]
	ldrh r2, [r0, #0x8]
	mov r12, #0x0
	add r1, r3, #0x1
	cmp r2, r1
	bgt _020B0854
	ldrh r0, [r0, #0x4]
	cmp r0, r3
	movls r12, #0x1
_020B0854:
	cmp r12, #0x0
	subne r0, r3, r2
	addne r0, r0, #0x1
	movne r0, r0, lsl #0x10
	movne r0, r0, lsr #0x10
	moveq r0, #0x0
	bx lr

	arm_func_start FUN_020B0870
FUN_020B0870: ; 0x020B0870
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020B09B4
	mov r0, r4
	bl FUN_020B0888
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020B0888
FUN_020B0888: ; 0x020B0888
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	ldr r0, [r5, #0x14]
	cmp r0, #0x0
	beq _020B0944
	ldrh r2, [r5, #0x6]
	ldrh r1, [r5, #0x8]
	mov r3, #0x0
	add r0, r2, #0x1
	cmp r1, r0
	bgt _020B08C0
	ldrh r0, [r5, #0x4]
	cmp r0, r2
	movls r3, #0x1
_020B08C0:
	cmp r3, #0x0
	moveq r4, #0x0
	beq _020B08E0
	ldrh r0, [r5, #0x4]
	sub r0, r2, r0
	add r0, r0, #0x1
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0xd
_020B08E0:
	ldr r2, [r5, #0x0]
	ldr r1, _020B09AC ; =0x021CCDA0
	mov r0, #0x540
	mla r1, r2, r0, r1
	ldrh r0, [r5, #0x4]
	add r2, r1, #0x100
	mov r1, r4
	add r6, r2, r0, lsl #0x3
	mov r0, r6
	bl DC_InvalidateRange
	ldr r0, _020B09B0 ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020B0930
	mov r1, r6
	mov r3, r4
	mov r2, #0xc0
	bl MI_DmaFill32
	b _020B0998
_020B0930:
	mov r1, r6
	mov r2, r4
	mov r0, #0xc0
	bl MIi_CpuClear32
	b _020B0998
_020B0944:
	ldr r2, [r5, #0x0]
	ldr r1, _020B09AC ; =0x021CCDA0
	mov r0, #0x540
	mla r1, r2, r0, r1
	ldrh r2, [r5, #0x4]
	ldrh r0, [r5, #0x6]
	add r1, r1, #0x100
	add r3, r1, r2, lsl #0x3
	sub r0, r0, r2
	add r0, r0, #0x1
	mov r0, r0, lsl #0x10
	movs r2, r0, lsr #0x10
	mov r0, #0x0
	beq _020B0998
	mov r1, #0xc0
_020B0980:
	add r0, r0, #0x1
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	cmp r0, r2
	strh r1, [r3], #0x8
	blo _020B0980
_020B0998:
	ldrh r0, [r5, #0x4]
	strh r0, [r5, #0x8]
	ldrh r0, [r5, #0xa]
	strh r0, [r5, #0xe]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B09AC: .word 0x021CCDA0
_020B09B0: .word 0x02106814

	arm_func_start FUN_020B09B4
FUN_020B09B4: ; 0x020B09B4
	stmdb sp!, {r4-r10,lr}
	mov r7, r0
	ldr r0, [r7, #0x14]
	cmp r0, #0x0
	beq _020B0A48
	ldr r5, [r7, #0x0]
	ldr r1, _020B0BA8 ; =0x021CCDA0
	mov r0, #0x540
	mla r1, r5, r0, r1
	ldrh r2, [r7, #0x4]
	ldrh r0, [r7, #0x6]
	add r1, r1, #0x100
	add r4, r1, r2, lsl #0x3
	sub r0, r0, r2
	add r0, r0, #0x1
	mov r0, r0, lsl #0x13
	mov r6, r0, lsr #0x10
	mov r2, r2, lsl #0x13
	mov r0, r4
	mov r1, r6
	mov r7, r2, lsr #0x10
	bl DC_FlushRange
_020B0A0C: ; 0x020B0A0C
	cmp r5, #0x0
	beq _020B0A20
	cmp r5, #0x1
	beq _020B0A34
	ldmia sp!, {r4-r10,pc}
_020B0A20:
	mov r0, r4
	mov r1, r7
	mov r2, r6
	bl GX_LoadOAM
	ldmia sp!, {r4-r10,pc}
_020B0A34:
	mov r0, r4
	mov r1, r7
	mov r2, r6
	bl GXS_LoadOAM
	ldmia sp!, {r4-r10,pc}
_020B0A48:
	ldr r0, [r7, #0x0]
	ldr r2, _020B0BA8 ; =0x021CCDA0
	mov r1, #0x540
	mla r2, r0, r1, r2
	ldrh r5, [r7, #0x4]
	ldrh r1, [r7, #0x6]
	ldr r3, _020B0BAC ; =0x0210655C
	add r4, r2, #0x100
	sub r1, r1, r5
	add r1, r1, #0x1
	mov r1, r1, lsl #0x10
	mov r2, r5, lsl #0x13
	add r6, r4, r5, lsl #0x3
	movs r5, r1, lsr #0x10
	mov r4, r2, lsr #0x10
	ldr r9, [r3, r0, lsl #0x2]
	mov r10, #0x0
	beq _020B0AC8
	mov r8, #0x6
_020B0A94:
	mov r0, r6
	mov r1, r4
	mov r2, r8
	blx r9
	add r0, r10, #0x1
	add r2, r4, #0x8
	mov r1, r0, lsl #0x10
	mov r0, r2, lsl #0x10
	mov r10, r1, lsr #0x10
	cmp r10, r5
	mov r4, r0, lsr #0x10
	add r6, r6, #0x8
	blo _020B0A94
_020B0AC8:
	ldrh r2, [r7, #0xc]
	ldrh r1, [r7, #0xe]
	mov r3, #0x0
	add r0, r2, #0x1
	cmp r1, r0
	bgt _020B0AEC
	ldrh r0, [r7, #0xa]
	cmp r0, r2
	movls r3, #0x1
_020B0AEC:
	cmp r3, #0x0
	ldmeqia sp!, {r4-r10,pc}
_020B0AF4: ; 0x020B0AF4
	ldr r0, [r7, #0x0]
	ldr r2, _020B0BA8 ; =0x021CCDA0
	mov r1, #0x540
	mla r2, r0, r1, r2
	ldrh r5, [r7, #0xa]
	add r4, r2, #0x100
	ldrh r1, [r7, #0xc]
	mov r2, r5, lsl #0x15
	ldr r3, _020B0BAC ; =0x0210655C
	sub r1, r1, r5
	add r1, r1, #0x1
	mov r1, r1, lsl #0x10
	add r9, r4, r5, lsl #0x5
	ldr r5, [r3, r0, lsl #0x2]
	movs r8, r1, lsr #0x10
	mov r7, r2, lsr #0x10
	mov r6, #0x0
	ldmeqia sp!, {r4-r10,pc}
_020B0B3C: ; 0x020B0B3C
	mov r4, #0x2
_020B0B40:
	mov r2, r4
	add r0, r9, #0x6
	add r1, r7, #0x6
	blx r5
	mov r2, r4
	add r0, r9, #0xe
	add r1, r7, #0xe
	blx r5
	mov r2, r4
	add r0, r9, #0x16
	add r1, r7, #0x16
	blx r5
	add r0, r9, #0x1e
	add r1, r7, #0x1e
	mov r2, r4
	blx r5
	add r0, r7, #0x20
	mov r0, r0, lsl #0x10
	mov r7, r0, lsr #0x10
	add r9, r9, #0x20
	add r0, r6, #0x1
	mov r0, r0, lsl #0x10
	mov r6, r0, lsr #0x10
	cmp r6, r8
	blo _020B0B40
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020B0BA8: .word 0x021CCDA0
_020B0BAC: .word 0x0210655C

	arm_func_start FUN_020B0BB0
FUN_020B0BB0: ; 0x020B0BB0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r12, [r0, #0xc]
	ldrh r3, [r0, #0xe]
	mov lr, #0x0
	add r2, r12, #0x1
	cmp r3, r2
	bgt _020B0BDC
	ldrh r2, [r0, #0xa]
	cmp r2, r12
	movls lr, #0x1
_020B0BDC:
	cmp lr, #0x0
	subne r2, r12, r3
	addne r2, r2, #0x1
	movne r2, r2, lsl #0x10
	movne r2, r2, lsr #0x10
	moveq r2, #0x0
	cmp r2, #0x1
	movcs r2, #0x1
	movcc r2, #0x0
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldreq r0, _020B0C74 ; =0x0000FFFE
	ldmeqia sp!, {pc}
	ldr lr, [r0, #0x0]
	ldr r3, _020B0C78 ; =0x021CCDA0
	mov r2, #0x540
	mla r12, lr, r2, r3
	ldr r3, [r1, #0x0]
	ldrh r2, [r0, #0xe]
	add r12, r12, #0x100
	mov r3, r3, asr #0x4
	add r12, r12, r2, lsl #0x5
	strh r3, [r12, #0x6]
	ldr r3, [r1, #0x4]
	mov r3, r3, asr #0x4
	strh r3, [r12, #0xe]
	ldr r3, [r1, #0x8]
	mov r3, r3, asr #0x4
	strh r3, [r12, #0x16]
	ldr r1, [r1, #0xc]
	mov r1, r1, asr #0x4
	strh r1, [r12, #0x1e]
	ldrh r1, [r0, #0xe]
	add r1, r1, #0x1
	strh r1, [r0, #0xe]
	mov r0, r2
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B0C74: .word 0x0000FFFE
_020B0C78: .word 0x021CCDA0

	arm_func_start FUN_020B0C7C
FUN_020B0C7C: ; 0x020B0C7C
	stmdb sp!, {r4,lr}
	ldrh r12, [r0, #0x6]
	ldrh r4, [r0, #0x8]
	mov lr, #0x0
	add r3, r12, #0x1
	cmp r4, r3
	bgt _020B0CA4
	ldrh r3, [r0, #0x4]
	cmp r3, r12
	movls lr, #0x1
_020B0CA4:
	cmp lr, #0x0
	subne r3, r12, r4
	addne r3, r3, #0x1
	movne r3, r3, lsl #0x10
	movne r3, r3, lsr #0x10
	moveq r3, #0x0
	cmp r3, #0x1
	movcs r3, #0x1
	movcc r3, #0x0
	cmp r3, #0x0
	beq _020B0D48
	ldr r4, [r0, #0x0]
	ldr ip, _020B0D50 ; =0x021CCDA0
	mov r3, #0x540
	mla r12, r4, r3, r12
	ldrh r3, [r0, #0x8]
	add r4, r12, #0x100
	ldrh r12, [r1, #0x0]
	mov lr, r3, lsl #0x3
	add r3, r4, r3, lsl #0x3
	strh r12, [r4, lr]
	ldrh lr, [r1, #0x2]
	ldr ip, _020B0D54 ; =0x0000FFFE
	strh lr, [r3, #0x2]
	ldrh r1, [r1, #0x4]
	cmp r2, r12
	strh r1, [r3, #0x4]
	beq _020B0D34
	ldr r1, [r3, #0x0]
	mov r12, r1, lsl #0x16
	mov r12, r12, lsr #0x1e
	ands r12, r12, #0x1
	bicne r12, r1, #0x3e000000
	andne r1, r2, #0x1f
	orrne r1, r12, r1, lsl #0x19
	strne r1, [r3, #0x0]
_020B0D34:
	ldrh r1, [r0, #0x8]
	add r1, r1, #0x1
	strh r1, [r0, #0x8]
	mov r0, #0x1
	ldmia sp!, {r4,pc}
_020B0D48:
	mov r0, #0x0
	ldmia sp!, {r4,pc}
	.balign 4
_020B0D50: .word 0x021CCDA0
_020B0D54: .word 0x0000FFFE

	arm_func_start FUN_020B0D58
FUN_020B0D58: ; 0x020B0D58
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldrh lr, [r0, #0x6]
	ldrh r12, [r0, #0x8]
	mov r4, #0x0
	add r3, lr, #0x1
	cmp r12, r3
	bgt _020B0D84
	ldrh r3, [r0, #0x4]
	cmp r3, lr
	movls r4, #0x1
_020B0D84:
	cmp r4, #0x0
	subne r3, lr, r12
	addne r3, r3, #0x1
	movne r3, r3, lsl #0x10
	movne r3, r3, lsr #0x10
	moveq r3, #0x0
	cmp r3, r2
	movcs r3, #0x1
	movcc r3, #0x0
	cmp r3, #0x0
	beq _020B0E24
	ldr lr, [r0, #0x0]
	ldr ip, _020B0E30 ; =0x021CCDA0
	mov r3, #0x540
	mla r12, lr, r3, r12
	ldrh r3, [r0, #0x8]
	add r12, r12, #0x100
	cmp r2, #0x0
	add r4, r12, r3, lsl #0x3
	mov r5, #0x0
	ble _020B0E18
	add r3, r0, #0x8
_020B0DDC:
	ldrh lr, [r1, #0x0]
	mov r0, r5, lsl #0x3
	add r12, r4, r5, lsl #0x3
	strh lr, [r4, r0]
	ldrh r0, [r1, #0x2]
	add r5, r5, #0x1
	cmp r5, r2
	strh r0, [r12, #0x2]
	ldrh r0, [r1, #0x4]
	add r1, r1, #0x8
	strh r0, [r12, #0x4]
	ldrh r0, [r3, #0x0]
	add r0, r0, #0x1
	strh r0, [r3, #0x0]
	blt _020B0DDC
_020B0E18:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,pc}
_020B0E24:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B0E30: .word 0x021CCDA0

	arm_func_start FUN_020B0E34
FUN_020B0E34: ; 0x020B0E34
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r5, [sp, #0x1c]
	ldr r6, _020B0FB4 ; =0x021CCDA0
	mov r4, #0x540
	mla r4, r5, r4, r6
	mov lr, r1
	sub r1, r2, #0x1
	add r1, lr, r1
	mov r1, r1, lsl #0x10
	mov r12, r1, lsr #0x10
	add r7, r4, lr, lsl #0x1
	add r2, r4, r12, lsl #0x1
	mov r6, r0
	mov r5, r3
	cmp r7, r2
	mov r3, lr, lsl #0x1
	bhi _020B0E9C
	ldr r0, _020B0FB8 ; =0x0000FFFF
_020B0E80:
	ldrh r1, [r7, #0x0]
	cmp r1, r0
	movne r0, #0x0
	bne _020B0EA0
	add r7, r7, #0x2
	cmp r7, r2
	bls _020B0E80
_020B0E9C:
	mov r0, #0x1
_020B0EA0:
	cmp r0, #0x0
	beq _020B0EE0
	ldr r0, _020B0FBC ; =0x021CCD9C
	sub r2, r12, lr
	ldrh r7, [r0, #0x0]
	add r1, r4, r3
	mov r2, r2, lsl #0x1
	add r3, r7, #0x1
	strh r3, [r0, #0x0]
	strh r7, [r6, #0x10]
	strh lr, [r6, #0x4]
	strh r12, [r6, #0x6]
	strh lr, [r6, #0x8]
	ldrh r0, [r6, #0x10]
	bl MIi_CpuClear16
	b _020B0EEC
_020B0EE0:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020B0EEC:
	ldrh r0, [sp, #0x18]
	add r4, r4, #0x500
	cmp r0, #0x0
	bne _020B0F18
	mov r0, #0x20
	strh r0, [r6, #0xa]
	mov r0, #0x0
	strh r0, [r6, #0xc]
	ldrh r0, [r6, #0xa]
	strh r0, [r6, #0xe]
	b _020B0F98
_020B0F18:
	sub r0, r0, #0x1
	add r0, r5, r0
	mov r0, r0, lsl #0x10
	mov r12, r0, lsr #0x10
	add r7, r4, r5, lsl #0x1
	add r2, r4, r12, lsl #0x1
	cmp r7, r2
	mov r3, r5, lsl #0x1
	bhi _020B0F5C
	ldr r0, _020B0FB8 ; =0x0000FFFF
_020B0F40:
	ldrh r1, [r7, #0x0]
	cmp r1, r0
	movne r0, #0x0
	bne _020B0F60
	add r7, r7, #0x2
	cmp r7, r2
	bls _020B0F40
_020B0F5C:
	mov r0, #0x1
_020B0F60:
	cmp r0, #0x0
	beq _020B0F8C
	strh r5, [r6, #0xa]
	strh r12, [r6, #0xc]
	strh r5, [r6, #0xe]
	ldrh r0, [r6, #0x10]
	sub r2, r12, r5
	add r1, r4, r3
	mov r2, r2, lsl #0x1
	bl MIi_CpuClear16
	b _020B0F98
_020B0F8C:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020B0F98:
	mov r1, #0x0
	ldr r0, [sp, #0x1c]
	str r1, [r6, #0x14]
	str r0, [r6, #0x0]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B0FB4: .word 0x021CCDA0
_020B0FB8: .word 0x0000FFFF
_020B0FBC: .word 0x021CCD9C

	arm_func_start FUN_020B0FC0
FUN_020B0FC0: ; 0x020B0FC0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020B1060 ; =0x021CCEA0
	mov r0, #0xc0
	mov r2, #0x400
	bl MIi_CpuClear16
	ldr r1, _020B1064 ; =0x021CD3E0
	mov r0, #0xc0
	mov r2, #0x400
	bl MIi_CpuClear16
	ldr r1, _020B1068 ; =0x021CD920
	mov r0, #0xc0
	mov r2, #0x400
	bl MIi_CpuClear16
	ldr r0, _020B106C ; =0x0000FFFF
	ldr r1, _020B1070 ; =0x021CCDA0
	mov r2, #0x100
	bl MIi_CpuClear16
	ldr r0, _020B106C ; =0x0000FFFF
	ldr r1, _020B1074 ; =0x021CD2E0
	mov r2, #0x100
	bl MIi_CpuClear16
	ldr r0, _020B106C ; =0x0000FFFF
	ldr r1, _020B1078 ; =0x021CD820
	mov r2, #0x100
	bl MIi_CpuClear16
	ldr r0, _020B106C ; =0x0000FFFF
	ldr r1, _020B107C ; =0x021CD2A0
	mov r2, #0x40
	bl MIi_CpuClear16
	ldr r0, _020B106C ; =0x0000FFFF
	ldr r1, _020B1080 ; =0x021CD7E0
	mov r2, #0x40
	bl MIi_CpuClear16
	ldr r0, _020B106C ; =0x0000FFFF
	ldr r1, _020B1084 ; =0x021CDD20
	mov r2, #0x40
	bl MIi_CpuClear16
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B1060: .word 0x021CCEA0
_020B1064: .word 0x021CD3E0
_020B1068: .word 0x021CD920
_020B106C: .word 0x0000FFFF
_020B1070: .word 0x021CCDA0
_020B1074: .word 0x021CD2E0
_020B1078: .word 0x021CD820
_020B107C: .word 0x021CD2A0
_020B1080: .word 0x021CD7E0
_020B1084: .word 0x021CDD20

	arm_func_start FUN_020B1088
FUN_020B1088: ; 0x020B1088
	ldr ip, _020B1094 ; =MIi_CpuCopy16
	add r1, r1, #0x7000000
	bx r12
	.balign 4
_020B1094: .word MIi_CpuCopy16

	arm_func_start FUN_020B1098
FUN_020B1098: ; 0x020B1098
	ldr r3, _020B10A8 ; =0x07000400
	ldr ip, _020B10AC ; =MIi_CpuCopy16
	add r1, r1, r3
	bx r12
	.balign 4
_020B10A8: .word 0x07000400
_020B10AC: .word MIi_CpuCopy16

	arm_func_start FUN_020B10B0
FUN_020B10B0: ; 0x020B10B0
	mov r1, r1, lsl #0x1
	ldrh r0, [r0, r1]
	bx lr

	arm_func_start FUN_020B10BC
FUN_020B10BC: ; 0x020B10BC
	ldr r0, [r0, r1, lsl #0x2]
	bx lr

	arm_func_start FUN_020B10C4
FUN_020B10C4:
	str r2, [r0, r1, lsl #0x2]
	bx lr

	arm_func_start FUN_020B10CC
FUN_020B10CC:
	mov r2, #0x0
	mvn r1, #0x0
_020B10D4:
	str r1, [r0, r2, lsl #0x2]
	add r2, r2, #0x1
	cmp r2, #0x3
	blt _020B10D4
	bx lr

	arm_func_start FUN_020B10E8
FUN_020B10E8: ; 0x020B10E8
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
_020B114C: ; 0x020B114C
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
	bl FUN_020B19D0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020B1240
FUN_020B1240: ; 0x020B1240
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
_020B126C: ; 0x020B126C
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
	bl FUN_020B19D0
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}

	arm_func_start FUN_020B1340
FUN_020B1340: ; 0x020B1340
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	ldr r0, [r7, #0x14]
	ldr r1, [r7, #0x10]
	mov r5, r2
	mov r4, r3
	bl DC_FlushRange
_020B1364: ; 0x020B1364
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
_020B13E4:
	b _020B1444
_020B13E8:
	b _020B1414
_020B13EC:
	b _020B141C
_020B13F0:
	b _020B1444
_020B13F4:
	b _020B1424
_020B13F8:
	b _020B1444
_020B13FC:
	b _020B1444
_020B1400:
	b _020B1444
_020B1404:
	b _020B142C
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
_020B146C:
	b _020B14CC
_020B1470:
	b _020B149C
_020B1474:
	b _020B14A4
_020B1478:
	b _020B14CC
_020B147C:
	b _020B14AC
_020B1480:
	b _020B14CC
_020B1484:
	b _020B14CC
_020B1488:
	b _020B14CC
_020B148C:
	b _020B14B4
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
	bl FUN_020B1A1C
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B1520: .word 0xFFCFFFEF
_020B1524: .word 0x04001000

	arm_func_start FUN_020B1528
FUN_020B1528: ; 0x020B1528
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
_020B159C: ; 0x020B159C
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
_020B1624:
	b _020B1684
_020B1628:
	b _020B1654
_020B162C:
	b _020B165C
_020B1630:
	b _020B1684
_020B1634:
	b _020B1664
_020B1638:
	b _020B1684
_020B163C:
	b _020B1684
_020B1640:
	b _020B1684
_020B1644:
	b _020B166C
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
_020B16AC:
	b _020B170C
_020B16B0:
	b _020B16DC
_020B16B4:
	b _020B16E4
_020B16B8:
	b _020B170C
_020B16BC:
	b _020B16EC
_020B16C0:
	b _020B170C
_020B16C4:
	b _020B170C
_020B16C8:
	b _020B170C
_020B16CC:
	b _020B16F4
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
	bl FUN_020B1A1C
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B1760: .word 0xFFCFFFEF
_020B1764: .word 0x04001000

	arm_func_start FUN_020B1768
FUN_020B1768: ; 0x020B1768
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
_020B17DC: ; 0x020B17DC
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
_020B1864:
	b _020B18C4
_020B1868:
	b _020B1894
_020B186C:
	b _020B189C
_020B1870:
	b _020B18C4
_020B1874:
	b _020B18A4
_020B1878:
	b _020B18C4
_020B187C:
	b _020B18C4
_020B1880:
	b _020B18C4
_020B1884:
	b _020B18AC
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
_020B18EC:
	b _020B194C
_020B18F0:
	b _020B191C
_020B18F4:
	b _020B1924
_020B18F8:
	b _020B194C
_020B18FC:
	b _020B192C
_020B1900:
	b _020B194C
_020B1904:
	b _020B194C
_020B1908:
	b _020B194C
_020B190C:
	b _020B1934
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
	bl FUN_020B1A1C
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B19A0: .word 0xFFCFFFEF
_020B19A4: .word 0x04001000

	arm_func_start FUN_020B19A8
FUN_020B19A8:
	add r0, r0, r1, lsl #0x2
	ldr r1, [r0, #0x8]
	mvn r0, #0x0
	cmp r1, r0
	movne r0, #0x1
	moveq r0, #0x0
	bx lr

	arm_func_start FUN_020B19C4
FUN_020B19C4: ; 0x020B19C4
	add r0, r0, r1, lsl #0x2
	ldr r0, [r0, #0x8]
	bx lr

	arm_func_start FUN_020B19D0
FUN_020B19D0: ; 0x020B19D0
	add r0, r0, r1, lsl #0x2
	str r2, [r0, #0x8]
	bx lr

	arm_func_start FUN_020B19DC
FUN_020B19DC: ; 0x020B19DC
	mov r3, #0x0
	mvn r2, #0x0
_020B19E4:
	add r1, r0, r3, lsl #0x2
	add r3, r3, #0x1
	str r2, [r1, #0x8]
	cmp r3, #0x3
	blt _020B19E4
	bx lr

	arm_func_start FUN_020B19FC
FUN_020B19FC:
	ldr r1, [r0, r1, lsl #0x2]
	mvn r0, #0x0
	cmp r1, r0
	movne r0, #0x1
	moveq r0, #0x0
	bx lr

	arm_func_start FUN_020B1A14
FUN_020B1A14: ; 0x020B1A14
	ldr r0, [r0, r1, lsl #0x2]
	bx lr

	arm_func_start FUN_020B1A1C
FUN_020B1A1C: ; 0x020B1A1C
	str r2, [r0, r1, lsl #0x2]
	bx lr

	arm_func_start FUN_020B1A24
FUN_020B1A24: ; 0x020B1A24
	mov r2, #0x0
	mvn r1, #0x0
_020B1A2C:
	str r1, [r0, r2, lsl #0x2]
	add r2, r2, #0x1
	cmp r2, #0x3
	blt _020B1A2C
	bx lr

	arm_func_start FUN_020B1A40
FUN_020B1A40: ; 0x020B1A40
	stmdb sp!, {r4,lr}
	mov r4, r0
	add r1, r4, #0x4
	mov r0, #0x0
	mov r2, #0x18
	bl MIi_CpuClear16
	mov r0, #0x1000
	str r0, [r4, #0x4]
	str r0, [r4, #0x8]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020B1A68
FUN_020B1A68:
	ldr ip, _020B1A74 ; =FUN_020B1A40
	str r1, [r0, #0x0]
	bx r12
	.balign 4
_020B1A74: .word FUN_020B1A40

	arm_func_start FUN_020B1A78
FUN_020B1A78: ; 0x020B1A78
	ldr r3, [r0, #0x0]
	cmp r3, #0x1
	ldreqh r3, [r0, #0x12]
	orreq r3, r3, #0x2
	streqh r3, [r0, #0x12]
	streq r1, [r0, #0x4]
	streq r2, [r0, #0x8]
	bx lr

	arm_func_start FUN_020B1A98
FUN_020B1A98: ; 0x020B1A98
	ldr r2, [r0, #0x0]
	cmp r2, #0x1
	ldreqh r2, [r0, #0x12]
	orreq r2, r2, #0x4
	streqh r2, [r0, #0x12]
	streqh r1, [r0, #0x10]
	bx lr

	arm_func_start FUN_020B1AB4
FUN_020B1AB4: ; 0x020B1AB4
	ldr r3, [r0, #0x0]
	cmp r3, #0x1
	ldreqh r3, [r0, #0x12]
	orreq r3, r3, #0x8
	streqh r3, [r0, #0x12]
	streqh r1, [r0, #0xc]
	streqh r2, [r0, #0xe]
	bx lr

	arm_func_start FUN_020B1AD4
FUN_020B1AD4: ; 0x020B1AD4
	mov r2, #0x0
	str r2, [r0, #0x0]
	str r1, [r0, #0x4]
	mov r1, #0x1
	str r1, [r0, #0x8]
	ldr ip, _020B1AF4 ; =FUN_020B1A68
	add r0, r0, #0xc
	bx r12
	.balign 4
_020B1AF4: .word FUN_020B1A68

	arm_func_start FUN_020B1AF8
FUN_020B1AF8: ; 0x020B1AF8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	ldrh r5, [r2, #0x0]
	ldr r4, [sp, #0x60]
	ldr r10, [sp, #0x58]
	str r4, [sp, #0x60]
	cmp r1, r5
	movcs r1, r5
	mov r4, #0x0
	cmp r1, #0x0
	str r4, [sp, #0x0]
	bls _020B1E7C
	ldrh r4, [sp, #0x5c]
	mov r4, r4, lsl #0x19
	str r4, [sp, #0x4]
	ldr r4, [sp, #0x0]
	str r4, [sp, #0x14]
	mov r4, #0x100
	str r4, [sp, #0xc]
	mov r4, #0x300
	str r4, [sp, #0x8]
	mov r4, #0x1
	str r4, [sp, #0x10]
_020B1B54:
	ldr r5, [sp, #0x0]
	mov r6, #0x6
	mul r6, r5, r6
	ldr r8, [r2, #0x4]
	ldr r4, [sp, #0x0]
	add r7, r0, r5, lsl #0x3
	ldrh r5, [r8, r6]
	mov r4, r4, lsl #0x3
	add r9, r8, r6
	strh r5, [r0, r4]
	ldrh r4, [r9, #0x2]
	cmp r3, #0x0
	strh r4, [r7, #0x2]
	ldrh r4, [r9, #0x4]
	strh r4, [r7, #0x4]
	bne _020B1B9C
	cmp r10, #0x0
	beq _020B1E60
_020B1B9C:
	ldr r5, [r7, #0x0]
	ldr r4, _020B1E88 ; =0x01FF0000
	and r4, r5, r4
	mov r4, r4, lsr #0x10
	mov r4, r4, lsl #0x10
	mov r4, r4, asr #0x10
	cmp r4, #0xff
	orrgt r4, r4, #0xff00
	movgt r4, r4, lsl #0x10
	movgt r4, r4, asr #0x10
	mov r4, r4, lsl #0xc
	str r4, [sp, #0x20]
	ldr r4, [r7, #0x0]
	and r4, r4, #0xff
	mov r4, r4, lsl #0x10
	mov r4, r4, asr #0x10
	cmp r4, #0x7f
	orrgt r4, r4, #0xff00
	movgt r4, r4, lsl #0x10
	movgt r4, r4, asr #0x10
	mov r4, r4, lsl #0xc
	str r4, [sp, #0x24]
	cmp r3, #0x0
	beq _020B1E00
	ldr r5, [r7, #0x0]
	and r6, r5, #0x300
	cmp r6, #0x100
	beq _020B1C1C
	cmp r6, #0x300
	beq _020B1C1C
	and r4, r5, #0x30000000
	orr r6, r6, r4
_020B1C1C:
	cmp r6, #0x300
	bne _020B1C70
	ldr r4, _020B1E8C ; =0xC000C000
	ldr r8, _020B1E90 ; =0x020FF8AC
	and r5, r5, r4
	and r4, r5, #0xc000
	mov r6, r4, asr #0xe
	and r4, r5, #0xc0000000
	mov r4, r4, lsr #0x1e
	mov r4, r4, lsl #0x1
	add r8, r8, r6, lsl #0x3
	ldrh r9, [r4, r8]
	ldr r8, _020B1E94 ; =0x020FF894
	ldr r5, [sp, #0x20]
	add r6, r8, r6, lsl #0x3
	add r5, r5, r9, lsl #0xb
	str r5, [sp, #0x20]
	ldrh r4, [r4, r6]
	ldr r5, [sp, #0x24]
	add r4, r5, r4, lsl #0xb
	str r4, [sp, #0x24]
_020B1C70:
	ldr r4, [sp, #0x60]
	ldr r5, [r3, #0x8]
	cmp r4, #0x0
	ldrne r8, [sp, #0x8]
	add r4, sp, #0x20
	ldreq r8, [sp, #0xc]
	mov r6, r4
	cmp r8, #0x300
	ldreq r9, [sp, #0x10]
	mov r12, #0x1000
	ldrne r9, [sp, #0x14]
	cmp r4, r4
	ldr r4, [sp, #0x24]
	addeq r6, sp, #0x28
	smull r11, r4, r5, r4
	adds r5, r11, r12
	adc r11, r4, #0x0
	ldr r4, [r3, #0x0]
	ldr lr, [sp, #0x20]
	smlal r5, r11, r4, lr
	mov r4, r5, lsr #0xc
	orr r4, r4, r11, lsl #0x14
	str r4, [r6, #0x0]
	ldr r4, [r3, #0xc]
	ldr r5, [sp, #0x24]
	ldr lr, [r3, #0x4]
	smull r11, r5, r4, r5
	adds r11, r11, r12
	adc r4, r5, #0x0
	add r5, sp, #0x28
	cmp r6, r5
	ldr r5, [sp, #0x20]
	smlal r11, r4, lr, r5
	mov r5, r11, lsr #0xc
	orr r5, r5, r4, lsl #0x14
	str r5, [r6, #0x4]
	ldreq r5, [sp, #0x28]
	ldreq r4, [sp, #0x2c]
	streq r5, [sp, #0x20]
	streq r4, [sp, #0x24]
	cmp r8, #0x100
	beq _020B1D38
	cmp r8, #0x300
	beq _020B1D38
	ldr r5, [r7, #0x0]
	ldr r4, _020B1E98 ; =0xC1FFFCFF
	and r4, r5, r4
	orr r4, r4, r8
	str r4, [r7, #0x0]
	b _020B1D54
_020B1D38:
	ldr r5, [r7, #0x0]
	ldr r4, _020B1E98 ; =0xC1FFFCFF
	and r4, r5, r4
	orr r5, r4, r8
	ldr r4, [sp, #0x4]
	orr r4, r4, r5
	str r4, [r7, #0x0]
_020B1D54:
	ldr r6, [r7, #0x0]
	ldr r5, _020B1E8C ; =0xC000C000
	cmp r9, #0x0
	and r8, r6, r5
	and r5, r8, #0xc000
	mov r6, r5, asr #0xe
	and r5, r8, #0xc0000000
	ldr r8, _020B1E90 ; =0x020FF8AC
	mov r5, r5, lsr #0x1e
	mov r5, r5, lsl #0x1
	add r8, r8, r6, lsl #0x3
	ldrh r9, [r5, r8]
	ldr r8, _020B1E94 ; =0x020FF894
	ldr r4, [sp, #0x20]
	add r6, r8, r6, lsl #0x3
	mov r11, r9, asr #0x1
	ldrh r5, [r5, r6]
	mov r8, r11, lsl #0xc
	ldr r6, [r3, #0x0]
	rsb r12, r8, #0x0
	mov r9, r5, asr #0x1
	mla r12, r6, r11, r12
	ldr r5, [r3, #0x8]
	mla r6, r5, r9, r12
	add r6, r4, r6
	str r6, [sp, #0x20]
	ldr r12, [r3, #0x4]
	mov r5, r9, lsl #0xc
	str r12, [sp, #0x1c]
	ldr r12, [r3, #0xc]
	rsb lr, r5, #0x0
	str r12, [sp, #0x18]
	ldr r12, [sp, #0x1c]
	ldr r4, [sp, #0x24]
	mla r11, r12, r11, lr
	ldr r12, [sp, #0x18]
	subne r6, r6, r8
	mla r9, r12, r9, r11
	add r4, r4, r9
	str r4, [sp, #0x24]
	subne r4, r4, r5
	strne r6, [sp, #0x20]
	strne r4, [sp, #0x24]
_020B1E00:
	cmp r10, #0x0
	beq _020B1E28
	ldr r6, [sp, #0x20]
	ldr r4, [r10, #0x0]
	ldr r5, [sp, #0x24]
	add r4, r6, r4
	str r4, [sp, #0x20]
	ldr r4, [r10, #0x4]
	add r4, r5, r4
	str r4, [sp, #0x24]
_020B1E28:
	ldr r4, [sp, #0x20]
	ldr r6, [r7, #0x0]
	add r5, r4, #0x800
	ldr r4, _020B1E9C ; =0x000001FF
	and r4, r4, r5, asr #0xc
	ldr r5, _020B1EA0 ; =0xFE00FF00
	and r6, r6, r5
	ldr r5, [sp, #0x24]
	add r5, r5, #0x800
	mov r5, r5, asr #0xc
	and r5, r5, #0xff
	orr r5, r6, r5
	orr r4, r5, r4, lsl #0x10
	str r4, [r7, #0x0]
_020B1E60:
	ldr r4, [sp, #0x0]
	add r4, r4, #0x1
	mov r4, r4, lsl #0x10
	mov r4, r4, lsr #0x10
	str r4, [sp, #0x0]
	cmp r4, r1
	blo _020B1B54
_020B1E7C:
	mov r0, r1
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B1E88: .word 0x01FF0000
_020B1E8C: .word 0xC000C000
_020B1E90: .word 0x020FF8AC
_020B1E94: .word 0x020FF894
_020B1E98: .word 0xC1FFFCFF
_020B1E9C: .word 0x000001FF
_020B1EA0: .word 0xFE00FF00

	arm_func_start FUN_020B1EA4
FUN_020B1EA4: ; 0x020B1EA4
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020B0518
_020B1EB0: ; 0x020B1EB0
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
_020B1EB8: ; 0x020B1EB8
	mov r0, r4
	bl FUN_020B1FC4
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020B1EC4
FUN_020B1EC4: ; 0x020B1EC4
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020B0534
_020B1ED0: ; 0x020B1ED0
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
_020B1ED8: ; 0x020B1ED8
	mov r0, r4
	bl FUN_020B1FC4
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020B1EE4
FUN_020B1EE4: ; 0x020B1EE4
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020B0438
	mov r0, r4
	bl FUN_020B1FC4
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020B1EFC
FUN_020B1EFC: ; 0x020B1EFC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov r4, r2
	ldr r2, [r4, #0xc]
	mov r5, r1
	ldr r1, [r2, #0x0]
	ldr r2, [sp, #0x34]
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x38]
	str r2, [sp, #0x4]
	mov r6, r3
	mov r7, r0
	ldr r12, [sp, #0x3c]
	str r1, [sp, #0x8]
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x2c]
	ldr r3, [sp, #0x30]
	mov r0, r6
	str r12, [sp, #0xc]
	bl FUN_020B45F0
	str r6, [r7, #0x34]
	str r4, [r7, #0x30]
	add r0, r7, #0x38
	mov r1, #0x1
	str r6, [r7, #0x34]
	bl FUN_020B1A68
	mov r0, r7
	bl FUN_020B04C0
	mov r0, r7
	mov r1, r5
	bl FUN_020B1EE4
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020B1F80
FUN_020B1F80: ; 0x020B1F80
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	str r2, [r5, #0x30]
	mvn r2, #0x0
	add r0, r5, #0x38
	mov r1, #0x1
	str r2, [r5, #0x34]
	bl FUN_020B1A68
	mov r0, r5
	bl FUN_020B04C0
	mov r0, r5
	mov r1, r4
	bl FUN_020B1EE4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020B1FC4
FUN_020B1FC4: ; 0x020B1FC4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r1, [r5, #0x0]
	ldrh r1, [r1, #0x4]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
_020B1FE4: ; 0x020B1FE4
	bl FUN_020B06E0
	mov r4, r0
	ldr r7, [r5, #0x30]
	ldrh r1, [r4, #0x0]
	mov r0, r7
	bl FUN_020AFE8C
	str r0, [r5, #0x2c]
	ldr r1, [r5, #0x18]
	add r0, r5, #0x38
	ldr r2, [r1, #0x4]
	mov r1, #0x1
	and r6, r2, #0xff
	bl FUN_020B1A68
_020B2018: ; 0x020B2018
	cmp r6, #0x0
	beq _020B2068
	cmp r6, #0x2
	bne _020B203C
	ldrsh r1, [r4, #0x4]
	ldrsh r2, [r4, #0x6]
	add r0, r5, #0x38
	bl FUN_020B1AB4
	b _020B2068
_020B203C:
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0x8]
	add r0, r5, #0x38
	bl FUN_020B1A78
	ldrh r1, [r4, #0x2]
	add r0, r5, #0x38
	bl FUN_020B1A98
	ldrsh r1, [r4, #0xc]
	ldrsh r2, [r4, #0xe]
	add r0, r5, #0x38
	bl FUN_020B1AB4
_020B2068:
	ldr r2, [r7, #0xc]
	cmp r2, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
_020B2084: ; 0x020B2084
	ldr r1, [r5, #0x34]
	mvn r0, #0x0
	cmp r1, r0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
_020B20A4: ; 0x020B20A4
	ldrh r1, [r4, #0x0]
	ldr r2, [r2, #0x4]
	ldr r0, [r5, #0x34]
	add r3, r2, r1, lsl #0x3
	ldr r1, [r2, r1, lsl #0x3]
	ldr r2, [r3, #0x4]
	bl FUN_020B4400
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020B20C8
FUN_020B20C8: ; 0x020B20C8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r6, #0x0
	str r6, [r0, #0x38]
	ldr r7, [sp, #0x30]
	str r6, [r0, #0x30]
	mov r10, r1
	str r7, [r0, #0x34]
	str r0, [sp, #0x0]
	movs r8, r3
	mov r9, r2
	str r10, [r0, #0x3c]
	ldr r11, [sp, #0x34]
	beq _020B215C
	mov r0, #0x1
	str r6, [sp, #0x8]
	str r0, [sp, #0x4]
_020B210C:
	mov r0, #0x28
	mul r4, r6, r0
	ldr r1, [sp, #0x4]
	add r0, r10, r4
	bl FUN_020B1AD4
	mov r0, #0x54
	mla r5, r6, r0, r9
	ldr r1, [sp, #0x8]
	mov r0, r7
	str r5, [r10, r4]
	bl FUN_020AFC04
	mov r1, r0
	mov r0, r5
	mov r2, r11
	bl FUN_020B1F80
	add r0, r6, #0x1
	mov r0, r0, lsl #0x10
	mov r6, r0, lsr #0x10
	cmp r6, r8
	blo _020B210C
_020B215C:
	ldr r0, [sp, #0x0]
	bl FUN_020B04C0
_020B2164: ; 0x020B2164
	ldr r0, [sp, #0x0]
	ldr r3, [sp, #0x38]
	ldr r2, [sp, #0x0]
	add r0, r0, #0x44
	mov r1, #0x1
	str r3, [r2, #0x40]
	bl FUN_020B1A68
_020B2180: ; 0x020B2180
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	strh r1, [r0, #0x2c]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020B2194
FUN_020B2194: ; 0x020B2194
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	bl FUN_020B0518
_020B21A4: ; 0x020B21A4
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
_020B21B0: ; 0x020B21B0
	mov r0, r7
	bl FUN_020B06E0
	mov r4, r0
	ldrh r1, [r4, #0x0]
	ldr r0, [r7, #0x40]
	bl FUN_020AFF34
	ldr r1, [r7, #0x18]
	mov r6, r0
	ldr r1, [r1, #0x4]
	add r0, r7, #0x44
	and r5, r1, #0xff
	mov r1, #0x1
	bl FUN_020B1A68
_020B21E4: ; 0x020B21E4
	cmp r5, #0x0
	beq _020B2234
	cmp r5, #0x2
	bne _020B2208
	ldrsh r1, [r4, #0x4]
	ldrsh r2, [r4, #0x6]
	add r0, r7, #0x44
	bl FUN_020B1AB4
	b _020B2234
_020B2208:
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0x8]
	add r0, r7, #0x44
	bl FUN_020B1A78
	ldrh r1, [r4, #0x2]
	add r0, r7, #0x44
	bl FUN_020B1A98
	ldrsh r1, [r4, #0xc]
	ldrsh r2, [r4, #0xe]
	add r0, r7, #0x44
	bl FUN_020B1AB4
_020B2234:
	ldrh r2, [r7, #0x2c]
	mov r1, r6
	add r0, r7, #0x30
	bl FUN_020B24E0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020B224C
FUN_020B224C: ; 0x020B224C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldr r2, [r4, #0x0]
	mov r6, r1
	ldrh r5, [r2, #0x4]
	bl FUN_020B0534
_020B2268: ; 0x020B2268
	cmp r0, #0x0
	beq _020B2318
	ldrh r1, [r4, #0x2c]
	mov r0, r4
	add r1, r1, r5
	strh r1, [r4, #0x2c]
	bl FUN_020B06E0
	mov r5, r0
	ldrh r1, [r5, #0x0]
	ldr r0, [r4, #0x40]
	bl FUN_020AFF34
	ldr r1, [r4, #0x18]
	mov r7, r0
	ldr r1, [r1, #0x4]
	add r0, r4, #0x44
	and r6, r1, #0xff
	mov r1, #0x1
	bl FUN_020B1A68
_020B22B0: ; 0x020B22B0
	cmp r6, #0x0
	beq _020B2300
	cmp r6, #0x2
	bne _020B22D4
	ldrsh r1, [r5, #0x4]
	ldrsh r2, [r5, #0x6]
	add r0, r4, #0x44
	bl FUN_020B1AB4
	b _020B2300
_020B22D4:
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x8]
	add r0, r4, #0x44
	bl FUN_020B1A78
	ldrh r1, [r5, #0x2]
	add r0, r4, #0x44
	bl FUN_020B1A98
	ldrsh r1, [r5, #0xc]
	ldrsh r2, [r5, #0xe]
	add r0, r4, #0x44
	bl FUN_020B1AB4
_020B2300:
	ldrh r2, [r4, #0x2c]
	mov r1, r7
	add r0, r4, #0x30
	bl FUN_020B24E0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
_020B2318:
	mov r1, r6
	add r0, r4, #0x30
	bl FUN_020B232C
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020B232C
FUN_020B232C: ; 0x020B232C
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	ldr r0, [r7, #0x8]
	mov r6, r1
	cmp r0, #0x1
	bne _020B238C
	ldr r0, [r7, #0x0]
	ldr r4, [r7, #0xc]
	ldrh r0, [r0, #0x2]
	mov r5, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r8,pc}
_020B235C: ; 0x020B235C
	mov r8, #0x58
_020B2360:
	mla r0, r5, r8, r4
	mov r1, r6
	bl FUN_020B1EC4
	ldr r1, [r7, #0x0]
	add r0, r5, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r1, #0x2]
	mov r5, r0, lsr #0x10
	cmp r5, r1
	blo _020B2360
	ldmia sp!, {r4-r8,pc}
_020B238C:
	ldr r0, [r7, #0x0]
	ldr r4, [r7, #0xc]
	ldrh r0, [r0, #0x0]
	mov r5, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r8,pc}
_020B23A4: ; 0x020B23A4
	mov r8, #0x28
_020B23A8:
	mul r0, r5, r8
	ldr r0, [r4, r0]
	mov r1, r6
	bl FUN_020B1EC4
	ldr r1, [r7, #0x0]
	add r0, r5, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r1, #0x0]
	mov r5, r0, lsr #0x10
	cmp r5, r1
	blo _020B23A8
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020B23D8
FUN_020B23D8: ; 0x020B23D8
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	ldrh r0, [r5, #0x0]
	mov r4, #0x0
	mov r6, r4
	cmp r0, #0x0
	bls _020B2424
_020B23F4:
	mov r0, r5
	mov r1, r6
	bl FUN_020AFF34
	ldrh r0, [r0, #0x0]
	ldrh r1, [r5, #0x0]
	cmp r0, r4
	movhi r4, r0
	add r0, r6, #0x1
	mov r0, r0, lsl #0x10
	mov r6, r0, lsr #0x10
	cmp r6, r1
	blo _020B23F4
_020B2424:
	mov r0, r4
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020B242C
FUN_020B242C: ; 0x020B242C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	bl FUN_020B0438
	mov r1, #0x0
	mov r0, r7
	strh r1, [r7, #0x2c]
	bl FUN_020B06E0
	mov r4, r0
	ldrh r1, [r4, #0x0]
	ldr r0, [r7, #0x40]
	bl FUN_020AFF34
	ldr r1, [r7, #0x18]
	mov r6, r0
	ldr r1, [r1, #0x4]
	add r0, r7, #0x44
	and r5, r1, #0xff
	mov r1, #0x1
	bl FUN_020B1A68
_020B2478: ; 0x020B2478
	cmp r5, #0x0
	beq _020B24C8
	cmp r5, #0x2
	bne _020B249C
	ldrsh r1, [r4, #0x4]
	ldrsh r2, [r4, #0x6]
	add r0, r7, #0x44
	bl FUN_020B1AB4
	b _020B24C8
_020B249C:
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0x8]
	add r0, r7, #0x44
	bl FUN_020B1A78
	ldrh r1, [r4, #0x2]
	add r0, r7, #0x44
	bl FUN_020B1A98
	ldrsh r1, [r4, #0xc]
	ldrsh r2, [r4, #0xe]
	add r0, r7, #0x44
	bl FUN_020B1AB4
_020B24C8:
	ldrh r2, [r7, #0x2c]
	mov r1, r6
	add r0, r7, #0x30
	bl FUN_020B24E0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020B24E0
FUN_020B24E0: ; 0x020B24E0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r10, r1
	str r0, [sp, #0x0]
	str r10, [r0, #0x0]
	ldr r0, [r0, #0x8]
	mov r9, r2
	cmp r0, #0x1
	bne _020B2654
	ldrh r1, [r10, #0x2]
	ldr r0, [sp, #0x0]
	mov r4, #0x0
	ldr r8, [r0, #0xc]
	cmp r1, #0x0
	bls _020B2544
	mov r3, r4
	mov r0, #0x58
_020B2524:
	mla r1, r4, r0, r8
	str r3, [r1, #0x54]
	add r1, r4, #0x1
	mov r1, r1, lsl #0x10
	ldrh r2, [r10, #0x2]
	mov r4, r1, lsr #0x10
	cmp r4, r2
	blo _020B2524
_020B2544:
	ldrh r0, [r10, #0x0]
	mov r5, #0x0
	cmp r0, #0x0
	addls sp, sp, #0x14
	ldmlsia sp!, {r4-r11,pc}
_020B2558: ; 0x020B2558
	str r5, [sp, #0x4]
	mov r11, #0x1
_020B2560:
	ldr r0, [r10, #0x4]
	mov r1, #0x58
	add r7, r0, r5, lsl #0x3
	ldrh r0, [r7, #0x6]
	and r0, r0, #0xff00
	mov r0, r0, lsl #0x8
	mov r0, r0, lsr #0x10
	mla r6, r0, r1, r8
	ldr r0, [r6, #0x54]
	cmp r0, #0x0
	bne _020B2634
	ldr r0, [sp, #0x0]
	ldrh r1, [r7, #0x0]
	ldr r0, [r0, #0x4]
	bl FUN_020AFC04
	mov r4, r0
	mov r0, r6
	mov r1, r4
	bl FUN_020B1EE4
	str r11, [r6, #0x8]
	ldrh r0, [r7, #0x6]
	and r0, r0, #0xf
	cmp r0, #0x1
	bne _020B2630
	ldrh r1, [r4, #0x0]
	ldr r7, [sp, #0x4]
	mov r3, r7
	cmp r1, #0x0
	bls _020B25F0
	ldr r2, [r4, #0xc]
_020B25D8:
	add r0, r2, r3, lsl #0x3
	ldrh r0, [r0, #0x4]
	add r3, r3, #0x1
	cmp r3, r1
	add r7, r7, r0
	blo _020B25D8
_020B25F0:
	mov r0, r6
	bl FUN_020B0408
_020B25F8: ; 0x020B25F8
	cmp r0, #0x0
	beq _020B261C
	mov r0, r9
	mov r1, r7
	bl _u32_div_f
	mov r0, r6
	mov r1, r1, lsl #0xc
	bl FUN_020B1EC4
	b _020B2630
_020B261C:
	cmp r9, r7
	movcc r7, r9
	mov r0, r6
	mov r1, r7, lsl #0xc
	bl FUN_020B1EC4
_020B2630:
	str r11, [r6, #0x54]
_020B2634:
	add r0, r5, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r10, #0x0]
	mov r5, r0, lsr #0x10
	cmp r5, r1
	blo _020B2560
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,pc}
_020B2654:
	ldrh r1, [r10, #0x0]
	ldr r0, [sp, #0x0]
	mov r4, #0x0
	cmp r1, #0x0
	ldr r11, [r0, #0xc]
	addls sp, sp, #0x14
	ldmlsia sp!, {r4-r11,pc}
_020B2670: ; 0x020B2670
	mov r0, #0x1
	str r4, [sp, #0xc]
	str r0, [sp, #0x8]
_020B267C:
	mov r0, #0x28
	mul r2, r4, r0
	ldr r3, [r10, #0x4]
	mov r0, r4, lsl #0x3
	ldrh r1, [r3, r0]
	ldr r0, [sp, #0x0]
	ldr r6, [r11, r2]
	ldr r0, [r0, #0x4]
	add r7, r3, r4, lsl #0x3
	bl FUN_020AFC04
	mov r5, r0
	mov r0, r6
	mov r1, r5
	bl FUN_020B1EE4
	ldr r0, [sp, #0x8]
	str r0, [r6, #0x8]
	ldrh r0, [r7, #0x6]
	and r0, r0, #0xf
	cmp r0, #0x1
	bne _020B2740
	ldrh r1, [r5, #0x0]
	ldr r8, [sp, #0xc]
	mov r0, r8
	cmp r1, #0x0
	bls _020B2700
	ldr r3, [r5, #0xc]
_020B26E4:
	add r1, r3, r0, lsl #0x3
	ldrh r2, [r1, #0x4]
	add r0, r0, #0x1
	ldrh r1, [r5, #0x0]
	add r8, r8, r2
	cmp r0, r1
	blo _020B26E4
_020B2700:
	mov r0, r6
	bl FUN_020B0408
_020B2708: ; 0x020B2708
	cmp r0, #0x0
	beq _020B272C
	mov r0, r9
	mov r1, r8
	bl _u32_div_f
	mov r0, r6
	mov r1, r1, lsl #0xc
	bl FUN_020B1EC4
	b _020B2740
_020B272C:
	cmp r9, r8
	movcc r8, r9
	mov r0, r6
	mov r1, r8, lsl #0xc
	bl FUN_020B1EC4
_020B2740:
	mov r0, #0x28
	mla r3, r4, r0, r11
	ldr r0, [sp, #0x8]
	str r0, [r3, #0x8]
	ldrsh r1, [r7, #0x2]
	ldrsh r2, [r7, #0x4]
	add r0, r3, #0xc
	bl FUN_020B1AB4
	add r0, r4, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r10, #0x0]
	mov r4, r0, lsr #0x10
	cmp r4, r1
	blo _020B267C
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,pc}

	arm_func_start thunk_FUN_020b5040
thunk_FUN_020b5040: ; 0x020B2780
	ldr ip, _020B2788 ; =FUN_020B5040
	bx r12
	.balign 4
_020B2788: .word FUN_020B5040

	arm_func_start FUN_020B278C
FUN_020B278C:
	ldr r0, [r0, #0x78]
	bx lr

	arm_func_start FUN_020B2794
FUN_020B2794: ; 0x020B2794
	stmdb sp!, {lr}
	sub sp, sp, #0x1c
	ldr r2, _020B2894 ; =0x021CDD70
	mov lr, #0x0
	ldr r12, [r2, #0x0]
	ldr r3, _020B2898 ; =0x021CDEF4
	mov r2, #0x18
	str r1, [sp, #0x0]
	str r1, [sp, #0xc]
	mla r1, r12, r2, r3
	rsb r3, r0, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0x0
	mov r2, r1
	str r3, [sp, #0x8]
	str lr, [sp, #0x10]
	str lr, [sp, #0x14]
	bl FUN_020B423C
	ldr r0, _020B2894 ; =0x021CDD70
	ldr r1, _020B289C ; =0x021CE1F4
	ldr r2, [r0, #0x0]
	mov r0, #0x18
	mla r1, r2, r0, r1
	add r0, sp, #0x0
	mov r2, r1
	bl FUN_020B423C
	ldr r0, _020B28A0 ; =0x021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020B2824
	ldr r1, _020B28A4 ; =0x02106570
	ldr r0, _020B28A8 ; =0x0000FFFE
	ldrh r1, [r1, #0x0]
	cmp r1, r0
	movne r0, #0x1
	bne _020B2828
_020B2824:
	mov r0, #0x0
_020B2828:
	cmp r0, #0x0
	ldreq r1, _020B2894 ; =0x021CDD70
	ldreq r0, _020B28A4 ; =0x02106570
	ldreq r1, [r1, #0x0]
	streqh r1, [r0, #0x0]
	ldr r0, _020B2894 ; =0x021CDD70
	ldr r1, _020B28AC ; =0x021CDDF4
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x10
	add r12, r1, r0, lsr #0xd
	ldrh r0, [r12, #0x4]
	cmp r0, #0x3
	addls pc, pc, r0, lsl #0x2
	b _020B288C
_020B2860:
	b _020B2870
_020B2864:
	b _020B288C
_020B2868:
	b _020B2870
_020B286C:
	b _020B2870
_020B2870:
	ldr r0, _020B28B0 ; =0x021CDD64
	mov r1, #0x1
	ldrh r3, [r0, #0x0]
	add r2, r3, #0x1
	strh r2, [r0, #0x0]
	strh r3, [r12, #0x2]
	strh r1, [r12, #0x4]
_020B288C:
	add sp, sp, #0x1c
	ldmia sp!, {pc}
	.balign 4
_020B2894: .word 0x021CDD70
_020B2898: .word 0x021CDEF4
_020B289C: .word 0x021CE1F4
_020B28A0: .word 0x021CDD68
_020B28A4: .word 0x02106570
_020B28A8: .word 0x0000FFFE
_020B28AC: .word 0x021CDDF4
_020B28B0: .word 0x021CDD64

	arm_func_start FUN_020B28B4
FUN_020B28B4: ; 0x020B28B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x1c
	ldr r2, _020B29E8 ; =0x021CDD70
	mov r12, #0x0
	ldr r3, [r2, #0x0]
	mov r4, r1
	ldr r2, _020B29EC ; =0x021CDEF4
	mov r1, #0x18
	mla r1, r3, r1, r2
	mov r5, r0
	add r0, sp, #0x0
	mov r2, r1
	str r5, [sp, #0x0]
	str r12, [sp, #0x4]
	str r12, [sp, #0x8]
	str r4, [sp, #0xc]
	str r12, [sp, #0x10]
	str r12, [sp, #0x14]
	bl FUN_020B423C
	mov r0, r5
	bl FX_Inv
	mov r1, #0x0
	str r0, [sp, #0x0]
	mov r0, r4
	str r1, [sp, #0x4]
	str r1, [sp, #0x8]
	bl FX_Inv
	mov r3, #0x0
	ldr r1, _020B29E8 ; =0x021CDD70
	str r0, [sp, #0xc]
	ldr r2, [r1, #0x0]
	ldr r1, _020B29F0 ; =0x021CE1F4
	mov r0, #0x18
	mla r1, r2, r0, r1
	add r0, sp, #0x0
	mov r2, r1
	str r3, [sp, #0x10]
	str r3, [sp, #0x14]
	bl FUN_020B423C
	ldr r0, _020B29F4 ; =0x021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020B2978
	ldr r1, _020B29F8 ; =0x02106570
	ldr r0, _020B29FC ; =0x0000FFFE
	ldrh r1, [r1, #0x0]
	cmp r1, r0
	movne r0, #0x1
	bne _020B297C
_020B2978:
	mov r0, #0x0
_020B297C:
	cmp r0, #0x0
	ldreq r1, _020B29E8 ; =0x021CDD70
	ldreq r0, _020B29F8 ; =0x02106570
	ldreq r1, [r1, #0x0]
	streqh r1, [r0, #0x0]
	ldr r0, _020B29E8 ; =0x021CDD70
	ldr r1, _020B2A00 ; =0x021CDDF4
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x10
	add r12, r1, r0, lsr #0xd
	ldrh r0, [r12, #0x4]
	cmp r0, #0x3
	addls pc, pc, r0, lsl #0x2
	b _020B29E0
_020B29B4:
	b _020B29C4
_020B29B8:
	b _020B29E0
_020B29BC:
	b _020B29C4
_020B29C0:
	b _020B29C4
_020B29C4:
	ldr r0, _020B2A04 ; =0x021CDD64
	mov r1, #0x1
	ldrh r3, [r0, #0x0]
	add r2, r3, #0x1
	strh r2, [r0, #0x0]
	strh r3, [r12, #0x2]
	strh r1, [r12, #0x4]
_020B29E0:
	add sp, sp, #0x1c
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B29E8: .word 0x021CDD70
_020B29EC: .word 0x021CDEF4
_020B29F0: .word 0x021CE1F4
_020B29F4: .word 0x021CDD68
_020B29F8: .word 0x02106570
_020B29FC: .word 0x0000FFFE
_020B2A00: .word 0x021CDDF4
_020B2A04: .word 0x021CDD64

	arm_func_start FUN_020B2A08
FUN_020B2A08: ; 0x020B2A08
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x1c
	ldr r3, _020B2AEC ; =0x021CDD68
	mov r4, r2
	ldr r2, [r3, #0x0]
	cmp r2, #0x0
	beq _020B2A6C
	ldr r2, _020B2AF0 ; =0x021CDD70
	mov r3, #0x18
	ldr r2, [r2, #0x0]
	ldr lr, _020B2AF4 ; =0x021CDF04
	mul r5, r2, r3
	ldr r3, [lr, r5]
	ldr ip, _020B2AF8 ; =0x021CDF08
	add r0, r3, r0
	str r0, [lr, r5]
	ldr r0, [r12, r5]
	ldr r3, _020B2AFC ; =0x021CDD74
	add r0, r0, r1
	str r0, [r12, r5]
	ldr r0, [r3, r2, lsl #0x2]
	add sp, sp, #0x1c
	add r0, r0, r4
	str r0, [r3, r2, lsl #0x2]
	ldmia sp!, {r4-r5,pc}
_020B2A6C:
	ldr r2, _020B2AF0 ; =0x021CDD70
	mov lr, #0x1000
	ldr r12, [r2, #0x0]
	ldr r3, _020B2B00 ; =0x021CDEF4
	mov r2, #0x18
	str r1, [sp, #0x14]
	mla r1, r12, r2, r3
	mov r3, #0x0
	str r0, [sp, #0x10]
	add r0, sp, #0x0
	mov r2, r1
	str lr, [sp, #0x0]
	str r3, [sp, #0x4]
	str r3, [sp, #0x8]
	str lr, [sp, #0xc]
	bl FUN_020B423C
	ldr r0, _020B2AF0 ; =0x021CDD70
	ldr r1, _020B2B04 ; =0x021CE1F4
	ldr r2, [r0, #0x0]
	mov r0, #0x18
	mla r1, r2, r0, r1
	add r0, sp, #0x0
	mov r2, r1
	bl FUN_020B423C
	ldr r0, _020B2AF0 ; =0x021CDD70
	ldr r2, _020B2AFC ; =0x021CDD74
	ldr r1, [r0, #0x0]
	ldr r0, [r2, r1, lsl #0x2]
	add r0, r0, r4
	str r0, [r2, r1, lsl #0x2]
	add sp, sp, #0x1c
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B2AEC: .word 0x021CDD68
_020B2AF0: .word 0x021CDD70
_020B2AF4: .word 0x021CDF04
_020B2AF8: .word 0x021CDF08
_020B2AFC: .word 0x021CDD74
_020B2B00: .word 0x021CDEF4
_020B2B04: .word 0x021CE1F4

	arm_func_start FUN_020B2B08
FUN_020B2B08: ; 0x020B2B08
	ldr r0, _020B2B4C ; =0x021CDD70
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	movle r0, #0x1
	movgt r0, #0x0
	cmp r0, #0x0
	bxne lr
	ldr r1, _020B2B4C ; =0x021CDD70
	ldr r0, _020B2B50 ; =0x02106570
	ldr r3, [r1, #0x0]
	ldrh r2, [r0, #0x0]
	sub r3, r3, #0x1
	str r3, [r1, #0x0]
	cmp r2, r3
	ldrgt r1, _020B2B54 ; =0x0000FFFE
	strgth r1, [r0, #0x0]
	bx lr
	.balign 4
_020B2B4C: .word 0x021CDD70
_020B2B50: .word 0x02106570
_020B2B54: .word 0x0000FFFE

	arm_func_start FUN_020B2B58
FUN_020B2B58: ; 0x020B2B58
	stmdb sp!, {r4-r10,lr}
	ldr r0, _020B2D74 ; =0x021CDD6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x7c]
	ands r0, r0, #0x1
	bne _020B2CA4
	ldr r0, _020B2D78 ; =0x021CDD70
	ldr r1, [r0, #0x0]
	mov r0, r1, lsl #0x10
	add r5, r1, #0x1
	cmp r5, #0x20
	mov r4, r0, lsr #0x10
	movlt r0, #0x1
	movge r0, #0x0
	cmp r0, #0x0
	beq _020B2C44
	ldr r0, _020B2D7C ; =0x021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020B2BE4
	ldr r1, _020B2D78 ; =0x021CDD70
	mov r0, #0x18
	ldr r3, [r1, #0x0]
	ldr r1, _020B2D80 ; =0x021CDD74
	mul r8, r3, r0
	ldr r6, _020B2D84 ; =0x021CDF04
	mul r7, r5, r0
	ldr r2, [r6, r8]
	ldr r0, [r1, r3, lsl #0x2]
	ldr r3, _020B2D88 ; =0x021CDF08
	str r2, [r6, r7]
	ldr r2, [r3, r8]
	str r0, [r1, r5, lsl #0x2]
	str r2, [r3, r7]
	b _020B2C3C
_020B2BE4:
	ldr r1, _020B2D78 ; =0x021CDD70
	mov r0, #0x18
	ldr r2, [r1, #0x0]
	ldr r7, _020B2D80 ; =0x021CDD74
	mul lr, r2, r0
	ldr r1, _020B2D8C ; =0x021CDEF4
	mul r12, r5, r0
	ldr r8, _020B2D90 ; =0x021CE1F4
	add r10, r1, lr
	ldr r6, [r7, r2, lsl #0x2]
	add r9, r1, r12
	ldmia r10!, {r0-r3}
	stmia r9!, {r0-r3}
	ldmia r10, {r0-r1}
	str r6, [r7, r5, lsl #0x2]
	add r7, r8, lr
	stmia r9, {r0-r1}
	add r6, r8, r12
	ldmia r7!, {r0-r3}
	stmia r6!, {r0-r3}
	ldmia r7, {r0-r1}
	stmia r6, {r0-r1}
_020B2C3C:
	ldr r0, _020B2D78 ; =0x021CDD70
	str r5, [r0, #0x0]
_020B2C44:
	ldr r0, _020B2D78 ; =0x021CDD70
	ldr r2, _020B2D94 ; =0x021CDDF4
	ldr r0, [r0, #0x0]
	mov r5, r4, lsl #0x3
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	add r4, r2, r4, lsl #0x3
	mov r6, r3, lsl #0x3
	ldrh r1, [r2, r5]
	ldrh r0, [r4, #0x2]
	add r3, r2, r3, lsl #0x3
	strh r1, [r2, r6]
	strh r0, [r3, #0x2]
	ldrh r2, [r4, #0x4]
	ldrh r0, [r4, #0x6]
	ldr r1, _020B2D98 ; =0x021CDDF8
	strh r2, [r3, #0x4]
	strh r0, [r3, #0x6]
	ldrh r0, [r1, r5]
	cmp r0, #0x1
	moveq r0, #0x2
	streqh r0, [r1, r6]
	strneh r0, [r1, r6]
	ldmia sp!, {r4-r10,pc}
_020B2CA4:
	ldr r0, _020B2D78 ; =0x021CDD70
	ldr r0, [r0, #0x0]
	add r4, r0, #0x1
	cmp r4, #0x20
	movlt r0, #0x1
	movge r0, #0x0
	cmp r0, #0x0
	ldmeqia sp!, {r4-r10,pc}
_020B2CC4: ; 0x020B2CC4
	ldr r0, _020B2D7C ; =0x021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020B2D10
	ldr r1, _020B2D78 ; =0x021CDD70
	mov r0, #0x18
	ldr r3, [r1, #0x0]
	ldr r1, _020B2D80 ; =0x021CDD74
	mul r7, r3, r0
	ldr r5, _020B2D84 ; =0x021CDF04
	mul r6, r4, r0
	ldr r2, [r5, r7]
	ldr r0, [r1, r3, lsl #0x2]
	ldr r3, _020B2D88 ; =0x021CDF08
	str r2, [r5, r6]
	ldr r2, [r3, r7]
	str r0, [r1, r4, lsl #0x2]
	str r2, [r3, r6]
	b _020B2D68
_020B2D10:
	ldr r1, _020B2D78 ; =0x021CDD70
	mov r0, #0x18
	ldr r2, [r1, #0x0]
	ldr ip, _020B2D80 ; =0x021CDD74
	mul r9, r2, r0
	ldr r1, _020B2D8C ; =0x021CDEF4
	mul r8, r4, r0
	ldr lr, _020B2D90 ; =0x021CE1F4
	add r6, r1, r9
	ldr r5, [r12, r2, lsl #0x2]
	add r7, r1, r8
	ldmia r6!, {r0-r3}
	stmia r7!, {r0-r3}
	ldmia r6, {r0-r1}
	add r6, lr, r9
	stmia r7, {r0-r1}
	add lr, lr, r8
	ldmia r6!, {r0-r3}
	stmia lr!, {r0-r3}
	ldmia r6, {r0-r1}
	stmia lr, {r0-r1}
	str r5, [r12, r4, lsl #0x2]
_020B2D68:
	ldr r0, _020B2D78 ; =0x021CDD70
	str r4, [r0, #0x0]
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020B2D74: .word 0x021CDD6C
_020B2D78: .word 0x021CDD70
_020B2D7C: .word 0x021CDD68
_020B2D80: .word 0x021CDD74
_020B2D84: .word 0x021CDF04
_020B2D88: .word 0x021CDF08
_020B2D8C: .word 0x021CDEF4
_020B2D90: .word 0x021CE1F4
_020B2D94: .word 0x021CDDF4
_020B2D98: .word 0x021CDDF8

	arm_func_start FUN_020B2D9C
FUN_020B2D9C: ; 0x020B2D9C
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	ldrh r0, [r4, #0x56]
	cmp r0, #0x0
	bne _020B2DBC
	add r0, r4, #0x30
	bl FUN_020B2E78
	ldmia sp!, {r4-r6,pc}
_020B2DBC:
	bl FUN_020B2B58
	ldrh r0, [r4, #0x56]
	ands r0, r0, #0x8
	beq _020B2E0C
	ldr r0, _020B2E70 ; =0x021CDD6C
	ldrsh r6, [r4, #0x52]
	ldr r0, [r0, #0x0]
	ldrsh r5, [r4, #0x50]
	bl FUN_020B4F88
_020B2DE0: ; 0x020B2DE0
	cmp r0, #0x0
	ldr r0, _020B2E70 ; =0x021CDD6C
	rsbne r5, r5, #0x0
	ldr r0, [r0, #0x0]
	bl FUN_020B4F74
_020B2DF4: ; 0x020B2DF4
	cmp r0, #0x0
	rsbne r6, r6, #0x0
	mov r0, r5, lsl #0xc
	mov r1, r6, lsl #0xc
	mov r2, #0x0
	bl FUN_020B2A08
_020B2E0C:
	ldrh r0, [r4, #0x56]
	ands r0, r0, #0x4
	beq _020B2E40
	ldrh r0, [r4, #0x54]
	ldr r2, _020B2E74 ; =0x020FFA38
	mov r0, r0, asr #0x4
	mov r1, r0, lsl #0x1
	add r0, r1, #0x1
	mov r3, r1, lsl #0x1
	mov r1, r0, lsl #0x1
	ldrsh r0, [r2, r3]
	ldrsh r1, [r2, r1]
	bl FUN_020B2794
_020B2E40:
	ldrh r0, [r4, #0x56]
	ands r0, r0, #0x2
	beq _020B2E5C
	ldr r0, [r4, #0x48]
	ldr r1, [r4, #0x4c]
	mov r2, #0x1000
	bl FUN_020B28B4
_020B2E5C:
	add r0, r4, #0x30
	bl FUN_020B2E78
	mov r0, #0x1
	bl FUN_020B2B08
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B2E70: .word 0x021CDD6C
_020B2E74: .word 0x020FFA38

	arm_func_start FUN_020B2E78
FUN_020B2E78: ; 0x020B2E78
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r5, r0
	ldr r0, [r5, #0x8]
	cmp r0, #0x1
	bne _020B309C
	ldr r0, [r5, #0x0]
	mov r2, #0x0
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	bls _020B2ED0
	ldr r3, _020B3174 ; =0x021CE8F4
	mov r4, r2
_020B2EAC:
	add r0, r3, r2, lsl #0x2
	str r4, [r0, #0x4]
	ldr r0, [r5, #0x0]
	add r2, r2, #0x1
	ldrh r1, [r0, #0x2]
	mov r0, r2, lsl #0x10
	mov r2, r0, lsr #0x10
	cmp r2, r1
	blo _020B2EAC
_020B2ED0:
	ldr r0, _020B3178 ; =0x021CDD6C
	mov r6, #0x1
	ldr r1, [r0, #0x0]
	ldr r0, _020B3174 ; =0x021CE8F4
	str r6, [r0, #0x404]
	ldr r0, [r1, #0x80]
	cmp r0, #0x0
	beq _020B2FD8
	bl FUN_020B4948
_020B2EF4: ; 0x020B2EF4
	str r0, [sp, #0x0]
	mov r0, r6
	bl FUN_020B497C
	ldr r0, _020B3178 ; =0x021CDD6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x80]
	bl FUN_020B4958
	ldr r2, [r5, #0x0]
	mov r7, #0x0
	ldrh r0, [r2, #0x0]
	cmp r0, #0x0
	bls _020B2FC0
	mov r11, r7
_020B2F28:
	ldr r0, [r2, #0x4]
	ldr r9, [r5, #0xc]
	add r10, r0, r7, lsl #0x3
	ldrh r0, [r10, #0x6]
	and r0, r0, #0xff00
	mov r0, r0, lsl #0x8
	mov r8, r0, lsr #0x10
	ldr r0, _020B3174 ; =0x021CE8F4
	strh r8, [r0, #0x0]
	bl FUN_020B2B58
	ldr r0, _020B3178 ; =0x021CDD6C
	ldrsh r4, [r10, #0x4]
	ldr r0, [r0, #0x0]
	ldrsh r10, [r10, #0x2]
	bl FUN_020B4F88
_020B2F64: ; 0x020B2F64
	cmp r0, #0x0
	ldr r0, _020B3178 ; =0x021CDD6C
	rsbne r10, r10, #0x0
	ldr r0, [r0, #0x0]
	bl FUN_020B4F74
_020B2F78: ; 0x020B2F78
	cmp r0, #0x0
	rsbne r4, r4, #0x0
	mov r2, r11
	mov r0, r10, lsl #0xc
	mov r1, r4, lsl #0xc
	bl FUN_020B2A08
	mov r0, #0x58
	mla r0, r8, r0, r9
	bl FUN_020B3554
	mov r0, r6
	bl FUN_020B2B08
	ldr r2, [r5, #0x0]
	add r0, r7, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r2, #0x0]
	mov r7, r0, lsr #0x10
	cmp r7, r1
	blo _020B2F28
_020B2FC0:
	mov r0, #0x0
	bl FUN_020B497C
_020B2FC8: ; 0x020B2FC8
	ldr r0, [sp, #0x0]
	bl FUN_020B4958
	bl FUN_020B4968
	b _020B3088
_020B2FD8:
	ldr r2, [r5, #0x0]
	mov r7, #0x0
	ldrh r0, [r2, #0x0]
	cmp r0, #0x0
	bls _020B3088
	str r7, [sp, #0x4]
	mov r11, #0x58
_020B2FF4:
	ldr r0, [r2, #0x4]
	ldr r9, [r5, #0xc]
	add r10, r0, r7, lsl #0x3
	ldrh r0, [r10, #0x6]
	and r0, r0, #0xff00
	mov r0, r0, lsl #0x8
	mov r8, r0, lsr #0x10
	ldr r0, _020B3174 ; =0x021CE8F4
	strh r8, [r0, #0x0]
	bl FUN_020B2B58
	ldr r0, _020B3178 ; =0x021CDD6C
	ldrsh r4, [r10, #0x4]
	ldr r0, [r0, #0x0]
	ldrsh r10, [r10, #0x2]
	bl FUN_020B4F88
_020B3030: ; 0x020B3030
	cmp r0, #0x0
	ldr r0, _020B3178 ; =0x021CDD6C
	rsbne r10, r10, #0x0
	ldr r0, [r0, #0x0]
	bl FUN_020B4F74
_020B3044: ; 0x020B3044
	cmp r0, #0x0
	rsbne r4, r4, #0x0
	ldr r2, [sp, #0x4]
	mov r0, r10, lsl #0xc
	mov r1, r4, lsl #0xc
	bl FUN_020B2A08
	mla r0, r8, r11, r9
	bl FUN_020B3554
	mov r0, r6
	bl FUN_020B2B08
	ldr r2, [r5, #0x0]
	add r0, r7, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r2, #0x0]
	mov r7, r0, lsr #0x10
	cmp r7, r1
	blo _020B2FF4
_020B3088:
	ldr r0, _020B3174 ; =0x021CE8F4
	mov r1, #0x0
	str r1, [r0, #0x404]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
_020B309C:
	ldr r0, _020B3178 ; =0x021CDD6C
	ldr r7, [r5, #0xc]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x80]
	cmp r0, #0x0
	beq _020B312C
	bl FUN_020B4948
	mov r6, r0
	mov r0, #0x1
	bl FUN_020B497C
	ldr r0, _020B3178 ; =0x021CDD6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x80]
	bl FUN_020B4958
_020B30D4: ; 0x020B30D4
	ldr r0, [r5, #0x0]
	mov r4, #0x0
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	bls _020B3110
	mov r8, #0x28
_020B30EC:
	mla r0, r4, r8, r7
	bl FUN_020B3474
	ldr r1, [r5, #0x0]
	add r0, r4, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r1, #0x0]
	mov r4, r0, lsr #0x10
	cmp r4, r1
	blo _020B30EC
_020B3110:
	mov r0, #0x0
	bl FUN_020B497C
	mov r0, r6
	bl FUN_020B4958
	bl FUN_020B4968
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
_020B312C:
	ldr r0, [r5, #0x0]
	mov r4, #0x0
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	addls sp, sp, #0xc
	ldmlsia sp!, {r4-r11,pc}
_020B3144: ; 0x020B3144
	mov r6, #0x28
_020B3148:
	mla r0, r4, r6, r7
	bl FUN_020B3474
	ldr r1, [r5, #0x0]
	add r0, r4, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r1, #0x0]
	mov r4, r0, lsr #0x10
	cmp r4, r1
	blo _020B3148
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B3174: .word 0x021CE8F4
_020B3178: .word 0x021CDD6C

	arm_func_start FUN_020B317C
FUN_020B317C: ; 0x020B317C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _020B31EC ; =0x021CDD6C
	mov r5, r0
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x80]
	cmp r1, #0x0
	beq _020B31E0
	bl FUN_020B4948
	mov r4, r0
	mov r0, #0x1
	bl FUN_020B497C
	ldr r0, _020B31EC ; =0x021CDD6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x80]
	bl FUN_020B4958
	mov r0, r5
	bl FUN_020B3554
_020B31C4: ; 0x020B31C4
	mov r0, #0x0
	bl FUN_020B497C
	mov r0, r4
	bl FUN_020B4958
	bl FUN_020B4968
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020B31E0:
	bl FUN_020B3554
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B31EC: .word 0x021CDD6C

	arm_func_start FUN_020B31F0
FUN_020B31F0: ; 0x020B31F0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020B3260 ; =0x04000448
	mov r2, #0x1
	ldr r0, _020B3264 ; =0x021CDD6C
	str r2, [r1, #0x0]
	ldr r2, [r0, #0x0]
	ldr r3, [r2, #0x7c]
	cmp r3, #0x0
	beq _020B324C
	ands r0, r3, #0x1
	ldrne r0, _020B3268 ; =0x021CDD68
	movne r1, #0x0
	strne r1, [r0, #0x0]
	ands r0, r3, #0x2
	beq _020B323C
	mov r0, #0x0
	str r0, [r2, #0x74]
	bl FUN_020B4DA0
_020B323C:
	ldr r0, _020B3264 ; =0x021CDD6C
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x7c]
_020B324C:
	ldr r0, _020B3264 ; =0x021CDD6C
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B3260: .word 0x04000448
_020B3264: .word 0x021CDD6C
_020B3268: .word 0x021CDD68

	arm_func_start FUN_020B326C
FUN_020B326C: ; 0x020B326C
	stmdb sp!, {r4-r8,lr}
	ldr r5, _020B330C ; =0x021CDD60
	ldr r3, _020B3310 ; =0x021CDD6C
	ldrh r6, [r5, #0x0]
	ldr r2, _020B3314 ; =0x021CDD70
	mov r4, #0x0
	ldr r7, _020B3318 ; =0x0000FFFE
	ldr r1, _020B331C ; =0x02106570
	str r0, [r3, #0x0]
	str r4, [r2, #0x0]
	strh r7, [r1, #0x0]
	cmp r6, #0x0
	ble _020B32D0
	ldr r8, _020B3320 ; =0x021CE4F4
	mvn r7, #0x0
	mov r6, #0x10
_020B32AC:
	mov r0, r7
	mov r2, r6
	add r1, r8, #0x10
	bl MIi_CpuClearFast
	ldrh r0, [r5, #0x0]
	add r4, r4, #0x1
	add r8, r8, #0x20
	cmp r4, r0
	blt _020B32AC
_020B32D0:
	ldr r4, _020B330C ; =0x021CDD60
	mov r0, #0x0
	ldr r3, _020B3324 ; =0x021CDD64
	ldr r1, _020B3328 ; =0x021CDDF4
	mov r2, #0x100
	strh r0, [r4, #0x0]
	strh r0, [r3, #0x0]
	bl MIi_CpuClearFast
	ldr r1, _020B332C ; =0x04000444
	mov r2, #0x0
	ldr r0, _020B3330 ; =0x04000454
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	bl FUN_020B4178
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020B330C: .word 0x021CDD60
_020B3310: .word 0x021CDD6C
_020B3314: .word 0x021CDD70
_020B3318: .word 0x0000FFFE
_020B331C: .word 0x02106570
_020B3320: .word 0x021CE4F4
_020B3324: .word 0x021CDD64
_020B3328: .word 0x021CDDF4
_020B332C: .word 0x04000444
_020B3330: .word 0x04000454

	arm_func_start FUN_020B3334
FUN_020B3334: ; 0x020B3334
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r1, r4
	mov r0, #0x0
	mov r2, #0x48
	bl MIi_CpuClear16
	mov r0, #0x1
	str r0, [r4, #0x10]
	mov r0, #0x3
	ldr r1, _020B3380 ; =FUN_020B3EE0
	str r0, [r4, #0x14]
	ldr r0, _020B3384 ; =FUN_020B3E48
	str r1, [r4, #0x18]
	ldr r1, _020B3388 ; =FUN_020B3C40
	str r0, [r4, #0x1c]
	ldr r0, _020B338C ; =FUN_020B3B90
	str r1, [r4, #0x20]
	str r0, [r4, #0x24]
	ldmia sp!, {r4,pc}
	.balign 4
_020B3380: .word FUN_020B3EE0
_020B3384: .word FUN_020B3E48
_020B3388: .word FUN_020B3C40
_020B338C: .word FUN_020B3B90

	arm_func_start FUN_020B3390
FUN_020B3390: ; 0x020B3390
	ldr r2, [r0, #0x70]
	str r2, [r1, #0x30]
	str r1, [r0, #0x70]
	bx lr

	arm_func_start FUN_020B33A0
FUN_020B33A0: ; 0x020B33A0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r0
	bl FUN_020B504C
	mov r7, #0x0
	str r7, [r4, #0x70]
	str r7, [r4, #0x74]
	str r7, [r4, #0x78]
	str r7, [r4, #0x7c]
	str r7, [r4, #0x80]
	str r7, [r4, #0x84]
	strh r7, [r4, #0x88]
	strh r7, [r4, #0x8a]
	str r7, [r4, #0x8c]
	str r7, [r4, #0x90]
	ldr r1, _020B3454 ; =0x021CDD70
	strh r7, [r4, #0x94]
	ldr r2, _020B3458 ; =0x0000FFFE
	ldr r0, _020B345C ; =0x02106570
	ldr r6, _020B3460 ; =0x021CE4F4
	str r7, [r1, #0x0]
	strh r2, [r0, #0x0]
	mvn r5, #0x0
	mov r4, #0x10
_020B3400:
	mov r0, r5
	mov r2, r4
	add r1, r6, #0x10
	bl MIi_CpuClearFast
	add r7, r7, #0x1
	cmp r7, #0x20
	add r6, r6, #0x20
	blt _020B3400
	ldr ip, _020B3464 ; =0x021CDD60
	mov r0, #0x0
	ldr r3, _020B3468 ; =0x021CDD64
	ldr r1, _020B346C ; =0x021CDDF4
	mov r2, #0x100
	strh r0, [r12, #0x0]
	strh r0, [r3, #0x0]
	bl MIi_CpuClearFast
	ldr r0, _020B3470 ; =0x021CDD68
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B3454: .word 0x021CDD70
_020B3458: .word 0x0000FFFE
_020B345C: .word 0x02106570
_020B3460: .word 0x021CE4F4
_020B3464: .word 0x021CDD60
_020B3468: .word 0x021CDD64
_020B346C: .word 0x021CDDF4
_020B3470: .word 0x021CDD68

	arm_func_start FUN_020B3474
FUN_020B3474: ; 0x020B3474
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
_020B3490: ; 0x020B3490
	ldr r4, [r5, #0x0]
	bl FUN_020B2B58
	ldrh r0, [r5, #0x1e]
	ands r0, r0, #0x8
	beq _020B34E4
	ldr r0, _020B354C ; =0x021CDD6C
	ldrsh r7, [r5, #0x1a]
	ldr r0, [r0, #0x0]
	ldrsh r6, [r5, #0x18]
	bl FUN_020B4F88
_020B34B8: ; 0x020B34B8
	cmp r0, #0x0
	ldr r0, _020B354C ; =0x021CDD6C
	rsbne r6, r6, #0x0
	ldr r0, [r0, #0x0]
	bl FUN_020B4F74
_020B34CC: ; 0x020B34CC
	cmp r0, #0x0
	rsbne r7, r7, #0x0
	mov r0, r6, lsl #0xc
	mov r1, r7, lsl #0xc
	mov r2, #0x0
	bl FUN_020B2A08
_020B34E4:
	ldrh r0, [r5, #0x1e]
	ands r0, r0, #0x4
	beq _020B3518
	ldrh r0, [r5, #0x1c]
	ldr r2, _020B3550 ; =0x020FFA38
	mov r0, r0, asr #0x4
	mov r1, r0, lsl #0x1
	add r0, r1, #0x1
	mov r3, r1, lsl #0x1
	mov r1, r0, lsl #0x1
	ldrsh r0, [r2, r3]
	ldrsh r1, [r2, r1]
	bl FUN_020B2794
_020B3518:
	ldrh r0, [r5, #0x1e]
	ands r0, r0, #0x2
	beq _020B3534
	ldr r0, [r5, #0x10]
	ldr r1, [r5, #0x14]
	mov r2, #0x1000
	bl FUN_020B28B4
_020B3534:
	mov r0, r4
	bl FUN_020B3554
	mov r0, #0x1
	bl FUN_020B2B08
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B354C: .word 0x021CDD6C
_020B3550: .word 0x020FFA38

	arm_func_start FUN_020B3554
FUN_020B3554:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrh r0, [r5, #0x4a]
	ldr r4, [r5, #0x2c]
	cmp r0, #0x0
	bne _020B35C0
	ldr r2, [r5, #0x34]
	mvn r0, #0x0
	cmp r2, r0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020B35B0
	ldr r1, _020B36B4 ; =0x02106574
	mov r0, r4
	str r2, [r1, #0x0]
	bl FUN_020B36C0
	ldr r0, _020B36B4 ; =0x02106574
	mvn r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
_020B35B0:
	mov r0, r4
	bl FUN_020B36C0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
_020B35C0:
	bl FUN_020B2B58
	ldrh r0, [r5, #0x4a]
	ands r0, r0, #0x8
	beq _020B3610
	ldr r0, _020B36B8 ; =0x021CDD6C
	ldrsh r7, [r5, #0x46]
	ldr r0, [r0, #0x0]
	ldrsh r6, [r5, #0x44]
	bl FUN_020B4F88
_020B35E4: ; 0x020B35E4
	cmp r0, #0x0
	ldr r0, _020B36B8 ; =0x021CDD6C
	rsbne r6, r6, #0x0
	ldr r0, [r0, #0x0]
	bl FUN_020B4F74
_020B35F8: ; 0x020B35F8
	cmp r0, #0x0
	rsbne r7, r7, #0x0
	mov r0, r6, lsl #0xc
	mov r1, r7, lsl #0xc
	mov r2, #0x0
	bl FUN_020B2A08
_020B3610:
	ldrh r0, [r5, #0x4a]
	ands r0, r0, #0x4
	beq _020B3644
	ldrh r0, [r5, #0x48]
	ldr r2, _020B36BC ; =0x020FFA38
	mov r0, r0, asr #0x4
	mov r1, r0, lsl #0x1
	add r0, r1, #0x1
	mov r3, r1, lsl #0x1
	mov r1, r0, lsl #0x1
	ldrsh r0, [r2, r3]
	ldrsh r1, [r2, r1]
	bl FUN_020B2794
_020B3644:
	ldrh r0, [r5, #0x4a]
	ands r0, r0, #0x2
	beq _020B3660
	ldr r0, [r5, #0x3c]
	ldr r1, [r5, #0x40]
	mov r2, #0x1000
	bl FUN_020B28B4
_020B3660:
	ldr r2, [r5, #0x34]
	mvn r0, #0x0
	cmp r2, r0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020B369C
	ldr r1, _020B36B4 ; =0x02106574
	mov r0, r4
	str r2, [r1, #0x0]
	bl FUN_020B36C0
	ldr r0, _020B36B4 ; =0x02106574
	mvn r1, #0x0
	str r1, [r0, #0x0]
	b _020B36A4
_020B369C:
	mov r0, r4
	bl FUN_020B36C0
_020B36A4:
	mov r0, #0x1
	bl FUN_020B2B08
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B36B4: .word 0x02106574
_020B36B8: .word 0x021CDD6C
_020B36BC: .word 0x020FFA38

	arm_func_start FUN_020B36C0
FUN_020B36C0: ; 0x020B36C0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r5, _020B3B54 ; =0x021CDD6C
	mov r10, r0
	ldr r0, [r5, #0x0]
	ldr r1, [r0, #0x7c]
	str r0, [sp, #0x0]
	ldr r9, [r0, #0x70]
	ands r0, r1, #0x2
	beq _020B38EC
	ldr r0, [r9, #0x14]
	cmp r0, #0x0
	beq _020B3840
	ldr r0, _020B3B58 ; =0x021CDD68
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020B3720
	ldr r2, _020B3B5C ; =0x02106570
	ldr r0, _020B3B60 ; =0x0000FFFE
	ldrh r2, [r2, #0x0]
	cmp r2, r0
	movne r0, #0x1
	bne _020B3724
_020B3720:
	mov r0, #0x0
_020B3724:
	cmp r0, #0x0
	beq _020B37AC
	ldr r0, _020B3B64 ; =0x021CE8F4
	ldr r1, [r0, #0x404]
	cmp r1, #0x0
	beq _020B3788
	ldrh r1, [r0, #0x0]
	ldr r0, _020B3B68 ; =0x021CE8F8
	ldr r1, [r0, r1, lsl #0x2]
	cmp r1, #0x0
	bne _020B37AC
	bl FUN_020B4010
	ldr r0, _020B3B6C ; =0x021CDD70
	ldr r2, _020B3B70 ; =0x021CDDF4
	ldr r0, [r0, #0x0]
	ldr r1, _020B3B64 ; =0x021CE8F4
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0xd
	ldrh r3, [r2, r0]
	ldr r4, _020B3B74 ; =0x021CE4F4
	ldrh r2, [r1, #0x0]
	ldr r0, _020B3B68 ; =0x021CE8F8
	add r1, r4, r3, lsl #0x5
	str r1, [r0, r2, lsl #0x2]
	b _020B37AC
_020B3788:
	bl FUN_020B4010
	ldr r0, _020B3B6C ; =0x021CDD70
	ldr r1, _020B3B70 ; =0x021CDDF4
	ldr r0, [r0, #0x0]
	ldr r2, _020B3B74 ; =0x021CE4F4
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0xd
	ldrh r0, [r1, r0]
	add r1, r2, r0, lsl #0x5
_020B37AC:
	ldr r0, _020B3B58 ; =0x021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldreq r0, _020B3B6C ; =0x021CDD70
	ldreq r3, _020B3B78 ; =0x021CDEF4
	ldreq r2, [r0, #0x0]
	moveq r0, #0x18
	mlaeq r0, r2, r0, r3
	beq _020B37FC
	ldr r2, _020B3B6C ; =0x021CDD70
	mov r0, #0x18
	ldr r2, [r2, #0x0]
	ldr r3, _020B3B7C ; =0x021CDF04
	mul r4, r2, r0
	ldr r2, _020B3B80 ; =0x021CDF08
	ldr r3, [r3, r4]
	ldr r0, _020B3B84 ; =0x02106578
	ldr r2, [r2, r4]
	str r3, [r0, #0x10]
	str r2, [r0, #0x14]
_020B37FC:
	bl FUN_020B4FAC
	ldr r1, _020B3B88 ; =0x02106574
	mvn r0, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, r0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020B3830
	mov r0, r10
	bl FUN_020B4BF4
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
_020B3830:
	mov r0, r10
	bl FUN_020B4CDC
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
_020B3840:
	ldr r0, _020B3B6C ; =0x021CDD70
	ldr r1, _020B3B8C ; =0x021CDD74
	ldr r2, [r0, #0x0]
	ldr r0, [sp, #0x0]
	ldr r1, [r1, r2, lsl #0x2]
	bl FUN_020B4FA4
	ldr r0, _020B3B58 ; =0x021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldreq r0, _020B3B6C ; =0x021CDD70
	ldreq r2, _020B3B78 ; =0x021CDEF4
	ldreq r1, [r0, #0x0]
	moveq r0, #0x18
	mlaeq r0, r1, r0, r2
	beq _020B38A8
	ldr r1, _020B3B6C ; =0x021CDD70
	mov r0, #0x18
	ldr r1, [r1, #0x0]
	ldr r2, _020B3B7C ; =0x021CDF04
	mul r3, r1, r0
	ldr r1, _020B3B80 ; =0x021CDF08
	ldr r2, [r2, r3]
	ldr r0, _020B3B84 ; =0x02106578
	ldr r1, [r1, r3]
	str r2, [r0, #0x10]
	str r1, [r0, #0x14]
_020B38A8:
	bl FUN_020B4FC4
	ldr r1, _020B3B88 ; =0x02106574
	mvn r0, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, r0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020B38DC
	mov r0, r10
	bl FUN_020B4BF4
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
_020B38DC:
	mov r0, r10
	bl FUN_020B4CDC
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
_020B38EC:
	cmp r9, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r11,pc}
_020B38F8: ; 0x020B38F8
	ldr r4, _020B3B6C ; =0x021CDD70
	ldr fp, _020B3B78 ; =0x021CDEF4
	mov r7, #0x0
	mov r6, #0x1
_020B3908:
	ldr r0, [r9, #0x10]
	cmp r0, #0x0
	beq _020B3B40
	ldr r0, [r9, #0x14]
	cmp r0, #0x0
	beq _020B3A8C
	ldr r8, [r5, #0x0]
	mov r1, r9
	str r9, [r8, #0x74]
	mov r0, r8
	bl FUN_020B4F9C
	ldr r1, [r9, #0x28]
	ldr r2, [r9, #0x2c]
	mov r0, r8
	bl FUN_020B5034
	mov r0, r8
	bl FUN_020B4E0C
	ldr r0, _020B3B58 ; =0x021CDD68
	mov r1, r7
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020B3978
	ldr r0, _020B3B5C ; =0x02106570
	ldrh r2, [r0, #0x0]
	ldr r0, _020B3B60 ; =0x0000FFFE
	cmp r2, r0
	movne r0, r6
	bne _020B397C
_020B3978:
	mov r0, r7
_020B397C:
	cmp r0, #0x0
	beq _020B3A04
	ldr r0, _020B3B64 ; =0x021CE8F4
	ldr r0, [r0, #0x404]
	cmp r0, #0x0
	beq _020B39E4
	ldr r0, _020B3B64 ; =0x021CE8F4
	ldrh r1, [r0, #0x0]
	add r0, r0, r1, lsl #0x2
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	bne _020B3A04
	bl FUN_020B4010
	ldr r0, _020B3B64 ; =0x021CE8F4
	ldr r2, [r4, #0x0]
	ldrh r1, [r0, #0x0]
	mov r0, r2, lsl #0x10
	mov r2, r0, lsr #0xd
	ldr r0, _020B3B70 ; =0x021CDDF4
	ldrh r3, [r0, r2]
	ldr r0, _020B3B64 ; =0x021CE8F4
	add r2, r0, r1, lsl #0x2
	ldr r0, _020B3B74 ; =0x021CE4F4
	add r1, r0, r3, lsl #0x5
	str r1, [r2, #0x4]
	b _020B3A04
_020B39E4:
	bl FUN_020B4010
_020B39E8: ; 0x020B39E8
	ldr r0, [r4, #0x0]
	mov r0, r0, lsl #0x10
	mov r1, r0, lsr #0xd
	ldr r0, _020B3B70 ; =0x021CDDF4
	ldrh r1, [r0, r1]
	ldr r0, _020B3B74 ; =0x021CE4F4
	add r1, r0, r1, lsl #0x5
_020B3A04:
	ldr r0, _020B3B58 ; =0x021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldreq r2, [r4, #0x0]
	moveq r0, #0x18
	mlaeq r0, r2, r0, r11
	beq _020B3A44
	ldr r2, [r4, #0x0]
	mov r0, #0x18
	mla r8, r2, r0, r11
	ldr r0, _020B3B84 ; =0x02106578
	ldr r3, [r8, #0x10]
	mov r2, r0
	str r3, [r2, #0x10]
	ldr r3, [r8, #0x14]
	str r3, [r2, #0x14]
_020B3A44:
	bl FUN_020B4FAC
	ldr r0, _020B3B88 ; =0x02106574
	ldr r1, [r0, #0x0]
	mvn r0, #0x0
	cmp r1, r0
	movne r0, r6
	moveq r0, r7
	cmp r0, #0x0
	beq _020B3A74
	mov r0, r10
	bl FUN_020B4BF4
	b _020B3A7C
_020B3A74:
	mov r0, r10
	bl FUN_020B4CDC
_020B3A7C:
	ldr r0, [r5, #0x0]
	str r7, [r0, #0x74]
	bl FUN_020B4DA0
	b _020B3B40
_020B3A8C:
	ldr r8, [r5, #0x0]
	mov r1, r9
	mov r0, r8
	str r9, [r8, #0x74]
	bl FUN_020B4F9C
	mov r0, r8
	bl FUN_020B4E0C
	ldr r2, [r4, #0x0]
	ldr r1, _020B3B8C ; =0x021CDD74
	ldr r0, [sp, #0x0]
	ldr r1, [r1, r2, lsl #0x2]
	bl FUN_020B4FA4
	ldr r0, _020B3B58 ; =0x021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldreq r1, [r4, #0x0]
	moveq r0, #0x18
	mlaeq r0, r1, r0, r11
	beq _020B3AFC
	ldr r1, [r4, #0x0]
	mov r0, #0x18
	mla r3, r1, r0, r11
	ldr r0, _020B3B84 ; =0x02106578
	ldr r2, [r3, #0x10]
	mov r1, r0
	str r2, [r1, #0x10]
	ldr r2, [r3, #0x14]
	str r2, [r1, #0x14]
_020B3AFC:
	bl FUN_020B4FC4
	ldr r0, _020B3B88 ; =0x02106574
	ldr r1, [r0, #0x0]
	mvn r0, #0x0
	cmp r1, r0
	movne r0, r6
	moveq r0, r7
	cmp r0, #0x0
	beq _020B3B2C
	mov r0, r10
	bl FUN_020B4BF4
	b _020B3B34
_020B3B2C:
	mov r0, r10
	bl FUN_020B4CDC
_020B3B34:
	ldr r0, [r5, #0x0]
	str r7, [r0, #0x74]
	bl FUN_020B4DA0
_020B3B40:
	ldr r9, [r9, #0x30]
	cmp r9, #0x0
	bne _020B3908
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B3B54: .word 0x021CDD6C
_020B3B58: .word 0x021CDD68
_020B3B5C: .word 0x02106570
_020B3B60: .word 0x0000FFFE
_020B3B64: .word 0x021CE8F4
_020B3B68: .word 0x021CE8F8
_020B3B6C: .word 0x021CDD70
_020B3B70: .word 0x021CDDF4
_020B3B74: .word 0x021CE4F4
_020B3B78: .word 0x021CDEF4
_020B3B7C: .word 0x021CDF04
_020B3B80: .word 0x021CDF08
_020B3B84: .word 0x02106578
_020B3B88: .word 0x02106574
_020B3B8C: .word 0x021CDD74

	arm_func_start FUN_020B3B90
FUN_020B3B90: ; 0x020B3B90
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	ldr r0, _020B3C24 ; =0x021CDD6C
	mov r12, r1
	ldr r0, [r0, #0x0]
	mov r3, r2
	ldr r1, [r0, #0x74]
	ldr r2, [r1, #0x44]
	cmp r2, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r6,pc}
_020B3BBC: ; 0x020B3BBC
	ldr r2, _020B3C28 ; =0x021CDD68
	ldr r2, [r2, #0x0]
	cmp r2, #0x0
	ldreq r2, _020B3C2C ; =0x021CDD70
	ldreq r4, _020B3C30 ; =0x021CDEF4
	ldreq lr, [r2, #0x0]
	moveq r2, #0x18
	mlaeq r6, lr, r2, r4
	beq _020B3C0C
	ldr lr, _020B3C2C ; =0x021CDD70
	mov r2, #0x18
	ldr lr, [lr, #0x0]
	ldr r4, _020B3C34 ; =0x021CDF04
	mul r5, lr, r2
	ldr r2, _020B3C38 ; =0x021CDF08
	ldr r4, [r4, r5]
	ldr r6, _020B3C3C ; =0x02106578
	ldr r2, [r2, r5]
	str r4, [r6, #0x10]
	str r2, [r6, #0x14]
_020B3C0C:
	str r6, [sp, #0x0]
	ldr lr, [r1, #0x44]
	mov r2, r12
	blx lr
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B3C24: .word 0x021CDD6C
_020B3C28: .word 0x021CDD68
_020B3C2C: .word 0x021CDD70
_020B3C30: .word 0x021CDEF4
_020B3C34: .word 0x021CDF04
_020B3C38: .word 0x021CDF08
_020B3C3C: .word 0x02106578

	arm_func_start FUN_020B3C40
FUN_020B3C40: ; 0x020B3C40
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	ldr r3, _020B3E2C ; =0x021CDD6C
	add r4, r0, #0x38
	ldr r0, [r3, #0x0]
	mov r6, r1
	mov r5, r2
	bl FUN_020B278C
_020B3C60: ; 0x020B3C60
	cmp r0, #0x0
	beq _020B3C90
	ldrh r1, [r4, #0x4]
	and r1, r1, #0xf000
	mov r1, r1, lsl #0x4
	mov r1, r1, lsr #0x10
	bl FUN_020B10B0
	ldr r1, [r4, #0x4]
	and r0, r0, #0xf
	bic r1, r1, #0xf000
	orr r0, r1, r0, lsl #0xc
	str r0, [r4, #0x4]
_020B3C90:
	ldr r0, _020B3E2C ; =0x021CDD6C
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x84]
	cmp r0, #0x0
	beq _020B3DA4
	ldr r0, [r1, #0x84]
	ands r0, r0, #0x1
	beq _020B3CC8
	ldrh r0, [r1, #0x88]
	ldr r1, [r4, #0x4]
	bic r1, r1, #0xc00
	and r0, r0, #0x3
	orr r0, r1, r0, lsl #0xa
	str r0, [r4, #0x4]
_020B3CC8:
	ldr r0, _020B3E2C ; =0x021CDD6C
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x84]
	ands r0, r0, #0x2
	beq _020B3CF4
	ldrh r0, [r1, #0x8a]
	ldr r1, [r4, #0x4]
	bic r1, r1, #0xf000
	and r0, r0, #0xf
	orr r0, r1, r0, lsl #0xc
	str r0, [r4, #0x4]
_020B3CF4:
	ldr r0, _020B3E2C ; =0x021CDD6C
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x84]
	ands r0, r0, #0x10
	beq _020B3D2C
	ldr r2, [r4, #0x4]
	ldrh r0, [r1, #0x94]
	mov r1, r2, lsl #0x10
	bic r2, r2, #0xf000
	add r0, r0, r1, lsr #0x1c
	and r0, r0, #0xf
	and r0, r0, #0xf
	orr r0, r2, r0, lsl #0xc
	str r0, [r4, #0x4]
_020B3D2C:
	ldr r0, _020B3E2C ; =0x021CDD6C
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x84]
	ands r0, r0, #0x4
	beq _020B3D60
	ldr r0, [r1, #0x90]
	cmp r0, #0x0
	ldrne r0, [r4, #0x0]
	orrne r0, r0, #0x1000
	strne r0, [r4, #0x0]
	ldreq r0, [r4, #0x0]
	biceq r0, r0, #0x1000
	streq r0, [r4, #0x0]
_020B3D60:
	ldr r0, _020B3E2C ; =0x021CDD6C
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x84]
	ands r0, r0, #0x8
	beq _020B3DA4
	ldr r0, [r4, #0x0]
	ldrh r2, [r4, #0x4]
	ldr r1, [r1, #0x8c]
	bic r0, r0, #0xc00
	orr r0, r0, r1, lsl #0xa
	str r0, [r4, #0x0]
	ldrh r0, [r4, #0x4]
	and r1, r2, #0xf000
	mov r1, r1, asr #0xc
	bic r0, r0, #0xf000
	orr r0, r0, r1, lsl #0xc
	strh r0, [r4, #0x4]
_020B3DA4:
	ldr r0, _020B3E2C ; =0x021CDD6C
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x74]
	ldr r2, [r1, #0x40]
	cmp r2, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r6,pc}
_020B3DC0: ; 0x020B3DC0
	ldr r2, _020B3E30 ; =0x021CDD68
	ldr r2, [r2, #0x0]
	cmp r2, #0x0
	ldreq r2, _020B3E34 ; =0x021CDD70
	ldreq r4, _020B3E38 ; =0x021CDEF4
	ldreq r3, [r2, #0x0]
	moveq r2, #0x18
	mlaeq r4, r3, r2, r4
	beq _020B3E10
	ldr r3, _020B3E34 ; =0x021CDD70
	mov r2, #0x18
	ldr r4, [r3, #0x0]
	ldr r3, _020B3E3C ; =0x021CDF04
	mul r12, r4, r2
	ldr r2, _020B3E40 ; =0x021CDF08
	ldr r3, [r3, r12]
	ldr r4, _020B3E44 ; =0x02106578
	ldr r2, [r2, r12]
	str r3, [r4, #0x10]
	str r2, [r4, #0x14]
_020B3E10:
	str r4, [sp, #0x0]
	ldr r4, [r1, #0x40]
	mov r2, r6
	mov r3, r5
	blx r4
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B3E2C: .word 0x021CDD6C
_020B3E30: .word 0x021CDD68
_020B3E34: .word 0x021CDD70
_020B3E38: .word 0x021CDEF4
_020B3E3C: .word 0x021CDF04
_020B3E40: .word 0x021CDF08
_020B3E44: .word 0x02106578

	arm_func_start FUN_020B3E48
FUN_020B3E48: ; 0x020B3E48
	stmdb sp!, {r4,lr}
	ldr r0, _020B3EC4 ; =0x021CDD6C
	mov r2, r1
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x74]
	ldr r3, [r1, #0x3c]
	cmp r3, #0x0
	ldmeqia sp!, {r4,pc}
_020B3E68: ; 0x020B3E68
	ldr r3, _020B3EC8 ; =0x021CDD68
	ldr r3, [r3, #0x0]
	cmp r3, #0x0
	ldreq r3, _020B3ECC ; =0x021CDD70
	ldreq lr, _020B3ED0 ; =0x021CDEF4
	ldreq r12, [r3, #0x0]
	moveq r3, #0x18
	mlaeq r3, r12, r3, lr
	beq _020B3EB8
	ldr ip, _020B3ECC ; =0x021CDD70
	mov r3, #0x18
	ldr r12, [r12, #0x0]
	ldr lr, _020B3ED4 ; =0x021CDF04
	mul r4, r12, r3
	ldr ip, _020B3ED8 ; =0x021CDF08
	ldr lr, [lr, r4]
	ldr r3, _020B3EDC ; =0x02106578
	ldr r12, [r12, r4]
	str lr, [r3, #0x10]
	str r12, [r3, #0x14]
_020B3EB8:
	ldr r12, [r1, #0x3c]
	blx r12
	ldmia sp!, {r4,pc}
	.balign 4
_020B3EC4: .word 0x021CDD6C
_020B3EC8: .word 0x021CDD68
_020B3ECC: .word 0x021CDD70
_020B3ED0: .word 0x021CDEF4
_020B3ED4: .word 0x021CDF04
_020B3ED8: .word 0x021CDF08
_020B3EDC: .word 0x02106578

	arm_func_start FUN_020B3EE0
FUN_020B3EE0: ; 0x020B3EE0
	stmdb sp!, {r4-r6,lr}
	ldr r2, _020B3FF4 ; =0x021CDD6C
	mov r6, r0
	ldr r0, [r2, #0x0]
	mov r5, r1
	ldr r4, [r0, #0x74]
	ldr r0, [r4, #0x34]
	cmp r0, #0x0
	beq _020B3F7C
	ldr r0, _020B3FF8 ; =0x021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldreq r0, _020B3FFC ; =0x021CDD70
	ldreq r1, _020B4000 ; =0x021CDEF4
	ldreq r2, [r0, #0x0]
	moveq r0, #0x18
	mlaeq r1, r2, r0, r1
	beq _020B3F54
	ldr r1, _020B3FFC ; =0x021CDD70
	mov r0, #0x18
	ldr r2, [r1, #0x0]
	ldr r1, _020B4004 ; =0x021CDF04
	mul r3, r2, r0
	ldr r0, _020B4008 ; =0x021CDF08
	ldr r2, [r1, r3]
	ldr r1, _020B400C ; =0x02106578
	ldr r0, [r0, r3]
	str r2, [r1, #0x10]
	str r0, [r1, #0x14]
_020B3F54:
	ldr r3, [r4, #0x34]
	mov r0, r5
	mov r2, r4
	blx r3
	cmp r0, #0x0
	moveq r0, #0x0
	streq r0, [r6, #0x30]
	ldmeqia sp!, {r4-r6,pc}
_020B3F74: ; 0x020B3F74
	mov r0, #0x1
	str r0, [r6, #0x30]
_020B3F7C:
	ldr r0, [r4, #0x38]
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020B3F88: ; 0x020B3F88
	ldr r0, _020B3FF8 ; =0x021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldreq r0, _020B3FFC ; =0x021CDD70
	ldreq r2, _020B4000 ; =0x021CDEF4
	ldreq r1, [r0, #0x0]
	moveq r0, #0x18
	mlaeq r3, r1, r0, r2
	beq _020B3FD8
	ldr r1, _020B3FFC ; =0x021CDD70
	mov r0, #0x18
	ldr r2, [r1, #0x0]
	ldr r1, _020B4004 ; =0x021CDF04
	mul r6, r2, r0
	ldr r0, _020B4008 ; =0x021CDF08
	ldr r1, [r1, r6]
	ldr r3, _020B400C ; =0x02106578
	ldr r0, [r0, r6]
	str r1, [r3, #0x10]
	str r0, [r3, #0x14]
_020B3FD8:
	ldr r0, _020B3FF4 ; =0x021CDD6C
	ldr r6, [r4, #0x38]
	ldr r0, [r0, #0x0]
	mov r1, r4
	mov r2, r5
	blx r6
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B3FF4: .word 0x021CDD6C
_020B3FF8: .word 0x021CDD68
_020B3FFC: .word 0x021CDD70
_020B4000: .word 0x021CDEF4
_020B4004: .word 0x021CDF04
_020B4008: .word 0x021CDF08
_020B400C: .word 0x02106578

	arm_func_start FUN_020B4010
FUN_020B4010:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020B4154 ; =0x021CDD70
	ldr r1, _020B4158 ; =0x021CDDF4
	ldr r0, [r0, #0x0]
	mov r2, #0x1
	mov r0, r0, lsl #0x10
	add r3, r1, r0, lsr #0xd
	ldrh r0, [r3, #0x4]
	cmp r0, #0x1
	beq _020B4044
	cmp r0, #0x2
	movne r2, #0x0
_020B4044:
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
_020B4050: ; 0x020B4050
	ldr r0, _020B415C ; =0x021CDD60
	mov r2, #0x10
	ldrh r4, [r0, #0x0]
	cmp r4, #0x1f
	addcc r1, r4, #0x1
	strcch r1, [r0, #0x0]
	ldr r0, _020B4160 ; =0x021CE4F4
	ldrh r5, [r3, #0x2]
	add r0, r0, r4, lsl #0x5
	add r1, r0, #0x10
	mvn r0, #0x0
	strh r4, [r3, #0x0]
	bl MIi_CpuClearFast
	ldr r0, _020B4154 ; =0x021CDD70
	ldr r1, _020B4164 ; =0x021CDD68
	ldr r0, [r0, #0x0]
	ldr r2, [r1, #0x0]
	mov r1, r0, lsl #0x10
	cmp r2, #0x0
	ldr r3, _020B4158 ; =0x021CDDF4
	mov r1, r1, lsr #0xd
	ldrh r1, [r3, r1]
	ldr r3, _020B4160 ; =0x021CE4F4
	moveq r2, #0x18
	add r1, r3, r1, lsl #0x5
	ldreq r3, _020B4168 ; =0x021CE1F4
	mlaeq r12, r0, r2, r3
	beq _020B40E4
	mov r2, #0x18
	mul r3, r0, r2
	ldr r2, _020B416C ; =0x021CDF04
	ldr r0, _020B4170 ; =0x021CDF08
	ldr r2, [r2, r3]
	ldr ip, _020B4174 ; =0x02106578
	ldr r0, [r0, r3]
	str r2, [r12, #0x10]
	str r0, [r12, #0x14]
_020B40E4:
	ldr r2, [r12, #0x0]
	ldr r0, _020B4154 ; =0x021CDD70
	str r2, [r1, #0x0]
	ldr r2, [r12, #0x4]
	str r2, [r1, #0x4]
	ldr r2, [r12, #0x8]
	str r2, [r1, #0x8]
	ldr r2, [r12, #0xc]
	str r2, [r1, #0xc]
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x10
	movs lr, r0, lsr #0x10
	addmi sp, sp, #0x4
	ldmmiia sp!, {r4-r5,pc}
_020B411C: ; 0x020B411C
	ldr r3, _020B4158 ; =0x021CDDF4
	mov r0, #0x3
_020B4124:
	add r2, r3, lr, lsl #0x3
	ldrh r1, [r2, #0x2]
	mov r12, lr, lsl #0x3
	cmp r5, r1
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,pc}
_020B413C: ; 0x020B413C
	strh r0, [r2, #0x4]
	strh r4, [r3, r12]
	subs lr, lr, #0x1
	bpl _020B4124
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B4154: .word 0x021CDD70
_020B4158: .word 0x021CDDF4
_020B415C: .word 0x021CDD60
_020B4160: .word 0x021CE4F4
_020B4164: .word 0x021CDD68
_020B4168: .word 0x021CE1F4
_020B416C: .word 0x021CDF04
_020B4170: .word 0x021CDF08
_020B4174: .word 0x02106578

	arm_func_start FUN_020B4178
FUN_020B4178: ; 0x020B4178
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020B4220 ; =0x021CDD68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020B41B8
	ldr r1, _020B4224 ; =0x021CDD70
	mov r0, #0x18
	ldr r12, [r1, #0x0]
	ldr r1, _020B4228 ; =0x021CDF04
	mul r3, r12, r0
	mov r2, #0x0
	ldr r0, _020B422C ; =0x021CDF08
	str r2, [r1, r3]
	str r2, [r0, r3]
	b _020B420C
_020B41B8:
	ldr r0, _020B4224 ; =0x021CDD70
	mov lr, #0x18
	ldr r1, [r0, #0x0]
	ldr r4, _020B4230 ; =0x021CDEF4
	mul r3, r1, lr
	mov r2, #0x1000
	str r2, [r4, r3]
	add r5, r4, r3
	mov r1, #0x0
	str r1, [r5, #0x4]
	str r1, [r5, #0x8]
	str r2, [r5, #0xc]
	str r1, [r5, #0x10]
	str r1, [r5, #0x14]
	ldr r12, [r0, #0x0]
	ldr r4, _020B4234 ; =0x021CE1F4
	ldmia r5!, {r0-r3}
	mla lr, r12, lr, r4
	stmia lr!, {r0-r3}
	ldmia r5, {r0-r1}
	stmia lr, {r0-r1}
_020B420C:
	ldr r0, _020B4238 ; =0x021CDD74
	mov r1, #0x0
	str r1, [r0, r12, lsl #0x2]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B4220: .word 0x021CDD68
_020B4224: .word 0x021CDD70
_020B4228: .word 0x021CDF04
_020B422C: .word 0x021CDF08
_020B4230: .word 0x021CDEF4
_020B4234: .word 0x021CE1F4
_020B4238: .word 0x021CDD74

	arm_func_start FUN_020B423C
FUN_020B423C: ; 0x020B423C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x1c
	ldr r4, [r0, #0x4]
	ldr r3, [r1, #0x8]
	mov r12, r2
	smull r6, r5, r4, r3
	ldr r4, [r0, #0x0]
	ldr r3, [r1, #0x0]
	cmp r12, r1
	smlal r6, r5, r4, r3
	mov r3, r6, lsr #0xc
	addeq r2, sp, #0x0
	orr r3, r3, r5, lsl #0x14
	str r3, [r2, #0x0]
	ldr r4, [r0, #0x4]
	ldr r3, [r1, #0xc]
	ldr r5, [r0, #0x0]
	smull r7, r6, r4, r3
	ldr r3, [r1, #0x4]
	add lr, sp, #0x0
	smlal r7, r6, r5, r3
	mov r3, r7, lsr #0xc
	orr r3, r3, r6, lsl #0x14
	str r3, [r2, #0x4]
	ldr r4, [r0, #0xc]
	ldr r3, [r1, #0x8]
	ldr r5, [r0, #0x8]
	smull r7, r6, r4, r3
	ldr r3, [r1, #0x0]
	cmp r2, lr
	smlal r7, r6, r5, r3
	mov r3, r7, lsr #0xc
	orr r3, r3, r6, lsl #0x14
	str r3, [r2, #0x8]
	ldr r4, [r0, #0xc]
	ldr r3, [r1, #0xc]
	ldr r5, [r0, #0x8]
	smull r7, r6, r4, r3
	ldr r3, [r1, #0x4]
	smlal r7, r6, r5, r3
	mov r3, r7, lsr #0xc
	orr r3, r3, r6, lsl #0x14
	str r3, [r2, #0xc]
	ldr r4, [r0, #0x14]
	ldr r3, [r1, #0x8]
	ldr r5, [r0, #0x10]
	smull r7, r6, r4, r3
	ldr r3, [r1, #0x0]
	ldr r4, [r1, #0x10]
	smlal r7, r6, r5, r3
	mov r3, r7, lsr #0xc
	orr r3, r3, r6, lsl #0x14
	add r3, r4, r3
	str r3, [r2, #0x10]
	ldr r4, [r0, #0x14]
	ldr r3, [r1, #0xc]
	ldr r5, [r0, #0x10]
	ldr r0, [r1, #0x4]
	smull r6, r3, r4, r3
	smlal r6, r3, r5, r0
	mov r0, r6, lsr #0xc
	ldr r1, [r1, #0x14]
	orr r0, r0, r3, lsl #0x14
	add r0, r1, r0
	str r0, [r2, #0x14]
	ldmeqia lr!, {r0-r3}
	stmeqia r12!, {r0-r3}
	ldmeqia lr, {r0-r1}
	stmeqia r12, {r0-r1}
	add sp, sp, #0x1c
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020B4358
FUN_020B4358: ; 0x020B4358
	stmdb sp!, {r4,lr}
	ldr r2, _020B43A0 ; =0x021CED04
	mov r1, #0x30
	ldr r2, [r2, #0x0]
	mla r4, r0, r1, r2
	mov r0, r4
	bl FUN_020B10CC
_020B4374: ; 0x020B4374
	mov r0, #0x0
	str r0, [r4, #0xc]
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	str r0, [r4, #0x20]
	str r0, [r4, #0x24]
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	ldmia sp!, {r4,pc}
	.balign 4
_020B43A0: .word 0x021CED04

	arm_func_start FUN_020B43A4
FUN_020B43A4: ; 0x020B43A4
	ldr r1, _020B43F8 ; =0x021CED00
	mov r0, #0x0
	ldr r3, [r1, #0x0]
	cmp r3, #0x0
	bls _020B43F0
	ldr r1, _020B43FC ; =0x021CED04
	ldr r2, [r1, #0x0]
	mov r12, r2
_020B43C4:
	ldr r1, [r12, #0x1c]
	cmp r1, #0x1
	movne r1, #0x30
	mlane r1, r0, r1, r2
	movne r2, #0x1
	strne r2, [r1, #0x1c]
	bxne lr
	add r0, r0, #0x1
	cmp r0, r3
	add r12, r12, #0x30
	blo _020B43C4
_020B43F0:
	mvn r0, #0x0
	bx lr
	.balign 4
_020B43F8: .word 0x021CED00
_020B43FC: .word 0x021CED04

	arm_func_start FUN_020B4400
FUN_020B4400: ; 0x020B4400
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	mov r4, r2
	bl FUN_020B469C
	mvn r1, #0x0
	str r1, [r0, #0x24]
	str r5, [r0, #0x28]
	str r4, [r0, #0x2c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020B442C
FUN_020B442C: ; 0x020B442C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r0, _020B4558 ; =0x021CED00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addls sp, sp, #0x14
	ldmlsia sp!, {r4-r11,pc}
_020B4450: ; 0x020B4450
	ldr r0, [sp, #0x0]
	mov r5, #0x1
	str r0, [sp, #0x4]
	mov r11, r0
	str r0, [sp, #0x8]
	str r0, [sp, #0xc]
_020B4468:
	ldr r0, _020B455C ; =0x021CED04
	ldr r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	add r8, r1, r0
	ldr r0, [r8, #0x1c]
	cmp r0, #0x0
	beq _020B4528
	ldr r9, [sp, #0x8]
	mov r0, r9
	cmp r0, #0x3
	bge _020B4520
	add r4, r8, #0x24
_020B4498:
	mov r6, r5, lsl r9
	mov r1, r11
	ldr r0, [r8, #0x24]
	ands r0, r0, r6
	beq _020B44B8
	ldr r0, [r8, #0x20]
	ands r0, r0, r6
	movne r1, r5
_020B44B8:
	cmp r1, #0x0
	beq _020B4514
	ldr r0, _020B4560 ; =0x020FF8C4
	cmp r9, #0x0
	ldr r7, [r0, r9, lsl #0x2]
	ldreq r10, [r8, #0x14]
	mov r0, r8
	mov r1, r9
	ldrne r10, [r8, #0x10]
	bl FUN_020B10BC
	mov r1, r0
	mov r0, r7
	ldr r7, _020B4564 ; =0x021CECFC
	ldr r2, [r8, #0x28]
	ldr r3, [r8, #0x2c]
	ldr r7, [r7, #0x0]
	add r2, r10, r2
	blx r7
	cmp r0, #0x0
	ldrne r1, [r4, #0x0]
	mvnne r0, r6
	andne r0, r1, r0
	strne r0, [r4, #0x0]
_020B4514:
	add r9, r9, #0x1
	cmp r9, #0x3
	blt _020B4498
_020B4520:
	ldr r0, [sp, #0xc]
	str r0, [r8, #0x20]
_020B4528:
	ldr r0, _020B4558 ; =0x021CED00
	ldr r1, [r0, #0x0]
	ldr r0, [sp, #0x0]
	add r0, r0, #0x1
	str r0, [sp, #0x0]
	cmp r0, r1
	ldr r0, [sp, #0x4]
	add r0, r0, #0x30
	str r0, [sp, #0x4]
	blo _020B4468
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B4558: .word 0x021CED00
_020B455C: .word 0x021CED04
_020B4560: .word 0x020FF8C4
_020B4564: .word 0x021CECFC

	arm_func_start FUN_020B4568
FUN_020B4568: ; 0x020B4568
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr ip, _020B45E4 ; =0x021CECFC
	movs r6, r1
	ldr r1, _020B45E8 ; =0x021CED00
	ldr r3, _020B45EC ; =0x021CED04
	mov r7, r0
	str r2, [r12, #0x0]
	mov r5, #0x0
	addeq sp, sp, #0x4
	str r7, [r3, #0x0]
	str r6, [r1, #0x0]
	ldmeqia sp!, {r4-r7,pc}
_020B459C: ; 0x020B459C
	mov r4, r5
_020B45A0:
	mov r0, r7
	bl FUN_020B10CC
	str r4, [r7, #0xc]
	str r4, [r7, #0x10]
	str r4, [r7, #0x14]
	str r4, [r7, #0x18]
	str r4, [r7, #0x1c]
	str r4, [r7, #0x20]
	str r4, [r7, #0x24]
	str r4, [r7, #0x28]
	add r5, r5, #0x1
	str r4, [r7, #0x2c]
	cmp r5, r6
	add r7, r7, #0x30
	blo _020B45A0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B45E4: .word 0x021CECFC
_020B45E8: .word 0x021CED00
_020B45EC: .word 0x021CED04

	arm_func_start FUN_020B45F0
FUN_020B45F0: ; 0x020B45F0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr ip, _020B4698 ; =0x021CED04
	mov r4, #0x30
	ldr r12, [r12, #0x0]
	mov r7, r1
	mla r4, r0, r4, r12
	mov r0, r4
	mov r6, r2
	mov r5, r3
	bl FUN_020B10CC
_020B461C: ; 0x020B461C
	mvn r0, #0x0
	cmp r7, r0
	beq _020B4638
	mov r0, r4
	mov r2, r7
	mov r1, #0x0
	bl FUN_020B10C4
_020B4638:
	mvn r0, #0x0
	cmp r6, r0
	beq _020B4654
	mov r0, r4
	mov r2, r6
	mov r1, #0x1
	bl FUN_020B10C4
_020B4654:
	mvn r0, #0x0
	cmp r5, r0
	beq _020B4670
	mov r0, r4
	mov r2, r5
	mov r1, #0x2
	bl FUN_020B10C4
_020B4670:
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	str r1, [r4, #0xc]
	ldr r1, [sp, #0x20]
	str r0, [r4, #0x10]
	ldr r0, [sp, #0x24]
	str r1, [r4, #0x14]
	str r0, [r4, #0x18]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B4698: .word 0x021CED04

	arm_func_start FUN_020B469C
FUN_020B469C: ; 0x020B469C
	ldr r2, _020B46B0 ; =0x021CED04
	mov r1, #0x30
	ldr r2, [r2, #0x0]
	mla r0, r1, r0, r2
	bx lr
	.balign 4
_020B46B0: .word 0x021CED04

	arm_func_start FUN_020B46B4
FUN_020B46B4: ; 0x020B46B4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x1c
	add r12, sp, #0x4
	mov r5, r1
	mov r4, r2
	mov r7, r3
	mov r6, r0
	ldr r1, [sp, #0x30]
	ldr r2, [sp, #0x34]
	ldr r3, [sp, #0x38]
	mov r0, r7
	str r12, [sp, #0x0]
	bl FUN_020B498C
	ldr r2, [r7, #0x0]
	and r1, r2, #0x300
	cmp r1, #0x100
	beq _020B4708
	cmp r1, #0x300
	beq _020B4708
	and r0, r2, #0x30000000
	orr r1, r1, r0
_020B4708:
	cmp r1, #0x300
	bne _020B478C
	ldr r0, _020B4914 ; =0xC000C000
	ldr r1, _020B4918 ; =0x021CED08
	and r0, r2, r0
	and r2, r0, #0xc0000000
	mov r12, r2, lsr #0x1e
	and r0, r0, #0xc000
	mov lr, r0, asr #0xe
	ldr r3, _020B491C ; =0x020FF8AC
	ldr r0, [r1, #0x0]
	ldr r2, _020B4920 ; =0x020FF894
	cmp r0, #0x0
	ldrne r0, _020B4924 ; =0x021CED10
	mov r12, r12, lsl #0x1
	add r1, r2, lr, lsl #0x3
	add r3, r3, lr, lsl #0x3
	ldrh r2, [r12, r3]
	ldrh r1, [r12, r1]
	ldrne r0, [r0, #0x0]
	mov r2, r2, asr #0x1
	addne r3, r0, r4, lsl #0xc
	mov r1, r1, asr #0x1
	add r0, r5, r1
	add r2, r6, r2
	ldr r1, _020B4928 ; =0x04000470
	mov r2, r2, lsl #0xc
	str r2, [r1, #0x0]
	mov r0, r0, lsl #0xc
	moveq r3, r4, lsl #0xc
	str r0, [r1, #0x0]
	str r3, [r1, #0x0]
	b _020B47C0
_020B478C:
	ldr r0, _020B4918 ; =0x021CED08
	ldr r1, _020B4928 ; =0x04000470
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldrne r0, _020B4924 ; =0x021CED10
	ldrne r0, [r0, #0x0]
	addne r2, r0, r4, lsl #0xc
	mov r0, r6, lsl #0xc
	str r0, [r1, #0x0]
	mov r0, r5, lsl #0xc
	moveq r2, r4, lsl #0xc
	str r0, [r1, #0x0]
	str r2, [r1, #0x0]
_020B47C0:
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	ldr r2, _020B492C ; =0x0400046C
	mov r0, r0, lsl #0xc
	str r0, [r2, #0x0]
	mov r0, r1, lsl #0xc
	str r0, [r2, #0x0]
	mov r1, #0x1000
	str r1, [r2, #0x0]
	ldr r0, _020B4930 ; =0x04000500
	mov r1, #0x1
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x10]
	mov r0, r0, lsl #0x8
	mov r1, r1, lsl #0x8
	mov r0, r0, asr #0x10
	mov r1, r1, asr #0x10
	mov r0, r0, lsl #0x10
	mov r1, r1, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r1, lsr #0x10
	orr r2, r2, r0, lsl #0x10
	ldr r1, _020B4934 ; =0x04000488
	ldr r0, _020B4938 ; =0x04000490
	str r2, [r1, #0x0]
	mov r2, #0x10000
	str r2, [r0, #0x0]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	mov r2, r2, lsl #0x8
	mov r3, r3, lsl #0x8
	mov r2, r2, asr #0x10
	mov r3, r3, asr #0x10
	mov r2, r2, lsl #0x10
	mov r3, r3, lsl #0x10
	mov r4, r2, lsr #0x10
	mov r2, r3, lsr #0x10
	orr r3, r4, r2, lsl #0x10
	ldr r2, _020B493C ; =0x00010040
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x8]
	mov r2, r2, lsl #0x8
	mov r3, r3, lsl #0x8
	mov r2, r2, asr #0x10
	mov r3, r3, asr #0x10
	mov r2, r2, lsl #0x10
	mov r3, r3, lsl #0x10
	mov r4, r2, lsr #0x10
	mov r2, r3, lsr #0x10
	orr r2, r4, r2, lsl #0x10
	str r2, [r1, #0x0]
	mov r2, #0x40
	str r2, [r0, #0x0]
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x8]
	mov r2, r2, lsl #0x8
	mov r3, r3, lsl #0x8
	mov r2, r2, asr #0x10
	mov r3, r3, asr #0x10
	mov r2, r2, lsl #0x10
	mov r3, r3, lsl #0x10
	mov r4, r2, lsr #0x10
	mov r2, r3, lsr #0x10
	orr r2, r4, r2, lsl #0x10
	str r2, [r1, #0x0]
	mov r2, #0x0
	str r2, [r0, #0x0]
	ldr r1, _020B4940 ; =0x04000504
	ldr r0, _020B4918 ; =0x021CED08
	str r2, [r1, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x1c
	ldmeqia sp!, {r4-r7,pc}
_020B48F4: ; 0x020B48F4
	ldr r1, _020B4924 ; =0x021CED10
	ldr r0, _020B4944 ; =0x02106590
	ldr r2, [r1, #0x0]
	ldr r0, [r0, #0x0]
	add r0, r2, r0
	str r0, [r1, #0x0]
	add sp, sp, #0x1c
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B4914: .word 0xC000C000
_020B4918: .word 0x021CED08
_020B491C: .word 0x020FF8AC
_020B4920: .word 0x020FF894
_020B4924: .word 0x021CED10
_020B4928: .word 0x04000470
_020B492C: .word 0x0400046C
_020B4930: .word 0x04000500
_020B4934: .word 0x04000488
_020B4938: .word 0x04000490
_020B493C: .word 0x00010040
_020B4940: .word 0x04000504
_020B4944: .word 0x02106590

	arm_func_start FUN_020B4948
FUN_020B4948:
	ldr r0, _020B4954 ; =0x02106590
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020B4954: .word 0x02106590

	arm_func_start FUN_020B4958
FUN_020B4958:
	ldr r1, _020B4964 ; =0x02106590
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020B4964: .word 0x02106590

	arm_func_start FUN_020B4968
FUN_020B4968: ; 0x020B4968
	ldr r0, _020B4978 ; =0x021CED10
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020B4978: .word 0x021CED10

	arm_func_start FUN_020B497C
FUN_020B497C:
	ldr r1, _020B4988 ; =0x021CED08
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020B4988: .word 0x021CED08

	arm_func_start FUN_020B498C
FUN_020B498C: ; 0x020B498C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0xc
	mov r6, r0
	ldr r4, [r6, #0x0]
	ldr r0, _020B4BCC ; =0xC000C000
	ldr r5, [r6, #0x4]
	and r4, r4, r0
	and r0, r4, #0xc0000000
	and r4, r4, #0xc000
	mov lr, r0, lsr #0x1e
	ldr r0, _020B4BD0 ; =0x020FF8AC
	mov r12, r4, asr #0xe
	ldr r8, _020B4BD4 ; =0x020FF894
	mov r4, lr, lsl #0x1
	add r0, r0, r12, lsl #0x3
	ldrh r9, [r4, r0]
	ldr r0, [sp, #0x28]
	mov r5, r5, lsl #0x16
	mov r5, r5, lsr #0x16
	mov r7, r5, lsl #0x10
	str r9, [r0, #0x10]
	add r5, r8, r12, lsl #0x3
	ldrh r8, [r4, r5]
	mov r5, r1
	mov r4, r3
	str r8, [r0, #0x14]
	ldr r1, [r5, #0x14]
	mov r7, r7, lsr #0x10
	cmp r1, #0x0
	bne _020B4A74
	ldr r1, [r5, #0x8]
	mov r2, r2, lsr #0x3
	orr r1, r2, r1, lsl #0x1a
	ldr r2, [r5, #0x0]
	orr r1, r1, #0x40000000
	ldr r3, [r5, #0x4]
	orr r1, r1, r2, lsl #0x14
	orr r2, r1, r3, lsl #0x17
	ldr r8, [r5, #0x10]
	ldr r1, _020B4BD8 ; =0x040004A8
	orr r2, r2, r8, lsl #0x1d
	str r2, [r1, #0x0]
	ldr r1, [r5, #0x8]
	ldr r2, [r5, #0x0]
	cmp r1, #0x4
	moveq r1, r7, lsl #0xf
	moveq r7, r1, lsr #0x10
	ldr r1, _020B4BDC ; =0x020FF8D8
	ldr r1, [r1, r2, lsl #0x2]
	sub r1, r1, #0x1
	and r1, r7, r1
	mov r1, r1, lsl #0xf
	str r1, [r0, #0x0]
	ldr r1, [r5, #0x0]
	mov r1, r7, asr r1
	mov r1, r1, lsl #0xf
	str r1, [r0, #0x4]
	b _020B4AE0
_020B4A74:
	and r1, r1, #0x700000
	mov r1, r1, asr #0x14
	mov r12, r12, lsl #0x10
	add r1, r1, #0x5
	ldr r3, [r5, #0x8]
	mov lr, lr, lsl #0x10
	ldr sb, _020B4BE0 ; =0x020FF8F8
	mov r12, r12, lsr #0x10
	ldr r8, _020B4BE4 ; =0x020FF928
	add r1, r2, r7, lsl r1
	mov r2, r3, lsl #0x1a
	orr r3, r2, r1, lsr #0x3
	mov r7, lr, lsr #0x10
	add r2, r9, r12, lsl #0x4
	add r1, r8, r12, lsl #0x4
	ldr r2, [r2, r7, lsl #0x2]
	orr r3, r3, #0x40000000
	ldr r1, [r1, r7, lsl #0x2]
	orr r2, r3, r2, lsl #0x14
	ldr r3, [r5, #0x10]
	orr r2, r2, r1, lsl #0x17
	ldr r1, _020B4BD8 ; =0x040004A8
	orr r2, r2, r3, lsl #0x1d
	str r2, [r1, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
_020B4AE0:
	ldr r2, [r0, #0x0]
	ldr r1, [r0, #0x10]
	add r1, r2, r1, lsl #0xc
	str r1, [r0, #0x8]
	ldr r2, [r0, #0x4]
	ldr r1, [r0, #0x14]
	add r1, r2, r1, lsl #0xc
	str r1, [r0, #0xc]
	ldr r1, [r6, #0x0]
	mov r2, r1, lsl #0x2
	mov r1, r1, lsl #0x3
	movs r3, r1, lsr #0x1f
	mov r12, r2, lsr #0x1f
	ldrne r2, [r0, #0x0]
	ldrne r1, [r0, #0x8]
	strne r1, [r0, #0x0]
	strne r2, [r0, #0x8]
	cmp r12, #0x0
	ldrne r2, [r0, #0x4]
	ldrne r1, [r0, #0xc]
	strne r1, [r0, #0x4]
	ldr r1, _020B4BE8 ; =0x021CED0C
	strne r2, [r0, #0xc]
	ldr r7, [r1, #0x0]
	cmp r7, #0x0
	beq _020B4B60
	str r3, [sp, #0x0]
	add r1, r0, #0x4
	add r2, r0, #0x8
	add r3, r0, #0xc
	str r12, [sp, #0x4]
	blx r7
_020B4B60:
	ldr r0, [r6, #0x4]
	ldr r1, [r6, #0x0]
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x1c
	mov r3, r1, lsl #0x12
	ldr r1, [r5, #0xc]
	mov r0, r0, lsl #0x10
	ldr r2, _020B4BEC ; =0x020FF8D0
	mov r3, r3, lsr #0x1f
	cmp r1, #0x0
	mov r0, r0, lsr #0x10
	ldr r1, [r2, r3, lsl #0x2]
	movne r0, r0, lsl #0x9
	bne _020B4BA4
	cmp r1, #0x4
	moveq r0, #0x0
	movne r0, r0, lsl #0x5
_020B4BA4:
	cmp r1, #0x2
	moveq r2, #0x1
	movne r2, #0x0
	add r1, r4, r0
	rsb r0, r2, #0x4
	mov r1, r1, lsr r0
	ldr r0, _020B4BF0 ; =0x040004AC
	str r1, [r0, #0x0]
	add sp, sp, #0xc
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020B4BCC: .word 0xC000C000
_020B4BD0: .word 0x020FF8AC
_020B4BD4: .word 0x020FF894
_020B4BD8: .word 0x040004A8
_020B4BDC: .word 0x020FF8D8
_020B4BE0: .word 0x020FF8F8
_020B4BE4: .word 0x020FF928
_020B4BE8: .word 0x021CED0C
_020B4BEC: .word 0x020FF8D0
_020B4BF0: .word 0x040004AC

	arm_func_start FUN_020B4BF4
FUN_020B4BF4: ; 0x020B4BF4
	stmdb sp!, {r4-r6,lr}
	ldr r2, _020B4CD8 ; =0x021CED14
	mov r6, r0
	ldr r3, [r2, #0x0]
	mov r4, r1
	ldr r5, [r3, #0x0]
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020B4C18: ; 0x020B4C18
	mov r0, #0x1
	str r0, [r3, #0x30]
	ldr r3, [r5, #0x18]
	cmp r3, #0x0
	beq _020B4C38
	ldr r0, [r2, #0x0]
	mov r1, r6
	blx r3
_020B4C38:
	ldr r0, _020B4CD8 ; =0x021CED14
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x30]
	cmp r0, #0x0
	beq _020B4CB8
	mvn r0, #0x0
	cmp r4, r0
	beq _020B4C7C
	mov r0, r4
	ldr r4, [r5, #0x14]
	bl FUN_020B469C
	mov r3, #0x1
	mvn r1, r3, lsl r4
	ldr r2, [r0, #0x20]
	and r1, r2, r1
	orr r1, r1, r3, lsl r4
	str r1, [r0, #0x20]
_020B4C7C:
	ldr r0, [r5, #0x14]
	cmp r0, #0x3
	addls pc, pc, r0, lsl #0x2
	b _020B4CB8
_020B4C8C:
	b _020B4C9C
_020B4C90:
	b _020B4CAC
_020B4C94:
	b _020B4CAC
_020B4C98:
	b _020B4CB8
_020B4C9C:
	mov r0, r5
	mov r1, r6
	bl FUN_020B5090
	b _020B4CB8
_020B4CAC:
	mov r0, r5
	mov r1, r6
	bl FUN_020B53B4
_020B4CB8:
	ldr r2, [r5, #0x1c]
	cmp r2, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020B4CC4: ; 0x020B4CC4
	ldr r0, _020B4CD8 ; =0x021CED14
	mov r1, r6
	ldr r0, [r0, #0x0]
	blx r2
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B4CD8: .word 0x021CED14

	arm_func_start FUN_020B4CDC
FUN_020B4CDC:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _020B4D9C ; =0x021CED14
	mov r5, r0
	ldr r2, [r1, #0x0]
	ldr r4, [r2, #0x0]
	ldr r0, [r4, #0x10]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
_020B4D04: ; 0x020B4D04
	mov r0, #0x1
	str r0, [r2, #0x30]
	ldr r2, [r4, #0x18]
	cmp r2, #0x0
	beq _020B4D24
	ldr r0, [r1, #0x0]
	mov r1, r5
	blx r2
_020B4D24:
	ldr r0, _020B4D9C ; =0x021CED14
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x30]
	cmp r0, #0x0
	beq _020B4D74
	ldr r0, [r4, #0x14]
	cmp r0, #0x3
	addls pc, pc, r0, lsl #0x2
	b _020B4D74
_020B4D48:
	b _020B4D58
_020B4D4C:
	b _020B4D68
_020B4D50:
	b _020B4D68
_020B4D54:
	b _020B4D74
_020B4D58:
	mov r0, r4
	mov r1, r5
	bl FUN_020B5090
	b _020B4D74
_020B4D68:
	mov r0, r4
	mov r1, r5
	bl FUN_020B53B4
_020B4D74:
	ldr r2, [r4, #0x1c]
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
_020B4D84: ; 0x020B4D84
	ldr r0, _020B4D9C ; =0x021CED14
	mov r1, r5
	ldr r0, [r0, #0x0]
	blx r2
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B4D9C: .word 0x021CED14

	arm_func_start FUN_020B4DA0
FUN_020B4DA0: ; 0x020B4DA0
	ldr r0, _020B4E00 ; =0x021CED14
	ldr r3, [r0, #0x0]
	ldr r1, [r3, #0x0]
	ldr r1, [r1, #0x14]
	cmp r1, #0x0
	bne _020B4DD8
	ldr r2, _020B4E04 ; =0x04000440
	mov r1, #0x0
	ldr r0, _020B4E08 ; =0x04000448
	str r1, [r2, #0x0]
	mov r1, #0x1
	str r1, [r0, #0x0]
	str r1, [r2, #0x0]
	b _020B4DF0
_020B4DD8:
	mov r2, #0x0
	str r2, [r3, #0x10]
	ldr r1, [r0, #0x0]
	str r2, [r1, #0x2c]
	ldr r0, [r0, #0x0]
	str r2, [r0, #0x28]
_020B4DF0:
	ldr r0, _020B4E00 ; =0x021CED14
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020B4E00: .word 0x021CED14
_020B4E04: .word 0x04000440
_020B4E08: .word 0x04000448

	arm_func_start FUN_020B4E0C
FUN_020B4E0C: ; 0x020B4E0C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r2, _020B4F28 ; =0x021CED14
	mov r4, r0
	str r4, [r2, #0x0]
	ldr r0, [r4, #0x0]
	ldr r5, [r0, #0x14]
	cmp r5, #0x0
	bne _020B4ED8
	ldr lr, _020B4F2C ; =0x04000440
	mov r1, #0x0
	ldr r0, _020B4F30 ; =0x04000444
	str r1, [lr, #0x0]
	str r1, [r0, #0x0]
	ldr r12, [r4, #0x0]
	ldr r0, _020B4F34 ; =0x04000470
	ldr r3, [r12, #0x0]
	ldr r12, [r12, #0x4]
	rsb r3, r3, #0x0
	str r3, [r0, #0x0]
	rsb r3, r12, #0x0
	str r3, [r0, #0x0]
	str r1, [r0, #0x0]
	mov r0, #0x1
	str r0, [lr, #0x0]
	ldr r0, [r2, #0x0]
	ldr r5, [r0, #0x8]
	mov r0, r5
	bl FUN_020B19FC
_020B4E80: ; 0x020B4E80
	cmp r0, #0x0
	moveq r0, #0x0
	beq _020B4E98
	mov r0, r5
	mov r1, #0x0
	bl FUN_020B1A14
_020B4E98:
	ldr r1, _020B4F28 ; =0x021CED14
	str r0, [r4, #0x14]
	ldr r0, [r1, #0x0]
	mov r1, #0x0
	ldr r5, [r0, #0xc]
	mov r0, r5
	bl FUN_020B19A8
_020B4EB4: ; 0x020B4EB4
	cmp r0, #0x0
	moveq r0, #0x0
	beq _020B4ECC
	mov r0, r5
	mov r1, #0x0
	bl FUN_020B19C4
_020B4ECC:
	add sp, sp, #0x4
	str r0, [r4, #0x18]
	ldmia sp!, {r4-r5,pc}
_020B4ED8:
	ldr r4, [r4, #0x8]
	mov r1, r5
	mov r0, r4
	bl FUN_020B19FC
_020B4EE8: ; 0x020B4EE8
	cmp r0, #0x0
	moveq r1, #0x0
	beq _020B4F14
	mov r0, r4
	mov r1, r5
	bl FUN_020B1A14
	ldr r1, [r4, #0x20]
	and r1, r1, #0x700000
	mov r1, r1, asr #0x14
	add r1, r1, #0x5
	mov r1, r0, lsr r1
_020B4F14:
	ldr r0, _020B4F28 ; =0x021CED14
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B4F28: .word 0x021CED14
_020B4F2C: .word 0x04000440
_020B4F30: .word 0x04000444
_020B4F34: .word 0x04000470

	arm_func_start FUN_020B4F38
FUN_020B4F38: ; 0x020B4F38
	cmp r1, #0x0
	ldrne r1, [r0, #0x24]
	orrne r1, r1, #0x1
	strne r1, [r0, #0x24]
	ldreq r1, [r0, #0x24]
	biceq r1, r1, #0x1
	streq r1, [r0, #0x24]
	cmp r2, #0x0
	ldrne r1, [r0, #0x24]
	orrne r1, r1, #0x2
	strne r1, [r0, #0x24]
	ldreq r1, [r0, #0x24]
	biceq r1, r1, #0x2
	streq r1, [r0, #0x24]
	bx lr

	arm_func_start FUN_020B4F74
FUN_020B4F74:
	ldr r0, [r0, #0x24]
	ands r0, r0, #0x2
	movne r0, #0x1
	moveq r0, #0x0
	bx lr

	arm_func_start FUN_020B4F88
FUN_020B4F88:
	ldr r0, [r0, #0x24]
	ands r0, r0, #0x1
	movne r0, #0x1
	moveq r0, #0x0
	bx lr

	arm_func_start FUN_020B4F9C
FUN_020B4F9C: ; 0x020B4F9C
	str r1, [r0, #0x0]
	bx lr

	arm_func_start FUN_020B4FA4
FUN_020B4FA4: ; 0x020B4FA4
	str r1, [r0, #0x34]
	bx lr

	arm_func_start FUN_020B4FAC
FUN_020B4FAC: ; 0x020B4FAC
	ldr r2, _020B4FC0 ; =0x021CED14
	ldr r2, [r2, #0x0]
	str r0, [r2, #0x2c]
	str r1, [r2, #0x28]
	bx lr
	.balign 4
_020B4FC0: .word 0x021CED14

	arm_func_start FUN_020B4FC4
FUN_020B4FC4: ; 0x020B4FC4
	ldr r1, _020B5028 ; =0x021CED14
	mov r3, #0x0
	ldr r12, [r1, #0x0]
	mov r1, #0x1000
	str r0, [r12, #0x2c]
	ldr r2, [r0, #0x0]
	str r2, [r12, #0x40]
	ldr r2, [r0, #0x4]
	str r2, [r12, #0x44]
	str r3, [r12, #0x48]
	ldr r2, [r0, #0x8]
	str r2, [r12, #0x4c]
	ldr r2, [r0, #0xc]
	str r2, [r12, #0x50]
	str r3, [r12, #0x54]
	str r3, [r12, #0x58]
	str r3, [r12, #0x5c]
	str r1, [r12, #0x60]
	ldr r1, [r0, #0x10]
	str r1, [r12, #0x64]
	ldr r0, [r0, #0x14]
	str r0, [r12, #0x68]
	ldr r0, [r12, #0x34]
	str r0, [r12, #0x6c]
	bx lr
	.balign 4
_020B5028: .word 0x021CED14

	arm_func_start FUN_020B502C
FUN_020B502C: ; 0x020B502C
	str r1, [r0, #0x4]
	bx lr

	arm_func_start FUN_020B5034
FUN_020B5034: ; 0x020B5034
	str r1, [r0, #0x1c]
	str r2, [r0, #0x20]
	bx lr

	arm_func_start FUN_020B5040
FUN_020B5040: ; 0x020B5040
	str r1, [r0, #0x8]
	str r2, [r0, #0xc]
	bx lr

	arm_func_start FUN_020B504C
FUN_020B504C: ; 0x020B504C
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r1, r4
	mov r0, #0x0
	mov r2, #0x70
	bl MIi_CpuClear16
	mov r1, #0x0
	str r1, [r4, #0x0]
	mov r0, #0x2
	str r0, [r4, #0x4]
	str r1, [r4, #0x8]
	str r1, [r4, #0xc]
	str r1, [r4, #0x24]
	mov r0, #0x1
	str r0, [r4, #0x30]
	str r1, [r4, #0x28]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020B5090
FUN_020B5090: ; 0x020B5090
	stmdb sp!, {r4-r10,lr}
	ldr r5, _020B5158 ; =0x021CED14
	mov r9, r1
	ldrh r1, [r9, #0x0]
	ldr r2, [r5, #0x0]
	mov r10, r0
	add r7, r2, #0x38
	mov r8, #0x0
	cmp r1, #0x0
	ldmlsia sp!, {r4-r10,pc}
_020B50B8: ; 0x020B50B8
	mov r6, #0x1
	mov r4, #0x6
_020B50C0:
	mul r1, r8, r4
	ldr r0, [r5, #0x0]
	str r6, [r0, #0x30]
	ldr r2, [r9, #0x4]
	ldrh r0, [r2, r1]
	add r1, r2, r1
	strh r0, [r7, #0x0]
	ldrh r0, [r1, #0x2]
	strh r0, [r7, #0x2]
	ldrh r0, [r1, #0x4]
	strh r0, [r7, #0x4]
	ldr r3, [r10, #0x20]
	cmp r3, #0x0
	beq _020B5108
	ldr r0, [r5, #0x0]
	mov r1, r9
	mov r2, r8
	blx r3
_020B5108:
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x30]
	cmp r0, #0x0
	beq _020B5120
	mov r0, r7
	bl FUN_020B515C
_020B5120:
	ldr r3, [r10, #0x24]
	cmp r3, #0x0
	beq _020B513C
	ldr r0, [r5, #0x0]
	mov r1, r9
	mov r2, r8
	blx r3
_020B513C:
	add r0, r8, #0x1
	mov r0, r0, lsl #0x10
	ldrh r1, [r9, #0x0]
	mov r8, r0, lsr #0x10
	cmp r8, r1
	blo _020B50C0
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020B5158: .word 0x021CED14

	arm_func_start FUN_020B515C
FUN_020B515C: ; 0x020B515C
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	ldr r1, _020B53A4 ; =0x021CED14
	mov r7, r0
	ldr r0, [r1, #0x0]
	add r0, r0, #0x40
	bl G3_LoadMtx43
	ldr r0, _020B53A4 ; =0x021CED14
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x24]
	cmp r1, #0x0
	beq _020B533C
	ldr r2, [r7, #0x0]
	ldr r1, _020B53A8 ; =0xC000C000
	and r4, r2, r1
	bl FUN_020B4F88
_020B519C: ; 0x020B519C
	cmp r0, #0x0
	beq _020B51F4
	ldr r0, [r7, #0x0]
	and r2, r4, #0xc000
	mov r0, r0, lsl #0x7
	mov r3, r0, lsr #0x17
	and r1, r4, #0xc0000000
	mov r1, r1, lsr #0x1e
	ldr r0, _020B53AC ; =0x020FF8AC
	mov r2, r2, asr #0xe
	mov r1, r1, lsl #0x1
	add r0, r0, r2, lsl #0x3
	cmp r3, #0xff
	ldrh r1, [r1, r0]
	orrgt r0, r3, #0xff00
	movgt r0, r0, lsl #0x10
	movgt r3, r0, asr #0x10
	add r0, r3, r1
	rsb r0, r0, #0x0
	mov r0, r0, lsl #0x10
	mov r1, r0, lsr #0x10
	b _020B5218
_020B51F4:
	ldr r0, [r7, #0x0]
	mov r0, r0, lsl #0x7
	mov r0, r0, lsr #0x17
	cmp r0, #0xff
	orrgt r0, r0, #0xff00
	movgt r0, r0, lsl #0x10
	movgt r0, r0, asr #0x10
	mov r0, r0, lsl #0x10
	mov r1, r0, lsr #0x10
_020B5218:
	ldr r0, _020B53A4 ; =0x021CED14
	mov r1, r1, lsl #0x10
	ldr r0, [r0, #0x0]
	mov r6, r1, asr #0x10
	bl FUN_020B4F74
_020B522C: ; 0x020B522C
	cmp r0, #0x0
	beq _020B527C
	and r1, r4, #0xc000
	and r0, r4, #0xc0000000
	ldrb r4, [r7, #0x0]
	ldr r2, _020B53B0 ; =0x020FF894
	mov r0, r0, lsr #0x1e
	mov r3, r1, asr #0xe
	mov r1, r0, lsl #0x1
	add r0, r2, r3, lsl #0x3
	cmp r4, #0x7f
	ldrh r1, [r1, r0]
	orrgt r0, r4, #0xff00
	movgt r0, r0, lsl #0x10
	movgt r4, r0, asr #0x10
	add r0, r4, r1
	rsb r0, r0, #0x0
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0x10
	b _020B5298
_020B527C:
	ldrb r0, [r7, #0x0]
	cmp r0, #0x7f
	orrgt r0, r0, #0xff00
	movgt r0, r0, lsl #0x10
	movgt r0, r0, asr #0x10
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0x10
_020B5298:
	ldr r0, _020B53A4 ; =0x021CED14
	ldr r1, [r7, #0x0]
	ldr r0, [r0, #0x0]
	mov r5, r1, lsl #0x3
	bl FUN_020B4F88
	ldr r2, [r7, #0x0]
	ldr r1, _020B53A4 ; =0x021CED14
	eor r5, r0, r5, lsr #0x1f
	ldr r0, [r1, #0x0]
	mov r8, r2, lsl #0x2
	bl FUN_020B4F74
	ldr r2, [r7, #0x0]
	eor r1, r0, r8, lsr #0x1f
	bic r0, r2, #0x10000000
	str r0, [r7, #0x0]
	ldr r2, [r7, #0x0]
	ldr r3, _020B53A4 ; =0x021CED14
	orr r2, r2, r5, lsl #0x1c
	str r2, [r7, #0x0]
	ldr r2, [r7, #0x0]
	mov r0, r6
	bic r2, r2, #0x20000000
	str r2, [r7, #0x0]
	ldr r5, [r7, #0x0]
	mov r2, r4, lsl #0x10
	orr r1, r5, r1, lsl #0x1d
	str r1, [r7, #0x0]
	ldr r5, [r3, #0x0]
	mov r1, r2, asr #0x10
	ldr r4, [r5, #0x8]
	mov r3, r7
	add r2, r4, #0xc
	str r2, [sp, #0x0]
	ldr r4, [r5, #0x14]
	mvn r2, #0x0
	str r4, [sp, #0x4]
	ldr r4, [r5, #0x18]
	str r4, [sp, #0x8]
	bl FUN_020B46B4
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}
_020B533C:
	ldr r2, _020B53A4 ; =0x021CED14
	ldr r0, [r7, #0x0]
	ldr r5, [r2, #0x0]
	mov r0, r0, lsl #0x7
	ldr r4, [r5, #0x8]
	mov r0, r0, lsr #0x17
	cmp r0, #0xff
	orrgt r0, r0, #0xff00
	movgt r0, r0, lsl #0x10
	ldrb r1, [r7, #0x0]
	add r4, r4, #0xc
	movgt r0, r0, asr #0x10
	str r4, [sp, #0x0]
	ldr r4, [r5, #0x14]
	cmp r1, #0x7f
	orrgt r1, r1, #0xff00
	movgt r1, r1, lsl #0x10
	str r4, [sp, #0x4]
	ldr r4, [r5, #0x18]
	movgt r1, r1, asr #0x10
	mov r3, r7
	mvn r2, #0x0
	str r4, [sp, #0x8]
	bl FUN_020B46B4
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020B53A4: .word 0x021CED14
_020B53A8: .word 0xC000C000
_020B53AC: .word 0x020FF8AC
_020B53B0: .word 0x020FF894

	arm_func_start FUN_020B53B4
FUN_020B53B4: ; 0x020B53B4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x44
	ldr r2, _020B57B0 ; =0x021CED14
	mov r10, r0
	ldr r0, [r2, #0x0]
	mov r11, r1
	ldr r9, [r0, #0x2c]
	ldr r1, _020B57B0 ; =0x021CED14
	cmp r9, #0x0
	ldreq sb, _020B57B4 ; =0x020FF958
	ldr r3, [r1, #0x0]
	ldr r4, [r9, #0x10]
	str r4, [sp, #0x18]
	ldr r2, [r9, #0x14]
	str r2, [sp, #0x1c]
	ldr r1, [r10, #0x0]
	sub r1, r4, r1
	str r1, [sp, #0x18]
	ldr r1, [r10, #0x4]
	sub r1, r2, r1
	str r1, [sp, #0x1c]
	ldr r2, [r3, #0x24]
	ldr r1, [r3, #0x10]
	cmp r2, #0x0
	str r1, [sp, #0x4]
	bne _020B5430
	ldr r1, [r3, #0x28]
	cmp r1, #0x0
	movne r1, #0x1
	strne r1, [sp, #0x0]
	bne _020B5438
_020B5430:
	mov r1, #0x0
	str r1, [sp, #0x0]
_020B5438:
	ldrh r1, [r11, #0x0]
	add r7, r0, #0x38
	mov r8, #0x0
	cmp r1, #0x0
	addls sp, sp, #0x44
	ldmlsia sp!, {r4-r11,pc}
_020B5450: ; 0x020B5450
	mov r0, #0x1
	ldr r4, _020B57B0 ; =0x021CED14
	str r8, [sp, #0x14]
	str r0, [sp, #0xc]
_020B5460:
	ldr r2, [r4, #0x0]
	ldr r0, [sp, #0xc]
	mov r1, #0x6
	str r0, [r2, #0x30]
	mul r0, r8, r1
	ldr r1, [r11, #0x4]
	add r2, r1, r0
	ldrh r0, [r1, r0]
	strh r0, [r7, #0x0]
	ldrh r0, [r2, #0x2]
	strh r0, [r7, #0x2]
	ldrh r0, [r2, #0x4]
	strh r0, [r7, #0x4]
	ldr r3, [r10, #0x20]
	cmp r3, #0x0
	beq _020B54B0
	ldr r0, [r4, #0x0]
	mov r1, r11
	mov r2, r8
	blx r3
_020B54B0:
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x30]
	cmp r0, #0x0
	beq _020B5790
	ldr r0, [sp, #0x0]
	ldr r1, [r7, #0x4]
	cmp r0, #0x0
	mov r0, #0x400
	rsb r0, r0, #0x0
	and r2, r1, r0
	ldr r0, [sp, #0x4]
	mov r1, r1, lsl #0x16
	add r1, r0, r1, lsr #0x16
	ldr r0, _020B57B8 ; =0x000003FF
	and r0, r1, r0
	orr r0, r2, r0
	str r0, [r7, #0x4]
	beq _020B5600
	ldr r0, [r10, #0x14]
	ldr lr, [r4, #0x0]
	sub r1, r0, #0x1
	ldr r0, [r7, #0x0]
	ldr r6, [lr, #0x28]
	mov r2, r0, lsl #0x2
	mov r2, r2, lsr #0x1f
	mov r2, r2, lsl #0x1
	mov r0, r0, lsl #0x3
	orr r5, r2, r0, lsr #0x1f
	add r0, r6, r5, lsl #0x2
	add r0, r0, r1, lsl #0x1
	ldrh r1, [r0, #0x10]
	ldr r0, _020B57BC ; =0x0000FFFF
	str r1, [sp, #0x8]
	cmp r1, r0
	bne _020B55CC
	cmp r5, #0x0
	bne _020B5558
	ldr r1, [lr, #0x20]
	mov r0, r6
	blx r1
	str r0, [sp, #0x8]
	b _020B55B4
_020B5558:
	ands r0, r5, #0x1
	add r12, sp, #0x30
	ldmia r6, {r0-r3}
	stmia r12, {r0-r3}
	beq _020B5584
	ldr r1, [sp, #0x30]
	ldr r0, [sp, #0x34]
	rsb r1, r1, #0x0
	str r1, [sp, #0x30]
	rsb r0, r0, #0x0
	str r0, [sp, #0x34]
_020B5584:
	ands r0, r5, #0x2
	beq _020B55A4
	ldr r1, [sp, #0x38]
	ldr r0, [sp, #0x3c]
	rsb r1, r1, #0x0
	str r1, [sp, #0x38]
	rsb r0, r0, #0x0
	str r0, [sp, #0x3c]
_020B55A4:
	ldr r1, [lr, #0x20]
	add r0, sp, #0x30
	blx r1
	str r0, [sp, #0x8]
_020B55B4:
	ldr r1, [r10, #0x14]
	add r0, r6, r5, lsl #0x2
	sub r1, r1, #0x1
	add r1, r0, r1, lsl #0x1
	ldr r0, [sp, #0x8]
	strh r0, [r1, #0x10]
_020B55CC:
	ldr r1, [r9, #0x0]
	add r0, sp, #0x20
	str r1, [sp, #0x20]
	ldr r2, [r9, #0x4]
	mov r1, r7
	str r2, [sp, #0x24]
	ldr r3, [r9, #0x8]
	add r2, sp, #0x18
	str r3, [sp, #0x28]
	ldr r3, [r9, #0xc]
	str r3, [sp, #0x2c]
	bl FUN_020B57D8
	b _020B5750
_020B5600:
	ldr r0, _020B57C0 ; =0x0000FFFE
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x0]
	ldr r1, [r0, #0x24]
	cmp r1, #0x0
	beq _020B5714
	ldr r2, [r7, #0x0]
	ldr r1, _020B57C4 ; =0xC000C000
	mov r6, r2, lsl #0x3
	and r5, r2, r1
	bl FUN_020B4F88
	ldr r1, [r7, #0x0]
	eor r6, r0, r6, lsr #0x1f
	mov r1, r1, lsl #0x2
	ldr r0, [r4, #0x0]
	str r1, [sp, #0x10]
	bl FUN_020B4F74
	ldr r1, [sp, #0x10]
	eor r0, r0, r1, lsr #0x1f
	ldr r1, [r7, #0x0]
	bic r1, r1, #0x10000000
	str r1, [r7, #0x0]
	ldr r1, [r7, #0x0]
	orr r1, r1, r6, lsl #0x1c
	str r1, [r7, #0x0]
	ldr r1, [r7, #0x0]
	bic r1, r1, #0x20000000
	str r1, [r7, #0x0]
	ldr r1, [r7, #0x0]
	orr r0, r1, r0, lsl #0x1d
	str r0, [r7, #0x0]
	ldr r0, [r4, #0x0]
	bl FUN_020B4F88
_020B5684: ; 0x020B5684
	cmp r0, #0x0
	beq _020B56D4
	and r1, r5, #0xc000
	mov r2, r1, asr #0xe
	ldr r1, _020B57C8 ; =0x020FF8AC
	and r3, r5, #0xc0000000
	mov r3, r3, lsr #0x1e
	add r2, r1, r2, lsl #0x3
	mov r3, r3, lsl #0x1
	ldr r0, [r7, #0x0]
	ldr r1, _020B57CC ; =0xFE00FFFF
	ldrh r2, [r3, r2]
	and r1, r0, r1
	mov r0, r0, lsl #0x7
	add r0, r2, r0, lsr #0x17
	rsb r2, r0, #0x0
	ldr r0, _020B57D0 ; =0x000001FF
	and r0, r2, r0
	orr r0, r1, r0, lsl #0x10
	str r0, [r7, #0x0]
_020B56D4:
	ldr r0, [r4, #0x0]
	bl FUN_020B4F74
_020B56DC: ; 0x020B56DC
	cmp r0, #0x0
	beq _020B5714
	and r1, r5, #0xc000
	mov r3, r1, asr #0xe
	and r1, r5, #0xc0000000
	mov r1, r1, lsr #0x1e
	mov r2, r1, lsl #0x1
	ldr r1, _020B57D4 ; =0x020FF894
	ldrb r0, [r7, #0x0]
	add r1, r1, r3, lsl #0x3
	ldrh r1, [r2, r1]
	add r0, r0, r1
	rsb r0, r0, #0x0
	strb r0, [r7, #0x0]
_020B5714:
	ldr r2, [r7, #0x0]
	ldr r0, _020B57CC ; =0xFE00FFFF
	ldr r1, [sp, #0x18]
	and r0, r2, r0
	mov r2, r2, lsl #0x7
	mov r2, r2, lsr #0x17
	add r2, r2, r1, asr #0xc
	ldr r1, _020B57D0 ; =0x000001FF
	and r1, r2, r1
	orr r0, r0, r1, lsl #0x10
	str r0, [r7, #0x0]
	ldrb r1, [r7, #0x0]
	ldr r0, [sp, #0x1c]
	add r0, r1, r0, asr #0xc
	strb r0, [r7, #0x0]
_020B5750:
	ldr r3, [r4, #0x0]
	ldr r1, [sp, #0x8]
	ldr r2, [sp, #0x14]
	ldr r3, [r3, #0x1c]
	mov r0, r7
	blx r3
	cmp r0, #0x1
	addne sp, sp, #0x44
	ldmneia sp!, {r4-r11,pc}
_020B5774: ; 0x020B5774
	ldr r3, [r10, #0x24]
	cmp r3, #0x0
	beq _020B5790
	ldr r0, [r4, #0x0]
	mov r1, r11
	mov r2, r8
	blx r3
_020B5790:
	add r0, r8, #0x1
	mov r0, r0, lsl #0x10
	mov r8, r0, lsr #0x10
	ldrh r0, [r11, #0x0]
	cmp r8, r0
	blo _020B5460
	add sp, sp, #0x44
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B57B0: .word 0x021CED14
_020B57B4: .word 0x020FF958
_020B57B8: .word 0x000003FF
_020B57BC: .word 0x0000FFFF
_020B57C0: .word 0x0000FFFE
_020B57C4: .word 0xC000C000
_020B57C8: .word 0x020FF8AC
_020B57CC: .word 0xFE00FFFF
_020B57D0: .word 0x000001FF
_020B57D4: .word 0x020FF894

	arm_func_start FUN_020B57D8
FUN_020B57D8: ; 0x020B57D8
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	ldr r4, [r1, #0x0]
	ldr r3, _020B5A9C ; =0x01FF0000
	and r3, r4, r3
	mov r3, r3, lsr #0x10
	mov r3, r3, lsl #0x10
	mov r3, r3, asr #0x10
	cmp r3, #0xff
	orrgt r3, r3, #0xff00
	movgt r3, r3, lsl #0x10
	movgt r3, r3, asr #0x10
	mov r3, r3, lsl #0xc
	str r3, [sp, #0x0]
	ldr r3, [r1, #0x0]
	and r3, r3, #0xff
	mov r3, r3, lsl #0x10
	mov r3, r3, asr #0x10
	cmp r3, #0x7f
	orrgt r3, r3, #0xff00
	movgt r3, r3, lsl #0x10
	movgt r3, r3, asr #0x10
	mov r3, r3, lsl #0xc
	str r3, [sp, #0x4]
	ldr r5, [r1, #0x0]
	and r4, r5, #0x300
	cmp r4, #0x100
	beq _020B5858
	cmp r4, #0x300
	beq _020B5858
	and r3, r5, #0x30000000
	orr r4, r4, r3
_020B5858:
	cmp r4, #0x300
	bne _020B58AC
	ldr r3, _020B5AA0 ; =0xC000C000
	ldr r4, _020B5AA4 ; =0x020FF8AC
	and r3, r5, r3
	and r5, r3, #0xc0000000
	and r3, r3, #0xc000
	mov r6, r5, lsr #0x1e
	mov r5, r3, asr #0xe
	ldr r3, _020B5AA8 ; =0x020FF894
	mov r6, r6, lsl #0x1
	add r4, r4, r5, lsl #0x3
	add r3, r3, r5, lsl #0x3
	ldrh r5, [r6, r4]
	ldr r7, [sp, #0x0]
	ldrh r3, [r6, r3]
	ldr r4, [sp, #0x4]
	add r5, r7, r5, lsl #0xb
	add r3, r4, r3, lsl #0xb
	str r5, [sp, #0x0]
	str r3, [sp, #0x4]
_020B58AC:
	ldr r5, [r0, #0x8]
	ldr r4, [sp, #0x4]
	add r3, sp, #0x0
	smull r8, r7, r5, r4
	cmp r3, r3
	ldr r6, [r0, #0x0]
	mov r4, #0x1000
	addeq r3, sp, #0x8
	adds r8, r8, r4
	ldr r5, [sp, #0x0]
	adc r7, r7, #0x0
	smlal r8, r7, r6, r5
	mov r5, r8, lsr #0xc
	orr r5, r5, r7, lsl #0x14
	str r5, [r3, #0x0]
	ldr r7, [r0, #0xc]
	ldr r6, [sp, #0x4]
	ldr r5, [r0, #0x4]
	smull r8, r6, r7, r6
	adds r7, r8, r4
	ldr r4, [sp, #0x0]
	adc r6, r6, #0x0
	smlal r7, r6, r5, r4
	mov r5, r7, lsr #0xc
	add r4, sp, #0x8
	orr r5, r5, r6, lsl #0x14
	str r5, [r3, #0x4]
	cmp r3, r4
	ldreq r3, [sp, #0xc]
	ldreq r4, [sp, #0x8]
	streq r3, [sp, #0x4]
	ldr r3, _020B5AAC ; =0x021CED14
	streq r4, [sp, #0x0]
	ldr r3, [r3, #0x0]
	ldr r3, [r3, #0x4]
	cmp r3, #0x0
	beq _020B597C
	cmp r3, #0x2
	moveq r5, #0x300
	movne r5, #0x100
	cmp r5, #0x100
	ldreq r4, [r1, #0x0]
	ldreq r3, _020B5AB0 ; =0xC1FFFCFF
	andeq r3, r4, r3
	orreq r3, r3, r5
	streq r3, [r1, #0x0]
	beq _020B597C
	ldr r4, [r1, #0x0]
	ldr r3, _020B5AB0 ; =0xC1FFFCFF
	and r3, r4, r3
	orr r3, r3, r5
	str r3, [r1, #0x0]
_020B597C:
	ldr r6, [r1, #0x0]
	and r5, r6, #0x300
	cmp r5, #0x100
	beq _020B599C
	cmp r5, #0x300
	beq _020B599C
	and r3, r6, #0x30000000
	orr r5, r5, r3
_020B599C:
	ldr r3, _020B5AA0 ; =0xC000C000
	ldr r4, _020B5AA4 ; =0x020FF8AC
	and r3, r6, r3
	and r6, r3, #0xc0000000
	and r3, r3, #0xc000
	mov lr, r3, asr #0xe
	mov r6, r6, lsr #0x1e
	mov r3, r6, lsl #0x1
	add r4, r4, lr, lsl #0x3
	ldrh r4, [r3, r4]
	ldr r6, [r0, #0x0]
	ldr r8, _020B5AA8 ; =0x020FF894
	mov r12, r4, asr #0x1
	mov r4, r12, lsl #0xc
	rsb r7, r4, #0x0
	mla r7, r6, r12, r7
	add lr, r8, lr, lsl #0x3
	ldrh r3, [r3, lr]
	ldr r6, [r0, #0x8]
	ldr lr, [sp, #0x0]
	mov r3, r3, asr #0x1
	mla r7, r6, r3, r7
	add r6, lr, r7
	str r6, [sp, #0x0]
	mov lr, r3, lsl #0xc
	ldr r6, [r0, #0x4]
	rsb r7, lr, #0x0
	mla r7, r6, r12, r7
	ldr r0, [r0, #0xc]
	ldr r6, [sp, #0x4]
	mla r3, r0, r3, r7
	add r0, r6, r3
	str r0, [sp, #0x4]
	cmp r5, #0x300
	moveq r0, #0x1
	movne r0, #0x0
	cmp r0, #0x0
	beq _020B5A4C
	ldr r3, [sp, #0x0]
	ldr r0, [sp, #0x4]
	sub r3, r3, r4
	sub r0, r0, lr
	str r3, [sp, #0x0]
	str r0, [sp, #0x4]
_020B5A4C:
	ldr r4, [sp, #0x0]
	ldr r0, [r2, #0x0]
	ldr r3, [sp, #0x4]
	add r5, r4, r0
	str r5, [sp, #0x0]
	ldr r2, [r2, #0x4]
	ldr r0, _020B5AB4 ; =0x000001FF
	add r2, r3, r2
	str r2, [sp, #0x4]
	mov r3, r2, asr #0xc
	ldr r4, [r1, #0x0]
	ldr r2, _020B5AB8 ; =0xFE00FF00
	and r3, r3, #0xff
	and r2, r4, r2
	and r4, r0, r5, asr #0xc
	orr r0, r2, r3
	orr r0, r0, r4, lsl #0x10
	str r0, [r1, #0x0]
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020B5A9C: .word 0x01FF0000
_020B5AA0: .word 0xC000C000
_020B5AA4: .word 0x020FF8AC
_020B5AA8: .word 0x020FF894
_020B5AAC: .word 0x021CED14
_020B5AB0: .word 0xC1FFFCFF
_020B5AB4: .word 0x000001FF
_020B5AB8: .word 0xFE00FF00

	arm_func_start FUN_020B5ABC
FUN_020B5ABC: ; 0x020B5ABC
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0xc
	add r5, sp, #0x0
	mov r4, #0x0
	str r4, [r5, #0x0]
	str r4, [r5, #0x4]
	mov r8, r2
	ldr r2, [sp, #0x28]
	mov r5, r0
	mov r9, r1
	mov r4, r3
	cmp r2, #0x0
	mov r7, #0x1
	beq _020B5B24
	add r6, sp, #0x28
_020B5AF8:
	mov r0, r9
	mov r1, r8
	mov r3, r6
	bl FUN_020B5BC8
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x28]
	cmp r0, r1
	strgt r0, [sp, #0x0]
	add r7, r7, #0x1
	cmp r2, #0x0
	bne _020B5AF8
_020B5B24:
	ldr r0, [r9, #0x0]
	sub r2, r7, #0x1
	ldrsb r1, [r0, #0x1]
	ldr r0, [sp, #0x0]
	add r1, r4, r1
	mul r1, r2, r1
	sub r1, r1, r4
	str r1, [sp, #0x4]
	str r0, [r5, #0x0]
	str r1, [r5, #0x4]
	add sp, sp, #0xc
	ldmia sp!, {r4-r9,pc}

	arm_func_start FUN_020B5B54
FUN_020B5B54: ; 0x020B5B54
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	str r2, [sp, #0x0]
	add r3, sp, #0x4
	mov r2, #0x0
	str r2, [r3, #0x0]
	mov r8, r0
	str r2, [r3, #0x4]
	ldr r7, [r8, #0x4]
	add r0, sp, #0x0
	mov r5, r1
	mov r4, #0x1
	blx r7
	cmp r0, #0x0
	beq _020B5BAC
	add r6, sp, #0x0
_020B5B94:
	cmp r0, #0xa
	mov r0, r6
	addeq r4, r4, #0x1
	blx r7
	cmp r0, #0x0
	bne _020B5B94
_020B5BAC:
	ldr r0, [r8, #0x0]
	ldrsb r0, [r0, #0x1]
	add r0, r5, r0
	mul r0, r4, r0
	sub r0, r0, r5
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020B5BC8
FUN_020B5BC8:
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x8
	mov r8, r0
	str r2, [sp, #0x0]
	ldr r4, [r8, #0x4]
	add r0, sp, #0x0
	mov r7, r1
	mov r6, r3
	mov r5, #0x0
	blx r4
	movs r1, r0
	beq _020B5C58
	ldr sb, _020B5C84 ; =0x0000FFFF
	add r10, sp, #0x0
_020B5C00:
	cmp r1, #0xa
	beq _020B5C58
	mov r0, r8
	bl FUN_020B5CE4
	mov r1, r0
	cmp r1, r9
	ldreq r0, [r8, #0x0]
	ldreqh r1, [r0, #0x2]
	mov r0, r8
	bl FUN_020B5C88
	ldrh r1, [r8, #0x8]
	cmp r1, #0x0
	ldrnesb r1, [r0, #0x0]
	ldrneb r0, [r0, #0x1]
	addne r0, r1, r0
	ldreqsb r0, [r0, #0x2]
	add r1, r7, r0
	mov r0, r10
	add r5, r5, r1
	blx r4
	movs r1, r0
	bne _020B5C00
_020B5C58:
	cmp r6, #0x0
	beq _020B5C70
	cmp r1, #0xa
	ldreq r0, [sp, #0x0]
	movne r0, #0x0
	str r0, [r6, #0x0]
_020B5C70:
	cmp r5, #0x0
	subgt r5, r5, r7
	mov r0, r5
	add sp, sp, #0x8
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020B5C84: .word 0x0000FFFF

	arm_func_start FUN_020B5C88
FUN_020B5C88: ; 0x020B5C88
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r0, #0x0]
	ldr lr, [r3, #0xc]
	cmp lr, #0x0
	beq _020B5CD8
_020B5CA0:
	ldrh r12, [lr, #0x0]
	cmp r12, r1
	bhi _020B5CCC
	ldrh r2, [lr, #0x2]
	cmp r1, r2
	ldrlsh r2, [r0, #0xa]
	addls r3, lr, #0x8
	subls r0, r1, r12
	mlals r0, r2, r0, r3
	addls sp, sp, #0x4
	ldmlsia sp!, {pc}
_020B5CCC:
	ldr lr, [lr, #0x4]
	cmp lr, #0x0
	bne _020B5CA0
_020B5CD8:
	add r0, r3, #0x4
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020B5CE4
FUN_020B5CE4: ; 0x020B5CE4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	beq _020B5D2C
_020B5CFC:
	ldrh r2, [r0, #0x0]
	cmp r2, r1
	bhi _020B5D20
	ldrh r2, [r0, #0x2]
	cmp r1, r2
	bhi _020B5D20
	bl FUN_020B5D7C
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020B5D20:
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	bne _020B5CFC
_020B5D2C:
	ldr r0, _020B5D38 ; =0x0000FFFF
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B5D38: .word 0x0000FFFF

	arm_func_start FUN_020B5D3C
FUN_020B5D3C: ; 0x020B5D3C
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, r1
	mov r1, r4
	bl FUN_020B7558
	sub r0, r0, #0x1
	strh r0, [r4, #0x8]
	ldrh r0, [r4, #0x8]
	cmp r0, #0x0
	movne r1, #0x2
	moveq r1, #0x3
	ldr r0, _020B5D78 ; =FUN_020B7718
	strh r1, [r4, #0xa]
	str r0, [r4, #0x4]
	ldmia sp!, {r4,pc}
	.balign 4
_020B5D78: .word FUN_020B7718

	arm_func_start FUN_020B5D7C
FUN_020B5D7C: ; 0x020B5D7C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r3, [r0, #0x4]
	ldr r2, _020B5E4C ; =0x0000FFFF
	cmp r3, #0x0
	beq _020B5DA8
	cmp r3, #0x1
	beq _020B5DC4
	cmp r3, #0x2
	beq _020B5DD8
	b _020B5E40
_020B5DA8:
	ldrh r2, [r0, #0x0]
	ldrh r3, [r0, #0xc]
	sub r0, r1, r2
	add r0, r3, r0
	mov r0, r0, lsl #0x10
	mov r2, r0, lsr #0x10
	b _020B5E40
_020B5DC4:
	ldrh r2, [r0, #0x0]
	sub r1, r1, r2
	add r0, r0, r1, lsl #0x1
	ldrh r2, [r0, #0xc]
	b _020B5E40
_020B5DD8:
	ldrh r3, [r0, #0xc]
	add r0, r0, #0xc
	add r0, r0, #0x2
	sub r3, r3, #0x1
	add lr, r0, r3, lsl #0x2
	cmp r0, lr
	bhi _020B5E40
_020B5DF4:
	sub r12, lr, r0
	mov r3, r12, asr #0x1
	add r3, r12, r3, lsr #0x1e
	mov r3, r3, asr #0x2
	add r3, r3, r3, lsr #0x1f
	mov r12, r3, asr #0x1
	mov r3, r12, lsl #0x2
	ldrh r3, [r0, r3]
	add r12, r0, r12, lsl #0x2
	cmp r3, r1
	addcc r0, r12, #0x4
	blo _020B5E38
	cmp r1, r3
	subcc lr, r12, #0x4
	blo _020B5E38
	ldrh r2, [r12, #0x2]
	b _020B5E40
_020B5E38:
	cmp r0, lr
	bls _020B5DF4
_020B5E40:
	mov r0, r2
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B5E4C: .word 0x0000FFFF

	arm_func_start FUN_020B5E50
FUN_020B5E50: ; 0x020B5E50
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x3c
	mov r7, r0
	mov r0, r1
	cmp r0, #0x8
	ldr r0, [sp, #0x60]
	str r1, [sp, #0x10]
	str r0, [sp, #0x60]
	ldr r0, [sp, #0x6c]
	str r2, [sp, #0x14]
	str r0, [sp, #0x6c]
	ldrlt r0, [sp, #0x10]
	mov r11, r3
	ldr r6, [sp, #0x64]
	ldr r5, [sp, #0x68]
	movge r2, #0x3
	clzlt r0, r0
	rsblt r2, r0, #0x1f
	ldr r0, [sp, #0x14]
	cmp r0, #0x8
	ldrlt r0, [sp, #0x14]
	movge r1, #0x3
	clzlt r0, r0
	rsblt r1, r0, #0x1f
	ldr r0, _020B6170 ; =0x020FF970
	mvn r3, #0x0
	add r1, r0, r1, lsl #0x3
	add r0, r1, r2, lsl #0x1
	ldrb r4, [r1, r2, lsl #0x1]
	ldrb r1, [r0, #0x1]
	ldr r2, [sp, #0x14]
	cmp r6, #0x0
	str r1, [sp, #0x18]
	ldr r1, [sp, #0x10]
	and r1, r1, r3, lsl r4
	str r1, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	and r1, r2, r3, lsl r1
	str r1, [sp, #0x20]
	moveq r1, #0x1
	streq r1, [sp, #0x24]
	movne r1, #0x2
	strne r1, [sp, #0x24]
	mov r1, #0x0
	str r1, [sp, #0x28]
	bl FUN_020B704C
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0x14]
	mov r10, r1, asr r4
	ldr r1, [sp, #0x18]
	mov r1, r2, asr r1
	str r1, [sp, #0x2c]
	ldr r1, [sp, #0x24]
	mov r2, r1, lsl r4
	ldr r1, [sp, #0x18]
	mov r2, r2, lsl r1
	ldr r1, [sp, #0x6c]
	mov r9, r2, asr r1
	mov r1, #0x0
	str r1, [sp, #0x30]
	str r1, [sp, #0x34]
	b _020B5FE8
_020B5F48:
	ldr r2, [sp, #0x30]
	ldr r1, [sp, #0x18]
	ldr r8, [sp, #0x34]
	mov r2, r2, lsl r1
	ldr r1, [sp, #0x60]
	add lr, r1, r2, lsl #0x3
	b _020B5FD4
_020B5F64:
	mov r1, r8, lsl r4
	add r2, r11, r1, lsl #0x3
	ldr r1, _020B6174 ; =0x000001FF
	ldr r3, [r7, #0x0]
	and r12, r2, r1
	ldr r1, _020B6178 ; =0xFE00FF00
	and r2, lr, #0xff
	and r1, r3, r1
	orr r1, r1, r2
	orr r1, r1, r12, lsl #0x10
	str r1, [r7, #0x0]
	ldr r3, [r7, #0x0]
	ldr r1, _020B617C ; =0x3FFF3FFF
	mov r2, #0x400
	and r1, r3, r1
	orr r1, r1, r0
	str r1, [r7, #0x0]
	rsb r1, r2, #0x0
	ldrh r2, [r7, #0x4]
	add r8, r8, #0x1
	and r1, r2, r1
	orr r1, r1, r5
	strh r1, [r7, #0x4]
	ldr r1, [r7, #0x0]
	add r5, r5, r9
	bic r1, r1, #0x2000
	orr r1, r1, r6, lsl #0xd
	str r1, [r7], #0x8
_020B5FD4:
	cmp r8, r10
	blt _020B5F64
	ldr r1, [sp, #0x30]
	add r1, r1, #0x1
	str r1, [sp, #0x30]
_020B5FE8:
	ldr r2, [sp, #0x30]
	ldr r1, [sp, #0x2c]
	cmp r2, r1
	blt _020B5F48
	ldr r0, [sp, #0x28]
	mla r0, r10, r1, r0
	str r0, [sp, #0x28]
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x10]
	cmp r1, r0
	bhs _020B6078
	ldr r0, [sp, #0x60]
	ldr r1, [sp, #0x10]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x1c]
	str r6, [sp, #0x4]
	sub r4, r1, r0
	ldr r1, [sp, #0x6c]
	str r5, [sp, #0x8]
	str r1, [sp, #0xc]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x20]
	add r3, r11, r1, lsl #0x3
	mov r0, r7
	mov r1, r4
	bl FUN_020B5E50
	ldr r1, [sp, #0x24]
	add r7, r7, r0, lsl #0x3
	mul r2, r1, r4
	ldr r1, [sp, #0x20]
	mul r2, r1, r2
	ldr r1, [sp, #0x6c]
	add r5, r5, r2, lsr r1
	ldr r1, [sp, #0x28]
	add r0, r1, r0
	str r0, [sp, #0x28]
_020B6078:
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bhs _020B60F0
	ldr r1, [sp, #0x60]
	ldr r0, [sp, #0x20]
	mov r3, r11
	add r0, r1, r0, lsl #0x3
	str r0, [sp, #0x0]
	str r6, [sp, #0x4]
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x20]
	str r5, [sp, #0x8]
	sub r4, r1, r0
	ldr r1, [sp, #0x6c]
	mov r0, r7
	str r1, [sp, #0xc]
	ldr r1, [sp, #0x1c]
	mov r2, r4
	bl FUN_020B5E50
	ldr r2, [sp, #0x24]
	ldr r1, [sp, #0x1c]
	add r7, r7, r0, lsl #0x3
	mul r1, r2, r1
	mul r2, r4, r1
	ldr r1, [sp, #0x6c]
	add r5, r5, r2, lsr r1
	ldr r1, [sp, #0x28]
	add r0, r1, r0
	str r0, [sp, #0x28]
_020B60F0:
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x10]
	cmp r1, r0
	bhs _020B6164
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bhs _020B6164
	ldr r1, [sp, #0x60]
	ldr r0, [sp, #0x20]
	ldr r2, [sp, #0x10]
	add r0, r1, r0, lsl #0x3
	ldr r1, [sp, #0x1c]
	ldr r3, [sp, #0x14]
	str r0, [sp, #0x0]
	sub r1, r2, r1
	ldr r2, [sp, #0x20]
	str r6, [sp, #0x4]
	sub r2, r3, r2
	ldr r3, [sp, #0x1c]
	ldr r4, [sp, #0x6c]
	str r5, [sp, #0x8]
	mov r0, r7
	add r3, r11, r3, lsl #0x3
	str r4, [sp, #0xc]
	bl FUN_020B5E50
	ldr r1, [sp, #0x28]
	add r0, r1, r0
	str r0, [sp, #0x28]
_020B6164:
	ldr r0, [sp, #0x28]
	add sp, sp, #0x3c
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B6170: .word 0x020FF970
_020B6174: .word 0x000001FF
_020B6178: .word 0xFE00FF00
_020B617C: .word 0x3FFF3FFF

	arm_func_start FUN_020B6180
FUN_020B6180: ; 0x020B6180
	stmdb sp!, {r4-r6,lr}
	mov r3, r0, lsr #0x3
	mov r6, r1, lsr #0x3
	mul r12, r3, r6
	and r2, r0, #0x4
	and lr, r0, #0x2
	and r0, r0, #0x1
	add r4, r0, lr, lsr #0x1
	mov r5, r2, lsr #0x2
	and r0, r1, #0x4
	add lr, r12, #0x0
	add r12, r5, r4, lsl #0x1
	mla r12, r6, r12, lr
	and lr, r1, #0x2
	and r1, r1, #0x1
	add lr, r1, lr, lsr #0x1
	mov r1, r0, lsr #0x2
	add r1, r1, lr, lsl #0x1
	mla r12, r3, r1, r12
	add r1, r4, r2, lsr #0x2
	add r0, lr, r0, lsr #0x2
	mla r0, r1, r0, r12
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020B61DC
FUN_020B61DC: ; 0x020B61DC
	stmdb sp!, {r4-r8,lr}
	ldr r12, [sp, #0x1c]
	ldr r8, [sp, #0x18]
	mov r12, r12, lsl #0x1c
	mov r4, r12, lsr #0x10
	mov r6, #0x0
	cmp r2, #0x0
	ldmleia sp!, {r4-r8,pc}
_020B61FC: ; 0x020B61FC
	mov lr, r3, lsl #0x1
	mov r12, r6
_020B6204:
	mov r5, r0
	mov r7, r12
	cmp r1, #0x0
	ble _020B622C
_020B6214:
	orr r3, r4, r8
	add r7, r7, #0x1
	cmp r7, r1
	add r8, r8, #0x1
	strh r3, [r5], #0x2
	blt _020B6214
_020B622C:
	add r6, r6, #0x1
	cmp r6, r2
	add r0, r0, lr
	blt _020B6204
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020B6240
FUN_020B6240: ; 0x020B6240
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	ldr r5, [sp, #0x24]
	ldr lr, [sp, #0x20]
	cmp r5, #0x20
	ldr r12, [sp, #0x28]
	bgt _020B6280
	mla r4, r5, lr, r3
	ldr lr, [sp, #0x2c]
	str r12, [sp, #0x0]
	mov r3, r5
	add r0, r0, r4, lsl #0x1
	str lr, [sp, #0x4]
	bl FUN_020B61DC
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,pc}
_020B6280:
	ldr r4, [sp, #0x2c]
	add r7, lr, r2
	mov r2, r4, lsl #0x1c
	cmp lr, r7
	add r8, r3, r1
	mov r4, r2, lsr #0x10
	addge sp, sp, #0x8
	ldmgeia sp!, {r4-r8,pc}
_020B62A0:
	cmp lr, #0x20
	movlt r1, lr
	addge r1, lr, #0x20
	mov r6, r3
	cmp r3, r8
	add r5, r0, r1, lsl #0x6
	bge _020B62E4
_020B62BC:
	cmp r6, #0x20
	movlt r1, r6
	addge r1, r6, #0x3e0
	orr r2, r4, r12
	mov r1, r1, lsl #0x1
	add r6, r6, #0x1
	strh r2, [r5, r1]
	cmp r6, r8
	add r12, r12, #0x1
	blt _020B62BC
_020B62E4:
	add lr, lr, #0x1
	cmp lr, r7
	blt _020B62A0
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020B62F8
FUN_020B62F8: ; 0x020B62F8
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x18
	cmp r2, #0x8
	movlt r4, r2
	movge r12, #0x3
	clzlt r4, r4
	rsblt r12, r4, #0x1f
	cmp r3, #0x8
	movlt r4, r3
	movge r6, #0x3
	clzlt r4, r4
	rsblt r6, r4, #0x1f
	ldr r4, _020B6378 ; =0x020FF970
	ldr r5, [sp, #0x28]
	add r4, r4, r6, lsl #0x3
	ldrb r6, [r4, r12, lsl #0x1]
	add r12, r4, r12, lsl #0x1
	ldr r4, _020B637C ; =FUN_020B6908
	strb r6, [sp, #0x14]
	ldrb r6, [r12, #0x1]
	ldr lr, _020B6380 ; =FUN_020B68AC
	ldr ip, _020B6384 ; =FUN_020B64C0
	strb r6, [sp, #0x15]
	str r5, [sp, #0x0]
	str r4, [sp, #0x4]
	str lr, [sp, #0x8]
	str r12, [sp, #0xc]
	ldr r12, [sp, #0x14]
	str r12, [sp, #0x10]
	bl FUN_020B6488
	add sp, sp, #0x18
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B6378: .word 0x020FF970
_020B637C: .word FUN_020B6908
_020B6380: .word FUN_020B68AC
_020B6384: .word FUN_020B64C0

	arm_func_start FUN_020B6388
FUN_020B6388: ; 0x020B6388
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	ldr lr, [sp, #0x18]
	ldr ip, _020B63C0 ; =FUN_020B6B10
	str lr, [sp, #0x0]
	ldr lr, _020B63C4 ; =FUN_020B68AC
	str r12, [sp, #0x4]
	ldr ip, _020B63C8 ; =FUN_020B66D4
	str lr, [sp, #0x8]
	str r12, [sp, #0xc]
	str r2, [sp, #0x10]
	bl FUN_020B6488
	add sp, sp, #0x14
	ldmia sp!, {pc}
	.balign 4
_020B63C0: .word FUN_020B6B10
_020B63C4: .word FUN_020B68AC
_020B63C8: .word FUN_020B66D4

	arm_func_start FUN_020B63CC
FUN_020B63CC: ; 0x020B63CC
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	mov r7, r1
	ldrh r1, [sp, #0x2c]
	mov r8, r0
	mov r0, r7
	mov r6, r2
	mov r5, r3
	bl FUN_020B5CE4
	ldr r1, _020B6484 ; =0x0000FFFF
	mov r4, r0
	cmp r4, r1
	ldreq r0, [r7, #0x0]
	ldreqh r4, [r0, #0x2]
	mov r0, r7
	mov r1, r4
	bl FUN_020B5C88
	str r0, [sp, #0x8]
	ldr r0, [r7, #0x0]
	ldr r2, [sp, #0x28]
	ldr r0, [r0, #0x8]
	add r1, sp, #0x8
	ldrh r3, [r0, #0x2]
	add r12, r0, #0x8
	mov r0, r8
	mla r3, r4, r3, r12
	str r3, [sp, #0xc]
	str r2, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x8]
	ldr r4, [r8, #0x14]
	ldrsb r2, [r1, #0x0]
	mov r1, r7
	mov r3, r5
	add r2, r6, r2
	blx r4
	ldrh r0, [r7, #0x8]
	cmp r0, #0x0
	ldrne r0, [sp, #0x8]
	ldrnesb r1, [r0, #0x0]
	ldrneb r0, [r0, #0x1]
	addne r0, r1, r0
	ldreq r0, [sp, #0x8]
	ldreqsb r0, [r0, #0x2]
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020B6484: .word 0x0000FFFF

	arm_func_start FUN_020B6488
FUN_020B6488: ; 0x020B6488
	str r2, [r0, #0x4]
	ldr r2, [sp, #0x0]
	str r3, [r0, #0x8]
	strb r2, [r0, #0xc]
	ldr r2, [sp, #0x4]
	str r1, [r0, #0x0]
	ldr r1, [sp, #0x8]
	str r2, [r0, #0x14]
	ldr r2, [sp, #0xc]
	str r1, [r0, #0x18]
	ldr r1, [sp, #0x10]
	str r2, [r0, #0x1c]
	str r1, [r0, #0x10]
	bx lr

	arm_func_start FUN_020B64C0
FUN_020B64C0: ; 0x020B64C0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x54
	ldrb r4, [r0, #0xc]
	mov r10, r2
	str r1, [sp, #0xc]
	str r4, [sp, #0x44]
	ldr r1, [sp, #0x44]
	ldr r4, [sp, #0x78]
	cmp r1, #0x4
	add r1, r10, r4
	str r1, [sp, #0x1c]
	ldr r2, [sp, #0x7c]
	mov r1, r3
	add r1, r1, r2
	str r1, [sp, #0x20]
	ldrne r1, [sp, #0xc]
	str r3, [sp, #0x10]
	orrne r1, r1, r1, lsl #0x8
	orrne r1, r1, r1, lsl #0x10
	strne r1, [sp, #0xc]
	bne _020B6528
	ldr r1, [sp, #0xc]
	orr r1, r1, r1, lsl #0x4
	orr r1, r1, r1, lsl #0x8
	orr r1, r1, r1, lsl #0x10
	str r1, [sp, #0xc]
_020B6528:
	bic r1, r10, #0x7
	str r1, [sp, #0x30]
	ldr r1, [sp, #0x10]
	ldr r2, [r0, #0x10]
	bic r1, r1, #0x7
	str r1, [sp, #0x14]
	ldr r1, [sp, #0x44]
	str r2, [sp, #0x4c]
	mov r3, r1, lsl #0x6
	mov r2, r3, asr #0x2
	ldr r1, [sp, #0x20]
	add r3, r3, r2, lsr #0x1d
	ldr r2, [sp, #0x1c]
	add r6, r1, #0x7
	add r2, r2, #0x7
	bic r5, r2, #0x7
	bic r2, r6, #0x7
	ldr r1, [sp, #0x30]
	str r2, [sp, #0x24]
	mov r2, r3, asr #0x3
	str r2, [sp, #0x48]
	mov r4, r1, asr #0x2
	ldr r2, [sp, #0x30]
	ldr r1, [sp, #0x14]
	add r2, r2, r4, lsr #0x1d
	mov r2, r2, asr #0x3
	str r2, [sp, #0x2c]
	ldr r2, [sp, #0x14]
	mov r1, r1, asr #0x2
	add r1, r2, r1, lsr #0x1d
	mov r6, r1, asr #0x3
	ldr r1, [sp, #0x24]
	cmp r2, r1
	ldr r1, [r0, #0x4]
	str r1, [sp, #0x40]
	ldr r1, [r0, #0x8]
	ldr r0, [r0, #0x0]
	str r1, [sp, #0x3c]
	str r0, [sp, #0x28]
	ldrb r0, [sp, #0x4c]
	str r0, [sp, #0x38]
	ldrb r0, [sp, #0x4d]
	str r0, [sp, #0x34]
	addge sp, sp, #0x54
	ldmgeia sp!, {r4-r11,pc}
_020B65DC: ; 0x020B65DC
	mov r4, #0x0
	mov r11, #0x8
_020B65E4:
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x10]
	ldr r7, [sp, #0x2c]
	cmp r1, r0
	movlt r1, r0
	ldrlt r0, [sp, #0x14]
	sublt r9, r1, r0
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #0x14]
	movge r9, r4
	sub r0, r1, r0
	cmp r0, #0x8
	movgt r0, r11
	sub r0, r0, r9
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x30]
	cmp r0, r5
	mov r8, r0
	bge _020B66B0
_020B6630:
	ldr r0, [sp, #0x38]
	ldr r2, [sp, #0x40]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x34]
	ldr r3, [sp, #0x3c]
	str r0, [sp, #0x4]
	mov r0, r7
	mov r1, r6
	bl FUN_020B7068
	ldr r2, [sp, #0x1c]
	cmp r8, r10
	sublt r1, r10, r8
	sub r2, r2, r8
	movge r1, r4
	cmp r2, #0x8
	movgt r2, r11
	sub r3, r2, r1
	ldr r2, [sp, #0x18]
	ldr r12, [sp, #0x48]
	str r2, [sp, #0x0]
	ldr r2, [sp, #0xc]
	str r2, [sp, #0x4]
	ldr r2, [sp, #0x44]
	str r2, [sp, #0x8]
	ldr r2, [sp, #0x28]
	mla r0, r12, r0, r2
	mov r2, r9
	bl FUN_020B6F18
	add r8, r8, #0x8
	add r7, r7, #0x1
	cmp r8, r5
	blt _020B6630
_020B66B0:
	ldr r0, [sp, #0x14]
	add r6, r6, #0x1
	add r1, r0, #0x8
	ldr r0, [sp, #0x24]
	str r1, [sp, #0x14]
	cmp r1, r0
	blt _020B65E4
	add sp, sp, #0x54
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020B66D4
FUN_020B66D4: ; 0x020B66D4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x3c
	ldrb r4, [r0, #0xc]
	mov r10, r2
	str r1, [sp, #0xc]
	str r4, [sp, #0x2c]
	ldr r1, [sp, #0x2c]
	ldr r4, [sp, #0x60]
	cmp r1, #0x4
	add r1, r10, r4
	str r1, [sp, #0x18]
	ldr r2, [sp, #0x64]
	mov r1, r3
	add r1, r1, r2
	str r1, [sp, #0x1c]
	ldrne r1, [sp, #0xc]
	str r3, [sp, #0x10]
	orrne r1, r1, r1, lsl #0x8
	orrne r1, r1, r1, lsl #0x10
	strne r1, [sp, #0xc]
	bne _020B673C
	ldr r1, [sp, #0xc]
	orr r1, r1, r1, lsl #0x4
	orr r1, r1, r1, lsl #0x8
	orr r1, r1, r1, lsl #0x10
	str r1, [sp, #0xc]
_020B673C:
	ldr r1, [sp, #0x10]
	bic r1, r1, #0x7
	mov r2, r1, asr #0x2
	str r1, [sp, #0x14]
	add r1, r1, r2, lsr #0x1d
	ldr r2, [r0, #0x10]
	mov r3, r1, asr #0x3
	mul r1, r3, r2
	bic r3, r10, #0x7
	str r3, [sp, #0x28]
	ldr r3, [sp, #0x2c]
	mov r6, r3, lsl #0x6
	ldr r3, [sp, #0x28]
	mov r4, r6, asr #0x2
	mov r5, r3, asr #0x2
	add r5, r3, r5, lsr #0x1d
	add r4, r6, r4, lsr #0x1d
	mov r3, r4, asr #0x3
	str r3, [sp, #0x30]
	ldr r3, [sp, #0x1c]
	add r1, r1, r5, asr #0x3
	add r4, r3, #0x7
	ldr r3, [r0, #0x0]
	ldr r0, [sp, #0x18]
	add r5, r0, #0x7
	ldr r0, [sp, #0x30]
	bic r7, r5, #0x7
	mla r1, r0, r1, r3
	bic r0, r4, #0x7
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x30]
	str r1, [sp, #0x24]
	mul r0, r2, r0
	str r0, [sp, #0x34]
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x20]
	cmp r1, r0
	addge sp, sp, #0x3c
	ldmgeia sp!, {r4-r11,pc}
_020B67D8: ; 0x020B67D8
	mov r5, #0x0
	mov r4, #0x8
_020B67E0:
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x10]
	ldr r6, [sp, #0x24]
	cmp r1, r0
	movlt r1, r0
	ldrlt r0, [sp, #0x14]
	sublt r9, r1, r0
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x14]
	movge r9, r5
	sub r0, r1, r0
	cmp r0, #0x8
	movgt r0, r4
	sub r11, r0, r9
	ldr r0, [sp, #0x28]
	cmp r0, r7
	mov r8, r0
	bge _020B687C
_020B6828:
	ldr r0, [sp, #0x18]
	cmp r8, r10
	sublt r1, r10, r8
	sub r0, r0, r8
	movge r1, r5
	cmp r0, #0x8
	movgt r0, r4
	sub r3, r0, r1
	ldr r0, [sp, #0xc]
	str r11, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x2c]
	mov r2, r9
	str r0, [sp, #0x8]
	mov r0, r6
	bl FUN_020B6F18
	ldr r0, [sp, #0x30]
	add r8, r8, #0x8
	add r6, r6, r0
	cmp r8, r7
	blt _020B6828
_020B687C:
	ldr r1, [sp, #0x24]
	ldr r0, [sp, #0x34]
	add r0, r1, r0
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x14]
	add r1, r0, #0x8
	ldr r0, [sp, #0x20]
	str r1, [sp, #0x14]
	cmp r1, r0
	blt _020B67E0
	add sp, sp, #0x3c
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020B68AC
FUN_020B68AC: ; 0x020B68AC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r3, r0
	ldrb r2, [r3, #0xc]
	ldr r12, [r3, #0x4]
	cmp r2, #0x4
	orreq r0, r1, r1, lsl #0x4
	orreq r0, r0, r0, lsl #0x8
	orreq r1, r0, r0, lsl #0x10
	orrne r0, r1, r1, lsl #0x8
	orrne r1, r0, r0, lsl #0x10
	ldr r0, [r3, #0x8]
	mov r2, r2, lsl #0x6
	mul lr, r12, r0
	mov r0, r2, asr #0x2
	add r0, r2, r0, lsr #0x1d
	mov r2, r0, asr #0x3
	mov r0, r1
	mul r2, lr, r2
	ldr r1, [r3, #0x0]
	bl MIi_CpuClearFast
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020B6908
FUN_020B6908: ; 0x020B6908
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4c
	ldr r7, [sp, #0x74]
	ldrb r5, [r0, #0xc]
	ldr r6, [r1, #0x0]
	ldr r4, [r7, #0x0]
	ldr r9, [r6, #0x8]
	mov r8, r5, lsl #0x6
	ldrb r4, [r4, #0x1]
	mov r5, r8, asr #0x2
	add r5, r8, r5, lsr #0x1d
	ldrb r9, [r9, #0x1]
	ldr r8, [r0, #0x4]
	ldr r6, [r0, #0x8]
	str r2, [sp, #0x8]
	str r3, [sp, #0xc]
	cmp r4, #0x0
	mov r5, r5, asr #0x3
	addeq sp, sp, #0x4c
	ldmeqia sp!, {r4-r11,pc}
_020B6958: ; 0x020B6958
	adds r3, r2, r4
	addmi sp, sp, #0x4c
	ldmmiia sp!, {r4-r11,pc}
_020B6964: ; 0x020B6964
	ldr r2, [sp, #0xc]
	adds r2, r2, r9
	addmi sp, sp, #0x4c
	ldmmiia sp!, {r4-r11,pc}
_020B6974: ; 0x020B6974
	ldr r10, [sp, #0x8]
	add r3, r3, #0x7
	cmp r10, #0x0
	movle r10, #0x0
	strle r10, [sp, #0x10]
	movgt r10, r10, lsr #0x3
	strgt r10, [sp, #0x10]
	ldr r10, [sp, #0xc]
	add r2, r2, #0x7
	cmp r10, #0x0
	movle r10, #0x0
	mov r11, r2, lsr #0x3
	mov r3, r3, lsr #0x3
	movgt r10, r10, lsr #0x3
	cmp r3, r8
	movcs r3, r8
	cmp r11, r6
	ldr r2, [sp, #0x10]
	movcs r11, r6
	subs r8, r3, r2
	addmi sp, sp, #0x4c
	sub r3, r11, r10
	ldmmiia sp!, {r4-r11,pc}
_020B69D0: ; 0x020B69D0
	cmp r3, #0x0
	addlt sp, sp, #0x4c
	ldmltia sp!, {r4-r11,pc}
_020B69DC: ; 0x020B69DC
	ldr r2, [sp, #0x8]
	ldr r6, [r0, #0x0]
	cmp r2, #0x0
	andge r2, r2, #0x7
	strge r2, [sp, #0x8]
	ldr r2, [sp, #0xc]
	ldr r11, [sp, #0x8]
	cmp r2, #0x0
	andge r2, r2, #0x7
	strge r2, [sp, #0xc]
	sub r8, r11, r8, lsl #0x3
	ldr r11, [sp, #0xc]
	ldr r2, [sp, #0x70]
	sub r3, r11, r3, lsl #0x3
	str r3, [sp, #0x14]
	ldr r3, [r7, #0x4]
	sub r2, r2, #0x1
	str r3, [sp, #0x28]
	str r2, [sp, #0x48]
	str r9, [sp, #0x38]
	str r4, [sp, #0x34]
	ldr r4, [r1, #0x0]
	ldr r2, [sp, #0x14]
	mov r3, r11
	cmp r3, r2
	ldr r2, [r4, #0x8]
	ldrb r3, [r2, #0x6]
	str r3, [sp, #0x40]
	ldrb r2, [r0, #0xc]
	str r2, [sp, #0x44]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x8]
	ldrb r1, [r1, #0x0]
	mul r1, r3, r1
	str r1, [sp, #0x3c]
	ldr r1, [r0, #0x10]
	str r1, [sp, #0x20]
	ldr r1, [r0, #0x4]
	ldr r0, [r0, #0x8]
	ldrb r11, [sp, #0x20]
	ldrb r4, [sp, #0x21]
	str r1, [sp, #0x1c]
	str r0, [sp, #0x18]
	addle sp, sp, #0x4c
	ldmleia sp!, {r4-r11,pc}
_020B6A90:
	ldr r0, [sp, #0xc]
	ldr r7, [sp, #0x10]
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x8]
	cmp r0, r8
	mov r9, r0
	ble _020B6AEC
_020B6AAC:
	ldr r2, [sp, #0x1c]
	str r11, [sp, #0x0]
	ldr r3, [sp, #0x18]
	mov r0, r7
	mov r1, r10
	str r4, [sp, #0x4]
	bl FUN_020B7068
	mla r1, r0, r5, r6
	add r0, sp, #0x24
	str r9, [sp, #0x2c]
	str r1, [sp, #0x24]
	bl FUN_020B6CAC
	sub r9, r9, #0x8
	add r7, r7, #0x1
	cmp r9, r8
	bgt _020B6AAC
_020B6AEC:
	ldr r0, [sp, #0xc]
	add r10, r10, #0x1
	sub r1, r0, #0x8
	ldr r0, [sp, #0x14]
	str r1, [sp, #0xc]
	cmp r1, r0
	bgt _020B6A90
	add sp, sp, #0x4c
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020B6B10
FUN_020B6B10: ; 0x020B6B10
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x2c
	ldr r4, [sp, #0x54]
	ldrb r5, [r0, #0xc]
	str r4, [sp, #0x54]
	ldr r4, [r4, #0x0]
	ldr r6, [r1, #0x0]
	mov r7, r5, lsl #0x6
	ldrb r4, [r4, #0x1]
	mov r5, r7, asr #0x2
	add r5, r7, r5, lsr #0x1d
	cmp r4, #0x0
	ldr r6, [r6, #0x8]
	mov r9, r3
	ldr r8, [r0, #0x4]
	ldr r7, [r0, #0x8]
	mov r10, r2
	mov r5, r5, asr #0x3
	addeq sp, sp, #0x2c
	ldr lr, [r0, #0x0]
	ldrb r3, [r6, #0x1]
	ldmeqia sp!, {r4-r11,pc}
_020B6B68: ; 0x020B6B68
	adds r6, r10, r4
	addmi sp, sp, #0x2c
	ldmmiia sp!, {r4-r11,pc}
_020B6B74: ; 0x020B6B74
	adds r2, r9, r3
	addmi sp, sp, #0x2c
	ldmmiia sp!, {r4-r11,pc}
_020B6B80: ; 0x020B6B80
	cmp r10, #0x0
	movle r11, #0x0
	add r6, r6, #0x7
	movgt r11, r10, lsr #0x3
	cmp r9, #0x0
	movle r12, #0x0
	add r2, r2, #0x7
	mov r6, r6, lsr #0x3
	movgt r12, r9, lsr #0x3
	cmp r6, r8
	movcs r6, r8
	mov r2, r2, lsr #0x3
	cmp r2, r7
	movcs r2, r7
	subs r7, r6, r11
	addmi sp, sp, #0x2c
	sub r2, r2, r12
	ldmmiia sp!, {r4-r11,pc}
_020B6BC8: ; 0x020B6BC8
	cmp r2, #0x0
	addlt sp, sp, #0x2c
	ldmltia sp!, {r4-r11,pc}
_020B6BD4: ; 0x020B6BD4
	ldr r6, [r0, #0x10]
	cmp r10, #0x0
	sub r8, r6, r7
	mul r8, r5, r8
	mla r11, r6, r12, r11
	andge r10, r10, #0x7
	str r8, [sp, #0x0]
	ldr r8, [sp, #0x54]
	mla r6, r5, r11, lr
	ldr r12, [r8, #0x4]
	ldr r11, [sp, #0x50]
	cmp r9, #0x0
	sub r8, r11, #0x1
	andge r9, r9, #0x7
	sub r11, r9, r2, lsl #0x3
	str r12, [sp, #0x8]
	str r4, [sp, #0x14]
	str r8, [sp, #0x28]
	str r3, [sp, #0x18]
	ldr r3, [r1, #0x0]
	cmp r9, r11
	ldr r2, [r3, #0x8]
	sub r7, r10, r7, lsl #0x3
	ldrb r2, [r2, #0x6]
	str r2, [sp, #0x20]
	ldrb r0, [r0, #0xc]
	str r0, [sp, #0x24]
	ldr r0, [r1, #0x0]
	ldr r0, [r0, #0x8]
	ldrb r0, [r0, #0x0]
	mul r0, r2, r0
	str r0, [sp, #0x1c]
	addle sp, sp, #0x2c
	ldmleia sp!, {r4-r11,pc}
_020B6C5C: ; 0x020B6C5C
	add r4, sp, #0x4
_020B6C60:
	mov r8, r10
	str r9, [sp, #0x10]
	cmp r10, r7
	ble _020B6C90
_020B6C70:
	mov r0, r4
	str r6, [sp, #0x4]
	str r8, [sp, #0xc]
	bl FUN_020B6CAC
	sub r8, r8, #0x8
	cmp r8, r7
	add r6, r6, r5
	bgt _020B6C70
_020B6C90:
	ldr r0, [sp, #0x0]
	sub r9, r9, #0x8
	cmp r9, r11
	add r6, r6, r0
	bgt _020B6C60
	add sp, sp, #0x2c
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020B6CAC
FUN_020B6CAC: ; 0x020B6CAC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	ldr r5, [r0, #0x8]
	ldr r4, [r0, #0xc]
	cmp r5, #0x0
	strge r5, [sp, #0x0]
	movlt r1, #0x0
	strlt r1, [sp, #0x0]
	ldr r1, [r0, #0x10]
	cmp r4, #0x0
	add r10, r5, r1
	ldr r1, [r0, #0x14]
	movge r2, r4
	movlt r2, #0x0
	cmp r10, #0x8
	add r3, r4, r1
	movge r10, #0x8
	cmp r3, #0x8
	movge r3, #0x8
	cmp r4, #0x0
	movgt r4, #0x0
	cmp r5, #0x0
	ldr r8, [r0, #0x20]
	movgt r5, #0x0
	rsb r1, r4, #0x0
	mul r7, r10, r8
	ldr r6, [r0, #0x1c]
	rsb r4, r5, #0x0
	mul r9, r6, r4
	ldr r4, [r0, #0x18]
	mov r10, r7
	str r4, [sp, #0x8]
	ldr r4, [sp, #0x0]
	cmp r8, #0x4
	mul r5, r4, r8
	ldr r4, [sp, #0x8]
	str r5, [sp, #0x0]
	mla r11, r1, r4, r9
	ldr r1, [r0, #0x4]
	str r1, [sp, #0x4]
	bne _020B6E24
	ldr r1, [r0, #0x0]
	ldr r7, [r0, #0x24]
	add r0, r1, r2, lsl #0x2
	str r0, [sp, #0xc]
	add r0, r1, r3, lsl #0x2
	ldr r1, [sp, #0xc]
	str r0, [sp, #0x10]
	cmp r1, r0
	addcs sp, sp, #0x34
	ldmcsia sp!, {r4-r11,pc}
_020B6D78: ; 0x020B6D78
	mov r0, #0x0
	add r9, sp, #0x24
	mov r4, #0xf
	str r0, [sp, #0x1c]
_020B6D88:
	ldr r0, [sp, #0xc]
	mov r1, r11, lsr #0x1f
	ldr r5, [r0, #0x0]
	ldr r0, [sp, #0x4]
	rsb r2, r1, r11, lsl #0x1d
	add r0, r0, r11, lsr #0x3
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x1c]
	add r1, r1, r2, ror #0x1d
	strb r0, [sp, #0x28]
	strb r0, [sp, #0x29]
	mov r0, r9
	bl FUN_020B76B0
	ldr r8, [sp, #0x0]
	mov r0, r8
	cmp r0, r10
	bhs _020B6DF8
_020B6DCC:
	mov r0, r9
	mov r1, r6
	bl FUN_020B76B0
_020B6DD8: ; 0x020B6DD8
	cmp r0, #0x0
	mvnne r1, r4, lsl r8
	addne r0, r7, r0
	andne r1, r5, r1
	orrne r5, r1, r0, lsl r8
	add r8, r8, #0x4
	cmp r8, r10
	blo _020B6DCC
_020B6DF8:
	ldr r0, [sp, #0xc]
	add r1, r0, #0x4
	str r5, [r0, #0x0]
	ldr r0, [sp, #0x10]
	str r1, [sp, #0xc]
	cmp r1, r0
	ldr r0, [sp, #0x8]
	add r11, r11, r0
	blo _020B6D88
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,pc}
_020B6E24:
	ldr r1, [r0, #0x0]
	ldr r9, [r0, #0x24]
	add r0, r1, r2, lsl #0x3
	str r0, [sp, #0x14]
	add r0, r1, r3, lsl #0x3
	ldr r1, [sp, #0x14]
	str r0, [sp, #0x18]
	cmp r1, r0
	addcs sp, sp, #0x34
	ldmcsia sp!, {r4-r11,pc}
_020B6E4C: ; 0x020B6E4C
	mov r0, #0x0
	mov r4, #0xff
	str r0, [sp, #0x20]
_020B6E58:
	mov r1, r11, lsr #0x1f
	rsb r0, r1, r11, lsl #0x1d
	add r1, r1, r0, ror #0x1d
	ldr r0, [sp, #0x14]
	ldr r8, [r0, #0x0]
	ldr r7, [r0, #0x4]
	ldr r0, [sp, #0x4]
	add r0, r0, r11, lsr #0x3
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x20]
	strb r0, [sp, #0x30]
	strb r0, [sp, #0x31]
	add r0, sp, #0x2c
	bl FUN_020B76B0
_020B6E90: ; 0x020B6E90
	ldr r0, [sp, #0x0]
	cmp r0, r10
	mov r5, r0
	bhs _020B6EE8
_020B6EA0:
	add r0, sp, #0x2c
	mov r1, r6
	bl FUN_020B76B0
_020B6EAC: ; 0x020B6EAC
	cmp r0, #0x0
	beq _020B6EDC
	cmp r5, #0x20
	mvncc r1, r4, lsl r5
	addcc r0, r9, r0
	andcc r1, r8, r1
	orrcc r8, r1, r0, lsl r5
	subcs r2, r5, #0x20
	mvncs r1, r4, lsl r2
	addcs r0, r9, r0
	andcs r1, r7, r1
	orrcs r7, r1, r0, lsl r2
_020B6EDC:
	add r5, r5, #0x8
	cmp r5, r10
	blo _020B6EA0
_020B6EE8:
	ldr r0, [sp, #0x14]
	str r8, [r0, #0x0]
	add r1, r0, #0x8
	str r7, [r0, #0x4]
	ldr r0, [sp, #0x18]
	str r1, [sp, #0x14]
	cmp r1, r0
	ldr r0, [sp, #0x8]
	add r11, r11, r0
	blo _020B6E58
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020B6F18
FUN_020B6F18: ; 0x020B6F18
	stmdb sp!, {r4-r6,lr}
	mov lr, r0
	cmp r3, #0x8
	ldr r0, [sp, #0x14]
	bne _020B6F4C
	ldr r4, [sp, #0x10]
	cmp r4, #0x8
	bne _020B6F4C
	ldr r2, [sp, #0x18]
	mov r1, lr
	mov r2, r2, lsl #0x3
	bl MIi_CpuClearFast
	ldmia sp!, {r4-r6,pc}
_020B6F4C:
	ldr r4, [sp, #0x18]
	cmp r4, #0x4
	bne _020B6FAC
	mov r5, r1, lsl #0x2
	add r4, r5, r3, lsl #0x2
	mvn r3, #0x0
	rsb r4, r4, #0x20
	mov r3, r3, lsr r5
	add r1, r4, r1, lsl #0x2
	mov r3, r3, lsl r1
	ldr r1, [sp, #0x10]
	add r5, lr, r2, lsl #0x2
	add r2, r5, r1, lsl #0x2
	and r6, r0, r3, lsr r4
	cmp r5, r2
	mvn r1, r3, lsr r4
	ldmcsia sp!, {r4-r6,pc}
_020B6F90:
	ldr r0, [r5, #0x0]
	and r0, r0, r1
	orr r0, r6, r0
	str r0, [r5], #0x4
	cmp r5, r2
	blo _020B6F90
	ldmia sp!, {r4-r6,pc}
_020B6FAC:
	mov r12, r1, lsl #0x3
	add r1, r12, r3, lsl #0x3
	rsb r1, r1, #0x40
	mvn r3, #0x0
	cmp r1, #0x20
	mov r5, r3, lsr r12
	subcs r4, r1, #0x20
	addcs r3, r12, r4
	movcs r3, r5, lsl r3
	movcs r3, r3, lsr r4
	movcc r3, r5, lsl r12
	mvn r4, #0x0
	add r5, lr, r2, lsl #0x3
	cmp r12, #0x20
	mov r4, r4, lsl r1
	subcs r12, r12, #0x20
	addcs r1, r12, r1
	movcs r1, r4, lsr r1
	movcs r6, r1, lsl r12
	movcc r6, r4, lsr r1
	ldr r1, [sp, #0x10]
	and lr, r0, r3
	add r4, r5, r1, lsl #0x3
	cmp r5, r4
	and r12, r0, r6
	mvn r2, r3
	mvn r1, r6
	ldmcsia sp!, {r4-r6,pc}
_020B701C:
	ldr r0, [r5, #0x0]
	and r0, r0, r2
	orr r0, lr, r0
	str r0, [r5, #0x0]
	ldr r0, [r5, #0x4]
	and r0, r0, r1
	orr r0, r12, r0
	str r0, [r5, #0x4]
	add r5, r5, #0x8
	cmp r5, r4
	blo _020B701C
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020B704C
FUN_020B704C: ; 0x020B704C
	ldrb r3, [r0, #0x1]
	ldr r2, _020B7064 ; =0x020FF990
	ldrb r1, [r0, #0x0]
	add r0, r2, r3, lsl #0x4
	ldr r0, [r0, r1, lsl #0x2]
	bx lr
	.balign 4
_020B7064: .word 0x020FF990

	arm_func_start FUN_020B7068
FUN_020B7068: ; 0x020B7068
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr fp, _020B7164 ; =0x020FF970
	mov r9, #0x0
	mov r10, #0x3
	mvn r7, #0x0
_020B7080:
	ldr r4, [sp, #0x2c]
	ldr r6, [sp, #0x28]
	and r12, r3, r7, lsl r4
	cmp r12, r1
	mov r8, r7, lsl r6
	mov r5, r7, lsl r4
	and lr, r2, r7, lsl r6
	bhi _020B70D0
	mla r9, r2, r12, r9
	cmp lr, r0
	movhi r2, lr
	subhi r1, r1, r12
	subhi r3, r3, r12
	bhi _020B7118
	sub r3, r3, r12
	mla r9, lr, r3, r9
	sub r0, r0, lr
	sub r1, r1, r12
	sub r2, r2, lr
	b _020B7118
_020B70D0:
	cmp lr, r0
	mlals r9, lr, r12, r9
	mvn r3, r5
	movls r3, r12
	subls r0, r0, lr
	subls r2, r2, lr
	bls _020B7118
	and r2, r1, r5
	mla r5, lr, r2, r9
	and r2, r0, r8
	and r1, r1, r3
	add r2, r5, r2, lsl r4
	mvn r3, r8
	add r1, r2, r1, lsl r6
	and r0, r0, r3
	add sp, sp, #0x4
	add r0, r1, r0
	ldmia sp!, {r4-r11,pc}
_020B7118:
	cmp r2, #0x8
	movlt r4, r2
	movge r5, r10
	clzlt r4, r4
	rsblt r5, r4, #0x1f
	cmp r3, #0x8
	movge r4, r10
	movlt r4, r3
	clzlt r4, r4
	rsblt r4, r4, #0x1f
	add r4, r11, r4, lsl #0x3
	add r6, r4, r5, lsl #0x1
	ldrb r5, [r4, r5, lsl #0x1]
	ldrb r4, [r6, #0x1]
	str r5, [sp, #0x28]
	str r4, [sp, #0x2c]
	b _020B7080
_020B715C: ; 0x020B715C
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B7164: .word 0x020FF970

	arm_func_start FUN_020B7168
FUN_020B7168: ; 0x020B7168
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	ldr r12, [sp, #0x28]
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	ands r0, r12, #0x100
	beq _020B71AC
	ldr r0, [r7, #0x4]
	ldr r1, [r7, #0xc]
	ldr r2, [sp, #0x2c]
	bl FUN_020B5B54
	ldr r1, [sp, #0x20]
	sub r0, r1, r0
	add r5, r5, r0
	b _020B71E4
_020B71AC:
	ands r0, r12, #0x80
	beq _020B71E4
	ldr r0, [r7, #0x4]
	ldr r1, [r7, #0xc]
	ldr r2, [sp, #0x2c]
	bl FUN_020B5B54
	ldr r2, [sp, #0x20]
	add r1, r0, #0x1
	add r0, r2, #0x1
	add r0, r0, r0, lsr #0x1f
	mov r2, r0, asr #0x1
	add r0, r1, r1, lsr #0x1f
	sub r0, r2, r0, asr #0x1
	add r5, r5, r0
_020B71E4:
	ldr r1, [sp, #0x24]
	ldr r0, [sp, #0x28]
	str r1, [sp, #0x0]
	ldr r12, [sp, #0x2c]
	str r0, [sp, #0x4]
	mov r0, r7
	mov r1, r6
	mov r2, r5
	mov r3, r4
	str r12, [sp, #0x8]
	bl FUN_020B72C4
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020B7218
FUN_020B7218: ; 0x020B7218
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x18
	ldr r4, [sp, #0x34]
	mov r8, r0
	str r4, [sp, #0x0]
	mov r7, r1
	mov r6, r2
	mov r5, r3
	ldr r4, [sp, #0x30]
	ldr r1, [r8, #0x4]
	ldr r2, [r8, #0x8]
	ldr r3, [r8, #0xc]
	add r0, sp, #0xc
	bl FUN_020B5ABC
	ands r0, r4, #0x10
	ldrne r0, [sp, #0xc]
	addne r0, r0, #0x1
	addne r0, r0, r0, lsr #0x1f
	subne r7, r7, r0, asr #0x1
	bne _020B7274
	ands r0, r4, #0x20
	ldrne r0, [sp, #0xc]
	subne r7, r7, r0
_020B7274:
	ands r0, r4, #0x2
	ldrne r0, [sp, #0x10]
	addne r0, r0, #0x1
	addne r0, r0, r0, lsr #0x1f
	subne r6, r6, r0, asr #0x1
	bne _020B7298
	ands r0, r4, #0x4
	ldrne r0, [sp, #0x10]
	subne r6, r6, r0
_020B7298:
	str r5, [sp, #0x0]
	ldr r0, [sp, #0x34]
	str r4, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r3, [sp, #0xc]
	mov r0, r8
	mov r1, r7
	mov r2, r6
	bl FUN_020B72C4
	add sp, sp, #0x18
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020B72C4
FUN_020B72C4: ; 0x020B72C4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r10, r0
	ldr r4, [r10, #0x4]
	ldr r0, [sp, #0x40]
	ldr r4, [r4, #0x0]
	ldr r5, [r10, #0xc]
	ldrsb r4, [r4, #0x1]
	cmp r0, #0x0
	mov r9, r1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x38]
	mov r8, r2
	str r0, [sp, #0x38]
	mov r7, r3
	add r6, r5, r4
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4-r11,pc}
_020B730C: ; 0x020B730C
	add r0, r7, #0x1
	ldr r1, [sp, #0x3c]
	add r0, r0, r0, lsr #0x1f
	mov r0, r0, asr #0x1
	and r5, r1, #0x800
	and r11, r1, #0x400
	str r0, [sp, #0x8]
	mov r4, #0x0
_020B732C:
	mov r1, r9
	cmp r5, #0x0
	beq _020B7358
	ldr r0, [r10, #0x4]
	ldr r1, [r10, #0x8]
	ldr r2, [sp, #0xc]
	mov r3, r4
	bl FUN_020B5BC8
_020B734C: ; 0x020B734C
	sub r0, r7, r0
	add r1, r9, r0
	b _020B7388
_020B7358:
	cmp r11, #0x0
	beq _020B7388
	ldr r0, [r10, #0x4]
	ldr r1, [r10, #0x8]
	ldr r2, [sp, #0xc]
	mov r3, r4
	bl FUN_020B5BC8
	add r0, r0, #0x1
	add r1, r0, r0, lsr #0x1f
	ldr r0, [sp, #0x8]
	sub r0, r0, r1, asr #0x1
	add r1, r9, r0
_020B7388:
	ldr r2, [sp, #0xc]
	add r3, sp, #0xc
	str r2, [sp, #0x0]
	str r3, [sp, #0x4]
	ldr r3, [sp, #0x38]
	mov r0, r10
	mov r2, r8
	bl FUN_020B73C0
	ldr r0, [sp, #0xc]
	add r8, r8, r6
	cmp r0, #0x0
	bne _020B732C
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020B73C0
FUN_020B73C0: ; 0x020B73C0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r10, r0
	ldr r6, [r10, #0x8]
	ldr r5, [r10, #0x4]
	ldr r4, [sp, #0x30]
	add r0, sp, #0x8
	str r4, [sp, #0x8]
	ldr r4, [r5, #0x4]
	mov r9, r1
	mov r8, r2
	mov r7, r3
	blx r4
	cmp r0, #0x0
	beq _020B743C
	add r11, sp, #0x8
_020B7400:
	cmp r0, #0xa
	beq _020B743C
	str r7, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [r10, #0x0]
	mov r1, r5
	mov r2, r9
	mov r3, r8
	bl FUN_020B63CC
	add r1, r9, r0
	mov r0, r11
	add r9, r1, r6
	blx r4
	cmp r0, #0x0
	bne _020B7400
_020B743C:
	ldr r1, [sp, #0x34]
	cmp r1, #0x0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r11,pc}
_020B744C: ; 0x020B744C
	cmp r0, #0xa
	ldreq r1, [sp, #0x8]
	ldr r0, [sp, #0x34]
	movne r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020B7468
FUN_020B7468: ; 0x020B7468
	stmdb sp!, {r4-r6,lr}
	ldrh r2, [r0, #0xc]
	ldrh r3, [r0, #0xe]
	mov r1, #0x0
	add r2, r0, r2
	cmp r3, #0x0
	ldmleia sp!, {r4-r6,pc}
_020B7484: ; 0x020B7484
	ldr r3, _020B7548 ; =0x46494E46
	ldr ip, _020B754C ; =0x43574448
	ldr r4, _020B7550 ; =0x434D4150
	ldr lr, _020B7554 ; =0x43474C50
_020B7494:
	ldr r5, [r2, #0x0]
	cmp r5, r4
	bhi _020B74B0
	cmp r5, r4
	bhs _020B7518
	cmp r5, lr
	b _020B752C
_020B74B0:
	cmp r5, r12
	bhi _020B74C4
	cmp r5, r12
	beq _020B7500
	b _020B752C
_020B74C4:
	cmp r5, r3
	bne _020B752C
	add r6, r2, #0x8
	ldr r5, [r6, #0x8]
	add r5, r5, r0
	str r5, [r6, #0x8]
	ldr r5, [r6, #0xc]
	cmp r5, #0x0
	addne r5, r5, r0
	strne r5, [r6, #0xc]
	ldr r5, [r6, #0x10]
	cmp r5, #0x0
	addne r5, r5, r0
	strne r5, [r6, #0x10]
	b _020B752C
_020B7500:
	add r6, r2, #0x8
	ldr r5, [r6, #0x4]
	cmp r5, #0x0
	addne r5, r5, r0
	strne r5, [r6, #0x4]
	b _020B752C
_020B7518:
	add r6, r2, #0x8
	ldr r5, [r6, #0x8]
	cmp r5, #0x0
	addne r5, r5, r0
	strne r5, [r6, #0x8]
_020B752C:
	ldrh r5, [r0, #0xe]
	ldr r6, [r2, #0x4]
	add r1, r1, #0x1
	cmp r1, r5
	add r2, r2, r6
	blt _020B7494
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B7548: .word 0x46494E46
_020B754C: .word 0x43574448
_020B7550: .word 0x434D4150
_020B7554: .word 0x43474C50

	arm_func_start FUN_020B7558
FUN_020B7558: ; 0x020B7558
	stmdb sp!, {r4-r6,lr}
	movs r6, r0
	mov r5, r1
	beq _020B75C8
	cmp r6, #0x0
	beq _020B7584
	ldr r1, [r6, #0x0]
	ldr r0, _020B76A8 ; =0x4E465452
	cmp r1, r0
	moveq r0, #0x1
	beq _020B7588
_020B7584:
	mov r0, #0x0
_020B7588:
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020B75CC
	cmp r6, #0x0
	beq _020B75B4
	ldrh r0, [r6, #0x6]
	cmp r0, #0x100
	movcs r0, #0x1
	bhs _020B75B8
_020B75B4:
	mov r0, #0x0
_020B75B8:
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	b _020B75CC
_020B75C8:
	mov r0, #0x0
_020B75CC:
	cmp r0, #0x0
	movne r4, #0x0
	bne _020B7654
	cmp r6, #0x0
	beq _020B7640
	cmp r6, #0x0
	beq _020B75FC
	ldr r1, [r6, #0x0]
	ldr r0, _020B76A8 ; =0x4E465452
	cmp r1, r0
	moveq r0, #0x1
	beq _020B7600
_020B75FC:
	mov r0, #0x0
_020B7600:
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020B7644
	cmp r6, #0x0
	beq _020B762C
	ldrh r0, [r6, #0x6]
	cmp r0, #0x1
	movcs r0, #0x1
	bhs _020B7630
_020B762C:
	mov r0, #0x0
_020B7630:
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	b _020B7644
_020B7640:
	mov r0, #0x0
_020B7644:
	cmp r0, #0x0
	movne r4, #0x1
	bne _020B7654
	bl OS_Terminate
_020B7654:
	mov r0, r6
	bl FUN_020B7468
	ldr r1, _020B76AC ; =0x46494E46
	mov r0, r6
	bl FUN_020B01F8
_020B7668: ; 0x020B7668
	cmp r0, #0x0
	moveq r0, #0x0
	streq r0, [r5, #0x0]
	ldmeqia sp!, {r4-r6,pc}
_020B7678: ; 0x020B7678
	add r0, r0, #0x8
	str r0, [r5, #0x0]
	cmp r4, #0x0
	beq _020B76A0
	ldr r2, [r5, #0x0]
	mov r1, #0x0
	ldrsb r0, [r2, #0x6]
	strb r0, [r2, #0x7]
	ldr r0, [r5, #0x0]
	strb r1, [r0, #0x6]
_020B76A0:
	add r0, r4, #0x1
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B76A8: .word 0x4E465452
_020B76AC: .word 0x46494E46

	arm_func_start FUN_020B76B0
FUN_020B76B0:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldrsb r2, [r0, #0x4]
	ldrb r12, [r0, #0x5]
	mov r4, r1
	cmp r2, r4
	subge r1, r2, r4
	movge r5, r12, lsr r1
	strgeb r1, [r0, #0x4]
	bge _020B7704
	ldr r3, [r0, #0x0]
	sub r1, r4, r2
	add r2, r3, #0x1
	str r2, [r0, #0x0]
	ldrb r2, [r3, #0x0]
	mov r5, r12, lsl r1
	strb r2, [r0, #0x5]
	mov r2, #0x8
	strb r2, [r0, #0x4]
	bl FUN_020B76B0
	orr r5, r0, r5
_020B7704:
	rsb r0, r4, #0x8
	mov r1, #0xff
	and r0, r5, r1, asr r0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020B7718
FUN_020B7718: ; 0x020B7718
	ldr r1, [r0, #0x0]
	ldrh r2, [r1], #0x2
	str r1, [r0, #0x0]
	mov r0, r2
	bx lr

	arm_func_start FUN_020B772C
FUN_020B772C: ; 0x020B772C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	ldrb r0, [r6, #0x9]
	mov r5, #0x0
	cmp r0, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r7,pc}
_020B774C: ; 0x020B774C
	add r4, r6, #0x8
_020B7750:
	ldrh r0, [r6, #0xe]
	ldrh r1, [r4, r0]
	add r0, r4, r0
	mla r0, r1, r5, r0
	ldr r0, [r0, #0x4]
	add r7, r6, r0
	mov r0, r7
	bl FUN_020B79A4
	mov r0, r7
	bl FUN_020B780C
	ldrb r0, [r6, #0x9]
	add r5, r5, #0x1
	cmp r5, r0
	blo _020B7750
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020B7790
FUN_020B7790: ; 0x020B7790
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r8, r0
	ldrb r0, [r8, #0x9]
	mov r7, r1
	mov r5, #0x1
	cmp r0, #0x0
	mov r6, #0x0
	bls _020B7800
	add r4, r8, #0x8
_020B77B8:
	ldrh r0, [r8, #0xe]
	mov r1, r7
	ldrh r2, [r4, r0]
	add r0, r4, r0
	mla r0, r2, r6, r0
	ldr r0, [r0, #0x4]
	add r9, r8, r0
	mov r0, r9
	bl FUN_020B7A04
	and r5, r5, r0
	mov r0, r9
	mov r1, r7
	bl FUN_020B7864
	ldrb r1, [r8, #0x9]
	add r6, r6, #0x1
	and r5, r5, r0
	cmp r6, r1
	blo _020B77B8
_020B7800:
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}

	arm_func_start FUN_020B780C
FUN_020B780C: ; 0x020B780C
	ldr r2, [r0, #0x8]
	mov r1, #0x0
	add r2, r0, r2
	ldrh r0, [r2, #0x2]
	add r12, r2, r0
	ldrb r0, [r12, #0x1]
	cmp r0, #0x0
	bxls lr
_020B782C:
	ldrh r2, [r12, #0x6]
	ldrh r0, [r12, r2]
	add r2, r12, r2
	add r2, r2, #0x4
	mla r3, r0, r1, r2
	ldrb r0, [r3, #0x3]
	add r1, r1, #0x1
	ands r2, r0, #0x1
	bicne r0, r0, #0x1
	strneb r0, [r3, #0x3]
	ldrb r0, [r12, #0x1]
	cmp r1, r0
	blo _020B782C
	bx lr

	arm_func_start FUN_020B7864
FUN_020B7864: ; 0x020B7864
	stmdb sp!, {r4-r10,lr}
	ldr r2, [r0, #0x8]
	mov r10, r1
	add r9, r0, r2
	ldrh r0, [r9, #0x2]
	mov r6, #0x1
	mov r7, #0x0
	add r8, r9, r0
	ldrb r0, [r8, #0x1]
	cmp r0, #0x0
	bls _020B7908
	mov r5, r7
	mov r4, r7
_020B7898:
	ldrh r1, [r8, #0x6]
	ldrh r0, [r10, #0x34]
	add r2, r8, r1
	ldrh r1, [r2, #0x2]
	add r0, r10, r0
	add r1, r2, r1
	add r1, r1, r5
	bl FUN_020BC2A0
	movs r3, r0
	beq _020B78F0
	ldrh r1, [r8, #0x6]
	ldrh r0, [r8, r1]
	add r1, r8, r1
	add r1, r1, #0x4
	mla r1, r0, r7, r1
	ldrb r0, [r1, #0x3]
	ands r0, r0, #0x1
	bne _020B78F4
	mov r0, r9
	mov r2, r10
	bl FUN_020B7910
_020B78EC: ; 0x020B78EC
	b _020B78F4
_020B78F0:
	mov r6, r4
_020B78F4:
	ldrb r0, [r8, #0x1]
	add r7, r7, #0x1
	add r5, r5, #0x10
	cmp r7, r0
	blo _020B7898
_020B7908:
	mov r0, r6
	ldmia sp!, {r4-r10,pc}

	arm_func_start FUN_020B7910
FUN_020B7910:
	stmdb sp!, {r4-r6,lr}
	ldrh r5, [r1, #0x0]
	ldr r2, [r2, #0x2c]
	ldrh r4, [r3, #0x2]
	mov r2, r2, lsl #0x10
	add r12, r0, r5
	mov r5, r2, lsr #0x10
	ands r2, r4, #0x1
	ldrh r4, [r3, #0x0]
	moveq r3, r5, lsl #0xf
	moveq r5, r3, lsr #0x10
	moveq r2, r4, lsl #0xf
	moveq r4, r2, lsr #0x10
	ldrb r3, [r1, #0x2]
	mov r2, #0x0
	cmp r3, #0x0
	bls _020B7994
	add r3, r4, r5
	mov r3, r3, lsl #0x10
	add r6, r0, #0x4
	mov r4, r3, lsr #0x10
_020B7964:
	ldrh r5, [r0, #0xa]
	ldrb r3, [r12, r2]
	add r2, r2, #0x1
	ldrh lr, [r6, r5]
	add r5, r6, r5
	mla r3, lr, r3, r5
	ldr r3, [r3, #0x4]
	add r3, r0, r3
	strh r4, [r3, #0x1c]
	ldrb r3, [r1, #0x2]
	cmp r2, r3
	blo _020B7964
_020B7994:
	ldrb r0, [r1, #0x3]
	orr r0, r0, #0x1
	strb r0, [r1, #0x3]
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020B79A4
FUN_020B79A4: ; 0x020B79A4
	stmdb sp!, {r4-r6,lr}
	ldr r2, [r0, #0x8]
	mov r4, #0x0
	ldrh r1, [r0, r2]
	add r6, r0, r2
	add r5, r6, r1
	ldrb r0, [r5, #0x1]
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020B79C8:
	ldrh r1, [r5, #0x6]
	ldrh r0, [r5, r1]
	add r1, r5, r1
	add r1, r1, #0x4
	mla r1, r0, r4, r1
	ldrb r0, [r1, #0x3]
	ands r0, r0, #0x1
	beq _020B79F0
	mov r0, r6
	bl FUN_020B7AB8
_020B79F0:
	ldrb r0, [r5, #0x1]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020B79C8
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020B7A04
FUN_020B7A04: ; 0x020B7A04
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x8]
	mov r10, r1
	ldrh r1, [r0, r2]
	add r9, r0, r2
	mov r11, #0x1
	add r8, r9, r1
	ldrb r0, [r8, #0x1]
	mov r7, #0x0
	cmp r0, #0x0
	bls _020B7AAC
	mov r6, r7
	mov r4, r7
	add r5, r10, #0x3c
_020B7A40:
	ldrh r1, [r8, #0x6]
	mov r0, r5
	add r2, r8, r1
	ldrh r1, [r2, #0x2]
	add r1, r2, r1
	add r1, r1, r6
	bl FUN_020BC2A0
	movs r3, r0
	beq _020B7A94
	ldrh r1, [r8, #0x6]
	ldrh r0, [r8, r1]
	add r1, r8, r1
	add r1, r1, #0x4
	mla r1, r0, r7, r1
	ldrb r0, [r1, #0x3]
	ands r0, r0, #0x1
	bne _020B7A98
	mov r0, r9
	mov r2, r10
	bl FUN_020B7B40
_020B7A90: ; 0x020B7A90
	b _020B7A98
_020B7A94:
	mov r11, r4
_020B7A98:
	ldrb r0, [r8, #0x1]
	add r7, r7, #0x1
	add r6, r6, #0x10
	cmp r7, r0
	blo _020B7A40
_020B7AAC:
	mov r0, r11
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020B7AB8
FUN_020B7AB8: ; 0x020B7AB8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldrh r4, [r1, #0x0]
	ldrb r2, [r1, #0x2]
	mov r3, #0x0
	add r12, r0, r4
	cmp r2, #0x0
	bls _020B7B28
	add r2, r0, #0x4
	mov r5, #0x1000
	ldr lr, _020B7B3C ; =0xC00F0000
_020B7AE4:
	ldrh r7, [r0, #0xa]
	ldrb r4, [r12, r3]
	add r3, r3, #0x1
	ldrh r6, [r2, r7]
	add r7, r2, r7
	mla r4, r6, r4, r7
	ldr r4, [r4, #0x4]
	add r6, r0, r4
	ldr r4, [r6, #0x14]
	and r4, r4, lr
	str r4, [r6, #0x14]
	str r5, [r6, #0x24]
	ldr r4, [r6, #0x24]
	str r4, [r6, #0x28]
	ldrb r4, [r1, #0x2]
	cmp r3, r4
	blo _020B7AE4
_020B7B28:
	ldrb r0, [r1, #0x3]
	bic r0, r0, #0x1
	strb r0, [r1, #0x3]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B7B3C: .word 0xC00F0000

	arm_func_start FUN_020B7B40
FUN_020B7B40:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r11, r1
	mov r9, r3
	ldr r1, [r9, #0x0]
	mov r10, r0
	and r0, r1, #0x1c000000
	cmp r0, #0x14000000
	ldrh r3, [r11, #0x0]
	ldrne r1, [r2, #0x8]
	mov r8, #0x0
	add r0, r10, r3
	str r0, [sp, #0x4]
	ldrne r0, _020B7C50 ; =0x0000FFFF
	andne r0, r1, r0
	strne r0, [sp, #0x0]
	ldreq r1, [r2, #0x18]
	ldreq r0, _020B7C50 ; =0x0000FFFF
	andeq r0, r1, r0
	streq r0, [sp, #0x0]
	ldrb r0, [r11, #0x2]
	cmp r0, #0x0
	bls _020B7C3C
	mov r4, #0x1000
	add r5, r10, #0x4
_020B7BA4:
	ldrh r6, [r10, #0xa]
	ldr r0, [sp, #0x4]
	ldr r1, [r9, #0x0]
	ldrb r2, [r0, r8]
	ldrh r3, [r5, r6]
	ldr r0, [sp, #0x0]
	add r6, r5, r6
	add r0, r1, r0
	mla r1, r3, r2, r6
	ldr r1, [r1, #0x4]
	add r6, r10, r1
	ldr r1, [r6, #0x14]
	orr r0, r1, r0
	str r0, [r6, #0x14]
	ldr r3, [r9, #0x4]
	ldr r0, _020B7C54 ; =0x000007FF
	ldrh r1, [r6, #0x20]
	and r2, r3, r0
	and r7, r0, r3, lsr #0xb
	cmp r2, r1
	moveq r0, r4
	beq _020B7C08
	mov r0, r2, lsl #0xc
	mov r1, r1, lsl #0xc
	bl FX_Div
_020B7C08:
	str r0, [r6, #0x24]
	ldrh r1, [r6, #0x22]
	cmp r7, r1
	moveq r0, r4
	beq _020B7C28
	mov r0, r7, lsl #0xc
	mov r1, r1, lsl #0xc
	bl FX_Div
_020B7C28:
	str r0, [r6, #0x28]
	ldrb r0, [r11, #0x2]
	add r8, r8, #0x1
	cmp r8, r0
	blo _020B7BA4
_020B7C3C:
	ldrb r0, [r11, #0x3]
	orr r0, r0, #0x1
	strb r0, [r11, #0x3]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B7C50: .word 0x0000FFFF
_020B7C54: .word 0x000007FF

	arm_func_start FUN_020B7C58
FUN_020B7C58: ; 0x020B7C58
	ldrh r2, [r0, #0x32]
	mov r1, #0x0
	bic r2, r2, #0x1
	strh r2, [r0, #0x32]
	ldr r2, [r0, #0x2c]
	str r1, [r0, #0x2c]
	mov r0, r2
	bx lr

	arm_func_start FUN_020B7C78
FUN_020B7C78: ; 0x020B7C78
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r4, r1
	mov r5, r0
	beq _020B7C90
	bl GX_BeginLoadTexPltt
_020B7C90:
	ldrh r2, [r5, #0x30]
	ldr r0, [r5, #0x38]
	ldr r3, [r5, #0x2c]
	ldr r1, _020B7CD8 ; =0x0000FFFF
	add r0, r5, r0
	and r1, r3, r1
	mov r1, r1, lsl #0x3
	mov r2, r2, lsl #0x3
	bl GX_LoadTexPltt
	ldrh r0, [r5, #0x32]
	cmp r4, #0x0
	addeq sp, sp, #0x4
	orr r0, r0, #0x1
	strh r0, [r5, #0x32]
	ldmeqia sp!, {r4-r5,pc}
_020B7CCC: ; 0x020B7CCC
	bl GX_EndLoadTexPltt
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B7CD8: .word 0x0000FFFF

	arm_func_start FUN_020B7CDC
FUN_020B7CDC: ; 0x020B7CDC
	str r1, [r0, #0x2c]
	bx lr

	arm_func_start FUN_020B7CE4
FUN_020B7CE4: ; 0x020B7CE4
	ldrh r0, [r0, #0x30]
	mov r0, r0, lsl #0x3
	bx lr

	arm_func_start FUN_020B7CF0
FUN_020B7CF0: ; 0x020B7CF0
	ldrh r12, [r0, #0x10]
	mov r3, #0x0
	bic r12, r12, #0x1
	strh r12, [r0, #0x10]
	ldrh r12, [r0, #0x20]
	bic r12, r12, #0x1
	strh r12, [r0, #0x20]
	ldr r12, [r0, #0x8]
	str r12, [r1, #0x0]
	str r3, [r0, #0x8]
	ldr r1, [r0, #0x18]
	str r1, [r2, #0x0]
	str r3, [r0, #0x18]
	bx lr

	arm_func_start FUN_020B7D28
FUN_020B7D28: ; 0x020B7D28
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	movs r8, r1
	mov r9, r0
	beq _020B7D40
	bl GX_BeginLoadTex
_020B7D40:
	ldrh r0, [r9, #0xc]
	movs r2, r0, lsl #0x3
	beq _020B7D74
	ldr r1, [r9, #0x8]
	ldr r0, _020B7DF4 ; =0x0000FFFF
	ldr r3, [r9, #0x14]
	and r1, r1, r0
	add r0, r9, r3
	mov r1, r1, lsl #0x3
	bl GX_LoadTex
	ldrh r0, [r9, #0x10]
	orr r0, r0, #0x1
	strh r0, [r9, #0x10]
_020B7D74:
	ldrh r0, [r9, #0x1c]
	movs r7, r0, lsl #0x3
	beq _020B7DDC
	ldr r1, [r9, #0x18]
	ldr r0, _020B7DF4 ; =0x0000FFFF
	ldr r3, [r9, #0x24]
	and r4, r1, r0
	mov r5, r4, lsl #0x3
	ldr r6, [r9, #0x28]
	mov r1, r5
	mov r2, r7
	add r0, r9, r3
	add r6, r9, r6
	bl GX_LoadTex
	ldr r0, _020B7DF8 ; =0x0001FFFF
	and r1, r5, #0x40000
	and r0, r0, r4, lsl #0x3
	mov r0, r0, lsr #0x1
	add r2, r0, #0x20000
	mov r0, r6
	add r1, r2, r1, lsr #0x2
	mov r2, r7, lsr #0x1
	bl GX_LoadTex
	ldrh r0, [r9, #0x20]
	orr r0, r0, #0x1
	strh r0, [r9, #0x20]
_020B7DDC:
	cmp r8, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r9,pc}
_020B7DE8: ; 0x020B7DE8
	bl GX_EndLoadTex
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020B7DF4: .word 0x0000FFFF
_020B7DF8: .word 0x0001FFFF

	arm_func_start FUN_020B7DFC
FUN_020B7DFC: ; 0x020B7DFC
	cmp r1, #0x0
	strne r1, [r0, #0x8]
	cmp r2, #0x0
	strne r2, [r0, #0x18]
	bx lr

	arm_func_start FUN_020B7E10
FUN_020B7E10: ; 0x020B7E10
	ldrh r0, [r0, #0x1c]
	mov r0, r0, lsl #0x3
	bx lr

	arm_func_start FUN_020B7E1C
FUN_020B7E1C: ; 0x020B7E1C
	ldrh r0, [r0, #0xc]
	mov r0, r0, lsl #0x3
	bx lr

	arm_func_start FUN_020B7E28
FUN_020B7E28: ; 0x020B7E28
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	add r0, r5, #0x8
	mov r4, r1
	bl FUN_020B7E88
_020B7E40: ; 0x020B7E40
	cmp r0, #0x0
	bne _020B7E74
	mov r1, r4
	add r0, r5, #0x10
	bl FUN_020B7E88
_020B7E54: ; 0x020B7E54
	cmp r0, #0x0
	bne _020B7E74
	mov r1, r4
	add r0, r5, #0x18
	bl FUN_020B7E88
_020B7E68: ; 0x020B7E68
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
_020B7E74:
	ldr r0, [r5, #0x0]
	orr r0, r0, #0x10
	str r0, [r5, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020B7E88
FUN_020B7E88:
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r2, r1
	bne _020B7EB8
	ldr r3, [r2, #0x10]
	mov r2, #0x0
	str r3, [r0, #0x0]
	str r2, [r1, #0x10]
	mov r0, #0x1
	bx lr
_020B7EB8:
	ldr r3, [r2, #0x10]
	cmp r3, #0x0
	beq _020B7EF4
_020B7EC4:
	cmp r3, r1
	bne _020B7EE4
	ldr r1, [r3, #0x10]
	mov r0, #0x0
	str r1, [r2, #0x10]
	str r0, [r3, #0x10]
	mov r0, #0x1
	bx lr
_020B7EE4:
	mov r2, r3
	ldr r3, [r3, #0x10]
	cmp r3, #0x0
	bne _020B7EC4
_020B7EF4:
	mov r0, #0x0
	bx lr

	arm_func_start FUN_020B7EFC
FUN_020B7EFC: ; 0x020B7EFC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	ldr r2, [r4, #0x8]
	mov r5, r0
	ldrb r0, [r2, #0x0]
	cmp r0, #0x4a
	beq _020B7F50
	cmp r0, #0x4d
	beq _020B7F34
	cmp r0, #0x56
	beq _020B7F6C
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020B7F34:
	add r0, r5, #0x3c
	bl FUN_020B7F88
	mov r1, r4
	add r0, r5, #0x8
	bl FUN_020B7FF8
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020B7F50:
	add r0, r5, #0x44
	bl FUN_020B7F88
	mov r1, r4
	add r0, r5, #0x10
	bl FUN_020B7FF8
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020B7F6C:
	add r0, r5, #0x4c
	bl FUN_020B7F88
	mov r1, r4
	add r0, r5, #0x18
	bl FUN_020B7FF8
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020B7F88
FUN_020B7F88: ; 0x020B7F88
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
_020B7F9C: ; 0x020B7F9C
	mov r3, #0x1
	mov r4, #0x0
_020B7FA4:
	ldrb r2, [r1, #0x19]
	mov r5, r4
	cmp r2, #0x0
	ble _020B7FE4
_020B7FB4:
	add r2, r1, r5, lsl #0x1
	ldrh r2, [r2, #0x1a]
	ands r2, r2, #0x100
	movne lr, r5, asr #0x5
	andne r2, r5, #0x1f
	ldrne r12, [r0, lr, lsl #0x2]
	add r5, r5, #0x1
	orrne r2, r12, r3, lsl r2
	strne r2, [r0, lr, lsl #0x2]
	ldrb r2, [r1, #0x19]
	cmp r5, r2
	blt _020B7FB4
_020B7FE4:
	ldr r1, [r1, #0x10]
	cmp r1, #0x0
	bne _020B7FA4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020B7FF8
FUN_020B7FF8: ; 0x020B7FF8
	ldr r12, [r0, #0x0]
	cmp r12, #0x0
	streq r1, [r0, #0x0]
	bxeq lr
	ldr r3, [r12, #0x10]
	cmp r3, #0x0
	bne _020B8058
	ldrb r3, [r12, #0x18]
	ldrb r2, [r1, #0x18]
	cmp r3, r2
	bls _020B8050
	ldr r2, [r1, #0x10]
	mov r3, r1
	cmp r2, #0x0
	beq _020B8044
_020B8034:
	ldr r3, [r3, #0x10]
	ldr r2, [r3, #0x10]
	cmp r2, #0x0
	bne _020B8034
_020B8044:
	str r12, [r3, #0x10]
	str r1, [r0, #0x0]
	bx lr
_020B8050:
	str r1, [r12, #0x10]
	bx lr
_020B8058:
	cmp r3, #0x0
	beq _020B80AC
	ldrb r2, [r1, #0x18]
_020B8064:
	ldrb r0, [r3, #0x18]
	cmp r0, r2
	blo _020B809C
	ldr r0, [r1, #0x10]
	mov r2, r1
	cmp r0, #0x0
	beq _020B8090
_020B8080:
	ldr r2, [r2, #0x10]
	ldr r0, [r2, #0x10]
	cmp r0, #0x0
	bne _020B8080
_020B8090:
	str r1, [r12, #0x10]
	str r3, [r2, #0x10]
	bx lr
_020B809C:
	mov r12, r3
	ldr r3, [r3, #0x10]
	cmp r3, #0x0
	bne _020B8064
_020B80AC:
	str r1, [r12, #0x10]
	bx lr

	arm_func_start FUN_020B80B4
FUN_020B80B4: ; 0x020B80B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	mov r1, r5
	mov r0, #0x0
	mov r2, #0x54
	bl MIi_CpuClear32
	ldr r0, _020B8104 ; =0x021065B4
	ldr r1, _020B8108 ; =0x021065B0
	ldr r2, [r0, #0x0]
	ldr r0, _020B810C ; =0x021065AC
	str r2, [r5, #0xc]
	ldr r1, [r1, #0x0]
	str r1, [r5, #0x14]
	ldr r0, [r0, #0x0]
	str r0, [r5, #0x1c]
	str r4, [r5, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B8104: .word 0x021065B4
_020B8108: .word 0x021065B0
_020B810C: .word 0x021065AC

	arm_func_start FUN_020B8110
FUN_020B8110: ; 0x020B8110
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r12, #0x0
	str r12, [r0, #0x0]
	str r1, [r0, #0x8]
	str r12, [r0, #0x10]
	mov r4, #0x7f
	strb r4, [r0, #0x18]
	mov r4, #0x1000
	str r4, [r0, #0x4]
	ldr lr, _020B81A4 ; =0x02106594
	str r3, [r0, #0x14]
	ldr r6, [lr, #0x0]
	cmp r6, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r7,pc}
_020B8150: ; 0x020B8150
	ldrb r7, [r1, #0x0]
	ldr r4, _020B81A8 ; =0x021065B8
_020B8158:
	ldrb r3, [r4, r12, lsl #0x3]
	mov r5, r12, lsl #0x3
	cmp r7, r3
	bne _020B8190
	add r3, r4, r5
	ldrh lr, [r1, #0x2]
	ldrh r3, [r3, #0x2]
	cmp lr, r3
	bne _020B8190
	ldr r3, _020B81AC ; =0x021065BC
	ldr r3, [r3, r5]
	blx r3
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
_020B8190:
	add r12, r12, #0x1
	cmp r12, r6
	blo _020B8158
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B81A4: .word 0x02106594
_020B81A8: .word 0x021065B8
_020B81AC: .word 0x021065BC

	arm_func_start FUN_020B81B0
FUN_020B81B0: ; 0x020B81B0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x4a
	beq _020B81E4
	cmp r0, #0x4d
	beq _020B81D0
	cmp r0, #0x56
	beq _020B81E4
	b _020B81F8
_020B81D0:
	ldrb r0, [r1, #0x18]
	mov r0, r0, lsl #0x1
	add r0, r0, #0x1c
	bic r0, r0, #0x3
	bx lr
_020B81E4:
	ldrb r0, [r1, #0x17]
	mov r0, r0, lsl #0x1
	add r0, r0, #0x1c
	bic r0, r0, #0x3
	bx lr
_020B81F8:
	mov r0, #0x0
	bx lr

	arm_func_start FUN_020B8200
FUN_020B8200: ; 0x020B8200
	cmp r0, #0x0
	ldrne ip, _020B8260 ; =0x021CED18
	ldrne r12, [r12, #0xa0]
	andne r12, r12, #0xff
	strne r12, [r0, #0x0]
	cmp r1, #0x0
	ldrne r0, _020B8260 ; =0x021CED18
	ldrne r0, [r0, #0xa0]
	movne r0, r0, lsr #0x8
	andne r0, r0, #0xff
	strne r0, [r1, #0x0]
	cmp r2, #0x0
	ldrne r0, _020B8260 ; =0x021CED18
	ldrne r0, [r0, #0xa0]
	movne r0, r0, lsr #0x10
	andne r0, r0, #0xff
	strne r0, [r2, #0x0]
	cmp r3, #0x0
	ldrne r0, _020B8260 ; =0x021CED18
	ldrne r0, [r0, #0xa0]
	movne r0, r0, lsr #0x18
	andne r0, r0, #0xff
	strne r0, [r3, #0x0]
	bx lr
	.balign 4
_020B8260: .word 0x021CED18

	arm_func_start FUN_020B8264
FUN_020B8264: ; 0x020B8264
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020B829C ; =0x021CED18
	ldr r0, [r0, #0xfc]
	ands r0, r0, #0x80
	bne _020B8290
	bl FUN_020B82E4
	ldr r0, _020B829C ; =0x021CED18
	ldr r1, [r0, #0xfc]
	orr r1, r1, #0x80
	str r1, [r0, #0xfc]
_020B8290:
	ldr r0, _020B82A0 ; =0x021CEE78
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B829C: .word 0x021CED18
_020B82A0: .word 0x021CEE78

	arm_func_start FUN_020B82A4
FUN_020B82A4: ; 0x020B82A4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020B82DC ; =0x021CED18
	ldr r0, [r0, #0xfc]
	ands r0, r0, #0x80
	bne _020B82D0
	bl FUN_020B82E4
	ldr r0, _020B82DC ; =0x021CED18
	ldr r1, [r0, #0xfc]
	orr r1, r1, #0x80
	str r1, [r0, #0xfc]
_020B82D0:
	ldr r0, _020B82E0 ; =0x021CEE48
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B82DC: .word 0x021CED18
_020B82E0: .word 0x021CEE48

	arm_func_start FUN_020B82E4
FUN_020B82E4: ; 0x020B82E4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020B8330 ; =0x021CEDD4
	ldr r1, _020B8334 ; =0x021CED64
	ldr r2, _020B8338 ; =0x021CEE48
	bl MTX_Concat43
	ldr r3, _020B833C ; =0x021CED18
	ldr r0, _020B8338 ; =0x021CEE48
	ldr r2, [r3, #0xf4]
	mov r1, r0
	str r2, [sp, #0x0]
	ldr r2, [r3, #0xec]
	ldr r3, [r3, #0xf0]
	bl MTX_ScaleApply43
	ldr r0, _020B8338 ; =0x021CEE48
	ldr r1, _020B8340 ; =0x021CEE78
	bl MTX_Inverse43
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B8330: .word 0x021CEDD4
_020B8334: .word 0x021CED64
_020B8338: .word 0x021CEE48
_020B833C: .word 0x021CED18
_020B8340: .word 0x021CEE78

	arm_func_start FUN_020B8344
FUN_020B8344: ; 0x020B8344
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020B8384 ; =0x021CED18
	ldr r0, [r0, #0xfc]
	ands r0, r0, #0x8
	bne _020B8378
	ldr r0, _020B8388 ; =0x021CED64
	ldr r1, _020B838C ; =0x021CEE18
	bl MTX_Inverse43
	ldr r0, _020B8384 ; =0x021CED18
	ldr r1, [r0, #0xfc]
	orr r1, r1, #0x8
	str r1, [r0, #0xfc]
_020B8378:
	ldr r0, _020B838C ; =0x021CEE18
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B8384: .word 0x021CED18
_020B8388: .word 0x021CED64
_020B838C: .word 0x021CEE18

	arm_func_start FUN_020B8390
FUN_020B8390: ; 0x020B8390
	orr r0, r0, r1, lsl #0x4

	arm_func_start FUN_020B8394
FUN_020B8394: ; 0x020B8394
	ldr r1, [sp, #0x4]
	orr r0, r0, r2, lsl #0x6
	orr r0, r1, r0
	ldr r2, [sp, #0x0]
	orr r1, r0, r3, lsl #0x18
	ldr r0, _020B83B8 ; =0x021CED18
	orr r1, r1, r2, lsl #0x10
	str r1, [r0, #0x9c]
	bx lr
	.balign 4
_020B83B8: .word 0x021CED18

	arm_func_start FUN_020B83BC
FUN_020B83BC: ; 0x020B83BC
	cmp r2, #0x0
	movne r2, #0x1
	orr r1, r0, r1, lsl #0x10
	moveq r2, #0x0
	ldr r0, _020B83DC ; =0x021CED18
	orr r1, r1, r2, lsl #0xf
	str r1, [r0, #0x98]
	bx lr
	.balign 4
_020B83DC: .word 0x021CED18

	arm_func_start FUN_020B83E0
FUN_020B83E0: ; 0x020B83E0
	cmp r2, #0x0
	movne r2, #0x1
	orr r1, r0, r1, lsl #0x10
	moveq r2, #0x0
	ldr r0, _020B8400 ; =0x021CED18
	orr r1, r1, r2, lsl #0xf
	str r1, [r0, #0x94]
	bx lr
	.balign 4
_020B8400: .word 0x021CED18

	arm_func_start FUN_020B8404
FUN_020B8404: ; 0x020B8404
	ldr r2, _020B8414 ; =0x021CEDC0
	orr r1, r1, r0, lsl #0x1e
	str r1, [r2, r0, lsl #0x2]
	bx lr
	.balign 4
_020B8414: .word 0x021CEDC0

	arm_func_start FUN_020B8418
FUN_020B8418: ; 0x020B8418
	stmdb sp!, {r4,lr}
	ldr ip, _020B8444 ; =0x000003FF
	ldr lr, _020B8448 ; =0x021CED98
	and r4, r12, r1, asr #0x3
	and r1, r12, r2, asr #0x3
	and r2, r12, r3, asr #0x3
	orr r1, r4, r1, lsl #0xa
	orr r1, r1, r2, lsl #0x14
	orr r1, r1, r0, lsl #0x1e
	str r1, [lr, r0, lsl #0x2]
	ldmia sp!, {r4,pc}
	.balign 4
_020B8444: .word 0x000003FF
_020B8448: .word 0x021CED98

	arm_func_start FUN_020B844C
FUN_020B844C: ; 0x020B844C
	ldr r3, _020B846C ; =0x021CEE04
	ldmia r0, {r0-r2}
	stmia r3, {r0-r2}
	ldr r0, _020B8470 ; =0x021CED18
	ldr r1, [r0, #0xfc]
	bic r1, r1, #0xa4
	str r1, [r0, #0xfc]
	bx lr
	.balign 4
_020B846C: .word 0x021CEE04
_020B8470: .word 0x021CED18

	arm_func_start FUN_020B8474
FUN_020B8474: ; 0x020B8474
	ldr r3, _020B8494 ; =0x021CEDF8
	ldmia r0, {r0-r2}
	stmia r3, {r0-r2}
	ldr r0, _020B8498 ; =0x021CED18
	ldr r1, [r0, #0xfc]
	bic r1, r1, #0xa4
	str r1, [r0, #0xfc]
	bx lr
	.balign 4
_020B8494: .word 0x021CEDF8
_020B8498: .word 0x021CED18

	arm_func_start FUN_020B849C
FUN_020B849C: ; 0x020B849C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020B84D4 ; =0x021CED18
	mov r2, #0x3e
	ldr r0, [r1], #0x4
	bl FUN_020BB1C0
	ldr r0, _020B84D4 ; =0x021CED18
	ldr r1, [r0, #0xfc]
	bic r1, r1, #0x1
	str r1, [r0, #0xfc]
	bic r1, r1, #0x2
	str r1, [r0, #0xfc]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020B84D4: .word 0x021CED18

	arm_func_start FUN_020B84D8
FUN_020B84D8: ; 0x020B84D8
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r8, _020B85F4 ; =0x17101610
	ldr r1, _020B85F8 ; =0x021CED18
	ldr r5, _020B85FC ; =0x32323232
	ldr r4, _020B8600 ; =0x60293130
	ldr r3, _020B8604 ; =0x33333333
	ldr r2, _020B8608 ; =0x002A1B19
	mov r7, #0x0
	mov r6, #0x2
	ldr r0, _020B860C ; =0x021CED64
	str r8, [r1, #0x0]
	str r7, [r1, #0x4]
	str r6, [r1, #0x48]
	str r5, [r1, #0x7c]
	str r4, [r1, #0x90]
	str r3, [r1, #0xa4]
	str r2, [r1, #0xb8]
	bl MTX_Identity43_
	ldr r0, _020B8610 ; =0x021CED20
	bl MTX_Identity44_
	mov r2, r7
	ldr r1, _020B85F8 ; =0x021CED18
	ldr r7, _020B8614 ; =0x4210C210
	ldr r0, _020B8618 ; =0x40000200
	ldr lr, _020B861C ; =0x2D8B62D8
	ldr sb, _020B8620 ; =0x800001FF
	ldr r8, _020B8624 ; =0xC0080000
	ldr r6, _020B8628 ; =0x001F008F
	ldr r5, _020B862C ; =0xBFFF0000
	ldr r4, _020B8630 ; =0x00007FFF
	ldr ip, _020B8634 ; =0x800003E0
	ldr r3, _020B8638 ; =0xC0007C00
	str r0, [r1, #0x84]
	str lr, [r1, #0x80]
	mov lr, #0x4000001f
	ldr r0, _020B863C ; =0x021CEDD4
	str r9, [r1, #0x88]
	str r8, [r1, #0x8c]
	str r7, [r1, #0x94]
	str r7, [r1, #0x98]
	str r6, [r1, #0x9c]
	str r5, [r1, #0xa0]
	str r4, [r1, #0xa8]
	str lr, [r1, #0xac]
	str r12, [r1, #0xb0]
	str r3, [r1, #0xb4]
	str r2, [r1, #0xe0]
	str r2, [r1, #0xe4]
	str r2, [r1, #0xe8]
	bl MTX_Identity33_
	mov r3, #0x1000
	ldr r0, _020B85F8 ; =0x021CED18
	mov r2, #0x0
	rsb r1, r3, #0x0
	str r3, [r0, #0xec]
	str r3, [r0, #0xf0]
	str r3, [r0, #0xf4]
	str r2, [r0, #0xf8]
	str r2, [r0, #0xfc]
	str r2, [r0, #0x248]
	str r2, [r0, #0x244]
	str r2, [r0, #0x240]
	str r2, [r0, #0x254]
	str r2, [r0, #0x24c]
	str r3, [r0, #0x250]
	str r2, [r0, #0x25c]
	str r2, [r0, #0x258]
	str r1, [r0, #0x260]
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020B85F4: .word 0x17101610
_020B85F8: .word 0x021CED18
_020B85FC: .word 0x32323232
_020B8600: .word 0x60293130
_020B8604: .word 0x33333333
_020B8608: .word 0x002A1B19
_020B860C: .word 0x021CED64
_020B8610: .word 0x021CED20
_020B8614: .word 0x4210C210
_020B8618: .word 0x40000200
_020B861C: .word 0x2D8B62D8
_020B8620: .word 0x800001FF
_020B8624: .word 0xC0080000
_020B8628: .word 0x001F008F
_020B862C: .word 0xBFFF0000
_020B8630: .word 0x00007FFF
_020B8634: .word 0x800003E0
_020B8638: .word 0xC0007C00
_020B863C: .word 0x021CEDD4

	arm_func_start FUN_020B8640
FUN_020B8640: ; 0x020B8640
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r7, r0
	mov r0, #0x0
	mov r6, r1
	str r0, [r7, #0x0]
	add r4, sp, #0x0
	mov r5, r2, lsl #0x1
	mov r8, #0x1
_020B8664:
	add r1, r5, r6
	ldrh r2, [r1, #0x1a]
	ands r1, r2, #0x100
	beq _020B869C
	ldr r3, [r6, #0xc]
	mov r0, r4
	mov r1, r6
	and r2, r2, #0xff
	blx r3
	ldr r2, [r7, #0x0]
	ldr r1, [sp, #0x0]
	mov r0, r8
	orr r1, r2, r1
	str r1, [r7, #0x0]
_020B869C:
	ldr r6, [r6, #0x10]
	cmp r6, #0x0
	bne _020B8664
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020B86B0
FUN_020B86B0: ; 0x020B86B0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x5c
	mov r9, r1
	ldr r3, [r9, #0x10]
	mov r10, r0
	mov r8, r2
	cmp r3, #0x0
	bne _020B8704
	add r2, r9, r8, lsl #0x1
	ldrh r4, [r2, #0x1a]
	and r2, r4, #0x300
	cmp r2, #0x100
	addne sp, sp, #0x5c
	movne r0, #0x0
	ldmneia sp!, {r4-r11,pc}
_020B86EC: ; 0x020B86EC
	ldr r3, [r9, #0xc]
	and r2, r4, #0xff
	blx r3
	add sp, sp, #0x5c
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_020B8704:
	mov r7, #0x0
	mov r3, r7
	mov r4, r9
	mov r2, r8, lsl #0x1
_020B8714:
	add r0, r2, r4
	ldrh r0, [r0, #0x1a]
	and r0, r0, #0x300
	cmp r0, #0x100
	ldreq r0, [r4, #0x4]
	moveq r1, r4
	ldr r4, [r4, #0x10]
	addeq r7, r7, r0
	addeq r3, r3, #0x1
	cmp r4, #0x0
	bne _020B8714
	cmp r7, #0x0
	addeq sp, sp, #0x5c
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,pc}
_020B8750: ; 0x020B8750
	cmp r3, #0x1
	bne _020B877C
	add r0, r1, r8, lsl #0x1
	ldrh r2, [r0, #0x1a]
	ldr r3, [r1, #0xc]
	mov r0, r10
	and r2, r2, #0xff
	blx r3
	add sp, sp, #0x5c
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_020B877C:
	mov r1, r10
	mov r0, #0x0
	mov r2, #0x58
	bl MIi_CpuClearFast
_020B878C: ; 0x020B878C
	mvn r0, #0x0
	str r0, [r10, #0x0]
	add r5, sp, #0x0
	add r4, sp, #0x4
	add r11, sp, #0x10
_020B87A0:
	add r0, r9, r8, lsl #0x1
	ldrh r2, [r0, #0x1a]
	and r0, r2, #0x300
	cmp r0, #0x100
	bne _020B8948
	ldr r0, [r9, #0x4]
	cmp r0, #0x0
	ble _020B8948
	ldr r3, [r9, #0xc]
	mov r0, r5
	mov r1, r9
	and r2, r2, #0xff
	blx r3
	cmp r7, #0x1000
	ldreq r6, [r9, #0x4]
	beq _020B87F0
	ldr r0, [r9, #0x4]
	mov r1, r7
	bl FX_Div
	mov r6, r0
_020B87F0:
	ldr r3, [sp, #0x0]
	mov r1, r4
	mov r2, r6
	add r0, r10, #0x4
	and r3, r3, #0x1
	bl FUN_020B8998
	ldr r1, [sp, #0x0]
	add r0, r10, #0x10
	and r3, r1, #0x8
	mov r1, r11
	mov r2, r6
	bl FUN_020B8998
	ldr r3, [sp, #0x0]
	add r0, r10, #0x1c
	add r1, sp, #0x1c
	mov r2, r6
	and r3, r3, #0x10
	bl FUN_020B8998
_020B8838: ; 0x020B8838
	ldr r0, [sp, #0x0]
	ands r0, r0, #0x4
	bne _020B8898
	ldr r0, [sp, #0x4c]
	ldr r2, [r10, #0x4c]
	smull r1, r0, r6, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	add r0, r2, r1
	str r0, [r10, #0x4c]
	ldr r0, [sp, #0x50]
	ldr r2, [r10, #0x50]
	smull r1, r0, r6, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	add r0, r2, r1
	str r0, [r10, #0x50]
	ldr r0, [sp, #0x54]
	ldr r2, [r10, #0x54]
	smull r1, r0, r6, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	add r0, r2, r1
	str r0, [r10, #0x54]
_020B8898:
	ldr r0, [sp, #0x0]
	ands r0, r0, #0x2
	bne _020B8920
	ldr r0, [sp, #0x28]
	ldr r1, [r10, #0x28]
	mul r0, r6, r0
	add r0, r1, r0, asr #0xc
	str r0, [r10, #0x28]
	ldr r0, [sp, #0x2c]
	ldr r1, [r10, #0x2c]
	mul r0, r6, r0
	add r0, r1, r0, asr #0xc
	str r0, [r10, #0x2c]
	ldr r0, [sp, #0x30]
	ldr r1, [r10, #0x30]
	mul r0, r6, r0
	add r0, r1, r0, asr #0xc
	str r0, [r10, #0x30]
	ldr r0, [sp, #0x34]
	ldr r1, [r10, #0x34]
	mul r0, r6, r0
	add r0, r1, r0, asr #0xc
	str r0, [r10, #0x34]
	ldr r0, [sp, #0x38]
	ldr r1, [r10, #0x38]
	mul r0, r6, r0
	add r0, r1, r0, asr #0xc
	str r0, [r10, #0x38]
	ldr r0, [sp, #0x3c]
	ldr r1, [r10, #0x3c]
	mul r0, r6, r0
	add r0, r1, r0, asr #0xc
	str r0, [r10, #0x3c]
	b _020B8938
_020B8920:
	ldr r0, [r10, #0x28]
	add r0, r0, r6
	str r0, [r10, #0x28]
	ldr r0, [r10, #0x38]
	add r0, r0, r6
	str r0, [r10, #0x38]
_020B8938:
	ldr r1, [r10, #0x0]
	ldr r0, [sp, #0x0]
	and r0, r1, r0
	str r0, [r10, #0x0]
_020B8948:
	ldr r9, [r9, #0x10]
	cmp r9, #0x0
	bne _020B87A0
	add r0, r10, #0x28
	add r1, r10, #0x34
	add r2, r10, #0x40
	bl VEC_CrossProduct
	add r0, r10, #0x28
	mov r1, r0
	bl VEC_Normalize
	add r0, r10, #0x40
	mov r1, r0
	bl VEC_Normalize
	add r0, r10, #0x40
	add r1, r10, #0x28
	add r2, r10, #0x34
	bl VEC_CrossProduct
	mov r0, #0x1
	add sp, sp, #0x5c
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020B8998
FUN_020B8998:
	cmp r3, #0x0
	beq _020B89C8
	ldr r1, [r0, #0x0]
	add r1, r1, r2
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, r2
	str r1, [r0, #0x4]
	ldr r1, [r0, #0x8]
	add r1, r1, r2
	str r1, [r0, #0x8]
	bx lr
_020B89C8:
	ldr r3, [r1, #0x0]
	ldr r12, [r0, #0x0]
	mul r3, r2, r3
	add r3, r12, r3, asr #0xc
	str r3, [r0, #0x0]
	ldr r3, [r1, #0x4]
	ldr r12, [r0, #0x4]
	mul r3, r2, r3
	add r3, r12, r3, asr #0xc
	str r3, [r0, #0x4]
	ldr r1, [r1, #0x8]
	ldr r3, [r0, #0x8]
	mul r1, r2, r1
	add r1, r3, r1, asr #0xc
	str r1, [r0, #0x8]
	bx lr

	arm_func_start FUN_020B8A08
FUN_020B8A08: ; 0x020B8A08
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r5, r1
	mov r0, #0x0
	mov r4, r2, lsl #0x1
	mov r7, #0x1
_020B8A24:
	add r1, r4, r5
	ldrh r2, [r1, #0x1a]
	ands r1, r2, #0x100
	beq _020B8A4C
	ldr r3, [r5, #0xc]
	mov r0, r6
	mov r1, r5
	and r2, r2, #0xff
	blx r3
	mov r0, r7
_020B8A4C:
	ldr r5, [r5, #0x10]
	cmp r5, #0x0
	bne _020B8A24
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020B8A60
FUN_020B8A60: ; 0x020B8A60
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x80
	mov r5, r0
	ldr r1, [r5, #0x8]
	ands r0, r1, #0x200
	bne _020B8DB4
	ands r0, r1, #0x1
	beq _020B8DB4
	add r0, sp, #0x10
	mov r1, #0x0
	bl FUN_020BB824
	mov r0, #0x1e
	str r0, [sp, #0x0]
	add r1, sp, #0x0
	mov r0, #0x13
	mov r2, #0x1
	bl FUN_020BB1C0
	ldr r2, [r5, #0xb0]
	ldr r0, [r2, #0x10]
	and r1, r0, #0xc0000000
	cmp r1, #0xc0000000
	beq _020B8AF0
	bic r0, r0, #0xc0000000
	str r0, [r2, #0x10]
	ldr r2, [r5, #0xb0]
	ldr r3, _020B8DC8 ; =0x02106630
	ldr r0, [r2, #0x10]
	ldr r1, _020B8DCC ; =0x02106634
	orr r0, r0, #0xc0000000
	str r0, [r2, #0x10]
	ldr r2, [r5, #0xb0]
	ldr r0, [r3, #0x0]
	ldr r4, [r2, #0x10]
	mov r2, #0x1
	str r4, [r3, #0x4]
	bl FUN_020BB1C0
_020B8AF0:
	ldr r0, [r5, #0x40]
	cmp r0, #0x0
	ldrneb r4, [r5, #0x99]
	moveq r4, #0x0
	cmp r4, #0x1
	bne _020B8B3C
	ldr r1, [r5, #0x8]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r5, #0x8]
	ldr r1, [r5, #0x40]
	blx r1
	ldr r0, [r5, #0x40]
	cmp r0, #0x0
	ldrneb r4, [r5, #0x99]
	ldr r0, [r5, #0x8]
	moveq r4, #0x0
	and r0, r0, #0x40
	b _020B8B40
_020B8B3C:
	mov r0, #0x0
_020B8B40:
	cmp r0, #0x0
	bne _020B8B84
	ldr r0, [r5, #0xb0]
	ldr r1, _020B8DD0 ; =0x02106660
	ldrh r6, [r0, #0x2e]
	ldrh r3, [r0, #0x2c]
	mov r0, #0x16
	rsb r2, r6, #0x0
	mov lr, r3, lsl #0xf
	mov r12, r2, lsl #0xf
	mov r3, r6, lsl #0xf
	mov r2, #0x10
	str lr, [r1, #0x0]
	str r12, [r1, #0x14]
	str lr, [r1, #0x30]
	str r3, [r1, #0x34]
	bl FUN_020BB1C0
_020B8B84:
	cmp r4, #0x2
	bne _020B8BC0
	ldr r1, [r5, #0x8]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r5, #0x8]
	ldr r1, [r5, #0x40]
	blx r1
	ldr r0, [r5, #0x40]
	cmp r0, #0x0
	ldrneb r4, [r5, #0x99]
	ldr r0, [r5, #0x8]
	moveq r4, #0x0
	and r0, r0, #0x40
	b _020B8BC4
_020B8BC0:
	mov r0, #0x0
_020B8BC4:
	cmp r0, #0x0
	bne _020B8C28
	ldr r12, [r5, #0xd8]
	ldr r0, [r5, #0x0]
	ldrh r2, [r12, #0xa]
	add r3, r12, #0x4
	ldrb r0, [r0, #0x1]
	ldrh r1, [r3, r2]
	add r2, r3, r2
	mla r0, r1, r0, r2
	ldr r0, [r0, #0x4]
	add r1, r12, r0
	ldrh r2, [r1, #0x1e]
	ands r0, r2, #0x2000
	beq _020B8C28
	add r1, r1, #0x2c
	ands r0, r2, #0x2
	addeq r1, r1, #0x8
	ands r0, r2, #0x4
	addeq r1, r1, #0x4
	ands r0, r2, #0x8
	addeq r1, r1, #0x8
	mov r0, #0x18
	mov r2, #0x10
	bl FUN_020BB1C0
_020B8C28:
	cmp r4, #0x3
	movne r0, #0x0
	bne _020B8C54
	ldr r1, [r5, #0x8]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r5, #0x8]
	ldr r1, [r5, #0x40]
	blx r1
	ldr r0, [r5, #0x8]
	and r0, r0, #0x40
_020B8C54:
	cmp r0, #0x0
	bne _020B8D84
	ldr r0, _020B8DD4 ; =0x021CED18
	ldr r1, [r0, #0xfc]
	ands r0, r1, #0x1
	beq _020B8CA0
	ldr r1, _020B8DD8 ; =0x021CEDF8
	mov r0, #0x1c
	mov r2, #0x3
	bl FUN_020BB1C0
	ldr r1, _020B8DDC ; =0x021CEDD4
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
	add r1, sp, #0x10
	mov r0, #0x19
	mov r2, #0xc
	bl FUN_020BB1C0
	b _020B8CE0
_020B8CA0:
	ands r0, r1, #0x2
	beq _020B8CBC
	add r1, sp, #0x10
	mov r0, #0x19
	mov r2, #0xc
	bl FUN_020BB1C0
	b _020B8CE0
_020B8CBC:
	bl FUN_020B8344
	mov r1, r0
	mov r0, #0x19
	mov r2, #0xc
	bl FUN_020BB1C0
	add r1, sp, #0x10
	mov r0, #0x19
	mov r2, #0xc
	bl FUN_020BB1C0
_020B8CE0:
	bl FUN_020BB394
	ldr r0, _020B8DE0 ; =0x04000440
	mov r2, #0x0
	ldr r1, _020B8DE4 ; =0x04000444
	str r2, [r0, #0x0]
	ldr r0, _020B8DE8 ; =0x04000454
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add r4, sp, #0x40
_020B8D04:
	mov r0, r4
	bl G3X_GetClipMtx
_020B8D0C: ; 0x020B8D0C
	cmp r0, #0x0
	bne _020B8D04
	ldr r1, _020B8DEC ; =0x04000448
	mov r2, #0x1
	str r2, [r1, #0x0]
	ldr r0, _020B8DE0 ; =0x04000440
	mov r2, #0x3
	str r2, [r0, #0x0]
	add r1, sp, #0x40
	mov r0, #0x16
	mov r2, #0x10
	bl FUN_020BB1C0
	ldr r1, [sp, #0x70]
	ldr r0, [sp, #0x74]
	mov r2, r1, asr #0x4
	mov r1, r0, asr #0x4
	mov r0, r2, lsl #0x8
	mov r1, r1, lsl #0x8
	mov r0, r0, asr #0x10
	mov r1, r1, asr #0x10
	mov r0, r0, lsl #0x10
	mov r1, r1, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r1, lsr #0x10
	orr r3, r2, r0, lsl #0x10
	add r1, sp, #0x4
	mov r0, #0x22
	mov r2, #0x1
	str r3, [sp, #0x4]
	bl FUN_020BB1C0
_020B8D84:
	mov r3, #0x2
	add r1, sp, #0x8
	mov r0, #0x10
	mov r2, #0x1
	str r3, [sp, #0x8]
	bl FUN_020BB1C0
	mov r3, #0x1e
	add r1, sp, #0xc
	mov r0, #0x14
	mov r2, #0x1
	str r3, [sp, #0xc]
	bl FUN_020BB1C0
_020B8DB4:
	ldr r0, [r5, #0x0]
	add r0, r0, #0x3
	str r0, [r5, #0x0]
	add sp, sp, #0x80
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B8DC8: .word 0x02106630
_020B8DCC: .word 0x02106634
_020B8DD0: .word 0x02106660
_020B8DD4: .word 0x021CED18
_020B8DD8: .word 0x021CEDF8
_020B8DDC: .word 0x021CEDD4
_020B8DE0: .word 0x04000440
_020B8DE4: .word 0x04000444
_020B8DE8: .word 0x04000454
_020B8DEC: .word 0x04000448

	arm_func_start FUN_020B8DF0
FUN_020B8DF0: ; 0x020B8DF0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x44
	mov r7, r0
	ldr r1, [r7, #0x8]
	ands r0, r1, #0x200
	bne _020B90E8
	ands r0, r1, #0x1
	beq _020B90E8
	ldr r2, [r7, #0xb0]
	ldr r0, [r2, #0x10]
	and r1, r0, #0xc0000000
	cmp r1, #0x80000000
	beq _020B8E5C
	bic r0, r0, #0xc0000000
	str r0, [r2, #0x10]
	ldr r2, [r7, #0xb0]
	ldr r3, _020B90FC ; =0x02106638
	ldr r0, [r2, #0x10]
	ldr r1, _020B9100 ; =0x0210663C
	orr r0, r0, #0x80000000
	str r0, [r2, #0x10]
	ldr r2, [r7, #0xb0]
	ldr r0, [r3, #0x0]
	ldr r4, [r2, #0x10]
	mov r2, #0x1
	str r4, [r3, #0x4]
	bl FUN_020BB1C0
_020B8E5C:
	mov r0, #0x3
	str r0, [sp, #0x0]
	add r1, sp, #0x0
	mov r0, #0x10
	mov r2, #0x1
	bl FUN_020BB1C0
	ldr r0, [r7, #0x3c]
	cmp r0, #0x0
	ldrneb r6, [r7, #0x98]
	moveq r6, #0x0
	cmp r6, #0x1
	bne _020B8EC0
	ldr r1, [r7, #0x8]
	mov r0, r7
	bic r1, r1, #0x40
	str r1, [r7, #0x8]
	ldr r1, [r7, #0x3c]
	blx r1
	ldr r0, [r7, #0x3c]
	cmp r0, #0x0
	ldrneb r6, [r7, #0x98]
	ldr r0, [r7, #0x8]
	moveq r6, #0x0
	and r0, r0, #0x40
	b _020B8EC4
_020B8EC0:
	mov r0, #0x0
_020B8EC4:
	cmp r0, #0x0
	bne _020B8F3C
	ldr r0, [r7, #0xb0]
	add r1, sp, #0x38
	ldrh r4, [r0, #0x2e]
	ldrh r5, [r0, #0x2c]
	mov r3, #0x10000
	rsb r0, r4, #0x0
	mov r12, r0, lsl #0xf
	mov lr, r5, lsl #0xf
	mov r0, #0x1b
	mov r2, #0x3
	str lr, [sp, #0x38]
	str r12, [sp, #0x3c]
	str r3, [sp, #0x40]
	bl FUN_020BB1C0
	mov r0, r5, lsl #0x13
	mov r1, r4, lsl #0x13
	mov r0, r0, asr #0x10
	mov r1, r1, asr #0x10
	mov r0, r0, lsl #0x10
	mov r1, r1, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r1, lsr #0x10
	orr r3, r2, r0, lsl #0x10
	add r1, sp, #0x4
	mov r0, #0x22
	mov r2, #0x1
	str r3, [sp, #0x4]
	bl FUN_020BB1C0
_020B8F3C:
	cmp r6, #0x2
	bne _020B8F78
	ldr r1, [r7, #0x8]
	mov r0, r7
	bic r1, r1, #0x40
	str r1, [r7, #0x8]
	ldr r1, [r7, #0x3c]
	blx r1
	ldr r0, [r7, #0x3c]
	cmp r0, #0x0
	ldrneb r6, [r7, #0x98]
	ldr r0, [r7, #0x8]
	moveq r6, #0x0
	and r0, r0, #0x40
	b _020B8F7C
_020B8F78:
	mov r0, #0x0
_020B8F7C:
	cmp r0, #0x0
	bne _020B8FE0
	ldr r4, [r7, #0xd8]
	ldr r0, [r7, #0x0]
	ldrh r2, [r4, #0xa]
	add r3, r4, #0x4
	ldrb r0, [r0, #0x1]
	ldrh r1, [r3, r2]
	add r2, r3, r2
	mla r0, r1, r0, r2
	ldr r0, [r0, #0x4]
	add r1, r4, r0
	ldrh r2, [r1, #0x1e]
	ands r0, r2, #0x2000
	beq _020B8FE0
	add r1, r1, #0x2c
	ands r0, r2, #0x2
	addeq r1, r1, #0x8
	ands r0, r2, #0x4
	addeq r1, r1, #0x4
	ands r0, r2, #0x8
	addeq r1, r1, #0x8
	mov r0, #0x18
	mov r2, #0x10
	bl FUN_020BB1C0
_020B8FE0:
	cmp r6, #0x3
	movne r0, #0x0
	bne _020B900C
	ldr r1, [r7, #0x8]
	mov r0, r7
	bic r1, r1, #0x40
	str r1, [r7, #0x8]
	ldr r1, [r7, #0x3c]
	blx r1
	ldr r0, [r7, #0x8]
	and r0, r0, #0x40
_020B900C:
	cmp r0, #0x0
	bne _020B90D0
	mov r3, #0x2
	add r1, sp, #0x8
	mov r0, #0x10
	mov r2, #0x1
	str r3, [sp, #0x8]
	bl FUN_020BB1C0
	add r1, sp, #0x14
	mov r0, #0x0
	bl FUN_020BB824
	mov r3, #0x3
	add r1, sp, #0xc
	mov r0, #0x10
	mov r2, #0x1
	str r3, [sp, #0xc]
	bl FUN_020BB1C0
	ldr r0, _020B9104 ; =0x021CED18
	ldr r1, [r0, #0xfc]
	ands r0, r1, #0x1
	beq _020B9094
	ldr r1, _020B9108 ; =0x021CED64
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
	ldr r1, _020B910C ; =0x021CEDD4
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
	add r1, sp, #0x14
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
	b _020B90D0
_020B9094:
	ands r0, r1, #0x2
	beq _020B90C0
	ldr r1, _020B9108 ; =0x021CED64
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
	add r1, sp, #0x14
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
	b _020B90D0
_020B90C0:
	add r1, sp, #0x14
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
_020B90D0:
	mov r3, #0x2
	add r1, sp, #0x10
	mov r0, #0x10
	mov r2, #0x1
	str r3, [sp, #0x10]
	bl FUN_020BB1C0
_020B90E8:
	ldr r0, [r7, #0x0]
	add r0, r0, #0x3
	str r0, [r7, #0x0]
	add sp, sp, #0x44
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B90FC: .word 0x02106638
_020B9100: .word 0x0210663C
_020B9104: .word 0x021CED18
_020B9108: .word 0x021CED64
_020B910C: .word 0x021CEDD4

	arm_func_start FUN_020B9110
FUN_020B9110: ; 0x020B9110
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x10
	mov r4, r0
	ldr r2, [r4, #0x8]
	ands r0, r2, #0x100
	bne _020B9164
	ands r0, r2, #0x200
	bne _020B9164
	cmp r1, #0x0
	ldreq r0, [r4, #0xe0]
	add r1, sp, #0x0
	streq r0, [sp, #0x8]
	streq r0, [sp, #0x4]
	streq r0, [sp, #0x0]
	ldrne r0, [r4, #0xe4]
	mov r2, #0x3
	strne r0, [sp, #0x8]
	strne r0, [sp, #0x4]
	strne r0, [sp, #0x0]
	mov r0, #0x1b
	bl FUN_020BB1C0
_020B9164:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	add sp, sp, #0x10
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020B9178
FUN_020B9178: ; 0x020B9178
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	ldr r0, [r5, #0x34]
	cmp r0, #0x0
	ldrneb r4, [r5, #0x96]
	moveq r4, #0x0
	cmp r4, #0x1
	bne _020B91CC
	ldr r1, [r5, #0x8]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r5, #0x8]
	ldr r1, [r5, #0x34]
	blx r1
	ldr r0, [r5, #0x34]
	cmp r0, #0x0
	ldrneb r4, [r5, #0x96]
	ldr r0, [r5, #0x8]
	moveq r4, #0x0
	and r1, r0, #0x40
	b _020B91D0
_020B91CC:
	mov r1, #0x0
_020B91D0:
	ldr r0, [r5, #0x8]
	ands r0, r0, #0x100
	bne _020B9228
	cmp r1, #0x0
	bne _020B9228
	ldr r0, [r5, #0x0]
	ldrb r12, [r0, #0x1]
	ldrb r3, [r0, #0x2]
	ldrb lr, [r0, #0x3]
	ldrb r2, [r0, #0x5]
	ldrb r1, [r0, #0x6]
	orr r3, r12, r3, lsl #0x8
	ldrb r6, [r0, #0x4]
	orr r12, r3, lr, lsl #0x10
	ldrb r3, [r0, #0x7]
	orr r1, r2, r1, lsl #0x8
	orr r6, r12, r6, lsl #0x18
	ldrb r2, [r0, #0x8]
	orr r1, r1, r3, lsl #0x10
	add r0, r0, r6
	orr r1, r1, r2, lsl #0x18
	bl FUN_020BB2B0
_020B9228:
	cmp r4, #0x3
	bne _020B9248
	ldr r1, [r5, #0x8]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r5, #0x8]
	ldr r1, [r5, #0x34]
	blx r1
_020B9248:
	ldr r0, [r5, #0x0]
	add r0, r0, #0x9
	str r0, [r5, #0x0]
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020B9258
FUN_020B9258: ; 0x020B9258
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x8c
	ldr r1, [r0, #0x4]
	ldr r4, [r0, #0x0]
	ldr r6, [r1, #0x4]
	ldrb r2, [r4, #0x2]
	ldr r3, [r6, #0x10]
	mov r10, #0x0
	str r0, [sp, #0x0]
	str r2, [sp, #0x8]
	add r3, r6, r3
	add r1, sp, #0x34
	mov r0, r10
	mov r2, #0x54
	mov r9, r10
	str r3, [sp, #0x4]
	add r8, r4, #0x3
	bl MIi_CpuClearFast
	bl FUN_020BB394
	ldr r0, _020B98AC ; =0x04000440
	mov r7, r10
	str r7, [r0, #0x0]
	mov r0, #0x1
	ldr r2, _020B98B0 ; =0x0400044C
	ldr r1, _020B98B4 ; =0x04000454
	str r0, [r2, #0x0]
	str r0, [sp, #0x10]
	str r7, [r1, #0x0]
	mov r1, #0x2
	ldr r0, _020B98AC ; =0x04000440
	str r1, [sp, #0x14]
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	bls _020B96CC
_020B92E4:
	ldrb r4, [r8, #0x1]
	mov r0, #0x64
	ldr r3, _020B98B8 ; =0x021D0380
	mul r0, r4, r0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x0]
	mov r1, r4, lsr #0x5
	add r0, r0, r1, lsl #0x2
	ldr r1, [sp, #0x10]
	and r2, r4, #0x1f
	mov r1, r1, lsl r2
	ldr r11, [r0, #0xcc]
	ldr r2, [sp, #0xc]
	ands r11, r1, r11
	add r6, r3, r2
	bne _020B9358
	ldr r3, [r0, #0xcc]
	mov r2, #0x54
	orr r1, r3, r1
	str r1, [r0, #0xcc]
	ldr r0, [sp, #0x4]
	ldr r1, _020B98BC ; =0x04000450
	mla r0, r4, r2, r0
	ldrb r2, [r8, #0x0]
	str r2, [r1, #0x0]
	ldr r2, [sp, #0x10]
	ldr r1, _020B98AC ; =0x04000440
	str r2, [r1, #0x0]
	bl G3_MultMtx43
_020B9358:
	cmp r7, #0x0
	beq _020B9500
	ldr r2, [sp, #0x6c]
	ldr r1, [r5, #0x0]
	str r2, [sp, #0x18]
	ldr r2, [sp, #0x70]
	mov r0, r1, asr #0x1f
	str r2, [sp, #0x1c]
	ldr r2, [sp, #0x74]
	ldr r12, [sp, #0x64]
	str r2, [sp, #0x20]
	ldr r2, [sp, #0x78]
	ldr lr, [sp, #0x68]
	str r2, [sp, #0x24]
	ldr r2, [sp, #0x7c]
	str r2, [sp, #0x28]
	ldr r2, [sp, #0x80]
	str r2, [sp, #0x2c]
	ldr r2, [sp, #0x84]
	str r2, [sp, #0x30]
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r0, r3, lsr #0xc
	orr r0, r0, r2, lsl #0x14
	adds r0, r12, r0
	str r0, [sp, #0x64]
	ldr r1, [r5, #0x4]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r0, r3, lsr #0xc
	orr r0, r0, r2, lsl #0x14
	adds r0, lr, r0
	str r0, [sp, #0x68]
	ldr r1, [r5, #0x8]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r1, r3, lsr #0xc
	ldr r0, [sp, #0x18]
	orr r1, r1, r2, lsl #0x14
	adds r0, r0, r1
	str r0, [sp, #0x6c]
	ldr r1, [r5, #0xc]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r1, r3, lsr #0xc
	ldr r0, [sp, #0x1c]
	orr r1, r1, r2, lsl #0x14
	adds r0, r0, r1
	str r0, [sp, #0x70]
	ldr r1, [r5, #0x10]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r1, r3, lsr #0xc
	ldr r0, [sp, #0x20]
	orr r1, r1, r2, lsl #0x14
	adds r0, r0, r1
	str r0, [sp, #0x74]
	ldr r1, [r5, #0x14]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r1, r3, lsr #0xc
	ldr r0, [sp, #0x24]
	orr r1, r1, r2, lsl #0x14
	adds r0, r0, r1
	str r0, [sp, #0x78]
	ldr r1, [r5, #0x18]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r1, r3, lsr #0xc
	ldr r0, [sp, #0x28]
	orr r1, r1, r2, lsl #0x14
	adds r0, r0, r1
	str r0, [sp, #0x7c]
	ldr r1, [r5, #0x1c]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r1, r3, lsr #0xc
	ldr r0, [sp, #0x2c]
	orr r1, r1, r2, lsl #0x14
	adds r0, r0, r1
	str r0, [sp, #0x80]
	ldr r1, [r5, #0x20]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r1, r3, lsr #0xc
	ldr r0, [sp, #0x30]
	orr r1, r1, r2, lsl #0x14
	adds r0, r0, r1
	str r0, [sp, #0x84]
_020B9500:
	cmp r11, #0x0
	bne _020B9538
_020B9508:
	mov r0, r6
	bl G3X_GetClipMtx
_020B9510: ; 0x020B9510
	cmp r0, #0x0
	bne _020B9508
	ldr r1, [sp, #0x14]
	ldr r0, _020B98AC ; =0x04000440
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	mov r1, #0x54
	mla r0, r4, r1, r0
	add r0, r0, #0x30
	bl G3_MultMtx33
_020B9538:
	ldrb r1, [r8, #0x2]
	ldr r2, [sp, #0x34]
	ldr r0, [r6, #0x0]
	mov r10, r1, lsl #0x4
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r2, r1
	str r0, [sp, #0x34]
	mov r9, r10, asr #0x1f
	ldr r2, [sp, #0x38]
	ldr r0, [r6, #0x4]
	ldr r3, [sp, #0x3c]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r2, r1
	str r0, [sp, #0x38]
	ldr r0, [r6, #0x8]
	ldr r2, [sp, #0x40]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r3, r1
	str r0, [sp, #0x3c]
	ldr r0, [r6, #0x10]
	ldr r3, [sp, #0x44]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r2, r1
	str r0, [sp, #0x40]
	ldr r0, [r6, #0x14]
	ldr r2, [sp, #0x48]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r3, r1
	str r0, [sp, #0x44]
	ldr r0, [r6, #0x18]
	ldr r3, [sp, #0x4c]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r2, r1
	str r0, [sp, #0x48]
	ldr r0, [r6, #0x20]
	ldr r2, [sp, #0x50]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r3, r1
	str r0, [sp, #0x4c]
	ldr r0, [r6, #0x24]
	ldr r3, [sp, #0x54]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r2, r1
	str r0, [sp, #0x50]
	ldr r0, [r6, #0x28]
	ldr r2, [sp, #0x58]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r3, r1
	str r0, [sp, #0x54]
	ldr r0, [r6, #0x30]
	ldr r3, [sp, #0x5c]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r2, r1
	str r0, [sp, #0x58]
	ldr r0, [r6, #0x34]
	ldr r2, [sp, #0x60]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r3, r1
	str r0, [sp, #0x5c]
	ldr r0, [r6, #0x38]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r2, r1
	str r0, [sp, #0x60]
	cmp r11, #0x0
	ldr r1, _020B98C0 ; =0x021D03C0
	ldr r0, [sp, #0xc]
	add r5, r1, r0
	add r8, r8, #0x3
	bne _020B96BC
_020B96AC:
	mov r0, r5
	bl G3X_GetVectorMtx
_020B96B4: ; 0x020B96B4
	cmp r0, #0x0
	bne _020B96AC
_020B96BC:
	ldr r0, [sp, #0x8]
	add r7, r7, #0x1
	cmp r7, r0
	blo _020B92E4
_020B96CC:
	ldr r1, [r5, #0x0]
	ldr r4, [sp, #0x64]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r0, r3, lsr #0xc
	orr r0, r0, r2, lsl #0x14
	adds r0, r4, r0
	str r0, [sp, #0x64]
	ldr r1, [r5, #0x4]
	ldr r4, [sp, #0x68]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r0, r3, lsr #0xc
	orr r0, r0, r2, lsl #0x14
	adds r0, r4, r0
	str r0, [sp, #0x68]
	ldr r1, [r5, #0x8]
	ldr r4, [sp, #0x6c]
	umull r0, r2, r10, r1
	mov r3, r0, lsr #0xc
	mov r0, r1, asr #0x1f
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	orr r3, r3, r2, lsl #0x14
	adds r0, r4, r3
	str r0, [sp, #0x6c]
	ldr r7, [r5, #0xc]
	ldr r12, [sp, #0x70]
	mov r6, r7, asr #0x1f
	umull r11, r8, r10, r7
	mla r8, r10, r6, r8
	mla r8, r9, r7, r8
	mov r6, r11, lsr #0xc
	orr r6, r6, r8, lsl #0x14
	adds r6, r12, r6
	str r6, [sp, #0x70]
	ldr r7, [r5, #0x10]
	ldr r4, [sp, #0x74]
	mov r6, r7, asr #0x1f
	umull r11, r8, r10, r7
	mla r8, r10, r6, r8
	mla r8, r9, r7, r8
	mov r6, r11, lsr #0xc
	orr r6, r6, r8, lsl #0x14
	adds r4, r4, r6
	str r4, [sp, #0x74]
	ldr r6, [r5, #0x14]
	ldr r3, [sp, #0x78]
	mov r4, r6, asr #0x1f
	umull r8, r7, r10, r6
	mla r7, r10, r4, r7
	mla r7, r9, r6, r7
	mov r4, r8, lsr #0xc
	orr r4, r4, r7, lsl #0x14
	adds r3, r3, r4
	str r3, [sp, #0x78]
	ldr r4, [r5, #0x18]
	ldr r2, [sp, #0x7c]
	mov r3, r4, asr #0x1f
	umull r7, r6, r10, r4
	mla r6, r10, r3, r6
	mla r6, r9, r4, r6
	mov r3, r7, lsr #0xc
	orr r3, r3, r6, lsl #0x14
	adds r2, r2, r3
	str r2, [sp, #0x7c]
	ldr r3, [r5, #0x1c]
	ldr r1, [sp, #0x80]
	mov r2, r3, asr #0x1f
	umull r6, r4, r10, r3
	mla r4, r10, r2, r4
	mla r4, r9, r3, r4
	mov r2, r6, lsr #0xc
	orr r2, r2, r4, lsl #0x14
	adds r1, r1, r2
	str r1, [sp, #0x80]
	ldr r2, [r5, #0x20]
	ldr lr, [sp, #0x84]
	mov r1, r2, asr #0x1f
	umull r4, r3, r10, r2
	mla r3, r10, r1, r3
	mla r3, r9, r2, r3
	mov r1, r4, lsr #0xc
	orr r1, r1, r3, lsl #0x14
	adds r1, lr, r1
	add r0, sp, #0x64
	str r1, [sp, #0x84]
	bl G3_LoadMtx43
	ldr r1, _020B98AC ; =0x04000440
	mov r2, #0x1
	add r0, sp, #0x34
	str r2, [r1, #0x0]
	bl G3_LoadMtx43
	ldr r3, _020B98AC ; =0x04000440
	mov r0, #0x0
	str r0, [r3, #0x0]
	ldr r1, _020B98BC ; =0x04000450
	mov r2, #0x1
	mov r0, #0x2
	str r2, [r1, #0x0]
	str r0, [r3, #0x0]
	ldr r0, [sp, #0x0]
	ldr r1, [r0, #0x0]
	ldr r0, _020B98B0 ; =0x0400044C
	ldrb r2, [r1, #0x1]
	mov r1, #0x3
	str r2, [r0, #0x0]
	ldr r0, [sp, #0x0]
	ldr r2, [r0, #0x0]
	ldrb r0, [r2, #0x2]
	add r0, r0, #0x1
	mla r1, r0, r1, r2
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x0]
	add sp, sp, #0x8c
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B98AC: .word 0x04000440
_020B98B0: .word 0x0400044C
_020B98B4: .word 0x04000454
_020B98B8: .word 0x021D0380
_020B98BC: .word 0x04000450
_020B98C0: .word 0x021D03C0

	arm_func_start FUN_020B98C4
FUN_020B98C4: ; 0x020B98C4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xcc
	mov r10, r0
	ldr r2, [r10, #0x8]
	mov r9, r1
	ands r0, r2, #0x200
	mov r7, #0x2
	ldr r6, _020B9C28 ; =0x02106718
	ldr fp, _020B9C2C ; =0x02106724
	ldr r5, _020B9C30 ; =0x021066F4
	beq _020B992C
	cmp r9, #0x40
	beq _020B9900
	cmp r9, #0x60
	bne _020B9904
_020B9900:
	add r7, r7, #0x1
_020B9904:
	cmp r9, #0x20
	beq _020B9914
	cmp r9, #0x60
	bne _020B9918
_020B9914:
	add r7, r7, #0x1
_020B9918:
	ldr r0, [r10, #0x0]
	add sp, sp, #0xcc
	add r0, r0, r7
	str r0, [r10, #0x0]
	ldmia sp!, {r4-r11,pc}
_020B992C:
	cmp r9, #0x40
	beq _020B993C
	cmp r9, #0x60
	bne _020B9974
_020B993C:
	add r7, r7, #0x1
	ands r0, r2, #0x100
	bne _020B9974
	cmp r9, #0x40
	ldreq r0, [r10, #0x0]
	add r1, sp, #0x0
	ldreqb r0, [r0, #0x2]
	mov r2, #0x1
	streq r0, [sp, #0x0]
	ldrne r0, [r10, #0x0]
	ldrneb r0, [r0, #0x3]
	strne r0, [sp, #0x0]
	mov r0, #0x14
	bl FUN_020BB1C0
_020B9974:
	ldr r0, [r10, #0x2c]
	cmp r0, #0x0
	ldrneb r8, [r10, #0x94]
	moveq r8, #0x0
	cmp r8, #0x1
	bne _020B99C0
	ldr r1, [r10, #0x8]
	mov r0, r10
	bic r1, r1, #0x40
	str r1, [r10, #0x8]
	ldr r1, [r10, #0x2c]
	blx r1
	ldr r0, [r10, #0x2c]
	cmp r0, #0x0
	ldrneb r8, [r10, #0x94]
	ldr r0, [r10, #0x8]
	moveq r8, #0x0
	and r1, r0, #0x40
	b _020B99C4
_020B99C0:
	mov r1, #0x0
_020B99C4:
	ldr r0, [r10, #0x8]
	ands r0, r0, #0x100
	bne _020B9BA4
	cmp r1, #0x0
	bne _020B9BA4
	bl FUN_020BB394
	ldr r2, _020B9C34 ; =0x00151110
	ldr r1, _020B9C38 ; =0x04000400
	mov r0, #0x0
	str r2, [r1, #0x0]
	str r0, [r1, #0x0]
	str r0, [r1, #0x0]
	add r4, sp, #0x8
_020B99F8:
	mov r0, r4
	bl G3X_GetClipMtx
_020B9A00: ; 0x020B9A00
	cmp r0, #0x0
	bne _020B99F8
	ldr r0, _020B9C3C ; =0x021CED18
	ldr r1, [r0, #0xfc]
	ands r0, r1, #0x1
	beq _020B9A38
	bl FUN_020B82A4
	add r1, sp, #0x48
	bl MTX_Copy43To44_
	add r0, sp, #0x8
	add r1, sp, #0x48
	mov r2, r0
	bl MTX_Concat44
	b _020B9A5C
_020B9A38:
	ands r0, r1, #0x2
	beq _020B9A5C
	ldr r0, _020B9C40 ; =0x021CED64
	add r1, sp, #0x88
	bl MTX_Copy43To44_
	add r0, sp, #0x8
	add r1, sp, #0x88
	mov r2, r0
	bl MTX_Concat44
_020B9A5C:
	ldr r1, [sp, #0x38]
	add r0, sp, #0x8
	str r1, [r6, #0x0]
	ldr r1, [sp, #0x3c]
	str r1, [r6, #0x4]
	ldr r1, [sp, #0x40]
	str r1, [r6, #0x8]
	bl VEC_Mag
_020B9A7C: ; 0x020B9A7C
	str r0, [r11, #0x0]
	add r0, sp, #0x18
	bl VEC_Mag
	str r0, [r11, #0x4]
	add r0, sp, #0x28
	bl VEC_Mag
	str r0, [r11, #0x8]
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	bne _020B9AB0
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	beq _020B9AD4
_020B9AB0:
	add r0, sp, #0x18
	add r1, r5, #0xc
	bl VEC_Normalize
	ldr r0, [r5, #0x14]
	rsb r0, r0, #0x0
	str r0, [r5, #0x1c]
	ldr r0, [r5, #0x10]
	str r0, [r5, #0x20]
	b _020B9AF4
_020B9AD4:
	add r0, sp, #0x28
	add r1, r5, #0x18
	bl VEC_Normalize
	ldr r0, [r5, #0x1c]
	rsb r0, r0, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0x20]
	str r0, [r5, #0x10]
_020B9AF4:
	ldr r0, _020B9C3C ; =0x021CED18
	ldr r1, [r0, #0xfc]
	ands r0, r1, #0x1
	beq _020B9B48
	ldr r3, _020B9C44 ; =0x00171012
	ldr r1, _020B9C38 ; =0x04000400
	ldr r0, _020B9C48 ; =0x021066EC
	mov r2, #0x8
	str r3, [r1, #0x0]
	bl MIi_CpuSend32
	bl FUN_020B8264
	ldr r1, _020B9C38 ; =0x04000400
	mov r2, #0x30
	bl MIi_CpuSend32
	ldr r2, _020B9C4C ; =0x00001B19
	ldr r1, _020B9C38 ; =0x04000400
	ldr r0, _020B9C30 ; =0x021066F4
	str r2, [r1, #0x0]
	mov r2, #0x3c
	bl MIi_CpuSend32
	b _020B9BA4
_020B9B48:
	ands r0, r1, #0x2
	beq _020B9B94
	ldr r3, _020B9C44 ; =0x00171012
	ldr r1, _020B9C38 ; =0x04000400
	ldr r0, _020B9C48 ; =0x021066EC
	mov r2, #0x8
	str r3, [r1, #0x0]
	bl MIi_CpuSend32
	bl FUN_020B8344
	ldr r1, _020B9C38 ; =0x04000400
	mov r2, #0x30
	bl MIi_CpuSend32
	ldr r2, _020B9C4C ; =0x00001B19
	ldr r1, _020B9C38 ; =0x04000400
	ldr r0, _020B9C30 ; =0x021066F4
	str r2, [r1, #0x0]
	mov r2, #0x3c
	bl MIi_CpuSend32
	b _020B9BA4
_020B9B94:
	ldr r0, _020B9C50 ; =0x021066E8
	ldr r1, _020B9C38 ; =0x04000400
	mov r2, #0x48
	bl MIi_CpuSend32
_020B9BA4:
	cmp r8, #0x3
	movne r0, #0x0
	bne _020B9BD0
	ldr r1, [r10, #0x8]
	mov r0, r10
	bic r1, r1, #0x40
	str r1, [r10, #0x8]
	ldr r1, [r10, #0x2c]
	blx r1
	ldr r0, [r10, #0x8]
	and r0, r0, #0x40
_020B9BD0:
	cmp r9, #0x20
	beq _020B9BE0
	cmp r9, #0x60
	bne _020B9C14
_020B9BE0:
	cmp r0, #0x0
	add r7, r7, #0x1
	bne _020B9C14
	ldr r0, [r10, #0x8]
	ands r0, r0, #0x100
	bne _020B9C14
	ldr r0, [r10, #0x0]
	add r1, sp, #0x4
	ldrb r3, [r0, #0x2]
	mov r0, #0x13
	mov r2, #0x1
	str r3, [sp, #0x4]
	bl FUN_020BB1C0
_020B9C14:
	ldr r0, [r10, #0x0]
	add r0, r0, r7
	str r0, [r10, #0x0]
	add sp, sp, #0xcc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B9C28: .word 0x02106718
_020B9C2C: .word 0x02106724
_020B9C30: .word 0x021066F4
_020B9C34: .word 0x00151110
_020B9C38: .word 0x04000400
_020B9C3C: .word 0x021CED18
_020B9C40: .word 0x021CED64
_020B9C44: .word 0x00171012
_020B9C48: .word 0x021066EC
_020B9C4C: .word 0x00001B19
_020B9C50: .word 0x021066E8

	arm_func_start FUN_020B9C54
FUN_020B9C54: ; 0x020B9C54
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0xc8
	mov r9, r0
	ldr r2, [r9, #0x8]
	mov r8, r1
	ands r0, r2, #0x200
	mov r6, #0x2
	ldr r5, _020B9F58 ; =0x021066D0
	ldr r4, _020B9F5C ; =0x021066DC
	beq _020B9CB8
	cmp r8, #0x40
	beq _020B9C8C
	cmp r8, #0x60
	bne _020B9C90
_020B9C8C:
	add r6, r6, #0x1
_020B9C90:
	cmp r8, #0x20
	beq _020B9CA0
	cmp r8, #0x60
	bne _020B9CA4
_020B9CA0:
	add r6, r6, #0x1
_020B9CA4:
	ldr r0, [r9, #0x0]
	add sp, sp, #0xc8
	add r0, r0, r6
	str r0, [r9, #0x0]
	ldmia sp!, {r4-r10,pc}
_020B9CB8:
	cmp r8, #0x40
	beq _020B9CC8
	cmp r8, #0x60
	bne _020B9D00
_020B9CC8:
	add r6, r6, #0x1
	ands r0, r2, #0x100
	bne _020B9D00
	cmp r8, #0x40
	ldreq r0, [r9, #0x0]
	add r1, sp, #0x0
	ldreqb r0, [r0, #0x2]
	mov r2, #0x1
	streq r0, [sp, #0x0]
	ldrne r0, [r9, #0x0]
	ldrneb r0, [r0, #0x3]
	strne r0, [sp, #0x0]
	mov r0, #0x14
	bl FUN_020BB1C0
_020B9D00:
	ldr r0, [r9, #0x28]
	cmp r0, #0x0
	ldrneb r7, [r9, #0x93]
	moveq r7, #0x0
	cmp r7, #0x1
	bne _020B9D4C
	ldr r1, [r9, #0x8]
	mov r0, r9
	bic r1, r1, #0x40
	str r1, [r9, #0x8]
	ldr r1, [r9, #0x28]
	blx r1
	ldr r0, [r9, #0x28]
	cmp r0, #0x0
	ldrneb r7, [r9, #0x93]
	ldr r0, [r9, #0x8]
	moveq r7, #0x0
	and r1, r0, #0x40
	b _020B9D50
_020B9D4C:
	mov r1, #0x0
_020B9D50:
	ldr r0, [r9, #0x8]
	ands r0, r0, #0x100
	bne _020B9ED4
	cmp r1, #0x0
	bne _020B9ED4
	bl FUN_020BB394
	ldr r2, _020B9F60 ; =0x00151110
	ldr r1, _020B9F64 ; =0x04000400
	mov r0, #0x0
	str r2, [r1, #0x0]
	str r0, [r1, #0x0]
	str r0, [r1, #0x0]
	add r10, sp, #0x8
_020B9D84:
	mov r0, r10
	bl G3X_GetClipMtx
_020B9D8C: ; 0x020B9D8C
	cmp r0, #0x0
	bne _020B9D84
	ldr r0, _020B9F68 ; =0x021CED18
	ldr r1, [r0, #0xfc]
	ands r0, r1, #0x1
	beq _020B9DC4
	bl FUN_020B82A4
	add r1, sp, #0x48
	bl MTX_Copy43To44_
	add r0, sp, #0x8
	add r1, sp, #0x48
	mov r2, r0
	bl MTX_Concat44
	b _020B9DE8
_020B9DC4:
	ands r0, r1, #0x2
	beq _020B9DE8
	ldr r0, _020B9F6C ; =0x021CED64
	add r1, sp, #0x88
	bl MTX_Copy43To44_
	add r0, sp, #0x8
	add r1, sp, #0x88
	mov r2, r0
	bl MTX_Concat44
_020B9DE8:
	ldr r1, [sp, #0x38]
	add r0, sp, #0x8
	str r1, [r5, #0x0]
	ldr r1, [sp, #0x3c]
	str r1, [r5, #0x4]
	ldr r1, [sp, #0x40]
	str r1, [r5, #0x8]
	bl VEC_Mag
_020B9E08: ; 0x020B9E08
	str r0, [r4, #0x0]
	add r0, sp, #0x18
	bl VEC_Mag
	str r0, [r4, #0x4]
	add r0, sp, #0x28
	bl VEC_Mag
	ldr r1, _020B9F68 ; =0x021CED18
	str r0, [r4, #0x8]
	ldr r1, [r1, #0xfc]
	ands r0, r1, #0x1
	beq _020B9E78
	ldr r3, _020B9F70 ; =0x00171012
	ldr r1, _020B9F64 ; =0x04000400
	ldr r0, _020B9F74 ; =0x021066A4
	mov r2, #0x8
	str r3, [r1, #0x0]
	bl MIi_CpuSend32
	bl FUN_020B8264
	ldr r1, _020B9F64 ; =0x04000400
	mov r2, #0x30
	bl MIi_CpuSend32
	ldr r2, _020B9F78 ; =0x00001B19
	ldr r1, _020B9F64 ; =0x04000400
	ldr r0, _020B9F7C ; =0x021066AC
	str r2, [r1, #0x0]
	mov r2, #0x3c
	bl MIi_CpuSend32
	b _020B9ED4
_020B9E78:
	ands r0, r1, #0x2
	beq _020B9EC4
	ldr r3, _020B9F70 ; =0x00171012
	ldr r1, _020B9F64 ; =0x04000400
	ldr r0, _020B9F74 ; =0x021066A4
	mov r2, #0x8
	str r3, [r1, #0x0]
	bl MIi_CpuSend32
	bl FUN_020B8344
	ldr r1, _020B9F64 ; =0x04000400
	mov r2, #0x30
	bl MIi_CpuSend32
	ldr r2, _020B9F78 ; =0x00001B19
	ldr r1, _020B9F64 ; =0x04000400
	ldr r0, _020B9F7C ; =0x021066AC
	str r2, [r1, #0x0]
	mov r2, #0x3c
	bl MIi_CpuSend32
	b _020B9ED4
_020B9EC4:
	ldr r0, _020B9F80 ; =0x021066A0
	ldr r1, _020B9F64 ; =0x04000400
	mov r2, #0x48
	bl MIi_CpuSend32
_020B9ED4:
	cmp r7, #0x3
	movne r0, #0x0
	bne _020B9F00
	ldr r1, [r9, #0x8]
	mov r0, r9
	bic r1, r1, #0x40
	str r1, [r9, #0x8]
	ldr r1, [r9, #0x28]
	blx r1
	ldr r0, [r9, #0x8]
	and r0, r0, #0x40
_020B9F00:
	cmp r8, #0x20
	beq _020B9F10
	cmp r8, #0x60
	bne _020B9F44
_020B9F10:
	cmp r0, #0x0
	add r6, r6, #0x1
	bne _020B9F44
	ldr r0, [r9, #0x8]
	ands r0, r0, #0x100
	bne _020B9F44
	ldr r0, [r9, #0x0]
	add r1, sp, #0x4
	ldrb r3, [r0, #0x2]
	mov r0, #0x13
	mov r2, #0x1
	str r3, [sp, #0x4]
	bl FUN_020BB1C0
_020B9F44:
	ldr r0, [r9, #0x0]
	add r0, r0, r6
	str r0, [r9, #0x0]
	add sp, sp, #0xc8
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020B9F58: .word 0x021066D0
_020B9F5C: .word 0x021066DC
_020B9F60: .word 0x00151110
_020B9F64: .word 0x04000400
_020B9F68: .word 0x021CED18
_020B9F6C: .word 0x021CED64
_020B9F70: .word 0x00171012
_020B9F74: .word 0x021066A4
_020B9F78: .word 0x00001B19
_020B9F7C: .word 0x021066AC
_020B9F80: .word 0x021066A0

	arm_func_start FUN_020B9F84
FUN_020B9F84: ; 0x020B9F84
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r10, r0
	ldr r0, [r10, #0x0]
	mov r9, r1
	ldrb r4, [r0, #0x1]
	mov r7, #0x4
	strb r4, [r10, #0xae]
	ldr r0, [r10, #0x8]
	orr r0, r0, #0x10
	str r0, [r10, #0x8]
	ldr r1, [r10, #0x8]
	ands r0, r1, #0x400
	beq _020BA01C
	cmp r9, #0x40
	beq _020B9FCC
	cmp r9, #0x60
	bne _020B9FD0
_020B9FCC:
	add r7, r7, #0x1
_020B9FD0:
	cmp r9, #0x20
	beq _020B9FE0
	cmp r9, #0x60
	bne _020BA008
_020B9FE0:
	add r7, r7, #0x1
	ands r0, r1, #0x100
	bne _020BA008
	ldr r0, [r10, #0x0]
	add r1, sp, #0x8
	ldrb r3, [r0, #0x4]
	mov r0, #0x14
	mov r2, #0x1
	str r3, [sp, #0x8]
	bl FUN_020BB1C0
_020BA008:
	ldr r0, [r10, #0x0]
	add sp, sp, #0x14
	add r0, r0, r7
	str r0, [r10, #0x0]
	ldmia sp!, {r4-r11,pc}
_020BA01C:
	cmp r9, #0x40
	beq _020BA02C
	cmp r9, #0x60
	bne _020BA068
_020BA02C:
	cmp r9, #0x40
	ldreq r0, [r10, #0x0]
	add r7, r7, #0x1
	ldreqb r0, [r0, #0x4]
	streq r0, [sp, #0xc]
	ldrne r0, [r10, #0x0]
	ldrneb r0, [r0, #0x5]
	strne r0, [sp, #0xc]
	ldr r0, [r10, #0x8]
	ands r0, r0, #0x100
	bne _020BA068
	add r1, sp, #0xc
	mov r0, #0x14
	mov r2, #0x1
	bl FUN_020BB1C0
_020BA068:
	add r0, r10, #0x12c
	str r0, [r10, #0xb4]
	ldr r0, [r10, #0x24]
	cmp r0, #0x0
	ldrneb r8, [r10, #0x92]
	moveq r8, #0x0
	cmp r8, #0x1
	bne _020BA0BC
	ldr r1, [r10, #0x8]
	mov r0, r10
	bic r1, r1, #0x40
	str r1, [r10, #0x8]
	ldr r1, [r10, #0x24]
	blx r1
	ldr r0, [r10, #0x24]
	cmp r0, #0x0
	ldrneb r8, [r10, #0x92]
	ldr r0, [r10, #0x8]
	moveq r8, #0x0
	and r0, r0, #0x40
	b _020BA0C0
_020BA0BC:
	mov r0, #0x0
_020BA0C0:
	cmp r0, #0x0
	bne _020BA2CC
	ldr r0, [r10, #0x4]
	ldr r1, [r0, #0x34]
	cmp r1, #0x0
	beq _020BA0F4
	mov r0, #0x58
	mla r6, r4, r0, r1
	ldr r0, [r10, #0x8]
	ands r0, r0, #0x80
	moveq r0, #0x1
	movne r0, #0x0
	b _020BA0FC
_020BA0F4:
	add r6, r10, #0x12c
	mov r0, #0x0
_020BA0FC:
	cmp r0, #0x0
	bne _020BA2C8
	mov r0, #0x0
	str r0, [r6, #0x0]
	ldr r0, [r10, #0x4]
	ldr r1, [r0, #0x10]
	cmp r1, #0x0
	beq _020BA134
	ldr r3, [r0, #0x14]
	mov r0, r6
	mov r2, r4
	blx r3
	cmp r0, #0x0
	bne _020BA2C8
_020BA134:
	ldr r2, [r10, #0xd4]
	ldrh r0, [r2, #0x6]
	ldrh r1, [r2, r0]
	add r0, r2, r0
	mla r0, r1, r4, r0
	ldr r1, [r0, #0x4]
	ldrh r0, [r2, r1]
	add r4, r2, r1
	add r5, r4, #0x4
	ands r0, r0, #0x1
	ldrne r0, [r6, #0x0]
	orrne r0, r0, #0x4
	strne r0, [r6, #0x0]
	bne _020BA188
	ldr r0, [r5, #0x0]
	str r0, [r6, #0x4c]
	ldr r0, [r5, #0x4]
	str r0, [r6, #0x50]
	ldr r0, [r5, #0x8]
	add r5, r5, #0xc
	str r0, [r6, #0x54]
_020BA188:
	ldrh r1, [r4, #0x0]
	ands r0, r1, #0x2
	ldrne r0, [r6, #0x0]
	orrne r0, r0, #0x2
	strne r0, [r6, #0x0]
	bne _020BA2B0
	ands r0, r1, #0x8
	beq _020BA264
	and r1, r1, #0xf0
	mov r11, r1, asr #0x4
	ldrsh r1, [r5, #0x0]
	add r0, r6, #0x28
	str r1, [sp, #0x0]
	ldrsh r1, [r5, #0x2]
	str r1, [sp, #0x4]
	blx MI_Zero36B
	ldrh r0, [r4, #0x0]
	add r1, r6, r11, lsl #0x2
	add r5, r5, #0x4
	ands r0, r0, #0x100
	movne r0, #0x1000
	rsbne r2, r0, #0x0
	moveq r2, #0x1000
	str r2, [r1, #0x28]
	ldr r0, _020BA3B4 ; =0x020FF9F0
	ldr r1, _020BA3B8 ; =0x020FF9F1
	ldrb r0, [r0, r11, lsl #0x2]
	add r2, r6, r0, lsl #0x2
	ldr r0, [sp, #0x0]
	str r0, [r2, #0x28]
	ldrb r0, [r1, r11, lsl #0x2]
	add r1, r6, r0, lsl #0x2
	ldr r0, [sp, #0x4]
	str r0, [r1, #0x28]
	ldrh r0, [r4, #0x0]
	ands r0, r0, #0x200
	ldrne r0, [sp, #0x4]
	rsbne r0, r0, #0x0
	strne r0, [sp, #0x4]
	ldr r0, _020BA3BC ; =0x020FF9F2
	ldrb r0, [r0, r11, lsl #0x2]
	add r1, r6, r0, lsl #0x2
	ldr r0, [sp, #0x4]
	str r0, [r1, #0x28]
	ldrh r0, [r4, #0x0]
	ands r0, r0, #0x400
	ldrne r0, [sp, #0x0]
	rsbne r0, r0, #0x0
	strne r0, [sp, #0x0]
	ldr r0, _020BA3C0 ; =0x020FF9F3
	ldrb r0, [r0, r11, lsl #0x2]
	add r1, r6, r0, lsl #0x2
	ldr r0, [sp, #0x0]
	str r0, [r1, #0x28]
	b _020BA2B0
_020BA264:
	ldrsh r0, [r4, #0x2]
	str r0, [r6, #0x28]
	ldrsh r0, [r5, #0x0]
	str r0, [r6, #0x2c]
	ldrsh r0, [r5, #0x2]
	str r0, [r6, #0x30]
	ldrsh r0, [r5, #0x4]
	str r0, [r6, #0x34]
	ldrsh r0, [r5, #0x6]
	str r0, [r6, #0x38]
	ldrsh r0, [r5, #0x8]
	str r0, [r6, #0x3c]
	ldrsh r0, [r5, #0xa]
	str r0, [r6, #0x40]
	ldrsh r0, [r5, #0xc]
	str r0, [r6, #0x44]
	ldrsh r0, [r5, #0xe]
	add r5, r5, #0x10
	str r0, [r6, #0x48]
_020BA2B0:
	ldrh r3, [r4, #0x0]
	ldr r2, [r10, #0x0]
	ldr r4, [r10, #0xe8]
	mov r0, r6
	mov r1, r5
	blx r4
_020BA2C8:
	str r6, [r10, #0xb4]
_020BA2CC:
	cmp r8, #0x2
	bne _020BA308
	ldr r1, [r10, #0x8]
	mov r0, r10
	bic r1, r1, #0x40
	str r1, [r10, #0x8]
	ldr r1, [r10, #0x24]
	blx r1
	ldr r0, [r10, #0x24]
	cmp r0, #0x0
	ldrneb r8, [r10, #0x92]
	ldr r0, [r10, #0x8]
	moveq r8, #0x0
	and r0, r0, #0x40
	b _020BA30C
_020BA308:
	mov r0, #0x0
_020BA30C:
	cmp r0, #0x0
	bne _020BA32C
	ldr r0, [r10, #0x8]
	ands r0, r0, #0x100
	bne _020BA32C
	ldr r0, [r10, #0xb4]
	ldr r1, [r10, #0xec]
	blx r1
_020BA32C:
	mov r0, #0x0
	str r0, [r10, #0xb4]
	cmp r8, #0x3
	bne _020BA35C
	ldr r1, [r10, #0x8]
	mov r0, r10
	bic r1, r1, #0x40
	str r1, [r10, #0x8]
	ldr r1, [r10, #0x24]
	blx r1
	ldr r0, [r10, #0x8]
	and r0, r0, #0x40
_020BA35C:
	cmp r9, #0x20
	beq _020BA36C
	cmp r9, #0x60
	bne _020BA3A0
_020BA36C:
	cmp r0, #0x0
	add r7, r7, #0x1
	bne _020BA3A0
	ldr r0, [r10, #0x8]
	ands r0, r0, #0x100
	bne _020BA3A0
	ldr r0, [r10, #0x0]
	add r1, sp, #0x10
	ldrb r3, [r0, #0x4]
	mov r0, #0x13
	mov r2, #0x1
	str r3, [sp, #0x10]
	bl FUN_020BB1C0
_020BA3A0:
	ldr r0, [r10, #0x0]
	add r0, r0, r7
	str r0, [r10, #0x0]
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020BA3B4: .word 0x020FF9F0
_020BA3B8: .word 0x020FF9F1
_020BA3BC: .word 0x020FF9F2
_020BA3C0: .word 0x020FF9F3

	arm_func_start FUN_020BA3C4
FUN_020BA3C4: ; 0x020BA3C4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldr r3, [r4, #0x8]
	ands r2, r3, #0x200
	bne _020BA420
	ands r2, r3, #0x1
	beq _020BA420
	ands r2, r3, #0x2
	bne _020BA420
	ldr r5, [r4, #0xdc]
	ldr r3, [r4, #0x0]
	ldrh r2, [r5, #0x6]
	ldrb r3, [r3, #0x1]
	ldr ip, _020BA434 ; =0x02106650
	ldrh lr, [r5, r2]
	add r2, r5, r2
	mla r2, lr, r3, r2
	ldr r2, [r2, #0x4]
	ldrh lr, [r5, r2]
	add r2, r5, r2
	ldr r12, [r12, lr, lsl #0x2]
	blx r12
_020BA420:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x2
	str r0, [r4, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020BA434: .word 0x02106650

	arm_func_start FUN_020BA438
FUN_020BA438: ; 0x020BA438
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldr r0, [r6, #0x20]
	mov r5, r2
	cmp r0, #0x0
	ldrneb r4, [r6, #0x91]
	moveq r4, #0x0
	cmp r4, #0x1
	bne _020BA490
	ldr r1, [r6, #0x8]
	mov r0, r6
	bic r1, r1, #0x40
	str r1, [r6, #0x8]
	ldr r1, [r6, #0x20]
	blx r1
	ldr r0, [r6, #0x20]
	cmp r0, #0x0
	ldrneb r4, [r6, #0x91]
	ldr r0, [r6, #0x8]
	moveq r4, #0x0
	and r0, r0, #0x40
	b _020BA494
_020BA490:
	mov r0, #0x0
_020BA494:
	cmp r0, #0x0
	bne _020BA4B8
	ldr r0, [r6, #0x8]
	ands r0, r0, #0x100
	bne _020BA4B8
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0xc]
	add r0, r5, r0
	bl FUN_020BB2B0
_020BA4B8:
	cmp r4, #0x2
	bne _020BA4E8
	ldr r1, [r6, #0x8]
	mov r0, r6
	bic r1, r1, #0x40
	str r1, [r6, #0x8]
	ldr r1, [r6, #0x20]
	blx r1
	ldr r0, [r6, #0x20]
	cmp r0, #0x0
	ldrneb r4, [r6, #0x91]
	moveq r4, #0x0
_020BA4E8:
	cmp r4, #0x3
	ldmneia sp!, {r4-r6,pc}
_020BA4F0: ; 0x020BA4F0
	ldr r1, [r6, #0x8]
	mov r0, r6
	bic r1, r1, #0x40
	str r1, [r6, #0x8]
	ldr r1, [r6, #0x20]
	blx r1
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BA50C
FUN_020BA50C: ; 0x020BA50C
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	ldr r5, [r4, #0x8]
	ands r0, r5, #0x200
	bne _020BA578
	ldr r2, [r4, #0x0]
	ands r0, r5, #0x1
	ldrb r3, [r2, #0x1]
	bne _020BA544
	ands r0, r5, #0x8
	beq _020BA544
	ldrb r0, [r4, #0xad]
	cmp r3, r0
	beq _020BA578
_020BA544:
	ldr r6, [r4, #0xd8]
	ldr ip, _020BA588 ; =0x02106640
	ldrh r2, [r6, #0xa]
	add r5, r6, #0x4
	mov r0, r4
	ldrh lr, [r5, r2]
	add r2, r5, r2
	mla r2, lr, r3, r2
	ldr r2, [r2, #0x4]
	ldrh lr, [r6, r2]
	add r2, r6, r2
	ldr r12, [r12, lr, lsl #0x2]
	blx r12
_020BA578:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x2
	str r0, [r4, #0x0]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020BA588: .word 0x02106640

	arm_func_start FUN_020BA58C
FUN_020BA58C: ; 0x020BA58C
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x20
	mov r8, r0
	mov r6, r3
	strb r6, [r8, #0xad]
	ldr r3, [r8, #0x8]
	add r0, r8, #0xf4
	orr r3, r3, #0x8
	str r3, [r8, #0x8]
	str r0, [r8, #0xb0]
	ldr r0, [r8, #0x1c]
	mov r4, r1
	cmp r0, #0x0
	ldrneb r5, [r8, #0x90]
	mov r7, r2
	moveq r5, #0x0
	cmp r5, #0x1
	bne _020BA608
	ldr r1, [r8, #0x8]
	mov r0, r8
	bic r1, r1, #0x40
	str r1, [r8, #0x8]
	ldr r1, [r8, #0x1c]
	blx r1
	ldr r0, [r8, #0x1c]
	cmp r0, #0x0
	ldrneb r5, [r8, #0x90]
	ldr r0, [r8, #0x8]
	moveq r5, #0x0
	and r0, r0, #0x40
	b _020BA60C
_020BA608:
	mov r0, #0x0
_020BA60C:
	cmp r0, #0x0
	bne _020BA8C0
	ldr r0, [r8, #0x4]
	ldr r0, [r0, #0x38]
	cmp r0, #0x0
	beq _020BA638
	ldr r1, [r8, #0x8]
	ands r1, r1, #0x80
	moveq r1, #0x38
	mlaeq r4, r6, r1, r0
	beq _020BA8BC
_020BA638:
	cmp r4, #0x20
	beq _020BA648
	cmp r4, #0x40
	bne _020BA684
_020BA648:
	mov r1, r6, lsr #0x5
	add r1, r8, r1, lsl #0x2
	and r2, r6, #0x1f
	mov r3, #0x1
	mov r2, r3, lsl r2
	ldr r1, [r1, #0xbc]
	ands r1, r2, r1
	beq _020BA684
	cmp r0, #0x0
	movne r1, #0x38
	mlane r4, r6, r1, r0
	ldreq r1, _020BA9D8 ; =0x021CEF80
	moveq r0, #0x38
	mlaeq r4, r6, r0, r1
	b _020BA8BC
_020BA684:
	cmp r0, #0x0
	beq _020BA6BC
	add r4, r8, #0xbc
	mov r3, r6, lsr #0x5
	ldr r2, [r4, r3, lsl #0x2]
	and r0, r6, #0x1f
	mov r1, #0x1
	orr r0, r2, r1, lsl r0
	str r0, [r4, r3, lsl #0x2]
	ldr r1, [r8, #0x4]
	mov r0, #0x38
	ldr r1, [r1, #0x38]
	mla r4, r6, r0, r1
	b _020BA6F0
_020BA6BC:
	cmp r4, #0x40
	addne r4, r8, #0xf4
	bne _020BA6F0
	add lr, r8, #0xbc
	mov r12, r6, lsr #0x5
	ldr r1, _020BA9D8 ; =0x021CEF80
	ldr r4, [lr, r12, lsl #0x2]
	mov r0, #0x38
	and r2, r6, #0x1f
	mov r3, #0x1
	orr r2, r4, r3, lsl r2
	mla r4, r6, r0, r1
	str r2, [lr, r12, lsl #0x2]
_020BA6F0:
	mov r0, #0x0
	str r0, [r4, #0x0]
	ldr r3, [r8, #0xd8]
	ldrh r0, [r3, #0xa]
	add r2, r3, #0x4
	ldrh r1, [r2, r0]
	add r0, r2, r0
	mla r0, r1, r6, r0
	ldr r0, [r0, #0x4]
	ldr r1, _020BA9DC ; =0x021CED18
	add r0, r3, r0
	ldrh r0, [r0, #0x1e]
	ands r0, r0, #0x20
	ldrne r0, [r4, #0x0]
	orrne r0, r0, #0x20
	strne r0, [r4, #0x0]
	ldrh r2, [r7, #0x1e]
	ldr r0, _020BA9E0 ; =0x020FF9D0
	ldr r12, [r1, #0x94]
	mov r2, r2, asr #0x6
	and r2, r2, #0x7
	ldr lr, [r0, r2, lsl #0x2]
	ldr r2, [r7, #0x4]
	mvn r3, lr
	and r3, r12, r3
	and r2, r2, lr
	orr r2, r3, r2
	str r2, [r4, #0x4]
	ldrh r12, [r7, #0x1e]
	ldr r3, [r1, #0x98]
	ldr r2, [r7, #0x8]
	mov r12, r12, asr #0x9
	and r12, r12, #0x7
	ldr r12, [r0, r12, lsl #0x2]
	mvn r0, r12
	and r3, r3, r0
	and r0, r2, r12
	orr r0, r3, r0
	str r0, [r4, #0x8]
	ldr r3, [r7, #0x10]
	ldr r0, [r7, #0xc]
	ldr r2, [r1, #0x9c]
	mvn r1, r3
	and r1, r2, r1
	and r0, r0, r3
	orr r0, r1, r0
	str r0, [r4, #0xc]
	ldr r0, [r7, #0x14]
	str r0, [r4, #0x10]
	ldrh r0, [r7, #0x1c]
	str r0, [r4, #0x14]
	ldrh r1, [r7, #0x1e]
	ands r0, r1, #0x1
	beq _020BA850
	ands r1, r1, #0x2
	ldrne r1, [r4, #0x0]
	add r0, r7, #0x2c
	orrne r1, r1, #0x1
	strne r1, [r4, #0x0]
	bne _020BA7F4
	ldr r1, [r0, #0x0]
	str r1, [r4, #0x18]
	ldr r1, [r0, #0x4]
	add r0, r0, #0x8
	str r1, [r4, #0x1c]
_020BA7F4:
	ldrh r1, [r7, #0x1e]
	ands r1, r1, #0x4
	ldrne r1, [r4, #0x0]
	orrne r1, r1, #0x2
	strne r1, [r4, #0x0]
	bne _020BA820
	ldrsh r1, [r0, #0x0]
	strh r1, [r4, #0x20]
	ldrsh r1, [r0, #0x2]
	add r0, r0, #0x4
	strh r1, [r4, #0x22]
_020BA820:
	ldrh r1, [r7, #0x1e]
	ands r1, r1, #0x8
	ldreq r1, [r0, #0x0]
	streq r1, [r4, #0x24]
	ldreq r0, [r0, #0x4]
	streq r0, [r4, #0x28]
	ldrne r0, [r4, #0x0]
	orrne r0, r0, #0x4
	strne r0, [r4, #0x0]
	ldr r0, [r4, #0x0]
	orr r0, r0, #0x8
	str r0, [r4, #0x0]
_020BA850:
	ldr r0, [r8, #0x4]
	ldr r1, [r0, #0x8]
	cmp r1, #0x0
	beq _020BA890
	mov r2, r6, lsr #0x5
	add r2, r0, r2, lsl #0x2
	and r3, r6, #0x1f
	mov r12, #0x1
	mov r3, r12, lsl r3
	ldr r2, [r2, #0x3c]
	ands r2, r3, r2
	beq _020BA890
	ldr r3, [r0, #0xc]
	mov r0, r4
	mov r2, r6
	blx r3
_020BA890:
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x18
	beq _020BA8BC
	ldrh r0, [r7, #0x20]
	strh r0, [r4, #0x2c]
	ldrh r0, [r7, #0x22]
	strh r0, [r4, #0x2e]
	ldr r0, [r7, #0x24]
	str r0, [r4, #0x30]
	ldr r0, [r7, #0x28]
	str r0, [r4, #0x34]
_020BA8BC:
	str r4, [r8, #0xb0]
_020BA8C0:
	cmp r5, #0x2
	bne _020BA8FC
	ldr r1, [r8, #0x8]
	mov r0, r8
	bic r1, r1, #0x40
	str r1, [r8, #0x8]
	ldr r1, [r8, #0x1c]
	blx r1
	ldr r0, [r8, #0x1c]
	cmp r0, #0x0
	ldrneb r5, [r8, #0x90]
	ldr r0, [r8, #0x8]
	moveq r5, #0x0
	and r0, r0, #0x40
	b _020BA900
_020BA8FC:
	mov r0, #0x0
_020BA900:
	cmp r0, #0x0
	bne _020BA9AC
	ldr r4, [r8, #0xb0]
	ldr r1, [r4, #0xc]
	ands r0, r1, #0x1f0000
	beq _020BA9A0
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x20
	bicne r0, r1, #0x1f0000
	strne r0, [r4, #0xc]
	ldr r0, [r8, #0x8]
	bic r0, r0, #0x2
	str r0, [r8, #0x8]
	ldr r0, [r8, #0x8]
	ands r0, r0, #0x100
	bne _020BA9AC
	ldr r0, _020BA9E4 ; =0x00293130
	ldr r3, _020BA9E8 ; =0x00002B2A
	str r0, [sp, #0x0]
	ldr r2, [r4, #0x4]
	add r1, sp, #0x4
	str r2, [sp, #0x4]
	ldr r6, [r4, #0x8]
	mov r2, #0x6
	str r6, [sp, #0x8]
	ldr r6, [r4, #0xc]
	str r6, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r3, [r4, #0x10]
	str r3, [sp, #0x14]
	ldr r3, [r4, #0x14]
	str r3, [sp, #0x18]
	bl FUN_020BB1C0
_020BA984: ; 0x020BA984
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x18
	beq _020BA9AC
	ldr r1, [r8, #0xf0]
	mov r0, r4
	blx r1
	b _020BA9AC
_020BA9A0:
	ldr r0, [r8, #0x8]
	orr r0, r0, #0x2
	str r0, [r8, #0x8]
_020BA9AC:
	cmp r5, #0x3
	addne sp, sp, #0x20
	ldmneia sp!, {r4-r8,pc}
_020BA9B8: ; 0x020BA9B8
	ldr r1, [r8, #0x8]
	mov r0, r8
	bic r1, r1, #0x40
	str r1, [r8, #0x8]
	ldr r1, [r8, #0x1c]
	blx r1
	add sp, sp, #0x20
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020BA9D8: .word 0x021CEF80
_020BA9DC: .word 0x021CED18
_020BA9E0: .word 0x020FF9D0
_020BA9E4: .word 0x00293130
_020BA9E8: .word 0x00002B2A

	arm_func_start FUN_020BA9EC
FUN_020BA9EC: ; 0x020BA9EC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r1, [r5, #0x8]
	ands r0, r1, #0x200
	bne _020BAAAC
	ands r0, r1, #0x1
	beq _020BAAAC
	ldr r0, [r5, #0x18]
	cmp r0, #0x0
	ldrneb r4, [r5, #0x8f]
	moveq r4, #0x0
	cmp r4, #0x1
	bne _020BAA58
	ldr r1, [r5, #0x8]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r5, #0x8]
	ldr r1, [r5, #0x18]
	blx r1
	ldr r0, [r5, #0x18]
	cmp r0, #0x0
	ldrneb r4, [r5, #0x8f]
	ldr r0, [r5, #0x8]
	moveq r4, #0x0
	and r0, r0, #0x40
	b _020BAA5C
_020BAA58:
	mov r0, #0x0
_020BAA5C:
	cmp r0, #0x0
	bne _020BAA8C
	ldr r0, [r5, #0x0]
	ldrb r0, [r0, #0x1]
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x8]
	ands r0, r0, #0x100
	bne _020BAA8C
	add r1, sp, #0x0
	mov r0, #0x14
	mov r2, #0x1
	bl FUN_020BB1C0
_020BAA8C:
	cmp r4, #0x3
	bne _020BAAAC
	ldr r1, [r5, #0x8]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r5, #0x8]
	ldr r1, [r5, #0x18]
	blx r1
_020BAAAC:
	ldr r0, [r5, #0x0]
	add r0, r0, #0x2
	str r0, [r5, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020BAAC0
FUN_020BAAC0: ; 0x020BAAC0
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldr r0, [r6, #0x8]
	ands r0, r0, #0x200
	bne _020BAC38
	ldr r1, [r6, #0x0]
	add r0, r6, #0x184
	ldrb r1, [r1, #0x1]
	strb r1, [r6, #0xac]
	ldr r1, [r6, #0x8]
	ldrb r4, [r6, #0xac]
	orr r1, r1, #0x4
	str r1, [r6, #0x8]
	str r0, [r6, #0xb8]
	ldr r0, [r6, #0x14]
	cmp r0, #0x0
	ldrneb r5, [r6, #0x8e]
	moveq r5, #0x0
	cmp r5, #0x1
	bne _020BAB44
	ldr r1, [r6, #0x8]
	mov r0, r6
	bic r1, r1, #0x40
	str r1, [r6, #0x8]
	ldr r1, [r6, #0x14]
	blx r1
	ldr r0, [r6, #0x14]
	cmp r0, #0x0
	ldrneb r5, [r6, #0x8e]
	ldr r0, [r6, #0x8]
	moveq r5, #0x0
	and r0, r0, #0x40
	b _020BAB48
_020BAB44:
	mov r0, #0x0
_020BAB48:
	cmp r0, #0x0
	bne _020BABAC
	ldr r12, [r6, #0x4]
	ldr r1, [r12, #0x18]
	cmp r1, #0x0
	beq _020BAB98
	mov r0, r4, lsr #0x5
	add r0, r12, r0, lsl #0x2
	and r2, r4, #0x1f
	mov r3, #0x1
	mov r2, r3, lsl r2
	ldr r0, [r0, #0x4c]
	ands r0, r2, r0
	beq _020BAB98
	ldr r0, [r6, #0xb8]
	ldr r3, [r12, #0x1c]
	mov r2, r4
	blx r3
	cmp r0, #0x0
	bne _020BABAC
_020BAB98:
	ldr r1, [r6, #0x0]
	ldr r0, [r6, #0xb8]
	ldrb r1, [r1, #0x2]
	and r1, r1, #0x1
	str r1, [r0, #0x0]
_020BABAC:
	cmp r5, #0x2
	bne _020BABE8
	ldr r1, [r6, #0x8]
	mov r0, r6
	bic r1, r1, #0x40
	str r1, [r6, #0x8]
	ldr r1, [r6, #0x14]
	blx r1
	ldr r0, [r6, #0x14]
	cmp r0, #0x0
	ldrneb r5, [r6, #0x8e]
	ldr r0, [r6, #0x8]
	moveq r5, #0x0
	and r0, r0, #0x40
	b _020BABEC
_020BABE8:
	mov r0, #0x0
_020BABEC:
	cmp r0, #0x0
	bne _020BAC18
	ldr r0, [r6, #0xb8]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldrne r0, [r6, #0x8]
	orrne r0, r0, #0x1
	strne r0, [r6, #0x8]
	ldreq r0, [r6, #0x8]
	biceq r0, r0, #0x1
	streq r0, [r6, #0x8]
_020BAC18:
	cmp r5, #0x3
	bne _020BAC38
	ldr r1, [r6, #0x8]
	mov r0, r6
	bic r1, r1, #0x40
	str r1, [r6, #0x8]
	ldr r1, [r6, #0x14]
	blx r1
_020BAC38:
	ldr r0, [r6, #0x0]
	add r0, r0, #0x3
	str r0, [r6, #0x0]
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BAC48
FUN_020BAC48: ; 0x020BAC48
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r1, [r4, #0x10]
	cmp r1, #0x0
	beq _020BAC60
	blx r1
_020BAC60:
	ldr r0, [r4, #0x8]
	orr r0, r0, #0x20
	str r0, [r4, #0x8]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020BAC70
FUN_020BAC70: ; 0x020BAC70
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	beq _020BAC88
	blx r1
_020BAC88:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020BAC98
FUN_020BAC98: ; 0x020BAC98
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x188
	mov r4, r0
	ldr r0, [r4, #0x0]
	and r0, r0, #0x10
	cmp r0, #0x10
	bne _020BAD2C
	add r1, r4, #0x3c
	mov r0, #0x0
	mov r2, #0x8
	bl MIi_CpuClear32
	add r1, r4, #0x44
	mov r0, #0x0
	mov r2, #0x8
	bl MIi_CpuClear32
	add r1, r4, #0x4c
	mov r0, #0x0
	mov r2, #0x8
	bl MIi_CpuClear32
	ldr r1, [r4, #0x8]
	cmp r1, #0x0
	beq _020BACF8
	add r0, r4, #0x3c
	bl FUN_020BAD74
_020BACF8:
	ldr r1, [r4, #0x10]
	cmp r1, #0x0
	beq _020BAD0C
	add r0, r4, #0x44
	bl FUN_020BAD74
_020BAD0C:
	ldr r1, [r4, #0x18]
	cmp r1, #0x0
	beq _020BAD20
	add r0, r4, #0x4c
	bl FUN_020BAD74
_020BAD20:
	ldr r0, [r4, #0x0]
	bic r0, r0, #0x10
	str r0, [r4, #0x0]
_020BAD2C:
	ldr r2, _020BAD70 ; =0x021CEF7C
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	beq _020BAD4C
	mov r1, r4
	bl FUN_020BADE4
	add sp, sp, #0x188
	ldmia sp!, {r4,pc}
_020BAD4C:
	add r0, sp, #0x0
	mov r1, r4
	str r0, [r2, #0x0]
	bl FUN_020BADE4
	ldr r0, _020BAD70 ; =0x021CEF7C
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x188
	ldmia sp!, {r4,pc}
	.balign 4
_020BAD70: .word 0x021CEF7C

	arm_func_start FUN_020BAD74
FUN_020BAD74:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
_020BAD88: ; 0x020BAD88
	mov r3, #0x1
	mov r4, #0x0
_020BAD90:
	ldrb r2, [r1, #0x19]
	mov r5, r4
	cmp r2, #0x0
	ble _020BADD0
_020BADA0:
	add r2, r1, r5, lsl #0x1
	ldrh r2, [r2, #0x1a]
	ands r2, r2, #0x100
	movne lr, r5, asr #0x5
	andne r2, r5, #0x1f
	ldrne r12, [r0, lr, lsl #0x2]
	add r5, r5, #0x1
	orrne r2, r12, r3, lsl r2
	strne r2, [r0, lr, lsl #0x2]
	ldrb r2, [r1, #0x19]
	cmp r5, r2
	blt _020BADA0
_020BADD0:
	ldr r1, [r1, #0x10]
	cmp r1, #0x0
	bne _020BAD90
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020BADE4
FUN_020BADE4: ; 0x020BADE4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	mov r1, r5
	mov r0, #0x0
	mov r2, #0x188
	bl MIi_CpuClearFast
	mov r0, #0x1
	str r0, [r5, #0xc4]
	str r0, [r5, #0x8]
	ldr r0, [r4, #0x30]
	ldr r2, _020BAF60 ; =0x02106614
	cmp r0, #0x0
	strne r0, [r5, #0x0]
	ldreq r1, [r4, #0x4]
	ldreq r0, [r1, #0x4]
	addeq r0, r1, r0
	streq r0, [r5, #0x0]
	str r4, [r5, #0x4]
	ldr r0, [r4, #0x4]
	ldr r1, _020BAF64 ; =0x02106608
	add r0, r0, #0x40
	str r0, [r5, #0xd4]
	ldr r12, [r4, #0x4]
	ldr r0, _020BAF68 ; =0x02106620
	ldr r3, [r12, #0x8]
	add r3, r12, r3
	str r3, [r5, #0xd8]
	ldr r12, [r4, #0x4]
	ldr r3, [r12, #0xc]
	add r3, r12, r3
	str r3, [r5, #0xdc]
	ldr r3, [r4, #0x4]
	ldrb r3, [r3, #0x15]
	ldr r2, [r2, r3, lsl #0x2]
	str r2, [r5, #0xe8]
	ldr r2, [r4, #0x4]
	ldrb r2, [r2, #0x15]
	ldr r1, [r1, r2, lsl #0x2]
	str r1, [r5, #0xec]
	ldr r1, [r4, #0x4]
	ldrb r1, [r1, #0x16]
	ldr r0, [r0, r1, lsl #0x2]
	str r0, [r5, #0xf0]
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x1c]
	str r0, [r5, #0xe0]
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x20]
	str r0, [r5, #0xe4]
	ldr r1, [r4, #0x20]
	cmp r1, #0x0
	beq _020BAEE0
	ldrb r0, [r4, #0x24]
	cmp r0, #0x20
	bhs _020BAEE0
	add r0, r5, r0, lsl #0x2
	str r1, [r0, #0xc]
	ldrb r0, [r4, #0x24]
	ldrb r1, [r4, #0x25]
	add r0, r5, r0
	strb r1, [r0, #0x8c]
_020BAEE0:
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x1
	ldrne r0, [r5, #0x8]
	orrne r0, r0, #0x80
	strne r0, [r5, #0x8]
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x2
	ldrne r0, [r5, #0x8]
	orrne r0, r0, #0x100
	strne r0, [r5, #0x8]
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x4
	ldrne r0, [r5, #0x8]
	orrne r0, r0, #0x200
	strne r0, [r5, #0x8]
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x8
	ldrne r0, [r5, #0x8]
	orrne r0, r0, #0x400
	strne r0, [r5, #0x8]
	ldr r1, [r4, #0x28]
	cmp r1, #0x0
	beq _020BAF44
	mov r0, r5
	blx r1
_020BAF44:
	mov r0, r5
	bl FUN_020BAF6C
_020BAF4C: ; 0x020BAF4C
	ldr r0, [r4, #0x0]
	bic r0, r0, #0x1
	str r0, [r4, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020BAF60: .word 0x02106614
_020BAF64: .word 0x02106608
_020BAF68: .word 0x02106620

	arm_func_start FUN_020BAF6C
FUN_020BAF6C:
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	ldr r6, _020BAFB4 ; =0x02106730
	add r4, r5, #0x8
_020BAF7C:
	ldr r1, [r4, #0x0]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r4, #0x0]
	ldr r1, [r5, #0x0]
	ldrb r3, [r1, #0x0]
	and r1, r3, #0x1f
	ldr r2, [r6, r1, lsl #0x2]
	and r1, r3, #0xe0
	blx r2
	ldr r0, [r5, #0x8]
	ands r0, r0, #0x20
	beq _020BAF7C
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020BAFB4: .word 0x02106730

	arm_func_start FUN_020BAFB8
FUN_020BAFB8: ; 0x020BAFB8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x6c
	mov r6, r0
	ldr r12, [r6, #0x1c]
	mov r4, r1
	mov r5, r2
	mov r7, r3
	cmp r12, #0x1000
	beq _020BAFF8
	add r1, sp, #0x54
	mov r0, #0x1b
	mov r2, #0x3
	str r12, [sp, #0x54]
	str r12, [sp, #0x58]
	str r12, [sp, #0x5c]
	bl FUN_020BB1C0
_020BAFF8:
	cmp r7, #0x0
	beq _020BB150
	ldr r0, [r6, #0x8]
	add r3, r6, r0
	ldrh r0, [r3, #0xa]
	add r2, r3, #0x4
	ldrh r1, [r2, r0]
	add r0, r2, r0
	mla r0, r1, r4, r0
	ldr r0, [r0, #0x4]
	add r4, r3, r0
	ldr r0, [r4, #0xc]
	ands r0, r0, #0x1f0000
	addeq sp, sp, #0x6c
	ldmeqia sp!, {r4-r7,pc}
_020BB034: ; 0x020BB034
	ldr r0, _020BB1B4 ; =0x00293130
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x4]
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x8]
	str r0, [sp, #0x8]
	ldr r1, [r4, #0xc]
	str r1, [sp, #0xc]
	ldrh r0, [r4, #0x1e]
	ands r0, r0, #0x20
	bicne r0, r1, #0x1f0000
	ldr r1, _020BB1B8 ; =0x00002B2A
	strne r0, [sp, #0xc]
	str r1, [sp, #0x10]
	ldr r2, [r4, #0x14]
	ldr r0, [sp, #0x0]
	str r2, [sp, #0x14]
	ldrh r3, [r4, #0x1c]
	add r1, sp, #0x4
	mov r2, #0x6
	str r3, [sp, #0x18]
	bl FUN_020BB1C0
	ldrh r0, [r4, #0x1e]
	ands r0, r0, #0x1
	beq _020BB150
	ldrb r12, [r6, #0x16]
	mov r3, #0x8
	ldr r1, _020BB1BC ; =0x02106620
	str r3, [sp, #0x1c]
	ldrh r2, [r4, #0x20]
	add r0, r4, #0x2c
	ldr r1, [r1, r12, lsl #0x2]
	strh r2, [sp, #0x48]
	ldrh r2, [r4, #0x22]
	strh r2, [sp, #0x4a]
	ldr r2, [r4, #0x24]
	str r2, [sp, #0x4c]
	ldr r2, [r4, #0x28]
	str r2, [sp, #0x50]
	ldrh r2, [r4, #0x1e]
	ands r2, r2, #0x2
	orrne r2, r3, #0x1
	strne r2, [sp, #0x1c]
	bne _020BB0F8
	ldr r2, [r0, #0x0]
	str r2, [sp, #0x34]
	ldr r2, [r0, #0x4]
	add r0, r0, #0x8
	str r2, [sp, #0x38]
_020BB0F8:
	ldrh r2, [r4, #0x1e]
	ands r2, r2, #0x4
	ldrne r2, [sp, #0x1c]
	orrne r2, r2, #0x2
	strne r2, [sp, #0x1c]
	bne _020BB124
	ldrsh r2, [r0, #0x0]
	strh r2, [sp, #0x3c]
	ldrsh r2, [r0, #0x2]
	add r0, r0, #0x4
	strh r2, [sp, #0x3e]
_020BB124:
	ldrh r2, [r4, #0x1e]
	ands r2, r2, #0x8
	ldreq r2, [r0, #0x0]
	streq r2, [sp, #0x40]
	ldreq r0, [r0, #0x4]
	streq r0, [sp, #0x44]
	ldrne r0, [sp, #0x1c]
	orrne r0, r0, #0x4
	strne r0, [sp, #0x1c]
	add r0, sp, #0x1c
	blx r1
_020BB150:
	ldr r0, [r6, #0xc]
	add r2, r6, r0
	ldrh r0, [r2, #0x6]
	ldrh r1, [r2, r0]
	add r0, r2, r0
	mla r0, r1, r5, r0
	ldr r0, [r0, #0x4]
	add r2, r2, r0
	ldr r0, [r2, #0x8]
	ldr r1, [r2, #0xc]
	add r0, r2, r0
	bl FUN_020BB2B0
	ldr r3, [r6, #0x20]
	cmp r3, #0x1000
	addeq sp, sp, #0x6c
	ldmeqia sp!, {r4-r7,pc}
_020BB190: ; 0x020BB190
	add r1, sp, #0x60
	mov r0, #0x1b
	mov r2, #0x3
	str r3, [sp, #0x60]
	str r3, [sp, #0x64]
	str r3, [sp, #0x68]
	bl FUN_020BB1C0
	add sp, sp, #0x6c
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020BB1B4: .word 0x00293130
_020BB1B8: .word 0x00002B2A
_020BB1BC: .word 0x02106620

	arm_func_start FUN_020BB1C0
FUN_020BB1C0:
	stmdb sp!, {r4-r6,lr}
	ldr r3, _020BB2A4 ; =0x021D1C80
	mov r6, r0
	ldr r12, [r3, #0x0]
	mov r5, r1
	mov r4, r2
	cmp r12, #0x0
	beq _020BB278
	ldr r0, _020BB2A8 ; =0x021D1C84
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020BB24C
	ldr r2, [r12, #0x0]
	add r0, r2, #0x1
	add r1, r0, r4
	cmp r1, #0xc0
	bhi _020BB24C
	str r0, [r12, #0x0]
	ldr r0, [r3, #0x0]
	cmp r4, #0x0
	add r0, r0, r2, lsl #0x2
	str r6, [r0, #0x4]
	ldmeqia sp!, {r4-r6,pc}
_020BB21C: ; 0x020BB21C
	ldr r2, [r3, #0x0]
	mov r0, r5
	ldr r1, [r2], #0x4
	add r1, r2, r1, lsl #0x2
	mov r2, r4, lsl #0x2
	bl MIi_CpuCopyFast
	ldr r0, _020BB2A4 ; =0x021D1C80
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x0]
	add r0, r0, r4
	str r0, [r1, #0x0]
	ldmia sp!, {r4-r6,pc}
_020BB24C:
	ldr r0, [r12, #0x0]
	cmp r0, #0x0
	beq _020BB260
	bl FUN_020BB394
	b _020BB28C
_020BB260:
	ldr r0, _020BB2A8 ; =0x021D1C84
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020BB28C
	bl FUN_020BB37C
	b _020BB28C
_020BB278:
	ldr r0, _020BB2A8 ; =0x021D1C84
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020BB28C
	bl FUN_020BB37C
_020BB28C:
	ldr r1, _020BB2AC ; =0x04000400
	mov r0, r5
	mov r2, r4, lsl #0x2
	str r6, [r1, #0x0]
	bl MIi_CpuSend32
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020BB2A4: .word 0x021D1C80
_020BB2A8: .word 0x021D1C84
_020BB2AC: .word 0x04000400

	arm_func_start FUN_020BB2B0
FUN_020BB2B0: ; 0x020BB2B0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r5, r0
	cmp r4, #0x100
	blo _020BB2DC
	ldr r1, _020BB360 ; =0x02106814
	mvn r0, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, r0
	bne _020BB2F8
_020BB2DC:
	mov r2, r4, lsr #0x2
	ldr r0, [r5, #0x0]
	add r1, r5, #0x4
	sub r2, r2, #0x1
	bl FUN_020BB1C0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020BB2F8:
	bl FUN_020BB394
	ldr r0, _020BB364 ; =0x021D1C88
	ldr r1, _020BB368 ; =0x021D1C84
	ldr r0, [r0, #0x0]
	mov r2, #0x1
	str r2, [r1, #0x0]
	cmp r0, #0x0
	beq _020BB33C
	ldr r0, _020BB360 ; =0x02106814
	str r1, [sp, #0x0]
	ldr r0, [r0, #0x0]
	ldr r3, _020BB36C ; =FUN_020BB370
	mov r1, r5
	mov r2, r4
	bl MI_SendGXCommandAsyncFast
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020BB33C:
	ldr r0, _020BB360 ; =0x02106814
	str r1, [sp, #0x0]
	ldr r0, [r0, #0x0]
	ldr r3, _020BB36C ; =FUN_020BB370
	mov r1, r5
	mov r2, r4
	bl MI_SendGXCommandAsync
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020BB360: .word 0x02106814
_020BB364: .word 0x021D1C88
_020BB368: .word 0x021D1C84
_020BB36C: .word FUN_020BB370

	arm_func_start FUN_020BB370
FUN_020BB370: ; 0x020BB370
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr

	arm_func_start FUN_020BB37C
FUN_020BB37C: ; 0x020BB37C
	ldr r0, _020BB390 ; =0x021D1C84
_020BB380:
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	bne _020BB380
	bx lr
	.balign 4
_020BB390: .word 0x021D1C84

	arm_func_start FUN_020BB394
FUN_020BB394: ; 0x020BB394
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020BB3FC ; =0x021D1C84
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020BB3B0
	bl FUN_020BB37C
_020BB3B0:
	ldr r0, _020BB400 ; =0x021D1C80
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r1, _020BB404 ; =0x04000400
	add r0, r0, #0x4
	mov r2, r2, lsl #0x2
	bl MIi_CpuSend32
	ldr r0, _020BB400 ; =0x021D1C80
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020BB3FC: .word 0x021D1C84
_020BB400: .word 0x021D1C80
_020BB404: .word 0x04000400

	arm_func_start FUN_020BB408
FUN_020BB408: ; 0x020BB408
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x1c
	mov r5, r1
	mov r4, r2
	ldr r6, _020BB594 ; =0x021CED20
	ldr r1, _020BB598 ; =0x021CED64
	add r2, sp, #0x10
	bl MTX_MultVec43
	ldr r1, [sp, #0x14]
	ldr r0, [r6, #0x1c]
	ldr r2, [sp, #0x10]
	smull r8, r7, r1, r0
	ldr r0, [r6, #0xc]
	ldr r3, [sp, #0x18]
	smlal r8, r7, r2, r0
	ldr r1, [r6, #0x2c]
	ldr r0, [r6, #0x3c]
	smlal r8, r7, r3, r1
	mov r1, r8, lsr #0xc
	orr r1, r1, r7, lsl #0x14
	add r0, r1, r0
	bl FX_InvAsync
	ldr r2, [sp, #0x14]
	ldr r1, [r6, #0x10]
	ldr r0, [r6, #0x14]
	smull lr, r8, r2, r1
	smull r12, r9, r2, r0
	ldr r1, [sp, #0x10]
	ldr r3, [r6, #0x0]
	ldr r0, [sp, #0x18]
	smlal lr, r8, r1, r3
	ldr r7, [r6, #0x20]
	ldr r2, [r6, #0x30]
	smlal lr, r8, r0, r7
	mov r3, lr, lsr #0xc
	orr r3, r3, r8, lsl #0x14
	add r7, r3, r2
	ldr r3, [r6, #0x4]
	ldr r8, [r6, #0x24]
	smlal r12, r9, r1, r3
	smlal r12, r9, r0, r8
	mov r0, r12, lsr #0xc
	ldr r2, [r6, #0x34]
	orr r0, r0, r9, lsl #0x14
	add r6, r0, r2
	bl FX_GetDivResultFx64c
	mov r2, r7, asr #0x1f
	umull r9, lr, r0, r7
	mla lr, r0, r2, lr
	mov r3, #0x80000000
	mla lr, r1, r7, lr
	adds r9, r9, r3
	adc r2, lr, #0x0
	add r2, r2, #0x1000
	add r2, r2, r2, lsr #0x1f
	mov r7, r2, asr #0x1
	umull lr, r2, r0, r6
	mov r12, r6, asr #0x1f
	mla r2, r0, r12, r2
	mla r2, r1, r6, r2
	adds r3, lr, r3
	adc r0, r2, #0x0
	add r0, r0, #0x1000
	add r0, r0, r0, lsr #0x1f
	mov r8, #0x0
	mov r6, r0, asr #0x1
	cmp r7, #0x0
	blt _020BB530
	cmp r6, #0x0
	blt _020BB530
	cmp r7, #0x1000
	bgt _020BB530
	cmp r6, #0x1000
	ble _020BB534
_020BB530:
	mvn r8, #0x0
_020BB534:
	add r0, sp, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x8
	add r3, sp, #0xc
	bl FUN_020B8200
	ldr r2, [sp, #0x0]
	ldr r0, [sp, #0x8]
	ldr r12, [sp, #0xc]
	sub r0, r0, r2
	mul r0, r7, r0
	add r1, r0, #0x800
	ldr r3, [sp, #0x4]
	add r1, r2, r1, asr #0xc
	sub r0, r12, r3
	mul r0, r6, r0
	str r1, [r5, #0x0]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x800
	rsb r1, r1, #0xbf
	sub r1, r1, r0, asr #0xc
	mov r0, r8
	str r1, [r4, #0x0]
	add sp, sp, #0x1c
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020BB594: .word 0x021CED20
_020BB598: .word 0x021CED64

	arm_func_start FUN_020BB59C
FUN_020BB59C: ; 0x020BB59C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r1, [r5, #0x0]
	ldr r0, _020BB7C8 ; =0x30415642
	cmp r1, r0
	bhi _020BB5F4
	cmp r1, r0
	bhs _020BB7B0
	ldr r0, _020BB7CC ; =0x30414D42
	cmp r1, r0
	bhi _020BB5E4
	cmp r1, r0
	bhs _020BB7B0
	ldr r0, _020BB7D0 ; =0x30414342
	cmp r1, r0
	beq _020BB7B0
	b _020BB7BC
_020BB5E4:
	ldr r0, _020BB7D4 ; =0x30415442
	cmp r1, r0
	beq _020BB7B0
	b _020BB7BC
_020BB5F4:
	ldr r0, _020BB7D8 ; =0x30505442
	cmp r1, r0
	bhi _020BB618
	cmp r1, r0
	bhs _020BB7B0
	ldr r0, _020BB7DC ; =0x30444D42
	cmp r1, r0
	beq _020BB624
	b _020BB7BC
_020BB618:
	ldr r0, _020BB7E0 ; =0x30585442
	cmp r1, r0
	bne _020BB7BC
_020BB624:
	mov r11, #0x1
	mov r0, r5
	mov r9, r11
	mov r8, r11
	bl FUN_020BC0FC
	movs r4, r0
	beq _020BB77C
	bl FUN_020B7E1C
	mov r7, r0
	mov r0, r4
	bl FUN_020B7E10
	mov r6, r0
	mov r0, r4
	bl FUN_020B7CE4
	mov r10, r0
	cmp r7, #0x0
	beq _020BB68C
	ldr r0, _020BB7E4 ; =0x021064B8
	mov r1, #0x0
	ldr r3, [r0, #0x0]
	mov r0, r7
	mov r2, r1
	blx r3
	movs r7, r0
	moveq r11, #0x0
	b _020BB690
_020BB68C:
	mov r7, #0x0
_020BB690:
	cmp r6, #0x0
	beq _020BB6BC
	ldr r1, _020BB7E4 ; =0x021064B8
	mov r0, r6
	ldr r3, [r1, #0x0]
	mov r1, #0x1
	mov r2, #0x0
	blx r3
	movs r6, r0
	moveq r9, #0x0
	b _020BB6C0
_020BB6BC:
	mov r6, #0x0
_020BB6C0:
	cmp r10, #0x0
	beq _020BB6F0
	ldr r1, _020BB7E8 ; =0x021064C0
	ldrh r2, [r4, #0x20]
	ldr r3, [r1, #0x0]
	mov r0, r10
	and r1, r2, #0x8000
	mov r2, #0x0
	blx r3
	movs r10, r0
	moveq r8, #0x0
	b _020BB6F4
_020BB6F0:
	mov r10, #0x0
_020BB6F4:
	cmp r11, #0x0
	beq _020BB70C
	cmp r9, #0x0
	beq _020BB70C
	cmp r8, #0x0
	bne _020BB748
_020BB70C:
	ldr r1, _020BB7EC ; =0x021064C4
	mov r0, r10
	ldr r1, [r1, #0x0]
	blx r1
	ldr r1, _020BB7F0 ; =0x021064BC
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	ldr r1, _020BB7F0 ; =0x021064BC
	mov r0, r7
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_020BB748:
	mov r0, r4
	mov r1, r7
	mov r2, r6
	bl FUN_020B7DFC
	mov r0, r4
	mov r1, r10
	bl FUN_020B7CDC
	mov r0, r4
	mov r1, #0x1
	bl FUN_020B7D28
	mov r0, r4
	mov r1, #0x1
	bl FUN_020B7C78
_020BB77C:
	ldr r1, [r5, #0x0]
	ldr r0, _020BB7DC ; =0x30444D42
	cmp r1, r0
	bne _020BB7A4
	mov r0, r5
	bl FUN_020BC13C
_020BB794: ; 0x020BB794
	cmp r4, #0x0
	beq _020BB7A4
	mov r1, r4
	bl FUN_020B7790
_020BB7A4:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_020BB7B0:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_020BB7BC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020BB7C8: .word 0x30415642
_020BB7CC: .word 0x30414D42
_020BB7D0: .word 0x30414342
_020BB7D4: .word 0x30415442
_020BB7D8: .word 0x30505442
_020BB7DC: .word 0x30444D42
_020BB7E0: .word 0x30585442
_020BB7E4: .word 0x021064B8
_020BB7E8: .word 0x021064C0
_020BB7EC: .word 0x021064C4
_020BB7F0: .word 0x021064BC

	arm_func_start FUN_020BB7F4
FUN_020BB7F4: ; 0x020BB7F4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl G3X_Init
	bl FUN_020B84D8
	ldr r1, _020BB820 ; =0x04000600
	ldr r0, [r1, #0x0]
	bic r0, r0, #0xc0000000
	orr r0, r0, #0x80000000
	str r0, [r1, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020BB820: .word 0x04000600

	arm_func_start FUN_020BB824
FUN_020BB824: ; 0x020BB824
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x40
	mov r6, r0
	mov r5, r1
	bl FUN_020BB394
	ldr r0, _020BB8B4 ; =0x04000440
	mov r2, #0x0
	ldr r1, _020BB8B8 ; =0x04000444
	str r2, [r0, #0x0]
	ldr r0, _020BB8BC ; =0x04000454
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	cmp r6, #0x0
	beq _020BB87C
	add r4, sp, #0x0
_020BB860:
	mov r0, r4
	bl G3X_GetClipMtx
_020BB868: ; 0x020BB868
	cmp r0, #0x0
	bne _020BB860
	add r0, sp, #0x0
	mov r1, r6
	bl MTX_Copy44To43_
_020BB87C:
	cmp r5, #0x0
	beq _020BB894
_020BB884:
	mov r0, r5
	bl G3X_GetVectorMtx
_020BB88C: ; 0x020BB88C
	cmp r0, #0x0
	bne _020BB884
_020BB894:
	ldr r1, _020BB8C0 ; =0x04000448
	mov r2, #0x1
	ldr r0, _020BB8B4 ; =0x04000440
	str r2, [r1, #0x0]
	mov r1, #0x2
	str r1, [r0, #0x0]
	add sp, sp, #0x40
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020BB8B4: .word 0x04000440
_020BB8B8: .word 0x04000444
_020BB8BC: .word 0x04000454
_020BB8C0: .word 0x04000448

	arm_func_start thunk_FUN_020ae84c
thunk_FUN_020ae84c: ; 0x020BB8C4
	ldr ip, _020BB8CC ; =FUN_020AE84C
	bx r12
	.balign 4
_020BB8CC: .word FUN_020AE84C

	arm_func_start FUN_020BB8D0
FUN_020BB8D0: ; 0x020BB8D0
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, r1
	mov r1, r2
	bl FUN_020B81B0
	mov r1, r0
	mov r0, r4
	bl FUN_020AE868
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020BB8F4
FUN_020BB8F4: ; 0x020BB8F4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BB910:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_020BBC74
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BB910
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BB934
FUN_020BB934: ; 0x020BB934
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BB950:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_020BBCB8
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BB950
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BB974
FUN_020BB974: ; 0x020BB974
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BB990:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_020BBCFC
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BB990
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BB9B4
FUN_020BB9B4: ; 0x020BB9B4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BB9D0:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_020BBD40
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BB9D0
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BB9F4
FUN_020BB9F4: ; 0x020BB9F4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBA10:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_020BBD84
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBA10
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BBA34
FUN_020BBA34: ; 0x020BBA34
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBA50:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_020BBDC8
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBA50
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BBA74
FUN_020BBA74: ; 0x020BBA74
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBA90:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_020BBE0C
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBA90
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BBAB4
FUN_020BBAB4: ; 0x020BBAB4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBAD0:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_020BBE50
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBAD0
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BBAF4
FUN_020BBAF4: ; 0x020BBAF4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBB10:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_020BBE94
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBB10
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BBB34
FUN_020BBB34: ; 0x020BBB34
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBB50:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_020BBED8
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBB50
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BBB74
FUN_020BBB74: ; 0x020BBB74
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBB90:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_020BBF1C
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBB90
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BBBB4
FUN_020BBBB4: ; 0x020BBBB4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBBD0:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_020BBF60
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBBD0
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BBBF4
FUN_020BBBF4: ; 0x020BBBF4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBC10:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_020BBFA4
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBC10
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BBC34
FUN_020BBC34: ; 0x020BBC34
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrb r0, [r6, #0x18]
	mov r5, r1
	mov r4, #0x0
	cmp r0, #0x0
	ldmlsia sp!, {r4-r6,pc}
_020BBC50:
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl FUN_020BBFE8
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	cmp r4, r0
	blo _020BBC50
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BBC74
FUN_020BBC74: ; 0x020BBC74
	ldr r3, [r0, #0x8]
	cmp r2, #0x0
	add r12, r0, r3
	ldrh r0, [r12, #0xa]
	add r3, r12, #0x4
	ldrh r2, [r3, r0]
	add r0, r3, r0
	mla r0, r2, r1, r0
	ldr r0, [r0, #0x4]
	add r1, r12, r0
	ldrne r0, [r1, #0xc]
	orrne r0, r0, #0x800
	strne r0, [r1, #0xc]
	ldreq r0, [r1, #0xc]
	biceq r0, r0, #0x800
	streq r0, [r1, #0xc]
	bx lr

	arm_func_start FUN_020BBCB8
FUN_020BBCB8: ; 0x020BBCB8
	ldr r3, [r0, #0x8]
	cmp r2, #0x0
	add r12, r0, r3
	ldrh r0, [r12, #0xa]
	add r3, r12, #0x4
	ldrh r2, [r3, r0]
	add r0, r3, r0
	mla r0, r2, r1, r0
	ldr r0, [r0, #0x4]
	add r1, r12, r0
	ldrne r0, [r1, #0xc]
	orrne r0, r0, #0x1000
	strne r0, [r1, #0xc]
	ldreq r0, [r1, #0xc]
	biceq r0, r0, #0x1000
	streq r0, [r1, #0xc]
	bx lr

	arm_func_start FUN_020BBCFC
FUN_020BBCFC: ; 0x020BBCFC
	ldr r3, [r0, #0x8]
	cmp r2, #0x0
	add r12, r0, r3
	ldrh r0, [r12, #0xa]
	add r3, r12, #0x4
	ldrh r2, [r3, r0]
	add r0, r3, r0
	mla r0, r2, r1, r0
	ldr r0, [r0, #0x4]
	add r1, r12, r0
	ldrne r0, [r1, #0xc]
	orrne r0, r0, #0x2000
	strne r0, [r1, #0xc]
	ldreq r0, [r1, #0xc]
	biceq r0, r0, #0x2000
	streq r0, [r1, #0xc]
	bx lr

	arm_func_start FUN_020BBD40
FUN_020BBD40: ; 0x020BBD40
	ldr r3, [r0, #0x8]
	cmp r2, #0x0
	add r12, r0, r3
	ldrh r0, [r12, #0xa]
	add r3, r12, #0x4
	ldrh r2, [r3, r0]
	add r0, r3, r0
	mla r0, r2, r1, r0
	ldr r0, [r0, #0x4]
	add r1, r12, r0
	ldrne r0, [r1, #0xc]
	orrne r0, r0, #0x4000
	strne r0, [r1, #0xc]
	ldreq r0, [r1, #0xc]
	biceq r0, r0, #0x4000
	streq r0, [r1, #0xc]
	bx lr

	arm_func_start FUN_020BBD84
FUN_020BBD84: ; 0x020BBD84
	ldr r3, [r0, #0x8]
	cmp r2, #0x0
	add r12, r0, r3
	ldrh r0, [r12, #0xa]
	add r3, r12, #0x4
	ldrh r2, [r3, r0]
	add r0, r3, r0
	mla r0, r2, r1, r0
	ldr r0, [r0, #0x4]
	add r1, r12, r0
	ldrne r0, [r1, #0xc]
	orrne r0, r0, #0x8000
	strne r0, [r1, #0xc]
	ldreq r0, [r1, #0xc]
	biceq r0, r0, #0x8000
	streq r0, [r1, #0xc]
	bx lr

	arm_func_start FUN_020BBDC8
FUN_020BBDC8: ; 0x020BBDC8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r0, #0x8]
	add lr, r0, r3
	ldrh r0, [lr, #0xa]
	add r12, lr, #0x4
	ldrh r3, [r12, r0]
	add r0, r12, r0
	mla r0, r3, r1, r0
	ldr r0, [r0, #0x4]
	add r1, lr, r0
	ldr r0, [r1, #0xc]
	bic r0, r0, #0x1f0000
	orr r0, r0, r2, lsl #0x10
	str r0, [r1, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020BBE0C
FUN_020BBE0C: ; 0x020BBE0C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r0, #0x8]
	add lr, r0, r3
	ldrh r0, [lr, #0xa]
	add r12, lr, #0x4
	ldrh r3, [r12, r0]
	add r0, r12, r0
	mla r0, r3, r1, r0
	ldr r0, [r0, #0x4]
	add r1, lr, r0
	ldr r0, [r1, #0xc]
	bic r0, r0, #0x3f000000
	orr r0, r0, r2, lsl #0x18
	str r0, [r1, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020BBE50
FUN_020BBE50: ; 0x020BBE50
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r0, #0x8]
	add lr, r0, r3
	ldrh r0, [lr, #0xa]
	add r12, lr, #0x4
	ldrh r3, [r12, r0]
	add r0, r12, r0
	mla r0, r3, r1, r0
	ldr r0, [r0, #0x4]
	add r1, lr, r0
	ldr r0, [r1, #0xc]
	bic r0, r0, #0xc0
	orr r0, r0, r2, lsl #0x6
	str r0, [r1, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020BBE94
FUN_020BBE94: ; 0x020BBE94
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r0, #0x8]
	add lr, r0, r3
	ldrh r0, [lr, #0xa]
	add r12, lr, #0x4
	ldrh r3, [r12, r0]
	add r0, r12, r0
	mla r0, r3, r1, r0
	ldr r0, [r0, #0x4]
	add r1, lr, r0
	ldr r0, [r1, #0xc]
	bic r0, r0, #0x30
	orr r0, r0, r2, lsl #0x4
	str r0, [r1, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020BBED8
FUN_020BBED8: ; 0x020BBED8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r0, #0x8]
	add lr, r0, r3
	ldrh r0, [lr, #0xa]
	add r12, lr, #0x4
	ldrh r3, [r12, r0]
	add r0, r12, r0
	mla r0, r3, r1, r0
	ldr r0, [r0, #0x4]
	add r1, lr, r0
	ldr r0, [r1, #0xc]
	bic r0, r0, #0xf
	orr r0, r0, r2
	str r0, [r1, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020BBF1C
FUN_020BBF1C: ; 0x020BBF1C
	stmdb sp!, {r4,lr}
	ldr r12, [r0, #0x8]
	ldr r3, _020BBF5C ; =0x8000FFFF
	add r4, r0, r12
	ldrh r0, [r4, #0xa]
	add lr, r4, #0x4
	ldrh r12, [lr, r0]
	add r0, lr, r0
	mla r0, r12, r1, r0
	ldr r0, [r0, #0x4]
	add r1, r4, r0
	ldr r0, [r1, #0x8]
	and r0, r0, r3
	orr r0, r0, r2, lsl #0x10
	str r0, [r1, #0x8]
	ldmia sp!, {r4,pc}
	.balign 4
_020BBF5C: .word 0x8000FFFF

	arm_func_start FUN_020BBF60
FUN_020BBF60: ; 0x020BBF60
	stmdb sp!, {r4,lr}
	ldr r12, [r0, #0x8]
	mov r3, #0x8000
	add r4, r0, r12
	ldrh r12, [r4, #0xa]
	add lr, r4, #0x4
	rsb r0, r3, #0x0
	ldrh r3, [lr, r12]
	add r12, lr, r12
	mla r1, r3, r1, r12
	ldr r1, [r1, #0x4]
	add r3, r4, r1
	ldr r1, [r3, #0x8]
	and r0, r1, r0
	orr r0, r0, r2
	str r0, [r3, #0x8]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020BBFA4
FUN_020BBFA4: ; 0x020BBFA4
	stmdb sp!, {r4,lr}
	ldr r12, [r0, #0x8]
	ldr r3, _020BBFE4 ; =0x8000FFFF
	add r4, r0, r12
	ldrh r0, [r4, #0xa]
	add lr, r4, #0x4
	ldrh r12, [lr, r0]
	add r0, lr, r0
	mla r0, r12, r1, r0
	ldr r0, [r0, #0x4]
	add r1, r4, r0
	ldr r0, [r1, #0x4]
	and r0, r0, r3
	orr r0, r0, r2, lsl #0x10
	str r0, [r1, #0x4]
	ldmia sp!, {r4,pc}
	.balign 4
_020BBFE4: .word 0x8000FFFF

	arm_func_start FUN_020BBFE8
FUN_020BBFE8: ; 0x020BBFE8
	stmdb sp!, {r4,lr}
	ldr r12, [r0, #0x8]
	mov r3, #0x8000
	add r4, r0, r12
	ldrh r12, [r4, #0xa]
	add lr, r4, #0x4
	rsb r0, r3, #0x0
	ldrh r3, [lr, r12]
	add r12, lr, r12
	mla r1, r3, r1, r12
	ldr r1, [r1, #0x4]
	add r3, r4, r1
	ldr r1, [r3, #0x4]
	and r0, r1, r0
	orr r0, r0, r2
	str r0, [r3, #0x4]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020BC02C
FUN_020BC02C: ; 0x020BC02C
	stmdb sp!, {r4-r6,lr}
	ldrb r4, [r0, #0x18]
	ldr r3, [r0, #0x8]
	mov lr, #0x0
	cmp r4, #0x0
	add r12, r0, r3
	ldmlsia sp!, {r4-r6,pc}
_020BC048: ; 0x020BC048
	mvn r3, r2
	add r0, r12, #0x4
_020BC050:
	ldrh r5, [r12, #0xa]
	cmp r1, #0x0
	ldrh r6, [r0, r5]
	add r5, r0, r5
	mla r5, r6, lr, r5
	ldr r5, [r5, #0x4]
	add lr, lr, #0x1
	add r6, r12, r5
	ldrne r5, [r6, #0x10]
	orrne r5, r5, r2
	strne r5, [r6, #0x10]
	ldreq r5, [r6, #0x10]
	andeq r5, r5, r3
	streq r5, [r6, #0x10]
	cmp lr, r4
	blo _020BC050
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BC094
FUN_020BC094: ; 0x020BC094
	stmdb sp!, {r4-r6,lr}
	ldrb r4, [r0, #0x18]
	ldr r3, [r0, #0x8]
	mov lr, #0x0
	cmp r4, #0x0
	add r12, r0, r3
	ldmlsia sp!, {r4-r6,pc}
_020BC0B0: ; 0x020BC0B0
	mvn r3, r2
	add r0, r12, #0x4
_020BC0B8:
	ldrh r5, [r12, #0xa]
	cmp r1, #0x0
	ldrh r6, [r0, r5]
	add r5, r0, r5
	mla r5, r6, lr, r5
	ldr r5, [r5, #0x4]
	add lr, lr, #0x1
	add r6, r12, r5
	ldrneh r5, [r6, #0x1e]
	orrne r5, r5, r2
	strneh r5, [r6, #0x1e]
	ldreqh r5, [r6, #0x1e]
	andeq r5, r5, r3
	streqh r5, [r6, #0x1e]
	cmp lr, r4
	blo _020BC0B8
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BC0FC
FUN_020BC0FC: ; 0x020BC0FC
	ldrh r2, [r0, #0xc]
	ldrh r1, [r0, #0xe]
	add r3, r0, r2
	cmp r1, #0x1
	bne _020BC12C
	ldr r2, [r0, #0x0]
	ldr r1, _020BC138 ; =0x30585442
	cmp r2, r1
	ldreq r1, [r3, #0x0]
	addeq r0, r0, r1
	movne r0, #0x0
	bx lr
_020BC12C:
	ldr r1, [r3, #0x4]
	add r0, r0, r1
	bx lr
	.balign 4
_020BC138: .word 0x30585442

	arm_func_start FUN_020BC13C
FUN_020BC13C:
	ldrh r1, [r0, #0xc]
	ldr r1, [r0, r1]
	add r0, r0, r1
	bx lr

	arm_func_start FUN_020BC14C
FUN_020BC14C:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldrb r2, [r0, #0x1]
	cmp r2, #0x10
	bhs _020BC1E4
	cmp r2, #0x0
	ldr lr, [r1, #0x0]
	ldr r12, [r1, #0x4]
	ldr r3, [r1, #0x8]
	ldr r2, [r1, #0xc]
	mov r4, #0x0
	bls _020BC294
	ldrh r5, [r0, #0x6]
	mov r1, r4
	add r6, r0, r5
	ldrh r5, [r6, #0x2]
	add r6, r6, r5
_020BC190:
	ldr r5, [r6, r1]
	add r7, r6, r1
	cmp r5, lr
	bne _020BC1CC
	ldr r5, [r7, #0x4]
	cmp r5, r12
	bne _020BC1CC
	ldr r5, [r7, #0x8]
	cmp r5, r3
	bne _020BC1CC
	ldr r5, [r7, #0xc]
	cmp r5, r2
	addeq sp, sp, #0x4
	moveq r0, r4
	ldmeqia sp!, {r4-r7,pc}
_020BC1CC:
	ldrb r5, [r0, #0x1]
	add r4, r4, #0x1
	add r1, r1, #0x10
	cmp r4, r5
	blo _020BC190
	b _020BC294
_020BC1E4:
	add r3, r0, #0x8
	ldrb r2, [r3, #0x1]
	cmp r2, #0x0
	beq _020BC294
	ldrb r5, [r3, r2, lsl #0x2]
	ldrb r4, [r3, #0x0]
	add r2, r3, r2, lsl #0x2
	cmp r4, r5
	bls _020BC238
_020BC208:
	mov r4, r5, asr #0x5
	ldr r12, [r1, r4, lsl #0x2]
	and r4, r5, #0x1f
	mov r4, r12, lsr r4
	and r4, r4, #0x1
	add r4, r2, r4
	ldrb r12, [r4, #0x1]
	ldrb r4, [r2, #0x0]
	ldrb r5, [r3, r12, lsl #0x2]
	add r2, r3, r12, lsl #0x2
	cmp r4, r5
	bhi _020BC208
_020BC238:
	ldrh r4, [r0, #0x6]
	ldr r3, [r1, #0x0]
	add r12, r0, r4
	ldrh r4, [r12, #0x2]
	ldrb r0, [r2, #0x3]
	add r4, r12, r4
	ldr r2, [r4, r0, lsl #0x4]
	add r4, r4, r0, lsl #0x4
	cmp r2, r3
	bne _020BC294
	ldr r3, [r4, #0x4]
	ldr r2, [r1, #0x4]
	cmp r3, r2
	bne _020BC294
	ldr r3, [r4, #0x8]
	ldr r2, [r1, #0x8]
	cmp r3, r2
	bne _020BC294
	ldr r2, [r4, #0xc]
	ldr r1, [r1, #0xc]
	cmp r2, r1
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
_020BC294:
	mvn r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020BC2A0
FUN_020BC2A0: ; 0x020BC2A0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldrb r2, [r0, #0x1]
	cmp r2, #0x10
	bhs _020BC34C
	cmp r2, #0x0
	ldr lr, [r1, #0x0]
	ldr r12, [r1, #0x4]
	ldr r3, [r1, #0x8]
	ldr r2, [r1, #0xc]
	mov r4, #0x0
	bls _020BC404
	ldrh r5, [r0, #0x6]
	mov r1, r4
	add r6, r0, r5
	ldrh r5, [r6, #0x2]
	add r6, r6, r5
_020BC2E4:
	ldr r5, [r6, r1]
	add r7, r6, r1
	cmp r5, lr
	bne _020BC334
	ldr r5, [r7, #0x4]
	cmp r5, r12
	bne _020BC334
	ldr r5, [r7, #0x8]
	cmp r5, r3
	bne _020BC334
	ldr r5, [r7, #0xc]
	cmp r5, r2
	bne _020BC334
	ldrh r2, [r0, #0x6]
	add sp, sp, #0x4
	ldrh r1, [r0, r2]
	add r0, r0, r2
	add r0, r0, #0x4
	mla r0, r1, r4, r0
	ldmia sp!, {r4-r7,pc}
_020BC334:
	ldrb r5, [r0, #0x1]
	add r4, r4, #0x1
	add r1, r1, #0x10
	cmp r4, r5
	blo _020BC2E4
	b _020BC404
_020BC34C:
	add r3, r0, #0x8
	ldrb r2, [r3, #0x1]
	cmp r2, #0x0
	beq _020BC404
	ldrb r5, [r3, r2, lsl #0x2]
	ldrb r4, [r3, #0x0]
	add r2, r3, r2, lsl #0x2
	cmp r4, r5
	bls _020BC3A0
_020BC370:
	mov r4, r5, asr #0x5
	ldr r12, [r1, r4, lsl #0x2]
	and r4, r5, #0x1f
	mov r4, r12, lsr r4
	and r4, r4, #0x1
	add r4, r2, r4
	ldrb r12, [r4, #0x1]
	ldrb r4, [r2, #0x0]
	ldrb r5, [r3, r12, lsl #0x2]
	add r2, r3, r12, lsl #0x2
	cmp r4, r5
	bhi _020BC370
_020BC3A0:
	ldrh r4, [r0, #0x6]
	ldrb r2, [r2, #0x3]
	ldr r3, [r1, #0x0]
	add r0, r0, r4
	ldrh r4, [r0, #0x2]
	add r12, r0, r4
	ldr r4, [r12, r2, lsl #0x4]
	add r12, r12, r2, lsl #0x4
	cmp r4, r3
	bne _020BC404
	ldr r4, [r12, #0x4]
	ldr r3, [r1, #0x4]
	cmp r4, r3
	bne _020BC404
	ldr r4, [r12, #0x8]
	ldr r3, [r1, #0x8]
	cmp r4, r3
	bne _020BC404
	ldr r3, [r12, #0xc]
	ldr r1, [r1, #0xc]
	cmp r3, r1
	ldreqh r1, [r0], #0x4
	addeq sp, sp, #0x4
	mlaeq r0, r1, r2, r0
	ldmeqia sp!, {r4-r7,pc}
_020BC404:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020BC410
FUN_020BC410: ; 0x020BC410
	ldrh r3, [r0, #0x12]
	add r0, r0, #0xc
	ldrh r2, [r0, r3]
	add r0, r0, r3
	add r0, r0, #0x4
	mla r0, r2, r1, r0
	bx lr

	arm_func_start FUN_020BC42C
FUN_020BC42C: ; 0x020BC42C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r2
	bl FUN_020BC410
	ldrsh r1, [r0, #0x4]
	ldrh r3, [r0, #0x6]
	mul r2, r1, r4
	add r3, r5, r3
	mov r2, r2, lsr #0xc
	b _020BC45C
_020BC458:
	sub r2, r2, #0x1
_020BC45C:
	cmp r2, #0x0
	beq _020BC474
	mov r1, r2, lsl #0x2
	ldrh r1, [r3, r1]
	cmp r1, r4
	bhs _020BC458
_020BC474:
	ldrh r1, [r0, #0x0]
	b _020BC480
_020BC47C:
	add r2, r2, #0x1
_020BC480:
	add r0, r2, #0x1
	cmp r0, r1
	bhs _020BC49C
	add r0, r3, r2, lsl #0x2
	ldrh r0, [r0, #0x4]
	cmp r0, r4
	bls _020BC47C
_020BC49C:
	add r0, r3, r2, lsl #0x2
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020BC4A8
FUN_020BC4A8: ; 0x020BC4A8
	ldrh r2, [r0, #0xa]
	add r0, r0, r2
	add r0, r0, r1, lsl #0x4
	bx lr

	arm_func_start FUN_020BC4B8
FUN_020BC4B8: ; 0x020BC4B8
	ldrh r2, [r0, #0x8]
	add r0, r0, r2
	add r0, r0, r1, lsl #0x4
	bx lr

	arm_func_start FUN_020BC4C8
FUN_020BC4C8: ; 0x020BC4C8
	ldrh r2, [r0, #0xc]
	ldr r2, [r0, r2]
	add r12, r0, r2
	ldrh r2, [r12, #0xe]
	add r3, r12, #0x8
	ldrh r0, [r3, r2]
	add r2, r3, r2
	add r2, r2, #0x4
	mul r1, r0, r1
	adds r0, r2, r1
	ldrne r0, [r0, #0x0]
	addne r0, r12, r0
	moveq r0, #0x0
	bx lr

	arm_func_start FUN_020BC500
FUN_020BC500:
	stmdb sp!, {r4,lr}
	ands r4, r3, #0x8000
	beq _020BC5E0
	mov r2, #0x0
	str r2, [r0, #0x20]
	ldr r4, [r0, #0x20]
	ldr r2, _020BC684 ; =0x00007FFF
	str r4, [r0, #0x1c]
	ldr r4, [r0, #0x1c]
	and r3, r3, r2
	str r4, [r0, #0x18]
	ldr r4, [r0, #0x18]
	mov r2, #0x3
	str r4, [r0, #0x14]
	ldr r4, [r0, #0x14]
	mul r2, r3, r2
	str r4, [r0, #0x10]
	ldr r4, [r0, #0x10]
	mov r3, r2, lsl #0x1
	str r4, [r0, #0xc]
	ldr r4, [r0, #0xc]
	add r2, r1, r2, lsl #0x1
	str r4, [r0, #0x8]
	ldr r4, [r0, #0x8]
	str r4, [r0, #0x4]
	ldr r4, [r0, #0x4]
	str r4, [r0, #0x0]
	ldrsh r4, [r1, r3]
	ldrsh r12, [r2, #0x2]
	ldrsh r3, [r2, #0x4]
	and r1, r4, #0xf
	ands r4, r4, #0x10
	movne lr, #0x1000
	rsbne lr, lr, #0x0
	moveq lr, #0x1000
	str lr, [r0, r1, lsl #0x2]
	ldr r4, _020BC688 ; =0x020FFA14
	ldr lr, _020BC68C ; =0x020FFA15
	ldrb r4, [r4, r1, lsl #0x2]
	str r12, [r0, r4, lsl #0x2]
	ldrb lr, [lr, r1, lsl #0x2]
	str r3, [r0, lr, lsl #0x2]
	ldrsh lr, [r2, #0x0]
	ands lr, lr, #0x20
	ldr lr, _020BC690 ; =0x020FFA16
	rsbne r3, r3, #0x0
	ldrb lr, [lr, r1, lsl #0x2]
	str r3, [r0, lr, lsl #0x2]
	ldrsh r2, [r2, #0x0]
	ands r2, r2, #0x40
	ldr r2, _020BC694 ; =0x020FFA17
	rsbne r12, r12, #0x0
	ldrb r1, [r2, r1, lsl #0x2]
	str r12, [r0, r1, lsl #0x2]
	mov r0, #0x0
	ldmia sp!, {r4,pc}
_020BC5E0:
	ldr r1, _020BC684 ; =0x00007FFF
	mov r12, #0x5
	and r1, r3, r1
	mul r3, r1, r12
	add r1, r2, r3, lsl #0x1
	ldrsh lr, [r1, #0x8]
	mov r12, r3, lsl #0x1
	mov r3, lr, asr #0x3
	str r3, [r0, #0x10]
	ldrsh r12, [r2, r12]
	and r2, lr, #0x7
	mov r2, r2, lsl #0x10
	mov r3, r12, asr #0x3
	str r3, [r0, #0x0]
	ldrsh r3, [r1, #0x2]
	and r12, r12, #0x7
	orr lr, r12, r2, asr #0xd
	mov r2, r3, asr #0x3
	str r2, [r0, #0x4]
	ldrsh r12, [r1, #0x4]
	mov r2, lr, lsl #0x10
	and lr, r3, #0x7
	mov r3, r12, asr #0x3
	str r3, [r0, #0x8]
	ldrsh r3, [r1, #0x6]
	orr r1, lr, r2, asr #0xd
	mov r1, r1, lsl #0x10
	and r2, r12, #0x7
	orr r1, r2, r1, asr #0xd
	mov r1, r1, lsl #0x10
	and r2, r3, #0x7
	orr r1, r2, r1, asr #0xd
	mov r1, r1, lsl #0x10
	mov r1, r1, asr #0x10
	mov r2, r3, asr #0x3
	mov r1, r1, lsl #0x13
	str r2, [r0, #0xc]
	mov r1, r1, asr #0x13
	str r1, [r0, #0x14]
	mov r0, #0x1
	ldmia sp!, {r4,pc}
	.balign 4
_020BC684: .word 0x00007FFF
_020BC688: .word 0x020FFA14
_020BC68C: .word 0x020FFA15
_020BC690: .word 0x020FFA16
_020BC694: .word 0x020FFA17

	arm_func_start FUN_020BC698
FUN_020BC698: ; 0x020BC698
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x48
	ldrh r4, [r3, #0x4]
	ldr r5, [r3, #0xc]
	ldr r8, [r3, #0x10]
	ldr r7, [r2, #0x4]
	mov r12, r1, asr #0xc
	sub r4, r4, #0x1
	mov r6, r0
	cmp r12, r4
	add r5, r3, r5
	add r4, r3, r8
	add r8, r3, r7
	ldr r7, [r2, #0x0]
	bne _020BC780
	ands r0, r7, #0xc0000000
	beq _020BC6F0
	ands r0, r7, #0x40000000
	andne r0, r12, #0x1
	addne r12, r0, r12, lsr #0x1
	andeq r0, r12, #0x3
	addeq r12, r0, r12, lsr #0x2
_020BC6F0:
	ldr r0, [r3, #0x8]
	ands r0, r0, #0x2
	movne r7, #0x0
	bne _020BC7F4
	mov r0, r12, lsl #0x1
	ldrh r3, [r8, r0]
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_020BC500
_020BC718: ; 0x020BC718
	cmp r0, #0x0
	addeq sp, sp, #0x48
	ldmeqia sp!, {r4-r10,pc}
_020BC724: ; 0x020BC724
	ldr r9, [r6, #0x14]
	ldr r5, [r6, #0x4]
	ldr r4, [r6, #0x10]
	ldr r2, [r6, #0x8]
	mul r1, r5, r9
	mul r0, r2, r4
	sub r0, r1, r0
	ldr r7, [r6, #0xc]
	ldr r8, [r6, #0x0]
	mov r3, r0, asr #0xc
	mul r1, r2, r7
	mul r0, r8, r9
	sub r2, r1, r0
	mul r1, r8, r4
	mul r0, r5, r7
	sub r0, r1, r0
	str r3, [r6, #0x18]
	mov r1, r2, asr #0xc
	str r1, [r6, #0x1c]
	mov r0, r0, asr #0xc
	add sp, sp, #0x48
	str r0, [r6, #0x20]
	ldmia sp!, {r4-r10,pc}
_020BC780:
	ands r0, r7, #0xc0000000
	beq _020BC7F0
	ldr r0, _020BC9C4 ; =0x1FFF0000
	ands r2, r7, #0x40000000
	and r0, r7, r0
	mov r0, r0, lsr #0x10
	beq _020BC7C4
	cmp r12, r0
	movcs r12, r0, lsr #0x1
	addcs r7, r12, #0x1
	bhs _020BC7F4
	ldr r0, _020BC9C8 ; =0x00001FFF
	mov r12, r12, lsr #0x1
	add r7, r12, #0x1
	and r10, r1, r0
	mov r9, #0x2
	b _020BC800
_020BC7C4:
	cmp r12, r0
	andcs r0, r12, #0x3
	addcs r12, r0, r12, lsr #0x2
	addcs r7, r12, #0x1
	bhs _020BC7F4
	ldr r0, _020BC9CC ; =0x00003FFF
	mov r12, r12, lsr #0x2
	add r7, r12, #0x1
	and r10, r1, r0
	mov r9, #0x4
	b _020BC800
_020BC7F0:
	add r7, r12, #0x1
_020BC7F4:
	ldr r0, _020BC9D0 ; =0x00000FFF
	mov r9, #0x1
	and r10, r1, r0
_020BC800:
	mov r0, r12, lsl #0x1
	ldrh r3, [r8, r0]
	add r0, sp, #0x0
	mov r1, r5
	mov r2, r4
	bl FUN_020BC500
	mov r1, r7, lsl #0x1
	ldrh r3, [r8, r1]
	orr r7, r0, #0x0
	add r0, sp, #0x24
	mov r1, r5
	mov r2, r4
	bl FUN_020BC500
	ldr r3, [sp, #0x0]
	ldr r1, [sp, #0x24]
	mul r2, r3, r9
	sub r1, r1, r3
	mul r1, r10, r1
	add r1, r2, r1, asr #0xc
	str r1, [r6, #0x0]
	ldr r3, [sp, #0x4]
	ldr r1, [sp, #0x28]
	mul r2, r3, r9
	sub r1, r1, r3
	mul r1, r10, r1
	add r1, r2, r1, asr #0xc
	str r1, [r6, #0x4]
	ldr r3, [sp, #0x8]
	ldr r1, [sp, #0x2c]
	mul r2, r3, r9
	sub r1, r1, r3
	mul r1, r10, r1
	add r1, r2, r1, asr #0xc
	str r1, [r6, #0x8]
	ldr r3, [sp, #0xc]
	ldr r1, [sp, #0x30]
	mul r2, r3, r9
	sub r1, r1, r3
	mul r1, r10, r1
	add r1, r2, r1, asr #0xc
	str r1, [r6, #0xc]
	ldr r2, [sp, #0x10]
	ldr r1, [sp, #0x34]
	orr r7, r7, r0
	sub r0, r1, r2
	mul r1, r2, r9
	mul r0, r10, r0
	add r0, r1, r0, asr #0xc
	str r0, [r6, #0x10]
	ldr r2, [sp, #0x14]
	ldr r0, [sp, #0x38]
	mul r1, r2, r9
	sub r0, r0, r2
	mul r0, r10, r0
	add r2, r1, r0, asr #0xc
	mov r0, r6
	mov r1, r6
	str r2, [r6, #0x14]
	bl VEC_Normalize
	add r0, r6, #0xc
	mov r1, r0
	bl VEC_Normalize
_020BC8F8: ; 0x020BC8F8
	cmp r7, #0x0
	bne _020BC968
	ldr r3, [sp, #0x18]
	ldr r1, [sp, #0x3c]
	mul r2, r3, r9
	sub r1, r1, r3
	mul r1, r10, r1
	add r1, r2, r1, asr #0xc
	str r1, [r6, #0x18]
	ldr r3, [sp, #0x1c]
	ldr r1, [sp, #0x40]
	mul r2, r3, r9
	sub r1, r1, r3
	mul r1, r10, r1
	add r1, r2, r1, asr #0xc
	str r1, [r6, #0x1c]
	ldr r3, [sp, #0x20]
	ldr r1, [sp, #0x44]
	mul r2, r3, r9
	sub r1, r1, r3
	mul r1, r10, r1
	add r2, r2, r1, asr #0xc
	add r0, r6, #0x18
	mov r1, r0
	str r2, [r6, #0x20]
	bl VEC_Normalize
	add sp, sp, #0x48
	ldmia sp!, {r4-r10,pc}
_020BC968:
	ldr r9, [r6, #0x14]
	ldr r5, [r6, #0x4]
	ldr r8, [r6, #0x0]
	ldr r4, [r6, #0x10]
	ldr r2, [r6, #0x8]
	ldr r7, [r6, #0xc]
	mul r1, r5, r9
	mul r0, r2, r4
	sub r0, r1, r0
	mov r3, r0, asr #0xc
	mul r1, r2, r7
	mul r0, r8, r9
	sub r2, r1, r0
	mul r1, r8, r4
	mul r0, r5, r7
	sub r0, r1, r0
	str r3, [r6, #0x18]
	mov r1, r2, asr #0xc
	str r1, [r6, #0x1c]
	mov r0, r0, asr #0xc
	str r0, [r6, #0x20]
	add sp, sp, #0x48
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020BC9C4: .word 0x1FFF0000
_020BC9C8: .word 0x00001FFF
_020BC9CC: .word 0x00003FFF
_020BC9D0: .word 0x00000FFF

	arm_func_start FUN_020BC9D4
FUN_020BC9D4: ; 0x020BC9D4
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4c
	ldr r5, [r3, #0xc]
	ldr r4, [r3, #0x10]
	ldr r12, [r2, #0x0]
	ldr r2, [r2, #0x4]
	mov r6, r0
	mov r0, r1, asr #0xc
	add r5, r3, r5
	add r4, r3, r4
	add r8, r3, r2
	ands r1, r12, #0xc0000000
	beq _020BCD40
	ldr r1, _020BCDC0 ; =0x1FFF0000
	ands r2, r12, #0x40000000
	and r1, r12, r1
	mov r2, r1, lsr #0x10
	beq _020BCA44
	ands r1, r0, #0x1
	beq _020BCA3C
	cmp r0, r2
	movhi r0, r2, lsr #0x1
	addhi r0, r0, #0x1
	bhi _020BCD40
	mov r7, r0, lsr #0x1
	b _020BCBE8
_020BCA3C:
	mov r0, r0, lsr #0x1
	b _020BCD40
_020BCA44:
	ands r1, r0, #0x3
	beq _020BCBE0
	cmp r0, r2
	addhi r0, r1, r2, lsr #0x2
	bhi _020BCD40
	ands r1, r0, #0x1
	beq _020BCBD8
	ands r1, r0, #0x2
	movne r9, r0, lsr #0x2
	addne r0, r9, #0x1
	moveq r0, r0, lsr #0x2
	addeq r9, r0, #0x1
	mov r0, r0, lsl #0x1
	ldrh r3, [r8, r0]
	mov r0, r6
	mov r1, r5
	mov r2, r4
	mov r7, #0x0
	bl FUN_020BC500
	mov r1, r9, lsl #0x1
	ldrh r3, [r8, r1]
	orr r7, r7, r0
	add r0, sp, #0x0
	mov r1, r5
	mov r2, r4
	bl FUN_020BC500
	ldr r3, [sp, #0x0]
	ldr r1, [r6, #0x0]
	mov r2, #0x3
	mla r3, r1, r2, r3
	str r3, [r6, #0x0]
	ldr r3, [sp, #0x4]
	ldr r1, [r6, #0x4]
	orr r7, r7, r0
	mla r0, r1, r2, r3
	str r0, [r6, #0x4]
	ldr r3, [sp, #0x8]
	ldr r1, [r6, #0x8]
	mov r0, r6
	mla r3, r1, r2, r3
	str r3, [r6, #0x8]
	ldr r4, [sp, #0xc]
	ldr r3, [r6, #0xc]
	mov r1, r6
	mla r4, r3, r2, r4
	str r4, [r6, #0xc]
	ldr r4, [sp, #0x10]
	ldr r3, [r6, #0x10]
	mla r4, r3, r2, r4
	str r4, [r6, #0x10]
	ldr r4, [sp, #0x14]
	ldr r3, [r6, #0x14]
	mla r2, r3, r2, r4
	str r2, [r6, #0x14]
	bl VEC_Normalize
	add r0, r6, #0xc
	mov r1, r0
	bl VEC_Normalize
_020BCB2C: ; 0x020BCB2C
	cmp r7, #0x0
	bne _020BCB7C
	ldr r1, [sp, #0x18]
	ldr r0, [r6, #0x18]
	mov r2, #0x3
	mla r1, r0, r2, r1
	str r1, [r6, #0x18]
	ldr r3, [sp, #0x1c]
	ldr r1, [r6, #0x1c]
	add r0, r6, #0x18
	mla r3, r1, r2, r3
	str r3, [r6, #0x1c]
	ldr r4, [sp, #0x20]
	ldr r3, [r6, #0x20]
	mov r1, r0
	mla r2, r3, r2, r4
	str r2, [r6, #0x20]
	bl VEC_Normalize
	add sp, sp, #0x4c
	ldmia sp!, {r4-r9,pc}
_020BCB7C:
	ldr r12, [r6, #0x14]
	ldr r5, [r6, #0x4]
	ldr r4, [r6, #0x10]
	ldr r2, [r6, #0x8]
	mul r1, r5, r12
	mul r0, r2, r4
	sub r0, r1, r0
	ldr r7, [r6, #0xc]
	ldr r8, [r6, #0x0]
	mov r3, r0, asr #0xc
	mul r1, r2, r7
	mul r0, r8, r12
	sub r2, r1, r0
	mul r1, r8, r4
	mul r0, r5, r7
	sub r0, r1, r0
	str r3, [r6, #0x18]
	mov r1, r2, asr #0xc
	str r1, [r6, #0x1c]
	mov r0, r0, asr #0xc
	add sp, sp, #0x4c
	str r0, [r6, #0x20]
	ldmia sp!, {r4-r9,pc}
_020BCBD8:
	mov r7, r0, lsr #0x2
	b _020BCBE8
_020BCBE0:
	mov r0, r0, lsr #0x2
	b _020BCD40
_020BCBE8:
	mov r0, r7, lsl #0x1
	ldrh r3, [r8, r0]
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_020BC500
	add r1, r8, r7, lsl #0x1
	ldrh r3, [r1, #0x2]
	orr r7, r0, #0x0
	add r0, sp, #0x24
	mov r1, r5
	mov r2, r4
	bl FUN_020BC500
	ldr r2, [r6, #0x0]
	ldr r1, [sp, #0x24]
	orr r7, r7, r0
	add r0, r2, r1
	str r0, [r6, #0x0]
	ldr r2, [r6, #0x4]
	ldr r1, [sp, #0x28]
	mov r0, r6
	add r1, r2, r1
	str r1, [r6, #0x4]
	ldr r3, [r6, #0x8]
	ldr r2, [sp, #0x2c]
	mov r1, r6
	add r2, r3, r2
	str r2, [r6, #0x8]
	ldr r3, [r6, #0xc]
	ldr r2, [sp, #0x30]
	add r2, r3, r2
	str r2, [r6, #0xc]
	ldr r3, [r6, #0x10]
	ldr r2, [sp, #0x34]
	add r2, r3, r2
	str r2, [r6, #0x10]
	ldr r3, [r6, #0x14]
	ldr r2, [sp, #0x38]
	add r2, r3, r2
	str r2, [r6, #0x14]
	bl VEC_Normalize
	add r0, r6, #0xc
	mov r1, r0
	bl VEC_Normalize
_020BCC98: ; 0x020BCC98
	cmp r7, #0x0
	bne _020BCCE4
	ldr r2, [r6, #0x18]
	ldr r1, [sp, #0x3c]
	add r0, r6, #0x18
	add r1, r2, r1
	str r1, [r6, #0x18]
	ldr r3, [r6, #0x1c]
	ldr r2, [sp, #0x40]
	mov r1, r0
	add r2, r3, r2
	str r2, [r6, #0x1c]
	ldr r3, [r6, #0x20]
	ldr r2, [sp, #0x44]
	add r2, r3, r2
	str r2, [r6, #0x20]
	bl VEC_Normalize
	add sp, sp, #0x4c
	ldmia sp!, {r4-r9,pc}
_020BCCE4:
	ldr r12, [r6, #0x14]
	ldr r5, [r6, #0x4]
	ldr r4, [r6, #0x10]
	ldr r2, [r6, #0x8]
	mul r1, r5, r12
	mul r0, r2, r4
	sub r0, r1, r0
	ldr r7, [r6, #0xc]
	ldr r8, [r6, #0x0]
	mov r3, r0, asr #0xc
	mul r1, r2, r7
	mul r0, r8, r12
	sub r2, r1, r0
	mul r1, r8, r4
	mul r0, r5, r7
	sub r0, r1, r0
	str r3, [r6, #0x18]
	mov r1, r2, asr #0xc
	str r1, [r6, #0x1c]
	mov r0, r0, asr #0xc
	add sp, sp, #0x4c
	str r0, [r6, #0x20]
	ldmia sp!, {r4-r9,pc}
_020BCD40:
	mov r0, r0, lsl #0x1
	ldrh r3, [r8, r0]
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_020BC500
_020BCD58: ; 0x020BCD58
	cmp r0, #0x0
	addeq sp, sp, #0x4c
	ldmeqia sp!, {r4-r9,pc}
_020BCD64: ; 0x020BCD64
	ldr r12, [r6, #0x14]
	ldr r5, [r6, #0x4]
	ldr r8, [r6, #0x0]
	ldr r4, [r6, #0x10]
	ldr r2, [r6, #0x8]
	ldr r7, [r6, #0xc]
	mul r1, r5, r12
	mul r0, r2, r4
	sub r0, r1, r0
	mov r3, r0, asr #0xc
	mul r1, r2, r7
	mul r0, r8, r12
	sub r2, r1, r0
	mul r1, r8, r4
	mul r0, r5, r7
	sub r0, r1, r0
	str r3, [r6, #0x18]
	mov r1, r2, asr #0xc
	str r1, [r6, #0x1c]
	mov r0, r0, asr #0xc
	str r0, [r6, #0x20]
	add sp, sp, #0x4c
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020BCDC0: .word 0x1FFF0000

	arm_func_start FUN_020BCDC4
FUN_020BCDC4: ; 0x020BCDC4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldrh r4, [r3, #0x4]
	ldr r6, [r2, #0x4]
	mov r5, r1, asr #0xc
	sub r4, r4, #0x1
	cmp r5, r4
	add r6, r3, r6
	ldr r2, [r2, #0x0]
	bne _020BCE58
	ands r4, r2, #0xc0000000
	beq _020BCE08
	ands r4, r2, #0x40000000
	andne r4, r5, #0x1
	addne r5, r4, r5, lsr #0x1
	andeq r4, r5, #0x3
	addeq r5, r4, r5, lsr #0x2
_020BCE08:
	ldr r3, [r3, #0x8]
	ands r3, r3, #0x2
	movne r4, #0x0
	bne _020BCED4
	ands r1, r2, #0x20000000
	ldreq r2, [r6, r5, lsl #0x3]
	addeq r1, r6, r5, lsl #0x3
	streq r2, [r0, #0x0]
	ldreq r1, [r1, #0x4]
	addeq sp, sp, #0x4
	streq r1, [r0, #0x4]
	ldmeqia sp!, {r4-r7,pc}
_020BCE38: ; 0x020BCE38
	mov r1, r5, lsl #0x2
	ldrsh r2, [r6, r1]
	add r1, r6, r5, lsl #0x2
	add sp, sp, #0x4
	str r2, [r0, #0x0]
	ldrsh r1, [r1, #0x2]
	str r1, [r0, #0x4]
	ldmia sp!, {r4-r7,pc}
_020BCE58:
	ands r3, r2, #0xc0000000
	beq _020BCED0
	ldr r3, _020BCF60 ; =0x1FFF0000
	ands r4, r2, #0x40000000
	and r3, r2, r3
	mov r3, r3, lsr #0x10
	beq _020BCEA0
	cmp r5, r3
	movcs r5, r3, lsr #0x1
	addcs r4, r5, #0x1
	bhs _020BCED4
	ldr r3, _020BCF64 ; =0x00001FFF
	mov r5, r5, lsr #0x1
	add r4, r5, #0x1
	and lr, r1, r3
	mov r12, #0x2
	mov r3, #0x1
	b _020BCEE4
_020BCEA0:
	cmp r5, r3
	andcs r3, r5, #0x3
	addcs r5, r3, r5, lsr #0x2
	addcs r4, r5, #0x1
	bhs _020BCED4
	ldr r3, _020BCF68 ; =0x00003FFF
	mov r5, r5, lsr #0x2
	add r4, r5, #0x1
	and lr, r1, r3
	mov r12, #0x4
	mov r3, #0x2
	b _020BCEE4
_020BCED0:
	add r4, r5, #0x1
_020BCED4:
	ldr r3, _020BCF6C ; =0x00000FFF
	mov r12, #0x1
	and lr, r1, r3
	mov r3, #0x0
_020BCEE4:
	ands r1, r2, #0x20000000
	beq _020BCF10
	mov r2, r5, lsl #0x2
	add r1, r6, r5, lsl #0x2
	mov r5, r4, lsl #0x2
	add r4, r6, r4, lsl #0x2
	ldrsh r2, [r6, r2]
	ldrsh r1, [r1, #0x2]
	ldrsh r5, [r6, r5]
	ldrsh r4, [r4, #0x2]
	b _020BCF28
_020BCF10:
	add r1, r6, r5, lsl #0x3
	add r7, r6, r4, lsl #0x3
	ldr r2, [r6, r5, lsl #0x3]
	ldr r1, [r1, #0x4]
	ldr r5, [r6, r4, lsl #0x3]
	ldr r4, [r7, #0x4]
_020BCF28:
	sub r5, r5, r2
	sub r4, r4, r1
	mul r6, r2, r12
	mul r2, lr, r5
	add r2, r6, r2, asr #0xc
	mov r5, r2, asr r3
	mul r2, r1, r12
	mul r1, lr, r4
	add r1, r2, r1, asr #0xc
	mov r1, r1, asr r3
	str r5, [r0, #0x0]
	str r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020BCF60: .word 0x1FFF0000
_020BCF64: .word 0x00001FFF
_020BCF68: .word 0x00003FFF
_020BCF6C: .word 0x00000FFF

	arm_func_start FUN_020BCF70
FUN_020BCF70: ; 0x020BCF70
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r4, [r2, #0x4]
	ldr r12, [r2, #0x0]
	mov r1, r1, asr #0xc
	add r3, r3, r4
	ands r2, r12, #0xc0000000
	beq _020BD0D0
	ldr r2, _020BD184 ; =0x1FFF0000
	ands r4, r12, #0x40000000
	and r2, r12, r2
	mov r4, r2, lsr #0x10
	beq _020BCFCC
	ands r2, r1, #0x1
	beq _020BCFC4
	cmp r1, r4
	movhi r1, r4, lsr #0x1
	addhi r1, r1, #0x1
	bhi _020BD0D0
	mov r2, r1, lsr #0x1
	b _020BD110
_020BCFC4:
	mov r1, r1, lsr #0x1
	b _020BD0D0
_020BCFCC:
	ands r2, r1, #0x3
	beq _020BD0CC
	cmp r1, r4
	addhi r1, r2, r4, lsr #0x2
	bhi _020BD0D0
	ands r2, r1, #0x1
	beq _020BD0C4
	ands r2, r1, #0x2
	movne r1, r1, lsr #0x2
	addne r2, r1, #0x1
	moveq r2, r1, lsr #0x2
	addeq r1, r2, #0x1
	ands r4, r12, #0x20000000
	beq _020BD04C
	mov r5, r2, lsl #0x2
	mov r4, r1, lsl #0x2
	ldrsh r12, [r3, r5]
	ldrsh r5, [r3, r4]
	add r2, r3, r2, lsl #0x2
	add r4, r12, r12, lsl #0x1
	add r4, r5, r4
	mov r4, r4, asr #0x2
	str r4, [r0, #0x0]
	add r1, r3, r1, lsl #0x2
	ldrsh r3, [r2, #0x2]
	ldrsh r2, [r1, #0x2]
	add sp, sp, #0x4
	add r1, r3, r3, lsl #0x1
	add r1, r2, r1
	mov r1, r1, asr #0x2
	str r1, [r0, #0x4]
	ldmia sp!, {r4-r5,pc}
_020BD04C:
	ldr r5, [r3, r2, lsl #0x3]
	ldr r4, [r3, r1, lsl #0x3]
	mov r12, r5, asr #0x1f
	mov r12, r12, lsl #0x1
	mov lr, r5, lsl #0x1
	orr r12, r12, r5, lsr #0x1f
	adds lr, lr, r5
	adc r12, r12, r5, asr #0x1f
	adds lr, lr, r4
	adc r12, r12, r4, asr #0x1f
	mov lr, lr, lsr #0x2
	orr lr, lr, r12, lsl #0x1e
	str lr, [r0, #0x0]
	add r2, r3, r2, lsl #0x3
	ldr r12, [r2, #0x4]
	add r1, r3, r1, lsl #0x3
	mov r2, r12, asr #0x1f
	mov r2, r2, lsl #0x1
	mov r3, r12, lsl #0x1
	ldr r1, [r1, #0x4]
	orr r2, r2, r12, lsr #0x1f
	adds r3, r3, r12
	adc r2, r2, r12, asr #0x1f
	adds r3, r3, r1
	adc r1, r2, r1, asr #0x1f
	mov r2, r3, lsr #0x2
	orr r2, r2, r1, lsl #0x1e
	str r2, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020BD0C4:
	mov r2, r1, lsr #0x2
	b _020BD110
_020BD0CC:
	mov r1, r1, lsr #0x2
_020BD0D0:
	ands r2, r12, #0x20000000
	ldreq r2, [r3, r1, lsl #0x3]
	addeq r1, r3, r1, lsl #0x3
	streq r2, [r0, #0x0]
	ldreq r1, [r1, #0x4]
	addeq sp, sp, #0x4
	streq r1, [r0, #0x4]
	ldmeqia sp!, {r4-r5,pc}
_020BD0F0: ; 0x020BD0F0
	mov r2, r1, lsl #0x2
	ldrsh r2, [r3, r2]
	add r1, r3, r1, lsl #0x2
	add sp, sp, #0x4
	str r2, [r0, #0x0]
	ldrsh r1, [r1, #0x2]
	str r1, [r0, #0x4]
	ldmia sp!, {r4-r5,pc}
_020BD110:
	ands r1, r12, #0x20000000
	beq _020BD150
	mov r1, r2, lsl #0x2
	add r12, r3, r2, lsl #0x2
	ldrsh r2, [r3, r1]
	ldrsh r1, [r12, #0x4]
	add sp, sp, #0x4
	add r1, r2, r1
	mov r1, r1, asr #0x1
	str r1, [r0, #0x0]
	ldrsh r2, [r12, #0x2]
	ldrsh r1, [r12, #0x6]
	add r1, r2, r1
	mov r1, r1, asr #0x1
	str r1, [r0, #0x4]
	ldmia sp!, {r4-r5,pc}
_020BD150:
	add r12, r3, r2, lsl #0x3
	ldr r2, [r3, r2, lsl #0x3]
	ldr r1, [r12, #0x8]
	add r1, r2, r1
	mov r1, r1, asr #0x1
	str r1, [r0, #0x0]
	ldr r2, [r12, #0x4]
	ldr r1, [r12, #0xc]
	add r1, r2, r1
	mov r1, r1, asr #0x1
	str r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020BD184: .word 0x1FFF0000

	arm_func_start FUN_020BD188
FUN_020BD188: ; 0x020BD188
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldrh r4, [r3, #0x4]
	ldr lr, [r2, #0x4]
	mov r12, r1, asr #0xc
	sub r4, r4, #0x1
	cmp r12, r4
	add r4, r3, lr
	ldr lr, [r2, #0x0]
	bne _020BD230
	ands r2, lr, #0xc0000000
	beq _020BD1CC
	ands r2, lr, #0x40000000
	andne r2, r12, #0x1
	addne r12, r2, r12, lsr #0x1
	andeq r2, r12, #0x3
	addeq r12, r2, r12, lsr #0x2
_020BD1CC:
	ldr r2, [r3, #0x8]
	ands r2, r2, #0x2
	beq _020BD210
	ldr r2, _020BD2E8 ; =0x00000FFF
	ands r3, lr, #0x20000000
	and r3, r1, r2
	movne r1, r12, lsl #0x1
	ldrnesh r2, [r4, r1]
	ldrnesh r1, [r4, #0x0]
	add sp, sp, #0x4
	ldreq r2, [r4, r12, lsl #0x2]
	ldreq r1, [r4, #0x0]
	sub r1, r1, r2
	mul r1, r3, r1
	add r1, r2, r1, asr #0xc
	str r1, [r0, #0x0]
	ldmia sp!, {r4-r5,pc}
_020BD210:
	ands r1, lr, #0x20000000
	movne r1, r12, lsl #0x1
	ldrnesh r1, [r4, r1]
	add sp, sp, #0x4
	strne r1, [r0, #0x0]
	ldreq r1, [r4, r12, lsl #0x2]
	streq r1, [r0, #0x0]
	ldmia sp!, {r4-r5,pc}
_020BD230:
	ands r2, lr, #0xc0000000
	beq _020BD298
	ldr r2, _020BD2EC ; =0x1FFF0000
	ands r3, lr, #0x40000000
	and r2, lr, r2
	mov r2, r2, lsr #0x10
	beq _020BD270
	cmp r12, r2
	movcs r12, r2, lsr #0x1
	bhs _020BD298
	ldr r2, _020BD2F0 ; =0x00001FFF
	mov r12, r12, lsr #0x1
	and r5, r1, r2
	mov r2, #0x2
	mov r1, #0x1
	b _020BD2A8
_020BD270:
	cmp r12, r2
	andcs r2, r12, #0x3
	addcs r12, r2, r12, lsr #0x2
	bhs _020BD298
	ldr r2, _020BD2F4 ; =0x00003FFF
	mov r12, r12, lsr #0x2
	and r5, r1, r2
	mov r2, #0x4
	mov r1, #0x2
	b _020BD2A8
_020BD298:
	ldr r3, _020BD2E8 ; =0x00000FFF
	mov r2, #0x1
	and r5, r1, r3
	mov r1, #0x0
_020BD2A8:
	ands r3, lr, #0x20000000
	addne r3, r4, r12, lsl #0x1
	movne lr, r12, lsl #0x1
	ldrnesh r12, [r4, lr]
	ldrnesh r3, [r3, #0x2]
	addeq r3, r4, r12, lsl #0x2
	ldreq r12, [r4, r12, lsl #0x2]
	ldreq r3, [r3, #0x4]
	mul r4, r12, r2
	sub r3, r3, r12
	mul r2, r5, r3
	add r2, r4, r2, asr #0xc
	mov r1, r2, asr r1
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020BD2E8: .word 0x00000FFF
_020BD2EC: .word 0x1FFF0000
_020BD2F0: .word 0x00001FFF
_020BD2F4: .word 0x00003FFF

	arm_func_start FUN_020BD2F8
FUN_020BD2F8: ; 0x020BD2F8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r12, [r2, #0x4]
	ldr r2, [r2, #0x0]
	mov r1, r1, asr #0xc
	add r3, r3, r12
	ands r12, r2, #0xc0000000
	beq _020BD44C
	ldr ip, _020BD46C ; =0x1FFF0000
	ands lr, r2, #0x40000000
	and r12, r2, r12
	mov lr, r12, lsr #0x10
	beq _020BD354
	ands r12, r1, #0x1
	beq _020BD34C
	cmp r1, lr
	movhi r1, lr, lsr #0x1
	addhi r1, r1, #0x1
	bhi _020BD44C
	mov r12, r1, lsr #0x1
	b _020BD400
_020BD34C:
	mov r1, r1, lsr #0x1
	b _020BD44C
_020BD354:
	ands r12, r1, #0x3
	beq _020BD3F8
	cmp r1, lr
	addhi r1, r12, lr, lsr #0x2
	bhi _020BD44C
	ands r12, r1, #0x1
	beq _020BD3F0
	ands r12, r1, #0x2
	movne lr, r1, lsr #0x2
	addne r12, lr, #0x1
	moveq r12, r1, lsr #0x2
	addeq lr, r12, #0x1
	ands r1, r2, #0x20000000
	beq _020BD3B4
	mov r2, r12, lsl #0x1
	mov r1, lr, lsl #0x1
	ldrsh r12, [r3, r2]
	ldrsh r2, [r3, r1]
	mov r1, #0x3
	add sp, sp, #0x4
	smlabb r1, r12, r1, r2
	mov r1, r1, asr #0x2
	str r1, [r0, #0x0]
	ldmia sp!, {pc}
_020BD3B4:
	ldr r12, [r3, r12, lsl #0x2]
	ldr r1, [r3, lr, lsl #0x2]
	mov r2, r12, asr #0x1f
	mov r2, r2, lsl #0x1
	mov r3, r12, lsl #0x1
	orr r2, r2, r12, lsr #0x1f
	adds r3, r3, r12
	adc r2, r2, r12, asr #0x1f
	adds r3, r3, r1
	adc r1, r2, r1, asr #0x1f
	mov r2, r3, lsr #0x2
	orr r2, r2, r1, lsl #0x1e
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020BD3F0:
	mov r12, r1, lsr #0x2
	b _020BD400
_020BD3F8:
	mov r1, r1, lsr #0x2
	b _020BD44C
_020BD400:
	ands r1, r2, #0x20000000
	beq _020BD42C
	mov r2, r12, lsl #0x1
	add r1, r3, r12, lsl #0x1
	ldrsh r2, [r3, r2]
	ldrsh r1, [r1, #0x2]
	add sp, sp, #0x4
	add r1, r2, r1
	mov r1, r1, asr #0x1
	str r1, [r0, #0x0]
	ldmia sp!, {pc}
_020BD42C:
	add r1, r3, r12, lsl #0x2
	ldr r2, [r3, r12, lsl #0x2]
	ldr r1, [r1, #0x4]
	mov r2, r2, asr #0x1
	add r1, r2, r1, asr #0x1
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020BD44C:
	ands r2, r2, #0x20000000
	movne r1, r1, lsl #0x1
	ldrnesh r1, [r3, r1]
	strne r1, [r0, #0x0]
	ldreq r1, [r3, r1, lsl #0x2]
	streq r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020BD46C: .word 0x1FFF0000

	arm_func_start FUN_020BD470
FUN_020BD470: ; 0x020BD470
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	mov r9, r0
	add r0, r9, r1, lsl #0x1
	ldrh r0, [r0, #0x14]
	mov r7, r3
	mov r8, r2
	ldr r5, [r9, r0]
	add r1, r9, r0
	ands r0, r5, #0x1
	movne r0, #0x7
	strne r0, [r7, #0x0]
	bne _020BD814
	ldr r0, _020BD848 ; =0x00000FFF
	add r4, r1, #0x4
	ands r0, r8, r0
	beq _020BD4C4
	ldr r0, [r9, #0x8]
	ands r0, r0, #0x1
	movne r6, #0x1
	bne _020BD4C8
_020BD4C4:
	mov r6, #0x0
_020BD4C8:
	mov r0, #0x0
	str r0, [r7, #0x0]
	ands r0, r5, #0x6
	bne _020BD5C0
	ands r0, r5, #0x8
	bne _020BD51C
	cmp r6, #0x0
	beq _020BD500
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x4c
	bl FUN_020BD188
	b _020BD514
_020BD500:
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x4c
	bl FUN_020BD2F8
_020BD514:
	add r4, r4, #0x8
	b _020BD524
_020BD51C:
	ldr r0, [r4], #0x4
	str r0, [r7, #0x4c]
_020BD524:
	ands r0, r5, #0x10
	bne _020BD568
	cmp r6, #0x0
	beq _020BD54C
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x50
	bl FUN_020BD188
	b _020BD560
_020BD54C:
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x50
	bl FUN_020BD2F8
_020BD560:
	add r4, r4, #0x8
	b _020BD570
_020BD568:
	ldr r0, [r4], #0x4
	str r0, [r7, #0x50]
_020BD570:
	ands r0, r5, #0x20
	bne _020BD5B4
	cmp r6, #0x0
	beq _020BD598
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x54
	bl FUN_020BD188
	b _020BD5AC
_020BD598:
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x54
	bl FUN_020BD2F8
_020BD5AC:
	add r4, r4, #0x8
	b _020BD5DC
_020BD5B4:
	ldr r0, [r4], #0x4
	str r0, [r7, #0x54]
	b _020BD5DC
_020BD5C0:
	ands r0, r5, #0x2
	ldrne r0, [r7, #0x0]
	orrne r0, r0, #0x4
	strne r0, [r7, #0x0]
	bne _020BD5DC
	mov r0, r7
	bl FUN_020BDA08
_020BD5DC:
	ands r0, r5, #0xc0
	bne _020BD6A8
	ands r0, r5, #0x100
	bne _020BD628
	cmp r6, #0x0
	beq _020BD60C
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x28
	bl FUN_020BC698
	b _020BD620
_020BD60C:
	mov r1, r8
	mov r2, r4
	mov r3, r9
	add r0, r7, #0x28
	bl FUN_020BC9D4
_020BD620:
	add r4, r4, #0x8
	b _020BD6C4
_020BD628:
	ldr r1, [r9, #0xc]
	ldr r2, [r9, #0x10]
	ldr r3, [r4, #0x0]
	add r0, r7, #0x28
	add r1, r9, r1
	add r2, r9, r2
	bl FUN_020BC500
_020BD644: ; 0x020BD644
	cmp r0, #0x0
	beq _020BD6A0
	ldr r12, [r7, #0x3c]
	ldr r0, [r7, #0x2c]
	ldr r3, [r7, #0x28]
	ldr r11, [r7, #0x38]
	ldr r1, [r7, #0x30]
	ldr r2, [r7, #0x34]
	mul r10, r0, r12
	mul lr, r1, r11
	sub r10, r10, lr
	mov r10, r10, asr #0xc
	mul lr, r1, r2
	mul r1, r3, r12
	sub r1, lr, r1
	mul r11, r3, r11
	mul r2, r0, r2
	sub r0, r11, r2
	str r10, [r7, #0x40]
	mov r1, r1, asr #0xc
	str r1, [r7, #0x44]
	mov r0, r0, asr #0xc
	str r0, [r7, #0x48]
_020BD6A0:
	add r4, r4, #0x4
	b _020BD6C4
_020BD6A8:
	ands r0, r5, #0x40
	ldrne r0, [r7, #0x0]
	orrne r0, r0, #0x2
	strne r0, [r7, #0x0]
	bne _020BD6C4
	mov r0, r7
	bl FUN_020BD850
_020BD6C4:
	ands r0, r5, #0x600
	bne _020BD7F0
	ands r0, r5, #0x800
	bne _020BD71C
	cmp r6, #0x0
	beq _020BD6F4
	add r0, sp, #0x0
	mov r1, r8
	mov r2, r4
	mov r3, r9
	bl FUN_020BCDC4
	b _020BD708
_020BD6F4:
	add r0, sp, #0x0
	mov r1, r8
	mov r2, r4
	mov r3, r9
	bl FUN_020BCF70
_020BD708:
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x18]
	str r0, [sp, #0x24]
	b _020BD72C
_020BD71C:
	ldr r0, [r4, #0x0]
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x4]
	str r0, [sp, #0x24]
_020BD72C:
	ands r0, r5, #0x1000
	bne _020BD77C
	cmp r6, #0x0
	beq _020BD754
	add r0, sp, #0x8
	mov r1, r8
	mov r3, r9
	add r2, r4, #0x8
	bl FUN_020BCDC4
	b _020BD768
_020BD754:
	add r0, sp, #0x8
	mov r1, r8
	mov r3, r9
	add r2, r4, #0x8
	bl FUN_020BCF70
_020BD768:
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	str r1, [sp, #0x1c]
	str r0, [sp, #0x28]
	b _020BD78C
_020BD77C:
	ldr r0, [r4, #0x8]
	str r0, [sp, #0x1c]
	ldr r0, [r4, #0xc]
	str r0, [sp, #0x28]
_020BD78C:
	ands r0, r5, #0x2000
	bne _020BD7DC
	cmp r6, #0x0
	beq _020BD7B4
	add r0, sp, #0x10
	mov r1, r8
	mov r3, r9
	add r2, r4, #0x10
	bl FUN_020BCDC4
	b _020BD7C8
_020BD7B4:
	add r0, sp, #0x10
	mov r1, r8
	mov r3, r9
	add r2, r4, #0x10
	bl FUN_020BCF70
_020BD7C8:
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #0x14]
	str r1, [sp, #0x20]
	str r0, [sp, #0x2c]
	b _020BD814
_020BD7DC:
	ldr r0, [r4, #0x10]
	str r0, [sp, #0x20]
	ldr r0, [r4, #0x14]
	str r0, [sp, #0x2c]
	b _020BD814
_020BD7F0:
	ands r0, r5, #0x200
	ldrne r0, [r7, #0x0]
	orrne r0, r0, #0x1
	strne r0, [r7, #0x0]
	bne _020BD814
	mov r0, r7
	bl FUN_020BD9A4
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,pc}
_020BD814:
	ldr r0, [r7, #0x0]
	add r1, sp, #0x18
	ands r0, r0, #0x1
	ldr r0, _020BD84C ; =0x021CEF7C
	movne r3, #0x4
	ldr r4, [r0, #0x0]
	moveq r3, #0x0
	ldr r2, [r4, #0x0]
	ldr r4, [r4, #0xe8]
	mov r0, r7
	blx r4
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020BD848: .word 0x00000FFF
_020BD84C: .word 0x021CEF7C

	arm_func_start FUN_020BD850
FUN_020BD850: ; 0x020BD850
	stmdb sp!, {r4-r8,lr}
	ldr r1, _020BD990 ; =0x021CEF7C
	mov r8, r0
	ldr r0, [r1, #0x0]
	ldr r3, [r0, #0xd4]
	ldr r0, [r0, #0x0]
	ldrh r2, [r3, #0x6]
	ldrb r0, [r0, #0x1]
	ldrh r1, [r3, r2]
	add r2, r3, r2
	mla r0, r1, r0, r2
	ldr r0, [r0, #0x4]
	ldrh r2, [r3, r0]
	add r4, r3, r0
	add r1, r4, #0x4
	ands r0, r2, #0x1
	addeq r1, r1, #0xc
	ands r0, r2, #0x2
	bne _020BD980
	ands r0, r2, #0x8
	beq _020BD934
	and r2, r2, #0xf0
	add r0, r8, #0x28
	mov r5, r2, asr #0x4
	ldrsh r7, [r1, #0x0]
	ldrsh r6, [r1, #0x2]
	blx MI_Zero36B
	ldrh r0, [r4, #0x0]
	add r1, r8, r5, lsl #0x2
	ands r0, r0, #0x100
	movne r0, #0x1000
	rsbne r2, r0, #0x0
	moveq r2, #0x1000
	ldr r0, _020BD994 ; =0x020FFA14
	str r2, [r1, #0x28]
	ldrb r1, [r0, r5, lsl #0x2]
	ldr r0, _020BD998 ; =0x020FFA15
	add r1, r8, r1, lsl #0x2
	str r7, [r1, #0x28]
	ldrb r0, [r0, r5, lsl #0x2]
	add r0, r8, r0, lsl #0x2
	str r6, [r0, #0x28]
	ldrh r0, [r4, #0x0]
	ands r0, r0, #0x200
	ldr r0, _020BD99C ; =0x020FFA16
	rsbne r6, r6, #0x0
	ldrb r0, [r0, r5, lsl #0x2]
	add r0, r8, r0, lsl #0x2
	str r6, [r0, #0x28]
	ldrh r0, [r4, #0x0]
	ands r0, r0, #0x400
	ldr r0, _020BD9A0 ; =0x020FFA17
	rsbne r7, r7, #0x0
	ldrb r0, [r0, r5, lsl #0x2]
	add r0, r8, r0, lsl #0x2
	str r7, [r0, #0x28]
	ldmia sp!, {r4-r8,pc}
_020BD934:
	ldrsh r0, [r4, #0x2]
	str r0, [r8, #0x28]
	ldrsh r0, [r1, #0x0]
	str r0, [r8, #0x2c]
	ldrsh r0, [r1, #0x2]
	str r0, [r8, #0x30]
	ldrsh r0, [r1, #0x4]
	str r0, [r8, #0x34]
	ldrsh r0, [r1, #0x6]
	str r0, [r8, #0x38]
	ldrsh r0, [r1, #0x8]
	str r0, [r8, #0x3c]
	ldrsh r0, [r1, #0xa]
	str r0, [r8, #0x40]
	ldrsh r0, [r1, #0xc]
	str r0, [r8, #0x44]
	ldrsh r0, [r1, #0xe]
	str r0, [r8, #0x48]
	ldmia sp!, {r4-r8,pc}
_020BD980:
	ldr r0, [r8, #0x0]
	orr r0, r0, #0x2
	str r0, [r8, #0x0]
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020BD990: .word 0x021CEF7C
_020BD994: .word 0x020FFA14
_020BD998: .word 0x020FFA15
_020BD99C: .word 0x020FFA16
_020BD9A0: .word 0x020FFA17

	arm_func_start FUN_020BD9A4
FUN_020BD9A4: ; 0x020BD9A4
	stmdb sp!, {r4,lr}
	ldr r1, _020BDA04 ; =0x021CEF7C
	ldr r12, [r1, #0x0]
	ldr r4, [r12, #0xd4]
	ldr r2, [r12, #0x0]
	ldrh lr, [r4, #0x6]
	ldrb r1, [r2, #0x1]
	ldrh r3, [r4, lr]
	add lr, r4, lr
	mla r1, r3, r1, lr
	ldr r1, [r1, #0x4]
	ldrh r3, [r4, r1]
	add r1, r4, r1
	add r1, r1, #0x4
	ands lr, r3, #0x1
	addeq r1, r1, #0xc
	ands lr, r3, #0x2
	bne _020BD9F8
	ands lr, r3, #0x8
	addne r1, r1, #0x4
	addeq r1, r1, #0x10
_020BD9F8:
	ldr r12, [r12, #0xe8]
	blx r12
	ldmia sp!, {r4,pc}
	.balign 4
_020BDA04: .word 0x021CEF7C

	arm_func_start FUN_020BDA08
FUN_020BDA08: ; 0x020BDA08
	ldr r1, _020BDA6C ; =0x021CEF7C
	ldr r1, [r1, #0x0]
	ldr r12, [r1, #0xd4]
	ldr r1, [r1, #0x0]
	ldrh r3, [r12, #0x6]
	ldrb r1, [r1, #0x1]
	ldrh r2, [r12, r3]
	add r3, r12, r3
	mla r1, r2, r1, r3
	ldr r2, [r1, #0x4]
	ldrh r1, [r12, r2]
	add r2, r12, r2
	ands r1, r1, #0x1
	ldrne r1, [r0, #0x0]
	orrne r1, r1, #0x4
	strne r1, [r0, #0x0]
	bxne lr
	ldr r1, [r2, #0x4]
	add r2, r2, #0x4
	str r1, [r0, #0x4c]
	ldr r1, [r2, #0x4]
	str r1, [r0, #0x50]
	ldr r1, [r2, #0x8]
	str r1, [r0, #0x54]
	bx lr
	.balign 4
_020BDA6C: .word 0x021CEF7C

	arm_func_start FUN_020BDA70
FUN_020BDA70: ; 0x020BDA70
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r3, r0
	ldr r0, [r1, #0x8]
	ldr r12, [r1, #0x0]
	ldrh r1, [r0, #0x4]
	mov r1, r1, lsl #0xc
	cmp r12, r1
	subge r12, r1, #0x1
	bge _020BDAA0
	cmp r12, #0x0
	movlt r12, #0x0
_020BDAA0:
	mov r1, r2
	mov r2, r12
	bl FUN_020BD470
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020BDAB4
FUN_020BDAB4: ; 0x020BDAB4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	ldr r0, _020BDB3C ; =0x0210659C
	str r4, [r5, #0x8]
	ldr r0, [r0, #0x0]
	add r1, r5, #0x1a
	str r0, [r5, #0xc]
	ldrb r2, [r2, #0x17]
	mov r0, #0x0
	strb r2, [r5, #0x19]
	ldrb r2, [r5, #0x19]
	mov r2, r2, lsl #0x1
	bl MIi_CpuClear16
	ldrh r0, [r4, #0x6]
	add r2, r4, #0x14
	mov r3, #0x0
	cmp r0, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r5,pc}
_020BDB08:
	mov r0, r3, lsl #0x1
	ldrh r1, [r2, r0]
	add r0, r5, r3, lsl #0x1
	add r3, r3, #0x1
	ldr r1, [r4, r1]
	mov r1, r1, lsr #0x18
	orr r1, r1, #0x100
	strh r1, [r0, #0x1a]
	ldrh r0, [r4, #0x6]
	cmp r3, r0
	blo _020BDB08
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020BDB3C: .word 0x0210659C

	arm_func_start FUN_020BDB40
FUN_020BDB40: ; 0x020BDB40
	stmdb sp!, {r4-r8,lr}
	ldr r7, [r1, #0x8]
	mov r2, r2, lsl #0x10
	ldrh r4, [r7, #0xe]
	add r5, r7, #0x8
	ldr r6, [r1, #0x0]
	ldrh r3, [r5, r4]
	mov r1, r2, lsr #0x10
	add r2, r5, r4
	mul r4, r3, r1
	add r3, r2, #0x4
	mov r6, r6, asr #0xc
	mov r8, r0
	ldr r1, [r3, r4]
	mov r0, r7
	mov r2, r6
	add r5, r3, r4
	bl FUN_020BDDAC
	mov r4, r0
	ldr r1, [r5, #0x4]
	mov r0, r7
	mov r2, r6
	bl FUN_020BDDAC
	ldr r1, [r8, #0x4]
	mov r2, r6
	and r1, r1, #0x8000
	orr r1, r1, r4
	orr r0, r1, r0, lsl #0x10
	str r0, [r8, #0x4]
	mov r0, r7
	ldr r1, [r5, #0xc]
	bl FUN_020BDDAC
	mov r4, r0
	mov r0, r7
	ldr r1, [r5, #0x8]
	mov r2, r6
	bl FUN_020BDDAC
	mov r2, r6
	ldr r1, [r8, #0x8]
	and r1, r1, #0x8000
	orr r0, r1, r0
	orr r0, r0, r4, lsl #0x10
	str r0, [r8, #0x8]
	mov r0, r7
	ldr r1, [r5, #0x10]
	bl FUN_020BDCB8
	ldr r1, [r8, #0xc]
	bic r1, r1, #0x1f0000
	orr r0, r1, r0, lsl #0x10
	str r0, [r8, #0xc]
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020BDC0C
FUN_020BDC0C: ; 0x020BDC0C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r3, _020BDCB4 ; =0x021065A8
	ldr r4, [r2, #0x8]
	ldr r3, [r3, #0x0]
	mov r9, r0
	str r3, [r9, #0xc]
	ldrb r0, [r2, #0x18]
	mov r8, r1
	add r4, r2, r4
	strb r0, [r9, #0x19]
	ldrb r2, [r9, #0x19]
	add r1, r9, #0x1a
	mov r0, #0x0
	mov r2, r2, lsl #0x1
	bl MIi_CpuClear16
	ldrb r0, [r8, #0x9]
	mov r7, #0x0
	cmp r0, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r9,pc}
_020BDC60: ; 0x020BDC60
	mov r6, r7
	add r5, r8, #0x8
	add r4, r4, #0x4
_020BDC6C:
	ldrh r1, [r8, #0xe]
	mov r0, r4
	add r2, r5, r1
	ldrh r1, [r2, #0x2]
	add r1, r2, r1
	add r1, r1, r6
	bl FUN_020BC14C
_020BDC88: ; 0x020BDC88
	cmp r0, #0x0
	orrge r1, r7, #0x100
	addge r0, r9, r0, lsl #0x1
	strgeh r1, [r0, #0x1a]
	ldrb r0, [r8, #0x9]
	add r7, r7, #0x1
	add r6, r6, #0x10
	cmp r7, r0
	blo _020BDC6C
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020BDCB4: .word 0x021065A8

	arm_func_start FUN_020BDCB8
FUN_020BDCB8: ; 0x020BDCB8
	ands r3, r1, #0x20000000
	movne r0, r1, lsl #0x10
	movne r0, r0, lsr #0x10
	bxne lr
	ldr r3, _020BDDA4 ; =0x0000FFFF
	ands r12, r1, #0xc0000000
	and r3, r1, r3
	add r0, r0, r3
	ldreqb r0, [r0, r2]
	bxeq lr
	ldr r3, _020BDDA8 ; =0x1FFF0000
	ands r12, r1, #0x40000000
	and r1, r1, r3
	mov r3, r1, lsr #0x10
	beq _020BDD30
	ands r1, r2, #0x1
	beq _020BDD28
	cmp r2, r3
	addhi r0, r0, r3, lsr #0x1
	ldrhib r0, [r0, #0x1]
	bxhi lr
	add r1, r0, r2, lsr #0x1
	ldrb r2, [r0, r2, lsr #0x1]
	ldrb r0, [r1, #0x1]
	add r0, r2, r0
	mov r0, r0, lsl #0xf
	mov r0, r0, lsr #0x10
	bx lr
_020BDD28:
	ldrb r0, [r0, r2, lsr #0x1]
	bx lr
_020BDD30:
	ands r1, r2, #0x3
	beq _020BDD9C
	cmp r2, r3
	addhi r0, r0, r3, lsr #0x2
	ldrhib r0, [r1, r0]
	bxhi lr
	ands r1, r2, #0x1
	beq _020BDD80
	ands r1, r2, #0x2
	movne r1, r2, lsr #0x2
	addne r2, r1, #0x1
	moveq r2, r2, lsr #0x2
	addeq r1, r2, #0x1
	ldrb r2, [r0, r2]
	ldrb r1, [r0, r1]
	mov r0, #0x3
	mla r0, r2, r0, r1
	mov r0, r0, lsl #0xe
	mov r0, r0, lsr #0x10
	bx lr
_020BDD80:
	add r1, r0, r2, lsr #0x2
	ldrb r2, [r0, r2, lsr #0x2]
	ldrb r0, [r1, #0x1]
	add r0, r2, r0
	mov r0, r0, lsl #0xf
	mov r0, r0, lsr #0x10
	bx lr
_020BDD9C:
	ldrb r0, [r0, r2, lsr #0x2]
	bx lr
	.balign 4
_020BDDA4: .word 0x0000FFFF
_020BDDA8: .word 0x1FFF0000

	arm_func_start FUN_020BDDAC
FUN_020BDDAC: ; 0x020BDDAC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ands r3, r1, #0x20000000
	movne r0, r1, lsl #0x10
	addne sp, sp, #0x4
	movne r0, r0, lsr #0x10
	ldmneia sp!, {pc}
	ldr r3, _020BDF2C ; =0x0000FFFF
	ands r12, r1, #0xc0000000
	and r3, r1, r3
	add r0, r0, r3
	moveq r1, r2, lsl #0x1
	addeq sp, sp, #0x4
	ldreqh r0, [r0, r1]
	ldmeqia sp!, {pc}
	ldr r3, _020BDF30 ; =0x1FFF0000
	ands r12, r1, #0x40000000
	and r1, r1, r3
	mov r3, r1, lsr #0x10
	beq _020BDE34
	ands r1, r2, #0x1
	beq _020BDE24
	cmp r2, r3
	bichi r1, r3, #0x1
	addhi r0, r0, r1
	addhi sp, sp, #0x4
	ldrhih r0, [r0, #0x2]
	ldmhiia sp!, {pc}
	mov r1, r2, lsr #0x1
	b _020BDEE0
_020BDE24:
	bic r1, r2, #0x1
	add sp, sp, #0x4
	ldrh r0, [r0, r1]
	ldmia sp!, {pc}
_020BDE34:
	ands r1, r2, #0x3
	beq _020BDECC
	cmp r2, r3
	movhi r2, r3, lsr #0x2
	movhi r1, r1, lsl #0x1
	addhi r0, r0, r2, lsl #0x1
	addhi sp, sp, #0x4
	ldrhih r0, [r1, r0]
	ldmhiia sp!, {pc}
	ands r1, r2, #0x1
	beq _020BDEC4
	ands r1, r2, #0x2
	movne r1, r2, lsr #0x2
	addne r2, r1, #0x1
	moveq r2, r2, lsr #0x2
	addeq r1, r2, #0x1
	mov r2, r2, lsl #0x1
	mov r1, r1, lsl #0x1
	ldrh r12, [r0, r2]
	ldrh lr, [r0, r1]
	ldr r0, _020BDF34 ; =0x00007C1F
	and r3, r12, #0x3e0
	and r2, lr, #0x3e0
	mov r1, #0x3
	mla r2, r3, r1, r2
	and r12, r12, r0
	and r3, lr, r0
	mla r1, r12, r1, r3
	mov r2, r2, lsr #0x2
	and r1, r0, r1, lsr #0x2
	and r0, r2, #0x3e0
	orr r0, r1, r0
	mov r0, r0, lsl #0x10
	add sp, sp, #0x4
	mov r0, r0, lsr #0x10
	ldmia sp!, {pc}
_020BDEC4:
	mov r1, r2, lsr #0x2
	b _020BDEE0
_020BDECC:
	mov r1, r2, lsr #0x2
	mov r1, r1, lsl #0x1
	add sp, sp, #0x4
	ldrh r0, [r0, r1]
	ldmia sp!, {pc}
_020BDEE0:
	mov r2, r1, lsl #0x1
	add r1, r0, r1, lsl #0x1
	ldrh r3, [r0, r2]
	ldrh r12, [r1, #0x2]
	ldr r0, _020BDF34 ; =0x00007C1F
	and r2, r3, #0x3e0
	and r1, r12, #0x3e0
	add r1, r2, r1
	mov r1, r1, lsr #0x1
	and r3, r3, r0
	and r2, r12, r0
	add r2, r3, r2
	and r2, r0, r2, lsr #0x1
	and r0, r1, #0x3e0
	orr r0, r2, r0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020BDF2C: .word 0x0000FFFF
_020BDF30: .word 0x1FFF0000
_020BDF34: .word 0x00007C1F

	arm_func_start FUN_020BDF38
FUN_020BDF38: ; 0x020BDF38
	stmdb sp!, {r4,lr}
	ldr r12, [r1, #0x0]
	mov r4, r0
	mov r2, r2, lsl #0x10
	ldr r0, [r1, #0x8]
	mov r1, r2, lsr #0x10
	mov r3, r4
	mov r2, r12, asr #0xc
	bl FUN_020BE030
	ldr r0, [r4, #0x10]
	bic r0, r0, #0xc0000000
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x10]
	orr r0, r0, #0x40000000
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x0]
	orr r0, r0, #0x8
	str r0, [r4, #0x0]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020BDF84
FUN_020BDF84: ; 0x020BDF84
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r3, _020BE02C ; =0x021065A0
	ldr r4, [r2, #0x8]
	ldr r3, [r3, #0x0]
	mov r9, r0
	str r3, [r9, #0xc]
	ldrb r0, [r2, #0x18]
	mov r8, r1
	add r4, r2, r4
	strb r0, [r9, #0x19]
	ldrb r2, [r9, #0x19]
	add r1, r9, #0x1a
	mov r0, #0x0
	mov r2, r2, lsl #0x1
	bl MIi_CpuClear16
	ldrb r0, [r8, #0x9]
	mov r7, #0x0
	cmp r0, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r9,pc}
_020BDFD8: ; 0x020BDFD8
	mov r6, r7
	add r5, r8, #0x8
	add r4, r4, #0x4
_020BDFE4:
	ldrh r1, [r8, #0xe]
	mov r0, r4
	add r2, r5, r1
	ldrh r1, [r2, #0x2]
	add r1, r2, r1
	add r1, r1, r6
	bl FUN_020BC14C
_020BE000: ; 0x020BE000
	cmp r0, #0x0
	orrge r1, r7, #0x100
	addge r0, r9, r0, lsl #0x1
	strgeh r1, [r0, #0x1a]
	ldrb r0, [r8, #0x9]
	add r7, r7, #0x1
	add r6, r6, #0x10
	cmp r7, r0
	blo _020BDFE4
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020BE02C: .word 0x021065A0

	arm_func_start FUN_020BE030
FUN_020BE030: ; 0x020BE030
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r8, r0
	ldrh r4, [r8, #0xe]
	add r5, r8, #0x8
	mov r6, r3
	ldrh r3, [r5, r4]
	add r4, r5, r4
	add r4, r4, #0x4
	mla r5, r3, r1, r4
	mov r7, r2
	ldr r1, [r5, #0x18]
	ldr r2, [r5, #0x1c]
	mov r3, r7
	ldr r4, [r6, #0x0]
	bl FUN_020BE238
	mov r9, r0
	ldr r1, [r5, #0x20]
	mov r0, r8
	ldr r2, [r5, #0x24]
	mov r3, r7
	bl FUN_020BE238
_020BE088: ; 0x020BE088
	cmp r9, #0x0
	bne _020BE09C
	cmp r0, #0x0
	orreq r4, r4, #0x4
	beq _020BE0A8
_020BE09C:
	str r9, [r6, #0x24]
	str r0, [r6, #0x28]
	bic r4, r4, #0x4
_020BE0A8:
	ldr r1, [r5, #0x10]
	ldr r2, [r5, #0x14]
	mov r0, r8
	mov r3, r7
	bl FUN_020BE12C
	cmp r0, #0x10000000
	strneh r0, [r6, #0x20]
	movne r0, r0, lsr #0x10
	strneh r0, [r6, #0x22]
	orreq r4, r4, #0x2
	ldr r1, [r5, #0x0]
	ldr r2, [r5, #0x4]
	mov r0, r8
	mov r3, r7
	bicne r4, r4, #0x2
	bl FUN_020BE238
	mov r9, r0
	ldr r1, [r5, #0x8]
	ldr r2, [r5, #0xc]
	mov r0, r8
	mov r3, r7
	bl FUN_020BE238
	cmp r9, #0x1000
	bne _020BE114
	cmp r0, #0x1000
	orreq r4, r4, #0x1
	beq _020BE120
_020BE114:
	str r9, [r6, #0x18]
	str r0, [r6, #0x1c]
	bic r4, r4, #0x1
_020BE120:
	str r4, [r6, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}

	arm_func_start FUN_020BE12C
FUN_020BE12C: ; 0x020BE12C
	ands r12, r1, #0x20000000
	movne r0, r2
	bxne lr
	add r0, r0, r2
	ands r2, r1, #0xc0000000
	beq _020BE1F8
	ldr r2, _020BE234 ; =0x0000FFFF
	ands r12, r1, #0x40000000
	and r2, r1, r2
	beq _020BE17C
	ands r1, r3, #0x1
	beq _020BE174
	cmp r3, r2
	movhi r1, r2, lsr #0x1
	addhi r3, r1, #0x1
	bhi _020BE1F8
	mov r2, r3, lsr #0x1
	b _020BE200
_020BE174:
	mov r3, r3, lsr #0x1
	b _020BE1F8
_020BE17C:
	ands r1, r3, #0x3
	beq _020BE1F4
	cmp r3, r2
	addhi r3, r1, r2, lsr #0x2
	bhi _020BE1F8
	ands r1, r3, #0x1
	beq _020BE1EC
	ands r1, r3, #0x2
	movne r1, r3, lsr #0x2
	addne r2, r1, #0x1
	moveq r2, r3, lsr #0x2
	addeq r1, r2, #0x1
	mov r12, r2, lsl #0x2
	add r3, r0, r2, lsl #0x2
	mov r2, r1, lsl #0x2
	add r1, r0, r1, lsl #0x2
	ldrsh r12, [r0, r12]
	ldrsh r2, [r0, r2]
	mov r0, #0x3
	ldrsh r3, [r3, #0x2]
	ldrsh r1, [r1, #0x2]
	mla r2, r12, r0, r2
	mla r1, r3, r0, r1
	ldr r0, _020BE234 ; =0x0000FFFF
	mov r1, r1, asr #0x2
	and r0, r0, r2, asr #0x2
	orr r0, r0, r1, lsl #0x10
	bx lr
_020BE1EC:
	mov r2, r3, lsr #0x2
	b _020BE200
_020BE1F4:
	mov r3, r3, lsr #0x2
_020BE1F8:
	ldr r0, [r0, r3, lsl #0x2]
	bx lr
_020BE200:
	add r1, r0, r2, lsl #0x2
	mov r2, r2, lsl #0x2
	ldrsh r12, [r0, r2]
	ldrsh r3, [r1, #0x4]
	ldrsh r2, [r1, #0x2]
	ldrsh r1, [r1, #0x6]
	ldr r0, _020BE234 ; =0x0000FFFF
	add r3, r12, r3
	add r1, r2, r1
	and r2, r0, r3, asr #0x1
	mov r0, r1, asr #0x1
	orr r0, r2, r0, lsl #0x10
	bx lr
	.balign 4
_020BE234: .word 0x0000FFFF

	arm_func_start FUN_020BE238
FUN_020BE238:
	ands r12, r1, #0x20000000
	movne r0, r2
	bxne lr
	add r0, r0, r2
	ands r2, r1, #0xc0000000
	beq _020BE2F0
	ldr r2, _020BE330 ; =0x0000FFFF
	ands r12, r1, #0x40000000
	and r12, r1, r2
	beq _020BE288
	ands r2, r3, #0x1
	beq _020BE280
	cmp r3, r12
	movhi r2, r12, lsr #0x1
	addhi r3, r2, #0x1
	bhi _020BE2F0
	mov r3, r3, lsr #0x1
	b _020BE304
_020BE280:
	mov r3, r3, lsr #0x1
	b _020BE2F0
_020BE288:
	ands r2, r3, #0x3
	beq _020BE2EC
	cmp r3, r12
	addhi r3, r2, r12, lsr #0x2
	bhi _020BE2F0
	ands r2, r3, #0x1
	beq _020BE2E4
	ands r2, r3, #0x2
	movne r3, r3, lsr #0x2
	addne r2, r3, #0x1
	moveq r2, r3, lsr #0x2
	addeq r3, r2, #0x1
	ands r1, r1, #0x10000000
	movne r2, r2, lsl #0x1
	movne r1, r3, lsl #0x1
	ldrnesh r2, [r0, r2]
	ldrnesh r1, [r0, r1]
	ldreq r2, [r0, r2, lsl #0x2]
	ldreq r1, [r0, r3, lsl #0x2]
	mov r0, #0x3
	mla r0, r2, r0, r1
	mov r0, r0, asr #0x2
	bx lr
_020BE2E4:
	mov r3, r3, lsr #0x2
	b _020BE304
_020BE2EC:
	mov r3, r3, lsr #0x2
_020BE2F0:
	ands r1, r1, #0x10000000
	movne r1, r3, lsl #0x1
	ldrnesh r0, [r0, r1]
	ldreq r0, [r0, r3, lsl #0x2]
	bx lr
_020BE304:
	ands r1, r1, #0x10000000
	movne r2, r3, lsl #0x1
	addne r1, r0, r3, lsl #0x1
	ldrnesh r2, [r0, r2]
	ldrnesh r0, [r1, #0x2]
	addeq r1, r0, r3, lsl #0x2
	ldreq r2, [r0, r3, lsl #0x2]
	ldreq r0, [r1, #0x4]
	add r0, r2, r0
	mov r0, r0, asr #0x1
	bx lr
	.balign 4
_020BE330: .word 0x0000FFFF

	arm_func_start FUN_020BE334
FUN_020BE334: ; 0x020BE334
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	ldr r3, [r6, #0x0]
	ldr r5, [r6, #0x8]
	mov r1, r2, lsl #0x10
	mov r2, r3, lsl #0x4
	mov r7, r0
	mov r0, r5
	mov r1, r1, lsr #0x10
	mov r2, r2, lsr #0x10
	bl FUN_020BC42C
	mov r4, r0
	ldrb r1, [r4, #0x2]
	mov r0, r5
	bl FUN_020BC4B8
	mov r1, r0
	ldr r0, [r6, #0x14]
	mov r2, r7
	bl FUN_020BE408
	ldrb r1, [r4, #0x3]
	cmp r1, #0xff
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
_020BE394: ; 0x020BE394
	mov r0, r5
	bl FUN_020BC4A8
	mov r1, r0
	ldr r0, [r6, #0x14]
	mov r2, r7
	bl FUN_020BE3B4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020BE3B4
FUN_020BE3B4: ; 0x020BE3B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrh r0, [r5, #0x34]
	mov r4, r2
	add r0, r5, r0
	bl FUN_020BC2A0
	ldr r1, [r5, #0x2c]
	ldrh r2, [r0, #0x2]
	mov r1, r1, lsl #0x10
	mov r3, r1, lsr #0x10
	ands r1, r2, #0x1
	ldrh r0, [r0, #0x0]
	moveq r1, r3, lsl #0xf
	moveq r3, r1, lsr #0x10
	moveq r0, r0, lsl #0xf
	moveq r0, r0, lsr #0x10
	add r0, r0, r3
	str r0, [r4, #0x14]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020BE408
FUN_020BE408: ; 0x020BE408
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	add r0, r5, #0x3c
	mov r4, r2
	bl FUN_020BC2A0
	ldr r1, [r0, #0x0]
	ldr r3, [r4, #0x10]
	and r1, r1, #0x1c000000
	cmp r1, #0x14000000
	ldrne r2, [r5, #0x8]
	ldrne r1, _020BE4E0 ; =0x0000FFFF
	andne r5, r2, r1
	ldreq r2, [r5, #0x18]
	ldreq r1, _020BE4E0 ; =0x0000FFFF
	andeq r5, r2, r1
	ldr r1, _020BE4E4 ; =0xC00F0000
	ldr r2, _020BE4E8 ; =0x000007FF
	and r1, r3, r1
	str r1, [r4, #0x10]
	ldr r1, [r0, #0x0]
	ldr r3, [r4, #0x10]
	add r1, r1, r5
	orr r1, r3, r1
	str r1, [r4, #0x10]
	ldr r3, [r0, #0x4]
	ldr r1, _020BE4EC ; =0x003FF800
	and r3, r3, r2
	strh r3, [r4, #0x2c]
	ldr r3, [r0, #0x4]
	and r1, r3, r1
	mov r1, r1, lsr #0xb
	strh r1, [r4, #0x2e]
	ldr r3, [r0, #0x4]
	ldrh r1, [r4, #0x2c]
	and r0, r3, r2
	and r5, r2, r3, lsr #0xb
	cmp r0, r1
	moveq r0, #0x1000
	beq _020BE4B4
	mov r0, r0, lsl #0xc
	mov r1, r1, lsl #0xc
	bl FX_Div
_020BE4B4:
	str r0, [r4, #0x30]
	ldrh r1, [r4, #0x2e]
	cmp r5, r1
	moveq r0, #0x1000
	beq _020BE4D4
	mov r0, r5, lsl #0xc
	mov r1, r1, lsl #0xc
	bl FX_Div
_020BE4D4:
	str r0, [r4, #0x34]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020BE4E0: .word 0x0000FFFF
_020BE4E4: .word 0xC00F0000
_020BE4E8: .word 0x000007FF
_020BE4EC: .word 0x003FF800

	arm_func_start FUN_020BE4F0
FUN_020BE4F0: ; 0x020BE4F0
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r3, _020BE59C ; =0x021065A4
	ldr r4, [r2, #0x8]
	ldr r3, [r3, #0x0]
	mov r9, r0
	str r3, [r9, #0xc]
	ldrb r0, [r2, #0x18]
	mov r8, r1
	add r4, r2, r4
	strb r0, [r9, #0x19]
	str r8, [r9, #0x8]
	ldrb r2, [r9, #0x19]
	add r1, r9, #0x1a
	mov r0, #0x0
	mov r2, r2, lsl #0x1
	bl MIi_CpuClear16
	ldrb r0, [r8, #0xd]
	mov r7, #0x0
	cmp r0, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r9,pc}
_020BE548: ; 0x020BE548
	mov r6, r7
	add r5, r8, #0xc
	add r4, r4, #0x4
_020BE554:
	ldrh r1, [r8, #0x12]
	mov r0, r4
	add r2, r5, r1
	ldrh r1, [r2, #0x2]
	add r1, r2, r1
	add r1, r1, r6
	bl FUN_020BC14C
_020BE570: ; 0x020BE570
	cmp r0, #0x0
	orrge r1, r7, #0x100
	addge r0, r9, r0, lsl #0x1
	strgeh r1, [r0, #0x1a]
	ldrb r0, [r8, #0xd]
	add r7, r7, #0x1
	add r6, r6, #0x10
	cmp r7, r0
	blo _020BE554
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020BE59C: .word 0x021065A4

	arm_func_start FUN_020BE5A0
FUN_020BE5A0: ; 0x020BE5A0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr lr, [r1, #0x8]
	ldr r3, [r1, #0x0]
	ldrh r1, [lr, #0x6]
	mov r12, r3, asr #0xc
	mov r3, #0x1
	mla r2, r12, r1, r2
	mov r1, r2, lsr #0x5
	add r1, lr, r1, lsl #0x2
	ldr r1, [r1, #0xc]
	and r2, r2, #0x1f
	and r1, r1, r3, lsl r2
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020BE5E0
FUN_020BE5E0: ; 0x020BE5E0
	ldr r3, _020BE628 ; =0x02106598
	mov r12, #0x0
	ldr r3, [r3, #0x0]
	str r3, [r0, #0xc]
	ldrb r2, [r2, #0x17]
	strb r2, [r0, #0x19]
	str r1, [r0, #0x8]
	ldrb r1, [r0, #0x19]
	cmp r1, #0x0
	bxls lr
_020BE608:
	orr r2, r12, #0x100
	add r1, r0, r12, lsl #0x1
	strh r2, [r1, #0x1a]
	ldrb r1, [r0, #0x19]
	add r12, r12, #0x1
	cmp r12, r1
	blo _020BE608
	bx lr
	.balign 4
_020BE628: .word 0x02106598

	arm_func_start FUN_020BE62C
FUN_020BE62C: ; 0x020BE62C
	ands r2, r3, #0x4
	ldrne r1, [r0, #0x0]
	orrne r1, r1, #0x1
	strne r1, [r0, #0x0]
	bne _020BE658

	arm_func_start FUN_020BE640
FUN_020BE640: ; 0x020BE640
	ldr r2, [r1, #0x0]
	str r2, [r0, #0x4]
	ldr r2, [r1, #0x4]
	str r2, [r0, #0x8]
	ldr r1, [r1, #0x8]
	str r1, [r0, #0xc]
_020BE658:
	ldr r1, [r0, #0x0]
	orr r1, r1, #0x18
	str r1, [r0, #0x0]
	bx lr

	arm_func_start FUN_020BE668
FUN_020BE668: ; 0x020BE668
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r1, [r4, #0x0]
	ands r0, r1, #0x4
	bne _020BE6AC
	ands r0, r1, #0x2
	bne _020BE698
	add r1, r4, #0x28
	mov r0, #0x19
	mov r2, #0xc
	bl FUN_020BB1C0
	b _020BE6C4
_020BE698:
	add r1, r4, #0x4c
	mov r0, #0x1c
	mov r2, #0x3
	bl FUN_020BB1C0
	b _020BE6C4
_020BE6AC:
	ands r0, r1, #0x2
	bne _020BE6C4
	add r1, r4, #0x28
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
_020BE6C4:
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x1
	ldmneia sp!, {r4,pc}
_020BE6D0: ; 0x020BE6D0
	add r1, r4, #0x4
	mov r0, #0x1b
	mov r2, #0x3
	bl FUN_020BB1C0
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020BE6E4
FUN_020BE6E4: ; 0x020BE6E4
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x50
	mov r4, r0
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	ands r0, r0, #0x8
	ldrne r0, _020BE820 ; =0x00101610
	mov r3, #0x3
	strne r0, [sp, #0x0]
	ldreq r0, _020BE824 ; =0x00101810
	mov r2, #0x2
	streq r0, [sp, #0x0]
	mov r0, #0x1000
	str r0, [sp, #0x44]
	str r3, [sp, #0x4]
	str r2, [sp, #0x48]
	str r1, [sp, #0x40]
	str r1, [sp, #0x34]
	str r1, [sp, #0x30]
	str r1, [sp, #0x2c]
	str r1, [sp, #0x28]
	str r1, [sp, #0x24]
	str r1, [sp, #0x20]
	str r1, [sp, #0x14]
	str r1, [sp, #0x10]
	ldr r1, [r4, #0x0]
	ldr r0, _020BE828 ; =0x021067B0
	and r1, r1, #0x7
	ldr r2, [r0, r1, lsl #0x2]
	add r0, sp, #0x8
	mov r1, r4
	blx r2
	ldr r3, [r4, #0x30]
	cmp r3, #0x1000
	beq _020BE7B4
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	smull r2, r0, r3, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x8]
	ldr r2, [r4, #0x30]
	ldr r0, [sp, #0x38]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0xc]
	ldr r1, [r4, #0x30]
	smull r2, r0, r1, r0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [sp, #0x38]
_020BE7B4:
	ldr r3, [r4, #0x34]
	cmp r3, #0x1000
	beq _020BE804
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	smull r2, r0, r3, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x18]
	ldr r2, [r4, #0x34]
	ldr r0, [sp, #0x3c]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0x1c]
	ldr r1, [r4, #0x34]
	smull r2, r0, r1, r0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [sp, #0x3c]
_020BE804:
	add r1, sp, #0x0
	ldr r0, [sp, #0x0]
	add r1, r1, #0x4
	mov r2, #0x12
	bl FUN_020BB1C0
	add sp, sp, #0x50
	ldmia sp!, {r4,pc}
	.balign 4
_020BE820: .word 0x00101610
_020BE824: .word 0x00101810
_020BE828: .word 0x021067B0

	arm_func_start FUN_020BE82C
FUN_020BE82C: ; 0x020BE82C
	mov r2, #0x1000
	str r2, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	str r1, [r0, #0x10]
	str r2, [r0, #0x14]
	str r1, [r0, #0x30]
	str r1, [r0, #0x34]
	bx lr

	arm_func_start FUN_020BE850
FUN_020BE850: ; 0x020BE850
	ldr r2, [r1, #0x18]
	mov r12, #0x0
	str r2, [r0, #0x0]
	ldr r2, [r1, #0x1c]
	str r2, [r0, #0x14]
	str r12, [r0, #0x4]
	str r12, [r0, #0x30]
	ldr r2, [r1, #0x1c]
	ldrh r3, [r1, #0x2e]
	mov r1, r2, lsl #0x1
	rsb r1, r1, #0x0
	add r1, r1, #0x2000
	mul r1, r3, r1
	mov r1, r1, lsl #0x3
	str r1, [r0, #0x34]
	str r12, [r0, #0x10]
	bx lr

	arm_func_start FUN_020BE894
FUN_020BE894: ; 0x020BE894
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldrh r2, [r5, #0x2c]
	ldrh r1, [r5, #0x2e]
	mov r6, r0
	mov r4, r2, lsl #0xc
	mov r7, r1, lsl #0xc
	mov r0, r7
	mov r1, r4
	bl FX_DivAsync
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x0]
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x14]
	bl FX_GetDivResult
	ldrsh r2, [r5, #0x20]
	mov r1, r7
	rsb r2, r2, #0x0
	mul r0, r2, r0
	mov r2, r0, asr #0xc
	mov r0, r4
	str r2, [r6, #0x4]
	bl FX_DivAsync
	ldrsh r1, [r5, #0x20]
	ldrsh r0, [r5, #0x22]
	ldrh r2, [r5, #0x2c]
	add r0, r1, r0
	rsb r0, r0, #0x0
	add r0, r0, #0x1000
	mul r0, r2, r0
	mov r0, r0, lsl #0x3
	str r0, [r6, #0x30]
	ldrsh r1, [r5, #0x20]
	ldrsh r0, [r5, #0x22]
	ldrh r2, [r5, #0x2e]
	sub r0, r1, r0
	add r0, r0, #0x1000
	mul r0, r2, r0
	mov r0, r0, lsl #0x3
	str r0, [r6, #0x34]
	bl FX_GetDivResult
	ldrsh r1, [r5, #0x20]
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r6, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020BE954
FUN_020BE954: ; 0x020BE954
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r1
	ldrh r2, [r9, #0x2c]
	ldrh r1, [r9, #0x2e]
	mov r10, r0
	mov r8, r2, lsl #0xc
	mov r11, r1, lsl #0xc
	mov r0, r11
	mov r1, r8
	bl FX_DivAsync
	ldrsh r5, [r9, #0x22]
	ldr r3, [r9, #0x18]
	ldrsh r0, [r9, #0x20]
	ldr r4, [r9, #0x1c]
	smull r2, r1, r3, r5
	mov r6, r2, lsr #0xc
	orr r6, r6, r1, lsl #0x14
	smull r2, r1, r3, r0
	mov r7, r2, lsr #0xc
	orr r7, r7, r1, lsl #0x14
	smull r3, r2, r4, r0
	smull r1, r0, r4, r5
	mov r5, r3, lsr #0xc
	orr r5, r5, r2, lsl #0x14
	mov r4, r1, lsr #0xc
	orr r4, r4, r0, lsl #0x14
	str r6, [r10, #0x0]
	str r4, [r10, #0x14]
	bl FX_GetDivResult
	mov r1, r11
	rsb r2, r5, #0x0
	mul r0, r2, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x4]
	mov r0, r8
	bl FX_DivAsync
	sub r1, r5, r4
	add r0, r7, r6
	ldrh r3, [r9, #0x2c]
	ldr r2, [r9, #0x18]
	sub r0, r2, r0
	mul r0, r3, r0
	mov r0, r0, lsl #0x3
	str r0, [r10, #0x30]
	ldrh r2, [r9, #0x2e]
	ldr r0, [r9, #0x1c]
	sub r0, r1, r0
	add r0, r0, #0x2000
	mul r0, r2, r0
	mov r0, r0, lsl #0x3
	str r0, [r10, #0x34]
	bl FX_GetDivResult
	mul r0, r7, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020BEA3C
FUN_020BEA3C: ; 0x020BEA3C
	mov r2, #0x1000
	str r2, [r0, #0x0]
	str r2, [r0, #0x14]
	mov r12, #0x0
	str r12, [r0, #0x4]
	ldrh r2, [r1, #0x2c]
	ldr r3, [r1, #0x24]
	mul r2, r3, r2
	rsb r2, r2, #0x0
	mov r2, r2, lsl #0x4
	str r2, [r0, #0x30]
	ldrh r2, [r1, #0x2e]
	ldr r1, [r1, #0x28]
	mul r2, r1, r2
	mov r1, r2, lsl #0x4
	str r1, [r0, #0x34]
	str r12, [r0, #0x10]
	bx lr

	arm_func_start FUN_020BEA84
FUN_020BEA84: ; 0x020BEA84
	stmdb sp!, {r4,lr}
	ldr r3, [r1, #0x18]
	mov r2, #0x0
	str r3, [r0, #0x0]
	ldr r3, [r1, #0x1c]
	str r3, [r0, #0x14]
	str r2, [r0, #0x4]
	ldr r4, [r1, #0x18]
	ldr r3, [r1, #0x24]
	ldrh lr, [r1, #0x2c]
	smull r12, r3, r4, r3
	mov r4, r12, lsr #0x8
	orr r4, r4, r3, lsl #0x18
	rsb r3, r4, #0x0
	mul r3, lr, r3
	str r3, [r0, #0x30]
	ldr r4, [r1, #0x1c]
	ldr r12, [r1, #0x28]
	mov r3, r4, lsl #0x1
	smull lr, r12, r4, r12
	rsb r4, r3, #0x0
	mov r3, lr, lsr #0x8
	ldrh lr, [r1, #0x2e]
	add r1, r4, #0x2000
	orr r3, r3, r12, lsl #0x18
	mul r4, lr, r1
	mul r1, lr, r3
	add r1, r1, r4, lsl #0x3
	str r1, [r0, #0x34]
	str r2, [r0, #0x10]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020BEB00
FUN_020BEB00: ; 0x020BEB00
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldrh r2, [r5, #0x2c]
	ldrh r1, [r5, #0x2e]
	mov r6, r0
	mov r4, r2, lsl #0xc
	mov r7, r1, lsl #0xc
	mov r0, r7
	mov r1, r4
	bl FX_DivAsync
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x0]
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x14]
	bl FX_GetDivResult
	ldrsh r2, [r5, #0x20]
	mov r1, r7
	rsb r2, r2, #0x0
	mul r0, r2, r0
	mov r2, r0, asr #0xc
	mov r0, r4
	str r2, [r6, #0x4]
	bl FX_DivAsync
	ldrsh r2, [r5, #0x20]
	ldrsh r1, [r5, #0x22]
	ldrh r3, [r5, #0x2c]
	ldr r0, [r5, #0x24]
	add r1, r2, r1
	rsb r1, r1, #0x0
	add r1, r1, #0x1000
	mul r2, r3, r1
	mul r1, r0, r3
	mov r0, r2, lsl #0x3
	sub r0, r0, r1, lsl #0x4
	str r0, [r6, #0x30]
	ldrsh r2, [r5, #0x20]
	ldrsh r1, [r5, #0x22]
	ldrh r3, [r5, #0x2e]
	ldr r0, [r5, #0x28]
	sub r1, r2, r1
	add r1, r1, #0x1000
	mul r2, r3, r1
	mul r1, r0, r3
	mov r0, r2, lsl #0x3
	add r0, r0, r1, lsl #0x4
	str r0, [r6, #0x34]
	bl FX_GetDivResult
	ldrsh r1, [r5, #0x20]
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r6, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020BEBD8
FUN_020BEBD8: ; 0x020BEBD8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r1
	ldrh r2, [r9, #0x2c]
	ldrh r1, [r9, #0x2e]
	mov r10, r0
	mov r8, r2, lsl #0xc
	mov r11, r1, lsl #0xc
	mov r0, r11
	mov r1, r8
	bl FX_DivAsync
	ldrsh r5, [r9, #0x22]
	ldr r3, [r9, #0x18]
	ldrsh r0, [r9, #0x20]
	ldr r4, [r9, #0x1c]
	smull r2, r1, r3, r5
	mov r6, r2, lsr #0xc
	orr r6, r6, r1, lsl #0x14
	smull r2, r1, r3, r0
	mov r7, r2, lsr #0xc
	orr r7, r7, r1, lsl #0x14
	smull r3, r2, r4, r0
	smull r1, r0, r4, r5
	mov r5, r3, lsr #0xc
	orr r5, r5, r2, lsl #0x14
	mov r4, r1, lsr #0xc
	orr r4, r4, r0, lsl #0x14
	str r6, [r10, #0x0]
	str r4, [r10, #0x14]
	bl FX_GetDivResult
	mov r1, r11
	rsb r2, r5, #0x0
	mul r0, r2, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x4]
	mov r0, r8
	bl FX_DivAsync
	sub r1, r5, r4
	add r2, r7, r6
	ldr r5, [r9, #0x18]
	ldrh r0, [r9, #0x2c]
	sub r3, r5, r2
	ldr r2, [r9, #0x24]
	mul r4, r0, r3
	smull r3, r2, r5, r2
	mov r4, r4, lsl #0x3
	mov r3, r3, lsr #0x8
	orr r3, r3, r2, lsl #0x18
	mul r2, r0, r3
	sub r0, r4, r2
	str r0, [r10, #0x30]
	ldr r4, [r9, #0x1c]
	ldrh r3, [r9, #0x2e]
	sub r0, r1, r4
	add r0, r0, #0x2000
	mul r2, r3, r0
	ldr r0, [r9, #0x28]
	smull r1, r0, r4, r0
	mov r1, r1, lsr #0x8
	orr r1, r1, r0, lsl #0x18
	mul r0, r3, r1
	add r0, r0, r2, lsl #0x3
	str r0, [r10, #0x34]
	bl FX_GetDivResult
	mul r0, r7, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020BECEC
FUN_020BECEC: ; 0x020BECEC
	stmdb sp!, {r4-r8,lr}
	mov r12, r0
	ands r0, r3, #0x4
	ldrb r3, [r2, #0x3]
	beq _020BED40
	ldr r1, [r12, #0x0]
	ands r0, r3, #0x2
	orr r0, r1, #0x1
	str r0, [r12, #0x0]
	beq _020BEDB8
	ldr r0, _020BEE2C ; =0x021CEF7C
	ldrb r7, [r2, #0x1]
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	add r6, r0, #0xc4
	mov r5, r7, lsr #0x5
	ldr r4, [r6, r5, lsl #0x2]
	and r0, r7, #0x1f
	orr r0, r4, r1, lsl r0
	str r0, [r6, r5, lsl #0x2]
	b _020BEDB8
_020BED40:
	ldr r4, [r1, #0x0]
	ands r0, r3, #0x2
	str r4, [r12, #0x4]
	ldr r0, [r1, #0x4]
	str r0, [r12, #0x8]
	ldr r0, [r1, #0x8]
	str r0, [r12, #0xc]
	beq _020BEDB8
	ldr lr, _020BEE2C ; =0x021CEF7C
	ldrb r0, [r2, #0x1]
	ldr r4, [lr, #0x0]
	mov lr, #0x18
	add r8, r4, #0xc4
	mov r7, r0, lsr #0x5
	and r4, r0, #0x1f
	mov r5, #0x1
	mvn r4, r5, lsl r4
	ldr r6, [r8, r7, lsl #0x2]
	mul r5, r0, lr
	and r0, r6, r4
	str r0, [r8, r7, lsl #0x2]
	ldr r4, [r1, #0xc]
	ldr r0, _020BEE30 ; =0x021CFD8C
	ldr lr, _020BEE34 ; =0x021CFD90
	str r4, [r0, r5]
	ldr r4, [r1, #0x10]
	ldr r0, _020BEE38 ; =0x021CFD94
	str r4, [lr, r5]
	ldr r1, [r1, #0x14]
	str r1, [r0, r5]
_020BEDB8:
	ands r0, r3, #0x1
	beq _020BEE1C
	ldrb r0, [r2, #0x2]
	ldr r2, [r12, #0x0]
	ldr r1, _020BEE2C ; =0x021CEF7C
	orr r2, r2, #0x20
	str r2, [r12, #0x0]
	ldr r2, [r1, #0x0]
	mov r1, r0, lsr #0x5
	add r1, r2, r1, lsl #0x2
	and r2, r0, #0x1f
	mov r3, #0x1
	mov r2, r3, lsl r2
	ldr r1, [r1, #0xc4]
	ands r1, r2, r1
	ldrne r0, [r12, #0x0]
	orrne r0, r0, #0x8
	strne r0, [r12, #0x0]
	bne _020BEE1C
	ldr r2, _020BEE30 ; =0x021CFD8C
	mov r1, #0x18
	mla r1, r0, r1, r2
	add r3, r12, #0x10
	ldmia r1, {r0-r2}
	stmia r3, {r0-r2}
_020BEE1C:
	ldr r0, [r12, #0x0]
	orr r0, r0, #0x10
	str r0, [r12, #0x0]
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020BEE2C: .word 0x021CEF7C
_020BEE30: .word 0x021CFD8C
_020BEE34: .word 0x021CFD90
_020BEE38: .word 0x021CFD94

	arm_func_start FUN_020BEE3C
FUN_020BEE3C: ; 0x020BEE3C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r1, [r5, #0x0]
	mov r4, #0x0
	ands r0, r1, #0x4
	moveq r4, #0x1
	ands r0, r1, #0x20
	beq _020BEE94
	ands r0, r1, #0x8
	bne _020BEE94
	cmp r4, #0x0
	beq _020BEE84
	add r1, r5, #0x4c
	mov r0, #0x1c
	mov r2, #0x3
	bl FUN_020BB1C0
	mov r4, #0x0
_020BEE84:
	add r1, r5, #0x10
	mov r0, #0x1b
	mov r2, #0x3
	bl FUN_020BB1C0
_020BEE94:
	ldr r0, [r5, #0x0]
	ands r0, r0, #0x2
	bne _020BEED0
	cmp r4, #0x0
	beq _020BEEBC
	add r1, r5, #0x28
	mov r0, #0x19
	mov r2, #0xc
	bl FUN_020BB1C0
	b _020BEEE8
_020BEEBC:
	add r1, r5, #0x28
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
	b _020BEEE8
_020BEED0:
	cmp r4, #0x0
	beq _020BEEE8
	add r1, r5, #0x4c
	mov r0, #0x1c
	mov r2, #0x3
	bl FUN_020BB1C0
_020BEEE8:
	ldr r0, [r5, #0x0]
	ands r0, r0, #0x1
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,pc}
_020BEEF8: ; 0x020BEEF8
	add r1, r5, #0x4
	mov r0, #0x1b
	mov r2, #0x3
	bl FUN_020BB1C0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020BEF10
FUN_020BEF10: ; 0x020BEF10
	stmdb sp!, {lr}
	sub sp, sp, #0x3c
	ldr r1, [r0, #0x0]
	mov r3, #0x0
	ands r1, r1, #0x8
	ldrne r1, _020BF0CC ; =0x00101710
	mov r2, #0x3
	strne r1, [sp, #0x0]
	ldreq r1, _020BF0D0 ; =0x00101910
	str r3, [sp, #0x34]
	streq r1, [sp, #0x0]
	mov r1, #0x2
	str r1, [sp, #0x38]
	str r3, [sp, #0x28]
	str r3, [sp, #0x24]
	str r3, [sp, #0x20]
	str r3, [sp, #0x1c]
	str r3, [sp, #0x14]
	str r3, [sp, #0x10]
	str r3, [sp, #0xc]
	str r2, [sp, #0x4]
	ldr r2, [r0, #0x0]
	ands r1, r2, #0x4
	beq _020BEFA0
	str r3, [sp, #0x2c]
	str r3, [sp, #0x30]
	ldr r1, [r0, #0x0]
	ands r1, r1, #0x1
	movne r1, #0x1000
	strne r1, [sp, #0x8]
	strne r1, [sp, #0x18]
	ldreq r1, [r0, #0x18]
	streq r1, [sp, #0x8]
	ldreq r1, [r0, #0x1c]
	streq r1, [sp, #0x18]
	b _020BF040
_020BEFA0:
	ands r1, r2, #0x1
	beq _020BEFE8
	ldr r2, [r0, #0x24]
	ldrh r1, [r0, #0x2c]
	mov r2, r2, lsl #0x4
	rsb r2, r2, #0x0
	mul r1, r2, r1
	str r1, [sp, #0x2c]
	ldr r2, [r0, #0x28]
	ldrh r1, [r0, #0x2e]
	mov r2, r2, lsl #0x4
	rsb r2, r2, #0x0
	mul r3, r2, r1
	mov r1, #0x1000
	str r3, [sp, #0x30]
	str r1, [sp, #0x8]
	str r1, [sp, #0x18]
	b _020BF040
_020BEFE8:
	ldr r2, [r0, #0x18]
	ldr r1, [r0, #0x24]
	ldrh r12, [r0, #0x2c]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0x8
	orr r2, r2, r1, lsl #0x18
	rsb r1, r2, #0x0
	mul r1, r12, r1
	str r1, [sp, #0x2c]
	ldr r2, [r0, #0x1c]
	ldr r1, [r0, #0x28]
	ldrh r12, [r0, #0x2e]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0x8
	orr r2, r2, r1, lsl #0x18
	rsb r1, r2, #0x0
	mul r1, r12, r1
	str r1, [sp, #0x30]
	ldr r1, [r0, #0x18]
	str r1, [sp, #0x8]
	ldr r1, [r0, #0x1c]
	str r1, [sp, #0x18]
_020BF040:
	ldr r12, [r0, #0x30]
	cmp r12, #0x1000
	beq _020BF078
	ldr r2, [sp, #0x8]
	ldr r1, [sp, #0x2c]
	smull r3, r2, r12, r2
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	str r3, [sp, #0x8]
	ldr r2, [r0, #0x30]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0x2c]
_020BF078:
	ldr r12, [r0, #0x34]
	cmp r12, #0x1000
	beq _020BF0B0
	ldr r2, [sp, #0x18]
	ldr r1, [sp, #0x30]
	smull r3, r2, r12, r2
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	str r3, [sp, #0x18]
	ldr r0, [r0, #0x34]
	smull r2, r1, r0, r1
	mov r0, r2, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	str r0, [sp, #0x30]
_020BF0B0:
	add r1, sp, #0x0
	ldr r0, [sp, #0x0]
	add r1, r1, #0x4
	mov r2, #0xe
	bl FUN_020BB1C0
	add sp, sp, #0x3c
	ldmia sp!, {pc}
	.balign 4
_020BF0CC: .word 0x00101710
_020BF0D0: .word 0x00101910

	arm_func_start FUN_020BF0D4
FUN_020BF0D4: ; 0x020BF0D4
	stmdb sp!, {r4-r8,lr}
	mov r5, r0
	ands r0, r3, #0x4
	ldrb r4, [r2, #0x1]
	ldrb r0, [r2, #0x2]
	beq _020BF174
	ldr r2, [r5, #0x0]
	ldr r1, _020BF2E0 ; =0x021CEF7C
	orr r2, r2, #0x1
	str r2, [r5, #0x0]
	ldr r3, [r1, #0x0]
	mov r1, r0, lsr #0x5
	add r1, r3, r1, lsl #0x2
	and r2, r0, #0x1f
	mov r6, #0x1
	mov r2, r6, lsl r2
	ldr r1, [r1, #0xc4]
	ands r1, r2, r1
	beq _020BF148
	add r3, r3, #0xc4
	mov r2, r4, lsr #0x5
	ldr r1, [r3, r2, lsl #0x2]
	and r0, r4, #0x1f
	orr r0, r1, r6, lsl r0
	str r0, [r3, r2, lsl #0x2]
	ldr r0, [r5, #0x0]
	orr r0, r0, #0x18
	str r0, [r5, #0x0]
	ldmia sp!, {r4-r8,pc}
_020BF148:
	ldr r1, _020BF2E4 ; =0x021CFD80
	mov r2, #0x18
	mla r6, r0, r2, r1
	mla r1, r4, r2, r1
	mov r0, r6
	bl MIi_CpuCopy32
	mov r0, r6
	add r1, r5, #0x10
	mov r2, #0x18
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r8,pc}
_020BF174:
	ldr r3, [r1, #0x0]
	ldr r2, _020BF2E0 ; =0x021CEF7C
	str r3, [r5, #0x4]
	ldr r3, [r1, #0x4]
	mov r7, r0, lsr #0x5
	str r3, [r5, #0x8]
	ldr r3, [r1, #0x8]
	and r8, r0, #0x1f
	str r3, [r5, #0xc]
	ldr r6, [r2, #0x0]
	mov r3, #0x1
	add r2, r6, r7, lsl #0x2
	mov r7, r3, lsl r8
	ldr r2, [r2, #0xc4]
	ands r2, r7, r2
	beq _020BF200
	ldr r3, _020BF2E4 ; =0x021CFD80
	mov r2, #0x18
	mov r0, r1
	mla r1, r4, r2, r3
	bl MIi_CpuCopy32
	ldr r0, _020BF2E0 ; =0x021CEF7C
	mov r2, r4, lsr #0x5
	ldr r1, [r0, #0x0]
	and r0, r4, #0x1f
	add r3, r1, #0xc4
	mov r1, #0x1
	mvn r0, r1, lsl r0
	ldr r1, [r3, r2, lsl #0x2]
	and r0, r1, r0
	str r0, [r3, r2, lsl #0x2]
	ldr r0, [r5, #0x0]
	orr r0, r0, #0x18
	str r0, [r5, #0x0]
	ldmia sp!, {r4-r8,pc}
_020BF200:
	mov r2, #0x18
	mul r12, r0, r2
	and r7, r4, #0x1f
	ldr r0, _020BF2E4 ; =0x021CFD80
	add r6, r6, #0xc4
	mov lr, r4, lsr #0x5
	mvn r7, r3, lsl r7
	ldr r8, [r6, lr, lsl #0x2]
	mul r3, r4, r2
	and r4, r8, r7
	str r4, [r6, lr, lsl #0x2]
	ldr r7, [r1, #0x0]
	ldr r4, [r0, r12]
	ldr r6, _020BF2E8 ; =0x021CFD84
	smull r8, r4, r7, r4
	mov r7, r8, lsr #0xc
	orr r7, r7, r4, lsl #0x14
	str r7, [r0, r3]
	ldr r8, [r1, #0x4]
	ldr r4, [r6, r12]
	ldr r7, _020BF2EC ; =0x021CFD88
	smull lr, r4, r8, r4
	mov r8, lr, lsr #0xc
	orr r8, r8, r4, lsl #0x14
	str r8, [r6, r3]
	ldr r8, [r1, #0x8]
	ldr r4, [r7, r12]
	ldr r6, _020BF2F0 ; =0x021CFD8C
	smull lr, r4, r8, r4
	mov r8, lr, lsr #0xc
	orr r8, r8, r4, lsl #0x14
	str r8, [r7, r3]
	ldr r7, [r1, #0xc]
	ldr r4, [r6, r12]
	ldr lr, _020BF2F4 ; =0x021CFD90
	smull r8, r4, r7, r4
	mov r7, r8, lsr #0xc
	orr r7, r7, r4, lsl #0x14
	str r7, [r6, r3]
	ldr r7, [r1, #0x10]
	ldr r4, [lr, r12]
	ldr r6, _020BF2F8 ; =0x021CFD94
	smull r8, r4, r7, r4
	add r0, r0, r12
	mov r7, r8, lsr #0xc
	orr r7, r7, r4, lsl #0x14
	str r7, [lr, r3]
	ldr lr, [r1, #0x14]
	ldr r4, [r6, r12]
	add r1, r5, #0x10
	smull r5, r4, lr, r4
	mov r5, r5, lsr #0xc
	orr r5, r5, r4, lsl #0x14
	str r5, [r6, r3]
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020BF2E0: .word 0x021CEF7C
_020BF2E4: .word 0x021CFD80
_020BF2E8: .word 0x021CFD84
_020BF2EC: .word 0x021CFD88
_020BF2F0: .word 0x021CFD8C
_020BF2F4: .word 0x021CFD90
_020BF2F8: .word 0x021CFD94

	arm_func_start FUN_020BF2FC
FUN_020BF2FC: ; 0x020BF2FC
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x10
	mov r6, r0
	ldr r0, [r6, #0x0]
	mov r5, #0x0
	ands r4, r0, #0x18
	bne _020BF328
	add r1, r6, #0x1c
	mov r0, #0x1b
	mov r2, #0x3
	bl FUN_020BB1C0
_020BF328:
	ldr r0, [r6, #0x0]
	ands r0, r0, #0x4
	bne _020BF398
	cmp r4, #0x0
	movne r5, #0x1
	bne _020BF398
	ldr r2, [r6, #0x4c]
	ldr r0, [r6, #0x10]
	add r1, sp, #0x0
	smull r3, r0, r2, r0
	mov r2, r3, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x0]
	ldr r3, [r6, #0x50]
	ldr r2, [r6, #0x14]
	mov r0, #0x1c
	smull r12, r2, r3, r2
	mov r3, r12, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	str r3, [sp, #0x4]
	ldr r12, [r6, #0x54]
	ldr r3, [r6, #0x18]
	mov r2, #0x3
	smull lr, r3, r12, r3
	mov r12, lr, lsr #0xc
	orr r12, r12, r3, lsl #0x14
	str r12, [sp, #0x8]
	bl FUN_020BB1C0
_020BF398:
	ldr r0, [r6, #0x0]
	ands r0, r0, #0x2
	bne _020BF3D4
	cmp r5, #0x0
	beq _020BF3C0
	add r1, r6, #0x28
	mov r0, #0x19
	mov r2, #0xc
	bl FUN_020BB1C0
	b _020BF3EC
_020BF3C0:
	add r1, r6, #0x28
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
	b _020BF3EC
_020BF3D4:
	cmp r5, #0x0
	beq _020BF3EC
	add r1, r6, #0x4c
	mov r0, #0x1c
	mov r2, #0x3
	bl FUN_020BB1C0
_020BF3EC:
	cmp r4, #0x0
	bne _020BF404
	add r1, r6, #0x10
	mov r0, #0x1b
	mov r2, #0x3
	bl FUN_020BB1C0
_020BF404:
	ldr r0, [r6, #0x0]
	ands r0, r0, #0x1
	addne sp, sp, #0x10
	ldmneia sp!, {r4-r6,pc}
_020BF414: ; 0x020BF414
	add r1, r6, #0x4
	mov r0, #0x1b
	mov r2, #0x3
	bl FUN_020BB1C0
	add sp, sp, #0x10
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BF42C
FUN_020BF42C: ; 0x020BF42C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x50
	mov r4, r0
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	ands r0, r0, #0x8
	ldrne r0, _020BF568 ; =0x00101610
	mov r3, #0x3
	strne r0, [sp, #0x0]
	ldreq r0, _020BF56C ; =0x00101810
	mov r2, #0x2
	streq r0, [sp, #0x0]
	mov r0, #0x1000
	str r0, [sp, #0x44]
	str r3, [sp, #0x4]
	str r2, [sp, #0x48]
	str r1, [sp, #0x40]
	str r1, [sp, #0x34]
	str r1, [sp, #0x30]
	str r1, [sp, #0x2c]
	str r1, [sp, #0x28]
	str r1, [sp, #0x24]
	str r1, [sp, #0x20]
	str r1, [sp, #0x14]
	str r1, [sp, #0x10]
	ldr r1, [r4, #0x0]
	ldr r0, _020BF570 ; =0x021067D0
	and r1, r1, #0x7
	ldr r2, [r0, r1, lsl #0x2]
	add r0, sp, #0x8
	mov r1, r4
	blx r2
	ldr r3, [r4, #0x30]
	cmp r3, #0x1000
	beq _020BF4FC
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	smull r2, r0, r3, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x8]
	ldr r2, [r4, #0x30]
	ldr r0, [sp, #0x38]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0xc]
	ldr r1, [r4, #0x30]
	smull r2, r0, r1, r0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [sp, #0x38]
_020BF4FC:
	ldr r3, [r4, #0x34]
	cmp r3, #0x1000
	beq _020BF54C
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	smull r2, r0, r3, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x18]
	ldr r2, [r4, #0x34]
	ldr r0, [sp, #0x3c]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0x1c]
	ldr r1, [r4, #0x34]
	smull r2, r0, r1, r0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [sp, #0x3c]
_020BF54C:
	add r1, sp, #0x0
	ldr r0, [sp, #0x0]
	add r1, r1, #0x4
	mov r2, #0x12
	bl FUN_020BB1C0
	add sp, sp, #0x50
	ldmia sp!, {r4,pc}
	.balign 4
_020BF568: .word 0x00101610
_020BF56C: .word 0x00101810
_020BF570: .word 0x021067D0

	arm_func_start FUN_020BF574
FUN_020BF574: ; 0x020BF574
	mov r2, #0x1000
	str r2, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	str r1, [r0, #0x10]
	str r2, [r0, #0x14]
	str r1, [r0, #0x30]
	str r1, [r0, #0x34]
	bx lr

	arm_func_start FUN_020BF598
FUN_020BF598: ; 0x020BF598
	ldr r2, [r1, #0x18]
	mov r12, #0x0
	str r2, [r0, #0x0]
	ldr r2, [r1, #0x1c]
	str r2, [r0, #0x14]
	str r12, [r0, #0x4]
	ldr r3, [r1, #0x18]
	ldrh r2, [r1, #0x2c]
	rsb r3, r3, #0x1000
	mul r2, r3, r2
	mov r2, r2, lsl #0x3
	str r2, [r0, #0x30]
	ldr r2, [r1, #0x1c]
	ldrh r1, [r1, #0x2e]
	rsb r2, r2, #0x1000
	mul r1, r2, r1
	mov r1, r1, lsl #0x3
	str r1, [r0, #0x34]
	str r12, [r0, #0x10]
	bx lr

	arm_func_start FUN_020BF5E8
FUN_020BF5E8: ; 0x020BF5E8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldrh r2, [r5, #0x2c]
	ldrh r1, [r5, #0x2e]
	mov r6, r0
	mov r4, r2, lsl #0xc
	mov r7, r1, lsl #0xc
	mov r0, r7
	mov r1, r4
	bl FX_DivAsync
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x0]
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x14]
	bl FX_GetDivResult
	ldrsh r2, [r5, #0x20]
	mov r1, r7
	mul r0, r2, r0
	mov r2, r0, asr #0xc
	mov r0, r4
	str r2, [r6, #0x4]
	bl FX_DivAsync
	ldrh r2, [r5, #0x2c]
	ldrh r1, [r5, #0x2e]
	ldrsh r4, [r5, #0x22]
	rsb r0, r2, #0x0
	rsb r1, r1, #0x0
	mov r0, r0, lsl #0xb
	ldrsh r3, [r5, #0x20]
	mov r1, r1, lsl #0xb
	smull r7, lr, r4, r0
	smull r12, r4, r3, r1
	subs r7, r7, r12
	sbc r3, lr, r4
	mov r4, r7, lsr #0x8
	orr r4, r4, r3, lsl #0x18
	add r2, r4, r2, lsl #0xf
	str r2, [r6, #0x30]
	ldrsh r2, [r5, #0x22]
	ldrsh r3, [r5, #0x20]
	ldrh r12, [r5, #0x2e]
	smull r4, r1, r2, r1
	smlal r4, r1, r3, r0
	mov r0, r4, lsr #0x8
	orr r0, r0, r1, lsl #0x18
	add r0, r0, r12, lsl #0xf
	str r0, [r6, #0x34]
	bl FX_GetDivResult
	ldrsh r1, [r5, #0x20]
	rsb r1, r1, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r6, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020BF6C8
FUN_020BF6C8: ; 0x020BF6C8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r1
	ldrh r2, [r9, #0x2c]
	ldrh r1, [r9, #0x2e]
	mov r10, r0
	mov r8, r2, lsl #0xc
	mov r11, r1, lsl #0xc
	mov r0, r11
	mov r1, r8
	bl FX_DivAsync
	ldrsh r0, [r9, #0x22]
	ldr r3, [r9, #0x18]
	ldrsh r5, [r9, #0x20]
	ldr r4, [r9, #0x1c]
	smull r2, r1, r3, r0
	mov r7, r2, lsr #0xc
	orr r7, r7, r1, lsl #0x14
	smull r2, r1, r3, r5
	mov r6, r2, lsr #0xc
	orr r6, r6, r1, lsl #0x14
	smull r3, r2, r4, r0
	smull r1, r0, r4, r5
	mov r5, r3, lsr #0xc
	orr r5, r5, r2, lsl #0x14
	mov r4, r1, lsr #0xc
	orr r4, r4, r0, lsl #0x14
	str r7, [r10, #0x0]
	str r5, [r10, #0x14]
	bl FX_GetDivResult
	mov r1, r11
	mul r0, r4, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x4]
	mov r0, r8
	bl FX_DivAsync
	ldrh r3, [r9, #0x2c]
	ldrh r1, [r9, #0x2e]
	rsb r0, r3, #0x0
	rsb r1, r1, #0x0
	mov r2, r1, lsl #0xb
	mov r11, r0, lsl #0xb
	smull r1, r0, r7, r11
	smull r8, r7, r5, r2
	smlal r8, r7, r4, r11
	mov r4, r8, lsr #0x8
	orr r4, r4, r7, lsl #0x18
	smull r5, r2, r6, r2
	subs r1, r1, r5
	sbc r0, r0, r2
	mov r1, r1, lsr #0x8
	orr r1, r1, r0, lsl #0x18
	add r0, r1, r3, lsl #0xf
	str r0, [r10, #0x30]
	ldrh r0, [r9, #0x2e]
	add r0, r4, r0, lsl #0xf
	str r0, [r10, #0x34]
	bl FX_GetDivResult
	rsb r1, r6, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020BF7C8
FUN_020BF7C8: ; 0x020BF7C8
	mov r2, #0x1000
	str r2, [r0, #0x0]
	str r2, [r0, #0x14]
	mov r12, #0x0
	str r12, [r0, #0x4]
	ldr r3, [r1, #0x24]
	ldrh r2, [r1, #0x2c]
	rsb r3, r3, #0x0
	mul r2, r3, r2
	mov r2, r2, lsl #0x4
	str r2, [r0, #0x30]
	ldrh r2, [r1, #0x2e]
	ldr r1, [r1, #0x28]
	mul r2, r1, r2
	mov r1, r2, lsl #0x4
	str r1, [r0, #0x34]
	str r12, [r0, #0x10]
	bx lr

	arm_func_start FUN_020BF810
FUN_020BF810: ; 0x020BF810
	stmdb sp!, {r4-r6,lr}
	ldr r2, [r1, #0x18]
	mov r3, #0x0
	str r2, [r0, #0x0]
	ldr r2, [r1, #0x1c]
	str r2, [r0, #0x14]
	str r3, [r0, #0x4]
	ldrh r5, [r1, #0x2c]
	ldr r12, [r1, #0x24]
	ldrh r2, [r1, #0x2e]
	mul lr, r12, r5
	rsb r12, r5, #0x0
	mov r12, r12, lsl #0xb
	ldr r4, [r1, #0x18]
	sub r12, r12, lr
	smull lr, r12, r4, r12
	ldr r6, [r1, #0x28]
	mov r4, lr, lsr #0x8
	orr r4, r4, r12, lsl #0x18
	add r4, r4, r5, lsl #0xf
	str r4, [r0, #0x30]
	mul r4, r6, r2
	rsb r5, r2, #0x0
	ldr r2, [r1, #0x1c]
	add r4, r4, r5, lsl #0xb
	smull lr, r12, r2, r4
	mov r2, lr, lsr #0x8
	ldrh r1, [r1, #0x2e]
	orr r2, r2, r12, lsl #0x18
	add r1, r2, r1, lsl #0xf
	str r1, [r0, #0x34]
	str r3, [r0, #0x10]
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020BF894
FUN_020BF894: ; 0x020BF894
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldrh r2, [r5, #0x2c]
	ldrh r1, [r5, #0x2e]
	mov r6, r0
	mov r4, r2, lsl #0xc
	mov r7, r1, lsl #0xc
	mov r0, r7
	mov r1, r4
	bl FX_DivAsync
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x0]
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x14]
	bl FX_GetDivResult
	ldrsh r2, [r5, #0x20]
	mov r1, r7
	mul r0, r2, r0
	mov r2, r0, asr #0xc
	mov r0, r4
	str r2, [r6, #0x4]
	bl FX_DivAsync
	ldrh r2, [r5, #0x2c]
	ldrh r7, [r5, #0x2e]
	ldr r1, [r5, #0x28]
	ldr r0, [r5, #0x24]
	rsb r4, r2, #0x0
	mul r3, r1, r7
	rsb r1, r7, #0x0
	add r1, r3, r1, lsl #0xb
	ldrsh r3, [r5, #0x20]
	mov r7, r4, lsl #0xb
	mul r4, r0, r2
	sub r0, r7, r4
	ldrsh lr, [r5, #0x22]
	smull r12, r4, r3, r1
	smull r7, r3, lr, r0
	subs r7, r7, r12
	sbc r3, r3, r4
	mov r4, r7, lsr #0x8
	orr r4, r4, r3, lsl #0x18
	add r2, r4, r2, lsl #0xf
	str r2, [r6, #0x30]
	ldrsh r2, [r5, #0x22]
	ldrsh r3, [r5, #0x20]
	ldrh r12, [r5, #0x2e]
	smull r4, r1, r2, r1
	smlal r4, r1, r3, r0
	mov r0, r4, lsr #0x8
	orr r0, r0, r1, lsl #0x18
	add r0, r0, r12, lsl #0xf
	str r0, [r6, #0x34]
	bl FX_GetDivResult
	ldrsh r1, [r5, #0x20]
	rsb r1, r1, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r6, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020BF988
FUN_020BF988: ; 0x020BF988
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r1
	ldrh r2, [r9, #0x2c]
	ldrh r1, [r9, #0x2e]
	mov r10, r0
	mov r8, r2, lsl #0xc
	mov r11, r1, lsl #0xc
	mov r0, r11
	mov r1, r8
	bl FX_DivAsync
	ldrsh r0, [r9, #0x22]
	ldr r3, [r9, #0x18]
	ldrsh r5, [r9, #0x20]
	ldr r4, [r9, #0x1c]
	smull r2, r1, r3, r0
	mov r7, r2, lsr #0xc
	orr r7, r7, r1, lsl #0x14
	smull r2, r1, r3, r5
	mov r6, r2, lsr #0xc
	orr r6, r6, r1, lsl #0x14
	smull r3, r2, r4, r0
	smull r1, r0, r4, r5
	mov r5, r3, lsr #0xc
	orr r5, r5, r2, lsl #0x14
	mov r4, r1, lsr #0xc
	orr r4, r4, r0, lsl #0x14
	str r7, [r10, #0x0]
	str r5, [r10, #0x14]
	bl FX_GetDivResult
	mov r1, r11
	mul r0, r4, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x4]
	mov r0, r8
	bl FX_DivAsync
	ldrh r1, [r9, #0x2c]
	ldrh r8, [r9, #0x2e]
	ldr r2, [r9, #0x28]
	rsb r0, r1, #0x0
	mul r3, r2, r8
	rsb r2, r8, #0x0
	add r8, r3, r2, lsl #0xb
	mov r0, r0, lsl #0xb
	smull r3, r2, r5, r8
	smull r8, r5, r6, r8
	ldr r11, [r9, #0x24]
	mul r12, r11, r1
	sub r0, r0, r12
	smlal r3, r2, r4, r0
	smull r4, r0, r7, r0
	subs r4, r4, r8
	sbc r0, r0, r5
	mov r4, r4, lsr #0x8
	orr r4, r4, r0, lsl #0x18
	add r0, r4, r1, lsl #0xf
	str r0, [r10, #0x30]
	ldrh r1, [r9, #0x2e]
	mov r0, r3, lsr #0x8
	orr r0, r0, r2, lsl #0x18
	add r0, r0, r1, lsl #0xf
	str r0, [r10, #0x34]
	bl FX_GetDivResult
	rsb r1, r6, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020BFA9C
FUN_020BFA9C: ; 0x020BFA9C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x50
	mov r4, r0
	ldr r0, [r4, #0x0]
	mov r3, #0x3
	ands r0, r0, #0x8
	ldrne r0, _020BFC1C ; =0x00101610
	mov r2, #0x2
	strne r0, [sp, #0x0]
	ldreq r0, _020BFC20 ; =0x00101810
	mov r1, #0x1000
	streq r0, [sp, #0x0]
	mov r0, #0x0
	str r3, [sp, #0x4]
	str r2, [sp, #0x48]
	str r1, [sp, #0x44]
	str r0, [sp, #0x40]
	str r0, [sp, #0x34]
	str r0, [sp, #0x30]
	str r0, [sp, #0x2c]
	str r0, [sp, #0x28]
	str r0, [sp, #0x24]
	str r0, [sp, #0x20]
	str r0, [sp, #0x14]
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x1
	strne r1, [r4, #0x1c]
	ldrne r0, [r4, #0x1c]
	strne r0, [r4, #0x18]
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x2
	movne r0, #0x1000
	strneh r0, [r4, #0x22]
	movne r0, #0x0
	strneh r0, [r4, #0x20]
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x4
	movne r0, #0x0
	strne r0, [r4, #0x28]
	ldrne r0, [r4, #0x28]
	strne r0, [r4, #0x24]
	ldr r1, [r4, #0x0]
	ldr r0, _020BFC24 ; =0x021067F0
	and r1, r1, #0x7
	ldr r2, [r0, r1, lsl #0x2]
	add r0, sp, #0x8
	mov r1, r4
	blx r2
	ldr r3, [r4, #0x30]
	cmp r3, #0x1000
	beq _020BFBB0
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	smull r2, r0, r3, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x8]
	ldr r2, [r4, #0x30]
	ldr r0, [sp, #0x38]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0xc]
	ldr r1, [r4, #0x30]
	smull r2, r0, r1, r0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [sp, #0x38]
_020BFBB0:
	ldr r3, [r4, #0x34]
	cmp r3, #0x1000
	beq _020BFC00
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	smull r2, r0, r3, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x18]
	ldr r2, [r4, #0x34]
	ldr r0, [sp, #0x3c]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0x1c]
	ldr r1, [r4, #0x34]
	smull r2, r0, r1, r0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [sp, #0x3c]
_020BFC00:
	add r1, sp, #0x0
	ldr r0, [sp, #0x0]
	add r1, r1, #0x4
	mov r2, #0x12
	bl FUN_020BB1C0
	add sp, sp, #0x50
	ldmia sp!, {r4,pc}
	.balign 4
_020BFC1C: .word 0x00101610
_020BFC20: .word 0x00101810
_020BFC24: .word 0x021067F0

	arm_func_start FUN_020BFC28
FUN_020BFC28: ; 0x020BFC28
	mov r2, #0x1000
	str r2, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	str r1, [r0, #0x10]
	str r2, [r0, #0x14]
	str r1, [r0, #0x30]
	str r1, [r0, #0x34]
	bx lr

	arm_func_start FUN_020BFC4C
FUN_020BFC4C: ; 0x020BFC4C
	ldr r2, [r1, #0x18]
	mov r3, #0x0
	str r2, [r0, #0x0]
	ldr r2, [r1, #0x1c]
	str r2, [r0, #0x14]
	str r3, [r0, #0x4]
	str r3, [r0, #0x30]
	ldrh r2, [r1, #0x2e]
	ldr r1, [r1, #0x1c]
	rsb r2, r2, #0x0
	sub r1, r1, #0x1000
	mul r1, r2, r1
	mov r1, r1, lsl #0x4
	str r1, [r0, #0x34]
	str r3, [r0, #0x10]
	bx lr

	arm_func_start FUN_020BFC8C
FUN_020BFC8C: ; 0x020BFC8C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldrh r2, [r5, #0x2c]
	ldrh r1, [r5, #0x2e]
	mov r6, r0
	mov r4, r2, lsl #0xc
	mov r7, r1, lsl #0xc
	mov r0, r7
	mov r1, r4
	bl FX_DivAsync
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x0]
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x14]
	bl FX_GetDivResult
	ldrsh r2, [r5, #0x20]
	mov r1, r7
	mul r0, r2, r0
	mov r2, r0, asr #0xc
	mov r0, r4
	str r2, [r6, #0x4]
	bl FX_DivAsync
	ldrh r1, [r5, #0x2c]
	ldrsh r0, [r5, #0x20]
	mul r0, r1, r0
	mov r0, r0, lsl #0x4
	str r0, [r6, #0x30]
	ldrh r1, [r5, #0x2e]
	ldrsh r0, [r5, #0x22]
	rsb r1, r1, #0x0
	sub r0, r0, #0x1000
	mul r0, r1, r0
	mov r0, r0, lsl #0x4
	str r0, [r6, #0x34]
	bl FX_GetDivResult
	ldrsh r1, [r5, #0x20]
	rsb r1, r1, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r6, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020BFD38
FUN_020BFD38: ; 0x020BFD38
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r1
	ldrh r2, [r9, #0x2c]
	ldrh r1, [r9, #0x2e]
	mov r10, r0
	mov r8, r2, lsl #0xc
	mov r11, r1, lsl #0xc
	mov r0, r11
	mov r1, r8
	bl FX_DivAsync
	ldrsh r3, [r9, #0x22]
	ldr r0, [r9, #0x18]
	ldrsh r7, [r9, #0x20]
	ldr r5, [r9, #0x1c]
	smull r2, r1, r0, r3
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [r10, #0x0]
	smull r2, r1, r5, r3
	mov r4, r2, lsr #0xc
	orr r4, r4, r1, lsl #0x14
	smull r2, r1, r0, r7
	mov r6, r2, lsr #0xc
	orr r6, r6, r1, lsl #0x14
	str r4, [r10, #0x14]
	bl FX_GetDivResult
	smull r2, r1, r5, r7
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	mul r0, r2, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x4]
	mov r0, r8
	mov r1, r11
	bl FX_DivAsync
	sub r0, r4, #0x1000
	ldrh r1, [r9, #0x2c]
	mul r2, r1, r6
	mov r1, r2, lsl #0x4
	str r1, [r10, #0x30]
	ldrh r1, [r9, #0x2e]
	rsb r1, r1, #0x0
	mul r0, r1, r0
	mov r0, r0, lsl #0x4
	str r0, [r10, #0x34]
	bl FX_GetDivResult
	rsb r1, r6, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020BFE0C
FUN_020BFE0C: ; 0x020BFE0C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, #0x1000
	str r2, [r0, #0x0]
	str r2, [r0, #0x14]
	mov lr, #0x0
	str lr, [r0, #0x4]
	ldr r2, [r1, #0x24]
	ldrh r3, [r1, #0x2c]
	rsb r2, r2, #0x0
	ldr r12, [r1, #0x28]
	mul r2, r3, r2
	mov r2, r2, lsl #0x4
	str r2, [r0, #0x30]
	ldrh r1, [r1, #0x2e]
	rsb r2, r12, #0x0
	rsb r1, r1, #0x0
	mul r2, r1, r2
	mov r1, r2, lsl #0x4
	str r1, [r0, #0x34]
	str lr, [r0, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020BFE68
FUN_020BFE68: ; 0x020BFE68
	stmdb sp!, {r4,lr}
	ldr r3, [r1, #0x18]
	mov r2, #0x0
	str r3, [r0, #0x0]
	ldr r3, [r1, #0x1c]
	str r3, [r0, #0x14]
	str r2, [r0, #0x4]
	ldr r12, [r1, #0x24]
	ldr r3, [r1, #0x18]
	ldr r4, [r1, #0x28]
	smull lr, r3, r12, r3
	mov r12, lr, lsr #0xc
	orr r12, r12, r3, lsl #0x14
	ldrh lr, [r1, #0x2c]
	rsb r3, r12, #0x0
	ldr r12, [r1, #0x1c]
	rsb r4, r4, #0x0
	mul r3, lr, r3
	smull lr, r12, r4, r12
	mov r3, r3, lsl #0x4
	str r3, [r0, #0x30]
	mov r4, lr, lsr #0xc
	ldrh r3, [r1, #0x2e]
	ldr r1, [r1, #0x1c]
	orr r4, r4, r12, lsl #0x14
	add r1, r1, r4
	rsb r3, r3, #0x0
	sub r1, r1, #0x1000
	mul r1, r3, r1
	mov r1, r1, lsl #0x4
	str r1, [r0, #0x34]
	str r2, [r0, #0x10]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020BFEEC
FUN_020BFEEC: ; 0x020BFEEC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldrh r2, [r5, #0x2c]
	ldrh r1, [r5, #0x2e]
	mov r6, r0
	mov r4, r2, lsl #0xc
	mov r7, r1, lsl #0xc
	mov r0, r7
	mov r1, r4
	bl FX_DivAsync
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x0]
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x14]
	bl FX_GetDivResult
	ldrsh r2, [r5, #0x20]
	mov r1, r7
	mul r0, r2, r0
	mov r2, r0, asr #0xc
	mov r0, r4
	str r2, [r6, #0x4]
	bl FX_DivAsync
	ldrsh lr, [r5, #0x20]
	ldr r4, [r5, #0x28]
	ldrsh r0, [r5, #0x22]
	ldr r12, [r5, #0x24]
	smull r3, r2, r4, lr
	smlal r3, r2, r12, r0
	smull r1, r0, r4, r0
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	sub r4, lr, r3
	smull r3, r2, r12, lr
	subs r1, r3, r1
	sbc r0, r2, r0
	ldrh r2, [r5, #0x2c]
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	mul r0, r2, r4
	mov r0, r0, lsl #0x4
	str r0, [r6, #0x30]
	ldrsh r0, [r5, #0x22]
	ldrh r2, [r5, #0x2e]
	add r0, r0, r1
	rsb r1, r2, #0x0
	sub r0, r0, #0x1000
	mul r0, r1, r0
	mov r0, r0, lsl #0x4
	str r0, [r6, #0x34]
	bl FX_GetDivResult
	ldrsh r1, [r5, #0x20]
	rsb r1, r1, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r6, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020BFFD4
FUN_020BFFD4: ; 0x020BFFD4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r6, r1
	ldrh r2, [r6, #0x2c]
	ldrh r1, [r6, #0x2e]
	mov r7, r0
	mov r10, r2, lsl #0xc
	mov r11, r1, lsl #0xc
	mov r0, r11
	mov r1, r10
	bl FX_DivAsync
	ldrsh r3, [r6, #0x22]
	ldr r0, [r6, #0x18]
	ldrsh r9, [r6, #0x20]
	smull r2, r1, r0, r3
	mov r2, r2, lsr #0xc
	ldr r8, [r6, #0x1c]
	orr r2, r2, r1, lsl #0x14
	str r2, [r7, #0x0]
	smull r2, r1, r8, r3
	mov r4, r2, lsr #0xc
	orr r4, r4, r1, lsl #0x14
	smull r2, r1, r0, r9
	mov r5, r2, lsr #0xc
	orr r5, r5, r1, lsl #0x14
	str r4, [r7, #0x14]
	bl FX_GetDivResult
	smull r2, r1, r8, r9
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	mul r0, r2, r0
	mov r0, r0, asr #0xc
	str r0, [r7, #0x4]
	mov r0, r10
	mov r1, r11
	bl FX_DivAsync
	ldr lr, [r6, #0x1c]
	ldrsh r2, [r6, #0x20]
	ldr r8, [r6, #0x24]
	ldr r0, [r6, #0x28]
	smull r10, r9, r8, r2
	ldrh r1, [r6, #0x2c]
	smull r3, r2, r0, r2
	ldrsh r12, [r6, #0x22]
	str r1, [sp, #0x0]
	mov r11, lr, asr #0x1f
	smlal r3, r2, r8, r12
	smull r8, r12, r0, r12
	subs r8, r10, r8
	sbc r0, r9, r12
	mov r9, r8, lsr #0xc
	mov r12, r3, lsr #0xc
	orr r9, r9, r0, lsl #0x14
	mov r3, r2, asr #0xc
	orr r12, r12, r2, lsl #0x14
	umull r10, r2, r9, lr
	mla r2, r9, r11, r2
	mov r8, r0, asr #0xc
	mla r2, r8, lr, r2
	ldr r1, [r6, #0x18]
	mov r8, r10, lsr #0xc
	orr r8, r8, r2, lsl #0x14
	add r2, r4, r8
	mov r0, r1, asr #0x1f
	umull r8, r4, r12, r1
	mla r4, r12, r0, r4
	mla r4, r3, r1, r4
	mov r0, r8, lsr #0xc
	orr r0, r0, r4, lsl #0x14
	sub r1, r5, r0
	ldr r0, [sp, #0x0]
	sub r2, r2, #0x1000
	mul r1, r0, r1
	mov r0, r1, lsl #0x4
	str r0, [r7, #0x30]
	ldrh r0, [r6, #0x2e]
	rsb r0, r0, #0x0
	mul r1, r0, r2
	mov r0, r1, lsl #0x4
	str r0, [r7, #0x34]
	bl FX_GetDivResult
	rsb r1, r5, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r7, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020C0130
FUN_020C0130: ; 0x020C0130
	ldr ip, _020C0138 ; =FUN_020C187C
	bx r12
	.balign 4
_020C0138: .word FUN_020C187C

	arm_func_start FUN_020C013C
FUN_020C013C: ; 0x020C013C
	stmdb sp!, {r4,lr}
	bl FUN_020C18F8
_020C0144: ; 0x020C0144
	mov r0, #0x0
	mov r1, r0
	mov r2, r0
	mov r3, r0
	bl SND_StopTimer
	bl SND_GetCurrentCommandTag
	mov r4, r0
	mov r0, #0x1
	bl SND_FlushCommand
	mov r0, r4
	bl SND_WaitForCommandProc
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C0174
FUN_020C0174: ; 0x020C0174
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	beq _020C0194
	mov r0, #0x40
	bl SND_SetMasterPan
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020C0194:
	bl SND_ResetMasterPan
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C01A0
FUN_020C01A0: ; 0x020C01A0
	stmdb sp!, {r4,lr}
	mov r4, #0x0
_020C01A8:
	mov r0, r4
	bl SND_RecvCommandReply
_020C01B0: ; 0x020C01B0
	cmp r0, #0x0
	bne _020C01A8
	bl FUN_020C0BA0
	bl FUN_020C1D9C
	bl FUN_020C3C88
_020C01C4: ; 0x020C01C4
	mov r0, #0x0
	bl SND_FlushCommand
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C01D0
FUN_020C01D0: ; 0x020C01D0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C0254 ; =0x021D1C94
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {pc}
	mov r1, #0x1
	str r1, [r0, #0x0]
	bl SND_Init
	ldr ip, _020C0258 ; =FUN_020C013C
	ldr r0, _020C025C ; =0x021D1C98
	mov r3, #0x0
	ldr r1, _020C0260 ; =0x021D1CA4
	ldr r2, _020C0264 ; =FUN_020C0130
	str r12, [r0, #0x0]
	str r3, [r0, #0x4]
	str r2, [r1, #0x0]
	str r3, [r1, #0x4]
	bl PM_PrependPreSleepCallback
	ldr r0, _020C0260 ; =0x021D1CA4
	bl PM_AppendPostSleepCallback
	bl FUN_020C0270
	bl FUN_020C1E38
	bl FUN_020C0D20
	ldr r1, _020C0268 ; =0x021D1C8C
	mvn r3, #0x0
	ldr r0, _020C026C ; =0x021D1C90
	mov r2, #0x1
	strb r3, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020C0254: .word 0x021D1C94
_020C0258: .word FUN_020C013C
_020C025C: .word 0x021D1C98
_020C0260: .word 0x021D1CA4
_020C0264: .word FUN_020C0130
_020C0268: .word 0x021D1C8C
_020C026C: .word 0x021D1C90

	arm_func_start FUN_020C0270
FUN_020C0270: ; 0x020C0270
	ldr r2, _020C0290 ; =0x021D1CB8
	mov r3, #0x0
	ldr r1, _020C0294 ; =0x021D1CB0
	ldr r0, _020C0298 ; =0x021D1CB4
	str r3, [r2, #0x0]
	str r3, [r1, #0x0]
	str r3, [r0, #0x0]
	bx lr
	.balign 4
_020C0290: .word 0x021D1CB8
_020C0294: .word 0x021D1CB0
_020C0298: .word 0x021D1CB4

	arm_func_start FUN_020C029C
FUN_020C029C: ; 0x020C029C
	ldr r1, _020C02B8 ; =0x021D1CB4
	mov r2, #0x1
	mvn r0, r2, lsl r0
	ldr r2, [r1, #0x0]
	and r0, r2, r0
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020C02B8: .word 0x021D1CB4

	arm_func_start FUN_020C02BC
FUN_020C02BC: ; 0x020C02BC
	ldr r0, _020C02FC ; =0x021D1CB4
	mov r3, #0x1
	ldr r2, [r0, #0x0]
	mov r0, #0x0
_020C02CC:
	ands r1, r2, r3
	ldreq r1, _020C02FC ; =0x021D1CB4
	ldreq r2, [r1, #0x0]
	orreq r2, r2, r3
	streq r2, [r1, #0x0]
	bxeq lr
	add r0, r0, #0x1
	cmp r0, #0x8
	mov r3, r3, lsl #0x1
	blt _020C02CC
	mvn r0, #0x0
	bx lr
	.balign 4
_020C02FC: .word 0x021D1CB4

	arm_func_start FUN_020C0300
FUN_020C0300: ; 0x020C0300
	ldr r1, _020C0318 ; =0x021D1CB0
	mvn r0, r0
	ldr r2, [r1, #0x0]
	and r0, r2, r0
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020C0318: .word 0x021D1CB0

	arm_func_start FUN_020C031C
FUN_020C031C:
	ldr r1, _020C033C ; =0x021D1CB0
	ldr r2, [r1, #0x0]
	ands r3, r0, r2
	movne r0, #0x0
	orreq r0, r2, r0
	streq r0, [r1, #0x0]
	moveq r0, #0x1
	bx lr
	.balign 4
_020C033C: .word 0x021D1CB0

	arm_func_start FUN_020C0340
FUN_020C0340:
	stmdb sp!, {r4,lr}
	movs r4, r0
	ldmeqia sp!, {r4,pc}
_020C034C: ; 0x020C034C
	mov r1, #0x0
	bl SND_UnlockChannel
	ldr r0, _020C036C ; =0x021D1CB8
	mvn r1, r4
	ldr r2, [r0, #0x0]
	and r1, r2, r1
	str r1, [r0, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_020C036C: .word 0x021D1CB8

	arm_func_start FUN_020C0370
FUN_020C0370:
	stmdb sp!, {r4,lr}
	movs r4, r0
	moveq r0, #0x1
	ldmeqia sp!, {r4,pc}
_020C0380: ; 0x020C0380
	ldr r1, _020C03B4 ; =0x021D1CB8
	ldr r1, [r1, #0x0]
	ands r1, r4, r1
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
_020C0394: ; 0x020C0394
	mov r1, #0x0
	bl SND_LockChannel
	ldr r1, _020C03B4 ; =0x021D1CB8
	mov r0, #0x1
	ldr r2, [r1, #0x0]
	orr r2, r2, r4
	str r2, [r1, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_020C03B4: .word 0x021D1CB8

	arm_func_start FUN_020C03B8
FUN_020C03B8: ; 0x020C03B8
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_020C03D0: ; 0x020C03D0
	ldr r0, [r4, #0xc]
	cmp r0, #0x0
	bne _020C03F8
	ldr r0, [r4, #0x10]
	bl SND_IsFinishedCommandTag
_020C03E4: ; 0x020C03E4
	cmp r0, #0x0
	moveq r0, #0x1
	ldmeqia sp!, {r4,pc}
_020C03F0: ; 0x020C03F0
	mov r0, #0x1
	str r0, [r4, #0xc]
_020C03F8:
	bl SND_GetChannelStatus
	ldr r1, [r4, #0x0]
	mov r2, #0x1
	mov r1, r2, lsl r1
	ands r0, r1, r0
	movne r0, r2
	moveq r0, #0x0
	streq r0, [r4, #0x8]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C041C
FUN_020C041C: ; 0x020C041C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x8]
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r0, [r0, #0x0]
	mov r2, #0x1
	mov r0, r2, lsl r0
	bl SND_SetChannelPan
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C044C
FUN_020C044C: ; 0x020C044C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, [r5, #0x8]
	mov r4, r1
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
_020C046C: ; 0x020C046C
	ldr r2, [r5, #0x4]
	ldr r0, _020C04D4 ; =0xD87F8000
	mov r3, r2, asr #0x1f
	mov r1, #0x7f
	bl _ll_udiv
	mov r2, r4
	mov r3, r4, asr #0x1f
	bl _ll_udiv
	mov r2, #0x0
	mov r3, r0
	mov r0, #0x10
	cmp r1, r2
	cmpeq r3, r0
	movcc r3, r0
	blo _020C04B8
	ldr r0, _020C04D8 ; =0x0000FFFF
	cmp r1, r2
	cmpeq r3, r0
	movhi r3, r0
_020C04B8:
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	mov r0, r1, lsl r0
	mov r1, r3
	bl SND_SetChannelTimer
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C04D4: .word 0xD87F8000
_020C04D8: .word 0x0000FFFF

	arm_func_start FUN_020C04DC
FUN_020C04DC: ; 0x020C04DC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x8]
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r0, [r0, #0x0]
	mov r2, #0x1
	mov r0, r2, lsl r0
	mov r2, #0x0
	bl SND_SetChannelVolume
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C0510
FUN_020C0510: ; 0x020C0510
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
_020C0524: ; 0x020C0524
	ldr r0, [r4, #0x0]
	mov r2, #0x1
	mov r1, #0x0
	mov r0, r2, lsl r0
	mov r2, r1
	mov r3, r1
	bl SND_StopTimer
_020C0540: ; 0x020C0540
	mov r0, #0x0
	str r0, [r4, #0x8]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C054C
FUN_020C054C: ; 0x020C054C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x1c
	movs r8, r1
	mov r9, r0
	mov r7, r2
	mov r6, r3
	beq _020C0584
	cmp r8, #0x1
	ldreq r0, [sp, #0x3c]
	ldreq r1, [sp, #0x38]
	moveq r0, r0, asr #0x1
	moveq r5, r1, asr #0x1
	subeq r4, r0, r1, asr #0x1
	b _020C0598
_020C0584:
	ldr r0, [sp, #0x3c]
	ldr r1, [sp, #0x38]
	mov r0, r0, asr #0x2
	mov r5, r1, asr #0x2
	sub r4, r0, r1, asr #0x2
_020C0598:
	ldr r2, [sp, #0x40]
	ldr r0, _020C0668 ; =0xD87F8000
	mov r3, r2, asr #0x1f
	mov r1, #0x7f
	bl _ll_udiv
	ldr r2, [sp, #0x48]
	mov r3, r2, asr #0x1f
	bl _ll_udiv
	mov r3, #0x0
	mov r2, #0x10
	cmp r1, r3
	cmpeq r0, r2
	movcc r0, r2
	blo _020C05E0
	ldr r2, _020C066C ; =0x0000FFFF
	cmp r1, r3
	cmpeq r0, r2
	movhi r0, r2
_020C05E0:
	str r5, [sp, #0x0]
	ldr r1, [sp, #0x44]
	str r4, [sp, #0x4]
	str r1, [sp, #0x8]
	mov r1, #0x0
	str r1, [sp, #0xc]
	cmp r6, #0x0
	movne r3, #0x1
	ldr r1, [sp, #0x4c]
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	ldr r0, [r9, #0x0]
	moveq r3, #0x2
	mov r1, r8
	mov r2, r7
	bl SND_SetupChannelPcm
	mov r1, #0x0
	ldr r0, [r9, #0x0]
	mov r2, #0x1
	mov r0, r2, lsl r0
	mov r2, r1
	mov r3, r1
	bl SND_StartTimer
	mov r0, #0x1
	str r0, [r9, #0x8]
	mov r0, #0x0
	str r0, [r9, #0xc]
	bl SND_GetCurrentCommandTag
	str r0, [r9, #0x10]
	ldr r1, [sp, #0x40]
	mov r0, #0x1
	str r1, [r9, #0x4]
	add sp, sp, #0x1c
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020C0668: .word 0xD87F8000
_020C066C: .word 0x0000FFFF

	arm_func_start FUN_020C0670
FUN_020C0670: ; 0x020C0670
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	ldr ip, _020C0684 ; =FUN_020C0340
	mov r0, r1, lsl r0
	bx r12
	.balign 4
_020C0684: .word FUN_020C0340

	arm_func_start FUN_020C0688
FUN_020C0688: ; 0x020C0688
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x1
	mov r0, r0, lsl r4
	bl FUN_020C0370
_020C069C: ; 0x020C069C
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_020C06A8: ; 0x020C06A8
	mov r0, #0x14
	mul r0, r4, r0
	ldr r2, _020C06C8 ; =0x021D1CBC
	mov r1, #0x0
	str r4, [r2, r0]
	add r0, r2, r0
	str r1, [r0, #0x8]
	ldmia sp!, {r4,pc}
	.balign 4
_020C06C8: .word 0x021D1CBC

	arm_func_start FUN_020C06CC
FUN_020C06CC: ; 0x020C06CC
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldr r4, [r6, #0x4]
	mov r5, r1
	cmp r4, #0x0
	beq _020C06F8
	mov r0, r4
	mov r1, r6
	bl FUN_020ADAB0
_020C06F0: ; 0x020C06F0
	mov r0, #0x0
	str r0, [r6, #0x4]
_020C06F8:
	ldr r0, _020C0728 ; =0x021D1E08
	mov r1, r6
	bl FUN_020ADAB0
	strb r5, [r6, #0x3d]
	cmp r4, #0x0
	beq _020C071C
	mov r0, r4
	mov r1, r6
	bl FUN_020C0910
_020C071C:
	mov r0, r6
	bl FUN_020C08B4
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C0728: .word 0x021D1E08

	arm_func_start FUN_020C072C
FUN_020C072C: ; 0x020C072C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
_020C0740: ; 0x020C0740
	bl FUN_020C2A7C
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x8]
	ldmneia sp!, {r4,pc}
_020C0758: ; 0x020C0758
	ldr r1, [r4, #0x10]
	ldr r2, _020C0778 ; =0x021D2254
	mov r0, #0x24
	mla r0, r1, r0, r2
	mov r1, r4
	add r0, r0, #0xc
	bl FUN_020ADAB0
	ldmia sp!, {r4,pc}
	.balign 4
_020C0778: .word 0x021D2254

	arm_func_start FUN_020C077C
FUN_020C077C: ; 0x020C077C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x0]
	strne r0, [r4, #0x0]
	ldr r5, [r4, #0x4]
	mov r1, r4
	mov r0, r5
	bl FUN_020ADAB0
_020C07AC: ; 0x020C07AC
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	cmp r1, #0x0
	beq _020C07D8
	add r0, r5, #0xc
	bl FUN_020ADBE8
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	str r1, [r0, #0xc]
	str r1, [r4, #0x8]
_020C07D8:
	ldr r0, _020C0800 ; =0x021D1E08
	mov r1, r4
	bl FUN_020ADAB0
	ldr r0, _020C0804 ; =0x021D1DFC
	mov r1, r4
	bl FUN_020ADBE8
_020C07F0: ; 0x020C07F0
	mov r0, #0x0
	strb r0, [r4, #0x2c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C0800: .word 0x021D1E08
_020C0804: .word 0x021D1DFC

	arm_func_start FUN_020C0808
FUN_020C0808: ; 0x020C0808
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, _020C0874 ; =0x021D1DFC
	mov r1, #0x0
	bl FUN_020ADA98
	movs r4, r0
	bne _020C0850
	ldr r0, _020C0878 ; =0x021D1E08
	mov r1, #0x0
	bl FUN_020ADA98
	mov r4, r0
	ldrb r1, [r4, #0x3d]
	cmp r5, r1
	addlt sp, sp, #0x4
	movlt r0, #0x0
	ldmltia sp!, {r4-r5,pc}
_020C084C: ; 0x020C084C
	bl FUN_020C087C
_020C0850:
	ldr r0, _020C0874 ; =0x021D1DFC
	mov r1, r4
	bl FUN_020ADAB0
	mov r0, r4
	strb r5, [r4, #0x3d]
	bl FUN_020C08B4
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C0874: .word 0x021D1DFC
_020C0878: .word 0x021D1E08

	arm_func_start FUN_020C087C
FUN_020C087C: ; 0x020C087C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldrb r0, [r4, #0x2c]
	cmp r0, #0x2
	bne _020C089C
	ldrb r0, [r4, #0x3c]
	ldr r1, _020C08B0 ; =0xFFFFFD2D
	bl SND_SetPlayerVolume
_020C089C:
	ldrb r0, [r4, #0x3c]
	bl SND_StopSeq
	mov r0, r4
	bl FUN_020C077C
	ldmia sp!, {r4,pc}
	.balign 4
_020C08B0: .word 0xFFFFFD2D

	arm_func_start FUN_020C08B4
FUN_020C08B4: ; 0x020C08B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, _020C090C ; =0x021D1E08
	mov r1, #0x0
	bl FUN_020ADA98
	movs r1, r0
	beq _020C08F8
	ldr r4, _020C090C ; =0x021D1E08
_020C08D8:
	ldrb r2, [r5, #0x3d]
	ldrb r0, [r1, #0x3d]
	cmp r2, r0
	blo _020C08F8
	mov r0, r4
	bl FUN_020ADA98
	movs r1, r0
	bne _020C08D8
_020C08F8:
	ldr r0, _020C090C ; =0x021D1E08
	mov r2, r5
	bl FUN_020ADB18
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C090C: .word 0x021D1E08

	arm_func_start FUN_020C0910
FUN_020C0910: ; 0x020C0910
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r1, #0x0
	mov r5, r0
	bl FUN_020ADA98
	movs r1, r0
	beq _020C0950
_020C0930:
	ldrb r2, [r4, #0x3d]
	ldrb r0, [r1, #0x3d]
	cmp r2, r0
	blo _020C0950
	mov r0, r5
	bl FUN_020ADA98
	movs r1, r0
	bne _020C0930
_020C0950:
	mov r0, r5
	mov r2, r4
	bl FUN_020ADB18
	str r5, [r4, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C0968
FUN_020C0968: ; 0x020C0968
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x0
	strb r0, [r4, #0x2e]
	strb r0, [r4, #0x2d]
	strb r0, [r4, #0x2f]
	strh r0, [r4, #0x34]
	strh r0, [r4, #0x3e]
	mov r1, #0x7f
	strb r1, [r4, #0x40]
	add r0, r4, #0x1c
	strb r1, [r4, #0x41]
	bl FUN_020C3E6C
	add r0, r4, #0x1c
	mov r1, #0x7f00
	mov r2, #0x1
	bl FUN_020C3E40
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C09B0
FUN_020C09B0: ; 0x020C09B0
	stmdb sp!, {r4-r6,lr}
	ldr r3, _020C0A00 ; =0x021D2254
	mov r2, #0x24
	mla r5, r0, r2, r3
	mov r6, r1
	add r0, r5, #0xc
	mov r1, #0x0
	bl FUN_020ADA98
	movs r4, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020C09DC: ; 0x020C09DC
	mov r1, r4
	add r0, r5, #0xc
	bl FUN_020ADAB0
	str r6, [r4, #0xc]
	str r4, [r6, #0x8]
	ldr r0, [r4, #0x8]
	bl FUN_020C29C0
	ldr r0, [r4, #0x8]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C0A00: .word 0x021D2254

	arm_func_start FUN_020C0A04
FUN_020C0A04: ; 0x020C0A04
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r5, r0
	mov r4, r1
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
_020C0A1C: ; 0x020C0A1C
	ldrb r0, [r5, #0x2e]
	cmp r4, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
_020C0A2C: ; 0x020C0A2C
	ldrb r0, [r5, #0x3c]
	bl SND_PauseSeq
	strb r4, [r5, #0x2e]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C0A40
FUN_020C0A40: ; 0x020C0A40
	stmdb sp!, {r4,lr}
	movs r4, r0
	mov r2, r1
	ldmeqia sp!, {r4,pc}
_020C0A50: ; 0x020C0A50
	ldrb r1, [r4, #0x2c]
	cmp r1, #0x0
	ldmeqia sp!, {r4,pc}
_020C0A5C: ; 0x020C0A5C
	cmp r2, #0x0
	bne _020C0A6C
	bl FUN_020C087C
	ldmia sp!, {r4,pc}
_020C0A6C:
	add r0, r4, #0x1c
	mov r1, #0x0
	bl FUN_020C3E40
	mov r0, r4
	mov r1, #0x0
	bl FUN_020C06CC
	mov r0, #0x2
	strb r0, [r4, #0x2c]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C0A90
FUN_020C0A90: ; 0x020C0A90
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrb r0, [r5, #0x3c]
	ldr r4, [r5, #0x4]
	bl SND_PrepareSeq
	ldr r2, [r4, #0x1c]
	cmp r2, #0x0
	beq _020C0AC0
	ldrb r0, [r5, #0x3c]
	ldr r1, _020C0AE4 ; =0x0000FFFF
	bl SND_SetTrackAllocatableChannel
_020C0AC0:
	mov r0, r5
	bl FUN_020C0968
	bl SND_GetCurrentCommandTag
	str r0, [r5, #0x30]
	mov r0, #0x1
	strb r0, [r5, #0x2f]
	strb r0, [r5, #0x2c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C0AE4: .word 0x0000FFFF

	arm_func_start thunk_FUN_020c077c
thunk_FUN_020c077c: ; 0x020C0AE8
	ldr ip, _020C0AF0 ; =FUN_020C077C
	bx r12
	.balign 4
_020C0AF0: .word FUN_020C077C

	arm_func_start FUN_020C0AF4
FUN_020C0AF4: ; 0x020C0AF4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr ip, _020C0B9C ; =0x021D2254
	mov r3, #0x24
	mov r4, r0
	ldr r5, [r4, #0x0]
	mla r6, r1, r3, r12
	mov r7, r2
	cmp r5, #0x0
	beq _020C0B20
	bl FUN_020C0F68
_020C0B20:
	ldrh r1, [r6, #0x8]
	ldr r0, [r6, #0x18]
	cmp r1, r0
	blo _020C0B64
	mov r0, r6
	mov r1, #0x0
	bl FUN_020ADA98
_020C0B3C: ; 0x020C0B3C
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
_020C0B4C: ; 0x020C0B4C
	ldrb r1, [r0, #0x3d]
	cmp r7, r1
	addlt sp, sp, #0x4
	movlt r0, #0x0
	ldmltia sp!, {r4-r7,pc}
_020C0B60: ; 0x020C0B60
	bl FUN_020C087C
_020C0B64:
	mov r0, r7
	bl FUN_020C0808
	movs r5, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
_020C0B7C: ; 0x020C0B7C
	mov r0, r6
	mov r1, r5
	bl FUN_020C0910
	str r4, [r5, #0x0]
	mov r0, r5
	str r5, [r4, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C0B9C: .word 0x021D2254

	arm_func_start FUN_020C0BA0
FUN_020C0BA0: ; 0x020C0BA0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	bl SND_GetPlayerStatus
_020C0BAC: ; 0x020C0BAC
	str r0, [sp, #0x0]
	ldr r0, _020C0D14 ; =0x021D1E08
	mov r1, #0x0
	bl FUN_020ADA98
	movs r10, r0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r11,pc}
_020C0BC8: ; 0x020C0BC8
	mov r0, #0x8000
	rsb r0, r0, #0x0
	ldr r4, _020C0D18 ; =0x02103BAC
	str r0, [sp, #0x4]
	mov r5, #0x1
	mov r11, #0x0
_020C0BE0:
	ldr r0, _020C0D14 ; =0x021D1E08
	mov r1, r10
	bl FUN_020ADA98
	ldrb r1, [r10, #0x2d]
	mov r9, r0
	cmp r1, #0x0
	bne _020C0C0C
	ldr r0, [r10, #0x30]
	bl SND_IsFinishedCommandTag
_020C0C04: ; 0x020C0C04
	cmp r0, #0x0
	strneb r5, [r10, #0x2d]
_020C0C0C:
	ldrb r0, [r10, #0x2d]
	cmp r0, #0x0
	beq _020C0C38
	ldrb r0, [r10, #0x3c]
	mov r1, r5, lsl r0
	ldr r0, [sp, #0x0]
	ands r0, r0, r1
	bne _020C0C38
	mov r0, r10
	bl FUN_020C077C
	b _020C0D00
_020C0C38:
	add r0, r10, #0x1c
	bl FUN_020C3DF4
	ldr r0, [r10, #0x4]
	ldrb r2, [r10, #0x41]
	ldrb r1, [r10, #0x40]
	ldrb r0, [r0, #0x20]
	mov r3, r2, lsl #0x1
	mov r2, r1, lsl #0x1
	mov r1, r0, lsl #0x1
	add r0, r10, #0x1c
	ldrsh r8, [r4, r3]
	ldrsh r7, [r4, r2]
	ldrsh r6, [r4, r1]
	bl FUN_020C3E0C
	mov r0, r0, asr #0x8
	mov r2, r0, lsl #0x1
	add r1, r7, r8
	mov r0, #0x8000
	ldrsh r2, [r4, r2]
	add r1, r6, r1
	rsb r0, r0, #0x0
	add r6, r2, r1
	cmp r6, r0
	ldrlt r6, [sp, #0x4]
	blt _020C0CA8
	ldr r0, _020C0D1C ; =0x00007FFF
	cmp r6, r0
	movgt r6, r0
_020C0CA8:
	ldrsh r0, [r10, #0x3e]
	cmp r6, r0
	beq _020C0CC4
	ldrb r0, [r10, #0x3c]
	mov r1, r6
	bl SND_SetPlayerVolume
	strh r6, [r10, #0x3e]
_020C0CC4:
	ldrb r0, [r10, #0x2c]
	cmp r0, #0x2
	bne _020C0CE8
	add r0, r10, #0x1c
	bl FUN_020C3DDC
_020C0CD8: ; 0x020C0CD8
	cmp r0, #0x0
	beq _020C0CE8
	mov r0, r10
	bl FUN_020C087C
_020C0CE8:
	ldrb r0, [r10, #0x2f]
	cmp r0, #0x0
	beq _020C0D00
	ldrb r0, [r10, #0x3c]
	bl SND_StartPreparedSeq
	strb r11, [r10, #0x2f]
_020C0D00:
	mov r10, r9
	cmp r9, #0x0
	bne _020C0BE0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020C0D14: .word 0x021D1E08
_020C0D18: .word 0x02103BAC
_020C0D1C: .word 0x00007FFF

	arm_func_start FUN_020C0D20
FUN_020C0D20: ; 0x020C0D20
	stmdb sp!, {r4-r10,lr}
	ldr r0, _020C0DC4 ; =0x021D1E08
	mov r1, #0x14
	bl FUN_020ADC74
	ldr r0, _020C0DC8 ; =0x021D1DFC
	mov r1, #0x14
	bl FUN_020ADC74
	ldr r6, _020C0DCC ; =0x021D1E14
	mov r7, #0x0
	ldr r4, _020C0DC8 ; =0x021D1DFC
	mov r5, r7
_020C0D4C:
	strb r5, [r6, #0x2c]
	mov r0, r4
	mov r1, r6
	strb r7, [r6, #0x3c]
	bl FUN_020ADBE8
	add r7, r7, #0x1
	cmp r7, #0x10
	add r6, r6, #0x44
	blt _020C0D4C
	ldr sl, _020C0DD0 ; =0x021D2254
	mov r9, #0x0
	mov r7, r9
	mov r4, r9
	mov r8, #0xc
	mov r6, #0x7f
	mov r5, #0x1
_020C0D8C:
	mov r0, r10
	mov r1, r8
	bl FUN_020ADC74
	mov r1, r7
	add r0, r10, #0xc
	bl FUN_020ADC74
	strb r6, [r10, #0x20]
	str r5, [r10, #0x18]
	add r9, r9, #0x1
	str r4, [r10, #0x1c]
	cmp r9, #0x20
	add r10, r10, #0x24
	blt _020C0D8C
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020C0DC4: .word 0x021D1E08
_020C0DC8: .word 0x021D1DFC
_020C0DCC: .word 0x021D1E14
_020C0DD0: .word 0x021D2254

	arm_func_start FUN_020C0DD4
FUN_020C0DD4: ; 0x020C0DD4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {pc}
	ldrb r0, [r1, #0x2d]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {pc}
	ldrb r0, [r1, #0x3c]
	bl SND_GetPlayerTickCounter
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C0E14
FUN_020C0E14: ; 0x020C0E14
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	mvneq r0, #0x0
	bxeq lr
	ldrh r0, [r1, #0x34]
	cmp r0, #0x1
	mvnne r0, #0x0
	ldreqh r0, [r1, #0x38]
	bx lr

	arm_func_start FUN_020C0E38
FUN_020C0E38: ; 0x020C0E38
	ldr r12, [r0, #0x0]
	cmp r12, #0x0
	bxeq lr
	mov r3, #0x2
	strh r3, [r12, #0x34]
	ldr r3, [r0, #0x0]
	strh r1, [r3, #0x38]
	ldr r0, [r0, #0x0]
	strh r2, [r0, #0x3a]
	bx lr

	arm_func_start FUN_020C0E60
FUN_020C0E60: ; 0x020C0E60
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	movne r2, #0x1
	strneh r2, [r3, #0x34]
	ldrne r0, [r0, #0x0]
	strneh r1, [r0, #0x38]
	bx lr

	arm_func_start FUN_020C0E7C
FUN_020C0E7C: ; 0x020C0E7C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldrb r0, [r0, #0x3c]
	bl SND_SetTrackPan
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C0EA4
FUN_020C0EA4: ; 0x020C0EA4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldrb r0, [r0, #0x3c]
	bl SND_SetTrackPitch
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C0ECC
FUN_020C0ECC: ; 0x020C0ECC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldrb r0, [r0, #0x3c]
	bl SND_SetPlayerChannelPriority
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C0EF4
FUN_020C0EF4: ; 0x020C0EF4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldrb r0, [r3, #0x2c]
	cmp r0, #0x2
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	add r0, r3, #0x1c
	mov r1, r1, lsl #0x8
	bl FUN_020C3E40
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C0F30
FUN_020C0F30: ; 0x020C0F30
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	strneb r1, [r0, #0x40]
	bx lr

	arm_func_start FUN_020C0F40
FUN_020C0F40: ; 0x020C0F40
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	strneb r1, [r0, #0x41]
	bx lr

	arm_func_start FUN_020C0F50
FUN_020C0F50: ; 0x020C0F50
	mov r1, #0x24
	mul r1, r0, r1
	ldr r0, _020C0F64 ; =0x021D225C
	ldrh r0, [r0, r1]
	bx lr
	.balign 4
_020C0F64: .word 0x021D225C

	arm_func_start FUN_020C0F68
FUN_020C0F68: ; 0x020C0F68
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	movne r1, #0x0
	strne r1, [r2, #0x0]
	strne r1, [r0, #0x0]
	bx lr

	arm_func_start FUN_020C0F80
FUN_020C0F80: ; 0x020C0F80
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr

	arm_func_start FUN_020C0F8C
FUN_020C0F8C: ; 0x020C0F8C
	ldr ip, _020C0F98 ; =FUN_020C0A04
	ldr r0, [r0, #0x0]
	bx r12
	.balign 4
_020C0F98: .word FUN_020C0A04

	arm_func_start FUN_020C0F9C
FUN_020C0F9C: ; 0x020C0F9C
	stmdb sp!, {r4-r6,lr}
	ldr r4, _020C0FD8 ; =0x021D1E14
	mov r6, r0
	mov r5, #0x0
_020C0FAC:
	ldrb r0, [r4, #0x2c]
	cmp r0, #0x0
	beq _020C0FC4
	mov r0, r4
	mov r1, r6
	bl FUN_020C0A40
_020C0FC4:
	add r5, r5, #0x1
	cmp r5, #0x10
	add r4, r4, #0x44
	blt _020C0FAC
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C0FD8: .word 0x021D1E14

	arm_func_start FUN_020C0FDC
FUN_020C0FDC: ; 0x020C0FDC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r4, _020C103C ; =0x021D1E14
	mov r7, r0
	mov r6, r1
	mov r5, #0x0
_020C0FF4:
	ldrb r0, [r4, #0x2c]
	cmp r0, #0x0
	beq _020C1024
	ldrh r0, [r4, #0x34]
	cmp r0, #0x1
	bne _020C1024
	ldrh r0, [r4, #0x38]
	cmp r0, r7
	bne _020C1024
	mov r0, r4
	mov r1, r6
	bl FUN_020C0A40
_020C1024:
	add r5, r5, #0x1
	cmp r5, #0x10
	add r4, r4, #0x44
	blt _020C0FF4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C103C: .word 0x021D1E14

	arm_func_start FUN_020C1040
FUN_020C1040: ; 0x020C1040
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r3, _020C109C ; =0x021D2254
	mov r2, #0x24
	mla r4, r0, r2, r3
	ldr r5, _020C10A0 ; =0x021D1E14
	mov r7, r1
	mov r6, #0x0
_020C1060:
	ldrb r0, [r5, #0x2c]
	cmp r0, #0x0
	beq _020C1084
	ldr r0, [r5, #0x4]
	cmp r0, r4
	bne _020C1084
	mov r0, r5
	mov r1, r7
	bl FUN_020C0A40
_020C1084:
	add r6, r6, #0x1
	cmp r6, #0x10
	add r5, r5, #0x44
	blt _020C1060
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C109C: .word 0x021D2254
_020C10A0: .word 0x021D1E14

	arm_func_start FUN_020C10A4
FUN_020C10A4: ; 0x020C10A4
	ldr ip, _020C10B0 ; =FUN_020C0A40
	ldr r0, [r0, #0x0]
	bx r12
	.balign 4
_020C10B0: .word FUN_020C0A40

	arm_func_start FUN_020C10B4
FUN_020C10B4:
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r5, r2
	mov r6, r0
	mov r0, r1
	mov r3, #0x0
	ldr r2, _020C1140 ; =FUN_020C072C
	add r1, r5, #0x14
	str r3, [sp, #0x0]
	bl FUN_020C2958
	movs r4, r0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020C10EC: ; 0x020C10EC
	mov r2, #0x0
	str r2, [r4, #0xc]
	str r6, [r4, #0x10]
	mov r1, r5
	add r0, r4, #0x14
	str r2, [r4, #0x8]
	bl FUN_020C2A94
_020C1108: ; 0x020C1108
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020C1118: ; 0x020C1118
	ldr r2, _020C1144 ; =0x021D2254
	mov r1, #0x24
	mla r2, r6, r1, r2
	str r0, [r4, #0x8]
	mov r1, r4
	add r0, r2, #0xc
	bl FUN_020ADBE8
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C1140: .word FUN_020C072C
_020C1144: .word 0x021D2254

	arm_func_start FUN_020C1148
FUN_020C1148: ; 0x020C1148
	mov r2, #0x24
	mul r2, r0, r2
	ldr r0, _020C115C ; =0x021D2270
	str r1, [r0, r2]
	bx lr
	.balign 4
_020C115C: .word 0x021D2270

	arm_func_start FUN_020C1160
FUN_020C1160: ; 0x020C1160
	mov r2, #0x24
	mul r2, r0, r2
	mov r0, r1, lsl #0x10
	ldr r1, _020C117C ; =0x021D226C
	mov r0, r0, lsr #0x10
	str r0, [r1, r2]
	bx lr
	.balign 4
_020C117C: .word 0x021D226C

	arm_func_start FUN_020C1180
FUN_020C1180: ; 0x020C1180
	mov r2, #0x24
	mul r2, r0, r2
	ldr r0, _020C1194 ; =0x021D2274
	strb r1, [r0, r2]
	bx lr
	.balign 4
_020C1194: .word 0x021D2274

	arm_func_start FUN_020C1198
FUN_020C1198: ; 0x020C1198
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	ldr r0, [r4, #0x24]
	mov r0, r0, lsl #0x1e
	movs r0, r0, asr #0x1f
	ldmeqia sp!, {r4-r6,pc}
_020C11B0: ; 0x020C11B0
	ldr r0, [r4, #0x38]
	cmp r0, #0x0
	beq _020C11E8
	mov r5, #0x1
_020C11C0:
	bl OS_DisableInterrupts
	mov r6, r0
	mov r0, r4
	mov r1, r5
	bl FUN_020C1254
	mov r0, r6
	bl OS_RestoreInterrupts
	ldr r0, [r4, #0x38]
	cmp r0, #0x0
	bne _020C11C0
_020C11E8:
	ldr r0, [r4, #0x40]
	mov r2, #0x1
	mov r1, #0x0
	mov r2, r2, lsl r0
	ldr r0, [r4, #0x44]
	mov r3, r1
	bl SND_StartTimer
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020C1208
FUN_020C1208: ; 0x020C1208
	stmdb sp!, {r4,lr}
	ldr r1, [r0, #0x24]
	mov r1, r1, lsl #0x1e
	movs r1, r1, asr #0x1f
	ldmeqia sp!, {r4,pc}
_020C121C: ; 0x020C121C
	ldr r2, [r0, #0x40]
	mov r3, #0x1
	mov r1, #0x0
	mov r2, r3, lsl r2
	ldr r0, [r0, #0x44]
	mov r3, r1
	bl SND_StopTimer
	bl SND_GetCurrentCommandTag
	mov r4, r0
	mov r0, #0x1
	bl SND_FlushCommand
	mov r0, r4
	bl SND_WaitForCommandProc
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C1254
FUN_020C1254: ; 0x020C1254
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r5, r0
	mov r4, r1
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	bl _u32_div_f
	ldr r1, [r5, #0x48]
	ldr r2, [r5, #0x38]
	mov r3, r0
	mul lr, r3, r2
	cmp r1, #0x0
	mov r12, #0x0
	ble _020C12B8
	ldr r2, _020C1300 ; =0x021D2724
	ldr r0, _020C1304 ; =0x021D26E4
_020C1294:
	add r1, r5, r12
	ldrb r1, [r1, #0x4c]
	ldr r1, [r2, r1, lsl #0x3]
	add r1, r1, lr
	str r1, [r0, r12, lsl #0x2]
	ldr r1, [r5, #0x48]
	add r12, r12, #0x1
	cmp r12, r1
	blt _020C1294
_020C12B8:
	ldr r0, [r5, #0x20]
	ldr r2, _020C1304 ; =0x021D26E4
	str r0, [sp, #0x0]
	ldr r12, [r5, #0x34]
	mov r0, r4
	str r12, [sp, #0x4]
	ldr r4, [r5, #0x30]
	blx r4
	ldr r0, [r5, #0x38]
	add r0, r0, #0x1
	str r0, [r5, #0x38]
	ldr r1, [r5, #0x38]
	ldr r0, [r5, #0x2c]
	cmp r1, r0
	movge r0, #0x0
	strge r0, [r5, #0x38]
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C1300: .word 0x021D2724
_020C1304: .word 0x021D26E4

	arm_func_start FUN_020C1308
FUN_020C1308: ; 0x020C1308
	ldr ip, _020C1314 ; =FUN_020C1254
	mov r1, #0x1
	bx r12
	.balign 4
_020C1314: .word FUN_020C1254

	arm_func_start FUN_020C1318
FUN_020C1318: ; 0x020C1318
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x40]
	bl FUN_020C029C
	ldr r0, _020C1344 ; =0x021D26D8
	mov r1, r4
	bl FUN_020ADAB0
	ldr r0, [r4, #0x24]
	bic r0, r0, #0x1
	str r0, [r4, #0x24]
	ldmia sp!, {r4,pc}
	.balign 4
_020C1344: .word 0x021D26D8

	arm_func_start FUN_020C1348
FUN_020C1348: ; 0x020C1348
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldr r0, [r4, #0x24]
	mov r0, r0, lsl #0x1e
	movs r0, r0, asr #0x1f
	beq _020C13B4
	ldr r0, [r4, #0x40]
	mov r2, #0x1
	mov r1, #0x0
	mov r2, r2, lsl r0
	ldr r0, [r4, #0x44]
	mov r3, r1
	bl SND_StopTimer
	add r0, r4, #0x8
	bl PM_DeletePreSleepCallback
	add r0, r4, #0x14
	bl PM_DeletePostSleepCallback
	ldr r0, [r4, #0x24]
	bic r0, r0, #0x2
	str r0, [r4, #0x24]
	bl SND_GetCurrentCommandTag
	mov r5, r0
	mov r0, #0x1
	bl SND_FlushCommand
	mov r0, r5
	bl SND_WaitForCommandProc
_020C13B4:
	mov r0, r4
	bl FUN_020C1318
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C13C4
FUN_020C13C4: ; 0x020C13C4
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	str r1, [r7, #0x3c]
	ldr r0, [r7, #0x48]
	mov r5, #0x0
	cmp r0, #0x0
	ldmleia sp!, {r4-r8,pc}
_020C13E0: ; 0x020C13E0
	ldr r4, _020C142C ; =0x021D2724
	mov r8, #0x1
_020C13E8:
	add r0, r7, r5
	ldrb r6, [r0, #0x4c]
	ldr r1, [r7, #0x3c]
	add r0, r4, r6, lsl #0x3
	ldr r0, [r0, #0x4]
	add r0, r1, r0
	bl SND_CalcChannelVolume
	mov r2, r0
	mov r0, r8, lsl r6
	and r1, r2, #0xff
	mov r2, r2, asr #0x8
	bl SND_SetChannelVolume
	ldr r0, [r7, #0x48]
	add r5, r5, #0x1
	cmp r5, r0
	blt _020C13E8
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020C142C: .word 0x021D2724

	arm_func_start FUN_020C1430
FUN_020C1430: ; 0x020C1430
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, [r0, #0x24]
	mov r1, r1, lsl #0x1f
	movs r1, r1, asr #0x1f
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	bl FUN_020C1348
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C1458
FUN_020C1458: ; 0x020C1458
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x40]
	mov r2, #0x1
	mov r1, #0x0
	mov r2, r2, lsl r0
	ldr r0, [r4, #0x44]
	mov r3, r1
	bl SND_StartTimer
	ldr r0, [r4, #0x24]
	mov r0, r0, lsl #0x1e
	movs r0, r0, asr #0x1f
	ldmneia sp!, {r4,pc}
_020C148C: ; 0x020C148C
	add r0, r4, #0x8
	bl PM_PrependPreSleepCallback
	add r0, r4, #0x14
	bl PM_AppendPostSleepCallback
	ldr r0, [r4, #0x24]
	orr r0, r0, #0x2
	str r0, [r4, #0x24]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C14AC
FUN_020C14AC: ; 0x020C14AC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x24
	mov r10, r0
	ldr r4, [r10, #0x24]
	mov r9, r1
	mov r1, r4, lsl #0x1f
	movs r1, r1, asr #0x1f
	ldr r1, [sp, #0x4c]
	str r2, [sp, #0x18]
	mov r4, r3
	str r1, [sp, #0x4c]
	beq _020C14E0
	bl FUN_020C1430
_020C14E0:
	ldr r0, [sp, #0x4c]
	ldr r2, [r10, #0x48]
	mov r0, r0, lsl #0x5
	mul r1, r2, r0
	mov r0, r4
	bl _u32_div_f
	ldr r1, [sp, #0x4c]
	ldr r2, [sp, #0x48]
	mul r1, r0, r1
	mov r0, r1, lsl #0x5
	str r0, [r10, #0x28]
	ldr r0, [r10, #0x28]
	cmp r9, #0x1
	moveq r0, r0, lsr #0x1
	mul r0, r2, r0
	ldr r1, [sp, #0x4c]
	bl _u32_div_f
	str r0, [sp, #0x1c]
	bl FUN_020C02BC
	str r0, [r10, #0x40]
	ldr r0, [r10, #0x40]
	cmp r0, #0x0
	addlt sp, sp, #0x24
	movlt r0, #0x0
	ldmltia sp!, {r4-r11,pc}
_020C1544: ; 0x020C1544
	ldr r0, [r10, #0x48]
	mov r8, #0x0
	cmp r0, #0x0
	ble _020C15D4
	ldr r0, [sp, #0x48]
	mov r7, r0, lsl #0x5
	ldr r6, _020C1668 ; =0x021D2724
	mov r5, r8
	mov r4, #0x7f
	mov r11, #0x40
	mov r0, #0x1
	str r0, [sp, #0x20]
_020C1574:
	ldr r2, [r10, #0x28]
	ldr r1, [sp, #0x18]
	add r0, r10, r8
	mla r1, r2, r8, r1
	ldrb r0, [r0, #0x4c]
	ldr r3, [sp, #0x20]
	str r1, [r6, r0, lsl #0x3]
	add r1, r6, r0, lsl #0x3
	str r5, [r1, #0x4]
	str r5, [sp, #0x0]
	ldr r2, [r10, #0x28]
	mov r1, r9
	mov r2, r2, lsr #0x2
	str r2, [sp, #0x4]
	str r4, [sp, #0x8]
	str r5, [sp, #0xc]
	str r7, [sp, #0x10]
	str r11, [sp, #0x14]
	ldr r2, [r6, r0, lsl #0x3]
	bl SND_SetupChannelPcm
	ldr r0, [r10, #0x48]
	add r8, r8, #0x1
	cmp r8, r0
	blt _020C1574
_020C15D4:
	str r10, [sp, #0x0]
	ldr r1, [sp, #0x1c]
	ldr r0, [r10, #0x40]
	ldr r3, _020C166C ; =FUN_020C1308
	mov r2, r1
	bl SND_SetupAlarm
	ldr r0, _020C1670 ; =0x021D26D8
	mov r1, r10
	bl FUN_020ADBE8
	ldr r0, [sp, #0x4c]
	str r9, [r10, #0x20]
	str r0, [r10, #0x2c]
	ldr r1, [sp, #0x50]
	ldr r0, [sp, #0x54]
	str r1, [r10, #0x30]
	str r0, [r10, #0x34]
	mov r0, #0x0
	str r0, [r10, #0x38]
	str r0, [r10, #0x3c]
	ldr r0, [r10, #0x24]
	bic r0, r0, #0x1
	orr r0, r0, #0x1
	str r0, [r10, #0x24]
	bl OS_DisableInterrupts
	mov r4, r0
	mov r2, #0x1
	mov r0, r10
	mov r1, #0x0
	str r2, [r10, #0x2c]
	bl FUN_020C1254
	ldr r1, [sp, #0x4c]
	mov r0, r4
	str r1, [r10, #0x2c]
	bl OS_RestoreInterrupts
	mov r0, #0x1
	add sp, sp, #0x24
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020C1668: .word 0x021D2724
_020C166C: .word FUN_020C1308
_020C1670: .word 0x021D26D8

	arm_func_start FUN_020C1674
FUN_020C1674: ; 0x020C1674
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x44]
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
_020C1688: ; 0x020C1688
	bl FUN_020C0340
_020C168C: ; 0x020C168C
	mov r0, #0x0
	str r0, [r4, #0x44]
	str r0, [r4, #0x48]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C169C
FUN_020C169C: ; 0x020C169C
	stmdb sp!, {r4-r6,lr}
	mov r5, r1
	mov r4, #0x0
	mov r6, r0
	mov r12, r4
	cmp r5, #0x0
	ble _020C16DC
	mov r1, #0x1
_020C16BC:
	ldrb r3, [r2, r12]
	add r0, r6, r12
	strb r3, [r0, #0x4c]
	ldrb r0, [r2, r12]
	add r12, r12, #0x1
	cmp r12, r5
	orr r4, r4, r1, lsl r0
	blt _020C16BC
_020C16DC:
	mov r0, r4
	bl FUN_020C0370
_020C16E4: ; 0x020C16E4
	cmp r0, #0x0
	moveq r0, #0x0
	strne r5, [r6, #0x48]
	strne r4, [r6, #0x44]
	movne r0, #0x1
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020C16FC
FUN_020C16FC: ; 0x020C16FC
	stmdb sp!, {r4,lr}
	ldr r1, _020C176C ; =0x021D26D4
	mov r4, r0
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	bne _020C172C
	ldr r0, _020C1770 ; =0x021D26D8
	mov r1, #0x0
	bl FUN_020ADC74
	ldr r0, _020C176C ; =0x021D26D4
	mov r1, #0x1
	str r1, [r0, #0x0]
_020C172C:
	ldr r1, _020C1774 ; =FUN_020C1208
	ldr r0, _020C1778 ; =FUN_020C1198
	str r1, [r4, #0x8]
	str r4, [r4, #0xc]
	str r0, [r4, #0x14]
	str r4, [r4, #0x18]
	mov r0, #0x0
	str r0, [r4, #0x44]
	str r0, [r4, #0x48]
	ldr r0, [r4, #0x24]
	bic r0, r0, #0x1
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x24]
	bic r0, r0, #0x2
	str r0, [r4, #0x24]
	ldmia sp!, {r4,pc}
	.balign 4
_020C176C: .word 0x021D26D4
_020C1770: .word 0x021D26D8
_020C1774: .word FUN_020C1208
_020C1778: .word FUN_020C1198

	arm_func_start FUN_020C177C
FUN_020C177C: ; 0x020C177C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldr r4, [r7, #0x18]
	ldr r0, [r7, #0x1c]
	ldr r1, _020C186C ; =0x021D27A4
	mul r0, r4, r0
	ldr r3, [r7, #0xc]
	ldr r2, [r7, #0x10]
	ldr r1, [r1, #0x0]
	add r6, r3, r0
	cmp r1, #0x0
	add r5, r2, r0
	beq _020C180C
	ldr r2, _020C1870 ; =0x021D27A8
	mov r1, #0x14
	ldr r2, [r2, #0x0]
	ldr r3, _020C1874 ; =0x021D2820
	mul r1, r2, r1
	str r7, [r3, r1]
	add r1, r3, r1
	str r4, [r1, #0x4]
	str r0, [r1, #0x8]
	str r6, [r1, #0xc]
	ldr r0, _020C1878 ; =0x021D27AC
	mov r2, #0x0
	str r5, [r1, #0x10]
	bl OS_SendMessage
	ldr r0, _020C1870 ; =0x021D27A8
	ldr r1, [r0, #0x0]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	cmp r1, #0x8
	movge r1, #0x0
	strge r1, [r0, #0x0]
	b _020C1844
_020C180C:
	mov r0, r6
	mov r1, r4
	bl DC_InvalidateRange
	mov r0, r5
	mov r1, r4
	bl DC_InvalidateRange
	ldr r1, [r7, #0x38]
	mov r0, r6
	str r1, [sp, #0x0]
	ldr r3, [r7, #0x8]
	ldr r6, [r7, #0x34]
	mov r1, r5
	mov r2, r4
	blx r6
_020C1844:
	ldr r0, [r7, #0x1c]
	add r0, r0, #0x1
	str r0, [r7, #0x1c]
	ldr r1, [r7, #0x1c]
	ldr r0, [r7, #0x30]
	cmp r1, r0
	movge r0, #0x0
	strge r0, [r7, #0x1c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C186C: .word 0x021D27A4
_020C1870: .word 0x021D27A8
_020C1874: .word 0x021D2820
_020C1878: .word 0x021D27AC

	arm_func_start FUN_020C187C
FUN_020C187C: ; 0x020C187C
	stmdb sp!, {r4,lr}
	ldr r4, _020C18F4 ; =0x021D27CC
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
_020C1890: ; 0x020C1890
	mov r0, #0x0
	str r0, [r4, #0x1c]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x14]
	bl MIi_CpuClear32
	ldr r1, [r4, #0x10]
	ldr r2, [r4, #0x14]
	mov r0, #0x0
	bl MIi_CpuClear32
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x14]
	bl DC_FlushRange
	ldr r0, [r4, #0x10]
	ldr r1, [r4, #0x14]
	bl DC_FlushRange
	ldr r1, [r4, #0x2c]
	mov r3, #0x0
	cmp r1, #0x0
	movge r0, #0x1
	movge r2, r0, lsl r1
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x28]
	movlt r2, #0x0
	bl SND_StartTimer
	ldmia sp!, {r4,pc}
	.balign 4
_020C18F4: .word 0x021D27CC

	arm_func_start FUN_020C18F8
FUN_020C18F8:
	stmdb sp!, {r4,lr}
	ldr r3, _020C194C ; =0x021D27CC
	ldr r0, [r3, #0x0]
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
_020C190C: ; 0x020C190C
	ldr r1, [r3, #0x2c]
	cmp r1, #0x0
	movge r0, #0x1
	movge r2, r0, lsl r1
	ldr r0, [r3, #0x24]
	ldr r1, [r3, #0x28]
	movlt r2, #0x0
	mov r3, #0x0
	bl SND_StopTimer
	bl SND_GetCurrentCommandTag
	mov r4, r0
	mov r0, #0x1
	bl SND_FlushCommand
	mov r0, r4
	bl SND_WaitForCommandProc
	ldmia sp!, {r4,pc}
	.balign 4
_020C194C: .word 0x021D27CC

	arm_func_start FUN_020C1950
FUN_020C1950: ; 0x020C1950
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r4, _020C1A3C ; =0x021D27CC
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
_020C196C: ; 0x020C196C
	ldr r1, [r4, #0x2c]
	mov r3, #0x0
	cmp r1, #0x0
	movge r7, #0x1
	movlt r7, #0x0
	cmp r7, #0x0
	movne r0, #0x1
	movne r2, r0, lsl r1
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x28]
	moveq r2, #0x0
	bl SND_StopTimer
_020C199C: ; 0x020C199C
	cmp r7, #0x0
	beq _020C19DC
	bl SND_GetCurrentCommandTag
	mov r5, r0
	mov r0, #0x1
	bl SND_FlushCommand
	mov r0, r5
	bl SND_WaitForCommandProc
	ldr r6, _020C1A40 ; =0x021D27AC
	mov r5, #0x0
_020C19C4:
	mov r0, r6
	mov r1, r5
	mov r2, r5
	bl OS_ReceiveMessage
_020C19D4: ; 0x020C19D4
	cmp r0, #0x0
	bne _020C19C4
_020C19DC:
	ldr r0, [r4, #0x28]
	cmp r0, #0x0
	beq _020C19EC
	bl FUN_020C0300
_020C19EC:
	ldr r0, [r4, #0x20]
	cmp r0, #0x0
	beq _020C19FC
	bl FUN_020C0340
_020C19FC:
	cmp r7, #0x0
	beq _020C1A0C
	ldr r0, [r4, #0x2c]
	bl FUN_020C029C
_020C1A0C:
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	bne _020C1A2C
	mov r0, #0x0
	mov r1, r0
	mov r2, r0
	mov r3, r0
	bl SND_SetOutputSelector
_020C1A2C:
	mov r0, #0x0
	str r0, [r4, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C1A3C: .word 0x021D27CC
_020C1A40: .word 0x021D27AC

	arm_func_start FUN_020C1A44
FUN_020C1A44: ; 0x020C1A44
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x3c
	mov r10, r3
	str r0, [sp, #0x18]
	str r2, [sp, #0x20]
	mov r2, #0x0
	str r1, [sp, #0x1c]
	mov r0, r1
	mov r1, r10
	ldr r9, [sp, #0x6c]
	ldr r8, [sp, #0x74]
	str r2, [sp, #0x2c]
	mvn r6, #0x0
	ldr r4, _020C1D90 ; =0x021D27CC
	bl DC_FlushRange
	ldr r0, [sp, #0x20]
	mov r1, r10
	bl DC_FlushRange
	ldr r0, [sp, #0x60]
	ldr r1, [sp, #0x70]
	cmp r0, #0x1
	moveq r7, #0x1
	ldr r0, _020C1D94 ; =0x00FFB0FF
	movne r7, #0x0
	bl _s32_div_f
	ldr r1, [sp, #0x84]
	mov r11, r0
	cmp r1, #0x0
	beq _020C1B00
	add r1, r11, #0x10
	bic r11, r1, #0x1f
	mov r2, r11, asr #0x5
	mov r0, r10
	cmp r7, #0x0
	ldr r1, [sp, #0x80]
	moveq r0, r10, lsr #0x1
	str r2, [sp, #0x34]
	bl _u32_div_f
	ldr r1, [sp, #0x34]
	mov r5, #0x20
	mul r0, r1, r0
	str r0, [sp, #0x30]
	cmp r7, #0x0
	ldr r0, [sp, #0x34]
	moveq r5, r5, lsr #0x1
	mul r0, r5, r0
	mov r5, r0
_020C1B00:
	cmp r7, #0x0
	movne r0, #0x0
	strne r0, [sp, #0x28]
	moveq r0, #0x1
	streq r0, [sp, #0x28]
	cmp r7, #0x0
	movne r0, #0x1
	strne r0, [sp, #0x24]
	moveq r0, #0x0
	streq r0, [sp, #0x24]
	ldr r0, [sp, #0x18]
	cmp r0, #0x2
	movne r0, #0xa
	strne r0, [sp, #0x2c]
	ldr r0, [sp, #0x84]
	cmp r0, #0x0
	beq _020C1B58
	bl FUN_020C02BC
	movs r6, r0
	addmi sp, sp, #0x3c
	movmi r0, #0x0
	ldmmiia sp!, {r4-r11,pc}
_020C1B58:
	mov r0, #0x3
	bl FUN_020C031C
_020C1B60: ; 0x020C1B60
	cmp r0, #0x0
	bne _020C1B84
	cmp r6, #0x0
	blt _020C1B78
	mov r0, r6
	bl FUN_020C029C
_020C1B78:
	add sp, sp, #0x3c
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_020C1B84:
	mov r0, #0xa
	bl FUN_020C0370
_020C1B8C: ; 0x020C1B8C
	cmp r0, #0x0
	bne _020C1BB8
	cmp r6, #0x0
	blt _020C1BA4
	mov r0, r6
	bl FUN_020C029C
_020C1BA4:
	mov r0, #0x3
	bl FUN_020C0300
	add sp, sp, #0x3c
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_020C1BB8:
	mov r0, #0x0
	mov r7, r10, lsr #0x2
	str r0, [sp, #0x0]
	str r7, [sp, #0x4]
	str r8, [sp, #0x8]
	str r0, [sp, #0xc]
	cmp r9, #0x0
	movne r3, #0x1
	ldr r1, [sp, #0x78]
	str r11, [sp, #0x10]
	str r1, [sp, #0x14]
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x1c]
	moveq r3, #0x2
	mov r0, #0x1
	bl SND_SetupChannelPcm
	ldr r1, [sp, #0x64]
	str r9, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r0, [sp, #0x68]
	ldr r1, [sp, #0x24]
	str r0, [sp, #0x8]
	ldr r2, [sp, #0x1c]
	mov r0, #0x0
	mov r3, r7
	bl SND_SetupCapture
_020C1C20: ; 0x020C1C20
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r7, [sp, #0x4]
	str r8, [sp, #0x8]
	str r0, [sp, #0xc]
	cmp r9, #0x0
	movne r3, #0x1
	ldr r2, [sp, #0x7c]
	str r11, [sp, #0x10]
	str r2, [sp, #0x14]
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x20]
	moveq r3, #0x2
	mov r0, #0x3
	bl SND_SetupChannelPcm
	ldr r2, [sp, #0x64]
	str r9, [sp, #0x0]
	str r2, [sp, #0x4]
	ldr r0, [sp, #0x68]
	ldr r1, [sp, #0x24]
	str r0, [sp, #0x8]
	ldr r2, [sp, #0x20]
	mov r3, r7
	mov r0, #0x1
	bl SND_SetupCapture
_020C1C84: ; 0x020C1C84
	cmp r6, #0x0
	blt _020C1CA8
	ldr r2, [sp, #0x30]
	ldr r3, _020C1D98 ; =FUN_020C177C
	mov r1, r2
	mov r0, r6
	add r1, r1, r5
	str r4, [sp, #0x0]
	bl SND_SetupAlarm
_020C1CA8:
	ldr r0, [sp, #0x18]
	cmp r0, #0x1
	bne _020C1CC8
	mov r0, #0x1
	mov r2, r0
	mov r3, r0
	mov r1, #0x2
	bl SND_SetOutputSelector
_020C1CC8:
	cmp r6, #0x0
	movge r0, #0x1
	movge r2, r0, lsl r6
	ldr r0, [sp, #0x2c]
	movlt r2, #0x0
	mov r1, #0x3
	mov r3, #0x0
	bl SND_StartTimer
	mov r0, #0x1
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x80]
	str r0, [r4, #0x4]
	mov r0, #0xa
	str r0, [r4, #0x20]
	ldr r0, [sp, #0x2c]
	str r0, [r4, #0x24]
	mov r0, #0x3
	str r0, [r4, #0x28]
	ldr r0, [sp, #0x60]
	str r6, [r4, #0x2c]
	str r0, [r4, #0x8]
	ldr r0, [sp, #0x1c]
	str r0, [r4, #0xc]
	ldr r0, [sp, #0x20]
	str r0, [r4, #0x10]
	mov r0, r10
	str r10, [r4, #0x14]
	bl _u32_div_f
	str r0, [r4, #0x18]
	mov r1, #0x0
	str r1, [r4, #0x1c]
	ldr r0, [sp, #0x80]
	ldr r1, [sp, #0x84]
	str r0, [r4, #0x30]
	ldr r0, [sp, #0x88]
	str r1, [r4, #0x34]
	str r0, [r4, #0x38]
	add r0, r4, #0x3c
	str r8, [r4, #0x50]
	bl FUN_020C3E6C
	add r0, r4, #0x3c
	mov r1, r8, lsl #0x8
	mov r2, #0x1
	bl FUN_020C3E40
_020C1D7C: ; 0x020C1D7C
	mov r0, #0x0
	str r0, [r4, #0x4c]
	mov r0, #0x1
	add sp, sp, #0x3c
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020C1D90: .word 0x021D27CC
_020C1D94: .word 0x00FFB0FF
_020C1D98: .word FUN_020C177C

	arm_func_start FUN_020C1D9C
FUN_020C1D9C: ; 0x020C1D9C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r5, _020C1E34 ; =0x021D27CC
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
_020C1DB8: ; 0x020C1DB8
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,pc}
_020C1DC8: ; 0x020C1DC8
	add r4, r5, #0x3c
	mov r0, r4
	bl FUN_020C3DF4
	ldr r0, [r5, #0x4c]
	cmp r0, #0x0
	beq _020C1DFC
	mov r0, r4
	bl FUN_020C3DDC
_020C1DE8: ; 0x020C1DE8
	cmp r0, #0x0
	beq _020C1DFC
	bl FUN_020C1950
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
_020C1DFC:
	mov r0, r4
	bl FUN_020C3E0C
	ldr r1, [r5, #0x50]
	mov r4, r0, asr #0x8
	cmp r4, r1
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
_020C1E18: ; 0x020C1E18
	ldr r0, [r5, #0x24]
	mov r1, r4
	mov r2, #0x0
	bl SND_SetChannelVolume
	str r4, [r5, #0x50]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C1E34: .word 0x021D27CC

	arm_func_start FUN_020C1E38
FUN_020C1E38: ; 0x020C1E38
	ldr r1, _020C1E50 ; =0x021D27A4
	mov r2, #0x0
	ldr r0, _020C1E54 ; =0x021D27CC
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	bx lr
	.balign 4
_020C1E50: .word 0x021D27A4
_020C1E54: .word 0x021D27CC

	arm_func_start FUN_020C1E58
FUN_020C1E58: ; 0x020C1E58
	ldr r0, _020C1E64 ; =0x021D27CC
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020C1E64: .word 0x021D27CC

	arm_func_start FUN_020C1E68
FUN_020C1E68: ; 0x020C1E68
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C1EA0 ; =0x021D27CC
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r0, [r0, #0x4]
	cmp r0, #0x1
	addne sp, sp, #0x4
	ldmneia sp!, {pc}
	bl FUN_020C1950
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020C1EA0: .word 0x021D27CC

	arm_func_start FUN_020C1EA4
FUN_020C1EA4: ; 0x020C1EA4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x2c
	mov r5, r0
	mov r4, r1
	mov r7, r2
	mov r6, r3
	bl FUN_020C1E68
	ldr r0, _020C1F50 ; =0x021D27CC
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x2c
	movne r0, #0x0
	ldmneia sp!, {r4-r7,pc}
_020C1ED8: ; 0x020C1ED8
	mov r1, r5
	mov r2, r4
	mov r0, #0x0
	bl MIi_CpuClear32
	mov r0, r5
	mov r1, r4
	bl DC_FlushRange
	str r7, [sp, #0x0]
	mov r2, #0x0
	str r2, [sp, #0x4]
	str r2, [sp, #0x8]
	mov r0, #0x1
	str r0, [sp, #0xc]
	str r6, [sp, #0x10]
	mov r1, #0x7f
	str r1, [sp, #0x14]
	str r2, [sp, #0x18]
	ldr r2, [sp, #0x40]
	str r1, [sp, #0x1c]
	ldr r1, [sp, #0x44]
	str r2, [sp, #0x20]
	ldr r12, [sp, #0x48]
	str r1, [sp, #0x24]
	mov r1, r5
	mov r3, r4, lsr #0x1
	add r2, r5, r4, lsr #0x1
	str r12, [sp, #0x28]
	bl FUN_020C1A44
	add sp, sp, #0x2c
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C1F50: .word 0x021D27CC

	arm_func_start FUN_020C1F54
FUN_020C1F54: ; 0x020C1F54
	stmdb sp!, {r4,lr}
	ldr r4, _020C1FA0 ; =0x021D27CC
	mov r2, r0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
_020C1F6C: ; 0x020C1F6C
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	ldmneia sp!, {r4,pc}
_020C1F78: ; 0x020C1F78
	cmp r2, #0x0
	bne _020C1F88
	bl FUN_020C1950
	ldmia sp!, {r4,pc}
_020C1F88:
	add r0, r4, #0x3c
	mov r1, #0x0
	bl FUN_020C3E40
	mov r0, #0x1
	str r0, [r4, #0x4c]
	ldmia sp!, {r4,pc}
	.balign 4
_020C1FA0: .word 0x021D27CC

	arm_func_start FUN_020C1FA4
FUN_020C1FA4: ; 0x020C1FA4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, _020C1FEC ; =0x021D27CC
	mov r12, r0
	ldr r0, [r3, #0x0]
	mov r2, r1
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r0, [r3, #0x4]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {pc}
	add r0, r3, #0x3c
	mov r1, r12, lsl #0x8
	bl FUN_020C3E40
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020C1FEC: .word 0x021D27CC

	arm_func_start FUN_020C1FF0
FUN_020C1FF0: ; 0x020C1FF0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x2c
	mov r5, r0
	mov r0, #0x0
	mov r4, r1
	mov r7, r2
	mov r6, r3
	bl FUN_020C1F54
	ldr r0, _020C2098 ; =0x021D27CC
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x2c
	movne r0, #0x0
	ldmneia sp!, {r4-r7,pc}
_020C2028: ; 0x020C2028
	mov r1, r5
	mov r2, r4
	mov r0, #0x0
	bl MIi_CpuClear32
	mov r0, r5
	mov r1, r4
	bl DC_FlushRange
	str r7, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r1, #0x1
	str r1, [sp, #0xc]
	ldr r1, [sp, #0x40]
	str r6, [sp, #0x10]
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	mov r1, #0x7f
	str r1, [sp, #0x1c]
	str r0, [sp, #0x20]
	str r0, [sp, #0x24]
	mov r1, r5
	mov r3, r4, lsr #0x1
	add r2, r5, r4, lsr #0x1
	str r0, [sp, #0x28]
	bl FUN_020C1A44
	add sp, sp, #0x2c
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C2098: .word 0x021D27CC

	arm_func_start FUN_020C209C
FUN_020C209C: ; 0x020C209C
	mov r0, #0x0
	str r0, [r2, #0x88]
	bx lr

	arm_func_start FUN_020C20A8
FUN_020C20A8: ; 0x020C20A8
	mov r0, #0x0
	str r0, [r2, #0x84]
	bx lr

	arm_func_start FUN_020C20B4
FUN_020C20B4: ; 0x020C20B4
	mov r0, #0x0
	str r0, [r2, #0x8c]
	bx lr

	arm_func_start FUN_020C20C0
FUN_020C20C0: ; 0x020C20C0
	ldr r2, _020C20D8 ; =0x021D28C0
	ldr r2, [r2, #0x0]
	ldr r2, [r2, #0x84]
	add r0, r2, r0, lsl #0x4
	str r1, [r0, #0x14]
	bx lr
	.balign 4
_020C20D8: .word 0x021D28C0

	arm_func_start FUN_020C20DC
FUN_020C20DC:
	ldr r1, _020C2100 ; =0x021D28C0
	ldr r1, [r1, #0x0]
	ldr r2, [r1, #0x84]
	ldr r1, [r2, #0x8]
	cmp r0, r1
	movcs r0, #0x0
	addcc r0, r2, r0, lsl #0x4
	ldrcc r0, [r0, #0x14]
	bx lr
	.balign 4
_020C2100: .word 0x021D28C0

	arm_func_start FUN_020C2104
FUN_020C2104:
	stmdb sp!, {r4-r6,lr}
	ldr r4, _020C2178 ; =0x021D28C0
	mov r5, r2
	ldr r4, [r4, #0x0]
	mov r6, r1
	ldr r2, [r4, #0x84]
	ldr r1, [r2, #0x8]
	cmp r0, r1
	mvncs r0, #0x0
	ldmcsia sp!, {r4-r6,pc}
_020C212C: ; 0x020C212C
	add r1, r2, #0xc
	add r1, r1, r0, lsl #0x4
	ldr r0, [r1, #0x4]
	ldr r1, [r1, #0x0]
	sub r0, r0, r3
	cmp r5, r0
	movhi r5, r0
	add r0, r4, #0x34
	add r1, r1, r3
	mov r2, #0x0
	bl FS_SeekFile
_020C2158: ; 0x020C2158
	cmp r0, #0x0
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020C2164: ; 0x020C2164
	mov r1, r6
	mov r2, r5
	add r0, r4, #0x34
	bl FS_ReadFile
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C2178: .word 0x021D28C0

	arm_func_start FUN_020C217C
FUN_020C217C: ; 0x020C217C
	ldr r1, _020C21A0 ; =0x021D28C0
	ldr r1, [r1, #0x0]
	ldr r2, [r1, #0x84]
	ldr r1, [r2, #0x8]
	cmp r0, r1
	movcs r0, #0x0
	addcc r0, r2, r0, lsl #0x4
	ldrcc r0, [r0, #0x10]
	bx lr
	.balign 4
_020C21A0: .word 0x021D28C0

	arm_func_start FUN_020C21A4
FUN_020C21A4: ; 0x020C21A4
	ldr r1, _020C2204 ; =0x021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0x1c]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C2204: .word 0x021D28C0

	arm_func_start FUN_020C2208
FUN_020C2208: ; 0x020C2208
	ldr r1, _020C2268 ; =0x021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0x18]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C2268: .word 0x021D28C0

	arm_func_start FUN_020C226C
FUN_020C226C:
	ldr r1, _020C22CC ; =0x021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0x14]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C22CC: .word 0x021D28C0

	arm_func_start FUN_020C22D0
FUN_020C22D0: ; 0x020C22D0
	ldr r1, _020C2330 ; =0x021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0x10]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C2330: .word 0x021D28C0

	arm_func_start FUN_020C2334
FUN_020C2334:
	ldr r1, _020C2394 ; =0x021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0xc]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C2394: .word 0x021D28C0

	arm_func_start FUN_020C2398
FUN_020C2398:
	ldr r1, _020C23F8 ; =0x021D28C0
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0x8c]
	ldr r1, [r2, #0x8]
	cmp r1, #0x0
	moveq r2, #0x0
	addne r2, r2, r1
	cmp r2, #0x0
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r1, [r2, #0x0]
	cmp r0, r1
	movcs r0, #0x0
	bxcs lr
	add r0, r2, r0, lsl #0x2
	ldr r1, [r0, #0x4]
	ldr r0, [r3, #0x8c]
	cmp r1, #0x0
	moveq r0, #0x0
	addne r0, r0, r1
	bx lr
	.balign 4
_020C23F8: .word 0x021D28C0

	arm_func_start FUN_020C23FC
FUN_020C23FC: ; 0x020C23FC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020C2398
_020C2408: ; 0x020C2408
	cmp r0, #0x0
	moveq r0, #0x0
	addne r0, r0, #0x4
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C241C
FUN_020C241C: ; 0x020C241C
	ldr r0, _020C2428 ; =0x021D28C0
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020C2428: .word 0x021D28C0

	arm_func_start FUN_020C242C
FUN_020C242C: ; 0x020C242C
	ldr r1, _020C2440 ; =0x021D28C0
	ldr r2, [r1, #0x0]
	str r0, [r1, #0x0]
	mov r0, r2
	bx lr
	.balign 4
_020C2440: .word 0x021D28C0

	arm_func_start FUN_020C2444
FUN_020C2444: ; 0x020C2444
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	mov r0, r4
	mov r1, r5
	mov r2, #0x30
	bl MIi_CpuCopy32
	ldr r0, [r5, #0x18]
	mov r12, #0x0
	cmp r0, #0x0
	moveq r0, #0x0
	addne r0, r4, r0
	str r0, [r5, #0x8c]
	ldr r0, [r5, #0x20]
	cmp r0, #0x0
	moveq r0, #0x0
	addne r0, r4, r0
	str r0, [r5, #0x84]
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	moveq r0, #0x0
	addne r0, r4, r0
	str r0, [r5, #0x88]
	ldr r2, [r5, #0x84]
	ldr r0, [r2, #0x8]
	cmp r0, #0x0
	bls _020C24F0
	mov r3, r12
	mov r1, r12
_020C24BC:
	add r2, r2, #0xc
	ldr r0, [r2, r3]
	add r2, r2, r3
	cmp r0, #0x0
	moveq r0, r1
	addne r0, r4, r0
	str r0, [r2, #0x8]
	ldr r2, [r5, #0x84]
	add r12, r12, #0x1
	ldr r0, [r2, #0x8]
	add r3, r3, #0x10
	cmp r12, r0
	blo _020C24BC
_020C24F0:
	mov r1, #0x0
	ldr r0, _020C2508 ; =0x021D28C0
	str r1, [r5, #0x30]
	str r5, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C2508: .word 0x021D28C0

	arm_func_start FUN_020C250C
FUN_020C250C:
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r6, r0
	mov r5, r1
	mov r1, #0x0
	mov r4, r2
	mov r2, r1
	add r0, r6, #0x34
	bl FS_SeekFile
_020C2530: ; 0x020C2530
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020C2540: ; 0x020C2540
	mov r1, r6
	add r0, r6, #0x34
	mov r2, #0x30
	bl FS_ReadFile
	cmp r0, #0x30
	addne sp, sp, #0x8
	movne r0, #0x0
	ldmneia sp!, {r4-r6,pc}
_020C2560: ; 0x020C2560
	cmp r5, #0x0
	beq _020C26E0
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, [r6, #0x1c]
	ldr r2, _020C26EC ; =FUN_020C20B4
	mov r0, r5
	mov r3, r6
	bl FUN_020C2958
	str r0, [r6, #0x8c]
	ldr r0, [r6, #0x8c]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020C259C: ; 0x020C259C
	ldr r1, [r6, #0x18]
	add r0, r6, #0x34
	mov r2, #0x0
	bl FS_SeekFile
_020C25AC: ; 0x020C25AC
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020C25BC: ; 0x020C25BC
	ldr r1, [r6, #0x8c]
	ldr r2, [r6, #0x1c]
	add r0, r6, #0x34
	bl FS_ReadFile
	ldr r1, [r6, #0x1c]
	cmp r0, r1
	addne sp, sp, #0x8
	movne r0, #0x0
	ldmneia sp!, {r4-r6,pc}
_020C25E0: ; 0x020C25E0
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, [r6, #0x24]
	ldr r2, _020C26F0 ; =FUN_020C20A8
	mov r0, r5
	mov r3, r6
	bl FUN_020C2958
	str r0, [r6, #0x84]
	ldr r0, [r6, #0x84]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020C2614: ; 0x020C2614
	ldr r1, [r6, #0x20]
	add r0, r6, #0x34
	mov r2, #0x0
	bl FS_SeekFile
_020C2624: ; 0x020C2624
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020C2634: ; 0x020C2634
	ldr r1, [r6, #0x84]
	ldr r2, [r6, #0x24]
	add r0, r6, #0x34
	bl FS_ReadFile
	ldr r1, [r6, #0x24]
	cmp r0, r1
	addne sp, sp, #0x8
	movne r0, #0x0
	ldmneia sp!, {r4-r6,pc}
_020C2658: ; 0x020C2658
	cmp r4, #0x0
	beq _020C26E0
	ldr r1, [r6, #0x14]
	cmp r1, #0x0
	beq _020C26E0
	mov r4, #0x0
	ldr r2, _020C26F4 ; =FUN_020C209C
	mov r0, r5
	mov r3, r6
	str r4, [sp, #0x0]
	bl FUN_020C2958
	str r0, [r6, #0x88]
	ldr r0, [r6, #0x88]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, r4
	ldmeqia sp!, {r4-r6,pc}
_020C269C: ; 0x020C269C
	ldr r1, [r6, #0x10]
	add r0, r6, #0x34
	mov r2, r4
	bl FS_SeekFile
_020C26AC: ; 0x020C26AC
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, r4
	ldmeqia sp!, {r4-r6,pc}
_020C26BC: ; 0x020C26BC
	ldr r1, [r6, #0x88]
	ldr r2, [r6, #0x14]
	add r0, r6, #0x34
	bl FS_ReadFile
	ldr r1, [r6, #0x14]
	cmp r0, r1
	addne sp, sp, #0x8
	movne r0, r4
	ldmneia sp!, {r4-r6,pc}
_020C26E0:
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C26EC: .word FUN_020C20B4
_020C26F0: .word FUN_020C20A8
_020C26F4: .word FUN_020C209C

	arm_func_start FUN_020C26F8
FUN_020C26F8: ; 0x020C26F8
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r12, #0x0
	str r12, [r6, #0x8c]
	str r12, [r6, #0x84]
	add r0, r6, #0x7c
	mov r5, r2
	mov r4, r3
	str r12, [r6, #0x88]
	bl FS_ConvertPathToFileID
_020C2720: ; 0x020C2720
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020C2728: ; 0x020C2728
	add r0, r6, #0x34
	bl FS_InitFile
	add r1, r6, #0x7c
	add r0, r6, #0x34
	ldmia r1, {r1-r2}
	bl FS_OpenFileFast
_020C2740: ; 0x020C2740
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
_020C2748: ; 0x020C2748
	mov r3, #0x1
	mov r0, r6
	mov r1, r5
	mov r2, r4
	str r3, [r6, #0x30]
	bl FUN_020C250C
_020C2760: ; 0x020C2760
	cmp r0, #0x0
	ldrne r0, _020C2770 ; =0x021D28C0
	strne r6, [r0, #0x0]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C2770: .word 0x021D28C0

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

	arm_func_start FUN_020C2794
FUN_020C2794:
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
_020C27C0: ; 0x020C27C0
	bl FUN_020C2818
	mov r1, r4
	add r0, r5, #0x4
	bl FUN_020ADBE8
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C27DC
FUN_020C27DC:
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
_020C2804: ; 0x020C2804
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C2818
FUN_020C2818: ; 0x020C2818
	ldr ip, _020C2824 ; =FUN_020ADC74
	mov r1, #0x0
	bx r12
	.balign 4
_020C2824: .word FUN_020ADC74

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
_020C28E4: ; 0x020C28E4
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

	arm_func_start FUN_020C290C
FUN_020C290C: ; 0x020C290C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldrh r1, [r4, #0xc]
	ldr r0, [r4, #0x0]
	bl FUN_020AE5B0
_020C2920: ; 0x020C2920
	cmp r0, #0x0
	mvneq r0, #0x0
	ldmeqia sp!, {r4,pc}
_020C292C: ; 0x020C292C
	mov r0, r4
	bl FUN_020C2794
_020C2934: ; 0x020C2934
	cmp r0, #0x0
	ldrneh r0, [r4, #0xc]
	subne r0, r0, #0x1
	ldmneia sp!, {r4,pc}
_020C2944: ; 0x020C2944
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl FUN_020AE554
_020C2950: ; 0x020C2950
	mvn r0, #0x0
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C2958
FUN_020C2958: ; 0x020C2958
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
	bl FUN_020AE638
	movs r4, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
_020C2990: ; 0x020C2990
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

	arm_func_start FUN_020C29C0
FUN_020C29C0:
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
_020C2A64: ; 0x020C2A64
	cmp r5, #0x0
	beq _020C2A70
	bl FUN_020C2774
_020C2A70:
	mov r0, r8
	bl FUN_020C2794
	ldmia sp!, {r4-r10,pc}

	arm_func_start FUN_020C2A7C
FUN_020C2A7C: ; 0x020C2A7C
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020C29C0
_020C2A88: ; 0x020C2A88
	ldr r0, [r4, #0x0]
	bl thunk_FUN_020adc8c_2
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C2A94
FUN_020C2A94:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	add r2, r0, #0x3
	add r0, r0, r1
	bic r5, r2, #0x3
	cmp r5, r0
	addhi sp, sp, #0x4
	movhi r0, #0x0
	ldmhiia sp!, {r4-r5,pc}
_020C2AB8: ; 0x020C2AB8
	sub r1, r0, r5
	cmp r1, #0x10
	addcc sp, sp, #0x4
	movcc r0, #0x0
	ldmccia sp!, {r4-r5,pc}
_020C2ACC: ; 0x020C2ACC
	add r0, r5, #0x10
	sub r1, r1, #0x10
	mov r2, #0x0
	bl FUN_020AE684
	movs r4, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
_020C2AEC: ; 0x020C2AEC
	mov r0, r5
	mov r1, r4
	bl FUN_020C27DC
_020C2AF8: ; 0x020C2AF8
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, r5
	ldmneia sp!, {r4-r5,pc}
_020C2B08: ; 0x020C2B08
	mov r0, r4
	bl thunk_FUN_020adc8c_2
_020C2B10: ; 0x020C2B10
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C2B1C
FUN_020C2B1C:
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x20
	mov r8, r0
	add r0, sp, #0x8
	mov r7, r1
	mov r6, r2
	mov r5, r3
	ldr r4, [sp, #0x40]
	bl SND_GetFirstInstDataPos
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	cmp r7, #0x0
	add r2, sp, #0x0
	addeq sp, sp, #0x20
	moveq r0, #0x0
	ldmeqia sp!, {r4-r10,pc}
_020C2B64: ; 0x020C2B64
	add r1, sp, #0x10
	mov r0, r7
	bl SND_GetNextInstData
_020C2B70: ; 0x020C2B70
	cmp r0, #0x0
	beq _020C2BD4
	add r10, sp, #0x10
	add r9, sp, #0x0
_020C2B80:
	ldrb r0, [sp, #0x10]
	cmp r0, #0x1
	bne _020C2BBC
	ldrh r0, [sp, #0x14]
	cmp r6, r0
	bne _020C2BBC
	ldrh r1, [sp, #0x12]
	mov r0, r8
	mov r2, r5
	mov r3, r4
	bl FUN_020C2BE0
_020C2BAC: ; 0x020C2BAC
	cmp r0, #0x0
	addeq sp, sp, #0x20
	moveq r0, #0x0
	ldmeqia sp!, {r4-r10,pc}
_020C2BBC:
	mov r0, r7
	mov r1, r10
	mov r2, r9
	bl SND_GetNextInstData
_020C2BCC: ; 0x020C2BCC
	cmp r0, #0x0
	bne _020C2B80
_020C2BD4:
	mov r0, #0x1
	add sp, sp, #0x20
	ldmia sp!, {r4-r10,pc}

	arm_func_start FUN_020C2BE0
FUN_020C2BE0:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl SND_GetWaveDataAddress
_020C2BFC: ; 0x020C2BFC
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, #0x1
	ldmneia sp!, {r4-r9,pc}
_020C2C0C: ; 0x020C2C0C
	mov r0, r7
	bl SND_GetWaveDataCount
	ldr r1, [r7, #0x38]
	sub r0, r0, #0x1
	add r1, r1, r6
	add r1, r7, r1, lsl #0x2
	cmp r6, r0
	ldrcc r0, [r1, #0x40]
	ldr r8, [r1, #0x3c]
	ldrcs r0, [r7, #0x8]
	cmp r4, #0x0
	sub r9, r0, r8
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,pc}
_020C2C48: ; 0x020C2C48
	ldr r2, _020C2CBC ; =FUN_020C2CC0
	mov r0, r4
	mov r3, r7
	add r1, r9, #0x20
	str r6, [sp, #0x0]
	bl FUN_020C2958
	movs r4, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,pc}
_020C2C70: ; 0x020C2C70
	mov r0, r5
	mov r1, r4
	mov r2, r9
	mov r3, r8
	bl FUN_020C2104
_020C2C84: ; 0x020C2C84
	cmp r9, r0
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r9,pc}
_020C2C94: ; 0x020C2C94
	mov r0, r4
	mov r1, r9
	bl DC_StoreRange
	mov r0, r7
	mov r1, r6
	mov r2, r4
	bl SND_SetWaveDataAddress
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020C2CBC: .word FUN_020C2CC0

	arm_func_start FUN_020C2CC0
FUN_020C2CC0: ; 0x020C2CC0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r2
	mov r7, r0
	mov r4, r3
	mov r6, r1
	mov r0, r5
	mov r1, r4
	bl SND_GetWaveDataAddress
_020C2CE4: ; 0x020C2CE4
	cmp r7, r0
	bne _020C2CFC
	mov r0, r5
	mov r1, r4
	mov r2, #0x0
	bl SND_SetWaveDataAddress
_020C2CFC:
	mov r0, r7
	add r1, r7, r6
	bl SND_InvalidateWaveData
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020C2D10
FUN_020C2D10: ; 0x020C2D10
	stmdb sp!, {r4,lr}
	mov r1, r2
	mov r4, r0
	mov r2, r3
	bl FUN_020C2DD0
	mov r0, r4
	bl SND_DestroyWaveArc
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C2D30
FUN_020C2D30: ; 0x020C2D30
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r1, r2
	mov r5, r0
	mov r2, r3
	bl FUN_020C2DD0
	mov r0, r5
	add r1, r5, r4
	bl SND_InvalidateWaveData
	mov r0, r5
	bl SND_DestroyWaveArc
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C2D68
FUN_020C2D68: ; 0x020C2D68
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r1, r2
	mov r5, r0
	mov r2, r3
	bl FUN_020C2DD0
	mov r0, r5
	add r1, r5, r4
	bl SND_InvalidateBankData
	mov r0, r5
	bl SND_DestroyBank
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C2DA0
FUN_020C2DA0: ; 0x020C2DA0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r1, r2
	mov r5, r0
	mov r2, r3
	bl FUN_020C2DD0
	mov r0, r5
	add r1, r5, r4
	bl SND_InvalidateSeqData
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C2DD0
FUN_020C2DD0: ; 0x020C2DD0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	movs r5, r1
	mov r7, r0
	mov r6, r2
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
_020C2DEC: ; 0x020C2DEC
	bl OS_DisableInterrupts
	mov r4, r0
	mov r0, r5
	bl FUN_020C242C
	mov r5, r0
	mov r0, r6
	bl FUN_020C20DC
_020C2E08: ; 0x020C2E08
	cmp r7, r0
	bne _020C2E1C
	mov r0, r6
	mov r1, #0x0
	bl FUN_020C20C0
_020C2E1C:
	mov r0, r5
	bl FUN_020C242C
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020C2E34
FUN_020C2E34: ; 0x020C2E34
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	mov r8, r1
	mov r7, r2
	bl FUN_020C20DC
	movs r6, r0
	bne _020C2F40
	ldr r1, _020C2F4C ; =0x021D28C4
	mov r0, r9
	mov r2, #0x3c
	mov r3, #0x0
	bl FUN_020C2104
	cmp r0, #0x3c
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r9,pc}
_020C2E78: ; 0x020C2E78
	ldr r0, _020C2F4C ; =0x021D28C4
	cmp r8, #0x0
	ldr r0, [r0, #0x38]
	addeq sp, sp, #0x4
	mov r4, r0, lsl #0x2
	mov r0, r4, lsl #0x1
	add r5, r0, #0x3c
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,pc}
_020C2E9C: ; 0x020C2E9C
	cmp r7, #0x0
	moveq r3, #0x0
	beq _020C2EB0
	bl FUN_020C241C
	mov r3, r0
_020C2EB0:
	ldr r2, _020C2F50 ; =FUN_020C2D10
	mov r0, r8
	add r1, r5, #0x20
	str r9, [sp, #0x0]
	bl FUN_020C2958
	movs r6, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,pc}
_020C2ED4: ; 0x020C2ED4
	mov r0, r9
	mov r1, r6
	add r2, r4, #0x3c
	mov r3, #0x0
	bl FUN_020C2104
	add r1, r4, #0x3c
	cmp r0, r1
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r9,pc}
_020C2EFC: ; 0x020C2EFC
	ldr r1, [r6, #0x38]
	add r0, r6, #0x3c
	mov r2, r4
	add r1, r0, r1, lsl #0x2
	bl MI_CpuCopy8
	mov r2, r4
	add r0, r6, #0x3c
	mov r1, #0x0
	bl MI_CpuFill8
	mov r0, r6
	mov r1, r5
	bl DC_StoreRange
_020C2F2C: ; 0x020C2F2C
	cmp r7, #0x0
	beq _020C2F40
	mov r0, r9
	mov r1, r6
	bl FUN_020C20C0
_020C2F40:
	mov r0, r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020C2F4C: .word 0x021D28C4
_020C2F50: .word FUN_020C2D10

	arm_func_start FUN_020C2F54
FUN_020C2F54:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl FUN_020C20DC
	movs r4, r0
	bne _020C2FBC
	cmp r5, #0x0
	moveq r2, #0x0
	beq _020C2F88
	bl FUN_020C241C
	mov r2, r0
_020C2F88:
	ldr r1, _020C2FC8 ; =FUN_020C2D30
	mov r0, r7
	mov r3, r7
	str r6, [sp, #0x0]
	bl FUN_020C3134
	mov r4, r0
	cmp r5, #0x0
	beq _020C2FBC
	cmp r4, #0x0
	beq _020C2FBC
	mov r0, r7
	mov r1, r4
	bl FUN_020C20C0
_020C2FBC:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C2FC8: .word FUN_020C2D30

	arm_func_start FUN_020C2FCC
FUN_020C2FCC: ; 0x020C2FCC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl FUN_020C20DC
	movs r4, r0
	bne _020C3034
	cmp r5, #0x0
	moveq r2, #0x0
	beq _020C3000
	bl FUN_020C241C
	mov r2, r0
_020C3000:
	ldr r1, _020C3040 ; =FUN_020C2D68
	mov r0, r7
	mov r3, r7
	str r6, [sp, #0x0]
	bl FUN_020C3134
	mov r4, r0
	cmp r5, #0x0
	beq _020C3034
	cmp r4, #0x0
	beq _020C3034
	mov r0, r7
	mov r1, r4
	bl FUN_020C20C0
_020C3034:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C3040: .word FUN_020C2D68

	arm_func_start FUN_020C3044
FUN_020C3044:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl FUN_020C20DC
	movs r4, r0
	bne _020C30AC
	cmp r5, #0x0
	moveq r2, #0x0
	beq _020C3078
	bl FUN_020C241C
	mov r2, r0
_020C3078:
	ldr r1, _020C30B8 ; =FUN_020C2DA0
	mov r0, r7
	mov r3, r7
	str r6, [sp, #0x0]
	bl FUN_020C3134
	mov r4, r0
	cmp r5, #0x0
	beq _020C30AC
	cmp r4, #0x0
	beq _020C30AC
	mov r0, r7
	mov r1, r4
	bl FUN_020C20C0
_020C30AC:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C30B8: .word FUN_020C2DA0

	arm_func_start FUN_020C30BC
FUN_020C30BC:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl FUN_020C20DC
	movs r4, r0
	bne _020C3124
	cmp r5, #0x0
	moveq r2, #0x0
	beq _020C30F0
	bl FUN_020C241C
	mov r2, r0
_020C30F0:
	ldr r1, _020C3130 ; =FUN_020C2DA0
	mov r0, r7
	mov r3, r7
	str r6, [sp, #0x0]
	bl FUN_020C3134
	mov r4, r0
	cmp r5, #0x0
	beq _020C3124
	cmp r4, #0x0
	beq _020C3124
	mov r0, r7
	mov r1, r4
	bl FUN_020C20C0
_020C3124:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C3130: .word FUN_020C2DA0

	arm_func_start FUN_020C3134
FUN_020C3134: ; 0x020C3134
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r4, r3
	bl FUN_020C217C
	movs r5, r0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
_020C3160: ; 0x020C3160
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
_020C3174: ; 0x020C3174
	mov r2, r7
	mov r3, r6
	add r1, r5, #0x20
	str r4, [sp, #0x0]
	bl FUN_020C2958
	movs r4, r0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
_020C3198: ; 0x020C3198
	mov r0, r8
	mov r1, r4
	mov r2, r5
	mov r3, #0x0
	bl FUN_020C2104
_020C31AC: ; 0x020C31AC
	cmp r5, r0
	addne sp, sp, #0x8
	movne r0, #0x0
	ldmneia sp!, {r4-r8,pc}
_020C31BC: ; 0x020C31BC
	mov r0, r4
	mov r1, r5
	bl DC_StoreRange
	mov r0, r4
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020C31D4
FUN_020C31D4:
	stmdb sp!, {r4-r6,lr}
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl FUN_020C226C
_020C31E8: ; 0x020C31E8
	cmp r0, #0x0
	moveq r0, #0x5
	ldmeqia sp!, {r4-r6,pc}
_020C31F4: ; 0x020C31F4
	ands r1, r6, #0x4
	beq _020C324C
	ldrb r1, [r0, #0x3]
	ands r1, r1, #0x1
	beq _020C3224
	ldr r0, [r0, #0x0]
	mov r1, r5
	mov r0, r0, lsl #0x8
	mov r2, r4
	mov r0, r0, lsr #0x8
	bl FUN_020C2E34
	b _020C323C
_020C3224:
	ldr r0, [r0, #0x0]
	mov r1, r5
	mov r0, r0, lsl #0x8
	mov r2, r4
	mov r0, r0, lsr #0x8
	bl FUN_020C2F54
_020C323C:
	cmp r0, #0x0
	bne _020C325C
	mov r0, #0x9
	ldmia sp!, {r4-r6,pc}
_020C324C:
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x8
	mov r0, r0, lsr #0x8
	bl FUN_020C20DC
_020C325C:
	ldr r1, [sp, #0x10]
	cmp r1, #0x0
	strne r0, [r1, #0x0]
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020C3270
FUN_020C3270:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r10, r1
	mov r9, r2
	mov r11, r3
	bl FUN_020C22D0
	movs r8, r0
	addeq sp, sp, #0xc
	moveq r0, #0x4
	ldmeqia sp!, {r4-r11,pc}
_020C3298: ; 0x020C3298
	ands r0, r10, #0x2
	beq _020C32C4
	ldr r0, [r8, #0x0]
	mov r1, r9
	mov r2, r11
	bl FUN_020C2FCC
	movs r7, r0
	bne _020C32D0
	add sp, sp, #0xc
	mov r0, #0x8
	ldmia sp!, {r4-r11,pc}
_020C32C4:
	ldr r0, [r8, #0x0]
	bl FUN_020C20DC
	mov r7, r0
_020C32D0:
	and r5, r10, #0x4
	mov r6, #0x0
_020C32D8:
	add r0, r8, r6, lsl #0x1
	ldrh r0, [r0, #0x4]
	ldr r1, _020C33B4 ; =0x0000FFFF
	cmp r0, r1
	beq _020C3390
	bl FUN_020C226C
	movs r4, r0
	addeq sp, sp, #0xc
	moveq r0, #0x5
	ldmeqia sp!, {r4-r11,pc}
_020C3300: ; 0x020C3300
	add r0, sp, #0x4
	str r0, [sp, #0x0]
	add r0, r8, r6, lsl #0x1
	ldrh r0, [r0, #0x4]
	mov r1, r10
	mov r2, r9
	mov r3, r11
	bl FUN_020C31D4
_020C3320: ; 0x020C3320
	cmp r0, #0x0
	addne sp, sp, #0xc
	ldmneia sp!, {r4-r11,pc}
_020C332C: ; 0x020C332C
	ldrb r0, [r4, #0x3]
	ands r0, r0, #0x1
	beq _020C3370
	cmp r5, #0x0
	beq _020C3370
	str r9, [sp, #0x0]
	ldr r1, [r4, #0x0]
	ldr r0, [sp, #0x4]
	mov r3, r1, lsl #0x8
	mov r1, r7
	mov r2, r6
	mov r3, r3, lsr #0x8
	bl FUN_020C2B1C
_020C3360: ; 0x020C3360
	cmp r0, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x9
	ldmeqia sp!, {r4-r11,pc}
_020C3370:
	cmp r7, #0x0
	beq _020C3390
	ldr r2, [sp, #0x4]
	cmp r2, #0x0
	beq _020C3390
	mov r0, r7
	mov r1, r6
	bl SND_AssignWaveArc
_020C3390:
	add r6, r6, #0x1
	cmp r6, #0x4
	blt _020C32D8
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	strne r7, [r0, #0x0]
	mov r0, #0x0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020C33B4: .word 0x0000FFFF

	arm_func_start FUN_020C33B8
FUN_020C33B8:
	stmdb sp!, {r4-r6,lr}
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl FUN_020C2334
_020C33CC: ; 0x020C33CC
	cmp r0, #0x0
	moveq r0, #0x3
	ldmeqia sp!, {r4-r6,pc}
_020C33D8: ; 0x020C33D8
	ands r1, r6, #0x8
	beq _020C3400
	ldr r0, [r0, #0x0]
	mov r1, r5
	mov r2, r4
	bl FUN_020C3044
_020C33F0: ; 0x020C33F0
	cmp r0, #0x0
	bne _020C3408
	mov r0, #0x7
	ldmia sp!, {r4-r6,pc}
_020C3400:
	ldr r0, [r0, #0x0]
	bl FUN_020C20DC
_020C3408:
	ldr r1, [sp, #0x10]
	cmp r1, #0x0
	strne r0, [r1, #0x0]
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020C341C
FUN_020C341C:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r1
	mov r6, r2
	mov r5, r3
	bl FUN_020C2398
	movs r4, r0
	addeq sp, sp, #0x4
	moveq r0, #0x2
	ldmeqia sp!, {r4-r7,pc}
_020C3444: ; 0x020C3444
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldrh r0, [r4, #0x4]
	mov r1, r7
	mov r2, r6
	mov r3, r5
	bl FUN_020C3270
_020C3460: ; 0x020C3460
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,pc}
_020C346C: ; 0x020C346C
	ands r0, r7, #0x1
	beq _020C3498
	ldr r0, [r4, #0x0]
	mov r1, r6
	mov r2, r5
	bl FUN_020C30BC
_020C3484: ; 0x020C3484
	cmp r0, #0x0
	bne _020C34A0
	add sp, sp, #0x4
	mov r0, #0x6
	ldmia sp!, {r4-r7,pc}
_020C3498:
	ldr r0, [r4, #0x0]
	bl FUN_020C20DC
_020C34A0:
	ldr r1, [sp, #0x18]
	cmp r1, #0x0
	strne r0, [r1, #0x0]
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020C34B8
FUN_020C34B8:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r9, r1
	bl FUN_020C21A4
	movs r8, r0
	addeq sp, sp, #0xc
	moveq r0, #0x1
	ldmeqia sp!, {r4-r11,pc}
_020C34D8: ; 0x020C34D8
	ldr r0, [r8, #0x0]
	mov r7, #0x0
	cmp r0, #0x0
	bls _020C35D4
	add r6, r8, #0x4
	str r7, [sp, #0x4]
	mov r11, r7
	mov r10, r7
	mov r5, r7
	mov r4, #0x1
_020C3500:
	ldrb r0, [r6, #0x0]
	cmp r0, #0x3
	addls pc, pc, r0, lsl #0x2
	b _020C35C0
_020C3510:
	b _020C3520
_020C3514:
	b _020C3570
_020C3518:
	b _020C3598
_020C351C:
	b _020C3548
_020C3520:
	str r5, [sp, #0x0]
	ldrb r1, [r6, #0x1]
	ldr r0, [r6, #0x4]
	mov r2, r9
	mov r3, r4
	bl FUN_020C341C
_020C3538: ; 0x020C3538
	cmp r0, #0x0
	beq _020C35C0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
_020C3548:
	str r10, [sp, #0x0]
	ldrb r1, [r6, #0x1]
	ldr r0, [r6, #0x4]
	mov r2, r9
	mov r3, r4
	bl FUN_020C33B8
_020C3560: ; 0x020C3560
	cmp r0, #0x0
	beq _020C35C0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
_020C3570:
	str r11, [sp, #0x0]
	ldrb r1, [r6, #0x1]
	ldr r0, [r6, #0x4]
	mov r2, r9
	mov r3, r4
	bl FUN_020C3270
_020C3588: ; 0x020C3588
	cmp r0, #0x0
	beq _020C35C0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
_020C3598:
	ldr r0, [sp, #0x4]
	mov r2, r9
	str r0, [sp, #0x0]
	ldrb r1, [r6, #0x1]
	ldr r0, [r6, #0x4]
	mov r3, r4
	bl FUN_020C31D4
_020C35B4: ; 0x020C35B4
	cmp r0, #0x0
	addne sp, sp, #0xc
	ldmneia sp!, {r4-r11,pc}
_020C35C0:
	ldr r0, [r8, #0x0]
	add r7, r7, #0x1
	cmp r7, r0
	add r6, r6, #0x8
	blo _020C3500
_020C35D4:
	mov r0, #0x0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}

	arm_func_start FUN_020C35E0
FUN_020C35E0: ; 0x020C35E0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r12, #0x0
	mov r3, #0x1
	str r12, [sp, #0x0]
	bl FUN_020C341C
_020C35F8: ; 0x020C35F8
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C360C
FUN_020C360C: ; 0x020C360C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r12, #0x0
	mov r1, #0xff
	mov r3, #0x1
	str r12, [sp, #0x0]
	bl FUN_020C31D4
_020C362C: ; 0x020C362C
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C3640
FUN_020C3640: ; 0x020C3640
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r12, #0x0
	mov r1, #0xff
	mov r3, #0x1
	str r12, [sp, #0x0]
	bl FUN_020C3270
_020C3660: ; 0x020C3660
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C3674
FUN_020C3674: ; 0x020C3674
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r12, #0x0
	mov r1, #0xff
	mov r3, #0x1
	str r12, [sp, #0x0]
	bl FUN_020C341C
_020C3694: ; 0x020C3694
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C36A8
FUN_020C36A8: ; 0x020C36A8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020C34B8
_020C36B4: ; 0x020C36B4
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C36C8
FUN_020C36C8: ; 0x020C36C8
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r7, r2
	mov r2, r3
	ldr r6, [sp, #0x20]
	mov r4, r0
	mov r8, r1
	bl FUN_020C0AF4
	movs r5, r0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
_020C36F8: ; 0x020C36F8
	mov r0, r8
	mov r1, r5
	bl FUN_020C09B0
	add r12, sp, #0x4
	mov r2, r0
	mov r0, r7
	mov r1, #0x6
	mov r3, #0x0
	str r12, [sp, #0x0]
	bl FUN_020C3270
_020C3720: ; 0x020C3720
	cmp r0, #0x0
	beq _020C373C
	mov r0, r5
	bl thunk_FUN_020c077c
	add sp, sp, #0x8
	mov r0, #0x0
	ldmia sp!, {r4-r8,pc}
_020C373C:
	ldr r12, [sp, #0x24]
	ldr r2, [r6, #0x0]
	ldr r1, [r12, #0x18]
	ldr r3, [sp, #0x4]
	mov r0, r5
	add r1, r12, r1
	bl FUN_020C0A90
	ldrb r1, [r6, #0x6]
	mov r0, r4
	bl FUN_020C0F30
	ldrb r1, [r6, #0x7]
	mov r0, r4
	bl FUN_020C0ECC
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x2c]
	mov r0, r4
	bl FUN_020C0E38
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020C378C
FUN_020C378C: ; 0x020C378C
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	mov r8, r2
	mov r2, r3
	ldr r5, [sp, #0x28]
	mov r6, r0
	mov r7, r1
	bl FUN_020C0AF4
	movs r4, r0
	addeq sp, sp, #0x10
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
_020C37BC: ; 0x020C37BC
	mov r0, r7
	mov r1, r4
	bl FUN_020C09B0
	mov r7, r0
	add r12, sp, #0x8
	mov r0, r8
	mov r2, r7
	mov r1, #0x6
	mov r3, #0x0
	str r12, [sp, #0x0]
	bl FUN_020C3270
_020C37E8: ; 0x020C37E8
	cmp r0, #0x0
	beq _020C3804
	mov r0, r4
	bl thunk_FUN_020c077c
	add sp, sp, #0x10
	mov r0, #0x0
	ldmia sp!, {r4-r8,pc}
_020C3804:
	ldr r0, [sp, #0x2c]
	add r12, sp, #0x4
	mov r2, r7
	mov r1, #0x1
	mov r3, #0x0
	str r12, [sp, #0x0]
	bl FUN_020C341C
_020C3820: ; 0x020C3820
	cmp r0, #0x0
	beq _020C383C
	mov r0, r4
	bl thunk_FUN_020c077c
	add sp, sp, #0x10
	mov r0, #0x0
	ldmia sp!, {r4-r8,pc}
_020C383C:
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x8]
	ldr r1, [r2, #0x18]
	mov r0, r4
	add r1, r2, r1
	mov r2, #0x0
	bl FUN_020C0A90
	ldrb r1, [r5, #0x6]
	mov r0, r6
	bl FUN_020C0F30
	ldrb r1, [r5, #0x7]
	mov r0, r6
	bl FUN_020C0ECC
	ldr r1, [sp, #0x2c]
	mov r0, r6
	bl FUN_020C0E60
	mov r0, #0x1
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020C3888
FUN_020C3888: ; 0x020C3888
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov r6, r1
	mov r7, r0
	mov r0, r6
	mov r5, r2
	bl FUN_020C2334
_020C38A4: ; 0x020C38A4
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
_020C38B4: ; 0x020C38B4
	ldr r0, [r0, #0x0]
	bl FUN_020C20DC
	movs r4, r0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
_020C38CC: ; 0x020C38CC
	mov r1, r5
	bl FUN_020C3D9C
_020C38D4: ; 0x020C38D4
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
_020C38E4: ; 0x020C38E4
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	str r6, [sp, #0x8]
	str r5, [sp, #0xc]
	ldrb r1, [r0, #0x9]
	ldrh r2, [r0, #0x4]
	ldrb r3, [r0, #0x8]
	mov r0, r7
	bl FUN_020C36C8
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020C3910
FUN_020C3910: ; 0x020C3910
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r7, r0
	ldr r0, [sp, #0x20]
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl FUN_020C2398
_020C3930: ; 0x020C3930
	cmp r0, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
_020C3940: ; 0x020C3940
	cmp r4, #0x0
	ldrltb r4, [r0, #0x8]
	cmp r5, #0x0
	ldrlth r5, [r0, #0x4]
	cmp r6, #0x0
	ldrltb r6, [r0, #0x9]
	ldr r12, [sp, #0x20]
	mov r2, r5
	str r0, [sp, #0x0]
	mov r0, r7
	mov r1, r6
	mov r3, r4
	str r12, [sp, #0x4]
	bl FUN_020C378C
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,pc}

	arm_func_start FUN_020C3980
FUN_020C3980: ; 0x020C3980
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r4, r1
	mov r5, r0
	mov r0, r4
	bl FUN_020C2398
_020C3998: ; 0x020C3998
	cmp r0, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
_020C39A8: ; 0x020C39A8
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	ldrb r1, [r0, #0x9]
	ldrh r2, [r0, #0x4]
	ldrb r3, [r0, #0x8]
	mov r0, r5
	bl FUN_020C378C
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020C39CC
FUN_020C39CC: ; 0x020C39CC
	stmdb sp!, {r4-r8,lr}
	mov r6, r0
	bl FUN_020C241C
	mov r5, #0x0
	mov r7, r5
_020C39E0:
	mov r0, r5
	bl FUN_020C2208
	movs r4, r0
	beq _020C3A58
	ldrb r1, [r4, #0x0]
	mov r0, r5
	bl FUN_020C1160
	ldrh r1, [r4, #0x2]
	mov r0, r5
	bl FUN_020C1148
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _020C3A58
	cmp r6, #0x0
	beq _020C3A58
	ldrb r0, [r4, #0x0]
	mov r8, r7
	cmp r0, #0x0
	ble _020C3A58
_020C3A2C:
	ldr r2, [r4, #0x4]
	mov r0, r5
	mov r1, r6
	bl FUN_020C10B4
_020C3A3C: ; 0x020C3A3C
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
_020C3A48: ; 0x020C3A48
	ldrb r0, [r4, #0x0]
	add r8, r8, #0x1
	cmp r8, r0
	blt _020C3A2C
_020C3A58:
	add r5, r5, #0x1
	cmp r5, #0x20
	blt _020C39E0
	mov r0, #0x1
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020C3A6C
FUN_020C3A6C: ; 0x020C3A6C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	mov r4, r0
	ldr r0, _020C3A9C ; =0x021D2904
	mov r1, r5
	bl FUN_020ADBE8
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C3A9C: .word 0x021D2904

	arm_func_start FUN_020C3AA0
FUN_020C3AA0: ; 0x020C3AA0
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	bl OS_DisableInterrupts
	mov r6, r0
	mov r0, r8
	mov r1, #0x0
	bl FUN_020ADA98
	movs r5, r0
	beq _020C3B04
_020C3AC8:
	mov r0, r8
	mov r1, r5
	bl FUN_020ADA98
	ldr r1, [r5, #0x8]
	mov r4, r0
	cmp r1, r7
	bne _020C3AF8
	mov r0, r8
	mov r1, r5
	bl FUN_020ADAB0
	mov r0, r5
	bl FUN_020C3A6C
_020C3AF8:
	mov r5, r4
	cmp r4, #0x0
	bne _020C3AC8
_020C3B04:
	mov r0, r6
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,pc}

	arm_func_start FUN_020C3B10
FUN_020C3B10: ; 0x020C3B10
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, [r0, #0x120]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	sub r1, r1, #0x1
	str r1, [r0, #0x120]
	ldr r1, [r0, #0x120]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {pc}
	bl FUN_020C1674
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020C3B4C
FUN_020C3B4C: ; 0x020C3B4C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r1, [r4, #0x110]
	mov r1, r1, lsl #0x1f
	movs r1, r1, asr #0x1f
	ldmeqia sp!, {r4,pc}
_020C3B64: ; 0x020C3B64
	bl FUN_020C3B10
	ldr r1, [r4, #0x164]
	mov r0, r4
	blx r1
	ldr r0, _020C3BA8 ; =0x021D2DF0
	mov r1, r4
	bl FUN_020C3AA0
	ldr r0, _020C3BAC ; =0x021D2900
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020C3B9C
	mov r1, r4
	add r0, r0, #0x4e0
	bl FUN_020C3AA0
_020C3B9C:
	mov r0, r4
	bl FUN_020C3C4C
	ldmia sp!, {r4,pc}
	.balign 4
_020C3BA8: .word 0x021D2DF0
_020C3BAC: .word 0x021D2900

	arm_func_start FUN_020C3BB0
FUN_020C3BB0: ; 0x020C3BB0
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, _020C3C40 ; =0x021D2DD8
	bl OS_LockMutex
	ldr r0, _020C3C44 ; =0x021D2900
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _020C3BDC
	ldr r0, _020C3C48 ; =0x000004C8
	add r0, r1, r0
	bl OS_LockMutex
_020C3BDC:
	ldr r0, [r4, #0x110]
	mov r0, r0, lsl #0x1e
	movs r0, r0, asr #0x1f
	beq _020C3BF4
	mov r0, r4
	bl FUN_020C1430
_020C3BF4:
	ldr r0, [r4, #0x110]
	mov r0, r0, lsl #0x1f
	movs r0, r0, asr #0x1f
	beq _020C3C10
	ldr r1, [r4, #0x16c]
	mov r0, r4
	blx r1
_020C3C10:
	mov r0, r4
	bl FUN_020C3B4C
	ldr r0, _020C3C40 ; =0x021D2DD8
	bl OS_UnlockMutex
	ldr r0, _020C3C44 ; =0x021D2900
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	ldmeqia sp!, {r4,pc}
_020C3C30: ; 0x020C3C30
	ldr r0, _020C3C48 ; =0x000004C8
	add r0, r1, r0
	bl OS_UnlockMutex
	ldmia sp!, {r4,pc}
	.balign 4
_020C3C40: .word 0x021D2DD8
_020C3C44: .word 0x021D2900
_020C3C48: .word 0x000004C8

	arm_func_start FUN_020C3C4C
FUN_020C3C4C: ; 0x020C3C4C
	ldr r2, [r0, #0x14c]
	cmp r2, #0x0
	movne r1, #0x0
	strne r1, [r2, #0x0]
	strne r1, [r0, #0x14c]
	ldr r1, [r0, #0x110]
	bic r1, r1, #0x1
	str r1, [r0, #0x110]
	ldr r1, [r0, #0x110]
	bic r1, r1, #0x4
	str r1, [r0, #0x110]
	ldr r1, [r0, #0x110]
	bic r1, r1, #0x2
	str r1, [r0, #0x110]
	bx lr

	arm_func_start FUN_020C3C88
FUN_020C3C88:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r5, _020C3D94 ; =0x021D2DFC
	mov r7, #0x0
	ldr r4, _020C3D98 ; =0x02103BAC
_020C3C9C:
	ldr r1, [r5, #0x110]
	mov r0, r1, lsl #0x1f
	movs r0, r0, asr #0x1f
	beq _020C3D7C
	ldr r0, [r5, #0x114]
	cmp r0, #0x0
	bne _020C3CC4
	mov r0, r5
	bl FUN_020C3BB0
	b _020C3D7C
_020C3CC4:
	mov r0, r1, lsl #0x1d
	movs r0, r0, asr #0x1f
	beq _020C3CFC
	ldr r0, [r5, #0x118]
	cmp r0, #0x0
	beq _020C3CFC
	mov r0, r5
	bl FUN_020C1458
	ldr r0, [r5, #0x110]
	orr r0, r0, #0x2
	str r0, [r5, #0x110]
	ldr r0, [r5, #0x110]
	bic r0, r0, #0x4
	str r0, [r5, #0x110]
_020C3CFC:
	ldr r0, [r5, #0x110]
	mov r0, r0, lsl #0x1e
	movs r0, r0, asr #0x1f
	beq _020C3D7C
	add r0, r5, #0xe8
	bl FUN_020C3DF4
	ldr r1, [r5, #0x154]
	add r0, r5, #0xe8
	mov r1, r1, lsl #0x1
	ldrsh r6, [r4, r1]
	bl FUN_020C3E0C
	mov r0, r0, asr #0x8
	mov r0, r0, lsl #0x1
	ldrsh r1, [r4, r0]
	ldr r0, [r5, #0x158]
	add r6, r1, r6
	cmp r6, r0
	beq _020C3D54
	mov r0, r5
	mov r1, r6
	bl FUN_020C13C4
	str r6, [r5, #0x158]
_020C3D54:
	ldr r0, [r5, #0x110]
	mov r0, r0, lsl #0x1c
	movs r0, r0, asr #0x1f
	beq _020C3D7C
	add r0, r5, #0xe8
	bl FUN_020C3DDC
_020C3D6C: ; 0x020C3D6C
	cmp r0, #0x0
	beq _020C3D7C
	mov r0, r5
	bl FUN_020C3BB0
_020C3D7C:
	add r7, r7, #0x1
	cmp r7, #0x4
	add r5, r5, #0x170
	blt _020C3C9C
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C3D94: .word 0x021D2DFC
_020C3D98: .word 0x02103BAC

	arm_func_start FUN_020C3D9C
FUN_020C3D9C:
	cmp r1, #0x0
	movlt r0, #0x0
	bxlt lr
	ldr r2, [r0, #0x1c]
	cmp r1, r2
	movcs r0, #0x0
	bxcs lr
	mov r2, #0xc
	mul r2, r1, r2
	add r3, r0, #0x20
	ldr r1, [r3, r2]
	mvn r0, #0x0
	cmp r1, r0
	add r0, r3, r2
	moveq r0, #0x0
	bx lr

	arm_func_start FUN_020C3DDC
FUN_020C3DDC:
	ldr r1, [r0, #0x8]
	ldr r0, [r0, #0xc]
	cmp r1, r0
	movge r0, #0x1
	movlt r0, #0x0
	bx lr

	arm_func_start FUN_020C3DF4
FUN_020C3DF4: ; 0x020C3DF4
	ldr r2, [r0, #0x8]
	ldr r1, [r0, #0xc]
	cmp r2, r1
	addlt r1, r2, #0x1
	strlt r1, [r0, #0x8]
	bx lr

	arm_func_start FUN_020C3E0C
FUN_020C3E0C:
	stmdb sp!, {r4,lr}
	ldr r1, [r0, #0xc]
	ldr r2, [r0, #0x8]
	cmp r2, r1
	ldrge r0, [r0, #0x4]
	ldmgeia sp!, {r4,pc}
_020C3E24: ; 0x020C3E24
	ldr r4, [r0, #0x0]
	ldr r0, [r0, #0x4]
	sub r0, r0, r4
	mul r0, r2, r0
	bl _s32_div_f
_020C3E38: ; 0x020C3E38
	add r0, r4, r0
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020C3E40
FUN_020C3E40:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl FUN_020C3E0C
_020C3E54: ; 0x020C3E54
	str r0, [r6, #0x0]
	str r5, [r6, #0x4]
	str r4, [r6, #0xc]
	mov r0, #0x0
	str r0, [r6, #0x8]
	ldmia sp!, {r4-r6,pc}

	arm_func_start FUN_020C3E6C
FUN_020C3E6C: ; 0x020C3E6C
	mov r2, #0x0
	str r2, [r0, #0x4]
	ldr r1, [r0, #0x4]
	str r1, [r0, #0x0]
	str r2, [r0, #0xc]
	ldr r1, [r0, #0xc]
	str r1, [r0, #0x8]
	bx lr

	arm_func_start FUN_020C3E8C
FUN_020C3E8C: ; 0x020C3E8C
	mov r1, #0x0
	mov r2, #0x1000
	mov r3, #0x0
	stmia r0!, {r2-r3}
	stmia r0!, {r1-r2}
	bx lr

	thumb_func_start FUN_020C3EA4
FUN_020C3EA4: ; 0x020C3EA4
	str r2, [r0, #0x0]
	str r1, [r0, #0x4]
	neg r1, r1
	str r1, [r0, #0x8]
	str r2, [r0, #0xc]
	bx lr

	arm_func_start FUN_020C3EB0
FUN_020C3EB0: ; 0x020C3EB0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r12, [r0, #0x0]
	smull lr, r12, r2, r12
	mov lr, lr, lsr #0xc
	orr lr, lr, r12, lsl #0x14
	str lr, [r1, #0x0]
	ldr r12, [r0, #0x4]
	smull lr, r12, r2, r12
	mov r2, lr, lsr #0xc
	orr r2, r2, r12, lsl #0x14
	str r2, [r1, #0x4]
	ldr r2, [r0, #0x8]
	smull r12, r2, r3, r2
	mov r12, r12, lsr #0xc
	orr r12, r12, r2, lsl #0x14
	str r12, [r1, #0x8]
	ldr r0, [r0, #0xc]
	smull r2, r0, r3, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [r1, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start MTX_Identity33_
MTX_Identity33_: ; 0x020C3F14
	mov r2, #0x1000
	str r2, [r0, #0x20]
	mov r3, #0x0
	stmia r0!, {r2-r3}
	mov r1, #0x0
	stmia r0!, {r1,r3}
	stmia r0!, {r2-r3}
	stmia r0!, {r1,r3}
	bx lr

	thumb_func_start MTX_RotX33_
MTX_RotX33_: ; 0x020C3F38
	mov r3, #0x1
	lsl r3, r3, #0xc
	str r3, [r0, #0x0]
	mov r3, #0x0
	str r3, [r0, #0x4]
	str r3, [r0, #0x8]
	str r3, [r0, #0xc]
	str r2, [r0, #0x10]
	str r1, [r0, #0x14]
	str r3, [r0, #0x18]
	neg r1, r1
	str r1, [r0, #0x1c]
	str r2, [r0, #0x20]
	bx lr

	thumb_func_start MTX_RotY33_
MTX_RotY33_: ; 0x020C3F54
	str r2, [r0, #0x0]
	str r2, [r0, #0x20]
	mov r3, #0x0
	str r3, [r0, #0x4]
	str r3, [r0, #0xc]
	str r3, [r0, #0x14]
	str r3, [r0, #0x1c]
	neg r2, r1
	mov r3, #0x1
	lsl r3, r3, #0xc
	str r1, [r0, #0x18]
	str r2, [r0, #0x8]
	str r3, [r0, #0x10]
	bx lr

	thumb_func_start MTX_RotZ33_
MTX_RotZ33_: ; 0x020C3F70
	stmia r0!, {r2}
	mov r3, #0x0
	stmia r0!, {r1,r3}
	neg r1, r1
	stmia r0!, {r1-r2}
	mov r1, #0x1
	lsl r1, r1, #0xc
	str r3, [r0, #0x0]
	str r3, [r0, #0x4]
	str r3, [r0, #0x8]
	str r1, [r0, #0xc]
	bx lr

	arm_func_start MTX_MultVec33
MTX_MultVec33: ; 0x020C3F88
	stmdb sp!, {r4-r6,lr}
	ldr r12, [r0, #0x4]
	ldr r4, [r1, #0xc]
	ldr r3, [r0, #0x0]
	smull r6, r5, r12, r4
	ldr r4, [r1, #0x0]
	ldr r0, [r0, #0x8]
	smlal r6, r5, r3, r4
	ldr r4, [r1, #0x18]
	smlal r6, r5, r0, r4
	mov r4, r6, lsr #0xc
	orr r4, r4, r5, lsl #0x14
	str r4, [r2, #0x0]
	ldr r4, [r1, #0x10]
	ldr r5, [r1, #0x4]
	smull r6, lr, r12, r4
	smlal r6, lr, r3, r5
	ldr r4, [r1, #0x1c]
	smlal r6, lr, r0, r4
	mov r4, r6, lsr #0xc
	orr r4, r4, lr, lsl #0x14
	str r4, [r2, #0x4]
	ldr lr, [r1, #0x14]
	ldr r4, [r1, #0x8]
	smull r5, lr, r12, lr
	smlal r5, lr, r3, r4
	ldr r1, [r1, #0x20]
	smlal r5, lr, r0, r1
	mov r0, r5, lsr #0xc
	orr r0, r0, lr, lsl #0x14
	str r0, [r2, #0x8]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start MTX_Concat33
MTX_Concat33: ; 0x020C400C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x24
	ldr r5, [r0, #0x4]
	ldr r3, [r1, #0xc]
	mov r12, r2
	smull r8, r7, r5, r3
	ldr r6, [r0, #0x0]
	ldr r3, [r1, #0x0]
	cmp r12, r1
	smlal r8, r7, r6, r3
	ldr r4, [r0, #0x8]
	ldr r3, [r1, #0x18]
	addeq r2, sp, #0x0
	smlal r8, r7, r4, r3
	mov r3, r8, lsr #0xc
	orr r3, r3, r7, lsl #0x14
	str r3, [r2, #0x0]
	ldr r3, [r1, #0x10]
	ldr r7, [r1, #0x4]
	smull r9, r8, r5, r3
	smlal r9, r8, r6, r7
	ldr r3, [r1, #0x1c]
	add lr, sp, #0x0
	smlal r9, r8, r4, r3
	mov r3, r9, lsr #0xc
	orr r3, r3, r8, lsl #0x14
	str r3, [r2, #0x4]
	ldr r3, [r1, #0x14]
	ldr r7, [r1, #0x8]
	smull r9, r8, r5, r3
	smlal r9, r8, r6, r7
	ldr r6, [r1, #0x20]
	cmp r2, lr
	smlal r9, r8, r4, r6
	mov r4, r9, lsr #0xc
	orr r4, r4, r8, lsl #0x14
	str r4, [r2, #0x8]
	ldr r4, [r0, #0x10]
	ldr r5, [r0, #0xc]
	smull r9, r8, r4, r3
	smlal r9, r8, r5, r7
	ldr r3, [r0, #0x14]
	addne sp, sp, #0x24
	smlal r9, r8, r3, r6
	mov r6, r9, lsr #0xc
	orr r6, r6, r8, lsl #0x14
	str r6, [r2, #0x14]
	ldr r6, [r1, #0x10]
	ldr r7, [r1, #0x4]
	smull r9, r8, r4, r6
	smlal r9, r8, r5, r7
	ldr r6, [r1, #0x1c]
	smlal r9, r8, r3, r6
	mov r6, r9, lsr #0xc
	orr r6, r6, r8, lsl #0x14
	str r6, [r2, #0x10]
	ldr r7, [r1, #0xc]
	ldr r6, [r1, #0x0]
	smull r9, r8, r4, r7
	smlal r9, r8, r5, r6
	ldr r5, [r1, #0x18]
	smlal r9, r8, r3, r5
	mov r3, r9, lsr #0xc
	orr r3, r3, r8, lsl #0x14
	str r3, [r2, #0xc]
	ldr r4, [r0, #0x1c]
	ldr r3, [r0, #0x18]
	smull r8, r7, r4, r7
	smlal r8, r7, r3, r6
	ldr r0, [r0, #0x20]
	smlal r8, r7, r0, r5
	mov r5, r8, lsr #0xc
	orr r5, r5, r7, lsl #0x14
	str r5, [r2, #0x18]
	ldr r5, [r1, #0x10]
	ldr r6, [r1, #0x4]
	smull r8, r5, r4, r5
	smlal r8, r5, r3, r6
	ldr r7, [r1, #0x1c]
	smlal r8, r5, r0, r7
	mov r6, r8, lsr #0xc
	orr r6, r6, r5, lsl #0x14
	str r6, [r2, #0x1c]
	ldr r6, [r1, #0x20]
	ldr r5, [r1, #0x8]
	ldr r1, [r1, #0x14]
	smull r7, r1, r4, r1
	smlal r7, r1, r3, r5
	smlal r7, r1, r0, r6
	mov r0, r7, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	str r0, [r2, #0x20]
	ldmneia sp!, {r4-r9,lr}
	bxne lr
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldr r0, [lr, #0x0]
	str r0, [r12, #0x0]
	add sp, sp, #0x24
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start MTX_ScaleApply33
MTX_ScaleApply33: ; 0x020C41A8
	stmdb sp!, {r4,lr}
	ldr r4, [r0, #0x0]
	ldr r12, [sp, #0x8]
	smull lr, r4, r2, r4
	mov lr, lr, lsr #0xc
	orr lr, lr, r4, lsl #0x14
	str lr, [r1, #0x0]
	ldr r4, [r0, #0x4]
	smull lr, r4, r2, r4
	mov lr, lr, lsr #0xc
	orr lr, lr, r4, lsl #0x14
	str lr, [r1, #0x4]
	ldr lr, [r0, #0x8]
	smull r4, lr, r2, lr
	mov r2, r4, lsr #0xc
	orr r2, r2, lr, lsl #0x14
	str r2, [r1, #0x8]
	ldr r2, [r0, #0xc]
	smull lr, r2, r3, r2
	mov lr, lr, lsr #0xc
	orr lr, lr, r2, lsl #0x14
	str lr, [r1, #0xc]
	ldr r2, [r0, #0x10]
	smull lr, r2, r3, r2
	mov lr, lr, lsr #0xc
	orr lr, lr, r2, lsl #0x14
	str lr, [r1, #0x10]
	ldr r2, [r0, #0x14]
	smull lr, r2, r3, r2
	mov r3, lr, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	str r3, [r1, #0x14]
	ldr r2, [r0, #0x18]
	smull r3, r2, r12, r2
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	str r3, [r1, #0x18]
	ldr r2, [r0, #0x1c]
	smull r3, r2, r12, r2
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	str r3, [r1, #0x1c]
	ldr r0, [r0, #0x20]
	smull r2, r0, r12, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [r1, #0x20]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start MTX_Identity43_
MTX_Identity43_: ; 0x020C426C
	mov r2, #0x1000
	mov r3, #0x0
	stmia r0!, {r2-r3}
	mov r1, #0x0
	stmia r0!, {r1,r3}
	stmia r0!, {r2-r3}
	stmia r0!, {r1,r3}
	stmia r0!, {r2-r3}
	stmia r0!, {r1,r3}
	bx lr

	arm_func_start MTX_Copy43To44_
MTX_Copy43To44_: ; 0x020C4294
	stmdb sp!, {r4}
	mov r12, #0x0
	ldmia r0!, {r2-r4}
	stmia r1!, {r2-r4,r12}
	ldmia r0!, {r2-r4}
	stmia r1!, {r2-r4,r12}
	ldmia r0!, {r2-r4}
	stmia r1!, {r2-r4,r12}
	mov r12, #0x1000
	ldmia r0!, {r2-r4}
	stmia r1!, {r2-r4,r12}
	ldmia sp!, {r4}
	bx lr

	thumb_func_start MTX_Scale43_
MTX_Scale43_: ; 0x020C42C8
	stmia r0!, {r1}
	mov r1, #0x0
	str r3, [r0, #0x1c]
	mov r3, #0x0
	stmia r0!, {r1,r3}
	stmia r0!, {r1-r3}
	mov r2, #0x0
	stmia r0!, {r1,r3}
	add r0, #0x4
	stmia r0!, {r1-r3}
	bx lr
	.balign 4

	thumb_func_start MTX_RotX43_
MTX_RotX43_: ; 0x020C42E0
	str r1, [r0, #0x14]
	neg r1, r1
	str r1, [r0, #0x1c]
	mov r1, #0x1
	lsl r1, r1, #0xc
	stmia r0!, {r1}
	mov r3, #0x0
	mov r1, #0x0
	stmia r0!, {r1,r3}
	stmia r0!, {r1-r2}
	str r1, [r0, #0x4]
	add r0, #0xc
	stmia r0!, {r2-r3}
	stmia r0!, {r1,r3}
	bx lr
	.balign 4

	thumb_func_start MTX_RotY43_
MTX_RotY43_: ; 0x020C4300
	str r1, [r0, #0x18]
	mov r3, #0x0
	stmia r0!, {r2-r3}
	neg r1, r1
	stmia r0!, {r1,r3}
	mov r1, #0x1
	lsl r1, r1, #0xc
	stmia r0!, {r1,r3}
	add r0, #0x4
	mov r1, #0x0
	stmia r0!, {r1-r3}
	stmia r0!, {r1,r3}
	bx lr
	.balign 4

	arm_func_start MTX_MultVec43
MTX_MultVec43: ; 0x020C431C
	stmdb sp!, {r4-r6,lr}
	ldr r12, [r0, #0x4]
	ldr r4, [r1, #0xc]
	ldr r3, [r0, #0x0]
	smull r6, r5, r12, r4
	ldr r4, [r1, #0x0]
	ldr r0, [r0, #0x8]
	smlal r6, r5, r3, r4
	ldr r4, [r1, #0x18]
	smlal r6, r5, r0, r4
	mov r4, r6, lsr #0xc
	orr r4, r4, r5, lsl #0x14
	str r4, [r2, #0x0]
	ldr r5, [r2, #0x0]
	ldr r4, [r1, #0x24]
	add r4, r5, r4
	str r4, [r2, #0x0]
	ldr r4, [r1, #0x10]
	ldr r5, [r1, #0x4]
	smull r6, lr, r12, r4
	smlal r6, lr, r3, r5
	ldr r4, [r1, #0x1c]
	smlal r6, lr, r0, r4
	mov r4, r6, lsr #0xc
	orr r4, r4, lr, lsl #0x14
	str r4, [r2, #0x4]
	ldr r5, [r2, #0x4]
	ldr r4, [r1, #0x28]
	add r4, r5, r4
	str r4, [r2, #0x4]
	ldr lr, [r1, #0x14]
	ldr r4, [r1, #0x8]
	smull r5, lr, r12, lr
	smlal r5, lr, r3, r4
	ldr r3, [r1, #0x20]
	smlal r5, lr, r0, r3
	mov r0, r5, lsr #0xc
	orr r0, r0, lr, lsl #0x14
	str r0, [r2, #0x8]
	ldr r3, [r2, #0x8]
	ldr r0, [r1, #0x2c]
	add r0, r3, r0
	str r0, [r2, #0x8]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start MTX_Concat43
MTX_Concat43: ; 0x020C43D0
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x30
	ldr r5, [r0, #0x4]
	ldr r3, [r1, #0xc]
	mov r12, r2
	smull r8, r7, r5, r3
	ldr r6, [r0, #0x0]
	ldr r3, [r1, #0x0]
	cmp r12, r1
	smlal r8, r7, r6, r3
	ldr r4, [r0, #0x8]
	ldr r3, [r1, #0x18]
	addeq r2, sp, #0x0
	smlal r8, r7, r4, r3
	mov r3, r8, lsr #0xc
	orr r3, r3, r7, lsl #0x14
	str r3, [r2, #0x0]
	ldr r3, [r1, #0x10]
	ldr r7, [r1, #0x4]
	smull r9, r8, r5, r3
	smlal r9, r8, r6, r7
	ldr r3, [r1, #0x1c]
	add lr, sp, #0x0
	smlal r9, r8, r4, r3
	mov r3, r9, lsr #0xc
	orr r3, r3, r8, lsl #0x14
	str r3, [r2, #0x4]
	ldr r3, [r1, #0x14]
	ldr r7, [r1, #0x8]
	smull r9, r8, r5, r3
	smlal r9, r8, r6, r7
	ldr r6, [r1, #0x20]
	smlal r9, r8, r4, r6
	mov r4, r9, lsr #0xc
	orr r4, r4, r8, lsl #0x14
	str r4, [r2, #0x8]
	ldr r4, [r0, #0x10]
	ldr r5, [r0, #0xc]
	smull r9, r8, r4, r3
	smlal r9, r8, r5, r7
	ldr r3, [r0, #0x14]
	smlal r9, r8, r3, r6
	mov r6, r9, lsr #0xc
	orr r6, r6, r8, lsl #0x14
	str r6, [r2, #0x14]
	ldr r6, [r1, #0x10]
	ldr r7, [r1, #0x4]
	smull r9, r8, r4, r6
	smlal r9, r8, r5, r7
	ldr r6, [r1, #0x1c]
	smlal r9, r8, r3, r6
	mov r6, r9, lsr #0xc
	orr r6, r6, r8, lsl #0x14
	str r6, [r2, #0x10]
	ldr r7, [r1, #0xc]
	ldr r8, [r1, #0x0]
	smull r10, r9, r4, r7
	smlal r10, r9, r5, r8
	ldr r6, [r1, #0x18]
	smlal r10, r9, r3, r6
	mov r3, r10, lsr #0xc
	orr r3, r3, r9, lsl #0x14
	str r3, [r2, #0xc]
	ldr r4, [r0, #0x1c]
	ldr r5, [r0, #0x18]
	smull r9, r7, r4, r7
	smlal r9, r7, r5, r8
	ldr r3, [r0, #0x20]
	smlal r9, r7, r3, r6
	mov r6, r9, lsr #0xc
	orr r6, r6, r7, lsl #0x14
	str r6, [r2, #0x18]
	ldr r6, [r1, #0x10]
	ldr r7, [r1, #0x4]
	smull r9, r6, r4, r6
	smlal r9, r6, r5, r7
	ldr r8, [r1, #0x1c]
	smlal r9, r6, r3, r8
	mov r7, r9, lsr #0xc
	orr r7, r7, r6, lsl #0x14
	str r7, [r2, #0x1c]
	ldr r7, [r1, #0x14]
	ldr r6, [r1, #0x8]
	smull r9, r8, r4, r7
	smlal r9, r8, r5, r6
	ldr r5, [r1, #0x20]
	smlal r9, r8, r3, r5
	mov r3, r9, lsr #0xc
	orr r3, r3, r8, lsl #0x14
	str r3, [r2, #0x20]
	ldr r4, [r0, #0x28]
	ldr r3, [r0, #0x24]
	smull r8, r7, r4, r7
	smlal r8, r7, r3, r6
	ldr r0, [r0, #0x2c]
	ldr r6, [r1, #0x2c]
	smlal r8, r7, r0, r5
	mov r5, r8, lsr #0xc
	orr r5, r5, r7, lsl #0x14
	adds r5, r6, r5
	str r5, [r2, #0x2c]
	ldr r5, [r1, #0x10]
	ldr r6, [r1, #0x4]
	smull r8, r5, r4, r5
	smlal r8, r5, r3, r6
	ldr r7, [r1, #0x1c]
	ldr r9, [r1, #0x28]
	smlal r8, r5, r0, r7
	mov r6, r8, lsr #0xc
	orr r6, r6, r5, lsl #0x14
	adds r5, r9, r6
	str r5, [r2, #0x28]
	ldr r8, [r1, #0x24]
	ldr r6, [r1, #0x18]
	ldr r5, [r1, #0x0]
	ldr r1, [r1, #0xc]
	smull r7, r1, r4, r1
	smlal r7, r1, r3, r5
	smlal r7, r1, r0, r6
	mov r0, r7, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	adds r0, r8, r0
	cmp r2, lr
	str r0, [r2, #0x24]
	addne sp, sp, #0x30
	ldmneia sp!, {r4-r10,lr}
	bxne lr
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr, {r0-r3}
	stmia r12, {r0-r3}
	add sp, sp, #0x30
	ldmia sp!, {r4-r10,lr}
	bx lr

	arm_func_start MTX_Inverse43
MTX_Inverse43: ; 0x020C45F0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x5c
	mov r10, r0
	ldr r11, [r10, #0x14]
	cmp r10, r1
	addeq r9, sp, #0x2c
	ldr r3, [r10, #0x18]
	ldr r2, [r10, #0xc]
	ldr r8, [r10, #0x20]
	str r1, [sp, #0x0]
	movne r9, r1
	smull r7, r5, r2, r8
	smull r6, r1, r11, r3
	ldr r4, [r10, #0x1c]
	subs r12, r7, r6
	ldr r0, [r10, #0x10]
	smull r6, lr, r11, r4
	sbc r11, r5, r1
	smull r5, r4, r2, r4
	mov r1, #0x800
	smull r8, r7, r0, r8
	smull r3, r2, r0, r3
	adds r12, r12, r1
	adc r0, r11, #0x0
	subs r8, r8, r6
	sbc r6, r7, lr
	adds r7, r8, r1
	adc r11, r6, #0x0
	mov r7, r7, lsr #0xc
	mov r8, r12, lsr #0xc
	orr r7, r7, r11, lsl #0x14
	orr r8, r8, r0, lsl #0x14
	subs r0, r5, r3
	sbc r12, r4, r2
	ldr r6, [r10, #0x4]
	ldr r11, [r10, #0x0]
	smull r3, r2, r6, r8
	adds r0, r0, r1
	smull r5, r4, r11, r7
	adc r11, r12, #0x0
	mov r6, r0, lsr #0xc
	subs r3, r5, r3
	ldr r0, [r10, #0x8]
	orr r6, r6, r11, lsl #0x14
	sbc r2, r4, r2
	smlal r3, r2, r0, r6
	adds r0, r3, r1
	mov r1, r8, asr #0x1f
	str r1, [sp, #0x4]
	mov r1, r7, asr #0x1f
	str r1, [sp, #0x8]
	mov r1, r6, asr #0x1f
	adc r2, r2, #0x0
	mov r0, r0, lsr #0xc
	orrs r0, r0, r2, lsl #0x14
	str r1, [sp, #0xc]
	addeq sp, sp, #0x5c
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	bl FX_InvAsync
	ldr r1, [r10, #0x8]
	ldr r2, [r10, #0x1c]
	ldr r11, [r10, #0x10]
	smull r0, r4, r2, r1
	smull r3, r2, r11, r1
	ldr r5, [r10, #0x18]
	str r2, [sp, #0x18]
	str r3, [sp, #0x14]
	smull r3, r2, r5, r1
	str r2, [sp, #0x20]
	ldr r2, [r10, #0x20]
	ldr lr, [r10, #0x4]
	str r2, [sp, #0x10]
	ldr r5, [sp, #0x10]
	str r3, [sp, #0x1c]
	smull r12, r5, lr, r5
	subs r0, r12, r0
	ldr r2, [r10, #0xc]
	sbc r4, r5, r4
	smull r1, r5, r2, r1
	str r5, [sp, #0x28]
	mov r5, r0, lsr #0xc
	ldr r11, [r10, #0x14]
	orr r5, r5, r4, lsl #0x14
	smull r4, r2, lr, r11
	ldr r0, [sp, #0x14]
	ldr r3, [r10, #0x0]
	subs r4, r4, r0
	ldr r0, [sp, #0x18]
	mov r4, r4, lsr #0xc
	sbc r0, r2, r0
	orr r4, r4, r0, lsl #0x14
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x1c]
	smull r12, r0, r3, r0
	subs r2, r12, r2
	ldr r12, [sp, #0x20]
	sbc r0, r0, r12
	smull r12, r11, r3, r11
	ldr r3, [sp, #0x28]
	subs r1, r12, r1
	sbc r3, r11, r3
	mov r11, r2, lsr #0xc
	orr r11, r11, r0, lsl #0x14
	mov r0, r1, lsr #0xc
	str r0, [sp, #0x24]
	orr r0, r0, r3, lsl #0x14
	str r0, [sp, #0x24]
	bl FX_GetDivResult
	smull r2, r1, r0, r5
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	rsb lr, r2, #0x0
	smull r2, r1, r0, r4
	mov r4, r2, lsr #0xc
	orr r4, r4, r1, lsl #0x14
	smull r2, r1, r0, r11
	mov r3, r2, lsr #0xc
	orr r3, r3, r1, lsl #0x14
	ldr r1, [sp, #0x24]
	umull r11, r5, r0, r7
	smull r2, r1, r0, r1
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	ldr r1, [sp, #0x8]
	mov r12, r0, asr #0x1f
	mla r5, r0, r1, r5
	mla r5, r12, r7, r5
	mov r1, r11, lsr #0xc
	orr r1, r1, r5, lsl #0x14
	str r1, [r9, #0x0]
	str lr, [r9, #0x4]
	str r4, [r9, #0x8]
	ldr r1, [sp, #0x4]
	umull r5, r4, r0, r8
	mla r4, r0, r1, r4
	mla r4, r12, r8, r4
	mov r1, r5, lsr #0xc
	orr r1, r1, r4, lsl #0x14
	rsb r1, r1, #0x0
	str r1, [r9, #0xc]
	ldr r1, [sp, #0xc]
	rsb r2, r2, #0x0
	str r3, [r9, #0x10]
	str r2, [r9, #0x14]
	umull r3, r2, r0, r6
	mla r2, r0, r1, r2
	mla r2, r12, r6, r2
	mov r1, r3, lsr #0xc
	orr r1, r1, r2, lsl #0x14
	str r1, [r9, #0x18]
	ldr r3, [r10, #0x0]
	ldr r1, [r10, #0x1c]
	ldr r2, [r10, #0x18]
	smull r5, r4, r3, r1
	ldr r1, [r10, #0x4]
	smull r3, r1, r2, r1
	subs r2, r5, r3
	sbc r1, r4, r1
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	smull r2, r1, r0, r2
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	rsb r1, r2, #0x0
	str r1, [r9, #0x1c]
	ldr r3, [r10, #0x0]
	ldr r1, [r10, #0x10]
	ldr r2, [r10, #0xc]
	smull r5, r4, r3, r1
	ldr r1, [r10, #0x4]
	smull r3, r1, r2, r1
	subs r2, r5, r3
	sbc r1, r4, r1
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	smull r2, r1, r0, r2
	mov r0, r2, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	str r0, [r9, #0x20]
	add r0, sp, #0x2c
	ldr r2, [r9, #0xc]
	ldr r1, [r10, #0x28]
	ldr r4, [r9, #0x0]
	smull r7, r1, r2, r1
	ldr r3, [r10, #0x24]
	ldr r6, [r9, #0x18]
	smlal r7, r1, r4, r3
	ldr r5, [r10, #0x2c]
	cmp r9, r0
	smlal r7, r1, r6, r5
	mov r2, r7, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	rsb r1, r2, #0x0
	str r1, [r9, #0x24]
	ldr r2, [r9, #0x10]
	ldr r1, [r10, #0x28]
	ldr r4, [r9, #0x4]
	smull r7, r1, r2, r1
	ldr r3, [r10, #0x24]
	ldr r6, [r9, #0x1c]
	smlal r7, r1, r4, r3
	ldr r5, [r10, #0x2c]
	smlal r7, r1, r6, r5
	mov r2, r7, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	rsb r1, r2, #0x0
	str r1, [r9, #0x28]
	ldr r1, [r10, #0x28]
	ldr r2, [r9, #0x14]
	ldr r4, [r9, #0x8]
	smull r7, r1, r2, r1
	ldr r3, [r10, #0x24]
	ldr r6, [r9, #0x20]
	smlal r7, r1, r4, r3
	ldr r5, [r10, #0x2c]
	smlal r7, r1, r6, r5
	mov r2, r7, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	rsb r1, r2, #0x0
	str r1, [r9, #0x2c]
	bne _020C4974
	ldr r1, [sp, #0x0]
	bl MI_Copy48B
_020C4974:
	mov r0, #0x0
	add sp, sp, #0x5c
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start MTX_ScaleApply43
MTX_ScaleApply43: ; 0x020C4984
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r12, [sp, #0x10]
	mov r5, r0
	str r12, [sp, #0x0]
	mov r4, r1
	bl MTX_ScaleApply33
	ldr r0, [r5, #0x24]
	str r0, [r4, #0x24]
	ldr r0, [r5, #0x28]
	str r0, [r4, #0x28]
	ldr r0, [r5, #0x2c]
	str r0, [r4, #0x2c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start MTX_Identity44_
MTX_Identity44_: ; 0x020C49C4
	mov r2, #0x1000
	mov r3, #0x0
	stmia r0!, {r2-r3}
	mov r1, #0x0
	stmia r0!, {r1,r3}
	stmia r0!, {r1-r3}
	stmia r0!, {r1,r3}
	stmia r0!, {r1-r3}
	stmia r0!, {r1,r3}
	stmia r0!, {r1-r2}
	bx lr

	arm_func_start MTX_Copy44To43_
MTX_Copy44To43_:
	ldmia r0!, {r2-r3,r12}
	add r0, r0, #0x4
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	add r0, r0, #0x4
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	add r0, r0, #0x4
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	add r0, r0, #0x4
	stmia r1!, {r2-r3,r12}
	bx lr

	thumb_func_start MTX_RotX44_
MTX_RotX44_: ; 0x020C4A24
	str r2, [r0, #0x14]
	str r2, [r0, #0x28]
	str r1, [r0, #0x18]
	neg r1, r1
	str r1, [r0, #0x24]
	mov r1, #0x1
	mov r2, #0x0
	lsl r1, r1, #0xc
	mov r3, #0x0
	stmia r0!, {r1-r3}
	stmia r0!, {r2-r3}
	add r0, #0x8
	stmia r0!, {r2-r3}
	add r0, #0x8
	stmia r0!, {r2-r3}
	stmia r0!, {r2-r3}
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start MTX_RotY44_
MTX_RotY44_: ; 0x020C4A48
	str r2, [r0, #0x0]
	str r2, [r0, #0x28]
	str r1, [r0, #0x20]
	neg r1, r1
	str r1, [r0, #0x8]
	mov r3, #0x1
	mov r1, #0x0
	lsl r3, r3, #0xc
	mov r2, #0x0
	str r2, [r0, #0x4]
	add r0, #0xc
	stmia r0!, {r1-r3}
	stmia r0!, {r1-r2}
	str r2, [r0, #0x4]
	add r0, #0xc
	stmia r0!, {r1-r2}
	stmia r0!, {r1-r3}
	bx lr

	thumb_func_start MTX_RotZ44_
MTX_RotZ44_: ; 0x020C4A6C
	str r2, [r0, #0x0]
	str r2, [r0, #0x14]
	str r1, [r0, #0x4]
	neg r1, r1
	str r1, [r0, #0x10]
	mov r3, #0x1
	mov r1, #0x0
	lsl r3, r3, #0xc
	mov r2, #0x0
	add r0, #0x8
	stmia r0!, {r1-r2}
	add r0, #0x8
	stmia r0!, {r1-r2}
	stmia r0!, {r1-r3}
	stmia r0!, {r1-r2}
	stmia r0!, {r1-r3}
	bx lr
	.balign 4

	arm_func_start MTX_Concat44
MTX_Concat44: ; 0x020C4A90
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x44
	ldr r5, [r0, #0x4]
	ldr r3, [r1, #0x10]
	mov r12, r2
	smull r6, r4, r5, r3
	ldr r9, [r0, #0x0]
	ldr r3, [r1, #0x0]
	cmp r12, r1
	smlal r6, r4, r9, r3
	ldr r10, [r0, #0x8]
	ldr r3, [r1, #0x20]
	ldr r8, [r0, #0xc]
	smlal r6, r4, r10, r3
	ldr r3, [r1, #0x30]
	addeq r2, sp, #0x0
	smlal r6, r4, r8, r3
	mov r3, r6, lsr #0xc
	orr r3, r3, r4, lsl #0x14
	str r3, [r2, #0x0]
	ldr r3, [r1, #0x14]
	ldr r4, [r1, #0x4]
	smull r7, r6, r5, r3
	smlal r7, r6, r9, r4
	ldr r3, [r1, #0x24]
	ldr r4, [r1, #0x34]
	smlal r7, r6, r10, r3
	smlal r7, r6, r8, r4
	mov r3, r7, lsr #0xc
	orr r3, r3, r6, lsl #0x14
	str r3, [r2, #0x4]
	ldr r3, [r1, #0x1c]
	ldr r4, [r1, #0xc]
	smull r7, r6, r5, r3
	smlal r7, r6, r9, r4
	ldr r3, [r1, #0x2c]
	ldr r4, [r1, #0x3c]
	smlal r7, r6, r10, r3
	smlal r7, r6, r8, r4
	mov r3, r7, lsr #0xc
	orr r3, r3, r6, lsl #0x14
	str r3, [r2, #0xc]
	ldr r6, [r1, #0x18]
	ldr r7, [r1, #0x8]
	smull r4, r3, r5, r6
	smlal r4, r3, r9, r7
	ldr r9, [r1, #0x28]
	ldr r5, [r1, #0x38]
	smlal r4, r3, r10, r9
	smlal r4, r3, r8, r5
	mov r4, r4, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x8]
	ldr r8, [r0, #0x14]
	ldr r10, [r0, #0x10]
	smull r4, r3, r8, r6
	smlal r4, r3, r10, r7
	ldr r7, [r0, #0x18]
	ldr r6, [r0, #0x1c]
	smlal r4, r3, r7, r9
	smlal r4, r3, r6, r5
	mov r4, r4, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x18]
	ldr r3, [r1, #0x14]
	ldr r4, [r1, #0x4]
	smull r11, r3, r8, r3
	smlal r11, r3, r10, r4
	ldr r5, [r1, #0x24]
	ldr r9, [r1, #0x34]
	smlal r11, r3, r7, r5
	smlal r11, r3, r6, r9
	mov r4, r11, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x14]
	ldr r3, [r1, #0x1c]
	ldr r4, [r1, #0xc]
	smull r11, r3, r8, r3
	smlal r11, r3, r10, r4
	ldr r5, [r1, #0x2c]
	ldr r9, [r1, #0x3c]
	smlal r11, r3, r7, r5
	smlal r11, r3, r6, r9
	mov r4, r11, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x1c]
	ldr r9, [r1, #0x10]
	ldr r11, [r1, #0x0]
	smull r4, r3, r8, r9
	smlal r4, r3, r10, r11
	ldr r5, [r1, #0x20]
	ldr r8, [r1, #0x30]
	smlal r4, r3, r7, r5
	smlal r4, r3, r6, r8
	mov r4, r4, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x10]
	ldr r6, [r0, #0x24]
	ldr r7, [r0, #0x20]
	smull r4, r3, r6, r9
	smlal r4, r3, r7, r11
	ldr r10, [r0, #0x28]
	add lr, sp, #0x0
	smlal r4, r3, r10, r5
	ldr r5, [r0, #0x2c]
	cmp r2, lr
	smlal r4, r3, r5, r8
	mov r4, r4, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x20]
	ldr r3, [r1, #0x14]
	ldr r4, [r1, #0x4]
	smull r11, r3, r6, r3
	smlal r11, r3, r7, r4
	ldr r8, [r1, #0x24]
	ldr r9, [r1, #0x34]
	smlal r11, r3, r10, r8
	smlal r11, r3, r5, r9
	mov r4, r11, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x24]
	ldr r3, [r1, #0x1c]
	ldr r4, [r1, #0xc]
	smull r11, r3, r6, r3
	smlal r11, r3, r7, r4
	ldr r8, [r1, #0x2c]
	ldr r9, [r1, #0x3c]
	smlal r11, r3, r10, r8
	smlal r11, r3, r5, r9
	mov r4, r11, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x2c]
	ldr r9, [r1, #0x18]
	ldr r8, [r1, #0x8]
	smull r4, r3, r6, r9
	smlal r4, r3, r7, r8
	ldr r7, [r1, #0x28]
	ldr r6, [r1, #0x38]
	smlal r4, r3, r10, r7
	smlal r4, r3, r5, r6
	mov r4, r4, lsr #0xc
	orr r4, r4, r3, lsl #0x14
	str r4, [r2, #0x28]
	ldr r5, [r0, #0x34]
	ldr r4, [r0, #0x30]
	smull r10, r9, r5, r9
	ldr r3, [r0, #0x38]
	smlal r10, r9, r4, r8
	smlal r10, r9, r3, r7
	ldr r0, [r0, #0x3c]
	addne sp, sp, #0x44
	smlal r10, r9, r0, r6
	mov r6, r10, lsr #0xc
	orr r6, r6, r9, lsl #0x14
	str r6, [r2, #0x38]
	ldr r6, [r1, #0x14]
	ldr r7, [r1, #0x4]
	smull r10, r6, r5, r6
	smlal r10, r6, r4, r7
	ldr r8, [r1, #0x24]
	ldr r9, [r1, #0x34]
	smlal r10, r6, r3, r8
	smlal r10, r6, r0, r9
	mov r7, r10, lsr #0xc
	orr r7, r7, r6, lsl #0x14
	str r7, [r2, #0x34]
	ldr r6, [r1, #0x10]
	ldr r7, [r1, #0x0]
	smull r10, r6, r5, r6
	smlal r10, r6, r4, r7
	ldr r8, [r1, #0x20]
	ldr r9, [r1, #0x30]
	smlal r10, r6, r3, r8
	smlal r10, r6, r0, r9
	mov r7, r10, lsr #0xc
	orr r7, r7, r6, lsl #0x14
	str r7, [r2, #0x30]
	ldr r8, [r1, #0x3c]
	ldr r7, [r1, #0x2c]
	ldr r6, [r1, #0xc]
	ldr r1, [r1, #0x1c]
	smull r9, r1, r5, r1
	smlal r9, r1, r4, r6
	smlal r9, r1, r3, r7
	smlal r9, r1, r0, r8
	mov r0, r9, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	str r0, [r2, #0x3c]
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr, {r0-r3}
	stmia r12, {r0-r3}
	add sp, sp, #0x44
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start MTX_TransApply44
MTX_TransApply44: ; 0x020C4DB4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	cmp r7, r6
	beq _020C4DD8
	bl MI_Copy48B
_020C4DD8:
	ldr r0, [r7, #0x10]
	ldr r1, [r7, #0x0]
	smull r3, r2, r4, r0
	smlal r3, r2, r5, r1
	ldr r0, [sp, #0x18]
	ldr r1, [r7, #0x20]
	ldr r12, [r7, #0x30]
	smlal r3, r2, r0, r1
	mov r1, r3, lsr #0xc
	orr r1, r1, r2, lsl #0x14
	add r1, r12, r1
	str r1, [r6, #0x30]
	ldr r1, [r7, #0x14]
	ldr r2, [r7, #0x4]
	smull r12, r3, r4, r1
	smlal r12, r3, r5, r2
	ldr r1, [r7, #0x24]
	ldr r2, [r7, #0x34]
	smlal r12, r3, r0, r1
	mov r1, r12, lsr #0xc
	orr r1, r1, r3, lsl #0x14
	add r1, r2, r1
	str r1, [r6, #0x34]
	ldr r1, [r7, #0x18]
	ldr r2, [r7, #0x8]
	smull r12, r3, r4, r1
	smlal r12, r3, r5, r2
	ldr r1, [r7, #0x28]
	ldr r2, [r7, #0x38]
	smlal r12, r3, r0, r1
	mov r1, r12, lsr #0xc
	orr r1, r1, r3, lsl #0x14
	add r1, r2, r1
	str r1, [r6, #0x38]
	ldr r1, [r7, #0x1c]
	ldr r2, [r7, #0xc]
	smull r12, r3, r4, r1
	smlal r12, r3, r5, r2
	ldr r1, [r7, #0x2c]
	ldr r2, [r7, #0x3c]
	smlal r12, r3, r0, r1
	mov r0, r12, lsr #0xc
	orr r0, r0, r3, lsl #0x14
	add r0, r2, r0
	str r0, [r6, #0x3c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FX_ModS32
FX_ModS32: ; 0x020C4E98
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr ip, _020C4EE0 ; =0x04000280
	mov lr, #0x0
	ldr r3, _020C4EE4 ; =0x04000290
	strh lr, [r12, #0x0]
	ldr r2, _020C4EE8 ; =0x04000298
	str r0, [r3, #0x0]
	str r1, [r2, #0x0]
	str lr, [r2, #0x4]
_020C4EC0:
	ldrh r0, [r12, #0x0]
	ands r0, r0, #0x8000
	bne _020C4EC0
	ldr r0, _020C4EEC ; =0x040002A8
	ldr r0, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C4EE0: .word 0x04000280
_020C4EE4: .word 0x04000290
_020C4EE8: .word 0x04000298
_020C4EEC: .word 0x040002A8

	arm_func_start FX_DivS32
FX_DivS32: ; 0x020C4EF0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr ip, _020C4F38 ; =0x04000280
	mov lr, #0x0
	ldr r3, _020C4F3C ; =0x04000290
	strh lr, [r12, #0x0]
	ldr r2, _020C4F40 ; =0x04000298
	str r0, [r3, #0x0]
	str r1, [r2, #0x0]
	str lr, [r2, #0x4]
_020C4F18:
	ldrh r0, [r12, #0x0]
	ands r0, r0, #0x8000
	bne _020C4F18
	ldr r0, _020C4F44 ; =0x040002A0
	ldr r0, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C4F38: .word 0x04000280
_020C4F3C: .word 0x04000290
_020C4F40: .word 0x04000298
_020C4F44: .word 0x040002A0

	arm_func_start FX_DivAsync
FX_DivAsync: ; 0x020C4F48
	ldr r2, _020C4F74 ; =0x04000280
	mov r12, #0x1
	ldr r3, _020C4F78 ; =0x04000290
	strh r12, [r2, #0x0]
	mov r12, #0x0
	str r12, [r3, #0x0]
	ldr r2, _020C4F7C ; =0x04000298
	str r0, [r3, #0x4]
	str r1, [r2, #0x0]
	str r12, [r2, #0x4]
	bx lr
	.balign 4
_020C4F74: .word 0x04000280
_020C4F78: .word 0x04000290
_020C4F7C: .word 0x04000298

	arm_func_start FX_GetSqerResult
FX_GetSqerResult: ; 0x020C4F80
	ldr r1, _020C4FA4 ; =0x040002B0
_020C4F84:
	ldrh r0, [r1, #0x0]
	ands r0, r0, #0x8000
	bne _020C4F84
	ldr r0, _020C4FA8 ; =0x040002B4
	ldr r0, [r0, #0x0]
	add r0, r0, #0x200
	mov r0, r0, lsr #0xa
	bx lr
	.balign 4
_020C4FA4: .word 0x040002B0
_020C4FA8: .word 0x040002B4

	arm_func_start FX_InvAsync
FX_InvAsync:
	ldr r1, _020C4FDC ; =0x04000280
	mov r3, #0x1
	ldr r2, _020C4FE0 ; =0x04000290
	strh r3, [r1, #0x0]
	mov r12, #0x0
	str r12, [r2, #0x0]
	mov r3, #0x1000
	ldr r1, _020C4FE4 ; =0x04000298
	str r3, [r2, #0x4]
	str r0, [r1, #0x0]
	str r12, [r1, #0x4]
	bx lr
	.balign 4
_020C4FDC: .word 0x04000280
_020C4FE0: .word 0x04000290
_020C4FE4: .word 0x04000298

	arm_func_start FX_GetDivResult
FX_GetDivResult: ; 0x020C4FE8
	ldr r1, _020C501C ; =0x04000280
_020C4FEC:
	ldrh r0, [r1, #0x0]
	ands r0, r0, #0x8000
	bne _020C4FEC
	ldr r1, _020C5020 ; =0x040002A0
	mov r0, #0x80000
	ldr r2, [r1, #0x0]
	ldr r1, [r1, #0x4]
	adds r0, r2, r0
	adc r1, r1, #0x0
	mov r0, r0, lsr #0x14
	orr r0, r0, r1, lsl #0xc
	bx lr
	.balign 4
_020C501C: .word 0x04000280
_020C5020: .word 0x040002A0

	arm_func_start FX_GetDivResultFx64c
FX_GetDivResultFx64c: ; 0x020C5024
	ldr r1, _020C5044 ; =0x04000280
_020C5028:
	ldrh r0, [r1, #0x0]
	ands r0, r0, #0x8000
	bne _020C5028
	ldr r1, _020C5048 ; =0x040002A0
	ldr r0, [r1, #0x0]
	ldr r1, [r1, #0x4]
	bx lr
	.balign 4
_020C5044: .word 0x04000280
_020C5048: .word 0x040002A0

	arm_func_start FX_Sqrt
FX_Sqrt: ; 0x020C504C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	addle sp, sp, #0x4
	movle r0, #0x0
	ldmleia sp!, {lr}
	bxle lr
	ldr r2, _020C5094 ; =0x040002B0
	mov r3, #0x1
	strh r3, [r2, #0x0]
	ldr r1, _020C5098 ; =0x040002B8
	mov r2, #0x0
	str r2, [r1, #0x0]
	str r0, [r1, #0x4]
	bl FX_GetSqerResult
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C5094: .word 0x040002B0
_020C5098: .word 0x040002B8

	arm_func_start FX_Inv
FX_Inv: ; 0x020C509C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FX_InvAsync
	bl FX_GetDivResult
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FX_Div
FX_Div: ; 0x020C50B8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FX_DivAsync
	bl FX_GetDivResult
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start VEC_MultAdd
VEC_MultAdd: ; 0x020C50D4
	stmdb sp!, {r4,lr}
	ldr r4, [r1, #0x0]
	ldr lr, [r2, #0x0]
	smull r12, r4, r0, r4
	mov r12, r12, lsr #0xc
	orr r12, r12, r4, lsl #0x14
	add r4, lr, r12
	str r4, [r3, #0x0]
	ldr r12, [r1, #0x4]
	ldr r4, [r2, #0x4]
	smull lr, r12, r0, r12
	mov lr, lr, lsr #0xc
	orr lr, lr, r12, lsl #0x14
	add r4, r4, lr
	str r4, [r3, #0x4]
	ldr r1, [r1, #0x8]
	ldr r12, [r2, #0x8]
	smull r2, r1, r0, r1
	mov r0, r2, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	add r0, r12, r0
	str r0, [r3, #0x8]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start VEC_Fx16Normalize
VEC_Fx16Normalize: ; 0x020C5134
	stmdb sp!, {r4-r8,lr}
	ldrsh r4, [r0, #0x0]
	ldrsh r3, [r0, #0x2]
	ldrsh r2, [r0, #0x4]
	mul r8, r4, r4
	mul r7, r3, r3
	mul r6, r2, r2
	ldr r2, _020C526C ; =0x04000280
	mov r3, #0x2
	ldr r4, _020C5270 ; =0x04000290
	strh r3, [r2, #0x0]
	mov r2, #0x0
	str r2, [r4, #0x0]
	mov r5, #0x1000000
	mov r2, r8, asr #0x1f
	adds r3, r8, r7
	adc r2, r2, r7, asr #0x1f
	adds r7, r3, r6
	adc r6, r2, r6, asr #0x1f
	mov r3, r6, lsl #0x2
	ldr r2, _020C5274 ; =0x04000298
	str r5, [r4, #0x4]
	str r7, [r2, #0x0]
	ldr r5, _020C5278 ; =0x040002B0
	str r6, [r2, #0x4]
	mov r4, #0x1
	ldr r2, _020C527C ; =0x040002B8
	strh r4, [r5, #0x0]
	mov r4, r7, lsl #0x2
	str r4, [r2, #0x0]
	orr r3, r3, r7, lsr #0x1e
	str r3, [r2, #0x4]
_020C51B4:
	ldrh r2, [r5, #0x0]
	ands r2, r2, #0x8000
	bne _020C51B4
	ldr r2, _020C5280 ; =0x040002B4
	ldr r12, [r2, #0x0]
	ldr r3, _020C526C ; =0x04000280
_020C51CC:
	ldrh r2, [r3, #0x0]
	ands r2, r2, #0x8000
	bne _020C51CC
	ldr r7, _020C5284 ; =0x040002A0
	ldrsh r5, [r0, #0x0]
	ldr r6, [r7, #0x0]
	mov r4, r12, asr #0x1f
	umull r3, r2, r6, r12
	mla r2, r6, r4, r2
	ldr r8, [r7, #0x4]
	mov r4, r5, asr #0x1f
	umull r7, r6, r3, r5
	mov lr, #0x0
	mla r2, r8, r12, r2
	mla r6, r3, r4, r6
	mla r6, r2, r5, r6
	adds r4, r7, lr
	adc r4, r6, #0x1000
	mov r4, r4, asr #0xd
	strh r4, [r1, #0x0]
	ldrsh r5, [r0, #0x2]
	umull r6, r12, r3, r5
	mov r4, r5, asr #0x1f
	mla r12, r3, r4, r12
	mla r12, r2, r5, r12
	adds r4, r6, lr
	adc r4, r12, #0x1000
	mov r4, r4, asr #0xd
	strh r4, [r1, #0x2]
	ldrsh r12, [r0, #0x4]
	umull r5, r4, r3, r12
	mov r0, r12, asr #0x1f
	adds r5, r5, lr
	mla r4, r3, r0, r4
	mla r4, r2, r12, r4
	adc r0, r4, #0x1000
	mov r0, r0, asr #0xd
	strh r0, [r1, #0x4]
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020C526C: .word 0x04000280
_020C5270: .word 0x04000290
_020C5274: .word 0x04000298
_020C5278: .word 0x040002B0
_020C527C: .word 0x040002B8
_020C5280: .word 0x040002B4
_020C5284: .word 0x040002A0

	arm_func_start VEC_Normalize
VEC_Normalize:
	stmdb sp!, {r4-r8,lr}
	ldr r3, [r0, #0x4]
	ldr r4, [r0, #0x0]
	smull r2, r7, r3, r3
	smlal r2, r7, r4, r4
	ldr r4, [r0, #0x8]
	ldr r3, _020C53AC ; =0x04000280
	smlal r2, r7, r4, r4
	mov r6, #0x2
	mov r4, r7, lsl #0x2
	ldr r5, _020C53B0 ; =0x04000290
	strh r6, [r3, #0x0]
	mov r3, #0x0
	str r3, [r5, #0x0]
	mov r6, #0x1000000
	ldr r3, _020C53B4 ; =0x04000298
	str r6, [r5, #0x4]
	str r2, [r3, #0x0]
	ldr r6, _020C53B8 ; =0x040002B0
	str r7, [r3, #0x4]
	mov r5, #0x1
	ldr r3, _020C53BC ; =0x040002B8
	strh r5, [r6, #0x0]
	mov r5, r2, lsl #0x2
	str r5, [r3, #0x0]
	orr r4, r4, r2, lsr #0x1e
	str r4, [r3, #0x4]
_020C52F4:
	ldrh r2, [r6, #0x0]
	ands r2, r2, #0x8000
	bne _020C52F4
	ldr r2, _020C53C0 ; =0x040002B4
	ldr r12, [r2, #0x0]
	ldr r3, _020C53AC ; =0x04000280
_020C530C:
	ldrh r2, [r3, #0x0]
	ands r2, r2, #0x8000
	bne _020C530C
	ldr r7, _020C53C4 ; =0x040002A0
	ldr r5, [r0, #0x0]
	ldr r6, [r7, #0x0]
	mov r4, r12, asr #0x1f
	umull r3, r2, r6, r12
	mla r2, r6, r4, r2
	ldr r8, [r7, #0x4]
	mov r4, r5, asr #0x1f
	umull r7, r6, r3, r5
	mov lr, #0x0
	mla r2, r8, r12, r2
	mla r6, r3, r4, r6
	mla r6, r2, r5, r6
	adds r4, r7, lr
	adc r4, r6, #0x1000
	mov r4, r4, asr #0xd
	str r4, [r1, #0x0]
	ldr r5, [r0, #0x4]
	umull r6, r12, r3, r5
	mov r4, r5, asr #0x1f
	mla r12, r3, r4, r12
	mla r12, r2, r5, r12
	adds r4, r6, lr
	adc r4, r12, #0x1000
	mov r4, r4, asr #0xd
	str r4, [r1, #0x4]
	ldr r12, [r0, #0x8]
	umull r5, r4, r3, r12
	mov r0, r12, asr #0x1f
	adds r5, r5, lr
	mla r4, r3, r0, r4
	mla r4, r2, r12, r4
	adc r0, r4, #0x1000
	mov r0, r0, asr #0xd
	str r0, [r1, #0x8]
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020C53AC: .word 0x04000280
_020C53B0: .word 0x04000290
_020C53B4: .word 0x04000298
_020C53B8: .word 0x040002B0
_020C53BC: .word 0x040002B8
_020C53C0: .word 0x040002B4
_020C53C4: .word 0x040002A0

	arm_func_start VEC_Mag
VEC_Mag:
	ldr r2, [r0, #0x4]
	ldr r3, [r0, #0x0]
	smull r12, r1, r2, r2
	smlal r12, r1, r3, r3
	ldr r0, [r0, #0x8]
	ldr r3, _020C5424 ; =0x040002B0
	smlal r12, r1, r0, r0
	mov r2, #0x1
	mov r1, r1, lsl #0x2
	ldr r0, _020C5428 ; =0x040002B8
	strh r2, [r3, #0x0]
	mov r2, r12, lsl #0x2
	str r2, [r0, #0x0]
	orr r1, r1, r12, lsr #0x1e
	str r1, [r0, #0x4]
_020C5404:
	ldrh r0, [r3, #0x0]
	ands r0, r0, #0x8000
	bne _020C5404
	ldr r0, _020C542C ; =0x040002B4
	ldr r0, [r0, #0x0]
	add r0, r0, #0x1
	mov r0, r0, asr #0x1
	bx lr
	.balign 4
_020C5424: .word 0x040002B0
_020C5428: .word 0x040002B8
_020C542C: .word 0x040002B4

	arm_func_start VEC_Fx16CrossProduct
VEC_Fx16CrossProduct: ; 0x020C5430
	stmdb sp!, {r4-r6,lr}
	ldrsh r4, [r1, #0x4]
	ldrsh r12, [r0, #0x2]
	ldrsh lr, [r0, #0x0]
	ldrsh r3, [r1, #0x2]
	ldrsh r6, [r0, #0x4]
	ldrsh r1, [r1, #0x0]
	mul r5, r12, r4
	mul r0, r6, r3
	sub r0, r5, r0
	add r0, r0, #0x800
	mov r0, r0, asr #0xc
	mul r5, r6, r1
	mul r4, lr, r4
	sub r4, r5, r4
	add r4, r4, #0x800
	mul r3, lr, r3
	mul r1, r12, r1
	sub r1, r3, r1
	add r1, r1, #0x800
	strh r0, [r2, #0x0]
	mov r0, r4, asr #0xc
	strh r0, [r2, #0x2]
	mov r0, r1, asr #0xc
	strh r0, [r2, #0x4]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start VEC_CrossProduct
VEC_CrossProduct:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r12, [r1, #0x8]
	ldr r9, [r0, #0x4]
	ldr r3, [r0, #0x0]
	ldr r11, [r1, #0x4]
	ldr r0, [r0, #0x8]
	ldr r10, [r1, #0x0]
	smull r4, r7, r9, r12
	smull r1, r6, r0, r11
	subs r8, r4, r1
	smull r5, r4, r0, r10
	smull lr, r12, r3, r12
	smull r1, r0, r3, r11
	smull r10, r3, r9, r10
	sbc r6, r7, r6
	mov r9, #0x800
	adds r7, r8, r9
	adc r6, r6, #0x0
	subs r8, r5, lr
	sbc r5, r4, r12
	adds r8, r8, r9
	mov r4, r7, lsr #0xc
	adc r5, r5, #0x0
	subs r1, r1, r10
	orr r4, r4, r6, lsl #0x14
	mov r6, r8, lsr #0xc
	sbc r0, r0, r3
	adds r1, r1, r9
	str r4, [r2, #0x0]
	orr r6, r6, r5, lsl #0x14
	adc r0, r0, #0x0
	mov r1, r1, lsr #0xc
	str r6, [r2, #0x4]
	orr r1, r1, r0, lsl #0x14
	str r1, [r2, #0x8]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start VEC_Fx16DotProduct
VEC_Fx16DotProduct: ; 0x020C5538
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldrsh lr, [r0, #0x2]
	ldrsh r12, [r1, #0x2]
	ldrsh r3, [r0, #0x4]
	ldrsh r2, [r1, #0x4]
	ldrsh r5, [r0, #0x0]
	ldrsh r4, [r1, #0x0]
	smulbb r1, lr, r12
	smulbb r0, r3, r2
	smlabb r1, r5, r4, r1
	add r0, r0, #0x800
	adds r2, r1, r0
	mov r1, r1, asr #0x1f
	adc r1, r1, r0, asr #0x1f
	mov r0, r2, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start VEC_DotProduct
VEC_DotProduct:
	stmdb sp!, {r4,lr}
	ldr r3, [r0, #0x4]
	ldr r2, [r1, #0x4]
	ldr r12, [r0, #0x0]
	smull r4, lr, r3, r2
	ldr r2, [r1, #0x0]
	ldr r3, [r0, #0x8]
	smlal r4, lr, r12, r2
	ldr r1, [r1, #0x8]
	mov r0, #0x800
	smlal r4, lr, r3, r1
	adds r0, r4, r0
	adc r1, lr, #0x0
	mov r0, r0, lsr #0xc
	orr r0, r0, r1, lsl #0x14
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start VEC_Fx16Add
VEC_Fx16Add: ; 0x020C55CC
	ldrsh r12, [r0, #0x0]
	ldrsh r3, [r1, #0x0]
	add r3, r12, r3
	strh r3, [r2, #0x0]
	ldrsh r12, [r0, #0x2]
	ldrsh r3, [r1, #0x2]
	add r3, r12, r3
	strh r3, [r2, #0x2]
	ldrsh r3, [r0, #0x4]
	ldrsh r0, [r1, #0x4]
	add r0, r3, r0
	strh r0, [r2, #0x4]
	bx lr

	arm_func_start VEC_Subtract
VEC_Subtract: ; 0x020C5600
	ldr r12, [r0, #0x0]
	ldr r3, [r1, #0x0]
	sub r3, r12, r3
	str r3, [r2, #0x0]
	ldr r12, [r0, #0x4]
	ldr r3, [r1, #0x4]
	sub r3, r12, r3
	str r3, [r2, #0x4]
	ldr r3, [r0, #0x8]
	ldr r0, [r1, #0x8]
	sub r0, r3, r0
	str r0, [r2, #0x8]
	bx lr

	arm_func_start VEC_Add
VEC_Add: ; 0x020C5634
	ldr r12, [r0, #0x0]
	ldr r3, [r1, #0x0]
	add r3, r12, r3
	str r3, [r2, #0x0]
	ldr r12, [r0, #0x4]
	ldr r3, [r1, #0x4]
	add r3, r12, r3
	str r3, [r2, #0x4]
	ldr r3, [r0, #0x8]
	ldr r0, [r1, #0x8]
	add r0, r3, r0
	str r0, [r2, #0x8]
	bx lr

	arm_func_start FX_Modf
FX_Modf: ; 0x020C5668
	stmdb sp!, {r4,lr}
	cmp r0, #0x0
	ble _020C5704
	cmp r1, #0x0
	ble _020C56B4
	cmp r1, r0
	movgt r3, r0
	movgt r4, #0x0
	movgt r0, #0x1
	bgt _020C57C8
	cmp r1, r0
	movlt r3, r1
	movlt r1, r0
	movlt r4, #0x4000
	movlt r0, #0x0
	blt _020C57C8
	mov r0, #0x2000
	ldmia sp!, {r4,lr}
	bx lr
_020C56B4:
	cmp r1, #0x0
	bge _020C56F8
	rsb r1, r1, #0x0
	cmp r1, r0
	movlt r3, r1
	movlt r1, r0
	movlt r4, #0x4000
	movlt r0, #0x1
	blt _020C57C8
	cmp r1, r0
	movgt r3, r0
	movgt r4, #0x8000
	movgt r0, #0x0
	bgt _020C57C8
	mov r0, #0x6000
	ldmia sp!, {r4,lr}
	bx lr
_020C56F8:
	mov r0, #0x4000
	ldmia sp!, {r4,lr}
	bx lr
_020C5704:
	cmp r0, #0x0
	bge _020C57B4
	cmp r1, #0x0
	rsb r2, r0, #0x0
	bge _020C5760
	rsb r1, r1, #0x0
	cmp r1, r2
	movgt r0, #0x8000
	rsbgt r4, r0, #0x0
	movgt r3, r2
	movgt r0, #0x1
	bgt _020C57C8
	cmp r1, r2
	bge _020C5754
	mov r0, #0x4000
	mov r3, r1
	mov r1, r2
	rsb r4, r0, #0x0
	mov r0, #0x0
	b _020C57C8
_020C5754:
	mov r0, #0xa000
	ldmia sp!, {r4,lr}
	bx lr
_020C5760:
	cmp r1, #0x0
	ble _020C57A8
	cmp r1, r2
	bge _020C5788
	mov r0, #0x4000
	mov r3, r1
	mov r1, r2
	rsb r4, r0, #0x0
	mov r0, #0x1
	b _020C57C8
_020C5788:
	cmp r1, r2
	movgt r4, #0x0
	movgt r3, r2
	movgt r0, r4
	bgt _020C57C8
	mov r0, #0xe000
	ldmia sp!, {r4,lr}
	bx lr
_020C57A8:
	mov r0, #0xc000
	ldmia sp!, {r4,lr}
	bx lr
_020C57B4:
	cmp r1, #0x0
	movge r0, #0x0
	movlt r0, #0x8000
	ldmia sp!, {r4,lr}
	bx lr
_020C57C8:
	cmp r1, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r0, #0x0
	beq _020C580C
	mov r0, r3
	bl FX_Div
	mov r1, r0, asr #0x5
	ldr r0, _020C5838 ; =0x02103A38
	mov r1, r1, lsl #0x1
	ldrsh r0, [r0, r1]
	add r0, r4, r0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {r4,lr}
	bx lr
_020C580C:
	mov r0, r3
	bl FX_Div
	mov r1, r0, asr #0x5
	ldr r0, _020C5838 ; =0x02103A38
	mov r1, r1, lsl #0x1
	ldrsh r0, [r0, r1]
	sub r0, r4, r0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C5838: .word 0x02103A38

	arm_func_start FUN_020C583C
FUN_020C583C: ; 0x020C583C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	blt _020C58A4
	cmp r0, #0x1000
	ble _020C5880
	bl FX_Inv
	mov r1, r0, asr #0x5
	ldr r0, _020C5924 ; =0x02103A38
	mov r1, r1, lsl #0x1
	ldrsh r0, [r0, r1]
	add sp, sp, #0x4
	rsb r0, r0, #0x4000
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {lr}
	bx lr
_020C5880:
	cmp r0, #0x1000
	movlt r1, r0, asr #0x5
	ldrlt r0, _020C5924 ; =0x02103A38
	movlt r1, r1, lsl #0x1
	ldrlth r0, [r0, r1]
	add sp, sp, #0x4
	movge r0, #0x2000
	ldmia sp!, {lr}
	bx lr
_020C58A4:
	mov r1, #0x1000
	rsb r1, r1, #0x0
	cmp r0, r1
	bge _020C58E4
	rsb r0, r0, #0x0
	bl FX_Inv
	mov r1, r0, asr #0x5
	ldr r0, _020C5924 ; =0x02103A38

	arm_func_start FUN_020C58C4
FUN_020C58C4: ; 0x020C58C4
	mov r1, r1, lsl #0x1
	ldrsh r0, [r0, r1]
	add sp, sp, #0x4
	sub r0, r0, #0x4000
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {lr}
	bx lr
_020C58E4:
	cmp r0, r1
	addle sp, sp, #0x4
	movle r0, #0xe000
	ldmleia sp!, {lr}
	bxle lr
	rsb r0, r0, #0x0
	mov r1, r0, asr #0x5
	ldr r0, _020C5924 ; =0x02103A38
	mov r1, r1, lsl #0x1
	ldrsh r0, [r0, r1]
	rsb r0, r0, #0x0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C5924: .word 0x02103A38

	arm_func_start FUN_020C5928
FUN_020C5928: ; 0x020C5928
	cmp r0, #0x0
	blt _020C5948
	ldr r2, _020C596C ; =0x7FFFF000
	ldr r3, _020C5970 ; =0x00000FFF
	and r2, r0, r2
	str r2, [r1, #0x0]
	and r0, r0, r3
	bx lr
_020C5948:
	ldr r2, _020C596C ; =0x7FFFF000
	rsb r3, r0, #0x0
	ldr r0, _020C5970 ; =0x00000FFF
	and r2, r3, r2
	rsb r2, r2, #0x0
	and r0, r3, r0
	str r2, [r1, #0x0]
	rsb r0, r0, #0x0
	bx lr
	.balign 4
_020C596C: .word 0x7FFFF000
_020C5970: .word 0x00000FFF

	arm_func_start FX_Init
FX_Init: ; 0x020C5974
	bx lr
