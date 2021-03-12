	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021E2E88
MOD05_021E2E88: ; 0x021E2E88
	push {r4, r5, r6, lr}
	lsl r6, r1, #5
	add r5, r0, #0
	add r4, r2, #0
	add r1, r6, #0
	bl DC_FlushRange
	add r0, r5, #0
	lsl r1, r4, #5
	add r2, r6, #0
	bl GX_LoadBGPltt
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E2EA4
MOD05_021E2EA4: ; 0x021E2EA4
	push {r3, r4, lr}
	sub sp, #0x14
	mov r3, #0
	add r4, r0, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r2, #3
	add r1, r4, #0
	str r2, [sp, #8]
	mov r0, #7
	str r0, [sp, #0xc]
	ldr r0, _021E2EDC ; =0x000002CD
	add r1, #0x20
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x1c]
	bl FUN_02019064
	mov r0, #0
	str r0, [sp]
	ldr r2, _021E2EE0 ; =0x000003CF
	add r0, r4, #0
	mov r1, #3
	mov r3, #7
	bl MOD05_021E2EE4
	add sp, #0x14
	pop {r3, r4, pc}
	.balign 4, 0
_021E2EDC: .word 0x000002CD
_021E2EE0: .word 0x000003CF

	thumb_func_start MOD05_021E2EE4
MOD05_021E2EE4: ; 0x021E2EE4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r2, #0
	add r5, r0, #0
	add r6, r1, #0
	ldr r2, _021E2F2C ; =UNK05_021FD610
	add r0, #0x38
	mov r1, #4
	add r7, r3, #0
	bl FUN_0201AB28
	str r0, [r5, #0x34]
	add r3, r0, #0
	str r4, [sp]
	ldr r2, [r3, #0x14]
	ldr r0, [r5, #0x1c]
	ldr r3, [r3, #0x10]
	add r1, r6, #0
	bl FUN_02017E14
	ldr r2, _021E2F30 ; =UNK05_021FD62C
	add r0, sp, #4
	mov r1, #4
	bl FUN_0201AB44
	ldr r0, [r0, #0xc]
	mov r1, #1
	add r2, r7, #0
	bl MOD05_021E2E88
	ldr r0, [sp, #4]
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E2F2C: .word UNK05_021FD610
_021E2F30: .word UNK05_021FD62C

	thumb_func_start MOD05_021E2F34
MOD05_021E2F34: ; 0x021E2F34
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r2, r1, #0
	add r2, #8
	add r5, r0, #0
	asr r0, r2, #2
	lsr r0, r0, #0x1d
	add r0, r2, r0
	asr r0, r0, #3
	lsl r0, r0, #3
	sub r2, r0, r1
	lsr r0, r2, #0x1f
	add r0, r2, r0
	asr r0, r0, #1
	add r2, r0, #4
	cmp r2, #8
	blt _021E2F5A
	mov r3, #0
	b _021E2F6C
_021E2F5A:
	mov r0, #8
	sub r0, r0, r2
	lsl r0, r0, #1
	add r2, r0, #7
	asr r0, r2, #2
	lsr r0, r0, #0x1d
	add r0, r2, r0
	lsl r0, r0, #0x15
	lsr r3, r0, #0x18
_021E2F6C:
	cmp r1, #0
	bgt _021E2F76
	mov r0, #0
	str r0, [sp, #0x18]
	b _021E2F92
_021E2F76:
	add r2, r1, #0
	add r2, #8
	asr r0, r2, #2
	lsr r0, r0, #0x1d
	add r0, r2, r0
	asr r0, r0, #3
	add r0, r0, r3
	str r0, [sp, #0x18]
	lsl r0, r0, #3
	add r0, #8
	sub r1, r0, r1
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
_021E2F92:
	add r1, r0, #4
	add r0, r5, #0
	add r0, #0x30
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0x20
	mov r1, #0
	bl FUN_02019620
	mov r2, #8
	str r2, [sp]
	add r0, r5, #0
	str r2, [sp, #4]
	mov r3, #0
	str r3, [sp, #8]
	str r3, [sp, #0xc]
	str r2, [sp, #0x10]
	str r2, [sp, #0x14]
	ldr r1, [r5, #0x34]
	add r0, #0x20
	ldr r1, [r1, #0x14]
	bl FUN_02019658
	ldr r0, [sp, #0x18]
	mov r1, #8
	add r0, r0, #1
	lsl r4, r0, #3
	str r1, [sp]
	lsl r0, r4, #0x10
	str r1, [sp, #4]
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	mov r3, #0
	str r3, [sp, #0xc]
	str r1, [sp, #0x10]
	str r1, [sp, #0x14]
	ldr r1, [r5, #0x34]
	add r0, r5, #0
	ldr r1, [r1, #0x14]
	add r0, #0x20
	mov r2, #0x18
	bl FUN_02019658
	mov r0, #8
	str r0, [sp]
	str r0, [sp, #4]
	mov r3, #0
	str r3, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r1, [r5, #0x34]
	add r0, r5, #0
	ldr r1, [r1, #0x14]
	add r0, #0x20
	mov r2, #0x38
	bl FUN_02019658
	mov r1, #8
	str r1, [sp]
	lsl r0, r4, #0x10
	str r1, [sp, #4]
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	str r1, [sp, #0x14]
	ldr r1, [r5, #0x34]
	add r0, r5, #0
	ldr r1, [r1, #0x14]
	add r0, #0x20
	mov r2, #0x40
	mov r3, #0
	bl FUN_02019658
	mov r1, #8
	str r1, [sp]
	str r1, [sp, #4]
	mov r3, #0
	str r3, [sp, #8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
	str r1, [sp, #0x14]
	ldr r1, [r5, #0x34]
	add r0, r5, #0
	ldr r1, [r1, #0x14]
	add r0, #0x20
	mov r2, #0x20
	bl FUN_02019658
	mov r1, #8
	str r1, [sp]
	lsl r0, r4, #0x10
	str r1, [sp, #4]
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
	str r1, [sp, #0x14]
	ldr r1, [r5, #0x34]
	add r0, r5, #0
	ldr r1, [r1, #0x14]
	add r0, #0x20
	mov r2, #0x30
	mov r3, #0
	bl FUN_02019658
	ldr r0, [sp, #0x18]
	mov r7, #0
	cmp r0, #0
	ble _021E30F2
	add r6, r5, #0
	add r6, #0x20
_021E3078:
	add r0, r7, #1
	lsl r4, r0, #3
	mov r0, #8
	str r0, [sp]
	str r0, [sp, #4]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #8
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r1, [r5, #0x34]
	add r0, r6, #0
	ldr r1, [r1, #0x14]
	mov r2, #0x10
	mov r3, #0
	bl FUN_02019658
	mov r0, #8
	str r0, [sp]
	str r0, [sp, #4]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r1, [r5, #0x34]
	add r0, r6, #0
	ldr r1, [r1, #0x14]
	mov r2, #0x48
	mov r3, #0
	bl FUN_02019658
	mov r0, #8
	str r0, [sp]
	str r0, [sp, #4]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	mov r0, #8
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r1, [r5, #0x34]
	add r0, r6, #0
	ldr r1, [r1, #0x14]
	mov r2, #0x28
	mov r3, #0
	bl FUN_02019658
	add r0, r7, #1
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	ldr r0, [sp, #0x18]
	cmp r7, r0
	blt _021E3078
_021E30F2:
	add r5, #0x20
	add r0, r5, #0
	bl CopyWindowToVram
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E3100
MOD05_021E3100: ; 0x021E3100
	mov r1, #0
	str r1, [r0]
	strb r1, [r0, #4]
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	strh r1, [r0, #0x10]
	str r1, [r0, #0x14]
	str r1, [r0, #0x18]
	str r1, [r0, #0x1c]
	bx lr

	thumb_func_start MOD05_021E3114
MOD05_021E3114: ; 0x021E3114
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD05_021E3100
	str r4, [r5, #0x1c]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E3124
MOD05_021E3124: ; 0x021E3124
	push {r4, lr}
	add r4, r1, #0
	ldrb r0, [r4, #4]
	cmp r0, #3
	bhi _021E31D0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E313A: ; jump table
	.short _021E31D0 - _021E313A - 2 ; case 0
	.short _021E3142 - _021E313A - 2 ; case 1
	.short _021E3180 - _021E313A - 2 ; case 2
	.short _021E316A - _021E313A - 2 ; case 3
_021E3142:
	ldr r0, [r4, #0xc]
	sub r0, r0, #4
	str r0, [r4, #0xc]
	bpl _021E314E
	mov r0, #0
	str r0, [r4, #0xc]
_021E314E:
	mov r1, #3
	ldr r0, [r4, #0x1c]
	ldr r3, [r4, #0xc]
	add r2, r1, #0
	bl FUN_020179E0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	bne _021E31D0
	mov r0, #0
	strh r0, [r4, #0x10]
	mov r0, #3
	strb r0, [r4, #4]
	pop {r4, pc}
_021E316A:
	ldrh r0, [r4, #0x10]
	add r0, r0, #1
	strh r0, [r4, #0x10]
	ldrh r0, [r4, #0x10]
	cmp r0, #0x3c
	blo _021E31D0
	mov r0, #0
	strh r0, [r4, #0x10]
	mov r0, #2
	strb r0, [r4, #4]
	pop {r4, pc}
_021E3180:
	ldr r0, [r4, #0xc]
	add r0, r0, #4
	str r0, [r4, #0xc]
	cmp r0, #0x26
	ble _021E318E
	mov r0, #0x26
	str r0, [r4, #0xc]
_021E318E:
	mov r1, #3
	ldr r0, [r4, #0x1c]
	ldr r3, [r4, #0xc]
	add r2, r1, #0
	bl FUN_020179E0
	ldr r0, [r4, #0xc]
	cmp r0, #0x26
	bne _021E31D0
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021E31CA
	mov r0, #0
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x3c]
	ldr r1, [r4, #0x18]
	ldr r2, [r4, #0x40]
	bl FUN_02064E4C
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021E2F34
	ldr r1, [r4, #0x40]
	add r0, r4, #0
	bl MOD05_021E31D4
	mov r0, #1
	strb r0, [r4, #4]
	pop {r4, pc}
_021E31CA:
	add r0, r4, #0
	bl MOD05_021E32F0
_021E31D0:
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E31D4
MOD05_021E31D4: ; 0x021E31D4
	push {r3, lr}
	sub sp, #0x10
	add r3, r0, #0
	mov r0, #3
	add r2, r1, #0
	str r0, [sp]
	mov r1, #0
	ldr r0, _021E31FC ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r3, #0
	str r1, [sp, #0xc]
	add r3, #0x30
	ldrb r3, [r3]
	add r0, #0x20
	bl AddTextPrinterParameterized2
	add sp, #0x10
	pop {r3, pc}
	nop
_021E31FC: .word 0x00010200

	thumb_func_start MOD05_021E3200
MOD05_021E3200: ; 0x021E3200
	mov r1, #2
	strb r1, [r0, #4]
	mov r1, #0
	strh r1, [r0, #0x10]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021E320C
MOD05_021E320C: ; 0x021E320C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #4
	mov r1, #0x44
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0x16
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0x40]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD05_021E3114
	add r0, r4, #0
	bl MOD05_021E2EA4
	ldr r2, _021E3244 ; =0x0000017E
	mov r0, #1
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	str r0, [r4, #0x3c]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021E3244: .word 0x0000017E

	thumb_func_start MOD05_021E3248
MOD05_021E3248: ; 0x021E3248
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x3c]
	bl DestroyMsgData
	add r0, r4, #0
	add r0, #0x20
	bl FUN_02019178
	ldr r0, [r4, #0x40]
	bl String_dtor
	ldr r0, [r4, #0x38]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E3270
MOD05_021E3270: ; 0x021E3270
	push {r4, lr}
	add r4, r0, #0
	str r1, [r4, #0x18]
	ldr r1, [r4]
	cmp r1, #0
	bne _021E32BC
	mov r0, #1
	str r0, [r4]
	mov r1, #3
	ldr r0, [r4, #0x1c]
	add r2, r1, #0
	mov r3, #0x26
	bl FUN_020179E0
	mov r0, #0x26
	str r0, [r4, #0xc]
	ldr r0, _021E32EC ; =MOD05_021E3124
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	str r0, [r4, #8]
	mov r0, #1
	strb r0, [r4, #4]
	ldr r0, [r4, #0x3c]
	ldr r1, [r4, #0x18]
	ldr r2, [r4, #0x40]
	bl FUN_02064E4C
	add r1, r0, #0
	add r0, r4, #0
	bl MOD05_021E2F34
	ldr r1, [r4, #0x40]
	add r0, r4, #0
	bl MOD05_021E31D4
	pop {r4, pc}
_021E32BC:
	ldrb r1, [r4, #4]
	cmp r1, #3
	bhi _021E32E6
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E32CE: ; jump table
	.short _021E32E6 - _021E32CE - 2 ; case 0
	.short _021E32D6 - _021E32CE - 2 ; case 1
	.short _021E32E0 - _021E32CE - 2 ; case 2
	.short _021E32D6 - _021E32CE - 2 ; case 3
_021E32D6:
	bl MOD05_021E3200
	mov r0, #1
	str r0, [r4, #0x14]
	pop {r4, pc}
_021E32E0:
	mov r0, #1
	str r0, [r4, #0x14]
	pop {r4, pc}
_021E32E6:
	bl ErrorHandling
	pop {r4, pc}
	.balign 4, 0
_021E32EC: .word MOD05_021E3124

	thumb_func_start MOD05_021E32F0
MOD05_021E32F0: ; 0x021E32F0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021E32FE
	bl FUN_0200CAB4
_021E32FE:
	add r0, r4, #0
	add r0, #0x20
	bl FUN_02019570
	mov r1, #3
	ldr r0, [r4, #0x1c]
	add r2, r1, #0
	mov r3, #0
	bl FUN_020179E0
	ldr r1, [r4, #0x1c]
	add r0, r4, #0
	bl MOD05_021E3114
	pop {r4, pc}

	thumb_func_start MOD05_021E331C
MOD05_021E331C: ; 0x021E331C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x1c]
	ldr r0, [r0]
	bl FUN_02034944
	cmp r0, #0
	bne _021E333E
	ldr r0, [r4, #0x1c]
	ldr r0, [r0]
	bl FUN_02034824
	add r1, r0, #0
	ldr r0, [r4, #4]
	ldr r0, [r0, #8]
	bl MOD05_021E3270
_021E333E:
	pop {r4, pc}

	.section .data

	.balign 4
	.global UNK05_021FD610
UNK05_021FD610: ; 0x021FD610
	.asciz "/data/dp_areawindow.NCGR"

	.balign 4
	.global UNK05_021FD62C
UNK05_021FD62C: ; 0x021FD62C
	.asciz "/data/dp_areawindow.NCLR"
