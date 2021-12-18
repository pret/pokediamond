	.include "asm/macros.inc"
	.include "global.inc"

	.data

__local_str__msl_assertion_failed: ; 0x02106B3C
	.asciz "Assertion (%s) failed in \"%s\", function \"%s\", line %d\n"
	.size __local_str__msl_assertion_failed,.-__local_str__msl_assertion_failed
	.balign 4, 0

	.text

	arm_func_start __msl_assertion_failed
__msl_assertion_failed: ; 0x020DE3FC
	stmdb sp!, {r3-r4,lr}
	sub sp, sp, #0x4
	mov r4, r0
	mov lr, r1
	mov r12, r2
	str r3, [sp, #0x0]
	ldr r0, _020DE434 ; =__local_str__msl_assertion_failed
	mov r1, r4
	mov r2, lr
	mov r3, r12
	bl printf
	bl abort
	add sp, sp, #0x4
	ldmia sp!, {r3-r4,pc}
	.balign 4
_020DE434: .word __local_str__msl_assertion_failed
	arm_func_end __msl_assertion_failed

	exception __msl_assertion_failed, 61, 0x00200100
