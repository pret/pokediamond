	.include "asm/macros.inc"

	.text

	arm_func_start Entry
Entry: @ 0x02000800
	mov ip, #0x4000000
	str ip, [ip, #0x208]
_02000808:
	ldrh r0, [ip, #6]
	cmp r0, #0
	bne _02000808
	bl sub_2000A78
	mov r0, #0x13
	msr cpsr_c, r0
	ldr r0, _02000918 @ =0x027E0000
	add r0, r0, #0x3fc0
	mov sp, r0
	mov r0, #0x12
	msr cpsr_c, r0
	ldr r0, _02000918 @ =0x027E0000
	add r0, r0, #0x3fc0
	sub r0, r0, #0x40
	sub sp, r0, #4
	tst sp, #4
	subeq sp, sp, #4
	ldr r1, _0200091C @ =0x00000400
	sub r1, r0, r1
	mov r0, #0x1f
	msr cpsr_fsxc, r0
	sub sp, r1, #4
	mov r0, #0
	ldr r1, _02000918 @ =0x027E0000
	mov r2, #0x4000
	bl sub_200093C
	mov r0, #0
	ldr r1, _02000920 @ =0x05000000
	mov r2, #1024
	bl sub_200093C
	mov r0, #512
	ldr r1, _02000924 @ =0x07000000
	mov r2, #1024
	bl sub_200093C
	ldr r1, _02000928 @ = _02000B68
	ldr r0, [r1, #20]
	bl sub_2000950
	bl sub_20009FC
	ldr r0, _02000928 @ =_02000B68
	ldr r1, [r0, #12]
	ldr r2, [r0, #16]
	mov r3, r1
	mov r0, #0
_020008B4:
	cmp r1, r2
	strcc r0, [r1], #4
	bcc _020008B4
	bic r1, r3, #31
_020008C4:
	mcr p15, #0, r0, cr7, cr10, 4
	mcr p15, #0, r1, cr7, cr5, 1
	mcr p15, #0, r1, cr7, cr14, 1
	add r1, #32
	cmp r1, r2
	blt _020008C4
	ldr r1, _0200092C @ =0x027FFF9C
	str r0, [r1]
	ldr r1, _02000918 @ =0x027E0000
	add r1, r1, #16320
	add r1, r1, #60
	ldr r0, _02000930 @ =0x01FF8000
	str r0, [r1]
	bl sub_20EC5CC
	bl sub_2000B64_dummy
	bl sub_20EC694
	ldr r1, _02000934 @ =0x02000C55
	ldr lr, _02000938 @ =0xFFFF0000
	tst sp, #4
	subne sp, sp, #4
	bx r1
_02000918: .4byte 0x027E0000
_0200091C: .4byte 0x00000400
_02000920: .4byte 0x05000000
_02000924: .4byte 0x07000000
_02000928: .4byte _02000B68
_0200092C: .4byte 0x027FFF9C
_02000930: .4byte 0x01FF8000
_02000934: .4byte NdsMain+1
_02000938: .4byte 0xFFFF0000
	arm_func_end Entry

	arm_func_start sub_200093C
sub_200093C:
	add ip, r1, r2
_02000940:
	cmp r1, ip
	stmlt r1!, {r0}
	blt _02000940
	bx lr
	arm_func_end sub_200093C

	arm_func_start sub_2000950
sub_2000950:
	cmp r0, #0
	beq _020009F8
	push {r4, r5, r6, r7}
	ldmdb r0, {r1, r2}
	add r2, r0, r2
	sub r3, r0, r1, lsr #24
	bic r1, r1, #-16777216
	sub r1, r0, r1
	mov r4, r2
_02000974:
	cmp r3, r1
	ble _020009D4
	ldrb r5, [r3, #-1]!
	mov r6, #8
_02000984:
	subs r6, r6, #1
	blt _02000974
	tst r5, #128
	bne _020009A0
	ldrb r0, [r3, #-1]!
	strb r0, [r2, #-1]!
	b _020009C8
_020009A0:
	ldrb ip, [r3, #-1]!
	ldrb r7, [r3, #-1]!
	orr r7, r7, ip, lsl #8
	bic r7, r7, #61440
	add r7, r7, #2
	add ip, ip, #32
_020009B8:
	ldrb r0, [r2, r7]
	strb r0, [r2, #-1]!
	subs ip, ip, #16
	bge _020009B8
_020009C8:
	cmp r3, r1
	lsl r5, r5, #1
	bgt _02000984
_020009D4:
	mov r0, #0
	bic r3, r1, #31
_020009DC:
	mcr p15, #0, r0, cr7, cr10, 4
	mcr p15, #0, r3, cr7, cr5, 1
	mcr p15, #0, r3, cr7, cr14, 1
	add r3, r3, #32
	cmp r3, r4
	blt _020009DC
	pop {r4, r5, r6, r7}
_020009F8:
	bx lr
	arm_func_end sub_2000950

	arm_func_start sub_20009FC
sub_20009FC:
	ldr r0, _02000A70 @ =_02000B68
	ldr r1, [r0]
	ldr r2, [r0, #4]
	ldr r3, [r0, #8]
_02000A0C:
	cmp r1, r2
	beq _02000A6C
	ldr r5, [r1], #4
	ldr r7, [r1], #4
	add r6, r5, r7
	mov r4, r5
_02000A24:
	cmp r4, r6
	ldrmi r7, [r3], #4
	strmi r7, [r4], #4
	bmi _02000A24
	ldr r7, [r1], #4
	add r6, r4, r7
	mov r7, #0
_02000A40:
	cmp r4, r6
	strcc r7, [r4], #4
	bcc _02000A40
	bic r4, r5, #31
_02000A50:
	mcr p15, #0, r7, cr7, cr10, 4
	mcr p15, #0, r4, cr7, cr5, 1
	mcr p15, #0, r4, cr7, cr14, 1
	add r4, r4, #32
	cmp r4, r6
	blt _02000A50
	b _02000A0C
_02000A6C:
	b _02000A74
_02000A70: .4byte _02000B68
_02000A74:
	bx lr
	arm_func_end sub_20009FC

	arm_func_start sub_2000A78
sub_2000A78: @ 0x02000A78
	mrc p15, #0, r0, c1, c0, #0
	ldr r1, _02000B30 @ =0x000F9005
	bic r0, r0, r1
	mcr p15, #0, r0, c1, c0, #0
	mov r0, #0
	mcr p15, #0, r0, c7, c5, #0
	mcr p15, #0, r0, c7, c6, #0
	mcr p15, #0, r0, c7, c10, #4
	ldr r0, _02000B34 @ =0x04000033
	mcr p15, #0, r0, c6, c0, #0
	ldr r0, _02000B38 @ =0x0200002D
	mcr p15, #0, r0, c6, c1, #0
	ldr r0, _02000B3C @ =0x027E0021
	mcr p15, #0, r0, c6, c2, #0
	ldr r0, _02000B40 @ =0x08000035
	mcr p15, #0, r0, c6, c3, #0
	ldr r0, _02000B44 @ =0x027E0000
	orr r0, r0, #0x1a
	orr r0, r0, #1
	mcr p15, #0, r0, c6, c4, #0
	ldr r0, _02000B48 @ =0x0100002F
	mcr p15, #0, r0, c6, c5, #0
	ldr r0, _02000B4C @ =0xFFFF001D
	mcr p15, #0, r0, c6, c6, #0
	ldr r0, _02000B50 @ =0x027FF017
	mcr p15, #0, r0, c6, c7, #0
	mov r0, #0x20
	mcr p15, #0, r0, c9, c1, #1
	ldr r0, _02000B44 @ =0x027E0000
	orr r0, r0, #0xa
	mcr p15, #0, r0, c9, c1, #0
	mov r0, #0x42
	mcr p15, #0, r0, c2, c0, #1
	mov r0, #0x42
	mcr p15, #0, r0, c2, c0, #0
	mov r0, #2
	mcr p15, #0, r0, c3, c0, #0
	ldr r0, _02000B54 @ =0x05100011
	mcr p15, #0, r0, c5, c0, #3
	ldr r0, _02000B58 @ =0x15111011
	mcr p15, #0, r0, c5, c0, #2
	mrc p15, #0, r0, c1, c0, #0
	ldr r1, _02000B5C @ =0x0005707D
	orr r0, r0, r1
	mcr p15, #0, r0, c1, c0, #0
	bx lr
	.align 2, 0
_02000B30: .4byte 0x000F9005
_02000B34: .4byte 0x04000033
_02000B38: .4byte 0x0200002D
_02000B3C: .4byte 0x027E0021
_02000B40: .4byte 0x08000035
_02000B44: .4byte 0x027E0000
_02000B48: .4byte 0x0100002F
_02000B4C: .4byte 0xFFFF001D
_02000B50: .4byte 0x027FF017
_02000B54: .4byte 0x05100011
_02000B58: .4byte 0x15111011
_02000B5C: .4byte 0x0005707D

	arm_func_start sub_2000B60_dummy
sub_2000B60_dummy: @ 0x02000B60
	bx lr

	arm_func_start sub_2000B64_dummy
sub_2000B64_dummy: @ 0x02000B64
	bx lr
_02000B68:
	.word 0x02107700
	.word 0x02107724
	.word 0x02106FA0
	.word 0x02106FA0
	.word 0x021D74E0
	.word 0x00000000

	.byte 0x31, 0x75, 0x02, 0x03, 0x21, 0x06, 0xC0, 0xDE, 0xDE, 0xC0, 0x06, 0x21
	
	# strings
	.balign 4
	.asciz "[SDK+NINTENDO:DWC1.2.30006.061019.2254_DWC_1_2_PLUS6]"
	.balign 4
	.asciz "[SDK+NINTENDO:WiFi1.2.30000.0609050341]"
	.balign 4
	.asciz "[SDK+UBIQUITOUS:CPS]"
	.balign 4
	.asciz "[SDK+UBIQUITOUS:SSL]"
	.balign 4
	.asciz "[SDK+Abiosso:libVCT 1.0.1_ec]"
	.balign 4
	.asciz "[SDK+NINTENDO:BACKUP]"
