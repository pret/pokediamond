	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD09_02211E60
MOD09_02211E60: ; 0x02211E60
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldrb r0, [r5, #0x11]
	cmp r0, #5
	bls _02211E6E
	mov r0, #0
	strb r0, [r5, #0x11]
_02211E6E:
	ldr r0, _02211ED8 ; =MOD09_02211EEC
	ldr r1, _02211EDC ; =0x00002090
	ldr r3, [r5, #0xc]
	mov r2, #0
	bl FUN_020061E8
	bl FUN_0201B6C8
	ldr r2, _02211EDC ; =0x00002090
	add r4, r0, #0
	mov r1, #0
	bl memset
	str r5, [r4]
	ldr r0, [r5, #8]
	bl MOD11_0222FF68
	mov r1, #0x79
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r5, #8]
	bl MOD11_022300CC
	mov r1, #0x7a
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, _02211EE0 ; =0x00002078
	mov r1, #0
	strb r1, [r4, r0]
	ldrb r1, [r5, #0x11]
	sub r0, r0, #2
	strb r1, [r4, r0]
	ldr r0, [r5, #8]
	bl MOD11_02231238
	ldr r3, _02211EE4 ; =0x00002077
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1c
	ldrb r1, [r4, r3]
	mov r2, #0xf0
	lsr r0, r0, #0x18
	bic r1, r2
	orr r0, r1
	strb r0, [r4, r3]
	ldr r0, [r5, #8]
	ldr r1, [r5, #0x28]
	bl MOD11_02230260
	ldr r1, _02211EE8 ; =0x0000208F
	strb r0, [r4, r1]
	pop {r3, r4, r5, pc}
	nop
_02211ED8: .word MOD09_02211EEC
_02211EDC: .word 0x00002090
_02211EE0: .word 0x00002078
_02211EE4: .word 0x00002077
_02211EE8: .word 0x0000208F

	thumb_func_start MOD09_02211EEC
MOD09_02211EEC: ; 0x02211EEC
	push {r4, lr}
	ldr r2, _02212094 ; =0x00002078
	add r4, r1, #0
	ldrb r2, [r4, r2]
	cmp r2, #0x1a
	bls _02211EFA
	b _0221207C
_02211EFA:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02211F06: ; jump table
	.short _02211F3C - _02211F06 - 2 ; case 0
	.short _02211F48 - _02211F06 - 2 ; case 1
	.short _02211F54 - _02211F06 - 2 ; case 2
	.short _02211F60 - _02211F06 - 2 ; case 3
	.short _02211F6C - _02211F06 - 2 ; case 4
	.short _02211F78 - _02211F06 - 2 ; case 5
	.short _02211F84 - _02211F06 - 2 ; case 6
	.short _02211F90 - _02211F06 - 2 ; case 7
	.short _02211F9C - _02211F06 - 2 ; case 8
	.short _02211FA8 - _02211F06 - 2 ; case 9
	.short _02211FB4 - _02211F06 - 2 ; case 10
	.short _02211FC0 - _02211F06 - 2 ; case 11
	.short _02211FCC - _02211F06 - 2 ; case 12
	.short _02211FD8 - _02211F06 - 2 ; case 13
	.short _02211FE4 - _02211F06 - 2 ; case 14
	.short _02211FF0 - _02211F06 - 2 ; case 15
	.short _02211FFC - _02211F06 - 2 ; case 16
	.short _02212008 - _02211F06 - 2 ; case 17
	.short _02212014 - _02211F06 - 2 ; case 18
	.short _02212020 - _02211F06 - 2 ; case 19
	.short _0221202C - _02211F06 - 2 ; case 20
	.short _02212038 - _02211F06 - 2 ; case 21
	.short _02212044 - _02211F06 - 2 ; case 22
	.short _02212050 - _02211F06 - 2 ; case 23
	.short _0221205C - _02211F06 - 2 ; case 24
	.short _02212068 - _02211F06 - 2 ; case 25
	.short _02212074 - _02211F06 - 2 ; case 26
_02211F3C:
	add r0, r4, #0
	bl MOD09_0221209C
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211F48:
	add r0, r4, #0
	bl MOD09_022121A0
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211F54:
	add r0, r4, #0
	bl MOD09_0221236C
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211F60:
	add r0, r4, #0
	bl MOD09_0221241C
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211F6C:
	add r0, r4, #0
	bl MOD09_022124DC
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211F78:
	add r0, r4, #0
	bl MOD09_022125E0
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211F84:
	add r0, r4, #0
	bl MOD09_0221296C
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211F90:
	add r0, r4, #0
	bl MOD09_02212978
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211F9C:
	add r0, r4, #0
	bl MOD09_02212984
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211FA8:
	add r0, r4, #0
	bl MOD09_02212990
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211FB4:
	add r0, r4, #0
	bl MOD09_0221299C
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211FC0:
	add r0, r4, #0
	bl MOD09_022129A8
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211FCC:
	add r0, r4, #0
	bl MOD09_022129CC
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211FD8:
	add r0, r4, #0
	bl MOD09_022129F8
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211FE4:
	add r0, r4, #0
	bl MOD09_02212A1C
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211FF0:
	add r0, r4, #0
	bl MOD09_02212A5C
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02211FFC:
	add r0, r4, #0
	bl MOD09_02212A74
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02212008:
	add r0, r4, #0
	bl MOD09_02212A88
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02212014:
	add r0, r4, #0
	bl MOD09_02212AA4
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02212020:
	add r0, r4, #0
	bl MOD09_02212658
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_0221202C:
	add r0, r4, #0
	bl MOD09_0221274C
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02212038:
	add r0, r4, #0
	bl MOD09_02212868
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02212044:
	add r0, r4, #0
	bl MOD09_02212ACC
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02212050:
	add r0, r4, #0
	bl MOD09_02212AE4
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_0221205C:
	add r0, r4, #0
	bl MOD09_02212C8C
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02212068:
	add r0, r4, #0
	bl MOD09_02212DB8
	ldr r1, _02212094 ; =0x00002078
	strb r0, [r4, r1]
	b _0221207C
_02212074:
	bl MOD09_02212DE4
	cmp r0, #1
	beq _02212090
_0221207C:
	add r0, r4, #0
	bl MOD09_02217580
	ldr r0, _02212098 ; =0x00001FB4
	ldr r0, [r4, r0]
	bl FUN_0200BC1C
	add r0, r4, #0
	bl MOD09_02218218
_02212090:
	pop {r4, pc}
	nop
_02212094: .word 0x00002078
_02212098: .word 0x00001FB4

	thumb_func_start MOD09_0221209C
MOD09_0221209C: ; 0x0221209C
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _02212190 ; =0x04001050
	mov r1, #0
	strh r1, [r0]
	ldr r0, [r5]
	add r0, #0x35
	ldrb r0, [r0]
	cmp r0, #3
	ldr r0, _02212194 ; =0x0000207A
	bne _022120BC
	mov r1, #6
	strb r1, [r5, r0]
	mov r4, #0x13
	b _022120C0
_022120BC:
	strb r1, [r5, r0]
	mov r4, #1
_022120C0:
	ldr r0, [r5]
	ldr r0, [r0, #0xc]
	bl MOD09_0221AC04
	ldr r1, _02212198 ; =0x00002088
	str r0, [r5, r1]
	add r0, r5, #0
	bl MOD09_022131C8
	add r0, r5, #0
	bl MOD09_02212E4C
	add r0, r5, #0
	bl MOD09_02212F8C
	add r0, r5, #0
	bl MOD09_02213138
	ldr r1, [r5]
	mov r0, #2
	ldr r1, [r1, #0xc]
	bl FUN_02002C50
	ldr r1, _02212194 ; =0x0000207A
	add r0, r5, #0
	ldrb r1, [r5, r1]
	bl MOD09_02213968
	ldr r1, _02212194 ; =0x0000207A
	add r0, r5, #0
	ldrb r1, [r5, r1]
	bl MOD09_022182E8
	ldr r1, _02212194 ; =0x0000207A
	add r0, r5, #0
	ldrb r1, [r5, r1]
	bl MOD09_02218640
	add r0, r5, #0
	bl MOD09_02216734
	ldr r1, _02212194 ; =0x0000207A
	add r0, r5, #0
	ldrb r1, [r5, r1]
	bl MOD09_02216D80
	add r0, r5, #0
	bl MOD09_02213CB8
	ldr r1, _02212194 ; =0x0000207A
	add r0, r5, #0
	ldrb r1, [r5, r1]
	bl MOD09_02213E28
	ldr r0, [r5]
	add r0, #0x32
	ldrb r0, [r0]
	cmp r0, #0
	beq _02212140
	ldr r0, _02212198 ; =0x00002088
	mov r1, #1
	ldr r0, [r5, r0]
	bl MOD09_0221AC2C
_02212140:
	ldr r0, _02212194 ; =0x0000207A
	ldrb r0, [r5, r0]
	cmp r0, #0
	bne _0221215A
	add r0, r5, #0
	mov r1, #0
	bl MOD09_02213BDC
	cmp r0, #1
	bne _0221215A
	ldr r0, [r5]
	mov r1, #1
	strb r1, [r0, #0x11]
_0221215A:
	ldr r1, _02212194 ; =0x0000207A
	add r0, r5, #0
	ldrb r1, [r5, r1]
	bl MOD09_02217838
	ldr r1, _02212194 ; =0x0000207A
	add r0, r5, #0
	ldrb r1, [r5, r1]
	bl MOD09_02213710
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x7a
	lsl r0, r0, #2
	mov r1, #0xa
	add r3, r1, #0
	ldr r0, [r5, r0]
	ldr r2, _0221219C ; =0x0000FFFF
	sub r3, #0x12
	bl FUN_02003210
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02212190: .word 0x04001050
_02212194: .word 0x0000207A
_02212198: .word 0x00002088
_0221219C: .word 0x0000FFFF

	thumb_func_start MOD09_022121A0
MOD09_022121A0: ; 0x022121A0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_020038E4
	cmp r0, #0
	beq _022121B6
	mov r0, #1
	pop {r4, pc}
_022121B6:
	add r0, r4, #0
	bl MOD09_0221347C
	cmp r0, #1
	bne _0221220E
	ldr r1, [r4]
	ldrb r0, [r1, #0x11]
	cmp r0, #6
	bne _022121E2
	add r1, #0x35
	ldrb r0, [r1]
	cmp r0, #1
	beq _0221220E
	ldr r0, _02212214 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #6
	bl MOD09_022181C8
	mov r0, #0x19
	pop {r4, pc}
_022121E2:
	ldr r0, _02212214 ; =0x000005DD
	bl PlaySE
	ldr r1, [r4]
	add r0, r4, #0
	ldrb r1, [r1, #0x11]
	bl MOD09_022181C8
	ldr r0, [r4]
	add r0, #0x35
	ldrb r0, [r0]
	cmp r0, #2
	bne _02212204
	add r0, r4, #0
	bl MOD09_0221221C
	pop {r4, pc}
_02212204:
	ldr r0, _02212218 ; =0x00002079
	mov r1, #7
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r4, pc}
_0221220E:
	mov r0, #1
	pop {r4, pc}
	nop
_02212214: .word 0x000005DD
_02212218: .word 0x00002079

	thumb_func_start MOD09_0221221C
MOD09_0221221C: ; 0x0221221C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r4, [r5]
	ldrb r1, [r4, #0x11]
	cmp r1, #0
	bne _0221222E
	ldr r0, [r4, #0x18]
	cmp r0, #0
	bne _02212238
_0221222E:
	cmp r1, #1
	bne _02212254
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _02212254
_02212238:
	add r0, r5, #0
	bl MOD09_022166D0
	add r0, r5, #0
	bl MOD09_02216314
	ldr r0, [r5]
	mov r1, #6
	strb r1, [r0, #0x11]
	ldr r0, _02212360 ; =0x00002079
	mov r1, #0x19
	strb r1, [r5, r0]
	mov r0, #0x11
	pop {r3, r4, r5, pc}
_02212254:
	ldrh r0, [r4, #0x22]
	ldr r2, [r4, #0xc]
	mov r1, #0x24
	bl GetItemAttr
	cmp r0, #0
	beq _0221228A
	ldrh r0, [r4, #0x22]
	ldr r2, [r4, #0xc]
	mov r1, #0x25
	bl GetItemAttr
	cmp r0, #0
	bne _0221228A
	ldrb r1, [r4, #0x11]
	mov r0, #0x50
	mul r0, r1
	add r0, r5, r0
	ldrb r0, [r0, #0x1b]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bne _0221228A
	ldr r0, _02212360 ; =0x00002079
	mov r1, #0xd
	strb r1, [r5, r0]
	mov r0, #0x16
	pop {r3, r4, r5, pc}
_0221228A:
	ldrh r0, [r4, #0x22]
	mov r3, #0
	str r0, [sp]
	ldrb r2, [r4, #0x11]
	ldr r0, [r4, #8]
	ldr r1, [r4, #0x28]
	add r2, r4, r2
	add r2, #0x2c
	ldrb r2, [r2]
	bl MOD11_02230370
	cmp r0, #1
	bne _0221233A
	ldrh r0, [r4, #0x22]
	ldr r2, [r4, #0xc]
	mov r1, #0x25
	bl GetItemAttr
	cmp r0, #0
	beq _022122BA
	ldr r0, _02212360 ; =0x00002079
	mov r1, #0xd
	strb r1, [r5, r0]
	b _02212330
_022122BA:
	ldrb r1, [r4, #0x11]
	add r0, r5, #0
	bl MOD09_02213620
	cmp r0, #1
	bne _0221232A
	ldrh r0, [r4, #0x22]
	ldr r2, [r4, #0xc]
	mov r1, #0x17
	bl GetItemAttr
	cmp r0, #0
	bne _0221232A
	add r2, r4, #0
	add r2, #0x33
	ldrh r1, [r4, #0x22]
	ldrb r2, [r2]
	ldr r0, [r4, #8]
	ldr r3, [r4, #0xc]
	bl MOD09_02213C84
	ldrb r2, [r4, #0x11]
	ldr r0, [r4, #8]
	ldr r1, [r4, #0x28]
	add r2, r4, r2
	add r2, #0x2c
	ldrb r2, [r2]
	bl MOD11_02230014
	ldrb r2, [r4, #0x11]
	mov r1, #0x50
	add r3, r2, #0
	mul r3, r1
	add r2, r5, r3
	str r0, [r2, #4]
	ldrb r0, [r4, #0x11]
	mov r2, #0
	mul r1, r0
	add r0, r5, r1
	ldr r0, [r0, #4]
	mov r1, #0xa2
	bl GetMonData
	strh r0, [r4, #0x20]
	ldrb r1, [r4, #0x11]
	mov r0, #0x50
	ldrh r2, [r4, #0x20]
	mul r0, r1
	add r0, r5, r0
	ldrh r0, [r0, #0x14]
	mov r1, #0x19
	sub r0, r2, r0
	strh r0, [r4, #0x20]
	ldr r0, _02212360 ; =0x00002079
	strb r1, [r5, r0]
	b _02212330
_0221232A:
	ldr r0, _02212360 ; =0x00002079
	mov r1, #0x17
	strb r1, [r5, r0]
_02212330:
	ldr r0, _02212364 ; =0x0000207C
	mov r1, #0
	strb r1, [r5, r0]
	mov r0, #0x16
	pop {r3, r4, r5, pc}
_0221233A:
	ldr r2, _02212368 ; =0x00001FA8
	mov r1, #0x51
	ldr r0, [r5, r2]
	add r2, #8
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	add r0, r5, #0
	bl MOD09_02216314
	ldr r0, [r5]
	mov r1, #6
	strb r1, [r0, #0x11]
	ldr r0, _02212360 ; =0x00002079
	mov r1, #0x19
	strb r1, [r5, r0]
	mov r0, #0x11
	pop {r3, r4, r5, pc}
	nop
_02212360: .word 0x00002079
_02212364: .word 0x0000207C
_02212368: .word 0x00001FA8

	thumb_func_start MOD09_0221236C
MOD09_0221236C: ; 0x0221236C
	push {r4, lr}
	add r4, r0, #0
	bl MOD09_022134F4
	cmp r0, #3
	bhi _0221240E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02212384: ; jump table
	.short _0221238C - _02212384 - 2 ; case 0
	.short _022123B2 - _02212384 - 2 ; case 1
	.short _022123D4 - _02212384 - 2 ; case 2
	.short _022123F6 - _02212384 - 2 ; case 3
_0221238C:
	ldr r0, _02212414 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #7
	bl MOD09_022181C8
	add r0, r4, #0
	bl MOD09_022139D4
	cmp r0, #1
	bne _022123A8
	mov r0, #0x19
	pop {r4, pc}
_022123A8:
	ldr r0, _02212418 ; =0x00002079
	mov r1, #0xf
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r4, pc}
_022123B2:
	add r0, r4, #0
	bl MOD09_02213B7C
	cmp r0, #1
	beq _0221240E
	ldr r0, _02212414 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #8
	bl MOD09_022181C8
	ldr r0, _02212418 ; =0x00002079
	mov r1, #8
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r4, pc}
_022123D4:
	add r0, r4, #0
	bl MOD09_02213B7C
	cmp r0, #1
	beq _0221240E
	ldr r0, _02212414 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #0xa
	bl MOD09_022181C8
	ldr r0, _02212418 ; =0x00002079
	mov r1, #9
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r4, pc}
_022123F6:
	ldr r0, _02212414 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #6
	bl MOD09_022181C8
	ldr r0, _02212418 ; =0x00002079
	mov r1, #6
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r4, pc}
_0221240E:
	mov r0, #2
	pop {r4, pc}
	nop
_02212414: .word 0x000005DD
_02212418: .word 0x00002079

	thumb_func_start MOD09_0221241C
MOD09_0221241C: ; 0x0221241C
	push {r4, lr}
	add r4, r0, #0
	bl MOD09_0221353C
	cmp r0, #3
	bhi _022124CC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02212434: ; jump table
	.short _0221243C - _02212434 - 2 ; case 0
	.short _0221246A - _02212434 - 2 ; case 1
	.short _02212496 - _02212434 - 2 ; case 2
	.short _022124AE - _02212434 - 2 ; case 3
_0221243C:
	ldr r1, [r4]
	mov r2, #0
	ldrb r1, [r1, #0x11]
	add r0, r4, #0
	mvn r2, r2
	bl MOD09_02213658
	cmp r0, #0xff
	beq _022124CC
	ldr r1, [r4]
	strb r0, [r1, #0x11]
	ldr r0, _022124D0 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #0xc
	bl MOD09_022181C8
	ldr r0, _022124D4 ; =0x00002079
	mov r1, #0xe
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r4, pc}
_0221246A:
	ldr r1, [r4]
	add r0, r4, #0
	ldrb r1, [r1, #0x11]
	mov r2, #1
	bl MOD09_02213658
	cmp r0, #0xff
	beq _022124CC
	ldr r1, [r4]
	strb r0, [r1, #0x11]
	ldr r0, _022124D0 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #0xd
	bl MOD09_022181C8
	ldr r0, _022124D4 ; =0x00002079
	mov r1, #0xe
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r4, pc}
_02212496:
	ldr r0, _022124D0 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #0xb
	bl MOD09_022181C8
	ldr r0, _022124D4 ; =0x00002079
	mov r1, #9
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r4, pc}
_022124AE:
	ldr r0, _022124D0 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #6
	bl MOD09_022181C8
	ldr r0, _022124D8 ; =0x0000208C
	mov r1, #1
	strb r1, [r4, r0]
	mov r1, #7
	sub r0, #0x13
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r4, pc}
_022124CC:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_022124D0: .word 0x000005DD
_022124D4: .word 0x00002079
_022124D8: .word 0x0000208C

	thumb_func_start MOD09_022124DC
MOD09_022124DC: ; 0x022124DC
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl MOD09_02213584
	add r5, r0, #0
	cmp r5, #7
	bhi _022125CE
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022124F6: ; jump table
	.short _02212506 - _022124F6 - 2 ; case 0
	.short _02212506 - _022124F6 - 2 ; case 1
	.short _02212506 - _022124F6 - 2 ; case 2
	.short _02212506 - _022124F6 - 2 ; case 3
	.short _0221253E - _022124F6 - 2 ; case 4
	.short _0221256C - _022124F6 - 2 ; case 5
	.short _02212598 - _022124F6 - 2 ; case 6
	.short _022125B0 - _022124F6 - 2 ; case 7
_02212506:
	ldr r0, [r4]
	ldrb r1, [r0, #0x11]
	mov r0, #0x50
	mul r0, r1
	add r1, r4, r0
	lsl r0, r5, #3
	add r0, r1, r0
	ldrh r0, [r0, #0x34]
	cmp r0, #0
	beq _022125CE
	ldr r0, _022125D4 ; =0x000005DD
	bl PlaySE
	add r1, r5, #0
	add r1, #0xe
	lsl r1, r1, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	bl MOD09_022181C8
	ldr r0, [r4]
	mov r1, #0xa
	add r0, #0x34
	strb r5, [r0]
	ldr r0, _022125D8 ; =0x00002079
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r3, r4, r5, pc}
_0221253E:
	ldr r1, [r4]
	mov r2, #0
	ldrb r1, [r1, #0x11]
	add r0, r4, #0
	mvn r2, r2
	bl MOD09_02213658
	cmp r0, #0xff
	beq _022125CE
	ldr r1, [r4]
	strb r0, [r1, #0x11]
	ldr r0, _022125D4 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #0xc
	bl MOD09_022181C8
	ldr r0, _022125D8 ; =0x00002079
	mov r1, #0xe
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r3, r4, r5, pc}
_0221256C:
	ldr r1, [r4]
	add r0, r4, #0
	ldrb r1, [r1, #0x11]
	mov r2, #1
	bl MOD09_02213658
	cmp r0, #0xff
	beq _022125CE
	ldr r1, [r4]
	strb r0, [r1, #0x11]
	ldr r0, _022125D4 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #0xd
	bl MOD09_022181C8
	ldr r0, _022125D8 ; =0x00002079
	mov r1, #0xe
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r3, r4, r5, pc}
_02212598:
	ldr r0, _022125D4 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #9
	bl MOD09_022181C8
	ldr r0, _022125D8 ; =0x00002079
	mov r1, #8
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r3, r4, r5, pc}
_022125B0:
	ldr r0, _022125D4 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #6
	bl MOD09_022181C8
	ldr r0, _022125DC ; =0x0000208C
	mov r1, #2
	strb r1, [r4, r0]
	mov r1, #7
	sub r0, #0x13
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r3, r4, r5, pc}
_022125CE:
	mov r0, #4
	pop {r3, r4, r5, pc}
	nop
_022125D4: .word 0x000005DD
_022125D8: .word 0x00002079
_022125DC: .word 0x0000208C

	thumb_func_start MOD09_022125E0
MOD09_022125E0: ; 0x022125E0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl MOD09_022135CC
	add r5, r0, #0
	cmp r5, #4
	bhi _0221264A
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022125FA: ; jump table
	.short _02212604 - _022125FA - 2 ; case 0
	.short _02212604 - _022125FA - 2 ; case 1
	.short _02212604 - _022125FA - 2 ; case 2
	.short _02212604 - _022125FA - 2 ; case 3
	.short _02212632 - _022125FA - 2 ; case 4
_02212604:
	ldr r1, [r4]
	add r0, r1, #0
	add r0, #0x34
	ldrb r0, [r0]
	cmp r0, r5
	beq _02212622
	ldrb r1, [r1, #0x11]
	mov r0, #0x50
	mul r0, r1
	add r1, r4, r0
	lsl r0, r5, #3
	add r0, r1, r0
	ldrh r0, [r0, #0x34]
	cmp r0, #0
	beq _0221264A
_02212622:
	ldr r0, _02212650 ; =0x000005DD
	bl PlaySE
	ldr r0, [r4]
	add r0, #0x34
	strb r5, [r0]
	mov r0, #0xa
	pop {r3, r4, r5, pc}
_02212632:
	ldr r0, _02212650 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #6
	bl MOD09_022181C8
	ldr r0, _02212654 ; =0x00002079
	mov r1, #9
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r3, r4, r5, pc}
_0221264A:
	mov r0, #5
	pop {r3, r4, r5, pc}
	nop
_02212650: .word 0x000005DD
_02212654: .word 0x00002079

	thumb_func_start MOD09_02212658
MOD09_02212658: ; 0x02212658
	push {r3, r4, r5, lr}
	ldr r1, _02212734 ; =0x0221AFD8
	add r4, r0, #0
	bl MOD09_02213614
	add r5, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	bne _02212682
	ldr r0, _02212738 ; =0x00002088
	ldr r0, [r4, r0]
	bl MOD09_0221AD30
	add r5, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	bne _02212688
	mov r5, #6
	b _02212688
_02212682:
	add r0, r4, #0
	bl MOD09_022178E4
_02212688:
	cmp r5, #6
	bhi _02212730
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02212698: ; jump table
	.short _022126A6 - _02212698 - 2 ; case 0
	.short _022126A6 - _02212698 - 2 ; case 1
	.short _022126A6 - _02212698 - 2 ; case 2
	.short _022126A6 - _02212698 - 2 ; case 3
	.short _022126A6 - _02212698 - 2 ; case 4
	.short _022126D0 - _02212698 - 2 ; case 5
	.short _02212710 - _02212698 - 2 ; case 6
_022126A6:
	lsl r0, r5, #0x18
	lsr r1, r0, #0x18
	ldr r0, [r4]
	add r0, #0x34
	strb r1, [r0]
	ldr r0, _0221273C ; =0x0000208D
	strb r1, [r4, r0]
	ldr r0, _02212740 ; =0x000005DD
	bl PlaySE
	add r5, #0x17
	lsl r1, r5, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	bl MOD09_022181C8
	ldr r0, _02212744 ; =0x00002079
	mov r1, #0xc
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r3, r4, r5, pc}
_022126D0:
	ldr r0, _02212748 ; =0x00002077
	ldrb r3, [r4, r0]
	lsl r1, r3, #0x18
	lsr r1, r1, #0x1c
	beq _02212730
	mov r2, #0xf
	add r1, r3, #0
	bic r1, r2
	lsl r2, r3, #0x1c
	lsr r3, r2, #0x1c
	mov r2, #1
	eor r2, r3
	lsl r2, r2, #0x18
	lsr r3, r2, #0x18
	mov r2, #0xf
	and r2, r3
	orr r1, r2
	strb r1, [r4, r0]
	add r0, #0x16
	strb r5, [r4, r0]
	ldr r0, _02212740 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #0x12
	bl MOD09_022181C8
	ldr r0, _02212744 ; =0x00002079
	mov r1, #0xb
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r3, r4, r5, pc}
_02212710:
	ldr r0, [r4]
	mov r1, #4
	add r0, #0x34
	strb r1, [r0]
	ldr r0, _02212740 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #6
	bl MOD09_022181C8
	ldr r0, _02212744 ; =0x00002079
	mov r1, #0x19
	strb r1, [r4, r0]
	mov r0, #0x16
	pop {r3, r4, r5, pc}
_02212730:
	mov r0, #0x13
	pop {r3, r4, r5, pc}
	.align 2, 0
_02212734: .word MOD9_0221AFD8
_02212738: .word 0x00002088
_0221273C: .word 0x0000208D
_02212740: .word 0x000005DD
_02212744: .word 0x00002079
_02212748: .word 0x00002077

	thumb_func_start MOD09_0221274C
MOD09_0221274C: ; 0x0221274C
	push {r3, r4, r5, lr}
	ldr r1, _02212850 ; =0x0221AEE0
	add r5, r0, #0
	bl MOD09_02213614
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _02212776
	ldr r0, _02212854 ; =0x00002088
	ldr r0, [r5, r0]
	bl MOD09_0221AD30
	add r4, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _0221277C
	mov r4, #2
	b _0221277C
_02212776:
	add r0, r5, #0
	bl MOD09_022178E4
_0221277C:
	cmp r4, #0
	beq _0221278A
	cmp r4, #1
	beq _022127E6
	cmp r4, #2
	beq _0221282C
	b _0221284A
_0221278A:
	ldr r0, _02212858 ; =0x000005DD
	bl PlaySE
	ldr r0, _0221285C ; =0x00002077
	ldrb r0, [r5, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	bne _022127A4
	add r0, r5, #0
	mov r1, #0x1c
	bl MOD09_022181C8
	b _022127AC
_022127A4:
	add r0, r5, #0
	mov r1, #0x1d
	bl MOD09_022181C8
_022127AC:
	add r0, r5, #0
	bl MOD09_02213C0C
	cmp r0, #1
	bne _022127DC
	add r0, r5, #0
	bl MOD09_0221534C
	ldr r0, _0221285C ; =0x00002077
	ldrb r0, [r5, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	bne _022127CE
	add r0, r5, #0
	bl MOD09_02213C34
	b _022127D4
_022127CE:
	add r0, r5, #0
	bl MOD09_02213C6C
_022127D4:
	ldr r0, _02212860 ; =0x00002079
	mov r1, #0x14
	strb r1, [r5, r0]
	b _022127E2
_022127DC:
	ldr r0, _02212860 ; =0x00002079
	mov r1, #0x19
	strb r1, [r5, r0]
_022127E2:
	mov r0, #0x16
	pop {r3, r4, r5, pc}
_022127E6:
	ldr r0, _0221285C ; =0x00002077
	ldrb r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	beq _0221284A
	ldr r0, _02212858 ; =0x000005DD
	bl PlaySE
	add r0, r5, #0
	mov r1, #0x12
	bl MOD09_022181C8
	ldr r2, _0221285C ; =0x00002077
	mov r1, #0xf
	ldrb r3, [r5, r2]
	add r0, r3, #0
	bic r0, r1
	lsl r1, r3, #0x1c
	lsr r3, r1, #0x1c
	mov r1, #1
	eor r1, r3
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	mov r1, #0xf
	and r1, r3
	orr r0, r1
	strb r0, [r5, r2]
	add r0, r2, #0
	add r0, #0x17
	strb r4, [r5, r0]
	mov r1, #0xc
	add r0, r2, #2
	strb r1, [r5, r0]
	mov r0, #0x16
	pop {r3, r4, r5, pc}
_0221282C:
	ldr r0, _02212858 ; =0x000005DD
	bl PlaySE
	add r0, r5, #0
	mov r1, #6
	bl MOD09_022181C8
	ldr r0, _02212864 ; =0x0000208E
	mov r1, #0
	strb r1, [r5, r0]
	mov r1, #0xb
	sub r0, #0x15
	strb r1, [r5, r0]
	mov r0, #0x16
	pop {r3, r4, r5, pc}
_0221284A:
	mov r0, #0x14
	pop {r3, r4, r5, pc}
	nop
_02212850: .word MOD9_0221AEE0
_02212854: .word 0x00002088
_02212858: .word 0x000005DD
_0221285C: .word 0x00002077
_02212860: .word 0x00002079
_02212864: .word 0x0000208E

	thumb_func_start MOD09_02212868
MOD09_02212868: ; 0x02212868
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	ldr r1, _02212954 ; =0x0221AF30
	add r4, r0, #0
	ldr r6, [r4]
	bl MOD09_02213614
	add r5, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	bne _02212896
	ldr r0, _02212958 ; =0x00002088
	ldr r0, [r4, r0]
	bl MOD09_0221AD30
	add r5, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	bne _0221289C
	mov r5, #4
	b _0221289C
_02212896:
	add r0, r4, #0
	bl MOD09_022178E4
_0221289C:
	cmp r5, #4
	bhi _0221294E
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022128AC: ; jump table
	.short _022128B6 - _022128AC - 2 ; case 0
	.short _022128B6 - _022128AC - 2 ; case 1
	.short _022128B6 - _022128AC - 2 ; case 2
	.short _022128B6 - _022128AC - 2 ; case 3
	.short _02212934 - _022128AC - 2 ; case 4
_022128B6:
	ldrb r1, [r6, #0x11]
	mov r0, #0x50
	mul r0, r1
	add r1, r4, r0
	lsl r0, r5, #3
	add r0, r1, r0
	ldrh r0, [r0, #0x34]
	cmp r0, #0
	beq _0221294E
	ldr r0, [r4]
	add r0, #0x34
	strb r5, [r0]
	ldr r0, _0221295C ; =0x000005DD
	bl PlaySE
	add r1, r5, #0
	add r1, #0x13
	lsl r1, r1, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	bl MOD09_022181C8
	ldrh r0, [r6, #0x22]
	add r3, r5, #0
	str r0, [sp]
	ldrb r2, [r6, #0x11]
	ldr r0, [r6, #8]
	ldr r1, [r6, #0x28]
	add r2, r6, r2
	add r2, #0x2c
	ldrb r2, [r2]
	bl MOD11_02230370
	cmp r0, #1
	bne _0221290E
	ldr r0, _02212960 ; =0x0000207C
	mov r1, #0
	strb r1, [r4, r0]
	mov r1, #0x17
	sub r0, r0, #3
	strb r1, [r4, r0]
	add sp, #4
	mov r0, #0x16
	pop {r3, r4, r5, r6, pc}
_0221290E:
	ldr r2, _02212964 ; =0x00001FA8
	mov r1, #0x51
	ldr r0, [r4, r2]
	add r2, #8
	ldr r2, [r4, r2]
	bl ReadMsgDataIntoString
	add r0, r4, #0
	bl MOD09_02216314
	ldr r0, [r4]
	mov r1, #6
	strb r1, [r0, #0x11]
	ldr r0, _02212968 ; =0x00002079
	mov r1, #0x19
	strb r1, [r4, r0]
	add sp, #4
	mov r0, #0x11
	pop {r3, r4, r5, r6, pc}
_02212934:
	ldr r0, _0221295C ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	mov r1, #6
	bl MOD09_022181C8
	ldr r0, _02212968 ; =0x00002079
	mov r1, #6
	strb r1, [r4, r0]
	add sp, #4
	mov r0, #0x16
	pop {r3, r4, r5, r6, pc}
_0221294E:
	mov r0, #0x15
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02212954: .word MOD9_0221AF30
_02212958: .word 0x00002088
_0221295C: .word 0x000005DD
_02212960: .word 0x0000207C
_02212964: .word 0x00001FA8
_02212968: .word 0x00002079

	thumb_func_start MOD09_0221296C
MOD09_0221296C: ; 0x0221296C
	push {r3, lr}
	mov r1, #0
	bl MOD09_022138F0
	mov r0, #1
	pop {r3, pc}

	thumb_func_start MOD09_02212978
MOD09_02212978: ; 0x02212978
	push {r3, lr}
	mov r1, #1
	bl MOD09_022138F0
	mov r0, #2
	pop {r3, pc}

	thumb_func_start MOD09_02212984
MOD09_02212984: ; 0x02212984
	push {r3, lr}
	mov r1, #2
	bl MOD09_022138F0
	mov r0, #3
	pop {r3, pc}

	thumb_func_start MOD09_02212990
MOD09_02212990: ; 0x02212990
	push {r3, lr}
	mov r1, #3
	bl MOD09_022138F0
	mov r0, #4
	pop {r3, pc}

	thumb_func_start MOD09_0221299C
MOD09_0221299C: ; 0x0221299C
	push {r3, lr}
	mov r1, #4
	bl MOD09_022138F0
	mov r0, #5
	pop {r3, pc}

	thumb_func_start MOD09_022129A8
MOD09_022129A8: ; 0x022129A8
	push {r3, lr}
	ldr r1, _022129C8 ; =0x00002077
	ldrb r1, [r0, r1]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	bne _022129BC
	mov r1, #6
	bl MOD09_022138F0
	b _022129C2
_022129BC:
	mov r1, #8
	bl MOD09_022138F0
_022129C2:
	mov r0, #0x13
	pop {r3, pc}
	nop
_022129C8: .word 0x00002077

	thumb_func_start MOD09_022129CC
MOD09_022129CC: ; 0x022129CC
	push {r4, lr}
	add r4, r0, #0
	bl MOD09_022174EC
	ldr r0, _022129F4 ; =0x00002077
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	bne _022129E8
	add r0, r4, #0
	mov r1, #7
	bl MOD09_022138F0
	b _022129F0
_022129E8:
	add r0, r4, #0
	mov r1, #9
	bl MOD09_022138F0
_022129F0:
	mov r0, #0x14
	pop {r4, pc}
	.align 2, 0
_022129F4: .word 0x00002077

	thumb_func_start MOD09_022129F8
MOD09_022129F8: ; 0x022129F8
	push {r4, lr}
	add r4, r0, #0
	mov r1, #5
	bl MOD09_022138F0
	ldr r2, [r4]
	mov r1, #0x25
	ldrh r0, [r2, #0x22]
	ldr r2, [r2, #0xc]
	bl GetItemAttr
	cmp r0, #0
	beq _02212A16
	mov r0, #0x18
	pop {r4, pc}
_02212A16:
	mov r0, #0x15
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD09_02212A1C
MOD09_02212A1C: ; 0x02212A1C
	push {r4, lr}
	ldr r1, _02212A58 ; =0x0000207A
	add r4, r0, #0
	ldrb r1, [r4, r1]
	bl MOD09_02216D80
	ldr r1, _02212A58 ; =0x0000207A
	add r0, r4, #0
	ldrb r1, [r4, r1]
	bl MOD09_02213E28
	ldr r1, _02212A58 ; =0x0000207A
	add r0, r4, #0
	ldrb r1, [r4, r1]
	bl MOD09_022182E8
	ldr r1, _02212A58 ; =0x0000207A
	add r0, r4, #0
	ldrb r1, [r4, r1]
	bl MOD09_02213710
	ldr r0, _02212A58 ; =0x0000207A
	ldrb r0, [r4, r0]
	cmp r0, #2
	bne _02212A52
	mov r0, #3
	pop {r4, pc}
_02212A52:
	mov r0, #4
	pop {r4, pc}
	nop
_02212A58: .word 0x0000207A

	thumb_func_start MOD09_02212A5C
MOD09_02212A5C: ; 0x02212A5C
	push {r4, lr}
	add r4, r0, #0
	bl MOD09_02216314
	ldr r0, _02212A70 ; =0x00002079
	mov r1, #0x10
	strb r1, [r4, r0]
	mov r0, #0x11
	pop {r4, pc}
	nop
_02212A70: .word 0x00002079

	thumb_func_start MOD09_02212A74
MOD09_02212A74: ; 0x02212A74
	push {r3, lr}
	ldr r1, _02212A84 ; =0x00002060
	add r0, r0, r1
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #2
	pop {r3, pc}
	.align 2, 0
_02212A84: .word 0x00002060

	thumb_func_start MOD09_02212A88
MOD09_02212A88: ; 0x02212A88
	push {r3, lr}
	ldr r1, _02212AA0 ; =0x0000207B
	ldrb r0, [r0, r1]
	bl FUN_0201BD70
	cmp r0, #0
	bne _02212A9A
	mov r0, #0x12
	pop {r3, pc}
_02212A9A:
	mov r0, #0x11
	pop {r3, pc}
	nop
_02212AA0: .word 0x0000207B

	thumb_func_start MOD09_02212AA4
MOD09_02212AA4: ; 0x02212AA4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02212AC4 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	bne _02212ABA
	bl FUN_02020AA4
	cmp r0, #1
	bne _02212AC0
_02212ABA:
	ldr r0, _02212AC8 ; =0x00002079
	ldrb r0, [r4, r0]
	pop {r4, pc}
_02212AC0:
	mov r0, #0x12
	pop {r4, pc}
	.align 2, 0
_02212AC4: .word gMain
_02212AC8: .word 0x00002079

	thumb_func_start MOD09_02212ACC
MOD09_02212ACC: ; 0x02212ACC
	ldr r1, _02212AE0 ; =0x00001FA3
	ldrb r2, [r0, r1]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1f
	bne _02212ADC
	add r1, #0xd6
	ldrb r0, [r0, r1]
	bx lr
_02212ADC:
	mov r0, #0x16
	bx lr
	.align 2, 0
_02212AE0: .word 0x00001FA3

	thumb_func_start MOD09_02212AE4
MOD09_02212AE4: ; 0x02212AE4
	push {r3, r4, r5, r6, r7, lr}
	ldr r7, _02212C7C ; =0x0000207C
	add r4, r0, #0
	ldrb r1, [r4, r7]
	ldr r5, [r4]
	cmp r1, #4
	bls _02212AF4
	b _02212C78
_02212AF4:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02212B00: ; jump table
	.short _02212B0A - _02212B00 - 2 ; case 0
	.short _02212BCE - _02212B00 - 2 ; case 1
	.short _02212BF6 - _02212B00 - 2 ; case 2
	.short _02212C2E - _02212B00 - 2 ; case 3
	.short _02212C4E - _02212B00 - 2 ; case 4
_02212B0A:
	ldrb r2, [r5, #0x11]
	ldr r0, [r5, #8]
	ldr r1, [r5, #0x28]
	add r2, r5, r2
	add r2, #0x2c
	ldrb r2, [r2]
	bl MOD11_02230014
	ldrb r2, [r5, #0x11]
	mov r1, #0x50
	mul r1, r2
	add r1, r4, r1
	str r0, [r1, #4]
	add r0, r4, #0
	bl MOD09_02216378
	sub r0, r7, #2
	ldrb r0, [r4, r0]
	ldrb r1, [r5, #0x11]
	cmp r0, #5
	bne _02212B54
	mov r0, #0x50
	mul r0, r1
	add r5, #0x34
	ldrb r1, [r5]
	add r0, r4, r0
	ldr r0, [r0, #4]
	add r1, #0x3a
	mov r2, #0
	bl GetMonData
	add r1, r7, #4
	strh r0, [r4, r1]
	mov r2, #2
	sub r0, r1, #4
	strb r2, [r4, r0]
	b _02212BC6
_02212B54:
	mov r0, #0x50
	mul r0, r1
	add r0, r4, r0
	ldr r0, [r0, #4]
	bl FUN_0207C2D4
	add r6, r0, #0
	ldrb r0, [r5, #0x11]
	add r3, r4, #0
	mov r7, #0x50
	add r2, r0, #0
	add r3, #0x1b
	mul r2, r7
	ldrb r1, [r3, r2]
	mov r0, #0x78
	bic r1, r0
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x19
	orr r0, r1
	strb r0, [r3, r2]
	ldrb r0, [r5, #0x11]
	add r1, r0, #0
	mul r1, r7
	add r1, r4, r1
	ldrb r1, [r1, #0x1b]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x1c
	cmp r1, #7
	bne _02212BAA
	add r0, #0xd
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r0, _02212C80 ; =0x00001FB8
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_0200C644
	ldrb r1, [r5, #0x11]
	add r0, r4, #0
	bl MOD09_022156DC
_02212BAA:
	ldrb r1, [r5, #0x11]
	mov r0, #0x50
	mov r2, #0
	mul r0, r1
	add r0, r4, r0
	ldr r0, [r0, #4]
	mov r1, #0xa2
	bl GetMonData
	ldr r1, _02212C84 ; =0x0000207E
	mov r2, #4
	strh r0, [r4, r1]
	sub r0, r1, #2
	strb r2, [r4, r0]
_02212BC6:
	ldr r0, _02212C88 ; =0x000005EC
	bl PlaySE
	b _02212C78
_02212BCE:
	ldrb r1, [r5, #0x11]
	add r6, r4, #0
	mov r2, #0x50
	add r3, r1, #0
	add r6, #0x14
	mul r3, r2
	add r1, r7, #2
	ldrh r2, [r4, r1]
	ldrh r1, [r6, r3]
	cmp r2, r1
	beq _02212BF0
	add r1, r1, #1
	strh r1, [r6, r3]
	ldrb r1, [r5, #0x11]
	bl MOD09_0221567C
	b _02212C78
_02212BF0:
	mov r0, #3
	strb r0, [r4, r7]
	b _02212C78
_02212BF6:
	ldrb r3, [r5, #0x11]
	add r1, r4, #0
	mov r2, #0x50
	add r1, #0x36
	mul r2, r3
	add r6, r1, r2
	add r1, r5, #0
	add r1, #0x34
	ldrb r1, [r1]
	lsl r3, r1, #3
	add r1, r7, #4
	ldrh r2, [r4, r1]
	ldrb r1, [r6, r3]
	cmp r2, r1
	beq _02212C28
	add r1, r1, #1
	strb r1, [r6, r3]
	add r5, #0x34
	ldrb r2, [r5]
	add r1, r2, #1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl MOD09_02216190
	b _02212C78
_02212C28:
	mov r0, #3
	strb r0, [r4, r7]
	b _02212C78
_02212C2E:
	add r2, r5, #0
	add r2, #0x33
	ldrh r1, [r5, #0x22]
	ldrb r2, [r2]
	ldr r0, [r5, #8]
	ldr r3, [r5, #0xc]
	bl MOD09_02213C84
	add r0, r4, #0
	bl MOD09_02216314
	mov r1, #0x19
	sub r0, r7, #3
	strb r1, [r4, r0]
	mov r0, #0x11
	pop {r3, r4, r5, r6, r7, pc}
_02212C4E:
	ldrb r1, [r5, #0x11]
	add r3, r4, #0
	mov r2, #0x50
	mul r2, r1
	add r1, r7, #2
	add r3, #0x14
	ldrh r6, [r4, r1]
	ldrh r1, [r3, r2]
	cmp r6, r1
	beq _02212C72
	add r1, r1, #1
	strh r1, [r3, r2]
	ldrb r1, [r5, #0x11]
	bl MOD09_0221567C
	add r0, r4, #0
	bl MOD09_022186C0
_02212C72:
	ldr r0, _02212C7C ; =0x0000207C
	mov r1, #1
	strb r1, [r4, r0]
_02212C78:
	mov r0, #0x17
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02212C7C: .word 0x0000207C
_02212C80: .word 0x00001FB8
_02212C84: .word 0x0000207E
_02212C88: .word 0x000005EC

	thumb_func_start MOD09_02212C8C
MOD09_02212C8C: ; 0x02212C8C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5]
	str r0, [sp, #4]
	ldr r0, _02212DAC ; =0x0000207C
	ldrb r0, [r5, r0]
	cmp r0, #0
	beq _02212CA8
	cmp r0, #1
	beq _02212D12
	cmp r0, #2
	beq _02212D7C
	b _02212DA4
_02212CA8:
	ldr r2, [sp, #4]
	ldr r0, [sp, #4]
	ldrb r3, [r2, #0x11]
	ldr r1, [sp, #4]
	ldr r0, [r0, #8]
	add r2, r2, r3
	add r2, #0x2c
	ldrb r2, [r2]
	ldr r1, [r1, #0x28]
	bl MOD11_02230014
	ldr r1, [sp, #4]
	mov r7, #0
	ldrb r2, [r1, #0x11]
	mov r1, #0x50
	add r6, r7, #0
	mul r1, r2
	add r1, r5, r1
	str r0, [r1, #4]
	add r4, r5, #0
_02212CD0:
	ldr r0, [sp, #4]
	ldrb r1, [r0, #0x11]
	mov r0, #0x50
	mul r0, r1
	add r1, r5, r0
	add r0, r1, r6
	ldrh r0, [r0, #0x34]
	cmp r0, #0
	beq _02212CF4
	ldr r0, [r1, #4]
	add r1, r7, #0
	add r1, #0x3a
	mov r2, #0
	bl GetMonData
	mov r1, #0x82
	lsl r1, r1, #6
	strh r0, [r4, r1]
_02212CF4:
	add r7, r7, #1
	add r6, #8
	add r4, r4, #2
	cmp r7, #4
	blo _02212CD0
	add r0, r5, #0
	bl MOD09_02216378
	ldr r0, _02212DB0 ; =0x000005EC
	bl PlaySE
	ldr r0, _02212DAC ; =0x0000207C
	mov r1, #1
	strb r1, [r5, r0]
	b _02212DA4
_02212D12:
	mov r6, #0
	add r4, r6, #0
	str r6, [sp]
	add r7, r5, #0
_02212D1A:
	ldr r0, [sp, #4]
	ldrb r1, [r0, #0x11]
	mov r0, #0x50
	mul r0, r1
	add r1, r5, r0
	ldr r0, [sp]
	add r1, r1, r0
	ldrh r0, [r1, #0x34]
	cmp r0, #0
	bne _02212D32
	add r6, r6, #1
	b _02212D62
_02212D32:
	mov r0, #0x82
	add r2, r1, #0
	lsl r0, r0, #6
	add r2, #0x36
	ldrh r0, [r7, r0]
	ldrb r2, [r2]
	cmp r0, r2
	beq _02212D60
	add r0, r1, #0
	add r0, #0x36
	ldrb r0, [r0]
	lsl r2, r4, #0x10
	add r1, #0x36
	add r0, r0, #1
	strb r0, [r1]
	add r1, r4, #1
	lsl r1, r1, #0x10
	add r0, r5, #0
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	bl MOD09_02216190
	b _02212D62
_02212D60:
	add r6, r6, #1
_02212D62:
	ldr r0, [sp]
	add r4, r4, #1
	add r0, #8
	add r7, r7, #2
	str r0, [sp]
	cmp r4, #4
	blo _02212D1A
	cmp r6, #4
	bne _02212DA4
	ldr r0, _02212DAC ; =0x0000207C
	mov r1, #2
	strb r1, [r5, r0]
	b _02212DA4
_02212D7C:
	ldr r2, [sp, #4]
	ldr r1, [sp, #4]
	ldr r0, [sp, #4]
	add r2, #0x33
	ldr r3, [sp, #4]
	ldrh r1, [r1, #0x22]
	ldrb r2, [r2]
	ldr r0, [r0, #8]
	ldr r3, [r3, #0xc]
	bl MOD09_02213C84
	add r0, r5, #0
	bl MOD09_02216314
	ldr r0, _02212DB4 ; =0x00002079
	mov r1, #0x19
	strb r1, [r5, r0]
	add sp, #8
	mov r0, #0x11
	pop {r3, r4, r5, r6, r7, pc}
_02212DA4:
	mov r0, #0x18
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02212DAC: .word 0x0000207C
_02212DB0: .word 0x000005EC
_02212DB4: .word 0x00002079

	thumb_func_start MOD09_02212DB8
MOD09_02212DB8: ; 0x02212DB8
	push {lr}
	sub sp, #0xc
	mov r2, #0
	str r2, [sp]
	mov r1, #0x10
	str r1, [sp, #4]
	mov r1, #0x7a
	str r2, [sp, #8]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r1, #0xa
	add r3, r1, #0
	ldr r2, _02212DE0 ; =0x0000FFFF
	sub r3, #0x12
	bl FUN_02003210
	mov r0, #0x1a
	add sp, #0xc
	pop {pc}
	nop
_02212DE0: .word 0x0000FFFF

	thumb_func_start MOD09_02212DE4
MOD09_02212DE4: ; 0x02212DE4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x7a
	add r4, r1, #0
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_020038E4
	cmp r0, #0
	beq _02212DFC
	mov r0, #0
	pop {r3, r4, r5, pc}
_02212DFC:
	add r0, r4, #0
	bl MOD09_02213190
	add r0, r4, #0
	bl MOD09_02216B74
	add r0, r4, #0
	bl MOD09_02213DF8
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD09_02212F5C
	ldr r0, _02212E48 ; =0x00002088
	ldr r0, [r4, r0]
	bl MOD09_0221AC28
	ldr r1, [r4]
	add r1, #0x32
	strb r0, [r1]
	ldr r0, _02212E48 ; =0x00002088
	ldr r0, [r4, r0]
	bl MOD09_0221AC1C
	mov r0, #2
	bl FUN_02002CF8
	ldr r0, [r4]
	mov r1, #1
	add r0, #0x36
	strb r1, [r0]
	add r0, r5, #0
	bl FUN_0200621C
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_02212E48: .word 0x00002088

	thumb_func_start MOD09_02212E4C
MOD09_02212E4C: ; 0x02212E4C
	push {r3, r4, r5, lr}
	sub sp, #0x80
	ldr r5, _02212F48 ; =0x0221AED0
	add r3, sp, #0x70
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	mov r1, #1
	bl SetScreenModeAndDisable
	ldr r5, _02212F4C ; =0x0221AF48
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #7
	str r0, [r3]
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r3, #0
	bl InitBgFromTemplate
	ldr r5, _02212F50 ; =0x0221AF80
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #6
	str r0, [r3]
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r3, #0
	bl InitBgFromTemplate
	ldr r5, _02212F54 ; =0x0221AF9C
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #5
	str r0, [r3]
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl BgClearTilemapBufferAndCommit
	ldr r5, _02212F58 ; =0x0221AF64
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #4
	str r0, [r3]
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #4
	bl BgClearTilemapBufferAndCommit
	ldr r3, [r4]
	mov r0, #5
	ldr r3, [r3, #0xc]
	mov r1, #0x20
	mov r2, #0
	bl BG_ClearCharDataRange
	ldr r3, [r4]
	mov r0, #4
	ldr r3, [r3, #0xc]
	mov r1, #0x20
	mov r2, #0
	bl BG_ClearCharDataRange
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl ScheduleBgTilemapBufferTransfer
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #4
	bl ScheduleBgTilemapBufferTransfer
	add sp, #0x80
	pop {r3, r4, r5, pc}
	.align 2, 0
_02212F48: .word MOD9_0221AED0
_02212F4C: .word MOD9_0221AF48
_02212F50: .word MOD9_0221AF80
_02212F54: .word MOD9_0221AF9C
_02212F58: .word MOD9_0221AF64

	thumb_func_start MOD09_02212F5C
MOD09_02212F5C: ; 0x02212F5C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x1f
	mov r1, #0
	bl GX_EngineBToggleLayers
	add r0, r4, #0
	mov r1, #4
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	mov r1, #5
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	mov r1, #6
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	mov r1, #7
	bl FreeBgTilemapBuffer
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD09_02212F8C
MOD09_02212F8C: ; 0x02212F8C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5]
	mov r2, #0x79
	ldr r0, [r0, #0xc]
	lsl r2, r2, #2
	str r0, [sp, #0xc]
	ldr r2, [r5, r2]
	mov r0, #0x48
	mov r1, #0x16
	mov r3, #7
	bl GfGfxLoader_LoadCharData
	ldr r2, [r5]
	mov r0, #0x48
	ldr r2, [r2, #0xc]
	mov r1, #0x14
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0x10
	add r4, r0, #0
	bl NNS_G2dGetUnpackedScreenData
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	add r1, #0xc
	bl MOD09_0221790C
	add r0, r4, #0
	bl FreeToHeap
	ldr r2, [r5]
	mov r0, #0x48
	ldr r2, [r2, #0xc]
	mov r1, #0x15
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0x10
	add r4, r0, #0
	bl NNS_G2dGetUnpackedScreenData
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	add r1, #0xc
	bl MOD09_02217C38
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	str r0, [sp]
	lsl r0, r0, #9
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #0x7a
	ldr r3, [r5]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r3, [r3, #0xc]
	mov r1, #0x48
	mov r2, #0x17
	bl PaletteData_LoadNarc
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl PaletteData_GetUnfadedBuf
	add r2, r0, #0
	ldr r0, _02213134 ; =0x00001F60
	mov r1, #6
	lsl r1, r1, #6
	add r1, r2, r1
	add r0, r5, r0
	mov r2, #0x40
	bl memcpy
	mov r0, #1
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xd0
	str r0, [sp, #8]
	mov r0, #0x7a
	ldr r3, [r5]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r3, [r3, #0xc]
	mov r1, #0xe
	mov r2, #6
	bl PaletteData_LoadNarc
	mov r0, #1
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xf0
	str r0, [sp, #8]
	ldr r3, [r5]
	add r0, #0xf8
	ldr r0, [r5, r0]
	ldr r3, [r3, #0xc]
	mov r1, #0xe
	mov r2, #7
	bl PaletteData_LoadNarc
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl MOD11_02230E44
	add r4, r0, #0
	bl FUN_0200CD60
	add r1, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5]
	mov r2, #0x79
	ldr r0, [r0, #0xc]
	lsl r2, r2, #2
	str r0, [sp, #0xc]
	ldr r2, [r5, r2]
	mov r0, #0x26
	mov r3, #4
	bl GfGfxLoader_LoadCharData
	add r0, r4, #0
	bl FUN_0200CD64
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xe0
	str r0, [sp, #8]
	mov r0, #0x7a
	ldr r3, [r5]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r3, [r3, #0xc]
	mov r1, #0x26
	bl PaletteData_LoadNarc
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl PaletteData_GetUnfadedBuf
	add r6, r0, #0
	ldr r0, [r5]
	mov r1, #0x20
	ldr r0, [r0, #0xc]
	bl AllocFromHeap
	mov r1, #0x1a
	lsl r1, r1, #4
	add r1, r6, r1
	mov r2, #0x20
	add r4, r0, #0
	bl memcpy
	mov r2, #0x4d
	lsl r2, r2, #2
	add r0, r6, r2
	ldrb r3, [r0]
	add r1, r4, #0
	add r1, #0xe
	strb r3, [r4, #0xe]
	ldrb r3, [r0, #1]
	strb r3, [r1, #1]
	ldrb r3, [r0, #2]
	strb r3, [r1, #2]
	ldrb r0, [r0, #3]
	mov r3, #0xd0
	strb r0, [r1, #3]
	add r1, r2, #4
	add r0, r2, #4
	ldrb r1, [r6, r1]
	add r0, r6, r0
	add r2, #0xb4
	strb r1, [r4, #6]
	ldrb r1, [r0, #1]
	strb r1, [r4, #7]
	ldrb r1, [r0, #2]
	strb r1, [r4, #8]
	ldrb r0, [r0, #3]
	add r1, r4, #0
	strb r0, [r4, #9]
	mov r0, #0x20
	str r0, [sp]
	ldr r0, [r5, r2]
	mov r2, #1
	bl PaletteData_LoadPalette
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	nop
_02213134: .word 0x00001F60

	thumb_func_start MOD09_02213138
MOD09_02213138: ; 0x02213138
	push {r4, lr}
	add r4, r0, #0
	ldr r3, [r4]
	mov r0, #0
	ldr r3, [r3, #0xc]
	mov r1, #0x1a
	mov r2, #3
	bl NewMsgDataFromNarc
	ldr r1, _02213180 ; =0x00001FA8
	mov r2, #0
	str r0, [r4, r1]
	ldr r3, [r4]
	mov r0, #0xf
	ldr r3, [r3, #0xc]
	mov r1, #0xe
	bl MessagePrinter_new
	ldr r1, _02213184 ; =0x00001FA4
	str r0, [r4, r1]
	ldr r0, [r4]
	ldr r0, [r0, #0xc]
	bl ScrStrBufs_new
	ldr r1, _02213188 ; =0x00001FAC
	str r0, [r4, r1]
	ldr r1, [r4]
	mov r0, #2
	ldr r1, [r1, #0xc]
	lsl r0, r0, #8
	bl String_ctor
	ldr r1, _0221318C ; =0x00001FB0
	str r0, [r4, r1]
	pop {r4, pc}
	nop
_02213180: .word 0x00001FA8
_02213184: .word 0x00001FA4
_02213188: .word 0x00001FAC
_0221318C: .word 0x00001FB0

	thumb_func_start MOD09_02213190
MOD09_02213190: ; 0x02213190
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _022131B8 ; =0x00001FA8
	ldr r0, [r4, r0]
	bl DestroyMsgData
	ldr r0, _022131BC ; =0x00001FA4
	ldr r0, [r4, r0]
	bl MessagePrinter_delete
	ldr r0, _022131C0 ; =0x00001FAC
	ldr r0, [r4, r0]
	bl ScrStrBufs_delete
	ldr r0, _022131C4 ; =0x00001FB0
	ldr r0, [r4, r0]
	bl String_dtor
	pop {r4, pc}
	nop
_022131B8: .word 0x00001FA8
_022131BC: .word 0x00001FA4
_022131C0: .word 0x00001FAC
_022131C4: .word 0x00001FB0

	thumb_func_start MOD09_022131C8
MOD09_022131C8: ; 0x022131C8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [sp]
	ldr r0, [r0]
	ldr r0, [r0]
	bl GetPartyCount
	cmp r0, #0
	bgt _022131E2
	b _02213476
_022131E2:
	ldr r0, [sp, #8]
	mov r1, #0x50
	mul r1, r0
	ldr r0, [sp]
	str r1, [sp, #4]
	add r4, r0, r1
	ldr r0, [r0]
	ldr r1, [sp, #8]
	ldr r0, [r0]
	bl GetPartyMonByIndex
	str r0, [r4, #4]
	mov r1, #5
	mov r2, #0
	bl GetMonData
	strh r0, [r4, #8]
	ldrh r0, [r4, #8]
	cmp r0, #0
	bne _0221320C
	b _0221345A
_0221320C:
	ldr r0, [sp, #8]
	mov r1, #0x50
	add r5, r0, #0
	mul r5, r1
	ldr r0, [sp]
	mov r1, #0xa4
	add r4, r0, r5
	ldr r0, [r4, #4]
	mov r2, #0
	bl GetMonData
	strh r0, [r4, #0xa]
	ldr r0, [r4, #4]
	mov r1, #0xa5
	mov r2, #0
	bl GetMonData
	strh r0, [r4, #0xc]
	ldr r0, [r4, #4]
	mov r1, #0xa6
	mov r2, #0
	bl GetMonData
	strh r0, [r4, #0xe]
	ldr r0, [r4, #4]
	mov r1, #0xa7
	mov r2, #0
	bl GetMonData
	strh r0, [r4, #0x10]
	ldr r0, [r4, #4]
	mov r1, #0xa8
	mov r2, #0
	bl GetMonData
	strh r0, [r4, #0x12]
	ldr r0, [r4, #4]
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	strh r0, [r4, #0x14]
	ldr r0, [r4, #4]
	mov r1, #0xa3
	mov r2, #0
	bl GetMonData
	strh r0, [r4, #0x16]
	ldr r0, [r4, #4]
	mov r1, #0xb0
	mov r2, #0
	bl GetMonData
	strb r0, [r4, #0x18]
	ldr r0, [r4, #4]
	mov r1, #0xb1
	mov r2, #0
	bl GetMonData
	ldr r6, [sp]
	strb r0, [r4, #0x19]
	ldr r0, [r4, #4]
	add r6, #0x1a
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	ldrb r1, [r6, r5]
	mov r2, #0x7f
	lsl r0, r0, #0x18
	bic r1, r2
	lsr r2, r0, #0x18
	mov r0, #0x7f
	and r0, r2
	orr r0, r1
	strb r0, [r6, r5]
	ldr r0, [r4, #4]
	mov r1, #0xaf
	mov r2, #0
	bl GetMonData
	cmp r0, #1
	ldrb r1, [r6, r5]
	bne _022132BC
	mov r0, #0x80
	bic r1, r0
	strb r1, [r6, r5]
	b _022132C2
_022132BC:
	mov r0, #0x80
	orr r0, r1
	strb r0, [r6, r5]
_022132C2:
	ldr r0, [sp]
	add r4, r0, r5
	add r6, r0, #0
	ldr r0, [r4, #4]
	add r6, #0x1b
	bl GetMonGender
	ldrb r1, [r6, r5]
	mov r2, #7
	bic r1, r2
	mov r2, #7
	and r0, r2
	orr r0, r1
	strb r0, [r6, r5]
	ldr r0, [r4, #4]
	bl FUN_0207C2D4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1c
	ldrb r1, [r6, r5]
	mov r2, #0x78
	lsr r0, r0, #0x19
	bic r1, r2
	orr r0, r1
	strb r0, [r6, r5]
	ldr r0, [r4, #4]
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1f
	ldrb r1, [r6, r5]
	mov r2, #0x80
	lsr r0, r0, #0x18
	bic r1, r2
	orr r0, r1
	strb r0, [r6, r5]
	ldr r0, [r4, #4]
	mov r1, #0xa
	mov r2, #0
	bl GetMonData
	strh r0, [r4, #0x1c]
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #0
	bl GetMonData
	strh r0, [r4, #0x1e]
	ldr r0, [r4, #4]
	mov r1, #8
	mov r2, #0
	bl GetMonData
	ldr r6, [sp]
	str r0, [r4, #0x20]
	add r6, #0x1a
	ldrb r1, [r6, r5]
	ldrh r0, [r4, #8]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x19
	bl GetMonExpBySpeciesAndLevel
	str r0, [r4, #0x24]
	ldrb r0, [r6, r5]
	lsl r0, r0, #0x19
	lsr r1, r0, #0x19
	cmp r1, #0x64
	bne _0221335A
	ldr r0, [sp]
	add r4, r0, r5
	ldr r0, [r4, #0x24]
	b _02213366
_0221335A:
	ldr r0, [sp]
	add r1, r1, #1
	add r4, r0, r5
	ldrh r0, [r4, #8]
	bl GetMonExpBySpeciesAndLevel
_02213366:
	str r0, [r4, #0x28]
	ldr r0, [r4, #4]
	mov r1, #0x13
	mov r2, #0
	bl GetMonData
	add r1, r4, #0
	add r1, #0x2c
	strb r0, [r1]
	ldr r0, [r4, #4]
	mov r1, #0x14
	mov r2, #0
	bl GetMonData
	add r1, r4, #0
	add r1, #0x2d
	strb r0, [r1]
	ldr r0, [r4, #4]
	mov r1, #0x15
	mov r2, #0
	bl GetMonData
	add r1, r4, #0
	add r1, #0x2e
	strb r0, [r1]
	ldr r0, [r4, #4]
	mov r1, #0x16
	mov r2, #0
	bl GetMonData
	add r1, r4, #0
	add r1, #0x2f
	strb r0, [r1]
	ldr r0, [r4, #4]
	mov r1, #0x17
	mov r2, #0
	bl GetMonData
	add r1, r4, #0
	add r1, #0x30
	strb r0, [r1]
	ldr r0, [r4, #4]
	mov r1, #0xa1
	mov r2, #0
	bl GetMonData
	add r1, r4, #0
	add r1, #0x31
	strb r0, [r1]
	ldr r0, [r4, #4]
	mov r1, #0x70
	mov r2, #0
	bl GetMonData
	add r4, #0x32
	strb r0, [r4]
	ldr r1, [sp]
	ldr r0, [sp, #4]
	add r1, #0x34
	add r7, r1, r0
	ldr r1, [sp]
	mov r4, #0
	add r6, r1, r0
_022133E4:
	lsl r0, r4, #3
	add r1, r4, #0
	str r0, [sp, #0xc]
	add r5, r7, r0
	ldr r0, [r6, #4]
	add r1, #0x36
	mov r2, #0
	bl GetMonData
	ldr r1, [sp, #0xc]
	strh r0, [r7, r1]
	add r0, r1, #0
	ldrh r0, [r7, r0]
	cmp r0, #0
	beq _02213450
	add r1, r4, #0
	ldr r0, [r6, #4]
	add r1, #0x3a
	mov r2, #0
	bl GetMonData
	strb r0, [r5, #2]
	add r1, r4, #0
	ldr r0, [r6, #4]
	add r1, #0x3e
	mov r2, #0
	bl GetMonData
	strb r0, [r5, #3]
	ldrh r0, [r5]
	ldrb r1, [r5, #3]
	bl WazaGetMaxPp
	strb r0, [r5, #3]
	ldrh r0, [r5]
	mov r1, #3
	bl GetWazaAttr
	strb r0, [r5, #4]
	ldrh r0, [r5]
	mov r1, #1
	bl GetWazaAttr
	strb r0, [r5, #5]
	ldrh r0, [r5]
	mov r1, #4
	bl GetWazaAttr
	strb r0, [r5, #6]
	ldrh r0, [r5]
	mov r1, #2
	bl GetWazaAttr
	strb r0, [r5, #7]
_02213450:
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #4
	blo _022133E4
_0221345A:
	ldr r0, [sp, #8]
	add r0, r0, #1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	ldr r0, [sp]
	ldr r0, [r0]
	ldr r0, [r0]
	bl GetPartyCount
	ldr r1, [sp, #8]
	cmp r1, r0
	bge _02213476
	b _022131E2
_02213476:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD09_0221347C
MOD09_0221347C: ; 0x0221347C
	push {r3, r4, r5, lr}
	ldr r1, _022134EC ; =0x0221AFB8
	add r4, r0, #0
	bl MOD09_02213614
	add r5, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	bne _022134C8
	ldr r0, _022134F0 ; =0x00002088
	ldr r0, [r4, r0]
	bl MOD09_0221AD30
	add r5, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	bne _022134A6
	mov r5, #6
	b _022134B0
_022134A6:
	add r0, r0, #1
	cmp r5, r0
	bne _022134B0
	mov r0, #0
	pop {r3, r4, r5, pc}
_022134B0:
	cmp r5, #6
	beq _022134C0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD09_02213620
	cmp r0, #0
	beq _022134E6
_022134C0:
	ldr r0, [r4]
	strb r5, [r0, #0x11]
	mov r0, #1
	pop {r3, r4, r5, pc}
_022134C8:
	cmp r5, #6
	beq _022134D8
	add r0, r4, #0
	add r1, r5, #0
	bl MOD09_02213620
	cmp r0, #0
	beq _022134E6
_022134D8:
	ldr r0, [r4]
	strb r5, [r0, #0x11]
	add r0, r4, #0
	bl MOD09_022178E4
	mov r0, #1
	pop {r3, r4, r5, pc}
_022134E6:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_022134EC: .word MOD9_0221AFB8
_022134F0: .word 0x00002088

	thumb_func_start MOD09_022134F4
MOD09_022134F4: ; 0x022134F4
	push {r3, r4, r5, lr}
	ldr r1, _02213534 ; =0x0221AEF0
	add r5, r0, #0
	bl MOD09_02213614
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _02213528
	ldr r0, _02213538 ; =0x00002088
	ldr r0, [r5, r0]
	bl MOD09_0221AD30
	add r4, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _0221351E
	mov r4, #3
	b _0221352E
_0221351E:
	add r0, r0, #1
	cmp r4, r0
	bne _0221352E
	mov r0, #0xff
	pop {r3, r4, r5, pc}
_02213528:
	add r0, r5, #0
	bl MOD09_022178E4
_0221352E:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_02213534: .word MOD9_0221AEF0
_02213538: .word 0x00002088

	thumb_func_start MOD09_0221353C
MOD09_0221353C: ; 0x0221353C
	push {r3, r4, r5, lr}
	ldr r1, _0221357C ; =0x0221AF04
	add r5, r0, #0
	bl MOD09_02213614
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _02213570
	ldr r0, _02213580 ; =0x00002088
	ldr r0, [r5, r0]
	bl MOD09_0221AD30
	add r4, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _02213566
	mov r4, #3
	b _02213576
_02213566:
	add r0, r0, #1
	cmp r4, r0
	bne _02213576
	mov r0, #0xff
	pop {r3, r4, r5, pc}
_02213570:
	add r0, r5, #0
	bl MOD09_022178E4
_02213576:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221357C: .word MOD9_0221AF04
_02213580: .word 0x00002088

	thumb_func_start MOD09_02213584
MOD09_02213584: ; 0x02213584
	push {r3, r4, r5, lr}
	ldr r1, _022135C4 ; =0x0221AFF8
	add r5, r0, #0
	bl MOD09_02213614
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _022135B8
	ldr r0, _022135C8 ; =0x00002088
	ldr r0, [r5, r0]
	bl MOD09_0221AD30
	add r4, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _022135AE
	mov r4, #7
	b _022135BE
_022135AE:
	add r0, r0, #1
	cmp r4, r0
	bne _022135BE
	mov r0, #0xff
	pop {r3, r4, r5, pc}
_022135B8:
	add r0, r5, #0
	bl MOD09_022178E4
_022135BE:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_022135C4: .word MOD9_0221AFF8
_022135C8: .word 0x00002088

	thumb_func_start MOD09_022135CC
MOD09_022135CC: ; 0x022135CC
	push {r3, r4, r5, lr}
	ldr r1, _0221360C ; =0x0221AF18
	add r5, r0, #0
	bl MOD09_02213614
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _02213600
	ldr r0, _02213610 ; =0x00002088
	ldr r0, [r5, r0]
	bl MOD09_0221AD30
	add r4, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _022135F6
	mov r4, #4
	b _02213606
_022135F6:
	add r0, r0, #1
	cmp r4, r0
	bne _02213606
	mov r0, #0xff
	pop {r3, r4, r5, pc}
_02213600:
	add r0, r5, #0
	bl MOD09_022178E4
_02213606:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221360C: .word MOD9_0221AF18
_02213610: .word 0x00002088

	thumb_func_start MOD09_02213614
MOD09_02213614: ; 0x02213614
	ldr r3, _0221361C ; =FUN_02020988
	add r0, r1, #0
	bx r3
	nop
_0221361C: .word FUN_02020988

	thumb_func_start MOD09_02213620
MOD09_02213620: ; 0x02213620
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #0x50
	add r5, r0, #0
	mul r1, r4
	add r1, r5, r1
	ldrh r1, [r1, #8]
	cmp r1, #0
	bne _02213636
	mov r0, #0
	pop {r3, r4, r5, pc}
_02213636:
	cmp r4, #0
	beq _02213650
	bl MOD09_02213B9C
	cmp r0, #0
	bne _0221364C
	add r0, r5, #0
	bl MOD09_02213BBC
	cmp r0, #0
	beq _02213654
_0221364C:
	cmp r4, #1
	bne _02213654
_02213650:
	mov r0, #1
	pop {r3, r4, r5, pc}
_02213654:
	mov r0, #2
	pop {r3, r4, r5, pc}

	thumb_func_start MOD09_02213658
MOD09_02213658: ; 0x02213658
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	add r7, r2, #0
	add r6, r4, #0
	bl MOD09_02213BBC
	cmp r0, #1
	bne _022136D0
	ldr r2, _0221370C ; =0x0221AEC8
	add r1, sp, #0
	ldrb r3, [r2]
	add r0, sp, #0
	mov r4, #0
	strb r3, [r1]
	ldrb r3, [r2, #1]
	strb r3, [r1, #1]
	ldrb r3, [r2, #2]
	strb r3, [r1, #2]
	ldrb r3, [r2, #3]
	strb r3, [r1, #3]
	ldrb r3, [r2, #4]
	ldrb r2, [r2, #5]
	strb r3, [r1, #4]
	strb r2, [r1, #5]
_0221368C:
	ldrb r1, [r0]
	cmp r6, r1
	beq _0221369A
	add r4, r4, #1
	add r0, r0, #1
	cmp r4, #6
	blt _0221368C
_0221369A:
	add r4, r4, r7
	bpl _022136A2
	mov r4, #5
	b _022136A8
_022136A2:
	cmp r4, #6
	blt _022136A8
	mov r4, #0
_022136A8:
	add r0, sp, #0
	ldrb r1, [r0, r4]
	cmp r6, r1
	beq _02213704
	add r0, r5, #0
	bl MOD09_02213620
	cmp r0, #0
	beq _0221369A
	add r0, sp, #0
	ldrb r0, [r0, r4]
	mov r1, #0x50
	mul r1, r0
	add r1, r5, r1
	ldrb r1, [r1, #0x1b]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1f
	bne _0221369A
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_022136D0:
	add r4, r4, r7
	bpl _022136D8
	mov r4, #5
	b _022136DE
_022136D8:
	cmp r4, #6
	blt _022136DE
	mov r4, #0
_022136DE:
	cmp r6, r4
	beq _02213704
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02213620
	cmp r0, #0
	beq _022136D0
	mov r0, #0x50
	mul r0, r4
	add r0, r5, r0
	ldrb r0, [r0, #0x1b]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bne _022136D0
	lsl r0, r4, #0x18
	add sp, #8
	lsr r0, r0, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_02213704:
	mov r0, #0xff
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221370C: .word MOD9_0221AEC8

	thumb_func_start MOD09_02213710
MOD09_02213710: ; 0x02213710
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	cmp r1, #2
	bne _0221378E
	ldr r0, [r6]
	add r2, r6, #4
	ldrb r1, [r0, #0x11]
	mov r0, #0x50
	mul r0, r1
	add r0, r2, r0
	ldrb r1, [r0, #0x16]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x19
	cmp r1, #0x64
	bhs _0221373A
	ldr r2, [r0, #0x20]
	ldr r1, [r0, #0x24]
	ldr r0, [r0, #0x1c]
	sub r1, r1, r2
	sub r0, r0, r2
	b _0221373E
_0221373A:
	mov r1, #0
	add r0, r1, #0
_0221373E:
	mov r2, #0x40
	bl FUN_02079A0C
	add r4, r0, #0
	mov r5, #0
	mov r7, #0x1e
_0221374A:
	cmp r4, #8
	blo _02213752
	add r1, r7, #0
	b _0221375A
_02213752:
	add r0, r4, #0
	add r0, #0x16
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
_0221375A:
	add r2, r5, #0
	add r2, #0xa
	lsl r2, r2, #0x10
	add r0, r6, #0
	lsr r2, r2, #0x10
	mov r3, #8
	bl MOD09_02213790
	cmp r4, #8
	bhs _02213772
	mov r4, #0
	b _02213778
_02213772:
	sub r4, #8
	lsl r0, r4, #0x18
	lsr r4, r0, #0x18
_02213778:
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #8
	blo _0221374A
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	mov r1, #7
	bl ScheduleBgTilemapBufferTransfer
_0221378E:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD09_02213790
MOD09_02213790: ; 0x02213790
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r1, #0
	lsl r1, r3, #0x18
	lsr r1, r1, #0x18
	str r1, [sp]
	mov r1, #1
	str r1, [sp, #4]
	add r4, r2, #0
	str r1, [sp, #8]
	mov r1, #0x10
	str r1, [sp, #0xc]
	mov r1, #0x79
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	lsl r3, r4, #0x18
	mov r1, #7
	add r2, r5, #0
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD09_022137C0
MOD09_022137C0: ; 0x022137C0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0xe
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x10
	lsl r6, r2, #1
	add r4, r1, #0
	str r0, [sp, #0xc]
	mov r0, #0x79
	add r7, r6, #2
	lsl r0, r0, #2
	lsl r3, r7, #0x18
	ldr r0, [r5, r0]
	mov r1, #7
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	mov r0, #0xe
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	mov r0, #0x79
	add r6, r6, #3
	lsl r0, r0, #2
	add r2, r4, #1
	lsl r2, r2, #0x10
	lsl r3, r6, #0x18
	ldr r0, [r5, r0]
	mov r1, #7
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	mov r0, #0xf
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	mov r0, #0x79
	add r2, r4, #0
	lsl r0, r0, #2
	add r2, #0x20
	lsl r2, r2, #0x10
	lsl r3, r7, #0x18
	ldr r0, [r5, r0]
	mov r1, #7
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	mov r0, #0xf
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	mov r0, #0x79
	lsl r0, r0, #2
	add r4, #0x21
	lsl r2, r4, #0x10
	lsl r3, r6, #0x18
	ldr r0, [r5, r0]
	mov r1, #7
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD09_02213860
MOD09_02213860: ; 0x02213860
	push {r4, r5, r6, lr}
	ldr r6, _02213880 ; =0x00000125
	add r5, r0, #0
	mov r4, #0
_02213868:
	lsl r2, r4, #0x18
	add r0, r5, #0
	add r1, r6, #0
	lsr r2, r2, #0x18
	bl MOD09_022137C0
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #6
	blo _02213868
	pop {r4, r5, r6, pc}
	.align 2, 0
_02213880: .word 0x00000125

	thumb_func_start MOD09_02213884
MOD09_02213884: ; 0x02213884
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	cmp r1, #9
	bne _022138EE
	bl MOD09_02213860
	ldr r1, [r5]
	add r0, r1, #0
	add r0, #0x34
	ldrb r2, [r0]
	cmp r2, #4
	bhs _022138AC
	ldrb r1, [r1, #0x11]
	mov r0, #0x50
	mul r0, r1
	add r1, r5, r0
	lsl r0, r2, #3
	add r0, r1, r0
	ldrh r0, [r0, #0x34]
	b _022138AE
_022138AC:
	ldrh r0, [r1, #0x24]
_022138AE:
	mov r1, #0xa
	bl GetWazaAttr
	bl FUN_02083114
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x18
	asr r6, r0, #0x18
	mov r4, #0
	cmp r6, #0
	ble _022138E2
	mov r7, #5
	lsl r7, r7, #6
_022138CC:
	lsl r2, r4, #0x18
	add r0, r5, #0
	add r1, r7, #0
	lsr r2, r2, #0x18
	bl MOD09_022137C0
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r6
	blt _022138CC
_022138E2:
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #7
	bl ScheduleBgTilemapBufferTransfer
_022138EE:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD09_022138F0
MOD09_022138F0: ; 0x022138F0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD09_02213968
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #4
	mov r2, #0
	bl BgFillTilemapBufferAndSchedule
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #5
	mov r2, #0
	bl BgFillTilemapBufferAndSchedule
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02216D80
	add r0, r5, #0
	bl MOD09_02213DE0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02213CF4
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02213E28
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02213710
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02213884
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02217838
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_022182E8
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02218640
	ldr r0, _02213964 ; =0x0000207A
	strb r4, [r5, r0]
	pop {r3, r4, r5, pc}
	nop
_02213964: .word 0x0000207A

	thumb_func_start MOD09_02213968
MOD09_02213968: ; 0x02213968
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r2, _022139D0 ; =0x0221B01C
	add r5, r0, #0
	lsl r0, r1, #3
	mov r4, #0
	add r6, r2, r0
_02213976:
	ldr r2, [r5]
	ldr r1, [r6]
	ldr r2, [r2, #0xc]
	mov r0, #0x48
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0xc
	add r7, r0, #0
	bl NNS_G2dGetUnpackedScreenData
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0x79
	lsl r0, r0, #2
	add r1, r4, #6
	ldr r2, [sp, #0xc]
	lsl r1, r1, #0x18
	ldr r0, [r5, r0]
	lsr r1, r1, #0x18
	add r2, #0xc
	mov r3, #0
	bl LoadRectToBgTilemapRect
	mov r0, #0x79
	lsl r0, r0, #2
	add r1, r4, #6
	lsl r1, r1, #0x18
	ldr r0, [r5, r0]
	lsr r1, r1, #0x18
	bl ScheduleBgTilemapBufferTransfer
	add r0, r7, #0
	bl FreeToHeap
	add r4, r4, #1
	add r6, r6, #4
	cmp r4, #2
	blo _02213976
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022139D0: .word MOD9_0221B01C

	thumb_func_start MOD09_022139D4
MOD09_022139D4: ; 0x022139D4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r1, [r5]
	mov r2, #0x50
	ldrb r1, [r1, #0x11]
	add r3, r5, #4
	mul r2, r1
	add r4, r3, r2
	bl MOD09_02213BDC
	cmp r0, #1
	bne _02213A30
	ldr r0, _02213B70 ; =0x00001FA8
	mov r1, #0x50
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	ldr r1, [r5]
	add r4, r0, #0
	ldr r0, [r1, #8]
	ldr r1, [r1, #0x28]
	bl MOD11_022302BC
	add r1, r0, #0
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl MOD11_02230188
	add r2, r0, #0
	ldr r0, _02213B74 ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferTrainerNameFromDataStruct
	ldr r1, _02213B74 ; =0x00001FAC
	add r2, r4, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02213A30:
	ldrh r0, [r4, #0x10]
	cmp r0, #0
	bne _02213A6C
	ldr r0, _02213B70 ; =0x00001FA8
	mov r1, #0x4d
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	add r6, r0, #0
	ldr r0, [r4]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _02213B74 ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferBoxMonNickname
	ldr r1, _02213B74 ; =0x00001FAC
	add r2, r6, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_dtor
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02213A6C:
	ldr r2, [r5]
	ldrb r0, [r2, #0x11]
	add r0, r2, r0
	add r0, #0x2c
	ldrb r1, [r0]
	ldrb r0, [r2, #0x14]
	cmp r0, r1
	beq _02213A82
	ldrb r0, [r2, #0x15]
	cmp r0, r1
	bne _02213AB8
_02213A82:
	ldr r0, _02213B70 ; =0x00001FA8
	mov r1, #0x4c
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	add r6, r0, #0
	ldr r0, [r4]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _02213B74 ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferBoxMonNickname
	ldr r1, _02213B74 ; =0x00001FAC
	add r2, r6, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_dtor
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02213AB8:
	add r0, r5, #0
	bl MOD09_02213B7C
	cmp r0, #1
	bne _02213AD4
	ldr r2, _02213B70 ; =0x00001FA8
	mov r1, #0x4f
	ldr r0, [r5, r2]
	add r2, #8
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02213AD4:
	ldr r2, [r5]
	ldrb r1, [r2, #0x12]
	cmp r1, #6
	beq _02213B24
	ldrb r4, [r2, #0x11]
	add r0, r2, r4
	add r0, #0x2c
	ldrb r0, [r0]
	cmp r1, r0
	bne _02213B24
	ldr r0, _02213B70 ; =0x00001FA8
	mov r1, #0x5d
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r0, #0x50
	mul r0, r4
	add r0, r5, r0
	ldr r0, [r0, #4]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _02213B74 ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferBoxMonNickname
	ldr r1, _02213B74 ; =0x00001FAC
	add r2, r6, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_dtor
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02213B24:
	ldrh r0, [r2, #0x24]
	cmp r0, #0
	beq _02213B6C
	ldr r1, _02213B78 ; =0x00002076
	mov r0, #0x50
	ldrb r2, [r5, r1]
	sub r1, #0xce
	add r4, r5, #4
	add r6, r2, #0
	mul r6, r0
	ldr r0, [r5, r1]
	mov r1, #0x4e
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldr r0, [r4, r6]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _02213B74 ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferBoxMonNickname
	ldr r1, _02213B74 ; =0x00001FAC
	add r2, r7, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r7, #0
	bl String_dtor
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02213B6C:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02213B70: .word 0x00001FA8
_02213B74: .word 0x00001FAC
_02213B78: .word 0x00002076

	thumb_func_start MOD09_02213B7C
MOD09_02213B7C: ; 0x02213B7C
	ldr r1, [r0]
	ldrb r2, [r1, #0x11]
	mov r1, #0x50
	mul r1, r2
	add r0, r0, r1
	ldrb r0, [r0, #0x1b]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	beq _02213B92
	mov r0, #1
	b _02213B94
_02213B92:
	mov r0, #0
_02213B94:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
	.align 2, 0

	thumb_func_start MOD09_02213B9C
MOD09_02213B9C: ; 0x02213B9C
	push {r3, lr}
	ldr r0, [r0]
	ldr r0, [r0, #8]
	bl MOD11_0222FF74
	cmp r0, #0x4a
	beq _02213BB8
	cmp r0, #0x4b
	beq _02213BB8
	mov r1, #0x12
	tst r0, r1
	beq _02213BB8
	mov r0, #1
	pop {r3, pc}
_02213BB8:
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD09_02213BBC
MOD09_02213BBC: ; 0x02213BBC
	push {r3, lr}
	ldr r0, [r0]
	ldr r0, [r0, #8]
	bl MOD11_0222FF74
	cmp r0, #0x4a
	beq _02213BD8
	cmp r0, #0x4b
	beq _02213BD8
	mov r1, #8
	tst r0, r1
	beq _02213BD8
	mov r0, #1
	pop {r3, pc}
_02213BD8:
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD09_02213BDC
MOD09_02213BDC: ; 0x02213BDC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD09_02213BBC
	cmp r0, #1
	bne _02213C04
	ldr r0, _02213C08 ; =0x0000208F
	ldrb r0, [r5, r0]
	cmp r0, #2
	bne _02213BFC
	mov r0, #1
	add r1, r4, #0
	tst r1, r0
	beq _02213C04
	pop {r3, r4, r5, pc}
_02213BFC:
	mov r0, #1
	add r1, r4, #0
	tst r1, r0
	beq _02213C06
_02213C04:
	mov r0, #0
_02213C06:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02213C08: .word 0x0000208F

	thumb_func_start MOD09_02213C0C
MOD09_02213C0C: ; 0x02213C0C
	ldr r2, [r0]
	add r1, r2, #0
	add r1, #0x34
	ldrb r3, [r1]
	cmp r3, #4
	bne _02213C1C
	ldrh r0, [r2, #0x24]
	b _02213C2A
_02213C1C:
	ldrb r2, [r2, #0x11]
	mov r1, #0x50
	mul r1, r2
	add r1, r0, r1
	lsl r0, r3, #3
	add r0, r1, r0
	ldrh r0, [r0, #0x34]
_02213C2A:
	ldr r3, _02213C30 ; =MoveIsHM
	bx r3
	nop
_02213C30: .word MoveIsHM

	thumb_func_start MOD09_02213C34
MOD09_02213C34: ; 0x02213C34
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02213C64 ; =0x00002020
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_0200C644
	ldr r0, _02213C68 ; =0x00002070
	ldr r0, [r4, r0]
	add r0, #0xa0
	bl ClearWindowTilemapAndScheduleTransfer
	ldr r0, _02213C68 ; =0x00002070
	ldr r0, [r4, r0]
	add r0, #0x60
	bl ClearWindowTilemapAndScheduleTransfer
	ldr r0, _02213C68 ; =0x00002070
	ldr r0, [r4, r0]
	add r0, #0x70
	bl ClearWindowTilemapAndScheduleTransfer
	pop {r4, pc}
	nop
_02213C64: .word 0x00002020
_02213C68: .word 0x00002070

	thumb_func_start MOD09_02213C6C
MOD09_02213C6C: ; 0x02213C6C
	push {r4, lr}
	add r4, r0, #0
	bl MOD09_02213860
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #7
	bl ScheduleBgTilemapBufferTransfer
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD09_02213C84
MOD09_02213C84: ; 0x02213C84
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	add r7, r3, #0
	cmp r4, #0x41
	beq _02213CA8
	cmp r4, #0x43
	beq _02213CA8
	cmp r4, #0x42
	beq _02213CA8
	bl MOD11_02230214
	add r1, r4, #0
	mov r2, #1
	add r3, r7, #0
	bl Bag_TakeItem
_02213CA8:
	add r0, r5, #0
	bl MOD11_02230218
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_0206F1E4
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD09_02213CB8
MOD09_02213CB8: ; 0x02213CB8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r0, _02213CE8 ; =0x00002050
	ldr r4, _02213CEC ; =0x0221B06C
	mov r6, #0
	add r5, r7, r0
_02213CC4:
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	add r1, r5, #0
	add r2, r4, #0
	bl AddWindow
	add r6, r6, #1
	add r4, #8
	add r5, #0x10
	cmp r6, #2
	blo _02213CC4
	ldr r1, _02213CF0 ; =0x0000207A
	add r0, r7, #0
	ldrb r1, [r7, r1]
	bl MOD09_02213CF4
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02213CE8: .word 0x00002050
_02213CEC: .word MOD9_0221B06C
_02213CF0: .word 0x0000207A

	thumb_func_start MOD09_02213CF4
MOD09_02213CF4: ; 0x02213CF4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	cmp r1, #9
	bhi _02213D74
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02213D08: ; jump table
	.short _02213D1C - _02213D08 - 2 ; case 0
	.short _02213D26 - _02213D08 - 2 ; case 1
	.short _02213D30 - _02213D08 - 2 ; case 2
	.short _02213D3A - _02213D08 - 2 ; case 3
	.short _02213D44 - _02213D08 - 2 ; case 4
	.short _02213D4E - _02213D08 - 2 ; case 5
	.short _02213D58 - _02213D08 - 2 ; case 6
	.short _02213D62 - _02213D08 - 2 ; case 7
	.short _02213D58 - _02213D08 - 2 ; case 8
	.short _02213D6C - _02213D08 - 2 ; case 9
_02213D1C:
	ldr r0, _02213DB4 ; =0x00002074
	mov r1, #6
	ldr r6, _02213DB8 ; =0x0221B120
	strb r1, [r4, r0]
	b _02213D74
_02213D26:
	ldr r0, _02213DB4 ; =0x00002074
	mov r1, #4
	ldr r6, _02213DBC ; =0x0221B0A8
	strb r1, [r4, r0]
	b _02213D74
_02213D30:
	ldr r0, _02213DB4 ; =0x00002074
	mov r1, #0x23
	ldr r6, _02213DC0 ; =0x0221B2C8
	strb r1, [r4, r0]
	b _02213D74
_02213D3A:
	ldr r0, _02213DB4 ; =0x00002074
	mov r1, #0xb
	ldr r6, _02213DC4 ; =0x0221B188
	strb r1, [r4, r0]
	b _02213D74
_02213D44:
	ldr r0, _02213DB4 ; =0x00002074
	mov r1, #0x11
	ldr r6, _02213DC8 ; =0x0221B240
	strb r1, [r4, r0]
	b _02213D74
_02213D4E:
	ldr r0, _02213DB4 ; =0x00002074
	mov r1, #5
	ldr r6, _02213DCC ; =0x0221B0C8
	strb r1, [r4, r0]
	b _02213D74
_02213D58:
	ldr r0, _02213DB4 ; =0x00002074
	mov r1, #6
	ldr r6, _02213DD0 ; =0x0221B0F0
	strb r1, [r4, r0]
	b _02213D74
_02213D62:
	ldr r0, _02213DB4 ; =0x00002074
	mov r1, #0xc
	ldr r6, _02213DD4 ; =0x0221B1E0
	strb r1, [r4, r0]
	b _02213D74
_02213D6C:
	ldr r0, _02213DB4 ; =0x00002074
	mov r1, #7
	ldr r6, _02213DD8 ; =0x0221B150
	strb r1, [r4, r0]
_02213D74:
	ldr r1, _02213DB4 ; =0x00002074
	ldr r0, [r4]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0xc]
	bl AllocWindows
	ldr r1, _02213DDC ; =0x00002070
	mov r5, #0
	str r0, [r4, r1]
	add r0, r1, #4
	ldrb r0, [r4, r0]
	cmp r0, #0
	bls _02213DB2
	add r7, r1, #4
_02213D90:
	ldr r1, _02213DDC ; =0x00002070
	mov r0, #0x79
	ldr r2, [r4, r1]
	lsl r0, r0, #2
	lsl r1, r5, #4
	add r1, r2, r1
	lsl r2, r5, #3
	ldr r0, [r4, r0]
	add r2, r6, r2
	bl AddWindow
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	ldrb r0, [r4, r7]
	cmp r5, r0
	blo _02213D90
_02213DB2:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02213DB4: .word 0x00002074
_02213DB8: .word MOD9_0221B120
_02213DBC: .word MOD9_0221B0A8
_02213DC0: .word MOD9_0221B2C8
_02213DC4: .word MOD9_0221B188
_02213DC8: .word MOD9_0221B240
_02213DCC: .word MOD9_0221B0C8
_02213DD0: .word MOD9_0221B0F0
_02213DD4: .word MOD9_0221B1E0
_02213DD8: .word MOD9_0221B150
_02213DDC: .word 0x00002070

	thumb_func_start MOD09_02213DE0
MOD09_02213DE0: ; 0x02213DE0
	ldr r1, _02213DF0 ; =0x00002070
	add r2, r0, #0
	ldr r0, [r2, r1]
	add r1, r1, #4
	ldr r3, _02213DF4 ; =FUN_020191A4
	ldrb r1, [r2, r1]
	bx r3
	nop
_02213DF0: .word 0x00002070
_02213DF4: .word WindowArray_dtor

	thumb_func_start MOD09_02213DF8
MOD09_02213DF8: ; 0x02213DF8
	push {r3, r4, r5, lr}
	ldr r1, _02213E20 ; =0x00002070
	add r5, r0, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldrb r1, [r5, r1]
	bl WindowArray_dtor
	ldr r0, _02213E24 ; =0x00002050
	mov r4, #0
	add r5, r5, r0
_02213E0E:
	add r0, r5, #0
	bl RemoveWindow
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #2
	blo _02213E0E
	pop {r3, r4, r5, pc}
	nop
_02213E20: .word 0x00002070
_02213E24: .word 0x00002050

	thumb_func_start MOD09_02213E28
MOD09_02213E28: ; 0x02213E28
	push {r3, lr}
	cmp r1, #9
	bhi _02213E82
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02213E3A: ; jump table
	.short _02213E4E - _02213E3A - 2 ; case 0
	.short _02213E54 - _02213E3A - 2 ; case 1
	.short _02213E5A - _02213E3A - 2 ; case 2
	.short _02213E60 - _02213E3A - 2 ; case 3
	.short _02213E66 - _02213E3A - 2 ; case 4
	.short _02213E6C - _02213E3A - 2 ; case 5
	.short _02213E72 - _02213E3A - 2 ; case 6
	.short _02213E78 - _02213E3A - 2 ; case 7
	.short _02213E72 - _02213E3A - 2 ; case 8
	.short _02213E7E - _02213E3A - 2 ; case 9
_02213E4E:
	bl MOD09_022155D0
	pop {r3, pc}
_02213E54:
	bl MOD09_022156FC
	pop {r3, pc}
_02213E5A:
	bl MOD09_02215A2C
	pop {r3, pc}
_02213E60:
	bl MOD09_022158EC
	pop {r3, pc}
_02213E66:
	bl MOD09_02215C44
	pop {r3, pc}
_02213E6C:
	bl MOD09_0221609C
	pop {r3, pc}
_02213E72:
	bl MOD09_02215DA8
	pop {r3, pc}
_02213E78:
	bl MOD09_02215ED0
	pop {r3, pc}
_02213E7E:
	bl MOD09_022161B0
_02213E82:
	pop {r3, pc}

	thumb_func_start MOD09_02213E84
MOD09_02213E84: ; 0x02213E84
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r6, r0, #0
	ldr r0, _02214014 ; =0x00002070
	str r3, [sp, #0x14]
	ldr r5, [r6, r0]
	lsl r4, r1, #4
	ldr r0, [sp, #0x14]
	mov r1, #0x50
	mul r1, r0
	add r7, r6, #4
	add r0, r7, r1
	str r1, [sp, #0x24]
	ldr r1, [r6]
	str r0, [sp, #0x20]
	ldr r1, [r1, #0xc]
	mov r0, #0xc
	str r2, [sp, #0x10]
	bl String_ctor
	ldr r1, [sp, #0x14]
	str r0, [sp, #0x1c]
	ldr r0, _02214018 ; =0x00001FA8
	lsl r2, r1, #2
	ldr r1, _0221401C ; =0x0221B090
	ldr r0, [r6, r0]
	ldr r1, [r1, r2]
	bl NewString_ReadMsgData
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x24]
	ldr r0, [r7, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _02214020 ; =0x00001FAC
	mov r1, #0
	ldr r0, [r6, r0]
	bl BufferBoxMonNickname
	ldr r0, _02214020 ; =0x00001FAC
	ldr r1, [sp, #0x1c]
	ldr r0, [r6, r0]
	ldr r2, [sp, #0x18]
	bl StringExpandPlaceholders
	ldr r0, [sp, #0x10]
	add r3, sp, #0x38
	cmp r0, #0
	bne _02213F06
	ldrb r7, [r3, #0x14]
	mov r0, #0xff
	ldr r1, [sp, #0x10]
	str r7, [sp]
	str r0, [sp, #4]
	ldr r0, _02214024 ; =0x000F0E00
	ldr r2, [sp, #0x1c]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldrb r3, [r3, #0x10]
	add r0, r5, r4
	bl AddTextPrinterParameterized2
	b _02213F22
_02213F06:
	ldrb r7, [r3, #0x14]
	mov r0, #0xff
	ldr r1, [sp, #0x10]
	str r7, [sp]
	str r0, [sp, #4]
	ldr r0, _02214028 ; =0x00070809
	ldr r2, [sp, #0x1c]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldrb r3, [r3, #0x10]
	add r0, r5, r4
	bl AddTextPrinterParameterized2
_02213F22:
	ldr r0, [sp, #0x18]
	bl String_dtor
	ldr r0, [sp, #0x1c]
	bl String_dtor
	ldr r0, [sp, #0x20]
	ldrb r0, [r0, #0x16]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bne _02214008
	ldr r0, [sp, #0x20]
	ldrb r0, [r0, #0x17]
	lsl r1, r0, #0x18
	lsr r1, r1, #0x1f
	bne _02214008
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1d
	bne _02213FA6
	ldr r0, _02214018 ; =0x00001FA8
	mov r1, #0x10
	ldr r0, [r6, r0]
	bl NewString_ReadMsgData
	add r6, r0, #0
	add r0, r5, r4
	bl GetWindowWidth
	str r0, [sp, #0x28]
	mov r0, #0
	add r1, r6, #0
	add r2, r0, #0
	bl FUN_02002E14
	ldr r1, [sp, #0x28]
	str r7, [sp]
	lsl r1, r1, #3
	sub r3, r1, r0
	ldr r0, [sp, #0x10]
	cmp r0, #0
	bne _02213F8A
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0221402C ; =0x00070800
	mov r1, #0
	str r0, [sp, #8]
	add r0, r5, r4
	add r2, r6, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	b _02213F9E
_02213F8A:
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214030 ; =0x000A0B00
	mov r1, #0
	str r0, [sp, #8]
	add r0, r5, r4
	add r2, r6, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
_02213F9E:
	add r0, r6, #0
	bl String_dtor
	b _02214008
_02213FA6:
	cmp r0, #1
	bne _02214008
	ldr r0, _02214018 ; =0x00001FA8
	mov r1, #0x11
	ldr r0, [r6, r0]
	bl NewString_ReadMsgData
	add r6, r0, #0
	add r0, r5, r4
	bl GetWindowWidth
	str r0, [sp, #0x2c]
	mov r0, #0
	add r1, r6, #0
	add r2, r0, #0
	bl FUN_02002E14
	ldr r1, [sp, #0x2c]
	str r7, [sp]
	lsl r1, r1, #3
	sub r3, r1, r0
	ldr r0, [sp, #0x10]
	cmp r0, #0
	bne _02213FEE
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0xc1
	lsl r0, r0, #0xa
	str r0, [sp, #8]
	mov r1, #0
	add r0, r5, r4
	add r2, r6, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	b _02214002
_02213FEE:
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214034 ; =0x000C0D00
	mov r1, #0
	str r0, [sp, #8]
	add r0, r5, r4
	add r2, r6, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
_02214002:
	add r0, r6, #0
	bl String_dtor
_02214008:
	add r0, r5, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02214014: .word 0x00002070
_02214018: .word 0x00001FA8
_0221401C: .word MOD9_0221B090
_02214020: .word 0x00001FAC
_02214024: .word 0x000F0E00
_02214028: .word 0x00070809
_0221402C: .word 0x00070800
_02214030: .word 0x000A0B00
_02214034: .word 0x000C0D00

	thumb_func_start MOD09_02214038
MOD09_02214038: ; 0x02214038
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _0221407C ; =0x00002070
	lsl r4, r1, #4
	ldr r1, [r5, r0]
	add r3, #8
	add r1, r1, r4
	str r1, [sp, #4]
	str r3, [sp, #8]
	add r1, sp, #0x10
	ldrb r1, [r1, #0x10]
	mov r3, #0x50
	mul r3, r2
	str r1, [sp, #0xc]
	add r2, r5, r3
	ldrb r2, [r2, #0x1a]
	sub r0, #0xcc
	ldr r0, [r5, r0]
	lsl r2, r2, #0x19
	mov r1, #1
	lsr r2, r2, #0x19
	mov r3, #3
	bl FUN_0200BA78
	ldr r0, _0221407C ; =0x00002070
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221407C: .word 0x00002070

	thumb_func_start MOD09_02214080
MOD09_02214080: ; 0x02214080
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0x50
	add r7, r3, #0
	mul r0, r2
	add r3, r5, #4
	add r0, r3, r0
	str r0, [sp, #0xc]
	add r0, sp, #0x18
	ldrb r6, [r0, #0x10]
	ldr r0, _022140F8 ; =0x00002070
	lsl r4, r1, #4
	ldr r1, [r5, r0]
	sub r0, #0xcc
	add r1, r1, r4
	str r1, [sp]
	str r7, [sp, #4]
	str r6, [sp, #8]
	ldr r1, [sp, #0xc]
	ldr r0, [r5, r0]
	ldrh r1, [r1, #0x10]
	mov r2, #3
	mov r3, #1
	bl FUN_0200B9EC
	add r3, r7, #0
	ldr r2, _022140FC ; =0x00001FA4
	str r6, [sp]
	ldr r0, [r5, r2]
	add r2, #0xcc
	ldr r2, [r5, r2]
	mov r1, #0
	add r2, r2, r4
	add r3, #0x18
	bl FUN_0200B9A8
	ldr r0, _022140F8 ; =0x00002070
	add r7, #0x20
	ldr r1, [r5, r0]
	sub r0, #0xcc
	add r1, r1, r4
	str r1, [sp]
	str r7, [sp, #4]
	str r6, [sp, #8]
	ldr r1, [sp, #0xc]
	ldr r0, [r5, r0]
	ldrh r1, [r1, #0x12]
	mov r2, #3
	mov r3, #0
	bl FUN_0200B9EC
	ldr r0, _022140F8 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022140F8: .word 0x00002070
_022140FC: .word 0x00001FA4

	thumb_func_start MOD09_02214100
MOD09_02214100: ; 0x02214100
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r0, #0
	mov r0, #0x50
	str r1, [sp, #8]
	mul r0, r2
	add r1, r4, #4
	str r3, [sp, #0xc]
	add r5, r1, r0
	ldrh r0, [r5, #0x10]
	ldrh r1, [r5, #0x12]
	mov r2, #0x30
	mov r7, #1
	bl FUN_02079A0C
	str r0, [sp, #0x14]
	ldrh r0, [r5, #0x10]
	ldrh r1, [r5, #0x12]
	mov r2, #0x30
	bl FUN_02079A54
	cmp r0, #4
	bhi _0221415E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221413A: ; jump table
	.short _02214144 - _0221413A - 2 ; case 0
	.short _0221415C - _0221413A - 2 ; case 1
	.short _02214158 - _0221413A - 2 ; case 2
	.short _02214156 - _0221413A - 2 ; case 3
	.short _02214156 - _0221413A - 2 ; case 4
_02214144:
	ldr r0, _022141D4 ; =0x00002070
	ldr r1, [r4, r0]
	ldr r0, [sp, #8]
	lsl r0, r0, #4
	add r0, r1, r0
	bl ScheduleWindowCopyToVram
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_02214156:
	b _0221415E
_02214158:
	mov r7, #3
	b _0221415E
_0221415C:
	mov r7, #5
_0221415E:
	add r0, sp, #0x20
	ldrb r6, [r0, #0x10]
	add r0, r7, #1
	str r0, [sp, #0x10]
	ldr r0, [sp, #8]
	ldr r1, [sp, #0x10]
	lsl r5, r0, #4
	ldr r0, [sp, #0x14]
	add r3, r6, #1
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _022141D4 ; =0x00002070
	lsl r1, r1, #0x18
	ldr r0, [r4, r0]
	lsl r3, r3, #0x10
	ldr r2, [sp, #0xc]
	add r0, r0, r5
	lsr r1, r1, #0x18
	lsr r3, r3, #0x10
	bl FillWindowPixelRect
	ldr r0, [sp, #0x14]
	add r3, r6, #2
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _022141D4 ; =0x00002070
	lsl r3, r3, #0x10
	ldr r0, [r4, r0]
	ldr r2, [sp, #0xc]
	add r0, r0, r5
	add r1, r7, #0
	lsr r3, r3, #0x10
	bl FillWindowPixelRect
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x10]
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _022141D4 ; =0x00002070
	add r3, r6, #4
	ldr r0, [r4, r0]
	lsl r1, r1, #0x18
	lsl r3, r3, #0x10
	ldr r2, [sp, #0xc]
	add r0, r0, r5
	lsr r1, r1, #0x18
	lsr r3, r3, #0x10
	bl FillWindowPixelRect
	ldr r0, _022141D4 ; =0x00002070
	ldr r0, [r4, r0]
	add r0, r0, r5
	bl ScheduleWindowCopyToVram
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022141D4: .word 0x00002070

	thumb_func_start MOD09_022141D8
MOD09_022141D8: ; 0x022141D8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, [r5]
	mov r0, #0x10
	ldr r1, [r1, #0xc]
	add r7, r2, #0
	bl String_ctor
	add r6, r0, #0
	ldr r0, _02214250 ; =0x00001FA8
	mov r1, #8
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	mov r2, #0x50
	mul r2, r7
	str r0, [sp, #0x10]
	ldr r0, _02214254 ; =0x00001FAC
	add r2, r5, r2
	ldrh r2, [r2, #0x1c]
	ldr r0, [r5, r0]
	mov r1, #0
	bl BufferAbilityName
	ldr r0, _02214254 ; =0x00001FAC
	ldr r2, [sp, #0x10]
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl StringExpandPlaceholders
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214258 ; =0x000F0E00
	lsl r4, r4, #4
	str r0, [sp, #8]
	ldr r0, _0221425C ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	add r2, r6, #0
	add r0, r0, r4
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	ldr r0, _0221425C ; =0x00002070
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02214250: .word 0x00001FA8
_02214254: .word 0x00001FAC
_02214258: .word 0x000F0E00
_0221425C: .word 0x00002070

	thumb_func_start MOD09_02214260
MOD09_02214260: ; 0x02214260
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0x50
	add r7, r1, #0
	add r1, r4, #4
	mul r0, r2
	add r5, r1, r0
	ldrh r0, [r5, #0x1a]
	cmp r0, #0
	bne _02214284
	ldr r0, _022142EC ; =0x00001FA8
	mov r1, #0x14
	ldr r0, [r4, r0]
	bl NewString_ReadMsgData
	add r6, r0, #0
	b _022142BA
_02214284:
	ldr r1, [r4]
	mov r0, #0x12
	ldr r1, [r1, #0xc]
	bl String_ctor
	add r6, r0, #0
	ldr r0, _022142EC ; =0x00001FA8
	mov r1, #9
	ldr r0, [r4, r0]
	bl NewString_ReadMsgData
	str r0, [sp, #0x10]
	ldr r0, _022142F0 ; =0x00001FAC
	ldrh r2, [r5, #0x1a]
	ldr r0, [r4, r0]
	mov r1, #0
	bl BufferItemName
	ldr r0, _022142F0 ; =0x00001FAC
	ldr r2, [sp, #0x10]
	ldr r0, [r4, r0]
	add r1, r6, #0
	bl StringExpandPlaceholders
	ldr r0, [sp, #0x10]
	bl String_dtor
_022142BA:
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022142F4 ; =0x000F0E00
	lsl r5, r7, #4
	str r0, [sp, #8]
	ldr r0, _022142F8 ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r4, r0]
	add r2, r6, #0
	add r0, r0, r5
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	ldr r0, _022142F8 ; =0x00002070
	ldr r0, [r4, r0]
	add r0, r0, r5
	bl ScheduleWindowCopyToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022142EC: .word 0x00001FA8
_022142F0: .word 0x00001FAC
_022142F4: .word 0x000F0E00
_022142F8: .word 0x00002070

	thumb_func_start MOD09_022142FC
MOD09_022142FC: ; 0x022142FC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	str r1, [sp, #0x10]
	ldr r1, [r5]
	ldr r0, _02214394 ; =0x00002070
	ldr r1, [r1, #0xc]
	ldr r4, [r5, r0]
	mov r0, #0x10
	str r3, [sp, #0x14]
	lsl r6, r2, #4
	bl String_ctor
	add r7, r0, #0
	ldr r0, _02214398 ; =0x00001FA8
	ldr r1, [sp, #0x14]
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	str r0, [sp, #0x18]
	ldr r0, _0221439C ; =0x00001FAC
	ldr r2, [sp, #0x10]
	ldr r0, [r5, r0]
	mov r1, #0
	bl BufferMoveName
	ldr r0, _0221439C ; =0x00001FAC
	ldr r2, [sp, #0x18]
	ldr r0, [r5, r0]
	add r1, r7, #0
	bl StringExpandPlaceholders
	add r0, sp, #0x20
	ldrh r0, [r0, #0x10]
	cmp r0, #2
	bne _02214360
	add r0, r4, r6
	bl GetWindowWidth
	add r5, r0, #0
	add r0, sp, #0x20
	ldrh r0, [r0, #0x10]
	add r1, r7, #0
	mov r2, #0
	bl FUN_02002E14
	lsl r1, r5, #3
	sub r0, r1, r0
	lsr r3, r0, #1
	b _02214362
_02214360:
	mov r3, #0
_02214362:
	add r1, sp, #0x20
	ldrh r0, [r1, #0x14]
	add r2, r7, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x38]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldrh r1, [r1, #0x10]
	add r0, r4, r6
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x18]
	bl String_dtor
	add r0, r7, #0
	bl String_dtor
	add r0, r4, r6
	bl ScheduleWindowCopyToVram
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02214394: .word 0x00002070
_02214398: .word 0x00001FA8
_0221439C: .word 0x00001FAC

	thumb_func_start MOD09_022143A0
MOD09_022143A0: ; 0x022143A0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r0, _022143EC ; =0x00001FA8
	str r2, [sp, #0x10]
	add r5, r1, #0
	ldr r0, [r4, r0]
	add r6, r3, #0
	mov r1, #0xe
	bl NewString_ReadMsgData
	add r7, r0, #0
	str r6, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022143F0 ; =0x000F0E00
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, _022143F4 ; =0x00002070
	lsl r5, r5, #4
	ldr r0, [r4, r0]
	ldr r3, [sp, #0x10]
	add r0, r0, r5
	add r2, r7, #0
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
	ldr r0, _022143F4 ; =0x00002070
	ldr r0, [r4, r0]
	add r0, r0, r5
	bl ScheduleWindowCopyToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_022143EC: .word 0x00001FA8
_022143F0: .word 0x000F0E00
_022143F4: .word 0x00002070

	thumb_func_start MOD09_022143F8
MOD09_022143F8: ; 0x022143F8
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, _02214450 ; =0x00002050
	add r5, r1, #0
	mov r1, #1
	add r0, r4, r0
	add r2, r1, #0
	mov r3, #0xe
	bl FUN_0200D0BC
	ldr r0, _02214450 ; =0x00002050
	mov r1, #0xf
	add r0, r4, r0
	bl FillWindowPixelBuffer
	ldr r0, _02214454 ; =0x00001FA8
	add r1, r5, #0
	ldr r0, [r4, r0]
	bl NewString_ReadMsgData
	add r5, r0, #0
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214458 ; =0x00010200
	mov r1, #1
	str r0, [sp, #8]
	ldr r0, _02214450 ; =0x00002050
	add r2, r5, #0
	add r0, r4, r0
	str r3, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r5, #0
	bl String_dtor
	ldr r0, _02214450 ; =0x00002050
	add r0, r4, r0
	bl ScheduleWindowCopyToVram
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_02214450: .word 0x00002050
_02214454: .word 0x00001FA8
_02214458: .word 0x00010200

	thumb_func_start MOD09_0221445C
MOD09_0221445C: ; 0x0221445C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r3, _022144B8 ; =0x00002070
	lsl r4, r1, #4
	ldr r5, [r0, r3]
	sub r3, #0xc8
	ldr r0, [r0, r3]
	add r1, r2, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	mov r0, #2
	add r1, r7, #0
	mov r2, #0
	bl FUN_02002E14
	add r6, r0, #0
	add r0, r5, r4
	bl GetWindowWidth
	add r3, r0, #0
	mov r0, #6
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022144BC ; =0x00070809
	lsl r3, r3, #3
	str r0, [sp, #8]
	mov r0, #0
	sub r3, r3, r6
	str r0, [sp, #0xc]
	add r0, r5, r4
	mov r1, #2
	add r2, r7, #0
	lsr r3, r3, #1
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
	add r0, r5, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022144B8: .word 0x00002070
_022144BC: .word 0x00070809

	thumb_func_start MOD09_022144C0
MOD09_022144C0: ; 0x022144C0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	mov r0, #0x50
	mul r0, r1
	add r2, r5, #4
	add r4, r2, r0
	ldr r1, _0221467C ; =0x00002075
	mov r0, #0x16
	ldrb r2, [r5, r1]
	sub r1, #0xcd
	mul r0, r2
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r0, [r5, r1]
	mov r1, #0x17
	bl NewString_ReadMsgData
	mov r1, #0
	add r7, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r2, _02214680 ; =0x000F0E00
	add r0, #0x31
	str r2, [sp, #8]
	ldr r2, _02214684 ; =0x00002070
	str r1, [sp, #0xc]
	ldr r2, [r5, r2]
	add r3, r1, #0
	add r0, r2, r0
	add r2, r7, #0
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
	ldr r0, _02214688 ; =0x00001FA8
	mov r1, #0x18
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	ldr r1, [r5]
	str r0, [sp, #0x18]
	ldr r1, [r1, #0xc]
	mov r0, #8
	bl String_ctor
	mov r1, #0
	str r0, [sp, #0x1c]
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldrb r2, [r4, #0x16]
	ldr r0, _0221468C ; =0x00001FAC
	mov r3, #3
	lsl r2, r2, #0x19
	ldr r0, [r5, r0]
	lsr r2, r2, #0x19
	bl BufferIntegerAsString
	ldr r0, _0221468C ; =0x00001FAC
	ldr r1, [sp, #0x1c]
	ldr r0, [r5, r0]
	ldr r2, [sp, #0x18]
	bl StringExpandPlaceholders
	mov r1, #0
	add r0, r6, #0
	add r0, #0xb
	lsl r7, r0, #4
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214680 ; =0x000F0E00
	ldr r2, [sp, #0x1c]
	str r0, [sp, #8]
	ldr r0, _02214684 ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	add r3, r1, #0
	add r0, r0, r7
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x18]
	bl String_dtor
	ldr r0, [sp, #0x1c]
	bl String_dtor
	ldr r0, _02214688 ; =0x00001FA8
	mov r1, #0x19
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	mov r1, #0
	str r0, [sp, #0x20]
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r2, _02214680 ; =0x000F0E00
	add r0, #0x41
	str r2, [sp, #8]
	ldr r2, _02214684 ; =0x00002070
	str r1, [sp, #0xc]
	ldr r2, [r5, r2]
	add r3, r1, #0
	add r0, r2, r0
	ldr r2, [sp, #0x20]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x20]
	bl String_dtor
	ldr r0, _02214688 ; =0x00001FA8
	mov r1, #0x1a
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	ldr r1, [r5]
	str r0, [sp, #0x14]
	ldr r1, [r1, #0xc]
	mov r0, #0xe
	bl String_ctor
	str r0, [sp, #0x10]
	ldrb r0, [r4, #0x16]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x19
	cmp r0, #0x64
	bhs _022145E0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221468C ; =0x00001FAC
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x1c]
	ldr r0, [r5, r0]
	sub r2, r2, r3
	mov r1, #0
	mov r3, #6
	bl BufferIntegerAsString
	b _022145F4
_022145E0:
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221468C ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	add r2, r1, #0
	mov r3, #6
	bl BufferIntegerAsString
_022145F4:
	ldr r0, _0221468C ; =0x00001FAC
	ldr r1, [sp, #0x10]
	ldr r0, [r5, r0]
	ldr r2, [sp, #0x14]
	bl StringExpandPlaceholders
	ldr r0, _02214684 ; =0x00002070
	add r6, #0xc
	ldr r0, [r5, r0]
	lsl r4, r6, #4
	add r0, r0, r4
	bl GetWindowWidth
	add r6, r0, #0
	mov r0, #0
	ldr r1, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02002E14
	lsl r1, r6, #3
	sub r0, r1, r0
	lsl r0, r0, #0x10
	mov r1, #0
	lsr r3, r0, #0x10
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214690 ; =0x00010200
	ldr r2, [sp, #0x10]
	str r0, [sp, #8]
	ldr r0, _02214684 ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x14]
	bl String_dtor
	ldr r0, [sp, #0x10]
	bl String_dtor
	ldr r0, _02214684 ; =0x00002070
	ldr r1, [r5, r0]
	mov r0, #0x13
	lsl r0, r0, #4
	add r0, r1, r0
	bl ScheduleWindowCopyToVram
	ldr r0, _02214684 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, r0, r7
	bl ScheduleWindowCopyToVram
	ldr r0, _02214684 ; =0x00002070
	ldr r1, [r5, r0]
	mov r0, #5
	lsl r0, r0, #6
	add r0, r1, r0
	bl ScheduleWindowCopyToVram
	ldr r0, _02214684 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0221467C: .word 0x00002075
_02214680: .word 0x000F0E00
_02214684: .word 0x00002070
_02214688: .word 0x00001FA8
_0221468C: .word 0x00001FAC
_02214690: .word 0x00010200

	thumb_func_start MOD09_02214694
MOD09_02214694: ; 0x02214694
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r1, #0
	add r5, r0, #0
	ldr r1, _02214778 ; =0x00002075
	mov r0, #0x16
	ldrb r2, [r5, r1]
	sub r1, #0xcd
	mul r0, r2
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [r5, r1]
	mov r1, #0x20
	bl NewString_ReadMsgData
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0221477C ; =0x000F0E00
	add r2, r6, #0
	str r0, [sp, #8]
	ldr r0, _02214780 ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	add r3, r1, #0
	add r0, #0xe0
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	ldr r0, _02214784 ; =0x00001FA8
	mov r1, #0x21
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	ldr r1, [r5]
	str r0, [sp, #0x10]
	ldr r1, [r1, #0xc]
	mov r0, #8
	bl String_ctor
	mov r1, #0
	mov r2, #0x50
	add r6, r0, #0
	mul r2, r7
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _02214788 ; =0x00001FAC
	add r2, r5, r2
	ldrh r2, [r2, #0xa]
	ldr r0, [r5, r0]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, _02214788 ; =0x00001FAC
	ldr r2, [sp, #0x10]
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r6, #0
	add r2, r0, #0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	add r0, r4, #5
	lsl r4, r0, #4
	ldr r0, _02214780 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r0, r0, r7
	lsl r0, r0, #0x18
	mov r1, #0
	lsr r3, r0, #0x18
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0221478C ; =0x00010200
	add r2, r6, #0
	str r0, [sp, #8]
	ldr r0, _02214780 ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	ldr r0, _02214780 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, #0xe0
	bl ScheduleWindowCopyToVram
	ldr r0, _02214780 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_02214778: .word 0x00002075
_0221477C: .word 0x000F0E00
_02214780: .word 0x00002070
_02214784: .word 0x00001FA8
_02214788: .word 0x00001FAC
_0221478C: .word 0x00010200

	thumb_func_start MOD09_02214790
MOD09_02214790: ; 0x02214790
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r1, #0
	add r5, r0, #0
	ldr r1, _02214874 ; =0x00002075
	mov r0, #0x16
	ldrb r2, [r5, r1]
	sub r1, #0xcd
	mul r0, r2
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [r5, r1]
	mov r1, #0x22
	bl NewString_ReadMsgData
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214878 ; =0x000F0E00
	add r2, r6, #0
	str r0, [sp, #8]
	ldr r0, _0221487C ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	add r3, r1, #0
	add r0, #0xf0
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	ldr r0, _02214880 ; =0x00001FA8
	mov r1, #0x23
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	ldr r1, [r5]
	str r0, [sp, #0x10]
	ldr r1, [r1, #0xc]
	mov r0, #8
	bl String_ctor
	mov r1, #0
	mov r2, #0x50
	add r6, r0, #0
	mul r2, r7
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _02214884 ; =0x00001FAC
	add r2, r5, r2
	ldrh r2, [r2, #0xc]
	ldr r0, [r5, r0]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, _02214884 ; =0x00001FAC
	ldr r2, [sp, #0x10]
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r6, #0
	add r2, r0, #0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	add r0, r4, #6
	lsl r4, r0, #4
	ldr r0, _0221487C ; =0x00002070
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r0, r0, r7
	lsl r0, r0, #0x18
	mov r1, #0
	lsr r3, r0, #0x18
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214888 ; =0x00010200
	add r2, r6, #0
	str r0, [sp, #8]
	ldr r0, _0221487C ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	ldr r0, _0221487C ; =0x00002070
	ldr r0, [r5, r0]
	add r0, #0xf0
	bl ScheduleWindowCopyToVram
	ldr r0, _0221487C ; =0x00002070
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_02214874: .word 0x00002075
_02214878: .word 0x000F0E00
_0221487C: .word 0x00002070
_02214880: .word 0x00001FA8
_02214884: .word 0x00001FAC
_02214888: .word 0x00010200

	thumb_func_start MOD09_0221488C
MOD09_0221488C: ; 0x0221488C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r1, #0
	add r5, r0, #0
	ldr r1, _02214974 ; =0x00002075
	mov r0, #0x16
	ldrb r2, [r5, r1]
	sub r1, #0xcd
	mul r0, r2
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [r5, r1]
	mov r1, #0x28
	bl NewString_ReadMsgData
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	ldr r0, _02214978 ; =0x000F0E00
	add r2, r2, #1
	str r0, [sp, #8]
	ldr r0, _0221497C ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	add r3, r1, #0
	add r0, r0, r2
	add r2, r6, #0
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	ldr r0, _02214980 ; =0x00001FA8
	mov r1, #0x29
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	ldr r1, [r5]
	str r0, [sp, #0x10]
	ldr r1, [r1, #0xc]
	mov r0, #8
	bl String_ctor
	mov r1, #0
	mov r2, #0x50
	add r6, r0, #0
	mul r2, r7
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _02214984 ; =0x00001FAC
	add r2, r5, r2
	ldrh r2, [r2, #0xe]
	ldr r0, [r5, r0]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, _02214984 ; =0x00001FAC
	ldr r2, [sp, #0x10]
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r6, #0
	add r2, r0, #0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	add r0, r4, #7
	lsl r4, r0, #4
	ldr r0, _0221497C ; =0x00002070
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r0, r0, r7
	lsl r0, r0, #0x18
	mov r1, #0
	lsr r3, r0, #0x18
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214988 ; =0x00010200
	add r2, r6, #0
	str r0, [sp, #8]
	ldr r0, _0221497C ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	ldr r0, _0221497C ; =0x00002070
	ldr r1, [r5, r0]
	mov r0, #1
	lsl r0, r0, #8
	add r0, r1, r0
	bl ScheduleWindowCopyToVram
	ldr r0, _0221497C ; =0x00002070
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02214974: .word 0x00002075
_02214978: .word 0x000F0E00
_0221497C: .word 0x00002070
_02214980: .word 0x00001FA8
_02214984: .word 0x00001FAC
_02214988: .word 0x00010200

	thumb_func_start MOD09_0221498C
MOD09_0221498C: ; 0x0221498C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r1, #0
	add r4, r0, #0
	ldr r1, _02214A74 ; =0x00002075
	mov r0, #0x16
	ldrb r2, [r4, r1]
	sub r1, #0xcd
	mul r0, r2
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	ldr r0, [r4, r1]
	mov r1, #0x24
	bl NewString_ReadMsgData
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r2, _02214A78 ; =0x000F0E00
	add r0, #0x11
	str r2, [sp, #8]
	ldr r2, _02214A7C ; =0x00002070
	str r1, [sp, #0xc]
	ldr r2, [r4, r2]
	add r3, r1, #0
	add r0, r2, r0
	add r2, r6, #0
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	ldr r0, _02214A80 ; =0x00001FA8
	mov r1, #0x25
	ldr r0, [r4, r0]
	bl NewString_ReadMsgData
	ldr r1, [r4]
	str r0, [sp, #0x10]
	ldr r1, [r1, #0xc]
	mov r0, #8
	bl String_ctor
	mov r1, #0
	mov r2, #0x50
	add r6, r0, #0
	mul r2, r7
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _02214A84 ; =0x00001FAC
	add r2, r4, r2
	ldrh r2, [r2, #0x10]
	ldr r0, [r4, r0]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, _02214A84 ; =0x00001FAC
	ldr r2, [sp, #0x10]
	ldr r0, [r4, r0]
	add r1, r6, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r6, #0
	add r2, r0, #0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	ldr r0, _02214A7C ; =0x00002070
	add r5, #8
	ldr r0, [r4, r0]
	lsl r5, r5, #4
	add r0, r0, r5
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r0, r0, r7
	lsl r0, r0, #0x18
	mov r1, #0
	lsr r3, r0, #0x18
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214A88 ; =0x00010200
	add r2, r6, #0
	str r0, [sp, #8]
	ldr r0, _02214A7C ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r4, r0]
	add r0, r0, r5
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	ldr r0, _02214A7C ; =0x00002070
	ldr r1, [r4, r0]
	mov r0, #0x11
	lsl r0, r0, #4
	add r0, r1, r0
	bl ScheduleWindowCopyToVram
	ldr r0, _02214A7C ; =0x00002070
	ldr r0, [r4, r0]
	add r0, r0, r5
	bl ScheduleWindowCopyToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02214A74: .word 0x00002075
_02214A78: .word 0x000F0E00
_02214A7C: .word 0x00002070
_02214A80: .word 0x00001FA8
_02214A84: .word 0x00001FAC
_02214A88: .word 0x00010200

	thumb_func_start MOD09_02214A8C
MOD09_02214A8C: ; 0x02214A8C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r1, #0
	add r4, r0, #0
	ldr r1, _02214B74 ; =0x00002075
	mov r0, #0x16
	ldrb r2, [r4, r1]
	sub r1, #0xcd
	mul r0, r2
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	ldr r0, [r4, r1]
	mov r1, #0x26
	bl NewString_ReadMsgData
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r2, _02214B78 ; =0x000F0E00
	add r0, #0x21
	str r2, [sp, #8]
	ldr r2, _02214B7C ; =0x00002070
	str r1, [sp, #0xc]
	ldr r2, [r4, r2]
	add r3, r1, #0
	add r0, r2, r0
	add r2, r6, #0
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	ldr r0, _02214B80 ; =0x00001FA8
	mov r1, #0x27
	ldr r0, [r4, r0]
	bl NewString_ReadMsgData
	ldr r1, [r4]
	str r0, [sp, #0x10]
	ldr r1, [r1, #0xc]
	mov r0, #8
	bl String_ctor
	mov r1, #0
	mov r2, #0x50
	add r6, r0, #0
	mul r2, r7
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _02214B84 ; =0x00001FAC
	add r2, r4, r2
	ldrh r2, [r2, #0x12]
	ldr r0, [r4, r0]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, _02214B84 ; =0x00001FAC
	ldr r2, [sp, #0x10]
	ldr r0, [r4, r0]
	add r1, r6, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r6, #0
	add r2, r0, #0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	ldr r0, _02214B7C ; =0x00002070
	add r5, #9
	ldr r0, [r4, r0]
	lsl r5, r5, #4
	add r0, r0, r5
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r0, r0, r7
	lsl r0, r0, #0x18
	mov r1, #0
	lsr r3, r0, #0x18
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214B88 ; =0x00010200
	add r2, r6, #0
	str r0, [sp, #8]
	ldr r0, _02214B7C ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r4, r0]
	add r0, r0, r5
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	ldr r0, _02214B7C ; =0x00002070
	ldr r1, [r4, r0]
	mov r0, #0x12
	lsl r0, r0, #4
	add r0, r1, r0
	bl ScheduleWindowCopyToVram
	ldr r0, _02214B7C ; =0x00002070
	ldr r0, [r4, r0]
	add r0, r0, r5
	bl ScheduleWindowCopyToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02214B74: .word 0x00002075
_02214B78: .word 0x000F0E00
_02214B7C: .word 0x00002070
_02214B80: .word 0x00001FA8
_02214B84: .word 0x00001FAC
_02214B88: .word 0x00010200

	thumb_func_start MOD09_02214B8C
MOD09_02214B8C: ; 0x02214B8C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	mov r0, #0x50
	mul r0, r1
	add r2, r5, #4
	add r7, r2, r0
	ldr r1, _02214D0C ; =0x00002075
	mov r0, #0x16
	ldrb r2, [r5, r1]
	sub r1, #0xcd
	mul r0, r2
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [r5, r1]
	mov r1, #0x1c
	bl NewString_ReadMsgData
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214D10 ; =0x000F0E00
	add r2, r6, #0
	str r0, [sp, #8]
	ldr r0, _02214D14 ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	add r3, r1, #0
	add r0, #0xd0
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	ldr r0, _02214D18 ; =0x00001FA8
	mov r1, #0x1f
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	str r0, [sp, #0x10]
	mov r0, #0
	ldr r1, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02002E14
	str r0, [sp, #0x14]
	ldr r0, _02214D14 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, #0x40
	bl GetWindowWidth
	lsl r1, r0, #3
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x10]
	sub r0, r1, r0
	lsl r0, r0, #0xf
	lsr r6, r0, #0x10
	add r0, r4, #4
	mov r1, #0
	lsl r4, r0, #4
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214D1C ; =0x00010200
	add r3, r6, #0
	str r0, [sp, #8]
	ldr r0, _02214D14 ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	bl String_dtor
	ldr r0, _02214D18 ; =0x00001FA8
	mov r1, #0x1d
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	ldr r1, [r5]
	str r0, [sp, #0x18]
	ldr r1, [r1, #0xc]
	mov r0, #8
	bl String_ctor
	str r0, [sp, #0x1c]
	mov r1, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _02214D20 ; =0x00001FAC
	ldrh r2, [r7, #0x10]
	ldr r0, [r5, r0]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, _02214D20 ; =0x00001FAC
	ldr r1, [sp, #0x1c]
	ldr r0, [r5, r0]
	ldr r2, [sp, #0x18]
	bl StringExpandPlaceholders
	mov r0, #0
	ldr r1, [sp, #0x1c]
	add r2, r0, #0
	bl FUN_02002E14
	add r3, r0, #0
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214D1C ; =0x00010200
	ldr r2, [sp, #0x1c]
	str r0, [sp, #8]
	ldr r0, _02214D14 ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	sub r3, r6, r3
	add r0, r0, r4
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x18]
	bl String_dtor
	ldr r0, [sp, #0x1c]
	bl String_dtor
	ldr r0, _02214D18 ; =0x00001FA8
	mov r1, #0x1e
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	ldr r1, [r5]
	str r0, [sp, #0x20]
	ldr r1, [r1, #0xc]
	mov r0, #8
	bl String_ctor
	mov r1, #0
	str r0, [sp, #0x24]
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _02214D20 ; =0x00001FAC
	ldrh r2, [r7, #0x12]
	ldr r0, [r5, r0]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, _02214D20 ; =0x00001FAC
	ldr r1, [sp, #0x24]
	ldr r0, [r5, r0]
	ldr r2, [sp, #0x20]
	bl StringExpandPlaceholders
	mov r1, #0
	ldr r3, [sp, #0x14]
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214D1C ; =0x00010200
	ldr r2, [sp, #0x24]
	str r0, [sp, #8]
	ldr r0, _02214D14 ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	add r3, r6, r3
	add r0, r0, r4
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x20]
	bl String_dtor
	ldr r0, [sp, #0x24]
	bl String_dtor
	ldr r0, _02214D14 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, #0xd0
	bl ScheduleWindowCopyToVram
	ldr r0, _02214D14 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02214D0C: .word 0x00002075
_02214D10: .word 0x000F0E00
_02214D14: .word 0x00002070
_02214D18: .word 0x00001FA8
_02214D1C: .word 0x00010200
_02214D20: .word 0x00001FAC

	thumb_func_start MOD09_02214D24
MOD09_02214D24: ; 0x02214D24
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, _02214D90 ; =0x00002075
	add r6, r1, #0
	ldrb r1, [r5, r0]
	ldr r3, [r5]
	mov r0, #0x16
	add r4, r1, #0
	mul r4, r0
	ldr r2, _02214D94 ; =0x0000022A
	ldr r3, [r3, #0xc]
	mov r0, #1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	mov r1, #0x50
	mul r1, r6
	add r1, r5, r1
	ldrh r1, [r1, #0x1c]
	add r7, r0, #0
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r1, #0
	add r0, r4, #2
	lsl r4, r0, #4
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214D98 ; =0x00010200
	add r2, r6, #0
	str r0, [sp, #8]
	ldr r0, _02214D9C ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	add r3, r1, #0
	add r0, r0, r4
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	add r0, r7, #0
	bl DestroyMsgData
	ldr r0, _02214D9C ; =0x00002070
	ldr r0, [r5, r0]
	add r0, r0, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02214D90: .word 0x00002075
_02214D94: .word 0x0000022A
_02214D98: .word 0x00010200
_02214D9C: .word 0x00002070

	thumb_func_start MOD09_02214DA0
MOD09_02214DA0: ; 0x02214DA0
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r2, _02214DE0 ; =0x00002070
	lsl r4, r1, #4
	ldr r5, [r0, r2]
	sub r2, #0xc8
	ldr r0, [r0, r2]
	mov r1, #0x33
	bl NewString_ReadMsgData
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214DE4 ; =0x000F0E00
	add r2, r6, #0
	str r0, [sp, #8]
	add r0, r5, r4
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	add r0, r5, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_02214DE0: .word 0x00002070
_02214DE4: .word 0x000F0E00

	thumb_func_start MOD09_02214DE8
MOD09_02214DE8: ; 0x02214DE8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r2, [sp, #0x10]
	add r5, r0, #0
	ldr r2, _02214EC4 ; =0x00002070
	ldr r0, [sp, #0x10]
	lsl r6, r1, #4
	ldr r4, [r5, r2]
	cmp r0, #0
	bne _02214E42
	sub r2, #0xc8
	ldr r0, [r5, r2]
	mov r1, #0x32
	bl NewString_ReadMsgData
	add r7, r0, #0
	mov r0, #0
	add r1, r7, #0
	add r2, r0, #0
	bl FUN_02002E14
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r4, r6
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r0, r0, r5
	lsl r0, r0, #0x10
	mov r1, #0
	lsr r3, r0, #0x10
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214EC8 ; =0x00010200
	add r2, r7, #0
	str r0, [sp, #8]
	add r0, r4, r6
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
	b _02214EB8
_02214E42:
	sub r2, #0xc8
	ldr r0, [r5, r2]
	mov r1, #0x34
	bl NewString_ReadMsgData
	ldr r1, [r5]
	str r0, [sp, #0x14]
	ldr r1, [r1, #0xc]
	mov r0, #8
	bl String_ctor
	mov r1, #0
	add r7, r0, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _02214ECC ; =0x00001FAC
	ldr r2, [sp, #0x10]
	ldr r0, [r5, r0]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, _02214ECC ; =0x00001FAC
	ldr r2, [sp, #0x14]
	ldr r0, [r5, r0]
	add r1, r7, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r7, #0
	add r2, r0, #0
	bl FUN_02002E14
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r4, r6
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r0, r0, r5
	lsl r0, r0, #0x10
	mov r1, #0
	lsr r3, r0, #0x10
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214EC8 ; =0x00010200
	add r2, r7, #0
	str r0, [sp, #8]
	add r0, r4, r6
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x14]
	bl String_dtor
	add r0, r7, #0
	bl String_dtor
_02214EB8:
	add r0, r4, r6
	bl ScheduleWindowCopyToVram
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02214EC4: .word 0x00002070
_02214EC8: .word 0x00010200
_02214ECC: .word 0x00001FAC

	thumb_func_start MOD09_02214ED0
MOD09_02214ED0: ; 0x02214ED0
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r2, _02214F10 ; =0x00002070
	lsl r4, r1, #4
	ldr r5, [r0, r2]
	sub r2, #0xc8
	ldr r0, [r0, r2]
	mov r1, #0x30
	bl NewString_ReadMsgData
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214F14 ; =0x000F0E00
	add r2, r6, #0
	str r0, [sp, #8]
	add r0, r5, r4
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	add r0, r5, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_02214F10: .word 0x00002070
_02214F14: .word 0x000F0E00

	thumb_func_start MOD09_02214F18
MOD09_02214F18: ; 0x02214F18
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r2, [sp, #0x10]
	add r5, r0, #0
	ldr r2, _02214FF4 ; =0x00002070
	ldr r0, [sp, #0x10]
	lsl r6, r1, #4
	ldr r4, [r5, r2]
	cmp r0, #1
	bhi _02214F72
	sub r2, #0xc8
	ldr r0, [r5, r2]
	mov r1, #0x32
	bl NewString_ReadMsgData
	add r7, r0, #0
	mov r0, #0
	add r1, r7, #0
	add r2, r0, #0
	bl FUN_02002E14
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r4, r6
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r0, r0, r5
	lsl r0, r0, #0x10
	mov r1, #0
	lsr r3, r0, #0x10
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214FF8 ; =0x00010200
	add r2, r7, #0
	str r0, [sp, #8]
	add r0, r4, r6
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
	b _02214FE8
_02214F72:
	sub r2, #0xc8
	ldr r0, [r5, r2]
	mov r1, #0x31
	bl NewString_ReadMsgData
	ldr r1, [r5]
	str r0, [sp, #0x14]
	ldr r1, [r1, #0xc]
	mov r0, #8
	bl String_ctor
	mov r1, #0
	add r7, r0, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _02214FFC ; =0x00001FAC
	ldr r2, [sp, #0x10]
	ldr r0, [r5, r0]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, _02214FFC ; =0x00001FAC
	ldr r2, [sp, #0x14]
	ldr r0, [r5, r0]
	add r1, r7, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r7, #0
	add r2, r0, #0
	bl FUN_02002E14
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r4, r6
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r0, r0, r5
	lsl r0, r0, #0x10
	mov r1, #0
	lsr r3, r0, #0x10
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214FF8 ; =0x00010200
	add r2, r7, #0
	str r0, [sp, #8]
	add r0, r4, r6
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x14]
	bl String_dtor
	add r0, r7, #0
	bl String_dtor
_02214FE8:
	add r0, r4, r6
	bl ScheduleWindowCopyToVram
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02214FF4: .word 0x00002070
_02214FF8: .word 0x00010200
_02214FFC: .word 0x00001FAC

	thumb_func_start MOD09_02215000
MOD09_02215000: ; 0x02215000
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r3, r0, #0
	ldr r0, _02215054 ; =0x00002070
	add r6, r2, #0
	ldr r5, [r3, r0]
	ldr r3, [r3]
	lsl r4, r1, #4
	ldr r2, _02215058 ; =0x0000024B
	ldr r3, [r3, #0xc]
	mov r0, #1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r1, r6, #0
	add r7, r0, #0
	bl NewString_ReadMsgData
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0221505C ; =0x00010200
	add r2, r6, #0
	str r0, [sp, #8]
	add r0, r5, r4
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	add r0, r7, #0
	bl DestroyMsgData
	add r0, r5, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02215054: .word 0x00002070
_02215058: .word 0x0000024B
_0221505C: .word 0x00010200

	thumb_func_start MOD09_02215060
MOD09_02215060: ; 0x02215060
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	ldr r0, _022150C0 ; =0x00002070
	lsl r4, r1, #4
	ldr r5, [r6, r0]
	add r0, r2, #0
	mov r1, #0xa
	bl GetWazaAttr
	bl FUN_0208315C
	ldr r3, [r6]
	add r7, r0, #0
	ldr r3, [r3, #0xc]
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0xc5
	bl NewMsgDataFromNarc
	add r1, r7, #0
	str r0, [sp, #0x10]
	bl NewString_ReadMsgData
	mov r1, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022150C4 ; =0x00010200
	add r2, r6, #0
	str r0, [sp, #8]
	add r0, r5, r4
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	ldr r0, [sp, #0x10]
	bl DestroyMsgData
	add r0, r5, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022150C0: .word 0x00002070
_022150C4: .word 0x00010200

	thumb_func_start MOD09_022150C8
MOD09_022150C8: ; 0x022150C8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r2, _02215124 ; =0x00002070
	lsl r4, r1, #4
	ldr r5, [r0, r2]
	sub r2, #0xc8
	ldr r0, [r0, r2]
	mov r1, #0x35
	bl NewString_ReadMsgData
	add r7, r0, #0
	mov r0, #0
	add r1, r7, #0
	add r2, r0, #0
	bl FUN_02002E14
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r5, r4
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r1, r0, r6
	lsr r0, r1, #0x1f
	add r0, r1, r0
	lsl r0, r0, #0xf
	mov r1, #0
	lsr r3, r0, #0x10
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02215128 ; =0x000F0E00
	add r2, r7, #0
	str r0, [sp, #8]
	add r0, r5, r4
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
	add r0, r5, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02215124: .word 0x00002070
_02215128: .word 0x000F0E00

	thumb_func_start MOD09_0221512C
MOD09_0221512C: ; 0x0221512C
	push {r4, r5, r6, lr}
	sub sp, #0x10
	ldr r3, _022151A0 ; =0x00002070
	lsl r4, r1, #4
	ldr r5, [r0, r3]
	cmp r2, #0
	beq _02215144
	cmp r2, #1
	beq _02215152
	cmp r2, #2
	beq _02215160
	b _0221516C
_02215144:
	sub r3, #0xc8
	ldr r0, [r0, r3]
	mov r1, #0x36
	bl NewString_ReadMsgData
	add r6, r0, #0
	b _0221516C
_02215152:
	sub r3, #0xc8
	ldr r0, [r0, r3]
	mov r1, #0x38
	bl NewString_ReadMsgData
	add r6, r0, #0
	b _0221516C
_02215160:
	sub r3, #0xc8
	ldr r0, [r0, r3]
	mov r1, #0x37
	bl NewString_ReadMsgData
	add r6, r0, #0
_0221516C:
	mov r0, #0
	add r1, r6, #0
	add r2, r0, #0
	mov r3, #0x38
	bl FUN_02002F40
	mov r1, #0
	add r3, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022151A4 ; =0x00010200
	add r2, r6, #0
	str r0, [sp, #8]
	add r0, r5, r4
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	add r0, r5, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_022151A0: .word 0x00002070
_022151A4: .word 0x00010200

	thumb_func_start MOD09_022151A8
MOD09_022151A8: ; 0x022151A8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r5, r0, #0
	ldr r0, _022152CC ; =0x00002070
	lsl r6, r1, #4
	ldr r4, [r5, r0]
	sub r0, #0xc8
	ldr r0, [r5, r0]
	mov r1, #0x2e
	str r2, [sp, #0x10]
	str r3, [sp, #0x14]
	bl NewString_ReadMsgData
	str r0, [sp, #0x18]
	mov r0, #0
	ldr r1, [sp, #0x18]
	add r2, r0, #0
	bl FUN_02002E14
	str r0, [sp, #0x1c]
	add r0, r4, r6
	bl GetWindowWidth
	lsl r1, r0, #3
	ldr r0, [sp, #0x1c]
	ldr r2, [sp, #0x18]
	sub r0, r1, r0
	lsr r7, r0, #1
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022152D0 ; =0x000F0E00
	add r3, r7, #0
	str r0, [sp, #8]
	add r0, r4, r6
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x18]
	bl String_dtor
	ldr r0, _022152D4 ; =0x00001FA8
	mov r1, #0x2c
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	ldr r1, [r5]
	str r0, [sp, #0x20]
	ldr r1, [r1, #0xc]
	mov r0, #6
	bl String_ctor
	mov r1, #0
	str r0, [sp, #0x24]
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _022152D8 ; =0x00001FAC
	ldr r2, [sp, #0x10]
	ldr r0, [r5, r0]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, _022152D8 ; =0x00001FAC
	ldr r1, [sp, #0x24]
	ldr r0, [r5, r0]
	ldr r2, [sp, #0x20]
	bl StringExpandPlaceholders
	mov r0, #0
	ldr r1, [sp, #0x24]
	add r2, r0, #0
	bl FUN_02002E14
	add r3, r0, #0
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022152D0 ; =0x000F0E00
	ldr r2, [sp, #0x24]
	str r0, [sp, #8]
	add r0, r4, r6
	sub r3, r7, r3
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x20]
	bl String_dtor
	ldr r0, [sp, #0x24]
	bl String_dtor
	ldr r0, _022152D4 ; =0x00001FA8
	mov r1, #0x2d
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	ldr r1, [r5]
	str r0, [sp, #0x28]
	ldr r1, [r1, #0xc]
	mov r0, #6
	bl String_ctor
	mov r1, #0
	str r0, [sp, #0x2c]
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _022152D8 ; =0x00001FAC
	ldr r2, [sp, #0x14]
	ldr r0, [r5, r0]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, _022152D8 ; =0x00001FAC
	ldr r1, [sp, #0x2c]
	ldr r0, [r5, r0]
	ldr r2, [sp, #0x28]
	bl StringExpandPlaceholders
	mov r1, #0
	ldr r3, [sp, #0x1c]
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022152D0 ; =0x000F0E00
	ldr r2, [sp, #0x2c]
	str r0, [sp, #8]
	add r0, r4, r6
	add r3, r7, r3
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x28]
	bl String_dtor
	ldr r0, [sp, #0x2c]
	bl String_dtor
	add r0, r4, r6
	bl ScheduleWindowCopyToVram
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022152CC: .word 0x00002070
_022152D0: .word 0x000F0E00
_022152D4: .word 0x00001FA8
_022152D8: .word 0x00001FAC

	thumb_func_start MOD09_022152DC
MOD09_022152DC: ; 0x022152DC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	lsl r4, r1, #4
	ldr r1, [r0]
	ldr r2, _02215344 ; =0x00002070
	add r1, #0x34
	ldrb r1, [r1]
	ldr r5, [r0, r2]
	cmp r1, #4
	bne _022152FC
	sub r2, #0xc8
	ldr r0, [r0, r2]
	mov r1, #0x3b
	bl NewString_ReadMsgData
	b _02215306
_022152FC:
	sub r2, #0xc8
	ldr r0, [r0, r2]
	mov r1, #0x3a
	bl NewString_ReadMsgData
_02215306:
	add r6, r0, #0
	mov r0, #2
	add r1, r6, #0
	mov r2, #0
	bl FUN_02002E14
	add r7, r0, #0
	mov r0, #6
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02215348 ; =0x00070809
	mov r3, #0x60
	str r0, [sp, #8]
	mov r0, #0
	sub r3, r3, r7
	str r0, [sp, #0xc]
	add r0, r5, r4
	mov r1, #2
	add r2, r6, #0
	lsr r3, r3, #1
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	add r0, r5, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02215344: .word 0x00002070
_02215348: .word 0x00070809

	thumb_func_start MOD09_0221534C
MOD09_0221534C: ; 0x0221534C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, _022153A4 ; =0x0000207A
	ldrb r1, [r4, r0]
	cmp r1, #7
	bne _02215362
	sub r0, #0xa
	ldr r5, [r4, r0]
	add r5, #0x80
	b _02215368
_02215362:
	sub r0, #0xa
	ldr r5, [r4, r0]
	add r5, #0x50
_02215368:
	add r0, r5, #0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _022153A8 ; =0x00001FA8
	mov r1, #0x3c
	ldr r0, [r4, r0]
	bl NewString_ReadMsgData
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022153AC ; =0x00010200
	add r2, r4, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	bl ScheduleWindowCopyToVram
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_022153A4: .word 0x0000207A
_022153A8: .word 0x00001FA8
_022153AC: .word 0x00010200

	thumb_func_start MOD09_022153B0
MOD09_022153B0: ; 0x022153B0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	str r1, [sp, #0x10]
	ldr r1, [r5]
	ldr r0, _022154EC ; =0x00002070
	ldr r1, [r1, #0xc]
	ldr r4, [r5, r0]
	mov r0, #6
	lsl r6, r2, #4
	bl String_ctor
	add r7, r0, #0
	ldr r0, _022154F0 ; =0x00001FA8
	mov r1, #0x2b
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	str r0, [sp, #0x14]
	mov r0, #0x18
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022154F4 ; =0x000F0E00
	ldr r2, [sp, #0x14]
	str r0, [sp, #8]
	mov r1, #0
	add r0, r4, r6
	mov r3, #0x28
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x14]
	bl String_dtor
	ldr r0, _022154F0 ; =0x00001FA8
	mov r1, #0x2e
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	str r0, [sp, #0x18]
	mov r0, #0
	ldr r1, [sp, #0x18]
	add r2, r0, #0
	bl FUN_02002E14
	str r0, [sp, #0x1c]
	mov r0, #0x18
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022154F4 ; =0x000F0E00
	ldr r2, [sp, #0x18]
	str r0, [sp, #8]
	mov r1, #0
	add r0, r4, r6
	mov r3, #0x50
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x18]
	bl String_dtor
	ldr r0, _022154F0 ; =0x00001FA8
	mov r1, #0x2d
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	mov r1, #0
	str r0, [sp, #0x20]
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, [sp, #0x10]
	ldr r0, _022154F8 ; =0x00001FAC
	ldrb r2, [r2, #3]
	ldr r0, [r5, r0]
	mov r3, #2
	bl BufferIntegerAsString
	ldr r0, _022154F8 ; =0x00001FAC
	ldr r2, [sp, #0x20]
	ldr r0, [r5, r0]
	add r1, r7, #0
	bl StringExpandPlaceholders
	mov r0, #0x18
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022154F4 ; =0x000F0E00
	ldr r3, [sp, #0x1c]
	str r0, [sp, #8]
	mov r1, #0
	add r3, #0x50
	add r0, r4, r6
	add r2, r7, #0
	str r1, [sp, #0xc]
	str r3, [sp, #0x1c]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x20]
	bl String_dtor
	ldr r0, _022154F0 ; =0x00001FA8
	mov r1, #0x2c
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	mov r1, #0
	str r0, [sp, #0x24]
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, [sp, #0x10]
	ldr r0, _022154F8 ; =0x00001FAC
	ldrb r2, [r2, #2]
	ldr r0, [r5, r0]
	mov r3, #2
	bl BufferIntegerAsString
	ldr r0, _022154F8 ; =0x00001FAC
	ldr r2, [sp, #0x24]
	ldr r0, [r5, r0]
	add r1, r7, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r7, #0
	add r2, r0, #0
	bl FUN_02002E14
	add r5, r0, #0
	mov r0, #0x18
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022154F4 ; =0x000F0E00
	mov r3, #0x50
	str r0, [sp, #8]
	mov r1, #0
	add r0, r4, r6
	add r2, r7, #0
	sub r3, r3, r5
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x24]
	bl String_dtor
	add r0, r7, #0
	bl String_dtor
	add r0, r4, r6
	bl ScheduleWindowCopyToVram
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022154EC: .word 0x00002070
_022154F0: .word 0x00001FA8
_022154F4: .word 0x000F0E00
_022154F8: .word 0x00001FAC

	thumb_func_start MOD09_022154FC
MOD09_022154FC: ; 0x022154FC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	str r1, [sp, #0x10]
	ldr r1, [r5]
	ldr r0, _022155C0 ; =0x00002070
	ldr r1, [r1, #0xc]
	ldr r4, [r5, r0]
	mov r0, #6
	lsl r6, r2, #4
	bl String_ctor
	str r0, [sp, #0x14]
	ldr r0, _022155C4 ; =0x00001FA8
	mov r1, #0x2b
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	str r0, [sp, #0x18]
	mov r0, #0
	ldr r1, [sp, #0x18]
	add r2, r0, #0
	bl FUN_02002E14
	add r7, r0, #0
	ldr r0, [sp, #0x18]
	bl String_dtor
	add r7, #0x28
	mov r0, #0x50
	sub r0, r0, r7
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	mov r0, #0x10
	lsl r2, r7, #0x10
	str r0, [sp, #4]
	add r0, r4, r6
	mov r1, #0
	lsr r2, r2, #0x10
	mov r3, #0x18
	bl FillWindowPixelRect
	ldr r0, _022155C4 ; =0x00001FA8
	mov r1, #0x2c
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	mov r1, #0
	add r7, r0, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, [sp, #0x10]
	ldr r0, _022155C8 ; =0x00001FAC
	ldrb r2, [r2, #2]
	ldr r0, [r5, r0]
	mov r3, #2
	bl BufferIntegerAsString
	ldr r0, _022155C8 ; =0x00001FAC
	ldr r1, [sp, #0x14]
	ldr r0, [r5, r0]
	add r2, r7, #0
	bl StringExpandPlaceholders
	mov r0, #0
	ldr r1, [sp, #0x14]
	add r2, r0, #0
	bl FUN_02002E14
	add r5, r0, #0
	mov r0, #0x18
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022155CC ; =0x000F0E00
	mov r3, #0x50
	str r0, [sp, #8]
	mov r1, #0
	ldr r2, [sp, #0x14]
	add r0, r4, r6
	sub r3, r3, r5
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
	ldr r0, [sp, #0x14]
	bl String_dtor
	add r0, r4, r6
	bl ScheduleWindowCopyToVram
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_022155C0: .word 0x00002070
_022155C4: .word 0x00001FA8
_022155C8: .word 0x00001FAC
_022155CC: .word 0x000F0E00

	thumb_func_start MOD09_022155D0
MOD09_022155D0: ; 0x022155D0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, [r5]
	mov r4, #0
	ldr r0, [r0]
	bl GetPartyCount
	cmp r0, #0
	ble _02215656
	add r0, r4, #0
	add r7, r5, #0
	str r0, [sp, #8]
	add r6, r5, #0
	add r7, #0x1b
_022155EE:
	ldr r0, _02215678 ; =0x00002070
	ldr r1, [r5, r0]
	ldr r0, [sp, #8]
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldrh r0, [r6, #8]
	cmp r0, #0
	beq _0221563E
	mov r0, #0x20
	str r0, [sp]
	mov r0, #8
	lsl r3, r4, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #2
	lsr r3, r3, #0x10
	bl MOD09_02213E84
	ldrb r0, [r7]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bne _0221562A
	lsl r1, r4, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	bl MOD09_0221567C
_0221562A:
	ldr r0, [r6, #4]
	bl FUN_0207C2D4
	cmp r0, #7
	bne _0221563E
	lsl r1, r4, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	bl MOD09_022156DC
_0221563E:
	ldr r0, [sp, #8]
	add r6, #0x50
	add r0, #0x10
	str r0, [sp, #8]
	ldr r0, [r5]
	add r7, #0x50
	ldr r0, [r0]
	add r4, r4, #1
	bl GetPartyCount
	cmp r4, r0
	blt _022155EE
_02215656:
	ldr r0, [r5]
	add r0, #0x35
	ldrb r0, [r0]
	cmp r0, #2
	bne _0221566C
	add r0, r5, #0
	mov r1, #7
	bl MOD09_022143F8
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0221566C:
	add r0, r5, #0
	mov r1, #6
	bl MOD09_022143F8
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02215678: .word 0x00002070

	thumb_func_start MOD09_0221567C
MOD09_0221567C: ; 0x0221567C
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0x18
	str r0, [sp]
	mov r0, #8
	add r6, r1, #0
	str r0, [sp, #4]
	ldr r0, _022156D8 ; =0x00002070
	lsl r4, r6, #4
	ldr r0, [r5, r0]
	mov r1, #0
	add r0, r0, r4
	mov r2, #0x38
	mov r3, #0x20
	bl FillWindowPixelRect
	mov r2, #0x40
	str r2, [sp]
	mov r0, #8
	str r0, [sp, #4]
	ldr r0, _022156D8 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	mov r3, #0x18
	add r0, r0, r4
	bl FillWindowPixelRect
	mov r0, #0x20
	str r0, [sp]
	add r0, r5, #0
	add r1, r6, #0
	add r2, r6, #0
	mov r3, #0x38
	bl MOD09_02214080
	mov r0, #0x18
	str r0, [sp]
	add r0, r5, #0
	add r1, r6, #0
	add r2, r6, #0
	mov r3, #0x40
	bl MOD09_02214100
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_022156D8: .word 0x00002070

	thumb_func_start MOD09_022156DC
MOD09_022156DC: ; 0x022156DC
	push {r3, lr}
	mov r2, #0x50
	mul r2, r1
	add r2, r0, r2
	ldrb r2, [r2, #0x1b]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1f
	bne _022156F8
	mov r2, #0x20
	str r2, [sp]
	add r2, r1, #0
	mov r3, #0
	bl MOD09_02214038
_022156F8:
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD09_022156FC
MOD09_022156FC: ; 0x022156FC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02215780 ; =0x00002070
	mov r1, #0
	ldr r0, [r4, r0]
	bl FillWindowPixelBuffer
	ldr r0, _02215780 ; =0x00002070
	mov r1, #0
	ldr r0, [r4, r0]
	add r0, #0x10
	bl FillWindowPixelBuffer
	ldr r0, _02215780 ; =0x00002070
	mov r1, #0
	ldr r0, [r4, r0]
	add r0, #0x20
	bl FillWindowPixelBuffer
	ldr r0, _02215780 ; =0x00002070
	mov r1, #0
	ldr r0, [r4, r0]
	add r0, #0x30
	bl FillWindowPixelBuffer
	ldr r1, [r4]
	add r0, r4, #0
	ldrb r1, [r1, #0x11]
	bl MOD09_02215784
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xf
	bl MOD09_0221445C
	ldr r0, [r4]
	ldrb r1, [r0, #0x11]
	mov r0, #0x50
	mul r0, r1
	add r0, r4, r0
	ldrb r0, [r0, #0x1b]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bne _0221576A
	add r0, r4, #0
	mov r1, #2
	mov r2, #0x12
	bl MOD09_0221445C
	add r0, r4, #0
	mov r1, #3
	mov r2, #0x13
	bl MOD09_0221445C
	pop {r4, pc}
_0221576A:
	ldr r0, _02215780 ; =0x00002070
	ldr r0, [r4, r0]
	add r0, #0x20
	bl ScheduleWindowCopyToVram
	ldr r0, _02215780 ; =0x00002070
	ldr r0, [r4, r0]
	add r0, #0x30
	bl ScheduleWindowCopyToVram
	pop {r4, pc}
	.align 2, 0
_02215780: .word 0x00002070

	thumb_func_start MOD09_02215784
MOD09_02215784: ; 0x02215784
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r0, #0
	ldr r0, _022158D0 ; =0x00002070
	add r6, r1, #0
	ldr r0, [r4, r0]
	ldr r1, [r4]
	str r0, [sp, #0x18]
	mov r0, #0x50
	add r7, r6, #0
	add r5, r4, #4
	mul r7, r0
	add r0, r5, r7
	str r0, [sp, #0x14]
	ldr r1, [r1, #0xc]
	mov r0, #0xc
	bl String_ctor
	str r0, [sp, #0x10]
	ldr r0, _022158D4 ; =0x00001FA8
	ldr r1, _022158D8 ; =0x0221B090
	lsl r2, r6, #2
	ldr r0, [r4, r0]
	ldr r1, [r1, r2]
	bl NewString_ReadMsgData
	add r6, r0, #0
	ldr r0, [r5, r7]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _022158DC ; =0x00001FAC
	mov r1, #0
	ldr r0, [r4, r0]
	bl BufferBoxMonNickname
	ldr r0, _022158DC ; =0x00001FAC
	ldr r1, [sp, #0x10]
	ldr r0, [r4, r0]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_dtor
	ldr r0, [sp, #0x14]
	mov r5, #0
	ldrb r0, [r0, #0x16]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bne _02215818
	ldr r0, [sp, #0x14]
	ldrb r0, [r0, #0x17]
	lsl r1, r0, #0x18
	lsr r1, r1, #0x1f
	bne _02215818
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1d
	bne _02215808
	ldr r0, _022158D4 ; =0x00001FA8
	mov r1, #0x10
	ldr r0, [r4, r0]
	bl NewString_ReadMsgData
	add r5, r0, #0
	b _02215818
_02215808:
	cmp r0, #1
	bne _02215818
	ldr r0, _022158D4 ; =0x00001FA8
	mov r1, #0x11
	ldr r0, [r4, r0]
	bl NewString_ReadMsgData
	add r5, r0, #0
_02215818:
	ldr r1, [sp, #0x10]
	mov r0, #2
	mov r2, #0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r5, #0
	bne _02215830
	mov r7, #0
	add r4, r7, #0
	b _02215840
_02215830:
	mov r0, #0
	add r1, r5, #0
	add r2, r0, #0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	mov r4, #8
_02215840:
	ldr r0, [sp, #0x18]
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r0, r0, r6
	sub r0, r0, r7
	sub r1, r0, r4
	lsr r0, r1, #0x1f
	add r0, r1, r0
	lsl r0, r0, #0x17
	lsr r7, r0, #0x18
	mov r0, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022158E0 ; =0x00070809
	ldr r2, [sp, #0x10]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x18]
	mov r1, #2
	add r3, r7, #0
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	bl String_dtor
	cmp r5, #0
	beq _022158C6
	ldr r0, [sp, #0x14]
	ldrb r0, [r0, #0x17]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1d
	bne _022158A4
	mov r0, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022158E4 ; =0x000A0B00
	add r3, r7, r6
	str r0, [sp, #8]
	mov r1, #0
	ldr r0, [sp, #0x18]
	add r2, r5, #0
	add r3, r4, r3
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	b _022158C0
_022158A4:
	mov r0, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022158E8 ; =0x000C0D00
	add r3, r7, r6
	str r0, [sp, #8]
	mov r1, #0
	ldr r0, [sp, #0x18]
	add r2, r5, #0
	add r3, r4, r3
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
_022158C0:
	add r0, r5, #0
	bl String_dtor
_022158C6:
	ldr r0, [sp, #0x18]
	bl ScheduleWindowCopyToVram
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022158D0: .word 0x00002070
_022158D4: .word 0x00001FA8
_022158D8: .word MOD9_0221B090
_022158DC: .word 0x00001FAC
_022158E0: .word 0x00070809
_022158E4: .word 0x000A0B00
_022158E8: .word 0x000C0D00

	thumb_func_start MOD09_022158EC
MOD09_022158EC: ; 0x022158EC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	ldr r0, _02215A1C ; =0x00002075
	mov r1, #6
	ldrb r2, [r5, r0]
	sub r0, r0, #5
	mul r1, r2
	lsl r1, r1, #0x10
	lsr r6, r1, #0x10
	ldr r1, [r5, r0]
	lsl r0, r6, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	add r0, r6, #1
	lsl r0, r0, #4
	str r0, [sp, #0x18]
	ldr r0, _02215A20 ; =0x00002070
	ldr r1, [r5, r0]
	ldr r0, [sp, #0x18]
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	add r0, r6, #2
	lsl r0, r0, #4
	str r0, [sp, #0x14]
	ldr r0, _02215A20 ; =0x00002070
	ldr r1, [r5, r0]
	ldr r0, [sp, #0x14]
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	add r0, r6, #3
	lsl r0, r0, #4
	str r0, [sp, #0x10]
	ldr r0, _02215A20 ; =0x00002070
	ldr r1, [r5, r0]
	ldr r0, [sp, #0x10]
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	add r0, r6, #4
	lsl r0, r0, #4
	str r0, [sp, #0xc]
	ldr r0, _02215A20 ; =0x00002070
	ldr r1, [r5, r0]
	ldr r0, [sp, #0xc]
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215A20 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x50
	bl FillWindowPixelBuffer
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r3, [r5]
	add r0, r5, #0
	ldrb r3, [r3, #0x11]
	add r1, r6, #0
	bl MOD09_02213E84
	add r0, r5, #0
	str r0, [sp, #0x1c]
	add r0, #0x34
	mov r4, #0
	add r7, r6, #1
	str r0, [sp, #0x1c]
_02215986:
	ldr r0, [r5]
	ldrb r1, [r0, #0x11]
	mov r0, #0x50
	add r2, r1, #0
	mul r2, r0
	ldr r0, [sp, #0x1c]
	lsl r1, r4, #3
	add r0, r0, r2
	str r1, [sp, #0x20]
	ldrh r1, [r0, r1]
	str r0, [sp, #0x24]
	cmp r1, #0
	beq _022159C8
	mov r0, #2
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	ldr r0, _02215A24 ; =0x00070809
	ldr r3, _02215A28 ; =0x0221B07C
	lsl r6, r4, #2
	str r0, [sp, #8]
	ldr r3, [r3, r6]
	add r0, r5, #0
	add r2, r7, r4
	bl MOD09_022142FC
	ldr r2, [sp, #0x20]
	ldr r1, [sp, #0x24]
	add r0, r5, #0
	add r1, r1, r2
	add r2, r7, r4
	bl MOD09_022153B0
_022159C8:
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #4
	blo _02215986
	add r0, r5, #0
	mov r1, #5
	mov r2, #0x12
	bl MOD09_0221445C
	ldr r0, _02215A20 ; =0x00002070
	ldr r1, [r5, r0]
	ldr r0, [sp, #0x18]
	add r0, r1, r0
	bl ScheduleWindowCopyToVram
	ldr r0, _02215A20 ; =0x00002070
	ldr r1, [r5, r0]
	ldr r0, [sp, #0x14]
	add r0, r1, r0
	bl ScheduleWindowCopyToVram
	ldr r0, _02215A20 ; =0x00002070
	ldr r1, [r5, r0]
	ldr r0, [sp, #0x10]
	add r0, r1, r0
	bl ScheduleWindowCopyToVram
	ldr r0, _02215A20 ; =0x00002070
	ldr r1, [r5, r0]
	ldr r0, [sp, #0xc]
	add r0, r1, r0
	bl ScheduleWindowCopyToVram
	ldr r1, _02215A1C ; =0x00002075
	mov r0, #1
	ldrb r2, [r5, r1]
	eor r0, r2
	strb r0, [r5, r1]
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02215A1C: .word 0x00002075
_02215A20: .word 0x00002070
_02215A24: .word 0x00070809
_02215A28: .word MOD9_0221B07C

	thumb_func_start MOD09_02215A2C
MOD09_02215A2C: ; 0x02215A2C
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, _02215C3C ; =0x00002075
	mov r1, #0x16
	ldrb r2, [r5, r0]
	sub r0, r0, #5
	add r4, r2, #0
	mul r4, r1
	ldr r1, [r5, r0]
	mov r0, #0x13
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	mov r0, #5
	lsl r0, r0, #6
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0xe0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0xf0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	mov r0, #1
	lsl r0, r0, #8
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	mov r0, #0x11
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	mov r0, #0x12
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0xd0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	mov r0, #0x15
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	lsl r0, r4, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #0
	add r0, #0xa
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #0
	add r0, #0xb
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #0
	add r0, #0xc
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #5
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #6
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #7
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #0
	add r0, #8
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #0
	add r0, #9
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #4
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #1
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #2
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215C40 ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #3
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	ldr r3, [r5]
	add r0, r5, #0
	ldrb r3, [r3, #0x11]
	add r1, r4, #0
	bl MOD09_02213E84
	ldr r1, [r5]
	add r0, r5, #0
	ldrb r1, [r1, #0x11]
	bl MOD09_02214B8C
	mov r3, #0
	str r3, [sp]
	ldr r2, [r5]
	add r1, r4, #0
	ldrb r2, [r2, #0x11]
	add r0, r5, #0
	add r1, #0xa
	bl MOD09_02214100
	ldr r1, [r5]
	add r0, r5, #0
	ldrb r1, [r1, #0x11]
	bl MOD09_022144C0
	ldr r1, [r5]
	add r0, r5, #0
	ldrb r1, [r1, #0x11]
	bl MOD09_02214694
	ldr r1, [r5]
	add r0, r5, #0
	ldrb r1, [r1, #0x11]
	bl MOD09_02214790
	ldr r1, [r5]
	add r0, r5, #0
	ldrb r1, [r1, #0x11]
	bl MOD09_0221488C
	ldr r1, [r5]
	add r0, r5, #0
	ldrb r1, [r1, #0x11]
	bl MOD09_0221498C
	ldr r1, [r5]
	add r0, r5, #0
	ldrb r1, [r1, #0x11]
	bl MOD09_02214A8C
	ldr r2, [r5]
	add r0, r5, #0
	ldrb r2, [r2, #0x11]
	add r1, r4, #1
	bl MOD09_022141D8
	ldr r2, [r5]
	add r0, r5, #0
	ldrb r2, [r2, #0x11]
	add r1, r4, #3
	bl MOD09_02214260
	ldr r1, [r5]
	add r0, r5, #0
	ldrb r1, [r1, #0x11]
	bl MOD09_02214D24
	add r0, r5, #0
	mov r1, #0x15
	mov r2, #0x13
	bl MOD09_0221445C
	ldr r1, _02215C3C ; =0x00002075
	mov r0, #1
	ldrb r2, [r5, r1]
	eor r0, r2
	strb r0, [r5, r1]
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02215C3C: .word 0x00002075
_02215C40: .word 0x00002070

	thumb_func_start MOD09_02215C44
MOD09_02215C44: ; 0x02215C44
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _02215D98 ; =0x00002075
	mov r1, #0xb
	ldrb r2, [r5, r0]
	sub r0, r0, #5
	ldr r0, [r5, r0]
	add r4, r2, #0
	mul r4, r1
	add r0, #0x60
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215D9C ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x70
	bl FillWindowPixelBuffer
	ldr r0, _02215D9C ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x80
	bl FillWindowPixelBuffer
	ldr r0, _02215D9C ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x90
	bl FillWindowPixelBuffer
	ldr r0, _02215D9C ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0xa0
	bl FillWindowPixelBuffer
	ldr r0, _02215D9C ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #1
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215D9C ; =0x00002070
	ldr r1, [r5, r0]
	lsl r0, r4, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215D9C ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #2
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215D9C ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #3
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215D9C ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #5
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02215D9C ; =0x00002070
	ldr r1, [r5, r0]
	add r0, r4, #4
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, [r5]
	add r2, r5, #0
	ldrb r3, [r0, #0x11]
	add r0, #0x34
	ldrb r0, [r0]
	mov r1, #0x50
	add r2, #0x34
	mul r1, r3
	add r1, r2, r1
	lsl r0, r0, #3
	add r7, r1, r0
	mov r2, #0
	str r2, [sp]
	add r0, r5, #0
	mov r1, #6
	str r2, [sp, #4]
	bl MOD09_02213E84
	mov r2, #0
	add r0, r5, #0
	mov r1, #7
	add r3, r2, #0
	bl MOD09_022143A0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02215DA0 ; =0x000F0E00
	add r2, r4, #0
	str r0, [sp, #8]
	ldr r3, [r5]
	ldrh r1, [r7]
	add r3, #0x34
	ldrb r3, [r3]
	add r0, r5, #0
	lsl r6, r3, #2
	ldr r3, _02215DA4 ; =0x0221B07C
	ldr r3, [r3, r6]
	bl MOD09_022142FC
	add r0, r5, #0
	mov r1, #8
	bl MOD09_02214DA0
	ldrb r2, [r7, #6]
	add r0, r5, #0
	add r1, r4, #2
	bl MOD09_02214DE8
	add r0, r5, #0
	mov r1, #9
	bl MOD09_02214ED0
	ldrb r2, [r7, #7]
	add r0, r5, #0
	add r1, r4, #3
	bl MOD09_02214F18
	ldrh r2, [r7]
	add r0, r5, #0
	add r1, r4, #4
	bl MOD09_02215000
	add r0, r5, #0
	mov r1, #0xa
	bl MOD09_022150C8
	ldrb r2, [r7, #5]
	add r0, r5, #0
	add r1, r4, #5
	bl MOD09_0221512C
	ldrb r2, [r7, #2]
	ldrb r3, [r7, #3]
	add r0, r5, #0
	add r1, r4, #1
	bl MOD09_022151A8
	ldr r1, _02215D98 ; =0x00002075
	mov r0, #1
	ldrb r2, [r5, r1]
	eor r0, r2
	strb r0, [r5, r1]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02215D98: .word 0x00002075
_02215D9C: .word 0x00002070
_02215DA0: .word 0x000F0E00
_02215DA4: .word MOD9_0221B07C

	thumb_func_start MOD09_02215DA8
MOD09_02215DA8: ; 0x02215DA8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldr r0, _02215EC4 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	bl FillWindowPixelBuffer
	ldr r0, _02215EC4 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x10
	bl FillWindowPixelBuffer
	ldr r0, _02215EC4 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x20
	bl FillWindowPixelBuffer
	ldr r0, _02215EC4 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x30
	bl FillWindowPixelBuffer
	ldr r0, _02215EC4 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x40
	bl FillWindowPixelBuffer
	ldr r0, _02215EC4 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x50
	bl FillWindowPixelBuffer
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	ldr r3, [r5]
	add r0, r5, #0
	ldrb r3, [r3, #0x11]
	add r2, r1, #0
	bl MOD09_02213E84
	add r0, r5, #0
	mov r6, #0
	str r0, [sp, #0x10]
	add r0, #0x34
	ldr r7, _02215EC8 ; =0x0221B07C
	add r4, r6, #0
	str r0, [sp, #0x10]
_02215E14:
	ldr r0, [r5]
	ldrb r1, [r0, #0x11]
	mov r0, #0x50
	add r2, r1, #0
	mul r2, r0
	ldr r0, [sp, #0x10]
	add r0, r0, r2
	ldrh r1, [r0, r4]
	str r0, [sp, #0xc]
	cmp r1, #0
	beq _02215E4C
	mov r0, #2
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	ldr r0, _02215ECC ; =0x00070809
	add r2, r6, #1
	str r0, [sp, #8]
	ldr r3, [r7]
	add r0, r5, #0
	bl MOD09_022142FC
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	add r1, r1, r4
	add r2, r6, #1
	bl MOD09_022153B0
_02215E4C:
	add r6, r6, #1
	add r4, #8
	add r7, r7, #4
	cmp r6, #4
	blo _02215E14
	mov r0, #2
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	ldr r0, _02215ECC ; =0x00070809
	mov r2, #5
	str r0, [sp, #8]
	ldr r1, [r5]
	add r0, r5, #0
	ldrh r1, [r1, #0x24]
	mov r3, #0x49
	bl MOD09_022142FC
	ldr r0, [r5]
	mov r1, #5
	ldrh r0, [r0, #0x24]
	bl GetWazaAttr
	add r1, sp, #0x14
	strb r0, [r1, #2]
	ldrb r0, [r1, #2]
	mov r2, #5
	strb r0, [r1, #3]
	add r0, r5, #0
	add r1, sp, #0x14
	bl MOD09_022153B0
	ldr r0, _02215EC4 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, #0x10
	bl ScheduleWindowCopyToVram
	ldr r0, _02215EC4 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, #0x20
	bl ScheduleWindowCopyToVram
	ldr r0, _02215EC4 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, #0x30
	bl ScheduleWindowCopyToVram
	ldr r0, _02215EC4 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, #0x40
	bl ScheduleWindowCopyToVram
	ldr r0, _02215EC4 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, #0x50
	bl ScheduleWindowCopyToVram
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_02215EC4: .word 0x00002070
_02215EC8: .word MOD9_0221B07C
_02215ECC: .word 0x00070809

	thumb_func_start MOD09_02215ED0
MOD09_02215ED0: ; 0x02215ED0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, _02216090 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	bl FillWindowPixelBuffer
	ldr r0, _02216090 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x20
	bl FillWindowPixelBuffer
	ldr r0, _02216090 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x30
	bl FillWindowPixelBuffer
	ldr r0, _02216090 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x10
	bl FillWindowPixelBuffer
	ldr r0, _02216090 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x40
	bl FillWindowPixelBuffer
	ldr r0, _02216090 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x60
	bl FillWindowPixelBuffer
	ldr r0, _02216090 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x50
	bl FillWindowPixelBuffer
	ldr r0, _02216090 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x70
	bl FillWindowPixelBuffer
	ldr r0, _02216090 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x90
	bl FillWindowPixelBuffer
	ldr r0, _02216090 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0xa0
	bl FillWindowPixelBuffer
	ldr r0, _02216090 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x80
	bl FillWindowPixelBuffer
	ldr r0, _02216090 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0xb0
	bl FillWindowPixelBuffer
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	ldr r3, [r5]
	add r0, r5, #0
	ldrb r3, [r3, #0x11]
	add r2, r1, #0
	bl MOD09_02213E84
	mov r2, #0
	add r0, r5, #0
	mov r1, #2
	add r3, r2, #0
	bl MOD09_022143A0
	add r0, r5, #0
	mov r1, #4
	bl MOD09_02214DA0
	add r0, r5, #0
	mov r1, #5
	bl MOD09_02214ED0
	add r0, r5, #0
	mov r1, #9
	bl MOD09_022150C8
	ldr r1, [r5]
	add r0, r1, #0
	add r0, #0x34
	ldrb r3, [r0]
	cmp r3, #4
	bhs _0221600C
	ldrb r1, [r1, #0x11]
	add r2, r5, #0
	mov r0, #0x50
	add r2, #0x34
	mul r0, r1
	add r7, r2, r0
	lsl r0, r3, #3
	str r0, [sp, #0xc]
	add r4, r7, r0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02216094 ; =0x000F0E00
	lsl r6, r3, #2
	str r0, [sp, #8]
	ldr r1, [sp, #0xc]
	ldr r3, _02216098 ; =0x0221B07C
	ldrh r1, [r7, r1]
	ldr r3, [r3, r6]
	add r0, r5, #0
	mov r2, #1
	bl MOD09_022142FC
	ldrb r2, [r4, #6]
	add r0, r5, #0
	mov r1, #6
	bl MOD09_02214DE8
	ldrb r2, [r4, #7]
	add r0, r5, #0
	mov r1, #7
	bl MOD09_02214F18
	ldr r2, [sp, #0xc]
	add r0, r5, #0
	ldrh r2, [r7, r2]
	mov r1, #8
	bl MOD09_02215000
	ldrb r2, [r4, #5]
	add r0, r5, #0
	mov r1, #0xa
	bl MOD09_0221512C
	ldrb r2, [r4, #2]
	ldrb r3, [r4, #3]
	add r0, r5, #0
	mov r1, #3
	bl MOD09_022151A8
	b _02216082
_0221600C:
	ldrh r0, [r1, #0x24]
	mov r1, #5
	bl GetWazaAttr
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02216094 ; =0x000F0E00
	mov r2, #1
	str r0, [sp, #8]
	ldr r1, [r5]
	add r0, r5, #0
	ldrh r1, [r1, #0x24]
	mov r3, #0x49
	bl MOD09_022142FC
	ldr r2, [r5]
	add r0, r5, #0
	ldrh r2, [r2, #0x24]
	mov r1, #8
	bl MOD09_02215000
	ldr r0, [r5]
	mov r1, #4
	ldrh r0, [r0, #0x24]
	bl GetWazaAttr
	add r2, r0, #0
	add r0, r5, #0
	mov r1, #6
	bl MOD09_02214DE8
	ldr r0, [r5]
	mov r1, #2
	ldrh r0, [r0, #0x24]
	bl GetWazaAttr
	add r2, r0, #0
	add r0, r5, #0
	mov r1, #7
	bl MOD09_02214F18
	ldr r0, [r5]
	mov r1, #1
	ldrh r0, [r0, #0x24]
	bl GetWazaAttr
	add r2, r0, #0
	add r0, r5, #0
	mov r1, #0xa
	bl MOD09_0221512C
	add r0, r5, #0
	mov r1, #3
	add r2, r4, #0
	add r3, r4, #0
	bl MOD09_022151A8
_02216082:
	add r0, r5, #0
	mov r1, #0xb
	bl MOD09_022152DC
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02216090: .word 0x00002070
_02216094: .word 0x000F0E00
_02216098: .word MOD9_0221B07C

	thumb_func_start MOD09_0221609C
MOD09_0221609C: ; 0x0221609C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, _02216184 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	bl FillWindowPixelBuffer
	ldr r0, _02216184 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x10
	bl FillWindowPixelBuffer
	ldr r0, _02216184 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x20
	bl FillWindowPixelBuffer
	ldr r0, _02216184 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x30
	bl FillWindowPixelBuffer
	ldr r0, _02216184 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x40
	bl FillWindowPixelBuffer
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	ldr r3, [r5]
	add r0, r5, #0
	ldrb r3, [r3, #0x11]
	add r2, r1, #0
	bl MOD09_02213E84
	add r0, r5, #0
	mov r6, #0
	str r0, [sp, #0x10]
	add r0, #0x34
	ldr r7, _02216188 ; =0x0221B07C
	add r4, r6, #0
	str r0, [sp, #0x10]
_022160FC:
	ldr r0, [r5]
	ldrb r1, [r0, #0x11]
	mov r0, #0x50
	add r2, r1, #0
	mul r2, r0
	ldr r0, [sp, #0x10]
	add r0, r0, r2
	ldrh r1, [r0, r4]
	str r0, [sp, #0xc]
	cmp r1, #0
	beq _02216134
	mov r0, #2
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	ldr r0, _0221618C ; =0x00070809
	add r2, r6, #1
	str r0, [sp, #8]
	ldr r3, [r7]
	add r0, r5, #0
	bl MOD09_022142FC
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	add r1, r1, r4
	add r2, r6, #1
	bl MOD09_022153B0
_02216134:
	add r6, r6, #1
	add r4, #8
	add r7, r7, #4
	cmp r6, #4
	blo _022160FC
	ldr r2, [r5]
	mov r1, #0x25
	ldrh r0, [r2, #0x22]
	ldr r2, [r2, #0xc]
	bl GetItemAttr
	cmp r0, #0
	bne _02216156
	add r0, r5, #0
	mov r1, #0x5e
	bl MOD09_022143F8
_02216156:
	ldr r0, _02216184 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, #0x10
	bl ScheduleWindowCopyToVram
	ldr r0, _02216184 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, #0x20
	bl ScheduleWindowCopyToVram
	ldr r0, _02216184 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, #0x30
	bl ScheduleWindowCopyToVram
	ldr r0, _02216184 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, #0x40
	bl ScheduleWindowCopyToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_02216184: .word 0x00002070
_02216188: .word MOD9_0221B07C
_0221618C: .word 0x00070809

	thumb_func_start MOD09_02216190
MOD09_02216190: ; 0x02216190
	push {r3, r4, r5, lr}
	ldr r4, [r0]
	add r3, r1, #0
	ldrb r5, [r4, #0x11]
	add r1, r0, #0
	mov r4, #0x50
	add r1, #0x34
	mul r4, r5
	add r4, r1, r4
	lsl r1, r2, #3
	add r1, r4, r1
	add r2, r3, #0
	bl MOD09_022154FC
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD09_022161B0
MOD09_022161B0: ; 0x022161B0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, _02216304 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	bl FillWindowPixelBuffer
	ldr r0, _02216304 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x20
	bl FillWindowPixelBuffer
	ldr r0, _02216304 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x30
	bl FillWindowPixelBuffer
	ldr r0, _02216304 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x10
	bl FillWindowPixelBuffer
	ldr r0, _02216304 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x40
	bl FillWindowPixelBuffer
	ldr r0, _02216304 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x50
	bl FillWindowPixelBuffer
	ldr r0, _02216304 ; =0x00002070
	mov r1, #0
	ldr r0, [r5, r0]
	add r0, #0x60
	bl FillWindowPixelBuffer
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	ldr r3, [r5]
	add r0, r5, #0
	ldrb r3, [r3, #0x11]
	add r2, r1, #0
	bl MOD09_02213E84
	mov r2, #0
	add r0, r5, #0
	mov r1, #2
	add r3, r2, #0
	bl MOD09_022143A0
	ldr r0, _02216308 ; =0x00001FA8
	mov r1, #0x39
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	add r4, r0, #0
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	mov r3, #0x60
	bl FUN_02002F40
	mov r1, #0
	add r3, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0221630C ; =0x000F0E00
	add r2, r4, #0
	str r0, [sp, #8]
	ldr r0, _02216304 ; =0x00002070
	str r1, [sp, #0xc]
	ldr r0, [r5, r0]
	add r0, #0x40
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl String_dtor
	ldr r0, _02216304 ; =0x00002070
	ldr r0, [r5, r0]
	add r0, #0x40
	bl ScheduleWindowCopyToVram
	ldr r1, [r5]
	add r0, r1, #0
	add r0, #0x34
	ldrb r3, [r0]
	cmp r3, #4
	bhs _022162BE
	ldrb r1, [r1, #0x11]
	add r2, r5, #0
	mov r0, #0x50
	add r2, #0x34
	mul r0, r1
	add r4, r2, r0
	lsl r7, r3, #3
	add r0, r4, r7
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221630C ; =0x000F0E00
	lsl r6, r3, #2
	str r0, [sp, #8]
	ldr r3, _02216310 ; =0x0221B07C
	ldrh r1, [r4, r7]
	ldr r3, [r3, r6]
	add r0, r5, #0
	mov r2, #1
	bl MOD09_022142FC
	ldrh r2, [r4, r7]
	add r0, r5, #0
	mov r1, #5
	bl MOD09_02215060
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x10]
	ldrb r2, [r2, #2]
	ldrb r3, [r3, #3]
	add r0, r5, #0
	mov r1, #3
	bl MOD09_022151A8
	b _022162F8
_022162BE:
	ldrh r0, [r1, #0x24]
	mov r1, #5
	bl GetWazaAttr
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221630C ; =0x000F0E00
	mov r2, #1
	str r0, [sp, #8]
	ldr r1, [r5]
	add r0, r5, #0
	ldrh r1, [r1, #0x24]
	mov r3, #0x49
	bl MOD09_022142FC
	ldr r2, [r5]
	add r0, r5, #0
	ldrh r2, [r2, #0x24]
	mov r1, #5
	bl MOD09_02215060
	add r0, r5, #0
	mov r1, #3
	add r2, r4, #0
	add r3, r4, #0
	bl MOD09_022151A8
_022162F8:
	add r0, r5, #0
	mov r1, #6
	bl MOD09_022152DC
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02216304: .word 0x00002070
_02216308: .word 0x00001FA8
_0221630C: .word 0x000F0E00
_02216310: .word MOD9_0221B07C

	thumb_func_start MOD09_02216314
MOD09_02216314: ; 0x02216314
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02216338 ; =0x00002060
	mov r1, #1
	add r0, r4, r0
	add r2, r1, #0
	mov r3, #0xe
	bl FUN_0200D0BC
	ldr r0, _02216338 ; =0x00002060
	mov r1, #0xf
	add r0, r4, r0
	bl FillWindowPixelBuffer
	add r0, r4, #0
	bl MOD09_0221633C
	pop {r4, pc}
	.align 2, 0
_02216338: .word 0x00002060

	thumb_func_start MOD09_0221633C
MOD09_0221633C: ; 0x0221633C
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #1
	bl TextFlags_SetCanABSpeedUpPrint
	ldr r0, [r4]
	ldr r0, [r0, #8]
	bl MOD11_02230E54
	mov r3, #0
	str r3, [sp]
	str r0, [sp, #4]
	ldr r2, _02216370 ; =0x00002060
	str r3, [sp, #8]
	add r0, r4, r2
	sub r2, #0xb0
	ldr r2, [r4, r2]
	mov r1, #1
	bl AddTextPrinterParameterized
	ldr r1, _02216374 ; =0x0000207B
	strb r0, [r4, r1]
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_02216370: .word 0x00002060
_02216374: .word 0x0000207B

	thumb_func_start MOD09_02216378
MOD09_02216378: ; 0x02216378
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5]
	mov r1, #0
	str r0, [sp, #0xc]
	ldr r2, [sp, #0xc]
	ldrh r0, [r0, #0x22]
	ldr r2, [r2, #0xc]
	bl LoadItemDataOrGfx
	ldr r2, [sp, #0xc]
	add r6, r0, #0
	ldrb r3, [r2, #0x11]
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0xc]
	add r2, r2, r3
	add r2, #0x2c
	ldrb r2, [r2]
	ldr r0, [r0, #8]
	ldr r1, [r1, #0x28]
	bl MOD11_02230014
	mov r1, #0xa2
	mov r2, #0
	add r7, r0, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	add r0, r6, #0
	mov r1, #0xf
	mov r4, #0
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0
	beq _022163CC
	mov r0, #1
	orr r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_022163CC:
	add r0, r6, #0
	mov r1, #0x10
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0
	beq _022163E0
	mov r0, #2
	orr r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_022163E0:
	add r0, r6, #0
	mov r1, #0x11
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0
	beq _022163F4
	mov r0, #4
	orr r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_022163F4:
	add r0, r6, #0
	mov r1, #0x12
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0
	beq _02216408
	mov r0, #8
	orr r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02216408:
	add r0, r6, #0
	mov r1, #0x13
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0
	beq _0221641C
	mov r0, #0x10
	orr r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_0221641C:
	add r0, r6, #0
	mov r1, #0x14
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0
	beq _02216430
	mov r0, #0x20
	orr r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02216430:
	add r0, r6, #0
	mov r1, #0x15
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0
	beq _02216444
	mov r0, #0x40
	orr r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_02216444:
	ldr r0, [sp, #0xc]
	ldrb r1, [r0, #0x11]
	mov r0, #0x50
	mul r0, r1
	add r0, r5, r0
	ldrh r1, [r0, #0x14]
	cmp r1, #0
	bne _0221648E
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _0221648E
	ldr r0, _022166C8 ; =0x00001FA8
	mov r1, #0x58
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r7, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _022166CC ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferBoxMonNickname
	ldr r1, _022166CC ; =0x00001FAC
	add r2, r4, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	b _022166BE
_0221648E:
	ldr r0, [sp, #8]
	cmp r0, r1
	beq _022164EA
	ldr r0, _022166C8 ; =0x00001FA8
	mov r1, #0x52
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r7, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _022166CC ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferBoxMonNickname
	mov r0, #0
	str r0, [sp]
	mov r1, #1
	ldr r2, [sp, #0xc]
	str r1, [sp, #4]
	ldrb r3, [r2, #0x11]
	mov r2, #0x50
	ldr r0, _022166CC ; =0x00001FAC
	mul r2, r3
	add r2, r5, r2
	ldrh r3, [r2, #0x14]
	ldr r2, [sp, #8]
	ldr r0, [r5, r0]
	sub r2, r2, r3
	mov r3, #3
	bl BufferIntegerAsString
	ldr r1, _022166CC ; =0x00001FAC
	add r2, r4, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	b _022166BE
_022164EA:
	add r0, r6, #0
	mov r1, #0x24
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0
	bne _02216502
	add r0, r6, #0
	mov r1, #0x25
	bl GetItemAttr_PreloadedItemData
	cmp r0, #0
	beq _02216512
_02216502:
	ldr r2, _022166C8 ; =0x00001FA8
	mov r1, #0x57
	ldr r0, [r5, r2]
	add r2, #8
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	b _022166BE
_02216512:
	cmp r4, #1
	ldr r0, _022166C8 ; =0x00001FA8
	bne _0221654A
	ldr r0, [r5, r0]
	mov r1, #0x5c
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r7, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _022166CC ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferBoxMonNickname
	ldr r1, _022166CC ; =0x00001FAC
	add r2, r4, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	b _022166BE
_0221654A:
	cmp r4, #2
	bne _02216580
	ldr r0, [r5, r0]
	mov r1, #0x53
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r7, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _022166CC ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferBoxMonNickname
	ldr r1, _022166CC ; =0x00001FAC
	add r2, r4, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	b _022166BE
_02216580:
	cmp r4, #4
	bne _022165B6
	ldr r0, [r5, r0]
	mov r1, #0x55
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r7, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _022166CC ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferBoxMonNickname
	ldr r1, _022166CC ; =0x00001FAC
	add r2, r4, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	b _022166BE
_022165B6:
	cmp r4, #8
	bne _022165EC
	ldr r0, [r5, r0]
	mov r1, #0x56
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r7, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _022166CC ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferBoxMonNickname
	ldr r1, _022166CC ; =0x00001FAC
	add r2, r4, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	b _022166BE
_022165EC:
	cmp r4, #0x10
	bne _02216622
	ldr r0, [r5, r0]
	mov r1, #0x54
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r7, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _022166CC ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferBoxMonNickname
	ldr r1, _022166CC ; =0x00001FAC
	add r2, r4, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	b _022166BE
_02216622:
	cmp r4, #0x20
	bne _02216658
	ldr r0, [r5, r0]
	mov r1, #0x5a
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r7, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _022166CC ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferBoxMonNickname
	ldr r1, _022166CC ; =0x00001FAC
	add r2, r4, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	b _022166BE
_02216658:
	cmp r4, #0x40
	bne _0221668E
	ldr r0, [r5, r0]
	mov r1, #0x5b
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r7, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _022166CC ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferBoxMonNickname
	ldr r1, _022166CC ; =0x00001FAC
	add r2, r4, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	b _022166BE
_0221668E:
	ldr r0, [r5, r0]
	mov r1, #0x59
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r7, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _022166CC ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferBoxMonNickname
	ldr r1, _022166CC ; =0x00001FAC
	add r2, r4, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
_022166BE:
	add r0, r6, #0
	bl FreeToHeap
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022166C8: .word 0x00001FA8
_022166CC: .word 0x00001FAC

	thumb_func_start MOD09_022166D0
MOD09_022166D0: ; 0x022166D0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r3, [r5]
	ldrb r2, [r3, #0x11]
	ldr r0, [r3, #8]
	ldr r1, [r3, #0x28]
	add r2, r3, r2
	add r2, #0x2c
	ldrb r2, [r2]
	bl MOD11_02230014
	add r6, r0, #0
	ldr r0, _02216728 ; =0x00001FA8
	mov r1, #0x5f
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r6, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, _0221672C ; =0x00001FAC
	mov r1, #0
	ldr r0, [r5, r0]
	bl BufferBoxMonNickname
	ldr r0, _0221672C ; =0x00001FAC
	ldr r2, _02216730 ; =0x00000175
	ldr r0, [r5, r0]
	mov r1, #1
	bl BufferMoveName
	ldr r1, _0221672C ; =0x00001FAC
	add r2, r4, #0
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	pop {r4, r5, r6, pc}
	.align 2, 0
_02216728: .word 0x00001FA8
_0221672C: .word 0x00001FAC
_02216730: .word 0x00000175

	thumb_func_start MOD09_02216734
MOD09_02216734: ; 0x02216734
	push {r4, lr}
	add r4, r0, #0
	bl MOD09_02216770
	add r0, r4, #0
	bl MOD09_022167BC
	add r0, r4, #0
	bl MOD09_02216894
	add r0, r4, #0
	bl MOD09_02216934
	add r0, r4, #0
	bl MOD09_022169AC
	add r0, r4, #0
	bl MOD09_02216A4C
	add r0, r4, #0
	bl MOD09_02216B4C
	add r0, r4, #0
	bl MOD09_02217750
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	pop {r4, pc}

	thumb_func_start MOD09_02216770
MOD09_02216770: ; 0x02216770
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r3, _022167B4 ; =0x0221B4B8
	add r2, sp, #0
	add r5, r0, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl MOD11_02230078
	add r4, r0, #0
	bl FUN_0200BB34
	ldr r1, _022167B8 ; =0x00001FB4
	mov r2, #0x2b
	str r0, [r5, r1]
	ldr r1, [r5, r1]
	add r0, r4, #0
	bl FUN_0200BBF0
	ldr r1, _022167B8 ; =0x00001FB4
	add r0, r4, #0
	ldr r1, [r5, r1]
	add r2, sp, #0
	bl FUN_0200BF60
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_022167B4: .word MOD9_0221B4B8
_022167B8: .word 0x00001FB4

	thumb_func_start MOD09_022167BC
MOD09_022167BC: ; 0x022167BC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r6, r0, #0
	ldr r0, [r6]
	ldr r0, [r0, #8]
	bl MOD11_02230078
	add r7, r0, #0
	bl FUN_0206B888
	mov r1, #0x13
	str r1, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r1, #3
	str r1, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _0221688C ; =0x0000B007
	ldr r3, _02216890 ; =0x00001FB4
	str r0, [sp, #0x14]
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	ldr r3, [r6, r3]
	add r2, r7, #0
	bl FUN_0200C0DC
	bl FUN_0206B890
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _0221688C ; =0x0000B007
	ldr r1, _02216890 ; =0x00001FB4
	str r0, [sp, #4]
	ldr r1, [r6, r1]
	add r0, r7, #0
	mov r2, #0x13
	bl FUN_0200C124
	bl FUN_0206B89C
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _0221688C ; =0x0000B007
	ldr r1, _02216890 ; =0x00001FB4
	str r0, [sp, #4]
	ldr r1, [r6, r1]
	add r0, r7, #0
	mov r2, #0x13
	bl FUN_0200C13C
	mov r4, #0
	add r5, r6, #0
_0221682E:
	ldrh r0, [r5, #8]
	cmp r0, #0
	beq _02216858
	ldr r0, [r5, #4]
	bl FUN_0206B6C8
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _0221688C ; =0x0000B007
	ldr r1, _02216890 ; =0x00001FB4
	add r0, r4, r0
	str r0, [sp, #8]
	ldr r1, [r6, r1]
	add r0, r7, #0
	mov r2, #0x13
	bl FUN_0200C00C
	b _0221687E
_02216858:
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	bl FUN_0206B6D4
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _0221688C ; =0x0000B007
	ldr r1, _02216890 ; =0x00001FB4
	add r0, r4, r0
	str r0, [sp, #8]
	ldr r1, [r6, r1]
	add r0, r7, #0
	mov r2, #0x13
	bl FUN_0200C00C
_0221687E:
	add r4, r4, #1
	add r5, #0x50
	cmp r4, #6
	blo _0221682E
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221688C: .word 0x0000B007
_02216890: .word 0x00001FB4

	thumb_func_start MOD09_02216894
MOD09_02216894: ; 0x02216894
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl MOD11_02230078
	add r4, r0, #0
	bl FUN_0207C2C8
	mov r1, #0x27
	str r1, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _02216928 ; =0x0000B008
	ldr r3, _0221692C ; =0x00001FB4
	str r0, [sp, #0x14]
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r3, [r5, r3]
	mov r1, #3
	add r2, r4, #0
	bl FUN_0200C0DC
	bl FUN_0207C2CC
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _02216928 ; =0x0000B008
	ldr r1, _0221692C ; =0x00001FB4
	str r0, [sp, #4]
	ldr r1, [r5, r1]
	add r0, r4, #0
	mov r2, #0x27
	bl FUN_0200C124
	bl FUN_0207C2D0
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _02216928 ; =0x0000B008
	ldr r1, _0221692C ; =0x00001FB4
	str r0, [sp, #4]
	ldr r1, [r5, r1]
	add r0, r4, #0
	mov r2, #0x27
	bl FUN_0200C13C
	bl FUN_0207C2C4
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _02216930 ; =0x0000B00D
	ldr r1, _0221692C ; =0x00001FB4
	str r0, [sp, #8]
	ldr r1, [r5, r1]
	add r0, r4, #0
	mov r2, #0x27
	bl FUN_0200C00C
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_02216928: .word 0x0000B008
_0221692C: .word 0x00001FB4
_02216930: .word 0x0000B00D

	thumb_func_start MOD09_02216934
MOD09_02216934: ; 0x02216934
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl MOD11_02230078
	add r6, r0, #0
	mov r0, #2
	str r0, [sp]
	ldr r0, _0221699C ; =0x0000B009
	ldr r3, _022169A0 ; =0x00001FB4
	str r0, [sp, #4]
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r3, [r5, r3]
	mov r1, #3
	add r2, r6, #0
	bl FUN_0206E198
	ldr r1, _022169A0 ; =0x00001FB4
	ldr r2, _0221699C ; =0x0000B009
	ldr r1, [r5, r1]
	add r0, r6, #0
	add r3, r2, #0
	bl FUN_0206E1D4
	ldr r4, _022169A4 ; =0x0000B00E
	add r7, r4, #6
_02216970:
	ldr r1, _022169A0 ; =0x00001FB4
	str r4, [sp]
	ldr r1, [r5, r1]
	add r0, r6, #0
	mov r2, #2
	mov r3, #0
	bl FUN_0206E130
	add r4, r4, #1
	cmp r4, r7
	bls _02216970
	ldr r0, _022169A8 ; =0x0000B015
	ldr r1, _022169A0 ; =0x00001FB4
	str r0, [sp]
	ldr r1, [r5, r1]
	add r0, r6, #0
	mov r2, #2
	mov r3, #0
	bl FUN_0206E2AC
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0221699C: .word 0x0000B009
_022169A0: .word 0x00001FB4
_022169A4: .word 0x0000B00E
_022169A8: .word 0x0000B015

	thumb_func_start MOD09_022169AC
MOD09_022169AC: ; 0x022169AC
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl MOD11_02230078
	add r4, r0, #0
	bl FUN_020724C8
	mov r1, #0x14
	str r1, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _02216A40 ; =0x0000B00A
	ldr r3, _02216A44 ; =0x00001FB4
	str r0, [sp, #0x14]
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r3, [r5, r3]
	mov r1, #3
	add r2, r4, #0
	bl FUN_0200C0DC
	bl FUN_020724CC
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _02216A40 ; =0x0000B00A
	ldr r1, _02216A44 ; =0x00001FB4
	str r0, [sp, #4]
	ldr r1, [r5, r1]
	add r0, r4, #0
	mov r2, #0x14
	bl FUN_0200C124
	bl FUN_020724D0
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _02216A40 ; =0x0000B00A
	ldr r1, _02216A44 ; =0x00001FB4
	str r0, [sp, #4]
	ldr r1, [r5, r1]
	add r0, r4, #0
	mov r2, #0x14
	bl FUN_0200C13C
	bl FUN_020724C4
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _02216A48 ; =0x0000B016
	ldr r1, _02216A44 ; =0x00001FB4
	str r0, [sp, #8]
	ldr r1, [r5, r1]
	add r0, r4, #0
	mov r2, #0x14
	bl FUN_0200C00C
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_02216A40: .word 0x0000B00A
_02216A44: .word 0x00001FB4
_02216A48: .word 0x0000B016

	thumb_func_start MOD09_02216A4C
MOD09_02216A4C: ; 0x02216A4C
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl MOD11_02230078
	add r4, r0, #0
	mov r0, #0x48
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _02216AD0 ; =0x0000B00B
	ldr r3, _02216AD4 ; =0x00001FB4
	str r0, [sp, #0x14]
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r3, [r5, r3]
	mov r1, #3
	add r2, r4, #0
	bl FUN_0200C0DC
	mov r0, #0
	str r0, [sp]
	ldr r0, _02216AD0 ; =0x0000B00B
	ldr r1, _02216AD4 ; =0x00001FB4
	str r0, [sp, #4]
	ldr r1, [r5, r1]
	add r0, r4, #0
	mov r2, #0x48
	mov r3, #0x19
	bl FUN_0200C124
	mov r0, #0
	str r0, [sp]
	ldr r0, _02216AD0 ; =0x0000B00B
	ldr r1, _02216AD4 ; =0x00001FB4
	str r0, [sp, #4]
	ldr r1, [r5, r1]
	add r0, r4, #0
	mov r2, #0x48
	mov r3, #0x18
	bl FUN_0200C13C
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _02216AD8 ; =0x0000B017
	ldr r1, _02216AD4 ; =0x00001FB4
	str r0, [sp, #8]
	ldr r1, [r5, r1]
	add r0, r4, #0
	mov r2, #0x48
	mov r3, #0x1a
	bl FUN_0200C00C
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_02216AD0: .word 0x0000B00B
_02216AD4: .word 0x00001FB4
_02216AD8: .word 0x0000B017

	thumb_func_start MOD09_02216ADC
MOD09_02216ADC: ; 0x02216ADC
	push {r4, r5, lr}
	sub sp, #0x34
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	ldr r0, [r0, #8]
	bl MOD11_02230078
	mov r2, #0
	add r1, sp, #0
	strh r2, [r1]
	strh r2, [r1, #2]
	strh r2, [r1, #4]
	strh r2, [r1, #6]
	mov r1, #0x14
	ldr r3, _02216B34 ; =0x0221B6F0
	mul r1, r4
	ldr r3, [r3, r1]
	str r2, [sp, #0xc]
	str r3, [sp, #8]
	mov r3, #2
	str r3, [sp, #0x10]
	ldr r3, _02216B38 ; =0x0221B6E0
	str r2, [sp, #0x30]
	ldr r3, [r3, r1]
	add r2, sp, #0
	str r3, [sp, #0x14]
	ldr r3, _02216B3C ; =0x0221B6E4
	ldr r3, [r3, r1]
	str r3, [sp, #0x18]
	ldr r3, _02216B40 ; =0x0221B6E8
	ldr r3, [r3, r1]
	str r3, [sp, #0x1c]
	ldr r3, _02216B44 ; =0x0221B6EC
	ldr r1, [r3, r1]
	str r1, [sp, #0x20]
	mov r1, #1
	str r1, [sp, #0x2c]
	ldr r1, _02216B48 ; =0x00001FB4
	ldr r1, [r5, r1]
	bl FUN_0200C154
	add sp, #0x34
	pop {r4, r5, pc}
	.align 2, 0
_02216B34: .word MOD9_0221B6F0
_02216B38: .word MOD9_0221B6E0
_02216B3C: .word MOD9_0221B6E4
_02216B40: .word MOD9_0221B6E8
_02216B44: .word MOD9_0221B6EC
_02216B48: .word 0x00001FB4

	thumb_func_start MOD09_02216B4C
MOD09_02216B4C: ; 0x02216B4C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r7, _02216B70 ; =0x00001FB8
	mov r4, #0
	add r5, r6, #0
_02216B56:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD09_02216ADC
	str r0, [r5, r7]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x26
	blo _02216B56
	add r0, r6, #0
	bl MOD09_02216BD0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02216B70: .word 0x00001FB8

	thumb_func_start MOD09_02216B74
MOD09_02216B74: ; 0x02216B74
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r0, [r7]
	ldr r0, [r0, #8]
	bl MOD11_02230078
	ldr r6, _02216BA8 ; =0x00001FB8
	str r0, [sp]
	mov r4, #0
	add r5, r7, #0
_02216B88:
	ldr r0, [r5, r6]
	bl FUN_0200C3DC
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x26
	blo _02216B88
	add r0, r7, #0
	bl MOD09_022177B4
	ldr r1, _02216BAC ; =0x00001FB4
	ldr r0, [sp]
	ldr r1, [r7, r1]
	bl FUN_0200C398
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02216BA8: .word 0x00001FB8
_02216BAC: .word 0x00001FB4

	thumb_func_start MOD09_02216BB0
MOD09_02216BB0: ; 0x02216BB0
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	mov r1, #1
	add r6, r0, #0
	bl FUN_0200C644
	lsl r1, r5, #0x10
	lsl r2, r4, #0x10
	add r0, r6, #0
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD09_02216BD0
MOD09_02216BD0: ; 0x02216BD0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r5, #0
	mov r7, #0
	add r4, #0x1b
	add r6, r5, #0
_02216BDC:
	ldrh r0, [r5, #8]
	cmp r0, #0
	beq _02216BFC
	add r1, r5, #0
	ldrb r2, [r4]
	add r1, #0x32
	ldrb r1, [r1]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1f
	bl FUN_0206B7BC
	add r1, r0, #0
	ldr r0, _02216C0C ; =0x00001FD4
	ldr r0, [r6, r0]
	bl FUN_0200C66C
_02216BFC:
	add r7, r7, #1
	add r5, #0x50
	add r4, #0x50
	add r6, r6, #4
	cmp r7, #6
	blt _02216BDC
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02216C0C: .word 0x00001FD4

	thumb_func_start MOD09_02216C10
MOD09_02216C10: ; 0x02216C10
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5]
	add r6, r3, #0
	ldr r0, [r0, #8]
	add r7, r1, #0
	add r4, r2, #0
	bl MOD11_02230078
	str r0, [sp, #8]
	bl FUN_0206E12C
	str r0, [sp, #0xc]
	add r0, r6, #0
	bl FUN_0206E0F0
	add r3, r0, #0
	mov r0, #1
	str r0, [sp]
	ldr r1, _02216C5C ; =0x00001FB4
	str r4, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, [r5, r1]
	ldr r2, [sp, #0xc]
	bl FUN_0200C9D8
	add r0, r6, #0
	bl FUN_0206E114
	add r1, r0, #0
	add r0, r7, #0
	add r1, r1, #4
	bl FUN_0200C66C
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02216C5C: .word 0x00001FB4

	thumb_func_start MOD09_02216C60
MOD09_02216C60: ; 0x02216C60
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r2, #0
	ldr r0, [r0, #8]
	add r6, r1, #0
	bl MOD11_02230078
	add r7, r0, #0
	bl FUN_0206E2A8
	str r0, [sp, #8]
	add r0, r4, #0
	bl FUN_0206E278
	add r3, r0, #0
	mov r0, #1
	str r0, [sp]
	ldr r0, _02216CAC ; =0x0000B015
	ldr r1, _02216CB0 ; =0x00001FB4
	str r0, [sp, #4]
	ldr r1, [r5, r1]
	ldr r2, [sp, #8]
	add r0, r7, #0
	bl FUN_0200C9D8
	add r0, r4, #0
	bl FUN_0206E290
	add r1, r0, #0
	add r0, r6, #0
	add r1, r1, #4
	bl FUN_0200C66C
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02216CAC: .word 0x0000B015
_02216CB0: .word 0x00001FB4

	thumb_func_start MOD09_02216CB4
MOD09_02216CB4: ; 0x02216CB4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r5, r1, #0
	add r4, r2, #0
	add r7, r3, #0
	cmp r6, #7
	beq _02216CD4
	add r0, r5, #0
	add r1, r6, #0
	bl FUN_0200C5C0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r7, #0
	bl MOD09_02216BB0
_02216CD4:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD09_02216CD8
MOD09_02216CD8: ; 0x02216CD8
	push {r4, r5, r6, lr}
	add r4, r1, #0
	ldr r1, _02216D1C ; =0x00002004
	add r5, r0, #0
	add r6, r2, #0
	ldrb r3, [r4, #0x14]
	ldr r1, [r5, r1]
	ldr r2, _02216D20 ; =0x0000B00E
	bl MOD09_02216C10
	ldr r0, _02216D1C ; =0x00002004
	ldr r1, [r6]
	ldr r0, [r5, r0]
	ldr r2, [r6, #4]
	bl MOD09_02216BB0
	ldrb r3, [r4, #0x15]
	ldrb r0, [r4, #0x14]
	cmp r0, r3
	beq _02216D18
	ldr r1, _02216D24 ; =0x00002008
	ldr r2, _02216D28 ; =0x0000B00F
	ldr r1, [r5, r1]
	add r0, r5, #0
	bl MOD09_02216C10
	ldr r0, _02216D24 ; =0x00002008
	ldr r1, [r6, #8]
	ldr r0, [r5, r0]
	ldr r2, [r6, #0xc]
	bl MOD09_02216BB0
_02216D18:
	pop {r4, r5, r6, pc}
	nop
_02216D1C: .word 0x00002004
_02216D20: .word 0x0000B00E
_02216D24: .word 0x00002008
_02216D28: .word 0x0000B00F

	thumb_func_start MOD09_02216D2C
MOD09_02216D2C: ; 0x02216D2C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	add r6, r3, #0
	cmp r0, #0
	beq _02216D5C
	bl ItemIdIsMail
	cmp r0, #1
	bne _02216D4A
	add r0, r5, #0
	mov r1, #1
	bl FUN_0200C5C0
	b _02216D52
_02216D4A:
	add r0, r5, #0
	mov r1, #0
	bl FUN_0200C5C0
_02216D52:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD09_02216BB0
_02216D5C:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD09_02216D60
MOD09_02216D60: ; 0x02216D60
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	add r6, r3, #0
	cmp r0, #0
	beq _02216D7E
	add r0, r5, #0
	mov r1, #2
	bl FUN_0200C5C0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD09_02216BB0
_02216D7E:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD09_02216D80
MOD09_02216D80: ; 0x02216D80
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r7, _02216E14 ; =0x00001FB8
	str r1, [sp]
	mov r5, #0
	add r4, r6, #0
_02216D8C:
	ldr r0, [r4, r7]
	mov r1, #0
	bl FUN_0200C644
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #0x26
	blo _02216D8C
	ldr r0, [sp]
	cmp r0, #9
	bhi _02216E10
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02216DAE: ; jump table
	.short _02216DC2 - _02216DAE - 2 ; case 0
	.short _02216DCA - _02216DAE - 2 ; case 1
	.short _02216DD2 - _02216DAE - 2 ; case 2
	.short _02216DDA - _02216DAE - 2 ; case 3
	.short _02216DE2 - _02216DAE - 2 ; case 4
	.short _02216DEA - _02216DAE - 2 ; case 5
	.short _02216DF2 - _02216DAE - 2 ; case 6
	.short _02216DFA - _02216DAE - 2 ; case 7
	.short _02216E02 - _02216DAE - 2 ; case 8
	.short _02216E0A - _02216DAE - 2 ; case 9
_02216DC2:
	add r0, r6, #0
	bl MOD09_02216E18
	pop {r3, r4, r5, r6, r7, pc}
_02216DCA:
	add r0, r6, #0
	bl MOD09_02216EB4
	pop {r3, r4, r5, r6, r7, pc}
_02216DD2:
	add r0, r6, #0
	bl MOD09_02216F0C
	pop {r3, r4, r5, r6, r7, pc}
_02216DDA:
	add r0, r6, #0
	bl MOD09_02216FA4
	pop {r3, r4, r5, r6, r7, pc}
_02216DE2:
	add r0, r6, #0
	bl MOD09_0221707C
	pop {r3, r4, r5, r6, r7, pc}
_02216DEA:
	add r0, r6, #0
	bl MOD09_02217270
	pop {r3, r4, r5, r6, r7, pc}
_02216DF2:
	add r0, r6, #0
	bl MOD09_02217140
	pop {r3, r4, r5, r6, r7, pc}
_02216DFA:
	add r0, r6, #0
	bl MOD09_022171AC
	pop {r3, r4, r5, r6, r7, pc}
_02216E02:
	add r0, r6, #0
	bl MOD09_02217354
	pop {r3, r4, r5, r6, r7, pc}
_02216E0A:
	add r0, r6, #0
	bl MOD09_022172DC
_02216E10:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02216E14: .word 0x00001FB8

	thumb_func_start MOD09_02216E18
MOD09_02216E18: ; 0x02216E18
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	mov r0, #0
	str r0, [sp, #4]
	add r0, r6, #0
	str r0, [sp]
	add r0, #0x1b
	ldr r4, _02216E9C ; =0x0221B5D0
	ldr r7, _02216EA0 ; =0x0221B600
	add r5, r6, #0
	str r0, [sp]
_02216E30:
	ldrh r0, [r6, #8]
	cmp r0, #0
	beq _02216E7E
	ldr r0, _02216EA4 ; =0x00001FD4
	ldr r1, [r4]
	ldr r0, [r5, r0]
	ldr r2, [r4, #4]
	bl MOD09_02216BB0
	ldr r0, [sp]
	ldr r1, _02216EA8 ; =0x00001FEC
	ldrb r0, [r0]
	ldr r1, [r5, r1]
	ldr r2, [r7]
	lsl r0, r0, #0x19
	ldr r3, [r7, #4]
	lsr r0, r0, #0x1c
	bl MOD09_02216CB4
	ldr r1, _02216EAC ; =0x00001FB8
	ldr r2, [r4]
	ldr r3, [r4, #4]
	ldrh r0, [r6, #0x1e]
	ldr r1, [r5, r1]
	add r2, #8
	add r3, #8
	bl MOD09_02216D2C
	add r0, r6, #0
	add r0, #0x31
	ldr r1, _02216EB0 ; =0x00002038
	ldr r2, [r4]
	ldr r3, [r4, #4]
	ldrb r0, [r0]
	ldr r1, [r5, r1]
	add r2, #0x10
	add r3, #8
	bl MOD09_02216D60
_02216E7E:
	ldr r0, [sp]
	add r6, #0x50
	add r0, #0x50
	str r0, [sp]
	ldr r0, [sp, #4]
	add r4, #8
	add r0, r0, #1
	add r5, r5, #4
	add r7, #8
	str r0, [sp, #4]
	cmp r0, #6
	blt _02216E30
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02216E9C: .word MOD9_0221B5D0
_02216EA0: .word MOD9_0221B600
_02216EA4: .word 0x00001FD4
_02216EA8: .word 0x00001FEC
_02216EAC: .word 0x00001FB8
_02216EB0: .word 0x00002038

	thumb_func_start MOD09_02216EB4
MOD09_02216EB4: ; 0x02216EB4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r1, r5, #4
	ldrb r2, [r0, #0x11]
	mov r0, #0x50
	mul r0, r2
	add r4, r1, r0
	add r0, r2, #7
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, _02216F08 ; =0x00001FB8
	mov r2, #0x48
	ldr r0, [r1, r0]
	mov r1, #0x80
	bl MOD09_02216BB0
	ldr r1, [r5]
	ldrh r0, [r4, #0x1a]
	ldrb r1, [r1, #0x11]
	mov r3, #0x50
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _02216F08 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0x88
	bl MOD09_02216D2C
	ldr r1, [r5]
	add r4, #0x2d
	ldrb r1, [r1, #0x11]
	ldrb r0, [r4]
	mov r3, #0x50
	add r1, #0x20
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _02216F08 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0x90
	bl MOD09_02216D60
	pop {r3, r4, r5, pc}
	.align 2, 0
_02216F08: .word 0x00001FB8

	thumb_func_start MOD09_02216F0C
MOD09_02216F0C: ; 0x02216F0C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r1, r5, #4
	ldrb r2, [r0, #0x11]
	mov r0, #0x50
	mul r0, r2
	add r4, r1, r0
	add r0, r2, #7
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, _02216F98 ; =0x00001FB8
	mov r2, #0xc
	ldr r0, [r1, r0]
	mov r1, #0x18
	bl MOD09_02216BB0
	ldr r1, [r5]
	ldrb r0, [r4, #0x17]
	ldrb r1, [r1, #0x11]
	mov r3, #0x14
	lsl r0, r0, #0x19
	add r1, #0xd
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _02216F98 ; =0x00001FB8
	lsr r0, r0, #0x1c
	ldr r1, [r2, r1]
	mov r2, #0xc6
	bl MOD09_02216CB4
	ldr r2, _02216F9C ; =0x0221B490
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02216CD8
	ldr r1, [r5]
	ldrh r0, [r4, #0x1a]
	ldrb r1, [r1, #0x11]
	mov r3, #0x14
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _02216F98 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0x20
	bl MOD09_02216D2C
	ldr r1, [r5]
	add r0, r4, #0
	ldrb r1, [r1, #0x11]
	add r0, #0x2d
	ldrb r0, [r0]
	add r1, #0x20
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _02216F98 ; =0x00001FB8
	mov r3, #0x14
	ldr r1, [r2, r1]
	mov r2, #0x28
	bl MOD09_02216D60
	ldr r1, _02216FA0 ; =0x00001FD0
	ldrh r0, [r4, #0x1a]
	ldr r1, [r5, r1]
	mov r2, #0x14
	mov r3, #0x84
	bl MOD09_02216D2C
	pop {r3, r4, r5, pc}
	nop
_02216F98: .word 0x00001FB8
_02216F9C: .word MOD9_0221B490
_02216FA0: .word 0x00001FD0

	thumb_func_start MOD09_02216FA4
MOD09_02216FA4: ; 0x02216FA4
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	ldr r0, [r0]
	ldrb r2, [r0, #0x11]
	ldr r0, [sp]
	add r1, r0, #4
	mov r0, #0x50
	mul r0, r2
	add r4, r1, r0
	add r0, r2, #7
	lsl r1, r0, #2
	ldr r0, [sp]
	mov r2, #0xc
	add r1, r0, r1
	ldr r0, _02217068 ; =0x00001FB8
	ldr r0, [r1, r0]
	mov r1, #0x18
	bl MOD09_02216BB0
	ldr r1, [sp]
	ldrb r0, [r4, #0x17]
	ldr r1, [r1]
	mov r3, #0x14
	ldrb r1, [r1, #0x11]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1c
	add r1, #0xd
	lsl r2, r1, #2
	ldr r1, [sp]
	add r2, r1, r2
	ldr r1, _02217068 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0xc6
	bl MOD09_02216CB4
	ldr r0, [sp]
	ldr r2, _0221706C ; =0x0221B470
	add r1, r4, #0
	bl MOD09_02216CD8
	ldr r1, [sp]
	ldrh r0, [r4, #0x1a]
	ldr r1, [r1]
	mov r3, #0x14
	ldrb r1, [r1, #0x11]
	lsl r2, r1, #2
	ldr r1, [sp]
	add r2, r1, r2
	ldr r1, _02217068 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0x20
	bl MOD09_02216D2C
	ldr r1, [sp]
	add r0, r4, #0
	ldr r1, [r1]
	add r0, #0x2d
	ldrb r1, [r1, #0x11]
	ldrb r0, [r0]
	mov r3, #0x14
	add r1, #0x20
	lsl r2, r1, #2
	ldr r1, [sp]
	add r2, r1, r2
	ldr r1, _02217068 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0x28
	bl MOD09_02216D60
	ldr r5, [sp]
	ldr r6, _02217070 ; =0x0221B4F0
	mov r7, #0
_02217034:
	ldrh r0, [r4, #0x30]
	cmp r0, #0
	beq _0221705A
	add r3, r4, #0
	ldr r1, _02217074 ; =0x0000200C
	add r3, #0x34
	ldr r2, _02217078 ; =0x0000B010
	ldrb r3, [r3]
	ldr r0, [sp]
	ldr r1, [r5, r1]
	add r2, r7, r2
	bl MOD09_02216C10
	ldr r0, _02217074 ; =0x0000200C
	ldr r1, [r6]
	ldr r0, [r5, r0]
	ldr r2, [r6, #4]
	bl MOD09_02216BB0
_0221705A:
	add r7, r7, #1
	add r4, #8
	add r5, r5, #4
	add r6, #8
	cmp r7, #4
	blo _02217034
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02217068: .word 0x00001FB8
_0221706C: .word MOD9_0221B470
_02217070: .word MOD9_0221B4F0
_02217074: .word 0x0000200C
_02217078: .word 0x0000B010

	thumb_func_start MOD09_0221707C
MOD09_0221707C: ; 0x0221707C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r1, r5, #4
	ldrb r2, [r0, #0x11]
	mov r0, #0x50
	mul r0, r2
	add r4, r1, r0
	add r0, r2, #7
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, _02217134 ; =0x00001FB8
	mov r2, #0xc
	ldr r0, [r1, r0]
	mov r1, #0x18
	bl MOD09_02216BB0
	ldr r1, [r5]
	ldrb r0, [r4, #0x17]
	ldrb r1, [r1, #0x11]
	mov r3, #0x14
	lsl r0, r0, #0x19
	add r1, #0xd
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _02217134 ; =0x00001FB8
	lsr r0, r0, #0x1c
	ldr r1, [r2, r1]
	mov r2, #0xc6
	bl MOD09_02216CB4
	ldr r2, _02217138 ; =0x0221B480
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02216CD8
	ldr r0, [r5]
	mov r2, #0x30
	add r0, #0x34
	ldrb r0, [r0]
	add r0, #0x15
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, _02217134 ; =0x00001FB8
	ldr r0, [r1, r0]
	mov r1, #0x88
	bl MOD09_02216BB0
	ldr r1, [r5]
	ldrh r0, [r4, #0x1a]
	ldrb r1, [r1, #0x11]
	mov r3, #0x14
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _02217134 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0x20
	bl MOD09_02216D2C
	ldr r1, [r5]
	add r0, r4, #0
	ldrb r1, [r1, #0x11]
	add r0, #0x2d
	ldrb r0, [r0]
	add r1, #0x20
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _02217134 ; =0x00001FB8
	mov r3, #0x14
	ldr r1, [r2, r1]
	mov r2, #0x28
	bl MOD09_02216D60
	ldr r2, [r5]
	ldr r1, _0221713C ; =0x00002020
	add r2, #0x34
	ldrb r2, [r2]
	ldr r1, [r5, r1]
	add r0, r5, #0
	lsl r2, r2, #3
	add r2, r4, r2
	add r2, #0x35
	ldrb r2, [r2]
	bl MOD09_02216C60
	ldr r0, _0221713C ; =0x00002020
	mov r1, #0x18
	ldr r0, [r5, r0]
	mov r2, #0x58
	bl MOD09_02216BB0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02217134: .word 0x00001FB8
_02217138: .word MOD9_0221B480
_0221713C: .word 0x00002020

	thumb_func_start MOD09_02217140
MOD09_02217140: ; 0x02217140
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r1, r5, #4
	ldrb r2, [r0, #0x11]
	mov r0, #0x50
	mul r0, r2
	add r4, r1, r0
	add r0, r2, #7
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, _022171A4 ; =0x00001FB8
	mov r2, #0xc
	ldr r0, [r1, r0]
	mov r1, #0x18
	bl MOD09_02216BB0
	ldr r2, _022171A8 ; =0x0221B460
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02216CD8
	ldr r1, [r5]
	ldrh r0, [r4, #0x1a]
	ldrb r1, [r1, #0x11]
	mov r3, #0x14
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _022171A4 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0x20
	bl MOD09_02216D2C
	ldr r1, [r5]
	add r4, #0x2d
	ldrb r1, [r1, #0x11]
	ldrb r0, [r4]
	mov r3, #0x14
	add r1, #0x20
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _022171A4 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0x28
	bl MOD09_02216D60
	add r0, r5, #0
	bl MOD09_022174EC
	pop {r3, r4, r5, pc}
	.align 2, 0
_022171A4: .word 0x00001FB8
_022171A8: .word MOD9_0221B460

	thumb_func_start MOD09_022171AC
MOD09_022171AC: ; 0x022171AC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r1, r5, #4
	ldrb r2, [r0, #0x11]
	mov r0, #0x50
	mul r0, r2
	add r4, r1, r0
	add r0, r2, #7
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, _02217264 ; =0x00001FB8
	mov r2, #0xc
	ldr r0, [r1, r0]
	mov r1, #0x18
	bl MOD09_02216BB0
	ldr r2, _02217268 ; =0x0221B450
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02216CD8
	ldr r0, [r5]
	mov r2, #0x30
	add r0, #0x34
	ldrb r0, [r0]
	add r0, #0x15
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, _02217264 ; =0x00001FB8
	ldr r0, [r1, r0]
	mov r1, #0x88
	bl MOD09_02216BB0
	ldr r1, [r5]
	ldrh r0, [r4, #0x1a]
	ldrb r1, [r1, #0x11]
	mov r3, #0x14
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _02217264 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0x20
	bl MOD09_02216D2C
	ldr r1, [r5]
	add r0, r4, #0
	ldrb r1, [r1, #0x11]
	add r0, #0x2d
	ldrb r0, [r0]
	add r1, #0x20
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _02217264 ; =0x00001FB8
	mov r3, #0x14
	ldr r1, [r2, r1]
	mov r2, #0x28
	bl MOD09_02216D60
	ldr r1, [r5]
	add r0, r1, #0
	add r0, #0x34
	ldrb r2, [r0]
	cmp r2, #4
	bhs _02217242
	lsl r2, r2, #3
	add r2, r4, r2
	ldr r1, _0221726C ; =0x00002020
	add r2, #0x35
	ldrb r2, [r2]
	ldr r1, [r5, r1]
	add r0, r5, #0
	bl MOD09_02216C60
	b _02217256
_02217242:
	ldrh r0, [r1, #0x24]
	mov r1, #1
	bl GetWazaAttr
	ldr r1, _0221726C ; =0x00002020
	add r2, r0, #0
	ldr r1, [r5, r1]
	add r0, r5, #0
	bl MOD09_02216C60
_02217256:
	ldr r0, _0221726C ; =0x00002020
	mov r1, #0x18
	ldr r0, [r5, r0]
	mov r2, #0x58
	bl MOD09_02216BB0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02217264: .word 0x00001FB8
_02217268: .word MOD9_0221B450
_0221726C: .word 0x00002020

	thumb_func_start MOD09_02217270
MOD09_02217270: ; 0x02217270
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r1, r5, #4
	ldrb r2, [r0, #0x11]
	mov r0, #0x50
	mul r0, r2
	add r4, r1, r0
	add r0, r2, #7
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, _022172D4 ; =0x00001FB8
	mov r2, #0xc
	ldr r0, [r1, r0]
	mov r1, #0x18
	bl MOD09_02216BB0
	ldr r2, _022172D8 ; =0x0221B460
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02216CD8
	ldr r1, [r5]
	ldrh r0, [r4, #0x1a]
	ldrb r1, [r1, #0x11]
	mov r3, #0x14
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _022172D4 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0x20
	bl MOD09_02216D2C
	ldr r1, [r5]
	add r4, #0x2d
	ldrb r1, [r1, #0x11]
	ldrb r0, [r4]
	mov r3, #0x14
	add r1, #0x20
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _022172D4 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0x28
	bl MOD09_02216D60
	add r0, r5, #0
	bl MOD09_022174EC
	pop {r3, r4, r5, pc}
	.align 2, 0
_022172D4: .word 0x00001FB8
_022172D8: .word MOD9_0221B460

	thumb_func_start MOD09_022172DC
MOD09_022172DC: ; 0x022172DC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r1, r5, #4
	ldrb r2, [r0, #0x11]
	mov r0, #0x50
	mul r0, r2
	add r4, r1, r0
	add r0, r2, #7
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, _02217350 ; =0x00001FB8
	mov r2, #0xc
	ldr r0, [r1, r0]
	mov r1, #0x18
	bl MOD09_02216BB0
	ldr r0, [r5]
	mov r2, #0x48
	add r0, #0x34
	ldrb r0, [r0]
	add r0, #0x15
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, _02217350 ; =0x00001FB8
	ldr r0, [r1, r0]
	mov r1, #0x88
	bl MOD09_02216BB0
	ldr r1, [r5]
	ldrh r0, [r4, #0x1a]
	ldrb r1, [r1, #0x11]
	mov r3, #0x14
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _02217350 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0x20
	bl MOD09_02216D2C
	ldr r1, [r5]
	add r4, #0x2d
	ldrb r1, [r1, #0x11]
	ldrb r0, [r4]
	mov r3, #0x14
	add r1, #0x20
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _02217350 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0x28
	bl MOD09_02216D60
	add r0, r5, #0
	bl MOD09_02217624
	pop {r3, r4, r5, pc}
	nop
_02217350: .word 0x00001FB8

	thumb_func_start MOD09_02217354
MOD09_02217354: ; 0x02217354
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r1, r5, #4
	ldrb r2, [r0, #0x11]
	mov r0, #0x50
	mul r0, r2
	add r4, r1, r0
	add r0, r2, #7
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, _022173B4 ; =0x00001FB8
	mov r2, #0xc
	ldr r0, [r1, r0]
	mov r1, #0x18
	bl MOD09_02216BB0
	ldr r1, [r5]
	ldrh r0, [r4, #0x1a]
	ldrb r1, [r1, #0x11]
	mov r3, #0x14
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _022173B4 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0x20
	bl MOD09_02216D2C
	ldr r1, [r5]
	add r4, #0x2d
	ldrb r1, [r1, #0x11]
	ldrb r0, [r4]
	mov r3, #0x14
	add r1, #0x20
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r1, _022173B4 ; =0x00001FB8
	ldr r1, [r2, r1]
	mov r2, #0x28
	bl MOD09_02216D60
	add r0, r5, #0
	bl MOD09_022174EC
	add r0, r5, #0
	bl MOD09_02217624
	pop {r3, r4, r5, pc}
	.align 2, 0
_022173B4: .word 0x00001FB8

	thumb_func_start MOD09_022173B8
MOD09_022173B8: ; 0x022173B8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6]
	add r2, r6, #4
	ldrb r1, [r0, #0x11]
	mov r0, #0x50
	mov r4, #0
	mul r0, r1
	add r0, r2, r0
	str r0, [sp]
_022173CC:
	ldr r0, [sp]
	lsl r5, r4, #3
	add r3, r0, r5
	ldrh r0, [r3, #0x30]
	cmp r0, #0
	beq _02217400
	lsl r0, r4, #2
	add r3, #0x34
	add r7, r6, r0
	ldr r1, _02217438 ; =0x0000200C
	ldr r2, _0221743C ; =0x0000B010
	ldrb r3, [r3]
	ldr r1, [r7, r1]
	add r0, r6, #0
	add r2, r4, r2
	bl MOD09_02216C10
	ldr r0, _02217440 ; =0x0221B5A8
	ldr r1, _02217440 ; =0x0221B5A8
	add r2, r0, r5
	ldr r0, _02217438 ; =0x0000200C
	ldr r1, [r1, r5]
	ldr r0, [r7, r0]
	ldr r2, [r2, #4]
	bl MOD09_02216BB0
_02217400:
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #4
	blo _022173CC
	ldr r0, [r6]
	ldrh r0, [r0, #0x24]
	cmp r0, #0
	beq _02217436
	mov r1, #3
	bl GetWazaAttr
	add r3, r0, #0
	ldr r1, _02217444 ; =0x0000201C
	lsl r3, r3, #0x18
	ldr r1, [r6, r1]
	ldr r2, _02217448 ; =0x0000B014
	add r0, r6, #0
	lsr r3, r3, #0x18
	bl MOD09_02216C10
	ldr r0, _02217444 ; =0x0000201C
	mov r1, #0x58
	ldr r0, [r6, r0]
	mov r2, #0xb0
	bl MOD09_02216BB0
_02217436:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02217438: .word 0x0000200C
_0221743C: .word 0x0000B010
_02217440: .word MOD9_0221B5A8
_02217444: .word 0x0000201C
_02217448: .word 0x0000B014

	thumb_func_start MOD09_0221744C
MOD09_0221744C: ; 0x0221744C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r0, [r7]
	add r2, r7, #4
	ldrb r1, [r0, #0x11]
	mov r0, #0x50
	mov r4, #0
	mul r0, r1
	add r0, r2, r0
	str r0, [sp]
_02217460:
	ldr r0, [sp]
	lsl r5, r4, #3
	add r0, r0, r5
	ldrh r0, [r0, #0x30]
	cmp r0, #0
	beq _0221749E
	lsl r1, r4, #2
	add r6, r7, r1
	mov r1, #0xb
	bl GetWazaAttr
	add r3, r0, #0
	ldr r1, _022174D8 ; =0x0000200C
	ldr r2, _022174DC ; =0x0000B010
	add r3, #0x12
	lsl r3, r3, #0x18
	ldr r1, [r6, r1]
	add r0, r7, #0
	add r2, r4, r2
	lsr r3, r3, #0x18
	bl MOD09_02216C10
	ldr r0, _022174E0 ; =0x0221B5A8
	ldr r1, _022174E0 ; =0x0221B5A8
	add r2, r0, r5
	ldr r0, _022174D8 ; =0x0000200C
	ldr r1, [r1, r5]
	ldr r0, [r6, r0]
	ldr r2, [r2, #4]
	bl MOD09_02216BB0
_0221749E:
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #4
	blo _02217460
	ldr r0, [r7]
	ldrh r0, [r0, #0x24]
	cmp r0, #0
	beq _022174D6
	mov r1, #0xb
	bl GetWazaAttr
	add r3, r0, #0
	ldr r1, _022174E4 ; =0x0000201C
	add r3, #0x12
	lsl r3, r3, #0x18
	ldr r1, [r7, r1]
	ldr r2, _022174E8 ; =0x0000B014
	add r0, r7, #0
	lsr r3, r3, #0x18
	bl MOD09_02216C10
	ldr r0, _022174E4 ; =0x0000201C
	mov r1, #0x58
	ldr r0, [r7, r0]
	mov r2, #0xb0
	bl MOD09_02216BB0
_022174D6:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022174D8: .word 0x0000200C
_022174DC: .word 0x0000B010
_022174E0: .word MOD9_0221B5A8
_022174E4: .word 0x0000201C
_022174E8: .word 0x0000B014

	thumb_func_start MOD09_022174EC
MOD09_022174EC: ; 0x022174EC
	push {r3, lr}
	ldr r1, _02217504 ; =0x00002077
	ldrb r1, [r0, r1]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	bne _022174FE
	bl MOD09_022173B8
	pop {r3, pc}
_022174FE:
	bl MOD09_0221744C
	pop {r3, pc}
	.align 2, 0
_02217504: .word 0x00002077

	thumb_func_start MOD09_02217508
MOD09_02217508: ; 0x02217508
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200C5CC
	cmp r4, r0
	beq _02217526
	add r0, r5, #0
	mov r1, #0
	bl FUN_0200C61C
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0200C5C0
_02217526:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD09_02217528
MOD09_02217528: ; 0x02217528
	push {r3, lr}
	add r2, r0, #0
	ldrh r0, [r2, #0x10]
	cmp r0, #0
	bne _02217536
	mov r0, #0
	pop {r3, pc}
_02217536:
	ldrb r1, [r2, #0x17]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x1c
	cmp r1, #7
	beq _02217548
	cmp r1, #6
	beq _02217548
	mov r0, #5
	pop {r3, pc}
_02217548:
	ldrh r1, [r2, #0x12]
	mov r2, #0x30
	bl FUN_02079A54
	cmp r0, #4
	bhi _0221757A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02217560: ; jump table
	.short _0221757A - _02217560 - 2 ; case 0
	.short _02217576 - _02217560 - 2 ; case 1
	.short _02217572 - _02217560 - 2 ; case 2
	.short _0221756E - _02217560 - 2 ; case 3
	.short _0221756A - _02217560 - 2 ; case 4
_0221756A:
	mov r0, #1
	pop {r3, pc}
_0221756E:
	mov r0, #2
	pop {r3, pc}
_02217572:
	mov r0, #3
	pop {r3, pc}
_02217576:
	mov r0, #4
	pop {r3, pc}
_0221757A:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD09_02217580
MOD09_02217580: ; 0x02217580
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	mov r4, #0
	ldr r0, [r0]
	bl GetPartyCount
	cmp r0, #0
	ble _022175D8
	add r7, r5, #4
_02217594:
	mov r0, #0x50
	add r1, r4, #0
	mul r1, r0
	add r0, r5, r1
	ldrh r0, [r0, #8]
	cmp r0, #0
	beq _022175C6
	add r0, r7, r1
	bl MOD09_02217528
	add r1, r0, #0
	lsl r0, r4, #2
	add r6, r5, r0
	ldr r0, _022175DC ; =0x00001FD4
	lsl r1, r1, #0x18
	ldr r0, [r6, r0]
	lsr r1, r1, #0x18
	bl MOD09_02217508
	ldr r0, _022175DC ; =0x00001FD4
	mov r1, #1
	ldr r0, [r6, r0]
	lsl r1, r1, #0xc
	bl FUN_0200C5B4
_022175C6:
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [r5]
	ldr r0, [r0]
	bl GetPartyCount
	cmp r4, r0
	blt _02217594
_022175D8:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022175DC: .word 0x00001FD4

	thumb_func_start MOD09_022175E0
MOD09_022175E0: ; 0x022175E0
	push {r4, lr}
	add r4, r2, #0
	cmp r4, r1
	ble _02217606
	add r0, #0x2c
	sub r1, r4, r1
	mul r1, r0
	lsl r0, r1, #0x10
	mov r1, #0x4b
	lsl r1, r1, #2
	bl _u32_div_f
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	sub r0, r4, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	pop {r4, pc}
_02217606:
	add r0, #0x2c
	sub r1, r1, r4
	mul r1, r0
	lsl r0, r1, #0x10
	mov r1, #0x4b
	lsl r1, r1, #2
	bl _u32_div_f
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, r4, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	pop {r4, pc}

	thumb_func_start MOD09_02217624
MOD09_02217624: ; 0x02217624
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6]
	add r5, r6, #4
	ldrb r1, [r0, #0x11]
	mov r0, #0x50
	add r4, r1, #0
	mul r4, r0
	ldr r0, _0221773C ; =0x00002024
	mov r1, #0
	ldr r0, [r6, r0]
	bl MOD09_02217508
	ldr r0, _02217740 ; =0x00002028
	mov r1, #1
	ldr r0, [r6, r0]
	bl MOD09_02217508
	ldr r0, _02217744 ; =0x0000202C
	mov r1, #3
	ldr r0, [r6, r0]
	bl MOD09_02217508
	ldr r0, _02217748 ; =0x00002030
	mov r1, #4
	ldr r0, [r6, r0]
	bl MOD09_02217508
	ldr r0, _0221774C ; =0x00002034
	mov r1, #2
	ldr r0, [r6, r0]
	bl MOD09_02217508
	add r0, r5, r4
	add r0, #0x28
	mov r1, #0x90
	ldrb r0, [r0]
	add r2, r1, #0
	bl MOD09_022175E0
	add r7, r0, #0
	add r0, r5, r4
	add r0, #0x28
	ldrb r0, [r0]
	mov r1, #2
	mov r2, #0x18
	bl MOD09_022175E0
	add r2, r0, #0
	ldr r0, _0221773C ; =0x00002024
	add r1, r7, #0
	ldr r0, [r6, r0]
	bl MOD09_02216BB0
	add r0, r5, r4
	add r0, #0x29
	ldrb r0, [r0]
	mov r1, #0xa7
	mov r2, #0x90
	bl MOD09_022175E0
	add r7, r0, #0
	add r0, r5, r4
	add r0, #0x29
	ldrb r0, [r0]
	mov r1, #0x12
	mov r2, #0x18
	bl MOD09_022175E0
	add r2, r0, #0
	ldr r0, _02217740 ; =0x00002028
	add r1, r7, #0
	ldr r0, [r6, r0]
	bl MOD09_02216BB0
	add r0, r5, r4
	add r0, #0x2a
	ldrb r0, [r0]
	mov r1, #0x9f
	mov r2, #0x90
	bl MOD09_022175E0
	add r7, r0, #0
	add r0, r5, r4
	add r0, #0x2a
	ldrb r0, [r0]
	mov r1, #0x2f
	mov r2, #0x18
	bl MOD09_022175E0
	add r2, r0, #0
	ldr r0, _02217744 ; =0x0000202C
	add r1, r7, #0
	ldr r0, [r6, r0]
	bl MOD09_02216BB0
	add r0, r5, r4
	add r0, #0x2b
	ldrb r0, [r0]
	mov r1, #0x80
	mov r2, #0x8f
	bl MOD09_022175E0
	add r7, r0, #0
	add r0, r5, r4
	add r0, #0x2b
	ldrb r0, [r0]
	mov r1, #0x2f
	mov r2, #0x18
	bl MOD09_022175E0
	add r2, r0, #0
	ldr r0, _02217748 ; =0x00002030
	add r1, r7, #0
	ldr r0, [r6, r0]
	bl MOD09_02216BB0
	add r0, r5, r4
	add r0, #0x2c
	ldrb r0, [r0]
	mov r1, #0x78
	mov r2, #0x8f
	bl MOD09_022175E0
	add r7, r0, #0
	add r0, r5, r4
	add r0, #0x2c
	ldrb r0, [r0]
	mov r1, #0x12
	mov r2, #0x18
	bl MOD09_022175E0
	add r2, r0, #0
	ldr r0, _0221774C ; =0x00002034
	add r1, r7, #0
	ldr r0, [r6, r0]
	bl MOD09_02216BB0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221773C: .word 0x00002024
_02217740: .word 0x00002028
_02217744: .word 0x0000202C
_02217748: .word 0x00002030
_0221774C: .word 0x00002034

	thumb_func_start MOD09_02217750
MOD09_02217750: ; 0x02217750
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl MOD11_02230078
	ldr r3, _022177A8 ; =0x0000B00C
	mov r2, #0x7a
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	ldr r1, _022177AC ; =0x00001FB4
	lsl r2, r2, #2
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	add r3, #0xc
	add r4, r0, #0
	bl MOD11_0225D3EC
	ldr r3, _022177A8 ; =0x0000B00C
	mov r0, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r1, _022177AC ; =0x00001FB4
	ldr r2, [r5]
	ldr r1, [r5, r1]
	ldr r2, [r2, #0xc]
	add r0, r4, #0
	add r3, #0xc
	bl MOD11_0225D484
	add r1, r0, #0
	ldr r0, _022177B0 ; =0x00002088
	ldr r0, [r5, r0]
	bl MOD09_0221AC30
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_022177A8: .word 0x0000B00C
_022177AC: .word 0x00001FB4
_022177B0: .word 0x00002088

	thumb_func_start MOD09_022177B4
MOD09_022177B4: ; 0x022177B4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, _022177DC ; =0x00002088
	ldr r0, [r4, r0]
	bl MOD09_0221AC24
	bl MOD11_0225D508
	ldr r2, _022177E0 ; =0x0000B00C
	ldr r0, _022177E4 ; =0x00001FB4
	str r2, [sp]
	add r1, r2, #0
	ldr r0, [r4, r0]
	add r1, #0xc
	add r3, r2, #0
	bl MOD11_0225D45C
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_022177DC: .word 0x00002088
_022177E0: .word 0x0000B00C
_022177E4: .word 0x00001FB4

	thumb_func_start MOD09_022177E8
MOD09_022177E8: ; 0x022177E8
	push {r3, lr}
	ldr r1, _0221780C ; =0x00002077
	ldrb r2, [r0, r1]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1c
	bne _02217800
	add r1, #0x11
	ldr r0, [r0, r1]
	mov r1, #0x5f
	bl MOD09_0221AC94
	pop {r3, pc}
_02217800:
	add r1, #0x11
	ldr r0, [r0, r1]
	mov r1, #0x7f
	bl MOD09_0221AC94
	pop {r3, pc}
	.align 2, 0
_0221780C: .word 0x00002077

	thumb_func_start MOD09_02217810
MOD09_02217810: ; 0x02217810
	push {r3, lr}
	ldr r1, _02217834 ; =0x00002077
	ldrb r2, [r0, r1]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1c
	bne _02217828
	add r1, #0x11
	ldr r0, [r0, r1]
	mov r1, #5
	bl MOD09_0221AC94
	pop {r3, pc}
_02217828:
	add r1, #0x11
	ldr r0, [r0, r1]
	mov r1, #7
	bl MOD09_0221AC94
	pop {r3, pc}
	.align 2, 0
_02217834: .word 0x00002077

	thumb_func_start MOD09_02217838
MOD09_02217838: ; 0x02217838
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldr r0, _022178D8 ; =0x00002088
	ldr r1, _022178DC ; =0x0221B558
	lsl r2, r5, #2
	ldr r0, [r4, r0]
	ldr r1, [r1, r2]
	bl MOD09_0221AC68
	cmp r5, #9
	bhi _022178D6
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221785C: ; jump table
	.short _02217870 - _0221785C - 2 ; case 0
	.short _0221788A - _0221785C - 2 ; case 1
	.short _022178D6 - _0221785C - 2 ; case 2
	.short _022178A0 - _0221785C - 2 ; case 3
	.short _022178A0 - _0221785C - 2 ; case 4
	.short _022178D6 - _0221785C - 2 ; case 5
	.short _022178B0 - _0221785C - 2 ; case 6
	.short _022178C4 - _0221785C - 2 ; case 7
	.short _022178B0 - _0221785C - 2 ; case 8
	.short _022178C4 - _0221785C - 2 ; case 9
_02217870:
	ldr r1, [r4]
	ldr r0, _022178D8 ; =0x00002088
	ldrb r1, [r1, #0x11]
	ldr r0, [r4, r0]
	bl MOD09_0221AC34
	ldr r0, _022178E0 ; =0x0000208C
	mov r1, #0
	strb r1, [r4, r0]
	ldr r0, [r4]
	add r0, #0x34
	strb r1, [r0]
	pop {r3, r4, r5, pc}
_0221788A:
	ldr r1, _022178D8 ; =0x00002088
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldrb r1, [r4, r1]
	bl MOD09_0221AC34
	ldr r0, [r4]
	mov r1, #0
	add r0, #0x34
	strb r1, [r0]
	pop {r3, r4, r5, pc}
_022178A0:
	ldr r1, [r4]
	ldr r0, _022178D8 ; =0x00002088
	add r1, #0x34
	ldrb r1, [r1]
	ldr r0, [r4, r0]
	bl MOD09_0221AC34
	pop {r3, r4, r5, pc}
_022178B0:
	add r0, r4, #0
	bl MOD09_022177E8
	ldr r1, _022178D8 ; =0x00002088
	ldr r0, [r4, r1]
	add r1, r1, #5
	ldrb r1, [r4, r1]
	bl MOD09_0221AC34
	pop {r3, r4, r5, pc}
_022178C4:
	add r0, r4, #0
	bl MOD09_02217810
	ldr r1, _022178D8 ; =0x00002088
	ldr r0, [r4, r1]
	add r1, r1, #6
	ldrb r1, [r4, r1]
	bl MOD09_0221AC34
_022178D6:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022178D8: .word 0x00002088
_022178DC: .word MOD9_0221B558
_022178E0: .word 0x0000208C

	thumb_func_start MOD09_022178E4
MOD09_022178E4: ; 0x022178E4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02217908 ; =0x00002088
	mov r1, #0
	ldr r0, [r4, r0]
	bl MOD09_0221AC2C
	ldr r0, _02217908 ; =0x00002088
	ldr r0, [r4, r0]
	bl MOD09_0221AC5C
	ldr r0, _02217908 ; =0x00002088
	ldr r0, [r4, r0]
	bl MOD09_0221AC24
	bl MOD11_0225D648
	pop {r4, pc}
	.align 2, 0
_02217908: .word 0x00002088

	thumb_func_start MOD09_0221790C
MOD09_0221790C: ; 0x0221790C
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0x7b
	lsl r0, r0, #2
	mov r2, #0
	add r0, r5, r0
	add r3, r2, #0
	add r4, r1, #0
	bl MOD09_02217CEC
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xab
	lsl r0, r0, #2
	mov r3, #6
	add r0, r5, r0
	add r1, r4, #0
	mov r2, #0
	str r3, [sp, #4]
	bl MOD09_02217CEC
	mov r0, #0x10
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0xdb
	lsl r0, r0, #2
	add r0, r5, r0
	add r1, r4, #0
	mov r2, #0
	mov r3, #0xc
	bl MOD09_02217CEC
	mov r0, #0x10
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	ldr r0, _02217BCC ; =0x0000042C
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x12
	bl MOD09_02217CEC
	mov r2, #0x10
	str r2, [sp]
	mov r0, #6
	str r0, [sp, #4]
	ldr r0, _02217BD0 ; =0x000004EC
	add r1, r4, #0
	add r0, r5, r0
	mov r3, #0
	bl MOD09_02217CEC
	ldr r0, _02217BD4 ; =0x000005AC
	mov r2, #0x10
	str r2, [sp]
	mov r3, #6
	add r0, r5, r0
	add r1, r4, #0
	str r3, [sp, #4]
	bl MOD09_02217CEC
	mov r2, #0x10
	str r2, [sp]
	mov r0, #6
	str r0, [sp, #4]
	ldr r0, _02217BD8 ; =0x0000066C
	add r1, r4, #0
	add r0, r5, r0
	mov r3, #0xc
	bl MOD09_02217CEC
	mov r2, #0x10
	str r2, [sp]
	mov r0, #6
	str r0, [sp, #4]
	ldr r0, _02217BDC ; =0x0000072C
	add r1, r4, #0
	add r0, r5, r0
	mov r3, #0x12
	bl MOD09_02217CEC
	mov r0, #0xd
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	ldr r0, _02217BE0 ; =0x000007EC
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x27
	bl MOD09_02217CEC
	mov r0, #0xd
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	ldr r0, _02217BE4 ; =0x0000086E
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x2c
	bl MOD09_02217CEC
	mov r2, #0xd
	str r2, [sp]
	mov r0, #5
	str r0, [sp, #4]
	mov r0, #0x8f
	lsl r0, r0, #4
	add r0, r5, r0
	add r1, r4, #0
	mov r3, #0x27
	bl MOD09_02217CEC
	mov r2, #0xd
	str r2, [sp]
	mov r0, #5
	str r0, [sp, #4]
	ldr r0, _02217BE8 ; =0x00000972
	add r1, r4, #0
	add r0, r5, r0
	mov r3, #0x2c
	bl MOD09_02217CEC
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02217BEC ; =0x000009F4
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x31
	bl MOD09_02217CEC
	ldr r0, _02217BF0 ; =0x00000A26
	mov r2, #5
	str r2, [sp]
	add r0, r5, r0
	add r1, r4, #0
	mov r3, #0x31
	str r2, [sp, #4]
	bl MOD09_02217CEC
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02217BF4 ; =0x00000A58
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0xa
	mov r3, #0x31
	bl MOD09_02217CEC
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02217BF8 ; =0x00000A8A
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0xf
	mov r3, #0x31
	bl MOD09_02217CEC
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02217BFC ; =0x00000ABC
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x36
	bl MOD09_02217CEC
	ldr r0, _02217C00 ; =0x00000AEE
	mov r2, #5
	str r2, [sp]
	add r0, r5, r0
	add r1, r4, #0
	mov r3, #0x36
	str r2, [sp, #4]
	bl MOD09_02217CEC
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0xb2
	lsl r0, r0, #4
	add r0, r5, r0
	add r1, r4, #0
	mov r2, #0xa
	mov r3, #0x36
	bl MOD09_02217CEC
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02217C04 ; =0x00000B52
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0xf
	mov r3, #0x36
	bl MOD09_02217CEC
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02217C08 ; =0x00000B84
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x1a
	mov r3, #0x18
	bl MOD09_02217CEC
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02217C0C ; =0x00000BB6
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x1a
	mov r3, #0x1d
	bl MOD09_02217CEC
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02217C10 ; =0x00000BE8
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x1a
	mov r3, #0x22
	bl MOD09_02217CEC
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02217C14 ; =0x00000C1A
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x1a
	mov r3, #0x27
	bl MOD09_02217CEC
	mov r0, #0x1a
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	mov r0, #0x6d
	lsl r0, r0, #6
	add r0, r5, r0
	add r1, r4, #0
	mov r2, #0
	mov r3, #0x18
	bl MOD09_02217CEC
	mov r0, #0x1a
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	ldr r0, _02217C18 ; =0x00001C44
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x1d
	bl MOD09_02217CEC
	mov r0, #0x1a
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	ldr r0, _02217C1C ; =0x00001D48
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x22
	bl MOD09_02217CEC
	mov r0, #9
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, _02217C20 ; =0x00001E4C
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x14
	mov r3, #0x31
	bl MOD09_02217CEC
	mov r0, #9
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, _02217C24 ; =0x00001E94
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x14
	mov r3, #0x35
	bl MOD09_02217CEC
	mov r0, #9
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, _02217C28 ; =0x00001EDC
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x14
	mov r3, #0x39
	bl MOD09_02217CEC
	mov r0, #5
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _02217C2C ; =0x00001F24
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x3b
	bl MOD09_02217CEC
	mov r2, #5
	str r2, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _02217C30 ; =0x00001F38
	add r1, r4, #0
	add r0, r5, r0
	mov r3, #0x3b
	bl MOD09_02217CEC
	mov r0, #5
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _02217C34 ; =0x00001F4C
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0xa
	mov r3, #0x3b
	bl MOD09_02217CEC
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_02217BCC: .word 0x0000042C
_02217BD0: .word 0x000004EC
_02217BD4: .word 0x000005AC
_02217BD8: .word 0x0000066C
_02217BDC: .word 0x0000072C
_02217BE0: .word 0x000007EC
_02217BE4: .word 0x0000086E
_02217BE8: .word 0x00000972
_02217BEC: .word 0x000009F4
_02217BF0: .word 0x00000A26
_02217BF4: .word 0x00000A58
_02217BF8: .word 0x00000A8A
_02217BFC: .word 0x00000ABC
_02217C00: .word 0x00000AEE
_02217C04: .word 0x00000B52
_02217C08: .word 0x00000B84
_02217C0C: .word 0x00000BB6
_02217C10: .word 0x00000BE8
_02217C14: .word 0x00000C1A
_02217C18: .word 0x00001C44
_02217C1C: .word 0x00001D48
_02217C20: .word 0x00001E4C
_02217C24: .word 0x00001E94
_02217C28: .word 0x00001EDC
_02217C2C: .word 0x00001F24
_02217C30: .word 0x00001F38
_02217C34: .word 0x00001F4C

	thumb_func_start MOD09_02217C38
MOD09_02217C38: ; 0x02217C38
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0x1e
	str r0, [sp]
	mov r0, #0x11
	str r0, [sp, #4]
	ldr r0, _02217CE0 ; =0x00000C4C
	mov r2, #0
	add r0, r5, r0
	add r3, r2, #0
	add r4, r1, #0
	bl MOD09_02217CEC
	mov r0, #0x1e
	str r0, [sp]
	ldr r0, _02217CE4 ; =0x00001048
	mov r3, #0x11
	add r0, r5, r0
	add r1, r4, #0
	mov r2, #0
	str r3, [sp, #4]
	bl MOD09_02217CEC
	mov r0, #0x1e
	str r0, [sp]
	mov r0, #0x11
	str r0, [sp, #4]
	ldr r0, _02217CE8 ; =0x00001444
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x22
	bl MOD09_02217CEC
	mov r0, #0x10
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0x61
	lsl r0, r0, #6
	add r0, r5, r0
	add r1, r4, #0
	mov r2, #0
	mov r3, #0x33
	bl MOD09_02217CEC
	mov r2, #0x10
	str r2, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0x19
	lsl r0, r0, #8
	add r0, r5, r0
	add r1, r4, #0
	mov r3, #0x33
	bl MOD09_02217CEC
	mov r0, #0x10
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0x67
	lsl r0, r0, #6
	add r0, r5, r0
	add r1, r4, #0
	mov r2, #0
	mov r3, #0x39
	bl MOD09_02217CEC
	mov r2, #0x10
	str r2, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0x6a
	lsl r0, r0, #6
	add r0, r5, r0
	add r1, r4, #0
	mov r3, #0x39
	bl MOD09_02217CEC
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_02217CE0: .word 0x00000C4C
_02217CE4: .word 0x00001048
_02217CE8: .word 0x00001444

	thumb_func_start MOD09_02217CEC
MOD09_02217CEC: ; 0x02217CEC
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	add r0, sp, #8
	mov lr, r3
	ldrb r3, [r0, #0x14]
	mov r6, #0
	mov ip, r3
	cmp r3, #0
	ble _02217D38
	ldrb r3, [r0, #0x10]
	lsl r2, r2, #1
	add r7, r1, r2
_02217D04:
	mov r2, #0
	cmp r3, #0
	ble _02217D2C
	mov r0, lr
	add r0, r0, r6
	lsl r0, r0, #6
	add r5, r7, r0
	add r0, r6, #0
	mul r0, r3
	lsl r1, r0, #1
	ldr r0, [sp]
	add r4, r0, r1
_02217D1C:
	lsl r1, r2, #1
	ldrh r0, [r5, r1]
	strh r0, [r4, r1]
	add r0, r2, #1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	cmp r2, r3
	blt _02217D1C
_02217D2C:
	add r0, r6, #1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	mov r0, ip
	cmp r6, r0
	blt _02217D04
_02217D38:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD09_02217D3C
MOD09_02217D3C: ; 0x02217D3C
	cmp r1, #0x21
	bhi _02217E22
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02217D4C: ; jump table
	.short _02217D90 - _02217D4C - 2 ; case 0
	.short _02217D90 - _02217D4C - 2 ; case 1
	.short _02217D90 - _02217D4C - 2 ; case 2
	.short _02217D90 - _02217D4C - 2 ; case 3
	.short _02217D90 - _02217D4C - 2 ; case 4
	.short _02217D90 - _02217D4C - 2 ; case 5
	.short _02217DAE - _02217D4C - 2 ; case 6
	.short _02217DBA - _02217D4C - 2 ; case 7
	.short _02217DC8 - _02217D4C - 2 ; case 8
	.short _02217DC8 - _02217D4C - 2 ; case 9
	.short _02217DC8 - _02217D4C - 2 ; case 10
	.short _02217DC8 - _02217D4C - 2 ; case 11
	.short _02217DD4 - _02217D4C - 2 ; case 12
	.short _02217DE0 - _02217D4C - 2 ; case 13
	.short _02217DEC - _02217D4C - 2 ; case 14
	.short _02217DEC - _02217D4C - 2 ; case 15
	.short _02217DEC - _02217D4C - 2 ; case 16
	.short _02217DEC - _02217D4C - 2 ; case 17
	.short _02217E0A - _02217D4C - 2 ; case 18
	.short _02217DEC - _02217D4C - 2 ; case 19
	.short _02217DEC - _02217D4C - 2 ; case 20
	.short _02217DEC - _02217D4C - 2 ; case 21
	.short _02217DEC - _02217D4C - 2 ; case 22
	.short _02217DEC - _02217D4C - 2 ; case 23
	.short _02217DEC - _02217D4C - 2 ; case 24
	.short _02217DEC - _02217D4C - 2 ; case 25
	.short _02217DEC - _02217D4C - 2 ; case 26
	.short _02217DEC - _02217D4C - 2 ; case 27
	.short _02217DFA - _02217D4C - 2 ; case 28
	.short _02217DFA - _02217D4C - 2 ; case 29
	.short _02217E16 - _02217D4C - 2 ; case 30
	.short _02217E16 - _02217D4C - 2 ; case 31
	.short _02217E16 - _02217D4C - 2 ; case 32
	.short _02217E16 - _02217D4C - 2 ; case 33
_02217D90:
	cmp r3, #0
	bne _02217DA2
	mov r1, #0x7b
	lsl r1, r1, #2
	add r1, r0, r1
	mov r0, #0xc0
	mul r0, r2
	add r0, r1, r0
	bx lr
_02217DA2:
	ldr r1, _02217E28 ; =0x000004EC
	add r1, r0, r1
	mov r0, #0xc0
	mul r0, r2
	add r0, r1, r0
	bx lr
_02217DAE:
	ldr r1, _02217E2C ; =0x00000B84
	add r1, r0, r1
	mov r0, #0x32
	mul r0, r2
	add r0, r1, r0
	bx lr
_02217DBA:
	ldr r1, _02217E30 ; =0x00000C4C
	add r1, r0, r1
	mov r0, #0xff
	lsl r0, r0, #2
	mul r0, r2
	add r0, r1, r0
	bx lr
_02217DC8:
	ldr r1, _02217E34 ; =0x000007EC
	add r1, r0, r1
	mov r0, #0x82
	mul r0, r2
	add r0, r1, r0
	bx lr
_02217DD4:
	ldr r1, _02217E38 ; =0x000009F4
	add r1, r0, r1
	mov r0, #0x32
	mul r0, r2
	add r0, r1, r0
	bx lr
_02217DE0:
	ldr r1, _02217E3C ; =0x00000ABC
	add r1, r0, r1
	mov r0, #0x32
	mul r0, r2
	add r0, r1, r0
	bx lr
_02217DEC:
	mov r1, #0x61
	lsl r1, r1, #6
	add r1, r0, r1
	mov r0, #0xc0
	mul r0, r2
	add r0, r1, r0
	bx lr
_02217DFA:
	mov r1, #0x6d
	lsl r1, r1, #6
	add r1, r0, r1
	lsl r0, r2, #6
	add r0, r2, r0
	lsl r0, r0, #2
	add r0, r1, r0
	bx lr
_02217E0A:
	ldr r1, _02217E40 ; =0x00001E4C
	add r1, r0, r1
	mov r0, #0x48
	mul r0, r2
	add r0, r1, r0
	bx lr
_02217E16:
	ldr r1, _02217E44 ; =0x00001F24
	add r1, r0, r1
	mov r0, #0x14
	mul r0, r2
	add r0, r1, r0
	bx lr
_02217E22:
	mov r0, #0
	bx lr
	nop
_02217E28: .word 0x000004EC
_02217E2C: .word 0x00000B84
_02217E30: .word 0x00000C4C
_02217E34: .word 0x000007EC
_02217E38: .word 0x000009F4
_02217E3C: .word 0x00000ABC
_02217E40: .word 0x00001E4C
_02217E44: .word 0x00001F24

	thumb_func_start MOD09_02217E48
MOD09_02217E48: ; 0x02217E48
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r2, #0
	add r2, r3, #0
	add r3, sp, #0x10
	add r4, r1, #0
	ldrb r3, [r3, #0x10]
	add r1, r7, #0
	str r0, [sp]
	bl MOD09_02217D3C
	add r1, r0, #0
	ldr r2, _02217F7C ; =0x0221BAF2
	lsl r0, r7, #2
	ldrb r6, [r2, r0]
	ldr r2, _02217F80 ; =0x0221BAF3
	ldrb r0, [r2, r0]
	add r5, r6, #0
	mul r5, r0
	add r0, r4, #0
	lsl r2, r5, #1
	bl memcpy
	cmp r7, #5
	bgt _02217E96
	cmp r7, #0
	blt _02217F78
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02217E8A: ; jump table
	.short _02217E9E - _02217E8A - 2 ; case 0
	.short _02217E9E - _02217E8A - 2 ; case 1
	.short _02217E9E - _02217E8A - 2 ; case 2
	.short _02217E9E - _02217E8A - 2 ; case 3
	.short _02217E9E - _02217E8A - 2 ; case 4
	.short _02217E9E - _02217E8A - 2 ; case 5
_02217E96:
	cmp r7, #0x1b
	beq _02217F58
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02217E9E:
	mov r0, #0x50
	add r1, r7, #0
	mul r1, r0
	ldr r0, [sp]
	add r0, r0, r1
	ldrh r1, [r0, #8]
	cmp r1, #0
	beq _02217F78
	ldrb r1, [r0, #0x1b]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1f
	beq _02217EFE
	lsl r2, r6, #1
	add r0, r2, #5
	lsl r0, r0, #1
	ldrh r1, [r4, r0]
	add r0, sp, #4
	strh r1, [r0]
	add r1, r6, r2
	add r1, r1, #5
	lsl r1, r1, #1
	ldrh r1, [r4, r1]
	strh r1, [r0, #2]
	mov r1, #0
	add r0, sp, #4
_02217ED0:
	add r5, r1, #2
	lsl r3, r1, #1
	add r7, r5, #0
	mul r7, r6
	lsl r5, r7, #1
	ldrh r3, [r0, r3]
	mov r2, #0
	add r5, r4, r5
_02217EE0:
	lsl r7, r2, #1
	add r2, r2, #1
	lsl r2, r2, #0x18
	add r7, r5, r7
	lsr r2, r2, #0x18
	strh r3, [r7, #0xc]
	cmp r2, #9
	blo _02217EE0
	add r1, r1, #1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, #2
	blo _02217ED0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02217EFE:
	ldrh r0, [r0, #0x14]
	cmp r0, #0
	bne _02217F28
	mov r1, #0
	cmp r5, #0
	ble _02217F78
	mov r3, #2
	ldr r2, _02217F84 ; =0x00000FFF
	lsl r3, r3, #0xc
_02217F10:
	lsl r0, r1, #1
	ldrh r6, [r4, r0]
	and r6, r2
	orr r6, r3
	strh r6, [r4, r0]
	add r0, r1, #1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	cmp r1, r5
	blt _02217F10
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02217F28:
	lsl r1, r7, #0x18
	ldr r0, [sp]
	lsr r1, r1, #0x18
	bl MOD09_02213BDC
	cmp r0, #1
	bne _02217F78
	mov r1, #0
	cmp r5, #0
	ble _02217F78
	ldr r2, _02217F84 ; =0x00000FFF
	add r3, r2, #1
_02217F40:
	lsl r0, r1, #1
	ldrh r6, [r4, r0]
	and r6, r2
	orr r6, r3
	strh r6, [r4, r0]
	add r0, r1, #1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	cmp r1, r5
	blt _02217F40
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02217F58:
	mov r1, #0
	cmp r5, #0
	ble _02217F78
	mov r3, #0xa
	ldr r2, _02217F84 ; =0x00000FFF
	lsl r3, r3, #0xc
_02217F64:
	lsl r0, r1, #1
	ldrh r6, [r4, r0]
	and r6, r2
	orr r6, r3
	strh r6, [r4, r0]
	add r0, r1, #1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	cmp r1, r5
	blt _02217F64
_02217F78:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02217F7C: .word MOD9_0221BAF2
_02217F80: .word MOD9_0221BAF3
_02217F84: .word 0x00000FFF

	thumb_func_start MOD09_02217F88
MOD09_02217F88: ; 0x02217F88
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	str r1, [sp, #0xc]
	str r2, [sp, #0x10]
	str r3, [sp, #0x14]
	add r5, r0, #0
	ldr r0, [sp, #0xc]
	lsl r4, r0, #2
	ldr r0, _02217FF4 ; =0x0221BAF3
	ldrb r7, [r0, r4]
	ldr r0, _02217FF8 ; =0x0221BAF2
	ldrb r6, [r0, r4]
	ldr r0, [r5]
	add r1, r6, #0
	mul r1, r7
	ldr r0, [r0, #0xc]
	lsl r1, r1, #1
	bl AllocFromHeap
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	str r0, [sp]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	add r0, r5, #0
	bl MOD09_02217E48
	ldr r0, _02217FFC ; =0x0221BAF1
	ldr r3, _02218000 ; =0x0221BAF0
	ldrb r0, [r0, r4]
	ldrb r3, [r3, r4]
	ldr r2, [sp, #0x18]
	str r0, [sp]
	str r6, [sp, #4]
	mov r0, #0x79
	str r7, [sp, #8]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #6
	bl LoadRectToBgTilemapRect
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #6
	bl ScheduleBgTilemapBufferTransfer
	ldr r0, [sp, #0x18]
	bl FreeToHeap
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_02217FF4: .word MOD9_0221BAF3
_02217FF8: .word MOD9_0221BAF2
_02217FFC: .word MOD9_0221BAF1
_02218000: .word MOD9_0221BAF0

	thumb_func_start MOD09_02218004
MOD09_02218004: ; 0x02218004
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _022180A4 ; =0x0221BA68
	lsl r3, r1, #2
	ldr r6, [r0, r3]
	cmp r6, #0
	beq _022180A2
	cmp r1, #5
	bhi _0221801E
	ldr r0, _022180A8 ; =0x0221BA58
	ldrb r0, [r0, r2]
	str r0, [sp]
	b _02218024
_0221801E:
	ldr r0, _022180AC ; =0x0221BA48
	ldrb r0, [r0, r2]
	str r0, [sp]
_02218024:
	cmp r2, #0
	beq _02218032
	cmp r2, #1
	beq _02218036
	cmp r2, #2
	beq _0221803A
	b _0221803C
_02218032:
	mov r7, #1
	b _0221803C
_02218036:
	mov r7, #0
	b _0221803C
_0221803A:
	mov r7, #1
_0221803C:
	cmp r1, #0xe
	blo _02218070
	cmp r1, #0x11
	bhi _02218070
	ldr r1, _022180B0 ; =0x00002070
	ldr r2, [sp]
	ldr r0, [r5, r1]
	add r1, r1, #5
	ldrb r1, [r5, r1]
	mov r3, #0
	ldrb r1, [r6, r1]
	lsl r1, r1, #4
	add r0, r0, r1
	add r1, r7, #0
	bl ScrollWindow
	ldr r1, _022180B0 ; =0x00002070
	ldr r0, [r5, r1]
	add r1, r1, #5
	ldrb r1, [r5, r1]
	ldrb r1, [r6, r1]
	lsl r1, r1, #4
	add r0, r0, r1
	bl ScheduleWindowCopyToVram
	pop {r3, r4, r5, r6, r7, pc}
_02218070:
	mov r4, #0
_02218072:
	ldrb r2, [r6, r4]
	cmp r2, #0xff
	beq _022180A2
	ldr r0, _022180B0 ; =0x00002070
	mov r3, #0
	ldr r1, [r5, r0]
	lsl r0, r2, #4
	add r0, r1, r0
	ldr r2, [sp]
	add r1, r7, #0
	bl ScrollWindow
	ldr r0, _022180B0 ; =0x00002070
	ldr r1, [r5, r0]
	ldrb r0, [r6, r4]
	lsl r0, r0, #4
	add r0, r1, r0
	bl ScheduleWindowCopyToVram
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #8
	blo _02218072
_022180A2:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022180A4: .word MOD9_0221BA68
_022180A8: .word MOD9_0221BA58
_022180AC: .word MOD9_0221BA48
_022180B0: .word 0x00002070

	thumb_func_start MOD09_022180B4
MOD09_022180B4: ; 0x022180B4
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #0x1b
	bhi _022181B8
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022180CA: ; jump table
	.short _02218102 - _022180CA - 2 ; case 0
	.short _02218102 - _022180CA - 2 ; case 1
	.short _02218102 - _022180CA - 2 ; case 2
	.short _02218102 - _022180CA - 2 ; case 3
	.short _02218102 - _022180CA - 2 ; case 4
	.short _02218102 - _022180CA - 2 ; case 5
	.short _022181B8 - _022180CA - 2 ; case 6
	.short _02218140 - _022180CA - 2 ; case 7
	.short _022181B8 - _022180CA - 2 ; case 8
	.short _022181B8 - _022180CA - 2 ; case 9
	.short _022181B8 - _022180CA - 2 ; case 10
	.short _022181B8 - _022180CA - 2 ; case 11
	.short _022181B8 - _022180CA - 2 ; case 12
	.short _022181B8 - _022180CA - 2 ; case 13
	.short _02218172 - _022180CA - 2 ; case 14
	.short _02218172 - _022180CA - 2 ; case 15
	.short _02218172 - _022180CA - 2 ; case 16
	.short _02218172 - _022180CA - 2 ; case 17
	.short _022181B8 - _022180CA - 2 ; case 18
	.short _0221818A - _022180CA - 2 ; case 19
	.short _0221818A - _022180CA - 2 ; case 20
	.short _0221818A - _022180CA - 2 ; case 21
	.short _0221818A - _022180CA - 2 ; case 22
	.short _022181A2 - _022180CA - 2 ; case 23
	.short _022181A2 - _022180CA - 2 ; case 24
	.short _022181A2 - _022180CA - 2 ; case 25
	.short _022181A2 - _022180CA - 2 ; case 26
	.short _022181A2 - _022180CA - 2 ; case 27
_02218102:
	ldr r0, _022181BC ; =0x0221BA62
	lsl r1, r2, #1
	ldrsh r6, [r0, r1]
	add r0, r5, #0
	add r0, #0xd
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r0, _022181C0 ; =0x00001FB8
	add r2, r6, #0
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_0200C82C
	lsl r0, r5, #2
	add r1, r4, r0
	ldr r0, _022181C0 ; =0x00001FB8
	add r2, r6, #0
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_0200C82C
	add r0, r5, #7
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r0, _022181C0 ; =0x00001FB8
	add r2, r6, #0
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_0200C82C
	pop {r4, r5, r6, pc}
_02218140:
	ldr r0, _022181C4 ; =0x0221BA5C
	lsl r1, r2, #1
	ldrsh r5, [r0, r1]
	ldr r0, [r4]
	ldrb r0, [r0, #0x11]
	add r2, r5, #0
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r0, _022181C0 ; =0x00001FB8
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_0200C82C
	ldr r0, [r4]
	add r2, r5, #0
	ldrb r0, [r0, #0x11]
	add r0, r0, #7
	lsl r0, r0, #2
	add r1, r4, r0
	ldr r0, _022181C0 ; =0x00001FB8
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_0200C82C
	pop {r4, r5, r6, pc}
_02218172:
	add r0, r5, #7
	lsl r0, r0, #2
	lsl r3, r2, #1
	ldr r2, _022181C4 ; =0x0221BA5C
	add r1, r4, r0
	ldr r0, _022181C0 ; =0x00001FB8
	ldrsh r2, [r2, r3]
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_0200C82C
	pop {r4, r5, r6, pc}
_0221818A:
	add r0, r5, #2
	lsl r0, r0, #2
	lsl r3, r2, #1
	ldr r2, _022181C4 ; =0x0221BA5C
	add r1, r4, r0
	ldr r0, _022181C0 ; =0x00001FB8
	ldrsh r2, [r2, r3]
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_0200C82C
	pop {r4, r5, r6, pc}
_022181A2:
	sub r0, r5, #2
	lsl r0, r0, #2
	lsl r3, r2, #1
	ldr r2, _022181C4 ; =0x0221BA5C
	add r1, r4, r0
	ldr r0, _022181C0 ; =0x00001FB8
	ldrsh r2, [r2, r3]
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_0200C82C
_022181B8:
	pop {r4, r5, r6, pc}
	nop
_022181BC: .word MOD9_0221BA62
_022181C0: .word 0x00001FB8
_022181C4: .word MOD9_0221BA5C

	thumb_func_start MOD09_022181C8
MOD09_022181C8: ; 0x022181C8
	push {r4, r5, r6, lr}
	ldr r3, _02218210 ; =0x00001FA3
	add r5, r0, #0
	ldrb r6, [r5, r3]
	mov r2, #0x70
	add r4, r1, #0
	bic r6, r2
	strb r6, [r5, r3]
	cmp r4, #5
	bhi _022181F2
	bl MOD09_02213620
	cmp r0, #2
	bne _022181F2
	ldr r1, _02218210 ; =0x00001FA3
	mov r0, #0x70
	ldrb r2, [r5, r1]
	bic r2, r0
	mov r0, #0x10
	orr r0, r2
	strb r0, [r5, r1]
_022181F2:
	ldr r0, _02218214 ; =0x00001FA0
	mov r2, #0
	strb r2, [r5, r0]
	add r1, r0, #1
	strb r2, [r5, r1]
	add r1, r0, #2
	strb r4, [r5, r1]
	add r1, r0, #3
	ldrb r2, [r5, r1]
	mov r1, #0x80
	add r0, r0, #3
	orr r1, r2
	strb r1, [r5, r0]
	pop {r4, r5, r6, pc}
	nop
_02218210: .word 0x00001FA3
_02218214: .word 0x00001FA0

	thumb_func_start MOD09_02218218
MOD09_02218218: ; 0x02218218
	push {r4, lr}
	ldr r2, _022182DC ; =0x00001FA3
	add r4, r0, #0
	ldrb r3, [r4, r2]
	lsl r1, r3, #0x18
	lsr r1, r1, #0x1f
	beq _022182D8
	sub r1, r2, #3
	ldrb r1, [r4, r1]
	cmp r1, #0
	beq _02218238
	cmp r1, #1
	beq _0221826C
	cmp r1, #2
	beq _022182A0
	pop {r4, pc}
_02218238:
	sub r1, r2, #1
	ldrb r1, [r4, r1]
	lsl r3, r3, #0x19
	mov r2, #1
	lsr r3, r3, #0x1d
	bl MOD09_02217F88
	ldr r1, _022182E0 ; =0x00001FA2
	add r0, r4, #0
	ldrb r1, [r4, r1]
	mov r2, #1
	bl MOD09_02218004
	ldr r1, _022182E0 ; =0x00001FA2
	add r0, r4, #0
	ldrb r1, [r4, r1]
	mov r2, #1
	bl MOD09_022180B4
	ldr r0, _022182E4 ; =0x00001FA1
	mov r1, #0
	strb r1, [r4, r0]
	mov r1, #1
	sub r0, r0, #1
	strb r1, [r4, r0]
	pop {r4, pc}
_0221826C:
	sub r1, r2, #1
	ldrb r1, [r4, r1]
	lsl r3, r3, #0x19
	mov r2, #2
	lsr r3, r3, #0x1d
	bl MOD09_02217F88
	ldr r1, _022182E0 ; =0x00001FA2
	add r0, r4, #0
	ldrb r1, [r4, r1]
	mov r2, #2
	bl MOD09_02218004
	ldr r1, _022182E0 ; =0x00001FA2
	add r0, r4, #0
	ldrb r1, [r4, r1]
	mov r2, #2
	bl MOD09_022180B4
	ldr r0, _022182E4 ; =0x00001FA1
	mov r1, #0
	strb r1, [r4, r0]
	mov r1, #2
	sub r0, r0, #1
	strb r1, [r4, r0]
	pop {r4, pc}
_022182A0:
	sub r1, r2, #1
	ldrb r1, [r4, r1]
	lsl r3, r3, #0x19
	mov r2, #0
	lsr r3, r3, #0x1d
	bl MOD09_02217F88
	ldr r1, _022182E0 ; =0x00001FA2
	add r0, r4, #0
	ldrb r1, [r4, r1]
	mov r2, #0
	bl MOD09_02218004
	ldr r1, _022182E0 ; =0x00001FA2
	add r0, r4, #0
	ldrb r1, [r4, r1]
	mov r2, #0
	bl MOD09_022180B4
	ldr r0, _022182E4 ; =0x00001FA1
	mov r1, #0
	strb r1, [r4, r0]
	add r1, r0, #2
	ldrb r2, [r4, r1]
	mov r1, #0x80
	add r0, r0, #2
	bic r2, r1
	strb r2, [r4, r0]
_022182D8:
	pop {r4, pc}
	nop
_022182DC: .word 0x00001FA3
_022182E0: .word 0x00001FA2
_022182E4: .word 0x00001FA1

	thumb_func_start MOD09_022182E8
MOD09_022182E8: ; 0x022182E8
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	cmp r1, #9
	bls _022182F2
	b _0221863A
_022182F2:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022182FE: ; jump table
	.short _02218312 - _022182FE - 2 ; case 0
	.short _0221838A - _022182FE - 2 ; case 1
	.short _022183E6 - _022182FE - 2 ; case 2
	.short _0221843A - _022182FE - 2 ; case 3
	.short _022184D8 - _022182FE - 2 ; case 4
	.short _02218524 - _022182FE - 2 ; case 5
	.short _0221857C - _022182FE - 2 ; case 6
	.short _022185DC - _022182FE - 2 ; case 7
	.short _0221857C - _022182FE - 2 ; case 8
	.short _0221860C - _022182FE - 2 ; case 9
_02218312:
	mov r5, #0
	mov r6, #3
	mov r7, #1
_02218318:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD09_02213620
	cmp r0, #0
	bne _02218334
	lsl r1, r5, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	add r2, r6, #0
	add r3, r7, #0
	bl MOD09_02217F88
	b _0221835A
_02218334:
	cmp r0, #1
	bne _02218348
	lsl r1, r5, #0x18
	mov r2, #0
	add r0, r4, #0
	lsr r1, r1, #0x18
	add r3, r2, #0
	bl MOD09_02217F88
	b _0221835A
_02218348:
	cmp r0, #2
	bne _0221835A
	lsl r1, r5, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	mov r2, #0
	mov r3, #1
	bl MOD09_02217F88
_0221835A:
	add r0, r5, #1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #6
	blo _02218318
	ldr r0, [r4]
	add r0, #0x35
	ldrb r0, [r0]
	cmp r0, #1
	bne _0221837C
	add r0, r4, #0
	mov r1, #6
	mov r2, #3
	mov r3, #0
	bl MOD09_02217F88
	pop {r3, r4, r5, r6, r7, pc}
_0221837C:
	mov r2, #0
	add r0, r4, #0
	mov r1, #6
	add r3, r2, #0
	bl MOD09_02217F88
	pop {r3, r4, r5, r6, r7, pc}
_0221838A:
	mov r2, #0
	mov r1, #6
	add r3, r2, #0
	bl MOD09_02217F88
	mov r2, #0
	add r0, r4, #0
	mov r1, #7
	add r3, r2, #0
	bl MOD09_02217F88
	ldr r0, [r4]
	ldrb r1, [r0, #0x11]
	mov r0, #0x50
	mul r0, r1
	add r0, r4, r0
	ldrb r0, [r0, #0x1b]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	beq _022183CC
	add r0, r4, #0
	mov r1, #8
	mov r2, #3
	mov r3, #0
	bl MOD09_02217F88
	add r0, r4, #0
	mov r1, #0xa
	mov r2, #3
	mov r3, #0
	bl MOD09_02217F88
	pop {r3, r4, r5, r6, r7, pc}
_022183CC:
	mov r2, #0
	add r0, r4, #0
	mov r1, #8
	add r3, r2, #0
	bl MOD09_02217F88
	mov r2, #0
	add r0, r4, #0
	mov r1, #0xa
	add r3, r2, #0
	bl MOD09_02217F88
	pop {r3, r4, r5, r6, r7, pc}
_022183E6:
	bl MOD09_02218680
	cmp r0, #1
	bne _02218408
	mov r2, #0
	add r0, r4, #0
	mov r1, #0xc
	add r3, r2, #0
	bl MOD09_02217F88
	mov r2, #0
	add r0, r4, #0
	mov r1, #0xd
	add r3, r2, #0
	bl MOD09_02217F88
	b _02218420
_02218408:
	add r0, r4, #0
	mov r1, #0xc
	mov r2, #3
	mov r3, #0
	bl MOD09_02217F88
	add r0, r4, #0
	mov r1, #0xd
	mov r2, #3
	mov r3, #0
	bl MOD09_02217F88
_02218420:
	mov r2, #0
	add r0, r4, #0
	mov r1, #0xb
	add r3, r2, #0
	bl MOD09_02217F88
	mov r2, #0
	add r0, r4, #0
	mov r1, #6
	add r3, r2, #0
	bl MOD09_02217F88
	pop {r3, r4, r5, r6, r7, pc}
_0221843A:
	bl MOD09_02218680
	cmp r0, #1
	bne _0221845C
	mov r2, #0
	add r0, r4, #0
	mov r1, #0xc
	add r3, r2, #0
	bl MOD09_02217F88
	mov r2, #0
	add r0, r4, #0
	mov r1, #0xd
	add r3, r2, #0
	bl MOD09_02217F88
	b _02218474
_0221845C:
	add r0, r4, #0
	mov r1, #0xc
	mov r2, #3
	mov r3, #0
	bl MOD09_02217F88
	add r0, r4, #0
	mov r1, #0xd
	mov r2, #3
	mov r3, #0
	bl MOD09_02217F88
_02218474:
	mov r5, #0
	mov r7, #3
	mov r6, #0x50
_0221847A:
	ldr r0, [r4]
	lsl r1, r5, #3
	ldrb r0, [r0, #0x11]
	add r2, r0, #0
	mul r2, r6
	add r0, r4, r2
	add r0, r1, r0
	ldrh r0, [r0, #0x34]
	cmp r0, #0
	beq _022184A2
	add r1, r5, #0
	add r1, #0xe
	lsl r1, r1, #0x18
	mov r2, #0
	add r0, r4, #0
	lsr r1, r1, #0x18
	add r3, r2, #0
	bl MOD09_02217F88
	b _022184B4
_022184A2:
	add r1, r5, #0
	add r1, #0xe
	lsl r1, r1, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	add r2, r7, #0
	mov r3, #0
	bl MOD09_02217F88
_022184B4:
	add r0, r5, #1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #4
	blo _0221847A
	mov r2, #0
	add r0, r4, #0
	mov r1, #9
	add r3, r2, #0
	bl MOD09_02217F88
	mov r2, #0
	add r0, r4, #0
	mov r1, #6
	add r3, r2, #0
	bl MOD09_02217F88
	pop {r3, r4, r5, r6, r7, pc}
_022184D8:
	mov r2, #0
	mov r1, #6
	add r3, r2, #0
	bl MOD09_02217F88
	mov r5, #0
	mov r6, #2
	add r7, r5, #0
_022184E8:
	ldr r0, [r4]
	add r0, #0x34
	ldrb r0, [r0]
	cmp r0, r5
	bne _02218506
	add r1, r5, #0
	add r1, #0x1e
	lsl r1, r1, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	add r2, r6, #0
	add r3, r7, #0
	bl MOD09_02217F88
	b _02218518
_02218506:
	add r1, r5, #0
	add r1, #0x1e
	lsl r1, r1, #0x18
	mov r2, #0
	add r0, r4, #0
	lsr r1, r1, #0x18
	add r3, r2, #0
	bl MOD09_02217F88
_02218518:
	add r0, r5, #1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #4
	blo _022184E8
	pop {r3, r4, r5, r6, r7, pc}
_02218524:
	mov r5, #0
	mov r7, #3
	mov r6, #0x50
_0221852A:
	ldr r0, [r4]
	lsl r1, r5, #3
	ldrb r0, [r0, #0x11]
	add r2, r0, #0
	mul r2, r6
	add r0, r4, r2
	add r0, r1, r0
	ldrh r0, [r0, #0x34]
	cmp r0, #0
	beq _02218552
	add r1, r5, #0
	add r1, #0x13
	lsl r1, r1, #0x18
	mov r2, #0
	add r0, r4, #0
	lsr r1, r1, #0x18
	add r3, r2, #0
	bl MOD09_02217F88
	b _02218564
_02218552:
	add r1, r5, #0
	add r1, #0x13
	lsl r1, r1, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	add r2, r7, #0
	mov r3, #0
	bl MOD09_02217F88
_02218564:
	add r0, r5, #1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #4
	blo _0221852A
	mov r2, #0
	add r0, r4, #0
	mov r1, #6
	add r3, r2, #0
	bl MOD09_02217F88
	pop {r3, r4, r5, r6, r7, pc}
_0221857C:
	mov r2, #0
	mov r1, #0x17
	add r3, r2, #0
	bl MOD09_02217F88
	mov r2, #0
	add r0, r4, #0
	mov r1, #0x18
	add r3, r2, #0
	bl MOD09_02217F88
	mov r2, #0
	add r0, r4, #0
	mov r1, #0x19
	add r3, r2, #0
	bl MOD09_02217F88
	mov r2, #0
	add r0, r4, #0
	mov r1, #0x1a
	add r3, r2, #0
	bl MOD09_02217F88
	mov r2, #0
	add r0, r4, #0
	mov r1, #0x1b
	add r3, r2, #0
	bl MOD09_02217F88
	mov r2, #0
	add r0, r4, #0
	mov r1, #6
	add r3, r2, #0
	bl MOD09_02217F88
	ldr r0, _0221863C ; =0x00002077
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	cmp r0, #1
	bne _0221863A
	mov r2, #0
	add r0, r4, #0
	mov r1, #0x12
	add r3, r2, #0
	bl MOD09_02217F88
	pop {r3, r4, r5, r6, r7, pc}
_022185DC:
	mov r2, #0
	mov r1, #0x1c
	add r3, r2, #0
	bl MOD09_02217F88
	mov r2, #0
	add r0, r4, #0
	mov r1, #6
	add r3, r2, #0
	bl MOD09_02217F88
	ldr r0, _0221863C ; =0x00002077
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	cmp r0, #1
	bne _0221863A
	mov r2, #0
	add r0, r4, #0
	mov r1, #0x12
	add r3, r2, #0
	bl MOD09_02217F88
	pop {r3, r4, r5, r6, r7, pc}
_0221860C:
	mov r2, #0
	mov r1, #0x1d
	add r3, r2, #0
	bl MOD09_02217F88
	mov r2, #0
	add r0, r4, #0
	mov r1, #6
	add r3, r2, #0
	bl MOD09_02217F88
	ldr r0, _0221863C ; =0x00002077
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	cmp r0, #1
	bne _0221863A
	mov r2, #0
	add r0, r4, #0
	mov r1, #0x12
	add r3, r2, #0
	bl MOD09_02217F88
_0221863A:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0221863C: .word 0x00002077

	thumb_func_start MOD09_02218640
MOD09_02218640: ; 0x02218640
	push {r3, lr}
	add r2, r0, #0
	cmp r1, #3
	bne _02218662
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x7a
	lsl r0, r0, #2
	mov r1, #0x7e
	lsl r1, r1, #6
	ldr r0, [r2, r0]
	add r1, r2, r1
	mov r2, #1
	mov r3, #0xc0
	bl PaletteData_LoadPalette
	pop {r3, pc}
_02218662:
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r1, _0221867C ; =0x00001F60
	ldr r0, [r2, r0]
	add r1, r2, r1
	mov r2, #1
	mov r3, #0xc0
	bl PaletteData_LoadPalette
	pop {r3, pc}
	nop
_0221867C: .word 0x00001F60

	thumb_func_start MOD09_02218680
MOD09_02218680: ; 0x02218680
	push {r4, r5}
	mov r2, #0
	add r1, r2, #0
	mov r3, #0x50
_02218688:
	add r4, r1, #0
	mul r4, r3
	add r5, r0, r4
	ldrh r4, [r5, #8]
	cmp r4, #0
	beq _022186A2
	ldrb r4, [r5, #0x1b]
	lsl r4, r4, #0x18
	lsr r4, r4, #0x1f
	bne _022186A2
	add r2, r2, #1
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
_022186A2:
	add r1, r1, #1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	cmp r1, #6
	blo _02218688
	cmp r2, #2
	blo _022186B4
	mov r0, #1
	b _022186B6
_022186B4:
	mov r0, #0
_022186B6:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r4, r5}
	bx lr
	.align 2, 0

	thumb_func_start MOD09_022186C0
MOD09_022186C0: ; 0x022186C0
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	ldrb r1, [r1, #0x11]
	bl MOD09_02213620
	cmp r0, #2
	bne _022186E0
	ldr r1, [r4]
	add r0, r4, #0
	ldrb r1, [r1, #0x11]
	mov r2, #0
	mov r3, #1
	bl MOD09_02217F88
	pop {r4, pc}
_022186E0:
	ldr r1, [r4]
	mov r2, #0
	ldrb r1, [r1, #0x11]
	add r0, r4, #0
	add r3, r2, #0
	bl MOD09_02217F88
	pop {r4, pc}

	thumb_func_start MOD09_022186F0
MOD09_022186F0: ; 0x022186F0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _02218780 ; =MOD09_0221878C
	ldr r1, _02218784 ; =0x0000115C
	ldr r3, [r5, #0xc]
	mov r2, #0x64
	bl FUN_020061E8
	bl FUN_0201B6C8
	ldr r2, _02218784 ; =0x0000115C
	add r4, r0, #0
	mov r1, #0
	bl memset
	str r5, [r4]
	ldr r0, [r5]
	bl MOD11_0222FF68
	str r0, [r4, #4]
	ldr r0, [r5]
	bl MOD11_022300CC
	str r0, [r4, #8]
	ldr r0, _02218788 ; =0x0000114A
	mov r1, #0
	strb r1, [r4, r0]
	ldr r0, [r5]
	bl MOD11_02230218
	add r6, r0, #0
	mov r5, #0
_02218730:
	ldr r3, [r4]
	add r0, r6, #0
	add r2, r3, #0
	add r2, #0x27
	add r3, #0x2c
	add r1, r5, #0
	add r2, r2, r5
	add r3, r3, r5
	bl FUN_0206F1A0
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #5
	blo _02218730
	add r0, r6, #0
	bl FUN_0206F1AC
	ldr r1, [r4]
	strh r0, [r1, #0x20]
	add r0, r6, #0
	bl FUN_0206F1B0
	ldr r1, [r4]
	strb r0, [r1, #0x1f]
	add r0, r4, #0
	bl MOD09_02219C38
	ldr r0, [r4]
	ldr r0, [r0]
	bl MOD11_0222FF74
	mov r1, #1
	lsl r1, r1, #0xa
	tst r0, r1
	beq _0221877E
	ldr r0, [r4]
	mov r1, #1
	str r1, [r0, #0x14]
_0221877E:
	pop {r4, r5, r6, pc}
	.align 2, 0
_02218780: .word MOD09_0221878C
_02218784: .word 0x0000115C
_02218788: .word 0x0000114A

	thumb_func_start MOD09_0221878C
MOD09_0221878C: ; 0x0221878C
	push {r4, lr}
	ldr r2, _02218884 ; =0x0000114A
	add r4, r1, #0
	ldrb r2, [r4, r2]
	cmp r2, #0xe
	bhi _02218872
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_022187A4: ; jump table
	.short _022187C2 - _022187A4 - 2 ; case 0
	.short _022187CE - _022187A4 - 2 ; case 1
	.short _022187DA - _022187A4 - 2 ; case 2
	.short _022187E6 - _022187A4 - 2 ; case 3
	.short _022187F2 - _022187A4 - 2 ; case 4
	.short _022187FE - _022187A4 - 2 ; case 5
	.short _0221880A - _022187A4 - 2 ; case 6
	.short _02218816 - _022187A4 - 2 ; case 7
	.short _02218822 - _022187A4 - 2 ; case 8
	.short _0221882E - _022187A4 - 2 ; case 9
	.short _0221883A - _022187A4 - 2 ; case 10
	.short _02218846 - _022187A4 - 2 ; case 11
	.short _02218852 - _022187A4 - 2 ; case 12
	.short _0221885E - _022187A4 - 2 ; case 13
	.short _0221886A - _022187A4 - 2 ; case 14
_022187C2:
	add r0, r4, #0
	bl MOD09_02218888
	ldr r1, _02218884 ; =0x0000114A
	strb r0, [r4, r1]
	b _02218872
_022187CE:
	add r0, r4, #0
	bl MOD09_0221895C
	ldr r1, _02218884 ; =0x0000114A
	strb r0, [r4, r1]
	b _02218872
_022187DA:
	add r0, r4, #0
	bl MOD09_02218A34
	ldr r1, _02218884 ; =0x0000114A
	strb r0, [r4, r1]
	b _02218872
_022187E6:
	add r0, r4, #0
	bl MOD09_02218BBC
	ldr r1, _02218884 ; =0x0000114A
	strb r0, [r4, r1]
	b _02218872
_022187F2:
	add r0, r4, #0
	bl MOD09_02218E44
	ldr r1, _02218884 ; =0x0000114A
	strb r0, [r4, r1]
	b _02218872
_022187FE:
	add r0, r4, #0
	bl MOD09_02218E50
	ldr r1, _02218884 ; =0x0000114A
	strb r0, [r4, r1]
	b _02218872
_0221880A:
	add r0, r4, #0
	bl MOD09_02218E5C
	ldr r1, _02218884 ; =0x0000114A
	strb r0, [r4, r1]
	b _02218872
_02218816:
	add r0, r4, #0
	bl MOD09_02218B44
	ldr r1, _02218884 ; =0x0000114A
	strb r0, [r4, r1]
	b _02218872
_02218822:
	add r0, r4, #0
	bl MOD09_02218E68
	ldr r1, _02218884 ; =0x0000114A
	strb r0, [r4, r1]
	b _02218872
_0221882E:
	add r0, r4, #0
	bl MOD09_02218E78
	ldr r1, _02218884 ; =0x0000114A
	strb r0, [r4, r1]
	b _02218872
_0221883A:
	add r0, r4, #0
	bl MOD09_02218E90
	ldr r1, _02218884 ; =0x0000114A
	strb r0, [r4, r1]
	b _02218872
_02218846:
	add r0, r4, #0
	bl MOD09_02218EB8
	ldr r1, _02218884 ; =0x0000114A
	strb r0, [r4, r1]
	b _02218872
_02218852:
	add r0, r4, #0
	bl MOD09_02218F90
	ldr r1, _02218884 ; =0x0000114A
	strb r0, [r4, r1]
	b _02218872
_0221885E:
	add r0, r4, #0
	bl MOD09_02218ED0
	ldr r1, _02218884 ; =0x0000114A
	strb r0, [r4, r1]
	b _02218872
_0221886A:
	bl MOD09_02218EF8
	cmp r0, #1
	beq _02218882
_02218872:
	add r0, r4, #0
	bl MOD09_0221AA14
	mov r0, #0xc3
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200BC1C
_02218882:
	pop {r4, pc}
	.align 2, 0
_02218884: .word 0x0000114A

	thumb_func_start MOD09_02218888
MOD09_02218888: ; 0x02218888
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, _0221894C ; =0x04001050
	mov r1, #0
	strh r1, [r0]
	ldr r0, [r4]
	ldr r0, [r0, #0xc]
	bl MOD09_0221AC04
	str r0, [r4, #0x34]
	add r0, r4, #0
	bl MOD09_022190CC
	add r0, r4, #0
	bl MOD09_022191C0
	add r0, r4, #0
	bl MOD09_022192A4
	ldr r1, [r4]
	mov r0, #2
	ldr r1, [r1, #0xc]
	bl FUN_02002C50
	ldr r0, [r4]
	ldr r0, [r0]
	bl MOD11_02230218
	bl FUN_0206F1B4
	ldr r1, _02218950 ; =0x0000114D
	strb r0, [r4, r1]
	add r0, r4, #0
	bl MOD09_02219CB4
	ldr r1, _02218954 ; =0x0000114C
	add r0, r4, #0
	ldrb r1, [r4, r1]
	bl MOD09_0221AAF0
	add r0, r4, #0
	bl MOD09_02219474
	ldr r1, _02218954 ; =0x0000114C
	add r0, r4, #0
	ldrb r1, [r4, r1]
	bl MOD09_0221953C
	add r0, r4, #0
	bl MOD09_02219DC8
	ldr r1, _02218954 ; =0x0000114C
	add r0, r4, #0
	ldrb r1, [r4, r1]
	bl MOD09_0221A044
	ldr r0, [r4]
	add r0, #0x25
	ldrb r0, [r0]
	cmp r0, #0
	beq _0221890C
	ldr r0, [r4, #0x34]
	mov r1, #1
	bl MOD09_0221AC2C
_0221890C:
	ldr r1, _02218954 ; =0x0000114C
	add r0, r4, #0
	ldrb r1, [r4, r1]
	bl MOD09_0221A1DC
	ldr r1, _02218954 ; =0x0000114C
	add r0, r4, #0
	ldrb r1, [r4, r1]
	bl MOD09_0221A2BC
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r1, #0xa
	str r0, [sp, #8]
	add r3, r1, #0
	ldr r0, [r4, #8]
	ldr r2, _02218958 ; =0x0000FFFF
	sub r3, #0x12
	bl FUN_02003210
	ldr r0, [r4]
	ldr r0, [r0, #0x14]
	cmp r0, #1
	bne _02218946
	add sp, #0xc
	mov r0, #0xc
	pop {r3, r4, pc}
_02218946:
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_0221894C: .word 0x04001050
_02218950: .word 0x0000114D
_02218954: .word 0x0000114C
_02218958: .word 0x0000FFFF

	thumb_func_start MOD09_0221895C
MOD09_0221895C: ; 0x0221895C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	bl FUN_020038E4
	cmp r0, #0
	beq _0221896E
	mov r0, #1
	pop {r3, r4, r5, pc}
_0221896E:
	ldr r1, _02218A28 ; =0x0221BBE8
	add r0, r4, #0
	bl MOD09_02219424
	add r5, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	bne _02218994
	ldr r0, [r4, #0x34]
	bl MOD09_0221AD30
	add r5, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	bne _0221899A
	mov r5, #5
	b _0221899A
_02218994:
	add r0, r4, #0
	bl MOD09_0221A224
_0221899A:
	cmp r5, #5
	bhi _02218A24
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022189AA: ; jump table
	.short _022189B6 - _022189AA - 2 ; case 0
	.short _022189B6 - _022189AA - 2 ; case 1
	.short _022189B6 - _022189AA - 2 ; case 2
	.short _022189B6 - _022189AA - 2 ; case 3
	.short _022189D6 - _022189AA - 2 ; case 4
	.short _02218A06 - _022189AA - 2 ; case 5
_022189B6:
	ldr r0, _02218A2C ; =0x000005DD
	bl PlaySE
	lsl r0, r5, #0x18
	lsr r1, r0, #0x18
	ldr r0, _02218A30 ; =0x0000114D
	mov r2, #5
	strb r1, [r4, r0]
	sub r0, r0, #2
	strb r2, [r4, r0]
	add r0, r4, #0
	mov r2, #0
	bl MOD09_0221A9D8
	mov r0, #0xb
	pop {r3, r4, r5, pc}
_022189D6:
	ldr r0, [r4]
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	beq _02218A24
	ldr r0, _02218A2C ; =0x000005DD
	bl PlaySE
	ldr r0, [r4]
	ldrb r1, [r0, #0x1f]
	ldr r0, _02218A30 ; =0x0000114D
	strb r1, [r4, r0]
	mov r1, #6
	sub r0, r0, #2
	strb r1, [r4, r0]
	add r0, r4, #0
	bl MOD09_02219C68
	add r0, r4, #0
	mov r1, #4
	mov r2, #0
	bl MOD09_0221A9D8
	mov r0, #0xb
	pop {r3, r4, r5, pc}
_02218A06:
	ldr r0, _02218A2C ; =0x000005DD
	bl PlaySE
	ldr r0, [r4]
	mov r2, #0
	strh r2, [r0, #0x1c]
	ldr r0, [r4]
	mov r1, #4
	strb r1, [r0, #0x1e]
	add r0, r4, #0
	mov r1, #5
	bl MOD09_0221A9D8
	mov r0, #0xd
	pop {r3, r4, r5, pc}
_02218A24:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_02218A28: .word MOD9_0221BBE8
_02218A2C: .word 0x000005DD
_02218A30: .word 0x0000114D

	thumb_func_start MOD09_02218A34
MOD09_02218A34: ; 0x02218A34
	push {r3, r4, r5, lr}
	ldr r1, _02218B34 ; =0x0221BC04
	add r4, r0, #0
	bl MOD09_02219424
	add r5, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	bne _02218A5C
	ldr r0, [r4, #0x34]
	bl MOD09_0221AD30
	add r5, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	bne _02218A62
	mov r5, #8
	b _02218A62
_02218A5C:
	add r0, r4, #0
	bl MOD09_0221A224
_02218A62:
	cmp r5, #8
	bhi _02218B30
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02218A72: ; jump table
	.short _02218A84 - _02218A72 - 2 ; case 0
	.short _02218A84 - _02218A72 - 2 ; case 1
	.short _02218A84 - _02218A72 - 2 ; case 2
	.short _02218A84 - _02218A72 - 2 ; case 3
	.short _02218A84 - _02218A72 - 2 ; case 4
	.short _02218A84 - _02218A72 - 2 ; case 5
	.short _02218ABA - _02218A72 - 2 ; case 6
	.short _02218AE8 - _02218A72 - 2 ; case 7
	.short _02218B16 - _02218A72 - 2 ; case 8
_02218A84:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD09_02219D94
	cmp r0, #0
	beq _02218B30
	ldr r0, _02218B38 ; =0x000005DD
	bl PlaySE
	ldr r0, _02218B3C ; =0x0000114D
	ldr r2, [r4]
	ldrb r1, [r4, r0]
	sub r0, r0, #2
	add r1, r2, r1
	add r1, #0x27
	strb r5, [r1]
	mov r1, #6
	strb r1, [r4, r0]
	add r1, r5, #6
	lsl r1, r1, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	mov r2, #0
	bl MOD09_0221A9D8
	mov r0, #0xb
	pop {r3, r4, r5, pc}
_02218ABA:
	ldr r0, _02218B3C ; =0x0000114D
	ldrb r1, [r4, r0]
	add r0, r0, #7
	add r1, r4, r1
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _02218B30
	ldr r0, _02218B38 ; =0x000005DD
	bl PlaySE
	ldr r0, _02218B40 ; =0x0000114B
	mov r1, #7
	strb r1, [r4, r0]
	sub r1, #8
	add r0, r0, #3
	strb r1, [r4, r0]
	add r0, r4, #0
	mov r1, #0xc
	mov r2, #0
	bl MOD09_0221A9D8
	mov r0, #0xb
	pop {r3, r4, r5, pc}
_02218AE8:
	ldr r0, _02218B3C ; =0x0000114D
	ldrb r1, [r4, r0]
	add r0, r0, #7
	add r1, r4, r1
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _02218B30
	ldr r0, _02218B38 ; =0x000005DD
	bl PlaySE
	ldr r0, _02218B40 ; =0x0000114B
	mov r1, #7
	strb r1, [r4, r0]
	mov r1, #1
	add r0, r0, #3
	strb r1, [r4, r0]
	add r0, r4, #0
	mov r1, #0xd
	mov r2, #0
	bl MOD09_0221A9D8
	mov r0, #0xb
	pop {r3, r4, r5, pc}
_02218B16:
	ldr r0, _02218B38 ; =0x000005DD
	bl PlaySE
	ldr r0, _02218B40 ; =0x0000114B
	mov r1, #4
	strb r1, [r4, r0]
	add r0, r4, #0
	mov r1, #0xe
	mov r2, #0
	bl MOD09_0221A9D8
	mov r0, #0xb
	pop {r3, r4, r5, pc}
_02218B30:
	mov r0, #2
	pop {r3, r4, r5, pc}
	.align 2, 0
_02218B34: .word MOD9_0221BC04
_02218B38: .word 0x000005DD
_02218B3C: .word 0x0000114D
_02218B40: .word 0x0000114B

	thumb_func_start MOD09_02218B44
MOD09_02218B44: ; 0x02218B44
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, _02218BB4 ; =0x0000114D
	ldr r1, [r4]
	ldrb r2, [r4, r0]
	mov r3, #0
	add r5, r1, r2
	mov r1, #0x2c
	ldrsb r2, [r5, r1]
	add r5, #0x27
	add r1, r0, #1
	strb r3, [r5]
	ldrsb r1, [r4, r1]
	add r1, r2, r1
	lsl r1, r1, #0x18
	asr r2, r1, #0x18
	ldrb r1, [r4, r0]
	add r0, r0, #7
	add r5, r4, r1
	ldrb r5, [r5, r0]
	cmp r2, r5
	ble _02218B7A
	ldr r0, [r4]
	add r0, r0, r1
	add r0, #0x2c
	strb r3, [r0]
	b _02218B8E
_02218B7A:
	cmp r2, #0
	ldr r0, [r4]
	bge _02218B88
	add r0, r0, r1
	add r0, #0x2c
	strb r5, [r0]
	b _02218B8E
_02218B88:
	add r0, r0, r1
	add r0, #0x2c
	strb r2, [r0]
_02218B8E:
	add r0, r4, #0
	bl MOD09_0221983C
	add r0, r4, #0
	bl MOD09_02219884
	ldr r1, _02218BB8 ; =0x0000114C
	add r0, r4, #0
	ldrb r1, [r4, r1]
	bl MOD09_0221A044
	ldr r1, _02218BB8 ; =0x0000114C
	add r0, r4, #0
	ldrb r1, [r4, r1]
	bl MOD09_0221AAF0
	mov r0, #2
	pop {r3, r4, r5, pc}
	nop
_02218BB4: .word 0x0000114D
_02218BB8: .word 0x0000114C

	thumb_func_start MOD09_02218BBC
MOD09_02218BBC: ; 0x02218BBC
	push {r3, r4, r5, lr}
	ldr r1, _02218C48 ; =0x0221BB78
	add r5, r0, #0
	bl MOD09_02219424
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _02218BE4
	ldr r0, [r5, #0x34]
	bl MOD09_0221AD30
	add r4, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _02218BEA
	mov r4, #1
	b _02218BEA
_02218BE4:
	add r0, r5, #0
	bl MOD09_0221A224
_02218BEA:
	cmp r4, #0
	beq _02218BF4
	cmp r4, #1
	beq _02218C2A
	b _02218C44
_02218BF4:
	ldr r0, _02218C4C ; =0x000005DD
	bl PlaySE
	ldr r1, _02218C50 ; =0x0000114D
	ldr r2, [r5]
	ldrb r1, [r5, r1]
	add r0, r5, #0
	add r1, r2, r1
	add r1, #0x27
	ldrb r1, [r1]
	bl MOD09_02219D94
	ldr r1, [r5]
	mov r2, #0
	strh r0, [r1, #0x1c]
	ldr r0, _02218C50 ; =0x0000114D
	ldrb r1, [r5, r0]
	ldr r0, [r5]
	strb r1, [r0, #0x1e]
	add r0, r5, #0
	mov r1, #0xf
	bl MOD09_0221A9D8
	add r0, r5, #0
	bl MOD09_02218C58
	pop {r3, r4, r5, pc}
_02218C2A:
	ldr r0, _02218C4C ; =0x000005DD
	bl PlaySE
	ldr r0, _02218C54 ; =0x0000114B
	mov r1, #5
	strb r1, [r5, r0]
	add r0, r5, #0
	mov r1, #0x10
	mov r2, #0
	bl MOD09_0221A9D8
	mov r0, #0xb
	pop {r3, r4, r5, pc}
_02218C44:
	mov r0, #3
	pop {r3, r4, r5, pc}
	.align 2, 0
_02218C48: .word MOD9_0221BB78
_02218C4C: .word 0x000005DD
_02218C50: .word 0x0000114D
_02218C54: .word 0x0000114B

	thumb_func_start MOD09_02218C58
MOD09_02218C58: ; 0x02218C58
	push {r3, r4, r5, r6, r7, lr}
	ldr r1, _02218E38 ; =0x0000114D
	add r5, r0, #0
	ldrb r1, [r5, r1]
	ldr r4, [r5]
	cmp r1, #3
	beq _02218C68
	b _02218D82
_02218C68:
	bl MOD09_02219430
	add r7, r0, #0
	ldrh r0, [r4, #0x1c]
	ldr r2, [r4, #0xc]
	mov r1, #7
	bl GetItemAttr
	add r6, r0, #0
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _02218CDA
	ldrh r0, [r4, #0x1c]
	cmp r0, #0x37
	beq _02218CDA
	cmp r6, #3
	beq _02218CDA
	ldr r0, [r4]
	ldr r1, [r4, #0x10]
	add r2, r7, #0
	bl MOD11_02230014
	add r6, r0, #0
	ldr r0, [r5, #0x10]
	mov r1, #0x2e
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r6, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r5, #0x14]
	mov r1, #0
	bl BufferBoxMonNickname
	ldr r0, [r5, #0x14]
	ldr r2, _02218E3C ; =0x00000175
	mov r1, #1
	bl BufferMoveName
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	add r0, r5, #0
	bl MOD09_02219BE0
	ldr r0, _02218E40 ; =0x0000114B
	mov r1, #8
	strb r1, [r5, r0]
	mov r0, #9
	pop {r3, r4, r5, r6, r7, pc}
_02218CDA:
	ldrh r0, [r4, #0x1c]
	add r2, r7, #0
	mov r3, #0
	str r0, [sp]
	ldr r0, [r4]
	ldr r1, [r4, #0x10]
	bl MOD11_02230370
	cmp r0, #1
	bne _02218D00
	ldr r2, _02218E38 ; =0x0000114D
	ldrh r1, [r4, #0x1c]
	ldrb r2, [r5, r2]
	ldr r0, [r4]
	ldr r3, [r4, #0xc]
	bl MOD09_0221944C
	mov r0, #0xd
	pop {r3, r4, r5, r6, r7, pc}
_02218D00:
	cmp r6, #3
	bne _02218D68
	ldr r0, [r4]
	bl MOD11_0222FF74
	mov r1, #1
	tst r0, r1
	bne _02218D22
	ldr r2, _02218E38 ; =0x0000114D
	ldrh r1, [r4, #0x1c]
	ldrb r2, [r5, r2]
	ldr r0, [r4]
	ldr r3, [r4, #0xc]
	bl MOD09_0221944C
	mov r0, #0xd
	pop {r3, r4, r5, r6, r7, pc}
_02218D22:
	ldr r3, [r4, #0xc]
	add r0, r1, #0
	mov r1, #0x1a
	mov r2, #0xc7
	bl NewMsgDataFromNarc
	mov r1, #0x24
	add r7, r0, #0
	bl NewString_ReadMsgData
	add r6, r0, #0
	ldr r0, [r5, #0x14]
	ldr r2, [r4, #4]
	mov r1, #0
	bl BufferPlayersName
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_dtor
	add r0, r7, #0
	bl DestroyMsgData
	add r0, r5, #0
	bl MOD09_02219BE0
	ldr r0, _02218E40 ; =0x0000114B
	mov r1, #8
	strb r1, [r5, r0]
	mov r0, #9
	pop {r3, r4, r5, r6, r7, pc}
_02218D68:
	ldr r0, [r5, #0x10]
	ldr r2, [r5, #0x18]
	mov r1, #0x22
	bl ReadMsgDataIntoString
	add r0, r5, #0
	bl MOD09_02219BE0
	ldr r0, _02218E40 ; =0x0000114B
	mov r1, #8
	strb r1, [r5, r0]
	mov r0, #9
	pop {r3, r4, r5, r6, r7, pc}
_02218D82:
	cmp r1, #2
	bne _02218E32
	add r0, r4, #0
	add r0, #0x22
	ldrb r0, [r0]
	cmp r0, #1
	bne _02218DAA
	ldr r0, [r5, #0x10]
	ldr r2, [r5, #0x18]
	mov r1, #0x2c
	bl ReadMsgDataIntoString
	add r0, r5, #0
	bl MOD09_02219BE0
	ldr r0, _02218E40 ; =0x0000114B
	mov r1, #8
	strb r1, [r5, r0]
	mov r0, #9
	pop {r3, r4, r5, r6, r7, pc}
_02218DAA:
	add r0, r4, #0
	add r0, #0x23
	ldrb r0, [r0]
	cmp r0, #1
	bne _02218DCE
	ldr r0, [r5, #0x10]
	ldr r2, [r5, #0x18]
	mov r1, #0x2f
	bl ReadMsgDataIntoString
	add r0, r5, #0
	bl MOD09_02219BE0
	ldr r0, _02218E40 ; =0x0000114B
	mov r1, #8
	strb r1, [r5, r0]
	mov r0, #9
	pop {r3, r4, r5, r6, r7, pc}
_02218DCE:
	add r0, r4, #0
	add r0, #0x24
	ldrb r0, [r0]
	cmp r0, #1
	bne _02218DF2
	ldr r0, [r5, #0x10]
	ldr r2, [r5, #0x18]
	mov r1, #0x30
	bl ReadMsgDataIntoString
	add r0, r5, #0
	bl MOD09_02219BE0
	ldr r0, _02218E40 ; =0x0000114B
	mov r1, #8
	strb r1, [r5, r0]
	mov r0, #9
	pop {r3, r4, r5, r6, r7, pc}
_02218DF2:
	ldr r0, [r4]
	ldr r1, [r4, #0x10]
	bl MOD11_0222FF88
	add r6, r0, #0
	ldr r0, [r4]
	bl MOD11_02230290
	add r4, r0, #0
	add r0, r6, #0
	bl GetPartyCount
	cmp r0, #6
	bne _02218E32
	add r0, r4, #0
	bl PCStorage_FindFirstBoxWithEmptySlot
	cmp r0, #0x12
	bne _02218E32
	ldr r0, [r5, #0x10]
	ldr r2, [r5, #0x18]
	mov r1, #0x2d
	bl ReadMsgDataIntoString
	add r0, r5, #0
	bl MOD09_02219BE0
	ldr r0, _02218E40 ; =0x0000114B
	mov r1, #8
	strb r1, [r5, r0]
	mov r0, #9
	pop {r3, r4, r5, r6, r7, pc}
_02218E32:
	mov r0, #0xd
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02218E38: .word 0x0000114D
_02218E3C: .word 0x00000175
_02218E40: .word 0x0000114B

	thumb_func_start MOD09_02218E44
MOD09_02218E44: ; 0x02218E44
	push {r3, lr}
	mov r1, #0
	bl MOD09_022193BC
	mov r0, #1
	pop {r3, pc}

	thumb_func_start MOD09_02218E50
MOD09_02218E50: ; 0x02218E50
	push {r3, lr}
	mov r1, #1
	bl MOD09_022193BC
	mov r0, #2
	pop {r3, pc}

	thumb_func_start MOD09_02218E5C
MOD09_02218E5C: ; 0x02218E5C
	push {r3, lr}
	mov r1, #2
	bl MOD09_022193BC
	mov r0, #3
	pop {r3, pc}

	thumb_func_start MOD09_02218E68
MOD09_02218E68: ; 0x02218E68
	push {r3, lr}
	add r0, #0x1c
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #3
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD09_02218E78
MOD09_02218E78: ; 0x02218E78
	push {r3, lr}
	add r0, #0x32
	ldrb r0, [r0]
	bl FUN_0201BD70
	cmp r0, #0
	bne _02218E8A
	mov r0, #0xa
	pop {r3, pc}
_02218E8A:
	mov r0, #9
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD09_02218E90
MOD09_02218E90: ; 0x02218E90
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02218EB0 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	bne _02218EA6
	bl FUN_02020AA4
	cmp r0, #1
	bne _02218EAC
_02218EA6:
	ldr r0, _02218EB4 ; =0x0000114B
	ldrb r0, [r4, r0]
	pop {r4, pc}
_02218EAC:
	mov r0, #0xa
	pop {r4, pc}
	.align 2, 0
_02218EB0: .word gMain
_02218EB4: .word 0x0000114B

	thumb_func_start MOD09_02218EB8
MOD09_02218EB8: ; 0x02218EB8
	ldr r1, _02218ECC ; =0x0000113E
	ldrb r2, [r0, r1]
	cmp r2, #2
	bne _02218EC6
	add r1, #0xd
	ldrb r0, [r0, r1]
	bx lr
_02218EC6:
	mov r0, #0xb
	bx lr
	nop
_02218ECC: .word 0x0000113E

	thumb_func_start MOD09_02218ED0
MOD09_02218ED0: ; 0x02218ED0
	push {lr}
	sub sp, #0xc
	mov r2, #0
	str r2, [sp]
	mov r1, #0x10
	str r1, [sp, #4]
	str r2, [sp, #8]
	mov r1, #0xa
	add r3, r1, #0
	ldr r0, [r0, #8]
	ldr r2, _02218EF4 ; =0x0000FFFF
	sub r3, #0x12
	bl FUN_02003210
	mov r0, #0xe
	add sp, #0xc
	pop {pc}
	nop
_02218EF4: .word 0x0000FFFF

	thumb_func_start MOD09_02218EF8
MOD09_02218EF8: ; 0x02218EF8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	ldr r0, [r5, #8]
	bl FUN_020038E4
	cmp r0, #0
	beq _02218F0C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02218F0C:
	add r0, r5, #0
	bl MOD09_02219FE4
	add r0, r5, #0
	bl MOD09_02219520
	add r0, r5, #0
	bl MOD09_022192E4
	ldr r0, [r5, #4]
	bl MOD09_02219198
	ldr r0, [r5, #0x34]
	bl MOD09_0221AC28
	ldr r1, [r5]
	add r1, #0x25
	strb r0, [r1]
	ldr r0, [r5, #0x34]
	bl MOD09_0221AC1C
	mov r0, #2
	bl FUN_02002CF8
	ldr r1, [r5]
	ldrh r0, [r1, #0x1c]
	cmp r0, #0
	beq _02218F78
	ldr r0, [r1]
	bl MOD11_02230218
	add r6, r0, #0
	mov r4, #0
_02218F4E:
	ldr r3, [r5]
	add r0, r6, #0
	add r2, r3, r4
	add r3, r3, r4
	add r2, #0x27
	add r3, #0x2c
	ldrb r2, [r2]
	ldrb r3, [r3]
	add r1, r4, #0
	bl FUN_0206F1B8
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #5
	blo _02218F4E
	ldr r1, _02218F8C ; =0x0000114D
	add r0, r6, #0
	ldrb r1, [r5, r1]
	bl FUN_0206F1EC
_02218F78:
	ldr r0, [r5]
	mov r1, #1
	add r0, #0x26
	strb r1, [r0]
	add r0, r7, #0
	bl FUN_0200621C
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02218F8C: .word 0x0000114D

	thumb_func_start MOD09_02218F90
MOD09_02218F90: ; 0x02218F90
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	bl FUN_020038E4
	cmp r0, #0
	beq _02218FA2
	mov r0, #0xc
	pop {r4, pc}
_02218FA2:
	ldr r0, _022190BC ; =0x00001159
	ldrb r0, [r4, r0]
	cmp r0, #4
	bls _02218FAC
	b _022190B6
_02218FAC:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02218FB8: ; jump table
	.short _02218FC2 - _02218FB8 - 2 ; case 0
	.short _02219004 - _02218FB8 - 2 ; case 1
	.short _02219014 - _02218FB8 - 2 ; case 2
	.short _0221905E - _02218FB8 - 2 ; case 3
	.short _0221906E - _02218FB8 - 2 ; case 4
_02218FC2:
	ldr r0, [r4, #0x38]
	bl MOD11_0225D824
	cmp r0, #1
	bne _02218FFA
	ldr r0, _022190C0 ; =0x000005DD
	bl PlaySE
	ldr r0, _022190C4 ; =0x0000114D
	mov r1, #2
	strb r1, [r4, r0]
	mov r2, #0xc
	sub r0, r0, #2
	strb r2, [r4, r0]
	add r0, r4, #0
	mov r2, #0
	bl MOD09_0221A9D8
	ldr r0, _022190C8 ; =0x0000115A
	mov r1, #0
	strb r1, [r4, r0]
	sub r1, r0, #1
	ldrb r1, [r4, r1]
	sub r0, r0, #1
	add r1, r1, #1
	strb r1, [r4, r0]
	mov r0, #0xb
	pop {r4, pc}
_02218FFA:
	ldr r0, _022190C8 ; =0x0000115A
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _022190B6
_02219004:
	add r0, r4, #0
	bl MOD09_02218E50
	ldr r0, _022190BC ; =0x00001159
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _022190B6
_02219014:
	ldr r0, [r4, #0x38]
	bl MOD11_0225D824
	cmp r0, #1
	bne _02219054
	ldr r0, _022190C0 ; =0x000005DD
	bl PlaySE
	ldr r0, _022190C4 ; =0x0000114D
	ldr r3, [r4]
	ldrb r1, [r4, r0]
	mov r2, #0
	sub r0, r0, #2
	add r1, r3, r1
	add r1, #0x27
	strb r2, [r1]
	mov r1, #0xc
	strb r1, [r4, r0]
	add r0, r4, #0
	mov r1, #6
	bl MOD09_0221A9D8
	ldr r0, _022190C8 ; =0x0000115A
	mov r1, #0
	strb r1, [r4, r0]
	sub r1, r0, #1
	ldrb r1, [r4, r1]
	sub r0, r0, #1
	add r1, r1, #1
	strb r1, [r4, r0]
	mov r0, #0xb
	pop {r4, pc}
_02219054:
	ldr r0, _022190C8 ; =0x0000115A
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _022190B6
_0221905E:
	add r0, r4, #0
	bl MOD09_02218E5C
	ldr r0, _022190BC ; =0x00001159
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _022190B6
_0221906E:
	ldr r0, [r4, #0x38]
	bl MOD11_0225D824
	cmp r0, #1
	bne _022190AE
	ldr r0, _022190C0 ; =0x000005DD
	bl PlaySE
	ldr r1, _022190C4 ; =0x0000114D
	ldr r2, [r4]
	ldrb r1, [r4, r1]
	add r0, r4, #0
	add r1, r2, r1
	add r1, #0x27
	ldrb r1, [r1]
	bl MOD09_02219D94
	ldr r1, [r4]
	mov r2, #0
	strh r0, [r1, #0x1c]
	ldr r0, _022190C4 ; =0x0000114D
	ldrb r1, [r4, r0]
	ldr r0, [r4]
	strb r1, [r0, #0x1e]
	add r0, r4, #0
	mov r1, #0xf
	bl MOD09_0221A9D8
	add r0, r4, #0
	bl MOD09_02218C58
	pop {r4, pc}
_022190AE:
	ldr r0, _022190C8 ; =0x0000115A
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
_022190B6:
	mov r0, #0xc
	pop {r4, pc}
	nop
_022190BC: .word 0x00001159
_022190C0: .word 0x000005DD
_022190C4: .word 0x0000114D
_022190C8: .word 0x0000115A

	thumb_func_start MOD09_022190CC
MOD09_022190CC: ; 0x022190CC
	push {r4, r5, lr}
	sub sp, #0x64
	ldr r5, _02219188 ; =0x0221BB84
	add r3, sp, #0x54
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	mov r1, #1
	bl SetScreenModeAndDisable
	ldr r5, _0221918C ; =0x0221BBCC
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #6
	str r0, [r3]
	ldr r0, [r4, #4]
	mov r3, #0
	bl InitBgFromTemplate
	ldr r5, _02219190 ; =0x0221BBB0
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #5
	str r0, [r3]
	ldr r0, [r4, #4]
	mov r3, #0
	bl InitBgFromTemplate
	ldr r0, [r4, #4]
	mov r1, #5
	bl BgClearTilemapBufferAndCommit
	ldr r5, _02219194 ; =0x0221BB94
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #4
	str r0, [r3]
	ldr r0, [r4, #4]
	mov r3, #0
	bl InitBgFromTemplate
	ldr r0, [r4, #4]
	mov r1, #4
	bl BgClearTilemapBufferAndCommit
	ldr r3, [r4]
	mov r0, #5
	ldr r3, [r3, #0xc]
	mov r1, #0x20
	mov r2, #0
	bl BG_ClearCharDataRange
	ldr r3, [r4]
	mov r0, #4
	ldr r3, [r3, #0xc]
	mov r1, #0x20
	mov r2, #0
	bl BG_ClearCharDataRange
	ldr r0, [r4, #4]
	mov r1, #5
	bl ScheduleBgTilemapBufferTransfer
	ldr r0, [r4, #4]
	mov r1, #4
	bl ScheduleBgTilemapBufferTransfer
	add sp, #0x64
	pop {r4, r5, pc}
	.align 2, 0
_02219188: .word MOD9_0221BB84
_0221918C: .word MOD9_0221BBCC
_02219190: .word MOD9_0221BBB0
_02219194: .word MOD9_0221BB94

	thumb_func_start MOD09_02219198
MOD09_02219198: ; 0x02219198
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x17
	mov r1, #0
	bl GX_EngineBToggleLayers
	add r0, r4, #0
	mov r1, #4
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	mov r1, #5
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	mov r1, #6
	bl FreeBgTilemapBuffer
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD09_022191C0
MOD09_022191C0: ; 0x022191C0
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5]
	mov r1, #2
	ldr r0, [r0, #0xc]
	mov r3, #6
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x4d
	bl GfGfxLoader_LoadCharData
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	ldr r0, [r5]
	mov r3, #6
	ldr r0, [r0, #0xc]
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x4d
	bl GfGfxLoader_LoadScrnData
	ldr r2, [r5]
	mov r0, #0x4d
	ldr r2, [r2, #0xc]
	mov r1, #1
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0x10
	add r4, r0, #0
	bl NNS_G2dGetUnpackedScreenData
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	add r1, #0xc
	bl MOD09_0221A2F4
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #6
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r3, [r5]
	ldr r0, [r5, #8]
	ldr r3, [r3, #0xc]
	mov r1, #0x4d
	mov r2, #3
	bl PaletteData_LoadNarc
	mov r0, #1
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xf0
	str r0, [sp, #8]
	ldr r3, [r5]
	ldr r0, [r5, #8]
	ldr r3, [r3, #0xc]
	mov r1, #0xe
	mov r2, #7
	bl PaletteData_LoadNarc
	ldr r0, [r5]
	ldr r0, [r0]
	bl MOD11_02230E44
	add r4, r0, #0
	bl FUN_0200CD60
	add r1, r0, #0
	ldr r0, _022192A0 ; =0x000003E2
	mov r3, #4
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5]
	ldr r0, [r0, #0xc]
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x26
	bl GfGfxLoader_LoadCharData
	add r0, r4, #0
	bl FUN_0200CD64
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xe0
	str r0, [sp, #8]
	ldr r3, [r5]
	ldr r0, [r5, #8]
	ldr r3, [r3, #0xc]
	mov r1, #0x26
	bl PaletteData_LoadNarc
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_022192A0: .word 0x000003E2

	thumb_func_start MOD09_022192A4
MOD09_022192A4: ; 0x022192A4
	push {r4, lr}
	add r4, r0, #0
	ldr r3, [r4]
	mov r0, #0
	ldr r3, [r3, #0xc]
	mov r1, #0x1a
	mov r2, #2
	bl NewMsgDataFromNarc
	str r0, [r4, #0x10]
	ldr r3, [r4]
	mov r0, #0xf
	ldr r3, [r3, #0xc]
	mov r1, #0xe
	mov r2, #0
	bl MessagePrinter_new
	str r0, [r4, #0xc]
	ldr r0, [r4]
	ldr r0, [r0, #0xc]
	bl ScrStrBufs_new
	str r0, [r4, #0x14]
	ldr r1, [r4]
	mov r0, #2
	ldr r1, [r1, #0xc]
	lsl r0, r0, #8
	bl String_ctor
	str r0, [r4, #0x18]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD09_022192E4
MOD09_022192E4: ; 0x022192E4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	bl DestroyMsgData
	ldr r0, [r4, #0xc]
	bl MessagePrinter_delete
	ldr r0, [r4, #0x14]
	bl ScrStrBufs_delete
	ldr r0, [r4, #0x18]
	bl String_dtor
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD09_02219304
MOD09_02219304: ; 0x02219304
	push {r4, lr}
	add r4, r0, #0
	cmp r1, #0
	beq _02219316
	cmp r1, #1
	beq _02219330
	cmp r1, #2
	beq _0221934C
	pop {r4, pc}
_02219316:
	mov r2, #0
	ldr r0, [r4, #4]
	mov r1, #6
	add r3, r2, #0
	bl ScheduleSetBgPosText
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #3
	mov r3, #0
	bl ScheduleSetBgPosText
	pop {r4, pc}
_02219330:
	mov r1, #6
	add r3, r1, #0
	ldr r0, [r4, #4]
	mov r2, #0
	add r3, #0xfa
	bl ScheduleSetBgPosText
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #3
	mov r3, #0
	bl ScheduleSetBgPosText
	pop {r4, pc}
_0221934C:
	mov r2, #0
	ldr r0, [r4, #4]
	mov r1, #6
	add r3, r2, #0
	bl ScheduleSetBgPosText
	mov r2, #3
	add r3, r2, #0
	ldr r0, [r4, #4]
	mov r1, #6
	add r3, #0xfd
	bl ScheduleSetBgPosText
	pop {r4, pc}

	thumb_func_start MOD09_02219368
MOD09_02219368: ; 0x02219368
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	cmp r1, #2
	bne _022193B2
	mov r0, #0x1c
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, _022193B8 ; =0x0000114D
	mov r1, #6
	ldrb r0, [r4, r0]
	mov r2, #2
	mov r3, #0x23
	add r0, #8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	bl BgTilemapRectChangePalette
	mov r0, #0x1c
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	ldr r0, _022193B8 ; =0x0000114D
	mov r1, #6
	ldrb r0, [r4, r0]
	mov r2, #2
	mov r3, #0x28
	add r0, #8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	bl BgTilemapRectChangePalette
_022193B2:
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_022193B8: .word 0x0000114D

	thumb_func_start MOD09_022193BC
MOD09_022193BC: ; 0x022193BC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD09_02219368
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02219304
	ldr r0, [r5, #4]
	mov r1, #4
	mov r2, #0
	bl BgFillTilemapBufferAndSchedule
	ldr r0, [r5, #4]
	mov r1, #5
	mov r2, #0
	bl BgFillTilemapBufferAndSchedule
	add r0, r5, #0
	bl MOD09_02219510
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02219498
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_0221953C
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_0221AAF0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_0221A1DC
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_0221A2BC
	ldr r1, _02219420 ; =0x0000114C
	add r0, r5, #0
	strb r4, [r5, r1]
	ldrb r1, [r5, r1]
	bl MOD09_0221A044
	pop {r3, r4, r5, pc}
	nop
_02219420: .word 0x0000114C

	thumb_func_start MOD09_02219424
MOD09_02219424: ; 0x02219424
	ldr r3, _0221942C ; =FUN_02020988
	add r0, r1, #0
	bx r3
	nop
_0221942C: .word FUN_02020988

	thumb_func_start MOD09_02219430
MOD09_02219430: ; 0x02219430
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r4, [r5]
	ldr r0, [r4]
	bl MOD11_0222FF78
	add r1, r0, #0
	ldr r0, [r5]
	ldr r3, [r4, #0x10]
	ldr r0, [r0]
	mov r2, #2
	bl MOD11_0224C474
	pop {r3, r4, r5, pc}

	thumb_func_start MOD09_0221944C
MOD09_0221944C: ; 0x0221944C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r7, r3, #0
	add r5, r0, #0
	add r6, r2, #0
	bl MOD11_02230214
	add r1, r4, #0
	mov r2, #1
	add r3, r7, #0
	bl Bag_TakeItem
	add r0, r5, #0
	bl MOD11_02230218
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_0206F1E4
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD09_02219474
MOD09_02219474: ; 0x02219474
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r4, #4]
	ldr r2, _02219490 ; =0x0221BC2C
	add r1, #0x1c
	bl AddWindow
	ldr r1, _02219494 ; =0x0000114C
	add r0, r4, #0
	ldrb r1, [r4, r1]
	bl MOD09_02219498
	pop {r4, pc}
	.align 2, 0
_02219490: .word MOD9_0221BC2C
_02219494: .word 0x0000114C

	thumb_func_start MOD09_02219498
MOD09_02219498: ; 0x02219498
	push {r4, r5, r6, lr}
	add r5, r0, #0
	cmp r1, #0
	beq _022194AA
	cmp r1, #1
	beq _022194B4
	cmp r1, #2
	beq _022194BE
	b _022194C6
_022194AA:
	mov r1, #5
	add r0, #0x30
	ldr r6, _02219504 ; =0x0221BC54
	strb r1, [r0]
	b _022194C6
_022194B4:
	mov r1, #0x1a
	add r0, #0x30
	ldr r6, _02219508 ; =0x0221BCAC
	strb r1, [r0]
	b _022194C6
_022194BE:
	ldr r6, _0221950C ; =0x0221BC34
	mov r1, #4
	add r0, #0x30
	strb r1, [r0]
_022194C6:
	add r1, r5, #0
	ldr r0, [r5]
	add r1, #0x30
	ldrb r1, [r1]
	ldr r0, [r0, #0xc]
	bl AllocWindows
	str r0, [r5, #0x2c]
	add r0, r5, #0
	add r0, #0x30
	ldrb r0, [r0]
	mov r4, #0
	cmp r0, #0
	bls _02219502
_022194E2:
	ldr r2, [r5, #0x2c]
	lsl r1, r4, #4
	add r1, r2, r1
	lsl r2, r4, #3
	ldr r0, [r5, #4]
	add r2, r6, r2
	bl AddWindow
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	add r0, r5, #0
	add r0, #0x30
	ldrb r0, [r0]
	cmp r4, r0
	blo _022194E2
_02219502:
	pop {r4, r5, r6, pc}
	.align 2, 0
_02219504: .word MOD9_0221BC54
_02219508: .word MOD9_0221BCAC
_0221950C: .word MOD9_0221BC34

	thumb_func_start MOD09_02219510
MOD09_02219510: ; 0x02219510
	add r1, r0, #0
	ldr r0, [r1, #0x2c]
	add r1, #0x30
	ldr r3, _0221951C ; =FUN_020191A4
	ldrb r1, [r1]
	bx r3
	.align 2, 0
_0221951C: .word WindowArray_dtor

	thumb_func_start MOD09_02219520
MOD09_02219520: ; 0x02219520
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	add r1, #0x30
	ldrb r1, [r1]
	ldr r0, [r4, #0x2c]
	bl WindowArray_dtor
	add r4, #0x1c
	add r0, r4, #0
	bl RemoveWindow
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD09_0221953C
MOD09_0221953C: ; 0x0221953C
	push {r3, lr}
	cmp r1, #0
	beq _0221954C
	cmp r1, #1
	beq _02219552
	cmp r1, #2
	beq _02219558
	pop {r3, pc}
_0221954C:
	bl MOD09_022195B8
	pop {r3, pc}
_02219552:
	bl MOD09_02219A74
	pop {r3, pc}
_02219558:
	bl MOD09_02219B60
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD09_02219560
MOD09_02219560: ; 0x02219560
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	ldr r5, [r0, #0x2c]
	lsl r4, r1, #4
	ldr r0, [r0, #0x10]
	add r1, r2, #0
	add r6, r3, #0
	bl NewString_ReadMsgData
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x10]
	add r0, r6, #0
	mov r2, #0
	bl FUN_02002E14
	add r7, r0, #0
	add r0, r5, r4
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r0, r0, r7
	lsr r3, r0, #1
	ldr r0, [sp, #0x28]
	ldr r2, [sp, #0x10]
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x2c]
	add r1, r6, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, r5, r4
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r5, r4
	bl ScheduleWindowCopyToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD09_022195B8
MOD09_022195B8: ; 0x022195B8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r6, #0
	add r5, r0, #0
	add r4, r6, #0
	add r7, r6, #0
_022195C4:
	ldr r0, [r5, #0x2c]
	add r1, r7, #0
	add r0, r0, r4
	bl FillWindowPixelBuffer
	add r6, r6, #1
	add r4, #0x10
	cmp r6, #5
	blo _022195C4
	mov r0, #8
	str r0, [sp]
	ldr r0, _02219690 ; =0x00030201
	mov r1, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r2, r1, #0
	mov r3, #2
	bl MOD09_02219560
	mov r0, #0x18
	str r0, [sp]
	ldr r0, _02219690 ; =0x00030201
	mov r1, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #1
	mov r3, #2
	bl MOD09_02219560
	mov r0, #8
	str r0, [sp]
	ldr r0, _02219690 ; =0x00030201
	mov r2, #2
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #1
	add r3, r2, #0
	bl MOD09_02219560
	mov r0, #0x18
	str r0, [sp]
	ldr r0, _02219690 ; =0x00030201
	mov r1, #1
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #3
	mov r3, #2
	bl MOD09_02219560
	mov r0, #8
	str r0, [sp]
	ldr r0, _02219690 ; =0x00030201
	mov r1, #2
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #7
	add r3, r1, #0
	bl MOD09_02219560
	mov r0, #8
	str r0, [sp]
	ldr r0, _02219690 ; =0x00030201
	mov r1, #3
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #6
	mov r3, #2
	bl MOD09_02219560
	ldr r0, [r5]
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	beq _0221968A
	ldr r0, [r5, #0x10]
	mov r1, #8
	bl NewString_ReadMsgData
	add r4, r0, #0
	mov r0, #6
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02219690 ; =0x00030201
	mov r3, #0
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r0, [r5, #0x2c]
	mov r1, #2
	add r0, #0x40
	add r2, r4, #0
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl String_dtor
	ldr r0, [r5, #0x2c]
	add r0, #0x40
	bl ScheduleWindowCopyToVram
_0221968A:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02219690: .word 0x00030201

	thumb_func_start MOD09_02219694
MOD09_02219694: ; 0x02219694
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r4, [r5, #0x2c]
	lsl r6, r3, #4
	add r7, r1, #0
	add r0, r4, r6
	mov r1, #0
	str r2, [sp, #0x10]
	bl FillWindowPixelBuffer
	ldr r0, _02219730 ; =0x0000114D
	lsl r7, r7, #2
	ldrb r1, [r5, r0]
	mov r0, #0x90
	mul r0, r1
	add r0, r5, r0
	add r0, r0, r7
	ldrh r0, [r0, #0x3c]
	cmp r0, #0
	beq _02219726
	ldr r1, [sp, #0x10]
	ldr r0, [r5, #0x10]
	lsl r2, r1, #3
	ldr r1, _02219734 ; =0x0221BC7C
	ldr r1, [r1, r2]
	bl NewString_ReadMsgData
	ldr r2, _02219730 ; =0x0000114D
	str r0, [sp, #0x14]
	ldrb r3, [r5, r2]
	mov r2, #0x90
	ldr r0, [r5, #0x14]
	mul r2, r3
	add r2, r5, r2
	add r2, r2, r7
	ldrh r2, [r2, #0x3c]
	mov r1, #0
	bl BufferItemName
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	ldr r2, [sp, #0x14]
	bl StringExpandPlaceholders
	ldr r0, [sp, #0x30]
	ldr r1, [r5, #0x18]
	mov r2, #0
	bl FUN_02002E14
	add r7, r0, #0
	add r0, r4, r6
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r0, r0, r7
	lsr r3, r0, #1
	mov r0, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x34]
	ldr r1, [sp, #0x30]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x18]
	add r0, r4, r6
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x14]
	bl String_dtor
_02219726:
	add r0, r4, r6
	bl ScheduleWindowCopyToVram
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02219730: .word 0x0000114D
_02219734: .word MOD9_0221BC7C

	thumb_func_start MOD09_02219738
MOD09_02219738: ; 0x02219738
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r4, [r5, #0x2c]
	lsl r7, r3, #4
	add r6, r1, #0
	add r0, r4, r7
	mov r1, #0
	str r2, [sp, #0x10]
	bl FillWindowPixelBuffer
	ldr r0, _022197C4 ; =0x0000114D
	lsl r6, r6, #2
	ldrb r1, [r5, r0]
	mov r0, #0x90
	mul r0, r1
	add r0, r5, r0
	add r0, r0, r6
	ldrh r0, [r0, #0x3e]
	cmp r0, #0
	beq _022197BA
	ldr r1, [sp, #0x10]
	ldr r0, [r5, #0x10]
	lsl r2, r1, #3
	ldr r1, _022197C8 ; =0x0221BC80
	ldr r1, [r1, r2]
	bl NewString_ReadMsgData
	mov r1, #0
	str r0, [sp, #0x14]
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, _022197C4 ; =0x0000114D
	ldr r0, [r5, #0x14]
	ldrb r3, [r5, r2]
	mov r2, #0x90
	mul r2, r3
	add r2, r5, r2
	add r2, r2, r6
	ldrh r2, [r2, #0x3e]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	ldr r2, [sp, #0x14]
	bl StringExpandPlaceholders
	ldr r0, [sp, #0x34]
	mov r3, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x38]
	ldr r1, [sp, #0x30]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r2, [r5, #0x18]
	add r0, r4, r7
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x14]
	bl String_dtor
_022197BA:
	add r0, r4, r7
	bl ScheduleWindowCopyToVram
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022197C4: .word 0x0000114D
_022197C8: .word MOD9_0221BC80

	thumb_func_start MOD09_022197CC
MOD09_022197CC: ; 0x022197CC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r0, #0
	ldr r0, _02219830 ; =0x0000114D
	add r5, r1, #0
	ldrb r0, [r6, r0]
	ldr r1, [r6]
	add r0, r1, r0
	add r0, #0x2c
	ldrb r1, [r0]
	mov r0, #6
	mul r0, r1
	str r0, [sp, #0xc]
	add r0, r6, #0
	add r0, #0x31
	ldrb r0, [r0]
	cmp r0, #0
	bne _022197F4
	mov r4, #0
	b _022197F6
_022197F4:
	mov r4, #0xc
_022197F6:
	mov r0, #2
	str r0, [sp]
	ldr r0, _02219834 ; =0x00030201
	ldr r1, [sp, #0xc]
	lsl r7, r5, #1
	str r0, [sp, #4]
	add r0, r6, #0
	add r1, r5, r1
	add r2, r5, #0
	add r3, r4, r7
	bl MOD09_02219694
	mov r0, #0
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, _02219838 ; =0x00010200
	ldr r1, [sp, #0xc]
	add r3, r4, #1
	str r0, [sp, #8]
	add r0, r6, #0
	add r1, r5, r1
	add r2, r5, #0
	add r3, r3, r7
	bl MOD09_02219738
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02219830: .word 0x0000114D
_02219834: .word 0x00030201
_02219838: .word 0x00010200

	thumb_func_start MOD09_0221983C
MOD09_0221983C: ; 0x0221983C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	mov r2, #0
	add r4, r0, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x13
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r4, #4]
	mov r1, #5
	add r3, r2, #0
	bl FillBgTilemapRect
	mov r5, #0
_0221985E:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD09_022197CC
	add r0, r5, #1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #6
	blo _0221985E
	add r0, r4, #0
	add r0, #0x31
	ldrb r1, [r0]
	mov r0, #1
	add r4, #0x31
	eor r0, r1
	strb r0, [r4]
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD09_02219884
MOD09_02219884: ; 0x02219884
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	mov r0, #0x19
	ldr r1, [r5, #0x2c]
	lsl r0, r0, #4
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, [r5, #0x10]
	mov r1, #0x1c
	ldr r4, [r5, #0x2c]
	bl NewString_ReadMsgData
	str r0, [sp, #0x10]
	mov r0, #0
	ldr r1, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02002E14
	add r7, r0, #0
	mov r0, #0x19
	lsl r0, r0, #4
	add r0, r4, r0
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r0, r0, r7
	lsr r6, r0, #1
	mov r0, #4
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022199AC ; =0x00010200
	ldr r2, [sp, #0x10]
	str r0, [sp, #8]
	mov r0, #0x19
	lsl r0, r0, #4
	mov r1, #0
	add r0, r4, r0
	add r3, r6, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	bl String_dtor
	ldr r0, [r5, #0x10]
	mov r1, #0x1d
	bl NewString_ReadMsgData
	mov r1, #0
	str r0, [sp, #0x14]
	ldr r3, _022199B0 ; =0x0000114D
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, _022199B0 ; =0x0000114D
	add r3, r3, #7
	ldrb r2, [r5, r2]
	ldr r0, [r5, #0x14]
	add r2, r5, r2
	ldrb r2, [r2, r3]
	mov r3, #2
	add r2, r2, #1
	bl BufferIntegerAsString
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	ldr r2, [sp, #0x14]
	bl StringExpandPlaceholders
	mov r0, #4
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022199AC ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r2, [r5, #0x18]
	add r0, r4, r0
	add r3, r6, r7
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x14]
	bl String_dtor
	ldr r0, [r5, #0x10]
	mov r1, #0x1e
	bl NewString_ReadMsgData
	mov r1, #0
	add r7, r0, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r3, _022199B0 ; =0x0000114D
	ldr r2, [r5]
	ldrb r3, [r5, r3]
	ldr r0, [r5, #0x14]
	add r2, r2, r3
	add r2, #0x2c
	ldrb r2, [r2]
	mov r3, #2
	add r2, r2, #1
	bl BufferIntegerAsString
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	add r2, r7, #0
	bl StringExpandPlaceholders
	mov r0, #0
	ldr r1, [r5, #0x18]
	add r2, r0, #0
	bl FUN_02002E14
	add r3, r0, #0
	mov r0, #4
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022199AC ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r2, [r5, #0x18]
	add r0, r4, r0
	sub r3, r6, r3
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
	mov r0, #0x19
	lsl r0, r0, #4
	add r0, r4, r0
	bl ScheduleWindowCopyToVram
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022199AC: .word 0x00010200
_022199B0: .word 0x0000114D

	thumb_func_start MOD09_022199B4
MOD09_022199B4: ; 0x022199B4
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #6
	ldr r1, [r4, #0x2c]
	lsl r0, r0, #6
	add r0, r1, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, _02219A6C ; =0x0000114D
	ldrb r0, [r4, r0]
	cmp r0, #3
	bhi _02219A68
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022199DC: ; jump table
	.short _022199E4 - _022199DC - 2 ; case 0
	.short _02219A10 - _022199DC - 2 ; case 1
	.short _02219A3C - _022199DC - 2 ; case 2
	.short _02219A54 - _022199DC - 2 ; case 3
_022199E4:
	mov r0, #4
	str r0, [sp]
	ldr r0, _02219A70 ; =0x00010200
	mov r1, #0x18
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x16
	mov r3, #0
	bl MOD09_02219560
	mov r0, #0x14
	str r0, [sp]
	ldr r0, _02219A70 ; =0x00010200
	mov r1, #0x18
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x17
	mov r3, #0
	bl MOD09_02219560
	add sp, #8
	pop {r4, pc}
_02219A10:
	mov r0, #4
	str r0, [sp]
	ldr r0, _02219A70 ; =0x00010200
	mov r1, #0x18
	str r0, [sp, #4]
	add r0, r4, #0
	add r2, r1, #0
	mov r3, #0
	bl MOD09_02219560
	mov r0, #0x14
	str r0, [sp]
	ldr r0, _02219A70 ; =0x00010200
	mov r1, #0x18
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x19
	mov r3, #0
	bl MOD09_02219560
	add sp, #8
	pop {r4, pc}
_02219A3C:
	mov r0, #0xc
	str r0, [sp]
	ldr r0, _02219A70 ; =0x00010200
	mov r1, #0x18
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x1a
	mov r3, #0
	bl MOD09_02219560
	add sp, #8
	pop {r4, pc}
_02219A54:
	mov r0, #0xc
	str r0, [sp]
	ldr r0, _02219A70 ; =0x00010200
	mov r1, #0x18
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x1b
	mov r3, #0
	bl MOD09_02219560
_02219A68:
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_02219A6C: .word 0x0000114D
_02219A70: .word 0x00010200

	thumb_func_start MOD09_02219A74
MOD09_02219A74: ; 0x02219A74
	push {r4, lr}
	add r4, r0, #0
	bl MOD09_0221983C
	add r0, r4, #0
	bl MOD09_022199B4
	add r0, r4, #0
	bl MOD09_02219884
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD09_02219A8C
MOD09_02219A8C: ; 0x02219A8C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5, #0x10]
	add r6, r1, #0
	mov r1, #9
	ldr r4, [r5, #0x2c]
	bl NewString_ReadMsgData
	ldr r2, _02219AF4 ; =0x0000114D
	add r7, r0, #0
	ldrb r3, [r5, r2]
	mov r2, #0x90
	ldr r0, [r5, #0x14]
	mul r2, r3
	add r2, r5, r2
	lsl r3, r6, #2
	add r2, r2, r3
	ldrh r2, [r2, #0x3c]
	mov r1, #0
	bl BufferItemName
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	add r2, r7, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02219AF8 ; =0x00010200
	add r3, r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x18]
	add r0, r4, #0
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
	add r0, r4, #0
	bl ScheduleWindowCopyToVram
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02219AF4: .word 0x0000114D
_02219AF8: .word 0x00010200

	thumb_func_start MOD09_02219AFC
MOD09_02219AFC: ; 0x02219AFC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r6, r1, #0
	ldr r1, [r5]
	ldr r4, [r5, #0x2c]
	ldr r1, [r1, #0xc]
	mov r0, #0x82
	add r4, #0x20
	bl String_ctor
	ldr r1, _02219B58 ; =0x0000114D
	add r7, r0, #0
	ldrb r2, [r5, r1]
	mov r1, #0x90
	mul r1, r2
	add r2, r5, r1
	lsl r1, r6, #2
	add r1, r2, r1
	ldr r2, [r5]
	ldrh r1, [r1, #0x3c]
	ldr r2, [r2, #0xc]
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	bl GetItemDescIntoString
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02219B5C ; =0x00010200
	add r2, r7, #0
	str r0, [sp, #8]
	add r0, r4, #0
	mov r3, #4
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
	add r0, r4, #0
	bl ScheduleWindowCopyToVram
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02219B58: .word 0x0000114D
_02219B5C: .word 0x00010200

	thumb_func_start MOD09_02219B60
MOD09_02219B60: ; 0x02219B60
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	mov r6, #0
	add r5, r0, #0
	add r4, r6, #0
	add r7, r6, #0
_02219B6C:
	ldr r0, [r5, #0x2c]
	add r1, r7, #0
	add r0, r0, r4
	bl FillWindowPixelBuffer
	add r6, r6, #1
	add r4, #0x10
	cmp r6, #4
	blo _02219B6C
	ldr r0, _02219BD4 ; =0x0000114D
	ldr r1, [r5]
	ldrb r2, [r5, r0]
	add r0, r1, r2
	add r0, #0x27
	ldrb r4, [r0]
	add r0, r1, r2
	add r0, #0x2c
	ldrb r1, [r0]
	mov r0, #6
	add r6, r1, #0
	mul r6, r0
	add r0, r5, #0
	add r1, r4, r6
	bl MOD09_02219A8C
	mov r2, #0
	str r2, [sp]
	ldr r0, _02219BD8 ; =0x00010200
	str r2, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, r4, r6
	mov r3, #1
	bl MOD09_02219738
	add r0, r5, #0
	add r1, r4, r6
	bl MOD09_02219AFC
	mov r0, #6
	str r0, [sp]
	ldr r0, _02219BDC ; =0x00030201
	mov r1, #3
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x1f
	mov r3, #2
	bl MOD09_02219560
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02219BD4: .word 0x0000114D
_02219BD8: .word 0x00010200
_02219BDC: .word 0x00030201

	thumb_func_start MOD09_02219BE0
MOD09_02219BE0: ; 0x02219BE0
	push {r4, lr}
	ldr r2, _02219C04 ; =0x000003E2
	add r4, r0, #0
	add r0, #0x1c
	mov r1, #1
	mov r3, #0xe
	bl FUN_0200D0BC
	add r0, r4, #0
	add r0, #0x1c
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r0, r4, #0
	bl MOD09_02219C08
	pop {r4, pc}
	nop
_02219C04: .word 0x000003E2

	thumb_func_start MOD09_02219C08
MOD09_02219C08: ; 0x02219C08
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #1
	bl TextFlags_SetCanABSpeedUpPrint
	ldr r0, [r4]
	ldr r0, [r0]
	bl MOD11_02230E54
	mov r3, #0
	str r3, [sp]
	str r0, [sp, #4]
	str r3, [sp, #8]
	add r0, r4, #0
	ldr r2, [r4, #0x18]
	add r0, #0x1c
	mov r1, #1
	bl AddTextPrinterParameterized
	add r4, #0x32
	strb r0, [r4]
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start MOD09_02219C38
MOD09_02219C38: ; 0x02219C38
	push {r4, lr}
	add r4, r0, #0
	ldr r3, [r4]
	ldrh r1, [r3, #0x20]
	cmp r1, #0
	bne _02219C48
	mov r0, #0
	pop {r4, pc}
_02219C48:
	ldr r0, [r3, #8]
	ldr r3, [r3, #0xc]
	mov r2, #1
	bl Bag_HasItem
	cmp r0, #0
	bne _02219C62
	ldr r1, [r4]
	mov r0, #0
	strh r0, [r1, #0x20]
	ldr r1, [r4]
	strb r0, [r1, #0x1f]
	pop {r4, pc}
_02219C62:
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD09_02219C68
MOD09_02219C68: ; 0x02219C68
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _02219CB0 ; =0x0000114D
	ldr r6, [r5]
	ldrb r7, [r5, r0]
	mov r0, #0x90
	ldrh r2, [r6, #0x20]
	mul r0, r7
	mov r4, #0
	add r1, r5, r0
_02219C7C:
	ldrh r0, [r1, #0x3c]
	cmp r2, r0
	bne _02219CA6
	add r0, r4, #0
	mov r1, #6
	bl _u32_div_f
	add r0, r6, r7
	add r0, #0x27
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #6
	bl _u32_div_f
	ldr r1, _02219CB0 ; =0x0000114D
	ldr r2, [r5]
	ldrb r1, [r5, r1]
	add r1, r2, r1
	add r1, #0x2c
	strb r0, [r1]
	pop {r3, r4, r5, r6, r7, pc}
_02219CA6:
	add r4, r4, #1
	add r1, r1, #4
	cmp r4, #0x24
	blo _02219C7C
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02219CB0: .word 0x0000114D

	thumb_func_start MOD09_02219CB4
MOD09_02219CB4: ; 0x02219CB4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0
	str r0, [sp, #4]
_02219CBE:
	mov r0, #0
	str r0, [sp]
	ldr r0, [sp, #4]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
_02219CCA:
	ldr r0, [r4]
	ldr r2, [sp]
	ldr r0, [r0, #8]
	lsl r2, r2, #0x10
	ldr r1, [sp, #8]
	lsr r2, r2, #0x10
	bl Bag_GetPocketSlotN
	add r5, r0, #0
	beq _02219D3C
	ldrh r0, [r5]
	cmp r0, #0
	beq _02219D34
	ldrh r1, [r5, #2]
	cmp r1, #0
	beq _02219D34
	ldr r2, [r4]
	mov r1, #0xd
	ldr r2, [r2, #0xc]
	bl GetItemAttr
	add r7, r0, #0
	ldr r1, _02219D88 ; =0x0221BD7C
	mov r0, #0
_02219CFA:
	mov r2, #1
	lsl r2, r0
	tst r2, r7
	beq _02219D2C
	ldrb r2, [r1]
	mov r3, #0x90
	add r6, r2, #0
	mul r6, r3
	add r3, r4, r2
	ldr r2, _02219D8C ; =0x0000114F
	ldrb r2, [r3, r2]
	add r3, r4, r6
	lsl r2, r2, #2
	add r2, r2, r3
	ldrh r3, [r5]
	strh r3, [r2, #0x3c]
	ldrh r3, [r5, #2]
	strh r3, [r2, #0x3e]
	ldrb r2, [r1]
	add r6, r4, r2
	ldr r2, _02219D8C ; =0x0000114F
	ldrb r2, [r6, r2]
	add r3, r2, #1
	ldr r2, _02219D8C ; =0x0000114F
	strb r3, [r6, r2]
_02219D2C:
	add r0, r0, #1
	add r1, r1, #1
	cmp r0, #5
	blo _02219CFA
_02219D34:
	ldr r0, [sp]
	add r0, r0, #1
	str r0, [sp]
	b _02219CCA
_02219D3C:
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #8
	blo _02219CBE
	mov r5, #0
	add r7, r5, #0
_02219D4A:
	ldr r0, _02219D8C ; =0x0000114F
	add r6, r4, r5
	ldrb r0, [r6, r0]
	cmp r0, #0
	bne _02219D5A
	ldr r0, _02219D90 ; =0x00001154
	strb r7, [r6, r0]
	b _02219D66
_02219D5A:
	sub r0, r0, #1
	mov r1, #6
	bl _s32_div_f
	ldr r1, _02219D90 ; =0x00001154
	strb r0, [r6, r1]
_02219D66:
	ldr r1, [r4]
	ldr r0, _02219D90 ; =0x00001154
	add r2, r1, r5
	add r2, #0x2c
	ldrb r0, [r6, r0]
	ldrb r2, [r2]
	cmp r0, r2
	bhs _02219D7C
	add r1, r1, r5
	add r1, #0x2c
	strb r0, [r1]
_02219D7C:
	add r5, r5, #1
	cmp r5, #5
	blo _02219D4A
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02219D88: .word MOD9_0221BD7C
_02219D8C: .word 0x0000114F
_02219D90: .word 0x00001154

	thumb_func_start MOD09_02219D94
MOD09_02219D94: ; 0x02219D94
	push {r3, r4}
	ldr r2, _02219DC4 ; =0x0000114D
	ldr r3, [r0]
	ldrb r2, [r0, r2]
	add r3, r3, r2
	add r3, #0x2c
	ldrb r4, [r3]
	mov r3, #6
	mul r3, r4
	add r1, r1, r3
	lsl r3, r1, #2
	mov r1, #0x90
	mul r1, r2
	add r0, r0, r1
	add r1, r0, r3
	ldrh r0, [r1, #0x3c]
	cmp r0, #0
	beq _02219DBE
	ldrh r1, [r1, #0x3e]
	cmp r1, #0
	bne _02219DC0
_02219DBE:
	mov r0, #0
_02219DC0:
	pop {r3, r4}
	bx lr
	.align 2, 0
_02219DC4: .word 0x0000114D

	thumb_func_start MOD09_02219DC8
MOD09_02219DC8: ; 0x02219DC8
	push {r4, lr}
	add r4, r0, #0
	bl MOD09_02219DF4
	add r0, r4, #0
	bl MOD09_02219E40
	add r0, r4, #0
	bl MOD09_02219FC4
	add r0, r4, #0
	bl MOD09_0221A158
	add r0, r4, #0
	bl MOD09_0221A244
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD09_02219DF4
MOD09_02219DF4: ; 0x02219DF4
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r3, _02219E3C ; =0x0221BDB0
	add r2, sp, #0
	add r5, r0, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r5]
	ldr r0, [r0]
	bl MOD11_02230078
	add r4, r0, #0
	bl FUN_0200BB34
	mov r1, #0xc3
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r1, [r5, r1]
	add r0, r4, #0
	mov r2, #0xc
	bl FUN_0200BBF0
	mov r1, #0xc3
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	add r0, r4, #0
	add r2, sp, #0
	bl FUN_0200BF60
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_02219E3C: .word MOD9_0221BDB0

	thumb_func_start MOD09_02219E40
MOD09_02219E40: ; 0x02219E40
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r6, r0, #0
	ldr r0, [r6]
	ldr r0, [r0]
	bl MOD11_02230078
	add r7, r0, #0
	mov r4, #0
_02219E52:
	ldr r0, _02219EE8 ; =0x0000B4B7
	add r5, r4, r0
	mov r0, #1
	add r1, r0, #0
	bl GetItemIndexMapping
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r1, #0xc3
	str r5, [sp, #8]
	lsl r1, r1, #2
	ldr r1, [r6, r1]
	add r0, r7, #0
	mov r2, #0x10
	bl FUN_0200C00C
	mov r0, #1
	mov r1, #2
	bl GetItemIndexMapping
	mov r1, #0x10
	str r1, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	mov r3, #0xc3
	str r5, [sp, #0x14]
	lsl r3, r3, #2
	ldr r0, [r6, #8]
	ldr r3, [r6, r3]
	mov r1, #3
	add r2, r7, #0
	bl FUN_0200C0DC
	add r4, r4, #1
	cmp r4, #6
	blo _02219E52
	bl FUN_0206E708
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _02219EE8 ; =0x0000B4B7
	mov r1, #0xc3
	str r0, [sp, #4]
	lsl r1, r1, #2
	ldr r1, [r6, r1]
	add r0, r7, #0
	mov r2, #0x10
	bl FUN_0200C124
	bl FUN_0206E70C
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _02219EE8 ; =0x0000B4B7
	mov r1, #0xc3
	str r0, [sp, #4]
	lsl r1, r1, #2
	ldr r1, [r6, r1]
	add r0, r7, #0
	mov r2, #0x10
	bl FUN_0200C13C
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02219EE8: .word 0x0000B4B7

	thumb_func_start MOD09_02219EEC
MOD09_02219EEC: ; 0x02219EEC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5]
	add r6, r1, #0
	ldr r0, [r0]
	add r4, r2, #0
	bl MOD11_02230078
	add r7, r0, #0
	add r0, r6, #0
	mov r1, #1
	bl GetItemIndexMapping
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r1, #0xc3
	str r4, [sp, #4]
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	add r0, r7, #0
	mov r2, #0x10
	bl FUN_0200C9D8
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD09_02219F24
MOD09_02219F24: ; 0x02219F24
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r0, r1, #0
	mov r1, #2
	add r4, r2, #0
	bl GetItemIndexMapping
	add r2, r0, #0
	mov r0, #3
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	lsl r0, r4, #0x14
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	ldr r3, [r5]
	ldr r0, [r5, #8]
	ldr r3, [r3, #0xc]
	mov r1, #0x10
	bl PaletteData_LoadNarc
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start MOD09_02219F54
MOD09_02219F54: ; 0x02219F54
	push {r4, r5, lr}
	sub sp, #0x34
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	ldr r0, [r0]
	bl MOD11_02230078
	mov r2, #0
	add r1, sp, #0
	strh r2, [r1]
	strh r2, [r1, #2]
	strh r2, [r1, #4]
	strh r2, [r1, #6]
	mov r1, #0x14
	ldr r3, _02219FB0 ; =0x0221BE98
	mul r1, r4
	ldr r3, [r3, r1]
	str r2, [sp, #0xc]
	str r3, [sp, #8]
	mov r3, #2
	str r3, [sp, #0x10]
	ldr r3, _02219FB4 ; =0x0221BE88
	str r2, [sp, #0x30]
	ldr r3, [r3, r1]
	add r2, sp, #0
	str r3, [sp, #0x14]
	ldr r3, _02219FB8 ; =0x0221BE8C
	ldr r3, [r3, r1]
	str r3, [sp, #0x18]
	ldr r3, _02219FBC ; =0x0221BE90
	ldr r3, [r3, r1]
	str r3, [sp, #0x1c]
	ldr r3, _02219FC0 ; =0x0221BE94
	ldr r1, [r3, r1]
	str r1, [sp, #0x20]
	mov r1, #1
	str r1, [sp, #0x2c]
	mov r1, #0xc3
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	bl FUN_0200C154
	add sp, #0x34
	pop {r4, r5, pc}
	nop
_02219FB0: .word MOD9_0221BE98
_02219FB4: .word MOD9_0221BE88
_02219FB8: .word MOD9_0221BE8C
_02219FBC: .word MOD9_0221BE90
_02219FC0: .word MOD9_0221BE94

	thumb_func_start MOD09_02219FC4
MOD09_02219FC4: ; 0x02219FC4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r7, #0x31
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #4
_02219FD0:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD09_02219F54
	str r0, [r5, r7]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blo _02219FD0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD09_02219FE4
MOD09_02219FE4: ; 0x02219FE4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r0, [r7]
	ldr r0, [r0]
	bl MOD11_02230078
	mov r6, #0x31
	str r0, [sp]
	mov r4, #0
	add r5, r7, #0
	lsl r6, r6, #4
_02219FFA:
	ldr r0, [r5, r6]
	bl FUN_0200C3DC
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blo _02219FFA
	add r0, r7, #0
	bl MOD09_0221A1B0
	add r0, r7, #0
	bl MOD09_0221A294
	mov r1, #0xc3
	lsl r1, r1, #2
	ldr r0, [sp]
	ldr r1, [r7, r1]
	bl FUN_0200C398
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD09_0221A024
MOD09_0221A024: ; 0x0221A024
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	mov r1, #1
	add r6, r0, #0
	bl FUN_0200C644
	lsl r1, r5, #0x10
	lsl r2, r4, #0x10
	add r0, r6, #0
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD09_0221A044
MOD09_0221A044: ; 0x0221A044
	push {r3, r4, r5, r6, r7, lr}
	mov r6, #0x31
	str r0, [sp]
	add r7, r1, #0
	mov r4, #0
	add r5, r0, #0
	lsl r6, r6, #4
_0221A052:
	ldr r0, [r5, r6]
	mov r1, #0
	bl FUN_0200C644
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blo _0221A052
	cmp r7, #0
	beq _0221A070
	cmp r7, #1
	beq _0221A078
	cmp r7, #2
	beq _0221A080
	pop {r3, r4, r5, r6, r7, pc}
_0221A070:
	ldr r0, [sp]
	bl MOD09_0221A088
	pop {r3, r4, r5, r6, r7, pc}
_0221A078:
	ldr r0, [sp]
	bl MOD09_0221A0BC
	pop {r3, r4, r5, r6, r7, pc}
_0221A080:
	ldr r0, [sp]
	bl MOD09_0221A114
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD09_0221A088
MOD09_0221A088: ; 0x0221A088
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	ldrh r1, [r1, #0x20]
	cmp r1, #0
	beq _0221A0B6
	ldr r2, _0221A0B8 ; =0x0000B4B7
	bl MOD09_02219EEC
	ldr r1, [r4]
	ldr r3, _0221A0B8 ; =0x0000B4B7
	ldrh r1, [r1, #0x20]
	add r0, r4, #0
	mov r2, #0
	bl MOD09_02219F24
	mov r0, #0x31
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0x18
	mov r2, #0xb2
	bl MOD09_0221A024
_0221A0B6:
	pop {r4, pc}
	.align 2, 0
_0221A0B8: .word 0x0000B4B7

	thumb_func_start MOD09_0221A0BC
MOD09_0221A0BC: ; 0x0221A0BC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r6, _0221A10C ; =0x0221BE10
	mov r4, #0
	add r7, r5, #0
_0221A0C6:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02219D94
	str r0, [sp]
	cmp r0, #0
	beq _0221A0FE
	ldr r2, _0221A110 ; =0x0000B4B7
	ldr r1, [sp]
	add r0, r5, #0
	add r2, r4, r2
	bl MOD09_02219EEC
	ldr r3, _0221A110 ; =0x0000B4B7
	lsl r2, r4, #0x10
	ldr r1, [sp]
	add r0, r5, #0
	lsr r2, r2, #0x10
	add r3, r4, r3
	bl MOD09_02219F24
	mov r0, #0x31
	lsl r0, r0, #4
	ldr r0, [r7, r0]
	ldr r1, [r6]
	ldr r2, [r6, #4]
	bl MOD09_0221A024
_0221A0FE:
	add r4, r4, #1
	add r6, #8
	add r7, r7, #4
	cmp r4, #6
	blo _0221A0C6
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221A10C: .word MOD9_0221BE10
_0221A110: .word 0x0000B4B7

	thumb_func_start MOD09_0221A114
MOD09_0221A114: ; 0x0221A114
	push {r3, r4, r5, lr}
	ldr r1, _0221A150 ; =0x0000114D
	add r4, r0, #0
	ldrb r1, [r4, r1]
	ldr r2, [r4]
	add r1, r2, r1
	add r1, #0x27
	ldrb r1, [r1]
	bl MOD09_02219D94
	add r5, r0, #0
	ldr r2, _0221A154 ; =0x0000B4B7
	add r0, r4, #0
	add r1, r5, #0
	bl MOD09_02219EEC
	ldr r3, _0221A154 ; =0x0000B4B7
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #0
	bl MOD09_02219F24
	mov r0, #0x31
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0x28
	mov r2, #0x2c
	bl MOD09_0221A024
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221A150: .word 0x0000114D
_0221A154: .word 0x0000B4B7

	thumb_func_start MOD09_0221A158
MOD09_0221A158: ; 0x0221A158
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5]
	ldr r0, [r0]
	bl MOD11_02230078
	ldr r3, _0221A1AC ; =0x0000B4BE
	add r4, r0, #0
	str r3, [sp]
	sub r1, r3, #5
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0xc3
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	ldr r2, [r5, #8]
	bl MOD11_0225D3EC
	ldr r3, _0221A1AC ; =0x0000B4BE
	mov r1, #0xc3
	str r3, [sp]
	sub r0, r3, #5
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r2, [r5]
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	ldr r2, [r2, #0xc]
	add r0, r4, #0
	bl MOD11_0225D484
	add r1, r0, #0
	ldr r0, [r5, #0x34]
	bl MOD09_0221AC30
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_0221A1AC: .word 0x0000B4BE

	thumb_func_start MOD09_0221A1B0
MOD09_0221A1B0: ; 0x0221A1B0
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #0x34]
	bl MOD09_0221AC24
	bl MOD11_0225D508
	ldr r3, _0221A1D8 ; =0x0000B4B9
	mov r0, #0xc3
	add r1, r3, #5
	str r3, [sp]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	bl MOD11_0225D45C
	add sp, #4
	pop {r3, r4, pc}
	nop
_0221A1D8: .word 0x0000B4B9

	thumb_func_start MOD09_0221A1DC
MOD09_0221A1DC: ; 0x0221A1DC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r1, _0221A21C ; =0x0221BD94
	lsl r2, r4, #2
	ldr r0, [r5, #0x34]
	ldr r1, [r1, r2]
	bl MOD09_0221AC68
	cmp r4, #0
	beq _0221A1FA
	cmp r4, #1
	beq _0221A206
	cmp r4, #2
	pop {r3, r4, r5, pc}
_0221A1FA:
	ldr r1, _0221A220 ; =0x0000114D
	ldr r0, [r5, #0x34]
	ldrb r1, [r5, r1]
	bl MOD09_0221AC34
	pop {r3, r4, r5, pc}
_0221A206:
	ldr r1, _0221A220 ; =0x0000114D
	ldr r2, [r5]
	ldrb r1, [r5, r1]
	ldr r0, [r5, #0x34]
	add r1, r2, r1
	add r1, #0x27
	ldrb r1, [r1]
	bl MOD09_0221AC34
	pop {r3, r4, r5, pc}
	nop
_0221A21C: .word MOD9_0221BD94
_0221A220: .word 0x0000114D

	thumb_func_start MOD09_0221A224
MOD09_0221A224: ; 0x0221A224
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl MOD09_0221AC2C
	ldr r0, [r4, #0x34]
	bl MOD09_0221AC5C
	ldr r0, [r4, #0x34]
	bl MOD09_0221AC24
	bl MOD11_0225D648
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD09_0221A244
MOD09_0221A244: ; 0x0221A244
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5]
	ldr r0, [r0]
	bl MOD11_02230078
	ldr r3, _0221A290 ; =0x0000B4BD
	add r4, r0, #0
	str r3, [sp]
	sub r1, r3, #5
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0xc3
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	ldr r2, [r5, #8]
	bl MOD11_0225D6A4
	ldr r3, _0221A290 ; =0x0000B4BD
	mov r1, #0xc3
	str r3, [sp]
	sub r0, r3, #5
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r2, [r5]
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	ldr r2, [r2, #0xc]
	add r0, r4, #0
	bl MOD11_0225D73C
	str r0, [r5, #0x38]
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_0221A290: .word 0x0000B4BD

	thumb_func_start MOD09_0221A294
MOD09_0221A294: ; 0x0221A294
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #0x38]
	bl MOD11_0225D7B8
	ldr r3, _0221A2B8 ; =0x0000B4B8
	mov r0, #0xc3
	add r1, r3, #5
	str r3, [sp]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, r1, #0
	bl MOD11_0225D714
	add sp, #4
	pop {r3, r4, pc}
	nop
_0221A2B8: .word 0x0000B4B8

	thumb_func_start MOD09_0221A2BC
MOD09_0221A2BC: ; 0x0221A2BC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	ldr r0, [r0, #0x14]
	cmp r0, #1
	bne _0221A2E2
	lsl r3, r1, #3
	ldr r1, _0221A2EC ; =0x0221BDC8
	ldr r2, _0221A2F0 ; =0x0221BDCC
	ldr r0, [r4, #0x38]
	ldr r1, [r1, r3]
	ldr r2, [r2, r3]
	bl MOD11_0225D800
	ldr r0, [r4, #0x38]
	mov r1, #0x3c
	bl MOD11_0225D820
	pop {r4, pc}
_0221A2E2:
	ldr r0, [r4, #0x38]
	bl MOD11_0225D80C
	pop {r4, pc}
	nop
_0221A2EC: .word MOD9_0221BDC8
_0221A2F0: .word MOD9_0221BDCC

	thumb_func_start MOD09_0221A2F4
MOD09_0221A2F4: ; 0x0221A2F4
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #9
	str r0, [sp, #4]
	mov r0, #0xca
	lsl r0, r0, #2
	mov r2, #0
	add r0, r5, r0
	add r3, r2, #0
	add r4, r1, #0
	bl MOD09_0221A62C
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _0221A5B0 ; =0x00000448
	mov r3, #9
	add r0, r5, r0
	add r1, r4, #0
	mov r2, #0
	str r3, [sp, #4]
	bl MOD09_0221A62C
	mov r0, #0x10
	str r0, [sp]
	mov r0, #9
	str r0, [sp, #4]
	ldr r0, _0221A5B4 ; =0x00000568
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x12
	bl MOD09_0221A62C
	mov r0, #0x1a
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	ldr r0, _0221A5B8 ; =0x00000688
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x1b
	bl MOD09_0221A62C
	mov r0, #0x1a
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	ldr r0, _0221A5BC ; =0x0000078C
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x20
	bl MOD09_0221A62C
	mov r0, #0x1a
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	mov r0, #0x89
	lsl r0, r0, #4
	add r0, r5, r0
	add r1, r4, #0
	mov r2, #0
	mov r3, #0x25
	bl MOD09_0221A62C
	mov r0, #0x1a
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	ldr r0, _0221A5C0 ; =0x00000994
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x25
	bl MOD09_0221A62C
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A5C4 ; =0x00000A98
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x39
	bl MOD09_0221A62C
	ldr r0, _0221A5C8 ; =0x00000ACA
	mov r2, #5
	str r2, [sp]
	add r0, r5, r0
	add r1, r4, #0
	mov r3, #0x39
	str r2, [sp, #4]
	bl MOD09_0221A62C
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A5CC ; =0x00000AFC
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0xa
	mov r3, #0x39
	bl MOD09_0221A62C
	mov r2, #0x10
	str r2, [sp]
	mov r0, #6
	str r0, [sp, #4]
	ldr r0, _0221A5D0 ; =0x00000B2E
	add r1, r4, #0
	add r0, r5, r0
	mov r3, #0
	bl MOD09_0221A62C
	ldr r0, _0221A5D4 ; =0x00000BEE
	mov r2, #0x10
	str r2, [sp]
	mov r3, #6
	add r0, r5, r0
	add r1, r4, #0
	str r3, [sp, #4]
	bl MOD09_0221A62C
	mov r2, #0x10
	str r2, [sp]
	mov r0, #6
	str r0, [sp, #4]
	ldr r0, _0221A5D8 ; =0x00000CAE
	add r1, r4, #0
	add r0, r5, r0
	mov r3, #0xc
	bl MOD09_0221A62C
	mov r2, #0x10
	str r2, [sp]
	mov r0, #6
	str r0, [sp, #4]
	ldr r0, _0221A5DC ; =0x00000D6E
	add r1, r4, #0
	add r0, r5, r0
	mov r3, #0x12
	bl MOD09_0221A62C
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A5E0 ; =0x00000E2E
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x2f
	bl MOD09_0221A62C
	mov r0, #0xe6
	mov r2, #5
	lsl r0, r0, #4
	str r2, [sp]
	add r0, r5, r0
	add r1, r4, #0
	mov r3, #0x2f
	str r2, [sp, #4]
	bl MOD09_0221A62C
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A5E4 ; =0x00000E92
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0xa
	mov r3, #0x2f
	bl MOD09_0221A62C
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A5E8 ; =0x00000EC4
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0xf
	mov r3, #0x2f
	bl MOD09_0221A62C
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A5EC ; =0x00000EF6
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0
	mov r3, #0x34
	bl MOD09_0221A62C
	ldr r0, _0221A5F0 ; =0x00000F28
	mov r2, #5
	str r2, [sp]
	add r0, r5, r0
	add r1, r4, #0
	mov r3, #0x34
	str r2, [sp, #4]
	bl MOD09_0221A62C
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A5F4 ; =0x00000F5A
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0xa
	mov r3, #0x34
	bl MOD09_0221A62C
	mov r0, #5
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A5F8 ; =0x00000F8C
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0xf
	mov r3, #0x34
	bl MOD09_0221A62C
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A5FC ; =0x00000FBE
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x14
	mov r3, #0x2f
	bl MOD09_0221A62C
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A600 ; =0x00000FDE
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x18
	mov r3, #0x2f
	bl MOD09_0221A62C
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A604 ; =0x00000FFE
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x1c
	mov r3, #0x2f
	bl MOD09_0221A62C
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A608 ; =0x0000101E
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x14
	mov r3, #0x33
	bl MOD09_0221A62C
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A60C ; =0x0000103E
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x18
	mov r3, #0x33
	bl MOD09_0221A62C
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A610 ; =0x0000105E
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x1c
	mov r3, #0x33
	bl MOD09_0221A62C
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A614 ; =0x0000107E
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x14
	mov r3, #0x37
	bl MOD09_0221A62C
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A618 ; =0x0000109E
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x18
	mov r3, #0x37
	bl MOD09_0221A62C
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A61C ; =0x000010BE
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x1c
	mov r3, #0x37
	bl MOD09_0221A62C
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A620 ; =0x000010DE
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x14
	mov r3, #0x3b
	bl MOD09_0221A62C
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A624 ; =0x000010FE
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x18
	mov r3, #0x3b
	bl MOD09_0221A62C
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0221A628 ; =0x0000111E
	add r1, r4, #0
	add r0, r5, r0
	mov r2, #0x1c
	mov r3, #0x3b
	bl MOD09_0221A62C
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221A5B0: .word 0x00000448
_0221A5B4: .word 0x00000568
_0221A5B8: .word 0x00000688
_0221A5BC: .word 0x0000078C
_0221A5C0: .word 0x00000994
_0221A5C4: .word 0x00000A98
_0221A5C8: .word 0x00000ACA
_0221A5CC: .word 0x00000AFC
_0221A5D0: .word 0x00000B2E
_0221A5D4: .word 0x00000BEE
_0221A5D8: .word 0x00000CAE
_0221A5DC: .word 0x00000D6E
_0221A5E0: .word 0x00000E2E
_0221A5E4: .word 0x00000E92
_0221A5E8: .word 0x00000EC4
_0221A5EC: .word 0x00000EF6
_0221A5F0: .word 0x00000F28
_0221A5F4: .word 0x00000F5A
_0221A5F8: .word 0x00000F8C
_0221A5FC: .word 0x00000FBE
_0221A600: .word 0x00000FDE
_0221A604: .word 0x00000FFE
_0221A608: .word 0x0000101E
_0221A60C: .word 0x0000103E
_0221A610: .word 0x0000105E
_0221A614: .word 0x0000107E
_0221A618: .word 0x0000109E
_0221A61C: .word 0x000010BE
_0221A620: .word 0x000010DE
_0221A624: .word 0x000010FE
_0221A628: .word 0x0000111E

	thumb_func_start MOD09_0221A62C
MOD09_0221A62C: ; 0x0221A62C
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	add r0, sp, #8
	mov lr, r3
	ldrb r3, [r0, #0x14]
	mov r6, #0
	mov ip, r3
	cmp r3, #0
	ble _0221A678
	ldrb r3, [r0, #0x10]
	lsl r2, r2, #1
	add r7, r1, r2
_0221A644:
	mov r2, #0
	cmp r3, #0
	ble _0221A66C
	mov r0, lr
	add r0, r0, r6
	lsl r0, r0, #6
	add r5, r7, r0
	add r0, r6, #0
	mul r0, r3
	lsl r1, r0, #1
	ldr r0, [sp]
	add r4, r0, r1
_0221A65C:
	lsl r1, r2, #1
	ldrh r0, [r5, r1]
	strh r0, [r4, r1]
	add r0, r2, #1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	cmp r2, r3
	blt _0221A65C
_0221A66C:
	add r0, r6, #1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	mov r0, ip
	cmp r6, r0
	blt _0221A644
_0221A678:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD09_0221A67C
MOD09_0221A67C: ; 0x0221A67C
	cmp r1, #0x10
	bhi _0221A70A
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0221A68C: ; jump table
	.short _0221A6AE - _0221A68C - 2 ; case 0
	.short _0221A6AE - _0221A68C - 2 ; case 1
	.short _0221A6AE - _0221A68C - 2 ; case 2
	.short _0221A6AE - _0221A68C - 2 ; case 3
	.short _0221A6BE - _0221A68C - 2 ; case 4
	.short _0221A6CC - _0221A68C - 2 ; case 5
	.short _0221A6D8 - _0221A68C - 2 ; case 6
	.short _0221A6D8 - _0221A68C - 2 ; case 7
	.short _0221A6D8 - _0221A68C - 2 ; case 8
	.short _0221A6D8 - _0221A68C - 2 ; case 9
	.short _0221A6D8 - _0221A68C - 2 ; case 10
	.short _0221A6D8 - _0221A68C - 2 ; case 11
	.short _0221A6E4 - _0221A68C - 2 ; case 12
	.short _0221A6F0 - _0221A68C - 2 ; case 13
	.short _0221A6CC - _0221A68C - 2 ; case 14
	.short _0221A6FC - _0221A68C - 2 ; case 15
	.short _0221A6CC - _0221A68C - 2 ; case 16
_0221A6AE:
	mov r1, #0xca
	lsl r1, r1, #2
	add r1, r0, r1
	mov r0, #0x12
	lsl r0, r0, #4
	mul r0, r2
	add r0, r1, r0
	bx lr
_0221A6BE:
	ldr r1, _0221A710 ; =0x00000688
	add r1, r0, r1
	lsl r0, r2, #6
	add r0, r2, r0
	lsl r0, r0, #2
	add r0, r1, r0
	bx lr
_0221A6CC:
	ldr r1, _0221A714 ; =0x00000A98
	add r1, r0, r1
	mov r0, #0x32
	mul r0, r2
	add r0, r1, r0
	bx lr
_0221A6D8:
	ldr r1, _0221A718 ; =0x00000B2E
	add r1, r0, r1
	mov r0, #0xc0
	mul r0, r2
	add r0, r1, r0
	bx lr
_0221A6E4:
	ldr r1, _0221A71C ; =0x00000E2E
	add r1, r0, r1
	mov r0, #0x32
	mul r0, r2
	add r0, r1, r0
	bx lr
_0221A6F0:
	ldr r1, _0221A720 ; =0x00000EF6
	add r1, r0, r1
	mov r0, #0x32
	mul r0, r2
	add r0, r1, r0
	bx lr
_0221A6FC:
	ldr r1, _0221A710 ; =0x00000688
	add r1, r0, r1
	lsl r0, r2, #6
	add r0, r2, r0
	lsl r0, r0, #2
	add r0, r1, r0
	bx lr
_0221A70A:
	mov r0, #0
	bx lr
	nop
_0221A710: .word 0x00000688
_0221A714: .word 0x00000A98
_0221A718: .word 0x00000B2E
_0221A71C: .word 0x00000E2E
_0221A720: .word 0x00000EF6

	thumb_func_start MOD09_0221A724
MOD09_0221A724: ; 0x0221A724
	cmp r2, #3
	bne _0221A72C
	mov r0, #5
	bx lr
_0221A72C:
	cmp r1, #0x10
	bhi _0221A78A
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0221A73C: ; jump table
	.short _0221A75E - _0221A73C - 2 ; case 0
	.short _0221A75E - _0221A73C - 2 ; case 1
	.short _0221A75E - _0221A73C - 2 ; case 2
	.short _0221A75E - _0221A73C - 2 ; case 3
	.short _0221A762 - _0221A73C - 2 ; case 4
	.short _0221A766 - _0221A73C - 2 ; case 5
	.short _0221A76A - _0221A73C - 2 ; case 6
	.short _0221A76A - _0221A73C - 2 ; case 7
	.short _0221A76A - _0221A73C - 2 ; case 8
	.short _0221A76A - _0221A73C - 2 ; case 9
	.short _0221A76A - _0221A73C - 2 ; case 10
	.short _0221A76A - _0221A73C - 2 ; case 11
	.short _0221A766 - _0221A73C - 2 ; case 12
	.short _0221A766 - _0221A73C - 2 ; case 13
	.short _0221A766 - _0221A73C - 2 ; case 14
	.short _0221A776 - _0221A73C - 2 ; case 15
	.short _0221A766 - _0221A73C - 2 ; case 16
_0221A75E:
	mov r0, #0
	bx lr
_0221A762:
	mov r0, #3
	bx lr
_0221A766:
	mov r0, #2
	bx lr
_0221A76A:
	ldr r1, _0221A790 ; =0x0000114D
	ldrb r0, [r0, r1]
	add r0, #8
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr
_0221A776:
	cmp r3, #2
	bne _0221A786
	ldr r1, _0221A790 ; =0x0000114D
	ldrb r0, [r0, r1]
	add r0, #8
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr
_0221A786:
	mov r0, #1
	bx lr
_0221A78A:
	mov r0, #0
	bx lr
	nop
_0221A790: .word 0x0000114D

	thumb_func_start MOD09_0221A794
MOD09_0221A794: ; 0x0221A794
	push {r4, r5, r6, r7}
	cmp r2, #0
	bne _0221A7A4
	ldr r2, _0221A7F8 ; =0x00000FBE
	add r2, r0, r2
	lsl r0, r3, #5
	add r0, r2, r0
	b _0221A7CC
_0221A7A4:
	cmp r2, #1
	bne _0221A7B2
	ldr r2, _0221A7FC ; =0x0000101E
	add r2, r0, r2
	lsl r0, r3, #5
	add r0, r2, r0
	b _0221A7CC
_0221A7B2:
	cmp r2, #2
	bne _0221A7C0
	ldr r2, _0221A800 ; =0x0000107E
	add r2, r0, r2
	lsl r0, r3, #5
	add r0, r2, r0
	b _0221A7CC
_0221A7C0:
	cmp r2, #3
	bne _0221A7F4
	ldr r2, _0221A804 ; =0x000010DE
	add r2, r0, r2
	lsl r0, r3, #5
	add r0, r2, r0
_0221A7CC:
	mov r2, #0
_0221A7CE:
	lsl r4, r2, #3
	lsl r5, r2, #5
	mov r3, #0
	add r4, r0, r4
	add r5, r1, r5
_0221A7D8:
	lsl r6, r3, #1
	ldrh r7, [r4, r6]
	add r3, r3, #1
	lsl r3, r3, #0x10
	add r6, r5, r6
	lsr r3, r3, #0x10
	strh r7, [r6, #0xc]
	cmp r3, #4
	blo _0221A7D8
	add r2, r2, #1
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	cmp r2, #4
	blo _0221A7CE
_0221A7F4:
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
_0221A7F8: .word 0x00000FBE
_0221A7FC: .word 0x0000101E
_0221A800: .word 0x0000107E
_0221A804: .word 0x000010DE

	thumb_func_start MOD09_0221A808
MOD09_0221A808: ; 0x0221A808
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r2, [sp, #4]
	str r3, [sp, #8]
	add r5, r1, #0
	ldr r1, [sp, #4]
	ldr r2, [sp, #8]
	str r0, [sp]
	bl MOD09_0221A67C
	add r3, sp, #0x10
	add r4, r0, #0
	ldrb r3, [r3, #0x10]
	ldr r0, [sp]
	ldr r1, [sp, #4]
	ldr r2, [sp, #8]
	bl MOD09_0221A724
	lsl r0, r0, #0x1c
	lsr r2, r0, #0x10
	ldr r0, [sp, #4]
	ldr r6, _0221A874 ; =0x0221BF4B
	lsl r3, r0, #2
	ldr r0, _0221A878 ; =0x0221BF4A
	ldrb r6, [r6, r3]
	ldrb r0, [r0, r3]
	mov r1, #0
	mul r6, r0
	cmp r6, #0
	ble _0221A864
	ldr r0, _0221A87C ; =0x0221BF48
	ldr r7, _0221A880 ; =0x00000FFF
	add r3, r0, r3
_0221A84A:
	lsl r0, r1, #1
	ldrh r6, [r4, r0]
	and r6, r7
	orr r6, r2
	strh r6, [r5, r0]
	add r0, r1, #1
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldrb r6, [r3, #2]
	ldrb r0, [r3, #3]
	mul r0, r6
	cmp r1, r0
	blt _0221A84A
_0221A864:
	ldr r0, [sp]
	ldr r2, [sp, #4]
	ldr r3, [sp, #8]
	add r1, r5, #0
	bl MOD09_0221A794
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0221A874: .word MOD9_0221BF4B
_0221A878: .word MOD9_0221BF4A
_0221A87C: .word MOD9_0221BF48
_0221A880: .word 0x00000FFF

	thumb_func_start MOD09_0221A884
MOD09_0221A884: ; 0x0221A884
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	str r1, [sp, #0xc]
	str r2, [sp, #0x10]
	str r3, [sp, #0x14]
	add r5, r0, #0
	ldr r0, [sp, #0xc]
	lsl r4, r0, #2
	ldr r0, _0221A8E8 ; =0x0221BF4B
	ldrb r7, [r0, r4]
	ldr r0, _0221A8EC ; =0x0221BF4A
	ldrb r6, [r0, r4]
	ldr r0, [r5]
	add r1, r6, #0
	mul r1, r7
	ldr r0, [r0, #0xc]
	lsl r1, r1, #1
	bl AllocFromHeap
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	str r0, [sp]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	add r0, r5, #0
	bl MOD09_0221A808
	ldr r0, _0221A8F0 ; =0x0221BF49
	ldr r3, _0221A8F4 ; =0x0221BF48
	ldrb r0, [r0, r4]
	ldrb r3, [r3, r4]
	ldr r2, [sp, #0x18]
	str r0, [sp]
	str r6, [sp, #4]
	str r7, [sp, #8]
	ldr r0, [r5, #4]
	mov r1, #6
	bl LoadRectToBgTilemapRect
	ldr r0, [r5, #4]
	mov r1, #6
	bl ScheduleBgTilemapBufferTransfer
	ldr r0, [sp, #0x18]
	bl FreeToHeap
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_0221A8E8: .word MOD9_0221BF4B
_0221A8EC: .word MOD9_0221BF4A
_0221A8F0: .word MOD9_0221BF49
_0221A8F4: .word MOD9_0221BF48

	thumb_func_start MOD09_0221A8F8
MOD09_0221A8F8: ; 0x0221A8F8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	cmp r1, #6
	blo _0221A916
	cmp r1, #0xb
	bhi _0221A916
	add r0, #0x31
	ldrb r0, [r0]
	cmp r0, #0
	bne _0221A916
	add r1, #0xb
	ldr r0, _0221A96C ; =0x0221BF8C
	lsl r1, r1, #2
	ldr r4, [r0, r1]
	b _0221A91C
_0221A916:
	ldr r0, _0221A96C ; =0x0221BF8C
	lsl r1, r1, #2
	ldr r4, [r0, r1]
_0221A91C:
	cmp r4, #0
	beq _0221A968
	cmp r2, #0
	beq _0221A92C
	cmp r2, #1
	beq _0221A934
	cmp r2, #2
	bne _0221A93A
_0221A92C:
	mov r0, #1
	str r0, [sp]
	mov r7, #2
	b _0221A93A
_0221A934:
	mov r0, #0
	str r0, [sp]
	mov r7, #4
_0221A93A:
	mov r5, #0
_0221A93C:
	ldrb r0, [r4, r5]
	cmp r0, #0xff
	beq _0221A968
	ldr r1, [r6, #0x2c]
	lsl r0, r0, #4
	add r0, r1, r0
	ldr r1, [sp]
	add r2, r7, #0
	mov r3, #0
	bl ScrollWindow
	ldrb r0, [r4, r5]
	ldr r1, [r6, #0x2c]
	lsl r0, r0, #4
	add r0, r1, r0
	bl ScheduleWindowCopyToVram
	add r0, r5, #1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #8
	blo _0221A93C
_0221A968:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221A96C: .word MOD9_0221BF8C

	thumb_func_start MOD09_0221A970
MOD09_0221A970: ; 0x0221A970
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	str r2, [sp]
	cmp r1, #6
	blo _0221A98C
	cmp r1, #0xb
	bhi _0221A98C
	sub r0, r1, #6
	lsl r0, r0, #2
	add r1, r5, r0
	mov r0, #0x31
	lsl r0, r0, #4
	ldr r6, [r1, r0]
	b _0221A9B0
_0221A98C:
	cmp r1, #4
	bne _0221A9D4
	mov r7, #0x31
	mov r4, #0
	lsl r7, r7, #4
_0221A996:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r6, [r0, r7]
	add r0, r6, #0
	bl FUN_0200C658
	cmp r0, #0
	bne _0221A9B0
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #6
	blo _0221A996
_0221A9B0:
	ldr r0, [sp]
	cmp r0, #0
	beq _0221A9BE
	cmp r0, #1
	beq _0221A9CA
	cmp r0, #2
	bne _0221A9D4
_0221A9BE:
	add r0, r6, #0
	mov r1, #0
	mov r2, #2
	bl FUN_0200C82C
	pop {r3, r4, r5, r6, r7, pc}
_0221A9CA:
	mov r1, #0
	add r0, r6, #0
	sub r2, r1, #4
	bl FUN_0200C82C
_0221A9D4:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD09_0221A9D8
MOD09_0221A9D8: ; 0x0221A9D8
	push {r4, r5}
	ldr r3, _0221AA10 ; =0x0000113E
	mov r5, #0
	strb r5, [r0, r3]
	add r4, r3, #1
	strb r5, [r0, r4]
	add r4, r3, #2
	strb r1, [r0, r4]
	add r1, r3, #3
	ldrb r4, [r0, r1]
	mov r1, #0xf0
	bic r4, r1
	lsl r1, r2, #0x1c
	lsr r1, r1, #0x18
	add r2, r4, #0
	orr r2, r1
	add r1, r3, #3
	strb r2, [r0, r1]
	ldrb r2, [r0, r1]
	mov r1, #0xf
	bic r2, r1
	mov r1, #1
	orr r2, r1
	add r1, r3, #3
	strb r2, [r0, r1]
	pop {r4, r5}
	bx lr
	nop
_0221AA10: .word 0x0000113E

	thumb_func_start MOD09_0221AA14
MOD09_0221AA14: ; 0x0221AA14
	push {r4, lr}
	ldr r3, _0221AAE8 ; =0x00001141
	add r4, r0, #0
	ldrb r1, [r4, r3]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	beq _0221AAE4
	sub r1, r3, #3
	ldrb r1, [r4, r1]
	cmp r1, #0
	beq _0221AA34
	cmp r1, #1
	beq _0221AA6C
	cmp r1, #2
	beq _0221AAA4
	pop {r4, pc}
_0221AA34:
	sub r1, r3, #1
	add r3, #0xb
	ldrb r1, [r4, r1]
	ldrb r3, [r4, r3]
	mov r2, #1
	bl MOD09_0221A884
	mov r1, #0x45
	lsl r1, r1, #6
	ldrb r1, [r4, r1]
	add r0, r4, #0
	mov r2, #1
	bl MOD09_0221A8F8
	mov r1, #0x45
	lsl r1, r1, #6
	ldrb r1, [r4, r1]
	add r0, r4, #0
	mov r2, #1
	bl MOD09_0221A970
	ldr r0, _0221AAEC ; =0x0000113F
	mov r1, #0
	strb r1, [r4, r0]
	mov r1, #1
	sub r0, r0, #1
	strb r1, [r4, r0]
	pop {r4, pc}
_0221AA6C:
	sub r1, r3, #1
	add r3, #0xb
	ldrb r1, [r4, r1]
	ldrb r3, [r4, r3]
	mov r2, #2
	bl MOD09_0221A884
	mov r1, #0x45
	lsl r1, r1, #6
	ldrb r1, [r4, r1]
	add r0, r4, #0
	mov r2, #2
	bl MOD09_0221A8F8
	mov r1, #0x45
	lsl r1, r1, #6
	ldrb r1, [r4, r1]
	add r0, r4, #0
	mov r2, #2
	bl MOD09_0221A970
	ldr r0, _0221AAEC ; =0x0000113F
	mov r1, #0
	strb r1, [r4, r0]
	mov r1, #2
	sub r0, r0, #1
	strb r1, [r4, r0]
	pop {r4, pc}
_0221AAA4:
	sub r1, r3, #1
	add r3, #0xb
	ldrb r1, [r4, r1]
	ldrb r3, [r4, r3]
	mov r2, #0
	bl MOD09_0221A884
	mov r1, #0x45
	lsl r1, r1, #6
	ldrb r1, [r4, r1]
	add r0, r4, #0
	mov r2, #0
	bl MOD09_0221A8F8
	mov r1, #0x45
	lsl r1, r1, #6
	ldrb r1, [r4, r1]
	add r0, r4, #0
	mov r2, #0
	bl MOD09_0221A970
	ldr r0, _0221AAEC ; =0x0000113F
	mov r2, #0
	strb r2, [r4, r0]
	sub r1, r0, #1
	strb r2, [r4, r1]
	add r1, r0, #2
	ldrb r2, [r4, r1]
	mov r1, #0xf
	add r0, r0, #2
	bic r2, r1
	strb r2, [r4, r0]
_0221AAE4:
	pop {r4, pc}
	nop
_0221AAE8: .word 0x00001141
_0221AAEC: .word 0x0000113F

	thumb_func_start MOD09_0221AAF0
MOD09_0221AAF0: ; 0x0221AAF0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	beq _0221AB02
	cmp r6, #1
	beq _0221AB60
	cmp r6, #2
	beq _0221ABE6
	pop {r3, r4, r5, r6, r7, pc}
_0221AB02:
	mov r1, #0
	add r2, r1, #0
	add r3, r6, #0
	bl MOD09_0221A884
	add r0, r5, #0
	mov r1, #1
	mov r2, #0
	add r3, r6, #0
	bl MOD09_0221A884
	add r0, r5, #0
	mov r1, #2
	mov r2, #0
	add r3, r6, #0
	bl MOD09_0221A884
	add r0, r5, #0
	mov r1, #3
	mov r2, #0
	add r3, r6, #0
	bl MOD09_0221A884
	ldr r0, [r5]
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	bne _0221AB46
	add r0, r5, #0
	mov r1, #4
	mov r2, #3
	add r3, r6, #0
	bl MOD09_0221A884
	b _0221AB52
_0221AB46:
	add r0, r5, #0
	mov r1, #4
	mov r2, #0
	add r3, r6, #0
	bl MOD09_0221A884
_0221AB52:
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	add r3, r6, #0
	bl MOD09_0221A884
	pop {r3, r4, r5, r6, r7, pc}
_0221AB60:
	mov r4, #0
	mov r7, #3
_0221AB64:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD09_02219D94
	cmp r0, #0
	bne _0221AB82
	add r1, r4, #6
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	add r2, r7, #0
	add r3, r6, #0
	bl MOD09_0221A884
	b _0221AB92
_0221AB82:
	add r1, r4, #6
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	mov r2, #0
	add r3, r6, #0
	bl MOD09_0221A884
_0221AB92:
	add r4, r4, #1
	cmp r4, #6
	blo _0221AB64
	ldr r0, _0221AC00 ; =0x0000114D
	ldrb r1, [r5, r0]
	add r0, r0, #7
	add r1, r5, r1
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _0221ABC0
	add r0, r5, #0
	mov r1, #0xc
	mov r2, #3
	add r3, r6, #0
	bl MOD09_0221A884
	add r0, r5, #0
	mov r1, #0xd
	mov r2, #3
	add r3, r6, #0
	bl MOD09_0221A884
	b _0221ABD8
_0221ABC0:
	add r0, r5, #0
	mov r1, #0xc
	mov r2, #0
	add r3, r6, #0
	bl MOD09_0221A884
	add r0, r5, #0
	mov r1, #0xd
	mov r2, #0
	add r3, r6, #0
	bl MOD09_0221A884
_0221ABD8:
	add r0, r5, #0
	mov r1, #0xe
	mov r2, #0
	add r3, r6, #0
	bl MOD09_0221A884
	pop {r3, r4, r5, r6, r7, pc}
_0221ABE6:
	mov r1, #0xf
	mov r2, #0
	add r3, r6, #0
	bl MOD09_0221A884
	add r0, r5, #0
	mov r1, #0x10
	mov r2, #0
	add r3, r6, #0
	bl MOD09_0221A884
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221AC00: .word 0x0000114D

	thumb_func_start MOD09_0221AC04
MOD09_0221AC04: ; 0x0221AC04
	push {r3, lr}
	mov r1, #0x10
	bl AllocFromHeap
	add r3, r0, #0
	mov r2, #0x10
	mov r1, #0
_0221AC12:
	strb r1, [r3]
	add r3, r3, #1
	sub r2, r2, #1
	bne _0221AC12
	pop {r3, pc}

	thumb_func_start MOD09_0221AC1C
MOD09_0221AC1C: ; 0x0221AC1C
	ldr r3, _0221AC20 ; =FreeToHeap
	bx r3
	.align 2, 0
_0221AC20: .word FreeToHeap

	thumb_func_start MOD09_0221AC24
MOD09_0221AC24: ; 0x0221AC24
	ldr r0, [r0]
	bx lr

	thumb_func_start MOD09_0221AC28
MOD09_0221AC28: ; 0x0221AC28
	ldrb r0, [r0, #8]
	bx lr

	thumb_func_start MOD09_0221AC2C
MOD09_0221AC2C: ; 0x0221AC2C
	strb r1, [r0, #8]
	bx lr

	thumb_func_start MOD09_0221AC30
MOD09_0221AC30: ; 0x0221AC30
	str r1, [r0]
	bx lr

	thumb_func_start MOD09_0221AC34
MOD09_0221AC34: ; 0x0221AC34
	push {r3, r4, lr}
	sub sp, #4
	strb r1, [r0, #9]
	ldrb r1, [r0, #8]
	cmp r1, #1
	bne _0221AC58
	ldrb r1, [r0, #9]
	ldr r2, [r0, #4]
	lsl r4, r1, #3
	add r3, r2, r4
	ldrb r1, [r3, #3]
	str r1, [sp]
	ldrb r1, [r2, r4]
	ldrb r2, [r3, #2]
	ldrb r3, [r3, #1]
	ldr r0, [r0]
	bl MOD11_0225D5DC
_0221AC58:
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start MOD09_0221AC5C
MOD09_0221AC5C: ; 0x0221AC5C
	mov r1, #0
	strb r1, [r0, #9]
	mov r1, #0xff
	strb r1, [r0, #0xa]
	bx lr
	.align 2, 0

	thumb_func_start MOD09_0221AC68
MOD09_0221AC68: ; 0x0221AC68
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r5, r1, #0
	bl MOD09_0221AC5C
	mov r0, #0
	str r5, [r4, #4]
	mvn r0, r0
	str r0, [r4, #0xc]
	ldrb r0, [r4, #8]
	cmp r0, #1
	bne _0221AC92
	ldr r3, [r4, #4]
	ldrb r0, [r3, #3]
	str r0, [sp]
	ldrb r1, [r3]
	ldrb r2, [r3, #2]
	ldrb r3, [r3, #1]
	ldr r0, [r4]
	bl MOD11_0225D5DC
_0221AC92:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD09_0221AC94
MOD09_0221AC94: ; 0x0221AC94
	str r1, [r0, #0xc]
	bx lr

	thumb_func_start MOD09_0221AC98
MOD09_0221AC98: ; 0x0221AC98
	push {r3, r4, lr}
	sub sp, #4
	ldrb r1, [r0, #8]
	cmp r1, #1
	bne _0221ACA8
	add sp, #4
	mov r0, #1
	pop {r3, r4, pc}
_0221ACA8:
	ldr r1, _0221ACDC ; =gMain
	ldr r2, [r1, #0x48]
	mov r1, #0xf3
	tst r1, r2
	beq _0221ACD4
	mov r1, #1
	strb r1, [r0, #8]
	ldrb r1, [r0, #9]
	ldr r2, [r0, #4]
	lsl r4, r1, #3
	add r3, r2, r4
	ldrb r1, [r3, #3]
	str r1, [sp]
	ldrb r1, [r2, r4]
	ldrb r2, [r3, #2]
	ldrb r3, [r3, #1]
	ldr r0, [r0]
	bl MOD11_0225D5DC
	ldr r0, _0221ACE0 ; =0x000005DC
	bl PlaySE
_0221ACD4:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	nop
_0221ACDC: .word gMain
_0221ACE0: .word 0x000005DC

	thumb_func_start MOD09_0221ACE4
MOD09_0221ACE4: ; 0x0221ACE4
	cmp r1, #3
	bhi _0221AD2C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0221ACF4: ; jump table
	.short _0221ACFC - _0221ACF4 - 2 ; case 0
	.short _0221AD08 - _0221ACF4 - 2 ; case 1
	.short _0221AD14 - _0221ACF4 - 2 ; case 2
	.short _0221AD20 - _0221ACF4 - 2 ; case 3
_0221ACFC:
	ldrb r1, [r0, #5]
	mov r0, #0x80
	tst r0, r1
	beq _0221AD2C
	mov r0, #1
	bx lr
_0221AD08:
	ldrb r1, [r0, #4]
	mov r0, #0x80
	tst r0, r1
	beq _0221AD2C
	mov r0, #1
	bx lr
_0221AD14:
	ldrb r1, [r0, #7]
	mov r0, #0x80
	tst r0, r1
	beq _0221AD2C
	mov r0, #1
	bx lr
_0221AD20:
	ldrb r1, [r0, #6]
	mov r0, #0x80
	tst r0, r1
	beq _0221AD2C
	mov r0, #1
	bx lr
_0221AD2C:
	mov r0, #0
	bx lr

	thumb_func_start MOD09_0221AD30
MOD09_0221AD30: ; 0x0221AD30
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	bl MOD09_0221AC98
	cmp r0, #0
	bne _0221AD46
	mov r0, #0
	add sp, #0x14
	mvn r0, r0
	pop {r4, r5, r6, r7, pc}
_0221AD46:
	ldr r0, _0221AEBC ; =gMain
	mov r1, #0x40
	ldr r0, [r0, #0x48]
	tst r1, r0
	beq _0221AD6A
	mov r1, #0
	str r1, [sp]
	ldrb r0, [r5, #9]
	add r2, r1, #0
	add r3, r1, #0
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldr r0, [r5, #4]
	bl FUN_0201C638
	add r4, r0, #0
	mov r6, #0
	b _0221ADD2
_0221AD6A:
	mov r1, #0x80
	tst r1, r0
	beq _0221AD8C
	mov r1, #0
	str r1, [sp]
	ldrb r0, [r5, #9]
	add r2, r1, #0
	add r3, r1, #0
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [r5, #4]
	bl FUN_0201C638
	add r4, r0, #0
	mov r6, #1
	b _0221ADD2
_0221AD8C:
	mov r1, #0x20
	tst r1, r0
	beq _0221ADAE
	mov r1, #0
	str r1, [sp]
	ldrb r0, [r5, #9]
	add r2, r1, #0
	add r3, r1, #0
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	ldr r0, [r5, #4]
	bl FUN_0201C638
	add r4, r0, #0
	mov r6, #2
	b _0221ADD2
_0221ADAE:
	mov r1, #0x10
	tst r0, r1
	beq _0221ADD0
	mov r1, #0
	str r1, [sp]
	ldrb r0, [r5, #9]
	add r2, r1, #0
	add r3, r1, #0
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, [r5, #4]
	bl FUN_0201C638
	add r4, r0, #0
	mov r6, #3
	b _0221ADD2
_0221ADD0:
	mov r4, #0xff
_0221ADD2:
	cmp r4, #0xff
	beq _0221AE92
	mov r0, #1
	str r0, [sp, #0xc]
	mov r0, #0x80
	add r1, r4, #0
	tst r1, r0
	beq _0221ADF2
	ldrb r1, [r5, #0xa]
	cmp r1, #0xff
	beq _0221ADEC
	add r4, r1, #0
	b _0221ADF2
_0221ADEC:
	eor r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_0221ADF2:
	mov r7, #0
_0221ADF4:
	mov r0, #1
	ldr r1, [r5, #0xc]
	lsl r0, r4
	tst r0, r1
	bne _0221AE2C
	str r7, [sp, #0xc]
	str r7, [sp]
	str r4, [sp, #4]
	str r6, [sp, #8]
	ldr r0, [r5, #4]
	add r1, r7, #0
	add r2, r7, #0
	add r3, r7, #0
	bl FUN_0201C638
	mov r1, #0x7f
	and r0, r1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	cmp r1, r4
	beq _0221AE24
	ldrb r0, [r5, #9]
	cmp r1, r0
	bne _0221AE28
_0221AE24:
	ldrb r4, [r5, #9]
	b _0221AE2C
_0221AE28:
	add r4, r1, #0
	b _0221ADF4
_0221AE2C:
	ldrb r0, [r5, #9]
	cmp r0, r4
	beq _0221AE8A
	ldr r0, [r5, #4]
	lsl r7, r4, #3
	add r1, sp, #0x10
	add r2, sp, #0x10
	add r0, r0, r7
	add r1, #3
	add r2, #2
	bl FUN_0201C620
	ldr r0, [r5, #4]
	add r1, sp, #0x10
	add r0, r0, r7
	add r1, #1
	add r2, sp, #0x10
	bl FUN_0201C62C
	ldr r0, [r5, #4]
	add r1, r6, #0
	add r0, r0, r7
	bl MOD09_0221ACE4
	cmp r0, #1
	bne _0221AE6C
	ldr r0, [sp, #0xc]
	cmp r0, #0
	beq _0221AE6C
	ldrb r0, [r5, #9]
	strb r0, [r5, #0xa]
	b _0221AE70
_0221AE6C:
	mov r0, #0xff
	strb r0, [r5, #0xa]
_0221AE70:
	strb r4, [r5, #9]
	add r3, sp, #0x10
	ldrb r0, [r3]
	str r0, [sp]
	ldrb r1, [r3, #3]
	ldrb r2, [r3, #1]
	ldrb r3, [r3, #2]
	ldr r0, [r5]
	bl MOD11_0225D5DC
	ldr r0, _0221AEC0 ; =0x000005DC
	bl PlaySE
_0221AE8A:
	mov r0, #0
	add sp, #0x14
	mvn r0, r0
	pop {r4, r5, r6, r7, pc}
_0221AE92:
	ldr r0, _0221AEBC ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _0221AEA2
	add sp, #0x14
	ldrb r0, [r5, #9]
	pop {r4, r5, r6, r7, pc}
_0221AEA2:
	mov r0, #2
	tst r1, r0
	beq _0221AEB6
	ldr r0, _0221AEC4 ; =0x000005DD
	bl PlaySE
	mov r0, #1
	add sp, #0x14
	mvn r0, r0
	pop {r4, r5, r6, r7, pc}
_0221AEB6:
	sub r0, r0, #3
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0221AEBC: .word gMain
_0221AEC0: .word 0x000005DC
_0221AEC4: .word 0x000005DD

	.rodata
	.global MOD9_0221AEC8
MOD9_0221AEC8: ; 0x0221AEC8
	.byte 0x00, 0x02, 0x04, 0x01, 0x03, 0x05, 0x00, 0x00

	.global MOD9_0221AED0
MOD9_0221AED0: ; 0x0221AED0
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD9_0221AEE0
MOD9_0221AEE0: ; 0x0221AEE0
	.byte 0x98, 0xBF, 0x00, 0xCF, 0x00, 0x27, 0xB8, 0xFF, 0x98, 0xBF, 0xD8, 0xFF, 0xFF, 0x00, 0x00, 0x00

	.global MOD9_0221AEF0
MOD9_0221AEF0: ; 0x0221AEF0
	.byte 0x08, 0x8F, 0x08, 0xF7, 0x98, 0xBF, 0x00, 0x67, 0x98, 0xBF, 0x68, 0xCF, 0x98, 0xBF, 0xD8, 0xFF
	.byte 0xFF, 0x00, 0x00, 0x00

	.global MOD9_0221AF04
MOD9_0221AF04: ; 0x0221AF04
	.byte 0x98, 0xBF, 0x00, 0x27, 0x98, 0xBF, 0x28, 0x4F, 0x98, 0xBF, 0x60, 0xC7, 0x98, 0xBF, 0xD8, 0xFF
	.byte 0xFF, 0x00, 0x00, 0x00

	.global MOD9_0221AF18
MOD9_0221AF18: ; 0x0221AF18
	.byte 0x98, 0xA7, 0x58, 0x7F, 0x98, 0xA7, 0x80, 0xA7, 0xA8, 0xB7, 0x58, 0x7F, 0xA8, 0xB7, 0x80, 0xA7
	.byte 0x98, 0xBF, 0xD8, 0xFF, 0xFF, 0x00, 0x00, 0x00

	.global MOD9_0221AF30
MOD9_0221AF30: ; 0x0221AF30
	.byte 0x30, 0x5F, 0x00, 0x7F, 0x30, 0x5F, 0x80, 0xFF, 0x60, 0x8F, 0x00, 0x7F, 0x60, 0x8F, 0x80, 0xFF
	.byte 0x98, 0xBF, 0xD8, 0xFF, 0xFF, 0x00, 0x00, 0x00

	.global MOD9_0221AF48
MOD9_0221AF48: ; 0x0221AF48
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x02, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD9_0221AF64
MOD9_0221AF64: ; 0x0221AF64
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD9_0221AF80
MOD9_0221AF80: ; 0x0221AF80
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x01, 0x02, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD9_0221AF9C
MOD9_0221AF9C: ; 0x0221AF9C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x02, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD9_0221AFB8
MOD9_0221AFB8: ; 0x0221AFB8
	.byte 0x00, 0x2F, 0x00, 0x7F, 0x08, 0x37, 0x80, 0xFF, 0x30, 0x5F, 0x00, 0x7F, 0x38, 0x67, 0x80, 0xFF
	.byte 0x60, 0x8F, 0x00, 0x7F, 0x68, 0x97, 0x80, 0xFF, 0x98, 0xBF, 0xD8, 0xFF, 0xFF, 0x00, 0x00, 0x00

	.global MOD9_0221AFD8
MOD9_0221AFD8: ; 0x0221AFD8
	.byte 0x30, 0x5F, 0x00, 0x7F, 0x30, 0x5F, 0x80, 0xFF, 0x60, 0x8F, 0x00, 0x7F, 0x60, 0x8F, 0x80, 0xFF
	.byte 0x90, 0xBF, 0x40, 0xBF, 0x00, 0x27, 0xB8, 0xFF, 0x98, 0xBF, 0xD8, 0xFF, 0xFF, 0x00, 0x00, 0x00

	.global MOD9_0221AFF8
MOD9_0221AFF8: ; 0x0221AFF8
	.byte 0x30, 0x5F, 0x00, 0x7F, 0x30, 0x5F, 0x80, 0xFF, 0x60, 0x8F, 0x00, 0x7F, 0x60, 0x8F, 0x80, 0xFF
	.byte 0x98, 0xBF, 0x00, 0x27, 0x98, 0xBF, 0x28, 0x4F, 0x98, 0xBF, 0x60, 0xC7, 0x98, 0xBF, 0xD8, 0xFF
	.byte 0xFF, 0x00, 0x00, 0x00

	.global MOD9_0221B01C
MOD9_0221B01C: ; 0x0221B01C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00
	.byte 0x0D, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD9_0221B06C
MOD9_0221B06C: ; 0x0221B06C
	.byte 0x04, 0x02, 0x15, 0x16, 0x02, 0x0F, 0x1F, 0x00, 0x04, 0x02, 0x13, 0x1B, 0x04, 0x0F, 0x1F, 0x00

	.global MOD9_0221B07C
MOD9_0221B07C: ; 0x0221B07C
	.byte 0x3D, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00
	.byte 0x49, 0x00, 0x00, 0x00

	.global MOD9_0221B090
MOD9_0221B090: ; 0x0221B090
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00

	.global MOD9_0221B0A8
MOD9_0221B0A8: ; 0x0221B0A8
	.byte 0x05, 0x0A, 0x04, 0x0C, 0x03, 0x09, 0x01, 0x00, 0x05, 0x0B, 0x0C, 0x0A, 0x03, 0x09, 0x25, 0x00
	.byte 0x05, 0x01, 0x14, 0x0B, 0x03, 0x09, 0x43, 0x00, 0x05, 0x0E, 0x14, 0x0B, 0x03, 0x09, 0x64, 0x00

	.global MOD9_0221B0C8
MOD9_0221B0C8: ; 0x0221B0C8
	.byte 0x04, 0x05, 0x01, 0x09, 0x02, 0x0D, 0x8B, 0x00, 0x04, 0x01, 0x06, 0x0E, 0x05, 0x09, 0x9D, 0x00
	.byte 0x04, 0x11, 0x06, 0x0E, 0x05, 0x09, 0xE3, 0x00, 0x04, 0x01, 0x0C, 0x0E, 0x05, 0x09, 0x29, 0x01
	.byte 0x04, 0x11, 0x0C, 0x0E, 0x05, 0x09, 0x6F, 0x01

	.global MOD9_0221B0F0
MOD9_0221B0F0: ; 0x0221B0F0
	.byte 0x04, 0x05, 0x01, 0x09, 0x02, 0x0D, 0x85, 0x00, 0x04, 0x01, 0x06, 0x0E, 0x05, 0x09, 0x97, 0x00
	.byte 0x04, 0x11, 0x06, 0x0E, 0x05, 0x09, 0xDD, 0x00, 0x04, 0x01, 0x0C, 0x0E, 0x05, 0x09, 0x23, 0x01
	.byte 0x04, 0x11, 0x0C, 0x0E, 0x05, 0x09, 0x69, 0x01, 0x04, 0x09, 0x12, 0x0E, 0x05, 0x09, 0xAF, 0x01

	.global MOD9_0221B120
MOD9_0221B120: ; 0x0221B120
	.byte 0x05, 0x00, 0x00, 0x0F, 0x05, 0x09, 0x85, 0x00, 0x05, 0x10, 0x01, 0x0F, 0x05, 0x09, 0xD0, 0x00
	.byte 0x05, 0x00, 0x06, 0x0F, 0x05, 0x09, 0x1B, 0x01, 0x05, 0x10, 0x07, 0x0F, 0x05, 0x09, 0x66, 0x01
	.byte 0x05, 0x00, 0x0C, 0x0F, 0x05, 0x09, 0xB1, 0x01, 0x05, 0x10, 0x0D, 0x0F, 0x05, 0x09, 0xFC, 0x01

	.global MOD9_0221B150
MOD9_0221B150: ; 0x0221B150
	.byte 0x05, 0x05, 0x01, 0x09, 0x02, 0x0D, 0x01, 0x00, 0x05, 0x04, 0x08, 0x0B, 0x02, 0x0D, 0x13, 0x00
	.byte 0x05, 0x14, 0x08, 0x02, 0x02, 0x0D, 0x29, 0x00, 0x05, 0x17, 0x08, 0x05, 0x02, 0x0D, 0x2D, 0x00
	.byte 0x05, 0x02, 0x0B, 0x0C, 0x02, 0x0D, 0x45, 0x01, 0x05, 0x10, 0x0B, 0x0F, 0x06, 0x0D, 0x5D, 0x01
	.byte 0x05, 0x07, 0x14, 0x0C, 0x03, 0x09, 0x37, 0x00

	.global MOD9_0221B188
MOD9_0221B188: ; 0x0221B188
	.byte 0x05, 0x05, 0x01, 0x09, 0x02, 0x0D, 0x25, 0x01, 0x05, 0x01, 0x06, 0x0E, 0x05, 0x09, 0x49, 0x01
	.byte 0x05, 0x11, 0x06, 0x0E, 0x05, 0x09, 0x8F, 0x01, 0x05, 0x01, 0x0C, 0x0E, 0x05, 0x09, 0xD5, 0x01
	.byte 0x05, 0x11, 0x0C, 0x0E, 0x05, 0x09, 0x1B, 0x02, 0x05, 0x0D, 0x14, 0x0B, 0x03, 0x09, 0x04, 0x01
	.byte 0x05, 0x05, 0x01, 0x09, 0x02, 0x0D, 0x37, 0x01, 0x05, 0x01, 0x06, 0x0E, 0x05, 0x09, 0x61, 0x02
	.byte 0x05, 0x11, 0x06, 0x0E, 0x05, 0x09, 0xA7, 0x02, 0x05, 0x01, 0x0C, 0x0E, 0x05, 0x09, 0xED, 0x02
	.byte 0x05, 0x11, 0x0C, 0x0E, 0x05, 0x09, 0x33, 0x03

	.global MOD9_0221B1E0
MOD9_0221B1E0: ; 0x0221B1E0
	.byte 0x05, 0x05, 0x01, 0x09, 0x02, 0x0D, 0x01, 0x00, 0x05, 0x04, 0x05, 0x0B, 0x02, 0x0D, 0x13, 0x00
	.byte 0x05, 0x14, 0x05, 0x02, 0x02, 0x0D, 0x29, 0x00, 0x05, 0x17, 0x05, 0x05, 0x02, 0x0D, 0x2D, 0x00
	.byte 0x05, 0x01, 0x10, 0x08, 0x02, 0x0D, 0x5B, 0x00, 0x05, 0x01, 0x0D, 0x08, 0x02, 0x0D, 0x6B, 0x00
	.byte 0x05, 0x0A, 0x10, 0x03, 0x02, 0x0D, 0x7B, 0x00, 0x05, 0x0A, 0x0D, 0x03, 0x02, 0x0D, 0x81, 0x00
	.byte 0x05, 0x10, 0x08, 0x0F, 0x0A, 0x0D, 0x87, 0x00, 0x05, 0x01, 0x08, 0x0C, 0x02, 0x0D, 0x1D, 0x01
	.byte 0x05, 0x06, 0x0A, 0x08, 0x02, 0x0D, 0x35, 0x01, 0x05, 0x07, 0x14, 0x0C, 0x03, 0x09, 0x37, 0x00

	.global MOD9_0221B240
MOD9_0221B240: ; 0x0221B240
	.byte 0x04, 0x04, 0x05, 0x0B, 0x02, 0x0D, 0x9D, 0x00, 0x04, 0x17, 0x05, 0x05, 0x02, 0x0D, 0xB7, 0x00
	.byte 0x04, 0x0A, 0x10, 0x03, 0x02, 0x0D, 0xE1, 0x00, 0x04, 0x0A, 0x0D, 0x03, 0x02, 0x0D, 0xE7, 0x00
	.byte 0x04, 0x10, 0x08, 0x0F, 0x0A, 0x0D, 0xED, 0x00, 0x04, 0x06, 0x0A, 0x08, 0x02, 0x0D, 0x9B, 0x01
	.byte 0x04, 0x05, 0x01, 0x09, 0x02, 0x0D, 0x8B, 0x00, 0x04, 0x14, 0x05, 0x02, 0x02, 0x0D, 0xB3, 0x00
	.byte 0x04, 0x01, 0x10, 0x08, 0x02, 0x0D, 0xC1, 0x00, 0x04, 0x01, 0x0D, 0x08, 0x02, 0x0D, 0xD1, 0x00
	.byte 0x04, 0x01, 0x08, 0x0C, 0x02, 0x0D, 0x83, 0x01, 0x04, 0x04, 0x05, 0x0B, 0x02, 0x0D, 0xAB, 0x01
	.byte 0x04, 0x17, 0x05, 0x05, 0x02, 0x0D, 0xC1, 0x01, 0x04, 0x0A, 0x10, 0x03, 0x02, 0x0D, 0xCB, 0x01
	.byte 0x04, 0x0A, 0x0D, 0x03, 0x02, 0x0D, 0xD1, 0x01, 0x04, 0x10, 0x08, 0x0F, 0x0A, 0x0D, 0xD7, 0x01
	.byte 0x04, 0x06, 0x0A, 0x08, 0x02, 0x0D, 0x6D, 0x02

	.global MOD9_0221B2C8
MOD9_0221B2C8: ; 0x0221B2C8
	.byte 0x05, 0x05, 0x01, 0x09, 0x02, 0x0D, 0x25, 0x01, 0x05, 0x01, 0x09, 0x0B, 0x02, 0x0D, 0x49, 0x01
	.byte 0x05, 0x01, 0x0B, 0x12, 0x04, 0x0D, 0x5F, 0x01, 0x05, 0x04, 0x10, 0x0C, 0x02, 0x0D, 0xA7, 0x01
	.byte 0x05, 0x18, 0x04, 0x07, 0x02, 0x0D, 0xBF, 0x01, 0x05, 0x1C, 0x07, 0x03, 0x02, 0x0D, 0xCD, 0x01
	.byte 0x05, 0x1C, 0x09, 0x03, 0x02, 0x0D, 0xD3, 0x01, 0x05, 0x1C, 0x0F, 0x03, 0x02, 0x0D, 0xD9, 0x01
	.byte 0x05, 0x1C, 0x0B, 0x03, 0x02, 0x0D, 0xDF, 0x01, 0x05, 0x1C, 0x0D, 0x03, 0x02, 0x0D, 0xE5, 0x01
	.byte 0x05, 0x19, 0x06, 0x06, 0x01, 0x09, 0xEB, 0x01, 0x05, 0x05, 0x04, 0x03, 0x02, 0x0D, 0xF1, 0x01
	.byte 0x05, 0x0D, 0x06, 0x06, 0x02, 0x0D, 0xF7, 0x01, 0x05, 0x15, 0x04, 0x02, 0x02, 0x0D, 0x85, 0x00
	.byte 0x05, 0x15, 0x07, 0x06, 0x02, 0x0D, 0x89, 0x00, 0x05, 0x15, 0x09, 0x06, 0x02, 0x0D, 0x95, 0x00
	.byte 0x05, 0x15, 0x0F, 0x06, 0x02, 0x0D, 0xA1, 0x00, 0x05, 0x15, 0x0B, 0x06, 0x02, 0x0D, 0xAD, 0x00
	.byte 0x05, 0x15, 0x0D, 0x06, 0x02, 0x0D, 0xB9, 0x00, 0x05, 0x01, 0x04, 0x04, 0x02, 0x0D, 0xC5, 0x00
	.byte 0x05, 0x01, 0x06, 0x0B, 0x02, 0x0D, 0xCD, 0x00, 0x05, 0x0D, 0x14, 0x0B, 0x03, 0x09, 0xE3, 0x00
	.byte 0x05, 0x05, 0x01, 0x09, 0x02, 0x0D, 0x37, 0x01, 0x05, 0x01, 0x09, 0x0B, 0x02, 0x0D, 0x61, 0x02
	.byte 0x05, 0x01, 0x0B, 0x12, 0x04, 0x0D, 0x77, 0x02, 0x05, 0x04, 0x10, 0x0C, 0x02, 0x0D, 0xBF, 0x02
	.byte 0x05, 0x18, 0x04, 0x07, 0x02, 0x0D, 0xD7, 0x02, 0x05, 0x1C, 0x07, 0x03, 0x02, 0x0D, 0xE5, 0x02
	.byte 0x05, 0x1C, 0x09, 0x03, 0x02, 0x0D, 0xEB, 0x02, 0x05, 0x1C, 0x0F, 0x03, 0x02, 0x0D, 0xF1, 0x02
	.byte 0x05, 0x1C, 0x0B, 0x03, 0x02, 0x0D, 0xF7, 0x02, 0x05, 0x1C, 0x0D, 0x03, 0x02, 0x0D, 0xFD, 0x02
	.byte 0x05, 0x19, 0x06, 0x06, 0x01, 0x09, 0x03, 0x03, 0x05, 0x05, 0x04, 0x03, 0x02, 0x0D, 0x09, 0x03
	.byte 0x05, 0x0D, 0x06, 0x06, 0x02, 0x0D, 0x0F, 0x03, 0x18, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0xC6, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x88, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0xC6, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0xC6, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x88, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x88, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00

	.global MOD9_0221B450
MOD9_0221B450: ; 0x0221B450
	.byte 0x82, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD9_0221B460
MOD9_0221B460: ; 0x0221B460
	.byte 0x82, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD9_0221B470
MOD9_0221B470: ; 0x0221B470
	.byte 0x82, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD9_0221B480
MOD9_0221B480: ; 0x0221B480
	.byte 0x82, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD9_0221B490
MOD9_0221B490: ; 0x0221B490
	.byte 0x82, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD9_0221B4A0
MOD9_0221B4A0: ; 0x0221B4A0
	.byte 0x08, 0xA0, 0xC8, 0xB8, 0x01, 0x00, 0x00, 0x02, 0xC0, 0x08, 0xF8, 0x18, 0x01, 0x82, 0x00, 0x01
	.byte 0xE0, 0xA0, 0xF8, 0xB8, 0x01, 0x02, 0x00, 0x02

	.global MOD9_0221B4B8
MOD9_0221B4B8: ; 0x0221B4B8
	.byte 0x12, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD9_0221B4D0
MOD9_0221B4D0: ; 0x0221B4D0
	.byte 0x08, 0xA0, 0x20, 0xB8, 0x00, 0x00, 0x00, 0x01
	.byte 0x30, 0xA0, 0x48, 0xB8, 0x01, 0x01, 0x00, 0x02, 0x68, 0xA0, 0xC0, 0xB8, 0x02, 0x02, 0x01, 0x03
	.byte 0xE0, 0xA0, 0xF8, 0xB8, 0x03, 0x03, 0x02, 0x03

	.global MOD9_0221B4F0
MOD9_0221B4F0: ; 0x0221B4F0
	.byte 0x18, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00

	.global MOD9_0221B510
MOD9_0221B510: ; 0x0221B510
	.byte 0x10, 0x10, 0xF0, 0x88, 0x00, 0x81, 0x00, 0x00, 0x08, 0xA0, 0x60, 0xB8, 0x00, 0x01, 0x01, 0x02
	.byte 0x70, 0xA0, 0xC8, 0xB8, 0x00, 0x02, 0x01, 0x03, 0xE0, 0xA0, 0xF8, 0xB8, 0x00, 0x03, 0x02, 0x03

	.global MOD9_0221B530
MOD9_0221B530: ; 0x0221B530
	.byte 0x5C, 0x9D, 0x7C, 0xA5, 0x00, 0x02, 0x00, 0x01, 0x84, 0x9D, 0xA4, 0xA5, 0x01, 0x03, 0x00, 0x04
	.byte 0x5C, 0xAD, 0x7C, 0xB5, 0x00, 0x02, 0x02, 0x03, 0x84, 0xAD, 0xA4, 0xB5, 0x01, 0x03, 0x02, 0x04
	.byte 0xE0, 0xA0, 0xF8, 0xB8, 0x04, 0x04, 0x83, 0x04

	.global MOD9_0221B558
MOD9_0221B558: ; 0x0221B558
	.word MOD9_0221B630, MOD9_0221B510, MOD9_0221B4D0, MOD9_0221B6A0
	.word MOD9_0221B530, MOD9_0221B580, MOD9_0221B668, MOD9_0221B4A0
	.word MOD9_0221B668, MOD9_0221B4A0

	.global MOD9_0221B580
MOD9_0221B580: ; 0x0221B580
	.byte 0x08, 0x38, 0x78, 0x58, 0x00, 0x02, 0x00, 0x01
	.byte 0x88, 0x38, 0xF8, 0x58, 0x01, 0x03, 0x00, 0x01, 0x08, 0x68, 0x78, 0x88, 0x00, 0x04, 0x02, 0x03
	.byte 0x88, 0x68, 0xF8, 0x88, 0x01, 0x04, 0x02, 0x03, 0xE0, 0xA0, 0xF8, 0xB8, 0x83, 0x04, 0x04, 0x04

	.global MOD9_0221B5A8
MOD9_0221B5A8: ; 0x0221B5A8
	.byte 0x18, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x58, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x00, 0x00

	.global MOD9_0221B5D0
MOD9_0221B5D0: ; 0x0221B5D0
	.byte 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00

	.global MOD9_0221B600
MOD9_0221B600: ; 0x0221B600
	.byte 0x1C, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x9C, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00
	.byte 0x1C, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x9C, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00
	.byte 0x1C, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x9C, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00

	.global MOD9_0221B630
MOD9_0221B630: ; 0x0221B630
	.byte 0x08, 0x08, 0x78, 0x28, 0x06, 0x02, 0x06, 0x01, 0x88, 0x10, 0xF8, 0x30, 0x04, 0x03, 0x00, 0x02
	.byte 0x08, 0x38, 0x78, 0x58, 0x00, 0x04, 0x01, 0x03, 0x88, 0x40, 0xF8, 0x60, 0x01, 0x05, 0x02, 0x04
	.byte 0x08, 0x68, 0x78, 0x88, 0x02, 0x01, 0x03, 0x05, 0x88, 0x70, 0xF8, 0x90, 0x03, 0x06, 0x04, 0x06
	.byte 0xE0, 0xA0, 0xF8, 0xB8, 0x05, 0x00, 0x05, 0x00

	.global MOD9_0221B668
MOD9_0221B668: ; 0x0221B668
	.byte 0x08, 0x38, 0x78, 0x58, 0x05, 0x02, 0x00, 0x01
	.byte 0x88, 0x38, 0xF8, 0x58, 0x05, 0x03, 0x00, 0x01, 0x08, 0x68, 0x78, 0x88, 0x00, 0x04, 0x02, 0x03
	.byte 0x88, 0x68, 0xF8, 0x88, 0x01, 0x06, 0x02, 0x03, 0x48, 0x98, 0xB8, 0xB8, 0x02, 0x04, 0x04, 0x06
	.byte 0xC0, 0x08, 0xF8, 0x18, 0x05, 0x81, 0x00, 0x05, 0xE0, 0xA0, 0xF8, 0xB8, 0x03, 0x06, 0x04, 0x06

	.global MOD9_0221B6A0
MOD9_0221B6A0: ; 0x0221B6A0
	.byte 0x08, 0x38, 0x78, 0x58, 0x00, 0x02, 0x00, 0x01, 0x88, 0x38, 0xF8, 0x58, 0x01, 0x03, 0x00, 0x01
	.byte 0x08, 0x68, 0x78, 0x88, 0x00, 0x84, 0x02, 0x03, 0x88, 0x68, 0xF8, 0x88, 0x01, 0x87, 0x02, 0x03
	.byte 0x08, 0xA0, 0x20, 0xB8, 0x02, 0x04, 0x04, 0x05, 0x30, 0xA0, 0x48, 0xB8, 0x02, 0x05, 0x04, 0x06
	.byte 0x68, 0xA0, 0xC0, 0xB8, 0x03, 0x06, 0x05, 0x07, 0xE0, 0xA0, 0xF8, 0xB8, 0x03, 0x07, 0x06, 0x07

	.global MOD9_0221B6E0
MOD9_0221B6E0: ; 0x0221B6E0
	.byte 0x16, 0xB0, 0x00, 0x00

	.global MOD9_0221B6E4
MOD9_0221B6E4: ; 0x0221B6E4
	.byte 0x0A, 0xB0, 0x00, 0x00

	.global MOD9_0221B6E8
MOD9_0221B6E8: ; 0x0221B6E8
	.byte 0x0A, 0xB0, 0x00, 0x00

	.global MOD9_0221B6EC
MOD9_0221B6EC: ; 0x0221B6EC
	.byte 0x0A, 0xB0, 0x00, 0x00

	.global MOD9_0221B6F0
MOD9_0221B6F0: ; 0x0221B6F0
	.byte 0x00, 0x00, 0x00, 0x00, 0x16, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00
	.byte 0x0A, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00
	.byte 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0xB0, 0x00, 0x00
	.byte 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x16, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x16, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00
	.byte 0x0A, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00
	.byte 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xB0, 0x00, 0x00
	.byte 0x07, 0xB0, 0x00, 0x00, 0x07, 0xB0, 0x00, 0x00, 0x07, 0xB0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x08, 0xB0, 0x00, 0x00, 0x07, 0xB0, 0x00, 0x00, 0x07, 0xB0, 0x00, 0x00, 0x07, 0xB0, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00, 0x07, 0xB0, 0x00, 0x00, 0x07, 0xB0, 0x00, 0x00
	.byte 0x07, 0xB0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x07, 0xB0, 0x00, 0x00
	.byte 0x07, 0xB0, 0x00, 0x00, 0x07, 0xB0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0B, 0xB0, 0x00, 0x00
	.byte 0x07, 0xB0, 0x00, 0x00, 0x07, 0xB0, 0x00, 0x00, 0x07, 0xB0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x0C, 0xB0, 0x00, 0x00, 0x07, 0xB0, 0x00, 0x00, 0x07, 0xB0, 0x00, 0x00, 0x07, 0xB0, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x0D, 0xB0, 0x00, 0x00, 0x08, 0xB0, 0x00, 0x00, 0x08, 0xB0, 0x00, 0x00
	.byte 0x08, 0xB0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0D, 0xB0, 0x00, 0x00, 0x08, 0xB0, 0x00, 0x00
	.byte 0x08, 0xB0, 0x00, 0x00, 0x08, 0xB0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0D, 0xB0, 0x00, 0x00
	.byte 0x08, 0xB0, 0x00, 0x00, 0x08, 0xB0, 0x00, 0x00, 0x08, 0xB0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x0D, 0xB0, 0x00, 0x00, 0x08, 0xB0, 0x00, 0x00, 0x08, 0xB0, 0x00, 0x00, 0x08, 0xB0, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x0D, 0xB0, 0x00, 0x00, 0x08, 0xB0, 0x00, 0x00, 0x08, 0xB0, 0x00, 0x00
	.byte 0x08, 0xB0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0D, 0xB0, 0x00, 0x00, 0x08, 0xB0, 0x00, 0x00
	.byte 0x08, 0xB0, 0x00, 0x00, 0x08, 0xB0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0E, 0xB0, 0x00, 0x00
	.byte 0x09, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x0F, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x10, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00
	.byte 0x09, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00
	.byte 0x09, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0xB0, 0x00, 0x00
	.byte 0x09, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x13, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x14, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00
	.byte 0x09, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00
	.byte 0x09, 0xB0, 0x00, 0x00, 0x09, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0xB0, 0x00, 0x00
	.byte 0x0B, 0xB0, 0x00, 0x00, 0x0B, 0xB0, 0x00, 0x00, 0x0B, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x17, 0xB0, 0x00, 0x00, 0x0B, 0xB0, 0x00, 0x00, 0x0B, 0xB0, 0x00, 0x00, 0x0B, 0xB0, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x17, 0xB0, 0x00, 0x00, 0x0B, 0xB0, 0x00, 0x00, 0x0B, 0xB0, 0x00, 0x00
	.byte 0x0B, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0xB0, 0x00, 0x00, 0x0B, 0xB0, 0x00, 0x00
	.byte 0x0B, 0xB0, 0x00, 0x00, 0x0B, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0xB0, 0x00, 0x00
	.byte 0x0B, 0xB0, 0x00, 0x00, 0x0B, 0xB0, 0x00, 0x00, 0x0B, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x16, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x16, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00
	.byte 0x0A, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00
	.byte 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0xB0, 0x00, 0x00
	.byte 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x16, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x16, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00
	.byte 0x0A, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00
	.byte 0x0A, 0xB0, 0x00, 0x00, 0x0A, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD9_0221B9EC
MOD9_0221B9EC: ; 0x0221B9EC
	.byte 0x02, 0xFF, 0x00, 0x00

	.global MOD9_0221B9F0
MOD9_0221B9F0: ; 0x0221B9F0
	.byte 0x03, 0xFF, 0x00, 0x00

	.global MOD9_0221B9F4
MOD9_0221B9F4: ; 0x0221B9F4
	.byte 0x04, 0xFF, 0x00, 0x00

	.global MOD9_0221B9F8
MOD9_0221B9F8: ; 0x0221B9F8
	.byte 0x01, 0xFF, 0x00, 0x00

	.global MOD9_0221B9FC
MOD9_0221B9FC: ; 0x0221B9FC
	.byte 0x01, 0xFF, 0x00, 0x00

	.global MOD9_0221BA00
MOD9_0221BA00: ; 0x0221BA00
	.byte 0x0B, 0xFF, 0x00, 0x00

	.global MOD9_0221BA04
MOD9_0221BA04: ; 0x0221BA04
	.byte 0x00, 0xFF, 0x00, 0x00

	.global MOD9_0221BA08
MOD9_0221BA08: ; 0x0221BA08
	.byte 0x03, 0xFF, 0x00, 0x00

	.global MOD9_0221BA0C
MOD9_0221BA0C: ; 0x0221BA0C
	.byte 0x05, 0xFF, 0x00, 0x00

	.global MOD9_0221BA10
MOD9_0221BA10: ; 0x0221BA10
	.byte 0x02, 0xFF, 0x00, 0x00

	.global MOD9_0221BA14
MOD9_0221BA14: ; 0x0221BA14
	.byte 0x06, 0xFF, 0x00, 0x00

	.global MOD9_0221BA18
MOD9_0221BA18: ; 0x0221BA18
	.byte 0x04, 0xFF, 0x00, 0x00

	.global MOD9_0221BA1C
MOD9_0221BA1C: ; 0x0221BA1C
	.byte 0x03, 0xFF, 0x00, 0x00

	.global MOD9_0221BA20
MOD9_0221BA20: ; 0x0221BA20
	.byte 0x02, 0xFF, 0x00, 0x00

	.global MOD9_0221BA24
MOD9_0221BA24: ; 0x0221BA24
	.byte 0x05, 0xFF, 0x00, 0x00

	.global MOD9_0221BA28
MOD9_0221BA28: ; 0x0221BA28
	.byte 0x01, 0xFF, 0x00, 0x00

	.global MOD9_0221BA2C
MOD9_0221BA2C: ; 0x0221BA2C
	.byte 0x04, 0xFF, 0x00, 0x00

	.global MOD9_0221BA30
MOD9_0221BA30: ; 0x0221BA30
	.byte 0x02, 0xFF, 0x00, 0x00

	.global MOD9_0221BA34
MOD9_0221BA34: ; 0x0221BA34
	.byte 0x03, 0xFF, 0x00, 0x00

	.global MOD9_0221BA38
MOD9_0221BA38: ; 0x0221BA38
	.byte 0x05, 0xFF, 0x00, 0x00

	.global MOD9_0221BA3C
MOD9_0221BA3C: ; 0x0221BA3C
	.byte 0x15, 0xFF, 0x00, 0x00

	.global MOD9_0221BA40
MOD9_0221BA40: ; 0x0221BA40
	.byte 0x00, 0x01, 0xFF, 0x00

	.global MOD9_0221BA44
MOD9_0221BA44: ; 0x0221BA44
	.byte 0x07, 0x01, 0xFF, 0x00

	.global MOD9_0221BA48
MOD9_0221BA48: ; 0x0221BA48
	.byte 0x02, 0x04, 0x02, 0x00

	.global MOD9_0221BA4C
MOD9_0221BA4C: ; 0x0221BA4C
	.byte 0x08, 0x02, 0xFF, 0x00

	.global MOD9_0221BA50
MOD9_0221BA50: ; 0x0221BA50
	.byte 0x09, 0x03, 0xFF, 0x00

	.global MOD9_0221BA54
MOD9_0221BA54: ; 0x0221BA54
	.byte 0x0A, 0x04, 0xFF, 0x00

	.global MOD9_0221BA58
MOD9_0221BA58: ; 0x0221BA58
	.byte 0x02, 0x03, 0x01, 0x00

	.global MOD9_0221BA5C
MOD9_0221BA5C: ; 0x0221BA5C
	.byte 0x02, 0x00, 0xFC, 0xFF, 0x02, 0x00

	.global MOD9_0221BA62
MOD9_0221BA62: ; 0x0221BA62
	.byte 0x02, 0x00, 0xFD, 0xFF, 0x01, 0x00

	.global MOD9_0221BA68
MOD9_0221BA68: ; 0x0221BA68
	.word MOD9_0221BA04, MOD9_0221B9FC, MOD9_0221BA30, MOD9_0221BA08
	.word MOD9_0221B9F4, MOD9_0221BA0C, 0x00000000, MOD9_0221BA40
	.word MOD9_0221B9EC, MOD9_0221BA38, MOD9_0221B9F0, MOD9_0221BA3C
	.word 0x00000000, 0x00000000, MOD9_0221BA44, MOD9_0221BA4C
	.word MOD9_0221BA50, MOD9_0221BA54, 0x00000000, MOD9_0221BA28
	.word MOD9_0221BA20, MOD9_0221BA1C, MOD9_0221BA18, MOD9_0221B9F8
	.word MOD9_0221BA10, MOD9_0221BA34, MOD9_0221BA2C, MOD9_0221BA24
	.word MOD9_0221BA00, MOD9_0221BA14, 0x00000000, 0x00000000
	.word 0x00000000, 0x00000000

	.global MOD9_0221BAF0
MOD9_0221BAF0: ; 0x0221BAF0
	.byte 0x00

	.global MOD9_0221BAF1
MOD9_0221BAF1: ; 0x0221BAF1
	.byte 0x00

	.global MOD9_0221BAF2
MOD9_0221BAF2: ; 0x0221BAF2
	.byte 0x10

	.global MOD9_0221BAF3
MOD9_0221BAF3: ; 0x0221BAF3
	.byte 0x06, 0x10, 0x01, 0x10, 0x06, 0x00, 0x06, 0x10, 0x06, 0x10, 0x07, 0x10, 0x06, 0x00, 0x0C, 0x10
	.byte 0x06, 0x10, 0x0D, 0x10, 0x06, 0x1B, 0x13, 0x05, 0x05, 0x01, 0x01, 0x1E, 0x11, 0x00, 0x13, 0x0D
	.byte 0x05, 0x0C, 0x13, 0x0D, 0x05, 0x0D, 0x13, 0x0D, 0x05, 0x0C, 0x13, 0x0D, 0x05, 0x00, 0x13, 0x05
	.byte 0x05, 0x05, 0x13, 0x05, 0x05, 0x00, 0x06, 0x10, 0x06, 0x10, 0x06, 0x10, 0x06, 0x00, 0x0C, 0x10
	.byte 0x06, 0x10, 0x0C, 0x10, 0x06, 0x17, 0x00, 0x09, 0x04, 0x00, 0x06, 0x10, 0x06, 0x10, 0x06, 0x10
	.byte 0x06, 0x00, 0x0C, 0x10, 0x06, 0x10, 0x0C, 0x10, 0x06, 0x00, 0x06, 0x10, 0x06, 0x10, 0x06, 0x10
	.byte 0x06, 0x00, 0x0C, 0x10, 0x06, 0x10, 0x0C, 0x10, 0x06, 0x08, 0x12, 0x10, 0x06, 0x00, 0x13, 0x1A
	.byte 0x05, 0x00, 0x13, 0x1A, 0x05, 0x0B, 0x13, 0x05, 0x02, 0x10, 0x13, 0x05, 0x02, 0x0B, 0x15, 0x05
	.byte 0x02, 0x10, 0x15, 0x05, 0x02

	.global MOD9_0221BB78
MOD9_0221BB78: ; 0x0221BB78
	.byte 0x98, 0xBF, 0x00, 0xCF, 0x98, 0xBF, 0xD8, 0xFF, 0xFF, 0x00, 0x00, 0x00

	.global MOD9_0221BB84
MOD9_0221BB84: ; 0x0221BB84
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD9_0221BB94
MOD9_0221BB94: ; 0x0221BB94
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD9_0221BBB0
MOD9_0221BBB0: ; 0x0221BBB0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD9_0221BBCC
MOD9_0221BBCC: ; 0x0221BBCC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x1A, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD9_0221BBE8
MOD9_0221BBE8: ; 0x0221BBE8
	.byte 0x08, 0x4F, 0x00, 0x7F, 0x50, 0x97, 0x00, 0x7F, 0x08, 0x4F, 0x80, 0xFF, 0x50, 0x97, 0x80, 0xFF
	.byte 0x98, 0xBF, 0x00, 0xCF, 0x98, 0xBF, 0xD8, 0xFF, 0xFF, 0x00, 0x00, 0x00

	.global MOD9_0221BC04
MOD9_0221BC04: ; 0x0221BC04
	.byte 0x08, 0x37, 0x00, 0x7F, 0x08, 0x37, 0x80, 0xFF, 0x38, 0x67, 0x00, 0x7F, 0x38, 0x67, 0x80, 0xFF
	.byte 0x68, 0x97, 0x00, 0x7F, 0x68, 0x97, 0x80, 0xFF, 0x98, 0xBF, 0x00, 0x27, 0x98, 0xBF, 0x28, 0x4F
	.byte 0x98, 0xBF, 0xD8, 0xFF, 0xFF, 0x00, 0x00, 0x00

	.global MOD9_0221BC2C
MOD9_0221BC2C: ; 0x0221BC2C
	.byte 0x04, 0x02, 0x13, 0x1B, 0x04, 0x0F, 0x76, 0x03

	.global MOD9_0221BC34
MOD9_0221BC34: ; 0x0221BC34
	.byte 0x05, 0x07, 0x04, 0x0C, 0x02, 0x04, 0xC7, 0x02, 0x05, 0x14, 0x04, 0x04, 0x02, 0x04, 0xDF, 0x02
	.byte 0x05, 0x02, 0x09, 0x1C, 0x06, 0x04, 0xE7, 0x02, 0x05, 0x0A, 0x14, 0x06, 0x03, 0x00, 0x8F, 0x03

	.global MOD9_0221BC54
MOD9_0221BC54: ; 0x0221BC54
	.byte 0x04, 0x02, 0x04, 0x0C, 0x05, 0x00, 0xCE, 0x02, 0x04, 0x02, 0x0D, 0x0C, 0x05, 0x00, 0x0A, 0x03
	.byte 0x04, 0x12, 0x05, 0x0C, 0x03, 0x00, 0x86, 0x02, 0x04, 0x12, 0x0E, 0x0C, 0x03, 0x00, 0xAA, 0x02
	.byte 0x04, 0x05, 0x14, 0x14, 0x03, 0x00, 0x4A, 0x02

	.global MOD9_0221BC7C
MOD9_0221BC7C: ; 0x0221BC7C
	.byte 0x09, 0x00, 0x00, 0x00

	.global MOD9_0221BC80
MOD9_0221BC80: ; 0x0221BC80
	.byte 0x0A, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00
	.byte 0x0E, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00
	.byte 0x12, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00

	.global MOD9_0221BCAC
MOD9_0221BCAC: ; 0x0221BCAC
	.byte 0x05, 0x01, 0x01, 0x0E, 0x03, 0x00, 0x01, 0x00, 0x05, 0x08, 0x04, 0x04, 0x03, 0x04, 0x2B, 0x00
	.byte 0x05, 0x11, 0x01, 0x0E, 0x03, 0x00, 0x37, 0x00, 0x05, 0x18, 0x04, 0x04, 0x03, 0x04, 0x61, 0x00
	.byte 0x05, 0x01, 0x07, 0x0E, 0x03, 0x00, 0x6D, 0x00, 0x05, 0x08, 0x0A, 0x04, 0x03, 0x04, 0x97, 0x00
	.byte 0x05, 0x11, 0x07, 0x0E, 0x03, 0x00, 0xA3, 0x00, 0x05, 0x18, 0x0A, 0x04, 0x03, 0x04, 0xCD, 0x00
	.byte 0x05, 0x01, 0x0D, 0x0E, 0x03, 0x00, 0xD9, 0x00, 0x05, 0x08, 0x10, 0x04, 0x03, 0x04, 0x03, 0x01
	.byte 0x05, 0x11, 0x0D, 0x0E, 0x03, 0x00, 0x0F, 0x01, 0x05, 0x18, 0x10, 0x04, 0x03, 0x04, 0x39, 0x01
	.byte 0x05, 0x01, 0x01, 0x0E, 0x03, 0x00, 0x45, 0x01, 0x05, 0x08, 0x04, 0x04, 0x03, 0x04, 0x6F, 0x01
	.byte 0x05, 0x11, 0x01, 0x0E, 0x03, 0x00, 0x7B, 0x01, 0x05, 0x18, 0x04, 0x04, 0x03, 0x04, 0xA5, 0x01
	.byte 0x05, 0x01, 0x07, 0x0E, 0x03, 0x00, 0xB1, 0x01, 0x05, 0x08, 0x0A, 0x04, 0x03, 0x04, 0xDB, 0x01
	.byte 0x05, 0x11, 0x07, 0x0E, 0x03, 0x00, 0xE7, 0x01, 0x05, 0x18, 0x0A, 0x04, 0x03, 0x04, 0x11, 0x02
	.byte 0x05, 0x01, 0x0D, 0x0E, 0x03, 0x00, 0x1D, 0x02, 0x05, 0x08, 0x10, 0x04, 0x03, 0x04, 0x47, 0x02
	.byte 0x05, 0x11, 0x0D, 0x0E, 0x03, 0x00, 0x53, 0x02, 0x05, 0x18, 0x10, 0x04, 0x03, 0x04, 0x7D, 0x02
	.byte 0x05, 0x0B, 0x13, 0x0A, 0x05, 0x04, 0x89, 0x02, 0x05, 0x16, 0x14, 0x04, 0x03, 0x04, 0xBB, 0x02

	.global MOD9_0221BD7C
MOD9_0221BD7C: ; 0x0221BD7C
	.byte 0x02, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0xB2, 0x00, 0x00, 0x00

	.global MOD9_0221BD94
MOD9_0221BD94: ; 0x0221BD94
	.word MOD9_0221BDE0, MOD9_0221BE40, MOD9_0221BDA0

	.global MOD9_0221BDA0
MOD9_0221BDA0: ; 0x0221BDA0
	.byte 0x08, 0xA0, 0xC8, 0xB8
	.byte 0x00, 0x00, 0x00, 0x01, 0xE0, 0xA0, 0xF8, 0xB8, 0x01, 0x01, 0x00, 0x01

	.global MOD9_0221BDB0
MOD9_0221BDB0: ; 0x0221BDB0
	.byte 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD9_0221BDC8
MOD9_0221BDC8: ; 0x0221BDC8
	.byte 0xC0, 0x00, 0x00, 0x00

	.global MOD9_0221BDCC
MOD9_0221BDCC: ; 0x0221BDCC
	.byte 0x18, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00
	.byte 0x98, 0x00, 0x00, 0x00

	.global MOD9_0221BDE0
MOD9_0221BDE0: ; 0x0221BDE0
	.byte 0x08, 0x10, 0x78, 0x48, 0x00, 0x01, 0x00, 0x02, 0x08, 0x58, 0x78, 0x90
	.byte 0x00, 0x04, 0x01, 0x03, 0x88, 0x10, 0xF8, 0x48, 0x02, 0x03, 0x00, 0x02, 0x88, 0x58, 0xF8, 0x90
	.byte 0x02, 0x05, 0x01, 0x03, 0x08, 0xA0, 0xC8, 0xB8, 0x01, 0x04, 0x04, 0x05, 0xE0, 0xA0, 0xF8, 0xB8
	.byte 0x83, 0x05, 0x04, 0x05

	.global MOD9_0221BE10
MOD9_0221BE10: ; 0x0221BE10
	.byte 0x2C, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00, 0xAC, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00
	.byte 0x2C, 0x00, 0x00, 0x00, 0x5D, 0x00, 0x00, 0x00, 0xAC, 0x00, 0x00, 0x00, 0x5D, 0x00, 0x00, 0x00
	.byte 0x2C, 0x00, 0x00, 0x00, 0x8D, 0x00, 0x00, 0x00, 0xAC, 0x00, 0x00, 0x00, 0x8D, 0x00, 0x00, 0x00

	.global MOD9_0221BE40
MOD9_0221BE40: ; 0x0221BE40
	.byte 0x08, 0x10, 0x78, 0x30, 0x00, 0x02, 0x00, 0x01, 0x88, 0x10, 0xF8, 0x30, 0x01, 0x03, 0x00, 0x01
	.byte 0x08, 0x40, 0x78, 0x60, 0x00, 0x04, 0x02, 0x03, 0x88, 0x40, 0xF8, 0x60, 0x01, 0x05, 0x02, 0x03
	.byte 0x08, 0x70, 0x78, 0x90, 0x02, 0x86, 0x04, 0x05, 0x88, 0x70, 0xF8, 0x90, 0x03, 0x08, 0x04, 0x05
	.byte 0x08, 0xA0, 0x20, 0xB8, 0x04, 0x06, 0x06, 0x07, 0x30, 0xA0, 0x48, 0xB8, 0x04, 0x07, 0x06, 0x08
	.byte 0xE0, 0xA0, 0xF8, 0xB8, 0x05, 0x08, 0x07, 0x08

	.global MOD9_0221BE88
MOD9_0221BE88: ; 0x0221BE88
	.byte 0xB7, 0xB4, 0x00, 0x00

	.global MOD9_0221BE8C
MOD9_0221BE8C: ; 0x0221BE8C
	.byte 0xB7, 0xB4, 0x00, 0x00

	.global MOD9_0221BE90
MOD9_0221BE90: ; 0x0221BE90
	.byte 0xB7, 0xB4, 0x00, 0x00

	.global MOD9_0221BE94
MOD9_0221BE94: ; 0x0221BE94
	.byte 0xB7, 0xB4, 0x00, 0x00

	.global MOD9_0221BE98
MOD9_0221BE98: ; 0x0221BE98
	.byte 0x01, 0x00, 0x00, 0x00, 0xB8, 0xB4, 0x00, 0x00, 0xB8, 0xB4, 0x00, 0x00, 0xB7, 0xB4, 0x00, 0x00
	.byte 0xB7, 0xB4, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xB9, 0xB4, 0x00, 0x00, 0xB9, 0xB4, 0x00, 0x00
	.byte 0xB7, 0xB4, 0x00, 0x00, 0xB7, 0xB4, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xBA, 0xB4, 0x00, 0x00
	.byte 0xBA, 0xB4, 0x00, 0x00, 0xB7, 0xB4, 0x00, 0x00, 0xB7, 0xB4, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0xBB, 0xB4, 0x00, 0x00, 0xBB, 0xB4, 0x00, 0x00, 0xB7, 0xB4, 0x00, 0x00, 0xB7, 0xB4, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xBC, 0xB4, 0x00, 0x00, 0xBC, 0xB4, 0x00, 0x00, 0xB7, 0xB4, 0x00, 0x00
	.byte 0xB7, 0xB4, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD9_0221BF00
MOD9_0221BF00: ; 0x0221BF00
	.byte 0x03, 0xFF, 0x00, 0x00

	.global MOD9_0221BF04
MOD9_0221BF04: ; 0x0221BF04
	.byte 0x03, 0xFF, 0x00, 0x00

	.global MOD9_0221BF08
MOD9_0221BF08: ; 0x0221BF08
	.byte 0x01, 0xFF, 0x00, 0x00

	.global MOD9_0221BF0C
MOD9_0221BF0C: ; 0x0221BF0C
	.byte 0x04, 0xFF, 0x00, 0x00

	.global MOD9_0221BF10
MOD9_0221BF10: ; 0x0221BF10
	.byte 0x02, 0xFF, 0x00, 0x00

	.global MOD9_0221BF14
MOD9_0221BF14: ; 0x0221BF14
	.byte 0x00, 0xFF, 0x00, 0x00

	.global MOD9_0221BF18
MOD9_0221BF18: ; 0x0221BF18
	.byte 0x0E, 0x0F, 0xFF, 0x00

	.global MOD9_0221BF1C
MOD9_0221BF1C: ; 0x0221BF1C
	.byte 0x10, 0x11, 0xFF, 0x00

	.global MOD9_0221BF20
MOD9_0221BF20: ; 0x0221BF20
	.byte 0x16, 0x17, 0xFF, 0x00

	.global MOD9_0221BF24
MOD9_0221BF24: ; 0x0221BF24
	.byte 0x06, 0x07, 0xFF, 0x00

	.global MOD9_0221BF28
MOD9_0221BF28: ; 0x0221BF28
	.byte 0x04, 0x05, 0xFF, 0x00

	.global MOD9_0221BF2C
MOD9_0221BF2C: ; 0x0221BF2C
	.byte 0x02, 0x03, 0xFF, 0x00

	.global MOD9_0221BF30
MOD9_0221BF30: ; 0x0221BF30
	.byte 0x00, 0x01, 0xFF, 0x00

	.global MOD9_0221BF34
MOD9_0221BF34: ; 0x0221BF34
	.byte 0x08, 0x09, 0xFF, 0x00

	.global MOD9_0221BF38
MOD9_0221BF38: ; 0x0221BF38
	.byte 0x12, 0x13, 0xFF, 0x00

	.global MOD9_0221BF3C
MOD9_0221BF3C: ; 0x0221BF3C
	.byte 0x0A, 0x0B, 0xFF, 0x00

	.global MOD9_0221BF40
MOD9_0221BF40: ; 0x0221BF40
	.byte 0x0C, 0x0D, 0xFF, 0x00

	.global MOD9_0221BF44
MOD9_0221BF44: ; 0x0221BF44
	.byte 0x14, 0x15, 0xFF, 0x00

	.global MOD9_0221BF48
MOD9_0221BF48: ; 0x0221BF48
	.byte 0x00

	.global MOD9_0221BF49
MOD9_0221BF49: ; 0x0221BF49
	.byte 0x01

	.global MOD9_0221BF4A
MOD9_0221BF4A: ; 0x0221BF4A
	.byte 0x10

	.global MOD9_0221BF4B
MOD9_0221BF4B: ; 0x0221BF4B
	.byte 0x09, 0x00, 0x0A, 0x10, 0x09, 0x10, 0x01, 0x10, 0x09, 0x10, 0x0A, 0x10, 0x09, 0x00, 0x13, 0x1A
	.byte 0x05, 0x1B, 0x13, 0x05, 0x05, 0x20, 0x01, 0x10, 0x06, 0x30, 0x01, 0x10, 0x06, 0x20, 0x07, 0x10
	.byte 0x06, 0x30, 0x07, 0x10, 0x06, 0x20, 0x0D, 0x10, 0x06, 0x30, 0x0D, 0x10, 0x06, 0x20, 0x13, 0x05
	.byte 0x05, 0x25, 0x13, 0x05, 0x05, 0x3B, 0x13, 0x05, 0x05, 0x00, 0x33, 0x1A, 0x05, 0x1B, 0x33, 0x05
	.byte 0x05

	.global MOD9_0221BF8C
MOD9_0221BF8C: ; 0x0221BF8C

	.word MOD9_0221BF14, MOD9_0221BF08, MOD9_0221BF10, MOD9_0221BF00
	.word MOD9_0221BF0C, 0x00000000, MOD9_0221BF30, MOD9_0221BF2C
	.word MOD9_0221BF28, MOD9_0221BF24, MOD9_0221BF34, MOD9_0221BF3C
	.word 0x00000000, 0x00000000, 0x00000000, MOD9_0221BF04
	.word 0x00000000, MOD9_0221BF40, MOD9_0221BF18, MOD9_0221BF1C
	.word MOD9_0221BF38, MOD9_0221BF44, MOD9_0221BF20

	.data
	.bss
