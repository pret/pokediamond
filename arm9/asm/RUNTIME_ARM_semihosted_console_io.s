	.include "asm/macros.inc"
	.include "global.inc"

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

	exception __read_console, 81, 0x00300F00
	exception __write_console, 53, 0x00200700
