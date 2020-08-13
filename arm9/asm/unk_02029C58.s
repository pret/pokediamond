	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02029C58
FUN_02029C58: ; 0x02029C58
	mov r0, #0x17
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_02029C60
FUN_02029C60: ; 0x02029C60
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02029C58
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x0
	bl MI_CpuFill8
	pop {r4, pc}

	thumb_func_start FUN_02029C74
FUN_02029C74: ; 0x02029C74
	ldr r3, _02029C7C ; =MI_CpuCopy8
	mov r2, #0x18
	bx r3
	nop
_02029C7C: .word MI_CpuCopy8

	thumb_func_start FUN_02029C80
FUN_02029C80: ; 0x02029C80
	ldr r3, _02029C88 ; =SavArray_get
	mov r1, #0x15
	bx r3
	nop
_02029C88: .word SavArray_get

	thumb_func_start FUN_02029C8C
FUN_02029C8C: ; 0x02029C8C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xc
	blt _02029C9A
	bl ErrorHandling
_02029C9A:
	mov r0, #0x18
	mul r0, r4
	add r0, r5, r0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02029CA4
FUN_02029CA4: ; 0x02029CA4
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r6, #0xc
	blt _02029CB4
	bl ErrorHandling
_02029CB4:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02029C8C
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02029C74
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02029CC8
FUN_02029CC8: ; 0x02029CC8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x8
	blt _02029CD6
	bl ErrorHandling
_02029CD6:
	lsl r0, r4, #0x1
	add r0, r4, r0
	add r0, r5, r0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02029CE0
FUN_02029CE0: ; 0x02029CE0
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02029CE4
FUN_02029CE4: ; 0x02029CE4
	ldrb r0, [r0, #0x1]
	bx lr

	thumb_func_start FUN_02029CE8
FUN_02029CE8: ; 0x02029CE8
	ldrb r0, [r0, #0x2]
	bx lr
