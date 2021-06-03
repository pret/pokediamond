	.include "asm/macros.inc"
	.include "global.inc"

	.bss

	.global __console_exit
__console_exit: ; 0x021D6F78
	.space 0x4
	.size __console_exit,.-__console_exit

	.global __stdio_exit
__stdio_exit: ; 0x021D6F7C
	.space 0x4
	.size __stdio_exit,.-__stdio_exit

	.global __atexit_curr_func
__atexit_curr_func: ; 0x021D6F80
	.space 0x4
	.size __atexit_curr_func,.-__atexit_curr_func

	.global __aborting
__aborting: ; 0x021D6F84
	.space 0x4
	.size __aborting,.-__aborting

	.global __atexit_funcs
__atexit_funcs: ; 0x021D6F88
	.space 0x100
	.size __atexit_funcs,.-__atexit_funcs

	.text

	arm_func_start abort
abort: ; 0x020DE14C
	stmdb sp!, {r3,lr}
	mov r0, #0x1
	bl raise
	ldr r1, _020DE16C ; =__aborting - 0xC
	mov r0, #0x1
	str r0, [r1, #0xc]
	bl exit
	ldmia sp!, {r3,pc}
	.balign 4
_020DE16C: .word __aborting - 0xC
	arm_func_end abort

	arm_func_start exit
exit: ; 0x020DE170
	stmdb sp!, {r4,lr}
	ldr r1, _020DE1B8 ; =__aborting - 0xC
	mov r4, r0
	ldr r0, [r1, #0xc]
	cmp r0, #0x0
	bne _020DE1AC
	bl __destroy_global_chain
	ldr r0, _020DE1B8 ; =__stdio_exit - 0x4
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _020DE1AC
	blx r0
	ldr r0, _020DE1B8 ; =__stdio_exit - 0x4
	mov r1, #0x0
	str r1, [r0, #0x4]
_020DE1AC:
	mov r0, r4
	bl __exit
	ldmia sp!, {r4,pc}
	.balign 4
_020DE1B8: .word __console_exit
	arm_func_end exit

	arm_func_start __exit
__exit: ; 0x020DE1BC
	stmdb sp!, {r3-r5,lr}
	ldr r0, _020DE2CC ; =__cs
	bl OS_TryLockMutex
	cmp r0, #0x0
	bne _020DE1F4
	ldr r0, _020DE2D0 ; =OSi_ThreadInfo
	ldr r1, _020DE2D4 ; =__cs_id
	ldr r2, [r0, #0x4]
	ldr r0, _020DE2D8 ; =__cs_ref
	ldr r3, [r2, #0x6c]
	mov r2, #0x1
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	b _020DE24C
_020DE1F4:
	ldr r0, _020DE2D0 ; =OSi_ThreadInfo
	ldr r1, _020DE2D4 ; =__cs_id
	ldr r0, [r0, #0x4]
	ldr r1, [r1, #0x0]
	ldr r0, [r0, #0x6c]
	cmp r1, r0
	bne _020DE224
	ldr r0, _020DE2D8 ; =__cs_ref
	ldr r1, [r0, #0x0]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	b _020DE24C
_020DE224:
	ldr r0, _020DE2CC ; =__cs
	bl OS_LockMutex
	ldr r0, _020DE2D0 ; =OSi_ThreadInfo
	ldr r1, _020DE2D4 ; =__cs_id
	ldr r2, [r0, #0x4]
	ldr r0, _020DE2D8 ; =__cs_ref
	ldr r3, [r2, #0x6c]
	mov r2, #0x1
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
_020DE24C:
	ldr r4, _020DE2DC ; =__console_exit
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	ble _020DE280
	ldr r5, _020DE2E0 ; =__atexit_funcs
_020DE260:
	ldr r0, [r4, #0x8]
	sub r1, r0, #0x1
	ldr r0, [r5, r1, lsl #0x2]
	str r1, [r4, #0x8]
	blx r0
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	bgt _020DE260
_020DE280:
	ldr r0, _020DE2D8 ; =__cs_ref
	ldr r1, [r0, #0x0]
	subs r1, r1, #0x1
	str r1, [r0, #0x0]
	bne _020DE29C
	ldr r0, _020DE2CC ; =__cs
	bl OS_UnlockMutex
_020DE29C:
	ldr r0, _020DE2DC ; =__console_exit
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020DE2BC
	blx r0
	ldr r0, _020DE2DC ; =__console_exit
	mov r1, #0x0
	str r1, [r0, #0x0]
_020DE2BC:
	mov r0, #0x0
	bl fflush
	bl _ExitProcess
	ldmia sp!, {r3-r5,pc}
	.balign 4
_020DE2CC: .word __cs
_020DE2D0: .word OSi_ThreadInfo
_020DE2D4: .word __cs_id
_020DE2D8: .word __cs_ref
_020DE2DC: .word __console_exit
_020DE2E0: .word __atexit_funcs
	arm_func_end __exit

	.section .exceptix,4

	.word abort
	.short 37
	.word 0x00100000
	.word exit
	.short 77
	.word 0x00100100
	.word __exit
	.short 297
	.word 0x00200300
