    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0205CDB4
FUN_0205CDB4: ; 0x0205CDB4
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020377AC
	bl FUN_02024ED8
	bl FUN_020254B4
	add r1, r0, #0x0
	beq _0205CDD2
	lsl r2, r1, #0x2
	ldr r1, _0205CDD4 ; =0x020F7220
	add r0, r4, #0x0
	ldr r1, [r1, r2]
	blx r1
_0205CDD2:
	pop {r4, pc}
	.balign 4
_0205CDD4: .word 0x020F7220

	thumb_func_start FUN_0205CDD8
FUN_0205CDD8: ; 0x0205CDD8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020377AC
	bl FUN_02024ED8
	bl FUN_020254B4
	cmp r0, #0x0
	beq _0205CDFA
	lsl r1, r0, #0x2
	ldr r0, _0205CDFC ; =0x020F7200
	ldr r1, [r0, r1]
	cmp r1, #0x0
	beq _0205CDFA
	add r0, r4, #0x0
	blx r1
_0205CDFA:
	pop {r4, pc}
	.balign 4
_0205CDFC: .word 0x020F7200

	thumb_func_start FUN_0205CE00
FUN_0205CE00: ; 0x0205CE00
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x4]
	bl FUN_020377AC
	bl FUN_02024ED8
	bl FUN_020254B4
	cmp r0, #0x0
	bne _0205CE22
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_0205CE22:
	lsl r1, r0, #0x2
	ldr r0, _0205CE44 ; =0x020F7240
	ldr r6, [r0, r1]
	cmp r6, #0x0
	beq _0205CE3E
	ldr r0, [sp, #0x20]
	ldr r3, [sp, #0x4]
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	blx r6
	add sp, #0x8
	pop {r3-r7, pc}
_0205CE3E:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0205CE44: .word 0x020F7240
