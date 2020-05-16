    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0200CA44
FUN_0200CA44: ; 0x0200CA44
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0200CA5C ; =0x021C48B8
	add r4, r1, #0x0
	add r3, r2, #0x0
	ldr r0, [r0, #0x18]
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0201B60C
	pop {r3-r5, pc}
	nop
_0200CA5C: .word 0x021C48B8

	thumb_func_start FUN_0200CA60
FUN_0200CA60: ; 0x0200CA60
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0200CA78 ; =0x021C48B8
	add r4, r1, #0x0
	add r3, r2, #0x0
	ldr r0, [r0, #0x1c]
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0201B60C
	pop {r3-r5, pc}
	nop
_0200CA78: .word 0x021C48B8

	thumb_func_start FUN_0200CA7C
FUN_0200CA7C: ; 0x0200CA7C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0200CA94 ; =0x021C48B8
	add r4, r1, #0x0
	add r3, r2, #0x0
	ldr r0, [r0, #0x24]
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0201B60C
	pop {r3-r5, pc}
	nop
_0200CA94: .word 0x021C48B8

	thumb_func_start FUN_0200CA98
FUN_0200CA98: ; 0x0200CA98
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0200CAB0 ; =0x021C48B8
	add r4, r1, #0x0
	add r3, r2, #0x0
	ldr r0, [r0, #0x20]
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0201B60C
	pop {r3-r5, pc}
	nop
_0200CAB0: .word 0x021C48B8

	thumb_func_start FUN_0200CAB4
FUN_0200CAB4: ; 0x0200CAB4
	ldr r3, _0200CAB8 ; =FUN_0201B6A0
	bx r3
	.balign 4
_0200CAB8: .word FUN_0201B6A0
