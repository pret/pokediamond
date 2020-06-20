	.include "asm/macros.inc"
	.include "global.inc"

    .section .text

	arm_func_start OS_IrqHandler
OS_IrqHandler: ; 0x037F853C
	stmfd	sp!, {lr}
	mov	ip, #67108864	; 0x4000000
	add	ip, ip, #528	; 0x210
	ldr	r1, [ip, #-8]
	cmp	r1, #0
	ldmeqfd	sp!, {pc}
	ldmia	ip, {r1, r2}
	ands	r1, r1, r2
	ldmeqfd	sp!, {pc}
	mov	r3, #1
	mov	r0, #0
_037F8568:
	ands	r2, r1, r3, lsl r0
	addeq	r0, r0, #1
	beq	_037F8568
	str	r2, [ip, #4]
	ldr	r1, _037F8588	; =OS_IRQTable
	ldr	r0, [r1, r0, lsl #2]
	ldr	lr, _037F858C	; =OS_IrqHandler_ThreadSwitch
	bx	r0
_037F8588:	.word	OS_IRQTable
_037F858C:	.word	OS_IrqHandler_ThreadSwitch

	arm_func_start OS_IrqHandler_ThreadSwitch
OS_IrqHandler_ThreadSwitch:
	ldr	ip, _037F86AC	; =OSi_IrqThreadQueue
	mov	r3, #0
	ldr	ip, [ip]
	mov	r2, #1
	cmp	ip, #0
	beq	_037F85E0
_037F85A8:
	str	r2, [ip, #72]	; 0x48
	str	r3, [ip, #92]	; 0x5c
	str	r3, [ip, #96]	; 0x60
	ldr	r0, [ip, #100]	; 0x64
	str	r3, [ip, #100]	; 0x64
	mov	ip, r0
	cmp	ip, #0
	bne	_037F85A8
	ldr	ip, _037F86AC	; =OSi_IrqThreadQueue
	str	r3, [ip]
	str	r3, [ip, #4]
	ldr	ip, _037F86B0	; =OSi_ThreadInfo
	mov	r1, #1
	strh	r1, [ip]
_037F85E0:
	ldr	ip, _037F86B0	; =OSi_ThreadInfo
	ldrh	r1, [ip]
	cmp	r1, #0
	ldreq	pc, [sp], #4		; (ldreq pc, [sp], #4)
	mov	r1, #0
	strh	r1, [ip]
	mov	r3, #210	; 0xd2
	msr	CPSR_c, r3
	add	r2, ip, #8
	ldr	r1, [r2]
_037F8608:
	cmp	r1, #0
	ldrneh	r0, [r1, #72]	; 0x48
	cmpne	r0, #1
	ldrne	r1, [r1, #76]	; 0x4c
	bne	_037F8608
	cmp	r1, #0
	bne	_037F8630
_037F8624:
	mov	r3, #146	; 0x92
	msr	CPSR_c, r3
	ldr pc, [sp], #4
_037F8630:
	ldr	r0, [ip, #4]
	cmp	r1, r0
	beq	_037F8624
	ldr	r3, [ip, #12]
	cmp	r3, #0
	beq	_037F8658
	stmdb	sp!, {r0, r1, ip}
	mov	lr, pc
	bx	r3
	ldmia	sp!, {r0, r1, ip}
_037F8658:
	str	r1, [ip, #4]
	mrs	r2, SPSR
	str	r2, [r0, #0]!
	ldmib	sp!, {r2, r3}
	stmib	r0!, {r2, r3}
	ldmib	sp!, {r2, r3, ip, lr}
	stmib	r0!, {r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
	stmib	r0!, {lr}
	mov	r3, #211	; 0xd3
	msr	CPSR_c, r3
	stmib	r0!, {sp}
	ldr	sp, [r1, #68]	; 0x44
	mov	r3, #210	; 0xd2
	msr	CPSR_c, r3
	ldr	r2, [r1, #0]!
	msr	SPSR_fc, r2
	ldr	lr, [r1, #64]	; 0x40
	ldmib	r1!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
	nop			; (mov r0, r0)
	stmda	sp!, {r0, r1, r2, r3, ip, lr}
	ldmia	sp!, {pc}
_037F86AC:	.word	OSi_IrqThreadQueue
_037F86B0:	.word	OSi_ThreadInfo
