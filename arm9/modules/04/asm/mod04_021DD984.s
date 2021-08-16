	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD04_021DD984
MOD04_021DD984: ; 0x021DD984
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD04_021DDCE8
	bl MOD04_021DDB14
	cmp r0, #0
	beq _021DD9CC
	bl MOD04_021EBAB8
	mov r2, r0
	cmp r2, #0x63
	ldr r1, _021DD9D8 ; =0xFFFF2D10
	movhi r2, #0x63
	mov r0, #8
	sub r1, r1, r2
	bl MOD04_021DD6B0
	bl MOD04_021DDBBC
	add sp, sp, #4
	mov r0, #1
	ldmfd sp!, {pc}
_021DD9CC:
	mov r0, #0
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DD9D8: .word 0xFFFF2D10
	arm_func_end MOD04_021DD984

	arm_func_start MOD04_021DD9DC
MOD04_021DD9DC: ; 0x021DD9DC
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x18
	mov r1, #0
	mov r2, #0x3c
	mov r4, r0
	bl MI_CpuFill8
	mov r0, #0xff
	str r0, [r4, #4]
	bl MOD04_021DDC1C
	cmp r0, #4
	addne sp, sp, #0x18
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	bl MOD04_021EBAB8
	str r0, [r4]
	bl OS_DisableInterrupts
	mov r6, r0
	bl WCM_GetApMacAddress
	mov r5, r0
	mov r1, #6
	bl DC_InvalidateRange
	cmp r5, #0
	bne _021DDA4C
	mov r0, r6
	bl OS_RestoreInterrupts
	add sp, sp, #0x18
	mov r0, #0
	ldmia sp!, {r4, r5, r6, pc}
_021DDA4C:
	mov r0, r5
	add r1, r4, #0x33
	mov r2, #6
	bl MI_CpuCopy8
	ldr r0, [r4]
	cmp r0, #0
	blt _021DDAB0
	cmp r0, #3
	bge _021DDAB0
	add r0, sp, #0
	bl WCM_GetApEssid
	mov r5, r0
	mov r1, #0x20
	bl DC_InvalidateRange
	cmp r5, #0
	bne _021DDAA0
	mov r0, r6
	bl OS_RestoreInterrupts
	add sp, sp, #0x18
	mov r0, #0
	ldmia sp!, {r4, r5, r6, pc}
_021DDAA0:
	ldrh r2, [sp]
	mov r0, r5
	add r1, r4, #0x12
	bl MI_CpuCopy8
_021DDAB0:
	mov r0, r6
	bl OS_RestoreInterrupts
	add r0, sp, #2
	mov r1, #0
	mov r2, #0x10
	bl MI_CpuFill8
	add r0, sp, #2
	bl MOD04_021EBA28
	cmp r0, #1
	bne _021DDAFC
	ldrb r1, [sp, #8]
	cmp r1, #0
	beq _021DDAFC
	sub r3, r1, #0x30
	add r0, sp, #9
	add r1, r4, #8
	mov r2, #9
	str r3, [r4, #4]
	bl MI_CpuCopy8
_021DDAFC:
	mov r0, #1
	add sp, sp, #0x18
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD04_021DD9DC

	arm_func_start MOD04_021DDB08
MOD04_021DDB08: ; 0x021DDB08
	ldr ip, _021DDB10 ; =WCM_GetLinkLevel
	bx ip
	.align 2, 0
_021DDB10: .word WCM_GetLinkLevel
	arm_func_end MOD04_021DDB08

	arm_func_start MOD04_021DDB14
MOD04_021DDB14: ; 0x021DDB14
	ldr r0, _021DDB3C ; =UNK04_02210518
	ldr r0, [r0]
	cmp r0, #0
	beq _021DDB34
	ldrh r0, [r0, #4]
	cmp r0, #6
	moveq r0, #1
	bxeq lr
_021DDB34:
	mov r0, #0
	bx lr
	.align 2, 0
_021DDB3C: .word UNK04_02210518
	arm_func_end MOD04_021DDB14

	arm_func_start MOD04_021DDB40
MOD04_021DDB40: ; 0x021DDB40
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021DDBB8 ; =UNK04_02210518
	ldr r2, [r0]
	cmp r2, #0
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	ldrh r1, [r2, #4]
	cmp r1, #8
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {pc}
	cmp r1, #1
	moveq r1, #0
	streq r1, [r0]
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	mov r0, #5
	strh r0, [r2, #4]
	bl MOD04_021EB9D8
	cmp r0, #0
	ldrne r0, _021DDBB8 ; =UNK04_02210518
	movne r1, #0
	strne r1, [r0]
	movne r0, #1
	moveq r0, #0
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DDBB8: .word UNK04_02210518
	arm_func_end MOD04_021DDB40

	arm_func_start MOD04_021DDBBC
MOD04_021DDBBC: ; 0x021DDBBC
	stmdb sp!, {r4, lr}
	ldr r0, _021DDC18 ; =UNK04_02210518
	ldr r1, [r0]
	cmp r1, #0
	ldmeqia sp!, {r4, pc}
	ldrh r1, [r1, #4]
	cmp r1, #1
	moveq r1, #0
	streq r1, [r0]
	ldmeqia sp!, {r4, pc}
	bl MOD04_021EB9D8
	cmp r0, #0
	bne _021DDC08
	mov r4, #0xa
_021DDBF4:
	mov r0, r4
	bl OS_Sleep
	bl MOD04_021EB9D8
	cmp r0, #0
	beq _021DDBF4
_021DDC08:
	ldr r0, _021DDC18 ; =UNK04_02210518
	mov r1, #0
	str r1, [r0]
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DDC18: .word UNK04_02210518
	arm_func_end MOD04_021DDBBC

	arm_func_start MOD04_021DDC1C
MOD04_021DDC1C: ; 0x021DDC1C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021DDCE4 ; =UNK04_02210518
	ldr r0, [r0]
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {pc}
	ldrh r0, [r0, #4]
	cmp r0, #1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD04_021EBAE8
	mov r1, r0
	cmp r1, #5
	bne _021DDC80
	ldr r1, _021DDCE4 ; =UNK04_02210518
	mov r0, #4
	ldr r3, [r1]
	mov r2, #1
	strh r0, [r3, #4]
	ldr r1, [r1]
	add sp, sp, #4
	strh r2, [r1, #6]
	ldmfd sp!, {pc}
_021DDC80:
	cmp r1, #0
	bge _021DDCD8
	mvn r0, #9
	cmp r1, r0
	blt _021DDCB8
	sub r1, r1, #0x2bc
	mov r0, #9
	bl MOD04_021DD6B0
	ldr r1, _021DDCE4 ; =UNK04_02210518
	mov r0, #8
	ldr r1, [r1]
	add sp, sp, #4
	strh r0, [r1, #4]
	ldmfd sp!, {pc}
_021DDCB8:
	mov r0, #5
	bl MOD04_021DD6B0
	ldr r1, _021DDCE4 ; =UNK04_02210518
	mov r0, #7
	ldr r1, [r1]
	add sp, sp, #4
	strh r0, [r1, #4]
	ldmfd sp!, {pc}
_021DDCD8:
	mov r0, #2
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DDCE4: .word UNK04_02210518
	arm_func_end MOD04_021DDC1C

	arm_func_start MOD04_021DDCE8
MOD04_021DDCE8: ; 0x021DDCE8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021DDD78 ; =UNK04_02210518
	ldr r1, [r0]
	cmp r1, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldrh r0, [r1, #4]
	cmp r0, #2
	bne _021DDD28
	bl MOD04_021EBB80
	ldr r1, _021DDD78 ; =UNK04_02210518
	add sp, sp, #4
	ldr r1, [r1]
	str r0, [r1]
	ldmfd sp!, {pc}
_021DDD28:
	cmp r0, #4
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldrh r0, [r1, #6]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl WCM_GetPhase
	cmp r0, #9
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _021DDD78 ; =UNK04_02210518
	mov r3, #0
	ldr r2, [r0]
	mov r1, #6
	strh r3, [r2, #6]
	ldr r0, [r0]
	strh r1, [r0, #4]
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DDD78: .word UNK04_02210518
	arm_func_end MOD04_021DDCE8

	arm_func_start MOD04_021DDD7C
MOD04_021DDD7C: ; 0x021DDD7C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021DDDC8 ; =UNK04_02210518
	ldr r1, [r0]
	cmp r1, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {pc}
	ldr r0, [r1]
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {pc}
	mov r0, #3
	strh r0, [r1, #4]
	bl MOD04_021DDC1C
	mov r0, #1
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DDDC8: .word UNK04_02210518
	arm_func_end MOD04_021DDD7C

	arm_func_start MOD04_021DDDCC
MOD04_021DDDCC: ; 0x021DDDCC
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r0, _021DDE70 ; =UNK04_02210518
	ldr r0, [r0]
	cmp r0, #0
	beq _021DDE5C
	ldrh r0, [r0, #4]
	cmp r0, #1
	addne sp, sp, #0xc
	ldmneia sp!, {pc}
	add r0, sp, #0
	mov r1, #0
	mov r2, #0xc
	bl MI_CpuFill8
	ldr r0, _021DDE70 ; =UNK04_02210518
	ldr r3, _021DDE74 ; =MOD04_021DD944
	ldr lr, [r0]
	ldr r2, _021DDE78 ; =MOD04_021DD904
	ldrh ip, [lr, #8]
	add r0, sp, #0
	mov r1, #2
	strb ip, [sp, #8]
	ldrh ip, [lr, #0xa]
	strb ip, [sp, #9]
	str r3, [sp]
	str r2, [sp, #4]
	strh r1, [lr, #4]
	bl MOD04_021EBC60
	cmp r0, #0
	addne sp, sp, #0xc
	ldmneia sp!, {pc}
	mov r0, #9
	mvn r1, #5
	bl MOD04_021DD6B0
	add sp, sp, #0xc
	ldmfd sp!, {pc}
_021DDE5C:
	mov r0, #9
	mvn r1, #3
	bl MOD04_021DD6B0
	add sp, sp, #0xc
	ldmfd sp!, {pc}
	.align 2, 0
_021DDE70: .word UNK04_02210518
_021DDE74: .word MOD04_021DD944
_021DDE78: .word MOD04_021DD904
	arm_func_end MOD04_021DDDCC

	arm_func_start MOD04_021DDE7C
MOD04_021DDE7C: ; 0x021DDE7C
	stmdb sp!, {lr}
	sub sp, sp, #4
	cmp r0, #0
	beq _021DDEA4
	cmp r0, #1
	beq _021DDEB4
	cmp r0, #2
	beq _021DDEC4
	add sp, sp, #4
	ldmfd sp!, {pc}
_021DDEA4:
	ldr r0, _021DDED4 ; =UNK04_0220D280
	bl MOD04_021D9C1C
	add sp, sp, #4
	ldmfd sp!, {pc}
_021DDEB4:
	ldr r0, _021DDED8 ; =UNK04_0220D2A8
	bl MOD04_021D9C1C
	add sp, sp, #4
	ldmfd sp!, {pc}
_021DDEC4:
	ldr r0, _021DDEDC ; =UNK04_0220D2CC
	bl MOD04_021D9C1C
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DDED4: .word UNK04_0220D280
_021DDED8: .word UNK04_0220D2A8
_021DDEDC: .word UNK04_0220D2CC
	arm_func_end MOD04_021DDE7C

	arm_func_start MOD04_021DDEE0
MOD04_021DDEE0: ; 0x021DDEE0
	stmdb sp!, {r4, r5, r6, lr}
	ldr r2, _021DDF3C ; =UNK04_02210518
	mov r6, r0
	ldr r2, [r2]
	mov r5, r1
	mov r4, r3
	cmp r2, #0
	ldmneia sp!, {r4, r5, r6, pc}
	mov r1, #0
	mov r2, #0xc
	bl MI_CpuFill8
	strh r5, [r6, #8]
	mov r0, #1
	strh r0, [r6, #0xa]
	strh r0, [r6, #4]
	mov r0, #0
	ldr r1, _021DDF3C ; =UNK04_02210518
	strh r0, [r6, #6]
	str r6, [r1]
	bl MOD04_021DDE7C
	mov r0, r4
	bl CPS_SetSslHandshakePriority
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021DDF3C: .word UNK04_02210518
	arm_func_end MOD04_021DDEE0

	.section .data

	.global UNK04_0220D280
UNK04_0220D280: ; 0x0220D280
	.asciz "https://nas.test.nintendowifi.net/ac"

	.balign 4, 0
	.global UNK04_0220D2A8
UNK04_0220D2A8: ; 0x0220D2A8
	.asciz "https://nas.dev.nintendowifi.net/ac"

	.balign 4, 0
	.global UNK04_0220D2CC
UNK04_0220D2CC: ; 0x0220D2CC
	.asciz "https://nas.nintendowifi.net/ac"

	.balign 4, 0
	.section .bss

	.global UNK04_02210518
UNK04_02210518: ; 0x02210518
	.space 0x4
