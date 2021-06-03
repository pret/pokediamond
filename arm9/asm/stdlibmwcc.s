	.include "asm/macros.inc"
	.include "global.inc"

	.bss

	.global __global_destructor_chain
__global_destructor_chain: ; 0x021D74C8
	.space 0x18

	.text

	arm_func_start sys_writec
sys_writec: ; 0x020EC5D0
	str lr, [sp, #-0x4]!
	mov r1, r0
	mov r0, #0x3
	swi 0x123456
	ldr pc, [sp], #0x4

	arm_func_start sys_readc
sys_readc: ; 0x020EC5E4
	str lr, [sp, #-0x4]!
	mov r1, #0x0
	mov r0, #0x7
	swi 0x123456
	ldr pc, [sp], #0x4

	arm_func_start sys_exit
sys_exit: ; 0x020EC5F8
	mov r1, #0x0
	mov r0, #0x18
	swi 0x123456
	mov pc, lr

	arm_func_start __read_console
__read_console: ; 0x020EC608
	stmdb sp!, {r3-r7,lr}
	mov r6, r2
	ldr r5, [r6, #0x0]
	mov r7, r1
	cmp r5, #0x0
	mov r4, #0x0
	bls _020EC650
_020EC624:
	bl sys_readc
	and r1, r0, #0xff
	cmp r1, #0xd
	strb r0, [r7, r4]
	cmpne r1, #0xa
	addeq r0, r4, #0x1
	streq r0, [r6, #0x0]
	beq _020EC650
	add r4, r4, #0x1
	cmp r4, r5
	blo _020EC624
_020EC650:
	mov r0, #0x0
	ldmia sp!, {r3-r7,pc}

	arm_func_start __write_console
__write_console: ; 0x020EC658
	stmdb sp!, {r4-r6,lr}
	ldr r5, [r2, #0x0]
	mov r6, r1
	cmp r5, #0x0
	mov r4, #0x0
	bls _020EC684
_020EC670:
	add r0, r6, r4
	bl sys_writec
	add r4, r4, #0x1
	cmp r4, r5
	blo _020EC670
_020EC684:
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}

	arm_func_start __close_console
__close_console: ; 0x020EC68C
	mov r0, #0x0
	bx lr

	.extern __sinit__
	arm_func_start __call_static_initializers
__call_static_initializers: ; 0x020EC694
	stmdb sp!, {r4,lr}
	ldr r4, _020EC6BC ; =__sinit__
	b _020EC6A8
_020EC6A0:
	blx r0
	add r4, r4, #0x4
_020EC6A8:
	cmp r4, #0x0
	ldrne r0, [r4, #0x0]
	cmpne r0, #0x0
	bne _020EC6A0
	ldmia sp!, {r4,pc}
	.balign 4
_020EC6BC: .word __sinit__

	arm_func_start __destroy_global_chain
__destroy_global_chain: ; 0x020EC6C0
	stmdb sp!, {r3-r5,lr}
	ldr r4, _020EC700 ; =__global_destructor_chain
	ldr r2, [r4, #0x0]
	cmp r2, #0x0
	ldmeqia sp!, {r3-r5,pc}
_020EC6D4: ; 0x020EC6D4
	mvn r5, #0x0
_020EC6D8:
	ldr r0, [r2, #0x0]
	mov r1, r5
	str r0, [r4, #0x0]
	ldr r0, [r2, #0x8]
	ldr r2, [r2, #0x4]
	blx r2
	ldr r2, [r4, #0x0]
	cmp r2, #0x0
	bne _020EC6D8
	ldmia sp!, {r3-r5,pc}
	.balign 4
_020EC700: .word __global_destructor_chain

	arm_func_start _ExitProcess
_ExitProcess: ; 0x020EC704
	ldr ip, _020EC70C ; =sys_exit
	bx r12
	.balign 4
_020EC70C: .word sys_exit

	.section .exception,8

	.section .exceptix,4

	.word __read_console
	.short 81
	.word 0x00300F00
	.word __write_console
	.short 53
	.word 0x00200700
	.word __call_static_initializers
	.short 45
	.word 0x00100100
	.word __destroy_global_chain
	.short 69
	.word 0x00200300
	.word _ExitProcess
	.short 13
	.word 0x00000000
