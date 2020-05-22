    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020F5838
	.extern UNK_020F5848
	.extern UNK_02105E74
	.extern UNK_02105E80
	.extern UNK_02105E94
	.extern UNK_02105EB0

	.section .bss

	.global UNK_021C5A6C
UNK_021C5A6C: ; 0x021C5A6C
	.space 0x4

	.text

	thumb_func_start FUN_0204FBA8
FUN_0204FBA8: ; 0x0204FBA8
	bx lr
	.balign 4

	thumb_func_start FUN_0204FBAC
FUN_0204FBAC: ; 0x0204FBAC
	bx lr
	.balign 4

	thumb_func_start FUN_0204FBB0
FUN_0204FBB0: ; 0x0204FBB0
	push {r4, lr}
	ldr r1, _0204FC08 ; =UNK_021C5A6C
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _0204FC04
	bl FUN_0208881C
	mov r0, #0xf
	mov r1, #0x48
	bl FUN_02016998
	ldr r1, _0204FC08 ; =UNK_021C5A6C
	mov r2, #0x48
	str r0, [r1, #0x0]
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r0, _0204FC08 ; =UNK_021C5A6C
	mov r1, #0x32
	ldr r0, [r0, #0x0]
	mov r2, #0xa
	strh r1, [r0, #0x3c]
	ldr r0, _0204FC0C ; =FUN_0205006C
	mov r1, #0x0
	bl FUN_0200CA44
	ldr r1, _0204FC08 ; =UNK_021C5A6C
	ldr r2, [r1, #0x0]
	str r0, [r2, #0x38]
	ldr r0, [r1, #0x0]
	mov r2, #0x0
	str r4, [r0, #0x18]
	ldr r0, [r1, #0x0]
	str r2, [r0, #0x44]
	bl FUN_0204FBA8
	ldr r0, _0204FC08 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	add r0, #0x1c
	bl FUN_020312BC
_0204FC04:
	pop {r4, pc}
	nop
_0204FC08: .word UNK_021C5A6C
_0204FC0C: .word FUN_0205006C

	thumb_func_start FUN_0204FC10
FUN_0204FC10: ; 0x0204FC10
	push {r4-r6, lr}
	ldr r0, _0204FC58 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0204FC56
	ldr r0, [r0, #0x38]
	bl FUN_0200CAB4
	mov r4, #0x0
	ldr r6, _0204FC58 ; =UNK_021C5A6C
	add r5, r4, #0x0
_0204FC26:
	ldr r0, [r6, #0x0]
	ldr r0, [r0, r5]
	cmp r0, #0x0
	beq _0204FC32
	bl FUN_02016A18
_0204FC32:
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x4
	blt _0204FC26
	ldr r0, _0204FC58 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x44]
	cmp r0, #0x0
	beq _0204FC48
	bl FUN_02016A18
_0204FC48:
	ldr r0, _0204FC58 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _0204FC58 ; =UNK_021C5A6C
	mov r1, #0x0
	str r1, [r0, #0x0]
_0204FC56:
	pop {r4-r6, pc}
	.balign 4
_0204FC58: .word UNK_021C5A6C

	thumb_func_start FUN_0204FC5C
FUN_0204FC5C: ; 0x0204FC5C
	push {r4, lr}
	ldr r1, _0204FC9C ; =UNK_021C5A6C
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _0204FC9A
	bl FUN_020377AC
	bl FUN_02031824
	add r0, r4, #0x0
	bl FUN_0204FBB0
	mov r2, #0x3a
	mov r0, #0x3
	mov r1, #0x21
	lsl r2, r2, #0xa
	bl FUN_0201681C
	ldr r0, _0204FC9C ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x18]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F194
	cmp r0, #0x0
	bne _0204FC9A
	bl FUN_02031924
_0204FC9A:
	pop {r4, pc}
	.balign 4
_0204FC9C: .word UNK_021C5A6C

	thumb_func_start FUN_0204FCA0
FUN_0204FCA0: ; 0x0204FCA0
	push {r3, lr}
	ldr r0, _0204FCD0 ; =UNK_021C5A6C
	mov r2, #0x1
	ldr r1, [r0, #0x0]
	add r1, #0x41
	strb r2, [r1, #0x0]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x18]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	mov r1, #0x24
	bl FUN_0202A170
	ldr r0, _0204FCD0 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x18]
	bl MOD18_0223E060
	ldr r0, _0204FCD4 ; =FUN_020500A4
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_0204FCD0: .word UNK_021C5A6C
_0204FCD4: .word FUN_020500A4

	thumb_func_start FUN_0204FCD8
FUN_0204FCD8: ; 0x0204FCD8
	push {r3, lr}
	ldr r0, _0204FCEC ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0204FCEA
	ldr r0, _0204FCF0 ; =FUN_02050D54
	mov r1, #0x3
	bl FUN_02050094
_0204FCEA:
	pop {r3, pc}
	.balign 4
_0204FCEC: .word UNK_021C5A6C
_0204FCF0: .word FUN_02050D54

	thumb_func_start FUN_0204FCF4
FUN_0204FCF4: ; 0x0204FCF4
	push {r3, lr}
	bl FUN_02031914
	ldr r0, _0204FD04 ; =FUN_020504D8
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_0204FD04: .word FUN_020504D8

	thumb_func_start FUN_0204FD08
FUN_0204FD08: ; 0x0204FD08
	push {r3, lr}
	bl FUN_0202EDD8
	cmp r0, #0x0
	bne _0204FD1E
	bl MOD18_02245F1C
	ldr r0, _0204FD20 ; =FUN_020500A4
	mov r1, #0x0
	bl FUN_02050094
_0204FD1E:
	pop {r3, pc}
	.balign 4
_0204FD20: .word FUN_020500A4

	thumb_func_start FUN_0204FD24
FUN_0204FD24: ; 0x0204FD24
	push {r3, lr}
	bl FUN_02031934
	ldr r0, _0204FD34 ; =FUN_0204FD08
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_0204FD34: .word FUN_0204FD08

	thumb_func_start FUN_0204FD38
FUN_0204FD38: ; 0x0204FD38
	push {r3-r7, lr}
	sub sp, #0x10
	ldr r0, _0204FDBC ; =UNK_021C5A6C
	add r2, sp, #0x0
	ldr r0, [r0, #0x0]
	ldr r3, _0204FDC0 ; =UNK_020F5838
	ldr r5, [r0, #0x34]
	add r6, r2, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, _0204FDC4 ; =FUN_020502AC
	ldr r4, _0204FDC8 ; =FUN_02050548
	ldr r7, _0204FDCC ; =FUN_02050168
	cmp r5, r0
	bne _0204FD68
	ldr r0, _0204FDD0 ; =FUN_0205031C
	mov r1, #0x0
	bl FUN_02050094
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_0204FD68:
	cmp r4, r5
	bne _0204FD7A
	ldr r0, _0204FDD4 ; =FUN_02050578
	mov r1, #0x0
	bl FUN_02050094
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_0204FD7A:
	cmp r7, r5
	bne _0204FD8C
	ldr r0, _0204FDD8 ; =FUN_020505E0
	mov r1, #0x0
	bl FUN_02050094
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_0204FD8C:
	ldr r0, _0204FDDC ; =FUN_020504D0
	cmp r0, r5
	bne _0204FDA0
	ldr r0, _0204FDE0 ; =FUN_02050610
	mov r1, #0x0
	bl FUN_02050094
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_0204FDA0:
	mov r1, #0x0
_0204FDA2:
	ldr r0, [r6, #0x0]
	cmp r5, r0
	bne _0204FDAE
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_0204FDAE:
	add r1, r1, #0x1
	add r6, r6, #0x4
	cmp r1, #0x4
	blo _0204FDA2
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_0204FDBC: .word UNK_021C5A6C
_0204FDC0: .word UNK_020F5838
_0204FDC4: .word FUN_020502AC
_0204FDC8: .word FUN_02050548
_0204FDCC: .word FUN_02050168
_0204FDD0: .word FUN_0205031C
_0204FDD4: .word FUN_02050578
_0204FDD8: .word FUN_020505E0
_0204FDDC: .word FUN_020504D0
_0204FDE0: .word FUN_02050610

	thumb_func_start FUN_0204FDE4
FUN_0204FDE4: ; 0x0204FDE4
	push {r4, lr}
	ldr r0, _0204FE38 ; =UNK_021C5A6C
	ldr r3, _0204FE3C ; =FUN_0205058C
	ldr r0, [r0, #0x0]
	ldr r2, _0204FE40 ; =FUN_020505F4
	ldr r4, [r0, #0x34]
	ldr r0, _0204FE44 ; =FUN_02050330
	ldr r1, _0204FE48 ; =FUN_02050624
	cmp r4, r0
	bne _0204FE04
	ldr r0, _0204FE4C ; =FUN_02050338
	mov r1, #0x0
	bl FUN_02050094
	mov r0, #0x1
	pop {r4, pc}
_0204FE04:
	cmp r3, r4
	bne _0204FE14
	ldr r0, _0204FE50 ; =FUN_02050594
	mov r1, #0x0
	bl FUN_02050094
	mov r0, #0x1
	pop {r4, pc}
_0204FE14:
	cmp r2, r4
	bne _0204FE24
	ldr r0, _0204FE54 ; =FUN_020505F8
	mov r1, #0x0
	bl FUN_02050094
	mov r0, #0x1
	pop {r4, pc}
_0204FE24:
	cmp r1, r4
	bne _0204FE34
	ldr r0, _0204FE58 ; =FUN_02050628
	mov r1, #0x0
	bl FUN_02050094
	mov r0, #0x1
	pop {r4, pc}
_0204FE34:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0204FE38: .word UNK_021C5A6C
_0204FE3C: .word FUN_0205058C
_0204FE40: .word FUN_020505F4
_0204FE44: .word FUN_02050330
_0204FE48: .word FUN_02050624
_0204FE4C: .word FUN_02050338
_0204FE50: .word FUN_02050594
_0204FE54: .word FUN_020505F8
_0204FE58: .word FUN_02050628

	thumb_func_start FUN_0204FE5C
FUN_0204FE5C: ; 0x0204FE5C
	push {r3-r4}
	sub sp, #0x38
	ldr r4, _0204FEA8 ; =UNK_020F5848
	add r3, sp, #0x0
	mov r2, #0x7
_0204FE66:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0204FE66
	ldr r0, _0204FEAC ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x34]
	cmp r0, #0x0
	bne _0204FE80
	add sp, #0x38
	mov r0, #0x0
	pop {r3-r4}
	bx lr
_0204FE80:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _0204FE9E
	add r2, sp, #0x0
_0204FE88:
	ldr r0, [r2, #0x0]
	cmp r1, r0
	bne _0204FE96
	add sp, #0x38
	mov r0, #0x1
	pop {r3-r4}
	bx lr
_0204FE96:
	add r2, r2, #0x4
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	bne _0204FE88
_0204FE9E:
	mov r0, #0x0
	add sp, #0x38
	pop {r3-r4}
	bx lr
	nop
_0204FEA8: .word UNK_020F5848
_0204FEAC: .word UNK_021C5A6C

	thumb_func_start FUN_0204FEB0
FUN_0204FEB0: ; 0x0204FEB0
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	bne _0204FEE8
	add r0, r5, #0x0
	bl FUN_020377AC
	mov r1, #0x0
	add r3, r5, #0x0
	str r1, [sp, #0x0]
	add r3, #0xac
	ldr r3, [r3, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02031948
	add r0, r5, #0x0
	bl FUN_0204FBB0
	ldr r0, _0204FEEC ; =FUN_02050640
	mov r1, #0x0
	bl FUN_02050094
_0204FEE8:
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_0204FEEC: .word FUN_02050640

	thumb_func_start FUN_0204FEF0
FUN_0204FEF0: ; 0x0204FEF0
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	bne _0204FF28
	add r0, r5, #0x0
	bl FUN_020377AC
	mov r1, #0x0
	add r3, r5, #0x0
	str r1, [sp, #0x0]
	add r3, #0xac
	ldr r3, [r3, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02031990
	add r0, r5, #0x0
	bl FUN_0204FBB0
	ldr r0, _0204FF2C ; =FUN_02050668
	mov r1, #0x0
	bl FUN_02050094
_0204FF28:
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_0204FF2C: .word FUN_02050668

	thumb_func_start FUN_0204FF30
FUN_0204FF30: ; 0x0204FF30
	ldr r1, _0204FF40 ; =UNK_021C5A6C
	ldr r3, _0204FF44 ; =FUN_02050094
	ldr r1, [r1, #0x0]
	add r1, #0x3e
	strb r0, [r1, #0x0]
	ldr r0, _0204FF48 ; =FUN_02050688
	mov r1, #0x0
	bx r3
	.balign 4
_0204FF40: .word UNK_021C5A6C
_0204FF44: .word FUN_02050094
_0204FF48: .word FUN_02050688

	thumb_func_start FUN_0204FF4C
FUN_0204FF4C: ; 0x0204FF4C
	ldr r3, _0204FF54 ; =FUN_02050094
	ldr r0, _0204FF58 ; =FUN_02050BBC
	mov r1, #0x0
	bx r3
	.balign 4
_0204FF54: .word FUN_02050094
_0204FF58: .word FUN_02050BBC

	thumb_func_start FUN_0204FF5C
FUN_0204FF5C: ; 0x0204FF5C
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0200E3BC
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0200E3BC
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_020334E8
	bl FUN_02031810
	cmp r0, #0x0
	beq _02050014
	ldr r0, _02050018 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	bne _0204FF9C
	add r0, r4, #0x0
	bl FUN_0204FBB0
	ldr r0, _02050018 ; =UNK_021C5A6C
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, #0x42
	strb r1, [r0, #0x0]
	b _0204FFA2
_0204FF9C:
	mov r0, #0x0
	add r1, #0x42
	strb r0, [r1, #0x0]
_0204FFA2:
	ldr r0, _02050018 ; =UNK_021C5A6C
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x43
	strb r1, [r0, #0x0]
	bl FUN_02031190
	str r0, [sp, #0x8]
	bl FUN_02031190
	bl FUN_0202DFA4
	mov r4, #0x0
	bl FUN_02030F20
	cmp r0, #0x0
	ble _0204FFEA
	ldr r6, _02050018 ; =UNK_021C5A6C
	add r5, r4, #0x0
	add r7, r4, #0x0
_0204FFCA:
	ldr r0, [r6, #0x0]
	ldr r0, [r0, r5]
	cmp r0, #0x0
	bne _0204FFDE
	ldr r1, _0205001C ; =0x0000066C
	add r0, r7, #0x0
	bl FUN_02016998
	ldr r1, [r6, #0x0]
	str r0, [r1, r5]
_0204FFDE:
	add r5, r5, #0x4
	add r4, r4, #0x1
	bl FUN_02030F20
	cmp r4, r0
	blt _0204FFCA
_0204FFEA:
	ldr r0, _02050018 ; =UNK_021C5A6C
	mov r3, #0xff
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x18]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x8]
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	str r0, [sp, #0x4]
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	bl FUN_02064E90
	mov r0, #0x5f
	bl FUN_02031588
	ldr r0, _02050020 ; =FUN_02050C14
	mov r1, #0x0
	bl FUN_02050094
_02050014:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02050018: .word UNK_021C5A6C
_0205001C: .word 0x0000066C
_02050020: .word FUN_02050C14

	thumb_func_start FUN_02050024
FUN_02050024: ; 0x02050024
	push {r3, lr}
	ldr r0, _02050040 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0205003E
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_020334E8
	ldr r0, _02050044 ; =FUN_02050DB0
	mov r1, #0x5
	bl FUN_02050094
_0205003E:
	pop {r3, pc}
	.balign 4
_02050040: .word UNK_021C5A6C
_02050044: .word FUN_02050DB0

	thumb_func_start FUN_02050048
FUN_02050048: ; 0x02050048
	push {r3, lr}
	ldr r0, _02050064 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02050060
	mov r0, #0x5b
	bl FUN_02031588
	ldr r0, _02050068 ; =FUN_02050D88
	mov r1, #0x5
	bl FUN_02050094
_02050060:
	pop {r3, pc}
	nop
_02050064: .word UNK_021C5A6C
_02050068: .word FUN_02050D88

	thumb_func_start FUN_0205006C
FUN_0205006C: ; 0x0205006C
	push {r3, lr}
	ldr r1, _02050090 ; =UNK_021C5A6C
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	bne _0205007C
	bl FUN_0200CAB4
	pop {r3, pc}
_0205007C:
	ldr r1, [r2, #0x34]
	cmp r1, #0x0
	beq _0205008C
	add r2, #0x40
	ldrb r0, [r2, #0x0]
	cmp r0, #0x0
	bne _0205008C
	blx r1
_0205008C:
	pop {r3, pc}
	nop
_02050090: .word UNK_021C5A6C

	thumb_func_start FUN_02050094
FUN_02050094: ; 0x02050094
	ldr r2, _020500A0 ; =UNK_021C5A6C
	ldr r3, [r2, #0x0]
	str r0, [r3, #0x34]
	ldr r0, [r2, #0x0]
	strh r1, [r0, #0x3c]
	bx lr
	.balign 4
_020500A0: .word UNK_021C5A6C

	thumb_func_start FUN_020500A4
FUN_020500A4: ; 0x020500A4
	push {r3, lr}
	ldr r0, _02050108 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _020500B6
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_020500B6:
	bl FUN_02030F40
	cmp r0, #0x0
	beq _02050104
	ldr r0, _02050108 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x18]
	bl MOD18_0223E1E0
	bl FUN_0202DBE0
	mov r0, #0x0
	bl FUN_0204D168
	bl MOD18_0223EF7C
	bl MOD06_02245FA0
	ldr r0, _02050108 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x18]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F194
	cmp r0, #0x0
	bne _020500F8
	ldr r0, _0205010C ; =FUN_02050114
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
_020500F8:
	bl FUN_0204F80C
	ldr r0, _02050110 ; =FUN_02050144
	mov r1, #0x18
	bl FUN_02050094
_02050104:
	pop {r3, pc}
	nop
_02050108: .word UNK_021C5A6C
_0205010C: .word FUN_02050114
_02050110: .word FUN_02050144

	thumb_func_start FUN_02050114
FUN_02050114: ; 0x02050114
	push {r3, lr}
	ldr r0, _0205013C ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x18]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F194
	cmp r0, #0x0
	beq _0205013A
	bl FUN_02031880
	bl FUN_0204F80C
	ldr r0, _02050140 ; =FUN_02050168
	mov r1, #0x18
	bl FUN_02050094
_0205013A:
	pop {r3, pc}
	.balign 4
_0205013C: .word UNK_021C5A6C
_02050140: .word FUN_02050168

	thumb_func_start FUN_02050144
FUN_02050144: ; 0x02050144
	push {r3, lr}
	ldr r0, _02050160 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050156
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_02050156:
	ldr r0, _02050164 ; =FUN_02050168
	mov r1, #0x18
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_02050160: .word UNK_021C5A6C
_02050164: .word FUN_02050168

	thumb_func_start FUN_02050168
FUN_02050168: ; 0x02050168
	push {r3, lr}
	bl MOD06_0223DFB4
	bl FUN_0204F80C
	bl FUN_020318C4
	cmp r0, #0x0
	beq _02050198
	bl FUN_02031190
	cmp r0, #0x0
	bne _02050190
	bl MOD18_02245324
	ldr r0, _0205019C ; =FUN_0205024C
	mov r1, #0x3c
	bl FUN_02050094
	pop {r3, pc}
_02050190:
	ldr r0, _020501A0 ; =FUN_020501A4
	mov r1, #0x78
	bl FUN_02050094
_02050198:
	pop {r3, pc}
	nop
_0205019C: .word FUN_0205024C
_020501A0: .word FUN_020501A4

	thumb_func_start FUN_020501A4
FUN_020501A4: ; 0x020501A4
	push {r3, lr}
	ldr r0, _02050240 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _020501B4
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
_020501B4:
	bl FUN_0202EE44
	cmp r0, #0x0
	bne _020501CE
	bl FUN_020311F0
	cmp r0, #0x0
	bne _020501CE
	ldr r0, _02050240 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x3c]
	cmp r0, #0x0
	bne _020501DC
_020501CE:
	bl FUN_02031880
	ldr r0, _02050244 ; =FUN_020504A4
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
_020501DC:
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0205023C
	ldr r0, _02050240 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050202
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	bl FUN_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	bne _0205023C
_02050202:
	bl MOD18_0223E6B8
	mov r0, #0x0
	bl FUN_0204D040
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl MOD18_022408FC
	mov r0, #0x0
	mov r1, #0x1
	bl MOD18_0223FCE8
	mov r0, #0x0
	bl FUN_0202DE78
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	bl FUN_0204D43C
	bl FUN_0204F858
	ldr r0, _02050248 ; =FUN_02050350
	mov r1, #0xa
	bl FUN_02050094
_0205023C:
	pop {r3, pc}
	nop
_02050240: .word UNK_021C5A6C
_02050244: .word FUN_020504A4
_02050248: .word FUN_02050350

	thumb_func_start FUN_0205024C
FUN_0205024C: ; 0x0205024C
	push {r3, lr}
	bl MOD06_0223DFB4
	ldr r0, _020502A0 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050260
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
_02050260:
	bl FUN_020311E8
	cmp r0, #0x0
	bne _02050272
	ldr r0, _020502A0 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x3c]
	cmp r0, #0x0
	bne _0205029E
_02050272:
	bl MOD18_0223E6B8
	cmp r0, #0x0
	beq _0205027E
	bl FUN_0204F7FC
_0205027E:
	ldr r0, _020502A4 ; =UNK_02105E74
	bl FUN_0204FBAC
	mov r0, #0x0
	bl FUN_0204D168
	bl FUN_0204F930
	bl MOD06_02245FA0
	bl MOD18_0223E7FC
	ldr r0, _020502A8 ; =FUN_020502AC
	mov r1, #0x0
	bl FUN_02050094
_0205029E:
	pop {r3, pc}
	.balign 4
_020502A0: .word UNK_021C5A6C
_020502A4: .word UNK_02105E74
_020502A8: .word FUN_020502AC

	thumb_func_start FUN_020502AC
FUN_020502AC: ; 0x020502AC
	push {r3, lr}
	bl MOD06_0223DFB4
	ldr r0, _02050314 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x18]
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	bne _02050310
	bl FUN_020311F0
	cmp r0, #0x0
	bne _020502E2
	bl FUN_0202EE24
	cmp r0, #0x0
	beq _020502E2
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _02050310
	bl FUN_02031280
	cmp r0, #0x0
	bne _02050310
_020502E2:
	mov r0, #0x0
	bl MOD18_02245358
	bl FUN_0204F90C
	bl MOD06_02247808
	mov r0, #0x2b
	bl FUN_020311DC
	bl FUN_02031190
	mov r1, #0x1
	bl MOD18_0223FCE8
	bl MOD18_0223E6B8
	bl FUN_020318B4
	ldr r0, _02050318 ; =FUN_02050458
	mov r1, #0x0
	bl FUN_02050094
_02050310:
	pop {r3, pc}
	nop
_02050314: .word UNK_021C5A6C
_02050318: .word FUN_02050458

	thumb_func_start FUN_0205031C
FUN_0205031C: ; 0x0205031C
	push {r3, lr}
	bl FUN_0204CC48
	ldr r0, _0205032C ; =FUN_02050330
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_0205032C: .word FUN_02050330

	thumb_func_start FUN_02050330
FUN_02050330: ; 0x02050330
	ldr r3, _02050334 ; =MOD06_0223DFB4
	bx r3
	.balign 4
_02050334: .word MOD06_0223DFB4

	thumb_func_start FUN_02050338
FUN_02050338: ; 0x02050338
	push {r3, lr}
	bl MOD18_02245F1C
	bl FUN_0204CC9C
	ldr r0, _0205034C ; =FUN_020502AC
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_0205034C: .word FUN_020502AC

	thumb_func_start FUN_02050350
FUN_02050350: ; 0x02050350
	push {r3, lr}
	ldr r0, _020503A8 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x3c]
	cmp r0, #0x9
	bne _02050364
	bl FUN_0202DBE0
	bl MOD18_0223E7FC
_02050364:
	ldr r0, _020503A8 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x3c]
	cmp r0, #0x1
	bne _02050374
	mov r0, #0x0
	bl FUN_0204D198
_02050374:
	ldr r0, _020503A8 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050384
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_02050384:
	bl FUN_0202DCF8
	cmp r0, #0x0
	beq _020503A0
	ldr r0, _020503AC ; =UNK_02105E80
	bl FUN_0204FBAC
	bl FUN_0204F930
	ldr r0, _020503B0 ; =FUN_020503B4
	mov r1, #0xc8
	bl FUN_02050094
	pop {r3, pc}
_020503A0:
	bl FUN_02050548
	pop {r3, pc}
	nop
_020503A8: .word UNK_021C5A6C
_020503AC: .word UNK_02105E80
_020503B0: .word FUN_020503B4

	thumb_func_start FUN_020503B4
FUN_020503B4: ; 0x020503B4
	push {r3, lr}
	bl FUN_0204FB00
	cmp r0, #0x0
	beq _020503CC
	bl MOD18_0223EF7C
	ldr r0, _020503E8 ; =FUN_020503F0
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
_020503CC:
	bl FUN_02050548
	ldr r0, _020503EC ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _020503E0
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_020503E0:
	bl FUN_02050510
	pop {r3, pc}
	nop
_020503E8: .word FUN_020503F0
_020503EC: .word UNK_021C5A6C

	thumb_func_start FUN_020503F0
FUN_020503F0: ; 0x020503F0
	push {r3, lr}
	bl MOD18_0223F4D8
	cmp r0, #0x0
	beq _02050412
	ldr r0, _02050418 ; =UNK_02105E94
	bl FUN_0204FBAC
	bl MOD18_0223F4F4
	bl MOD06_02245FA0
	ldr r0, _0205041C ; =FUN_02050420
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
_02050412:
	bl FUN_02050548
	pop {r3, pc}
	.balign 4
_02050418: .word UNK_02105E94
_0205041C: .word FUN_02050420

	thumb_func_start FUN_02050420
FUN_02050420: ; 0x02050420
	push {r3, lr}
	bl MOD18_022461A4
	cmp r0, #0x0
	beq _0205044A
	ldr r0, _02050450 ; =UNK_02105EB0
	bl FUN_0204FBAC
	bl MOD18_022461B8
	mov r0, #0x1
	bl FUN_0204D168
	mov r0, #0x1f
	bl FUN_020311DC
	ldr r0, _02050454 ; =FUN_02050548
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
_0205044A:
	bl FUN_02050548
	pop {r3, pc}
	.balign 4
_02050450: .word UNK_02105EB0
_02050454: .word FUN_02050548

	thumb_func_start FUN_02050458
FUN_02050458: ; 0x02050458
	push {r3, lr}
	bl FUN_02031280
	cmp r0, #0x0
	beq _02050472
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0204EAD8
	ldr r0, _02050474 ; =FUN_02050478
	mov r1, #0x1e
	bl FUN_02050094
_02050472:
	pop {r3, pc}
	.balign 4
_02050474: .word FUN_02050478

	thumb_func_start FUN_02050478
FUN_02050478: ; 0x02050478
	push {r3, lr}
	ldr r0, _0205049C ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _0205048A
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_0205048A:
	bl FUN_02031190
	cmp r0, #0x0
	bne _0205049A
	ldr r0, _020504A0 ; =FUN_020500A4
	mov r1, #0x0
	bl FUN_02050094
_0205049A:
	pop {r3, pc}
	.balign 4
_0205049C: .word UNK_021C5A6C
_020504A0: .word FUN_020500A4

	thumb_func_start FUN_020504A4
FUN_020504A4: ; 0x020504A4
	push {r3, lr}
	ldr r0, _020504C8 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _020504B6
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_020504B6:
	bl FUN_02031190
	cmp r0, #0x0
	bne _020504C6
	ldr r0, _020504CC ; =FUN_020500A4
	mov r1, #0x0
	bl FUN_02050094
_020504C6:
	pop {r3, pc}
	.balign 4
_020504C8: .word UNK_021C5A6C
_020504CC: .word FUN_020500A4

	thumb_func_start FUN_020504D0
FUN_020504D0: ; 0x020504D0
	ldr r3, _020504D4 ; =MOD06_0223DFB4
	bx r3
	.balign 4
_020504D4: .word MOD06_0223DFB4

	thumb_func_start FUN_020504D8
FUN_020504D8: ; 0x020504D8
	push {r3, lr}
	bl FUN_02031190
	cmp r0, #0x0
	bne _02050506
	ldr r0, _02050508 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x18]
	bl MOD18_0223E1E0
	bl FUN_0202DBE0
	mov r0, #0x0
	bl FUN_0204D168
	bl MOD18_0223EF7C
	bl MOD06_02245FA0
	ldr r0, _0205050C ; =FUN_020504D0
	mov r1, #0x0
	bl FUN_02050094
_02050506:
	pop {r3, pc}
	.balign 4
_02050508: .word UNK_021C5A6C
_0205050C: .word FUN_020504D0

	thumb_func_start FUN_02050510
FUN_02050510: ; 0x02050510
	push {r3, lr}
	bl FUN_02031190
	mov r1, #0x1
	bl MOD18_0223FCE8
	bl FUN_02031190
	mov r1, #0x1
	bl MOD18_02247728
	bl MOD18_0223CACC
	bl FUN_0204CEF8
	bl MOD18_0223E6B8
	bl FUN_02031880
	bl FUN_0204FB28
	ldr r0, _02050544 ; =FUN_020504A4
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_02050544: .word FUN_020504A4

	thumb_func_start FUN_02050548
FUN_02050548: ; 0x02050548
	push {r3, lr}
	bl MOD06_0223DFB4
	bl FUN_0204F80C
	ldr r0, _02050574 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x18]
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	bne _02050572
	bl FUN_0202EE44
	cmp r0, #0x0
	bne _0205056E
	bl FUN_020311F0
	cmp r0, #0x0
	beq _02050572
_0205056E:
	bl FUN_02050510
_02050572:
	pop {r3, pc}
	.balign 4
_02050574: .word UNK_021C5A6C

	thumb_func_start FUN_02050578
FUN_02050578: ; 0x02050578
	push {r3, lr}
	bl FUN_0204CC48
	ldr r0, _02050588 ; =FUN_0205058C
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_02050588: .word FUN_0205058C

	thumb_func_start FUN_0205058C
FUN_0205058C: ; 0x0205058C
	ldr r3, _02050590 ; =MOD18_02247830
	bx r3
	.balign 4
_02050590: .word MOD18_02247830

	thumb_func_start FUN_02050594
FUN_02050594: ; 0x02050594
	push {r3, lr}
	bl MOD18_02245F1C
	bl FUN_0204CC9C
	bl FUN_0202EE44
	cmp r0, #0x0
	bne _020505AE
	bl FUN_020311F0
	cmp r0, #0x0
	beq _020505CC
_020505AE:
	bl MOD18_022452A4
	bl FUN_0204CEF8
	bl MOD18_0223E6B8
	bl FUN_02031880
	bl FUN_0204FB28
	ldr r0, _020505D8 ; =FUN_020504A4
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
_020505CC:
	ldr r0, _020505DC ; =FUN_02050548
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
	nop
_020505D8: .word FUN_020504A4
_020505DC: .word FUN_02050548

	thumb_func_start FUN_020505E0
FUN_020505E0: ; 0x020505E0
	push {r3, lr}
	bl FUN_0204CC48
	ldr r0, _020505F0 ; =FUN_020505F4
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_020505F0: .word FUN_020505F4

	thumb_func_start FUN_020505F4
FUN_020505F4: ; 0x020505F4
	bx lr
	.balign 4

	thumb_func_start FUN_020505F8
FUN_020505F8: ; 0x020505F8
	push {r3, lr}
	bl MOD18_02245F1C
	bl FUN_0204CC9C
	ldr r0, _0205060C ; =FUN_02050168
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_0205060C: .word FUN_02050168

	thumb_func_start FUN_02050610
FUN_02050610: ; 0x02050610
	push {r3, lr}
	bl FUN_0204CF24
	ldr r0, _02050620 ; =FUN_02050624
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_02050620: .word FUN_02050624

	thumb_func_start FUN_02050624
FUN_02050624: ; 0x02050624
	bx lr
	.balign 4

	thumb_func_start FUN_02050628
FUN_02050628: ; 0x02050628
	push {r3, lr}
	bl MOD18_02245F1C
	bl FUN_0204CC9C
	ldr r0, _0205063C ; =FUN_020504D0
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_0205063C: .word FUN_020504D0

	thumb_func_start FUN_02050640
FUN_02050640: ; 0x02050640
	push {r3, lr}
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0205065E
	bl MOD06_02240834
	bl FUN_0202DBE0
	ldr r0, _02050660 ; =FUN_02050664
	mov r1, #0x0
	bl FUN_02050094
_0205065E:
	pop {r3, pc}
	.balign 4
_02050660: .word FUN_02050664

	thumb_func_start FUN_02050664
FUN_02050664: ; 0x02050664
	bx lr
	.balign 4

	thumb_func_start FUN_02050668
FUN_02050668: ; 0x02050668
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _0205067E
	bl MOD06_022407CC
	ldr r0, _02050680 ; =FUN_02050684
	mov r1, #0x0
	bl FUN_02050094
_0205067E:
	pop {r3, pc}
	.balign 4
_02050680: .word FUN_02050684

	thumb_func_start FUN_02050684
FUN_02050684: ; 0x02050684
	bx lr
	.balign 4

	thumb_func_start FUN_02050688
FUN_02050688: ; 0x02050688
	push {r3, lr}
	ldr r0, _020506A0 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	bl FUN_020319D8
	ldr r0, _020506A4 ; =FUN_020506A8
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_020506A0: .word UNK_021C5A6C
_020506A4: .word FUN_020506A8

	thumb_func_start FUN_020506A8
FUN_020506A8: ; 0x020506A8
	push {r3, lr}
	bl FUN_02031A2C
	cmp r0, #0x0
	beq _020506BE
	bl FUN_0202DBE0
	ldr r0, _020506C0 ; =FUN_020506C4
	mov r1, #0x0
	bl FUN_02050094
_020506BE:
	pop {r3, pc}
	.balign 4
_020506C0: .word FUN_020506C4

	thumb_func_start FUN_020506C4
FUN_020506C4: ; 0x020506C4
	bx lr
	.balign 4

	thumb_func_start FUN_020506C8
FUN_020506C8: ; 0x020506C8
	push {r3, lr}
	mov r0, #0x62
	bl FUN_020315D8
	cmp r0, #0x0
	beq _02050704
	bl FUN_0204D320
	add r1, r0, #0x0
	mov r0, #0xf
	bl FUN_02016998
	ldr r1, _02050720 ; =UNK_021C5A6C
	mov r2, #0x0
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x18]
	bl FUN_0204CB20
	bl FUN_0204F80C
	bl FUN_02030FC8
	mov r0, #0x5c
	bl FUN_02031588
	ldr r0, _02050724 ; =FUN_02050728
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
_02050704:
	ldr r0, _02050720 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050714
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_02050714:
	mov r0, #0x1e
	strh r0, [r1, #0x3c]
	mov r0, #0x62
	bl FUN_02031588
	pop {r3, pc}
	.balign 4
_02050720: .word UNK_021C5A6C
_02050724: .word FUN_02050728

	thumb_func_start FUN_02050728
FUN_02050728: ; 0x02050728
	push {lr}
	sub sp, #0xc
	bl FUN_02031190
	cmp r0, #0x0
	bne _02050738
	bl FUN_0202DDE8
_02050738:
	mov r0, #0x5c
	bl FUN_020315D8
	cmp r0, #0x0
	beq _02050776
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0x0
	add r2, r1, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	mov r0, #0x0
	bl FUN_0200E388
	mov r0, #0x1
	bl FUN_0200E388
	bl FUN_0204CC9C
	mov r0, #0x0
	bl FUN_0204D168
	ldr r0, _0205077C ; =FUN_020507B4
	mov r1, #0x1
	bl FUN_02050094
_02050776:
	add sp, #0xc
	pop {pc}
	nop
_0205077C: .word FUN_020507B4

	thumb_func_start FUN_02050780
FUN_02050780: ; 0x02050780
	push {r3, lr}
	ldr r0, _020507AC ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050792
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_02050792:
	mov r0, #0x1e
	bl FUN_020315D8
	cmp r0, #0x0
	beq _020507A8
	bl FUN_02030FA8
	ldr r0, _020507B0 ; =FUN_02050930
	mov r1, #0x0
	bl FUN_02050094
_020507A8:
	pop {r3, pc}
	nop
_020507AC: .word UNK_021C5A6C
_020507B0: .word FUN_02050930

	thumb_func_start FUN_020507B4
FUN_020507B4: ; 0x020507B4
	push {r3, lr}
	ldr r0, _020507F0 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _020507C6
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_020507C6:
	bl FUN_02031190
	cmp r0, #0x0
	bne _020507DE
	bl FUN_0204ED08
	cmp r0, #0x0
	beq _020507EC
	mov r0, #0x1e
	bl FUN_02031588
	b _020507E4
_020507DE:
	mov r0, #0x1e
	bl FUN_02031588
_020507E4:
	ldr r0, _020507F4 ; =FUN_02050780
	mov r1, #0x14
	bl FUN_02050094
_020507EC:
	pop {r3, pc}
	nop
_020507F0: .word UNK_021C5A6C
_020507F4: .word FUN_02050780

	thumb_func_start FUN_020507F8
FUN_020507F8: ; 0x020507F8
	push {r3, lr}
	mov r0, #0x62
	bl FUN_020315D8
	cmp r0, #0x0
	beq _02050830
	bl FUN_0204D320
	add r1, r0, #0x0
	mov r0, #0xf
	bl FUN_02016998
	ldr r1, _0205084C ; =UNK_021C5A6C
	mov r2, #0x0
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x18]
	bl FUN_0204CB20
	bl FUN_0204F80C
	mov r0, #0x5c
	bl FUN_02031588
	ldr r0, _02050850 ; =FUN_02050854
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
_02050830:
	ldr r0, _0205084C ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050840
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_02050840:
	mov r0, #0x1e
	strh r0, [r1, #0x3c]
	mov r0, #0x62
	bl FUN_02031588
	pop {r3, pc}
	.balign 4
_0205084C: .word UNK_021C5A6C
_02050850: .word FUN_02050854

	thumb_func_start FUN_02050854
FUN_02050854: ; 0x02050854
	push {r3, lr}
	sub sp, #0x10
	bl FUN_02031190
	cmp r0, #0x0
	bne _02050864
	bl FUN_0202DDE8
_02050864:
	mov r0, #0x5c
	bl FUN_020315D8
	cmp r0, #0x0
	beq _020508B0
	bl FUN_0204CC9C
	mov r0, #0x0
	bl FUN_0204D168
	mov r1, #0x1
	add r0, sp, #0xc
	strb r1, [r0, #0x0]
	mov r0, #0x5e
	add r1, sp, #0xc
	bl FUN_020311D0
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0x0
	add r2, r1, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	mov r0, #0x0
	bl FUN_0200E388
	mov r0, #0x1
	bl FUN_0200E388
	ldr r0, _020508B4 ; =FUN_02050A14
	mov r1, #0x0
	bl FUN_02050094
_020508B0:
	add sp, #0x10
	pop {r3, pc}
	.balign 4
_020508B4: .word FUN_02050A14

	thumb_func_start FUN_020508B8
FUN_020508B8: ; 0x020508B8
	push {r3-r7, lr}
	mov r7, #0x0
	bl FUN_02030F20
	cmp r0, #0x0
	ble _02050916
	ldr r6, _02050928 ; =UNK_021C5A6C
_020508C6:
	bl FUN_02031190
	cmp r7, r0
	beq _0205090C
	add r0, r7, #0x0
	bl FUN_020315FC
	cmp r0, #0x5e
	bne _0205090C
	ldr r0, [r6, #0x0]
	ldr r0, [r0, #0x18]
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	bne _0205090C
	mov r4, #0x0
	add r5, r4, #0x0
_020508E6:
	ldr r0, [r6, #0x0]
	ldr r0, [r0, r5]
	cmp r0, #0x0
	beq _020508F8
	bl FUN_02016A18
	ldr r1, [r6, #0x0]
	mov r0, #0x0
	str r0, [r1, r5]
_020508F8:
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x4
	blt _020508E6
	ldr r0, [r6, #0x0]
	ldr r1, _0205092C ; =0x0000238E
	ldr r0, [r0, #0x18]
	mov r2, #0x0
	bl FUN_02038C78
_0205090C:
	add r7, r7, #0x1
	bl FUN_02030F20
	cmp r7, r0
	blt _020508C6
_02050916:
	ldr r1, _02050928 ; =UNK_021C5A6C
	mov r0, #0x4
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x18]
	ldr r1, [r1, #0x8]
	bl FUN_020335F0
	pop {r3-r7, pc}
	nop
_02050928: .word UNK_021C5A6C
_0205092C: .word 0x0000238E

	thumb_func_start FUN_02050930
FUN_02050930: ; 0x02050930
	push {r3, lr}
	bl FUN_0204EB44
	cmp r0, #0x0
	bne _0205095A
	ldr r0, _02050960 ; =UNK_021C5A6C
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x43
	strb r1, [r0, #0x0]
	mov r1, #0x1
	add r0, sp, #0x0
	strb r1, [r0, #0x0]
	mov r0, #0x5e
	add r1, sp, #0x0
	bl FUN_020311D0
	ldr r0, _02050964 ; =FUN_02050A14
	mov r1, #0x0
	bl FUN_02050094
_0205095A:
	bl FUN_020508B8
	pop {r3, pc}
	.balign 4
_02050960: .word UNK_021C5A6C
_02050964: .word FUN_02050A14

	thumb_func_start FUN_02050968
FUN_02050968: ; 0x02050968
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	beq _02050986
	mov r0, #0xb
	bl FUN_0206B8AC
	ldr r1, _020509AC ; =UNK_021C5A6C
	ldr r2, [r1, #0x0]
	str r0, [r2, #0x44]
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	ldr r1, [r1, #0x44]
	bl FUN_0206BAD0
_02050986:
	cmp r5, #0x0
	beq _02050994
	ldr r0, _020509B0 ; =FUN_02050B8C
	mov r1, #0x3
	bl FUN_02050094
	pop {r3-r5, pc}
_02050994:
	mov r1, #0x3
	add r0, sp, #0x0
	strb r1, [r0, #0x0]
	mov r0, #0x5e
	add r1, sp, #0x0
	bl FUN_020311D0
	ldr r0, _020509B4 ; =FUN_02050930
	mov r1, #0x0
	bl FUN_02050094
	pop {r3-r5, pc}
	.balign 4
_020509AC: .word UNK_021C5A6C
_020509B0: .word FUN_02050B8C
_020509B4: .word FUN_02050930

	thumb_func_start FUN_020509B8
FUN_020509B8: ; 0x020509B8
	ldr r3, _020509C0 ; =FUN_02050094
	ldr r0, _020509C4 ; =FUN_02050930
	mov r1, #0x0
	bx r3
	.balign 4
_020509C0: .word FUN_02050094
_020509C4: .word FUN_02050930

	thumb_func_start FUN_020509C8
FUN_020509C8: ; 0x020509C8
	push {r3, lr}
	bl FUN_02031438
	cmp r0, #0x0
	bne _02050A06
	bl FUN_02031190
	bl FUN_0204F6B4
	cmp r0, #0x0
	bne _02050A06
	ldr r0, _02050A08 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _020509EE
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_020509EE:
	bl FUN_0204F7E4
	ldr r0, _02050A08 ; =UNK_021C5A6C
	ldr r1, _02050A0C ; =FUN_02050968
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x18]
	bl FUN_02051880
	ldr r0, _02050A10 ; =FUN_020509B8
	mov r1, #0x0
	bl FUN_02050094
_02050A06:
	pop {r3, pc}
	.balign 4
_02050A08: .word UNK_021C5A6C
_02050A0C: .word FUN_02050968
_02050A10: .word FUN_020509B8

	thumb_func_start FUN_02050A14
FUN_02050A14: ; 0x02050A14
	push {r3, lr}
	ldr r0, _02050A40 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	add r0, #0x43
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02050A38
	ldr r0, _02050A44 ; =FUN_020509C8
	mov r1, #0x5
	bl FUN_02050094
	mov r1, #0x0
	add r0, sp, #0x0
	strb r1, [r0, #0x0]
	mov r0, #0x5e
	add r1, sp, #0x0
	bl FUN_020311D0
_02050A38:
	bl FUN_020508B8
	pop {r3, pc}
	nop
_02050A40: .word UNK_021C5A6C
_02050A44: .word FUN_020509C8

	thumb_func_start FUN_02050A48
FUN_02050A48: ; 0x02050A48
	push {r4, lr}
	add r4, r2, #0x0
	bl FUN_02031190
	ldrb r1, [r4, #0x0]
	cmp r1, r0
	bne _02050A60
	ldr r0, _02050A64 ; =UNK_021C5A6C
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, #0x43
	strb r1, [r0, #0x0]
_02050A60:
	pop {r4, pc}
	nop
_02050A64: .word UNK_021C5A6C

	thumb_func_start FUN_02050A68
FUN_02050A68: ; 0x02050A68
	ldr r0, _02050A88 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02050A82
	ldr r1, [r0, #0x34]
	ldr r0, _02050A8C ; =FUN_02050A14
	cmp r1, r0
	beq _02050A7E
	ldr r0, _02050A90 ; =FUN_02050930
	cmp r1, r0
	bne _02050A82
_02050A7E:
	mov r0, #0x1
	bx lr
_02050A82:
	mov r0, #0x0
	bx lr
	nop
_02050A88: .word UNK_021C5A6C
_02050A8C: .word FUN_02050A14
_02050A90: .word FUN_02050930

	thumb_func_start FUN_02050A94
FUN_02050A94: ; 0x02050A94
	push {r4, lr}
	sub sp, #0x8
	ldr r0, _02050B00 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050AAA
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	add sp, #0x8
	pop {r4, pc}
_02050AAA:
	mov r4, #0x5
	bl FUN_02033534
	cmp r0, #0x2
	beq _02050AC0
	cmp r0, #0x4
	beq _02050ABC
	cmp r0, #0x5
	bne _02050AC2
_02050ABC:
	mov r4, #0xf
	b _02050AC2
_02050AC0:
	mov r4, #0x7
_02050AC2:
	add r0, sp, #0x0
	bl FUN_02033578
	ldr r0, _02050B00 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x44]
	ldr r0, [r0, #0x18]
	cmp r1, #0x0
	bne _02050ADE
	add r1, sp, #0x0
	add r2, r4, #0x0
	bl FUN_0204726C
	b _02050AF6
_02050ADE:
	add r2, r4, #0x0
	bl FUN_020472B0
	ldr r0, _02050B00 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x44]
	bl FUN_02016A18
	ldr r0, _02050B00 ; =UNK_021C5A6C
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x44]
_02050AF6:
	bl FUN_0204FC10
	add sp, #0x8
	pop {r4, pc}
	nop
_02050B00: .word UNK_021C5A6C

	thumb_func_start FUN_02050B04
FUN_02050B04: ; 0x02050B04
	push {r3, lr}
	bl FUN_0202FA48
	cmp r0, #0x0
	beq _02050B3E
	ldr r0, _02050B40 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050B1C
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
_02050B1C:
	ldr r0, _02050B40 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x3c]
	cmp r0, #0x5a
	bne _02050B2C
	mov r0, #0x4
	bl FUN_02031588
_02050B2C:
	mov r0, #0x4
	bl FUN_020315D8
	cmp r0, #0x0
	beq _02050B3E
	ldr r0, _02050B44 ; =FUN_02050A94
	mov r1, #0x0
	bl FUN_02050094
_02050B3E:
	pop {r3, pc}
	.balign 4
_02050B40: .word UNK_021C5A6C
_02050B44: .word FUN_02050A94

	thumb_func_start FUN_02050B48
FUN_02050B48: ; 0x02050B48
	push {r3, lr}
	ldr r0, _02050B68 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050B5A
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_02050B5A:
	bl FUN_0202FA10
	ldr r0, _02050B6C ; =FUN_02050B04
	mov r1, #0x78
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_02050B68: .word UNK_021C5A6C
_02050B6C: .word FUN_02050B04

	thumb_func_start FUN_02050B70
FUN_02050B70: ; 0x02050B70
	push {r3, lr}
	mov r0, #0x3
	bl FUN_020315D8
	cmp r0, #0x0
	beq _02050B84
	ldr r0, _02050B88 ; =FUN_02050B48
	mov r1, #0x2
	bl FUN_02050094
_02050B84:
	pop {r3, pc}
	nop
_02050B88: .word FUN_02050B48

	thumb_func_start FUN_02050B8C
FUN_02050B8C: ; 0x02050B8C
	push {r3, lr}
	ldr r0, _02050BB4 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050B9E
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_02050B9E:
	mov r0, #0x0
	bl FUN_0204CCE0
	mov r0, #0x3
	bl FUN_02031588
	ldr r0, _02050BB8 ; =FUN_02050B70
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_02050BB4: .word UNK_021C5A6C
_02050BB8: .word FUN_02050B70

	thumb_func_start FUN_02050BBC
FUN_02050BBC: ; 0x02050BBC
	push {r3, lr}
	bl FUN_020319F4
	ldr r0, _02050BCC ; =FUN_02050BD0
	mov r1, #0x2
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_02050BCC: .word FUN_02050BD0

	thumb_func_start FUN_02050BD0
FUN_02050BD0: ; 0x02050BD0
	push {r3, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _02050BE2
	ldr r0, _02050BE4 ; =FUN_020506A8
	mov r1, #0xa
	bl FUN_02050094
_02050BE2:
	pop {r3, pc}
	.balign 4
_02050BE4: .word FUN_020506A8

	thumb_func_start FUN_02050BE8
FUN_02050BE8: ; 0x02050BE8
	ldr r1, _02050BF4 ; =UNK_021C5A6C
	mov r2, #0x1
	ldr r1, [r1, #0x0]
	add r0, r1, r0
	strb r2, [r0, #0x10]
	bx lr
	.balign 4
_02050BF4: .word UNK_021C5A6C

	thumb_func_start FUN_02050BF8
FUN_02050BF8: ; 0x02050BF8
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x4
	blt _02050C04
	bl ErrorHandling
_02050C04:
	ldr r0, _02050C10 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x2
	ldr r0, [r1, r0]
	pop {r4, pc}
	nop
_02050C10: .word UNK_021C5A6C

	thumb_func_start FUN_02050C14
FUN_02050C14: ; 0x02050C14
	push {r4, lr}
	bl FUN_02031190
	add r4, r0, #0x0
	mov r0, #0x5f
	bl FUN_020315D8
	cmp r0, #0x0
	beq _02050C3E
	ldr r1, _02050C40 ; =UNK_021C5A6C
	mov r0, #0x58
	ldr r2, [r1, #0x0]
	lsl r1, r4, #0x2
	ldr r1, [r2, r1]
	ldr r2, _02050C44 ; =0x0000066C
	bl FUN_02030A78
	ldr r0, _02050C48 ; =FUN_02050C4C
	mov r1, #0x0
	bl FUN_02050094
_02050C3E:
	pop {r4, pc}
	.balign 4
_02050C40: .word UNK_021C5A6C
_02050C44: .word 0x0000066C
_02050C48: .word FUN_02050C4C

	thumb_func_start FUN_02050C4C
FUN_02050C4C: ; 0x02050C4C
	push {r3-r5, lr}
	mov r4, #0x0
	bl FUN_02030F20
	cmp r0, #0x0
	ble _02050C6E
	ldr r5, _02050C80 ; =UNK_021C5A6C
_02050C5A:
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	ldrb r0, [r0, #0x10]
	cmp r0, #0x0
	beq _02050C7C
	add r4, r4, #0x1
	bl FUN_02030F20
	cmp r4, r0
	blt _02050C5A
_02050C6E:
	mov r0, #0x61
	bl FUN_02031588
	ldr r0, _02050C84 ; =FUN_02050CF4
	mov r1, #0x0
	bl FUN_02050094
_02050C7C:
	pop {r3-r5, pc}
	nop
_02050C80: .word UNK_021C5A6C
_02050C84: .word FUN_02050CF4

	thumb_func_start FUN_02050C88
FUN_02050C88: ; 0x02050C88
	push {r3, lr}
	bl FUN_0202FA48
	cmp r0, #0x0
	bne _02050CC2
	ldr r0, _02050CC4 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050CA0
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
_02050CA0:
	ldr r0, _02050CC4 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x3c]
	cmp r0, #0x5a
	bne _02050CB0
	mov r0, #0x5
	bl FUN_02031588
_02050CB0:
	mov r0, #0x5
	bl FUN_020315D8
	cmp r0, #0x0
	beq _02050CC2
	ldr r0, _02050CC8 ; =FUN_02050D10
	mov r1, #0x0
	bl FUN_02050094
_02050CC2:
	pop {r3, pc}
	.balign 4
_02050CC4: .word UNK_021C5A6C
_02050CC8: .word FUN_02050D10

	thumb_func_start FUN_02050CCC
FUN_02050CCC: ; 0x02050CCC
	push {r3, lr}
	ldr r0, _02050CEC ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050CDE
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_02050CDE:
	bl FUN_0202FA1C
	ldr r0, _02050CF0 ; =FUN_02050C88
	mov r1, #0x78
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_02050CEC: .word UNK_021C5A6C
_02050CF0: .word FUN_02050C88

	thumb_func_start FUN_02050CF4
FUN_02050CF4: ; 0x02050CF4
	push {r3, lr}
	mov r0, #0x61
	bl FUN_020315D8
	cmp r0, #0x0
	beq _02050D08
	ldr r0, _02050D0C ; =FUN_02050CCC
	mov r1, #0x2
	bl FUN_02050094
_02050D08:
	pop {r3, pc}
	nop
_02050D0C: .word FUN_02050CCC

	thumb_func_start FUN_02050D10
FUN_02050D10: ; 0x02050D10
	push {r3, lr}
	ldr r0, _02050D48 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050D22
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_02050D22:
	mov r0, #0x62
	bl FUN_02031588
	ldr r0, _02050D48 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	add r0, #0x42
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02050D3E
	ldr r0, _02050D4C ; =FUN_020506C8
	mov r1, #0x1e
	bl FUN_02050094
	pop {r3, pc}
_02050D3E:
	ldr r0, _02050D50 ; =FUN_020507F8
	mov r1, #0x1e
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_02050D48: .word UNK_021C5A6C
_02050D4C: .word FUN_020506C8
_02050D50: .word FUN_020507F8

	thumb_func_start FUN_02050D54
FUN_02050D54: ; 0x02050D54
	push {r3, lr}
	ldr r0, _02050D84 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050D66
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_02050D66:
	bl MOD18_0223E1A4
	bl FUN_02031860
	mov r0, #0x21
	bl FUN_020168D0
	ldr r0, _02050D84 ; =UNK_021C5A6C
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x41
	strb r1, [r0, #0x0]
	bl FUN_0204FC10
	pop {r3, pc}
	.balign 4
_02050D84: .word UNK_021C5A6C

	thumb_func_start FUN_02050D88
FUN_02050D88: ; 0x02050D88
	push {r3, lr}
	mov r0, #0x5b
	bl FUN_020315D8
	cmp r0, #0x0
	beq _02050DAA
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_020334E8
	mov r0, #0x1
	bl FUN_0204CCE0
	ldr r0, _02050DAC ; =FUN_02050DC8
	mov r1, #0x5
	bl FUN_02050094
_02050DAA:
	pop {r3, pc}
	.balign 4
_02050DAC: .word FUN_02050DC8

	thumb_func_start FUN_02050DB0
FUN_02050DB0: ; 0x02050DB0
	push {r3, lr}
	mov r0, #0x1
	bl FUN_0204CCE0
	ldr r0, _02050DC4 ; =FUN_02050DC8
	mov r1, #0x5
	bl FUN_02050094
	pop {r3, pc}
	nop
_02050DC4: .word FUN_02050DC8

	thumb_func_start FUN_02050DC8
FUN_02050DC8: ; 0x02050DC8
	push {r3, lr}
	ldr r0, _02050DE8 ; =UNK_021C5A6C
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3c]
	cmp r0, #0x0
	beq _02050DDA
	sub r0, r0, #0x1
	strh r0, [r1, #0x3c]
	pop {r3, pc}
_02050DDA:
	bl FUN_02031A08
	ldr r0, _02050DEC ; =FUN_0204FC10
	mov r1, #0x0
	bl FUN_02050094
	pop {r3, pc}
	.balign 4
_02050DE8: .word UNK_021C5A6C
_02050DEC: .word FUN_0204FC10

	thumb_func_start FUN_02050DF0
FUN_02050DF0: ; 0x02050DF0
	push {r3, lr}
	ldr r1, _02050E0C ; =UNK_021C5A6C
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _02050E02
	add r1, #0x41
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02050E06
_02050E02:
	mov r0, #0x0
	pop {r3, pc}
_02050E06:
	bl MOD18_0223E2AC
	pop {r3, pc}
	.balign 4
_02050E0C: .word UNK_021C5A6C

	thumb_func_start FUN_02050E10
FUN_02050E10: ; 0x02050E10
	push {r3, lr}
	ldr r0, _02050E28 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02050E26
	add r0, #0x41
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02050E26
	bl MOD18_0223E118
_02050E26:
	pop {r3, pc}
	.balign 4
_02050E28: .word UNK_021C5A6C

	thumb_func_start FUN_02050E2C
FUN_02050E2C: ; 0x02050E2C
	push {r3, lr}
	ldr r0, _02050E44 ; =UNK_021C5A6C
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02050E42
	add r0, #0x41
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02050E42
	bl MOD18_0223E154
_02050E42:
	pop {r3, pc}
	.balign 4
_02050E44: .word UNK_021C5A6C
