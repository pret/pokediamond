	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD79_02211E60
MOD79_02211E60: ; 0x02211E60
	lsl r1, r0, #0x10
	orr r1, r0
	ldr r0, _02211E6C ; =0x02217120
	str r1, [r0]
	bx lr
	nop
_02211E6C: .word 0x02217120
	thumb_func_end MOD79_02211E60

	thumb_func_start MOD79_02211E70
MOD79_02211E70: ; 0x02211E70
	ldr r1, _02211E8C ; =0x02217120
	mov r0, #0x45
	ldr r2, [r1]
	add r3, r2, #0
	mul r3, r0
	ldr r0, _02211E90 ; =0x00001111
	add r2, r3, r0
	ldr r0, _02211E94 ; =0x7FFFFFFF
	and r0, r2
	str r0, [r1]
	asr r0, r0, #0x10
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
	.align 2, 0
_02211E8C: .word 0x02217120
_02211E90: .word 0x00001111
_02211E94: .word 0x7FFFFFFF
	thumb_func_end MOD79_02211E70

	thumb_func_start MOD79_02211E98
MOD79_02211E98: ; 0x02211E98
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r0, #0
	mov r0, #0
	add r5, r2, #0
	str r0, [sp, #0x14]
	add r0, r5, #0
	str r0, [sp, #0x10]
	add r0, #8
	add r7, r1, #0
	str r3, [sp]
	str r0, [sp, #0x10]
	bl MOD79_02211FA4
	ldr r1, [sp, #0x30]
	add r0, r0, #1
	cmp r1, r0
	bge _02211EC2
	add sp, #0x18
	mov r0, #2
	pop {r3, r4, r5, r6, r7, pc}
_02211EC2:
	ldr r1, [sp, #0x10]
	mov r0, #0xa
	bl MOD04_021DD944
	add r6, r0, #0
	bne _02211ED4
	add sp, #0x18
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02211ED4:
	lsr r0, r4, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r0, [sp, #0x14]
	add r0, r0, r1
	lsr r1, r4, #0x10
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #8]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r0, r0, r1
	lsr r1, r4, #8
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0xc]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r0, r0, r1
	lsl r1, r4, #0x18
	lsr r4, r1, #0x18
	lsl r1, r4, #0x18
	lsr r1, r1, #0x18
	add r0, r0, r1
	str r0, [sp, #0x14]
	mov r0, #0
	cmp r5, #0
	ble _02211F20
_02211F12:
	ldrb r2, [r7, r0]
	ldr r1, [sp, #0x14]
	add r0, r0, #1
	add r1, r1, r2
	str r1, [sp, #0x14]
	cmp r0, r5
	blt _02211F12
_02211F20:
	ldr r0, [sp, #0x14]
	bl MOD79_02211E60
	bl MOD79_02211E70
	eor r0, r4
	strb r0, [r6, #4]
	bl MOD79_02211E70
	ldr r1, [sp, #0xc]
	eor r0, r1
	strb r0, [r6, #5]
	bl MOD79_02211E70
	ldr r1, [sp, #8]
	eor r0, r1
	strb r0, [r6, #6]
	bl MOD79_02211E70
	ldr r1, [sp, #4]
	mov r4, #0
	eor r0, r1
	strb r0, [r6, #7]
	cmp r5, #0
	ble _02211F64
_02211F52:
	bl MOD79_02211E70
	ldrb r1, [r7, r4]
	eor r1, r0
	add r0, r6, r4
	add r4, r4, #1
	strb r1, [r0, #8]
	cmp r4, r5
	blt _02211F52
_02211F64:
	ldr r1, _02211FA0 ; =0x4A3B2C1D
	ldr r0, [sp, #0x14]
	add r5, #8
	eor r1, r0
	lsr r0, r1, #0x18
	strb r0, [r6]
	lsr r0, r1, #0x10
	strb r0, [r6, #1]
	lsr r0, r1, #8
	strb r0, [r6, #2]
	strb r1, [r6, #3]
	ldr r1, [sp]
	add r0, r6, #0
	add r2, r5, #0
	mov r3, #2
	bl MOD04_021EF820
	ldr r0, [sp, #0x10]
	bl MOD79_02211FA4
	ldr r1, [sp]
	mov r2, #0
	strb r2, [r1, r0]
	mov r0, #0xa
	add r1, r6, #0
	bl MOD04_021DD904
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02211FA0: .word 0x4A3B2C1D
	thumb_func_end MOD79_02211E98

	thumb_func_start MOD79_02211FA4
MOD79_02211FA4: ; 0x02211FA4
	push {r3, r4, r5, lr}
	mov r1, #3
	add r5, r0, #0
	bl _u32_div_f
	cmp r1, #0
	beq _02211FB6
	mov r4, #1
	b _02211FB8
_02211FB6:
	mov r4, #0
_02211FB8:
	add r0, r5, #0
	mov r1, #3
	bl _u32_div_f
	add r0, r0, r4
	lsl r0, r0, #2
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD79_02211FA4

	thumb_func_start MOD79_02211FC8
MOD79_02211FC8: ; 0x02211FC8
	add r0, #8
	cmp r0, #7
	bhi _02212022
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02211FDA: ; jump table
	.short _02211FEA - _02211FDA - 2 ; case 0
	.short _02212022 - _02211FDA - 2 ; case 1
	.short _02211FF2 - _02211FDA - 2 ; case 2
	.short _02211FFA - _02211FDA - 2 ; case 3
	.short _02212002 - _02211FDA - 2 ; case 4
	.short _0221200A - _02211FDA - 2 ; case 5
	.short _02212012 - _02211FDA - 2 ; case 6
	.short _0221201A - _02211FDA - 2 ; case 7
_02211FEA:
	ldr r0, _0221202C ; =0x02216760
	mov r1, #0
	str r1, [r0, #8]
	bx lr
_02211FF2:
	ldr r0, _0221202C ; =0x02216760
	mov r1, #1
	str r1, [r0, #8]
	bx lr
_02211FFA:
	ldr r0, _0221202C ; =0x02216760
	mov r1, #2
	str r1, [r0, #8]
	bx lr
_02212002:
	ldr r0, _0221202C ; =0x02216760
	mov r1, #3
	str r1, [r0, #8]
	bx lr
_0221200A:
	ldr r0, _0221202C ; =0x02216760
	mov r1, #4
	str r1, [r0, #8]
	bx lr
_02212012:
	ldr r0, _0221202C ; =0x02216760
	mov r1, #5
	str r1, [r0, #8]
	bx lr
_0221201A:
	ldr r0, _0221202C ; =0x02216760
	mov r1, #6
	str r1, [r0, #8]
	bx lr
_02212022:
	ldr r0, _0221202C ; =0x02216760
	mov r1, #0
	str r1, [r0, #8]
	bx lr
	nop
_0221202C: .word 0x02216760
	thumb_func_end MOD79_02211FC8

	thumb_func_start MOD79_02212030
MOD79_02212030: ; 0x02212030
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	add r4, r1, #0
	mov r3, #0
	ldr r1, _022122B8 ; =0x02216760
	mvn r3, r3
	str r3, [r1, #4]
	ldr r3, [r1]
	add r6, r0, #0
	cmp r3, #1
	bne _02212048
	b _022122B2
_02212048:
	cmp r2, #0
	beq _0221204E
	b _02212202
_0221204E:
	cmp r3, #4
	beq _0221205A
	cmp r3, #6
	beq _02212126
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_0221205A:
	cmp r4, #0x20
	bne _0221211E
	ldr r5, [r1, #0x28]
	ldr r3, _022122BC ; =0x02216724
	add r5, #0x14
	add r2, sp, #4
	mov r1, #0x11
_02212068:
	ldrb r0, [r3]
	add r3, r3, #1
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _02212068
	add r3, sp, #0x14
	ldr r2, _022122C0 ; =0x02216794
	add r3, #1
	mov r1, #0x15
_0221207C:
	ldrb r0, [r2]
	add r2, r2, #1
	strb r0, [r3]
	add r3, r3, #1
	sub r1, r1, #1
	bne _0221207C
	add r0, sp, #0x14
	add r0, #1
	add r1, r6, #0
	add r2, r4, #0
	bl strncat
	add r0, sp, #0x14
	add r0, #1
	bl strlen
	add r1, sp, #0x14
	add r2, r0, #0
	add r0, r5, #0
	add r1, #1
	bl MATH_CalcSHA1
	ldr r0, _022122B8 ; =0x02216760
	ldr r1, _022122C4 ; =0x022167AC
	ldr r0, [r0, #0x24]
	bl strcat
	mov r2, #0
	ldr r4, _022122B8 ; =0x02216760
	add r3, r2, #0
	add r1, sp, #4
	mov r7, #0xf
_022120BC:
	ldrb r0, [r5, r2]
	asr r0, r0, #4
	ldrsb r6, [r1, r0]
	ldr r0, [r4, #0x28]
	strb r6, [r0, r3]
	ldrb r0, [r5, r2]
	ldr r6, [r4, #0x28]
	add r2, r2, #1
	and r0, r7
	ldrsb r0, [r1, r0]
	add r6, r6, r3
	add r3, r3, #2
	strb r0, [r6, #1]
	cmp r2, #0x14
	blt _022120BC
	ldr r0, _022122B8 ; =0x02216760
	mov r2, #0
	ldr r1, [r0, #0x28]
	add r1, #0x28
	strb r2, [r1]
	ldr r0, [r0, #0x24]
	ldr r1, _022122C8 ; =0x022167B4
	bl strcat
	ldr r3, _022122B8 ; =0x02216760
	ldr r0, [r3, #0x30]
	str r0, [sp]
	ldr r0, [r3, #0x10]
	ldr r1, [r3, #0x14]
	ldr r2, [r3, #0x18]
	ldr r3, [r3, #0x2c]
	bl MOD79_02211E98
	cmp r0, #0
	beq _02212114
	cmp r0, #1
	beq _0221210A
	cmp r0, #2
	bne _02212114
_0221210A:
	ldr r0, _022122B8 ; =0x02216760
	mov r1, #1
	str r1, [r0]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_02212114:
	ldr r0, _022122B8 ; =0x02216760
	mov r1, #5
	str r1, [r0]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_0221211E:
	mov r0, #1
	str r0, [r1]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_02212126:
	cmp r4, #0x16
	bne _022121D0
	ldr r1, _022122CC ; =0x022167BC
	mov r2, #0x16
	bl strncmp
	cmp r0, #0
	bne _02212144
	ldr r0, _022122B8 ; =0x02216760
	mov r1, #1
	str r1, [r0]
	mov r1, #0x1a
	str r1, [r0, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_02212144:
	ldr r1, _022122D0 ; =0x022167D4
	add r0, r6, #0
	mov r2, #0x16
	bl strncmp
	cmp r0, #0
	bne _02212160
	ldr r0, _022122B8 ; =0x02216760
	mov r1, #1
	str r1, [r0]
	mov r1, #0x1b
	str r1, [r0, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_02212160:
	ldr r1, _022122D4 ; =0x022167EC
	add r0, r6, #0
	mov r2, #0x16
	bl strncmp
	cmp r0, #0
	bne _0221217C
	ldr r0, _022122B8 ; =0x02216760
	mov r1, #1
	str r1, [r0]
	mov r1, #0x1c
	str r1, [r0, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_0221217C:
	ldr r1, _022122D8 ; =0x02216804
	add r0, r6, #0
	mov r2, #0x16
	bl strncmp
	cmp r0, #0
	bne _02212198
	ldr r0, _022122B8 ; =0x02216760
	mov r1, #1
	str r1, [r0]
	mov r1, #0x1d
	str r1, [r0, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_02212198:
	ldr r1, _022122DC ; =0x0221681C
	add r0, r6, #0
	mov r2, #0x16
	bl strncmp
	cmp r0, #0
	bne _022121B4
	ldr r0, _022122B8 ; =0x02216760
	mov r1, #1
	str r1, [r0]
	mov r1, #0x1e
	str r1, [r0, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_022121B4:
	ldr r1, _022122E0 ; =0x02216834
	add r0, r6, #0
	mov r2, #0x16
	bl strncmp
	cmp r0, #0
	bne _022121D0
	ldr r0, _022122B8 ; =0x02216760
	mov r1, #1
	str r1, [r0]
	mov r1, #0x1f
	str r1, [r0, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_022121D0:
	ldr r0, _022122B8 ; =0x02216760
	ldr r2, [r0, #0x20]
	cmp r4, r2
	ldr r0, [r0, #0x1c]
	bgt _022121EA
	add r1, r6, #0
	add r2, r4, #0
	bl memcpy
	ldr r0, _022122B8 ; =0x02216760
	mov r1, #7
	str r1, [r0]
	b _022121FA
_022121EA:
	add r1, r6, #0
	bl memcpy
	ldr r0, _022122B8 ; =0x02216760
	mov r1, #1
	str r1, [r0]
	mov r1, #0x20
	str r1, [r0, #8]
_022121FA:
	ldr r0, _022122B8 ; =0x02216760
	add sp, #0x4c
	str r4, [r0, #0xc]
	pop {r4, r5, r6, r7, pc}
_02212202:
	mov r0, #1
	str r0, [r1]
	cmp r2, #0x13
	bhi _022122B2
	add r0, r2, r2
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02212216: ; jump table
	.short _022122B2 - _02212216 - 2 ; case 0
	.short _0221223E - _02212216 - 2 ; case 1
	.short _02212246 - _02212216 - 2 ; case 2
	.short _0221224E - _02212216 - 2 ; case 3
	.short _02212256 - _02212216 - 2 ; case 4
	.short _0221225E - _02212216 - 2 ; case 5
	.short _02212266 - _02212216 - 2 ; case 6
	.short _0221226E - _02212216 - 2 ; case 7
	.short _02212276 - _02212216 - 2 ; case 8
	.short _0221227E - _02212216 - 2 ; case 9
	.short _02212286 - _02212216 - 2 ; case 10
	.short _0221228E - _02212216 - 2 ; case 11
	.short _02212296 - _02212216 - 2 ; case 12
	.short _022122B2 - _02212216 - 2 ; case 13
	.short _022122B2 - _02212216 - 2 ; case 14
	.short _0221229E - _02212216 - 2 ; case 15
	.short _022122A6 - _02212216 - 2 ; case 16
	.short _022122B2 - _02212216 - 2 ; case 17
	.short _022122B2 - _02212216 - 2 ; case 18
	.short _022122AE - _02212216 - 2 ; case 19
_0221223E:
	mov r0, #8
	str r0, [r1, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_02212246:
	mov r0, #9
	str r0, [r1, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_0221224E:
	mov r0, #0xa
	str r0, [r1, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_02212256:
	mov r0, #0xb
	str r0, [r1, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_0221225E:
	mov r0, #0xc
	str r0, [r1, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_02212266:
	mov r0, #0xd
	str r0, [r1, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_0221226E:
	mov r0, #0xe
	str r0, [r1, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_02212276:
	mov r0, #0xf
	str r0, [r1, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_0221227E:
	mov r0, #0x10
	str r0, [r1, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_02212286:
	mov r0, #0x11
	str r0, [r1, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_0221228E:
	mov r0, #0x12
	str r0, [r1, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_02212296:
	mov r0, #0x13
	str r0, [r1, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_0221229E:
	mov r0, #0x16
	str r0, [r1, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_022122A6:
	mov r0, #0x17
	str r0, [r1, #8]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_022122AE:
	mov r0, #0x19
	str r0, [r1, #8]
_022122B2:
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
	nop
_022122B8: .word 0x02216760
_022122BC: .word 0x02216724
_022122C0: .word 0x02216794
_022122C4: .word 0x022167AC
_022122C8: .word 0x022167B4
_022122CC: .word 0x022167BC
_022122D0: .word 0x022167D4
_022122D4: .word 0x022167EC
_022122D8: .word 0x02216804
_022122DC: .word 0x0221681C
_022122E0: .word 0x02216834
	thumb_func_end MOD79_02212030

	thumb_func_start MOD79_022122E4
MOD79_022122E4: ; 0x022122E4
	push {r3, lr}
	ldr r0, _02212304 ; =0x02216760
	mov r1, #2
	str r1, [r0]
	sub r1, r1, #3
	str r1, [r0, #4]
	mov r0, #0
	bl MOD04_021EB59C
	cmp r0, #0
	bne _02212300
	ldr r0, _02212304 ; =0x02216760
	mov r1, #1
	str r1, [r0]
_02212300:
	pop {r3, pc}
	nop
_02212304: .word 0x02216760
	thumb_func_end MOD79_022122E4

	thumb_func_start MOD79_02212308
MOD79_02212308: ; 0x02212308
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r1, _02212398 ; =0x02216760
	add r4, r3, #0
	ldr r3, [r1]
	add r7, r0, #0
	cmp r3, #2
	beq _0221231C
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0221231C:
	str r5, [r1, #0x10]
	str r2, [r1, #0x14]
	str r4, [r1, #0x18]
	ldr r2, [sp, #0x18]
	add r4, #8
	str r2, [r1, #0x1c]
	ldr r2, [sp, #0x1c]
	str r2, [r1, #0x20]
	bl strlen
	add r6, r0, #0
	add r0, r4, #0
	bl MOD79_02211FA4
	add r1, r0, #0
	add r6, #0x45
	mov r0, #0xa
	add r1, r6, r1
	bl MOD04_021DD944
	ldr r1, _02212398 ; =0x02216760
	cmp r0, #0
	str r0, [r1, #0x24]
	bne _02212350
	mov r0, #2
	pop {r3, r4, r5, r6, r7, pc}
_02212350:
	ldr r1, _0221239C ; =0x0221684C
	add r2, r7, #0
	add r3, r5, #0
	bl sprintf
	ldr r0, _02212398 ; =0x02216760
	ldr r5, [r0, #0x24]
	add r0, r5, #0
	bl strlen
	add r6, r0, #0
	ldr r0, _022123A0 ; =0x022167AC
	bl strlen
	add r1, r5, r6
	add r1, r1, r0
	ldr r0, _02212398 ; =0x02216760
	str r1, [r0, #0x28]
	ldr r0, _022123A4 ; =0x022167B4
	bl strlen
	ldr r1, _02212398 ; =0x02216760
	ldr r2, [r1, #0x28]
	add r2, #0x28
	add r0, r2, r0
	str r0, [r1, #0x2c]
	add r0, r4, #0
	bl MOD79_02211FA4
	add r1, r0, #1
	ldr r0, _02212398 ; =0x02216760
	str r1, [r0, #0x30]
	mov r1, #3
	str r1, [r0]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02212398: .word 0x02216760
_0221239C: .word 0x0221684C
_022123A0: .word 0x022167AC
_022123A4: .word 0x022167B4
	thumb_func_end MOD79_02212308

	thumb_func_start MOD79_022123A8
MOD79_022123A8: ; 0x022123A8
	push {r3, lr}
	ldr r1, _02212440 ; =0x02216760
	ldr r0, [r1]
	cmp r0, #7
	bhi _02212438
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022123BE: ; jump table
	.short _02212438 - _022123BE - 2 ; case 0
	.short _02212438 - _022123BE - 2 ; case 1
	.short _02212438 - _022123BE - 2 ; case 2
	.short _022123CE - _022123BE - 2 ; case 3
	.short _022123F4 - _022123BE - 2 ; case 4
	.short _02212404 - _022123BE - 2 ; case 5
	.short _0221242A - _022123BE - 2 ; case 6
	.short _02212438 - _022123BE - 2 ; case 7
_022123CE:
	ldr r0, [r1, #0x24]
	ldr r1, _02212444 ; =MOD79_02212030
	ldr r2, _02212448 ; =0x02216760
	bl MOD04_021EB3B8
	ldr r1, _02212440 ; =0x02216760
	str r0, [r1, #4]
	bl MOD79_02211FC8
	ldr r0, _02212440 ; =0x02216760
	ldr r1, [r0, #4]
	cmp r1, #0
	blt _022123EE
	mov r1, #4
	str r1, [r0]
	b _02212438
_022123EE:
	mov r1, #1
	str r1, [r0]
	b _02212438
_022123F4:
	bl MOD04_021EB524
	cmp r0, #0
	bne _02212438
	ldr r0, _02212440 ; =0x02216760
	mov r1, #1
	str r1, [r0]
	b _02212438
_02212404:
	ldr r0, [r1, #0x24]
	ldr r1, _02212444 ; =MOD79_02212030
	ldr r2, _02212448 ; =0x02216760
	bl MOD04_021EB3B8
	ldr r1, _02212440 ; =0x02216760
	str r0, [r1, #4]
	bl MOD79_02211FC8
	ldr r0, _02212440 ; =0x02216760
	ldr r1, [r0, #4]
	cmp r1, #0
	blt _02212424
	mov r1, #6
	str r1, [r0]
	b _02212438
_02212424:
	mov r1, #1
	str r1, [r0]
	b _02212438
_0221242A:
	bl MOD04_021EB524
	cmp r0, #0
	bne _02212438
	ldr r0, _02212440 ; =0x02216760
	mov r1, #1
	str r1, [r0]
_02212438:
	ldr r0, _02212440 ; =0x02216760
	ldr r0, [r0]
	pop {r3, pc}
	nop
_02212440: .word 0x02216760
_02212444: .word MOD79_02212030
_02212448: .word 0x02216760
	thumb_func_end MOD79_022123A8

	thumb_func_start MOD79_0221244C
MOD79_0221244C: ; 0x0221244C
	push {r3, lr}
	ldr r0, _02212470 ; =0x02216760
	ldr r1, [r0, #0x24]
	cmp r1, #0
	beq _02212464
	mov r0, #0xa
	mov r2, #0
	bl MOD04_021DD904
	ldr r0, _02212470 ; =0x02216760
	mov r1, #0
	str r1, [r0, #0x24]
_02212464:
	bl MOD04_021EB550
	ldr r0, _02212470 ; =0x02216760
	mov r1, #1
	str r1, [r0]
	pop {r3, pc}
	.align 2, 0
_02212470: .word 0x02216760
	thumb_func_end MOD79_0221244C

	thumb_func_start MOD79_02212474
MOD79_02212474: ; 0x02212474
	ldr r0, _0221247C ; =0x02216760
	ldr r0, [r0, #8]
	bx lr
	nop
_0221247C: .word 0x02216760
	thumb_func_end MOD79_02212474

	thumb_func_start MOD79_02212480
MOD79_02212480: ; 0x02212480
	ldr r0, _02212488 ; =0x02216760
	ldr r0, [r0, #0xc]
	bx lr
	nop
_02212488: .word 0x02216760
	thumb_func_end MOD79_02212480

	.section .rodata
	; 0x02216724
	.byte 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66
	.byte 0x00, 0x00, 0x00, 0x00
	
	.section .data
	; 0x02216760
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x73, 0x41, 0x64, 0x65, 0x71, 0x57, 0x6F, 0x33, 0x76, 0x6F, 0x4C, 0x65
	.byte 0x43, 0x35, 0x72, 0x31, 0x36, 0x44, 0x59, 0x76, 0x00, 0x00, 0x00, 0x00, 0x26, 0x68, 0x61, 0x73
	.byte 0x68, 0x3D, 0x00, 0x00, 0x26, 0x64, 0x61, 0x74, 0x61, 0x3D, 0x00, 0x00, 0x65, 0x72, 0x72, 0x6F
	.byte 0x72, 0x3A, 0x20, 0x63, 0x68, 0x65, 0x63, 0x6B, 0x20, 0x73, 0x75, 0x6D, 0x20, 0x20, 0x20, 0x20
	.byte 0x20, 0x20, 0x00, 0x00, 0x65, 0x72, 0x72, 0x6F, 0x72, 0x3A, 0x20, 0x70, 0x69, 0x64, 0x20, 0x20
	.byte 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x65, 0x72, 0x72, 0x6F
	.byte 0x72, 0x3A, 0x20, 0x64, 0x61, 0x74, 0x61, 0x20, 0x6C, 0x65, 0x6E, 0x67, 0x74, 0x68, 0x20, 0x20
	.byte 0x20, 0x20, 0x00, 0x00, 0x65, 0x72, 0x72, 0x6F, 0x72, 0x3A, 0x20, 0x74, 0x6F, 0x6B, 0x65, 0x6E
	.byte 0x20, 0x6E, 0x6F, 0x74, 0x20, 0x66, 0x6F, 0x75, 0x6E, 0x64, 0x00, 0x00, 0x65, 0x72, 0x72, 0x6F
	.byte 0x72, 0x3A, 0x20, 0x74, 0x6F, 0x6B, 0x65, 0x6E, 0x20, 0x65, 0x78, 0x70, 0x69, 0x72, 0x65, 0x64
	.byte 0x20, 0x20, 0x00, 0x00, 0x65, 0x72, 0x72, 0x6F, 0x72, 0x3A, 0x20, 0x69, 0x6E, 0x63, 0x6F, 0x72
	.byte 0x72, 0x65, 0x63, 0x74, 0x20, 0x68, 0x61, 0x73, 0x68, 0x20, 0x00, 0x00, 0x25, 0x73, 0x3F, 0x70
	.byte 0x69, 0x64, 0x3D, 0x25, 0x64, 0x00, 0x00, 0x00, 0x62, 0x75, 0x66, 0x66, 0x65, 0x72, 0x49, 0x6E
	.byte 0x20, 0x21, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00, 0x00, 0x00, 0x00

	.section .bss
	; 0x2217120
	.space 0x40
