	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD63_021DAE5C
MOD63_021DAE5C: ; 0x021DAE5C
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _021DAE88 ; =MOD63_021DBEAC
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_0201D040
	mov r0, #1
	mov r1, #0x4c
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021DAE88: .word MOD63_021DBEAC
	thumb_func_end MOD63_021DAE5C

	thumb_func_start MOD63_021DAE8C
MOD63_021DAE8C: ; 0x021DAE8C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x2c
	add r4, r1, #0
	mov r1, #0
	add r5, r0, #0
	str r1, [sp]
	sub r0, r1, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r6, r2, #0
	str r1, [sp, #0xc]
	mov r2, #0x4b
	str r1, [sp, #0x10]
	lsl r2, r2, #2
	ldr r0, [r5, r2]
	add r3, r1, #0
	str r0, [sp, #0x14]
	add r0, r2, #4
	ldr r0, [r5, r0]
	str r0, [sp, #0x18]
	add r0, r2, #0
	add r0, #8
	ldr r0, [r5, r0]
	add r2, #0xc
	str r0, [sp, #0x1c]
	ldr r0, [r5, r2]
	add r2, r1, #0
	str r0, [sp, #0x20]
	str r1, [sp, #0x24]
	str r1, [sp, #0x28]
	add r0, r6, #0
	bl FUN_02008AA4
	ldr r0, [r5]
	mov r1, #0
	str r0, [r4]
	str r6, [r4, #4]
	str r1, [r4, #8]
	str r1, [r4, #0xc]
	mov r0, #1
	str r1, [r4, #0x10]
	lsl r0, r0, #0xc
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	strh r1, [r4, #0x20]
	mov r0, #1
	str r0, [r4, #0x24]
	str r0, [r4, #0x28]
	mov r0, #0x4c
	str r0, [r4, #0x2c]
	add sp, #0x2c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD63_021DAE8C

	thumb_func_start MOD63_021DAEF8
MOD63_021DAEF8: ; 0x021DAEF8
	push {r4, lr}
	mov r1, #0x7d
	mov r0, #0x4c
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x7d
	add r4, r0, #0
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	add r0, r4, #0
	bl MOD63_021DAFEC
	add r0, r4, #0
	bl MOD63_021DB150
	add r0, r4, #0
	pop {r4, pc}
	thumb_func_end MOD63_021DAEF8

	thumb_func_start MOD63_021DAF20
MOD63_021DAF20: ; 0x021DAF20
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x4c
	mov r1, #8
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0xc
	add r6, r5, #0
	mul r6, r0
	mov r0, #0x4c
	add r1, r6, #0
	bl AllocFromHeap
	mov r1, #0
	add r2, r6, #0
	str r0, [r4, #4]
	bl memset
	str r5, [r4]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD63_021DAF20

	thumb_func_start MOD63_021DAF4C
MOD63_021DAF4C: ; 0x021DAF4C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5]
	mov r6, #0
	cmp r0, #0
	ble _021DAF72
	add r4, r6, #0
_021DAF5A:
	ldr r0, [r5, #4]
	add r0, r0, r4
	ldr r0, [r0, #8]
	cmp r0, #0
	beq _021DAF68
	bl FUN_0200CAB4
_021DAF68:
	ldr r0, [r5]
	add r6, r6, #1
	add r4, #0xc
	cmp r6, r0
	blt _021DAF5A
_021DAF72:
	ldr r0, [r5, #4]
	bl FreeToHeap
	add r0, r5, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
	thumb_func_end MOD63_021DAF4C

	thumb_func_start MOD63_021DAF80
MOD63_021DAF80: ; 0x021DAF80
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	cmp r4, r0
	blt _021DAF90
	bl ErrorHandling
_021DAF90:
	mov r0, #0xc
	ldr r1, [r5, #4]
	mul r0, r4
	add r0, r1, r0
	add r0, r0, #4
	pop {r3, r4, r5, pc}
	thumb_func_end MOD63_021DAF80

	thumb_func_start MOD63_021DAF9C
MOD63_021DAF9C: ; 0x021DAF9C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl MOD63_021DB108
	mov r6, #0x73
	mov r4, #0
	lsl r6, r6, #2
_021DAFAA:
	lsl r0, r4, #4
	add r0, r5, r0
	ldr r0, [r0, r6]
	cmp r0, #0
	beq _021DAFB8
	bl FUN_0200CAB4
_021DAFB8:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #3
	blo _021DAFAA
	mov r6, #0x55
	mov r4, #0
	mov r7, #0xc
	lsl r6, r6, #2
_021DAFCA:
	add r0, r4, #0
	mul r0, r7
	add r0, r5, r0
	ldr r0, [r0, r6]
	cmp r0, #0
	beq _021DAFDA
	bl FUN_0200CAB4
_021DAFDA:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0xa
	blo _021DAFCA
	add r0, r5, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD63_021DAF9C

	thumb_func_start MOD63_021DAFEC
MOD63_021DAFEC: ; 0x021DAFEC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	add r7, r0, #0
	add r3, r1, #0
	ldr r0, _021DB0FC ; =0xFFCFFFEF
	mov r1, #0x10
	and r3, r0
	orr r3, r1
	str r3, [r2]
	ldr r3, _021DB100 ; =0x04001000
	ldr r2, [r3]
	and r0, r2
	orr r0, r1
	str r0, [r3]
	bl MOD63_021DAE5C
	bl NNS_G2dInitOamManagerModule
	mov r0, #0
	str r0, [sp]
	mov r1, #0x80
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x4c
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	mov r0, #0xa
	add r1, r7, #4
	mov r2, #0x4c
	bl FUN_02008C9C
	ldr r4, _021DB104 ; =MOD63_021DBEBC
	str r0, [r7]
	mov r6, #0
	add r5, r7, #0
_021DB040:
	ldrb r0, [r4]
	add r1, r6, #0
	mov r2, #0x4c
	bl FUN_02008DEC
	mov r1, #0x4b
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r6, r6, #1
	add r4, r4, #1
	add r5, r5, #4
	cmp r6, #4
	blt _021DB040
	mov r3, #0
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe0
	ldr r0, [r7, r0]
	mov r1, #0x80
	mov r2, #4
	bl FUN_02008F34
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [r7, r1]
	mov r3, #0
	str r3, [sp]
	mov r2, #3
	str r2, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x4c
	str r0, [sp, #0xc]
	add r0, #0xe4
	ldr r0, [r7, r0]
	mov r1, #0x80
	bl FUN_02008FEC
	mov r1, #5
	lsl r1, r1, #6
	str r0, [r7, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xe8
	ldr r0, [r7, r0]
	mov r1, #0x80
	mov r2, #5
	bl FUN_020090AC
	mov r1, #0x51
	lsl r1, r1, #2
	str r0, [r7, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x4c
	str r0, [sp, #8]
	add r0, #0xec
	ldr r0, [r7, r0]
	mov r1, #0x80
	mov r2, #6
	bl FUN_020090AC
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r7, r1]
	sub r1, #0xc
	ldr r0, [r7, r1]
	bl FUN_02009A50
	mov r0, #5
	lsl r0, r0, #6
	ldr r0, [r7, r0]
	bl FUN_02009CF0
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021DB0FC: .word 0xFFCFFFEF
_021DB100: .word 0x04001000
_021DB104: .word MOD63_021DBEBC
	thumb_func_end MOD63_021DAFEC

	thumb_func_start MOD63_021DB108
MOD63_021DB108: ; 0x021DB108
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x4f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009C0C
	mov r0, #5
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	bl FUN_02009E04
	mov r6, #0x4b
	mov r4, #0
	lsl r6, r6, #2
_021DB126:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, r6]
	bl FUN_02008E2C
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021DB126
	ldr r0, [r5]
	bl FUN_0201FD58
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD63_021DB108

	thumb_func_start MOD63_021DB150
MOD63_021DB150: ; 0x021DB150
	push {r4, r5, r6, r7, lr}
	sub sp, #0x54
	add r7, r0, #0
	mov r6, #0
	add r4, r6, #0
	add r5, r7, #0
_021DB15C:
	add r0, r7, #0
	add r1, sp, #0
	add r2, sp, #0x30
	bl MOD63_021DAE8C
	add r0, sp, #0
	str r4, [sp, #8]
	str r4, [sp, #0xc]
	bl FUN_0201FE94
	mov r1, #0x15
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200BC
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #2
	lsl r0, r0, #0xc
	add r6, r6, #1
	add r4, r4, r0
	add r5, #0xc
	cmp r6, #0xa
	blt _021DB15C
	add sp, #0x54
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD63_021DB150

	thumb_func_start MOD63_021DB1A0
MOD63_021DB1A0: ; 0x021DB1A0
	ldr r3, _021DB1A8 ; =FUN_0201FDEC
	ldr r0, [r0]
	bx r3
	nop
_021DB1A8: .word FUN_0201FDEC
	thumb_func_end MOD63_021DB1A0

	thumb_func_start MOD63_021DB1AC
MOD63_021DB1AC: ; 0x021DB1AC
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	cmp r1, #0xb4
	bne _021DB1CE
	mov r2, #3
	str r2, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #0x71
	lsl r0, r0, #2
	add r0, r4, r0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD63_021DB1F8
	b _021DB1E8
_021DB1CE:
	ldr r0, _021DB1F4 ; =0x0000011D
	cmp r1, r0
	bne _021DB1E8
	mov r2, #3
	add r0, #0xb7
	str r2, [sp]
	mov r1, #1
	str r1, [sp, #4]
	add r0, r4, r0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD63_021DB1F8
_021DB1E8:
	add r0, r4, #0
	bl MOD63_021DB1A0
	add sp, #8
	pop {r4, pc}
	nop
_021DB1F4: .word 0x0000011D
	thumb_func_end MOD63_021DB1AC

	thumb_func_start MOD63_021DB1F8
MOD63_021DB1F8: ; 0x021DB1F8
	push {r4, lr}
	add r4, r0, #0
	strb r2, [r4]
	ldr r2, _021DB228 ; =0xFFFFFFF8
	strb r3, [r4, #1]
	add r2, sp
	ldrb r0, [r2, #0x10]
	strb r0, [r4, #2]
	mov r0, #0
	strb r0, [r4, #4]
	strb r0, [r4, #3]
	mov r0, #0x53
	lsl r0, r0, #2
	add r0, r1, r0
	str r0, [r4, #0xc]
	ldrb r0, [r2, #0x14]
	add r1, r4, #0
	mov r2, #0xa
	strb r0, [r4, #5]
	ldr r0, _021DB22C ; =MOD63_021DB2F8
	bl FUN_0200CA44
	str r0, [r4, #8]
	pop {r4, pc}
	.align 2, 0
_021DB228: .word 0xFFFFFFF8
_021DB22C: .word MOD63_021DB2F8
	thumb_func_end MOD63_021DB1F8

	thumb_func_start MOD63_021DB230
MOD63_021DB230: ; 0x021DB230
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r1, #0
	str r0, [sp]
	cmp r2, #0
	bne _021DB240
	mov r7, #0x40
	b _021DB242
_021DB240:
	mov r7, #0x20
_021DB242:
	mov r5, #0
	cmp r6, #0
	bls _021DB2BE
_021DB248:
	ldr r0, [sp]
	mov r1, #0xa
	bl MOD63_021DB2C8
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FUN_0202011C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #4
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r2, r0, #0x19
	sub r2, r2, r1
	mov r0, #0x19
	ror r2, r0
	add r0, r1, r2
	add r0, #0x40
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	bl LCRandom
	lsr r1, r0, #0x1f
	lsl r2, r0, #0x1a
	sub r2, r2, r1
	mov r0, #0x1a
	ror r2, r0
	add r0, r1, r2
	add r0, r7, r0
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	add r1, sp, #4
	bl FUN_02020044
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, _021DB2C4 ; =MOD63_021DB334
	add r1, r4, #0
	mov r2, #0x14
	bl FUN_0200CA44
	str r0, [r4, #8]
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, r6
	blo _021DB248
_021DB2BE:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DB2C4: .word MOD63_021DB334
	thumb_func_end MOD63_021DB230

	thumb_func_start MOD63_021DB2C8
MOD63_021DB2C8: ; 0x021DB2C8
	push {r4, lr}
	mov r4, #0
	mov r2, #0xc
_021DB2CE:
	add r1, r4, #0
	mul r1, r2
	add r3, r0, r1
	ldrb r1, [r0, r1]
	cmp r1, #0
	bne _021DB2E6
	mov r0, #1
	strb r0, [r3]
	mov r0, #0
	strb r0, [r3, #1]
	add r0, r3, #0
	pop {r4, pc}
_021DB2E6:
	add r1, r4, #1
	lsl r1, r1, #0x18
	lsr r4, r1, #0x18
	cmp r4, #0xa
	blo _021DB2CE
	bl ErrorHandling
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD63_021DB2C8

	thumb_func_start MOD63_021DB2F8
MOD63_021DB2F8: ; 0x021DB2F8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4, #4]
	add r5, r0, #0
	add r0, r1, #1
	strb r0, [r4, #4]
	ldrb r0, [r4, #1]
	cmp r1, r0
	blo _021DB330
	ldrb r1, [r4]
	ldrb r2, [r4, #5]
	ldr r0, [r4, #0xc]
	bl MOD63_021DB230
	mov r0, #0
	strb r0, [r4, #4]
	ldrb r0, [r4, #3]
	add r0, r0, #1
	strb r0, [r4, #3]
	ldrb r1, [r4, #3]
	ldrb r0, [r4, #2]
	cmp r1, r0
	blo _021DB330
	add r0, r5, #0
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #8]
_021DB330:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021DB2F8

	thumb_func_start MOD63_021DB334
MOD63_021DB334: ; 0x021DB334
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	str r0, [r3]
	mov r0, #3
	ldr r1, [sp, #4]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #4]
	ldr r0, [r4, #4]
	add r1, r2, #0
	bl FUN_02020044
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	ldrb r0, [r4, #1]
	cmp r0, #0x50
	blo _021DB388
	add r0, r5, #0
	bl FUN_0200CAB4
	mov r1, #0
	str r1, [r4, #8]
	strb r1, [r4]
	ldr r0, [r4, #4]
	bl FUN_020200BC
	ldr r0, [r4, #4]
	mov r1, #0
	bl FUN_020200A0
_021DB388:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD63_021DB334

	thumb_func_start MOD63_021DB38C
MOD63_021DB38C: ; 0x021DB38C
	ldr r3, _021DB394 ; =MOD63_021DB398
	mov r1, #2
	bx r3
	nop
_021DB394: .word MOD63_021DB398
	thumb_func_end MOD63_021DB38C

	thumb_func_start MOD63_021DB398
MOD63_021DB398: ; 0x021DB398
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r0, #0
	ldr r0, [r6, #4]
	add r7, r1, #0
	str r0, [sp]
	ldr r5, _021DB418 ; =0x00000000
	beq _021DB414
_021DB3A8:
	ldr r0, [sp]
	ldr r1, [r6]
	bl MOD63_021DB2C8
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FUN_0202011C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #4
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	bl LCRandom
	mov r1, #0xe0
	bl _s32_div_f
	add r1, #0xa
	lsl r0, r1, #0xc
	str r0, [sp, #4]
	bl LCRandom
	mov r1, #0x38
	bl _s32_div_f
	ldr r0, _021DB41C ; =0x0000013A
	add r0, r1, r0
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	add r1, sp, #4
	bl FUN_02020044
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, _021DB420 ; =MOD63_021DB424
	add r1, r4, #0
	mov r2, #0x14
	bl FUN_0200CA44
	str r0, [r4, #8]
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, r7
	blo _021DB3A8
_021DB414:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DB418: .word 0x00000000
_021DB41C: .word 0x0000013A
_021DB420: .word MOD63_021DB424
	thumb_func_end MOD63_021DB398

	thumb_func_start MOD63_021DB424
MOD63_021DB424: ; 0x021DB424
	push {r4, lr}
	add r4, r1, #0
	ldrb r1, [r4, #1]
	add r1, r1, #1
	strb r1, [r4, #1]
	ldrb r1, [r4, #1]
	cmp r1, #8
	blo _021DB44C
	bl FUN_0200CAB4
	mov r1, #0
	str r1, [r4, #8]
	strb r1, [r4]
	ldr r0, [r4, #4]
	bl FUN_020200BC
	ldr r0, [r4, #4]
	mov r1, #0
	bl FUN_020200A0
_021DB44C:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD63_021DB424

	.section .rodata

	.global MOD63_021DBEAC
MOD63_021DBEAC: ; 0x021DBEAC
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x4C, 0x00, 0x00, 0x00

	.global MOD63_021DBEBC
MOD63_021DBEBC: ; 0x021DBEBC
	.byte 0x01, 0x01, 0x01, 0x01
