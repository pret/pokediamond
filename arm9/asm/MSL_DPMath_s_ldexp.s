	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start ldexp
ldexp: ; 0x020E8318
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4,lr}
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	mov r4, r2
	bl __fpclassifyf
	cmp r0, #0x2
	ble _020E8350
	mov r0, #0x0
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	mov r1, r0
	bl _deq
	bne _020E8364
_020E8350:
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E8364:
	ldr r3, [sp, #0xc]
	ldr r0, _020E8538 ; =0x7FF00000
	ldr r1, [sp, #0x8]
	and r0, r3, r0
	movs r12, r0, asr #0x14
	bne _020E83F0
	bic r0, r3, #0x80000000
	orrs r0, r1, r0
	ldreq r0, [sp, #0x8]
	ldreq r1, [sp, #0xc]
	ldmeqia sp!, {r4,lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	ldr r3, _020E853C ; =0x43500000
	mov r2, #0x0
	bl _dmul
	mov r3, r1
	ldr r1, _020E8538 ; =0x7FF00000
	ldr ip, _020E8540 ; =0xFFFF3CB0
	and r1, r3, r1
	mov r2, r0
	mov r0, r1, asr #0x14
	str r2, [sp, #0x8]
	str r3, [sp, #0xc]
	cmp r4, r12
	sub r12, r0, #0x36
	bge _020E83F0
	ldr r0, _020E8544 ; =0xC2F8F359
	ldr r1, _020E8548 ; =0x01A56E1F
	bl _dmul
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E83F0:
	ldr r0, _020E854C ; =0x000007FF
	cmp r12, r0
	bne _020E841C
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	mov r2, r0
	mov r3, r1
	bl _dadd
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E841C:
	add r2, r12, r4
	sub r0, r0, #0x1
	cmp r2, r0
	ble _020E8460
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	ldr r0, _020E8550 ; =0x8800759C
	ldr r1, _020E8554 ; =0x7E37E43C
	bl copysign
	mov r2, r0
	mov r3, r1
	ldr r0, _020E8550 ; =0x8800759C
	ldr r1, _020E8554 ; =0x7E37E43C
	bl _dmul
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E8460:
	cmp r2, #0x0
	ble _020E8488
	ldr r1, _020E8558 ; =0x800FFFFF
	ldr r0, [sp, #0x8]
	and r1, r3, r1
	orr r1, r1, r2, lsl #0x14
	str r1, [sp, #0xc]
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E8488:
	mvn r0, #0x35
	cmp r2, r0
	bgt _020E8508
	ldr r0, _020E855C ; =0x0000C350
	cmp r4, r0
	ble _020E84D4
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	ldr r0, _020E8550 ; =0x8800759C
	ldr r1, _020E8554 ; =0x7E37E43C
	bl copysign
	mov r2, r0
	mov r3, r1
	ldr r0, _020E8550 ; =0x8800759C
	ldr r1, _020E8554 ; =0x7E37E43C
	bl _dmul
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E84D4:
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	ldr r0, _020E8544 ; =0xC2F8F359
	ldr r1, _020E8548 ; =0x01A56E1F
	bl copysign
	mov r2, r0
	mov r3, r1
	ldr r0, _020E8544 ; =0xC2F8F359
	ldr r1, _020E8548 ; =0x01A56E1F
	bl _dmul
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E8508:
	ldr r0, _020E8558 ; =0x800FFFFF
	add r1, r2, #0x36
	and r0, r3, r0
	orr r3, r0, r1, lsl #0x14
	ldr r2, [sp, #0x8]
	ldr r1, _020E8560 ; =0x3C900000
	mov r0, #0x0
	str r3, [sp, #0xc]
	bl _dmul
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E8538: .word 0x7FF00000
_020E853C: .word 0x43500000
_020E8540: .word 0xFFFF3CB0
_020E8544: .word 0xC2F8F359
_020E8548: .word 0x01A56E1F
_020E854C: .word 0x000007FF
_020E8550: .word 0x8800759C
_020E8554: .word 0x7E37E43C
_020E8558: .word 0x800FFFFF
_020E855C: .word 0x0000C350
_020E8560: .word 0x3C900000
    arm_func_end ldexp

    .section .exceptix,4

	.word ldexp
	.short 589
	.word 0x00300120
