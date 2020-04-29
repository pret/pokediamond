	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start GXS_EndLoadOBJExtPltt
GXS_EndLoadOBJExtPltt: ; 0x020C8728
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C876C ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C8748
	bl MI_WaitDma
_020C8748:
	ldr r0, _020C8770 ; =0x021D33F8
	ldr r0, [r0, #0x0]
	bl GX_SetBankForSubOBJExtPltt
	ldr r0, _020C8770 ; =0x021D33F8
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C876C: .word 0x02106814
_020C8770: .word 0x021D33F8

	arm_func_start GXS_LoadOBJExtPltt
GXS_LoadOBJExtPltt: ; 0x020C8774
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	ldr r3, _020C87E0 ; =0x02106814
	mvn r12, #0x0
	ldr lr, [r3, #0x0]
	mov r5, r0
	mov r4, r1
	mov r3, r2
	cmp lr, r12
	beq _020C87C8
	ldr r2, _020C87E4 ; =0x068A0000
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r0, lr
	mov r1, r5
	add r2, r4, r2
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
_020C87C8:
	ldr r1, _020C87E4 ; =0x068A0000
	add r1, r4, r1
	bl MIi_CpuCopy32
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C87E0: .word 0x02106814
_020C87E4: .word 0x068A0000

	arm_func_start GXS_BeginLoadOBJExtPltt
GXS_BeginLoadOBJExtPltt: ; 0x020C87E8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl GX_ResetBankForSubOBJ
	ldr r1, _020C8808 ; =0x021D33F8
	str r0, [r1, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C8808: .word 0x021D33F8

	arm_func_start GXS_EndLoadBGExtPltt
GXS_EndLoadBGExtPltt: ; 0x020C880C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C8850 ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C882C
	bl MI_WaitDma
_020C882C:
	ldr r0, _020C8854 ; =0x021D33E0
	ldr r0, [r0, #0x0]
	bl GX_SetBankForSubBGExtPltt
	ldr r0, _020C8854 ; =0x021D33E0
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C8850: .word 0x02106814
_020C8854: .word 0x021D33E0

	arm_func_start GXS_LoadBGExtPltt
GXS_LoadBGExtPltt: ; 0x020C8858
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	ldr r3, _020C88C4 ; =0x02106814
	mvn r12, #0x0
	ldr lr, [r3, #0x0]
	mov r5, r0
	mov r4, r1
	mov r3, r2
	cmp lr, r12
	beq _020C88AC
	ldr r2, _020C88C8 ; =0x06898000
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r0, lr
	mov r1, r5
	add r2, r4, r2
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
_020C88AC:
	ldr r1, _020C88C8 ; =0x06898000
	add r1, r4, r1
	bl MIi_CpuCopy32
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C88C4: .word 0x02106814
_020C88C8: .word 0x06898000

	arm_func_start GXS_BeginLoadBGExtPltt
GXS_BeginLoadBGExtPltt: ; 0x020C88CC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020C6034
	ldr r1, _020C88EC ; =0x021D33E0
	str r0, [r1, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C88EC: .word 0x021D33E0

	arm_func_start GX_EndLoadOBJExtPltt
GX_EndLoadOBJExtPltt: ; 0x020C88F0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C893C ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C8910
	bl MI_WaitDma
_020C8910:
	ldr r0, _020C8940 ; =0x021D33E8
	ldr r0, [r0, #0x0]
	bl GX_SetBankForOBJExtPltt
	ldr r1, _020C8940 ; =0x021D33E8
	mov r2, #0x0
	ldr r0, _020C8944 ; =0x021D33E4
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C893C: .word 0x02106814
_020C8940: .word 0x021D33E8
_020C8944: .word 0x021D33E4

	arm_func_start GX_LoadOBJExtPltt
GX_LoadOBJExtPltt: ; 0x020C8948
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	ldr ip, _020C89B4 ; =0x021D33E4
	ldr r3, _020C89B8 ; =0x02106814
	ldr r4, [r12, #0x0]
	ldr lr, [r3, #0x0]
	mvn r12, #0x0
	mov r5, r0
	mov r3, r2
	cmp lr, r12
	add r4, r4, r1
	beq _020C89A0
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r0, lr
	mov r1, r5
	mov r2, r4
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
_020C89A0:
	mov r1, r4
	bl MIi_CpuCopy32
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C89B4: .word 0x021D33E4
_020C89B8: .word 0x02106814

	arm_func_start GX_BeginLoadOBJExtPltt
GX_BeginLoadOBJExtPltt: ; 0x020C89BC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl GX_ResetBankForOBJExtPltt
	ldr r1, _020C8A1C ; =0x021D33E8
	cmp r0, #0x0
	str r0, [r1, #0x0]
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	cmp r0, #0x20
	beq _020C8A04
	cmp r0, #0x40
	ldreq r1, _020C8A20 ; =0x06894000
	ldreq r0, _020C8A24 ; =0x021D33E4
	add sp, sp, #0x4
	streq r1, [r0, #0x0]
	ldmia sp!, {lr}
	bx lr
_020C8A04:
	ldr r1, _020C8A28 ; =0x06890000
	ldr r0, _020C8A24 ; =0x021D33E4
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C8A1C: .word 0x021D33E8
_020C8A20: .word 0x06894000
_020C8A24: .word 0x021D33E4
_020C8A28: .word 0x06890000

	arm_func_start GX_EndLoadBGExtPltt
GX_EndLoadBGExtPltt: ; 0x020C8A2C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C8A80 ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C8A4C
	bl MI_WaitDma
_020C8A4C:
	ldr r0, _020C8A84 ; =0x021D33F4
	ldr r0, [r0, #0x0]
	bl GX_SetBankForBGExtPltt
	ldr r2, _020C8A84 ; =0x021D33F4
	mov r3, #0x0
	ldr r1, _020C8A88 ; =0x021D33F0
	ldr r0, _020C8A8C ; =0x021D33EC
	str r3, [r2, #0x0]
	str r3, [r1, #0x0]
	str r3, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C8A80: .word 0x02106814
_020C8A84: .word 0x021D33F4
_020C8A88: .word 0x021D33F0
_020C8A8C: .word 0x021D33EC

	arm_func_start GX_LoadBGExtPltt
GX_LoadBGExtPltt: ; 0x020C8A90
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	ldr lr, _020C8B04 ; =0x021D33F0
	ldr ip, _020C8B08 ; =0x021D33EC
	ldr r3, _020C8B0C ; =0x02106814
	ldr lr, [lr, #0x0]
	ldr r4, [r12, #0x0]
	add r5, lr, r1
	ldr lr, [r3, #0x0]
	mvn r12, #0x0
	mov r1, r0
	mov r3, r2
	cmp lr, r12
	sub r4, r5, r4
	beq _020C8AF0
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r0, lr
	mov r2, r4
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
_020C8AF0:
	mov r1, r4
	bl MIi_CpuCopy32
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C8B04: .word 0x021D33F0
_020C8B08: .word 0x021D33EC
_020C8B0C: .word 0x02106814

	arm_func_start GX_BeginLoadBGExtPltt
GX_BeginLoadBGExtPltt: ; 0x020C8B10
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl GX_ResetBankForBGExtPltt
	ldr r1, _020C8BFC ; =0x021D33F4
	cmp r0, #0x20
	str r0, [r1, #0x0]
	bgt _020C8B60
	cmp r0, #0x20
	bge _020C8BD8
	cmp r0, #0x0
	bgt _020C8B4C
	add sp, sp, #0x4
	cmp r0, #0x0
	ldmia sp!, {lr}
	bx lr
_020C8B4C:
	cmp r0, #0x10
	beq _020C8B90
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020C8B60:
	cmp r0, #0x40
	bgt _020C8B7C
	cmp r0, #0x40
	beq _020C8BB4
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020C8B7C:
	cmp r0, #0x60
	beq _020C8BD8
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020C8B90:
	ldr r3, _020C8C00 ; =0x06880000
	ldr r1, _020C8C04 ; =0x021D33F0
	ldr r0, _020C8C08 ; =0x021D33EC
	mov r2, #0x0
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020C8BB4:
	ldr r3, _020C8C0C ; =0x06894000
	ldr r1, _020C8C04 ; =0x021D33F0
	ldr r0, _020C8C08 ; =0x021D33EC
	mov r2, #0x4000
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020C8BD8:
	ldr r3, _020C8C10 ; =0x06890000
	ldr r1, _020C8C04 ; =0x021D33F0
	ldr r0, _020C8C08 ; =0x021D33EC
	mov r2, #0x0
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C8BFC: .word 0x021D33F4
_020C8C00: .word 0x06880000
_020C8C04: .word 0x021D33F0
_020C8C08: .word 0x021D33EC
_020C8C0C: .word 0x06894000
_020C8C10: .word 0x06890000

	arm_func_start GXS_LoadBG3Char
GXS_LoadBG3Char: ; 0x020C8C14
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG3CharPtr
	ldr r1, _020C8C78 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8C60
	cmp r4, #0x30
	bls _020C8C60
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8C60:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8C78: .word 0x02106814

	arm_func_start GX_LoadBG3Char
GX_LoadBG3Char: ; 0x020C8C7C
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG3CharPtr
	ldr r1, _020C8CE0 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8CC8
	cmp r4, #0x30
	bls _020C8CC8
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8CC8:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8CE0: .word 0x02106814

	arm_func_start GXS_LoadBG2Char
GXS_LoadBG2Char: ; 0x020C8CE4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG2CharPtr
	ldr r1, _020C8D48 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8D30
	cmp r4, #0x30
	bls _020C8D30
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8D30:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8D48: .word 0x02106814

	arm_func_start GX_LoadBG2Char
GX_LoadBG2Char: ; 0x020C8D4C
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG2CharPtr
	ldr r1, _020C8DB0 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8D98
	cmp r4, #0x30
	bls _020C8D98
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8D98:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8DB0: .word 0x02106814

	arm_func_start GXS_LoadBG1Char
GXS_LoadBG1Char: ; 0x020C8DB4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG1CharPtr
	ldr r1, _020C8E18 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8E00
	cmp r4, #0x30
	bls _020C8E00
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8E00:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8E18: .word 0x02106814

	arm_func_start GX_LoadBG1Char
GX_LoadBG1Char: ; 0x020C8E1C
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG1CharPtr
	ldr r1, _020C8E80 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8E68
	cmp r4, #0x30
	bls _020C8E68
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8E68:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8E80: .word 0x02106814

	arm_func_start GXS_LoadBG0Char
GXS_LoadBG0Char: ; 0x020C8E84
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG0CharPtr
	ldr r1, _020C8EE8 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8ED0
	cmp r4, #0x30
	bls _020C8ED0
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8ED0:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8EE8: .word 0x02106814

	arm_func_start GX_LoadBG0Char
GX_LoadBG0Char: ; 0x020C8EEC
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG0CharPtr
	ldr r1, _020C8F50 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8F38
	cmp r4, #0x30
	bls _020C8F38
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8F38:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy32
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8F50: .word 0x02106814

	arm_func_start GXS_LoadBG3Scr
GXS_LoadBG3Scr: ; 0x020C8F54
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG3ScrPtr
	ldr r1, _020C8FB8 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C8FA0
	cmp r4, #0x1c
	bls _020C8FA0
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C8FA0:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C8FB8: .word 0x02106814

	arm_func_start GX_LoadBG3Scr
GX_LoadBG3Scr: ; 0x020C8FBC
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG3ScrPtr
	ldr r1, _020C9020 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C9008
	cmp r4, #0x1c
	bls _020C9008
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C9008:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C9020: .word 0x02106814

	arm_func_start GXS_LoadBG2Scr
GXS_LoadBG2Scr: ; 0x020C9024
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG2ScrPtr
	ldr r1, _020C9088 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C9070
	cmp r4, #0x1c
	bls _020C9070
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C9070:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C9088: .word 0x02106814

	arm_func_start GX_LoadBG2Scr
GX_LoadBG2Scr: ; 0x020C908C
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG2ScrPtr
	ldr r1, _020C90F0 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C90D8
	cmp r4, #0x1c
	bls _020C90D8
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C90D8:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C90F0: .word 0x02106814

	arm_func_start GXS_LoadBG1Scr
GXS_LoadBG1Scr: ; 0x020C90F4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG1ScrPtr
	ldr r1, _020C9158 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C9140
	cmp r4, #0x1c
	bls _020C9140
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C9140:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C9158: .word 0x02106814

	arm_func_start GX_LoadBG1Scr
GX_LoadBG1Scr: ; 0x020C915C
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG1ScrPtr
	ldr r1, _020C91C0 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C91A8
	cmp r4, #0x1c
	bls _020C91A8
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C91A8:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C91C0: .word 0x02106814

	arm_func_start GXS_LoadBG0Scr
GXS_LoadBG0Scr: ; 0x020C91C4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2S_GetBG0ScrPtr
	ldr r1, _020C9228 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C9210
	cmp r4, #0x1c
	bls _020C9210
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C9210:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C9228: .word 0x02106814

	arm_func_start GX_LoadBG0Scr
GX_LoadBG0Scr: ; 0x020C922C
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl G2_GetBG0ScrPtr
	ldr r1, _020C9290 ; =0x02106814
	mov r12, r0
	ldr r0, [r1, #0x0]
	mvn r1, #0x0
	cmp r0, r1
	beq _020C9278
	cmp r4, #0x1c
	bls _020C9278
	mov r1, r6
	mov r3, r4
	add r2, r12, r5
	bl MI_DmaCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
_020C9278:
	mov r0, r6
	mov r2, r4
	add r1, r12, r5
	bl MIi_CpuCopy16
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C9290: .word 0x02106814

	arm_func_start GXS_LoadOBJ
GXS_LoadOBJ: ; 0x020C9294
	stmdb sp!, {r4,lr}
	ldr r3, _020C92F0 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	mov r12, #0x6600000
	beq _020C92D8
	cmp r3, #0x30
	bls _020C92D8
	mov r1, r4
	add r2, r12, lr
	bl MI_DmaCopy32
	ldmia sp!, {r4,lr}
	bx lr
_020C92D8:
	mov r0, r4
	mov r2, r3
	add r1, r12, lr
	bl MIi_CpuCopy32
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C92F0: .word 0x02106814

	arm_func_start GX_LoadOBJ
GX_LoadOBJ: ; 0x020C92F4
	stmdb sp!, {r4,lr}
	ldr r3, _020C9350 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	mov r12, #0x6400000
	beq _020C9338
	cmp r3, #0x30
	bls _020C9338
	mov r1, r4
	add r2, r12, lr
	bl MI_DmaCopy32
	ldmia sp!, {r4,lr}
	bx lr
_020C9338:
	mov r0, r4
	mov r2, r3
	add r1, r12, lr
	bl MIi_CpuCopy32
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C9350: .word 0x02106814

	arm_func_start GXS_LoadOAM
GXS_LoadOAM: ; 0x020C9354
	stmdb sp!, {r4,lr}
	ldr r3, _020C93B4 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	beq _020C9398
	cmp r3, #0x30
	bls _020C9398
	ldr r2, _020C93B8 ; =0x07000400
	mov r1, r4
	add r2, lr, r2
	bl MI_DmaCopy32
	ldmia sp!, {r4,lr}
	bx lr
_020C9398:
	ldr r1, _020C93B8 ; =0x07000400
	mov r0, r4
	mov r2, r3
	add r1, lr, r1
	bl MIi_CpuCopy32
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C93B4: .word 0x02106814
_020C93B8: .word 0x07000400

	arm_func_start GX_LoadOAM
GX_LoadOAM: ; 0x020C93BC
	stmdb sp!, {r4,lr}
	ldr r3, _020C9414 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	beq _020C93FC
	cmp r3, #0x30
	bls _020C93FC
	mov r1, r4
	add r2, lr, #0x7000000
	bl MI_DmaCopy32
	ldmia sp!, {r4,lr}
	bx lr
_020C93FC:
	mov r0, r4
	mov r2, r3
	add r1, lr, #0x7000000
	bl MIi_CpuCopy32
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C9414: .word 0x02106814

	arm_func_start GXS_LoadOBJPltt
GXS_LoadOBJPltt: ; 0x020C9418
	stmdb sp!, {r4,lr}
	ldr r3, _020C9478 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	beq _020C945C
	cmp r3, #0x1c
	bls _020C945C
	ldr r2, _020C947C ; =0x05000600
	mov r1, r4
	add r2, lr, r2
	bl MI_DmaCopy16
	ldmia sp!, {r4,lr}
	bx lr
_020C945C:
	ldr r1, _020C947C ; =0x05000600
	mov r0, r4
	mov r2, r3
	add r1, lr, r1
	bl MIi_CpuCopy16
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C9478: .word 0x02106814
_020C947C: .word 0x05000600

	arm_func_start GX_LoadOBJPltt
GX_LoadOBJPltt: ; 0x020C9480
	stmdb sp!, {r4,lr}
	ldr r3, _020C94E0 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	beq _020C94C4
	cmp r3, #0x1c
	bls _020C94C4
	ldr r2, _020C94E4 ; =0x05000200
	mov r1, r4
	add r2, lr, r2
	bl MI_DmaCopy16
	ldmia sp!, {r4,lr}
	bx lr
_020C94C4:
	ldr r1, _020C94E4 ; =0x05000200
	mov r0, r4
	mov r2, r3
	add r1, lr, r1
	bl MIi_CpuCopy16
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C94E0: .word 0x02106814
_020C94E4: .word 0x05000200

	arm_func_start GXS_LoadBGPltt
GXS_LoadBGPltt: ; 0x020C94E8
	stmdb sp!, {r4,lr}
	ldr r3, _020C9548 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	beq _020C952C
	cmp r3, #0x1c
	bls _020C952C
	ldr r2, _020C954C ; =0x05000400
	mov r1, r4
	add r2, lr, r2
	bl MI_DmaCopy16
	ldmia sp!, {r4,lr}
	bx lr
_020C952C:
	ldr r1, _020C954C ; =0x05000400
	mov r0, r4
	mov r2, r3
	add r1, lr, r1
	bl MIi_CpuCopy16
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C9548: .word 0x02106814
_020C954C: .word 0x05000400

	arm_func_start GX_LoadBGPltt
GX_LoadBGPltt: ; 0x020C9550
	stmdb sp!, {r4,lr}
	ldr r3, _020C95A8 ; =0x02106814
	mov r4, r0
	ldr r0, [r3, #0x0]
	mvn r12, #0x0
	mov lr, r1
	mov r3, r2
	cmp r0, r12
	beq _020C9590
	cmp r3, #0x1c
	bls _020C9590
	mov r1, r4
	add r2, lr, #0x5000000
	bl MI_DmaCopy16
	ldmia sp!, {r4,lr}
	bx lr
_020C9590:
	mov r0, r4
	mov r2, r3
	add r1, lr, #0x5000000
	bl MIi_CpuCopy16
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C95A8: .word 0x02106814
