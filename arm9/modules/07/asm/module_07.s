	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD07_02211E60
MOD07_02211E60: ; 0x02211E60
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _02211E88 ; =MOD07_02211E94
	ldr r1, _02211E8C ; =0x00000B84
	ldr r3, [r5, #0x24]
	mov r2, #0x64
	bl FUN_020061E8
	bl FUN_0201B6C8
	ldr r2, _02211E8C ; =0x00000B84
	mov r1, #0
	add r4, r0, #0
	bl memset
	ldr r0, _02211E90 ; =0x00000B7F
	str r5, [r4]
	mov r1, #0
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
	.align 2, 0
_02211E88: .word MOD07_02211E94
_02211E8C: .word 0x00000B84
_02211E90: .word 0x00000B7F

	thumb_func_start MOD07_02211E94
MOD07_02211E94: ; 0x02211E94
	push {r4, r5, r6, lr}
	ldr r2, _02211F0C ; =0x00000B7F
	add r5, r1, #0
	ldrb r2, [r5, r2]
	cmp r2, #0
	beq _02211EAA
	cmp r2, #1
	beq _02211EB6
	cmp r2, #2
	beq _02211ED8
	b _02211EE0
_02211EAA:
	add r0, r5, #0
	bl MOD07_02211F34
	ldr r1, _02211F0C ; =0x00000B7F
	strb r0, [r5, r1]
	b _02211EE0
_02211EB6:
	mov r4, #0x2e
	lsl r4, r4, #6
	add r6, r4, #0
_02211EBC:
	ldrb r1, [r5, r6]
	ldr r2, [r5, #4]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	blx r1
	cmp r0, #0
	beq _02211ED2
	ldrb r1, [r5, r4]
	add r1, r1, #1
	strb r1, [r5, r4]
_02211ED2:
	cmp r0, #2
	beq _02211EBC
	b _02211EE0
_02211ED8:
	bl MOD07_02212B64
	cmp r0, #1
	beq _02211F0A
_02211EE0:
	mov r0, #0x2e
	lsl r0, r0, #6
	ldrb r0, [r5, r0]
	cmp r0, #0
	beq _02211EFA
	add r0, r5, #0
	bl MOD07_02212D30
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0200BC1C
_02211EFA:
	ldr r0, [r5]
	add r0, #0x28
	ldrb r0, [r0]
	cmp r0, #0
	beq _02211F0A
	ldr r0, _02211F10 ; =0x04000540
	mov r1, #1
	str r1, [r0]
_02211F0A:
	pop {r4, r5, r6, pc}
	.align 2, 0
_02211F0C: .word 0x00000B7F
_02211F10: .word 0x04000540

	thumb_func_start MOD07_02211F14
MOD07_02211F14: ; 0x02211F14
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _02211F30 ; =0x02214AD8
	add r3, sp, #0
	mov r2, #5
_02211F1E:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02211F1E
	add r0, sp, #0
	bl GX_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_02211F30: .word MOD7_02214AD8

	thumb_func_start MOD07_02211F34
MOD07_02211F34: ; 0x02211F34
	push {r4, lr}
	ldr r1, _02211FE0 ; =0x04000050
	add r4, r0, #0
	mov r0, #0
	strh r0, [r1]
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r2, [r0]
	ldr r1, _02211FE4 ; =0xFFFFE0FF
	ldr r3, _02211FE8 ; =0x04001000
	and r2, r1
	str r2, [r0]
	ldr r2, [r3]
	add r0, #0x50
	and r1, r2
	str r1, [r3]
	mov r1, #0
	strh r1, [r0]
	add r3, #0x50
	strh r1, [r3]
	bl MOD07_02211F14
	ldr r0, [r4]
	ldr r0, [r0, #0x24]
	bl FUN_02016B94
	str r0, [r4, #0xc]
	ldr r0, [r4]
	ldr r0, [r0, #0x24]
	bl FUN_02002FD0
	str r0, [r4, #8]
	ldr r3, [r4]
	mov r1, #0
	ldr r3, [r3, #0x24]
	mov r2, #0x60
	bl FUN_02003008
	ldr r0, _02211FEC ; =0x00000B82
	mov r3, #0
	strb r3, [r4, r0]
	sub r1, r0, #1
	mov r2, #8
	strb r2, [r4, r1]
	sub r0, r0, #2
	strb r3, [r4, r0]
	ldr r1, [r4]
	add r0, r1, #0
	add r0, #0x28
	ldrb r0, [r0]
	cmp r0, #0
	beq _02211FB8
	cmp r0, #1
	beq _02211FBE
	cmp r0, #2
	beq _02211FC4
	b _02211FDA
_02211FB8:
	ldr r0, _02211FF0 ; =0x022149A0
	str r0, [r4, #4]
	b _02211FDA
_02211FBE:
	ldr r0, _02211FF4 ; =0x022149B4
	str r0, [r4, #4]
	b _02211FDA
_02211FC4:
	add r1, #0x2a
	ldrb r0, [r1]
	cmp r0, #3
	bne _02211FD0
	ldr r0, _02211FF8 ; =0x02214B00
	b _02211FD2
_02211FD0:
	ldr r0, _02211FFC ; =0x02214B64
_02211FD2:
	str r0, [r4, #4]
	ldr r0, [r4]
	bl MOD07_02214720
_02211FDA:
	mov r0, #1
	pop {r4, pc}
	nop
_02211FE0: .word 0x04000050
_02211FE4: .word 0xFFFFE0FF
_02211FE8: .word 0x04001000
_02211FEC: .word 0x00000B82
_02211FF0: .word MOD7_022149A0
_02211FF4: .word MOD7_022149B4
_02211FF8: .word MOD7_02214B00
_02211FFC: .word MOD7_02214B64

	thumb_func_start MOD07_02212000
MOD07_02212000: ; 0x02212000
	push {r4, lr}
	ldr r1, _02212074 ; =0x00000B82
	add r4, r0, #0
	ldrb r2, [r4, r1]
	cmp r2, #0
	beq _02212016
	cmp r2, #1
	beq _02212022
	cmp r2, #2
	beq _0221202E
	b _02212068
_02212016:
	bl MOD07_02213858
	add r0, r4, #0
	bl MOD07_02213924
	b _02212068
_02212022:
	bl MOD07_02213D30
	add r0, r4, #0
	bl MOD07_02213F28
	b _02212068
_0221202E:
	mov r2, #0
	strb r2, [r4, r1]
	mov r2, #0x20
	sub r1, r1, #1
	strb r2, [r4, r1]
	bl MOD07_022139BC
	add r0, r4, #0
	bl MOD07_0221424C
	add r0, r4, #0
	bl MOD07_0221469C
	add r0, r4, #0
	bl MOD07_02213AEC
	bl FUN_02033E74
	ldr r1, [r4]
	mov r0, #0
	ldr r1, [r1, #0x24]
	bl FUN_02079A70
	ldr r0, _02212078 ; =MOD07_02212D68
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	mov r0, #1
	pop {r4, pc}
_02212068:
	ldr r0, _02212074 ; =0x00000B82
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_02212074: .word 0x00000B82
_02212078: .word MOD07_02212D68

	thumb_func_start MOD07_0221207C
MOD07_0221207C: ; 0x0221207C
	push {r4, lr}
	ldr r1, _022120F4 ; =0x00000B82
	add r4, r0, #0
	ldrb r1, [r4, r1]
	cmp r1, #0
	beq _02212092
	cmp r1, #1
	beq _022120A2
	cmp r1, #2
	beq _022120B8
	b _022120E6
_02212092:
	bl MOD07_02212D98
	add r0, r4, #0
	bl MOD07_02212E90
	bl MOD07_02212F2C
	b _022120E6
_022120A2:
	bl MOD07_022133B4
	add r0, r4, #0
	bl MOD07_02212F44
	bl FUN_02033E74
	add r0, r4, #0
	bl MOD07_022136B4
	b _022120E6
_022120B8:
	ldr r1, [r4]
	mov r0, #0
	ldr r1, [r1, #0x24]
	bl FUN_02079A70
	ldr r0, _022120F8 ; =MOD07_02212D68
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	ldr r1, _022120F4 ; =0x00000B82
	mov r0, #0
	strb r0, [r4, r1]
	mov r2, #8
	sub r0, r1, #6
	strb r2, [r4, r0]
	sub r0, r1, #5
	mov r2, #4
	strb r2, [r4, r0]
	mov r0, #0x10
	sub r1, #0xe
	str r0, [r4, r1]
	mov r0, #1
	pop {r4, pc}
_022120E6:
	ldr r0, _022120F4 ; =0x00000B82
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	mov r0, #0
	pop {r4, pc}
	nop
_022120F4: .word 0x00000B82
_022120F8: .word MOD07_02212D68

	thumb_func_start MOD07_022120FC
MOD07_022120FC: ; 0x022120FC
	push {r4, lr}
	ldr r1, _0221216C ; =0x00000B82
	add r4, r0, #0
	ldrb r1, [r4, r1]
	cmp r1, #0
	beq _02212112
	cmp r1, #1
	beq _02212122
	cmp r1, #2
	beq _02212132
	b _02212160
_02212112:
	bl MOD07_02212D98
	add r0, r4, #0
	bl MOD07_02212E90
	bl MOD07_02212F2C
	b _02212160
_02212122:
	bl MOD07_022133B4
	add r0, r4, #0
	bl MOD07_02213484
	bl FUN_02033E74
	b _02212160
_02212132:
	ldr r1, [r4]
	mov r0, #0
	ldr r1, [r1, #0x24]
	bl FUN_02079A70
	ldr r0, _02212170 ; =MOD07_02212D68
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	ldr r1, _0221216C ; =0x00000B82
	mov r0, #0
	strb r0, [r4, r1]
	mov r2, #4
	sub r0, r1, #6
	strb r2, [r4, r0]
	sub r0, r1, #5
	mov r2, #2
	strb r2, [r4, r0]
	mov r0, #0xc
	sub r1, #0xe
	str r0, [r4, r1]
	mov r0, #1
	pop {r4, pc}
_02212160:
	ldr r0, _0221216C ; =0x00000B82
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_0221216C: .word 0x00000B82
_02212170: .word MOD07_02212D68

	thumb_func_start MOD07_02212174
MOD07_02212174: ; 0x02212174
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0200E308
	cmp r0, #0
	bne _02212184
	mov r0, #0
	pop {r4, pc}
_02212184:
	ldr r1, _022121A8 ; =0x00000B81
	add r0, r1, #1
	ldrb r2, [r4, r1]
	ldrb r0, [r4, r0]
	cmp r2, r0
	bne _0221219A
	mov r2, #0
	add r0, r1, #1
	strb r2, [r4, r0]
	mov r0, #1
	pop {r4, pc}
_0221219A:
	add r0, r1, #1
	ldrb r0, [r4, r0]
	add r2, r0, #1
	add r0, r1, #1
	strb r2, [r4, r0]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_022121A8: .word 0x00000B81

	thumb_func_start MOD07_022121AC
MOD07_022121AC: ; 0x022121AC
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	mov r1, #3
	bl FUN_02017B48
	cmp r0, #0x18
	bgt _02212248
	ldr r1, _02212370 ; =0x00000B82
	mov r2, #0
	add r0, r1, #0
	strb r2, [r4, r1]
	sub r0, #0xa
	strh r2, [r4, r0]
	sub r1, #8
	strh r2, [r4, r1]
	ldr r0, [r4, #0xc]
	mov r1, #3
	mov r3, #0x18
	bl FUN_0201AEE4
	mov r2, #0
	add r3, r2, #0
	ldr r0, [r4, #0xc]
	mov r1, #2
	sub r3, #0x18
	bl FUN_0201AEE4
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	add r3, r1, #0
	bl MOD07_0221309C
	mov r2, #0
	add r0, r4, #0
	mov r1, #1
	add r3, r2, #0
	bl MOD07_0221309C
	mov r2, #0
	add r0, r4, #0
	mov r1, #2
	add r3, r2, #0
	bl MOD07_0221309C
	mov r2, #0
	add r0, r4, #0
	mov r1, #3
	add r3, r2, #0
	bl MOD07_0221309C
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	add r3, r1, #0
	bl MOD07_02213354
	mov r2, #0
	add r0, r4, #0
	mov r1, #1
	add r3, r2, #0
	bl MOD07_02213354
	mov r2, #0
	add r0, r4, #0
	mov r1, #2
	add r3, r2, #0
	bl MOD07_02213354
	mov r2, #0
	add r0, r4, #0
	mov r1, #3
	add r3, r2, #0
	bl MOD07_02213354
	mov r0, #1
	pop {r3, r4, r5, pc}
_02212248:
	ldr r3, _02212374 ; =0x00000B74
	ldr r0, [r4, #0xc]
	ldr r3, [r4, r3]
	mov r1, #3
	mov r2, #2
	bl FUN_0201AEE4
	ldr r3, _02212374 ; =0x00000B74
	ldr r0, [r4, #0xc]
	ldr r3, [r4, r3]
	mov r1, #2
	mov r2, #1
	bl FUN_0201AEE4
	ldr r3, _02212370 ; =0x00000B82
	mov r1, #0
	ldrb r0, [r4, r3]
	add r2, r3, #0
	sub r2, #0xe
	add r0, r0, #1
	strb r0, [r4, r3]
	ldr r5, [r4, r2]
	ldrb r2, [r4, r3]
	add r3, r5, #0
	add r0, r4, #0
	mul r3, r2
	mov r2, #1
	lsl r2, r2, #8
	sub r2, r3, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add r3, r1, #0
	bl MOD07_0221309C
	ldr r2, _02212374 ; =0x00000B74
	mov r1, #1
	ldr r3, [r4, r2]
	add r2, #0xe
	add r5, r3, #0
	ldrb r2, [r4, r2]
	add r0, r4, #0
	mov r3, #0
	mul r5, r2
	add r2, r1, #0
	add r2, #0xff
	sub r2, r5, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_0221309C
	ldr r2, _02212374 ; =0x00000B74
	mov r1, #2
	ldr r3, [r4, r2]
	add r2, #0xe
	add r5, r3, #0
	ldrb r2, [r4, r2]
	add r0, r4, #0
	mov r3, #0
	mul r5, r2
	add r2, r1, #0
	add r2, #0xfe
	sub r2, r2, r5
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_0221309C
	ldr r2, _02212374 ; =0x00000B74
	mov r1, #3
	ldr r3, [r4, r2]
	add r2, #0xe
	add r5, r3, #0
	ldrb r2, [r4, r2]
	add r0, r4, #0
	mov r3, #0
	mul r5, r2
	add r2, r1, #0
	add r2, #0xfd
	sub r2, r2, r5
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_0221309C
	ldr r2, _02212374 ; =0x00000B74
	mov r1, #0
	ldr r3, [r4, r2]
	add r2, #0xe
	add r5, r3, #0
	ldrb r2, [r4, r2]
	add r0, r4, #0
	add r3, r1, #0
	mul r5, r2
	mov r2, #1
	lsl r2, r2, #8
	sub r2, r5, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_02213354
	ldr r2, _02212374 ; =0x00000B74
	mov r1, #1
	ldr r3, [r4, r2]
	add r2, #0xe
	add r5, r3, #0
	ldrb r2, [r4, r2]
	add r0, r4, #0
	mov r3, #0
	mul r5, r2
	add r2, r1, #0
	add r2, #0xff
	sub r2, r5, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_02213354
	ldr r2, _02212374 ; =0x00000B74
	mov r1, #2
	ldr r3, [r4, r2]
	add r2, #0xe
	add r5, r3, #0
	ldrb r2, [r4, r2]
	add r0, r4, #0
	mov r3, #0
	mul r5, r2
	add r2, r1, #0
	add r2, #0xfe
	sub r2, r2, r5
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_02213354
	ldr r2, _02212374 ; =0x00000B74
	add r0, r4, #0
	ldr r3, [r4, r2]
	add r2, #0xe
	ldrb r2, [r4, r2]
	add r4, r3, #0
	mov r1, #3
	mul r4, r2
	add r2, r1, #0
	add r2, #0xfd
	sub r2, r2, r4
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	mov r3, #0
	bl MOD07_02213354
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02212370: .word 0x00000B82
_02212374: .word 0x00000B74

	thumb_func_start MOD07_02212378
MOD07_02212378: ; 0x02212378
	push {r4, r5, r6, lr}
	add r5, r0, #0
	bl MOD07_022137A4
	cmp r0, #0
	bne _02212394
	ldr r0, _02212574 ; =0x00000B82
	ldrb r1, [r5, r0]
	cmp r1, #0x18
	bls _02212394
	mov r1, #0
	strb r1, [r5, r0]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02212394:
	ldr r0, _02212574 ; =0x00000B82
	ldrb r0, [r5, r0]
	cmp r0, #0
	bne _022123B4
	ldr r0, [r5]
	add r0, #0x28
	ldrb r0, [r0]
	cmp r0, #1
	bne _022123AE
	ldr r0, _02212578 ; =0x00000715
	bl FUN_020054C8
	b _022123B4
_022123AE:
	ldr r0, _0221257C ; =0x00000852
	bl FUN_020054C8
_022123B4:
	ldr r0, _02212574 ; =0x00000B82
	ldrb r1, [r5, r0]
	cmp r1, #0x18
	bne _02212450
	ldr r0, [r5, #0xc]
	mov r1, #3
	mov r2, #0
	mov r3, #0x18
	bl FUN_0201AEE4
	mov r2, #0
	add r3, r2, #0
	ldr r0, [r5, #0xc]
	mov r1, #2
	sub r3, #0x18
	bl FUN_0201AEE4
	mov r1, #3
	ldr r0, [r5, #0xc]
	add r2, r1, #0
	mov r3, #0
	bl FUN_0201AEE4
	ldr r0, [r5, #0xc]
	mov r1, #2
	mov r2, #3
	mov r3, #0
	bl FUN_0201AEE4
	mov r1, #0
	add r0, r5, #0
	add r2, r1, #0
	add r3, r1, #0
	bl MOD07_0221309C
	mov r2, #0
	add r0, r5, #0
	mov r1, #1
	add r3, r2, #0
	bl MOD07_0221309C
	mov r2, #0
	add r0, r5, #0
	mov r1, #2
	add r3, r2, #0
	bl MOD07_0221309C
	mov r2, #0
	add r0, r5, #0
	mov r1, #3
	add r3, r2, #0
	bl MOD07_0221309C
	mov r1, #0
	add r0, r5, #0
	add r2, r1, #0
	add r3, r1, #0
	bl MOD07_02213354
	mov r2, #0
	add r0, r5, #0
	mov r1, #1
	add r3, r2, #0
	bl MOD07_02213354
	mov r2, #0
	add r0, r5, #0
	mov r1, #2
	add r3, r2, #0
	bl MOD07_02213354
	mov r2, #0
	add r0, r5, #0
	mov r1, #3
	add r3, r2, #0
	bl MOD07_02213354
	b _02212568
_02212450:
	blo _02212454
	b _02212568
_02212454:
	sub r0, r0, #6
	ldrsb r4, [r5, r0]
	bl LCRandom
	add r1, r4, #0
	bl _s32_div_f
	lsr r0, r4, #0x1f
	add r0, r4, r0
	asr r0, r0, #1
	sub r0, r1, r0
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	ldr r0, _02212580 ; =0x00000B7D
	ldrsb r4, [r5, r0]
	bl LCRandom
	add r1, r4, #0
	bl _s32_div_f
	lsr r0, r4, #0x1f
	add r0, r4, r0
	asr r0, r0, #1
	sub r0, r1, r0
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	cmp r6, #0
	bge _02212494
	ldr r0, _02212584 ; =0x00000B78
	ldrsh r0, [r5, r0]
	cmp r0, #0
	blt _022124A0
_02212494:
	cmp r6, #0
	ble _022124AA
	ldr r0, _02212584 ; =0x00000B78
	ldrsh r0, [r5, r0]
	cmp r0, #0
	ble _022124AA
_022124A0:
	mov r0, #0
	mvn r0, r0
	mul r0, r6
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
_022124AA:
	cmp r4, #0
	bge _022124B6
	ldr r0, _02212588 ; =0x00000B7A
	ldrsh r0, [r5, r0]
	cmp r0, #0
	blt _022124C2
_022124B6:
	cmp r4, #0
	ble _022124CC
	ldr r0, _02212588 ; =0x00000B7A
	ldrsh r0, [r5, r0]
	cmp r0, #0
	ble _022124CC
_022124C2:
	mov r0, #0
	mvn r0, r0
	mul r0, r4
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
_022124CC:
	add r3, r6, #0
	ldr r0, [r5, #0xc]
	mov r1, #3
	mov r2, #0
	add r3, #0x18
	bl FUN_0201AEE4
	add r3, r6, #0
	ldr r0, [r5, #0xc]
	mov r1, #2
	mov r2, #0
	sub r3, #0x18
	bl FUN_0201AEE4
	mov r1, #3
	ldr r0, [r5, #0xc]
	add r2, r1, #0
	add r3, r4, #0
	bl FUN_0201AEE4
	ldr r0, [r5, #0xc]
	mov r1, #2
	mov r2, #3
	add r3, r4, #0
	bl FUN_0201AEE4
	add r0, r5, #0
	mov r1, #0
	add r2, r6, #0
	add r3, r4, #0
	bl MOD07_0221309C
	add r0, r5, #0
	mov r1, #1
	add r2, r6, #0
	add r3, r4, #0
	bl MOD07_0221309C
	add r0, r5, #0
	mov r1, #2
	add r2, r6, #0
	add r3, r4, #0
	bl MOD07_0221309C
	add r0, r5, #0
	mov r1, #3
	add r2, r6, #0
	add r3, r4, #0
	bl MOD07_0221309C
	add r0, r5, #0
	mov r1, #0
	add r2, r6, #0
	add r3, r4, #0
	bl MOD07_02213354
	add r0, r5, #0
	mov r1, #1
	add r2, r6, #0
	add r3, r4, #0
	bl MOD07_02213354
	add r0, r5, #0
	mov r1, #2
	add r2, r6, #0
	add r3, r4, #0
	bl MOD07_02213354
	add r0, r5, #0
	mov r1, #3
	add r2, r6, #0
	add r3, r4, #0
	bl MOD07_02213354
	ldr r0, _02212584 ; =0x00000B78
	strh r6, [r5, r0]
	add r0, r0, #2
	strh r4, [r5, r0]
_02212568:
	ldr r0, _02212574 ; =0x00000B82
	ldrb r1, [r5, r0]
	add r1, r1, #1
	strb r1, [r5, r0]
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_02212574: .word 0x00000B82
_02212578: .word 0x00000715
_0221257C: .word 0x00000852
_02212580: .word 0x00000B7D
_02212584: .word 0x00000B78
_02212588: .word 0x00000B7A

	thumb_func_start MOD07_0221258C
MOD07_0221258C: ; 0x0221258C
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, _022126A4 ; =0x00000B82
	ldrb r0, [r4, r0]
	cmp r0, #8
	bne _022125B4
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	ldr r3, _022126A8 ; =0x00007FFF
	ldr r0, [r0, #0x24]
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	bl FUN_0200E1D0
_022125B4:
	ldr r0, _022126A4 ; =0x00000B82
	ldrb r0, [r4, r0]
	cmp r0, #8
	blo _022125D0
	bl FUN_0200E308
	cmp r0, #1
	bne _022125D0
	ldr r0, _022126AC ; =0x00000B7F
	mov r1, #2
	strb r1, [r4, r0]
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, pc}
_022125D0:
	ldr r0, _022126A4 ; =0x00000B82
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _022125DE
	ldr r0, _022126B0 ; =0x00000719
	bl FUN_020054C8
_022125DE:
	ldr r0, [r4, #0xc]
	mov r1, #3
	mov r2, #1
	mov r3, #0x10
	bl FUN_0201AEE4
	mov r1, #2
	ldr r0, [r4, #0xc]
	add r2, r1, #0
	mov r3, #0x10
	bl FUN_0201AEE4
	ldr r2, _022126A4 ; =0x00000B82
	mov r1, #0
	ldrb r0, [r4, r2]
	add r3, r1, #0
	add r0, r0, #1
	strb r0, [r4, r2]
	ldrb r2, [r4, r2]
	add r0, r4, #0
	lsl r2, r2, #4
	neg r2, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_0221309C
	ldr r2, _022126A4 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #1
	mov r3, #0
	lsl r2, r2, #4
	neg r2, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_0221309C
	ldr r2, _022126A4 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #2
	mov r3, #0
	lsl r2, r2, #0x14
	asr r2, r2, #0x10
	bl MOD07_0221309C
	ldr r2, _022126A4 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #3
	mov r3, #0
	lsl r2, r2, #0x14
	asr r2, r2, #0x10
	bl MOD07_0221309C
	ldr r2, _022126A4 ; =0x00000B82
	mov r1, #0
	ldrb r2, [r4, r2]
	add r0, r4, #0
	add r3, r1, #0
	lsl r2, r2, #4
	neg r2, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_02213354
	ldr r2, _022126A4 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #1
	mov r3, #0
	lsl r2, r2, #4
	neg r2, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_02213354
	ldr r2, _022126A4 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #2
	mov r3, #0
	lsl r2, r2, #0x14
	asr r2, r2, #0x10
	bl MOD07_02213354
	ldr r2, _022126A4 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #3
	mov r3, #0
	lsl r2, r2, #0x14
	asr r2, r2, #0x10
	bl MOD07_02213354
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_022126A4: .word 0x00000B82
_022126A8: .word 0x00007FFF
_022126AC: .word 0x00000B7F
_022126B0: .word 0x00000719

	thumb_func_start MOD07_022126B4
MOD07_022126B4: ; 0x022126B4
	ldr r1, _022126C0 ; =0x00000B81
	mov r2, #0x10
	strb r2, [r0, r1]
	mov r0, #2
	bx lr
	nop
_022126C0: .word 0x00000B81

	thumb_func_start MOD07_022126C4
MOD07_022126C4: ; 0x022126C4
	push {r4, lr}
	add r4, r0, #0
	bl MOD07_02212BD4
	cmp r0, #1
	ldr r0, [r4]
	bne _022126E8
	add r0, #0x2a
	ldrb r0, [r0]
	cmp r0, #1
	ldr r0, _02212700 ; =0x00000B7E
	bne _022126E2
	mov r1, #0
	strb r1, [r4, r0]
	b _022126FC
_022126E2:
	mov r1, #1
	strb r1, [r4, r0]
	b _022126FC
_022126E8:
	add r0, #0x2a
	ldrb r0, [r0]
	cmp r0, #1
	ldr r0, _02212700 ; =0x00000B7E
	bne _022126F8
	mov r1, #1
	strb r1, [r4, r0]
	b _022126FC
_022126F8:
	mov r1, #0
	strb r1, [r4, r0]
_022126FC:
	mov r0, #2
	pop {r4, pc}
	.align 2, 0
_02212700: .word 0x00000B7E

	thumb_func_start MOD07_02212704
MOD07_02212704: ; 0x02212704
	push {r3, lr}
	ldr r1, _0221271C ; =0x00000B7E
	ldrb r1, [r0, r1]
	cmp r1, #0
	bne _02212714
	bl MOD07_02212720
	pop {r3, pc}
_02212714:
	bl MOD07_02212824
	pop {r3, pc}
	nop
_0221271C: .word 0x00000B7E

	thumb_func_start MOD07_02212720
MOD07_02212720: ; 0x02212720
	push {r3, r4, r5, lr}
	ldr r3, _02212814 ; =0x00000B82
	add r4, r0, #0
	ldrb r3, [r4, r3]
	mov r1, #2
	ldr r0, [r4, #0xc]
	lsl r5, r3, #1
	ldr r3, _02212818 ; =0x02214960
	add r2, r1, #0
	ldrb r3, [r3, r5]
	bl FUN_0201AEE4
	ldr r3, _02212814 ; =0x00000B82
	ldr r0, [r4, #0xc]
	ldrb r3, [r4, r3]
	mov r1, #3
	mov r2, #2
	lsl r5, r3, #1
	ldr r3, _02212818 ; =0x02214960
	ldrb r3, [r3, r5]
	bl FUN_0201AEE4
	ldr r2, _02212814 ; =0x00000B82
	mov r1, #0
	ldrb r2, [r4, r2]
	add r0, r4, #0
	lsl r3, r2, #1
	ldr r2, _0221281C ; =0x02214961
	ldrb r2, [r2, r3]
	add r3, r1, #0
	bl MOD07_0221309C
	ldr r2, _02212814 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #1
	lsl r3, r2, #1
	ldr r2, _0221281C ; =0x02214961
	ldrb r2, [r2, r3]
	mov r3, #0
	bl MOD07_0221309C
	ldr r2, _02212814 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #2
	lsl r3, r2, #1
	ldr r2, _0221281C ; =0x02214961
	ldrb r2, [r2, r3]
	mov r3, #0
	bl MOD07_0221309C
	ldr r2, _02212814 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #3
	lsl r3, r2, #1
	ldr r2, _0221281C ; =0x02214961
	ldrb r2, [r2, r3]
	mov r3, #0
	bl MOD07_0221309C
	ldr r2, _02212814 ; =0x00000B82
	mov r1, #0
	ldrb r2, [r4, r2]
	add r0, r4, #0
	lsl r3, r2, #1
	ldr r2, _0221281C ; =0x02214961
	ldrb r2, [r2, r3]
	add r3, r1, #0
	bl MOD07_02213354
	ldr r2, _02212814 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #1
	lsl r3, r2, #1
	ldr r2, _0221281C ; =0x02214961
	ldrb r2, [r2, r3]
	mov r3, #0
	bl MOD07_02213354
	ldr r2, _02212814 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #2
	lsl r3, r2, #1
	ldr r2, _0221281C ; =0x02214961
	ldrb r2, [r2, r3]
	mov r3, #0
	bl MOD07_02213354
	ldr r2, _02212814 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #3
	lsl r3, r2, #1
	ldr r2, _0221281C ; =0x02214961
	ldrb r2, [r2, r3]
	mov r3, #0
	bl MOD07_02213354
	ldr r0, _02212814 ; =0x00000B82
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _022127FA
	ldr r0, _02212820 ; =0x00000853
	bl FUN_020054C8
_022127FA:
	ldr r0, _02212814 ; =0x00000B82
	ldrb r1, [r4, r0]
	cmp r1, #5
	bne _0221280A
	mov r1, #0
	strb r1, [r4, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_0221280A:
	add r1, r1, #1
	strb r1, [r4, r0]
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02212814: .word 0x00000B82
_02212818: .word MOD7_02214960
_0221281C: .word MOD7_02214961
_02212820: .word 0x00000853

	thumb_func_start MOD07_02212824
MOD07_02212824: ; 0x02212824
	push {r3, r4, r5, lr}
	ldr r3, _02212948 ; =0x00000B82
	add r4, r0, #0
	ldrb r3, [r4, r3]
	ldr r0, [r4, #0xc]
	mov r1, #2
	lsl r5, r3, #1
	ldr r3, _0221294C ; =0x02214960
	mov r2, #1
	ldrb r3, [r3, r5]
	bl FUN_0201AEE4
	ldr r3, _02212948 ; =0x00000B82
	ldr r0, [r4, #0xc]
	ldrb r3, [r4, r3]
	mov r1, #3
	mov r2, #1
	lsl r5, r3, #1
	ldr r3, _0221294C ; =0x02214960
	ldrb r3, [r3, r5]
	bl FUN_0201AEE4
	ldr r2, _02212948 ; =0x00000B82
	mov r1, #0
	ldrb r2, [r4, r2]
	add r0, r4, #0
	lsl r3, r2, #1
	ldr r2, _02212950 ; =0x02214961
	ldrb r2, [r2, r3]
	add r3, r1, #0
	neg r2, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_0221309C
	ldr r2, _02212948 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #1
	lsl r3, r2, #1
	ldr r2, _02212950 ; =0x02214961
	ldrb r2, [r2, r3]
	mov r3, #0
	neg r2, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_0221309C
	ldr r2, _02212948 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #2
	lsl r3, r2, #1
	ldr r2, _02212950 ; =0x02214961
	ldrb r2, [r2, r3]
	mov r3, #0
	neg r2, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_0221309C
	ldr r2, _02212948 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #3
	lsl r3, r2, #1
	ldr r2, _02212950 ; =0x02214961
	ldrb r2, [r2, r3]
	mov r3, #0
	neg r2, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_0221309C
	ldr r2, _02212948 ; =0x00000B82
	mov r1, #0
	ldrb r2, [r4, r2]
	add r0, r4, #0
	lsl r3, r2, #1
	ldr r2, _02212950 ; =0x02214961
	ldrb r2, [r2, r3]
	add r3, r1, #0
	neg r2, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_02213354
	ldr r2, _02212948 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #1
	lsl r3, r2, #1
	ldr r2, _02212950 ; =0x02214961
	ldrb r2, [r2, r3]
	mov r3, #0
	neg r2, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_02213354
	ldr r2, _02212948 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #2
	lsl r3, r2, #1
	ldr r2, _02212950 ; =0x02214961
	ldrb r2, [r2, r3]
	mov r3, #0
	neg r2, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_02213354
	ldr r2, _02212948 ; =0x00000B82
	add r0, r4, #0
	ldrb r2, [r4, r2]
	mov r1, #3
	lsl r3, r2, #1
	ldr r2, _02212950 ; =0x02214961
	ldrb r2, [r2, r3]
	mov r3, #0
	neg r2, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl MOD07_02213354
	ldr r0, _02212948 ; =0x00000B82
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _0221292E
	ldr r0, _02212954 ; =0x00000853
	bl FUN_020054C8
_0221292E:
	ldr r0, _02212948 ; =0x00000B82
	ldrb r1, [r4, r0]
	cmp r1, #5
	bne _0221293E
	mov r1, #0
	strb r1, [r4, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_0221293E:
	add r1, r1, #1
	strb r1, [r4, r0]
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02212948: .word 0x00000B82
_0221294C: .word MOD7_02214960
_02212950: .word MOD7_02214961
_02212954: .word 0x00000853

	thumb_func_start MOD07_02212958
MOD07_02212958: ; 0x02212958
	ldr r1, _02212964 ; =0x00000B81
	mov r2, #0x10
	strb r2, [r0, r1]
	mov r0, #2
	bx lr
	nop
_02212964: .word 0x00000B81

	thumb_func_start MOD07_02212968
MOD07_02212968: ; 0x02212968
	push {r4, r5, r6, lr}
	add r4, r0, #0
	ldr r0, _022129F0 ; =0x00000B82
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _022129AC
	mov r0, #2
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #1
	lsl r0, r0, #0x1a
	add r3, r0, #0
	ldr r2, [r0]
	ldr r1, _022129F4 ; =0xFFFF1FFF
	add r3, #0x48
	and r2, r1
	lsr r1, r0, #0xd
	orr r1, r2
	str r1, [r0]
	ldrh r5, [r3]
	mov r2, #0x3f
	mov r1, #0x1f
	bic r5, r2
	orr r5, r1
	mov r1, #0x20
	orr r1, r5
	strh r1, [r3]
	add r0, #0x4a
	ldrh r3, [r0]
	mov r1, #0x1d
	bic r3, r2
	orr r1, r3
	strh r1, [r0]
_022129AC:
	ldr r3, _022129F0 ; =0x00000B82
	ldrb r1, [r4, r3]
	cmp r1, #0x10
	bne _022129CC
	mov r0, #0
	mov r1, #0x20
	strb r0, [r4, r3]
	sub r0, r3, #1
	strb r1, [r4, r0]
	lsl r2, r1, #0x15
	ldr r1, [r2]
	ldr r0, _022129F4 ; =0xFFFF1FFF
	and r0, r1
	str r0, [r2]
	mov r0, #1
	pop {r4, r5, r6, pc}
_022129CC:
	mov r2, #0x5f
	sub r2, r2, r1
	add r1, #0x60
	lsl r1, r1, #0x18
	mov r6, #0xff
	ldr r0, _022129F8 ; =0x04000040
	lsl r5, r2, #8
	lsl r2, r6, #8
	and r2, r5
	lsr r1, r1, #0x18
	strh r6, [r0]
	orr r1, r2
	strh r1, [r0, #4]
	ldrb r0, [r4, r3]
	add r0, r0, #1
	strb r0, [r4, r3]
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_022129F0: .word 0x00000B82
_022129F4: .word 0xFFFF1FFF
_022129F8: .word 0x04000040

	thumb_func_start MOD07_022129FC
MOD07_022129FC: ; 0x022129FC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02212A34 ; =0x0000071A
	bl FUN_020054C8
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_0200C644
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_0200C644
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200C5C0
	ldr r0, _02212A38 ; =0x00000B81
	mov r1, #0x20
	strb r1, [r4, r0]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_02212A34: .word 0x0000071A
_02212A38: .word 0x00000B81

	thumb_func_start MOD07_02212A3C
MOD07_02212A3C: ; 0x02212A3C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02212A5C ; =0x0000071A
	bl FUN_020054C8
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_0200C644
	ldr r0, _02212A60 ; =0x00000B81
	mov r1, #0x40
	strb r1, [r4, r0]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_02212A5C: .word 0x0000071A
_02212A60: .word 0x00000B81

	thumb_func_start MOD07_02212A64
MOD07_02212A64: ; 0x02212A64
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD07_02212BD4
	cmp r0, #1
	ldr r0, [r4]
	bne _02212AA8
	add r0, #0x2a
	ldrb r0, [r0]
	cmp r0, #1
	bne _02212A92
	mov r3, #0
	str r3, [sp]
	mov r0, #4
	str r0, [sp, #4]
	str r3, [sp, #8]
	ldr r0, [r4, #8]
	mov r1, #1
	mov r2, #2
	bl FUN_02003210
	b _02212ADA
_02212A92:
	mov r3, #0
	str r3, [sp]
	mov r0, #4
	str r0, [sp, #4]
	str r3, [sp, #8]
	mov r1, #1
	ldr r0, [r4, #8]
	add r2, r1, #0
	bl FUN_02003210
	b _02212ADA
_02212AA8:
	add r0, #0x2a
	ldrb r0, [r0]
	cmp r0, #1
	bne _02212AC6
	mov r3, #0
	str r3, [sp]
	mov r0, #4
	str r0, [sp, #4]
	str r3, [sp, #8]
	mov r1, #1
	ldr r0, [r4, #8]
	add r2, r1, #0
	bl FUN_02003210
	b _02212ADA
_02212AC6:
	mov r3, #0
	str r3, [sp]
	mov r0, #4
	str r0, [sp, #4]
	str r3, [sp, #8]
	ldr r0, [r4, #8]
	mov r1, #1
	mov r2, #2
	bl FUN_02003210
_02212ADA:
	ldr r0, _02212AEC ; =0x0000071B
	bl FUN_020054C8
	ldr r0, _02212AF0 ; =0x00000B81
	mov r1, #0x40
	strb r1, [r4, r0]
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_02212AEC: .word 0x0000071B
_02212AF0: .word 0x00000B81

	thumb_func_start MOD07_02212AF4
MOD07_02212AF4: ; 0x02212AF4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02212B40 ; =0x00000B82
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _02212B06
	ldr r0, _02212B44 ; =0x00000719
	bl FUN_020054C8
_02212B06:
	ldr r1, _02212B40 ; =0x00000B82
	ldrb r0, [r4, r1]
	cmp r0, #0x10
	bne _02212B1C
	mov r0, #0
	strb r0, [r4, r1]
	mov r2, #0x40
	sub r0, r1, #1
	strb r2, [r4, r0]
	mov r0, #1
	pop {r4, pc}
_02212B1C:
	add r0, r0, #1
	strb r0, [r4, r1]
	ldrb r2, [r4, r1]
	mov r1, #0x10
	add r0, r4, #0
	sub r1, r1, r2
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	bl MOD07_022141CC
	ldr r1, _02212B40 ; =0x00000B82
	add r0, r4, #0
	ldrb r1, [r4, r1]
	bl MOD07_02213B20
	mov r0, #0
	pop {r4, pc}
	nop
_02212B40: .word 0x00000B82
_02212B44: .word 0x00000719

	thumb_func_start MOD07_02212B48
MOD07_02212B48: ; 0x02212B48
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	mov r0, #1
	ldr r1, [r1, #0x24]
	bl FUN_02079A70
	ldr r0, _02212B60 ; =0x00000B7F
	mov r1, #2
	strb r1, [r4, r0]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_02212B60: .word 0x00000B7F

	thumb_func_start MOD07_02212B64
MOD07_02212B64: ; 0x02212B64
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200E308
	cmp r0, #0
	bne _02212B76
	mov r0, #0
	pop {r3, r4, r5, pc}
_02212B76:
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	ldr r0, [r4]
	add r0, #0x28
	ldrb r0, [r0]
	cmp r0, #0
	beq _02212B9C
	add r0, r4, #0
	bl MOD07_02212E64
	add r0, r4, #0
	bl MOD07_022137DC
	add r0, r4, #0
	bl MOD07_02213380
	b _02212BA8
_02212B9C:
	add r0, r4, #0
	bl MOD07_022138F8
	add r0, r4, #0
	bl MOD07_02214274
_02212BA8:
	add r0, r4, #0
	bl MOD07_02212CEC
	bl FUN_0201C29C
	ldr r0, [r4, #8]
	mov r1, #0
	bl FUN_02003038
	ldr r0, [r4, #8]
	bl FUN_02002FEC
	ldr r0, [r4]
	mov r1, #1
	add r0, #0x2b
	strb r1, [r0]
	add r0, r5, #0
	bl FUN_0200621C
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD07_02212BD4
MOD07_02212BD4: ; 0x02212BD4
	push {r3, lr}
	bl FUN_02031190
	bl FUN_020313CC
	cmp r0, #3
	bhi _02212BFE
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02212BEE: ; jump table
	.short _02212BF6 - _02212BEE - 2 ; case 0
	.short _02212BFA - _02212BEE - 2 ; case 1
	.short _02212BF6 - _02212BEE - 2 ; case 2
	.short _02212BFA - _02212BEE - 2 ; case 3
_02212BF6:
	mov r0, #1
	pop {r3, pc}
_02212BFA:
	mov r0, #0
	pop {r3, pc}
_02212BFE:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD07_02212C04
MOD07_02212C04: ; 0x02212C04
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r5, r0, #0
	str r1, [sp]
	ldr r1, [r5]
	mov r0, #0x40
	ldr r1, [r1, #0x24]
	add r4, r2, #0
	bl FUN_0201C24C
	ldr r0, [r5]
	ldr r0, [r0, #0x24]
	bl FUN_0200BB14
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	bl FUN_0200BB34
	mov r1, #0x65
	lsl r1, r1, #2
	add r2, sp, #0x18
	ldr r3, _02212C9C ; =0x02214AB8
	str r0, [r5, r1]
	ldmia r3!, {r0, r1}
	add r6, r2, #0
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r3, _02212CA0 ; =0x0221498C
	add r2, sp, #4
	ldmia r3!, {r0, r1}
	add r7, r2, #0
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r6, #0
	str r0, [r2]
	mov r0, #0x65
	lsl r0, r0, #2
	str r4, [sp, #4]
	sub r0, r0, #4
	ldr r0, [r5, r0]
	add r2, r7, #0
	mov r3, #0x10
	bl FUN_0200BB6C
	mov r1, #0x19
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl FUN_0200BBF0
	mov r1, #0x19
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	ldr r2, [sp]
	bl FUN_0200BF60
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02212C9C: .word MOD7_02214AB8
_02212CA0: .word MOD7_0221498C

	thumb_func_start MOD07_02212CA4
MOD07_02212CA4: ; 0x02212CA4
	push {lr}
	sub sp, #0x34
	add r2, r0, #0
	mov r0, #0
	add r3, sp, #0
	strh r0, [r3]
	strh r0, [r3, #2]
	strh r0, [r3, #4]
	strh r0, [r3, #6]
	ldr r3, [r1, #0x14]
	str r3, [sp, #8]
	ldr r3, [r1, #0x18]
	str r3, [sp, #0xc]
	mov r3, #1
	str r3, [sp, #0x10]
	ldr r3, [r1]
	str r3, [sp, #0x14]
	ldr r3, [r1, #4]
	str r3, [sp, #0x18]
	ldr r3, [r1, #8]
	str r3, [sp, #0x1c]
	ldr r3, [r1, #0xc]
	str r3, [sp, #0x20]
	ldr r1, [r1, #0x10]
	str r1, [sp, #0x2c]
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #0x30]
	ldr r0, [r2, r1]
	add r1, r1, #4
	ldr r1, [r2, r1]
	add r2, sp, #0
	bl FUN_0200C154
	add sp, #0x34
	pop {pc}

	thumb_func_start MOD07_02212CEC
MOD07_02212CEC: ; 0x02212CEC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	mov r4, #0
	cmp r0, #0
	bls _02212D16
	mov r7, #0x21
	add r5, r6, #0
	lsl r7, r7, #4
_02212D02:
	mov r0, #0x66
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0200C3DC
	ldr r0, [r6, r7]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blo _02212D02
_02212D16:
	mov r1, #0x19
	lsl r1, r1, #4
	ldr r0, [r6, r1]
	add r1, r1, #4
	ldr r1, [r6, r1]
	bl FUN_0200C398
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	bl FUN_0200BD04
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD07_02212D30
MOD07_02212D30: ; 0x02212D30
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r4, #0
	cmp r0, #0
	bls _02212D64
	mov r7, #0x66
	lsl r7, r7, #2
	add r6, r7, #0
	add r6, #0x78
_02212D48:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, r7]
	mov r1, #1
	ldr r0, [r0]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [r5, r6]
	cmp r4, r0
	blo _02212D48
_02212D64:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD07_02212D68
MOD07_02212D68: ; 0x02212D68
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl FUN_0201AB60
	ldr r0, [r4, #8]
	bl FUN_0200372C
	bl FUN_0201C30C
	bl FUN_0200BC30
	ldr r3, _02212D90 ; =0x027E0000
	ldr r1, _02212D94 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	nop
_02212D90: .word 0x027E0000
_02212D94: .word 0x00003FF8

	thumb_func_start MOD07_02212D98
MOD07_02212D98: ; 0x02212D98
	push {r4, r5, lr}
	sub sp, #0x64
	ldr r5, _02212E54 ; =0x0221496C
	add r3, sp, #0x54
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _02212E58 ; =0x02214A2C
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #3
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0xc]
	mov r1, #3
	bl FUN_02018744
	mov r1, #3
	add r3, r1, #0
	ldr r0, [r4, #0xc]
	mov r2, #0
	add r3, #0xfd
	bl FUN_0201AEE4
	ldr r5, _02212E5C ; =0x02214A48
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl FUN_02018744
	mov r3, #0xff
	ldr r0, [r4, #0xc]
	mov r1, #2
	mov r2, #0
	mvn r3, r3
	bl FUN_0201AEE4
	ldr r5, _02212E60 ; =0x02214A64
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_02018744
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	add sp, #0x64
	pop {r4, r5, pc}
	nop
_02212E54: .word MOD7_0221496C
_02212E58: .word MOD7_02214A2C
_02212E5C: .word MOD7_02214A48
_02212E60: .word MOD7_02214A64

	thumb_func_start MOD07_02212E64
MOD07_02212E64: ; 0x02212E64
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x1f
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, [r4, #0xc]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD07_02212E90
MOD07_02212E90: ; 0x02212E90
	push {r4, lr}
	sub sp, #0x10
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	add r4, r0, #0
	str r1, [sp, #8]
	ldr r0, [r4]
	mov r3, #1
	ldr r0, [r0, #0x24]
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x6c
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #4
	ldr r0, [r0, #0x24]
	mov r3, #1
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x6c
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #2
	ldr r0, [r0, #0x24]
	add r3, r1, #0
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x6c
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #3
	ldr r0, [r0, #0x24]
	add r3, r1, #0
	str r0, [sp, #0xc]
	ldr r2, [r4, #0xc]
	mov r0, #0x6c
	bl GfGfxLoader_LoadScrnData
	mov r2, #0
	str r2, [sp]
	ldr r0, [r4]
	mov r1, #1
	ldr r0, [r0, #0x24]
	add r3, r2, #0
	str r0, [sp, #4]
	mov r0, #0x6c
	bl GfGfxLoader_GXLoadPal
	mov r1, #0
	ldr r0, [r4, #8]
	add r2, r1, #0
	mov r3, #0x60
	bl FUN_02003108
	ldr r1, _02212F28 ; =0x000018C6
	mov r0, #1
	bl FUN_02017FE4
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_02212F28: .word 0x000018C6

	thumb_func_start MOD07_02212F2C
MOD07_02212F2C: ; 0x02212F2C
	push {r3, lr}
	mov r0, #8
	str r0, [sp]
	ldr r0, _02212F40 ; =0x04000050
	mov r1, #3
	mov r2, #0x1c
	mov r3, #0x17
	bl G2x_SetBlendAlpha_
	pop {r3, pc}
	.align 2, 0
_02212F40: .word 0x04000050

	thumb_func_start MOD07_02212F44
MOD07_02212F44: ; 0x02212F44
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	ldr r4, _02213014 ; =0x022149E0
	add r3, sp, #0
	add r6, r0, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r1, r2, #0
	add r0, r6, #0
	mov r2, #0x15
	bl MOD07_02212C04
	add r0, r6, #0
	bl MOD07_0221301C
	ldr r4, _02213018 ; =0x02214C64
	mov r7, #0
	add r5, r6, #0
_02212F72:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD07_02212CA4
	mov r1, #0x66
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r7, r7, #1
	add r4, #0x1c
	add r5, r5, #4
	cmp r7, #0xc
	blo _02212F72
	mov r1, #0
	mov r2, #0xff
	add r0, r6, #0
	mvn r2, r2
	add r3, r1, #0
	bl MOD07_0221309C
	mov r2, #0xff
	add r0, r6, #0
	mov r1, #1
	mvn r2, r2
	mov r3, #0
	bl MOD07_0221309C
	mov r1, #2
	add r2, r1, #0
	add r0, r6, #0
	add r2, #0xfe
	mov r3, #0
	bl MOD07_0221309C
	mov r1, #3
	add r2, r1, #0
	add r0, r6, #0
	add r2, #0xfd
	mov r3, #0
	bl MOD07_0221309C
	add r0, r6, #0
	bl MOD07_022131C0
	mov r0, #0x21
	mov r1, #0xc
	lsl r0, r0, #4
	str r1, [r6, r0]
	add r0, r6, #0
	bl MOD07_022132CC
	mov r1, #0
	mov r2, #0xff
	add r0, r6, #0
	mvn r2, r2
	add r3, r1, #0
	bl MOD07_02213354
	mov r2, #0xff
	add r0, r6, #0
	mov r1, #1
	mvn r2, r2
	mov r3, #0
	bl MOD07_02213354
	mov r1, #2
	add r2, r1, #0
	add r0, r6, #0
	add r2, #0xfe
	mov r3, #0
	bl MOD07_02213354
	mov r1, #3
	add r2, r1, #0
	add r0, r6, #0
	add r2, #0xfd
	mov r3, #0
	bl MOD07_02213354
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02213014: .word MOD7_022149E0
_02213018: .word MOD7_02214C64

	thumb_func_start MOD07_0221301C
MOD07_0221301C: ; 0x0221301C
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02213098 ; =0x0000B807
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #8]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x1b
	mov r3, #0x90
	bl FUN_0200C00C
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, _02213098 ; =0x0000B807
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #0xc]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x6c
	mov r3, #8
	bl FUN_0200C06C
	mov r0, #1
	str r0, [sp]
	ldr r0, _02213098 ; =0x0000B807
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x1b
	mov r3, #0x8f
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _02213098 ; =0x0000B807
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x1b
	mov r3, #0x91
	bl FUN_0200C13C
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_02213098: .word 0x0000B807

	thumb_func_start MOD07_0221309C
MOD07_0221309C: ; 0x0221309C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	ldr r4, _022130F8 ; =0x02214950
	str r2, [sp]
	ldrb r5, [r4]
	str r3, [sp, #4]
	add r3, sp, #8
	strb r5, [r3]
	ldrb r5, [r4, #1]
	add r2, sp, #8
	mov r7, #0
	strb r5, [r3, #1]
	ldrb r5, [r4, #2]
	ldrb r4, [r4, #3]
	add r6, r0, r1
	strb r5, [r3, #2]
	strb r4, [r3, #3]
	ldrb r2, [r2, r1]
	add r4, r7, #0
	lsl r2, r2, #2
	add r5, r0, r2
_022130C6:
	ldr r1, _022130FC ; =0x00000B64
	mov r0, #0x66
	ldrb r1, [r6, r1]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r2, r1, r4
	ldr r1, [sp]
	add r1, r1, r2
	ldr r2, _02213100 ; =0x00000B68
	lsl r1, r1, #0x10
	ldrb r3, [r6, r2]
	ldr r2, [sp, #4]
	asr r1, r1, #0x10
	add r2, r2, r3
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	add r7, r7, #1
	add r4, #0x13
	add r5, r5, #4
	cmp r7, #3
	blo _022130C6
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022130F8: .word MOD7_02214950
_022130FC: .word 0x00000B64
_02213100: .word 0x00000B68

	thumb_func_start MOD07_02213104
MOD07_02213104: ; 0x02213104
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r0, #0
	add r0, r1, #0
	str r1, [sp]
	str r2, [sp, #4]
	add r7, r3, #0
	bl GetPartyCount
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r5, #0
	ldr r0, [sp, #4]
	add r4, r5, #0
	cmp r0, #0
	ble _022131BC
	lsl r0, r7, #2
	add r6, r6, r0
_0221312A:
	lsl r0, r4, #2
	add r1, r6, r0
	mov r0, #0x66
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_0200C5C0
	ldr r0, [sp, #8]
	cmp r0, r4
	bls _022131B0
	ldr r0, [sp]
	add r1, r4, #0
	bl GetPartyMonByIndex
	mov r1, #5
	mov r2, #0
	add r7, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _022131B0
	add r0, r7, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _022131B0
	add r0, r7, #0
	bl FUN_0207C2D4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #6
	bne _02213184
	lsl r0, r5, #2
	add r1, r6, r0
	mov r0, #0x66
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #3
	bl FUN_0200C5C0
	b _022131AA
_02213184:
	cmp r0, #7
	beq _0221319A
	lsl r0, r5, #2
	add r1, r6, r0
	mov r0, #0x66
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #2
	bl FUN_0200C5C0
	b _022131AA
_0221319A:
	lsl r0, r5, #2
	add r1, r6, r0
	mov r0, #0x66
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_0200C5C0
_022131AA:
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
_022131B0:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, [sp, #4]
	cmp r4, r0
	blt _0221312A
_022131BC:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD07_022131C0
MOD07_022131C0: ; 0x022131C0
	push {r4, lr}
	add r4, r0, #0
	ldr r2, [r4]
	add r1, r2, #0
	add r1, #0x29
	ldrb r1, [r1]
	cmp r1, #0
	ldr r1, [r2, #4]
	bne _022131EA
	mov r2, #6
	mov r3, #0
	bl MOD07_02213104
	ldr r1, [r4]
	mov r2, #6
	ldr r1, [r1, #8]
	add r0, r4, #0
	add r3, r2, #0
	bl MOD07_02213104
	pop {r4, pc}
_022131EA:
	mov r2, #3
	mov r3, #0
	bl MOD07_02213104
	ldr r1, [r4]
	mov r2, #3
	ldr r1, [r1, #0xc]
	add r0, r4, #0
	add r3, r2, #0
	bl MOD07_02213104
	ldr r1, [r4]
	add r0, r4, #0
	ldr r1, [r1, #8]
	mov r2, #3
	mov r3, #6
	bl MOD07_02213104
	ldr r1, [r4]
	add r0, r4, #0
	ldr r1, [r1, #0x10]
	mov r2, #3
	mov r3, #9
	bl MOD07_02213104
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD07_02213220
MOD07_02213220: ; 0x02213220
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r4, r0, #0
	mov r0, #0
	add r5, r4, #0
	str r0, [sp]
	str r0, [sp, #4]
	add r7, r2, #0
	add r5, #0x10
	add r6, r1, #0
	ldr r0, [r4, #0xc]
	add r1, r5, #0
	mov r2, #8
	mov r3, #2
	bl AddTextWindowTopLeftCorner
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0xc1
	lsl r0, r0, #0xa
	str r0, [sp, #8]
	add r0, r5, #0
	add r2, r7, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, _022132C0 ; =0x00000B44
	ldr r0, [r4, r0]
	str r0, [sp, #0x10]
	mov r0, #0x65
	str r5, [sp, #0x14]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200CA40
	str r0, [sp, #0x18]
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r1, _022132C4 ; =0x0000B807
	bl FUN_0200C334
	mov r1, #0x3e
	lsl r2, r6, #4
	lsl r1, r1, #4
	sub r1, r1, r2
	lsl r1, r1, #5
	str r0, [sp, #0x1c]
	mov r0, #0
	str r1, [sp, #0x24]
	mov r1, #2
	str r0, [sp, #0x20]
	str r0, [sp, #0x28]
	str r0, [sp, #0x2c]
	str r0, [sp, #0x34]
	mov r0, #1
	str r1, [sp, #0x30]
	str r0, [sp, #0x38]
	ldr r0, [r4]
	lsl r6, r6, #2
	ldr r0, [r0, #0x24]
	str r0, [sp, #0x3c]
	ldr r0, _022132C8 ; =0x00000B48
	add r4, r4, r0
	add r0, sp, #0x10
	bl FUN_020117E8
	str r0, [r4, r6]
	ldr r0, [r4, r6]
	mov r1, #0
	bl FUN_02011A60
	add r0, r5, #0
	bl RemoveWindow
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022132C0: .word 0x00000B44
_022132C4: .word 0x0000B807
_022132C8: .word 0x00000B48

	thumb_func_start MOD07_022132CC
MOD07_022132CC: ; 0x022132CC
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	mov r0, #8
	ldr r1, [r1, #0x24]
	bl FUN_02011744
	ldr r1, _02213348 ; =0x00000B44
	str r0, [r4, r1]
	ldr r2, [r4]
	add r0, r4, #0
	ldr r2, [r2, #0x14]
	mov r1, #0
	bl MOD07_02213220
	ldr r2, [r4]
	add r0, r4, #0
	ldr r2, [r2, #0x18]
	mov r1, #2
	bl MOD07_02213220
	ldr r2, [r4]
	add r0, r2, #0
	add r0, #0x29
	ldrb r0, [r0]
	cmp r0, #1
	bne _0221331A
	ldr r2, [r2, #0x1c]
	add r0, r4, #0
	mov r1, #1
	bl MOD07_02213220
	ldr r2, [r4]
	add r0, r4, #0
	ldr r2, [r2, #0x20]
	mov r1, #3
	bl MOD07_02213220
	pop {r4, pc}
_0221331A:
	ldr r2, [r2, #0x14]
	add r0, r4, #0
	mov r1, #1
	bl MOD07_02213220
	ldr r2, [r4]
	add r0, r4, #0
	ldr r2, [r2, #0x18]
	mov r1, #3
	bl MOD07_02213220
	ldr r0, _0221334C ; =0x00000B4C
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_020119D0
	ldr r0, _02213350 ; =0x00000B54
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_020119D0
	pop {r4, pc}
	nop
_02213348: .word 0x00000B44
_0221334C: .word 0x00000B4C
_02213350: .word 0x00000B54

	thumb_func_start MOD07_02213354
MOD07_02213354: ; 0x02213354
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r1, r2, #0
	add r2, r3, #0
	add r4, r0, #0
	lsl r0, r5, #2
	add r0, r4, r0
	ldr r3, _0221337C ; =0x00000B48
	add r4, r4, r5
	add r5, r3, #0
	ldr r0, [r0, r3]
	add r5, #0x24
	add r3, #0x28
	ldrb r5, [r4, r5]
	ldrb r3, [r4, r3]
	add r1, r1, r5
	add r2, r2, r3
	bl FUN_020118C4
	pop {r3, r4, r5, pc}
	.align 2, 0
_0221337C: .word 0x00000B48

	thumb_func_start MOD07_02213380
MOD07_02213380: ; 0x02213380
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r0, [r7]
	add r0, #0x28
	ldrb r0, [r0]
	cmp r0, #0
	beq _022133AA
	ldr r6, _022133AC ; =0x00000B48
	mov r4, #0
	add r5, r7, #0
_02213394:
	ldr r0, [r5, r6]
	bl FUN_02011870
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blo _02213394
	ldr r0, _022133B0 ; =0x00000B44
	ldr r0, [r7, r0]
	bl FUN_020117BC
_022133AA:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022133AC: .word 0x00000B48
_022133B0: .word 0x00000B44

	thumb_func_start MOD07_022133B4
MOD07_022133B4: ; 0x022133B4
	push {r3, r4}
	ldr r1, [r0]
	add r1, #0x29
	ldrb r1, [r1]
	cmp r1, #1
	ldr r1, _02213480 ; =0x00000B64
	bne _02213432
	mov r2, #0x18
	strb r2, [r0, r1]
	mov r3, #0x8c
	add r2, r1, #4
	strb r3, [r0, r2]
	mov r3, #0x55
	add r2, r1, #1
	strb r3, [r0, r2]
	mov r3, #0xa4
	add r2, r1, #5
	strb r3, [r0, r2]
	mov r3, #0x84
	add r2, r1, #2
	strb r3, [r0, r2]
	mov r3, #0x2c
	add r2, r1, #6
	strb r3, [r0, r2]
	mov r3, #0xc1
	add r2, r1, #3
	strb r3, [r0, r2]
	mov r3, #0x44
	add r2, r1, #7
	strb r3, [r0, r2]
	add r2, r1, #0
	mov r3, #0xf
	add r2, #8
	strb r3, [r0, r2]
	add r2, r1, #0
	mov r3, #0x72
	add r2, #0xc
	strb r3, [r0, r2]
	add r2, r1, #0
	mov r3, #0x4c
	add r2, #9
	strb r3, [r0, r2]
	add r2, r1, #0
	mov r3, #0x8a
	add r2, #0xd
	strb r3, [r0, r2]
	add r2, r1, #0
	mov r3, #0x7b
	add r2, #0xa
	strb r3, [r0, r2]
	add r2, r1, #0
	mov r3, #0x12
	add r2, #0xe
	strb r3, [r0, r2]
	add r2, r1, #0
	mov r3, #0xb8
	add r2, #0xb
	strb r3, [r0, r2]
	mov r2, #0x2a
	add r1, #0xf
	strb r2, [r0, r1]
	pop {r3, r4}
	bx lr
_02213432:
	mov r2, #0x18
	strb r2, [r0, r1]
	mov r4, #0xa0
	add r2, r1, #4
	strb r4, [r0, r2]
	mov r3, #0x51
	add r2, r1, #1
	strb r3, [r0, r2]
	add r2, r1, #5
	strb r4, [r0, r2]
	mov r3, #0x88
	add r2, r1, #2
	strb r3, [r0, r2]
	mov r4, #0x30
	add r2, r1, #6
	strb r4, [r0, r2]
	mov r3, #0xc1
	add r2, r1, #3
	strb r3, [r0, r2]
	add r2, r1, #7
	strb r4, [r0, r2]
	add r2, r1, #0
	mov r3, #0xf
	add r2, #8
	strb r3, [r0, r2]
	add r2, r1, #0
	mov r3, #0x86
	add r2, #0xc
	strb r3, [r0, r2]
	add r2, r1, #0
	mov r3, #0x80
	add r2, #0xa
	strb r3, [r0, r2]
	mov r2, #0x16
	add r1, #0xe
	strb r2, [r0, r1]
	pop {r3, r4}
	bx lr
	nop
_02213480: .word 0x00000B64

	thumb_func_start MOD07_02213484
MOD07_02213484: ; 0x02213484
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	ldr r4, _02213560 ; =0x022149C8
	add r3, sp, #0
	add r6, r0, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r1, r2, #0
	add r0, r6, #0
	mov r2, #0x17
	bl MOD07_02212C04
	add r0, r6, #0
	bl MOD07_0221301C
	add r0, r6, #0
	bl MOD07_02213568
	ldr r4, _02213564 ; =0x02214C64
	mov r7, #0
	add r5, r6, #0
_022134B8:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD07_02212CA4
	mov r1, #0x66
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r7, r7, #1
	add r4, #0x1c
	add r5, r5, #4
	cmp r7, #0xe
	blo _022134B8
	mov r1, #0
	mov r2, #0xff
	add r0, r6, #0
	mvn r2, r2
	add r3, r1, #0
	bl MOD07_0221309C
	mov r2, #0xff
	add r0, r6, #0
	mov r1, #1
	mvn r2, r2
	mov r3, #0
	bl MOD07_0221309C
	mov r1, #2
	add r2, r1, #0
	add r0, r6, #0
	add r2, #0xfe
	mov r3, #0
	bl MOD07_0221309C
	mov r1, #3
	add r2, r1, #0
	add r0, r6, #0
	add r2, #0xfd
	mov r3, #0
	bl MOD07_0221309C
	add r0, r6, #0
	bl MOD07_022131C0
	add r0, r6, #0
	bl MOD07_022135C8
	add r0, r6, #0
	bl MOD07_022132CC
	mov r1, #0
	mov r2, #0xff
	add r0, r6, #0
	mvn r2, r2
	add r3, r1, #0
	bl MOD07_02213354
	mov r2, #0xff
	add r0, r6, #0
	mov r1, #1
	mvn r2, r2
	mov r3, #0
	bl MOD07_02213354
	mov r1, #2
	add r2, r1, #0
	add r0, r6, #0
	add r2, #0xfe
	mov r3, #0
	bl MOD07_02213354
	mov r1, #3
	add r2, r1, #0
	add r0, r6, #0
	add r2, #0xfd
	mov r3, #0
	bl MOD07_02213354
	mov r0, #0x21
	mov r1, #0xe
	lsl r0, r0, #4
	str r1, [r6, r0]
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02213560: .word MOD7_022149C8
_02213564: .word MOD7_02214C64

	thumb_func_start MOD07_02213568
MOD07_02213568: ; 0x02213568
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _022135C4 ; =0x0000B808
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #8]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x6c
	mov r3, #5
	bl FUN_0200C00C
	mov r0, #0
	str r0, [sp]
	ldr r0, _022135C4 ; =0x0000B808
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x6c
	mov r3, #6
	bl FUN_0200C124
	mov r0, #0
	str r0, [sp]
	ldr r0, _022135C4 ; =0x0000B808
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x6c
	mov r3, #7
	bl FUN_0200C13C
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_022135C4: .word 0x0000B808

	thumb_func_start MOD07_022135C8
MOD07_022135C8: ; 0x022135C8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200C644
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4]
	add r0, #0x2a
	ldrb r0, [r0]
	cmp r0, #3
	bne _0221360A
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x80
	mov r2, #0x60
	bl FUN_0200C714
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_0200C5C0
	pop {r4, pc}
_0221360A:
	bl MOD07_02212BD4
	cmp r0, #1
	ldr r0, [r4]
	bne _02213658
	add r0, #0x2a
	ldrb r0, [r0]
	cmp r0, #1
	bne _0221363A
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x30
	mov r2, #0x60
	bl FUN_0200C714
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xd0
	mov r2, #0x60
	bl FUN_0200C714
	b _0221369A
_0221363A:
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xd0
	mov r2, #0x60
	bl FUN_0200C714
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x30
	mov r2, #0x60
	bl FUN_0200C714
	b _0221369A
_02213658:
	add r0, #0x2a
	ldrb r0, [r0]
	cmp r0, #1
	bne _0221367E
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xd0
	mov r2, #0x60
	bl FUN_0200C714
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x30
	mov r2, #0x60
	bl FUN_0200C714
	b _0221369A
_0221367E:
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x30
	mov r2, #0x60
	bl FUN_0200C714
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xd0
	mov r2, #0x60
	bl FUN_0200C714
_0221369A:
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200C5C0
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_0200C5C0
	pop {r4, pc}

	thumb_func_start MOD07_022136B4
MOD07_022136B4: ; 0x022136B4
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #2
	mov r1, #0
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r4]
	mov r2, #4
	ldr r0, [r0, #0x24]
	add r3, r1, #0
	bl FUN_02022318
	ldr r1, _0221378C ; =0x00000B58
	ldr r2, _02213790 ; =0x04000060
	str r0, [r4, r1]
	ldrh r1, [r2]
	ldr r0, _02213794 ; =0xFFFFCFFF
	and r1, r0
	mov r0, #8
	orr r0, r1
	strh r0, [r2]
	bl FUN_02012CC8
	ldr r0, [r4]
	mov r1, #0x12
	ldr r0, [r0, #0x24]
	lsl r1, r1, #0xa
	bl AllocFromHeap
	mov r2, #0xb6
	lsl r2, r2, #4
	str r0, [r4, r2]
	mov r0, #1
	str r0, [sp]
	ldr r0, [r4]
	mov r3, #0x12
	ldr r0, [r0, #0x24]
	ldr r1, _02213798 ; =MOD07_02213834
	str r0, [sp, #4]
	ldr r0, _0221379C ; =MOD07_02213810
	ldr r2, [r4, r2]
	lsl r3, r3, #0xa
	bl FUN_02012CDC
	ldr r1, _022137A0 ; =0x00000B5C
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	bl FUN_0201343C
	add r2, r0, #0
	mov r0, #1
	mov r1, #0xe1
	lsl r0, r0, #0xc
	lsl r1, r1, #0xe
	bl FUN_0201EC94
	ldr r2, [r4]
	mov r0, #0x3d
	ldr r2, [r2, #0x24]
	mov r1, #2
	bl FUN_0201318C
	add r1, r0, #0
	ldr r0, _022137A0 ; =0x00000B5C
	mov r2, #0xa
	ldr r0, [r4, r0]
	mov r3, #1
	bl FUN_02013194
	mov r1, #0
	ldr r0, _022137A0 ; =0x00000B5C
	add r2, r1, #0
	ldr r0, [r4, r0]
	add r3, r1, #0
	bl FUN_020133AC
	ldr r0, _022137A0 ; =0x00000B5C
	mov r2, #0
	ldr r0, [r4, r0]
	mov r1, #1
	add r3, r2, #0
	bl FUN_020133AC
	ldr r0, _022137A0 ; =0x00000B5C
	mov r2, #0
	ldr r0, [r4, r0]
	mov r1, #2
	add r3, r2, #0
	bl FUN_020133AC
	ldr r0, _022137A0 ; =0x00000B5C
	mov r2, #0
	ldr r0, [r4, r0]
	mov r1, #3
	add r3, r2, #0
	bl FUN_020133AC
	ldr r0, _022137A0 ; =0x00000B5C
	mov r2, #0
	ldr r0, [r4, r0]
	mov r1, #4
	add r3, r2, #0
	bl FUN_020133AC
	add sp, #8
	pop {r4, pc}
	nop
_0221378C: .word 0x00000B58
_02213790: .word 0x04000060
_02213794: .word 0xFFFFCFFF
_02213798: .word MOD07_02213834
_0221379C: .word MOD07_02213810
_022137A0: .word 0x00000B5C

	thumb_func_start MOD07_022137A4
MOD07_022137A4: ; 0x022137A4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	add r0, #0x28
	ldrb r0, [r0]
	cmp r0, #1
	beq _022137B6
	mov r0, #0
	pop {r4, pc}
_022137B6:
	bl FUN_020222AC
	ldr r0, _022137D8 ; =0x00000B5C
	ldr r0, [r4, r0]
	bl FUN_020133C8
	cmp r0, #0
	bne _022137CA
	mov r0, #0
	pop {r4, pc}
_022137CA:
	bl FUN_02013364
	bl FUN_02013388
	mov r0, #1
	pop {r4, pc}
	nop
_022137D8: .word 0x00000B5C

	thumb_func_start MOD07_022137DC
MOD07_022137DC: ; 0x022137DC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	add r0, #0x28
	ldrb r0, [r0]
	cmp r0, #1
	bne _02213804
	ldr r0, _02213808 ; =0x00000B5C
	ldr r0, [r4, r0]
	bl FUN_02012DE4
	mov r0, #0xb6
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r0, _0221380C ; =0x00000B58
	ldr r0, [r4, r0]
	bl FUN_020223BC
_02213804:
	pop {r4, pc}
	nop
_02213808: .word 0x00000B5C
_0221380C: .word 0x00000B58

	thumb_func_start MOD07_02213810
MOD07_02213810: ; 0x02213810
	push {r4, lr}
	ldr r3, _02213830 ; =NNS_GfdDefaultFuncAllocTexVram
	mov r2, #0
	ldr r3, [r3]
	blx r3
	add r4, r0, #0
	bl FUN_0201327C
	cmp r4, #0
	bne _02213828
	bl GF_AssertFail
_02213828:
	lsl r0, r4, #0x10
	lsr r0, r0, #0xd
	pop {r4, pc}
	nop
_02213830: .word NNS_GfdDefaultFuncAllocTexVram

	thumb_func_start MOD07_02213834
MOD07_02213834: ; 0x02213834
	push {r4, lr}
	ldr r3, _02213854 ; =NNS_GfdDefaultFuncAllocPlttVram
	mov r2, #1
	ldr r3, [r3]
	blx r3
	add r4, r0, #0
	bl FUN_020132BC
	cmp r4, #0
	bne _0221384C
	bl GF_AssertFail
_0221384C:
	lsl r0, r4, #0x10
	lsr r0, r0, #0xd
	pop {r4, pc}
	nop
_02213854: .word NNS_GfdDefaultFuncAllocPlttVram

	thumb_func_start MOD07_02213858
MOD07_02213858: ; 0x02213858
	push {r4, r5, lr}
	sub sp, #0x64
	ldr r5, _022138E8 ; =0x0221497C
	add r3, sp, #0x54
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _022138EC ; =0x02214A9C
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_02018744
	ldr r5, _022138F0 ; =0x02214A10
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl FUN_02018744
	ldr r5, _022138F4 ; =0x02214A80
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #3
	str r0, [r3]
	ldr r0, [r4, #0xc]
	mov r3, #0
	bl FUN_02016C18
	add sp, #0x64
	pop {r4, r5, pc}
	nop
_022138E8: .word MOD7_0221497C
_022138EC: .word MOD7_02214A9C
_022138F0: .word MOD7_02214A10
_022138F4: .word MOD7_02214A80

	thumb_func_start MOD07_022138F8
MOD07_022138F8: ; 0x022138F8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x1e
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, [r4, #0xc]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #0xc]
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD07_02213924
MOD07_02213924: ; 0x02213924
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5]
	mov r1, #0xf
	ldr r0, [r0, #0x24]
	mov r3, #3
	str r0, [sp, #0xc]
	ldr r2, [r5, #0xc]
	mov r0, #0x14
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5]
	mov r1, #0x11
	ldr r0, [r0, #0x24]
	mov r3, #3
	str r0, [sp, #0xc]
	ldr r2, [r5, #0xc]
	mov r0, #0x14
	bl GfGfxLoader_LoadScrnData
	ldr r2, [r5]
	mov r0, #0x14
	ldr r2, [r2, #0x24]
	mov r1, #0x10
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0x10
	add r4, r0, #0
	bl NNS_G2dGetUnpackedPaletteData
	ldr r2, [sp, #0x10]
	mov r0, #3
	ldr r1, [r2, #0xc]
	ldr r2, [r2, #8]
	mov r3, #0
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	bl FUN_02017FB4
	ldr r1, [sp, #0x10]
	ldr r0, _022139B4 ; =0x000004E4
	ldr r1, [r1, #0xc]
	add r0, r5, r0
	add r1, #0x60
	mov r2, #0x60
	bl memcpy
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [r5]
	mov r2, #0xa9
	lsl r2, r2, #2
	ldr r3, _022139B8 ; =0x00000424
	add r1, r5, r2
	add r2, #0xc0
	ldr r0, [r0, #0x24]
	add r2, r5, r2
	add r3, r5, r3
	bl FUN_020724D4
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_022139B4: .word 0x000004E4
_022139B8: .word 0x00000424

	thumb_func_start MOD07_022139BC
MOD07_022139BC: ; 0x022139BC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldr r6, _02213A90 ; =0x02214954
	mov r4, #0
	add r7, r5, #0
_022139C8:
	cmp r4, #0
	beq _022139D0
	cmp r4, #3
	bne _022139D8
_022139D0:
	mov r0, #0xa9
	lsl r0, r0, #2
	add r1, r5, r0
	b _022139EE
_022139D8:
	mov r0, #0x86
	lsl r0, r0, #2
	ldrh r0, [r7, r0]
	cmp r0, #0
	bne _022139E8
	ldr r0, _02213A94 ; =0x00000424
	add r1, r5, r0
	b _022139EE
_022139E8:
	mov r0, #0xd9
	lsl r0, r0, #2
	add r1, r5, r0
_022139EE:
	mov r0, #0x10
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #0x10
	str r0, [sp, #0x14]
	mov r0, #6
	str r0, [sp, #0x18]
	ldrb r2, [r6]
	ldrb r3, [r6, #1]
	ldr r0, [r5, #0xc]
	mov r1, #2
	bl FUN_02018170
	mov r0, #0x86
	lsl r0, r0, #2
	ldrh r0, [r7, r0]
	cmp r0, #0
	beq _02213A7A
	mov r0, #0x10
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	add r0, r4, #3
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldrb r2, [r6]
	ldrb r3, [r6, #1]
	ldr r0, [r5, #0xc]
	mov r1, #2
	bl FUN_020186B4
	cmp r4, #3
	bhs _02213A46
	ldr r0, [r5]
	add r0, #0x29
	ldrb r0, [r0]
	cmp r0, #1
	beq _02213A54
_02213A46:
	cmp r4, #3
	blo _02213A68
	ldr r0, [r5]
	add r0, #0x29
	ldrb r0, [r0]
	cmp r0, #0
	bne _02213A68
_02213A54:
	ldr r1, _02213A98 ; =0x00000504
	add r3, r4, #3
	lsl r3, r3, #0x15
	mov r0, #2
	add r1, r5, r1
	mov r2, #0x20
	lsr r3, r3, #0x10
	bl FUN_02017FB4
	b _02213A7A
_02213A68:
	ldr r1, _02213A9C ; =0x000004E4
	add r3, r4, #3
	lsl r3, r3, #0x15
	mov r0, #2
	add r1, r5, r1
	mov r2, #0x20
	lsr r3, r3, #0x10
	bl FUN_02017FB4
_02213A7A:
	add r4, r4, #1
	add r7, #0x18
	add r6, r6, #2
	cmp r4, #6
	blo _022139C8
	ldr r0, [r5, #0xc]
	mov r1, #2
	bl FUN_0201AC68
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02213A90: .word MOD7_02214954
_02213A94: .word 0x00000424
_02213A98: .word 0x00000504
_02213A9C: .word 0x000004E4

	thumb_func_start MOD07_02213AA0
MOD07_02213AA0: ; 0x02213AA0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	str r1, [sp]
	add r1, r2, #0
	bl GetBgTilemapBuffer
	add r6, r0, #0
	ldr r0, [r4]
	add r0, #0x29
	ldrb r0, [r0]
	cmp r0, #0
	bne _02213ABE
	mov r7, #0x10
	b _02213AC0
_02213ABE:
	mov r7, #0
_02213AC0:
	mov r5, #0
_02213AC2:
	lsl r0, r5, #5
	add r0, r7, r0
	lsl r4, r0, #1
	ldr r0, [sp]
	lsl r1, r5, #5
	add r0, r0, r1
	add r1, r6, r4
	mov r2, #0x20
	bl memcpy
	add r0, r6, r4
	mov r1, #0
	mov r2, #0x20
	bl memset
	add r0, r5, #1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x18
	blo _02213AC2
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD07_02213AEC
MOD07_02213AEC: ; 0x02213AEC
	push {r4, lr}
	ldr r1, _02213B18 ; =0x00000544
	add r4, r0, #0
	add r1, r4, r1
	mov r2, #1
	bl MOD07_02213AA0
	ldr r1, _02213B1C ; =0x00000844
	add r0, r4, #0
	add r1, r4, r1
	mov r2, #2
	bl MOD07_02213AA0
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_0201AC68
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl FUN_0201AC68
	pop {r4, pc}
	.align 2, 0
_02213B18: .word 0x00000544
_02213B1C: .word 0x00000844

	thumb_func_start MOD07_02213B20
MOD07_02213B20: ; 0x02213B20
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	add r0, #0x29
	ldrb r0, [r0]
	cmp r0, #0
	bne _02213B80
	mov r0, #0x20
	sub r6, r0, r4
	ldr r1, _02213BE4 ; =0x00000544
	str r4, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	add r1, r5, r1
	str r1, [sp, #8]
	mov r3, #0
	str r3, [sp, #0xc]
	lsl r2, r6, #0x18
	str r3, [sp, #0x10]
	mov r1, #0x10
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	ldr r0, [r5, #0xc]
	mov r1, #1
	lsr r2, r2, #0x18
	bl FUN_02018170
	ldr r0, _02213BE8 ; =0x00000844
	lsl r2, r6, #0x18
	str r4, [sp]
	mov r1, #0x18
	str r1, [sp, #4]
	add r0, r5, r0
	str r0, [sp, #8]
	mov r3, #0
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	mov r0, #0x10
	str r0, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r0, [r5, #0xc]
	mov r1, #2
	lsr r2, r2, #0x18
	bl FUN_02018170
	b _02213BCE
_02213B80:
	ldr r2, _02213BE4 ; =0x00000544
	mov r0, #0x10
	str r4, [sp]
	mov r1, #0x18
	sub r6, r0, r4
	str r1, [sp, #4]
	add r2, r5, r2
	str r2, [sp, #8]
	lsl r2, r6, #0x18
	lsr r2, r2, #0x18
	str r2, [sp, #0xc]
	mov r2, #0
	str r2, [sp, #0x10]
	str r0, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r0, [r5, #0xc]
	mov r1, #1
	add r3, r2, #0
	bl FUN_02018170
	ldr r1, _02213BE8 ; =0x00000844
	mov r2, #0
	str r4, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	add r1, r5, r1
	str r1, [sp, #8]
	lsl r1, r6, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0xc]
	str r2, [sp, #0x10]
	mov r1, #0x10
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	ldr r0, [r5, #0xc]
	mov r1, #2
	add r3, r2, #0
	bl FUN_02018170
_02213BCE:
	ldr r0, [r5, #0xc]
	mov r1, #1
	bl FUN_0201AC68
	ldr r0, [r5, #0xc]
	mov r1, #2
	bl FUN_0201AC68
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	nop
_02213BE4: .word 0x00000544
_02213BE8: .word 0x00000844

	thumb_func_start MOD07_02213BEC
MOD07_02213BEC: ; 0x02213BEC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r0, r1, #0
	str r1, [sp]
	add r5, r2, #0
	bl GetPartyCount
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	mov r0, #0x18
	mul r0, r5
	add r0, r4, r0
	mov r6, #0
	str r0, [sp, #4]
_02213C0C:
	ldr r0, [sp, #8]
	cmp r0, r6
	bhi _02213C2E
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	bl FUN_0206B6D4
	mov r1, #0x18
	add r2, r6, #0
	mul r2, r1
	ldr r1, [sp, #4]
	add r2, r1, r2
	mov r1, #0x85
	lsl r1, r1, #2
	str r0, [r2, r1]
	b _02213D08
_02213C2E:
	ldr r0, [sp]
	add r1, r6, #0
	bl GetPartyMonByIndex
	mov r1, #0x18
	add r2, r6, #0
	mul r2, r1
	ldr r1, [sp, #4]
	add r4, r0, #0
	add r7, r1, r2
	bl FUN_0206B6C8
	mov r1, #0x85
	lsl r1, r1, #2
	str r0, [r7, r1]
	add r0, r4, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	mov r1, #0x86
	lsl r1, r1, #2
	strh r0, [r7, r1]
	add r0, r1, #0
	ldrh r0, [r7, r0]
	cmp r0, #0
	beq _02213D08
	mov r0, #0x18
	add r1, r6, #0
	mul r1, r0
	ldr r0, [sp, #4]
	mov r2, #0
	add r5, r0, r1
	add r0, r4, #0
	mov r1, #0x4c
	bl GetMonData
	ldr r1, _02213D18 ; =0x00000223
	mov r2, #0
	strb r0, [r5, r1]
	add r0, r4, #0
	mov r1, #0xa2
	bl GetMonData
	ldr r1, _02213D1C ; =0x0000021A
	mov r2, #0
	strh r0, [r5, r1]
	add r0, r4, #0
	mov r1, #0xa3
	bl GetMonData
	mov r1, #0x87
	lsl r1, r1, #2
	strh r0, [r5, r1]
	add r0, r4, #0
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	mov r1, #0x22
	lsl r1, r1, #4
	strb r0, [r5, r1]
	add r0, r4, #0
	mov r1, #6
	mov r2, #0
	bl GetMonData
	ldr r1, _02213D20 ; =0x0000021E
	mov r2, #0
	strh r0, [r5, r1]
	add r0, r4, #0
	mov r1, #0xa1
	bl GetMonData
	mov r1, #0x89
	lsl r1, r1, #2
	strb r0, [r5, r1]
	add r0, r4, #0
	mov r1, #0x70
	mov r2, #0
	bl GetMonData
	ldr r1, _02213D24 ; =0x00000225
	mov r2, #0
	strb r0, [r5, r1]
	add r0, r4, #0
	mov r1, #0xaf
	bl GetMonData
	cmp r0, #1
	bne _02213CE8
	mov r1, #0
	b _02213CEA
_02213CE8:
	mov r1, #1
_02213CEA:
	ldr r0, _02213D28 ; =0x00000222
	strb r1, [r7, r0]
	add r0, r4, #0
	bl GetMonGender
	ldr r1, _02213D2C ; =0x00000221
	strb r0, [r5, r1]
	add r0, r4, #0
	bl FUN_0207C2D4
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #0x8a
	lsl r0, r0, #2
	str r1, [r5, r0]
_02213D08:
	add r0, r6, #1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, #3
	bhs _02213D14
	b _02213C0C
_02213D14:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02213D18: .word 0x00000223
_02213D1C: .word 0x0000021A
_02213D20: .word 0x0000021E
_02213D24: .word 0x00000225
_02213D28: .word 0x00000222
_02213D2C: .word 0x00000221

	thumb_func_start MOD07_02213D30
MOD07_02213D30: ; 0x02213D30
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x85
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	mov r2, #0x90
	bl memset
	ldr r1, [r4]
	add r0, r4, #0
	ldr r1, [r1, #4]
	mov r2, #0
	bl MOD07_02213BEC
	ldr r1, [r4]
	add r0, r4, #0
	ldr r1, [r1, #0xc]
	mov r2, #3
	bl MOD07_02213BEC
	pop {r4, pc}

	thumb_func_start MOD07_02213D5C
MOD07_02213D5C: ; 0x02213D5C
	push {r4, lr}
	add r3, r0, #0
	add r2, r1, #0
	mov r0, #0x18
	mul r2, r0
	ldr r1, _02213DC0 ; =0x0000021A
	add r4, r3, r2
	ldrh r0, [r4, r1]
	cmp r0, #0
	bne _02213D74
	mov r0, #0
	pop {r4, pc}
_02213D74:
	add r1, #0xe
	ldr r1, [r4, r1]
	cmp r1, #7
	beq _02213D84
	cmp r1, #0
	beq _02213D84
	mov r0, #5
	pop {r4, pc}
_02213D84:
	mov r1, #0x87
	add r2, r3, r2
	lsl r1, r1, #2
	ldrh r1, [r2, r1]
	mov r2, #0x30
	bl FUN_02079A54
	cmp r0, #4
	bhi _02213DBC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02213DA2: ; jump table
	.short _02213DBC - _02213DA2 - 2 ; case 0
	.short _02213DB8 - _02213DA2 - 2 ; case 1
	.short _02213DB4 - _02213DA2 - 2 ; case 2
	.short _02213DB0 - _02213DA2 - 2 ; case 3
	.short _02213DAC - _02213DA2 - 2 ; case 4
_02213DAC:
	mov r0, #1
	pop {r4, pc}
_02213DB0:
	mov r0, #2
	pop {r4, pc}
_02213DB4:
	mov r0, #3
	pop {r4, pc}
_02213DB8:
	mov r0, #4
	pop {r4, pc}
_02213DBC:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_02213DC0: .word 0x0000021A

	thumb_func_start MOD07_02213DC4
MOD07_02213DC4: ; 0x02213DC4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0
	str r0, [sp, #8]
	str r1, [sp]
	add r0, r1, #0
	lsl r1, r0, #2
	ldr r0, [sp]
	ldr r2, _02213F1C ; =0x02214B28
	add r7, r0, r1
	lsl r0, r7, #2
	add r4, r5, r0
	ldr r0, [sp]
	mov r1, #0xa
	mul r1, r0
	str r4, [sp, #4]
	add r6, r2, r1
_02213DE8:
	mov r1, #0x1c
	add r2, r7, #0
	mul r2, r1
	ldr r1, _02213F20 ; =0x02214DEC
	add r0, r5, #0
	add r1, r1, r2
	bl MOD07_02212CA4
	mov r1, #0x66
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #0
	ldrb r1, [r6]
	ldrb r2, [r6, #1]
	ldr r0, [r4, r0]
	bl FUN_0200C714
	ldr r0, [sp, #8]
	add r7, r7, #1
	add r0, r0, #1
	add r4, r4, #4
	add r6, r6, #2
	str r0, [sp, #8]
	cmp r0, #5
	blo _02213DE8
	ldr r0, [sp]
	mov r3, #0x86
	mov r1, #0x18
	add r6, r0, #0
	mul r6, r1
	add r2, r5, r6
	lsl r3, r3, #2
	ldrh r0, [r2, r3]
	cmp r0, #0
	bne _02213E50
	mov r5, #0
	add r4, r3, #0
	add r6, r5, #0
	sub r4, #0x80
_02213E36:
	ldr r0, [sp, #4]
	add r1, r6, #0
	ldr r0, [r0, r4]
	bl FUN_0200C644
	ldr r0, [sp, #4]
	add r5, r5, #1
	add r0, r0, #4
	str r0, [sp, #4]
	cmp r5, #5
	blo _02213E36
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_02213E50:
	ldr r1, [sp]
	mov r4, #0x14
	mul r4, r1
	add r1, r3, #0
	sub r1, #0x80
	add r7, r5, r1
	add r1, r3, #0
	add r1, #0xd
	add r3, #0xb
	ldrb r1, [r2, r1]
	ldrb r2, [r2, r3]
	bl FUN_0206B7BC
	add r1, r0, #0
	ldr r0, [r7, r4]
	bl FUN_0200C66C
	ldr r1, [sp]
	add r0, r5, #0
	bl MOD07_02213D5C
	add r1, r0, #0
	ldr r0, [r7, r4]
	bl FUN_0200C5C0
	ldr r1, _02213F24 ; =0x0000021E
	add r0, r5, r6
	ldrh r0, [r0, r1]
	cmp r0, #0
	bne _02213E9A
	add r0, r5, r4
	sub r1, #0x82
	ldr r0, [r0, r1]
	mov r1, #0
	bl FUN_0200C644
	b _02213EC0
_02213E9A:
	bl ItemIdIsMail
	cmp r0, #1
	bne _02213EB2
	mov r0, #0x67
	add r1, r5, r4
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_0200C5C0
	b _02213EC0
_02213EB2:
	mov r0, #0x67
	add r1, r5, r4
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_0200C5C0
_02213EC0:
	mov r0, #0x89
	add r1, r5, r6
	lsl r0, r0, #2
	ldrb r1, [r1, r0]
	cmp r1, #0
	bne _02213EDA
	add r1, r5, r4
	sub r0, #0x84
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_0200C644
	b _02213EE6
_02213EDA:
	add r1, r5, r4
	sub r0, #0x84
	ldr r0, [r1, r0]
	mov r1, #2
	bl FUN_0200C5C0
_02213EE6:
	mov r3, #0x8a
	add r0, r5, r6
	lsl r3, r3, #2
	ldr r0, [r0, r3]
	cmp r0, #7
	bne _02213F02
	add r0, r5, r4
	sub r3, #0x84
	ldr r0, [r0, r3]
	mov r1, #0
	bl FUN_0200C644
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_02213F02:
	add r0, r3, #0
	add r1, r5, r4
	sub r0, #0x84
	ldr r0, [r1, r0]
	ldr r1, [sp, #8]
	mov r2, #0x18
	mul r2, r1
	add r1, r5, r2
	ldr r1, [r1, r3]
	bl FUN_0200C5C0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02213F1C: .word MOD7_02214B28
_02213F20: .word MOD7_02214DEC
_02213F24: .word 0x0000021E

	thumb_func_start MOD07_02213F28
MOD07_02213F28: ; 0x02213F28
	push {r3, r4, r5, lr}
	sub sp, #0x18
	ldr r5, _02213F88 ; =0x022149F8
	add r3, sp, #0
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r1, r2, #0
	add r0, r4, #0
	mov r2, #0x1f
	bl MOD07_02212C04
	add r0, r4, #0
	bl MOD07_02213F8C
	add r0, r4, #0
	bl MOD07_02214034
	add r0, r4, #0
	bl MOD07_022140BC
	add r0, r4, #0
	bl MOD07_02214144
	mov r5, #0
_02213F64:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD07_02213DC4
	add r5, r5, #1
	cmp r5, #6
	blo _02213F64
	add r0, r4, #0
	mov r1, #0x10
	bl MOD07_022141CC
	mov r0, #0x21
	mov r1, #0x1e
	lsl r0, r0, #4
	str r1, [r4, r0]
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_02213F88: .word MOD7_022149F8

	thumb_func_start MOD07_02213F8C
MOD07_02213F8C: ; 0x02213F8C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	bl FUN_0206B888
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, _0221402C ; =0x0000B808
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #0xc]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x13
	bl FUN_0200C06C
	bl FUN_0206B890
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _02214030 ; =0x0000B809
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x13
	bl FUN_0200C124
	bl FUN_0206B89C
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _02214030 ; =0x0000B809
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x13
	bl FUN_0200C13C
	mov r4, #0
	add r6, r5, #0
	add r7, r4, #0
_02213FFA:
	str r7, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _02214030 ; =0x0000B809
	mov r1, #0x65
	add r0, r4, r0
	str r0, [sp, #8]
	mov r0, #0x19
	mov r3, #0x85
	lsl r0, r0, #4
	lsl r1, r1, #2
	lsl r3, r3, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	ldr r3, [r6, r3]
	mov r2, #0x13
	bl FUN_0200C00C
	add r4, r4, #1
	add r6, #0x18
	cmp r4, #6
	blo _02213FFA
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0221402C: .word 0x0000B808
_02214030: .word 0x0000B809

	thumb_func_start MOD07_02214034
MOD07_02214034: ; 0x02214034
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _022140B0 ; =0x0000B80F
	mov r1, #0x19
	mov r2, #0x14
	lsl r1, r1, #4
	str r0, [sp, #8]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	add r3, r2, #0
	bl FUN_0200C00C
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, _022140B4 ; =0x0000B809
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #0xc]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x14
	mov r3, #0x15
	bl FUN_0200C06C
	mov r0, #0
	str r0, [sp]
	ldr r0, _022140B8 ; =0x0000B80A
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x14
	mov r3, #0x13
	bl FUN_0200C124
	mov r0, #0
	str r0, [sp]
	ldr r0, _022140B8 ; =0x0000B80A
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x14
	mov r3, #0x12
	bl FUN_0200C13C
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_022140B0: .word 0x0000B80F
_022140B4: .word 0x0000B809
_022140B8: .word 0x0000B80A

	thumb_func_start MOD07_022140BC
MOD07_022140BC: ; 0x022140BC
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _02214138 ; =0x0000B810
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #8]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x27
	mov r3, #0x40
	bl FUN_0200C00C
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, _0221413C ; =0x0000B80A
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #0xc]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x27
	mov r3, #0x41
	bl FUN_0200C06C
	mov r0, #0
	str r0, [sp]
	ldr r0, _02214140 ; =0x0000B80B
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x27
	mov r3, #0x3f
	bl FUN_0200C124
	mov r0, #0
	str r0, [sp]
	ldr r0, _02214140 ; =0x0000B80B
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x27
	mov r3, #0x3e
	bl FUN_0200C13C
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_02214138: .word 0x0000B810
_0221413C: .word 0x0000B80A
_02214140: .word 0x0000B80B

	thumb_func_start MOD07_02214144
MOD07_02214144: ; 0x02214144
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _022141C0 ; =0x0000B811
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #8]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x14
	mov r3, #2
	bl FUN_0200C00C
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, _022141C4 ; =0x0000B80B
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #0xc]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x14
	mov r3, #8
	bl FUN_0200C06C
	mov r0, #0
	str r0, [sp]
	ldr r0, _022141C8 ; =0x0000B80C
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x14
	mov r3, #1
	bl FUN_0200C124
	mov r3, #0
	mov r1, #0x19
	ldr r0, _022141C8 ; =0x0000B80C
	str r3, [sp]
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x14
	bl FUN_0200C13C
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_022141C0: .word 0x0000B811
_022141C4: .word 0x0000B80B
_022141C8: .word 0x0000B80C

	thumb_func_start MOD07_022141CC
MOD07_022141CC: ; 0x022141CC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp]
	ldr r0, [r0]
	add r7, r1, #0
	add r0, #0x29
	ldrb r0, [r0]
	cmp r0, #0
	bne _022141E6
	mov r0, #3
	str r0, [sp, #8]
	lsl r0, r7, #0x13
	b _022141F0
_022141E6:
	mov r0, #0
	str r0, [sp, #8]
	lsl r0, r7, #3
	neg r0, r0
	lsl r0, r0, #0x10
_022141F0:
	asr r7, r0, #0x10
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #8]
	mov r1, #0xa
	ldr r2, _02214248 ; =0x02214B28
	mul r1, r0
	add r0, r2, r1
	str r0, [sp, #4]
_02214202:
	ldr r1, [sp, #8]
	ldr r0, [sp, #0xc]
	ldr r4, [sp, #4]
	add r1, r1, r0
	lsl r0, r1, #2
	add r0, r1, r0
	lsl r1, r0, #2
	ldr r0, [sp]
	mov r6, #0
	add r5, r0, r1
_02214216:
	ldrb r1, [r4]
	mov r0, #0x66
	lsl r0, r0, #2
	add r1, r7, r1
	lsl r1, r1, #0x10
	ldrb r2, [r4, #1]
	ldr r0, [r5, r0]
	asr r1, r1, #0x10
	bl FUN_0200C714
	add r6, r6, #1
	add r4, r4, #2
	add r5, r5, #4
	cmp r6, #5
	blt _02214216
	ldr r0, [sp, #4]
	add r0, #0xa
	str r0, [sp, #4]
	ldr r0, [sp, #0xc]
	add r0, r0, #1
	str r0, [sp, #0xc]
	cmp r0, #3
	blt _02214202
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02214248: .word MOD7_02214B28

	thumb_func_start MOD07_0221424C
MOD07_0221424C: ; 0x0221424C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r7, #0
	ldr r4, _02214270 ; =0x02214BA4
	mov r6, #0
	add r5, #0x10
_02214258:
	ldr r0, [r7, #0xc]
	add r1, r5, #0
	add r2, r4, #0
	bl AddWindow
	add r6, r6, #1
	add r4, #8
	add r5, #0x10
	cmp r6, #0x18
	blo _02214258
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02214270: .word MOD7_02214BA4

	thumb_func_start MOD07_02214274
MOD07_02214274: ; 0x02214274
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
	add r5, #0x10
_0221427C:
	add r0, r5, #0
	bl RemoveWindow
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #0x18
	blo _0221427C
	pop {r3, r4, r5, pc}

	thumb_func_start MOD07_0221428C
MOD07_0221428C: ; 0x0221428C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	ldr r4, [sp, #0x3c]
	add r5, r0, #0
	add r7, r5, #0
	lsl r0, r4, #6
	add r7, #0x10
	str r0, [sp, #0x1c]
	str r1, [sp, #0x10]
	str r3, [sp, #0x14]
	ldr r6, [sp, #0x38]
	cmp r4, #3
	ldr r0, [r5]
	bhs _022142B4
	ldr r0, [r0, #4]
	add r1, r4, #0
	bl GetPartyMonByIndex
	str r0, [sp, #0x18]
	b _022142BE
_022142B4:
	ldr r0, [r0, #0xc]
	sub r1, r4, #3
	bl GetPartyMonByIndex
	str r0, [sp, #0x18]
_022142BE:
	add r1, r4, #0
	ldr r0, [sp, #0x10]
	add r1, #8
	bl NewString_ReadMsgData
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x18]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [sp, #0x14]
	mov r1, #0
	bl BufferBoxMonNickname
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x20]
	add r1, r6, #0
	bl StringExpandPlaceholders
	ldr r0, [sp, #0x20]
	bl String_dtor
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214370 ; =0x000F0E00
	add r2, r6, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x1c]
	add r3, r1, #0
	add r0, r7, r0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	mov r0, #0x18
	mul r0, r4
	add r2, r5, r0
	ldr r0, _02214374 ; =0x00000222
	ldrb r1, [r2, r0]
	cmp r1, #0
	bne _0221436C
	sub r0, r0, #1
	ldrb r0, [r2, r0]
	cmp r0, #0
	bne _02214344
	ldr r0, [sp, #0x10]
	mov r1, #0x1b
	add r2, r6, #0
	bl ReadMsgDataIntoString
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0xc1
	lsl r0, r0, #0xa
	str r0, [sp, #8]
	ldr r0, [sp, #0x1c]
	add r2, r6, #0
	add r0, r7, r0
	mov r3, #0x40
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
_02214344:
	cmp r0, #1
	bne _0221436C
	ldr r0, [sp, #0x10]
	mov r1, #0x1c
	add r2, r6, #0
	bl ReadMsgDataIntoString
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02214378 ; =0x00050600
	add r2, r6, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x1c]
	mov r3, #0x40
	add r0, r7, r0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
_0221436C:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02214370: .word 0x000F0E00
_02214374: .word 0x00000222
_02214378: .word 0x00050600

	thumb_func_start MOD07_0221437C
MOD07_0221437C: ; 0x0221437C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	ldr r0, [sp, #0x2c]
	add r5, r6, #0
	lsl r0, r0, #2
	add r0, r0, #1
	lsl r4, r0, #4
	mov r0, #5
	add r7, r1, #0
	str r3, [sp, #0x10]
	str r0, [sp]
	add r5, #0x10
	add r0, r2, #0
	mov r1, #1
	add r2, r5, r4
	mov r3, #0
	bl FUN_0200B9A8
	ldr r1, [sp, #0x2c]
	add r0, r7, #0
	add r1, r1, #2
	bl NewString_ReadMsgData
	mov r1, #0
	add r7, r0, #0
	ldr r3, [sp, #0x2c]
	mov r2, #0x18
	mul r2, r3
	add r3, r6, r2
	mov r2, #0x22
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	lsl r2, r2, #4
	ldrb r2, [r3, r2]
	ldr r0, [sp, #0x10]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x28]
	add r2, r7, #0
	bl StringExpandPlaceholders
	add r0, r7, #0
	bl String_dtor
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022143F8 ; =0x000F0E00
	ldr r2, [sp, #0x28]
	str r0, [sp, #8]
	add r0, r5, r4
	mov r3, #0x10
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022143F8: .word 0x000F0E00

	thumb_func_start MOD07_022143FC
MOD07_022143FC: ; 0x022143FC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	ldr r5, [sp, #0x44]
	add r7, r0, #0
	str r0, [sp, #0x10]
	lsl r0, r5, #2
	add r0, r0, #2
	lsl r0, r0, #4
	str r0, [sp, #0x28]
	str r1, [sp, #0x14]
	add r0, r1, #0
	add r1, r5, #0
	add r1, #0x14
	str r3, [sp, #0x18]
	ldr r4, [sp, #0x40]
	add r7, #0x10
	bl NewString_ReadMsgData
	str r0, [sp, #0x20]
	mov r0, #0x18
	mul r0, r5
	str r0, [sp, #0x1c]
	mov r1, #0
	ldr r3, [sp, #0x10]
	ldr r2, [sp, #0x1c]
	str r1, [sp]
	mov r0, #1
	add r3, r3, r2
	str r0, [sp, #4]
	ldr r2, _02214508 ; =0x0000021A
	ldr r0, [sp, #0x18]
	ldrh r2, [r3, r2]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #0x20]
	add r1, r4, #0
	bl StringExpandPlaceholders
	ldr r0, [sp, #0x20]
	bl String_dtor
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	bl FUN_02002E14
	mov ip, r0
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0221450C ; =0x000F0E00
	mov r6, ip
	str r0, [sp, #8]
	ldr r0, [sp, #0x28]
	mov r3, #0x1c
	add r0, r7, r0
	add r2, r4, #0
	sub r3, r3, r6
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x14]
	mov r1, #0x1a
	add r2, r4, #0
	bl ReadMsgDataIntoString
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0221450C ; =0x000F0E00
	add r2, r4, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x28]
	mov r3, #0x1c
	add r0, r7, r0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	bl FUN_02002E14
	str r0, [sp, #0x24]
	add r5, #0xe
	ldr r0, [sp, #0x14]
	add r1, r5, #0
	bl NewString_ReadMsgData
	add r5, r0, #0
	ldr r3, [sp, #0x10]
	ldr r2, [sp, #0x1c]
	mov r1, #0
	add r3, r3, r2
	mov r2, #0x87
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	lsl r2, r2, #2
	ldrh r2, [r3, r2]
	ldr r0, [sp, #0x18]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, [sp, #0x18]
	add r1, r4, #0
	add r2, r5, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	bl String_dtor
	mov r1, #0
	ldr r3, [sp, #0x24]
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0221450C ; =0x000F0E00
	add r3, #0x1c
	str r0, [sp, #8]
	ldr r0, [sp, #0x28]
	add r2, r4, #0
	add r0, r7, r0
	str r1, [sp, #0xc]
	str r3, [sp, #0x24]
	bl AddTextPrinterParameterized2
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_02214508: .word 0x0000021A
_0221450C: .word 0x000F0E00

	thumb_func_start MOD07_02214510
MOD07_02214510: ; 0x02214510
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	lsl r0, r1, #2
	add r2, r5, #0
	add r0, r0, #3
	add r2, #0x10
	lsl r0, r0, #4
	add r4, r2, r0
	mov r0, #0x18
	add r6, r1, #0
	mul r6, r0
	mov r0, #0x87
	lsl r0, r0, #2
	add r7, r5, r0
	sub r0, r0, #2
	add r0, r5, r0
	str r0, [sp, #8]
	ldrh r0, [r0, r6]
	ldrh r1, [r7, r6]
	mov r2, #0x30
	bl FUN_02079A54
	cmp r0, #4
	bhi _0221459E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0221454E: ; jump table
	.short _0221459E - _0221454E - 2 ; case 0
	.short _02214588 - _0221454E - 2 ; case 1
	.short _02214570 - _0221454E - 2 ; case 2
	.short _02214558 - _0221454E - 2 ; case 3
	.short _02214558 - _0221454E - 2 ; case 4
_02214558:
	ldrb r3, [r4, #9]
	ldr r1, _022145F4 ; =0x000004F6
	mov r0, #1
	lsl r3, r3, #4
	add r3, #9
	lsl r3, r3, #0x11
	add r1, r5, r1
	mov r2, #4
	lsr r3, r3, #0x10
	bl FUN_02017FB4
	b _0221459E
_02214570:
	ldrb r3, [r4, #9]
	ldr r1, _022145F8 ; =0x00000516
	mov r0, #1
	lsl r3, r3, #4
	add r3, #9
	lsl r3, r3, #0x11
	add r1, r5, r1
	mov r2, #4
	lsr r3, r3, #0x10
	bl FUN_02017FB4
	b _0221459E
_02214588:
	ldrb r3, [r4, #9]
	ldr r1, _022145FC ; =0x00000536
	mov r0, #1
	lsl r3, r3, #4
	add r3, #9
	lsl r3, r3, #0x11
	add r1, r5, r1
	mov r2, #4
	lsr r3, r3, #0x10
	bl FUN_02017FB4
_0221459E:
	ldr r0, [sp, #8]
	ldrh r1, [r7, r6]
	ldrh r0, [r0, r6]
	mov r2, #0x30
	bl FUN_02079A0C
	add r5, r0, #0
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0xa
	mov r2, #0
	mov r3, #2
	bl FillWindowPixelRect
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #9
	mov r2, #0
	mov r3, #3
	bl FillWindowPixelRect
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0xa
	mov r2, #0
	mov r3, #5
	bl FillWindowPixelRect
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_022145F4: .word 0x000004F6
_022145F8: .word 0x00000516
_022145FC: .word 0x00000536

	thumb_func_start MOD07_02214600
MOD07_02214600: ; 0x02214600
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r0, #0
	ldr r6, [sp, #0x2c]
	add r5, r7, #0
	str r1, [sp, #8]
	add r5, #0x10
	lsl r4, r6, #6
	add r0, r5, r4
	mov r1, #0
	str r2, [sp, #0xc]
	str r3, [sp, #0x10]
	bl FillWindowPixelBuffer
	add r0, r5, r4
	add r0, #0x10
	mov r1, #0
	bl FillWindowPixelBuffer
	add r0, r5, r4
	add r0, #0x20
	mov r1, #0
	bl FillWindowPixelBuffer
	add r0, r5, r4
	add r0, #0x30
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, [sp, #0x28]
	ldr r1, [sp, #8]
	str r0, [sp]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	add r0, r7, #0
	str r6, [sp, #4]
	bl MOD07_0221428C
	ldr r0, [sp, #0x28]
	ldr r1, [sp, #8]
	str r0, [sp]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	add r0, r7, #0
	str r6, [sp, #4]
	bl MOD07_0221437C
	ldr r0, [sp, #0x28]
	ldr r1, [sp, #8]
	str r0, [sp]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	add r0, r7, #0
	str r6, [sp, #4]
	bl MOD07_022143FC
	add r0, r7, #0
	add r1, r6, #0
	bl MOD07_02214510
	add r0, r5, r4
	bl FUN_02019220
	add r0, r5, r4
	add r0, #0x10
	bl FUN_02019220
	add r0, r5, r4
	add r0, #0x20
	bl FUN_02019220
	add r0, r5, r4
	add r0, #0x30
	bl FUN_02019220
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD07_0221469C
MOD07_0221469C: ; 0x0221469C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	ldr r3, [r6]
	ldr r2, _0221471C ; =0x00000192
	ldr r3, [r3, #0x24]
	mov r0, #0
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	ldr r3, [r6]
	str r0, [sp, #0x10]
	ldr r3, [r3, #0x24]
	mov r0, #0xf
	mov r1, #0xe
	mov r2, #0
	bl MessagePrinter_new
	str r0, [sp, #0xc]
	ldr r0, [r6]
	ldr r0, [r0, #0x24]
	bl ScrStrBufs_new
	ldr r1, [r6]
	str r0, [sp, #8]
	ldr r1, [r1, #0x24]
	mov r0, #0x20
	bl String_ctor
	add r7, r0, #0
	mov r4, #0
	add r5, r6, #0
_022146DC:
	mov r0, #0x86
	lsl r0, r0, #2
	ldrh r0, [r5, r0]
	cmp r0, #0
	beq _022146F6
	ldr r1, [sp, #0x10]
	str r7, [sp]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #8]
	add r0, r6, #0
	str r4, [sp, #4]
	bl MOD07_02214600
_022146F6:
	add r4, r4, #1
	add r5, #0x18
	cmp r4, #6
	blo _022146DC
	add r0, r7, #0
	bl String_dtor
	ldr r0, [sp, #0x10]
	bl DestroyMsgData
	ldr r0, [sp, #0xc]
	bl MessagePrinter_delete
	ldr r0, [sp, #8]
	bl ScrStrBufs_delete
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0221471C: .word 0x00000192

	thumb_func_start MOD07_02214720
MOD07_02214720: ; 0x02214720
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _022147A4
	bl FUN_02031190
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	add r0, r4, #0
	add r0, #0x2a
	ldrb r0, [r0]
	ldr r1, [r4]
	sub r0, r0, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02034998
	cmp r0, #1
	bne _0221479C
	mov r0, #1
	add r7, r5, #0
	eor r7, r0
	mov r0, #0x34
	ldr r1, [r4]
	mul r0, r7
	add r0, r1, r0
	add r0, #0x29
	ldrb r0, [r0]
	bl TrainerClass_GetGenderOrTrainerCount
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x24]
	mov r1, #0x10
	bl AllocFromHeap
	add r5, r0, #0
	add r0, r7, #0
	bl FUN_020313CC
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x14]
	add r1, r5, #0
	mov r2, #8
	bl CopyStringToU16Array
	ldr r1, [sp, #0x10]
	ldr r3, [r4, #0x24]
	add r0, r5, #0
	add r2, r6, #0
	bl FUN_020294B4
	add r6, r0, #0
	add r0, r5, #0
	bl FreeToHeap
	b _0221493A
_0221479C:
	bl FUN_02033534
	cmp r0, #4
	bls _022147A6
_022147A4:
	b _0221494A
_022147A6:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022147B2: ; jump table
	.short _02214936 - _022147B2 - 2 ; case 0
	.short _022147BC - _022147B2 - 2 ; case 1
	.short _02214808 - _022147B2 - 2 ; case 2
	.short _02214854 - _022147B2 - 2 ; case 3
	.short _022148A0 - _022147B2 - 2 ; case 4
_022147BC:
	mov r0, #1
	add r7, r5, #0
	eor r7, r0
	mov r0, #0x34
	ldr r1, [r4]
	mul r0, r7
	add r0, r1, r0
	add r0, #0x29
	ldrb r0, [r0]
	bl TrainerClass_GetGenderOrTrainerCount
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x24]
	mov r1, #0x10
	bl AllocFromHeap
	add r5, r0, #0
	add r0, r7, #0
	bl FUN_020313CC
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x14]
	add r1, r5, #0
	mov r2, #8
	bl CopyStringToU16Array
	ldr r1, [sp, #0x14]
	ldr r3, [r4, #0x24]
	add r0, r5, #0
	add r2, r6, #0
	bl FUN_0202930C
	add r6, r0, #0
	add r0, r5, #0
	bl FreeToHeap
	b _0221493A
_02214808:
	mov r0, #1
	add r7, r5, #0
	eor r7, r0
	mov r0, #0x34
	ldr r1, [r4]
	mul r0, r7
	add r0, r1, r0
	add r0, #0x29
	ldrb r0, [r0]
	bl TrainerClass_GetGenderOrTrainerCount
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x24]
	mov r1, #0x10
	bl AllocFromHeap
	add r5, r0, #0
	add r0, r7, #0
	bl FUN_020313CC
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x14]
	add r1, r5, #0
	mov r2, #8
	bl CopyStringToU16Array
	ldr r1, [sp, #0x18]
	ldr r3, [r4, #0x24]
	add r0, r5, #0
	add r2, r6, #0
	bl FUN_0202934C
	add r6, r0, #0
	add r0, r5, #0
	bl FreeToHeap
	b _0221493A
_02214854:
	mov r0, #1
	add r7, r5, #0
	eor r7, r0
	mov r0, #0x34
	ldr r1, [r4]
	mul r0, r7
	add r0, r1, r0
	add r0, #0x29
	ldrb r0, [r0]
	bl TrainerClass_GetGenderOrTrainerCount
	str r0, [sp, #0x1c]
	ldr r0, [r4, #0x24]
	mov r1, #0x10
	bl AllocFromHeap
	add r5, r0, #0
	add r0, r7, #0
	bl FUN_020313CC
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r0, [r0, #0x14]
	add r1, r5, #0
	mov r2, #8
	bl CopyStringToU16Array
	ldr r1, [sp, #0x1c]
	ldr r3, [r4, #0x24]
	add r0, r5, #0
	add r2, r6, #0
	bl FUN_020293EC
	add r6, r0, #0
	add r0, r5, #0
	bl FreeToHeap
	b _0221493A
_022148A0:
	ldr r0, [r4, #0x24]
	mov r1, #0x10
	bl AllocFromHeap
	add r5, r0, #0
	ldr r0, [r4, #0x24]
	mov r1, #0x10
	bl AllocFromHeap
	add r7, r0, #0
	bl MOD07_02212BD4
	cmp r0, #1
	ldr r0, [r4]
	bne _022148EA
	add r0, #0x5d
	ldrb r0, [r0]
	bl TrainerClass_GetGenderOrTrainerCount
	str r0, [sp, #8]
	ldr r0, [r4]
	add r0, #0xc5
	ldrb r0, [r0]
	bl TrainerClass_GetGenderOrTrainerCount
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x18]
	add r1, r5, #0
	mov r2, #8
	bl CopyStringToU16Array
	ldr r0, [r4, #0x20]
	add r1, r7, #0
	mov r2, #8
	bl CopyStringToU16Array
	b _02214914
_022148EA:
	add r0, #0x29
	ldrb r0, [r0]
	bl TrainerClass_GetGenderOrTrainerCount
	str r0, [sp, #8]
	ldr r0, [r4]
	add r0, #0x91
	ldrb r0, [r0]
	bl TrainerClass_GetGenderOrTrainerCount
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x14]
	add r1, r5, #0
	mov r2, #8
	bl CopyStringToU16Array
	ldr r0, [r4, #0x1c]
	add r1, r7, #0
	mov r2, #8
	bl CopyStringToU16Array
_02214914:
	str r6, [sp]
	ldr r0, [r4, #0x24]
	add r1, r7, #0
	str r0, [sp, #4]
	ldr r2, [sp, #8]
	ldr r3, [sp, #0xc]
	add r0, r5, #0
	bl FUN_0202938C
	add r6, r0, #0
	add r0, r5, #0
	bl FreeToHeap
	add r0, r7, #0
	bl FreeToHeap
	b _0221493A
_02214936:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
_0221493A:
	mov r0, #0x52
	ldr r1, [r4]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, r6, #0
	mov r2, #4
	bl FUN_02028AD4
_0221494A:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	.rodata
	.global MOD7_02214950
MOD7_02214950: ; 0x02214950
	.byte 0x00, 0x03, 0x06, 0x09

	.global MOD7_02214954
MOD7_02214954: ; 0x02214954
	.byte 0x00, 0x00, 0x00, 0x06, 0x00, 0x0C, 0x10, 0x01, 0x10, 0x07, 0x10, 0x0D

	.global MOD7_02214960
MOD7_02214960: ; 0x02214960
	.byte 0x08

	.global MOD7_02214961
MOD7_02214961: ; 0x02214961
	.byte 0x08, 0x00, 0x08, 0x00, 0x08, 0x04, 0x0C, 0x00, 0x0C, 0x00, 0x0C

	.global MOD7_0221496C
MOD7_0221496C: ; 0x0221496C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD7_0221497C
MOD7_0221497C: ; 0x0221497C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD7_0221498C
MOD7_0221498C: ; 0x0221498C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00

	.global MOD7_022149A0
MOD7_022149A0: ; 0x022149A0
	.word MOD07_02212000, MOD07_02212174, MOD07_02212AF4, MOD07_02212174
	.word MOD07_02212B48

	.global MOD7_022149B4
MOD7_022149B4: ; 0x022149B4
	.word MOD07_0221207C, MOD07_02212174, MOD07_022121AC, MOD07_02212378
	.word MOD07_0221258C

	.global MOD7_022149C8
MOD7_022149C8: ; 0x022149C8
	.byte 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD7_022149E0
MOD7_022149E0: ; 0x022149E0
	.byte 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD7_022149F8
MOD7_022149F8: ; 0x022149F8
	.byte 0x09, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD7_02214A10
MOD7_02214A10: ; 0x02214A10
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD7_02214A2C
MOD7_02214A2C: ; 0x02214A2C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x1E, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD7_02214A48
MOD7_02214A48: ; 0x02214A48
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x1C, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD7_02214A64
MOD7_02214A64: ; 0x02214A64
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1B, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD7_02214A80
MOD7_02214A80: ; 0x02214A80
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1D, 0x04, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD7_02214A9C
MOD7_02214A9C: ; 0x02214A9C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD7_02214AB8
MOD7_02214AB8: ; 0x02214AB8
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00

	.global MOD7_02214AD8
MOD7_02214AD8: ; 0x02214AD8
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD7_02214B00
MOD7_02214B00: ; 0x02214B00
	.word MOD07_022120FC, MOD07_02212174, MOD07_022121AC, MOD07_02212378
	.word MOD07_02212958, MOD07_02212968, MOD07_02212174, MOD07_02212A3C
	.word MOD07_02212174, MOD07_02212B48

	.global MOD7_02214B28
MOD7_02214B28: ; 0x02214B28
	.byte 0x1E, 0x10, 0x26, 0x18, 0x2E, 0x18, 0x24, 0x2C, 0x10, 0x0E, 0x1E, 0x40, 0x26, 0x48, 0x2E, 0x48
	.byte 0x24, 0x5C, 0x10, 0x3E, 0x1E, 0x70, 0x26, 0x78, 0x2E, 0x78, 0x24, 0x8C, 0x10, 0x6E, 0x9E, 0x18
	.byte 0xA6, 0x20, 0xAE, 0x20, 0xA4, 0x34, 0x90, 0x16, 0x9E, 0x48, 0xA6, 0x50, 0xAE, 0x50, 0xA4, 0x64
	.byte 0x90, 0x46, 0x9E, 0x78, 0xA6, 0x80, 0xAE, 0x80, 0xA4, 0x94, 0x90, 0x76

	.global MOD7_02214B64
MOD7_02214B64: ; 0x02214B64
	.word MOD07_022120FC, MOD07_02212174, MOD07_022121AC, MOD07_02212378
	.word MOD07_022126B4, MOD07_02212174, MOD07_022126C4, MOD07_02212704
	.word MOD07_02212958, MOD07_02212968, MOD07_02212174, MOD07_022129FC
	.word MOD07_02212174, MOD07_02212A64, MOD07_02212174, MOD07_02212B48

	.global MOD7_02214BA4
MOD7_02214BA4: ; 0x02214BA4
	.byte 0x01, 0x06, 0x01, 0x09, 0x02, 0x00, 0x01, 0x00, 0x01, 0x01, 0x04, 0x05, 0x02, 0x00, 0x13, 0x00
	.byte 0x01, 0x07, 0x04, 0x08, 0x02, 0x00, 0x1D, 0x00, 0x01, 0x08, 0x03, 0x06, 0x01, 0x03, 0x2D, 0x00
	.byte 0x01, 0x06, 0x07, 0x09, 0x02, 0x00, 0x33, 0x00, 0x01, 0x01, 0x0A, 0x05, 0x02, 0x00, 0x45, 0x00
	.byte 0x01, 0x07, 0x0A, 0x08, 0x02, 0x00, 0x4F, 0x00, 0x01, 0x08, 0x09, 0x06, 0x01, 0x04, 0x5F, 0x00
	.byte 0x01, 0x06, 0x0D, 0x09, 0x02, 0x00, 0x65, 0x00, 0x01, 0x01, 0x10, 0x05, 0x02, 0x00, 0x77, 0x00
	.byte 0x01, 0x07, 0x10, 0x08, 0x02, 0x00, 0x81, 0x00, 0x01, 0x08, 0x0F, 0x06, 0x01, 0x05, 0x91, 0x00
	.byte 0x01, 0x16, 0x02, 0x09, 0x02, 0x00, 0x97, 0x00, 0x01, 0x11, 0x05, 0x05, 0x02, 0x00, 0xA9, 0x00
	.byte 0x01, 0x17, 0x05, 0x08, 0x02, 0x00, 0xB3, 0x00, 0x01, 0x18, 0x04, 0x06, 0x01, 0x06, 0xC3, 0x00
	.byte 0x01, 0x16, 0x08, 0x09, 0x02, 0x00, 0xC9, 0x00, 0x01, 0x11, 0x0B, 0x05, 0x02, 0x00, 0xDB, 0x00
	.byte 0x01, 0x17, 0x0B, 0x08, 0x02, 0x00, 0xE5, 0x00, 0x01, 0x18, 0x0A, 0x06, 0x01, 0x07, 0xF5, 0x00
	.byte 0x01, 0x16, 0x0E, 0x09, 0x02, 0x00, 0xFB, 0x00, 0x01, 0x11, 0x11, 0x05, 0x02, 0x00, 0x0D, 0x01
	.byte 0x01, 0x17, 0x11, 0x08, 0x02, 0x00, 0x17, 0x01, 0x01, 0x18, 0x10, 0x06, 0x01, 0x08, 0x27, 0x01

	.global MOD7_02214C64
MOD7_02214C64: ; 0x02214C64
	.byte 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00
	.byte 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00
	.byte 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00
	.byte 0x07, 0xB8, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00
	.byte 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00
	.byte 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00
	.byte 0x07, 0xB8, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00
	.byte 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00
	.byte 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00
	.byte 0x07, 0xB8, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x08, 0xB8, 0x00, 0x00, 0x07, 0xB8, 0x00, 0x00, 0x08, 0xB8, 0x00, 0x00, 0x08, 0xB8, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0xB8, 0x00, 0x00
	.byte 0x07, 0xB8, 0x00, 0x00, 0x08, 0xB8, 0x00, 0x00, 0x08, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD7_02214DEC
MOD7_02214DEC: ; 0x02214DEC
	.byte 0x09, 0xB8, 0x00, 0x00, 0x08, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xB8, 0x00, 0x00
	.byte 0x09, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00
	.byte 0x0A, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x10, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x0B, 0xB8, 0x00, 0x00
	.byte 0x0B, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x11, 0xB8, 0x00, 0x00, 0x0B, 0xB8, 0x00, 0x00, 0x0C, 0xB8, 0x00, 0x00, 0x0C, 0xB8, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00
	.byte 0x08, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00
	.byte 0x0A, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x0F, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00
	.byte 0x0A, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x0B, 0xB8, 0x00, 0x00, 0x0B, 0xB8, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0xB8, 0x00, 0x00
	.byte 0x0B, 0xB8, 0x00, 0x00, 0x0C, 0xB8, 0x00, 0x00, 0x0C, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xB8, 0x00, 0x00, 0x08, 0xB8, 0x00, 0x00
	.byte 0x09, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x0F, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00
	.byte 0x0A, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x0F, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xB8, 0x00, 0x00
	.byte 0x0A, 0xB8, 0x00, 0x00, 0x0B, 0xB8, 0x00, 0x00, 0x0B, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0xB8, 0x00, 0x00, 0x0B, 0xB8, 0x00, 0x00
	.byte 0x0C, 0xB8, 0x00, 0x00, 0x0C, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x0C, 0xB8, 0x00, 0x00, 0x08, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00
	.byte 0x09, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x0F, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xB8, 0x00, 0x00
	.byte 0x09, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00
	.byte 0x0B, 0xB8, 0x00, 0x00, 0x0B, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x11, 0xB8, 0x00, 0x00, 0x0B, 0xB8, 0x00, 0x00, 0x0C, 0xB8, 0x00, 0x00
	.byte 0x0C, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x0D, 0xB8, 0x00, 0x00, 0x08, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xB8, 0x00, 0x00
	.byte 0x09, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00
	.byte 0x0A, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x10, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x0B, 0xB8, 0x00, 0x00
	.byte 0x0B, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x11, 0xB8, 0x00, 0x00, 0x0B, 0xB8, 0x00, 0x00, 0x0C, 0xB8, 0x00, 0x00, 0x0C, 0xB8, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0xB8, 0x00, 0x00
	.byte 0x08, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00
	.byte 0x0A, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x0F, 0xB8, 0x00, 0x00, 0x09, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00
	.byte 0x0A, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0xB8, 0x00, 0x00, 0x0A, 0xB8, 0x00, 0x00, 0x0B, 0xB8, 0x00, 0x00, 0x0B, 0xB8, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0xB8, 0x00, 0x00
	.byte 0x0B, 0xB8, 0x00, 0x00, 0x0C, 0xB8, 0x00, 0x00, 0x0C, 0xB8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.data
	.bss
