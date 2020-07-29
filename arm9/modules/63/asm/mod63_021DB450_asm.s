	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

	.extern MOD63_021DBED8
	.extern MOD63_021DBEC0
	.extern MOD63_021DBEDC

	thumb_func_start MOD63_021DB5A8
MOD63_021DB5A8: ; 0x021DB5A8
	push {r4, lr}
	add r4, r0, #0
	beq _021DB5C8
	bl FUN_020222AC
	bl FUN_020B02C8
	ldr r0, [r4]
	bl FUN_02006ED4
	bl MOD63_021DB934
	mov r0, #1
	mov r1, #0
	bl FUN_020222B4
_021DB5C8:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD63_021DB5A8

	thumb_func_start MOD63_021DB5CC
MOD63_021DB5CC: ; 0x021DB5CC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r0, #0
	add r7, r2, #0
	ldrb r2, [r4, #0x1c]
	add r5, r4, #0
	add r6, r1, #0
	add r5, #0x1c
	cmp r2, #5
	bls _021DB5E2
	b _021DB6FC
_021DB5E2:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021DB5EE: ; jump table
	.short _021DB5FA - _021DB5EE - 2 ; case 0
	.short _021DB63C - _021DB5EE - 2 ; case 1
	.short _021DB658 - _021DB5EE - 2 ; case 2
	.short _021DB690 - _021DB5EE - 2 ; case 3
	.short _021DB6BE - _021DB5EE - 2 ; case 4
	.short _021DB6E4 - _021DB5EE - 2 ; case 5
_021DB5FA:
	ldr r0, _021DB704 ; =0x0400004A
	mov r1, #0x3f
	ldrh r2, [r0]
	add r7, r4, #4
	bic r2, r1
	mov r1, #0x11
	orr r1, r2
	mov r2, #0x20
	orr r1, r2
	strh r1, [r0]
	lsl r0, r6, #2
	str r0, [sp]
	ldr r0, [r7, r0]
	mov r1, #0xc
	lsl r2, r2, #5
	bl FUN_02007558
	ldr r0, [sp]
	mov r2, #1
	ldr r0, [r7, r0]
	mov r1, #0xd
	lsl r2, r2, #0xa
	bl FUN_02007558
	ldr r0, [sp]
	mov r1, #6
	ldr r0, [r7, r0]
	mov r2, #0
	bl FUN_02007558
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
_021DB63C:
	ldr r2, _021DB708 ; =MOD63_021DBED8
	lsl r3, r6, #3
	ldr r2, [r2, r3]
	add r0, r4, #0
	add r1, r6, #0
	blx r2
	cmp r0, #0
	beq _021DB6FC
	mov r0, #0
	strb r0, [r4, #0x1d]
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
	b _021DB6FC
_021DB658:
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_02013440
	lsl r0, r6, #2
	str r0, [sp, #4]
	ldr r1, _021DB70C ; =MOD63_021DBF08
	lsl r6, r6, #3
	ldr r3, [sp, #4]
	add r7, r4, #4
	ldr r0, [r4, #0x18]
	ldr r1, [r1, r6]
	ldr r2, _021DB710 ; =MOD63_021DB940
	ldr r3, [r7, r3]
	bl FUN_020133AC
	ldr r1, _021DB714 ; =MOD63_021DBF0C
	ldr r3, [sp, #4]
	ldr r0, [r4, #0x18]
	ldr r1, [r1, r6]
	ldr r2, _021DB710 ; =MOD63_021DB940
	ldr r3, [r7, r3]
	bl FUN_020133AC
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
	b _021DB6FC
_021DB690:
	ldr r0, [r4, #0x18]
	bl FUN_020133C8
	cmp r0, #0
	bne _021DB6FC
	ldr r0, _021DB718 ; =MOD63_021DBEC0
	lsl r1, r6, #2
	ldr r0, [r0, r1]
	cmp r7, r0
	blt _021DB6FC
	ldr r1, _021DB704 ; =0x0400004A
	mov r0, #0x3f
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #0x10
	orr r2, r0
	mov r0, #0x20
	orr r0, r2
	strh r0, [r1]
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
	b _021DB6FC
_021DB6BE:
	ldr r2, _021DB71C ; =MOD63_021DBEDC
	lsl r3, r6, #3
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #0
	beq _021DB6FC
	lsl r0, r6, #2
	add r0, r4, r0
	ldr r0, [r0, #4]
	mov r1, #6
	mov r2, #1
	bl FUN_02007558
	mov r0, #0
	strb r0, [r4, #0x1d]
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
	b _021DB6FC
_021DB6E4:
	ldrb r0, [r4, #0x1d]
	add r0, r0, #1
	strb r0, [r4, #0x1d]
	ldrb r0, [r4, #0x1d]
	cmp r0, #0x14
	blo _021DB6FC
	mov r0, #0
	strb r0, [r4, #0x1d]
	strb r0, [r5]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DB6FC:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DB704: .word 0x0400004A
_021DB708: .word MOD63_021DBED8
_021DB70C: .word MOD63_021DBF08
_021DB710: .word MOD63_021DB940
_021DB714: .word MOD63_021DBF0C
_021DB718: .word MOD63_021DBEC0
_021DB71C: .word MOD63_021DBEDC
	thumb_func_end MOD63_021DB5CC

	thumb_func_start MOD63_021DB720
MOD63_021DB720: ; 0x021DB720
	push {r3, r4, r5, lr}
	add r5, r0, #0
	lsl r0, r1, #2
	add r0, r5, r0
	ldr r4, [r0, #4]
	mov r1, #0
	add r0, r4, #0
	mov r2, #6
	bl FUN_020079E0
	mov r1, #1
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x11
	bl FUN_020079E0
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x8c
	bl FUN_020079E0
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x8d
	bl FUN_020079E0
	ldrb r0, [r5, #0x1d]
	add r0, r0, #1
	strb r0, [r5, #0x1d]
	ldrb r0, [r5, #0x1d]
	cmp r0, #6
	blo _021DB780
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf3
	bl FUN_02007558
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DB780:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD63_021DB720

	thumb_func_start MOD63_021DB784
MOD63_021DB784: ; 0x021DB784
	push {r3, r4, r5, lr}
	add r5, r0, #0
	lsl r0, r1, #2
	add r0, r5, r0
	ldr r4, [r0, #4]
	mov r1, #0
	add r0, r4, #0
	sub r2, r1, #3
	bl FUN_020079E0
	mov r1, #1
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x13
	bl FUN_020079E0
	ldrb r0, [r5, #0x1d]
	add r0, r0, #1
	strb r0, [r5, #0x1d]
	ldrb r0, [r5, #0x1d]
	cmp r0, #6
	blo _021DB7CC
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf3
	bl FUN_02007558
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DB7CC:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD63_021DB784

	thumb_func_start MOD63_021DB7D0
MOD63_021DB7D0: ; 0x021DB7D0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	lsl r0, r1, #2
	add r0, r5, r0
	ldr r4, [r0, #4]
	mov r1, #0
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x10
	bl FUN_020079E0
	mov r1, #1
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x11
	bl FUN_020079E0
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x8c
	bl FUN_020079E0
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x8d
	bl FUN_020079E0
	ldrb r0, [r5, #0x1d]
	add r0, r0, #1
	strb r0, [r5, #0x1d]
	ldrb r0, [r5, #0x1d]
	cmp r0, #6
	blo _021DB832
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf3
	bl FUN_02007558
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DB832:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021DB7D0

	thumb_func_start MOD63_021DB838
MOD63_021DB838: ; 0x021DB838
	push {r3, r4, r5, lr}
	add r5, r0, #0
	lsl r0, r1, #2
	add r0, r5, r0
	ldr r4, [r0, #4]
	mov r1, #0
	add r0, r4, #0
	sub r2, r1, #6
	bl FUN_020079E0
	mov r1, #1
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x11
	bl FUN_020079E0
	ldrb r0, [r5, #0x1d]
	add r0, r0, #1
	strb r0, [r5, #0x1d]
	ldrb r0, [r5, #0x1d]
	cmp r0, #6
	blo _021DB880
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf3
	bl FUN_02007558
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DB880:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD63_021DB838

	thumb_func_start MOD63_021DB884
MOD63_021DB884: ; 0x021DB884
	push {r3, r4, r5, lr}
	add r5, r0, #0
	lsl r0, r1, #2
	add r0, r5, r0
	ldr r4, [r0, #4]
	mov r1, #0
	add r0, r4, #0
	mov r2, #8
	bl FUN_020079E0
	mov r1, #1
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x11
	bl FUN_020079E0
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x8c
	bl FUN_020079E0
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x8d
	bl FUN_020079E0
	ldrb r0, [r5, #0x1d]
	add r0, r0, #1
	strb r0, [r5, #0x1d]
	ldrb r0, [r5, #0x1d]
	cmp r0, #6
	blo _021DB8E4
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf3
	bl FUN_02007558
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DB8E4:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD63_021DB884

	thumb_func_start MOD63_021DB8E8
MOD63_021DB8E8: ; 0x021DB8E8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	lsl r0, r1, #2
	add r0, r5, r0
	ldr r4, [r0, #4]
	mov r1, #0
	add r0, r4, #0
	mov r2, #6
	bl FUN_020079E0
	mov r1, #1
	add r2, r1, #0
	add r0, r4, #0
	sub r2, #0x15
	bl FUN_020079E0
	ldrb r0, [r5, #0x1d]
	add r0, r0, #1
	strb r0, [r5, #0x1d]
	ldrb r0, [r5, #0x1d]
	cmp r0, #6
	blo _021DB930
	mov r1, #0xc
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0
	add r0, r4, #0
	add r2, #0xf3
	bl FUN_02007558
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DB930:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD63_021DB8E8

	thumb_func_start MOD63_021DB934
MOD63_021DB934: ; 0x021DB934
	push {r3, lr}
	bl FUN_02013364
	bl FUN_02013388
	pop {r3, pc}
	thumb_func_end MOD63_021DB934

	thumb_func_start MOD63_021DB940
MOD63_021DB940: ; 0x021DB940
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	bl FUN_0201341C
	add r2, sp, #0
	mov r1, #0
	str r1, [r2]
	str r1, [r2, #4]
	add r4, r0, #0
	str r1, [r2, #8]
	bl FUN_0200782C
	sub r0, #0x80
	mov r1, #0xac
	mul r1, r0
	str r1, [sp]
	add r0, r4, #0
	mov r1, #1
	bl FUN_0200782C
	sub r0, #0x60
	mov r1, #0xac
	mul r1, r0
	str r1, [sp, #4]
	mov r0, #0x40
	str r0, [sp, #8]
	ldr r0, [r5, #0x20]
	ldr r1, [sp]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	add r0, r1, r0
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r1, r0
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x20]
	ldr r1, [sp, #8]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	add r0, r1, r0
	str r0, [r5, #0x30]
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD63_021DB940

	.section .rodata

	.global MOD63_021DBF08
MOD63_021DBF08: ; 0x021DBF08
	.byte 0x04, 0x00, 0x00, 0x00

	.global MOD63_021DBF0C
MOD63_021DBF0C: ; 0x021DBF0C
	.byte 0x05, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
