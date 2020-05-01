    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start MIi_CpuClear16
MIi_CpuClear16: ; 0x020CE1C8
	mov r3, #0x0
_020CE1CC:
	cmp r3, r2
	strlth r0, [r1, r3]
	addlt r3, r3, #0x2
	blt _020CE1CC
	bx lr

	arm_func_start MIi_CpuCopy16
MIi_CpuCopy16: ; 0x020CE1E0
	mov r12, #0x0
_020CE1E4:
	cmp r12, r2
	ldrlth r3, [r0, r12]
	strlth r3, [r1, r12]
	addlt r12, r12, #0x2
	blt _020CE1E4
	bx lr

	arm_func_start MIi_CpuClear32
MIi_CpuClear32: ; 0x020CE1FC
	add r12, r1, r2
_020CE200:
	cmp r1, r12
	stmltia r1!, {r0}
	blt _020CE200
	bx lr

	arm_func_start MIi_CpuCopy32
MIi_CpuCopy32: ; 0x020CE210
	add r12, r1, r2
_020CE214:
	cmp r1, r12
	ldmltia r0!, {r2}
	stmltia r1!, {r2}
	blt _020CE214
	bx lr

	arm_func_start MIi_CpuSend32
MIi_CpuSend32: ; 0x020CE228
	add r12, r0, r2
_020CE22C:
	cmp r0, r12
	ldmltia r0!, {r2}
	strlt r2, [r1, #0x0]
	blt _020CE22C
	bx lr

	arm_func_start MIi_CpuClearFast
MIi_CpuClearFast: ; 0x020CE240
	stmdb sp!, {r4-r9}
	add r9, r1, r2
	mov r12, r2, lsr #0x5
	add r12, r1, r12, lsl #0x5
	mov r2, r0
	mov r3, r2
	mov r4, r2
	mov r5, r2
	mov r6, r2
	mov r7, r2
	mov r8, r2
_020CE26C:
	cmp r1, r12
	stmltia r1!, {r0,r2-r8}
	blt _020CE26C
_020CE278:
	cmp r1, r9
	stmltia r1!, {r0}
	blt _020CE278
	ldmia sp!, {r4-r9}
	bx lr

	arm_func_start MIi_CpuCopyFast
MIi_CpuCopyFast: ; 0x020CE28C
	stmdb sp!, {r4-r10}
	add r10, r1, r2
	mov r12, r2, lsr #0x5
	add r12, r1, r12, lsl #0x5
_020CE29C:
	cmp r1, r12
	ldmltia r0!, {r2-r9}
	stmltia r1!, {r2-r9}
	blt _020CE29C
_020CE2AC:
	cmp r1, r10
	ldmltia r0!, {r2}
	stmltia r1!, {r2}
	blt _020CE2AC
	ldmia sp!, {r4-r10}
	bx lr

	arm_func_start MI_Copy16B
MI_Copy16B:
	ldmia r0!, {r2, r3, ip}
	stmia r1!, {r2, r3, ip}
	ldmia r0!, {r2, r3, ip}
	stmia r1!, {r2, r3, ip}
	ldmia r0!, {r2, r3}
	stmia r1!, {r2, r3}
	bx lr

	arm_func_start MI_Copy36B
MI_Copy36B: ; 0x020CE2E0
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	bx lr

	arm_func_start MI_Copy48B
MI_Copy48B: ; 0x020CE2FC
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	bx lr

	arm_func_start MI_Copy64B
MI_Copy64B: ; 0x020CE320
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0, {r0,r2-r3,r12}
	stmia r1!, {r0,r2-r3,r12}
	bx lr

	arm_func_start MI_CpuFill8
MI_CpuFill8: ; 0x020CE34C
	cmp r2, #0x0
	bxeq lr
	tst r0, #0x1
	beq _020CE378
	ldrh r12, [r0, #-0x1]
	and r12, r12, #0xff
	orr r3, r12, r1, lsl #0x8
	strh r3, [r0, #-0x1]
	add r0, r0, #0x1
	subs r2, r2, #0x1
	bxeq lr
_020CE378:
	cmp r2, #0x2
	blo _020CE3C0
	orr r1, r1, r1, lsl #0x8
	tst r0, #0x2
	beq _020CE398
	strh r1, [r0], #0x2
	subs r2, r2, #0x2
	bxeq lr
_020CE398:
	orr r1, r1, r1, lsl #0x10
	bics r3, r2, #0x3
	beq _020CE3B8
	sub r2, r2, r3
	add r12, r3, r0
_020CE3AC:
	str r1, [r0], #0x4
	cmp r0, r12
	blo _020CE3AC
_020CE3B8:
	tst r2, #0x2
	strneh r1, [r0], #0x2
_020CE3C0:
	tst r2, #0x1
	bxeq lr
	ldrh r3, [r0, #0x0]
	and r3, r3, #0xff00
	and r1, r1, #0xff
	orr r1, r1, r3
	strh r1, [r0, #0x0]
	bx lr

	arm_func_start MI_CpuCopy8
MI_CpuCopy8:
	cmp r2, #0x0
	bxeq lr
	tst r1, #0x1
	beq _020CE420
	ldrh r12, [r1, #-0x1]
	and r12, r12, #0xff
	tst r0, #0x1
	ldrneh r3, [r0, #-0x1]
	movne r3, r3, lsr #0x8
	ldreqh r3, [r0, #0x0]
	orr r3, r12, r3, lsl #0x8
	strh r3, [r1, #-0x1]
	add r0, r0, #0x1
	add r1, r1, #0x1
	subs r2, r2, #0x1
	bxeq lr
_020CE420:
	eor r12, r1, r0
	tst r12, #0x1
	beq _020CE474
	bic r0, r0, #0x1
	ldrh r12, [r0], #0x2
	mov r3, r12, lsr #0x8
	subs r2, r2, #0x2
	blo _020CE458
_020CE440:
	ldrh r12, [r0], #0x2
	orr r12, r3, r12, lsl #0x8
	strh r12, [r1], #0x2
	mov r3, r12, lsr #0x10
	subs r2, r2, #0x2
	bhs _020CE440
_020CE458:
	tst r2, #0x1
	bxeq lr
	ldrh r12, [r1, #0x0]
	and r12, r12, #0xff00
	orr r12, r12, r3
	strh r12, [r1, #0x0]
	bx lr
_020CE474:
	tst r12, #0x2
	beq _020CE4A0
	bics r3, r2, #0x1
	beq _020CE4EC
	sub r2, r2, r3
	add r12, r3, r1
_020CE48C:
	ldrh r3, [r0], #0x2
	strh r3, [r1], #0x2
	cmp r1, r12
	blo _020CE48C
	b _020CE4EC
_020CE4A0:
	cmp r2, #0x2
	blo _020CE4EC
	tst r1, #0x2
	beq _020CE4C0
	ldrh r3, [r0], #0x2
	strh r3, [r1], #0x2
	subs r2, r2, #0x2
	bxeq lr
_020CE4C0:
	bics r3, r2, #0x3
	beq _020CE4E0
	sub r2, r2, r3
	add r12, r3, r1
_020CE4D0:
	ldr r3, [r0], #0x4
	str r3, [r1], #0x4
	cmp r1, r12
	blo _020CE4D0
_020CE4E0:
	tst r2, #0x2
	ldrneh r3, [r0], #0x2
	strneh r3, [r1], #0x2
_020CE4EC:
	tst r2, #0x1
	bxeq lr
	ldrh r2, [r1, #0x0]
	ldrh r0, [r0, #0x0]
	and r2, r2, #0xff00
	and r0, r0, #0xff
	orr r0, r2, r0
	strh r0, [r1, #0x0]
	bx lr

	thumb_func_start MI_Zero36B
MI_Zero36B: ; 0x020CE510
	mov r1, #0x0
	mov r2, #0x0
	mov r3, #0x0
	stmia r0!, {r1-r3}
	stmia r0!, {r1-r3}
	stmia r0!, {r1-r3}
	bx lr
