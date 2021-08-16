	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD04_021DDF40
MOD04_021DDF40: ; 0x021DDF40
	ldr ip, _021DDF48 ; =MOD04_021D9974
	bx ip
	.align 2, 0
_021DDF48: .word MOD04_021D9974
	arm_func_end MOD04_021DDF40

	arm_func_start MOD04_021DDF4C
MOD04_021DDF4C: ; 0x021DDF4C
	stmdb sp!, {lr}
	sub sp, sp, #0x1c4
	ldr r0, _021DE054 ; =UNK04_0221051C
	ldr r0, [r0]
	cmp r0, #0
	addeq sp, sp, #0x1c4
	moveq r0, #0
	ldmeqia sp!, {pc}
	add r0, r0, #0x1000
	ldr r0, [r0, #0xba0]
	cmp r0, #0
	addeq sp, sp, #0x1c4
	moveq r0, #1
	ldmeqia sp!, {pc}
	bl MOD04_021D988C
	cmp r0, #0
	beq _021DDFA4
	cmp r0, #0x14
	beq _021DDFE0
	cmp r0, #0x15
	beq _021DDFB0
	b _021DE010
_021DDFA4:
	add sp, sp, #0x1c4
	mov r0, #2
	ldmfd sp!, {pc}
_021DDFB0:
	bl MOD04_021D991C
	ldr r0, _021DE054 ; =UNK04_0221051C
	ldr r2, _021DE058 ; =0x00001E1C
	ldr r1, [r0]
	mov r0, #4
	bl MOD04_021DD904
	ldr r0, _021DE054 ; =UNK04_0221051C
	mov r1, #0
	str r1, [r0]
	add sp, sp, #0x1c4
	mov r0, #3
	ldmfd sp!, {pc}
_021DDFE0:
	bl MOD04_021D991C
	ldr r0, _021DE054 ; =UNK04_0221051C
	ldr r2, _021DE058 ; =0x00001E1C
	ldr r1, [r0]
	mov r0, #4
	bl MOD04_021DD904
	ldr r0, _021DE054 ; =UNK04_0221051C
	mov r1, #0
	str r1, [r0]
	add sp, sp, #0x1c4
	mov r0, #5
	ldmfd sp!, {pc}
_021DE010:
	add r0, sp, #0
	bl MOD04_021D97F8
	bl MOD04_021D991C
	ldr r0, _021DE054 ; =UNK04_0221051C
	ldr r2, _021DE058 ; =0x00001E1C
	ldr r1, [r0]
	mov r0, #4
	bl MOD04_021DD904
	ldr r1, [sp]
	ldr r2, _021DE054 ; =UNK04_0221051C
	mov r3, #0
	mov r0, #2
	str r3, [r2]
	bl MOD04_021DD6B0
	mov r0, #4
	add sp, sp, #0x1c4
	ldmfd sp!, {pc}
	.align 2, 0
_021DE054: .word UNK04_0221051C
_021DE058: .word 0x00001E1C
	arm_func_end MOD04_021DDF4C

	arm_func_start MOD04_021DE05C
MOD04_021DE05C: ; 0x021DE05C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021DE130 ; =UNK04_0221051C
	ldr r0, [r0]
	cmp r0, #0
	beq _021DE078
	bl OS_Terminate
_021DE078:
	ldr r1, _021DE134 ; =0x00001E1C
	mov r0, #4
	bl MOD04_021DD944
	ldr r1, _021DE130 ; =UNK04_0221051C
	cmp r0, #0
	str r0, [r1]
	bne _021DE0AC
	ldr r1, _021DE138 ; =0xFFFFB17C
	mov r0, #9
	bl MOD04_021DD6B0
	add sp, sp, #4
	mov r0, #0
	ldmfd sp!, {pc}
_021DE0AC:
	ldr r2, _021DE134 ; =0x00001E1C
	mov r1, #0
	bl MI_CpuFill8
	ldr r0, _021DE130 ; =UNK04_0221051C
	ldr r1, _021DE13C ; =0x00001C44
	ldr r2, [r0]
	ldr r0, _021DE140 ; =UNK04_0220D2EC
	add r1, r2, r1
	mov r2, #9
	bl MI_CpuCopy8
	ldr r1, _021DE130 ; =UNK04_0221051C
	ldr r2, _021DE144 ; =MOD04_021DD944
	ldr r0, [r1]
	ldr r3, _021DE148 ; =MOD04_021DD904
	add r0, r0, #0x1000
	str r2, [r0, #0xc50]
	ldr r0, [r1]
	ldr r2, _021DE14C ; =0x00001C10
	add r0, r0, #0x1000
	str r3, [r0, #0xc54]
	ldr r1, [r1]
	add r0, r1, r2
	bl MOD04_021D9ACC
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	ldr r1, _021DE138 ; =0xFFFFB17C
	mov r0, #9
	bl MOD04_021DD6B0
	mov r0, #0
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DE130: .word UNK04_0221051C
_021DE134: .word 0x00001E1C
_021DE138: .word 0xFFFFB17C
_021DE13C: .word 0x00001C44
_021DE140: .word UNK04_0220D2EC
_021DE144: .word MOD04_021DD944
_021DE148: .word MOD04_021DD904
_021DE14C: .word 0x00001C10
	arm_func_end MOD04_021DE05C

	arm_func_start MOD04_021DE150
MOD04_021DE150: ; 0x021DE150
	stmdb sp!, {r4, lr}
	bl MOD04_021DCF00
	mov r4, r0
	sub r0, r4, #3
	cmp r0, #2
	bhi _021DE16C
	bl MOD04_021DD26C
_021DE16C:
	mov r0, r4
	ldmia sp!, {r4, pc}
	arm_func_end MOD04_021DE150

	arm_func_start MOD04_021DE174
MOD04_021DE174: ; 0x021DE174
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	mov r4, r1
	ldr r0, _021DE1EC ; =MOD04_021DD944
	ldr r1, _021DE1F0 ; =MOD04_021DD904
	bl MOD04_021DD2C4
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, pc}
	mov r0, r5
	bl strlen
	cmp r0, #0
	bne _021DE1C0
	ldr r0, _021DE1F4 ; =UNK04_0220D2F0
	mov r1, r4
	bl MOD04_021DCFFC
	b _021DE1CC
_021DE1C0:
	mov r0, r5
	mov r1, r4
	bl MOD04_021DCFFC
_021DE1CC:
	cmp r0, #0
	addne sp, sp, #4
	movne r0, #1
	ldmneia sp!, {r4, r5, pc}
	bl MOD04_021DD26C
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021DE1EC: .word MOD04_021DD944
_021DE1F0: .word MOD04_021DD904
_021DE1F4: .word UNK04_0220D2F0
	arm_func_end MOD04_021DE174

	arm_func_start MOD04_021DE1F8
MOD04_021DE1F8: ; 0x021DE1F8
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r2, _021DE2C4 ; =UNK04_022104F8
	mov r5, r0
	ldr r2, [r2]
	mov r4, r1
	cmp r2, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, pc}
	bl RTC_GetDate
	cmp r0, #0
	bne _021DE23C
	mov r0, r4
	bl RTC_GetTime
	cmp r0, #0
	beq _021DE248
_021DE23C:
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_021DE248:
	mov r0, r5
	mov r1, r4
	bl RTC_ConvertDateTimeToSecond
	mvn r2, #0
	cmp r1, r2
	cmpeq r0, r2
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, pc}
	ldr r2, _021DE2C8 ; =UNK04_022104FC
	mov ip, #0
	ldr lr, [r2]
	ldr r3, [r2, #4]
	subs r2, r0, lr
	sbc r3, r1, r3
	subs r0, r2, ip
	sbcs r0, r3, ip
	blt _021DE2A0
	ldr r0, _021DE2CC ; =0xBC19137F
	subs r0, r0, r2
	sbcs r0, ip, r3
	bge _021DE2AC
_021DE2A0:
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_021DE2AC:
	mov r0, r5
	mov r1, r4
	bl RTC_ConvertSecondToDateTime
	mov r0, #1
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021DE2C4: .word UNK04_022104F8
_021DE2C8: .word UNK04_022104FC
_021DE2CC: .word 0xBC19137F
	arm_func_end MOD04_021DE1F8

	.section .data

	.global UNK_0220D2EC
UNK04_0220D2EC: ; 0x0220D2EC
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_0220D2F0
UNK04_0220D2F0: ; 0x0220D2F0
	.asciz "0000"

	.balign 4, 0
	.section .bss

	.global UNK04_0221051C
UNK04_0221051C: ; 0x0221051C
	.space 0x4
