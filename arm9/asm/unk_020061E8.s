	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

	thumb_func_start FUN_020061E8
FUN_020061E8: ; 0x020061E8
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r6, r0, #0x0
	add r7, r2, #0x0
	cmp r5, #0x0
	beq _0200620C
	add r0, r3, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	bne _02006202
	mov r0, #0x0
	pop {r3-r7, pc}
_02006202:
	mov r1, #0x0
	add r2, r5, #0x0
	bl memset
	b _0200620E
_0200620C:
	mov r4, #0x0
_0200620E:
	add r0, r6, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl FUN_0200CA44
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200621C
FUN_0200621C: ; 0x0200621C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0201B6C8
	cmp r0, #0x0
	beq _0200622C
	bl FUN_02016A18
_0200622C:
	add r0, r4, #0x0
	bl FUN_0200CAB4
	pop {r4, pc}
