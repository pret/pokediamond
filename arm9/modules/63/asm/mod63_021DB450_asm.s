	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

	.extern MOD63_021DBED8
	.extern MOD63_021DBEC0
	.extern MOD63_021DBEDC
	.extern MOD63_021DBF08

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
