	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD04_021DCCC8
MOD04_021DCCC8: ; 0x021DCCC8
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r0, _021DCED4 ; =UNK04_02210504
	mov r1, #0
	ldr r0, [r0]
	add r4, r0, #8
	mov r0, r4
	bl MOD04_021DA3DC
	cmp r0, #0
	bne _021DCD08
	ldr r1, _021DCED8 ; =0xFFFF9DF3
	mov r0, #0x10
	bl MOD04_021DD6B0
	add sp, sp, #8
	mov r0, #0
	ldmia sp!, {r4, pc}
_021DCD08:
	ldr r1, _021DCEDC ; =UNK04_0220C5A0
	mov r0, r4
	bl MOD04_021DA388
	cmp r0, #0
	beq _021DCD20
	bl MOD04_021DCA84
_021DCD20:
	ldr r1, _021DCEE0 ; =UNK04_0220C5A8
	mov r0, r4
	bl MOD04_021DA388
	cmp r0, #0
	bne _021DCD4C
	ldr r1, _021DCED8 ; =0xFFFF9DF3
	mov r0, #0x10
	bl MOD04_021DD6B0
	add sp, sp, #8
	mov r0, #0
	ldmia sp!, {r4, pc}
_021DCD4C:
	bl atol
	ldr r1, _021DCEE4 ; =errno
	mov r2, r0
	ldr r0, [r1]
	cmp r0, #0x22
	bne _021DCD7C
	ldr r1, _021DCED8 ; =0xFFFF9DF3
	mov r0, #0x10
	bl MOD04_021DD6B0
	add sp, sp, #8
	mov r0, #0
	ldmia sp!, {r4, pc}
_021DCD7C:
	cmp r2, #0xc8
	beq _021DCDA0
	ldr r1, _021DCEE8 ; =0xFFFF9E58
	mov r0, #0x10
	sub r1, r1, r2
	bl MOD04_021DD6B0
	add sp, sp, #8
	mov r0, #0
	ldmia sp!, {r4, pc}
_021DCDA0:
	ldr r1, _021DCEEC ; =UNK04_0220C5B4
	add r2, sp, #0
	mov r0, r4
	mov r3, #4
	bl MOD04_021DA334
	cmp r0, #0
	bgt _021DCDD4
	ldr r1, _021DCED8 ; =0xFFFF9DF3
	mov r0, #0x10
	bl MOD04_021DD6B0
	add sp, sp, #8
	mov r0, #0
	ldmia sp!, {r4, pc}
_021DCDD4:
	add r0, sp, #0
	bl atol
	ldr r1, _021DCEE4 ; =errno
	mov r2, r0
	ldr r0, [r1]
	cmp r0, #0x22
	bne _021DCE08
	ldr r1, _021DCED8 ; =0xFFFF9DF3
	mov r0, #0x10
	bl MOD04_021DD6B0
	add sp, sp, #8
	mov r0, #0
	ldmia sp!, {r4, pc}
_021DCE08:
	cmp r2, #0x64
	blt _021DCE2C
	ldr r1, _021DCEF0 ; =0xFFFFA240
	mov r0, #0x10
	sub r1, r1, r2
	bl MOD04_021DD6B0
	add sp, sp, #8
	mov r0, #0
	ldmia sp!, {r4, pc}
_021DCE2C:
	ldr r0, _021DCED4 ; =UNK04_02210504
	ldr r1, _021DCEF4 ; =UNK04_0220C5C0
	ldr r2, [r0]
	mov r0, r4
	add r2, r2, #0x1000
	ldr r2, [r2, #0xc18]
	mov r3, #0x40
	add r2, r2, #4
	bl MOD04_021DA334
	ldr r0, _021DCED4 ; =UNK04_02210504
	ldr r1, _021DCEF8 ; =UNK04_0220C5C8
	ldr r2, [r0]
	mov r0, r4
	add r2, r2, #0x1000
	ldr r2, [r2, #0xc18]
	mov r3, #0x12c
	add r2, r2, #0x45
	bl MOD04_021DA334
	ldr r1, _021DCEFC ; =UNK04_0220C5D8
	add r2, sp, #0
	mov r0, r4
	mov r3, #1
	bl MOD04_021DA334
	ldrsb r0, [sp]
	cmp r0, #0x59
	bne _021DCEB0
	ldr r0, _021DCED4 ; =UNK04_02210504
	mov r1, #1
	ldr r0, [r0]
	add r0, r0, #0x1000
	ldr r0, [r0, #0xc18]
	str r1, [r0]
	b _021DCEC8
_021DCEB0:
	ldr r0, _021DCED4 ; =UNK04_02210504
	mov r1, #0
	ldr r0, [r0]
	add r0, r0, #0x1000
	ldr r0, [r0, #0xc18]
	str r1, [r0]
_021DCEC8:
	mov r0, #1
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DCED4: .word UNK04_02210504
_021DCED8: .word 0xFFFF9DF3
_021DCEDC: .word UNK04_0220C5A0
_021DCEE0: .word UNK04_0220C5A8
_021DCEE4: .word errno
_021DCEE8: .word 0xFFFF9E58
_021DCEEC: .word UNK04_0220C5B4
_021DCEF0: .word 0xFFFFA240
_021DCEF4: .word UNK04_0220C5C0
_021DCEF8: .word UNK04_0220C5C8
_021DCEFC: .word UNK04_0220C5D8
	arm_func_end MOD04_021DCCC8

	arm_func_start MOD04_021DCF00
MOD04_021DCF00: ; 0x021DCF00
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021DCFF0 ; =UNK04_02210504
	ldr r1, [r0]
	cmp r1, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {pc}
	add r0, r1, #0x1000
	ldr r0, [r0, #0xba8]
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	ldr r0, _021DCFF4 ; =0x00001B3C
	add r0, r1, r0
	bl OS_IsThreadTerminated
	cmp r0, #1
	bne _021DCFE4
	ldr r0, _021DCFF0 ; =UNK04_02210504
	ldr r1, [r0]
	add r0, r1, #0x1000
	ldr r0, [r0, #0x28]
	cmp r0, #7
	beq _021DCFB0
	cmp r0, #8
	bne _021DCFC4
	bl MOD04_021DCCC8
	cmp r0, #0
	bne _021DCF94
	ldr r0, _021DCFF0 ; =UNK04_02210504
	ldr r0, [r0]
	add r0, r0, #8
	bl MOD04_021DAE4C
	add sp, sp, #4
	mov r0, #4
	ldmfd sp!, {pc}
_021DCF94:
	ldr r0, _021DCFF0 ; =UNK04_02210504
	ldr r0, [r0]
	add r0, r0, #8
	bl MOD04_021DAE4C
	add sp, sp, #4
	mov r0, #3
	ldmfd sp!, {pc}
_021DCFB0:
	add r0, r1, #8
	bl MOD04_021DAE4C
	add sp, sp, #4
	mov r0, #5
	ldmfd sp!, {pc}
_021DCFC4:
	add r0, r1, #8
	bl MOD04_021DAE4C
	ldr r1, _021DCFF8 ; =0xFFFFA1DB
	mov r0, #0x11
	bl MOD04_021DD6B0
	add sp, sp, #4
	mov r0, #4
	ldmfd sp!, {pc}
_021DCFE4:
	mov r0, #2
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DCFF0: .word UNK04_02210504
_021DCFF4: .word 0x00001B3C
_021DCFF8: .word 0xFFFFA1DB
	arm_func_end MOD04_021DCF00

	arm_func_start MOD04_021DCFFC
MOD04_021DCFFC: ; 0x021DCFFC
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0xb4
	ldr r2, _021DD244 ; =UNK04_02210504
	mov r5, r0
	ldr r2, [r2]
	mov r0, r1
	add r2, r2, #0x1000
	str r1, [r2, #0xc18]
	mov r1, #0
	mov r2, #0x174
	bl MI_CpuFill8
	ldr r0, _021DD244 ; =UNK04_02210504
	ldr r1, [r0]
	add r0, r1, #0x1000
	ldr r0, [r0, #0xba8]
	cmp r0, #0
	beq _021DD058
	ldr r0, _021DD248 ; =0x00001B3C
	add r0, r1, r0
	bl OS_IsThreadTerminated
	cmp r0, #0
	bne _021DD058
	bl OS_Terminate
_021DD058:
	ldr r0, _021DD24C ; =UNK04_0220BEB4
	ldr r1, _021DD244 ; =UNK04_02210504
	ldr r0, [r0]
	mov r3, #0
	ldr r4, [r1]
	mov r2, #0x1000
	str r0, [sp]
	str r3, [sp, #4]
	str r2, [sp, #8]
	ldr r2, [r4]
	ldr r1, _021DD250 ; =UNK04_0220C5E4
	str r2, [sp, #0xc]
	ldr r2, [r4, #4]
	str r2, [sp, #0x10]
	bl strcmp
	cmp r0, #0
	movne r0, #1
	strne r0, [sp, #0x14]
	moveq r0, #0
	ldr r2, _021DD254 ; =0x00004E20
	streq r0, [sp, #0x14]
	add r1, sp, #0
	add r0, r4, #8
	str r2, [sp, #0x18]
	bl MOD04_021DB608
	cmp r0, #0
	beq _021DD0DC
	ldr r1, _021DD258 ; =0xFFFFA1DC
	mov r0, #9
	bl MOD04_021DD6B0
	add sp, sp, #0xb4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_021DD0DC:
	add r0, sp, #0x1c
	bl MOD04_021DA238
	cmp r0, #0
	beq _021DD10C
	ldr r0, _021DD244 ; =UNK04_02210504
	add r1, sp, #0x1c
	ldr r0, [r0]
	mov r2, #0
	add r0, r0, #8
	bl MOD04_021D9C2C
	cmp r0, #0
	bne _021DD134
_021DD10C:
	ldr r0, _021DD244 ; =UNK04_02210504
	ldr r0, [r0]
	add r0, r0, #8
	bl MOD04_021DAE4C
	ldr r1, _021DD258 ; =0xFFFFA1DC
	mov r0, #9
	bl MOD04_021DD6B0
	add sp, sp, #0xb4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_021DD134:
	ldr r0, _021DD244 ; =UNK04_02210504
	ldr r1, _021DD25C ; =UNK04_0220C604
	ldr r0, [r0]
	ldr r2, _021DD260 ; =UNK04_0220C60C
	add r0, r0, #8
	mov r3, #6
	bl MOD04_021DAB68
	cmp r0, #0
	bne _021DD17C
	ldr r0, _021DD244 ; =UNK04_02210504
	ldr r1, _021DD264 ; =UNK04_0220C614
	ldr r0, [r0]
	mov r2, r5
	add r0, r0, #8
	mov r3, #4
	bl MOD04_021DAB68
	cmp r0, #0
	beq _021DD1A4
_021DD17C:
	ldr r0, _021DD244 ; =UNK04_02210504
	ldr r0, [r0]
	add r0, r0, #8
	bl MOD04_021DAE4C
	ldr r1, _021DD258 ; =0xFFFFA1DC
	mov r0, #9
	bl MOD04_021DD6B0
	add sp, sp, #0xb4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_021DD1A4:
	ldr r0, _021DD244 ; =UNK04_02210504
	ldr r0, [r0]
	add r0, r0, #8
	bl MOD04_021DB570
	cmp r0, #0
	beq _021DD1E4
	ldr r0, _021DD244 ; =UNK04_02210504
	ldr r0, [r0]
	add r0, r0, #8
	bl MOD04_021DAE4C
	ldr r1, _021DD258 ; =0xFFFFA1DC
	mov r0, #9
	bl MOD04_021DD6B0
	add sp, sp, #0xb4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_021DD1E4:
	ldr r0, _021DD268 ; =OSi_ThreadInfo
	ldr r0, [r0, #4]
	bl OS_GetThreadPriority
	ldr r1, _021DD244 ; =UNK04_02210504
	ldr r2, [r1]
	sub r1, r0, #1
	add r0, r2, #8
	bl MOD04_021DB4A4
	ldr r0, _021DD244 ; =UNK04_02210504
	ldr r1, [r0]
	add r0, r1, #0x1000
	ldr r0, [r0, #0xba8]
	cmp r0, #0
	addne sp, sp, #0xb4
	movne r0, #1
	ldmneia sp!, {r4, r5, pc}
	add r0, r1, #8
	bl MOD04_021DAE4C
	ldr r1, _021DD258 ; =0xFFFFA1DC
	mov r0, #9
	bl MOD04_021DD6B0
	mov r0, #0
	add sp, sp, #0xb4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021DD244: .word UNK04_02210504
_021DD248: .word 0x00001B3C
_021DD24C: .word UNK04_0220BEB4
_021DD250: .word UNK04_0220C5E4
_021DD254: .word 0x00004E20
_021DD258: .word 0xFFFFA1DC
_021DD25C: .word UNK04_0220C604
_021DD260: .word UNK04_0220C60C
_021DD264: .word UNK04_0220C614
_021DD268: .word OSi_ThreadInfo
	arm_func_end MOD04_021DCFFC

	arm_func_start MOD04_021DD26C
MOD04_021DD26C: ; 0x021DD26C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021DD2BC ; =UNK04_02210504
	ldr r0, [r0]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	add r0, r0, #8
	bl MOD04_021DAE4C
	ldr r1, _021DD2BC ; =UNK04_02210504
	ldr r0, _021DD2C0 ; =UNK04_0220C618
	ldr r1, [r1]
	mov r2, #0
	ldr r3, [r1, #4]
	blx r3
	ldr r0, _021DD2BC ; =UNK04_02210504
	mov r1, #0
	str r1, [r0]
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DD2BC: .word UNK04_02210504
_021DD2C0: .word UNK04_0220C618
	arm_func_end MOD04_021DD26C

	arm_func_start MOD04_021DD2C4
MOD04_021DD2C4: ; 0x021DD2C4
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r2, _021DD35C ; =UNK04_02210504
	mov r5, r0
	ldr r0, [r2]
	mov r4, r1
	cmp r0, #0
	beq _021DD2FC
	ldr r1, _021DD360 ; =0xFFFFA1DC
	mov r0, #9
	bl MOD04_021DD6B0
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_021DD2FC:
	ldr r0, _021DD364 ; =UNK04_0220C628
	ldr r1, _021DD368 ; =0x00001C1C
	blx r5
	ldr r1, _021DD35C ; =UNK04_02210504
	cmp r0, #0
	str r0, [r1]
	bne _021DD330
	ldr r1, _021DD360 ; =0xFFFFA1DC
	mov r0, #9
	bl MOD04_021DD6B0
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_021DD330:
	ldr r2, _021DD368 ; =0x00001C1C
	mov r1, #0
	bl MI_CpuFill8
	ldr r1, _021DD35C ; =UNK04_02210504
	mov r0, #1
	ldr r2, [r1]
	str r5, [r2]
	ldr r1, [r1]
	str r4, [r1, #4]
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021DD35C: .word UNK04_02210504
_021DD360: .word 0xFFFFA1DC
_021DD364: .word UNK04_0220C628
_021DD368: .word 0x00001C1C
	arm_func_end MOD04_021DD2C4

	.section .data

	.global UNK04_0220C5A0
UNK04_0220C5A0: ; 0x0220C5A0
	.asciz "Date"

	.balign 4, 0
	.global UNK04_0220C5A8
UNK04_0220C5A8: ; 0x0220C5A8
	.asciz "httpresult"

	.balign 4, 0
	.global UNK04_0220C5B4
UNK04_0220C5B4: ; 0x0220C5B4
	.asciz "returncd"

	.balign 4, 0
	.global UNK04_0220C5C0
UNK04_0220C5C0: ; 0x0220C5C0
	.asciz "svchost"

	.balign 4, 0
	.global UNK04_0220C5C8
UNK04_0220C5C8: ; 0x0220C5C8
	.asciz "servicetoken"

	.balign 4, 0
	.global UNK04_0220C5D8
UNK04_0220C5D8: ; 0x0220C5D8
	.asciz "statusdata"

	.balign 4, 0
	.global UNK04_0220C5E4
UNK04_0220C5E4: ; 0x0220C5E4
	.asciz "https://nas.nintendowifi.net/ac"

	.balign 4, 0
	.global UNK04_0220C604
UNK04_0220C604: ; 0x0220C604
	.asciz "action"

	.balign 4, 0
	.global UNK04_0220C60C
UNK04_0220C60C: ; 0x0220C60C
	.asciz "SVCLOC"

	.balign 4, 0
	.global UNK04_0220C614
UNK04_0220C614: ; 0x0220C614
	.asciz "svc"

	.balign 4, 0
	.global UNK04_0220C618
UNK04_0220C618: ; 0x0220C618
	.asciz "FREE intwork"

	.balign 4, 0
	.global UNK04_0220C628
UNK04_0220C628: ; 0x0220C628
	.asciz "ALLOC intwork"

	.balign 4, 0
	.section .bss

	.global UNK04_02210504
UNK04_02210504: ; 0x02210504
	.space 0x4
