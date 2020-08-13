	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0202C0E0
FUN_0202C0E0: ; 0x0202C0E0
	mov r0, #0x28
	bx lr

	thumb_func_start FUN_0202C0E4
FUN_0202C0E4: ; 0x0202C0E4
	push {r4-r5}
	mov r4, #0x0
	add r1, r4, #0x0
	add r2, r4, #0x0
_0202C0EC:
	add r3, r2, #0x0
	add r5, r0, #0x0
_0202C0F0:
	add r3, r3, #0x1
	strh r1, [r5, #0x0]
	add r5, r5, #0x2
	cmp r3, #0x4
	blt _0202C0F0
	add r4, r4, #0x1
	add r0, #0x8
	cmp r4, #0x5
	blt _0202C0EC
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_0202C108
FUN_0202C108: ; 0x0202C108
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r1, #0x21
	add r4, r2, #0x0
	bl SavArray_get
	lsl r1, r5, #0x3
	add r3, r0, r1
	lsl r2, r4, #0x1
	ldrh r1, [r3, r2]
	ldr r0, _0202C128 ; =0x0000270F
	cmp r1, r0
	bhs _0202C126
	add r0, r1, #0x1
	strh r0, [r3, r2]
_0202C126:
	pop {r3-r5, pc}
	.balign 4
_0202C128: .word 0x0000270F

	thumb_func_start FUN_0202C12C
FUN_0202C12C: ; 0x0202C12C
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r1, #0x21
	add r4, r2, #0x0
	bl SavArray_get
	lsl r2, r5, #0x3
	lsl r1, r4, #0x1
	add r0, r0, r2
	ldrh r0, [r1, r0]
	pop {r3-r5, pc}
	.balign 4
