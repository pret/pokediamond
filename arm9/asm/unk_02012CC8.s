    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_021CED64

	.section .rodata

	.global UNK_020ED4E4
UNK_020ED4E4: ; 0x020ED4E4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020ED4F0
UNK_020ED4F0: ; 0x020ED4F0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020ED4FC
UNK_020ED4FC: ; 0x020ED4FC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00

	.global UNK_020ED508
UNK_020ED508: ; 0x020ED508
	.word FUN_02012ECC
	.word FUN_02012EF8
	.word FUN_02012F24
	.word FUN_02012F50
	.word FUN_02012F7C
	.word FUN_02012FA8
	.word FUN_02012FD4
	.word FUN_02013000
	.word FUN_0201302C
	.word FUN_02013058
	.word FUN_02013084
	.word FUN_020130B0
	.word FUN_020130DC
	.word FUN_02013108
	.word FUN_02013134
	.word FUN_02013160

	.global UNK_020ED548
UNK_020ED548: ; 0x020ED548
	.byte 0x1F, 0x01, 0xFF, 0xFF

	.section .bss

	.global UNK_021C4850
UNK_021C4850: ; 0x021C4850
	.space 0x8

	.global UNK_021C4858
UNK_021C4858: ; 0x021C4858
	.space 0x40

	.text

	thumb_func_start FUN_02012CC8
FUN_02012CC8: ; 0x02012CC8
	mov r1, #0x0
	ldr r2, _02012CD8 ; =UNK_021C4858
	add r0, r1, #0x0
_02012CCE:
	add r1, r1, #0x1
	stmia r2!, {r0}
	cmp r1, #0x10
	blt _02012CCE
	bx lr
	.balign 4
_02012CD8: .word UNK_021C4858

	thumb_func_start FUN_02012CDC
FUN_02012CDC: ; 0x02012CDC
	push {r3-r7, lr}
	sub sp, #0x10
	str r1, [sp, #0x8]
	ldr r1, _02012DD0 ; =UNK_021C4858
	add r7, r0, #0x0
	add r6, r2, #0x0
	str r3, [sp, #0xc]
	mov r5, #0x0
_02012CEC:
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	beq _02012CFA
	add r5, r5, #0x1
	add r1, r1, #0x4
	cmp r5, #0x10
	blt _02012CEC
_02012CFA:
	cmp r5, #0x10
	blt _02012D04
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_02012D04:
	ldr r0, [sp, #0x2c]
	mov r1, #0xdc
	bl AllocFromHeap
	add r4, r0, #0x0
	bne _02012D14
	bl ErrorHandling
_02012D14:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0xdc
	bl memset
	add r2, r4, #0x0
	ldr r0, [sp, #0x8]
	str r7, [r4, #0x18]
	ldr r3, _02012DD4 ; =UNK_020ED4FC
	str r0, [r4, #0x1c]
	ldmia r3!, {r0-r1}
	add r2, #0x34
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	ldr r3, _02012DD8 ; =UNK_020ED4E4
	str r0, [r2, #0x0]
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x40
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	ldr r3, _02012DDC ; =UNK_020ED4F0
	str r0, [r2, #0x0]
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x4c
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	mov r1, #0x0
	str r0, [r2, #0x0]
	ldr r2, [sp, #0xc]
	add r0, r6, #0x0
	bl memset
	ldr r0, [sp, #0xc]
	str r6, [r4, #0xc]
	str r6, [r4, #0x10]
	add r0, r6, r0
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	add r0, #0xda
	strb r5, [r0, #0x0]
	ldr r0, _02012DD0 ; =UNK_021C4858
	lsl r5, r5, #0x2
	str r4, [r0, r5]
	ldr r0, [sp, #0x28]
	cmp r0, #0x1
	bne _02012DA8
	ldr r0, [sp, #0x2c]
	bl FUN_0201EB64
	str r0, [r4, #0x20]
	mov r3, #0x0
	str r3, [r4, #0x24]
	str r3, [r4, #0x28]
	mov r0, #0x2
	str r3, [r4, #0x2c]
	lsl r0, r0, #0xc
	strh r0, [r4, #0x30]
	str r3, [sp, #0x0]
	ldr r0, [r4, #0x20]
	ldr r1, _02012DD4 ; =UNK_020ED4FC
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x30]
	ldr r0, _02012DDC ; =UNK_020ED4F0
	bl FUN_0201ED5C
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0xdb
	strb r1, [r0, #0x0]
	ldr r0, [r4, #0x20]
	bl FUN_0201EB8C
_02012DA8:
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x3f
	str r0, [sp, #0x4]
	ldr r0, _02012DE0 ; =UNK_020ED508
	mov r1, #0x14
	ldr r0, [r0, r5]
	mov r2, #0xc8
	mov r3, #0x5
	bl FUN_0208B4A0
	str r0, [r4, #0x0]
	ldr r1, _02012DD8 ; =UNK_020ED4E4
	add r0, r4, #0x0
	bl FUN_020133FC
	add r0, r4, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_02012DD0: .word UNK_021C4858
_02012DD4: .word UNK_020ED4FC
_02012DD8: .word UNK_020ED4E4
_02012DDC: .word UNK_020ED4F0
_02012DE0: .word UNK_020ED508

	thumb_func_start FUN_02012DE4
FUN_02012DE4: ; 0x02012DE4
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_020133D0
	add r0, r5, #0x0
	add r0, #0xd8
	ldrb r1, [r0, #0x0]
	mov r0, #0x1
	tst r0, r1
	beq _02012E02
	add r0, r5, #0x0
	add r0, #0x58
	bl FUN_020AE8CC
	b _02012E22
_02012E02:
	mov r0, #0x2
	tst r0, r1
	beq _02012E22
	mov r6, #0x0
	add r4, r5, #0x0
	add r7, r6, #0x0
_02012E0E:
	ldr r0, [r4, #0x58]
	cmp r0, #0x0
	beq _02012E1A
	bl FUN_020AF894
	str r7, [r4, #0x58]
_02012E1A:
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, #0x10
	blt _02012E0E
_02012E22:
	add r0, r5, #0x0
	add r0, #0xd8
	ldrb r1, [r0, #0x0]
	mov r0, #0x4
	tst r0, r1
	beq _02012E38
	add r0, r5, #0x0
	add r0, #0x98
	bl FUN_020AEC7C
	b _02012E60
_02012E38:
	mov r0, #0x8
	tst r0, r1
	beq _02012E60
	mov r6, #0x0
	add r4, r5, #0x0
	add r7, r6, #0x0
_02012E44:
	add r0, r4, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02012E58
	bl FUN_020AFA80
	add r0, r4, #0x0
	add r0, #0x98
	str r7, [r0, #0x0]
_02012E58:
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, #0x10
	blt _02012E44
_02012E60:
	add r0, r5, #0x0
	mov r1, #0x0
	add r0, #0xd8
	strb r1, [r0, #0x0]
	str r1, [r5, #0x8]
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	beq _02012E78
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r5, #0x4]
_02012E78:
	ldr r2, _02012EA8 ; =UNK_021C4858
	mov r1, #0x0
_02012E7C:
	ldr r0, [r2, #0x0]
	cmp r0, r5
	bne _02012E8C
	ldr r0, _02012EA8 ; =UNK_021C4858
	mov r2, #0x0
	lsl r1, r1, #0x2
	str r2, [r0, r1]
	b _02012E94
_02012E8C:
	add r1, r1, #0x1
	add r2, r2, #0x4
	cmp r1, #0x10
	blt _02012E7C
_02012E94:
	ldr r0, [r5, #0x20]
	cmp r0, #0x0
	beq _02012E9E
	bl FUN_0201EB70
_02012E9E:
	add r0, r5, #0x0
	bl FreeToHeap
	pop {r3-r7, pc}
	nop
_02012EA8: .word UNK_021C4858

	thumb_func_start FUN_02012EAC
FUN_02012EAC: ; 0x02012EAC
	push {r3-r5, lr}
	ldr r5, _02012EC8 ; =UNK_021C4858
	mov r4, #0x0
_02012EB2:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _02012EBC
	bl FUN_02012DE4
_02012EBC:
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x10
	blt _02012EB2
	pop {r3-r5, pc}
	nop
_02012EC8: .word UNK_021C4858

	thumb_func_start FUN_02012ECC
FUN_02012ECC: ; 0x02012ECC
	push {r4, lr}
	ldr r1, _02012EF4 ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x8]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02012EE4
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02012EE4:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02012EF0
	bl ErrorHandling
_02012EF0:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02012EF4: .word UNK_021C4850

	thumb_func_start FUN_02012EF8
FUN_02012EF8: ; 0x02012EF8
	push {r4, lr}
	ldr r1, _02012F20 ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0xc]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02012F10
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02012F10:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02012F1C
	bl ErrorHandling
_02012F1C:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02012F20: .word UNK_021C4850

	thumb_func_start FUN_02012F24
FUN_02012F24: ; 0x02012F24
	push {r4, lr}
	ldr r1, _02012F4C ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x10]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02012F3C
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02012F3C:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02012F48
	bl ErrorHandling
_02012F48:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02012F4C: .word UNK_021C4850

	thumb_func_start FUN_02012F50
FUN_02012F50: ; 0x02012F50
	push {r4, lr}
	ldr r1, _02012F78 ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x14]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02012F68
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02012F68:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02012F74
	bl ErrorHandling
_02012F74:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02012F78: .word UNK_021C4850

	thumb_func_start FUN_02012F7C
FUN_02012F7C: ; 0x02012F7C
	push {r4, lr}
	ldr r1, _02012FA4 ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x18]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02012F94
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02012F94:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02012FA0
	bl ErrorHandling
_02012FA0:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02012FA4: .word UNK_021C4850

	thumb_func_start FUN_02012FA8
FUN_02012FA8: ; 0x02012FA8
	push {r4, lr}
	ldr r1, _02012FD0 ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x1c]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02012FC0
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02012FC0:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02012FCC
	bl ErrorHandling
_02012FCC:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02012FD0: .word UNK_021C4850

	thumb_func_start FUN_02012FD4
FUN_02012FD4: ; 0x02012FD4
	push {r4, lr}
	ldr r1, _02012FFC ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x20]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02012FEC
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02012FEC:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02012FF8
	bl ErrorHandling
_02012FF8:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02012FFC: .word UNK_021C4850

	thumb_func_start FUN_02013000
FUN_02013000: ; 0x02013000
	push {r4, lr}
	ldr r1, _02013028 ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x24]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02013018
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02013018:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02013024
	bl ErrorHandling
_02013024:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02013028: .word UNK_021C4850

	thumb_func_start FUN_0201302C
FUN_0201302C: ; 0x0201302C
	push {r4, lr}
	ldr r1, _02013054 ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x28]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02013044
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02013044:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02013050
	bl ErrorHandling
_02013050:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02013054: .word UNK_021C4850

	thumb_func_start FUN_02013058
FUN_02013058: ; 0x02013058
	push {r4, lr}
	ldr r1, _02013080 ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x2c]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02013070
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02013070:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _0201307C
	bl ErrorHandling
_0201307C:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02013080: .word UNK_021C4850

	thumb_func_start FUN_02013084
FUN_02013084: ; 0x02013084
	push {r4, lr}
	ldr r1, _020130AC ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x30]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _0201309C
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_0201309C:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _020130A8
	bl ErrorHandling
_020130A8:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_020130AC: .word UNK_021C4850

	thumb_func_start FUN_020130B0
FUN_020130B0: ; 0x020130B0
	push {r4, lr}
	ldr r1, _020130D8 ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x34]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _020130C8
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_020130C8:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _020130D4
	bl ErrorHandling
_020130D4:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_020130D8: .word UNK_021C4850

	thumb_func_start FUN_020130DC
FUN_020130DC: ; 0x020130DC
	push {r4, lr}
	ldr r1, _02013104 ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x38]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _020130F4
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_020130F4:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02013100
	bl ErrorHandling
_02013100:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02013104: .word UNK_021C4850

	thumb_func_start FUN_02013108
FUN_02013108: ; 0x02013108
	push {r4, lr}
	ldr r1, _02013130 ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x3c]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02013120
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02013120:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _0201312C
	bl ErrorHandling
_0201312C:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02013130: .word UNK_021C4850

	thumb_func_start FUN_02013134
FUN_02013134: ; 0x02013134
	push {r4, lr}
	ldr r1, _0201315C ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x40]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _0201314C
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_0201314C:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02013158
	bl ErrorHandling
_02013158:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_0201315C: .word UNK_021C4850

	thumb_func_start FUN_02013160
FUN_02013160: ; 0x02013160
	push {r4, lr}
	ldr r1, _02013188 ; =UNK_021C4850
	mov r2, #0x3
	ldr r1, [r1, #0x44]
	ldr r4, [r1, #0x10]
	add r0, r4, r0
	add r3, r0, #0x0
	and r3, r2
	beq _02013178
	mov r2, #0x4
	sub r2, r2, r3
	add r0, r0, r2
_02013178:
	str r0, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r0, r1
	blo _02013184
	bl ErrorHandling
_02013184:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_02013188: .word UNK_021C4850

	thumb_func_start FUN_0201318C
FUN_0201318C: ; 0x0201318C
	ldr r3, _02013190 ; =AllocAndReadWholeNarcMemberByIdPair
	bx r3
	.balign 4
_02013190: .word AllocAndReadWholeNarcMemberByIdPair

	thumb_func_start FUN_02013194
FUN_02013194: ; 0x02013194
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r6, r1, #0x0
	add r4, r2, #0x0
	add r7, r3, #0x0
	cmp r0, #0x0
	bne _020131A8
	bl ErrorHandling
_020131A8:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	beq _020131B2
	bl ErrorHandling
_020131B2:
	add r0, r5, #0x0
	add r0, #0xd8
	strb r4, [r0, #0x0]
	mov r0, #0x1
	tst r0, r4
	beq _020131C8
	add r0, r5, #0x0
	add r0, #0x58
	bl FUN_020AE918
	b _020131DE
_020131C8:
	mov r0, #0x2
	tst r0, r4
	beq _020131DE
	mov r1, #0x0
	add r2, r5, #0x0
	add r0, r1, #0x0
_020131D4:
	add r1, r1, #0x1
	str r0, [r2, #0x58]
	add r2, r2, #0x4
	cmp r1, #0x10
	blt _020131D4
_020131DE:
	mov r0, #0x4
	tst r0, r4
	beq _020131EE
	add r0, r5, #0x0
	add r0, #0x98
	bl FUN_020AEC98
	b _02013208
_020131EE:
	mov r0, #0x8
	tst r0, r4
	beq _02013208
	mov r2, #0x0
	add r3, r5, #0x0
	add r1, r2, #0x0
_020131FA:
	add r0, r3, #0x0
	add r0, #0x98
	add r2, r2, #0x1
	add r3, r3, #0x4
	str r1, [r0, #0x0]
	cmp r2, #0x10
	blt _020131FA
_02013208:
	str r6, [r5, #0x4]
	cmp r7, #0x1
	bne _02013216
	add r0, r5, #0x0
	bl FUN_02013228
	pop {r3-r7, pc}
_02013216:
	ldr r0, _02013224 ; =FUN_02013268
	add r1, r5, #0x0
	mov r2, #0x5
	bl FUN_0200CA98
	pop {r3-r7, pc}
	nop
_02013224: .word FUN_02013268

	thumb_func_start FUN_02013228
FUN_02013228: ; 0x02013228
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x4]
	bl FUN_0208B128
	ldr r0, _02013264 ; =UNK_021C4850
	str r4, [r0, #0x0]
	ldr r1, [r4, #0x18]
	ldr r0, [r4, #0x0]
	cmp r1, #0x0
	bne _02013246
	bl FUN_0208AF94
	b _0201324A
_02013246:
	bl FUN_0208B05C
_0201324A:
	ldr r1, [r4, #0x1c]
	ldr r0, [r4, #0x0]
	cmp r1, #0x0
	bne _02013258
	bl FUN_0208AF80
	b _0201325C
_02013258:
	bl FUN_0208AFA8
_0201325C:
	ldr r0, _02013264 ; =UNK_021C4850
	mov r1, #0x0
	str r1, [r0, #0x0]
	pop {r4, pc}
	.balign 4
_02013264: .word UNK_021C4850

	thumb_func_start FUN_02013268
FUN_02013268: ; 0x02013268
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02013228
	add r0, r4, #0x0
	bl FUN_0200CAB4
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201327C
FUN_0201327C: ; 0x0201327C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02013286
	bl ErrorHandling
_02013286:
	ldr r0, _020132B8 ; =UNK_021C4850
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02013292
	bl ErrorHandling
_02013292:
	ldr r0, _020132B8 ; =UNK_021C4850
	mov r1, #0x0
	ldr r3, [r0, #0x0]
	add r2, r3, #0x0
_0201329A:
	ldr r0, [r2, #0x58]
	cmp r0, #0x0
	bne _020132A8
	lsl r0, r1, #0x2
	add r0, r3, r0
	str r4, [r0, #0x58]
	pop {r4, pc}
_020132A8:
	add r1, r1, #0x1
	add r2, r2, #0x4
	cmp r1, #0x10
	blt _0201329A
	bl ErrorHandling
	pop {r4, pc}
	nop
_020132B8: .word UNK_021C4850

	thumb_func_start FUN_020132BC
FUN_020132BC: ; 0x020132BC
	push {r4, lr}
	add r4, r0, #0x0
	bne _020132C6
	bl ErrorHandling
_020132C6:
	ldr r0, _020132FC ; =UNK_021C4850
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020132D2
	bl ErrorHandling
_020132D2:
	ldr r0, _020132FC ; =UNK_021C4850
	mov r1, #0x0
	ldr r3, [r0, #0x0]
	add r2, r3, #0x0
_020132DA:
	add r0, r2, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020132EE
	lsl r0, r1, #0x2
	add r0, r3, r0
	add r0, #0x98
	str r4, [r0, #0x0]
	pop {r4, pc}
_020132EE:
	add r1, r1, #0x1
	add r2, r2, #0x4
	cmp r1, #0x10
	blt _020132DA
	bl ErrorHandling
	pop {r4, pc}
	.balign 4
_020132FC: .word UNK_021C4850

	thumb_func_start FUN_02013300
FUN_02013300: ; 0x02013300
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x20]
	cmp r1, #0x0
	beq _0201331C
	add r0, #0xdb
	ldrb r0, [r0, #0x0]
	bl FUN_0201EE2C
	ldr r0, [r4, #0x20]
	bl FUN_0201EB8C
	bl FUN_0201EBA4
_0201331C:
	bl FUN_020B849C
	ldr r0, [r4, #0x0]
	ldr r1, _02013338 ; =UNK_021CED64
	bl FUN_0208AD80
	ldr r0, [r4, #0x20]
	cmp r0, #0x0
	beq _02013332
	bl FUN_0201EB98
_02013332:
	bl FUN_020B849C
	pop {r4, pc}
	.balign 4
_02013338: .word UNK_021CED64

	thumb_func_start FUN_0201333C
FUN_0201333C: ; 0x0201333C
	ldr r3, _02013344 ; =0x0208AE48
	ldr r0, [r0, #0x0]
	bx r3
	nop
_02013344: .word FUN_0208AE48

	thumb_func_start FUN_02013348
FUN_02013348: ; 0x02013348
	mov r0, #0x0
	ldr r3, _02013360 ; =UNK_021C4858
	add r2, r0, #0x0
_0201334E:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	beq _02013356
	add r0, r0, #0x1
_02013356:
	add r2, r2, #0x1
	add r3, r3, #0x4
	cmp r2, #0x10
	blt _0201334E
	bx lr
	.balign 4
_02013360: .word UNK_021C4858

	thumb_func_start FUN_02013364
FUN_02013364: ; 0x02013364
	push {r4-r6, lr}
	mov r4, #0x0
	ldr r5, _02013384 ; =UNK_021C4858
	add r6, r4, #0x0
_0201336C:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _02013378
	bl FUN_02013300
	add r4, r4, #0x1
_02013378:
	add r6, r6, #0x1
	add r5, r5, #0x4
	cmp r6, #0x10
	blt _0201336C
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02013384: .word UNK_021C4858

	thumb_func_start FUN_02013388
FUN_02013388: ; 0x02013388
	push {r4-r6, lr}
	mov r4, #0x0
	ldr r5, _020133A8 ; =UNK_021C4858
	add r6, r4, #0x0
_02013390:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0201339C
	bl FUN_0201333C
	add r4, r4, #0x1
_0201339C:
	add r6, r6, #0x1
	add r5, r5, #0x4
	cmp r6, #0x10
	blt _02013390
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_020133A8: .word UNK_021C4858

	thumb_func_start FUN_020133AC
FUN_020133AC: ; 0x020133AC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020133C4 ; =UNK_021C4850
	str r3, [r0, #0x4]
	ldr r0, [r4, #0x0]
	bl FUN_0208ACEC
	ldr r1, _020133C4 ; =UNK_021C4850
	mov r2, #0x0
	str r2, [r1, #0x4]
	str r0, [r4, #0x8]
	pop {r4, pc}
	.balign 4
_020133C4: .word UNK_021C4850

	thumb_func_start FUN_020133C8
FUN_020133C8: ; 0x020133C8
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x8]
	bx lr
	.balign 4

	thumb_func_start FUN_020133D0
FUN_020133D0: ; 0x020133D0
	ldr r3, _020133D8 ; =0x0208AC14
	ldr r0, [r0, #0x0]
	bx r3
	nop
_020133D8: .word FUN_0208AC14

	thumb_func_start FUN_020133DC
FUN_020133DC: ; 0x020133DC
	ldr r3, _020133E4 ; =0x0208AC58
	ldr r0, [r0, #0x0]
	bx r3
	nop
_020133E4: .word FUN_0208AC58

	thumb_func_start FUN_020133E8
FUN_020133E8: ; 0x020133E8
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start FUN_020133EC
FUN_020133EC: ; 0x020133EC
	add r2, r0, #0x0
	add r2, #0x40
	add r3, r1, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr

	thumb_func_start FUN_020133FC
FUN_020133FC: ; 0x020133FC
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r3, r4, #0x0
	add r2, r5, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x40
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldr r1, [r5, #0x20]
	add r0, r4, #0x0
	bl FUN_0201EC58
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201341C
FUN_0201341C: ; 0x0201341C
	ldr r0, _02013424 ; =UNK_021C4850
	ldr r0, [r0, #0x4]
	bx lr
	nop
_02013424: .word UNK_021C4850

	thumb_func_start FUN_02013428
FUN_02013428: ; 0x02013428
	ldr r2, _02013438 ; =UNK_020ED4E4
	add r3, r0, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr
	nop
_02013438: .word UNK_020ED4E4

	thumb_func_start FUN_0201343C
FUN_0201343C: ; 0x0201343C
	ldr r0, [r0, #0x20]
	bx lr

	thumb_func_start FUN_02013440
FUN_02013440: ; 0x02013440
	add r0, #0xdb
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02013448
FUN_02013448: ; 0x02013448
	add r0, #0xdb
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02013450
FUN_02013450: ; 0x02013450
	ldr r0, [r0, #0x20]
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x10]
	bx lr

	thumb_func_start FUN_02013458
FUN_02013458: ; 0x02013458
	push {r4-r7}
	ldr r0, [r0, #0x20]
	add r4, r1, #0x0
	ldrh r2, [r0, #0x1c]
	cmp r2, #0x0
	bne _0201346A
	mov r0, #0x0
	pop {r4-r7}
	bx lr
_0201346A:
	mov r1, #0x0
	cmp r2, #0x0
	ble _020134F4
	ldr r3, [r0, #0x18]
	ldr r7, _020134FC ; =0x020908DC
	ldr r0, _02013500 ; =0x020909A4
_02013476:
	cmp r3, #0x0
	beq _020134EC
	cmp r4, #0x5
	bhi _020134E6
	add r5, r4, r4
	add r5, pc
	ldrh r5, [r5, #0x6]
	lsl r5, r5, #0x10
	asr r5, r5, #0x10
	add pc, r5
_0201348A: ; jump table (using 16-bit offset)
	.short _02013496 - _0201348A - 2; case 0
	.short _020134A2 - _0201348A - 2; case 1
	.short _020134AE - _0201348A - 2; case 2
	.short _020134BC - _0201348A - 2; case 3
	.short _020134CA - _0201348A - 2; case 4
	.short _020134D8 - _0201348A - 2; case 5
_02013496:
	ldr r5, [r3, #0x0]
	cmp r5, r0
	bne _020134EC
	ldr r0, [r3, #0x4]
	pop {r4-r7}
	bx lr
_020134A2:
	ldr r5, [r3, #0x0]
	cmp r5, r7
	bne _020134EC
	ldr r0, [r3, #0x4]
	pop {r4-r7}
	bx lr
_020134AE:
	ldr r6, [r3, #0x0]
	ldr r5, _02013504 ; =0x02090858
	cmp r6, r5
	bne _020134EC
	ldr r0, [r3, #0x4]
	pop {r4-r7}
	bx lr
_020134BC:
	ldr r6, [r3, #0x0]
	ldr r5, _02013508 ; =0x02090780
	cmp r6, r5
	bne _020134EC
	ldr r0, [r3, #0x4]
	pop {r4-r7}
	bx lr
_020134CA:
	ldr r6, [r3, #0x0]
	ldr r5, _0201350C ; =0x02090664
	cmp r6, r5
	bne _020134EC
	ldr r0, [r3, #0x4]
	pop {r4-r7}
	bx lr
_020134D8:
	ldr r6, [r3, #0x0]
	ldr r5, _02013510 ; =0x020905D0
	cmp r6, r5
	bne _020134EC
	ldr r0, [r3, #0x4]
	pop {r4-r7}
	bx lr
_020134E6:
	mov r0, #0x0
	pop {r4-r7}
	bx lr
_020134EC:
	add r1, r1, #0x1
	add r3, #0x8
	cmp r1, r2
	blt _02013476
_020134F4:
	mov r0, #0x0
	pop {r4-r7}
	bx lr
	nop
_020134FC: .word FUN_020908DC
_02013500: .word FUN_020909A4
_02013504: .word FUN_02090858
_02013508: .word FUN_02090780
_0201350C: .word FUN_02090664
_02013510: .word FUN_020905D0

	thumb_func_start FUN_02013514
FUN_02013514: ; 0x02013514
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x0
	bl FUN_02013458
	cmp r0, #0x0
	beq _0201352E
	ldrh r1, [r4, #0x0]
	strh r1, [r0, #0x0]
	ldrh r1, [r4, #0x2]
	strh r1, [r0, #0x2]
	ldrh r1, [r4, #0x4]
	strh r1, [r0, #0x4]
_0201352E:
	pop {r4, pc}

	thumb_func_start FUN_02013530
FUN_02013530: ; 0x02013530
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x2
	bl FUN_02013458
	add r2, r0, #0x0
	beq _02013546
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r2, #0x0]
_02013546:
	pop {r4, pc}

	thumb_func_start FUN_02013548
FUN_02013548: ; 0x02013548
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	mov r1, #0x2
	bl FUN_02013458
	add r2, r0, #0x0
	bne _0201356E
	add r2, sp, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	str r0, [r2, #0x4]
	str r0, [r2, #0x8]
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r2, #0x0]
	add sp, #0xc
	str r0, [r4, #0x0]
	pop {r3-r4, pc}
_0201356E:
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r4, #0x0]
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0201357C
FUN_0201357C: ; 0x0201357C
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x2
	bl FUN_02013458
	cmp r0, #0x0
	beq _02013590
	mov r1, #0x0
	ldrsh r1, [r4, r1]
	strh r1, [r0, #0xc]
_02013590:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02013594
FUN_02013594: ; 0x02013594
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x2
	bl FUN_02013458
	cmp r0, #0x0
	bne _020135A8
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4, pc}
_020135A8:
	mov r1, #0xc
	ldrsh r0, [r0, r1]
	strh r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_020135B0
FUN_020135B0: ; 0x020135B0
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x3
	bl FUN_02013458
	cmp r0, #0x0
	beq _020135C2
	ldrh r1, [r4, #0x0]
	strh r1, [r0, #0x0]
_020135C2:
	pop {r4, pc}

	thumb_func_start FUN_020135C4
FUN_020135C4: ; 0x020135C4
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x3
	bl FUN_02013458
	cmp r0, #0x0
	bne _020135D8
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4, pc}
_020135D8:
	ldrh r0, [r0, #0x0]
	strh r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020135E0
FUN_020135E0: ; 0x020135E0
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x3
	bl FUN_02013458
	cmp r0, #0x0
	beq _020135F2
	ldrh r1, [r4, #0x0]
	strh r1, [r0, #0x2]
_020135F2:
	pop {r4, pc}

	thumb_func_start FUN_020135F4
FUN_020135F4: ; 0x020135F4
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x3
	bl FUN_02013458
	cmp r0, #0x0
	bne _02013608
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4, pc}
_02013608:
	ldrh r0, [r0, #0x2]
	strh r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02013610
FUN_02013610: ; 0x02013610
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x5
	bl FUN_02013458
	add r2, r0, #0x0
	beq _02013626
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r2, #0x0]
_02013626:
	pop {r4, pc}

	thumb_func_start FUN_02013628
FUN_02013628: ; 0x02013628
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	mov r1, #0x5
	bl FUN_02013458
	add r2, r0, #0x0
	bne _0201364E
	add r2, sp, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	str r0, [r2, #0x4]
	str r0, [r2, #0x8]
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r2, #0x0]
	add sp, #0xc
	str r0, [r4, #0x0]
	pop {r3-r4, pc}
_0201364E:
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r4, #0x0]
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0201365C
FUN_0201365C: ; 0x0201365C
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x5
	bl FUN_02013458
	cmp r0, #0x0
	beq _02013670
	mov r1, #0x0
	ldrsh r1, [r4, r1]
	strh r1, [r0, #0xc]
_02013670:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02013674
FUN_02013674: ; 0x02013674
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x5
	bl FUN_02013458
	cmp r0, #0x0
	bne _02013688
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r4, pc}
_02013688:
	mov r1, #0xc
	ldrsh r0, [r0, r1]
	strh r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02013690
FUN_02013690: ; 0x02013690
	push {r3-r5, lr}
	mov r1, #0x8
	add r5, r0, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	beq _020136B2
	ldr r0, _020136B8 ; =0x0001020F
	add r1, r5, #0x0
	str r0, [r4, #0x0]
	mov r0, #0x4
	bl String_ctor
	ldr r1, _020136BC ; =UNK_020ED548
	str r0, [r4, #0x4]
	bl CopyU16ArrayToString
_020136B2:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	nop
_020136B8: .word 0x0001020F
_020136BC: .word UNK_020ED548

	thumb_func_start DestroyListMenuCursorObj
DestroyListMenuCursorObj: ; 0x020136C0
	push {r4, lr}
	add r4, r0, #0x0
	bne _020136CA
	bl ErrorHandling
_020136CA:
	cmp r4, #0x0
	beq _020136DE
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _020136D8
	bl String_dtor
_020136D8:
	add r0, r4, #0x0
	bl FreeToHeap
_020136DE:
	pop {r4, pc}

	thumb_func_start CreateListMenuCursorObj
CreateListMenuCursorObj: ; 0x020136E0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020136EE
	bl ErrorHandling
_020136EE:
	cmp r5, #0x0
	beq _020136F4
	str r4, [r5, #0x0]
_020136F4:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ListMenuUpdateCursorObj
ListMenuUpdateCursorObj: ; 0x020136F8
	push {r4-r6, lr}
	sub sp, #0x10
	add r6, r0, #0x0
	str r3, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, [r6, #0x0]
	add r5, r1, #0x0
	str r0, [sp, #0x8]
	mov r1, #0x0
	add r4, r2, #0x0
	str r1, [sp, #0xc]
	ldr r2, [r6, #0x4]
	add r0, r5, #0x0
	add r3, r4, #0x0
	bl AddTextPrinterParameterized2
	add r0, r5, #0x0
	bl FUN_02019548
	add sp, #0x10
	pop {r4-r6, pc}
