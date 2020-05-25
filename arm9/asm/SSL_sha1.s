	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global ssl_sha1_padding
ssl_sha1_padding: ; 0x0210642C
	.byte 0x80
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.section .text

	arm_func_start CPSi_sha1_result_prng
CPSi_sha1_result_prng: ; 0x020A405C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	ldr r1, _020A4094 ; =ssl_sha1_padding+1
	mov r5, r0
	mov r2, #0x2c
	bl CPSi_sha1_calc
	mov r0, r4
	mov r1, r5
	mov r2, #0x14
	bl ssl_sha1_char_from_long
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A4094: .word ssl_sha1_padding+1

	arm_func_start CPSi_sha1_result
CPSi_sha1_result: ; 0x020A4098
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	mov r0, r4
	add r1, r5, #0x14
	mov r2, #0x8
	bl ssl_sha1_char_from_long
	ldr r0, [r5, #0x18]
	ldr r1, _020A4108 ; =ssl_sha1_padding
	mov r0, r0, lsr #0x3
	and r0, r0, #0x3f
	cmp r0, #0x38
	rsblt r2, r0, #0x38
	rsbge r2, r0, #0x78
	mov r0, r5
	bl CPSi_sha1_calc
	mov r0, r5
	mov r1, r4
	mov r2, #0x8
	bl CPSi_sha1_calc
	mov r0, r4
	mov r1, r5
	mov r2, #0x14
	bl ssl_sha1_char_from_long
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A4108: .word ssl_sha1_padding

	arm_func_start CPSi_sha1_calc
CPSi_sha1_calc:
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	ldr r3, [r8, #0x18]
	mov r6, r2
	add r0, r3, r6, lsl #0x3
	str r0, [r8, #0x18]
	ldr r0, [r8, #0x18]
	mov r2, r3, lsr #0x3
	cmp r0, r6, lsl #0x3
	ldrcc r0, [r8, #0x14]
	and r4, r2, #0x3f
	addcc r0, r0, #0x1
	strcc r0, [r8, #0x14]
	ldr r0, [r8, #0x14]
	rsb r5, r4, #0x40
	add r0, r0, r6, lsr #0x1d
	mov r7, r1
	str r0, [r8, #0x14]
	cmp r6, r5
	blo _020A41AC
	add r1, r8, #0x1c
	mov r0, r7
	mov r2, r5
	add r1, r1, r4
	bl MI_CpuCopy8
	mov r0, r8
	add r1, r8, #0x1c
	mov r4, #0x0
	bl CPSi_sha1_block
	add r0, r5, #0x3f
	cmp r0, r6
	bhs _020A41B0
_020A418C:
	mov r0, r8
	add r1, r7, r5
	bl CPSi_sha1_block
	add r5, r5, #0x40
	add r0, r5, #0x3f
	cmp r0, r6
	blo _020A418C
	b _020A41B0
_020A41AC:
	mov r5, #0x0
_020A41B0:
	add r1, r8, #0x1c
	add r0, r7, r5
	add r1, r1, r4
	sub r2, r6, r5
	bl MI_CpuCopy8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start CPSi_sha1_init
CPSi_sha1_init: ; 0x020A41CC
	stmdb sp!, {r4,lr}
	mov r1, #0x0
	mov r2, #0x5c
	mov r4, r0
	bl MI_CpuFill8
	ldr r0, _020A4210 ; =0x67452301
	ldr r1, _020A4214 ; =0xEFCDAB89
	str r0, [r4, #0x0]
	ldr r0, _020A4218 ; =0x98BADCFE
	str r1, [r4, #0x4]
	ldr r1, _020A421C ; =0x10325476
	str r0, [r4, #0x8]
	ldr r0, _020A4220 ; =0xC3D2E1F0
	str r1, [r4, #0xc]
	str r0, [r4, #0x10]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A4210: .word 0x67452301
_020A4214: .word 0xEFCDAB89
_020A4218: .word 0x98BADCFE
_020A421C: .word 0x10325476
_020A4220: .word 0xC3D2E1F0

	arm_func_start CPSi_sha1_block
CPSi_sha1_block: ; 0x020A4224
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x54
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x0]
	add r0, sp, #0x10
	mov r2, #0x40
	ldr r6, [r3, #0x0]
	ldr r7, [r3, #0x4]
	ldr r8, [r3, #0x8]
	ldr r5, [r3, #0xc]
	ldr r4, [r3, #0x10]
	bl ssl_sha1_long_from_char
	mov r2, #0x0
	ldr r3, _020A48BC ; =0x5A827999
	mov r0, r2
	add r1, sp, #0x10
_020A4264:
	eor r9, r8, r5
	mov r10, r6, lsl #0x5
	and r9, r7, r9
	orr r10, r10, r6, lsr #0x1b
	eor r9, r5, r9
	mov r11, r7, lsl #0x1e
	orr r7, r11, r7, lsr #0x2
	eor r11, r7, r8
	add r9, r10, r9
	ldr r12, [r1, r2, lsl #0x2]
	and r10, r6, r11
	add r9, r12, r9
	add r9, r9, r3
	add r4, r4, r9
	add r9, r2, #0x1
	ldr r9, [r1, r9, lsl #0x2]
	eor r10, r8, r10
	mov r11, r4, lsl #0x5
	orr r11, r11, r4, lsr #0x1b
	add r10, r11, r10
	add r10, r9, r10
	mov r9, r6, lsl #0x1e
	add r10, r10, r3
	add r5, r5, r10
	orr r6, r9, r6, lsr #0x2
	add r9, r2, #0x2
	ldr r10, [r1, r9, lsl #0x2]
	mov r9, r5, lsl #0x5
	orr r9, r9, r5, lsr #0x1b
	eor r11, r6, r7
	and r11, r4, r11
	eor r11, r7, r11
	add r9, r9, r11
	add r9, r10, r9
	add r9, r9, r3
	add r8, r8, r9
	mov r9, r4, lsl #0x1e
	orr r4, r9, r4, lsr #0x2
	add r9, r2, #0x3
	ldr r10, [r1, r9, lsl #0x2]
	mov r9, r8, lsl #0x5
	orr r9, r9, r8, lsr #0x1b
	eor r11, r4, r6
	and r11, r5, r11
	eor r11, r6, r11
	add r9, r9, r11
	add r9, r10, r9
	add r9, r9, r3
	add r7, r7, r9
	mov r9, r5, lsl #0x1e
	orr r5, r9, r5, lsr #0x2
	add r9, r2, #0x4
	ldr r10, [r1, r9, lsl #0x2]
	mov r9, r7, lsl #0x5
	orr r9, r9, r7, lsr #0x1b
	eor r11, r5, r4
	and r11, r8, r11
	eor r11, r4, r11
	add r9, r9, r11
	add r9, r10, r9
	add r9, r9, r3
	add r6, r6, r9
	mov r9, r8, lsl #0x1e
	orr r8, r9, r8, lsr #0x2
	add r2, r2, #0x5
	add r0, r0, #0x1
	cmp r0, #0x3
	blt _020A4264
	eor r0, r8, r5
	mov r2, r6, lsl #0x5
	and r0, r7, r0
	orr r3, r2, r6, lsr #0x1b
	eor r0, r5, r0
	add r3, r3, r0
	ldr r9, [sp, #0x4c]
	ldr r0, _020A48BC ; =0x5A827999
	add r3, r9, r3
	add r3, r3, r0
	mov r2, r7, lsl #0x1e
	orr r9, r2, r7, lsr #0x2
	mov r0, #0x0
	add r4, r4, r3
	bl R
	eor r1, r9, r8
	mov r3, r4, lsl #0x5
	and r1, r6, r1
	mov r2, r6, lsl #0x1e
	orr r3, r3, r4, lsr #0x1b
	eor r1, r8, r1
	add r1, r3, r1
	add r3, r1, r0
	ldr r0, _020A48BC ; =0x5A827999
	add r1, sp, #0x10
	add r3, r3, r0
	orr r10, r2, r6, lsr #0x2
	mov r0, #0x1
	add r5, r5, r3
	bl R
	eor r1, r10, r9
	mov r2, r5, lsl #0x5
	and r1, r4, r1
	orr r2, r2, r5, lsr #0x1b
	eor r1, r9, r1
	add r1, r2, r1
	add r2, r1, r0
	ldr r0, _020A48BC ; =0x5A827999
	mov r1, r4, lsl #0x1e
	add r0, r2, r0
	orr r6, r1, r4, lsr #0x2
	add r8, r8, r0
	add r1, sp, #0x10
	mov r0, #0x2
	bl R
	mov r1, r8, lsl #0x5
	orr r2, r1, r8, lsr #0x1b
	eor r1, r6, r10
	and r1, r5, r1
	eor r1, r10, r1
	add r1, r2, r1
	add r2, r1, r0
	ldr r0, _020A48BC ; =0x5A827999
	mov r1, r5, lsl #0x1e
	add r0, r2, r0
	orr r7, r1, r5, lsr #0x2
	add r9, r9, r0
	mov r0, #0x3
	add r1, sp, #0x10
	bl R
	mov r1, r9, lsl #0x5
	orr r2, r1, r9, lsr #0x1b
	eor r1, r7, r6
	and r1, r8, r1
	eor r1, r6, r1
	add r1, r2, r1
	add r2, r1, r0
	ldr r0, _020A48BC ; =0x5A827999
	mov r1, r8, lsl #0x1e
	add r0, r2, r0
	add r10, r10, r0
	mov r0, #0x0
	ldr r4, _020A48C0 ; =0x6ED9EBA1
	orr r8, r1, r8, lsr #0x2
	mov r5, #0x4
	str r0, [sp, #0xc]
	add r11, sp, #0x10
_020A44A8:
	mov r0, r5
	mov r1, r11
	bl R
	mov r2, r10, lsl #0x5
	eor r1, r9, r8
	orr r2, r2, r10, lsr #0x1b
	eor r1, r7, r1
	add r1, r2, r1
	add r0, r1, r0
	add r1, r0, r4
	mov r0, r9, lsl #0x1e
	add r6, r6, r1
	orr r9, r0, r9, lsr #0x2
	add r0, r5, #0x1
	mov r1, r11
	bl R
	mov r1, r6, lsl #0x5
	orr r2, r1, r6, lsr #0x1b
	eor r1, r10, r9
	eor r1, r8, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r7, r7, r0
	mov r0, r10, lsl #0x1e
	orr r10, r0, r10, lsr #0x2
	add r0, r5, #0x2
	and r5, r0, #0xf
	mov r0, r5
	mov r1, r11
	bl R
	mov r1, r7, lsl #0x5
	orr r2, r1, r7, lsr #0x1b
	eor r1, r6, r10
	eor r1, r9, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r8, r8, r0
	mov r0, r6, lsl #0x1e
	orr r6, r0, r6, lsr #0x2
	add r0, r5, #0x1
	mov r1, r11
	bl R
	mov r1, r8, lsl #0x5
	orr r2, r1, r8, lsr #0x1b
	eor r1, r7, r6
	eor r1, r10, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r9, r9, r0
	mov r0, r7, lsl #0x1e
	orr r7, r0, r7, lsr #0x2
	add r0, r5, #0x2
	mov r1, r11
	bl R
	mov r1, r9, lsl #0x5
	orr r2, r1, r9, lsr #0x1b
	eor r1, r8, r7
	eor r1, r6, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r10, r10, r0
	mov r0, r8, lsl #0x1e
	orr r8, r0, r8, lsr #0x2
	ldr r0, [sp, #0xc]
	add r5, r5, #0x3
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	cmp r0, #0x4
	blt _020A44A8
	mov r0, #0x0
	ldr r4, _020A48C4 ; =0x8F1BBCDC
	str r0, [sp, #0x8]
	add r11, sp, #0x10
_020A45DC:
	mov r0, r5
	mov r1, r11
	bl R
	orr r2, r8, r7
	mov r1, r10, lsl #0x5
	and r3, r9, r2
	and r2, r8, r7
	orr r1, r1, r10, lsr #0x1b
	orr r2, r3, r2
	add r1, r1, r2
	add r1, r1, r0
	mov r0, r9, lsl #0x1e
	add r1, r1, r4
	add r6, r6, r1
	orr r9, r0, r9, lsr #0x2
	add r0, r5, #0x1
	mov r1, r11
	bl R
	orr r2, r9, r8
	mov r1, r6, lsl #0x5
	and r3, r10, r2
	and r2, r9, r8
	orr r1, r1, r6, lsr #0x1b
	orr r2, r3, r2
	add r1, r1, r2
	add r0, r1, r0
	add r0, r0, r4
	add r7, r7, r0
	mov r0, r10, lsl #0x1e
	orr r10, r0, r10, lsr #0x2
	add r0, r5, #0x2
	mov r1, r11
	bl R
	orr r2, r10, r9
	mov r1, r7, lsl #0x5
	and r3, r6, r2
	and r2, r10, r9
	orr r1, r1, r7, lsr #0x1b
	orr r2, r3, r2
	add r1, r1, r2
	add r0, r1, r0
	add r0, r0, r4
	add r8, r8, r0
	mov r0, r6, lsl #0x1e
	orr r6, r0, r6, lsr #0x2
	add r0, r5, #0x3
	and r5, r0, #0xf
	mov r0, r5
	mov r1, r11
	bl R
	orr r2, r6, r10
	mov r1, r8, lsl #0x5
	and r3, r7, r2
	and r2, r6, r10
	orr r1, r1, r8, lsr #0x1b
	orr r2, r3, r2
	add r1, r1, r2
	add r0, r1, r0
	add r0, r0, r4
	add r9, r9, r0
	mov r0, r7, lsl #0x1e
	orr r7, r0, r7, lsr #0x2
	add r0, r5, #0x1
	mov r1, r11
	bl R
	orr r2, r7, r6
	mov r1, r9, lsl #0x5
	and r3, r8, r2
	and r2, r7, r6
	orr r1, r1, r9, lsr #0x1b
	orr r2, r3, r2
	add r1, r1, r2
	add r0, r1, r0
	add r0, r0, r4
	add r10, r10, r0
	mov r0, r8, lsl #0x1e
	orr r8, r0, r8, lsr #0x2
	ldr r0, [sp, #0x8]
	add r5, r5, #0x2
	add r0, r0, #0x1
	str r0, [sp, #0x8]
	cmp r0, #0x4
	blt _020A45DC
	mov r0, #0x0
	ldr r4, _020A48C8 ; =0xCA62C1D6
	str r0, [sp, #0x4]
	add r11, sp, #0x10
_020A4738:
	mov r0, r5
	mov r1, r11
	bl R
	mov r2, r10, lsl #0x5
	eor r1, r9, r8
	orr r2, r2, r10, lsr #0x1b
	eor r1, r7, r1
	add r1, r2, r1
	add r0, r1, r0
	add r1, r0, r4
	mov r0, r9, lsl #0x1e
	add r6, r6, r1
	orr r9, r0, r9, lsr #0x2
	add r0, r5, #0x1
	mov r1, r11
	bl R
	mov r1, r6, lsl #0x5
	orr r2, r1, r6, lsr #0x1b
	eor r1, r10, r9
	eor r1, r8, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r7, r7, r0
	mov r0, r10, lsl #0x1e
	orr r10, r0, r10, lsr #0x2
	add r0, r5, #0x2
	mov r1, r11
	bl R
	mov r1, r7, lsl #0x5
	orr r2, r1, r7, lsr #0x1b
	eor r1, r6, r10
	eor r1, r9, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r8, r8, r0
	mov r0, r6, lsl #0x1e
	orr r6, r0, r6, lsr #0x2
	add r0, r5, #0x3
	mov r1, r11
	bl R
	mov r1, r8, lsl #0x5
	orr r2, r1, r8, lsr #0x1b
	eor r1, r7, r6
	eor r1, r10, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r9, r9, r0
	mov r0, r7, lsl #0x1e
	orr r7, r0, r7, lsr #0x2
	add r0, r5, #0x4
	and r5, r0, #0xf
	mov r0, r5
	mov r1, r11
	bl R
	mov r1, r9, lsl #0x5
	orr r2, r1, r9, lsr #0x1b
	eor r1, r8, r7
	eor r1, r6, r1
	add r1, r2, r1
	add r0, r1, r0
	add r0, r0, r4
	add r10, r10, r0
	mov r0, r8, lsl #0x1e
	orr r8, r0, r8, lsr #0x2
	ldr r0, [sp, #0x4]
	add r5, r5, #0x1
	add r0, r0, #0x1
	str r0, [sp, #0x4]
	cmp r0, #0x4
	blt _020A4738
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	add r1, r0, r10
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x0]
	ldr r0, [r0, #0x4]
	add r1, r0, r9
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x4]
	ldr r0, [r0, #0x8]
	add r1, r0, r8
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x8]
	ldr r0, [r0, #0xc]
	add r1, r0, r7
	ldr r0, [sp, #0x0]
	str r1, [r0, #0xc]
	ldr r0, [r0, #0x10]
	add r1, r0, r6
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x10]
	add sp, sp, #0x54
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A48BC: .word 0x5A827999
_020A48C0: .word 0x6ED9EBA1
_020A48C4: .word 0x8F1BBCDC
_020A48C8: .word 0xCA62C1D6

	arm_func_start ssl_sha1_long_from_char
ssl_sha1_long_from_char: ; 0x020A48CC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	addls sp, sp, #0x4
	mov r3, #0x0
	ldmlsia sp!, {r4-r5,lr}
	bxls lr
_020A48E8:
	add r12, r3, #0x1
	ldrb lr, [r1, r3]
	add r4, r3, #0x2
	add r5, r3, #0x3
	ldrb r12, [r1, r12]
	mov lr, lr, lsl #0x18
	add r3, r3, #0x4
	ldrb r4, [r1, r4]
	orr r12, lr, r12, lsl #0x10
	ldrb lr, [r1, r5]
	orr r4, r12, r4, lsl #0x8
	cmp r3, r2
	orr r4, lr, r4
	str r4, [r0], #0x4
	blo _020A48E8
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start ssl_sha1_char_from_long
ssl_sha1_char_from_long: ; 0x020A4930
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	movs r12, r2, lsr #0x2
	mov lr, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
_020A494C:
	ldr r3, [r1], #0x4
	add lr, lr, #0x1
	mov r2, r3, lsr #0x18
	strb r2, [r0, #0x0]
	mov r2, r3, lsr #0x10
	strb r2, [r0, #0x1]
	mov r2, r3, lsr #0x8
	strb r2, [r0, #0x2]
	strb r3, [r0, #0x3]
	cmp lr, r12
	add r0, r0, #0x4
	blo _020A494C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start R
R: ; 0x020A4988
	add r2, r0, #0xd
	add r12, r0, #0x2
	and r3, r2, #0xf
	eor r2, r0, #0x8
	and r12, r12, #0xf
	ldr r3, [r1, r3, lsl #0x2]
	ldr r2, [r1, r2, lsl #0x2]
	ldr r12, [r1, r12, lsl #0x2]
	eor r2, r3, r2
	ldr r3, [r1, r0, lsl #0x2]
	eor r2, r12, r2
	eor r3, r3, r2
	mov r2, r3, lsl #0x1
	orr r2, r2, r3, lsr #0x1f
	str r2, [r1, r0, lsl #0x2]
	ldr r0, [r1, r0, lsl #0x2]
	bx lr
