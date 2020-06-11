#todo identify and split
	.include "asm/macros.inc"
	.include "global.inc"

    .section .bss

	.global _03807F4C
_03807F4C: ;0x03807F4C
	.space 0x03807F50 - 0x03807F4C

	.global _03807F50
_03807F50: ;0x03807F50
	.space 0x03807F58 - 0x03807F50

	.global _03807F58
_03807F58: ;0x03807F58
	.space 0x03807F68 - 0x03807F58

	.global SNDi_SharedWork
SNDi_SharedWork: ;0x03807F68
	.space 0x03807F6C - 0x03807F68

    .section .text

	arm_func_start FUN_037FD440
FUN_037FD440: ; 0x037FD440
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	cmp	r2, #3
	addls	pc, pc, r2, lsl #2
	b	_037FD4B8
	b	_037FD464
	b	_037FD474
	b	_037FD484
	b	_037FD49C
_037FD464:
	ldrb	r0, [r4]
	bic	r0, r0, #4
	strb	r0, [r4]
	b	_037FD4B8
_037FD474:
	ldrb	r0, [r4]
	orr	r0, r0, #4
	strb	r0, [r4]
	b	_037FD4B8
_037FD484:
	ldrb	r2, [r4]
	orr	r2, r2, #4
	strb	r2, [r4]
	mvn	r2, #0
	bl	FUN_037FE588
	b	_037FD4B8
_037FD49C:
	ldrb	r2, [r4]
	orr	r2, r2, #4
	strb	r2, [r4]
	mov	r2, #127	; 0x7f
	bl	FUN_037FE588
	mov	r0, r4
	bl	FUN_037FE54C
_037FD4B8:
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start FUN_037FD4C0
FUN_037FD4C0: ; 0x037FD4C0
	mov	r0, #0
	ldr	r3, _037FD500	; =_038086EC
	b	_037FD4F0
_037FD4CC:
	add	ip, r3, r0, lsl #6
	ldrb	r1, [r3, r0, lsl #6]
	mov	r2, r1, lsl #31
	movs	r2, r2, lsr #31
	biceq	r1, r1, #1
	orreq	r1, r1, #1
	streqb	r1, [ip]
	bxeq	lr
	add	r0, r0, #1
_037FD4F0:
	cmp	r0, #32
	blt	_037FD4CC
	mvn	r0, #0
	bx	lr
_037FD500:	.word	_038086EC

	arm_func_start FUN_037FD504
FUN_037FD504: ; 0x037FD504
	ldr	r2, _037FD544	; =SNDi_SharedWork
	ldr	r2, [r2]
	cmp	r2, #0
	moveq	r0, #0
	bxeq	lr
	cmp	r1, #16
	addge	r2, r2, #608	; 0x260
	subge	r0, r1, #16
	addge	r0, r2, r0, lsl #1
	bxge	lr
	add	r3, r2, #32
	ldrb	r2, [r0, #1]
	mov	r0, #36	; 0x24
	mla	r0, r2, r0, r3
	add	r0, r0, r1, lsl #1
	bx	lr
_037FD544:	.word	SNDi_SharedWork

	arm_func_start FUN_037FD548
FUN_037FD548: ; 0x037FD548
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r8, r0
	mov	r7, r1
	mov	r6, #0
	mov	r5, r6
	mov	r4, #1
_037FD560:
	mov	r0, r8
	mov	r1, r5
	bl	FUN_037FE460
	cmp	r0, #0
	beq	_037FD5A8
	ldr	r1, [r0, #40]	; 0x28
	cmp	r1, #0
	beq	_037FD5A8
	mov	r1, r8
	mov	r2, r5
	mov	r3, r7
	bl	FUN_037FD5C8
	cmp	r0, #0
	moveq	r6, r4
	beq	_037FD5A8
	mov	r0, r8
	mov	r1, r5
	bl	FUN_037FE3EC
_037FD5A8:
	add	r5, r5, #1
	cmp	r5, #16
	blt	_037FD560
	cmp	r6, #0
	moveq	r0, #1
	movne	r0, #0
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr

	arm_func_start FUN_037FD5C8
FUN_037FD5C8: ; 0x037FD5C8
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #52	; 0x34
	mov	r9, r0
	mov	r8, r1
	str	r3, [sp, #4]
	ldr	r2, [r9, #60]	; 0x3c
	b	_037FD61C
_037FD5E4:
	ldr	r0, [r2, #52]	; 0x34
	cmp	r0, #0
	subgt	r0, r0, #1
	strgt	r0, [r2, #52]	; 0x34
	ldrb	r0, [r2, #3]
	mov	r0, r0, lsl #29
	movs	r0, r0, lsr #31
	bne	_037FD618
	ldr	r1, [r2, #20]
	ldr	r0, [r2, #24]
	cmp	r1, r0
	addlt	r0, r1, #1
	strlt	r0, [r2, #20]
_037FD618:
	ldr	r2, [r2, #80]	; 0x50
_037FD61C:
	cmp	r2, #0
	bne	_037FD5E4
	ldrb	r1, [r9]
	mov	r0, r1, lsl #27
	movs	r0, r0, lsr #31
	beq	_037FD64C
	ldr	r0, [r9, #60]	; 0x3c
	cmp	r0, #0
	movne	r0, #0
	bne	_037FDF84
	bic	r0, r1, #16
	strb	r0, [r9]
_037FD64C:
	ldr	r0, [r9, #32]
	cmp	r0, #0
	ble	_037FD670
	sub	r0, r0, #1
	str	r0, [r9, #32]
	ldr	r0, [r9, #32]
	cmp	r0, #0
	movgt	r0, #0
	bgt	_037FDF84
_037FD670:
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE9B8
	add	r0, r9, #40	; 0x28
	str	r0, [sp, #28]
	mov	r0, #2
	str	r0, [sp, #32]
	mov	r0, #127	; 0x7f
	str	r0, [sp, #36]	; 0x24
	mov	fp, #0
	mvn	r0, #0
	str	r0, [sp, #40]	; 0x28
	mov	sl, #1
	mov	r0, #3
	str	r0, [sp, #20]
	mov	r0, #4
	str	r0, [sp, #24]
	b	_037FDF64
_037FD6B4:
	mov	r4, fp
	mov	r6, sl
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE968
	mov	r7, r0
	ldr	r0, [r9, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r9, #40]	; 0x28
	cmp	r7, #162	; 0xa2
	bne	_037FD700
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE968
	mov	r7, r0
	ldr	r0, [r9, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r9, #40]	; 0x28
	ldrb	r0, [r9]
	mov	r0, r0, lsl #25
	mov	r6, r0, lsr #31
_037FD700:
	cmp	r7, #160	; 0xa0
	bne	_037FD72C
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE968
	mov	r7, r0
	ldr	r0, [r9, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r9, #40]	; 0x28
	ldr	r0, [sp, #20]
	str	r0, [sp, #8]
	mov	r4, sl
_037FD72C:
	cmp	r7, #161	; 0xa1
	bne	_037FD758
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE968
	mov	r7, r0
	ldr	r0, [r9, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r9, #40]	; 0x28
	ldr	r0, [sp, #24]
	str	r0, [sp, #8]
	mov	r4, sl
_037FD758:
	ands	r0, r7, #128	; 0x80
	bne	_037FD82C
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE968
	str	r0, [sp, #12]
	ldr	r0, [sp, #28]
	ldr	r0, [r0]
	add	r1, r0, #1
	ldr	r0, [sp, #28]
	str	r1, [r0]
	cmp	r4, #0
	ldrne	r2, [sp, #8]
	ldreq	r2, [sp, #32]
	mov	r0, r9
	mov	r1, r8
	bl	FUN_037FE7B0
	mov	r5, r0
	ldrsb	r0, [r9, #19]
	add	r4, r7, r0
	cmp	r6, #0
	beq	_037FDF64
	cmp	r4, #0
	movlt	r4, fp
	blt	_037FD7C0
	cmp	r4, #127	; 0x7f
	ldrgt	r4, [sp, #36]	; 0x24
_037FD7C0:
	ldrb	r0, [r9]
	mov	r0, r0, lsl #29
	movs	r0, r0, lsr #31
	bne	_037FD800
	ldr	r0, [sp, #4]
	cmp	r0, #0
	beq	_037FD800
	cmp	r5, #0
	movgt	r0, r5
	ldrle	r0, [sp, #40]	; 0x28
	str	r0, [sp]
	mov	r0, r9
	mov	r1, r8
	mov	r2, r4
	ldr	r3, [sp, #12]
	bl	FUN_037FDF94
_037FD800:
	strb	r4, [r9, #20]
	ldrb	r0, [r9]
	mov	r0, r0, lsl #30
	movs	r0, r0, lsr #31
	beq	_037FDF64
	str	r5, [r9, #32]
	cmp	r5, #0
	ldreqb	r0, [r9]
	orreq	r0, r0, #16
	streqb	r0, [r9]
	b	_037FDF64
_037FD82C:
	and	r0, r7, #240	; 0xf0
	cmp	r0, #192	; 0xc0
	bgt	_037FD868
	cmp	r0, #192	; 0xc0
	bge	_037FD9B8
	cmp	r0, #144	; 0x90
	bgt	_037FD85C
	cmp	r0, #144	; 0x90
	bge	_037FD8D8
	cmp	r0, #128	; 0x80
	beq	_037FD890
	b	_037FDF64
_037FD85C:
	cmp	r0, #176	; 0xb0
	beq	_037FDC68
	b	_037FDF64
_037FD868:
	cmp	r0, #224	; 0xe0
	bgt	_037FD884
	cmp	r0, #224	; 0xe0
	bge	_037FDC14
	cmp	r0, #208	; 0xd0
	beq	_037FD9B8
	b	_037FDF64
_037FD884:
	cmp	r0, #240	; 0xf0
	beq	_037FDEC0
	b	_037FDF64
_037FD890:
	cmp	r4, #0
	ldrne	r2, [sp, #8]
	ldreq	r2, [sp, #32]
	mov	r0, r9
	mov	r1, r8
	bl	FUN_037FE7B0
	cmp	r6, #0
	beq	_037FDF64
	cmp	r7, #128	; 0x80
	beq	_037FD8C4
	cmp	r7, #129	; 0x81
	beq	_037FD8CC
	b	_037FDF64
_037FD8C4:
	str	r0, [r9, #32]
	b	_037FDF64
_037FD8CC:
	cmp	r0, #65536	; 0x10000
	strlth	r0, [r9, #2]
	b	_037FDF64
_037FD8D8:
	cmp	r7, #147	; 0x93
	beq	_037FD8F4
	cmp	r7, #148	; 0x94
	beq	_037FD958
	cmp	r7, #149	; 0x95
	beq	_037FD974
	b	_037FDF64
_037FD8F4:
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE968
	mov	r4, r0
	ldr	r0, [r9, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r9, #40]	; 0x28
	mov	r0, r9
	bl	FUN_037FE8B8
	mov	r5, r0
	cmp	r6, #0
	beq	_037FDF64
	mov	r0, r8
	mov	r1, r4
	bl	FUN_037FE460
	movs	r4, r0
	beq	_037FDF64
	cmp	r4, r9
	beq	_037FDF64
	mov	r1, r8
	bl	FUN_037FE440
	mov	r0, r4
	ldr	r1, [r9, #36]	; 0x24
	mov	r2, r5
	bl	FUN_037FE6A8
	b	_037FDF64
_037FD958:
	mov	r0, r9
	bl	FUN_037FE8B8
	cmp	r6, #0
	ldrne	r1, [r9, #36]	; 0x24
	addne	r0, r1, r0
	strne	r0, [r9, #40]	; 0x28
	b	_037FDF64
_037FD974:
	mov	r0, r9
	bl	FUN_037FE8B8
	cmp	r6, #0
	beq	_037FDF64
	ldrb	r1, [r9, #59]	; 0x3b
	cmp	r1, #3
	bcs	_037FDF64
	ldr	r2, [r9, #40]	; 0x28
	add	r1, r9, r1, lsl #2
	str	r2, [r1, #44]	; 0x2c
	ldrb	r1, [r9, #59]	; 0x3b
	add	r1, r1, #1
	strb	r1, [r9, #59]	; 0x3b
	ldr	r1, [r9, #36]	; 0x24
	add	r0, r1, r0
	str	r0, [r9, #40]	; 0x28
	b	_037FDF64
_037FD9B8:
	cmp	r4, #0
	ldrne	r2, [sp, #8]
	moveq	r2, fp
	mov	r0, r9
	mov	r1, r8
	bl	FUN_037FE7B0
	strb	r0, [sp, #44]	; 0x2c
	cmp	r6, #0
	beq	_037FDF64
	sub	r0, r7, #192	; 0xc0
	cmp	r0, #23
	addls	pc, pc, r0, lsl #2
	b	_037FDF64
	b	_037FDBE4
	b	_037FDA4C
	b	_037FDA64
	b	_037FDBCC
	b	_037FDBD8
	b	_037FDA70
	b	_037FDA7C
	b	_037FDA88
	b	_037FDB48
	b	_037FDB90
	b	_037FDAB0
	b	_037FDABC
	b	_037FDAC8
	b	_037FDAD4
	b	_037FDBB0
	b	_037FDAA4
	b	_037FDAE0
	b	_037FDAEC
	b	_037FDAF8
	b	_037FDB04
	b	_037FDB10
	b	_037FDA58
	b	_037FDBF4
	b	_037FDB7C
_037FDA4C:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #4]
	b	_037FDF64
_037FDA58:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #5]
	b	_037FDF64
_037FDA64:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r8, #5]
	b	_037FDF64
_037FDA70:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #7]
	b	_037FDF64
_037FDA7C:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #18]
	b	_037FDF64
_037FDA88:
	ldrb	r0, [r9]
	bic	r1, r0, #2
	ldrb	r0, [sp, #44]	; 0x2c
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #1
	strb	r0, [r9]
	b	_037FDF64
_037FDAA4:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #21]
	b	_037FDF64
_037FDAB0:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #26]
	b	_037FDF64
_037FDABC:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #25]
	b	_037FDF64
_037FDAC8:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #24]
	b	_037FDF64
_037FDAD4:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #27]
	b	_037FDF64
_037FDAE0:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #14]
	b	_037FDF64
_037FDAEC:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #15]
	b	_037FDF64
_037FDAF8:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #16]
	b	_037FDF64
_037FDB04:
	ldrb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #17]
	b	_037FDF64
_037FDB10:
	ldrb	r0, [r9, #59]	; 0x3b
	cmp	r0, #3
	bcs	_037FDF64
	ldr	r1, [r9, #40]	; 0x28
	add	r0, r9, r0, lsl #2
	str	r1, [r0, #44]	; 0x2c
	ldrb	r1, [sp, #44]	; 0x2c
	ldrb	r0, [r9, #59]	; 0x3b
	add	r0, r9, r0
	strb	r1, [r0, #56]	; 0x38
	ldrb	r0, [r9, #59]	; 0x3b
	add	r0, r0, #1
	strb	r0, [r9, #59]	; 0x3b
	b	_037FDF64
_037FDB48:
	ldrb	r0, [r9]
	bic	r1, r0, #8
	ldrb	r0, [sp, #44]	; 0x2c
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #3
	strb	r0, [r9]
	mov	r0, r9
	mov	r1, r8
	ldr	r2, [sp, #40]	; 0x28
	bl	FUN_037FE588
	mov	r0, r9
	bl	FUN_037FE54C
	b	_037FDF64
_037FDB7C:
	mov	r0, r9
	mov	r1, r8
	ldrb	r2, [sp, #44]	; 0x2c
	bl	FUN_037FD440
	b	_037FDF64
_037FDB90:
	ldrb	r1, [sp, #44]	; 0x2c
	ldrsb	r0, [r9, #19]
	add	r0, r1, r0
	strb	r0, [r9, #20]
	ldrb	r0, [r9]
	orr	r0, r0, #32
	strb	r0, [r9]
	b	_037FDF64
_037FDBB0:
	ldrb	r0, [r9]
	bic	r1, r0, #32
	ldrb	r0, [sp, #44]	; 0x2c
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #5
	strb	r0, [r9]
	b	_037FDF64
_037FDBCC:
	ldrsb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #19]
	b	_037FDF64
_037FDBD8:
	ldrsb	r0, [sp, #44]	; 0x2c
	strb	r0, [r9, #6]
	b	_037FDF64
_037FDBE4:
	ldrb	r0, [sp, #44]	; 0x2c
	sub	r0, r0, #64	; 0x40
	strb	r0, [r9, #8]
	b	_037FDF64
_037FDBF4:
	ldr	r0, _037FDF90	; =_03807F4C
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_037FDF64
	mov	r0, r8
	ldrb	r1, [sp, #44]	; 0x2c
	bl	FUN_037FD504
	b	_037FDF64
_037FDC14:
	cmp	r4, #0
	ldrne	r2, [sp, #8]
	moveq	r2, sl
	mov	r0, r9
	mov	r1, r8
	bl	FUN_037FE7B0
	mov	r0, r0, lsl #16
	mov	r0, r0, asr #16
	cmp	r6, #0
	beq	_037FDF64
	cmp	r7, #224	; 0xe0
	beq	_037FDC60
	cmp	r7, #225	; 0xe1
	beq	_037FDC58
	cmp	r7, #227	; 0xe3
	streqh	r0, [r9, #22]
	b	_037FDF64
_037FDC58:
	strh	r0, [r8, #24]
	b	_037FDF64
_037FDC60:
	strh	r0, [r9, #28]
	b	_037FDF64
_037FDC68:
	ldr	r0, [r9, #40]	; 0x28
	bl	FUN_037FE968
	str	r0, [sp, #16]
	ldr	r0, [r9, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r9, #40]	; 0x28
	cmp	r4, #0
	ldrne	r2, [sp, #8]
	moveq	r2, sl
	mov	r0, r9
	mov	r1, r8
	bl	FUN_037FE7B0
	mov	r0, r0, lsl #16
	mov	r5, r0, asr #16
	mov	r0, r8
	ldr	r1, [sp, #16]
	bl	FUN_037FD504
	mov	r4, r0
	cmp	r6, #0
	beq	_037FDF64
	cmp	r4, #0
	beq	_037FDF64
	sub	r0, r7, #176	; 0xb0
	cmp	r0, #13
	addls	pc, pc, r0, lsl #2
	b	_037FDF64
	b	_037FDD08
	b	_037FDD10
	b	_037FDD20
	b	_037FDD30
	b	_037FDD40
	b	_037FDD5C
	b	_037FDD80
	b	_037FDF64
	b	_037FDDB8
	b	_037FDDE4
	b	_037FDE10
	b	_037FDE3C
	b	_037FDE68
	b	_037FDE94
_037FDD08:
	strh	r5, [r4]
	b	_037FDF64
_037FDD10:
	ldrsh	r0, [r4]
	add	r0, r0, r5
	strh	r0, [r4]
	b	_037FDF64
_037FDD20:
	ldrsh	r0, [r4]
	sub	r0, r0, r5
	strh	r0, [r4]
	b	_037FDF64
_037FDD30:
	ldrsh	r0, [r4]
	mul	r1, r0, r5
	strh	r1, [r4]
	b	_037FDF64
_037FDD40:
	cmp	r5, #0
	beq	_037FDF64
	ldrsh	r0, [r4]
	mov	r1, r5
	bl	_s32_div_f
	strh	r0, [r4]
	b	_037FDF64
_037FDD5C:
	cmp	r5, #0
	ldrgesh	r0, [r4]
	movge	r0, r0, lsl r5
	strgeh	r0, [r4]
	ldrltsh	r1, [r4]
	rsblt	r0, r5, #0
	movlt	r0, r1, asr r0
	strlth	r0, [r4]
	b	_037FDF64
_037FDD80:
	mov	r6, fp
	cmp	r5, #0
	movlt	r6, sl
	rsblt	r0, r5, #0
	movlt	r0, r0, lsl #16
	movlt	r5, r0, asr #16
	bl	SND_CalcRandom
	add	r1, r5, #1
	mul	r1, r0, r1
	mov	r0, r1, asr #16
	cmp	r6, #0
	rsbne	r0, r0, #0
	strh	r0, [r4]
	b	_037FDF64
_037FDDB8:
	ldrsh	r0, [r4]
	cmp	r0, r5
	moveq	r2, sl
	movne	r2, fp
	ldrb	r0, [r9]
	bic	r1, r0, #64	; 0x40
	and	r0, r2, #255	; 0xff
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #6
	strb	r0, [r9]
	b	_037FDF64
_037FDDE4:
	ldrsh	r0, [r4]
	cmp	r0, r5
	movge	r2, sl
	movlt	r2, fp
	ldrb	r0, [r9]
	bic	r1, r0, #64	; 0x40
	and	r0, r2, #255	; 0xff
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #6
	strb	r0, [r9]
	b	_037FDF64
_037FDE10:
	ldrsh	r0, [r4]
	cmp	r0, r5
	movgt	r2, sl
	movle	r2, fp
	ldrb	r0, [r9]
	bic	r1, r0, #64	; 0x40
	and	r0, r2, #255	; 0xff
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #6
	strb	r0, [r9]
	b	_037FDF64
_037FDE3C:
	ldrsh	r0, [r4]
	cmp	r0, r5
	movle	r2, sl
	movgt	r2, fp
	ldrb	r0, [r9]
	bic	r1, r0, #64	; 0x40
	and	r0, r2, #255	; 0xff
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #6
	strb	r0, [r9]
	b	_037FDF64
_037FDE68:
	ldrsh	r0, [r4]
	cmp	r0, r5
	movlt	r2, sl
	movge	r2, fp
	ldrb	r0, [r9]
	bic	r1, r0, #64	; 0x40
	and	r0, r2, #255	; 0xff
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #6
	strb	r0, [r9]
	b	_037FDF64
_037FDE94:
	ldrsh	r0, [r4]
	cmp	r0, r5
	movne	r2, sl
	moveq	r2, fp
	ldrb	r0, [r9]
	bic	r1, r0, #64	; 0x40
	and	r0, r2, #255	; 0xff
	and	r0, r0, #1
	orr	r0, r1, r0, lsl #6
	strb	r0, [r9]
	b	_037FDF64
_037FDEC0:
	cmp	r6, #0
	beq	_037FDF64
	sub	r0, r7, #252	; 0xfc
	cmp	r0, #3
	addls	pc, pc, r0, lsl #2
	b	_037FDF64
	b	_037FDF10
	b	_037FDEE8
	b	_037FDF64
	b	_037FDF5C
_037FDEE8:
	ldrb	r0, [r9, #59]	; 0x3b
	cmp	r0, #0
	beq	_037FDF64
	sub	r0, r0, #1
	strb	r0, [r9, #59]	; 0x3b
	ldrb	r0, [r9, #59]	; 0x3b
	add	r0, r9, r0, lsl #2
	ldr	r0, [r0, #44]	; 0x2c
	str	r0, [r9, #40]	; 0x28
	b	_037FDF64
_037FDF10:
	ldrb	r0, [r9, #59]	; 0x3b
	cmp	r0, #0
	beq	_037FDF64
	sub	r1, r0, #1
	add	r2, r9, r1
	ldrb	r0, [r2, #56]	; 0x38
	cmp	r0, #0
	beq	_037FDF40
	sub	r0, r0, #1
	ands	r0, r0, #255	; 0xff
	streqb	r1, [r9, #59]	; 0x3b
	beq	_037FDF64
_037FDF40:
	strb	r0, [r2, #56]	; 0x38
	ldrb	r0, [r9, #59]	; 0x3b
	sub	r0, r0, #1
	add	r0, r9, r0, lsl #2
	ldr	r0, [r0, #44]	; 0x2c
	str	r0, [r9, #40]	; 0x28
	b	_037FDF64
_037FDF5C:
	mvn	r0, #0
	b	_037FDF84
_037FDF64:
	ldr	r0, [r9, #32]
	cmp	r0, #0
	bne	_037FDF80
	ldrb	r0, [r9]
	mov	r0, r0, lsl #27
	movs	r0, r0, lsr #31
	beq	_037FD6B4
_037FDF80:
	mov	r0, #0
_037FDF84:
	add	sp, sp, #52	; 0x34
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FDF90:	.word	_03807F4C

	arm_func_start FUN_037FDF94
FUN_037FDF94: ; 0x037FDF94
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	sub	sp, sp, #24
	mov	r8, r0
	mov	r7, r1
	mov	r6, r2
	mov	r5, r3
	mov	r4, #0
	ldrb	r0, [r8]
	mov	r0, r0, lsl #28
	movs	r0, r0, lsr #31
	beq	_037FDFD0
	ldr	r4, [r8, #60]	; 0x3c
	cmp	r4, #0
	strneb	r6, [r4, #8]
	strneb	r5, [r4, #9]
_037FDFD0:
	cmp	r4, #0
	bne	_037FE0C4
	ldr	r0, [r7, #32]
	ldrh	r1, [r8, #2]
	mov	r2, r6
	add	r3, sp, #8
	bl	SND_ReadInstData
	cmp	r0, #0
	beq	_037FE18C
	ldrb	r0, [sp, #8]
	cmp	r0, #4
	addls	pc, pc, r0, lsl #2
	b	_037FE030
	b	_037FE030
	b	_037FE018
	b	_037FE020
	b	_037FE028
	b	_037FE018
_037FE018:
	ldr	r1, _037FE198	; =0x0000FFFF
	b	_037FE034
_037FE020:
	mov	r1, #16128	; 0x3f00
	b	_037FE034
_037FE028:
	mov	r1, #49152	; 0xc000
	b	_037FE034
_037FE030:
	b	_037FE18C
_037FE034:
	ldrh	r0, [r8, #30]
	and	r0, r1, r0
	str	r8, [sp]
	ldrb	r2, [r7, #4]
	ldrb	r1, [r8, #18]
	add	r1, r2, r1
	ldrb	r2, [r8]
	mov	r2, r2, lsl #24
	mov	r2, r2, lsr #31
	ldr	r3, _037FE19C	; =FUN_037FE344
	bl	SND_AllocExChannel
	movs	r4, r0
	beq	_037FE18C
	ldrb	r0, [r8]
	mov	r0, r0, lsl #28
	movs	r0, r0, lsr #31
	mvnne	r3, #0
	ldreq	r3, [sp, #48]	; 0x30
	ldr	r0, [r7, #32]
	str	r0, [sp]
	add	r0, sp, #8
	str	r0, [sp, #4]
	mov	r0, r4
	mov	r1, r6
	mov	r2, r5
	bl	SND_NoteOn
	cmp	r0, #0
	bne	_037FE0B8
	mov	r0, #0
	strb	r0, [r4, #34]	; 0x22
	mov	r0, r4
	bl	SND_FreeExChannel
	b	_037FE18C
_037FE0B8:
	ldr	r0, [r8, #60]	; 0x3c
	str	r0, [r4, #80]	; 0x50
	str	r4, [r8, #60]	; 0x3c
_037FE0C4:
	ldrb	r1, [r8, #14]
	cmp	r1, #255	; 0xff
	beq	_037FE0D8
	mov	r0, r4
	bl	SND_SetExChannelAttack
_037FE0D8:
	ldrb	r1, [r8, #15]
	cmp	r1, #255	; 0xff
	beq	_037FE0EC
	mov	r0, r4
	bl	SND_SetExChannelDecay
_037FE0EC:
	ldrb	r1, [r8, #16]
	cmp	r1, #255	; 0xff
	beq	_037FE100
	mov	r0, r4
	bl	SND_SetExChannelSustain
_037FE100:
	ldrb	r1, [r8, #17]
	cmp	r1, #255	; 0xff
	beq	_037FE114
	mov	r0, r4
	bl	SND_SetExChannelRelease
_037FE114:
	ldrsh	r0, [r8, #22]
	strh	r0, [r4, #50]	; 0x32
	ldrb	r0, [r8]
	mov	r0, r0, lsl #26
	movs	r0, r0, lsr #31
	beq	_037FE144
	ldrsh	r1, [r4, #50]	; 0x32
	ldrb	r0, [r8, #20]
	sub	r0, r0, r6
	mov	r0, r0, lsl #22
	add	r0, r1, r0, asr #16
	strh	r0, [r4, #50]	; 0x32
_037FE144:
	ldrb	r0, [r8, #21]
	cmp	r0, #0
	bne	_037FE168
	ldr	r0, [sp, #48]	; 0x30
	str	r0, [r4, #24]
	ldrb	r0, [r4, #3]
	bic	r0, r0, #4
	strb	r0, [r4, #3]
	b	_037FE184
_037FE168:
	mul	r1, r0, r0
	ldrsh	r0, [r4, #50]	; 0x32
	cmp	r0, #0
	rsblt	r0, r0, #0
	mul	r0, r1, r0
	mov	r0, r0, asr #11
	str	r0, [r4, #24]
_037FE184:
	mov	r0, #0
	str	r0, [r4, #20]
_037FE18C:
	add	sp, sp, #24
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_037FE198:	.word	0x0000FFFF
_037FE19C:	.word	FUN_037FE344

	arm_func_start FUN_037FE1A0
FUN_037FE1A0: ; 0x037FE1A0
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, #0
	mov	r4, #1
_037FE1B0:
	mov	r0, r6
	mov	r1, r5
	bl	FUN_037FE460
	cmp	r0, #0
	beq	_037FE1D0
	mov	r1, r6
	mov	r2, r4
	bl	FUN_037FE1E4
_037FE1D0:
	add	r5, r5, #1
	cmp	r5, #16
	blt	_037FE1B0
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start FUN_037FE1E4
FUN_037FE1E4: ; 0x037FE1E4
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	mov	sl, r0
	mov	fp, r2
	ldrb	r0, [r1, #5]
	mov	r0, r0, lsl #1
	ldr	r4, _037FE340	; =SNDi_DecibelSquareTable
	ldrsh	r3, [r4, r0]
	ldrb	r0, [sl, #4]
	mov	r0, r0, lsl #1
	ldrsh	r2, [r4, r0]
	ldrb	r0, [sl, #5]
	mov	r0, r0, lsl #1
	ldrsh	r0, [r4, r0]
	add	r0, r2, r0
	add	r3, r3, r0
	ldrsh	r2, [sl, #10]
	ldrsh	r0, [r1, #6]
	add	r2, r2, r0
	ldrsb	r4, [sl, #6]
	ldrb	r0, [sl, #7]
	mov	r0, r0, lsl #6
	mul	r1, r4, r0
	ldrsh	r0, [sl, #12]
	add	r0, r0, r1, asr #7
	ldrsb	r1, [sl, #8]
	ldrb	r4, [sl, #1]
	cmp	r4, #127	; 0x7f
	mulne	r4, r1, r4
	addne	r1, r4, #64	; 0x40
	movne	r1, r1, asr #7
	ldrsb	r4, [sl, #9]
	add	r1, r1, r4
	mov	r4, #32768	; 0x8000
	rsb	r4, r4, #0
	cmp	r3, r4
	movlt	r3, r4
	mov	r4, #32768	; 0x8000
	rsb	r4, r4, #0
	cmp	r2, r4
	movlt	r2, r4
	mvn	r4, #127	; 0x7f
	cmp	r1, r4
	movlt	r1, r4
	blt	_037FE2A0
	cmp	r1, #127	; 0x7f
	movgt	r1, #127	; 0x7f
_037FE2A0:
	ldr	r9, [sl, #60]	; 0x3c
	mov	r4, #1
	mov	r3, r3, lsl #16
	mov	r7, r3, asr #16
	mov	r0, r0, lsl #16
	mov	r6, r0, asr #16
	mov	r0, r1, lsl #24
	mov	r5, r0, asr #24
	mov	r0, r2, lsl #16
	mov	r8, r0, asr #16
	b	_037FE32C
_037FE2CC:
	strh	r8, [r9, #6]
	ldrb	r0, [r9, #2]
	cmp	r0, #3
	beq	_037FE328
	strh	r7, [r9, #12]
	strh	r6, [r9, #14]
	strb	r5, [r9, #11]
	ldrb	r0, [sl, #1]
	strb	r0, [r9, #4]
	ldrh	r0, [sl, #24]
	strh	r0, [r9, #40]	; 0x28
	ldrh	r0, [sl, #26]
	strh	r0, [r9, #42]	; 0x2a
	ldrh	r0, [sl, #28]
	strh	r0, [r9, #44]	; 0x2c
	ldr	r0, [r9, #52]	; 0x34
	cmp	r0, #0
	bne	_037FE328
	cmp	fp, #0
	beq	_037FE328
	strb	r4, [r9, #34]	; 0x22
	mov	r0, r9
	bl	SND_ReleaseExChannel
_037FE328:
	ldr	r9, [r9, #80]	; 0x50
_037FE32C:
	cmp	r9, #0
	bne	_037FE2CC
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_037FE340:	.word	SNDi_DecibelSquareTable

	arm_func_start FUN_037FE344
FUN_037FE344: ; 0x037FE344
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, r2
	cmp	r1, #1
	bne	_037FE368
	mov	r1, #0
	strb	r1, [r5, #34]	; 0x22
	bl	SND_FreeExChannel
_037FE368:
	ldr	r1, [r4, #60]	; 0x3c
	cmp	r1, r5
	ldreq	r0, [r5, #80]	; 0x50
	streq	r0, [r4, #60]	; 0x3c
	beq	_037FE3A0
	b	_037FE394
_037FE380:
	cmp	r0, r5
	ldreq	r0, [r5, #80]	; 0x50
	streq	r0, [r1, #80]	; 0x50
	beq	_037FE3A0
	mov	r1, r0
_037FE394:
	ldr	r0, [r1, #80]	; 0x50
	cmp	r0, #0
	bne	_037FE380
_037FE3A0:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start FUN_037FE3AC
FUN_037FE3AC: ; 0x037FE3AC
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, #0
_037FE3BC:
	mov	r0, r5
	mov	r1, r4
	bl	FUN_037FE3EC
	add	r4, r4, #1
	cmp	r4, #16
	blt	_037FE3BC
	ldrb	r0, [r5]
	bic	r0, r0, #1
	strb	r0, [r5]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start FUN_037FE3EC
FUN_037FE3EC: ; 0x037FE3EC
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, r1
	bl	FUN_037FE460
	cmp	r0, #0
	beq	_037FE430
	mov	r1, r5
	bl	FUN_037FE440
	add	r3, r5, #8
	ldr	r2, _037FE43C	; =_038086EC
	ldrb	r1, [r3, r4]
	ldrb	r0, [r2, r1, lsl #6]
	bic	r0, r0, #1
	strb	r0, [r2, r1, lsl #6]
	mov	r0, #255	; 0xff
	strb	r0, [r3, r4]
_037FE430:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_037FE43C:	.word	_038086EC

	arm_func_start FUN_037FE440
FUN_037FE440: ; 0x037FE440
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mvn	r2, #0
	bl	FUN_037FE588
	mov	r0, r4
	bl	FUN_037FE54C
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start FUN_037FE460
FUN_037FE460: ; 0x037FE460
	cmp	r1, #15
	movgt	r0, #0
	bxgt	lr
	add	r0, r0, r1
	ldrb	r1, [r0, #8]
	cmp	r1, #255	; 0xff
	moveq	r0, #0
	ldrne	r0, _037FE488	; =_038086EC
	addne	r0, r0, r1, lsl #6
	bx	lr
_037FE488:	.word	_038086EC

	arm_func_start FUN_037FE48C
FUN_037FE48C: ; 0x037FE48C
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r6, r0
	mov	r5, #0
	add	r1, r6, #28
	b	_037FE4B4
_037FE4A4:
	ldrh	r0, [r1]
	sub	r0, r0, #240	; 0xf0
	strh	r0, [r1]
	add	r5, r5, #1
_037FE4B4:
	ldrh	r0, [r6, #28]
	cmp	r0, #240	; 0xf0
	bcs	_037FE4A4
	mov	r4, #0
	mov	r7, #1
	b	_037FE4F0
_037FE4CC:
	mov	r0, r6
	mov	r1, r7
	bl	FUN_037FD548
	cmp	r0, #0
	beq	_037FE4EC
	mov	r0, r6
	bl	FUN_037FE3AC
	b	_037FE4F8
_037FE4EC:
	add	r4, r4, #1
_037FE4F0:
	cmp	r4, r5
	blt	_037FE4CC
_037FE4F8:
	ldr	r0, _037FE548	; =SNDi_SharedWork
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_037FE524
	add	r3, r0, #64	; 0x40
	ldrb	r1, [r6, #1]
	mov	r0, #36	; 0x24
	mul	r2, r1, r0
	ldr	r0, [r3, r2]
	add	r0, r0, r4
	str	r0, [r3, r2]
_037FE524:
	ldrh	r2, [r6, #24]
	ldrh	r0, [r6, #26]
	mul	r1, r2, r0
	ldrh	r0, [r6, #28]
	add	r0, r0, r1, asr #8
	strh	r0, [r6, #28]
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_037FE548:	.word	SNDi_SharedWork

	arm_func_start FUN_037FE54C
FUN_037FE54C: ; 0x037FE54C
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	ldr	r4, [r5, #60]	; 0x3c
	b	_037FE56C
_037FE560:
	mov	r0, r4
	bl	SND_FreeExChannel
	ldr	r4, [r4, #80]	; 0x50
_037FE56C:
	cmp	r4, #0
	bne	_037FE560
	mov	r0, #0
	str	r0, [r5, #60]	; 0x3c
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start FUN_037FE588
FUN_037FE588: ; 0x037FE588
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r4, r0
	mov	r7, r2
	mov	r2, #0
	bl	FUN_037FE1E4
	ldr	r6, [r4, #60]	; 0x3c
	and	r5, r7, #255	; 0xff
	mov	r4, #1
	b	_037FE5E4
_037FE5B0:
	mov	r0, r6
	bl	SND_IsExChannelActive
	cmp	r0, #0
	beq	_037FE5E0
	cmp	r7, #0
	blt	_037FE5D4
	mov	r0, r6
	mov	r1, r5
	bl	SND_SetExChannelRelease
_037FE5D4:
	strb	r4, [r6, #34]	; 0x22
	mov	r0, r6
	bl	SND_ReleaseExChannel
_037FE5E0:
	ldr	r6, [r6, #80]	; 0x50
_037FE5E4:
	cmp	r6, #0
	bne	_037FE5B0
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

	arm_func_start FUN_037FE5F8
FUN_037FE5F8: ; 0x037FE5F8
	stmdb	sp!, {r4, lr}
	ldrb	r2, [r0]
	bic	r2, r2, #4
	strb	r2, [r0]
	str	r1, [r0, #32]
	mov	r1, #120	; 0x78
	strh	r1, [r0, #24]
	mov	r1, #256	; 0x100
	strh	r1, [r0, #26]
	mov	r1, #240	; 0xf0
	strh	r1, [r0, #28]
	mov	r1, #127	; 0x7f
	strb	r1, [r0, #5]
	mov	r3, #0
	strh	r3, [r0, #6]
	mov	r1, #64	; 0x40
	strb	r1, [r0, #4]
	mov	r2, #255	; 0xff
_037FE640:
	add	r1, r0, r3
	strb	r2, [r1, #8]
	add	r3, r3, #1
	cmp	r3, #16
	blt	_037FE640
	ldr	r2, _037FE6A4	; =SNDi_SharedWork
	ldr	r3, [r2]
	cmp	r3, #0
	beq	_037FE69C
	mov	r4, #0
	ldrb	ip, [r0, #1]
	mov	r1, #36	; 0x24
	mla	r3, ip, r1, r3
	str	r4, [r3, #64]	; 0x40
	mvn	lr, #0
_037FE67C:
	ldr	r3, [r2]
	ldrb	ip, [r0, #1]
	mla	r3, ip, r1, r3
	add	r3, r3, r4, lsl #1
	strh	lr, [r3, #32]
	add	r4, r4, #1
	cmp	r4, #16
	blt	_037FE67C
_037FE69C:
	ldmia	sp!, {r4, lr}
	bx	lr
_037FE6A4:	.word	SNDi_SharedWork

	arm_func_start FUN_037FE6A8
FUN_037FE6A8: ; 0x037FE6A8
	str	r1, [r0, #36]	; 0x24
	ldr	r1, [r0, #36]	; 0x24
	add	r1, r1, r2
	str	r1, [r0, #40]	; 0x28
	bx	lr

	arm_func_start FUN_037FE6BC
FUN_037FE6BC: ; 0x037FE6BC
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	mov	r0, #0
	str	r0, [r4, #36]	; 0x24
	str	r0, [r4, #40]	; 0x28
	ldrb	r1, [r4]
	orr	r1, r1, #2
	strb	r1, [r4]
	ldrb	r1, [r4]
	bic	r1, r1, #4
	strb	r1, [r4]
	ldrb	r1, [r4]
	bic	r1, r1, #8
	strb	r1, [r4]
	ldrb	r1, [r4]
	bic	r1, r1, #16
	strb	r1, [r4]
	ldrb	r1, [r4]
	bic	r1, r1, #32
	strb	r1, [r4]
	ldrb	r1, [r4]
	orr	r1, r1, #64	; 0x40
	strb	r1, [r4]
	ldrb	r1, [r4]
	bic	r1, r1, #128	; 0x80
	strb	r1, [r4]
	strb	r0, [r4, #59]	; 0x3b
	strh	r0, [r4, #2]
	mov	r1, #64	; 0x40
	strb	r1, [r4, #18]
	mov	r2, #127	; 0x7f
	strb	r2, [r4, #4]
	strb	r2, [r4, #5]
	strh	r0, [r4, #10]
	strb	r0, [r4, #8]
	strb	r0, [r4, #9]
	strb	r0, [r4, #6]
	strh	r0, [r4, #12]
	mov	r1, #255	; 0xff
	strb	r1, [r4, #14]
	strb	r1, [r4, #15]
	strb	r1, [r4, #16]
	strb	r1, [r4, #17]
	strb	r2, [r4, #1]
	mov	r1, #2
	strb	r1, [r4, #7]
	mov	r1, #60	; 0x3c
	strb	r1, [r4, #20]
	strb	r0, [r4, #21]
	strh	r0, [r4, #22]
	strb	r0, [r4, #19]
	ldr	r0, _037FE7AC	; =0x0000FFFF
	strh	r0, [r4, #30]
	add	r0, r4, #24
	bl	SND_InitLfoParam
	mov	r0, #0
	str	r0, [r4, #32]
	str	r0, [r4, #60]	; 0x3c
	ldmia	sp!, {r4, lr}
	bx	lr
_037FE7AC:	.word	0x0000FFFF

	arm_func_start FUN_037FE7B0
FUN_037FE7B0: ; 0x037FE7B0
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r4, r0
	mov	r6, r1
	cmp	r2, #4
	addls	pc, pc, r2, lsl #2
	b	_037FE86C
	b	_037FE7DC
	b	_037FE7F8
	b	_037FE804
	b	_037FE83C
	b	_037FE810
_037FE7DC:
	ldr	r0, [r4, #40]	; 0x28
	bl	FUN_037FE968
	mov	r5, r0
	ldr	r0, [r4, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r4, #40]	; 0x28
	b	_037FE86C
_037FE7F8:
	bl	FUN_037FE918
	mov	r5, r0
	b	_037FE86C
_037FE804:
	bl	FUN_037FE878
	mov	r5, r0
	b	_037FE86C
_037FE810:
	ldr	r0, [r4, #40]	; 0x28
	bl	FUN_037FE968
	mov	r1, r0
	ldr	r0, [r4, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r4, #40]	; 0x28
	mov	r0, r6
	bl	FUN_037FD504
	cmp	r0, #0
	ldrnesh	r5, [r0]
	b	_037FE86C
_037FE83C:
	bl	FUN_037FE918
	mov	r5, r0, lsl #16
	mov	r0, r4
	bl	FUN_037FE918
	mov	r0, r0, lsl #16
	mov	r4, r0, asr #16
	bl	SND_CalcRandom
	sub	r1, r4, r5, asr #16
	add	r1, r1, #1
	mul	r1, r0, r1
	mov	r0, r1, asr #16
	add	r5, r0, r5, asr #16
_037FE86C:
	mov	r0, r5
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start FUN_037FE878
FUN_037FE878: ; 0x037FE878
	stmdb	sp!, {r4, r5, r6, lr}
	mov	r6, r0
	mov	r5, #0
	add	r4, r6, #40	; 0x28
_037FE888:
	ldr	r0, [r6, #40]	; 0x28
	bl	FUN_037FE968
	ldr	r1, [r4]
	add	r1, r1, #1
	str	r1, [r4]
	and	r1, r0, #127	; 0x7f
	orr	r5, r1, r5, lsl #7
	ands	r0, r0, #128	; 0x80
	bne	_037FE888
	mov	r0, r5
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr

	arm_func_start FUN_037FE8B8
FUN_037FE8B8: ; 0x037FE8B8
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r4, r0
	ldr	r0, [r4, #40]	; 0x28
	bl	FUN_037FE968
	mov	r5, r0
	ldr	r0, [r4, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r4, #40]	; 0x28
	ldr	r0, [r4, #40]	; 0x28
	bl	FUN_037FE968
	ldr	r1, [r4, #40]	; 0x28
	add	r1, r1, #1
	str	r1, [r4, #40]	; 0x28
	orr	r5, r5, r0, lsl #8
	ldr	r0, [r4, #40]	; 0x28
	bl	FUN_037FE968
	ldr	r1, [r4, #40]	; 0x28
	add	r1, r1, #1
	str	r1, [r4, #40]	; 0x28
	orr	r0, r5, r0, lsl #16
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start FUN_037FE918
FUN_037FE918: ; 0x037FE918
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	ldr	r0, [r5, #40]	; 0x28
	bl	FUN_037FE968
	mov	r4, r0
	ldr	r0, [r5, #40]	; 0x28
	add	r0, r0, #1
	str	r0, [r5, #40]	; 0x28
	ldr	r0, [r5, #40]	; 0x28
	bl	FUN_037FE968
	ldr	r1, [r5, #40]	; 0x28
	add	r1, r1, #1
	str	r1, [r5, #40]	; 0x28
	orr	r0, r4, r0, lsl #8
	mov	r0, r0, lsl #16
	mov	r0, r0, lsr #16
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr

	arm_func_start FUN_037FE968
FUN_037FE968: ; 0x037FE968
	stmdb	sp!, {r4, lr}
	mov	r4, r0
	ldr	r0, _037FE9B0	; =_03807F50
	ldr	r1, [r0]
	cmp	r4, r1
	bcc	_037FE98C
	ldr	r0, [r0, #4]
	cmp	r4, r0
	bcc	_037FE994
_037FE98C:
	mov	r0, r4
	bl	FUN_037FE9B8
_037FE994:
	ldr	r0, _037FE9B0	; =_03807F50
	ldr	r0, [r0]
	sub	r1, r4, r0
	ldr	r0, _037FE9B4	; =_03807F58
	ldrb	r0, [r0, r1]
	ldmia	sp!, {r4, lr}
	bx	lr
_037FE9B0:	.word	_03807F50
_037FE9B4:	.word	_03807F58

	arm_func_start FUN_037FE9B8
FUN_037FE9B8: ; 0x037FE9B8
	bic	r2, r0, #3
	ldr	r0, _037FE9F0	; =_03807F50
	str	r2, [r0]
	add	r1, r2, #16
	str	r1, [r0, #4]
	ldr	r1, [r2]
	str	r1, [r0, #8]
	ldr	r1, [r2, #4]
	str	r1, [r0, #12]
	ldr	r1, [r2, #8]
	str	r1, [r0, #16]
	ldr	r1, [r2, #12]
	str	r1, [r0, #20]
	bx	lr
_037FE9F0:	.word	_03807F50
