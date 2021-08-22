	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021F5268
MOD05_021F5268: ; 0x021F5268
	push {r3, r4, r5, lr}
	mov r5, #0
	add r4, r0, #0
	add r0, r1, #0
	add r1, r2, #0
	str r5, [sp]
	add r2, r5, #0
	bl GfGfxLoader_LoadFromNarc
	str r0, [r4]
	bl NNS_G3dGetMdlSet
	str r0, [r4, #4]
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r0, r0, r1
	str r0, [r4, #8]
	ldr r0, [r4]
	bl NNS_G3dGetTex
	str r0, [r4, #0xc]
	cmp r0, #0
	beq _021F52A4
	mov r2, #1
	ldr r0, _021F52A8 ; =MOD05_021F52AC
	add r1, r4, #0
	lsl r2, r2, #0xa
	bl FUN_0200CA98
_021F52A4:
	pop {r3, r4, r5, pc}
	nop
_021F52A8: .word MOD05_021F52AC

	thumb_func_start MOD05_021F52AC
MOD05_021F52AC: ; 0x021F52AC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	bl FUN_0201B3C4
	ldr r0, [r4]
	ldr r1, [r4, #0xc]
	bl FUN_0201B3A8
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F52C8
MOD05_021F52C8: ; 0x021F52C8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021F52F8
	add r1, sp, #4
	add r2, sp, #0
	bl NNS_G3dTexReleaseTexKey
	ldr r1, _021F5314 ; =NNS_GfdDefaultFuncFreeTexVram
	ldr r0, [sp, #4]
	ldr r1, [r1]
	blx r1
	ldr r1, _021F5314 ; =NNS_GfdDefaultFuncFreeTexVram
	ldr r0, [sp]
	ldr r1, [r1]
	blx r1
	ldr r0, [r4, #0xc]
	bl NNS_G3dPlttReleasePlttKey
	ldr r1, _021F5318 ; =NNS_GfdDefaultFuncFreePlttVram
	ldr r1, [r1]
	blx r1
_021F52F8:
	ldr r0, [r4]
	cmp r0, #0
	beq _021F5302
	bl FreeToHeap
_021F5302:
	mov r1, #0x10
	mov r0, #0
_021F5306:
	strb r0, [r4]
	add r4, r4, #1
	sub r1, r1, #1
	bne _021F5306
	add sp, #8
	pop {r4, pc}
	nop
_021F5314: .word NNS_GfdDefaultFuncFreeTexVram
_021F5318: .word NNS_GfdDefaultFuncFreePlttVram

	thumb_func_start MOD05_021F531C
MOD05_021F531C: ; 0x021F531C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	mov r6, #0
	add r1, r3, #0
	add r5, r0, #0
	add r0, r2, #0
	ldr r3, [sp, #0x18]
	add r2, r6, #0
	str r6, [sp]
	bl GfGfxLoader_LoadFromNarc
	add r2, r0, #0
	ldr r3, [sp, #0x1c]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F54EC
	add r0, r6, #0
	str r0, [r5, #0x10]
	add sp, #4
	pop {r3, r4, r5, r6, pc}

	thumb_func_start MOD05_021F5348
MOD05_021F5348: ; 0x021F5348
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021F54EC
	mov r0, #1
	str r0, [r4, #0x10]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F5358
MOD05_021F5358: ; 0x021F5358
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F5376
	add r0, r1, #0
	ldr r1, [r4, #8]
	bl NNS_G3dFreeAnmObj
	ldr r0, [r4, #0x10]
	cmp r0, #0
	bne _021F5376
	ldr r0, [r4]
	bl FreeToHeap
_021F5376:
	mov r1, #0x14
	mov r0, #0
_021F537A:
	strb r0, [r4]
	add r4, r4, #1
	sub r1, r1, #1
	bne _021F537A
	pop {r4, pc}

	thumb_func_start MOD05_021F5384
MOD05_021F5384: ; 0x021F5384
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	ldr r0, [r0, #8]
	ldrh r0, [r0, #4]
	lsl r2, r0, #0xc
	cmp r1, #0
	ble _021F53A2
	ldr r0, [r4, #0xc]
	add r0, r0, r1
	add r1, r2, #0
	bl _s32_div_f
	str r1, [r4, #0xc]
	b _021F53B4
_021F53A2:
	ldr r0, [r4, #0xc]
	add r3, r4, #0
	add r3, #0xc
	add r0, r0, r1
	str r0, [r4, #0xc]
	bpl _021F53B4
	ldr r0, [r3]
	add r0, r0, r2
	str r0, [r3]
_021F53B4:
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #8]
	str r1, [r0]
	pop {r4, pc}

	thumb_func_start MOD05_021F53BC
MOD05_021F53BC: ; 0x021F53BC
	push {r3, r4}
	ldr r2, [r0, #8]
	ldr r3, [r0, #0xc]
	ldr r2, [r2, #8]
	ldrh r2, [r2, #4]
	lsl r4, r2, #0xc
	mov r2, #0
	cmp r1, #0
	ble _021F53DE
	add r1, r3, r1
	cmp r1, r4
	bge _021F53D8
	str r1, [r0, #0xc]
	b _021F53EA
_021F53D8:
	str r4, [r0, #0xc]
	mov r2, #1
	b _021F53EA
_021F53DE:
	add r1, r3, r1
	bmi _021F53E6
	str r1, [r0, #0xc]
	b _021F53EA
_021F53E6:
	str r2, [r0, #0xc]
	mov r2, #1
_021F53EA:
	ldr r1, [r0, #0xc]
	ldr r0, [r0, #8]
	str r1, [r0]
	add r0, r2, #0
	pop {r3, r4}
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F53F8
MOD05_021F53F8: ; 0x021F53F8
	str r1, [r0, #0xc]
	ldr r0, [r0, #8]
	str r1, [r0]
	bx lr

	thumb_func_start MOD05_021F5400
MOD05_021F5400: ; 0x021F5400
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r1, #0
	mov r2, #0x78
	add r4, r0, #0
	bl memset
	ldr r1, [r5, #8]
	add r0, r4, #0
	bl NNS_G3dRenderObjInit
	mov r0, #1
	str r0, [r4, #0x6c]
	lsl r0, r0, #0xc
	str r0, [r4, #0x60]
	str r0, [r4, #0x64]
	str r0, [r4, #0x68]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F5424
MOD05_021F5424: ; 0x021F5424
	ldr r3, _021F542C ; =NNS_G3dRenderObjAddAnmObj
	ldr r1, [r1, #8]
	bx r3
	nop
_021F542C: .word NNS_G3dRenderObjAddAnmObj

	thumb_func_start MOD05_021F5430
MOD05_021F5430: ; 0x021F5430
	push {r4, lr}
	sub sp, #0x48
	add r4, r0, #0
	ldr r0, [r4, #0x6c]
	cmp r0, #0
	beq _021F54C4
	add r0, sp, #0x24
	bl MTX_Identity33_
	add r0, r4, #0
	add r0, #0x70
	ldrh r0, [r0]
	ldr r3, _021F54C8 ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0
	bl MTX_RotX33_
	add r1, sp, #0x24
	add r0, sp, #0
	add r2, r1, #0
	bl MTX_Concat33
	add r0, r4, #0
	add r0, #0x74
	ldrh r0, [r0]
	ldr r3, _021F54C8 ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0
	bl MTX_RotZ33_
	add r1, sp, #0x24
	add r0, sp, #0
	add r2, r1, #0
	bl MTX_Concat33
	add r0, r4, #0
	add r0, #0x72
	ldrh r0, [r0]
	ldr r3, _021F54C8 ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0
	bl MTX_RotY33_
	add r1, sp, #0x24
	add r0, sp, #0
	add r2, r1, #0
	bl MTX_Concat33
	add r1, r4, #0
	add r0, r4, #0
	add r4, #0x60
	add r1, #0x54
	add r2, sp, #0x24
	add r3, r4, #0
	bl FUN_0201B26C
_021F54C4:
	add sp, #0x48
	pop {r4, pc}
	.balign 4, 0
_021F54C8: .word FX_SinCosTable_

	thumb_func_start MOD05_021F54CC
MOD05_021F54CC: ; 0x021F54CC
	str r1, [r0, #0x6c]
	bx lr

	thumb_func_start MOD05_021F54D0
MOD05_021F54D0: ; 0x021F54D0
	str r1, [r0, #0x54]
	str r2, [r0, #0x58]
	str r3, [r0, #0x5c]
	bx lr

	thumb_func_start MOD05_021F54D8
MOD05_021F54D8: ; 0x021F54D8
	str r1, [r0, #0x60]
	str r2, [r0, #0x64]
	str r3, [r0, #0x68]
	bx lr

	thumb_func_start MOD05_021F54E0
MOD05_021F54E0: ; 0x021F54E0
	lsl r2, r2, #1
	add r0, r0, r2
	add r0, #0x70
	strh r1, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F54EC
MOD05_021F54EC: ; 0x021F54EC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	str r2, [r5]
	add r0, r2, #0
	mov r1, #0
	add r6, r3, #0
	bl NNS_G3dGetAnmByIdx
	str r0, [r5, #4]
	ldr r1, [r5, #4]
	ldr r2, [r4, #8]
	add r0, r6, #0
	bl NNS_G3dAllocAnmObj
	str r0, [r5, #8]
	ldr r1, [r5, #4]
	ldr r2, [r4, #8]
	ldr r3, [r4, #0xc]
	bl NNS_G3dAnmObjInit
	pop {r4, r5, r6, pc}
