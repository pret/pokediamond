	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	.extern MOD21_02254B60
	.extern MOD21_02254BF4
	.extern MOD21_02254C14
	.extern MOD21_02254C40

	thumb_func_start MOD21_02254C5C
MOD21_02254C5C: ; 0x02254C5C
	push {r4, r5, lr}
	sub sp, #0x1c
	add r4, r0, #0
	ldr r0, [r4]
	ldr r2, _02254D74 ; =0x04000280
	ldr r0, [r0]
	mov r3, #0
	strh r3, [r2]
	str r0, [r2, #0x10]
	add r0, r2, #0
	mov r1, #0xa
	add r0, #0x18
	str r1, [r0]
	str r3, [r0, #4]
	lsr r0, r2, #0xb
_02254C7A:
	ldrh r1, [r2]
	tst r1, r0
	bne _02254C7A
	ldr r0, _02254D78 ; =0x040002A0
	add r3, r0, #0
	ldr r1, [r0]
	sub r3, #0x20
	lsr r0, r0, #0xb
_02254C8A:
	ldrh r2, [r3]
	tst r2, r0
	bne _02254C8A
	ldr r0, _02254D7C ; =0x040002A8
	add r2, r4, #0
	ldr r5, [r0]
	mov r0, #4
	str r0, [sp]
	mov r0, #9
	lsl r1, r1, #0x1a
	str r0, [sp, #4]
	add r2, #0x30
	str r2, [sp, #8]
	lsr r1, r1, #0x18
	str r1, [sp, #0xc]
	mov r1, #0
	str r1, [sp, #0x10]
	mov r1, #0x28
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #3
	mov r3, #7
	bl FUN_02018170
	mov r0, #4
	str r0, [sp]
	mov r0, #9
	add r1, r4, #0
	str r0, [sp, #4]
	add r1, #0x30
	str r1, [sp, #8]
	lsl r1, r5, #0x1a
	lsr r1, r1, #0x18
	str r1, [sp, #0xc]
	mov r1, #0
	str r1, [sp, #0x10]
	mov r1, #0x28
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #8
	mov r3, #7
	bl FUN_02018170
	ldr r0, [r4]
	ldr r2, _02254D74 ; =0x04000280
	ldr r0, [r0, #4]
	mov r3, #0
	strh r3, [r2]
	str r0, [r2, #0x10]
	add r0, r2, #0
	mov r1, #0xa
	add r0, #0x18
	str r1, [r0]
	str r3, [r0, #4]
	lsr r0, r2, #0xb
_02254D00:
	ldrh r1, [r2]
	tst r1, r0
	bne _02254D00
	ldr r0, _02254D78 ; =0x040002A0
	add r3, r0, #0
	ldr r1, [r0]
	sub r3, #0x20
	lsr r0, r0, #0xb
_02254D10:
	ldrh r2, [r3]
	tst r2, r0
	bne _02254D10
	ldr r0, _02254D7C ; =0x040002A8
	add r2, r4, #0
	ldr r5, [r0]
	mov r0, #4
	str r0, [sp]
	mov r0, #9
	lsl r1, r1, #0x1a
	str r0, [sp, #4]
	add r2, #0x30
	str r2, [sp, #8]
	lsr r1, r1, #0x18
	str r1, [sp, #0xc]
	mov r1, #0
	str r1, [sp, #0x10]
	mov r1, #0x28
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #0xf
	mov r3, #7
	bl FUN_02018170
	mov r0, #4
	str r0, [sp]
	mov r0, #9
	add r1, r4, #0
	str r0, [sp, #4]
	add r1, #0x30
	str r1, [sp, #8]
	lsl r1, r5, #0x1a
	lsr r1, r1, #0x18
	str r1, [sp, #0xc]
	mov r1, #0
	str r1, [sp, #0x10]
	mov r1, #0x28
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #0x14
	mov r3, #7
	bl FUN_02018170
	add sp, #0x1c
	pop {r4, r5, pc}
	nop
_02254D74: .word 0x04000280
_02254D78: .word 0x040002A0
_02254D7C: .word 0x040002A8
	thumb_func_end MOD21_02254C5C

	.section .rodata

	.global MOD21_02254D90
MOD21_02254D90: ; 0x02254D90
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD21_02254DAC
MOD21_02254DAC: ; 0x02254DAC
	.word 0x00, MOD21_02254B60, 0x00
	.word 0x01, MOD21_02254BF4, 0x00
	.word 0x02, MOD21_02254C14, 0x00
	.word 0x03, MOD21_02254C40, 0x00
	.word 0x00, 0x00000000, 0x00
