	.include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020EEA7C
UNK_020EEA7C: ; 0x020EEA7C
	.short 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0002, 0x0002
	.short 0x0002, 0x0002, 0x0003, 0x0003, 0x0003, 0x0007, 0x0007, 0x0007
	.short 0x000A, 0x000A, 0x000B, 0x000B, 0x000B, 0x000B, 0x0014, 0x001E
	.short 0x0023, 0x0028, 0x01F4, 0x2710, 0x001E, 0x001E, 0x0002, 0x0005
	.short 0x0001, 0x0001, 0x0005, 0x0003, 0x0001, 0x0001

	.section .data

	.global UNK_02105CD8
UNK_02105CD8: ; 0x02105CD8
	.byte 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_02029FB0
FUN_02029FB0: ; 0x02029FB0
	mov r0, #0x53
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_02029FB8
FUN_02029FB8: ; 0x02029FB8
	ldr r3, _02029FC4 ; =MIi_CpuClear32
	mov r2, #0x53
	add r1, r0, #0x0
	mov r0, #0x0
	lsl r2, r2, #0x2
	bx r3
	.balign 4
_02029FC4: .word MIi_CpuClear32

	thumb_func_start FUN_02029FC8
FUN_02029FC8: ; 0x02029FC8
	ldr r3, _02029FD0 ; =SavArray_get
	mov r1, #0x14
	bx r3
	nop
_02029FD0: .word SavArray_get

	thumb_func_start FUN_02029FD4
FUN_02029FD4: ; 0x02029FD4
	push {r3, lr}
	cmp r1, #0x2c
	bge _02029FE0
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	pop {r3, pc}
_02029FE0:
	cmp r1, #0x79
	bge _02029FF0
	sub r1, #0x2c
	lsl r1, r1, #0x1
	add r0, r0, r1
	add r0, #0xb0
	ldrh r0, [r0, #0x0]
	pop {r3, pc}
_02029FF0:
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02029FF8
FUN_02029FF8: ; 0x02029FF8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x2c
	bge _0202A008
	lsl r0, r4, #0x2
	str r2, [r5, r0]
	b _0202A01E
_0202A008:
	cmp r4, #0x79
	bge _0202A01A
	add r0, r4, #0x0
	sub r0, #0x2c
	lsl r0, r0, #0x1
	add r0, r5, r0
	add r0, #0xb0
	strh r2, [r0, #0x0]
	b _0202A01E
_0202A01A:
	bl GF_AssertFail
_0202A01E:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029FD4
	pop {r3-r5, pc}

	thumb_func_start FUN_0202A028
FUN_0202A028: ; 0x0202A028
	push {r3, lr}
	cmp r0, #0x2c
	bge _0202A03E
	ldr r1, _0202A05C ; =UNK_02105CD8
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0202A03A
	ldr r0, _0202A060 ; =0x3B9AC9FF
	pop {r3, pc}
_0202A03A:
	ldr r0, _0202A064 ; =0x000F423F
	pop {r3, pc}
_0202A03E:
	cmp r0, #0x79
	bge _0202A052
	ldr r1, _0202A05C ; =UNK_02105CD8
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0202A04E
	ldr r0, _0202A068 ; =0x0000FFFF
	pop {r3, pc}
_0202A04E:
	ldr r0, _0202A06C ; =0x0000270F
	pop {r3, pc}
_0202A052:
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3, pc}
	nop
_0202A05C: .word UNK_02105CD8
_0202A060: .word 0x3B9AC9FF
_0202A064: .word 0x000F423F
_0202A068: .word 0x0000FFFF
_0202A06C: .word 0x0000270F

	thumb_func_start FUN_0202A070
FUN_0202A070: ; 0x0202A070
	lsl r1, r0, #0x1
	ldr r0, _0202A078 ; =UNK_020EEA7C
	ldrh r0, [r0, r1]
	bx lr
	.balign 4
_0202A078: .word UNK_020EEA7C

	thumb_func_start FUN_0202A07C
FUN_0202A07C: ; 0x0202A07C
	push {r4-r6, lr}
	add r5, r1, #0x0
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r4, r2, #0x0
	bl FUN_0202A028
	add r2, r0, #0x0
	cmp r4, r2
	bhs _0202A09C
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02029FF8
	pop {r4-r6, pc}
_0202A09C:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02029FF8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202A0A8
FUN_0202A0A8: ; 0x0202A0A8
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r7, r0, #0x0
	add r0, r6, #0x0
	add r5, r2, #0x0
	bl FUN_0202A028
	add r4, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	bl FUN_02029FD4
	cmp r5, r4
	bls _0202A0C6
	add r5, r4, #0x0
_0202A0C6:
	cmp r0, r5
	bhs _0202A0D6
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02029FF8
	pop {r3-r7, pc}
_0202A0D6:
	cmp r0, r4
	bls _0202A0E4
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02029FF8
_0202A0E4:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202A0E8
FUN_0202A0E8: ; 0x0202A0E8
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0202A028
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02029FD4
	add r2, r0, #0x1
	cmp r2, r4
	bhs _0202A10E
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02029FF8
	pop {r4-r6, pc}
_0202A10E:
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02029FF8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202A11C
FUN_0202A11C: ; 0x0202A11C
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r7, r2, #0x0
	bl FUN_0202A028
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029FD4
	add r2, r0, r7
	cmp r2, r6
	bhs _0202A144
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029FF8
	pop {r3-r7, pc}
_0202A144:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02029FF8
	pop {r3-r7, pc}

	thumb_func_start FUN_0202A150
FUN_0202A150: ; 0x0202A150
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0202A028
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02029FD4
	cmp r0, r4
	bhi _0202A16C
	add r4, r0, #0x0
_0202A16C:
	add r0, r4, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0202A170
FUN_0202A170: ; 0x0202A170
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x26
	blt _0202A17E
	bl GF_AssertFail
_0202A17E:
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0202A150
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0202A070
	ldr r2, _0202A1B4 ; =0x05F5E0FF
	add r0, r6, r0
	cmp r0, r2
	bls _0202A1A0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0202A07C
	pop {r4-r6, pc}
_0202A1A0:
	add r0, r4, #0x0
	bl FUN_0202A070
	add r2, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0202A11C
	pop {r4-r6, pc}
	nop
_0202A1B4: .word 0x05F5E0FF

	thumb_func_start FUN_0202A1B8
FUN_0202A1B8: ; 0x0202A1B8
	ldr r3, _0202A1C0 ; =FUN_0202A150
	mov r1, #0x0
	bx r3
	nop
_0202A1C0: .word FUN_0202A150

	thumb_func_start FUN_0202A1C4
FUN_0202A1C4: ; 0x0202A1C4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	bl Pokedex_CheckMonCaughtFlag
	cmp r0, #0x0
	bne _0202A1DC
	add r0, r4, #0x0
	mov r1, #0x16
	bl FUN_0202A170
_0202A1DC:
	pop {r4, pc}
	.balign 4
