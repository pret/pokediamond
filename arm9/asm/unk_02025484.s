	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02025484
FUN_02025484: ; 0x02025484
	ldr r3, _0202548C ; =MI_CpuFill8
	mov r1, #0x0
	mov r2, #0x24
	bx r3
	.balign 4
_0202548C: .word MI_CpuFill8

	thumb_func_start FUN_02025490
FUN_02025490: ; 0x02025490
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02025484
	str r4, [r5, #0x0]
	add r0, r5, #0x4
	pop {r3-r5, pc}

	thumb_func_start FUN_020254A0
FUN_020254A0: ; 0x020254A0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, r1
	beq _020254AE
	bl ErrorHandling
_020254AE:
	add r0, r4, #0x4
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020254B4
FUN_020254B4: ; 0x020254B4
	ldr r0, [r0, #0x0]
	bx lr
