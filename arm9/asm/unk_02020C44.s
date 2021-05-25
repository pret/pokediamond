	.include "asm/macros.inc"
    .include "global.inc"

	.extern NNS_GfdDefaultFuncAllocTexVram
	.extern NNS_GfdDefaultFuncAllocPlttVram
	.extern NNS_GfdDefaultFuncFreePlttVram
	.extern NNS_GfdDefaultFuncFreeTexVram

	.text

	thumb_func_start FUN_02020C44
FUN_02020C44: ; 0x02020C44
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0xc
	bl AllocFromHeap
	add r6, r0, #0x0
	bne _02020C5A
	bl GF_AssertFail
_02020C5A:
	add r0, r4, #0x0
	lsl r1, r7, #0x3
	bl AllocFromHeap
	str r0, [r6, #0x0]
	cmp r0, #0x0
	bne _02020C6C
	bl GF_AssertFail
_02020C6C:
	mov r4, #0x0
	cmp r7, #0x0
	ble _02020C84
	add r5, r4, #0x0
_02020C74:
	ldr r0, [r6, #0x0]
	add r0, r0, r5
	bl FUN_02020E78
	add r4, r4, #0x1
	add r5, #0x8
	cmp r4, r7
	blt _02020C74
_02020C84:
	str r7, [r6, #0x4]
	mov r0, #0x0
	str r0, [r6, #0x8]
	add r0, r6, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02020C90
FUN_02020C90: ; 0x02020C90
	push {r4, lr}
	add r4, r0, #0x0
	bne _02020C9A
	bl GF_AssertFail
_02020C9A:
	add r0, r4, #0x0
	bl FUN_02020D9C
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02020CB0
FUN_02020CB0: ; 0x02020CB0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020CBE
	bl GF_AssertFail
_02020CBE:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02020DD8
	cmp r0, #0x0
	bne _02020CCE
	mov r0, #0x1
	pop {r3-r5, pc}
_02020CCE:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02020CD4
FUN_02020CD4: ; 0x02020CD4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r6, r2, #0x0
	cmp r5, #0x0
	bne _02020CE4
	bl GF_AssertFail
_02020CE4:
	add r0, r5, #0x0
	bl FUN_02020E48
	add r4, r0, #0x0
	bne _02020CF2
	bl GF_AssertFail
_02020CF2:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02020CB0
	cmp r0, #0x1
	beq _02020D02
	bl GF_AssertFail
_02020D02:
	str r7, [r4, #0x4]
	str r6, [r4, #0x0]
	ldr r0, [r5, #0x8]
	add r0, r0, #0x1
	str r0, [r5, #0x8]
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02020D10
FUN_02020D10: ; 0x02020D10
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x0]
	cmp r5, #0x0
	bne _02020D22
	bl GF_AssertFail
_02020D22:
	cmp r6, #0x0
	bne _02020D2A
	bl GF_AssertFail
_02020D2A:
	add r0, r5, #0x0
	bl FUN_02020E48
	add r4, r0, #0x0
	bne _02020D38
	bl GF_AssertFail
_02020D38:
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02020CB0
	cmp r0, #0x1
	beq _02020D48
	bl GF_AssertFail
_02020D48:
	ldr r0, [sp, #0x0]
	add r1, r6, #0x0
	bl FUN_020161A4
	str r0, [r4, #0x4]
	cmp r0, #0x0
	bne _02020D5A
	bl GF_AssertFail
_02020D5A:
	str r7, [r4, #0x0]
	ldr r0, [r5, #0x8]
	add r0, r0, #0x1
	str r0, [r5, #0x8]
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02020D68
FUN_02020D68: ; 0x02020D68
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020D76
	bl GF_AssertFail
_02020D76:
	cmp r4, #0x0
	bne _02020D7E
	bl GF_AssertFail
_02020D7E:
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _02020D8C
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x4]
_02020D8C:
	mov r0, #0x0
	mvn r0, r0
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x8]
	sub r0, r0, #0x1
	str r0, [r5, #0x8]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02020D9C
FUN_02020D9C: ; 0x02020D9C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bne _02020DA6
	bl GF_AssertFail
_02020DA6:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	bne _02020DB0
	bl GF_AssertFail
_02020DB0:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02020DD6
	add r4, r6, #0x0
	sub r7, r6, #0x1
_02020DBC:
	ldr r1, [r5, #0x0]
	ldr r0, [r1, r4]
	cmp r0, r7
	beq _02020DCC
	add r0, r5, #0x0
	add r1, r1, r4
	bl FUN_02020D68
_02020DCC:
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0x8
	cmp r6, r0
	blt _02020DBC
_02020DD6:
	pop {r3-r7, pc}

	thumb_func_start FUN_02020DD8
FUN_02020DD8: ; 0x02020DD8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020DE6
	bl GF_AssertFail
_02020DE6:
	ldr r6, [r5, #0x4]
	mov r1, #0x0
	cmp r6, #0x0
	ble _02020E06
	ldr r3, [r5, #0x0]
	add r2, r3, #0x0
_02020DF2:
	ldr r0, [r2, #0x0]
	cmp r4, r0
	bne _02020DFE
	lsl r0, r1, #0x3
	add r0, r3, r0
	pop {r4-r6, pc}
_02020DFE:
	add r1, r1, #0x1
	add r2, #0x8
	cmp r1, r6
	blt _02020DF2
_02020E06:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02020E0C
FUN_02020E0C: ; 0x02020E0C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02020E16
	bl GF_AssertFail
_02020E16:
	ldr r0, [r4, #0x4]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02020E1C
FUN_02020E1C: ; 0x02020E1C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020E2A
	bl GF_AssertFail
_02020E2A:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	beq _02020E34
	bl FreeToHeap
_02020E34:
	str r4, [r5, #0x4]
	pop {r3-r5, pc}

	thumb_func_start FUN_02020E38
FUN_02020E38: ; 0x02020E38
	push {r4, lr}
	add r4, r0, #0x0
	bne _02020E42
	bl GF_AssertFail
_02020E42:
	ldr r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02020E48
FUN_02020E48: ; 0x02020E48
	push {r3-r5, lr}
	add r4, r0, #0x0
	bne _02020E52
	bl GF_AssertFail
_02020E52:
	ldr r5, [r4, #0x4]
	mov r2, #0x0
	cmp r5, #0x0
	ble _02020E74
	ldr r4, [r4, #0x0]
	sub r0, r2, #0x1
	add r3, r4, #0x0
_02020E60:
	ldr r1, [r3, #0x0]
	cmp r1, r0
	bne _02020E6C
	lsl r0, r2, #0x3
	add r0, r4, r0
	pop {r3-r5, pc}
_02020E6C:
	add r2, r2, #0x1
	add r3, #0x8
	cmp r2, r5
	blt _02020E60
_02020E74:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02020E78
FUN_02020E78: ; 0x02020E78
	push {r4, lr}
	add r4, r0, #0x0
	bne _02020E82
	bl GF_AssertFail
_02020E82:
	mov r0, #0x0
	mvn r0, r0
	str r0, [r4, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x4]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02020E90
FUN_02020E90: ; 0x02020E90
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x8
	bl AllocFromHeap
	add r7, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02020C44
	mov r1, #0x18
	str r0, [r7, #0x0]
	add r0, r4, #0x0
	mul r1, r6
	bl AllocFromHeap
	mov r4, #0x0
	str r0, [r7, #0x4]
	cmp r6, #0x0
	ble _02020ECE
	add r5, r4, #0x0
_02020EBE:
	ldr r0, [r7, #0x4]
	add r0, r0, r5
	bl FUN_0202120C
	add r4, r4, #0x1
	add r5, #0x18
	cmp r4, r6
	blt _02020EBE
_02020ECE:
	add r0, r7, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02020ED4
FUN_02020ED4: ; 0x02020ED4
	push {r4, lr}
	add r4, r0, #0x0
	bne _02020EDE
	bl GF_AssertFail
_02020EDE:
	add r0, r4, #0x0
	bl FUN_02021010
	ldr r0, [r4, #0x0]
	bl FUN_02020C90
	ldr r0, [r4, #0x4]
	bl FreeToHeap
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start FUN_02020EF8
FUN_02020EF8: ; 0x02020EF8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020F06
	bl GF_AssertFail
_02020F06:
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_02020CB0
	pop {r3-r5, pc}

	thumb_func_start FUN_02020F10
FUN_02020F10: ; 0x02020F10
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r3, #0x0
	str r2, [sp, #0x0]
	cmp r5, #0x0
	bne _02020F22
	bl GF_AssertFail
_02020F22:
	add r0, r5, #0x0
	bl FUN_020211DC
	add r4, r0, #0x0
	strh r7, [r4, #0x16]
	ldrh r0, [r4, #0x16]
	cmp r0, #0x1
	bne _02020F40
	ldr r1, [sp, #0x18]
	add r0, r6, #0x0
	bl FUN_02021310
	add r1, r0, #0x0
	str r6, [r4, #0x10]
	b _02020F46
_02020F40:
	mov r0, #0x0
	add r1, r6, #0x0
	str r0, [r4, #0x10]
_02020F46:
	ldr r0, [r5, #0x0]
	ldr r2, [sp, #0x0]
	bl FUN_02020CD4
	str r0, [r4, #0x0]
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02020F54
FUN_02020F54: ; 0x02020F54
	push {r3-r4, lr}
	sub sp, #0x4
	ldr r4, [sp, #0x10]
	str r4, [sp, #0x0]
	bl FUN_02020F10
	add r4, r0, #0x0
	bl FUN_02021174
	add r0, r4, #0x0
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_02020F6C
FUN_02020F6C: ; 0x02020F6C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020F7A
	bl GF_AssertFail
_02020F7A:
	cmp r4, #0x0
	bne _02020F82
	bl GF_AssertFail
_02020F82:
	ldrh r0, [r4, #0x16]
	cmp r0, #0x1
	bne _02020F98
	ldrh r0, [r4, #0x14]
	cmp r0, #0x0
	bne _02020F98
	ldr r0, [r4, #0x10]
	bl FreeToHeap
	mov r0, #0x0
	strh r0, [r4, #0x16]
_02020F98:
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	beq _02020FA4
	ldr r0, [r5, #0x0]
	bl FUN_02020D68
_02020FA4:
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _02020FB8
	ldr r1, _02020FE8 ; =NNS_GfdDefaultFuncFreeTexVram
	ldr r1, [r1, #0x0]
	blx r1
	cmp r0, #0x0
	beq _02020FB8
	bl GF_AssertFail
_02020FB8:
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	beq _02020FCC
	ldr r1, _02020FE8 ; =NNS_GfdDefaultFuncFreeTexVram
	ldr r1, [r1, #0x0]
	blx r1
	cmp r0, #0x0
	beq _02020FCC
	bl GF_AssertFail
_02020FCC:
	ldr r0, [r4, #0xc]
	cmp r0, #0x0
	beq _02020FE0
	ldr r1, _02020FEC ; =NNS_GfdDefaultFuncFreePlttVram
	ldr r1, [r1, #0x0]
	blx r1
	cmp r0, #0x0
	beq _02020FE0
	bl GF_AssertFail
_02020FE0:
	add r0, r4, #0x0
	bl FUN_0202120C
	pop {r3-r5, pc}
	.balign 4
_02020FE8: .word NNS_GfdDefaultFuncFreeTexVram
_02020FEC: .word NNS_GfdDefaultFuncFreePlttVram

	thumb_func_start FUN_02020FF0
FUN_02020FF0: ; 0x02020FF0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020FFE
	bl GF_AssertFail
_02020FFE:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02021050
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02020F6C
	pop {r3-r5, pc}

	thumb_func_start FUN_02021010
FUN_02021010: ; 0x02021010
	push {r4-r6, lr}
	add r5, r0, #0x0
	bne _0202101A
	bl GF_AssertFail
_0202101A:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	bne _02021024
	bl GF_AssertFail
_02021024:
	ldr r0, [r5, #0x0]
	mov r6, #0x0
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	ble _0202104C
	add r4, r6, #0x0
_02021030:
	ldr r1, [r5, #0x4]
	ldr r0, [r1, r4]
	cmp r0, #0x0
	beq _02021040
	add r0, r5, #0x0
	add r1, r1, r4
	bl FUN_02020F6C
_02021040:
	ldr r0, [r5, #0x0]
	add r6, r6, #0x1
	ldr r0, [r0, #0x4]
	add r4, #0x18
	cmp r6, r0
	blt _02021030
_0202104C:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02021050
FUN_02021050: ; 0x02021050
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r7, r1, #0x0
	cmp r6, #0x0
	bne _0202105E
	bl GF_AssertFail
_0202105E:
	ldr r0, [r6, #0x0]
	mov r4, #0x0
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	ble _02021092
	add r5, r4, #0x0
_0202106A:
	ldr r1, [r6, #0x4]
	ldr r0, [r1, r5]
	cmp r0, #0x0
	beq _02021086
	add r0, r1, r5
	bl FUN_02021098
	cmp r0, r7
	bne _02021086
	mov r0, #0x18
	ldr r1, [r6, #0x4]
	mul r0, r4
	add r0, r1, r0
	pop {r3-r7, pc}
_02021086:
	ldr r0, [r6, #0x0]
	add r4, r4, #0x1
	ldr r0, [r0, #0x4]
	add r5, #0x18
	cmp r4, r0
	blt _0202106A
_02021092:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02021098
FUN_02021098: ; 0x02021098
	push {r4, lr}
	add r4, r0, #0x0
	bne _020210A2
	bl GF_AssertFail
_020210A2:
	ldr r0, [r4, #0x0]
	bl FUN_02020E38
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020210AC
FUN_020210AC: ; 0x020210AC
	push {r4, lr}
	add r4, r0, #0x0
	bne _020210B6
	bl GF_AssertFail
_020210B6:
	add r0, r4, #0x0
	bl FUN_02021220
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020210C0
FUN_020210C0: ; 0x020210C0
	push {r4, lr}
	add r4, r0, #0x0
	bne _020210CA
	bl GF_AssertFail
_020210CA:
	ldrh r0, [r4, #0x14]
	cmp r0, #0x0
	beq _020210D4
	bl GF_AssertFail
_020210D4:
	ldr r0, [r4, #0xc]
	cmp r0, #0x0
	bne _020210E0
	bl GF_AssertFail
	pop {r4, pc}
_020210E0:
	add r0, r4, #0x0
	bl FUN_02021230
	add r1, r4, #0x0
	bl FUN_020212B8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020210F0
FUN_020210F0: ; 0x020210F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020210FE
	bl GF_AssertFail
_020210FE:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02021050
	bl FUN_020210C0
	pop {r3-r5, pc}

	thumb_func_start FUN_0202110C
FUN_0202110C: ; 0x0202110C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02021116
	bl GF_AssertFail
_02021116:
	ldrh r0, [r4, #0x16]
	cmp r0, #0x0
	bne _02021122
	bl GF_AssertFail
	pop {r4, pc}
_02021122:
	ldrh r0, [r4, #0x14]
	cmp r0, #0x0
	beq _0202112E
	bl GF_AssertFail
	pop {r4, pc}
_0202112E:
	add r0, r4, #0x0
	bl FUN_02021230
	bl FUN_020212F8
	add r0, r4, #0x0
	bl FUN_02021220
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0x8]
	ldr r3, [r4, #0xc]
	bl FUN_020212E4
	ldr r0, [r4, #0x10]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x10]
	mov r0, #0x1
	strh r0, [r4, #0x14]
	pop {r4, pc}

	thumb_func_start FUN_02021158
FUN_02021158: ; 0x02021158
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02021166
	bl GF_AssertFail
_02021166:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02021050
	bl FUN_0202110C
	pop {r3-r5, pc}

	thumb_func_start FUN_02021174
FUN_02021174: ; 0x02021174
	push {r4, lr}
	add r4, r0, #0x0
	bne _0202117E
	bl GF_AssertFail
_0202117E:
	ldrh r0, [r4, #0x14]
	cmp r0, #0x0
	beq _02021188
	bl GF_AssertFail
_02021188:
	ldr r0, [r4, #0xc]
	cmp r0, #0x0
	beq _02021194
	bl GF_AssertFail
	pop {r4, pc}
_02021194:
	add r0, r4, #0x0
	bl FUN_02021230
	add r2, r4, #0x0
	add r1, r4, #0x4
	add r4, #0xc
	add r2, #0x8
	add r3, r4, #0x0
	bl FUN_02021248
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020211AC
FUN_020211AC: ; 0x020211AC
	push {r4, lr}
	add r4, r0, #0x0
	bne _020211B6
	bl GF_AssertFail
_020211B6:
	ldr r0, [r4, #0x4]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020211BC
FUN_020211BC: ; 0x020211BC
	push {r4, lr}
	add r4, r0, #0x0
	bne _020211C6
	bl GF_AssertFail
_020211C6:
	ldr r0, [r4, #0x8]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020211CC
FUN_020211CC: ; 0x020211CC
	push {r4, lr}
	add r4, r0, #0x0
	bne _020211D6
	bl GF_AssertFail
_020211D6:
	ldr r0, [r4, #0xc]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020211DC
FUN_020211DC: ; 0x020211DC
	push {r3-r4}
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	ldr r4, [r1, #0x4]
	cmp r4, #0x0
	ble _02021204
	ldr r3, [r0, #0x4]
_020211EA:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	bne _020211FC
	ldr r1, [r0, #0x4]
	mov r0, #0x18
	mul r0, r2
	add r0, r1, r0
	pop {r3-r4}
	bx lr
_020211FC:
	add r2, r2, #0x1
	add r3, #0x18
	cmp r2, r4
	blt _020211EA
_02021204:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_0202120C
FUN_0202120C: ; 0x0202120C
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	str r1, [r0, #0x8]
	str r1, [r0, #0xc]
	strh r1, [r0, #0x14]
	str r1, [r0, #0x10]
	strh r1, [r0, #0x14]
	bx lr
	.balign 4

	thumb_func_start FUN_02021220
FUN_02021220: ; 0x02021220
	push {r3, lr}
	ldr r0, [r0, #0x0]
	bl FUN_02020E0C
	bl NNS_G3dGetTex
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02021230
FUN_02021230: ; 0x02021230
	push {r3, lr}
	ldrh r1, [r0, #0x16]
	cmp r1, #0x0
	bne _02021240
	ldr r0, [r0, #0x0]
	bl FUN_02020E0C
	b _02021242
_02021240:
	ldr r0, [r0, #0x10]
_02021242:
	bl NNS_G3dGetTex
	pop {r3, pc}

	thumb_func_start FUN_02021248
FUN_02021248: ; 0x02021248
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	bl NNS_G3dTexGetRequiredSize
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl NNS_G3dTex4x4GetRequiredSize
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl NNS_G3dPlttGetRequiredSize
	add r4, r0, #0x0
	cmp r7, #0x0
	beq _0202127E
	ldr r3, _020212B0 ; =NNS_GfdDefaultFuncAllocTexVram
	mov r1, #0x0
	ldr r3, [r3, #0x0]
	add r0, r7, #0x0
	add r2, r1, #0x0
	blx r3
	ldr r1, [sp, #0x0]
	str r0, [r1, #0x0]
_0202127E:
	cmp r6, #0x0
	beq _02021292
	ldr r3, _020212B0 ; =NNS_GfdDefaultFuncAllocTexVram
	add r0, r6, #0x0
	ldr r3, [r3, #0x0]
	mov r1, #0x1
	mov r2, #0x0
	blx r3
	ldr r1, [sp, #0x4]
	str r0, [r1, #0x0]
_02021292:
	cmp r4, #0x0
	beq _020212AC
	ldr r3, _020212B4 ; =NNS_GfdDefaultFuncAllocPlttVram
	mov r1, #0x2
	ldrh r2, [r5, #0x20]
	lsl r1, r1, #0xe
	ldr r3, [r3, #0x0]
	and r1, r2
	add r0, r4, #0x0
	mov r2, #0x0
	blx r3
	ldr r1, [sp, #0x8]
	str r0, [r1, #0x0]
_020212AC:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_020212B0: .word NNS_GfdDefaultFuncAllocTexVram
_020212B4: .word NNS_GfdDefaultFuncAllocPlttVram

	thumb_func_start FUN_020212B8
FUN_020212B8: ; 0x020212B8
	push {r4, lr}
	add r3, r1, #0x0
	ldr r1, [r3, #0x4]
	ldr r2, [r3, #0x8]
	ldr r3, [r3, #0xc]
	add r4, r0, #0x0
	bl FUN_020212E4
	ldr r1, [r4, #0x4]
	add r0, r4, #0x0
	bl DC_FlushRange
	add r0, r4, #0x0
	mov r1, #0x1
	bl NNS_G3dTexLoad
	add r0, r4, #0x0
	mov r1, #0x1
	bl NNS_G3dPlttLoad
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020212E4
FUN_020212E4: ; 0x020212E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r3, #0x0
	bl NNS_G3dTexSetTexKey
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl NNS_G3dPlttSetPlttKey
	pop {r3-r5, pc}

	thumb_func_start FUN_020212F8
FUN_020212F8: ; 0x020212F8
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x0
	bl NNS_G3dTexReleaseTexKey
	add r0, r4, #0x0
	bl NNS_G3dPlttReleasePlttKey
	add sp, #0x8
	pop {r4, pc}

	thumb_func_start FUN_02021310
FUN_02021310: ; 0x02021310
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02021334
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl AllocFromHeap
	add r1, r6, #0x0
	add r2, r5, #0x0
	add r4, r0, #0x0
	bl memcpy
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02021334
FUN_02021334: ; 0x02021334
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl NNS_G3dGetTex
	add r4, r0, #0x0
	bne _02021344
	bl GF_AssertFail
_02021344:
	ldr r0, [r4, #0x14]
	add r0, r4, r0
	sub r0, r0, r5
	pop {r3-r5, pc}
