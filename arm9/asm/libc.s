	.include "asm/macros.inc"
	.include "global.inc"
	.extern OSi_ThreadInfo
	.extern __console_exit
    .extern __stdio_exit
    .extern __cs_id
    .extern __cs_ref
    .extern __cs
    .extern __files
    .extern __prep_buffer
    .extern __float_nan
    .extern __float_huge
    .extern __double_huge
    .extern memchr
    .extern __StringRead
    .extern wmemchr
    .extern copysign

	.section .data

	.balign 4, 0

	.section .text
	.balign 4, 0

	arm_func_start stricmp
stricmp: ; 0x020E9AD0
	stmdb sp!, {r3,lr}
	ldr r3, _020E9B34 ; =__lower_mapC
_020E9AD8:
	ldrb r2, [r0], #0x1
	cmp r2, #0x0
	blt _020E9AF0
	cmp r2, #0x80
	bge _020E9AF0
	ldrb r2, [r3, r2]
_020E9AF0:
	ldrb lr, [r1], #0x1
	and r12, r2, #0xff
	cmp lr, #0x0
	blt _020E9B0C
	cmp lr, #0x80
	bge _020E9B0C
	ldrb lr, [r3, lr]
_020E9B0C:
	and r2, lr, #0xff
	cmp r12, r2
	mvncc r0, #0x0
	ldmccia sp!, {r3,pc}
	movhi r0, #0x1
	ldmhiia sp!, {r3,pc}
	cmp r12, #0x0
	bne _020E9AD8
	mov r0, #0x0
	ldmia sp!, {r3,pc}
	.balign 4
_020E9B34: .word __lower_mapC

	arm_func_start strnicmp
strnicmp: ; 0x020E9B38
	ldr ip, _020E9B40 ; =stricmp
	bx r12
	.balign 4
_020E9B40: .word stricmp
