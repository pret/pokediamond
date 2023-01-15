	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F5D1C
UNK_020F5D1C: ; 0x020F5D1C
	.word FUN_02055C6C, FUN_02055C78, FUN_02055DAC, FUN_02055EF8
	.word FUN_02055F44, FUN_02055F90

	.global UNK_020F5D34
UNK_020F5D34: ; 0x020F5D34
	.word FUN_020548F0, 0x00000001
	.word FUN_020549FC, 0x00000002
	.word FUN_02054A24, 0x00000003
	.word FUN_02054A30, 0x00000004
	.word 0x00000000, 0x00000006

	.text

	thumb_func_start FUN_020557F4
FUN_020557F4: ; 0x020557F4
	push {r3-r7, lr}
	add r7, r1, #0x0
	mov r1, #0x0
	add r4, r2, #0x0
	mvn r1, r1
	add r5, r0, #0x0
	add r6, r3, #0x0
	cmp r4, r1
	bne _02055812
	add r2, sp, #0x8
	ldrh r2, [r2, #0x10]
	add r1, r6, #0x0
	bl FUN_02057060
	add r4, r0, #0x0
_02055812:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020563F0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020558A0
	cmp r0, #0x0
	beq _02055896
	add r3, sp, #0x8
	ldrh r3, [r3, #0x10]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02055900
	add r0, r5, #0x0
	bl MOD05_021E5FE0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02055BD4
	cmp r0, #0x1
	bne _0205584E
	add r0, r5, #0x0
	bl MOD05_021E7138
	pop {r3-r7, pc}
_0205584E:
	add r0, r5, #0x0
	bl FUN_020553C4
	cmp r0, #0x0
	bne _02055878
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020561D0
	cmp r0, #0x0
	beq _0205586C
	add r0, r5, #0x0
	bl MOD05_021E7138
	b _02055878
_0205586C:
	ldr r0, [sp, #0x1c]
	cmp r0, #0x1
	bne _02055878
	add r0, r5, #0x0
	bl MOD05_021E70F0
_02055878:
	add r0, sp, #0x8
	ldrh r0, [r0, #0x10]
	add r1, r7, #0x0
	add r2, r4, #0x0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r3, r6, #0x0
	bl FUN_02056110
	add r0, r5, #0x0
	bl FUN_02055928
	add r0, r5, #0x0
	bl FUN_02055968
_02055896:
	pop {r3-r7, pc}

	thumb_func_start FUN_02055898
FUN_02055898: ; 0x02055898
	ldr r3, _0205589C ; =FUN_020558A0
	bx r3
	.balign 4
_0205589C: .word FUN_020558A0

	thumb_func_start FUN_020558A0
FUN_020558A0: ; 0x020558A0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020553A0
	add r6, r0, #0x0
	bl FUN_0205AD98
	cmp r0, #0x1
	bne _020558B8
	mov r0, #0x1
	pop {r4-r6, pc}
_020558B8:
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	bne _020558C4
	mov r0, #0x0
	pop {r4-r6, pc}
_020558C4:
	add r0, r6, #0x0
	bl FUN_020586F0
	bl FUN_020570F0
	cmp r0, #0x1
	bne _020558FA
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02056B74
	cmp r0, #0x0
	bne _020558E4
	mov r0, #0x1
	pop {r4-r6, pc}
_020558E4:
	cmp r0, #0x20
	bne _020558F6
	add r0, r5, #0x0
	bl FUN_020553C4
	cmp r0, #0x2
	bne _020558F6
	mov r0, #0x1
	pop {r4-r6, pc}
_020558F6:
	mov r0, #0x0
	pop {r4-r6, pc}
_020558FA:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02055900
FUN_02055900: ; 0x02055900
	push {r4-r6, lr}
	add r6, r3, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02057028
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02057044
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0205543C
	add r0, r5, #0x0
	bl FUN_020557B0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02055928
FUN_02055928: ; 0x02055928
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020557BC
	cmp r0, #0x1
	bne _02055964
	add r0, r4, #0x0
	bl FUN_02055370
	cmp r0, #0x1
	bne _02055964
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_020556C8
	add r0, r4, #0x0
	bl FUN_02055764
	cmp r0, #0x1
	bne _02055964
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0205574C
	add r0, r4, #0x0
	bl FUN_020553A0
	mov r1, #0x0
	bl FUN_02058A18
_02055964:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02055968
FUN_02055968: ; 0x02055968
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl FUN_02055370
	cmp r0, #0x1
	bne _02055A20
	add r0, r4, #0x0
	bl FUN_020553A0
	add r4, r0, #0x0
	bl FUN_02058720
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	add r0, r4, #0x0
	bl FUN_020586F0
	bl FUN_0205B020
	add r1, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r1, r0
	bne _0205599C
	add r6, r5, #0x0
	b _020559A6
_0205599C:
	add r0, r4, #0x0
	bl FUN_02059C90
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
_020559A6:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02059B2C
	cmp r0, #0x1
	bne _020559B8
	ldr r0, _02055A24 ; =0x0000061F
	bl PlaySE
_020559B8:
	add r0, r5, #0x0
	bl FUN_02054AF0
	cmp r0, #0x1
	bne _020559C8
	ldr r0, _02055A28 ; =0x00000641
	bl PlaySE
_020559C8:
	add r0, r5, #0x0
	bl FUN_0205483C
	cmp r0, #0x1
	bne _020559D8
	ldr r0, _02055A2C ; =0x00000642
	bl PlaySE
_020559D8:
	add r0, r5, #0x0
	bl FUN_02054830
	add r0, r5, #0x0
	bl FUN_02054974
	cmp r0, #0x1
	bne _020559F8
	add r0, r5, #0x0
	bl FUN_02054984
	cmp r0, #0x1
	beq _020559F8
	ldr r0, _02055A30 ; =0x00000655
	bl PlaySE
_020559F8:
	add r0, r4, #0x0
	bl FUN_020586F0
	bl FUN_020570F0
	cmp r0, #0x0
	bne _02055A20
	add r0, r5, #0x0
	bl FUN_02054798
	cmp r0, #0x1
	beq _02055A1A
	add r0, r6, #0x0
	bl FUN_02054798
	cmp r0, #0x1
	bne _02055A20
_02055A1A:
	ldr r0, _02055A34 ; =0x00000653
	bl PlaySE
_02055A20:
	pop {r4-r6, pc}
	nop
_02055A24: .word 0x0000061F
_02055A28: .word 0x00000641
_02055A2C: .word 0x00000642
_02055A30: .word 0x00000655
_02055A34: .word 0x00000653

	thumb_func_start FUN_02055A38
FUN_02055A38: ; 0x02055A38
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_02055370
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02055378
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020553A0
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02055374
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	bl FUN_02055BEC
	cmp r0, #0x0
	beq _02055A76
	cmp r0, #0x5
	beq _02055A76
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_02055374
	pop {r3-r7, pc}
_02055A76:
	add r0, r7, #0x0
	bl FUN_0205AD98
	cmp r0, #0x0
	bne _02055AC2
	cmp r6, #0x0
	beq _02055B10
	cmp r6, #0x1
	beq _02055A8E
	cmp r6, #0x2
	beq _02055AB8
	pop {r3-r7, pc}
_02055A8E:
	add r0, r7, #0x0
	bl FUN_020586F0
	bl FUN_020570F0
	cmp r0, #0x1
	beq _02055B10
	cmp r4, #0x0
	beq _02055AA4
	cmp r4, #0x3
	bne _02055AAE
_02055AA4:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02055374
	pop {r3-r7, pc}
_02055AAE:
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_02055374
	pop {r3-r7, pc}
_02055AB8:
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_02055374
	pop {r3-r7, pc}
_02055AC2:
	add r0, r7, #0x0
	bl FUN_0205AE28
	cmp r0, #0x1
	bne _02055B10
	cmp r6, #0x0
	beq _02055B10
	cmp r6, #0x1
	beq _02055ADA
	cmp r6, #0x2
	beq _02055AF6
	pop {r3-r7, pc}
_02055ADA:
	cmp r4, #0x0
	beq _02055B10
	cmp r4, #0x3
	bne _02055AEC
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02055374
	pop {r3-r7, pc}
_02055AEC:
	add r0, r5, #0x0
	mov r1, #0x3
	bl FUN_02055374
	pop {r3-r7, pc}
_02055AF6:
	cmp r4, #0x0
	beq _02055B10
	cmp r4, #0x3
	bne _02055B08
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02055374
	pop {r3-r7, pc}
_02055B08:
	add r0, r5, #0x0
	mov r1, #0x3
	bl FUN_02055374
_02055B10:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02055B14
FUN_02055B14: ; 0x02055B14
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	bl FUN_0205536C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02055374
	add r0, r4, #0x0
	bl FUN_02055410
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02055B30
FUN_02055B30: ; 0x02055B30
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02055370
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02055378
	cmp r4, #0x0
	bne _02055B48
	mov r0, #0x1
	pop {r3-r5, pc}
_02055B48:
	cmp r4, #0x2
	bne _02055B50
	mov r0, #0x1
	pop {r3-r5, pc}
_02055B50:
	cmp r4, #0x1
	bne _02055B86
	cmp r0, #0x0
	beq _02055B5C
	cmp r0, #0x3
	bne _02055B60
_02055B5C:
	mov r0, #0x1
	pop {r3-r5, pc}
_02055B60:
	add r0, r5, #0x0
	bl FUN_020553A0
	add r4, r0, #0x0
	bl FUN_0205AD98
	cmp r0, #0x1
	bne _02055B74
	mov r0, #0x1
	pop {r3-r5, pc}
_02055B74:
	add r0, r4, #0x0
	bl FUN_020586F0
	bl FUN_020570F0
	cmp r0, #0x1
	bne _02055B86
	mov r0, #0x1
	pop {r3-r5, pc}
_02055B86:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02055B8C
FUN_02055B8C: ; 0x02055B8C
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	mov r1, #0x0
	bl FUN_0205536C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02055374
	add r0, r4, #0x0
	bl FUN_020553A0
	add r4, r0, #0x0
	add r1, r5, #0x0
	bl FUN_020584AC
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02058544
	add r0, r4, #0x0
	bl FUN_02059C60
	add r0, r4, #0x0
	bl FUN_0205AE80
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0205AFDC
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205ADDC
	pop {r3-r5, pc}

	thumb_func_start FUN_02055BD4
FUN_02055BD4: ; 0x02055BD4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02055BEC
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02055C4C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02055BEC
FUN_02055BEC: ; 0x02055BEC
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r4, #0x0
	bl FUN_020553A0
	bl FUN_02058720
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_0205733C
	cmp r0, #0x1
	bne _02055C10
	mov r0, #0x5
	pop {r3-r7, pc}
_02055C10:
	add r0, r5, #0x0
	bl FUN_020556E0
	cmp r0, #0x1
	bne _02055C1E
	add r0, r4, #0x0
	pop {r3-r7, pc}
_02055C1E:
	lsl r0, r7, #0x18
	ldr r5, _02055C44 ; =UNK_020F5D34
	lsr r6, r0, #0x18
_02055C24:
	ldr r1, [r5, #0x0]
	add r0, r6, #0x0
	blx r1
	cmp r0, #0x1
	bne _02055C36
	ldr r0, _02055C48 ; =UNK_020F5D34 + 4
	lsl r1, r4, #0x3
	ldr r0, [r0, r1]
	pop {r3-r7, pc}
_02055C36:
	add r5, #0x8
	ldr r0, [r5, #0x0]
	add r4, r4, #0x1
	cmp r0, #0x0
	bne _02055C24
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02055C44: .word UNK_020F5D34
_02055C48: .word UNK_020F5D34 + 4

	thumb_func_start FUN_02055C4C
FUN_02055C4C: ; 0x02055C4C
	push {r3, lr}
	add r3, r1, #0x0
	add r1, r2, #0x0
	ldr r2, _02055C68 ; =UNK_020F5D1C
	lsl r3, r3, #0x2
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #0x1
	bne _02055C62
	mov r0, #0x1
	pop {r3, pc}
_02055C62:
	mov r0, #0x0
	pop {r3, pc}
	nop
_02055C68: .word UNK_020F5D1C

	thumb_func_start FUN_02055C6C
FUN_02055C6C: ; 0x02055C6C
	push {r3, lr}
	bl FUN_02055FFC
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02055C78
FUN_02055C78: ; 0x02055C78
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_020553A0
	add r4, r0, #0x0
	bl FUN_020584D4
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02056040
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02056B74
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205569C
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _02055D28
	add r0, r5, #0x0
	bl FUN_02055FFC
	cmp r7, #0x1
	beq _02055CCA
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_020556C8
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0205536C
	mov r0, #0x0
	pop {r3-r7, pc}
_02055CCA:
	add r0, r6, #0x0
	bl FUN_02059E74
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02056B74
	cmp r0, #0x0
	beq _02055CE4
	mov r0, #0x0
	pop {r3-r7, pc}
_02055CE4:
	mov r1, #0x6
	add r0, r4, #0x0
	lsl r1, r1, #0x6
	bl FUN_02058410
	add r0, r6, #0x0
	mov r1, #0x8
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02056B5C
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_020556C8
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205569C
	mov r1, #0x0
	mvn r1, r1
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_0205543C
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205536C
	mov r0, #0x1
	pop {r3-r7, pc}
_02055D28:
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_020560A0
	cmp r0, #0x0
	bne _02055D8E
	add r0, r5, #0x0
	bl FUN_02055FFC
	add r0, r6, #0x0
	bl FUN_02059E74
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02056B74
	cmp r0, #0x0
	beq _02055D54
	mov r0, #0x0
	pop {r3-r7, pc}
_02055D54:
	mov r1, #0x6
	add r0, r4, #0x0
	lsl r1, r1, #0x6
	bl FUN_02058410
	add r0, r6, #0x0
	mov r1, #0x8
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02056B5C
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_020556C8
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205569C
	mov r1, #0x0
	mvn r1, r1
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_0205543C
	b _02055DA0
_02055D8E:
	mov r1, #0x6
	add r0, r4, #0x0
	lsl r1, r1, #0x6
	bl FUN_02058410
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020560D0
_02055DA0:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205536C
	mov r0, #0x1
	pop {r3-r7, pc}

	thumb_func_start FUN_02055DAC
FUN_02055DAC: ; 0x02055DAC
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	bl FUN_020553A0
	add r6, r0, #0x0
	bl FUN_020584D4
	add r4, r0, #0x0
	ldr r0, _02055EF4 ; =0x00000654
	bl PlaySE
	cmp r4, #0x0
	bne _02055E62
	add r0, r5, #0x0
	bl FUN_020553C4
	cmp r0, #0x1
	bne _02055DFE
	add r0, r5, #0x0
	bl FUN_02055408
	cmp r0, #0x3
	blt _02055DFE
	cmp r7, #0x0
	bne _02055DFE
	add r0, r4, #0x0
	mov r1, #0x15
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02056B5C
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205536C
	mov r0, #0x1
	pop {r3-r7, pc}
_02055DFE:
	add r0, r4, #0x0
	bl FUN_02059E74
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02056B74
	cmp r0, #0x0
	beq _02055E18
	mov r0, #0x0
	pop {r3-r7, pc}
_02055E18:
	mov r1, #0x6
	add r0, r6, #0x0
	lsl r1, r1, #0x6
	bl FUN_02058410
	add r0, r4, #0x0
	mov r1, #0x8
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02056B5C
	add r0, r5, #0x0
	bl FUN_02055410
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205569C
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205536C
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02055778
	mov r1, #0x0
	mvn r1, r1
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_0205543C
	mov r0, #0x1
	pop {r3-r7, pc}
_02055E62:
	cmp r4, #0x1
	bne _02055EF0
	add r0, r5, #0x0
	bl FUN_02055790
	cmp r0, #0x0
	bne _02055EAC
	add r0, r4, #0x0
	mov r1, #0x15
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02056B5C
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205536C
	add r0, r5, #0x0
	bl FUN_020554BC
	cmp r0, #0x1
	bne _02055E9C
	add r0, r5, #0x0
	mov r1, #0x3
	bl FUN_0205540C
_02055E9C:
	mov r1, #0x0
	mvn r1, r1
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_0205543C
	mov r0, #0x1
	pop {r3-r7, pc}
_02055EAC:
	mov r1, #0x6
	add r0, r6, #0x0
	lsl r1, r1, #0x6
	bl FUN_02058410
	add r0, r4, #0x0
	mov r1, #0x8
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02056B5C
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205569C
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205536C
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02055778
	mov r1, #0x0
	mvn r1, r1
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_0205543C
	mov r0, #0x1
	pop {r3-r7, pc}
_02055EF0:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02055EF4: .word 0x00000654

	thumb_func_start FUN_02055EF8
FUN_02055EF8: ; 0x02055EF8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020553A0
	add r4, r0, #0x0
	bl FUN_020584D4
	add r0, r5, #0x0
	bl FUN_020554BC
	cmp r0, #0x1
	bne _02055F22
	ldr r0, _02055F40 ; =0x00000656
	bl PlaySE
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x5f
	bl FUN_02056B5C
	b _02055F2C
_02055F22:
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x5d
	bl FUN_02056B5C
_02055F2C:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205569C
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_020557D0
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_02055F40: .word 0x00000656

	thumb_func_start FUN_02055F44
FUN_02055F44: ; 0x02055F44
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020553A0
	add r4, r0, #0x0
	bl FUN_020584D4
	add r0, r5, #0x0
	bl FUN_020554BC
	cmp r0, #0x1
	bne _02055F6E
	ldr r0, _02055F8C ; =0x00000656
	bl PlaySE
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x5e
	bl FUN_02056B5C
	b _02055F78
_02055F6E:
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x5c
	bl FUN_02056B5C
_02055F78:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205569C
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_020557D0
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_02055F8C: .word 0x00000656

	thumb_func_start FUN_02055F90
FUN_02055F90: ; 0x02055F90
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020553A0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x1
	bl FUN_02056B74
	cmp r0, #0x0
	bne _02055FCE
	mov r0, #0x1
	mov r1, #0x14
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02056B5C
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205536C
	add r0, r5, #0x0
	mov r1, #0x3
	bl FUN_0205540C
	mov r0, #0x1
	pop {r3-r5, pc}
_02055FCE:
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02056B5C
	add r0, r5, #0x0
	bl FUN_02055410
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0205536C
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_020556F4
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02055FFC
FUN_02055FFC: ; 0x02055FFC
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020556B4
	cmp r0, #0x1
	bne _0205603E
	add r0, r4, #0x0
	bl FUN_020553A0
	mov r1, #0x6
	lsl r1, r1, #0x6
	bl FUN_02058418
	add r0, r4, #0x0
	bl FUN_020557E8
	cmp r0, #0x0
	bne _02056026
	add r0, r4, #0x0
	bl FUN_02055410
_02056026:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0205569C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_020557D0
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02055778
_0205603E:
	pop {r4, pc}

	thumb_func_start FUN_02056040
FUN_02056040: ; 0x02056040
	push {r4-r6, lr}
	sub sp, #0x18
	add r5, r1, #0x0
	bl FUN_020553A0
	add r4, r0, #0x0
	bl FUN_02058738
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r1, sp, #0xc
	bl FUN_02058B5C
	add r4, sp, #0xc
	add r3, sp, #0x0
	ldmia r4!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r4, #0x0]
	add r1, r2, #0x0
	mov r2, #0x1
	str r0, [r3, #0x0]
	add r0, r5, #0x0
	lsl r2, r2, #0xe
	bl FUN_02059E28
	add r0, r6, #0x0
	add r1, sp, #0x0
	bl FUN_02059E9C
	cmp r0, #0x0
	beq _02056088
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x10]
	cmp r0, r1
	bne _0205608E
_02056088:
	add sp, #0x18
	mov r0, #0x0
	pop {r4-r6, pc}
_0205608E:
	cmp r0, r1
	ble _02056098
	add sp, #0x18
	mov r0, #0x2
	pop {r4-r6, pc}
_02056098:
	mov r0, #0x1
	add sp, #0x18
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020560A0
FUN_020560A0: ; 0x020560A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02055408
	add r1, r0, #0x0
	cmp r4, #0x1
	bne _020560B8
	sub r1, r1, #0x1
	bpl _020560C4
	mov r0, #0x0
	pop {r3-r5, pc}
_020560B8:
	cmp r4, #0x2
	bne _020560C4
	add r1, r1, #0x1
	cmp r1, #0x3
	ble _020560C4
	mov r1, #0x3
_020560C4:
	add r0, r5, #0x0
	bl FUN_0205540C
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020560D0
FUN_020560D0: ; 0x020560D0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	bl FUN_020553A0
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r4, #0x10
	bl FUN_02055408
	cmp r0, #0x1
	beq _020560F2
	cmp r0, #0x2
	beq _020560F6
	cmp r0, #0x3
	beq _020560FA
	b _020560FC
_020560F2:
	mov r4, #0x50
	b _020560FC
_020560F6:
	mov r4, #0x14
	b _020560FC
_020560FA:
	mov r4, #0x14
_020560FC:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02056B5C
	pop {r3-r7, pc}

	thumb_func_start FUN_02056110
FUN_02056110: ; 0x02056110
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	add r7, r1, #0x0
	str r2, [sp, #0x8]
	add r5, r3, #0x0
	bl FUN_020553C4
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_020553A0
	add r1, r0, #0x0
	cmp r4, #0x0
	beq _02056136
	cmp r4, #0x1
	beq _0205614C
	cmp r4, #0x2
	bne _02056162
_02056136:
	str r5, [sp, #0x0]
	add r0, sp, #0x10
	ldrh r0, [r0, #0x10]
	ldr r3, [sp, #0x8]
	add r2, r7, #0x0
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	bl FUN_0205616C
	add sp, #0xc
	pop {r4-r7, pc}
_0205614C:
	str r5, [sp, #0x0]
	add r0, sp, #0x10
	ldrh r0, [r0, #0x10]
	ldr r3, [sp, #0x8]
	add r2, r7, #0x0
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	bl FUN_020563A8
	add sp, #0xc
	pop {r4-r7, pc}
_02056162:
	bl GF_AssertFail
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0205616C
FUN_0205616C: ; 0x0205616C
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r3, #0x0
	add r4, r1, #0x0
	add r1, r6, #0x0
	add r5, r0, #0x0
	bl FUN_020561D0
	cmp r0, #0x0
	beq _0205618C
	cmp r0, #0x1
	beq _020561A2
	cmp r0, #0x2
	beq _020561B8
	add sp, #0x4
	pop {r3-r6, pc}
_0205618C:
	add r3, sp, #0x8
	ldrh r0, [r3, #0x14]
	add r1, r4, #0x0
	add r2, r6, #0x0
	str r0, [sp, #0x0]
	ldrh r3, [r3, #0x10]
	add r0, r5, #0x0
	bl FUN_02056288
	add sp, #0x4
	pop {r3-r6, pc}
_020561A2:
	add r3, sp, #0x8
	ldrh r0, [r3, #0x14]
	add r1, r4, #0x0
	add r2, r6, #0x0
	str r0, [sp, #0x0]
	ldrh r3, [r3, #0x10]
	add r0, r5, #0x0
	bl FUN_020562A8
	add sp, #0x4
	pop {r3-r6, pc}
_020561B8:
	add r3, sp, #0x8
	ldrh r0, [r3, #0x14]
	add r1, r4, #0x0
	add r2, r6, #0x0
	str r0, [sp, #0x0]
	ldrh r3, [r3, #0x10]
	add r0, r5, #0x0
	bl FUN_02056384
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_020561D0
FUN_020561D0: ; 0x020561D0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02056244
	add r4, r0, #0x0
	bl FUN_020561EC
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205536C
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020561EC
FUN_020561EC: ; 0x020561EC
	push {r3, lr}
	cmp r0, #0x0
	beq _020561FC
	cmp r0, #0x1
	beq _02056200
	cmp r0, #0x2
	beq _02056204
	b _02056208
_020561FC:
	mov r0, #0x0
	pop {r3, pc}
_02056200:
	mov r0, #0x1
	pop {r3, pc}
_02056204:
	mov r0, #0x2
	pop {r3, pc}
_02056208:
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02056210
FUN_02056210: ; 0x02056210
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r0, r5, #0x0
	add r4, r2, #0x0
	bl FUN_020549F0
	cmp r0, #0x1
	bne _02056224
	mov r0, #0x4
	pop {r3-r5, pc}
_02056224:
	add r0, r5, #0x0
	bl FUN_020549E4
	cmp r0, #0x1
	bne _02056232
	mov r0, #0x8
	pop {r3-r5, pc}
_02056232:
	add r0, r5, #0x0
	bl FUN_020549D8
	cmp r0, #0x1
	bne _0205623E
	mov r4, #0xc
_0205623E:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02056244
FUN_02056244: ; 0x02056244
	push {r3-r5, lr}
	add r4, r1, #0x0
	mov r1, #0x0
	mvn r1, r1
	add r5, r0, #0x0
	cmp r4, r1
	bne _0205625C
	mov r1, #0x0
	bl FUN_0205536C
	mov r0, #0x0
	pop {r3-r5, pc}
_0205625C:
	bl PlayerAvatar_GetFacingDirection
	cmp r0, r4
	beq _0205627A
	add r0, r5, #0x0
	bl FUN_02055370
	cmp r0, #0x1
	beq _0205627A
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0205536C
	mov r0, #0x2
	pop {r3-r5, pc}
_0205627A:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205536C
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02056288
FUN_02056288: ; 0x02056288
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020584C4
	mov r1, #0x0
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02056B5C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020562A8
FUN_020562A8: ; 0x020562A8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	str r2, [sp, #0x0]
	bl FUN_02056B74
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020553C4
	cmp r0, #0x2
	beq _0205632A
	mov r0, #0x4
	tst r0, r4
	beq _020562CA
	mov r7, #0x38
	b _0205636C
_020562CA:
	cmp r4, #0x0
	beq _020562E6
	mov r0, #0x8
	mov r7, #0x1c
	tst r0, r4
	bne _020562DC
	ldr r0, _02056380 ; =0x00000601
	bl PlaySE
_020562DC:
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	bl FUN_020584CC
	b _0205636C
_020562E6:
	add r0, r5, #0x0
	mov r4, #0xc
	bl FUN_0205545C
	bl FUN_02055474
	cmp r0, #0x1
	bne _02056306
	add r1, sp, #0x8
	ldrh r1, [r1, #0x10]
	add r0, r5, #0x0
	bl FUN_02057114
	cmp r0, #0x1
	bne _02056306
	mov r4, #0x58
_02056306:
	add r0, r6, #0x0
	bl FUN_02058720
	add r1, r0, #0x0
	lsl r1, r1, #0x18
	add r0, r6, #0x0
	lsr r1, r1, #0x18
	add r2, r4, #0x0
	bl FUN_02056210
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020572D4
	add r0, r5, #0x0
	bl FUN_020557A4
	b _0205636C
_0205632A:
	cmp r4, #0x0
	beq _02056332
	cmp r4, #0x20
	bne _02056356
_02056332:
	add r0, r6, #0x0
	bl FUN_02058720
	add r1, r0, #0x0
	lsl r1, r1, #0x18
	add r0, r6, #0x0
	lsr r1, r1, #0x18
	mov r2, #0xc
	bl FUN_02056210
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020572D4
	add r0, r5, #0x0
	bl FUN_020557A4
	b _0205636C
_02056356:
	mov r0, #0x8
	mov r7, #0x1c
	tst r0, r4
	bne _02056364
	ldr r0, _02056380 ; =0x00000601
	bl PlaySE
_02056364:
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	bl FUN_020584CC
_0205636C:
	ldr r0, [sp, #0x0]
	add r1, r7, #0x0
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02056B5C
	pop {r3-r7, pc}
	.balign 4
_02056380: .word 0x00000601

	thumb_func_start FUN_02056384
FUN_02056384: ; 0x02056384
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r0, r6, #0x0
	mov r1, #0x28
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02056B5C
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_020584CC
	pop {r4-r6, pc}

	thumb_func_start FUN_020563A8
FUN_020563A8: ; 0x020563A8
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_020554BC
	cmp r0, #0x1
	add r0, sp, #0x10
	bne _020563D6
	ldrh r1, [r0, #0x10]
	add r2, r6, #0x0
	add r3, r7, #0x0
	str r1, [sp, #0x0]
	ldrh r0, [r0, #0x14]
	add r1, r4, #0x0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_020567E4
	add sp, #0x8
	pop {r3-r7, pc}
_020563D6:
	ldrh r1, [r0, #0x10]
	add r2, r6, #0x0
	add r3, r7, #0x0
	str r1, [sp, #0x0]
	ldrh r0, [r0, #0x14]
	add r1, r4, #0x0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_020564C8
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020563F0
FUN_020563F0: ; 0x020563F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020553C4
	cmp r0, #0x1
	bne _0205642C
	mov r0, #0x2
	tst r0, r4
	beq _0205642C
	add r0, r5, #0x0
	mov r4, #0x1
	bl FUN_020554BC
	cmp r0, #0x1
	bne _02056412
	mov r4, #0x0
_02056412:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020554AC
	cmp r4, #0x0
	bne _02056426
	ldr r0, _02056430 ; =0x0000061C
	bl PlaySE
	pop {r3-r5, pc}
_02056426:
	ldr r0, _02056434 ; =0x00000619
	bl PlaySE
_0205642C:
	pop {r3-r5, pc}
	nop
_02056430: .word 0x0000061C
_02056434: .word 0x00000619

	thumb_func_start FUN_02056438
FUN_02056438: ; 0x02056438
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r4, #0x4c
	bl FUN_02055408
	cmp r0, #0x1
	beq _02056450
	cmp r0, #0x2
	beq _02056454
	cmp r0, #0x3
	beq _02056458
	b _0205645A
_02056450:
	mov r4, #0x10
	b _0205645A
_02056454:
	mov r4, #0x50
	b _0205645A
_02056458:
	mov r4, #0x14
_0205645A:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0205AFDC
	pop {r3-r5, pc}

	thumb_func_start FUN_02056464
FUN_02056464: ; 0x02056464
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r1, #0x1
	mov r2, #0x3
	bl FUN_0205541C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205570C
	cmp r0, #0x0
	bne _02056488
	cmp r4, #0x2
	blt _02056488
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_020556F4
_02056488:
	cmp r4, #0x3
	bne _02056490
	mov r0, #0x1
	pop {r3-r5, pc}
_02056490:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02056494
FUN_02056494: ; 0x02056494
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r6, #0x1
	bl FUN_02055408
	sub r4, r0, #0x1
	bpl _020564A6
	mov r4, #0x0
	add r6, r4, #0x0
_020564A6:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0205540C
	add r0, r5, #0x0
	bl FUN_0205570C
	cmp r0, #0x1
	bne _020564C4
	cmp r4, #0x0
	bne _020564C4
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_020556F4
_020564C4:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020564C8
FUN_020564C8: ; 0x020564C8
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r1, #0x0
	add r1, r3, #0x0
	add r6, r0, #0x0
	str r3, [sp, #0x4]
	ldr r5, [sp, #0x20]
	ldr r4, [sp, #0x24]
	bl FUN_0205653C
	cmp r0, #0x3
	bhi _02056538
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020564EC: ; jump table (using 16-bit offset)
	.short _020564F4 - _020564EC - 2; case 0
	.short _02056506 - _020564EC - 2; case 1
	.short _02056518 - _020564EC - 2; case 2
	.short _0205652A - _020564EC - 2; case 3
_020564F4:
	ldr r2, [sp, #0x4]
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r3, r5, #0x0
	str r4, [sp, #0x0]
	bl FUN_020565F0
	add sp, #0x8
	pop {r3-r7, pc}
_02056506:
	ldr r2, [sp, #0x4]
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r3, r5, #0x0
	str r4, [sp, #0x0]
	bl FUN_02056614
	add sp, #0x8
	pop {r3-r7, pc}
_02056518:
	ldr r2, [sp, #0x4]
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r3, r5, #0x0
	str r4, [sp, #0x0]
	bl FUN_02056704
	add sp, #0x8
	pop {r3-r7, pc}
_0205652A:
	ldr r2, [sp, #0x4]
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r3, r5, #0x0
	str r4, [sp, #0x0]
	bl FUN_02056740
_02056538:
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0205653C
FUN_0205653C: ; 0x0205653C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0205658C
	add r4, r0, #0x0
	bl FUN_02056558
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205536C
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02056558
FUN_02056558: ; 0x02056558
	push {r3, lr}
	cmp r0, #0x3
	bhi _02056582
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205656A: ; jump table (using 16-bit offset)
	.short _02056572 - _0205656A - 2; case 0
	.short _02056576 - _0205656A - 2; case 1
	.short _0205657A - _0205656A - 2; case 2
	.short _0205657E - _0205656A - 2; case 3
_02056572:
	mov r0, #0x0
	pop {r3, pc}
_02056576:
	mov r0, #0x1
	pop {r3, pc}
_0205657A:
	mov r0, #0x2
	pop {r3, pc}
_0205657E:
	mov r0, #0x1
	pop {r3, pc}
_02056582:
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205658C
FUN_0205658C: ; 0x0205658C
	push {r4-r6, lr}
	add r4, r1, #0x0
	mov r1, #0x0
	mvn r1, r1
	add r5, r0, #0x0
	cmp r4, r1
	bne _020565BA
	bl FUN_0205570C
	cmp r0, #0x1
	bne _020565AE
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205536C
	mov r0, #0x3
	pop {r4-r6, pc}
_020565AE:
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0205536C
	mov r0, #0x0
	pop {r4-r6, pc}
_020565BA:
	bl PlayerAvatar_GetFacingDirection
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_020556F4
	cmp r6, r4
	beq _020565E2
	add r0, r5, #0x0
	bl FUN_02055370
	cmp r0, #0x1
	beq _020565E2
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0205536C
	mov r0, #0x2
	pop {r4-r6, pc}
_020565E2:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205536C
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020565F0
FUN_020565F0: ; 0x020565F0
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020584C4
	mov r1, #0x0
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02056B5C
	add r0, r5, #0x0
	bl FUN_02055410
	pop {r3-r5, pc}

	thumb_func_start FUN_02056614
FUN_02056614: ; 0x02056614
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	str r2, [sp, #0x0]
	bl FUN_02056B74
	add r4, r0, #0x0
	mov r0, #0x4
	tst r0, r4
	beq _02056638
	add r0, r5, #0x0
	mov r7, #0x38
	bl FUN_020572D4
	add r0, r5, #0x0
	bl FUN_020557A4
	b _020566EA
_02056638:
	mov r0, #0x10
	tst r0, r4
	beq _02056656
	add r0, r5, #0x0
	mov r7, #0x50
	bl FUN_020572D4
	add r0, r5, #0x0
	bl FUN_020557A4
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205569C
	b _020566EA
_02056656:
	mov r0, #0x40
	tst r0, r4
	beq _02056680
	add r0, r6, #0x0
	mov r7, #0x0
	bl FUN_020584D4
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_02055410
	sub r1, r7, #0x1
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_0205543C
	b _020566EA
_02056680:
	cmp r4, #0x0
	beq _020566D4
	ldr r2, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020572EC
	cmp r0, #0x0
	bne _020566B0
	mov r0, #0x8
	mov r7, #0x1c
	tst r0, r4
	bne _020566A0
	ldr r0, _02056700 ; =0x00000601
	bl PlaySE
_020566A0:
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_02055410
	b _020566EA
_020566B0:
	add r0, r6, #0x0
	mov r7, #0x0
	bl FUN_020584D4
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_02055410
	sub r1, r7, #0x1
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_0205543C
	b _020566EA
_020566D4:
	add r0, r5, #0x0
	mov r7, #0x50
	bl FUN_020572D4
	add r0, r5, #0x0
	bl FUN_020557A4
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0205540C
_020566EA:
	ldr r0, [sp, #0x0]
	add r1, r7, #0x0
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02056B5C
	pop {r3-r7, pc}
	nop
_02056700: .word 0x00000601

	thumb_func_start FUN_02056704
FUN_02056704: ; 0x02056704
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02055410
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020572EC
	cmp r0, #0x1
	beq _0205673E
	add r0, r6, #0x0
	mov r1, #0x28
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02056B5C
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_02055410
_0205673E:
	pop {r4-r6, pc}

	thumb_func_start FUN_02056740
FUN_02056740: ; 0x02056740
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r7, r1, #0x0
	bl FUN_02056494
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02055314
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_02056B74
	add r4, r0, #0x0
	mov r0, #0x4
	tst r0, r4
	beq _02056774
	add r0, r6, #0x0
	mov r1, #0x38
	bl FUN_0205AFDC
	str r0, [sp, #0x4]
	b _020567C4
_02056774:
	mov r0, #0x40
	tst r0, r4
	beq _0205678C
	add r0, r6, #0x0
	mov r1, #0x0
	bl FUN_0205AFDC
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02055410
	b _020567C4
_0205678C:
	cmp r4, #0x0
	beq _020567BA
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r0, r6, #0x0
	mov r1, #0x1c
	bl FUN_0205AFDC
	str r0, [sp, #0x4]
	mov r0, #0x8
	tst r0, r4
	bne _020567AA
	ldr r0, _020567E0 ; =0x00000601
	bl PlaySE
_020567AA:
	add r0, r7, #0x0
	add r1, r6, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_02055410
	b _020567C4
_020567BA:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02056438
	str r0, [sp, #0x4]
_020567C4:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bne _020567D2
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_020556F4
_020567D2:
	ldr r2, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02056B5C
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020567E0: .word 0x00000601

	thumb_func_start FUN_020567E4
FUN_020567E4: ; 0x020567E4
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r1, #0x0
	add r1, r3, #0x0
	add r6, r0, #0x0
	str r3, [sp, #0x4]
	ldr r5, [sp, #0x20]
	ldr r4, [sp, #0x24]
	bl FUN_02056858
	cmp r0, #0x3
	bhi _02056854
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02056808: ; jump table (using 16-bit offset)
	.short _02056810 - _02056808 - 2; case 0
	.short _02056822 - _02056808 - 2; case 1
	.short _02056834 - _02056808 - 2; case 2
	.short _02056846 - _02056808 - 2; case 3
_02056810:
	ldr r2, [sp, #0x4]
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r3, r5, #0x0
	str r4, [sp, #0x0]
	bl FUN_02056914
	add sp, #0x8
	pop {r3-r7, pc}
_02056822:
	ldr r2, [sp, #0x4]
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r3, r5, #0x0
	str r4, [sp, #0x0]
	bl FUN_02056938
	add sp, #0x8
	pop {r3-r7, pc}
_02056834:
	ldr r2, [sp, #0x4]
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r3, r5, #0x0
	str r4, [sp, #0x0]
	bl FUN_02056A7C
	add sp, #0x8
	pop {r3-r7, pc}
_02056846:
	ldr r2, [sp, #0x4]
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r3, r5, #0x0
	str r4, [sp, #0x0]
	bl FUN_02056AB8
_02056854:
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02056858
FUN_02056858: ; 0x02056858
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020568A8
	add r4, r0, #0x0
	bl FUN_02056874
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205536C
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02056874
FUN_02056874: ; 0x02056874
	push {r3, lr}
	cmp r0, #0x3
	bhi _0205689E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02056886: ; jump table (using 16-bit offset)
	.short _0205688E - _02056886 - 2; case 0
	.short _02056892 - _02056886 - 2; case 1
	.short _02056896 - _02056886 - 2; case 2
	.short _0205689A - _02056886 - 2; case 3
_0205688E:
	mov r0, #0x0
	pop {r3, pc}
_02056892:
	mov r0, #0x1
	pop {r3, pc}
_02056896:
	mov r0, #0x2
	pop {r3, pc}
_0205689A:
	mov r0, #0x1
	pop {r3, pc}
_0205689E:
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020568A8
FUN_020568A8: ; 0x020568A8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02055408
	add r6, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	bne _020568D8
	cmp r6, #0x2
	bge _020568CC
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0205536C
	mov r0, #0x0
	pop {r4-r6, pc}
_020568CC:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205536C
	mov r0, #0x3
	pop {r4-r6, pc}
_020568D8:
	add r0, r5, #0x0
	bl PlayerAvatar_GetFacingDirection
	cmp r0, r4
	beq _02056908
	add r0, r5, #0x0
	bl FUN_02055370
	cmp r0, #0x1
	beq _02056908
	cmp r6, #0x2
	bge _020568FC
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0205536C
	mov r0, #0x2
	pop {r4-r6, pc}
_020568FC:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205536C
	mov r0, #0x3
	pop {r4-r6, pc}
_02056908:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205536C
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_02056914
FUN_02056914: ; 0x02056914
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020584C4
	mov r1, #0x0
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02056B5C
	add r0, r5, #0x0
	bl FUN_02055410
	pop {r3-r5, pc}

	thumb_func_start FUN_02056938
FUN_02056938: ; 0x02056938
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl FUN_02056B74
	add r4, r0, #0x0
	mov r0, #0x4
	tst r0, r4
	beq _0205696A
	add r0, r7, #0x0
	mov r1, #0x38
	bl FUN_0205AFDC
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02056464
	add r0, r5, #0x0
	bl FUN_020572D4
	add r0, r5, #0x0
	bl FUN_020557A4
	b _02056A6C
_0205696A:
	mov r0, #0x10
	tst r0, r4
	beq _020569BA
	add r0, r5, #0x0
	bl FUN_02055408
	cmp r0, #0x3
	blt _02056994
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02056438
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_020557A4
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205569C
	b _02056A6C
_02056994:
	add r0, r7, #0x0
	mov r1, #0x1c
	bl FUN_0205AFDC
	str r0, [sp, #0x0]
	mov r0, #0x8
	tst r0, r4
	bne _020569AA
	ldr r0, _02056A78 ; =0x00000601
	bl PlaySE
_020569AA:
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_02055410
	b _02056A6C
_020569BA:
	mov r0, #0x40
	tst r0, r4
	beq _020569EC
	add r0, r6, #0x0
	bl FUN_020584D4
	add r4, r0, #0x0
	mov r1, #0x0
	bl FUN_0205AFDC
	str r0, [sp, #0x0]
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_02055410
	mov r1, #0x0
	mvn r1, r1
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_0205543C
	b _02056A6C
_020569EC:
	cmp r4, #0x0
	beq _02056A50
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020572EC
	cmp r0, #0x0
	bne _02056A24
	add r0, r7, #0x0
	mov r1, #0x1c
	bl FUN_0205AFDC
	str r0, [sp, #0x0]
	mov r0, #0x8
	tst r0, r4
	bne _02056A14
	ldr r0, _02056A78 ; =0x00000601
	bl PlaySE
_02056A14:
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_02055410
	b _02056A6C
_02056A24:
	add r0, r6, #0x0
	bl FUN_020584D4
	add r4, r0, #0x0
	mov r1, #0x0
	bl FUN_0205AFDC
	str r0, [sp, #0x0]
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_02055410
	mov r1, #0x0
	mvn r1, r1
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_0205543C
	b _02056A6C
_02056A50:
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02056438
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02056464
	add r0, r5, #0x0
	bl FUN_020572D4
	add r0, r5, #0x0
	bl FUN_020557A4
_02056A6C:
	ldr r2, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02056B5C
	pop {r3-r7, pc}
	.balign 4
_02056A78: .word 0x00000601

	thumb_func_start FUN_02056A7C
FUN_02056A7C: ; 0x02056A7C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02055410
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020572EC
	cmp r0, #0x1
	beq _02056AB6
	add r0, r6, #0x0
	mov r1, #0x28
	bl FUN_0205AFDC
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02056B5C
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_02055410
_02056AB6:
	pop {r4-r6, pc}

	thumb_func_start FUN_02056AB8
FUN_02056AB8: ; 0x02056AB8
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r7, r1, #0x0
	bl FUN_02056494
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02055314
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_02056B74
	add r4, r0, #0x0
	mov r0, #0x4
	tst r0, r4
	beq _02056AEC
	add r0, r6, #0x0
	mov r1, #0x38
	bl FUN_0205AFDC
	str r0, [sp, #0x4]
	b _02056B3C
_02056AEC:
	mov r0, #0x40
	tst r0, r4
	beq _02056B04
	add r0, r6, #0x0
	mov r1, #0x0
	bl FUN_0205AFDC
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02055410
	b _02056B3C
_02056B04:
	cmp r4, #0x0
	beq _02056B32
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r0, r6, #0x0
	mov r1, #0x1c
	bl FUN_0205AFDC
	str r0, [sp, #0x4]
	mov r0, #0x8
	tst r0, r4
	bne _02056B22
	ldr r0, _02056B58 ; =0x00000601
	bl PlaySE
_02056B22:
	add r0, r7, #0x0
	add r1, r6, #0x0
	bl FUN_020584CC
	add r0, r5, #0x0
	bl FUN_02055410
	b _02056B3C
_02056B32:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02056438
	str r0, [sp, #0x4]
_02056B3C:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bne _02056B4A
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_020556F4
_02056B4A:
	ldr r2, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02056B5C
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02056B58: .word 0x00000601

	thumb_func_start FUN_02056B5C
FUN_02056B5C: ; 0x02056B5C
	push {r3-r5, lr}
	add r4, r2, #0x0
	add r5, r1, #0x0
	add r1, r4, #0x0
	bl FUN_02055460
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0205ADDC
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02056B74
FUN_02056B74: ; 0x02056B74
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	mov r4, #0x0
	bl FUN_02056C0C
	mov r1, #0xa
	str r0, [sp, #0x0]
	tst r0, r1
	beq _02056BA0
	mov r0, #0x1
	orr r4, r0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02056D58
	cmp r0, #0x0
	beq _02056BA0
	mov r0, #0x8
	orr r4, r0
_02056BA0:
	ldr r0, [sp, #0x0]
	mov r1, #0x4
	tst r0, r1
	beq _02056BAC
	mov r0, #0x2
	orr r4, r0
_02056BAC:
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02056CCC
	cmp r0, #0x0
	beq _02056BBE
	mov r0, #0x4
	orr r4, r0
_02056BBE:
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02056E04
	cmp r0, #0x1
	bne _02056BD0
	mov r0, #0x10
	orr r4, r0
_02056BD0:
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02056E6C
	cmp r0, #0x1
	bne _02056BE2
	mov r0, #0x20
	orr r4, r0
_02056BE2:
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02056EC8
	cmp r0, #0x1
	bne _02056BF4
	mov r0, #0x41
	orr r4, r0
_02056BF4:
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02056F78
	cmp r0, #0x1
	bne _02056C06
	mov r0, #0x1
	orr r4, r0
_02056C06:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02056C0C
FUN_02056C0C: ; 0x02056C0C
	push {r3-r7, lr}
	sub sp, #0x28
	add r5, r1, #0x0
	str r2, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02058B2C
	add r7, r0, #0x0
	ldr r0, [sp, #0x4]
	bl FUN_02059BF4
	str r0, [sp, #0x14]
	add r0, r5, #0x0
	bl FUN_02058B3C
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl FUN_02058B4C
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x4]
	bl FUN_02059C00
	str r0, [sp, #0x10]
	add r0, r5, #0x0
	add r1, sp, #0x1c
	bl FUN_02058B5C
	ldr r1, [sp, #0x14]
	ldr r6, [sp, #0xc]
	ldr r3, [sp, #0x10]
	ldr r2, [sp, #0x8]
	add r0, r5, #0x0
	add r1, r7, r1
	add r3, r6, r3
	mov r4, #0x0
	bl FUN_02059A08
	cmp r0, #0x1
	bne _02056C60
	mov r0, #0x1
	orr r4, r0
_02056C60:
	add r0, r5, #0x0
	bl FUN_02058738
	ldr r2, [sp, #0x14]
	add r1, sp, #0x18
	str r1, [sp, #0x0]
	ldr r6, [sp, #0xc]
	ldr r3, [sp, #0x10]
	add r1, sp, #0x1c
	add r2, r7, r2
	add r3, r6, r3
	bl FUN_0204A7C8
	cmp r0, #0x1
	bne _02056C90
	mov r0, #0x2
	orr r4, r0
	add r1, sp, #0x18
	mov r0, #0x0
	ldrsb r0, [r1, r0]
	cmp r0, #0x0
	beq _02056C90
	mov r0, #0x8
	orr r4, r0
_02056C90:
	ldr r3, [sp, #0xc]
	ldr r2, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r2, r3, r2
	ldr r3, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r7, r1
	bl FUN_02059A60
	cmp r0, #0x1
	bne _02056CAA
	mov r0, #0x2
	orr r4, r0
_02056CAA:
	add r0, r5, #0x0
	ldr r1, [sp, #0x14]
	ldr r5, [sp, #0xc]
	ldr r3, [sp, #0x10]
	ldr r2, [sp, #0x8]
	add r1, r7, r1
	add r3, r5, r3
	bl FUN_0205995C
	cmp r0, #0x1
	bne _02056CC4
	mov r0, #0x4
	orr r4, r0
_02056CC4:
	add r0, r4, #0x0
	add sp, #0x28
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02056CCC
FUN_02056CCC: ; 0x02056CCC
	push {r3-r7, lr}
	mov r0, #0x0
	add r4, r2, #0x0
	mvn r0, r0
	add r5, r1, #0x0
	cmp r4, r0
	beq _02056D54
	add r0, r5, #0x0
	bl FUN_02058738
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02058B2C
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02059BF4
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B4C
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02059C00
	add r2, r0, #0x0
	ldr r0, [sp, #0x0]
	add r1, r6, r7
	add r2, r5, r2
	bl FUN_0204A6E0
	cmp r4, #0x3
	bhi _02056D54
	add r1, r4, r4
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02056D1C: ; jump table (using 16-bit offset)
	.short _02056D24 - _02056D1C - 2; case 0
	.short _02056D30 - _02056D1C - 2; case 1
	.short _02056D3C - _02056D1C - 2; case 2
	.short _02056D48 - _02056D1C - 2; case 3
_02056D24:
	bl FUN_02054848
	cmp r0, #0x1
	bne _02056D54
	mov r0, #0x1
	pop {r3-r7, pc}
_02056D30:
	bl FUN_02054854
	cmp r0, #0x1
	bne _02056D54
	mov r0, #0x1
	pop {r3-r7, pc}
_02056D3C:
	bl FUN_02054860
	cmp r0, #0x1
	bne _02056D54
	mov r0, #0x1
	pop {r3-r7, pc}
_02056D48:
	bl FUN_0205486C
	cmp r0, #0x1
	bne _02056D54
	mov r0, #0x1
	pop {r3-r7, pc}
_02056D54:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02056D58
FUN_02056D58: ; 0x02056D58
	push {r3-r7, lr}
	mov r0, #0x0
	add r4, r2, #0x0
	mvn r0, r0
	add r5, r1, #0x0
	cmp r4, r0
	beq _02056E00
	add r0, r5, #0x0
	bl FUN_02058738
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B2C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B4C
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x0]
	add r0, r7, #0x0
	add r1, r6, #0x0
	bl FUN_0204A6E0
	add r5, r0, #0x0
	cmp r4, #0x3
	bhi _02056DD8
	add r1, r4, r4
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02056D9A: ; jump table (using 16-bit offset)
	.short _02056DA2 - _02056D9A - 2; case 0
	.short _02056DAE - _02056D9A - 2; case 1
	.short _02056DBC - _02056D9A - 2; case 2
	.short _02056DCA - _02056D9A - 2; case 3
_02056DA2:
	bl FUN_020547D4
	cmp r0, #0x1
	bne _02056DAE
	mov r0, #0x1
	pop {r3-r7, pc}
_02056DAE:
	add r0, r5, #0x0
	bl FUN_020547E0
	cmp r0, #0x1
	bne _02056DBC
	mov r0, #0x1
	pop {r3-r7, pc}
_02056DBC:
	add r0, r5, #0x0
	bl FUN_020547C8
	cmp r0, #0x1
	bne _02056DCA
	mov r0, #0x1
	pop {r3-r7, pc}
_02056DCA:
	add r0, r5, #0x0
	bl FUN_020547BC
	cmp r0, #0x1
	bne _02056DD8
	mov r0, #0x1
	pop {r3-r7, pc}
_02056DD8:
	add r0, r4, #0x0
	bl FUN_02059BF4
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02059C00
	add r3, r0, #0x0
	ldr r2, [sp, #0x0]
	add r0, r7, #0x0
	add r1, r6, r5
	add r2, r2, r3
	bl FUN_0204A6E0
	bl FUN_020547B0
	cmp r0, #0x1
	bne _02056E00
	mov r0, #0x1
	pop {r3-r7, pc}
_02056E00:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02056E04
FUN_02056E04: ; 0x02056E04
	push {r3-r7, lr}
	mov r0, #0x0
	add r5, r2, #0x0
	mvn r0, r0
	add r4, r1, #0x0
	cmp r5, r0
	beq _02056E68
	add r0, r4, #0x0
	bl FUN_02058738
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_02058B2C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02059BF4
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058B4C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02059C00
	add r2, r0, #0x0
	ldr r0, [sp, #0x0]
	add r1, r6, r7
	add r2, r4, r2
	bl FUN_0204A6E0
	add r4, r0, #0x0
	cmp r5, #0x3
	bne _02056E56
	bl FUN_02054A24
	cmp r0, #0x0
	beq _02056E56
	mov r0, #0x1
	pop {r3-r7, pc}
_02056E56:
	cmp r5, #0x2
	bne _02056E68
	add r0, r4, #0x0
	bl FUN_02054A30
	cmp r0, #0x0
	beq _02056E68
	mov r0, #0x1
	pop {r3-r7, pc}
_02056E68:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02056E6C
FUN_02056E6C: ; 0x02056E6C
	push {r3-r7, lr}
	sub sp, #0x8
	mov r0, #0x0
	add r4, r2, #0x0
	mvn r0, r0
	add r5, r1, #0x0
	cmp r4, r0
	beq _02056EC2
	add r0, r5, #0x0
	bl FUN_02058738
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02058B2C
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02059BF4
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B4C
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl FUN_02059C00
	add r3, r0, #0x0
	ldr r2, [sp, #0x4]
	ldr r0, [sp, #0x0]
	add r1, r6, r7
	add r2, r2, r3
	bl FUN_0204A6E0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02059AC4
	cmp r0, #0x0
	beq _02056EC2
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_02056EC2:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02056EC8
FUN_02056EC8: ; 0x02056EC8
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	mov r0, #0x0
	add r4, r2, #0x0
	mvn r0, r0
	add r5, r1, #0x0
	cmp r4, r0
	beq _02056F72
	add r0, r5, #0x0
	bl FUN_02058738
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02058B2C
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02059BF4
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B4C
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl FUN_02059C00
	add r2, r0, #0x0
	ldr r3, [sp, #0x8]
	ldr r0, [sp, #0x4]
	add r1, r6, r7
	add r2, r3, r2
	bl FUN_0204A6E0
	add r6, r0, #0x0
	ldr r0, [sp, #0x0]
	bl FUN_020553C4
	cmp r0, #0x1
	bne _02056F54
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02059BB4
	cmp r0, #0x1
	bne _02056F36
	cmp r4, #0x1
	bls _02056F30
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_02056F30:
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02056F36:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02059BD4
	cmp r0, #0x1
	bne _02056F72
	sub r0, r4, #0x2
	cmp r0, #0x1
	bls _02056F4E
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_02056F4E:
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02056F54:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02059BB4
	cmp r0, #0x1
	beq _02056F6C
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02059BD4
	cmp r0, #0x1
	bne _02056F72
_02056F6C:
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_02056F72:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_02056F78
FUN_02056F78: ; 0x02056F78
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r1, #0x0
	mov r1, #0x0
	add r4, r2, #0x0
	mvn r1, r1
	cmp r4, r1
	beq _0205701A
	bl FUN_020553C4
	cmp r0, #0x1
	bne _0205701A
	add r0, r5, #0x0
	bl FUN_02058738
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02058B2C
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02059BF4
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B4C
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl FUN_02059C00
	add r3, r0, #0x0
	ldr r2, [sp, #0x4]
	ldr r0, [sp, #0x0]
	add r1, r6, r7
	add r2, r2, r3
	bl FUN_0204A6E0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02059AC4
	cmp r0, #0x0
	beq _02056FD8
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_02056FD8:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02059B2C
	cmp r0, #0x0
	beq _02056FEA
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_02056FEA:
	add r0, r4, #0x0
	bl FUN_02054798
	cmp r0, #0x0
	beq _02056FFA
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_02056FFA:
	add r0, r4, #0x0
	bl FUN_02054974
	cmp r0, #0x0
	beq _0205700A
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_0205700A:
	add r0, r4, #0x0
	bl FUN_02054990
	cmp r0, #0x0
	beq _0205701A
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_0205701A:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02057020
FUN_02057020: ; 0x02057020
	ldr r3, _02057024 ; =FUN_02057060
	bx r3
	.balign 4
_02057024: .word FUN_02057060

	thumb_func_start FUN_02057028
FUN_02057028: ; 0x02057028
	mov r1, #0x20
	tst r1, r0
	beq _02057032
	mov r0, #0x2
	bx lr
_02057032:
	mov r1, #0x10
	tst r0, r1
	beq _0205703C
	mov r1, #0x3
	b _0205703E
_0205703C:
	sub r1, #0x11
_0205703E:
	add r0, r1, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02057044
FUN_02057044: ; 0x02057044
	mov r1, #0x40
	tst r1, r0
	beq _0205704E
	mov r0, #0x0
	bx lr
_0205704E:
	mov r1, #0x80
	tst r0, r1
	beq _02057058
	mov r1, #0x1
	b _0205705A
_02057058:
	sub r1, #0x81
_0205705A:
	add r0, r1, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02057060
FUN_02057060: ; 0x02057060
	push {r3-r7, lr}
	add r5, r2, #0x0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02057028
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02057044
	mov r1, #0x0
	mvn r1, r1
	add r5, r0, #0x0
	cmp r4, r1
	beq _020570C0
	cmp r5, r1
	bne _02057086
	add r0, r4, #0x0
	pop {r3-r7, pc}
_02057086:
	add r0, r6, #0x0
	bl FUN_02055314
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02055430
	str r0, [sp, #0x0]
	add r0, r6, #0x0
	bl FUN_02055438
	mov r1, #0x0
	mvn r1, r1
	cmp r7, r1
	beq _020570BE
	ldr r1, [sp, #0x0]
	cmp r4, r1
	bne _020570B2
	cmp r5, r0
	bne _020570B2
	add r0, r7, #0x0
	pop {r3-r7, pc}
_020570B2:
	cmp r5, r0
	beq _020570BA
	add r0, r5, #0x0
	pop {r3-r7, pc}
_020570BA:
	add r0, r4, #0x0
	pop {r3-r7, pc}
_020570BE:
	add r0, r5, #0x0
_020570C0:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020570C4
FUN_020570C4: ; 0x020570C4
	push {r4, lr}
	bl FUN_020553A0
	add r4, r0, #0x0
	bl FUN_0205AD98
	cmp r0, #0x1
	bne _020570D8
	mov r0, #0x1
	pop {r4, pc}
_020570D8:
	add r0, r4, #0x0
	bl FUN_020586F0
	bl FUN_020570F0
	cmp r0, #0x1
	bne _020570EA
	mov r0, #0x1
	pop {r4, pc}
_020570EA:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020570F0
FUN_020570F0: ; 0x020570F0
	sub r0, #0x1c
	cmp r0, #0x3
	bhi _0205710E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02057102: ; jump table (using 16-bit offset)
	.short _0205710A - _02057102 - 2; case 0
	.short _0205710A - _02057102 - 2; case 1
	.short _0205710A - _02057102 - 2; case 2
	.short _0205710A - _02057102 - 2; case 3
_0205710A:
	mov r0, #0x1
	bx lr
_0205710E:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02057114
FUN_02057114: ; 0x02057114
	mov r0, #0x2
	tst r0, r1
	beq _0205711E
	mov r0, #0x1
	bx lr
_0205711E:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02057124
FUN_02057124: ; 0x02057124
	push {r3, lr}
	bl FUN_02055464
	sub r0, #0x58
	cmp r0, #0x3
	bhi _02057148
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205713C: ; jump table (using 16-bit offset)
	.short _02057144 - _0205713C - 2; case 0
	.short _02057144 - _0205713C - 2; case 1
	.short _02057144 - _0205713C - 2; case 2
	.short _02057144 - _0205713C - 2; case 3
_02057144:
	mov r0, #0x1
	pop {r3, pc}
_02057148:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0205714C
FUN_0205714C: ; 0x0205714C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020553C4
	cmp r0, #0x0
	beq _02057162
	cmp r0, #0x1
	beq _02057172
	cmp r0, #0x2
	bne _02057188
_02057162:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02056244
	bl FUN_020561EC
	add r4, r0, #0x0
	b _0205718E
_02057172:
	add r0, r5, #0x0
	bl FUN_020554BC
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020568A8
	bl FUN_02056874
	add r4, r0, #0x0
	b _0205718E
_02057188:
	mov r4, #0x0
	bl GF_AssertFail
_0205718E:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02057194
FUN_02057194: ; 0x02057194
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02057060
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_0205714C
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0205536C
	cmp r4, #0x0
	bne _020571C6
	add r0, r5, #0x0
	bl PlayerAvatar_GetFacingDirection
	mov r1, #0x0
	bl FUN_0205AFDC
	pop {r3-r7, pc}
_020571C6:
	cmp r4, #0x2
	bne _020571D4
	ldr r0, [sp, #0x0]
	mov r1, #0x28
	bl FUN_0205AFDC
	pop {r3-r7, pc}
_020571D4:
	add r0, r5, #0x0
	bl FUN_020553A0
	ldr r0, [sp, #0x1c]
	mov r4, #0x4
	add r1, r0, #0x0
	tst r1, r4
	beq _020571E8
	mov r4, #0x38
	b _02057244
_020571E8:
	cmp r0, #0x0
	beq _020571FC
	mov r1, #0x8
	mov r4, #0x1c
	tst r0, r1
	bne _02057244
	ldr r0, _02057250 ; =0x00000601
	bl PlaySE
	b _02057244
_020571FC:
	cmp r6, #0x5
	bhi _0205722E
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205720C: ; jump table (using 16-bit offset)
	.short _02057218 - _0205720C - 2; case 0
	.short _0205721A - _0205720C - 2; case 1
	.short _0205721E - _0205720C - 2; case 2
	.short _02057222 - _0205720C - 2; case 3
	.short _02057226 - _0205720C - 2; case 4
	.short _0205722A - _0205720C - 2; case 5
_02057218:
	b _02057230
_0205721A:
	mov r4, #0x8
	b _02057230
_0205721E:
	mov r4, #0xc
	b _02057230
_02057222:
	mov r4, #0x4c
	b _02057230
_02057226:
	mov r4, #0x10
	b _02057230
_0205722A:
	mov r4, #0x14
	b _02057230
_0205722E:
	mov r4, #0x4
_02057230:
	ldr r0, [sp, #0x18]
	cmp r0, #0x1
	bne _02057244
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02057114
	cmp r0, #0x1
	bne _02057244
	mov r4, #0x58
_02057244:
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	bl FUN_0205AFDC
	pop {r3-r7, pc}
	nop
_02057250: .word 0x00000601

	thumb_func_start FUN_02057254
FUN_02057254: ; 0x02057254
	push {r3, lr}
	bl FUN_020553A0
	bl FUN_0205AD98
	pop {r3, pc}

	thumb_func_start FUN_02057260
FUN_02057260: ; 0x02057260
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020553A0
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02056B5C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02057278
FUN_02057278: ; 0x02057278
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_020553A0
	add r1, r4, #0x0
	bl FUN_02059C90
	pop {r4, pc}

	thumb_func_start FUN_02057288
FUN_02057288: ; 0x02057288
	push {r3-r7, lr}
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	add r4, r2, #0x0
	add r7, r3, #0x0
	bl GetPlayerXCoord
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02059BF4
	add r0, r6, r0
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x0]
	bl GetPlayerYCoord
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02059C00
	add r0, r4, r0
	str r0, [r7, #0x0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020572B8
FUN_020572B8: ; 0x020572B8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl PlayerAvatar_GetFacingDirection
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl FUN_02057288
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020572D4
FUN_020572D4: ; 0x020572D4
	push {r3, lr}
	bl FUN_020553A0
	bl FUN_02058738
	ldr r0, [r0, #0xc]
	bl Sav2_GameStats_get
	mov r1, #0x5
	bl GameStats_Inc
	pop {r3, pc}

	thumb_func_start FUN_020572EC
FUN_020572EC: ; 0x020572EC
	push {r4-r6, lr}
	mov r0, #0x0
	add r4, r2, #0x0
	mvn r0, r0
	add r5, r1, #0x0
	cmp r4, r0
	beq _02057336
	add r0, r5, #0x0
	bl FUN_02058720
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02059BB4
	cmp r0, #0x1
	bne _0205731C
	cmp r4, #0x1
	bls _02057318
	mov r0, #0x1
	pop {r4-r6, pc}
_02057318:
	mov r0, #0x0
	pop {r4-r6, pc}
_0205731C:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02059BD4
	cmp r0, #0x1
	bne _02057336
	sub r0, r4, #0x2
	cmp r0, #0x1
	bls _02057332
	mov r0, #0x1
	pop {r4-r6, pc}
_02057332:
	mov r0, #0x0
	pop {r4-r6, pc}
_02057336:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0205733C
FUN_0205733C: ; 0x0205733C
	push {r3-r5, lr}
	add r4, r1, #0x0
	mov r1, #0x0
	mvn r1, r1
	add r5, r0, #0x0
	cmp r2, r1
	beq _0205734E
	mov r0, #0x0
	pop {r3-r5, pc}
_0205734E:
	bl FUN_020553C4
	cmp r0, #0x1
	beq _0205735A
	mov r0, #0x0
	pop {r3-r5, pc}
_0205735A:
	add r0, r5, #0x0
	bl FUN_02055738
	cmp r0, #0x0
	bne _02057368
	mov r0, #0x0
	pop {r3-r5, pc}
_02057368:
	add r0, r5, #0x0
	bl FUN_020553A0
	add r1, r4, #0x0
	bl FUN_02059B94
	cmp r0, #0x1
	bne _0205737C
	mov r0, #0x1
	pop {r3-r5, pc}
_0205737C:
	mov r0, #0x0
	pop {r3-r5, pc}
