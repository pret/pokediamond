	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD45_02254840
MOD45_02254840: ; 0x02254840
	ldr r3, _02254848 ; =MOD20_02252978
	ldr r0, _0225484C ; =MOD45_02254854
	ldr r1, _02254850 ; =MOD45_02254A30
	bx r3
	.align 2, 0
_02254848: .word MOD20_02252978
_0225484C: .word MOD45_02254854
_02254850: .word MOD45_02254A30
	thumb_func_end MOD45_02254840

	thumb_func_start MOD45_02254854
MOD45_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0xb0
	add r7, r2, #0
	str r3, [sp]
	bl FUN_02016998
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD45_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD45_022549EC
	add r1, r4, #0
	mov r2, #1
	bl FUN_0200CA44
	cmp r0, #0
	beq _0225488C
	str r4, [r5]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0225488C:
	add r0, r4, #0
	bl FUN_02016A18
_02254892:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254898: .word MOD45_022549EC
	thumb_func_end MOD45_02254854

	thumb_func_start MOD45_0225489C
MOD45_0225489C: ; 0x0225489C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r4, r1, #0
	add r0, sp, #4
	add r6, r2, #0
	bl FUN_020126B4
	add r0, r4, #0
	bl MOD20_02252C3C
	add r1, r5, #0
	add r1, #0x98
	str r0, [r1]
	add r0, r5, #4
	add r1, r5, #0
	add r2, sp, #4
	bl MOD45_0225492C
	add r0, r5, #0
	ldrb r1, [r5, #0x12]
	add r0, #0xa8
	add r2, r6, #0
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xa8
	ldr r1, [r0]
	ldr r0, [r5, #8]
	sub r0, r0, #1
	add r1, r1, r0
	add r0, r5, #0
	add r0, #0xac
	str r1, [r0]
	add r0, r5, #0
	add r0, #0x90
	add r1, r5, #4
	bl MOD45_02254B90
	cmp r0, #0
	beq _0225491C
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	mov r0, #8
	str r0, [sp]
	ldr r0, _02254924 ; =0x02255018
	ldr r2, _02254928 ; =MOD45_022549E0
	mov r1, #0x25
	add r3, r5, #0
	bl MOD20_02254130
	add r1, r5, #0
	add r1, #0x9c
	str r0, [r1]
	add r0, r5, #0
	mov r1, #0
	add r0, #0xa0
	str r1, [r0]
	add r5, #0x94
	add sp, #0x14
	str r4, [r5]
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_0225491C:
	mov r0, #0
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	nop
_02254924: .word 0x02255018
_02254928: .word MOD45_022549E0
	thumb_func_end MOD45_0225489C

	thumb_func_start MOD45_0225492C
MOD45_0225492C: ; 0x0225492C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r2, #0
	add r6, r0, #0
	ldr r0, [r4, #4]
	str r1, [sp]
	str r0, [r6]
	ldr r0, [r4, #8]
	str r0, [r6, #8]
	ldr r1, [r6]
	ldr r0, _022549BC ; =0x022550AB
	ldrb r0, [r0, r1]
	str r0, [r6, #4]
	ldr r0, [r6]
	cmp r0, #2
	bne _02254970
	ldr r5, [r4]
	mov r1, #0x19
	add r0, r5, #0
	lsl r1, r1, #4
	bl _u32_div_f
	cmp r1, #0
	beq _0225496C
	add r0, r5, #0
	mov r1, #0x64
	bl _u32_div_f
	cmp r1, #0
	beq _02254970
	mov r0, #3
	tst r0, r5
	bne _02254970
_0225496C:
	mov r0, #0x1d
	str r0, [r6, #4]
_02254970:
	ldr r0, [r4, #8]
	mov r1, #7
	sub r0, r0, #1
	bl _u32_div_f
	mov r2, #7
	ldr r3, [r4, #0xc]
	sub r0, r2, r1
	add r7, r3, r0
	cmp r7, #7
	blo _02254990
	add r0, r7, #0
	add r1, r2, #0
	bl _u32_div_f
	add r7, r1, #0
_02254990:
	ldr r0, [r6, #4]
	mov r4, #0
	cmp r0, #0
	bls _022549BA
	add r5, r6, #0
_0225499A:
	ldr r0, [sp]
	add r2, r4, #1
	strh r2, [r5, #0xc]
	add r0, #0x98
	ldr r0, [r0]
	ldr r1, [r6]
	bl FUN_0204C064
	strb r0, [r5, #0xf]
	add r0, r7, r4
	strb r0, [r5, #0xe]
	ldr r0, [r6, #4]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blo _0225499A
_022549BA:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022549BC: .word 0x022550AB
	thumb_func_end MOD45_0225492C

	thumb_func_start MOD45_022549C0
MOD45_022549C0: ; 0x022549C0
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x9c
	ldr r0, [r0]
	bl MOD20_02254198
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	bl MOD45_02254BCC
	add r0, r4, #0
	bl FUN_02016A18
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD45_022549C0

	thumb_func_start MOD45_022549E0
MOD45_022549E0: ; 0x022549E0
	add r2, r3, #0
	add r2, #0xa4
	str r0, [r2]
	add r3, #0xa0
	str r1, [r3]
	bx lr
	thumb_func_end MOD45_022549E0

	thumb_func_start MOD45_022549EC
MOD45_022549EC: ; 0x022549EC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhs _02254A2A
	add r0, r4, #0
	add r0, #0x94
	add r1, #0x9c
	ldr r0, [r0]
	ldr r1, [r1]
	bl MOD20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _02254A2C ; =0x0225500C
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254A2A
	add r0, r4, #0
	bl MOD45_022549C0
	add r0, r5, #0
	bl FUN_0200CAB4
	add r4, #0x94
	ldr r0, [r4]
	bl MOD20_022529A0
_02254A2A:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254A2C: .word 0x0225500C
	thumb_func_end MOD45_022549EC

	thumb_func_start MOD45_02254A30
MOD45_02254A30: ; 0x02254A30
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD45_02254A30

	thumb_func_start MOD45_02254A38
MOD45_02254A38: ; 0x02254A38
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254A40
	b _02254A42
_02254A40:
	mov r1, #2
_02254A42:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD45_02254A38

	thumb_func_start MOD45_02254A4C
MOD45_02254A4C: ; 0x02254A4C
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A5C
	cmp r0, #1
	beq _02254A70
	b _02254A92
_02254A5C:
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	mov r1, #0
	bl MOD45_02254C7C
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A92
_02254A70:
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	mov r1, #0
	bl MOD45_02254CA0
	cmp r0, #0
	beq _02254A92
	add r0, r4, #0
	add r0, #0x94
	ldr r0, [r0]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD45_02254A38
_02254A92:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD45_02254A4C

	thumb_func_start MOD45_02254A98
MOD45_02254A98: ; 0x02254A98
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldrb r1, [r5, #2]
	cmp r1, #0
	beq _02254AAC
	mov r1, #2
	bl MOD45_02254A38
	mov r0, #0
	pop {r3, r4, r5, pc}
_02254AAC:
	ldrb r0, [r5, #1]
	cmp r0, #0
	beq _02254AB8
	cmp r0, #1
	beq _02254B3E
	b _02254B52
_02254AB8:
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	cmp r0, #1
	bne _02254B52
	add r0, r5, #0
	mov r1, #0
	add r0, #0xa0
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xa8
	ldr r2, [r0]
	add r0, r5, #0
	add r0, #0xa4
	ldr r1, [r0]
	cmp r1, r2
	blo _02254B52
	add r0, r5, #0
	add r0, #0xac
	ldr r0, [r0]
	cmp r1, r0
	bhi _02254B52
	add r0, r5, #0
	add r0, #0x98
	sub r4, r1, r2
	ldr r0, [r0]
	ldr r1, [r5, #4]
	add r2, r4, #1
	bl FUN_0204C064
	cmp r0, #0
	beq _02254B08
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	ldr r1, [r5, #4]
	add r2, r4, #1
	bl FUN_0204C02C
	b _02254B16
_02254B08:
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	ldr r1, [r5, #4]
	add r2, r4, #1
	bl FUN_0204BFF0
_02254B16:
	add r3, r5, #0
	add r3, #0x13
	lsl r2, r4, #2
	ldrb r1, [r3, r2]
	mov r0, #1
	eor r0, r1
	strb r0, [r3, r2]
	add r0, r5, #0
	add r0, #0x8c
	str r4, [r0]
	add r0, r5, #0
	add r0, #0x90
	ldr r0, [r0]
	mov r1, #2
	bl MOD45_02254C7C
	ldrb r0, [r5, #1]
	add r0, r0, #1
	strb r0, [r5, #1]
	b _02254B52
_02254B3E:
	add r0, r5, #0
	add r0, #0x90
	ldr r0, [r0]
	mov r1, #2
	bl MOD45_02254CA0
	cmp r0, #0
	beq _02254B52
	mov r0, #0
	strb r0, [r5, #1]
_02254B52:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD45_02254A98

	thumb_func_start MOD45_02254B58
MOD45_02254B58: ; 0x02254B58
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254B68
	cmp r0, #1
	beq _02254B7C
	b _02254B8C
_02254B68:
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	mov r1, #1
	bl MOD45_02254C7C
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254B8C
_02254B7C:
	add r4, #0x90
	ldr r0, [r4]
	bl MOD45_02254CAC
	cmp r0, #0
	beq _02254B8C
	mov r0, #1
	pop {r4, pc}
_02254B8C:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD45_02254B58

	thumb_func_start MOD45_02254B90
MOD45_02254B90: ; 0x02254B90
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #8
	mov r1, #0x3c
	bl FUN_02016998
	add r4, r0, #0
	beq _02254BC6
	add r0, #8
	mov r1, #4
	bl MOD20_022536F4
	str r5, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	bl MOD20_02252D24
	str r0, [r4, #0x20]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD45_02254BE0
	str r4, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254BC6:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD45_02254B90

	thumb_func_start MOD45_02254BCC
MOD45_02254BCC: ; 0x02254BCC
	push {r4, lr}
	add r4, r0, #0
	beq _02254BDC
	bl MOD45_02254C64
	add r0, r4, #0
	bl FUN_02016A18
_02254BDC:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD45_02254BCC

	thumb_func_start MOD45_02254BE0
MOD45_02254BE0: ; 0x02254BE0
	push {r4, r5, lr}
	sub sp, #0xc
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	add r5, r0, #0
	add r4, r1, #0
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x72
	bl FUN_02006A34
	mov r0, #8
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x28
	mov r1, #0xc
	mov r2, #0x70
	mov r3, #0x71
	bl MOD20_02253FBC
	add r2, r5, #0
	ldr r0, [r5, #0x20]
	ldr r1, _02254C2C ; =0x022550B8
	add r2, #0x28
	bl MOD20_02253E74
	str r0, [r5, #0x24]
	ldr r1, [r4, #8]
	lsl r1, r1, #2
	add r1, r4, r1
	ldrb r1, [r1, #0xa]
	bl MOD45_02254C30
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02254C2C: .word 0x022550B8
	thumb_func_end MOD45_02254BE0

	thumb_func_start MOD45_02254C30
MOD45_02254C30: ; 0x02254C30
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	mov r1, #7
	bl _u32_div_f
	add r4, r1, #0
	add r0, r6, #0
	mov r1, #7
	bl _u32_div_f
	add r2, r0, #0
	lsl r1, r4, #1
	lsl r3, r2, #1
	add r1, r4, r1
	add r2, r2, r3
	add r1, r1, #5
	add r2, r2, #6
	add r0, r5, #0
	lsl r1, r1, #0xf
	lsl r2, r2, #0xf
	bl MOD20_02253F64
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD45_02254C30

	thumb_func_start MOD45_02254C64
MOD45_02254C64: ; 0x02254C64
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0x24]
	bl MOD20_02253F14
	add r4, #0x28
	add r0, r4, #0
	bl MOD20_02254014
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD45_02254C64

	thumb_func_start MOD45_02254C7C
MOD45_02254C7C: ; 0x02254C7C
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254C9C ; =0x02255140
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254C9C: .word 0x02255140
	thumb_func_end MOD45_02254C7C

	thumb_func_start MOD45_02254CA0
MOD45_02254CA0: ; 0x02254CA0
	ldr r3, _02254CA8 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254CA8: .word MOD20_02253794
	thumb_func_end MOD45_02254CA0

	thumb_func_start MOD45_02254CAC
MOD45_02254CAC: ; 0x02254CAC
	ldr r3, _02254CB4 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254CB4: .word MOD20_022537B8
	thumb_func_end MOD45_02254CAC

	thumb_func_start MOD45_02254CB8
MOD45_02254CB8: ; 0x02254CB8
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD45_02254CB8

	thumb_func_start MOD45_02254CCC
MOD45_02254CCC: ; 0x02254CCC
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r5, r0, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r4, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254D60 ; =0x022550FC
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r5, #4]
	ldr r2, _02254D64 ; =0x022550E0
	mov r1, #7
	mov r3, #0
	bl FUN_02016C18
	add r0, r5, #0
	add r1, r4, #0
	bl MOD45_02254DDC
	add r0, r5, #0
	add r1, r4, #0
	bl MOD45_02254E74
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x6f
	mov r3, #7
	bl FUN_0200687C
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r0, [r5, #4]
	mov r1, #7
	bl FUN_02017CD0
	ldr r1, _02254D68 ; =0x04001000
	ldr r0, _02254D6C ; =0xFFFFE0FF
	ldr r3, [r1]
	ldr r2, [r1]
	str r3, [sp, #0x10]
	and r0, r2
	lsl r2, r3, #0x13
	lsr r3, r2, #0x1b
	mov r2, #0xc
	orr r2, r3
	lsl r2, r2, #8
	orr r0, r2
	str r0, [r1]
	add r0, r6, #0
	bl MOD45_02254CB8
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02254D60: .word 0x022550FC
_02254D64: .word 0x022550E0
_02254D68: .word 0x04001000
_02254D6C: .word 0xFFFFE0FF
	thumb_func_end MOD45_02254CCC

	thumb_func_start MOD45_02254D70
MOD45_02254D70: ; 0x02254D70
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #7
	bl FUN_020178A0
	add r0, r5, #0
	bl MOD45_02254CB8
	pop {r3, r4, r5, pc}
	thumb_func_end MOD45_02254D70

	thumb_func_start MOD45_02254D94
MOD45_02254D94: ; 0x02254D94
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	add r0, r4, #0
	bl MOD20_022538A4
	add r2, r0, #0
	add r0, #0x88
	ldr r0, [r0]
	lsl r3, r0, #2
	add r0, r2, r3
	ldrb r0, [r0, #0xf]
	cmp r0, #0
	beq _02254DBA
	mov r1, #0x8f
	b _02254DBC
_02254DBA:
	mov r1, #0x83
_02254DBC:
	add r2, r2, r3
	ldrb r2, [r2, #0xe]
	lsl r1, r1, #0x10
	ldr r0, [r5, #4]
	lsr r1, r1, #0x10
	bl MOD45_02254E28
	ldr r0, [r5, #4]
	mov r1, #7
	bl FUN_02017CD0
	add r0, r4, #0
	bl MOD45_02254CB8
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD45_02254D94

	thumb_func_start MOD45_02254DDC
MOD45_02254DDC: ; 0x02254DDC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	add r6, r1, #0
	ldr r2, [r7, #4]
	mov r0, #0xc
	mov r1, #0x6e
	mov r3, #7
	bl FUN_020068C8
	ldr r0, [r6, #4]
	mov r4, #0
	cmp r0, #0
	bls _02254E22
	add r5, r6, #0
_02254E08:
	ldrb r0, [r5, #0xf]
	cmp r0, #0
	beq _02254E18
	ldrb r2, [r5, #0xe]
	ldr r0, [r7, #4]
	mov r1, #0x8f
	bl MOD45_02254E28
_02254E18:
	ldr r0, [r6, #4]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blo _02254E08
_02254E22:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD45_02254DDC

	thumb_func_start MOD45_02254E28
MOD45_02254E28: ; 0x02254E28
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r2, #0
	add r5, r0, #0
	add r6, r1, #0
	add r0, r7, #0
	mov r1, #7
	bl _u32_div_f
	add r4, r1, #0
	add r0, r7, #0
	mov r1, #7
	bl _u32_div_f
	lsl r1, r0, #1
	add r0, r0, r1
	add r0, r0, #5
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r3, r4, #1
	str r0, [sp]
	mov r0, #2
	add r3, r4, r3
	str r0, [sp, #4]
	add r3, r3, #4
	str r0, [sp, #8]
	mov r0, #0
	lsl r3, r3, #0x18
	str r0, [sp, #0xc]
	add r0, r5, #0
	mov r1, #7
	add r2, r6, #0
	lsr r3, r3, #0x18
	bl FUN_02018540
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD45_02254E28

	thumb_func_start MOD45_02254E74
MOD45_02254E74: ; 0x02254E74
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r3, #0
	add r7, r0, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	add r6, r1, #0
	ldr r0, [r7, #4]
	mov r1, #6
	mov r2, #0x82
	bl FUN_02018540
	ldr r0, [r7, #4]
	ldr r1, [r6]
	bl MOD45_02254EBC
	ldr r0, [r6, #4]
	mov r4, #0
	cmp r0, #0
	bls _02254EB8
	add r5, r6, #0
_02254EA4:
	ldrb r2, [r5, #0xe]
	ldr r0, [r7, #4]
	add r1, r4, #1
	bl MOD45_02254F14
	ldr r0, [r6, #4]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blo _02254EA4
_02254EB8:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD45_02254E74

	thumb_func_start MOD45_02254EBC
MOD45_02254EBC: ; 0x02254EBC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r0, #0
	ldr r0, _02254F10 ; =0x022550C6
	lsl r1, r1, #1
	ldrh r4, [r0, r1]
	mov r0, #0
	str r0, [sp, #0x10]
_02254ECC:
	ldr r0, [sp, #0x10]
	mov r5, #0
	add r0, r0, #2
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
_02254ED6:
	add r3, r5, #0
	add r2, r4, r5
	add r3, #0xc
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	str r6, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, r7, #0
	mov r1, #6
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	add r5, r5, #1
	cmp r5, #4
	blt _02254ED6
	ldr r0, [sp, #0x10]
	add r4, #0xc
	add r0, r0, #1
	str r0, [sp, #0x10]
	cmp r0, #2
	blt _02254ECC
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_02254F10: .word 0x022550C6
	thumb_func_end MOD45_02254EBC

	thumb_func_start MOD45_02254F14
MOD45_02254F14: ; 0x02254F14
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r2, #0
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	add r0, r5, #0
	mov r1, #7
	bl _u32_div_f
	add r6, r1, #0
	lsl r0, r6, #1
	add r0, r6, r0
	add r4, r0, #4
	add r0, r5, #0
	mov r1, #7
	bl _u32_div_f
	lsl r1, r0, #1
	add r0, r0, r1
	add r5, r0, #5
	cmp r6, #0
	bne _02254F44
	mov r6, #1
	b _02254F46
_02254F44:
	mov r6, #0
_02254F46:
	ldr r0, [sp, #0x14]
	mov r1, #0xa
	bl _u32_div_f
	add r7, r0, #0
	ldr r0, [sp, #0x14]
	mov r1, #0xa
	bl _u32_div_f
	str r1, [sp, #0x18]
	cmp r7, #0
	beq _02254FAE
	mov r0, #0x14
	add r2, r6, #0
	mul r2, r0
	ldr r0, _02255008 ; =0x02255118
	lsl r1, r7, #1
	add r0, r0, r2
	ldrh r7, [r1, r0]
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	lsl r3, r4, #0x18
	ldr r0, [sp, #0x10]
	mov r1, #6
	add r2, r7, #0
	lsr r3, r3, #0x18
	bl FUN_02018540
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	add r7, #0xc
	str r0, [sp, #0xc]
	lsl r2, r7, #0x10
	lsl r3, r4, #0x18
	ldr r0, [sp, #0x10]
	mov r1, #6
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
_02254FAE:
	mov r0, #0x14
	add r3, r6, #0
	mul r3, r0
	ldr r0, [sp, #0x18]
	ldr r2, _02255008 ; =0x02255118
	lsl r1, r0, #1
	add r0, r2, r3
	ldrh r6, [r1, r0]
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	add r3, r4, #1
	str r0, [sp, #0xc]
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	mov r1, #6
	add r2, r6, #0
	lsr r3, r3, #0x18
	bl FUN_02018540
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	add r6, #0xc
	add r3, r4, #1
	str r0, [sp, #0xc]
	lsl r2, r6, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x10]
	mov r1, #6
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02255008: .word 0x02255118
	thumb_func_end MOD45_02254F14

	.section .rodata
	; 0x0225500C
	.incbin "baserom.nds", 0x2961CC, 0x164

	.section .sinit
	.word MOD45_02254840
