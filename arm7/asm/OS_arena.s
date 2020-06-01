	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start OS_SetArenaLo
OS_SetArenaLo: ; 0x037F9BBC
	mov	r0, r0, lsl #2
	add	r0, r0, #40894464	; 0x2700000
	add	r0, r0, #1044480	; 0xff000
	str	r1, [r0, #3488]	; 0xda0
	bx	lr

	arm_func_start OS_SetArenaHi
OS_SetArenaHi: ; 0x037F9BD0
	mov	r0, r0, lsl #2
	add	r0, r0, #40894464	; 0x2700000
	add	r0, r0, #1044480	; 0xff000
	str	r1, [r0, #3524]	; 0xdc4
	bx	lr

	arm_func_start OS_GetInitArenaLo
OS_GetInitArenaLo: ; 0x037F9BE4
	cmp	r0, #1
	beq	_037F9C00
	cmp	r0, #7
	beq	_037F9C08
	cmp	r0, #8
	beq	_037F9C18
	b	_037F9C2C
_037F9C00:
	ldr	r0, _037F9C34	; =0x027FAFCC
	bx	lr
_037F9C08:
	ldr	r0, _037F9C38	; =0x0380B92C
	cmp	r0, #58720256	; 0x03800000
	movhi	r0, #58720256	; 0x03800000
	bx	lr
_037F9C18:
	mov	r0, #58720256	; 0x03800000
	ldr	r1, _037F9C38	; =0x0380B92C
	cmp	r1, #58720256	; 0x03800000
	movhi	r0, r1
	bx	lr
_037F9C2C:
	mov	r0, #0
	bx	lr
_037F9C34:	.word	0x027FAFCC
_037F9C38:	.word	0x0380B92C

	arm_func_start OS_GetInitArenaHi
OS_GetInitArenaHi: ; 0x037F9C3C
	cmp	r0, #1
	beq	_037F9C58
	cmp	r0, #7
	beq	_037F9C60
	cmp	r0, #8
	beq	_037F9C68
	b	_037F9CA0
_037F9C58:
	ldr	r0, _037F9CA8	; =0x027FF000
	bx	lr
_037F9C60:
	mov	r0, #58720256	; 0x03800000
	bx	lr
_037F9C68:
	ldr	r1, _037F9CAC	; =0x00000400
	ldr	r0, _037F9CB0	; =0x0380FF80
	sub	r2, r0, r1
	mov	r0, #58720256	; 0x03800000
	ldr	r1, _037F9CB4	; =0x0380B92C
	cmp	r1, #58720256	; 0x03800000
	movhi	r0, r1
	ldr	r1, _037F9CB8	; =0x00000400
	cmp	r1, #0
	bxeq	lr
	cmp	r1, #0
	sublt	r0, r0, r1
	subge	r0, r2, r1
	bx	lr
_037F9CA0:
	mov	r0, #0
	bx	lr
_037F9CA8:	.word	0x027FF000
_037F9CAC:	.word	0x00000400
_037F9CB0:	.word	0x0380FF80
_037F9CB4:	.word	0x0380B92C
_037F9CB8:	.word	0x00000400

	arm_func_start OS_GetArenaLo
OS_GetArenaLo: ; 0x037F9CBC
	mov	r0, r0, lsl #2
	add	r0, r0, #40894464	; 0x2700000
	add	r0, r0, #1044480	; 0xff000
	ldr	r0, [r0, #3488]	; 0xda0
	bx	lr

	arm_func_start OS_GetArenaHi
OS_GetArenaHi: ; 0x037F9CD0
	mov	r0, r0, lsl #2
	add	r0, r0, #40894464	; 0x2700000
	add	r0, r0, #1044480	; 0xff000
	ldr	r0, [r0, #3524]	; 0xdc4
	bx	lr

	arm_func_start OS_InitArena
OS_InitArena: ; 0x037F9CE4
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r1, _037F9D84	; =_038078F4
	ldr	r0, [r1]
	cmp	r0, #0
	bne	_037F9D78
	mov	r0, #1
	str	r0, [r1]
	bl	OS_GetInitArenaHi
	mov	r1, r0
	mov	r0, #1
	bl	OS_SetArenaHi
	mov	r0, #1
	bl	OS_GetInitArenaLo
	mov	r1, r0
	mov	r0, #1
	bl	OS_SetArenaLo
	mov	r0, #7
	bl	OS_GetInitArenaHi
	mov	r1, r0
	mov	r0, #7
	bl	OS_SetArenaHi
	mov	r0, #7
	bl	OS_GetInitArenaLo
	mov	r1, r0
	mov	r0, #7
	bl	OS_SetArenaLo
	mov	r0, #8
	bl	OS_GetInitArenaHi
	mov	r1, r0
	mov	r0, #8
	bl	OS_SetArenaHi
	mov	r0, #8
	bl	OS_GetInitArenaLo
	mov	r1, r0
	mov	r0, #8
	bl	OS_SetArenaLo
_037F9D78:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_037F9D84:	.word	_038078F4
