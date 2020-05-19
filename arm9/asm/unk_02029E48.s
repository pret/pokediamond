	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02029E48
FUN_02029E48: ; 0x02029E48
	mov r1, #0x0
	strh r1, [r0, #0x0]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	bx lr
	.balign 4

	thumb_func_start FUN_02029E54
FUN_02029E54: ; 0x02029E54
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldrh r6, [r5, #0x0]
	ldr r0, _02029EB8 ; =0x000003E7
	cmp r6, r0
	bne _02029E6C
	ldrb r0, [r5, #0x2]
	cmp r0, #0x3b
	bne _02029E6C
	ldrb r0, [r5, #0x3]
	cmp r0, #0x3b
	beq _02029EB4
_02029E6C:
	ldrb r0, [r5, #0x3]
	ldrb r4, [r5, #0x2]
	add r7, r0, r1
	cmp r7, #0x3b
	bls _02029EAE
	add r0, r7, #0x0
	mov r1, #0x3c
	bl _u32_div_f
	add r4, r4, r0
	add r0, r7, #0x0
	mov r1, #0x3c
	bl _u32_div_f
	add r7, r1, #0x0
	cmp r4, #0x3b
	bls _02029EAE
	add r0, r4, #0x0
	mov r1, #0x3c
	bl _u32_div_f
	add r6, r6, r0
	add r0, r4, #0x0
	mov r1, #0x3c
	bl _u32_div_f
	ldr r0, _02029EB8 ; =0x000003E7
	add r4, r1, #0x0
	cmp r6, r0
	blo _02029EAE
	mov r4, #0x3b
	add r6, r0, #0x0
	add r7, r4, #0x0
_02029EAE:
	strh r6, [r5, #0x0]
	strb r4, [r5, #0x2]
	strb r7, [r5, #0x3]
_02029EB4:
	pop {r3-r7, pc}
	nop
_02029EB8: .word 0x000003E7

	thumb_func_start FUN_02029EBC
FUN_02029EBC: ; 0x02029EBC
	ldrh r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02029EC0
FUN_02029EC0: ; 0x02029EC0
	ldrb r0, [r0, #0x2]
	bx lr
