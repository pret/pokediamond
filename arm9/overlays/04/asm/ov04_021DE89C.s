	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start ov04_021DE89C
ov04_021DE89C: ; 0x021DE89C
	ldrh r1, [r0]
	mov r2, #0
	cmp r1, #0
	beq _021DE8C0
_021DE8AC:
	add r2, r2, #1
	mov r1, r2, lsl #1
	ldrh r1, [r0, r1]
	cmp r1, #0
	bne _021DE8AC
_021DE8C0:
	mov r0, r2
	bx lr
	arm_func_end ov04_021DE89C

	arm_func_start ov04_021DE8C8
ov04_021DE8C8: ; 0x021DE8C8
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r2, _021DE9E4 ; =ov04_02210524
	mov r1, #0
	ldr r3, [r2, #4]
	ldr ip, [r2]
	cmp r3, r1
	mov r4, r0
	cmpeq ip, r1
	bne _021DE98C
	ldr r0, [r2, #0xc]
	ldr r3, [r2, #8]
	cmp r0, r1
	cmpeq r3, r1
	bne _021DE98C
	ldr r0, [r2, #0x14]
	ldr r2, [r2, #0x10]
	cmp r0, r1
	cmpeq r2, r1
	bne _021DE98C
	add r0, sp, #0
	bl OS_GetMacAddress
	bl OS_GetTick
	ldr r2, [sp]
	ldr r3, [sp, #4]
	mov lr, r2, lsr #0x18
	mov r2, r1, lsl #0x18
	orr lr, lr, r3, lsl #8
	mvn r1, #0xff000000
	mov ip, r3, lsr #0x18
	and r1, lr, r1
	orr r3, r1, r0, lsl #24
	and r1, ip, #0
	orr r2, r2, r0, lsr #8
	orr r1, r1, r2
	str r1, [sp, #4]
	ldr ip, _021DE9E4 ; =ov04_02210524
	add r0, sp, #0
	str r3, [sp]
	ldmia r0, {r2, r3}
	stmia ip, {r2, r3}
	ldr r3, _021DE9E8 ; =0x6C078965
	ldr r2, _021DE9EC ; =0x5D588B65
	ldr r1, _021DE9F0 ; =0x00269EC3
	mov r0, #0
	str r3, [ip, #8]
	str r2, [ip, #0xc]
	str r1, [ip, #0x10]
	str r0, [ip, #0x14]
_021DE98C:
	ldr r1, _021DE9E4 ; =ov04_02210524
	ldr r3, [r1, #8]
	ldr r2, [r1]
	ldr r0, [r1, #4]
	umull lr, ip, r3, r2
	mla ip, r3, r0, ip
	ldr r0, [r1, #0xc]
	ldr r3, [r1, #0x10]
	mla ip, r0, r2, ip
	adds r2, r3, lr
	ldr r0, [r1, #0x14]
	str r2, [r1]
	adc r0, r0, ip
	cmp r4, #0
	str r0, [r1, #4]
	movne r3, #0
	umullne r2, r1, r0, r4
	mlane r1, r0, r3, r1
	mlane r1, r3, r4, r1
	movne r0, r1
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DE9E4: .word ov04_02210524
_021DE9E8: .word 0x6C078965
_021DE9EC: .word 0x5D588B65
_021DE9F0: .word 0x00269EC3
	arm_func_end ov04_021DE8C8

	arm_func_start ov04_021DE9F4
ov04_021DE9F4: ; 0x021DE9F4
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	movs r4, r1
	mov r7, r0
	mov r6, r3
	addeq sp, sp, #4
	mvneq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	mov r0, r2
	mov r1, r6
	bl strchr
	movs r5, r0
	addeq sp, sp, #4
	mvneq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
_021DEA30:
	mov r0, r7
	bl strlen
	mov r2, r0
	mov r1, r7
	add r0, r5, #1
	bl strncmp
	cmp r0, #0
	bne _021DEA68
	mov r0, r7
	bl strlen
	add r0, r0, r5
	ldrsb r0, [r0, #1]
	cmp r6, r0
	beq _021DEAA4
_021DEA68:
	mov r1, r6
	add r0, r5, #1
	bl strchr
	cmp r0, #0
	addeq sp, sp, #4
	mvneq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	mov r1, r6
	add r0, r0, #1
	bl strchr
	movs r5, r0
	bne _021DEA30
	add sp, sp, #4
	mvn r0, #0
	ldmia sp!, {r4, r5, r6, r7, pc}
_021DEAA4:
	mov r1, r6
	add r0, r5, #1
	bl strchr
	movs r5, r0
	addeq sp, sp, #4
	mvneq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	mov r1, r6
	add r0, r5, #1
	bl strchr
	cmp r0, #0
	addne r1, r5, #1
	subne r6, r0, r1
	bne _021DEAE8
	add r0, r5, #1
	bl strlen
	mov r6, r0
_021DEAE8:
	mov r0, r4
	mov r2, r6
	add r1, r5, #1
	bl strncpy
	mov r1, #0
	mov r0, r6
	strb r1, [r4, r6]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	arm_func_end ov04_021DE9F4

	arm_func_start ov04_021DEB0C
ov04_021DEB0C: ; 0x021DEB0C
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r5, r2
	mov r7, r0
	mov r6, r1
	mov r4, r3
	mov r0, r5
	mov r1, #0
	bl strchr
	mov r2, r0
	mov r0, r7
	mov r1, r6
	mov r3, r4
	bl ov04_021DEB54
	mov r0, r5
	bl strlen
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	arm_func_end ov04_021DEB0C

	arm_func_start ov04_021DEB54
ov04_021DEB54: ; 0x021DEB54
	stmdb sp!, {r4, lr}
	sub sp, sp, #0x10
	str r0, [sp]
	mov r4, r2
	str r3, [sp, #4]
	str r1, [sp, #8]
	ldr r2, _021DEB8C ; =ov04_0220D328
	mov r0, r4
	mov r1, #0x1000
	bl OS_SNPrintf
	mov r0, r4
	bl strlen
	add sp, sp, #0x10
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DEB8C: .word ov04_0220D328
	arm_func_end ov04_021DEB54

	.section .data

	.global ov04_0220D328
ov04_0220D328: ; 0x0220D328
	.asciz "%c%s%c%s"

	.balign 4, 0

	.section .bss

	.global ov04_02210524
ov04_02210524: ; 0x02210524
	.space 0x18
