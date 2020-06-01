    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_InitContext
OS_InitContext: ; 0x037F9740
	add	r1, r1, #4
	str	r1, [r0, #64]	; 0x40
	str	r2, [r0, #68]	; 0x44
	sub	r2, r2, #64	; 0x40
	tst	r2, #4
	subne	r2, r2, #4
	str	r2, [r0, #56]	; 0x38
	ands	r1, r1, #1
	movne	r1, #63	; 0x3f
	moveq	r1, #31
	str	r1, [r0]
	mov	r1, #0
	str	r1, [r0, #4]
	str	r1, [r0, #8]
	str	r1, [r0, #12]
	str	r1, [r0, #16]
	str	r1, [r0, #20]
	str	r1, [r0, #24]
	str	r1, [r0, #28]
	str	r1, [r0, #32]
	str	r1, [r0, #36]	; 0x24
	str	r1, [r0, #40]	; 0x28
	str	r1, [r0, #44]	; 0x2c
	str	r1, [r0, #48]	; 0x30
	str	r1, [r0, #52]	; 0x34
	str	r1, [r0, #60]	; 0x3c
	bx	lr

	arm_func_start OS_SaveContext
OS_SaveContext: ; 0x037F97AC
	add	r1, r0, #0
	mrs	r2, CPSR
	str	r2, [r1], #4
	mov	r0, #211	; 0xd3
	msr	CPSR_c, r0
	str	sp, [r1, #64]	; 0x40
	msr	CPSR_c, r2
	mov	r0, #1
	stmia	r1, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}
	adr	r0, _037F97E0
	str	r0, [r1, #60]	; 0x3c
	mov	r0, #0
	bx	lr

	arm_func_start OS_LoadContext
OS_LoadContext: ; 0x037F97E0
_037F97E0: ; needed because otherwise it breaks
	mrs	r1, CPSR
	bic	r1, r1, #31
	orr	r1, r1, #211	; 0xd3
	msr	CPSR_c, r1
	ldr	r1, [r0], #4
	msr	SPSR_fsxc, r1
	ldr	sp, [r0, #64]	; 0x40
	ldr	lr, [r0, #60]	; 0x3c
	ldmia	r0, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
	nop			; (mov r0, r0)
	subs	pc, lr, #4
