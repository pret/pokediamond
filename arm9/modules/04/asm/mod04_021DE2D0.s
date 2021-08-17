	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD04_021DE2D0
MOD04_021DE2D0: ; 0x021DE2D0
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	mov r4, r1
	bl MOD04_021DD6D4
	cmp r0, #0
	addne sp, sp, #4
	movne r0, #0
	ldmneia sp!, {r4, r5, pc}
	mov r0, r5
	mov r1, r4
	bl MOD04_02207330
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	arm_func_end MOD04_021DE2D0

	arm_func_start MOD04_021DE308
MOD04_021DE308: ; 0x021DE308
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD04_021DD6D4
	cmp r0, #0
	addne sp, sp, #4
	movne r0, #0
	ldmneia sp!, {pc}
	bl MOD04_02207158
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end MOD04_021DE308

	arm_func_start MOD04_021DE330
MOD04_021DE330: ; 0x021DE330
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl MOD04_021DD6D4
	cmp r0, #0
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl MOD04_0220733C
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD04_021DE330

	arm_func_start MOD04_021DE364
MOD04_021DE364: ; 0x021DE364
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl MOD04_021DD6D4
	cmp r0, #0
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	mov r0, #0xb0
	mul r2, r4, r0
	mov r0, r6
	mov r1, #0
	bl MI_CpuFill8
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl MOD04_022074EC
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD04_021DE364

	arm_func_start MOD04_021DE3AC
MOD04_021DE3AC: ; 0x021DE3AC
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl MOD04_021DD6D4
	cmp r0, #0
	movne r0, #0
	ldmneia sp!, {r4, pc}
	mov r0, r4
	bl MOD04_022077A8
	ldmia sp!, {r4, pc}
	arm_func_end MOD04_021DE3AC

	arm_func_start MOD04_021DE3D0
MOD04_021DE3D0: ; 0x021DE3D0
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl MOD04_021DD6D4
	cmp r0, #0
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl MOD04_022069DC
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD04_021DE3D0

	arm_func_start MOD04_021DE404
MOD04_021DE404: ; 0x021DE404
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _021DE454 ; =UNK04_02210520
	ldr r2, [r1]
	cmp r2, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {pc}
	str r0, [r2, #4]
	ldr r0, [r1]
	ldr r0, [r0, #0x48]
	cmp r0, #0
	bne _021DE440
	bl MOD04_021DE730
	b _021DE448
_021DE440:
	ldr r0, _021DE458 ; =MOD04_021DE730
	bl MOD04_02206E6C
_021DE448:
	mov r0, #1
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DE454: .word UNK04_02210520
_021DE458: .word MOD04_021DE730
	arm_func_end MOD04_021DE404

	arm_func_start MOD04_021DE45C
MOD04_021DE45C: ; 0x021DE45C
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #8
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl MOD04_021DD6D4
	cmp r0, #0
	addne sp, sp, #8
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	mov r0, #0xa80
	mov r1, #0x20
	bl MOD04_021DE884
	ldr r2, _021DE568 ; =UNK04_02210520
	mov r1, #0
	str r0, [r2]
	str r1, [r0, #0x48]
	ldr r0, [r2]
	mov r2, #0xa80
	bl MI_CpuFill8
	ldr r0, _021DE568 ; =UNK04_02210520
	mov r1, r5
	ldr r3, [r0]
	mov r2, #0x1f
	str r6, [r3]
	ldr r0, [r0]
	add r0, r0, #8
	bl strncpy
	ldr r0, _021DE568 ; =UNK04_02210520
	mov r1, r4
	ldr r0, [r0]
	mov r2, #0x1f
	add r0, r0, #0x28
	bl strncpy
	ldr r1, _021DE568 ; =UNK04_02210520
	ldr r0, _021DE56C ; =UNK04_0220D2F8
	ldr r1, [r1]
	add r1, r1, #0x4c
	bl MOD04_021DE174
	cmp r0, #0
	bne _021DE520
	ldr r0, _021DE568 ; =UNK04_02210520
	ldr r0, [r0]
	bl MOD04_021DE86C
	ldr r1, _021DE568 ; =UNK04_02210520
	mov r0, #0
	str r0, [r1]
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, pc}
_021DE520:
	ldr r0, _021DE568 ; =UNK04_02210520
	mov r2, #0x800
	ldr r0, [r0]
	ldr r1, _021DE570 ; =MOD04_021DE574
	add r0, r0, #0x9c0
	mov r3, r0
	str r2, [sp]
	mov ip, #0x10
	mov r2, #0
	str ip, [sp, #4]
	bl OS_CreateThread
	ldr r0, _021DE568 ; =UNK04_02210520
	ldr r0, [r0]
	add r0, r0, #0x9c0
	bl OS_WakeupThreadDirect
	mov r0, #1
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021DE568: .word UNK04_02210520
_021DE56C: .word UNK04_0220D2F8
_021DE570: .word MOD04_021DE574
	arm_func_end MOD04_021DE45C

	arm_func_start MOD04_021DE574
MOD04_021DE574: ; 0x021DE574
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0x2a4
	mov r7, #0
	mov r6, #6
	mvn r5, #0
	mov r4, #0x64
_021DE58C:
	bl MOD04_021DE150
	cmp r0, #3
	bne _021DE6AC
	ldr r0, _021DE718 ; =UNK04_02210520
	ldr r5, [r0]
	add r0, r5, #0x50
	bl strlen
	mov r4, r0
	ldr r0, _021DE71C ; =UNK04_0220D300
	bl strlen
	add r0, r4, r0
	cmp r0, #0xff
	bls _021DE5D8
	mov r0, #0
	mov r1, #8
	mvn r2, #0
	bl MOD04_021DE774
	add sp, sp, #0x2a4
	ldmia sp!, {r4, r5, r6, r7, pc}
_021DE5D8:
	ldr r2, _021DE720 ; =UNK04_0220D314
	add r0, sp, #0x10
	add r3, r5, #0x50
	mov r1, #0x100
	bl OS_SNPrintf
	ldr r0, _021DE718 ; =UNK04_02210520
	ldr r4, [r0]
	add r0, r4, #0x91
	bl strlen
	mov r1, r0
	add r2, sp, #0x110
	add r0, r4, #0x91
	mov r3, #0x190
	bl MOD04_021DD4FC
	cmp r0, #0
	bge _021DE630
	mov r0, #0
	mov r1, #8
	mvn r2, #0
	bl MOD04_021DE774
	add sp, sp, #0x2a4
	ldmia sp!, {r4, r5, r6, r7, pc}
_021DE630:
	ldr r0, _021DE718 ; =UNK04_02210520
	ldr r4, _021DE724 ; =MOD04_021DE774
	ldr r2, [r0]
	ldr r0, _021DE728 ; =MOD04_021DE884
	add r1, r2, #8
	str r1, [sp]
	add r1, r2, #0x28
	str r1, [sp, #4]
	ldr r1, _021DE72C ; =MOD04_021DE86C
	add r2, sp, #0x10
	add r3, sp, #0x110
	str r4, [sp, #8]
	bl MOD04_02206EFC
	cmp r0, #0
	bne _021DE684
	mov r0, #0
	mov r1, #8
	mvn r2, #0
	bl MOD04_021DE774
	add sp, sp, #0x2a4
	ldmia sp!, {r4, r5, r6, r7, pc}
_021DE684:
	ldr r1, _021DE718 ; =UNK04_02210520
	mov r0, #0
	ldr r3, [r1]
	mov r4, #1
	mov r1, r0
	mvn r2, #0
	str r4, [r3, #0x48]
	bl MOD04_021DE774
	add sp, sp, #0x2a4
	ldmia sp!, {r4, r5, r6, r7, pc}
_021DE6AC:
	cmp r0, #4
	bne _021DE6EC
	add r0, sp, #0xc
	bl MOD04_021DD808
	ldr r1, [sp, #0xc]
	mov r0, #0xe
	bl MOD04_021DD6B0
	ldr r1, _021DE718 ; =UNK04_02210520
	mov r0, #0
	ldr r2, [r1]
	mov r1, #3
	ldr r3, [r2]
	mvn r2, #0
	blx r3
	add sp, sp, #0x2a4
	ldmia sp!, {r4, r5, r6, r7, pc}
_021DE6EC:
	cmp r0, #5
	bne _021DE704
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl MOD04_021DE774
_021DE704:
	mov r0, r4
	bl OS_Sleep
	b _021DE58C
	arm_func_end MOD04_021DE574

	arm_func_start MOD04_021DE710
MOD04_021DE710: ; 0x021DE710
	add sp, sp, #0x2a4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021DE718: .word UNK04_02210520
_021DE71C: .word UNK04_0220D300
_021DE720: .word UNK04_0220D314
_021DE724: .word MOD04_021DE774
_021DE728: .word MOD04_021DE884
_021DE72C: .word MOD04_021DE86C
	arm_func_end MOD04_021DE710

	arm_func_start MOD04_021DE730
MOD04_021DE730: ; 0x021DE730
	stmdb sp!, {r4, lr}
	ldr r0, _021DE770 ; =UNK04_02210520
	ldr r0, [r0]
	add r0, r0, #0x9c0
	bl OS_JoinThread
	ldr r0, _021DE770 ; =UNK04_02210520
	ldr r0, [r0]
	ldr r4, [r0, #4]
	bl MOD04_021DE86C
	ldr r0, _021DE770 ; =UNK04_02210520
	mov r1, #0
	str r1, [r0]
	cmp r4, #0
	ldmeqia sp!, {r4, pc}
	blx r4
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DE770: .word UNK04_02210520
	arm_func_end MOD04_021DE730

	arm_func_start MOD04_021DE774
MOD04_021DE774: ; 0x021DE774
	stmdb sp!, {r4, r5, r6, lr}
	movs r5, r1
	mov r6, r0
	mov r4, r2
	bne _021DE79C
	ldr r3, _021DE854 ; =UNK04_02210520
	ldr r3, [r3]
	ldr r3, [r3]
	blx r3
	ldmia sp!, {r4, r5, r6, pc}
_021DE79C:
	cmp r5, #8
	addls pc, pc, r5, lsl #2
	b _021DE830
_021DE7A8: ; jump table
	b _021DE830 ; case 0
	b _021DE7CC ; case 1
	b _021DE7DC ; case 2
	b _021DE7E4 ; case 3
	b _021DE7F4 ; case 4
	b _021DE804 ; case 5
	b _021DE834 ; case 6
	b _021DE818 ; case 7
	b _021DE820 ; case 8
_021DE7CC:
	ldr r1, _021DE858 ; =0xFFFF86E7
	mov r0, #9
	bl MOD04_021DD6B0
	b _021DE834
_021DE7DC:
	bl OS_Terminate
	b _021DE834
_021DE7E4:
	ldr r1, _021DE85C ; =0xFFFF86D4
	mov r0, #0xf
	bl MOD04_021DD6B0
	b _021DE834
_021DE7F4:
	ldr r1, _021DE860 ; =0xFFFF86CA
	mov r0, #0xe
	bl MOD04_021DD6B0
	b _021DE834
_021DE804:
	ldr r1, _021DE864 ; =0xFFFF86E8
	mov r0, #0xe
	sub r1, r1, r4
	bl MOD04_021DD6B0
	b _021DE834
_021DE818:
	bl OS_Terminate
	b _021DE834
_021DE820:
	ldr r1, _021DE868 ; =0xFFFF86DF
	mov r0, #9
	bl MOD04_021DD6B0
	b _021DE834
_021DE830:
	bl OS_Terminate
_021DE834:
	ldr r1, _021DE854 ; =UNK04_02210520
	mov r0, r6
	ldr r2, [r1]
	mov r1, r5
	ldr r3, [r2]
	mov r2, r4
	blx r3
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021DE854: .word UNK04_02210520
_021DE858: .word 0xFFFF86E7
_021DE85C: .word 0xFFFF86D4
_021DE860: .word 0xFFFF86CA
_021DE864: .word 0xFFFF86E8
_021DE868: .word 0xFFFF86DF
	arm_func_end MOD04_021DE774

	arm_func_start MOD04_021DE86C
MOD04_021DE86C: ; 0x021DE86C
	ldr ip, _021DE880 ; =MOD04_021DD904
	mov r1, r0
	mov r0, #6
	mov r2, #0
	bx ip
	.align 2, 0
_021DE880: .word MOD04_021DD904
	arm_func_end MOD04_021DE86C

	arm_func_start MOD04_021DE884
MOD04_021DE884: ; 0x021DE884
	ldr ip, _021DE898 ; =MOD04_021DD924
	mov r2, r1
	mov r1, r0
	mov r0, #6
	bx ip
	.align 2, 0
_021DE898: .word MOD04_021DD924
	arm_func_end MOD04_021DE884

	.section .data

	.global UNK04_0220D2F8
UNK04_0220D2F8: ; 0x0220D2F8
	.asciz "9000"

	.balign 4, 0
	.global UNK04_0220D300
UNK04_0220D300: ; 0x0220D300
	.asciz "https:///download"

	.balign 4, 0
	.global UNK04_0220D314
UNK04_0220D314: ; 0x0220D314
	.asciz "https://%s/download"

	.balign 4, 0
	.section .bss

	.global UNK04_02210520
UNK04_02210520: ; 0x02210520
	.space 0x4
