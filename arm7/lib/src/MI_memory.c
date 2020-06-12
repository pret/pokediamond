#include "function_target.h"
#include "MI_memory.h"

asm void MIi_CpuClear16(register u16 value, register u16 * dst, register u32 size) {
    mov	r3, #0
loop:
	cmp	r3, r2
	strlth	r0, [r1, r3]
	addlt	r3, r3, #2
	blt	loop
	bx	lr
}

asm void MIi_CpuCopy16(register u16 * src, register u16 * dst, register u32 size) {
	mov	ip, #0
_037FB31C:
	cmp	ip, r2
	ldrlth	r3, [r0, ip]
	strlth	r3, [r1, ip]
	addlt	ip, ip, #2
	blt	_037FB31C
	bx	lr
}

asm void MIi_CpuClear32(register u32 value, register u32 * dst, register u32 size) {
	add	ip, r1, r2
_037FB338:
	cmp	r1, ip
	stmltia	r1!, {r0}
	blt	_037FB338
	bx	lr
}

asm void MIi_CpuCopy32(register u32 * src, register u32 * dst, register u32 size) {
	add	ip, r1, r2
_037FB34C:
	cmp	r1, ip
	ldmltia	r0!, {r2}
	stmltia	r1!, {r2}
	blt	_037FB34C
	bx	lr
}

asm void MIi_CpuClearFast(register u32 value, register u32 * dst, register u32 size) {
	stmdb	sp!, {r4, r5, r6, r7, r8, r9}
	add	r9, r1, r2
	mov	ip, r2, lsr #5
	add	ip, r1, ip, lsl #5
	mov	r2, r0
	mov	r3, r2
	mov	r4, r2
	mov	r5, r2
	mov	r6, r2
	mov	r7, r2
	mov	r8, r2
_037FB38C:
	cmp	r1, ip
	stmltia	r1!, {r0, r2, r3, r4, r5, r6, r7, r8}
	blt	_037FB38C
_037FB398:
	cmp	r1, r9
	stmltia	r1!, {r0}
	blt	_037FB398
	ldmia	sp!, {r4, r5, r6, r7, r8, r9}
	bx	lr
}

asm void MIi_CpuCopyFast(register u32 * src, register u32 * dst, register u32 size) {
	stmdb	sp!, {r4-r9, r10}
	add	r10, r1, r2
	mov	ip, r2, lsr #5
	add	ip, r1, ip, lsl #5
_037FB3BC:
	cmp	r1, ip
	ldmltia	r0!, {r2-r9}
	stmltia	r1!, {r2-r9}
	blt	_037FB3BC
_037FB3CC:
	cmp	r1, r10
	ldmltia	r0!, {r2}
	stmltia	r1!, {r2}
	blt	_037FB3CC
	ldmia	sp!, {r4-r9, r10}
	bx	lr
}

asm void MI_CpuFill8(register u8 value, register u8 * dst, register u32 size) {
	cmp	r2, #0
	bxeq	lr
	tst	r0, #1
	beq	_037FB410
	ldrh	ip, [r0, #-1]
	and	ip, ip, #0xff
	orr	r3, ip, r1, lsl #8
	strh	r3, [r0, #-1]
	add	r0, r0, #1
	subs	r2, r2, #1
	bxeq	lr
_037FB410:
	cmp	r2, #2
	bcc	_037FB458
	orr	r1, r1, r1, lsl #8
	tst	r0, #2
	beq	_037FB430
	strh	r1, [r0], #2
	subs	r2, r2, #2
	bxeq	lr
_037FB430:
	orr	r1, r1, r1, lsl #16
	bics	r3, r2, #3
	beq	_037FB450
	sub	r2, r2, r3
	add	ip, r3, r0
_037FB444:
	str	r1, [r0], #4
	cmp	r0, ip
	bcc	_037FB444
_037FB450:
	tst	r2, #2
	strneh	r1, [r0], #2
_037FB458:
	tst	r2, #1
	bxeq	lr
	ldrh	r3, [r0]
	and	r3, r3, #0xff00
	and	r1, r1, #0xff
	orr	r1, r1, r3
	strh	r1, [r0]
	bx	lr
}

asm void MI_CpuCopy8(register u8 * src, register u8 * dst, register u32 size) {
	cmp	r2, #0
	bxeq	lr
	tst	r1, #1
	beq	_037FB4B8
	ldrh	ip, [r1, #-1]
	and	ip, ip, #0xff
	tst	r0, #1
	ldrneh	r3, [r0, #-1]
	movne	r3, r3, lsr #8
	ldreqh	r3, [r0]
	orr	r3, ip, r3, lsl #8
	strh	r3, [r1, #-1]
	add	r0, r0, #1
	add	r1, r1, #1
	subs	r2, r2, #1
	bxeq	lr
_037FB4B8:
	eor	ip, r1, r0
	tst	ip, #1
	beq	_037FB50C
	bic	r0, r0, #1
	ldrh	ip, [r0], #2
	mov	r3, ip, lsr #8
	subs	r2, r2, #2
	bcc	_037FB4F0
_037FB4D8:
	ldrh	ip, [r0], #2
	orr	ip, r3, ip, lsl #8
	strh	ip, [r1], #2
	mov	r3, ip, lsr #16
	subs	r2, r2, #2
	bcs	_037FB4D8
_037FB4F0:
	tst	r2, #1
	bxeq	lr
	ldrh	ip, [r1]
	and	ip, ip, #0xff00
	orr	ip, ip, r3
	strh	ip, [r1]
	bx	lr
_037FB50C:
	tst	ip, #2
	beq	_037FB538
	bics	r3, r2, #1
	beq	_037FB584
	sub	r2, r2, r3
	add	ip, r3, r1
_037FB524:
	ldrh	r3, [r0], #2
	strh	r3, [r1], #2
	cmp	r1, ip
	bcc	_037FB524
	b	_037FB584
_037FB538:
	cmp	r2, #2
	bcc	_037FB584
	tst	r1, #2
	beq	_037FB558
	ldrh	r3, [r0], #2
	strh	r3, [r1], #2
	subs	r2, r2, #2
	bxeq	lr
_037FB558:
	bics	r3, r2, #3
	beq	_037FB578
	sub	r2, r2, r3
	add	ip, r3, r1
_037FB568:
	ldr	r3, [r0], #4
	str	r3, [r1], #4
	cmp	r1, ip
	bcc	_037FB568
_037FB578:
	tst	r2, #2
	ldrneh	r3, [r0], #2
	strneh	r3, [r1], #2
_037FB584:
	tst	r2, #1
	bxeq	lr
	ldrh	r2, [r1]
	ldrh	r0, [r0]
	and	r2, r2, #0xff00
	and	r0, r0, #0xff
	orr	r0, r2, r0
	strh	r0, [r1]
	bx	lr
}
