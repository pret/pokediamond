	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss
	.global UNK_021D5300
UNK_021D5300: ; 0x021D5300
	.space 0x60

    .text

	arm_func_start SNDi_CallAlarmHandler
SNDi_CallAlarmHandler: ; 0x020CF4B0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, _020CF50C ; =UNK_021D5300
	and r2, r0, #0xff
	mov r1, #0xc
	mla r3, r2, r1, r3
	mov r1, r0, asr #0x8
	ldrb r0, [r3, #0x8]
	and r1, r1, #0xff
	cmp r1, r0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r0, [r3, #0x4]
	blx r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CF50C: .word UNK_021D5300

	arm_func_start SNDi_SetAlarmHandler
SNDi_SetAlarmHandler:
	mov r3, #0xc
	mul r3, r0, r3
	ldr r0, _020CF53C ; =UNK_021D5300
	str r1, [r0, r3]
	add r1, r0, r3
	str r2, [r1, #0x4]
	ldrb r0, [r1, #0x8]
	add r0, r0, #0x1
	strb r0, [r1, #0x8]
	ldrb r0, [r1, #0x8]
	bx lr
	.balign 4
_020CF53C: .word UNK_021D5300

	arm_func_start SNDi_IncAlarmId
SNDi_IncAlarmId: ; 0x020CF540
	ldr r2, _020CF55C ; =UNK_021D5300
	mov r1, #0xc
	mla r1, r0, r1, r2
	ldrb r0, [r1, #0x8]
	add r0, r0, #0x1
	strb r0, [r1, #0x8]
	bx lr
	.balign 4
_020CF55C: .word UNK_021D5300

	arm_func_start SND_AlarmInit
SND_AlarmInit: ; 0x020CF560
	ldr r1, _020CF58C ; =UNK_021D5300
	mov r2, #0x0
	mov r0, r2
_020CF56C:
	str r0, [r1, #0x0]
	str r0, [r1, #0x4]
	add r2, r2, #0x1
	strb r0, [r1, #0x8]
	cmp r2, #0x8
	add r1, r1, #0xc
	blt _020CF56C
	bx lr
	.balign 4
_020CF58C: .word UNK_021D5300
