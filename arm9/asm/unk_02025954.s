	.include "asm/macros.inc"
    .include "global.inc"

	.extern gMain

	.section .rodata

	.global UNK_020EE958
UNK_020EE958: ; 0x020EE958
	.byte 0x00, 0x02, 0x02, 0x04, 0x04, 0x05, 0x00, 0x01, 0x01, 0x03, 0x03, 0x05

	.section .data

	.global UNK_02105C74
UNK_02105C74: ; 0x02105C74
	.byte 0x6E, 0x00, 0x6F, 0x00, 0x50, 0x00, 0x5B, 0x00, 0x51, 0x00, 0xEE, 0x00, 0x53, 0x00, 0xE5, 0x00
	.byte 0x52, 0x00, 0x54, 0x00, 0x55, 0x00, 0x5C, 0x00, 0x65, 0x00, 0x66, 0x00, 0x64, 0x00, 0x63, 0x00
	.byte 0x67, 0x00, 0x6A, 0x00, 0x1C, 0x00, 0x1D, 0x00, 0x48, 0x00, 0x49, 0x00, 0x4A, 0x00, 0x4B, 0x00
	.byte 0x5D, 0x00, 0x68, 0x00, 0x69, 0x00, 0x0D, 0x01, 0x16, 0x01, 0x1A, 0x01, 0x1B, 0x01, 0x1C, 0x01
	.byte 0x1D, 0x01, 0x2A, 0x01, 0x2B, 0x01, 0x2C, 0x01, 0x2D, 0x01, 0x2E, 0x01, 0x2F, 0x01, 0x30, 0x01
	.byte 0x31, 0x01, 0x32, 0x01, 0x33, 0x01, 0x34, 0x01, 0x35, 0x01, 0x36, 0x01, 0x37, 0x01, 0x38, 0x01
	.byte 0x39, 0x01, 0x00, 0x00

	.text

	thumb_func_start FUN_02025954
FUN_02025954: ; 0x02025954
	ldr r0, _02025958 ; =0x000009B4
	bx lr
	.balign 4
_02025958: .word 0x000009B4

	thumb_func_start FUN_0202595C
FUN_0202595C: ; 0x0202595C
	mov r0, #0x94
	bx lr

	thumb_func_start FUN_02025960
FUN_02025960: ; 0x02025960
	mov r0, #0x3c
	bx lr

	thumb_func_start FUN_02025964
FUN_02025964: ; 0x02025964
	push {r4, lr}
	mov r1, #0x3c
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x3c
	add r4, r0, #0x0
	bl MI_CpuFill8
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202597C
FUN_0202597C: ; 0x0202597C
	push {r4-r7, lr}
	sub sp, #0x1c
	add r4, r0, #0x0
	add r0, sp, #0xc
	add r1, sp, #0x0
	bl GF_RTC_CopyDateTime
	ldr r0, _020259D8 ; =gMain
	ldr r6, [sp, #0xc]
	ldr r1, [sp, #0x8]
	ldr r0, [r0, #0x2c]
	lsl r6, r6, #0x5
	add r5, r1, r0
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r0, r0, r6
	lsl r0, r0, #0x5
	add r0, r1, r0
	mov r7, #0x0
	ldr r2, [sp, #0x0]
	lsl r0, r0, #0x5
	add r0, r2, r0
	ldr r3, [sp, #0x4]
	lsl r0, r0, #0x5
	add r0, r3, r0
	lsl r0, r0, #0x5
	add r5, r5, r0
	ldr r2, _020259DC ; =0x000009B4
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl MI_CpuFill8
	add r0, r4, #0x0
	add r0, #0x94
	mov r1, #0x9b
	str r5, [r0, #0x0]
	lsl r1, r1, #0x4
	ldrb r2, [r4, r1]
	mov r0, #0xf
	bic r2, r0
	mov r0, #0x1
	orr r0, r2
	strb r0, [r4, r1]
	add sp, #0x1c
	pop {r4-r7, pc}
	nop
_020259D8: .word gMain
_020259DC: .word 0x000009B4

	thumb_func_start FUN_020259E0
FUN_020259E0: ; 0x020259E0
	mov r1, #0x9
	mov r3, #0x0
	lsl r1, r1, #0x8
_020259E6:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	bne _020259F2
	add r0, r3, #0x0
	bx lr
_020259F2:
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _020259E6
	mov r0, #0x0
	mvn r0, r0
	bx lr
	.balign 4

	thumb_func_start FUN_02025A00
FUN_02025A00: ; 0x02025A00
	mov r1, #0x95
	mov r3, #0x0
	lsl r1, r1, #0x4
_02025A06:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	bne _02025A12
	add r0, r3, #0x0
	bx lr
_02025A12:
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02025A06
	mov r0, #0x0
	mvn r0, r0
	bx lr
	.balign 4

	thumb_func_start FUN_02025A20
FUN_02025A20: ; 0x02025A20
	ldr r1, _02025A3C ; =0x00000928
	mov r3, #0x0
_02025A24:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	bne _02025A30
	add r0, r3, #0x0
	bx lr
_02025A30:
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02025A24
	mov r0, #0x0
	mvn r0, r0
	bx lr
	.balign 4
_02025A3C: .word 0x00000928

	thumb_func_start FUN_02025A40
FUN_02025A40: ; 0x02025A40
	ldr r1, _02025A5C ; =0x000008D8
	mov r3, #0x0
_02025A44:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	bne _02025A50
	add r0, r3, #0x0
	bx lr
_02025A50:
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02025A44
	mov r0, #0x0
	mvn r0, r0
	bx lr
	.balign 4
_02025A5C: .word 0x000008D8

	thumb_func_start FUN_02025A60
FUN_02025A60: ; 0x02025A60
	push {r4-r7, lr}
	sub sp, #0x14
	str r1, [sp, #0x0]
	bl FUN_02026CC4
	ldr r1, _02025B50 ; =UNK_020EE958
	add r6, r0, #0x0
	ldrb r2, [r1, #0x0]
	add r0, sp, #0x8
	strb r2, [r0, #0x6]
	ldrb r2, [r1, #0x1]
	strb r2, [r0, #0x7]
	ldrb r2, [r1, #0x2]
	strb r2, [r0, #0x8]
	ldrb r2, [r1, #0x3]
	strb r2, [r0, #0x9]
	ldrb r2, [r1, #0x4]
	strb r2, [r0, #0xa]
	ldrb r2, [r1, #0x5]
	strb r2, [r0, #0xb]
	ldrb r2, [r1, #0x6]
	strb r2, [r0, #0x0]
	ldrb r2, [r1, #0x7]
	strb r2, [r0, #0x1]
	ldrb r2, [r1, #0x8]
	strb r2, [r0, #0x2]
	ldrb r2, [r1, #0x9]
	strb r2, [r0, #0x3]
	ldrb r2, [r1, #0xa]
	strb r2, [r0, #0x4]
	ldrb r1, [r1, #0xb]
	strb r1, [r0, #0x5]
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	ble _02025B4C
	str r0, [sp, #0x4]
	cmp r0, #0x63
	ble _02025AB0
	mov r0, #0x63
	str r0, [sp, #0x4]
_02025AB0:
	add r0, r6, #0x0
	add r0, #0x94
	ldr r3, [r0, #0x0]
	mov r0, #0x0
	mov r12, r0
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _02025B28
	add r7, sp, #0xc
	add r7, #0x2
_02025AC4:
	mov r2, #0x0
_02025AC6:
	ldr r0, _02025B54 ; =0x0000055C
	add r4, r6, r2
	ldrb r5, [r4, r0]
	cmp r5, #0x0
	beq _02025B16
	ldr r0, _02025B58 ; =0x5D588B65
	ldrb r1, [r7, r5]
	mul r0, r3
	ldr r3, _02025B5C ; =0x00269EC3
	add r3, r0, r3
	cmp r1, #0x0
	bne _02025AE2
	lsr r0, r3, #0x10
	b _02025AE8
_02025AE2:
	lsr r0, r3, #0x10
	mul r1, r0
	lsr r0, r1, #0x10
_02025AE8:
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	add r0, sp, #0x8
	ldrb r0, [r0, r5]
	add r0, r0, r1
	mov r1, #0x17
	lsl r1, r1, #0x6
	ldrb r1, [r4, r1]
	add r1, r0, r1
	cmp r1, #0x63
	bge _02025B0E
	mov r1, #0x17
	lsl r1, r1, #0x6
	ldrb r1, [r4, r1]
	add r1, r1, r0
	mov r0, #0x17
	lsl r0, r0, #0x6
	strb r1, [r4, r0]
	b _02025B16
_02025B0E:
	mov r0, #0x17
	mov r1, #0x63
	lsl r0, r0, #0x6
	strb r1, [r4, r0]
_02025B16:
	add r2, r2, #0x1
	cmp r2, #0x64
	blt _02025AC6
	mov r0, r12
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	mov r12, r1
	cmp r1, r0
	blt _02025AC4
_02025B28:
	add r0, r6, #0x0
	add r0, #0x94
	ldr r1, [r0, #0x0]
	ldr r0, [sp, #0x0]
	add r0, r1, r0
	bl PRandom
	add r1, r6, #0x0
	add r1, #0x94
	str r0, [r1, #0x0]
	mov r1, #0x9b
	lsl r1, r1, #0x4
	ldrb r2, [r6, r1]
	mov r0, #0xf
	bic r2, r0
	mov r0, #0x1
	orr r0, r2
	strb r0, [r6, r1]
_02025B4C:
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02025B50: .word UNK_020EE958
_02025B54: .word 0x0000055C
_02025B58: .word 0x5D588B65
_02025B5C: .word 0x00269EC3

	thumb_func_start FUN_02025B60
FUN_02025B60: ; 0x02025B60
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r2, #0x0
	bl FUN_02026CC4
	cmp r4, #0x0
	blt _02025B90
	cmp r5, #0x0
	bne _02025B90
	add r1, r0, #0x0
	add r1, #0x98
	ldr r1, [r1, #0x0]
	cmp r1, r4
	bge _02025B84
	mov r1, #0x0
	add r0, #0x98
	str r1, [r0, #0x0]
	pop {r3-r5, pc}
_02025B84:
	add r1, r0, #0x0
	add r1, #0x98
	ldr r1, [r1, #0x0]
	add r0, #0x98
	sub r1, r1, r4
	str r1, [r0, #0x0]
_02025B90:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02025B94
FUN_02025B94: ; 0x02025B94
	push {r3, lr}
	bl FUN_02026CC4
	add r1, r0, #0x0
	add r1, #0x98
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02025BB6
	add r1, r0, #0x0
	add r1, #0x9c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x2
	bne _02025BB6
	add r1, r0, #0x0
	mov r2, #0x0
	add r1, #0x9c
	strb r2, [r1, #0x0]
_02025BB6:
	add r1, r0, #0x0
	add r1, #0x98
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02025BD4
	add r1, r0, #0x0
	add r1, #0x9c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x1
	bne _02025BD4
	mov r2, #0x5a
	add r1, r0, #0x0
	lsl r2, r2, #0x4
	add r1, #0x98
	str r2, [r1, #0x0]
_02025BD4:
	add r1, r0, #0x0
	add r1, #0x9c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x1
	bne _02025BE4
	mov r1, #0x2
	add r0, #0x9c
	strb r1, [r0, #0x0]
_02025BE4:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02025BE8
FUN_02025BE8: ; 0x02025BE8
	push {r3, lr}
	bl FUN_02026CC4
	add r1, r0, #0x0
	add r1, #0x9c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02025BFE
	mov r1, #0x1
	add r0, #0x9c
	strb r1, [r0, #0x0]
_02025BFE:
	pop {r3, pc}

	thumb_func_start FUN_02025C00
FUN_02025C00: ; 0x02025C00
	push {r3, lr}
	bl FUN_02026CC4
	add r1, r0, #0x0
	add r1, #0x9c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x1
	bne _02025C16
	mov r1, #0x0
	add r0, #0x9c
	strb r1, [r0, #0x0]
_02025C16:
	pop {r3, pc}

	thumb_func_start FUN_02025C18
FUN_02025C18: ; 0x02025C18
	push {r3, lr}
	bl FUN_02026CC4
	add r0, #0x9c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	beq _02025C2A
	mov r0, #0x1
	pop {r3, pc}
_02025C2A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02025C30
FUN_02025C30: ; 0x02025C30
	mov r1, #0x1
	add r0, #0x9d
	strb r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02025C38
FUN_02025C38: ; 0x02025C38
	add r0, #0x9d
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02025C40
FUN_02025C40: ; 0x02025C40
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, _02025CD0 ; =0x0000010E
	add r6, r1, #0x0
	ldrb r0, [r7, r0]
	mov r4, #0x0
	add r5, r7, #0x0
	str r0, [sp, #0x0]
_02025C50:
	add r0, r6, #0x0
	bl PlayerProfile_GetTrainerID
	add r1, r5, #0x0
	add r1, #0xa0
	ldr r1, [r1, #0x0]
	cmp r1, r0
	beq _02025CCC
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x5
	blt _02025C50
	ldr r0, [sp, #0x0]
	cmp r0, #0x5
	blt _02025C72
	bl ErrorHandling
_02025C72:
	add r0, r6, #0x0
	bl PlayerProfile_GetNamePtr
	ldr r1, [sp, #0x0]
	add r2, r7, #0x0
	add r2, #0xb4
	lsl r1, r1, #0x4
	add r1, r2, r1
	mov r2, #0x10
	bl MI_CpuCopy8
	add r0, r6, #0x0
	bl PlayerProfile_GetTrainerID
	ldr r1, [sp, #0x0]
	lsl r1, r1, #0x2
	add r1, r7, r1
	add r1, #0xa0
	str r0, [r1, #0x0]
	add r0, r6, #0x0
	bl PlayerProfile_GetLanguage
	ldr r1, [sp, #0x0]
	add r2, r7, r1
	mov r1, #0x41
	lsl r1, r1, #0x2
	strb r0, [r2, r1]
	add r0, r6, #0x0
	bl PlayerProfile_GetVersion
	ldr r1, [sp, #0x0]
	add r2, r7, r1
	ldr r1, _02025CD4 ; =0x00000109
	strb r0, [r2, r1]
	add r0, r1, #0x5
	ldrb r0, [r7, r0]
	add r2, r0, #0x1
	add r0, r1, #0x5
	strb r2, [r7, r0]
	ldrb r0, [r7, r0]
	cmp r0, #0x5
	blo _02025CCC
	mov r2, #0x0
	add r0, r1, #0x5
	strb r2, [r7, r0]
_02025CCC:
	pop {r3-r7, pc}
	nop
_02025CD0: .word 0x0000010E
_02025CD4: .word 0x00000109

	thumb_func_start FUN_02025CD8
FUN_02025CD8: ; 0x02025CD8
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _02025D38 ; =0x0000010E
	ldrb r0, [r5, r0]
	sub r0, r0, r2
	sub r4, r0, #0x1
	bpl _02025CE8
	add r4, r4, #0x5
_02025CE8:
	add r7, r5, #0x0
	lsl r0, r4, #0x4
	add r7, #0xb4
	str r0, [sp, #0x0]
	ldrh r0, [r7, r0]
	cmp r0, #0x0
	beq _02025D32
	add r0, r1, #0x0
	bl PlayerProfile_new
	ldr r1, [sp, #0x0]
	add r6, r0, #0x0
	add r1, r7, r1
	bl CopyPlayerName
	ldr r1, _02025D3C ; =0x00000109
	add r2, r5, r4
	ldrb r1, [r2, r1]
	add r0, r6, #0x0
	bl PlayerProfile_SetVersion
	mov r1, #0x41
	add r2, r5, r4
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	add r0, r6, #0x0
	bl PlayerProfile_SetLanguage
	lsl r1, r4, #0x2
	add r1, r5, r1
	add r1, #0xa0
	ldr r1, [r1, #0x0]
	add r0, r6, #0x0
	bl PlayerProfile_SetTrainerID
	add r0, r6, #0x0
	pop {r3-r7, pc}
_02025D32:
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_02025D38: .word 0x0000010E
_02025D3C: .word 0x00000109

	thumb_func_start FUN_02025D40
FUN_02025D40: ; 0x02025D40
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02025D48
FUN_02025D48: ; 0x02025D48
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0xb
	bge _02025D54
	bl ErrorHandling
_02025D54:
	cmp r4, #0x3c
	blt _02025D5C
	bl ErrorHandling
_02025D5C:
	sub r4, #0xb
	ldr r0, _02025D68 ; =UNK_02105C74
	lsl r1, r4, #0x1
	ldrh r0, [r0, r1]
	pop {r4, pc}
	nop
_02025D68: .word UNK_02105C74

	thumb_func_start FUN_02025D6C
FUN_02025D6C: ; 0x02025D6C
	push {r4-r5}
	mov r2, #0x81
	mov r5, #0x0
	lsl r2, r2, #0x4
_02025D74:
	add r4, r0, r5
	ldrb r3, [r4, r2]
	cmp r3, #0x0
	bne _02025D88
	mov r0, #0x81
	lsl r0, r0, #0x4
	strb r1, [r4, r0]
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_02025D88:
	add r5, r5, #0x1
	cmp r5, #0xc8
	blt _02025D74
	mov r0, #0x0
	pop {r4-r5}
	bx lr

	thumb_func_start FUN_02025D94
FUN_02025D94: ; 0x02025D94
	mov r1, #0x81
	mov r3, #0x0
	lsl r1, r1, #0x4
_02025D9A:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	bne _02025DA6
	mov r0, #0x1
	bx lr
_02025DA6:
	add r3, r3, #0x1
	cmp r3, #0xc8
	blt _02025D9A
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02025DB0
FUN_02025DB0: ; 0x02025DB0
	mov r1, #0x81
	mov r3, #0x0
	lsl r1, r1, #0x4
_02025DB6:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	beq _02025DC4
	add r3, r3, #0x1
	cmp r3, #0xc8
	blt _02025DB6
_02025DC4:
	add r0, r3, #0x0
	bx lr

	thumb_func_start FUN_02025DC8
FUN_02025DC8: ; 0x02025DC8
	add r1, r0, r1
	mov r0, #0x81
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02025DD4
FUN_02025DD4: ; 0x02025DD4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02025F0C
	cmp r0, #0x0
	beq _02025DE6
	bl ErrorHandling
_02025DE6:
	mov r0, #0x81
	add r1, r5, r4
	lsl r0, r0, #0x4
	add r6, r4, #0x0
	ldrb r7, [r1, r0]
	cmp r4, #0xc7
	bge _02025E06
	mov r1, #0x81
	add r0, r0, #0x1
	lsl r1, r1, #0x4
_02025DFA:
	add r3, r5, r6
	ldrb r2, [r3, r0]
	add r6, r6, #0x1
	cmp r6, #0xc7
	strb r2, [r3, r1]
	blt _02025DFA
_02025E06:
	ldr r0, _02025E1C ; =0x000008D7
	mov r2, #0x0
	strb r2, [r5, r0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	sub r2, r2, #0x1
	bl FUN_02025F58
	add r0, r7, #0x0
	pop {r3-r7, pc}
	nop
_02025E1C: .word 0x000008D7

	thumb_func_start FUN_02025E20
FUN_02025E20: ; 0x02025E20
	push {r4-r7, lr}
	sub sp, #0xd4
	mov r4, #0x0
	add r5, r0, #0x0
	sub r0, r4, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x81
	lsl r0, r0, #0x4
	str r1, [sp, #0x8]
	str r2, [sp, #0x0]
	add r0, r5, r0
	add r1, sp, #0xc
	mov r2, #0xc8
	bl MI_CpuCopy8
	ldr r2, [sp, #0x8]
	add r1, sp, #0xc
	add r0, r4, #0x0
	add r7, r1, r2
_02025E46:
	ldr r2, [sp, #0x8]
	cmp r0, r2
	beq _02025E58
	ldrb r6, [r1, #0x0]
	mov r2, #0x81
	add r3, r5, r4
	lsl r2, r2, #0x4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_02025E58:
	ldr r2, [sp, #0x0]
	cmp r0, r2
	bne _02025E6A
	ldrb r6, [r7, #0x0]
	mov r2, #0x81
	add r3, r5, r4
	lsl r2, r2, #0x4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_02025E6A:
	add r0, r0, #0x1
	add r1, r1, #0x1
	cmp r0, #0xc8
	blt _02025E46
	ldr r0, [sp, #0x8]
	mov r3, #0x0
	add r2, r0, #0x1
	mov r0, #0x9a
	lsl r0, r0, #0x4
_02025E7C:
	add r1, r5, r3
	ldrb r1, [r1, r0]
	cmp r2, r1
	bne _02025E88
	str r3, [sp, #0x4]
	b _02025E8E
_02025E88:
	add r3, r3, #0x1
	cmp r3, #0xf
	blt _02025E7C
_02025E8E:
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	mov r2, #0x1
	bl FUN_02025F58
	mov r2, #0x0
	ldr r1, [sp, #0x8]
	add r0, r5, #0x0
	mvn r2, r2
	bl FUN_02025F58
	mov r1, #0x0
	ldr r0, [sp, #0x4]
	mvn r1, r1
	cmp r0, r1
	beq _02025ED6
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x8]
	cmp r0, r1
	bge _02025EC8
	add r0, r1, #0x0
	add r2, r0, #0x1
	ldr r0, [sp, #0x4]
	add sp, #0xd4
	add r1, r5, r0
	mov r0, #0x9a
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
	pop {r4-r7, pc}
_02025EC8:
	add r0, r1, #0x0
	add r2, r0, #0x2
	ldr r0, [sp, #0x4]
	add r1, r5, r0
	mov r0, #0x9a
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
_02025ED6:
	add sp, #0xd4
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02025EDC
FUN_02025EDC: ; 0x02025EDC
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r6, #0x1
	bge _02025EEC
	bl ErrorHandling
_02025EEC:
	cmp r6, #0xf
	ble _02025EF4
	bl ErrorHandling
_02025EF4:
	sub r0, r6, #0x1
	add r1, r5, r0
	mov r0, #0x9a
	add r2, r4, #0x1
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
	mov r0, #0x81
	add r1, r5, r4
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02025F0C
FUN_02025F0C: ; 0x02025F0C
	push {r3-r4}
	add r3, r1, #0x1
	mov r1, #0x9a
	mov r4, #0x0
	lsl r1, r1, #0x4
_02025F16:
	add r2, r0, r4
	ldrb r2, [r2, r1]
	cmp r3, r2
	bne _02025F24
	mov r0, #0x1
	pop {r3-r4}
	bx lr
_02025F24:
	add r4, r4, #0x1
	cmp r4, #0xf
	blt _02025F16
	mov r0, #0x0
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02025F30
FUN_02025F30: ; 0x02025F30
	sub r1, r1, #0x1
	cmp r1, #0xf
	bge _02025F40
	add r1, r0, r1
	mov r0, #0x9a
	mov r2, #0x0
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
_02025F40:
	bx lr
	.balign 4

	thumb_func_start FUN_02025F44
FUN_02025F44: ; 0x02025F44
	mov r1, #0x9a
	lsl r1, r1, #0x4
	add r0, r0, r1
	ldr r3, _02025F54 ; =MI_CpuFill8
	mov r1, #0x0
	mov r2, #0xf
	bx r3
	nop
_02025F54: .word MI_CpuFill8

	thumb_func_start FUN_02025F58
FUN_02025F58: ; 0x02025F58
	push {r4-r7}
	mov r6, #0x9a
	lsl r6, r6, #0x4
	mov r4, #0x0
	add r1, r1, #0x1
	add r7, r6, #0x0
_02025F64:
	add r3, r0, r4
	ldrb r5, [r3, r7]
	cmp r5, r1
	ble _02025F76
	mov r5, #0x9a
	lsl r5, r5, #0x4
	ldrb r5, [r3, r5]
	add r5, r5, r2
	strb r5, [r3, r6]
_02025F76:
	add r4, r4, #0x1
	cmp r4, #0xf
	blt _02025F64
	pop {r4-r7}
	bx lr

	thumb_func_start FUN_02025F80
FUN_02025F80: ; 0x02025F80
	mov r1, #0x9
	mov r3, #0x0
	lsl r1, r1, #0x8
_02025F86:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	beq _02025F94
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02025F86
_02025F94:
	add r0, r3, #0x0
	bx lr

	thumb_func_start FUN_02025F98
FUN_02025F98: ; 0x02025F98
	add r1, r0, r1
	mov r0, #0x9
	lsl r0, r0, #0x8
	ldrb r0, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02025FA4
FUN_02025FA4: ; 0x02025FA4
	push {r3-r6}
	mov r2, #0x9
	add r3, r0, r1
	lsl r2, r2, #0x8
	ldrb r2, [r3, r2]
	cmp r1, #0x27
	bge _02025FC2
	ldr r3, _02025FD0 ; =0x00000901
	sub r4, r3, #0x1
_02025FB6:
	add r6, r0, r1
	ldrb r5, [r6, r3]
	add r1, r1, #0x1
	cmp r1, #0x27
	strb r5, [r6, r4]
	blt _02025FB6
_02025FC2:
	ldr r1, _02025FD4 ; =0x00000927
	mov r3, #0x0
	strb r3, [r0, r1]
	add r0, r2, #0x0
	pop {r3-r6}
	bx lr
	nop
_02025FD0: .word 0x00000901
_02025FD4: .word 0x00000927

	thumb_func_start FUN_02025FD8
FUN_02025FD8: ; 0x02025FD8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020259E0
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _02025FF6
	add r1, r5, r0
	mov r0, #0x9
	lsl r0, r0, #0x8
	strb r4, [r1, r0]
	mov r0, #0x1
	pop {r3-r5, pc}
_02025FF6:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02025FFC
FUN_02025FFC: ; 0x02025FFC
	push {r3-r7, lr}
	sub sp, #0x30
	add r5, r0, #0x0
	mov r0, #0x9
	lsl r0, r0, #0x8
	str r1, [sp, #0x4]
	str r2, [sp, #0x0]
	add r0, r5, r0
	add r1, sp, #0x8
	mov r2, #0x28
	mov r4, #0x0
	bl MI_CpuCopy8
	ldr r2, [sp, #0x4]
	add r1, sp, #0x8
	add r0, r4, #0x0
	add r7, r1, r2
_0202601E:
	ldr r2, [sp, #0x4]
	cmp r0, r2
	beq _02026030
	ldrb r6, [r1, #0x0]
	mov r2, #0x9
	add r3, r5, r4
	lsl r2, r2, #0x8
	strb r6, [r3, r2]
	add r4, r4, #0x1
_02026030:
	ldr r2, [sp, #0x0]
	cmp r0, r2
	bne _02026042
	ldrb r6, [r7, #0x0]
	mov r2, #0x9
	add r3, r5, r4
	lsl r2, r2, #0x8
	strb r6, [r3, r2]
	add r4, r4, #0x1
_02026042:
	add r0, r0, #0x1
	add r1, r1, #0x1
	cmp r0, #0x28
	blt _0202601E
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02026050
FUN_02026050: ; 0x02026050
	mov r1, #0x95
	mov r3, #0x0
	lsl r1, r1, #0x4
_02026056:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	beq _02026064
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02026056
_02026064:
	add r0, r3, #0x0
	bx lr

	thumb_func_start FUN_02026068
FUN_02026068: ; 0x02026068
	add r1, r0, r1
	mov r0, #0x95
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026074
FUN_02026074: ; 0x02026074
	add r1, r0, r1
	ldr r0, _0202607C ; =0x00000978
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_0202607C: .word 0x00000978

	thumb_func_start FUN_02026080
FUN_02026080: ; 0x02026080
	push {r4-r7}
	add r2, r0, #0x0
	mov r0, #0x95
	add r3, r2, r1
	lsl r0, r0, #0x4
	ldrb r0, [r3, r0]
	cmp r1, #0x27
	mov r12, r0
	bge _020260AE
	ldr r7, _020260BC ; =0x00000951
	add r4, r7, #0x0
	add r5, r7, #0x0
	sub r3, r7, #0x1
	add r4, #0x28
	add r5, #0x27
_0202609E:
	add r0, r2, r1
	ldrb r6, [r0, r7]
	add r1, r1, #0x1
	cmp r1, #0x27
	strb r6, [r0, r3]
	ldrb r6, [r0, r4]
	strb r6, [r0, r5]
	blt _0202609E
_020260AE:
	ldr r0, _020260C0 ; =0x00000977
	mov r1, #0x0
	strb r1, [r2, r0]
	mov r0, r12
	pop {r4-r7}
	bx lr
	nop
_020260BC: .word 0x00000951
_020260C0: .word 0x00000977

	thumb_func_start FUN_020260C4
FUN_020260C4: ; 0x020260C4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02025A00
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _020260E8
	add r1, r5, r0
	mov r0, #0x95
	lsl r0, r0, #0x4
	strb r4, [r1, r0]
	add r0, #0x28
	strb r6, [r1, r0]
	mov r0, #0x1
	pop {r4-r6, pc}
_020260E8:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020260EC
FUN_020260EC: ; 0x020260EC
	push {r4-r7, lr}
	sub sp, #0x5c
	add r7, r0, #0x0
	mov r0, #0x95
	lsl r0, r0, #0x4
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	add r0, r7, r0
	add r1, sp, #0x34
	mov r2, #0x28
	mov r4, #0x0
	bl MI_CpuCopy8
	ldr r0, _02026168 ; =0x00000978
	add r1, sp, #0xc
	add r0, r7, r0
	mov r2, #0x28
	bl MI_CpuCopy8
	ldr r3, [sp, #0x0]
	add r1, sp, #0x34
	add r3, r1, r3
	mov r12, r3
	ldr r3, [sp, #0x0]
	add r2, sp, #0xc
	add r3, r2, r3
	add r0, r4, #0x0
	str r3, [sp, #0x8]
_02026124:
	ldr r3, [sp, #0x0]
	cmp r0, r3
	beq _0202613C
	ldrb r5, [r1, #0x0]
	mov r3, #0x95
	add r6, r7, r4
	lsl r3, r3, #0x4
	strb r5, [r6, r3]
	ldrb r5, [r2, #0x0]
	add r3, #0x28
	add r4, r4, #0x1
	strb r5, [r6, r3]
_0202613C:
	ldr r3, [sp, #0x4]
	cmp r0, r3
	bne _02026158
	mov r3, r12
	ldrb r5, [r3, #0x0]
	mov r3, #0x95
	add r6, r7, r4
	lsl r3, r3, #0x4
	strb r5, [r6, r3]
	ldr r3, [sp, #0x8]
	add r4, r4, #0x1
	ldrb r5, [r3, #0x0]
	ldr r3, _02026168 ; =0x00000978
	strb r5, [r6, r3]
_02026158:
	add r0, r0, #0x1
	add r1, r1, #0x1
	add r2, r2, #0x1
	cmp r0, #0x28
	blt _02026124
	add sp, #0x5c
	pop {r4-r7, pc}
	nop
_02026168: .word 0x00000978

	thumb_func_start FUN_0202616C
FUN_0202616C: ; 0x0202616C
	ldr r1, _02026184 ; =0x00000928
	mov r3, #0x0
_02026170:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	beq _0202617E
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02026170
_0202617E:
	add r0, r3, #0x0
	bx lr
	nop
_02026184: .word 0x00000928

	thumb_func_start FUN_02026188
FUN_02026188: ; 0x02026188
	add r1, r0, r1
	ldr r0, _02026190 ; =0x00000928
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_02026190: .word 0x00000928

	thumb_func_start FUN_02026194
FUN_02026194: ; 0x02026194
	push {r3-r6}
	ldr r2, _020261BC ; =0x00000928
	add r3, r0, r1
	ldrb r2, [r3, r2]
	cmp r1, #0x27
	bge _020261B0
	ldr r3, _020261C0 ; =0x00000929
	sub r4, r3, #0x1
_020261A4:
	add r6, r0, r1
	ldrb r5, [r6, r3]
	add r1, r1, #0x1
	cmp r1, #0x27
	strb r5, [r6, r4]
	blt _020261A4
_020261B0:
	ldr r1, _020261C4 ; =0x0000094F
	mov r3, #0x0
	strb r3, [r0, r1]
	add r0, r2, #0x0
	pop {r3-r6}
	bx lr
	.balign 4
_020261BC: .word 0x00000928
_020261C0: .word 0x00000929
_020261C4: .word 0x0000094F

	thumb_func_start FUN_020261C8
FUN_020261C8: ; 0x020261C8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02025A20
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _020261E4
	add r1, r5, r0
	ldr r0, _020261E8 ; =0x00000928
	strb r4, [r1, r0]
	mov r0, #0x1
	pop {r3-r5, pc}
_020261E4:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_020261E8: .word 0x00000928

	thumb_func_start FUN_020261EC
FUN_020261EC: ; 0x020261EC
	push {r3-r7, lr}
	sub sp, #0x30
	add r5, r0, #0x0
	ldr r0, _02026238 ; =0x00000928
	str r1, [sp, #0x4]
	str r2, [sp, #0x0]
	add r0, r5, r0
	add r1, sp, #0x8
	mov r2, #0x28
	mov r4, #0x0
	bl MI_CpuCopy8
	ldr r2, [sp, #0x4]
	add r1, sp, #0x8
	add r0, r4, #0x0
	add r7, r1, r2
_0202620C:
	ldr r2, [sp, #0x4]
	cmp r0, r2
	beq _0202621C
	ldrb r6, [r1, #0x0]
	ldr r2, _02026238 ; =0x00000928
	add r3, r5, r4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_0202621C:
	ldr r2, [sp, #0x0]
	cmp r0, r2
	bne _0202622C
	ldrb r6, [r7, #0x0]
	ldr r2, _02026238 ; =0x00000928
	add r3, r5, r4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_0202622C:
	add r0, r0, #0x1
	add r1, r1, #0x1
	cmp r0, #0x28
	blt _0202620C
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_02026238: .word 0x00000928

	thumb_func_start FUN_0202623C
FUN_0202623C: ; 0x0202623C
	ldr r1, _02026254 ; =0x000008D8
	mov r3, #0x0
_02026240:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	beq _0202624E
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02026240
_0202624E:
	add r0, r3, #0x0
	bx lr
	nop
_02026254: .word 0x000008D8

	thumb_func_start FUN_02026258
FUN_02026258: ; 0x02026258
	add r1, r0, r1
	ldr r0, _02026260 ; =0x000008D8
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_02026260: .word 0x000008D8

	thumb_func_start FUN_02026264
FUN_02026264: ; 0x02026264
	push {r3-r6}
	ldr r2, _0202628C ; =0x000008D8
	add r3, r0, r1
	ldrb r2, [r3, r2]
	cmp r1, #0x27
	bge _02026280
	ldr r3, _02026290 ; =0x000008D9
	sub r4, r3, #0x1
_02026274:
	add r6, r0, r1
	ldrb r5, [r6, r3]
	add r1, r1, #0x1
	cmp r1, #0x27
	strb r5, [r6, r4]
	blt _02026274
_02026280:
	ldr r1, _02026294 ; =0x000008FF
	mov r3, #0x0
	strb r3, [r0, r1]
	add r0, r2, #0x0
	pop {r3-r6}
	bx lr
	.balign 4
_0202628C: .word 0x000008D8
_02026290: .word 0x000008D9
_02026294: .word 0x000008FF

	thumb_func_start FUN_02026298
FUN_02026298: ; 0x02026298
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02025A40
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _020262B4
	add r1, r5, r0
	ldr r0, _020262B8 ; =0x000008D8
	strb r4, [r1, r0]
	mov r0, #0x1
	pop {r3-r5, pc}
_020262B4:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_020262B8: .word 0x000008D8

	thumb_func_start FUN_020262BC
FUN_020262BC: ; 0x020262BC
	push {r3-r7, lr}
	sub sp, #0x30
	add r5, r0, #0x0
	ldr r0, _02026308 ; =0x000008D8
	str r1, [sp, #0x4]
	str r2, [sp, #0x0]
	add r0, r5, r0
	add r1, sp, #0x8
	mov r2, #0x28
	mov r4, #0x0
	bl MI_CpuCopy8
	ldr r2, [sp, #0x4]
	add r1, sp, #0x8
	add r0, r4, #0x0
	add r7, r1, r2
_020262DC:
	ldr r2, [sp, #0x4]
	cmp r0, r2
	beq _020262EC
	ldrb r6, [r1, #0x0]
	ldr r2, _02026308 ; =0x000008D8
	add r3, r5, r4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_020262EC:
	ldr r2, [sp, #0x0]
	cmp r0, r2
	bne _020262FC
	ldrb r6, [r7, #0x0]
	ldr r2, _02026308 ; =0x000008D8
	add r3, r5, r4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_020262FC:
	add r0, r0, #0x1
	add r1, r1, #0x1
	cmp r0, #0x28
	blt _020262DC
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_02026308: .word 0x000008D8

	thumb_func_start FUN_0202630C
FUN_0202630C: ; 0x0202630C
	push {r3-r7, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r6, r3, #0x0
	cmp r4, #0x40
	blt _0202631E
	bl ErrorHandling
_0202631E:
	ldr r0, _02026350 ; =0x0000010F
	add r1, r5, r4
	strb r7, [r1, r0]
	lsl r1, r4, #0x1
	add r1, r4, r1
	add r2, r0, #0x0
	add r1, r5, r1
	add r2, #0x40
	strb r6, [r1, r2]
	mov r2, #0xf
	lsl r2, r2, #0x8
	add r3, r6, #0x0
	and r3, r2
	asr r4, r3, #0x8
	ldr r3, [sp, #0x18]
	and r2, r3
	asr r2, r2, #0x4
	add r4, r4, r2
	add r2, r0, #0x0
	add r2, #0x41
	strb r4, [r1, r2]
	add r0, #0x42
	strb r3, [r1, r0]
	pop {r3-r7, pc}
	nop
_02026350: .word 0x0000010F

	thumb_func_start FUN_02026354
FUN_02026354: ; 0x02026354
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x40
	blt _02026362
	bl ErrorHandling
_02026362:
	ldr r0, _0202636C ; =0x0000010F
	add r1, r5, r4
	ldrb r0, [r1, r0]
	pop {r3-r5, pc}
	nop
_0202636C: .word 0x0000010F

	thumb_func_start FUN_02026370
FUN_02026370: ; 0x02026370
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x40
	blt _0202637E
	bl ErrorHandling
_0202637E:
	lsl r0, r4, #0x1
	add r0, r4, r0
	add r1, r5, r0
	ldr r0, _02026398 ; =0x0000014F
	ldrb r2, [r1, r0]
	add r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x8
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	pop {r3-r5, pc}
	.balign 4
_02026398: .word 0x0000014F

	thumb_func_start FUN_0202639C
FUN_0202639C: ; 0x0202639C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x40
	blt _020263AA
	bl ErrorHandling
_020263AA:
	lsl r0, r4, #0x1
	add r0, r4, r0
	add r1, r5, r0
	ldr r0, _020263C4 ; =0x00000151
	ldrb r2, [r1, r0]
	sub r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x4
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	pop {r3-r5, pc}
	.balign 4
_020263C4: .word 0x00000151

	thumb_func_start FUN_020263C8
FUN_020263C8: ; 0x020263C8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x40
	blt _020263D6
	bl ErrorHandling
_020263D6:
	ldr r0, _020263F0 ; =0x0000010F
	mov r1, #0x0
	add r2, r5, r4
	strb r1, [r2, r0]
	add r0, #0x40
	add r2, r5, r0
	lsl r0, r4, #0x1
	add r0, r4, r0
	add r0, r2, r0
	mov r2, #0x3
	bl MI_CpuFill8
	pop {r3-r5, pc}
	.balign 4
_020263F0: .word 0x0000010F

	thumb_func_start FUN_020263F4
FUN_020263F4: ; 0x020263F4
	push {r3-r7, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r6, r3, #0x0
	cmp r4, #0x10
	blt _02026406
	bl ErrorHandling
_02026406:
	lsl r2, r4, #0x1
	ldr r1, _02026440 ; =0x0000050C
	add r0, r5, r4
	add r2, r4, r2
	add r4, r5, r2
	add r2, r1, #0x0
	mov r5, #0xf
	strb r7, [r0, r1]
	add r2, #0x10
	strb r6, [r4, r2]
	lsl r5, r5, #0x8
	add r2, r6, #0x0
	and r2, r5
	asr r3, r2, #0x8
	ldr r2, [sp, #0x18]
	and r5, r2
	asr r5, r5, #0x4
	add r5, r3, r5
	add r3, r1, #0x0
	add r3, #0x11
	strb r5, [r4, r3]
	add r3, r1, #0x0
	add r3, #0x12
	strb r2, [r4, r3]
	ldr r2, [sp, #0x1c]
	add r1, #0x40
	strb r2, [r0, r1]
	pop {r3-r7, pc}
	nop
_02026440: .word 0x0000050C

	thumb_func_start FUN_02026444
FUN_02026444: ; 0x02026444
	add r1, r0, r1
	ldr r0, _0202644C ; =0x0000050C
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_0202644C: .word 0x0000050C

	thumb_func_start FUN_02026450
FUN_02026450: ; 0x02026450
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _0202646C ; =0x0000051C
	ldrb r2, [r1, r0]
	add r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x8
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_0202646C: .word 0x0000051C

	thumb_func_start FUN_02026470
FUN_02026470: ; 0x02026470
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _0202648C ; =0x0000051E
	ldrb r2, [r1, r0]
	sub r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x4
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_0202648C: .word 0x0000051E

	thumb_func_start FUN_02026490
FUN_02026490: ; 0x02026490
	add r1, r0, r1
	ldr r0, _02026498 ; =0x0000054C
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_02026498: .word 0x0000054C

	thumb_func_start FUN_0202649C
FUN_0202649C: ; 0x0202649C
	push {r3-r7, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r3, #0x0
	cmp r4, #0x64
	blt _020264AE
	bl ErrorHandling
_020264AE:
	ldr r1, _020264E8 ; =0x0000055C
	add r0, r5, r4
	strb r6, [r0, r1]
	lsl r1, r4, #0x1
	add r1, r4, r1
	add r4, r5, r1
	mov r5, #0xf
	lsl r5, r5, #0x8
	add r2, r7, #0x0
	and r2, r5
	asr r3, r2, #0x8
	ldr r2, [sp, #0x18]
	ldr r1, _020264EC ; =0x00000688
	and r5, r2
	asr r5, r5, #0x4
	add r5, r3, r5
	strb r7, [r4, r1]
	add r3, r1, #0x1
	strb r5, [r4, r3]
	add r3, r1, #0x2
	strb r2, [r4, r3]
	add r2, r1, #0x0
	ldr r3, [sp, #0x1c]
	sub r2, #0x64
	strb r3, [r0, r2]
	ldr r2, [sp, #0x20]
	sub r1, #0xc8
	strb r2, [r0, r1]
	pop {r3-r7, pc}
	.balign 4
_020264E8: .word 0x0000055C
_020264EC: .word 0x00000688

	thumb_func_start FUN_020264F0
FUN_020264F0: ; 0x020264F0
	add r1, r0, r1
	ldr r0, _020264F8 ; =0x0000055C
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_020264F8: .word 0x0000055C

	thumb_func_start FUN_020264FC
FUN_020264FC: ; 0x020264FC
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _02026518 ; =0x00000688
	ldrb r2, [r1, r0]
	add r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x8
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_02026518: .word 0x00000688

	thumb_func_start FUN_0202651C
FUN_0202651C: ; 0x0202651C
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _02026538 ; =0x0000068A
	ldrb r2, [r1, r0]
	sub r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x4
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_02026538: .word 0x0000068A

	thumb_func_start FUN_0202653C
FUN_0202653C: ; 0x0202653C
	add r1, r0, r1
	ldr r0, _02026544 ; =0x00000624
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_02026544: .word 0x00000624

	thumb_func_start FUN_02026548
FUN_02026548: ; 0x02026548
	add r1, r0, r1
	mov r0, #0x17
	lsl r0, r0, #0x6
	ldrb r0, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026554
FUN_02026554: ; 0x02026554
	push {r4-r7}
	ldr r3, _020265B0 ; =0x00000211
	add r7, r0, #0x0
	mov r12, r1
	mov r0, #0x0
	add r1, r7, #0x0
	sub r4, r3, #0x1
	sub r5, r3, #0x2
_02026564:
	ldrb r6, [r1, r5]
	cmp r6, #0x0
	bne _020265A0
	ldrb r6, [r1, r4]
	cmp r6, #0x0
	bne _020265A0
	ldrb r6, [r1, r3]
	cmp r6, #0x0
	bne _020265A0
	lsl r1, r0, #0x1
	add r1, r0, r1
	mov r5, #0xf
	ldr r4, _020265B4 ; =0x0000020F
	add r1, r7, r1
	mov r3, r12
	strb r3, [r1, r4]
	lsl r5, r5, #0x8
	mov r3, r12
	and r3, r5
	asr r6, r3, #0x8
	add r3, r2, #0x0
	and r3, r5
	asr r3, r3, #0x4
	add r5, r6, r3
	add r3, r4, #0x1
	strb r5, [r1, r3]
	add r3, r4, #0x2
	strb r2, [r1, r3]
	pop {r4-r7}
	bx lr
_020265A0:
	add r0, r0, #0x1
	add r1, r1, #0x3
	cmp r0, #0xff
	blt _02026564
	mov r0, #0x0
	pop {r4-r7}
	bx lr
	nop
_020265B0: .word 0x00000211
_020265B4: .word 0x0000020F

	thumb_func_start FUN_020265B8
FUN_020265B8: ; 0x020265B8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xff
	blt _020265C6
	bl ErrorHandling
_020265C6:
	ldr r0, _020265DC ; =0x0000020F
	mov r2, #0x3
	add r1, r5, r0
	lsl r0, r4, #0x1
	add r0, r4, r0
	add r0, r1, r0
	mov r1, #0x0
	bl MI_CpuFill8
	pop {r3-r5, pc}
	nop
_020265DC: .word 0x0000020F

	thumb_func_start FUN_020265E0
FUN_020265E0: ; 0x020265E0
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _020265FC ; =0x0000020F
	ldrb r2, [r1, r0]
	add r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x8
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_020265FC: .word 0x0000020F

	thumb_func_start FUN_02026600
FUN_02026600: ; 0x02026600
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _0202661C ; =0x00000211
	ldrb r2, [r1, r0]
	sub r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x4
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_0202661C: .word 0x00000211

	thumb_func_start FUN_02026620
FUN_02026620: ; 0x02026620
	mov r1, #0x9b
	lsl r1, r1, #0x4
	ldrb r0, [r0, r1]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	bne _02026630
	mov r0, #0x1
	bx lr
_02026630:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02026634
FUN_02026634: ; 0x02026634
	mov r2, #0x9b
	lsl r2, r2, #0x4
	ldrb r3, [r0, r2]
	mov r1, #0xf0
	bic r3, r1
	mov r1, #0x10
	orr r1, r3
	strb r1, [r0, r2]
	bx lr
	.balign 4

	thumb_func_start FUN_02026648
FUN_02026648: ; 0x02026648
	mov r1, #0x9b
	lsl r1, r1, #0x4
	ldrb r0, [r0, r1]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	bx lr

	thumb_func_start FUN_02026654
FUN_02026654: ; 0x02026654
	mov r2, #0x9b
	lsl r2, r2, #0x4
	ldrb r3, [r0, r2]
	mov r1, #0xf
	bic r3, r1
	strb r3, [r0, r2]
	bx lr
	.balign 4

	thumb_func_start FUN_02026664
FUN_02026664: ; 0x02026664
	push {r3-r4}
	cmp r1, #0x2c
	blt _0202667E
	cmp r1, #0x3b
	bgt _0202667E
	ldr r2, _02026684 ; =0x0000080C
	mov r3, #0x1
	sub r1, #0x2c
	ldr r4, [r0, r2]
	lsl r3, r1
	add r1, r4, #0x0
	orr r1, r3
	str r1, [r0, r2]
_0202667E:
	pop {r3-r4}
	bx lr
	nop
_02026684: .word 0x0000080C

	thumb_func_start FUN_02026688
FUN_02026688: ; 0x02026688
	cmp r1, #0x2c
	blt _02026690
	cmp r1, #0x3b
	ble _02026694
_02026690:
	mov r0, #0x1
	bx lr
_02026694:
	ldr r2, _020266AC ; =0x0000080C
	sub r1, #0x2c
	ldr r3, [r0, r2]
	mov r0, #0x1
	add r2, r0, #0x0
	lsl r2, r1
	add r1, r3, #0x0
	tst r1, r2
	beq _020266A8
	mov r0, #0x0
_020266A8:
	bx lr
	nop
_020266AC: .word 0x0000080C

	thumb_func_start FUN_020266B0
FUN_020266B0: ; 0x020266B0
	ldr r1, _020266C4 ; =0x000009AF
	ldrb r2, [r0, r1]
	cmp r2, #0x63
	blo _020266BE
	mov r2, #0x0
	strb r2, [r0, r1]
	bx lr
_020266BE:
	add r2, r2, #0x1
	strb r2, [r0, r1]
	bx lr
	.balign 4
_020266C4: .word 0x000009AF

	thumb_func_start FUN_020266C8
FUN_020266C8: ; 0x020266C8
	ldr r1, _020266D0 ; =0x000009AF
	ldrb r0, [r0, r1]
	bx lr
	nop
_020266D0: .word 0x000009AF

	thumb_func_start FUN_020266D4
FUN_020266D4: ; 0x020266D4
	ldr r3, _020266DC ; =MI_CpuFill8
	mov r1, #0x0
	mov r2, #0x94
	bx r3
	.balign 4
_020266DC: .word MI_CpuFill8

	thumb_func_start FUN_020266E0
FUN_020266E0: ; 0x020266E0
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0x2d
	bl MI_CpuFill8
	add r0, r4, #0x0
	add r0, #0x2d
	mov r1, #0x0
	mov r2, #0x20
	bl MI_CpuFill8
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x8c
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x8e
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x90
	strb r1, [r0, #0x0]
	add r4, #0x91
	strb r1, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02026714
FUN_02026714: ; 0x02026714
	mov r1, #0x0
	add r0, #0x91
	strb r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0202671C
FUN_0202671C: ; 0x0202671C
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r7, r2, #0x0
	add r6, r3, #0x0
	cmp r4, #0x20
	blt _0202672E
	bl ErrorHandling
_0202672E:
	cmp r6, #0x20
	blt _02026736
	bl ErrorHandling
_02026736:
	ldr r0, [sp, #0x18]
	cmp r0, #0x20
	blt _02026740
	bl ErrorHandling
_02026740:
	cmp r5, #0x0
	bne _02026748
	bl ErrorHandling
_02026748:
	cmp r4, #0x0
	beq _02026774
	cmp r4, #0x10
	bge _02026762
	sub r1, r4, #0x1
	lsl r0, r1, #0x1
	add r0, r1, r0
	strb r6, [r5, r0]
	ldr r1, [sp, #0x18]
	add r0, r5, r0
	strb r1, [r0, #0x1]
	strb r7, [r0, #0x2]
	pop {r3-r7, pc}
_02026762:
	sub r4, #0x10
	lsl r2, r4, #0x1
	add r0, r5, r2
	add r0, #0x2d
	strb r6, [r0, #0x0]
	add r0, r5, r2
	ldr r1, [sp, #0x18]
	add r0, #0x2e
	strb r1, [r0, #0x0]
_02026774:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02026778
FUN_02026778: ; 0x02026778
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	add r4, r3, #0x0
	bl FUN_020267C4
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r3, r7, #0x0
	str r4, [sp, #0x0]
	bl FUN_0202671C
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02026798
FUN_02026798: ; 0x02026798
	add r0, #0x88
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	cmp r0, #0x32
	blt _020267A8
	mov r0, #0x5
	bx lr
_020267A8:
	cmp r0, #0xa
	blt _020267B0
	mov r0, #0x4
	bx lr
_020267B0:
	cmp r0, #0x3
	blt _020267B8
	mov r0, #0x3
	bx lr
_020267B8:
	cmp r0, #0x1
	blt _020267C0
	mov r0, #0x2
	bx lr
_020267C0:
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_020267C4
FUN_020267C4: ; 0x020267C4
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x20
	blt _020267D2
	bl ErrorHandling
_020267D2:
	cmp r5, #0x0
	bne _020267DE
	add r0, r4, #0x0
	bl FUN_02026798
	pop {r3-r5, pc}
_020267DE:
	cmp r5, #0x10
	bge _020267EE
	sub r1, r5, #0x1
	lsl r0, r1, #0x1
	add r0, r1, r0
	add r0, r4, r0
	ldrb r0, [r0, #0x2]
	pop {r3-r5, pc}
_020267EE:
	sub r5, #0x10
	lsl r1, r5, #0x1
	add r0, r4, r1
	add r0, #0x2d
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202680A
	add r0, r4, r1
	add r0, #0x2e
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202680A
	mov r0, #0x6
	pop {r3-r5, pc}
_0202680A:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02026810
FUN_02026810: ; 0x02026810
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x20
	blt _0202681E
	bl ErrorHandling
_0202681E:
	cmp r5, #0x0
	bne _02026826
	mov r0, #0xf
	pop {r3-r5, pc}
_02026826:
	cmp r5, #0x10
	bge _02026834
	sub r1, r5, #0x1
	lsl r0, r1, #0x1
	add r0, r1, r0
	ldrb r0, [r4, r0]
	pop {r3-r5, pc}
_02026834:
	sub r5, #0x10
	lsl r0, r5, #0x1
	add r0, r4, r0
	add r0, #0x2d
	ldrb r0, [r0, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02026840
FUN_02026840: ; 0x02026840
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x20
	blt _0202684E
	bl ErrorHandling
_0202684E:
	cmp r5, #0x0
	bne _02026856
	mov r0, #0xc
	pop {r3-r5, pc}
_02026856:
	cmp r5, #0x10
	bge _02026866
	sub r1, r5, #0x1
	lsl r0, r1, #0x1
	add r0, r1, r0
	add r0, r4, r0
	ldrb r0, [r0, #0x1]
	pop {r3-r5, pc}
_02026866:
	sub r5, #0x10
	lsl r0, r5, #0x1
	add r0, r4, r0
	add r0, #0x2e
	ldrb r0, [r0, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02026874
FUN_02026874: ; 0x02026874
	add r0, #0x88
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	cmp r0, #0x32
	blo _02026884
	mov r0, #0x0
	bx lr
_02026884:
	cmp r0, #0xa
	blo _0202688C
	mov r0, #0x6
	bx lr
_0202688C:
	cmp r0, #0x3
	blo _02026894
	mov r0, #0xb
	bx lr
_02026894:
	cmp r0, #0x1
	blo _0202689C
	mov r0, #0xf
	bx lr
_0202689C:
	mov r0, #0x10
	bx lr

	thumb_func_start FUN_020268A0
FUN_020268A0: ; 0x020268A0
	add r0, #0x88
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	cmp r0, #0x32
	blo _020268B0
	mov r0, #0xf
	bx lr
_020268B0:
	cmp r0, #0xa
	blo _020268B8
	mov r0, #0xf
	bx lr
_020268B8:
	cmp r0, #0x3
	blo _020268C0
	mov r0, #0xf
	bx lr
_020268C0:
	cmp r0, #0x1
	blo _020268C8
	mov r0, #0xc
	bx lr
_020268C8:
	mov r0, #0xa
	bx lr

	thumb_func_start FUN_020268CC
FUN_020268CC: ; 0x020268CC
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_020268D4
FUN_020268D4: ; 0x020268D4
	push {r3, lr}
	bl FUN_020269A0
	cmp r0, #0x4
	bne _020268E2
	mov r0, #0x1
	pop {r3, pc}
_020268E2:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020268E8
FUN_020268E8: ; 0x020268E8
	ldr r3, [r0, #0x0]
	ldr r2, _020268F8 ; =0xFFF00000
	and r3, r2
	ldr r2, _020268FC ; =0x000FFFFF
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020268F8: .word 0xFFF00000
_020268FC: .word 0x000FFFFF

	thumb_func_start FUN_02026900
FUN_02026900: ; 0x02026900
	ldr r0, [r0, #0x4]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026908
FUN_02026908: ; 0x02026908
	push {r3-r4}
	ldr r2, [r0, #0x4]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _0202692C ; =0x000F423F
	cmp r4, r1
	bhs _02026926
	ldr r1, _02026930 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026934 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x4]
_02026926:
	pop {r3-r4}
	bx lr
	nop
_0202692C: .word 0x000F423F
_02026930: .word 0xFFF00000
_02026934: .word 0x000FFFFF

	thumb_func_start FUN_02026938
FUN_02026938: ; 0x02026938
	ldr r0, [r0, #0x8]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026940
FUN_02026940: ; 0x02026940
	push {r3-r4}
	ldr r2, [r0, #0x8]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026964 ; =0x000F423F
	cmp r4, r1
	bhs _0202695E
	ldr r1, _02026968 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _0202696C ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x8]
_0202695E:
	pop {r3-r4}
	bx lr
	nop
_02026964: .word 0x000F423F
_02026968: .word 0xFFF00000
_0202696C: .word 0x000FFFFF

	thumb_func_start FUN_02026970
FUN_02026970: ; 0x02026970
	push {r3-r4}
	ldr r2, [r0, #0xc]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026994 ; =0x000F423F
	cmp r4, r1
	bhs _0202698E
	ldr r1, _02026998 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _0202699C ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0xc]
_0202698E:
	pop {r3-r4}
	bx lr
	nop
_02026994: .word 0x000F423F
_02026998: .word 0xFFF00000
_0202699C: .word 0x000FFFFF

	thumb_func_start FUN_020269A0
FUN_020269A0: ; 0x020269A0
	ldr r0, [r0, #0x38]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	cmp r0, #0x32
	blt _020269AE
	mov r0, #0x4
	bx lr
_020269AE:
	cmp r0, #0xa
	blt _020269B6
	mov r0, #0x3
	bx lr
_020269B6:
	cmp r0, #0x3
	blt _020269BE
	mov r0, #0x2
	bx lr
_020269BE:
	cmp r0, #0x1
	blt _020269C6
	mov r0, #0x1
	bx lr
_020269C6:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_020269CC
FUN_020269CC: ; 0x020269CC
	ldr r0, [r0, #0x38]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_020269D4
FUN_020269D4: ; 0x020269D4
	push {r3-r4}
	ldr r2, [r0, #0x38]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _020269F8 ; =0x000F423F
	cmp r4, r1
	bhs _020269F2
	ldr r1, _020269FC ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026A00 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x38]
_020269F2:
	pop {r3-r4}
	bx lr
	nop
_020269F8: .word 0x000F423F
_020269FC: .word 0xFFF00000
_02026A00: .word 0x000FFFFF

	thumb_func_start FUN_02026A04
FUN_02026A04: ; 0x02026A04
	ldr r0, [r0, #0x10]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026A0C
FUN_02026A0C: ; 0x02026A0C
	push {r4-r5}
	cmp r1, #0x0
	ble _02026A2C
	ldr r4, [r0, #0x10]
	lsl r2, r4, #0xc
	lsr r5, r2, #0xc
	ldr r2, _02026A44 ; =0x000F423F
	sub r3, r2, r1
	cmp r5, r3
	bls _02026A2C
	ldr r1, _02026A48 ; =0xFFF00000
	and r1, r4
	orr r1, r2
	str r1, [r0, #0x10]
	pop {r4-r5}
	bx lr
_02026A2C:
	ldr r3, [r0, #0x10]
	ldr r2, _02026A48 ; =0xFFF00000
	and r2, r3
	lsl r3, r3, #0xc
	lsr r3, r3, #0xc
	add r3, r3, r1
	ldr r1, _02026A4C ; =0x000FFFFF
	and r1, r3
	orr r1, r2
	str r1, [r0, #0x10]
	pop {r4-r5}
	bx lr
	.balign 4
_02026A44: .word 0x000F423F
_02026A48: .word 0xFFF00000
_02026A4C: .word 0x000FFFFF

	thumb_func_start FUN_02026A50
FUN_02026A50: ; 0x02026A50
	ldr r0, [r0, #0x14]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026A58
FUN_02026A58: ; 0x02026A58
	push {r4-r5}
	cmp r1, #0x0
	ble _02026A78
	ldr r4, [r0, #0x14]
	lsl r2, r4, #0xc
	lsr r5, r2, #0xc
	ldr r2, _02026A90 ; =0x000F423F
	sub r3, r2, r1
	cmp r5, r3
	bls _02026A78
	ldr r1, _02026A94 ; =0xFFF00000
	and r1, r4
	orr r1, r2
	str r1, [r0, #0x14]
	pop {r4-r5}
	bx lr
_02026A78:
	ldr r3, [r0, #0x14]
	ldr r2, _02026A94 ; =0xFFF00000
	and r2, r3
	lsl r3, r3, #0xc
	lsr r3, r3, #0xc
	add r3, r3, r1
	ldr r1, _02026A98 ; =0x000FFFFF
	and r1, r3
	orr r1, r2
	str r1, [r0, #0x14]
	pop {r4-r5}
	bx lr
	.balign 4
_02026A90: .word 0x000F423F
_02026A94: .word 0xFFF00000
_02026A98: .word 0x000FFFFF

	thumb_func_start FUN_02026A9C
FUN_02026A9C: ; 0x02026A9C
	push {r4-r5}
	cmp r1, #0x0
	ble _02026ABC
	ldr r4, [r0, #0x18]
	lsl r2, r4, #0xc
	lsr r5, r2, #0xc
	ldr r2, _02026AD4 ; =0x000F423F
	sub r3, r2, r1
	cmp r5, r3
	bls _02026ABC
	ldr r1, _02026AD8 ; =0xFFF00000
	and r1, r4
	orr r1, r2
	str r1, [r0, #0x18]
	pop {r4-r5}
	bx lr
_02026ABC:
	ldr r3, [r0, #0x18]
	ldr r2, _02026AD8 ; =0xFFF00000
	and r2, r3
	lsl r3, r3, #0xc
	lsr r3, r3, #0xc
	add r3, r3, r1
	ldr r1, _02026ADC ; =0x000FFFFF
	and r1, r3
	orr r1, r2
	str r1, [r0, #0x18]
	pop {r4-r5}
	bx lr
	.balign 4
_02026AD4: .word 0x000F423F
_02026AD8: .word 0xFFF00000
_02026ADC: .word 0x000FFFFF

	thumb_func_start FUN_02026AE0
FUN_02026AE0: ; 0x02026AE0
	ldr r0, [r0, #0x1c]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026AE8
FUN_02026AE8: ; 0x02026AE8
	push {r3-r4}
	ldr r2, [r0, #0x1c]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026B0C ; =0x000F423F
	cmp r4, r1
	bhs _02026B06
	ldr r1, _02026B10 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026B14 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x1c]
_02026B06:
	pop {r3-r4}
	bx lr
	nop
_02026B0C: .word 0x000F423F
_02026B10: .word 0xFFF00000
_02026B14: .word 0x000FFFFF

	thumb_func_start FUN_02026B18
FUN_02026B18: ; 0x02026B18
	ldr r0, [r0, #0x20]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026B20
FUN_02026B20: ; 0x02026B20
	push {r3-r4}
	ldr r2, [r0, #0x20]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026B44 ; =0x000F423F
	cmp r4, r1
	bhs _02026B3E
	ldr r1, _02026B48 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026B4C ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x20]
_02026B3E:
	pop {r3-r4}
	bx lr
	nop
_02026B44: .word 0x000F423F
_02026B48: .word 0xFFF00000
_02026B4C: .word 0x000FFFFF

	thumb_func_start FUN_02026B50
FUN_02026B50: ; 0x02026B50
	ldr r0, [r0, #0x24]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026B58
FUN_02026B58: ; 0x02026B58
	push {r3-r4}
	ldr r2, [r0, #0x24]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026B7C ; =0x000F423F
	cmp r4, r1
	bhs _02026B76
	ldr r1, _02026B80 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026B84 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x24]
_02026B76:
	pop {r3-r4}
	bx lr
	nop
_02026B7C: .word 0x000F423F
_02026B80: .word 0xFFF00000
_02026B84: .word 0x000FFFFF

	thumb_func_start FUN_02026B88
FUN_02026B88: ; 0x02026B88
	ldr r0, [r0, #0x28]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026B90
FUN_02026B90: ; 0x02026B90
	push {r3-r4}
	ldr r2, [r0, #0x28]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026BB4 ; =0x000F423F
	cmp r4, r1
	bhs _02026BAE
	ldr r1, _02026BB8 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026BBC ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x28]
_02026BAE:
	pop {r3-r4}
	bx lr
	nop
_02026BB4: .word 0x000F423F
_02026BB8: .word 0xFFF00000
_02026BBC: .word 0x000FFFFF

	thumb_func_start FUN_02026BC0
FUN_02026BC0: ; 0x02026BC0
	ldr r0, [r0, #0x2c]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026BC8
FUN_02026BC8: ; 0x02026BC8
	push {r3-r4}
	ldr r2, [r0, #0x2c]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026BEC ; =0x000F423F
	cmp r4, r1
	bhs _02026BE6
	ldr r1, _02026BF0 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026BF4 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x2c]
_02026BE6:
	pop {r3-r4}
	bx lr
	nop
_02026BEC: .word 0x000F423F
_02026BF0: .word 0xFFF00000
_02026BF4: .word 0x000FFFFF

	thumb_func_start FUN_02026BF8
FUN_02026BF8: ; 0x02026BF8
	ldr r0, [r0, #0x30]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026C00
FUN_02026C00: ; 0x02026C00
	push {r3-r4}
	ldr r2, [r0, #0x30]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026C24 ; =0x000F423F
	cmp r4, r1
	bhs _02026C1E
	ldr r1, _02026C28 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026C2C ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x30]
_02026C1E:
	pop {r3-r4}
	bx lr
	nop
_02026C24: .word 0x000F423F
_02026C28: .word 0xFFF00000
_02026C2C: .word 0x000FFFFF

	thumb_func_start FUN_02026C30
FUN_02026C30: ; 0x02026C30
	ldr r0, [r0, #0x34]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026C38
FUN_02026C38: ; 0x02026C38
	push {r3-r4}
	ldr r2, [r0, #0x34]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026C5C ; =0x000F423F
	cmp r4, r1
	bhs _02026C56
	ldr r1, _02026C60 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026C64 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x34]
_02026C56:
	pop {r3-r4}
	bx lr
	nop
_02026C5C: .word 0x000F423F
_02026C60: .word 0xFFF00000
_02026C64: .word 0x000FFFFF

	thumb_func_start FUN_02026C68
FUN_02026C68: ; 0x02026C68
	push {r3-r4}
	add r4, r0, #0x0
	add r4, #0x8c
	strh r1, [r4, #0x0]
	add r1, r0, #0x0
	add r1, #0x8e
	strh r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x90
	strb r3, [r1, #0x0]
	mov r1, #0x1
	add r0, #0x91
	strb r1, [r0, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_02026C88
FUN_02026C88: ; 0x02026C88
	add r0, #0x8c
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026C90
FUN_02026C90: ; 0x02026C90
	add r0, #0x8e
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026C98
FUN_02026C98: ; 0x02026C98
	add r0, #0x90
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026CA0
FUN_02026CA0: ; 0x02026CA0
	add r0, #0x91
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026CA8
FUN_02026CA8: ; 0x02026CA8
	ldr r3, _02026CB0 ; =SavArray_get
	mov r1, #0xc
	bx r3
	nop
_02026CB0: .word SavArray_get

	thumb_func_start FUN_02026CB4
FUN_02026CB4: ; 0x02026CB4
	push {r3, lr}
	mov r1, #0xc
	bl SavArray_get
	add r0, #0x50
	pop {r3, pc}

	thumb_func_start FUN_02026CC0
FUN_02026CC0: ; 0x02026CC0
	add r0, #0x50
	bx lr

	thumb_func_start FUN_02026CC4
FUN_02026CC4: ; 0x02026CC4
	ldr r3, _02026CCC ; =SavArray_get
	mov r1, #0xc
	bx r3
	nop
_02026CCC: .word SavArray_get
