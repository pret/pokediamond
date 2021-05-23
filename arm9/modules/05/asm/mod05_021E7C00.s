	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021E7C00
MOD05_021E7C00: ; 0x021E7C00
	push {r4, lr}
	mov r1, #0x46
	lsl r1, r1, #6
	bl AllocFromHeap
	add r4, r0, #0
	bl MOD05_021E7C1C
	add r0, r4, #0
	pop {r4, pc}

	thumb_func_start MOD05_021E7C14
MOD05_021E7C14: ; 0x021E7C14
	ldr r3, _021E7C18 ; =FreeToHeap
	bx r3
	.balign 4, 0
_021E7C18: .word FreeToHeap

	thumb_func_start MOD05_021E7C1C
MOD05_021E7C1C: ; 0x021E7C1C
	push {r3, r4, r5, r6, r7}
	sub sp, #0xc
	mov r4, #0
	mov ip, r0
	add r7, sp, #0
	add r3, r4, #0
_021E7C28:
	str r3, [r7]
	str r3, [r7, #4]
	mov r0, #0x8c
	add r1, r4, #0
	mul r1, r0
	mov r0, ip
	add r2, r0, r1
	add r5, r2, #0
	str r3, [r7, #8]
	mov r0, ip
	str r3, [r0, r1]
	str r3, [r2, #4]
	str r3, [r2, #8]
	str r3, [r2, #0xc]
	add r6, r7, #0
	ldmia r6!, {r0, r1}
	add r5, #0x68
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	add r6, r7, #0
	str r0, [r5]
	add r5, r2, #0
	ldmia r6!, {r0, r1}
	add r5, #0x74
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	add r6, r7, #0
	str r0, [r5]
	add r5, r2, #0
	ldmia r6!, {r0, r1}
	add r5, #0x80
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	str r0, [r5]
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	str r3, [r2, #0x64]
	cmp r4, #0x20
	blo _021E7C28
	add sp, #0xc
	pop {r3, r4, r5, r6, r7}
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021E7C80
MOD05_021E7C80: ; 0x021E7C80
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	cmp r5, #0x20
	blt _021E7C90
	bl ErrorHandling
_021E7C90:
	add r6, sp, #0
	mov r3, #0
	str r3, [r6]
	str r3, [r6, #4]
	mov r0, #0x8c
	mul r0, r5
	str r3, [r6, #8]
	str r3, [r4, r0]
	add r2, r4, r0
	str r3, [r2, #4]
	str r3, [r2, #8]
	add r4, r2, #0
	str r3, [r2, #0xc]
	add r5, r6, #0
	ldmia r5!, {r0, r1}
	add r4, #0x68
	stmia r4!, {r0, r1}
	ldr r0, [r5]
	add r5, r6, #0
	str r0, [r4]
	add r4, r2, #0
	ldmia r5!, {r0, r1}
	add r4, #0x74
	stmia r4!, {r0, r1}
	ldr r0, [r5]
	str r0, [r4]
	add r4, r2, #0
	ldmia r6!, {r0, r1}
	add r4, #0x80
	stmia r4!, {r0, r1}
	ldr r0, [r6]
	str r0, [r4]
	str r3, [r2, #0x64]
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E7CD8
MOD05_021E7CD8: ; 0x021E7CD8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	ldr r0, [sp, #0x28]
	add r4, r1, #0
	str r0, [sp, #0x28]
	mov r0, #0
	add r7, r2, #0
	add r5, r3, #0
	str r0, [sp, #4]
	cmp r4, #0
	beq _021E7D0E
	mov r0, #4
	bl AllocFromHeapAtEnd
	str r0, [sp, #4]
	ldr r2, [sp, #4]
	add r0, r6, #0
	add r1, r4, #0
	bl NARC_ReadFile
	add r0, r4, #0
	mov r1, #0x30
	bl _u32_div_f
	str r0, [sp]
	b _021E7D10
_021E7D0E:
	str r0, [sp]
_021E7D10:
	ldr r4, [sp, #4]
	mov r6, #0
_021E7D14:
	ldr r0, [sp]
	cmp r6, r0
	bhs _021E7D82
	ldr r0, [r4]
	add r2, r5, #0
	str r0, [r5]
	mov r0, #1
	str r0, [r5, #4]
	mov r0, #0
	add r3, r4, #4
	str r0, [r5, #0xc]
	ldmia r3!, {r0, r1}
	add r2, #0x68
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r3, r4, #0
	str r0, [r2]
	add r3, #0x10
	add r2, r5, #0
	ldmia r3!, {r0, r1}
	add r2, #0x74
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r3, r4, #0
	str r0, [r2]
	add r3, #0x1c
	add r2, r5, #0
	ldmia r3!, {r0, r1}
	add r2, #0x80
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r3, r5, #0
	str r0, [r2]
	add r2, r5, #0
	ldr r0, [r5]
	add r1, r7, #0
	add r2, #0x10
	add r3, #0x64
	bl MOD05_021E7F10
	ldr r1, [r5]
	add r0, r7, #0
	bl MOD05_021F4CE4
	cmp r0, #0
	bne _021E7D74
	mov r0, #0
	str r0, [r5]
_021E7D74:
	add r1, r5, #0
	ldr r0, [r5]
	ldr r2, [sp, #0x28]
	add r1, #0x10
	bl MOD05_021D9E80
	b _021E7DBE
_021E7D82:
	mov r1, #0
	add r0, sp, #8
	str r1, [r0]
	str r1, [r0, #4]
	str r1, [r0, #8]
	add r0, r1, #0
	str r0, [r5]
	str r0, [r5, #4]
	add r2, r5, #0
	add r3, sp, #8
	str r0, [r5, #0xc]
	ldmia r3!, {r0, r1}
	add r2, #0x68
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r3, sp, #8
	str r0, [r2]
	add r2, r5, #0
	ldmia r3!, {r0, r1}
	add r2, #0x74
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r3, sp, #8
	str r0, [r2]
	add r2, r5, #0
	ldmia r3!, {r0, r1}
	add r2, #0x80
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
_021E7DBE:
	add r6, r6, #1
	add r5, #0x8c
	add r4, #0x30
	cmp r6, #0x20
	blt _021E7D14
	ldr r0, [sp, #4]
	cmp r0, #0
	beq _021E7DD2
	bl FreeToHeap
_021E7DD2:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E7DD8
MOD05_021E7DD8: ; 0x021E7DD8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x48
	ldr r4, _021E7E94 ; =UNK05_021F7878
	str r2, [sp, #0xc]
	str r3, [sp, #0x10]
	add r6, r0, #0
	str r1, [sp, #8]
	add r3, sp, #0x18
	mov r2, #4
_021E7DEA:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021E7DEA
	ldr r0, [r4]
	ldr r5, [sp, #0x60]
	str r0, [r3]
	mov r7, #0
_021E7DFA:
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _021E7E86
	ldr r0, [r5, #8]
	cmp r0, #0
	bne _021E7E86
	add r4, r5, #0
	add r4, #0x68
	ldmia r4!, {r0, r1}
	add r3, sp, #0x3c
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	str r0, [r3]
	ldr r1, [sp, #0x3c]
	ldr r0, [r6]
	add r3, r5, #0
	add r0, r1, r0
	str r0, [sp, #0x3c]
	ldr r1, [sp, #0x44]
	ldr r0, [r6, #8]
	add r3, #0x80
	add r0, r1, r0
	str r0, [sp, #0x44]
	add r1, r2, #0
	ldr r0, [r5, #0x64]
	add r2, sp, #0x18
	bl FUN_0201B6D0
	cmp r0, #0
	beq _021E7E86
	ldr r0, [sp, #8]
	bl MOD05_021F4C9C
	add r4, r0, #0
	ldr r0, [sp, #0xc]
	cmp r0, #1
	bne _021E7E50
	ldr r0, [sp, #0x10]
	ldr r1, [r5, #0x64]
	ldr r2, _021E7E98 ; =0x00000F33
	bl MOD05_021DBB8C
_021E7E50:
	ldr r0, [r5]
	add r1, r4, #0
	add r2, sp, #0x14
	bl MOD05_021DB9D4
	add r0, sp, #0x14
	ldrh r0, [r0]
	add r1, sp, #0x3c
	cmp r0, #0
	bne _021E7E74
	add r0, r5, #0
	add r3, r5, #0
	add r0, #0x10
	add r2, sp, #0x18
	add r3, #0x80
	bl FUN_0201B26C
	b _021E7E86
_021E7E74:
	str r4, [sp]
	ldr r0, [r5]
	add r3, r5, #0
	str r0, [sp, #4]
	ldr r0, [r5, #0x64]
	add r2, sp, #0x18
	add r3, #0x80
	bl MOD05_021E7F34
_021E7E86:
	add r7, r7, #1
	add r5, #0x8c
	cmp r7, #0x20
	blt _021E7DFA
	add sp, #0x48
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E7E94: .word UNK05_021F7878
_021E7E98: .word 0x00000F33

	thumb_func_start MOD05_021E7E9C
MOD05_021E7E9C: ; 0x021E7E9C
	add r0, #0x74
	bx lr

	thumb_func_start MOD05_021E7EA0
MOD05_021E7EA0: ; 0x021E7EA0
	add r2, r1, #0
	add r2, #0x68
	add r3, r0, #0
	ldmia r2!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r2]
	str r0, [r3]
	bx lr

	thumb_func_start MOD05_021E7EB0
MOD05_021E7EB0: ; 0x021E7EB0
	add r3, r1, #0
	add r2, r0, #0
	ldmia r3!, {r0, r1}
	add r2, #0x68
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	bx lr

	thumb_func_start MOD05_021E7EC0
MOD05_021E7EC0: ; 0x021E7EC0
	str r1, [r0, #8]
	bx lr

	thumb_func_start MOD05_021E7EC4
MOD05_021E7EC4: ; 0x021E7EC4
	ldr r0, [r0]
	bx lr

	thumb_func_start MOD05_021E7EC8
MOD05_021E7EC8: ; 0x021E7EC8
	add r0, #0x10
	bx lr

	thumb_func_start MOD05_021E7ECC
MOD05_021E7ECC: ; 0x021E7ECC
	ldr r0, [r0, #0x64]
	bx lr

	thumb_func_start MOD05_021E7ED0
MOD05_021E7ED0: ; 0x021E7ED0
	mov r2, #0x8c
	mul r2, r1
	add r0, r0, r2
	bx lr

	thumb_func_start MOD05_021E7ED8
MOD05_021E7ED8: ; 0x021E7ED8
	mov r3, #0
_021E7EDA:
	ldr r2, [r0]
	cmp r2, r1
	beq _021E7EEA
	add r3, r3, #1
	add r0, #0x8c
	cmp r3, #0x20
	blt _021E7EDA
	mov r0, #0
_021E7EEA:
	bx lr

	thumb_func_start MOD05_021E7EEC
MOD05_021E7EEC: ; 0x021E7EEC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	cmp r4, #0x20
	blt _021E7EFA
	bl ErrorHandling
_021E7EFA:
	mov r0, #0x8c
	mul r0, r4
	add r4, r5, r0
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021E7F0A
	bl ErrorHandling
_021E7F0A:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E7F10
MOD05_021E7F10: ; 0x021E7F10
	push {r3, r4, r5, lr}
	add r5, r2, #0
	add r4, r3, #0
	bl MOD05_021F4BD0
	ldr r0, [r0]
	bl NNS_G3dGetMdlSet
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r1, r0, r1
	add r0, r5, #0
	str r1, [r4]
	bl NNS_G3dRenderObjInit
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E7F34
MOD05_021E7F34: ; 0x021E7F34
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r0, r1, #0
	add r4, r2, #0
	add r5, r3, #0
	bl NNS_G3dGlbSetBaseTrans
	ldr r1, _021E7FB4 ; =NNS_G3dGlb + 0xBC
	add r0, r4, #0
	bl MI_Copy36B
	ldr r1, _021E7FB8 ; =NNS_G3dGlb + 0x80
	mov r0, #0xa4
	ldr r2, [r1, #0x7c]
	bic r2, r0
	add r0, r5, #0
	str r2, [r1, #0x7c]
	bl NNS_G3dGlbSetBaseScale
	bl NNS_G3dGlbFlushP
	add r2, sp, #0
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	add r2, #2
	add r3, sp, #0
	bl MOD05_021DB9E0
	add r0, sp, #0
	ldrh r0, [r0]
	ldr r1, [sp, #0x18]
	bl MOD05_021DB9F8
	add r6, r0, #0
	add r0, sp, #0
	ldrh r0, [r0, #2]
	mov r5, #0xff
	mov r4, #0
	cmp r0, #0
	ble _021E7FB0
_021E7F84:
	lsl r0, r4, #2
	add r2, r6, r0
	ldrh r0, [r6, r0]
	cmp r5, r0
	beq _021E7F96
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	mov r3, #1
	b _021E7F98
_021E7F96:
	mov r3, #0
_021E7F98:
	ldrh r2, [r2, #2]
	add r0, r7, #0
	add r1, r5, #0
	bl NNS_G3dDraw1Mat1Shp
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	add r0, sp, #0
	ldrh r0, [r0, #2]
	cmp r4, r0
	blt _021E7F84
_021E7FB0:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E7FB4: .word NNS_G3dGlb + 0xBC
_021E7FB8: .word NNS_G3dGlb + 0x80

	thumb_func_start MOD05_021E7FBC
MOD05_021E7FBC: ; 0x021E7FBC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r5, _021E8058 ; =UNK05_021F786C
	add r6, r0, #0
	add r7, r1, #0
	ldmia r5!, {r0, r1}
	add r4, sp, #4
	stmia r4!, {r0, r1}
	ldr r0, [r5]
	str r0, [r4]
	mov r4, #0
	mov r0, #0x8c
_021E7FD4:
	add r1, r4, #0
	mul r1, r0
	add r5, r6, r1
	ldr r1, [r5, #4]
	cmp r1, #0
	bne _021E8044
	mov r0, #1
	str r0, [r5, #4]
	add r6, r5, #0
	ldmia r3!, {r0, r1}
	add r6, #0x68
	stmia r6!, {r0, r1}
	ldr r0, [r3]
	str r0, [r6]
	ldr r6, [sp, #0x28]
	cmp r6, #0
	beq _021E8008
	mov r0, #1
	str r0, [r5, #0xc]
	add r3, r5, #0
	ldmia r6!, {r0, r1}
	add r3, #0x74
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	str r0, [r3]
	b _021E800C
_021E8008:
	mov r0, #0
	str r0, [r5, #0xc]
_021E800C:
	add r6, sp, #4
	add r3, r5, #0
	ldmia r6!, {r0, r1}
	add r3, #0x80
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	add r1, r7, #0
	str r0, [r3]
	add r3, r5, #0
	str r2, [r5]
	add r0, r2, #0
	add r2, r5, #0
	add r2, #0x10
	add r3, #0x64
	bl MOD05_021E7F10
	ldr r0, [sp, #0x2c]
	mov r1, #0
	str r0, [sp]
	ldr r0, [r5]
	add r5, #0x10
	add r2, r1, #0
	add r3, r5, #0
	bl MOD05_021D9DC0
	add sp, #0x10
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
_021E8044:
	add r1, r4, #1
	lsl r1, r1, #0x18
	lsr r4, r1, #0x18
	cmp r4, #0x20
	blo _021E7FD4
	bl ErrorHandling
	mov r0, #0x20
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E8058: .word UNK05_021F786C

	thumb_func_start MOD05_021E805C
MOD05_021E805C: ; 0x021E805C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	ldr r4, _021E80F4 ; =UNK05_021F789C
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r3, sp, #0x14
	mov r2, #4
_021E806A:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021E806A
	ldr r0, [r4]
	mov r4, #0
	str r0, [r3]
	add r7, sp, #0x14
_021E807A:
	mov r0, #0x8c
	add r1, r4, #0
	mul r1, r0
	ldr r0, [sp, #8]
	add r5, r0, r1
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _021E80E4
	ldr r0, [r5, #8]
	cmp r0, #0
	bne _021E80E4
	ldr r0, [sp, #0xc]
	bl MOD05_021F4C9C
	add r6, r0, #0
	ldr r0, [r5]
	add r1, r6, #0
	add r2, sp, #0x10
	bl MOD05_021DB9D4
	ldr r0, [r5, #0xc]
	cmp r0, #0
	beq _021E80B2
	add r1, r5, #0
	add r0, r7, #0
	add r1, #0x74
	bl FUN_0201CAA8
_021E80B2:
	add r0, sp, #0x10
	ldrh r0, [r0]
	cmp r0, #0
	bne _021E80CE
	add r0, r5, #0
	add r1, r5, #0
	add r5, #0x80
	add r0, #0x10
	add r1, #0x68
	add r2, r7, #0
	add r3, r5, #0
	bl FUN_0201B26C
	b _021E80E4
_021E80CE:
	str r6, [sp]
	ldr r0, [r5]
	add r1, r5, #0
	str r0, [sp, #4]
	ldr r0, [r5, #0x64]
	add r5, #0x80
	add r1, #0x68
	add r2, r7, #0
	add r3, r5, #0
	bl MOD05_021E7F34
_021E80E4:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x20
	blo _021E807A
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E80F4: .word UNK05_021F789C

	.section .rodata

	.global UNK05_021F786C
UNK05_021F786C: ; 0x021F786C
	.word 0x00001000, 0x00001000, 0x00001000

	.global UNK05_021F7878
UNK05_021F7878: ; 0x021F7878
	.byte 0x00, 0x10, 0x00, 0x00 ;word
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global UNK05_021F789C
UNK05_021F789C: ; 0x021F789C
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ;word
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
