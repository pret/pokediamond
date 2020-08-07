    .include "asm/macros.inc"
    .include "global.inc"

	.extern gMain

	.section .rodata

	.global UNK_020F9CAC
UNK_020F9CAC: ; 0x020F9CAC
	.word FUN_02074480, FUN_020750C4, FUN_02073DF4, FUN_02073EB8
	.word FUN_02073EEC, FUN_020740AC, FUN_02074170, FUN_020741A4
	.word FUN_020743AC, 0xFFFFFFFE, 0xFFFFFFFE, FUN_02074E74
	.word FUN_02074FAC, FUN_02075090, FUN_020750F8, FUN_02075244
	.word FUN_020752D4, FUN_0207528C, FUN_02075274, FUN_020752A4
	.word FUN_0207525C, FUN_020752EC, FUN_020752BC, FUN_02075304
	.word FUN_0207531C, FUN_02075334, FUN_0207534C, FUN_02075364
	.word FUN_0207537C, FUN_02075398, 0xFFFFFFFE

	.text

	thumb_func_start FUN_02073DA8
FUN_02073DA8: ; 0x02073DA8
	lsl r1, r0, #0x2
	ldr r0, _02073DB0 ; =UNK_020F9CAC
	ldr r0, [r0, r1]
	bx lr
	.balign 4
_02073DB0: .word UNK_020F9CAC

	thumb_func_start FUN_02073DB4
FUN_02073DB4: ; 0x02073DB4
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x95
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200CCF8
	mov r0, #0x95
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	ldr r0, _02073DEC ; =0x000006FC
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_02001C5C
	ldr r0, _02073DF0 ; =0x000006F8
	ldr r0, [r4, r0]
	bl FUN_02012870
	mov r0, #0x95
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019178
	pop {r4, pc}
	.balign 4
_02073DEC: .word 0x000006FC
_02073DF0: .word 0x000006F8

	thumb_func_start FUN_02073DF4
FUN_02073DF4: ; 0x02073DF4
	push {r3-r6, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02073DB4
	add r0, r5, #0x0
	mov r1, #0x26
	mov r2, #0x0
	bl FUN_020731D4
	mov r0, #0x3
	mov r1, #0xc
	bl FUN_02012838
	ldr r1, _02073EB0 ; =0x000006F8
	str r0, [r5, r1]
	mov r0, #0x3
	bl FUN_02073DA8
	ldr r1, _02073EB0 ; =0x000006F8
	add r2, r0, #0x0
	ldr r0, [r5, r1]
	sub r1, #0x40
	ldr r1, [r5, r1]
	bl FUN_020128A0
	mov r0, #0x4
	bl FUN_02073DA8
	ldr r1, _02073EB0 ; =0x000006F8
	add r2, r0, #0x0
	ldr r0, [r5, r1]
	sub r1, #0x3c
	ldr r1, [r5, r1]
	bl FUN_020128A0
	mov r0, #0x9
	bl FUN_02073DA8
	ldr r1, _02073EB0 ; =0x000006F8
	add r2, r0, #0x0
	ldr r0, [r5, r1]
	sub r1, #0x28
	ldr r1, [r5, r1]
	bl FUN_020128A0
	ldr r0, _02073EB0 ; =0x000006F8
	mov r1, #0x0
	ldr r0, [r5, r0]
	add r2, sp, #0x8
	str r0, [sp, #0x8]
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r5, r0
	str r0, [sp, #0xc]
	strb r1, [r2, #0x8]
	mov r1, #0x1
	strb r1, [r2, #0x9]
	mov r3, #0x3
	strb r3, [r2, #0xa]
	ldrb r6, [r2, #0xb]
	mov r3, #0xf
	bic r6, r3
	strb r6, [r2, #0xb]
	ldrb r6, [r2, #0xb]
	mov r3, #0x30
	bic r6, r3
	strb r6, [r2, #0xb]
	ldrb r6, [r2, #0xb]
	mov r3, #0xc0
	bic r6, r3
	strb r6, [r2, #0xb]
	add r2, r1, #0x0
	mov r3, #0xe
	bl FUN_0200CCA4
	mov r0, #0xc
	str r0, [sp, #0x0]
	mov r0, #0x2
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0x8
	mov r1, #0x8
	add r3, r2, #0x0
	bl FUN_02001C14
	ldr r1, _02073EB4 ; =0x000006FC
	str r0, [r5, r1]
	mov r0, #0xd
	str r0, [r4, #0x0]
	add sp, #0x14
	pop {r3-r6, pc}
	nop
_02073EB0: .word 0x000006F8
_02073EB4: .word 0x000006FC

	thumb_func_start FUN_02073EB8
FUN_02073EB8: ; 0x02073EB8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02073EE0 ; =0x000006FC
	add r4, r1, #0x0
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_02001C5C
	ldr r0, _02073EE4 ; =0x000006F8
	ldr r0, [r5, r0]
	bl FUN_02012870
	ldr r0, _02073EE8 ; =0x000005A4
	mov r1, #0x3
	ldr r0, [r5, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	mov r0, #0x1b
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4
_02073EE0: .word 0x000006FC
_02073EE4: .word 0x000006F8
_02073EE8: .word 0x000005A4

	thumb_func_start FUN_02073EEC
FUN_02073EEC: ; 0x02073EEC
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r4, r1, #0x0
	add r0, r5, r0
	mov r1, #0x1
	bl FUN_0200CCF8
	ldr r0, _02074044 ; =0x000006FC
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_02001C5C
	ldr r0, _02074048 ; =0x000006F8
	ldr r0, [r5, r0]
	bl FUN_02012870
	ldr r0, _0207404C ; =0x00000B25
	ldrb r1, [r5, r0]
	mov r0, #0x2c
	mul r0, r1
	add r2, r5, r0
	ldr r0, _02074050 ; =0x0000070C
	ldrh r2, [r2, r0]
	ldr r0, _02074054 ; =0x000005A4
	cmp r2, #0x0
	bne _02073F66
	ldr r0, [r5, r0]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	ldr r2, _02074058 ; =0x0000069C
	add r6, r0, #0x0
	ldr r0, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	mov r1, #0x51
	bl ReadMsgDataIntoString
	add r0, r6, #0x0
	bl FUN_020690E4
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_0200ACF8
	mov r2, #0x6a
	lsl r2, r2, #0x4
	add r1, r2, #0x4
	ldr r0, [r5, r2]
	add r2, #0x8
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	bl FUN_0200B7B8
	b _02074018
_02073F66:
	ldr r0, [r5, r0]
	add r1, r2, #0x0
	ldr r0, [r0, #0x4]
	mov r2, #0x1
	mov r3, #0xc
	bl FUN_0206ED38
	cmp r0, #0x1
	bne _0207400A
	ldr r0, _02074054 ; =0x000005A4
	ldr r1, _0207404C ; =0x00000B25
	ldr r0, [r5, r0]
	ldrb r1, [r5, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	mov r1, #0x0
	str r1, [sp, #0x0]
	add r6, r0, #0x0
	mov r1, #0x6
	add r2, sp, #0x0
	bl SetMonData
	add r0, r6, #0x0
	bl FUN_02069EC4
	ldr r2, _02074058 ; =0x0000069C
	mov r1, #0x52
	ldr r0, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	add r0, r6, #0x0
	bl FUN_020690E4
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_0200ACF8
	ldr r2, _0207404C ; =0x00000B25
	mov r3, #0x6a
	ldrb r6, [r5, r2]
	mov r2, #0x2c
	lsl r3, r3, #0x4
	mul r2, r6
	ldr r0, [r5, r3]
	add r2, r5, r2
	add r3, #0x6c
	ldrh r2, [r2, r3]
	mov r1, #0x1
	bl FUN_0200AE38
	mov r2, #0x6a
	lsl r2, r2, #0x4
	add r1, r2, #0x4
	ldr r0, [r5, r2]
	add r2, #0x8
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	bl FUN_0200B7B8
	ldr r1, _0207404C ; =0x00000B25
	mov r2, #0x2c
	ldrb r3, [r5, r1]
	mov r0, #0x0
	add r6, r3, #0x0
	mul r6, r2
	ldr r3, _02074050 ; =0x0000070C
	add r6, r5, r6
	strh r0, [r6, r3]
	ldrb r1, [r5, r1]
	add r0, r5, #0x0
	mul r2, r1
	add r2, r5, r2
	ldrh r2, [r2, r3]
	bl FUN_02073A78
	b _02074018
_0207400A:
	ldr r2, _02074058 ; =0x0000069C
	mov r1, #0x53
	ldr r0, [r5, r2]
	add r2, #0x8
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
_02074018:
	mov r0, #0x89
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0x1
	mov r2, #0xa
	mov r3, #0xf
	bl FUN_0200D0BC
	mov r0, #0x89
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0xf
	bl FUN_02019620
	add r0, r5, #0x0
	bl FUN_0207322C
	mov r0, #0xf
	str r0, [r4, #0x0]
	add sp, #0x4
	pop {r3-r6, pc}
	nop
_02074044: .word 0x000006FC
_02074048: .word 0x000006F8
_0207404C: .word 0x00000B25
_02074050: .word 0x0000070C
_02074054: .word 0x000005A4
_02074058: .word 0x0000069C

	thumb_func_start FUN_0207405C
FUN_0207405C: ; 0x0207405C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020740A0 ; =0x00000B24
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _0207409A
	ldr r0, _020740A4 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _0207409A
	mov r0, #0x89
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	add r0, r4, #0x0
	mov r1, #0x1d
	mov r2, #0x1
	bl FUN_020731C0
	ldr r0, _020740A8 ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C664
	mov r0, #0x1
	pop {r4, pc}
_0207409A:
	mov r0, #0xf
	pop {r4, pc}
	nop
_020740A0: .word 0x00000B24
_020740A4: .word gMain
_020740A8: .word 0x000005C8

	thumb_func_start FUN_020740AC
FUN_020740AC: ; 0x020740AC
	push {r3-r6, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02073DB4
	add r0, r5, #0x0
	mov r1, #0x27
	mov r2, #0x0
	bl FUN_020731D4
	mov r0, #0x3
	mov r1, #0xc
	bl FUN_02012838
	ldr r1, _02074168 ; =0x000006F8
	str r0, [r5, r1]
	mov r0, #0x6
	bl FUN_02073DA8
	ldr r1, _02074168 ; =0x000006F8
	add r2, r0, #0x0
	ldr r0, [r5, r1]
	sub r1, #0x34
	ldr r1, [r5, r1]
	bl FUN_020128A0
	mov r0, #0x7
	bl FUN_02073DA8
	ldr r1, _02074168 ; =0x000006F8
	add r2, r0, #0x0
	ldr r0, [r5, r1]
	sub r1, #0x30
	ldr r1, [r5, r1]
	bl FUN_020128A0
	mov r0, #0x9
	bl FUN_02073DA8
	ldr r1, _02074168 ; =0x000006F8
	add r2, r0, #0x0
	ldr r0, [r5, r1]
	sub r1, #0x28
	ldr r1, [r5, r1]
	bl FUN_020128A0
	ldr r0, _02074168 ; =0x000006F8
	mov r1, #0x0
	ldr r0, [r5, r0]
	add r2, sp, #0x8
	str r0, [sp, #0x8]
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r5, r0
	str r0, [sp, #0xc]
	strb r1, [r2, #0x8]
	mov r1, #0x1
	strb r1, [r2, #0x9]
	mov r3, #0x3
	strb r3, [r2, #0xa]
	ldrb r6, [r2, #0xb]
	mov r3, #0xf
	bic r6, r3
	strb r6, [r2, #0xb]
	ldrb r6, [r2, #0xb]
	mov r3, #0x30
	bic r6, r3
	strb r6, [r2, #0xb]
	ldrb r6, [r2, #0xb]
	mov r3, #0xc0
	bic r6, r3
	strb r6, [r2, #0xb]
	add r2, r1, #0x0
	mov r3, #0xe
	bl FUN_0200CCA4
	mov r0, #0xc
	str r0, [sp, #0x0]
	mov r0, #0x2
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0x8
	mov r1, #0x8
	add r3, r2, #0x0
	bl FUN_02001C14
	ldr r1, _0207416C ; =0x000006FC
	str r0, [r5, r1]
	mov r0, #0xd
	str r0, [r4, #0x0]
	add sp, #0x14
	pop {r3-r6, pc}
	nop
_02074168: .word 0x000006F8
_0207416C: .word 0x000006FC

	thumb_func_start FUN_02074170
FUN_02074170: ; 0x02074170
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02074198 ; =0x000006FC
	add r4, r1, #0x0
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_02001C5C
	ldr r0, _0207419C ; =0x000006F8
	ldr r0, [r5, r0]
	bl FUN_02012870
	ldr r0, _020741A0 ; =0x000005A4
	mov r1, #0x7
	ldr r0, [r5, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	mov r0, #0x1b
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4
_02074198: .word 0x000006FC
_0207419C: .word 0x000006F8
_020741A0: .word 0x000005A4

	thumb_func_start FUN_020741A4
FUN_020741A4: ; 0x020741A4
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r4, r1, #0x0
	add r0, r5, r0
	mov r1, #0x1
	bl FUN_0200CCF8
	ldr r0, _020741EC ; =0x000006FC
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_02001C5C
	ldr r0, _020741F0 ; =0x000006F8
	ldr r0, [r5, r0]
	bl FUN_02012870
	add r0, r5, #0x0
	mov r1, #0x2b
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _020741F4 ; =FUN_02074200
	ldr r1, _020741F8 ; =0x00000B18
	ldr r2, _020741FC ; =FUN_02074278
	str r0, [r5, r1]
	add r0, r1, #0x4
	str r2, [r5, r0]
	mov r0, #0x16
	add r1, #0xa
	strb r0, [r5, r1]
	mov r0, #0x14
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	nop
_020741EC: .word 0x000006FC
_020741F0: .word 0x000006F8
_020741F4: .word FUN_02074200
_020741F8: .word 0x00000B18
_020741FC: .word FUN_02074278

	thumb_func_start FUN_02074200
FUN_02074200: ; 0x02074200
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, _02074268 ; =0x000005A4
	ldr r1, _0207426C ; =0x00000B25
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	add r1, r0, #0x0
	ldr r0, _02074268 ; =0x000005A4
	mov r2, #0xc
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x8]
	bl FUN_02085644
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _02074254
	ldr r1, _0207426C ; =0x00000B25
	mov r2, #0x2c
	ldrb r3, [r4, r1]
	mov r0, #0x0
	add r5, r3, #0x0
	mul r5, r2
	ldr r3, _02074270 ; =0x0000070C
	add r5, r4, r5
	strh r0, [r5, r3]
	ldrb r1, [r4, r1]
	add r0, r4, #0x0
	mul r2, r1
	add r2, r4, r2
	ldrh r2, [r2, r3]
	bl FUN_02073A78
	add r0, r4, #0x0
	mov r1, #0x2e
	mov r2, #0x0
	bl FUN_020731E8
	b _0207425E
_02074254:
	add r0, r4, #0x0
	mov r1, #0x32
	mov r2, #0x0
	bl FUN_020731E8
_0207425E:
	ldr r0, _02074274 ; =0x00000B22
	mov r1, #0x10
	strb r1, [r4, r0]
	mov r0, #0x14
	pop {r3-r5, pc}
	.balign 4
_02074268: .word 0x000005A4
_0207426C: .word 0x00000B25
_02074270: .word 0x0000070C
_02074274: .word 0x00000B22

	thumb_func_start FUN_02074278
FUN_02074278: ; 0x02074278
	push {r4, lr}
	mov r1, #0x2f
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_020731E8
	ldr r0, _0207429C ; =FUN_020742A8
	ldr r1, _020742A0 ; =0x00000B18
	ldr r2, _020742A4 ; =FUN_02074340
	str r0, [r4, r1]
	add r0, r1, #0x4
	str r2, [r4, r0]
	mov r0, #0x16
	add r1, #0xa
	strb r0, [r4, r1]
	mov r0, #0x14
	pop {r4, pc}
	nop
_0207429C: .word FUN_020742A8
_020742A0: .word 0x00000B18
_020742A4: .word FUN_02074340

	thumb_func_start FUN_020742A8
FUN_020742A8: ; 0x020742A8
	push {r3-r5, lr}
	ldr r1, _02074330 ; =0x00000B25
	add r4, r0, #0x0
	ldrb r2, [r4, r1]
	mov r1, #0x2c
	ldr r0, _02074334 ; =0x000005A4
	mul r1, r2
	add r2, r4, r1
	ldr r1, _02074338 ; =0x0000070C
	ldr r0, [r4, r0]
	ldrh r1, [r2, r1]
	ldr r0, [r0, #0x4]
	mov r2, #0x1
	mov r3, #0xc
	bl FUN_0206ED38
	cmp r0, #0x1
	bne _0207431A
	ldr r0, _02074334 ; =0x000005A4
	ldr r1, _02074330 ; =0x00000B25
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	mov r1, #0x0
	str r1, [sp, #0x0]
	add r5, r0, #0x0
	mov r1, #0x6
	add r2, sp, #0x0
	bl SetMonData
	add r0, r5, #0x0
	bl FUN_02069EC4
	ldr r1, _02074330 ; =0x00000B25
	mov r2, #0x2c
	ldrb r3, [r4, r1]
	mov r0, #0x0
	add r5, r3, #0x0
	mul r5, r2
	ldr r3, _02074338 ; =0x0000070C
	add r5, r4, r5
	strh r0, [r5, r3]
	ldrb r1, [r4, r1]
	add r0, r4, #0x0
	mul r2, r1
	add r2, r4, r2
	ldrh r2, [r2, r3]
	bl FUN_02073A78
	add r0, r4, #0x0
	mov r1, #0x33
	mov r2, #0x0
	bl FUN_020731E8
	b _02074324
_0207431A:
	add r0, r4, #0x0
	mov r1, #0x53
	mov r2, #0x0
	bl FUN_020731E8
_02074324:
	ldr r0, _0207433C ; =0x00000B22
	mov r1, #0x10
	strb r1, [r4, r0]
	mov r0, #0x14
	pop {r3-r5, pc}
	nop
_02074330: .word 0x00000B25
_02074334: .word 0x000005A4
_02074338: .word 0x0000070C
_0207433C: .word 0x00000B22

	thumb_func_start FUN_02074340
FUN_02074340: ; 0x02074340
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x89
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	add r0, r4, #0x0
	mov r1, #0x1d
	mov r2, #0x1
	bl FUN_020731C0
	ldr r0, _02074368 ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C664
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_02074368: .word 0x000005C8

	thumb_func_start FUN_0207436C
FUN_0207436C: ; 0x0207436C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020743A4 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _0207439E
	mov r0, #0x89
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	add r0, r4, #0x0
	mov r1, #0x1d
	mov r2, #0x1
	bl FUN_020731C0
	ldr r0, _020743A8 ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C664
	mov r0, #0x1
	pop {r4, pc}
_0207439E:
	mov r0, #0x10
	pop {r4, pc}
	nop
_020743A4: .word gMain
_020743A8: .word 0x000005C8

	thumb_func_start FUN_020743AC
FUN_020743AC: ; 0x020743AC
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r1, _0207440C ; =0x00000B25
	add r5, r0, #0x0
	ldrb r2, [r5, r1]
	mov r1, #0x2c
	mul r1, r2
	add r2, r5, r1
	ldr r1, _02074410 ; =0x00000712
	ldrh r2, [r2, r1]
	cmp r2, #0x0
	bne _020743E6
	sub r1, #0x16
	ldr r0, [r5, r1]
	mov r1, #0x0
	bl FUN_02001C5C
	ldr r0, _02074414 ; =0x000006F8
	ldr r0, [r5, r0]
	bl FUN_02012870
	ldr r0, _02074418 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r5, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	mov r0, #0x1b
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
_020743E6:
	bl FUN_02073DB4
	add r0, r5, #0x0
	mov r1, #0xc3
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _0207441C ; =FUN_02074428
	ldr r1, _02074420 ; =0x00000B18
	ldr r2, _02074424 ; =FUN_02074454
	str r0, [r5, r1]
	add r0, r1, #0x4
	str r2, [r5, r0]
	mov r0, #0x16
	add r1, #0xa
	strb r0, [r5, r1]
	mov r0, #0x14
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4
_0207440C: .word 0x00000B25
_02074410: .word 0x00000712
_02074414: .word 0x000006F8
_02074418: .word 0x000005A4
_0207441C: .word FUN_02074428
_02074420: .word 0x00000B18
_02074424: .word FUN_02074454

	thumb_func_start FUN_02074428
FUN_02074428: ; 0x02074428
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0207444C ; =0x000005A4
	ldr r1, _02074450 ; =0x00000B25
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	bl FUN_0206AA84
	ldr r0, _0207444C ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r4, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	mov r0, #0x1b
	pop {r4, pc}
	.balign 4
_0207444C: .word 0x000005A4
_02074450: .word 0x00000B25

	thumb_func_start FUN_02074454
FUN_02074454: ; 0x02074454
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x89
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	add r0, r4, #0x0
	mov r1, #0x1d
	mov r2, #0x1
	bl FUN_020731C0
	ldr r0, _0207447C ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C664
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0207447C: .word 0x000005C8

	thumb_func_start FUN_02074480
FUN_02074480: ; 0x02074480
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02074528 ; =0x00000B23
	add r4, r1, #0x0
	ldrb r2, [r5, r0]
	mov r1, #0x40
	orr r1, r2
	strb r1, [r5, r0]
	ldrb r1, [r5, r0]
	mov r2, #0x3f
	bic r1, r2
	add r2, r0, #0x2
	ldrb r3, [r5, r2]
	mov r2, #0x3f
	and r2, r3
	orr r1, r2
	strb r1, [r5, r0]
	ldr r0, _0207452C ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_0200C664
	ldr r0, _0207452C ; =0x000005C8
	add r1, sp, #0x0
	ldr r0, [r5, r0]
	add r1, #0x2
	add r2, sp, #0x0
	bl FUN_0200C75C
	ldr r0, _02074530 ; =0x000005CC
	add r3, sp, #0x0
	mov r1, #0x2
	mov r2, #0x0
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldr r0, [r5, r0]
	bl FUN_0200C6E4
	ldr r0, _02074534 ; =0x000005A4
	ldr r1, _02074528 ; =0x00000B23
	ldr r0, [r5, r0]
	ldrb r1, [r5, r1]
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1a
	bl FUN_020714BC
	add r1, r0, #0x0
	ldr r0, _02074530 ; =0x000005CC
	add r1, r1, #0x2
	ldr r0, [r5, r0]
	bl FUN_02020130
	ldr r0, _02074530 ; =0x000005CC
	mov r1, #0x1
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r1, _02074528 ; =0x00000B23
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1a
	bl FUN_020709FC
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	add r0, r5, #0x0
	bl FUN_02073DB4
	add r0, r5, #0x0
	mov r1, #0x1e
	mov r2, #0x1
	bl FUN_020731C0
	mov r0, #0x18
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	nop
_02074528: .word 0x00000B23
_0207452C: .word 0x000005C8
_02074530: .word 0x000005CC
_02074534: .word 0x000005A4

	thumb_func_start FUN_02074538
FUN_02074538: ; 0x02074538
	push {r4, lr}
	ldr r1, _02074578 ; =0x00000B23
	add r4, r0, #0x0
	ldrb r2, [r4, r1]
	mov r0, #0x40
	bic r2, r0
	strb r2, [r4, r1]
	ldr r0, _0207457C ; =0x000005CC
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	ldr r0, _02074580 ; =0x00000B25
	ldrb r1, [r4, r0]
	cmp r1, #0x6
	bhs _0207455E
	add r0, r4, #0x0
	bl FUN_020709FC
_0207455E:
	ldr r1, _02074578 ; =0x00000B23
	add r0, r4, #0x0
	ldrb r1, [r4, r1]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1a
	bl FUN_020709FC
	add r0, r4, #0x0
	mov r1, #0x1d
	mov r2, #0x1
	bl FUN_020731C0
	pop {r4, pc}
	.balign 4
_02074578: .word 0x00000B23
_0207457C: .word 0x000005CC
_02074580: .word 0x00000B25

	thumb_func_start FUN_02074584
FUN_02074584: ; 0x02074584
	push {r3-r7, lr}
	sub sp, #0x28
	ldr r2, _020746AC ; =0x00000B25
	add r6, r0, #0x0
	ldrb r1, [r6, r2]
	add r0, r2, #0x0
	sub r0, #0x19
	strb r1, [r6, r0]
	sub r0, r2, #0x2
	ldrb r0, [r6, r0]
	add r3, r2, #0x0
	sub r3, #0x13
	lsl r0, r0, #0x1a
	lsr r1, r0, #0x1a
	add r0, r2, #0x0
	sub r0, #0x18
	strb r1, [r6, r0]
	add r0, r2, #0x0
	mov r1, #0x1
	sub r0, #0x15
	strb r1, [r6, r0]
	mov r0, #0x0
	strb r0, [r6, r3]
	add r3, r2, #0x0
	sub r3, #0x14
	strb r0, [r6, r3]
	add r3, r2, #0x0
	sub r3, #0x19
	ldrb r3, [r6, r3]
	tst r3, r1
	beq _020745C8
	sub r2, #0x17
	strb r1, [r6, r2]
	b _020745CC
_020745C8:
	sub r2, #0x17
	strb r0, [r6, r2]
_020745CC:
	ldr r0, _020746B0 ; =0x00000B0D
	mov r1, #0x1
	ldrb r2, [r6, r0]
	tst r2, r1
	beq _020745D8
	b _020745DA
_020745D8:
	mov r1, #0x0
_020745DA:
	add r0, r0, #0x2
	strb r1, [r6, r0]
	ldr r0, [r6, #0x0]
	mov r1, #0x2
	bl FUN_0201886C
	str r0, [sp, #0x14]
	ldr r0, [r6, #0x0]
	mov r1, #0x1
	bl FUN_0201886C
	ldr r1, _020746B4 ; =0x00000B0C
	str r0, [sp, #0x10]
	ldrb r3, [r6, r1]
	add r1, r1, #0x1
	mov r2, #0x2c
	add r0, r3, #0x0
	ldrb r3, [r6, r1]
	mul r0, r2
	mov r4, #0x0
	add r1, r3, #0x0
	add r3, r6, r0
	ldr r0, _020746B8 ; =0x00000715
	mul r1, r2
	ldrsb r2, [r3, r0]
	str r2, [sp, #0xc]
	sub r2, r0, #0x1
	ldrsb r2, [r3, r2]
	str r2, [sp, #0x8]
	add r2, r6, r1
	ldrsb r1, [r2, r0]
	sub r0, r0, #0x1
	ldrsb r0, [r2, r0]
	str r1, [sp, #0x4]
	str r0, [sp, #0x0]
	ldr r0, _020746BC ; =0x0000080C
	add r0, r6, r0
	str r0, [sp, #0x18]
	ldr r0, _020746C0 ; =0x0000098C
	add r0, r6, r0
	str r0, [sp, #0x1c]
	ldr r0, _020746C4 ; =0x000008CC
	add r0, r6, r0
	str r0, [sp, #0x20]
	ldr r0, _020746C8 ; =0x00000A4C
	add r0, r6, r0
	str r0, [sp, #0x24]
_02074638:
	ldr r0, [sp, #0xc]
	lsl r5, r4, #0x5
	add r0, r0, r4
	lsl r1, r0, #0x5
	ldr r0, [sp, #0x8]
	mov r2, #0x20
	add r0, r0, r1
	lsl r7, r0, #0x1
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x14]
	add r0, r0, r5
	add r1, r1, r7
	bl memcpy
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x10]
	add r0, r0, r5
	add r1, r1, r7
	mov r2, #0x20
	bl memcpy
	ldr r0, [sp, #0x4]
	mov r2, #0x20
	add r0, r0, r4
	lsl r1, r0, #0x5
	ldr r0, [sp, #0x0]
	add r0, r0, r1
	lsl r7, r0, #0x1
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x14]
	add r0, r0, r5
	add r1, r1, r7
	bl memcpy
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x10]
	add r0, r0, r5
	add r1, r1, r7
	mov r2, #0x20
	bl memcpy
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x6
	blo _02074638
	ldr r0, _020746CC ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r6, r0]
	bl FUN_020200A0
	ldr r0, _020746D0 ; =0x000005CC
	mov r1, #0x0
	ldr r0, [r6, r0]
	bl FUN_020200A0
	add sp, #0x28
	pop {r3-r7, pc}
	.balign 4
_020746AC: .word 0x00000B25
_020746B0: .word 0x00000B0D
_020746B4: .word 0x00000B0C
_020746B8: .word 0x00000715
_020746BC: .word 0x0000080C
_020746C0: .word 0x0000098C
_020746C4: .word 0x000008CC
_020746C8: .word 0x00000A4C
_020746CC: .word 0x000005C8
_020746D0: .word 0x000005CC

	thumb_func_start FUN_020746D4
FUN_020746D4: ; 0x020746D4
	push {r3-r5, lr}
	ldr r1, _02074828 ; =0x0000080C
	add r5, r0, #0x0
	ldr r2, _0207482C ; =0x00000305
	add r4, r5, r1
	ldrb r1, [r4, r2]
	cmp r1, #0x4
	bls _020746E6
	b _02074822
_020746E6:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020746F2: ; jump table (using 16-bit offset)
	.short _020746FC - _020746F2 - 2; case 0
	.short _0207470C - _020746F2 - 2; case 1
	.short _0207475C - _020746F2 - 2; case 2
	.short _02074770 - _020746F2 - 2; case 3
	.short _020747CE - _020746F2 - 2; case 4
_020746FC:
	mov r0, #0x6a
	lsl r0, r0, #0x4
	bl FUN_020054C8
	ldr r0, _0207482C ; =0x00000305
	mov r1, #0x1
	strb r1, [r4, r0]
	b _02074822
_0207470C:
	add r1, r2, #0x1
	ldrb r1, [r4, r1]
	add r3, r1, #0x1
	add r1, r2, #0x1
	strb r3, [r4, r1]
	mov r1, #0x0
	bl FUN_02074848
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02074848
	ldr r2, _02074830 ; =0x00000302
	add r0, r5, #0x0
	ldrb r2, [r4, r2]
	mov r1, #0x0
	bl FUN_0207499C
	ldr r2, _02074834 ; =0x00000303
	add r0, r5, #0x0
	ldrb r2, [r4, r2]
	mov r1, #0x1
	bl FUN_0207499C
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	bl FUN_0201AC68
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	bl FUN_0201AC68
	ldr r0, _02074838 ; =0x00000306
	ldrb r1, [r4, r0]
	cmp r1, #0x10
	bne _02074822
	mov r1, #0x2
	sub r0, r0, #0x1
	strb r1, [r4, r0]
	b _02074822
_0207475C:
	bl FUN_02074AF4
	mov r0, #0x6a
	lsl r0, r0, #0x4
	bl FUN_020054C8
	ldr r0, _0207482C ; =0x00000305
	mov r1, #0x3
	strb r1, [r4, r0]
	b _02074822
_02074770:
	add r1, r2, #0x1
	ldrb r1, [r4, r1]
	sub r3, r1, #0x1
	add r1, r2, #0x1
	strb r3, [r4, r1]
	mov r1, #0x0
	bl FUN_02074848
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02074848
	ldr r2, _02074830 ; =0x00000302
	add r0, r5, #0x0
	ldrb r3, [r4, r2]
	mov r2, #0x1
	mov r1, #0x0
	eor r2, r3
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	bl FUN_0207499C
	ldr r2, _02074834 ; =0x00000303
	mov r1, #0x1
	ldrb r2, [r4, r2]
	add r0, r5, #0x0
	eor r2, r1
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	bl FUN_0207499C
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	bl FUN_0201AC68
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	bl FUN_0201AC68
	ldr r0, _02074838 ; =0x00000306
	ldrb r1, [r4, r0]
	cmp r1, #0x0
	bne _02074822
	mov r1, #0x4
	sub r0, r0, #0x1
	strb r1, [r4, r0]
	b _02074822
_020747CE:
	ldr r0, _0207483C ; =0x000005A4
	sub r1, r2, #0x5
	ldr r0, [r5, r0]
	sub r2, r2, #0x4
	ldrb r1, [r4, r1]
	ldrb r2, [r4, r2]
	ldr r0, [r0, #0x0]
	bl FUN_0206BA38
	ldr r0, _02074840 ; =0x000005C8
	mov r1, #0x1
	ldr r0, [r5, r0]
	bl FUN_020200A0
	mov r0, #0xc1
	mov r1, #0x0
	lsl r0, r0, #0x2
	strb r1, [r4, r0]
	ldr r1, _02074844 ; =0x00000B23
	mov r0, #0x40
	ldrb r2, [r5, r1]
	bic r2, r0
	strb r2, [r5, r1]
	add r1, r1, #0x2
	ldrb r1, [r5, r1]
	add r0, r5, #0x0
	bl FUN_020709FC
	ldr r1, _02074844 ; =0x00000B23
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1a
	bl FUN_020709FC
	add r0, r5, #0x0
	mov r1, #0x1d
	mov r2, #0x0
	bl FUN_020731C0
	mov r0, #0x1
	pop {r3-r5, pc}
_02074822:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_02074828: .word 0x0000080C
_0207482C: .word 0x00000305
_02074830: .word 0x00000302
_02074834: .word 0x00000303
_02074838: .word 0x00000306
_0207483C: .word 0x000005A4
_02074840: .word 0x000005C8
_02074844: .word 0x00000B23

	thumb_func_start FUN_02074848
FUN_02074848: ; 0x02074848
	push {r3-r7, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	ldr r0, _02074990 ; =0x0000080C
	str r1, [sp, #0x1c]
	ldr r1, [sp, #0x1c]
	add r4, r5, r0
	add r2, r4, r1
	mov r1, #0x3
	lsl r1, r1, #0x8
	ldrb r2, [r2, r1]
	mov r1, #0x2c
	mul r1, r2
	add r2, r5, r1
	add r1, r0, #0x0
	sub r1, #0xf8
	ldrsb r7, [r2, r1]
	sub r0, #0xf7
	ldrb r6, [r2, r0]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x20]
	str r6, [sp, #0x0]
	mov r1, #0x10
	str r1, [sp, #0x4]
	mov r0, #0x6
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	ldr r0, [r5, #0x0]
	ldr r3, [sp, #0x20]
	mov r1, #0x2
	mov r2, #0x0
	bl FUN_02018540
	str r6, [sp, #0x0]
	mov r1, #0x10
	str r1, [sp, #0x4]
	mov r0, #0x6
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	ldr r0, [r5, #0x0]
	ldr r3, [sp, #0x20]
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_02018540
	ldr r0, [sp, #0x1c]
	add r1, r4, r0
	ldr r0, _02074994 ; =0x00000302
	ldrb r1, [r1, r0]
	cmp r1, #0x0
	bne _02074918
	add r0, r0, #0x4
	ldrb r2, [r4, r0]
	ldr r0, [sp, #0x1c]
	mov r3, #0x10
	add r7, r0, #0x0
	sub r0, r3, r2
	lsl r0, r0, #0x18
	mov r1, #0xc0
	lsr r0, r0, #0x18
	mul r7, r1
	str r0, [sp, #0x0]
	mov r1, #0x6
	str r1, [sp, #0x4]
	add r0, r4, r7
	str r0, [sp, #0x8]
	str r2, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	str r3, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r0, [r5, #0x0]
	ldr r2, [sp, #0x20]
	mov r1, #0x2
	add r3, r6, #0x0
	bl FUN_02018170
	ldr r0, _02074998 ; =0x00000306
	mov r3, #0x10
	ldrb r2, [r4, r0]
	mov r1, #0x6
	sub r0, r3, r2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	lsl r0, r1, #0x6
	add r0, r4, r0
	str r1, [sp, #0x4]
	add r0, r0, r7
	str r0, [sp, #0x8]
	str r2, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	str r3, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r0, [r5, #0x0]
	ldr r2, [sp, #0x20]
	mov r1, #0x1
	add r3, r6, #0x0
	bl FUN_02018170
	add sp, #0x28
	pop {r3-r7, pc}
_02074918:
	ldr r1, [sp, #0x1c]
	mov r2, #0xc0
	mul r2, r1
	str r2, [sp, #0x24]
	add r0, r0, #0x4
	ldrb r2, [r4, r0]
	mov r3, #0x10
	ldr r1, [sp, #0x24]
	sub r0, r3, r2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x6
	str r0, [sp, #0x4]
	add r1, r4, r1
	str r1, [sp, #0x8]
	mov r1, #0x0
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	str r3, [sp, #0x14]
	add r2, r7, r2
	str r0, [sp, #0x18]
	lsl r2, r2, #0x18
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	lsr r2, r2, #0x18
	add r3, r6, #0x0
	bl FUN_02018170
	ldr r0, _02074998 ; =0x00000306
	ldrb r2, [r4, r0]
	mov r0, #0x10
	sub r0, r0, r2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x6
	lsl r1, r0, #0x6
	add r3, r4, r1
	ldr r1, [sp, #0x24]
	add r2, r7, r2
	add r1, r3, r1
	str r0, [sp, #0x4]
	str r1, [sp, #0x8]
	mov r1, #0x0
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	mov r1, #0x10
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	lsl r2, r2, #0x18
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	lsr r2, r2, #0x18
	add r3, r6, #0x0
	bl FUN_02018170
	add sp, #0x28
	pop {r3-r7, pc}
	nop
_02074990: .word 0x0000080C
_02074994: .word 0x00000302
_02074998: .word 0x00000306

	thumb_func_start FUN_0207499C
FUN_0207499C: ; 0x0207499C
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _02074AE0 ; =0x0000080C
	add r4, r1, #0x0
	add r1, r5, r0
	mov r0, #0x3
	lsl r0, r0, #0x8
	add r6, r1, r0
	ldrb r0, [r6, r4]
	add r7, r2, #0x0
	add r2, sp, #0x0
	lsl r0, r0, #0x2
	add r1, r5, r0
	mov r0, #0x5b
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	add r1, sp, #0x0
	add r1, #0x2
	bl FUN_0200C75C
	cmp r7, #0x0
	ldr r0, _02074AE4 ; =0x00000716
	bne _02074A04
	ldrb r3, [r6, r4]
	mov r7, #0x2c
	add r2, r5, r0
	add r1, r3, #0x0
	mul r1, r7
	ldrsh r3, [r2, r1]
	sub r3, #0x8
	strh r3, [r2, r1]
	ldrb r3, [r6, r4]
	add r1, r0, #0x4
	add r2, r5, r1
	add r1, r3, #0x0
	mul r1, r7
	ldrsh r3, [r2, r1]
	add r0, #0x8
	add r0, r5, r0
	sub r3, #0x8
	strh r3, [r2, r1]
	ldrb r1, [r6, r4]
	add r2, r1, #0x0
	mul r2, r7
	ldrsh r1, [r0, r2]
	sub r1, #0x8
	strh r1, [r0, r2]
	add r1, sp, #0x0
	mov r0, #0x2
	ldrsh r0, [r1, r0]
	sub r0, #0x8
	b _02074A3C
_02074A04:
	ldrb r3, [r6, r4]
	mov r7, #0x2c
	add r2, r5, r0
	add r1, r3, #0x0
	mul r1, r7
	ldrsh r3, [r2, r1]
	add r3, #0x8
	strh r3, [r2, r1]
	ldrb r3, [r6, r4]
	add r1, r0, #0x4
	add r2, r5, r1
	add r1, r3, #0x0
	mul r1, r7
	ldrsh r3, [r2, r1]
	add r0, #0x8
	add r0, r5, r0
	add r3, #0x8
	strh r3, [r2, r1]
	ldrb r1, [r6, r4]
	add r2, r1, #0x0
	mul r2, r7
	ldrsh r1, [r0, r2]
	add r1, #0x8
	strh r1, [r0, r2]
	add r1, sp, #0x0
	mov r0, #0x2
	ldrsh r0, [r1, r0]
	add r0, #0x8
_02074A3C:
	strh r0, [r1, #0x2]
	ldrb r1, [r6, r4]
	mov r0, #0x2c
	ldr r2, _02074AE8 ; =0x00000724
	mul r0, r1
	add r3, r5, r0
	add r1, r2, #0x0
	ldr r0, [r3, r2]
	sub r1, #0xe
	sub r2, #0xc
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	bl FUN_0200C6E4
	ldrb r2, [r6, r4]
	mov r0, #0x2c
	ldr r3, _02074AEC ; =0x0000071A
	add r1, r2, #0x0
	add r2, #0xa
	mul r1, r0
	lsl r0, r2, #0x2
	add r2, r5, r0
	mov r0, #0x5b
	lsl r0, r0, #0x4
	ldr r0, [r2, r0]
	add r2, r5, r1
	ldrsh r1, [r2, r3]
	add r3, r3, #0x2
	ldrsh r2, [r2, r3]
	bl FUN_0200C6E4
	ldrb r2, [r6, r4]
	mov r0, #0x2c
	ldr r3, _02074AF0 ; =0x0000071E
	add r1, r2, #0x0
	add r2, #0x10
	mul r1, r0
	lsl r0, r2, #0x2
	add r2, r5, r0
	mov r0, #0x5b
	lsl r0, r0, #0x4
	ldr r0, [r2, r0]
	add r2, r5, r1
	ldrsh r1, [r2, r3]
	add r3, r3, #0x2
	ldrsh r2, [r2, r3]
	bl FUN_0200C6E4
	ldrb r2, [r6, r4]
	mov r0, #0x2c
	ldr r3, _02074AF0 ; =0x0000071E
	add r1, r2, #0x0
	add r2, #0x16
	mul r1, r0
	lsl r0, r2, #0x2
	add r2, r5, r0
	mov r0, #0x5b
	lsl r0, r0, #0x4
	ldr r0, [r2, r0]
	add r2, r5, r1
	ldrsh r1, [r2, r3]
	add r3, r3, #0x2
	ldrsh r2, [r2, r3]
	add r1, #0x8
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	bl FUN_0200C6E4
	ldrb r0, [r6, r4]
	add r3, sp, #0x0
	mov r2, #0x0
	lsl r0, r0, #0x2
	add r1, r5, r0
	mov r0, #0x5b
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	mov r1, #0x2
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	bl FUN_0200C6E4
	pop {r3-r7, pc}
	.balign 4
_02074AE0: .word 0x0000080C
_02074AE4: .word 0x00000716
_02074AE8: .word 0x00000724
_02074AEC: .word 0x0000071A
_02074AF0: .word 0x0000071E

	thumb_func_start FUN_02074AF4
FUN_02074AF4: ; 0x02074AF4
	push {r4-r7, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	ldr r0, _02074DD0 ; =0x0000080C
	mov r1, #0x2c
	add r4, r5, r0
	mov r0, #0xc
	bl AllocFromHeap
	add r7, r0, #0x0
	mov r0, #0x3
	lsl r0, r0, #0x8
	ldrb r1, [r4, r0]
	mov r0, #0x2c
	add r3, r7, #0x0
	mul r0, r1
	add r1, r5, r0
	mov r0, #0x7
	lsl r0, r0, #0x8
	add r6, r1, r0
	mov r2, #0x5
_02074B1E:
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02074B1E
	ldr r0, [r6, #0x0]
	mov r1, #0x3
	lsl r1, r1, #0x8
	str r0, [r3, #0x0]
	ldrb r0, [r4, r1]
	add r1, r1, #0x1
	ldrb r1, [r4, r1]
	mov r2, #0x2c
	add r3, r0, #0x0
	mul r3, r2
	mul r2, r1
	mov r1, #0x7
	add r0, r5, r3
	lsl r1, r1, #0x8
	add r2, r5, r2
	add r6, r2, r1
	add r3, r0, r1
	mov r2, #0x5
_02074B4A:
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02074B4A
	ldr r0, [r6, #0x0]
	add r6, r7, #0x0
	str r0, [r3, #0x0]
	ldr r0, _02074DD4 ; =0x00000301
	mov r2, #0x5
	ldrb r1, [r4, r0]
	mov r0, #0x2c
	mul r0, r1
	add r1, r5, r0
	mov r0, #0x7
	lsl r0, r0, #0x8
	add r3, r1, r0
_02074B6A:
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02074B6A
	ldr r0, [r6, #0x0]
	add r1, r7, #0x0
	str r0, [r3, #0x0]
	mov r0, #0xc
	bl FUN_02016A8C
	mov r1, #0x3
	lsl r1, r1, #0x8
	ldrb r3, [r4, r1]
	ldr r0, _02074DD8 ; =0x00000716
	add r2, r5, r0
	mov r0, #0x2c
	add r7, r3, #0x0
	mul r7, r0
	ldrsh r3, [r2, r7]
	str r3, [sp, #0x0]
	add r3, r1, #0x1
	ldrb r3, [r4, r3]
	add r6, r3, #0x0
	mul r6, r0
	ldr r3, _02074DD8 ; =0x00000716
	add r6, r5, r6
	ldrsh r3, [r6, r3]
	strh r3, [r2, r7]
	add r2, r1, #0x1
	ldrb r2, [r4, r2]
	add r3, r2, #0x0
	mul r3, r0
	add r6, r5, r3
	ldr r3, [sp, #0x0]
	ldr r2, _02074DD8 ; =0x00000716
	strh r3, [r6, r2]
	add r2, r2, #0x2
	add r3, r5, r2
	ldrb r2, [r4, r1]
	add r7, r2, #0x0
	mul r7, r0
	ldrsh r2, [r3, r7]
	str r2, [sp, #0x4]
	add r2, r1, #0x1
	ldrb r2, [r4, r2]
	add r6, r2, #0x0
	mul r6, r0
	add r2, r5, r6
	ldr r6, _02074DD8 ; =0x00000716
	add r6, r6, #0x2
	ldrsh r2, [r2, r6]
	strh r2, [r3, r7]
	add r2, r1, #0x1
	ldrb r2, [r4, r2]
	add r3, r2, #0x0
	mul r3, r0
	add r2, r5, r3
	ldr r3, _02074DD8 ; =0x00000716
	add r6, r3, #0x2
	ldr r3, [sp, #0x4]
	strh r3, [r2, r6]
	ldr r2, _02074DD8 ; =0x00000716
	add r2, r2, #0x4
	add r3, r5, r2
	ldrb r2, [r4, r1]
	add r7, r2, #0x0
	mul r7, r0
	ldrsh r2, [r3, r7]
	str r2, [sp, #0x8]
	add r2, r1, #0x1
	ldrb r2, [r4, r2]
	add r6, r2, #0x0
	mul r6, r0
	add r2, r5, r6
	ldr r6, _02074DD8 ; =0x00000716
	add r6, r6, #0x4
	ldrsh r2, [r2, r6]
	strh r2, [r3, r7]
	add r2, r1, #0x1
	ldrb r2, [r4, r2]
	add r3, r2, #0x0
	mul r3, r0
	add r2, r5, r3
	ldr r3, _02074DD8 ; =0x00000716
	add r6, r3, #0x4
	ldr r3, [sp, #0x8]
	strh r3, [r2, r6]
	ldr r2, _02074DD8 ; =0x00000716
	add r2, r2, #0x6
	add r3, r5, r2
	ldrb r2, [r4, r1]
	add r7, r2, #0x0
	mul r7, r0
	ldrsh r2, [r3, r7]
	str r2, [sp, #0xc]
	add r2, r1, #0x1
	ldrb r2, [r4, r2]
	add r6, r2, #0x0
	mul r6, r0
	add r2, r5, r6
	ldr r6, _02074DD8 ; =0x00000716
	add r6, r6, #0x6
	ldrsh r2, [r2, r6]
	strh r2, [r3, r7]
	add r2, r1, #0x1
	ldrb r2, [r4, r2]
	add r3, r2, #0x0
	mul r3, r0
	add r2, r5, r3
	ldr r3, _02074DD8 ; =0x00000716
	add r6, r3, #0x6
	ldr r3, [sp, #0xc]
	strh r3, [r2, r6]
	ldr r2, _02074DD8 ; =0x00000716
	add r2, #0x8
	add r6, r5, r2
	ldrb r2, [r4, r1]
	add r7, r2, #0x0
	mul r7, r0
	ldrsh r2, [r6, r7]
	str r2, [sp, #0x10]
	add r2, r1, #0x1
	ldrb r2, [r4, r2]
	add r3, r2, #0x0
	mul r3, r0
	add r2, r5, r3
	ldr r3, _02074DD8 ; =0x00000716
	add r3, #0x8
	ldrsh r2, [r2, r3]
	strh r2, [r6, r7]
	add r2, r1, #0x1
	ldrb r2, [r4, r2]
	add r3, r2, #0x0
	mul r3, r0
	add r6, r5, r3
	ldr r3, _02074DD8 ; =0x00000716
	ldr r2, [sp, #0x10]
	add r3, #0x8
	strh r2, [r6, r3]
	ldr r2, _02074DD8 ; =0x00000716
	add r2, #0xa
	add r6, r5, r2
	ldrb r2, [r4, r1]
	add r7, r2, #0x0
	mul r7, r0
	ldrsh r2, [r6, r7]
	str r2, [sp, #0x14]
	add r2, r1, #0x1
	ldrb r2, [r4, r2]
	add r3, r2, #0x0
	mul r3, r0
	add r2, r5, r3
	ldr r3, _02074DD8 ; =0x00000716
	add r3, #0xa
	ldrsh r2, [r2, r3]
	strh r2, [r6, r7]
	add r2, r1, #0x1
	ldrb r2, [r4, r2]
	add r3, r2, #0x0
	mul r3, r0
	add r6, r5, r3
	ldr r3, _02074DD8 ; =0x00000716
	ldr r2, [sp, #0x14]
	add r3, #0xa
	strh r2, [r6, r3]
	ldr r2, _02074DD8 ; =0x00000716
	sub r2, r2, #0x2
	add r3, r5, r2
	ldrb r2, [r4, r1]
	add r7, r2, #0x0
	mul r7, r0
	ldrsb r2, [r3, r7]
	str r2, [sp, #0x18]
	add r2, r1, #0x1
	ldrb r2, [r4, r2]
	add r6, r2, #0x0
	mul r6, r0
	add r2, r5, r6
	ldr r6, _02074DD8 ; =0x00000716
	sub r6, r6, #0x2
	ldrsb r2, [r2, r6]
	strb r2, [r3, r7]
	add r2, r1, #0x1
	ldrb r2, [r4, r2]
	add r3, r2, #0x0
	mul r3, r0
	add r2, r5, r3
	ldr r3, _02074DD8 ; =0x00000716
	sub r6, r3, #0x2
	ldr r3, [sp, #0x18]
	strb r3, [r2, r6]
	ldr r2, _02074DD8 ; =0x00000716
	sub r2, r2, #0x1
	add r6, r5, r2
	ldrb r2, [r4, r1]
	add r7, r2, #0x0
	mul r7, r0
	ldrsb r2, [r6, r7]
	mov r12, r2
	add r2, r1, #0x1
	ldrb r2, [r4, r2]
	add r3, r2, #0x0
	ldr r2, _02074DD8 ; =0x00000716
	mul r3, r0
	add r3, r5, r3
	sub r2, r2, #0x1
	ldrsb r2, [r3, r2]
	strb r2, [r6, r7]
	add r2, r1, #0x1
	ldrb r2, [r4, r2]
	mul r0, r2
	ldr r2, _02074DD8 ; =0x00000716
	add r0, r5, r0
	sub r3, r2, #0x1
	mov r2, r12
	strb r2, [r0, r3]
	ldrb r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_02072D1C
	ldr r1, _02074DD4 ; =0x00000301
	add r0, r5, #0x0
	ldrb r1, [r4, r1]
	bl FUN_02072D1C
	mov r1, #0x3
	lsl r1, r1, #0x8
	ldrb r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_02072E14
	ldr r1, _02074DD4 ; =0x00000301
	add r0, r5, #0x0
	ldrb r1, [r4, r1]
	bl FUN_02072E14
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02074DE4
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02074DE4
	mov r0, #0x3
	lsl r0, r0, #0x8
	ldrb r1, [r4, r0]
	mov r2, #0x2c
	add r0, r5, #0x0
	mul r2, r1
	add r3, r5, r2
	ldr r2, _02074DDC ; =0x0000070E
	ldrh r2, [r3, r2]
	lsl r2, r2, #0x14
	lsr r2, r2, #0x14
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	bl FUN_02073A4C
	ldr r0, _02074DD4 ; =0x00000301
	mov r2, #0x2c
	ldrb r1, [r4, r0]
	add r0, r5, #0x0
	mul r2, r1
	add r3, r5, r2
	ldr r2, _02074DDC ; =0x0000070E
	ldrh r2, [r3, r2]
	lsl r2, r2, #0x14
	lsr r2, r2, #0x14
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	bl FUN_02073A4C
	mov r0, #0x3
	lsl r0, r0, #0x8
	ldrb r1, [r4, r0]
	mov r2, #0x2c
	add r0, r5, #0x0
	mul r2, r1
	add r3, r5, r2
	ldr r2, _02074DE0 ; =0x0000070C
	ldrh r2, [r3, r2]
	bl FUN_02073A78
	ldr r0, _02074DD4 ; =0x00000301
	mov r2, #0x2c
	ldrb r1, [r4, r0]
	add r0, r5, #0x0
	mul r2, r1
	add r3, r5, r2
	ldr r2, _02074DE0 ; =0x0000070C
	ldrh r2, [r3, r2]
	bl FUN_02073A78
	mov r1, #0x3
	lsl r1, r1, #0x8
	ldrb r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_02073B3C
	ldr r1, _02074DD4 ; =0x00000301
	add r0, r5, #0x0
	ldrb r1, [r4, r1]
	bl FUN_02073B3C
	add sp, #0x1c
	pop {r4-r7, pc}
	.balign 4
_02074DD0: .word 0x0000080C
_02074DD4: .word 0x00000301
_02074DD8: .word 0x00000716
_02074DDC: .word 0x0000070E
_02074DE0: .word 0x0000070C

	thumb_func_start FUN_02074DE4
FUN_02074DE4: ; 0x02074DE4
	push {r3-r7, lr}
	add r7, r1, #0x0
	ldr r1, _02074E6C ; =0x0000080C
	add r6, r0, #0x0
	add r4, r6, r1
	mov r1, #0xc0
	mul r1, r7
	add r5, r4, r1
	bl FUN_020703BC
	add r3, r0, #0x0
	mov r0, #0x3
	add r1, r4, r7
	lsl r0, r0, #0x8
	ldrb r1, [r1, r0]
	mov r0, #0x2c
	mul r0, r1
	add r1, r6, r0
	mov r0, #0x71
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	cmp r0, #0x1
	bne _02074E3C
	mov r3, #0xf
	mov r1, #0x0
	lsl r3, r3, #0xc
	mov r4, #0x17
_02074E1A:
	lsl r0, r1, #0x1
	add r2, r5, r0
	add r2, #0x6c
	ldrh r2, [r2, #0x0]
	add r0, r5, r0
	add r0, #0x6c
	and r2, r3
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	orr r2, r4
	strh r2, [r0, #0x0]
	add r0, r1, #0x1
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	cmp r1, #0x9
	blo _02074E1A
	pop {r3-r7, pc}
_02074E3C:
	mov r6, #0xf
	ldr r0, _02074E70 ; =0x00000FFF
	mov r4, #0x0
	lsl r6, r6, #0xc
_02074E44:
	lsl r2, r4, #0x1
	add r1, r5, r2
	add r1, #0x6c
	ldrh r1, [r1, #0x0]
	ldrh r7, [r3, r2]
	and r1, r6
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	and r7, r0
	orr r7, r1
	add r1, r5, r2
	add r1, #0x6c
	strh r7, [r1, #0x0]
	add r1, r4, #0x1
	lsl r1, r1, #0x10
	lsr r4, r1, #0x10
	cmp r4, #0x9
	blo _02074E44
	pop {r3-r7, pc}
	nop
_02074E6C: .word 0x0000080C
_02074E70: .word 0x00000FFF

	thumb_func_start FUN_02074E74
FUN_02074E74: ; 0x02074E74
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r6, r1, #0x0
	add r0, r5, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	add r0, r5, #0x0
	bl FUN_02073DB4
	ldr r0, _02074F5C ; =0x000005A4
	mov r4, #0x0
	ldr r0, [r5, r0]
	add r1, r0, #0x0
	add r1, #0x32
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1c
	beq _02074EFA
_02074E9E:
	add r2, r0, r4
	add r2, #0x2c
	ldrb r2, [r2, #0x0]
	cmp r2, #0x0
	bne _02074EF0
	ldr r1, _02074F60 ; =0x00000B25
	add r0, r0, r4
	ldrb r2, [r5, r1]
	add r0, #0x2c
	add r2, r2, #0x1
	strb r2, [r0, #0x0]
	ldrb r1, [r5, r1]
	add r0, r5, #0x0
	bl FUN_02073024
	add r0, r5, #0x0
	mov r1, #0x22
	mov r2, #0x1
	bl FUN_020731C0
	ldr r0, _02074F64 ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_0200C664
	ldr r0, _02074F5C ; =0x000005A4
	ldr r0, [r5, r0]
	add r0, #0x32
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	sub r0, r0, #0x1
	cmp r4, r0
	bne _02074EEA
	add r0, r5, #0x0
	mov r1, #0x6
	bl FUN_02070E60
_02074EEA:
	mov r0, #0x1
	str r0, [r6, #0x0]
	pop {r4-r6, pc}
_02074EF0:
	add r2, r4, #0x1
	lsl r2, r2, #0x18
	lsr r4, r2, #0x18
	cmp r4, r1
	blo _02074E9E
_02074EFA:
	cmp r1, #0x5
	bhi _02074F50
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02074F0A: ; jump table (using 16-bit offset)
	.short _02074F50 - _02074F0A - 2; case 0
	.short _02074F16 - _02074F0A - 2; case 1
	.short _02074F22 - _02074F0A - 2; case 2
	.short _02074F2E - _02074F0A - 2; case 3
	.short _02074F3A - _02074F0A - 2; case 4
	.short _02074F46 - _02074F0A - 2; case 5
_02074F16:
	add r0, r5, #0x0
	mov r1, #0x7b
	mov r2, #0x1
	bl FUN_020731E8
	b _02074F50
_02074F22:
	add r0, r5, #0x0
	mov r1, #0x64
	mov r2, #0x1
	bl FUN_020731E8
	b _02074F50
_02074F2E:
	add r0, r5, #0x0
	mov r1, #0x7c
	mov r2, #0x1
	bl FUN_020731E8
	b _02074F50
_02074F3A:
	add r0, r5, #0x0
	mov r1, #0x7d
	mov r2, #0x1
	bl FUN_020731E8
	b _02074F50
_02074F46:
	add r0, r5, #0x0
	mov r1, #0x7e
	mov r2, #0x1
	bl FUN_020731E8
_02074F50:
	ldr r0, _02074F68 ; =0x00000B22
	mov r1, #0x13
	strb r1, [r5, r0]
	mov r0, #0x14
	str r0, [r6, #0x0]
	pop {r4-r6, pc}
	.balign 4
_02074F5C: .word 0x000005A4
_02074F60: .word 0x00000B25
_02074F64: .word 0x000005C8
_02074F68: .word 0x00000B22

	thumb_func_start FUN_02074F6C
FUN_02074F6C: ; 0x02074F6C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02074FA4 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _02074F9E
	mov r0, #0x89
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	add r0, r4, #0x0
	mov r1, #0x22
	mov r2, #0x1
	bl FUN_020731C0
	ldr r0, _02074FA8 ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C664
	mov r0, #0x1
	pop {r4, pc}
_02074F9E:
	mov r0, #0x13
	pop {r4, pc}
	nop
_02074FA4: .word gMain
_02074FA8: .word 0x000005C8

	thumb_func_start FUN_02074FAC
FUN_02074FAC: ; 0x02074FAC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _02075080 ; =0x000005A4
	str r1, [sp, #0x0]
	ldr r1, [r5, r0]
	mov r4, #0x0
	add r0, r1, #0x0
	add r0, #0x32
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r2, r0, #0x1c
	beq _0207502C
	ldr r0, _02075084 ; =0x00000B25
	ldrb r0, [r5, r0]
	add r0, r0, #0x1
_02074FCA:
	add r3, r1, r4
	add r3, #0x2c
	ldrb r3, [r3, #0x0]
	cmp r0, r3
	bne _02075022
	add r0, r1, r4
	mov r2, #0x0
	add r0, #0x2c
	strb r2, [r0, #0x0]
	ldr r0, _02075080 ; =0x000005A4
	ldr r6, [r5, r0]
	add r0, r6, #0x0
	add r0, #0x32
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	sub r0, r0, #0x1
	cmp r4, r0
	bge _0207502C
	ldr r0, _02075080 ; =0x000005A4
	add r1, r0, #0x0
_02074FF4:
	add r3, r6, r4
	add r3, #0x2d
	ldrb r3, [r3, #0x0]
	add r6, r6, r4
	add r6, #0x2c
	strb r3, [r6, #0x0]
	ldr r3, [r5, r0]
	add r3, r3, r4
	add r3, #0x2d
	strb r2, [r3, #0x0]
	add r3, r4, #0x1
	lsl r3, r3, #0x18
	ldr r6, [r5, r1]
	lsr r4, r3, #0x18
	add r3, r6, #0x0
	add r3, #0x32
	ldrb r3, [r3, #0x0]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x1c
	sub r3, r3, #0x1
	cmp r4, r3
	blt _02074FF4
	b _0207502C
_02075022:
	add r3, r4, #0x1
	lsl r3, r3, #0x18
	lsr r4, r3, #0x18
	cmp r4, r2
	blo _02074FCA
_0207502C:
	ldr r6, _02075088 ; =0x00000729
	mov r4, #0x0
	mov r7, #0x2c
_02075032:
	add r0, r4, #0x0
	mul r0, r7
	add r0, r5, r0
	ldrb r0, [r0, r6]
	cmp r0, #0x0
	beq _02075046
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02073024
_02075046:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x6
	blo _02075032
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	add r0, r5, #0x0
	bl FUN_02073DB4
	add r0, r5, #0x0
	mov r1, #0x1d
	mov r2, #0x1
	bl FUN_020731C0
	ldr r0, _0207508C ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_0200C664
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	str r1, [r0, #0x0]
	pop {r3-r7, pc}
	nop
_02075080: .word 0x000005A4
_02075084: .word 0x00000B25
_02075088: .word 0x00000729
_0207508C: .word 0x000005C8

	thumb_func_start FUN_02075090
FUN_02075090: ; 0x02075090
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _020750B8 ; =0x000005A4
	add r4, r1, #0x0
	ldr r0, [r5, r0]
	mov r1, #0x0
	add r0, #0x23
	strb r1, [r0, #0x0]
	ldr r0, _020750BC ; =0x000006FC
	ldr r0, [r5, r0]
	bl FUN_02001C5C
	ldr r0, _020750C0 ; =0x000006F8
	ldr r0, [r5, r0]
	bl FUN_02012870
	mov r0, #0x1b
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	nop
_020750B8: .word 0x000005A4
_020750BC: .word 0x000006FC
_020750C0: .word 0x000006F8

	thumb_func_start FUN_020750C4
FUN_020750C4: ; 0x020750C4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _020750EC ; =0x000005A4
	add r4, r1, #0x0
	ldr r0, [r5, r0]
	mov r1, #0x1
	add r0, #0x23
	strb r1, [r0, #0x0]
	ldr r0, _020750F0 ; =0x000006FC
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_02001C5C
	ldr r0, _020750F4 ; =0x000006F8
	ldr r0, [r5, r0]
	bl FUN_02012870
	mov r0, #0x1b
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4
_020750EC: .word 0x000005A4
_020750F0: .word 0x000006FC
_020750F4: .word 0x000006F8

	thumb_func_start FUN_020750F8
FUN_020750F8: ; 0x020750F8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02073DB4
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	add r0, r5, #0x0
	bl FUN_02075118
	str r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02075118
FUN_02075118: ; 0x02075118
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02075190 ; =0x000005A4
	ldr r1, _02075194 ; =0x00000B25
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	mov r1, #0xa1
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	ldr r2, _02075198 ; =0x0000069C
	bne _0207515C
	ldr r0, [r4, r2]
	add r2, #0x8
	ldr r2, [r4, r2]
	mov r1, #0x81
	bl ReadMsgDataIntoString
	ldr r0, _02075194 ; =0x00000B25
	ldrb r0, [r4, r0]
	add r0, #0x16
	lsl r0, r0, #0x2
	add r1, r4, r0
	mov r0, #0x5b
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	mov r1, #0x1
	bl FUN_020200A0
	b _0207516E
_0207515C:
	ldr r0, [r4, r2]
	add r2, #0x8
	ldr r2, [r4, r2]
	mov r1, #0x82
	bl ReadMsgDataIntoString
	ldr r0, _02075194 ; =0x00000B25
	mov r1, #0x7
	strb r1, [r4, r0]
_0207516E:
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _02075190 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r4, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	ldr r0, _0207519C ; =0x00000B22
	mov r1, #0x15
	strb r1, [r4, r0]
	mov r0, #0x14
	pop {r4, pc}
	nop
_02075190: .word 0x000005A4
_02075194: .word 0x00000B25
_02075198: .word 0x0000069C
_0207519C: .word 0x00000B22

	thumb_func_start FUN_020751A0
FUN_020751A0: ; 0x020751A0
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r4, r0, #0x0
	ldr r1, _02075234 ; =0x000005A4
	mov r0, #0x1
	ldr r1, [r4, r1]
	add r1, #0x23
	ldrb r1, [r1, #0x0]
	sub r1, #0xb
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02063948
	add r1, r0, #0x0
	beq _020751C8
	ldr r0, _02075234 ; =0x000005A4
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x18]
	blx r1
	b _020751CA
_020751C8:
	mov r0, #0x1
_020751CA:
	cmp r0, #0x4
	bhi _0207520A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020751DA: ; jump table (using 16-bit offset)
	.short _020751E4 - _020751DA - 2; case 0
	.short _020751FC - _020751DA - 2; case 1
	.short _02075200 - _020751DA - 2; case 2
	.short _02075204 - _020751DA - 2; case 3
	.short _02075208 - _020751DA - 2; case 4
_020751E4:
	ldr r0, _02075238 ; =0x000006FC
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_02001C5C
	ldr r0, _0207523C ; =0x000006F8
	ldr r0, [r4, r0]
	bl FUN_02012870
	mov r0, #0x1b
	str r0, [r6, #0x0]
	pop {r4-r6, pc}
_020751FC:
	mov r5, #0x68
	b _0207520A
_02075200:
	mov r5, #0x4c
	b _0207520A
_02075204:
	mov r5, #0xc4
	b _0207520A
_02075208:
	mov r5, #0x66
_0207520A:
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	add r0, r4, #0x0
	bl FUN_02073DB4
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _02075240 ; =0x00000B22
	mov r1, #0x3
	strb r1, [r4, r0]
	mov r0, #0x14
	str r0, [r6, #0x0]
	pop {r4-r6, pc}
	nop
_02075234: .word 0x000005A4
_02075238: .word 0x000006FC
_0207523C: .word 0x000006F8
_02075240: .word 0x00000B22

	thumb_func_start FUN_02075244
FUN_02075244: ; 0x02075244
	ldr r2, _02075254 ; =0x000005A4
	mov r3, #0xb
	ldr r2, [r0, r2]
	add r2, #0x23
	strb r3, [r2, #0x0]
	ldr r3, _02075258 ; =FUN_020751A0
	bx r3
	nop
_02075254: .word 0x000005A4
_02075258: .word FUN_020751A0

	thumb_func_start FUN_0207525C
FUN_0207525C: ; 0x0207525C
	ldr r2, _0207526C ; =0x000005A4
	mov r3, #0x10
	ldr r2, [r0, r2]
	add r2, #0x23
	strb r3, [r2, #0x0]
	ldr r3, _02075270 ; =FUN_020751A0
	bx r3
	nop
_0207526C: .word 0x000005A4
_02075270: .word FUN_020751A0

	thumb_func_start FUN_02075274
FUN_02075274: ; 0x02075274
	ldr r2, _02075284 ; =0x000005A4
	mov r3, #0xe
	ldr r2, [r0, r2]
	add r2, #0x23
	strb r3, [r2, #0x0]
	ldr r3, _02075288 ; =FUN_020751A0
	bx r3
	nop
_02075284: .word 0x000005A4
_02075288: .word FUN_020751A0

	thumb_func_start FUN_0207528C
FUN_0207528C: ; 0x0207528C
	ldr r2, _0207529C ; =0x000005A4
	mov r3, #0xd
	ldr r2, [r0, r2]
	add r2, #0x23
	strb r3, [r2, #0x0]
	ldr r3, _020752A0 ; =FUN_020751A0
	bx r3
	nop
_0207529C: .word 0x000005A4
_020752A0: .word FUN_020751A0

	thumb_func_start FUN_020752A4
FUN_020752A4: ; 0x020752A4
	ldr r2, _020752B4 ; =0x000005A4
	mov r3, #0xf
	ldr r2, [r0, r2]
	add r2, #0x23
	strb r3, [r2, #0x0]
	ldr r3, _020752B8 ; =FUN_020751A0
	bx r3
	nop
_020752B4: .word 0x000005A4
_020752B8: .word FUN_020751A0

	thumb_func_start FUN_020752BC
FUN_020752BC: ; 0x020752BC
	ldr r2, _020752CC ; =0x000005A4
	mov r3, #0x12
	ldr r2, [r0, r2]
	add r2, #0x23
	strb r3, [r2, #0x0]
	ldr r3, _020752D0 ; =FUN_020751A0
	bx r3
	nop
_020752CC: .word 0x000005A4
_020752D0: .word FUN_020751A0

	thumb_func_start FUN_020752D4
FUN_020752D4: ; 0x020752D4
	ldr r2, _020752E4 ; =0x000005A4
	mov r3, #0xc
	ldr r2, [r0, r2]
	add r2, #0x23
	strb r3, [r2, #0x0]
	ldr r3, _020752E8 ; =FUN_020751A0
	bx r3
	nop
_020752E4: .word 0x000005A4
_020752E8: .word FUN_020751A0

	thumb_func_start FUN_020752EC
FUN_020752EC: ; 0x020752EC
	ldr r2, _020752FC ; =0x000005A4
	mov r3, #0x11
	ldr r2, [r0, r2]
	add r2, #0x23
	strb r3, [r2, #0x0]
	ldr r3, _02075300 ; =FUN_020751A0
	bx r3
	nop
_020752FC: .word 0x000005A4
_02075300: .word FUN_020751A0

	thumb_func_start FUN_02075304
FUN_02075304: ; 0x02075304
	ldr r2, _02075314 ; =0x000005A4
	mov r3, #0x13
	ldr r2, [r0, r2]
	add r2, #0x23
	strb r3, [r2, #0x0]
	ldr r3, _02075318 ; =FUN_020751A0
	bx r3
	nop
_02075314: .word 0x000005A4
_02075318: .word FUN_020751A0

	thumb_func_start FUN_0207531C
FUN_0207531C: ; 0x0207531C
	ldr r2, _0207532C ; =0x000005A4
	mov r3, #0x14
	ldr r2, [r0, r2]
	add r2, #0x23
	strb r3, [r2, #0x0]
	ldr r3, _02075330 ; =FUN_020751A0
	bx r3
	nop
_0207532C: .word 0x000005A4
_02075330: .word FUN_020751A0

	thumb_func_start FUN_02075334
FUN_02075334: ; 0x02075334
	ldr r2, _02075344 ; =0x000005A4
	mov r3, #0x15
	ldr r2, [r0, r2]
	add r2, #0x23
	strb r3, [r2, #0x0]
	ldr r3, _02075348 ; =FUN_020751A0
	bx r3
	nop
_02075344: .word 0x000005A4
_02075348: .word FUN_020751A0

	thumb_func_start FUN_0207534C
FUN_0207534C: ; 0x0207534C
	ldr r2, _0207535C ; =0x000005A4
	mov r3, #0x16
	ldr r2, [r0, r2]
	add r2, #0x23
	strb r3, [r2, #0x0]
	ldr r3, _02075360 ; =FUN_020751A0
	bx r3
	nop
_0207535C: .word 0x000005A4
_02075360: .word FUN_020751A0

	thumb_func_start FUN_02075364
FUN_02075364: ; 0x02075364
	ldr r2, _02075374 ; =0x000005A4
	mov r3, #0x17
	ldr r2, [r0, r2]
	add r2, #0x23
	strb r3, [r2, #0x0]
	ldr r3, _02075378 ; =FUN_020751A0
	bx r3
	nop
_02075374: .word 0x000005A4
_02075378: .word FUN_020751A0

	thumb_func_start FUN_0207537C
FUN_0207537C: ; 0x0207537C
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	bl FUN_020753B4
	str r0, [r5, #0x0]
	cmp r0, #0x1a
	bne _02075392
	ldr r0, _02075394 ; =0x00000B2E
	mov r1, #0xd
	strh r1, [r4, r0]
_02075392:
	pop {r3-r5, pc}
	.balign 4
_02075394: .word 0x00000B2E

	thumb_func_start FUN_02075398
FUN_02075398: ; 0x02075398
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	bl FUN_020753B4
	str r0, [r5, #0x0]
	cmp r0, #0x1a
	bne _020753AE
	ldr r0, _020753B0 ; =0x00000B2E
	mov r1, #0xe
	strh r1, [r4, r0]
_020753AE:
	pop {r3-r5, pc}
	.balign 4
_020753B0: .word 0x00000B2E

	thumb_func_start FUN_020753B4
FUN_020753B4: ; 0x020753B4
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	add r0, r4, #0x0
	bl FUN_02073DB4
	ldr r0, _020754A8 ; =0x00000B25
	ldrb r1, [r4, r0]
	mov r0, #0x2c
	mul r0, r1
	add r1, r4, r0
	ldr r0, _020754AC ; =0x00000708
	ldrh r0, [r1, r0]
	mov r1, #0x5
	bl _s32_div_f
	ldr r1, _020754B0 ; =0x00000B28
	strh r0, [r4, r1]
	sub r0, r1, #0x3
	ldrb r2, [r4, r0]
	mov r0, #0x2c
	mul r0, r2
	add r2, r4, r0
	ldr r0, _020754B4 ; =0x00000706
	ldrh r2, [r2, r0]
	ldrh r0, [r4, r1]
	cmp r2, r0
	bhi _0207540E
	add r0, r4, #0x0
	mov r1, #0x8a
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _020754B8 ; =0x00000B22
	mov r1, #0x3
	strb r1, [r4, r0]
	add sp, #0x4
	mov r0, #0x14
	pop {r3-r4, pc}
_0207540E:
	sub r0, r1, #0x5
	ldrb r2, [r4, r0]
	mov r0, #0x40
	orr r2, r0
	sub r0, r1, #0x5
	strb r2, [r4, r0]
	ldrb r0, [r4, r0]
	mov r2, #0x3f
	bic r0, r2
	sub r2, r1, #0x3
	ldrb r3, [r4, r2]
	mov r2, #0x3f
	and r2, r3
	orr r2, r0
	sub r0, r1, #0x5
	strb r2, [r4, r0]
	ldr r0, _020754BC ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C664
	ldr r0, _020754BC ; =0x000005C8
	add r1, sp, #0x0
	ldr r0, [r4, r0]
	add r1, #0x2
	add r2, sp, #0x0
	bl FUN_0200C75C
	ldr r0, _020754C0 ; =0x000005CC
	add r3, sp, #0x0
	mov r1, #0x2
	mov r2, #0x0
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldr r0, [r4, r0]
	bl FUN_0200C6E4
	ldr r0, _020754C4 ; =0x000005A4
	ldr r1, _020754C8 ; =0x00000B23
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1a
	bl FUN_020714BC
	add r1, r0, #0x0
	ldr r0, _020754C0 ; =0x000005CC
	add r1, r1, #0x2
	ldr r0, [r4, r0]
	bl FUN_02020130
	ldr r0, _020754C0 ; =0x000005CC
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	ldr r1, _020754C8 ; =0x00000B23
	add r0, r4, #0x0
	ldrb r1, [r4, r1]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1a
	bl FUN_020709FC
	add r0, r4, #0x0
	mov r1, #0x24
	mov r2, #0x1
	bl FUN_020731C0
	ldr r0, _020754CC ; =0x00000B2A
	mov r1, #0x0
	strh r1, [r4, r0]
	mov r0, #0x1a
	add sp, #0x4
	pop {r3-r4, pc}
	nop
_020754A8: .word 0x00000B25
_020754AC: .word 0x00000708
_020754B0: .word 0x00000B28
_020754B4: .word 0x00000706
_020754B8: .word 0x00000B22
_020754BC: .word 0x000005C8
_020754C0: .word 0x000005CC
_020754C4: .word 0x000005A4
_020754C8: .word 0x00000B23
_020754CC: .word 0x00000B2A

	thumb_func_start FUN_020754D0
FUN_020754D0: ; 0x020754D0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02075504 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r1, r0
	beq _02075500
	mov r0, #0x89
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	add r0, r4, #0x0
	mov r1, #0x1d
	mov r2, #0x1
	bl FUN_020731C0
	ldr r0, _02075508 ; =0x000005C8
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C664
	mov r0, #0x1
_02075500:
	pop {r4, pc}
	nop
_02075504: .word gMain
_02075508: .word 0x000005C8
