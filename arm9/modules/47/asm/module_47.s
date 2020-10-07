	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD47_02254854
MOD47_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x24
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD47_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD47_022548E0
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
	bl FreeToHeap
_02254892:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254898: .word MOD47_022548E0
	thumb_func_end MOD47_02254854

	thumb_func_start MOD47_0225489C
MOD47_0225489C: ; 0x0225489C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r0, #0x14
	add r1, r5, #4
	bl MOD47_02254D14
	cmp r0, #0
	beq _022548C8
	mov r1, #0
	strb r1, [r5]
	strb r1, [r5, #1]
	add r0, r5, #0
	strb r1, [r5, #2]
	add r0, #0x20
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0x21
	strb r1, [r0]
	str r4, [r5, #0x18]
	mov r0, #1
	pop {r3, r4, r5, pc}
_022548C8:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD47_0225489C

	thumb_func_start MOD47_022548CC
MOD47_022548CC: ; 0x022548CC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	bl MOD47_02254D6C
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD47_022548CC

	thumb_func_start MOD47_022548E0
MOD47_022548E0: ; 0x022548E0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #6
	bhs _02254914
	add r0, r4, #0
	bl MOD47_02254C6C
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _02254918 ; =MOD47_022553B8
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254914
	add r0, r4, #0
	bl MOD47_022548CC
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x18]
	bl MOD20_022529A0
_02254914:
	pop {r3, r4, r5, pc}
	nop
_02254918: .word MOD47_022553B8
	thumb_func_end MOD47_022548E0

	thumb_func_start MOD47_0225491C
MOD47_0225491C: ; 0x0225491C
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD47_0225491C

	thumb_func_start MOD47_02254924
MOD47_02254924: ; 0x02254924
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _0225492C
	b _0225492E
_0225492C:
	mov r1, #5
_0225492E:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD47_02254924

	thumb_func_start MOD47_02254938
MOD47_02254938: ; 0x02254938
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254948
	cmp r0, #1
	beq _02254958
	b _02254972
_02254948:
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl MOD47_02254E24
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254972
_02254958:
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl MOD47_02254E48
	cmp r0, #0
	beq _02254972
	ldr r0, [r4, #0x18]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD47_02254924
_02254972:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD47_02254938

	thumb_func_start MOD47_02254978
MOD47_02254978: ; 0x02254978
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _0225498C
	mov r1, #5
	bl MOD47_02254924
	mov r0, #0
	pop {r3, r4, r5, pc}
_0225498C:
	ldrb r1, [r4, #1]
	cmp r1, #0
	bne _022549DA
	bl MOD47_02254BD4
	cmp r0, #0
	beq _022549DA
	add r0, r4, #0
	bl MOD47_02254D04
	cmp r0, #0
	beq _022549D4
	ldr r0, [r4, #0x18]
	bl MOD20_02252C38
	add r5, r0, #0
	ldr r0, [r4, #0x14]
	mov r1, #3
	bl MOD47_02254E24
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	bl FUN_02034984
	cmp r0, #0
	beq _022549CA
	add r0, r4, #0
	mov r1, #3
	bl MOD47_02254924
	b _022549DA
_022549CA:
	add r0, r4, #0
	mov r1, #2
	bl MOD47_02254924
	b _022549DA
_022549D4:
	ldr r0, _022549E0 ; =0x0000066E
	bl MOD20_02252B28
_022549DA:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_022549E0: .word 0x0000066E
	thumb_func_end MOD47_02254978

	thumb_func_start MOD47_022549E4
MOD47_022549E4: ; 0x022549E4
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _022549F8
	mov r1, #5
	bl MOD47_02254924
	mov r0, #0
	pop {r4, pc}
_022549F8:
	ldrb r1, [r4, #1]
	cmp r1, #0
	beq _02254A08
	cmp r1, #1
	beq _02254A18
	cmp r1, #2
	beq _02254A60
	b _02254AAC
_02254A08:
	bl MOD47_02254CCC
	mov r0, #0
	str r0, [r4, #0x1c]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254AAC
_02254A18:
	bl MOD47_02254AB0
	cmp r0, #0
	beq _02254A2C
	add r0, r4, #0
	mov r1, #4
	bl MOD47_02254924
	mov r0, #0
	pop {r4, pc}
_02254A2C:
	ldr r0, [r4, #0x1c]
	cmp r0, #0x3c
	bhs _02254A36
	add r0, r0, #1
	str r0, [r4, #0x1c]
_02254A36:
	add r0, r4, #0
	bl MOD47_02254CEC
	cmp r0, #0
	beq _02254AAC
	ldr r0, [r4, #0x1c]
	cmp r0, #0x3c
	blo _02254AAC
	add r0, r4, #0
	bl MOD47_02254C1C
	ldr r0, [r4, #0x14]
	mov r1, #6
	bl MOD47_02254E24
	mov r0, #0
	str r0, [r4, #0x1c]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254AAC
_02254A60:
	bl MOD47_02254AB0
	cmp r0, #0
	bne _02254A72
	add r0, r4, #0
	bl MOD47_02254BD4
	cmp r0, #0
	beq _02254A8C
_02254A72:
	add r0, r4, #0
	bl MOD47_02254CFC
	ldr r0, [r4, #0x14]
	mov r1, #2
	bl MOD47_02254E24
	add r0, r4, #0
	mov r1, #1
	bl MOD47_02254924
	mov r0, #0
	pop {r4, pc}
_02254A8C:
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
	cmp r0, #0x1e
	blo _02254AAC
	mov r0, #0
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD47_02254C1C
	cmp r0, #0
	beq _02254AAC
	ldr r0, [r4, #0x14]
	mov r1, #6
	bl MOD47_02254E24
_02254AAC:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD47_022549E4

	thumb_func_start MOD47_02254AB0
MOD47_02254AB0: ; 0x02254AB0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	bl MOD20_02252C08
	cmp r0, #0
	beq _02254AC2
	mov r0, #1
	pop {r4, pc}
_02254AC2:
	ldr r0, [r4, #0x18]
	bl MOD20_02252C30
	cmp r0, #0
	beq _02254AD0
	mov r0, #1
	pop {r4, pc}
_02254AD0:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD47_02254AB0

	thumb_func_start MOD47_02254AD4
MOD47_02254AD4: ; 0x02254AD4
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254AE8
	mov r1, #5
	bl MOD47_02254924
	mov r0, #0
	pop {r4, pc}
_02254AE8:
	ldrb r1, [r4, #1]
	cmp r1, #0
	beq _02254AF8
	cmp r1, #1
	beq _02254B02
	cmp r1, #2
	beq _02254B1C
	b _02254B34
_02254AF8:
	mov r0, #0
	str r0, [r4, #0x1c]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
_02254B02:
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
	cmp r0, #0x3c
	blo _02254B34
	ldr r0, [r4, #0x14]
	mov r1, #4
	bl MOD47_02254E24
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254B34
_02254B1C:
	bl MOD47_02254BD4
	cmp r0, #0
	beq _02254B34
	ldr r0, [r4, #0x14]
	mov r1, #2
	bl MOD47_02254E24
	add r0, r4, #0
	mov r1, #1
	bl MOD47_02254924
_02254B34:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD47_02254AD4

	thumb_func_start MOD47_02254B38
MOD47_02254B38: ; 0x02254B38
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254B4C
	mov r1, #5
	bl MOD47_02254924
	mov r0, #0
	pop {r4, pc}
_02254B4C:
	ldrb r1, [r4, #1]
	cmp r1, #0
	beq _02254B58
	cmp r1, #1
	beq _02254B6C
	b _02254B84
_02254B58:
	bl MOD47_02254CFC
	ldr r0, [r4, #0x14]
	mov r1, #5
	bl MOD47_02254E24
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254B84
_02254B6C:
	bl MOD47_02254BD4
	cmp r0, #0
	beq _02254B84
	ldr r0, [r4, #0x14]
	mov r1, #2
	bl MOD47_02254E24
	add r0, r4, #0
	mov r1, #1
	bl MOD47_02254924
_02254B84:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD47_02254B38

	thumb_func_start MOD47_02254B88
MOD47_02254B88: ; 0x02254B88
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #1]
	cmp r1, #0
	beq _02254B9C
	cmp r1, #1
	beq _02254BA6
	cmp r1, #2
	beq _02254BC0
	b _02254BCE
_02254B9C:
	bl MOD47_02254CFC
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
_02254BA6:
	add r0, r4, #0
	bl MOD47_02254D04
	cmp r0, #0
	beq _02254BCE
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl MOD47_02254E24
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254BCE
_02254BC0:
	ldr r0, [r4, #0x14]
	bl MOD47_02254E54
	cmp r0, #0
	beq _02254BCE
	mov r0, #1
	pop {r4, pc}
_02254BCE:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD47_02254B88

	thumb_func_start MOD47_02254BD4
MOD47_02254BD4: ; 0x02254BD4
	push {r3, lr}
	sub sp, #8
	ldr r0, [r0, #0x18]
	bl MOD20_02252C08
	cmp r0, #0
	bne _02254C14
	add r0, sp, #4
	add r1, sp, #0
	bl FUN_02020ACC
	cmp r0, #0
	beq _02254C14
	ldr r0, [sp, #4]
	sub r0, #0x10
	cmp r0, #0xbf
	bhs _02254BFA
	mov r1, #1
	b _02254BFC
_02254BFA:
	mov r1, #0
_02254BFC:
	ldr r0, [sp]
	sub r0, #0x10
	cmp r0, #0x9f
	bhs _02254C08
	mov r0, #1
	b _02254C0A
_02254C08:
	mov r0, #0
_02254C0A:
	tst r0, r1
	beq _02254C14
	add sp, #8
	mov r0, #1
	pop {r3, pc}
_02254C14:
	mov r0, #0
	add sp, #8
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD47_02254BD4

	thumb_func_start MOD47_02254C1C
MOD47_02254C1C: ; 0x02254C1C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r0, #0
	mov r0, #0
	ldr r5, _02254C68 ; =MOD47_022553D0
	str r0, [sp]
	str r0, [sp, #4]
_02254C2A:
	ldr r0, [r5, #4]
	mov r4, #0
	add r6, r4, #0
	cmp r0, #0
	bls _02254C46
_02254C34:
	ldr r0, [r5]
	ldrb r0, [r0, r4]
	bl FUN_0202F0DC
	add r6, r6, r0
	ldr r0, [r5, #4]
	add r4, r4, #1
	cmp r4, r0
	blo _02254C34
_02254C46:
	ldr r0, [r7, #4]
	cmp r6, r0
	beq _02254C52
	mov r0, #1
	str r6, [r7, #4]
	str r0, [sp]
_02254C52:
	ldr r0, [sp, #4]
	add r5, #8
	add r0, r0, #1
	add r7, r7, #4
	str r0, [sp, #4]
	cmp r0, #4
	blo _02254C2A
	ldr r0, [sp]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254C68: .word MOD47_022553D0
	thumb_func_end MOD47_02254C1C

	thumb_func_start MOD47_02254C6C
MOD47_02254C6C: ; 0x02254C6C
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #3
	bhi _02254CC8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02254C84: ; jump table
	.short _02254CC8 - _02254C84 - 2 ; case 0
	.short _02254C8C - _02254C84 - 2 ; case 1
	.short _02254C9C - _02254C84 - 2 ; case 2
	.short _02254CBA - _02254C84 - 2 ; case 3
_02254C8C:
	bl FUN_02032C28
	cmp r0, #0
	beq _02254CC8
	mov r0, #2
	add r4, #0x20
	strb r0, [r4]
	pop {r4, pc}
_02254C9C:
	add r0, r4, #0
	add r0, #0x21
	ldrb r0, [r0]
	cmp r0, #0
	beq _02254CC8
	bl FUN_02032C0C
	add r0, r4, #0
	mov r1, #0
	add r0, #0x21
	strb r1, [r0]
	mov r0, #3
	add r4, #0x20
	strb r0, [r4]
	pop {r4, pc}
_02254CBA:
	bl FUN_02030F40
	cmp r0, #0
	bne _02254CC8
	mov r0, #0
	add r4, #0x20
	strb r0, [r4]
_02254CC8:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD47_02254C6C

	thumb_func_start MOD47_02254CCC
MOD47_02254CCC: ; 0x02254CCC
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #0
	bne _02254CE8
	ldr r0, [r4, #0x18]
	bl MOD20_02252C40
	bl FUN_02032BD0
	mov r0, #1
	add r4, #0x20
	strb r0, [r4]
_02254CE8:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD47_02254CCC

	thumb_func_start MOD47_02254CEC
MOD47_02254CEC: ; 0x02254CEC
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #2
	bne _02254CF8
	mov r0, #1
	bx lr
_02254CF8:
	mov r0, #0
	bx lr
	thumb_func_end MOD47_02254CEC

	thumb_func_start MOD47_02254CFC
MOD47_02254CFC: ; 0x02254CFC
	mov r1, #1
	add r0, #0x21
	strb r1, [r0]
	bx lr
	thumb_func_end MOD47_02254CFC

	thumb_func_start MOD47_02254D04
MOD47_02254D04: ; 0x02254D04
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #0
	bne _02254D10
	mov r0, #1
	bx lr
_02254D10:
	mov r0, #0
	bx lr
	thumb_func_end MOD47_02254D04

	thumb_func_start MOD47_02254D14
MOD47_02254D14: ; 0x02254D14
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #8
	mov r1, #0x60
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254D62
	add r0, #8
	mov r1, #4
	bl MOD20_022536F4
	str r5, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	bl MOD20_02252D24
	str r0, [r4, #0x30]
	ldr r2, _02254D68 ; =0x0000019A
	mov r0, #1
	mov r1, #0x1a
	mov r3, #8
	bl NewMsgDataFromNarc
	str r0, [r4, #0x58]
	mov r0, #0x60
	mov r1, #8
	bl String_ctor
	str r0, [r4, #0x5c]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD47_02254D8C
	str r4, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254D62:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_02254D68: .word 0x0000019A
	thumb_func_end MOD47_02254D14

	thumb_func_start MOD47_02254D6C
MOD47_02254D6C: ; 0x02254D6C
	push {r4, lr}
	add r4, r0, #0
	beq _02254D8A
	ldr r0, [r4, #0x5c]
	bl String_dtor
	ldr r0, [r4, #0x58]
	bl DestroyMsgData
	add r0, r4, #0
	bl MOD47_02254DFC
	add r0, r4, #0
	bl FreeToHeap
_02254D8A:
	pop {r4, pc}
	thumb_func_end MOD47_02254D6C

	thumb_func_start MOD47_02254D8C
MOD47_02254D8C: ; 0x02254D8C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	add r6, r0, #0
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x63
	bl FUN_02006A34
	mov r0, #8
	str r0, [sp]
	add r0, r6, #0
	add r0, #0x44
	mov r1, #0xc
	mov r2, #0x61
	mov r3, #0x62
	bl MOD20_02253FBC
	add r0, r6, #0
	str r0, [sp, #0xc]
	add r0, #0x44
	ldr r4, _02254DF8 ; =MOD47_02255410
	mov r7, #0
	add r5, r6, #0
	str r0, [sp, #0xc]
_02254DC6:
	ldr r0, [r6, #0x30]
	ldr r2, [sp, #0xc]
	add r1, r4, #0
	bl MOD20_02253E74
	str r0, [r5, #0x34]
	add r7, r7, #1
	add r4, #0x10
	add r5, r5, #4
	cmp r7, #4
	blt _02254DC6
	ldr r0, [r6, #0x38]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r6, #0x3c]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r6, #0x40]
	mov r1, #1
	bl MOD20_02253F78
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254DF8: .word MOD47_02255410
	thumb_func_end MOD47_02254D8C

	thumb_func_start MOD47_02254DFC
MOD47_02254DFC: ; 0x02254DFC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_02254E04:
	ldr r1, [r5, #0x34]
	cmp r1, #0
	beq _02254E10
	ldr r0, [r6, #0x30]
	bl MOD20_02253F14
_02254E10:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _02254E04
	add r6, #0x44
	add r0, r6, #0
	bl MOD20_02254014
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD47_02254DFC

	thumb_func_start MOD47_02254E24
MOD47_02254E24: ; 0x02254E24
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254E44 ; =MOD47_02255450
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254E44: .word MOD47_02255450
	thumb_func_end MOD47_02254E24

	thumb_func_start MOD47_02254E48
MOD47_02254E48: ; 0x02254E48
	ldr r3, _02254E50 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254E50: .word MOD20_02253794
	thumb_func_end MOD47_02254E48

	thumb_func_start MOD47_02254E54
MOD47_02254E54: ; 0x02254E54
	ldr r3, _02254E5C ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254E5C: .word MOD20_022537B8
	thumb_func_end MOD47_02254E54

	thumb_func_start MOD47_02254E60
MOD47_02254E60: ; 0x02254E60
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD47_02254E60

	thumb_func_start MOD47_02254E74
MOD47_02254E74: ; 0x02254E74
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254F28 ; =MOD47_022553F4
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x60
	mov r3, #6
	bl FUN_0200687C
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x5f
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	mov r3, #2
	add r1, r5, #0
	str r3, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #0x14
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	lsl r0, r4, #0xb
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r5, #4]
	add r1, #0x20
	mov r2, #6
	bl FUN_02019064
	add r0, r5, #0
	add r0, #0x20
	bl FUN_02019270
	add r0, r5, #0
	bl MOD47_022550FC
	ldr r0, [r5, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r1, _02254F2C ; =0x04001000
	ldr r0, _02254F30 ; =0xFFFFE0FF
	ldr r3, [r1]
	ldr r2, [r1]
	str r3, [sp, #0x14]
	and r0, r2
	lsl r2, r3, #0x13
	lsr r3, r2, #0x1b
	mov r2, #4
	orr r2, r3
	lsl r2, r2, #8
	orr r0, r2
	str r0, [r1]
	add r0, r6, #0
	bl MOD47_02254E60
	add sp, #0x18
	pop {r4, r5, r6, pc}
	.align 2, 0
_02254F28: .word MOD47_022553F4
_02254F2C: .word 0x04001000
_02254F30: .word 0xFFFFE0FF
	thumb_func_end MOD47_02254E74

	thumb_func_start MOD47_02254F34
MOD47_02254F34: ; 0x02254F34
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, #0x20
	bl FUN_02019178
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r5, #0
	bl MOD47_02254E60
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD47_02254F34

	thumb_func_start MOD47_02254F58
MOD47_02254F58: ; 0x02254F58
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r4, #0x3c]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r4, #0x40]
	mov r1, #1
	bl MOD20_02253F78
	add r0, r4, #0
	bl MOD47_022550FC
	ldr r0, _02254F98 ; =0x00000663
	bl MOD20_02252B28
	add r0, r5, #0
	bl MOD47_02254E60
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254F98: .word 0x00000663
	thumb_func_end MOD47_02254F58

	thumb_func_start MOD47_02254F9C
MOD47_02254F9C: ; 0x02254F9C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r4, #0x38]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r4, #0x3c]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r4, #0x40]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl MOD20_02253F28
	add r0, r4, #0
	bl MOD47_02255184
	ldr r0, _02254FE4 ; =0x00000663
	bl MOD20_02252B28
	add r0, r5, #0
	bl MOD47_02254E60
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254FE4: .word 0x00000663
	thumb_func_end MOD47_02254F9C

	thumb_func_start MOD47_02254FE8
MOD47_02254FE8: ; 0x02254FE8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r4, #0x3c]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r4, #0x40]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r4, #0x3c]
	mov r1, #2
	bl MOD20_02253F28
	add r0, r4, #0
	bl MOD47_022551D8
	ldr r0, _02255030 ; =0x0000066E
	bl MOD20_02252B28
	add r0, r5, #0
	bl MOD47_02254E60
	pop {r3, r4, r5, pc}
	.align 2, 0
_02255030: .word 0x0000066E
	thumb_func_end MOD47_02254FE8

	thumb_func_start MOD47_02255034
MOD47_02255034: ; 0x02255034
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r4, #0x3c]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r4, #0x40]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r4, #0x3c]
	mov r1, #2
	bl MOD20_02253F28
	add r0, r4, #0
	bl MOD47_02255250
	ldr r0, _0225507C ; =0x0000066E
	bl MOD20_02252B28
	add r0, r5, #0
	bl MOD47_02254E60
	pop {r3, r4, r5, pc}
	.align 2, 0
_0225507C: .word 0x0000066E
	thumb_func_end MOD47_02255034

	thumb_func_start MOD47_02255080
MOD47_02255080: ; 0x02255080
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r6, r0, #0
	ldr r0, [r4, #0x34]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r4, #0x3c]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r4, #0x40]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r4, #0x40]
	mov r1, #0
	bl MOD20_02253F28
	add r0, r4, #0
	add r1, r6, #0
	bl MOD47_022552D8
	ldr r0, _022550D4 ; =0x00000663
	bl MOD20_02252B28
	add r0, r5, #0
	bl MOD47_02254E60
	pop {r4, r5, r6, pc}
	nop
_022550D4: .word 0x00000663
	thumb_func_end MOD47_02255080

	thumb_func_start MOD47_022550D8
MOD47_022550D8: ; 0x022550D8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r1, r0, #0
	add r0, r4, #0
	bl MOD47_022552D8
	add r0, r5, #0
	bl MOD47_02254E60
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD47_022550D8

	thumb_func_start MOD47_022550FC
MOD47_022550FC: ; 0x022550FC
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	add r0, #0x20
	mov r1, #4
	bl FUN_02019620
	ldr r0, [r4, #0x58]
	ldr r2, [r4, #0x5c]
	mov r1, #0
	bl ReadMsgDataIntoString
	mov r0, #0
	ldr r1, [r4, #0x5c]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xc0
	sub r0, r1, r0
	lsr r3, r0, #1
	mov r0, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02255180 ; =0x00010104
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x5c]
	add r0, #0x20
	bl AddTextPrinterParameterized2
	ldr r0, [r4, #0x58]
	ldr r2, [r4, #0x5c]
	mov r1, #0xa
	bl ReadMsgDataIntoString
	mov r0, #0
	ldr r1, [r4, #0x5c]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xc0
	sub r0, r1, r0
	lsr r3, r0, #1
	mov r0, #0x38
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02255180 ; =0x00010104
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x5c]
	add r0, #0x20
	bl AddTextPrinterParameterized2
	add r4, #0x20
	add r0, r4, #0
	bl FUN_02019548
	add sp, #0x10
	pop {r4, pc}
	nop
_02255180: .word 0x00010104
	thumb_func_end MOD47_022550FC

	thumb_func_start MOD47_02255184
MOD47_02255184: ; 0x02255184
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	add r0, #0x20
	mov r1, #4
	bl FUN_02019620
	ldr r0, [r4, #0x58]
	ldr r2, [r4, #0x5c]
	mov r1, #1
	bl ReadMsgDataIntoString
	mov r0, #0
	ldr r1, [r4, #0x5c]
	add r2, r0, #0
	bl FUN_02002F08
	mov r1, #0xc0
	sub r0, r1, r0
	lsr r3, r0, #1
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022551D4 ; =0x00010104
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x5c]
	add r0, #0x20
	bl AddTextPrinterParameterized2
	add r4, #0x20
	add r0, r4, #0
	bl FUN_02019548
	add sp, #0x10
	pop {r4, pc}
	nop
_022551D4: .word 0x00010104
	thumb_func_end MOD47_02255184

	thumb_func_start MOD47_022551D8
MOD47_022551D8: ; 0x022551D8
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	add r0, #0x20
	mov r1, #4
	bl FUN_02019620
	ldr r0, [r4, #0x58]
	ldr r2, [r4, #0x5c]
	mov r1, #2
	bl ReadMsgDataIntoString
	mov r0, #0
	ldr r1, [r4, #0x5c]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xc0
	sub r0, r1, r0
	lsr r3, r0, #1
	mov r0, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0225524C ; =0x00010104
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x5c]
	add r0, #0x20
	bl AddTextPrinterParameterized2
	ldr r0, [r4, #0x58]
	ldr r2, [r4, #0x5c]
	mov r1, #3
	bl ReadMsgDataIntoString
	mov r0, #0x18
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0225524C ; =0x00010104
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x5c]
	add r0, #0x20
	mov r3, #0x10
	bl AddTextPrinterParameterized2
	add r4, #0x20
	add r0, r4, #0
	bl FUN_02019548
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_0225524C: .word 0x00010104
	thumb_func_end MOD47_022551D8

	thumb_func_start MOD47_02255250
MOD47_02255250: ; 0x02255250
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	add r0, #0x20
	mov r1, #4
	bl FUN_02019620
	ldr r0, [r4, #0x58]
	ldr r2, [r4, #0x5c]
	mov r1, #2
	bl ReadMsgDataIntoString
	mov r0, #0
	ldr r1, [r4, #0x5c]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xc0
	sub r0, r1, r0
	lsr r3, r0, #1
	mov r0, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022552D4 ; =0x00010104
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x5c]
	add r0, #0x20
	bl AddTextPrinterParameterized2
	ldr r0, [r4, #0x58]
	ldr r2, [r4, #0x5c]
	mov r1, #4
	bl ReadMsgDataIntoString
	mov r0, #0
	ldr r1, [r4, #0x5c]
	add r2, r0, #0
	bl FUN_02002F08
	mov r1, #0xc0
	sub r0, r1, r0
	lsr r3, r0, #1
	mov r0, #0x18
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022552D4 ; =0x00010104
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x5c]
	add r0, #0x20
	bl AddTextPrinterParameterized2
	add r4, #0x20
	add r0, r4, #0
	bl FUN_02019548
	add sp, #0x10
	pop {r4, pc}
	nop
_022552D4: .word 0x00010104
	thumb_func_end MOD47_02255250

	thumb_func_start MOD47_022552D8
MOD47_022552D8: ; 0x022552D8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r7, r1, #0
	add r0, #0x20
	mov r1, #4
	bl FUN_02019620
	ldr r0, [r5, #0x58]
	ldr r2, [r5, #0x5c]
	mov r1, #5
	bl ReadMsgDataIntoString
	mov r0, #0
	ldr r1, [r5, #0x5c]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xc0
	sub r0, r1, r0
	lsr r3, r0, #1
	mov r0, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02255398 ; =0x00010104
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r5, #0
	ldr r2, [r5, #0x5c]
	add r0, #0x20
	bl AddTextPrinterParameterized2
	mov r0, #0
	str r0, [sp, #0x10]
	add r0, r5, #0
	str r0, [sp, #0x14]
	add r0, #0x20
	ldr r6, _0225539C ; =0x022553F0
	mov r4, #0x20
	str r0, [sp, #0x14]
_0225532C:
	ldrb r1, [r6]
	ldr r0, [r5, #0x58]
	ldr r2, [r5, #0x5c]
	bl ReadMsgDataIntoString
	str r4, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02255398 ; =0x00010104
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x14]
	ldr r2, [r5, #0x5c]
	mov r3, #8
	bl AddTextPrinterParameterized2
	mov r0, #1
	str r0, [sp]
	mov r2, #2
	ldr r0, [r5, #0x5c]
	ldr r1, [r7]
	add r3, r2, #0
	bl String16_FormatInteger
	str r4, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02255398 ; =0x00010104
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x14]
	ldr r2, [r5, #0x5c]
	mov r3, #0xa0
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	add r6, r6, #1
	add r0, r0, #1
	add r4, #0x10
	add r7, r7, #4
	str r0, [sp, #0x10]
	cmp r0, #4
	blt _0225532C
	add r5, #0x20
	add r0, r5, #0
	bl FUN_02019548
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02255398: .word 0x00010104
_0225539C: .word MOD47_022553F0
	thumb_func_end MOD47_022552D8

	.section .rodata

	.global MOD47_022553A0
MOD47_022553A0: ; 0x022553A0
	.byte 0x0A

	.balign 4, 0
	.global MOD47_022553A4
MOD47_022553A4: ; 0x022553A4
	.byte 0x09, 0x0D, 0x07, 0x12

	.balign 4, 0
	.global MOD47_022553A8
MOD47_022553A8: ; 0x022553A8
	.byte 0x01, 0x02, 0x03, 0x04, 0x05

	.balign 4, 0
	.global MOD47_022553B0
MOD47_022553B0: ; 0x022553B0
	.byte 0x00, 0x06, 0x08, 0x0B, 0x0C, 0x0E

	.balign 4, 0
	.global MOD47_022553B8
MOD47_022553B8: ; 0x022553B8
	.word MOD47_02254938, MOD47_02254978, MOD47_022549E4, MOD47_02254AD4
	.word MOD47_02254B38, MOD47_02254B88

	.global MOD47_022553D0
MOD47_022553D0: ; 0x022553D0
	.word MOD47_022553A4, 0x00000004
	.word MOD47_022553A0, 0x00000001
	.word MOD47_022553A8, 0x00000005
	.word MOD47_022553B0, 0x00000006

	.global MOD47_022553F0
MOD47_022553F0: ; 0x022553F0
	.byte 0x06, 0x07, 0x08, 0x09

	.global MOD47_022553F4
MOD47_022553F4: ; 0x022553F4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD47_02255410
MOD47_02255410: ; 0x02255410
	.byte 0x00, 0x00, 0x07, 0x00, 0x00, 0x60, 0x09, 0x00, 0x03, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x07, 0x00, 0x00, 0x60, 0x06, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x07, 0x00, 0x00, 0x60, 0x06, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x07, 0x00, 0x00, 0x60, 0x09, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00

	.global MOD47_02255450
MOD47_02255450: ; 0x02255450
	.word 0x00, MOD47_02254E74, 0x00
	.word 0x01, MOD47_02254F34, 0x00
	.word 0x02, MOD47_02254F58, 0x00
	.word 0x03, MOD47_02254F9C, 0x00
	.word 0x04, MOD47_02254FE8, 0x00
	.word 0x05, MOD47_02255034, 0x00
	.word 0x06, MOD47_02255080, 0x00
	.word 0x07, MOD47_022550D8, 0x00
	.word 0x00, 0x00000000, 0x00
