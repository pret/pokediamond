	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD12_0222D5C0
MOD12_0222D5C0: ; 0x0222D5C0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r1, #1
	lsl r1, r1, #0x1a
	ldr r0, [r1]
	ldr r2, _0222D85C ; =0xFFFFE0FF
	and r0, r2
	str r0, [r1]
	ldr r0, _0222D860 ; =0x04001000
	ldr r3, [r0]
	and r2, r3
	str r2, [r0]
	ldr r3, [r1]
	ldr r2, _0222D864 ; =0xFFFF1FFF
	and r3, r2
	str r3, [r1]
	ldr r3, [r0]
	add r1, #0x50
	and r2, r3
	str r2, [r0]
	mov r2, #0
	strh r2, [r1]
	add r0, #0x50
	strh r2, [r0]
	mov r2, #7
	mov r0, #3
	mov r1, #0x15
	lsl r2, r2, #0x10
	bl FUN_0201681C
	ldr r1, _0222D868 ; =0x00001658
	add r0, r5, #0
	mov r2, #0x15
	bl OverlayManager_CreateAndGetData
	ldr r2, _0222D868 ; =0x00001658
	mov r1, #0
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0x15
	bl MOD12_022312D8
	str r0, [r4, #8]
	add r0, r5, #0
	bl OverlayManager_GetField18
	mov r1, #0x5b
	str r0, [r4]
	lsl r1, r1, #2
	str r4, [r0, r1]
	ldr r2, [r4]
	mov r3, #2
	add r0, r1, #4
	strb r3, [r2, r0]
	ldr r0, [r4]
	str r0, [r4, #0xc]
	add r0, r4, #0
	bl MOD12_0222DCEC
	mov r0, #0x15
	bl FUN_02002FD0
	str r0, [r4, #0x5c]
	mov r1, #1
	bl FUN_020038F0
	mov r2, #2
	ldr r0, [r4, #0x5c]
	mov r1, #0
	lsl r2, r2, #8
	mov r3, #0x15
	bl FUN_02003008
	mov r1, #1
	ldr r0, [r4, #0x5c]
	lsl r2, r1, #9
	mov r3, #0x15
	bl FUN_02003008
	mov r2, #7
	ldr r0, [r4, #0x5c]
	mov r1, #2
	lsl r2, r2, #6
	mov r3, #0x15
	bl FUN_02003008
	mov r2, #2
	ldr r0, [r4, #0x5c]
	mov r1, #3
	lsl r2, r2, #8
	mov r3, #0x15
	bl FUN_02003008
	mov r0, #0x15
	bl FUN_02016B94
	str r0, [r4, #0x30]
	mov r0, #0x40
	mov r1, #0x15
	bl FUN_0201C24C
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	mov r2, #0x23
	add r1, r4, #0
	lsl r2, r2, #4
	ldr r0, [r4]
	add r1, #0xc
	add r2, r4, r2
	bl MOD12_02231A24
	ldr r1, _0222D86C ; =0x0000081C
	str r0, [r4, r1]
	ldr r0, [r4, #0x30]
	bl MOD12_0222DB50
	bl FUN_0201CC08
	mov r0, #4
	bl FUN_0201CC24
	mov r0, #2
	mov r1, #0x15
	bl FUN_02002C50
	mov r0, #0x15
	bl FUN_0200BB14
	ldr r1, _0222D870 ; =MOD12_022449C8
	ldr r2, _0222D874 ; =MOD12_0224499C
	mov r3, #0x20
	str r0, [r4, #0x24]
	bl FUN_0200BB6C
	ldr r1, _0222D878 ; =0x00100010
	mov r0, #1
	bl FUN_02008D44
	mov r0, #1
	bl FUN_02008DDC
	ldr r0, [r4, #0x24]
	bl FUN_0200BB34
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x28]
	mov r2, #0x80
	bl FUN_0200BBF0
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x28]
	ldr r2, _0222D87C ; =MOD12_022449B0
	bl FUN_0200BF60
	ldr r0, [r4, #0x24]
	bl FUN_0200BB68
	mov r2, #0x11
	mov r1, #0
	lsl r2, r2, #0x10
	bl FUN_02008D24
	mov r0, #0x15
	bl FUN_02006D98
	str r0, [r4, #0x10]
	bl MOD12_0222DCAC
	mov r0, #0x15
	bl MOD08_02211F5C
	mov r1, #1
	str r0, [r4, #0x2c]
	bl MOD08_02211FF0
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0xbf
	mov r3, #0x15
	bl NewMsgDataFromNarc
	str r0, [r4, #0x44]
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0xc0
	mov r3, #0x15
	bl NewMsgDataFromNarc
	str r0, [r4, #0x48]
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0xc5
	mov r3, #0x15
	bl NewMsgDataFromNarc
	str r0, [r4, #0x4c]
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0xc6
	mov r3, #0x15
	bl NewMsgDataFromNarc
	str r0, [r4, #0x50]
	mov r0, #8
	mov r1, #0x15
	bl FUN_02011744
	str r0, [r4, #0x60]
	mov r0, #0x15
	bl ScrStrBufs_new
	str r0, [r4, #0x54]
	mov r0, #0x1e
	lsl r0, r0, #4
	mov r1, #0x15
	bl String_ctor
	str r0, [r4, #0x58]
	add r0, r4, #0
	bl MOD12_0222DFC4
	add r0, r4, #0
	bl MOD12_0222E0F8
	add r0, r4, #0
	bl MOD12_0222DC80
	add r0, r4, #0
	bl MOD12_022335B0
	add r0, r4, #0
	bl MOD12_0222DD20
	add r0, r4, #0
	bl MOD12_0222DE30
	ldr r7, _0222D880 ; =0x00000123
	mov r6, #0
	add r5, sp, #0xc
_0222D7BC:
	ldr r1, [r4]
	mov r2, #0
	ldrb r0, [r1, r7]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, r6, #0
	add r1, #0x36
	bl GetMonData
	strh r0, [r5]
	add r6, r6, #1
	add r5, r5, #2
	cmp r6, #4
	blt _0222D7BC
	ldr r0, _0222D86C ; =0x0000081C
	add r1, sp, #0xc
	ldr r0, [r4, r0]
	bl MOD12_02232C08
	ldr r0, _0222D86C ; =0x0000081C
	mov r1, #0
	ldr r0, [r4, r0]
	mov r2, #1
	add r3, r1, #0
	bl MOD12_02231B4C
	add r0, r4, #0
	add r0, #0xc
	bl MOD12_02233758
	bl FUN_02033E74
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r1, #0x15
	str r1, [sp, #8]
	mov r1, #0x1f
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, _0222D884 ; =MOD12_0222DB18
	ldr r2, _0222D888 ; =0x0000EA60
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #4]
	ldr r0, _0222D88C ; =0x00000824
	mov r1, #1
	strb r1, [r4, r0]
	bl GX_BothDispOn
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	ldr r1, _0222D890 ; =0x0000046F
	mov r0, #6
	mov r2, #1
	bl FUN_0200433C
	ldr r1, [r4]
	ldr r0, _0222D894 ; =0x00000171
	ldrb r0, [r1, r0]
	bl FUN_020833D4
	ldr r0, _0222D898 ; =MOD12_0222DAE4
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	mov r0, #1
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0222D85C: .word 0xFFFFE0FF
_0222D860: .word 0x04001000
_0222D864: .word 0xFFFF1FFF
_0222D868: .word 0x00001658
_0222D86C: .word 0x0000081C
_0222D870: .word MOD12_022449C8
_0222D874: .word MOD12_0224499C
_0222D878: .word 0x00100010
_0222D87C: .word MOD12_022449B0
_0222D880: .word 0x00000123
_0222D884: .word MOD12_0222DB18
_0222D888: .word 0x0000EA60
_0222D88C: .word 0x00000824
_0222D890: .word 0x0000046F
_0222D894: .word 0x00000171
_0222D898: .word MOD12_0222DAE4

	thumb_func_start MOD12_0222D89C
MOD12_0222D89C: ; 0x0222D89C
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_02082878
	ldr r0, [r5]
	cmp r0, #0
	beq _0222D8BE
	cmp r0, #1
	beq _0222D8CC
	cmp r0, #2
	beq _0222D986
	b _0222D994
_0222D8BE:
	bl FUN_0200E308
	cmp r0, #1
	bne _0222D994
	mov r0, #1
	str r0, [r5]
	b _0222D994
_0222D8CC:
	ldr r0, [r4]
	bl FUN_020828BC
	cmp r0, #1
	bne _0222D93E
	ldr r2, _0222D99C ; =0x00000822
	ldr r1, _0222D9A0 ; =0x00001648
	ldrh r2, [r4, r2]
	add r0, r4, #0
	add r1, r4, r1
	lsl r3, r2, #2
	ldr r2, _0222D9A4 ; =MOD12_02244A10
	ldr r2, [r2, r3]
	blx r2
	sub r1, r0, #1
	cmp r1, #1
	bhi _0222D910
	cmp r0, #1
	bne _0222D8FA
	ldr r0, _0222D99C ; =0x00000822
	ldrh r1, [r4, r0]
	add r1, r1, #1
	b _0222D900
_0222D8FA:
	ldr r0, _0222D9A8 ; =0x0000164A
	ldrh r1, [r4, r0]
	ldr r0, _0222D99C ; =0x00000822
_0222D900:
	strh r1, [r4, r0]
	ldr r0, _0222D9A0 ; =0x00001648
	mov r1, #0
	add r0, r4, r0
	mov r2, #8
	bl MI_CpuFill8
	b _0222D93E
_0222D910:
	cmp r0, #3
	bne _0222D93E
	mov r0, #2
	str r0, [r5]
	ldr r0, _0222D9A0 ; =0x00001648
	mov r1, #0
	add r0, r4, r0
	mov r2, #8
	bl MI_CpuFill8
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x15
	mov r1, #0x20
	str r0, [sp, #8]
	mov r0, #2
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	b _0222D994
_0222D93E:
	mov r0, #0xc3
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD12_022410A0
	mov r0, #0xc3
	lsl r0, r0, #4
	add r0, r4, r0
	add r1, r4, #0
	bl MOD12_02241114
	ldr r0, _0222D9AC ; =0x00001650
	ldrb r1, [r4, r0]
	cmp r1, #1
	bne _0222D994
	mov r1, #2
	sub r0, #8
	str r1, [r5]
	add r0, r4, r0
	mov r1, #0
	mov r2, #8
	bl MI_CpuFill8
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x15
	mov r1, #0x20
	str r0, [sp, #8]
	mov r0, #2
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	b _0222D994
_0222D986:
	bl FUN_0200E308
	cmp r0, #1
	bne _0222D994
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_0222D994:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0222D99C: .word 0x00000822
_0222D9A0: .word 0x00001648
_0222D9A4: .word MOD12_02244A10
_0222D9A8: .word 0x0000164A
_0222D9AC: .word 0x00001650

	thumb_func_start MOD12_0222D9B0
MOD12_0222D9B0: ; 0x0222D9B0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	bl FUN_02012EAC
	ldr r0, [r4, #0x2c]
	bl MOD08_02212024
	add r0, r4, #0
	bl MOD12_0222DDC4
	add r0, r4, #0
	bl MOD12_0222DEEC
	add r0, r4, #0
	bl MOD12_0222E0F4
	add r0, r4, #0
	bl MOD12_0222E0FC
	add r0, r4, #0
	add r0, #0x34
	bl FUN_02019178
	mov r0, #1
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #0x30]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #0x30]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #0x30]
	bl MOD12_022319FC
	ldr r0, _0222DAD8 ; =0x0000081C
	ldr r0, [r4, r0]
	bl MOD12_02231AE8
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x28]
	bl FUN_0200C398
	ldr r0, [r4, #0x24]
	bl FUN_0200BD04
	bl FUN_0201C29C
	add r0, r4, #0
	add r0, #0xc
	bl MOD12_02233848
	ldr r0, [r4, #0x10]
	bl FUN_020072E8
	mov r0, #2
	bl FUN_02002CF8
	ldr r0, [r4, #0x60]
	bl FUN_020117BC
	ldr r0, [r4, #0x5c]
	mov r1, #0
	bl FUN_02003038
	ldr r0, [r4, #0x5c]
	mov r1, #1
	bl FUN_02003038
	ldr r0, [r4, #0x5c]
	mov r1, #2
	bl FUN_02003038
	ldr r0, [r4, #0x5c]
	mov r1, #3
	bl FUN_02003038
	ldr r0, [r4, #0x5c]
	bl FUN_02002FEC
	ldr r0, [r4, #0x58]
	bl String_dtor
	ldr r0, [r4, #0x54]
	bl ScrStrBufs_delete
	ldr r0, [r4, #0x44]
	bl DestroyMsgData
	ldr r0, [r4, #0x48]
	bl DestroyMsgData
	ldr r0, [r4, #0x4c]
	bl DestroyMsgData
	ldr r0, [r4, #0x50]
	bl DestroyMsgData
	ldr r0, [r4, #0x30]
	bl FreeToHeap
	ldr r0, [r4, #4]
	bl FUN_0200CAB4
	ldr r0, [r4, #8]
	bl MOD12_02231378
	bl FUN_0201CD04
	add r0, r5, #0
	bl OverlayManager_FreeData
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	mov r0, #0x15
	bl FUN_020168D0
	bl FUN_02083404
	bl FUN_02033ED0
	ldr r0, _0222DADC ; =SDK_OVERLAY_MODULE_08_ID
	bl UnloadOverlayByID
	ldr r0, _0222DAE0 ; =SDK_OVERLAY_MODULE_17_ID
	bl UnloadOverlayByID
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_0222DAD8: .word 0x0000081C
_0222DADC: .word SDK_OVERLAY_MODULE_08_ID
_0222DAE0: .word SDK_OVERLAY_MODULE_17_ID

	thumb_func_start MOD12_0222DAE4
MOD12_0222DAE4: ; 0x0222DAE4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	bl FUN_020081C4
	bl FUN_0201C30C
	bl FUN_0200BC30
	ldr r0, [r4, #0x5c]
	bl FUN_0200372C
	ldr r0, [r4, #0x30]
	bl FUN_0201AB60
	ldr r3, _0222DB10 ; =0x027E0000
	ldr r1, _0222DB14 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	.align 2, 0
_0222DB10: .word 0x027E0000
_0222DB14: .word 0x00003FF8

	thumb_func_start MOD12_0222DB18
MOD12_0222DB18: ; 0x0222DB18
	push {r4, lr}
	ldr r0, _0222DB48 ; =0x00000824
	add r4, r1, #0
	ldrb r0, [r4, r0]
	cmp r0, #1
	bne _0222DB3E
	ldr r0, [r4, #0x10]
	bl FUN_02006ED4
	bl MOD08_02215A44
	ldr r0, [r4, #0x28]
	bl FUN_0200BC1C
	bl FUN_0200BC38
	ldr r0, _0222DB4C ; =0x04000540
	mov r1, #1
	str r1, [r0]
_0222DB3E:
	ldr r1, [r4, #0x30]
	mov r0, #0x15
	bl FUN_020335F0
	pop {r4, pc}
	.align 2, 0
_0222DB48: .word 0x00000824
_0222DB4C: .word 0x04000540

	thumb_func_start MOD12_0222DB50
MOD12_0222DB50: ; 0x0222DB50
	push {r4, r5, lr}
	sub sp, #0x8c
	add r4, r0, #0
	bl GX_DisableEngineALayers
	ldr r5, _0222DC70 ; =MOD12_022449E8
	add r3, sp, #0x10
	mov r2, #5
_0222DB60:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222DB60
	add r0, sp, #0x10
	bl GX_SetBanks
	mov r1, #6
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x18
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x62
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	mov r1, #0x19
	mov r2, #1
	mov r0, #0
	lsl r1, r1, #0x16
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x66
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	ldr r5, _0222DC74 ; =MOD12_0224498C
	add r3, sp, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _0222DC78 ; =MOD12_02244A50
	add r3, sp, #0x38
	mov r2, #0xa
_0222DBC0:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222DBC0
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	add r2, sp, #0x38
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	mov r2, #0
	add r0, r4, #0
	mov r1, #1
	add r3, r2, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #1
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #2
	add r2, sp, #0x54
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #2
	bl FUN_02018744
	mov r2, #0
	add r0, r4, #0
	mov r1, #2
	add r3, r2, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #2
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #3
	add r2, sp, #0x70
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #3
	bl FUN_02018744
	mov r2, #0
	add r0, r4, #0
	mov r1, #3
	add r3, r2, #0
	bl FUN_020179E0
	mov r1, #3
	add r0, r4, #0
	add r2, r1, #0
	mov r3, #0
	bl FUN_020179E0
	ldr r1, _0222DC7C ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #2
	orr r0, r2
	strh r0, [r1]
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	add r0, r4, #0
	bl MOD12_022319A4
	add sp, #0x8c
	pop {r4, r5, pc}
	.align 2, 0
_0222DC70: .word MOD12_022449E8
_0222DC74: .word MOD12_0224498C
_0222DC78: .word MOD12_02244A50
_0222DC7C: .word 0x04000008

	thumb_func_start MOD12_0222DC80
MOD12_0222DC80: ; 0x0222DC80
	push {lr}
	sub sp, #0x14
	add r1, r0, #0
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x14
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #3
	lsl r0, r0, #8
	str r0, [sp, #0x10]
	ldr r0, [r1, #0x30]
	add r1, #0x34
	mov r2, #1
	mov r3, #0xb
	bl FUN_02019064
	add sp, #0x14
	pop {pc}

	thumb_func_start MOD12_0222DCAC
MOD12_0222DCAC: ; 0x0222DCAC
	push {r3, r4, r5, lr}
	ldr r3, _0222DCE4 ; =UNK_021064B8
	mov r0, #2
	mov r1, #0
	ldr r3, [r3]
	lsl r0, r0, #0xe
	add r2, r1, #0
	blx r3
	ldr r3, _0222DCE8 ; =UNK_021064C0
	mov r1, #0
	add r4, r0, #0
	ldr r3, [r3]
	mov r0, #0x80
	add r2, r1, #0
	blx r3
	add r5, r0, #0
	cmp r4, #0
	bne _0222DCD4
	bl ErrorHandling
_0222DCD4:
	cmp r5, #0
	bne _0222DCDC
	bl ErrorHandling
_0222DCDC:
	bl FUN_02012CC8
	pop {r3, r4, r5, pc}
	nop
_0222DCE4: .word UNK_021064B8
_0222DCE8: .word UNK_021064C0

	thumb_func_start MOD12_0222DCEC
MOD12_0222DCEC: ; 0x0222DCEC
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	bne _0222DCFA
	bl ErrorHandling
_0222DCFA:
	ldr r1, _0222DD1C ; =0x00000172
	mov r0, #0
	add r2, r1, #0
	add r2, #0xbf
_0222DD02:
	ldr r3, [r4]
	add r3, r3, r0
	ldrb r5, [r3, r1]
	add r3, r4, r0
	add r0, r0, #1
	strb r5, [r3, r2]
	cmp r0, #4
	blt _0222DD02
	add r0, r4, #0
	bl MOD12_02235D7C
	pop {r3, r4, r5, pc}
	nop
_0222DD1C: .word 0x00000172

	thumb_func_start MOD12_0222DD20
MOD12_0222DD20: ; 0x0222DD20
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0
	mov r0, #0x2e
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #6
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, _0222DDB8 ; =0x000080E9
	mov r1, #2
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x5c]
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x28]
	bl FUN_0200C0DC
	mov r0, #0x2e
	str r0, [sp]
	mov r0, #9
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, _0222DDBC ; =0x000080ED
	mov r1, #2
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x5c]
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x28]
	bl FUN_0200C0DC
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x28]
	bl MOD12_02235194
	add r0, r4, #0
	bl MOD12_022350F8
	add r0, r4, #0
	ldr r1, [r4]
	add r0, #0xc
	bl MOD12_02233A8C
	add r0, r4, #0
	ldr r2, [r4]
	ldr r1, _0222DDC0 ; =0x0000011E
	add r0, #0xc
	ldrb r1, [r2, r1]
	bl MOD12_02233EEC
	ldr r0, [r4, #0x5c]
	ldr r1, [r4, #0x24]
	ldr r2, [r4, #0x28]
	bl MOD12_02233B04
	add r0, r4, #0
	add r0, #0xc
	bl MOD12_02233B7C
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x28]
	bl MOD12_02233FAC
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x28]
	bl MOD12_022342A8
	add sp, #0x18
	pop {r4, pc}
	nop
_0222DDB8: .word 0x000080E9
_0222DDBC: .word 0x000080ED
_0222DDC0: .word 0x0000011E

	thumb_func_start MOD12_0222DDC4
MOD12_0222DDC4: ; 0x0222DDC4
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xc
	bl MOD12_02233F78
	add r0, r4, #0
	add r0, #0xc
	bl MOD12_02233AD4
	add r0, r4, #0
	bl MOD12_02235114
	add r0, r4, #0
	add r0, #0xc
	bl MOD12_0223524C
	ldr r0, [r4, #0x28]
	bl MOD12_022351E0
	ldr r0, [r4, #0x28]
	ldr r1, _0222DE28 ; =0x000080E9
	bl FUN_0200C368
	ldr r0, [r4, #0x28]
	ldr r1, _0222DE2C ; =0x000080ED
	bl FUN_0200C368
	add r0, r4, #0
	add r0, #0xc
	bl MOD12_02233BBC
	ldr r0, [r4, #0x28]
	bl MOD12_02233B58
	ldr r0, [r4, #0x28]
	bl MOD12_02233FF8
	add r0, r4, #0
	add r0, #0xc
	bl MOD12_02234044
	ldr r0, [r4, #0x28]
	bl MOD12_02234334
	add r4, #0xc
	add r0, r4, #0
	bl MOD12_0223439C
	pop {r4, pc}
	nop
_0222DE28: .word 0x000080E9
_0222DE2C: .word 0x000080ED

	thumb_func_start MOD12_0222DE30
MOD12_0222DE30: ; 0x0222DE30
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	mov r0, #0x2e
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r1, #3
	str r1, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _0222DED8 ; =0x000080EF
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x5c]
	ldr r2, [r5, #0x24]
	ldr r3, [r5, #0x28]
	bl FUN_0200C0DC
	mov r0, #0x2e
	str r0, [sp]
	mov r0, #9
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _0222DEDC ; =0x000080F0
	mov r1, #3
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x5c]
	ldr r2, [r5, #0x24]
	ldr r3, [r5, #0x28]
	bl FUN_0200C0DC
	ldr r0, [r5, #0x24]
	ldr r1, [r5, #0x28]
	bl MOD12_022334A4
	ldr r0, [r5, #0x24]
	ldr r1, [r5, #0x28]
	bl MOD12_022333F8
	ldr r2, _0222DEE0 ; =0x000080F4
	ldr r0, [r5, #0x24]
	ldr r1, [r5, #0x28]
	add r3, r2, #0
	bl MOD12_02240E34
	ldr r7, _0222DEE4 ; =0x000080F6
	ldr r6, _0222DEE8 ; =0x00000123
	mov r4, #0
_0222DE9E:
	ldr r1, [r5]
	mov r2, #0
	ldrb r0, [r1, r6]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, r4, #0
	add r1, #0x36
	bl GetMonData
	cmp r0, #0
	beq _0222DEBE
	mov r1, #0xb
	bl GetWazaAttr
	add r3, r0, #0
	b _0222DEC0
_0222DEBE:
	mov r3, #0
_0222DEC0:
	add r0, r4, r7
	str r0, [sp]
	ldr r0, [r5, #0x24]
	ldr r1, [r5, #0x28]
	mov r2, #2
	bl MOD12_02240E00
	add r4, r4, #1
	cmp r4, #4
	blt _0222DE9E
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222DED8: .word 0x000080EF
_0222DEDC: .word 0x000080F0
_0222DEE0: .word 0x000080F4
_0222DEE4: .word 0x000080F6
_0222DEE8: .word 0x00000123

	thumb_func_start MOD12_0222DEEC
MOD12_0222DEEC: ; 0x0222DEEC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x28]
	ldr r1, _0222DF24 ; =0x000080EF
	bl FUN_0200C368
	ldr r0, [r5, #0x28]
	bl MOD12_0223353C
	ldr r0, [r5, #0x28]
	bl MOD12_02233478
	ldr r1, _0222DF28 ; =0x000080F4
	ldr r0, [r5, #0x28]
	add r2, r1, #0
	bl MOD12_02240E84
	ldr r6, _0222DF2C ; =0x000080F6
	mov r4, #0
_0222DF12:
	ldr r0, [r5, #0x28]
	add r1, r4, r6
	bl MOD12_02240E7C
	add r4, r4, #1
	cmp r4, #4
	blt _0222DF12
	pop {r4, r5, r6, pc}
	nop
_0222DF24: .word 0x000080EF
_0222DF28: .word 0x000080F4
_0222DF2C: .word 0x000080F6

	thumb_func_start MOD12_0222DF30
MOD12_0222DF30: ; 0x0222DF30
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r4, r2, #0
	cmp r1, #0
	bne _0222DF9A
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xe
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x15
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x30]
	mov r0, #0x2d
	mov r1, #3
	mov r3, #2
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x15
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x30]
	mov r0, #0x2d
	mov r1, #5
	mov r3, #2
	bl FUN_020068C8
	mov r0, #1
	add r1, r0, #0
	bl FUN_020178BC
	mov r0, #2
	mov r1, #0
	bl FUN_020178BC
	add r0, r5, #0
	bl MOD12_022335B0
	cmp r4, #1
	bne _0222DFBE
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	add sp, #0x10
	pop {r3, r4, r5, pc}
_0222DF9A:
	mov r0, #2
	lsl r1, r0, #0xd
	mov r2, #0
	mov r3, #0x15
	bl FUN_02017F18
	ldr r0, [r5, #0x30]
	mov r1, #2
	bl FUN_02018744
	mov r0, #1
	mov r1, #0
	bl FUN_020178BC
	mov r0, #2
	mov r1, #1
	bl FUN_020178BC
_0222DFBE:
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_0222DFC4
MOD12_0222DFC4: ; 0x0222DFC4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	mov r0, #0x15
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x30]
	mov r0, #0x2d
	mov r3, #3
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x15
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x30]
	mov r0, #0x2d
	mov r1, #2
	mov r3, #3
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x15
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x30]
	mov r0, #0x2d
	mov r1, #3
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x15
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x30]
	mov r0, #0x2d
	mov r1, #4
	bl FUN_020068C8
	mov r1, #0
	add r0, r5, #0
	add r2, r1, #0
	bl MOD12_0222DF30
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5, #0x5c]
	mov r1, #0x2d
	mov r2, #0x1d
	mov r3, #0x15
	bl FUN_020030E8
	mov r0, #0x15
	mov r1, #0x20
	bl AllocFromHeap
	add r7, r0, #0
	mov r0, #0x15
	mov r1, #0x20
	bl AllocFromHeap
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x5c]
	mov r1, #0
	bl FUN_020031FC
	add r4, r0, #0
	ldr r0, [r5, #0x5c]
	mov r1, #0
	bl FUN_02003204
	str r0, [sp, #0x14]
	ldr r0, _0222E0EC ; =MOD12_022451D0
	add r1, r7, #0
	ldrb r0, [r0]
	mov r2, #0x20
	lsl r6, r0, #5
	add r0, r4, r6
	bl MIi_CpuCopy16
	ldr r1, [r5]
	ldr r0, _0222E0F0 ; =0x00000123
	mov r2, #0x20
	ldrb r1, [r1, r0]
	ldr r0, _0222E0EC ; =MOD12_022451D0
	ldrb r0, [r0, r1]
	ldr r1, [sp, #0x10]
	lsl r0, r0, #5
	add r0, r4, r0
	bl MIi_CpuCopy16
	ldr r2, [r5]
	ldr r1, _0222E0F0 ; =0x00000123
	add r0, r7, #0
	ldrb r2, [r2, r1]
	ldr r1, _0222E0EC ; =MOD12_022451D0
	ldrb r1, [r1, r2]
	mov r2, #0x20
	lsl r1, r1, #5
	add r1, r4, r1
	bl MIi_CpuCopy16
	ldr r0, [sp, #0x10]
	add r1, r4, r6
	mov r2, #0x20
	bl MIi_CpuCopy16
	ldr r2, [r5]
	ldr r1, _0222E0F0 ; =0x00000123
	add r0, r7, #0
	ldrb r2, [r2, r1]
	ldr r1, _0222E0EC ; =MOD12_022451D0
	ldrb r1, [r1, r2]
	lsl r2, r1, #5
	ldr r1, [sp, #0x14]
	add r1, r1, r2
	mov r2, #0x20
	bl MIi_CpuCopy16
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x10]
	add r1, r1, r6
	mov r2, #0x20
	bl MIi_CpuCopy16
	add r0, r7, #0
	bl FreeToHeap
	ldr r0, [sp, #0x10]
	bl FreeToHeap
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222E0EC: .word MOD12_022451D0
_0222E0F0: .word 0x00000123

	thumb_func_start MOD12_0222E0F4
MOD12_0222E0F4: ; 0x0222E0F4
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0222E0F8
MOD12_0222E0F8: ; 0x0222E0F8
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0222E0FC
MOD12_0222E0FC: ; 0x0222E0FC
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0222E100
MOD12_0222E100: ; 0x0222E100
	push {r4, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	bne _0222E128
	mov r0, #0xc3
	lsl r0, r0, #4
	add r0, r2, r0
	add r1, r2, #0
	mov r2, #2
	mov r3, #0
	bl MOD12_02241050
	cmp r0, #1
	bne _0222E148
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222E148
_0222E128:
	mov r0, #0xc3
	lsl r0, r0, #4
	ldr r3, [r2]
	ldr r4, _0222E14C ; =0x00000127
	add r0, r2, r0
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222E148
	mov r0, #1
	pop {r4, pc}
_0222E148:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_0222E14C: .word 0x00000127

	thumb_func_start MOD12_0222E150
MOD12_0222E150: ; 0x0222E150
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	bl FUN_020832EC
	cmp r0, #0
	bne _0222E164
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222E164:
	ldrh r0, [r4]
	cmp r0, #0
	bne _0222E196
	ldr r3, _0222E1BC ; =0x0000040C
	mov r1, #0
	strb r1, [r5, r3]
	add r0, r3, #2
	strb r1, [r5, r0]
	add r0, r3, #3
	strb r1, [r5, r0]
	mov r0, #0xc3
	lsl r0, r0, #4
	sub r3, #0xe4
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #0x14
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _0222E1B6
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222E1B6
_0222E196:
	ldr r4, _0222E1C0 ; =0x00000127
	ldr r3, [r5]
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	mov r0, #0xc3
	lsl r0, r0, #4
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	add r0, r5, r0
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222E1B6
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222E1B6:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_0222E1BC: .word 0x0000040C
_0222E1C0: .word 0x00000127

	thumb_func_start MOD12_0222E1C4
MOD12_0222E1C4: ; 0x0222E1C4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	bne _0222E218
	ldr r0, [r5]
	bl FUN_020832EC
	cmp r0, #1
	bne _0222E1E2
	ldr r0, _0222E23C ; =0x0000040C
	mov r1, #0x2d
	strb r1, [r5, r0]
	b _0222E1F0
_0222E1E2:
	ldr r1, [r5]
	ldr r0, _0222E240 ; =0x0000011F
	ldrb r0, [r1, r0]
	bl MOD12_02235A98
	ldr r1, _0222E23C ; =0x0000040C
	strb r0, [r5, r1]
_0222E1F0:
	ldr r3, _0222E244 ; =0x0000040E
	mov r1, #0
	strb r1, [r5, r3]
	add r0, r3, #1
	strb r1, [r5, r0]
	mov r0, #0xc3
	lsl r0, r0, #4
	sub r3, #0xe6
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #0x14
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _0222E238
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222E238
_0222E218:
	ldr r4, _0222E248 ; =0x00000127
	ldr r3, [r5]
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	mov r0, #0xc3
	lsl r0, r0, #4
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	add r0, r5, r0
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222E238
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222E238:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222E23C: .word 0x0000040C
_0222E240: .word 0x0000011F
_0222E244: .word 0x0000040E
_0222E248: .word 0x00000127

	thumb_func_start MOD12_0222E24C
MOD12_0222E24C: ; 0x0222E24C
	mov r0, #1
	bx lr

	thumb_func_start MOD12_0222E250
MOD12_0222E250: ; 0x0222E250
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r1, [sp]
	ldrh r1, [r1]
	add r4, r0, #0
	cmp r1, #0
	beq _0222E268
	cmp r1, #1
	beq _0222E288
	cmp r1, #2
	beq _0222E2B0
	b _0222E2F0
_0222E268:
	mov r0, #0xc3
	lsl r0, r0, #4
	add r0, r4, r0
	add r1, r4, #0
	mov r2, #8
	mov r3, #0
	bl MOD12_02241050
	cmp r0, #1
	bne _0222E300
	ldr r0, [sp]
	ldrh r0, [r0]
	add r1, r0, #1
	ldr r0, [sp]
	strh r1, [r0]
	b _0222E300
_0222E288:
	mov r0, #0xc3
	lsl r0, r0, #4
	ldr r3, [r4]
	add r0, r4, r0
	ldr r4, _0222E308 ; =0x00000127
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222E300
	ldr r0, [sp]
	ldrh r0, [r0]
	add r1, r0, #1
	ldr r0, [sp]
	strh r1, [r0]
	b _0222E300
_0222E2B0:
	add r1, sp, #4
	bl MOD12_0223900C
	ldr r1, [r4]
	ldr r0, _0222E308 ; =0x00000127
	ldrb r0, [r1, r0]
	cmp r0, #4
	bge _0222E2E4
	lsl r2, r0, #1
	add r3, sp, #4
	add r1, r3, r2
	ldr r7, _0222E30C ; =0x0000023E
	add r2, r4, r2
	add r3, r3, r0
_0222E2CC:
	ldrh r6, [r1]
	ldr r5, _0222E310 ; =0x00000236
	add r1, r1, #2
	strh r6, [r2, r5]
	ldrb r6, [r3, #8]
	add r5, r4, r0
	add r0, r0, #1
	strb r6, [r5, r7]
	add r2, r2, #2
	add r3, r3, #1
	cmp r0, #4
	blt _0222E2CC
_0222E2E4:
	ldr r0, [sp]
	ldrh r0, [r0]
	add r1, r0, #1
	ldr r0, [sp]
	strh r1, [r0]
	b _0222E300
_0222E2F0:
	mov r1, #0xce
	lsl r1, r1, #2
	add r1, r4, r1
	bl MOD12_0223808C
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0222E300:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E308: .word 0x00000127
_0222E30C: .word 0x0000023E
_0222E310: .word 0x00000236

	thumb_func_start MOD12_0222E314
MOD12_0222E314: ; 0x0222E314
	push {r3, r4, r5, r6, r7, lr}
	ldr r2, _0222E394 ; =0x00000235
	add r4, r0, #0
	ldrb r0, [r4, r2]
	add r1, r4, r0
	sub r0, r2, #4
	ldrb r0, [r1, r0]
	add r1, r2, #0
	add r1, #0xf3
	strb r0, [r4, r1]
	str r0, [sp]
	add r0, r2, #0
	ldrb r1, [r4, r2]
	add r0, #0xf4
	strb r1, [r4, r0]
	ldr r0, [sp]
	add r1, r4, r0
	add r0, r2, #0
	add r0, #9
	ldrb r3, [r1, r0]
	add r0, r2, #0
	add r0, #0xf5
	strb r3, [r4, r0]
	add r3, r2, #0
	mov r0, #0
	add r3, #0xf6
	strb r0, [r4, r3]
	ldrb r2, [r4, r2]
	cmp r2, #0
	ble _0222E374
	ldr r7, _0222E398 ; =0x0000023E
	mov r5, #1
	add r3, r7, #0
_0222E356:
	ldr r2, _0222E39C ; =0x00000231
	add r6, r4, r0
	ldrb r2, [r6, r2]
	add r2, r4, r2
	ldrb r6, [r2, r7]
	ldrb r2, [r1, r3]
	cmp r6, r2
	bne _0222E36A
	ldr r2, _0222E3A0 ; =0x0000032B
	strb r5, [r4, r2]
_0222E36A:
	ldr r2, _0222E394 ; =0x00000235
	add r0, r0, #1
	ldrb r2, [r4, r2]
	cmp r0, r2
	blt _0222E356
_0222E374:
	mov r1, #1
	lsl r1, r1, #0xa
	ldr r2, [sp]
	add r0, r4, #0
	add r1, r4, r1
	bl MOD12_02235274
	ldr r1, _0222E3A4 ; =0x00000406
	ldr r2, [sp]
	add r0, r4, #0
	add r1, r4, r1
	bl MOD12_02235274
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E394: .word 0x00000235
_0222E398: .word 0x0000023E
_0222E39C: .word 0x00000231
_0222E3A0: .word 0x0000032B
_0222E3A4: .word 0x00000406

	thumb_func_start MOD12_0222E3A8
MOD12_0222E3A8: ; 0x0222E3A8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	bne _0222E3D4
	mov r0, #0xc3
	mov r3, #0xca
	lsl r0, r0, #4
	lsl r3, r3, #2
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #4
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _0222E3F4
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222E3F4
_0222E3D4:
	ldr r4, _0222E3F8 ; =0x00000127
	ldr r3, [r5]
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	mov r0, #0xc3
	lsl r0, r0, #4
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	add r0, r5, r0
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222E3F4
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222E3F4:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222E3F8: .word 0x00000127

	thumb_func_start MOD12_0222E3FC
MOD12_0222E3FC: ; 0x0222E3FC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldrh r0, [r5]
	cmp r0, #0
	bne _0222E42C
	ldr r3, _0222E458 ; =0x0000040C
	mov r0, #0
	strb r0, [r4, r3]
	mov r0, #0xc3
	lsl r0, r0, #4
	sub r3, #0xe4
	add r0, r4, r0
	add r1, r4, #0
	mov r2, #6
	add r3, r4, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _0222E452
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _0222E452
_0222E42C:
	ldr r5, _0222E45C ; =0x00000127
	ldr r3, [r4]
	sub r2, r5, #4
	ldrb r1, [r3, r5]
	mov r0, #0xc3
	lsl r0, r0, #4
	sub r5, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r5]
	add r0, r4, r0
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222E452
	ldr r0, _0222E458 ; =0x0000040C
	mov r1, #0
	strb r1, [r4, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222E452:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_0222E458: .word 0x0000040C
_0222E45C: .word 0x00000127

	thumb_func_start MOD12_0222E460
MOD12_0222E460: ; 0x0222E460
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldrh r0, [r5]
	cmp r0, #0
	beq _0222E472
	cmp r0, #1
	beq _0222E4A2
	b _0222E4C2
_0222E472:
	ldr r0, _0222E4F0 ; =0x0000040C
	mov r1, #4
	strb r1, [r4, r0]
	add r1, r0, #0
	sub r1, #0xe1
	ldrb r1, [r4, r1]
	cmp r1, #1
	bne _0222E486
	mov r1, #5
	b _0222E488
_0222E486:
	mov r1, #0
_0222E488:
	mov r2, #0xce
	add r0, r0, #1
	strb r1, [r4, r0]
	lsl r2, r2, #2
	add r1, r4, r2
	sub r2, #0x10
	ldrb r2, [r4, r2]
	add r0, r4, #0
	bl MOD12_02238224
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
_0222E4A2:
	mov r0, #0xc3
	mov r3, #0xca
	lsl r0, r0, #4
	lsl r3, r3, #2
	add r0, r4, r0
	add r1, r4, #0
	mov r2, #7
	add r3, r4, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _0222E4EC
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _0222E4EC
_0222E4C2:
	ldr r5, _0222E4F4 ; =0x00000127
	ldr r3, [r4]
	sub r2, r5, #4
	ldrb r1, [r3, r5]
	mov r0, #0xc3
	lsl r0, r0, #4
	sub r5, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r5]
	add r0, r4, r0
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222E4EC
	ldr r0, _0222E4F0 ; =0x0000040C
	mov r1, #0
	strb r1, [r4, r0]
	add r0, r0, #1
	strb r1, [r4, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222E4EC:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222E4F0: .word 0x0000040C
_0222E4F4: .word 0x00000127

	thumb_func_start MOD12_0222E4F8
MOD12_0222E4F8: ; 0x0222E4F8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrh r1, [r4]
	add r5, r0, #0
	cmp r1, #0xc
	bls _0222E506
	b _0222E6B6
_0222E506:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222E512: ; jump table
	.short _0222E52C - _0222E512 - 2 ; case 0
	.short _0222E542 - _0222E512 - 2 ; case 1
	.short _0222E556 - _0222E512 - 2 ; case 2
	.short _0222E576 - _0222E512 - 2 ; case 3
	.short _0222E59C - _0222E512 - 2 ; case 4
	.short _0222E5B6 - _0222E512 - 2 ; case 5
	.short _0222E5D6 - _0222E512 - 2 ; case 6
	.short _0222E5FA - _0222E512 - 2 ; case 7
	.short _0222E614 - _0222E512 - 2 ; case 8
	.short _0222E634 - _0222E512 - 2 ; case 9
	.short _0222E658 - _0222E512 - 2 ; case 10
	.short _0222E672 - _0222E512 - 2 ; case 11
	.short _0222E692 - _0222E512 - 2 ; case 12
_0222E52C:
	mov r2, #0xce
	lsl r2, r2, #2
	add r1, r5, r2
	sub r2, #0x10
	ldrb r2, [r5, r2]
	bl MOD12_022380FC
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222E6CA
_0222E542:
	mov r2, #0xce
	lsl r2, r2, #2
	add r1, r5, r2
	sub r2, #0x10
	ldrb r2, [r5, r2]
	bl MOD12_02238280
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
_0222E556:
	mov r0, #0xc3
	mov r3, #0xca
	lsl r0, r0, #4
	lsl r3, r3, #2
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #0xa
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _0222E592
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222E6CA
_0222E576:
	mov r0, #0xc3
	lsl r0, r0, #4
	ldr r3, [r5]
	add r0, r5, r0
	ldr r5, _0222E6D0 ; =0x00000127
	sub r2, r5, #4
	ldrb r1, [r3, r5]
	sub r5, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r5]
	bl MOD12_022411F4
	cmp r0, #1
	beq _0222E594
_0222E592:
	b _0222E6CA
_0222E594:
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222E6CA
_0222E59C:
	mov r3, #0xce
	lsl r3, r3, #2
	add r2, r3, #0
	add r1, r5, r3
	sub r2, #0x10
	sub r3, #0xf
	ldrb r2, [r5, r2]
	ldrb r3, [r5, r3]
	bl MOD12_022382A8
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
_0222E5B6:
	mov r0, #0xc3
	mov r3, #0xca
	lsl r0, r0, #4
	lsl r3, r3, #2
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #0xb
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _0222E6CA
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222E6CA
_0222E5D6:
	mov r0, #0xc3
	lsl r0, r0, #4
	ldr r3, [r5]
	add r0, r5, r0
	ldr r5, _0222E6D0 ; =0x00000127
	sub r2, r5, #4
	ldrb r1, [r3, r5]
	sub r5, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r5]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222E6CA
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222E6CA
_0222E5FA:
	mov r3, #0xce
	lsl r3, r3, #2
	add r2, r3, #0
	add r1, r5, r3
	sub r2, #0x10
	sub r3, #0xf
	ldrb r2, [r5, r2]
	ldrb r3, [r5, r3]
	bl MOD12_02238370
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
_0222E614:
	mov r0, #0xc3
	mov r3, #0xca
	lsl r0, r0, #4
	lsl r3, r3, #2
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #0xc
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _0222E6CA
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222E6CA
_0222E634:
	mov r0, #0xc3
	lsl r0, r0, #4
	ldr r3, [r5]
	add r0, r5, r0
	ldr r5, _0222E6D0 ; =0x00000127
	sub r2, r5, #4
	ldrb r1, [r3, r5]
	sub r5, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r5]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222E6CA
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222E6CA
_0222E658:
	mov r3, #0xce
	lsl r3, r3, #2
	add r2, r3, #0
	sub r2, #0x10
	ldrb r2, [r5, r2]
	add r1, r5, r3
	add r3, #0xc8
	add r3, r5, r3
	bl MOD12_0223850C
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
_0222E672:
	mov r0, #0xc3
	mov r3, #0xca
	lsl r0, r0, #4
	lsl r3, r3, #2
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #0xd
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _0222E6CA
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222E6CA
_0222E692:
	mov r0, #0xc3
	lsl r0, r0, #4
	ldr r3, [r5]
	add r0, r5, r0
	ldr r5, _0222E6D0 ; =0x00000127
	sub r2, r5, #4
	ldrb r1, [r3, r5]
	sub r5, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r5]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222E6CA
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222E6CA
_0222E6B6:
	mov r2, #0xce
	lsl r2, r2, #2
	add r1, r5, r2
	sub r2, #0x10
	ldrb r2, [r5, r2]
	add r0, r5, #0
	bl MOD12_02238160
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222E6CA:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_0222E6D0: .word 0x00000127

	thumb_func_start MOD12_0222E6D4
MOD12_0222E6D4: ; 0x0222E6D4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	bne _0222E700
	mov r0, #0xc3
	mov r3, #0xca
	lsl r0, r0, #4
	lsl r3, r3, #2
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #5
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _0222E720
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222E720
_0222E700:
	ldr r4, _0222E724 ; =0x00000127
	ldr r3, [r5]
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	mov r0, #0xc3
	lsl r0, r0, #4
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	add r0, r5, r0
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222E720
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222E720:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222E724: .word 0x00000127

	thumb_func_start MOD12_0222E728
MOD12_0222E728: ; 0x0222E728
	ldr r2, _0222E744 ; =0x00000235
	ldrb r3, [r0, r2]
	add r3, r3, #1
	strb r3, [r0, r2]
	ldrb r0, [r0, r2]
	cmp r0, #4
	blo _0222E73A
	mov r0, #1
	bx lr
_0222E73A:
	mov r0, #5
	strh r0, [r1, #2]
	mov r0, #2
	bx lr
	nop
_0222E744: .word 0x00000235

	thumb_func_start MOD12_0222E748
MOD12_0222E748: ; 0x0222E748
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	add r7, r1, #0
	ldrh r1, [r7]
	str r0, [sp]
	cmp r1, #0x18
	bls _0222E758
	b _0222EBFA
_0222E758:
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222E764: ; jump table
	.short _0222E796 - _0222E764 - 2 ; case 0
	.short _0222E79C - _0222E764 - 2 ; case 1
	.short _0222E7BA - _0222E764 - 2 ; case 2
	.short _0222E7E8 - _0222E764 - 2 ; case 3
	.short _0222E80C - _0222E764 - 2 ; case 4
	.short _0222E834 - _0222E764 - 2 ; case 5
	.short _0222E850 - _0222E764 - 2 ; case 6
	.short _0222E878 - _0222E764 - 2 ; case 7
	.short _0222E9CE - _0222E764 - 2 ; case 8
	.short _0222E9D6 - _0222E764 - 2 ; case 9
	.short _0222E9FA - _0222E764 - 2 ; case 10
	.short _0222EA2C - _0222E764 - 2 ; case 11
	.short _0222EA44 - _0222E764 - 2 ; case 12
	.short _0222EA50 - _0222E764 - 2 ; case 13
	.short _0222EA6E - _0222E764 - 2 ; case 14
	.short _0222EA9C - _0222E764 - 2 ; case 15
	.short _0222EAC0 - _0222E764 - 2 ; case 16
	.short _0222EB12 - _0222E764 - 2 ; case 17
	.short _0222EB2A - _0222E764 - 2 ; case 18
	.short _0222EB36 - _0222E764 - 2 ; case 19
	.short _0222EB48 - _0222E764 - 2 ; case 20
	.short _0222EB66 - _0222E764 - 2 ; case 21
	.short _0222EB94 - _0222E764 - 2 ; case 22
	.short _0222EBB8 - _0222E764 - 2 ; case 23
	.short _0222EBDE - _0222E764 - 2 ; case 24
_0222E796:
	add r0, r1, #1
	strh r0, [r7]
	b _0222EC00
_0222E79C:
	ldr r1, [r7, #4]
	ldr r0, [sp]
	ldr r2, _0222EAE4 ; =0x00000231
	add r0, r0, r1
	ldrb r3, [r0, r2]
	add r1, r2, #0
	ldr r0, [sp]
	add r1, #0xf7
	strb r3, [r0, r1]
	ldr r1, [r7, #4]
	add r2, #0xf8
	strb r1, [r0, r2]
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
_0222E7BA:
	mov r3, #0xce
	ldr r0, [sp]
	lsl r3, r3, #2
	add r4, r3, #0
	add r1, r0, #0
	add r1, r1, r3
	sub r4, #0x10
	add r2, r0, #0
	ldrb r2, [r2, r4]
	sub r3, #0xf
	add r4, r0, #0
	ldrb r3, [r4, r3]
	bl MOD12_022383EC
	cmp r0, #1
	bne _0222E7E2
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222E7E2:
	mov r0, #5
	strh r0, [r7]
	b _0222EC00
_0222E7E8:
	mov r1, #0xc3
	ldr r0, [sp]
	lsl r1, r1, #4
	add r0, r0, r1
	ldr r1, [sp]
	mov r4, #0xca
	lsl r4, r4, #2
	add r3, r1, #0
	mov r2, #0xe
	add r3, r3, r4
	bl MOD12_02241050
	cmp r0, #1
	bne _0222E82A
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222E80C:
	ldr r0, [sp]
	mov r1, #0xc3
	ldr r4, _0222EAE8 ; =0x00000127
	ldr r3, [r0]
	lsl r1, r1, #4
	add r0, r0, r1
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	beq _0222E82C
_0222E82A:
	b _0222EC00
_0222E82C:
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222E834:
	ldr r0, [r7, #4]
	add r0, r0, #1
	str r0, [r7, #4]
	cmp r0, #4
	blt _0222E84A
	mov r0, #0
	str r0, [r7, #4]
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222E84A:
	mov r0, #1
	strh r0, [r7]
	b _0222EC00
_0222E850:
	mov r6, #0xce
	lsl r6, r6, #2
	add r5, r6, #0
	mov r4, #0
	add r5, #0xc8
_0222E85A:
	ldr r0, [sp]
	add r2, r4, #0
	add r1, r0, #0
	add r3, r0, #0
	add r1, r1, r6
	add r3, r3, r5
	bl MOD12_02238660
	add r4, r4, #1
	cmp r4, #4
	blt _0222E85A
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222E878:
	mov r5, #0
	add r2, sp, #0x40
	add r3, sp, #0x34
	add r6, sp, #4
	mov r0, #4
_0222E882:
	mov r1, #0
	str r1, [r2]
	str r5, [r3]
	add r4, r6, #0
_0222E88A:
	add r1, r1, #1
	stmia r4!, {r0}
	cmp r1, #4
	blt _0222E88A
	add r5, r5, #1
	add r2, r2, #4
	add r3, r3, #4
	add r6, #0x10
	cmp r5, #3
	blt _0222E882
	mov r3, #0
	add r6, sp, #0x40
_0222E8A2:
	ldr r0, [sp]
	add r1, r0, r3
	ldr r0, _0222EAE4 ; =0x00000231
	ldrb r1, [r1, r0]
	ldr r0, [sp]
	add r2, r0, r1
	ldr r0, _0222EAEC ; =0x0000023E
	ldrb r0, [r2, r0]
	lsl r0, r0, #2
	ldr r4, [r6, r0]
	add r4, r4, #1
	str r4, [r6, r0]
	ldr r0, _0222EAEC ; =0x0000023E
	mov r4, #0
	ldrb r0, [r2, r0]
	lsl r2, r0, #4
	add r0, sp, #4
	add r5, r0, r2
	add r2, r5, #0
_0222E8C8:
	ldr r0, [r2]
	cmp r0, #4
	bne _0222E8D4
	lsl r0, r4, #2
	str r1, [r5, r0]
	b _0222E8DC
_0222E8D4:
	add r4, r4, #1
	add r2, r2, #4
	cmp r4, #4
	blt _0222E8C8
_0222E8DC:
	add r3, r3, #1
	cmp r3, #4
	blt _0222E8A2
	mov r6, #0
_0222E8E4:
	mov r2, #2
	cmp r6, #2
	bge _0222E910
	add r0, sp, #0x48
	add r1, sp, #0x3c
_0222E8EE:
	sub r3, r0, #4
	ldr r5, [r0]
	ldr r4, [r3]
	cmp r4, r5
	bge _0222E906
	str r4, [r0]
	str r5, [r3]
	sub r3, r1, #4
	ldr r5, [r1]
	ldr r4, [r3]
	str r4, [r1]
	str r5, [r3]
_0222E906:
	sub r2, r2, #1
	sub r0, r0, #4
	sub r1, r1, #4
	cmp r2, r6
	bgt _0222E8EE
_0222E910:
	add r6, r6, #1
	cmp r6, #2
	blt _0222E8E4
	ldr r0, [r7, #4]
	mov r2, #0x41
	lsl r0, r0, #2
	add r1, sp, #0x34
	ldr r3, [r1, r0]
	ldr r0, [sp]
	lsl r2, r2, #4
	strb r3, [r0, r2]
	mov r3, #0
	ldr r6, _0222EAF0 ; =0x00000411
	add r2, r3, #0
	add r5, sp, #4
_0222E92E:
	ldr r0, [r7, #4]
	ldr r4, [sp]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r4, r4, r3
	lsl r0, r0, #4
	add r0, r5, r0
	ldr r0, [r2, r0]
	add r3, r3, #1
	add r2, r2, #4
	strb r0, [r4, r6]
	cmp r3, #4
	blt _0222E92E
	ldr r0, [r7, #4]
	lsl r1, r0, #2
	add r0, sp, #0x40
	ldr r0, [r0, r1]
	cmp r0, #4
	bhi _0222E992
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222E960: ; jump table
	.short _0222E992 - _0222E960 - 2 ; case 0
	.short _0222E96A - _0222E960 - 2 ; case 1
	.short _0222E974 - _0222E960 - 2 ; case 2
	.short _0222E97E - _0222E960 - 2 ; case 3
	.short _0222E988 - _0222E960 - 2 ; case 4
_0222E96A:
	ldr r1, _0222EAF4 ; =0x0000040C
	ldr r0, [sp]
	mov r2, #0xa
	strb r2, [r0, r1]
	b _0222E99C
_0222E974:
	ldr r1, _0222EAF4 ; =0x0000040C
	ldr r0, [sp]
	mov r2, #7
	strb r2, [r0, r1]
	b _0222E99C
_0222E97E:
	ldr r1, _0222EAF4 ; =0x0000040C
	ldr r0, [sp]
	mov r2, #8
	strb r2, [r0, r1]
	b _0222E99C
_0222E988:
	ldr r1, _0222EAF4 ; =0x0000040C
	ldr r0, [sp]
	mov r2, #9
	strb r2, [r0, r1]
	b _0222E99C
_0222E992:
	mov r0, #0xc
	strh r0, [r7]
	add sp, #0x4c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0222E99C:
	ldr r2, _0222EAF8 ; =0x0000040D
	ldr r0, [sp]
	mov r1, #0
	add r3, r2, #0
	strb r1, [r0, r2]
	sub r3, #0xd
	add r1, r0, #0
	add r1, r1, r3
	sub r2, #0xe5
	add r3, r0, #0
	ldrb r2, [r3, r2]
	bl MOD12_02235274
	ldr r0, [sp]
	ldr r3, _0222EAFC ; =0x00000406
	add r1, r0, #0
	add r1, r1, r3
	sub r3, #0xde
	add r2, r0, #0
	ldrb r2, [r2, r3]
	bl MOD12_02235274
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
_0222E9CE:
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222E9D6:
	mov r1, #0xc3
	ldr r0, [sp]
	lsl r1, r1, #4
	add r0, r0, r1
	ldr r1, [sp]
	mov r4, #0xca
	lsl r4, r4, #2
	add r3, r1, #0
	mov r2, #0x10
	add r3, r3, r4
	bl MOD12_02241050
	cmp r0, #1
	bne _0222EADE
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222E9FA:
	ldr r0, [sp]
	mov r1, #0xc3
	ldr r4, _0222EAE8 ; =0x00000127
	ldr r3, [r0]
	lsl r1, r1, #4
	add r0, r0, r1
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222EADE
	ldr r1, _0222EAF4 ; =0x0000040C
	ldr r0, [sp]
	mov r2, #0
	strb r2, [r0, r1]
	add r1, r1, #1
	strb r2, [r0, r1]
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222EA2C:
	ldr r0, [r7, #4]
	add r0, r0, #1
	str r0, [r7, #4]
	cmp r0, #3
	bge _0222EA3C
	mov r0, #7
	strh r0, [r7]
	b _0222EC00
_0222EA3C:
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222EA44:
	mov r0, #0
	str r0, [r7, #4]
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222EA50:
	ldr r1, [r7, #4]
	ldr r0, [sp]
	ldr r2, _0222EAE4 ; =0x00000231
	add r0, r0, r1
	ldrb r3, [r0, r2]
	add r1, r2, #0
	ldr r0, [sp]
	add r1, #0xf7
	strb r3, [r0, r1]
	ldr r1, [r7, #4]
	add r2, #0xf8
	strb r1, [r0, r2]
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
_0222EA6E:
	mov r3, #0xce
	ldr r0, [sp]
	lsl r3, r3, #2
	add r4, r3, #0
	add r1, r0, #0
	add r1, r1, r3
	sub r4, #0x10
	add r2, r0, #0
	ldrb r2, [r2, r4]
	sub r3, #0xf
	add r4, r0, #0
	ldrb r3, [r4, r3]
	bl MOD12_0223844C
	cmp r0, #0
	bne _0222EA94
	mov r0, #0x11
	strh r0, [r7]
	b _0222EC00
_0222EA94:
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222EA9C:
	mov r1, #0xc3
	ldr r0, [sp]
	lsl r1, r1, #4
	add r0, r0, r1
	ldr r1, [sp]
	mov r4, #0xca
	lsl r4, r4, #2
	add r3, r1, #0
	mov r2, #0x11
	add r3, r3, r4
	bl MOD12_02241050
	cmp r0, #1
	bne _0222EADE
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222EAC0:
	ldr r0, [sp]
	mov r1, #0xc3
	ldr r4, _0222EAE8 ; =0x00000127
	ldr r3, [r0]
	lsl r1, r1, #4
	add r0, r0, r1
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	beq _0222EAE0
_0222EADE:
	b _0222EC00
_0222EAE0:
	ldr r1, _0222EAF4 ; =0x0000040C
	b _0222EB00
	.align 2, 0
_0222EAE4: .word 0x00000231
_0222EAE8: .word 0x00000127
_0222EAEC: .word 0x0000023E
_0222EAF0: .word 0x00000411
_0222EAF4: .word 0x0000040C
_0222EAF8: .word 0x0000040D
_0222EAFC: .word 0x00000406
_0222EB00:
	ldr r0, [sp]
	mov r2, #0
	strb r2, [r0, r1]
	add r1, r1, #1
	strb r2, [r0, r1]
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222EB12:
	ldr r0, [r7, #4]
	add r0, r0, #1
	str r0, [r7, #4]
	cmp r0, #4
	bge _0222EB22
	mov r0, #0xd
	strh r0, [r7]
	b _0222EC00
_0222EB22:
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222EB2A:
	mov r0, #0
	str r0, [r7, #4]
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222EB36:
	mov r1, #0xce
	ldr r0, [sp]
	lsl r1, r1, #2
	add r0, r0, r1
	bl MOD12_02238210
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
_0222EB48:
	ldr r1, [r7, #4]
	ldr r0, [sp]
	ldr r2, _0222EC08 ; =0x00000231
	add r0, r0, r1
	ldrb r3, [r0, r2]
	add r1, r2, #0
	ldr r0, [sp]
	add r1, #0xf7
	strb r3, [r0, r1]
	ldr r1, [r7, #4]
	add r2, #0xf8
	strb r1, [r0, r2]
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
_0222EB66:
	mov r3, #0xce
	ldr r0, [sp]
	lsl r3, r3, #2
	add r4, r3, #0
	add r1, r0, #0
	add r1, r1, r3
	sub r4, #0x10
	add r2, r0, #0
	ldrb r2, [r2, r4]
	sub r3, #0xf
	add r4, r0, #0
	ldrb r3, [r4, r3]
	bl MOD12_022384AC
	cmp r0, #1
	bne _0222EB8E
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222EB8E:
	mov r0, #0x18
	strh r0, [r7]
	b _0222EC00
_0222EB94:
	mov r1, #0xc3
	ldr r0, [sp]
	lsl r1, r1, #4
	add r0, r0, r1
	ldr r1, [sp]
	mov r4, #0xca
	lsl r4, r4, #2
	add r3, r1, #0
	mov r2, #0xf
	add r3, r3, r4
	bl MOD12_02241050
	cmp r0, #1
	bne _0222EC00
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222EBB8:
	ldr r0, [sp]
	mov r1, #0xc3
	ldr r4, _0222EC0C ; =0x00000127
	ldr r3, [r0]
	lsl r1, r1, #4
	add r0, r0, r1
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222EC00
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222EBDE:
	ldr r0, [r7, #4]
	add r0, r0, #1
	str r0, [r7, #4]
	cmp r0, #4
	blt _0222EBF4
	mov r0, #0
	str r0, [r7, #4]
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _0222EC00
_0222EBF4:
	mov r0, #0x14
	strh r0, [r7]
	b _0222EC00
_0222EBFA:
	add sp, #0x4c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0222EC00:
	mov r0, #0
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
	nop
_0222EC08: .word 0x00000231
_0222EC0C: .word 0x00000127

	thumb_func_start MOD12_0222EC10
MOD12_0222EC10: ; 0x0222EC10
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	beq _0222EC26
	cmp r0, #1
	beq _0222EC2C
	cmp r0, #2
	beq _0222EC4C
	b _0222EC70
_0222EC26:
	add r0, r0, #1
	strh r0, [r4]
	b _0222EC74
_0222EC2C:
	mov r0, #0xc3
	mov r3, #0xca
	lsl r0, r0, #4
	lsl r3, r3, #2
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #0x12
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _0222EC74
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222EC74
_0222EC4C:
	mov r0, #0xc3
	lsl r0, r0, #4
	ldr r3, [r5]
	add r0, r5, r0
	ldr r5, _0222EC78 ; =0x00000127
	sub r2, r5, #4
	ldrb r1, [r3, r5]
	sub r5, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r5]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222EC74
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222EC74
_0222EC70:
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222EC74:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222EC78: .word 0x00000127

	thumb_func_start MOD12_0222EC7C
MOD12_0222EC7C: ; 0x0222EC7C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldrh r1, [r5]
	add r4, r0, #0
	cmp r1, #6
	bls _0222EC8A
	b _0222EDEE
_0222EC8A:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222EC96: ; jump table
	.short _0222ECA4 - _0222EC96 - 2 ; case 0
	.short _0222ECC4 - _0222EC96 - 2 ; case 1
	.short _0222ECEA - _0222EC96 - 2 ; case 2
	.short _0222ED4A - _0222EC96 - 2 ; case 3
	.short _0222ED6E - _0222EC96 - 2 ; case 4
	.short _0222EDAA - _0222EC96 - 2 ; case 5
	.short _0222EDCA - _0222EC96 - 2 ; case 6
_0222ECA4:
	mov r0, #0xc3
	mov r3, #0xca
	lsl r0, r0, #4
	lsl r3, r3, #2
	add r0, r4, r0
	add r1, r4, #0
	mov r2, #0x15
	add r3, r4, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _0222ECE0
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _0222EE0E
_0222ECC4:
	mov r0, #0xc3
	lsl r0, r0, #4
	ldr r3, [r4]
	add r0, r4, r0
	ldr r4, _0222EE14 ; =0x00000127
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	beq _0222ECE2
_0222ECE0:
	b _0222EE0E
_0222ECE2:
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _0222EE0E
_0222ECEA:
	mov r2, #0x36
	mov r1, #0
	lsl r2, r2, #4
	add r0, r1, #0
	add r2, r4, r2
_0222ECF4:
	ldr r3, [r2]
	lsl r3, r3, #0x1a
	lsr r3, r3, #0x1e
	beq _0222ECFE
	add r1, r1, #1
_0222ECFE:
	add r0, r0, #1
	add r2, #0x2c
	cmp r0, #4
	blt _0222ECF4
	mov r0, #0x23
	lsl r0, r0, #4
	ldrb r0, [r4, r0]
	cmp r0, #3
	bhs _0222ED1C
	cmp r1, #4
	bge _0222ED1C
	ldr r0, _0222EE18 ; =0x0000040C
	mov r1, #0x2a
	strb r1, [r4, r0]
	b _0222ED22
_0222ED1C:
	ldr r0, _0222EE18 ; =0x0000040C
	mov r1, #0
	strb r1, [r4, r0]
_0222ED22:
	ldr r3, _0222EE1C ; =0x0000040E
	mov r1, #0
	strb r1, [r4, r3]
	add r0, r3, #1
	strb r1, [r4, r0]
	mov r0, #0xc3
	lsl r0, r0, #4
	sub r3, #0xe6
	add r0, r4, r0
	add r1, r4, #0
	mov r2, #0x14
	add r3, r4, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _0222EE0E
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _0222EE0E
_0222ED4A:
	mov r0, #0xc3
	lsl r0, r0, #4
	ldr r3, [r4]
	add r0, r4, r0
	ldr r4, _0222EE14 ; =0x00000127
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222EE0E
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _0222EE0E
_0222ED6E:
	mov r1, #0xce
	lsl r1, r1, #2
	add r1, r4, r1
	bl MOD12_0223818C
	mov r0, #0x23
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD12_02235C60
	ldr r0, _0222EE20 ; =0x00000236
	mov r6, #0
	add r1, r0, #0
	add r3, r4, #0
	add r1, #0x20
_0222ED8C:
	ldrh r2, [r3, r0]
	add r6, r6, #1
	strh r2, [r3, r1]
	add r3, r3, #2
	cmp r6, #4
	blt _0222ED8C
	mov r0, #0x23
	lsl r0, r0, #4
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _0222EE0E
_0222EDAA:
	mov r0, #0xc3
	mov r3, #0x23
	lsl r0, r0, #4
	lsl r3, r3, #4
	add r0, r4, r0
	add r1, r4, #0
	mov r2, #0x13
	add r3, r4, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _0222EE0E
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _0222EE0E
_0222EDCA:
	mov r0, #0xc3
	lsl r0, r0, #4
	ldr r3, [r4]
	add r0, r4, r0
	ldr r4, _0222EE14 ; =0x00000127
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222EE0E
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _0222EE0E
_0222EDEE:
	mov r0, #0x23
	lsl r0, r0, #4
	ldrb r1, [r4, r0]
	cmp r1, #4
	blo _0222EE00
	mov r0, #0xf
	strh r0, [r5, #2]
	mov r0, #2
	pop {r4, r5, r6, pc}
_0222EE00:
	mov r1, #0
	add r0, r0, #5
	strb r1, [r4, r0]
	mov r0, #3
	strh r0, [r5, #2]
	mov r0, #2
	pop {r4, r5, r6, pc}
_0222EE0E:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_0222EE14: .word 0x00000127
_0222EE18: .word 0x0000040C
_0222EE1C: .word 0x0000040E
_0222EE20: .word 0x00000236

	thumb_func_start MOD12_0222EE24
MOD12_0222EE24: ; 0x0222EE24
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r3, r0, #0
	ldrh r0, [r4]
	cmp r0, #3
	bhi _0222EED0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222EE3C: ; jump table
	.short _0222EE44 - _0222EE3C - 2 ; case 0
	.short _0222EE66 - _0222EE3C - 2 ; case 1
	.short _0222EE90 - _0222EE3C - 2 ; case 2
	.short _0222EEB4 - _0222EE3C - 2 ; case 3
_0222EE44:
	mov r1, #0
	ldr r7, _0222EEF4 ; =0x0000012E
	add r2, r3, #0
	add r5, r1, #0
_0222EE4C:
	ldr r0, _0222EEF8 ; =0x00000242
	ldr r6, [r3]
	ldrsh r0, [r2, r0]
	add r6, r6, r5
	add r1, r1, #1
	strh r0, [r6, r7]
	add r2, r2, #2
	add r5, #0xc
	cmp r1, #4
	blt _0222EE4C
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
_0222EE66:
	ldr r5, _0222EEFC ; =0x0000040C
	mov r0, #0x2b
	strb r0, [r3, r5]
	add r0, r5, #1
	mov r1, #0
	strb r1, [r3, r0]
	mov r0, #0xc3
	lsl r0, r0, #4
	sub r5, #0xe4
	add r0, r3, r0
	add r1, r3, #0
	mov r2, #3
	add r3, r3, r5
	bl MOD12_02241050
	cmp r0, #1
	bne _0222EEF0
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222EEF0
_0222EE90:
	mov r0, #0xc3
	lsl r0, r0, #4
	ldr r5, [r3]
	add r0, r3, r0
	ldr r3, _0222EF00 ; =0x00000127
	sub r2, r3, #4
	ldrb r1, [r5, r3]
	sub r3, #0xb
	ldrb r2, [r5, r2]
	ldrb r3, [r5, r3]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222EEF0
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222EEF0
_0222EEB4:
	mov r0, #0xc3
	lsl r0, r0, #4
	add r0, r3, r0
	add r1, r3, #0
	mov r2, #1
	mov r3, #0
	bl MOD12_02241050
	cmp r0, #1
	bne _0222EEF0
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222EEF0
_0222EED0:
	mov r0, #0xc3
	lsl r0, r0, #4
	ldr r4, [r3]
	add r0, r3, r0
	ldr r3, _0222EF00 ; =0x00000127
	sub r2, r3, #4
	ldrb r1, [r4, r3]
	sub r3, #0xb
	ldrb r2, [r4, r2]
	ldrb r3, [r4, r3]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222EEF0
	mov r0, #3
	pop {r3, r4, r5, r6, r7, pc}
_0222EEF0:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222EEF4: .word 0x0000012E
_0222EEF8: .word 0x00000242
_0222EEFC: .word 0x0000040C
_0222EF00: .word 0x00000127

	thumb_func_start MOD12_0222EF04
MOD12_0222EF04: ; 0x0222EF04
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r1, #1
	lsl r1, r1, #0x1a
	ldr r0, [r1]
	ldr r2, _0222F15C ; =0xFFFFE0FF
	and r0, r2
	str r0, [r1]
	ldr r0, _0222F160 ; =0x04001000
	ldr r3, [r0]
	and r2, r3
	str r2, [r0]
	ldr r3, [r1]
	ldr r2, _0222F164 ; =0xFFFF1FFF
	and r3, r2
	str r3, [r1]
	ldr r3, [r0]
	add r1, #0x50
	and r2, r3
	str r2, [r0]
	mov r2, #0
	strh r2, [r1]
	add r0, #0x50
	strh r2, [r0]
	mov r2, #7
	mov r0, #3
	mov r1, #0x16
	lsl r2, r2, #0x10
	bl FUN_0201681C
	ldr r1, _0222F168 ; =0x00000F68
	add r0, r4, #0
	mov r2, #0x16
	bl OverlayManager_CreateAndGetData
	ldr r2, _0222F168 ; =0x00000F68
	mov r1, #0
	add r5, r0, #0
	bl MI_CpuFill8
	mov r0, #0x16
	bl MOD12_022312D8
	str r0, [r5, #8]
	add r0, r4, #0
	bl OverlayManager_GetField18
	mov r1, #0x5b
	str r0, [r5]
	lsl r1, r1, #2
	str r5, [r0, r1]
	ldr r2, [r5]
	mov r3, #0
	add r0, r1, #4
	strb r3, [r2, r0]
	ldr r0, [r5]
	str r0, [r5, #0xc]
	add r0, r5, #0
	bl MOD12_0222F720
	mov r0, #0x16
	bl FUN_02002FD0
	str r0, [r5, #0x50]
	mov r1, #1
	bl FUN_020038F0
	mov r2, #2
	ldr r0, [r5, #0x50]
	mov r1, #0
	lsl r2, r2, #8
	mov r3, #0x16
	bl FUN_02003008
	mov r1, #1
	ldr r0, [r5, #0x50]
	lsl r2, r1, #9
	mov r3, #0x16
	bl FUN_02003008
	mov r2, #7
	ldr r0, [r5, #0x50]
	mov r1, #2
	lsl r2, r2, #6
	mov r3, #0x16
	bl FUN_02003008
	mov r2, #2
	ldr r0, [r5, #0x50]
	mov r1, #3
	lsl r2, r2, #8
	mov r3, #0x16
	bl FUN_02003008
	mov r0, #0x16
	bl FUN_02016B94
	str r0, [r5, #0x30]
	mov r0, #0x40
	mov r1, #0x16
	bl FUN_0201C24C
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	ldr r0, [r5, #0x30]
	bl MOD12_0222F548
	bl FUN_0201CC08
	mov r0, #4
	bl FUN_0201CC24
	mov r0, #2
	mov r1, #0x16
	bl FUN_02002C50
	mov r0, #0x16
	bl FUN_0200BB14
	ldr r1, _0222F16C ; =MOD12_02244AFC
	ldr r2, _0222F170 ; =MOD12_02244AB4
	mov r3, #0x20
	str r0, [r5, #0x28]
	bl FUN_0200BB6C
	ldr r1, _0222F174 ; =0x00100010
	mov r0, #1
	bl FUN_02008D44
	mov r0, #1
	bl FUN_02008DDC
	ldr r0, [r5, #0x28]
	bl FUN_0200BB34
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	mov r2, #0x80
	bl FUN_0200BBF0
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	ldr r2, _0222F178 ; =MOD12_02244AC8
	bl FUN_0200BF60
	ldr r0, [r5, #0x28]
	bl FUN_0200BB68
	mov r2, #1
	mov r1, #0
	lsl r2, r2, #0x14
	bl FUN_02008D24
	mov r0, #0x16
	bl FUN_02006D98
	str r0, [r5, #0x10]
	bl MOD12_0222F6E0
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0xc4
	mov r3, #0x16
	bl NewMsgDataFromNarc
	str r0, [r5, #0x44]
	mov r0, #0x16
	bl ScrStrBufs_new
	str r0, [r5, #0x48]
	mov r0, #5
	lsl r0, r0, #6
	mov r1, #0x16
	bl String_ctor
	str r0, [r5, #0x4c]
	add r0, r5, #0
	bl MOD12_0222F834
	add r0, r5, #0
	bl MOD12_0222F938
	add r0, r5, #0
	bl MOD12_0222F6B4
	add r0, r5, #0
	bl MOD12_0222F748
	add r0, r5, #0
	bl MOD12_0222F7F4
	mov r0, #1
	str r0, [sp]
	add r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	ldr r0, [r5, #0x50]
	ldr r3, _0222F17C ; =0x00007FFF
	add r2, r1, #0
	bl FUN_02003914
	mov r1, #1
	add r0, r1, #0
	str r1, [sp]
	add r0, #0xff
	str r0, [sp, #4]
	ldr r0, [r5, #0x50]
	ldr r3, _0222F17C ; =0x00007FFF
	mov r2, #0
	bl FUN_02003914
	mov r2, #0
	str r2, [sp]
	mov r0, #0xe0
	str r0, [sp, #4]
	ldr r0, [r5, #0x50]
	ldr r3, _0222F17C ; =0x00007FFF
	mov r1, #2
	bl FUN_02003914
	mov r2, #0
	mov r0, #1
	str r2, [sp]
	lsl r0, r0, #8
	str r0, [sp, #4]
	ldr r0, [r5, #0x50]
	ldr r3, _0222F17C ; =0x00007FFF
	mov r1, #3
	bl FUN_02003914
	bl FUN_02033E74
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r1, #0x16
	str r1, [sp, #8]
	mov r1, #0x1b
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, _0222F180 ; =MOD12_0222F4F4
	ldr r2, _0222F184 ; =0x0000EA60
	add r1, r5, #0
	bl FUN_0200CA44
	str r0, [r5, #4]
	ldr r0, _0222F188 ; =0x000004F8
	mov r1, #1
	strb r1, [r5, r0]
	bl GX_BothDispOn
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	mov r0, #0
	bl FUN_0200415C
	ldr r1, _0222F18C ; =0x0000046F
	mov r0, #6
	mov r2, #1
	bl FUN_0200433C
	ldr r1, [r5]
	ldr r0, _0222F190 ; =0x00000171
	ldrb r0, [r1, r0]
	bl FUN_020833D4
	ldr r0, _0222F194 ; =MOD12_0222F458
	add r1, r5, #0
	bl Main_SetVBlankIntrCB
	ldr r0, _0222F198 ; =0x00000605
	bl FUN_020054C8
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0222F15C: .word 0xFFFFE0FF
_0222F160: .word 0x04001000
_0222F164: .word 0xFFFF1FFF
_0222F168: .word 0x00000F68
_0222F16C: .word MOD12_02244AFC
_0222F170: .word MOD12_02244AB4
_0222F174: .word 0x00100010
_0222F178: .word MOD12_02244AC8
_0222F17C: .word 0x00007FFF
_0222F180: .word MOD12_0222F4F4
_0222F184: .word 0x0000EA60
_0222F188: .word 0x000004F8
_0222F18C: .word 0x0000046F
_0222F190: .word 0x00000171
_0222F194: .word MOD12_0222F458
_0222F198: .word 0x00000605

	thumb_func_start MOD12_0222F19C
MOD12_0222F19C: ; 0x0222F19C
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_02082878
	ldr r0, [r5]
	cmp r0, #0
	beq _0222F1C0
	cmp r0, #1
	beq _0222F236
	cmp r0, #2
	bne _0222F1BE
	b _0222F2EC
_0222F1BE:
	b _0222F2FA
_0222F1C0:
	bl FUN_0200E308
	cmp r0, #1
	beq _0222F1CA
	b _0222F2FA
_0222F1CA:
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0222F300 ; =0x00007FFF
	ldr r2, _0222F304 ; =0x0000FFFF
	str r0, [sp, #8]
	ldr r0, [r4, #0x50]
	mov r1, #1
	mov r3, #6
	bl FUN_02003210
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0222F300 ; =0x00007FFF
	ldr r2, _0222F304 ; =0x0000FFFF
	str r0, [sp, #8]
	ldr r0, [r4, #0x50]
	mov r1, #2
	mov r3, #6
	bl FUN_02003210
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0
	ldr r2, _0222F300 ; =0x00007FFF
	str r0, [sp, #4]
	str r2, [sp, #8]
	ldr r0, [r4, #0x50]
	mov r1, #4
	lsr r2, r2, #1
	mov r3, #6
	bl FUN_02003210
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0222F300 ; =0x00007FFF
	ldr r2, _0222F304 ; =0x0000FFFF
	str r0, [sp, #8]
	ldr r0, [r4, #0x50]
	mov r1, #8
	mov r3, #6
	bl FUN_02003210
	ldr r0, _0222F308 ; =0x000006E5
	bl FUN_020054C8
	mov r0, #1
	str r0, [r5]
	b _0222F2FA
_0222F236:
	ldr r0, [r4]
	bl FUN_020828BC
	cmp r0, #1
	bne _0222F2A8
	ldr r2, _0222F30C ; =0x000004F6
	ldr r1, _0222F310 ; =0x00000F14
	ldrh r2, [r4, r2]
	add r0, r4, #0
	add r1, r4, r1
	lsl r3, r2, #2
	ldr r2, _0222F314 ; =MOD12_02244B44
	ldr r2, [r2, r3]
	blx r2
	sub r1, r0, #1
	cmp r1, #1
	bhi _0222F27A
	cmp r0, #1
	bne _0222F264
	ldr r0, _0222F30C ; =0x000004F6
	ldrh r1, [r4, r0]
	add r1, r1, #1
	b _0222F26A
_0222F264:
	ldr r0, _0222F318 ; =0x00000F16
	ldrh r1, [r4, r0]
	ldr r0, _0222F30C ; =0x000004F6
_0222F26A:
	strh r1, [r4, r0]
	ldr r0, _0222F310 ; =0x00000F14
	mov r1, #0
	add r0, r4, r0
	mov r2, #8
	bl MI_CpuFill8
	b _0222F2A8
_0222F27A:
	cmp r0, #3
	bne _0222F2A8
	mov r0, #2
	str r0, [r5]
	ldr r0, _0222F310 ; =0x00000F14
	mov r1, #0
	add r0, r4, r0
	mov r2, #8
	bl MI_CpuFill8
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x16
	str r0, [sp, #8]
	mov r0, #2
	mov r1, #0x10
	mov r2, #0x24
	mov r3, #0
	bl FUN_0200E1D0
	b _0222F2FA
_0222F2A8:
	ldr r0, _0222F31C ; =0x000004FC
	add r0, r4, r0
	bl MOD12_022410A0
	ldr r0, _0222F31C ; =0x000004FC
	add r1, r4, #0
	add r0, r4, r0
	bl MOD12_02241114
	ldr r0, _0222F320 ; =0x00000F1C
	ldrb r1, [r4, r0]
	cmp r1, #1
	bne _0222F2FA
	mov r1, #2
	sub r0, #8
	str r1, [r5]
	add r0, r4, r0
	mov r1, #0
	mov r2, #8
	bl MI_CpuFill8
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x16
	str r0, [sp, #8]
	mov r0, #2
	mov r1, #0x10
	mov r2, #0x24
	mov r3, #0
	bl FUN_0200E1D0
	b _0222F2FA
_0222F2EC:
	bl FUN_0200E308
	cmp r0, #1
	bne _0222F2FA
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_0222F2FA:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_0222F300: .word 0x00007FFF
_0222F304: .word 0x0000FFFF
_0222F308: .word 0x000006E5
_0222F30C: .word 0x000004F6
_0222F310: .word 0x00000F14
_0222F314: .word MOD12_02244B44
_0222F318: .word 0x00000F16
_0222F31C: .word 0x000004FC
_0222F320: .word 0x00000F1C

	thumb_func_start MOD12_0222F324
MOD12_0222F324: ; 0x0222F324
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	bl OverlayManager_GetData
	add r4, r0, #0
	bl FUN_02012EAC
	add r0, r4, #0
	bl MOD12_0222F7C0
	add r0, r4, #0
	bl MOD12_0222F824
	add r0, r4, #0
	bl MOD12_0222F934
	add r0, r4, #0
	bl MOD12_0222F98C
	add r0, r4, #0
	add r0, #0x34
	bl FUN_02019178
	mov r0, #1
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #0x30]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #0x30]
	mov r1, #3
	bl FUN_020178A0
	mov r0, #4
	mov r1, #0
	bl FUN_0201797C
	ldr r0, [r4, #0x30]
	mov r1, #4
	bl FUN_020178A0
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x2c]
	bl FUN_0200C398
	ldr r0, [r4, #0x28]
	bl FUN_0200BD04
	bl FUN_0201C29C
	mov r7, #0xf2
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #4
_0222F3A4:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _0222F3AE
	bl MOD17_021DD540
_0222F3AE:
	add r6, r6, #1
	add r5, #0x10
	cmp r6, #4
	blt _0222F3A4
	add r0, r4, #0
	add r0, #0xc
	bl MOD12_02239874
	add r0, r4, #0
	bl MOD12_02239A58
	ldr r0, [r4, #0x10]
	bl FUN_020072E8
	mov r0, #2
	bl FUN_02002CF8
	ldr r0, [r4, #0x50]
	mov r1, #0
	bl FUN_02003038
	ldr r0, [r4, #0x50]
	mov r1, #1
	bl FUN_02003038
	ldr r0, [r4, #0x50]
	mov r1, #2
	bl FUN_02003038
	ldr r0, [r4, #0x50]
	mov r1, #3
	bl FUN_02003038
	ldr r0, [r4, #0x50]
	bl FUN_02002FEC
	ldr r0, [r4, #0x48]
	bl ScrStrBufs_delete
	ldr r0, [r4, #0x4c]
	bl String_dtor
	ldr r0, [r4, #0x44]
	bl DestroyMsgData
	ldr r0, [r4, #0x30]
	bl FreeToHeap
	ldr r0, [r4, #4]
	bl FUN_0200CAB4
	ldr r0, [r4, #8]
	bl MOD12_02231378
	bl FUN_0201CD04
	ldr r0, [sp]
	bl OverlayManager_FreeData
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	mov r0, #0x16
	bl FUN_020168D0
	bl FUN_02083404
	bl FUN_02033ED0
	ldr r0, _0222F450 ; =SDK_OVERLAY_MODULE_08_ID
	bl UnloadOverlayByID
	ldr r0, _0222F454 ; =SDK_OVERLAY_MODULE_17_ID
	bl UnloadOverlayByID
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222F450: .word SDK_OVERLAY_MODULE_08_ID
_0222F454: .word SDK_OVERLAY_MODULE_17_ID

	thumb_func_start MOD12_0222F458
MOD12_0222F458: ; 0x0222F458
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, _0222F4E4 ; =0x00000F63
	sub r1, r0, #2
	ldrb r3, [r6, r1]
	sub r1, r0, #3
	ldrb r1, [r6, r1]
	sub r5, r0, #1
	ldrb r5, [r6, r5]
	lsl r2, r1, #8
	mov r1, #0xff
	lsl r1, r1, #8
	and r2, r1
	orr r2, r5
	ldrb r4, [r6, r0]
	ldr r5, _0222F4E8 ; =0x04000040
	strh r2, [r5]
	lsl r2, r3, #8
	and r2, r1
	orr r2, r4
	strh r2, [r5, #4]
	add r2, r0, #4
	ldrb r4, [r6, r2]
	add r2, r0, #2
	ldrb r3, [r6, r2]
	add r2, r0, #1
	ldrb r2, [r6, r2]
	add r0, r0, #3
	ldrb r0, [r6, r0]
	lsl r2, r2, #8
	and r2, r1
	orr r0, r2
	strh r0, [r5, #2]
	lsl r0, r3, #8
	and r0, r1
	orr r0, r4
	strh r0, [r5, #6]
	ldr r0, [r6, #0x10]
	bl FUN_020081C4
	mov r7, #0xf2
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #4
_0222F4B0:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _0222F4BA
	bl MOD17_021DD58C
_0222F4BA:
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #4
	blt _0222F4B0
	bl FUN_0201C30C
	bl FUN_0200BC30
	ldr r0, [r6, #0x50]
	bl FUN_0200372C
	ldr r0, [r6, #0x30]
	bl FUN_0201AB60
	ldr r3, _0222F4EC ; =0x027E0000
	ldr r1, _0222F4F0 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222F4E4: .word 0x00000F63
_0222F4E8: .word 0x04000040
_0222F4EC: .word 0x027E0000
_0222F4F0: .word 0x00003FF8

	thumb_func_start MOD12_0222F4F4
MOD12_0222F4F4: ; 0x0222F4F4
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, _0222F540 ; =0x000004F8
	add r6, r1, #0
	ldrb r0, [r6, r0]
	cmp r0, #1
	bne _0222F534
	ldr r0, [r6, #0x10]
	bl FUN_02006ED4
	mov r7, #0xf2
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #4
_0222F50E:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _0222F518
	bl MOD17_021DD518
_0222F518:
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #4
	blt _0222F50E
	bl MOD08_02215A44
	ldr r0, [r6, #0x2c]
	bl FUN_0200BC1C
	bl FUN_0200BC38
	ldr r0, _0222F544 ; =0x04000540
	mov r1, #1
	str r1, [r0]
_0222F534:
	ldr r1, [r6, #0x30]
	mov r0, #0x16
	bl FUN_020335F0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222F540: .word 0x000004F8
_0222F544: .word 0x04000540

	thumb_func_start MOD12_0222F548
MOD12_0222F548: ; 0x0222F548
	push {r3, r4, r5, lr}
	sub sp, #0xa8
	add r4, r0, #0
	bl GX_DisableEngineALayers
	ldr r5, _0222F6A0 ; =MOD12_02244B1C
	add r3, sp, #0x2c
	mov r2, #5
_0222F558:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222F558
	add r0, sp, #0x2c
	bl GX_SetBanks
	mov r1, #6
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x18
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x62
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	mov r1, #0x19
	mov r2, #1
	mov r0, #0
	lsl r1, r1, #0x16
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x66
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	ldr r5, _0222F6A4 ; =MOD12_02244AA4
	add r3, sp, #0x1c
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _0222F6A8 ; =MOD12_02244B70
	add r3, sp, #0x54
	mov r2, #0xa
_0222F5B8:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222F5B8
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	add r2, sp, #0x54
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	mov r2, #0
	add r0, r4, #0
	mov r1, #1
	add r3, r2, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #1
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #2
	add r2, sp, #0x70
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #2
	bl FUN_02018744
	mov r2, #0
	add r0, r4, #0
	mov r1, #2
	add r3, r2, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #2
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #3
	add r2, sp, #0x8c
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #3
	bl FUN_02018744
	mov r2, #0
	add r0, r4, #0
	mov r1, #3
	add r3, r2, #0
	bl FUN_020179E0
	mov r1, #3
	add r0, r4, #0
	add r2, r1, #0
	mov r3, #0
	bl FUN_020179E0
	ldr r1, _0222F6AC ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #1
	orr r2, r0
	strh r2, [r1]
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r5, _0222F6B0 ; =MOD12_02244AE0
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
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	mov r2, #0
	add r0, r4, #0
	mov r1, #4
	add r3, r2, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #4
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add sp, #0xa8
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222F6A0: .word MOD12_02244B1C
_0222F6A4: .word MOD12_02244AA4
_0222F6A8: .word MOD12_02244B70
_0222F6AC: .word 0x04000008
_0222F6B0: .word MOD12_02244AE0

	thumb_func_start MOD12_0222F6B4
MOD12_0222F6B4: ; 0x0222F6B4
	push {lr}
	sub sp, #0x14
	add r1, r0, #0
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x1f
	str r0, [sp, #0x10]
	ldr r0, [r1, #0x30]
	add r1, #0x34
	mov r2, #1
	mov r3, #2
	bl FUN_02019064
	add sp, #0x14
	pop {pc}
	.align 2, 0

	thumb_func_start MOD12_0222F6E0
MOD12_0222F6E0: ; 0x0222F6E0
	push {r3, r4, r5, lr}
	ldr r3, _0222F718 ; =UNK_021064B8
	mov r0, #2
	mov r1, #0
	ldr r3, [r3]
	lsl r0, r0, #0xe
	add r2, r1, #0
	blx r3
	ldr r3, _0222F71C ; =UNK_021064C0
	mov r1, #0
	add r4, r0, #0
	ldr r3, [r3]
	mov r0, #0x80
	add r2, r1, #0
	blx r3
	add r5, r0, #0
	cmp r4, #0
	bne _0222F708
	bl ErrorHandling
_0222F708:
	cmp r5, #0
	bne _0222F710
	bl ErrorHandling
_0222F710:
	bl FUN_02012CC8
	pop {r3, r4, r5, pc}
	nop
_0222F718: .word UNK_021064B8
_0222F71C: .word UNK_021064C0

	thumb_func_start MOD12_0222F720
MOD12_0222F720: ; 0x0222F720
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	bne _0222F72E
	bl ErrorHandling
_0222F72E:
	mov r3, #0
	mov r0, #3
_0222F732:
	add r1, r4, r3
	sub r2, r0, r3
	add r1, #0xd4
	add r3, r3, #1
	strb r2, [r1]
	cmp r3, #4
	blt _0222F732
	add r0, r4, #0
	bl MOD12_02239B88
	pop {r4, pc}

	thumb_func_start MOD12_0222F748
MOD12_0222F748: ; 0x0222F748
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	mov r0, #0x2e
	str r0, [sp]
	mov r0, #7
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, _0222F7B8 ; =0x000080E9
	mov r1, #2
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x50]
	ldr r2, [r4, #0x28]
	ldr r3, [r4, #0x2c]
	bl FUN_0200C0DC
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x2c]
	bl MOD12_0223988C
	mov r0, #0
	mvn r0, r0
	ldr r3, _0222F7B8 ; =0x000080E9
	str r0, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x2c]
	ldr r2, [r4, #0x50]
	bl MOD12_022316F8
	ldr r3, _0222F7B8 ; =0x000080E9
	mov r0, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	str r0, [sp, #0xc]
	mov r0, #0xc8
	str r0, [sp, #0x10]
	mov r0, #3
	str r0, [sp, #0x14]
	ldr r0, _0222F7BC ; =0x0000C350
	str r0, [sp, #0x18]
	add r0, r4, #0
	ldr r1, [r4, #0x28]
	ldr r2, [r4, #0x2c]
	add r0, #0xb4
	bl MOD12_022317C8
	add sp, #0x1c
	pop {r3, r4, pc}
	.align 2, 0
_0222F7B8: .word 0x000080E9
_0222F7BC: .word 0x0000C350

	thumb_func_start MOD12_0222F7C0
MOD12_0222F7C0: ; 0x0222F7C0
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #0x2c]
	bl MOD12_022398D8
	add r0, r4, #0
	add r0, #0xb4
	bl MOD12_0223185C
	ldr r1, _0222F7F0 ; =0x000080E9
	mov r2, #0
	str r1, [sp]
	ldr r0, [r4, #0x2c]
	mvn r2, r2
	add r3, r1, #0
	bl MOD12_02231780
	ldr r0, [r4, #0x2c]
	ldr r1, _0222F7F0 ; =0x000080E9
	bl FUN_0200C368
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0222F7F0: .word 0x000080E9

	thumb_func_start MOD12_0222F7F4
MOD12_0222F7F4: ; 0x0222F7F4
	push {r3, lr}
	sub sp, #0x18
	add r3, r0, #0
	mov r0, #0x2e
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, _0222F820 ; =0x000080EA
	mov r1, #3
	str r0, [sp, #0x14]
	ldr r0, [r3, #0x50]
	ldr r2, [r3, #0x28]
	ldr r3, [r3, #0x2c]
	bl FUN_0200C0DC
	add sp, #0x18
	pop {r3, pc}
	.align 2, 0
_0222F820: .word 0x000080EA

	thumb_func_start MOD12_0222F824
MOD12_0222F824: ; 0x0222F824
	ldr r3, _0222F82C ; =FUN_0200C368
	ldr r0, [r0, #0x2c]
	ldr r1, _0222F830 ; =0x000080EA
	bx r3
	.align 2, 0
_0222F82C: .word FUN_0200C368
_0222F830: .word 0x000080EA

	thumb_func_start MOD12_0222F834
MOD12_0222F834: ; 0x0222F834
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r1, #0x16
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x30]
	mov r0, #0x2d
	mov r3, #3
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x16
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x30]
	mov r0, #0x2d
	mov r1, #0x15
	mov r3, #3
	bl FUN_020068C8
	ldr r0, [r5, #0x30]
	mov r1, #1
	bl FUN_02018744
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5, #0x50]
	mov r1, #0x2d
	mov r2, #0x22
	mov r3, #0x16
	bl FUN_020030E8
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xd0
	str r0, [sp, #8]
	ldr r0, [r5, #0x50]
	mov r1, #0x2d
	mov r2, #0x23
	mov r3, #0x16
	bl FUN_020030E8
	ldr r1, [r5]
	ldr r0, _0222F930 ; =0x00001988
	ldr r0, [r1, r0]
	bl Options_GetFrame
	add r4, r0, #0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x16
	str r0, [sp, #4]
	mov r1, #1
	ldr r0, [r5, #0x30]
	add r2, r1, #0
	mov r3, #0xf
	bl FUN_0200CD68
	add r0, r4, #0
	bl FUN_0200CD64
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xe0
	str r0, [sp, #8]
	ldr r0, [r5, #0x50]
	mov r1, #0x26
	mov r3, #0x16
	bl FUN_020030E8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x16
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x30]
	mov r0, #0x2d
	mov r1, #0x17
	mov r3, #2
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x16
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x30]
	mov r0, #0x2d
	mov r1, #0x14
	mov r3, #2
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xc0
	str r0, [sp, #8]
	ldr r0, [r5, #0x50]
	mov r1, #0x2d
	mov r2, #0x24
	mov r3, #0x16
	bl FUN_020030E8
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222F930: .word 0x00001988

	thumb_func_start MOD12_0222F934
MOD12_0222F934: ; 0x0222F934
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0222F938
MOD12_0222F938: ; 0x0222F938
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x16
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x30]
	mov r0, #0x2d
	mov r1, #0x12
	mov r3, #4
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x16
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x30]
	mov r0, #0x2d
	mov r1, #0x13
	mov r3, #4
	bl FUN_020068C8
	mov r0, #1
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4, #0x50]
	mov r1, #0x2d
	mov r2, #0x21
	mov r3, #0x16
	bl FUN_020030E8
	add sp, #0x10
	pop {r4, pc}

	thumb_func_start MOD12_0222F98C
MOD12_0222F98C: ; 0x0222F98C
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0222F990
MOD12_0222F990: ; 0x0222F990
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	bne _0222F9BC
	ldr r0, [r5, #0x50]
	bl FUN_020038E4
	cmp r0, #0
	bne _0222F9C0
	ldr r0, [r5]
	mov r1, #0x16
	bl MOD12_022314CC
	ldr r0, [r5]
	bl MOD12_0223150C
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222F9C0
_0222F9BC:
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222F9C0:
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_0222F9C4
MOD12_0222F9C4: ; 0x0222F9C4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldrh r0, [r5]
	cmp r0, #0
	bne _0222FA10
	ldr r0, [r4]
	bl FUN_020832EC
	cmp r0, #1
	bne _0222F9DE
	mov r1, #2
	b _0222F9E0
_0222F9DE:
	mov r1, #1
_0222F9E0:
	add r0, r4, #0
	add r0, #0xe9
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xea
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0xeb
	strb r1, [r0]
	ldr r0, _0222FA34 ; =0x000004FC
	add r1, r4, #0
	add r0, r4, r0
	add r4, #0xe2
	mov r2, #0xd
	add r3, r4, #0
	bl MOD12_02241050
	cmp r0, #1
	bne _0222FA2E
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _0222FA2E
_0222FA10:
	ldr r0, _0222FA34 ; =0x000004FC
	ldr r3, [r4]
	add r0, r4, r0
	ldr r4, _0222FA38 ; =0x00000127
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222FA2E
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222FA2E:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_0222FA34: .word 0x000004FC
_0222FA38: .word 0x00000127

	thumb_func_start MOD12_0222FA3C
MOD12_0222FA3C: ; 0x0222FA3C
	push {r4, lr}
	add r4, r1, #0
	add r3, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	bne _0222FA74
	add r0, r3, #0
	add r0, #0xd8
	ldrb r0, [r0]
	mov r2, #0
	add r0, r3, r0
	add r0, #0xd4
	ldrb r1, [r0]
	add r0, r3, #0
	add r0, #0xe2
	strb r1, [r0]
	ldr r0, _0222FA98 ; =0x000004FC
	add r1, r3, #0
	add r0, r3, r0
	add r3, #0xe2
	bl MOD12_02241050
	cmp r0, #1
	bne _0222FA92
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222FA92
_0222FA74:
	ldr r0, _0222FA98 ; =0x000004FC
	ldr r4, [r3]
	add r0, r3, r0
	ldr r3, _0222FA9C ; =0x00000127
	sub r2, r3, #4
	ldrb r1, [r4, r3]
	sub r3, #0xb
	ldrb r2, [r4, r2]
	ldrb r3, [r4, r3]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222FA92
	mov r0, #1
	pop {r4, pc}
_0222FA92:
	mov r0, #0
	pop {r4, pc}
	nop
_0222FA98: .word 0x000004FC
_0222FA9C: .word 0x00000127

	thumb_func_start MOD12_0222FAA0
MOD12_0222FAA0: ; 0x0222FAA0
	push {r4, lr}
	add r4, r1, #0
	add r3, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	bne _0222FAE6
	add r1, r3, #0
	mov r0, #0
	add r1, #0xec
	strb r0, [r1]
	add r2, r0, #0
	add r1, r3, #0
	sub r2, #0x10
	add r1, #0xed
	strb r2, [r1]
	add r1, r3, #0
	mov r2, #0x10
	add r1, #0xee
	strb r2, [r1]
	add r1, r3, #0
	add r1, #0xf0
	strh r0, [r1]
	ldr r0, _0222FB08 ; =0x000004FC
	add r1, r3, #0
	add r0, r3, r0
	mov r2, #0xe
	add r3, #0xe2
	bl MOD12_02241050
	cmp r0, #1
	bne _0222FB04
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222FB04
_0222FAE6:
	ldr r0, _0222FB08 ; =0x000004FC
	ldr r4, [r3]
	add r0, r3, r0
	ldr r3, _0222FB0C ; =0x00000127
	sub r2, r3, #4
	ldrb r1, [r4, r3]
	sub r3, #0xb
	ldrb r2, [r4, r2]
	ldrb r3, [r4, r3]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222FB04
	mov r0, #1
	pop {r4, pc}
_0222FB04:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_0222FB08: .word 0x000004FC
_0222FB0C: .word 0x00000127

	thumb_func_start MOD12_0222FB10
MOD12_0222FB10: ; 0x0222FB10
	push {r4, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	ldr r0, _0222FB58 ; =0x000004FC
	bne _0222FB36
	add r0, r2, r0
	add r1, r2, #0
	mov r2, #0xf
	mov r3, #0
	bl MOD12_02241050
	cmp r0, #1
	bne _0222FB52
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222FB52
_0222FB36:
	ldr r3, [r2]
	ldr r4, _0222FB5C ; =0x00000127
	add r0, r2, r0
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222FB52
	mov r0, #1
	pop {r4, pc}
_0222FB52:
	mov r0, #0
	pop {r4, pc}
	nop
_0222FB58: .word 0x000004FC
_0222FB5C: .word 0x00000127

	thumb_func_start MOD12_0222FB60
MOD12_0222FB60: ; 0x0222FB60
	push {r4, lr}
	add r4, r1, #0
	add r3, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	ldr r0, _0222FBA8 ; =0x000004FC
	bne _0222FB86
	add r0, r3, r0
	add r1, r3, #0
	mov r2, #2
	add r3, #0xe2
	bl MOD12_02241050
	cmp r0, #1
	bne _0222FBA2
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222FBA2
_0222FB86:
	ldr r4, [r3]
	add r0, r3, r0
	ldr r3, _0222FBAC ; =0x00000127
	sub r2, r3, #4
	ldrb r1, [r4, r3]
	sub r3, #0xb
	ldrb r2, [r4, r2]
	ldrb r3, [r4, r3]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222FBA2
	mov r0, #1
	pop {r4, pc}
_0222FBA2:
	mov r0, #0
	pop {r4, pc}
	nop
_0222FBA8: .word 0x000004FC
_0222FBAC: .word 0x00000127

	thumb_func_start MOD12_0222FBB0
MOD12_0222FBB0: ; 0x0222FBB0
	push {r4, lr}
	add r4, r1, #0
	add r3, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	beq _0222FBC2
	cmp r0, #1
	beq _0222FC1C
	b _0222FC36
_0222FBC2:
	add r0, r3, #0
	add r0, #0xd8
	ldrb r0, [r0]
	cmp r0, #0
	beq _0222FBD6
	cmp r0, #1
	beq _0222FBE0
	cmp r0, #2
	beq _0222FBEA
	b _0222FBF4
_0222FBD6:
	add r0, r3, #0
	mov r1, #3
	add r0, #0xe9
	strb r1, [r0]
	b _0222FBFC
_0222FBE0:
	add r0, r3, #0
	mov r1, #4
	add r0, #0xe9
	strb r1, [r0]
	b _0222FBFC
_0222FBEA:
	add r0, r3, #0
	mov r1, #5
	add r0, #0xe9
	strb r1, [r0]
	b _0222FBFC
_0222FBF4:
	add r0, r3, #0
	mov r1, #6
	add r0, #0xe9
	strb r1, [r0]
_0222FBFC:
	add r0, r3, #0
	mov r1, #0
	add r0, #0xea
	strb r1, [r0]
	add r0, r3, #0
	add r0, #0xeb
	strb r1, [r0]
	add r0, r3, #0
	add r0, #0xe2
	ldrb r1, [r0]
	add r0, r3, #0
	add r0, #0xe5
	strb r1, [r0]
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
_0222FC1C:
	ldr r0, _0222FC58 ; =0x000004FC
	add r1, r3, #0
	add r0, r3, r0
	mov r2, #0xd
	add r3, #0xe2
	bl MOD12_02241050
	cmp r0, #1
	bne _0222FC54
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222FC54
_0222FC36:
	ldr r0, _0222FC58 ; =0x000004FC
	ldr r4, [r3]
	add r0, r3, r0
	ldr r3, _0222FC5C ; =0x00000127
	sub r2, r3, #4
	ldrb r1, [r4, r3]
	sub r3, #0xb
	ldrb r2, [r4, r2]
	ldrb r3, [r4, r3]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222FC54
	mov r0, #1
	pop {r4, pc}
_0222FC54:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_0222FC58: .word 0x000004FC
_0222FC5C: .word 0x00000127

	thumb_func_start MOD12_0222FC60
MOD12_0222FC60: ; 0x0222FC60
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	beq _0222FC76
	cmp r0, #1
	beq _0222FCA0
	cmp r0, #2
	beq _0222FCBC
	b _0222FCDE
_0222FC76:
	add r1, r5, #0
	add r1, #0xe2
	ldrb r1, [r1]
	ldr r0, [r5]
	bl FUN_02083308
	add r1, r5, #0
	add r1, #0xe3
	strb r0, [r1]
	add r1, r5, #0
	add r1, #0xe2
	ldrb r1, [r1]
	ldr r0, [r5]
	bl FUN_0208336C
	add r1, r5, #0
	add r1, #0xe4
	strb r0, [r1]
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
_0222FCA0:
	ldr r0, _0222FCE8 ; =0x000004FC
	add r1, r5, #0
	add r0, r5, r0
	add r5, #0xe2
	mov r2, #6
	add r3, r5, #0
	bl MOD12_02241050
	cmp r0, #1
	bne _0222FCE2
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222FCE2
_0222FCBC:
	ldr r0, _0222FCE8 ; =0x000004FC
	ldr r3, [r5]
	add r0, r5, r0
	ldr r5, _0222FCEC ; =0x00000127
	sub r2, r5, #4
	ldrb r1, [r3, r5]
	sub r5, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r5]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222FCE2
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222FCE2
_0222FCDE:
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222FCE2:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_0222FCE8: .word 0x000004FC
_0222FCEC: .word 0x00000127

	thumb_func_start MOD12_0222FCF0
MOD12_0222FCF0: ; 0x0222FCF0
	ldrh r2, [r1]
	cmp r2, #0
	bne _0222FD0A
	add r2, r0, #0
	add r2, #0xd8
	ldrb r2, [r2]
	add r0, #0xd8
	add r2, r2, #1
	strb r2, [r0]
	ldrh r0, [r1]
	add r0, r0, #1
	strh r0, [r1]
	b _0222FD1C
_0222FD0A:
	add r0, #0xd8
	ldrb r0, [r0]
	cmp r0, #4
	blo _0222FD16
	mov r0, #1
	bx lr
_0222FD16:
	mov r0, #2
	strh r0, [r1, #2]
	bx lr
_0222FD1C:
	mov r0, #0
	bx lr

	thumb_func_start MOD12_0222FD20
MOD12_0222FD20: ; 0x0222FD20
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r3, r0, #0
	ldrh r0, [r4]
	cmp r0, #3
	bhi _0222FDC8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222FD38: ; jump table
	.short _0222FD40 - _0222FD38 - 2 ; case 0
	.short _0222FD62 - _0222FD38 - 2 ; case 1
	.short _0222FD84 - _0222FD38 - 2 ; case 2
	.short _0222FDAE - _0222FD38 - 2 ; case 3
_0222FD40:
	add r0, r3, #0
	ldr r1, _0222FDEC ; =0x000006E5
	add r0, #0xf2
	strh r1, [r0]
	ldr r0, _0222FDF0 ; =0x000004FC
	add r1, r3, #0
	add r0, r3, r0
	mov r2, #0x10
	add r3, #0xe2
	bl MOD12_02241050
	cmp r0, #1
	bne _0222FDE6
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222FDE6
_0222FD62:
	ldr r0, _0222FDF0 ; =0x000004FC
	ldr r5, [r3]
	add r0, r3, r0
	ldr r3, _0222FDF4 ; =0x00000127
	sub r2, r3, #4
	ldrb r1, [r5, r3]
	sub r3, #0xb
	ldrb r2, [r5, r2]
	ldrb r3, [r5, r3]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222FDE6
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222FDE6
_0222FD84:
	ldr r1, [r3]
	ldr r0, _0222FDF8 ; =0x00000121
	ldrb r0, [r1, r0]
	cmp r0, #2
	bne _0222FD92
	mov r1, #7
	b _0222FD94
_0222FD92:
	mov r1, #0
_0222FD94:
	add r0, r3, #0
	add r0, #0xe9
	strb r1, [r0]
	add r0, r3, #0
	mov r1, #0
	add r0, #0xea
	strb r1, [r0]
	add r0, r3, #0
	add r0, #0xeb
	strb r1, [r0]
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
_0222FDAE:
	ldr r0, _0222FDF0 ; =0x000004FC
	add r1, r3, #0
	add r0, r3, r0
	mov r2, #0xd
	add r3, #0xe2
	bl MOD12_02241050
	cmp r0, #1
	bne _0222FDE6
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222FDE6
_0222FDC8:
	ldr r0, _0222FDF0 ; =0x000004FC
	ldr r4, [r3]
	add r0, r3, r0
	ldr r3, _0222FDF4 ; =0x00000127
	sub r2, r3, #4
	ldrb r1, [r4, r3]
	sub r3, #0xb
	ldrb r2, [r4, r2]
	ldrb r3, [r4, r3]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222FDE6
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222FDE6:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_0222FDEC: .word 0x000006E5
_0222FDF0: .word 0x000004FC
_0222FDF4: .word 0x00000127
_0222FDF8: .word 0x00000121

	thumb_func_start MOD12_0222FDFC
MOD12_0222FDFC: ; 0x0222FDFC
	push {r4, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	ldr r0, _0222FE44 ; =0x000004FC
	bne _0222FE22
	add r0, r2, r0
	add r1, r2, #0
	mov r2, #1
	mov r3, #0
	bl MOD12_02241050
	cmp r0, #1
	bne _0222FE3E
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _0222FE3E
_0222FE22:
	ldr r3, [r2]
	ldr r4, _0222FE48 ; =0x00000127
	add r0, r2, r0
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _0222FE3E
	mov r0, #3
	pop {r4, pc}
_0222FE3E:
	mov r0, #0
	pop {r4, pc}
	nop
_0222FE44: .word 0x000004FC
_0222FE48: .word 0x00000127

	thumb_func_start MOD12_0222FE4C
MOD12_0222FE4C: ; 0x0222FE4C
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r1, #1
	lsl r1, r1, #0x1a
	ldr r0, [r1]
	ldr r2, _022300E0 ; =0xFFFFE0FF
	and r0, r2
	str r0, [r1]
	ldr r0, _022300E4 ; =0x04001000
	ldr r3, [r0]
	and r2, r3
	str r2, [r0]
	ldr r3, [r1]
	ldr r2, _022300E8 ; =0xFFFF1FFF
	and r3, r2
	str r3, [r1]
	ldr r3, [r0]
	add r1, #0x50
	and r2, r3
	str r2, [r0]
	mov r2, #0
	strh r2, [r1]
	add r0, #0x50
	strh r2, [r0]
	mov r2, #0xa
	mov r0, #3
	mov r1, #0x17
	lsl r2, r2, #0x10
	bl FUN_0201681C
	ldr r1, _022300EC ; =0x00001BF4
	add r0, r4, #0
	mov r2, #0x17
	bl OverlayManager_CreateAndGetData
	ldr r2, _022300EC ; =0x00001BF4
	mov r1, #0
	add r5, r0, #0
	bl MI_CpuFill8
	mov r0, #0x17
	bl MOD12_022312D8
	str r0, [r5, #0x10]
	add r0, r4, #0
	bl OverlayManager_GetField18
	mov r1, #0x5b
	str r0, [r5]
	lsl r1, r1, #2
	str r5, [r0, r1]
	ldr r2, [r5]
	mov r3, #1
	add r0, r1, #4
	strb r3, [r2, r0]
	ldr r0, [r5]
	str r0, [r5, #0x14]
	add r0, r5, #0
	bl MOD12_022306F8
	mov r0, #0x17
	bl FUN_02002FD0
	add r1, r5, #0
	add r1, #0xa4
	str r0, [r1]
	add r0, r5, #0
	add r0, #0xa4
	ldr r0, [r0]
	mov r1, #1
	bl FUN_020038F0
	add r0, r5, #0
	add r0, #0xa4
	mov r2, #2
	ldr r0, [r0]
	mov r1, #0
	lsl r2, r2, #8
	mov r3, #0x17
	bl FUN_02003008
	add r0, r5, #0
	add r0, #0xa4
	mov r1, #1
	ldr r0, [r0]
	lsl r2, r1, #9
	mov r3, #0x17
	bl FUN_02003008
	add r0, r5, #0
	add r0, #0xa4
	mov r2, #7
	ldr r0, [r0]
	mov r1, #2
	lsl r2, r2, #6
	mov r3, #0x17
	bl FUN_02003008
	add r0, r5, #0
	add r0, #0xa4
	mov r2, #2
	ldr r0, [r0]
	mov r1, #3
	lsl r2, r2, #8
	mov r3, #0x17
	bl FUN_02003008
	mov r1, #2
	mov r0, #0x17
	lsl r1, r1, #8
	bl AllocFromHeap
	ldr r1, _022300F0 ; =0x0000110C
	str r0, [r5, r1]
	add r0, r5, #0
	mov r1, #1
	bl MOD12_0223EC7C
	mov r0, #0x17
	bl FUN_02016B94
	str r0, [r5, #0x74]
	mov r0, #0x40
	mov r1, #0x17
	bl FUN_0201C24C
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	add r1, r5, #0
	ldr r0, [r5]
	add r1, #0x14
	bl MOD12_0223B49C
	ldr r1, _022300F4 ; =0x00001130
	str r0, [r5, r1]
	ldr r0, [r5, #0x74]
	bl MOD12_02230574
	bl FUN_0201CC08
	mov r0, #4
	bl FUN_0201CC24
	mov r0, #2
	mov r1, #0x17
	bl FUN_02002C50
	mov r0, #0x17
	bl FUN_0200BB14
	ldr r1, _022300F8 ; =MOD12_02244C18
	ldr r2, _022300FC ; =MOD12_02244BD4
	mov r3, #0x20
	str r0, [r5, #0x6c]
	bl FUN_0200BB6C
	ldr r1, _02230100 ; =0x00100010
	mov r0, #1
	bl FUN_02008D44
	mov r0, #1
	bl FUN_02008DDC
	ldr r0, [r5, #0x6c]
	bl FUN_0200BB34
	str r0, [r5, #0x70]
	ldr r0, [r5, #0x6c]
	ldr r1, [r5, #0x70]
	mov r2, #0x80
	bl FUN_0200BBF0
	ldr r0, [r5, #0x6c]
	ldr r1, [r5, #0x70]
	ldr r2, _02230104 ; =MOD12_02244C00
	bl FUN_0200BF60
	ldr r0, [r5, #0x6c]
	bl FUN_0200BB68
	mov r2, #1
	mov r1, #0
	lsl r2, r2, #0x14
	bl FUN_02008D24
	mov r0, #0x17
	bl FUN_02006D98
	str r0, [r5, #0x58]
	bl MOD12_022306F0
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0xc1
	mov r3, #0x17
	bl NewMsgDataFromNarc
	add r1, r5, #0
	add r1, #0x98
	str r0, [r1]
	mov r0, #0x17
	bl ScrStrBufs_new
	add r1, r5, #0
	add r1, #0x9c
	str r0, [r1]
	mov r0, #5
	lsl r0, r0, #6
	mov r1, #0x17
	bl String_ctor
	add r1, r5, #0
	add r1, #0xa0
	str r0, [r1]
	mov r0, #9
	mov r1, #0x17
	bl FUN_02011744
	add r1, r5, #0
	add r1, #0xa8
	str r0, [r1]
	add r0, r5, #0
	bl MOD12_022308F0
	add r0, r5, #0
	bl MOD12_022309D0
	add r0, r5, #0
	bl MOD12_022306A4
	add r0, r5, #0
	bl MOD12_02230750
	add r0, r5, #0
	bl MOD12_02230880
	ldr r0, _022300F4 ; =0x00001130
	mov r1, #0
	ldr r0, [r5, r0]
	mov r2, #1
	add r3, r1, #0
	bl MOD12_0223B758
	add r0, r5, #0
	bl MOD12_0223C248
	add r0, r5, #0
	add r0, #0x14
	bl MOD12_0223D0CC
	add r0, r5, #0
	bl MOD12_022309D8
	add r0, r5, #0
	bl MOD12_0223CAF8
	add r0, r5, #0
	bl MOD12_0223D55C
	bl FUN_02033E74
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r1, #0x17
	str r1, [sp, #8]
	mov r1, #0x11
	mov r2, #0x25
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, _02230108 ; =MOD12_02230520
	ldr r2, _0223010C ; =0x00013880
	add r1, r5, #0
	bl FUN_0200CA44
	str r0, [r5, #4]
	ldr r0, _02230110 ; =0x00001154
	mov r1, #1
	strb r1, [r5, r0]
	bl GX_BothDispOn
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	ldr r1, _02230114 ; =0x0000046F
	mov r0, #6
	mov r2, #1
	bl FUN_0200433C
	ldr r1, [r5]
	ldr r0, _02230118 ; =0x00000171
	ldrb r0, [r1, r0]
	bl FUN_020833D4
	mov r1, #0x39
	add r2, r1, #0
	ldr r0, _0223011C ; =0x04000050
	sub r2, #0x3f
	bl G2x_SetBlendBrightness_
	ldr r0, _02230120 ; =0x000006E5
	bl FUN_020054C8
	ldr r0, _02230124 ; =MOD12_022303C0
	add r1, r5, #0
	bl Main_SetVBlankIntrCB
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_022300E0: .word 0xFFFFE0FF
_022300E4: .word 0x04001000
_022300E8: .word 0xFFFF1FFF
_022300EC: .word 0x00001BF4
_022300F0: .word 0x0000110C
_022300F4: .word 0x00001130
_022300F8: .word MOD12_02244C18
_022300FC: .word MOD12_02244BD4
_02230100: .word 0x00100010
_02230104: .word MOD12_02244C00
_02230108: .word MOD12_02230520
_0223010C: .word 0x00013880
_02230110: .word 0x00001154
_02230114: .word 0x0000046F
_02230118: .word 0x00000171
_0223011C: .word 0x04000050
_02230120: .word 0x000006E5
_02230124: .word MOD12_022303C0

	thumb_func_start MOD12_02230128
MOD12_02230128: ; 0x02230128
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_02082878
	ldr r0, [r5]
	cmp r0, #0
	beq _0223014A
	cmp r0, #1
	beq _02230158
	cmp r0, #2
	beq _0223020E
	b _0223021C
_0223014A:
	bl FUN_0200E308
	cmp r0, #1
	bne _0223021C
	mov r0, #1
	str r0, [r5]
	b _0223021C
_02230158:
	ldr r0, [r4]
	bl FUN_020828BC
	cmp r0, #1
	bne _022301CA
	ldr r2, _02230224 ; =0x00001152
	ldr r1, _02230228 ; =0x00001BE8
	ldrh r2, [r4, r2]
	add r0, r4, #0
	add r1, r4, r1
	lsl r3, r2, #2
	ldr r2, _0223022C ; =MOD12_02244C60
	ldr r2, [r2, r3]
	blx r2
	sub r1, r0, #1
	cmp r1, #1
	bhi _0223019C
	cmp r0, #1
	bne _02230186
	ldr r0, _02230224 ; =0x00001152
	ldrh r1, [r4, r0]
	add r1, r1, #1
	b _0223018C
_02230186:
	ldr r0, _02230230 ; =0x00001BEA
	ldrh r1, [r4, r0]
	ldr r0, _02230224 ; =0x00001152
_0223018C:
	strh r1, [r4, r0]
	ldr r0, _02230228 ; =0x00001BE8
	mov r1, #0
	add r0, r4, r0
	mov r2, #8
	bl MI_CpuFill8
	b _022301CA
_0223019C:
	cmp r0, #3
	bne _022301CA
	mov r0, #2
	str r0, [r5]
	ldr r0, _02230228 ; =0x00001BE8
	mov r1, #0
	add r0, r4, r0
	mov r2, #8
	bl MI_CpuFill8
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x17
	mov r1, #0x1e
	str r0, [sp, #8]
	mov r0, #2
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	b _0223021C
_022301CA:
	ldr r0, _02230234 ; =0x00001158
	add r0, r4, r0
	bl MOD12_022410A0
	ldr r0, _02230234 ; =0x00001158
	add r1, r4, #0
	add r0, r4, r0
	bl MOD12_02241114
	ldr r0, _02230238 ; =0x00001BF0
	ldrb r1, [r4, r0]
	cmp r1, #1
	bne _0223021C
	mov r1, #2
	sub r0, #8
	str r1, [r5]
	add r0, r4, r0
	mov r1, #0
	mov r2, #8
	bl MI_CpuFill8
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x17
	mov r1, #0x1e
	str r0, [sp, #8]
	mov r0, #2
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	b _0223021C
_0223020E:
	bl FUN_0200E308
	cmp r0, #1
	bne _0223021C
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_0223021C:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_02230224: .word 0x00001152
_02230228: .word 0x00001BE8
_0223022C: .word MOD12_02244C60
_02230230: .word 0x00001BEA
_02230234: .word 0x00001158
_02230238: .word 0x00001BF0

	thumb_func_start MOD12_0223023C
MOD12_0223023C: ; 0x0223023C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl FUN_020133C8
	cmp r0, #0
	beq _02230254
	bl ErrorHandling
_02230254:
	add r0, r4, #0
	bl MOD12_02230A40
	bl FUN_02012EAC
	add r0, r4, #0
	add r0, #0x14
	bl MOD12_0223CA1C
	add r0, r4, #0
	bl MOD12_0223CB18
	add r0, r4, #0
	bl MOD12_0223D578
	add r0, r4, #0
	bl MOD12_0223DCC0
	add r0, r4, #0
	bl MOD12_02230808
	add r0, r4, #0
	bl MOD12_022308EC
	add r0, r4, #0
	bl MOD12_022309CC
	add r0, r4, #0
	bl MOD12_022309D4
	add r5, r4, #0
	mov r6, #0
	add r5, #0x78
_02230296:
	add r0, r5, #0
	bl FUN_02019178
	add r6, r6, #1
	add r5, #0x10
	cmp r6, #2
	blt _02230296
	mov r0, #1
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, [r4, #0x74]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #0x74]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #0x74]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #0x74]
	bl MOD12_0223B474
	ldr r0, _022303B0 ; =0x00001130
	ldr r0, [r4, r0]
	bl MOD12_0223B4C0
	ldr r0, [r4, #0x6c]
	ldr r1, [r4, #0x70]
	bl FUN_0200C398
	ldr r0, [r4, #0x6c]
	bl FUN_0200BD04
	bl FUN_0201C29C
	add r0, r4, #0
	add r0, #0x14
	bl MOD12_0223C300
	ldr r0, [r4, #0x58]
	bl FUN_020072E8
	add r0, r4, #0
	add r0, #0xa8
	ldr r0, [r0]
	bl FUN_020117BC
	mov r0, #2
	bl FUN_02002CF8
	ldr r0, _022303B4 ; =0x0000110C
	ldr r0, [r4, r0]
	bl FreeToHeap
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	mov r1, #0
	bl FUN_02003038
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	mov r1, #1
	bl FUN_02003038
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	mov r1, #2
	bl FUN_02003038
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	mov r1, #3
	bl FUN_02003038
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	bl FUN_02002FEC
	add r0, r4, #0
	add r0, #0xa0
	ldr r0, [r0]
	bl String_dtor
	add r0, r4, #0
	add r0, #0x9c
	ldr r0, [r0]
	bl ScrStrBufs_delete
	add r0, r4, #0
	add r0, #0x98
	ldr r0, [r0]
	bl DestroyMsgData
	ldr r0, [r4, #0x74]
	bl FreeToHeap
	ldr r0, [r4, #4]
	bl FUN_0200CAB4
	ldr r0, [r4, #0x10]
	bl MOD12_02231378
	bl FUN_0201CD04
	add r0, r7, #0
	bl OverlayManager_FreeData
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	mov r0, #0x17
	bl FUN_020168D0
	bl FUN_02083404
	bl FUN_02033ED0
	ldr r0, _022303B8 ; =SDK_OVERLAY_MODULE_08_ID
	bl UnloadOverlayByID
	ldr r0, _022303BC ; =SDK_OVERLAY_MODULE_17_ID
	bl UnloadOverlayByID
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022303B0: .word 0x00001130
_022303B4: .word 0x0000110C
_022303B8: .word SDK_OVERLAY_MODULE_08_ID
_022303BC: .word SDK_OVERLAY_MODULE_17_ID

	thumb_func_start MOD12_022303C0
MOD12_022303C0: ; 0x022303C0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldr r0, _02230494 ; =0x00001134
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _02230450
	add r1, r0, #4
	add r3, r4, r1
	ldr r2, [r4, r1]
	mov r5, #0
	ldr r1, [r3, #4]
	add r2, r2, #1
	adc r1, r5
	add r0, r0, #4
	str r2, [r4, r0]
	mov r0, #7
	str r1, [r3, #4]
	bl FUN_02004F64
	ldr r1, _02230498 ; =0x00000AF8
	ldr r1, [r4, r1]
	mul r0, r1
	ldr r1, _0223049C ; =0x00001388
	add r0, r0, r1
	lsl r1, r1, #1
	bl _u32_div_f
	ldr r7, _022304A0 ; =0x0000114C
	add r5, r0, #1
	add r1, r7, #0
	str r0, [r4, r7]
	sub r1, #0x14
	ldr r2, [r4, r1]
	add r1, r7, #0
	sub r1, #0x10
	add r0, r5, #0
	ldr r6, [r4, r1]
	mov r3, #0
	add r1, r3, #0
	eor r1, r6
	eor r0, r2
	orr r0, r1
	beq _0223044C
	sub r0, r7, #4
	ldr r0, [r4, r0]
	cmp r0, #0x12
	bhi _02230430
	mov ip, r3
	mov r0, ip
	sub r1, r5, r2
	sbc r0, r6
	mov r6, #0
	mov r2, #1
	sub r1, r2, r1
	sbc r6, r0
	bhs _02230440
_02230430:
	ldr r1, _022304A4 ; =0x00001138
	str r5, [r4, r1]
	add r0, r1, #4
	str r3, [r4, r0]
	mov r0, #0
	add r1, #0x10
	str r0, [r4, r1]
	b _02230450
_02230440:
	sub r0, r7, #4
	ldr r0, [r4, r0]
	add r1, r0, #1
	sub r0, r7, #4
	str r1, [r4, r0]
	b _02230450
_0223044C:
	sub r0, r7, #4
	str r3, [r4, r0]
_02230450:
	ldr r0, [r4, #0x58]
	bl FUN_020081C4
	mov r6, #0
	add r5, r4, #0
_0223045A:
	ldr r0, [r5, #0x18]
	cmp r0, #0
	beq _02230464
	bl MOD17_021DD58C
_02230464:
	add r6, r6, #1
	add r5, #0x10
	cmp r6, #4
	blt _0223045A
	bl FUN_0201C30C
	bl FUN_0200BC30
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	bl FUN_0200372C
	ldr r0, [r4, #0x74]
	bl FUN_0201AB60
	ldr r3, _022304A8 ; =0x027E0000
	ldr r1, _022304AC ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02230494: .word 0x00001134
_02230498: .word 0x00000AF8
_0223049C: .word 0x00001388
_022304A0: .word 0x0000114C
_022304A4: .word 0x00001138
_022304A8: .word 0x027E0000
_022304AC: .word 0x00003FF8

	thumb_func_start MOD12_022304B0
MOD12_022304B0: ; 0x022304B0
	push {r3, r4, r5, lr}
	ldr r1, _0223051C ; =0x0000110C
	add r5, r0, r1
	ldrb r1, [r5, #0x11]
	cmp r1, #0
	beq _02230518
	add r0, #0xa4
	ldr r0, [r0]
	mov r1, #0
	bl FUN_02003204
	add r4, r0, #0
	mov r2, #2
	ldr r0, [r5]
	add r1, r4, #0
	lsl r2, r2, #8
	bl MIi_CpuCopy16
	ldrb r0, [r5, #0x10]
	cmp r0, #1
	bne _02230518
	ldrh r0, [r5, #0xe]
	add r1, r4, #0
	str r0, [sp]
	ldrh r3, [r5, #8]
	ldrh r2, [r5, #6]
	ldr r0, [r5]
	asr r3, r3, #8
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FUN_02003A30
	ldrh r3, [r5, #0xa]
	ldrh r1, [r5, #8]
	cmp r1, r3
	bne _022304FE
	mov r0, #0
	strb r0, [r5, #0x10]
	pop {r3, r4, r5, pc}
_022304FE:
	mov r0, #0xc
	ldrsh r2, [r5, r0]
	add r0, r1, r2
	cmp r2, #0
	ble _0223050C
	cmp r0, r3
	bge _02230514
_0223050C:
	cmp r2, #0
	bge _02230516
	cmp r0, r3
	bgt _02230516
_02230514:
	add r0, r3, #0
_02230516:
	strh r0, [r5, #8]
_02230518:
	pop {r3, r4, r5, pc}
	nop
_0223051C: .word 0x0000110C

	thumb_func_start MOD12_02230520
MOD12_02230520: ; 0x02230520
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl MOD12_022304B0
	ldr r0, _0223056C ; =0x00001154
	ldrb r0, [r6, r0]
	cmp r0, #1
	bne _02230562
	ldr r0, [r6, #0x58]
	bl FUN_02006ED4
	mov r4, #0
	add r5, r6, #0
_0223053C:
	ldr r0, [r5, #0x18]
	cmp r0, #0
	beq _02230546
	bl MOD17_021DD518
_02230546:
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #4
	blt _0223053C
	bl MOD08_02215A44
	ldr r0, [r6, #0x70]
	bl FUN_0200BC1C
	bl FUN_0200BC38
	ldr r0, _02230570 ; =0x04000540
	mov r1, #1
	str r1, [r0]
_02230562:
	ldr r1, [r6, #0x74]
	mov r0, #0x17
	bl FUN_020335F0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223056C: .word 0x00001154
_02230570: .word 0x04000540

	thumb_func_start MOD12_02230574
MOD12_02230574: ; 0x02230574
	push {r4, r5, lr}
	sub sp, #0x8c
	add r4, r0, #0
	bl GX_DisableEngineALayers
	ldr r5, _02230694 ; =MOD12_02244C38
	add r3, sp, #0x10
	mov r2, #5
_02230584:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02230584
	add r0, sp, #0x10
	bl GX_SetBanks
	mov r1, #6
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x18
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x62
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	mov r1, #0x19
	mov r2, #1
	mov r0, #0
	lsl r1, r1, #0x16
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x66
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	ldr r5, _02230698 ; =MOD12_02244BC4
	add r3, sp, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _0223069C ; =MOD12_02244C94
	add r3, sp, #0x38
	mov r2, #0xa
_022305E4:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _022305E4
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	add r2, sp, #0x38
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	mov r2, #0
	add r0, r4, #0
	mov r1, #1
	add r3, r2, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #1
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #2
	add r2, sp, #0x54
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #2
	bl FUN_02018744
	mov r2, #0
	add r0, r4, #0
	mov r1, #2
	add r3, r2, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #2
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #3
	add r2, sp, #0x70
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #3
	bl FUN_02018744
	mov r2, #0
	add r0, r4, #0
	mov r1, #3
	add r3, r2, #0
	bl FUN_020179E0
	mov r1, #3
	add r0, r4, #0
	add r2, r1, #0
	mov r3, #0
	bl FUN_020179E0
	ldr r1, _022306A0 ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #2
	orr r0, r2
	strh r0, [r1]
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	add r0, r4, #0
	bl MOD12_0223B41C
	add sp, #0x8c
	pop {r4, r5, pc}
	.align 2, 0
_02230694: .word MOD12_02244C38
_02230698: .word MOD12_02244BC4
_0223069C: .word MOD12_02244C94
_022306A0: .word 0x04000008

	thumb_func_start MOD12_022306A4
MOD12_022306A4: ; 0x022306A4
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x1f
	str r0, [sp, #0x10]
	add r1, r4, #0
	ldr r0, [r4, #0x74]
	add r1, #0x78
	mov r2, #1
	mov r3, #2
	bl FUN_02019064
	mov r0, #0xb
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r3, #2
	str r3, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x1f
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x74]
	add r4, #0x88
	add r1, r4, #0
	mov r2, #1
	bl FUN_02019064
	add sp, #0x14
	pop {r3, r4, pc}

	thumb_func_start MOD12_022306F0
MOD12_022306F0: ; 0x022306F0
	ldr r3, _022306F4 ; =FUN_02012CC8
	bx r3
	.align 2, 0
_022306F4: .word FUN_02012CC8

	thumb_func_start MOD12_022306F8
MOD12_022306F8: ; 0x022306F8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	cmp r0, #0
	bne _02230706
	bl ErrorHandling
_02230706:
	mov r4, #0xad
	lsl r4, r4, #4
	mov r1, #0
	mov r2, #3
	add r6, r4, #5
_02230710:
	sub r3, r2, r1
	lsl r3, r3, #0x18
	add r0, r5, r1
	lsr r3, r3, #0x18
	strb r3, [r0, r4]
	add r1, r1, #1
	strb r3, [r0, r6]
	cmp r1, #4
	blt _02230710
	add r0, r5, #0
	bl MOD12_0223EE80
	mov r4, #0
	ldr r7, _0223074C ; =0x00000AB4
	add r6, r4, #0
_0223072E:
	ldr r0, [r5]
	mov r1, #5
	ldr r0, [r0, r6]
	mov r2, #0
	bl GetMonData
	bl MOD12_0223EE70
	add r1, r5, r4
	add r4, r4, #1
	add r6, r6, #4
	strb r0, [r1, r7]
	cmp r4, #4
	blt _0223072E
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223074C: .word 0x00000AB4

	thumb_func_start MOD12_02230750
MOD12_02230750: ; 0x02230750
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0
	mov r0, #0x2e
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, _02230804 ; =0x000080E9
	mov r1, #2
	str r0, [sp, #0x14]
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	ldr r2, [r4, #0x6c]
	ldr r3, [r4, #0x70]
	bl FUN_0200C0DC
	ldr r0, [r4, #0x6c]
	ldr r1, [r4, #0x70]
	bl MOD12_0223C320
	ldr r0, [r4, #0x6c]
	ldr r1, [r4, #0x70]
	bl MOD12_0223C450
	ldr r0, [r4, #0x6c]
	ldr r1, [r4, #0x70]
	bl MOD12_0223C668
	add r0, r4, #0
	ldr r1, [r4, #0x6c]
	ldr r2, [r4, #0x70]
	add r0, #0x14
	bl MOD12_0223C6DC
	add r0, r4, #0
	add r0, #0x14
	bl MOD12_0223C734
	ldr r0, [r4, #0x6c]
	ldr r1, [r4, #0x70]
	bl MOD12_0223CA44
	add r0, r4, #0
	ldr r1, [r4, #0x6c]
	ldr r2, [r4, #0x70]
	add r0, #0x14
	bl MOD12_0223CAB8
	ldr r0, [r4, #0x6c]
	ldr r1, [r4, #0x70]
	bl MOD12_0223E2B8
	ldr r1, [r4, #0x6c]
	ldr r2, [r4, #0x70]
	add r0, r4, #0
	bl MOD12_0223E32C
	ldr r0, [r4, #0x6c]
	ldr r1, [r4, #0x70]
	bl MOD12_0223CB54
	add r0, r4, #0
	ldr r1, [r4, #0x6c]
	ldr r2, [r4, #0x70]
	add r0, #0x14
	bl MOD12_0223CBC8
	ldr r0, [r4, #0x6c]
	ldr r1, [r4, #0x70]
	bl MOD12_0223CD40
	add r0, r4, #0
	ldr r1, [r4, #0x6c]
	ldr r2, [r4, #0x70]
	add r0, #0x14
	bl MOD12_0223CDB4
	ldr r0, [r4, #0x6c]
	ldr r1, [r4, #0x70]
	bl MOD12_0223CDBC
	add sp, #0x18
	pop {r4, pc}
	.align 2, 0
_02230804: .word 0x000080E9

	thumb_func_start MOD12_02230808
MOD12_02230808: ; 0x02230808
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x70]
	bl MOD12_0223C324
	ldr r0, [r4, #0x70]
	bl MOD12_0223C4E8
	add r0, r4, #0
	add r0, #0x14
	bl MOD12_0223C640
	ldr r0, [r4, #0x70]
	bl MOD12_0223C6B8
	add r0, r4, #0
	add r0, #0x14
	bl MOD12_0223C710
	add r0, r4, #0
	add r0, #0x14
	bl MOD12_0223C878
	ldr r0, [r4, #0x70]
	bl MOD12_0223CA94
	add r0, r4, #0
	add r0, #0x14
	bl MOD12_0223CADC
	add r0, r4, #0
	bl MOD12_0223E38C
	ldr r0, [r4, #0x70]
	bl MOD12_0223E308
	ldr r0, [r4, #0x70]
	bl MOD12_0223CBA4
	add r0, r4, #0
	add r0, #0x14
	bl MOD12_0223CC70
	ldr r0, [r4, #0x70]
	bl MOD12_0223CD90
	add r0, r4, #0
	add r0, #0x14
	bl MOD12_0223CDB8
	ldr r0, [r4, #0x70]
	bl MOD12_0223CE0C
	ldr r0, [r4, #0x70]
	ldr r1, _0223087C ; =0x000080E9
	bl FUN_0200C368
	pop {r4, pc}
	.align 2, 0
_0223087C: .word 0x000080E9

	thumb_func_start MOD12_02230880
MOD12_02230880: ; 0x02230880
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0
	mov r0, #0x2e
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, _022308E0 ; =0x000080EA
	mov r1, #3
	str r0, [sp, #0x14]
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	ldr r2, [r4, #0x6c]
	ldr r3, [r4, #0x70]
	bl FUN_0200C0DC
	mov r0, #0x2e
	str r0, [sp]
	mov r0, #9
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, _022308E4 ; =0x000080EB
	mov r1, #3
	str r0, [sp, #0x14]
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	ldr r2, [r4, #0x6c]
	ldr r3, [r4, #0x70]
	bl FUN_0200C0DC
	ldr r0, _022308E8 ; =0x00001130
	ldr r0, [r4, r0]
	bl MOD12_0223B4E0
	add sp, #0x18
	pop {r4, pc}
	.align 2, 0
_022308E0: .word 0x000080EA
_022308E4: .word 0x000080EB
_022308E8: .word 0x00001130

	thumb_func_start MOD12_022308EC
MOD12_022308EC: ; 0x022308EC
	bx lr
	.align 2, 0

	thumb_func_start MOD12_022308F0
MOD12_022308F0: ; 0x022308F0
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x17
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x74]
	mov r0, #0x2d
	mov r1, #0xd
	mov r3, #3
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x17
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x74]
	mov r0, #0x2d
	mov r1, #0xe
	mov r3, #3
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xa4
	ldr r0, [r0]
	mov r1, #0x2d
	mov r2, #0x1f
	mov r3, #0x17
	bl FUN_020030E8
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xd0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xa4
	ldr r0, [r0]
	mov r1, #0x2d
	mov r2, #0x23
	mov r3, #0x17
	bl FUN_020030E8
	ldr r1, [r5]
	ldr r0, _022309C4 ; =0x00001988
	ldr r0, [r1, r0]
	bl Options_GetFrame
	add r4, r0, #0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x17
	str r0, [sp, #4]
	mov r1, #1
	ldr r0, [r5, #0x74]
	add r2, r1, #0
	mov r3, #0xf
	bl FUN_0200CD68
	add r0, r4, #0
	bl FUN_0200CD64
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xe0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xa4
	ldr r0, [r0]
	mov r1, #0x26
	mov r3, #0x17
	bl FUN_020030E8
	add r0, r5, #0
	bl MOD12_0223E734
	add r0, r5, #0
	add r0, #0xa4
	ldr r0, [r0]
	mov r1, #0
	bl FUN_020031FC
	ldr r1, _022309C8 ; =0x0000110C
	mov r2, #2
	ldr r1, [r5, r1]
	lsl r2, r2, #8
	bl MIi_CpuCopy16
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_022309C4: .word 0x00001988
_022309C8: .word 0x0000110C

	thumb_func_start MOD12_022309CC
MOD12_022309CC: ; 0x022309CC
	bx lr
	.align 2, 0

	thumb_func_start MOD12_022309D0
MOD12_022309D0: ; 0x022309D0
	bx lr
	.align 2, 0

	thumb_func_start MOD12_022309D4
MOD12_022309D4: ; 0x022309D4
	bx lr
	.align 2, 0

	thumb_func_start MOD12_022309D8
MOD12_022309D8: ; 0x022309D8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _022309E8
	bl ErrorHandling
_022309E8:
	mov r1, #0x12
	mov r0, #0x17
	lsl r1, r1, #0xa
	bl AllocFromHeap
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #0x17
	str r0, [sp, #4]
	mov r3, #0x12
	ldr r0, _02230A38 ; =MOD12_02230A60
	ldr r1, _02230A3C ; =MOD12_02230A7C
	lsl r3, r3, #0xa
	bl FUN_02012CDC
	str r0, [r4, #0xc]
	bl FUN_0201343C
	add r2, r0, #0
	mov r0, #1
	mov r1, #0xe1
	lsl r0, r0, #0xc
	lsl r1, r1, #0xe
	bl FUN_0201EC94
	mov r0, #0x3d
	mov r1, #3
	mov r2, #0x17
	bl FUN_0201318C
	add r1, r0, #0
	ldr r0, [r4, #0xc]
	mov r2, #0xa
	mov r3, #1
	bl FUN_02013194
	add sp, #8
	pop {r4, pc}
	nop
_02230A38: .word MOD12_02230A60
_02230A3C: .word MOD12_02230A7C

	thumb_func_start MOD12_02230A40
MOD12_02230A40: ; 0x02230A40
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl FUN_020133E8
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	bl FUN_02012DE4
	add r0, r5, #0
	bl FreeToHeap
	mov r0, #0
	str r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_02230A60
MOD12_02230A60: ; 0x02230A60
	push {r4, lr}
	ldr r3, _02230A78 ; =UNK_021064B8
	mov r2, #0
	ldr r3, [r3]
	blx r3
	add r4, r0, #0
	bl FUN_0201327C
	lsl r0, r4, #0x10
	lsr r0, r0, #0xd
	pop {r4, pc}
	nop
_02230A78: .word UNK_021064B8

	thumb_func_start MOD12_02230A7C
MOD12_02230A7C: ; 0x02230A7C
	push {r4, lr}
	ldr r3, _02230A94 ; =UNK_021064C0
	mov r2, #0
	ldr r3, [r3]
	blx r3
	add r4, r0, #0
	bl FUN_020132BC
	lsl r0, r4, #0x10
	lsr r0, r0, #0xd
	pop {r4, pc}
	nop
_02230A94: .word UNK_021064C0

	thumb_func_start MOD12_02230A98
MOD12_02230A98: ; 0x02230A98
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	ldr r0, _02230AE4 ; =0x00001158
	bne _02230AC2
	mov r3, #0xad
	lsl r3, r3, #4
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #0xa
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _02230ADE
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02230ADE
_02230AC2:
	ldr r4, _02230AE8 ; =0x00000127
	ldr r3, [r5]
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	add r0, r5, r0
	bl MOD12_022411F4
	cmp r0, #1
	bne _02230ADE
	mov r0, #1
	pop {r3, r4, r5, pc}
_02230ADE:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02230AE4: .word 0x00001158
_02230AE8: .word 0x00000127

	thumb_func_start MOD12_02230AEC
MOD12_02230AEC: ; 0x02230AEC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	beq _02230AFE
	cmp r0, #1
	beq _02230B52
	b _02230B74
_02230AFE:
	ldr r0, _02230B7C ; =0x00000B37
	mov r2, #0
	strb r2, [r5, r0]
	add r1, r0, #1
	strb r2, [r5, r1]
	ldr r2, [r5]
	ldr r1, _02230B80 ; =0x00000123
	sub r0, r0, #7
	ldrb r2, [r2, r1]
	strb r2, [r5, r0]
	ldr r2, [r5]
	sub r0, r1, #3
	ldrb r0, [r2, r0]
	bl MOD12_0223E464
	ldr r1, _02230B84 ; =0x00000B34
	strb r0, [r5, r1]
	ldr r0, [r5]
	bl FUN_020832EC
	cmp r0, #1
	bne _02230B2E
	mov r1, #2
	b _02230B30
_02230B2E:
	mov r1, #1
_02230B30:
	ldr r0, _02230B88 ; =0x00000B36
	mov r3, #0xb
	strb r1, [r5, r0]
	ldr r0, _02230B8C ; =0x00001158
	lsl r3, r3, #8
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #9
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _02230B78
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02230B78
_02230B52:
	ldr r0, _02230B8C ; =0x00001158
	ldr r3, [r5]
	add r0, r5, r0
	ldr r5, _02230B90 ; =0x00000127
	sub r2, r5, #4
	ldrb r1, [r3, r5]
	sub r5, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r5]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02230B78
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02230B78
_02230B74:
	mov r0, #1
	pop {r3, r4, r5, pc}
_02230B78:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02230B7C: .word 0x00000B37
_02230B80: .word 0x00000123
_02230B84: .word 0x00000B34
_02230B88: .word 0x00000B36
_02230B8C: .word 0x00001158
_02230B90: .word 0x00000127

	thumb_func_start MOD12_02230B94
MOD12_02230B94: ; 0x02230B94
	push {r4, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	ldr r0, _02230BDC ; =0x00001158
	bne _02230BBA
	add r0, r2, r0
	add r1, r2, #0
	mov r2, #3
	mov r3, #0
	bl MOD12_02241050
	cmp r0, #1
	bne _02230BD6
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02230BD6
_02230BBA:
	ldr r3, [r2]
	ldr r4, _02230BE0 ; =0x00000127
	add r0, r2, r0
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02230BD6
	mov r0, #1
	pop {r4, pc}
_02230BD6:
	mov r0, #0
	pop {r4, pc}
	nop
_02230BDC: .word 0x00001158
_02230BE0: .word 0x00000127

	thumb_func_start MOD12_02230BE4
MOD12_02230BE4: ; 0x02230BE4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldrh r0, [r5]
	cmp r0, #4
	bls _02230BF2
	b _02230D7C
_02230BF2:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02230BFE: ; jump table
	.short _02230C08 - _02230BFE - 2 ; case 0
	.short _02230CFE - _02230BFE - 2 ; case 1
	.short _02230D1C - _02230BFE - 2 ; case 2
	.short _02230D3E - _02230BFE - 2 ; case 3
	.short _02230D5A - _02230BFE - 2 ; case 4
_02230C08:
	mov r0, #0x12
	ldr r1, [r4]
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _02230C18
	cmp r0, #1
	bne _02230C1C
_02230C18:
	mov r1, #0
	b _02230C1E
_02230C1C:
	mov r1, #1
_02230C1E:
	mov r0, #0xc
	add r6, r1, #0
	mul r6, r0
	ldr r0, _02230D84 ; =MOD12_02244BE8
	add r1, r0, r6
	mov r0, #0xab
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r0, _02230D88 ; =MOD12_02244BE8 + 2
	ldrh r7, [r0, r6]
	ldr r0, _02230D8C ; =0x0112A880
	add r1, r7, #0
	bl _s32_div_f
	ldr r1, _02230D90 ; =0x00000AE8
	mov r3, #0
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	ldr r2, _02230D94 ; =0x00001388
	lsl r0, r0, #4
	mov ip, r3
	mov r1, ip
	add r0, r0, r2
	adc r1, r3
	lsl r2, r2, #1
	bl _ll_udiv
	ldr r1, _02230D98 ; =0x00000AEC
	str r0, [r4, r1]
	add r0, r1, #0
	add r0, #0x10
	strh r7, [r4, r0]
	sub r0, r1, #4
	ldr r2, [r4, r0]
	ldr r0, _02230D9C ; =MOD12_02244BE8 + 6
	add r3, r2, #0
	ldrb r0, [r0, r6]
	mul r3, r0
	add r0, r1, #4
	str r3, [r4, r0]
	sub r0, r1, #4
	ldr r2, [r4, r0]
	ldr r0, _02230DA0 ; =MOD12_02244BE8 + 7
	add r3, r2, #0
	ldrb r0, [r0, r6]
	mul r3, r0
	add r0, r1, #0
	add r0, #8
	str r3, [r4, r0]
	sub r0, r1, #4
	ldr r0, [r4, r0]
	mov r1, #0x30
	bl _u32_div_f
	ldr r1, _02230DA4 ; =0x00000AF8
	str r0, [r4, r1]
	ldr r0, _02230DA8 ; =MOD12_02244BE8 + 5
	ldrb r2, [r0, r6]
	add r0, r1, #6
	strb r2, [r4, r0]
	ldr r0, _02230D84 ; =MOD12_02244BE8
	ldrh r2, [r0, r6]
	add r0, r1, #0
	sub r0, #0x14
	str r2, [r4, r0]
	add r0, r1, #0
	sub r0, #0x48
	ldr r0, [r4, r0]
	add r2, r1, #0
	ldrh r3, [r0]
	add r2, #0x2c
	strh r3, [r4, r2]
	add r2, r1, #0
	ldrh r3, [r0, #2]
	add r2, #0x2e
	strh r3, [r4, r2]
	add r2, r1, #0
	ldrh r3, [r0, #4]
	add r2, #0x30
	strh r3, [r4, r2]
	add r2, r1, #0
	ldrh r3, [r0, #6]
	add r2, #0x32
	strh r3, [r4, r2]
	add r2, r1, #0
	ldrh r3, [r0, #8]
	add r2, #0x34
	strh r3, [r4, r2]
	ldrh r2, [r0, #0xa]
	add r0, r1, #0
	add r0, #0x36
	strh r2, [r4, r0]
	add r0, r1, #0
	sub r0, #0x10
	ldr r2, [r4, r0]
	add r0, r1, #0
	add r0, #0x10
	str r2, [r4, r0]
	add r0, r1, #0
	sub r0, #0xc
	ldr r2, [r4, r0]
	add r0, r1, #0
	add r0, #0x14
	str r2, [r4, r0]
	add r0, r1, #4
	ldrh r0, [r4, r0]
	add r1, #0x18
	strh r0, [r4, r1]
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _02230D80
_02230CFE:
	ldr r0, _02230DAC ; =0x00001158
	mov r3, #0xad
	lsl r3, r3, #4
	add r0, r4, r0
	add r1, r4, #0
	mov r2, #0xa
	add r3, r4, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _02230D80
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _02230D80
_02230D1C:
	ldr r0, _02230DAC ; =0x00001158
	ldr r3, [r4]
	add r0, r4, r0
	ldr r4, _02230DB0 ; =0x00000127
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02230D80
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _02230D80
_02230D3E:
	ldr r0, _02230DAC ; =0x00001158
	mov r2, #0xb
	lsl r3, r2, #8
	add r0, r4, r0
	add r1, r4, #0
	add r3, r4, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _02230D80
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _02230D80
_02230D5A:
	ldr r0, _02230DAC ; =0x00001158
	ldr r3, [r4]
	add r0, r4, r0
	ldr r4, _02230DB0 ; =0x00000127
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02230D80
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _02230D80
_02230D7C:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02230D80:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02230D84: .word MOD12_02244BE8
_02230D88: .word MOD12_02244BE8 + 2
_02230D8C: .word 0x0112A880
_02230D90: .word 0x00000AE8
_02230D94: .word 0x00001388
_02230D98: .word 0x00000AEC
_02230D9C: .word MOD12_02244BE8 + 6
_02230DA0: .word MOD12_02244BE8 + 7
_02230DA4: .word 0x00000AF8
_02230DA8: .word MOD12_02244BE8 + 5
_02230DAC: .word 0x00001158
_02230DB0: .word 0x00000127

	thumb_func_start MOD12_02230DB4
MOD12_02230DB4: ; 0x02230DB4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldrh r0, [r1]
	str r1, [sp]
	cmp r0, #0
	bne _02230E0E
	ldr r1, _02230E18 ; =0x00000AD4
	mov r4, #0
	ldrb r0, [r5, r1]
	add r2, r5, r0
	sub r0, r1, #4
	ldrb r0, [r2, r0]
	add r1, #0x2c
	strb r0, [r5, r1]
	ldr r0, _02230E1C ; =0x00000AD5
	add r1, r0, #0
	add r1, #0x2d
_02230DD6:
	add r3, r5, r4
	ldrb r2, [r3, r0]
	add r4, r4, #1
	cmp r4, #4
	strb r2, [r3, r1]
	blt _02230DD6
	ldr r1, [r5]
	ldr r0, _02230E20 ; =0x00000127
	ldrb r6, [r1, r0]
	cmp r6, #4
	bge _02230E02
	lsl r0, r6, #2
	ldr r7, _02230E24 ; =0x00000B14
	add r4, r5, r0
_02230DF2:
	ldr r0, [r5]
	bl FUN_02082878
	str r0, [r4, r7]
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _02230DF2
_02230E02:
	ldr r0, [sp]
	ldrh r0, [r0]
	add r1, r0, #1
	ldr r0, [sp]
	strh r1, [r0]
	b _02230E12
_02230E0E:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02230E12:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02230E18: .word 0x00000AD4
_02230E1C: .word 0x00000AD5
_02230E20: .word 0x00000127
_02230E24: .word 0x00000B14

	thumb_func_start MOD12_02230E28
MOD12_02230E28: ; 0x02230E28
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	ldr r0, _02230E74 ; =0x00001158
	bne _02230E52
	mov r3, #0xb
	lsl r3, r3, #8
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #7
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _02230E6E
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02230E6E
_02230E52:
	ldr r4, _02230E78 ; =0x00000127
	ldr r3, [r5]
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	add r0, r5, r0
	bl MOD12_022411F4
	cmp r0, #1
	bne _02230E6E
	mov r0, #1
	pop {r3, r4, r5, pc}
_02230E6E:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02230E74: .word 0x00001158
_02230E78: .word 0x00000127

	thumb_func_start MOD12_02230E7C
MOD12_02230E7C: ; 0x02230E7C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	ldr r0, _02230EC8 ; =0x00001158
	bne _02230EA6
	mov r3, #0xb
	lsl r3, r3, #8
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #5
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _02230EC2
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02230EC2
_02230EA6:
	ldr r4, _02230ECC ; =0x00000127
	ldr r3, [r5]
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	add r0, r5, r0
	bl MOD12_022411F4
	cmp r0, #1
	bne _02230EC2
	mov r0, #1
	pop {r3, r4, r5, pc}
_02230EC2:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02230EC8: .word 0x00001158
_02230ECC: .word 0x00000127

	thumb_func_start MOD12_02230ED0
MOD12_02230ED0: ; 0x02230ED0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	ldr r0, _02230F1C ; =0x00001158
	bne _02230EFA
	mov r3, #0xb
	lsl r3, r3, #8
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #8
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _02230F16
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02230F16
_02230EFA:
	ldr r4, _02230F20 ; =0x00000127
	ldr r3, [r5]
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	add r0, r5, r0
	bl MOD12_022411F4
	cmp r0, #1
	bne _02230F16
	mov r0, #1
	pop {r3, r4, r5, pc}
_02230F16:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02230F1C: .word 0x00001158
_02230F20: .word 0x00000127

	thumb_func_start MOD12_02230F24
MOD12_02230F24: ; 0x02230F24
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	bne _02230F76
	ldr r1, _02230F98 ; =0x00000AD4
	ldrb r0, [r5, r1]
	cmp r0, #3
	blo _02230F3C
	mov r0, #1
	pop {r3, r4, r5, pc}
_02230F3C:
	add r0, r1, #2
	ldrb r0, [r5, r0]
	add r1, #0x5c
	strb r0, [r5, r1]
	mov r0, #0x12
	ldr r1, [r5]
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	bl MOD12_0223E464
	ldr r3, _02230F9C ; =0x00000B34
	mov r1, #0
	strb r0, [r5, r3]
	add r0, r3, #2
	strb r1, [r5, r0]
	ldr r0, _02230FA0 ; =0x00001158
	sub r3, #0x34
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #6
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _02230F94
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02230F94
_02230F76:
	ldr r4, _02230FA4 ; =0x00000127
	ldr r3, [r5]
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	ldr r0, _02230FA0 ; =0x00001158
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	add r0, r5, r0
	bl MOD12_022411F4
	cmp r0, #1
	bne _02230F94
	mov r0, #1
	pop {r3, r4, r5, pc}
_02230F94:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02230F98: .word 0x00000AD4
_02230F9C: .word 0x00000B34
_02230FA0: .word 0x00001158
_02230FA4: .word 0x00000127

	thumb_func_start MOD12_02230FA8
MOD12_02230FA8: ; 0x02230FA8
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r3, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	beq _02230FBE
	cmp r0, #1
	beq _02230FE8
	cmp r0, #2
	beq _02231006
	b _02231028
_02230FBE:
	ldr r0, _0223104C ; =0x00000AD5
	ldr r1, _0223104C ; =0x00000AD5
	ldrb r7, [r3, r0]
	mov r6, #0
	add r0, r0, #1
_02230FC8:
	add r5, r3, r6
	ldrb r2, [r5, r0]
	add r6, r6, #1
	cmp r6, #3
	strb r2, [r5, r1]
	blt _02230FC8
	ldr r0, _02231050 ; =0x00000AD8
	strb r7, [r3, r0]
	sub r1, r0, #4
	ldrb r1, [r3, r1]
	sub r0, r0, #4
	add r1, r1, #1
	strb r1, [r3, r0]
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
_02230FE8:
	ldr r0, _02231054 ; =0x00001158
	mov r5, #0xad
	lsl r5, r5, #4
	add r0, r3, r0
	add r1, r3, #0
	mov r2, #0xa
	add r3, r3, r5
	bl MOD12_02241050
	cmp r0, #1
	bne _02231048
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02231048
_02231006:
	ldr r0, _02231054 ; =0x00001158
	ldr r5, [r3]
	add r0, r3, r0
	ldr r3, _02231058 ; =0x00000127
	sub r2, r3, #4
	ldrb r1, [r5, r3]
	sub r3, #0xb
	ldrb r2, [r5, r2]
	ldrb r3, [r5, r3]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02231048
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02231048
_02231028:
	ldr r1, _0223105C ; =0x00000AD4
	ldrb r0, [r3, r1]
	cmp r0, #4
	bhs _02231044
	add r0, r1, #0
	add r0, #0x2d
	ldrb r0, [r3, r0]
	add r1, #0x2d
	add r0, r0, #1
	strb r0, [r3, r1]
	mov r0, #4
	strh r0, [r4, #2]
	mov r0, #2
	pop {r3, r4, r5, r6, r7, pc}
_02231044:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02231048:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223104C: .word 0x00000AD5
_02231050: .word 0x00000AD8
_02231054: .word 0x00001158
_02231058: .word 0x00000127
_0223105C: .word 0x00000AD4

	thumb_func_start MOD12_02231060
MOD12_02231060: ; 0x02231060
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	beq _02231072
	cmp r0, #1
	beq _02231090
	b _022310B2
_02231072:
	ldr r0, _022310BC ; =0x00001158
	mov r3, #0xb
	lsl r3, r3, #8
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #0xc
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _022310B6
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _022310B6
_02231090:
	ldr r0, _022310BC ; =0x00001158
	ldr r3, [r5]
	add r0, r5, r0
	ldr r5, _022310C0 ; =0x00000127
	sub r2, r5, #4
	ldrb r1, [r3, r5]
	sub r5, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r5]
	bl MOD12_022411F4
	cmp r0, #1
	bne _022310B6
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _022310B6
_022310B2:
	mov r0, #1
	pop {r3, r4, r5, pc}
_022310B6:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_022310BC: .word 0x00001158
_022310C0: .word 0x00000127

	thumb_func_start MOD12_022310C4
MOD12_022310C4: ; 0x022310C4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r0, [sp]
	ldrh r0, [r1]
	str r1, [sp, #4]
	cmp r0, #0
	beq _022310DE
	cmp r0, #1
	beq _022311D4
	cmp r0, #2
	bne _022310DC
	b _022311FA
_022310DC:
	b _02231222
_022310DE:
	mov r1, #0
	mov r6, #0x4b
	ldr r2, [sp]
	ldr r5, _02231230 ; =0x00000ADA
	add r3, r1, #0
	lsl r6, r6, #2
_022310EA:
	ldr r4, [sp]
	ldrsh r0, [r2, r5]
	ldr r4, [r4]
	add r1, r1, #1
	add r4, r4, r3
	strh r0, [r4, r6]
	add r2, r2, #2
	add r3, #0xc
	cmp r1, #4
	blt _022310EA
	ldr r0, [sp]
	mov r1, #0
	ldr r0, [r0]
	add r2, sp, #0x1c
	bl MOD12_022435E4
	ldr r0, [sp]
	mov r1, #1
	ldr r0, [r0]
	add r2, sp, #0x14
	bl MOD12_022435E4
	mov r6, #0
	add r2, sp, #0x14
	add r3, sp, #0x1c
	add r4, sp, #0xc
	add r5, sp, #8
	add r7, r6, #0
_02231122:
	mov r0, #0
	ldrsh r1, [r3, r0]
	ldrsh r0, [r2, r7]
	strb r6, [r5]
	add r6, r6, #1
	add r0, r1, r0
	strh r0, [r4]
	add r2, r2, #2
	add r3, r3, #2
	add r4, r4, #2
	add r5, r5, #1
	cmp r6, #4
	blt _02231122
	mov r6, #0
	sub r7, r6, #2
_02231140:
	mov r3, #3
	cmp r6, #3
	bge _02231172
	add r4, sp, #0x10
	add r5, sp, #8
	add r4, #2
	add r5, #3
_0223114E:
	mov r0, #0
	ldrsh r0, [r4, r0]
	ldrsh r1, [r4, r7]
	cmp r1, r0
	bge _02231168
	strh r1, [r4]
	sub r1, r4, #2
	strh r0, [r1]
	sub r0, r5, #1
	ldrb r2, [r5]
	ldrb r1, [r0]
	strb r1, [r5]
	strb r2, [r0]
_02231168:
	sub r3, r3, #1
	sub r4, r4, #2
	sub r5, r5, #1
	cmp r3, r6
	bgt _0223114E
_02231172:
	add r6, r6, #1
	cmp r6, #3
	blt _02231140
	ldr r1, _02231234 ; =0x00000172
	mov r4, #0
	add r3, sp, #8
_0223117E:
	ldr r0, [sp]
	ldrb r2, [r3]
	ldr r0, [r0]
	add r3, r3, #1
	add r0, r0, r4
	add r4, r4, #1
	strb r2, [r0, r1]
	cmp r4, #4
	blt _0223117E
	ldr r2, _02231238 ; =0x00000B37
	ldr r1, [sp]
	mov r0, #0
	strb r0, [r1, r2]
	add r3, r2, #1
	strb r0, [r1, r3]
	ldr r1, [r1]
	ldr r4, _02231234 ; =0x00000172
	sub r3, r2, #7
	ldrb r5, [r1, r4]
	ldr r1, [sp]
	sub r4, #0x51
	strb r5, [r1, r3]
	ldr r1, [r1]
	ldrb r1, [r1, r4]
	cmp r1, #0
	beq _022311BA
	cmp r1, #1
	beq _022311BA
	cmp r1, #2
	bne _022311C4
_022311BA:
	ldr r1, _0223123C ; =0x00000B36
	ldr r0, [sp]
	mov r2, #6
	strb r2, [r0, r1]
	b _022311CA
_022311C4:
	ldr r1, [sp]
	sub r2, r2, #1
	strb r0, [r1, r2]
_022311CA:
	ldr r0, [sp, #4]
	ldrh r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #4]
	strh r1, [r0]
_022311D4:
	ldr r1, _02231240 ; =0x00001158
	ldr r0, [sp]
	mov r4, #0xb
	add r0, r0, r1
	ldr r1, [sp]
	lsl r4, r4, #8
	add r3, r1, #0
	mov r2, #9
	add r3, r3, r4
	bl MOD12_02241050
	cmp r0, #1
	bne _02231228
	ldr r0, [sp, #4]
	ldrh r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #4]
	strh r1, [r0]
	b _02231228
_022311FA:
	ldr r0, [sp]
	ldr r4, _02231244 ; =0x00000127
	ldr r3, [r0]
	ldr r1, _02231240 ; =0x00001158
	sub r2, r4, #4
	add r0, r0, r1
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02231228
	ldr r0, [sp, #4]
	ldrh r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #4]
	strh r1, [r0]
	b _02231228
_02231222:
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02231228:
	mov r0, #0
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_02231230: .word 0x00000ADA
_02231234: .word 0x00000172
_02231238: .word 0x00000B37
_0223123C: .word 0x00000B36
_02231240: .word 0x00001158
_02231244: .word 0x00000127

	thumb_func_start MOD12_02231248
MOD12_02231248: ; 0x02231248
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	beq _0223125A
	cmp r0, #1
	beq _0223125E
	b _0223128E
_0223125A:
	add r0, r0, #1
	strh r0, [r4]
_0223125E:
	ldr r3, _022312B0 ; =0x00000172
	mov r0, #0
	add r1, sp, #0
_02231264:
	ldr r5, [r2]
	add r5, r5, r0
	ldrb r5, [r5, r3]
	add r0, r0, #1
	strb r5, [r1]
	add r1, r1, #1
	cmp r0, #4
	blt _02231264
	ldr r0, _022312B4 ; =0x00001158
	add r1, r2, #0
	add r0, r2, r0
	mov r2, #4
	add r3, sp, #0
	bl MOD12_02241050
	cmp r0, #1
	bne _022312AC
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _022312AC
_0223128E:
	ldr r0, _022312B4 ; =0x00001158
	ldr r3, [r2]
	ldr r4, _022312B8 ; =0x00000127
	add r0, r2, r0
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _022312AC
	mov r0, #3
	pop {r3, r4, r5, pc}
_022312AC:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_022312B0: .word 0x00000172
_022312B4: .word 0x00001158
_022312B8: .word 0x00000127

	thumb_func_start MOD12_022312BC
MOD12_022312BC: ; 0x022312BC __sinit
	push {r3, lr}
	ldr r0, _022312D0 ; =SDK_OVERLAY_MODULE_08_ID
	mov r1, #2
	bl HandleLoadOverlay
	ldr r0, _022312D4 ; =SDK_OVERLAY_MODULE_17_ID
	mov r1, #2
	bl HandleLoadOverlay
	pop {r3, pc}
	.align 2, 0
_022312D0: .word SDK_OVERLAY_MODULE_08_ID
_022312D4: .word SDK_OVERLAY_MODULE_17_ID

	thumb_func_start MOD12_022312D8
MOD12_022312D8: ; 0x022312D8
	push {r3, lr}
	sub sp, #8
	mov r2, #2
	ldr r1, _022312F0 ; =MOD12_022312F4
	str r2, [sp]
	str r1, [sp, #4]
	mov r1, #0
	add r3, r1, #0
	bl FUN_02022318
	add sp, #8
	pop {r3, pc}
	.align 2, 0
_022312F0: .word MOD12_022312F4

	thumb_func_start MOD12_022312F4
MOD12_022312F4: ; 0x022312F4
	push {r3, lr}
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r0, _02231360 ; =0x04000008
	mov r1, #3
	ldrh r2, [r0]
	bic r2, r1
	mov r1, #1
	orr r1, r2
	strh r1, [r0]
	add r0, #0x58
	ldrh r2, [r0]
	ldr r1, _02231364 ; =0xFFFFCFFD
	and r2, r1
	strh r2, [r0]
	add r2, r1, #2
	ldrh r3, [r0]
	add r1, r1, #2
	and r3, r2
	mov r2, #0x10
	orr r2, r3
	strh r2, [r0]
	ldrh r3, [r0]
	ldr r2, _02231368 ; =0x0000CFFB
	and r3, r2
	strh r3, [r0]
	ldrh r3, [r0]
	sub r2, #0x1c
	and r3, r1
	mov r1, #8
	orr r1, r3
	strh r1, [r0]
	ldrh r1, [r0]
	and r1, r2
	strh r1, [r0]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl G3X_SetFog
	mov r0, #0
	ldr r2, _0223136C ; =0x00007FFF
	add r1, r0, #0
	mov r3, #0x3f
	str r0, [sp]
	bl G3X_SetClearColor
	ldr r1, _02231370 ; =0xBFFF0000
	ldr r0, _02231374 ; =0x04000580
	str r1, [r0]
	pop {r3, pc}
	.align 2, 0
_02231360: .word 0x04000008
_02231364: .word 0xFFFFCFFD
_02231368: .word 0x0000CFFB
_0223136C: .word 0x00007FFF
_02231370: .word 0xBFFF0000
_02231374: .word 0x04000580

	thumb_func_start MOD12_02231378
MOD12_02231378: ; 0x02231378
	ldr r3, _0223137C ; =FUN_020223BC
	bx r3
	.align 2, 0
_0223137C: .word FUN_020223BC

	thumb_func_start MOD12_02231380
MOD12_02231380: ; 0x02231380
	push {r4, r5, r6, r7, lr}
	sub sp, #0x74
	str r0, [sp, #0x18]
	str r1, [sp, #0x1c]
	str r2, [sp, #0x20]
	ldr r0, [sp, #0x90]
	ldr r1, [sp, #0x8c]
	mov r2, #0
	str r3, [sp, #0x24]
	ldr r5, [sp, #0x88]
	ldr r4, [sp, #0xa0]
	bl FUN_02002E14
	add r7, r0, #0
	asr r1, r7, #2
	lsr r1, r1, #0x1d
	add r1, r7, r1
	asr r6, r1, #3
	mov r1, #8
	bl FX_ModS32
	cmp r0, #0
	beq _022313B0
	add r6, r6, #1
_022313B0:
	add r0, sp, #0x34
	bl InitWindow
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	lsl r2, r6, #0x18
	ldr r0, [sp, #0x1c]
	add r1, sp, #0x34
	lsr r2, r2, #0x18
	mov r3, #2
	bl FUN_020190EC
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x94]
	ldr r1, [sp, #0x90]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r2, [sp, #0x8c]
	add r0, sp, #0x34
	str r3, [sp, #0x14]
	bl AddTextPrinterParameterized3
	ldr r2, [sp, #0x18]
	add r0, sp, #0x34
	mov r1, #1
	bl FUN_02011898
	mov r1, #1
	add r2, r1, #0
	add r3, sp, #0x28
	bl FUN_0201D568
	ldr r0, [sp, #0xa8]
	cmp r0, #1
	bne _02231408
	lsr r0, r7, #0x1f
	add r0, r7, r0
	asr r0, r0, #1
	sub r4, r4, r0
_02231408:
	ldr r0, [sp, #0x24]
	str r0, [sp, #0x44]
	add r0, sp, #0x34
	str r0, [sp, #0x48]
	ldr r0, [sp, #0x20]
	bl FUN_0200CA40
	str r0, [sp, #0x4c]
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x9c]
	bl FUN_0200C334
	str r0, [sp, #0x50]
	mov r0, #0
	str r0, [sp, #0x54]
	ldr r0, [sp, #0x2c]
	str r4, [sp, #0x5c]
	str r0, [sp, #0x58]
	ldr r0, [sp, #0xa4]
	sub r0, #8
	str r0, [sp, #0x60]
	ldr r0, [sp, #0xac]
	str r0, [sp, #0x64]
	ldr r0, [sp, #0xb0]
	str r0, [sp, #0x68]
	mov r0, #1
	str r0, [sp, #0x6c]
	ldr r0, [sp, #0x18]
	str r0, [sp, #0x70]
	add r0, sp, #0x44
	bl FUN_020117E8
	ldr r1, [sp, #0x98]
	add r6, r0, #0
	cmp r1, #0
	beq _02231454
	bl FUN_02011A90
_02231454:
	ldr r2, [sp, #0xa4]
	add r0, r6, #0
	add r1, r4, #0
	sub r2, #8
	bl FUN_020118C4
	add r0, sp, #0x34
	bl FUN_02019178
	str r6, [r5]
	add r3, sp, #0x28
	ldmia r3!, {r0, r1}
	add r2, r5, #4
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	strh r7, [r5, #0x10]
	add sp, #0x74
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_0223147C
MOD12_0223147C: ; 0x0223147C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_02011870
	add r0, r4, #4
	bl FUN_0201D5E8
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_02231490
MOD12_02231490: ; 0x02231490
	cmp r3, #1
	bne _0223149A
	ldrh r3, [r0, #0x10]
	lsr r3, r3, #1
	sub r1, r1, r3
_0223149A:
	ldr r3, _022314A4 ; =FUN_020118C4
	ldr r0, [r0]
	sub r2, #8
	bx r3
	nop
_022314A4: .word FUN_020118C4

	thumb_func_start MOD12_022314A8
MOD12_022314A8: ; 0x022314A8
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r3, r1, #0
	mov r0, #1
	mov r1, #0x1a
	mov r2, #0xc2
	bl NewMsgDataFromNarc
	add r5, r0, #0
	add r1, r4, #0
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r5, #0
	bl DestroyMsgData
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_022314CC
MOD12_022314CC: ; 0x022314CC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, r1, #0
	ldr r1, _02231504 ; =0x00000122
	ldrb r1, [r5, r1]
	bl MOD12_0224473C
	add r7, r0, #0
	mov r6, #0
	add r4, r5, #0
_022314E0:
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	add r1, r7, #0
	bl MOD12_02244710
	ldr r1, _02231508 ; =0x0000012A
	add r6, r6, #1
	strh r0, [r4, r1]
	add r5, r5, #4
	add r4, #0xc
	cmp r6, #4
	blt _022314E0
	add r0, r7, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02231504: .word 0x00000122
_02231508: .word 0x0000012A

	thumb_func_start MOD12_0223150C
MOD12_0223150C: ; 0x0223150C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r0, [sp]
	ldr r4, [sp]
	mov r0, #0
	str r0, [sp, #0x10]
	add r0, r4, #0
	str r0, [sp, #4]
_0223151C:
	ldr r0, [r4]
	mov r1, #6
	mov r2, #0
	bl GetMonData
	mov r6, #0x64
	add r5, r0, #0
	add r0, r6, #0
	ldr r1, [sp]
	add r0, #0xbb
	ldrb r0, [r1, r0]
	cmp r0, #4
	bls _02231538
	b _022316AA
_02231538:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02231544: ; jump table
	.short _0223154E - _02231544 - 2 ; case 0
	.short _02231594 - _02231544 - 2 ; case 1
	.short _022315DA - _02231544 - 2 ; case 2
	.short _02231620 - _02231544 - 2 ; case 3
	.short _02231666 - _02231544 - 2 ; case 4
_0223154E:
	ldr r0, [r4]
	mov r1, #0x13
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0xc]
	ldr r0, [r4]
	mov r1, #0x17
	mov r2, #0
	bl GetMonData
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #0x14
	mov r2, #0
	bl GetMonData
	add r7, r0, #0
	add r0, r6, #0
	add r0, #0xa0
	cmp r5, r0
	beq _0223158C
	add r0, r6, #0
	add r0, #0xa1
	cmp r5, r0
	beq _02231590
	add r0, r6, #0
	add r0, #0xa4
	cmp r5, r0
	beq _02231590
	b _022316B2
_0223158C:
	mov r6, #0x6e
	b _022316B2
_02231590:
	mov r6, #0x69
	b _022316B2
_02231594:
	ldr r0, [r4]
	mov r1, #0x14
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0xc]
	ldr r0, [r4]
	mov r1, #0x13
	mov r2, #0
	bl GetMonData
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #0x15
	mov r2, #0
	bl GetMonData
	add r7, r0, #0
	add r0, r6, #0
	add r0, #0xa0
	cmp r5, r0
	beq _022315D6
	add r0, r6, #0
	add r0, #0xa1
	cmp r5, r0
	beq _022315D2
	add r0, r6, #0
	add r0, #0xa2
	cmp r5, r0
	beq _022315D6
	b _022316B2
_022315D2:
	mov r6, #0x6e
	b _022316B2
_022315D6:
	mov r6, #0x69
	b _022316B2
_022315DA:
	ldr r0, [r4]
	mov r1, #0x15
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0xc]
	ldr r0, [r4]
	mov r1, #0x14
	mov r2, #0
	bl GetMonData
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #0x16
	mov r2, #0
	bl GetMonData
	add r7, r0, #0
	add r0, r6, #0
	add r0, #0xa1
	cmp r5, r0
	beq _0223161C
	add r0, r6, #0
	add r0, #0xa2
	cmp r5, r0
	beq _02231618
	add r0, r6, #0
	add r0, #0xa3
	cmp r5, r0
	beq _0223161C
	b _022316B2
_02231618:
	mov r6, #0x6e
	b _022316B2
_0223161C:
	mov r6, #0x69
	b _022316B2
_02231620:
	ldr r0, [r4]
	mov r1, #0x16
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0xc]
	ldr r0, [r4]
	mov r1, #0x15
	mov r2, #0
	bl GetMonData
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #0x17
	mov r2, #0
	bl GetMonData
	add r7, r0, #0
	add r0, r6, #0
	add r0, #0xa2
	cmp r5, r0
	beq _02231662
	add r0, r6, #0
	add r0, #0xa3
	cmp r5, r0
	beq _0223165E
	add r0, r6, #0
	add r0, #0xa4
	cmp r5, r0
	beq _02231662
	b _022316B2
_0223165E:
	mov r6, #0x6e
	b _022316B2
_02231662:
	mov r6, #0x69
	b _022316B2
_02231666:
	ldr r0, [r4]
	mov r1, #0x17
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0xc]
	ldr r0, [r4]
	mov r1, #0x16
	mov r2, #0
	bl GetMonData
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #0x13
	mov r2, #0
	bl GetMonData
	add r7, r0, #0
	add r0, r6, #0
	add r0, #0xa0
	cmp r5, r0
	beq _022316A6
	add r0, r6, #0
	add r0, #0xa3
	cmp r5, r0
	beq _022316A6
	add r0, r6, #0
	add r0, #0xa4
	cmp r5, r0
	bne _022316B2
	mov r6, #0x6e
	b _022316B2
_022316A6:
	mov r6, #0x69
	b _022316B2
_022316AA:
	bl ErrorHandling
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_022316B2:
	ldr r0, [r4]
	mov r1, #0x18
	mov r2, #0
	bl GetMonData
	ldr r1, [sp, #8]
	add r1, r1, r7
	add r1, r0, r1
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r1, r0, #1
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	add r0, r1, #0
	mul r0, r6
	mov r1, #0x64
	bl _s32_div_f
	mov r1, #0x4a
	ldr r2, [sp, #4]
	lsl r1, r1, #2
	strh r0, [r2, r1]
	add r0, r2, #0
	add r0, #0xc
	str r0, [sp, #4]
	ldr r0, [sp, #0x10]
	add r4, r4, #4
	add r0, r0, #1
	str r0, [sp, #0x10]
	cmp r0, #4
	bge _022316F2
	b _0223151C
_022316F2:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_022316F8
MOD12_022316F8: ; 0x022316F8
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r6, r2, #0
	mov r2, #0
	mvn r2, r2
	add r5, r0, #0
	add r4, r1, #0
	cmp r3, r2
	beq _0223171A
	mov r2, #1
	str r2, [sp]
	str r2, [sp, #4]
	str r3, [sp, #8]
	mov r2, #0x2e
	mov r3, #0x49
	bl FUN_0200C00C
_0223171A:
	mov r1, #0
	ldr r0, [sp, #0x28]
	mvn r1, r1
	cmp r0, r1
	beq _02231744
	mov r1, #0x2e
	str r1, [sp]
	mov r1, #7
	str r1, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	mov r1, #1
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	add r0, r6, #0
	mov r1, #2
	add r2, r5, #0
	add r3, r4, #0
	bl FUN_0200C0DC
_02231744:
	mov r0, #0
	ldr r1, [sp, #0x2c]
	mvn r0, r0
	cmp r1, r0
	beq _02231760
	mov r0, #1
	str r0, [sp]
	str r1, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x2e
	mov r3, #0x4a
	bl FUN_0200C124
_02231760:
	mov r0, #0
	ldr r1, [sp, #0x30]
	mvn r0, r0
	cmp r1, r0
	beq _0223177C
	mov r0, #1
	str r0, [sp]
	str r1, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x2e
	mov r3, #0x4b
	bl FUN_0200C13C
_0223177C:
	add sp, #0x18
	pop {r4, r5, r6, pc}

	thumb_func_start MOD12_02231780
MOD12_02231780: ; 0x02231780
	push {r4, r5, r6, lr}
	add r4, r2, #0
	mov r2, #0
	mvn r2, r2
	add r5, r0, #0
	add r6, r3, #0
	cmp r1, r2
	beq _02231794
	bl FUN_0200C358
_02231794:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	beq _022317A4
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0200C368
_022317A4:
	mov r0, #0
	mvn r0, r0
	cmp r6, r0
	beq _022317B4
	add r0, r5, #0
	add r1, r6, #0
	bl FUN_0200C378
_022317B4:
	mov r0, #0
	ldr r1, [sp, #0x10]
	mvn r0, r0
	cmp r1, r0
	beq _022317C4
	add r0, r5, #0
	bl FUN_0200C388
_022317C4:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD12_022317C8
MOD12_022317C8: ; 0x022317C8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	ldr r5, _02231850 ; =MOD12_02244D18
	str r2, [sp, #4]
	str r0, [sp]
	add r7, r1, #0
	add r4, sp, #8
	mov r2, #6
_022317D8:
	ldmia r5!, {r0, r1}
	stmia r4!, {r0, r1}
	sub r2, r2, #1
	bne _022317D8
	ldr r0, [r5]
	ldr r5, _02231854 ; =MOD12_02244CE8
	str r0, [r4]
	ldr r0, [sp, #0x50]
	ldr r4, [sp]
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x54]
	str r3, [sp, #0x1c]
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x58]
	mov r6, #0
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x5c]
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x60]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x64]
	str r0, [sp, #0x34]
_02231804:
	ldr r1, [sp, #4]
	add r0, r7, #0
	add r2, sp, #8
	bl FUN_0200C154
	str r0, [r4]
	mov r1, #0
	mov r2, #2
	ldrsh r1, [r5, r1]
	ldrsh r2, [r5, r2]
	bl FUN_0200C714
	ldrb r1, [r5, #6]
	ldr r0, [r4]
	bl FUN_0200C5C0
	ldr r0, [r4]
	mov r1, #1
	bl FUN_0200C840
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_0200C59C
	add r6, r6, #1
	add r4, r4, #4
	add r5, #8
	cmp r6, #6
	blt _02231804
	ldr r0, _02231858 ; =MOD12_02231880
	ldr r1, [sp]
	ldr r2, [sp, #0x68]
	bl FUN_0200CA44
	ldr r1, [sp]
	str r0, [r1, #0x18]
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02231850: .word MOD12_02244D18
_02231854: .word MOD12_02244CE8
_02231858: .word MOD12_02231880

	thumb_func_start MOD12_0223185C
MOD12_0223185C: ; 0x0223185C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_02231864:
	ldr r0, [r5]
	bl FUN_0200C3DC
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _02231864
	ldr r0, [r6, #0x18]
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r6, #0x18]
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD12_02231880
MOD12_02231880: ; 0x02231880
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, _022318A0 ; =MOD12_02244CE8
	add r5, r1, #0
	mov r6, #0
	mov r7, #4
_0223188A:
	ldrsh r1, [r4, r7]
	ldr r0, [r5]
	bl FUN_0200C8BC
	add r6, r6, #1
	add r4, #8
	add r5, r5, #4
	cmp r6, #6
	blt _0223188A
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022318A0: .word MOD12_02244CE8

	thumb_func_start MOD12_022318A4
MOD12_022318A4: ; 0x022318A4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	mov r1, #0x14
	add r6, r2, #0
	add r7, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x14
	bl MI_CpuFill8
	str r5, [r4, #4]
	str r6, [r4, #0xc]
	ldr r0, [sp, #0x18]
	strb r7, [r4, #0x10]
	strb r0, [r4, #0x12]
	ldr r0, _022318D8 ; =MOD12_0223190C
	ldr r2, [sp, #0x1c]
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4]
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022318D8: .word MOD12_0223190C

	thumb_func_start MOD12_022318DC
MOD12_022318DC: ; 0x022318DC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	bne _022318EA
	bl ErrorHandling
_022318EA:
	ldr r0, [r4]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD12_022318F8
MOD12_022318F8: ; 0x022318F8
	push {r3, lr}
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #1
	bne _02231908
	mov r0, #1
	pop {r3, pc}
_02231908:
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD12_0223190C
MOD12_0223190C: ; 0x0223190C
	push {r3, r4, lr}
	sub sp, #4
	mov r0, #1
	add r4, r1, #0
	bl FUN_0200A344
	cmp r0, #0
	beq _02231972
	ldr r0, [r4, #8]
	add r2, r0, #1
	str r2, [r4, #8]
	ldrb r0, [r4, #0x11]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #1
	ldrh r0, [r1, r0]
	cmp r2, r0
	ble _02231972
	mov r0, #1
	str r0, [sp]
	mov r0, #6
	mov r1, #0
	mov r2, #4
	mov r3, #0x3f
	bl FUN_0200A208
	ldr r0, _02231978 ; =0x000005F8
	bl FUN_020054C8
	mov r0, #0
	str r0, [r4, #8]
	ldrb r0, [r4, #0x11]
	add r0, r0, #1
	strb r0, [r4, #0x11]
	ldrb r1, [r4, #0x11]
	ldrb r0, [r4, #0x10]
	cmp r1, r0
	blo _02231972
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _02231966
	add r0, r4, #0
	bl MOD12_022318DC
	add sp, #4
	pop {r3, r4, pc}
_02231966:
	cmp r0, #0xff
	beq _0223196E
	sub r0, r0, #1
	strb r0, [r4, #0x12]
_0223196E:
	mov r0, #0
	strb r0, [r4, #0x11]
_02231972:
	add sp, #4
	pop {r3, r4, pc}
	nop
_02231978: .word 0x000005F8

	thumb_func_start MOD12_0223197C
MOD12_0223197C: ; 0x0223197C
	push {r4, lr}
	mov r1, #0x32
	mov r0, #0x15
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r2, #0x32
	mov r1, #0
	lsl r2, r2, #4
	add r4, r0, #0
	bl MI_CpuFill8
	mov r1, #0
	mov r0, #0x2e
	mvn r1, r1
	lsl r0, r0, #4
	strb r1, [r4, r0]
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_022319A4
MOD12_022319A4: ; 0x022319A4
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	ldr r6, _022319F8 ; =MOD12_02244F64
	add r5, r0, #0
	add r7, r4, #0
_022319AE:
	add r1, r4, #4
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	add r2, r6, #0
	add r3, r7, #0
	bl FUN_02016C18
	add r1, r4, #4
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	mov r2, #0
	bl FUN_02018768
	add r1, r4, #4
	lsl r1, r1, #0x18
	mov r2, #0
	add r0, r5, #0
	lsr r1, r1, #0x18
	add r3, r2, #0
	bl FUN_020179E0
	add r1, r4, #4
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add r4, r4, #1
	add r6, #0x1c
	cmp r4, #4
	blo _022319AE
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022319F8: .word MOD12_02244F64

	thumb_func_start MOD12_022319FC
MOD12_022319FC: ; 0x022319FC
	push {r4, r5, r6, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r4, #0
_02231A04:
	add r0, r4, #4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, r6, #0
	bl FUN_0201797C
	add r1, r4, #4
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	bl FUN_020178A0
	add r4, r4, #1
	cmp r4, #4
	blo _02231A04
	pop {r4, r5, r6, pc}

	thumb_func_start MOD12_02231A24
MOD12_02231A24: ; 0x02231A24
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	bl MOD12_0223197C
	add r4, r0, #0
	str r5, [r4]
	str r6, [r4, #4]
	mov r0, #0xc
	mov r1, #0x15
	str r7, [r4, #8]
	bl FUN_02011744
	mov r7, #2
	str r0, [r4, #0x3c]
	mov r5, #0
	lsl r7, r7, #0xa
	b _02231A88
_02231A4C:
	mov r0, #0x15
	add r1, r7, #0
	bl AllocFromHeap
	lsl r1, r5, #2
	add r1, r4, r1
	str r0, [r1, #0x20]
	mov r0, #0x15
	str r0, [sp]
	ldr r1, _02231AE0 ; =MOD12_02244D6C
	lsl r2, r5, #1
	ldrh r1, [r1, r2]
	mov r0, #0x2d
	mov r2, #1
	add r3, sp, #0xc
	bl FUN_02006BDC
	add r6, r0, #0
	lsl r0, r5, #2
	add r0, r4, r0
	ldr r1, [r0, #0x20]
	ldr r0, [sp, #0xc]
	add r2, r7, #0
	add r0, #0xc
	bl MIi_CpuCopy32
	add r0, r6, #0
	bl FreeToHeap
	add r5, r5, #1
_02231A88:
	cmp r5, #5
	blt _02231A4C
	ldr r0, [r4, #4]
	mov r7, #2
	ldr r6, [r0, #0x50]
	mov r5, #0
	lsl r7, r7, #8
	b _02231AD6
_02231A98:
	mov r0, #0x15
	add r1, r7, #0
	bl AllocFromHeap
	lsl r1, r5, #2
	add r1, r4, r1
	str r0, [r1, #0x34]
	mov r0, #1
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r2, _02231AE4 ; =MOD12_02244D54
	lsl r3, r5, #1
	ldrh r2, [r2, r3]
	add r0, r6, #0
	mov r1, #0x2d
	mov r3, #0x15
	bl FUN_020030E8
	add r0, r6, #0
	mov r1, #1
	bl FUN_020031FC
	lsl r1, r5, #2
	add r1, r4, r1
	ldr r1, [r1, #0x34]
	add r2, r7, #0
	bl MIi_CpuCopy16
	add r5, r5, #1
_02231AD6:
	cmp r5, #2
	blt _02231A98
	add r0, r4, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02231AE0: .word MOD12_02244D6C
_02231AE4: .word MOD12_02244D54

	thumb_func_start MOD12_02231AE8
MOD12_02231AE8: ; 0x02231AE8
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r6, r0, #0
	bl MOD12_02232638
	ldr r0, [r6, #0x3c]
	bl FUN_020117BC
	ldr r3, _02231B48 ; =0x000080F8
	str r3, [sp]
	ldr r0, [r6, #4]
	add r1, r3, #5
	ldr r0, [r0, #0x1c]
	sub r2, r3, #7
	bl MOD12_022447C0
	mov r0, #0xc5
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl MOD12_0224486C
	mov r4, #0
	add r5, r6, #0
_02231B16:
	ldr r0, [r5, #0x20]
	bl FreeToHeap
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _02231B16
	mov r5, #0
	add r4, r6, #0
_02231B28:
	ldr r0, [r4, #0x34]
	bl FreeToHeap
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #2
	blt _02231B28
	add r0, r6, #0
	bl MOD12_02232B7C
	add r0, r6, #0
	bl FreeToHeap
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_02231B48: .word 0x000080F8

	thumb_func_start MOD12_02231B4C
MOD12_02231B4C: ; 0x02231B4C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r7, r0, #0
	str r3, [r7, #0xc]
	ldr r0, [r7, #4]
	str r2, [sp, #8]
	ldr r0, [r0, #0x24]
	str r1, [sp, #4]
	str r0, [sp, #0xc]
	mov r0, #0x2e
	lsl r0, r0, #4
	ldrsb r2, [r7, r0]
	mov r0, #0
	mvn r0, r0
	cmp r2, r0
	bne _02231B76
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0x10]
	b _02231B80
_02231B76:
	mov r0, #0x30
	ldr r1, _02231C70 ; =MOD12_02245074
	mul r0, r2
	add r0, r1, r0
	str r0, [sp, #0x10]
_02231B80:
	ldr r0, [sp, #4]
	mov r1, #0x30
	ldr r2, _02231C70 ; =MOD12_02245074
	mul r1, r0
	add r0, r2, r1
	str r0, [sp, #0x14]
	mov r4, #0
	add r5, r0, #0
_02231B90:
	ldrh r1, [r5, #0xc]
	add r0, r4, #4
	lsl r0, r0, #0x18
	lsl r1, r1, #0x18
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl FUN_020178BC
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, #4
	blt _02231B90
	mov r0, #2
	lsl r0, r0, #8
	str r0, [sp]
	ldr r1, [sp, #0x14]
	ldr r0, [r7, #4]
	ldrh r1, [r1, #2]
	ldr r0, [r0, #0x50]
	mov r2, #1
	lsl r1, r1, #2
	add r1, r7, r1
	ldr r1, [r1, #0x34]
	mov r3, #0
	bl FUN_02003054
	ldr r6, [sp, #0x14]
	ldr r4, [sp, #0x10]
	mov r5, #0
_02231BCA:
	ldrh r2, [r6, #4]
	ldr r0, _02231C74 ; =0x0000FFFF
	cmp r2, r0
	beq _02231C00
	ldr r0, [sp, #8]
	cmp r0, #1
	beq _02231BDE
	ldrh r0, [r4, #4]
	cmp r2, r0
	beq _02231C00
_02231BDE:
	lsl r2, r2, #2
	add r1, r5, #4
	add r2, r7, r2
	lsl r1, r1, #0x18
	mov r3, #2
	ldr r0, [sp, #0xc]
	ldr r2, [r2, #0x20]
	lsr r1, r1, #0x18
	lsl r3, r3, #0xa
	bl FUN_02017DFC
	add r1, r5, #4
	lsl r1, r1, #0x18
	ldr r0, [sp, #0xc]
	lsr r1, r1, #0x18
	bl FUN_0201AC68
_02231C00:
	add r5, r5, #1
	add r6, r6, #2
	add r4, r4, #2
	cmp r5, #4
	blt _02231BCA
	mov r1, #0x2e
	ldr r0, [sp, #4]
	lsl r1, r1, #4
	strb r0, [r7, r1]
	add r0, r7, #0
	bl MOD12_02232638
	ldr r0, [sp, #0x14]
	ldr r3, [r0, #0x28]
	cmp r3, #0
	beq _02231C28
	ldr r1, [sp, #4]
	ldr r2, [sp, #8]
	add r0, r7, #0
	blx r3
_02231C28:
	ldr r0, [sp, #0x14]
	ldrh r1, [r0]
	ldr r0, _02231C74 ; =0x0000FFFF
	cmp r1, r0
	beq _02231C62
	ldr r0, [sp, #8]
	cmp r0, #1
	beq _02231C40
	ldr r0, [sp, #0x10]
	ldrh r0, [r0]
	cmp r1, r0
	beq _02231C62
_02231C40:
	mov r3, #0xb7
	mov r0, #0x15
	lsl r3, r3, #2
	str r0, [sp]
	mov r0, #0x2d
	mov r2, #1
	add r3, r7, r3
	bl FUN_02006BB0
	mov r1, #0xb6
	lsl r1, r1, #2
	str r0, [r7, r1]
	ldr r0, _02231C78 ; =MOD12_0223336C
	add r1, r7, #0
	mov r2, #0xa
	bl FUN_0200CA98
_02231C62:
	ldr r0, _02231C7C ; =MOD12_022333A8
	add r1, r7, #0
	mov r2, #0xa
	bl FUN_0200CA98
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02231C70: .word MOD12_02245074
_02231C74: .word 0x0000FFFF
_02231C78: .word MOD12_0223336C
_02231C7C: .word MOD12_022333A8

	thumb_func_start MOD12_02231C80
MOD12_02231C80: ; 0x02231C80
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0x2e
	lsl r0, r0, #4
	ldrsb r1, [r5, r0]
	mov r6, #0
	sub r0, r6, #1
	cmp r1, r0
	bne _02231C96
	bl ErrorHandling
_02231C96:
	mov r0, #0x2e
	lsl r0, r0, #4
	ldrsb r1, [r5, r0]
	ldr r3, _02231D44 ; =MOD12_02245074
	mov r0, #0x30
	add r2, r1, #0
	mul r2, r0
	add r4, r3, r2
	ldr r1, [r4, #0x14]
	cmp r1, #0
	bne _02231CB0
	sub r0, #0x31
	pop {r3, r4, r5, r6, r7, pc}
_02231CB0:
	ldr r0, [r4, #0x18]
	cmp r0, #0
	bne _02231CBA
	bl ErrorHandling
_02231CBA:
	ldr r0, [r4, #0x14]
	bl FUN_02020988
	add r7, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r7, r0
	bne _02231CD4
	add r0, r5, #0
	bl MOD12_02232E18
	add r7, r0, #0
	add r6, r6, #1
_02231CD4:
	mov r0, #0
	mvn r0, r0
	str r0, [sp]
	cmp r7, r0
	bne _02231CE2
	mov r2, #0xff
	b _02231CEE
_02231CE2:
	ldr r1, [r4, #0x18]
	lsl r0, r7, #2
	ldr r0, [r1, r0]
	str r0, [sp]
	ldr r0, [r4, #0x1c]
	ldrb r2, [r0, r7]
_02231CEE:
	ldr r3, [r4, #0x2c]
	cmp r3, #0
	beq _02231D3E
	ldr r1, [sp]
	add r0, r5, #0
	blx r3
	mov r1, #0
	mvn r1, r1
	str r0, [sp]
	cmp r0, r1
	beq _02231D3E
	ldr r2, [r4, #0x24]
	cmp r2, #0
	beq _02231D10
	add r0, r5, #0
	add r1, r7, #0
	blx r2
_02231D10:
	mov r0, #0xc6
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	mov r2, #4
	bl MI_CpuFill8
	mov r0, #0xc5
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl MOD12_0224493C
	cmp r6, #0
	ble _02231D36
	mov r0, #0xc7
	mov r1, #1
	lsl r0, r0, #2
	strb r1, [r5, r0]
	b _02231D3E
_02231D36:
	mov r0, #0xc7
	mov r1, #0
	lsl r0, r0, #2
	strb r1, [r5, r0]
_02231D3E:
	ldr r0, [sp]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02231D44: .word MOD12_02245074

	thumb_func_start MOD12_02231D48
MOD12_02231D48: ; 0x02231D48
	ldr r1, [r0, #0x10]
	cmp r1, #0
	bne _02231D58
	ldr r0, [r0, #0x14]
	cmp r0, #0
	bne _02231D58
	mov r0, #1
	bx lr
_02231D58:
	mov r0, #0
	bx lr

	thumb_func_start MOD12_02231D5C
MOD12_02231D5C: ; 0x02231D5C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldr r0, [r5, #4]
	mov r2, #0x12
	lsl r2, r2, #4
	ldr r3, [r0]
	add r1, r2, #1
	ldrb r0, [r3, r2]
	ldrb r1, [r3, r1]
	ldr r3, [r5]
	add r2, #0x51
	ldrb r2, [r3, r2]
	bl FUN_02083228
	add r4, r0, #0
	ldr r0, [r5, #4]
	ldr r1, _02231E28 ; =0x0000011F
	ldr r2, [r0]
	ldrb r0, [r2, r1]
	add r1, r1, #2
	ldrb r1, [r2, r1]
	bl FUN_020832A4
	add r6, r0, #0
	ldr r0, [r5, #4]
	add r1, r4, #0
	ldr r0, [r0, #0x38]
	bl NewString_ReadMsgData
	add r4, r0, #0
	ldr r0, [r5, #4]
	add r1, r6, #0
	ldr r0, [r0, #0x38]
	bl NewString_ReadMsgData
	add r6, r0, #0
	ldr r0, _02231E2C ; =0x00010200
	add r1, r5, #0
	str r0, [sp]
	mov r3, #0
	ldr r0, _02231E30 ; =0x000080F0
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x7f
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r1, #0x40
	add r2, r4, #0
	str r3, [sp, #0x18]
	bl MOD12_022322C0
	ldr r0, _02231E2C ; =0x00010200
	add r1, r5, #0
	str r0, [sp]
	mov r3, #0
	ldr r0, _02231E30 ; =0x000080F0
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x9f
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r1, #0x54
	add r2, r6, #0
	str r3, [sp, #0x18]
	bl MOD12_022322C0
	add r0, r4, #0
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	ldr r2, [r5, #4]
	mov r0, #1
	str r0, [sp]
	mov r1, #0x20
	str r1, [sp, #4]
	str r1, [sp, #8]
	ldr r0, [r2]
	add r1, #0xff
	ldrb r0, [r0, r1]
	mov r1, #0x2d
	mov r3, #0x15
	lsl r0, r0, #0x14
	lsr r0, r0, #0x10
	str r0, [sp, #0xc]
	ldr r0, [r2, #0x50]
	mov r2, #0x25
	bl FUN_02003084
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	nop
_02231E28: .word 0x0000011F
_02231E2C: .word 0x00010200
_02231E30: .word 0x000080F0

	thumb_func_start MOD12_02231E34
MOD12_02231E34: ; 0x02231E34
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	add r6, r0, #0
	mov r0, #0x69
	lsl r0, r0, #2
	add r5, r6, r0
	ldr r0, _022320A0 ; =0x000002E1
	mov r1, #0xff
	strb r1, [r6, r0]
	add r0, r5, #0
	str r0, [sp, #0x24]
	add r0, #0x50
	str r0, [sp, #0x24]
	add r0, r5, #0
	add r7, r6, #0
	str r0, [sp, #0x28]
	add r0, #0xa0
	mov r4, #0
	add r7, #0x40
	str r0, [sp, #0x28]
	b _02231F80
_02231E5E:
	ldr r0, [r6, #4]
	ldr r1, _022320A4 ; =0x00000123
	ldr r0, [r0]
	mov r2, #0
	ldrb r1, [r0, r1]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	add r1, r4, #0
	add r1, #0x36
	bl GetMonData
	lsl r1, r4, #1
	add r2, sp, #0x3c
	strh r0, [r2, r1]
	add r0, r2, #0
	ldrh r0, [r0, r1]
	cmp r0, #0
	beq _02231E8C
	mov r0, #0x4b
	add r2, r5, r4
	lsl r0, r0, #2
	ldrb r2, [r2, r0]
	b _02231E8E
_02231E8C:
	mov r2, #0
_02231E8E:
	add r0, sp, #0x34
	strh r2, [r0, r1]
	ldr r0, _022320A8 ; =0x00010708
	ldr r1, _022320AC ; =MOD12_02244D94
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _022320B0 ; =0x000080F0
	mov r2, #0
	str r0, [sp, #8]
	lsl r0, r4, #2
	ldrh r1, [r1, r0]
	mov r3, #2
	str r1, [sp, #0xc]
	ldr r1, _022320AC ; =MOD12_02244D94
	add r0, r1, r0
	ldrh r0, [r0, #2]
	add r1, r4, #0
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x14]
	mov r0, #0x14
	mul r1, r0
	add r0, r5, r1
	str r0, [sp, #0x18]
	add r0, r6, #0
	add r1, r7, r1
	bl MOD12_022322C0
	ldr r0, _022320B4 ; =0x00010200
	ldr r1, _022320B8 ; =MOD12_02244E30
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _022320B0 ; =0x000080F0
	add r2, r4, #4
	str r0, [sp, #8]
	lsl r0, r4, #3
	ldrh r1, [r1, r0]
	str r1, [sp, #0xc]
	ldr r1, _022320B8 ; =MOD12_02244E30
	add r0, r1, r0
	ldrh r0, [r0, #2]
	add r1, r4, #0
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x14]
	mov r0, #0x14
	mul r1, r0
	ldr r0, [sp, #0x24]
	add r0, r0, r1
	mov r1, #0x14
	mul r1, r2
	mov r2, #0
	str r0, [sp, #0x18]
	add r0, r6, #0
	add r1, r7, r1
	add r3, r2, #0
	bl MOD12_022322C0
	ldr r0, _022320B4 ; =0x00010200
	add r2, r4, #0
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _022320B0 ; =0x000080F0
	lsl r1, r4, #3
	str r0, [sp, #8]
	ldr r0, _022320B8 ; =MOD12_02244E30
	add r2, #8
	add r1, r0, r1
	ldrh r0, [r1, #4]
	str r0, [sp, #0xc]
	ldrh r0, [r1, #6]
	add r1, r4, #0
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x14]
	mov r0, #0x14
	mul r1, r0
	ldr r0, [sp, #0x28]
	add r0, r0, r1
	mov r1, #0x14
	mul r1, r2
	mov r2, #0
	str r0, [sp, #0x18]
	add r0, r6, #0
	add r1, r7, r1
	add r3, r2, #0
	bl MOD12_022322C0
	lsl r1, r4, #1
	add r0, sp, #0x3c
	ldrh r0, [r0, r1]
	cmp r0, #0
	bne _02231F7E
	mov r0, #0x14
	mul r0, r4
	add r0, r6, r0
	ldr r0, [r0, #0x40]
	mov r1, #0
	bl FUN_020119D0
	add r1, r4, #4
	mov r0, #0x14
	mul r0, r1
	add r0, r6, r0
	ldr r0, [r0, #0x40]
	mov r1, #0
	bl FUN_020119D0
	add r1, r4, #0
	add r1, #8
	mov r0, #0x14
	mul r0, r1
	add r0, r6, r0
	ldr r0, [r0, #0x40]
	mov r1, #0
	bl FUN_020119D0
_02231F7E:
	add r4, r4, #1
_02231F80:
	cmp r4, #4
	bge _02231F86
	b _02231E5E
_02231F86:
	mov r4, #0
	add r7, sp, #0x3c
	b _02231FB4
_02231F8C:
	lsl r0, r4, #1
	ldrh r0, [r7, r0]
	cmp r0, #0
	beq _02231FA6
	mov r0, #0x13
	add r1, r5, r4
	lsl r0, r0, #4
	ldrb r1, [r1, r0]
	add r0, r6, #0
	add r2, r4, #0
	bl MOD12_022325AC
	b _02231FB2
_02231FA6:
	mov r1, #0
	add r0, r6, #0
	mvn r1, r1
	add r2, r4, #0
	bl MOD12_022325AC
_02231FB2:
	add r4, r4, #1
_02231FB4:
	cmp r4, #4
	blt _02231F8C
	mov r4, #0
	mov r7, #0x20
	add r5, sp, #0x3c
	b _02232006
_02231FC0:
	lsl r0, r4, #1
	ldrh r2, [r5, r0]
	cmp r2, #0
	beq _02232004
	ldr r1, [r6, #4]
	ldr r0, [r6, #8]
	ldr r3, [r1]
	ldr r1, _022320A4 ; =0x00000123
	ldrb r1, [r3, r1]
	bl MOD12_02235BEC
	cmp r0, #0
	bne _02232004
	str r7, [sp]
	ldr r0, [r6, #4]
	mov r1, #1
	add r3, r4, #4
	lsl r3, r3, #0x14
	ldr r2, [r6, #0x38]
	lsl r1, r1, #8
	add r1, r2, r1
	ldr r0, [r0, #0x50]
	mov r2, #1
	lsr r3, r3, #0x10
	bl FUN_02003054
	ldr r0, _022320A0 ; =0x000002E1
	ldrb r0, [r6, r0]
	cmp r0, #0xff
	beq _02232000
	bl ErrorHandling
_02232000:
	ldr r0, _022320A0 ; =0x000002E1
	strb r4, [r6, r0]
_02232004:
	add r4, r4, #1
_02232006:
	cmp r4, #4
	blt _02231FC0
	add r0, r6, #0
	add r1, sp, #0x3c
	bl MOD12_02232470
	mov r4, #0
	b _02232096
_02232016:
	lsl r1, r4, #1
	add r0, sp, #0x3c
	ldrh r0, [r0, r1]
	cmp r0, #0
	beq _02232094
	add r0, sp, #0x34
	ldrh r0, [r0, r1]
	bl FUN_02083114
	str r0, [sp, #0x20]
	cmp r0, #0
	bge _02232030
	neg r0, r0
_02232030:
	mov r1, #0xa
	bl _s32_div_f
	str r0, [sp, #0x1c]
	cmp r0, #6
	ble _02232040
	bl ErrorHandling
_02232040:
	mov r0, #0x18
	mul r0, r4
	add r7, r6, r0
	lsl r0, r4, #3
	ldr r1, _022320BC ; =MOD12_02244E50
	str r0, [sp, #0x2c]
	add r0, r1, r0
	mov r5, #0
	str r0, [sp, #0x30]
	b _0223208E
_02232054:
	lsl r0, r5, #2
	add r1, r7, r0
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02232066
	bl ErrorHandling
_02232066:
	ldr r0, [sp, #0x20]
	ldr r3, _022320BC ; =MOD12_02244E50
	str r0, [sp]
	ldr r2, [sp, #0x2c]
	ldr r1, [r6, #4]
	ldr r3, [r3, r2]
	lsl r2, r5, #3
	add r2, r3, r2
	ldr r3, [sp, #0x30]
	ldr r0, [r1, #0x18]
	ldr r1, [r1, #0x1c]
	ldr r3, [r3, #4]
	bl MOD12_022334F4
	lsl r1, r5, #2
	add r2, r7, r1
	mov r1, #0x51
	lsl r1, r1, #2
	str r0, [r2, r1]
	add r5, r5, #1
_0223208E:
	ldr r0, [sp, #0x1c]
	cmp r5, r0
	blt _02232054
_02232094:
	add r4, r4, #1
_02232096:
	cmp r4, #4
	blt _02232016
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	nop
_022320A0: .word 0x000002E1
_022320A4: .word 0x00000123
_022320A8: .word 0x00010708
_022320AC: .word MOD12_02244D94
_022320B0: .word 0x000080F0
_022320B4: .word 0x00010200
_022320B8: .word MOD12_02244E30
_022320BC: .word MOD12_02244E50

	thumb_func_start MOD12_022320C0
MOD12_022320C0: ; 0x022320C0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	mov r0, #0x69
	lsl r0, r0, #2
	add r6, r5, r0
	add r7, r5, #0
	mov r4, #0
	add r6, #0xf0
	add r7, #0x40
	b _0223210E
_022320D6:
	ldr r0, _0223216C ; =0x0001090A
	ldr r1, _02232170 ; =MOD12_02244D78
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _02232174 ; =0x000080F0
	mov r2, #0
	str r0, [sp, #8]
	lsl r0, r4, #2
	ldrh r1, [r1, r0]
	mov r3, #2
	str r1, [sp, #0xc]
	ldr r1, _02232170 ; =MOD12_02244D78
	add r0, r1, r0
	ldrh r0, [r0, #2]
	add r1, r4, #0
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0x14
	mul r1, r0
	add r0, r6, r1
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, r7, r1
	bl MOD12_022322C0
	add r4, r4, #1
_0223210E:
	cmp r4, #3
	blt _022320D6
	ldr r0, [r5, #4]
	mov r1, #0x35
	ldr r0, [r0, #0x38]
	bl NewString_ReadMsgData
	add r6, r0, #0
	ldr r0, _0223216C ; =0x0001090A
	ldr r1, _02232174 ; =0x000080F0
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0x80
	str r1, [sp, #0xc]
	mov r1, #0xa4
	str r1, [sp, #0x10]
	mov r1, #1
	str r1, [sp, #0x14]
	add r2, r5, #0
	mov r1, #0x14
	str r0, [sp, #0x18]
	add r2, #0x40
	mul r1, r4
	add r1, r2, r1
	add r0, r5, #0
	add r2, r6, #0
	mov r3, #2
	bl MOD12_022322C0
	add r0, r6, #0
	bl String_dtor
	ldr r2, [r5, #4]
	ldr r0, [r2, #0x18]
	ldr r1, [r2, #0x1c]
	ldr r3, [r2]
	ldr r2, _02232178 ; =0x0000011E
	ldrb r2, [r3, r2]
	bl MOD12_02233448
	mov r1, #5
	lsl r1, r1, #6
	str r0, [r5, r1]
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223216C: .word 0x0001090A
_02232170: .word MOD12_02244D78
_02232174: .word 0x000080F0
_02232178: .word 0x0000011E

	thumb_func_start MOD12_0223217C
MOD12_0223217C: ; 0x0223217C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r4, r0, #0
	add r0, r5, #1
	str r2, [sp]
	cmp r0, #4
	bhi _022321A0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02232196: ; jump table
	.short _022321A0 - _02232196 - 2 ; case 0
	.short _022321A6 - _02232196 - 2 ; case 1
	.short _022321A6 - _02232196 - 2 ; case 2
	.short _022321A6 - _02232196 - 2 ; case 3
	.short _022321A6 - _02232196 - 2 ; case 4
_022321A0:
	mov r0, #0
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_022321A6:
	ldr r0, [r4, #4]
	mov r2, #0
	ldr r1, [r0]
	ldr r0, _02232208 ; =0x00000123
	ldrb r0, [r1, r0]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, r5, #0
	add r1, #0x36
	bl GetMonData
	cmp r0, #0
	beq _022321C8
	ldr r0, _0223220C ; =0x000002E1
	ldrb r0, [r4, r0]
	cmp r0, r5
	bne _022321CE
_022321C8:
	mov r0, #0
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_022321CE:
	mov r0, #6
	ldr r1, _02232210 ; =MOD12_02244E00
	mul r0, r5
	add r7, r1, r0
	ldr r1, _02232214 ; =MOD12_02244EA4
	lsl r0, r5, #4
	add r6, r1, r0
	ldr r1, [sp]
	add r0, r4, #0
	bl MOD12_02232AB8
	ldr r0, _02232218 ; =MOD12_022327E0
	add r1, r4, #0
	bl MOD12_02232654
	mov r1, #0xbd
	lsl r1, r1, #2
	str r7, [r4, r1]
	add r0, r1, #4
	str r6, [r4, r0]
	add r0, r1, #0
	mov r2, #2
	add r0, #0xc
	strb r2, [r4, r0]
	add r1, #8
	str r5, [r4, r1]
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02232208: .word 0x00000123
_0223220C: .word 0x000002E1
_02232210: .word MOD12_02244E00
_02232214: .word MOD12_02244EA4
_02232218: .word MOD12_022327E0

	thumb_func_start MOD12_0223221C
MOD12_0223221C: ; 0x0223221C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r4, r0, #0
	add r0, r5, #1
	cmp r0, #4
	bhi _0223223E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02232234: ; jump table
	.short _0223223E - _02232234 - 2 ; case 0
	.short _02232242 - _02232234 - 2 ; case 1
	.short _02232246 - _02232234 - 2 ; case 2
	.short _0223224A - _02232234 - 2 ; case 3
	.short _0223224E - _02232234 - 2 ; case 4
_0223223E:
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
_02232242:
	mov r6, #0
	b _02232250
_02232246:
	mov r6, #1
	b _02232250
_0223224A:
	mov r6, #2
	b _02232250
_0223224E:
	mov r6, #3
_02232250:
	ldr r0, [r4, #4]
	ldr r1, [r0]
	ldr r0, _022322B0 ; =0x0000011E
	ldrb r0, [r1, r0]
	cmp r5, r0
	bne _02232260
	mov r7, #1
	b _02232262
_02232260:
	mov r7, #0
_02232262:
	add r0, r4, #0
	add r1, r2, #0
	bl MOD12_02232AB8
	ldr r0, _022322B4 ; =MOD12_022326A4
	add r1, r4, #0
	bl MOD12_02232654
	mov r0, #6
	ldr r1, _022322B8 ; =MOD12_02244E18
	mul r0, r5
	add r0, r1, r0
	mov r1, #0xbd
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r2, _022322BC ; =MOD12_02244EE4
	lsl r0, r5, #4
	add r2, r2, r0
	add r0, r1, #4
	str r2, [r4, r0]
	mov r2, #3
	lsl r0, r2, #8
	strb r2, [r4, r0]
	add r0, r1, #0
	add r0, #8
	str r5, [r4, r0]
	add r0, r1, #0
	add r0, #0xd
	strb r6, [r4, r0]
	cmp r7, #1
	bne _022322AA
	mov r0, #5
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	sub r1, #0xc
	str r0, [r4, r1]
_022322AA:
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022322B0: .word 0x0000011E
_022322B4: .word MOD12_022326A4
_022322B8: .word MOD12_02244E18
_022322BC: .word MOD12_02244EE4

	thumb_func_start MOD12_022322C0
MOD12_022322C0: ; 0x022322C0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x7c
	add r5, r1, #0
	add r7, r0, #0
	ldr r0, [r5]
	str r2, [sp, #0x18]
	str r3, [sp, #0x1c]
	ldr r6, [sp, #0x9c]
	ldr r4, [sp, #0xa8]
	cmp r0, #0
	beq _022322DA
	bl ErrorHandling
_022322DA:
	ldr r1, [r7, #4]
	cmp r4, #0
	ldr r0, [r1, #0x24]
	str r0, [sp, #0x24]
	ldr r0, [r1, #0x1c]
	str r0, [sp, #0x20]
	bne _022322F6
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	add r2, sp, #0x2c
	add r3, sp, #0x28
	bl MOD12_02232DE8
	b _022322FE
_022322F6:
	ldrh r0, [r4, #0x12]
	str r0, [sp, #0x2c]
	ldrh r0, [r4, #0x10]
	str r0, [sp, #0x28]
_022322FE:
	cmp r4, #0
	bne _0223233C
	add r0, sp, #0x3c
	bl InitWindow
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r2, [sp, #0x28]
	ldr r0, [sp, #0x24]
	lsl r2, r2, #0x18
	add r1, sp, #0x3c
	lsr r2, r2, #0x18
	mov r3, #2
	bl FUN_020190EC
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x90]
	ldr r1, [sp, #0x1c]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r2, [sp, #0x18]
	add r0, sp, #0x3c
	str r3, [sp, #0x14]
	bl AddTextPrinterParameterized3
	b _02232348
_0223233C:
	add r3, r4, #0
	add r2, sp, #0x3c
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
_02232348:
	add r0, sp, #0x3c
	mov r1, #2
	mov r2, #0x15
	bl FUN_02011898
	mov r1, #1
	mov r2, #2
	add r3, sp, #0x30
	bl FUN_0201D568
	ldr r0, [sp, #0xa4]
	cmp r0, #1
	bne _0223236C
	ldr r1, [sp, #0x2c]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	sub r6, r6, r0
_0223236C:
	ldr r0, [r7, #0x3c]
	str r0, [sp, #0x4c]
	add r0, sp, #0x3c
	str r0, [sp, #0x50]
	ldr r0, [sp, #0x20]
	bl FUN_0200CA40
	str r0, [sp, #0x54]
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x98]
	bl FUN_0200C334
	str r0, [sp, #0x58]
	mov r0, #0
	ldr r1, [sp, #0x34]
	str r0, [sp, #0x5c]
	str r0, [sp, #0x6c]
	mov r0, #0x64
	str r1, [sp, #0x60]
	mov r1, #0x42
	str r0, [sp, #0x70]
	mov r0, #2
	str r0, [sp, #0x74]
	mov r0, #0x15
	str r0, [sp, #0x78]
	ldr r2, [sp, #0xa0]
	lsl r1, r1, #2
	add r1, r2, r1
	add r0, sp, #0x4c
	str r6, [sp, #0x64]
	str r1, [sp, #0x68]
	bl FUN_020117E8
	ldr r1, [sp, #0x94]
	add r7, r0, #0
	bl FUN_02011AC0
	mov r2, #0x42
	ldr r3, [sp, #0xa0]
	lsl r2, r2, #2
	add r0, r7, #0
	add r1, r6, #0
	add r2, r3, r2
	bl FUN_020118C4
	cmp r4, #0
	bne _022323D0
	add r0, sp, #0x3c
	bl FUN_02019178
_022323D0:
	str r7, [r5]
	add r3, sp, #0x30
	ldmia r3!, {r0, r1}
	add r2, r5, #4
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [sp, #0x2c]
	strh r0, [r5, #0x10]
	add sp, #0x7c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_022323E8
MOD12_022323E8: ; 0x022323E8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r6, #0
	add r4, r5, #0
	add r4, #0x44
	add r7, r6, #0
_022323F4:
	ldr r0, [r5, #0x40]
	cmp r0, #0
	beq _02232406
	bl FUN_02011870
	add r0, r4, #0
	bl FUN_0201D5E8
	str r7, [r5, #0x40]
_02232406:
	add r6, r6, #1
	add r5, #0x14
	add r4, #0x14
	cmp r6, #0xc
	blt _022323F4
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_02232414
MOD12_02232414: ; 0x02232414
	push {r4, lr}
	add r4, r0, #0
	mov r0, #5
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0223242E
	bl MOD12_0223349C
	mov r0, #5
	mov r1, #0
	lsl r0, r0, #6
	str r1, [r4, r0]
_0223242E:
	pop {r4, pc}

	thumb_func_start MOD12_02232430
MOD12_02232430: ; 0x02232430
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp]
	mov r0, #0
	mov r7, #0x51
	str r0, [sp, #4]
	add r6, r0, #0
	lsl r7, r7, #2
_02232440:
	ldr r5, [sp]
	mov r4, #0
_02232444:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _02232454
	bl MOD12_02233534
	mov r0, #0x51
	lsl r0, r0, #2
	str r6, [r5, r0]
_02232454:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _02232444
	ldr r0, [sp]
	add r0, #0x18
	str r0, [sp]
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #4
	blt _02232440
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD12_02232470
MOD12_02232470: ; 0x02232470
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	add r5, r0, #0
	add r7, r1, #0
	ldr r1, [r5, #4]
	ldr r4, _02232504 ; =MOD12_02244E70
	ldr r0, [r1, #0x18]
	add r3, sp, #8
	str r0, [sp, #4]
	ldr r0, [r1, #0x1c]
	mov r2, #6
	str r0, [sp]
_02232488:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02232488
	ldr r0, [r4]
	mov r4, #0
	str r0, [r3]
	add r6, sp, #8
	b _022324FC
_0223249A:
	lsl r0, r4, #2
	add r1, r5, r0
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _022324AC
	bl ErrorHandling
_022324AC:
	lsl r0, r4, #1
	ldrh r0, [r7, r0]
	cmp r0, #0
	beq _022324FA
	mov r0, #0xb5
	add r1, r5, r4
	lsl r0, r0, #2
	ldrb r2, [r1, r0]
	ldr r0, _02232508 ; =0x000080F6
	ldr r1, _0223250C ; =MOD12_02244DB4
	add r0, r4, r0
	str r0, [sp, #0x1c]
	lsl r0, r4, #2
	ldrh r1, [r1, r0]
	add r3, sp, #8
	strh r1, [r6]
	ldr r1, _0223250C ; =MOD12_02244DB4
	add r0, r1, r0
	ldrh r0, [r0, #2]
	ldr r1, [sp]
	strh r0, [r6, #2]
	ldr r0, [sp, #4]
	bl MOD12_02240E98
	lsl r1, r4, #2
	mov r2, #0x13
	mov r3, #0x11
	add r1, r5, r1
	lsl r2, r2, #4
	str r0, [r1, r2]
	add r0, r2, #0
	ldr r0, [r1, r0]
	mov r1, #0
	mov r2, #2
	ldrsh r1, [r6, r1]
	ldrsh r2, [r6, r2]
	lsl r3, r3, #0x10
	bl FUN_0200C750
_022324FA:
	add r4, r4, #1
_022324FC:
	cmp r4, #4
	blt _0223249A
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02232504: .word MOD12_02244E70
_02232508: .word 0x000080F6
_0223250C: .word MOD12_02244DB4

	thumb_func_start MOD12_02232510
MOD12_02232510: ; 0x02232510
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	mov r7, #0x13
	add r5, r0, #0
	add r6, r4, #0
	lsl r7, r7, #4
_0223251C:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _0223252C
	bl MOD12_02240EC8
	mov r0, #0x13
	lsl r0, r0, #4
	str r6, [r5, r0]
_0223252C:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0223251C
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_02232538
MOD12_02232538: ; 0x02232538
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5, #4]
	add r6, r1, #0
	ldr r0, [r0, #0x24]
	add r7, r3, #0
	mov r1, #4
	add r4, r2, #0
	str r0, [sp, #4]
	bl FUN_0201886C
	mov ip, r0
	lsl r0, r7, #2
	add r0, r5, r0
	ldr r0, [r0, #0x20]
	ldr r7, [r4]
	str r0, [sp]
	ldr r0, [sp, #0x20]
	lsl r0, r0, #1
	ldrsh r1, [r6, r0]
	ldr r0, [r4, #4]
	cmp r7, r0
	bgt _0223259E
	lsl r6, r7, #5
_0223256A:
	lsl r2, r6, #1
	mov r0, ip
	add r5, r0, r2
	ldr r0, [sp]
	ldr r3, [r4, #0xc]
	add r2, r0, r2
	ldr r0, [r4, #8]
	cmp r0, r3
	bgt _02232594
	lsl r3, r0, #1
	add r2, r2, r3
	add r3, r5, r3
_02232582:
	ldrh r5, [r2]
	add r0, r0, #1
	add r2, r2, #2
	add r5, r1, r5
	strh r5, [r3]
	ldr r5, [r4, #0xc]
	add r3, r3, #2
	cmp r0, r5
	ble _02232582
_02232594:
	ldr r0, [r4, #4]
	add r7, r7, #1
	add r6, #0x20
	cmp r7, r0
	ble _0223256A
_0223259E:
	ldr r0, [sp, #4]
	mov r1, #4
	bl FUN_0201AC68
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_022325AC
MOD12_022325AC: ; 0x022325AC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	ldr r6, _02232624 ; =MOD12_02244DD8
	add r5, r2, #0
	add r4, r0, #0
	add r3, r1, #0
	add r2, sp, #4
	ldmia r6!, {r0, r1}
	add r7, r2, #0
	stmia r2!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r6]
	str r0, [r2]
	mov r0, #0
	mvn r0, r0
	cmp r3, r0
	beq _022325EC
	mov r0, #0x20
	str r0, [sp]
	lsl r1, r3, #2
	ldr r0, [r4, #4]
	add r3, r5, #4
	lsl r3, r3, #0x14
	ldr r0, [r0, #0x50]
	ldr r1, [r7, r1]
	mov r2, #1
	lsr r3, r3, #0x10
	bl FUN_02003054
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_022325EC:
	ldr r2, _02232628 ; =MOD12_02244D64
	lsl r1, r5, #1
	mov r0, #0
	add r1, r2, r1
	str r0, [sp]
	ldr r3, _0223262C ; =MOD12_02244F24
	lsl r2, r5, #4
	add r2, r3, r2
	add r0, r4, #0
	mov r3, #2
	bl MOD12_02232538
	mov r2, #0x20
	str r2, [sp]
	ldr r0, [r4, #4]
	add r3, r5, #4
	lsl r3, r3, #0x14
	ldr r1, [r4, #0x38]
	add r2, #0xe0
	add r1, r1, r2
	ldr r0, [r0, #0x50]
	mov r2, #1
	lsr r3, r3, #0x10
	bl FUN_02003054
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02232624: .word MOD12_02244DD8
_02232628: .word MOD12_02244D64
_0223262C: .word MOD12_02244F24

	thumb_func_start MOD12_02232630
MOD12_02232630: ; 0x02232630
	ldr r3, _02232634 ; =MOD12_02232638
	bx r3
	.align 2, 0
_02232634: .word MOD12_02232638

	thumb_func_start MOD12_02232638
MOD12_02232638: ; 0x02232638
	push {r4, lr}
	add r4, r0, #0
	bl MOD12_02232414
	add r0, r4, #0
	bl MOD12_02232430
	add r0, r4, #0
	bl MOD12_02232510
	add r0, r4, #0
	bl MOD12_022323E8
	pop {r4, pc}

	thumb_func_start MOD12_02232654
MOD12_02232654: ; 0x02232654
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _02232664
	bl ErrorHandling
_02232664:
	mov r0, #0xb9
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	mov r2, #0x20
	bl MI_CpuFill8
	ldr r2, _02232680 ; =0x00000514
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
	.align 2, 0
_02232680: .word 0x00000514

	thumb_func_start MOD12_02232684
MOD12_02232684: ; 0x02232684
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _022326A2
	bl FUN_0200CAB4
	mov r0, #0xb9
	lsl r0, r0, #2
	mov r1, #0
	add r0, r4, r0
	mov r2, #0x20
	str r1, [r4, #0x10]
	bl MI_CpuFill8
_022326A2:
	pop {r4, pc}

	thumb_func_start MOD12_022326A4
MOD12_022326A4: ; 0x022326A4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	mov r3, #0xb9
	add r5, r1, #0
	lsl r3, r3, #2
	ldrsh r0, [r5, r3]
	cmp r0, #0
	beq _022326BE
	cmp r0, #1
	beq _02232730
	cmp r0, #2
	beq _0223274C
	b _022327BC
_022326BE:
	mov r0, #2
	str r0, [sp]
	add r1, r3, #0
	add r2, r3, #0
	add r3, #0x1c
	add r1, #0x10
	add r2, #0x14
	ldrb r3, [r5, r3]
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	add r0, r5, #0
	bl MOD12_02232538
	ldr r0, _022327DC ; =0x00000301
	add r2, sp, #4
	ldrb r1, [r5, r0]
	mov r0, #0x14
	mul r0, r1
	add r0, r5, r0
	ldr r0, [r0, #0x40]
	add r1, sp, #8
	bl FUN_020119A4
	ldr r0, _022327DC ; =0x00000301
	ldr r2, [sp, #4]
	ldrb r1, [r5, r0]
	mov r0, #0x14
	sub r2, r2, #2
	mul r0, r1
	add r0, r5, r0
	ldr r0, [r0, #0x40]
	ldr r1, [sp, #8]
	bl FUN_020118C4
	mov r7, #0xba
	mov r6, #0
	add r4, r5, #0
	lsl r7, r7, #2
_0223270A:
	ldr r0, [r4, r7]
	cmp r0, #0
	beq _0223271A
	mov r1, #0
	ldr r0, [r0]
	sub r2, r1, #2
	bl FUN_0200C7FC
_0223271A:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #3
	blt _0223270A
	mov r0, #0xb9
	lsl r0, r0, #2
	ldrsh r1, [r5, r0]
	add sp, #0xc
	add r1, r1, #1
	strh r1, [r5, r0]
	pop {r4, r5, r6, r7, pc}
_02232730:
	add r0, r3, #2
	ldrsh r0, [r5, r0]
	add r1, r0, #1
	add r0, r3, #2
	strh r1, [r5, r0]
	ldrsh r0, [r5, r0]
	cmp r0, #0
	ble _022327D8
	mov r1, #0
	add r0, r3, #2
	strh r1, [r5, r0]
	ldrsh r0, [r5, r3]
	add r0, r0, #1
	strh r0, [r5, r3]
_0223274C:
	mov r0, #1
	mov r3, #0xbd
	str r0, [sp]
	lsl r3, r3, #2
	add r2, r3, #4
	ldr r1, [r5, r3]
	add r3, #0xc
	ldrb r3, [r5, r3]
	ldr r2, [r5, r2]
	add r0, r5, #0
	bl MOD12_02232538
	ldr r0, _022327DC ; =0x00000301
	add r2, sp, #4
	ldrb r1, [r5, r0]
	mov r0, #0x14
	mul r0, r1
	add r0, r5, r0
	ldr r0, [r0, #0x40]
	add r1, sp, #8
	bl FUN_020119A4
	ldr r0, _022327DC ; =0x00000301
	ldr r2, [sp, #4]
	ldrb r1, [r5, r0]
	mov r0, #0x14
	add r2, r2, #1
	mul r0, r1
	add r0, r5, r0
	ldr r0, [r0, #0x40]
	ldr r1, [sp, #8]
	bl FUN_020118C4
	mov r7, #0xba
	mov r6, #0
	add r4, r5, #0
	lsl r7, r7, #2
_02232796:
	ldr r0, [r4, r7]
	cmp r0, #0
	beq _022327A6
	ldr r0, [r0]
	mov r1, #0
	mov r2, #1
	bl FUN_0200C7FC
_022327A6:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #3
	blt _02232796
	mov r0, #0xb9
	lsl r0, r0, #2
	ldrsh r1, [r5, r0]
	add sp, #0xc
	add r1, r1, #1
	strh r1, [r5, r0]
	pop {r4, r5, r6, r7, pc}
_022327BC:
	add r0, r3, #2
	ldrsh r0, [r5, r0]
	add r1, r0, #1
	add r0, r3, #2
	strh r1, [r5, r0]
	ldrsh r0, [r5, r0]
	cmp r0, #0
	ble _022327D8
	add r0, r5, #0
	bl MOD12_02232630
	add r0, r5, #0
	bl MOD12_02232684
_022327D8:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022327DC: .word 0x00000301

	thumb_func_start MOD12_022327E0
MOD12_022327E0: ; 0x022327E0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	ldr r7, _02232A64 ; =0x00000123
	add r4, r1, #0
	mov r6, #0
	add r5, sp, #0x20
_022327EC:
	ldr r0, [r4, #4]
	mov r2, #0
	ldr r0, [r0]
	ldrb r1, [r0, r7]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	add r1, r6, #0
	add r1, #0x36
	bl GetMonData
	strh r0, [r5]
	add r6, r6, #1
	add r5, r5, #2
	cmp r6, #4
	blt _022327EC
	mov r0, #0xbf
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #3
	bhi _02232870
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02232820: ; jump table
	.short _02232828 - _02232820 - 2 ; case 0
	.short _0223283A - _02232820 - 2 ; case 1
	.short _0223284C - _02232820 - 2 ; case 2
	.short _0223285E - _02232820 - 2 ; case 3
_02232828:
	mov r0, #8
	str r0, [sp, #0xc]
	add r0, sp, #0x20
	ldrh r0, [r0]
	mov r5, #0
	mov r6, #4
	str r0, [sp, #8]
	str r5, [sp, #4]
	b _02232878
_0223283A:
	mov r0, #9
	str r0, [sp, #0xc]
	add r0, sp, #0x20
	ldrh r0, [r0, #2]
	mov r5, #1
	mov r6, #5
	str r0, [sp, #8]
	str r5, [sp, #4]
	b _02232878
_0223284C:
	mov r0, #0xa
	str r0, [sp, #0xc]
	add r0, sp, #0x20
	ldrh r0, [r0, #4]
	mov r5, #2
	mov r6, #6
	str r0, [sp, #8]
	str r5, [sp, #4]
	b _02232878
_0223285E:
	mov r0, #0xb
	str r0, [sp, #0xc]
	add r0, sp, #0x20
	ldrh r0, [r0, #6]
	mov r5, #3
	mov r6, #7
	str r0, [sp, #8]
	str r5, [sp, #4]
	b _02232878
_02232870:
	mov r5, #0
	add r6, r5, #0
	str r5, [sp, #0xc]
	str r5, [sp, #8]
_02232878:
	mov r3, #0xb9
	lsl r3, r3, #2
	ldrsh r0, [r4, r3]
	cmp r0, #0
	beq _0223288C
	cmp r0, #1
	beq _0223295A
	cmp r0, #2
	beq _02232976
	b _02232A42
_0223288C:
	mov r0, #2
	str r0, [sp]
	add r1, r3, #0
	add r2, r3, #0
	add r3, #0x1c
	add r1, #0x10
	add r2, #0x14
	ldrb r3, [r4, r3]
	ldr r1, [r4, r1]
	ldr r2, [r4, r2]
	add r0, r4, #0
	bl MOD12_02232538
	add r7, r4, #0
	mov r0, #0x14
	mul r0, r5
	add r7, #0x40
	str r0, [sp, #0x10]
	ldr r0, [r7, r0]
	add r1, sp, #0x2c
	add r2, sp, #0x28
	bl FUN_020119A4
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x28]
	ldr r0, [r7, r0]
	ldr r1, [sp, #0x2c]
	sub r2, r2, #2
	bl FUN_020118C4
	add r7, r4, #0
	mov r0, #0x14
	mul r0, r6
	add r7, #0x40
	str r0, [sp, #0x14]
	ldr r0, [r7, r0]
	add r1, sp, #0x2c
	add r2, sp, #0x28
	bl FUN_020119A4
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x28]
	ldr r0, [r7, r0]
	ldr r1, [sp, #0x2c]
	sub r2, r2, #2
	bl FUN_020118C4
	ldr r0, [sp, #0xc]
	add r6, r4, #0
	mov r1, #0x14
	add r7, r0, #0
	mul r7, r1
	add r6, #0x40
	ldr r0, [r6, r7]
	add r1, sp, #0x2c
	add r2, sp, #0x28
	bl FUN_020119A4
	ldr r2, [sp, #0x28]
	ldr r0, [r6, r7]
	ldr r1, [sp, #0x2c]
	sub r2, r2, #2
	bl FUN_020118C4
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _0223294C
	lsl r0, r5, #2
	add r1, r4, r0
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #0
	ldr r0, [r0]
	sub r2, r1, #2
	bl FUN_0200C7FC
	mov r7, #0x51
	ldr r0, [sp, #4]
	mov r1, #0x18
	mul r1, r0
	mov r6, #0
	add r5, r4, r1
	lsl r7, r7, #2
_02232934:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _02232944
	mov r1, #0
	ldr r0, [r0]
	sub r2, r1, #2
	bl FUN_0200C7FC
_02232944:
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #6
	blt _02232934
_0223294C:
	mov r0, #0xb9
	lsl r0, r0, #2
	ldrsh r1, [r4, r0]
	add sp, #0x30
	add r1, r1, #1
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_0223295A:
	add r0, r3, #2
	ldrsh r0, [r4, r0]
	add r1, r0, #1
	add r0, r3, #2
	strh r1, [r4, r0]
	ldrsh r0, [r4, r0]
	cmp r0, #0
	ble _02232A5E
	mov r1, #0
	add r0, r3, #2
	strh r1, [r4, r0]
	ldrsh r0, [r4, r3]
	add r0, r0, #1
	strh r0, [r4, r3]
_02232976:
	mov r0, #1
	mov r3, #0xbd
	str r0, [sp]
	lsl r3, r3, #2
	add r2, r3, #4
	ldr r1, [r4, r3]
	add r3, #0xc
	ldrb r3, [r4, r3]
	ldr r2, [r4, r2]
	add r0, r4, #0
	bl MOD12_02232538
	add r7, r4, #0
	mov r0, #0x14
	mul r0, r5
	add r7, #0x40
	str r0, [sp, #0x18]
	ldr r0, [r7, r0]
	add r1, sp, #0x2c
	add r2, sp, #0x28
	bl FUN_020119A4
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #0x28]
	ldr r0, [r7, r0]
	ldr r1, [sp, #0x2c]
	add r2, r2, #1
	bl FUN_020118C4
	add r7, r4, #0
	mov r0, #0x14
	mul r0, r6
	add r7, #0x40
	str r0, [sp, #0x1c]
	ldr r0, [r7, r0]
	add r1, sp, #0x2c
	add r2, sp, #0x28
	bl FUN_020119A4
	ldr r0, [sp, #0x1c]
	ldr r2, [sp, #0x28]
	ldr r0, [r7, r0]
	ldr r1, [sp, #0x2c]
	add r2, r2, #1
	bl FUN_020118C4
	ldr r0, [sp, #0xc]
	add r6, r4, #0
	mov r1, #0x14
	add r7, r0, #0
	mul r7, r1
	add r6, #0x40
	ldr r0, [r6, r7]
	add r1, sp, #0x2c
	add r2, sp, #0x28
	bl FUN_020119A4
	ldr r2, [sp, #0x28]
	ldr r0, [r6, r7]
	ldr r1, [sp, #0x2c]
	add r2, r2, #1
	bl FUN_020118C4
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _02232A34
	lsl r0, r5, #2
	add r1, r4, r0
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #0
	ldr r0, [r0]
	mov r2, #1
	bl FUN_0200C7FC
	mov r7, #0x51
	ldr r0, [sp, #4]
	mov r1, #0x18
	mul r1, r0
	mov r6, #0
	add r5, r4, r1
	lsl r7, r7, #2
_02232A1C:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _02232A2C
	ldr r0, [r0]
	mov r1, #0
	mov r2, #1
	bl FUN_0200C7FC
_02232A2C:
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #6
	blt _02232A1C
_02232A34:
	mov r0, #0xb9
	lsl r0, r0, #2
	ldrsh r1, [r4, r0]
	add sp, #0x30
	add r1, r1, #1
	strh r1, [r4, r0]
	pop {r3, r4, r5, r6, r7, pc}
_02232A42:
	add r0, r3, #2
	ldrsh r0, [r4, r0]
	add r1, r0, #1
	add r0, r3, #2
	strh r1, [r4, r0]
	ldrsh r0, [r4, r0]
	cmp r0, #0
	ble _02232A5E
	add r0, r4, #0
	bl MOD12_02232630
	add r0, r4, #0
	bl MOD12_02232684
_02232A5E:
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02232A64: .word 0x00000123

	thumb_func_start MOD12_02232A68
MOD12_02232A68: ; 0x02232A68
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _02232A78
	bl ErrorHandling
_02232A78:
	mov r0, #0xc1
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	mov r2, #0xc
	bl MI_CpuFill8
	ldr r2, _02232A94 ; =0x00000528
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #0x14]
	pop {r3, r4, r5, pc}
	.align 2, 0
_02232A94: .word 0x00000528

	thumb_func_start MOD12_02232A98
MOD12_02232A98: ; 0x02232A98
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _02232AB6
	bl FUN_0200CAB4
	mov r0, #0xc1
	lsl r0, r0, #2
	mov r1, #0
	add r0, r4, r0
	mov r2, #0xc
	str r1, [r4, #0x14]
	bl MI_CpuFill8
_02232AB6:
	pop {r4, pc}

	thumb_func_start MOD12_02232AB8
MOD12_02232AB8: ; 0x02232AB8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	cmp r4, #0xff
	beq _02232ACE
	ldr r0, _02232AD0 ; =MOD12_02232AD8
	add r1, r5, #0
	bl MOD12_02232A68
	ldr r0, _02232AD4 ; =0x0000030D
	strb r4, [r5, r0]
_02232ACE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02232AD0: .word MOD12_02232AD8
_02232AD4: .word 0x0000030D

	thumb_func_start MOD12_02232AD8
MOD12_02232AD8: ; 0x02232AD8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r0, #0xc1
	add r5, r1, #0
	lsl r0, r0, #2
	add r2, r5, r0
	ldr r0, [r5, #4]
	mov r4, #0
	ldr r3, [r0, #0x50]
	ldrb r0, [r2, #8]
	cmp r0, #0
	beq _02232AF8
	cmp r0, #1
	beq _02232B14
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02232AF8:
	mov r0, #0xa
	lsl r0, r0, #8
	strh r0, [r2, #4]
	ldr r0, _02232B74 ; =0xFFFFFB00
	strh r0, [r2, #6]
	mov r0, #4
	ldrsh r1, [r2, r0]
	mov r0, #6
	ldrsh r0, [r2, r0]
	sub r0, r1, r0
	strh r0, [r2, #4]
	ldrb r0, [r2, #8]
	add r0, r0, #1
	strb r0, [r2, #8]
_02232B14:
	mov r7, #4
	mov r6, #6
	ldrsh r1, [r2, r7]
	ldrsh r0, [r2, r6]
	add r0, r1, r0
	strh r0, [r2, #4]
	ldrsh r6, [r2, r6]
	cmp r6, #0
	blt _02232B34
	ldrsh r1, [r2, r7]
	lsl r0, r7, #0xa
	cmp r1, r0
	blt _02232B34
	strh r0, [r2, #4]
	mov r4, #1
	b _02232B46
_02232B34:
	cmp r6, #0
	bge _02232B46
	mov r0, #4
	ldrsh r0, [r2, r0]
	cmp r0, #0
	bgt _02232B46
	mov r0, #0
	strh r0, [r2, #4]
	mov r4, #1
_02232B46:
	mov r0, #4
	ldrsh r0, [r2, r0]
	mov r1, #1
	asr r0, r0, #8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, _02232B78 ; =0x00007FFF
	str r0, [sp, #4]
	ldrb r2, [r2, #9]
	add r0, r3, #0
	mov r3, #0x10
	lsl r2, r2, #0x14
	lsr r2, r2, #0x10
	bl FUN_020039E8
	cmp r4, #1
	bne _02232B70
	add r0, r5, #0
	bl MOD12_02232A98
_02232B70:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02232B74: .word 0xFFFFFB00
_02232B78: .word 0x00007FFF

	thumb_func_start MOD12_02232B7C
MOD12_02232B7C: ; 0x02232B7C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r1, #0x69
	add r5, r0, #0
	mov r0, #0
	lsl r1, r1, #2
	str r0, [sp, #4]
	add r0, r5, r1
	str r0, [sp]
	add r0, r1, #0
	add r0, #0x50
	add r1, #0xa0
	add r4, r5, #0
	add r7, r5, r0
	add r6, r5, r1
_02232B9A:
	mov r0, #0x1b
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02232BAA
	ldr r0, [sp]
	bl FUN_02019178
_02232BAA:
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02232BBA
	add r0, r7, #0
	bl FUN_02019178
_02232BBA:
	mov r0, #0x25
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02232BCA
	add r0, r6, #0
	bl FUN_02019178
_02232BCA:
	ldr r0, [sp]
	add r4, #0x14
	add r0, #0x14
	str r0, [sp]
	ldr r0, [sp, #4]
	add r7, #0x14
	add r0, r0, #1
	add r6, #0x14
	str r0, [sp, #4]
	cmp r0, #4
	blt _02232B9A
	mov r0, #0xa5
	lsl r0, r0, #2
	add r7, r0, #0
	mov r6, #0
	add r4, r5, r0
	add r7, #0xc
_02232BEC:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _02232BF8
	add r0, r4, #0
	bl FUN_02019178
_02232BF8:
	add r6, r6, #1
	add r5, #0x14
	add r4, #0x14
	cmp r6, #3
	blt _02232BEC
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_02232C08
MOD12_02232C08: ; 0x02232C08
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r5, r0, #0
	mov r0, #0x69
	lsl r0, r0, #2
	add r6, r5, r0
	mov r0, #0
	str r0, [sp, #0x20]
	add r0, r6, #0
	str r0, [sp, #0x18]
	add r0, #0x50
	str r0, [sp, #0x18]
	add r0, r6, #0
	str r0, [sp, #0x14]
	add r0, #0xa0
	add r7, r1, #0
	str r6, [sp, #0x1c]
	str r0, [sp, #0x14]
_02232C2C:
	ldrh r0, [r7]
	cmp r0, #0
	beq _02232C52
	ldr r1, [sp, #0x20]
	add r4, r6, r1
	mov r1, #0xa
	bl GetWazaAttr
	mov r1, #0x4b
	lsl r1, r1, #2
	strb r0, [r4, r1]
	ldrh r0, [r7]
	mov r1, #0xb
	bl GetWazaAttr
	mov r1, #0x13
	lsl r1, r1, #4
	strb r0, [r4, r1]
	b _02232C62
_02232C52:
	ldr r0, [sp, #0x20]
	mov r1, #0
	add r4, r6, r0
	mov r0, #0x4b
	lsl r0, r0, #2
	strb r1, [r4, r0]
	add r0, r0, #4
	strb r1, [r4, r0]
_02232C62:
	ldrh r0, [r7]
	mov r1, #0x15
	bl GetMoveName
	str r0, [sp, #0x24]
	ldr r0, _02232D6C ; =0x00010708
	ldr r1, [sp, #0x24]
	str r0, [sp]
	ldr r3, [sp, #0x1c]
	add r0, r5, #0
	mov r2, #2
	bl MOD12_02232D7C
	ldr r0, [sp, #0x24]
	bl String_dtor
	mov r0, #0x4b
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	add r1, sp, #0x34
	add r2, sp, #0x30
	bl FUN_02083130
	ldr r0, [r5, #4]
	ldr r1, [sp, #0x34]
	ldr r0, [r0, #0x40]
	bl NewString_ReadMsgData
	str r0, [sp, #0x28]
	ldr r0, [r5, #4]
	ldr r1, [sp, #0x30]
	ldr r0, [r0, #0x40]
	bl NewString_ReadMsgData
	add r4, r0, #0
	ldr r0, _02232D70 ; =0x00010200
	ldr r1, [sp, #0x28]
	str r0, [sp]
	ldr r3, [sp, #0x18]
	add r0, r5, #0
	mov r2, #0
	bl MOD12_02232D7C
	ldr r0, _02232D70 ; =0x00010200
	ldr r3, [sp, #0x14]
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0
	bl MOD12_02232D7C
	ldr r0, [sp, #0x28]
	bl String_dtor
	add r0, r4, #0
	bl String_dtor
	ldr r0, [sp, #0x1c]
	add r7, r7, #2
	add r0, #0x14
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r0, #0x14
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r0, #0x14
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x20]
	add r0, r0, #1
	str r0, [sp, #0x20]
	cmp r0, #4
	blt _02232C2C
	mov r7, #0
	add r4, r7, #0
	add r6, #0xf0
_02232CF8:
	ldr r0, [r5, #4]
	mov r1, #0x15
	ldr r0, [r0]
	add r0, r0, r4
	add r0, #0xd0
	ldrh r0, [r0]
	bl MOD12_022314A8
	str r0, [sp, #0x2c]
	ldr r0, _02232D74 ; =0x0001090A
	ldr r1, [sp, #0x2c]
	str r0, [sp]
	add r0, r5, #0
	mov r2, #2
	add r3, r6, #0
	bl MOD12_02232D7C
	ldr r0, [sp, #0x2c]
	bl String_dtor
	add r7, r7, #1
	add r4, #8
	add r6, #0x14
	cmp r7, #3
	blt _02232CF8
	ldr r3, _02232D78 ; =0x000080F1
	ldr r2, [r5, #4]
	add r0, r3, #7
	str r3, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r2, #0x18]
	ldr r1, [r2, #0x1c]
	ldr r2, [r2, #0x50]
	add r3, #0xc
	bl MOD12_02244750
	ldr r3, _02232D78 ; =0x000080F1
	ldr r1, [r5, #4]
	add r0, r3, #7
	str r3, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #5
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [r1, #0x18]
	ldr r1, [r1, #0x1c]
	mov r2, #0x15
	add r3, #0xc
	bl MOD12_022447E8
	mov r1, #0xc5
	lsl r1, r1, #2
	str r0, [r5, r1]
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02232D6C: .word 0x00010708
_02232D70: .word 0x00010200
_02232D74: .word 0x0001090A
_02232D78: .word 0x000080F1

	thumb_func_start MOD12_02232D7C
MOD12_02232D7C: ; 0x02232D7C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r7, r2, #0
	add r6, r1, #0
	add r5, r0, #0
	add r4, r3, #0
	add r0, r6, #0
	add r1, r7, #0
	add r2, sp, #0x1c
	add r3, sp, #0x18
	bl MOD12_02232DE8
	ldr r0, [sp, #0x1c]
	strh r0, [r4, #0x12]
	ldr r0, [sp, #0x18]
	strh r0, [r4, #0x10]
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _02232DA8
	add r0, r4, #0
	bl FUN_02019178
_02232DA8:
	add r0, r4, #0
	bl InitWindow
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [r5, #4]
	ldr r2, [sp, #0x18]
	ldr r0, [r0, #0x24]
	lsl r2, r2, #0x18
	add r1, r4, #0
	lsr r2, r2, #0x18
	mov r3, #2
	bl FUN_020190EC
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x38]
	add r1, r7, #0
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	add r0, r4, #0
	add r2, r6, #0
	str r3, [sp, #0x14]
	bl AddTextPrinterParameterized3
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_02232DE8
MOD12_02232DE8: ; 0x02232DE8
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r6, r2, #0
	add r0, r1, #0
	add r1, r4, #0
	mov r2, #0
	add r7, r3, #0
	bl FUN_02002E14
	add r4, r0, #0
	asr r1, r4, #2
	lsr r1, r1, #0x1d
	add r1, r4, r1
	asr r5, r1, #3
	mov r1, #8
	bl FX_ModS32
	cmp r0, #0
	beq _02232E10
	add r5, r5, #1
_02232E10:
	str r4, [r6]
	str r5, [r7]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_02232E18
MOD12_02232E18: ; 0x02232E18
	push {r4, r5, r6, lr}
	mov r6, #0xc6
	lsl r6, r6, #2
	add r2, r6, #0
	add r5, r0, #0
	sub r2, #0x38
	ldrsb r2, [r5, r2]
	ldr r1, _02232E7C ; =MOD12_02245074
	mov r3, #0x30
	add r4, r2, #0
	mul r4, r3
	add r4, r1, r4
	ldr r2, [r4, #0x20]
	cmp r2, #0
	bne _02232E3C
	sub r3, #0x31
	add r0, r3, #0
	pop {r4, r5, r6, pc}
_02232E3C:
	ldrb r1, [r5, r6]
	cmp r1, #0
	bne _02232E76
	add r0, r6, #4
	ldrb r0, [r5, r0]
	cmp r0, #1
	beq _02232E54
	ldr r1, _02232E80 ; =gMain
	ldr r2, [r1, #0x48]
	ldr r1, _02232E84 ; =0x00000CF3
	tst r1, r2
	beq _02232E70
_02232E54:
	cmp r0, #0
	bne _02232E5E
	ldr r0, _02232E88 ; =0x000005DC
	bl FUN_020054C8
_02232E5E:
	mov r1, #1
	mov r0, #0xc7
	strb r1, [r5, r6]
	mov r2, #0
	lsl r0, r0, #2
	strb r2, [r5, r0]
	ldr r2, [r4, #0x20]
	add r0, r5, #0
	blx r2
_02232E70:
	mov r0, #0
	mvn r0, r0
	pop {r4, r5, r6, pc}
_02232E76:
	mov r1, #0
	blx r2
	pop {r4, r5, r6, pc}
	.align 2, 0
_02232E7C: .word MOD12_02245074
_02232E80: .word gMain
_02232E84: .word 0x00000CF3
_02232E88: .word 0x000005DC

	thumb_func_start MOD12_02232E8C
MOD12_02232E8C: ; 0x02232E8C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	str r1, [sp, #8]
	mov r1, #0x31
	add r5, r0, #0
	lsl r1, r1, #4
	add r0, r5, r1
	str r0, [sp, #0xc]
	add r0, r1, #0
	sub r1, #0x30
	add r0, #8
	add r6, r5, r0
	ldrsb r1, [r5, r1]
	mov r0, #0x30
	ldr r2, _02232FE4 ; =MOD12_02245074
	mul r0, r1
	add r7, r2, r0
	mov r4, #0
	b _02232ED0
_02232EB2:
	ldr r0, [r5, #4]
	ldr r1, _02232FE8 ; =0x00000123
	ldr r0, [r0]
	mov r2, #0
	ldrb r1, [r0, r1]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	add r1, r4, #0
	add r1, #0x36
	bl GetMonData
	lsl r2, r4, #1
	add r1, sp, #0x10
	strh r0, [r1, r2]
	add r4, r4, #1
_02232ED0:
	cmp r4, #4
	blt _02232EB2
	ldr r0, [sp, #8]
	cmp r0, #1
	bne _02232F4E
	ldr r0, [sp, #0xc]
	mov r1, #0
	ldrsb r0, [r0, r1]
	mov r4, #1
	strb r0, [r6, #2]
	ldr r0, [sp, #0xc]
	ldrsb r0, [r0, r4]
	strb r0, [r6, #1]
	ldrsb r0, [r6, r4]
	lsl r3, r0, #1
	mov r0, #2
	ldrsb r2, [r6, r0]
	ldr r0, _02232FEC ; =MOD12_02244D58
	add r0, r0, r3
	ldrb r3, [r2, r0]
	add r0, sp, #0x10
	lsl r2, r3, #1
	ldrh r0, [r0, r2]
	cmp r0, #0
	bne _02232F1A
	ldr r0, [sp, #0xc]
	strb r1, [r0]
	strb r1, [r0, #1]
	strb r1, [r6, #2]
	strb r1, [r6, #1]
	ldrsb r0, [r6, r4]
	lsl r2, r0, #1
	mov r0, #2
	ldrsb r1, [r6, r0]
	ldr r0, _02232FEC ; =MOD12_02244D58
	add r0, r0, r2
	ldrb r3, [r1, r0]
_02232F1A:
	ldr r0, [r7, #0x14]
	lsl r3, r3, #2
	add r0, r0, r3
	ldrb r0, [r0, #1]
	sub r0, #8
	str r0, [sp]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r4, [r7, #0x14]
	mov r0, #0xc5
	add r2, r4, r3
	ldrb r1, [r2, #2]
	ldrb r2, [r2, #3]
	ldrb r3, [r4, r3]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, #8
	sub r2, #8
	add r3, #8
	bl MOD12_02244918
	mov r0, #0
	add sp, #0x1c
	mvn r0, r0
	pop {r4, r5, r6, r7, pc}
_02232F4E:
	ldr r0, _02232FEC ; =MOD12_02244D58
	add r1, sp, #0x18
	mov r2, #4
	bl MI_CpuCopy8
	mov r1, #2
	add r0, r6, #0
	add r2, r1, #0
	add r3, sp, #0x18
	bl MOD12_0223318C
	cmp r0, #0x20
	bhi _02232F7E
	bhs _02232F8A
	cmp r0, #2
	bhi _02232F78
	cmp r0, #1
	blo _02232FDC
	beq _02232FC8
	cmp r0, #2
	b _02232FDC
_02232F78:
	cmp r0, #0x10
	beq _02232F8A
	b _02232FDC
_02232F7E:
	cmp r0, #0x40
	bhi _02232F86
	beq _02232F8A
	b _02232FDC
_02232F86:
	cmp r0, #0x80
	bne _02232FDC
_02232F8A:
	mov r0, #1
	ldrsb r0, [r6, r0]
	ldr r2, _02232FEC ; =MOD12_02244D58
	lsl r3, r0, #1
	mov r0, #2
	ldrsb r1, [r6, r0]
	add r0, r2, r3
	ldrb r1, [r1, r0]
	ldr r0, [r7, #0x14]
	lsl r3, r1, #2
	add r0, r0, r3
	ldrb r0, [r0, #1]
	sub r0, #8
	str r0, [sp]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r4, [r7, #0x14]
	mov r0, #0xc5
	add r2, r4, r3
	ldrb r1, [r2, #2]
	ldrb r2, [r2, #3]
	ldrb r3, [r4, r3]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, #8
	sub r2, #8
	add r3, #8
	bl MOD12_02244918
	b _02232FDC
_02232FC8:
	mov r0, #1
	ldrsb r0, [r6, r0]
	ldr r2, _02232FEC ; =MOD12_02244D58
	add sp, #0x1c
	lsl r3, r0, #1
	mov r0, #2
	ldrsb r1, [r6, r0]
	add r0, r2, r3
	ldrb r0, [r1, r0]
	pop {r4, r5, r6, r7, pc}
_02232FDC:
	mov r0, #0
	mvn r0, r0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02232FE4: .word MOD12_02245074
_02232FE8: .word 0x00000123
_02232FEC: .word MOD12_02244D58

	thumb_func_start MOD12_02232FF0
MOD12_02232FF0: ; 0x02232FF0
	push {r4, r5, r6, r7}
	mov r2, #0x31
	lsl r2, r2, #4
	mov r4, #0
	add r2, r0, r2
	ldr r7, _02233028 ; =MOD12_02244D58
	add r0, r4, #0
	b _0223301E
_02233000:
	lsl r5, r4, #1
	add r3, r0, #0
	add r6, r7, r5
	b _02233018
_02233008:
	ldrb r5, [r3, r6]
	cmp r1, r5
	bne _02233016
	strb r3, [r2]
	strb r4, [r2, #1]
	pop {r4, r5, r6, r7}
	bx lr
_02233016:
	add r3, r3, #1
_02233018:
	cmp r3, #2
	blt _02233008
	add r4, r4, #1
_0223301E:
	cmp r4, #2
	blt _02233000
	pop {r4, r5, r6, r7}
	bx lr
	nop
_02233028: .word MOD12_02244D58

	thumb_func_start MOD12_0223302C
MOD12_0223302C: ; 0x0223302C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r7, #0x31
	lsl r7, r7, #4
	add r3, r7, #0
	add r5, r0, #0
	sub r3, #0x30
	add r0, r7, #0
	ldrsb r6, [r5, r3]
	add r0, #8
	add r4, r5, r0
	mov r3, #0x30
	add r2, r1, #0
	ldr r0, _02233144 ; =MOD12_02245074
	mul r3, r6
	add r1, r5, r7
	add r6, r0, r3
	cmp r2, #1
	bne _022330A0
	mov r0, #2
	ldrsb r2, [r1, r0]
	strb r2, [r4, #2]
	mov r2, #3
	ldrsb r1, [r1, r2]
	strb r1, [r4, #1]
	mov r1, #1
	ldrsb r2, [r4, r1]
	ldrsb r3, [r4, r0]
	lsl r1, r2, #1
	add r2, r2, r1
	ldr r1, _02233148 ; =MOD12_02244D5C
	add r0, r1, r2
	ldrb r1, [r3, r0]
	ldr r0, [r6, #0x14]
	lsl r3, r1, #2
	add r0, r0, r3
	ldrb r0, [r0, #1]
	sub r0, #8
	str r0, [sp]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r4, [r6, #0x14]
	add r0, r7, #4
	add r2, r4, r3
	ldrb r1, [r2, #2]
	ldrb r2, [r2, #3]
	ldrb r3, [r4, r3]
	ldr r0, [r5, r0]
	add r1, #8
	sub r2, #8
	add r3, #8
	bl MOD12_02244918
	mov r0, #0
	add sp, #0x10
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_022330A0:
	ldr r0, _02233148 ; =MOD12_02244D5C
	add r1, sp, #8
	mov r2, #6
	bl MI_CpuCopy8
	add r0, r4, #0
	mov r1, #3
	mov r2, #2
	add r3, sp, #8
	bl MOD12_0223318C
	cmp r0, #0x20
	bhi _022330D2
	bhs _022330DE
	cmp r0, #2
	bhi _022330CC
	cmp r0, #1
	blo _0223313A
	beq _0223311E
	cmp r0, #2
	beq _02233134
	b _0223313A
_022330CC:
	cmp r0, #0x10
	beq _022330DE
	b _0223313A
_022330D2:
	cmp r0, #0x40
	bhi _022330DA
	beq _022330DE
	b _0223313A
_022330DA:
	cmp r0, #0x80
	bne _0223313A
_022330DE:
	mov r0, #1
	ldrsb r1, [r4, r0]
	ldr r2, _02233148 ; =MOD12_02244D5C
	lsl r0, r1, #1
	add r3, r1, r0
	mov r0, #2
	ldrsb r1, [r4, r0]
	add r0, r2, r3
	ldrb r1, [r1, r0]
	ldr r0, [r6, #0x14]
	lsl r3, r1, #2
	add r0, r0, r3
	ldrb r0, [r0, #1]
	sub r0, #8
	str r0, [sp]
	mov r0, #0x11
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r4, [r6, #0x14]
	mov r0, #0xc5
	add r2, r4, r3
	ldrb r1, [r2, #2]
	ldrb r2, [r2, #3]
	ldrb r3, [r4, r3]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, #8
	sub r2, #8
	add r3, #8
	bl MOD12_02244918
	b _0223313A
_0223311E:
	mov r0, #1
	ldrsb r1, [r4, r0]
	ldr r2, _02233148 ; =MOD12_02244D5C
	add sp, #0x10
	lsl r0, r1, #1
	add r3, r1, r0
	mov r0, #2
	ldrsb r1, [r4, r0]
	add r0, r2, r3
	ldrb r0, [r1, r0]
	pop {r3, r4, r5, r6, r7, pc}
_02233134:
	add sp, #0x10
	mov r0, #3
	pop {r3, r4, r5, r6, r7, pc}
_0223313A:
	mov r0, #0
	mvn r0, r0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02233144: .word MOD12_02245074
_02233148: .word MOD12_02244D5C

	thumb_func_start MOD12_0223314C
MOD12_0223314C: ; 0x0223314C
	push {r4, r5, r6, r7}
	cmp r1, #3
	beq _02233184
	mov r2, #0x31
	lsl r2, r2, #4
	add r3, r0, r2
	mov r5, #0
	ldr r0, _02233188 ; =MOD12_02244D5C
	add r2, r5, #0
	b _02233180
_02233160:
	lsl r6, r5, #1
	add r6, r5, r6
	add r4, r2, #0
	add r7, r0, r6
	b _0223317A
_0223316A:
	ldrb r6, [r4, r7]
	cmp r1, r6
	bne _02233178
	strb r4, [r3, #2]
	strb r5, [r3, #3]
	pop {r4, r5, r6, r7}
	bx lr
_02233178:
	add r4, r4, #1
_0223317A:
	cmp r4, #3
	blt _0223316A
	add r5, r5, #1
_02233180:
	cmp r5, #2
	blt _02233160
_02233184:
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
_02233188: .word MOD12_02244D5C

	thumb_func_start MOD12_0223318C
MOD12_0223318C: ; 0x0223318C
	push {r3, r4, r5, r6, r7, lr}
	mov r7, #2
	add r4, r1, #0
	ldrsb r1, [r0, r7]
	mov r5, #1
	add r6, r2, #0
	str r1, [sp]
	ldrsb r1, [r0, r5]
	add r2, r3, #0
	mov r3, #0x40
	mov ip, r1
	ldr r1, _02233364 ; =gMain
	ldr r1, [r1, #0x48]
	tst r3, r1
	beq _022331FA
	mov r1, ip
	sub r1, r1, #1
	strb r1, [r0, #1]
	ldrsb r1, [r0, r5]
	cmp r1, #0
	bge _022331BA
	mov r1, #0
	strb r1, [r0, #1]
_022331BA:
	cmp r2, #0
	beq _022331F6
	mov r3, #1
	mov r1, #2
	ldrsb r3, [r0, r3]
	ldrsb r1, [r0, r1]
	mul r3, r4
	add r1, r1, r3
	ldrb r1, [r2, r1]
	cmp r1, #0xff
	bne _022331F6
	add r1, r0, #1
	mov r7, #0
	mov r6, #1
_022331D6:
	ldrsb r3, [r1, r7]
	sub r3, r3, #1
	strb r3, [r1]
	ldrsb r3, [r0, r6]
	cmp r3, #0
	bge _022331E8
	mov r1, ip
	strb r1, [r0, #1]
	b _022331F6
_022331E8:
	mov r5, #2
	ldrsb r5, [r0, r5]
	mul r3, r4
	add r5, r2, r5
	ldrb r3, [r3, r5]
	cmp r3, #0xff
	beq _022331D6
_022331F6:
	mov r5, #0x40
	b _0223330E
_022331FA:
	mov r3, #0x80
	tst r3, r1
	beq _02233250
	mov r1, ip
	add r1, r1, #1
	strb r1, [r0, #1]
	ldrsb r1, [r0, r5]
	cmp r1, r6
	blt _02233210
	sub r1, r6, #1
	strb r1, [r0, #1]
_02233210:
	cmp r2, #0
	beq _0223324C
	mov r3, #1
	mov r1, #2
	ldrsb r3, [r0, r3]
	ldrsb r1, [r0, r1]
	mul r3, r4
	add r1, r1, r3
	ldrb r1, [r2, r1]
	cmp r1, #0xff
	bne _0223324C
	add r1, r0, #1
	mov r7, #1
_0223322A:
	mov r3, #0
	ldrsb r3, [r1, r3]
	add r3, r3, #1
	strb r3, [r1]
	ldrsb r3, [r0, r7]
	cmp r3, r6
	blt _0223323E
	mov r1, ip
	strb r1, [r0, #1]
	b _0223324C
_0223323E:
	mov r5, #2
	ldrsb r5, [r0, r5]
	mul r3, r4
	add r5, r2, r5
	ldrb r3, [r3, r5]
	cmp r3, #0xff
	beq _0223322A
_0223324C:
	mov r5, #0x80
	b _0223330E
_02233250:
	mov r3, #0x20
	tst r3, r1
	beq _022332A6
	ldr r1, [sp]
	sub r1, r1, #1
	strb r1, [r0, #2]
	ldrsb r1, [r0, r7]
	cmp r1, #0
	bge _02233266
	mov r1, #0
	strb r1, [r0, #2]
_02233266:
	cmp r2, #0
	beq _022332A2
	mov r3, #1
	mov r1, #2
	ldrsb r3, [r0, r3]
	ldrsb r1, [r0, r1]
	mul r3, r4
	add r1, r1, r3
	ldrb r1, [r2, r1]
	cmp r1, #0xff
	bne _022332A2
	add r5, r0, #2
	mov r7, #0
	mov r6, #2
_02233282:
	ldrsb r1, [r5, r7]
	sub r1, r1, #1
	strb r1, [r5]
	ldrsb r3, [r0, r6]
	cmp r3, #0
	bge _02233294
	ldr r1, [sp]
	strb r1, [r0, #2]
	b _022332A2
_02233294:
	mov r1, #1
	ldrsb r1, [r0, r1]
	add r3, r2, r3
	mul r1, r4
	ldrb r1, [r1, r3]
	cmp r1, #0xff
	beq _02233282
_022332A2:
	mov r5, #0x20
	b _0223330E
_022332A6:
	mov r3, #0x10
	tst r3, r1
	beq _022332FC
	ldr r1, [sp]
	add r1, r1, #1
	strb r1, [r0, #2]
	ldrsb r1, [r0, r7]
	cmp r1, r4
	blt _022332BC
	sub r1, r4, #1
	strb r1, [r0, #2]
_022332BC:
	cmp r2, #0
	beq _022332F8
	mov r3, #1
	mov r1, #2
	ldrsb r3, [r0, r3]
	ldrsb r1, [r0, r1]
	mul r3, r4
	add r1, r1, r3
	ldrb r1, [r2, r1]
	cmp r1, #0xff
	bne _022332F8
	add r5, r0, #2
	mov r7, #0
	mov r6, #2
_022332D8:
	ldrsb r1, [r5, r7]
	add r1, r1, #1
	strb r1, [r5]
	ldrsb r3, [r0, r6]
	cmp r3, r4
	blt _022332EA
	ldr r1, [sp]
	strb r1, [r0, #2]
	b _022332F8
_022332EA:
	mov r1, #1
	ldrsb r1, [r0, r1]
	add r3, r2, r3
	mul r1, r4
	ldrb r1, [r1, r3]
	cmp r1, #0xff
	beq _022332D8
_022332F8:
	mov r5, #0x10
	b _0223330E
_022332FC:
	add r3, r1, #0
	tst r3, r5
	bne _0223330E
	tst r1, r7
	beq _0223330A
	add r5, r7, #0
	b _0223330E
_0223330A:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223330E:
	cmp r2, #0
	beq _02233338
	mov r1, ip
	add r3, r4, #0
	mul r3, r1
	ldr r1, [sp]
	add r1, r1, r3
	mov r3, #2
	ldrsb r6, [r0, r3]
	mov r3, #1
	ldrsb r3, [r0, r3]
	ldrb r1, [r2, r1]
	mul r3, r4
	add r3, r6, r3
	ldrb r2, [r2, r3]
	cmp r1, r2
	bne _02233338
	ldr r1, [sp]
	strb r1, [r0, #2]
	mov r1, ip
	strb r1, [r0, #1]
_02233338:
	mov r1, #2
	ldrsb r2, [r0, r1]
	ldr r1, [sp]
	cmp r2, r1
	bne _0223334C
	mov r1, #1
	ldrsb r1, [r0, r1]
	mov r0, ip
	cmp r1, r0
	beq _02233354
_0223334C:
	ldr r0, _02233368 ; =0x000005DC
	bl FUN_020054C8
	b _0223335E
_02233354:
	mov r0, #0xf0
	tst r0, r5
	beq _0223335E
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223335E:
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02233364: .word gMain
_02233368: .word 0x000005DC

	thumb_func_start MOD12_0223336C
MOD12_0223336C: ; 0x0223336C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0
	mov r2, #0xb7
	add r4, r1, #0
	str r0, [sp]
	lsl r2, r2, #2
	ldr r0, [r4, #4]
	ldr r2, [r4, r2]
	mov r3, #6
	ldr r0, [r0, #0x24]
	ldr r2, [r2, #0x14]
	mov r1, #4
	lsl r3, r3, #0xc
	bl FUN_02017E14
	mov r0, #0xb6
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0xb6
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_022333A8
MOD12_022333A8: ; 0x022333A8
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	mov r0, #0x2e
	lsl r0, r0, #4
	ldrsb r1, [r1, r0]
	mov r0, #0x30
	mov r4, #0
	ldr r2, _022333F0 ; =MOD12_02245074
	mul r0, r1
	ldr r6, _022333F4 ; =0x0000FFFF
	add r5, r2, r0
	add r7, r4, #0
_022333C0:
	ldrh r0, [r5, #4]
	cmp r0, r6
	bne _022333D4
	add r0, r4, #4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, r7, #0
	bl FUN_0201797C
	b _022333E0
_022333D4:
	add r0, r4, #4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r1, #1
	bl FUN_0201797C
_022333E0:
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, #4
	blt _022333C0
	ldr r0, [sp]
	bl FUN_0200CAB4
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022333F0: .word MOD12_02245074
_022333F4: .word 0x0000FFFF

	thumb_func_start MOD12_022333F8
MOD12_022333F8: ; 0x022333F8
	push {r4, r5, lr}
	sub sp, #0xc
	mov r2, #1
	str r2, [sp]
	mov r2, #2
	str r2, [sp, #4]
	ldr r2, _02233440 ; =0x000080FB
	mov r3, #0x2a
	str r2, [sp, #8]
	mov r2, #0x2e
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _02233444 ; =0x000080F6
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x2b
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _02233444 ; =0x000080F6
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x2c
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02233440: .word 0x000080FB
_02233444: .word 0x000080F6

	thumb_func_start MOD12_02233448
MOD12_02233448: ; 0x02233448
	push {r3, r4, r5, lr}
	add r5, r2, #0
	ldr r2, _02233474 ; =MOD12_02245168
	bl FUN_0200C154
	mov r1, #0x58
	mul r1, r5
	add r1, #0x28
	lsl r1, r1, #0x10
	mov r3, #0x11
	add r4, r0, #0
	asr r1, r1, #0x10
	mov r2, #0x60
	lsl r3, r3, #0x10
	bl FUN_0200C750
	ldr r0, [r4]
	bl FUN_0200C59C
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_02233474: .word MOD12_02245168

	thumb_func_start MOD12_02233478
MOD12_02233478: ; 0x02233478
	push {r4, lr}
	ldr r1, _02233494 ; =0x000080FB
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _02233498 ; =0x000080F6
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _02233498 ; =0x000080F6
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_02233494: .word 0x000080FB
_02233498: .word 0x000080F6

	thumb_func_start MOD12_0223349C
MOD12_0223349C: ; 0x0223349C
	ldr r3, _022334A0 ; =FUN_0200C3DC
	bx r3
	.align 2, 0
_022334A0: .word FUN_0200C3DC

	thumb_func_start MOD12_022334A4
MOD12_022334A4: ; 0x022334A4
	push {r4, r5, lr}
	sub sp, #0xc
	mov r2, #1
	str r2, [sp]
	mov r2, #2
	str r2, [sp, #4]
	ldr r2, _022334EC ; =0x000080FA
	mov r3, #0x2d
	str r2, [sp, #8]
	mov r2, #0x2e
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _022334F0 ; =0x000080F5
	mov r2, #0x2e
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	add r3, r2, #0
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _022334F0 ; =0x000080F5
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x2f
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_022334EC: .word 0x000080FA
_022334F0: .word 0x000080F5

	thumb_func_start MOD12_022334F4
MOD12_022334F4: ; 0x022334F4
	push {r4, r5, r6, lr}
	add r5, r2, #0
	ldr r2, [sp, #0x10]
	add r6, r3, #0
	cmp r2, #0
	blt _02233508
	ldr r2, _0223352C ; =MOD12_02245134
	bl FUN_0200C154
	b _0223350E
_02233508:
	ldr r2, _02233530 ; =MOD12_0224519C
	bl FUN_0200C154
_0223350E:
	add r4, r0, #0
	lsl r1, r5, #0x10
	lsl r2, r6, #0x10
	mov r3, #0x11
	add r0, r4, #0
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	lsl r3, r3, #0x10
	bl FUN_0200C750
	ldr r0, [r4]
	bl FUN_0200C59C
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223352C: .word MOD12_02245134
_02233530: .word MOD12_0224519C

	thumb_func_start MOD12_02233534
MOD12_02233534: ; 0x02233534
	ldr r3, _02233538 ; =FUN_0200C3DC
	bx r3
	.align 2, 0
_02233538: .word FUN_0200C3DC

	thumb_func_start MOD12_0223353C
MOD12_0223353C: ; 0x0223353C
	push {r4, lr}
	ldr r1, _02233558 ; =0x000080FA
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _0223355C ; =0x000080F5
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _0223355C ; =0x000080F5
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_02233558: .word 0x000080FA
_0223355C: .word 0x000080F5

	thumb_func_start MOD12_02233560
MOD12_02233560: ; 0x02233560
	ldr r0, _02233568 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	bx lr
	.align 2, 0
_02233568: .word 0x04000050

	thumb_func_start MOD12_0223356C
MOD12_0223356C: ; 0x0223356C
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, [r0, #0x30]
	add r5, r1, #0
	mov r1, #2
	add r4, r2, #0
	bl FUN_0201886C
	mov r1, #0xc0
	mul r1, r5
	lsl r1, r1, #1
	mov r2, #0
	ldr r6, _022335AC ; =0x00000FFF
	add r0, r0, r1
	add r3, r2, #0
	lsl r4, r4, #0xc
_0223358A:
	lsl r5, r3, #1
	mov r1, #0
	add r5, r0, r5
_02233590:
	ldrh r7, [r5]
	add r1, r1, #1
	and r7, r6
	orr r7, r4
	strh r7, [r5]
	add r5, r5, #2
	cmp r1, #0xa
	blt _02233590
	add r2, r2, #1
	add r3, #0x20
	cmp r2, #6
	blt _0223358A
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022335AC: .word 0x00000FFF

	thumb_func_start MOD12_022335B0
MOD12_022335B0: ; 0x022335B0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r4, #0
	ldr r6, _022335DC ; =MOD12_022451D0
	ldr r7, _022335E0 ; =0x00000231
	b _022335CC
_022335BC:
	add r2, r5, r4
	ldrb r2, [r2, r7]
	add r0, r5, #0
	add r1, r4, #0
	ldrb r2, [r6, r2]
	bl MOD12_0223356C
	add r4, r4, #1
_022335CC:
	cmp r4, #4
	blt _022335BC
	ldr r0, [r5, #0x30]
	mov r1, #2
	bl FUN_0201AC68
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022335DC: .word MOD12_022451D0
_022335E0: .word 0x00000231

	thumb_func_start MOD12_022335E4
MOD12_022335E4: ; 0x022335E4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x15
	mov r1, #0xc
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0xc
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [r5, #0x5c]
	ldr r2, _02233614 ; =0x00009CA4
	str r0, [r4]
	ldr r0, _02233618 ; =MOD12_02233648
	add r1, r4, #0
	strb r6, [r4, #0xa]
	bl FUN_0200CA44
	str r0, [r4, #4]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	nop
_02233614: .word 0x00009CA4
_02233618: .word MOD12_02233648

	thumb_func_start MOD12_0223361C
MOD12_0223361C: ; 0x0223361C
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #0xb]
	cmp r0, #0
	beq _0223362A
	bl ErrorHandling
_0223362A:
	ldr r0, [r4, #4]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD12_02233638
MOD12_02233638: ; 0x02233638
	mov r1, #1
	strb r1, [r0, #0xb]
	mov r1, #0xa
	lsl r1, r1, #8
	strh r1, [r0, #8]
	bx lr

	thumb_func_start MOD12_02233644
MOD12_02233644: ; 0x02233644
	ldrb r0, [r0, #0xb]
	bx lr

	thumb_func_start MOD12_02233648
MOD12_02233648: ; 0x02233648
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	ldrb r0, [r4, #0xb]
	cmp r0, #0
	beq _0223369E
	mov r0, #8
	ldrsh r0, [r4, r0]
	ldr r2, _022336A4 ; =MOD12_022451D0
	mov r1, #0
	asr r0, r0, #8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, _022336A8 ; =0x00007FFF
	str r0, [sp, #4]
	ldrb r3, [r4, #0xa]
	ldr r0, [r4]
	ldrb r2, [r2, r3]
	mov r3, #4
	lsl r2, r2, #4
	add r2, r2, #1
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	bl FUN_020039E8
	mov r1, #8
	ldrsh r2, [r4, r1]
	cmp r2, #0
	bne _0223368C
	mov r0, #0
	add sp, #8
	strb r0, [r4, #0xb]
	pop {r4, pc}
_0223368C:
	mov r0, #0xa
	lsl r0, r0, #6
	sub r0, r2, r0
	strh r0, [r4, #8]
	ldrsh r0, [r4, r1]
	cmp r0, #0
	bge _0223369E
	mov r0, #0
	strh r0, [r4, #8]
_0223369E:
	add sp, #8
	pop {r4, pc}
	nop
_022336A4: .word MOD12_022451D0
_022336A8: .word 0x00007FFF

	thumb_func_start MOD12_022336AC
MOD12_022336AC: ; 0x022336AC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	str r0, [sp, #0x18]
	add r0, #8
	str r0, [sp, #0x18]
	add r6, r1, #0
	lsl r0, r6, #2
	ldr r1, [sp, #0x18]
	str r0, [sp, #0x1c]
	ldr r0, [r1, r0]
	bl FUN_02007534
	lsl r0, r6, #4
	add r0, r5, r0
	ldr r0, [r0, #0x58]
	cmp r0, #0
	bne _022336D4
	bl ErrorHandling
_022336D4:
	add r2, r5, #0
	add r2, #0x58
	lsl r1, r6, #4
	add r0, r2, r1
	str r0, [sp, #0x14]
	ldr r0, [r2, r1]
	mov r2, #0x32
	mov r1, #0
	lsl r2, r2, #6
	bl MI_CpuFill8
	ldr r1, [sp, #0x14]
	lsl r0, r6, #5
	str r1, [sp]
	mov r1, #0x15
	str r1, [sp, #4]
	mov r1, #0xd8
	sub r1, r1, r0
	str r1, [sp, #8]
	mov r1, #0x70
	sub r0, r1, r0
	str r0, [sp, #0xc]
	ldr r0, _02233754 ; =0xFFFFFE00
	add r7, r5, #0
	str r0, [sp, #0x10]
	ldr r2, [r5]
	lsl r4, r6, #2
	ldr r0, [r5, #4]
	ldr r2, [r2, r4]
	add r7, #8
	add r1, r6, #0
	mov r3, #0
	bl FUN_02082E64
	str r0, [r7, r4]
	ldr r0, [r7, r4]
	mov r1, #6
	mov r2, #1
	bl FUN_02007558
	ldr r0, [r7, r4]
	mov r1, #0x25
	mov r2, #1
	bl FUN_02007558
	ldr r0, [r5]
	mov r1, #5
	ldr r0, [r0, r4]
	mov r2, #0
	bl GetMonData
	bl MOD08_0222A6C8
	cmp r0, #1
	bne _02233750
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	mov r2, #1
	ldr r0, [r1, r0]
	mov r1, #0x23
	bl FUN_02007558
_02233750:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02233754: .word 0xFFFFFE00

	thumb_func_start MOD12_02233758
MOD12_02233758: ; 0x02233758
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r0, [sp, #0x14]
	ldr r7, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x1c]
	add r6, r0, #0
	add r0, r7, #0
	str r0, [sp, #0x18]
	add r0, #0x58
	ldr r4, [sp, #0x1c]
	str r0, [sp, #0x18]
	add r5, r7, #0
_02233772:
	ldr r0, [r7, #0x58]
	cmp r0, #0
	beq _0223377C
	bl ErrorHandling
_0223377C:
	mov r1, #0x32
	mov r0, #0x15
	lsl r1, r1, #6
	bl AllocFromHeap
	str r0, [r7, #0x58]
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #0x14]
	str r0, [sp]
	mov r0, #0x15
	str r0, [sp, #4]
	mov r0, #0xd8
	sub r0, r0, r6
	str r0, [sp, #8]
	mov r0, #0x70
	sub r0, r0, r6
	str r0, [sp, #0xc]
	ldr r0, _02233844 ; =0xFFFFFE00
	ldr r1, [sp, #0x1c]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	ldr r2, [r2]
	ldr r0, [r0, #4]
	ldr r2, [r2, r4]
	mov r3, #0
	bl FUN_02082E64
	str r0, [r5, #8]
	mov r1, #6
	mov r2, #1
	bl FUN_02007558
	ldr r0, [r5, #8]
	mov r1, #0x25
	mov r2, #1
	bl FUN_02007558
	ldr r0, [sp, #0x14]
	mov r1, #5
	ldr r0, [r0]
	mov r2, #0
	ldr r0, [r0, r4]
	bl GetMonData
	bl MOD08_0222A6C8
	cmp r0, #1
	bne _022337E6
	ldr r0, [r5, #8]
	mov r1, #0x23
	mov r2, #1
	bl FUN_02007558
_022337E6:
	ldr r0, [sp, #0x18]
	add r7, #0x10
	add r0, #0x10
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	add r6, #0x20
	add r0, r0, #1
	add r4, r4, #4
	add r5, r5, #4
	str r0, [sp, #0x1c]
	cmp r0, #4
	blt _02233772
	ldr r0, [sp, #0x14]
	add r0, #0x98
	ldr r0, [r0]
	cmp r0, #0
	beq _0223380C
	bl ErrorHandling
_0223380C:
	mov r1, #0x32
	mov r0, #0x15
	lsl r1, r1, #6
	bl AllocFromHeap
	ldr r1, [sp, #0x14]
	mov r2, #0x32
	add r1, #0x98
	str r0, [r1]
	ldr r0, [sp, #0x14]
	lsl r2, r2, #6
	ldr r1, [r0, #0x60]
	add r0, #0xa0
	str r1, [r0]
	ldr r0, [sp, #0x14]
	ldr r1, [r0, #0x5c]
	add r0, #0x9c
	str r1, [r0]
	ldr r1, [sp, #0x14]
	mov r0, #0
	add r1, #0x98
	str r1, [sp, #0x14]
	ldr r1, [r1]
	bl MIi_CpuClear32
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02233844: .word 0xFFFFFE00

	thumb_func_start MOD12_02233848
MOD12_02233848: ; 0x02233848
	push {r3, r4, r5, r6, r7, lr}
	mov r6, #0
	str r0, [sp]
	add r4, r0, #0
	add r5, r0, #0
	add r7, r6, #0
_02233854:
	ldr r0, [r4, #8]
	bl FUN_02007534
	ldr r0, [r5, #0x58]
	bl FreeToHeap
	str r7, [r5, #0x58]
	add r6, r6, #1
	add r4, r4, #4
	add r5, #0x10
	cmp r6, #4
	blt _02233854
	ldr r0, [sp]
	add r0, #0x98
	ldr r0, [r0]
	bl FreeToHeap
	ldr r0, [sp]
	mov r1, #0
	add r0, #0x98
	str r0, [sp]
	str r1, [r0]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_02233884
MOD12_02233884: ; 0x02233884
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x58
	ldr r4, [sp, #0x70]
	str r0, [sp, #0x18]
	add r5, r1, #0
	add r7, r2, #0
	cmp r4, #0
	beq _0223389A
	cmp r4, #1
	beq _022338A8
	b _022338B6
_0223389A:
	mov r0, #0x20
	str r0, [sp, #0x20]
	mov r0, #0x1e
	mov r3, #0x1f
	mov r6, #1
	str r0, [sp, #0x1c]
	b _022338C2
_022338A8:
	mov r0, #0x26
	str r0, [sp, #0x20]
	mov r0, #0x24
	mov r3, #0x25
	mov r6, #3
	str r0, [sp, #0x1c]
	b _022338C2
_022338B6:
	mov r0, #0x23
	str r0, [sp, #0x20]
	mov r0, #0x21
	mov r3, #0x22
	mov r6, #2
	str r0, [sp, #0x1c]
_022338C2:
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0223396C ; =0x000080E9
	add r1, r7, #0
	add r0, r4, r0
	str r0, [sp, #8]
	add r0, r5, #0
	mov r2, #0x2e
	bl FUN_0200C00C
	mov r0, #0x2e
	str r0, [sp]
	str r6, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, _02233970 ; =0x000080EA
	mov r1, #2
	add r0, r4, r0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x18]
	add r2, r5, #0
	add r3, r7, #0
	bl FUN_0200C0DC
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223396C ; =0x000080E9
	ldr r3, [sp, #0x20]
	add r0, r4, r0
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #0x2e
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223396C ; =0x000080E9
	ldr r3, [sp, #0x1c]
	add r0, r4, r0
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #0x2e
	bl FUN_0200C13C
	ldr r6, _02233974 ; =MOD12_022453D8
	add r3, sp, #0x24
	mov r2, #6
_0223392C:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0223392C
	ldr r0, [r6]
	add r2, sp, #0x24
	str r0, [r3]
	ldr r0, _0223396C ; =0x000080E9
	add r1, r4, r0
	add r0, r0, #1
	add r0, r4, r0
	str r0, [sp, #0x3c]
	str r1, [sp, #0x38]
	str r1, [sp, #0x40]
	str r1, [sp, #0x44]
	lsl r1, r4, #5
	add r1, #0x60
	add r0, sp, #0x24
	strh r1, [r0]
	mov r1, #0x28
	strh r1, [r0, #2]
	add r0, r5, #0
	add r1, r7, #0
	bl FUN_0200C154
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_0200C59C
	add r0, r4, #0
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223396C: .word 0x000080E9
_02233970: .word 0x000080EA
_02233974: .word MOD12_022453D8

	thumb_func_start MOD12_02233978
MOD12_02233978: ; 0x02233978
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, r1, #0
	add r4, r2, #0
	bl FUN_0200C3DC
	ldr r1, _022339B0 ; =0x000080E9
	add r0, r5, #0
	add r1, r4, r1
	bl FUN_0200C358
	ldr r1, _022339B4 ; =0x000080EA
	add r0, r5, #0
	add r1, r4, r1
	bl FUN_0200C368
	ldr r1, _022339B0 ; =0x000080E9
	add r0, r5, #0
	add r1, r4, r1
	bl FUN_0200C378
	ldr r1, _022339B0 ; =0x000080E9
	add r0, r5, #0
	add r1, r4, r1
	bl FUN_0200C388
	pop {r3, r4, r5, pc}
	nop
_022339B0: .word 0x000080E9
_022339B4: .word 0x000080EA

	thumb_func_start MOD12_022339B8
MOD12_022339B8: ; 0x022339B8
	push {r4, r5, lr}
	sub sp, #0xc
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02233A04 ; =0x000080EC
	add r4, r2, #0
	add r5, r1, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x2e
	mov r3, #0x27
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _02233A04 ; =0x000080EC
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x28
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _02233A04 ; =0x000080EC
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x29
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_02233A04: .word 0x000080EC

	thumb_func_start MOD12_02233A08
MOD12_02233A08: ; 0x02233A08
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	ldr r4, _02233A5C ; =MOD12_0224520C
	add r6, r2, #0
	add r3, r0, #0
	add r7, r1, #0
	ldmia r4!, {r0, r1}
	add r2, sp, #0
	stmia r2!, {r0, r1}
	ldr r0, [r4]
	ldr r5, _02233A60 ; =MOD12_0224533C
	str r0, [r2]
	add r4, sp, #0xc
	mov r2, #6
_02233A24:
	ldmia r5!, {r0, r1}
	stmia r4!, {r0, r1}
	sub r2, r2, #1
	bne _02233A24
	ldr r0, [r5]
	lsl r1, r6, #5
	str r0, [r4]
	add r1, #0x60
	add r0, sp, #0
	strh r1, [r0, #0xc]
	mov r1, #0x20
	strh r1, [r0, #0xe]
	lsl r1, r6, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	add r1, r7, #0
	str r0, [sp, #0x18]
	add r0, r3, #0
	add r2, sp, #0xc
	bl FUN_0200C154
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_0200C59C
	add r0, r4, #0
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02233A5C: .word MOD12_0224520C
_02233A60: .word MOD12_0224533C

	thumb_func_start MOD12_02233A64
MOD12_02233A64: ; 0x02233A64
	ldr r3, _02233A68 ; =FUN_0200C3DC
	bx r3
	.align 2, 0
_02233A68: .word FUN_0200C3DC

	thumb_func_start MOD12_02233A6C
MOD12_02233A6C: ; 0x02233A6C
	push {r4, lr}
	ldr r1, _02233A88 ; =0x000080EC
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _02233A88 ; =0x000080EC
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _02233A88 ; =0x000080EC
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_02233A88: .word 0x000080EC

	thumb_func_start MOD12_02233A8C
MOD12_02233A8C: ; 0x02233A8C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r6, r1, #0
	ldr r0, [r7, #0x50]
	ldr r1, [r7, #0x18]
	ldr r2, [r7, #0x1c]
	bl MOD12_022339B8
	mov r4, #0
	add r5, r7, #0
	add r6, #0xd0
_02233AA2:
	ldr r0, [r7, #0x18]
	ldr r1, [r7, #0x1c]
	add r2, r4, #0
	bl MOD12_02233A08
	add r1, r5, #0
	add r1, #0xb4
	str r0, [r1]
	str r4, [sp]
	ldr r0, [r7, #0x50]
	ldr r1, [r7, #0x18]
	ldr r2, [r7, #0x1c]
	add r3, r6, #0
	bl MOD12_02233884
	add r1, r5, #0
	add r1, #0xa8
	add r4, r4, #1
	str r0, [r1]
	add r5, r5, #4
	add r6, #8
	cmp r4, #3
	blt _02233AA2
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_02233AD4
MOD12_02233AD4: ; 0x02233AD4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_02233ADC:
	add r1, r5, #0
	add r1, #0xa8
	ldr r0, [r6, #0x1c]
	ldr r1, [r1]
	add r2, r4, #0
	bl MOD12_02233978
	add r0, r5, #0
	add r0, #0xb4
	ldr r0, [r0]
	bl MOD12_02233A64
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _02233ADC
	ldr r0, [r6, #0x1c]
	bl MOD12_02233A6C
	pop {r4, r5, r6, pc}

	thumb_func_start MOD12_02233B04
MOD12_02233B04: ; 0x02233B04
	push {r4, r5, lr}
	sub sp, #0xc
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02233B50 ; =0x000080F5
	add r4, r2, #0
	add r5, r1, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x2e
	mov r3, #0xe
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _02233B54 ; =0x000080F3
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0xd
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _02233B54 ; =0x000080F3
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0xc
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_02233B50: .word 0x000080F5
_02233B54: .word 0x000080F3

	thumb_func_start MOD12_02233B58
MOD12_02233B58: ; 0x02233B58
	push {r4, lr}
	ldr r1, _02233B74 ; =0x000080F5
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _02233B78 ; =0x000080F3
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _02233B78 ; =0x000080F3
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_02233B74: .word 0x000080F5
_02233B78: .word 0x000080F3

	thumb_func_start MOD12_02233B7C
MOD12_02233B7C: ; 0x02233B7C
	push {r4, r5, lr}
	sub sp, #0x34
	ldr r4, _02233BB8 ; =MOD12_022452D4
	add r5, r0, #0
	add r3, sp, #0
	mov r2, #6
_02233B88:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02233B88
	ldr r0, [r4]
	add r2, sp, #0
	str r0, [r3]
	ldr r0, [r5, #0x18]
	ldr r1, [r5, #0x1c]
	bl FUN_0200C154
	add r4, r0, #0
	mov r1, #0
	bl FUN_0200C644
	ldr r0, [r4]
	bl FUN_0200C59C
	mov r0, #0x5f
	lsl r0, r0, #2
	str r4, [r5, r0]
	add sp, #0x34
	pop {r4, r5, pc}
	nop
_02233BB8: .word MOD12_022452D4

	thumb_func_start MOD12_02233BBC
MOD12_02233BBC: ; 0x02233BBC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02233BCE
	bl ErrorHandling
_02233BCE:
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200C3DC
	mov r0, #0x5f
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_02233BE4
MOD12_02233BE4: ; 0x02233BE4
	push {r4, r5, r6, lr}
	add r4, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r6, r1, #0
	add r5, r2, #0
	cmp r0, #0
	bne _02233BFA
	bl ErrorHandling
_02233BFA:
	ldr r1, _02233C60 ; =MOD12_02245200
	lsl r2, r6, #2
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r3, _02233C64 ; =MOD12_02245200 + 2
	ldrsh r1, [r1, r2]
	ldrsh r2, [r3, r2]
	ldr r0, [r4, r0]
	bl FUN_0200C714
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r5, #0
	bl FUN_0200C5C0
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_0200C644
	cmp r5, #3
	bhi _02233C5C
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02233C36: ; jump table
	.short _02233C3E - _02233C36 - 2 ; case 0
	.short _02233C46 - _02233C36 - 2 ; case 1
	.short _02233C4E - _02233C36 - 2 ; case 2
	.short _02233C56 - _02233C36 - 2 ; case 3
_02233C3E:
	ldr r0, _02233C68 ; =0x000006E1
	bl FUN_020054C8
	pop {r4, r5, r6, pc}
_02233C46:
	ldr r0, _02233C6C ; =0x000006DF
	bl FUN_020054C8
	pop {r4, r5, r6, pc}
_02233C4E:
	ldr r0, _02233C70 ; =0x000005DD
	bl FUN_020054C8
	pop {r4, r5, r6, pc}
_02233C56:
	ldr r0, _02233C70 ; =0x000005DD
	bl FUN_020054C8
_02233C5C:
	pop {r4, r5, r6, pc}
	nop
_02233C60: .word MOD12_02245200
_02233C64: .word MOD12_02245200 + 2
_02233C68: .word 0x000006E1
_02233C6C: .word 0x000006DF
_02233C70: .word 0x000005DD

	thumb_func_start MOD12_02233C74
MOD12_02233C74: ; 0x02233C74
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02233C86
	bl ErrorHandling
_02233C86:
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200C644
	pop {r4, pc}

	thumb_func_start MOD12_02233C94
MOD12_02233C94: ; 0x02233C94
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	str r1, [sp]
	mov r0, #0x15
	mov r1, #0x28
	add r6, r2, #0
	add r7, r3, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x28
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0
	strb r0, [r7]
	str r7, [r4, #4]
	add r1, r4, #0
	add r2, r4, #0
	ldr r0, [sp]
	str r5, [r4]
	strb r0, [r4, #8]
	lsl r0, r0, #2
	add r0, r5, r0
	add r0, #0xb4
	ldr r0, [r0]
	add r1, #0xc
	add r2, #0xe
	bl FUN_0200C7A0
	cmp r6, #6
	bhi _02233CEE
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02233CE0: ; jump table
	.short _02233CEE - _02233CE0 - 2 ; case 0
	.short _02233D04 - _02233CE0 - 2 ; case 1
	.short _02233D10 - _02233CE0 - 2 ; case 2
	.short _02233D20 - _02233CE0 - 2 ; case 3
	.short _02233D30 - _02233CE0 - 2 ; case 4
	.short _02233D40 - _02233CE0 - 2 ; case 5
	.short _02233D50 - _02233CE0 - 2 ; case 6
_02233CEE:
	mov r0, #1
	strb r0, [r4, #0x18]
	ldr r0, _02233D64 ; =0xFFFFFE00
	ldr r2, _02233D68 ; =0x00009C40
	strh r0, [r4, #0x24]
	strh r0, [r4, #0x26]
	ldr r0, _02233D6C ; =MOD12_02233E48
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
_02233D04:
	ldr r0, _02233D70 ; =MOD12_02233D84
	ldr r2, _02233D68 ; =0x00009C40
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
_02233D10:
	ldr r0, _02233D74 ; =0xFFFFFD00
	ldr r2, _02233D68 ; =0x00009C40
	strh r0, [r4, #0x24]
	ldr r0, _02233D6C ; =MOD12_02233E48
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
_02233D20:
	ldr r0, _02233D78 ; =0xFFFFFC00
	ldr r2, _02233D68 ; =0x00009C40
	strh r0, [r4, #0x24]
	ldr r0, _02233D6C ; =MOD12_02233E48
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
_02233D30:
	ldr r0, _02233D7C ; =0xFFFFFB80
	ldr r2, _02233D68 ; =0x00009C40
	strh r0, [r4, #0x24]
	ldr r0, _02233D6C ; =MOD12_02233E48
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
_02233D40:
	ldr r0, _02233D80 ; =0xFFFFFD80
	ldr r2, _02233D68 ; =0x00009C40
	strh r0, [r4, #0x24]
	ldr r0, _02233D6C ; =MOD12_02233E48
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
_02233D50:
	mov r0, #0xff
	mvn r0, r0
	strh r0, [r4, #0x24]
	ldr r0, _02233D6C ; =MOD12_02233E48
	ldr r2, _02233D68 ; =0x00009C40
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02233D64: .word 0xFFFFFE00
_02233D68: .word 0x00009C40
_02233D6C: .word MOD12_02233E48
_02233D70: .word MOD12_02233D84
_02233D74: .word 0xFFFFFD00
_02233D78: .word 0xFFFFFC00
_02233D7C: .word 0xFFFFFB80
_02233D80: .word 0xFFFFFD80

	thumb_func_start MOD12_02233D84
MOD12_02233D84: ; 0x02233D84
	push {r4, lr}
	add r2, r1, #0
	add r4, r0, #0
	ldrb r0, [r2, #0xa]
	cmp r0, #0
	beq _02233D9A
	cmp r0, #1
	beq _02233DB0
	cmp r0, #2
	beq _02233DF0
	b _02233E0A
_02233D9A:
	mov r0, #0xc
	ldrsh r0, [r2, r0]
	lsl r0, r0, #8
	str r0, [r2, #0x10]
	mov r0, #0xe
	ldrsh r0, [r2, r0]
	lsl r0, r0, #8
	str r0, [r2, #0x14]
	ldrb r0, [r2, #0xa]
	add r0, r0, #1
	strb r0, [r2, #0xa]
_02233DB0:
	ldrb r0, [r2, #0x18]
	mov r1, #1
	tst r0, r1
	beq _02233DC4
	mov r0, #0xc
	ldrsh r0, [r2, r0]
	lsl r3, r0, #8
	lsl r0, r1, #9
	add r0, r3, r0
	b _02233DCE
_02233DC4:
	mov r0, #0xc
	ldrsh r0, [r2, r0]
	lsl r3, r0, #8
	lsl r0, r1, #9
	sub r0, r3, r0
_02233DCE:
	str r0, [r2, #0x10]
	ldrb r0, [r2, #0x18]
	add r0, r0, #1
	strb r0, [r2, #0x18]
	ldrb r0, [r2, #0x18]
	cmp r0, #4
	bls _02233E1E
	mov r0, #0xc
	ldrsh r0, [r2, r0]
	lsl r0, r0, #8
	str r0, [r2, #0x10]
	mov r0, #0
	strb r0, [r2, #0x18]
	ldrb r0, [r2, #0xa]
	add r0, r0, #1
	strb r0, [r2, #0xa]
	b _02233E1E
_02233DF0:
	mov r0, #9
	ldrsb r1, [r2, r0]
	add r1, r1, #1
	strb r1, [r2, #9]
	ldrsb r0, [r2, r0]
	cmp r0, #0xf
	ble _02233E1E
	mov r0, #0
	strb r0, [r2, #9]
	ldrb r0, [r2, #0xa]
	add r0, r0, #1
	strb r0, [r2, #0xa]
	b _02233E1E
_02233E0A:
	ldr r0, [r2, #4]
	mov r1, #1
	strb r1, [r0]
	add r0, r2, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
	pop {r4, pc}
_02233E1E:
	ldrb r0, [r2, #8]
	ldr r1, [r2]
	ldr r3, [r2, #0x10]
	lsl r0, r0, #2
	add r0, r1, r0
	asr r1, r3, #7
	lsr r1, r1, #0x18
	add r1, r3, r1
	ldr r3, [r2, #0x14]
	add r0, #0xb4
	asr r2, r3, #7
	lsr r2, r2, #0x18
	add r2, r3, r2
	lsl r1, r1, #8
	lsl r2, r2, #8
	ldr r0, [r0]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	pop {r4, pc}

	thumb_func_start MOD12_02233E48
MOD12_02233E48: ; 0x02233E48
	push {r4, lr}
	add r2, r1, #0
	add r4, r0, #0
	ldrb r0, [r2, #0xa]
	cmp r0, #0
	beq _02233E5A
	cmp r0, #1
	beq _02233E70
	b _02233ED8
_02233E5A:
	mov r0, #0xc
	ldrsh r0, [r2, r0]
	lsl r0, r0, #8
	str r0, [r2, #0x10]
	mov r0, #0xe
	ldrsh r0, [r2, r0]
	lsl r0, r0, #8
	str r0, [r2, #0x14]
	ldrb r0, [r2, #0xa]
	add r0, r0, #1
	strb r0, [r2, #0xa]
_02233E70:
	mov r0, #0x24
	ldrsh r1, [r2, r0]
	ldr r3, [r2, #0x14]
	add r1, r3, r1
	str r1, [r2, #0x14]
	ldrsh r0, [r2, r0]
	add r0, #0x80
	strh r0, [r2, #0x24]
	mov r0, #0xe
	ldrsh r0, [r2, r0]
	lsl r1, r0, #8
	ldr r0, [r2, #0x14]
	cmp r0, r1
	blt _02233EAE
	str r1, [r2, #0x14]
	ldrb r0, [r2, #0x18]
	cmp r0, #0
	beq _02233EA8
	mov r0, #0x26
	ldrsh r0, [r2, r0]
	strh r0, [r2, #0x24]
	ldrb r0, [r2, #0x18]
	sub r0, r0, #1
	strb r0, [r2, #0x18]
	ldrb r0, [r2, #0xa]
	sub r0, r0, #1
	strb r0, [r2, #0xa]
	b _02233EAE
_02233EA8:
	ldrb r0, [r2, #0xa]
	add r0, r0, #1
	strb r0, [r2, #0xa]
_02233EAE:
	ldrb r0, [r2, #8]
	ldr r1, [r2]
	ldr r3, [r2, #0x10]
	lsl r0, r0, #2
	add r0, r1, r0
	asr r1, r3, #7
	lsr r1, r1, #0x18
	add r1, r3, r1
	ldr r3, [r2, #0x14]
	add r0, #0xb4
	asr r2, r3, #7
	lsr r2, r2, #0x18
	add r2, r3, r2
	lsl r1, r1, #8
	lsl r2, r2, #8
	ldr r0, [r0]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	pop {r4, pc}
_02233ED8:
	ldr r0, [r2, #4]
	mov r1, #1
	strb r1, [r0]
	add r0, r2, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
	pop {r4, pc}

	thumb_func_start MOD12_02233EEC
MOD12_02233EEC: ; 0x02233EEC
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r0, #0xc0
	ldr r0, [r0]
	add r4, r1, #0
	cmp r0, #0
	beq _02233F00
	bl ErrorHandling
_02233F00:
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02233F70 ; =0x000080ED
	mov r2, #0x2e
	str r0, [sp, #8]
	ldr r0, [r5, #0x18]
	ldr r1, [r5, #0x1c]
	mov r3, #0x14
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _02233F70 ; =0x000080ED
	mov r2, #0x2e
	str r0, [sp, #4]
	ldr r0, [r5, #0x18]
	ldr r1, [r5, #0x1c]
	mov r3, #0x13
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _02233F70 ; =0x000080ED
	mov r2, #0x2e
	str r0, [sp, #4]
	ldr r0, [r5, #0x18]
	ldr r1, [r5, #0x1c]
	mov r3, #0x12
	bl FUN_0200C13C
	ldr r0, [r5, #0x18]
	ldr r1, [r5, #0x1c]
	ldr r2, _02233F74 ; =MOD12_02245370
	bl FUN_0200C154
	add r1, r5, #0
	add r1, #0xc0
	str r0, [r1]
	add r0, r5, #0
	add r0, #0xc0
	ldr r0, [r0]
	ldr r0, [r0]
	bl FUN_0200C59C
	lsl r1, r4, #5
	add r5, #0xc0
	add r1, #0x60
	lsl r1, r1, #0x10
	ldr r0, [r5]
	asr r1, r1, #0x10
	mov r2, #0x38
	bl FUN_0200C714
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02233F70: .word 0x000080ED
_02233F74: .word MOD12_02245370

	thumb_func_start MOD12_02233F78
MOD12_02233F78: ; 0x02233F78
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x1c]
	ldr r1, _02233FA8 ; =0x000080ED
	bl FUN_0200C358
	ldr r0, [r4, #0x1c]
	ldr r1, _02233FA8 ; =0x000080ED
	bl FUN_0200C378
	ldr r0, [r4, #0x1c]
	ldr r1, _02233FA8 ; =0x000080ED
	bl FUN_0200C388
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	bl FUN_0200C3DC
	mov r0, #0
	add r4, #0xc0
	str r0, [r4]
	pop {r4, pc}
	nop
_02233FA8: .word 0x000080ED

	thumb_func_start MOD12_02233FAC
MOD12_02233FAC: ; 0x02233FAC
	push {r4, r5, lr}
	sub sp, #0xc
	mov r2, #1
	str r2, [sp]
	str r2, [sp, #4]
	ldr r2, _02233FF4 ; =0x000080EE
	mov r3, #0x11
	str r2, [sp, #8]
	mov r2, #0x2e
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _02233FF4 ; =0x000080EE
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x10
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _02233FF4 ; =0x000080EE
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0xf
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_02233FF4: .word 0x000080EE

	thumb_func_start MOD12_02233FF8
MOD12_02233FF8: ; 0x02233FF8
	push {r4, lr}
	ldr r1, _02234014 ; =0x000080EE
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _02234014 ; =0x000080EE
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _02234014 ; =0x000080EE
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_02234014: .word 0x000080EE

	thumb_func_start MOD12_02234018
MOD12_02234018: ; 0x02234018
	push {r4, r5, r6, lr}
	mov r2, #0x18
	mov r4, #0
	mul r2, r1
	add r5, r0, r2
	add r6, r4, #0
_02234024:
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #0
	beq _02234038
	bl FUN_0200C3DC
	add r0, r5, #0
	add r0, #0xc4
	str r6, [r0]
_02234038:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _02234024
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD12_02234044
MOD12_02234044: ; 0x02234044
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_0223404A:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD12_02234018
	add r4, r4, #1
	cmp r4, #4
	blt _0223404A
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_0223405C
MOD12_0223405C: ; 0x0223405C
	push {r4, r5, r6, lr}
	add r5, r2, #0
	ldr r2, _02234084 ; =MOD12_022453A4
	add r4, r3, #0
	bl FUN_0200C154
	add r6, r0, #0
	ldr r0, [r6]
	bl FUN_0200C59C
	lsl r1, r5, #0x10
	lsl r2, r4, #0x10
	add r0, r6, #0
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	nop
_02234084: .word MOD12_022453A4

	thumb_func_start MOD12_02234088
MOD12_02234088: ; 0x02234088
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r0, [sp]
	add r7, r1, #0
	add r0, r3, #0
	mov r1, #0xa
	str r2, [sp, #4]
	bl _s32_div_f
	str r0, [sp, #8]
	cmp r0, #0x18
	ble _022340A4
	mov r0, #0x18
	str r0, [sp, #8]
_022340A4:
	mov r0, #0x18
	add r1, r7, #0
	mul r1, r0
	ldr r0, [sp]
	ldr r4, [sp, #8]
	mov r6, #0
	add r5, r0, r1
	b _022340CE
_022340B4:
	lsl r0, r4, #2
	add r0, r5, r0
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #0
	beq _022340CC
	bl FUN_0200C3DC
	lsl r0, r4, #2
	add r0, r5, r0
	add r0, #0xc4
	str r6, [r0]
_022340CC:
	add r4, r4, #1
_022340CE:
	cmp r4, #6
	blt _022340B4
	ldr r0, [sp, #8]
	add r1, r7, #0
	sub r4, r0, #1
	mov r0, #0x18
	mul r1, r0
	ldr r0, [sp]
	add r7, r0, r1
	ldr r0, [sp, #4]
	ldr r1, _02234190 ; =MOD12_02245228
	lsl r0, r0, #2
	str r0, [sp, #0xc]
	add r0, r1, r0
	str r0, [sp, #0x10]
	b _02234170
_022340EE:
	add r0, r4, #0
	mov r1, #6
	bl _s32_div_f
	add r5, r1, #0
	add r0, r4, #0
	mov r1, #6
	bl _s32_div_f
	str r0, [sp, #0x14]
	lsl r0, r5, #2
	add r0, r7, r0
	add r0, #0xc4
	ldr r0, [r0]
	cmp r0, #0
	bne _0223414C
	ldr r3, _02234190 ; =MOD12_02245228
	ldr r2, [sp, #0xc]
	ldr r0, [sp]
	ldrsh r3, [r3, r2]
	lsl r2, r5, #3
	ldr r1, [sp]
	add r2, r3, r2
	ldr r6, [sp, #0x10]
	mov r3, #2
	ldrsh r3, [r6, r3]
	ldr r0, [r0, #0x18]
	ldr r1, [r1, #0x1c]
	bl MOD12_0223405C
	lsl r2, r5, #2
	add r1, r7, r2
	add r1, #0xc4
	str r0, [r1]
	add r0, r7, r2
	add r0, #0xc4
	ldr r0, [r0]
	ldr r1, [sp, #0x14]
	bl FUN_0200C5C0
	lsl r0, r5, #2
	add r0, r7, r0
	add r0, #0xc4
	ldr r0, [r0]
	bl MOD12_0223419C
	b _0223416E
_0223414C:
	bl FUN_0200C5CC
	ldr r1, [sp, #0x14]
	cmp r0, r1
	bhs _0223416E
	lsl r0, r5, #2
	add r0, r7, r0
	add r0, #0xc4
	ldr r0, [r0]
	bl FUN_0200C5C0
	lsl r0, r5, #2
	add r0, r7, r0
	add r0, #0xc4
	ldr r0, [r0]
	bl MOD12_0223419C
_0223416E:
	sub r4, r4, #1
_02234170:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bgt _022340EE
	ldr r0, _02234194 ; =0x000006E1
	bl FUN_020054C8
	ldr r2, [sp, #8]
	ldr r0, _02234194 ; =0x000006E1
	sub r2, r2, #1
	ldr r1, _02234198 ; =0x0000FFFF
	lsl r2, r2, #6
	bl FUN_02004D34
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02234190: .word MOD12_02245228
_02234194: .word 0x000006E1
_02234198: .word 0x0000FFFF

	thumb_func_start MOD12_0223419C
MOD12_0223419C: ; 0x0223419C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x15
	mov r1, #0x10
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x10
	add r4, r0, #0
	bl MI_CpuFill8
	add r0, r5, #0
	mov r1, #0
	str r5, [r4]
	bl FUN_0200C644
	ldr r0, _022341C8 ; =MOD12_022341D0
	ldr r2, _022341CC ; =0x00009C40
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, pc}
	.align 2, 0
_022341C8: .word MOD12_022341D0
_022341CC: .word 0x00009C40

	thumb_func_start MOD12_022341D0
MOD12_022341D0: ; 0x022341D0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0xc]
	cmp r0, #0
	beq _022341E6
	cmp r0, #1
	beq _02234202
	cmp r0, #2
	beq _0223423C
	b _0223428A
_022341E6:
	ldr r0, [r4]
	mov r1, #2
	bl FUN_0200C840
	ldr r0, _022342A0 ; =0x3DCCCCCD
	mov r1, #1
	str r0, [r4, #4]
	str r0, [r4, #8]
	ldr r0, [r4]
	bl FUN_0200C644
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02234202:
	ldr r0, [r4, #4]
	ldr r1, _022342A4 ; =0x3E99999A
	bl _fadd
	str r0, [r4, #4]
	ldr r0, [r4, #8]
	ldr r1, _022342A4 ; =0x3E99999A
	bl _fadd
	str r0, [r4, #8]
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	bl FUN_0200C884
	ldr r0, [r4]
	mov r1, #0
	bl FUN_0200C8BC
	mov r1, #0xff
	ldr r0, [r4, #4]
	lsl r1, r1, #0x16
	bl _fgeq
	blo _0223429E
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223423C:
	ldr r0, [r4, #4]
	ldr r1, _022342A4 ; =0x3E99999A
	bl _fsub
	str r0, [r4, #4]
	ldr r0, [r4, #8]
	ldr r1, _022342A4 ; =0x3E99999A
	bl _fsub
	str r0, [r4, #8]
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	bl FUN_0200C884
	ldr r0, [r4]
	mov r1, #0
	bl FUN_0200C8BC
	mov r1, #0xfe
	ldr r0, [r4, #4]
	lsl r1, r1, #0x16
	bl _fleq
	bhi _0223429E
	mov r1, #0xfe
	lsl r1, r1, #0x16
	ldr r0, [r4]
	add r2, r1, #0
	bl FUN_0200C884
	ldr r0, [r4]
	mov r1, #0
	bl FUN_0200C898
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223428A:
	ldr r0, [r4]
	mov r1, #0
	bl FUN_0200C840
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_0223429E:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022342A0: .word 0x3DCCCCCD
_022342A4: .word 0x3E99999A

	thumb_func_start MOD12_022342A8
MOD12_022342A8: ; 0x022342A8
	push {r4, r5, lr}
	sub sp, #0xc
	mov r2, #1
	str r2, [sp]
	str r2, [sp, #4]
	ldr r2, _0223432C ; =0x000080F0
	mov r3, #0x1a
	str r2, [sp, #8]
	mov r2, #0x2e
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223432C ; =0x000080F0
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x19
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223432C ; =0x000080F0
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x18
	bl FUN_0200C13C
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02234330 ; =0x000080EF
	add r1, r4, #0
	str r0, [sp, #8]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x1d
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _02234330 ; =0x000080EF
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x1c
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _02234330 ; =0x000080EF
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x1b
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_0223432C: .word 0x000080F0
_02234330: .word 0x000080EF

	thumb_func_start MOD12_02234334
MOD12_02234334: ; 0x02234334
	push {r4, lr}
	ldr r1, _02234368 ; =0x000080F0
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _02234368 ; =0x000080F0
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _02234368 ; =0x000080F0
	add r0, r4, #0
	bl FUN_0200C388
	ldr r1, _0223436C ; =0x000080EF
	add r0, r4, #0
	bl FUN_0200C358
	ldr r1, _0223436C ; =0x000080EF
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _0223436C ; =0x000080EF
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_02234368: .word 0x000080F0
_0223436C: .word 0x000080EF

	thumb_func_start MOD12_02234370
MOD12_02234370: ; 0x02234370
	push {r3, r4, r5, r6, r7, lr}
	mov r2, #0x14
	mov r4, #0
	mul r2, r1
	mov r7, #0x49
	add r5, r0, r2
	add r6, r4, #0
	lsl r7, r7, #2
_02234380:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _02234390
	bl FUN_0200C3DC
	mov r0, #0x49
	lsl r0, r0, #2
	str r6, [r5, r0]
_02234390:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _02234380
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_0223439C
MOD12_0223439C: ; 0x0223439C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_022343A2:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD12_02234370
	add r4, r4, #1
	cmp r4, #3
	blt _022343A2
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_022343B4
MOD12_022343B4: ; 0x022343B4
	push {r4, r5, r6, lr}
	add r5, r2, #0
	ldr r2, _022343DC ; =MOD12_02245308
	add r4, r3, #0
	bl FUN_0200C154
	add r6, r0, #0
	ldr r0, [r6]
	bl FUN_0200C59C
	lsl r1, r5, #0x10
	lsl r2, r4, #0x10
	add r0, r6, #0
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	nop
_022343DC: .word MOD12_02245308

	thumb_func_start MOD12_022343E0
MOD12_022343E0: ; 0x022343E0
	push {r4, r5, r6, lr}
	add r5, r2, #0
	ldr r2, _02234408 ; =MOD12_02245238
	add r4, r3, #0
	bl FUN_0200C154
	add r6, r0, #0
	ldr r0, [r6]
	bl FUN_0200C59C
	lsl r1, r5, #0x10
	lsl r2, r4, #0x10
	add r0, r6, #0
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	nop
_02234408: .word MOD12_02245238

	thumb_func_start MOD12_0223440C
MOD12_0223440C: ; 0x0223440C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x2e
	ldrb r0, [r0]
	cmp r0, #5
	bls _0223441E
	b _022345AC
_0223441E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223442A: ; jump table
	.short _02234436 - _0223442A - 2 ; case 0
	.short _0223447C - _0223442A - 2 ; case 1
	.short _022344BC - _0223442A - 2 ; case 2
	.short _022344EC - _0223442A - 2 ; case 3
	.short _0223452A - _0223442A - 2 ; case 4
	.short _0223457C - _0223442A - 2 ; case 5
_02234436:
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_0200C840
	mov r0, #2
	ldr r1, [r4, #0x10]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [r4, #0x20]
	mov r0, #0x12
	ldr r1, [r4, #0x14]
	lsl r0, r0, #0xa
	add r0, r1, r0
	str r0, [r4, #0x24]
	ldr r1, [r4, #0x20]
	ldr r0, [r4, #0x10]
	sub r0, r1, r0
	mov r1, #0xa
	bl _s32_div_f
	strh r0, [r4, #0x28]
	ldr r1, [r4, #0x24]
	ldr r0, [r4, #0x14]
	sub r0, r1, r0
	mov r1, #0xa
	bl _s32_div_f
	strh r0, [r4, #0x2a]
	add r0, r4, #0
	add r0, #0x2e
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2e
	strb r1, [r0]
_0223447C:
	mov r1, #0x28
	ldrsh r0, [r4, r1]
	ldr r2, [r4, #0x10]
	add r0, r2, r0
	str r0, [r4, #0x10]
	mov r0, #0x2a
	ldrsh r0, [r4, r0]
	ldr r2, [r4, #0x14]
	add r0, r2, r0
	str r0, [r4, #0x14]
	ldrsh r2, [r4, r1]
	cmp r2, #0
	ble _0223449E
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x20]
	cmp r1, r0
	bge _022344AC
_0223449E:
	cmp r2, #0
	bge _022344AA
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x20]
	cmp r1, r0
	ble _022344AC
_022344AA:
	b _022345D0
_022344AC:
	add r0, r4, #0
	add r0, #0x2e
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2e
	strb r1, [r0]
	b _022345D0
_022344BC:
	add r0, r4, #0
	add r0, #0x2f
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2f
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x2f
	ldrb r0, [r0]
	cmp r0, #3
	bls _022345D0
	add r0, r4, #0
	mov r1, #0
	add r0, #0x2f
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x2e
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2e
	strb r1, [r0]
	b _022345D0
_022344EC:
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	lsl r0, r0, #8
	str r0, [r4, #0x20]
	add r0, r4, #0
	add r0, #0x2d
	ldrb r0, [r0]
	lsl r0, r0, #8
	str r0, [r4, #0x24]
	ldr r1, [r4, #0x20]
	ldr r0, [r4, #0x10]
	sub r0, r1, r0
	mov r1, #6
	bl _s32_div_f
	strh r0, [r4, #0x28]
	ldr r1, [r4, #0x24]
	ldr r0, [r4, #0x14]
	sub r0, r1, r0
	mov r1, #6
	bl _s32_div_f
	strh r0, [r4, #0x2a]
	add r0, r4, #0
	add r0, #0x2e
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2e
	strb r1, [r0]
_0223452A:
	mov r1, #0x28
	ldrsh r0, [r4, r1]
	ldr r2, [r4, #0x10]
	add r0, r2, r0
	str r0, [r4, #0x10]
	mov r0, #0x2a
	ldrsh r0, [r4, r0]
	ldr r2, [r4, #0x14]
	add r0, r2, r0
	str r0, [r4, #0x14]
	ldrsh r2, [r4, r1]
	cmp r2, #0
	ble _0223454C
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x20]
	cmp r1, r0
	bge _02234558
_0223454C:
	cmp r2, #0
	bge _022345D0
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x20]
	cmp r1, r0
	bgt _022345D0
_02234558:
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	lsl r0, r0, #8
	str r0, [r4, #0x10]
	add r0, r4, #0
	add r0, #0x2d
	ldrb r0, [r0]
	lsl r0, r0, #8
	str r0, [r4, #0x14]
	add r0, r4, #0
	add r0, #0x2e
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2e
	strb r1, [r0]
	b _022345D0
_0223457C:
	add r0, r4, #0
	add r0, #0x2f
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2f
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x2f
	ldrb r0, [r0]
	cmp r0, #2
	bls _022345D0
	add r0, r4, #0
	mov r1, #0
	add r0, #0x2f
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x2e
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2e
	strb r1, [r0]
	b _022345D0
_022345AC:
	ldr r0, [r4, #4]
	bl FUN_0200C3DC
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_0200C644
	mov r0, #0x6e
	lsl r0, r0, #4
	bl FUN_020054C8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
_022345D0:
	mov r1, #2
	ldr r0, [r4, #4]
	lsl r1, r1, #0xc
	bl FUN_0200C8BC
	ldr r2, [r4, #0x10]
	ldr r3, [r4, #0x14]
	asr r1, r2, #7
	lsr r1, r1, #0x18
	add r1, r2, r1
	asr r2, r3, #7
	lsr r2, r2, #0x18
	add r2, r3, r2
	lsl r1, r1, #8
	lsl r2, r2, #8
	ldr r0, [r4, #4]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_022345FC
MOD12_022345FC: ; 0x022345FC
	push {r4, r5, r6, lr}
	mov r2, #0x14
	mul r2, r1
	mov r6, #0x49
	mov r4, #0
	add r5, r0, r2
	lsl r6, r6, #2
_0223460A:
	ldr r0, [r5, r6]
	cmp r0, #0
	beq _0223461C
	bl FUN_0200C658
	cmp r0, #0
	bne _0223461C
	mov r0, #0
	pop {r4, r5, r6, pc}
_0223461C:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _0223460A
	mov r0, #1
	pop {r4, r5, r6, pc}

	thumb_func_start MOD12_02234628
MOD12_02234628: ; 0x02234628
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r4, r2, #0
	str r0, [sp, #0x1c]
	str r1, [sp]
	add r0, r4, #0
	mov r1, #0xa
	bl _s32_div_f
	str r0, [sp, #4]
	cmp r0, #5
	ble _02234644
	bl ErrorHandling
_02234644:
	ldr r0, [sp]
	mov r1, #0x14
	lsl r7, r0, #2
	ldr r0, _02234770 ; =MOD12_022451F4
	mov r5, #0
	add r0, r0, r7
	str r0, [sp, #0xc]
	ldr r0, [sp]
	mul r1, r0
	ldr r0, [sp, #0x1c]
	add r0, r0, r1
	str r0, [sp, #8]
	ldr r0, _02234774 ; =MOD12_02245200
	add r0, r0, r7
	str r0, [sp, #0x10]
	ldr r0, [sp]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x14]
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	b _02234738
_02234672:
	ldr r0, [sp, #8]
	lsl r2, r5, #2
	add r1, r0, r2
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02234736
	ldr r3, _02234770 ; =MOD12_022451F4
	ldr r0, [sp, #0x1c]
	ldrsh r3, [r3, r7]
	add r2, r5, r2
	ldr r4, [sp, #0xc]
	ldr r1, [sp, #0x1c]
	add r2, r3, r2
	mov r3, #2
	ldrsh r3, [r4, r3]
	ldr r0, [r0, #0x18]
	ldr r1, [r1, #0x1c]
	bl MOD12_022343B4
	ldr r1, [sp, #8]
	lsl r2, r5, #2
	add r2, r1, r2
	mov r1, #0x49
	lsl r1, r1, #2
	str r0, [r2, r1]
	add r0, r1, #0
	ldr r0, [r2, r0]
	mov r1, #0
	bl FUN_0200C644
	mov r0, #0x15
	mov r1, #0x34
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x34
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp, #0x1c]
	lsl r1, r5, #2
	str r0, [r4]
	ldr r0, [sp, #8]
	ldr r2, _02234774 ; =MOD12_02245200
	add r1, r0, r1
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r6, [sp, #0x10]
	str r0, [r4, #8]
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x1c]
	mov r3, #2
	ldrsh r2, [r2, r7]
	ldrsh r3, [r6, r3]
	ldr r0, [r0, #0x18]
	ldr r1, [r1, #0x1c]
	bl MOD12_022343E0
	str r0, [r4, #4]
	ldr r0, _02234774 ; =MOD12_02245200
	ldr r1, [sp, #0x10]
	ldrsh r0, [r0, r7]
	ldr r2, _02234778 ; =0x00009C40
	lsl r0, r0, #8
	str r0, [r4, #0x10]
	mov r0, #2
	ldrsh r0, [r1, r0]
	lsl r0, r0, #8
	str r0, [r4, #0x14]
	ldr r0, _02234770 ; =MOD12_022451F4
	ldrsh r1, [r0, r7]
	lsl r0, r5, #2
	add r0, r5, r0
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0x2c
	strb r1, [r0]
	ldr r1, [sp, #0xc]
	mov r0, #2
	ldrsh r1, [r1, r0]
	add r0, r4, #0
	add r0, #0x2d
	strb r1, [r0]
	add r1, r4, #0
	ldr r0, [sp, #0x14]
	add r1, #0x30
	strb r0, [r1]
	add r1, r4, #0
	ldr r0, [sp, #0x18]
	add r1, #0x31
	strb r0, [r1]
	ldr r0, _0223477C ; =MOD12_0223440C
	add r1, r4, #0
	bl FUN_0200CA44
_02234736:
	add r5, r5, #1
_02234738:
	ldr r0, [sp, #4]
	cmp r5, r0
	blt _02234672
	ldr r0, [sp]
	mov r1, #0x14
	mul r1, r0
	ldr r0, [sp, #0x1c]
	mov r7, #0x49
	lsl r7, r7, #2
	add r4, r0, r1
	add r6, r7, #0
	b _02234768
_02234750:
	lsl r0, r5, #2
	add r0, r4, r0
	ldr r0, [r0, r6]
	cmp r0, #0
	beq _02234766
	bl FUN_0200C3DC
	lsl r0, r5, #2
	add r1, r4, r0
	mov r0, #0
	str r0, [r1, r7]
_02234766:
	add r5, r5, #1
_02234768:
	cmp r5, #5
	blt _02234750
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02234770: .word MOD12_022451F4
_02234774: .word MOD12_02245200
_02234778: .word 0x00009C40
_0223477C: .word MOD12_0223440C

	thumb_func_start MOD12_02234780
MOD12_02234780: ; 0x02234780
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r1, #0
	str r0, [sp]
	cmp r2, #1
	bne _02234790
	mov r6, #1
	b _02234792
_02234790:
	mov r6, #0
_02234792:
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp]
	str r0, [sp, #8]
	str r0, [sp, #4]
_0223479C:
	ldr r5, [sp]
	mov r4, #0
_022347A0:
	add r0, r5, #0
	add r0, #0xd0
	ldr r0, [r0]
	cmp r0, #0
	beq _022347BC
	add r1, r7, #0
	bl FUN_0200C90C
	add r0, r5, #0
	add r0, #0xd0
	ldr r0, [r0]
	add r1, r6, #0
	bl FUN_0200C644
_022347BC:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _022347A0
	mov r1, #0x5b
	ldr r0, [sp, #8]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	cmp r0, #0
	beq _022347E4
	add r1, r7, #0
	bl FUN_0200C90C
	mov r1, #0x5b
	ldr r0, [sp, #8]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	add r1, r6, #0
	bl FUN_0200C644
_022347E4:
	mov r1, #0x63
	ldr r0, [sp, #4]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	add r1, r7, #0
	bl FUN_02011AF0
	mov r1, #0x77
	ldr r0, [sp, #4]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	add r1, r7, #0
	bl FUN_02011AF0
	mov r1, #0x63
	ldr r0, [sp, #4]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	add r1, r6, #0
	bl FUN_020119D0
	mov r1, #0x77
	ldr r0, [sp, #4]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	add r1, r6, #0
	bl FUN_020119D0
	ldr r0, [sp]
	add r0, #0x18
	str r0, [sp]
	ldr r0, [sp, #8]
	add r0, r0, #4
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	add r0, #0x14
	str r0, [sp, #4]
	ldr r0, [sp, #0xc]
	add r0, r0, #1
	str r0, [sp, #0xc]
	cmp r0, #4
	blt _0223479C
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD12_0223483C
MOD12_0223483C: ; 0x0223483C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	mov r0, #0
	strb r0, [r7]
	mov r0, #0x15
	mov r1, #0x10
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x10
	bl MI_CpuFill8
	str r5, [r4]
	mov r2, #0xfa
	strb r6, [r4, #0xd]
	ldr r0, _02234870 ; =MOD12_02234874
	add r1, r4, #0
	lsl r2, r2, #2
	str r7, [r4, #4]
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02234870: .word MOD12_02234874

	thumb_func_start MOD12_02234874
MOD12_02234874: ; 0x02234874
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0xc]
	cmp r0, #3
	bls _02234882
	b _022349B8
_02234882:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223488E: ; jump table
	.short _02234896 - _0223488E - 2 ; case 0
	.short _022348F2 - _0223488E - 2 ; case 1
	.short _02234926 - _0223488E - 2 ; case 2
	.short _0223497A - _0223488E - 2 ; case 3
_02234896:
	ldrb r0, [r4, #0xd]
	cmp r0, #0
	bne _022348BE
	mov r0, #1
	lsl r0, r0, #0xc
	strh r0, [r4, #8]
	mov r1, #0
	strh r1, [r4, #0xa]
	ldr r0, _022349D0 ; =0x04000050
	str r1, [sp]
	mov r2, #0xe
	mov r3, #0x10
	bl G2x_SetBlendAlpha_
	mov r1, #1
	ldr r0, [r4]
	add r2, r1, #0
	bl MOD12_02234780
	b _022348E0
_022348BE:
	mov r3, #0
	mov r0, #1
	strh r3, [r4, #8]
	lsl r0, r0, #0xc
	strh r0, [r4, #0xa]
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _022349D0 ; =0x04000050
	mov r1, #4
	mov r2, #0xe
	bl G2x_SetBlendAlpha_
	ldr r0, [r4]
	mov r1, #0
	mov r2, #1
	bl MOD12_0222DF30
_022348E0:
	ldr r0, _022349D4 ; =MOD12_022349D8
	add r1, r4, #0
	mov r2, #0xa
	bl FUN_0200CA98
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_022348F2:
	ldrb r1, [r4, #0xd]
	cmp r1, #0
	bne _02234912
	mov r0, #8
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bne _02234912
	mov r1, #0
	ldr r0, [r4]
	add r2, r1, #0
	bl MOD12_02234780
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02234912:
	cmp r1, #1
	bne _022349CE
	mov r0, #0xa
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bne _022349CE
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02234926:
	ldrb r0, [r4, #0xd]
	cmp r0, #0
	bne _02234946
	mov r0, #1
	lsl r0, r0, #0xc
	strh r0, [r4, #8]
	mov r0, #0
	strh r0, [r4, #0xa]
	str r0, [sp]
	ldr r0, _022349D0 ; =0x04000050
	mov r1, #4
	mov r2, #0xe
	mov r3, #0x10
	bl G2x_SetBlendAlpha_
	b _02234968
_02234946:
	mov r1, #0
	mov r0, #1
	strh r1, [r4, #8]
	lsl r0, r0, #0xc
	strh r0, [r4, #0xa]
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _022349D0 ; =0x04000050
	mov r2, #0xe
	add r3, r1, #0
	bl G2x_SetBlendAlpha_
	mov r1, #1
	ldr r0, [r4]
	add r2, r1, #0
	bl MOD12_02234780
_02234968:
	ldr r0, _022349D4 ; =MOD12_022349D8
	add r1, r4, #0
	mov r2, #0xa
	bl FUN_0200CA98
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223497A:
	ldrb r1, [r4, #0xd]
	cmp r1, #0
	bne _0223499A
	mov r0, #8
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bne _0223499A
	mov r1, #1
	ldr r0, [r4]
	add r2, r1, #0
	bl MOD12_0222DF30
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223499A:
	cmp r1, #1
	bne _022349CE
	mov r0, #0xa
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bne _022349CE
	ldr r0, [r4]
	mov r1, #0
	mov r2, #1
	bl MOD12_02234780
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_022349B8:
	bl MOD12_02233560
	ldr r0, [r4, #4]
	mov r1, #1
	strb r1, [r0]
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_022349CE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022349D0: .word 0x04000050
_022349D4: .word MOD12_022349D8

	thumb_func_start MOD12_022349D8
MOD12_022349D8: ; 0x022349D8
	push {r3, r4, r5, lr}
	ldrb r3, [r1, #0xd]
	mov r2, #0
	cmp r3, #0
	bne _02234A10
	mov r4, #8
	ldrsh r5, [r1, r4]
	lsl r3, r4, #8
	sub r3, r5, r3
	strh r3, [r1, #8]
	mov r3, #0xa
	ldrsh r5, [r1, r3]
	lsl r3, r4, #8
	add r3, r5, r3
	strh r3, [r1, #0xa]
	ldrsh r3, [r1, r4]
	cmp r3, #0
	bgt _02234A00
	strh r2, [r1, #8]
	add r2, r2, #1
_02234A00:
	mov r3, #0xa
	ldrsh r4, [r1, r3]
	mov r3, #1
	lsl r3, r3, #0xc
	cmp r4, r3
	blt _02234A3C
	strh r3, [r1, #0xa]
	b _02234A3C
_02234A10:
	mov r4, #8
	ldrsh r5, [r1, r4]
	lsl r3, r4, #8
	add r3, r5, r3
	strh r3, [r1, #8]
	mov r3, #0xa
	ldrsh r5, [r1, r3]
	lsl r3, r4, #8
	sub r3, r5, r3
	strh r3, [r1, #0xa]
	ldrsh r5, [r1, r4]
	lsl r3, r4, #9
	cmp r5, r3
	blt _02234A30
	strh r3, [r1, #8]
	add r2, r2, #1
_02234A30:
	mov r3, #0xa
	ldrsh r3, [r1, r3]
	cmp r3, #0
	bgt _02234A3C
	mov r3, #0
	strh r3, [r1, #0xa]
_02234A3C:
	mov r3, #8
	ldrsh r3, [r1, r3]
	asr r4, r3, #8
	mov r3, #0xa
	ldrsh r3, [r1, r3]
	mov r1, #0xff
	bic r3, r1
	orr r3, r4
	ldr r1, _02234A5C ; =0x04000052
	cmp r2, #0
	strh r3, [r1]
	ble _02234A58
	bl FUN_0200CAB4
_02234A58:
	pop {r3, r4, r5, pc}
	nop
_02234A5C: .word 0x04000052

	thumb_func_start MOD12_02234A60
MOD12_02234A60: ; 0x02234A60
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r1, #0
	add r4, r0, #0
	add r5, r2, #0
	add r6, r3, #0
	cmp r7, #2
	blt _02234A78
	cmp r5, #0
	bne _02234A78
	bl ErrorHandling
_02234A78:
	cmp r7, #0x1c
	bls _02234A7E
	b _02234EF2
_02234A7E:
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02234A8A: ; jump table
	.short _02234EF6 - _02234A8A - 2 ; case 0
	.short _02234AC4 - _02234A8A - 2 ; case 1
	.short _02234AE2 - _02234A8A - 2 ; case 2
	.short _02234AFC - _02234A8A - 2 ; case 3
	.short _02234B16 - _02234A8A - 2 ; case 4
	.short _02234B24 - _02234A8A - 2 ; case 5
	.short _02234B38 - _02234A8A - 2 ; case 6
	.short _02234B50 - _02234A8A - 2 ; case 7
	.short _02234B80 - _02234A8A - 2 ; case 8
	.short _02234BA4 - _02234A8A - 2 ; case 9
	.short _02234BD0 - _02234A8A - 2 ; case 10
	.short _02234BFE - _02234A8A - 2 ; case 11
	.short _02234C2E - _02234A8A - 2 ; case 12
	.short _02234C52 - _02234A8A - 2 ; case 13
	.short _02234C7E - _02234A8A - 2 ; case 14
	.short _02234CAE - _02234A8A - 2 ; case 15
	.short _02234CD2 - _02234A8A - 2 ; case 16
	.short _02234CF6 - _02234A8A - 2 ; case 17
	.short _02234D16 - _02234A8A - 2 ; case 18
	.short _02234D3A - _02234A8A - 2 ; case 19
	.short _02234D64 - _02234A8A - 2 ; case 20
	.short _02234D8E - _02234A8A - 2 ; case 21
	.short _02234DAC - _02234A8A - 2 ; case 22
	.short _02234DD6 - _02234A8A - 2 ; case 23
	.short _02234E04 - _02234A8A - 2 ; case 24
	.short _02234E32 - _02234A8A - 2 ; case 25
	.short _02234E54 - _02234A8A - 2 ; case 26
	.short _02234E7E - _02234A8A - 2 ; case 27
	.short _02234EB6 - _02234A8A - 2 ; case 28
_02234AC4:
	mov r0, #0xca
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferBoxMonNickname
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234AE2:
	ldrb r0, [r5]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferBoxMonNickname
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234AFC:
	ldrb r0, [r5, #1]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferBoxMonNickname
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234B16:
	ldrh r2, [r5, #2]
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferMoveName
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234B24:
	mov r1, #0
	str r1, [sp]
	mov r3, #1
	str r3, [sp, #4]
	ldrb r2, [r5, #4]
	ldr r0, [r4, #0x54]
	bl BufferIntegerAsString
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234B38:
	ldrb r2, [r5, #5]
	ldr r3, [r4, #0xc]
	ldr r0, [r4, #0x54]
	lsl r2, r2, #3
	add r2, r3, r2
	add r2, #0xd0
	ldrh r2, [r2]
	mov r1, #0
	bl BufferContestJudgeName
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234B50:
	ldrb r0, [r5]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferBoxMonNickname
	ldrb r0, [r5, #1]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #1
	bl BufferBoxMonNickname
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234B80:
	ldrb r0, [r5]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferBoxMonNickname
	ldrh r2, [r5, #2]
	ldr r0, [r4, #0x54]
	mov r1, #1
	bl BufferMoveName
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234BA4:
	ldrb r0, [r5]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferBoxMonNickname
	mov r0, #0
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	ldrb r2, [r5, #4]
	ldr r0, [r4, #0x54]
	add r3, r1, #0
	bl BufferIntegerAsString
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234BD0:
	ldrb r0, [r5]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferBoxMonNickname
	ldrb r2, [r5, #5]
	ldr r3, [r4, #0xc]
	ldr r0, [r4, #0x54]
	lsl r2, r2, #3
	add r2, r3, r2
	add r2, #0xd0
	ldrh r2, [r2]
	mov r1, #1
	bl BufferContestJudgeName
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234BFE:
	ldrb r0, [r5, #1]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferBoxMonNickname
	ldrb r0, [r5]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #1
	bl BufferBoxMonNickname
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234C2E:
	ldrb r0, [r5, #1]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferBoxMonNickname
	ldrh r2, [r5, #2]
	ldr r0, [r4, #0x54]
	mov r1, #1
	bl BufferMoveName
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234C52:
	ldrb r0, [r5, #1]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferBoxMonNickname
	mov r0, #0
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	ldrb r2, [r5, #4]
	ldr r0, [r4, #0x54]
	add r3, r1, #0
	bl BufferIntegerAsString
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234C7E:
	ldrb r0, [r5, #1]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferBoxMonNickname
	ldrb r0, [r5]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #1
	bl BufferBoxMonNickname
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234CAE:
	ldrh r2, [r5, #2]
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferMoveName
	ldrb r0, [r5]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #1
	bl BufferBoxMonNickname
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234CD2:
	ldrh r2, [r5, #2]
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferMoveName
	ldrb r0, [r5, #1]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #1
	bl BufferBoxMonNickname
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234CF6:
	ldrh r2, [r5, #2]
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferMoveName
	mov r0, #0
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	ldrb r2, [r5, #4]
	ldr r0, [r4, #0x54]
	add r3, r1, #0
	bl BufferIntegerAsString
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234D16:
	ldrh r2, [r5, #2]
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferMoveName
	ldrb r0, [r5]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #1
	bl BufferBoxMonNickname
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234D3A:
	mov r1, #0
	str r1, [sp]
	mov r3, #1
	str r3, [sp, #4]
	ldrb r2, [r5, #4]
	ldr r0, [r4, #0x54]
	bl BufferIntegerAsString
	ldrb r0, [r5]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #1
	bl BufferBoxMonNickname
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234D64:
	mov r1, #0
	str r1, [sp]
	mov r3, #1
	str r3, [sp, #4]
	ldrb r2, [r5, #4]
	ldr r0, [r4, #0x54]
	bl BufferIntegerAsString
	ldrb r0, [r5, #1]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #1
	bl BufferBoxMonNickname
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234D8E:
	mov r1, #0
	str r1, [sp]
	mov r3, #1
	str r3, [sp, #4]
	ldrb r2, [r5, #4]
	ldr r0, [r4, #0x54]
	bl BufferIntegerAsString
	ldrh r2, [r5, #2]
	ldr r0, [r4, #0x54]
	mov r1, #1
	bl BufferMoveName
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234DAC:
	mov r1, #0
	str r1, [sp]
	mov r3, #1
	str r3, [sp, #4]
	ldrb r2, [r5, #4]
	ldr r0, [r4, #0x54]
	bl BufferIntegerAsString
	ldrb r0, [r5]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #1
	bl BufferBoxMonNickname
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234DD6:
	ldrb r2, [r5, #5]
	ldr r3, [r4, #0xc]
	ldr r0, [r4, #0x54]
	lsl r2, r2, #3
	add r2, r3, r2
	add r2, #0xd0
	ldrh r2, [r2]
	mov r1, #0
	bl BufferContestJudgeName
	ldrb r0, [r5]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #1
	bl BufferBoxMonNickname
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234E04:
	ldrb r2, [r5, #5]
	ldr r3, [r4, #0xc]
	ldr r0, [r4, #0x54]
	lsl r2, r2, #3
	add r2, r3, r2
	add r2, #0xd0
	ldrh r2, [r2]
	mov r1, #0
	bl BufferContestJudgeName
	ldrb r0, [r5, #1]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #1
	bl BufferBoxMonNickname
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234E32:
	ldrb r2, [r5, #5]
	ldr r3, [r4, #0xc]
	ldr r0, [r4, #0x54]
	lsl r2, r2, #3
	add r2, r3, r2
	add r2, #0xd0
	ldrh r2, [r2]
	mov r1, #0
	bl BufferContestJudgeName
	ldrh r2, [r5, #2]
	ldr r0, [r4, #0x54]
	mov r1, #1
	bl BufferMoveName
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234E54:
	ldrb r2, [r5, #5]
	ldr r3, [r4, #0xc]
	ldr r0, [r4, #0x54]
	lsl r2, r2, #3
	add r2, r3, r2
	add r2, #0xd0
	ldrh r2, [r2]
	mov r1, #0
	bl BufferContestJudgeName
	mov r0, #0
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	ldrb r2, [r5, #4]
	ldr r0, [r4, #0x54]
	add r3, r1, #0
	bl BufferIntegerAsString
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234E7E:
	ldrb r0, [r5]
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl BufferBoxMonNickname
	ldrb r2, [r5, #5]
	ldr r3, [r4, #0xc]
	ldr r0, [r4, #0x54]
	lsl r2, r2, #3
	add r2, r3, r2
	add r2, #0xd0
	ldrh r2, [r2]
	mov r1, #1
	bl BufferContestJudgeName
	ldrh r2, [r5, #2]
	ldr r0, [r4, #0x54]
	mov r1, #2
	bl BufferMoveName
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234EB6:
	ldrb r2, [r6]
	ldr r3, [r4, #0xc]
	ldr r0, [r4, #0x54]
	lsl r2, r2, #3
	add r2, r3, r2
	add r2, #0xd0
	ldrh r2, [r2]
	mov r1, #0
	bl BufferContestJudgeName
	mov r5, #0
_02234ECC:
	add r0, r6, r5
	ldrb r0, [r0, #1]
	cmp r0, #4
	beq _02234EF6
	ldr r1, [r4, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r4, #0x54]
	add r1, r5, #1
	bl BufferBoxMonNickname
	add r5, r5, #1
	cmp r5, #4
	blt _02234ECC
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02234EF2:
	bl ErrorHandling
_02234EF6:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_02234EFC
MOD12_02234EFC: ; 0x02234EFC
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x34
	mov r1, #0xff
	bl FillWindowPixelBuffer
	add r4, #0x34
	add r0, r4, #0
	bl CopyWindowToVram
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_02234F14
MOD12_02234F14: ; 0x02234F14
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [sp, #0x30]
	add r6, r1, #0
	add r7, r2, #0
	str r3, [sp, #0xc]
	cmp r0, #1
	bne _02234F2A
	mov r4, #0
	b _02234F42
_02234F2A:
	ldr r1, [r5]
	ldr r0, _02234FA8 ; =0x00000171
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _02234F40
	ldr r0, _02234FAC ; =0x00001988
	ldr r0, [r1, r0]
	bl Options_GetTextFrameDelay
	add r4, r0, #0
	b _02234F42
_02234F40:
	mov r4, #1
_02234F42:
	add r0, r6, #0
	add r1, r7, #0
	bl NewString_ReadMsgData
	add r6, r0, #0
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x2c]
	add r0, r5, #0
	bl MOD12_02234A60
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	add r0, #0x34
	mov r1, #0xff
	bl FillWindowPixelBuffer
	mov r3, #0
	str r3, [sp]
	str r4, [sp, #4]
	str r3, [sp, #8]
	add r0, r5, #0
	ldr r2, [r5, #0x58]
	add r0, #0x34
	mov r1, #1
	bl AddTextPrinterParameterized
	mov r1, #0x8b
	lsl r1, r1, #2
	strb r0, [r5, r1]
	cmp r4, #0
	bne _02234F96
	mov r0, #0xff
	strb r0, [r5, r1]
	add r0, r5, #0
	add r0, #0x34
	bl CopyWindowToVram
_02234F96:
	ldr r0, [r5, #0x30]
	mov r1, #1
	bl FUN_02017B48
	add r0, r6, #0
	bl String_dtor
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02234FA8: .word 0x00000171
_02234FAC: .word 0x00001988

	thumb_func_start MOD12_02234FB0
MOD12_02234FB0: ; 0x02234FB0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r7, r0, #0
	add r4, r2, #0
	add r6, r3, #0
	cmp r5, #0x2f
	blo _02234FC4
	bl ErrorHandling
_02234FC4:
	ldr r0, _02234FE4 ; =MOD12_0224540C + 3
	lsl r3, r5, #2
	ldrb r0, [r0, r3]
	str r4, [sp]
	ldr r2, _02234FE8 ; =MOD12_0224540C
	str r6, [sp, #4]
	str r0, [sp, #8]
	ldr r4, _02234FEC ; =MOD12_0224540C+ 2
	ldrh r2, [r2, r3]
	ldrb r3, [r4, r3]
	ldr r1, [r7, #0x44]
	add r0, r7, #0
	bl MOD12_02234F14
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02234FE4: .word MOD12_0224540C + 3
_02234FE8: .word MOD12_0224540C
_02234FEC: .word MOD12_0224540C + 2

	thumb_func_start MOD12_02234FF0
MOD12_02234FF0: ; 0x02234FF0
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r0, #0
	add r5, r3, #0
	add r0, r1, #0
	add r1, r2, #0
	add r2, sp, #0x10
	add r3, sp, #0xc
	bl FUN_02083170
	ldr r0, [sp, #0x20]
	str r5, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r1, [r4, #0x50]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	add r0, r4, #0
	bl MOD12_02234F14
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_02235020
MOD12_02235020: ; 0x02235020
	push {r3, lr}
	mov r1, #0x8b
	lsl r1, r1, #2
	ldrb r0, [r0, r1]
	cmp r0, #0xff
	bne _02235030
	mov r0, #0
	pop {r3, pc}
_02235030:
	bl FUN_0201BD70
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02235038
MOD12_02235038: ; 0x02235038
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0xc
	mov r1, #0x15
	bl String_ctor
	str r0, [sp, #0x30]
	lsl r0, r4, #2
	ldr r1, [r5, #0xc]
	str r0, [sp, #0x2c]
	ldr r0, [r1, r0]
	ldr r2, [sp, #0x30]
	mov r1, #0x76
	bl GetMonData
	ldr r1, [r5]
	ldr r0, _022350E8 ; =0x00000123
	ldrb r0, [r1, r0]
	cmp r4, r0
	bne _02235068
	ldr r6, _022350EC ; =0x00010200
	b _0223506A
_02235068:
	ldr r6, _022350F0 ; =0x00050600
_0223506A:
	mov r0, #0x14
	add r7, r4, #0
	mul r7, r0
	mov r0, #0x77
	lsl r0, r0, #2
	add r0, r5, r0
	add r0, r0, r7
	str r0, [sp]
	ldr r0, [sp, #0x30]
	mov r1, #0
	str r0, [sp, #4]
	str r1, [sp, #8]
	str r6, [sp, #0xc]
	ldr r0, _022350F4 ; =0x000080ED
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	str r1, [sp, #0x18]
	str r1, [sp, #0x1c]
	str r1, [sp, #0x20]
	str r1, [sp, #0x24]
	mov r0, #0xf
	str r0, [sp, #0x28]
	ldr r1, [r5, #0x30]
	ldr r2, [r5, #0x28]
	ldr r3, [r5, #0x60]
	mov r0, #0x15
	bl MOD12_02231380
	mov r0, #0x63
	lsl r0, r0, #2
	add r0, r5, r0
	add r0, r0, r7
	str r0, [sp]
	ldr r1, [r5]
	ldr r0, [sp, #0x2c]
	add r0, r1, r0
	add r0, #0xe8
	ldr r0, [r0]
	mov r1, #0
	str r0, [sp, #4]
	str r1, [sp, #8]
	str r6, [sp, #0xc]
	ldr r0, _022350F4 ; =0x000080ED
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	str r1, [sp, #0x18]
	str r1, [sp, #0x1c]
	str r1, [sp, #0x20]
	str r1, [sp, #0x24]
	mov r0, #0xf
	str r0, [sp, #0x28]
	ldr r1, [r5, #0x30]
	ldr r2, [r5, #0x28]
	ldr r3, [r5, #0x60]
	mov r0, #0x15
	bl MOD12_02231380
	ldr r0, [sp, #0x30]
	bl String_dtor
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	nop
_022350E8: .word 0x00000123
_022350EC: .word 0x00010200
_022350F0: .word 0x00050600
_022350F4: .word 0x000080ED

	thumb_func_start MOD12_022350F8
MOD12_022350F8: ; 0x022350F8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_022350FE:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD12_02235038
	add r4, r4, #1
	cmp r4, #4
	blt _022350FE
	add r0, r5, #0
	bl MOD12_0223513C
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_02235114
MOD12_02235114: ; 0x02235114
	push {r4, r5, r6, lr}
	mov r1, #0x77
	lsl r1, r1, #2
	add r4, r0, r1
	sub r1, #0x50
	mov r6, #0
	add r5, r0, r1
_02235122:
	add r0, r4, #0
	bl MOD12_0223147C
	add r0, r5, #0
	bl MOD12_0223147C
	add r6, r6, #1
	add r4, #0x14
	add r5, #0x14
	cmp r6, #4
	blt _02235122
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD12_0223513C
MOD12_0223513C: ; 0x0223513C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	mov r1, #0x77
	lsl r1, r1, #2
	str r0, [sp]
	add r0, r0, r1
	str r0, [sp, #4]
	ldr r0, [sp]
	sub r1, #0x50
	add r0, r0, r1
	mov r4, #0
	mov r6, #0xc
	mov r5, #0x1c
	str r0, [sp, #8]
_02235158:
	ldr r0, [sp]
	add r2, r6, #0
	add r1, r0, r4
	ldr r0, _02235190 ; =0x00000231
	mov r3, #0
	ldrb r1, [r1, r0]
	mov r0, #0x14
	add r7, r1, #0
	mul r7, r0
	ldr r0, [sp, #4]
	mov r1, #1
	add r0, r0, r7
	bl MOD12_02231490
	ldr r0, [sp, #8]
	mov r1, #1
	add r0, r0, r7
	add r2, r5, #0
	mov r3, #0
	bl MOD12_02231490
	add r4, r4, #1
	add r6, #0x30
	add r5, #0x30
	cmp r4, #4
	blt _02235158
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02235190: .word 0x00000231

	thumb_func_start MOD12_02235194
MOD12_02235194: ; 0x02235194
	push {r4, r5, lr}
	sub sp, #0xc
	mov r2, #1
	str r2, [sp]
	str r2, [sp, #4]
	ldr r2, _022351DC ; =0x000080F1
	mov r3, #0x17
	str r2, [sp, #8]
	mov r2, #0x2e
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _022351DC ; =0x000080F1
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x16
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _022351DC ; =0x000080F1
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x15
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_022351DC: .word 0x000080F1

	thumb_func_start MOD12_022351E0
MOD12_022351E0: ; 0x022351E0
	push {r4, lr}
	ldr r1, _022351FC ; =0x000080F1
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _022351FC ; =0x000080F1
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _022351FC ; =0x000080F1
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_022351FC: .word 0x000080F1

	thumb_func_start MOD12_02235200
MOD12_02235200: ; 0x02235200
	push {r3, r4, r5, r6, r7, lr}
	add r3, r0, #0
	mov r0, #0x16
	add r6, r1, #0
	lsl r0, r0, #4
	lsl r5, r6, #2
	add r4, r3, r0
	ldr r0, [r4, r5]
	add r7, r2, #0
	cmp r0, #0
	bne _02235222
	ldr r0, [r3, #0x18]
	ldr r1, [r3, #0x1c]
	ldr r2, _02235248 ; =MOD12_0224526C
	bl FUN_0200C154
	str r0, [r4, r5]
_02235222:
	ldr r0, [r4, r5]
	add r1, r7, #0
	bl FUN_0200C5C0
	mov r2, #0x30
	mul r2, r6
	add r2, #0x2a
	lsl r2, r2, #0x10
	ldr r0, [r4, r5]
	mov r1, #0x40
	asr r2, r2, #0x10
	bl FUN_0200C714
	ldr r0, [r4, r5]
	ldr r0, [r0]
	bl FUN_0200C59C
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02235248: .word MOD12_0224526C

	thumb_func_start MOD12_0223524C
MOD12_0223524C: ; 0x0223524C
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	mov r7, #0x16
	add r5, r0, #0
	add r6, r4, #0
	lsl r7, r7, #4
_02235258:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _02235268
	bl FUN_0200C3DC
	mov r0, #0x16
	lsl r0, r0, #4
	str r6, [r5, r0]
_02235268:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _02235258
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_02235274
MOD12_02235274: ; 0x02235274
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	add r0, r4, #0
	mov r1, #0
	mov r2, #6
	bl MI_CpuFill8
	lsl r0, r6, #1
	add r1, r5, r0
	ldr r0, _0223529C ; =0x00000236
	strb r6, [r4]
	ldrh r1, [r1, r0]
	add r0, #8
	strh r1, [r4, #2]
	add r1, r5, r6
	ldrb r0, [r1, r0]
	strb r0, [r4, #5]
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223529C: .word 0x00000236

	thumb_func_start MOD12_022352A0
MOD12_022352A0: ; 0x022352A0
	strb r0, [r2]
	cmp r1, #0
	bgt _022352AA
	mov r0, #0x1f
	bx lr
_022352AA:
	cmp r1, #0x14
	bgt _022352B2
	mov r0, #0x20
	bx lr
_022352B2:
	cmp r1, #0x32
	bgt _022352BA
	mov r0, #0x21
	bx lr
_022352BA:
	cmp r1, #0x5a
	bgt _022352C2
	mov r0, #0x22
	bx lr
_022352C2:
	mov r0, #0x23
	bx lr
	.align 2, 0

	thumb_func_start MOD12_022352C8
MOD12_022352C8: ; 0x022352C8
	push {r4, lr}
	mov r1, #0x32
	bl _s32_div_f
	cmp r0, #4
	blo _022352D6
	mov r0, #3
_022352D6:
	lsl r1, r0, #2
	ldr r0, _022352F0 ; =MOD12_02245218
	ldr r4, [r0, r1]
	cmp r4, #0
	bge _022352E4
	bl ErrorHandling
_022352E4:
	cmp r4, #0x7f
	ble _022352EC
	bl ErrorHandling
_022352EC:
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0
_022352F0: .word MOD12_02245218

	thumb_func_start MOD12_022352F4
MOD12_022352F4: ; 0x022352F4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	ldr r0, [sp, #0x1c]
	mov r1, #0
	strb r1, [r0]
	mov r0, #0x15
	mov r1, #0x14
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x14
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp, #0x1c]
	str r5, [r4]
	str r0, [r4, #0x10]
	strb r7, [r4, #0xd]
	ldr r0, [sp]
	strb r6, [r4, #0xb]
	str r0, [r4, #4]
	ldr r0, [sp, #0x18]
	ldr r2, _02235334 ; =0x00000BB8
	strb r0, [r4, #0xe]
	ldr r0, _02235338 ; =MOD12_0223533C
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02235334: .word 0x00000BB8
_02235338: .word MOD12_0223533C

	thumb_func_start MOD12_0223533C
MOD12_0223533C: ; 0x0223533C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #8]
	cmp r0, #0
	beq _02235354
	cmp r0, #1
	beq _02235376
	cmp r0, #2
	beq _022353A6
	b _0223541C
_02235354:
	ldrb r0, [r4, #0xd]
	cmp r0, #0
	beq _02235362
	sub r0, r0, #1
	add sp, #0x10
	strb r0, [r4, #0xd]
	pop {r3, r4, r5, pc}
_02235362:
	ldr r0, _02235468 ; =0x000006E5
	bl FUN_020054C8
	ldr r0, _02235468 ; =0x000006E5
	ldr r1, [r4, #4]
	bl FUN_0200488C
	ldrb r0, [r4, #8]
	add r0, r0, #1
	strb r0, [r4, #8]
_02235376:
	ldrb r0, [r4, #9]
	cmp r0, #0
	bne _02235380
	mov r1, #0
	b _02235382
_02235380:
	mov r1, #2
_02235382:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x15
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x2d
	ldr r2, [r2, #0x30]
	mov r3, #3
	bl FUN_020068C8
	ldrb r0, [r4, #8]
	add sp, #0x10
	add r0, r0, #1
	strb r0, [r4, #8]
	pop {r3, r4, r5, pc}
_022353A6:
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	ldrb r0, [r4, #0xc]
	cmp r0, #2
	bls _022353DE
	mov r0, #0
	strb r0, [r4, #0xc]
	ldrb r1, [r4, #9]
	mov r0, #1
	eor r0, r1
	strb r0, [r4, #9]
	ldrb r0, [r4, #8]
	sub r0, r0, #1
	strb r0, [r4, #8]
	ldrb r0, [r4, #9]
	cmp r0, #0
	bne _022353DE
	ldrb r0, [r4, #0xa]
	add r0, r0, #1
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0xa]
	cmp r0, #2
	bls _022353DE
	mov r0, #0xff
	add sp, #0x10
	strb r0, [r4, #8]
	pop {r3, r4, r5, pc}
_022353DE:
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	bne _02235464
	ldrb r0, [r4, #0xb]
	mov r1, #0x32
	lsl r0, r0, #4
	bl _s32_div_f
	mov r1, #0xf
	ldrsb r2, [r4, r1]
	cmp r2, r0
	bge _02235464
	add r2, r2, #2
	strb r2, [r4, #0xf]
	ldrsb r1, [r4, r1]
	cmp r1, r0
	ble _02235402
	strb r0, [r4, #0xf]
_02235402:
	ldrb r0, [r4, #0xf]
	mov r1, #0
	mov r2, #1
	str r0, [sp]
	ldr r0, _0223546C ; =0x0000237E
	mov r3, #2
	str r0, [sp, #4]
	ldr r0, [r4]
	ldr r0, [r0, #0x5c]
	bl FUN_020039E8
	add sp, #0x10
	pop {r3, r4, r5, pc}
_0223541C:
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	bne _02235452
	mov r0, #0xf
	ldrsb r1, [r4, r0]
	cmp r1, #0
	beq _02235452
	sub r1, r1, #2
	strb r1, [r4, #0xf]
	ldrsb r0, [r4, r0]
	cmp r0, #0
	bge _02235438
	mov r0, #0
	strb r0, [r4, #0xf]
_02235438:
	ldrb r0, [r4, #0xf]
	mov r1, #0
	mov r2, #1
	str r0, [sp]
	ldr r0, _0223546C ; =0x0000237E
	mov r3, #2
	str r0, [sp, #4]
	ldr r0, [r4]
	ldr r0, [r0, #0x5c]
	bl FUN_020039E8
	add sp, #0x10
	pop {r3, r4, r5, pc}
_02235452:
	ldr r0, [r4, #0x10]
	mov r1, #1
	strb r1, [r0]
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02235464:
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_02235468: .word 0x000006E5
_0223546C: .word 0x0000237E

	thumb_func_start MOD12_02235470
MOD12_02235470: ; 0x02235470
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r3, #0
	ldr r3, [sp, #0x38]
	add r6, sp, #0x1c
	str r3, [sp, #0x38]
	mov r3, #0
	str r3, [sp, #8]
	strb r3, [r5]
	mov r3, #0x30
	mul r3, r2
	ldr r2, [sp, #8]
	str r3, [sp, #0x10]
	add r3, #0x18
	str r2, [sp, #4]
	str r2, [sp, #0xc]
	mov r2, #0x18
	mul r2, r1
	add r7, r0, r2
	add r0, r3, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r3, [sp, #0x10]
	str r0, [sp, #0x18]
_022354A0:
	add r0, r7, #0
	add r0, #0xd0
	ldr r0, [r0]
	cmp r0, #0
	bne _022354AC
	b _0223560C
_022354AC:
	ldrb r1, [r5]
	cmp r1, #0
	bne _02235576
	add r1, sp, #0x20
	add r1, #2
	add r2, sp, #0x20
	bl FUN_0200C7A0
	mov r0, #4
	ldrsh r1, [r6, r0]
	ldr r0, [sp, #0x10]
	sub r1, r1, r0
	bpl _022354C8
	neg r1, r1
_022354C8:
	mov r0, #6
	ldrsh r0, [r6, r0]
	sub r0, #0x28
	bpl _022354D2
	neg r0, r0
_022354D2:
	bl FUN_020799F4
	lsl r0, r0, #8
	str r0, [sp, #8]
	mov r0, #6
	ldrsh r0, [r6, r0]
	sub r0, #0x28
	bl _fflt
	str r0, [sp, #0x14]
	mov r0, #4
	ldrsh r1, [r6, r0]
	ldr r0, [sp, #0x10]
	sub r0, r1, r0
	bl _fflt
	add r4, r0, #0
	ldr r0, [sp, #0x14]
	mov r1, #0
	bl _fgr
	ldr r0, _02235620 ; =0x45800000
	bls _02235514
	ldr r1, [sp, #0x14]
	bl _fmul
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	str r0, [sp]
	b _02235524
_02235514:
	ldr r1, [sp, #0x14]
	bl _fmul
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
	str r0, [sp]
_02235524:
	add r0, r4, #0
	mov r1, #0
	bl _fgr
	ldr r0, _02235620 ; =0x45800000
	bls _02235542
	add r1, r4, #0
	bl _fmul
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _02235550
_02235542:
	add r1, r4, #0
	bl _fmul
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_02235550:
	bl _ffix
	add r4, r0, #0
	ldr r0, [sp]
	bl _ffix
	add r1, r0, #0
	add r0, r4, #0
	bl FX_Atan2
	ldr r1, _02235624 ; =0x00008CA0
	mul r1, r0
	add r0, r1, #0
	ldr r1, _02235628 ; =0x0000FFFF
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
_02235576:
	mov r0, #0x15
	mov r1, #0x28
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x28
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp, #0x38]
	add r1, r4, #0
	str r0, [r4, #4]
	add r0, r7, #0
	add r0, #0xd0
	ldr r0, [r0]
	add r1, #0x21
	str r0, [r4, #8]
	ldr r0, [sp, #8]
	add r2, sp, #0x1c
	str r0, [r4, #0x10]
	ldr r0, [sp, #4]
	strh r0, [r4, #0x1e]
	mov r0, #2
	lsl r0, r0, #0xa
	str r0, [r4, #0x14]
	mov r0, #0x28
	strb r0, [r1]
	add r1, r4, #0
	ldr r0, [sp, #0x18]
	add r1, #0x22
	strb r0, [r1]
	str r5, [r4, #0xc]
	mov r0, #6
	ldrsh r1, [r6, r0]
	add r0, r4, #0
	add r0, #0x23
	strb r1, [r0]
	mov r0, #4
	ldrsh r1, [r6, r0]
	add r0, r4, #0
	add r0, #0x24
	strb r1, [r0]
	add r0, r7, #0
	add r0, #0xd0
	add r1, sp, #0x1c
	ldr r0, [r0]
	add r1, #2
	bl FUN_0200C7A0
	mov r0, #6
	ldrsh r1, [r6, r0]
	mov r0, #2
	ldrsh r0, [r6, r0]
	sub r0, r1, r0
	bpl _022355E6
	neg r0, r0
_022355E6:
	ldrb r2, [r5]
	lsl r0, r0, #8
	lsl r1, r2, #1
	add r1, r2, r1
	bl _s32_div_f
	strh r0, [r4, #0x1c]
	mov r0, #2
	ldrsh r0, [r6, r0]
	ldr r2, _0223562C ; =0x00009C40
	add r1, r4, #0
	lsl r0, r0, #8
	str r0, [r4, #0x18]
	ldr r0, _02235630 ; =MOD12_02235634
	bl FUN_0200CA44
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
_0223560C:
	ldr r0, [sp, #0xc]
	add r7, r7, #4
	add r0, r0, #1
	str r0, [sp, #0xc]
	cmp r0, #6
	bge _0223561A
	b _022354A0
_0223561A:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_02235620: .word 0x45800000
_02235624: .word 0x00008CA0
_02235628: .word 0x0000FFFF
_0223562C: .word 0x00009C40
_02235630: .word MOD12_02235634

	thumb_func_start MOD12_02235634
MOD12_02235634: ; 0x02235634
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #0
	beq _0223564C
	cmp r0, #1
	beq _02235696
	b _02235778
_0223564C:
	ldrh r0, [r5, #0x1c]
	ldr r1, [r5, #0x18]
	sub r1, r1, r0
	add r0, r5, #0
	str r1, [r5, #0x18]
	add r0, #0x23
	ldrb r0, [r0]
	lsl r0, r0, #8
	cmp r1, r0
	bgt _02235670
	str r0, [r5, #0x18]
	add r0, r5, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0x20
	strb r1, [r0]
_02235670:
	add r1, sp, #0xc
	ldr r0, [r5, #8]
	add r1, #2
	add r2, sp, #0xc
	bl FUN_0200C7A0
	ldr r0, [r5, #0x18]
	add r3, sp, #0xc
	asr r0, r0, #8
	strh r0, [r3, #2]
	mov r1, #2
	mov r2, #0
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldr r0, [r5, #8]
	bl FUN_0200C714
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_02235696:
	ldrh r2, [r5, #0x1e]
	ldr r1, [r5, #0x14]
	add r0, r5, #0
	add r1, r2, r1
	strh r1, [r5, #0x1e]
	ldrh r2, [r5, #0x1e]
	ldr r1, _022357A4 ; =0x00008CA0
	add r0, #0x1e
	cmp r2, r1
	blo _022356B0
	ldrh r2, [r0]
	sub r1, r2, r1
	strh r1, [r0]
_022356B0:
	mov r0, #3
	ldr r1, [r5, #0x10]
	lsl r0, r0, #8
	cmp r1, r0
	bls _022356BE
	sub r0, r1, r0
	b _022356C0
_022356BE:
	mov r0, #0
_022356C0:
	str r0, [r5, #0x10]
	mov r0, #2
	ldr r1, [r5, #0x10]
	lsl r0, r0, #8
	cmp r1, r0
	bhi _022356DA
	add r0, r5, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0x20
	strb r1, [r0]
_022356DA:
	ldr r0, [r5, #0x10]
	mov r1, #0x64
	lsr r4, r0, #8
	ldrh r0, [r5, #0x1e]
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl Cos
	str r0, [sp]
	lsl r6, r4, #0xc
	ldrh r0, [r5, #0x1e]
	mov r1, #0x64
	asr r7, r6, #0x1f
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl Sin
	str r0, [sp, #4]
	ldr r0, [sp]
	add r2, r6, #0
	asr r1, r0, #0x1f
	add r3, r7, #0
	bl _ll_mul
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	add r4, r1, #0
	asr r1, r0, #0x1f
	add r2, r6, #0
	add r3, r7, #0
	bl _ll_mul
	mov r3, #2
	add r2, r1, #0
	add r1, r5, #0
	add r7, r0, #0
	add r1, #0x21
	ldr r6, [sp, #8]
	lsl r3, r3, #0xa
	add r6, r6, r3
	ldr r3, _022357A8 ; =0x00000000
	ldrb r1, [r1]
	adc r4, r3
	lsl r3, r4, #0x14
	lsr r4, r6, #0xc
	orr r4, r3
	asr r3, r4, #0xb
	lsr r3, r3, #0x14
	add r3, r4, r3
	asr r3, r3, #0xc
	add r1, r1, r3
	mov r4, #2
	ldr r0, [r5, #8]
	lsl r1, r1, #0x10
	add r5, #0x22
	lsl r4, r4, #0xa
	asr r1, r1, #0x10
	ldrb r3, [r5]
	add r5, r7, r4
	ldr r4, _022357A8 ; =0x00000000
	adc r2, r4
	lsl r2, r2, #0x14
	lsr r4, r5, #0xc
	orr r4, r2
	asr r2, r4, #0xb
	lsr r2, r2, #0x14
	add r2, r4, r2
	asr r2, r2, #0xc
	add r2, r3, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_02235778:
	ldr r0, [r5, #8]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, _022357AC ; =0x000005E1
	bl FUN_020054C8
	ldr r0, [r5, #4]
	bl MOD12_02233638
	ldr r1, [r5, #0xc]
	ldrb r0, [r1]
	sub r0, r0, #1
	strb r0, [r1]
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022357A4: .word 0x00008CA0
_022357A8: .word 0x00000000
_022357AC: .word 0x000005E1

	thumb_func_start MOD12_022357B0
MOD12_022357B0: ; 0x022357B0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x15
	mov r1, #0xc
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0xc
	add r4, r0, #0
	bl MI_CpuFill8
	str r5, [r4]
	ldr r0, _022357DC ; =MOD12_022357F8
	ldr r2, _022357E0 ; =0x00009C40
	add r1, r4, #0
	strb r6, [r4, #8]
	bl FUN_0200CA44
	str r0, [r4, #4]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_022357DC: .word MOD12_022357F8
_022357E0: .word 0x00009C40

	thumb_func_start MOD12_022357E4
MOD12_022357E4: ; 0x022357E4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_022357F8
MOD12_022357F8: ; 0x022357F8
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	mov r7, #0x13
	add r6, r1, #0
	add r5, r4, #0
	lsl r7, r7, #4
_02235804:
	ldrb r2, [r6, #8]
	mov r1, #0x14
	ldr r0, [r6]
	mul r1, r2
	add r0, r0, r1
	add r0, r5, r0
	ldr r0, [r0, r7]
	cmp r0, #0
	beq _0223581A
	bl FUN_0200C5A8
_0223581A:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _02235804
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD12_02235824
MOD12_02235824: ; 0x02235824
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp]
	mov r0, #0x30
	mul r0, r2
	add r0, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r1, #0x14
	add r2, r3, #0
	mul r2, r1
	ldr r1, [sp]
	ldr r5, [sp, #0x20]
	mov r7, #0
	strb r7, [r5]
	add r6, r1, r2
	str r0, [sp, #4]
_02235846:
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _02235890
	mov r0, #0x15
	mov r1, #0x28
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x28
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp]
	ldr r2, _0223589C ; =0x00009C40
	str r0, [r4]
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	str r0, [r4, #4]
	str r5, [r4, #8]
	mov r0, #0x28
	strb r0, [r4, #0xf]
	ldr r0, [sp, #4]
	strb r0, [r4, #0x10]
	ldrb r1, [r5]
	mov r0, #0xc
	mul r0, r1
	strh r0, [r4, #0x24]
	ldr r0, _022358A0 ; =MOD12_022358A4
	add r1, r4, #0
	bl FUN_0200CA44
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
_02235890:
	add r7, r7, #1
	add r6, r6, #4
	cmp r7, #5
	blt _02235846
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223589C: .word 0x00009C40
_022358A0: .word MOD12_022358A4

	thumb_func_start MOD12_022358A4
MOD12_022358A4: ; 0x022358A4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	add r4, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _022358BE
	cmp r0, #1
	beq _022358FE
	cmp r0, #2
	bne _022358BC
	b _02235A26
_022358BC:
	b _02235A5E
_022358BE:
	mov r0, #0x24
	ldrsh r0, [r5, r0]
	cmp r0, #0
	ble _022358CE
	sub r0, r0, #1
	add sp, #8
	strh r0, [r5, #0x24]
	pop {r3, r4, r5, r6, r7, pc}
_022358CE:
	add r1, sp, #4
	ldr r0, [r5, #4]
	add r1, #2
	add r2, sp, #4
	bl FUN_0200C7A0
	add r2, sp, #4
	mov r1, #0
	ldrsh r0, [r2, r1]
	add r0, r0, #6
	strh r0, [r2]
	mov r0, #2
	ldrsh r0, [r2, r0]
	lsl r0, r0, #8
	str r0, [r5, #0x1c]
	ldrsh r0, [r2, r1]
	lsl r0, r0, #8
	str r0, [r5, #0x20]
	ldr r0, _02235A84 ; =0x000007F9
	bl FUN_020054C8
	ldrb r0, [r5, #0xe]
	add r0, r0, #1
	strb r0, [r5, #0xe]
_022358FE:
	ldrh r2, [r5, #0xc]
	mov r1, #2
	lsl r1, r1, #0xa
	add r1, r2, r1
	strh r1, [r5, #0xc]
	ldrh r2, [r5, #0xc]
	ldr r1, _02235A88 ; =0x00008CA0
	add r0, r5, #0
	add r0, #0xc
	cmp r2, r1
	blo _0223591A
	ldrh r2, [r0]
	sub r1, r2, r1
	strh r1, [r0]
_0223591A:
	ldrh r0, [r5, #0xc]
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl Sin
	add r4, r0, #0
	ldrh r0, [r5, #0xc]
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl Cos
	add r6, r0, #0
	ldr r0, [r5, #0x20]
	mov r2, #3
	add r0, #0x80
	str r0, [r5, #0x20]
	asr r1, r4, #0x1f
	add r0, r4, #0
	lsl r2, r2, #0xe
	mov r3, #0
	bl _ll_mul
	mov r2, #6
	str r0, [sp]
	add r4, r1, #0
	asr r1, r6, #0x1f
	add r0, r6, #0
	lsl r2, r2, #0xc
	mov r3, #0
	bl _ll_mul
	add r2, r1, #0
	ldr r1, [r5, #0x1c]
	mov r6, #2
	add r7, r0, #0
	ldr r3, [sp]
	lsl r6, r6, #0xa
	asr r1, r1, #8
	add r6, r3, r6
	ldr r3, _02235A8C ; =0x00000000
	ldr r0, [r5, #4]
	adc r4, r3
	lsl r3, r4, #0x14
	lsr r4, r6, #0xc
	orr r4, r3
	asr r3, r4, #0xb
	lsr r3, r3, #0x14
	add r3, r4, r3
	asr r3, r3, #0xc
	add r1, r1, r3
	ldr r3, [r5, #0x20]
	mov r4, #2
	lsl r1, r1, #0x10
	ldr r6, _02235A8C ; =0x00000000
	lsl r4, r4, #0xa
	asr r1, r1, #0x10
	asr r3, r3, #8
	add r4, r7, r4
	adc r2, r6
	lsl r6, r2, #0x14
	lsr r2, r4, #0xc
	orr r2, r6
	asr r4, r2, #0xb
	lsr r4, r4, #0x14
	add r4, r2, r4
	asr r2, r4, #0xc
	add r2, r3, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	mov r0, #0x24
	ldrsh r1, [r5, r0]
	add r1, r1, #1
	strh r1, [r5, #0x24]
	ldrsh r0, [r5, r0]
	cmp r0, #0x50
	ble _02235A80
	mov r0, #0
	strh r0, [r5, #0x24]
	add r1, sp, #4
	ldr r0, [r5, #4]
	add r1, #2
	add r2, sp, #4
	bl FUN_0200C7A0
	add r2, sp, #4
	mov r0, #2
	ldrsh r0, [r2, r0]
	lsl r1, r0, #8
	str r1, [r5, #0x1c]
	mov r1, #0
	ldrsh r6, [r2, r1]
	lsl r1, r6, #8
	str r1, [r5, #0x20]
	ldrb r1, [r5, #0xf]
	sub r0, r0, r1
	bpl _022359EC
	neg r0, r0
_022359EC:
	ldrb r1, [r5, #0x10]
	lsl r0, r0, #8
	sub r4, r6, r1
	bpl _022359F6
	neg r4, r4
_022359F6:
	mov r1, #3
	lsl r1, r1, #8
	str r1, [r5, #0x14]
	bl _s32_div_f
	add r1, r0, #0
	lsl r0, r4, #8
	bl _s32_div_f
	str r0, [r5, #0x18]
	ldrb r0, [r5, #0x10]
	cmp r0, r6
	bge _02235A16
	ldr r0, [r5, #0x18]
	neg r0, r0
	str r0, [r5, #0x18]
_02235A16:
	ldr r0, _02235A90 ; =0x000006EA
	bl FUN_020054C8
	ldrb r0, [r5, #0xe]
	add sp, #8
	add r0, r0, #1
	strb r0, [r5, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02235A26:
	ldr r1, [r5, #0x1c]
	ldr r0, [r5, #0x14]
	sub r0, r1, r0
	str r0, [r5, #0x1c]
	ldr r1, [r5, #0x20]
	ldr r0, [r5, #0x18]
	add r0, r1, r0
	str r0, [r5, #0x20]
	ldrb r0, [r5, #0xf]
	lsl r1, r0, #8
	ldr r0, [r5, #0x1c]
	cmp r0, r1
	bgt _02235A48
	str r1, [r5, #0x1c]
	ldrb r0, [r5, #0xe]
	add r0, r0, #1
	strb r0, [r5, #0xe]
_02235A48:
	ldr r1, [r5, #0x1c]
	ldr r2, [r5, #0x20]
	lsl r1, r1, #8
	lsl r2, r2, #8
	ldr r0, [r5, #4]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02235A5E:
	ldr r0, [r5, #4]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, _02235A94 ; =0x000005E1
	bl FUN_020054C8
	ldr r1, [r5, #8]
	ldrb r0, [r1]
	sub r0, r0, #1
	strb r0, [r1]
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_02235A80:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02235A84: .word 0x000007F9
_02235A88: .word 0x00008CA0
_02235A8C: .word 0x00000000
_02235A90: .word 0x000006EA
_02235A94: .word 0x000005E1

	thumb_func_start MOD12_02235A98
MOD12_02235A98: ; 0x02235A98
	push {r4}
	sub sp, #0xc
	ldr r3, _02235AC0 ; =MOD12_022451D4
	add r2, sp, #0
	ldrh r4, [r3, #0x14]
	add r1, sp, #0
	lsl r0, r0, #1
	strh r4, [r2]
	ldrh r4, [r3, #0x16]
	strh r4, [r2, #2]
	ldrh r4, [r3, #0x18]
	strh r4, [r2, #4]
	ldrh r4, [r3, #0x1a]
	ldrh r3, [r3, #0x1c]
	strh r4, [r2, #6]
	strh r3, [r2, #8]
	ldrh r0, [r1, r0]
	add sp, #0xc
	pop {r4}
	bx lr
	.align 2, 0
_02235AC0: .word MOD12_022451D4

	thumb_func_start MOD12_02235AC4
MOD12_02235AC4: ; 0x02235AC4
	push {r4}
	sub sp, #0xc
	ldr r3, _02235AEC ; =MOD12_022451D4
	add r2, sp, #0
	ldrh r4, [r3, #0xa]
	add r1, sp, #0
	lsl r0, r0, #1
	strh r4, [r2]
	ldrh r4, [r3, #0xc]
	strh r4, [r2, #2]
	ldrh r4, [r3, #0xe]
	strh r4, [r2, #4]
	ldrh r4, [r3, #0x10]
	ldrh r3, [r3, #0x12]
	strh r4, [r2, #6]
	strh r3, [r2, #8]
	ldrh r0, [r1, r0]
	add sp, #0xc
	pop {r4}
	bx lr
	.align 2, 0
_02235AEC: .word MOD12_022451D4

	thumb_func_start MOD12_02235AF0
MOD12_02235AF0: ; 0x02235AF0
	push {r4}
	sub sp, #0xc
	ldr r3, _02235B18 ; =MOD12_022451D4
	add r2, sp, #0
	ldrh r4, [r3]
	add r1, sp, #0
	lsl r0, r0, #1
	strh r4, [r2]
	ldrh r4, [r3, #2]
	strh r4, [r2, #2]
	ldrh r4, [r3, #4]
	strh r4, [r2, #4]
	ldrh r4, [r3, #6]
	ldrh r3, [r3, #8]
	strh r4, [r2, #6]
	strh r3, [r2, #8]
	ldrh r0, [r1, r0]
	add sp, #0xc
	pop {r4}
	bx lr
	.align 2, 0
_02235B18: .word MOD12_022451D4

	thumb_func_start MOD12_02235B1C
MOD12_02235B1C: ; 0x02235B1C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r3, #0
	add r6, r0, #0
	add r7, r1, #0
	add r5, r2, #0
	add r0, r4, #0
	mov r1, #0
	mov r2, #0xc
	bl MI_CpuFill8
	strh r5, [r4, #4]
	cmp r5, #0x8f
	bgt _02235B52
	bge _02235B8A
	cmp r5, #0x4c
	bgt _02235B44
	bge _02235B8A
	cmp r5, #0xd
	beq _02235B8A
	pop {r3, r4, r5, r6, r7, pc}
_02235B44:
	cmp r5, #0x77
	bgt _02235B4C
	beq _02235BC8
	pop {r3, r4, r5, r6, r7, pc}
_02235B4C:
	cmp r5, #0x82
	beq _02235B8A
	pop {r3, r4, r5, r6, r7, pc}
_02235B52:
	ldr r1, _02235BE4 ; =0x0000010B
	cmp r5, r1
	bgt _02235B72
	bge _02235BCE
	cmp r5, #0xae
	bgt _02235B62
	beq _02235B9C
	pop {r3, r4, r5, r6, r7, pc}
_02235B62:
	cmp r5, #0xda
	bgt _02235BE2
	cmp r5, #0xd8
	blt _02235BE2
	beq _02235B90
	cmp r5, #0xda
	beq _02235B96
	pop {r3, r4, r5, r6, r7, pc}
_02235B72:
	add r0, r1, #0
	add r0, #0xd
	cmp r5, r0
	bgt _02235B82
	add r1, #0xd
	cmp r5, r1
	beq _02235BD4
	pop {r3, r4, r5, r6, r7, pc}
_02235B82:
	add r1, #0xc8
	cmp r5, r1
	beq _02235BDA
	pop {r3, r4, r5, r6, r7, pc}
_02235B8A:
	mov r0, #1
	strb r0, [r4, #6]
	pop {r3, r4, r5, r6, r7, pc}
_02235B90:
	mov r0, #0xff
	strb r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_02235B96:
	mov r0, #0
	strb r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_02235B9C:
	lsl r5, r7, #2
	ldr r0, [r6, r5]
	mov r1, #0xb0
	mov r2, #0
	bl GetMonData
	add r7, r0, #0
	ldr r0, [r6, r5]
	mov r1, #0xb1
	mov r2, #0
	bl GetMonData
	cmp r7, #7
	beq _02235BBC
	cmp r0, #7
	bne _02235BC2
_02235BBC:
	mov r0, #1
	strb r0, [r4, #7]
	pop {r3, r4, r5, r6, r7, pc}
_02235BC2:
	mov r0, #0
	strb r0, [r4, #7]
	pop {r3, r4, r5, r6, r7, pc}
_02235BC8:
	mov r0, #1
	strh r0, [r4, #4]
	pop {r3, r4, r5, r6, r7, pc}
_02235BCE:
	mov r0, #0xa1
	strh r0, [r4, #4]
	pop {r3, r4, r5, r6, r7, pc}
_02235BD4:
	mov r0, #1
	strb r0, [r4, #7]
	pop {r3, r4, r5, r6, r7, pc}
_02235BDA:
	mov r0, #1
	strb r0, [r4, #6]
	ldr r0, _02235BE8 ; =0x200400C0
	str r0, [r4]
_02235BE2:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02235BE4: .word 0x0000010B
_02235BE8: .word 0x200400C0

	thumb_func_start MOD12_02235BEC
MOD12_02235BEC: ; 0x02235BEC
	cmp r2, #0
	bne _02235BF4
	mov r0, #0
	bx lr
_02235BF4:
	lsl r3, r1, #1
	add r3, r0, r3
	ldrh r3, [r3, #0x26]
	cmp r2, r3
	bne _02235C12
	lsl r1, r1, #2
	add r0, r0, r1
	add r0, #0xe0
	ldr r0, [r0]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r2, r0
	beq _02235C12
	mov r0, #0
	bx lr
_02235C12:
	mov r0, #1
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02235C18
MOD12_02235C18: ; 0x02235C18
	push {r3, r4}
	add r1, r0, r1
	ldrb r4, [r1, #0xe]
	mov r3, #0
	add r2, r3, #0
_02235C22:
	add r1, r0, r2
	ldrb r1, [r1, #0xe]
	cmp r1, r4
	bne _02235C2C
	add r3, r3, #1
_02235C2C:
	add r2, r2, #1
	cmp r2, #4
	blt _02235C22
	sub r0, r3, #1
	pop {r3, r4}
	bx lr

	thumb_func_start MOD12_02235C38
MOD12_02235C38: ; 0x02235C38
	ldr r1, _02235C40 ; =MOD12_022454C8
	ldrb r0, [r1, r0]
	bx lr
	nop
_02235C40: .word MOD12_022454C8

	thumb_func_start MOD12_02235C44
MOD12_02235C44: ; 0x02235C44
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #0xb
	bl GetWazaAttr
	lsl r1, r4, #2
	add r2, r4, r1
	ldr r1, _02235C5C ; =MOD12_022454E4
	add r1, r1, r2
	ldrsb r0, [r0, r1]
	pop {r4, pc}
	.align 2, 0
_02235C5C: .word MOD12_022454E4

	thumb_func_start MOD12_02235C60
MOD12_02235C60: ; 0x02235C60
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r3, #0
	mov lr, r0
	add r2, sp, #8
	add r1, sp, #4
	add r7, r3, #0
	add r0, sp, #0
	mov r6, #0x1a
	b _02235C9A
_02235C74:
	lsl r4, r3, #1
	mov r5, lr
	add r5, r5, r4
	ldrsh r5, [r5, r6]
	strb r3, [r1, r3]
	strh r5, [r2, r4]
	add r4, r7, #0
	b _02235C94
_02235C84:
	mov r5, lr
	add r5, r5, r4
	ldrb r5, [r5, #1]
	cmp r3, r5
	bne _02235C92
	strb r4, [r0, r3]
	b _02235C98
_02235C92:
	add r4, r4, #1
_02235C94:
	cmp r4, #4
	blt _02235C84
_02235C98:
	add r3, r3, #1
_02235C9A:
	cmp r3, #4
	blt _02235C74
	mov r3, #0
	ldr r6, _02235D70 ; =MOD12_022454D4
	add r1, sp, #8
	ldr r0, _02235D74 ; =MOD12_022454CC
	ldr r2, _02235D78 ; =MOD12_022454DC
	mov r7, #0x2c
	b _02235CFC
_02235CAC:
	add r5, r3, #0
	mul r5, r7
	mov r4, lr
	add r4, r4, r5
	ldr r4, [r4, #0x58]
	lsl r5, r4, #0x1a
	lsr r5, r5, #0x1e
	cmp r5, #3
	bhi _02235CFA
	add r5, r5, r5
	add r5, pc
	ldrh r5, [r5, #6]
	lsl r5, r5, #0x10
	asr r5, r5, #0x10
	add pc, r5
_02235CCA: ; jump table
	.short _02235CFA - _02235CCA - 2 ; case 0
	.short _02235CD2 - _02235CCA - 2 ; case 1
	.short _02235CE0 - _02235CCA - 2 ; case 2
	.short _02235CEE - _02235CCA - 2 ; case 3
_02235CD2:
	lsl r4, r4, #0x18
	lsr r4, r4, #0x1e
	lsl r4, r4, #1
	ldrsh r5, [r2, r4]
	lsl r4, r3, #1
	strh r5, [r1, r4]
	b _02235CFA
_02235CE0:
	lsl r4, r4, #0x18
	lsr r4, r4, #0x1e
	lsl r4, r4, #1
	ldrsh r5, [r0, r4]
	lsl r4, r3, #1
	strh r5, [r1, r4]
	b _02235CFA
_02235CEE:
	lsl r4, r4, #0x18
	lsr r4, r4, #0x1e
	lsl r4, r4, #1
	ldrsh r5, [r6, r4]
	lsl r4, r3, #1
	strh r5, [r1, r4]
_02235CFA:
	add r3, r3, #1
_02235CFC:
	cmp r3, #4
	blt _02235CAC
	mov r3, #0
	b _02235D52
_02235D04:
	mov r4, #3
	add r2, sp, #8
	add r7, sp, #0
	b _02235D4C
_02235D0C:
	sub r1, r4, #1
	lsl r0, r1, #1
	lsl r5, r4, #1
	ldrsh r0, [r2, r0]
	ldrsh r5, [r2, r5]
	cmp r0, r5
	bgt _02235D26
	cmp r0, r5
	bne _02235D4A
	ldrb r1, [r7, r1]
	ldrb r0, [r7, r4]
	cmp r1, r0
	bhs _02235D4A
_02235D26:
	sub r0, r4, #1
	lsl r1, r4, #1
	lsl r5, r0, #1
	mov ip, r5
	ldrsh r6, [r2, r1]
	ldrsh r5, [r2, r5]
	strh r5, [r2, r1]
	mov r1, ip
	strh r6, [r2, r1]
	add r1, sp, #4
	ldrb r6, [r1, r4]
	ldrb r5, [r1, r0]
	strb r5, [r1, r4]
	strb r6, [r1, r0]
	ldrb r5, [r7, r4]
	ldrb r1, [r7, r0]
	strb r1, [r7, r4]
	strb r5, [r7, r0]
_02235D4A:
	sub r4, r4, #1
_02235D4C:
	cmp r4, r3
	bgt _02235D0C
	add r3, r3, #1
_02235D52:
	cmp r3, #3
	blt _02235D04
	mov r3, #0
	add r2, sp, #4
	b _02235D66
_02235D5C:
	ldrb r1, [r2, r3]
	mov r0, lr
	add r0, r0, r3
	strb r1, [r0, #1]
	add r3, r3, #1
_02235D66:
	cmp r3, #4
	blt _02235D5C
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02235D70: .word MOD12_022454D4
_02235D74: .word MOD12_022454CC
_02235D78: .word MOD12_022454DC

	thumb_func_start MOD12_02235D7C
MOD12_02235D7C: ; 0x02235D7C
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r1, _02235DB4 ; =MOD12_02245500
	add r3, sp, #0
	str r1, [sp]
	mov r1, #0x16
	strh r1, [r3, #4]
	ldr r1, [r0]
	ldr r2, _02235DB8 ; =0x00000123
	ldrb r1, [r1, r2]
	strb r1, [r3, #6]
	sub r1, r2, #7
	ldr r4, [r0]
	add r2, #0x4e
	ldrb r1, [r4, r1]
	strb r1, [r3, #8]
	ldr r1, [r0]
	ldrb r1, [r1, r2]
	strb r1, [r3, #7]
	mov r1, #0xc3
	lsl r1, r1, #4
	add r0, r0, r1
	add r1, sp, #0
	bl MOD12_02240ED0
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_02235DB4: .word MOD12_02245500
_02235DB8: .word 0x00000123

	thumb_func_start MOD12_02235DBC
MOD12_02235DBC: ; 0x02235DBC
	push {r3, lr}
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	mov r3, #0
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02235DD4
MOD12_02235DD4: ; 0x02235DD4
	push {r3, lr}
	mov r0, #0xc3
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r2, #0
	mov r2, #0
	add r3, r2, #0
	bl MOD12_02240FB0
	pop {r3, pc}

	thumb_func_start MOD12_02235DE8
MOD12_02235DE8: ; 0x02235DE8
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02235DEC
MOD12_02235DEC: ; 0x02235DEC
	push {r3, lr}
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	mov r3, #0
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02235E04
MOD12_02235E04: ; 0x02235E04
	push {r3, lr}
	ldr r0, _02235E20 ; =0x00001650
	mov r3, #1
	strb r3, [r1, r0]
	mov r0, #0xc3
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r2, #0
	mov r2, #0
	add r3, r2, #0
	bl MOD12_02240FB0
	pop {r3, pc}
	nop
_02235E20: .word 0x00001650

	thumb_func_start MOD12_02235E24
MOD12_02235E24: ; 0x02235E24
	push {r3, lr}
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	mov r3, #0
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02235E3C
MOD12_02235E3C: ; 0x02235E3C
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r0, #0x15
	mov r1, #0x10
	add r5, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x10
	bl MI_CpuFill8
	str r6, [r4]
	ldrh r0, [r5]
	ldr r2, _02235E74 ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, _02235E78 ; =MOD12_02235E7C
	bl FUN_0200CA44
	pop {r4, r5, r6, pc}
	nop
_02235E74: .word 0x00007530
_02235E78: .word MOD12_02235E7C

	thumb_func_start MOD12_02235E7C
MOD12_02235E7C: ; 0x02235E7C
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	ldrb r1, [r4, #0xf]
	add r5, r0, #0
	cmp r1, #0
	beq _02235E94
	cmp r1, #1
	beq _02235EB2
	cmp r1, #2
	beq _02235ECC
	b _02235EDA
_02235E94:
	mov r1, #0
	add r0, r4, #0
	str r1, [sp]
	add r0, #0xe
	str r0, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	mov r3, #0x46
	bl MOD12_022352F4
	ldrb r0, [r4, #0xf]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xf]
	pop {r3, r4, r5, pc}
_02235EB2:
	ldrh r0, [r4, #0xc]
	add r0, r0, #1
	strh r0, [r4, #0xc]
	ldrh r0, [r4, #0xc]
	cmp r0, #0x1e
	bls _02235EF8
	mov r0, #0
	strh r0, [r4, #0xc]
	ldrb r0, [r4, #0xf]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xf]
	pop {r3, r4, r5, pc}
_02235ECC:
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	bne _02235EF8
	add r0, r1, #1
	add sp, #8
	strb r0, [r4, #0xf]
	pop {r3, r4, r5, pc}
_02235EDA:
	mov r0, #0xc3
	mov r2, #0
	ldr r1, [r4]
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02235EF8:
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_02235EFC
MOD12_02235EFC: ; 0x02235EFC
	push {r3, lr}
	mov r0, #0xf4
	str r0, [sp]
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02235F14
MOD12_02235F14: ; 0x02235F14
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	mov r0, #0x15
	mov r1, #0x1c
	add r5, r2, #0
	add r6, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x1c
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _02235F6C ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	add r0, r6, #0
	add r0, #0xe4
	ldrb r0, [r0]
	strb r0, [r4, #0x18]
	add r0, r6, #0
	add r0, #0xd8
	ldrh r0, [r0]
	strh r0, [r4, #0x12]
	add r0, r6, #0
	add r0, #0xda
	ldrh r0, [r0]
	add r6, #0xdc
	strh r0, [r4, #0x14]
	ldrh r0, [r6]
	strh r0, [r4, #0x16]
	ldr r0, _02235F70 ; =MOD12_02235F74
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02235F6C: .word 0x00007530
_02235F70: .word MOD12_02235F74

	thumb_func_start MOD12_02235F74
MOD12_02235F74: ; 0x02235F74
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0xc]
	cmp r0, #4
	bhi _0223601A
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02235F8E: ; jump table
	.short _02235F98 - _02235F8E - 2 ; case 0
	.short _02235FBA - _02235F8E - 2 ; case 1
	.short _02235FD4 - _02235F8E - 2 ; case 2
	.short _02235FEE - _02235F8E - 2 ; case 3
	.short _0223600C - _02235F8E - 2 ; case 4
_02235F98:
	ldrb r1, [r4, #0x18]
	cmp r1, #0
	beq _02235FAA
	add r2, r4, #0
	ldr r0, [r4]
	add r2, #0x12
	mov r3, #0
	bl MOD12_02234FB0
_02235FAA:
	ldr r0, _0223603C ; =0x000006F9
	bl FUN_020054C8
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02235FBA:
	ldrb r0, [r4, #0x18]
	cmp r0, #0
	beq _02235FCA
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _02236038
_02235FCA:
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02235FD4:
	ldrh r0, [r4, #0xe]
	add r0, r0, #1
	strh r0, [r4, #0xe]
	ldrh r0, [r4, #0xe]
	cmp r0, #0x1e
	bls _02236038
	mov r0, #0
	strh r0, [r4, #0xe]
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02235FEE:
	mov r1, #0
	add r0, r4, #0
	str r1, [sp]
	add r0, #0x10
	str r0, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	mov r3, #0x46
	bl MOD12_022352F4
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223600C:
	ldrb r1, [r4, #0x10]
	cmp r1, #1
	bne _02236038
	add r0, r0, #1
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223601A:
	mov r0, #0xc3
	mov r2, #0
	ldr r1, [r4]
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02236038:
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223603C: .word 0x000006F9

	thumb_func_start MOD12_02236040
MOD12_02236040: ; 0x02236040
	push {r3, lr}
	mov r0, #0xf4
	str r0, [sp]
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02236058
MOD12_02236058: ; 0x02236058
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	mov r0, #0x15
	mov r1, #0x1c
	add r5, r2, #0
	add r7, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x1c
	bl MI_CpuFill8
	str r6, [r4]
	ldrh r0, [r5]
	add r2, r4, #0
	mov r1, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	add r2, #0x16
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldrb r0, [r7]
	strb r0, [r4, #0x15]
	add r0, r6, #0
	bl MOD12_0223483C
	ldr r0, _022360A8 ; =MOD12_022360B0
	ldr r2, _022360AC ; =0x00007530
	add r1, r4, #0
	bl FUN_0200CA44
	add r0, r6, #0
	bl MOD12_02234EFC
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022360A8: .word MOD12_022360B0
_022360AC: .word 0x00007530

	thumb_func_start MOD12_022360B0
MOD12_022360B0: ; 0x022360B0
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r1, [r0, #0xc]
	ldrb r0, [r4, #0x15]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_02068E14
	add r5, r0, #0
	ldrb r0, [r4, #0x14]
	cmp r0, #3
	bls _022360D0
	b _022361DA
_022360D0:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022360DC: ; jump table
	.short _022360E4 - _022360DC - 2 ; case 0
	.short _02236100 - _022360DC - 2 ; case 1
	.short _02236162 - _022360DC - 2 ; case 2
	.short _0223617C - _022360DC - 2 ; case 3
_022360E4:
	mov r0, #0x18
	ldrsh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, #0x18]
	ldrsh r0, [r4, r0]
	cmp r0, #0xa
	bgt _022360F4
	b _022361FE
_022360F4:
	mov r0, #0
	strh r0, [r4, #0x18]
	ldrb r0, [r4, #0x14]
	add r0, r0, #1
	strb r0, [r4, #0x14]
	pop {r4, r5, r6, pc}
_02236100:
	ldrb r0, [r4, #0x15]
	mov r1, #0
	lsl r5, r0, #2
	ldr r0, [r4]
	ldr r0, [r0, #0xc]
	ldr r0, [r0, r5]
	bl FUN_02068E14
	add r6, r0, #0
	ldr r0, [r4]
	mov r1, #0x25
	add r0, r0, r5
	ldr r0, [r0, #0x14]
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4]
	mov r1, #6
	add r0, r0, r5
	ldr r0, [r0, #0x14]
	mov r2, #0
	bl FUN_02007558
	ldr r0, [r4]
	mov r2, #1
	add r0, r0, r5
	ldr r0, [r0, #0x14]
	mov r1, #0
	lsl r2, r2, #8
	bl FUN_02007558
	ldr r0, [r4]
	add r6, #0xac
	add r0, r0, r5
	ldr r0, [r0, #0x14]
	mov r1, #1
	add r2, r6, #0
	bl FUN_02007558
	mov r0, #1
	lsl r0, r0, #0x10
	str r0, [r4, #0xc]
	mov r0, #0x2b
	lsl r0, r0, #0xa
	str r0, [r4, #0x10]
	ldrb r0, [r4, #0x14]
	add r0, r0, #1
	strb r0, [r4, #0x14]
	pop {r4, r5, r6, pc}
_02236162:
	ldr r0, [r4]
	ldrb r2, [r4, #0x15]
	ldr r1, [r0]
	ldr r0, _02236200 ; =0x00000123
	ldrb r0, [r1, r0]
	cmp r2, r0
	bne _02236176
	ldr r0, _02236204 ; =0x000006F8
	bl FUN_020054C8
_02236176:
	ldrb r0, [r4, #0x14]
	add r0, r0, #1
	strb r0, [r4, #0x14]
_0223617C:
	ldr r1, [r4, #0xc]
	ldr r0, _02236208 ; =0x000005B6
	sub r0, r1, r0
	str r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	ldr r0, _0223620C ; =0x00000892
	sub r0, r1, r0
	str r0, [r4, #0x10]
	ldr r0, [r4, #0xc]
	asr r0, r0, #8
	cmp r0, #0xd8
	ble _0223619C
	ldr r0, [r4, #0x10]
	asr r0, r0, #8
	cmp r0, #0x70
	bgt _022361AE
_0223619C:
	mov r0, #0x36
	lsl r0, r0, #0xa
	str r0, [r4, #0xc]
	mov r0, #7
	lsl r0, r0, #0xc
	str r0, [r4, #0x10]
	ldrb r0, [r4, #0x14]
	add r0, r0, #1
	strb r0, [r4, #0x14]
_022361AE:
	ldrb r0, [r4, #0x15]
	ldr r2, [r4, #0xc]
	ldr r1, [r4]
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #0x14]
	mov r1, #0
	asr r2, r2, #8
	bl FUN_02007558
	ldrb r0, [r4, #0x15]
	ldr r2, [r4, #0x10]
	ldr r1, [r4]
	lsl r0, r0, #2
	add r0, r1, r0
	asr r2, r2, #8
	ldr r0, [r0, #0x14]
	mov r1, #1
	add r2, r2, r5
	bl FUN_02007558
	pop {r4, r5, r6, pc}
_022361DA:
	ldrb r0, [r4, #0x16]
	cmp r0, #1
	bne _022361FE
	mov r0, #0xc3
	mov r2, #0
	ldr r1, [r4]
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r6, #0
	bl FUN_0200CAB4
_022361FE:
	pop {r4, r5, r6, pc}
	.align 2, 0
_02236200: .word 0x00000123
_02236204: .word 0x000006F8
_02236208: .word 0x000005B6
_0223620C: .word 0x00000892

	thumb_func_start MOD12_02236210
MOD12_02236210: ; 0x02236210
	push {r3, lr}
	mov r0, #0xf4
	str r0, [sp]
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02236228
MOD12_02236228: ; 0x02236228
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	mov r0, #0x15
	mov r1, #0x1c
	add r5, r2, #0
	add r7, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x1c
	bl MI_CpuFill8
	str r6, [r4]
	ldrh r0, [r5]
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldrb r0, [r7]
	strb r0, [r4, #0x15]
	ldr r1, [r6, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_02068E14
	mov r0, #0x36
	lsl r0, r0, #0xa
	str r0, [r4, #0xc]
	mov r0, #7
	lsl r0, r0, #0xc
	str r0, [r4, #0x10]
	ldr r0, _0223627C ; =MOD12_02236284
	ldr r2, _02236280 ; =0x00007530
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223627C: .word MOD12_02236284
_02236280: .word 0x00007530

	thumb_func_start MOD12_02236284
MOD12_02236284: ; 0x02236284
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	ldrb r0, [r5, #0x15]
	mov r1, #0
	lsl r4, r0, #2
	ldr r0, [r5]
	ldr r0, [r0, #0xc]
	ldr r0, [r0, r4]
	bl FUN_02068E14
	add r6, r0, #0
	ldrb r0, [r5, #0x14]
	cmp r0, #0
	beq _022362A8
	cmp r0, #1
	beq _0223631A
	b _02236342
_022362A8:
	ldr r1, [r5, #0xc]
	ldr r0, _02236364 ; =0x000005B6
	add r0, r1, r0
	str r0, [r5, #0xc]
	ldr r1, [r5, #0x10]
	ldr r0, _02236368 ; =0x00000892
	add r0, r1, r0
	str r0, [r5, #0x10]
	ldr r0, [r5, #0xc]
	asr r1, r0, #8
	mov r0, #1
	lsl r0, r0, #8
	cmp r1, r0
	bge _022362CC
	ldr r0, [r5, #0x10]
	asr r0, r0, #8
	cmp r0, #0xac
	blt _022362EE
_022362CC:
	ldr r0, [r5]
	mov r1, #0x25
	add r0, r0, r4
	ldr r0, [r0, #0x14]
	mov r2, #1
	bl FUN_02007558
	ldr r0, [r5]
	mov r1, #6
	add r0, r0, r4
	ldr r0, [r0, #0x14]
	mov r2, #1
	bl FUN_02007558
	ldrb r0, [r5, #0x14]
	add r0, r0, #1
	strb r0, [r5, #0x14]
_022362EE:
	ldrb r0, [r5, #0x15]
	ldr r2, [r5, #0xc]
	ldr r1, [r5]
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #0x14]
	mov r1, #0
	asr r2, r2, #8
	bl FUN_02007558
	ldrb r0, [r5, #0x15]
	ldr r2, [r5, #0x10]
	ldr r1, [r5]
	lsl r0, r0, #2
	add r0, r1, r0
	asr r2, r2, #8
	ldr r0, [r0, #0x14]
	mov r1, #1
	add r2, r2, r6
	bl FUN_02007558
	pop {r3, r4, r5, r6, r7, pc}
_0223631A:
	ldrb r1, [r5, #0x15]
	ldr r0, [r5]
	ldr r2, _0223636C ; =0x00001652
	add r3, r0, r1
	ldrb r2, [r3, r2]
	cmp r2, #1
	bne _0223633A
	add r0, #0xc
	bl MOD12_022336AC
	ldrb r0, [r5, #0x15]
	ldr r1, [r5]
	mov r2, #0
	add r1, r1, r0
	ldr r0, _0223636C ; =0x00001652
	strb r2, [r1, r0]
_0223633A:
	ldrb r0, [r5, #0x14]
	add r0, r0, #1
	strb r0, [r5, #0x14]
	pop {r3, r4, r5, r6, r7, pc}
_02236342:
	mov r0, #0xc3
	mov r2, #0
	ldr r1, [r5]
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r5, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r5, #0
	bl FreeToHeap
	add r0, r7, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02236364: .word 0x000005B6
_02236368: .word 0x00000892
_0223636C: .word 0x00001652

	thumb_func_start MOD12_02236370
MOD12_02236370: ; 0x02236370
	push {r3, lr}
	mov r0, #0xf4
	str r0, [sp]
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02236388
MOD12_02236388: ; 0x02236388
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	mov r0, #0x15
	mov r1, #0x1c
	add r6, r2, #0
	add r5, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x1c
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r6]
	ldr r2, _022363EC ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r6, #2]
	strh r0, [r4, #6]
	ldrh r0, [r6, #4]
	strh r0, [r4, #8]
	ldrh r0, [r6, #6]
	strh r0, [r4, #0xa]
	ldrb r0, [r5]
	strb r0, [r4, #0xd]
	ldrb r0, [r5, #2]
	strb r0, [r4, #0xe]
	add r0, r5, #0
	add r0, #0xe4
	ldrb r0, [r0]
	strb r0, [r4, #0x1a]
	add r0, r5, #0
	add r0, #0xd8
	ldrh r0, [r0]
	strh r0, [r4, #0x14]
	add r0, r5, #0
	add r0, #0xda
	ldrh r0, [r0]
	strh r0, [r4, #0x16]
	add r0, r5, #0
	add r0, #0xdc
	ldrh r0, [r0]
	strh r0, [r4, #0x18]
	ldrb r0, [r5, #3]
	strb r0, [r4, #0x10]
	ldr r0, _022363F0 ; =MOD12_022363F4
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022363EC: .word 0x00007530
_022363F0: .word MOD12_022363F4

	thumb_func_start MOD12_022363F4
MOD12_022363F4: ; 0x022363F4
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0xc]
	cmp r0, #8
	bhi _02236502
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223640E: ; jump table
	.short _02236420 - _0223640E - 2 ; case 0
	.short _0223645C - _0223640E - 2 ; case 1
	.short _0223646A - _0223640E - 2 ; case 2
	.short _02236472 - _0223640E - 2 ; case 3
	.short _02236496 - _0223640E - 2 ; case 4
	.short _022364AA - _0223640E - 2 ; case 5
	.short _022364B2 - _0223640E - 2 ; case 6
	.short _022364D6 - _0223640E - 2 ; case 7
	.short _022364E4 - _0223640E - 2 ; case 8
_02236420:
	ldrb r0, [r4, #0xd]
	ldr r1, [r4]
	lsl r0, r0, #1
	add r1, r1, r0
	ldr r0, _02236524 ; =0x00000242
	ldrsh r0, [r1, r0]
	bl MOD12_022352C8
	add r3, r0, #0
	cmp r3, #0
	ble _0223644A
	mov r1, #0
	add r0, r4, #0
	str r1, [sp]
	add r0, #0x12
	str r0, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	bl MOD12_022352F4
	b _02236452
_0223644A:
	mov r0, #2
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02236452:
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223645C:
	ldrb r1, [r4, #0x12]
	cmp r1, #1
	bne _02236520
	add r0, r0, #1
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223646A:
	add r0, r0, #1
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02236472:
	ldrb r1, [r4, #0x1a]
	cmp r1, #0
	beq _0223648E
	add r2, r4, #0
	ldr r0, [r4]
	add r2, #0x14
	mov r3, #0
	bl MOD12_02234FB0
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223648E:
	mov r0, #5
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02236496:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _02236520
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_022364AA:
	add r0, r0, #1
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_022364B2:
	ldr r0, [r4]
	ldrb r1, [r4, #0xe]
	ldrb r2, [r4, #0x10]
	add r0, #0xc
	bl MOD12_02233BE4
	add r3, r4, #0
	ldrb r1, [r4, #0xe]
	ldrb r2, [r4, #0x10]
	ldr r0, [r4]
	add r3, #0xf
	bl MOD12_02233C94
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_022364D6:
	ldrb r1, [r4, #0xf]
	cmp r1, #1
	bne _02236520
	add r0, r0, #1
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_022364E4:
	ldrb r0, [r4, #0x11]
	add r0, r0, #1
	strb r0, [r4, #0x11]
	ldrb r0, [r4, #0x11]
	cmp r0, #5
	bls _02236520
	ldr r0, [r4]
	add r0, #0xc
	bl MOD12_02233C74
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02236502:
	mov r0, #0xc3
	mov r2, #0
	ldr r1, [r4]
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02236520:
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02236524: .word 0x00000242

	thumb_func_start MOD12_02236528
MOD12_02236528: ; 0x02236528
	push {r3, lr}
	mov r0, #0xf4
	str r0, [sp]
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02236540
MOD12_02236540: ; 0x02236540
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	mov r1, #0x49
	mov r0, #0x15
	lsl r1, r1, #2
	add r6, r2, #0
	add r5, r3, #0
	bl AllocFromHeap
	mov r2, #0x49
	add r4, r0, #0
	mov r1, #0
	lsl r2, r2, #2
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r6]
	add r3, r4, #0
	add r3, #0x14
	strh r0, [r4, #4]
	ldrh r0, [r6, #2]
	strh r0, [r4, #6]
	ldrh r0, [r6, #4]
	strh r0, [r4, #8]
	ldrh r0, [r6, #6]
	strh r0, [r4, #0xa]
	ldrb r0, [r5]
	strb r0, [r4, #0xd]
	ldrb r1, [r5]
	mov r0, #0x2c
	add r2, r1, #0
	mul r2, r0
	add r1, r5, r2
	ldrh r1, [r1, #0x10]
	strh r1, [r4, #0xe]
	add r1, r5, #0
	add r1, #0xe4
	ldrb r2, [r1]
	add r1, r0, #0
	add r1, #0xe2
	strb r2, [r4, r1]
	add r1, r5, #0
	add r1, #0xd8
	ldrh r2, [r1]
	add r1, r0, #0
	add r1, #0xdc
	strh r2, [r4, r1]
	add r1, r5, #0
	add r1, #0xda
	ldrh r2, [r1]
	add r1, r0, #0
	add r1, #0xde
	strh r2, [r4, r1]
	add r1, r5, #0
	add r1, #0xdc
	ldrh r2, [r1]
	add r1, r0, #0
	add r1, #0xe0
	strh r2, [r4, r1]
	add r1, r5, #0
	add r1, #0xe5
	ldrb r2, [r1]
	add r1, r0, #0
	add r1, #0xea
	strb r2, [r4, r1]
	add r1, r5, #0
	add r1, #0xde
	ldrh r2, [r1]
	add r1, r0, #0
	add r1, #0xe4
	strh r2, [r4, r1]
	add r1, r5, #0
	add r1, #0xe0
	ldrh r2, [r1]
	add r1, r0, #0
	add r1, #0xe6
	strh r2, [r4, r1]
	add r1, r5, #0
	add r1, #0xe2
	ldrh r1, [r1]
	add r0, #0xe8
	mov r2, #0x1e
	strh r1, [r4, r0]
_022365E6:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _022365E6
	ldr r0, [r5]
	add r1, r4, #0
	str r0, [r3]
	ldr r0, _02236600 ; =MOD12_02236604
	mov r2, #5
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02236600: .word MOD12_02236604

	thumb_func_start MOD12_02236604
MOD12_02236604: ; 0x02236604
	push {r4, r5, r6, r7, lr}
	sub sp, #0x114
	add r4, r1, #0
	ldrb r1, [r4, #0xd]
	add r6, r0, #0
	add r2, r4, #0
	mov r5, #0x2c
	add r0, r1, #0
	add r2, #0x24
	mul r0, r5
	add r3, r2, r0
	ldrb r0, [r4, #0xc]
	cmp r0, #0xe
	bls _02236622
	b _02236A70
_02236622:
	add r2, r0, r0
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0223662E: ; jump table
	.short _0223664C - _0223662E - 2 ; case 0
	.short _02236674 - _0223662E - 2 ; case 1
	.short _02236688 - _0223662E - 2 ; case 2
	.short _02236690 - _0223662E - 2 ; case 3
	.short _022366B6 - _0223662E - 2 ; case 4
	.short _022366CA - _0223662E - 2 ; case 5
	.short _022366D2 - _0223662E - 2 ; case 6
	.short _022366FA - _0223662E - 2 ; case 7
	.short _02236710 - _0223662E - 2 ; case 8
	.short _02236718 - _0223662E - 2 ; case 9
	.short _0223672C - _0223662E - 2 ; case 10
	.short _022369D6 - _0223662E - 2 ; case 11
	.short _02236A2C - _0223662E - 2 ; case 12
	.short _02236A4C - _0223662E - 2 ; case 13
	.short _02236A62 - _0223662E - 2 ; case 14
_0223664C:
	add r0, r5, #0
	add r0, #0xe2
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _0223666C
	add r5, #0xdc
	ldr r0, [r4]
	add r2, r4, r5
	mov r3, #0
	bl MOD12_02234FB0
	ldrb r0, [r4, #0xc]
	add sp, #0x114
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_0223666C:
	mov r0, #2
	add sp, #0x114
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_02236674:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _02236704
	ldrb r0, [r4, #0xc]
	add sp, #0x114
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_02236688:
	add r0, r0, #1
	add sp, #0x114
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_02236690:
	ldrb r1, [r3, #0x12]
	cmp r1, #0
	beq _022366AE
	mov r0, #0
	str r0, [sp]
	ldrb r2, [r3, #0x13]
	ldr r0, [r4]
	add r3, #0xc
	bl MOD12_02234FF0
	ldrb r0, [r4, #0xc]
	add sp, #0x114
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_022366AE:
	mov r0, #5
	add sp, #0x114
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_022366B6:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _02236704
	ldrb r0, [r4, #0xc]
	add sp, #0x114
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_022366CA:
	add r0, r0, #1
	add sp, #0x114
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_022366D2:
	add r0, r5, #0
	add r0, #0xea
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _022366F2
	add r5, #0xdc
	ldr r0, [r4]
	add r2, r4, r5
	mov r3, #0
	bl MOD12_02234FB0
	ldrb r0, [r4, #0xc]
	add sp, #0x114
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_022366F2:
	mov r0, #8
	add sp, #0x114
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_022366FA:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	beq _02236706
_02236704:
	b _02236A8E
_02236706:
	ldrb r0, [r4, #0xc]
	add sp, #0x114
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_02236710:
	add r0, r0, #1
	add sp, #0x114
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_02236718:
	ldr r0, [r4]
	ldrh r2, [r4, #0xe]
	add r5, #0xec
	ldr r0, [r0]
	add r3, r4, r5
	bl MOD12_02235B1C
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_0223672C:
	ldrb r0, [r4, #0xd]
	add r5, r0, #1
	cmp r5, #4
	blt _02236736
	mov r5, #0
_02236736:
	add r0, sp, #0xbc
	mov r1, #0
	mov r2, #0x58
	bl MI_CpuFill8
	add r0, sp, #0x2c
	mov r1, #0
	mov r2, #0x90
	bl MI_CpuFill8
	ldr r0, [r4]
	mov r2, #0
	ldr r1, [r0, #0xc]
	ldrb r0, [r4, #0xd]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #5
	bl GetMonData
	add r6, r0, #0
	ldr r0, [r4]
	mov r2, #0
	ldr r1, [r0, #0xc]
	ldrb r0, [r4, #0xd]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0x6f
	bl GetMonData
	add r7, r0, #0
	ldr r0, [r4]
	ldr r1, [r0, #0xc]
	ldrb r0, [r4, #0xd]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MonIsShiny
	str r0, [sp, #0x20]
	ldr r0, [r4]
	mov r2, #0
	ldr r1, [r0, #0xc]
	ldrb r0, [r4, #0xd]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0x70
	bl GetMonData
	str r0, [sp, #0x1c]
	ldr r0, [r4]
	ldr r1, [r0, #0xc]
	ldrb r0, [r4, #0xd]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	add r2, r1, #0
	bl GetMonData
	str r0, [sp, #8]
	ldr r0, [r4]
	lsl r5, r5, #2
	ldr r0, [r0, #0xc]
	mov r1, #5
	ldr r0, [r0, r5]
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0x18]
	ldr r0, [r4]
	mov r1, #0x6f
	ldr r0, [r0, #0xc]
	mov r2, #0
	ldr r0, [r0, r5]
	bl GetMonData
	str r0, [sp, #0x14]
	ldr r0, [r4]
	ldr r0, [r0, #0xc]
	ldr r0, [r0, r5]
	bl MonIsShiny
	str r0, [sp, #0x10]
	ldr r0, [r4]
	mov r1, #0x70
	ldr r0, [r0, #0xc]
	mov r2, #0
	ldr r0, [r0, r5]
	bl GetMonData
	str r0, [sp, #0xc]
	ldr r0, [r4]
	mov r1, #0
	ldr r0, [r0, #0xc]
	add r2, r1, #0
	ldr r0, [r0, r5]
	bl GetMonData
	str r0, [sp, #4]
	mov r2, #0x47
	mov r0, #0
	add r1, sp, #0xbc
	strb r0, [r1]
	strb r0, [r1, #1]
	lsl r2, r2, #2
	ldrh r3, [r4, r2]
	mov r5, #1
	strh r3, [r1, #2]
	str r5, [sp, #0xc0]
	mov r3, #0xa
	strh r3, [r1, #8]
	add r3, r2, #3
	ldrb r3, [r4, r3]
	add r2, r2, #4
	strh r3, [r1, #0xa]
	ldrb r2, [r4, r2]
	strh r2, [r1, #0xc]
	str r0, [sp, #0xcc]
	strh r0, [r1, #0x14]
	strh r5, [r1, #0x16]
	mov r2, #9
	str r2, [sp, #0x110]
	lsl r2, r6, #0x10
	lsr r2, r2, #0x10
_0223682A:
	add r0, r0, #1
	strh r2, [r1, #0x18]
	add r1, r1, #2
	cmp r0, #4
	blt _0223682A
	ldr r0, [sp, #0x18]
	add r1, sp, #0xbc
	strh r0, [r1, #0x1a]
	ldr r0, [r4]
	mov r5, #0
	ldr r0, [r0, #0x30]
	str r0, [sp, #0x30]
	ldr r0, [r4]
	ldr r0, [r0, #0x5c]
	str r0, [sp, #0x34]
	ldrb r0, [r4, #0xd]
	ldr r1, [r4]
	add r1, #0x64
	lsl r0, r0, #4
	add r0, r1, r0
	str r0, [sp, #0x38]
	ldr r0, [r4]
	add r1, sp, #0x2c
	add r0, #0xa4
	str r0, [sp, #0x3c]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x28]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x20]
	add r2, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov ip, r0
	ldr r0, [sp, #0x1c]
	add r3, r1, #0
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
_0223687A:
	mov r0, #0xff
	strb r0, [r1, #0x1c]
	ldr r0, [sp, #0x28]
	add r6, r1, #0
	strh r0, [r2, #0x34]
	ldr r0, [sp, #0x24]
	add r6, #0x3c
	strb r0, [r6]
	add r6, r1, #0
	add r6, #0x40
	mov r0, ip
	strb r0, [r6]
	add r0, r1, #0
	add r0, #0x44
	strb r7, [r0]
	ldr r0, [sp, #8]
	add r5, r5, #1
	str r0, [r3, #0x48]
	mov r0, #0
	str r0, [r3, #0x58]
	add r1, r1, #1
	add r2, r2, #2
	add r3, r3, #4
	cmp r5, #4
	blt _0223687A
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r2, sp, #0x2c
	str r0, [sp, #0x84]
	mov r0, #0
	strb r0, [r2, #0x1c]
	mov r0, #1
	ldr r1, [sp, #0x18]
	strb r0, [r2, #0x1d]
	strh r1, [r2, #0x36]
	ldr r1, [sp, #0x14]
	add r2, sp, #0x4c
	strb r1, [r2, #0x1d]
	ldr r1, [sp, #0x10]
	add r2, sp, #0x6c
	strb r1, [r2, #1]
	ldr r1, [sp, #0xc]
	strb r1, [r2, #5]
	ldr r1, [sp, #4]
	str r1, [sp, #0x78]
	ldrb r1, [r4, #0xd]
	ldr r2, [r4]
	lsl r1, r1, #2
	add r1, r2, r1
	ldr r1, [r1, #0x14]
	str r1, [sp, #0x4c]
	ldrb r1, [r4, #0xd]
	cmp r1, #0
	beq _022368EA
	mov r0, #0
_022368EA:
	lsl r5, r0, #2
	ldr r0, [r4]
	mov r2, #0x57
	add r0, r0, r5
	ldr r0, [r0, #0x14]
	mov r1, #8
	str r1, [sp, #0x94]
	mov r1, #0x2d
	str r1, [sp, #0x98]
	mov r1, #1
	str r1, [sp, #0x9c]
	mov r1, #0x1d
	str r0, [sp, #0x50]
	mov r0, #0
	str r1, [sp, #0xa0]
	mov r1, #2
	str r0, [sp, #0x5c]
	str r0, [sp, #0xa8]
	mov r0, #3
	str r1, [sp, #0xa4]
	str r0, [sp, #0xac]
	ldr r0, [r4]
	lsl r2, r2, #2
	ldr r0, [r0, #0x24]
	add r3, sp, #0x2c
	str r0, [sp, #0x2c]
	ldr r0, [r4]
	ldr r1, [r0]
	ldrb r0, [r4, #0xd]
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, r2]
	sub r2, #0x40
	str r0, [sp, #0xb0]
	ldr r0, [r4]
	ldrh r2, [r4, r2]
	ldr r0, [r0, #0x2c]
	add r1, sp, #0xbc
	bl MOD08_02212048
	ldr r0, [r4]
	ldr r1, [r0, #0xc]
	ldrb r0, [r4, #0xd]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_02068E14
	add r6, r0, #0
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	ldr r0, _02236A94 ; =0xDFFBFF3F
	cmp r1, r0
	beq _0223696A
	ldrb r0, [r4, #0xd]
	ldr r1, [r4]
	mov r2, #0
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #0x14]
	mov r1, #6
	bl FUN_02007558
_0223696A:
	ldrb r0, [r4, #0xd]
	ldr r1, [r4]
	mov r2, #0
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #0x14]
	mov r1, #0x25
	bl FUN_02007558
	ldrb r0, [r4, #0xd]
	ldr r1, [r4]
	mov r2, #0xd8
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #0x14]
	mov r1, #0
	bl FUN_02007558
	ldrb r0, [r4, #0xd]
	add r6, #0x70
	ldr r1, [r4]
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #0x14]
	mov r1, #1
	add r2, r6, #0
	bl FUN_02007558
	ldr r0, [r4]
	mov r1, #0x25
	add r0, r0, r5
	ldr r0, [r0, #0x14]
	mov r2, #1
	bl FUN_02007558
	ldr r0, [r4]
	mov r1, #0
	add r0, r0, r5
	ldr r0, [r0, #0x14]
	mov r2, #0x50
	bl FUN_02007558
	ldr r0, [r4]
	mov r1, #1
	add r0, r0, r5
	ldr r0, [r0, #0x14]
	mov r2, #0x2a
	bl FUN_02007558
	ldrb r0, [r4, #0xc]
	add sp, #0x114
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_022369D6:
	ldr r0, [r4]
	ldr r0, [r0, #0x2c]
	bl MOD08_02212384
	ldr r0, [r4]
	ldr r0, [r0, #0x2c]
	bl MOD08_022123A0
	cmp r0, #0
	bne _02236A8E
	ldr r0, [r4]
	ldr r0, [r0, #0x2c]
	bl MOD08_022123B0
	add r1, r5, #0
	add r1, #0xf2
	ldrb r0, [r4, r1]
	cmp r0, #0
	beq _02236A22
	sub r0, r0, #1
	strb r0, [r4, r1]
	add r0, r1, #1
	ldrb r0, [r4, r0]
	add r2, r0, #1
	add r0, r1, #1
	strb r2, [r4, r0]
	sub r0, r1, #6
	ldr r2, [r4, r0]
	ldr r0, _02236A98 ; =0x200400C0
	cmp r2, r0
	bne _02236A1A
	ldr r2, _02236A94 ; =0xDFFBFF3F
	sub r0, r1, #6
	str r2, [r4, r0]
_02236A1A:
	mov r0, #0xa
	add sp, #0x114
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_02236A22:
	ldrb r0, [r4, #0xc]
	add sp, #0x114
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_02236A2C:
	add r5, #0xf0
	ldrh r0, [r4, r5]
	cmp r0, #0x90
	beq _02236A38
	cmp r0, #0xa4
	bne _02236A42
_02236A38:
	ldr r0, [r4]
	mov r2, #1
	add r1, r0, r1
	ldr r0, _02236A9C ; =0x00001652
	strb r2, [r1, r0]
_02236A42:
	ldrb r0, [r4, #0xc]
	add sp, #0x114
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_02236A4C:
	add r2, r4, #0
	ldr r0, [r4]
	mov r1, #1
	add r2, #0x10
	bl MOD12_0223483C
	ldrb r0, [r4, #0xc]
	add sp, #0x114
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_02236A62:
	ldrb r1, [r4, #0x10]
	cmp r1, #1
	bne _02236A8E
	add r0, r0, #1
	add sp, #0x114
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, r7, pc}
_02236A70:
	mov r0, #0xc3
	mov r2, #0
	ldr r1, [r4]
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r6, #0
	bl FUN_0200CAB4
_02236A8E:
	add sp, #0x114
	pop {r4, r5, r6, r7, pc}
	nop
_02236A94: .word 0xDFFBFF3F
_02236A98: .word 0x200400C0
_02236A9C: .word 0x00001652

	thumb_func_start MOD12_02236AA0
MOD12_02236AA0: ; 0x02236AA0
	push {r3, lr}
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	mov r3, #0
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02236AB8
MOD12_02236AB8: ; 0x02236AB8
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r0, #0x15
	mov r1, #0x14
	add r5, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x14
	bl MI_CpuFill8
	str r6, [r4]
	ldrh r0, [r5]
	mov r2, #0x64
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r1, [r6, #0xc]
	ldr r0, _02236AF8 ; =0x00000123
	ldrb r0, [r1, r0]
	add r1, r4, #0
	strb r0, [r4, #0xd]
	ldr r0, _02236AFC ; =MOD12_02236B00
	bl FUN_0200CA44
	pop {r4, r5, r6, pc}
	nop
_02236AF8: .word 0x00000123
_02236AFC: .word MOD12_02236B00

	thumb_func_start MOD12_02236B00
MOD12_02236B00: ; 0x02236B00
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0xc]
	cmp r0, #0xa
	bls _02236B10
	b _02236C9E
_02236B10:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02236B1C: ; jump table
	.short _02236B32 - _02236B1C - 2 ; case 0
	.short _02236B4C - _02236B1C - 2 ; case 1
	.short _02236BAA - _02236B1C - 2 ; case 2
	.short _02236BBA - _02236B1C - 2 ; case 3
	.short _02236BF4 - _02236B1C - 2 ; case 4
	.short _02236C08 - _02236B1C - 2 ; case 5
	.short _02236C0E - _02236B1C - 2 ; case 6
	.short _02236C42 - _02236B1C - 2 ; case 7
	.short _02236C52 - _02236B1C - 2 ; case 8
	.short _02236C76 - _02236B1C - 2 ; case 9
	.short _02236C98 - _02236B1C - 2 ; case 10
_02236B32:
	ldr r1, [r4]
	ldr r0, _02236CE8 ; =0x0000081C
	mov r2, #0
	ldr r0, [r1, r0]
	mov r1, #1
	add r3, r2, #0
	bl MOD12_02231B4C
	ldrb r0, [r4, #0xc]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, pc}
_02236B4C:
	ldr r1, [r4]
	ldr r0, _02236CE8 ; =0x0000081C
	mov r2, #0
	ldr r0, [r1, r0]
	mov r1, #2
	add r3, r2, #0
	bl MOD12_02231B4C
	mov r0, #0x23
	ldr r1, [r4]
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	add r2, r0, #1
	cmp r2, #4
	bne _02236B6E
	mov r1, #3
	b _02236B70
_02236B6E:
	mov r1, #2
_02236B70:
	add r0, sp, #0
	strb r2, [r0, #0xa]
	add r2, sp, #4
	ldr r0, [r4]
	add r2, #2
	mov r3, #0
	bl MOD12_02234FB0
	mov r0, #0x23
	ldr r1, [r4]
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	add r0, r0, #1
	cmp r0, #4
	bne _02236BA0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _02236BA0
	ldr r0, _02236CEC ; =0x000006F6
	bl FUN_020054C8
	ldrb r0, [r4, #0xe]
	add r0, r0, #1
	strb r0, [r4, #0xe]
_02236BA0:
	ldrb r0, [r4, #0xc]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, pc}
_02236BAA:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _02236BCE
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02236BBA:
	ldr r1, [r4]
	ldr r0, _02236CE8 ; =0x0000081C
	ldr r0, [r1, r0]
	bl MOD12_02231C80
	add r1, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	bne _02236BD0
_02236BCE:
	b _02236CE4
_02236BD0:
	ldr r0, [r4]
	add r1, #0x36
	ldr r2, [r0, #0xc]
	ldrb r0, [r4, #0xd]
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	mov r2, #0
	bl GetMonData
	strh r0, [r4, #0x10]
	ldr r0, _02236CF0 ; =0x000005DD
	bl FUN_020054C8
	ldrb r0, [r4, #0xc]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, pc}
_02236BF4:
	ldr r1, [r4]
	ldr r0, _02236CE8 ; =0x0000081C
	ldr r0, [r1, r0]
	bl MOD12_02231D48
	cmp r0, #0
	beq _02236CE4
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02236C08:
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02236C0E:
	ldr r1, [r4]
	ldr r0, _02236CE8 ; =0x0000081C
	mov r2, #0
	ldr r0, [r1, r0]
	mov r1, #3
	add r3, r2, #0
	bl MOD12_02231B4C
	mov r0, #0x23
	ldr r1, [r4]
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	add r2, sp, #0
	mov r3, #0
	add r1, r0, #1
	add r0, sp, #0
	strb r1, [r0, #4]
	ldr r0, [r4]
	mov r1, #1
	bl MOD12_02234FB0
	ldrb r0, [r4, #0xc]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, pc}
_02236C42:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _02236CE4
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02236C52:
	ldr r1, [r4]
	ldr r0, _02236CE8 ; =0x0000081C
	ldr r0, [r1, r0]
	bl MOD12_02231C80
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _02236CE4
	strh r0, [r4, #0x12]
	ldr r0, _02236CF0 ; =0x000005DD
	bl FUN_020054C8
	ldrb r0, [r4, #0xc]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, pc}
_02236C76:
	ldr r1, [r4]
	ldr r0, _02236CE8 ; =0x0000081C
	ldr r0, [r1, r0]
	bl MOD12_02231D48
	cmp r0, #0
	beq _02236CE4
	ldrh r0, [r4, #0x12]
	cmp r0, #3
	bne _02236C92
	mov r0, #1
	add sp, #0xc
	strb r0, [r4, #0xc]
	pop {r4, r5, pc}
_02236C92:
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02236C98:
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02236C9E:
	ldr r0, [r4]
	ldr r1, _02236CF4 ; =0x00000171
	ldr r2, [r0]
	ldrb r1, [r2, r1]
	cmp r1, #1
	bne _02236CB4
	mov r2, #0
	mov r1, #0x2e
	add r3, r2, #0
	bl MOD12_02234FB0
_02236CB4:
	mov r0, #0xc3
	add r2, r4, #0
	ldr r1, [r4]
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r4, #4
	add r2, #0x10
	mov r3, #4
	bl MOD12_02240FB0
	ldr r1, [r4]
	ldr r0, _02236CE8 ; =0x0000081C
	ldr r0, [r1, r0]
	mov r1, #0
	add r2, r1, #0
	add r3, r1, #0
	bl MOD12_02231B4C
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02236CE4:
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02236CE8: .word 0x0000081C
_02236CEC: .word 0x000006F6
_02236CF0: .word 0x000005DD
_02236CF4: .word 0x00000171

	thumb_func_start MOD12_02236CF8
MOD12_02236CF8: ; 0x02236CF8
	push {r4, r5}
	ldr r0, [sp, #8]
	lsl r2, r0, #2
	ldr r5, [r3, r2]
	lsl r2, r0, #1
	ldrh r4, [r5]
	add r3, r1, r2
	ldr r2, _02236D18 ; =0x00000236
	add r0, r1, r0
	strh r4, [r3, r2]
	ldrh r3, [r5, #2]
	add r2, #8
	strb r3, [r0, r2]
	pop {r4, r5}
	bx lr
	nop
_02236D18: .word 0x00000236

	thumb_func_start MOD12_02236D1C
MOD12_02236D1C: ; 0x02236D1C
	push {r3, lr}
	mov r0, #0xf4
	str r0, [sp]
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02236D34
MOD12_02236D34: ; 0x02236D34
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02236D38
MOD12_02236D38: ; 0x02236D38
	push {r3, lr}
	mov r0, #0xf4
	str r0, [sp]
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02236D50
MOD12_02236D50: ; 0x02236D50
	push {r3, r4, r5, r6, r7, lr}
	mov r0, #0x15
	add r7, r1, #0
	add r1, r0, #0
	add r1, #0xff
	add r6, r2, #0
	add r5, r3, #0
	bl AllocFromHeap
	mov r2, #0x45
	add r4, r0, #0
	mov r1, #0
	lsl r2, r2, #2
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r6]
	add r3, r4, #0
	add r3, #0x14
	strh r0, [r4, #4]
	ldrh r0, [r6, #2]
	mov r2, #0x1e
	strh r0, [r4, #6]
	ldrh r0, [r6, #4]
	strh r0, [r4, #8]
	ldrh r0, [r6, #6]
	strh r0, [r4, #0xa]
	ldrb r0, [r5]
	strb r0, [r4, #0xd]
	ldrb r0, [r5, #1]
	strb r0, [r4, #0xe]
_02236D8E:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02236D8E
	ldr r0, [r5]
	ldr r2, _02236DA8 ; =0x00007530
	str r0, [r3]
	ldr r0, _02236DAC ; =MOD12_02236DB0
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02236DA8: .word 0x00007530
_02236DAC: .word MOD12_02236DB0

	thumb_func_start MOD12_02236DB0
MOD12_02236DB0: ; 0x02236DB0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4, #0xd]
	add r5, r0, #0
	add r3, r4, #0
	add r2, r1, #0
	mov r0, #0x2c
	ldrb r1, [r4, #0xc]
	add r3, #0x24
	mul r2, r0
	add r2, r3, r2
	cmp r1, #4
	bhi _02236E48
	add r3, r1, r1
	add r3, pc
	ldrh r3, [r3, #6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_02236DD6: ; jump table
	.short _02236DE0 - _02236DD6 - 2 ; case 0
	.short _02236DF0 - _02236DD6 - 2 ; case 1
	.short _02236DF6 - _02236DD6 - 2 ; case 2
	.short _02236E2E - _02236DD6 - 2 ; case 3
	.short _02236E48 - _02236DD6 - 2 ; case 4
_02236DE0:
	mov r0, #0x1a
	ldrsh r1, [r2, r0]
	add r0, #0xee
	strh r1, [r4, r0]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02236DF0:
	add r0, r1, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02236DF6:
	add r0, #0xdc
	mov r3, #0x18
	ldrsh r1, [r4, r0]
	ldrsh r0, [r2, r3]
	cmp r1, r0
	bge _02236E28
	add r0, r3, #0
	add r0, #0xf0
	ldrsh r1, [r4, r0]
	add r0, r3, #0
	add r0, #0xf0
	add r1, #0xa
	strh r1, [r4, r0]
	add r3, #0xf0
	ldr r0, [r4]
	ldrb r1, [r4, #0xd]
	ldrb r2, [r4, #0xe]
	ldrsh r3, [r4, r3]
	add r0, #0xc
	bl MOD12_02234088
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02236E28:
	mov r0, #4
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02236E2E:
	mov r0, #0xf
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #0xf]
	ldrsb r0, [r4, r0]
	cmp r0, #2
	ble _02236E66
	mov r0, #0
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xc]
	sub r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02236E48:
	mov r0, #0xc3
	mov r2, #0
	ldr r1, [r4]
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02236E66:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_02236E68
MOD12_02236E68: ; 0x02236E68
	push {r3, lr}
	mov r0, #0xf4
	str r0, [sp]
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02236E80
MOD12_02236E80: ; 0x02236E80
	push {r3, r4, r5, r6, r7, lr}
	mov r0, #0x15
	add r7, r1, #0
	add r1, r0, #0
	add r1, #0xff
	add r6, r2, #0
	add r5, r3, #0
	bl AllocFromHeap
	mov r2, #0x45
	add r4, r0, #0
	mov r1, #0
	lsl r2, r2, #2
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r6]
	add r3, r4, #0
	add r3, #0x14
	strh r0, [r4, #4]
	ldrh r0, [r6, #2]
	mov r2, #0x1e
	strh r0, [r4, #6]
	ldrh r0, [r6, #4]
	strh r0, [r4, #8]
	ldrh r0, [r6, #6]
	strh r0, [r4, #0xa]
	ldrb r0, [r5]
	strb r0, [r4, #0xd]
	ldrb r0, [r5, #1]
	strb r0, [r4, #0xe]
_02236EBE:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02236EBE
	ldr r0, [r5]
	ldr r2, _02236ED8 ; =0x00007530
	str r0, [r3]
	ldr r0, _02236EDC ; =MOD12_02236EE0
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02236ED8: .word 0x00007530
_02236EDC: .word MOD12_02236EE0

	thumb_func_start MOD12_02236EE0
MOD12_02236EE0: ; 0x02236EE0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	ldrb r1, [r4, #0xd]
	str r0, [sp, #4]
	add r2, r4, #0
	mov r0, #0x2c
	add r2, #0x24
	mul r0, r1
	add r3, r2, r0
	ldrb r0, [r4, #0xc]
	cmp r0, #0x10
	bls _02236EFC
	b _022370D4
_02236EFC:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02236F08: ; jump table
	.short _02236F2A - _02236F08 - 2 ; case 0
	.short _02236F3C - _02236F08 - 2 ; case 1
	.short _02236F62 - _02236F08 - 2 ; case 2
	.short _02236F76 - _02236F08 - 2 ; case 3
	.short _02236F7A - _02236F08 - 2 ; case 4
	.short _02236F80 - _02236F08 - 2 ; case 5
	.short _02236FB2 - _02236F08 - 2 ; case 6
	.short _02236FD0 - _02236F08 - 2 ; case 7
	.short _02236FD4 - _02236F08 - 2 ; case 8
	.short _02237000 - _02236F08 - 2 ; case 9
	.short _02237052 - _02236F08 - 2 ; case 10
	.short _0223706E - _02236F08 - 2 ; case 11
	.short _02237072 - _02236F08 - 2 ; case 12
	.short _02237078 - _02236F08 - 2 ; case 13
	.short _022370C8 - _02236F08 - 2 ; case 14
	.short _022370CE - _02236F08 - 2 ; case 15
	.short _022370D4 - _02236F08 - 2 ; case 16
_02236F2A:
	mov r0, #0x1a
	ldrsh r1, [r3, r0]
	add r0, #0xee
	add sp, #8
	strh r1, [r4, r0]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02236F3C:
	ldrb r1, [r3, #0x12]
	cmp r1, #0
	beq _02236F5A
	mov r0, #0
	str r0, [sp]
	ldrb r2, [r3, #0x13]
	ldr r0, [r4]
	add r3, #0xc
	bl MOD12_02234FF0
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02236F5A:
	mov r0, #3
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02236F62:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _02236FC0
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02236F76:
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02236F7A:
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02236F80:
	mov r5, #0x42
	lsl r5, r5, #2
	mov r0, #0x18
	ldrsh r1, [r4, r5]
	ldrsh r0, [r3, r0]
	cmp r1, r0
	bge _02236FAA
	add r1, #0xa
	strh r1, [r4, r5]
	ldr r0, [r4]
	ldrb r1, [r4, #0xd]
	ldrb r2, [r4, #0xe]
	ldrsh r3, [r4, r5]
	add r0, #0xc
	bl MOD12_02234088
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02236FAA:
	mov r0, #7
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02236FB2:
	mov r0, #0xf
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #0xf]
	ldrsb r0, [r4, r0]
	cmp r0, #2
	bgt _02236FC2
_02236FC0:
	b _022370F2
_02236FC2:
	mov r0, #0
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xc]
	add sp, #8
	sub r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02236FD0:
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02236FD4:
	ldr r0, [r3, #0x28]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _02236FF8
	ldrb r0, [r3, #3]
	add sp, #8
	add r1, r4, r0
	mov r0, #0xe4
	ldrsb r1, [r1, r0]
	add r0, #0x26
	strh r1, [r4, r0]
	mov r0, #0
	strb r0, [r4, #0x10]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02236FF8:
	mov r0, #0xb
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02237000:
	mov r0, #0x10
	ldrsb r0, [r4, r0]
	mov r6, #0
	add r5, r6, #0
	add r0, r0, #1
	strb r0, [r4, #0x10]
	mov r7, #0xe7
_0223700E:
	mov r2, #0x10
	ldrsb r3, [r4, r2]
	add r1, r4, r5
	mov r0, #0xe4
	mov r2, #0xa
	ldrsb r0, [r1, r0]
	mul r2, r3
	sub r2, r0, r2
	ldrsb r0, [r1, r7]
	cmp r0, r2
	bgt _02237036
	ldr r0, [r4]
	add r1, r5, #0
	add r0, #0xc
	add r6, r6, #1
	bl MOD12_02234628
	ldr r0, _022370F8 ; =0x000006DF
	bl FUN_020054C8
_02237036:
	add r5, r5, #1
	cmp r5, #3
	blt _0223700E
	cmp r6, #0
	ble _0223704A
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223704A:
	mov r0, #0xb
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02237052:
	mov r0, #0xf
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #0xf]
	ldrsb r0, [r4, r0]
	cmp r0, #2
	ble _022370F2
	mov r0, #0
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xc]
	add sp, #8
	sub r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223706E:
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02237072:
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02237078:
	add r6, r4, #0
	mov r5, #0
	add r6, #0x4c
_0223707E:
	ldr r2, [r4]
	ldr r0, _022370FC ; =0x00000231
	add r1, r2, r5
	ldrb r1, [r1, r0]
	mov r0, #0x2c
	add r7, r1, #0
	mul r7, r0
	ldr r0, [r6, r7]
	lsl r1, r0, #0x1a
	lsl r3, r0, #0x16
	lsr r1, r1, #0x1e
	lsr r3, r3, #0x1e
	cmp r1, r3
	bne _022370A6
	lsl r1, r0, #0x18
	lsl r0, r0, #0x14
	lsr r1, r1, #0x1e
	lsr r0, r0, #0x1e
	cmp r1, r0
	beq _022370BC
_022370A6:
	add r2, #0xc
	add r0, r2, #0
	ldr r2, [r6, r7]
	add r1, r5, #0
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1e
	bl MOD12_02235200
	ldr r0, _02237100 ; =0x000006E2
	bl FUN_020054C8
_022370BC:
	add r5, r5, #1
	cmp r5, #4
	blt _0223707E
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_022370C8:
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_022370CE:
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_022370D4:
	mov r0, #0xc3
	mov r2, #0
	ldr r1, [r4]
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [sp, #4]
	bl FUN_0200CAB4
_022370F2:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022370F8: .word 0x000006DF
_022370FC: .word 0x00000231
_02237100: .word 0x000006E2

	thumb_func_start MOD12_02237104
MOD12_02237104: ; 0x02237104
	push {r3, lr}
	mov r0, #0xf4
	str r0, [sp]
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_0223711C
MOD12_0223711C: ; 0x0223711C
	push {r3, r4, r5, r6, r7, lr}
	mov r0, #0x15
	add r7, r1, #0
	add r1, r0, #0
	add r1, #0xff
	add r6, r2, #0
	add r5, r3, #0
	bl AllocFromHeap
	mov r2, #0x45
	add r4, r0, #0
	mov r1, #0
	lsl r2, r2, #2
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r6]
	add r3, r4, #0
	add r3, #0x14
	strh r0, [r4, #4]
	ldrh r0, [r6, #2]
	mov r2, #0x1e
	strh r0, [r4, #6]
	ldrh r0, [r6, #4]
	strh r0, [r4, #8]
	ldrh r0, [r6, #6]
	strh r0, [r4, #0xa]
	ldrb r0, [r5]
	strb r0, [r4, #0xd]
	ldrb r0, [r5, #1]
	strb r0, [r4, #0xe]
_0223715A:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0223715A
	ldr r0, [r5]
	ldr r2, _02237174 ; =0x00007530
	str r0, [r3]
	ldr r0, _02237178 ; =MOD12_0223717C
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02237174: .word 0x00007530
_02237178: .word MOD12_0223717C

	thumb_func_start MOD12_0223717C
MOD12_0223717C: ; 0x0223717C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4, #0xd]
	add r5, r0, #0
	add r2, r4, #0
	mov r0, #0x2c
	add r2, #0x24
	mul r0, r1
	add r3, r2, r0
	ldrb r0, [r4, #0xc]
	cmp r0, #8
	bhi _0223724C
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022371A0: ; jump table
	.short _022371B2 - _022371A0 - 2 ; case 0
	.short _022371C2 - _022371A0 - 2 ; case 1
	.short _022371E4 - _022371A0 - 2 ; case 2
	.short _022371F6 - _022371A0 - 2 ; case 3
	.short _022371FA - _022371A0 - 2 ; case 4
	.short _02237200 - _022371A0 - 2 ; case 5
	.short _0223722E - _022371A0 - 2 ; case 6
	.short _02237248 - _022371A0 - 2 ; case 7
	.short _0223724C - _022371A0 - 2 ; case 8
_022371B2:
	mov r0, #0x1a
	ldrsh r1, [r3, r0]
	add r0, #0xee
	strh r1, [r4, r0]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_022371C2:
	ldrb r1, [r3, #0x12]
	cmp r1, #0
	beq _022371DE
	mov r0, #0
	str r0, [sp]
	ldrb r2, [r3, #0x13]
	ldr r0, [r4]
	add r3, #0xc
	bl MOD12_02234FF0
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_022371DE:
	mov r0, #3
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_022371E4:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _0223726A
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_022371F6:
	add r0, r0, #1
	strb r0, [r4, #0xc]
_022371FA:
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02237200:
	mov r5, #0x42
	lsl r5, r5, #2
	mov r0, #0x18
	ldrsh r1, [r4, r5]
	ldrsh r0, [r3, r0]
	cmp r1, r0
	bge _02237228
	add r1, #0xa
	strh r1, [r4, r5]
	ldr r0, [r4]
	ldrb r1, [r4, #0xd]
	ldrb r2, [r4, #0xe]
	ldrsh r3, [r4, r5]
	add r0, #0xc
	bl MOD12_02234088
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237228:
	mov r0, #7
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223722E:
	mov r0, #0xf
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #0xf]
	ldrsb r0, [r4, r0]
	cmp r0, #2
	ble _0223726A
	mov r0, #0
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xc]
	sub r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237248:
	add r0, r0, #1
	strb r0, [r4, #0xc]
_0223724C:
	mov r0, #0xc3
	mov r2, #0
	ldr r1, [r4]
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_0223726A:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_0223726C
MOD12_0223726C: ; 0x0223726C
	push {r3, lr}
	mov r0, #0xf4
	str r0, [sp]
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02237284
MOD12_02237284: ; 0x02237284
	push {r3, r4, r5, r6, r7, lr}
	mov r0, #0x15
	add r7, r1, #0
	add r1, r0, #0
	add r1, #0xff
	add r6, r2, #0
	add r5, r3, #0
	bl AllocFromHeap
	mov r2, #0x45
	add r4, r0, #0
	mov r1, #0
	lsl r2, r2, #2
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r6]
	add r3, r4, #0
	add r3, #0x14
	strh r0, [r4, #4]
	ldrh r0, [r6, #2]
	mov r2, #0x1e
	strh r0, [r4, #6]
	ldrh r0, [r6, #4]
	strh r0, [r4, #8]
	ldrh r0, [r6, #6]
	strh r0, [r4, #0xa]
	ldrb r0, [r5]
	strb r0, [r4, #0xd]
	ldrb r0, [r5, #1]
	strb r0, [r4, #0xe]
_022372C2:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _022372C2
	ldr r0, [r5]
	ldr r2, _022372DC ; =0x00007530
	str r0, [r3]
	ldr r0, _022372E0 ; =MOD12_022372E4
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022372DC: .word 0x00007530
_022372E0: .word MOD12_022372E4

	thumb_func_start MOD12_022372E4
MOD12_022372E4: ; 0x022372E4
	push {r4, r5, r6, lr}
	sub sp, #8
	add r4, r1, #0
	ldrb r1, [r4, #0xd]
	add r6, r0, #0
	add r3, r4, #0
	add r2, r1, #0
	mov r0, #0x2c
	ldrb r1, [r4, #0xc]
	add r3, #0x24
	mul r2, r0
	add r5, r3, r2
	cmp r1, #0x19
	bls _02237302
	b _02237624
_02237302:
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0223730E: ; jump table
	.short _02237342 - _0223730E - 2 ; case 0
	.short _02237358 - _0223730E - 2 ; case 1
	.short _0223739C - _0223730E - 2 ; case 2
	.short _022373AC - _0223730E - 2 ; case 3
	.short _022373B0 - _0223730E - 2 ; case 4
	.short _022373D8 - _0223730E - 2 ; case 5
	.short _022373EC - _0223730E - 2 ; case 6
	.short _022373F0 - _0223730E - 2 ; case 7
	.short _02237424 - _0223730E - 2 ; case 8
	.short _02237442 - _0223730E - 2 ; case 9
	.short _02237446 - _0223730E - 2 ; case 10
	.short _0223744C - _0223730E - 2 ; case 11
	.short _022374B8 - _0223730E - 2 ; case 12
	.short _022374D0 - _0223730E - 2 ; case 13
	.short _022374EA - _0223730E - 2 ; case 14
	.short _0223750A - _0223730E - 2 ; case 15
	.short _02237532 - _0223730E - 2 ; case 16
	.short _02237548 - _0223730E - 2 ; case 17
	.short _0223754C - _0223730E - 2 ; case 18
	.short _02237578 - _0223730E - 2 ; case 19
	.short _02237586 - _0223730E - 2 ; case 20
	.short _0223758A - _0223730E - 2 ; case 21
	.short _0223759C - _0223730E - 2 ; case 22
	.short _022375E0 - _0223730E - 2 ; case 23
	.short _022375FC - _0223730E - 2 ; case 24
	.short _02237624 - _0223730E - 2 ; case 25
_02237342:
	ldrb r0, [r5, #3]
	add sp, #8
	add r1, r4, r0
	mov r0, #0xe4
	ldrsb r1, [r1, r0]
	add r0, #0x26
	strh r1, [r4, r0]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_02237358:
	ldrb r1, [r5, #3]
	mov r0, #0xe7
	add r3, r4, r1
	ldrsb r2, [r3, r0]
	mov r0, #0xe4
	ldrsb r0, [r3, r0]
	cmp r2, r0
	ble _02237394
	cmp r2, #0x32
	blt _02237370
	mov r6, #3
	b _02237372
_02237370:
	mov r6, #2
_02237372:
	ldr r0, [r4]
	add r2, r6, #0
	add r0, #0xc
	bl MOD12_02233BE4
	ldr r3, _0223764C ; =0x0000010E
	ldrb r1, [r5, #3]
	ldr r0, [r4]
	add r2, r6, #0
	add r3, r4, r3
	bl MOD12_02233C94
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_02237394:
	mov r0, #3
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_0223739C:
	add r0, #0xe2
	ldrb r0, [r4, r0]
	cmp r0, #1
	bne _02237432
	add r0, r1, #1
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_022373AC:
	add r0, r1, #1
	strb r0, [r4, #0xc]
_022373B0:
	add r0, r4, #0
	add r0, #0xf8
	ldrb r1, [r0]
	cmp r1, #0
	beq _022373D0
	add r2, r4, #0
	ldr r0, [r4]
	add r2, #0xec
	mov r3, #0
	bl MOD12_02234FB0
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_022373D0:
	mov r0, #6
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_022373D8:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _02237432
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_022373EC:
	add r0, r1, #1
	strb r0, [r4, #0xc]
_022373F0:
	ldrb r0, [r5, #3]
	add r2, r4, r0
	mov r0, #0xe7
	ldrsb r1, [r2, r0]
	mov r0, #0xe4
	ldrsb r0, [r2, r0]
	cmp r1, r0
	ble _02237416
	mov r0, #1
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x11
	str r0, [sp, #4]
	ldr r0, [r4]
	mov r2, #0
	mov r3, #0x46
	bl MOD12_022352F4
	b _0223741A
_02237416:
	mov r0, #1
	strb r0, [r4, #0x11]
_0223741A:
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_02237424:
	mov r0, #0xf
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #0xf]
	ldrsb r0, [r4, r0]
	cmp r0, #8
	bgt _02237434
_02237432:
	b _02237648
_02237434:
	mov r0, #0
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_02237442:
	add r0, r1, #1
	strb r0, [r4, #0xc]
_02237446:
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_0223744C:
	ldrb r0, [r5, #3]
	add r3, r4, r0
	mov r0, #0xe7
	ldrsb r1, [r3, r0]
	add r0, #0x23
	ldrsh r0, [r4, r0]
	cmp r0, r1
	beq _022374B0
	mov r2, #0xe4
	ldrsb r0, [r3, r2]
	sub r0, r1, r0
	cmp r0, #0
	ble _02237484
	add r0, r2, #0
	add r0, #0x26
	ldrsh r1, [r4, r0]
	add r0, r2, #0
	add r0, #0x26
	add r1, #0xa
	strh r1, [r4, r0]
	add r2, #0x26
	ldr r0, [r4]
	ldrb r1, [r5, #3]
	ldrsh r2, [r4, r2]
	add r0, #0xc
	bl MOD12_02234628
	b _022374A6
_02237484:
	add r0, r2, #0
	add r0, #0x26
	ldrsh r1, [r4, r0]
	add r0, r2, #0
	add r0, #0x26
	sub r1, #0xa
	strh r1, [r4, r0]
	add r2, #0x26
	ldr r0, [r4]
	ldrb r1, [r5, #3]
	ldrsh r2, [r4, r2]
	add r0, #0xc
	bl MOD12_02234628
	ldr r0, _02237650 ; =0x000006DF
	bl FUN_020054C8
_022374A6:
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_022374B0:
	mov r0, #0xe
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_022374B8:
	ldr r0, [r4]
	ldrb r1, [r5, #3]
	add r0, #0xc
	bl MOD12_022345FC
	cmp r0, #1
	bne _0223753C
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_022374D0:
	mov r0, #0xf
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #0xf]
	ldrsb r0, [r4, r0]
	cmp r0, #2
	ble _0223753C
	mov r0, #0
	strb r0, [r4, #0xf]
	mov r0, #0xb
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_022374EA:
	add r0, #0xde
	ldrsh r0, [r4, r0]
	cmp r0, #0x32
	blt _02237500
	ldrb r1, [r5, #3]
	ldr r0, [r4]
	bl MOD12_022357B0
	mov r1, #0x11
	lsl r1, r1, #4
	str r0, [r4, r1]
_02237500:
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_0223750A:
	add r0, r4, #0
	add r0, #0xf9
	ldrb r1, [r0]
	cmp r1, #0
	beq _0223752A
	add r2, r4, #0
	ldr r0, [r4]
	add r2, #0xf2
	mov r3, #0
	bl MOD12_02234FB0
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_0223752A:
	mov r0, #0x11
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_02237532:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	beq _0223753E
_0223753C:
	b _02237648
_0223753E:
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_02237548:
	add r0, r1, #1
	strb r0, [r4, #0xc]
_0223754C:
	ldr r0, _02237654 ; =0x0000010A
	ldrsh r0, [r4, r0]
	cmp r0, #0x32
	blt _02237570
	add r0, r4, #0
	add r0, #0x12
	str r0, [sp]
	ldrb r1, [r4, #0xd]
	ldrb r2, [r4, #0xe]
	ldrb r3, [r5, #3]
	ldr r0, [r4]
	bl MOD12_02235824
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_02237570:
	mov r0, #0x14
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_02237578:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _02237648
	add r0, r1, #1
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_02237586:
	add r0, r1, #1
	strb r0, [r4, #0xc]
_0223758A:
	mov r0, #0x1a
	ldrsh r1, [r5, r0]
	add r0, #0xee
	add sp, #8
	strh r1, [r4, r0]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_0223759C:
	add r0, #0xdc
	mov r3, #0x18
	ldrsh r1, [r4, r0]
	ldrsh r0, [r5, r3]
	cmp r1, r0
	bge _022375D0
	add r0, r3, #0
	add r0, #0xf0
	ldrsh r1, [r4, r0]
	add r0, r3, #0
	add r0, #0xf0
	add r1, #0xa
	strh r1, [r4, r0]
	add r3, #0xf0
	ldr r0, [r4]
	ldrb r1, [r4, #0xd]
	ldrb r2, [r4, #0xe]
	ldrsh r3, [r4, r3]
	add r0, #0xc
	bl MOD12_02234088
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_022375D0:
	ldr r0, [r4]
	add r0, #0xc
	bl MOD12_02233C74
	mov r0, #0x18
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_022375E0:
	mov r0, #0xf
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #0xf]
	ldrsb r0, [r4, r0]
	cmp r0, #2
	ble _02237648
	mov r0, #0
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xc]
	add sp, #8
	sub r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_022375FC:
	add r1, r0, #0
	add r1, #0xde
	ldrsh r1, [r4, r1]
	cmp r1, #0x32
	blt _0223761A
	add r0, #0xe4
	ldr r0, [r4, r0]
	bl MOD12_022357E4
	ldr r0, [r4]
	ldrb r1, [r5, #3]
	add r0, #0xc
	mov r2, #0
	bl MOD12_02234628
_0223761A:
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r4, r5, r6, pc}
_02237624:
	ldrb r0, [r4, #0x11]
	cmp r0, #1
	bne _02237648
	mov r0, #0xc3
	mov r2, #0
	ldr r1, [r4]
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r6, #0
	bl FUN_0200CAB4
_02237648:
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223764C: .word 0x0000010E
_02237650: .word 0x000006DF
_02237654: .word 0x0000010A

	thumb_func_start MOD12_02237658
MOD12_02237658: ; 0x02237658
	push {r3, lr}
	mov r0, #0xf4
	str r0, [sp]
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02237670
MOD12_02237670: ; 0x02237670
	push {r3, r4, r5, r6, r7, lr}
	mov r0, #0x15
	add r7, r1, #0
	add r1, r0, #0
	add r1, #0xff
	add r6, r2, #0
	add r5, r3, #0
	bl AllocFromHeap
	mov r2, #0x45
	add r4, r0, #0
	mov r1, #0
	lsl r2, r2, #2
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r6]
	add r3, r4, #0
	add r3, #0x14
	strh r0, [r4, #4]
	ldrh r0, [r6, #2]
	mov r2, #0x1e
	strh r0, [r4, #6]
	ldrh r0, [r6, #4]
	strh r0, [r4, #8]
	ldrh r0, [r6, #6]
	strh r0, [r4, #0xa]
	ldrb r0, [r5]
	strb r0, [r4, #0xd]
	ldrb r0, [r5, #1]
	strb r0, [r4, #0xe]
_022376AE:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _022376AE
	ldr r0, [r5]
	ldr r2, _022376C8 ; =0x00007530
	str r0, [r3]
	ldr r0, _022376CC ; =MOD12_022376D0
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022376C8: .word 0x00007530
_022376CC: .word MOD12_022376D0

	thumb_func_start MOD12_022376D0
MOD12_022376D0: ; 0x022376D0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4, #0xd]
	add r5, r0, #0
	add r2, r4, #0
	mov r0, #0x2c
	add r2, #0x24
	mul r0, r1
	add r3, r2, r0
	ldrb r0, [r4, #0xc]
	cmp r0, #8
	bhi _022377A0
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022376F4: ; jump table
	.short _02237706 - _022376F4 - 2 ; case 0
	.short _02237716 - _022376F4 - 2 ; case 1
	.short _02237738 - _022376F4 - 2 ; case 2
	.short _0223774A - _022376F4 - 2 ; case 3
	.short _0223774E - _022376F4 - 2 ; case 4
	.short _02237754 - _022376F4 - 2 ; case 5
	.short _02237782 - _022376F4 - 2 ; case 6
	.short _0223779C - _022376F4 - 2 ; case 7
	.short _022377A0 - _022376F4 - 2 ; case 8
_02237706:
	mov r0, #0x1a
	ldrsh r1, [r3, r0]
	add r0, #0xee
	strh r1, [r4, r0]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237716:
	ldrb r1, [r3, #0x12]
	cmp r1, #0
	beq _02237732
	mov r0, #0
	str r0, [sp]
	ldrb r2, [r3, #0x13]
	ldr r0, [r4]
	add r3, #0xc
	bl MOD12_02234FF0
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237732:
	mov r0, #3
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237738:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _022377BE
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223774A:
	add r0, r0, #1
	strb r0, [r4, #0xc]
_0223774E:
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02237754:
	mov r5, #0x42
	lsl r5, r5, #2
	mov r0, #0x18
	ldrsh r1, [r4, r5]
	ldrsh r0, [r3, r0]
	cmp r1, r0
	bge _02237776
	add r1, #0xa
	strh r1, [r4, r5]
	ldr r0, [r4]
	ldrb r1, [r4, #0xd]
	ldrb r2, [r4, #0xe]
	ldrsh r3, [r4, r5]
	add r0, #0xc
	bl MOD12_02234088
	b _0223777A
_02237776:
	mov r0, #7
	strb r0, [r4, #0xc]
_0223777A:
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237782:
	mov r0, #0xf
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #0xf]
	ldrsb r0, [r4, r0]
	cmp r0, #2
	ble _022377BE
	mov r0, #0
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xc]
	sub r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223779C:
	add r0, r0, #1
	strb r0, [r4, #0xc]
_022377A0:
	mov r0, #0xc3
	mov r2, #0
	ldr r1, [r4]
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_022377BE:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_022377C0
MOD12_022377C0: ; 0x022377C0
	push {r3, lr}
	mov r0, #0xf4
	str r0, [sp]
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_022377D8
MOD12_022377D8: ; 0x022377D8
	push {r3, r4, r5, r6, r7, lr}
	mov r0, #0x15
	add r7, r1, #0
	add r1, r0, #0
	add r1, #0xf7
	add r5, r2, #0
	add r6, r3, #0
	bl AllocFromHeap
	mov r2, #0x43
	add r4, r0, #0
	mov r1, #0
	lsl r2, r2, #2
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	add r3, r4, #0
	add r3, #0x10
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	mov r2, #0x1e
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
_0223780E:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0223780E
	ldr r0, [r6]
	ldr r2, _02237828 ; =0x00007530
	str r0, [r3]
	ldr r0, _0223782C ; =MOD12_02237830
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02237828: .word 0x00007530
_0223782C: .word MOD12_02237830

	thumb_func_start MOD12_02237830
MOD12_02237830: ; 0x02237830
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp, #4]
	ldr r0, _02237A8C ; =0x00000106
	add r4, r1, #0
	ldrb r0, [r4, r0]
	mov r7, #0
	add r0, r4, r0
	add r0, #0xf9
	ldrb r1, [r0]
	cmp r1, #4
	beq _0223786C
	add r2, r4, #0
	mov r0, #0x2c
	add r2, #0x20
	mul r0, r1
	add r5, r2, r0
	ldr r3, [r4]
	ldr r6, _02237A90 ; =0x00000231
	add r2, r7, #0
_02237858:
	ldrb r0, [r3, r6]
	cmp r1, r0
	bne _02237862
	add r7, r2, #0
	b _0223786E
_02237862:
	add r2, r2, #1
	add r3, r3, #1
	cmp r2, #4
	blt _02237858
	b _0223786E
_0223786C:
	add r5, r7, #0
_0223786E:
	ldrb r0, [r4, #0xc]
	cmp r0, #0x11
	bls _02237876
	b _02237A6A
_02237876:
	add r2, r0, r0
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02237882: ; jump table
	.short _022378A6 - _02237882 - 2 ; case 0
	.short _022378B4 - _02237882 - 2 ; case 1
	.short _02237908 - _02237882 - 2 ; case 2
	.short _02237918 - _02237882 - 2 ; case 3
	.short _0223791C - _02237882 - 2 ; case 4
	.short _02237944 - _02237882 - 2 ; case 5
	.short _0223795A - _02237882 - 2 ; case 6
	.short _0223795E - _02237882 - 2 ; case 7
	.short _02237988 - _02237882 - 2 ; case 8
	.short _0223799C - _02237882 - 2 ; case 9
	.short _022379A0 - _02237882 - 2 ; case 10
	.short _022379C8 - _02237882 - 2 ; case 11
	.short _022379DC - _02237882 - 2 ; case 12
	.short _022379E0 - _02237882 - 2 ; case 13
	.short _022379F2 - _02237882 - 2 ; case 14
	.short _02237A24 - _02237882 - 2 ; case 15
	.short _02237A40 - _02237882 - 2 ; case 16
	.short _02237A6A - _02237882 - 2 ; case 17
_022378A6:
	mov r0, #0x1a
	ldrsh r1, [r5, r0]
	add r0, #0xea
	strh r1, [r4, r0]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_022378B4:
	ldrb r0, [r5, #9]
	cmp r0, #0
	bne _022378C6
	mov r0, #0x6f
	lsl r0, r0, #4
	mov r6, #4
	bl FUN_020054C8
	b _022378F0
_022378C6:
	cmp r0, #1
	bne _022378D4
	ldr r0, _02237A94 ; =0x000006EF
	mov r6, #5
	bl FUN_020054C8
	b _022378F0
_022378D4:
	cmp r0, #2
	bne _022378E2
	ldr r0, _02237A98 ; =0x000006EE
	mov r6, #6
	bl FUN_020054C8
	b _022378F0
_022378E2:
	mov r0, #3
	strb r0, [r4, #0xc]
	ldr r0, _02237A9C ; =0x000006DF
	bl FUN_020054C8
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_022378F0:
	ldr r3, _02237AA0 ; =0x00000107
	ldrb r1, [r5, #3]
	ldr r0, [r4]
	add r2, r6, #0
	add r3, r4, r3
	bl MOD12_02233C94
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02237908:
	ldr r1, _02237AA0 ; =0x00000107
	ldrb r1, [r4, r1]
	cmp r1, #1
	bne _0223794E
	add r0, r0, #1
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02237918:
	add r0, r0, #1
	strb r0, [r4, #0xc]
_0223791C:
	ldrb r1, [r5, #0x12]
	cmp r1, #0
	beq _0223793C
	mov r0, #0
	str r0, [sp]
	ldrb r2, [r5, #0x13]
	add r5, #0xc
	ldr r0, [r4]
	add r3, r5, #0
	bl MOD12_02234FF0
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223793C:
	mov r0, #6
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02237944:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	beq _02237950
_0223794E:
	b _02237A88
_02237950:
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223795A:
	add r0, r0, #1
	strb r0, [r4, #0xc]
_0223795E:
	add r0, r4, #0
	add r0, #0xf4
	ldrb r1, [r0]
	cmp r1, #0
	beq _02237980
	add r2, r4, #0
	add r3, r4, #0
	ldr r0, [r4]
	add r2, #0xe8
	add r3, #0xf8
	bl MOD12_02234FB0
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02237980:
	mov r0, #9
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02237988:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _02237A88
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_0223799C:
	add r0, r0, #1
	strb r0, [r4, #0xc]
_022379A0:
	add r0, r4, #0
	add r0, #0xf5
	ldrb r1, [r0]
	cmp r1, #0
	beq _022379C0
	add r2, r4, #0
	ldr r0, [r4]
	add r2, #0xee
	mov r3, #0
	bl MOD12_02234FB0
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_022379C0:
	mov r0, #0xc
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_022379C8:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _02237A88
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_022379DC:
	add r0, r0, #1
	strb r0, [r4, #0xc]
_022379E0:
	mov r0, #0x1a
	ldrsh r1, [r5, r0]
	add r0, #0xea
	add sp, #8
	strh r1, [r4, r0]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_022379F2:
	mov r3, #0x41
	lsl r3, r3, #2
	mov r2, #0x18
	ldrsh r0, [r4, r3]
	ldrsh r2, [r5, r2]
	cmp r0, r2
	bge _02237A12
	add r0, #0xa
	strh r0, [r4, r3]
	ldr r0, [r4]
	ldrsh r3, [r4, r3]
	add r0, #0xc
	add r2, r7, #0
	bl MOD12_02234088
	b _02237A1A
_02237A12:
	mov r0, #0x10
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02237A1A:
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02237A24:
	mov r0, #0xd
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #0xd]
	ldrsb r0, [r4, r0]
	cmp r0, #2
	ble _02237A88
	mov r0, #0
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xc]
	add sp, #8
	sub r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02237A40:
	ldr r0, _02237A8C ; =0x00000106
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	ldrb r0, [r4, r0]
	cmp r0, #4
	bhs _02237A60
	add r0, r4, r0
	add r0, #0xf9
	ldrb r0, [r0]
	cmp r0, #4
	beq _02237A60
	mov r0, #0xd
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02237A60:
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02237A6A:
	mov r0, #0xc3
	mov r2, #0
	ldr r1, [r4]
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [sp, #4]
	bl FUN_0200CAB4
_02237A88:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02237A8C: .word 0x00000106
_02237A90: .word 0x00000231
_02237A94: .word 0x000006EF
_02237A98: .word 0x000006EE
_02237A9C: .word 0x000006DF
_02237AA0: .word 0x00000107

	thumb_func_start MOD12_02237AA4
MOD12_02237AA4: ; 0x02237AA4
	push {r3, lr}
	mov r0, #0xf4
	str r0, [sp]
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02237ABC
MOD12_02237ABC: ; 0x02237ABC
	push {r3, r4, r5, r6, r7, lr}
	mov r0, #0x15
	add r7, r1, #0
	add r1, r0, #0
	add r1, #0xff
	add r6, r2, #0
	add r5, r3, #0
	bl AllocFromHeap
	mov r2, #0x45
	add r4, r0, #0
	mov r1, #0
	lsl r2, r2, #2
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r6]
	add r3, r4, #0
	add r3, #0x14
	strh r0, [r4, #4]
	ldrh r0, [r6, #2]
	mov r2, #0x1e
	strh r0, [r4, #6]
	ldrh r0, [r6, #4]
	strh r0, [r4, #8]
	ldrh r0, [r6, #6]
	strh r0, [r4, #0xa]
	ldrb r0, [r5]
	strb r0, [r4, #0xd]
	ldrb r0, [r5, #1]
	strb r0, [r4, #0xe]
_02237AFA:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02237AFA
	ldr r0, [r5]
	ldr r2, _02237B14 ; =0x00007530
	str r0, [r3]
	ldr r0, _02237B18 ; =MOD12_02237B1C
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02237B14: .word 0x00007530
_02237B18: .word MOD12_02237B1C

	thumb_func_start MOD12_02237B1C
MOD12_02237B1C: ; 0x02237B1C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4, #0xd]
	add r5, r0, #0
	add r2, r4, #0
	mov r0, #0x2c
	add r2, #0x24
	mul r0, r1
	add r3, r2, r0
	ldrb r0, [r4, #0xc]
	cmp r0, #0xe
	bls _02237B36
	b _02237C6E
_02237B36:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02237B42: ; jump table
	.short _02237B60 - _02237B42 - 2 ; case 0
	.short _02237B70 - _02237B42 - 2 ; case 1
	.short _02237B92 - _02237B42 - 2 ; case 2
	.short _02237BA4 - _02237B42 - 2 ; case 3
	.short _02237BA8 - _02237B42 - 2 ; case 4
	.short _02237BCC - _02237B42 - 2 ; case 5
	.short _02237BDE - _02237B42 - 2 ; case 6
	.short _02237BE2 - _02237B42 - 2 ; case 7
	.short _02237C06 - _02237B42 - 2 ; case 8
	.short _02237C18 - _02237B42 - 2 ; case 9
	.short _02237C1C - _02237B42 - 2 ; case 10
	.short _02237C22 - _02237B42 - 2 ; case 11
	.short _02237C50 - _02237B42 - 2 ; case 12
	.short _02237C6A - _02237B42 - 2 ; case 13
	.short _02237C6E - _02237B42 - 2 ; case 14
_02237B60:
	mov r0, #0x1a
	ldrsh r1, [r3, r0]
	add r0, #0xee
	strh r1, [r4, r0]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237B70:
	ldrb r1, [r3, #0x12]
	cmp r1, #0
	beq _02237B8C
	mov r0, #0
	str r0, [sp]
	ldrb r2, [r3, #0x13]
	ldr r0, [r4]
	add r3, #0xc
	bl MOD12_02234FF0
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237B8C:
	mov r0, #3
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237B92:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _02237C8C
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237BA4:
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02237BA8:
	add r0, r4, #0
	add r0, #0xf8
	ldrb r1, [r0]
	cmp r1, #0
	beq _02237BC6
	add r2, r4, #0
	ldr r0, [r4]
	add r2, #0xec
	mov r3, #0
	bl MOD12_02234FB0
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237BC6:
	mov r0, #6
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237BCC:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _02237C8C
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237BDE:
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02237BE2:
	add r0, r4, #0
	add r0, #0xf9
	ldrb r1, [r0]
	cmp r1, #0
	beq _02237C00
	add r2, r4, #0
	ldr r0, [r4]
	add r2, #0xf2
	mov r3, #0
	bl MOD12_02234FB0
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237C00:
	mov r0, #9
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237C06:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _02237C8C
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237C18:
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02237C1C:
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02237C22:
	mov r5, #0x42
	lsl r5, r5, #2
	mov r0, #0x18
	ldrsh r1, [r4, r5]
	ldrsh r0, [r3, r0]
	cmp r1, r0
	bge _02237C44
	add r1, #0xa
	strh r1, [r4, r5]
	ldr r0, [r4]
	ldrb r1, [r4, #0xd]
	ldrb r2, [r4, #0xe]
	ldrsh r3, [r4, r5]
	add r0, #0xc
	bl MOD12_02234088
	b _02237C48
_02237C44:
	mov r0, #0xd
	strb r0, [r4, #0xc]
_02237C48:
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237C50:
	mov r0, #0xf
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #0xf]
	ldrsb r0, [r4, r0]
	cmp r0, #2
	ble _02237C8C
	mov r0, #0
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xc]
	sub r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237C6A:
	add r0, r0, #1
	strb r0, [r4, #0xc]
_02237C6E:
	mov r0, #0xc3
	mov r2, #0
	ldr r1, [r4]
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02237C8C:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_02237C90
MOD12_02237C90: ; 0x02237C90
	push {r3, lr}
	mov r0, #0xf4
	str r0, [sp]
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02237CA8
MOD12_02237CA8: ; 0x02237CA8
	push {r3, r4, r5, r6, r7, lr}
	mov r0, #0x15
	add r7, r1, #0
	add r1, r0, #0
	add r1, #0xff
	add r5, r2, #0
	add r6, r3, #0
	bl AllocFromHeap
	mov r2, #0x45
	add r4, r0, #0
	mov r1, #0
	lsl r2, r2, #2
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	add r3, r4, #0
	add r3, #0x14
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	mov r2, #0x1e
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r1, [r7, #0xc]
	ldr r0, _02237D04 ; =0x00000123
	ldrb r0, [r1, r0]
	strb r0, [r4, #0xd]
	ldrb r0, [r6, #1]
	strb r0, [r4, #0xe]
_02237CEA:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02237CEA
	ldr r0, [r6]
	ldr r2, _02237D08 ; =0x00007530
	str r0, [r3]
	ldr r0, _02237D0C ; =MOD12_02237D10
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02237D04: .word 0x00000123
_02237D08: .word 0x00007530
_02237D0C: .word MOD12_02237D10

	thumb_func_start MOD12_02237D10
MOD12_02237D10: ; 0x02237D10
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0xd]
	add r2, r4, #0
	mov r1, #0x2c
	add r2, #0x24
	mul r1, r0
	add r2, r2, r1
	ldrb r1, [r4, #0xc]
	cmp r1, #0
	beq _02237D34
	cmp r1, #1
	beq _02237D54
	cmp r1, #2
	beq _02237D68
	b _02237D70
_02237D34:
	mov r1, #0x18
	ldrsh r1, [r2, r1]
	add r2, sp, #0
	bl MOD12_022352A0
	add r1, r0, #0
	ldr r0, [r4]
	add r2, sp, #0
	mov r3, #0
	bl MOD12_02234FB0
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237D54:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _02237D8E
	ldrb r0, [r4, #0xc]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237D68:
	add r0, r1, #1
	add sp, #8
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_02237D70:
	mov r0, #0xc3
	mov r2, #0
	ldr r1, [r4]
	lsl r0, r0, #4
	add r0, r1, r0
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02237D8E:
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_02237D94
MOD12_02237D94: ; 0x02237D94
	push {r3, lr}
	mov r1, #0xf4
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02237DA8
MOD12_02237DA8: ; 0x02237DA8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x15
	mov r1, #0x28
	add r5, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x28
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _02237DE4 ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, _02237DE8 ; =MOD12_02237DEC
	str r6, [r4, #0xc]
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02237DE4: .word 0x00007530
_02237DE8: .word MOD12_02237DEC

	thumb_func_start MOD12_02237DEC
MOD12_02237DEC: ; 0x02237DEC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #3
	bhi _02237EC2
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237E0A: ; jump table
	.short _02237E12 - _02237E0A - 2 ; case 0
	.short _02237E36 - _02237E0A - 2 ; case 1
	.short _02237E78 - _02237E0A - 2 ; case 2
	.short _02237EC2 - _02237E0A - 2 ; case 3
_02237E12:
	mov r1, #0
	add r0, r4, #0
	str r1, [sp]
	add r0, #0x27
	str r0, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	mov r3, #0x46
	bl MOD12_022352F4
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r4, #0x20
	add sp, #8
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_02237E36:
	add r7, r4, #0
	mov r5, #0
	add r6, r4, #0
	add r7, #0x23
_02237E3E:
	ldr r0, [r4]
	ldr r1, _02237EE8 ; =0x00000231
	add r2, r0, r5
	ldrb r1, [r2, r1]
	bl MOD12_022335E4
	str r0, [r6, #0x10]
	ldr r1, [r4]
	add r3, r7, r5
	str r0, [sp]
	add r0, r1, #0
	add r2, r1, r5
	ldr r1, _02237EE8 ; =0x00000231
	ldrb r1, [r2, r1]
	add r2, r5, #0
	bl MOD12_02235470
	add r5, r5, #1
	add r6, r6, #4
	cmp r5, #4
	blt _02237E3E
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r4, #0x20
	add sp, #8
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_02237E78:
	mov r7, #0
	add r6, r7, #0
	add r5, r4, #0
_02237E7E:
	add r0, r4, r6
	add r0, #0x23
	ldrb r0, [r0]
	cmp r0, #0
	bne _02237E94
	ldr r0, [r5, #0x10]
	bl MOD12_02233644
	cmp r0, #0
	bne _02237E94
	add r7, r7, #1
_02237E94:
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #4
	blt _02237E7E
	cmp r7, #4
	bne _02237EE4
	mov r6, #0
	add r5, r4, #0
_02237EA4:
	ldr r0, [r5, #0x10]
	bl MOD12_0223361C
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #4
	blt _02237EA4
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r4, #0x20
	add sp, #8
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_02237EC2:
	add r0, r4, #0
	add r0, #0x27
	ldrb r0, [r0]
	cmp r0, #1
	bne _02237EE4
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02237EE4:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02237EE8: .word 0x00000231

	thumb_func_start MOD12_02237EEC
MOD12_02237EEC: ; 0x02237EEC
	push {r3, lr}
	mov r0, #0xf8
	str r0, [sp]
	mov r0, #0xc3
	lsl r0, r0, #4
	lsl r2, r2, #0x10
	add r0, r1, r0
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}

	thumb_func_start MOD12_02237F04
MOD12_02237F04: ; 0x02237F04
	push {r4, r5, r6, lr}
	mov r0, #0x23
	add r5, r1, #0
	lsl r0, r0, #4
	add r4, r2, #0
	add r6, r5, r0
	mov r2, #0x1f
_02237F12:
	ldmia r3!, {r0, r1}
	stmia r6!, {r0, r1}
	sub r2, r2, #1
	bne _02237F12
	add r0, r5, #0
	add r0, #0xc
	bl MOD12_02234044
	add r0, r5, #0
	add r0, #0xc
	bl MOD12_0223524C
	add r0, r5, #0
	bl MOD12_0223513C
	add r0, r5, #0
	bl MOD12_022335B0
	mov r0, #0xc3
	lsl r0, r0, #4
	mov r2, #0
	add r0, r5, r0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD12_02240FB0
	pop {r4, r5, r6, pc}

	thumb_func_start MOD12_02237F48
MOD12_02237F48: ; 0x02237F48
	push {r3, lr}
	mov r1, #0xf4
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02237F5C
MOD12_02237F5C: ; 0x02237F5C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	str r1, [sp]
	mov r0, #0x15
	mov r1, #0x20
	add r6, r2, #0
	add r5, r3, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x20
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp]
	ldr r2, _02237FCC ; =0x00007530
	str r0, [r4]
	ldrh r0, [r6]
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r6, #2]
	strh r0, [r4, #6]
	ldrh r0, [r6, #4]
	strh r0, [r4, #8]
	ldrh r0, [r6, #6]
	strh r0, [r4, #0xa]
	str r7, [r4, #0xc]
	ldrb r0, [r5]
	strb r0, [r4, #0x11]
	add r0, r5, #0
	add r0, #0xd8
	ldrh r0, [r0]
	strh r0, [r4, #0x14]
	add r0, r5, #0
	add r0, #0xda
	ldrh r0, [r0]
	strh r0, [r4, #0x16]
	add r0, r5, #0
	add r0, #0xdc
	ldrh r0, [r0]
	strh r0, [r4, #0x18]
	add r0, r5, #0
	add r0, #0xe4
	ldrb r0, [r0]
	strb r0, [r4, #0x1a]
	add r0, r5, #0
	add r0, #0xe7
	ldrb r0, [r0]
	add r5, #0xe6
	strb r0, [r4, #0x1c]
	ldrb r0, [r5]
	strb r0, [r4, #0x1b]
	ldr r0, _02237FD0 ; =MOD12_02237FD4
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02237FCC: .word 0x00007530
_02237FD0: .word MOD12_02237FD4

	thumb_func_start MOD12_02237FD4
MOD12_02237FD4: ; 0x02237FD4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _02237FEA
	cmp r0, #1
	beq _0223800A
	cmp r0, #2
	beq _0223801C
	b _02238040
_02237FEA:
	ldrb r1, [r4, #0x1a]
	cmp r1, #0
	beq _02238004
	add r2, r4, #0
	ldr r0, [r4]
	add r2, #0x14
	mov r3, #0
	bl MOD12_02234FB0
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02238004:
	mov r0, #0x64
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223800A:
	ldr r0, [r4]
	bl MOD12_02235020
	cmp r0, #0
	bne _02238058
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223801C:
	ldrb r0, [r4, #0x12]
	add r0, r0, #1
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x1c]
	cmp r0, #1
	bne _02238030
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02238030:
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x1b]
	cmp r1, r0
	blo _02238058
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02238040:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02238058:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_0223805C
MOD12_0223805C: ; 0x0223805C
	strb r1, [r0, #0x12]
	ldr r1, _02238088 ; =0x00007530
	strb r2, [r0, #0x13]
	cmp r3, r1
	beq _02238068
	strb r3, [r0, #0xc]
_02238068:
	ldr r2, [sp]
	ldr r1, _02238088 ; =0x00007530
	cmp r2, r1
	beq _02238072
	strb r2, [r0, #0xd]
_02238072:
	ldr r2, [sp, #4]
	ldr r1, _02238088 ; =0x00007530
	cmp r2, r1
	beq _0223807C
	strh r2, [r0, #0xe]
_0223807C:
	ldr r2, [sp, #8]
	ldr r1, _02238088 ; =0x00007530
	cmp r2, r1
	beq _02238086
	strb r2, [r0, #0x10]
_02238086:
	bx lr
	.align 2, 0
_02238088: .word 0x00007530

	thumb_func_start MOD12_0223808C
MOD12_0223808C: ; 0x0223808C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x26
	add r5, r1, #0
	lsl r0, r0, #4
	add r4, r6, r0
	add r3, r5, #0
	mov r2, #0x19
_0223809C:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0223809C
	add r0, r5, #0
	bl MOD12_02238688
	add r0, r5, #0
	mov r1, #0
	mov r2, #0xb0
	bl MI_CpuFill8
	mov r4, #0
	add r7, r6, #0
_022380B8:
	add r1, r5, #0
	add r0, r6, #0
	add r1, #0xc
	add r2, r4, #0
	bl MOD12_02235274
	ldr r0, _022380F4 ; =0x0000023E
	add r1, r6, r4
	ldrb r0, [r1, r0]
	mov r1, #0xa
	strb r0, [r5, #3]
	ldr r0, _022380F8 ; =0x00000236
	ldrh r0, [r7, r0]
	strh r0, [r5]
	bl GetWazaAttr
	strb r0, [r5, #2]
	mov r0, #0x23
	lsl r0, r0, #4
	add r0, r6, r0
	add r1, r4, #0
	bl MOD12_02235C18
	strb r0, [r5, #9]
	add r4, r4, #1
	add r5, #0x2c
	add r7, r7, #2
	cmp r4, #4
	blt _022380B8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022380F4: .word 0x0000023E
_022380F8: .word 0x00000236

	thumb_func_start MOD12_022380FC
MOD12_022380FC: ; 0x022380FC
	push {r4, r5, r6, r7}
	add r3, r1, #0
	ldr r5, _02238154 ; =0xFFFFFCFF
	ldr r6, _02238158 ; =0xFFFFF3FF
	add r4, r0, #0
	mov r1, #0
	add r2, r3, #0
_0223810A:
	ldr r7, [r2, #0x28]
	add r1, r1, #1
	add r0, r7, #0
	lsl r7, r7, #0x1a
	lsr r7, r7, #0x1e
	lsl r7, r7, #0x1e
	and r0, r5
	lsr r7, r7, #0x16
	orr r7, r0
	add r0, r7, #0
	lsl r7, r7, #0x18
	lsr r7, r7, #0x1e
	lsl r7, r7, #0x1e
	and r0, r6
	lsr r7, r7, #0x14
	orr r0, r7
	str r0, [r2, #0x28]
	add r2, #0x2c
	cmp r1, #4
	blt _0223810A
	ldr r1, _0223815C ; =0x00000252
	mov r0, #0
	add r5, r1, #0
_02238138:
	add r7, r4, r0
	ldrsb r6, [r7, r1]
	add r2, r3, r0
	add r2, #0xc0
	strb r6, [r2]
	add r2, r3, r0
	ldrsb r6, [r7, r5]
	add r2, #0xc3
	add r0, r0, #1
	strb r6, [r2]
	cmp r0, #3
	blt _02238138
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
_02238154: .word 0xFFFFFCFF
_02238158: .word 0xFFFFF3FF
_0223815C: .word 0x00000252

	thumb_func_start MOD12_02238160
MOD12_02238160: ; 0x02238160
	push {r4, r5, r6, r7}
	mov r5, #0
	ldr r2, _02238188 ; =0x00000252
	add r3, r5, #0
_02238168:
	add r7, r1, r5
	mov r6, #0xc3
	ldrsb r7, [r7, r6]
	ldr r6, _02238188 ; =0x00000252
	add r4, r0, r5
	strb r7, [r4, r6]
	ldrsb r6, [r4, r2]
	cmp r6, #0x32
	blt _0223817E
	ldr r6, _02238188 ; =0x00000252
	strb r3, [r4, r6]
_0223817E:
	add r5, r5, #1
	cmp r5, #3
	blt _02238168
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
_02238188: .word 0x00000252

	thumb_func_start MOD12_0223818C
MOD12_0223818C: ; 0x0223818C
	push {r3, r4, r5, r6, r7, lr}
	ldr r7, _022381D4 ; =0x00000242
	mov ip, r1
	add r5, r7, #0
	mov lr, r0
	mov r1, #0
	mov r2, ip
	add r3, r0, #0
	mov r6, #0x18
	add r5, #8
_022381A0:
	ldr r0, _022381D4 ; =0x00000242
	mov r4, #0x18
	ldrsh r0, [r3, r0]
	ldrsh r4, [r2, r4]
	add r1, r1, #1
	add r0, r0, r4
	strh r0, [r3, r7]
	ldrsh r0, [r2, r6]
	add r2, #0x2c
	strh r0, [r3, r5]
	add r3, r3, #2
	cmp r1, #4
	blt _022381A0
	mov r1, #0x26
	lsl r1, r1, #4
	mov r0, lr
	add r4, r0, r1
	mov r3, #0x19
_022381C4:
	mov r2, ip
	ldmia r2!, {r0, r1}
	mov ip, r2
	stmia r4!, {r0, r1}
	sub r3, r3, #1
	bne _022381C4
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022381D4: .word 0x00000242

	thumb_func_start MOD12_022381D8
MOD12_022381D8: ; 0x022381D8
	push {r3, r4}
	mov r2, #0x2c
	mul r2, r1
	add r2, r0, r2
	mov r1, #0x18
	ldrsh r1, [r2, r1]
	mov r4, #0
	strh r1, [r2, #0x1a]
	strh r4, [r2, #0x1e]
	strh r4, [r2, #0x20]
	mov r1, #0xc3
_022381EE:
	add r3, r0, r4
	ldrsb r2, [r3, r1]
	add r3, #0xc0
	add r4, r4, #1
	strb r2, [r3]
	cmp r4, #3
	blt _022381EE
	mov r2, #0
	add r1, r2, #0
_02238200:
	strb r1, [r0, #0x14]
	strb r1, [r0, #0x12]
	add r2, r2, #1
	add r0, #0x2c
	cmp r2, #4
	blt _02238200
	pop {r3, r4}
	bx lr

	thumb_func_start MOD12_02238210
MOD12_02238210: ; 0x02238210
	mov r3, #0
	mov r1, #0x18
_02238214:
	ldrsh r2, [r0, r1]
	add r3, r3, #1
	strh r2, [r0, #0x1c]
	add r0, #0x2c
	cmp r3, #4
	blt _02238214
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02238224
MOD12_02238224: ; 0x02238224
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r1, #0
	add r7, r2, #0
	add r0, r5, #0
	add r1, r7, #0
	bl MOD12_022381D8
	mov r0, #0x2c
	add r4, r7, #0
	mul r4, r0
	add r6, r5, #2
	ldrb r0, [r6, r4]
	ldr r1, _02238274 ; =MOD12_02245618 + 1
	lsl r2, r0, #3
	ldrb r1, [r1, r2]
	cmp r1, #0
	bne _0223826E
	mov r1, #4
	add r2, sp, #0x10
	add r3, sp, #0xc
	bl FUN_02083170
	ldr r1, [sp, #0x10]
	ldr r0, _02238278 ; =0x0000FFFF
	cmp r1, r0
	beq _0223826E
	ldr r0, _0223827C ; =0x00007530
	mov r2, #4
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldrb r1, [r6, r4]
	add r0, r5, r4
	add r3, r7, #0
	bl MOD12_0223805C
_0223826E:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_02238274: .word MOD12_02245618 + 1
_02238278: .word 0x0000FFFF
_0223827C: .word 0x00007530

	thumb_func_start MOD12_02238280
MOD12_02238280: ; 0x02238280
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r2, #0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD12_022381D8
	add r4, r6, #0
	mov r0, #0x2c
	mul r4, r0
	add r0, r5, r4
	ldrb r0, [r0, #2]
	add r6, r5, #4
	bl FUN_02083114
	strb r0, [r6, r4]
	ldrb r1, [r6, r4]
	add r0, r5, r4
	strh r1, [r0, #0x18]
	pop {r4, r5, r6, pc}

	thumb_func_start MOD12_022382A8
MOD12_022382A8: ; 0x022382A8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r1, #0
	str r0, [sp, #4]
	str r2, [sp, #8]
	add r0, r7, #0
	add r1, r2, #0
	str r3, [sp, #0xc]
	bl MOD12_022381D8
	ldr r0, [sp, #8]
	mov r1, #0x2c
	add r4, r0, #0
	mul r4, r1
	add r0, r7, r4
	ldrb r0, [r0, #2]
	lsl r6, r0, #3
	ldr r0, _02238364 ; =MOD12_02245618
	ldrb r0, [r0, r6]
	cmp r0, #3
	bne _022382FE
	ldr r0, [sp, #0xc]
	ldr r5, _02238368 ; =MOD12_02245614
	str r0, [sp]
	ldr r2, [sp, #8]
	ldr r0, [sp, #4]
	ldr r5, [r5, r6]
	add r1, r7, #0
	add r3, r2, #0
	blx r5
	add r2, r7, #0
	mov r0, #1
	add r3, r7, r4
	strb r0, [r3, #0x14]
	mov r0, #0x1e
	add r2, #0x18
	mov r5, #0x20
	ldrsh r0, [r3, r0]
	ldrsh r3, [r3, r5]
	ldrsh r1, [r2, r4]
	add r0, r0, r3
	add r0, r1, r0
	strh r0, [r2, r4]
_022382FE:
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xc]
	cmp r0, #0
	blt _02238360
_02238308:
	ldr r1, [sp, #4]
	ldr r0, [sp, #0x10]
	add r1, r1, r0
	ldr r0, _0223836C ; =0x00000231
	ldrb r5, [r1, r0]
	mov r0, #0x2c
	mul r0, r5
	add r4, r7, r0
	ldrb r0, [r4, #2]
	lsl r1, r0, #3
	ldr r0, _02238368 ; =MOD12_02245614
	add r0, r0, r1
	ldrb r0, [r0, #4]
	cmp r0, #2
	bne _02238354
	add r0, r7, #0
	add r1, r5, #0
	bl MOD12_022381D8
	ldr r0, [sp, #0xc]
	add r3, r5, #0
	str r0, [sp]
	ldrb r5, [r4, #2]
	ldr r0, [sp, #4]
	ldr r2, [sp, #8]
	lsl r6, r5, #3
	ldr r5, _02238368 ; =MOD12_02245614
	add r1, r7, #0
	ldr r5, [r5, r6]
	blx r5
	mov r0, #1
	strb r0, [r4, #0x14]
	mov r0, #0x18
	ldrsh r1, [r4, r0]
	mov r0, #0x1e
	ldrsh r0, [r4, r0]
	add r0, r1, r0
	strh r0, [r4, #0x18]
_02238354:
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0xc]
	add r0, r0, #1
	str r0, [sp, #0x10]
	cmp r0, r1
	ble _02238308
_02238360:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02238364: .word MOD12_02245618
_02238368: .word MOD12_02245614
_0223836C: .word 0x00000231

	thumb_func_start MOD12_02238370
MOD12_02238370: ; 0x02238370
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r6, r2, #0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD12_022381D8
	add r7, r5, #0
	lsl r0, r6, #2
	add r7, #0xb0
	str r0, [sp, #0xc]
	ldr r0, [r7, r0]
	lsl r0, r0, #8
	lsr r0, r0, #0x18
	beq _022383C6
	mov r0, #0x2c
	add r4, r6, #0
	mul r4, r0
	add r1, r5, r4
	mov r0, #0x18
	ldrsh r0, [r1, r0]
	add r1, r5, #0
	add r1, #0x1e
	ldrsh r2, [r1, r4]
	add r2, r2, r0
	strh r2, [r1, r4]
	mov r1, #0xa
	bl _s32_div_f
	ldr r1, _022383E8 ; =0x00007530
	mov r2, #0
	str r1, [sp]
	str r1, [sp, #4]
	str r0, [sp, #8]
	ldr r1, [sp, #0xc]
	add r0, r5, r4
	ldr r1, [r7, r1]
	add r3, r6, #0
	lsl r1, r1, #8
	lsr r1, r1, #0x18
	bl MOD12_0223805C
_022383C6:
	mov r0, #0x2c
	add r2, r6, #0
	add r1, r5, #0
	mul r2, r0
	add r1, #0x18
	add r5, r5, r2
	mov r3, #0x1e
	ldrsh r4, [r5, r3]
	mov r3, #0x20
	ldrsh r3, [r5, r3]
	ldrsh r0, [r1, r2]
	add r3, r4, r3
	add r0, r0, r3
	strh r0, [r1, r2]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022383E8: .word 0x00007530

	thumb_func_start MOD12_022383EC
MOD12_022383EC: ; 0x022383EC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r6, r2, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r6, #0
	str r3, [sp, #8]
	bl MOD12_022381D8
	mov r0, #0x2c
	add r4, r6, #0
	mul r4, r0
	add r0, r5, r4
	ldrb r0, [r0, #2]
	lsl r7, r0, #3
	ldr r0, _02238444 ; =MOD12_02245618
	ldrb r0, [r0, r7]
	cmp r0, #4
	bne _0223843C
	ldr r0, [sp, #8]
	add r2, r6, #0
	add r3, r6, #0
	ldr r6, _02238448 ; =MOD12_02245614
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r6, [r6, r7]
	add r1, r5, #0
	blx r6
	add r3, r5, r4
	mov r0, #1
	strb r0, [r3, #0x14]
	add r5, #0x18
	mov r1, #0x1e
	ldrsh r2, [r5, r4]
	ldrsh r1, [r3, r1]
	add sp, #0xc
	add r1, r2, r1
	strh r1, [r5, r4]
	pop {r4, r5, r6, r7, pc}
_0223843C:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02238444: .word MOD12_02245618
_02238448: .word MOD12_02245614

	thumb_func_start MOD12_0223844C
MOD12_0223844C: ; 0x0223844C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r6, r2, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r6, #0
	str r3, [sp, #8]
	bl MOD12_022381D8
	mov r0, #0x2c
	add r4, r6, #0
	mul r4, r0
	add r0, r5, r4
	ldrb r0, [r0, #2]
	lsl r7, r0, #3
	ldr r0, _022384A4 ; =MOD12_02245618
	ldrb r0, [r0, r7]
	cmp r0, #5
	bne _0223849C
	ldr r0, [sp, #8]
	add r2, r6, #0
	add r3, r6, #0
	ldr r6, _022384A8 ; =MOD12_02245614
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r6, [r6, r7]
	add r1, r5, #0
	blx r6
	add r3, r5, r4
	mov r0, #1
	strb r0, [r3, #0x14]
	add r5, #0x18
	mov r1, #0x1e
	ldrsh r2, [r5, r4]
	ldrsh r1, [r3, r1]
	add sp, #0xc
	add r1, r2, r1
	strh r1, [r5, r4]
	pop {r4, r5, r6, r7, pc}
_0223849C:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_022384A4: .word MOD12_02245618
_022384A8: .word MOD12_02245614

	thumb_func_start MOD12_022384AC
MOD12_022384AC: ; 0x022384AC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r6, r2, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r6, #0
	str r3, [sp, #8]
	bl MOD12_022381D8
	mov r0, #0x2c
	add r4, r6, #0
	mul r4, r0
	add r0, r5, r4
	ldrb r0, [r0, #2]
	lsl r7, r0, #3
	ldr r0, _02238504 ; =MOD12_02245618
	ldrb r0, [r0, r7]
	cmp r0, #6
	bne _022384FC
	ldr r0, [sp, #8]
	add r2, r6, #0
	add r3, r6, #0
	ldr r6, _02238508 ; =MOD12_02245614
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r6, [r6, r7]
	add r1, r5, #0
	blx r6
	add r3, r5, r4
	mov r0, #1
	strb r0, [r3, #0x14]
	add r5, #0x18
	mov r1, #0x1e
	ldrsh r2, [r5, r4]
	ldrsh r1, [r3, r1]
	add sp, #0xc
	add r1, r2, r1
	strh r1, [r5, r4]
	pop {r4, r5, r6, r7, pc}
_022384FC:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02238504: .word MOD12_02245618
_02238508: .word MOD12_02245614

	thumb_func_start MOD12_0223850C
MOD12_0223850C: ; 0x0223850C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r1, #0
	str r0, [sp]
	add r0, r4, #0
	add r1, r2, #0
	str r2, [sp, #4]
	add r7, r3, #0
	bl MOD12_022381D8
	mov r0, #0
	strb r0, [r7, #0xc]
	strb r0, [r7, #0xd]
	ldr r1, [sp]
	ldr r0, [sp, #4]
	mov r6, #0x2c
	add r1, r1, r0
	ldr r0, _02238658 ; =0x0000023E
	ldrb r5, [r1, r0]
	ldr r0, [sp]
	ldr r3, [r0]
	ldr r0, [sp, #4]
	add r2, r5, #0
	add r1, r0, #0
	mul r1, r6
	add r0, r4, r1
	str r0, [sp, #0xc]
	add r0, r6, #0
	add r0, #0xf3
	str r1, [sp, #0x10]
	add r6, #0xf2
	ldrb r0, [r3, r0]
	ldrh r1, [r4, r1]
	ldrb r3, [r3, r6]
	bl MOD12_02235C44
	add r6, r0, #0
	cmp r6, #0
	ble _0223857A
	ldr r0, [sp, #0xc]
	ldr r0, [r0, #0x28]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bne _0223857A
	add r0, r4, #0
	add r0, #0xc3
	ldrsb r1, [r0, r5]
	add r1, r1, r6
	strb r1, [r0, r5]
	ldrsb r1, [r0, r5]
	cmp r1, #0x32
	blt _022385A6
	mov r1, #0x32
	strb r1, [r0, r5]
	b _022385A6
_0223857A:
	cmp r6, #0
	bge _022385A4
	ldr r0, [sp, #0xc]
	ldr r0, [r0, #0x28]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	bne _022385A4
	add r0, r4, #0
	add r0, #0xc3
	add r1, r0, r5
	ldrsb r0, [r0, r5]
	cmp r0, #0
	ble _022385A4
	add r0, r0, r6
	mov r2, #0
	strb r0, [r1]
	ldrsb r0, [r1, r2]
	cmp r0, #0
	bgt _022385A6
	strb r2, [r1]
	b _022385A6
_022385A4:
	mov r6, #0
_022385A6:
	add r1, r4, #0
	add r1, #0xc3
	add r0, r1, r5
	str r0, [sp, #8]
	ldrsb r0, [r1, r5]
	cmp r0, #0x32
	blt _022385D2
	ldr r0, [sp]
	ldr r1, [r0]
	ldr r0, _0223865C ; =0x0000011E
	ldrb r0, [r1, r0]
	cmp r5, r0
	bne _022385CA
	ldr r0, [sp, #0x10]
	mov r1, #0x50
	add r0, r4, r0
	strb r1, [r0, #8]
	b _022385D2
_022385CA:
	ldr r0, [sp, #0x10]
	mov r1, #0x32
	add r0, r4, r0
	strb r1, [r0, #8]
_022385D2:
	add r0, r4, #0
	ldr r1, [sp, #0x10]
	add r0, #8
	add r5, r0, r1
	ldrsb r0, [r0, r1]
	mov r1, #0xa
	bl _s32_div_f
	strb r0, [r7, #0xa]
	cmp r6, #0
	ble _0223862C
	ldr r0, [sp, #0xc]
	mov r1, #0xb
	ldrh r0, [r0]
	bl GetWazaAttr
	bl MOD12_02235AC4
	strb r0, [r7, #0xc]
	ldr r0, [sp, #8]
	mov r1, #0
	ldrsb r0, [r0, r1]
	mov r1, #0xa
	bl _s32_div_f
	cmp r0, #5
	bhi _0223863E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02238614: ; jump table
	.short _0223863E - _02238614 - 2 ; case 0
	.short _0223863E - _02238614 - 2 ; case 1
	.short _0223863E - _02238614 - 2 ; case 2
	.short _0223863E - _02238614 - 2 ; case 3
	.short _02238620 - _02238614 - 2 ; case 4
	.short _02238626 - _02238614 - 2 ; case 5
_02238620:
	mov r0, #0x19
	strb r0, [r7, #0xd]
	b _0223863E
_02238626:
	mov r0, #0x1a
	strb r0, [r7, #0xd]
	b _0223863E
_0223862C:
	bge _0223863E
	ldr r0, [sp, #0xc]
	mov r1, #0xb
	ldrh r0, [r0]
	bl GetWazaAttr
	bl MOD12_02235AF0
	strb r0, [r7, #0xc]
_0223863E:
	ldr r0, [sp, #4]
	mov r1, #0x2c
	add r2, r0, #0
	mov r0, #0
	add r4, #0x18
	mul r2, r1
	ldrsh r1, [r4, r2]
	ldrsb r0, [r5, r0]
	add r0, r1, r0
	strh r0, [r4, r2]
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_02238658: .word 0x0000023E
_0223865C: .word 0x0000011E

	thumb_func_start MOD12_02238660
MOD12_02238660: ; 0x02238660
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r2, #0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD12_022381D8
	mov r0, #0x2c
	add r4, r6, #0
	mul r4, r0
	add r0, r5, r4
	ldrb r0, [r0, #9]
	bl MOD12_02235C38
	add r5, #0x18
	ldrsh r1, [r5, r4]
	add r0, r1, r0
	strh r0, [r5, r4]
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD12_02238688
MOD12_02238688: ; 0x02238688
	push {r3, r4, r5, r6}
	add r3, r0, #0
	ldr r4, _022386B8 ; =0xFFFF0000
	ldr r5, _022386BC ; =0xFF00FFFF
	mov r2, #0
	add r3, #0xb0
_02238694:
	ldr r1, [r3]
	add r2, r2, #1
	and r1, r4
	str r1, [r3]
	ldr r6, [r0, #0x28]
	and r1, r5
	lsl r6, r6, #0xc
	lsr r6, r6, #0x18
	lsl r6, r6, #0x18
	lsr r6, r6, #8
	orr r1, r6
	add r0, #0x2c
	stmia r3!, {r1}
	cmp r2, #4
	blt _02238694
	pop {r3, r4, r5, r6}
	bx lr
	nop
_022386B8: .word 0xFFFF0000
_022386BC: .word 0xFF00FFFF

	thumb_func_start MOD12_022386C0
MOD12_022386C0: ; 0x022386C0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r0, #4
	str r3, [sp, #0xc]
	mov ip, r0
	add r7, r1, #0
	mov r0, #0
	add r2, sp, #0x10
	mov r3, #0xff
_022386D2:
	ldr r4, [r1, #0x28]
	lsl r5, r4, #0x1a
	lsr r5, r5, #0x1e
	bne _022386DE
	strb r3, [r2]
	b _022386F2
_022386DE:
	cmp r5, #1
	bne _022386EA
	lsl r4, r4, #0x18
	lsr r4, r4, #0x1e
	bne _022386EA
	mov ip, r0
_022386EA:
	ldr r4, [r1, #0x28]
	lsl r4, r4, #0x18
	lsr r4, r4, #0x1e
	strb r4, [r2]
_022386F2:
	add r0, r0, #1
	add r1, #0x2c
	add r2, r2, #1
	cmp r0, #4
	blt _022386D2
	ldr r0, [sp, #0xc]
	mov r1, #0xff
	add r6, sp, #0x10
	strb r1, [r6, r0]
	mov r4, #0
_02238706:
	mov r1, #0
	add r2, r6, #0
	add r3, r7, #0
_0223870C:
	ldrb r0, [r2]
	cmp r0, #0xff
	beq _02238728
	cmp r4, r0
	bne _02238728
	ldr r5, [r3, #0x28]
	lsl r5, r5, #0x18
	lsr r5, r5, #0x1e
	cmp r0, r5
	bne _02238728
	ldrb r0, [r6, r1]
	add r0, r0, #1
	strb r0, [r6, r1]
	b _02238732
_02238728:
	add r1, r1, #1
	add r2, r2, #1
	add r3, #0x2c
	cmp r1, #4
	blt _0223870C
_02238732:
	cmp r1, #4
	beq _0223873C
	add r4, r4, #1
	cmp r4, #4
	blt _02238706
_0223873C:
	mov r3, #0
	add r1, sp, #0x10
	add r2, r7, #0
	mov r4, #0xc0
_02238744:
	ldrb r5, [r1]
	cmp r5, #0xff
	beq _02238756
	ldr r0, [r2, #0x28]
	lsl r5, r5, #0x1e
	bic r0, r4
	lsr r5, r5, #0x18
	orr r0, r5
	str r0, [r2, #0x28]
_02238756:
	add r3, r3, #1
	add r1, r1, #1
	add r2, #0x2c
	cmp r3, #4
	blt _02238744
	ldr r0, [sp, #0xc]
	mov r1, #0x2c
	mul r1, r0
	add r0, r7, r1
	ldr r2, [r0, #0x28]
	mov r1, #0x30
	bic r2, r1
	mov r1, #0x10
	orr r2, r1
	mov r1, #0xc0
	bic r2, r1
	mov r1, ip
	str r2, [r0, #0x28]
	cmp r1, #4
	beq _02238794
	mov r1, ip
	str r1, [sp]
	ldr r1, _022387AC ; =0x00007530
	ldr r3, [sp, #0xc]
	str r1, [sp, #4]
	str r1, [sp, #8]
	ldrb r1, [r0, #2]
	mov r2, #1
	bl MOD12_0223805C
	b _022387A6
_02238794:
	ldr r1, _022387AC ; =0x00007530
	ldr r3, [sp, #0xc]
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	ldrb r1, [r0, #2]
	mov r2, #0
	bl MOD12_0223805C
_022387A6:
	mov r0, #1
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022387AC: .word 0x00007530

	thumb_func_start MOD12_022387B0
MOD12_022387B0: ; 0x022387B0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r0, #4
	str r3, [sp, #0xc]
	mov ip, r0
	add r7, r1, #0
	mov r0, #0
	add r2, sp, #0x10
	mov r3, #0xff
_022387C2:
	ldr r4, [r1, #0x28]
	lsl r5, r4, #0x1a
	lsr r5, r5, #0x1e
	bne _022387CE
	strb r3, [r2]
	b _022387E4
_022387CE:
	cmp r5, #2
	bne _022387DC
	lsl r4, r4, #0x18
	lsr r4, r4, #0x1e
	cmp r4, #3
	bne _022387DC
	mov ip, r0
_022387DC:
	ldr r4, [r1, #0x28]
	lsl r4, r4, #0x18
	lsr r4, r4, #0x1e
	strb r4, [r2]
_022387E4:
	add r0, r0, #1
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	add r1, #0x2c
	add r2, r2, #1
	cmp r0, #4
	blt _022387C2
	ldr r0, [sp, #0xc]
	mov r1, #0xff
	add r6, sp, #0x10
	strb r1, [r6, r0]
	mov r4, #3
_022387FC:
	mov r1, #0
	add r2, r6, #0
	add r3, r7, #0
_02238802:
	ldrb r0, [r2]
	cmp r0, #0xff
	beq _0223881E
	cmp r4, r0
	bne _0223881E
	ldr r5, [r3, #0x28]
	lsl r5, r5, #0x18
	lsr r5, r5, #0x1e
	cmp r0, r5
	bne _0223881E
	ldrb r0, [r6, r1]
	sub r0, r0, #1
	strb r0, [r6, r1]
	b _0223882C
_0223881E:
	add r0, r1, #1
	lsl r0, r0, #0x18
	asr r1, r0, #0x18
	add r2, r2, #1
	add r3, #0x2c
	cmp r1, #4
	blt _02238802
_0223882C:
	cmp r1, #4
	beq _0223883E
	sub r0, r4, #1
	lsl r0, r0, #0x18
	asr r4, r0, #0x18
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bgt _022387FC
_0223883E:
	mov r3, #0
	add r1, sp, #0x10
	add r2, r7, #0
	mov r4, #0xc0
_02238846:
	ldrb r5, [r1]
	cmp r5, #0xff
	beq _02238858
	ldr r0, [r2, #0x28]
	lsl r5, r5, #0x1e
	bic r0, r4
	lsr r5, r5, #0x18
	orr r0, r5
	str r0, [r2, #0x28]
_02238858:
	add r0, r3, #1
	lsl r0, r0, #0x18
	asr r3, r0, #0x18
	add r1, r1, #1
	add r2, #0x2c
	cmp r3, #4
	blt _02238846
	ldr r0, [sp, #0xc]
	mov r1, #0x2c
	mul r1, r0
	add r0, r7, r1
	ldr r2, [r0, #0x28]
	mov r1, #0x30
	bic r2, r1
	mov r1, #0x20
	orr r2, r1
	mov r1, #0xc0
	bic r2, r1
	mov r1, #0xc0
	orr r1, r2
	str r1, [r0, #0x28]
	mov r1, ip
	cmp r1, #4
	bne _0223889C
	ldr r1, _022388B8 ; =0x00007530
	ldr r3, [sp, #0xc]
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	ldrb r1, [r0, #2]
	mov r2, #0
	bl MOD12_0223805C
	b _022388B0
_0223889C:
	mov r1, ip
	str r1, [sp]
	ldr r1, _022388B8 ; =0x00007530
	ldr r3, [sp, #0xc]
	str r1, [sp, #4]
	str r1, [sp, #8]
	ldrb r1, [r0, #2]
	mov r2, #1
	bl MOD12_0223805C
_022388B0:
	mov r0, #1
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_022388B8: .word 0x00007530

	thumb_func_start MOD12_022388BC
MOD12_022388BC: ; 0x022388BC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r2, r4, #0
	mov r0, #0x2c
	add r7, r3, #0
	mul r3, r0
	add r2, #9
	add r1, #0x1e
	ldrb r6, [r2, r3]
	mov r5, #0x14
	ldrsh r0, [r1, r3]
	mul r5, r6
	add r0, r0, r5
	strh r0, [r1, r3]
	ldrb r0, [r2, r3]
	cmp r0, #0
	beq _022388EA
	cmp r0, #1
	beq _022388EE
	cmp r0, #2
	beq _022388F2
	b _022388F6
_022388EA:
	mov r2, #0
	b _022388F8
_022388EE:
	mov r2, #1
	b _022388F8
_022388F2:
	mov r2, #2
	b _022388F8
_022388F6:
	mov r2, #3
_022388F8:
	ldr r0, _02238910 ; =0x00007530
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r4, r3
	ldrb r1, [r0, #2]
	add r3, r7, #0
	bl MOD12_0223805C
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02238910: .word 0x00007530

	thumb_func_start MOD12_02238914
MOD12_02238914: ; 0x02238914
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r3, [sp, #0xc]
	ldr r3, [r0]
	ldr r0, [sp, #0xc]
	mov r6, #0x2c
	add r4, r0, #0
	add r0, r6, #0
	mul r4, r6
	add r5, r1, #0
	add r7, r5, r4
	add r0, #0xf3
	add r6, #0xf2
	ldrb r0, [r3, r0]
	ldrh r1, [r5, r4]
	ldrb r2, [r7, #3]
	ldrb r3, [r3, r6]
	bl MOD12_02235C44
	cmp r0, #0
	ble _0223896C
	ldr r0, [r7, #0x28]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bne _0223896C
	add r1, r5, #0
	add r1, #0x1e
	ldrsh r0, [r1, r4]
	ldr r2, _02238974 ; =0x00007530
	ldr r3, [sp, #0xc]
	add r0, #0x14
	strh r0, [r1, r4]
	str r2, [sp]
	ldrh r1, [r5, r4]
	add r0, r7, #0
	str r1, [sp, #4]
	str r2, [sp, #8]
	ldrb r1, [r0, #2]
	mov r2, #0
	bl MOD12_0223805C
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223896C:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02238974: .word 0x00007530

	thumb_func_start MOD12_02238978
MOD12_02238978: ; 0x02238978
	mov r0, #1
	bx lr

	thumb_func_start MOD12_0223897C
MOD12_0223897C: ; 0x0223897C
	push {r3, r4, lr}
	sub sp, #0xc
	mov r0, #0x2c
	add r4, r3, #0
	mul r4, r0
	add r0, r1, r4
	ldrb r2, [r0, #9]
	cmp r2, #0
	bne _022389A8
	add r1, #0x1e
	ldrsh r2, [r1, r4]
	add r2, #0x1e
	strh r2, [r1, r4]
	ldr r1, _022389C0 ; =0x00007530
	mov r2, #0
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	ldrb r1, [r0, #2]
	bl MOD12_0223805C
	b _022389B8
_022389A8:
	ldr r1, _022389C0 ; =0x00007530
	mov r2, #1
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	ldrb r1, [r0, #2]
	bl MOD12_0223805C
_022389B8:
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_022389C0: .word 0x00007530

	thumb_func_start MOD12_022389C4
MOD12_022389C4: ; 0x022389C4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	lsl r4, r3, #1
	add r2, r1, #0
	add r4, r0, r4
	ldr r0, _02238A10 ; =0x00000256
	mov r1, #0x2c
	add r7, r3, #0
	mul r7, r1
	ldrh r1, [r2, r7]
	ldrh r0, [r4, r0]
	cmp r1, r0
	beq _02238A0A
	add r6, r2, #0
	add r6, #0xb0
	lsl r5, r3, #2
	lsl r1, r1, #0x10
	ldr r4, [r6, r5]
	ldr r0, _02238A14 ; =0xFFFF0000
	lsr r1, r1, #0x10
	and r0, r4
	orr r0, r1
	str r0, [r6, r5]
	ldr r0, _02238A18 ; =0x00007530
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r2, r7
	ldrb r1, [r0, #2]
	mov r2, #0
	bl MOD12_0223805C
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02238A0A:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02238A10: .word 0x00000256
_02238A14: .word 0xFFFF0000
_02238A18: .word 0x00007530

	thumb_func_start MOD12_02238A1C
MOD12_02238A1C: ; 0x02238A1C
	push {r4, r5, lr}
	sub sp, #0xc
	mov r0, #0x2c
	add r4, r3, #0
	add r5, r1, #0
	mul r4, r0
	add r0, r5, r4
	ldrb r0, [r0, #3]
	add r2, r5, #0
	add r2, #0x1e
	add r1, r5, r0
	mov r0, #0xc0
	ldrsb r0, [r1, r0]
	ldrsh r1, [r2, r4]
	add r1, r1, r0
	strh r1, [r2, r4]
	mov r1, #0xa
	bl _s32_div_f
	ldr r3, _02238A5C ; =0x00007530
	mov r2, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, r4
	ldrb r1, [r0, #2]
	bl MOD12_0223805C
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_02238A5C: .word 0x00007530

	thumb_func_start MOD12_02238A60
MOD12_02238A60: ; 0x02238A60
	push {r3, r4, lr}
	sub sp, #0xc
	mov r0, #0x2c
	add r4, r3, #0
	mul r4, r0
	add r0, r1, r4
	ldrb r2, [r0, #9]
	cmp r2, #3
	bne _02238A8C
	add r1, #0x1e
	ldrsh r2, [r1, r4]
	add r2, #0x96
	strh r2, [r1, r4]
	ldr r1, _02238AA4 ; =0x00007530
	mov r2, #0
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	ldrb r1, [r0, #2]
	bl MOD12_0223805C
	b _02238A9C
_02238A8C:
	ldr r1, _02238AA4 ; =0x00007530
	mov r2, #1
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	ldrb r1, [r0, #2]
	bl MOD12_0223805C
_02238A9C:
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_02238AA4: .word 0x00007530

	thumb_func_start MOD12_02238AA8
MOD12_02238AA8: ; 0x02238AA8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	mov r0, #0x2c
	add r7, r3, #0
	add r4, r1, #0
	mul r7, r0
	add r1, r4, r7
	ldr r0, [r1, #0x28]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _02238AC6
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_02238AC6:
	mov r3, #0
	mov r0, #0xc3
_02238ACA:
	add r2, r4, r3
	ldrsb r2, [r2, r0]
	cmp r2, #0
	bne _02238AD8
	add r3, r3, #1
	cmp r3, #3
	blt _02238ACA
_02238AD8:
	cmp r3, #3
	bne _02238AE2
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_02238AE2:
	ldr r2, [r1, #0x28]
	mov r0, #8
	orr r0, r2
	mov r3, #0xc3
	str r0, [r1, #0x28]
	mov r2, #0
	add r5, r3, #0
_02238AF0:
	add r0, r4, r2
	ldrsb r6, [r0, r5]
	cmp r6, #0
	ble _02238B00
	ldrsb r6, [r0, r3]
	add r0, #0xc3
	sub r6, #0xa
	strb r6, [r0]
_02238B00:
	add r2, r2, #1
	cmp r2, #3
	blt _02238AF0
	ldr r3, _02238B20 ; =0x00007530
	add r0, r1, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	add r1, r4, r7
	ldrb r1, [r1, #2]
	mov r2, #0
	bl MOD12_0223805C
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02238B20: .word 0x00007530

	thumb_func_start MOD12_02238B24
MOD12_02238B24: ; 0x02238B24
	mov r0, #0x2c
	mul r0, r3
	add r2, r1, r0
	ldr r1, [r2, #0x28]
	ldr r0, _02238B40 ; =0xFFF00FFF
	and r1, r0
	ldrb r0, [r2, #2]
	lsl r0, r0, #0x18
	lsr r0, r0, #0xc
	orr r0, r1
	str r0, [r2, #0x28]
	mov r0, #1
	bx lr
	nop
_02238B40: .word 0xFFF00FFF

	thumb_func_start MOD12_02238B44
MOD12_02238B44: ; 0x02238B44
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r2, r1, #0
	ldr r1, [sp, #0x20]
	add r4, r0, #0
	mov ip, r3
	cmp r1, #4
	bge _02238B70
	ldr r7, _02238B90 ; =0x00000231
	mov r6, #0x2c
	mov r3, #2
_02238B5A:
	add r0, r4, r1
	ldrb r0, [r0, r7]
	add r1, r1, #1
	add r5, r0, #0
	mul r5, r6
	add r0, r2, r5
	ldr r5, [r0, #0x28]
	orr r5, r3
	str r5, [r0, #0x28]
	cmp r1, #4
	blt _02238B5A
_02238B70:
	ldr r3, _02238B94 ; =0x00007530
	mov r1, #0x2c
	mov r0, ip
	str r3, [sp]
	mul r1, r0
	str r3, [sp, #4]
	add r0, r2, r1
	str r3, [sp, #8]
	ldrb r1, [r0, #2]
	mov r2, #0
	bl MOD12_0223805C
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02238B90: .word 0x00000231
_02238B94: .word 0x00007530

	thumb_func_start MOD12_02238B98
MOD12_02238B98: ; 0x02238B98
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r1, [sp, #0x20]
	cmp r1, #0
	bne _02238BAA
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_02238BAA:
	sub r1, r1, #1
	add r1, r0, r1
	ldr r0, _02238BF0 ; =0x00000231
	ldrb r4, [r1, r0]
	mov r0, #0x2c
	add r1, r4, #0
	mul r1, r0
	add r2, r5, r1
	mov r1, #8
	ldrsb r2, [r2, r1]
	cmp r2, #0
	bne _02238BC8
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_02238BC8:
	add r1, r3, #0
	mul r1, r0
	add r0, r5, #0
	add r0, #0x1e
	ldrsh r6, [r0, r1]
	add r2, r6, r2
	strh r2, [r0, r1]
	ldr r0, _02238BF4 ; =0x00007530
	str r4, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, r1
	ldrb r1, [r0, #2]
	mov r2, #0
	bl MOD12_0223805C
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_02238BF0: .word 0x00000231
_02238BF4: .word 0x00007530

	thumb_func_start MOD12_02238BF8
MOD12_02238BF8: ; 0x02238BF8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	str r1, [sp, #0xc]
	str r3, [sp, #0x10]
	mov r3, #0
	add r0, sp, #0x18
	add r1, sp, #0x14
_02238C08:
	lsl r2, r3, #0x18
	lsr r2, r2, #0x18
	strb r2, [r0]
	strb r2, [r1]
	add r2, r3, #1
	lsl r2, r2, #0x18
	asr r3, r2, #0x18
	add r0, r0, #1
	add r1, r1, #1
	cmp r3, #4
	blt _02238C08
	mov r4, #0
	add r7, sp, #0x18
	add r6, sp, #0x14
_02238C24:
	ldr r0, [r5]
	bl FUN_02082878
	mov r1, #4
	sub r1, r1, r4
	bl _s32_div_f
	lsl r0, r1, #0x18
	lsr r2, r0, #0x18
	mov r1, #0
	add r3, r6, #0
_02238C3A:
	ldrb r0, [r3]
	cmp r0, #0xff
	beq _02238C52
	cmp r2, #0
	bne _02238C4C
	mov r0, #0xff
	strb r4, [r7, r1]
	strb r0, [r6, r1]
	b _02238C5E
_02238C4C:
	sub r0, r2, #1
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
_02238C52:
	add r0, r1, #1
	lsl r0, r0, #0x18
	asr r1, r0, #0x18
	add r3, r3, #1
	cmp r1, #4
	blt _02238C3A
_02238C5E:
	add r0, r4, #1
	lsl r0, r0, #0x18
	asr r4, r0, #0x18
	cmp r4, #4
	blt _02238C24
	ldr r1, [sp, #0xc]
	mov r3, #0
	add r2, sp, #0x18
	mov r4, #0x30
	mov r7, #0x30
	mov r5, #0xc0
_02238C74:
	ldr r0, [r1, #0x28]
	bic r0, r4
	orr r0, r7
	str r0, [r1, #0x28]
	ldrb r6, [r2]
	bic r0, r5
	add r2, r2, #1
	lsl r6, r6, #0x1e
	lsr r6, r6, #0x18
	orr r0, r6
	str r0, [r1, #0x28]
	add r0, r3, #1
	lsl r0, r0, #0x18
	asr r3, r0, #0x18
	add r1, #0x2c
	cmp r3, #4
	blt _02238C74
	ldr r3, _02238CB8 ; =0x00007530
	ldr r0, [sp, #0x10]
	mov r1, #0x2c
	mul r1, r0
	str r3, [sp]
	ldr r0, [sp, #0xc]
	str r3, [sp, #4]
	str r3, [sp, #8]
	add r0, r0, r1
	ldrb r1, [r0, #2]
	mov r2, #0
	bl MOD12_0223805C
	mov r0, #1
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_02238CB8: .word 0x00007530

	thumb_func_start MOD12_02238CBC
MOD12_02238CBC: ; 0x02238CBC
	push {r4, r5, lr}
	sub sp, #0xc
	ldr r0, [sp, #0x18]
	add r5, r1, #0
	cmp r0, #3
	bne _02238CFE
	add r4, r3, #0
	mov r0, #0x2c
	add r3, r5, #0
	add r2, r5, #0
	mul r4, r0
	add r3, #0x18
	add r2, #0x1e
	ldrsh r1, [r2, r4]
	ldrsh r0, [r3, r4]
	add r0, r1, r0
	strh r0, [r2, r4]
	ldrsh r0, [r3, r4]
	mov r1, #0xa
	bl _s32_div_f
	ldr r3, _02238D04 ; =0x00007530
	mov r2, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, r4
	ldrb r1, [r0, #2]
	bl MOD12_0223805C
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_02238CFE:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02238D04: .word 0x00007530

	thumb_func_start MOD12_02238D08
MOD12_02238D08: ; 0x02238D08
	push {r4, r5, lr}
	sub sp, #0xc
	mov r0, #0x2c
	add r4, r3, #0
	add r5, r1, #0
	mul r4, r0
	add r0, r5, r4
	ldrb r0, [r0, #3]
	add r1, r5, r0
	mov r0, #0xc0
	ldrsb r0, [r1, r0]
	mov r1, #0xa
	bl _s32_div_f
	ldr r1, _02238D50 ; =MOD12_0224560C
	add r2, r5, #0
	add r2, #0x1e
	ldrb r0, [r1, r0]
	ldrsh r1, [r2, r4]
	add r1, r1, r0
	strh r1, [r2, r4]
	mov r1, #0xa
	bl _s32_div_f
	ldr r3, _02238D54 ; =0x00007530
	mov r2, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, r4
	ldrb r1, [r0, #2]
	bl MOD12_0223805C
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02238D50: .word MOD12_0224560C
_02238D54: .word 0x00007530

	thumb_func_start MOD12_02238D58
MOD12_02238D58: ; 0x02238D58
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r0, [sp, #0x18]
	cmp r0, #0
	bne _02238D8A
	add r4, r3, #0
	mov r0, #0x2c
	add r2, r1, #0
	mul r4, r0
	add r2, #0x1e
	ldrsh r0, [r2, r4]
	ldr r3, _02238D90 ; =0x00007530
	add r0, #0x14
	strh r0, [r2, r4]
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	add r0, r1, r4
	ldrb r1, [r0, #2]
	mov r2, #0
	bl MOD12_0223805C
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, pc}
_02238D8A:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_02238D90: .word 0x00007530

	thumb_func_start MOD12_02238D94
MOD12_02238D94: ; 0x02238D94
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r0, [sp, #0x18]
	cmp r0, #3
	bne _02238DC6
	add r4, r3, #0
	mov r0, #0x2c
	add r2, r1, #0
	mul r4, r0
	add r2, #0x1e
	ldrsh r0, [r2, r4]
	ldr r3, _02238DCC ; =0x00007530
	add r0, #0x14
	strh r0, [r2, r4]
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	add r0, r1, r4
	ldrb r1, [r0, #2]
	mov r2, #0
	bl MOD12_0223805C
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, pc}
_02238DC6:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_02238DCC: .word 0x00007530

	thumb_func_start MOD12_02238DD0
MOD12_02238DD0: ; 0x02238DD0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r2, r1, #0
	ldr r1, [sp, #0x20]
	add r4, r0, #0
	mov ip, r3
	cmp r1, #4
	bge _02238DFC
	ldr r7, _02238E1C ; =0x00000231
	mov r6, #0x2c
	mov r3, #4
_02238DE6:
	add r0, r4, r1
	ldrb r0, [r0, r7]
	add r1, r1, #1
	add r5, r0, #0
	mul r5, r6
	add r0, r2, r5
	ldr r5, [r0, #0x28]
	orr r5, r3
	str r5, [r0, #0x28]
	cmp r1, #4
	blt _02238DE6
_02238DFC:
	ldr r3, _02238E20 ; =0x00007530
	mov r1, #0x2c
	mov r0, ip
	str r3, [sp]
	mul r1, r0
	str r3, [sp, #4]
	add r0, r2, r1
	str r3, [sp, #8]
	ldrb r1, [r0, #2]
	mov r2, #0
	bl MOD12_0223805C
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02238E1C: .word 0x00000231
_02238E20: .word 0x00007530

	thumb_func_start MOD12_02238E24
MOD12_02238E24: ; 0x02238E24
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r6, r0, #0
	ldr r0, [sp, #0x38]
	add r5, r1, #0
	str r3, [sp, #0xc]
	cmp r0, #0
	bne _02238E3A
	add sp, #0x24
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_02238E3A:
	sub r0, r0, #1
	add r1, r6, r0
	ldr r0, _02238EDC ; =0x00000231
	mov r3, #0x2c
	ldrb r0, [r1, r0]
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0xc]
	add r4, r0, #0
	mul r4, r3
	add r0, r5, r4
	str r0, [sp, #0x18]
	ldr r0, [r0, #0x28]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bne _02238E6C
	ldr r0, [sp, #0x1c]
	add r1, r0, #0
	mul r1, r3
	add r0, r5, r1
	str r0, [sp, #0x14]
	ldr r0, [r0, #0x28]
	str r1, [sp, #0x10]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	beq _02238E72
_02238E6C:
	add sp, #0x24
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_02238E72:
	add r0, r3, #0
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x18]
	ldr r7, [r6]
	add r0, #0xf3
	add r3, #0xf2
	ldrb r0, [r7, r0]
	ldrh r1, [r1]
	ldrb r2, [r2, #3]
	ldrb r3, [r7, r3]
	bl MOD12_02235C44
	ldr r2, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r2, r5, r2
	ldr r6, [r6]
	ldr r3, _02238EE0 ; =0x0000011F
	str r0, [sp, #0x20]
	ldrb r0, [r6, r3]
	sub r3, r3, #1
	ldrh r1, [r1]
	ldrb r2, [r2, #3]
	ldrb r3, [r6, r3]
	bl MOD12_02235C44
	cmp r0, #0
	ble _02238ED6
	ldr r0, [sp, #0x20]
	cmp r0, #0
	ble _02238ED6
	add r1, r5, #0
	add r1, #0x1e
	ldrsh r0, [r1, r4]
	ldr r3, [sp, #0xc]
	mov r2, #0
	add r0, #0x1e
	strh r0, [r1, r4]
	ldr r0, [sp, #0x1c]
	add r1, r5, r4
	str r0, [sp]
	ldr r0, _02238EE4 ; =0x00007530
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldrb r1, [r1, #2]
	ldr r0, [sp, #0x18]
	bl MOD12_0223805C
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02238ED6:
	mov r0, #0
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02238EDC: .word 0x00000231
_02238EE0: .word 0x0000011F
_02238EE4: .word 0x00007530

	thumb_func_start MOD12_02238EE8
MOD12_02238EE8: ; 0x02238EE8
	push {r4, r5, lr}
	sub sp, #0xc
	add r0, r1, #0
	mov r1, #0x2c
	mul r1, r3
	add r4, r0, r1
	mov r1, #0x1e
	ldrsh r2, [r4, r1]
	ldr r1, [sp, #0x18]
	ldr r5, _02238F44 ; =MOD12_02245608
	ldrb r5, [r5, r1]
	add r2, r2, r5
	strh r2, [r4, #0x1e]
	cmp r1, #3
	bhi _02238F26
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02238F12: ; jump table
	.short _02238F1A - _02238F12 - 2 ; case 0
	.short _02238F1E - _02238F12 - 2 ; case 1
	.short _02238F22 - _02238F12 - 2 ; case 2
	.short _02238F26 - _02238F12 - 2 ; case 3
_02238F1A:
	mov r2, #0
	b _02238F28
_02238F1E:
	mov r2, #1
	b _02238F28
_02238F22:
	mov r2, #2
	b _02238F28
_02238F26:
	mov r2, #3
_02238F28:
	ldr r1, _02238F48 ; =0x00007530
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0x2c
	mul r1, r3
	add r0, r0, r1
	ldrb r1, [r0, #2]
	bl MOD12_0223805C
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_02238F44: .word MOD12_02245608
_02238F48: .word 0x00007530

	thumb_func_start MOD12_02238F4C
MOD12_02238F4C: ; 0x02238F4C
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r2, [sp, #0x18]
	cmp r2, #0
	bne _02238F5C
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_02238F5C:
	sub r2, r2, #1
	add r2, r0, r2
	ldr r0, _02238FA4 ; =0x00000231
	ldrb r2, [r2, r0]
	mov r0, #0x2c
	mul r0, r2
	add r2, r1, r0
	mov r0, #8
	ldrsb r0, [r2, r0]
	cmp r0, #0x32
	bge _02238F76
	cmp r0, #0x50
	blt _02238F9E
_02238F76:
	add r2, r1, #0
	mov r0, #0x2c
	add r4, r3, #0
	mul r4, r0
	add r2, #0x1e
	ldrsh r0, [r2, r4]
	add r0, #0x1e
	strh r0, [r2, r4]
	ldr r0, _02238FA8 ; =0x00007530
	mov r2, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r1, r4
	ldrb r1, [r0, #2]
	bl MOD12_0223805C
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, pc}
_02238F9E:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_02238FA4: .word 0x00000231
_02238FA8: .word 0x00007530

	thumb_func_start MOD12_02238FAC
MOD12_02238FAC: ; 0x02238FAC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	mov ip, r1
	mov r0, #0x2c
	add r6, r3, #0
	mul r6, r0
	mov r0, ip
	mov r2, #0
	add r4, r1, #0
	add r5, r0, r6
	mov r7, #0x1c
_02238FC2:
	cmp r2, r3
	beq _02238FD0
	mov r0, #0x1a
	ldrsh r1, [r4, r0]
	ldrsh r0, [r5, r7]
	cmp r1, r0
	blt _02238FD8
_02238FD0:
	add r2, r2, #1
	add r4, #0x2c
	cmp r2, #4
	blt _02238FC2
_02238FD8:
	cmp r2, #4
	beq _02238FE2
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_02238FE2:
	mov r1, ip
	add r1, #0x1e
	ldrsh r0, [r1, r6]
	mov r2, #0
	add r0, #0x1e
	strh r0, [r1, r6]
	ldr r0, _02239008 ; =0x00007530
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, ip
	add r0, r0, r6
	ldrb r1, [r0, #2]
	bl MOD12_0223805C
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02239008: .word 0x00007530

	thumb_func_start MOD12_0223900C
MOD12_0223900C: ; 0x0223900C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	str r1, [sp, #4]
	mov r0, #0x15
	mov r1, #0x32
	bl AllocFromHeap
	add r7, r0, #0
	ldr r1, [r6]
	ldr r0, _02239060 ; =0x00000127
	ldrb r4, [r1, r0]
	cmp r4, #4
	bge _02239056
	ldr r0, [sp, #4]
	lsl r1, r4, #1
	add r5, r0, r1
	add r0, #8
	str r0, [sp, #4]
_02239032:
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	bl MOD12_02239064
	ldr r0, [sp, #4]
	add r1, r7, #0
	add r0, r0, r4
	str r0, [sp]
	add r0, r6, #0
	add r2, r4, #0
	add r3, r5, #0
	bl MOD12_022390DC
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, #4
	blt _02239032
_02239056:
	add r0, r7, #0
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02239060: .word 0x00000127

	thumb_func_start MOD12_02239064
MOD12_02239064: ; 0x02239064
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	add r7, r2, #0
	str r1, [sp]
	add r0, r1, #0
	mov r1, #0
	mov r2, #0x32
	bl MI_CpuFill8
	lsl r0, r7, #2
	ldr r5, [sp]
	mov r4, #0
	str r0, [sp, #4]
_02239080:
	ldr r1, [r6]
	ldr r0, [sp, #4]
	mov r2, #0
	ldr r0, [r0, r1]
	add r1, r4, #0
	add r1, #0x36
	bl GetMonData
	strh r0, [r5]
	mov r0, #0x23
	lsl r0, r0, #4
	ldrh r2, [r5]
	add r0, r6, r0
	add r1, r7, #0
	bl MOD12_02235BEC
	cmp r0, #1
	bne _022390BA
	ldrh r0, [r5]
	mov r1, #0xa
	bl GetWazaAttr
	strb r0, [r5, #0xa]
	ldrh r0, [r5]
	mov r1, #0xb
	bl GetWazaAttr
	strb r0, [r5, #0xb]
	b _022390BE
_022390BA:
	mov r0, #0
	strh r0, [r5]
_022390BE:
	add r4, r4, #1
	add r5, #0xc
	cmp r4, #4
	blt _02239080
	ldr r0, [r6]
	add r1, r0, r7
	mov r0, #0x43
	lsl r0, r0, #2
	ldrb r1, [r1, r0]
	ldr r0, [sp]
	add r0, #0x30
	str r0, [sp]
	strb r1, [r0]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD12_022390DC
MOD12_022390DC: ; 0x022390DC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	str r0, [sp, #4]
	ldr r0, [sp, #0x58]
	str r1, [sp, #8]
	str r0, [sp, #0x58]
	mov r1, #0x23
	ldr r0, [sp, #4]
	lsl r1, r1, #4
	add r0, r0, r1
	str r0, [sp, #0x1c]
	mov r0, #0
	str r2, [sp, #0xc]
	str r3, [sp, #0x10]
	str r0, [sp, #0x20]
_022390FA:
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x20]
	add r0, r1, r0
	ldrb r1, [r0, #1]
	ldr r0, [sp, #0xc]
	cmp r0, r1
	beq _02239112
	ldr r0, [sp, #0x20]
	add r0, r0, #1
	str r0, [sp, #0x20]
	cmp r0, #4
	blt _022390FA
_02239112:
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, _022393A4 ; =MOD12_0224574C
	str r0, [sp, #0x18]
_0223911A:
	ldr r0, [sp, #0x20]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	ldrb r0, [r0]
	cmp r1, r0
	bne _0223920C
	mov r1, #0
	add r2, sp, #0x3c
	add r2, #2
	add r0, r1, #0
_0223912E:
	add r1, r1, #1
	strb r0, [r2]
	add r2, r2, #1
	cmp r1, #3
	blt _0223912E
	ldr r0, [sp, #4]
	add r3, sp, #0x3c
	ldr r1, [r0]
	ldr r0, _022393A8 ; =0x0000011F
	ldr r4, [sp, #0x18]
	ldrb r0, [r1, r0]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #8]
	str r0, [sp]
	ldrb r4, [r4, #1]
	ldr r0, [sp, #0x1c]
	add r3, #2
	lsl r5, r4, #2
	ldr r4, _022393AC ; =MOD12_022456D8
	ldr r4, [r4, r5]
	blx r4
	cmp r0, #1
	bne _0223920C
	ldr r0, [sp, #0x18]
	mov r1, #3
	ldrsb r0, [r0, r1]
	cmp r0, #0
	beq _02239170
	cmp r0, #2
	beq _02239184
	cmp r0, #3
	beq _02239184
	b _0223919A
_02239170:
	mov r2, #0
	add r1, sp, #0x3c
	add r1, #2
	add r0, r2, #0
_02239178:
	add r2, r2, #1
	strb r0, [r1]
	add r1, r1, #1
	cmp r2, #3
	blt _02239178
	b _0223919A
_02239184:
	add r2, sp, #0x3c
	mov r3, #0
	add r2, #2
	mov r0, #1
_0223918C:
	ldrb r1, [r2]
	add r3, r3, #1
	eor r1, r0
	strb r1, [r2]
	add r2, r2, #1
	cmp r3, #3
	blt _0223918C
_0223919A:
	ldr r0, [sp, #4]
	ldr r1, [r0]
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	mov r0, #0x43
	lsl r0, r0, #2
	ldrb r2, [r1, r0]
	ldr r0, [sp, #0x18]
	lsl r1, r2, #1
	add r0, r0, r1
	mov r1, #4
	ldrsh r4, [r0, r1]
	cmp r2, #0
	beq _022391BC
	ldr r0, [sp, #0x18]
	ldrsh r0, [r0, r1]
	add r4, r4, r0
_022391BC:
	ldr r0, [sp, #0x18]
	ldrb r0, [r0, #2]
	cmp r0, #0xf0
	beq _022391CA
	cmp r0, #0xf1
	beq _0223920E
	b _0223924E
_022391CA:
	ldr r0, [sp, #8]
	mov r7, #0
	mov r5, #4
_022391D0:
	ldr r1, [sp, #4]
	ldr r2, [r1]
	ldr r1, _022393A8 ; =0x0000011F
	ldrb r2, [r2, r1]
	ldrb r1, [r0, #0xb]
	cmp r2, r1
	bne _02239204
	mov r1, #2
	ldrsh r1, [r0, r1]
	mov r3, #0
	add r2, r0, #0
	add r1, r1, r4
	strh r1, [r0, #2]
	add r1, sp, #0x3c
	add r1, #2
_022391EE:
	ldrb r6, [r1]
	cmp r6, #1
	bne _022391FA
	ldrsh r6, [r2, r5]
	add r6, r6, r4
	strh r6, [r2, #4]
_022391FA:
	add r3, r3, #1
	add r1, r1, #1
	add r2, r2, #2
	cmp r3, #3
	blt _022391EE
_02239204:
	add r7, r7, #1
	add r0, #0xc
	cmp r7, #4
	blt _022391D0
_0223920C:
	b _0223928C
_0223920E:
	ldr r5, [sp, #8]
	mov r7, #0
	mov r6, #4
_02239214:
	ldrb r0, [r5, #0xa]
	bl FUN_02083114
	cmp r0, #0x14
	blt _02239244
	mov r0, #2
	ldrsh r0, [r5, r0]
	mov r2, #0
	add r1, r5, #0
	add r0, r0, r4
	strh r0, [r5, #2]
	add r0, sp, #0x3c
	add r0, #2
_0223922E:
	ldrb r3, [r0]
	cmp r3, #1
	bne _0223923A
	ldrsh r3, [r1, r6]
	add r3, r3, r4
	strh r3, [r1, #4]
_0223923A:
	add r2, r2, #1
	add r0, r0, #1
	add r1, r1, #2
	cmp r2, #3
	blt _0223922E
_02239244:
	add r7, r7, #1
	add r5, #0xc
	cmp r7, #4
	blt _02239214
	b _0223928C
_0223924E:
	ldr r0, [sp, #8]
	mov r7, #0
	mov r5, #4
_02239254:
	ldr r1, [sp, #0x18]
	ldrb r2, [r1, #2]
	ldrb r1, [r0, #0xa]
	cmp r2, r1
	bne _02239284
	mov r1, #2
	ldrsh r1, [r0, r1]
	mov r3, #0
	add r2, r0, #0
	add r1, r1, r4
	strh r1, [r0, #2]
	add r1, sp, #0x3c
	add r1, #2
_0223926E:
	ldrb r6, [r1]
	cmp r6, #1
	bne _0223927A
	ldrsh r6, [r2, r5]
	add r6, r6, r4
	strh r6, [r2, #4]
_0223927A:
	add r3, r3, #1
	add r1, r1, #1
	add r2, r2, #2
	cmp r3, #3
	blt _0223926E
_02239284:
	add r7, r7, #1
	add r0, #0xc
	cmp r7, #4
	blt _02239254
_0223928C:
	ldr r0, [sp, #0x18]
	add r0, #0xc
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r0, r0, #1
	str r0, [sp, #0x14]
	cmp r0, #0xa5
	bge _0223929E
	b _0223911A
_0223929E:
	add r4, sp, #0x34
	mov r5, #0
	add r4, #2
_022392A4:
	ldr r0, [sp, #4]
	ldr r0, [r0]
	bl FUN_02082878
	strh r0, [r4]
	add r5, r5, #1
	add r4, r4, #2
	cmp r5, #4
	blt _022392A4
	mov r5, #0
	add r4, sp, #0x30
_022392BA:
	ldr r0, [sp, #4]
	ldr r0, [r0]
	bl FUN_02082878
	strh r0, [r4]
	add r5, r5, #1
	add r4, r4, #2
	cmp r5, #3
	blt _022392BA
	ldr r0, [sp, #8]
	mov r7, #0
	ldrh r0, [r0]
	cmp r0, #0
	bne _022392E2
	ldr r1, [sp, #8]
_022392D8:
	add r1, #0xc
	ldrh r0, [r1]
	add r7, r7, #1
	cmp r0, #0
	beq _022392D8
_022392E2:
	mov r2, #0xc
	add r1, r7, #0
	ldr r0, [sp, #8]
	mul r1, r2
	add r1, r0, r1
	mov r0, #2
	add r4, r7, #1
	ldrsh r1, [r1, r0]
	cmp r4, #4
	bge _02239336
	ldr r0, [sp, #8]
	mul r2, r4
	add r2, r0, r2
	add r0, sp, #0x34
	lsl r3, r4, #1
	add r0, #2
	add r3, r0, r3
_02239304:
	ldrh r0, [r2]
	cmp r0, #0
	beq _0223932C
	mov r0, #2
	ldrsh r0, [r2, r0]
	cmp r0, r1
	bgt _02239328
	cmp r0, r1
	bne _0223932C
	ldrh r5, [r3]
	lsl r6, r7, #1
	str r5, [sp, #0x28]
	add r5, sp, #0x34
	add r5, #2
	ldrh r6, [r5, r6]
	ldr r5, [sp, #0x28]
	cmp r5, r6
	bls _0223932C
_02239328:
	add r7, r4, #0
	add r1, r0, #0
_0223932C:
	add r4, r4, #1
	add r2, #0xc
	add r3, r3, #2
	cmp r4, #4
	blt _02239304
_02239336:
	ldr r0, [sp, #4]
	ldr r5, [r0]
	ldr r0, _022393B0 ; =0x00000171
	ldrb r0, [r5, r0]
	cmp r0, #0
	bne _022393CA
	mov r0, #0xc
	add r6, r7, #0
	mul r6, r0
	ldr r0, [sp, #8]
	mov r2, #0
	add r4, r0, r6
	add r3, r2, #0
	mov r0, #4
_02239352:
	ldrsh r1, [r4, r0]
	cmp r1, #0
	bne _0223935A
	add r2, r2, #1
_0223935A:
	add r3, r3, #1
	add r4, r4, #2
	cmp r3, #3
	blt _02239352
	cmp r2, #3
	bne _022393CA
	ldr r1, _022393B4 ; =MOD12_022456D4
	add r0, sp, #0x2c
	ldrb r2, [r1]
	strb r2, [r0]
	ldrb r2, [r1, #1]
	strb r2, [r0, #1]
	ldrb r2, [r1, #2]
	ldrb r1, [r1, #3]
	strb r2, [r0, #2]
	strb r1, [r0, #3]
	add r0, r5, #0
	bl FUN_02082878
	ldr r1, [sp, #4]
	mov r2, #0x12
	lsl r0, r0, #0x18
	ldr r1, [r1]
	lsl r2, r2, #4
	ldrb r4, [r1, r2]
	add r3, sp, #0x2c
	lsr r0, r0, #0x18
	ldrb r3, [r3, r4]
	cmp r0, r3
	bge _022393CA
	add r2, r2, #3
	ldrb r2, [r1, r2]
	ldr r1, [sp, #4]
	ldr r0, [sp, #8]
	add r2, r1, r2
	ldr r1, _022393B8 ; =0x0000023E
	b _022393BC
	.align 2, 0
_022393A4: .word MOD12_0224574C
_022393A8: .word 0x0000011F
_022393AC: .word MOD12_022456D8
_022393B0: .word 0x00000171
_022393B4: .word MOD12_022456D4
_022393B8: .word 0x0000023E
_022393BC:
	add r0, r0, #4
	ldrb r1, [r2, r1]
	add r0, r0, r6
	lsl r2, r1, #1
	ldrsh r1, [r0, r2]
	sub r1, #0x64
	strh r1, [r0, r2]
_022393CA:
	mov r0, #0
	str r0, [sp, #0x24]
	mov r0, #0xc
	add r1, r7, #0
	mul r1, r0
	ldr r0, [sp, #8]
	add r3, sp, #0x30
	add r0, r0, r1
	mov r1, #4
	ldrsh r5, [r0, r1]
	mov ip, r0
	mov r4, #1
	add r2, r0, #2
	add r3, #2
_022393E6:
	mov r0, #4
	ldrsh r6, [r2, r0]
	cmp r6, r5
	bgt _02239400
	cmp r6, r5
	bne _02239404
	ldr r0, [sp, #0x24]
	ldrh r7, [r3]
	lsl r1, r0, #1
	add r0, sp, #0x30
	ldrh r0, [r0, r1]
	cmp r7, r0
	bls _02239404
_02239400:
	str r4, [sp, #0x24]
	add r5, r6, #0
_02239404:
	add r4, r4, #1
	add r2, r2, #2
	add r3, r3, #2
	cmp r4, #3
	blt _022393E6
	mov r0, ip
	ldrh r1, [r0]
	ldr r0, [sp, #0x10]
	strh r1, [r0]
	ldr r1, [sp, #0x58]
	ldr r0, [sp, #0x24]
	strb r0, [r1]
	ldr r0, [sp, #0x10]
	ldrh r0, [r0]
	cmp r0, #0
	bne _02239428
	bl ErrorHandling
_02239428:
	ldr r0, [sp, #0x58]
	ldrb r0, [r0]
	cmp r0, #3
	blo _02239434
	bl ErrorHandling
_02239434:
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD12_02239438
MOD12_02239438: ; 0x02239438
	ldrb r0, [r0]
	cmp r0, #4
	bne _02239442
	mov r0, #1
	bx lr
_02239442:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02239448
MOD12_02239448: ; 0x02239448
	lsl r1, r1, #2
	add r0, r0, r1
	add r0, #0xe0
	ldr r0, [r0]
	lsl r0, r0, #8
	lsr r0, r0, #0x18
	beq _0223945A
	mov r0, #1
	bx lr
_0223945A:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02239460
MOD12_02239460: ; 0x02239460
	mov r1, #0
_02239462:
	ldrb r0, [r2, #0xa]
	cmp r0, #5
	bne _0223946C
	mov r0, #1
	bx lr
_0223946C:
	add r1, r1, #1
	add r2, #0xc
	cmp r1, #4
	blt _02239462
	mov r0, #0
	bx lr

	thumb_func_start MOD12_02239478
MOD12_02239478: ; 0x02239478
	mov r1, #0
_0223947A:
	ldrb r0, [r2, #0xa]
	cmp r0, #9
	bne _02239484
	mov r0, #1
	bx lr
_02239484:
	add r1, r1, #1
	add r2, #0xc
	cmp r1, #4
	blt _0223947A
	mov r0, #0
	bx lr

	thumb_func_start MOD12_02239490
MOD12_02239490: ; 0x02239490
	mov r1, #0
_02239492:
	ldrb r0, [r2, #0xa]
	cmp r0, #0xc
	bne _0223949C
	mov r0, #1
	bx lr
_0223949C:
	add r1, r1, #1
	add r2, #0xc
	cmp r1, #4
	blt _02239492
	mov r0, #0
	bx lr

	thumb_func_start MOD12_022394A8
MOD12_022394A8: ; 0x022394A8
	mov r1, #0
_022394AA:
	ldrb r0, [r2, #0xa]
	cmp r0, #0xf
	bne _022394B4
	mov r0, #1
	bx lr
_022394B4:
	add r1, r1, #1
	add r2, #0xc
	cmp r1, #4
	blt _022394AA
	mov r0, #0
	bx lr

	thumb_func_start MOD12_022394C0
MOD12_022394C0: ; 0x022394C0
	mov r1, #0
_022394C2:
	ldrb r0, [r2, #0xa]
	cmp r0, #0x11
	bne _022394CC
	mov r0, #1
	bx lr
_022394CC:
	add r1, r1, #1
	add r2, #0xc
	cmp r1, #4
	blt _022394C2
	mov r0, #0
	bx lr

	thumb_func_start MOD12_022394D8
MOD12_022394D8: ; 0x022394D8
	mov r1, #0
_022394DA:
	ldrb r0, [r2, #0xa]
	cmp r0, #0x12
	bne _022394E4
	mov r0, #1
	bx lr
_022394E4:
	add r1, r1, #1
	add r2, #0xc
	cmp r1, #4
	blt _022394DA
	mov r0, #0
	bx lr

	thumb_func_start MOD12_022394F0
MOD12_022394F0: ; 0x022394F0
	mov r1, #0
_022394F2:
	ldrb r0, [r2, #0xa]
	cmp r0, #0x13
	bne _022394FC
	mov r0, #1
	bx lr
_022394FC:
	add r1, r1, #1
	add r2, #0xc
	cmp r1, #4
	blt _022394F2
	mov r0, #0
	bx lr

	thumb_func_start MOD12_02239508
MOD12_02239508: ; 0x02239508
	mov r1, #0
_0223950A:
	ldrb r0, [r2, #0xa]
	cmp r0, #0x14
	bne _02239514
	mov r0, #1
	bx lr
_02239514:
	add r1, r1, #1
	add r2, #0xc
	cmp r1, #4
	blt _0223950A
	mov r0, #0
	bx lr

	thumb_func_start MOD12_02239520
MOD12_02239520: ; 0x02239520
	mov r1, #0
_02239522:
	ldrb r0, [r2, #0xa]
	cmp r0, #0x15
	bne _0223952C
	mov r0, #1
	bx lr
_0223952C:
	add r1, r1, #1
	add r2, #0xc
	cmp r1, #4
	blt _02239522
	mov r0, #0
	bx lr

	thumb_func_start MOD12_02239538
MOD12_02239538: ; 0x02239538
	push {r3, r4}
	lsl r1, r1, #1
	add r2, r0, r1
	mov r1, #0x12
	ldrsh r3, [r2, r1]
	mov r4, #0
_02239544:
	ldrsh r2, [r0, r1]
	cmp r3, r2
	bgt _02239552
	add r4, r4, #1
	add r0, r0, #2
	cmp r4, #4
	blt _02239544
_02239552:
	cmp r4, #4
	bne _0223955C
	mov r0, #1
	pop {r3, r4}
	bx lr
_0223955C:
	mov r0, #0
	pop {r3, r4}
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02239564
MOD12_02239564: ; 0x02239564
	push {r3, r4}
	ldrb r2, [r0]
	cmp r2, #4
	bne _0223958E
	lsl r1, r1, #1
	add r2, r0, r1
	mov r1, #0x12
	ldrsh r3, [r2, r1]
	mov r4, #0
_02239576:
	ldrsh r2, [r0, r1]
	cmp r3, r2
	bgt _02239584
	add r4, r4, #1
	add r0, r0, #2
	cmp r4, #4
	blt _02239576
_02239584:
	cmp r4, #4
	bne _0223958E
	mov r0, #1
	pop {r3, r4}
	bx lr
_0223958E:
	mov r0, #0
	pop {r3, r4}
	bx lr

	thumb_func_start MOD12_02239594
MOD12_02239594: ; 0x02239594
	ldr r3, [sp]
	mov r1, #0
_02239598:
	ldrb r0, [r2, #0xa]
	cmp r0, #4
	bne _022395A8
	ldrb r0, [r2, #0xb]
	cmp r3, r0
	bne _022395A8
	mov r0, #1
	bx lr
_022395A8:
	add r1, r1, #1
	add r2, #0xc
	cmp r1, #4
	blt _02239598
	mov r0, #0
	bx lr

	thumb_func_start MOD12_022395B4
MOD12_022395B4: ; 0x022395B4
	ldr r3, [sp]
	mov r1, #0
_022395B8:
	ldrb r0, [r2, #0xb]
	cmp r3, r0
	bne _022395C2
	mov r0, #1
	bx lr
_022395C2:
	add r1, r1, #1
	add r2, #0xc
	cmp r1, #4
	blt _022395B8
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD12_022395D0
MOD12_022395D0: ; 0x022395D0
	push {r3, r4, r5, r6}
	ldr r5, [sp, #0x10]
	mov r4, #0
_022395D6:
	ldrb r1, [r2, #0xb]
	cmp r5, r1
	beq _022395E4
	add r4, r4, #1
	add r2, #0xc
	cmp r4, #4
	blt _022395D6
_022395E4:
	cmp r4, #4
	bne _022395EE
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr
_022395EE:
	mov r5, #0
	add r6, r5, #0
	mov r2, #1
	mov r1, #0x22
_022395F6:
	add r4, r0, r6
	ldrsb r4, [r4, r1]
	cmp r4, #0x28
	bne _02239602
	strb r2, [r3, r6]
	add r5, r5, #1
_02239602:
	add r6, r6, #1
	cmp r6, #3
	blt _022395F6
	cmp r5, #0
	ble _02239612
	mov r0, #1
	pop {r3, r4, r5, r6}
	bx lr
_02239612:
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr

	thumb_func_start MOD12_02239618
MOD12_02239618: ; 0x02239618
	push {r3, r4, r5, r6}
	ldr r5, [sp, #0x10]
	mov r4, #0
_0223961E:
	ldrb r1, [r2, #0xb]
	cmp r5, r1
	beq _0223962C
	add r4, r4, #1
	add r2, #0xc
	cmp r4, #4
	blt _0223961E
_0223962C:
	cmp r4, #4
	bne _02239636
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr
_02239636:
	mov r5, #0
	add r6, r5, #0
	mov r2, #1
	mov r1, #0x22
_0223963E:
	add r4, r0, r6
	ldrsb r4, [r4, r1]
	cmp r4, #0x1e
	bne _0223964A
	add r5, r5, #1
	strb r2, [r3, r6]
_0223964A:
	add r6, r6, #1
	cmp r6, #3
	blt _0223963E
	cmp r5, #0
	ble _0223965A
	mov r0, #1
	pop {r3, r4, r5, r6}
	bx lr
_0223965A:
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr

	thumb_func_start MOD12_02239660
MOD12_02239660: ; 0x02239660
	mov r1, #0
_02239662:
	ldrb r0, [r2, #0xa]
	cmp r0, #8
	bne _0223966C
	mov r0, #1
	bx lr
_0223966C:
	add r1, r1, #1
	add r2, #0xc
	cmp r1, #4
	blt _02239662
	mov r0, #0
	bx lr

	thumb_func_start MOD12_02239678
MOD12_02239678: ; 0x02239678
	mov r1, #0
_0223967A:
	ldrb r0, [r2, #0xa]
	cmp r0, #0xd
	bne _02239684
	mov r0, #1
	bx lr
_02239684:
	add r1, r1, #1
	add r2, #0xc
	cmp r1, #4
	blt _0223967A
	mov r0, #0
	bx lr

	thumb_func_start MOD12_02239690
MOD12_02239690: ; 0x02239690
	push {r3, r4, r5, r6}
	mov r6, #0
	add r5, r6, #0
	mov r2, #1
	mov r1, #0x22
_0223969A:
	add r4, r0, r5
	ldrsb r4, [r4, r1]
	cmp r4, #0x28
	bne _022396A6
	add r6, r6, #1
	strb r2, [r3, r5]
_022396A6:
	add r5, r5, #1
	cmp r5, #3
	blt _0223969A
	cmp r6, #0
	ble _022396B6
	mov r0, #1
	pop {r3, r4, r5, r6}
	bx lr
_022396B6:
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr

	thumb_func_start MOD12_022396BC
MOD12_022396BC: ; 0x022396BC
	push {r3, r4, r5, r6}
	mov r6, #0
	add r5, r6, #0
	mov r2, #1
	mov r1, #0x22
_022396C6:
	add r4, r0, r5
	ldrsb r4, [r4, r1]
	cmp r4, #0x1e
	bne _022396D2
	add r6, r6, #1
	strb r2, [r3, r5]
_022396D2:
	add r5, r5, #1
	cmp r5, #3
	blt _022396C6
	cmp r6, #0
	ble _022396E2
	mov r0, #1
	pop {r3, r4, r5, r6}
	bx lr
_022396E2:
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr

	thumb_func_start MOD12_022396E8
MOD12_022396E8: ; 0x022396E8
	push {r3, r4, r5, r6}
	mov r6, #0
	add r5, r6, #0
	mov r2, #1
	mov r1, #0x22
_022396F2:
	add r4, r0, r5
	ldrsb r4, [r4, r1]
	cmp r4, #0xa
	bgt _022396FE
	add r6, r6, #1
	strb r2, [r3, r5]
_022396FE:
	add r5, r5, #1
	cmp r5, #3
	blt _022396F2
	cmp r6, #0
	ble _0223970E
	mov r0, #1
	pop {r3, r4, r5, r6}
	bx lr
_0223970E:
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr

	thumb_func_start MOD12_02239714
MOD12_02239714: ; 0x02239714
	push {r3, r4}
	mov r4, #0
	mov r1, #0x22
_0223971A:
	add r2, r0, r4
	ldrsb r2, [r2, r1]
	cmp r2, #0x14
	bge _02239728
	mov r0, #0
	pop {r3, r4}
	bx lr
_02239728:
	add r4, r4, #1
	cmp r4, #3
	blt _0223971A
	mov r1, #0
	mov r0, #1
_02239732:
	strb r0, [r3, r1]
	add r1, r1, #1
	cmp r1, #3
	blt _02239732
	pop {r3, r4}
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02239740
MOD12_02239740: ; 0x02239740
	push {r3, r4}
	mov r4, #0
	mov r1, #0x22
_02239746:
	add r2, r0, r4
	ldrsb r2, [r2, r1]
	cmp r2, #0x14
	ble _02239754
	mov r0, #0
	pop {r3, r4}
	bx lr
_02239754:
	add r4, r4, #1
	cmp r4, #3
	blt _02239746
	mov r1, #0
	mov r0, #1
_0223975E:
	strb r0, [r3, r1]
	add r1, r1, #1
	cmp r1, #3
	blt _0223975E
	pop {r3, r4}
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0223976C
MOD12_0223976C: ; 0x0223976C
	push {r3, r4, r5, r6}
	mov r6, #0
	add r5, r6, #0
	mov r2, #1
	mov r1, #0x22
_02239776:
	add r4, r0, r5
	ldrsb r4, [r4, r1]
	cmp r4, #0x14
	bgt _02239782
	strb r2, [r3, r5]
	add r6, r6, #1
_02239782:
	add r5, r5, #1
	cmp r5, #3
	blt _02239776
	cmp r6, #1
	bne _02239792
	mov r0, #1
	pop {r3, r4, r5, r6}
	bx lr
_02239792:
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr

	thumb_func_start MOD12_02239798
MOD12_02239798: ; 0x02239798
	push {r3, r4, r5, r6}
	mov r6, #0
	add r5, r6, #0
	mov r2, #1
	mov r1, #0x22
_022397A2:
	add r4, r0, r5
	ldrsb r4, [r4, r1]
	cmp r4, #0x28
	bne _022397AE
	strb r2, [r3, r5]
	add r6, r6, #1
_022397AE:
	add r5, r5, #1
	cmp r5, #3
	blt _022397A2
	cmp r6, #2
	bne _022397BE
	mov r0, #1
	pop {r3, r4, r5, r6}
	bx lr
_022397BE:
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr

	thumb_func_start MOD12_022397C4
MOD12_022397C4: ; 0x022397C4
	push {r3, r4, r5, r6}
	mov r6, #0
	add r5, r6, #0
	mov r2, #1
	mov r1, #0x22
_022397CE:
	add r4, r0, r5
	ldrsb r4, [r4, r1]
	cmp r4, #0
	bne _022397DA
	strb r2, [r3, r5]
	add r6, r6, #1
_022397DA:
	add r5, r5, #1
	cmp r5, #3
	blt _022397CE
	cmp r6, #1
	bne _022397EA
	mov r0, #1
	pop {r3, r4, r5, r6}
	bx lr
_022397EA:
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr

	thumb_func_start MOD12_022397F0
MOD12_022397F0: ; 0x022397F0
	push {r3, r4, r5, r6}
	ldr r5, [sp, #0x10]
	mov r4, #0
_022397F6:
	ldrb r1, [r2, #0xb]
	cmp r5, r1
	beq _02239804
	add r4, r4, #1
	add r2, #0xc
	cmp r4, #4
	blt _022397F6
_02239804:
	cmp r4, #4
	bne _0223980E
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr
_0223980E:
	mov r5, #0
	add r6, r5, #0
	mov r2, #1
	mov r1, #0x22
_02239816:
	add r4, r0, r6
	ldrsb r4, [r4, r1]
	cmp r4, #0x28
	bne _02239822
	strb r2, [r3, r6]
	add r5, r5, #1
_02239822:
	add r6, r6, #1
	cmp r6, #3
	blt _02239816
	cmp r5, #0
	ble _02239832
	mov r0, #1
	pop {r3, r4, r5, r6}
	bx lr
_02239832:
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr

	thumb_func_start MOD12_02239838
MOD12_02239838: ; 0x02239838
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #8]
	cmp r0, #0
	bne _02239858
	lsl r0, r4, #4
	add r0, r5, r0
	ldr r0, [r0, #0x48]
	cmp r0, #0
	beq _02239872
	bl ErrorHandling
	pop {r3, r4, r5, r6, r7, pc}
_02239858:
	bl FUN_02007534
	add r6, r5, #0
	add r6, #0x48
	lsl r7, r4, #4
	ldr r0, [r6, r7]
	bl FreeToHeap
	lsl r0, r4, #2
	mov r1, #0
	add r0, r5, r0
	str r1, [r0, #8]
	str r1, [r6, r7]
_02239872:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD12_02239874
MOD12_02239874: ; 0x02239874
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_0223987A:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD12_02239838
	add r4, r4, #1
	cmp r4, #4
	blt _0223987A
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_0223988C
MOD12_0223988C: ; 0x0223988C
	push {r4, r5, lr}
	sub sp, #0xc
	mov r2, #1
	str r2, [sp]
	mov r2, #2
	str r2, [sp, #4]
	ldr r2, _022398D4 ; =0x000080EA
	mov r3, #0x43
	str r2, [sp, #8]
	mov r2, #0x2e
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _022398D4 ; =0x000080EA
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x44
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _022398D4 ; =0x000080EA
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x45
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_022398D4: .word 0x000080EA

	thumb_func_start MOD12_022398D8
MOD12_022398D8: ; 0x022398D8
	push {r4, lr}
	ldr r1, _022398F4 ; =0x000080EA
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _022398F4 ; =0x000080EA
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _022398F4 ; =0x000080EA
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_022398F4: .word 0x000080EA

	thumb_func_start MOD12_022398F8
MOD12_022398F8: ; 0x022398F8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x16
	mov r1, #0x18
	add r7, r2, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x18
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	ldr r2, _0223996C ; =MOD12_02245F14
	bl FUN_0200C154
	lsl r1, r6, #0x10
	lsl r2, r7, #0x10
	mov r3, #1
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	lsl r3, r3, #0x14
	str r0, [r4, #4]
	bl FUN_0200C750
	ldr r0, [sp, #0x18]
	cmp r0, #1
	bne _0223993C
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_0200C5C0
_0223993C:
	ldr r0, [r4, #4]
	ldr r0, [r0]
	bl FUN_0200C59C
	lsl r0, r6, #8
	str r0, [r4, #8]
	lsl r0, r7, #8
	str r0, [r4, #0xc]
	ldr r0, _02239970 ; =0x000004F9
	ldr r2, _02239974 ; =0x0000C350
	add r1, r5, r0
	str r1, [r4]
	ldrb r0, [r1]
	add r0, r0, #1
	strb r0, [r1]
	ldr r0, _02239978 ; =MOD12_02239980
	add r1, r4, #0
	bl FUN_0200CA44
	ldr r0, _0223997C ; =0x000006E1
	bl FUN_020054C8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223996C: .word MOD12_02245F14
_02239970: .word 0x000004F9
_02239974: .word 0x0000C350
_02239978: .word MOD12_02239980
_0223997C: .word 0x000006E1

	thumb_func_start MOD12_02239980
MOD12_02239980: ; 0x02239980
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x14]
	cmp r0, #0
	bne _022399EE
	ldr r0, [r4, #0x10]
	bl Sin32
	lsl r1, r0, #3
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r5, r0, #0xc
	mov r0, #6
	mov r3, #1
	ldr r1, [r4, #0x10]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [r4, #0x10]
	ldr r0, [r4, #0xc]
	lsl r3, r3, #8
	sub r2, r0, r3
	str r2, [r4, #0xc]
	ldr r1, [r4, #8]
	ldr r0, [r4, #4]
	asr r6, r1, #7
	lsr r6, r6, #0x18
	add r6, r1, r6
	asr r1, r6, #8
	add r1, r1, r5
	asr r5, r2, #7
	lsr r5, r5, #0x18
	add r5, r2, r5
	lsl r1, r1, #0x10
	lsl r2, r5, #8
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	lsl r3, r3, #0xc
	bl FUN_0200C750
	ldrh r0, [r4, #0x16]
	add r0, r0, #1
	strh r0, [r4, #0x16]
	ldrh r0, [r4, #0x16]
	cmp r0, #0x3c
	bhs _022399E6
	ldr r1, [r4, #0xc]
	ldr r0, _02239A0C ; =0xFFFFE000
	cmp r1, r0
	bgt _02239A08
_022399E6:
	ldrb r0, [r4, #0x14]
	add r0, r0, #1
	strb r0, [r4, #0x14]
	pop {r4, r5, r6, pc}
_022399EE:
	ldr r0, [r4, #4]
	bl FUN_0200C3DC
	ldr r1, [r4]
	ldrb r0, [r1]
	sub r0, r0, #1
	strb r0, [r1]
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02239A08:
	pop {r4, r5, r6, pc}
	nop
_02239A0C: .word 0xFFFFE000

	thumb_func_start MOD12_02239A10
MOD12_02239A10: ; 0x02239A10
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r0, #0
	ldr r0, [r5, #0x24]
	add r4, r1, #0
	cmp r0, #0
	beq _02239A22
	bl ErrorHandling
_02239A22:
	mov r1, #0x30
	ldr r2, [r5]
	mul r1, r4
	add r1, r2, r1
	ldrh r1, [r1, #0x1a]
	add r0, sp, #0x10
	bl FUN_020690AC
	ldr r0, _02239A54 ; =0xFFFFFDC0
	mov r2, #5
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x10]
	add r1, sp, #0x10
	lsl r2, r2, #6
	mov r3, #0x20
	bl FUN_020073A0
	str r0, [r5, #0x24]
	add sp, #0x20
	pop {r3, r4, r5, pc}
	.align 2, 0
_02239A54: .word 0xFFFFFDC0

	thumb_func_start MOD12_02239A58
MOD12_02239A58: ; 0x02239A58
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _02239A6A
	bl FUN_02007534
	mov r0, #0
	str r0, [r4, #0x24]
_02239A6A:
	pop {r4, pc}

	thumb_func_start MOD12_02239A6C
MOD12_02239A6C: ; 0x02239A6C
	push {r4, r5, r6, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	cmp r4, #0
	beq _02239A82
	cmp r6, #0
	bne _02239A82
	bl ErrorHandling
_02239A82:
	cmp r4, #0
	beq _02239ACC
	cmp r4, #1
	bne _02239AC8
	ldrb r4, [r6]
	ldr r3, [r5]
	mov r0, #1
	lsl r2, r4, #2
	str r0, [sp]
	mov r0, #2
	add r2, r3, r2
	add r4, r3, r4
	mov r3, #0x42
	str r0, [sp, #4]
	lsl r3, r3, #2
	add r2, #0xe8
	ldrb r3, [r4, r3]
	ldr r0, [r5, #0x48]
	ldr r2, [r2]
	mov r1, #0
	bl BufferString
	ldrb r0, [r6]
	ldr r1, [r5, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r5, #0x48]
	mov r1, #1
	bl BufferBoxMonNickname
	add sp, #8
	pop {r4, r5, r6, pc}
_02239AC8:
	bl ErrorHandling
_02239ACC:
	add sp, #8
	pop {r4, r5, r6, pc}

	thumb_func_start MOD12_02239AD0
MOD12_02239AD0: ; 0x02239AD0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r6, r1, #0
	ldr r1, [r5]
	ldr r0, _02239B40 ; =0x00000171
	add r7, r2, #0
	ldrb r0, [r1, r0]
	str r3, [sp, #0xc]
	cmp r0, #0
	bne _02239AF2
	ldr r0, _02239B44 ; =0x00001988
	ldr r0, [r1, r0]
	bl Options_GetTextFrameDelay
	add r4, r0, #0
	b _02239AF4
_02239AF2:
	mov r4, #1
_02239AF4:
	add r0, r6, #0
	add r1, r7, #0
	bl NewString_ReadMsgData
	add r6, r0, #0
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x28]
	add r0, r5, #0
	bl MOD12_02239A6C
	ldr r0, [r5, #0x48]
	ldr r1, [r5, #0x4c]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	add r0, #0x34
	mov r1, #0xff
	bl FillWindowPixelBuffer
	mov r3, #0
	str r3, [sp]
	str r4, [sp, #4]
	str r3, [sp, #8]
	add r0, r5, #0
	ldr r2, [r5, #0x4c]
	add r0, #0x34
	mov r1, #1
	bl AddTextPrinterParameterized
	add r5, #0xd0
	strb r0, [r5]
	add r0, r6, #0
	bl String_dtor
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02239B40: .word 0x00000171
_02239B44: .word 0x00001988

	thumb_func_start MOD12_02239B48
MOD12_02239B48: ; 0x02239B48
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r1, #0
	add r6, r0, #0
	add r4, r2, #0
	cmp r5, #0xf
	blo _02239B5A
	bl ErrorHandling
_02239B5A:
	str r4, [sp]
	ldr r2, _02239B74 ; =MOD12_02245F48
	lsl r3, r5, #2
	ldr r4, _02239B78 ; =MOD12_02245F48 + 2
	ldrh r2, [r2, r3]
	ldrb r3, [r4, r3]
	ldr r1, [r6, #0x44]
	add r0, r6, #0
	bl MOD12_02239AD0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_02239B74: .word MOD12_02245F48
_02239B78: .word MOD12_02245F48 + 2

	thumb_func_start MOD12_02239B7C
MOD12_02239B7C: ; 0x02239B7C
	ldr r3, _02239B84 ; =FUN_0201BD70
	add r0, #0xd0
	ldrb r0, [r0]
	bx r3
	.align 2, 0
_02239B84: .word FUN_0201BD70

	thumb_func_start MOD12_02239B88
MOD12_02239B88: ; 0x02239B88
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r1, _02239BBC ; =MOD12_02245FA4
	add r3, sp, #0
	str r1, [sp]
	mov r1, #0x11
	strh r1, [r3, #4]
	ldr r1, [r0]
	ldr r2, _02239BC0 ; =0x00000123
	ldrb r1, [r1, r2]
	strb r1, [r3, #6]
	sub r1, r2, #7
	ldr r4, [r0]
	add r2, #0x4e
	ldrb r1, [r4, r1]
	strb r1, [r3, #8]
	ldr r1, [r0]
	ldrb r1, [r1, r2]
	strb r1, [r3, #7]
	ldr r1, _02239BC4 ; =0x000004FC
	add r0, r0, r1
	add r1, sp, #0
	bl MOD12_02240ED0
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_02239BBC: .word MOD12_02245FA4
_02239BC0: .word 0x00000123
_02239BC4: .word 0x000004FC

	thumb_func_start MOD12_02239BC8
MOD12_02239BC8: ; 0x02239BC8
	push {r3, lr}
	lsl r2, r2, #0x10
	mov r3, #0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02239BDC
MOD12_02239BDC: ; 0x02239BDC
	push {r3, lr}
	add r1, r2, #0
	mov r2, #0
	add r3, r2, #0
	bl MOD12_02240FB0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02239BEC
MOD12_02239BEC: ; 0x02239BEC
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02239BF0
MOD12_02239BF0: ; 0x02239BF0
	push {r3, lr}
	lsl r2, r2, #0x10
	mov r3, #0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02239C04
MOD12_02239C04: ; 0x02239C04
	push {r4, lr}
	ldr r3, _02239C18 ; =0x00000F1C
	mov r4, #1
	strb r4, [r1, r3]
	add r1, r2, #0
	mov r2, #0
	add r3, r2, #0
	bl MOD12_02240FB0
	pop {r4, pc}
	.align 2, 0
_02239C18: .word 0x00000F1C

	thumb_func_start MOD12_02239C1C
MOD12_02239C1C: ; 0x02239C1C
	push {r3, lr}
	mov r1, #0x12
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02239C30
MOD12_02239C30: ; 0x02239C30
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r0, [sp, #0x10]
	add r6, r1, #0
	mov r0, #0x16
	mov r1, #0x1c
	add r5, r2, #0
	add r7, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x1c
	bl MI_CpuFill8
	str r6, [r4]
	ldrh r0, [r5]
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	mov r5, #0
	strh r0, [r4, #0xa]
	ldr r0, [sp, #0x10]
	str r0, [r4, #0xc]
	ldrb r0, [r7]
	strb r0, [r4, #0x11]
	b _02239C90
_02239C6C:
	ldr r1, [r4]
	lsl r0, r5, #4
	add r1, r1, r0
	mov r0, #0xf2
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02239C8E
	bl MOD17_021DD540
	ldr r1, [r4]
	lsl r0, r5, #4
	add r2, r1, r0
	mov r0, #0xf2
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r2, r0]
_02239C8E:
	add r5, r5, #1
_02239C90:
	cmp r5, #4
	blt _02239C6C
	ldrb r0, [r7]
	ldr r1, [r6, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #2
	bl FUN_02068E14
	add r0, sp, #0x14
	mov r1, #0
	mov r2, #0x10
	bl MI_CpuFill8
	mov r0, #0x16
	str r0, [sp, #0x20]
	mov r1, #0x80
	mov r0, #0x68
	str r1, [sp, #0x18]
	str r0, [sp, #0x1c]
	ldrb r2, [r7]
	lsl r2, r2, #4
	add r3, r6, r2
	ldr r2, _02239D74 ; =0x00000F24
	str r1, [r3, r2]
	ldrb r1, [r7]
	lsl r1, r1, #4
	add r3, r6, r1
	add r1, r2, #4
	str r0, [r3, r1]
	ldrb r1, [r7]
	ldr r2, [r6]
	add r0, sp, #0x14
	lsl r1, r1, #2
	add r1, r2, r1
	add r1, #0xf8
	ldr r1, [r1]
	bl MOD17_021DD4F4
	ldrb r1, [r7]
	lsl r1, r1, #4
	add r2, r6, r1
	mov r1, #0xf2
	lsl r1, r1, #4
	str r0, [r2, r1]
	ldrb r0, [r7]
	lsl r0, r0, #4
	add r0, r6, r0
	ldr r0, [r0, r1]
	mov r1, #0
	bl MOD17_021DD594
	ldr r0, _02239D78 ; =0x04000048
	mov r2, #0x3f
	ldrh r1, [r0]
	mov r3, #0x1f
	bic r1, r2
	add r5, r1, #0
	orr r5, r3
	mov r1, #0x20
	orr r1, r5
	strh r1, [r0]
	ldrh r1, [r0, #2]
	bic r1, r2
	orr r1, r3
	strh r1, [r0, #2]
	mov r1, #1
	add r2, r1, #0
	add r0, #8
	sub r2, #0x11
	bl G2x_SetBlendBrightness_
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _02239D7C ; =0xFFFF1FFF
	mov r3, #0xff
	and r1, r0
	lsr r0, r2, #0xd
	orr r0, r1
	mov r1, #0xf6
	str r0, [r2]
	lsl r1, r1, #4
	mov r0, #0
	strb r0, [r6, r1]
	add r2, r1, #1
	strb r0, [r6, r2]
	add r2, r1, #2
	strb r3, [r6, r2]
	ldr r2, _02239D80 ; =MOD12_02245F84
	add r1, r1, #3
	ldrsb r2, [r2, r0]
	mov r3, #2
	add r2, r2, #4
	lsl r2, r2, #3
	strb r2, [r6, r1]
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x16
	str r0, [sp, #0xc]
	ldr r2, [r6, #0x30]
	mov r0, #0x2d
	mov r1, #0x14
	bl FUN_020068C8
	ldr r0, _02239D84 ; =MOD12_02239D8C
	ldr r2, _02239D88 ; =0x00007530
	add r1, r4, #0
	bl FUN_0200CA44
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02239D74: .word 0x00000F24
_02239D78: .word 0x04000048
_02239D7C: .word 0xFFFF1FFF
_02239D80: .word MOD12_02245F84
_02239D84: .word MOD12_02239D8C
_02239D88: .word 0x00007530

	thumb_func_start MOD12_02239D8C
MOD12_02239D8C: ; 0x02239D8C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #4
	bhi _02239E6E
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02239DA4: ; jump table
	.short _02239DAE - _02239DA4 - 2 ; case 0
	.short _02239DB4 - _02239DA4 - 2 ; case 1
	.short _02239E0E - _02239DA4 - 2 ; case 2
	.short _02239E14 - _02239DA4 - 2 ; case 3
	.short _02239E54 - _02239DA4 - 2 ; case 4
_02239DAE:
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02239DB4:
	ldr r1, _02239E88 ; =0x04000048
	mov r0, #0x3f
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #0x1e
	orr r2, r0
	mov r0, #0x20
	orr r0, r2
	strh r0, [r1]
	ldr r0, [r4]
	ldr r1, [r0, #0xc]
	ldrb r0, [r4, #0x11]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #2
	bl FUN_02068E14
	add r3, r0, #0
	ldrb r0, [r4, #0x11]
	mov r2, #0xf2
	lsl r2, r2, #4
	lsl r1, r0, #4
	ldr r0, [r4]
	add r5, r0, r1
	add r1, r2, #4
	ldr r0, [r5, r2]
	add r2, #8
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	bl MOD17_021DD678
	ldrb r0, [r4, #0x11]
	ldr r1, [r4]
	lsl r0, r0, #4
	add r1, r1, r0
	mov r0, #0xf2
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #1
	bl MOD17_021DD594
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02239E0E:
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02239E14:
	ldr r1, _02239E88 ; =0x04000048
	mov r0, #0x3f
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #0x1f
	orr r2, r0
	mov r0, #0x20
	orr r0, r2
	strh r0, [r1]
	mov r1, #0
	str r1, [sp]
	ldr r0, [r4]
	ldr r2, _02239E8C ; =0x00001FFF
	ldr r0, [r0, #0x50]
	add r3, r1, #0
	bl FUN_02003A64
	mov r3, #0
	str r3, [sp]
	ldr r0, [r4]
	ldr r2, _02239E90 ; =0x00003FFF
	ldr r0, [r0, #0x50]
	mov r1, #2
	bl FUN_02003A64
	ldr r0, _02239E94 ; =0x000006EC
	bl FUN_020054C8
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02239E54:
	mov r0, #0x12
	ldrsh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, #0x12]
	ldrsh r0, [r4, r0]
	cmp r0, #0xa
	ble _02239E86
	mov r0, #0
	strh r0, [r4, #0x12]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02239E6E:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02239E86:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02239E88: .word 0x04000048
_02239E8C: .word 0x00001FFF
_02239E90: .word 0x00003FFF
_02239E94: .word 0x000006EC

	thumb_func_start MOD12_02239E98
MOD12_02239E98: ; 0x02239E98
	push {r3, lr}
	mov r1, #0x12
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02239EAC
MOD12_02239EAC: ; 0x02239EAC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x16
	mov r1, #0x1c
	add r5, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x1c
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _02239EF0 ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, [sp]
	str r6, [r4, #0xc]
	ldrb r0, [r0]
	strb r0, [r4, #0x11]
	ldr r0, _02239EF4 ; =MOD12_02239EF8
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02239EF0: .word 0x00007530
_02239EF4: .word MOD12_02239EF8

	thumb_func_start MOD12_02239EF8
MOD12_02239EF8: ; 0x02239EF8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _02239F0A
	cmp r0, #1
	beq _02239F3A
	b _02239F8E
_02239F0A:
	ldrb r0, [r4, #0x11]
	ldr r1, [r4]
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #0x14]
	mov r1, #0
	bl FUN_0200782C
	lsl r0, r0, #8
	str r0, [r4, #0x14]
	ldrb r0, [r4, #0x11]
	ldr r1, [r4]
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #0x14]
	mov r1, #1
	bl FUN_0200782C
	lsl r0, r0, #8
	str r0, [r4, #0x18]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02239F3A:
	ldr r0, [r4]
	ldr r1, [r0, #0xc]
	ldrb r0, [r4, #0x11]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #2
	bl FUN_02068E14
	mov r0, #1
	ldr r1, [r4, #0x18]
	lsl r0, r0, #8
	add r2, r1, r0
	lsl r1, r0, #6
	str r2, [r4, #0x18]
	cmp r2, r1
	blt _02239F64
	lsl r0, r0, #6
	str r0, [r4, #0x18]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
_02239F64:
	ldrb r0, [r4, #0x11]
	ldr r2, [r4, #0x14]
	ldr r1, [r4]
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #0x14]
	mov r1, #0
	asr r2, r2, #8
	bl FUN_02007558
	ldrb r0, [r4, #0x11]
	ldr r2, [r4, #0x18]
	ldr r1, [r4]
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #0x14]
	mov r1, #1
	asr r2, r2, #8
	bl FUN_02007558
	pop {r3, r4, r5, pc}
_02239F8E:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_02239FA8
MOD12_02239FA8: ; 0x02239FA8
	push {r3, lr}
	mov r1, #0x12
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02239FBC
MOD12_02239FBC: ; 0x02239FBC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x16
	mov r1, #0x1c
	add r5, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x1c
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _0223A004 ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, [sp]
	str r6, [r4, #0xc]
	ldrb r0, [r0, #1]
	strb r0, [r4, #0x12]
	mov r0, #0
	strb r0, [r4, #0x1a]
	ldr r0, _0223A008 ; =MOD12_0223A0BC
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223A004: .word 0x00007530
_0223A008: .word MOD12_0223A0BC

	thumb_func_start MOD12_0223A00C
MOD12_0223A00C: ; 0x0223A00C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x16
	mov r1, #0x1c
	add r5, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x1c
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _0223A054 ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, [sp]
	str r6, [r4, #0xc]
	ldrb r0, [r0, #2]
	strb r0, [r4, #0x12]
	mov r0, #1
	strb r0, [r4, #0x1a]
	ldr r0, _0223A058 ; =MOD12_0223A0BC
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223A054: .word 0x00007530
_0223A058: .word MOD12_0223A0BC

	thumb_func_start MOD12_0223A05C
MOD12_0223A05C: ; 0x0223A05C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	str r1, [sp]
	mov r0, #0x16
	mov r1, #0x1c
	add r5, r2, #0
	add r6, r3, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x1c
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp]
	ldr r2, _0223A0B4 ; =0x00007530
	str r0, [r4]
	ldrh r0, [r5]
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	str r7, [r4, #0xc]
	ldrb r1, [r6, #1]
	ldrb r0, [r6, #2]
	add r0, r1, r0
	strb r0, [r4, #0x12]
	ldrb r0, [r6, #1]
	add r1, r4, #0
	strb r0, [r4, #0x14]
	ldrb r0, [r6, #2]
	strb r0, [r4, #0x15]
	mov r0, #0
	strb r0, [r4, #0x1a]
	mov r0, #1
	strb r0, [r4, #0x1b]
	ldr r0, _0223A0B8 ; =MOD12_0223A0BC
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223A0B4: .word 0x00007530
_0223A0B8: .word MOD12_0223A0BC

	thumb_func_start MOD12_0223A0BC
MOD12_0223A0BC: ; 0x0223A0BC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	add r4, r0, #0
	ldrb r0, [r5, #0x10]
	cmp r0, #0
	beq _0223A0D6
	cmp r0, #1
	beq _0223A0E6
	cmp r0, #2
	bne _0223A0D4
	b _0223A22E
_0223A0D4:
	b _0223A248
_0223A0D6:
	ldr r0, _0223A264 ; =0x000006E5
	bl FUN_020054C8
	mov r0, #0xf
	strb r0, [r5, #0x11]
	ldrb r0, [r5, #0x10]
	add r0, r0, #1
	strb r0, [r5, #0x10]
_0223A0E6:
	ldrb r1, [r5, #0x13]
	ldrb r0, [r5, #0x12]
	cmp r1, r0
	blo _0223A102
	mov r0, #0
	strb r0, [r5, #0x11]
	ldr r0, _0223A264 ; =0x000006E5
	bl FUN_020054C8
	ldrb r0, [r5, #0x10]
	add sp, #8
	add r0, r0, #1
	strb r0, [r5, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0223A102:
	ldrb r0, [r5, #0x1b]
	cmp r0, #1
	bne _0223A112
	ldrb r0, [r5, #0x14]
	cmp r1, r0
	blo _0223A112
	mov r0, #1
	strb r0, [r5, #0x1a]
_0223A112:
	ldrb r0, [r5, #0x11]
	cmp r0, #0
	beq _0223A120
	sub r0, r0, #1
	add sp, #8
	strb r0, [r5, #0x11]
	pop {r3, r4, r5, r6, r7, pc}
_0223A120:
	mov r0, #3
	strb r0, [r5, #0x11]
	ldr r0, [r5]
	ldr r0, [r0]
	bl FUN_02082878
	mov r1, #0x60
	bl _s32_div_f
	lsl r0, r1, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, [r5]
	ldr r0, [r0]
	bl FUN_02082878
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1a
	sub r1, r1, r2
	mov r0, #0x1a
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x10
	asr r7, r0, #0x10
	ldr r0, [r5]
	ldr r0, [r0]
	bl FUN_02082878
	mov r1, #1
	tst r0, r1
	beq _0223A164
	ldr r0, [sp, #4]
	add r0, #0x80
	b _0223A16A
_0223A164:
	ldr r0, [sp, #4]
	mov r1, #0x80
	sub r0, r1, r0
_0223A16A:
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	ldr r0, [r5]
	ldr r0, [r0]
	bl FUN_02082878
	mov r1, #1
	tst r0, r1
	beq _0223A182
	add r0, r7, #0
	add r0, #0x60
	b _0223A186
_0223A182:
	mov r0, #0x60
	sub r0, r0, r7
_0223A186:
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	ldrb r0, [r5, #0x13]
	cmp r0, #0
	beq _0223A1F6
	mov r0, #0x16
	ldrsh r0, [r5, r0]
	cmp r0, #0x80
	bge _0223A19C
	cmp r6, #0x80
	blt _0223A1A4
_0223A19C:
	cmp r0, #0x80
	ble _0223A1F6
	cmp r6, #0x80
	ble _0223A1F6
_0223A1A4:
	mov r0, #0x18
	ldrsh r0, [r5, r0]
	cmp r0, #0x60
	bge _0223A1B0
	cmp r4, #0x60
	blt _0223A1B8
_0223A1B0:
	cmp r0, #0x60
	ble _0223A1F6
	cmp r4, #0x60
	ble _0223A1F6
_0223A1B8:
	ldr r0, [r5]
	ldr r0, [r0]
	bl FUN_02082878
	mov r1, #1
	tst r0, r1
	beq _0223A1E2
	cmp r6, #0x80
	bge _0223A1D6
	ldr r0, [sp, #4]
	add r0, #0x80
	str r0, [sp, #4]
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	b _0223A1F6
_0223A1D6:
	ldr r0, [sp, #4]
	mov r1, #0x80
	sub r0, r1, r0
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	b _0223A1F6
_0223A1E2:
	cmp r4, #0x60
	bge _0223A1EE
	add r7, #0x60
	lsl r0, r7, #0x10
	asr r4, r0, #0x10
	b _0223A1F6
_0223A1EE:
	mov r0, #0x60
	sub r0, r0, r7
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
_0223A1F6:
	ldrb r1, [r5, #0x13]
	mov r0, #1
	tst r0, r1
	ldrb r0, [r5, #0x1a]
	beq _0223A212
	str r0, [sp]
	mov r3, #0x2d
	ldr r0, [r5]
	add r1, r6, #0
	add r2, r4, #0
	lsl r3, r3, #0xe
	bl MOD12_022398F8
	b _0223A220
_0223A212:
	str r0, [sp]
	ldr r0, [r5]
	add r1, r6, #0
	add r2, r4, #0
	mov r3, #0
	bl MOD12_022398F8
_0223A220:
	strh r6, [r5, #0x16]
	strh r4, [r5, #0x18]
	ldrb r0, [r5, #0x13]
	add sp, #8
	add r0, r0, #1
	strb r0, [r5, #0x13]
	pop {r3, r4, r5, r6, r7, pc}
_0223A22E:
	ldrb r0, [r5, #0x11]
	add r0, r0, #1
	strb r0, [r5, #0x11]
	ldrb r0, [r5, #0x11]
	cmp r0, #0x1e
	bls _0223A260
	mov r0, #0
	strb r0, [r5, #0x11]
	ldrb r0, [r5, #0x10]
	add sp, #8
	add r0, r0, #1
	strb r0, [r5, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0223A248:
	mov r2, #0
	ldr r0, [r5, #0xc]
	add r1, r5, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_0223A260:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223A264: .word 0x000006E5

	thumb_func_start MOD12_0223A268
MOD12_0223A268: ; 0x0223A268
	push {r3, lr}
	mov r1, #0x12
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223A27C
MOD12_0223A27C: ; 0x0223A27C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x16
	mov r1, #0x1c
	add r5, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x1c
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _0223A2C0 ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, [sp]
	str r6, [r4, #0xc]
	ldrb r0, [r0]
	strb r0, [r4, #0x11]
	ldr r0, _0223A2C4 ; =MOD12_0223A2C8
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223A2C0: .word 0x00007530
_0223A2C4: .word MOD12_0223A2C8

	thumb_func_start MOD12_0223A2C8
MOD12_0223A2C8: ; 0x0223A2C8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	ldr r1, [r0, #0xc]
	ldrb r0, [r4, #0x11]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #2
	bl FUN_02068E14
	add r3, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _0223A2EC
	cmp r0, #1
	beq _0223A314
	b _0223A348
_0223A2EC:
	ldrb r0, [r4, #0x11]
	ldr r1, [r4]
	lsl r0, r0, #4
	add r1, r1, r0
	ldr r0, _0223A384 ; =0x00000F24
	ldr r1, [r1, r0]
	add r0, r0, #4
	lsl r1, r1, #8
	str r1, [r4, #0x14]
	ldrb r1, [r4, #0x11]
	ldr r2, [r4]
	lsl r1, r1, #4
	add r1, r2, r1
	ldr r0, [r1, r0]
	lsl r0, r0, #8
	str r0, [r4, #0x18]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223A314:
	mov r0, #3
	ldr r1, [r4, #0x14]
	lsl r0, r0, #8
	add r1, r1, r0
	mov r0, #0x4b
	lsl r0, r0, #0xa
	str r1, [r4, #0x14]
	cmp r1, r0
	blt _0223A32C
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
_0223A32C:
	ldrb r0, [r4, #0x11]
	ldr r2, [r4, #0x18]
	ldr r1, [r4]
	lsl r0, r0, #4
	add r1, r1, r0
	mov r0, #0xf2
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	ldr r1, [r4, #0x14]
	asr r2, r2, #8
	asr r1, r1, #8
	bl MOD17_021DD678
	pop {r3, r4, r5, pc}
_0223A348:
	ldrb r0, [r4, #0x11]
	ldr r1, [r4]
	lsl r0, r0, #4
	add r1, r1, r0
	mov r0, #0xf2
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl MOD17_021DD540
	ldrb r0, [r4, #0x11]
	mov r2, #0
	ldr r1, [r4]
	lsl r0, r0, #4
	add r1, r1, r0
	mov r0, #0xf2
	lsl r0, r0, #4
	str r2, [r1, r0]
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	nop
_0223A384: .word 0x00000F24

	thumb_func_start MOD12_0223A388
MOD12_0223A388: ; 0x0223A388
	push {r3, lr}
	lsl r2, r2, #0x10
	mov r3, #0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223A39C
MOD12_0223A39C: ; 0x0223A39C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x16
	mov r1, #0x18
	add r5, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x18
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _0223A3D8 ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, _0223A3DC ; =MOD12_0223A3E0
	str r6, [r4, #0xc]
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223A3D8: .word 0x00007530
_0223A3DC: .word MOD12_0223A3E0

	thumb_func_start MOD12_0223A3E0
MOD12_0223A3E0: ; 0x0223A3E0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldrb r0, [r1, #0x10]
	str r1, [sp]
	cmp r0, #0
	beq _0223A3F0
	b _0223A516
_0223A3F0:
	ldr r0, [sp]
	mov r1, #0x14
	ldrsb r0, [r0, r1]
	cmp r0, #0
	ble _0223A404
	sub r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x14]
	pop {r4, r5, r6, r7, pc}
_0223A404:
	ldr r0, [sp]
	mov r1, #0x13
	ldrsb r0, [r0, r1]
	cmp r0, #0
	ble _0223A418
	sub r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x13]
	pop {r4, r5, r6, r7, pc}
_0223A418:
	ldr r0, [sp]
	mov r1, #1
	strb r1, [r0, #0x13]
	ldr r0, [r0]
	mov r1, #2
	ldr r0, [r0, #0x30]
	bl FUN_0201886C
	mov ip, r0
	mov r0, #0
	str r0, [sp, #8]
	b _0223A490
_0223A430:
	ldr r0, [sp]
	mov r1, #0x11
	ldrsb r1, [r0, r1]
	ldr r0, _0223A534 ; =MOD12_02245F84
	ldrsb r1, [r0, r1]
	ldr r0, [sp, #8]
	add r0, r1, r0
	bmi _0223A48A
	lsl r1, r0, #6
	mov r0, ip
	add r3, r0, r1
	ldr r0, [sp]
	mov r5, #0
	ldrb r0, [r0, #0x12]
	mov r7, #0x3f
	str r5, [sp, #4]
	lsl r1, r0, #1
	ldr r0, _0223A538 ; =MOD12_02245F8C
	lsl r7, r7, #0xa
	ldrh r1, [r0, r1]
	ldr r0, [sp, #8]
	lsl r0, r0, #5
	add r6, r1, r0
	b _0223A484
_0223A460:
	mov r4, #0
	b _0223A478
_0223A464:
	add r0, r5, r4
	lsl r2, r0, #1
	ldrh r0, [r3, r2]
	and r0, r7
	strh r0, [r3, r2]
	ldrh r1, [r3, r2]
	add r0, r6, r4
	add r4, r4, #1
	orr r0, r1
	strh r0, [r3, r2]
_0223A478:
	cmp r4, #8
	blt _0223A464
	ldr r0, [sp, #4]
	add r5, #8
	add r0, r0, #1
	str r0, [sp, #4]
_0223A484:
	ldr r0, [sp, #4]
	cmp r0, #4
	blt _0223A460
_0223A48A:
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
_0223A490:
	ldr r0, [sp, #8]
	cmp r0, #4
	blt _0223A430
	ldr r0, [sp]
	mov r1, #0x11
	ldrsb r1, [r0, r1]
	cmp r1, #0
	ble _0223A4D2
	ldrb r0, [r0, #0x12]
	cmp r0, #0
	bne _0223A4D2
	ldr r0, _0223A534 ; =MOD12_02245F84
	sub r1, r1, #1
	ldrsb r0, [r0, r1]
	lsl r1, r0, #6
	mov r0, ip
	add r3, r0, r1
	mov r0, #0
	mov r1, #0x3f
	str r0, [sp, #4]
	lsl r1, r1, #0xa
	b _0223A4CC
_0223A4BC:
	ldr r0, [sp, #4]
	lsl r2, r0, #1
	ldrh r0, [r3, r2]
	and r0, r1
	strh r0, [r3, r2]
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
_0223A4CC:
	ldr r0, [sp, #4]
	cmp r0, #0x20
	blt _0223A4BC
_0223A4D2:
	ldr r0, [sp]
	mov r1, #2
	ldr r0, [r0]
	ldr r0, [r0, #0x30]
	bl FUN_0201AC68
	ldr r0, [sp]
	ldrb r0, [r0, #0x12]
	add r1, r0, #1
	ldr r0, [sp]
	strb r1, [r0, #0x12]
	ldrb r0, [r0, #0x12]
	cmp r0, #0xc
	blo _0223A530
	ldr r1, [sp]
	mov r0, #0
	mov r2, #0x11
	strb r0, [r1, #0x12]
	ldrsb r1, [r1, r2]
	add r3, r1, #1
	ldr r1, [sp]
	strb r3, [r1, #0x11]
	strb r0, [r1, #0x14]
	add r0, r1, #0
	ldrsb r0, [r0, r2]
	cmp r0, #5
	blo _0223A530
	add r0, r1, #0
	ldrb r0, [r0, #0x10]
	add r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x10]
	pop {r4, r5, r6, r7, pc}
_0223A516:
	add r0, r1, #0
	mov r2, #0
	ldr r0, [r0, #0xc]
	add r1, r1, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	ldr r0, [sp]
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_0223A530:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223A534: .word MOD12_02245F84
_0223A538: .word MOD12_02245F8C

	thumb_func_start MOD12_0223A53C
MOD12_0223A53C: ; 0x0223A53C
	push {r3, lr}
	lsl r2, r2, #0x10
	mov r3, #0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223A550
MOD12_0223A550: ; 0x0223A550
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x16
	mov r1, #0x18
	add r5, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x18
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _0223A58C ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, _0223A590 ; =MOD12_0223A594
	str r6, [r4, #0xc]
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223A58C: .word 0x00007530
_0223A590: .word MOD12_0223A594

	thumb_func_start MOD12_0223A594
MOD12_0223A594: ; 0x0223A594
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldrb r0, [r1, #0x10]
	str r1, [sp]
	cmp r0, #0
	beq _0223A5A4
	b _0223A6F2
_0223A5A4:
	ldr r0, [sp]
	mov r1, #0x14
	ldrsb r0, [r0, r1]
	cmp r0, #0
	ble _0223A5B8
	sub r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x14]
	pop {r4, r5, r6, r7, pc}
_0223A5B8:
	ldr r0, [sp]
	mov r1, #0x13
	ldrsb r0, [r0, r1]
	cmp r0, #0
	ble _0223A5CC
	sub r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x13]
	pop {r4, r5, r6, r7, pc}
_0223A5CC:
	ldr r0, [sp]
	mov r1, #1
	strb r1, [r0, #0x13]
	ldr r0, [r0]
	mov r1, #2
	ldr r0, [r0, #0x30]
	bl FUN_0201886C
	mov ip, r0
	mov r0, #0
	str r0, [sp, #8]
	b _0223A64C
_0223A5E4:
	ldr r0, [sp]
	mov r1, #0x11
	ldrsb r1, [r0, r1]
	mov r0, #4
	sub r1, r0, r1
	ldr r0, _0223A710 ; =MOD12_02245F84
	ldrsb r1, [r0, r1]
	ldr r0, [sp, #8]
	add r0, r1, r0
	bmi _0223A646
	lsl r1, r0, #6
	mov r0, ip
	add r3, r0, r1
	ldr r0, [sp]
	mov r5, #0
	ldrb r1, [r0, #0x12]
	mov r0, #0xb
	mov r7, #0x3f
	sub r0, r0, r1
	lsl r1, r0, #1
	ldr r0, _0223A714 ; =MOD12_02245F8C
	str r5, [sp, #4]
	ldrh r1, [r0, r1]
	ldr r0, [sp, #8]
	lsl r7, r7, #0xa
	lsl r0, r0, #5
	add r6, r1, r0
	b _0223A640
_0223A61C:
	mov r4, #0
	b _0223A634
_0223A620:
	add r0, r5, r4
	lsl r2, r0, #1
	ldrh r0, [r3, r2]
	and r0, r7
	strh r0, [r3, r2]
	ldrh r1, [r3, r2]
	add r0, r6, r4
	add r4, r4, #1
	orr r0, r1
	strh r0, [r3, r2]
_0223A634:
	cmp r4, #8
	blt _0223A620
	ldr r0, [sp, #4]
	add r5, #8
	add r0, r0, #1
	str r0, [sp, #4]
_0223A640:
	ldr r0, [sp, #4]
	cmp r0, #4
	blt _0223A61C
_0223A646:
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
_0223A64C:
	ldr r0, [sp, #8]
	cmp r0, #4
	blt _0223A5E4
	ldr r0, [sp]
	mov r1, #0x11
	ldrsb r1, [r0, r1]
	cmp r1, #0
	ble _0223A6AE
	ldrb r0, [r0, #0x12]
	cmp r0, #0
	bne _0223A6AE
	mov r0, #5
	sub r1, r0, r1
	ldr r0, _0223A710 ; =MOD12_02245F84
	mov r7, #0x3f
	ldrsb r0, [r0, r1]
	lsl r7, r7, #0xa
	mov r6, #0x1d
	add r0, r0, #3
	lsl r1, r0, #6
	mov r0, ip
	add r3, r0, r1
	mov r0, #0
	mov r1, #2
	str r0, [sp, #4]
	lsl r1, r1, #8
	b _0223A6A8
_0223A682:
	ldr r0, [sp, #4]
	ldr r5, [sp, #4]
	lsl r4, r0, #1
	ldrh r0, [r3, r4]
	lsl r5, r5, #0x1d
	and r0, r7
	strh r0, [r3, r4]
	ldr r0, [sp, #4]
	ldrh r2, [r3, r4]
	lsr r0, r0, #0x1f
	sub r5, r5, r0
	ror r5, r6
	add r0, r0, r5
	add r0, r0, r1
	orr r0, r2
	strh r0, [r3, r4]
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
_0223A6A8:
	ldr r0, [sp, #4]
	cmp r0, #0x20
	blt _0223A682
_0223A6AE:
	ldr r0, [sp]
	mov r1, #2
	ldr r0, [r0]
	ldr r0, [r0, #0x30]
	bl FUN_0201AC68
	ldr r0, [sp]
	ldrb r0, [r0, #0x12]
	add r1, r0, #1
	ldr r0, [sp]
	strb r1, [r0, #0x12]
	ldrb r0, [r0, #0x12]
	cmp r0, #0xc
	blo _0223A70C
	ldr r1, [sp]
	mov r0, #0
	mov r2, #0x11
	strb r0, [r1, #0x12]
	ldrsb r1, [r1, r2]
	add r3, r1, #1
	ldr r1, [sp]
	strb r3, [r1, #0x11]
	strb r0, [r1, #0x14]
	add r0, r1, #0
	ldrsb r0, [r0, r2]
	cmp r0, #5
	blo _0223A70C
	add r0, r1, #0
	ldrb r0, [r0, #0x10]
	add r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x10]
	pop {r4, r5, r6, r7, pc}
_0223A6F2:
	add r0, r1, #0
	mov r2, #0
	ldr r0, [r0, #0xc]
	add r1, r1, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	ldr r0, [sp]
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_0223A70C:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223A710: .word MOD12_02245F84
_0223A714: .word MOD12_02245F8C

	thumb_func_start MOD12_0223A718
MOD12_0223A718: ; 0x0223A718
	push {r3, lr}
	mov r1, #0x12
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223A72C
MOD12_0223A72C: ; 0x0223A72C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x16
	mov r1, #0x1c
	add r5, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x1c
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _0223A770 ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, [sp]
	str r6, [r4, #0xc]
	ldrb r0, [r0]
	strb r0, [r4, #0x11]
	ldr r0, _0223A774 ; =MOD12_0223A778
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223A770: .word 0x00007530
_0223A774: .word MOD12_0223A778

	thumb_func_start MOD12_0223A778
MOD12_0223A778: ; 0x0223A778
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _0223A78A
	cmp r0, #1
	beq _0223A7B4
	b _0223A7F8
_0223A78A:
	ldrb r1, [r4, #0x11]
	ldr r0, [r4]
	bl MOD12_02239A10
	ldr r0, [r4]
	mov r1, #0
	ldr r0, [r0, #0x24]
	bl FUN_0200782C
	lsl r0, r0, #8
	str r0, [r4, #0x14]
	ldr r0, [r4]
	mov r1, #1
	ldr r0, [r0, #0x24]
	bl FUN_0200782C
	lsl r0, r0, #8
	str r0, [r4, #0x18]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
_0223A7B4:
	mov r0, #1
	ldr r1, [r4, #0x14]
	lsl r0, r0, #0xa
	sub r1, r1, r0
	mov r0, #0xe6
	lsl r0, r0, #8
	str r1, [r4, #0x14]
	cmp r1, r0
	bgt _0223A7CE
	str r0, [r4, #0x14]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
_0223A7CE:
	ldr r3, [r4, #0x14]
	ldr r0, [r4]
	asr r2, r3, #7
	lsr r2, r2, #0x18
	add r2, r3, r2
	ldr r0, [r0, #0x24]
	mov r1, #0
	asr r2, r2, #8
	bl FUN_02007558
	ldr r3, [r4, #0x18]
	ldr r0, [r4]
	asr r2, r3, #7
	lsr r2, r2, #0x18
	add r2, r3, r2
	ldr r0, [r0, #0x24]
	mov r1, #1
	asr r2, r2, #8
	bl FUN_02007558
	pop {r3, r4, r5, pc}
_0223A7F8:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_0223A814
MOD12_0223A814: ; 0x0223A814
	push {r3, lr}
	mov r1, #0x12
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223A828
MOD12_0223A828: ; 0x0223A828
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x16
	mov r1, #0x1c
	add r5, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x1c
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _0223A86C ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, [sp]
	str r6, [r4, #0xc]
	ldrb r0, [r0]
	strb r0, [r4, #0x11]
	ldr r0, _0223A870 ; =MOD12_0223A874
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223A86C: .word 0x00007530
_0223A870: .word MOD12_0223A874

	thumb_func_start MOD12_0223A874
MOD12_0223A874: ; 0x0223A874
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _0223A886
	cmp r0, #1
	beq _0223A8B4
	b _0223A8F8
_0223A886:
	ldr r0, [r4]
	ldr r0, [r0, #0x24]
	cmp r0, #0
	bne _0223A892
	bl ErrorHandling
_0223A892:
	ldr r0, [r4]
	mov r1, #0
	ldr r0, [r0, #0x24]
	bl FUN_0200782C
	lsl r0, r0, #8
	str r0, [r4, #0x14]
	ldr r0, [r4]
	mov r1, #1
	ldr r0, [r0, #0x24]
	bl FUN_0200782C
	lsl r0, r0, #8
	str r0, [r4, #0x18]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
_0223A8B4:
	mov r0, #1
	ldr r1, [r4, #0x14]
	lsl r0, r0, #0xa
	add r1, r1, r0
	mov r0, #5
	lsl r0, r0, #0xe
	str r1, [r4, #0x14]
	cmp r1, r0
	blt _0223A8CE
	str r0, [r4, #0x14]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
_0223A8CE:
	ldr r3, [r4, #0x14]
	ldr r0, [r4]
	asr r2, r3, #7
	lsr r2, r2, #0x18
	add r2, r3, r2
	ldr r0, [r0, #0x24]
	mov r1, #0
	asr r2, r2, #8
	bl FUN_02007558
	ldr r3, [r4, #0x18]
	ldr r0, [r4]
	asr r2, r3, #7
	lsr r2, r2, #0x18
	add r2, r3, r2
	ldr r0, [r0, #0x24]
	mov r1, #1
	asr r2, r2, #8
	bl FUN_02007558
	pop {r3, r4, r5, pc}
_0223A8F8:
	ldr r0, [r4]
	bl MOD12_02239A58
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_0223A918
MOD12_0223A918: ; 0x0223A918
	push {r3, lr}
	mov r1, #0x12
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223A92C
MOD12_0223A92C: ; 0x0223A92C
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	add r6, r1, #0
	mov r0, #0x16
	mov r1, #0x58
	add r5, r2, #0
	add r7, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x58
	bl MI_CpuFill8
	str r6, [r4]
	ldrh r0, [r5]
	ldr r2, _0223A988 ; =0x00007530
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, [sp]
	str r0, [r4, #0xc]
	ldrb r0, [r7]
	strb r0, [r4, #0x11]
	str r6, [r4, #0x2c]
	str r6, [r4, #0x38]
	add r0, r4, #0
	ldrb r1, [r7]
	add r0, #0x46
	strb r1, [r0]
	str r6, [r4, #0x48]
	ldrb r0, [r7]
	ldr r1, [r6, #0xc]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, r4, #0
	str r0, [r4, #0x24]
	ldr r0, _0223A98C ; =MOD12_0223A990
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223A988: .word 0x00007530
_0223A98C: .word MOD12_0223A990

	thumb_func_start MOD12_0223A990
MOD12_0223A990: ; 0x0223A990
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r4, r0, #0
	ldrb r0, [r5, #0x10]
	cmp r0, #0
	beq _0223A9A8
	cmp r0, #1
	beq _0223AA32
	cmp r0, #2
	beq _0223AA5C
	b _0223AA8A
_0223A9A8:
	ldr r0, _0223AAA8 ; =MOD12_0223AB54
	ldr r2, _0223AAAC ; =0x0000753A
	add r1, #0x2c
	bl FUN_0200CA44
	add r1, r5, #0
	ldr r0, _0223AAB0 ; =MOD12_0223ACFC
	ldr r2, _0223AAAC ; =0x0000753A
	add r1, #0x48
	bl FUN_0200CA44
	ldr r0, [r5, #0x38]
	ldr r1, [r0, #0xc]
	add r0, r5, #0
	add r0, #0x46
	ldrb r0, [r0]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #2
	bl FUN_02068E14
	add r4, r0, #0
	add r0, sp, #0
	mov r1, #0
	mov r2, #0x10
	bl MI_CpuFill8
	mov r0, #0x16
	str r0, [sp, #0xc]
	mov r0, #0x80
	add r4, #0x40
	str r0, [sp, #4]
	str r4, [sp, #8]
	ldr r1, [r5, #0x38]
	add r0, sp, #0
	ldr r2, [r1]
	add r1, r5, #0
	add r1, #0x46
	ldrb r1, [r1]
	lsl r1, r1, #2
	add r1, r2, r1
	add r1, #0xf8
	ldr r1, [r1]
	bl MOD17_021DD4F4
	add r1, r5, #0
	add r1, #0x46
	ldrb r1, [r1]
	ldr r2, [r5, #0x38]
	lsl r1, r1, #4
	add r2, r2, r1
	mov r1, #0xf2
	lsl r1, r1, #4
	str r0, [r2, r1]
	add r0, r5, #0
	add r0, #0x46
	ldrb r0, [r0]
	ldr r2, [r5, #0x38]
	lsl r0, r0, #4
	add r0, r2, r0
	ldr r0, [r0, r1]
	mov r1, #0
	bl MOD17_021DD594
	ldrb r0, [r5, #0x10]
	add sp, #0x10
	add r0, r0, #1
	strb r0, [r5, #0x10]
	pop {r3, r4, r5, pc}
_0223AA32:
	add r0, r5, #0
	add r0, #0x35
	ldrb r0, [r0]
	cmp r0, #1
	bne _0223AAA2
	ldr r0, _0223AAB4 ; =MOD12_0223AAF8
	ldr r2, _0223AAAC ; =0x0000753A
	add r1, #0x14
	bl FUN_0200CA44
	add r1, r5, #0
	ldr r0, _0223AAB8 ; =MOD12_0223ABD4
	ldr r2, _0223AAAC ; =0x0000753A
	add r1, #0x38
	bl FUN_0200CA44
	ldrb r0, [r5, #0x10]
	add sp, #0x10
	add r0, r0, #1
	strb r0, [r5, #0x10]
	pop {r3, r4, r5, pc}
_0223AA5C:
	add r0, r5, #0
	add r0, #0x29
	ldrb r0, [r0]
	cmp r0, #1
	bne _0223AAA2
	add r0, r5, #0
	add r0, #0x45
	ldrb r0, [r0]
	cmp r0, #1
	bne _0223AAA2
	add r0, r5, #0
	add r0, #0x55
	ldrb r0, [r0]
	cmp r0, #1
	bne _0223AAA2
	ldr r0, _0223AABC ; =0x000006E5
	bl FUN_020054C8
	ldrb r0, [r5, #0x10]
	add sp, #0x10
	add r0, r0, #1
	strb r0, [r5, #0x10]
	pop {r3, r4, r5, pc}
_0223AA8A:
	mov r2, #0
	ldr r0, [r5, #0xc]
	add r1, r5, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_0223AAA2:
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_0223AAA8: .word MOD12_0223AB54
_0223AAAC: .word 0x0000753A
_0223AAB0: .word MOD12_0223ACFC
_0223AAB4: .word MOD12_0223AAF8
_0223AAB8: .word MOD12_0223ABD4
_0223AABC: .word 0x000006E5

	thumb_func_start MOD12_0223AAC0
MOD12_0223AAC0: ; 0x0223AAC0
	push {r3}
	sub sp, #0xc
	add r2, sp, #0
	mov r1, #0
	str r1, [r2]
	str r1, [r2, #4]
	str r1, [r2, #8]
	ldr r1, [r0, #0x20]
	ldr r2, [sp]
	ldr r1, [r1]
	ldr r1, [r1, #4]
	add r1, r2, r1
	str r1, [r0, #0x28]
	ldr r1, [r0, #0x20]
	ldr r2, [sp, #4]
	ldr r1, [r1]
	ldr r1, [r1, #8]
	add r1, r2, r1
	str r1, [r0, #0x2c]
	ldr r1, [r0, #0x20]
	ldr r2, [sp, #8]
	ldr r1, [r1]
	ldr r1, [r1, #0xc]
	add r1, r2, r1
	str r1, [r0, #0x30]
	add sp, #0xc
	pop {r3}
	bx lr

	thumb_func_start MOD12_0223AAF8
MOD12_0223AAF8: ; 0x0223AAF8
	push {r4, lr}
	add r4, r1, #0
	ldrb r2, [r4, #0x14]
	cmp r2, #0
	beq _0223AB08
	cmp r2, #1
	beq _0223AB2C
	b _0223AB44
_0223AB08:
	mov r0, #0
	str r0, [r4]
	ldr r0, [r4, #0x10]
	str r0, [r4, #8]
	mov r0, #0x16
	bl MOD08_02228218
	str r0, [r4, #0xc]
	bl MOD08_02228524
	ldr r0, [r4, #0xc]
	ldr r1, _0223AB50 ; =MOD12_0223AAC0
	bl MOD08_02228574
	ldrb r0, [r4, #0x14]
	add r0, r0, #1
	strb r0, [r4, #0x14]
	pop {r4, pc}
_0223AB2C:
	ldr r0, [r4, #0xc]
	bl MOD08_022285B4
	cmp r0, #0
	bne _0223AB4C
	ldr r0, [r4, #0xc]
	bl MOD08_02228618
	ldrb r0, [r4, #0x14]
	add r0, r0, #1
	strb r0, [r4, #0x14]
	pop {r4, pc}
_0223AB44:
	mov r1, #1
	strb r1, [r4, #0x15]
	bl FUN_0200CAB4
_0223AB4C:
	pop {r4, pc}
	nop
_0223AB50: .word MOD12_0223AAC0

	thumb_func_start MOD12_0223AB54
MOD12_0223AB54: ; 0x0223AB54
	push {r3, r4, r5, lr}
	sub sp, #0x28
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #8]
	cmp r0, #0
	beq _0223AB6C
	cmp r0, #1
	beq _0223AB86
	cmp r0, #2
	beq _0223ABB6
	b _0223ABC0
_0223AB6C:
	ldrb r0, [r4, #0xa]
	add r0, r0, #1
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0xa]
	cmp r0, #1
	blo _0223ABD0
	mov r0, #0
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #8]
	add sp, #0x28
	add r0, r0, #1
	strb r0, [r4, #8]
	pop {r3, r4, r5, pc}
_0223AB86:
	mov r0, #0xe
	str r0, [sp]
	mov r0, #0x16
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, [r4]
	ldr r0, [r0, #0x28]
	str r0, [sp, #0x1c]
	ldr r0, [r4]
	ldr r0, [r0, #0x50]
	str r0, [sp, #0x20]
	mov r0, #1
	str r0, [sp, #0x14]
	add r0, sp, #0
	bl MOD08_02229918
	str r0, [r4, #4]
	ldrb r0, [r4, #8]
	add sp, #0x28
	add r0, r0, #1
	strb r0, [r4, #8]
	pop {r3, r4, r5, pc}
_0223ABB6:
	ldr r0, [r4, #4]
	bl MOD08_022299E8
	cmp r0, #1
	beq _0223ABD0
_0223ABC0:
	ldr r0, [r4, #4]
	bl MOD08_02229A2C
	mov r0, #1
	strb r0, [r4, #9]
	add r0, r5, #0
	bl FUN_0200CAB4
_0223ABD0:
	add sp, #0x28
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_0223ABD4
MOD12_0223ABD4: ; 0x0223ABD4
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	ldr r1, [r0, #0xc]
	ldrb r0, [r4, #0xe]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #2
	bl FUN_02068E14
	add r6, r0, #0
	ldrb r0, [r4, #0xc]
	cmp r0, #0
	beq _0223ABFA
	cmp r0, #1
	beq _0223AC4A
	b _0223ACE8
_0223ABFA:
	mov r1, #0
	str r1, [r4, #4]
	str r1, [r4, #8]
	ldrb r0, [r4, #0xe]
	mov r3, #0xf2
	ldr r2, [r4]
	lsl r0, r0, #4
	add r0, r2, r0
	lsl r3, r3, #4
	ldr r0, [r0, r3]
	add r2, r1, #0
	add r3, #0xe0
	bl MOD05_021DD60C
	ldrb r1, [r4, #0xe]
	ldr r2, [r4]
	mov r0, #0x80
	lsl r1, r1, #4
	add r2, r2, r1
	ldr r1, _0223ACF8 ; =0x00000F24
	str r0, [r2, r1]
	ldrb r2, [r4, #0xe]
	ldr r3, [r4]
	mov r0, #0x68
	lsl r2, r2, #4
	add r3, r3, r2
	add r2, r1, #4
	str r0, [r3, r2]
	ldrb r0, [r4, #0xe]
	ldr r2, [r4]
	lsl r0, r0, #4
	add r2, r2, r0
	sub r0, r1, #4
	ldr r0, [r2, r0]
	mov r1, #1
	bl MOD17_021DD594
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_0223AC4A:
	mov r0, #2
	ldr r1, [r4, #4]
	lsl r0, r0, #8
	add r1, r1, r0
	str r1, [r4, #4]
	ldr r1, [r4, #8]
	add r1, r1, r0
	str r1, [r4, #8]
	ldr r2, [r4, #4]
	lsl r1, r0, #3
	cmp r2, r1
	blt _0223AC68
	lsl r0, r0, #3
	str r0, [r4, #4]
	str r0, [r4, #8]
_0223AC68:
	ldrb r0, [r4, #0xe]
	mov r3, #0xf2
	ldr r1, [r4]
	lsl r0, r0, #4
	add r0, r1, r0
	lsl r3, r3, #4
	ldr r0, [r0, r3]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	add r3, #0xe0
	bl MOD05_021DD60C
	ldrb r0, [r4, #0xe]
	mov r2, #0xf2
	lsl r2, r2, #4
	lsl r1, r0, #4
	ldr r0, [r4]
	add r3, r0, r1
	add r1, r2, #4
	ldr r0, [r3, r2]
	add r2, #8
	ldr r1, [r3, r1]
	ldr r2, [r3, r2]
	add r3, r6, #0
	bl MOD17_021DD678
	mov r0, #1
	ldr r1, [r4, #4]
	lsl r0, r0, #0xc
	cmp r1, r0
	blt _0223ACF2
	ldr r0, [r4]
	mov r2, #0
	ldr r1, [r0, #0xc]
	ldrb r0, [r4, #0xe]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #5
	bl GetMonData
	add r2, r0, #0
	mov r0, #0x7f
	str r0, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r3, #0x16
	str r3, [sp, #8]
	ldr r3, [r4]
	lsl r2, r2, #0x10
	ldr r5, [r3]
	ldrb r3, [r4, #0xe]
	add r0, #0xdd
	lsr r2, r2, #0x10
	lsl r3, r3, #2
	add r3, r5, r3
	ldr r0, [r3, r0]
	add r3, r1, #0
	bl FUN_02069FB0
	ldrb r0, [r4, #0xc]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, r6, pc}
_0223ACE8:
	mov r0, #1
	strb r0, [r4, #0xd]
	add r0, r5, #0
	bl FUN_0200CAB4
_0223ACF2:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_0223ACF8: .word 0x00000F24

	thumb_func_start MOD12_0223ACFC
MOD12_0223ACFC: ; 0x0223ACFC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0xc]
	cmp r0, #4
	bls _0223AD0A
	b _0223AE32
_0223AD0A:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223AD16: ; jump table
	.short _0223AD20 - _0223AD16 - 2 ; case 0
	.short _0223AD46 - _0223AD16 - 2 ; case 1
	.short _0223AD68 - _0223AD16 - 2 ; case 2
	.short _0223ADD6 - _0223AD16 - 2 ; case 3
	.short _0223ADEE - _0223AD16 - 2 ; case 4
_0223AD20:
	ldr r0, [r4]
	ldr r0, [r0, #0x24]
	cmp r0, #0
	bne _0223AD2C
	bl ErrorHandling
_0223AD2C:
	ldrb r0, [r4, #0xf]
	add r0, r0, #1
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xf]
	cmp r0, #1
	bhi _0223AD3A
	b _0223AE42
_0223AD3A:
	mov r0, #0
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223AD46:
	ldr r0, [r4]
	mov r1, #0
	ldr r0, [r0, #0x24]
	bl FUN_0200782C
	lsl r0, r0, #8
	str r0, [r4, #4]
	ldr r0, [r4]
	mov r1, #1
	ldr r0, [r0, #0x24]
	bl FUN_0200782C
	lsl r0, r0, #8
	str r0, [r4, #8]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_0223AD68:
	ldrb r1, [r4, #0xe]
	mov r0, #1
	tst r0, r1
	ldr r0, [r4]
	beq _0223AD9A
	ldr r3, [r4, #4]
	ldr r0, [r0, #0x24]
	asr r2, r3, #7
	lsr r2, r2, #0x18
	add r2, r3, r2
	mov r1, #0
	asr r2, r2, #8
	bl FUN_02007558
	ldr r3, [r4, #8]
	ldr r0, [r4]
	asr r2, r3, #7
	lsr r2, r2, #0x18
	add r2, r3, r2
	ldr r0, [r0, #0x24]
	mov r1, #1
	asr r2, r2, #8
	bl FUN_02007558
	b _0223ADC2
_0223AD9A:
	ldr r3, [r4, #4]
	ldr r0, [r0, #0x24]
	asr r2, r3, #7
	lsr r2, r2, #0x18
	add r2, r3, r2
	mov r1, #0
	asr r2, r2, #8
	bl FUN_02007558
	ldr r3, [r4, #8]
	ldr r0, [r4]
	asr r2, r3, #7
	lsr r2, r2, #0x18
	add r2, r3, r2
	asr r2, r2, #8
	ldr r0, [r0, #0x24]
	mov r1, #1
	sub r2, r2, #3
	bl FUN_02007558
_0223ADC2:
	ldrb r0, [r4, #0xe]
	add r0, r0, #1
	strb r0, [r4, #0xe]
	ldrb r0, [r4, #0xe]
	cmp r0, #3
	blo _0223AE42
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223ADD6:
	ldrb r0, [r4, #0xf]
	add r0, r0, #1
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xf]
	cmp r0, #7
	blo _0223AE42
	mov r0, #0
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
_0223ADEE:
	mov r0, #1
	ldr r1, [r4, #4]
	lsl r0, r0, #0xa
	add r1, r1, r0
	mov r0, #5
	lsl r0, r0, #0xe
	str r1, [r4, #4]
	cmp r1, r0
	blt _0223AE08
	str r0, [r4, #4]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
_0223AE08:
	ldr r3, [r4, #4]
	ldr r0, [r4]
	asr r2, r3, #7
	lsr r2, r2, #0x18
	add r2, r3, r2
	ldr r0, [r0, #0x24]
	mov r1, #0
	asr r2, r2, #8
	bl FUN_02007558
	ldr r3, [r4, #8]
	ldr r0, [r4]
	asr r2, r3, #7
	lsr r2, r2, #0x18
	add r2, r3, r2
	ldr r0, [r0, #0x24]
	mov r1, #1
	asr r2, r2, #8
	bl FUN_02007558
	pop {r3, r4, r5, pc}
_0223AE32:
	ldr r0, [r4]
	bl MOD12_02239A58
	mov r0, #1
	strb r0, [r4, #0xd]
	add r0, r5, #0
	bl FUN_0200CAB4
_0223AE42:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_0223AE44
MOD12_0223AE44: ; 0x0223AE44
	push {r3, lr}
	mov r1, #0x12
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223AE58
MOD12_0223AE58: ; 0x0223AE58
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	str r1, [sp]
	mov r0, #0x16
	mov r1, #0x1c
	add r6, r2, #0
	add r5, r3, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x1c
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp]
	ldr r2, _0223AEB8 ; =0x00007530
	str r0, [r4]
	ldrh r0, [r6]
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r6, #2]
	strh r0, [r4, #6]
	ldrh r0, [r6, #4]
	strh r0, [r4, #8]
	ldrh r0, [r6, #6]
	strh r0, [r4, #0xa]
	str r7, [r4, #0xc]
	ldrb r0, [r5]
	strb r0, [r4, #0x11]
	ldrb r0, [r5, #3]
	strb r0, [r4, #0x13]
	ldrb r0, [r5, #4]
	strb r0, [r4, #0x14]
	ldrb r0, [r5, #5]
	strb r0, [r4, #0x15]
	ldrb r0, [r5, #6]
	strb r0, [r4, #0x16]
	ldrb r0, [r5, #7]
	strb r0, [r4, #0x17]
	ldrb r0, [r5, #9]
	strb r0, [r4, #0x19]
	ldrb r0, [r5, #8]
	strb r0, [r4, #0x18]
	ldr r0, _0223AEBC ; =MOD12_0223AEC0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223AEB8: .word 0x00007530
_0223AEBC: .word MOD12_0223AEC0

	thumb_func_start MOD12_0223AEC0
MOD12_0223AEC0: ; 0x0223AEC0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _0223AED6
	cmp r0, #1
	beq _0223AF0E
	cmp r0, #2
	beq _0223AF20
	b _0223AF58
_0223AED6:
	ldrb r0, [r4, #0x17]
	cmp r0, #0
	beq _0223AF08
	ldr r0, [r4]
	mov r1, #1
	add r0, #0x34
	add r2, r1, #0
	mov r3, #0xe
	bl FUN_0200D0BC
	ldr r0, [r4]
	mov r1, #1
	ldr r0, [r0, #0x30]
	bl FUN_0201AC68
	add r2, r4, #0
	ldrb r1, [r4, #0x17]
	ldr r0, [r4]
	add r2, #0x13
	bl MOD12_02239B48
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223AF08:
	mov r0, #0x64
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223AF0E:
	ldr r0, [r4]
	bl MOD12_02239B7C
	cmp r0, #0
	bne _0223AF70
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223AF20:
	ldrb r0, [r4, #0x12]
	add r0, r0, #1
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x19]
	cmp r0, #1
	bne _0223AF34
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223AF34:
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x18]
	cmp r1, r0
	blo _0223AF70
	ldr r0, [r4]
	mov r1, #1
	add r0, #0x34
	bl FUN_0200D0E0
	ldr r0, [r4]
	mov r1, #1
	ldr r0, [r0, #0x30]
	bl FUN_0201AC68
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223AF58:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_0223AF70:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_0223AF74
MOD12_0223AF74: ; 0x0223AF74
	push {r3, lr}
	mov r1, #0x12
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223AF88
MOD12_0223AF88: ; 0x0223AF88
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	str r1, [sp]
	mov r0, #0x16
	mov r1, #0x18
	add r5, r2, #0
	add r6, r3, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x18
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp]
	ldr r2, _0223AFD8 ; =0x00007530
	str r0, [r4]
	ldrh r0, [r5]
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	str r7, [r4, #0xc]
	mov r0, #0xa
	ldrsb r0, [r6, r0]
	strb r0, [r4, #0x11]
	mov r0, #0xb
	ldrsb r0, [r6, r0]
	strb r0, [r4, #0x12]
	mov r0, #0xc
	ldrsb r0, [r6, r0]
	strb r0, [r4, #0x13]
	ldr r0, _0223AFDC ; =MOD12_0223AFE0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223AFD8: .word 0x00007530
_0223AFDC: .word MOD12_0223AFE0

	thumb_func_start MOD12_0223AFE0
MOD12_0223AFE0: ; 0x0223AFE0
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _0223AFF4
	cmp r0, #1
	beq _0223B06C
	b _0223B0A8
_0223AFF4:
	ldr r0, [r4]
	ldr r1, [r0]
	ldr r0, _0223B0C4 ; =0x00000171
	ldrb r0, [r1, r0]
	cmp r0, #1
	bne _0223B04E
	ldr r0, _0223B0C8 ; =0x04000048
	ldr r1, _0223B0CC ; =0xFFFFC0FF
	ldrh r2, [r0]
	and r2, r1
	mov r1, #0x1f
	lsl r1, r1, #8
	orr r1, r2
	strh r1, [r0]
	ldrh r2, [r0, #2]
	mov r1, #0x3f
	bic r2, r1
	mov r1, #0x1f
	orr r2, r1
	mov r1, #0x20
	orr r2, r1
	strh r2, [r0, #2]
	lsl r3, r1, #0x15
	ldr r2, [r3]
	ldr r0, _0223B0D0 ; =0xFFFF1FFF
	and r2, r0
	lsl r0, r1, #9
	orr r0, r2
	str r0, [r3]
	ldr r1, [r4]
	ldr r0, _0223B0D4 ; =0x00000F64
	mov r2, #0xf0
	strb r2, [r1, r0]
	ldr r2, [r4]
	mov r3, #0
	add r1, r0, #1
	strb r3, [r2, r1]
	add r1, r0, #2
	ldr r2, [r4]
	mov r3, #0xff
	strb r3, [r2, r1]
	ldr r1, [r4]
	mov r2, #0x10
	add r0, r0, #3
	strb r2, [r1, r0]
_0223B04E:
	mov r0, #1
	str r0, [sp]
	mov r1, #0x12
	mov r2, #0x11
	ldrb r0, [r4, #0x13]
	ldrsb r1, [r4, r1]
	ldrsb r2, [r4, r2]
	mov r3, #0x3d
	bl FUN_0200A208
	ldrb r0, [r4, #0x10]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223B06C:
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #1
	bne _0223B0C0
	mov r1, #0
	str r1, [sp]
	mov r0, #0xd0
	str r0, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	ldr r0, [r0, #0x50]
	add r3, r1, #0
	bl FUN_02003914
	mov r2, #0
	str r2, [sp]
	mov r0, #0xe0
	str r0, [sp, #4]
	ldr r0, [r4]
	mov r1, #2
	ldr r0, [r0, #0x50]
	add r3, r2, #0
	bl FUN_02003914
	ldrb r0, [r4, #0x10]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223B0A8:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_0223B0C0:
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223B0C4: .word 0x00000171
_0223B0C8: .word 0x04000048
_0223B0CC: .word 0xFFFFC0FF
_0223B0D0: .word 0xFFFF1FFF
_0223B0D4: .word 0x00000F64

	thumb_func_start MOD12_0223B0D8
MOD12_0223B0D8: ; 0x0223B0D8
	push {r3, lr}
	lsl r2, r2, #0x10
	mov r3, #0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223B0EC
MOD12_0223B0EC: ; 0x0223B0EC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x16
	mov r1, #0x1c
	add r5, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x1c
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _0223B128 ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, _0223B12C ; =MOD12_0223B130
	str r6, [r4, #0xc]
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223B128: .word 0x00007530
_0223B12C: .word MOD12_0223B130

	thumb_func_start MOD12_0223B130
MOD12_0223B130: ; 0x0223B130
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r1, #0x18]
	str r1, [sp]
	add r1, r0, #1
	ldr r0, [sp]
	cmp r1, #0x1e
	str r1, [r0, #0x18]
	bne _0223B14C
	mov r1, #0x1e
	strb r1, [r0, #0x13]
	mov r1, #1
	strb r1, [r0, #0x15]
_0223B14C:
	ldr r0, [sp]
	ldr r0, [r0]
	ldr r1, [r0]
	ldr r0, _0223B344 ; =0x00000171
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _0223B186
	ldr r0, [sp]
	ldr r0, [r0, #0x18]
	cmp r0, #0x1e
	bge _0223B186
	ldr r0, _0223B348 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	bne _0223B174
	ldr r0, _0223B34C ; =gMain + 0x40
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	beq _0223B186
_0223B174:
	ldr r0, [sp]
	mov r1, #0x1e
	str r1, [r0, #0x18]
	ldr r1, [sp]
	mov r0, #0
	strb r0, [r1, #0x13]
	mov r2, #1
	strb r2, [r1, #0x15]
	b _0223B194
_0223B186:
	ldr r0, [sp]
	ldr r0, [r0, #0x18]
	cmp r0, #0x1e
	ble _0223B192
	mov r0, #0
	b _0223B194
_0223B192:
	mov r0, #1
_0223B194:
	ldr r1, [sp]
	ldrb r1, [r1, #0x10]
	cmp r1, #0
	beq _0223B19E
	b _0223B316
_0223B19E:
	ldr r1, [sp]
	mov r2, #0x14
	ldrsb r1, [r1, r2]
	cmp r1, #0
	ble _0223B1B2
	ldr r0, [sp]
	sub r1, r1, #1
	strb r1, [r0, #0x14]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0223B1B2:
	ldr r1, [sp]
	mov r2, #0x13
	ldrsb r1, [r1, r2]
	cmp r1, #0
	ble _0223B1C6
	ldr r0, [sp]
	sub r1, r1, #1
	strb r1, [r0, #0x13]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0223B1C6:
	ldr r1, [sp]
	strb r0, [r1, #0x13]
	add r0, r1, #0
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _0223B1DE
	ldr r0, _0223B350 ; =0x000006ED
	bl FUN_020054C8
	ldr r0, [sp]
	mov r1, #0
	strb r1, [r0, #0x15]
_0223B1DE:
	ldr r0, [sp]
	mov r1, #2
	ldr r0, [r0]
	ldr r0, [r0, #0x30]
	bl FUN_0201886C
	mov ip, r0
	mov r0, #0
	str r0, [sp, #8]
	b _0223B252
_0223B1F2:
	ldr r0, [sp]
	mov r1, #0x11
	ldrsb r1, [r0, r1]
	ldr r0, _0223B354 ; =MOD12_02245F84
	ldrsb r1, [r0, r1]
	ldr r0, [sp, #8]
	add r0, r1, r0
	bmi _0223B24C
	lsl r1, r0, #6
	mov r0, ip
	add r3, r0, r1
	ldr r0, [sp]
	mov r5, #0
	ldrb r0, [r0, #0x12]
	mov r7, #0x3f
	str r5, [sp, #4]
	lsl r1, r0, #1
	ldr r0, _0223B358 ; =MOD12_02245F8C
	lsl r7, r7, #0xa
	ldrh r1, [r0, r1]
	ldr r0, [sp, #8]
	lsl r0, r0, #5
	add r6, r1, r0
	b _0223B246
_0223B222:
	mov r4, #0
	b _0223B23A
_0223B226:
	add r0, r5, r4
	lsl r2, r0, #1
	ldrh r0, [r3, r2]
	and r0, r7
	strh r0, [r3, r2]
	ldrh r1, [r3, r2]
	add r0, r6, r4
	add r4, r4, #1
	orr r0, r1
	strh r0, [r3, r2]
_0223B23A:
	cmp r4, #8
	blt _0223B226
	ldr r0, [sp, #4]
	add r5, #8
	add r0, r0, #1
	str r0, [sp, #4]
_0223B246:
	ldr r0, [sp, #4]
	cmp r0, #4
	blt _0223B222
_0223B24C:
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
_0223B252:
	ldr r0, [sp, #8]
	cmp r0, #4
	blt _0223B1F2
	ldr r0, [sp]
	mov r1, #0x11
	ldrsb r1, [r0, r1]
	cmp r1, #0
	ble _0223B294
	ldrb r0, [r0, #0x12]
	cmp r0, #0
	bne _0223B294
	ldr r0, _0223B354 ; =MOD12_02245F84
	sub r1, r1, #1
	ldrsb r0, [r0, r1]
	lsl r1, r0, #6
	mov r0, ip
	add r3, r0, r1
	mov r0, #0
	mov r1, #0x3f
	str r0, [sp, #4]
	lsl r1, r1, #0xa
	b _0223B28E
_0223B27E:
	ldr r0, [sp, #4]
	lsl r2, r0, #1
	ldrh r0, [r3, r2]
	and r0, r1
	strh r0, [r3, r2]
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
_0223B28E:
	ldr r0, [sp, #4]
	cmp r0, #0x20
	blt _0223B27E
_0223B294:
	ldr r0, [sp]
	mov r1, #2
	ldr r0, [r0]
	ldr r0, [r0, #0x30]
	bl FUN_0201AC68
	ldr r0, [sp]
	mov r1, #0xc
	ldrb r0, [r0, #0x12]
	lsl r0, r0, #5
	bl _u32_div_f
	ldr r1, [sp]
	mov r2, #0x11
	ldrsb r2, [r1, r2]
	ldr r1, _0223B354 ; =MOD12_02245F84
	ldrsb r1, [r1, r2]
	add r1, r1, #4
	lsl r1, r1, #3
	sub r2, r1, r0
	ldr r0, [sp]
	ldr r1, _0223B35C ; =0x00000F63
	ldr r0, [r0]
	strb r2, [r0, r1]
	ldr r0, [sp]
	ldr r0, [r0]
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _0223B2DE
	ldr r2, _0223B360 ; =0x04000050
	mov r0, #0
	strh r0, [r2]
	sub r2, #0x50
	ldr r1, [r2]
	ldr r0, _0223B364 ; =0xFFFF1FFF
	and r0, r1
	str r0, [r2]
_0223B2DE:
	ldr r0, [sp]
	ldrb r0, [r0, #0x12]
	add r1, r0, #1
	ldr r0, [sp]
	strb r1, [r0, #0x12]
	ldrb r0, [r0, #0x12]
	cmp r0, #0xc
	blo _0223B340
	ldr r1, [sp]
	mov r0, #0
	mov r2, #0x11
	strb r0, [r1, #0x12]
	ldrsb r1, [r1, r2]
	add r3, r1, #1
	ldr r1, [sp]
	strb r3, [r1, #0x11]
	strb r0, [r1, #0x14]
	add r0, r1, #0
	ldrsb r0, [r0, r2]
	cmp r0, #5
	blo _0223B340
	add r0, r1, #0
	ldrb r0, [r0, #0x10]
	add r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x10]
	pop {r4, r5, r6, r7, pc}
_0223B316:
	ldr r3, _0223B360 ; =0x04000050
	mov r2, #0
	strh r2, [r3]
	sub r3, #0x50
	ldr r1, [r3]
	ldr r0, _0223B364 ; =0xFFFF1FFF
	and r0, r1
	str r0, [r3]
	ldr r0, [sp]
	ldr r1, [sp]
	ldr r0, [r0, #0xc]
	add r1, r1, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	ldr r0, [sp]
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_0223B340:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223B344: .word 0x00000171
_0223B348: .word gMain
_0223B34C: .word gMain + 0x40
_0223B350: .word 0x000006ED
_0223B354: .word MOD12_02245F84
_0223B358: .word MOD12_02245F8C
_0223B35C: .word 0x00000F63
_0223B360: .word 0x04000050
_0223B364: .word 0xFFFF1FFF

	thumb_func_start MOD12_0223B368
MOD12_0223B368: ; 0x0223B368
	push {r3, lr}
	mov r1, #0x12
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223B37C
MOD12_0223B37C: ; 0x0223B37C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x16
	mov r1, #0x14
	add r5, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x14
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, [sp]
	str r6, [r4, #0xc]
	ldrh r0, [r0, #0x10]
	bl FUN_020054C8
	ldr r0, _0223B3C0 ; =MOD12_0223B3C8
	ldr r2, _0223B3C4 ; =0x00007530
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223B3C0: .word MOD12_0223B3C8
_0223B3C4: .word 0x00007530

	thumb_func_start MOD12_0223B3C8
MOD12_0223B3C8: ; 0x0223B3C8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r1, [r4]
	ldr r0, _0223B3F4 ; =0x000004F9
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _0223B3F0
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_0223B3F0:
	pop {r3, r4, r5, pc}
	nop
_0223B3F4: .word 0x000004F9

	thumb_func_start MOD12_0223B3F8
MOD12_0223B3F8: ; 0x0223B3F8
	push {r4, lr}
	mov r0, #0x17
	mov r1, #0xf4
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0xf4
	add r4, r0, #0
	bl MI_CpuFill8
	mov r1, #0
	add r0, r4, #0
	mvn r1, r1
	add r0, #0x96
	strb r1, [r0]
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_0223B41C
MOD12_0223B41C: ; 0x0223B41C
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	ldr r6, _0223B470 ; =MOD12_022460DC
	add r5, r0, #0
	add r7, r4, #0
_0223B426:
	add r1, r4, #4
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	add r2, r6, #0
	add r3, r7, #0
	bl FUN_02016C18
	add r1, r4, #4
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	mov r2, #0
	bl FUN_02018768
	add r1, r4, #4
	lsl r1, r1, #0x18
	mov r2, #0
	add r0, r5, #0
	lsr r1, r1, #0x18
	add r3, r2, #0
	bl FUN_020179E0
	add r1, r4, #4
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add r4, r4, #1
	add r6, #0x1c
	cmp r4, #4
	blo _0223B426
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223B470: .word MOD12_022460DC

	thumb_func_start MOD12_0223B474
MOD12_0223B474: ; 0x0223B474
	push {r4, r5, r6, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r4, #0
_0223B47C:
	add r0, r4, #4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, r6, #0
	bl FUN_0201797C
	add r1, r4, #4
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	bl FUN_020178A0
	add r4, r4, #1
	cmp r4, #4
	blo _0223B47C
	pop {r4, r5, r6, pc}

	thumb_func_start MOD12_0223B49C
MOD12_0223B49C: ; 0x0223B49C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	bl MOD12_0223B3F8
	add r4, r0, #0
	str r5, [r4]
	str r6, [r4, #4]
	mov r0, #6
	mov r1, #0x17
	bl FUN_02011744
	str r0, [r4, #0x18]
	add r0, r4, #0
	bl MOD12_0223B4F8
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start MOD12_0223B4C0
MOD12_0223B4C0: ; 0x0223B4C0
	push {r4, lr}
	add r4, r0, #0
	bl MOD12_0223B710
	add r0, r4, #0
	mov r1, #1
	bl MOD12_0223BE50
	ldr r0, [r4, #0x18]
	bl FUN_020117BC
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_0223B4E0
MOD12_0223B4E0: ; 0x0223B4E0
	push {r4, lr}
	add r4, r0, #0
	bl MOD12_0223B940
	add r0, r4, #0
	bl MOD12_0223BA0C
	add r0, r4, #0
	mov r1, #0
	bl MOD12_0223BE10
	pop {r4, pc}

	thumb_func_start MOD12_0223B4F8
MOD12_0223B4F8: ; 0x0223B4F8
	push {r3, r4, r5, lr}
	sub sp, #0x10
	mov r1, #6
	add r4, r0, #0
	mov r0, #0x17
	lsl r1, r1, #0xc
	bl AllocFromHeap
	add r1, r4, #0
	add r1, #0xd0
	str r0, [r1]
	mov r1, #6
	mov r0, #0x17
	lsl r1, r1, #0xc
	bl AllocFromHeap
	add r1, r4, #0
	add r1, #0xd4
	str r0, [r1]
	mov r1, #0x1b
	mov r0, #0x17
	lsl r1, r1, #8
	bl AllocFromHeap
	add r1, r4, #0
	add r1, #0xd8
	str r0, [r1]
	mov r1, #2
	mov r0, #0x17
	lsl r1, r1, #0xa
	bl AllocFromHeap
	add r1, r4, #0
	add r1, #0xdc
	str r0, [r1]
	mov r1, #2
	mov r0, #0x17
	lsl r1, r1, #0xa
	bl AllocFromHeap
	add r1, r4, #0
	add r1, #0xe0
	str r0, [r1]
	mov r1, #2
	mov r0, #0x17
	lsl r1, r1, #0xa
	bl AllocFromHeap
	add r1, r4, #0
	add r1, #0xe4
	str r0, [r1]
	mov r1, #2
	mov r0, #0x17
	lsl r1, r1, #0xa
	bl AllocFromHeap
	add r1, r4, #0
	add r1, #0xe8
	str r0, [r1]
	mov r1, #2
	mov r0, #0x17
	lsl r1, r1, #8
	bl AllocFromHeap
	add r1, r4, #0
	add r1, #0xec
	str r0, [r1]
	mov r1, #2
	mov r0, #0x17
	lsl r1, r1, #8
	bl AllocFromHeap
	add r1, r4, #0
	add r1, #0xf0
	str r0, [r1]
	mov r0, #0x17
	str r0, [sp]
	mov r0, #0x2d
	mov r1, #9
	mov r2, #1
	add r3, sp, #0xc
	bl FUN_02006BB0
	add r5, r0, #0
	ldr r0, [sp, #0xc]
	add r1, r4, #0
	add r1, #0xd0
	mov r2, #6
	ldr r0, [r0, #0x14]
	ldr r1, [r1]
	lsl r2, r2, #0xc
	bl MIi_CpuCopy32
	add r0, r5, #0
	bl FreeToHeap
	mov r0, #0x17
	str r0, [sp]
	mov r0, #0x2d
	mov r1, #0x11
	mov r2, #1
	add r3, sp, #0xc
	bl FUN_02006BB0
	add r5, r0, #0
	ldr r0, [sp, #0xc]
	add r1, r4, #0
	add r1, #0xd4
	mov r2, #6
	ldr r0, [r0, #0x14]
	ldr r1, [r1]
	lsl r2, r2, #0xc
	bl MIi_CpuCopy32
	add r0, r5, #0
	bl FreeToHeap
	mov r0, #0x17
	str r0, [sp]
	mov r0, #0x2d
	mov r1, #0xf
	mov r2, #1
	add r3, sp, #0xc
	bl FUN_02006BB0
	add r5, r0, #0
	ldr r0, [sp, #0xc]
	add r1, r4, #0
	add r1, #0xd8
	mov r2, #0x1b
	ldr r0, [r0, #0x14]
	ldr r1, [r1]
	lsl r2, r2, #8
	bl MIi_CpuCopy32
	add r0, r5, #0
	bl FreeToHeap
	mov r0, #0x17
	str r0, [sp]
	mov r0, #0x2d
	mov r1, #7
	mov r2, #1
	add r3, sp, #8
	bl FUN_02006BDC
	add r1, r4, #0
	add r5, r0, #0
	ldr r0, [sp, #8]
	add r1, #0xdc
	mov r2, #2
	ldr r1, [r1]
	add r0, #0xc
	lsl r2, r2, #0xa
	bl MIi_CpuCopy32
	add r0, r5, #0
	bl FreeToHeap
	mov r0, #0x17
	str r0, [sp]
	mov r0, #0x2d
	mov r1, #8
	mov r2, #1
	add r3, sp, #8
	bl FUN_02006BDC
	add r1, r4, #0
	add r5, r0, #0
	ldr r0, [sp, #8]
	add r1, #0xe0
	mov r2, #2
	ldr r1, [r1]
	add r0, #0xc
	lsl r2, r2, #0xa
	bl MIi_CpuCopy32
	add r0, r5, #0
	bl FreeToHeap
	mov r0, #0x17
	str r0, [sp]
	mov r0, #0x2d
	mov r1, #0x10
	mov r2, #1
	add r3, sp, #8
	bl FUN_02006BDC
	add r1, r4, #0
	add r5, r0, #0
	ldr r0, [sp, #8]
	add r1, #0xe4
	mov r2, #2
	ldr r1, [r1]
	add r0, #0xc
	lsl r2, r2, #0xa
	bl MIi_CpuCopy32
	add r0, r5, #0
	bl FreeToHeap
	mov r0, #0x17
	str r0, [sp]
	mov r0, #0x2d
	mov r1, #0x1b
	mov r2, #1
	add r3, sp, #8
	bl FUN_02006BDC
	add r1, r4, #0
	add r5, r0, #0
	ldr r0, [sp, #8]
	add r1, #0xe8
	mov r2, #2
	ldr r1, [r1]
	add r0, #0xc
	lsl r2, r2, #0xa
	bl MIi_CpuCopy32
	add r0, r5, #0
	bl FreeToHeap
	mov r0, #0
	str r0, [sp]
	add r0, r4, #0
	add r0, #0xec
	ldr r0, [r0]
	mov r3, #2
	str r0, [sp, #4]
	mov r0, #0x2d
	mov r1, #0x1e
	mov r2, #0x17
	lsl r3, r3, #8
	bl FUN_0200317C
	ldr r0, [r4, #4]
	mov r2, #0x17
	ldr r1, [r0]
	ldr r0, _0223B70C ; =0x0000011F
	mov r3, #0x20
	ldrb r0, [r1, r0]
	mov r1, #0x25
	lsl r0, r0, #0x14
	lsr r0, r0, #0x10
	str r0, [sp]
	add r0, r4, #0
	add r0, #0xec
	ldr r0, [r0]
	add r0, #0x40
	str r0, [sp, #4]
	mov r0, #0x2d
	bl FUN_0200317C
	mov r0, #0
	mov r1, #0x20
	add r4, #0xf0
	str r0, [sp]
	ldr r0, [r4]
	mov r2, #0x17
	str r0, [sp, #4]
	mov r0, #0x2d
	lsl r3, r1, #4
	bl FUN_0200317C
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223B70C: .word 0x0000011F

	thumb_func_start MOD12_0223B710
MOD12_0223B710: ; 0x0223B710
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r6, #0
	add r4, r5, #0
_0223B718:
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl FreeToHeap
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #3
	blt _0223B718
	mov r6, #0
	add r4, r5, #0
_0223B72E:
	add r0, r4, #0
	add r0, #0xdc
	ldr r0, [r0]
	bl FreeToHeap
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _0223B72E
	mov r4, #0
_0223B742:
	add r0, r5, #0
	add r0, #0xec
	ldr r0, [r0]
	bl FreeToHeap
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blt _0223B742
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD12_0223B758
MOD12_0223B758: ; 0x0223B758
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r0, #0
	str r3, [r7, #8]
	ldr r0, [r7, #4]
	str r2, [sp, #8]
	ldr r0, [r0, #0x60]
	str r1, [sp, #4]
	str r0, [sp, #0xc]
	mov r0, #0x96
	ldrsb r2, [r7, r0]
	sub r0, #0x97
	cmp r2, r0
	bne _0223B77C
	mov r0, #1
	str r0, [sp, #8]
	mov r6, #0
	b _0223B784
_0223B77C:
	mov r0, #0x24
	ldr r1, _0223B868 ; =MOD12_02246094
	mul r0, r2
	add r6, r1, r0
_0223B784:
	ldr r0, [sp, #4]
	mov r1, #0x24
	ldr r2, _0223B868 ; =MOD12_02246094
	mul r1, r0
	add r0, r2, r1
	str r0, [sp, #0x10]
	mov r4, #0
	add r5, r0, #0
_0223B794:
	ldrh r1, [r5, #0xc]
	add r0, r4, #4
	lsl r0, r0, #0x18
	lsl r1, r1, #0x18
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl FUN_020178BC
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, #4
	blt _0223B794
	ldr r0, [sp, #0x10]
	mov r2, #8
	ldrh r1, [r0]
	add r0, r7, #0
	add r0, #0x94
	strh r1, [r0]
	ldr r0, _0223B86C ; =MOD12_0223C19C
	add r1, r7, #0
	bl FUN_0200CA98
	ldr r0, [sp, #0x10]
	ldrh r1, [r0, #2]
	ldr r0, _0223B870 ; =0x0000FFFF
	cmp r1, r0
	beq _0223B7F2
	ldr r0, [sp, #8]
	cmp r0, #1
	beq _0223B7D6
	ldrh r0, [r6, #2]
	cmp r1, r0
	beq _0223B7F2
_0223B7D6:
	mov r0, #2
	lsl r0, r0, #8
	str r0, [sp]
	ldr r0, [r7, #4]
	lsl r1, r1, #2
	add r1, r7, r1
	add r0, #0x90
	add r1, #0xec
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #1
	mov r3, #0
	bl FUN_02003054
_0223B7F2:
	ldr r4, [sp, #0x10]
	mov r5, #0
_0223B7F6:
	ldrh r2, [r4, #4]
	ldr r0, _0223B870 ; =0x0000FFFF
	cmp r2, r0
	beq _0223B82E
	ldr r0, [sp, #8]
	cmp r0, #1
	beq _0223B80A
	ldrh r0, [r6, #4]
	cmp r2, r0
	beq _0223B82E
_0223B80A:
	lsl r2, r2, #2
	add r2, r7, r2
	add r1, r5, #4
	add r2, #0xdc
	lsl r1, r1, #0x18
	mov r3, #2
	ldr r0, [sp, #0xc]
	ldr r2, [r2]
	lsr r1, r1, #0x18
	lsl r3, r3, #0xa
	bl FUN_02017DFC
	add r1, r5, #4
	lsl r1, r1, #0x18
	ldr r0, [sp, #0xc]
	lsr r1, r1, #0x18
	bl FUN_0201AC68
_0223B82E:
	add r5, r5, #1
	add r4, r4, #2
	add r6, r6, #2
	cmp r5, #4
	blt _0223B7F6
	add r1, r7, #0
	ldr r0, [sp, #4]
	add r1, #0x96
	strb r0, [r1]
	add r0, r7, #0
	mov r1, #0
	bl MOD12_0223BE50
	ldr r0, [sp, #0x10]
	ldr r3, [r0, #0x1c]
	cmp r3, #0
	beq _0223B858
	ldr r1, [sp, #4]
	ldr r2, [sp, #8]
	add r0, r7, #0
	blx r3
_0223B858:
	ldr r0, _0223B874 ; =MOD12_0223C14C
	add r1, r7, #0
	mov r2, #0xa
	bl FUN_0200CA98
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0223B868: .word MOD12_02246094
_0223B86C: .word MOD12_0223C19C
_0223B870: .word 0x0000FFFF
_0223B874: .word MOD12_0223C14C

	thumb_func_start MOD12_0223B878
MOD12_0223B878: ; 0x0223B878
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x96
	ldrsb r1, [r5, r0]
	sub r0, #0x97
	cmp r1, r0
	bne _0223B88A
	bl ErrorHandling
_0223B88A:
	mov r0, #0x96
	ldrsb r1, [r5, r0]
	ldr r3, _0223B910 ; =MOD12_02246094
	mov r0, #0x24
	add r2, r1, #0
	mul r2, r0
	add r4, r3, r2
	ldr r1, [r4, #0x14]
	cmp r1, #0
	bne _0223B8A2
	sub r0, #0x25
	pop {r4, r5, r6, pc}
_0223B8A2:
	ldr r0, [r4, #0x18]
	cmp r0, #0
	bne _0223B8AC
	bl ErrorHandling
_0223B8AC:
	ldr r0, [r4, #0x14]
	bl FUN_02020988
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _0223B8F0
	ldr r2, [r4, #0x18]
	ldr r1, _0223B914 ; =MOD12_02246070
	cmp r2, r1
	bne _0223B8F0
	ldr r1, _0223B918 ; =gMain
	mov r2, #0x11
	ldr r1, [r1, #0x48]
	add r3, r1, #0
	tst r3, r2
	beq _0223B8D2
	mov r0, #3
	b _0223B8F0
_0223B8D2:
	mov r3, #0x82
	add r6, r1, #0
	tst r6, r3
	beq _0223B8DE
	mov r0, #1
	b _0223B8F0
_0223B8DE:
	lsl r2, r2, #6
	tst r2, r1
	beq _0223B8E8
	mov r0, #0
	b _0223B8F0
_0223B8E8:
	lsl r2, r3, #4
	tst r1, r2
	beq _0223B8F0
	mov r0, #2
_0223B8F0:
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0223B8FE
	ldr r1, [r4, #0x18]
	lsl r0, r0, #2
	ldr r1, [r1, r0]
_0223B8FE:
	ldr r2, [r4, #0x20]
	cmp r2, #0
	beq _0223B90A
	add r0, r5, #0
	blx r2
	add r1, r0, #0
_0223B90A:
	add r0, r1, #0
	pop {r4, r5, r6, pc}
	nop
_0223B910: .word MOD12_02246094
_0223B914: .word MOD12_02246070
_0223B918: .word gMain

	thumb_func_start MOD12_0223B91C
MOD12_0223B91C: ; 0x0223B91C
	ldr r0, [r0, #0xc]
	cmp r0, #0
	bne _0223B926
	mov r0, #1
	bx lr
_0223B926:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0223B92C
MOD12_0223B92C: ; 0x0223B92C
	mov r1, #0x96
	ldrsb r0, [r0, r1]
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0223B934
MOD12_0223B934: ; 0x0223B934
	ldr r3, _0223B93C ; =MOD12_0223BE10
	mov r1, #1
	bx r3
	nop
_0223B93C: .word MOD12_0223BE10

	thumb_func_start MOD12_0223B940
MOD12_0223B940: ; 0x0223B940
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	mov r0, #1
	mov r1, #0x1a
	mov r2, #0xbf
	mov r3, #0x17
	bl NewMsgDataFromNarc
	add r4, r0, #0
	ldr r0, [r5, #4]
	mov r2, #0x12
	lsl r2, r2, #4
	ldr r3, [r0]
	add r1, r2, #1
	ldrb r0, [r3, r2]
	ldrb r1, [r3, r1]
	ldr r3, [r5]
	add r2, #0x51
	ldrb r2, [r3, r2]
	bl FUN_02083228
	add r6, r0, #0
	ldr r0, [r5, #4]
	ldr r1, _0223B9F4 ; =0x0000011F
	ldr r2, [r0]
	ldrb r0, [r2, r1]
	add r1, r1, #2
	ldrb r1, [r2, r1]
	bl FUN_020832A4
	add r7, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	bl NewString_ReadMsgData
	add r6, r0, #0
	add r0, r4, #0
	add r1, r7, #0
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldr r0, _0223B9F8 ; =0x00010200
	add r1, r5, #0
	str r0, [sp]
	mov r3, #0
	ldr r0, _0223B9FC ; =0x000080EB
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x7f
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r1, #0x1c
	add r2, r6, #0
	bl MOD12_0223BCD8
	ldr r0, _0223B9F8 ; =0x00010200
	mov r3, #0
	str r0, [sp]
	ldr r0, _0223B9FC ; =0x000080EB
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x9f
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r5, #0x30
	add r1, r5, #0
	add r2, r7, #0
	bl MOD12_0223BCD8
	add r0, r6, #0
	bl String_dtor
	add r0, r7, #0
	bl String_dtor
	add r0, r4, #0
	bl DestroyMsgData
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223B9F4: .word 0x0000011F
_0223B9F8: .word 0x00010200
_0223B9FC: .word 0x000080EB

	thumb_func_start MOD12_0223BA00
MOD12_0223BA00: ; 0x0223BA00
	ldr r3, _0223BA08 ; =MOD12_0223BE10
	mov r1, #1
	bx r3
	nop
_0223BA08: .word MOD12_0223BE10

	thumb_func_start MOD12_0223BA0C
MOD12_0223BA0C: ; 0x0223BA0C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	ldr r2, [r0, #4]
	str r0, [sp, #0x18]
	add r0, r2, #0
	add r0, #0x84
	ldr r5, [r0]
	ldr r1, [r2]
	ldr r0, _0223BB14 ; =0x00000123
	ldrb r0, [r1, r0]
	add r1, r2, r0
	mov r0, #0xaa
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	cmp r0, #1
	bne _0223BA36
	add r0, r5, #0
	mov r1, #0
	bl NewString_ReadMsgData
	b _0223BA3E
_0223BA36:
	add r0, r5, #0
	mov r1, #1
	bl NewString_ReadMsgData
_0223BA3E:
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #2
	bl NewString_ReadMsgData
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #3
	bl NewString_ReadMsgData
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #4
	bl NewString_ReadMsgData
	add r5, r0, #0
	ldr r0, _0223BB18 ; =0x0001010B
	add r2, r4, #0
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0223BB1C ; =0x000080EB
	mov r3, #2
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x18
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x18]
	add r1, r0, #0
	add r1, #0x44
	bl MOD12_0223BCD8
	ldr r0, _0223BB18 ; =0x0001010B
	add r2, r6, #0
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0223BB1C ; =0x000080EB
	mov r3, #2
	str r0, [sp, #8]
	mov r0, #0x80
	str r0, [sp, #0xc]
	mov r0, #0x78
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x18]
	add r1, r0, #0
	add r1, #0x58
	bl MOD12_0223BCD8
	ldr r0, _0223BB18 ; =0x0001010B
	add r2, r7, #0
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0223BB1C ; =0x000080EB
	mov r3, #2
	str r0, [sp, #8]
	mov r0, #0x30
	str r0, [sp, #0xc]
	mov r0, #0x40
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x18]
	add r1, r0, #0
	add r1, #0x6c
	bl MOD12_0223BCD8
	ldr r0, _0223BB18 ; =0x0001010B
	add r2, r5, #0
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0223BB1C ; =0x000080EB
	mov r3, #2
	str r0, [sp, #8]
	mov r0, #0xd0
	str r0, [sp, #0xc]
	mov r0, #0x40
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x18]
	add r1, r0, #0
	add r1, #0x80
	str r1, [sp, #0x18]
	bl MOD12_0223BCD8
	add r0, r4, #0
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	add r0, r7, #0
	bl String_dtor
	add r0, r5, #0
	bl String_dtor
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223BB14: .word 0x00000123
_0223BB18: .word 0x0001010B
_0223BB1C: .word 0x000080EB

	thumb_func_start MOD12_0223BB20
MOD12_0223BB20: ; 0x0223BB20
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r4, r0, #0
	add r0, r6, #1
	cmp r0, #4
	bhi _0223BB42
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223BB38: ; jump table
	.short _0223BB42 - _0223BB38 - 2 ; case 0
	.short _0223BB46 - _0223BB38 - 2 ; case 1
	.short _0223BB4A - _0223BB38 - 2 ; case 2
	.short _0223BB4E - _0223BB38 - 2 ; case 3
	.short _0223BB52 - _0223BB38 - 2 ; case 4
_0223BB42:
	add r0, r6, #0
	pop {r4, r5, r6, pc}
_0223BB46:
	mov r5, #2
	b _0223BB54
_0223BB4A:
	mov r5, #3
	b _0223BB54
_0223BB4E:
	mov r5, #4
	b _0223BB54
_0223BB52:
	mov r5, #5
_0223BB54:
	ldr r0, _0223BBB0 ; =MOD12_0223BEB4
	add r1, r4, #0
	bl MOD12_0223BE64
	add r0, r4, #0
	mov r1, #2
	add r0, #0xb8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc0
	str r1, [r0]
	add r0, r4, #0
	mov r1, #0x12
	add r0, #0xca
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0x2d
	add r0, #0xc8
	strh r1, [r0]
	mov r0, #0xc
	ldr r1, _0223BBB4 ; =MOD12_0224614C
	mul r0, r6
	add r2, r1, r0
	add r1, r4, #0
	add r1, #0xa0
	str r2, [r1]
	ldr r1, _0223BBB8 ; =MOD12_0224617C
	add r2, r1, r0
	add r1, r4, #0
	add r1, #0xa4
	str r2, [r1]
	ldr r1, _0223BBBC ; =MOD12_022461AC
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0xa8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc4
	str r6, [r0]
	add r4, #0xcc
	strb r5, [r4]
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223BBB0: .word MOD12_0223BEB4
_0223BBB4: .word MOD12_0224614C
_0223BBB8: .word MOD12_0224617C
_0223BBBC: .word MOD12_022461AC

	thumb_func_start MOD12_0223BBC0
MOD12_0223BBC0: ; 0x0223BBC0
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x17
	mov r1, #0x20
	add r5, r3, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x20
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	beq _0223BBEC
	lsl r0, r5, #2
	add r0, r6, r0
	add r0, #0xd0
	ldr r0, [r0]
	str r0, [r4, #0xc]
_0223BBEC:
	ldr r0, [sp, #0x1c]
	lsl r0, r0, #5
	strh r0, [r4, #0x1c]
	ldr r0, [sp, #0x18]
	ldrh r1, [r0]
	strh r1, [r4, #0x10]
	ldrh r1, [r0, #2]
	strh r1, [r4, #0x12]
	ldrh r1, [r0, #4]
	strh r1, [r4, #0x14]
	ldrh r1, [r0, #6]
	strh r1, [r4, #0x16]
	ldrh r1, [r0, #8]
	strh r1, [r4, #0x18]
	ldrh r0, [r0, #0xa]
	strh r0, [r4, #0x1a]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	bl FUN_020187B0
	str r0, [r4, #4]
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_0223BC1C
MOD12_0223BC1C: ; 0x0223BC1C
	push {r4, lr}
	sub sp, #8
	ldr r4, [sp, #0x10]
	str r4, [sp]
	ldr r4, [sp, #0x14]
	str r4, [sp, #4]
	bl MOD12_0223BBC0
	add r4, r0, #0
	ldr r0, _0223BC40 ; =MOD12_0223C1DC
	add r1, r4, #0
	mov r2, #0x14
	bl FUN_0200CA98
	str r0, [r4]
	add r0, r4, #0
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_0223BC40: .word MOD12_0223C1DC

	thumb_func_start MOD12_0223BC44
MOD12_0223BC44: ; 0x0223BC44
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	bne _0223BC62
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _0223BC58
	bl FreeToHeap
_0223BC58:
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r4, pc}
_0223BC62:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_0223BC68
MOD12_0223BC68: ; 0x0223BC68
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldrh r1, [r5, #0x16]
	ldrh r0, [r5, #0x1c]
	mov r6, #0
	mul r0, r1
	str r0, [sp]
	ldrh r0, [r5, #0x12]
	lsl r7, r0, #0xa
	ldrh r0, [r5, #0x1a]
	cmp r0, #0
	ble _0223BCD4
	add r4, r6, #0
_0223BC82:
	ldr r2, [r5, #0xc]
	cmp r2, #0
	beq _0223BCB0
	ldrh r0, [r5, #0x14]
	ldrh r3, [r5, #0x1c]
	lsl r1, r0, #5
	add r0, r3, #0
	ldr r3, [sp]
	mul r0, r6
	add r0, r3, r0
	add r0, r1, r0
	ldrh r1, [r5, #0x10]
	add r0, r2, r0
	ldr r3, [r5, #4]
	lsl r2, r1, #5
	add r1, r7, r4
	add r1, r2, r1
	ldrh r2, [r5, #0x18]
	add r1, r3, r1
	lsl r2, r2, #5
	bl MIi_CpuCopy16
	b _0223BCC6
_0223BCB0:
	ldrh r1, [r5, #0x10]
	ldr r3, [r5, #4]
	mov r0, #0
	lsl r2, r1, #5
	add r1, r7, r4
	add r1, r2, r1
	ldrh r2, [r5, #0x18]
	add r1, r3, r1
	lsl r2, r2, #5
	bl MIi_CpuClear16
_0223BCC6:
	mov r0, #1
	lsl r0, r0, #0xa
	add r4, r4, r0
	ldrh r0, [r5, #0x1a]
	add r6, r6, #1
	cmp r6, r0
	blt _0223BC82
_0223BCD4:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_0223BCD8
MOD12_0223BCD8: ; 0x0223BCD8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x78
	add r5, r1, #0
	str r0, [sp, #0x18]
	ldr r0, [r5]
	str r2, [sp, #0x1c]
	str r3, [sp, #0x20]
	ldr r4, [sp, #0x9c]
	cmp r0, #0
	beq _0223BCF0
	bl ErrorHandling
_0223BCF0:
	ldr r0, [sp, #0x18]
	mov r2, #0
	ldr r1, [r0, #4]
	ldr r0, [r1, #0x60]
	str r0, [sp, #0x28]
	ldr r0, [r1, #0x5c]
	ldr r1, [sp, #0x1c]
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x20]
	bl FUN_02002E14
	add r7, r0, #0
	asr r1, r7, #2
	lsr r1, r1, #0x1d
	add r1, r7, r1
	asr r6, r1, #3
	mov r1, #8
	bl FX_ModS32
	cmp r0, #0
	beq _0223BD1C
	add r6, r6, #1
_0223BD1C:
	add r0, sp, #0x38
	bl InitWindow
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	lsl r2, r6, #0x18
	ldr r0, [sp, #0x28]
	add r1, sp, #0x38
	lsr r2, r2, #0x18
	mov r3, #2
	bl FUN_020190EC
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x90]
	ldr r1, [sp, #0x20]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r2, [sp, #0x1c]
	add r0, sp, #0x38
	str r3, [sp, #0x14]
	bl AddTextPrinterParameterized3
	add r0, sp, #0x38
	mov r1, #2
	mov r2, #0x17
	bl FUN_02011898
	mov r1, #1
	mov r2, #2
	add r3, sp, #0x2c
	bl FUN_0201D568
	ldr r0, [sp, #0xa4]
	cmp r0, #1
	bne _0223BD74
	lsr r0, r7, #0x1f
	add r0, r7, r0
	asr r0, r0, #1
	sub r4, r4, r0
_0223BD74:
	ldr r0, [sp, #0x18]
	ldr r0, [r0, #0x18]
	str r0, [sp, #0x48]
	add r0, sp, #0x38
	str r0, [sp, #0x4c]
	ldr r0, [sp, #0x24]
	bl FUN_0200CA40
	str r0, [sp, #0x50]
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x98]
	bl FUN_0200C334
	mov r1, #0
	str r0, [sp, #0x54]
	ldr r0, [sp, #0x30]
	str r1, [sp, #0x58]
	str r0, [sp, #0x5c]
	ldr r0, [sp, #0xa0]
	str r4, [sp, #0x60]
	add r0, #0xf8
	str r0, [sp, #0x64]
	mov r0, #0x64
	str r0, [sp, #0x6c]
	mov r0, #2
	str r0, [sp, #0x70]
	mov r0, #0x17
	str r0, [sp, #0x74]
	add r0, sp, #0x48
	str r1, [sp, #0x68]
	bl FUN_020117E8
	ldr r1, [sp, #0x94]
	add r6, r0, #0
	bl FUN_02011AC0
	ldr r2, [sp, #0xa0]
	add r0, r6, #0
	add r1, r4, #0
	add r2, #0xf8
	bl FUN_020118C4
	add r0, sp, #0x38
	bl FUN_02019178
	str r6, [r5]
	add r3, sp, #0x2c
	ldmia r3!, {r0, r1}
	add r2, r5, #4
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	strh r7, [r5, #0x10]
	add sp, #0x78
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_0223BDE4
MOD12_0223BDE4: ; 0x0223BDE4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r6, #0
	add r4, r5, #0
	add r4, #0x20
	add r7, r6, #0
_0223BDF0:
	ldr r0, [r5, #0x1c]
	cmp r0, #0
	beq _0223BE02
	bl FUN_02011870
	add r0, r4, #0
	bl FUN_0201D5E8
	str r7, [r5, #0x1c]
_0223BE02:
	add r6, r6, #1
	add r5, #0x14
	add r4, #0x14
	cmp r6, #6
	blt _0223BDF0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_0223BE10
MOD12_0223BE10: ; 0x0223BE10
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	cmp r7, #1
	bne _0223BE2C
	mov r1, #0x96
	ldrsb r1, [r0, r1]
	cmp r1, #0
	bne _0223BE26
	mov r4, #0
	mov r6, #1
	b _0223BE30
_0223BE26:
	mov r4, #2
	mov r6, #5
	b _0223BE30
_0223BE2C:
	mov r4, #0
	mov r6, #5
_0223BE30:
	cmp r4, r6
	bgt _0223BE4E
	mov r1, #0x14
	mul r1, r4
	add r5, r0, r1
_0223BE3A:
	ldr r0, [r5, #0x1c]
	cmp r0, #0
	beq _0223BE46
	add r1, r7, #0
	bl FUN_020119D0
_0223BE46:
	add r4, r4, #1
	add r5, #0x14
	cmp r4, r6
	ble _0223BE3A
_0223BE4E:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD12_0223BE50
MOD12_0223BE50: ; 0x0223BE50
	push {r3, lr}
	cmp r1, #1
	bne _0223BE5C
	bl MOD12_0223BDE4
	pop {r3, pc}
_0223BE5C:
	mov r1, #0
	bl MOD12_0223BE10
	pop {r3, pc}

	thumb_func_start MOD12_0223BE64
MOD12_0223BE64: ; 0x0223BE64
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _0223BE74
	bl ErrorHandling
_0223BE74:
	add r0, r4, #0
	add r0, #0x98
	mov r1, #0
	mov r2, #0x38
	bl MI_CpuFill8
	ldr r2, _0223BE90 ; =0x00000514
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #0xc]
	pop {r3, r4, r5, pc}
	nop
_0223BE90: .word 0x00000514

	thumb_func_start MOD12_0223BE94
MOD12_0223BE94: ; 0x0223BE94
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _0223BEB0
	bl FUN_0200CAB4
	mov r1, #0
	str r1, [r4, #0xc]
	add r4, #0x98
	add r0, r4, #0
	mov r2, #0x38
	bl MI_CpuFill8
_0223BEB0:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_0223BEB4
MOD12_0223BEB4: ; 0x0223BEB4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	mov r0, #0x98
	ldrsh r0, [r4, r0]
	cmp r0, #8
	bls _0223BEC4
	b _0223C140
_0223BEC4:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223BED0: ; jump table
	.short _0223BEE2 - _0223BED0 - 2 ; case 0
	.short _0223BF6A - _0223BED0 - 2 ; case 1
	.short _0223BF84 - _0223BED0 - 2 ; case 2
	.short _0223BFAA - _0223BED0 - 2 ; case 3
	.short _0223C034 - _0223BED0 - 2 ; case 4
	.short _0223C050 - _0223BED0 - 2 ; case 5
	.short _0223C076 - _0223BED0 - 2 ; case 6
	.short _0223C100 - _0223BED0 - 2 ; case 7
	.short _0223C11A - _0223BED0 - 2 ; case 8
_0223BEE2:
	add r0, r4, #0
	add r0, #0xa0
	ldr r0, [r0]
	add r2, r4, #0
	str r0, [sp]
	add r0, r4, #0
	add r0, #0xca
	ldrh r0, [r0]
	add r3, r4, #0
	add r2, #0xc8
	str r0, [sp, #4]
	add r3, #0xb8
	ldrh r2, [r2]
	ldr r3, [r3]
	add r0, r4, #0
	mov r1, #4
	bl MOD12_0223BC1C
	add r1, r4, #0
	add r1, #0x9c
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xcc
	ldrb r1, [r0]
	mov r0, #0x14
	add r2, sp, #8
	mul r0, r1
	add r0, r4, r0
	ldr r0, [r0, #0x1c]
	add r1, sp, #0xc
	bl FUN_020119A4
	add r0, r4, #0
	add r0, #0xcc
	ldrb r1, [r0]
	mov r0, #0x14
	ldr r2, [sp, #8]
	mul r0, r1
	add r0, r4, r0
	ldr r0, [r0, #0x1c]
	ldr r1, [sp, #0xc]
	add r2, #0x10
	bl FUN_020118C4
	mov r6, #0
	add r5, r4, #0
	add r7, r6, #0
_0223BF40:
	add r0, r5, #0
	add r0, #0xac
	ldr r0, [r0]
	cmp r0, #0
	beq _0223BF54
	ldr r0, [r0]
	add r1, r7, #0
	mov r2, #0x10
	bl FUN_0200C7FC
_0223BF54:
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _0223BF40
	mov r0, #0x98
	ldrsh r0, [r4, r0]
	add r4, #0x98
	add sp, #0x10
	add r0, r0, #1
	strh r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_0223BF6A:
	add r0, r4, #0
	add r0, #0x9c
	ldr r0, [r0]
	bl MOD12_0223BC44
	cmp r0, #0
	beq _0223C042
	mov r0, #0x98
	ldrsh r0, [r4, r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x98
	strh r1, [r0]
_0223BF84:
	mov r1, #0x9a
	ldrsh r0, [r4, r1]
	add r2, r0, #1
	add r0, r4, #0
	add r0, #0x9a
	strh r2, [r0]
	ldrsh r0, [r4, r1]
	cmp r0, #2
	ble _0223C042
	add r0, r4, #0
	mov r1, #0
	add r0, #0x9a
	strh r1, [r0]
	mov r0, #0x98
	ldrsh r0, [r4, r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x98
	strh r1, [r0]
_0223BFAA:
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	add r2, r4, #0
	str r0, [sp]
	add r0, r4, #0
	add r0, #0xca
	ldrh r0, [r0]
	add r3, r4, #0
	add r2, #0xc8
	str r0, [sp, #4]
	add r3, #0xbc
	ldrh r2, [r2]
	ldr r3, [r3]
	add r0, r4, #0
	mov r1, #4
	bl MOD12_0223BC1C
	add r1, r4, #0
	add r1, #0x9c
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xcc
	ldrb r1, [r0]
	mov r0, #0x14
	add r2, sp, #8
	mul r0, r1
	add r0, r4, r0
	ldr r0, [r0, #0x1c]
	add r1, sp, #0xc
	bl FUN_020119A4
	add r0, r4, #0
	add r0, #0xcc
	ldrb r1, [r0]
	mov r0, #0x14
	ldr r2, [sp, #8]
	mul r0, r1
	add r0, r4, r0
	ldr r0, [r0, #0x1c]
	ldr r1, [sp, #0xc]
	sub r2, r2, #4
	bl FUN_020118C4
	mov r6, #0
	add r5, r4, #0
	add r7, r6, #0
_0223C008:
	add r0, r5, #0
	add r0, #0xac
	ldr r0, [r0]
	cmp r0, #0
	beq _0223C01E
	mov r2, #3
	ldr r0, [r0]
	add r1, r7, #0
	mvn r2, r2
	bl FUN_0200C7FC
_0223C01E:
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _0223C008
	mov r0, #0x98
	ldrsh r0, [r4, r0]
	add r4, #0x98
	add sp, #0x10
	add r0, r0, #1
	strh r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_0223C034:
	add r0, r4, #0
	add r0, #0x9c
	ldr r0, [r0]
	bl MOD12_0223BC44
	cmp r0, #0
	bne _0223C044
_0223C042:
	b _0223C146
_0223C044:
	mov r0, #0x98
	ldrsh r0, [r4, r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x98
	strh r1, [r0]
_0223C050:
	mov r1, #0x9a
	ldrsh r0, [r4, r1]
	add r2, r0, #1
	add r0, r4, #0
	add r0, #0x9a
	strh r2, [r0]
	ldrsh r0, [r4, r1]
	cmp r0, #2
	ble _0223C146
	add r0, r4, #0
	mov r1, #0
	add r0, #0x9a
	strh r1, [r0]
	mov r0, #0x98
	ldrsh r0, [r4, r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x98
	strh r1, [r0]
_0223C076:
	add r0, r4, #0
	add r0, #0xa8
	ldr r0, [r0]
	add r2, r4, #0
	str r0, [sp]
	add r0, r4, #0
	add r0, #0xca
	ldrh r0, [r0]
	add r3, r4, #0
	add r2, #0xc8
	str r0, [sp, #4]
	add r3, #0xc0
	ldrh r2, [r2]
	ldr r3, [r3]
	add r0, r4, #0
	mov r1, #4
	bl MOD12_0223BC1C
	add r1, r4, #0
	add r1, #0x9c
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xcc
	ldrb r1, [r0]
	mov r0, #0x14
	add r2, sp, #8
	mul r0, r1
	add r0, r4, r0
	ldr r0, [r0, #0x1c]
	add r1, sp, #0xc
	bl FUN_020119A4
	add r0, r4, #0
	add r0, #0xcc
	ldrb r1, [r0]
	mov r0, #0x14
	ldr r2, [sp, #8]
	mul r0, r1
	add r0, r4, r0
	ldr r0, [r0, #0x1c]
	ldr r1, [sp, #0xc]
	sub r2, #0xc
	bl FUN_020118C4
	mov r6, #0
	add r5, r4, #0
	add r7, r6, #0
_0223C0D4:
	add r0, r5, #0
	add r0, #0xac
	ldr r0, [r0]
	cmp r0, #0
	beq _0223C0EA
	mov r2, #0xb
	ldr r0, [r0]
	add r1, r7, #0
	mvn r2, r2
	bl FUN_0200C7FC
_0223C0EA:
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _0223C0D4
	mov r0, #0x98
	ldrsh r0, [r4, r0]
	add r4, #0x98
	add sp, #0x10
	add r0, r0, #1
	strh r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_0223C100:
	add r0, r4, #0
	add r0, #0x9c
	ldr r0, [r0]
	bl MOD12_0223BC44
	cmp r0, #0
	beq _0223C146
	mov r0, #0x98
	ldrsh r0, [r4, r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x98
	strh r1, [r0]
_0223C11A:
	mov r1, #0x9a
	ldrsh r0, [r4, r1]
	add r2, r0, #1
	add r0, r4, #0
	add r0, #0x9a
	strh r2, [r0]
	ldrsh r0, [r4, r1]
	cmp r0, #2
	ble _0223C146
	add r0, r4, #0
	mov r1, #0
	add r0, #0x9a
	strh r1, [r0]
	mov r0, #0x98
	ldrsh r0, [r4, r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x98
	strh r1, [r0]
_0223C140:
	add r0, r4, #0
	bl MOD12_0223BE94
_0223C146:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_0223C14C
MOD12_0223C14C: ; 0x0223C14C
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	mov r0, #0x96
	ldrsb r1, [r1, r0]
	mov r0, #0x24
	mov r4, #0
	ldr r2, _0223C194 ; =MOD12_02246094
	mul r0, r1
	ldr r6, _0223C198 ; =0x0000FFFF
	add r5, r2, r0
	add r7, r4, #0
_0223C162:
	ldrh r0, [r5, #4]
	cmp r0, r6
	bne _0223C176
	add r0, r4, #4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, r7, #0
	bl FUN_0201797C
	b _0223C182
_0223C176:
	add r0, r4, #4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r1, #1
	bl FUN_0201797C
_0223C182:
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, #4
	blt _0223C162
	ldr r0, [sp]
	bl FUN_0200CAB4
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223C194: .word MOD12_02246094
_0223C198: .word 0x0000FFFF

	thumb_func_start MOD12_0223C19C
MOD12_0223C19C: ; 0x0223C19C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x94
	ldrh r2, [r0]
	ldr r0, _0223C1D8 ; =0x0000FFFF
	cmp r2, r0
	beq _0223C1CE
	mov r0, #0
	lsl r2, r2, #2
	str r0, [sp]
	ldr r0, [r4, #4]
	add r2, r4, r2
	add r2, #0xd0
	mov r3, #6
	ldr r0, [r0, #0x60]
	ldr r2, [r2]
	mov r1, #4
	lsl r3, r3, #0xc
	bl FUN_02017E14
	ldr r0, _0223C1D8 ; =0x0000FFFF
	add r4, #0x94
	strh r0, [r4]
_0223C1CE:
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	nop
_0223C1D8: .word 0x0000FFFF

	thumb_func_start MOD12_0223C1DC
MOD12_0223C1DC: ; 0x0223C1DC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl MOD12_0223BC68
	mov r0, #0
	str r0, [r4]
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_0223C1F4
MOD12_0223C1F4: ; 0x0223C1F4
	push {r3, lr}
	sub sp, #8
	str r2, [sp]
	str r1, [sp, #4]
	ldr r0, [r0, #4]
	mov r1, #1
	add r0, #0x90
	ldr r0, [r0]
	mov r2, #0
	mov r3, #0x40
	bl FUN_020039E8
	add sp, #8
	pop {r3, pc}

	thumb_func_start MOD12_0223C210
MOD12_0223C210: ; 0x0223C210
	mov r1, #6
	mul r1, r0
	ldr r0, _0223C21C ; =MOD12_022461F4
	ldrsh r0, [r0, r1]
	bx lr
	nop
_0223C21C: .word MOD12_022461F4

	thumb_func_start MOD12_0223C220
MOD12_0223C220: ; 0x0223C220
	mov r1, #6
	mul r1, r0
	ldr r0, _0223C230 ; =MOD12_022461F4
	add r1, r0, r1
	mov r0, #2
	ldrsh r0, [r1, r0]
	bx lr
	nop
_0223C230: .word MOD12_022461F4

	thumb_func_start MOD12_0223C234
MOD12_0223C234: ; 0x0223C234
	mov r1, #6
	mul r1, r0
	ldr r0, _0223C244 ; =MOD12_022461F4
	add r1, r0, r1
	mov r0, #4
	ldrsh r0, [r1, r0]
	bx lr
	nop
_0223C244: .word MOD12_022461F4

	thumb_func_start MOD12_0223C248
MOD12_0223C248: ; 0x0223C248
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r4, #0
	b _0223C264
_0223C252:
	lsl r0, r4, #4
	add r0, r5, r0
	add r0, #0xac
	ldr r0, [r0]
	cmp r0, #0
	beq _0223C262
	bl ErrorHandling
_0223C262:
	add r4, r4, #1
_0223C264:
	cmp r4, #4
	blt _0223C252
	add r0, sp, #0
	mov r1, #0
	mov r2, #0x10
	bl MI_CpuFill8
	mov r0, #0x17
	str r0, [sp, #0xc]
	mov r4, #0
	ldr r7, _0223C2F8 ; =MOD12_022461F4
	b _0223C2F0
_0223C27C:
	ldr r0, _0223C2FC ; =0x00000AD5
	add r1, r5, r4
	ldrb r6, [r1, r0]
	ldr r1, [r5]
	lsl r0, r6, #2
	ldr r0, [r1, r0]
	mov r1, #2
	bl FUN_02068E14
	add r2, r0, #0
	mov r0, #6
	mul r0, r4
	ldrsh r1, [r7, r0]
	add r0, r7, r0
	mov r3, #2
	ldrsh r3, [r0, r3]
	str r1, [sp, #4]
	add r2, r2, r3
	str r2, [sp, #8]
	lsl r2, r6, #4
	add r2, r5, r2
	str r1, [r2, #0x1c]
	ldr r1, [sp, #8]
	str r1, [r2, #0x20]
	mov r1, #4
	ldrsh r0, [r0, r1]
	lsl r1, r6, #2
	str r0, [r2, #0x24]
	ldr r2, [r5]
	add r0, sp, #0
	add r1, r2, r1
	add r1, #0xf8
	ldr r1, [r1]
	bl MOD17_021DD4F4
	lsl r1, r6, #4
	add r2, r5, r1
	str r0, [r2, #0x18]
	ldr r1, [r2, #0x1c]
	ldr r2, [r2, #0x20]
	bl MOD17_021DD620
	cmp r4, #0
	ble _0223C2EE
	lsl r0, r6, #4
	add r0, r5, r0
	ldr r0, [r0, #0x18]
	mov r1, #0
	bl MOD17_021DD59C
	lsl r0, r6, #4
	add r0, r5, r0
	mov r1, #0x63
	ldr r0, [r0, #0x18]
	mvn r1, r1
	bl MOD17_021DD6CC
_0223C2EE:
	add r4, r4, #1
_0223C2F0:
	cmp r4, #4
	blt _0223C27C
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223C2F8: .word MOD12_022461F4
_0223C2FC: .word 0x00000AD5

	thumb_func_start MOD12_0223C300
MOD12_0223C300: ; 0x0223C300
	push {r4, r5, r6, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r4, #0
_0223C308:
	ldr r0, [r5, #4]
	bl MOD17_021DD540
	add r0, r5, #0
	add r0, #0x98
	add r4, r4, #1
	add r5, #0x10
	str r6, [r0]
	cmp r4, #4
	blt _0223C308
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD12_0223C320
MOD12_0223C320: ; 0x0223C320
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0223C324
MOD12_0223C324: ; 0x0223C324
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0223C328
MOD12_0223C328: ; 0x0223C328
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #8
	cmp r1, r0
	ble _0223C338
	add r1, r0, #0
_0223C338:
	asr r0, r1, #2
	lsr r0, r0, #0x1d
	add r0, r1, r0
	lsr r2, r1, #0x1f
	lsl r1, r1, #0x1d
	asr r4, r0, #3
	sub r1, r1, r2
	mov r0, #0x1d
	ror r1, r0
	add r0, r2, r1
	str r0, [sp, #4]
	ldr r0, [sp]
	mov r1, #3
	ldr r0, [r0, #0x60]
	bl FUN_0201886C
	add r2, r0, #0
	mov r1, #0
	cmp r4, #0
	ble _0223C394
	ldr r0, _0223C420 ; =0x00002014
	add r3, r2, #0
	mov r7, #0x1d
_0223C366:
	lsr r6, r1, #0x1f
	lsl r5, r1, #0x1d
	sub r5, r5, r6
	ror r5, r7
	add r5, r6, r5
	bne _0223C37A
	mov r5, #0x13
	lsl r5, r5, #6
	strh r0, [r3, r5]
	b _0223C38C
_0223C37A:
	mov r5, #1
	tst r5, r1
	beq _0223C384
	ldr r6, _0223C424 ; =0x00002034
	b _0223C386
_0223C384:
	ldr r6, _0223C428 ; =0x00002054
_0223C386:
	mov r5, #0x13
	lsl r5, r5, #6
	strh r6, [r3, r5]
_0223C38C:
	add r1, r1, #1
	add r3, r3, #2
	cmp r1, r4
	blt _0223C366
_0223C394:
	cmp r1, #0x20
	bge _0223C3D4
	lsr r4, r1, #0x1f
	lsl r3, r1, #0x1d
	sub r3, r3, r4
	mov r0, #0x1d
	ror r3, r0
	add r0, r4, r3
	bne _0223C3B8
	ldr r3, _0223C42C ; =0x0000200C
	ldr r0, [sp, #4]
	add r4, r0, r3
	lsl r0, r1, #1
	add r3, r2, r0
	mov r0, #0x13
	lsl r0, r0, #6
	strh r4, [r3, r0]
	b _0223C3D2
_0223C3B8:
	mov r0, #1
	tst r0, r1
	beq _0223C3C2
	ldr r3, _0223C430 ; =0x0000202C
	b _0223C3C4
_0223C3C2:
	ldr r3, _0223C434 ; =0x0000204C
_0223C3C4:
	ldr r0, [sp, #4]
	add r4, r0, r3
	lsl r0, r1, #1
	add r3, r2, r0
	mov r0, #0x13
	lsl r0, r0, #6
	strh r4, [r3, r0]
_0223C3D2:
	add r1, r1, #1
_0223C3D4:
	cmp r1, #0x20
	bge _0223C410
	lsl r0, r1, #1
	add r2, r2, r0
	mov r4, #0x13
	ldr r0, _0223C42C ; =0x0000200C
	mov r7, #1
	lsl r4, r4, #6
	mov r5, #0x1d
_0223C3E6:
	lsr r6, r1, #0x1f
	lsl r3, r1, #0x1d
	sub r3, r3, r6
	ror r3, r5
	add r3, r6, r3
	bne _0223C3F6
	strh r0, [r2, r4]
	b _0223C408
_0223C3F6:
	add r3, r1, #0
	tst r3, r7
	beq _0223C400
	ldr r6, _0223C430 ; =0x0000202C
	b _0223C402
_0223C400:
	ldr r6, _0223C434 ; =0x0000204C
_0223C402:
	mov r3, #0x13
	lsl r3, r3, #6
	strh r6, [r2, r3]
_0223C408:
	add r1, r1, #1
	add r2, r2, #2
	cmp r1, #0x20
	blt _0223C3E6
_0223C410:
	ldr r0, [sp]
	mov r1, #3
	ldr r0, [r0, #0x60]
	bl FUN_0201AC68
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223C420: .word 0x00002014
_0223C424: .word 0x00002034
_0223C428: .word 0x00002054
_0223C42C: .word 0x0000200C
_0223C430: .word 0x0000202C
_0223C434: .word 0x0000204C

	thumb_func_start MOD12_0223C438
MOD12_0223C438: ; 0x0223C438
	push {r4, lr}
	add r4, r0, #0
	lsl r0, r1, #8
	add r1, r2, #0
	bl _s32_div_f
	add r1, r0, #0
	add r0, r4, #0
	bl MOD12_0223C328
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_0223C450
MOD12_0223C450: ; 0x0223C450
	push {r4, r5, lr}
	sub sp, #0xc
	mov r2, #1
	str r2, [sp]
	str r2, [sp, #4]
	ldr r2, _0223C4D8 ; =0x000080EB
	mov r3, #0x3a
	str r2, [sp, #8]
	mov r2, #0x2e
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0223C4DC ; =0x000080EC
	add r1, r4, #0
	str r0, [sp, #8]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x3b
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0223C4E0 ; =0x000080ED
	add r1, r4, #0
	str r0, [sp, #8]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x3c
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0223C4E4 ; =0x000080EE
	add r1, r4, #0
	str r0, [sp, #8]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x3d
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223C4D8 ; =0x000080EB
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x3e
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223C4D8 ; =0x000080EB
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x3f
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_0223C4D8: .word 0x000080EB
_0223C4DC: .word 0x000080EC
_0223C4E0: .word 0x000080ED
_0223C4E4: .word 0x000080EE

	thumb_func_start MOD12_0223C4E8
MOD12_0223C4E8: ; 0x0223C4E8
	push {r4, lr}
	ldr r1, _0223C51C ; =0x000080EB
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _0223C520 ; =0x000080EC
	add r0, r4, #0
	bl FUN_0200C358
	ldr r1, _0223C524 ; =0x000080ED
	add r0, r4, #0
	bl FUN_0200C358
	ldr r1, _0223C528 ; =0x000080EE
	add r0, r4, #0
	bl FUN_0200C358
	ldr r1, _0223C51C ; =0x000080EB
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _0223C51C ; =0x000080EB
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_0223C51C: .word 0x000080EB
_0223C520: .word 0x000080EC
_0223C524: .word 0x000080ED
_0223C528: .word 0x000080EE

	thumb_func_start MOD12_0223C52C
MOD12_0223C52C: ; 0x0223C52C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	ldr r4, _0223C62C ; =MOD12_022462E0
	add r7, r2, #0
	add r6, r3, #0
	add r5, r0, #0
	mov ip, r1
	add r3, sp, #0
	mov r2, #6
_0223C53E:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0223C53E
	ldr r0, [r4]
	cmp r6, #2
	str r0, [r3]
	bne _0223C556
	ldr r0, [sp, #8]
	add r0, #0xa
	str r0, [sp, #8]
	b _0223C586
_0223C556:
	ldr r0, [sp, #0x54]
	cmp r0, #3
	bhi _0223C586
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223C568: ; jump table
	.short _0223C586 - _0223C568 - 2 ; case 0
	.short _0223C570 - _0223C568 - 2 ; case 1
	.short _0223C578 - _0223C568 - 2 ; case 2
	.short _0223C580 - _0223C568 - 2 ; case 3
_0223C570:
	ldr r0, [sp, #8]
	add r0, r0, #3
	str r0, [sp, #8]
	b _0223C586
_0223C578:
	ldr r0, [sp, #8]
	add r0, r0, #2
	str r0, [sp, #8]
	b _0223C586
_0223C580:
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
_0223C586:
	ldr r0, [sp, #0x48]
	cmp r0, #4
	bhi _0223C5C0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223C598: ; jump table
	.short _0223C5C0 - _0223C598 - 2 ; case 0
	.short _0223C5B6 - _0223C598 - 2 ; case 1
	.short _0223C5C0 - _0223C598 - 2 ; case 2
	.short _0223C5A2 - _0223C598 - 2 ; case 3
	.short _0223C5AC - _0223C598 - 2 ; case 4
_0223C5A2:
	ldr r0, _0223C630 ; =0x000080EC
	str r0, [sp, #0x14]
	mov r0, #2
	str r0, [sp, #0xc]
	b _0223C5C8
_0223C5AC:
	ldr r0, _0223C634 ; =0x000080EE
	str r0, [sp, #0x14]
	mov r0, #6
	str r0, [sp, #0xc]
	b _0223C5C8
_0223C5B6:
	ldr r0, _0223C638 ; =0x000080ED
	str r0, [sp, #0x14]
	mov r0, #7
	str r0, [sp, #0xc]
	b _0223C5C8
_0223C5C0:
	ldr r0, _0223C63C ; =0x000080EB
	str r0, [sp, #0x14]
	mov r0, #2
	str r0, [sp, #0xc]
_0223C5C8:
	mov r0, ip
	add r1, r7, #0
	add r2, sp, #0
	bl FUN_0200C154
	add r4, r0, #0
	add r1, r6, #0
	bl FUN_0200C5C0
	ldr r0, [r4]
	bl FUN_0200C59C
	ldr r1, [sp, #0x4c]
	ldr r2, [sp, #0x50]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	mov r3, #1
	add r0, r4, #0
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	lsl r3, r3, #0x14
	bl FUN_0200C750
	add r0, r4, #0
	mov r1, #1
	bl FUN_0200C5E0
	mov r0, #0
	add r2, r5, #0
_0223C602:
	add r1, r2, #0
	add r1, #0xd8
	ldr r1, [r1]
	cmp r1, #0
	bne _0223C618
	lsl r1, r0, #2
	add r1, r5, r1
	add r1, #0xd8
	add sp, #0x34
	str r4, [r1]
	pop {r4, r5, r6, r7, pc}
_0223C618:
	add r0, r0, #1
	add r2, r2, #4
	cmp r0, #0x44
	blt _0223C602
	bl ErrorHandling
	mov r0, #0
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	nop
_0223C62C: .word MOD12_022462E0
_0223C630: .word 0x000080EC
_0223C634: .word 0x000080EE
_0223C638: .word 0x000080ED
_0223C63C: .word 0x000080EB

	thumb_func_start MOD12_0223C640
MOD12_0223C640: ; 0x0223C640
	push {r4, r5, r6, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r4, #0
_0223C648:
	add r0, r5, #0
	add r0, #0xd8
	ldr r0, [r0]
	cmp r0, #0
	beq _0223C65C
	bl FUN_0200C3DC
	add r0, r5, #0
	add r0, #0xd8
	str r6, [r0]
_0223C65C:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x44
	blt _0223C648
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD12_0223C668
MOD12_0223C668: ; 0x0223C668
	push {r4, r5, lr}
	sub sp, #0xc
	mov r2, #1
	str r2, [sp]
	str r2, [sp, #4]
	ldr r2, _0223C6B0 ; =0x000080EF
	mov r3, #0x37
	str r2, [sp, #8]
	mov r2, #0x2e
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223C6B4 ; =0x000080EC
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x38
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223C6B4 ; =0x000080EC
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x39
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0223C6B0: .word 0x000080EF
_0223C6B4: .word 0x000080EC

	thumb_func_start MOD12_0223C6B8
MOD12_0223C6B8: ; 0x0223C6B8
	push {r4, lr}
	ldr r1, _0223C6D4 ; =0x000080EF
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _0223C6D8 ; =0x000080EC
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _0223C6D8 ; =0x000080EC
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_0223C6D4: .word 0x000080EF
_0223C6D8: .word 0x000080EC

	thumb_func_start MOD12_0223C6DC
MOD12_0223C6DC: ; 0x0223C6DC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	mov r4, #0
_0223C6E6:
	ldr r2, _0223C708 ; =MOD12_02246314
	add r0, r6, #0
	add r1, r7, #0
	bl FUN_0200C154
	ldr r1, _0223C70C ; =0x000009DC
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200C644
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _0223C6E6
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223C708: .word MOD12_02246314
_0223C70C: .word 0x000009DC

	thumb_func_start MOD12_0223C710
MOD12_0223C710: ; 0x0223C710
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	ldr r7, _0223C730 ; =0x000009DC
	add r5, r0, #0
	add r6, r4, #0
_0223C71A:
	ldr r0, _0223C730 ; =0x000009DC
	ldr r0, [r5, r0]
	bl FUN_0200C3DC
	str r6, [r5, r7]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _0223C71A
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223C730: .word 0x000009DC

	thumb_func_start MOD12_0223C734
MOD12_0223C734: ; 0x0223C734
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r5, r0, #0
	add r0, #0x84
	ldr r0, [r0]
	mov r1, #5
	bl NewString_ReadMsgData
	str r0, [sp, #0x38]
	add r0, r5, #0
	add r0, #0x84
	ldr r0, [r0]
	mov r1, #6
	bl NewString_ReadMsgData
	str r0, [sp, #0x34]
	add r0, r5, #0
	add r0, #0x84
	ldr r0, [r0]
	mov r1, #7
	bl NewString_ReadMsgData
	str r0, [sp, #0x30]
	mov r0, #0
	ldr r1, _0223C868 ; =0x000009E8
	str r0, [sp, #0x3c]
	add r0, r5, r1
	str r0, [sp, #0x2c]
	add r0, r1, #0
	add r0, #0x3c
	add r1, #0x78
	add r4, r5, #0
	add r7, r5, r0
	add r6, r5, r1
_0223C778:
	ldr r0, [sp, #0x2c]
	add r3, r5, #0
	str r0, [sp]
	ldr r0, [sp, #0x38]
	add r3, #0x94
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, _0223C86C ; =0x000B0C00
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, _0223C870 ; =0x000080E9
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	str r0, [sp, #0x1c]
	mov r0, #1
	str r0, [sp, #0x20]
	str r0, [sp, #0x24]
	mov r0, #0xc
	str r0, [sp, #0x28]
	ldr r1, [r5, #0x60]
	ldr r2, [r5, #0x5c]
	ldr r3, [r3]
	mov r0, #0x17
	bl MOD12_02231380
	ldr r0, _0223C868 ; =0x000009E8
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_020119D0
	add r3, r5, #0
	ldr r0, [sp, #0x34]
	str r7, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, _0223C86C ; =0x000B0C00
	add r3, #0x94
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, _0223C870 ; =0x000080E9
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	str r0, [sp, #0x1c]
	mov r0, #1
	str r0, [sp, #0x20]
	str r0, [sp, #0x24]
	mov r0, #0xc
	str r0, [sp, #0x28]
	ldr r1, [r5, #0x60]
	ldr r2, [r5, #0x5c]
	ldr r3, [r3]
	mov r0, #0x17
	bl MOD12_02231380
	ldr r0, _0223C874 ; =0x00000A24
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_020119D0
	add r3, r5, #0
	ldr r0, [sp, #0x30]
	str r6, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, _0223C86C ; =0x000B0C00
	add r3, #0x94
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, _0223C870 ; =0x000080E9
	str r0, [sp, #0x14]
	mov r0, #0
	str r0, [sp, #0x18]
	str r0, [sp, #0x1c]
	mov r0, #1
	str r0, [sp, #0x20]
	str r0, [sp, #0x24]
	mov r0, #0xc
	str r0, [sp, #0x28]
	ldr r1, [r5, #0x60]
	ldr r2, [r5, #0x5c]
	ldr r3, [r3]
	mov r0, #0x17
	bl MOD12_02231380
	mov r0, #0xa6
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020119D0
	ldr r0, [sp, #0x2c]
	add r4, #0x14
	add r0, #0x14
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x3c]
	add r7, #0x14
	add r0, r0, #1
	add r6, #0x14
	str r0, [sp, #0x3c]
	cmp r0, #3
	blt _0223C778
	ldr r0, [sp, #0x38]
	bl String_dtor
	ldr r0, [sp, #0x34]
	bl String_dtor
	ldr r0, [sp, #0x30]
	bl String_dtor
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223C868: .word 0x000009E8
_0223C86C: .word 0x000B0C00
_0223C870: .word 0x000080E9
_0223C874: .word 0x00000A24

	thumb_func_start MOD12_0223C878
MOD12_0223C878: ; 0x0223C878
	push {r3, r4, r5, r6, r7, lr}
	ldr r1, _0223C89C ; =0x000009E8
	mov r7, #0
	add r6, r0, r1
_0223C880:
	mov r4, #0
	add r5, r6, #0
_0223C884:
	add r0, r5, #0
	bl MOD12_0223147C
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #3
	blt _0223C884
	add r7, r7, #1
	add r6, #0x3c
	cmp r7, #3
	blt _0223C880
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223C89C: .word 0x000009E8

	thumb_func_start MOD12_0223C8A0
MOD12_0223C8A0: ; 0x0223C8A0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r4, [sp, #0x2c]
	add r5, r0, #0
	str r3, [sp]
	cmp r4, #0
	bne _0223C8B2
	str r4, [sp, #4]
	b _0223C8B6
_0223C8B2:
	sub r0, r4, #1
	str r0, [sp, #4]
_0223C8B6:
	mov r0, #0x9a
	lsl r0, r0, #4
	add r2, r5, r0
	ldr r0, [sp, #4]
	mov r1, #0x14
	mul r1, r0
	add r6, r2, r1
	ldr r0, [r6, #8]
	cmp r0, #0
	beq _0223C8CE
	bl FUN_0200CAB4
_0223C8CE:
	add r0, r6, #0
	mov r1, #0
	mov r2, #0x14
	bl MI_CpuFill8
	ldr r1, _0223C980 ; =MOD12_022461E4
	lsl r2, r4, #2
	ldrsh r0, [r1, r2]
	add r1, r1, r2
	str r0, [sp, #0xc]
	mov r0, #2
	ldrsh r0, [r1, r0]
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, _0223C984 ; =0x000009DC
	ldr r0, [r1, r0]
	ldr r1, [sp]
	str r0, [r6]
	bl FUN_0200C5C0
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #8]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	mov r3, #1
	ldr r0, [r6]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	lsl r3, r3, #0x14
	bl FUN_0200C750
	ldr r0, [r6]
	ldr r0, [r0]
	bl FUN_0200C59C
	ldr r0, [r6]
	mov r1, #1
	bl FUN_0200C644
	ldr r0, [sp, #4]
	mov r1, #0x14
	add r7, r0, #0
	mov r4, #0
	mul r7, r1
	b _0223C940
_0223C92C:
	mov r0, #0x3c
	mul r0, r4
	add r0, r5, r0
	add r1, r0, r7
	ldr r0, _0223C988 ; =0x000009E8
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_020119D0
	add r4, r4, #1
_0223C940:
	cmp r4, #3
	blt _0223C92C
	ldr r0, _0223C988 ; =0x000009E8
	mov r1, #0x3c
	add r2, r5, r0
	ldr r0, [sp]
	mov r3, #1
	mul r1, r0
	add r2, r2, r1
	ldr r0, [sp, #4]
	mov r1, #0x14
	mul r1, r0
	add r0, r2, r1
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #8]
	str r0, [r6, #4]
	bl MOD12_02231490
	ldr r0, [r6, #4]
	mov r1, #1
	ldr r0, [r0]
	bl FUN_020119D0
	ldr r0, _0223C98C ; =MOD12_0223C994
	ldr r2, _0223C990 ; =0x00009D08
	add r1, r6, #0
	bl FUN_0200CA44
	str r0, [r6, #8]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223C980: .word MOD12_022461E4
_0223C984: .word 0x000009DC
_0223C988: .word 0x000009E8
_0223C98C: .word MOD12_0223C994
_0223C990: .word 0x00009D08

	thumb_func_start MOD12_0223C994
MOD12_0223C994: ; 0x0223C994
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _0223C9A8
	cmp r0, #1
	beq _0223C9E6
	b _0223C9FA
_0223C9A8:
	ldr r0, [r4, #4]
	add r1, sp, #4
	ldr r0, [r0]
	add r2, sp, #0
	bl FUN_020119A4
	ldr r0, [sp]
	ldr r1, [sp, #4]
	sub r2, r0, #4
	str r2, [sp]
	ldr r0, [r4, #4]
	ldr r0, [r0]
	bl FUN_020118C4
	mov r1, #0
	ldr r0, [r4]
	sub r2, r1, #4
	bl FUN_0200C82C
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	cmp r0, #4
	ble _0223CA16
	mov r0, #0
	str r0, [r4, #0xc]
	ldrb r0, [r4, #0x10]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223C9E6:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	cmp r0, #0xe
	ble _0223CA16
	ldrb r0, [r4, #0x10]
	add sp, #8
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223C9FA:
	ldr r0, [r4, #4]
	mov r1, #0
	ldr r0, [r0]
	bl FUN_020119D0
	ldr r0, [r4]
	mov r1, #0
	bl FUN_0200C644
	mov r0, #0
	str r0, [r4, #8]
	add r0, r5, #0
	bl FUN_0200CAB4
_0223CA16:
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_0223CA1C
MOD12_0223CA1C: ; 0x0223CA1C
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	ldr r7, _0223CA40 ; =0x000009A8
	add r5, r0, #0
	add r6, r4, #0
_0223CA26:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _0223CA34
	bl FUN_0200CAB4
	ldr r0, _0223CA40 ; =0x000009A8
	str r6, [r5, r0]
_0223CA34:
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #3
	blt _0223CA26
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223CA40: .word 0x000009A8

	thumb_func_start MOD12_0223CA44
MOD12_0223CA44: ; 0x0223CA44
	push {r4, r5, lr}
	sub sp, #0xc
	mov r2, #1
	str r2, [sp]
	str r2, [sp, #4]
	ldr r2, _0223CA8C ; =0x000080F0
	mov r3, #0x40
	str r2, [sp, #8]
	mov r2, #0x2e
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223CA90 ; =0x000080ED
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x41
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223CA90 ; =0x000080ED
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x42
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0223CA8C: .word 0x000080F0
_0223CA90: .word 0x000080ED

	thumb_func_start MOD12_0223CA94
MOD12_0223CA94: ; 0x0223CA94
	push {r4, lr}
	ldr r1, _0223CAB0 ; =0x000080F0
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _0223CAB4 ; =0x000080ED
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _0223CAB4 ; =0x000080ED
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_0223CAB0: .word 0x000080F0
_0223CAB4: .word 0x000080ED

	thumb_func_start MOD12_0223CAB8
MOD12_0223CAB8: ; 0x0223CAB8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, r1, #0
	add r1, r2, #0
	ldr r2, _0223CAD8 ; =MOD12_02246244
	bl FUN_0200C154
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_0200C59C
	mov r0, #0x7a
	lsl r0, r0, #2
	str r4, [r5, r0]
	pop {r3, r4, r5, pc}
	nop
_0223CAD8: .word MOD12_02246244

	thumb_func_start MOD12_0223CADC
MOD12_0223CADC: ; 0x0223CADC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0223CAF6
	bl FUN_0200C3DC
	mov r0, #0x7a
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
_0223CAF6:
	pop {r4, pc}

	thumb_func_start MOD12_0223CAF8
MOD12_0223CAF8: ; 0x0223CAF8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0223CB10 ; =MOD12_0223CB28
	ldr r2, _0223CB14 ; =0x00009CAE
	add r1, r4, #0
	bl FUN_0200CA44
	mov r1, #2
	lsl r1, r1, #8
	str r0, [r4, r1]
	pop {r4, pc}
	nop
_0223CB10: .word MOD12_0223CB28
_0223CB14: .word 0x00009CAE

	thumb_func_start MOD12_0223CB18
MOD12_0223CB18: ; 0x0223CB18
	mov r1, #2
	lsl r1, r1, #8
	ldr r3, _0223CB24 ; =FUN_0200CAB4
	ldr r0, [r0, r1]
	bx r3
	nop
_0223CB24: .word FUN_0200CAB4

	thumb_func_start MOD12_0223CB28
MOD12_0223CB28: ; 0x0223CB28
	push {r3, lr}
	ldr r2, [r1]
	ldr r0, _0223CB50 ; =0x00000123
	mov r3, #1
	ldrb r2, [r2, r0]
	add r0, #0xd9
	ldr r0, [r1, r0]
	lsl r2, r2, #4
	add r2, r1, r2
	ldr r1, [r2, #0x1c]
	ldr r2, [r2, #0x20]
	lsl r1, r1, #0x10
	sub r2, #0x28
	lsl r2, r2, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	lsl r3, r3, #0x14
	bl FUN_0200C750
	pop {r3, pc}
	.align 2, 0
_0223CB50: .word 0x00000123

	thumb_func_start MOD12_0223CB54
MOD12_0223CB54: ; 0x0223CB54
	push {r4, r5, lr}
	sub sp, #0xc
	mov r2, #1
	str r2, [sp]
	str r2, [sp, #4]
	ldr r2, _0223CB9C ; =0x000080F2
	mov r3, #0x5a
	str r2, [sp, #8]
	mov r2, #0x2e
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223CBA0 ; =0x000080EF
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x59
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223CBA0 ; =0x000080EF
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x58
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0223CB9C: .word 0x000080F2
_0223CBA0: .word 0x000080EF

	thumb_func_start MOD12_0223CBA4
MOD12_0223CBA4: ; 0x0223CBA4
	push {r4, lr}
	ldr r1, _0223CBC0 ; =0x000080F2
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _0223CBC4 ; =0x000080EF
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _0223CBC4 ; =0x000080EF
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_0223CBC0: .word 0x000080F2
_0223CBC4: .word 0x000080EF

	thumb_func_start MOD12_0223CBC8
MOD12_0223CBC8: ; 0x0223CBC8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp]
	mov r0, #0
	str r1, [sp, #4]
	str r0, [sp, #0xc]
	ldr r4, [sp]
	mov r1, #2
	add r0, r4, #0
	lsl r1, r1, #8
	ldr r6, [sp, #0xc]
	str r2, [sp, #8]
	add r7, r0, #4
	add r5, r0, r1
_0223CBE4:
	ldr r0, [sp, #4]
	ldr r1, [sp, #8]
	ldr r2, _0223CC60 ; =MOD12_022462AC
	bl FUN_0200C154
	mov r1, #0x81
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	ldr r0, [r0]
	bl FUN_0200C59C
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_0200C840
	ldr r1, [sp, #0xc]
	ldr r0, _0223CC64 ; =0x00000213
	strb r1, [r4, r0]
	sub r0, r0, #7
	str r7, [r4, r0]
	ldr r0, [sp]
	mov r1, #2
	ldr r0, [r0]
	ldr r0, [r0, r6]
	bl FUN_02068E14
	mov r1, #0x85
	lsl r1, r1, #2
	strb r0, [r4, r1]
	mov r1, #1
	add r0, r5, #0
	add r2, r1, #0
	bl MOD12_0223CD38
	ldr r0, _0223CC68 ; =MOD12_0223CCBC
	ldr r2, _0223CC6C ; =0x0000A08C
	add r1, r5, #0
	bl FUN_0200CA44
	mov r1, #2
	lsl r1, r1, #8
	str r0, [r4, r1]
	ldr r0, [sp, #0xc]
	add r4, #0x18
	add r0, r0, #1
	add r7, #0x10
	add r6, r6, #4
	add r5, #0x18
	str r0, [sp, #0xc]
	cmp r0, #4
	blt _0223CBE4
	ldr r0, [sp]
	mov r1, #0
	bl MOD12_0223CC9C
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223CC60: .word MOD12_022462AC
_0223CC64: .word 0x00000213
_0223CC68: .word MOD12_0223CCBC
_0223CC6C: .word 0x0000A08C

	thumb_func_start MOD12_0223CC70
MOD12_0223CC70: ; 0x0223CC70
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	mov r7, #0x81
	add r5, r0, #0
	add r6, r4, #0
	lsl r7, r7, #2
_0223CC7C:
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0200C3DC
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r5, r0]
	bl FUN_0200CAB4
	str r6, [r5, r7]
	add r4, r4, #1
	add r5, #0x18
	cmp r4, #4
	blt _0223CC7C
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD12_0223CC9C
MOD12_0223CC9C: ; 0x0223CC9C
	push {r3, r4, r5, r6, r7, lr}
	mov r7, #0x81
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #0
	lsl r7, r7, #2
_0223CCA8:
	ldr r0, [r5, r7]
	add r1, r6, #0
	bl FUN_0200C644
	add r4, r4, #1
	add r5, #0x18
	cmp r4, #4
	blt _0223CCA8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_0223CCBC
MOD12_0223CCBC: ; 0x0223CCBC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r0, [r5, #0xc]
	ldr r6, [r0, #4]
	ldr r4, [r0, #8]
	ldr r0, [r0, #0xc]
	bl MOD12_0223D06C
	mov r1, #0x14
	ldrsb r2, [r5, r1]
	mov r1, #0x28
	sub r2, r1, r2
	add r1, r2, #0
	mul r1, r0
	asr r2, r1, #7
	lsr r2, r2, #0x18
	add r2, r1, r2
	asr r1, r2, #8
	add r4, r4, r1
	mov r1, #0x64
	mul r1, r0
	asr r0, r1, #7
	lsr r0, r0, #0x18
	add r0, r1, r0
	asr r0, r0, #8
	bl _fflt
	ldr r1, _0223CD34 ; =0x42C80000
	bl _fdiv
	add r7, r0, #0
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _0223CD16
	add r1, sp, #0
	mov r3, #1
	ldr r0, [r5, #4]
	add r1, #2
	add r2, sp, #0
	lsl r3, r3, #0x14
	bl FUN_0200C7F0
	add r1, sp, #0
	mov r0, #0
	ldrsh r4, [r1, r0]
_0223CD16:
	lsl r1, r6, #0x10
	lsl r2, r4, #0x10
	mov r3, #1
	ldr r0, [r5, #4]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	lsl r3, r3, #0x14
	bl FUN_0200C750
	ldr r0, [r5, #4]
	add r1, r7, #0
	add r2, r7, #0
	bl FUN_0200C884
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223CD34: .word 0x42C80000

	thumb_func_start MOD12_0223CD38
MOD12_0223CD38: ; 0x0223CD38
	strb r1, [r0, #0x11]
	strb r2, [r0, #0x12]
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0223CD40
MOD12_0223CD40: ; 0x0223CD40
	push {r4, r5, lr}
	sub sp, #0xc
	mov r2, #1
	str r2, [sp]
	str r2, [sp, #4]
	ldr r2, _0223CD88 ; =0x000080F3
	mov r3, #0x5d
	str r2, [sp, #8]
	mov r2, #0x2e
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223CD8C ; =0x000080F0
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x5c
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223CD8C ; =0x000080F0
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x5b
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0223CD88: .word 0x000080F3
_0223CD8C: .word 0x000080F0

	thumb_func_start MOD12_0223CD90
MOD12_0223CD90: ; 0x0223CD90
	push {r4, lr}
	ldr r1, _0223CDAC ; =0x000080F3
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _0223CDB0 ; =0x000080F0
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _0223CDB0 ; =0x000080F0
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_0223CDAC: .word 0x000080F3
_0223CDB0: .word 0x000080F0

	thumb_func_start MOD12_0223CDB4
MOD12_0223CDB4: ; 0x0223CDB4
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0223CDB8
MOD12_0223CDB8: ; 0x0223CDB8
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0223CDBC
MOD12_0223CDBC: ; 0x0223CDBC
	push {r4, r5, lr}
	sub sp, #0xc
	mov r2, #1
	str r2, [sp]
	str r2, [sp, #4]
	ldr r2, _0223CE04 ; =0x000080F4
	mov r3, #0x60
	str r2, [sp, #8]
	mov r2, #0x2e
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223CE08 ; =0x000080F1
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x5f
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223CE08 ; =0x000080F1
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x5e
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0223CE04: .word 0x000080F4
_0223CE08: .word 0x000080F1

	thumb_func_start MOD12_0223CE0C
MOD12_0223CE0C: ; 0x0223CE0C
	push {r4, lr}
	ldr r1, _0223CE28 ; =0x000080F4
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _0223CE2C ; =0x000080F1
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _0223CE2C ; =0x000080F1
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_0223CE28: .word 0x000080F4
_0223CE2C: .word 0x000080F1

	thumb_func_start MOD12_0223CE30
MOD12_0223CE30: ; 0x0223CE30
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0xad
	lsl r0, r0, #2
	add r7, r1, #0
	add r1, r5, r0
	sub r0, #0xf4
	mul r0, r7
	add r4, r1, r0
	str r2, [sp]
	mov r1, #0
_0223CE48:
	ldr r0, [r4]
	cmp r0, #0
	beq _0223CE56
	add r1, r1, #1
	add r4, #0x1c
	cmp r1, #0x10
	blt _0223CE48
_0223CE56:
	cmp r1, #0x10
	bne _0223CE60
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223CE60:
	ldr r0, [r5, #0x6c]
	ldr r1, [r5, #0x70]
	ldr r2, _0223CF2C ; =MOD12_02246348
	bl FUN_0200C154
	add r6, r0, #0
	bne _0223CE74
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223CE74:
	lsl r1, r7, #4
	add r2, r5, r1
	ldr r1, [r2, #0x1c]
	ldr r7, [r2, #0x20]
	str r1, [sp, #4]
	ldr r1, [sp]
	bl FUN_0200C5C0
	ldr r1, [sp, #4]
	lsl r2, r7, #0x10
	lsl r1, r1, #0x10
	mov r3, #1
	add r0, r6, #0
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	lsl r3, r3, #0x14
	bl FUN_0200C750
	ldr r0, [r6]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r6]
	bl FUN_0200C59C
	ldr r0, [r5]
	bl FUN_02082878
	ldr r2, _0223CF30 ; =0x04000280
	mov r1, #0
	strh r1, [r2]
	str r0, [r2, #0x10]
	mov r0, #5
	lsl r0, r0, #8
	add r2, #0x18
	str r0, [r2]
	str r1, [r2, #4]
	add r0, r4, #0
	mov r2, #0x1c
	bl MI_CpuFill8
	ldr r0, [sp, #4]
	str r6, [r4, #4]
	lsl r0, r0, #8
	str r0, [r4, #8]
	lsl r0, r7, #8
	ldr r2, _0223CF30 ; =0x04000280
	str r0, [r4, #0xc]
	lsr r0, r2, #0xb
_0223CED6:
	ldrh r1, [r2]
	tst r1, r0
	bne _0223CED6
	ldr r0, _0223CF34 ; =0x040002A8
	ldr r1, [r0]
	mov r0, #1
	str r1, [r4, #0x10]
	tst r0, r1
	beq _0223CEEC
	neg r0, r1
	str r0, [r4, #0x10]
_0223CEEC:
	ldr r0, [r5]
	bl FUN_02082878
	ldr r2, _0223CF38 ; =0x04000290
	mov r1, #0xf
	str r0, [r2]
	lsl r1, r1, #8
	add r2, #8
	mov r0, #0
	str r1, [r2]
	str r0, [r2, #4]
	ldr r2, _0223CF30 ; =0x04000280
	lsr r0, r2, #0xb
_0223CF06:
	ldrh r1, [r2]
	tst r1, r0
	bne _0223CF06
	ldr r0, _0223CF34 ; =0x040002A8
	ldr r2, _0223CF3C ; =0x00009C40
	ldr r1, [r0]
	lsr r0, r0, #0x10
	add r0, r1, r0
	neg r0, r0
	str r0, [r4, #0x14]
	ldr r0, _0223CF40 ; =MOD12_0223CF44
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4]
	mov r0, #1
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223CF2C: .word MOD12_02246348
_0223CF30: .word 0x04000280
_0223CF34: .word 0x040002A8
_0223CF38: .word 0x04000290
_0223CF3C: .word 0x00009C40
_0223CF40: .word MOD12_0223CF44

	thumb_func_start MOD12_0223CF44
MOD12_0223CF44: ; 0x0223CF44
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r1, [r4, #8]
	ldr r0, [r4, #0x10]
	add r0, r1, r0
	str r0, [r4, #8]
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x14]
	add r0, r1, r0
	str r0, [r4, #0xc]
	mov r0, #2
	ldr r1, [r4, #0x14]
	lsl r0, r0, #8
	add r0, r1, r0
	str r0, [r4, #0x14]
	ldrh r0, [r4, #0x18]
	add r0, r0, #1
	strh r0, [r4, #0x18]
	ldrh r0, [r4, #0x18]
	cmp r0, #0xa
	bhi _0223CF8A
	mov r0, #0x11
	ldr r1, [r4, #8]
	lsl r0, r0, #0xc
	cmp r1, r0
	bgt _0223CF8A
	ldr r0, _0223CFF0 ; =0xFFFEF000
	cmp r1, r0
	blt _0223CF8A
	mov r0, #0xd
	ldr r2, [r4, #0xc]
	lsl r0, r0, #0xc
	cmp r2, r0
	ble _0223CF9E
_0223CF8A:
	ldr r0, [r4, #4]
	bl FUN_0200C3DC
	add r0, r5, #0
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #4]
	str r0, [r4]
	pop {r3, r4, r5, pc}
_0223CF9E:
	ldr r0, _0223CFF4 ; =0x04000280
	mov r3, #0
	strh r3, [r0]
	str r1, [r0, #0x10]
	add r1, r0, #0
	lsr r2, r0, #0x12
	add r1, #0x18
	str r2, [r1]
	str r3, [r1, #4]
	lsr r1, r0, #0xb
_0223CFB2:
	ldrh r2, [r0]
	tst r2, r1
	bne _0223CFB2
	ldr r3, _0223CFF8 ; =0x040002A0
	ldr r2, [r4, #0xc]
	add r0, r3, #0
	ldr r1, [r3]
	sub r0, #0x10
	str r2, [r0]
	lsr r2, r3, #0x12
	sub r3, #8
	mov r0, #0
	str r2, [r3]
	str r0, [r3, #4]
	ldr r3, _0223CFF4 ; =0x04000280
	lsr r0, r3, #0xb
_0223CFD2:
	ldrh r2, [r3]
	tst r2, r0
	bne _0223CFD2
	ldr r2, _0223CFF8 ; =0x040002A0
	lsl r1, r1, #0x10
	ldr r2, [r2]
	mov r3, #1
	lsl r2, r2, #0x10
	ldr r0, [r4, #4]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	lsl r3, r3, #0x14
	bl FUN_0200C750
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223CFF0: .word 0xFFFEF000
_0223CFF4: .word 0x04000280
_0223CFF8: .word 0x040002A0

	thumb_func_start MOD12_0223CFFC
MOD12_0223CFFC: ; 0x0223CFFC
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	str r1, [sp]
	cmp r2, #2
	beq _0223D058
	add r0, r1, #0
	lsl r0, r0, #1
	add r1, r7, r0
	ldr r0, _0223D05C ; =0x00000ADA
	ldrsh r0, [r1, r0]
	cmp r0, #0
	beq _0223D058
	ldr r1, _0223D060 ; =0x04000280
	mov r6, #0
	strh r6, [r1]
	str r0, [r1, #0x10]
	mov r0, #2
	add r1, #0x18
	str r0, [r1]
	str r6, [r1, #4]
	cmp r3, #0
	beq _0223D02A
	mov r6, #1
_0223D02A:
	ldr r2, _0223D060 ; =0x04000280
	lsr r0, r2, #0xb
_0223D02E:
	ldrh r1, [r2]
	tst r1, r0
	bne _0223D02E
	ldr r0, _0223D064 ; =0x040002A0
	ldr r5, [r0]
	cmp r5, #0x10
	ble _0223D03E
	mov r5, #0x10
_0223D03E:
	mov r4, #0
	cmp r5, #0
	ble _0223D058
_0223D044:
	ldr r1, [sp]
	add r0, r7, #0
	add r2, r6, #0
	bl MOD12_0223CE30
	cmp r0, #0
	beq _0223D058
	add r4, r4, #1
	cmp r4, r5
	blt _0223D044
_0223D058:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223D05C: .word 0x00000ADA
_0223D060: .word 0x04000280
_0223D064: .word 0x040002A0

	thumb_func_start MOD12_0223D068
MOD12_0223D068: ; 0x0223D068
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0223D06C
MOD12_0223D06C: ; 0x0223D06C
	ldr r1, _0223D098 ; =0xFFFFFD80
	cmp r0, r1
	bne _0223D076
	mov r0, #0xc0
	bx lr
_0223D076:
	add r1, #0x80
	cmp r0, r1
	bne _0223D082
	mov r0, #1
	lsl r0, r0, #8
	bx lr
_0223D082:
	mov r1, #0xa
	lsl r1, r1, #6
	add r0, r0, r1
	lsl r1, r0, #6
	asr r0, r1, #6
	lsr r0, r0, #0x19
	add r0, r1, r0
	asr r0, r0, #7
	add r0, #0xc0
	bx lr
	nop
_0223D098: .word 0xFFFFFD80

	thumb_func_start MOD12_0223D09C
MOD12_0223D09C: ; 0x0223D09C
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0xc]
	bl MOD12_0223D06C
	mov r1, #1
	lsl r1, r1, #8
	cmp r0, r1
	bne _0223D0B2
	lsl r1, r1, #4
	b _0223D0BC
_0223D0B2:
	lsl r1, r0, #0xc
	asr r0, r1, #7
	lsr r0, r0, #0x18
	add r0, r1, r0
	asr r1, r0, #8
_0223D0BC:
	mov r3, #1
	ldr r0, [r4]
	add r2, r1, #0
	lsl r3, r3, #0xc
	bl MOD05_021DD60C
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_0223D0CC
MOD12_0223D0CC: ; 0x0223D0CC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r6, #0
	add r4, r5, #4
_0223D0D4:
	ldr r0, [r5, #0x48]
	add r1, r4, #0
	bl MOD12_0223D09C
	add r6, r6, #1
	add r4, #0x10
	add r5, r5, #4
	cmp r6, #4
	blt _0223D0D4
	pop {r4, r5, r6, pc}

	thumb_func_start MOD12_0223D0E8
MOD12_0223D0E8: ; 0x0223D0E8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldrb r0, [r2, #2]
	str r2, [sp, #0x10]
	cmp r0, r1
	bne _0223D0FC
	mov r0, #0
	str r0, [sp, #0x14]
	b _0223D100
_0223D0FC:
	mov r0, #1
	str r0, [sp, #0x14]
_0223D100:
	ldr r0, [sp, #0x10]
	mov r4, #0
	ldrb r0, [r0, #6]
	lsl r6, r0, #3
	ldr r0, [sp, #0x10]
	ldrb r1, [r0, #7]
	ldr r0, _0223D1C0 ; =MOD12_022461DC
	ldrb r7, [r0, r1]
	b _0223D156
_0223D112:
	lsl r0, r4, #2
	add r0, r5, r0
	add r0, #0xec
	ldr r0, [r0]
	cmp r0, #0
	beq _0223D154
	add r1, sp, #0x18
	mov r3, #1
	add r1, #2
	add r2, sp, #0x18
	lsl r3, r3, #0x14
	bl FUN_0200C7F0
	add r1, sp, #0x18
	mov r0, #2
	ldrsh r0, [r1, r0]
	cmp r0, r6
	bne _0223D154
	mov r0, #0
	ldrsh r0, [r1, r0]
	cmp r0, r7
	bne _0223D154
	lsl r0, r4, #2
	add r0, r5, r0
	add r0, #0xec
	ldr r0, [r0]
	bl FUN_0200C5CC
	cmp r0, #2
	beq _0223D154
	add sp, #0x1c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223D154:
	add r4, r4, #1
_0223D156:
	cmp r4, #0x44
	blt _0223D112
	ldr r0, [sp, #0x10]
	ldr r3, [sp, #0x14]
	ldrb r0, [r0, #3]
	str r0, [sp]
	str r6, [sp, #4]
	ldr r0, [sp, #0x10]
	str r7, [sp, #8]
	ldrb r0, [r0, #7]
	str r0, [sp, #0xc]
	add r0, r5, #0
	ldr r1, [r5, #0x6c]
	ldr r2, [r5, #0x70]
	add r0, #0x14
	bl MOD12_0223C52C
	ldr r0, [sp, #0x10]
	ldrb r0, [r0, #7]
	cmp r0, #0
	bne _0223D1BA
	ldr r0, [sp, #0x14]
	cmp r0, #1
	bne _0223D1BA
	ldr r0, [r5]
	ldr r1, _0223D1C4 ; =0x00000123
	ldr r2, _0223D1C8 ; =0x00000AD5
	ldrb r0, [r0, r1]
	add r6, #0x80
	add r0, r5, r0
	ldrb r3, [r0, r2]
	ldr r0, _0223D1C0 ; =MOD12_022461DC
	ldrb r3, [r0, r3]
	ldr r0, [sp, #0x10]
	ldrb r0, [r0, #3]
	str r0, [sp]
	str r6, [sp, #4]
	str r3, [sp, #8]
	ldr r0, [r5]
	mov r3, #2
	ldrb r0, [r0, r1]
	add r0, r5, r0
	ldrb r0, [r0, r2]
	str r0, [sp, #0xc]
	add r0, r5, #0
	ldr r1, [r5, #0x6c]
	ldr r2, [r5, #0x70]
	add r0, #0x14
	bl MOD12_0223C52C
_0223D1BA:
	mov r0, #1
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223D1C0: .word MOD12_022461DC
_0223D1C4: .word 0x00000123
_0223D1C8: .word 0x00000AD5

	thumb_func_start MOD12_0223D1CC
MOD12_0223D1CC: ; 0x0223D1CC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldrb r1, [r4, #5]
	add r5, r0, #0
	ldrb r0, [r4, #2]
	cmp r1, #3
	bhi _0223D200
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223D1E8: ; jump table
	.short _0223D1F0 - _0223D1E8 - 2 ; case 0
	.short _0223D1F4 - _0223D1E8 - 2 ; case 1
	.short _0223D1F8 - _0223D1E8 - 2 ; case 2
	.short _0223D1FC - _0223D1E8 - 2 ; case 3
_0223D1F0:
	mov r2, #2
	b _0223D202
_0223D1F4:
	mov r2, #2
	b _0223D202
_0223D1F8:
	mov r2, #1
	b _0223D202
_0223D1FC:
	mov r2, #1
	b _0223D202
_0223D200:
	mov r2, #0
_0223D202:
	ldr r1, _0223D498 ; =0x00000ADA
	lsl r0, r0, #1
	add r1, r5, r1
	add r3, r1, r0
	str r3, [sp, #8]
	ldrsh r3, [r1, r0]
	add r2, r3, r2
	strh r2, [r1, r0]
	ldrb r0, [r4, #7]
	cmp r0, #0
	bne _0223D262
	ldr r0, _0223D49C ; =0x00001BA0
	mov r2, #0
	add r3, r5, r0
	add r6, r5, #0
	sub r7, r0, #2
_0223D222:
	ldrb r0, [r3]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	bne _0223D250
	mov r0, #0xa
	mul r0, r2
	ldrh r1, [r4]
	ldr r2, _0223D4A0 ; =0x00001B98
	add r0, r5, r0
	strh r1, [r0, r2]
	ldrh r3, [r4, #2]
	add r1, r2, #2
	strh r3, [r0, r1]
	ldrh r3, [r4, #4]
	add r1, r2, #4
	strh r3, [r0, r1]
	add r1, r2, #6
	ldrh r3, [r4, #6]
	add r2, #8
	strh r3, [r0, r1]
	ldrh r1, [r4, #8]
	strh r1, [r0, r2]
	b _0223D262
_0223D250:
	ldrb r1, [r4, #6]
	ldrb r0, [r6, r7]
	cmp r1, r0
	beq _0223D262
	add r2, r2, #1
	add r3, #0xa
	add r6, #0xa
	cmp r2, #8
	blt _0223D222
_0223D262:
	ldrb r0, [r4, #4]
	cmp r0, #0
	bne _0223D280
	ldr r0, _0223D4A4 ; =0x00000AB9
	ldrb r2, [r4, #2]
	add r3, r5, r0
	add r0, r0, #4
	ldrb r1, [r3, r2]
	add r1, r1, #1
	strb r1, [r3, r2]
	ldrb r1, [r4, #2]
	add r2, r5, r0
	ldrb r0, [r2, r1]
	add r0, r0, #1
	b _0223D290
_0223D280:
	ldrb r1, [r4, #2]
	mov r0, #0
	add r2, r5, r1
	ldr r1, _0223D4A4 ; =0x00000AB9
	strb r0, [r2, r1]
	ldrb r2, [r4, #2]
	add r1, r1, #4
	add r2, r5, r2
_0223D290:
	strb r0, [r2, r1]
	ldrb r0, [r4, #4]
	cmp r0, #2
	beq _0223D2A6
	ldr r0, _0223D4A8 ; =0x00000AC8
	ldrb r1, [r4, #2]
	add r2, r5, r0
	ldrb r0, [r2, r1]
	add r0, r0, #1
	strb r0, [r2, r1]
	b _0223D2BC
_0223D2A6:
	ldr r0, _0223D4AC ; =0x00000AC1
	ldrb r2, [r4, #2]
	add r3, r5, r0
	add r0, r0, #7
	ldrb r1, [r3, r2]
	add r1, r1, #1
	strb r1, [r3, r2]
	ldrb r1, [r4, #2]
	mov r2, #0
	add r1, r5, r1
	strb r2, [r1, r0]
_0223D2BC:
	ldrb r0, [r4, #7]
	cmp r0, #0
	beq _0223D2EE
	ldrb r0, [r4, #4]
	cmp r0, #0
	beq _0223D2D2
	cmp r0, #1
	beq _0223D2DC
	cmp r0, #2
	beq _0223D2E6
	b _0223D2EE
_0223D2D2:
	ldr r0, _0223D4B0 ; =0x00000AC5
	ldrb r1, [r5, r0]
	add r1, r1, #1
	strb r1, [r5, r0]
	b _0223D2EE
_0223D2DC:
	ldr r0, _0223D4B4 ; =0x00000AC6
	ldrb r1, [r5, r0]
	add r1, r1, #1
	strb r1, [r5, r0]
	b _0223D2EE
_0223D2E6:
	ldr r0, _0223D4B8 ; =0x00000AC7
	ldrb r1, [r5, r0]
	add r1, r1, #1
	strb r1, [r5, r0]
_0223D2EE:
	ldrb r0, [r4, #2]
	str r0, [sp]
	ldrb r0, [r4, #7]
	str r0, [sp, #4]
	add r0, r5, #0
	ldrb r3, [r4, #4]
	ldr r1, [r5, #0x6c]
	ldr r2, [r5, #0x70]
	add r0, #0x14
	bl MOD12_0223C8A0
	ldr r2, [r5]
	ldr r1, _0223D4BC ; =0x00000123
	add r0, r5, #0
	ldrb r1, [r2, r1]
	add r2, r4, #0
	bl MOD12_0223D0E8
	ldrb r0, [r4, #8]
	mov r1, #0
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	str r0, [sp]
	ldr r0, [sp, #8]
	ldrsh r0, [r0, r1]
	str r0, [sp, #4]
	ldrb r1, [r4, #2]
	ldrb r2, [r4, #7]
	ldrb r3, [r4, #3]
	add r0, r5, #0
	bl MOD12_0223D4E8
	ldrb r1, [r4, #2]
	ldrb r2, [r4, #4]
	ldrb r3, [r4, #7]
	add r0, r5, #0
	bl MOD12_0223CFFC
	add r0, r5, #0
	add r1, r4, #0
	bl MOD12_0223E788
	ldr r1, [r5]
	ldr r0, _0223D4BC ; =0x00000123
	ldrb r2, [r4, #2]
	ldrb r0, [r1, r0]
	cmp r2, r0
	bne _0223D36E
	ldrb r0, [r4, #4]
	cmp r0, #0
	bne _0223D360
	ldrb r1, [r4, #6]
	add r0, r5, #0
	mov r2, #1
	bl MOD12_0223E9C4
	b _0223D36E
_0223D360:
	cmp r0, #1
	bne _0223D36E
	ldrb r1, [r4, #6]
	add r0, r5, #0
	mov r2, #0
	bl MOD12_0223E9C4
_0223D36E:
	ldrb r1, [r4, #7]
	cmp r1, #0
	bne _0223D3AC
	ldrb r0, [r4, #8]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _0223D3AC
	ldrb r1, [r4, #2]
	ldr r0, _0223D4C0 ; =0x00000AFE
	add r2, r5, r1
	add r1, r0, #0
	sub r1, #0x41
	ldrb r3, [r5, r0]
	ldrb r1, [r2, r1]
	cmp r3, r1
	bne _0223D39A
	add r0, r5, #0
	mov r1, #1
	bl MOD12_0223EA48
	b _0223D3F2
_0223D39A:
	sub r0, #0x3d
	ldrb r0, [r2, r0]
	cmp r0, #0
	bne _0223D3F2
	add r0, r5, #0
	mov r1, #0
	bl MOD12_0223EA48
	b _0223D3F2
_0223D3AC:
	cmp r1, #0
	beq _0223D3F2
	ldrb r0, [r4, #8]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _0223D3F2
	ldr r3, _0223D4B0 ; =0x00000AC5
	add r0, r3, #2
	ldrb r1, [r5, r0]
	add r0, r3, #0
	ldrb r2, [r5, r3]
	add r0, #0x39
	add r3, r3, #1
	ldrb r6, [r5, r0]
	ldrb r3, [r5, r3]
	lsl r0, r6, #1
	add r3, r2, r3
	add r0, r6, r0
	add r3, r1, r3
	cmp r0, r3
	bne _0223D3F2
	cmp r2, r0
	bne _0223D3E6
	add r0, r5, #0
	mov r1, #1
	bl MOD12_0223EA48
	b _0223D3F2
_0223D3E6:
	cmp r1, #0
	bne _0223D3F2
	add r0, r5, #0
	mov r1, #0
	bl MOD12_0223EA48
_0223D3F2:
	ldrb r0, [r4, #8]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _0223D404
	ldr r0, _0223D4C4 ; =0x000006F5
	bl FUN_020054C8
	b _0223D40A
_0223D404:
	ldr r0, _0223D4C8 ; =0x000006F4
	bl FUN_020054C8
_0223D40A:
	ldr r0, _0223D4CC ; =0x00000ACC
	ldrb r0, [r5, r0]
	cmp r0, #0
	beq _0223D426
	beq _0223D492
	ldrb r0, [r4, #7]
	cmp r0, #0
	beq _0223D426
	ldr r1, [r5]
	ldr r0, _0223D4BC ; =0x00000123
	ldrb r2, [r4, #2]
	ldrb r0, [r1, r0]
	cmp r2, r0
	bne _0223D492
_0223D426:
	ldrb r0, [r4, #4]
	cmp r0, #0
	beq _0223D438
	cmp r0, #1
	beq _0223D46E
	cmp r0, #2
	beq _0223D478
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0223D438:
	ldrb r0, [r4, #2]
	add r1, r5, r0
	ldr r0, _0223D4D0 ; =0x00000ABD
	ldrb r1, [r1, r0]
	add r0, #0x41
	ldrb r0, [r5, r0]
	cmp r0, r1
	bne _0223D454
	mov r0, #0x6f
	lsl r0, r0, #4
	bl FUN_020054C8
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0223D454:
	sub r0, r0, #1
	cmp r0, r1
	bne _0223D464
	ldr r0, _0223D4D4 ; =0x000006EF
	bl FUN_020054C8
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0223D464:
	ldr r0, _0223D4D8 ; =0x000006EE
	bl FUN_020054C8
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0223D46E:
	ldr r0, _0223D4DC ; =0x000006F1
	bl FUN_020054C8
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0223D478:
	ldrb r0, [r4, #8]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _0223D48C
	ldr r0, _0223D4E0 ; =0x000006F2
	bl FUN_020054C8
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0223D48C:
	ldr r0, _0223D4E4 ; =0x000005F6
	bl FUN_020054C8
_0223D492:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_0223D498: .word 0x00000ADA
_0223D49C: .word 0x00001BA0
_0223D4A0: .word 0x00001B98
_0223D4A4: .word 0x00000AB9
_0223D4A8: .word 0x00000AC8
_0223D4AC: .word 0x00000AC1
_0223D4B0: .word 0x00000AC5
_0223D4B4: .word 0x00000AC6
_0223D4B8: .word 0x00000AC7
_0223D4BC: .word 0x00000123
_0223D4C0: .word 0x00000AFE
_0223D4C4: .word 0x000006F5
_0223D4C8: .word 0x000006F4
_0223D4CC: .word 0x00000ACC
_0223D4D0: .word 0x00000ABD
_0223D4D4: .word 0x000006EF
_0223D4D8: .word 0x000006EE
_0223D4DC: .word 0x000006F1
_0223D4E0: .word 0x000006F2
_0223D4E4: .word 0x000005F6

	thumb_func_start MOD12_0223D4E8
MOD12_0223D4E8: ; 0x0223D4E8
	push {r4, r5, r6, lr}
	ldr r4, _0223D558 ; =0x00000F3C
	add r5, r0, r4
	mov r0, #0x4c
	add r4, r1, #0
	mul r4, r0
	add r1, r5, r4
	add r4, r1, #0
	add r4, #0x20
	ldrb r4, [r4]
	sub r0, #0x4d
	add r6, r4, #0
	cmp r4, #0x20
	bge _0223D514
_0223D504:
	ldrb r5, [r1, r6]
	cmp r5, #0
	bne _0223D50E
	add r0, r6, #0
	b _0223D514
_0223D50E:
	add r6, r6, #1
	cmp r6, #0x20
	blt _0223D504
_0223D514:
	mov r5, #0
	mvn r5, r5
	cmp r0, r5
	bne _0223D532
	mov r6, #0
	cmp r4, #0
	ble _0223D532
_0223D522:
	ldrb r5, [r1, r6]
	cmp r5, #0
	bne _0223D52C
	add r0, r6, #0
	b _0223D532
_0223D52C:
	add r6, r6, #1
	cmp r6, r4
	blt _0223D522
_0223D532:
	mov r4, #0
	mvn r4, r4
	cmp r0, r4
	bne _0223D540
	bl ErrorHandling
	pop {r4, r5, r6, pc}
_0223D540:
	strb r3, [r1, r0]
	add r0, r1, #0
	add r0, #0x21
	strb r2, [r0]
	add r0, r1, #0
	ldr r2, [sp, #0x10]
	add r0, #0x22
	strb r2, [r0]
	ldr r0, [sp, #0x14]
	add r1, #0x23
	strb r0, [r1]
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223D558: .word 0x00000F3C

	thumb_func_start MOD12_0223D55C
MOD12_0223D55C: ; 0x0223D55C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0223D570 ; =MOD12_0223D5B0
	ldr r2, _0223D574 ; =0x00009862
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #8]
	pop {r4, pc}
	nop
_0223D570: .word MOD12_0223D5B0
_0223D574: .word 0x00009862

	thumb_func_start MOD12_0223D578
MOD12_0223D578: ; 0x0223D578
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #8]
	pop {r4, pc}

	thumb_func_start MOD12_0223D588
MOD12_0223D588: ; 0x0223D588
	ldr r1, _0223D5AC ; =0x00000F3C
	mov r2, #0
	add r1, r0, r1
_0223D58E:
	add r0, r1, #0
	add r0, #0x20
	ldrb r0, [r0]
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _0223D59E
	mov r0, #0
	bx lr
_0223D59E:
	add r2, r2, #1
	add r1, #0x4c
	cmp r2, #4
	blt _0223D58E
	mov r0, #1
	bx lr
	nop
_0223D5AC: .word 0x00000F3C

	thumb_func_start MOD12_0223D5B0
MOD12_0223D5B0: ; 0x0223D5B0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r1, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x18]
	ldr r1, _0223D76C ; =0x00000F3C
	ldr r0, [sp, #0x10]
	ldr r6, [sp, #0x10]
	add r4, r0, r1
	mov r1, #0x85
	lsl r1, r1, #2
	add r0, r0, r1
	ldr r5, [sp, #0x10]
	str r0, [sp, #0x14]
	add r6, #0x18
_0223D5CE:
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	mov r7, #0
	ldrb r0, [r4, r0]
	str r0, [sp, #0x1c]
	cmp r0, #0
	bne _0223D5E0
	b _0223D750
_0223D5E0:
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	mov r2, #4
	bl MOD12_0223DCE8
	ldr r1, [sp, #0x10]
	ldr r0, _0223D770 ; =0x00000AE8
	ldr r0, [r1, r0]
	ldr r1, _0223D774 ; =0x00002710
	bl _u32_div_f
	ldr r1, [sp, #0x1c]
	cmp r1, #4
	bls _0223D5FE
	b _0223D708
_0223D5FE:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223D60A: ; jump table
	.short _0223D708 - _0223D60A - 2 ; case 0
	.short _0223D614 - _0223D60A - 2 ; case 1
	.short _0223D67E - _0223D60A - 2 ; case 2
	.short _0223D6AC - _0223D60A - 2 ; case 3
	.short _0223D6DA - _0223D60A - 2 ; case 4
_0223D614:
	ldr r2, [sp, #0x10]
	ldr r1, [sp, #0x18]
	add r2, r2, r1
	ldr r1, _0223D778 ; =0x00000AB4
	ldrb r1, [r2, r1]
	cmp r1, #1
	bne _0223D650
	add r1, r4, #0
	add r1, #0x22
	ldrb r1, [r1]
	add r3, r4, #0
	sub r0, r0, #1
	str r1, [sp]
	add r1, r4, #0
	add r1, #0x23
	ldrb r1, [r1]
	add r3, #0x21
	add r2, r6, #0
	str r1, [sp, #4]
	ldr r1, [sp, #0x14]
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	add r0, r4, #0
	ldrb r3, [r3]
	ldr r1, [r5, #0x5c]
	add r0, #0x24
	bl MOD12_0223D77C
	add r7, r0, #0
	b _0223D70C
_0223D650:
	add r1, r4, #0
	add r1, #0x22
	ldrb r1, [r1]
	add r3, r4, #0
	sub r0, r0, #1
	str r1, [sp]
	add r1, r4, #0
	add r1, #0x23
	ldrb r1, [r1]
	add r3, #0x21
	add r2, r6, #0
	str r1, [sp, #4]
	add r1, r7, #0
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	add r0, r4, #0
	ldrb r3, [r3]
	ldr r1, [r5, #0x5c]
	add r0, #0x24
	bl MOD12_0223D890
	add r7, r0, #0
	b _0223D70C
_0223D67E:
	add r1, r4, #0
	add r1, #0x22
	ldrb r1, [r1]
	add r3, r4, #0
	sub r0, r0, #1
	str r1, [sp]
	add r1, r4, #0
	add r1, #0x23
	ldrb r1, [r1]
	add r3, #0x21
	add r2, r6, #0
	str r1, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	add r0, r4, #0
	ldrb r3, [r3]
	ldr r1, [r5, #0x5c]
	add r0, #0x24
	bl MOD12_0223D890
	add r7, r0, #0
	b _0223D70C
_0223D6AC:
	add r1, r4, #0
	add r1, #0x22
	ldrb r1, [r1]
	add r3, r4, #0
	sub r0, r0, #1
	str r1, [sp]
	add r1, r4, #0
	add r1, #0x23
	ldrb r1, [r1]
	add r3, #0x21
	add r2, r6, #0
	str r1, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	add r0, r4, #0
	ldrb r3, [r3]
	ldr r1, [r5, #0x5c]
	add r0, #0x24
	bl MOD12_0223DA10
	add r7, r0, #0
	b _0223D70C
_0223D6DA:
	add r1, r4, #0
	add r1, #0x22
	ldrb r1, [r1]
	add r3, r4, #0
	sub r0, r0, #1
	str r1, [sp]
	add r1, r4, #0
	add r1, #0x23
	ldrb r1, [r1]
	add r3, #0x21
	add r2, r6, #0
	str r1, [sp, #4]
	add r1, r7, #0
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	add r0, r4, #0
	ldrb r3, [r3]
	ldr r1, [r5, #0x5c]
	add r0, #0x24
	bl MOD12_0223DA10
	add r7, r0, #0
	b _0223D70C
_0223D708:
	bl ErrorHandling
_0223D70C:
	cmp r7, #1
	bne _0223D750
	add r0, r4, #0
	add r0, #0x20
	ldrb r1, [r0]
	mov r0, #0
	strb r0, [r4, r1]
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x20
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #0x20
	blo _0223D73A
	add r1, r4, #0
	add r1, #0x20
	mov r0, #0
	strb r0, [r1]
_0223D73A:
	add r0, r4, #0
	add r0, #0x24
	mov r1, #0
	mov r2, #0x28
	bl MI_CpuFill8
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	mov r2, #3
	bl MOD12_0223DCE8
_0223D750:
	ldr r0, [sp, #0x14]
	add r4, #0x4c
	add r0, #0x18
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x18]
	add r6, #0x10
	add r0, r0, #1
	add r5, r5, #4
	str r0, [sp, #0x18]
	cmp r0, #4
	bge _0223D768
	b _0223D5CE
_0223D768:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223D76C: .word 0x00000F3C
_0223D770: .word 0x00000AE8
_0223D774: .word 0x00002710
_0223D778: .word 0x00000AB4

	thumb_func_start MOD12_0223D77C
MOD12_0223D77C: ; 0x0223D77C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0
	str r0, [sp, #4]
	ldrb r0, [r5, #0x10]
	add r4, r2, #0
	add r6, r3, #0
	cmp r0, #0
	beq _0223D796
	cmp r0, #1
	beq _0223D7E4
	b _0223D818
_0223D796:
	ldr r0, [r4, #4]
	ldr r1, [sp, #0x2c]
	lsl r0, r0, #8
	str r0, [r5]
	ldr r0, [r4, #8]
	lsr r1, r1, #1
	lsl r0, r0, #8
	str r0, [r5, #4]
	ldr r0, [r5]
	str r0, [r5, #8]
	ldr r0, [r5, #4]
	str r0, [r5, #0xc]
	mov r0, #5
	lsl r0, r0, #8
	bl _u32_div_f
	ldr r1, [sp, #0x20]
	cmp r1, #1
	bne _0223D7CE
	ldr r1, _0223D888 ; =0xFFFFF600
	strh r1, [r5, #0x14]
	mov r1, #0xc8
	mul r1, r0
	add r0, r1, #0
	mov r1, #0x64
	bl _s32_div_f
	b _0223D7D2
_0223D7CE:
	ldr r1, _0223D88C ; =0xFFFFFB00
	strh r1, [r5, #0x14]
_0223D7D2:
	strh r0, [r5, #0x16]
	ldr r0, [sp, #0x28]
	mov r1, #1
	mov r2, #0
	bl MOD12_0223CD38
	ldrb r0, [r5, #0x10]
	add r0, r0, #1
	strb r0, [r5, #0x10]
_0223D7E4:
	mov r0, #0x14
	ldrsh r1, [r5, r0]
	ldr r2, [r5, #0xc]
	add r1, r2, r1
	str r1, [r5, #0xc]
	ldrsh r1, [r5, r0]
	mov r0, #0x16
	ldrsh r0, [r5, r0]
	add r0, r1, r0
	strh r0, [r5, #0x14]
	ldr r1, [r5, #4]
	ldr r0, [r5, #0xc]
	cmp r0, r1
	blt _0223D81E
	str r1, [r5, #0xc]
	mov r1, #1
	ldr r0, [sp, #0x28]
	add r2, r1, #0
	bl MOD12_0223CD38
	mov r0, #1
	str r0, [sp, #4]
	ldrb r0, [r5, #0x10]
	add r0, r0, #1
	strb r0, [r5, #0x10]
	b _0223D81E
_0223D818:
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0223D81E:
	cmp r6, #0
	bne _0223D826
	mov r6, #0x64
	b _0223D828
_0223D826:
	mov r6, #0x28
_0223D828:
	ldr r0, [sp, #0x24]
	lsl r1, r0, #9
	mov r0, #0x19
	lsl r0, r0, #0xa
	cmp r1, r0
	ble _0223D836
	add r1, r0, #0
_0223D836:
	asr r0, r1, #8
	add r6, r6, r0
	ldr r0, [r5]
	ldr r1, [r5, #8]
	str r0, [sp]
	sub r1, r1, r0
	ldr r7, [r5, #4]
	ldr r0, [r5, #0xc]
	sub r5, r0, r7
	add r0, r1, #0
	mul r0, r6
	mov r1, #0x64
	bl _s32_div_f
	str r0, [sp, #8]
	add r0, r5, #0
	mul r0, r6
	mov r1, #0x64
	bl _s32_div_f
	ldr r2, [sp]
	ldr r1, [sp, #8]
	add r2, r2, r1
	asr r1, r2, #7
	lsr r1, r1, #0x18
	add r1, r2, r1
	asr r1, r1, #8
	str r1, [r4, #4]
	add r1, r7, r0
	asr r0, r1, #7
	lsr r0, r0, #0x18
	add r0, r1, r0
	asr r2, r0, #8
	str r2, [r4, #8]
	ldr r0, [r4]
	ldr r1, [r4, #4]
	bl MOD17_021DD620
	ldr r0, [sp, #4]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223D888: .word 0xFFFFF600
_0223D88C: .word 0xFFFFFB00

	thumb_func_start MOD12_0223D890
MOD12_0223D890: ; 0x0223D890
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0
	str r0, [sp, #0xc]
	ldrb r0, [r4, #0x10]
	add r6, r2, #0
	str r3, [sp]
	ldr r5, [sp, #0x30]
	cmp r0, #0
	beq _0223D8B0
	cmp r0, #1
	beq _0223D908
	cmp r0, #2
	beq _0223D95A
	b _0223D99E
_0223D8B0:
	ldr r0, [r6, #4]
	ldr r1, [sp, #0x34]
	lsl r0, r0, #8
	str r0, [r4]
	ldr r0, [r6, #8]
	lsl r0, r0, #8
	str r0, [r4, #4]
	ldr r0, [r4]
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	str r0, [r4, #0xc]
	mov r0, #0x1e
	mul r0, r1
	mov r1, #0x64
	bl _u32_div_f
	add r7, r0, #0
	mov r0, #1
	lsl r0, r0, #0xc
	add r1, r7, #0
	bl _s32_div_f
	ldr r1, [sp, #0x34]
	str r0, [r4, #0x14]
	mov r0, #1
	lsl r0, r0, #0xc
	sub r1, r1, r7
	bl _s32_div_f
	str r0, [r4, #0x18]
	cmp r5, #0
	bne _0223D902
	ldr r1, [r4, #0x14]
	mov r0, #0
	mvn r0, r0
	add r2, r1, #0
	mul r2, r0
	str r2, [r4, #0x14]
	ldr r1, [r4, #0x18]
	mul r0, r1
	str r0, [r4, #0x18]
_0223D902:
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
_0223D908:
	ldr r0, [sp, #0x28]
	cmp r0, #1
	bne _0223D924
	ldr r1, [r4, #0x14]
	mov r0, #0xc8
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	ldr r1, [r4, #0xc]
	add r0, r1, r0
	str r0, [r4, #0xc]
	mov r0, #0x20
	b _0223D92E
_0223D924:
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x14]
	add r0, r1, r0
	str r0, [r4, #0xc]
	mov r0, #0x10
_0223D92E:
	lsl r0, r0, #8
	str r0, [sp, #8]
	ldr r7, [r4, #4]
	ldr r0, [r4, #0xc]
	sub r0, r0, r7
	bl abs
	ldr r1, [sp, #8]
	cmp r0, r1
	blt _0223D9A4
	cmp r5, #1
	bne _0223D94C
	add r0, r1, #0
	add r0, r7, r0
	b _0223D950
_0223D94C:
	add r0, r1, #0
	sub r0, r7, r0
_0223D950:
	str r0, [r4, #0xc]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	b _0223D9A4
_0223D95A:
	ldr r0, [sp, #0x28]
	cmp r0, #1
	bne _0223D970
	ldr r1, [r4, #0x18]
	mov r0, #0xc8
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	ldr r1, [r4, #0xc]
	b _0223D974
_0223D970:
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x18]
_0223D974:
	sub r0, r1, r0
	str r0, [r4, #0xc]
	cmp r5, #1
	bne _0223D984
	ldr r1, [r4, #4]
	ldr r0, [r4, #0xc]
	cmp r0, r1
	ble _0223D990
_0223D984:
	cmp r5, #0
	bne _0223D9A4
	ldr r1, [r4, #4]
	ldr r0, [r4, #0xc]
	cmp r0, r1
	blt _0223D9A4
_0223D990:
	str r1, [r4, #0xc]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	mov r0, #1
	str r0, [sp, #0xc]
	b _0223D9A4
_0223D99E:
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0223D9A4:
	ldr r0, [sp]
	cmp r0, #0
	bne _0223D9AE
	mov r5, #0x64
	b _0223D9B0
_0223D9AE:
	mov r5, #0x28
_0223D9B0:
	ldr r0, [sp, #0x2c]
	lsl r1, r0, #9
	mov r0, #0x19
	lsl r0, r0, #0xa
	cmp r1, r0
	ble _0223D9BE
	add r1, r0, #0
_0223D9BE:
	asr r0, r1, #8
	add r5, r5, r0
	ldr r0, [r4]
	ldr r1, [r4, #8]
	str r0, [sp, #4]
	sub r1, r1, r0
	ldr r7, [r4, #4]
	ldr r0, [r4, #0xc]
	sub r4, r0, r7
	add r0, r1, #0
	mul r0, r5
	mov r1, #0x64
	bl _s32_div_f
	str r0, [sp, #0x10]
	add r0, r4, #0
	mul r0, r5
	mov r1, #0x64
	bl _s32_div_f
	ldr r2, [sp, #4]
	ldr r1, [sp, #0x10]
	add r2, r2, r1
	asr r1, r2, #7
	lsr r1, r1, #0x18
	add r1, r2, r1
	asr r1, r1, #8
	str r1, [r6, #4]
	add r1, r7, r0
	asr r0, r1, #7
	lsr r0, r0, #0x18
	add r0, r1, r0
	asr r2, r0, #8
	str r2, [r6, #8]
	ldr r0, [r6]
	ldr r1, [r6, #4]
	bl MOD17_021DD620
	ldr r0, [sp, #0xc]
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD12_0223DA10
MOD12_0223DA10: ; 0x0223DA10
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	mov r0, #0
	str r0, [sp, #0x10]
	ldrb r0, [r5, #0x10]
	add r4, r2, #0
	str r3, [sp]
	ldr r6, [sp, #0x38]
	cmp r0, #0
	beq _0223DA30
	cmp r0, #1
	beq _0223DAB0
	cmp r0, #2
	beq _0223DB22
	b _0223DB84
_0223DA30:
	ldr r0, [r4, #4]
	ldr r1, [sp, #0x3c]
	lsl r0, r0, #8
	str r0, [r5]
	ldr r0, [r4, #8]
	lsl r0, r0, #8
	str r0, [r5, #4]
	ldr r0, [r5]
	str r0, [r5, #8]
	ldr r0, [r5, #4]
	str r0, [r5, #0xc]
	mov r0, #0x1e
	mul r0, r1
	mov r1, #0x64
	bl _u32_div_f
	ldr r1, [sp, #0x3c]
	str r0, [sp, #0x14]
	sub r7, r1, r0
	ldr r0, _0223DC04 ; =0x00038E00
	ldr r1, [sp, #0x14]
	bl _s32_div_f
	str r0, [r5, #0x18]
	ldr r0, _0223DC08 ; =0xFFFC7200
	add r1, r7, #0
	bl _s32_div_f
	str r0, [r5, #0x1c]
	mov r0, #1
	ldr r1, [sp, #0x14]
	lsl r0, r0, #0xc
	bl _s32_div_f
	str r0, [r5, #0x20]
	mov r0, #1
	lsl r0, r0, #0xc
	add r1, r7, #0
	bl _s32_div_f
	neg r0, r0
	str r0, [r5, #0x24]
	cmp r6, #1
	bne _0223DAAA
	ldr r1, [r5, #0x18]
	mov r0, #0
	mvn r0, r0
	add r2, r1, #0
	mul r2, r0
	str r2, [r5, #0x18]
	ldr r1, [r5, #0x1c]
	add r2, r1, #0
	mul r2, r0
	str r2, [r5, #0x1c]
	ldr r1, [r5, #0x20]
	add r2, r1, #0
	mul r2, r0
	str r2, [r5, #0x20]
	ldr r1, [r5, #0x24]
	mul r0, r1
	str r0, [r5, #0x24]
_0223DAAA:
	ldrb r0, [r5, #0x10]
	add r0, r0, #1
	strb r0, [r5, #0x10]
_0223DAB0:
	ldr r0, [sp, #0x30]
	cmp r0, #1
	bne _0223DADC
	ldr r1, [r5, #0x20]
	mov r0, #0xc8
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	ldr r1, [r5, #8]
	add r0, r1, r0
	str r0, [r5, #8]
	mov r0, #0x20
	str r0, [sp, #0xc]
	ldr r1, [r5, #0x18]
	mov r0, #0xc8
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	ldr r1, [r5, #0x14]
	b _0223DAEC
_0223DADC:
	ldr r1, [r5, #8]
	ldr r0, [r5, #0x20]
	add r0, r1, r0
	str r0, [r5, #8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldr r1, [r5, #0x14]
	ldr r0, [r5, #0x18]
_0223DAEC:
	add r0, r1, r0
	str r0, [r5, #0x14]
	ldr r0, [sp, #0xc]
	ldr r7, [r5]
	lsl r0, r0, #8
	str r0, [sp, #8]
	ldr r0, [r5, #8]
	sub r0, r0, r7
	bl abs
	ldr r1, [sp, #8]
	cmp r0, r1
	blt _0223DB8A
	cmp r6, #1
	bne _0223DB10
	add r0, r1, #0
	sub r0, r7, r0
	b _0223DB14
_0223DB10:
	add r0, r1, #0
	add r0, r7, r0
_0223DB14:
	str r0, [r5, #8]
	ldr r0, [r5, #4]
	str r0, [r5, #0xc]
	ldrb r0, [r5, #0x10]
	add r0, r0, #1
	strb r0, [r5, #0x10]
	b _0223DB8A
_0223DB22:
	ldr r0, [sp, #0x30]
	cmp r0, #1
	bne _0223DB4A
	ldr r1, [r5, #0x24]
	mov r0, #0xc8
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	ldr r1, [r5, #8]
	add r0, r1, r0
	str r0, [r5, #8]
	ldr r1, [r5, #0x1c]
	mov r0, #0xc8
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	ldr r1, [r5, #0x14]
	b _0223DB56
_0223DB4A:
	ldr r1, [r5, #8]
	ldr r0, [r5, #0x24]
	add r0, r1, r0
	str r0, [r5, #8]
	ldr r1, [r5, #0x14]
	ldr r0, [r5, #0x1c]
_0223DB56:
	add r0, r1, r0
	str r0, [r5, #0x14]
	cmp r6, #1
	bne _0223DB66
	ldr r1, [r5]
	ldr r0, [r5, #8]
	cmp r0, r1
	bge _0223DB72
_0223DB66:
	cmp r6, #0
	bne _0223DB8A
	ldr r1, [r5]
	ldr r0, [r5, #8]
	cmp r0, r1
	bgt _0223DB8A
_0223DB72:
	str r1, [r5, #8]
	mov r0, #0
	str r0, [r5, #0x14]
	ldrb r0, [r5, #0x10]
	add r0, r0, #1
	strb r0, [r5, #0x10]
	mov r0, #1
	str r0, [sp, #0x10]
	b _0223DB8A
_0223DB84:
	add sp, #0x1c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0223DB8A:
	ldr r1, [r5, #0x14]
	ldr r0, [r4]
	lsl r1, r1, #8
	lsr r1, r1, #0x10
	bl MOD17_021DD604
	ldr r0, [sp]
	cmp r0, #0
	bne _0223DBA0
	mov r6, #0x64
	b _0223DBA2
_0223DBA0:
	mov r6, #0x28
_0223DBA2:
	ldr r0, [sp, #0x34]
	lsl r1, r0, #9
	mov r0, #0x19
	lsl r0, r0, #0xa
	cmp r1, r0
	ble _0223DBB0
	add r1, r0, #0
_0223DBB0:
	asr r0, r1, #8
	add r6, r6, r0
	ldr r0, [r5]
	ldr r1, [r5, #8]
	str r0, [sp, #4]
	sub r1, r1, r0
	ldr r7, [r5, #4]
	ldr r0, [r5, #0xc]
	sub r5, r0, r7
	add r0, r1, #0
	mul r0, r6
	mov r1, #0x64
	bl _s32_div_f
	str r0, [sp, #0x18]
	add r0, r5, #0
	mul r0, r6
	mov r1, #0x64
	bl _s32_div_f
	ldr r2, [sp, #4]
	ldr r1, [sp, #0x18]
	add r2, r2, r1
	asr r1, r2, #7
	lsr r1, r1, #0x18
	add r1, r2, r1
	asr r1, r1, #8
	str r1, [r4, #4]
	add r1, r7, r0
	asr r0, r1, #7
	lsr r0, r0, #0x18
	add r0, r1, r0
	asr r2, r0, #8
	str r2, [r4, #8]
	ldr r0, [r4]
	ldr r1, [r4, #4]
	bl MOD17_021DD620
	ldr r0, [sp, #0x10]
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_0223DC04: .word 0x00038E00
_0223DC08: .word 0xFFFC7200

	thumb_func_start MOD12_0223DC0C
MOD12_0223DC0C: ; 0x0223DC0C
	ldr r1, _0223DC24 ; =0x00001BA0
	mov r2, #0
	add r3, r0, r1
	mov r0, #4
_0223DC14:
	ldrb r1, [r3]
	add r2, r2, #1
	bic r1, r0
	strb r1, [r3]
	add r3, #0xa
	cmp r2, #8
	blt _0223DC14
	bx lr
	.align 2, 0
_0223DC24: .word 0x00001BA0

	thumb_func_start MOD12_0223DC28
MOD12_0223DC28: ; 0x0223DC28
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _0223DCAC ; =0x00001070
	add r6, r1, #0
	add r7, r5, r0
	mov r0, #0x28
	mul r0, r6
	str r0, [sp, #4]
	ldr r0, [r7, r0]
	str r2, [sp]
	cmp r0, #0
	beq _0223DC46
	bl ErrorHandling
_0223DC46:
	ldr r0, _0223DCB0 ; =0x0000106C
	mov r2, #0x28
	add r4, r6, #0
	add r0, r5, r0
	mul r4, r2
	str r0, [sp, #8]
	add r0, r0, r4
	mov r1, #0
	bl MI_CpuFill8
	ldr r0, [sp, #8]
	ldr r2, _0223DCB4 ; =0x00001086
	str r5, [r0, r4]
	add r3, r5, r4
	ldr r0, [sp]
	strb r6, [r3, r2]
	sub r1, r2, #1
	strb r0, [r3, r1]
	lsl r0, r6, #2
	add r0, r5, r0
	add r1, r2, #0
	ldr r0, [r0, #0x5c]
	sub r1, #0x12
	str r0, [r3, r1]
	add r0, r5, #0
	add r0, #0x18
	lsl r1, r6, #4
	add r1, r0, r1
	add r0, r2, #0
	sub r0, #0xe
	str r1, [r3, r0]
	add r2, #0xa
	add r0, r5, r2
	ldrb r2, [r0, r4]
	mov r1, #4
	orr r1, r2
	strb r1, [r0, r4]
	ldrb r2, [r0, r4]
	mov r1, #8
	orr r1, r2
	strb r1, [r0, r4]
	ldr r1, [sp, #8]
	ldr r0, _0223DCB8 ; =MOD12_0223DE10
	ldr r2, _0223DCBC ; =0x00009858
	add r1, r1, r4
	bl FUN_0200CA44
	ldr r1, [sp, #4]
	str r0, [r7, r1]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223DCAC: .word 0x00001070
_0223DCB0: .word 0x0000106C
_0223DCB4: .word 0x00001086
_0223DCB8: .word MOD12_0223DE10
_0223DCBC: .word 0x00009858

	thumb_func_start MOD12_0223DCC0
MOD12_0223DCC0: ; 0x0223DCC0
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	ldr r7, _0223DCE4 ; =0x00001070
	add r5, r0, #0
	add r6, r4, #0
_0223DCCA:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _0223DCD8
	bl FUN_0200CAB4
	ldr r0, _0223DCE4 ; =0x00001070
	str r6, [r5, r0]
_0223DCD8:
	add r4, r4, #1
	add r5, #0x28
	cmp r4, #4
	blt _0223DCCA
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223DCE4: .word 0x00001070

	thumb_func_start MOD12_0223DCE8
MOD12_0223DCE8: ; 0x0223DCE8
	push {r3, r4, r5, lr}
	mov r3, #0x28
	mul r3, r1
	ldr r1, _0223DDAC ; =0x00001070
	add r4, r0, r3
	ldr r5, [r4, r1]
	cmp r5, #0
	beq _0223DDA8
	cmp r2, #5
	bhi _0223DDA4
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0223DD08: ; jump table
	.short _0223DD14 - _0223DD08 - 2 ; case 0
	.short _0223DD2A - _0223DD08 - 2 ; case 1
	.short _0223DD38 - _0223DD08 - 2 ; case 2
	.short _0223DD46 - _0223DD08 - 2 ; case 3
	.short _0223DD64 - _0223DD08 - 2 ; case 4
	.short _0223DD92 - _0223DD08 - 2 ; case 5
_0223DD14:
	add r1, #0x20
	add r2, r0, r1
	ldrb r1, [r2, r3]
	mov r0, #0x20
	bic r1, r0
	strb r1, [r2, r3]
	ldrb r1, [r2, r3]
	mov r0, #0x10
	bic r1, r0
	strb r1, [r2, r3]
	pop {r3, r4, r5, pc}
_0223DD2A:
	add r1, #0x20
	add r2, r0, r1
	ldrb r1, [r2, r3]
	mov r0, #0x20
	orr r0, r1
	strb r0, [r2, r3]
	pop {r3, r4, r5, pc}
_0223DD38:
	add r1, #0x20
	add r2, r0, r1
	ldrb r1, [r2, r3]
	mov r0, #0x10
	orr r0, r1
	strb r0, [r2, r3]
	pop {r3, r4, r5, pc}
_0223DD46:
	add r1, #0x20
	add r0, r0, r1
	ldrb r2, [r0, r3]
	mov r1, #2
	bic r2, r1
	strb r2, [r0, r3]
	ldrb r2, [r0, r3]
	mov r1, #1
	bic r2, r1
	strb r2, [r0, r3]
	ldrb r2, [r0, r3]
	mov r1, #4
	orr r1, r2
	strb r1, [r0, r3]
	pop {r3, r4, r5, pc}
_0223DD64:
	add r2, r1, #0
	add r2, #0x20
	ldrb r2, [r4, r2]
	lsl r2, r2, #0x1e
	lsr r2, r2, #0x1f
	bne _0223DDA8
	add r2, r1, #0
	add r2, #0x20
	add r5, r0, r2
	ldrb r2, [r5, r3]
	mov r0, #2
	orr r0, r2
	strb r0, [r5, r3]
	ldrb r0, [r5, r3]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	bne _0223DDA8
	add r0, r1, #0
	add r0, #0x10
	ldr r0, [r4, r0]
	add r1, #0x1c
	str r0, [r4, r1]
	pop {r3, r4, r5, pc}
_0223DD92:
	add r1, #0x20
	add r2, r0, r1
	ldrb r1, [r2, r3]
	mov r0, #1
	bic r1, r0
	mov r0, #1
	orr r0, r1
	strb r0, [r2, r3]
	pop {r3, r4, r5, pc}
_0223DDA4:
	bl ErrorHandling
_0223DDA8:
	pop {r3, r4, r5, pc}
	nop
_0223DDAC: .word 0x00001070

	thumb_func_start MOD12_0223DDB0
MOD12_0223DDB0: ; 0x0223DDB0
	mov r2, #0x28
	mul r2, r1
	ldr r1, _0223DDE0 ; =0x00001070
	add r2, r0, r2
	ldr r0, [r2, r1]
	cmp r0, #0
	bne _0223DDC2
	mov r0, #1
	bx lr
_0223DDC2:
	add r0, r1, #0
	add r0, #0x20
	ldrb r0, [r2, r0]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1f
	cmp r0, #1
	beq _0223DDD8
	add r1, #0x15
	ldrb r0, [r2, r1]
	cmp r0, #0
	bne _0223DDDC
_0223DDD8:
	mov r0, #1
	bx lr
_0223DDDC:
	mov r0, #0
	bx lr
	.align 2, 0
_0223DDE0: .word 0x00001070

	thumb_func_start MOD12_0223DDE4
MOD12_0223DDE4: ; 0x0223DDE4
	mov r2, #0x28
	mul r2, r1
	add r2, r0, r2
	ldr r0, _0223DE0C ; =0x00001070
	ldr r1, [r2, r0]
	cmp r1, #0
	bne _0223DDF6
	mov r0, #1
	bx lr
_0223DDF6:
	add r0, #0x20
	ldrb r0, [r2, r0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _0223DE06
	mov r0, #1
	bx lr
_0223DE06:
	mov r0, #0
	bx lr
	nop
_0223DE0C: .word 0x00001070

	thumb_func_start MOD12_0223DE10
MOD12_0223DE10: ; 0x0223DE10
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD12_0223DE24
	add r0, r4, #0
	bl MOD12_0223DF18
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_0223DE24
MOD12_0223DE24: ; 0x0223DE24
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r0, #0x24
	ldrb r0, [r0]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1f
	cmp r0, #1
	beq _0223DF00
	ldrb r0, [r4, #0x19]
	cmp r0, #0
	beq _0223DF00
	ldr r5, [r4]
	ldr r1, _0223DF04 ; =0x00001138
	ldr r2, _0223DF08 ; =0x00002710
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r3, #0
	bl _ll_mul
	ldr r2, _0223DF0C ; =0x00000AE8
	mov r3, #0
	ldr r7, [r5, r2]
	add r2, r7, #0
	bl _ull_mod
	add r5, r0, #0
	add r6, r1, #0
	lsr r7, r7, #1
	lsr r0, r5, #0x13
	lsl r1, r6, #0xd
	orr r1, r0
	lsl r0, r5, #0xd
	add r2, r7, #0
	mov r3, #0
	bl _ll_udiv
	add r2, r1, #0
	mov r1, #1
	sub r3, r5, r7
	ldr r3, _0223DF10 ; =0x00000000
	sbc r6, r3
	blo _0223DE80
	lsl r3, r1, #0xe
	mov r1, #0
	sub r0, r3, r0
_0223DE80:
	add r2, r4, #0
	add r2, #0x24
	ldrb r2, [r2]
	ldr r3, _0223DF14 ; =0xFFFD8000
	mov r5, #0x40
	add r0, r0, r3
	str r0, [r4, #0x10]
	add r0, r4, #0
	add r0, #0x24
	ldrb r0, [r0]
	lsl r2, r2, #0x19
	lsr r2, r2, #0x1f
	bic r0, r5
	lsl r5, r1, #0x18
	lsr r5, r5, #0x18
	lsl r5, r5, #0x1f
	lsr r5, r5, #0x19
	orr r5, r0
	add r0, r4, #0
	add r0, #0x24
	strb r5, [r0]
	add r0, r4, #0
	add r0, #0x24
	ldrb r0, [r0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _0223DEEA
	ldr r0, [r4, #0x10]
	cmp r0, r3
	beq _0223DEC6
	cmp r2, #0
	bne _0223DEEA
	cmp r1, #1
	bne _0223DEEA
_0223DEC6:
	ldr r0, _0223DF14 ; =0xFFFD8000
	str r0, [r4, #0x10]
	add r0, r4, #0
	add r0, #0x24
	ldrb r1, [r0]
	mov r0, #0x10
	bic r1, r0
	add r0, r4, #0
	add r0, #0x24
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x24
	ldrb r1, [r0]
	mov r0, #0x20
	orr r1, r0
	add r0, r4, #0
	add r0, #0x24
	strb r1, [r0]
_0223DEEA:
	ldr r1, [r4, #0x10]
	asr r0, r1, #7
	lsr r0, r0, #0x18
	add r0, r1, r0
	asr r1, r0, #8
	ldr r0, [r4, #0xc]
	str r1, [r0, #0xc]
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	bl MOD12_0223D09C
_0223DF00:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223DF04: .word 0x00001138
_0223DF08: .word 0x00002710
_0223DF0C: .word 0x00000AE8
_0223DF10: .word 0x00000000
_0223DF14: .word 0xFFFD8000

	thumb_func_start MOD12_0223DF18
MOD12_0223DF18: ; 0x0223DF18
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldr r2, [r4]
	ldr r1, _0223E058 ; =0x00001138
	mov r3, #0
	ldr r0, [r2, r1]
	add r1, r1, #4
	ldr r1, [r2, r1]
	ldr r2, _0223E05C ; =0x00002710
	ldr r5, [r4, #0x14]
	bl _ll_mul
	ldr r3, [r4]
	ldr r2, _0223E060 ; =0x00000AE8
	ldr r2, [r3, r2]
	mov r3, #0
	lsl r2, r2, #1
	bl _ull_mod
	mov r2, #0x5a
	lsl r2, r2, #2
	mov r3, #0
	bl _ll_mul
	ldr r3, [r4]
	ldr r2, _0223E060 ; =0x00000AE8
	ldr r2, [r3, r2]
	mov r3, #0
	lsl r2, r2, #1
	bl _ll_udiv
	lsr r2, r0, #0x18
	lsl r1, r1, #8
	orr r1, r2
	lsl r0, r0, #8
	add r2, r4, #0
	str r0, [r4, #0x14]
	add r2, #0x24
	ldrb r2, [r2]
	lsl r3, r2, #0x1e
	lsr r3, r3, #0x1f
	bne _0223E054
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x1f
	cmp r2, #1
	bne _0223DF86
	add r2, r4, #0
	add r2, #0x24
	ldrb r2, [r2]
	mov r3, #8
	add r5, r0, #0
	bic r2, r3
	add r3, r4, #0
	add r3, #0x24
	strb r2, [r3]
_0223DF86:
	add r2, r4, #0
	add r2, #0x24
	ldrb r2, [r2]
	lsl r2, r2, #0x1d
	lsr r2, r2, #0x1f
	cmp r2, #1
	bne _0223DFCE
	mov r2, #0
	sub r3, r0, r5
	mov ip, r1
	mov r3, ip
	sbc r3, r2
	bhs _0223DFA4
	add r7, r5, r0
	b _0223DFA6
_0223DFA4:
	add r7, r0, #0
_0223DFA6:
	ldr r6, [r4, #0x20]
	mov r2, #0
	add r3, r2, #0
	add r2, r6, #0
	eor r3, r1
	eor r2, r0
	orr r2, r3
	beq _0223DFBE
	cmp r5, r6
	bhi _0223E054
	cmp r6, r7
	bhi _0223E054
_0223DFBE:
	add r2, r4, #0
	add r2, #0x24
	ldrb r3, [r2]
	mov r2, #4
	bic r3, r2
	add r2, r4, #0
	add r2, #0x24
	strb r3, [r2]
_0223DFCE:
	add r2, r4, #0
	add r2, #0x24
	ldrb r2, [r2]
	lsl r2, r2, #0x1f
	lsr r2, r2, #0x1f
	cmp r2, #1
	bne _0223E014
	mov r3, #0
	mov r2, #0
	eor r3, r1
	eor r2, r0
	orr r2, r3
	beq _0223DFF0
	mov r2, #0
	sub r0, r0, r5
	sbc r1, r2
	bhs _0223E014
_0223DFF0:
	add r1, r4, #0
	add r1, #0x24
	ldrb r2, [r1]
	mov r1, #1
	mov r0, #0
	bic r2, r1
	add r1, r4, #0
	add r1, #0x24
	strb r2, [r1]
	add r1, r4, #0
	add r1, #0x24
	ldrb r2, [r1]
	mov r1, #2
	orr r2, r1
	add r1, r4, #0
	add r1, #0x24
	strb r2, [r1]
	str r0, [r4, #0x20]
_0223E014:
	ldrb r0, [r4, #0x19]
	cmp r0, #0
	bne _0223E01C
	b _0223E01C
_0223E01C:
	ldr r0, [r4, #0x14]
	mov r5, #3
	lsl r0, r0, #8
	lsr r0, r0, #0x10
	bl Cos
	add r1, r5, #0
	mul r1, r0
	ldrb r2, [r4, #0x19]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	mov r1, #6
	add r3, r2, #0
	mul r3, r1
	ldr r1, _0223E064 ; =MOD12_022461F4
	asr r0, r0, #0xc
	ldrsh r1, [r1, r3]
	add r0, r0, r1
	sub r1, r0, r5
	ldr r0, [r4, #0xc]
	str r1, [r0, #4]
	ldr r2, [r4, #0xc]
	ldr r0, [r2]
	ldr r1, [r2, #4]
	ldr r2, [r2, #8]
	bl MOD17_021DD620
_0223E054:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223E058: .word 0x00001138
_0223E05C: .word 0x00002710
_0223E060: .word 0x00000AE8
_0223E064: .word MOD12_022461F4

	thumb_func_start MOD12_0223E068
MOD12_0223E068: ; 0x0223E068
	push {r4, r5, r6, lr}
	sub sp, #8
	add r6, r1, #0
	add r4, r0, #0
	add r5, r2, #0
	cmp r6, #0
	beq _0223E07E
	cmp r5, #0
	bne _0223E07E
	bl ErrorHandling
_0223E07E:
	cmp r6, #6
	bls _0223E084
	b _0223E1E4
_0223E084:
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223E090: ; jump table
	.short _0223E1E8 - _0223E090 - 2 ; case 0
	.short _0223E09E - _0223E090 - 2 ; case 1
	.short _0223E0BA - _0223E090 - 2 ; case 2
	.short _0223E0DE - _0223E090 - 2 ; case 3
	.short _0223E0F4 - _0223E090 - 2 ; case 4
	.short _0223E138 - _0223E090 - 2 ; case 5
	.short _0223E16A - _0223E090 - 2 ; case 6
_0223E09E:
	ldrb r0, [r5]
	ldr r1, [r4, #0x14]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r4, #0x9c
	add r2, r0, #0
	ldr r0, [r4]
	mov r1, #0
	bl BufferBoxMonNickname
	add sp, #8
	pop {r4, r5, r6, pc}
_0223E0BA:
	mov r2, #0x12
	lsl r2, r2, #4
	ldr r3, [r4]
	add r1, r2, #1
	ldrb r0, [r3, r2]
	add r2, #0x51
	ldrb r1, [r3, r1]
	ldrb r2, [r3, r2]
	bl FUN_02083228
	add r4, #0x9c
	add r2, r0, #0
	ldr r0, [r4]
	mov r1, #0
	bl BufferContestMessage
	add sp, #8
	pop {r4, r5, r6, pc}
_0223E0DE:
	mov r1, #0
	str r1, [sp]
	mov r3, #1
	str r3, [sp, #4]
	add r4, #0x9c
	ldrb r2, [r5, #4]
	ldr r0, [r4]
	bl BufferIntegerAsString
	add sp, #8
	pop {r4, r5, r6, pc}
_0223E0F4:
	ldrb r6, [r5]
	ldr r3, [r4]
	mov r0, #1
	lsl r2, r6, #2
	str r0, [sp]
	mov r0, #2
	add r2, r3, r2
	add r6, r3, r6
	mov r3, #0x42
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r3, r3, #2
	add r0, #0x9c
	add r2, #0xe8
	ldrb r3, [r6, r3]
	ldr r0, [r0]
	ldr r2, [r2]
	mov r1, #0
	bl BufferString
	ldrb r0, [r5]
	ldr r1, [r4, #0x14]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r4, #0x9c
	add r2, r0, #0
	ldr r0, [r4]
	mov r1, #1
	bl BufferBoxMonNickname
	add sp, #8
	pop {r4, r5, r6, pc}
_0223E138:
	ldrb r0, [r5]
	ldr r1, [r4, #0x14]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0x9c
	ldr r0, [r0]
	mov r1, #0
	bl BufferBoxMonNickname
	mov r0, #0
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	add r4, #0x9c
	ldrb r2, [r5, #4]
	ldr r0, [r4]
	add r3, r1, #0
	bl BufferIntegerAsString
	add sp, #8
	pop {r4, r5, r6, pc}
_0223E16A:
	mov r2, #0x12
	lsl r2, r2, #4
	ldr r3, [r4]
	add r1, r2, #1
	ldrb r0, [r3, r2]
	add r2, #0x51
	ldrb r1, [r3, r1]
	ldrb r2, [r3, r2]
	bl FUN_02083228
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0x9c
	ldr r0, [r0]
	mov r1, #0
	bl BufferContestMessage
	mov r0, #0
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	add r0, r4, #0
	add r0, #0x9c
	ldrb r2, [r5, #4]
	ldr r0, [r0]
	add r3, r1, #0
	bl BufferIntegerAsString
	ldrb r6, [r5]
	ldr r3, [r4]
	mov r0, #1
	lsl r2, r6, #2
	str r0, [sp]
	mov r1, #2
	add r2, r3, r2
	add r6, r3, r6
	mov r3, #0x42
	add r0, r4, #0
	str r1, [sp, #4]
	lsl r3, r3, #2
	add r0, #0x9c
	add r2, #0xe8
	ldrb r3, [r6, r3]
	ldr r0, [r0]
	ldr r2, [r2]
	bl BufferString
	ldrb r0, [r5]
	ldr r1, [r4, #0x14]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r4, #0x9c
	add r2, r0, #0
	ldr r0, [r4]
	mov r1, #3
	bl BufferBoxMonNickname
	add sp, #8
	pop {r4, r5, r6, pc}
_0223E1E4:
	bl ErrorHandling
_0223E1E8:
	add sp, #8
	pop {r4, r5, r6, pc}

	thumb_func_start MOD12_0223E1EC
MOD12_0223E1EC: ; 0x0223E1EC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r6, r1, #0
	ldr r1, [r5]
	ldr r0, _0223E268 ; =0x00000171
	add r7, r2, #0
	ldrb r0, [r1, r0]
	str r3, [sp, #0xc]
	cmp r0, #0
	bne _0223E20E
	ldr r0, _0223E26C ; =0x00001988
	ldr r0, [r1, r0]
	bl Options_GetTextFrameDelay
	add r4, r0, #0
	b _0223E210
_0223E20E:
	mov r4, #1
_0223E210:
	add r0, r6, #0
	add r1, r7, #0
	bl NewString_ReadMsgData
	add r6, r0, #0
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x28]
	add r0, r5, #0
	bl MOD12_0223E068
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0x9c
	add r1, #0xa0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	add r0, #0x78
	mov r1, #0xff
	bl FillWindowPixelBuffer
	mov r3, #0
	str r3, [sp]
	str r4, [sp, #4]
	add r2, r5, #0
	add r0, r5, #0
	str r3, [sp, #8]
	add r2, #0xa0
	ldr r2, [r2]
	add r0, #0x78
	mov r1, #1
	bl AddTextPrinterParameterized
	ldr r1, _0223E270 ; =0x00000AB8
	strb r0, [r5, r1]
	add r0, r6, #0
	bl String_dtor
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223E268: .word 0x00000171
_0223E26C: .word 0x00001988
_0223E270: .word 0x00000AB8

	thumb_func_start MOD12_0223E274
MOD12_0223E274: ; 0x0223E274
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	cmp r4, #8
	blo _0223E286
	bl ErrorHandling
_0223E286:
	lsl r3, r4, #2
	ldr r2, _0223E2A0 ; =MOD12_02246224
	add r0, r5, #0
	ldr r4, _0223E2A4 ; =MOD12_02246224 + 2
	ldrh r2, [r2, r3]
	str r6, [sp]
	add r5, #0x98
	ldrb r3, [r4, r3]
	ldr r1, [r5]
	bl MOD12_0223E1EC
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0223E2A0: .word MOD12_02246224
_0223E2A4: .word MOD12_02246224 + 2

	thumb_func_start MOD12_0223E2A8
MOD12_0223E2A8: ; 0x0223E2A8
	ldr r1, _0223E2B0 ; =0x00000AB8
	ldr r3, _0223E2B4 ; =FUN_0201BD70
	ldrb r0, [r0, r1]
	bx r3
	.align 2, 0
_0223E2B0: .word 0x00000AB8
_0223E2B4: .word FUN_0201BD70

	thumb_func_start MOD12_0223E2B8
MOD12_0223E2B8: ; 0x0223E2B8
	push {r4, r5, lr}
	sub sp, #0xc
	mov r2, #1
	str r2, [sp]
	str r2, [sp, #4]
	ldr r2, _0223E300 ; =0x000080F1
	mov r3, #0x4c
	str r2, [sp, #8]
	mov r2, #0x2e
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223E304 ; =0x000080EE
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x4d
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0223E304 ; =0x000080EE
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x2e
	mov r3, #0x4e
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0223E300: .word 0x000080F1
_0223E304: .word 0x000080EE

	thumb_func_start MOD12_0223E308
MOD12_0223E308: ; 0x0223E308
	push {r4, lr}
	ldr r1, _0223E324 ; =0x000080F1
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _0223E328 ; =0x000080EE
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _0223E328 ; =0x000080EE
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_0223E324: .word 0x000080F1
_0223E328: .word 0x000080EE

	thumb_func_start MOD12_0223E32C
MOD12_0223E32C: ; 0x0223E32C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _0223E33E
	bl ErrorHandling
_0223E33E:
	mov r0, #0x17
	mov r1, #0x10
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x10
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0x21
	lsl r0, r0, #4
	str r4, [r5, r0]
	str r5, [r4, #8]
	ldr r0, [r5, #0x6c]
	ldr r1, [r5, #0x70]
	ldr r2, _0223E380 ; =MOD12_02246278
	bl FUN_0200C154
	str r0, [r4, #4]
	ldr r0, [r0]
	bl FUN_0200C59C
	ldr r0, [r4, #4]
	mov r1, #0
	bl FUN_0200C644
	ldr r0, _0223E384 ; =MOD12_0223E3BC
	ldr r2, _0223E388 ; =0x00009C4F
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4]
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223E380: .word MOD12_02246278
_0223E384: .word MOD12_0223E3BC
_0223E388: .word 0x00009C4F

	thumb_func_start MOD12_0223E38C
MOD12_0223E38C: ; 0x0223E38C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	ldr r0, [r0]
	bl FUN_0200CAB4
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	ldr r0, [r0, #4]
	bl FUN_0200C3DC
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0x21
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	pop {r4, pc}

	thumb_func_start MOD12_0223E3BC
MOD12_0223E3BC: ; 0x0223E3BC
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	beq _0223E3CA
	cmp r0, #1
	beq _0223E3CE
	cmp r0, #2
	b _0223E3CE
_0223E3CA:
	add r0, r0, #1
	strb r0, [r1, #0xc]
_0223E3CE:
	ldr r0, [r1, #4]
	ldr r3, _0223E3D8 ; =FUN_0200C59C
	ldr r0, [r0]
	bx r3
	nop
_0223E3D8: .word FUN_0200C59C

	thumb_func_start MOD12_0223E3DC
MOD12_0223E3DC: ; 0x0223E3DC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	lsl r0, r1, #8
	add r1, r2, #0
	bl _u32_div_f
	ldr r1, _0223E434 ; =0x00002710
	add r4, r0, #0
	mul r0, r1
	lsl r1, r1, #4
	mov r6, #0x90
	bl _u32_div_f
	mov r0, #0xb4
	mul r0, r1
	ldr r1, _0223E438 ; =0x00027100
	bl _u32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl Sin
	mov r1, #0xa
	mul r1, r0
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	sub r2, r6, r0
	lsl r1, r4, #0x10
	lsl r2, r2, #0x10
	mov r3, #1
	ldr r0, [r5, #4]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	lsl r3, r3, #0x14
	bl FUN_0200C750
	ldr r0, [r5, #4]
	mov r1, #1
	bl FUN_0200C644
	pop {r4, r5, r6, pc}
	nop
_0223E434: .word 0x00002710
_0223E438: .word 0x00027100

	thumb_func_start MOD12_0223E43C
MOD12_0223E43C: ; 0x0223E43C
	ldr r3, _0223E444 ; =FUN_0200C644
	ldr r0, [r0, #4]
	mov r1, #0
	bx r3
	.align 2, 0
_0223E444: .word FUN_0200C644

	thumb_func_start MOD12_0223E448
MOD12_0223E448: ; 0x0223E448
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_0200C644
	mov r3, #1
	ldr r0, [r4, #4]
	mov r1, #0
	mov r2, #0x90
	lsl r3, r3, #0x14
	bl FUN_0200C750
	pop {r4, pc}

	thumb_func_start MOD12_0223E464
MOD12_0223E464: ; 0x0223E464
	push {r3, r4}
	ldr r2, _0223E484 ; =MOD12_022461E0
	add r1, sp, #0
	ldrb r3, [r2]
	add r4, sp, #0
	strb r3, [r1]
	ldrb r3, [r2, #1]
	strb r3, [r1, #1]
	ldrb r3, [r2, #2]
	ldrb r2, [r2, #3]
	strb r3, [r1, #2]
	strb r2, [r1, #3]
	ldrb r0, [r4, r0]
	pop {r3, r4}
	bx lr
	nop
_0223E484: .word MOD12_022461E0

	thumb_func_start MOD12_0223E488
MOD12_0223E488: ; 0x0223E488
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	add r7, r2, #0
	cmp r4, #8
	blo _0223E49A
	bl ErrorHandling
_0223E49A:
	ldr r0, _0223E51C ; =0x00001BF1
	ldrb r0, [r5, r0]
	cmp r0, #1
	beq _0223E516
	add r0, r5, #0
	mov r1, #1
	add r0, #0x88
	add r2, r1, #0
	mov r3, #0xe
	bl FUN_0200D0BC
	ldr r0, [r5, #0x74]
	mov r1, #1
	bl FUN_0201AC68
	add r0, r5, #0
	add r0, #0x98
	ldr r1, _0223E520 ; =MOD12_02246224
	lsl r4, r4, #2
	ldrh r1, [r1, r4]
	ldr r0, [r0]
	bl NewString_ReadMsgData
	ldr r1, _0223E524 ; =MOD12_02246224 + 2
	add r6, r0, #0
	ldrb r1, [r1, r4]
	add r0, r5, #0
	add r2, r7, #0
	bl MOD12_0223E068
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0x9c
	add r1, #0xa0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	add r0, #0x88
	mov r1, #0xff
	bl FillWindowPixelBuffer
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	add r2, r5, #0
	add r0, r5, #0
	str r3, [sp, #8]
	add r2, #0xa0
	ldr r2, [r2]
	add r0, #0x88
	mov r1, #1
	bl AddTextPrinterParameterized
	add r0, r6, #0
	bl String_dtor
	ldr r0, _0223E51C ; =0x00001BF1
	mov r1, #1
	strb r1, [r5, r0]
_0223E516:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_0223E51C: .word 0x00001BF1
_0223E520: .word MOD12_02246224
_0223E524: .word MOD12_02246224 + 2

	thumb_func_start MOD12_0223E528
MOD12_0223E528: ; 0x0223E528
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x88
	mov r1, #1
	bl FUN_0200D0E0
	ldr r0, [r4, #0x74]
	mov r1, #1
	bl FUN_0201AC68
	ldr r0, _0223E544 ; =0x00001BF1
	mov r1, #0
	strb r1, [r4, r0]
	pop {r4, pc}
	.align 2, 0
_0223E544: .word 0x00001BF1

	thumb_func_start MOD12_0223E548
MOD12_0223E548: ; 0x0223E548
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _0223E584 ; =0x00000AEC
	ldrb r1, [r1, #4]
	ldr r3, [r5, r0]
	add r6, r2, #0
	mul r1, r3
	mul r6, r1
	add r1, r0, #4
	add r0, #8
	ldr r1, [r5, r1]
	ldr r0, [r5, r0]
	mov r4, #0
	add r0, r1, r0
	mul r0, r2
	add r0, r1, r0
	ldr r1, _0223E588 ; =0x00002710
	bl _u32_div_f
	add r1, r4, #0
	add r3, r6, r0
	ldr r0, _0223E58C ; =0x00001138
	adc r4, r1
	ldr r2, [r5, r0]
	add r0, r0, #4
	ldr r1, [r5, r0]
	sub r0, r3, r2
	sbc r4, r1
	add r1, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223E584: .word 0x00000AEC
_0223E588: .word 0x00002710
_0223E58C: .word 0x00001138

	thumb_func_start MOD12_0223E590
MOD12_0223E590: ; 0x0223E590
	ldr r3, _0223E594 ; =MOD12_0223E548
	bx r3
	.align 2, 0
_0223E594: .word MOD12_0223E548

	thumb_func_start MOD12_0223E598
MOD12_0223E598: ; 0x0223E598
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r5, r1, #0
	add r7, r2, #0
	mov r0, #0
	strb r0, [r7]
	mov r0, #0x17
	mov r1, #0x2c
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x2c
	add r4, r0, #0
	bl MI_CpuFill8
	add r1, r6, #0
	add r1, #0x18
	lsl r0, r5, #4
	str r6, [r4]
	add r0, r1, r0
	str r0, [r4, #4]
	mov r0, #0x85
	lsl r0, r0, #2
	add r1, r6, r0
	mov r0, #0x18
	mul r0, r5
	add r0, r1, r0
	str r0, [r4, #8]
	ldr r0, _0223E5F4 ; =0x00000AB4
	str r7, [r4, #0xc]
	add r1, r6, r5
	ldrb r0, [r1, r0]
	ldr r2, _0223E5F8 ; =0x00009C40
	cmp r0, #1
	bne _0223E5E8
	ldr r0, _0223E5FC ; =MOD12_0223E604
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
_0223E5E8:
	ldr r0, _0223E600 ; =MOD12_0223E6A4
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223E5F4: .word 0x00000AB4
_0223E5F8: .word 0x00009C40
_0223E5FC: .word MOD12_0223E604
_0223E600: .word MOD12_0223E6A4

	thumb_func_start MOD12_0223E604
MOD12_0223E604: ; 0x0223E604
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _0223E616
	cmp r0, #1
	beq _0223E636
	b _0223E686
_0223E616:
	ldr r0, [r4, #8]
	mov r1, #1
	mov r2, #0
	bl MOD12_0223CD38
	ldr r0, [r4, #4]
	ldr r0, [r0, #8]
	lsl r0, r0, #8
	str r0, [r4, #0x1c]
	str r0, [r4, #0x18]
	mov r0, #5
	lsl r0, r0, #8
	str r0, [r4, #0x14]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
_0223E636:
	ldr r1, [r4, #0x18]
	ldr r0, [r4, #0x14]
	sub r0, r1, r0
	str r0, [r4, #0x18]
	mov r0, #2
	ldr r1, [r4, #0x14]
	lsl r0, r0, #8
	sub r0, r1, r0
	str r0, [r4, #0x14]
	ldr r1, [r4, #0x1c]
	ldr r0, [r4, #0x18]
	cmp r0, r1
	blt _0223E66A
	str r1, [r4, #0x18]
	ldrb r0, [r4, #0x11]
	add r0, r0, #1
	strb r0, [r4, #0x11]
	ldrb r0, [r4, #0x11]
	cmp r0, #1
	bls _0223E666
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	b _0223E66A
_0223E666:
	mov r0, #0
	strb r0, [r4, #0x10]
_0223E66A:
	ldr r1, [r4, #0x18]
	asr r0, r1, #7
	lsr r0, r0, #0x18
	add r0, r1, r0
	asr r1, r0, #8
	ldr r0, [r4, #4]
	str r1, [r0, #8]
	ldr r2, [r4, #4]
	ldr r0, [r2]
	ldr r1, [r2, #4]
	ldr r2, [r2, #8]
	bl MOD17_021DD620
	pop {r3, r4, r5, pc}
_0223E686:
	ldr r0, [r4, #0xc]
	mov r1, #1
	strb r1, [r0]
	ldr r0, [r4, #8]
	add r2, r1, #0
	bl MOD12_0223CD38
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_0223E6A4
MOD12_0223E6A4: ; 0x0223E6A4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _0223E6B6
	cmp r0, #1
	beq _0223E6C6
	b _0223E720
_0223E6B6:
	ldr r0, [r4, #4]
	ldr r0, [r0, #4]
	lsl r0, r0, #8
	str r0, [r4, #0x28]
	str r0, [r4, #0x24]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
_0223E6C6:
	ldr r0, [r4, #0x20]
	bl Sin32
	lsl r1, r0, #2
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	mov r1, #0x32
	ldr r2, [r4, #0x20]
	lsl r1, r1, #0xc
	add r1, r2, r1
	str r1, [r4, #0x20]
	asr r2, r1, #0xc
	mov r1, #0x5a
	lsl r1, r1, #2
	asr r0, r0, #0xc
	cmp r2, r1
	blt _0223E702
	ldrb r1, [r4, #0x11]
	add r1, r1, #1
	strb r1, [r4, #0x11]
	ldrb r1, [r4, #0x11]
	cmp r1, #5
	bls _0223E702
	ldr r0, [r4, #0x28]
	str r0, [r4, #0x24]
	ldrb r1, [r4, #0x10]
	mov r0, #0
	add r1, r1, #1
	strb r1, [r4, #0x10]
_0223E702:
	ldr r2, [r4, #0x24]
	asr r1, r2, #7
	lsr r1, r1, #0x18
	add r1, r2, r1
	asr r1, r1, #8
	add r1, r1, r0
	ldr r0, [r4, #4]
	str r1, [r0, #4]
	ldr r2, [r4, #4]
	ldr r0, [r2]
	ldr r1, [r2, #4]
	ldr r2, [r2, #8]
	bl MOD17_021DD620
	pop {r3, r4, r5, pc}
_0223E720:
	ldr r0, [r4, #0xc]
	mov r1, #1
	strb r1, [r0]
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_0223E734
MOD12_0223E734: ; 0x0223E734
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0223E738
MOD12_0223E738: ; 0x0223E738
	push {r3, lr}
	ldr r0, _0223E74C ; =0x04000050
	mov r3, #0
	mov r1, #1
	mov r2, #0x3e
	str r3, [sp]
	bl G2x_SetBlendAlpha_
	pop {r3, pc}
	nop
_0223E74C: .word 0x04000050

	thumb_func_start MOD12_0223E750
MOD12_0223E750: ; 0x0223E750
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r0, #0xa4
	add r5, r1, #0
	ldr r0, [r0]
	mov r1, #0
	bl FUN_020031FC
	ldr r3, _0223E77C ; =MOD12_0224620C
	lsl r5, r5, #2
	ldrh r1, [r3, r5]
	add r3, r3, r5
	ldr r2, _0223E780 ; =0x00001FE3
	str r1, [sp]
	ldrh r3, [r3, #2]
	ldr r1, _0223E784 ; =0x0000110C
	lsl r3, r3, #0x18
	ldr r1, [r4, r1]
	lsr r3, r3, #0x18
	bl FUN_02003A30
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223E77C: .word MOD12_0224620C
_0223E780: .word 0x00001FE3
_0223E784: .word 0x0000110C

	thumb_func_start MOD12_0223E788
MOD12_0223E788: ; 0x0223E788
	push {r3, lr}
	ldrb r2, [r1, #7]
	cmp r2, #0
	bne _0223E7D0
	ldrb r2, [r1, #4]
	cmp r2, #0
	beq _0223E79E
	cmp r2, #1
	beq _0223E79E
	cmp r2, #2
	b _0223E7CA
_0223E79E:
	ldrb r2, [r1, #3]
	cmp r2, #4
	bhi _0223E7CC
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0223E7B0: ; jump table
	.short _0223E7CC - _0223E7B0 - 2 ; case 0
	.short _0223E7BA - _0223E7B0 - 2 ; case 1
	.short _0223E7BE - _0223E7B0 - 2 ; case 2
	.short _0223E7C2 - _0223E7B0 - 2 ; case 3
	.short _0223E7C6 - _0223E7B0 - 2 ; case 4
_0223E7BA:
	mov r1, #1
	b _0223E7CC
_0223E7BE:
	mov r1, #2
	b _0223E7CC
_0223E7C2:
	mov r1, #3
	b _0223E7CC
_0223E7C6:
	mov r1, #4
	b _0223E7CC
_0223E7CA:
	mov r1, #5
_0223E7CC:
	bl MOD12_0223E750
_0223E7D0:
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223E7D4
MOD12_0223E7D4: ; 0x0223E7D4
	push {r3, r4, r5, r6, r7, lr}
	str r1, [sp]
	ldr r1, _0223E844 ; =0x00000AE8
	mov ip, r0
	ldr r0, [r0, r1]
	ldr r1, _0223E848 ; =0x00001BA0
	lsr r7, r0, #1
	mov r0, ip
	add r3, r0, r1
	ldr r1, _0223E84C ; =0x04000280
	mov r6, #0
	mov r4, ip
	lsr r0, r1, #0xb
_0223E7EE:
	ldrb r2, [r3]
	lsl r2, r2, #0x1d
	lsr r2, r2, #0x1f
	cmp r2, #1
	bne _0223E836
	ldr r2, _0223E850 ; =0x00001B9E
	mov r5, #0
	ldrb r2, [r4, r2]
	add r2, #0x10
	strh r5, [r1]
	ldr r5, _0223E854 ; =0x04000290
	mul r2, r7
	str r2, [r5]
	ldr r5, _0223E858 ; =0x00002710
	ldr r2, _0223E85C ; =0x04000298
	str r5, [r2]
	mov r5, #0
	str r5, [r2, #4]
_0223E812:
	ldrh r2, [r1]
	tst r2, r0
	bne _0223E812
	ldr r2, _0223E860 ; =0x040002A0
	ldr r5, [r2]
	ldr r2, [sp]
	cmp r5, r2
	bne _0223E836
	ldr r2, _0223E864 ; =0x00001B98
	mov r1, ip
	add r2, r1, r2
	mov r1, #0xa
	mul r1, r6
	mov r0, ip
	add r1, r2, r1
	bl MOD12_0223E788
	pop {r3, r4, r5, r6, r7, pc}
_0223E836:
	add r6, r6, #1
	add r3, #0xa
	add r4, #0xa
	cmp r6, #8
	blt _0223E7EE
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223E844: .word 0x00000AE8
_0223E848: .word 0x00001BA0
_0223E84C: .word 0x04000280
_0223E850: .word 0x00001B9E
_0223E854: .word 0x04000290
_0223E858: .word 0x00002710
_0223E85C: .word 0x04000298
_0223E860: .word 0x040002A0
_0223E864: .word 0x00001B98

	thumb_func_start MOD12_0223E868
MOD12_0223E868: ; 0x0223E868
	push {r3, r4, r5, lr}
	add r4, r0, #0
	mov r0, #0x82
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0223E87A
	bl ErrorHandling
_0223E87A:
	mov r0, #0x81
	lsl r0, r0, #2
	add r5, r4, r0
	ldr r0, _0223E890 ; =MOD12_0223E8EC
	ldr r2, _0223E894 ; =0x00009C40
	add r1, r5, #0
	str r4, [r5]
	bl FUN_0200CA44
	str r0, [r5, #4]
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223E890: .word MOD12_0223E8EC
_0223E894: .word 0x00009C40

	thumb_func_start MOD12_0223E898
MOD12_0223E898: ; 0x0223E898
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x82
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0223E8B2
	bl FUN_0200CAB4
	mov r0, #0x82
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
_0223E8B2:
	pop {r4, pc}

	thumb_func_start MOD12_0223E8B4
MOD12_0223E8B4: ; 0x0223E8B4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r1, #0x81
	lsl r1, r1, #2
	add r4, r0, r1
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _0223E8C8
	bl ErrorHandling
_0223E8C8:
	cmp r5, #0
	bne _0223E8D0
	mov r0, #0x40
	b _0223E8D2
_0223E8D0:
	mov r0, #0x30
_0223E8D2:
	strb r0, [r4, #0xa]
	mov r0, #1
	strb r0, [r4, #0xb]
	mov r0, #0xa
	lsl r0, r0, #8
	strh r0, [r4, #8]
	ldr r0, _0223E8E8 ; =0x000006F8
	bl FUN_020054C8
	pop {r3, r4, r5, pc}
	nop
_0223E8E8: .word 0x000006F8

	thumb_func_start MOD12_0223E8EC
MOD12_0223E8EC: ; 0x0223E8EC
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldrb r0, [r4, #0xb]
	cmp r0, #0
	beq _0223E946
	ldr r0, [r4]
	mov r1, #0
	add r0, #0xa4
	ldr r0, [r0]
	bl FUN_020031FC
	ldrb r1, [r4, #0xa]
	lsl r3, r1, #1
	ldr r1, _0223E94C ; =0x00007FFF
	add r0, r0, r3
	str r1, [sp]
	ldr r2, [r4]
	ldr r1, _0223E950 ; =0x0000110C
	ldr r1, [r2, r1]
	mov r2, #0x10
	add r1, r1, r3
	ldrh r3, [r4, #8]
	asr r3, r3, #8
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FUN_02003974
	ldrh r1, [r4, #8]
	cmp r1, #0
	bne _0223E932
	mov r0, #0
	add sp, #4
	strb r0, [r4, #0xb]
	pop {r3, r4, pc}
_0223E932:
	mov r0, #1
	lsl r0, r0, #8
	cmp r1, r0
	bls _0223E942
	sub r0, r1, r0
	add sp, #4
	strh r0, [r4, #8]
	pop {r3, r4, pc}
_0223E942:
	mov r0, #0
	strh r0, [r4, #8]
_0223E946:
	add sp, #4
	pop {r3, r4, pc}
	nop
_0223E94C: .word 0x00007FFF
_0223E950: .word 0x0000110C

	thumb_func_start MOD12_0223E954
MOD12_0223E954: ; 0x0223E954
	push {r3, r4, r5, lr}
	ldr r5, _0223E97C ; =0x00001120
	add r4, r0, #0
	str r2, [r4, r5]
	add r0, r5, #4
	str r3, [r4, r0]
	add r0, r5, #0
	ldr r2, [sp, #0x10]
	add r0, #8
	str r2, [r4, r0]
	ldr r0, [sp, #0x14]
	add r5, #0xc
	str r0, [r4, r5]
	ldr r0, [r4, #0xc]
	ldr r2, _0223E980 ; =MOD12_0223E984
	add r3, r4, #0
	bl FUN_020133AC
	pop {r3, r4, r5, pc}
	nop
_0223E97C: .word 0x00001120
_0223E980: .word MOD12_0223E984

	thumb_func_start MOD12_0223E984
MOD12_0223E984: ; 0x0223E984
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0201341C
	ldr r1, _0223E9C0 ; =0x00001120
	add r1, r0, r1
	ldr r0, [r4, #0x20]
	ldr r2, [r1]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	add r0, r2, r0
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x20]
	ldr r2, [r1, #4]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	add r0, r2, r0
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x20]
	ldr r2, [r1, #8]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	add r0, r2, r0
	str r0, [r4, #0x30]
	ldr r1, [r1, #0xc]
	add r0, r4, #0
	bl FUN_02013450
	pop {r4, pc}
	nop
_0223E9C0: .word 0x00001120

	thumb_func_start MOD12_0223E9C4
MOD12_0223E9C4: ; 0x0223E9C4
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r1, #0
	add r4, r0, #0
	add r6, r2, #0
	cmp r5, #0x21
	blo _0223E9D6
	bl ErrorHandling
_0223E9D6:
	ldr r0, _0223EA3C ; =MOD12_0224637C
	lsl r1, r5, #2
	ldr r5, [r0, r1]
	cmp r6, #0
	ldr r0, _0223EA40 ; =0xFFFFEB80
	ldr r3, _0223EA44 ; =0xFFFFBADC
	bne _0223EA10
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	add r2, r5, #0
	bl MOD12_0223E954
	ldr r0, _0223EA40 ; =0xFFFFEB80
	ldr r3, _0223EA44 ; =0xFFFFBADC
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #1
	add r2, r5, #0
	bl MOD12_0223E954
	add sp, #8
	pop {r4, r5, r6, pc}
_0223EA10:
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #2
	add r2, r5, #0
	bl MOD12_0223E954
	ldr r0, _0223EA40 ; =0xFFFFEB80
	ldr r3, _0223EA44 ; =0xFFFFBADC
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #3
	add r2, r5, #0
	bl MOD12_0223E954
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223EA3C: .word MOD12_0224637C
_0223EA40: .word 0xFFFFEB80
_0223EA44: .word 0xFFFFBADC

	thumb_func_start MOD12_0223EA48
MOD12_0223EA48: ; 0x0223EA48
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	cmp r1, #0
	ldr r1, _0223EBFC ; =0xFFFFEB80
	ldr r3, _0223EC00 ; =0xFFFFE764
	bne _0223EAD6
	str r1, [sp]
	mov r1, #1
	lsl r1, r1, #0xc
	str r1, [sp, #4]
	ldr r2, _0223EC04 ; =0xFFFFCD38
	mov r1, #5
	bl MOD12_0223E954
	ldr r0, _0223EBFC ; =0xFFFFEB80
	ldr r2, _0223EC04 ; =0xFFFFCD38
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r3, _0223EC00 ; =0xFFFFE764
	add r0, r4, #0
	mov r1, #6
	bl MOD12_0223E954
	ldr r0, _0223EBFC ; =0xFFFFEB80
	ldr r2, _0223EC04 ; =0xFFFFCD38
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r3, _0223EC00 ; =0xFFFFE764
	add r0, r4, #0
	mov r1, #7
	bl MOD12_0223E954
	ldr r0, _0223EBFC ; =0xFFFFEB80
	ldr r2, _0223EC08 ; =0x00005014
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r3, _0223EC00 ; =0xFFFFE764
	add r0, r4, #0
	mov r1, #5
	bl MOD12_0223E954
	ldr r0, _0223EBFC ; =0xFFFFEB80
	ldr r2, _0223EC08 ; =0x00005014
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r3, _0223EC00 ; =0xFFFFE764
	add r0, r4, #0
	mov r1, #6
	bl MOD12_0223E954
	ldr r0, _0223EBFC ; =0xFFFFEB80
	ldr r2, _0223EC08 ; =0x00005014
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r3, _0223EC00 ; =0xFFFFE764
	add r0, r4, #0
	mov r1, #7
	bl MOD12_0223E954
	b _0223EBAC
_0223EAD6:
	str r1, [sp]
	mov r1, #1
	lsl r1, r1, #0xc
	str r1, [sp, #4]
	ldr r2, _0223EC0C ; =0xFFFFBD98
	mov r1, #8
	bl MOD12_0223E954
	ldr r0, _0223EBFC ; =0xFFFFEB80
	ldr r2, _0223EC0C ; =0xFFFFBD98
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r3, _0223EC00 ; =0xFFFFE764
	add r0, r4, #0
	mov r1, #9
	bl MOD12_0223E954
	ldr r0, _0223EBFC ; =0xFFFFEB80
	ldr r2, _0223EC0C ; =0xFFFFBD98
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r3, _0223EC00 ; =0xFFFFE764
	add r0, r4, #0
	mov r1, #0xa
	bl MOD12_0223E954
	ldr r0, _0223EBFC ; =0xFFFFEB80
	ldr r2, _0223EC0C ; =0xFFFFBD98
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r3, _0223EC00 ; =0xFFFFE764
	add r0, r4, #0
	mov r1, #0xb
	bl MOD12_0223E954
	ldr r0, _0223EBFC ; =0xFFFFEB80
	ldr r2, _0223EC0C ; =0xFFFFBD98
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r3, _0223EC00 ; =0xFFFFE764
	add r0, r4, #0
	mov r1, #0xc
	bl MOD12_0223E954
	ldr r0, _0223EBFC ; =0xFFFFEB80
	ldr r2, _0223EC10 ; =0x00004074
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r3, _0223EC00 ; =0xFFFFE764
	add r0, r4, #0
	mov r1, #8
	bl MOD12_0223E954
	ldr r0, _0223EBFC ; =0xFFFFEB80
	ldr r2, _0223EC10 ; =0x00004074
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r3, _0223EC00 ; =0xFFFFE764
	add r0, r4, #0
	mov r1, #9
	bl MOD12_0223E954
	ldr r0, _0223EBFC ; =0xFFFFEB80
	ldr r2, _0223EC10 ; =0x00004074
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r3, _0223EC00 ; =0xFFFFE764
	add r0, r4, #0
	mov r1, #0xa
	bl MOD12_0223E954
	ldr r0, _0223EBFC ; =0xFFFFEB80
	ldr r2, _0223EC10 ; =0x00004074
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r3, _0223EC00 ; =0xFFFFE764
	add r0, r4, #0
	mov r1, #0xb
	bl MOD12_0223E954
	ldr r0, _0223EBFC ; =0xFFFFEB80
	ldr r2, _0223EC10 ; =0x00004074
	str r0, [sp]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r3, _0223EC00 ; =0xFFFFE764
	add r0, r4, #0
	mov r1, #0xc
	bl MOD12_0223E954
_0223EBAC:
	mov r0, #0
	str r0, [sp]
	ldr r0, _0223EC14 ; =0x00007FFF
	ldr r1, _0223EC18 ; =0x00001FE3
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #8
	mov r3, #0x10
	bl MOD12_0223EC4C
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r2, _0223EC14 ; =0x00007FFF
	add r0, r4, #0
	str r2, [sp, #8]
	add r0, #0xa4
	mov r1, #4
	ldr r0, [r0]
	lsr r2, r2, #1
	sub r3, r1, #5
	bl FUN_02003210
	ldr r0, _0223EC1C ; =0x04000050
	mov r1, #0x3f
	mov r2, #0x10
	bl G2x_SetBlendBrightness_
	mov r2, #0xfa
	ldr r0, _0223EC20 ; =MOD12_0223EC28
	add r1, r4, #0
	lsl r2, r2, #2
	bl FUN_0200CA44
	ldr r0, _0223EC24 ; =0x000006E5
	bl FUN_020054C8
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_0223EBFC: .word 0xFFFFEB80
_0223EC00: .word 0xFFFFE764
_0223EC04: .word 0xFFFFCD38
_0223EC08: .word 0x00005014
_0223EC0C: .word 0xFFFFBD98
_0223EC10: .word 0x00004074
_0223EC14: .word 0x00007FFF
_0223EC18: .word 0x00001FE3
_0223EC1C: .word 0x04000050
_0223EC20: .word MOD12_0223EC28
_0223EC24: .word 0x000006E5

	thumb_func_start MOD12_0223EC28
MOD12_0223EC28: ; 0x0223EC28
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r3, #0
	ldr r0, _0223EC48 ; =0x04000050
	mov r1, #1
	mov r2, #0x3e
	str r3, [sp]
	bl G2x_SetBlendAlpha_
	add r0, r4, #0
	bl FUN_0200CAB4
	add sp, #4
	pop {r3, r4, pc}
	nop
_0223EC48: .word 0x04000050

	thumb_func_start MOD12_0223EC4C
MOD12_0223EC4C: ; 0x0223EC4C
	push {r3, r4, r5, lr}
	ldr r4, _0223EC78 ; =0x0000110C
	ldr r5, [sp, #0x10]
	add r4, r0, r4
	lsl r0, r3, #8
	strh r0, [r4, #8]
	lsl r0, r5, #8
	strh r0, [r4, #0xa]
	add r0, sp, #0
	ldrh r0, [r0, #0x14]
	strh r0, [r4, #0xe]
	sub r0, r5, r3
	strh r1, [r4, #6]
	lsl r0, r0, #8
	add r1, r2, #0
	bl _u32_div_f
	strh r0, [r4, #0xc]
	mov r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
	nop
_0223EC78: .word 0x0000110C

	thumb_func_start MOD12_0223EC7C
MOD12_0223EC7C: ; 0x0223EC7C
	ldr r2, _0223EC84 ; =0x0000111D
	strb r1, [r0, r2]
	bx lr
	nop
_0223EC84: .word 0x0000111D

	thumb_func_start MOD12_0223EC88
MOD12_0223EC88: ; 0x0223EC88
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	str r1, [sp]
	cmp r2, #0
	bne _0223EC98
	ldr r7, _0223ECC4 ; =0x00007FFF
	ldr r6, _0223ECC8 ; =0x0000254A
	b _0223EC9C
_0223EC98:
	ldr r7, _0223ECC8 ; =0x0000254A
	ldr r6, _0223ECC4 ; =0x00007FFF
_0223EC9C:
	mov r4, #0
_0223EC9E:
	ldr r0, [sp]
	cmp r4, r0
	ldr r0, [r5, #0x18]
	bne _0223ECAE
	add r1, r7, #0
	bl MOD17_021DD6B8
	b _0223ECB4
_0223ECAE:
	add r1, r6, #0
	bl MOD17_021DD6B8
_0223ECB4:
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #4
	blt _0223EC9E
	ldr r0, _0223ECCC ; =0x000006EC
	bl FUN_020054C8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223ECC4: .word 0x00007FFF
_0223ECC8: .word 0x0000254A
_0223ECCC: .word 0x000006EC

	thumb_func_start MOD12_0223ECD0
MOD12_0223ECD0: ; 0x0223ECD0
	push {r4, r5, r6, lr}
	ldr r6, _0223ECEC ; =0x00007FFF
	add r5, r0, #0
	mov r4, #0
_0223ECD8:
	ldr r0, [r5, #0x18]
	add r1, r6, #0
	bl MOD17_021DD6B8
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #4
	blt _0223ECD8
	pop {r4, r5, r6, pc}
	nop
_0223ECEC: .word 0x00007FFF

	thumb_func_start MOD12_0223ECF0
MOD12_0223ECF0: ; 0x0223ECF0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r0, [sp, #0xc]
	mov r4, #0
	add r5, sp, #0x18
	add r3, sp, #0x14
	ldr r2, _0223ED9C ; =0x00000ADA
	b _0223ED0E
_0223ED00:
	ldr r1, [sp, #0xc]
	lsl r0, r4, #1
	add r1, r1, r0
	ldrsh r1, [r1, r2]
	strb r4, [r3, r4]
	add r4, r4, #1
	strh r1, [r5, r0]
_0223ED0E:
	cmp r4, #4
	blt _0223ED00
	mov r4, #0
	add r7, sp, #0x18
	b _0223ED42
_0223ED18:
	mov r6, #3
	b _0223ED3C
_0223ED1C:
	sub r3, r6, #1
	lsl r5, r3, #1
	lsl r1, r6, #1
	ldrsh r2, [r7, r5]
	ldrsh r0, [r7, r1]
	cmp r2, r0
	bge _0223ED3A
	strh r2, [r7, r1]
	strh r0, [r7, r5]
	add r0, sp, #0x14
	add r1, sp, #0x14
	ldrb r0, [r0, r6]
	ldrb r2, [r1, r3]
	strb r2, [r1, r6]
	strb r0, [r1, r3]
_0223ED3A:
	sub r6, r6, #1
_0223ED3C:
	cmp r6, r4
	bgt _0223ED1C
	add r4, r4, #1
_0223ED42:
	cmp r4, #3
	blt _0223ED18
	ldr r3, _0223EDA0 ; =MOD12_02246400
	add r0, sp, #0x10
	ldrb r1, [r3]
	mov r4, #1
	add r2, sp, #0x10
	strb r1, [r0]
	add r1, sp, #0x18
	b _0223ED6E
_0223ED56:
	ldrb r0, [r3, r4]
	sub r6, r4, #1
	lsl r5, r6, #1
	strb r0, [r2, r4]
	lsl r0, r4, #1
	ldrsh r0, [r1, r0]
	ldrsh r5, [r1, r5]
	cmp r0, r5
	bne _0223ED6C
	ldrb r0, [r2, r6]
	strb r0, [r2, r4]
_0223ED6C:
	add r4, r4, #1
_0223ED6E:
	cmp r4, #4
	blt _0223ED56
	mov r4, #0
	add r5, sp, #0x10
	mov r6, #0x1e
	add r7, r4, #0
	b _0223ED94
_0223ED7C:
	ldrb r0, [r5, r4]
	add r1, sp, #0x14
	ldrb r1, [r1, r4]
	str r0, [sp]
	str r6, [sp, #4]
	ldr r0, [sp, #0xc]
	ldr r2, _0223EDA4 ; =0x00007FFF
	ldr r3, _0223EDA8 ; =0x0000254A
	str r7, [sp, #8]
	bl MOD12_0223EDAC
	add r4, r4, #1
_0223ED94:
	cmp r4, #4
	blt _0223ED7C
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223ED9C: .word 0x00000ADA
_0223EDA0: .word MOD12_02246400
_0223EDA4: .word 0x00007FFF
_0223EDA8: .word 0x0000254A

	thumb_func_start MOD12_0223EDAC
MOD12_0223EDAC: ; 0x0223EDAC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r0, #0
	str r1, [sp]
	mov r0, #0x17
	mov r1, #0x14
	add r6, r2, #0
	str r3, [sp, #4]
	ldr r5, [sp, #0x28]
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x14
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp]
	ldr r1, [sp, #0x24]
	lsl r0, r0, #4
	add r0, r7, r0
	ldr r0, [r0, #0x18]
	str r0, [r4]
	strh r6, [r4, #8]
	ldr r0, [sp, #4]
	strh r0, [r4, #0xa]
	ldr r0, [sp, #0x20]
	strb r0, [r4, #0x10]
	lsl r0, r0, #8
	bl _s32_div_f
	strh r0, [r4, #0xc]
	str r5, [r4, #4]
	cmp r5, #0
	beq _0223EDF4
	mov r0, #0
	strb r0, [r5]
_0223EDF4:
	ldr r0, [r4]
	add r1, r6, #0
	bl MOD17_021DD6B8
	ldr r0, _0223EE0C ; =MOD12_0223EE14
	ldr r2, _0223EE10 ; =0x00009C40
	add r1, r4, #0
	bl FUN_0200CA44
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223EE0C: .word MOD12_0223EE14
_0223EE10: .word 0x00009C40

	thumb_func_start MOD12_0223EE14
MOD12_0223EE14: ; 0x0223EE14
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r1, #0
	add r6, r0, #0
	ldrh r1, [r5, #0xe]
	ldrh r0, [r5, #0xc]
	add r0, r1, r0
	strh r0, [r5, #0xe]
	ldrh r0, [r5, #0xe]
	asr r4, r0, #8
	ldrb r0, [r5, #0x10]
	cmp r4, r0
	ble _0223EE30
	add r4, r0, #0
_0223EE30:
	ldrh r0, [r5, #0xa]
	lsl r3, r4, #0x18
	add r1, sp, #4
	str r0, [sp]
	add r0, r5, #0
	add r0, #8
	mov r2, #1
	lsr r3, r3, #0x18
	bl FUN_02003974
	add r1, sp, #4
	ldrh r1, [r1]
	ldr r0, [r5]
	bl MOD17_021DD6B8
	ldrb r0, [r5, #0x10]
	cmp r4, r0
	blt _0223EE6A
	ldr r1, [r5, #4]
	cmp r1, #0
	beq _0223EE5E
	mov r0, #1
	strb r0, [r1]
_0223EE5E:
	add r0, r5, #0
	bl FreeToHeap
	add r0, r6, #0
	bl FUN_0200CAB4
_0223EE6A:
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD12_0223EE70
MOD12_0223EE70: ; 0x0223EE70
	cmp r0, #0x32
	beq _0223EE78
	cmp r0, #0x33
	bne _0223EE7C
_0223EE78:
	mov r0, #0
	bx lr
_0223EE7C:
	mov r0, #1
	bx lr

	thumb_func_start MOD12_0223EE80
MOD12_0223EE80: ; 0x0223EE80
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r1, _0223EEB4 ; =MOD12_02246424
	add r3, sp, #0
	str r1, [sp]
	mov r1, #0xd
	strh r1, [r3, #4]
	ldr r1, [r0]
	ldr r2, _0223EEB8 ; =0x00000123
	ldrb r1, [r1, r2]
	strb r1, [r3, #6]
	sub r1, r2, #7
	ldr r4, [r0]
	add r2, #0x4e
	ldrb r1, [r4, r1]
	strb r1, [r3, #8]
	ldr r1, [r0]
	ldrb r1, [r1, r2]
	strb r1, [r3, #7]
	ldr r1, _0223EEBC ; =0x00001158
	add r0, r0, r1
	add r1, sp, #0
	bl MOD12_02240ED0
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_0223EEB4: .word MOD12_02246424
_0223EEB8: .word 0x00000123
_0223EEBC: .word 0x00001158

	thumb_func_start MOD12_0223EEC0
MOD12_0223EEC0: ; 0x0223EEC0
	push {r3, lr}
	lsl r2, r2, #0x10
	mov r3, #0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223EED4
MOD12_0223EED4: ; 0x0223EED4
	push {r3, lr}
	add r1, r2, #0
	mov r2, #0
	add r3, r2, #0
	bl MOD12_02240FB0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223EEE4
MOD12_0223EEE4: ; 0x0223EEE4
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0223EEE8
MOD12_0223EEE8: ; 0x0223EEE8
	push {r3, lr}
	lsl r2, r2, #0x10
	mov r3, #0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223EEFC
MOD12_0223EEFC: ; 0x0223EEFC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x17
	mov r1, #0x18
	add r5, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x18
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _0223EF38 ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, _0223EF3C ; =MOD12_0223EF40
	str r6, [r4, #0xc]
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223EF38: .word 0x00007530
_0223EF3C: .word MOD12_0223EF40

	thumb_func_start MOD12_0223EF40
MOD12_0223EF40: ; 0x0223EF40
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldrb r0, [r1, #0x10]
	str r1, [sp]
	cmp r0, #0
	beq _0223EF50
	b _0223F076
_0223EF50:
	ldr r0, [sp]
	mov r1, #0x14
	ldrsb r0, [r0, r1]
	cmp r0, #0
	ble _0223EF64
	sub r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x14]
	pop {r4, r5, r6, r7, pc}
_0223EF64:
	ldr r0, [sp]
	mov r1, #0x13
	ldrsb r0, [r0, r1]
	cmp r0, #0
	ble _0223EF78
	sub r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x13]
	pop {r4, r5, r6, r7, pc}
_0223EF78:
	ldr r0, [sp]
	mov r1, #1
	strb r1, [r0, #0x13]
	ldr r0, [r0]
	mov r1, #2
	ldr r0, [r0, #0x74]
	bl FUN_0201886C
	mov ip, r0
	mov r0, #0
	str r0, [sp, #8]
	b _0223EFF0
_0223EF90:
	ldr r0, [sp]
	mov r1, #0x11
	ldrsb r1, [r0, r1]
	ldr r0, _0223F094 ; =MOD12_02246404
	ldrsb r1, [r0, r1]
	ldr r0, [sp, #8]
	add r0, r1, r0
	bmi _0223EFEA
	lsl r1, r0, #6
	mov r0, ip
	add r3, r0, r1
	ldr r0, [sp]
	mov r5, #0
	ldrb r0, [r0, #0x12]
	mov r7, #0x3f
	str r5, [sp, #4]
	lsl r1, r0, #1
	ldr r0, _0223F098 ; =MOD12_0224640C
	lsl r7, r7, #0xa
	ldrh r1, [r0, r1]
	ldr r0, [sp, #8]
	lsl r0, r0, #5
	add r6, r1, r0
	b _0223EFE4
_0223EFC0:
	mov r4, #0
	b _0223EFD8
_0223EFC4:
	add r0, r5, r4
	lsl r2, r0, #1
	ldrh r0, [r3, r2]
	and r0, r7
	strh r0, [r3, r2]
	ldrh r1, [r3, r2]
	add r0, r6, r4
	add r4, r4, #1
	orr r0, r1
	strh r0, [r3, r2]
_0223EFD8:
	cmp r4, #8
	blt _0223EFC4
	ldr r0, [sp, #4]
	add r5, #8
	add r0, r0, #1
	str r0, [sp, #4]
_0223EFE4:
	ldr r0, [sp, #4]
	cmp r0, #4
	blt _0223EFC0
_0223EFEA:
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
_0223EFF0:
	ldr r0, [sp, #8]
	cmp r0, #4
	blt _0223EF90
	ldr r0, [sp]
	mov r1, #0x11
	ldrsb r1, [r0, r1]
	cmp r1, #0
	ble _0223F032
	ldrb r0, [r0, #0x12]
	cmp r0, #0
	bne _0223F032
	ldr r0, _0223F094 ; =MOD12_02246404
	sub r1, r1, #1
	ldrsb r0, [r0, r1]
	lsl r1, r0, #6
	mov r0, ip
	add r3, r0, r1
	mov r0, #0
	mov r1, #0x3f
	str r0, [sp, #4]
	lsl r1, r1, #0xa
	b _0223F02C
_0223F01C:
	ldr r0, [sp, #4]
	lsl r2, r0, #1
	ldrh r0, [r3, r2]
	and r0, r1
	strh r0, [r3, r2]
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
_0223F02C:
	ldr r0, [sp, #4]
	cmp r0, #0x20
	blt _0223F01C
_0223F032:
	ldr r0, [sp]
	mov r1, #2
	ldr r0, [r0]
	ldr r0, [r0, #0x74]
	bl FUN_0201AC68
	ldr r0, [sp]
	ldrb r0, [r0, #0x12]
	add r1, r0, #1
	ldr r0, [sp]
	strb r1, [r0, #0x12]
	ldrb r0, [r0, #0x12]
	cmp r0, #0xc
	blo _0223F090
	ldr r1, [sp]
	mov r0, #0
	mov r2, #0x11
	strb r0, [r1, #0x12]
	ldrsb r1, [r1, r2]
	add r3, r1, #1
	ldr r1, [sp]
	strb r3, [r1, #0x11]
	strb r0, [r1, #0x14]
	add r0, r1, #0
	ldrsb r0, [r0, r2]
	cmp r0, #5
	blo _0223F090
	add r0, r1, #0
	ldrb r0, [r0, #0x10]
	add r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x10]
	pop {r4, r5, r6, r7, pc}
_0223F076:
	add r0, r1, #0
	mov r2, #0
	ldr r0, [r0, #0xc]
	add r1, r1, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	ldr r0, [sp]
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_0223F090:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223F094: .word MOD12_02246404
_0223F098: .word MOD12_0224640C

	thumb_func_start MOD12_0223F09C
MOD12_0223F09C: ; 0x0223F09C
	push {r3, lr}
	lsl r2, r2, #0x10
	mov r3, #0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223F0B0
MOD12_0223F0B0: ; 0x0223F0B0
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r6, r1, #0
	mov r0, #0x17
	mov r1, #0x18
	add r5, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x18
	bl MI_CpuFill8
	str r6, [r4]
	ldrh r0, [r5]
	ldr r2, _0223F0F8 ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, _0223F0FC ; =MOD12_0223F108
	str r7, [r4, #0xc]
	bl FUN_0200CA44
	ldr r0, _0223F100 ; =0x00001134
	mov r1, #0
	strb r1, [r6, r0]
	ldr r0, _0223F104 ; =0x0000046F
	bl FUN_0200521C
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223F0F8: .word 0x00007530
_0223F0FC: .word MOD12_0223F108
_0223F100: .word 0x00001134
_0223F104: .word 0x0000046F

	thumb_func_start MOD12_0223F108
MOD12_0223F108: ; 0x0223F108
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldrb r0, [r1, #0x10]
	str r1, [sp]
	cmp r0, #0
	beq _0223F118
	b _0223F266
_0223F118:
	ldr r0, [sp]
	mov r1, #0x14
	ldrsb r0, [r0, r1]
	cmp r0, #0
	ble _0223F12C
	sub r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x14]
	pop {r4, r5, r6, r7, pc}
_0223F12C:
	ldr r0, [sp]
	mov r1, #0x13
	ldrsb r0, [r0, r1]
	cmp r0, #0
	ble _0223F140
	sub r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x13]
	pop {r4, r5, r6, r7, pc}
_0223F140:
	ldr r0, [sp]
	mov r1, #1
	strb r1, [r0, #0x13]
	ldr r0, [r0]
	mov r1, #2
	ldr r0, [r0, #0x74]
	bl FUN_0201886C
	mov ip, r0
	mov r0, #0
	str r0, [sp, #8]
	b _0223F1C0
_0223F158:
	ldr r0, [sp]
	mov r1, #0x11
	ldrsb r1, [r0, r1]
	mov r0, #4
	sub r1, r0, r1
	ldr r0, _0223F284 ; =MOD12_02246404
	ldrsb r1, [r0, r1]
	ldr r0, [sp, #8]
	add r0, r1, r0
	bmi _0223F1BA
	lsl r1, r0, #6
	mov r0, ip
	add r3, r0, r1
	ldr r0, [sp]
	mov r5, #0
	ldrb r1, [r0, #0x12]
	mov r0, #0xb
	mov r7, #0x3f
	sub r0, r0, r1
	lsl r1, r0, #1
	ldr r0, _0223F288 ; =MOD12_0224640C
	str r5, [sp, #4]
	ldrh r1, [r0, r1]
	ldr r0, [sp, #8]
	lsl r7, r7, #0xa
	lsl r0, r0, #5
	add r6, r1, r0
	b _0223F1B4
_0223F190:
	mov r4, #0
	b _0223F1A8
_0223F194:
	add r0, r5, r4
	lsl r2, r0, #1
	ldrh r0, [r3, r2]
	and r0, r7
	strh r0, [r3, r2]
	ldrh r1, [r3, r2]
	add r0, r6, r4
	add r4, r4, #1
	orr r0, r1
	strh r0, [r3, r2]
_0223F1A8:
	cmp r4, #8
	blt _0223F194
	ldr r0, [sp, #4]
	add r5, #8
	add r0, r0, #1
	str r0, [sp, #4]
_0223F1B4:
	ldr r0, [sp, #4]
	cmp r0, #4
	blt _0223F190
_0223F1BA:
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
_0223F1C0:
	ldr r0, [sp, #8]
	cmp r0, #4
	blt _0223F158
	ldr r0, [sp]
	mov r1, #0x11
	ldrsb r1, [r0, r1]
	cmp r1, #0
	ble _0223F222
	ldrb r0, [r0, #0x12]
	cmp r0, #0
	bne _0223F222
	mov r0, #5
	sub r1, r0, r1
	ldr r0, _0223F284 ; =MOD12_02246404
	mov r7, #0x3f
	ldrsb r0, [r0, r1]
	lsl r7, r7, #0xa
	mov r6, #0x1d
	add r0, r0, #3
	lsl r1, r0, #6
	mov r0, ip
	add r3, r0, r1
	mov r0, #0
	mov r1, #2
	str r0, [sp, #4]
	lsl r1, r1, #8
	b _0223F21C
_0223F1F6:
	ldr r0, [sp, #4]
	ldr r5, [sp, #4]
	lsl r4, r0, #1
	ldrh r0, [r3, r4]
	lsl r5, r5, #0x1d
	and r0, r7
	strh r0, [r3, r4]
	ldr r0, [sp, #4]
	ldrh r2, [r3, r4]
	lsr r0, r0, #0x1f
	sub r5, r5, r0
	ror r5, r6
	add r0, r0, r5
	add r0, r0, r1
	orr r0, r2
	strh r0, [r3, r4]
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
_0223F21C:
	ldr r0, [sp, #4]
	cmp r0, #0x20
	blt _0223F1F6
_0223F222:
	ldr r0, [sp]
	mov r1, #2
	ldr r0, [r0]
	ldr r0, [r0, #0x74]
	bl FUN_0201AC68
	ldr r0, [sp]
	ldrb r0, [r0, #0x12]
	add r1, r0, #1
	ldr r0, [sp]
	strb r1, [r0, #0x12]
	ldrb r0, [r0, #0x12]
	cmp r0, #0xc
	blo _0223F280
	ldr r1, [sp]
	mov r0, #0
	mov r2, #0x11
	strb r0, [r1, #0x12]
	ldrsb r1, [r1, r2]
	add r3, r1, #1
	ldr r1, [sp]
	strb r3, [r1, #0x11]
	strb r0, [r1, #0x14]
	add r0, r1, #0
	ldrsb r0, [r0, r2]
	cmp r0, #5
	blo _0223F280
	add r0, r1, #0
	ldrb r0, [r0, #0x10]
	add r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x10]
	pop {r4, r5, r6, r7, pc}
_0223F266:
	add r0, r1, #0
	mov r2, #0
	ldr r0, [r0, #0xc]
	add r1, r1, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	ldr r0, [sp]
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_0223F280:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223F284: .word MOD12_02246404
_0223F288: .word MOD12_0224640C

	thumb_func_start MOD12_0223F28C
MOD12_0223F28C: ; 0x0223F28C
	push {r3, lr}
	lsl r2, r2, #0x10
	mov r3, #0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223F2A0
MOD12_0223F2A0: ; 0x0223F2A0
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x17
	mov r1, #0x14
	add r5, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x14
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _0223F2DC ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, _0223F2E0 ; =MOD12_0223F2E4
	str r6, [r4, #0xc]
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223F2DC: .word 0x00007530
_0223F2E0: .word MOD12_0223F2E4

	thumb_func_start MOD12_0223F2E4
MOD12_0223F2E4: ; 0x0223F2E4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #5
	bhi _0223F388
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223F2FC: ; jump table
	.short _0223F308 - _0223F2FC - 2 ; case 0
	.short _0223F318 - _0223F2FC - 2 ; case 1
	.short _0223F328 - _0223F2FC - 2 ; case 2
	.short _0223F34A - _0223F2FC - 2 ; case 3
	.short _0223F364 - _0223F2FC - 2 ; case 4
	.short _0223F37C - _0223F2FC - 2 ; case 5
_0223F308:
	ldr r0, _0223F3A4 ; =0x0000046F
	mov r1, #0x1e
	bl FUN_02005350
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223F318:
	bl FUN_02005404
	cmp r0, #0
	bne _0223F3A0
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223F328:
	ldr r0, _0223F3A8 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	bl MOD12_0223E738
	ldr r0, [r4]
	mov r1, #1
	add r0, #0x14
	bl MOD12_0223CC9C
	ldr r0, _0223F3AC ; =0x000006EC
	bl FUN_020054C8
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223F34A:
	mov r0, #0x12
	ldrsh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, #0x12]
	ldrsh r0, [r4, r0]
	cmp r0, #0x1e
	ble _0223F3A0
	mov r0, #0
	strh r0, [r4, #0x12]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223F364:
	ldr r0, [r4]
	ldr r1, _0223F3B0 ; =0x00000123
	ldr r2, [r0]
	ldrb r1, [r2, r1]
	add r2, r4, #0
	add r2, #0x11
	bl MOD12_0223E598
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223F37C:
	ldrb r1, [r4, #0x11]
	cmp r1, #1
	bne _0223F3A0
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0223F388:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_0223F3A0:
	pop {r3, r4, r5, pc}
	nop
_0223F3A4: .word 0x0000046F
_0223F3A8: .word 0x04000050
_0223F3AC: .word 0x000006EC
_0223F3B0: .word 0x00000123

	thumb_func_start MOD12_0223F3B4
MOD12_0223F3B4: ; 0x0223F3B4
	push {r3, lr}
	mov r1, #4
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223F3C8
MOD12_0223F3C8: ; 0x0223F3C8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	add r4, r2, #0
	add r2, r3, #0
	ldr r0, _0223F3F8 ; =0x00001BF0
	mov r1, #1
	strb r1, [r5, r0]
	ldr r3, _0223F3FC ; =0x00000172
	mov r1, #0
_0223F3DC:
	ldr r6, [r5]
	ldrb r0, [r2, r1]
	add r6, r6, r1
	add r1, r1, #1
	strb r0, [r6, r3]
	cmp r1, #4
	blt _0223F3DC
	mov r2, #0
	add r0, r7, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD12_02240FB0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223F3F8: .word 0x00001BF0
_0223F3FC: .word 0x00000172

	thumb_func_start MOD12_0223F400
MOD12_0223F400: ; 0x0223F400
	push {r3, lr}
	mov r1, #0x3c
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223F414
MOD12_0223F414: ; 0x0223F414
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r1, #0
	mov r1, #0x57
	add r7, r0, #0
	mov r0, #0x17
	lsl r1, r1, #2
	add r5, r2, #0
	str r3, [sp, #4]
	bl AllocFromHeap
	mov r2, #0x57
	add r4, r0, #0
	mov r1, #0
	lsl r2, r2, #2
	bl MI_CpuFill8
	str r6, [r4]
	ldrh r0, [r5]
	add r3, r4, #0
	add r3, #0x18
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	mov r2, #7
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	ldr r5, [sp, #4]
	strh r0, [r4, #0xa]
	str r7, [r4, #0xc]
_0223F452:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0223F452
	ldr r0, [r5]
	ldr r2, _0223F510 ; =0x00007530
	str r0, [r3]
	ldr r0, _0223F514 ; =MOD12_0223F5CC
	add r1, r4, #0
	str r6, [r4, #0x54]
	bl FUN_0200CA44
	mov r7, #0
	add r5, r4, #0
_0223F46E:
	ldr r1, [r6]
	ldr r0, _0223F518 ; =0x00000127
	ldrb r0, [r1, r0]
	cmp r7, r0
	bge _0223F482
	add r0, r6, #0
	mov r1, #0
	bl MOD12_0223F524
	b _0223F48A
_0223F482:
	add r0, r6, #0
	mov r1, #1
	bl MOD12_0223F524
_0223F48A:
	mov r1, #0x53
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r7, r7, #1
	add r5, r5, #4
	cmp r7, #4
	blt _0223F46E
	ldr r1, [r4]
	ldr r2, _0223F51C ; =0x00000123
	ldr r3, [r1]
	mov r0, #0
	ldrb r3, [r3, r2]
_0223F4A2:
	add r2, r4, r0
	ldrb r2, [r2, #0x1a]
	cmp r3, r2
	bne _0223F4B0
	ldr r2, _0223F520 ; =0x00000ACC
	strb r0, [r1, r2]
	b _0223F4B6
_0223F4B0:
	add r0, r0, #1
	cmp r0, #4
	blt _0223F4A2
_0223F4B6:
	add r0, r6, #0
	bl MOD12_0223FDA0
	ldr r1, [r6]
	ldr r0, _0223F518 ; =0x00000127
	ldrb r5, [r1, r0]
	cmp r5, #4
	bge _0223F50C
	ldr r0, [sp, #4]
	lsl r1, r5, #2
	add r7, r0, r1
	add r1, r4, #0
	mov r0, #0x3c
	add r1, #0x5c
	mul r0, r5
	add r0, r1, r0
	str r0, [sp, #8]
_0223F4D8:
	mov r2, #0
_0223F4DA:
	add r0, r4, r2
	ldrb r0, [r0, #0x1a]
	cmp r5, r0
	beq _0223F4E8
	add r2, r2, #1
	cmp r2, #4
	blt _0223F4DA
_0223F4E8:
	ldr r0, [r6]
	add r1, r0, r5
	mov r0, #0x43
	lsl r0, r0, #2
	ldrb r0, [r1, r0]
	add r1, r5, #0
	str r0, [sp]
	ldr r0, [sp, #8]
	ldr r3, [r7, #0x14]
	bl MOD12_02240774
	ldr r0, [sp, #8]
	add r5, r5, #1
	add r0, #0x3c
	add r7, r7, #4
	str r0, [sp, #8]
	cmp r5, #4
	blt _0223F4D8
_0223F50C:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223F510: .word 0x00007530
_0223F514: .word MOD12_0223F5CC
_0223F518: .word 0x00000127
_0223F51C: .word 0x00000123
_0223F520: .word 0x00000ACC

	thumb_func_start MOD12_0223F524
MOD12_0223F524: ; 0x0223F524
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x17
	mov r1, #0x14
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x14
	add r4, r0, #0
	bl MI_CpuFill8
	str r5, [r4, #4]
	ldr r0, _0223F550 ; =MOD12_0223F588
	ldr r2, _0223F554 ; =0x00007594
	add r1, r4, #0
	strb r6, [r4, #0x12]
	bl FUN_0200CA44
	str r0, [r4]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223F550: .word MOD12_0223F588
_0223F554: .word 0x00007594

	thumb_func_start MOD12_0223F558
MOD12_0223F558: ; 0x0223F558
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_0223F56C
MOD12_0223F56C: ; 0x0223F56C
	ldrh r2, [r1]
	strh r2, [r0, #8]
	ldrh r2, [r1, #2]
	strh r2, [r0, #0xa]
	ldrh r2, [r1, #4]
	strh r2, [r0, #0xc]
	ldrh r2, [r1, #6]
	strh r2, [r0, #0xe]
	ldrh r1, [r1, #8]
	strh r1, [r0, #0x10]
	mov r1, #1
	strb r1, [r0, #0x13]
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0223F588
MOD12_0223F588: ; 0x0223F588
	push {r4, lr}
	add r4, r1, #0
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _0223F5C4
	ldr r0, [r4, #4]
	ldr r1, _0223F5C8 ; =0x00000171
	ldr r2, [r0]
	ldrb r1, [r2, r1]
	cmp r1, #0
	beq _0223F5A4
	ldrb r1, [r4, #0x12]
	cmp r1, #1
	bne _0223F5B2
_0223F5A4:
	add r1, r4, #0
	add r1, #8
	bl MOD12_0223D1CC
	mov r0, #0
	strb r0, [r4, #0x13]
	pop {r4, pc}
_0223F5B2:
	add r1, r4, #0
	mov r0, #0x19
	add r1, #8
	bl FUN_020311D0
	cmp r0, #1
	bne _0223F5C4
	mov r0, #0
	strb r0, [r4, #0x13]
_0223F5C4:
	pop {r4, pc}
	nop
_0223F5C8: .word 0x00000171

	thumb_func_start MOD12_0223F5CC
MOD12_0223F5CC: ; 0x0223F5CC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	add r4, r1, #0
	str r0, [sp, #0x18]
	ldr r0, [r4]
	ldr r1, _0223F920 ; =0x00000123
	ldr r2, [r0]
	ldrb r2, [r2, r1]
	ldrb r1, [r4, #0x18]
	cmp r2, r1
	beq _0223F5E6
	mov r7, #1
	b _0223F5E8
_0223F5E6:
	mov r7, #0
_0223F5E8:
	ldr r1, _0223F924 ; =0x00001138
	ldr r2, [r0, r1]
	add r1, #8
	ldr r1, [r0, r1]
	sub r1, r2, r1
	ldr r2, [r4, #0x24]
	str r1, [sp, #0x20]
	lsr r3, r2, #1
	cmp r1, r3
	blo _0223F602
	mov r1, #1
	str r1, [sp, #0x1c]
	b _0223F606
_0223F602:
	mov r1, #0
	str r1, [sp, #0x1c]
_0223F606:
	ldrb r1, [r4, #0x10]
	cmp r1, #3
	bls _0223F60E
	b _0223FA38
_0223F60E:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223F61A: ; jump table
	.short _0223F622 - _0223F61A - 2 ; case 0
	.short _0223F68A - _0223F61A - 2 ; case 1
	.short _0223F6F4 - _0223F61A - 2 ; case 2
	.short _0223F9C8 - _0223F61A - 2 ; case 3
_0223F622:
	add r0, #0x14
	mov r1, #0
	bl MOD12_0223D068
	ldr r0, [r4]
	bl MOD12_0223DC0C
	add r3, r4, #0
	ldrb r2, [r4, #0x18]
	mov r1, #0x3c
	add r3, #0x5c
	mul r1, r2
	add r1, r3, r1
	ldr r0, [r4]
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x20]
	bl MOD12_022407D4
	mov r0, #0x21
	ldr r1, [r4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl MOD12_0223E448
	ldr r0, [r4]
	mov r1, #0
	bl MOD12_0223E750
	ldr r0, [r4]
	bl MOD12_0223E868
	add r0, r4, #0
	add r0, #0x41
	ldrb r1, [r0]
	add r0, sp, #0x2c
	cmp r7, #0
	strb r1, [r0, #4]
	ldr r0, [r4]
	add r2, sp, #0x2c
	bne _0223F67A
	mov r1, #4
	bl MOD12_0223E488
	b _0223F680
_0223F67A:
	mov r1, #5
	bl MOD12_0223E488
_0223F680:
	ldrb r0, [r4, #0x10]
	add sp, #0x44
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, r6, r7, pc}
_0223F68A:
	ldrb r2, [r4, #0x19]
	add r1, r4, #0
	add r1, #0x3c
	bl MOD12_0223E590
	mov r3, #0
	mov r2, #0
	sub r0, r2, r0
	sbc r3, r1
	bge _0223F6A0
	b _0223FA66
_0223F6A0:
	ldr r0, [r4]
	bl MOD12_0223E528
	ldr r5, [r4]
	add r1, r4, #0
	ldrb r2, [r4, #0x19]
	add r0, r5, #0
	add r1, #0x3c
	bl MOD12_0223E590
	ldr r2, _0223F924 ; =0x00001138
	add r6, r0, #0
	add r0, r1, #0
	add r1, r2, #4
	ldr r3, [r5, r2]
	ldr r1, [r5, r1]
	add r3, r3, r6
	adc r1, r0
	add r0, r2, #0
	add r0, #8
	add r2, #0xc
	str r3, [r5, r0]
	str r1, [r5, r2]
	cmp r7, #0
	bne _0223F6E0
	ldr r0, [r4]
	add r1, r7, #0
	bl MOD12_0223E8B4
	ldrb r0, [r4, #0x11]
	add r0, r0, #1
	strb r0, [r4, #0x11]
_0223F6E0:
	ldrb r1, [r4, #0x18]
	ldr r0, [r4]
	mov r2, #0
	bl MOD12_0223EC88
	ldrb r0, [r4, #0x10]
	add sp, #0x44
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, r6, r7, pc}
_0223F6F4:
	ldr r1, [sp, #0x20]
	add r0, #0x14
	bl MOD12_0223C438
	mov r0, #0x21
	ldr r3, [r4]
	ldr r1, _0223F924 ; =0x00001138
	lsl r0, r0, #4
	ldr r2, [r3, r1]
	add r1, #8
	ldr r1, [r3, r1]
	ldr r0, [r3, r0]
	sub r1, r2, r1
	ldr r2, [r4, #0x24]
	bl MOD12_0223E3DC
	ldr r5, [r4, #0x24]
	ldr r0, [sp, #0x20]
	cmp r0, r5
	blo _0223F7DC
	ldrb r0, [r4, #0x16]
	ldr r1, _0223F924 ; =0x00001138
	add r0, r0, #1
	strb r0, [r4, #0x16]
	ldr r5, [r4]
	add r0, r5, r1
	ldmia r0!, {r2, r3}
	add r1, #8
	add r0, r5, r1
	stmia r0!, {r2, r3}
	mov r0, #0
	strb r0, [r4, #0x11]
	strb r0, [r4, #0x12]
	ldr r0, [r4]
	bl MOD12_0223FDA0
	mov r0, #0
	strb r0, [r4, #0x17]
	ldr r0, [r4]
	ldr r1, [r0]
	ldr r0, _0223F928 ; =0x00000127
	ldrb r6, [r1, r0]
	cmp r6, #4
	bge _0223F764
	add r1, r4, #0
	mov r0, #0x3c
	add r1, #0x5c
	mul r0, r6
	add r5, r1, r0
_0223F756:
	add r0, r5, #0
	bl MOD12_0224079C
	add r6, r6, #1
	add r5, #0x3c
	cmp r6, #4
	blt _0223F756
_0223F764:
	ldr r0, [r4]
	add r0, #0x14
	bl MOD12_0223C640
	ldr r0, [r4]
	bl MOD12_0223DC0C
	add r3, r4, #0
	ldrb r2, [r4, #0x18]
	mov r1, #0x3c
	add r3, #0x5c
	mul r1, r2
	add r1, r3, r1
	ldr r0, [r4]
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x20]
	bl MOD12_022407D4
	ldr r0, [r4]
	mov r1, #0
	bl MOD12_0223E750
	add r0, r4, #0
	add r0, #0x40
	ldrb r1, [r4, #0x16]
	ldrb r0, [r0]
	cmp r1, r0
	ldr r0, [r4]
	blo _0223F7B6
	bl MOD12_0223ECD0
	ldr r0, [r4]
	mov r1, #2
	add r0, #0x14
	bl MOD12_0223D068
	ldrb r0, [r4, #0x10]
	add sp, #0x44
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, r6, r7, pc}
_0223F7B6:
	ldrb r1, [r4, #0x18]
	mov r2, #0
	bl MOD12_0223EC88
	cmp r7, #0
	bne _0223F7C8
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	beq _0223F7CA
_0223F7C8:
	b _0223FA66
_0223F7CA:
	ldr r0, [r4]
	add r1, r7, #0
	bl MOD12_0223E8B4
	ldrb r0, [r4, #0x11]
	add sp, #0x44
	add r0, r0, #1
	strb r0, [r4, #0x11]
	pop {r4, r5, r6, r7, pc}
_0223F7DC:
	ldr r1, [r4]
	ldr r0, _0223F92C ; =0x00000ACC
	ldrb r6, [r1, r0]
	ldr r0, [sp, #0x20]
	lsr r1, r5, #1
	cmp r0, r1
	blo _0223F7EE
	mov r0, #1
	b _0223F7F0
_0223F7EE:
	mov r0, #0
_0223F7F0:
	cmp r7, #0
	bne _0223F88C
	cmp r0, #0
	bne _0223F828
	add r0, r4, #0
	add r0, #0x41
	ldrb r1, [r4, #0x17]
	ldrb r0, [r0]
	cmp r1, r0
	bhs _0223F828
	ldr r0, [r4, #0x20]
	ldr r1, _0223F930 ; =0x00002710
	lsr r0, r0, #2
	bl _u32_div_f
	lsr r1, r5, #1
	sub r1, r1, r0
	ldr r0, [sp, #0x20]
	cmp r0, r1
	bhs _0223F828
	add r0, r4, #0
	mov r2, #0
	add r0, #0x54
	add r1, sp, #0x34
	add r3, r2, #0
	bl MOD12_0223FA74
	b _0223F836
_0223F828:
	add r0, r4, #0
	mov r2, #1
	add r0, #0x54
	add r1, sp, #0x34
	add r3, r2, #0
	bl MOD12_0223FA74
_0223F836:
	mov r0, #0
	ldr r1, [sp, #0x34]
	mvn r0, r0
	cmp r1, r0
	bne _0223F842
	b _0223F94E
_0223F842:
	add r0, r4, #0
	add r0, #0x44
	str r0, [sp]
	add r0, sp, #0x38
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r6, [sp, #0xc]
	ldrb r0, [r4, #0x17]
	str r0, [sp, #0x10]
	add r0, r4, #0
	add r0, #0x41
	ldrb r0, [r0]
	str r0, [sp, #0x14]
	ldr r0, [r4]
	ldr r3, [r4, #0x20]
	ldr r2, [r0]
	ldr r0, _0223F920 ; =0x00000123
	ldrb r0, [r2, r0]
	ldr r2, [sp, #0x20]
	bl MOD12_0223FCAC
	ldr r0, [r4]
	ldr r1, [r0]
	ldr r0, _0223F920 ; =0x00000123
	ldrb r1, [r1, r0]
	add r0, #0x29
	lsl r1, r1, #2
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, sp, #0x38
	bl MOD12_0223F56C
	ldrb r0, [r4, #0x17]
	add r0, r0, #1
	strb r0, [r4, #0x17]
	b _0223F94E
_0223F88C:
	cmp r0, #1
	bne _0223F8D2
	add r0, r4, #0
	add r0, #0x41
	ldrb r1, [r4, #0x17]
	ldrb r0, [r0]
	cmp r1, r0
	bhs _0223F8D2
	ldr r0, [r4, #0x20]
	ldr r1, _0223F930 ; =0x00002710
	lsr r0, r0, #2
	bl _u32_div_f
	sub r1, r5, r0
	ldr r0, [sp, #0x20]
	cmp r0, r1
	bhs _0223F8D2
	add r0, r4, #0
	mov r2, #0
	add r0, #0x54
	add r1, sp, #0x34
	add r3, r2, #0
	bl MOD12_0223FA74
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _0223F8E0
	ldr r0, [r4]
	add r1, r7, #0
	bl MOD12_0223E8B4
	ldrb r0, [r4, #0x11]
	add r0, r0, #1
	strb r0, [r4, #0x11]
	b _0223F8E0
_0223F8D2:
	add r0, r4, #0
	mov r2, #1
	add r0, #0x54
	add r1, sp, #0x34
	add r3, r2, #0
	bl MOD12_0223FA74
_0223F8E0:
	mov r0, #0
	ldr r1, [sp, #0x34]
	mvn r0, r0
	cmp r1, r0
	beq _0223F94E
	add r2, r4, #0
	ldr r0, [r4]
	add r2, #0x44
	str r2, [sp]
	add r2, sp, #0x38
	str r2, [sp, #4]
	ldr r2, _0223F934 ; =0x00001B98
	add r2, r0, r2
	str r2, [sp, #8]
	str r6, [sp, #0xc]
	ldrb r2, [r4, #0x17]
	str r2, [sp, #0x10]
	add r2, r4, #0
	add r2, #0x41
	ldrb r2, [r2]
	str r2, [sp, #0x14]
	ldr r2, [r0]
	ldr r0, _0223F920 ; =0x00000123
	ldr r3, [r4, #0x20]
	ldrb r0, [r2, r0]
	ldr r2, [sp, #0x20]
	bl MOD12_0223FCAC
	ldr r0, [r4]
	ldr r1, [r0]
	ldr r0, _0223F920 ; =0x00000123
	b _0223F938
	.align 2, 0
_0223F920: .word 0x00000123
_0223F924: .word 0x00001138
_0223F928: .word 0x00000127
_0223F92C: .word 0x00000ACC
_0223F930: .word 0x00002710
_0223F934: .word 0x00001B98
_0223F938:
	ldrb r1, [r1, r0]
	add r0, #0x29
	lsl r1, r1, #2
	add r1, r4, r1
	ldr r0, [r1, r0]
	add r1, sp, #0x38
	bl MOD12_0223F56C
	ldrb r0, [r4, #0x17]
	add r0, r0, #1
	strb r0, [r4, #0x17]
_0223F94E:
	ldr r0, [r4]
	ldr r1, [r0]
	ldr r0, _0223FA6C ; =0x00000127
	ldrb r7, [r1, r0]
	cmp r7, #4
	bge _0223F99A
	lsl r0, r7, #2
	add r5, r4, r0
	add r1, r4, #0
	mov r0, #0x3c
	add r1, #0x5c
	mul r0, r7
	add r6, r1, r0
	add r0, r4, #0
	str r0, [sp, #0x28]
	add r0, #0x3c
	str r0, [sp, #0x28]
_0223F970:
	ldr r0, [r4, #0x24]
	ldr r3, [sp, #0x20]
	str r0, [sp]
	ldr r0, [r4, #0x20]
	add r2, r6, #0
	str r0, [sp, #4]
	ldr r0, [sp, #0x28]
	str r0, [sp, #8]
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x1c]
	ldr r1, [r4]
	bl MOD12_02240B08
	add r7, r7, #1
	add r5, r5, #4
	add r6, #0x3c
	cmp r7, #4
	blt _0223F970
_0223F99A:
	ldr r0, [sp, #0x1c]
	cmp r0, #1
	bne _0223F9B6
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _0223F9B6
	ldrb r1, [r4, #0x18]
	ldr r0, [r4]
	mov r2, #1
	bl MOD12_0223EC88
	ldrb r0, [r4, #0x12]
	add r0, r0, #1
	strb r0, [r4, #0x12]
_0223F9B6:
	ldr r0, [sp, #0x1c]
	cmp r0, #1
	bne _0223FA66
	ldr r0, [r4]
	ldr r1, [sp, #0x20]
	bl MOD12_0223E7D4
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
_0223F9C8:
	add r0, r4, #0
	add r0, #0x54
	add r1, sp, #0x34
	mov r2, #1
	mov r3, #0
	bl MOD12_0223FA74
	cmp r0, #1
	bne _0223FA66
	ldr r0, [r4]
	add r0, #0x14
	bl MOD12_0223C640
	ldr r0, [r4]
	ldr r2, [r4, #0x24]
	add r0, #0x14
	mov r1, #0
	bl MOD12_0223C438
	mov r0, #0x21
	ldr r1, [r4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl MOD12_0223E43C
	ldr r0, [r4]
	mov r1, #2
	add r0, #0x14
	bl MOD12_0223D068
	ldr r0, [r4]
	mov r1, #0
	bl MOD12_0223E750
	ldr r0, [r4]
	bl MOD12_0223E898
	ldr r1, [r4]
	ldr r0, _0223FA70 ; =0x00001130
	ldr r0, [r1, r0]
	bl MOD12_0223B92C
	cmp r0, #0
	beq _0223FA2E
	ldr r1, [r4]
	ldr r0, _0223FA70 ; =0x00001130
	mov r2, #6
	ldr r0, [r1, r0]
	mov r1, #0
	bl MOD12_0223C1F4
_0223FA2E:
	ldrb r0, [r4, #0x10]
	add sp, #0x44
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, r6, r7, pc}
_0223FA38:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	mov r7, #0x53
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #2
_0223FA4C:
	ldr r0, [r5, r7]
	bl MOD12_0223F558
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #4
	blt _0223FA4C
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [sp, #0x18]
	bl FUN_0200CAB4
_0223FA66:
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	nop
_0223FA6C: .word 0x00000127
_0223FA70: .word 0x00001130

	thumb_func_start MOD12_0223FA74
MOD12_0223FA74: ; 0x0223FA74
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	add r5, r0, #0
	add r7, r1, #0
	sub r0, r4, #1
	add r6, r2, #0
	str r3, [sp]
	str r0, [r7]
	cmp r6, #0
	bne _0223FAA6
	ldrb r0, [r5, #5]
	cmp r0, #0
	beq _0223FAA6
	sub r0, r0, #1
	strb r0, [r5, #5]
	ldrb r0, [r5, #5]
	cmp r0, #0
	bne _0223FAA6
	ldr r1, [r5]
	ldr r0, _0223FB74 ; =0x00001130
	add r2, r4, #0
	ldr r0, [r1, r0]
	add r1, r4, #0
	bl MOD12_0223C1F4
_0223FAA6:
	ldrb r0, [r5, #4]
	cmp r0, #0
	beq _0223FAB6
	cmp r0, #1
	beq _0223FADC
	cmp r0, #2
	beq _0223FB1E
	b _0223FB44
_0223FAB6:
	cmp r6, #0
	bne _0223FAD8
	ldr r0, [sp]
	cmp r0, #0
	bne _0223FAD8
	mov r1, #0
	strb r1, [r5, #5]
	ldr r2, [r5]
	ldr r0, _0223FB74 ; =0x00001130
	ldr r0, [r2, r0]
	add r2, r1, #0
	bl MOD12_0223C1F4
	ldrb r0, [r5, #4]
	add r0, r0, #1
	strb r0, [r5, #4]
	b _0223FB44
_0223FAD8:
	mov r4, #1
	b _0223FB44
_0223FADC:
	cmp r6, #1
	beq _0223FAE6
	ldrb r0, [r5, #5]
	cmp r0, #0
	beq _0223FAEA
_0223FAE6:
	mov r4, #1
	b _0223FB44
_0223FAEA:
	ldr r1, [r5]
	ldr r0, _0223FB74 ; =0x00001130
	ldr r0, [r1, r0]
	bl MOD12_0223B878
	mov r1, #0
	mvn r1, r1
	str r0, [r7]
	cmp r0, r1
	beq _0223FB1A
	ldr r1, [r5]
	ldr r0, _0223FB78 ; =0x00000AE8
	ldr r0, [r1, r0]
	ldr r1, _0223FB7C ; =0x00002710
	bl _u32_div_f
	strb r0, [r5, #5]
	ldrb r0, [r5, #5]
	sub r0, r0, #2
	strb r0, [r5, #5]
	ldrb r0, [r5, #4]
	add r0, r0, #1
	strb r0, [r5, #4]
	b _0223FB44
_0223FB1A:
	mov r4, #1
	b _0223FB44
_0223FB1E:
	ldr r1, [r5]
	ldr r0, _0223FB74 ; =0x00001130
	ldr r0, [r1, r0]
	bl MOD12_0223B91C
	cmp r0, #1
	bne _0223FB44
	ldrb r0, [r5, #5]
	cmp r0, #0
	beq _0223FB40
	ldr r1, [r5]
	ldr r0, _0223FB74 ; =0x00001130
	mov r2, #6
	ldr r0, [r1, r0]
	mov r1, #0
	bl MOD12_0223C1F4
_0223FB40:
	mov r0, #1
	strb r0, [r5, #4]
_0223FB44:
	ldr r0, [sp]
	cmp r0, #1
	bne _0223FB6E
	cmp r4, #1
	bne _0223FB6E
	ldr r1, [r5]
	ldr r0, _0223FB74 ; =0x00001130
	ldr r0, [r1, r0]
	bl MOD12_0223B92C
	cmp r0, #0
	beq _0223FB6E
	ldr r1, [r5]
	ldr r0, _0223FB74 ; =0x00001130
	mov r2, #6
	ldr r0, [r1, r0]
	mov r1, #0
	bl MOD12_0223C1F4
	mov r0, #0
	strb r0, [r5, #4]
_0223FB6E:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223FB74: .word 0x00001130
_0223FB78: .word 0x00000AE8
_0223FB7C: .word 0x00002710

	thumb_func_start MOD12_0223FB80
MOD12_0223FB80: ; 0x0223FB80
	push {r3, lr}
	cmp r0, #3
	bhi _0223FBAA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223FB92: ; jump table
	.short _0223FB9A - _0223FB92 - 2 ; case 0
	.short _0223FB9E - _0223FB92 - 2 ; case 1
	.short _0223FBA2 - _0223FB92 - 2 ; case 2
	.short _0223FBA6 - _0223FB92 - 2 ; case 3
_0223FB9A:
	mov r0, #1
	pop {r3, pc}
_0223FB9E:
	mov r0, #2
	pop {r3, pc}
_0223FBA2:
	mov r0, #3
	pop {r3, pc}
_0223FBA6:
	mov r0, #4
	pop {r3, pc}
_0223FBAA:
	bl ErrorHandling
	mov r0, #0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223FBB4
MOD12_0223FBB4: ; 0x0223FBB4
	push {r3, lr}
	cmp r0, #4
	bhi _0223FBE0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223FBC6: ; jump table
	.short _0223FBE0 - _0223FBC6 - 2 ; case 0
	.short _0223FBD0 - _0223FBC6 - 2 ; case 1
	.short _0223FBD4 - _0223FBC6 - 2 ; case 2
	.short _0223FBD8 - _0223FBC6 - 2 ; case 3
	.short _0223FBDC - _0223FBC6 - 2 ; case 4
_0223FBD0:
	mov r0, #0
	pop {r3, pc}
_0223FBD4:
	mov r0, #1
	pop {r3, pc}
_0223FBD8:
	mov r0, #2
	pop {r3, pc}
_0223FBDC:
	mov r0, #3
	pop {r3, pc}
_0223FBE0:
	bl ErrorHandling
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD12_0223FBE8
MOD12_0223FBE8: ; 0x0223FBE8
	push {r3, r4}
	ldrb r4, [r1]
	cmp r0, r4
	bgt _0223FBFA
	mov r0, #0
	strb r0, [r2]
	strb r0, [r3]
	pop {r3, r4}
	bx lr
_0223FBFA:
	ldrb r4, [r1, #1]
	cmp r0, r4
	bgt _0223FC0C
	mov r0, #0
	strb r0, [r2]
	mov r0, #1
	strb r0, [r3]
	pop {r3, r4}
	bx lr
_0223FC0C:
	ldrb r4, [r1, #2]
	cmp r0, r4
	bgt _0223FC1E
	mov r0, #1
	strb r0, [r2]
	mov r0, #2
	strb r0, [r3]
	pop {r3, r4}
	bx lr
_0223FC1E:
	ldrb r1, [r1, #3]
	cmp r0, r1
	bgt _0223FC30
	mov r0, #1
	strb r0, [r2]
	mov r0, #3
	strb r0, [r3]
	pop {r3, r4}
	bx lr
_0223FC30:
	mov r0, #2
	strb r0, [r2]
	mov r0, #4
	strb r0, [r3]
	pop {r3, r4}
	bx lr

	thumb_func_start MOD12_0223FC3C
MOD12_0223FC3C: ; 0x0223FC3C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r2, #0
	add r6, r0, #0
	mov r0, #0
	ldr r2, _0223FCA4 ; =0x00002710
	str r3, [sp]
	mul r6, r2
	lsr r1, r1, #1
	add r5, r0, #0
	add r4, r0, #0
	cmp r6, #0
	bls _0223FC62
	bls _0223FC60
_0223FC58:
	add r4, r4, r1
	add r5, r5, #1
	cmp r4, r6
	blo _0223FC58
_0223FC60:
	sub r0, r4, r1
_0223FC62:
	ldr r1, _0223FCA8 ; =0x00001388
	add r0, r0, r1
	lsl r1, r1, #1
	bl _u32_div_f
	ldr r1, _0223FCA8 ; =0x00001388
	str r0, [sp, #4]
	add r0, r4, r1
	lsl r1, r1, #1
	bl _u32_div_f
	add r4, r0, #0
	ldr r1, _0223FCA4 ; =0x00002710
	add r0, r6, #0
	bl _u32_div_f
	ldr r1, [sp, #4]
	sub r1, r0, r1
	bpl _0223FC8A
	neg r1, r1
_0223FC8A:
	sub r0, r0, r4
	bpl _0223FC90
	neg r0, r0
_0223FC90:
	cmp r1, r0
	bhi _0223FC98
	sub r5, r5, #1
	b _0223FC9A
_0223FC98:
	add r1, r0, #0
_0223FC9A:
	ldr r0, [sp]
	str r1, [r7]
	str r5, [r0]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223FCA4: .word 0x00002710
_0223FCA8: .word 0x00001388

	thumb_func_start MOD12_0223FCAC
MOD12_0223FCAC: ; 0x0223FCAC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	str r0, [sp]
	str r2, [sp, #4]
	str r3, [sp, #8]
	add r0, r1, #0
	ldr r5, [sp, #0x34]
	ldr r6, [sp, #0x38]
	mov r7, #0
	bl MOD12_0223FB80
	str r0, [sp, #0xc]
	ldr r0, [sp, #4]
	ldr r1, [sp, #8]
	add r2, sp, #0x18
	add r3, sp, #0x14
	bl MOD12_0223FC3C
	cmp r6, #0
	beq _0223FD00
	ldr r0, [sp, #0x14]
	add r4, r7, #0
	sub r0, #0x10
	add r1, r6, #0
	add r2, r6, #0
_0223FCDE:
	ldrb r3, [r1, #8]
	lsl r3, r3, #0x1d
	lsr r3, r3, #0x1f
	cmp r3, #1
	bne _0223FCEE
	ldrb r3, [r2, #6]
	cmp r0, r3
	beq _0223FCF8
_0223FCEE:
	add r4, r4, #1
	add r1, #0xa
	add r2, #0xa
	cmp r4, #8
	blo _0223FCDE
_0223FCF8:
	cmp r4, #8
	bne _0223FD00
	mov r0, #0xff
	str r0, [sp, #0x18]
_0223FD00:
	add r2, sp, #0x10
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x30]
	add r2, #1
	add r3, sp, #0x10
	bl MOD12_0223FBE8
	cmp r6, #0
	beq _0223FD40
	cmp r4, #8
	beq _0223FD40
	add r0, sp, #0x10
	ldrb r0, [r0, #1]
	cmp r0, #0
	beq _0223FD22
	cmp r0, #1
	bne _0223FD40
_0223FD22:
	mov r0, #0xa
	mul r0, r4
	add r0, r6, r0
	ldrb r1, [r0, #3]
	ldr r0, [sp, #0xc]
	cmp r0, r1
	beq _0223FD40
	mov r0, #0xff
	str r0, [sp, #0x18]
	mov r1, #4
	add r0, sp, #0x10
	strb r1, [r0]
	mov r1, #2
	strb r1, [r0, #1]
	mov r7, #1
_0223FD40:
	ldr r0, [sp]
	strb r0, [r5, #2]
	ldr r0, [sp, #4]
	strh r0, [r5]
	ldr r0, [sp, #0xc]
	strb r0, [r5, #3]
	add r0, sp, #0x10
	ldrb r1, [r0, #1]
	strb r1, [r5, #4]
	ldrb r0, [r0]
	ldr r1, [sp, #0x40]
	strb r0, [r5, #5]
	ldr r0, [sp, #0x14]
	strb r0, [r5, #6]
	ldr r0, [sp, #0x3c]
	strb r0, [r5, #7]
	ldr r0, [sp, #0x44]
	sub r0, r0, #1
	cmp r1, r0
	blt _0223FD6C
	mov r1, #1
	b _0223FD6E
_0223FD6C:
	mov r1, #0
_0223FD6E:
	ldrb r2, [r5, #8]
	mov r0, #1
	bic r2, r0
	lsl r0, r1, #0x18
	lsr r1, r0, #0x18
	mov r0, #1
	and r0, r1
	orr r0, r2
	strb r0, [r5, #8]
	ldrb r1, [r5, #8]
	mov r0, #2
	bic r1, r0
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1e
	orr r0, r1
	strb r0, [r5, #8]
	ldrb r1, [r5, #8]
	mov r0, #4
	orr r0, r1
	strb r0, [r5, #8]
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_0223FDA0
MOD12_0223FDA0: ; 0x0223FDA0
	push {r4, r5}
	ldr r1, _0223FDC8 ; =0x00000ABD
	mov r5, #0
	add r3, r5, #0
	add r2, r1, #4
_0223FDAA:
	add r4, r0, r5
	strb r3, [r4, r1]
	add r5, r5, #1
	strb r3, [r4, r2]
	cmp r5, #4
	blt _0223FDAA
	ldr r1, _0223FDCC ; =0x00000AC5
	strb r3, [r0, r1]
	add r2, r1, #1
	strb r3, [r0, r2]
	add r1, r1, #2
	strb r3, [r0, r1]
	pop {r4, r5}
	bx lr
	nop
_0223FDC8: .word 0x00000ABD
_0223FDCC: .word 0x00000AC5

	thumb_func_start MOD12_0223FDD0
MOD12_0223FDD0: ; 0x0223FDD0
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0223FDD4
MOD12_0223FDD4: ; 0x0223FDD4
	push {r3, lr}
	mov r1, #0x3c
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0223FDE8
MOD12_0223FDE8: ; 0x0223FDE8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r0, #0x17
	str r1, [sp]
	add r1, r0, #0
	add r1, #0xed
	add r5, r2, #0
	add r6, r3, #0
	bl AllocFromHeap
	mov r2, #0x41
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp]
	add r3, r4, #0
	str r0, [r4]
	ldrh r0, [r5]
	add r3, #0xc8
	mov r2, #7
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	str r7, [r4, #0xc]
_0223FE24:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0223FE24
	ldr r0, [r6]
	ldr r2, _0223FE3C ; =0x00007530
	str r0, [r3]
	ldr r0, _0223FE40 ; =MOD12_0223FE44
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223FE3C: .word 0x00007530
_0223FE40: .word MOD12_0223FE44

	thumb_func_start MOD12_0223FE44
MOD12_0223FE44: ; 0x0223FE44
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #5
	bls _0223FE54
	b _02240002
_0223FE54:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223FE60: ; jump table
	.short _0223FE6C - _0223FE60 - 2 ; case 0
	.short _0223FEBC - _0223FE60 - 2 ; case 1
	.short _0223FEEA - _0223FE60 - 2 ; case 2
	.short _0223FF9C - _0223FE60 - 2 ; case 3
	.short _0223FFBE - _0223FE60 - 2 ; case 4
	.short _0223FFE2 - _0223FE60 - 2 ; case 5
_0223FE6C:
	ldr r0, [r4]
	mov r1, #0
	bl MOD12_0223EC7C
	mov r1, #0
	str r1, [sp]
	mov r0, #6
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldr r0, [r4]
	mov r1, #1
	add r0, #0xa4
	ldr r0, [r0]
	ldr r2, _02240020 ; =0x00001FE3
	sub r3, r1, #3
	bl FUN_02003210
	add r6, r4, #0
	mov r5, #0
	mov r7, #0x10
	add r6, #0x11
_0223FE96:
	str r7, [sp]
	mov r0, #4
	str r0, [sp, #4]
	add r0, r6, r5
	str r0, [sp, #8]
	ldr r0, [r4]
	ldr r2, _02240024 ; =0x00007FFF
	ldr r3, _02240028 ; =0x0000254A
	add r1, r5, #0
	bl MOD12_0223EDAC
	add r5, r5, #1
	cmp r5, #4
	blt _0223FE96
	ldrb r0, [r4, #0x10]
	add sp, #0x18
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0223FEBC:
	ldr r0, [r4]
	add r0, #0xa4
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	bne _0223FEDE
	mov r1, #0
_0223FECC:
	add r0, r4, r1
	ldrb r0, [r0, #0x11]
	cmp r0, #0
	beq _0223FEDA
	add r1, r1, #1
	cmp r1, #4
	blt _0223FECC
_0223FEDA:
	cmp r1, #4
	beq _0223FEE0
_0223FEDE:
	b _0224001A
_0223FEE0:
	ldrb r0, [r4, #0x10]
	add sp, #0x18
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0223FEEA:
	add r0, r4, #0
	str r0, [sp, #0xc]
	add r0, #0x18
	mov r6, #0
	str r0, [sp, #0xc]
_0223FEF4:
	add r0, r4, r6
	add r0, #0xca
	ldrb r1, [r0]
	mov r2, #0x2c
	add r7, r1, #0
	mul r7, r2
	ldr r2, [r4]
	lsl r0, r1, #2
	ldr r2, [r2, #0x14]
	add r5, r4, r7
	ldr r2, [r2, r0]
	str r2, [r5, #0x18]
	ldr r2, [r4]
	add r0, r2, r0
	ldr r0, [r0, #0x5c]
	str r0, [r5, #0x1c]
	ldr r2, [r4]
	lsl r0, r1, #4
	add r2, #0x18
	add r0, r2, r0
	str r0, [r5, #0x20]
	ldr r1, [r4]
	ldr r0, _0224002C ; =0x00000AF4
	ldr r0, [r1, r0]
	ldr r1, _02240030 ; =0x00002710
	bl _u32_div_f
	mov r1, #0x28
	mul r1, r0
	add r0, r1, #0
	mov r1, #0x64
	bl _u32_div_f
	strh r0, [r5, #0x26]
	add r0, r5, #0
	add r0, #0x24
	strb r6, [r0]
	cmp r6, #0
	bne _0223FF48
	add r5, #0x25
	mov r0, #3
	b _0223FF4C
_0223FF48:
	sub r0, r6, #1
	add r5, #0x25
_0223FF4C:
	ldr r1, [sp, #0xc]
	strb r0, [r5]
	ldr r0, _02240034 ; =MOD12_02240044
	ldr r2, _02240038 ; =0x00009CA4
	add r1, r1, r7
	bl FUN_0200CA44
	add r6, r6, #1
	cmp r6, #4
	blt _0223FEF4
	add r0, r4, #0
	add r0, #0xf1
	ldrb r1, [r0]
	add r0, sp, #0x10
	strb r1, [r0, #4]
	ldr r0, [r4]
	add r1, r4, #0
	add r1, #0xcb
	ldrb r3, [r1]
	ldr r2, [r0]
	ldr r1, _0224003C ; =0x00000123
	ldrb r1, [r2, r1]
	cmp r3, r1
	add r2, sp, #0x10
	bne _0223FF86
	mov r1, #4
	bl MOD12_0223E488
	b _0223FF8C
_0223FF86:
	mov r1, #5
	bl MOD12_0223E488
_0223FF8C:
	ldr r0, _02240040 ; =0x000006F7
	bl FUN_020054C8
	ldrb r0, [r4, #0x10]
	add sp, #0x18
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0223FF9C:
	mov r2, #0
_0223FF9E:
	add r0, r1, #0
	add r0, #0x43
	ldrb r0, [r0]
	cmp r0, #0
	beq _0223FFB0
	add r2, r2, #1
	add r1, #0x2c
	cmp r2, #4
	blt _0223FF9E
_0223FFB0:
	cmp r2, #4
	bne _0224001A
	ldrb r0, [r4, #0x10]
	add sp, #0x18
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0223FFBE:
	mov r0, #6
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #1
	add r0, #0xa4
	ldr r0, [r0]
	ldr r2, _02240020 ; =0x00001FE3
	sub r3, r1, #3
	bl FUN_02003210
	ldrb r0, [r4, #0x10]
	add sp, #0x18
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0223FFE2:
	ldr r0, [r4]
	add r0, #0xa4
	ldr r0, [r0]
	bl FUN_020038E4
	cmp r0, #0
	bne _0224001A
	ldr r0, [r4]
	mov r1, #1
	bl MOD12_0223EC7C
	ldrb r0, [r4, #0x10]
	add sp, #0x18
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_02240002:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_0224001A:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02240020: .word 0x00001FE3
_02240024: .word 0x00007FFF
_02240028: .word 0x0000254A
_0224002C: .word 0x00000AF4
_02240030: .word 0x00002710
_02240034: .word MOD12_02240044
_02240038: .word 0x00009CA4
_0224003C: .word 0x00000123
_02240040: .word 0x000006F7

	thumb_func_start MOD12_02240044
MOD12_02240044: ; 0x02240044
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r1, #0x2a
	ldrb r1, [r1]
	cmp r1, #0
	beq _02240058
	cmp r1, #1
	beq _02240114
	b _0224025E
_02240058:
	ldr r0, [r5, #8]
	ldr r0, [r0, #4]
	lsl r0, r0, #8
	str r0, [r5, #0x10]
	ldr r0, [r5, #8]
	ldr r0, [r0, #8]
	lsl r0, r0, #8
	str r0, [r5, #0x14]
	ldr r0, [r5, #8]
	ldr r0, [r0, #0xc]
	lsl r0, r0, #8
	str r0, [r5, #0x18]
	ldrb r0, [r5, #0xc]
	bl MOD12_0223C210
	lsl r4, r0, #8
	ldrb r0, [r5, #0xc]
	bl MOD12_0223C220
	lsl r0, r0, #8
	str r0, [sp, #8]
	ldrb r0, [r5, #0xc]
	bl MOD12_0223C234
	lsl r0, r0, #8
	str r0, [sp, #4]
	ldrb r0, [r5, #0xd]
	cmp r0, #0
	beq _02240096
	cmp r0, #3
	bne _022400C8
_02240096:
	cmp r0, #0
	bne _0224009E
	ldr r0, _0224026C ; =0xFFFFB000
	b _022400A2
_0224009E:
	mov r0, #0x59
	lsl r0, r0, #0xa
_022400A2:
	ldrh r1, [r5, #0xe]
	sub r0, r0, r4
	lsr r1, r1, #1
	bl _s32_div_f
	str r0, [r5, #0x1c]
	ldrh r1, [r5, #0xe]
	mov r0, #0
	lsr r1, r1, #1
	bl _s32_div_f
	str r0, [r5, #0x20]
	ldrh r1, [r5, #0xe]
	mov r0, #0
	lsr r1, r1, #1
	bl _s32_div_f
	str r0, [r5, #0x24]
	b _02240104
_022400C8:
	bl MOD12_0223C210
	lsl r6, r0, #8
	ldrb r0, [r5, #0xd]
	bl MOD12_0223C220
	lsl r0, r0, #8
	str r0, [sp]
	ldrb r0, [r5, #0xd]
	bl MOD12_0223C234
	lsl r7, r0, #8
	ldrh r1, [r5, #0xe]
	sub r0, r6, r4
	bl _s32_div_f
	str r0, [r5, #0x1c]
	ldr r1, [sp]
	ldr r0, [sp, #8]
	sub r0, r1, r0
	ldrh r1, [r5, #0xe]
	bl _s32_div_f
	str r0, [r5, #0x20]
	ldr r0, [sp, #4]
	ldrh r1, [r5, #0xe]
	sub r0, r7, r0
	bl _s32_div_f
	str r0, [r5, #0x24]
_02240104:
	add r0, r5, #0
	add r0, #0x2a
	ldrb r0, [r0]
	add r5, #0x2a
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r5]
	pop {r4, r5, r6, r7, pc}
_02240114:
	ldr r1, [r5, #0x10]
	ldr r0, [r5, #0x1c]
	add r0, r1, r0
	str r0, [r5, #0x10]
	ldr r1, [r5, #0x14]
	ldr r0, [r5, #0x20]
	add r0, r1, r0
	str r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	ldr r0, [r5, #0x24]
	add r0, r1, r0
	str r0, [r5, #0x18]
	ldrh r0, [r5, #0x28]
	add r0, r0, #1
	strh r0, [r5, #0x28]
	ldrb r0, [r5, #0xd]
	cmp r0, #0
	beq _0224013C
	cmp r0, #3
	bne _022401DC
_0224013C:
	ldrh r1, [r5, #0xe]
	ldrh r2, [r5, #0x28]
	lsr r1, r1, #1
	cmp r2, r1
	bne _022401DC
	cmp r0, #0
	bne _02240164
	ldr r0, _02240270 ; =0xFFFF9C00
	mov r1, #1
	str r0, [r5, #0x10]
	ldr r0, [r5, #8]
	ldr r0, [r0]
	bl MOD17_021DD59C
	ldr r0, [r5, #8]
	mov r1, #0x64
	ldr r0, [r0]
	bl MOD17_021DD6CC
	b _02240184
_02240164:
	bl MOD12_0223C210
	add r0, #0x50
	lsl r0, r0, #8
	str r0, [r5, #0x10]
	ldr r0, [r5, #8]
	mov r1, #0
	ldr r0, [r0]
	bl MOD17_021DD59C
	ldr r0, [r5, #8]
	mov r1, #0x63
	ldr r0, [r0]
	mvn r1, r1
	bl MOD17_021DD6CC
_02240184:
	ldr r0, [r5]
	mov r1, #2
	bl FUN_02068E14
	add r4, r0, #0
	ldrb r0, [r5, #0xd]
	bl MOD12_0223C220
	add r0, r4, r0
	lsl r0, r0, #8
	str r0, [r5, #0x14]
	ldrb r0, [r5, #0xd]
	bl MOD12_0223C234
	lsl r0, r0, #8
	str r0, [r5, #0x18]
	ldrb r0, [r5, #0xd]
	bl MOD12_0223C210
	ldrh r2, [r5, #0xe]
	ldrh r1, [r5, #0x28]
	lsl r0, r0, #8
	ldr r7, [r5, #0x14]
	sub r1, r2, r1
	sub r4, r1, #1
	ldr r1, [r5, #0x10]
	ldr r6, [r5, #0x18]
	sub r0, r0, r1
	add r1, r4, #0
	bl _s32_div_f
	str r0, [r5, #0x1c]
	ldr r0, [r5, #0x14]
	add r1, r4, #0
	sub r0, r7, r0
	bl _s32_div_f
	str r0, [r5, #0x20]
	ldr r0, [r5, #0x18]
	add r1, r4, #0
	sub r0, r6, r0
	bl _s32_div_f
	str r0, [r5, #0x24]
_022401DC:
	ldrh r1, [r5, #0x28]
	ldrh r0, [r5, #0xe]
	cmp r1, r0
	blo _0224021C
	ldr r0, [r5]
	mov r1, #2
	bl FUN_02068E14
	add r4, r0, #0
	ldrb r0, [r5, #0xd]
	bl MOD12_0223C210
	lsl r0, r0, #8
	str r0, [r5, #0x10]
	ldrb r0, [r5, #0xd]
	bl MOD12_0223C220
	add r0, r4, r0
	lsl r0, r0, #8
	str r0, [r5, #0x14]
	ldrb r0, [r5, #0xd]
	bl MOD12_0223C234
	lsl r0, r0, #8
	str r0, [r5, #0x18]
	add r0, r5, #0
	add r0, #0x2a
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0x2a
	strb r1, [r0]
_0224021C:
	ldr r1, [r5, #0x10]
	asr r0, r1, #7
	lsr r0, r0, #0x18
	add r0, r1, r0
	asr r1, r0, #8
	ldr r0, [r5, #8]
	str r1, [r0, #4]
	ldr r1, [r5, #0x14]
	asr r0, r1, #7
	lsr r0, r0, #0x18
	add r0, r1, r0
	asr r1, r0, #8
	ldr r0, [r5, #8]
	str r1, [r0, #8]
	ldr r1, [r5, #0x18]
	asr r0, r1, #7
	lsr r0, r0, #0x18
	add r0, r1, r0
	asr r1, r0, #8
	ldr r0, [r5, #8]
	str r1, [r0, #0xc]
	ldr r2, [r5, #8]
	ldr r0, [r2]
	ldr r1, [r2, #4]
	ldr r2, [r2, #8]
	bl MOD17_021DD620
	ldr r0, [r5, #4]
	ldr r1, [r5, #8]
	bl MOD12_0223D09C
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0224025E:
	mov r1, #1
	add r5, #0x2b
	strb r1, [r5]
	bl FUN_0200CAB4
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224026C: .word 0xFFFFB000
_02240270: .word 0xFFFF9C00

	thumb_func_start MOD12_02240274
MOD12_02240274: ; 0x02240274
	push {r3, lr}
	mov r1, #0x3c
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02240288
MOD12_02240288: ; 0x02240288
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	str r1, [sp]
	mov r0, #0x17
	mov r1, #0x50
	add r5, r2, #0
	add r6, r3, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x50
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp]
	add r3, r4, #0
	str r0, [r4]
	ldrh r0, [r5]
	add r3, #0x10
	mov r2, #7
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	str r7, [r4, #0xc]
_022402C0:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _022402C0
	ldr r0, [r6]
	ldr r2, _022402D8 ; =0x00007530
	str r0, [r3]
	ldr r0, _022402DC ; =MOD12_022402E0
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022402D8: .word 0x00007530
_022402DC: .word MOD12_022402E0

	thumb_func_start MOD12_022402E0
MOD12_022402E0: ; 0x022402E0
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0x4c
	ldrb r0, [r0]
	cmp r0, #0
	bne _02240330
	mov r4, #0
_022402F2:
	add r1, r5, r4
	ldrb r1, [r1, #0x12]
	ldr r0, [r5]
	add r2, r4, #0
	bl MOD12_0223DC28
	add r4, r4, #1
	cmp r4, #4
	blt _022402F2
	ldr r1, [r5]
	ldr r0, _0224034C ; =0x00001130
	mov r3, #0
	ldr r0, [r1, r0]
	mov r1, #1
	add r2, r1, #0
	bl MOD12_0223B758
	ldr r1, [r5]
	ldr r0, _0224034C ; =0x00001130
	mov r2, #6
	ldr r0, [r1, r0]
	mov r1, #0
	bl MOD12_0223C1F4
	add r0, r5, #0
	add r0, #0x4c
	ldrb r0, [r0]
	add r5, #0x4c
	add r0, r0, #1
	strb r0, [r5]
	pop {r3, r4, r5, pc}
_02240330:
	mov r2, #0
	ldr r0, [r5, #0xc]
	add r1, r5, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	nop
_0224034C: .word 0x00001130

	thumb_func_start MOD12_02240350
MOD12_02240350: ; 0x02240350
	push {r3, lr}
	mov r1, #0x3c
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02240364
MOD12_02240364: ; 0x02240364
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	str r1, [sp]
	mov r0, #0x17
	mov r1, #0x50
	add r5, r2, #0
	add r6, r3, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x50
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp]
	add r3, r4, #0
	str r0, [r4]
	ldrh r0, [r5]
	add r3, #0x10
	mov r2, #7
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	str r7, [r4, #0xc]
_0224039C:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0224039C
	ldr r0, [r6]
	ldr r2, _022403B4 ; =0x00007530
	str r0, [r3]
	ldr r0, _022403B8 ; =MOD12_022403BC
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022403B4: .word 0x00007530
_022403B8: .word MOD12_022403BC

	thumb_func_start MOD12_022403BC
MOD12_022403BC: ; 0x022403BC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0x4c
	ldrb r0, [r0]
	cmp r0, #0
	beq _022403D2
	cmp r0, #1
	beq _0224040A
	b _0224044E
_022403D2:
	ldr r0, [r5]
	bl MOD12_0223D588
	cmp r0, #0
	beq _02240484
	mov r4, #0
	mov r6, #2
	mov r7, #5
_022403E2:
	ldr r0, [r5]
	add r1, r4, #0
	add r2, r6, #0
	bl MOD12_0223DCE8
	ldr r0, [r5]
	add r1, r4, #0
	add r2, r7, #0
	bl MOD12_0223DCE8
	add r4, r4, #1
	cmp r4, #4
	blt _022403E2
	add r0, r5, #0
	add r0, #0x4c
	ldrb r0, [r0]
	add r5, #0x4c
	add r0, r0, #1
	strb r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_0224040A:
	mov r7, #0
	add r6, r7, #0
	add r4, r7, #0
_02240410:
	ldr r0, [r5]
	add r1, r4, #0
	bl MOD12_0223DDB0
	cmp r0, #1
	bne _0224041E
	add r7, r7, #1
_0224041E:
	ldr r0, [r5]
	add r1, r4, #0
	bl MOD12_0223DDE4
	cmp r0, #1
	bne _0224042C
	add r6, r6, #1
_0224042C:
	add r4, r4, #1
	cmp r4, #4
	blt _02240410
	cmp r7, #4
	blt _02240484
	cmp r6, #4
	blt _02240484
	ldr r0, [r5]
	bl MOD12_0223DCC0
	add r0, r5, #0
	add r0, #0x4c
	ldrb r0, [r0]
	add r5, #0x4c
	add r0, r0, #1
	strb r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_0224044E:
	ldr r1, [r5]
	ldr r0, _02240488 ; =0x00001130
	mov r2, #1
	ldr r0, [r1, r0]
	mov r1, #0
	add r3, r1, #0
	bl MOD12_0223B758
	ldr r1, [r5]
	ldr r0, _02240488 ; =0x00001130
	ldr r0, [r1, r0]
	mov r1, #0
	add r2, r1, #0
	bl MOD12_0223C1F4
	mov r2, #0
	ldr r0, [r5, #0xc]
	add r1, r5, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_02240484:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02240488: .word 0x00001130

	thumb_func_start MOD12_0224048C
MOD12_0224048C: ; 0x0224048C
	push {r3, lr}
	mov r1, #0x3c
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_022404A0
MOD12_022404A0: ; 0x022404A0
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	str r1, [sp]
	mov r0, #0x17
	mov r1, #0x20
	add r6, r2, #0
	add r5, r3, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x20
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp]
	ldr r2, _02240504 ; =0x00007530
	str r0, [r4]
	ldrh r0, [r6]
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r6, #2]
	strh r0, [r4, #6]
	ldrh r0, [r6, #4]
	strh r0, [r4, #8]
	ldrh r0, [r6, #6]
	strh r0, [r4, #0xa]
	str r7, [r4, #0xc]
	ldrb r0, [r5]
	strb r0, [r4, #0x11]
	ldrh r0, [r5, #0x30]
	strh r0, [r4, #0x14]
	ldrh r0, [r5, #0x32]
	strh r0, [r4, #0x16]
	ldrh r0, [r5, #0x34]
	strh r0, [r4, #0x18]
	add r0, r5, #0
	add r0, #0x36
	ldrb r0, [r0]
	strb r0, [r4, #0x1a]
	add r0, r5, #0
	add r0, #0x38
	ldrb r0, [r0]
	add r5, #0x37
	strb r0, [r4, #0x1c]
	ldrb r0, [r5]
	strb r0, [r4, #0x1b]
	ldr r0, _02240508 ; =MOD12_0224050C
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02240504: .word 0x00007530
_02240508: .word MOD12_0224050C

	thumb_func_start MOD12_0224050C
MOD12_0224050C: ; 0x0224050C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _02240522
	cmp r0, #1
	beq _0224055A
	cmp r0, #2
	beq _0224056C
	b _022405A4
_02240522:
	ldrb r0, [r4, #0x1a]
	cmp r0, #0
	beq _02240554
	ldr r0, [r4]
	mov r1, #1
	add r0, #0x78
	add r2, r1, #0
	mov r3, #0xe
	bl FUN_0200D0BC
	ldr r0, [r4]
	mov r1, #1
	ldr r0, [r0, #0x74]
	bl FUN_0201AC68
	add r2, r4, #0
	ldrb r1, [r4, #0x1a]
	ldr r0, [r4]
	add r2, #0x14
	bl MOD12_0223E274
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02240554:
	mov r0, #0x64
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0224055A:
	ldr r0, [r4]
	bl MOD12_0223E2A8
	cmp r0, #0
	bne _022405BC
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0224056C:
	ldrb r0, [r4, #0x12]
	add r0, r0, #1
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x1c]
	cmp r0, #1
	bne _02240580
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02240580:
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x1b]
	cmp r1, r0
	blo _022405BC
	ldr r0, [r4]
	mov r1, #1
	add r0, #0x78
	bl FUN_0200D0E0
	ldr r0, [r4]
	mov r1, #1
	ldr r0, [r0, #0x74]
	bl FUN_0201AC68
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_022405A4:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_022405BC:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_022405C0
MOD12_022405C0: ; 0x022405C0
	push {r3, lr}
	mov r1, #0x30
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_022405D4
MOD12_022405D4: ; 0x022405D4
	push {r4, r5, r6, lr}
	add r4, r0, #0
	mov r0, #0xad
	lsl r0, r0, #4
	add r6, r1, r0
	mov r5, #6
_022405E0:
	ldmia r3!, {r0, r1}
	stmia r6!, {r0, r1}
	sub r5, r5, #1
	bne _022405E0
	add r1, r2, #0
	mov r2, #0
	add r0, r4, #0
	add r3, r2, #0
	bl MOD12_02240FB0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD12_022405F8
MOD12_022405F8: ; 0x022405F8
	push {r3, lr}
	mov r1, #0x3c
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0224060C
MOD12_0224060C: ; 0x0224060C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r3, #0
	add r6, r0, #0
	add r5, r1, #0
	add r7, r2, #0
	bl FUN_0200541C
	ldrh r0, [r4, #0x24]
	bl FUN_0200521C
	ldr r0, _02240640 ; =0x00001134
	mov r1, #1
	strb r1, [r5, r0]
	add r1, r0, #4
	add r0, #0xc
	add r1, r5, r1
	ldmia r1!, {r2, r3}
	add r0, r5, r0
	stmia r0!, {r2, r3}
	mov r2, #0
	add r0, r6, #0
	add r1, r7, #0
	add r3, r2, #0
	bl MOD12_02240FB0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02240640: .word 0x00001134

	thumb_func_start MOD12_02240644
MOD12_02240644: ; 0x02240644
	push {r3, lr}
	mov r1, #0x3c
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02240658
MOD12_02240658: ; 0x02240658
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	str r1, [sp]
	mov r0, #0x17
	mov r1, #0x54
	add r5, r2, #0
	add r6, r3, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x54
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp]
	add r3, r4, #0
	str r0, [r4]
	ldrh r0, [r5]
	add r3, #0x10
	mov r2, #7
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	str r7, [r4, #0xc]
_02240690:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02240690
	ldr r0, [r6]
	ldr r2, _022406A8 ; =0x00007530
	str r0, [r3]
	ldr r0, _022406AC ; =MOD12_022406B0
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022406A8: .word 0x00007530
_022406AC: .word MOD12_022406B0

	thumb_func_start MOD12_022406B0
MOD12_022406B0: ; 0x022406B0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x50
	ldrb r0, [r0]
	cmp r0, #4
	bhi _0224074E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022406CC: ; jump table
	.short _022406D6 - _022406CC - 2 ; case 0
	.short _022406EC - _022406CC - 2 ; case 1
	.short _02240704 - _022406CC - 2 ; case 2
	.short _02240718 - _022406CC - 2 ; case 3
	.short _02240734 - _022406CC - 2 ; case 4
_022406D6:
	ldr r1, [r4]
	ldr r0, _02240768 ; =0x00001134
	mov r2, #0
	strb r2, [r1, r0]
	add r0, r4, #0
	add r0, #0x50
	ldrb r0, [r0]
	add r4, #0x50
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_022406EC:
	ldrh r0, [r4, #0x34]
	bl FUN_02005410
	cmp r0, #0
	bne _02240766
	add r0, r4, #0
	add r0, #0x50
	ldrb r0, [r0]
	add r4, #0x50
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_02240704:
	ldr r0, [r4]
	bl MOD12_0223ECF0
	add r0, r4, #0
	add r0, #0x50
	ldrb r0, [r0]
	add r4, #0x50
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_02240718:
	ldr r0, [r4, #0x4c]
	add r0, r0, #1
	str r0, [r4, #0x4c]
	cmp r0, #0x3c
	bls _02240766
	mov r0, #0
	str r0, [r4, #0x4c]
	add r0, r4, #0
	add r0, #0x50
	ldrb r0, [r0]
	add r4, #0x50
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_02240734:
	ldr r0, _0224076C ; =0x0000046F
	bl FUN_0200521C
	ldr r0, _02240770 ; =0x000006E5
	bl FUN_020054C8
	add r0, r4, #0
	add r0, #0x50
	ldrb r0, [r0]
	add r4, #0x50
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_0224074E:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02240766:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02240768: .word 0x00001134
_0224076C: .word 0x0000046F
_02240770: .word 0x000006E5

	thumb_func_start MOD12_02240774
MOD12_02240774: ; 0x02240774
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r6, r2, #0
	add r5, r0, #0
	mov r1, #0
	mov r2, #0x3c
	add r7, r3, #0
	bl MI_CpuFill8
	add r0, r5, #0
	add r0, #0x37
	strb r4, [r0]
	add r0, r5, #0
	add r0, #0x38
	strb r6, [r0]
	str r7, [r5, #0x30]
	ldr r0, [sp, #0x18]
	add r5, #0x39
	strb r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD12_0224079C
MOD12_0224079C: ; 0x0224079C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r1, [r5, #0x30]
	mov r2, #0x3c
	str r1, [sp]
	add r1, r5, #0
	add r1, #0x37
	ldrb r7, [r1]
	add r1, r5, #0
	add r1, #0x38
	ldrb r6, [r1]
	add r1, r5, #0
	add r1, #0x39
	ldrb r4, [r1]
	mov r1, #0
	bl MI_CpuFill8
	ldr r0, [sp]
	str r0, [r5, #0x30]
	add r0, r5, #0
	add r0, #0x37
	strb r7, [r0]
	add r0, r5, #0
	add r0, #0x38
	strb r6, [r0]
	add r5, #0x39
	strb r4, [r5]
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD12_022407D4
MOD12_022407D4: ; 0x022407D4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r4, r1, #0
	add r7, r0, #0
	ldr r1, _022409BC ; =0x00001388
	lsr r0, r3, #2
	add r0, r0, r1
	lsl r1, r1, #1
	str r3, [sp]
	bl _u32_div_f
	str r0, [sp, #8]
	mov r0, #0x12
	ldr r1, [r7]
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _022407FC
	cmp r0, #1
	bne _02240806
_022407FC:
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #8
	str r0, [sp, #0x10]
	b _02240814
_02240806:
	mov r0, #1
	str r0, [sp, #0xc]
	mov r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [sp]
	lsr r0, r0, #1
	str r0, [sp]
_02240814:
	mov r5, #0
	add r1, r5, #0
	add r0, sp, #0x24
	b _02240820
_0224081C:
	strb r1, [r0, r5]
	add r5, r5, #1
_02240820:
	cmp r5, #0x10
	blt _0224081C
	ldr r0, [sp, #0x10]
	mov r6, #0
	sub r0, r0, #1
	str r0, [sp, #0x18]
	add r0, r4, #0
	str r0, [sp, #0x14]
	add r0, #0x30
	str r0, [sp, #0x14]
_02240834:
	ldr r0, [r4, #0x30]
	ldr r1, [sp, #0x14]
	bl FUN_02082880
	ldr r1, [sp, #0x10]
	bl _s32_div_f
	add r5, r1, #0
	beq _02240834
	add r0, sp, #0x24
	ldrb r0, [r0, r5]
	cmp r0, #0
	bne _02240834
	ldr r0, [sp, #0xc]
	cmp r0, #1
	bne _0224088E
	ldr r0, [sp, #0x18]
	cmp r5, r0
	bne _02240864
	sub r1, r5, #1
	add r0, sp, #0x24
	ldrb r0, [r0, r1]
	cmp r0, #1
	beq _02240834
_02240864:
	sub r1, r5, #1
	add r0, sp, #0x24
	ldrb r0, [r0, r1]
	cmp r0, #1
	beq _02240834
	add r1, r5, #1
	add r0, sp, #0x24
	ldrb r0, [r0, r1]
	cmp r0, #1
	beq _02240834
	mov r0, #1
	tst r0, r5
	beq _0224088E
	ldr r0, [r4, #0x30]
	ldr r1, [sp, #0x14]
	bl FUN_02082880
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x80
	blt _02240834
_0224088E:
	mov r1, #1
	add r0, sp, #0x24
	strb r1, [r0, r5]
	ldr r0, _022409C0 ; =0x00000AFE
	add r6, r6, #1
	ldrb r0, [r7, r0]
	cmp r6, r0
	blt _02240834
	mov r6, #0
	add r5, r6, #0
	b _022408C4
_022408A4:
	add r0, sp, #0x24
	ldrb r0, [r0, r5]
	cmp r0, #1
	bne _022408C2
	ldr r0, [sp]
	add r1, r5, #0
	mul r1, r0
	ldr r0, _022409BC ; =0x00001388
	add r0, r1, r0
	ldr r1, _022409C4 ; =0x00002710
	bl _u32_div_f
	lsl r1, r6, #2
	str r0, [r4, r1]
	add r6, r6, #1
_022408C2:
	add r5, r5, #1
_022408C4:
	cmp r5, #0x10
	blt _022408A4
	mov r0, #0x12
	ldr r1, [r7]
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	add r1, r4, #0
	add r1, #0x39
	ldrb r1, [r1]
	bl MOD12_022409CC
	add r6, r0, #0
	add r0, r4, #0
	str r0, [sp, #0x1c]
	add r0, #0x30
	str r0, [sp, #0x1c]
	lsr r0, r6, #0x1f
	add r0, r6, r0
	asr r0, r0, #1
	add r0, r0, #1
	mov r5, #0
	str r0, [sp, #0x20]
	b _0224092C
_022408F2:
	ldr r0, [r4, #0x30]
	ldr r1, [sp, #0x1c]
	bl FUN_02082880
	add r1, r6, #2
	bl _s32_div_f
	lsl r0, r5, #2
	ldr r0, [r4, r0]
	add r1, r0, r1
	ldr r0, [sp, #0x20]
	sub r3, r1, r0
	bpl _0224090E
	mov r3, #0
_0224090E:
	lsl r0, r5, #2
	ldr r1, [r4, r0]
	ldr r0, [sp, #8]
	sub r2, r3, r1
	cmp r2, r0
	blo _0224091E
	add r0, r0, r1
	sub r3, r0, #1
_0224091E:
	lsl r0, r5, #2
	add r1, r4, r5
	str r3, [r4, r0]
	add r1, #0x28
	mov r0, #1
	strb r0, [r1]
	add r5, r5, #1
_0224092C:
	ldr r0, _022409C0 ; =0x00000AFE
	ldrb r0, [r7, r0]
	cmp r5, r0
	blt _022408F2
	mov r0, #0x12
	ldr r1, [r7]
	lsl r0, r0, #4
	ldrb r1, [r1, r0]
	ldr r0, _022409C8 ; =MOD12_022464C4
	ldrb r0, [r0, r1]
	add r1, r4, #0
	add r1, #0x30
	str r0, [sp, #4]
	ldr r0, [r4, #0x30]
	bl FUN_02082880
	add r6, r4, #0
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r4, #0
	add r1, r2, r1
	add r0, #0x20
	strb r1, [r0]
	mov r5, #1
	add r6, #0x30
	b _022409B0
_02240966:
	ldr r0, _022409C0 ; =0x00000AFE
	ldrb r0, [r7, r0]
	sub r0, r0, #1
	cmp r5, r0
	bge _02240994
	ldr r0, [r4, #0x30]
	add r1, r6, #0
	bl FUN_02082880
	mov r1, #0x64
	bl _s32_div_f
	ldr r0, [sp, #4]
	cmp r0, r1
	ble _02240994
	sub r0, r5, #1
	add r0, r4, r0
	add r0, #0x20
	ldrb r1, [r0]
	add r0, r4, r5
	add r0, #0x20
	strb r1, [r0]
	b _022409AE
_02240994:
	ldr r0, [r4, #0x30]
	add r1, r6, #0
	bl FUN_02082880
	lsr r1, r0, #0x1f
	lsl r2, r0, #0x1e
	sub r2, r2, r1
	mov r0, #0x1e
	ror r2, r0
	add r0, r4, r5
	add r1, r1, r2
	add r0, #0x20
	strb r1, [r0]
_022409AE:
	add r5, r5, #1
_022409B0:
	ldr r0, _022409C0 ; =0x00000AFE
	ldrb r0, [r7, r0]
	cmp r5, r0
	blt _02240966
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022409BC: .word 0x00001388
_022409C0: .word 0x00000AFE
_022409C4: .word 0x00002710
_022409C8: .word MOD12_022464C4

	thumb_func_start MOD12_022409CC
MOD12_022409CC: ; 0x022409CC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #4
	blo _022409DA
	bl ErrorHandling
_022409DA:
	ldr r0, _02240A0C ; =MOD12_022464C0
	cmp r4, #3
	ldrsb r0, [r0, r5]
	bhi _02240A02
	add r1, r4, r4
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022409EE: ; jump table
	.short _022409F6 - _022409EE - 2 ; case 0
	.short _02240A08 - _022409EE - 2 ; case 1
	.short _022409FA - _022409EE - 2 ; case 2
	.short _02240A02 - _022409EE - 2 ; case 3
_022409F6:
	lsl r0, r0, #1
	pop {r3, r4, r5, pc}
_022409FA:
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r0, r1, #1
	pop {r3, r4, r5, pc}
_02240A02:
	mov r1, #3
	bl _s32_div_f
_02240A08:
	pop {r3, r4, r5, pc}
	nop
_02240A0C: .word MOD12_022464C0

	thumb_func_start MOD12_02240A10
MOD12_02240A10: ; 0x02240A10
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r6, r0, #0
	add r5, r2, #0
	add r4, r3, #0
	cmp r7, #4
	blo _02240A22
	bl ErrorHandling
_02240A22:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	beq _02240A3C
	mov r0, #1
	add r1, r5, #0
	and r1, r0
	and r0, r4
	cmp r1, r0
	sub r0, r5, r4
	cmp r0, #4
	sub r0, r5, r4
	cmp r0, #8
_02240A3C:
	ldr r0, _02240A70 ; =MOD12_022464C0
	cmp r6, #3
	ldrsb r0, [r0, r7]
	bhi _02240A68
	add r1, r6, r6
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02240A50: ; jump table
	.short _02240A58 - _02240A50 - 2 ; case 0
	.short _02240A5C - _02240A50 - 2 ; case 1
	.short _02240A60 - _02240A50 - 2 ; case 2
	.short _02240A68 - _02240A50 - 2 ; case 3
_02240A58:
	lsl r0, r0, #1
	b _02240A68
_02240A5C:
	lsl r0, r0, #1
	b _02240A68
_02240A60:
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r1, r1, #1
	add r0, r0, r1
_02240A68:
	cmp r0, #0
	bge _02240A6E
	mov r0, #0
_02240A6E:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02240A70: .word MOD12_022464C0

	thumb_func_start MOD12_02240A74
MOD12_02240A74: ; 0x02240A74
	push {r4, r5}
	mov r4, #0
	ldr r5, [sp, #8]
	cmp r1, #3
	bhi _02240AB0
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02240A8A: ; jump table
	.short _02240A92 - _02240A8A - 2 ; case 0
	.short _02240A9A - _02240A8A - 2 ; case 1
	.short _02240AA2 - _02240A8A - 2 ; case 2
	.short _02240AAA - _02240A8A - 2 ; case 3
_02240A92:
	cmp r5, #1
	bne _02240AB0
	add r4, r4, #3
	b _02240AB0
_02240A9A:
	cmp r5, #2
	bne _02240AB0
	add r4, r4, #3
	b _02240AB0
_02240AA2:
	cmp r5, #4
	bne _02240AB0
	add r4, r4, #3
	b _02240AB0
_02240AAA:
	cmp r5, #3
	bne _02240AB0
	add r4, r4, #3
_02240AB0:
	ldr r1, [sp, #0xc]
	cmp r1, #0
	beq _02240ABC
	cmp r5, r1
	beq _02240ABC
	add r4, #8
_02240ABC:
	mov r1, #0
	mvn r1, r1
	cmp r3, r1
	beq _02240ADA
	mov r1, #1
	add r5, r2, #0
	and r5, r1
	and r1, r3
	cmp r5, r1
	beq _02240AD2
	add r4, r4, #2
_02240AD2:
	sub r1, r2, r3
	cmp r1, #8
	blt _02240ADA
	add r4, r4, #5
_02240ADA:
	cmp r0, #3
	bhi _02240B02
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02240AEA: ; jump table
	.short _02240AF2 - _02240AEA - 2 ; case 0
	.short _02240AF6 - _02240AEA - 2 ; case 1
	.short _02240AFA - _02240AEA - 2 ; case 2
	.short _02240B02 - _02240AEA - 2 ; case 3
_02240AF2:
	lsl r4, r4, #1
	b _02240B02
_02240AF6:
	lsl r4, r4, #1
	b _02240B02
_02240AFA:
	lsr r0, r4, #0x1f
	add r0, r4, r0
	asr r0, r0, #1
	add r4, r4, r0
_02240B02:
	add r0, r4, #0
	pop {r4, r5}
	bx lr

	thumb_func_start MOD12_02240B08
MOD12_02240B08: ; 0x02240B08
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r2, #0
	add r4, #0x38
	ldrb r4, [r4]
	cmp r4, #0
	bne _02240B36
	cmp r0, #0
	bne _02240B36
	ldr r0, [sp, #0x1c]
	str r0, [sp]
	ldr r0, [sp, #0x20]
	str r0, [sp, #4]
	ldr r0, [sp, #0x24]
	str r0, [sp, #8]
	add r0, r1, #0
	add r1, r2, #0
	add r2, r3, #0
	ldr r3, [sp, #0x18]
	bl MOD12_02240B5C
	add sp, #0xc
	pop {r3, r4, pc}
_02240B36:
	cmp r4, #0
	beq _02240B56
	cmp r0, #1
	bne _02240B56
	ldr r0, [sp, #0x1c]
	str r0, [sp]
	ldr r0, [sp, #0x20]
	str r0, [sp, #4]
	ldr r0, [sp, #0x24]
	str r0, [sp, #8]
	add r0, r1, #0
	add r1, r2, #0
	add r2, r3, #0
	ldr r3, [sp, #0x18]
	bl MOD12_02240C00
_02240B56:
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start MOD12_02240B5C
MOD12_02240B5C: ; 0x02240B5C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x24
	add r4, r1, #0
	add r0, r4, #0
	add r0, #0x38
	ldrb r3, [r0]
	cmp r3, #0
	bne _02240BF6
	ldr r0, [sp, #0x3c]
	add r1, #0x36
	ldrb r0, [r0, #5]
	ldrb r1, [r1]
	cmp r1, r0
	bhs _02240BF6
	mov r5, #0x34
	ldrsh r5, [r4, r5]
	cmp r5, #0
	ble _02240B88
	sub r0, r5, #1
	add sp, #0x24
	strh r0, [r4, #0x34]
	pop {r3, r4, r5, r6, pc}
_02240B88:
	mov r5, #0
_02240B8A:
	add r6, r4, r5
	add r6, #0x28
	ldrb r6, [r6]
	cmp r6, #1
	beq _02240B9A
	add r5, r5, #1
	cmp r5, #8
	blt _02240B8A
_02240B9A:
	cmp r5, #8
	bge _02240BF6
	lsl r6, r5, #2
	ldr r6, [r4, r6]
	cmp r6, r2
	bhi _02240BF6
	ldr r6, [sp, #0x3c]
	add r6, #8
	str r6, [sp]
	add r6, sp, #0x18
	str r6, [sp, #4]
	mov r6, #0
	str r6, [sp, #8]
	str r3, [sp, #0xc]
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	add r0, r4, #0
	add r1, r4, r5
	add r0, #0x37
	add r1, #0x20
	ldrb r0, [r0]
	ldrb r1, [r1]
	ldr r3, [sp, #0x38]
	bl MOD12_0223FCAC
	ldr r0, [sp, #0x40]
	add r1, sp, #0x18
	bl MOD12_0223F56C
	add r0, r4, r5
	add r1, r6, #0
	add r0, #0x28
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x36
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x36
	strb r1, [r0]
	ldr r0, [sp, #0x38]
	ldr r1, _02240BFC ; =0x00002710
	bl _u32_div_f
	sub r0, r0, #2
	strh r0, [r4, #0x34]
_02240BF6:
	add sp, #0x24
	pop {r3, r4, r5, r6, pc}
	nop
_02240BFC: .word 0x00002710

	thumb_func_start MOD12_02240C00
MOD12_02240C00: ; 0x02240C00
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	add r7, r0, #0
	ldr r0, [sp, #0x5c]
	add r5, r1, #0
	str r0, [sp, #0x5c]
	ldr r0, [sp, #0x58]
	str r2, [sp, #0x18]
	lsr r0, r0, #1
	str r0, [sp, #0x34]
	add r0, r5, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #0
	beq _02240C3C
	add r0, r5, #0
	add r0, #0x36
	ldrb r1, [r0]
	ldr r0, [sp, #0x5c]
	ldrb r0, [r0, #5]
	cmp r1, r0
	bhs _02240C3C
	mov r0, #0xa
	mul r0, r1
	ldr r2, _02240DB4 ; =0x00001BA0
	add r4, r7, r0
	ldrb r2, [r4, r2]
	lsl r2, r2, #0x1d
	lsr r2, r2, #0x1f
	bne _02240C3E
_02240C3C:
	b _02240DB0
_02240C3E:
	mov r6, #0x34
	ldrsh r2, [r5, r6]
	cmp r2, #0
	ble _02240C4E
	sub r0, r2, #1
	add sp, #0x44
	strh r0, [r5, #0x34]
	pop {r4, r5, r6, r7, pc}
_02240C4E:
	ldr r2, _02240DB4 ; =0x00001BA0
	sub r2, #8
	add r2, r7, r2
	add r4, r2, r0
	ldr r0, [sp, #0x18]
	lsr r2, r3, #1
	sub r0, r0, r2
	str r0, [sp, #0x30]
	ldrb r0, [r5, #5]
	cmp r0, #0
	bne _02240D4C
	cmp r1, #0
	bne _02240C70
	mov r0, #0
	sub r6, #0x35
	str r0, [sp, #0x1c]
	b _02240C86
_02240C70:
	sub r1, r1, #1
	mov r0, #0xa
	mul r0, r1
	ldr r1, _02240DB4 ; =0x00001BA0
	add r0, r7, r0
	sub r1, r1, #2
	ldrb r6, [r0, r1]
	ldr r1, _02240DB4 ; =0x00001BA0
	sub r1, r1, #5
	ldrb r0, [r0, r1]
	str r0, [sp, #0x1c]
_02240C86:
	mov r0, #0x12
	ldr r1, [r7]
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	add r1, r5, #0
	add r1, #0x39
	ldrb r1, [r1]
	ldrb r2, [r4, #6]
	add r3, r6, #0
	bl MOD12_02240A10
	str r0, [sp, #0x28]
	ldrb r0, [r4, #3]
	add r3, r6, #0
	str r0, [sp]
	ldr r0, [sp, #0x1c]
	str r0, [sp, #4]
	mov r0, #0x12
	ldr r1, [r7]
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	add r1, r5, #0
	add r1, #0x39
	ldrb r1, [r1]
	ldrb r2, [r4, #6]
	bl MOD12_02240A74
	str r0, [sp, #0x24]
	ldrb r1, [r4, #6]
	ldr r0, [sp, #0x34]
	mul r0, r1
	ldr r1, _02240DB8 ; =0x00001388
	add r0, r0, r1
	lsl r1, r1, #1
	bl _u32_div_f
	add r6, r0, #0
	add r1, r5, #0
	ldr r0, [r5, #0x30]
	add r1, #0x30
	bl FUN_02082880
	ldr r1, [sp, #0x28]
	add r1, r1, #2
	bl _s32_div_f
	ldr r0, [sp, #0x28]
	lsr r2, r0, #0x1f
	add r2, r0, r2
	asr r0, r2, #1
	add r0, r0, #1
	sub r0, r1, r0
	add r0, r0, r6
	str r0, [sp, #0x2c]
	bpl _02240CF8
	mov r0, #0
	str r0, [sp, #0x2c]
_02240CF8:
	add r1, r5, #0
	ldr r0, [r5, #0x30]
	add r1, #0x30
	bl FUN_02082880
	mov r1, #0x64
	bl _s32_div_f
	ldr r2, [sp, #0x28]
	ldr r0, [sp, #0x24]
	add r0, r2, r0
	cmp r1, r0
	bge _02240D38
	add r6, r5, #0
	add r6, #0x30
_02240D16:
	ldr r0, [r5, #0x30]
	add r1, r6, #0
	bl FUN_02082880
	lsr r1, r0, #0x1f
	lsl r2, r0, #0x1e
	sub r2, r2, r1
	mov r0, #0x1e
	ror r2, r0
	add r0, r1, r2
	str r0, [sp, #0x20]
	bl MOD12_0223FB80
	ldrb r1, [r4, #3]
	cmp r1, r0
	beq _02240D16
	b _02240D40
_02240D38:
	ldrb r0, [r4, #3]
	bl MOD12_0223FBB4
	str r0, [sp, #0x20]
_02240D40:
	ldr r0, [sp, #0x2c]
	str r0, [r5]
	ldr r0, [sp, #0x20]
	strb r0, [r5, #4]
	mov r0, #1
	strb r0, [r5, #5]
_02240D4C:
	ldr r1, [r5]
	ldr r0, [sp, #0x30]
	cmp r1, r0
	bhi _02240DB0
	ldr r0, [sp, #0x5c]
	ldr r2, [sp, #0x18]
	add r0, #8
	str r0, [sp]
	add r0, sp, #0x38
	str r0, [sp, #4]
	ldr r0, _02240DBC ; =0x00001B98
	ldr r3, [sp, #0x58]
	add r0, r7, r0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0x38
	ldrb r0, [r0]
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r0, #0x36
	ldrb r0, [r0]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x5c]
	ldrb r0, [r0, #5]
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r0, #0x37
	ldrb r0, [r0]
	ldrb r1, [r5, #4]
	bl MOD12_0223FCAC
	ldr r0, [sp, #0x60]
	add r1, sp, #0x38
	bl MOD12_0223F56C
	mov r0, #0
	strb r0, [r5, #5]
	add r0, r5, #0
	add r0, #0x36
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0x36
	strb r1, [r0]
	ldr r0, [sp, #0x58]
	ldr r1, _02240DC0 ; =0x00002710
	bl _u32_div_f
	sub r0, r0, #2
	strh r0, [r5, #0x34]
_02240DB0:
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02240DB4: .word 0x00001BA0
_02240DB8: .word 0x00001388
_02240DBC: .word 0x00001B98
_02240DC0: .word 0x00002710

	thumb_func_start MOD12_02240DC4
MOD12_02240DC4: ; 0x02240DC4
	push {r4, lr}
	add r4, r0, #0
	cmp r4, #5
	blo _02240DD0
	bl ErrorHandling
_02240DD0:
	ldr r0, _02240DD8 ; =MOD12_022464D0
	lsl r1, r4, #2
	ldr r0, [r0, r1]
	pop {r4, pc}
	.align 2, 0
_02240DD8: .word MOD12_022464D0

	thumb_func_start MOD12_02240DDC
MOD12_02240DDC: ; 0x02240DDC
	mov r0, #0x31
	bx lr

	thumb_func_start MOD12_02240DE0
MOD12_02240DE0: ; 0x02240DE0
	mov r0, #0x32
	bx lr

	thumb_func_start MOD12_02240DE4
MOD12_02240DE4: ; 0x02240DE4
	push {r4, lr}
	add r4, r0, #0
	cmp r4, #5
	blo _02240DF0
	bl ErrorHandling
_02240DF0:
	ldr r0, _02240DF8 ; =MOD12_022464C8
	ldrb r0, [r0, r4]
	pop {r4, pc}
	nop
_02240DF8: .word MOD12_022464C8

	thumb_func_start MOD12_02240DFC
MOD12_02240DFC: ; 0x02240DFC
	mov r0, #0x2e
	bx lr

	thumb_func_start MOD12_02240E00
MOD12_02240E00: ; 0x02240E00
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r3, #0
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	bl MOD12_02240DFC
	str r0, [sp, #0xc]
	add r0, r7, #0
	bl MOD12_02240DC4
	add r3, r0, #0
	mov r0, #1
	str r0, [sp]
	ldr r0, [sp, #0x28]
	str r4, [sp, #4]
	str r0, [sp, #8]
	ldr r2, [sp, #0xc]
	add r0, r5, #0
	add r1, r6, #0
	bl FUN_0200C00C
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_02240E34
MOD12_02240E34: ; 0x02240E34
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MOD12_02240DFC
	str r0, [sp, #8]
	bl MOD12_02240DDC
	add r3, r0, #0
	mov r0, #1
	str r0, [sp]
	ldr r2, [sp, #8]
	add r0, r5, #0
	add r1, r4, #0
	str r6, [sp, #4]
	bl FUN_0200C124
	bl MOD12_02240DFC
	add r6, r0, #0
	bl MOD12_02240DE0
	add r3, r0, #0
	mov r0, #1
	str r0, [sp]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	str r7, [sp, #4]
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD12_02240E7C
MOD12_02240E7C: ; 0x02240E7C
	ldr r3, _02240E80 ; =FUN_0200C358
	bx r3
	.align 2, 0
_02240E80: .word FUN_0200C358

	thumb_func_start MOD12_02240E84
MOD12_02240E84: ; 0x02240E84
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r2, #0
	bl FUN_0200C378
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0200C388
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_02240E98
MOD12_02240E98: ; 0x02240E98
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r6, r3, #0
	add r4, r0, #0
	add r7, r1, #0
	add r5, sp, #0
	mov r3, #6
_02240EA6:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r3, r3, #1
	bne _02240EA6
	ldr r0, [r6]
	str r0, [r5]
	add r0, r2, #0
	bl MOD12_02240DE4
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r1, r7, #0
	add r2, sp, #0
	bl FUN_0200C154
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD12_02240EC8
MOD12_02240EC8: ; 0x02240EC8
	ldr r3, _02240ECC ; =FUN_0200C3DC
	bx r3
	.align 2, 0
_02240ECC: .word FUN_0200C3DC

	thumb_func_start MOD12_02240ED0
MOD12_02240ED0: ; 0x02240ED0
	push {r3, r4, r5, lr}
	ldr r2, _02240EF4 ; =0x00000A18
	add r4, r1, #0
	mov r1, #0
	add r5, r0, #0
	bl MI_CpuFill8
	ldr r0, [r4]
	str r0, [r5]
	ldrh r0, [r4, #4]
	strh r0, [r5, #4]
	ldrb r0, [r4, #6]
	strb r0, [r5, #6]
	ldrb r0, [r4, #7]
	strb r0, [r5, #7]
	ldrb r0, [r4, #8]
	strb r0, [r5, #8]
	pop {r3, r4, r5, pc}
	.align 2, 0
_02240EF4: .word 0x00000A18

	thumb_func_start MOD12_02240EF8
MOD12_02240EF8: ; 0x02240EF8
	push {r3, r4, r5, lr}
	ldr r5, [r0, #0xc]
	mov r4, #0
	mov r2, #1
_02240F00:
	add r3, r2, #0
	lsl r3, r4
	add r1, r5, #0
	tst r1, r3
	bne _02240F14
	ldr r1, [r0, #0xc]
	orr r1, r3
	str r1, [r0, #0xc]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_02240F14:
	add r4, r4, #1
	cmp r4, #0x20
	blt _02240F00
	bl ErrorHandling
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_02240F24
MOD12_02240F24: ; 0x02240F24
	push {r3, r4}
	mov r2, #1
	add r3, r2, #0
	lsl r3, r1
	sub r1, r2, #2
	ldr r4, [r0, #0xc]
	eor r1, r3
	and r1, r4
	str r1, [r0, #0xc]
	pop {r3, r4}
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02240F3C
MOD12_02240F3C: ; 0x02240F3C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r4, [sp, #0x28]
	add r5, r0, #0
	mov r0, #2
	str r4, [sp, #4]
	add r4, #8
	lsl r0, r0, #8
	add r6, r1, #0
	add r7, r2, #0
	str r3, [sp]
	cmp r4, r0
	bls _02240F5A
	bl ErrorHandling
_02240F5A:
	add r0, r5, #0
	mov r2, #2
	add r0, #0x10
	mov r1, #0
	lsl r2, r2, #8
	bl MI_CpuFill8
	add r0, sp, #8
	strb r6, [r0, #4]
	strh r7, [r0, #2]
	add r0, r5, #0
	bl MOD12_02240EF8
	add r1, sp, #8
	strb r0, [r1, #5]
	mov r0, #0
	strb r0, [r1, #6]
	strh r4, [r1]
	add r1, r5, #0
	add r0, sp, #8
	add r1, #0x10
	mov r2, #8
	bl MIi_CpuCopy32
	add r1, r5, #0
	ldr r0, [sp]
	ldr r2, [sp, #4]
	add r1, #0x18
	bl MI_CpuCopy8
	ldr r0, _02240FAC ; =0x00000A15
	mov r1, #0
	strb r1, [r5, r0]
	mov r1, #1
	sub r0, r0, #5
	strb r1, [r5, r0]
	add r0, sp, #8
	ldrb r0, [r0, #5]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02240FAC: .word 0x00000A15

	thumb_func_start MOD12_02240FB0
MOD12_02240FB0: ; 0x02240FB0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r7, r3, #0
	mov r0, #2
	add r7, #8
	lsl r0, r0, #8
	add r4, r1, #0
	add r6, r2, #0
	str r3, [sp]
	cmp r7, r0
	bls _02240FCC
	bl ErrorHandling
_02240FCC:
	add r0, r5, #0
	mov r2, #2
	add r0, #0x10
	mov r1, #0
	lsl r2, r2, #8
	bl MI_CpuFill8
	ldrh r2, [r4]
	add r1, sp, #4
	add r0, sp, #4
	strh r2, [r1]
	ldrh r2, [r4, #2]
	strh r2, [r1, #2]
	ldrh r2, [r4, #4]
	strh r2, [r1, #4]
	ldrh r2, [r4, #6]
	strh r2, [r1, #6]
	mov r2, #0xfe
	strb r2, [r1, #4]
	mov r2, #1
	strb r2, [r1, #6]
	strh r7, [r1]
	add r1, r5, #0
	add r1, #0x10
	mov r2, #8
	bl MIi_CpuCopy32
	cmp r6, #0
	beq _02241012
	add r1, r5, #0
	ldr r2, [sp]
	add r0, r6, #0
	add r1, #0x18
	bl MI_CpuCopy8
_02241012:
	mov r0, #0xa1
	mov r1, #1
	lsl r0, r0, #4
	strb r1, [r5, r0]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_02241020
MOD12_02241020: ; 0x02241020
	push {r4, r5}
	lsl r5, r1, #9
	mov r1, #0x21
	lsl r1, r1, #4
	add r4, r0, r1
	add r1, #8
	add r4, r4, r5
	add r0, r0, r1
	str r4, [r2]
	add r0, r0, r5
	str r0, [r3]
	pop {r4, r5}
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0224103C
MOD12_0224103C: ; 0x0224103C
	mov r1, #0xa1
	lsl r1, r1, #4
	ldrb r0, [r0, r1]
	cmp r0, #1
	bne _0224104A
	mov r0, #0
	bx lr
_0224104A:
	mov r0, #1
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02241050
MOD12_02241050: ; 0x02241050
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	add r7, r3, #0
	bl MOD12_0224103C
	cmp r0, #0
	bne _02241066
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02241066:
	ldrh r0, [r5, #4]
	cmp r4, r0
	blt _02241070
	bl ErrorHandling
_02241070:
	add r0, r5, #0
	add r1, r6, #0
	mov r6, #0xc
	ldr r5, [r5]
	mul r6, r4
	add r2, r4, #0
	ldr r4, [r5, r6]
	add r3, r7, #0
	blx r4
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD12_02241088
MOD12_02241088: ; 0x02241088
	cmp r0, r2
	beq _02241098
	cmp r2, #0xff
	beq _02241098
	cmp r2, #0xfe
	bne _0224109C
	cmp r1, r0
	bne _0224109C
_02241098:
	mov r0, #1
	bx lr
_0224109C:
	mov r0, #0
	bx lr

	thumb_func_start MOD12_022410A0
MOD12_022410A0: ; 0x022410A0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xa1
	lsl r0, r0, #4
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _022410B2
	mov r0, #0
	pop {r4, pc}
_022410B2:
	ldrb r0, [r4, #7]
	cmp r0, #0
	bne _022410F0
	ldrb r1, [r4, #6]
	mov r2, #0x21
	lsl r2, r2, #4
	add r0, r4, #0
	add r3, r4, r2
	lsl r1, r1, #9
	add r0, #0x10
	add r1, r3, r1
	sub r2, #0x10
	bl MI_CpuCopy8
	ldrb r0, [r4, #6]
	mov r2, #1
	add r1, r4, r0
	ldr r0, _02241110 ; =0x00000A11
	strb r2, [r1, r0]
	add r0, r4, #0
	add r0, #0x10
	mov r1, #0
	lsl r2, r2, #9
	bl MI_CpuFill8
	mov r0, #0xa1
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	mov r0, #1
	pop {r4, pc}
_022410F0:
	ldrh r2, [r4, #0x10]
	add r1, r4, #0
	mov r0, #0x18
	add r1, #0x10
	bl FUN_02030A78
	cmp r0, #1
	bne _0224110C
	mov r0, #0xa1
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	mov r0, #1
	pop {r4, pc}
_0224110C:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_02241110: .word 0x00000A11

	thumb_func_start MOD12_02241114
MOD12_02241114: ; 0x02241114
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r7, r0, #0
	add r4, r1, #0
	add r0, sp, #0x18
	mov r1, #0
	mov r2, #0x10
	bl MI_CpuFill8
	ldr r0, _022411EC ; =0x00000A11
	mov r6, #0
_0224112A:
	add r1, r7, r6
	ldrb r1, [r1, r0]
	cmp r1, #1
	bne _022411DE
	add r0, r7, #0
	add r1, r6, #0
	add r2, sp, #0x14
	add r3, sp, #0x10
	bl MOD12_02241020
	ldr r2, [sp, #0x14]
	ldrb r0, [r7, #6]
	ldrb r1, [r7, #8]
	ldrb r2, [r2, #4]
	bl MOD12_02241088
	cmp r0, #1
	bne _022411C0
	ldr r2, [sp, #0x14]
	ldrh r1, [r7, #4]
	ldrh r0, [r2, #2]
	str r0, [sp, #8]
	cmp r0, r1
	bhs _022411C0
	ldrb r0, [r2, #6]
	cmp r0, #0
	bne _0224117A
	add r1, r4, #0
	ldr r4, [r7]
	ldr r5, [sp, #8]
	str r4, [sp, #4]
	mov r4, #0xc
	mul r4, r5
	ldr r5, [sp, #4]
	ldr r3, [sp, #0x10]
	add r4, r5, r4
	ldr r4, [r4, #4]
	add r0, r7, #0
	blx r4
	b _022411C0
_0224117A:
	ldr r1, [sp, #8]
	mov r3, #0xc
	ldr r0, [r7]
	mul r3, r1
	add r0, r0, r3
	ldr r0, [r0, #8]
	cmp r0, #0
	beq _022411AE
	ldr r1, [sp, #0x10]
	lsl r0, r6, #2
	add r3, sp, #0x18
	str r1, [r3, r0]
	str r6, [sp]
	add r1, r4, #0
	ldr r4, [r7]
	mov r5, #0xc
	mov ip, r4
	ldrh r4, [r2, #2]
	add r0, r7, #0
	mul r5, r4
	str r5, [sp, #0xc]
	ldr r4, [sp, #0xc]
	mov r5, ip
	add r4, r5, r4
	ldr r4, [r4, #8]
	blx r4
_022411AE:
	ldr r1, [sp, #0x14]
	add r0, r7, #0
	ldrb r1, [r1, #5]
	bl MOD12_02240F24
	ldr r0, _022411F0 ; =0x00000A15
	ldrb r1, [r7, r0]
	add r1, r1, #1
	strb r1, [r7, r0]
_022411C0:
	ldr r0, _022411EC ; =0x00000A11
	mov r1, #0
	add r2, r7, r6
	strb r1, [r2, r0]
	mov r2, #0x21
	lsl r2, r2, #4
	add r3, r7, r2
	lsl r0, r6, #9
	add r0, r3, r0
	sub r2, #0x10
	bl MI_CpuFill8
	add sp, #0x28
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022411DE:
	add r6, r6, #1
	cmp r6, #4
	blt _0224112A
	mov r0, #0
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022411EC: .word 0x00000A11
_022411F0: .word 0x00000A15

	thumb_func_start MOD12_022411F4
MOD12_022411F4: ; 0x022411F4
	cmp r2, r3
	beq _022411FC
	mov r0, #1
	bx lr
_022411FC:
	ldr r2, _0224120C ; =0x00000A15
	ldrb r0, [r0, r2]
	cmp r0, r1
	blt _02241208
	mov r0, #1
	bx lr
_02241208:
	mov r0, #0
	bx lr
	.align 2, 0
_0224120C: .word 0x00000A15

	thumb_func_start MOD12_02241210
MOD12_02241210: ; 0x02241210
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r1, #1
	lsl r1, r1, #0x1a
	ldr r0, [r1]
	ldr r2, _02241454 ; =0xFFFFE0FF
	and r0, r2
	str r0, [r1]
	ldr r0, _02241458 ; =0x04001000
	ldr r3, [r0]
	and r2, r3
	str r2, [r0]
	ldr r3, [r1]
	ldr r2, _0224145C ; =0xFFFF1FFF
	and r3, r2
	str r3, [r1]
	ldr r3, [r0]
	add r1, #0x50
	and r2, r3
	str r2, [r0]
	mov r2, #0
	strh r2, [r1]
	add r0, #0x50
	strh r2, [r0]
	mov r2, #7
	mov r0, #3
	mov r1, #0x18
	lsl r2, r2, #0x10
	bl FUN_0201681C
	mov r1, #0x4a
	add r0, r4, #0
	lsl r1, r1, #6
	mov r2, #0x18
	bl OverlayManager_CreateAndGetData
	mov r2, #0x4a
	mov r1, #0
	lsl r2, r2, #6
	add r5, r0, #0
	bl MI_CpuFill8
	mov r0, #0x18
	bl MOD12_022312D8
	str r0, [r5, #0xc]
	add r0, r4, #0
	bl OverlayManager_GetField18
	mov r1, #0x5b
	str r0, [r5]
	lsl r1, r1, #2
	str r5, [r0, r1]
	ldr r2, [r5]
	mov r3, #3
	add r0, r1, #4
	strb r3, [r2, r0]
	ldr r0, [r5]
	str r0, [r5, #0x10]
	add r0, r5, #0
	bl MOD12_02241B4C
	ldr r0, _02241460 ; =0x0000127F
	mov r1, #0
	strb r1, [r5, r0]
	mov r0, #0x18
	bl FUN_02002FD0
	add r1, r5, #0
	add r1, #0xd0
	str r0, [r1]
	add r0, r5, #0
	add r0, #0xd0
	ldr r0, [r0]
	mov r1, #1
	bl FUN_020038F0
	add r0, r5, #0
	add r0, #0xd0
	mov r2, #2
	ldr r0, [r0]
	mov r1, #0
	lsl r2, r2, #8
	mov r3, #0x18
	bl FUN_02003008
	add r0, r5, #0
	add r0, #0xd0
	mov r1, #1
	ldr r0, [r0]
	lsl r2, r1, #9
	mov r3, #0x18
	bl FUN_02003008
	add r0, r5, #0
	add r0, #0xd0
	mov r2, #7
	ldr r0, [r0]
	mov r1, #2
	lsl r2, r2, #6
	mov r3, #0x18
	bl FUN_02003008
	add r0, r5, #0
	add r0, #0xd0
	mov r2, #2
	ldr r0, [r0]
	mov r1, #3
	lsl r2, r2, #8
	mov r3, #0x18
	bl FUN_02003008
	mov r0, #0x18
	bl FUN_02016B94
	str r0, [r5, #0x30]
	mov r0, #0x40
	mov r1, #0x18
	bl FUN_0201C24C
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	ldr r0, [r5, #0x30]
	bl MOD12_02241864
	bl FUN_0201CC08
	mov r0, #4
	bl FUN_0201CC24
	mov r0, #2
	mov r1, #0x18
	bl FUN_02002C50
	mov r0, #0x18
	bl FUN_0200BB14
	ldr r1, _02241464 ; =MOD12_0224654C
	ldr r2, _02241468 ; =MOD12_02246504
	mov r3, #0x20
	str r0, [r5, #0x28]
	bl FUN_0200BB6C
	ldr r1, _0224146C ; =0x00100010
	mov r0, #1
	bl FUN_02008D44
	mov r0, #1
	bl FUN_02008DDC
	ldr r0, [r5, #0x28]
	bl FUN_0200BB34
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	mov r2, #0x80
	bl FUN_0200BBF0
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	ldr r2, _02241470 ; =MOD12_02246518
	bl FUN_0200BF60
	mov r0, #0x18
	bl FUN_02006D98
	str r0, [r5, #0x14]
	bl MOD12_02241B0C
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0xcc
	mov r3, #0x18
	bl NewMsgDataFromNarc
	add r1, r5, #0
	add r1, #0xc4
	str r0, [r1]
	mov r0, #0x18
	bl ScrStrBufs_new
	add r1, r5, #0
	add r1, #0xc8
	str r0, [r1]
	mov r0, #5
	lsl r0, r0, #6
	mov r1, #0x18
	bl String_ctor
	add r1, r5, #0
	add r1, #0xcc
	str r0, [r1]
	mov r0, #0xa
	mov r1, #0x18
	bl FUN_02011744
	add r1, r5, #0
	add r1, #0xd4
	str r0, [r1]
	add r0, r5, #0
	bl MOD12_02241B90
	add r0, r5, #0
	bl MOD12_02241BA0
	add r0, r5, #0
	bl MOD12_022419D0
	add r0, r5, #0
	bl MOD12_02241B78
	add r0, r5, #0
	bl MOD12_02241B88
	add r0, r5, #0
	bl MOD12_02242454
	bl FUN_02033E74
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r1, #0x18
	str r1, [sp, #8]
	mov r1, #0x21
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, _02241474 ; =MOD12_0224182C
	ldr r2, _02241478 ; =0x00013880
	add r1, r5, #0
	bl FUN_0200CA44
	str r0, [r5, #4]
	mov r0, #0x85
	mov r1, #1
	lsl r0, r0, #4
	strb r1, [r5, r0]
	bl GX_BothDispOn
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	ldr r1, _0224147C ; =0x0000046F
	mov r0, #6
	mov r2, #1
	bl FUN_0200433C
	ldr r1, [r5]
	ldr r0, _02241480 ; =0x00000171
	ldrb r0, [r1, r0]
	bl FUN_020833D4
	ldr r0, _02241484 ; =MOD12_02241754
	add r1, r5, #0
	bl Main_SetVBlankIntrCB
	ldr r0, _02241488 ; =MOD12_02241814
	add r1, r5, #0
	mov r2, #0xa
	bl FUN_0200CA60
	str r0, [r5, #8]
	ldr r0, _0224148C ; =0x000006E5
	bl FUN_020054C8
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02241454: .word 0xFFFFE0FF
_02241458: .word 0x04001000
_0224145C: .word 0xFFFF1FFF
_02241460: .word 0x0000127F
_02241464: .word MOD12_0224654C
_02241468: .word MOD12_02246504
_0224146C: .word 0x00100010
_02241470: .word MOD12_02246518
_02241474: .word MOD12_0224182C
_02241478: .word 0x00013880
_0224147C: .word 0x0000046F
_02241480: .word 0x00000171
_02241484: .word MOD12_02241754
_02241488: .word MOD12_02241814
_0224148C: .word 0x000006E5

	thumb_func_start MOD12_02241490
MOD12_02241490: ; 0x02241490
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_02082878
	ldr r0, [r5]
	cmp r0, #0
	beq _022414B2
	cmp r0, #1
	beq _022414E4
	cmp r0, #2
	beq _0224156C
	b _0224157A
_022414B2:
	bl FUN_0200E308
	cmp r0, #1
	bne _0224157A
	ldr r0, _02241580 ; =MOD12_022417DC
	add r1, r4, #0
	bl FUN_02015F34
	mov r0, #0xff
	str r0, [sp]
	ldr r0, _02241584 ; =0x0000D6D8
	add r1, r4, #0
	str r0, [sp, #4]
	add r1, #0xd0
	ldr r1, [r1]
	ldr r2, _02241588 ; =MOD12_022464F4
	mov r0, #0x18
	mov r3, #8
	bl MOD12_022318A4
	ldr r1, _0224158C ; =0x00000848
	str r0, [r4, r1]
	mov r0, #1
	str r0, [r5]
	b _0224157A
_022414E4:
	ldr r0, [r4]
	bl FUN_020828BC
	cmp r0, #1
	bne _02241540
	ldr r2, _02241590 ; =0x0000084E
	ldr r1, _02241594 ; =0x00001274
	ldrh r2, [r4, r2]
	add r0, r4, #0
	add r1, r4, r1
	lsl r3, r2, #2
	ldr r2, _02241598 ; =MOD12_02246594
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #1
	beq _02241508
	cmp r0, #2
	bne _0224152A
_02241508:
	cmp r0, #1
	bne _02241514
	ldr r0, _02241590 ; =0x0000084E
	ldrh r1, [r4, r0]
	add r1, r1, #1
	b _0224151A
_02241514:
	ldr r0, _0224159C ; =0x00001276
	ldrh r1, [r4, r0]
	ldr r0, _02241590 ; =0x0000084E
_0224151A:
	strh r1, [r4, r0]
	ldr r0, _02241594 ; =0x00001274
	mov r1, #0
	add r0, r4, r0
	mov r2, #8
	bl MI_CpuFill8
	b _02241540
_0224152A:
	cmp r0, #3
	bne _02241540
	mov r0, #2
	str r0, [r5]
	ldr r0, _02241594 ; =0x00001274
	mov r1, #0
	add r0, r4, r0
	mov r2, #8
	bl MI_CpuFill8
	b _0224157A
_02241540:
	ldr r0, _022415A0 ; =0x0000085C
	add r0, r4, r0
	bl MOD12_022410A0
	ldr r0, _022415A0 ; =0x0000085C
	add r1, r4, #0
	add r0, r4, r0
	bl MOD12_02241114
	ldr r0, _022415A4 ; =0x0000127C
	ldrb r1, [r4, r0]
	cmp r1, #1
	bne _0224157A
	mov r1, #2
	sub r0, #8
	str r1, [r5]
	add r0, r4, r0
	mov r1, #0
	mov r2, #8
	bl MI_CpuFill8
	b _0224157A
_0224156C:
	bl FUN_0200E308
	cmp r0, #1
	bne _0224157A
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224157A:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02241580: .word MOD12_022417DC
_02241584: .word 0x0000D6D8
_02241588: .word MOD12_022464F4
_0224158C: .word 0x00000848
_02241590: .word 0x0000084E
_02241594: .word 0x00001274
_02241598: .word MOD12_02246594
_0224159C: .word 0x00001276
_022415A0: .word 0x0000085C
_022415A4: .word 0x0000127C

	thumb_func_start MOD12_022415A8
MOD12_022415A8: ; 0x022415A8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	bl FUN_02012EAC
	add r0, r4, #0
	bl MOD12_02241B80
	add r0, r4, #0
	bl MOD12_02241B8C
	add r0, r4, #0
	bl MOD12_02241B98
	add r0, r4, #0
	bl MOD12_02241BF8
	add r5, r4, #0
	mov r6, #0
	add r5, #0x34
_022415D4:
	add r0, r5, #0
	bl FUN_02019178
	add r6, r6, #1
	add r5, #0x10
	cmp r6, #9
	blt _022415D4
	mov r0, #1
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, [r4, #0x30]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #0x30]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #0x30]
	mov r1, #3
	bl FUN_020178A0
	mov r0, #4
	mov r1, #0
	bl FUN_0201797C
	ldr r0, [r4, #0x30]
	mov r1, #4
	bl FUN_020178A0
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x2c]
	bl FUN_0200C398
	ldr r0, [r4, #0x28]
	bl FUN_0200BD04
	bl FUN_0201C29C
	add r0, r4, #0
	add r0, #0x10
	bl MOD12_022424D4
	ldr r0, [r4, #0x14]
	bl FUN_020072E8
	add r0, r4, #0
	add r0, #0xd4
	ldr r0, [r0]
	bl FUN_020117BC
	mov r0, #2
	bl FUN_02002CF8
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	mov r1, #0
	bl FUN_02003038
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	mov r1, #1
	bl FUN_02003038
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	mov r1, #2
	bl FUN_02003038
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	mov r1, #3
	bl FUN_02003038
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl FUN_02002FEC
	add r0, r4, #0
	add r0, #0xcc
	ldr r0, [r0]
	bl String_dtor
	add r0, r4, #0
	add r0, #0xc8
	ldr r0, [r0]
	bl ScrStrBufs_delete
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	bl DestroyMsgData
	ldr r0, [r4, #0x30]
	bl FreeToHeap
	ldr r0, [r4, #4]
	bl FUN_0200CAB4
	ldr r0, [r4, #8]
	bl FUN_0200CAB4
	ldr r0, [r4, #0xc]
	bl MOD12_02231378
	bl FUN_0201CD04
	add r0, r7, #0
	bl OverlayManager_FreeData
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _02241734 ; =0xFFFF1FFF
	and r1, r0
	str r1, [r2]
	ldr r2, _02241738 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	mov r0, #0x18
	bl FUN_020168D0
	bl FUN_02083404
	mov r1, #5
	mov r2, #2
	ldr r0, _0224173C ; =0x00007FFF
	lsl r1, r1, #0x18
	lsl r2, r2, #8
	bl MIi_CpuClear16
	mov r2, #2
	ldr r0, _0224173C ; =0x00007FFF
	ldr r1, _02241740 ; =0x05000200
	lsl r2, r2, #8
	bl MIi_CpuClear16
	mov r2, #2
	ldr r0, _0224173C ; =0x00007FFF
	ldr r1, _02241744 ; =0x05000400
	lsl r2, r2, #8
	bl MIi_CpuClear16
	mov r2, #2
	ldr r0, _0224173C ; =0x00007FFF
	ldr r1, _02241748 ; =0x05000600
	lsl r2, r2, #8
	bl MIi_CpuClear16
	bl FUN_02033ED0
	ldr r0, _0224174C ; =SDK_OVERLAY_MODULE_08_ID
	bl UnloadOverlayByID
	ldr r0, _02241750 ; =SDK_OVERLAY_MODULE_17_ID
	bl UnloadOverlayByID
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02241734: .word 0xFFFF1FFF
_02241738: .word 0x04001000
_0224173C: .word 0x00007FFF
_02241740: .word 0x05000200
_02241744: .word 0x05000400
_02241748: .word 0x05000600
_0224174C: .word SDK_OVERLAY_MODULE_08_ID
_02241750: .word SDK_OVERLAY_MODULE_17_ID

	thumb_func_start MOD12_02241754
MOD12_02241754: ; 0x02241754
	push {r4, r5, r6, lr}
	add r4, r0, #0
	ldr r0, _022417CC ; =0x00000854
	sub r1, r0, #2
	ldrb r3, [r4, r1]
	sub r1, r0, #3
	ldrb r1, [r4, r1]
	sub r6, r0, #1
	ldrb r6, [r4, r6]
	lsl r2, r1, #8
	mov r1, #0xff
	lsl r1, r1, #8
	and r2, r1
	orr r2, r6
	ldrb r5, [r4, r0]
	ldr r6, _022417D0 ; =0x04000040
	strh r2, [r6]
	lsl r2, r3, #8
	and r2, r1
	orr r2, r5
	strh r2, [r6, #4]
	add r2, r0, #4
	ldrb r5, [r4, r2]
	add r2, r0, #2
	ldrb r3, [r4, r2]
	add r2, r0, #1
	ldrb r2, [r4, r2]
	add r0, r0, #3
	ldrb r0, [r4, r0]
	lsl r2, r2, #8
	and r2, r1
	orr r0, r2
	strh r0, [r6, #2]
	lsl r0, r3, #8
	and r0, r1
	orr r0, r5
	strh r0, [r6, #6]
	ldr r0, [r4, #0x14]
	bl FUN_020081C4
	bl FUN_0201C30C
	bl FUN_0200BC30
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	bl FUN_0200372C
	ldr r0, [r4, #0x30]
	bl FUN_0201AB60
	ldr r3, _022417D4 ; =0x027E0000
	ldr r1, _022417D8 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, r5, r6, pc}
	nop
_022417CC: .word 0x00000854
_022417D0: .word 0x04000040
_022417D4: .word 0x027E0000
_022417D8: .word 0x00003FF8

	thumb_func_start MOD12_022417DC
MOD12_022417DC: ; 0x022417DC
	push {r3, lr}
	ldr r1, _0224180C ; =0x0000127F
	ldrb r0, [r0, r1]
	cmp r0, #1
	bne _02241808
	ldr r0, _02241810 ; =0x04000006
	ldrh r0, [r0]
	cmp r0, #0x90
	blt _022417FC
	cmp r0, #0x98
	bgt _022417FC
	mov r0, #1
	mov r1, #0
	bl FUN_020178BC
	pop {r3, pc}
_022417FC:
	cmp r0, #0x90
	bge _02241808
	mov r0, #1
	mov r1, #2
	bl FUN_020178BC
_02241808:
	pop {r3, pc}
	nop
_0224180C: .word 0x0000127F
_02241810: .word 0x04000006

	thumb_func_start MOD12_02241814
MOD12_02241814: ; 0x02241814
	push {r3, lr}
	ldr r0, _02241828 ; =0x0000127F
	ldrb r0, [r1, r0]
	cmp r0, #1
	bne _02241826
	mov r0, #1
	mov r1, #2
	bl FUN_020178BC
_02241826:
	pop {r3, pc}
	.align 2, 0
_02241828: .word 0x0000127F

	thumb_func_start MOD12_0224182C
MOD12_0224182C: ; 0x0224182C
	push {r4, lr}
	mov r0, #0x85
	add r4, r1, #0
	lsl r0, r0, #4
	ldrb r0, [r4, r0]
	cmp r0, #1
	bne _02241854
	ldr r0, [r4, #0x14]
	bl FUN_02006ED4
	bl MOD08_02215A44
	ldr r0, [r4, #0x2c]
	bl FUN_0200BC1C
	bl FUN_0200BC38
	ldr r0, _02241860 ; =0x04000540
	mov r1, #1
	str r1, [r0]
_02241854:
	ldr r1, [r4, #0x30]
	mov r0, #0x18
	bl FUN_020335F0
	pop {r4, pc}
	nop
_02241860: .word 0x04000540

	thumb_func_start MOD12_02241864
MOD12_02241864: ; 0x02241864
	push {r3, r4, r5, lr}
	sub sp, #0xa8
	add r4, r0, #0
	bl GX_DisableEngineALayers
	ldr r5, _022419BC ; =MOD12_0224656C
	add r3, sp, #0x2c
	mov r2, #5
_02241874:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02241874
	add r0, sp, #0x2c
	bl GX_SetBanks
	mov r1, #6
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x18
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x62
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	mov r1, #0x19
	mov r2, #1
	mov r0, #0
	lsl r1, r1, #0x16
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x66
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	ldr r5, _022419C0 ; =MOD12_022464E4
	add r3, sp, #0x1c
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _022419C4 ; =MOD12_022465C0
	add r3, sp, #0x54
	mov r2, #0xa
_022418D4:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _022418D4
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	add r2, sp, #0x54
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	mov r2, #0
	add r0, r4, #0
	mov r1, #1
	add r3, r2, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #1
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #2
	add r2, sp, #0x70
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #2
	bl FUN_02018744
	mov r2, #0
	add r0, r4, #0
	mov r1, #2
	add r3, r2, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #2
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #3
	add r2, sp, #0x8c
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #3
	bl FUN_02018744
	mov r2, #0
	add r0, r4, #0
	mov r1, #3
	add r3, r2, #0
	bl FUN_020179E0
	mov r1, #3
	add r0, r4, #0
	add r2, r1, #0
	mov r3, #0
	bl FUN_020179E0
	ldr r1, _022419C8 ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #1
	orr r2, r0
	strh r2, [r1]
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r5, _022419CC ; =MOD12_02246530
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
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	mov r2, #0
	add r0, r4, #0
	mov r1, #4
	add r3, r2, #0
	bl FUN_020179E0
	add r0, r4, #0
	mov r1, #4
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	add sp, #0xa8
	pop {r3, r4, r5, pc}
	.align 2, 0
_022419BC: .word MOD12_0224656C
_022419C0: .word MOD12_022464E4
_022419C4: .word MOD12_022465C0
_022419C8: .word 0x04000008
_022419CC: .word MOD12_02246530

	thumb_func_start MOD12_022419D0
MOD12_022419D0: ; 0x022419D0
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x1f
	str r0, [sp, #0x10]
	add r1, r4, #0
	ldr r0, [r4, #0x30]
	add r1, #0x34
	mov r2, #1
	mov r3, #2
	bl FUN_02019064
	mov r2, #1
	add r1, r4, #0
	str r2, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x8b
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x30]
	add r1, #0x44
	mov r3, #6
	bl FUN_02019064
	mov r0, #5
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0xa3
	str r0, [sp, #0x10]
	add r1, r4, #0
	ldr r0, [r4, #0x30]
	add r1, #0x54
	mov r2, #1
	mov r3, #6
	bl FUN_02019064
	mov r0, #9
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0xbb
	str r0, [sp, #0x10]
	add r1, r4, #0
	ldr r0, [r4, #0x30]
	add r1, #0x64
	mov r2, #1
	mov r3, #6
	bl FUN_02019064
	mov r1, #0xd
	str r1, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #0xd3
	str r0, [sp, #0x10]
	add r1, r4, #0
	ldr r0, [r4, #0x30]
	add r1, #0x74
	mov r2, #1
	mov r3, #6
	bl FUN_02019064
	mov r2, #1
	add r1, r4, #0
	str r2, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0xeb
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x30]
	add r1, #0x84
	mov r3, #0x10
	bl FUN_02019064
	mov r0, #5
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	add r0, #0xf6
	str r0, [sp, #0x10]
	add r1, r4, #0
	ldr r0, [r4, #0x30]
	add r1, #0x94
	mov r2, #1
	mov r3, #0x10
	bl FUN_02019064
	mov r0, #9
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _02241B04 ; =0x0000011B
	add r1, r4, #0
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x30]
	add r1, #0xa4
	mov r2, #1
	mov r3, #0x10
	bl FUN_02019064
	mov r1, #0xd
	str r1, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, _02241B08 ; =0x00000133
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x30]
	add r4, #0xb4
	add r1, r4, #0
	mov r2, #1
	mov r3, #0x10
	bl FUN_02019064
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0
_02241B04: .word 0x0000011B
_02241B08: .word 0x00000133

	thumb_func_start MOD12_02241B0C
MOD12_02241B0C: ; 0x02241B0C
	push {r3, r4, r5, lr}
	ldr r3, _02241B44 ; =UNK_021064B8
	mov r0, #2
	mov r1, #0
	ldr r3, [r3]
	lsl r0, r0, #0xe
	add r2, r1, #0
	blx r3
	ldr r3, _02241B48 ; =UNK_021064C0
	mov r1, #0
	add r4, r0, #0
	ldr r3, [r3]
	mov r0, #0x80
	add r2, r1, #0
	blx r3
	add r5, r0, #0
	cmp r4, #0
	bne _02241B34
	bl ErrorHandling
_02241B34:
	cmp r5, #0
	bne _02241B3C
	bl ErrorHandling
_02241B3C:
	bl FUN_02012CC8
	pop {r3, r4, r5, pc}
	nop
_02241B44: .word UNK_021064B8
_02241B48: .word UNK_021064C0

	thumb_func_start MOD12_02241B4C
MOD12_02241B4C: ; 0x02241B4C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	bne _02241B5A
	bl ErrorHandling
_02241B5A:
	mov r1, #0xf3
	mov r5, #0
	mov r0, #3
	lsl r1, r1, #2
_02241B62:
	sub r3, r0, r5
	add r2, r4, r5
	add r5, r5, #1
	strb r3, [r2, r1]
	cmp r5, #4
	blt _02241B62
	add r0, r4, #0
	bl MOD12_02243A20
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_02241B78
MOD12_02241B78: ; 0x02241B78
	ldr r3, _02241B7C ; =MOD12_0224278C
	bx r3
	.align 2, 0
_02241B7C: .word MOD12_0224278C

	thumb_func_start MOD12_02241B80
MOD12_02241B80: ; 0x02241B80
	ldr r3, _02241B84 ; =MOD12_02242A6C
	bx r3
	.align 2, 0
_02241B84: .word MOD12_02242A6C

	thumb_func_start MOD12_02241B88
MOD12_02241B88: ; 0x02241B88
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02241B8C
MOD12_02241B8C: ; 0x02241B8C
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02241B90
MOD12_02241B90: ; 0x02241B90
	ldr r3, _02241B94 ; =MOD12_022426BC
	bx r3
	.align 2, 0
_02241B94: .word MOD12_022426BC

	thumb_func_start MOD12_02241B98
MOD12_02241B98: ; 0x02241B98
	ldr r3, _02241B9C ; =MOD12_02242A18
	bx r3
	.align 2, 0
_02241B9C: .word MOD12_02242A18

	thumb_func_start MOD12_02241BA0
MOD12_02241BA0: ; 0x02241BA0
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x18
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x30]
	mov r0, #0x2d
	mov r1, #0x12
	mov r3, #4
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x18
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x30]
	mov r0, #0x2d
	mov r1, #0x13
	mov r3, #4
	bl FUN_020068C8
	mov r0, #1
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	add r4, #0xd0
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #0x2d
	mov r2, #0x21
	mov r3, #0x18
	bl FUN_020030E8
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_02241BF8
MOD12_02241BF8: ; 0x02241BF8
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02241BFC
MOD12_02241BFC: ; 0x02241BFC
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	ldrh r1, [r7]
	add r4, r0, #0
	cmp r1, #0
	beq _02241C12
	cmp r1, #1
	beq _02241CA0
	cmp r1, #2
	beq _02241CBE
	b _02241CE0
_02241C12:
	bl MOD12_022436D0
	mov r0, #0x13
	ldr r2, [r4]
	mov r5, #0
	lsl r0, r0, #4
_02241C1E:
	ldrb r1, [r2, r0]
	cmp r1, #0
	beq _02241C2C
	add r5, r5, #1
	add r2, #0xc
	cmp r5, #4
	blt _02241C1E
_02241C2C:
	cmp r5, #4
	bne _02241C34
	bl ErrorHandling
_02241C34:
	ldr r0, _02241CE8 ; =0x00000438
	ldr r1, _02241CEC ; =0x00000439
	strb r5, [r4, r0]
	mov r5, #0
	sub r0, #0x67
_02241C3E:
	add r3, r4, r5
	ldrb r2, [r3, r0]
	add r5, r5, #1
	cmp r5, #4
	strb r2, [r3, r1]
	blt _02241C3E
	mov r3, #0
	add r1, r3, #0
	add r2, r4, #0
_02241C50:
	ldr r0, [r4]
	mov r5, #0x4a
	add r0, r0, r1
	lsl r5, r5, #2
	ldrh r6, [r0, r5]
	mov r5, #0xe7
	lsl r5, r5, #2
	strh r6, [r2, r5]
	ldr r5, _02241CF0 ; =0x0000012A
	add r3, r3, #1
	ldrh r6, [r0, r5]
	ldr r5, _02241CF4 ; =0x0000039E
	add r1, #0xc
	strh r6, [r2, r5]
	mov r5, #0x4b
	lsl r5, r5, #2
	ldrh r6, [r0, r5]
	mov r5, #0x3a
	lsl r5, r5, #4
	strh r6, [r2, r5]
	ldr r5, _02241CF8 ; =0x0000012E
	ldrh r6, [r0, r5]
	ldr r5, _02241CFC ; =0x000003A2
	strh r6, [r2, r5]
	mov r5, #0x13
	lsl r5, r5, #4
	ldrh r6, [r0, r5]
	mov r5, #0xe9
	lsl r5, r5, #2
	strh r6, [r2, r5]
	ldr r5, _02241D00 ; =0x00000132
	ldrh r5, [r0, r5]
	ldr r0, _02241D04 ; =0x000003A6
	strh r5, [r2, r0]
	add r2, #0xc
	cmp r3, #4
	blt _02241C50
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
_02241CA0:
	ldr r0, _02241D08 ; =0x0000085C
	mov r3, #0xe7
	lsl r3, r3, #2
	add r0, r4, r0
	add r1, r4, #0
	mov r2, #1
	add r3, r4, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _02241CE4
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _02241CE4
_02241CBE:
	ldr r0, _02241D08 ; =0x0000085C
	ldr r3, [r4]
	add r0, r4, r0
	ldr r4, _02241D0C ; =0x00000127
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02241CE4
	ldrh r0, [r7]
	add r0, r0, #1
	strh r0, [r7]
	b _02241CE4
_02241CE0:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02241CE4:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02241CE8: .word 0x00000438
_02241CEC: .word 0x00000439
_02241CF0: .word 0x0000012A
_02241CF4: .word 0x0000039E
_02241CF8: .word 0x0000012E
_02241CFC: .word 0x000003A2
_02241D00: .word 0x00000132
_02241D04: .word 0x000003A6
_02241D08: .word 0x0000085C
_02241D0C: .word 0x00000127

	thumb_func_start MOD12_02241D10
MOD12_02241D10: ; 0x02241D10
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	beq _02241D22
	cmp r0, #1
	beq _02241D5C
	b _02241D7E
_02241D22:
	ldr r3, _02241D88 ; =0x00000445
	mov r1, #0
	strb r1, [r5, r3]
	add r0, r3, #2
	strb r1, [r5, r0]
	add r0, r3, #1
	strb r1, [r5, r0]
	add r0, r3, #0
	sub r0, #0x79
	ldrb r1, [r5, r0]
	sub r0, r3, #7
	mov r2, #5
	strb r1, [r5, r0]
	sub r0, r3, #1
	mov r1, #1
	strb r1, [r5, r0]
	ldr r0, _02241D8C ; =0x0000085C
	sub r3, #0xf
	add r0, r5, r0
	add r1, r5, #0
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _02241D82
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02241D82
_02241D5C:
	ldr r0, _02241D8C ; =0x0000085C
	ldr r3, [r5]
	add r0, r5, r0
	ldr r5, _02241D90 ; =0x00000127
	sub r2, r5, #4
	ldrb r1, [r3, r5]
	sub r5, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r5]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02241D82
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02241D82
_02241D7E:
	mov r0, #1
	pop {r3, r4, r5, pc}
_02241D82:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02241D88: .word 0x00000445
_02241D8C: .word 0x0000085C
_02241D90: .word 0x00000127

	thumb_func_start MOD12_02241D94
MOD12_02241D94: ; 0x02241D94
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	beq _02241DA6
	cmp r0, #1
	beq _02241DC4
	b _02241DE6
_02241DA6:
	ldr r0, _02241DF0 ; =0x0000085C
	mov r3, #0xe7
	lsl r3, r3, #2
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #6
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _02241DEA
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02241DEA
_02241DC4:
	ldr r0, _02241DF0 ; =0x0000085C
	ldr r3, [r5]
	add r0, r5, r0
	ldr r5, _02241DF4 ; =0x00000127
	sub r2, r5, #4
	ldrb r1, [r3, r5]
	sub r5, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r5]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02241DEA
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02241DEA
_02241DE6:
	mov r0, #1
	pop {r3, r4, r5, pc}
_02241DEA:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02241DF0: .word 0x0000085C
_02241DF4: .word 0x00000127

	thumb_func_start MOD12_02241DF8
MOD12_02241DF8: ; 0x02241DF8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	beq _02241E0E
	cmp r0, #1
	beq _02241E40
	cmp r0, #2
	beq _02241E62
	b _02241E74
_02241E0E:
	ldr r3, _02241E7C ; =0x00000445
	mov r0, #0
	strb r0, [r5, r3]
	mov r1, #1
	add r0, r3, #2
	strb r1, [r5, r0]
	add r0, r3, #1
	strb r1, [r5, r0]
	sub r0, r3, #1
	mov r1, #6
	strb r1, [r5, r0]
	ldr r0, _02241E80 ; =0x0000085C
	sub r3, #0xf
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #5
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _02241E78
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02241E78
_02241E40:
	ldr r0, _02241E80 ; =0x0000085C
	ldr r3, [r5]
	add r0, r5, r0
	ldr r5, _02241E84 ; =0x00000127
	sub r2, r5, #4
	ldrb r1, [r3, r5]
	sub r5, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r5]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02241E78
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02241E78
_02241E62:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	cmp r0, #0x3c
	ble _02241E78
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02241E78
_02241E74:
	mov r0, #1
	pop {r3, r4, r5, pc}
_02241E78:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02241E7C: .word 0x00000445
_02241E80: .word 0x0000085C
_02241E84: .word 0x00000127

	thumb_func_start MOD12_02241E88
MOD12_02241E88: ; 0x02241E88
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r3, r0, #0
	ldrh r0, [r4]
	cmp r0, #4
	bhi _02241F78
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02241EA0: ; jump table
	.short _02241EAA - _02241EA0 - 2 ; case 0
	.short _02241F00 - _02241EA0 - 2 ; case 1
	.short _02241F22 - _02241EA0 - 2 ; case 2
	.short _02241F44 - _02241EA0 - 2 ; case 3
	.short _02241F66 - _02241EA0 - 2 ; case 4
_02241EAA:
	ldr r1, [r3]
	ldr r0, _02241F80 ; =0x00000121
	ldrb r0, [r1, r0]
	cmp r0, #4
	bhi _02241ECA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02241EC0: ; jump table
	.short _02241ECE - _02241EC0 - 2 ; case 0
	.short _02241ECE - _02241EC0 - 2 ; case 1
	.short _02241ECE - _02241EC0 - 2 ; case 2
	.short _02241ECE - _02241EC0 - 2 ; case 3
	.short _02241ECE - _02241EC0 - 2 ; case 4
_02241ECA:
	mov r0, #1
	pop {r3, r4, r5, pc}
_02241ECE:
	ldr r5, _02241F84 ; =0x00000445
	mov r0, #0
	strb r0, [r3, r5]
	mov r1, #1
	add r0, r5, #2
	strb r1, [r3, r0]
	add r0, r5, #1
	strb r1, [r3, r0]
	sub r0, r5, #1
	mov r1, #2
	strb r1, [r3, r0]
	ldr r0, _02241F88 ; =0x0000085C
	sub r5, #0xf
	add r0, r3, r0
	add r1, r3, #0
	mov r2, #5
	add r3, r3, r5
	bl MOD12_02241050
	cmp r0, #1
	bne _02241F7C
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02241F7C
_02241F00:
	ldr r0, _02241F88 ; =0x0000085C
	ldr r5, [r3]
	add r0, r3, r0
	ldr r3, _02241F8C ; =0x00000127
	sub r2, r3, #4
	ldrb r1, [r5, r3]
	sub r3, #0xb
	ldrb r2, [r5, r2]
	ldrb r3, [r5, r3]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02241F7C
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02241F7C
_02241F22:
	ldr r5, _02241F90 ; =0x0000043D
	mov r0, #0
	strb r0, [r3, r5]
	ldr r0, _02241F88 ; =0x0000085C
	sub r5, r5, #7
	add r0, r3, r0
	add r1, r3, #0
	mov r2, #9
	add r3, r3, r5
	bl MOD12_02241050
	cmp r0, #1
	bne _02241F7C
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02241F7C
_02241F44:
	ldr r0, _02241F88 ; =0x0000085C
	ldr r5, [r3]
	add r0, r3, r0
	ldr r3, _02241F8C ; =0x00000127
	sub r2, r3, #4
	ldrb r1, [r5, r3]
	sub r3, #0xb
	ldrb r2, [r5, r2]
	ldrb r3, [r5, r3]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02241F7C
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02241F7C
_02241F66:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	cmp r0, #0x3c
	ble _02241F7C
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02241F7C
_02241F78:
	mov r0, #1
	pop {r3, r4, r5, pc}
_02241F7C:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02241F80: .word 0x00000121
_02241F84: .word 0x00000445
_02241F88: .word 0x0000085C
_02241F8C: .word 0x00000127
_02241F90: .word 0x0000043D

	thumb_func_start MOD12_02241F94
MOD12_02241F94: ; 0x02241F94
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldrh r0, [r5]
	cmp r0, #4
	bhi _022420A0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02241FAC: ; jump table
	.short _02241FB6 - _02241FAC - 2 ; case 0
	.short _02242028 - _02241FAC - 2 ; case 1
	.short _0224204A - _02241FAC - 2 ; case 2
	.short _0224206C - _02241FAC - 2 ; case 3
	.short _0224208E - _02241FAC - 2 ; case 4
_02241FB6:
	ldr r1, [r4]
	ldr r0, _022420A8 ; =0x00000121
	ldrb r0, [r1, r0]
	cmp r0, #6
	bhi _02241FDA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02241FCC: ; jump table
	.short _02241FDA - _02241FCC - 2 ; case 0
	.short _02241FDE - _02241FCC - 2 ; case 1
	.short _02241FDE - _02241FCC - 2 ; case 2
	.short _02241FDA - _02241FCC - 2 ; case 3
	.short _02241FDA - _02241FCC - 2 ; case 4
	.short _02241FDE - _02241FCC - 2 ; case 5
	.short _02241FDE - _02241FCC - 2 ; case 6
_02241FDA:
	mov r0, #1
	pop {r3, r4, r5, pc}
_02241FDE:
	ldr r1, _022420AC ; =0x00000445
	mov r0, #0
	strb r0, [r4, r1]
	mov r2, #1
	add r0, r1, #2
	strb r2, [r4, r0]
	add r0, r1, #1
	strb r2, [r4, r0]
	add r0, r1, #0
	sub r0, #0x79
	ldrb r2, [r4, r0]
	sub r0, r1, #7
	sub r1, #0x79
	strb r2, [r4, r0]
	ldrb r0, [r4, r1]
	bl FUN_020832DC
	ldr r3, _022420B0 ; =0x00000442
	add r0, r0, #1
	strb r0, [r4, r3]
	add r0, r3, #2
	mov r1, #3
	strb r1, [r4, r0]
	ldr r0, _022420B4 ; =0x0000085C
	sub r3, #0xc
	add r0, r4, r0
	add r1, r4, #0
	mov r2, #5
	add r3, r4, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _022420A4
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _022420A4
_02242028:
	ldr r0, _022420B4 ; =0x0000085C
	ldr r3, [r4]
	add r0, r4, r0
	ldr r4, _022420B8 ; =0x00000127
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _022420A4
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _022420A4
_0224204A:
	ldr r3, _022420BC ; =0x0000043D
	mov r0, #1
	strb r0, [r4, r3]
	ldr r0, _022420B4 ; =0x0000085C
	sub r3, r3, #7
	add r0, r4, r0
	add r1, r4, #0
	mov r2, #9
	add r3, r4, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _022420A4
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _022420A4
_0224206C:
	ldr r0, _022420B4 ; =0x0000085C
	ldr r3, [r4]
	add r0, r4, r0
	ldr r4, _022420B8 ; =0x00000127
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _022420A4
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _022420A4
_0224208E:
	ldr r0, [r5, #4]
	add r0, r0, #1
	str r0, [r5, #4]
	cmp r0, #0x5a
	ble _022420A4
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _022420A4
_022420A0:
	mov r0, #1
	pop {r3, r4, r5, pc}
_022420A4:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_022420A8: .word 0x00000121
_022420AC: .word 0x00000445
_022420B0: .word 0x00000442
_022420B4: .word 0x0000085C
_022420B8: .word 0x00000127
_022420BC: .word 0x0000043D

	thumb_func_start MOD12_022420C0
MOD12_022420C0: ; 0x022420C0
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldrh r0, [r5]
	cmp r0, #4
	bls _022420CE
	b _022421D2
_022420CE:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022420DA: ; jump table
	.short _022420E4 - _022420DA - 2 ; case 0
	.short _0224215A - _022420DA - 2 ; case 1
	.short _0224217C - _022420DA - 2 ; case 2
	.short _0224219E - _022420DA - 2 ; case 3
	.short _022421C0 - _022420DA - 2 ; case 4
_022420E4:
	ldr r1, [r4]
	ldr r0, _022421DC ; =0x00000121
	ldrb r0, [r1, r0]
	cmp r0, #8
	bhi _0224210C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022420FA: ; jump table
	.short _02242110 - _022420FA - 2 ; case 0
	.short _0224210C - _022420FA - 2 ; case 1
	.short _02242110 - _022420FA - 2 ; case 2
	.short _0224210C - _022420FA - 2 ; case 3
	.short _0224210C - _022420FA - 2 ; case 4
	.short _0224210C - _022420FA - 2 ; case 5
	.short _0224210C - _022420FA - 2 ; case 6
	.short _02242110 - _022420FA - 2 ; case 7
	.short _02242110 - _022420FA - 2 ; case 8
_0224210C:
	mov r0, #1
	pop {r3, r4, r5, pc}
_02242110:
	ldr r1, _022421E0 ; =0x00000445
	mov r0, #0
	strb r0, [r4, r1]
	mov r2, #1
	add r0, r1, #2
	strb r2, [r4, r0]
	add r0, r1, #1
	strb r2, [r4, r0]
	add r0, r1, #0
	sub r0, #0x79
	ldrb r2, [r4, r0]
	sub r0, r1, #7
	sub r1, #0x79
	strb r2, [r4, r0]
	ldrb r0, [r4, r1]
	bl FUN_020832DC
	ldr r3, _022421E4 ; =0x00000442
	add r0, r0, #1
	strb r0, [r4, r3]
	add r0, r3, #2
	mov r1, #4
	strb r1, [r4, r0]
	ldr r0, _022421E8 ; =0x0000085C
	sub r3, #0xc
	add r0, r4, r0
	add r1, r4, #0
	mov r2, #5
	add r3, r4, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _022421D6
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _022421D6
_0224215A:
	ldr r0, _022421E8 ; =0x0000085C
	ldr r3, [r4]
	add r0, r4, r0
	ldr r4, _022421EC ; =0x00000127
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _022421D6
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _022421D6
_0224217C:
	ldr r3, _022421F0 ; =0x0000043D
	mov r0, #2
	strb r0, [r4, r3]
	ldr r0, _022421E8 ; =0x0000085C
	sub r3, r3, #7
	add r0, r4, r0
	add r1, r4, #0
	mov r2, #9
	add r3, r4, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _022421D6
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _022421D6
_0224219E:
	ldr r0, _022421E8 ; =0x0000085C
	ldr r3, [r4]
	add r0, r4, r0
	ldr r4, _022421EC ; =0x00000127
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _022421D6
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _022421D6
_022421C0:
	ldr r0, [r5, #4]
	add r0, r0, #1
	str r0, [r5, #4]
	cmp r0, #0xf
	ble _022421D6
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _022421D6
_022421D2:
	mov r0, #1
	pop {r3, r4, r5, pc}
_022421D6:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_022421DC: .word 0x00000121
_022421E0: .word 0x00000445
_022421E4: .word 0x00000442
_022421E8: .word 0x0000085C
_022421EC: .word 0x00000127
_022421F0: .word 0x0000043D

	thumb_func_start MOD12_022421F4
MOD12_022421F4: ; 0x022421F4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	beq _02242206
	cmp r0, #1
	beq _02242222
	b _02242244
_02242206:
	ldr r0, _0224224C ; =0x0000085C
	ldr r3, _02242250 ; =0x00000436
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #7
	add r3, r5, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _02242248
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02242248
_02242222:
	ldr r0, _0224224C ; =0x0000085C
	ldr r3, [r5]
	add r0, r5, r0
	ldr r5, _02242254 ; =0x00000127
	sub r2, r5, #4
	ldrb r1, [r3, r5]
	sub r5, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r5]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02242248
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02242248
_02242244:
	mov r0, #1
	pop {r3, r4, r5, pc}
_02242248:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224224C: .word 0x0000085C
_02242250: .word 0x00000436
_02242254: .word 0x00000127

	thumb_func_start MOD12_02242258
MOD12_02242258: ; 0x02242258
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldrh r0, [r5]
	cmp r0, #3
	bhi _02242320
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02242270: ; jump table
	.short _02242278 - _02242270 - 2 ; case 0
	.short _022422C0 - _02242270 - 2 ; case 1
	.short _022422E2 - _02242270 - 2 ; case 2
	.short _022422FE - _02242270 - 2 ; case 3
_02242278:
	ldr r1, _02242328 ; =0x00000445
	mov r0, #0
	strb r0, [r4, r1]
	mov r2, #1
	add r0, r1, #2
	strb r2, [r4, r0]
	add r0, r1, #1
	strb r2, [r4, r0]
	add r0, r1, #0
	sub r0, #0xd
	ldrb r2, [r4, r0]
	sub r0, r1, #7
	sub r1, #0xd
	strb r2, [r4, r0]
	ldrb r0, [r4, r1]
	bl FUN_020832DC
	ldr r3, _0224232C ; =0x00000442
	add r0, r0, #1
	strb r0, [r4, r3]
	add r0, r3, #2
	mov r2, #5
	strb r2, [r4, r0]
	ldr r0, _02242330 ; =0x0000085C
	sub r3, #0xc
	add r0, r4, r0
	add r1, r4, #0
	add r3, r4, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _02242324
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _02242324
_022422C0:
	ldr r0, _02242330 ; =0x0000085C
	ldr r3, [r4]
	add r0, r4, r0
	ldr r4, _02242334 ; =0x00000127
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02242324
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _02242324
_022422E2:
	ldr r0, _02242330 ; =0x0000085C
	ldr r3, _02242338 ; =0x00000436
	add r0, r4, r0
	add r1, r4, #0
	mov r2, #8
	add r3, r4, r3
	bl MOD12_02241050
	cmp r0, #1
	bne _02242324
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _02242324
_022422FE:
	ldr r0, _02242330 ; =0x0000085C
	ldr r3, [r4]
	add r0, r4, r0
	ldr r4, _02242334 ; =0x00000127
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02242324
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	b _02242324
_02242320:
	mov r0, #1
	pop {r3, r4, r5, pc}
_02242324:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02242328: .word 0x00000445
_0224232C: .word 0x00000442
_02242330: .word 0x0000085C
_02242334: .word 0x00000127
_02242338: .word 0x00000436

	thumb_func_start MOD12_0224233C
MOD12_0224233C: ; 0x0224233C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r3, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	beq _0224234E
	cmp r0, #1
	beq _02242386
	b _022423A8
_0224234E:
	ldr r5, _022423B0 ; =0x00000445
	mov r0, #0
	strb r0, [r3, r5]
	add r1, r5, #2
	strb r0, [r3, r1]
	add r1, r5, #1
	strb r0, [r3, r1]
	add r1, r5, #0
	sub r1, #0x79
	ldrb r2, [r3, r1]
	sub r1, r5, #7
	strb r2, [r3, r1]
	sub r1, r5, #1
	strb r0, [r3, r1]
	ldr r0, _022423B4 ; =0x0000085C
	sub r5, #0xf
	add r0, r3, r0
	add r1, r3, #0
	mov r2, #5
	add r3, r3, r5
	bl MOD12_02241050
	cmp r0, #1
	bne _022423AC
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _022423AC
_02242386:
	ldr r0, _022423B4 ; =0x0000085C
	ldr r5, [r3]
	add r0, r3, r0
	ldr r3, _022423B8 ; =0x00000127
	sub r2, r3, #4
	ldrb r1, [r5, r3]
	sub r3, #0xb
	ldrb r2, [r5, r2]
	ldrb r3, [r5, r3]
	bl MOD12_022411F4
	cmp r0, #1
	bne _022423AC
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _022423AC
_022423A8:
	mov r0, #1
	pop {r3, r4, r5, pc}
_022423AC:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_022423B0: .word 0x00000445
_022423B4: .word 0x0000085C
_022423B8: .word 0x00000127

	thumb_func_start MOD12_022423BC
MOD12_022423BC: ; 0x022423BC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r2, r0, #0
	ldrh r0, [r4]
	cmp r0, #0
	beq _022423D2
	cmp r0, #1
	beq _022423EC
	cmp r0, #2
	beq _0224240E
	b _02242428
_022423D2:
	ldr r0, _0224244C ; =0x0000085C
	add r1, r2, #0
	add r0, r2, r0
	mov r2, #0xa
	mov r3, #0
	bl MOD12_02241050
	cmp r0, #1
	bne _02242446
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02242446
_022423EC:
	ldr r0, _0224244C ; =0x0000085C
	ldr r3, [r2]
	ldr r5, _02242450 ; =0x00000127
	add r0, r2, r0
	sub r2, r5, #4
	ldrb r1, [r3, r5]
	sub r5, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r5]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02242446
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02242446
_0224240E:
	ldr r0, _0224244C ; =0x0000085C
	add r1, r2, #0
	add r0, r2, r0
	mov r2, #4
	mov r3, #0
	bl MOD12_02241050
	cmp r0, #1
	bne _02242446
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	b _02242446
_02242428:
	ldr r0, _0224244C ; =0x0000085C
	ldr r3, [r2]
	ldr r4, _02242450 ; =0x00000127
	add r0, r2, r0
	sub r2, r4, #4
	ldrb r1, [r3, r4]
	sub r4, #0xb
	ldrb r2, [r3, r2]
	ldrb r3, [r3, r4]
	bl MOD12_022411F4
	cmp r0, #1
	bne _02242446
	mov r0, #3
	pop {r3, r4, r5, pc}
_02242446:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_0224244C: .word 0x0000085C
_02242450: .word 0x00000127

	thumb_func_start MOD12_02242454
MOD12_02242454: ; 0x02242454
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r7, r5, #0
	mov r4, #0
	add r7, #0xd8
	b _022424C6
_02242462:
	mov r0, #0xf3
	add r1, r5, r4
	lsl r0, r0, #2
	ldrb r6, [r1, r0]
	lsl r0, r6, #4
	add r0, r5, r0
	add r0, #0xd8
	ldr r0, [r0]
	cmp r0, #0
	beq _0224247A
	bl ErrorHandling
_0224247A:
	mov r1, #0x32
	mov r0, #0x18
	lsl r1, r1, #6
	bl AllocFromHeap
	lsl r2, r6, #4
	add r1, r5, r2
	add r1, #0xd8
	str r0, [r1]
	add r0, r7, r2
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #6
	ldr r1, _022424D0 ; =MOD12_02246634
	mul r0, r4
	ldrsh r1, [r1, r0]
	lsl r2, r6, #2
	str r1, [sp, #8]
	ldr r1, _022424D0 ; =MOD12_02246634
	add r0, r1, r0
	mov r1, #2
	ldrsh r1, [r0, r1]
	str r1, [sp, #0xc]
	mov r1, #4
	ldrsh r0, [r0, r1]
	add r1, r4, #0
	str r0, [sp, #0x10]
	ldr r3, [r5, #0x10]
	ldr r0, [r5, #0x14]
	ldr r2, [r3, r2]
	mov r3, #2
	bl FUN_02082E64
	lsl r1, r6, #2
	add r1, r5, r1
	str r0, [r1, #0x18]
	add r4, r4, #1
_022424C6:
	cmp r4, #4
	blt _02242462
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_022424D0: .word MOD12_02246634

	thumb_func_start MOD12_022424D4
MOD12_022424D4: ; 0x022424D4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r6, #0
	add r4, r5, #0
	add r7, r6, #0
_022424DE:
	ldr r0, [r5, #8]
	bl FUN_02007534
	add r0, r4, #0
	add r0, #0xc8
	ldr r0, [r0]
	bl FreeToHeap
	add r0, r4, #0
	add r0, #0xc8
	add r6, r6, #1
	str r7, [r0]
	add r5, r5, #4
	add r4, #0x10
	cmp r6, #4
	blt _022424DE
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD12_02242500
MOD12_02242500: ; 0x02242500
	push {r4, r5, r6, lr}
	sub sp, #8
	add r6, r1, #0
	add r4, r0, #0
	add r5, r2, #0
	cmp r6, #0
	beq _02242516
	cmp r5, #0
	bne _02242516
	bl ErrorHandling
_02242516:
	cmp r6, #3
	bhi _022425EC
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02242526: ; jump table
	.short _022425F0 - _02242526 - 2 ; case 0
	.short _0224252E - _02242526 - 2 ; case 1
	.short _02242552 - _02242526 - 2 ; case 2
	.short _02242596 - _02242526 - 2 ; case 3
_0224252E:
	mov r2, #0x12
	lsl r2, r2, #4
	ldr r3, [r4]
	add r1, r2, #1
	ldrb r0, [r3, r2]
	add r2, #0x51
	ldrb r1, [r3, r1]
	ldrb r2, [r3, r2]
	bl FUN_02083228
	add r4, #0xc8
	add r2, r0, #0
	ldr r0, [r4]
	mov r1, #0
	bl BufferContestMessage
	add sp, #8
	pop {r4, r5, r6, pc}
_02242552:
	ldrb r6, [r5]
	ldr r3, [r4]
	mov r0, #1
	lsl r2, r6, #2
	str r0, [sp]
	mov r0, #2
	add r2, r3, r2
	add r6, r3, r6
	mov r3, #0x42
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r3, r3, #2
	add r0, #0xc8
	add r2, #0xe8
	ldrb r3, [r6, r3]
	ldr r0, [r0]
	ldr r2, [r2]
	mov r1, #0
	bl BufferString
	ldrb r0, [r5]
	ldr r1, [r4, #0x10]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r4, #0xc8
	add r2, r0, #0
	ldr r0, [r4]
	mov r1, #1
	bl BufferBoxMonNickname
	add sp, #8
	pop {r4, r5, r6, pc}
_02242596:
	mov r1, #0
	str r1, [sp]
	mov r3, #1
	str r3, [sp, #4]
	add r0, r4, #0
	add r0, #0xc8
	ldrb r2, [r5, #4]
	ldr r0, [r0]
	bl BufferIntegerAsString
	ldrb r6, [r5]
	ldr r3, [r4]
	mov r1, #1
	lsl r2, r6, #2
	add r2, r3, r2
	add r6, r3, r6
	mov r3, #0x42
	str r1, [sp]
	mov r0, #2
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r3, r3, #2
	add r0, #0xc8
	add r2, #0xe8
	ldrb r3, [r6, r3]
	ldr r0, [r0]
	ldr r2, [r2]
	bl BufferString
	ldrb r0, [r5]
	ldr r1, [r4, #0x10]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_020690E4
	add r4, #0xc8
	add r2, r0, #0
	ldr r0, [r4]
	mov r1, #2
	bl BufferBoxMonNickname
	add sp, #8
	pop {r4, r5, r6, pc}
_022425EC:
	bl ErrorHandling
_022425F0:
	add sp, #8
	pop {r4, r5, r6, pc}

	thumb_func_start MOD12_022425F4
MOD12_022425F4: ; 0x022425F4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r6, r1, #0
	ldr r1, [r5]
	ldr r0, _02242670 ; =0x00000171
	add r7, r2, #0
	ldrb r0, [r1, r0]
	str r3, [sp, #0xc]
	cmp r0, #0
	bne _02242616
	ldr r0, _02242674 ; =0x00001988
	ldr r0, [r1, r0]
	bl Options_GetTextFrameDelay
	add r4, r0, #0
	b _02242618
_02242616:
	mov r4, #1
_02242618:
	add r0, r6, #0
	add r1, r7, #0
	bl NewString_ReadMsgData
	add r6, r0, #0
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x28]
	add r0, r5, #0
	bl MOD12_02242500
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xc8
	add r1, #0xcc
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	add r0, #0x34
	mov r1, #0xff
	bl FillWindowPixelBuffer
	mov r3, #0
	str r3, [sp]
	str r4, [sp, #4]
	add r2, r5, #0
	add r0, r5, #0
	str r3, [sp, #8]
	add r2, #0xcc
	ldr r2, [r2]
	add r0, #0x34
	mov r1, #1
	bl AddTextPrinterParameterized
	mov r1, #0xe6
	lsl r1, r1, #2
	strb r0, [r5, r1]
	add r0, r6, #0
	bl String_dtor
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02242670: .word 0x00000171
_02242674: .word 0x00001988

	thumb_func_start MOD12_02242678
MOD12_02242678: ; 0x02242678
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	cmp r4, #7
	blo _0224268A
	bl ErrorHandling
_0224268A:
	lsl r3, r4, #2
	ldr r2, _022426A4 ; =MOD12_0224664C
	add r0, r5, #0
	ldr r4, _022426A8 ; =MOD12_0224664C + 2
	ldrh r2, [r2, r3]
	str r6, [sp]
	add r5, #0xc4
	ldrb r3, [r4, r3]
	ldr r1, [r5]
	bl MOD12_022425F4
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_022426A4: .word MOD12_0224664C
_022426A8: .word MOD12_0224664C + 2

	thumb_func_start MOD12_022426AC
MOD12_022426AC: ; 0x022426AC
	mov r1, #0xe6
	lsl r1, r1, #2
	ldr r3, _022426B8 ; =FUN_0201BD70
	ldrb r0, [r0, r1]
	bx r3
	nop
_022426B8: .word FUN_0201BD70

	thumb_func_start MOD12_022426BC
MOD12_022426BC: ; 0x022426BC
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x18
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x30]
	mov r0, #0x2d
	mov r1, #0x16
	mov r3, #3
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x18
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x30]
	mov r0, #0x2d
	mov r1, #0x15
	mov r3, #3
	bl FUN_020068C8
	ldr r0, [r5, #0x30]
	mov r1, #1
	bl FUN_02018744
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xd0
	ldr r0, [r0]
	mov r1, #0x2d
	mov r2, #0x22
	mov r3, #0x18
	bl FUN_020030E8
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xd0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xd0
	ldr r0, [r0]
	mov r1, #0x2d
	mov r2, #0x23
	mov r3, #0x18
	bl FUN_020030E8
	ldr r1, [r5]
	ldr r0, _02242784 ; =0x00001988
	ldr r0, [r1, r0]
	bl Options_GetFrame
	add r4, r0, #0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r1, #1
	ldr r0, [r5, #0x30]
	add r2, r1, #0
	mov r3, #0xf
	bl FUN_0200CD68
	add r0, r4, #0
	bl FUN_0200CD64
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xe0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xd0
	ldr r0, [r0]
	mov r1, #0x26
	mov r3, #0x18
	bl FUN_020030E8
	ldr r0, [r5, #0x30]
	mov r1, #2
	bl FUN_02018744
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_02242784: .word 0x00001988

	thumb_func_start MOD12_02242788
MOD12_02242788: ; 0x02242788
	bx lr
	.align 2, 0

	thumb_func_start MOD12_0224278C
MOD12_0224278C: ; 0x0224278C
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	ldr r0, _022427D4 ; =0x000080EA
	add r2, r4, #0
	str r0, [sp]
	sub r3, r0, #1
	str r3, [sp, #4]
	str r3, [sp, #8]
	add r2, #0xd0
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x2c]
	ldr r2, [r2]
	bl MOD12_022316F8
	ldr r0, _022427D4 ; =0x000080EA
	mov r1, #0xc8
	str r0, [sp]
	sub r3, r0, #1
	str r3, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
	mov r0, #3
	str r0, [sp, #0x14]
	ldr r0, _022427D8 ; =0x0000C350
	add r1, #0x50
	str r0, [sp, #0x18]
	add r0, r4, r1
	ldr r1, [r4, #0x28]
	ldr r2, [r4, #0x2c]
	bl MOD12_022317C8
	add sp, #0x1c
	pop {r3, r4, pc}
	.align 2, 0
_022427D4: .word 0x000080EA
_022427D8: .word 0x0000C350

	thumb_func_start MOD12_022427DC
MOD12_022427DC: ; 0x022427DC
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #0x46
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD12_0223185C
	ldr r1, _02242800 ; =0x000080E9
	str r1, [sp]
	ldr r0, [r4, #0x2c]
	add r2, r1, #1
	add r3, r1, #0
	bl MOD12_02231780
	add sp, #4
	pop {r3, r4, pc}
	nop
_02242800: .word 0x000080E9

	thumb_func_start MOD12_02242804
MOD12_02242804: ; 0x02242804
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r6, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x18
	str r0, [sp, #0xc]
	ldr r2, [r6, #0x30]
	mov r0, #0x2d
	mov r1, #0x1a
	mov r3, #3
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r1, #0x18
	str r1, [sp, #0xc]
	ldr r2, [r6, #0x30]
	mov r0, #0x2d
	mov r3, #3
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x18
	str r0, [sp, #0xc]
	ldr r2, [r6, #0x30]
	mov r0, #0x2d
	mov r1, #0x19
	mov r3, #2
	bl FUN_020068C8
	ldr r0, [r6, #0x30]
	mov r1, #1
	bl FUN_02018744
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r6, #0
	add r0, #0xd0
	ldr r0, [r0]
	mov r1, #0x2d
	mov r2, #0x26
	mov r3, #0x18
	bl FUN_020030E8
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xd0
	str r0, [sp, #8]
	add r0, r6, #0
	add r0, #0xd0
	ldr r0, [r0]
	mov r1, #0x2d
	mov r2, #0x23
	mov r3, #0x18
	bl FUN_020030E8
	ldr r1, [r6]
	ldr r0, _022429D0 ; =0x00001988
	ldr r0, [r1, r0]
	bl Options_GetFrame
	add r4, r0, #0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r1, #1
	ldr r0, [r6, #0x30]
	add r2, r1, #0
	mov r3, #0xf
	bl FUN_0200CD68
	add r0, r4, #0
	bl FUN_0200CD64
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xe0
	str r0, [sp, #8]
	add r0, r6, #0
	add r0, #0xd0
	ldr r0, [r0]
	mov r1, #0x26
	mov r3, #0x18
	bl FUN_020030E8
	mov r0, #0xc
	mov r1, #0x18
	bl String_ctor
	add r4, r6, #0
	add r7, r0, #0
	mov r5, #0
	add r4, #0x34
_022428E6:
	mov r0, #0xf3
	add r1, r6, r5
	lsl r0, r0, #2
	ldrb r0, [r1, r0]
	ldr r1, [r6, #0x10]
	add r2, r7, #0
	lsl r0, r0, #2
	str r0, [sp, #0x10]
	ldr r0, [r1, r0]
	mov r1, #0x76
	bl GetMonData
	add r0, r5, #1
	lsl r0, r0, #4
	str r0, [sp, #0x14]
	add r0, r4, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	add r0, r5, #5
	lsl r0, r0, #4
	str r0, [sp, #0x18]
	add r0, r4, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r0, #3
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _022429D4 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x14]
	add r2, r7, #0
	add r0, r4, r0
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	mov r0, #3
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _022429D4 ; =0x00010200
	ldr r2, [sp, #0x10]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r3, [r6]
	ldr r0, [sp, #0x18]
	add r2, r3, r2
	add r2, #0xe8
	mov r1, #0
	ldr r2, [r2]
	add r0, r4, r0
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	add r5, r5, #1
	cmp r5, #4
	blt _022428E6
	add r0, r7, #0
	bl String_dtor
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _022429D8 ; =0xFFFF1FFF
	mov r5, #0x3f
	and r1, r0
	mov r0, #6
	lsl r0, r0, #0xc
	orr r0, r1
	add r1, r2, #0
	add r1, #0x48
	str r0, [r2]
	ldrh r0, [r1]
	mov r3, #0x1f
	bic r0, r5
	add r4, r0, #0
	orr r4, r3
	mov r0, #0x20
	orr r4, r0
	strh r4, [r1]
	ldrh r6, [r1]
	ldr r4, _022429DC ; =0xFFFFC0FF
	lsl r3, r3, #8
	and r4, r6
	orr r4, r3
	lsl r3, r0, #8
	orr r3, r4
	strh r3, [r1]
	add r3, r2, #0
	add r3, #0x4a
	ldrh r4, [r3]
	mov r1, #0x1b
	bic r4, r5
	orr r1, r4
	orr r0, r1
	strh r0, [r3]
	add r0, r2, #0
	mov r3, #0xff
	add r0, #0x40
	strh r3, [r0]
	add r0, r2, #0
	mov r1, #0
	add r0, #0x44
	strh r1, [r0]
	add r0, r2, #0
	add r0, #0x42
	strh r3, [r0]
	add r2, #0x46
	strh r1, [r2]
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022429D0: .word 0x00001988
_022429D4: .word 0x00010200
_022429D8: .word 0xFFFF1FFF
_022429DC: .word 0xFFFFC0FF

	thumb_func_start MOD12_022429E0
MOD12_022429E0: ; 0x022429E0
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r3, #0
	mov r0, #1
	str r3, [sp]
	lsl r0, r0, #8
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	mov r1, #1
	mov r2, #2
	bl FUN_02003914
	mov r3, #0
	mov r0, #1
	str r3, [sp]
	lsl r0, r0, #8
	add r4, #0xd0
	str r0, [sp, #4]
	ldr r0, [r4]
	mov r1, #3
	mov r2, #2
	bl FUN_02003914
	add sp, #8
	pop {r4, pc}

	thumb_func_start MOD12_02242A18
MOD12_02242A18: ; 0x02242A18
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02242A1C
MOD12_02242A1C: ; 0x02242A1C
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0
	mov r0, #0x2e
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, _02242A68 ; =0x000080E9
	mov r1, #2
	str r0, [sp, #0x14]
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	ldr r2, [r4, #0x28]
	ldr r3, [r4, #0x2c]
	bl FUN_0200C0DC
	add r0, r4, #0
	bl MOD12_02242C38
	add r0, r4, #0
	bl MOD12_02242A90
	add r0, r4, #0
	bl MOD12_02242EE0
	add r0, r4, #0
	bl MOD12_02242FF8
	add sp, #0x18
	pop {r4, pc}
	nop
_02242A68: .word 0x000080E9

	thumb_func_start MOD12_02242A6C
MOD12_02242A6C: ; 0x02242A6C
	push {r4, lr}
	add r4, r0, #0
	bl MOD12_02242BCC
	add r0, r4, #0
	bl MOD12_02242F94
	add r0, r4, #0
	bl MOD12_022431F8
	add r0, r4, #0
	bl MOD12_02242C88
	add r0, r4, #0
	bl MOD12_02243074
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_02242A90
MOD12_02242A90: ; 0x02242A90
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	add r5, r0, #0
	bl FUN_0206B888
	mov r1, #0x13
	str r1, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, _02242BB4 ; =0x000080EB
	mov r1, #2
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r0, #0xd0
	ldr r0, [r0]
	ldr r2, [r5, #0x28]
	ldr r3, [r5, #0x2c]
	bl FUN_0200C0DC
	bl FUN_0206B894
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _02242BB8 ; =0x000080EA
	mov r2, #0x13
	str r0, [sp, #4]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	bl FUN_0200C124
	bl FUN_0206B8A0
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _02242BB8 ; =0x000080EA
	mov r2, #0x13
	str r0, [sp, #4]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	bl FUN_0200C13C
	ldr r4, _02242BBC ; =MOD12_0224669C
	add r3, sp, #0x18
	mov r2, #6
_02242AF6:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02242AF6
	ldr r0, [r4]
	mov r7, #0
	str r0, [r3]
	add r6, r7, #0
	add r4, r5, #0
_02242B08:
	ldr r0, [r5]
	ldr r0, [r0, r6]
	bl FUN_0206B6C8
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _02242BB8 ; =0x000080EA
	mov r2, #0x13
	add r0, r7, r0
	str r0, [sp, #8]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	bl FUN_0200C978
	ldr r0, _02242BB8 ; =0x000080EA
	add r2, sp, #0x18
	add r0, r7, r0
	str r0, [sp, #0x2c]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	bl FUN_0200C154
	mov r1, #0x4e
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_0200C5C0
	ldr r0, [r5]
	ldr r0, [r0, r6]
	bl FUN_0206B87C
	add r1, r0, #0
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r0, [r0]
	bl FUN_020202DC
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200C5A8
	add r7, r7, #1
	add r6, r6, #4
	add r4, r4, #4
	cmp r7, #4
	blt _02242B08
	ldr r4, _02242BC0 ; =MOD12_02246614
	mov r6, #0
	mov r7, #2
_02242B7A:
	mov r0, #0xf3
	add r1, r5, r6
	lsl r0, r0, #2
	ldrb r0, [r1, r0]
	ldrsh r2, [r4, r7]
	lsl r0, r0, #2
	add r1, r5, r0
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	ldrsh r1, [r4, r1]
	bl FUN_0200C714
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _02242B7A
	ldr r0, _02242BC4 ; =MOD12_02242C1C
	ldr r2, _02242BC8 ; =0x0000C738
	add r1, r5, #0
	bl FUN_0200CA44
	mov r1, #0x4d
	lsl r1, r1, #2
	str r0, [r5, r1]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
	nop
_02242BB4: .word 0x000080EB
_02242BB8: .word 0x000080EA
_02242BBC: .word MOD12_0224669C
_02242BC0: .word MOD12_02246614
_02242BC4: .word MOD12_02242C1C
_02242BC8: .word 0x0000C738

	thumb_func_start MOD12_02242BCC
MOD12_02242BCC: ; 0x02242BCC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x2c]
	ldr r1, _02242C14 ; =0x000080EA
	bl FUN_0200C378
	ldr r0, [r6, #0x2c]
	ldr r1, _02242C14 ; =0x000080EA
	bl FUN_0200C388
	ldr r0, [r6, #0x2c]
	ldr r1, _02242C18 ; =0x000080EB
	bl FUN_0200C368
	mov r7, #0x4e
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_02242BF0:
	ldr r1, _02242C14 ; =0x000080EA
	ldr r0, [r6, #0x2c]
	add r1, r4, r1
	bl FUN_0200C358
	ldr r0, [r5, r7]
	bl FUN_0200C3DC
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _02242BF0
	mov r0, #0x4d
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_0200CAB4
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02242C14: .word 0x000080EA
_02242C18: .word 0x000080EB

	thumb_func_start MOD12_02242C1C
MOD12_02242C1C: ; 0x02242C1C
	push {r4, r5, r6, lr}
	mov r6, #0x4e
	add r5, r1, #0
	mov r4, #0
	lsl r6, r6, #2
_02242C26:
	ldr r0, [r5, r6]
	bl FUN_0200C5A8
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _02242C26
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD12_02242C38
MOD12_02242C38: ; 0x02242C38
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02242C80 ; =0x000080EF
	mov r2, #0x2e
	str r0, [sp, #8]
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x2c]
	mov r3, #0x51
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _02242C84 ; =0x000080EC
	mov r2, #0x2e
	str r0, [sp, #4]
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x2c]
	mov r3, #0x50
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _02242C84 ; =0x000080EC
	mov r2, #0x2e
	str r0, [sp, #4]
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x2c]
	mov r3, #0x4f
	bl FUN_0200C13C
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_02242C80: .word 0x000080EF
_02242C84: .word 0x000080EC

	thumb_func_start MOD12_02242C88
MOD12_02242C88: ; 0x02242C88
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x2c]
	ldr r1, _02242CA8 ; =0x000080EF
	bl FUN_0200C358
	ldr r0, [r4, #0x2c]
	ldr r1, _02242CAC ; =0x000080EC
	bl FUN_0200C378
	ldr r0, [r4, #0x2c]
	ldr r1, _02242CAC ; =0x000080EC
	bl FUN_0200C388
	pop {r4, pc}
	nop
_02242CA8: .word 0x000080EF
_02242CAC: .word 0x000080EC

	thumb_func_start MOD12_02242CB0
MOD12_02242CB0: ; 0x02242CB0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x18
	mov r1, #8
	bl AllocFromHeap
	mov r1, #0
	mov r2, #8
	add r6, r0, #0
	bl MI_CpuFill8
	str r5, [r6]
	mov r4, #0
_02242CCA:
	add r0, r5, #0
	bl MOD12_02242D3C
	add r4, r4, #1
	cmp r4, #8
	blt _02242CCA
	ldr r0, _02242CE4 ; =MOD12_02242CF8
	ldr r2, _02242CE8 ; =0x0000C35A
	add r1, r6, #0
	bl FUN_0200CA44
	pop {r4, r5, r6, pc}
	nop
_02242CE4: .word MOD12_02242CF8
_02242CE8: .word 0x0000C35A

	thumb_func_start MOD12_02242CEC
MOD12_02242CEC: ; 0x02242CEC
	ldr r1, _02242CF4 ; =0x0000127D
	mov r2, #1
	strb r2, [r0, r1]
	bx lr
	.align 2, 0
_02242CF4: .word 0x0000127D

	thumb_func_start MOD12_02242CF8
MOD12_02242CF8: ; 0x02242CF8
	push {r4, lr}
	add r4, r0, #0
	ldr r3, [r1]
	ldr r0, _02242D38 ; =0x0000127D
	ldrb r2, [r3, r0]
	cmp r2, #1
	bne _02242D14
	add r0, r1, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
	pop {r4, pc}
_02242D14:
	add r0, r0, #1
	ldrb r0, [r3, r0]
	cmp r0, #0x30
	bhs _02242D34
	mov r0, #4
	ldrsh r2, [r1, r0]
	add r2, r2, #1
	strh r2, [r1, #4]
	ldrsh r0, [r1, r0]
	cmp r0, #6
	ble _02242D34
	mov r0, #0
	strh r0, [r1, #4]
	ldr r0, [r1]
	bl MOD12_02242D3C
_02242D34:
	pop {r4, pc}
	nop
_02242D38: .word 0x0000127D

	thumb_func_start MOD12_02242D3C
MOD12_02242D3C: ; 0x02242D3C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x18
	mov r1, #0x20
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x20
	bl MI_CpuFill8
	str r5, [r4]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	ldr r2, _02242DE8 ; =MOD12_02246668
	bl FUN_0200C154
	str r0, [r4, #4]
	ldr r0, [r5]
	bl FUN_02082878
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldr r0, [r5]
	add r6, #0x14
	bl FUN_02082878
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1a
	sub r1, r1, r2
	mov r0, #0x1a
	ror r1, r0
	add r2, r2, r1
	lsl r0, r6, #8
	lsl r1, r6, #0x10
	sub r2, #0x10
	str r0, [r4, #8]
	lsl r0, r2, #8
	str r0, [r4, #0xc]
	lsl r2, r2, #0x10
	ldr r0, [r4, #4]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	ldr r0, [r5]
	bl FUN_02082878
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x18
	sub r1, r1, r2
	mov r0, #0x18
	ror r1, r0
	add r0, r2, r1
	add r0, #0x30
	str r0, [r4, #0x14]
	ldr r0, [r5]
	bl FUN_02082878
	mov r1, #3
	lsl r1, r1, #8
	bl _s32_div_f
	str r1, [r4, #0x18]
	ldr r0, [r5]
	bl FUN_02082878
	mov r1, #0x18
	bl _s32_div_f
	add r1, #0x10
	strh r1, [r4, #0x12]
	ldr r0, [r4, #4]
	bl FUN_0200C5A8
	ldr r0, _02242DEC ; =MOD12_02242DF8
	ldr r2, _02242DF0 ; =0x0000C35B
	add r1, r4, #0
	bl FUN_0200CA44
	ldr r0, _02242DF4 ; =0x0000127E
	ldrb r1, [r5, r0]
	add r1, r1, #1
	strb r1, [r5, r0]
	pop {r4, r5, r6, pc}
	nop
_02242DE8: .word MOD12_02246668
_02242DEC: .word MOD12_02242DF8
_02242DF0: .word 0x0000C35B
_02242DF4: .word 0x0000127E

	thumb_func_start MOD12_02242DF8
MOD12_02242DF8: ; 0x02242DF8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	ldr r1, _02242ED8 ; =0x0000127D
	ldrb r1, [r0, r1]
	cmp r1, #1
	beq _02242E2C
	ldr r2, [r4, #0xc]
	asr r1, r2, #7
	lsr r1, r1, #0x18
	add r1, r2, r1
	asr r1, r1, #8
	cmp r1, #0xd0
	bgt _02242E2C
	mov r2, #0x10
	ldrsh r1, [r4, r2]
	ldr r3, [r4, #8]
	sub r2, #0x20
	add r3, r3, r1
	asr r1, r3, #7
	lsr r1, r1, #0x18
	add r1, r3, r1
	asr r1, r1, #8
	cmp r1, r2
	bge _02242E48
_02242E2C:
	ldr r1, _02242EDC ; =0x0000127E
	ldrb r2, [r0, r1]
	sub r2, r2, #1
	strb r2, [r0, r1]
	ldr r0, [r4, #4]
	bl FUN_0200C3DC
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
_02242E48:
	ldr r2, [r4, #0x1c]
	ldr r1, [r4, #0x18]
	add r0, r4, #0
	add r2, r2, r1
	mov r1, #0x5a
	lsl r1, r1, #0xa
	add r0, #0x1c
	str r2, [r4, #0x1c]
	cmp r2, r1
	blt _02242E62
	ldr r2, [r0]
	sub r1, r2, r1
	str r1, [r0]
_02242E62:
	mov r0, #0x12
	ldrsh r0, [r4, r0]
	ldr r1, [r4, #0x1c]
	lsl r5, r0, #0xc
	asr r0, r1, #7
	lsr r0, r0, #0x18
	add r0, r1, r0
	lsl r0, r0, #8
	lsr r0, r0, #0x10
	bl Sin
	asr r1, r0, #0x1f
	asr r3, r5, #0x1f
	add r2, r5, #0
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r5, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r5, #0xc
	orr r1, r0
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	strh r0, [r4, #0x10]
	ldr r1, [r4, #8]
	ldr r0, [r4, #0x14]
	sub r0, r1, r0
	str r0, [r4, #8]
	ldr r1, [r4, #0xc]
	lsr r0, r2, #2
	add r2, r1, r0
	str r2, [r4, #0xc]
	ldr r3, [r4, #8]
	ldr r0, [r4, #4]
	asr r1, r3, #7
	lsr r1, r1, #0x18
	add r1, r3, r1
	asr r3, r1, #8
	mov r1, #0x10
	ldrsh r1, [r4, r1]
	add r1, r3, r1
	asr r3, r2, #7
	lsr r3, r3, #0x18
	add r3, r2, r3
	lsl r1, r1, #0x10
	lsl r2, r3, #8
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C714
	ldr r0, [r4, #4]
	bl FUN_0200C5A8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02242ED8: .word 0x0000127D
_02242EDC: .word 0x0000127E

	thumb_func_start MOD12_02242EE0
MOD12_02242EE0: ; 0x02242EE0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _02242F84 ; =0x000080EE
	mov r2, #0x2e
	str r0, [sp, #8]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	mov r3, #0x54
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _02242F88 ; =0x000080EB
	mov r2, #0x2e
	str r0, [sp, #4]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	mov r3, #0x53
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _02242F88 ; =0x000080EB
	mov r2, #0x2e
	str r0, [sp, #4]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	mov r3, #0x52
	bl FUN_0200C13C
	mov r7, #0x52
	mov r6, #0
	add r4, r5, #0
	lsl r7, r7, #2
_02242F2C:
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	ldr r2, _02242F8C ; =MOD12_022466D0
	bl FUN_0200C154
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	bl FUN_0200C5A8
	ldr r0, [r4, r7]
	mov r1, #0
	bl FUN_0200C644
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _02242F2C
	ldr r4, _02242F90 ; =MOD12_02246624
	mov r6, #0
	mov r7, #2
_02242F5A:
	mov r0, #0xf3
	add r1, r5, r6
	lsl r0, r0, #2
	ldrb r0, [r1, r0]
	ldrsh r2, [r4, r7]
	lsl r0, r0, #2
	add r1, r5, r0
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	ldrsh r1, [r4, r1]
	bl FUN_0200C714
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _02242F5A
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02242F84: .word 0x000080EE
_02242F88: .word 0x000080EB
_02242F8C: .word MOD12_022466D0
_02242F90: .word MOD12_02246624

	thumb_func_start MOD12_02242F94
MOD12_02242F94: ; 0x02242F94
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x2c]
	ldr r1, _02242FC8 ; =0x000080EE
	bl FUN_0200C358
	ldr r0, [r5, #0x2c]
	ldr r1, _02242FCC ; =0x000080EB
	bl FUN_0200C378
	ldr r0, [r5, #0x2c]
	ldr r1, _02242FCC ; =0x000080EB
	bl FUN_0200C388
	mov r6, #0x52
	mov r4, #0
	lsl r6, r6, #2
_02242FB6:
	ldr r0, [r5, r6]
	bl FUN_0200C3DC
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _02242FB6
	pop {r4, r5, r6, pc}
	nop
_02242FC8: .word 0x000080EE
_02242FCC: .word 0x000080EB

	thumb_func_start MOD12_02242FD0
MOD12_02242FD0: ; 0x02242FD0
	push {r3, r4, r5, lr}
	mov r3, #0x52
	lsl r3, r3, #2
	lsl r4, r1, #2
	add r5, r0, r3
	ldr r0, [r5, r4]
	add r1, r2, #0
	bl FUN_0200C5C0
	ldr r0, [r5, r4]
	mov r1, #1
	bl FUN_0200C644
	ldr r0, _02242FF4 ; =0x000005DD
	bl FUN_020054C8
	pop {r3, r4, r5, pc}
	nop
_02242FF4: .word 0x000005DD

	thumb_func_start MOD12_02242FF8
MOD12_02242FF8: ; 0x02242FF8
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0
	mov r0, #0x2e
	str r0, [sp]
	mov r0, #0xb
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, _02243068 ; =0x000080EC
	mov r1, #2
	str r0, [sp, #0x14]
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	ldr r2, [r4, #0x28]
	ldr r3, [r4, #0x2c]
	bl FUN_0200C0DC
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0224306C ; =0x000080F0
	mov r2, #0x2e
	str r0, [sp, #8]
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x2c]
	mov r3, #0x57
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _02243070 ; =0x000080ED
	mov r2, #0x2e
	str r0, [sp, #4]
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x2c]
	mov r3, #0x56
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _02243070 ; =0x000080ED
	mov r2, #0x2e
	str r0, [sp, #4]
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x2c]
	mov r3, #0x55
	bl FUN_0200C13C
	add sp, #0x18
	pop {r4, pc}
	nop
_02243068: .word 0x000080EC
_0224306C: .word 0x000080F0
_02243070: .word 0x000080ED

	thumb_func_start MOD12_02243074
MOD12_02243074: ; 0x02243074
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x2c]
	ldr r1, _0224309C ; =0x000080EC
	bl FUN_0200C368
	ldr r0, [r4, #0x2c]
	ldr r1, _022430A0 ; =0x000080F0
	bl FUN_0200C358
	ldr r0, [r4, #0x2c]
	ldr r1, _022430A4 ; =0x000080ED
	bl FUN_0200C378
	ldr r0, [r4, #0x2c]
	ldr r1, _022430A4 ; =0x000080ED
	bl FUN_0200C388
	pop {r4, pc}
	nop
_0224309C: .word 0x000080EC
_022430A0: .word 0x000080F0
_022430A4: .word 0x000080ED

	thumb_func_start MOD12_022430A8
MOD12_022430A8: ; 0x022430A8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r7, r0, #0
	str r3, [sp]
	cmp r2, #0
	beq _022430BE
	cmp r2, #1
	beq _022430D2
	cmp r2, #2
	beq _022430EC
	b _0224310C
_022430BE:
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0x56
	lsl r0, r0, #2
	add r2, r7, r0
	mov r0, #0x30
	mul r0, r1
	mov r6, #0
	add r4, r2, r0
	b _02243114
_022430D2:
	lsl r0, r1, #1
	add r2, r7, r0
	ldr r0, _022431F0 ; =0x0000041E
	ldrsh r6, [r2, r0]
	mov r0, #0x11
	str r0, [sp, #0x14]
	mov r0, #0x86
	lsl r0, r0, #2
	add r2, r7, r0
	mov r0, #0x30
	mul r0, r1
	add r4, r2, r0
	b _02243114
_022430EC:
	lsl r0, r1, #1
	add r3, r7, r0
	ldr r0, _022431F0 ; =0x0000041E
	ldrsh r2, [r3, r0]
	add r0, #8
	ldrsh r0, [r3, r0]
	add r6, r2, r0
	mov r0, #0x21
	str r0, [sp, #0x14]
	mov r0, #0xb6
	lsl r0, r0, #2
	add r2, r7, r0
	mov r0, #0x30
	mul r0, r1
	add r4, r2, r0
	b _02243114
_0224310C:
	bl ErrorHandling
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_02243114:
	ldr r0, [sp, #0x30]
	add r6, #0x30
	lsl r0, r0, #5
	str r0, [sp, #0x10]
	add r0, #0x20
	str r0, [sp, #0x10]
	ldr r0, [sp]
	asr r0, r0, #3
	lsr r1, r0, #0x1c
	ldr r0, [sp]
	add r1, r0, r1
	asr r0, r1, #4
	str r0, [sp, #0xc]
	ldr r0, [sp]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1c
	sub r1, r1, r2
	mov r0, #0x1c
	ror r1, r0
	add r0, r2, r1
	beq _02243144
	ldr r0, [sp, #0xc]
	add r0, r0, #1
	str r0, [sp, #0xc]
_02243144:
	ldr r0, [sp, #0xc]
	cmp r0, #0xc
	ble _0224314E
	bl ErrorHandling
_0224314E:
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	cmp r0, #0
	ble _0224317A
	add r5, r4, #0
_0224315A:
	ldr r0, [r5]
	cmp r0, #0
	bne _0224316C
	ldr r0, [r7, #0x28]
	ldr r1, [r7, #0x2c]
	ldr r2, _022431F4 ; =MOD12_02246704
	bl FUN_0200C154
	str r0, [r5]
_0224316C:
	ldr r0, [sp, #8]
	add r5, r5, #4
	add r1, r0, #1
	ldr r0, [sp, #0xc]
	str r1, [sp, #8]
	cmp r1, r0
	blt _0224315A
_0224317A:
	ldr r0, [sp]
	mov r7, #0
	cmp r0, #0x10
	blt _022431A2
	ldr r0, [sp, #0x14]
	add r5, r4, #0
	str r0, [sp, #4]
	add r0, #0xf
	str r0, [sp, #4]
_0224318C:
	ldr r0, [r5]
	ldr r1, [sp, #4]
	bl FUN_0200C5C0
	ldr r0, [sp]
	add r5, r5, #4
	sub r0, #0x10
	add r7, r7, #1
	str r0, [sp]
	cmp r0, #0x10
	bge _0224318C
_022431A2:
	ldr r0, [sp]
	cmp r0, #0
	ble _022431BE
	ldr r0, [sp, #0xc]
	cmp r7, r0
	bge _022431BE
	ldr r2, [sp, #0x14]
	ldr r1, [sp]
	lsl r0, r7, #2
	add r1, r2, r1
	ldr r0, [r4, r0]
	sub r1, r1, #1
	bl FUN_0200C5C0
_022431BE:
	ldr r0, [sp, #0xc]
	mov r5, #0
	cmp r0, #0
	ble _022431EA
	ldr r0, [sp, #0x10]
	lsl r0, r0, #0x10
	asr r7, r0, #0x10
_022431CC:
	lsl r1, r6, #0x10
	ldr r0, [r4]
	asr r1, r1, #0x10
	add r2, r7, #0
	bl FUN_0200C714
	ldr r0, [r4]
	bl FUN_0200C5A8
	ldr r0, [sp, #0xc]
	add r5, r5, #1
	add r6, #0x10
	add r4, r4, #4
	cmp r5, r0
	blt _022431CC
_022431EA:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022431F0: .word 0x0000041E
_022431F4: .word MOD12_02246704

	thumb_func_start MOD12_022431F8
MOD12_022431F8: ; 0x022431F8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r7, #0x86
	lsl r7, r7, #2
	str r0, [sp]
	mov r0, #0
	add r6, r7, #0
	str r0, [sp, #4]
	sub r6, #0xc0
_0224320A:
	ldr r5, [sp]
	mov r4, #0
_0224320E:
	ldr r0, [r5, r6]
	cmp r0, #0
	beq _02243218
	bl FUN_0200C3DC
_02243218:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _02243222
	bl FUN_0200C3DC
_02243222:
	mov r0, #0xb6
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02243230
	bl FUN_0200C3DC
_02243230:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xc
	blt _0224320E
	ldr r0, [sp]
	add r0, #0x30
	str r0, [sp]
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #4
	blt _0224320A
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD12_0224324C
MOD12_0224324C: ; 0x0224324C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	mov r0, #0
	strb r0, [r7]
	mov r0, #0x18
	mov r1, #0x14
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x14
	bl MI_CpuFill8
	str r5, [r4]
	str r7, [r4, #4]
	cmp r6, #0
	ldr r2, _0224329C ; =0x0000A028
	bne _02243286
	mov r0, #6
	lsl r0, r0, #0xc
	str r0, [r4, #8]
	str r0, [r4, #0xc]
	ldr r0, _022432A0 ; =MOD12_022432A8
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
_02243286:
	mov r0, #3
	lsl r0, r0, #0xc
	str r0, [r4, #8]
	mov r0, #9
	lsl r0, r0, #0xc
	str r0, [r4, #0xc]
	ldr r0, _022432A4 ; =MOD12_0224333C
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224329C: .word 0x0000A028
_022432A0: .word MOD12_022432A8
_022432A4: .word MOD12_0224333C

	thumb_func_start MOD12_022432A8
MOD12_022432A8: ; 0x022432A8
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldrb r0, [r1, #0x10]
	cmp r0, #0
	bne _02243322
	mov r0, #1
	ldr r2, [r1, #8]
	lsl r0, r0, #0xa
	sub r2, r2, r0
	str r2, [r1, #8]
	ldr r2, [r1, #0xc]
	add r0, r2, r0
	str r0, [r1, #0xc]
	mov r0, #3
	ldr r2, [r1, #8]
	lsl r0, r0, #0xc
	cmp r2, r0
	bgt _022432DA
	str r0, [r1, #8]
	mov r0, #9
	lsl r0, r0, #0xc
	str r0, [r1, #0xc]
	ldrb r0, [r1, #0x10]
	add r0, r0, #1
	strb r0, [r1, #0x10]
_022432DA:
	ldr r3, [r1]
	ldr r2, _02243338 ; =0x00000851
	mov r0, #0
	strb r0, [r3, r2]
	ldr r3, [r1, #8]
	ldr r4, [r1]
	asr r5, r3, #8
	add r3, r2, #1
	strb r5, [r4, r3]
	ldr r4, [r1]
	mov r5, #0xff
	add r3, r2, #2
	strb r5, [r4, r3]
	ldr r3, [r1, #0xc]
	ldr r4, [r1]
	asr r5, r3, #8
	add r3, r2, #3
	strb r5, [r4, r3]
	ldr r4, [r1]
	mov r5, #1
	add r3, r2, #4
	strb r5, [r4, r3]
	ldr r3, [r1, #8]
	ldr r4, [r1]
	asr r5, r3, #8
	add r3, r2, #5
	strb r5, [r4, r3]
	ldr r4, [r1]
	add r3, r2, #6
	strb r0, [r4, r3]
	ldr r0, [r1, #0xc]
	ldr r1, [r1]
	asr r3, r0, #8
	add r0, r2, #7
	strb r3, [r1, r0]
	pop {r3, r4, r5, pc}
_02243322:
	ldr r0, [r1, #4]
	mov r2, #1
	strb r2, [r0]
	add r0, r1, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	nop
_02243338: .word 0x00000851

	thumb_func_start MOD12_0224333C
MOD12_0224333C: ; 0x0224333C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldrb r0, [r1, #0x10]
	cmp r0, #0
	bne _022433B2
	mov r0, #1
	ldr r2, [r1, #8]
	lsl r0, r0, #0xa
	add r2, r2, r0
	str r2, [r1, #8]
	ldr r2, [r1, #0xc]
	sub r0, r2, r0
	str r0, [r1, #0xc]
	mov r0, #6
	ldr r2, [r1, #8]
	lsl r0, r0, #0xc
	cmp r2, r0
	blt _0224336A
	str r0, [r1, #8]
	str r0, [r1, #0xc]
	ldrb r0, [r1, #0x10]
	add r0, r0, #1
	strb r0, [r1, #0x10]
_0224336A:
	ldr r3, [r1]
	ldr r2, _022433C8 ; =0x00000851
	mov r0, #0
	strb r0, [r3, r2]
	ldr r3, [r1, #8]
	ldr r4, [r1]
	asr r5, r3, #8
	add r3, r2, #1
	strb r5, [r4, r3]
	ldr r4, [r1]
	mov r5, #0xff
	add r3, r2, #2
	strb r5, [r4, r3]
	ldr r3, [r1, #0xc]
	ldr r4, [r1]
	asr r5, r3, #8
	add r3, r2, #3
	strb r5, [r4, r3]
	ldr r4, [r1]
	mov r5, #1
	add r3, r2, #4
	strb r5, [r4, r3]
	ldr r3, [r1, #8]
	ldr r4, [r1]
	asr r5, r3, #8
	add r3, r2, #5
	strb r5, [r4, r3]
	ldr r4, [r1]
	add r3, r2, #6
	strb r0, [r4, r3]
	ldr r0, [r1, #0xc]
	ldr r1, [r1]
	asr r3, r0, #8
	add r0, r2, #7
	strb r3, [r1, r0]
	pop {r3, r4, r5, pc}
_022433B2:
	ldr r0, [r1, #4]
	mov r2, #1
	strb r2, [r0]
	add r0, r1, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	nop
_022433C8: .word 0x00000851

	thumb_func_start MOD12_022433CC
MOD12_022433CC: ; 0x022433CC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r1, #0
	add r0, r3, #0
	strb r1, [r0]
	mov r0, #0x18
	mov r1, #0x14
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x14
	add r4, r0, #0
	bl MI_CpuFill8
	lsl r0, r6, #2
	add r0, r5, r0
	ldr r0, [r0, #0x18]
	cmp r7, #0
	str r0, [r4]
	ldr r0, [sp]
	ldr r2, _0224342C ; =0x0000C350
	str r0, [r4, #4]
	bne _02243416
	mov r0, #0x4a
	lsl r0, r0, #0xa
	str r0, [r4, #8]
	mov r0, #6
	lsl r0, r0, #0xc
	str r0, [r4, #0xc]
	ldr r0, _02243430 ; =MOD12_02243438
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
_02243416:
	mov r0, #2
	lsl r0, r0, #0xe
	str r0, [r4, #8]
	mov r0, #6
	lsl r0, r0, #0xc
	str r0, [r4, #0xc]
	ldr r0, _02243434 ; =MOD12_022434A4
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224342C: .word 0x0000C350
_02243430: .word MOD12_02243438
_02243434: .word MOD12_022434A4

	thumb_func_start MOD12_02243438
MOD12_02243438: ; 0x02243438
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _0224344A
	cmp r0, #1
	beq _0224345A
	b _0224348E
_0224344A:
	ldr r0, [r4]
	mov r1, #6
	mov r2, #0
	bl FUN_02007558
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
_0224345A:
	mov r0, #2
	ldr r1, [r4, #8]
	lsl r0, r0, #0xa
	sub r2, r1, r0
	lsl r1, r0, #4
	str r2, [r4, #8]
	cmp r2, r1
	bgt _02243474
	lsl r0, r0, #4
	str r0, [r4, #8]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
_02243474:
	ldr r2, [r4, #8]
	ldr r0, [r4]
	mov r1, #0
	asr r2, r2, #8
	bl FUN_02007558
	ldr r2, [r4, #0xc]
	ldr r0, [r4]
	mov r1, #1
	asr r2, r2, #8
	bl FUN_02007558
	pop {r3, r4, r5, pc}
_0224348E:
	ldr r0, [r4, #4]
	mov r1, #1
	strb r1, [r0]
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD12_022434A4
MOD12_022434A4: ; 0x022434A4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _022434B6
	cmp r0, #1
	beq _022434BA
	b _022434F0
_022434B6:
	add r0, r0, #1
	strb r0, [r4, #0x10]
_022434BA:
	mov r0, #2
	ldr r1, [r4, #8]
	lsl r0, r0, #0xa
	sub r1, r1, r0
	ldr r0, _02243510 ; =0xFFFFD800
	str r1, [r4, #8]
	cmp r1, r0
	bgt _022434D0
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
_022434D0:
	ldr r3, [r4, #8]
	ldr r0, [r4]
	asr r2, r3, #7
	lsr r2, r2, #0x18
	add r2, r3, r2
	mov r1, #0
	asr r2, r2, #8
	bl FUN_02007558
	ldr r2, [r4, #0xc]
	ldr r0, [r4]
	mov r1, #1
	asr r2, r2, #8
	bl FUN_02007558
	pop {r3, r4, r5, pc}
_022434F0:
	ldr r0, [r4]
	mov r1, #6
	mov r2, #1
	bl FUN_02007558
	ldr r0, [r4, #4]
	mov r1, #1
	strb r1, [r0]
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	nop
_02243510: .word 0xFFFFD800

	thumb_func_start MOD12_02243514
MOD12_02243514: ; 0x02243514
	ldr r2, _022435B0 ; =0x00000121
	ldrb r0, [r0, r2]
	cmp r0, #8
	bhi _022435AA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02243528: ; jump table
	.short _0224353A - _02243528 - 2 ; case 0
	.short _02243552 - _02243528 - 2 ; case 1
	.short _02243568 - _02243528 - 2 ; case 2
	.short _02243586 - _02243528 - 2 ; case 3
	.short _02243586 - _02243528 - 2 ; case 4
	.short _02243592 - _02243528 - 2 ; case 5
	.short _02243592 - _02243528 - 2 ; case 6
	.short _0224359E - _02243528 - 2 ; case 7
	.short _0224359E - _02243528 - 2 ; case 8
_0224353A:
	cmp r1, #0
	beq _02243544
	cmp r1, #2
	beq _02243548
	b _0224354E
_02243544:
	ldr r0, _022435B4 ; =0x00001770
	bx lr
_02243548:
	mov r0, #0xfa
	lsl r0, r0, #4
	bx lr
_0224354E:
	mov r0, #0
	bx lr
_02243552:
	cmp r1, #0
	beq _0224355C
	cmp r1, #1
	beq _02243560
	b _02243564
_0224355C:
	ldr r0, _022435B8 ; =0x00001B58
	bx lr
_02243560:
	ldr r0, _022435BC ; =0x00000BB8
	bx lr
_02243564:
	mov r0, #0
	bx lr
_02243568:
	cmp r1, #0
	beq _02243576
	cmp r1, #1
	beq _0224357A
	cmp r1, #2
	beq _0224357E
	b _02243582
_02243576:
	ldr r0, _022435C0 ; =0x00000D05
	bx lr
_0224357A:
	ldr r0, _022435C0 ; =0x00000D05
	bx lr
_0224357E:
	ldr r0, _022435C0 ; =0x00000D05
	bx lr
_02243582:
	mov r0, #0
	bx lr
_02243586:
	cmp r1, #0
	bne _0224358E
	ldr r0, _022435C4 ; =0x00002710
	bx lr
_0224358E:
	mov r0, #0
	bx lr
_02243592:
	cmp r1, #1
	bne _0224359A
	ldr r0, _022435C4 ; =0x00002710
	bx lr
_0224359A:
	mov r0, #0
	bx lr
_0224359E:
	cmp r1, #2
	bne _022435A6
	ldr r0, _022435C4 ; =0x00002710
	bx lr
_022435A6:
	mov r0, #0
	bx lr
_022435AA:
	mov r0, #0
	bx lr
	nop
_022435B0: .word 0x00000121
_022435B4: .word 0x00001770
_022435B8: .word 0x00001B58
_022435BC: .word 0x00000BB8
_022435C0: .word 0x00000D05
_022435C4: .word 0x00002710

	thumb_func_start MOD12_022435C8
MOD12_022435C8: ; 0x022435C8
	push {r3, lr}
	bl MOD12_02243514
	mov r1, #0xc0
	add r2, r0, #0
	mul r2, r1
	ldr r1, _022435E0 ; =0x00001388
	add r0, r2, r1
	lsl r1, r1, #1
	bl _s32_div_f
	pop {r3, pc}
	.align 2, 0
_022435E0: .word 0x00001388

	thumb_func_start MOD12_022435E4
MOD12_022435E4: ; 0x022435E4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	str r0, [sp]
	mov r0, #0
	ldr r7, [sp]
	add r5, r1, #0
	add r6, r2, #0
	str r0, [sp, #8]
	add r4, sp, #0x24
_022435F6:
	cmp r5, #0
	beq _02243604
	cmp r5, #1
	beq _0224361E
	cmp r5, #2
	beq _02243628
	b _02243630
_02243604:
	ldr r0, [sp]
	ldr r1, [sp, #8]
	bl FUN_02083308
	str r0, [sp, #0x10]
	ldr r0, [sp]
	ldr r1, [sp, #8]
	bl FUN_0208336C
	ldr r1, [sp, #0x10]
	add r0, r1, r0
	str r0, [r4]
	b _02243638
_0224361E:
	mov r0, #0x4b
	lsl r0, r0, #2
	ldrsh r0, [r7, r0]
	str r0, [r4]
	b _02243638
_02243628:
	ldr r0, _022436CC ; =0x0000012E
	ldrsh r0, [r7, r0]
	str r0, [r4]
	b _02243638
_02243630:
	bl ErrorHandling
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
_02243638:
	ldr r0, [sp, #8]
	add r4, r4, #4
	add r0, r0, #1
	add r7, #0xc
	str r0, [sp, #8]
	cmp r0, #4
	blt _022435F6
	mov r4, #0
	mov r3, #1
	add r2, sp, #0x28
	add r7, sp, #0x24
_0224364E:
	lsl r0, r4, #2
	ldr r1, [r7, r0]
	ldr r0, [r2]
	cmp r1, r0
	bge _0224365A
	add r4, r3, #0
_0224365A:
	add r3, r3, #1
	add r2, r2, #4
	cmp r3, #4
	blt _0224364E
	ldr r0, [sp]
	add r1, r5, #0
	bl MOD12_02243514
	lsl r2, r4, #2
	add r1, sp, #0x24
	ldr r1, [r1, r2]
	bl _s32_div_f
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #4]
	add r7, sp, #0x24
	add r4, sp, #0x14
_0224367E:
	ldr r0, [r7]
	ldr r1, [sp, #0xc]
	mul r0, r1
	str r0, [r4]
	add r0, #0x32
	mov r1, #0x64
	bl _s32_div_f
	stmia r4!, {r0}
	ldr r0, [sp, #4]
	add r7, r7, #4
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #4
	blt _0224367E
	mov r2, #0
	add r1, sp, #0x14
_022436A0:
	cmp r5, #0
	beq _022436AE
	cmp r5, #1
	beq _022436B4
	cmp r5, #2
	beq _022436BA
	b _022436BE
_022436AE:
	ldr r0, [r1]
	strh r0, [r6]
	b _022436BE
_022436B4:
	ldr r0, [r1]
	strh r0, [r6]
	b _022436BE
_022436BA:
	ldr r0, [r1]
	strh r0, [r6]
_022436BE:
	add r2, r2, #1
	add r1, r1, #4
	add r6, r6, #2
	cmp r2, #4
	blt _022436A0
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022436CC: .word 0x0000012E

	thumb_func_start MOD12_022436D0
MOD12_022436D0: ; 0x022436D0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	str r0, [sp]
	ldr r0, [r0]
	ldr r1, _022439F0 ; =0x00000121
	ldrb r1, [r0, r1]
	cmp r1, #8
	bhi _02243790
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022436EC: ; jump table
	.short _022436FE - _022436EC - 2 ; case 0
	.short _0224371C - _022436EC - 2 ; case 1
	.short _0224373A - _022436EC - 2 ; case 2
	.short _02243768 - _022436EC - 2 ; case 3
	.short _02243768 - _022436EC - 2 ; case 4
	.short _02243776 - _022436EC - 2 ; case 5
	.short _02243776 - _022436EC - 2 ; case 6
	.short _02243784 - _022436EC - 2 ; case 7
	.short _02243784 - _022436EC - 2 ; case 8
_022436FE:
	ldr r3, _022439F4 ; =0x000003D6
	ldr r2, [sp]
	mov r1, #0
	add r2, r2, r3
	bl MOD12_022435E4
	ldr r0, [sp]
	ldr r3, _022439F8 ; =0x000003E6
	ldr r2, [sp]
	ldr r0, [r0]
	mov r1, #2
	add r2, r2, r3
	bl MOD12_022435E4
	b _02243790
_0224371C:
	ldr r3, _022439F4 ; =0x000003D6
	ldr r2, [sp]
	mov r1, #0
	add r2, r2, r3
	bl MOD12_022435E4
	ldr r0, [sp]
	ldr r3, _022439FC ; =0x000003DE
	ldr r2, [sp]
	ldr r0, [r0]
	mov r1, #1
	add r2, r2, r3
	bl MOD12_022435E4
	b _02243790
_0224373A:
	ldr r3, _022439F4 ; =0x000003D6
	ldr r2, [sp]
	mov r1, #0
	add r2, r2, r3
	bl MOD12_022435E4
	ldr r0, [sp]
	ldr r3, _022439FC ; =0x000003DE
	ldr r2, [sp]
	ldr r0, [r0]
	mov r1, #1
	add r2, r2, r3
	bl MOD12_022435E4
	ldr r0, [sp]
	ldr r3, _022439F8 ; =0x000003E6
	ldr r2, [sp]
	ldr r0, [r0]
	mov r1, #2
	add r2, r2, r3
	bl MOD12_022435E4
	b _02243790
_02243768:
	ldr r3, _022439F4 ; =0x000003D6
	ldr r2, [sp]
	mov r1, #0
	add r2, r2, r3
	bl MOD12_022435E4
	b _02243790
_02243776:
	ldr r3, _022439FC ; =0x000003DE
	ldr r2, [sp]
	mov r1, #1
	add r2, r2, r3
	bl MOD12_022435E4
	b _02243790
_02243784:
	ldr r3, _022439F8 ; =0x000003E6
	ldr r2, [sp]
	mov r1, #2
	add r2, r2, r3
	bl MOD12_022435E4
_02243790:
	ldr r7, _022439F4 ; =0x000003D6
	ldr r6, [sp]
	add r0, r7, #0
	add r1, r7, #0
	mov r5, #0
	add r0, #8
	add r1, #0x18
_0224379E:
	ldr r2, _022439F8 ; =0x000003E6
	ldrsh r3, [r6, r7]
	ldrsh r4, [r6, r2]
	ldrsh r2, [r6, r0]
	add r5, r5, #1
	add r2, r3, r2
	add r2, r4, r2
	strh r2, [r6, r1]
	add r6, r6, #2
	cmp r5, #4
	blt _0224379E
	ldr r1, [sp]
	ldr r4, _022439F4 ; =0x000003D6
	mov r0, #0
	mov r2, #1
	add r1, r1, #2
	add r5, r4, #0
_022437C0:
	ldr r3, [sp]
	lsl r6, r0, #1
	add r3, r3, r6
	ldrsh r6, [r3, r4]
	ldrsh r3, [r1, r5]
	cmp r6, r3
	bge _022437D0
	add r0, r2, #0
_022437D0:
	add r2, r2, #1
	add r1, r1, #2
	cmp r2, #4
	blt _022437C0
	lsl r1, r0, #1
	ldr r0, [sp]
	ldr r4, [sp]
	add r1, r0, r1
	ldr r0, _022439F4 ; =0x000003D6
	mov r5, #0
	add r7, r0, #0
	ldrsh r6, [r1, r0]
	add r7, #0x20
_022437EA:
	ldr r0, _022439F4 ; =0x000003D6
	ldrsh r1, [r4, r0]
	mov r0, #0x64
	mul r0, r1
	add r1, r6, #0
	bl _s32_div_f
	strh r0, [r4, r7]
	add r5, r5, #1
	add r4, r4, #2
	cmp r5, #4
	blt _022437EA
	ldr r0, [sp]
	ldr r4, _022439FC ; =0x000003DE
	mov r2, #0
	mov r1, #1
	add r0, r0, #2
	add r5, r4, #0
_0224380E:
	ldr r3, [sp]
	lsl r6, r2, #1
	add r3, r3, r6
	ldrsh r6, [r3, r4]
	ldrsh r3, [r0, r5]
	cmp r6, r3
	bge _0224381E
	add r2, r1, #0
_0224381E:
	add r1, r1, #1
	add r0, r0, #2
	cmp r1, #4
	blt _0224380E
	ldr r0, [sp]
	lsl r1, r2, #1
	add r1, r0, r1
	ldr r0, _022439FC ; =0x000003DE
	ldr r4, [sp]
	add r7, r0, #0
	ldrsh r6, [r1, r0]
	mov r5, #0
	add r7, #0x20
_02243838:
	ldr r0, _022439FC ; =0x000003DE
	ldrsh r1, [r4, r0]
	mov r0, #0x64
	mul r0, r1
	add r1, r6, #0
	bl _s32_div_f
	strh r0, [r4, r7]
	add r5, r5, #1
	add r4, r4, #2
	cmp r5, #4
	blt _02243838
	ldr r0, [sp]
	ldr r4, _022439F8 ; =0x000003E6
	mov r2, #0
	mov r1, #1
	add r0, r0, #2
	add r5, r4, #0
_0224385C:
	ldr r3, [sp]
	lsl r6, r2, #1
	add r3, r3, r6
	ldrsh r6, [r3, r4]
	ldrsh r3, [r0, r5]
	cmp r6, r3
	bge _0224386C
	add r2, r1, #0
_0224386C:
	add r1, r1, #1
	add r0, r0, #2
	cmp r1, #4
	blt _0224385C
	ldr r0, [sp]
	lsl r1, r2, #1
	add r1, r0, r1
	ldr r0, _022439F8 ; =0x000003E6
	ldr r4, [sp]
	add r7, r0, #0
	ldrsh r6, [r1, r0]
	mov r5, #0
	add r7, #0x20
_02243886:
	ldr r0, _022439F8 ; =0x000003E6
	ldrsh r1, [r4, r0]
	mov r0, #0x64
	mul r0, r1
	add r1, r6, #0
	bl _s32_div_f
	strh r0, [r4, r7]
	add r5, r5, #1
	add r4, r4, #2
	cmp r5, #4
	blt _02243886
	ldr r0, [sp]
	mov r1, #0
	ldr r0, [r0]
	bl MOD12_022435C8
	ldr r4, [sp]
	ldr r7, _02243A00 ; =0x0000041E
	add r6, r0, #0
	mov r5, #0
_022438B0:
	ldr r0, _02243A04 ; =0x000003F6
	mov r1, #0x64
	ldrsh r0, [r4, r0]
	mul r0, r6
	bl _s32_div_f
	strh r0, [r4, r7]
	add r5, r5, #1
	add r4, r4, #2
	cmp r5, #4
	blt _022438B0
	ldr r0, [sp]
	mov r1, #1
	ldr r0, [r0]
	bl MOD12_022435C8
	ldr r4, [sp]
	ldr r7, _02243A08 ; =0x00000426
	add r6, r0, #0
	mov r5, #0
_022438D8:
	ldr r0, _02243A0C ; =0x000003FE
	mov r1, #0x64
	ldrsh r0, [r4, r0]
	mul r0, r6
	bl _s32_div_f
	strh r0, [r4, r7]
	add r5, r5, #1
	add r4, r4, #2
	cmp r5, #4
	blt _022438D8
	ldr r0, [sp]
	mov r1, #2
	ldr r0, [r0]
	bl MOD12_022435C8
	ldr r4, [sp]
	ldr r7, _02243A10 ; =0x0000042E
	add r6, r0, #0
	mov r5, #0
_02243900:
	ldr r0, _02243A14 ; =0x00000406
	mov r1, #0x64
	ldrsh r0, [r4, r0]
	mul r0, r6
	bl _s32_div_f
	strh r0, [r4, r7]
	add r5, r5, #1
	add r4, r4, #2
	cmp r5, #4
	blt _02243900
	ldr r7, _02243A00 ; =0x0000041E
	ldr r5, [sp]
	add r0, r7, #0
	add r1, r7, #0
	mov r6, #0
	add r0, #8
	sub r1, #8
_02243924:
	ldr r2, _02243A10 ; =0x0000042E
	ldrsh r3, [r5, r7]
	ldrsh r4, [r5, r2]
	ldrsh r2, [r5, r0]
	add r6, r6, #1
	add r2, r3, r2
	add r2, r4, r2
	strh r2, [r5, r1]
	add r5, r5, #2
	cmp r6, #4
	blt _02243924
	ldr r0, [sp]
	mov r7, #0
	add r6, sp, #0x18
	str r0, [sp, #4]
	add r4, sp, #8
	add r5, sp, #0x28
_02243946:
	stmia r6!, {r7}
	ldr r1, [sp, #4]
	ldr r0, _02243A18 ; =0x00000416
	ldrsh r0, [r1, r0]
	stmia r4!, {r0}
	ldr r0, [sp]
	ldr r0, [r0]
	bl FUN_02082878
	stmia r5!, {r0}
	ldr r0, [sp, #4]
	add r7, r7, #1
	add r0, r0, #2
	str r0, [sp, #4]
	cmp r7, #4
	blt _02243946
	mov r0, #0
	mov ip, r0
_0224396A:
	mov r0, ip
	mov r7, #3
	cmp r0, #3
	bge _022439B8
	add r2, sp, #0x14
	add r3, sp, #0x34
	add r4, sp, #0x24
_02243978:
	sub r0, r2, #4
	ldr r5, [r2]
	ldr r6, [r0]
	cmp r6, r5
	blt _02243990
	cmp r6, r5
	bne _022439AA
	sub r0, r3, #4
	ldr r1, [r0]
	ldr r0, [r3]
	cmp r1, r0
	bge _022439AA
_02243990:
	str r6, [r2]
	sub r0, r2, #4
	str r5, [r0]
	sub r0, r4, #4
	ldr r5, [r4]
	ldr r1, [r0]
	str r1, [r4]
	str r5, [r0]
	sub r0, r3, #4
	ldr r5, [r3]
	ldr r1, [r0]
	str r1, [r3]
	str r5, [r0]
_022439AA:
	sub r7, r7, #1
	mov r0, ip
	sub r2, r2, #4
	sub r3, r3, #4
	sub r4, r4, #4
	cmp r7, r0
	bgt _02243978
_022439B8:
	mov r0, ip
	add r0, r0, #1
	mov ip, r0
	cmp r0, #3
	blt _0224396A
	mov r1, #0x13
	ldr r7, _02243A1C ; =0x000003D1
	mov r6, #0
	add r5, sp, #0x18
	mov r0, #0xc
	lsl r1, r1, #4
_022439CE:
	ldr r3, [sp]
	ldr r2, [r5]
	add r3, r3, r6
	strb r2, [r3, r7]
	ldr r2, [sp]
	ldr r4, [r2]
	ldr r2, [r5]
	add r5, r5, #4
	add r3, r2, #0
	mul r3, r0
	add r2, r4, r3
	strb r6, [r2, r1]
	add r6, r6, #1
	cmp r6, #4
	blt _022439CE
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022439F0: .word 0x00000121
_022439F4: .word 0x000003D6
_022439F8: .word 0x000003E6
_022439FC: .word 0x000003DE
_02243A00: .word 0x0000041E
_02243A04: .word 0x000003F6
_02243A08: .word 0x00000426
_02243A0C: .word 0x000003FE
_02243A10: .word 0x0000042E
_02243A14: .word 0x00000406
_02243A18: .word 0x00000416
_02243A1C: .word 0x000003D1

	thumb_func_start MOD12_02243A20
MOD12_02243A20: ; 0x02243A20
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r1, _02243A54 ; =MOD12_02246758
	add r3, sp, #0
	str r1, [sp]
	mov r1, #0xb
	strh r1, [r3, #4]
	ldr r1, [r0]
	ldr r2, _02243A58 ; =0x00000123
	ldrb r1, [r1, r2]
	strb r1, [r3, #6]
	sub r1, r2, #7
	ldr r4, [r0]
	add r2, #0x4e
	ldrb r1, [r4, r1]
	strb r1, [r3, #8]
	ldr r1, [r0]
	ldrb r1, [r1, r2]
	strb r1, [r3, #7]
	ldr r1, _02243A5C ; =0x0000085C
	add r0, r0, r1
	add r1, sp, #0
	bl MOD12_02240ED0
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_02243A54: .word MOD12_02246758
_02243A58: .word 0x00000123
_02243A5C: .word 0x0000085C

	thumb_func_start MOD12_02243A60
MOD12_02243A60: ; 0x02243A60
	push {r3, lr}
	lsl r2, r2, #0x10
	mov r3, #0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02243A74
MOD12_02243A74: ; 0x02243A74
	push {r3, lr}
	add r1, r2, #0
	mov r2, #0
	add r3, r2, #0
	bl MOD12_02240FB0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02243A84
MOD12_02243A84: ; 0x02243A84
	bx lr
	.align 2, 0

	thumb_func_start MOD12_02243A88
MOD12_02243A88: ; 0x02243A88
	push {r3, lr}
	mov r1, #0x9a
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02243A9C
MOD12_02243A9C: ; 0x02243A9C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	mov r1, #0xe7
	lsl r1, r1, #2
	str r0, [sp]
	mov ip, r2
	add r0, r3, #0
	add r4, r6, r1
	mov r2, #0x4d
_02243AAE:
	ldrh r1, [r0]
	add r0, r0, #2
	strh r1, [r4]
	add r4, r4, #2
	sub r2, r2, #1
	bne _02243AAE
	mov r1, #0
	ldr r7, _02243B04 ; =0x00000132
	add r2, r1, #0
_02243AC0:
	ldr r0, [r6]
	mov r4, #0x4a
	add r0, r0, r2
	ldrh r5, [r3]
	lsl r4, r4, #2
	add r1, r1, #1
	strh r5, [r0, r4]
	ldrh r5, [r3, #2]
	add r4, r4, #2
	add r2, #0xc
	strh r5, [r0, r4]
	mov r4, #0x4b
	ldrh r5, [r3, #4]
	lsl r4, r4, #2
	strh r5, [r0, r4]
	ldrh r5, [r3, #6]
	add r4, r4, #2
	strh r5, [r0, r4]
	mov r4, #0x13
	ldrh r5, [r3, #8]
	lsl r4, r4, #4
	strh r5, [r0, r4]
	ldrh r4, [r3, #0xa]
	add r3, #0xc
	cmp r1, #4
	strh r4, [r0, r7]
	blt _02243AC0
	mov r2, #0
	ldr r0, [sp]
	mov r1, ip
	add r3, r2, #0
	bl MOD12_02240FB0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02243B04: .word 0x00000132

	thumb_func_start MOD12_02243B08
MOD12_02243B08: ; 0x02243B08
	push {r3, lr}
	lsl r2, r2, #0x10
	mov r3, #0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02243B1C
MOD12_02243B1C: ; 0x02243B1C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x18
	add r7, r1, #0
	add r1, r0, #0
	add r5, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x18
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _02243B58 ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, _02243B5C ; =MOD12_02243B60
	str r6, [r4, #0xc]
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02243B58: .word 0x00007530
_02243B5C: .word MOD12_02243B60

	thumb_func_start MOD12_02243B60
MOD12_02243B60: ; 0x02243B60
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldrb r0, [r1, #0x10]
	str r1, [sp]
	cmp r0, #0
	beq _02243B70
	b _02243C96
_02243B70:
	ldr r0, [sp]
	mov r1, #0x14
	ldrsb r0, [r0, r1]
	cmp r0, #0
	ble _02243B84
	sub r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x14]
	pop {r4, r5, r6, r7, pc}
_02243B84:
	ldr r0, [sp]
	mov r1, #0x13
	ldrsb r0, [r0, r1]
	cmp r0, #0
	ble _02243B98
	sub r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x13]
	pop {r4, r5, r6, r7, pc}
_02243B98:
	ldr r0, [sp]
	mov r1, #1
	strb r1, [r0, #0x13]
	ldr r0, [r0]
	mov r1, #2
	ldr r0, [r0, #0x30]
	bl FUN_0201886C
	mov ip, r0
	mov r0, #0
	str r0, [sp, #8]
	b _02243C10
_02243BB0:
	ldr r0, [sp]
	mov r1, #0x11
	ldrsb r1, [r0, r1]
	ldr r0, _02243CB4 ; =MOD12_02246738
	ldrsb r1, [r0, r1]
	ldr r0, [sp, #8]
	add r0, r1, r0
	bmi _02243C0A
	lsl r1, r0, #6
	mov r0, ip
	add r3, r0, r1
	ldr r0, [sp]
	mov r5, #0
	ldrb r0, [r0, #0x12]
	mov r7, #0x3f
	str r5, [sp, #4]
	lsl r1, r0, #1
	ldr r0, _02243CB8 ; =MOD12_02246740
	lsl r7, r7, #0xa
	ldrh r1, [r0, r1]
	ldr r0, [sp, #8]
	lsl r0, r0, #5
	add r6, r1, r0
	b _02243C04
_02243BE0:
	mov r4, #0
	b _02243BF8
_02243BE4:
	add r0, r5, r4
	lsl r2, r0, #1
	ldrh r0, [r3, r2]
	and r0, r7
	strh r0, [r3, r2]
	ldrh r1, [r3, r2]
	add r0, r6, r4
	add r4, r4, #1
	orr r0, r1
	strh r0, [r3, r2]
_02243BF8:
	cmp r4, #8
	blt _02243BE4
	ldr r0, [sp, #4]
	add r5, #8
	add r0, r0, #1
	str r0, [sp, #4]
_02243C04:
	ldr r0, [sp, #4]
	cmp r0, #4
	blt _02243BE0
_02243C0A:
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
_02243C10:
	ldr r0, [sp, #8]
	cmp r0, #4
	blt _02243BB0
	ldr r0, [sp]
	mov r1, #0x11
	ldrsb r1, [r0, r1]
	cmp r1, #0
	ble _02243C52
	ldrb r0, [r0, #0x12]
	cmp r0, #0
	bne _02243C52
	ldr r0, _02243CB4 ; =MOD12_02246738
	sub r1, r1, #1
	ldrsb r0, [r0, r1]
	lsl r1, r0, #6
	mov r0, ip
	add r3, r0, r1
	mov r0, #0
	mov r1, #0x3f
	str r0, [sp, #4]
	lsl r1, r1, #0xa
	b _02243C4C
_02243C3C:
	ldr r0, [sp, #4]
	lsl r2, r0, #1
	ldrh r0, [r3, r2]
	and r0, r1
	strh r0, [r3, r2]
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
_02243C4C:
	ldr r0, [sp, #4]
	cmp r0, #0x20
	blt _02243C3C
_02243C52:
	ldr r0, [sp]
	mov r1, #2
	ldr r0, [r0]
	ldr r0, [r0, #0x30]
	bl FUN_0201AC68
	ldr r0, [sp]
	ldrb r0, [r0, #0x12]
	add r1, r0, #1
	ldr r0, [sp]
	strb r1, [r0, #0x12]
	ldrb r0, [r0, #0x12]
	cmp r0, #0xc
	blo _02243CB0
	ldr r1, [sp]
	mov r0, #0
	mov r2, #0x11
	strb r0, [r1, #0x12]
	ldrsb r1, [r1, r2]
	add r3, r1, #1
	ldr r1, [sp]
	strb r3, [r1, #0x11]
	strb r0, [r1, #0x14]
	add r0, r1, #0
	ldrsb r0, [r0, r2]
	cmp r0, #5
	blo _02243CB0
	add r0, r1, #0
	ldrb r0, [r0, #0x10]
	add r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x10]
	pop {r4, r5, r6, r7, pc}
_02243C96:
	add r0, r1, #0
	mov r2, #0
	ldr r0, [r0, #0xc]
	add r1, r1, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	ldr r0, [sp]
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_02243CB0:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02243CB4: .word MOD12_02246738
_02243CB8: .word MOD12_02246740

	thumb_func_start MOD12_02243CBC
MOD12_02243CBC: ; 0x02243CBC
	push {r3, lr}
	lsl r2, r2, #0x10
	mov r3, #0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02243CD0
MOD12_02243CD0: ; 0x02243CD0
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x18
	add r7, r1, #0
	add r1, r0, #0
	add r5, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x18
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _02243D0C ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, _02243D10 ; =MOD12_02243D14
	str r6, [r4, #0xc]
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02243D0C: .word 0x00007530
_02243D10: .word MOD12_02243D14

	thumb_func_start MOD12_02243D14
MOD12_02243D14: ; 0x02243D14
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldrb r0, [r1, #0x10]
	str r1, [sp]
	cmp r0, #0
	beq _02243D24
	b _02243E72
_02243D24:
	ldr r0, [sp]
	mov r1, #0x14
	ldrsb r0, [r0, r1]
	cmp r0, #0
	ble _02243D38
	sub r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x14]
	pop {r4, r5, r6, r7, pc}
_02243D38:
	ldr r0, [sp]
	mov r1, #0x13
	ldrsb r0, [r0, r1]
	cmp r0, #0
	ble _02243D4C
	sub r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x13]
	pop {r4, r5, r6, r7, pc}
_02243D4C:
	ldr r0, [sp]
	mov r1, #1
	strb r1, [r0, #0x13]
	ldr r0, [r0]
	mov r1, #2
	ldr r0, [r0, #0x30]
	bl FUN_0201886C
	mov ip, r0
	mov r0, #0
	str r0, [sp, #8]
	b _02243DCC
_02243D64:
	ldr r0, [sp]
	mov r1, #0x11
	ldrsb r1, [r0, r1]
	mov r0, #4
	sub r1, r0, r1
	ldr r0, _02243E90 ; =MOD12_02246738
	ldrsb r1, [r0, r1]
	ldr r0, [sp, #8]
	add r0, r1, r0
	bmi _02243DC6
	lsl r1, r0, #6
	mov r0, ip
	add r3, r0, r1
	ldr r0, [sp]
	mov r5, #0
	ldrb r1, [r0, #0x12]
	mov r0, #0xb
	mov r7, #0x3f
	sub r0, r0, r1
	lsl r1, r0, #1
	ldr r0, _02243E94 ; =MOD12_02246740
	str r5, [sp, #4]
	ldrh r1, [r0, r1]
	ldr r0, [sp, #8]
	lsl r7, r7, #0xa
	lsl r0, r0, #5
	add r6, r1, r0
	b _02243DC0
_02243D9C:
	mov r4, #0
	b _02243DB4
_02243DA0:
	add r0, r5, r4
	lsl r2, r0, #1
	ldrh r0, [r3, r2]
	and r0, r7
	strh r0, [r3, r2]
	ldrh r1, [r3, r2]
	add r0, r6, r4
	add r4, r4, #1
	orr r0, r1
	strh r0, [r3, r2]
_02243DB4:
	cmp r4, #8
	blt _02243DA0
	ldr r0, [sp, #4]
	add r5, #8
	add r0, r0, #1
	str r0, [sp, #4]
_02243DC0:
	ldr r0, [sp, #4]
	cmp r0, #4
	blt _02243D9C
_02243DC6:
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
_02243DCC:
	ldr r0, [sp, #8]
	cmp r0, #4
	blt _02243D64
	ldr r0, [sp]
	mov r1, #0x11
	ldrsb r1, [r0, r1]
	cmp r1, #0
	ble _02243E2E
	ldrb r0, [r0, #0x12]
	cmp r0, #0
	bne _02243E2E
	mov r0, #5
	sub r1, r0, r1
	ldr r0, _02243E90 ; =MOD12_02246738
	mov r7, #0x3f
	ldrsb r0, [r0, r1]
	lsl r7, r7, #0xa
	mov r6, #0x1d
	add r0, r0, #3
	lsl r1, r0, #6
	mov r0, ip
	add r3, r0, r1
	mov r0, #0
	mov r1, #2
	str r0, [sp, #4]
	lsl r1, r1, #8
	b _02243E28
_02243E02:
	ldr r0, [sp, #4]
	ldr r5, [sp, #4]
	lsl r4, r0, #1
	ldrh r0, [r3, r4]
	lsl r5, r5, #0x1d
	and r0, r7
	strh r0, [r3, r4]
	ldr r0, [sp, #4]
	ldrh r2, [r3, r4]
	lsr r0, r0, #0x1f
	sub r5, r5, r0
	ror r5, r6
	add r0, r0, r5
	add r0, r0, r1
	orr r0, r2
	strh r0, [r3, r4]
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
_02243E28:
	ldr r0, [sp, #4]
	cmp r0, #0x20
	blt _02243E02
_02243E2E:
	ldr r0, [sp]
	mov r1, #2
	ldr r0, [r0]
	ldr r0, [r0, #0x30]
	bl FUN_0201AC68
	ldr r0, [sp]
	ldrb r0, [r0, #0x12]
	add r1, r0, #1
	ldr r0, [sp]
	strb r1, [r0, #0x12]
	ldrb r0, [r0, #0x12]
	cmp r0, #0xc
	blo _02243E8C
	ldr r1, [sp]
	mov r0, #0
	mov r2, #0x11
	strb r0, [r1, #0x12]
	ldrsb r1, [r1, r2]
	add r3, r1, #1
	ldr r1, [sp]
	strb r3, [r1, #0x11]
	strb r0, [r1, #0x14]
	add r0, r1, #0
	ldrsb r0, [r0, r2]
	cmp r0, #5
	blo _02243E8C
	add r0, r1, #0
	ldrb r0, [r0, #0x10]
	add r1, r0, #1
	ldr r0, [sp]
	add sp, #0xc
	strb r1, [r0, #0x10]
	pop {r4, r5, r6, r7, pc}
_02243E72:
	add r0, r1, #0
	mov r2, #0
	ldr r0, [r0, #0xc]
	add r1, r1, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	ldr r0, [sp]
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_02243E8C:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02243E90: .word MOD12_02246738
_02243E94: .word MOD12_02246740

	thumb_func_start MOD12_02243E98
MOD12_02243E98: ; 0x02243E98
	push {r3, lr}
	lsl r2, r2, #0x10
	mov r3, #0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02243EAC
MOD12_02243EAC: ; 0x02243EAC
	push {r4, lr}
	ldr r3, _02243EC0 ; =0x0000127C
	mov r4, #1
	strb r4, [r1, r3]
	add r1, r2, #0
	mov r2, #0
	add r3, r2, #0
	bl MOD12_02240FB0
	pop {r4, pc}
	.align 2, 0
_02243EC0: .word 0x0000127C

	thumb_func_start MOD12_02243EC4
MOD12_02243EC4: ; 0x02243EC4
	push {r3, lr}
	mov r1, #0x12
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02243ED8
MOD12_02243ED8: ; 0x02243ED8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	str r1, [sp]
	mov r0, #0x18
	mov r1, #0x20
	add r6, r2, #0
	add r5, r3, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x20
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp]
	ldr r2, _02243F38 ; =0x00007530
	str r0, [r4]
	ldrh r0, [r6]
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r6, #2]
	strh r0, [r4, #6]
	ldrh r0, [r6, #4]
	strh r0, [r4, #8]
	ldrh r0, [r6, #6]
	strh r0, [r4, #0xa]
	str r7, [r4, #0xc]
	ldrb r0, [r5]
	strb r0, [r4, #0x11]
	ldrh r0, [r5, #8]
	strh r0, [r4, #0x14]
	ldrh r0, [r5, #0xa]
	strh r0, [r4, #0x16]
	ldrh r0, [r5, #0xc]
	strh r0, [r4, #0x18]
	ldrb r0, [r5, #0xe]
	strb r0, [r4, #0x1a]
	ldrb r0, [r5, #0x11]
	strb r0, [r4, #0x1d]
	ldrb r0, [r5, #0x10]
	strb r0, [r4, #0x1c]
	ldrb r0, [r5, #0xf]
	strb r0, [r4, #0x1b]
	ldr r0, _02243F3C ; =MOD12_02243F40
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02243F38: .word 0x00007530
_02243F3C: .word MOD12_02243F40

	thumb_func_start MOD12_02243F40
MOD12_02243F40: ; 0x02243F40
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _02243F56
	cmp r0, #1
	beq _02243F94
	cmp r0, #2
	beq _02243FA6
	b _02243FDE
_02243F56:
	ldrb r0, [r4, #0x1a]
	cmp r0, #0
	beq _02243F8E
	ldrb r0, [r4, #0x1d]
	cmp r0, #0
	bne _02243F7A
	ldr r0, [r4]
	mov r1, #1
	add r0, #0x34
	add r2, r1, #0
	mov r3, #0xe
	bl FUN_0200D0BC
	ldr r0, [r4]
	mov r1, #1
	ldr r0, [r0, #0x30]
	bl FUN_0201AC68
_02243F7A:
	ldrb r1, [r4, #0x1a]
	add r2, r4, #0
	ldr r0, [r4]
	add r2, #0x14
	bl MOD12_02242678
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02243F8E:
	mov r0, #0x64
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02243F94:
	ldr r0, [r4]
	bl MOD12_022426AC
	cmp r0, #0
	bne _02243FF6
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02243FA6:
	ldrb r0, [r4, #0x12]
	add r0, r0, #1
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x1c]
	cmp r0, #1
	bne _02243FBA
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02243FBA:
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x1b]
	cmp r1, r0
	blo _02243FF6
	ldr r0, [r4]
	mov r1, #1
	add r0, #0x34
	bl FUN_0200D0E0
	ldr r0, [r4]
	mov r1, #1
	ldr r0, [r0, #0x30]
	bl FUN_0201AC68
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02243FDE:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02243FF6:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_02243FF8
MOD12_02243FF8: ; 0x02243FF8
	push {r3, lr}
	mov r1, #0x9a
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0224400C
MOD12_0224400C: ; 0x0224400C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r0, #0xe7
	add r6, r1, #0
	lsl r0, r0, #2
	add r5, r2, #0
	add r2, r6, r0
	mov r1, #0x4d
_0224401C:
	ldrh r0, [r3]
	add r3, r3, #2
	strh r0, [r2]
	add r2, r2, #2
	sub r1, r1, #1
	bne _0224401C
	mov r0, #0x18
	mov r1, #0x14
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x14
	bl MI_CpuFill8
	str r6, [r4]
	ldrh r0, [r5]
	mov r2, #0xfa
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	lsl r2, r2, #2
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, _0224405C ; =MOD12_02244060
	str r7, [r4, #0xc]
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224405C: .word MOD12_02244060

	thumb_func_start MOD12_02244060
MOD12_02244060: ; 0x02244060
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #6
	bls _02244070
	b _0224419A
_02244070:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224407C: ; jump table
	.short _0224408A - _0224407C - 2 ; case 0
	.short _0224409E - _0224407C - 2 ; case 1
	.short _022440B2 - _0224407C - 2 ; case 2
	.short _022440DC - _0224407C - 2 ; case 3
	.short _022440EE - _0224407C - 2 ; case 4
	.short _0224415A - _0224407C - 2 ; case 5
	.short _02244182 - _0224407C - 2 ; case 6
_0224408A:
	ldr r1, [r4]
	ldr r0, _022441B8 ; =0x00000848
	ldr r0, [r1, r0]
	bl MOD12_022318DC
	ldrb r0, [r4, #0x10]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, r6, r7, pc}
_0224409E:
	bl MOD12_022318F8
	cmp r0, #1
	beq _022440A8
	b _022441B2
_022440A8:
	ldrb r0, [r4, #0x10]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, r6, r7, pc}
_022440B2:
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldr r0, _022441BC ; =0x0000046F
	mov r1, #0x1e
	bl FUN_02005350
	ldrb r0, [r4, #0x10]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, r6, r7, pc}
_022440DC:
	bl FUN_0200E308
	cmp r0, #1
	bne _022441B2
	ldrb r0, [r4, #0x10]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, r6, r7, pc}
_022440EE:
	ldr r0, [r4]
	bl MOD12_02242788
	ldr r0, [r4]
	bl MOD12_022427DC
	ldr r0, [r4]
	bl MOD12_02242804
	ldr r0, [r4]
	bl MOD12_02242A1C
	ldr r0, [r4]
	bl MOD12_022429E0
	ldr r0, [r4]
	mov r1, #0
	add r0, #0x34
	mov r2, #1
	mov r3, #0xe
	bl FUN_0200D0BC
	ldr r0, [r4]
	mov r1, #0xff
	add r0, #0x34
	bl FillWindowPixelBuffer
	ldr r0, [r4]
	add r0, #0x34
	bl CopyWindowToVram
	mov r6, #0
	add r5, r6, #0
	mov r7, #6
_02244132:
	ldr r0, [r4]
	add r1, r7, #0
	add r0, r0, r5
	ldr r0, [r0, #0x18]
	mov r2, #1
	bl FUN_02007558
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #4
	blt _02244132
	ldr r1, [r4]
	ldr r0, _022441C0 ; =0x0000127F
	mov r2, #1
	strb r2, [r1, r0]
	ldrb r0, [r4, #0x10]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, r6, r7, pc}
_0224415A:
	bl FUN_02005404
	cmp r0, #0
	bne _022441B2
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldrb r0, [r4, #0x10]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, r6, r7, pc}
_02244182:
	bl FUN_0200E308
	cmp r0, #1
	bne _022441B2
	ldr r0, _022441C4 ; =0x0000049D
	bl FUN_0200521C
	ldrb r0, [r4, #0x10]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, r6, r7, pc}
_0224419A:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_022441B2:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_022441B8: .word 0x00000848
_022441BC: .word 0x0000046F
_022441C0: .word 0x0000127F
_022441C4: .word 0x0000049D

	thumb_func_start MOD12_022441C8
MOD12_022441C8: ; 0x022441C8
	push {r3, lr}
	mov r1, #0x12
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_022441DC
MOD12_022441DC: ; 0x022441DC
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r0, #0x18
	str r1, [sp]
	add r1, r0, #0
	add r6, r2, #0
	add r5, r3, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x18
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp]
	mov r2, #0
	str r0, [r4]
	ldrh r0, [r6]
	strh r0, [r4, #4]
	ldrh r0, [r6, #2]
	strh r0, [r4, #6]
	ldrh r0, [r6, #4]
	strh r0, [r4, #8]
	ldrh r0, [r6, #6]
	strh r0, [r4, #0xa]
	str r7, [r4, #0xc]
_02244210:
	add r0, r5, r2
	ldrb r1, [r0, #3]
	add r0, r4, r2
	add r2, r2, #1
	strb r1, [r0, #0x11]
	cmp r2, #4
	blt _02244210
	ldr r0, _0224422C ; =MOD12_02244234
	ldr r2, _02244230 ; =0x00007530
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224422C: .word MOD12_02244234
_02244230: .word 0x00007530

	thumb_func_start MOD12_02244234
MOD12_02244234: ; 0x02244234
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #4
	bhi _022442A6
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224424C: ; jump table
	.short _02244256 - _0224424C - 2 ; case 0
	.short _0224425C - _0224424C - 2 ; case 1
	.short _0224427A - _0224424C - 2 ; case 2
	.short _02244294 - _0224424C - 2 ; case 3
	.short _022442A6 - _0224424C - 2 ; case 4
_02244256:
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0224425C:
	ldrb r1, [r4, #0x15]
	mov r0, #3
	sub r2, r0, r1
	add r1, r4, r2
	ldrb r1, [r1, #0x11]
	ldr r0, [r4]
	bl MOD12_02242FD0
	ldrb r0, [r4, #0x15]
	add r0, r0, #1
	strb r0, [r4, #0x15]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0224427A:
	mov r0, #0x16
	ldrsh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, #0x16]
	ldrsh r0, [r4, r0]
	cmp r0, #0x1e
	ble _022442BE
	mov r0, #0
	strh r0, [r4, #0x16]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_02244294:
	ldrb r1, [r4, #0x15]
	cmp r1, #4
	bhs _022442A0
	mov r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_022442A0:
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_022442A6:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_022442BE:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD12_022442C0
MOD12_022442C0: ; 0x022442C0
	push {r3, lr}
	mov r1, #0x12
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_022442D4
MOD12_022442D4: ; 0x022442D4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x18
	add r7, r1, #0
	add r1, r0, #0
	add r5, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x18
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _02244318 ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, [sp]
	str r6, [r4, #0xc]
	ldrb r0, [r0, #2]
	strb r0, [r4, #0x11]
	ldr r0, _0224431C ; =MOD12_02244320
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02244318: .word 0x00007530
_0224431C: .word MOD12_02244320

	thumb_func_start MOD12_02244320
MOD12_02244320: ; 0x02244320
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #6
	bhi _02244414
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224433A: ; jump table
	.short _02244348 - _0224433A - 2 ; case 0
	.short _02244370 - _0224433A - 2 ; case 1
	.short _0224437E - _0224433A - 2 ; case 2
	.short _02244396 - _0224433A - 2 ; case 3
	.short _022443A4 - _0224433A - 2 ; case 4
	.short _022443E6 - _0224433A - 2 ; case 5
	.short _022443F8 - _0224433A - 2 ; case 6
_02244348:
	ldr r0, [r4]
	bl MOD12_02242CB0
	add r2, r4, #0
	ldr r0, [r4]
	mov r1, #0
	add r2, #0x12
	bl MOD12_0224324C
	ldr r0, _02244430 ; =0x0000049E
	bl FUN_0200521C
	ldr r0, _02244434 ; =0x000006E5
	bl FUN_020054C8
	ldrb r0, [r4, #0x10]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, pc}
_02244370:
	ldrb r1, [r4, #0x12]
	cmp r1, #1
	bne _0224442C
	add r0, r0, #1
	add sp, #0xc
	strb r0, [r4, #0x10]
	pop {r4, r5, pc}
_0224437E:
	ldrb r1, [r4, #0x11]
	add r3, r4, #0
	ldr r0, [r4]
	mov r2, #0
	add r3, #0x13
	bl MOD12_022433CC
	ldrb r0, [r4, #0x10]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, pc}
_02244396:
	ldrb r1, [r4, #0x13]
	cmp r1, #1
	bne _0224442C
	add r0, r0, #1
	add sp, #0xc
	strb r0, [r4, #0x10]
	pop {r4, r5, pc}
_022443A4:
	ldr r0, [r4]
	mov r2, #0
	ldr r1, [r0, #0x10]
	ldrb r0, [r4, #0x11]
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #5
	bl GetMonData
	add r2, r0, #0
	mov r0, #0x7f
	str r0, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r3, #0x18
	str r3, [sp, #8]
	ldr r3, [r4]
	lsl r2, r2, #0x10
	ldr r5, [r3]
	ldrb r3, [r4, #0x11]
	add r0, #0xdd
	lsr r2, r2, #0x10
	lsl r3, r3, #2
	add r3, r5, r3
	ldr r0, [r3, r0]
	add r3, r1, #0
	bl FUN_02069FB0
	ldrb r0, [r4, #0x10]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, pc}
_022443E6:
	bl FUN_02005670
	cmp r0, #0
	bne _0224442C
	ldrb r0, [r4, #0x10]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, pc}
_022443F8:
	mov r0, #0x14
	ldrsh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, #0x14]
	ldrsh r0, [r4, r0]
	cmp r0, #0x3c
	ble _0224442C
	mov r0, #0
	strh r0, [r4, #0x14]
	ldrb r0, [r4, #0x10]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r4, r5, pc}
_02244414:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_0224442C:
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02244430: .word 0x0000049E
_02244434: .word 0x000006E5

	thumb_func_start MOD12_02244438
MOD12_02244438: ; 0x02244438
	push {r3, lr}
	mov r1, #0x12
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r1, #0xff
	lsr r2, r2, #0x10
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_0224444C
MOD12_0224444C: ; 0x0224444C
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	add r5, r1, #0
	mov r0, #0x18
	mov r1, #0x24
	add r6, r2, #0
	add r7, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x24
	bl MI_CpuFill8
	str r5, [r4]
	ldrh r0, [r6]
	strh r0, [r4, #4]
	ldrh r0, [r6, #2]
	strh r0, [r4, #6]
	ldrh r0, [r6, #4]
	strh r0, [r4, #8]
	ldrh r0, [r6, #6]
	strh r0, [r4, #0xa]
	ldr r0, [sp]
	str r0, [r4, #0xc]
	ldrb r0, [r7, #7]
	strb r0, [r4, #0x11]
	ldrb r0, [r7, #7]
	cmp r0, #0
	beq _02244492
	cmp r0, #1
	beq _022444A8
	cmp r0, #2
	beq _022444BE
	b _022444D4
_02244492:
	ldr r0, _022444E4 ; =0x0000041E
	mov r2, #0
	add r3, r4, #0
_02244498:
	ldrsh r1, [r5, r0]
	add r2, r2, #1
	add r5, r5, #2
	strh r1, [r3, #0x14]
	add r3, r3, #2
	cmp r2, #4
	blt _02244498
	b _022444D8
_022444A8:
	ldr r0, _022444E8 ; =0x00000426
	mov r3, #0
	add r2, r4, #0
_022444AE:
	ldrsh r1, [r5, r0]
	add r3, r3, #1
	add r5, r5, #2
	strh r1, [r2, #0x14]
	add r2, r2, #2
	cmp r3, #4
	blt _022444AE
	b _022444D8
_022444BE:
	ldr r0, _022444EC ; =0x0000042E
	mov r3, #0
	add r2, r4, #0
_022444C4:
	ldrsh r1, [r5, r0]
	add r3, r3, #1
	add r5, r5, #2
	strh r1, [r2, #0x14]
	add r2, r2, #2
	cmp r3, #4
	blt _022444C4
	b _022444D8
_022444D4:
	bl ErrorHandling
_022444D8:
	ldr r0, _022444F0 ; =MOD12_022444F8
	ldr r2, _022444F4 ; =0x00007530
	add r1, r4, #0
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022444E4: .word 0x0000041E
_022444E8: .word 0x00000426
_022444EC: .word 0x0000042E
_022444F0: .word MOD12_022444F8
_022444F4: .word 0x00007530

	thumb_func_start MOD12_022444F8
MOD12_022444F8: ; 0x022444F8
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #5
	bhi _022445E8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02244510: ; jump table
	.short _0224451C - _02244510 - 2 ; case 0
	.short _0224452A - _02244510 - 2 ; case 1
	.short _02244544 - _02244510 - 2 ; case 2
	.short _02244566 - _02244510 - 2 ; case 3
	.short _022445BC - _02244510 - 2 ; case 4
	.short _022445E8 - _02244510 - 2 ; case 5
_0224451C:
	ldr r0, _02244604 ; =0x000006FA
	bl FUN_020054C8
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0224452A:
	mov r0, #0x12
	ldrsh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, #0x12]
	ldrsh r0, [r4, r0]
	cmp r0, #0x2d
	ble _02244600
	mov r0, #0
	strh r0, [r4, #0x12]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_02244544:
	mov r2, #0
	add r3, r4, #0
	mov r0, #0x14
_0224454A:
	ldrsh r1, [r3, r0]
	cmp r1, #0
	ble _02244558
	ldr r0, _02244608 ; =0x000006FB
	bl FUN_020054C8
	b _02244560
_02244558:
	add r2, r2, #1
	add r3, r3, #2
	cmp r2, #4
	blt _0224454A
_02244560:
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
_02244566:
	mov r0, #0x12
	ldrsh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, #0x12]
	ldrsh r0, [r4, r0]
	cmp r0, #1
	blt _02244600
	mov r6, #0
	strh r6, [r4, #0x12]
	add r5, r6, #0
	mov r7, #0x14
_0224457C:
	ldr r0, [r4]
	mov r2, #0x1c
	add r1, r0, r5
	mov r0, #0xf3
	lsl r0, r0, #2
	ldrb r1, [r1, r0]
	lsl r0, r1, #1
	add r0, r4, r0
	ldrsh r2, [r0, r2]
	add r2, r2, #1
	strh r2, [r0, #0x1c]
	mov r2, #0x1c
	ldrsh r3, [r0, r2]
	ldrsh r0, [r0, r7]
	cmp r3, r0
	bgt _022445A8
	str r5, [sp]
	ldrb r2, [r4, #0x11]
	ldr r0, [r4]
	bl MOD12_022430A8
	b _022445AA
_022445A8:
	add r6, r6, #1
_022445AA:
	add r5, r5, #1
	cmp r5, #4
	blt _0224457C
	cmp r6, #4
	blt _02244600
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_022445BC:
	mov r3, #0
	add r2, r4, #0
	mov r0, #0x14
_022445C2:
	ldrsh r1, [r2, r0]
	cmp r1, #0
	ble _022445D0
	ldr r0, _0224460C ; =0x000006F9
	bl FUN_020054C8
	b _022445D8
_022445D0:
	add r3, r3, #1
	add r2, r2, #2
	cmp r3, #4
	blt _022445C2
_022445D8:
	ldr r0, _02244604 ; =0x000006FA
	mov r1, #0
	bl FUN_020054F0
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_022445E8:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02244600:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02244604: .word 0x000006FA
_02244608: .word 0x000006FB
_0224460C: .word 0x000006F9

	thumb_func_start MOD12_02244610
MOD12_02244610: ; 0x02244610
	push {r3, lr}
	lsl r2, r2, #0x10
	mov r3, #0
	mov r1, #0xff
	lsr r2, r2, #0x10
	str r3, [sp]
	bl MOD12_02240F3C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02244624
MOD12_02244624: ; 0x02244624
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #0x18
	mov r1, #0x14
	add r5, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x14
	bl MI_CpuFill8
	str r7, [r4]
	ldrh r0, [r5]
	ldr r2, _02244660 ; =0x00007530
	add r1, r4, #0
	strh r0, [r4, #4]
	ldrh r0, [r5, #2]
	strh r0, [r4, #6]
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strh r0, [r4, #0xa]
	ldr r0, _02244664 ; =MOD12_02244668
	str r6, [r4, #0xc]
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02244660: .word 0x00007530
_02244664: .word MOD12_02244668

	thumb_func_start MOD12_02244668
MOD12_02244668: ; 0x02244668
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _0224467E
	cmp r0, #1
	beq _0224469E
	cmp r0, #2
	beq _022446CE
	b _022446E8
_0224467E:
	mov r0, #3
	str r0, [sp]
	mov r0, #0x5a
	mov r1, #0x10
	mov r2, #0
	mov r3, #0x3f
	bl FUN_0200A208
	ldr r0, _02244704 ; =0x0000049E
	mov r1, #0x5a
	bl FUN_02005350
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_0224469E:
	mov r0, #3
	bl FUN_0200A344
	cmp r0, #1
	bne _02244700
	bl FUN_02005404
	cmp r0, #0
	bne _02244700
	ldr r0, [r4]
	bl MOD12_02242CEC
	ldr r0, _02244708 ; =0x0400006C
	mov r1, #0x10
	bl GXx_SetMasterBrightness_
	ldr r0, _0224470C ; =0x0400106C
	mov r1, #0x10
	bl GXx_SetMasterBrightness_
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_022446CE:
	mov r0, #0x12
	ldrsh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, #0x12]
	ldrsh r0, [r4, r0]
	cmp r0, #0x3c
	ble _02244700
	mov r0, #0
	strh r0, [r4, #0x12]
	ldrb r0, [r4, #0x10]
	add r0, r0, #1
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
_022446E8:
	mov r2, #0
	ldr r0, [r4, #0xc]
	add r1, r4, #4
	add r3, r2, #0
	bl MOD12_02240FB0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
_02244700:
	pop {r3, r4, r5, pc}
	nop
_02244704: .word 0x0000049E
_02244708: .word 0x0400006C
_0224470C: .word 0x0400106C

	thumb_func_start MOD12_02244710
MOD12_02244710: ; 0x02244710
	push {r3, r4, r5, r6, r7, lr}
	mov r6, #0
	add r5, r0, #0
	add r7, r1, #0
	add r4, r6, #0
_0224471A:
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02027A14
	cmp r0, #1
	bne _02244732
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02027BDC
	ldrb r0, [r7, r0]
	add r6, r6, r0
_02244732:
	add r4, r4, #1
	cmp r4, #0x14
	blt _0224471A
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD12_0224473C
MOD12_0224473C: ; 0x0224473C
	push {r3, lr}
	add r3, r0, #0
	mov r2, #0
	mov r0, #0x5a
	add r1, r1, #3
	str r2, [sp]
	bl UncompressFromNarc
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD12_02244750
MOD12_02244750: ; 0x02244750
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r5, r0, #0
	mov r0, #0x1b
	str r0, [sp]
	mov r0, #0x2c
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x28]
	add r4, r1, #0
	add r6, r3, #0
	str r0, [sp, #0x14]
	add r0, r2, #0
	mov r1, #3
	add r2, r5, #0
	add r3, r4, #0
	bl FUN_0200C0DC
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x1b
	mov r3, #0xba
	str r6, [sp, #8]
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, [sp, #0x2c]
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x1b
	mov r3, #0xbb
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, [sp, #0x30]
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x1b
	mov r3, #0xbc
	bl FUN_0200C13C
	add sp, #0x18
	pop {r4, r5, r6, pc}

	thumb_func_start MOD12_022447C0
MOD12_022447C0: ; 0x022447C0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r2, #0
	add r6, r3, #0
	bl FUN_0200C358
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0200C368
	add r0, r5, #0
	add r1, r6, #0
	bl FUN_0200C378
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	bl FUN_0200C388
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD12_022447E8
MOD12_022447E8: ; 0x022447E8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r5, r3, #0
	mov ip, r2
	ldr r3, _02244860 ; =MOD12_022467DC
	add r6, r0, #0
	add r7, r1, #0
	add r2, sp, #4
	mov r4, #6
_022447FA:
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	sub r4, r4, #1
	bne _022447FA
	ldr r0, [r3]
	mov r1, #0x18
	str r0, [r2]
	ldr r0, [sp, #0x50]
	str r5, [sp, #0x18]
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x54]
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x58]
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x5c]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x60]
	str r0, [sp, #0x30]
	mov r0, ip
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x18
	str r0, [sp]
	bl MI_CpuFill8
	ldr r5, [sp]
	mov r4, #0
_02244832:
	add r0, r6, #0
	add r1, r7, #0
	add r2, sp, #4
	bl FUN_0200C154
	mov r1, #0
	stmia r5!, {r0}
	bl FUN_0200C644
	add r4, r4, #1
	cmp r4, #5
	blt _02244832
	ldr r0, _02244864 ; =MOD12_02244958
	ldr r1, [sp]
	ldr r2, _02244868 ; =0x00009C40
	bl FUN_0200CA44
	ldr r1, [sp]
	str r0, [r1, #0x14]
	add r0, r1, #0
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02244860: .word MOD12_022467DC
_02244864: .word MOD12_02244958
_02244868: .word 0x00009C40

	thumb_func_start MOD12_0224486C
MOD12_0224486C: ; 0x0224486C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_02244874:
	ldr r0, [r5]
	bl FUN_0200C3DC
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _02244874
	ldr r0, [r6, #0x14]
	bl FUN_0200CAB4
	add r0, r6, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}

	thumb_func_start MOD12_02244890
MOD12_02244890: ; 0x02244890
	push {r4, r5, r6, lr}
	add r5, r0, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r4, [sp, #0x24]
	add r6, r3, #0
	ldr r0, [r5]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	add r3, r4, #0
	bl FUN_0200C750
	ldr r2, [sp, #0x10]
	lsl r1, r6, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r5, #4]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	add r3, r4, #0
	bl FUN_0200C750
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x18]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r5, #8]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	add r3, r4, #0
	bl FUN_0200C750
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x20]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r5, #0xc]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	add r3, r4, #0
	bl FUN_0200C750
	ldr r0, [r5]
	mov r1, #0
	bl FUN_0200C5C0
	ldr r0, [r5, #4]
	mov r1, #1
	bl FUN_0200C5C0
	ldr r0, [r5, #8]
	mov r1, #2
	bl FUN_0200C5C0
	ldr r0, [r5, #0xc]
	mov r1, #3
	bl FUN_0200C5C0
	mov r4, #0
	mov r6, #1
_02244906:
	ldr r0, [r5]
	add r1, r6, #0
	bl FUN_0200C644
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _02244906
	pop {r4, r5, r6, pc}

	thumb_func_start MOD12_02244918
MOD12_02244918: ; 0x02244918
	push {r4, lr}
	sub sp, #0x18
	add r4, r2, #0
	str r3, [sp]
	ldr r2, [sp, #0x20]
	str r1, [sp, #4]
	str r2, [sp, #8]
	str r4, [sp, #0xc]
	str r2, [sp, #0x10]
	ldr r2, [sp, #0x24]
	str r2, [sp, #0x14]
	add r2, r3, #0
	add r3, r4, #0
	bl MOD12_02244890
	add sp, #0x18
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD12_0224493C
MOD12_0224493C: ; 0x0224493C
	push {r4, r5, r6, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r4, #0
_02244944:
	ldr r0, [r5]
	add r1, r6, #0
	bl FUN_0200C644
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _02244944
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD12_02244958
MOD12_02244958: ; 0x02244958
	push {r4, r5, r6, lr}
	add r6, r1, #0
	ldr r0, [r6]
	bl FUN_0200C658
	cmp r0, #0
	beq _02244988
	mov r4, #0
	add r5, r6, #0
_0224496A:
	ldr r0, [r5]
	bl FUN_0200C5A8
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0224496A
	ldr r0, [r6, #0x10]
	bl FUN_0200C658
	cmp r0, #1
	bne _02244988
	ldr r0, [r6, #0x10]
	bl FUN_0200C5A8
_02244988:
	pop {r4, r5, r6, pc}

	.section .rodata

	.global MOD12_0224498C
MOD12_0224498C: ; 0x0224498C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD12_0224499C
MOD12_0224499C: ; 0x0224499C
	.byte 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x00, 0x10, 0x00, 0x10, 0x00
	.byte 0x10, 0x00, 0x00, 0x00

	.global MOD12_022449B0
MOD12_022449B0: ; 0x022449B0
	.byte 0x60, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00
	.byte 0x40, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00

	.global MOD12_022449C8
MOD12_022449C8: ; 0x022449C8
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00

	.global MOD12_022449E8
MOD12_022449E8: ; 0x022449E8
	.byte 0x04, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x60, 0x00, 0x00, 0x00

	.global MOD12_02244A10
MOD12_02244A10: ; 0x02244A10
	.word MOD12_0222E100, MOD12_0222E150, MOD12_0222E1C4
	.word MOD12_0222E24C, MOD12_0222E250, MOD12_0222E314, MOD12_0222E3A8
	.word MOD12_0222E3FC, MOD12_0222E460, MOD12_0222E4F8, MOD12_0222E6D4
	.word MOD12_0222E728, MOD12_0222E748, MOD12_0222EC10, MOD12_0222EC7C
	.word MOD12_0222EE24

	.global MOD12_02244A50
MOD12_02244A50: ; 0x02244A50
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x02, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x06, 0x04
	.byte 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02244AA4
MOD12_02244AA4: ; 0x02244AA4
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD12_02244AB4
MOD12_02244AB4: ; 0x02244AB4
	.byte 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00
	.byte 0x00, 0x40, 0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD12_02244AC8
MOD12_02244AC8: ; 0x02244AC8
	.word 0x60, 0x20, 0x40, 0x40
	.word 0x08, 0x08

	.global MOD12_02244AE0
MOD12_02244AE0: ; 0x02244AE0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0F, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02244AFC
MOD12_02244AFC: ; 0x02244AFC
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00

	.global MOD12_02244B1C
MOD12_02244B1C: ; 0x02244B1C
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD12_02244B44
MOD12_02244B44: ; 0x02244B44
	.word MOD12_0222F990, MOD12_0222F9C4
	.word MOD12_0222FA3C, MOD12_0222FAA0, MOD12_0222FBB0, MOD12_0222FB60
	.word MOD12_0222FB10, MOD12_0222FC60, MOD12_0222FCF0, MOD12_0222FD20
	.word MOD12_0222FDFC

	.global MOD12_02244B70
MOD12_02244B70: ; 0x02244B70
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x02, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x06, 0x01
	.byte 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02244BC4
MOD12_02244BC4: ; 0x02244BC4
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD12_02244BD4
MOD12_02244BD4: ; 0x02244BD4
	.byte 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00
	.byte 0x00, 0x40, 0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD12_02244BE8
MOD12_02244BE8: ; 0x02244BE8
	.byte 0x99, 0x04, 0x78, 0x00, 0x02, 0x03, 0x04, 0x04, 0x02, 0x02, 0x03, 0x03
	.byte 0x9B, 0x04, 0x78, 0x00, 0x02, 0x04, 0x04, 0x04, 0x02, 0x02, 0x03, 0x03

	.global MOD12_02244C00
MOD12_02244C00: ; 0x02244C00
	.byte 0x60, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00
	.byte 0x40, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00

	.global MOD12_02244C18
MOD12_02244C18: ; 0x02244C18
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00

	.global MOD12_02244C38
MOD12_02244C38: ; 0x02244C38
	.byte 0x04, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x60, 0x00, 0x00, 0x00

	.global MOD12_02244C60
MOD12_02244C60: ; 0x02244C60
	.word MOD12_02230A98, MOD12_02230AEC, MOD12_02230B94
	.word MOD12_02230BE4, MOD12_02230DB4, MOD12_02230E28, MOD12_02230E7C
	.word MOD12_02230ED0, MOD12_02230F24, MOD12_02230FA8, MOD12_02231060
	.word MOD12_022310C4, MOD12_02231248

	.global MOD12_02244C94
MOD12_02244C94: ; 0x02244C94
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x06, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02244CE8
MOD12_02244CE8: ; 0x02244CE8
	.byte 0x0D, 0x00, 0xAC, 0x00
	.byte 0x80, 0xFE, 0x01, 0x00, 0x25, 0x00, 0xA4, 0x00, 0x00, 0x03, 0x01, 0x00, 0x40, 0x00, 0xB0, 0x00
	.byte 0x80, 0xFF, 0x00, 0x00, 0xC0, 0x00, 0xB0, 0x00, 0x80, 0x00, 0x00, 0x00, 0xDB, 0x00, 0xA4, 0x00
	.byte 0x00, 0xFD, 0x01, 0x00, 0xF3, 0x00, 0xAC, 0x00, 0x80, 0x01, 0x01, 0x00

	.global MOD12_02244D18
MOD12_02244D18: ; 0x02244D18
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02244D4C
MOD12_02244D4C: ; 0x02244D4C
	.byte 0x04, 0x05, 0x06, 0x07

	.global MOD12_02244D50
MOD12_02244D50: ; 0x02244D50
	.byte 0x00, 0x01, 0x02, 0x03

	.global MOD12_02244D54
MOD12_02244D54: ; 0x02244D54
	.byte 0x1E, 0x00, 0x27, 0x00

	.global MOD12_02244D58
MOD12_02244D58: ; 0x02244D58
	.byte 0x00, 0x01, 0x02, 0x03

	.global MOD12_02244D5C
MOD12_02244D5C: ; 0x02244D5C
	.byte 0x00, 0x01, 0x02, 0x03, 0x03, 0x03, 0x00, 0x00

	.global MOD12_02244D64
MOD12_02244D64: ; 0x02244D64
	.byte 0x14, 0x02, 0x11, 0x02, 0x0E, 0x02, 0x0B, 0x02

	.global MOD12_02244D6C
MOD12_02244D6C: ; 0x02244D6C
	.byte 0x08, 0x00, 0x07, 0x00, 0x06, 0x00, 0x0A, 0x00, 0x1C, 0x00, 0x00, 0x00

	.global MOD12_02244D78
MOD12_02244D78: ; 0x02244D78
	.byte 0x28, 0x00, 0x48, 0x00
	.byte 0x80, 0x00, 0x48, 0x00, 0xD8, 0x00, 0x48, 0x00

	.global MOD12_02244D84
MOD12_02244D84: ; 0x02244D84
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00

	.global MOD12_02244D94
MOD12_02244D94: ; 0x02244D94
	.byte 0x13, 0x00, 0x20, 0x00, 0x93, 0x00, 0x20, 0x00
	.byte 0x13, 0x00, 0x80, 0x00, 0x93, 0x00, 0x80, 0x00

	.global MOD12_02244DA4
MOD12_02244DA4: ; 0x02244DA4
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00

	.global MOD12_02244DB4
MOD12_02244DB4: ; 0x02244DB4
	.byte 0x27, 0x00, 0x30, 0x00, 0xA7, 0x00, 0x30, 0x00
	.byte 0x27, 0x00, 0x90, 0x00, 0xA7, 0x00, 0x90, 0x00

	.global MOD12_02244DC4
MOD12_02244DC4: ; 0x02244DC4
	.byte 0x08, 0x80, 0x00, 0x50, 0x08, 0x80, 0x58, 0xA8
	.byte 0x08, 0x80, 0xB0, 0xFF, 0x88, 0xC0, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00

	.global MOD12_02244DD8
MOD12_02244DD8: ; 0x02244DD8
	.word MOD12_02245034, MOD12_02245054, MOD12_02244FF4, MOD12_02245014
	.word MOD12_02244FD4

	.global MOD12_02244DEC
MOD12_02244DEC: ; 0x02244DEC
	.byte 0x08, 0x60, 0x08, 0x78, 0x08, 0x60, 0x88, 0xF8, 0x68, 0xC0, 0x08, 0x78, 0x68, 0xC0, 0x88, 0xF8
	.byte 0xFF, 0x00, 0x00, 0x00

	.global MOD12_02244E00
MOD12_02244E00: ; 0x02244E00
	.byte 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01, 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01
	.byte 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01, 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01

	.global MOD12_02244E18
MOD12_02244E18: ; 0x02244E18
	.byte 0x00, 0x00, 0xC0, 0x00
	.byte 0x80, 0x01, 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01, 0x00, 0x00, 0xC0, 0x00, 0x80, 0x01, 0x00, 0x00
	.byte 0xC0, 0x00, 0x80, 0x01

	.global MOD12_02244E30
MOD12_02244E30: ; 0x02244E30
	.byte 0x13, 0x00, 0x40, 0x00, 0x13, 0x00, 0x50, 0x00, 0x93, 0x00, 0x40, 0x00
	.byte 0x93, 0x00, 0x50, 0x00, 0x13, 0x00, 0xA0, 0x00, 0x13, 0x00, 0xB0, 0x00, 0x93, 0x00, 0xA0, 0x00
	.byte 0x93, 0x00, 0xB0, 0x00

	.global MOD12_02244E50
MOD12_02244E50: ; 0x02244E50
	.byte 0x3F, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0xBF, 0x00, 0x00, 0x00
	.byte 0x34, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 0xBF, 0x00, 0x00, 0x00
	.byte 0x94, 0x00, 0x00, 0x00

	.global MOD12_02244E70
MOD12_02244E70: ; 0x02244E70
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xF6, 0x80, 0x00, 0x00, 0xEF, 0x80, 0x00, 0x00
	.byte 0xF4, 0x80, 0x00, 0x00, 0xF4, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02244EA4
MOD12_02244EA4: ; 0x02244EA4
	.byte 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00
	.byte 0x11, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00
	.byte 0x11, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00

	.global MOD12_02244EE4
MOD12_02244EE4: ; 0x02244EE4
	.byte 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
	.byte 0x16, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00

	.global MOD12_02244F24
MOD12_02244F24: ; 0x02244F24
	.word 0x01, 0x0B, 0x01, 0x0E
	.word 0x01, 0x0B, 0x11, 0x1E
	.word 0x0D, 0x17, 0x01, 0x0E
	.word 0x0D, 0x17, 0x11, 0x1E

	.global MOD12_02244F64
MOD12_02244F64: ; 0x02244F64
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0F, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02244FD4
MOD12_02244FD4: ; 0x02244FD4
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0xFF, 0x67, 0xFF, 0x4B
	.byte 0xFF, 0x2F, 0xFF, 0x13, 0x9F, 0x03, 0x3E, 0x03, 0x4D, 0x15, 0xFF, 0x4F, 0x08, 0x21, 0x2B, 0x7C
	.byte 0x8C, 0x31, 0x31, 0x46, 0xD6, 0x5A, 0x00, 0x00

	.global MOD12_02244FF4
MOD12_02244FF4: ; 0x02244FF4
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0x9F, 0x7F, 0x3F, 0x7F
	.byte 0xDF, 0x7A, 0x9F, 0x72, 0x5F, 0x6A, 0x9F, 0x65, 0xED, 0x1C, 0x5F, 0x7F, 0x08, 0x21, 0x2B, 0x7C
	.byte 0x8C, 0x31, 0x31, 0x46, 0xD6, 0x5A, 0x00, 0x00

	.global MOD12_02245014
MOD12_02245014: ; 0x02245014
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0xFC, 0x63, 0xF7, 0x37
	.byte 0x73, 0x2F, 0x30, 0x27, 0x0C, 0x1F, 0xC8, 0x16, 0x46, 0x11, 0xF8, 0x5B, 0x08, 0x21, 0x2B, 0x7C
	.byte 0x8C, 0x31, 0x31, 0x46, 0xD6, 0x5A, 0x00, 0x00

	.global MOD12_02245034
MOD12_02245034: ; 0x02245034
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0x1F, 0x4F, 0xDF, 0x4A
	.byte 0x7F, 0x46, 0x1F, 0x3E, 0xBF, 0x39, 0xBF, 0x00, 0xED, 0x1C, 0x5F, 0x5B, 0x08, 0x21, 0x2B, 0x7C
	.byte 0x8C, 0x31, 0x31, 0x46, 0xD6, 0x5A, 0x00, 0x00

	.global MOD12_02245054
MOD12_02245054: ; 0x02245054
	.byte 0xCD, 0x75, 0xFF, 0x7F, 0xF9, 0x7F, 0x93, 0x7F
	.byte 0x0E, 0x7F, 0xAA, 0x7F, 0x68, 0x77, 0xC5, 0x7E, 0x04, 0x29, 0xB7, 0x7F, 0x08, 0x21, 0x2B, 0x7C
	.byte 0x8C, 0x31, 0x31, 0x46, 0xD6, 0x5A, 0x00, 0x00

	.global MOD12_02245074
MOD12_02245074: ; 0x02245074
	.byte 0x09, 0x00, 0x00, 0x00, 0x01, 0x00, 0xFF, 0xFF
	.byte 0x00, 0x00, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word MOD12_02231D5C
	.byte 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x01, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x04, 0x00, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x01, 0x00, 0x02, 0x00, 0xFF, 0xFF
	.byte 0x04, 0x00, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00
	.word MOD12_02244DEC, MOD12_02244DA4, MOD12_02244D4C, MOD12_02232E8C
	.word MOD12_02232FF0, MOD12_02231E34, MOD12_0223217C
	.byte 0x0B, 0x00, 0x01, 0x00, 0x03, 0x00, 0xFF, 0xFF
	.byte 0x04, 0x00, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00
	.word MOD12_02244DC4, MOD12_02244D84, MOD12_02244D50, MOD12_0223302C
	.word MOD12_0223314C, MOD12_022320C0, MOD12_0223221C

	.global MOD12_02245134
MOD12_02245134: ; 0x02245134
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xE9, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xFA, 0x80, 0x00, 0x00
	.byte 0xEF, 0x80, 0x00, 0x00, 0xF5, 0x80, 0x00, 0x00, 0xF5, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02245168
MOD12_02245168: ; 0x02245168
	.byte 0x28, 0x00, 0x60, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0xE8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0xFB, 0x80, 0x00, 0x00, 0xEF, 0x80, 0x00, 0x00, 0xF6, 0x80, 0x00, 0x00, 0xF6, 0x80, 0x00, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_0224519C
MOD12_0224519C: ; 0x0224519C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE9, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0xFA, 0x80, 0x00, 0x00, 0xEF, 0x80, 0x00, 0x00, 0xF5, 0x80, 0x00, 0x00
	.byte 0xF5, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD12_022451D0
MOD12_022451D0: ; 0x022451D0
	.byte 0x06, 0x07, 0x0A, 0x0B

	.global MOD12_022451D4
MOD12_022451D4: ; 0x022451D4
	.short 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x000C, 0x000D, 0x000E
	.short 0x000F, 0x0010, 0x0029, 0x0028, 0x0024, 0x0026, 0x0027, 0x0000

	.global MOD12_022451F4
MOD12_022451F4: ; 0x022451F4
	.short 0x0058, 0x000C, 0x0078, 0x000C, 0x0098, 0x000C

	.global MOD12_02245200
MOD12_02245200: ; 0x02245200
	.short 0x0060, 0x0014, 0x0080, 0x0014, 0x00A0, 0x0014

	.global MOD12_0224520C
MOD12_0224520C: ; 0x0224520C
	.byte 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00

	.global MOD12_02245218
MOD12_02245218: ; 0x02245218
	.word 0x00, 0x28, 0x46, 0x64

	.global MOD12_02245228
MOD12_02245228: ; 0x02245228
	.short 0x05, 0x2B, 0x05, 0x5B, 0x05, 0x8B, 0x05, 0xBB

	.global MOD12_02245238
MOD12_02245238: ; 0x02245238
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0xEF, 0x80, 0x00, 0x00, 0xE9, 0x80, 0x00, 0x00, 0xEF, 0x80, 0x00, 0x00, 0xEF, 0x80, 0x00, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_0224526C
MOD12_0224526C: ; 0x0224526C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xF1, 0x80, 0x00, 0x00, 0xE9, 0x80, 0x00, 0x00, 0xF1, 0x80, 0x00, 0x00
	.byte 0xF1, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xF2, 0x80, 0x00, 0x00, 0xEE, 0x80, 0x00, 0x00
	.byte 0xF2, 0x80, 0x00, 0x00, 0xF2, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_022452D4
MOD12_022452D4: ; 0x022452D4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x11, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xF5, 0x80, 0x00, 0x00
	.byte 0xE9, 0x80, 0x00, 0x00, 0xF3, 0x80, 0x00, 0x00, 0xF3, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02245308
MOD12_02245308: ; 0x02245308
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0xF0, 0x80, 0x00, 0x00, 0xE9, 0x80, 0x00, 0x00, 0xF0, 0x80, 0x00, 0x00, 0xF0, 0x80, 0x00, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_0224533C
MOD12_0224533C: ; 0x0224533C
	.byte 0x60, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x27, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xEC, 0x80, 0x00, 0x00, 0xE9, 0x80, 0x00, 0x00, 0xEC, 0x80, 0x00, 0x00
	.byte 0xEC, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD12_02245370
MOD12_02245370: ; 0x02245370
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xED, 0x80, 0x00, 0x00, 0xE9, 0x80, 0x00, 0x00
	.byte 0xED, 0x80, 0x00, 0x00, 0xED, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_022453A4
MOD12_022453A4: ; 0x022453A4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xEE, 0x80, 0x00, 0x00
	.byte 0xE9, 0x80, 0x00, 0x00, 0xEE, 0x80, 0x00, 0x00, 0xEE, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_022453D8
MOD12_022453D8: ; 0x022453D8
	.byte 0x60, 0x00, 0x28, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x13, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_0224540C
MOD12_0224540C: ; 0x0224540C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x00, 0x05, 0x01, 0x02, 0x00, 0x05, 0x01
	.byte 0x03, 0x00, 0x1B, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x06, 0x00, 0x1C, 0x00
	.byte 0x07, 0x00, 0x1C, 0x00, 0x08, 0x00, 0x1C, 0x00, 0x09, 0x00, 0x1C, 0x00, 0x0A, 0x00, 0x06, 0x00
	.byte 0x0B, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x06, 0x00, 0x0D, 0x00, 0x06, 0x00, 0x0E, 0x00, 0x06, 0x00
	.byte 0x0F, 0x00, 0x06, 0x00, 0x10, 0x00, 0x06, 0x00, 0x11, 0x00, 0x06, 0x00, 0x12, 0x00, 0x06, 0x00
	.byte 0x13, 0x00, 0x06, 0x00, 0x14, 0x00, 0x06, 0x00, 0x15, 0x00, 0x06, 0x00, 0x16, 0x00, 0x00, 0x00
	.byte 0x17, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x19, 0x00, 0x05, 0x00, 0x1A, 0x00, 0x00, 0x00
	.byte 0x1B, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x02, 0x00
	.byte 0x1F, 0x00, 0x02, 0x00, 0x20, 0x00, 0x02, 0x00, 0x21, 0x00, 0x02, 0x00, 0x22, 0x00, 0x02, 0x00
	.byte 0x23, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00
	.byte 0x27, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00
	.byte 0x46, 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x01

	.global MOD12_022454C8
MOD12_022454C8: ; 0x022454C8
	.byte 0x1E, 0x14, 0x0A, 0x00

	.global MOD12_022454CC
MOD12_022454CC: ; 0x022454CC
	.byte 0x12, 0x75, 0x1C, 0x75, 0x26, 0x75, 0x30, 0x75

	.global MOD12_022454D4
MOD12_022454D4: ; 0x022454D4
	.byte 0xF0, 0xD8, 0x0C, 0xFE, 0xF4, 0x01, 0x10, 0x27

	.global MOD12_022454DC
MOD12_022454DC: ; 0x022454DC
	.byte 0xD0, 0x8A, 0xDA, 0x8A, 0xE4, 0x8A, 0xEE, 0x8A

	.global MOD12_022454E4
MOD12_022454E4: ; 0x022454E4
	.byte 0x0A, 0x00, 0xF6, 0xF6, 0x00, 0x00, 0x0A, 0x00
	.byte 0xF6, 0xF6, 0xF6, 0x00, 0x0A, 0x00, 0xF6, 0xF6, 0xF6, 0x00, 0x0A, 0x00, 0x00, 0xF6, 0xF6, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00

	.global MOD12_02245500
MOD12_02245500: ; 0x02245500
	.word MOD12_02235DBC, MOD12_02235DD4, MOD12_02235DE8
	.word MOD12_02235DEC, MOD12_02235E04, 0x00000000, MOD12_02235E24
	.word MOD12_02235E3C, 0x00000000, MOD12_02235EFC, MOD12_02235F14
	.word 0x00000000, MOD12_02236040, MOD12_02236058, 0x00000000
	.word MOD12_02236210, MOD12_02236228, 0x00000000, MOD12_02236370
	.word MOD12_02236388, 0x00000000, MOD12_02236528, MOD12_02236540
	.word 0x00000000, MOD12_02236AA0, MOD12_02236AB8, MOD12_02236CF8
	.word MOD12_02236D1C, MOD12_02236D34, 0x00000000, MOD12_02236D38
	.word MOD12_02236D50, 0x00000000, MOD12_02236E68, MOD12_02236E80
	.word 0x00000000, MOD12_02237104, MOD12_0223711C, 0x00000000
	.word MOD12_0223726C, MOD12_02237284, 0x00000000, MOD12_02237658
	.word MOD12_02237670, 0x00000000, MOD12_02237658, MOD12_02237670
	.word 0x00000000, MOD12_022377C0, MOD12_022377D8, 0x00000000
	.word MOD12_02237AA4, MOD12_02237ABC, 0x00000000, MOD12_02237C90
	.word MOD12_02237CA8, 0x00000000, MOD12_02237EEC, MOD12_02237F04
	.word 0x00000000, MOD12_02237F48, MOD12_02237F5C, 0x00000000
	.word MOD12_02237D94, MOD12_02237DA8, 0x00000000

	.global MOD12_02245608
MOD12_02245608: ; 0x02245608
	.byte 0x0A, 0x14, 0x1E, 0x28

	.global MOD12_0224560C
MOD12_0224560C: ; 0x0224560C
	.byte 0x28, 0x1E, 0x14, 0x0A, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02245614
MOD12_02245614: ; 0x02245614
	.word MOD12_02238978

	.global MOD12_02245618
MOD12_02245618: ; 0x02245618
	.word 0x0000FF03
	.word MOD12_022386C0, 0x0000FF03, MOD12_022387B0, 0x0000FF03
	.word MOD12_022388BC, 0x0000FF05, MOD12_02238914, 0x0000FF03
	.word MOD12_02238978, 0x0000FF03, MOD12_0223897C, 0x00000005
	.word MOD12_022389C4, 0x0000FF03, MOD12_02238A1C, 0x0000FF03
	.word MOD12_02238A60, 0x00000005, MOD12_02238AA8, 0x0000FF03
	.word MOD12_02238B24, 0x0000FF03, MOD12_02238B98, 0x0000FF03
	.word MOD12_02238B44, 0x0000FF03, MOD12_02238BF8, 0x0000FF03
	.word MOD12_02238CBC, 0x0000FF03, MOD12_02238D08, 0x0000FF03
	.word MOD12_02238D58, 0x0000FF03, MOD12_02238D94, 0x0000FF03
	.word MOD12_02238DD0, 0x0000FF03, MOD12_02238E24, 0x0000FF03
	.word MOD12_02238EE8, 0x0000FF03, MOD12_02238F4C, 0x0000FF03
	.word MOD12_02238FAC, 0x0000FF06

	.global MOD12_022456D4
MOD12_022456D4: ; 0x022456D4
	.byte 0xE6, 0x80, 0x33, 0x00

	.global MOD12_022456D8
MOD12_022456D8: ; 0x022456D8
	.byte 0x00, 0x00, 0x00, 0x00
	.word MOD12_02239438, MOD12_02239448, MOD12_02239460, MOD12_02239478
	.word MOD12_02239490, MOD12_022394A8, MOD12_022394C0, MOD12_022394D8
	.word MOD12_022394F0, MOD12_02239508, MOD12_02239520, MOD12_02239538
	.word MOD12_02239564, MOD12_02239594, MOD12_022395B4, MOD12_022395D0
	.word MOD12_02239618, MOD12_02239660, MOD12_02239678, MOD12_02239690
	.word MOD12_022396BC, MOD12_022396E8, MOD12_02239714, MOD12_02239740
	.word MOD12_0223976C, MOD12_02239798, MOD12_022397C4, MOD12_022397F0

	.global MOD12_0224574C
MOD12_0224574C: ; 0x0224574C
	.byte 0x01, 0x14, 0xF0, 0x01, 0x46, 0x00, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x01, 0x14, 0x16, 0x01
	.byte 0x64, 0x00, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x01, 0x14, 0x08, 0x01, 0x28, 0x00, 0x14, 0x00
	.byte 0x14, 0x00, 0xEC, 0xFF, 0x01, 0x14, 0x17, 0x02, 0x0A, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x15, 0xF0, 0x02, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x16, 0x10, 0x01
	.byte 0x28, 0x00, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x01, 0x17, 0x0A, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x18, 0x09, 0x00, 0x18, 0xFC, 0x14, 0x00, 0xEC, 0xFF, 0x00, 0x00
	.byte 0x01, 0x19, 0x09, 0x01, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x00, 0x00, 0x01, 0x1A, 0x06, 0x03
	.byte 0x0A, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1B, 0x06, 0x01, 0x0A, 0x00, 0x14, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x1C, 0x0D, 0x01, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF
	.byte 0x01, 0x0E, 0x04, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x14, 0x00, 0x14, 0x00, 0x01, 0x0F, 0xF0, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x14, 0x00, 0x14, 0x00, 0x01, 0x0F, 0x01, 0x00, 0x0A, 0x00, 0x14, 0x00
	.byte 0x14, 0x00, 0x14, 0x00, 0x01, 0x10, 0x0D, 0x01, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00
	.byte 0x01, 0x11, 0x0D, 0x01, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x01, 0x01, 0x0B, 0x00
	.byte 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x18, 0xFC, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x0E, 0x00, 0x18, 0xFC, 0x00, 0x00, 0xEC, 0xFF, 0x00, 0x00
	.byte 0x01, 0x01, 0x02, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xF1, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x01, 0x02, 0x09, 0x00, 0x0A, 0x00, 0x14, 0x00
	.byte 0xEC, 0xFF, 0x14, 0x00, 0x01, 0x02, 0x02, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x02, 0x01, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0E, 0x00
	.byte 0x18, 0xFC, 0x00, 0x00, 0xEC, 0xFF, 0x00, 0x00, 0x01, 0x02, 0x0B, 0x00, 0x18, 0xFC, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x17, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x03, 0x05, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x01, 0x03, 0x0B, 0x00
	.byte 0x19, 0x00, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x01, 0x04, 0x0B, 0x00, 0x0A, 0x00, 0x14, 0x00
	.byte 0x14, 0x00, 0xEC, 0xFF, 0x01, 0x05, 0x0C, 0x00, 0x18, 0xFC, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF
	.byte 0x01, 0x06, 0x02, 0x00, 0x28, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x01, 0x06, 0x0B, 0x00
	.byte 0x32, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x01, 0x07, 0x11, 0x00, 0x1E, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0xEC, 0xFF, 0x01, 0x08, 0x12, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF
	.byte 0x01, 0x09, 0x13, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x01, 0x0A, 0x14, 0x00
	.byte 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x01, 0x0B, 0x15, 0x00, 0x18, 0xFC, 0x00, 0x00
	.byte 0x00, 0x00, 0xEC, 0xFF, 0x01, 0x0B, 0x0B, 0x00, 0x23, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0xEC, 0xFF
	.byte 0x01, 0x0B, 0x02, 0x00, 0x28, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0xEC, 0xFF, 0x01, 0x0C, 0x0E, 0x00
	.byte 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x14, 0x00, 0x01, 0x0C, 0x09, 0x00, 0x14, 0x00, 0x14, 0x00
	.byte 0xEC, 0xFF, 0x14, 0x00, 0x01, 0x0D, 0x09, 0x00, 0x3C, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x14, 0x00
	.byte 0x02, 0x14, 0xF0, 0x01, 0x32, 0x00, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x02, 0x14, 0x16, 0x01
	.byte 0x50, 0x00, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x02, 0x14, 0x08, 0x01, 0x28, 0x00, 0x14, 0x00
	.byte 0x14, 0x00, 0xEC, 0xFF, 0x02, 0x14, 0x0C, 0x01, 0x32, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0xEC, 0xFF
	.byte 0x02, 0x14, 0x14, 0x01, 0x28, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x02, 0x14, 0x17, 0x02
	.byte 0x14, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x02, 0x16, 0x10, 0x01, 0x1E, 0x00, 0x14, 0x00
	.byte 0x00, 0x00, 0xEC, 0xFF, 0x02, 0x17, 0x0A, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF
	.byte 0x02, 0x18, 0x09, 0x00, 0x18, 0xFC, 0x14, 0x00, 0xEC, 0xFF, 0xEC, 0xFF, 0x02, 0x19, 0x09, 0x01
	.byte 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0xEC, 0xFF, 0x02, 0x1A, 0x06, 0x03, 0x1E, 0x00, 0x14, 0x00
	.byte 0xEC, 0xFF, 0xEC, 0xFF, 0x02, 0x1B, 0x06, 0x01, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF
	.byte 0x02, 0x1C, 0x0D, 0x01, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x02, 0x0E, 0x04, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x14, 0x00, 0x14, 0x00, 0x02, 0x0F, 0xF0, 0x00, 0x0F, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x14, 0x00, 0x02, 0x0F, 0x01, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x14, 0x00, 0x14, 0x00
	.byte 0x02, 0x10, 0x0D, 0x01, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x02, 0x01, 0x0B, 0x00
	.byte 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x01, 0x00, 0x18, 0xFC, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x0E, 0x00, 0x18, 0xFC, 0x00, 0x00, 0xEC, 0xFF, 0x14, 0x00
	.byte 0x02, 0x01, 0x02, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0xF1, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x14, 0x00, 0x14, 0x00, 0x02, 0x02, 0x17, 0x00, 0x18, 0xFC, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x09, 0x00, 0x0A, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x14, 0x00
	.byte 0x02, 0x02, 0x02, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x01, 0x00
	.byte 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x0E, 0x00, 0x18, 0xFC, 0x00, 0x00
	.byte 0xEC, 0xFF, 0x14, 0x00, 0x02, 0x02, 0x0B, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x03, 0x0B, 0x00, 0x1E, 0x00, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x02, 0x04, 0x0B, 0x00
	.byte 0x0A, 0x00, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x02, 0x06, 0x0B, 0x00, 0x32, 0x00, 0x14, 0x00
	.byte 0x14, 0x00, 0xEC, 0xFF, 0x02, 0x06, 0x02, 0x00, 0x28, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF
	.byte 0x02, 0x06, 0x0E, 0x00, 0x0A, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0xEC, 0xFF, 0x02, 0x07, 0x11, 0x00
	.byte 0x18, 0xFC, 0x00, 0x00, 0xEC, 0xFF, 0xEC, 0xFF, 0x02, 0x08, 0x12, 0x00, 0x18, 0xFC, 0x00, 0x00
	.byte 0xEC, 0xFF, 0xEC, 0xFF, 0x02, 0x09, 0x13, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF
	.byte 0x02, 0x0B, 0x02, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x02, 0x0B, 0x15, 0x00
	.byte 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x02, 0x0B, 0x0B, 0x00, 0x28, 0x00, 0x14, 0x00
	.byte 0x00, 0x00, 0xEC, 0xFF, 0x02, 0x0B, 0x0E, 0x00, 0x0A, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF
	.byte 0x02, 0x0C, 0x0E, 0x00, 0x14, 0x00, 0x14, 0x00, 0x00, 0x00, 0x14, 0x00, 0x02, 0x0C, 0x09, 0x00
	.byte 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x14, 0x00, 0x02, 0x0D, 0x09, 0x00, 0x3C, 0x00, 0x14, 0x00
	.byte 0xEC, 0xFF, 0x14, 0x00, 0x03, 0x14, 0x10, 0x01, 0x28, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF
	.byte 0x03, 0x14, 0x14, 0x01, 0x28, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x03, 0x14, 0x0C, 0x01
	.byte 0x28, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0xEC, 0xFF, 0x03, 0x15, 0x14, 0x01, 0x28, 0x00, 0x14, 0x00
	.byte 0x00, 0x00, 0xEC, 0xFF, 0x03, 0x15, 0x0C, 0x01, 0x1E, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0xEC, 0xFF
	.byte 0x03, 0x15, 0xF0, 0x01, 0x1E, 0x00, 0x00, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x03, 0x17, 0x0A, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x03, 0x18, 0x09, 0x00, 0x18, 0xFC, 0x14, 0x00
	.byte 0xEC, 0xFF, 0xEC, 0xFF, 0x03, 0x19, 0x09, 0x01, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0xEC, 0xFF
	.byte 0x03, 0x1A, 0x06, 0x03, 0x1E, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x03, 0x1C, 0x0D, 0x01
	.byte 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x03, 0x0E, 0x04, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x14, 0x00, 0x03, 0x0F, 0xF0, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x14, 0x00, 0x14, 0x00
	.byte 0x03, 0x0F, 0x01, 0x00, 0x0A, 0x00, 0x14, 0x00, 0x14, 0x00, 0x14, 0x00, 0x03, 0x01, 0x0B, 0x00
	.byte 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x00, 0x18, 0xFC, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x0E, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00
	.byte 0x03, 0x01, 0x02, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x17, 0x00
	.byte 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x09, 0x00, 0x0A, 0x00, 0x14, 0x00
	.byte 0xEC, 0xFF, 0x14, 0x00, 0x03, 0x02, 0x02, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x02, 0x01, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x0E, 0x00
	.byte 0x18, 0xFC, 0x00, 0x00, 0xEC, 0xFF, 0x14, 0x00, 0x03, 0x02, 0x0B, 0x00, 0x18, 0xFC, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0xF1, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x03, 0x03, 0x0B, 0x00, 0x1E, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x03, 0x04, 0x0B, 0x00
	.byte 0x0A, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x03, 0x06, 0x02, 0x00, 0x28, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0xEC, 0xFF, 0x03, 0x06, 0x0E, 0x00, 0x0A, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF
	.byte 0x03, 0x06, 0x0B, 0x00, 0x14, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x03, 0x07, 0x11, 0x00
	.byte 0x18, 0xFC, 0x00, 0x00, 0xEC, 0xFF, 0xEC, 0xFF, 0x03, 0x08, 0x12, 0x00, 0x18, 0xFC, 0x00, 0x00
	.byte 0xEC, 0xFF, 0xEC, 0xFF, 0x03, 0x09, 0x13, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF
	.byte 0x03, 0x0B, 0x0E, 0x00, 0x0A, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0xEC, 0xFF, 0x03, 0x0B, 0x02, 0x00
	.byte 0x14, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x03, 0x0B, 0x0B, 0x00, 0x14, 0x00, 0x14, 0x00
	.byte 0x00, 0x00, 0xEC, 0xFF, 0x03, 0x0B, 0x15, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF
	.byte 0x03, 0x0C, 0x0E, 0x00, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x14, 0x00, 0x03, 0x0C, 0x09, 0x00
	.byte 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x14, 0x00, 0x03, 0x0D, 0x09, 0x00, 0x3C, 0x00, 0x14, 0x00
	.byte 0xEC, 0xFF, 0x14, 0x00, 0x04, 0x14, 0x10, 0x01, 0x28, 0x00, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF
	.byte 0x04, 0x14, 0x0C, 0x01, 0x28, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0xEC, 0xFF, 0x04, 0x14, 0x14, 0x01
	.byte 0x14, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x04, 0x15, 0x10, 0x01, 0x1E, 0x00, 0x14, 0x00
	.byte 0x00, 0x00, 0xEC, 0xFF, 0x04, 0x15, 0x0C, 0x01, 0x1E, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0xEC, 0xFF
	.byte 0x04, 0x15, 0x14, 0x01, 0x28, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x04, 0x17, 0x0A, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x04, 0x18, 0x09, 0x00, 0x18, 0xFC, 0x14, 0x00
	.byte 0xEC, 0xFF, 0xEC, 0xFF, 0x04, 0x19, 0x09, 0x01, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0xEC, 0xFF
	.byte 0x04, 0x1A, 0x06, 0x03, 0x1E, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x04, 0x0E, 0x04, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x04, 0x0F, 0xF0, 0x00, 0x0F, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x14, 0x00, 0x04, 0x0F, 0x01, 0x00, 0x0A, 0x00, 0x14, 0x00, 0x14, 0x00, 0x14, 0x00
	.byte 0x04, 0x01, 0x0B, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x01, 0x01, 0x00
	.byte 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x01, 0x0E, 0x00, 0x18, 0xFC, 0x00, 0x00
	.byte 0xEC, 0xFF, 0x14, 0x00, 0x04, 0x01, 0x02, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x02, 0x17, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0x09, 0x00
	.byte 0x0A, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x14, 0x00, 0x04, 0x02, 0x02, 0x00, 0x18, 0xFC, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0x01, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x02, 0x0E, 0x00, 0x18, 0xFC, 0x00, 0x00, 0xEC, 0xFF, 0x14, 0x00, 0x04, 0x02, 0x0B, 0x00
	.byte 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0xF1, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x14, 0x00, 0x04, 0x02, 0x15, 0x00, 0x50, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x02, 0x0F, 0x00, 0x50, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x12, 0x08, 0x00
	.byte 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x04, 0x13, 0x0D, 0x00, 0x18, 0xFC, 0x00, 0x00
	.byte 0x00, 0x00, 0xEC, 0xFF, 0x04, 0x06, 0x0B, 0x00, 0x1E, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF
	.byte 0x04, 0x06, 0x0F, 0x00, 0x3C, 0x00, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x04, 0x07, 0x11, 0x00
	.byte 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x04, 0x08, 0x12, 0x00, 0x28, 0x00, 0x14, 0x00
	.byte 0x14, 0x00, 0xEC, 0xFF, 0x04, 0x09, 0x13, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFF
	.byte 0x04, 0x0B, 0x15, 0x00, 0x3C, 0x00, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x04, 0x0B, 0x0B, 0x00
	.byte 0x0A, 0x00, 0x14, 0x00, 0x00, 0x00, 0xEC, 0xFF, 0x04, 0x0C, 0x0E, 0x00, 0x14, 0x00, 0x14, 0x00
	.byte 0xEC, 0xFF, 0x14, 0x00, 0x04, 0x0C, 0x09, 0x00, 0x14, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x14, 0x00
	.byte 0x04, 0x0D, 0x09, 0x00, 0x3C, 0x00, 0x14, 0x00, 0xEC, 0xFF, 0x14, 0x00, 0x09, 0x00, 0x0A, 0x00
	.byte 0x0B, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x00, 0x00

	.global MOD12_02245F14
MOD12_02245F14: ; 0x02245F14
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xEA, 0x80, 0x00, 0x00
	.byte 0xEA, 0x80, 0x00, 0x00, 0xEA, 0x80, 0x00, 0x00, 0xEA, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02245F48
MOD12_02245F48: ; 0x02245F48
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00
	.byte 0x03, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00

	.global MOD12_02245F84
MOD12_02245F84: ; 0x02245F84
	.byte 0x0D, 0x09, 0x05, 0x01, 0xFD, 0x00, 0x00, 0x00

	.global MOD12_02245F8C
MOD12_02245F8C: ; 0x02245F8C
	.short 0x20, 0x28, 0x30, 0x38, 0xA0, 0xA8, 0xB0, 0xB8
	.short 0x0120, 0x0128, 0x0130, 0x0138

	.global MOD12_02245FA4
MOD12_02245FA4: ; 0x02245FA4
	.word MOD12_02239BC8, MOD12_02239BDC
	.word MOD12_02239BEC, MOD12_02239BF0, MOD12_02239C04, 0x00000000
	.word MOD12_02239C1C, MOD12_02239C30, 0x00000000, MOD12_02239E98
	.word MOD12_02239EAC, 0x00000000, MOD12_02239FA8, MOD12_02239FBC
	.word 0x00000000, MOD12_02239FA8, MOD12_0223A00C, 0x00000000
	.word MOD12_02239FA8, MOD12_0223A05C, 0x00000000, MOD12_0223A268
	.word MOD12_0223A27C, 0x00000000, MOD12_0223A388, MOD12_0223A39C
	.word 0x00000000, MOD12_0223A53C, MOD12_0223A550, 0x00000000
	.word MOD12_0223A718, MOD12_0223A72C, 0x00000000, MOD12_0223A814
	.word MOD12_0223A828, 0x00000000, MOD12_0223A918, MOD12_0223A92C
	.word 0x00000000, MOD12_0223AE44, MOD12_0223AE58, 0x00000000
	.word MOD12_0223AF74, MOD12_0223AF88, 0x00000000, MOD12_0223B0D8
	.word MOD12_0223B0EC, 0x00000000, MOD12_0223B368, MOD12_0223B37C
	.word 0x00000000

	.global MOD12_02246070
MOD12_02246070: ; 0x02246070
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00

	.global MOD12_02246080
MOD12_02246080: ; 0x02246080
	.byte 0x00, 0x50, 0x58, 0xA8, 0x60, 0xB0, 0x58, 0xA8, 0x28, 0x78, 0x08, 0x58
	.byte 0x28, 0x78, 0xA8, 0xF8, 0xFF, 0x00, 0x00, 0x00

	.global MOD12_02246094
MOD12_02246094: ; 0x02246094
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF
	.byte 0x01, 0x00, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.word 0x00000000, MOD12_0223B934, 0x00000000, 0x00010001
	.byte 0x02, 0x00, 0xFF, 0xFF, 0x03, 0x00, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00
	.word MOD12_02246080, MOD12_02246070, MOD12_0223BA00, MOD12_0223BB20

	.global MOD12_022460DC
MOD12_022460DC: ; 0x022460DC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0D, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_0224614C
MOD12_0224614C: ; 0x0224614C
	.byte 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x12, 0x00, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0C, 0x00

	.global MOD12_0224617C
MOD12_0224617C: ; 0x0224617C
	.byte 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x12, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0C, 0x00

	.global MOD12_022461AC
MOD12_022461AC: ; 0x022461AC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x12, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0C, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0C, 0x00

	.global MOD12_022461DC
MOD12_022461DC: ; 0x022461DC
	.byte 0xB0, 0xA8, 0xB0, 0xB8

	.global MOD12_022461E0
MOD12_022461E0: ; 0x022461E0
	.byte 0x03, 0x03, 0x04, 0x04

	.global MOD12_022461E4
MOD12_022461E4: ; 0x022461E4
	.short 0x80, 0x58, 0x30, 0x20, 0x80, 0x20, 0xD0, 0x20

	.global MOD12_022461F4
MOD12_022461F4: ; 0x022461F4
	.short 0x80, 0x60, -0x200, 0x30, 0x28, -0x280, 0x80, 0x28
	.short -0x280, 0xD0, 0x28, -0x280

	.global MOD12_0224620C
MOD12_0224620C: ; 0x0224620C
	.byte 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x07, 0x00, 0x00, 0x7C, 0x07, 0x00, 0xE0, 0x03, 0x07, 0x00
	.byte 0xFF, 0x27, 0x08, 0x00, 0x00, 0x00, 0x07, 0x00

	.global MOD12_02246224
MOD12_02246224: ; 0x02246224
	.short 0x00, 0x00, 0x08, 0x06, 0x14, 0x01, 0x0B, 0x00
	.short 0x09, 0x03, 0x0A, 0x03, 0x12, 0x04, 0x13, 0x00

	.global MOD12_02246244
MOD12_02246244: ; 0x02246244
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x2D, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xF0, 0x80, 0x00, 0x00
	.byte 0xE9, 0x80, 0x00, 0x00, 0xED, 0x80, 0x00, 0x00, 0xED, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02246278
MOD12_02246278: ; 0x02246278
	.byte 0x00, 0x00, 0x90, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0xF1, 0x80, 0x00, 0x00, 0xE9, 0x80, 0x00, 0x00, 0xEE, 0x80, 0x00, 0x00, 0xEE, 0x80, 0x00, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_022462AC
MOD12_022462AC: ; 0x022462AC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xF2, 0x80, 0x00, 0x00, 0xE9, 0x80, 0x00, 0x00, 0xEF, 0x80, 0x00, 0x00
	.byte 0xEF, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD12_022462E0
MOD12_022462E0: ; 0x022462E0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xEB, 0x80, 0x00, 0x00, 0xE9, 0x80, 0x00, 0x00
	.byte 0xEB, 0x80, 0x00, 0x00, 0xEB, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02246314
MOD12_02246314: ; 0x02246314
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x0D, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xEF, 0x80, 0x00, 0x00
	.byte 0xE9, 0x80, 0x00, 0x00, 0xEC, 0x80, 0x00, 0x00, 0xEC, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02246348
MOD12_02246348: ; 0x02246348
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0xF4, 0x80, 0x00, 0x00, 0xE9, 0x80, 0x00, 0x00, 0xF1, 0x80, 0x00, 0x00, 0xF1, 0x80, 0x00, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_0224637C
MOD12_0224637C: ; 0x0224637C
	.byte 0x08, 0x8A, 0xFF, 0xFF, 0x04, 0x91, 0xFF, 0xFF, 0xFF, 0x97, 0xFF, 0xFF, 0xFB, 0x9E, 0xFF, 0xFF
	.byte 0xF6, 0xA5, 0xFF, 0xFF, 0xF2, 0xAC, 0xFF, 0xFF, 0xED, 0xB3, 0xFF, 0xFF, 0x21, 0xBA, 0xFF, 0xFF
	.byte 0xE4, 0xC1, 0xFF, 0xFF, 0xE0, 0xC8, 0xFF, 0xFF, 0xDB, 0xCF, 0xFF, 0xFF, 0xD7, 0xD6, 0xFF, 0xFF
	.byte 0xD2, 0xDD, 0xFF, 0xFF, 0xCE, 0xE4, 0xFF, 0xFF, 0xC9, 0xEB, 0xFF, 0xFF, 0xC5, 0xF2, 0xFF, 0xFF
	.byte 0xC0, 0xF9, 0xFF, 0xFF, 0xBB, 0x00, 0x00, 0x00, 0xB7, 0x07, 0x00, 0x00, 0xB2, 0x0E, 0x00, 0x00
	.byte 0xAE, 0x15, 0x00, 0x00, 0xA9, 0x1C, 0x00, 0x00, 0xA5, 0x23, 0x00, 0x00, 0xA0, 0x2A, 0x00, 0x00
	.byte 0x9C, 0x31, 0x00, 0x00, 0x97, 0x38, 0x00, 0x00, 0x93, 0x3F, 0x00, 0x00, 0x8E, 0x46, 0x00, 0x00
	.byte 0x8A, 0x4D, 0x00, 0x00, 0x85, 0x54, 0x00, 0x00, 0x81, 0x5B, 0x00, 0x00, 0x7C, 0x62, 0x00, 0x00
	.byte 0x78, 0x69, 0x00, 0x00

	.global MOD12_02246400
MOD12_02246400: ; 0x02246400
	.byte 0x00, 0x04, 0x08, 0x0C

	.global MOD12_02246404
MOD12_02246404: ; 0x02246404
	.byte 0x0F, 0x0B, 0x07, 0x03, 0xFF, 0x00, 0x00, 0x00

	.global MOD12_0224640C
MOD12_0224640C: ; 0x0224640C
	.short 0x20, 0x28, 0x30, 0x38, 0xA0, 0xA8, 0xB0, 0xB8
	.short 0x120, 0x128, 0x130, 0x138

	.global MOD12_02246424
MOD12_02246424: ; 0x02246424
	.word MOD12_0223EEC0, MOD12_0223EED4
	.word MOD12_0223EEE4, MOD12_0223EEE8, MOD12_0223EEFC, 0x00000000
	.word MOD12_0223F09C, MOD12_0223F0B0, 0x00000000, MOD12_0223F28C
	.word MOD12_0223F2A0, 0x00000000, MOD12_0223F3B4, MOD12_0223F3C8
	.word 0x00000000, MOD12_0223F400, MOD12_0223F414, MOD12_0223FDD0
	.word MOD12_0223FDD4, MOD12_0223FDE8, 0x00000000, MOD12_02240274
	.word MOD12_02240288, 0x00000000, MOD12_02240350, MOD12_02240364
	.word 0x00000000, MOD12_0224048C, MOD12_022404A0, 0x00000000
	.word MOD12_022405C0, MOD12_022405D4, 0x00000000, MOD12_022405F8
	.word MOD12_0224060C, 0x00000000, MOD12_02240644, MOD12_02240658
	.word 0x00000000

	.global MOD12_022464C0
MOD12_022464C0: ; 0x022464C0
	.byte 0x01, 0x02, 0x03, 0x04

	.global MOD12_022464C4
MOD12_022464C4: ; 0x022464C4
	.byte 0x5A, 0x28, 0x00, 0x00

	.global MOD12_022464C8
MOD12_022464C8: ; 0x022464C8
	.byte 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x00, 0x00, 0x00

	.global MOD12_022464D0
MOD12_022464D0: ; 0x022464D0
	.word 0x30, 0x34, 0x33, 0x35
	.word 0x36

	.global MOD12_022464E4
MOD12_022464E4: ; 0x022464E4
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD12_022464F4
MOD12_022464F4: ; 0x022464F4
	.byte 0x14, 0x00, 0x23, 0x00, 0x08, 0x00, 0x1E, 0x00
	.byte 0x15, 0x00, 0x19, 0x00, 0x1E, 0x00, 0x0F, 0x00

	.global MOD12_02246504
MOD12_02246504: ; 0x02246504
	.byte 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00
	.byte 0x00, 0x40, 0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD12_02246518
MOD12_02246518: ; 0x02246518
	.byte 0x60, 0x00, 0x00, 0x00
	.byte 0x20, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00

	.global MOD12_02246530
MOD12_02246530: ; 0x02246530
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0F, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_0224654C
MOD12_0224654C: ; 0x0224654C
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00

	.global MOD12_0224656C
MOD12_0224656C: ; 0x0224656C
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD12_02246594
MOD12_02246594: ; 0x02246594
	.word MOD12_02241BFC, MOD12_02241D10
	.word MOD12_02241D94, MOD12_02241DF8, MOD12_02241E88, MOD12_02241F94
	.word MOD12_022420C0, MOD12_022421F4, MOD12_02242258, MOD12_0224233C
	.word MOD12_022423BC

	.global MOD12_022465C0
MOD12_022465C0: ; 0x022465C0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x02, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x06, 0x01
	.byte 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02246614
MOD12_02246614: ; 0x02246614
	.short 0x1C, 0x14, 0x1C, 0x34, 0x1C, 0x54, 0x1C, 0x74

	.global MOD12_02246624
MOD12_02246624: ; 0x02246624
	.short 0xE8, 0x0D, 0xE8, 0x2D, 0xE8, 0x4D, 0xE8, 0x6D

	.global MOD12_02246634
MOD12_02246634: ; 0x02246634
	.short 0x2C, 0x46, -0x200, 0x64, 0x46, -0x280, 0x9C, 0x46
	.short -0x280, 0xD4, 0x46, -0x280

	.global MOD12_0224664C
MOD12_0224664C: ; 0x0224664C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x03, 0x00, 0x05, 0x00, 0x00, 0x00

	.global MOD12_02246668
MOD12_02246668: ; 0x02246668
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0xEF, 0x80, 0x00, 0x00, 0xE9, 0x80, 0x00, 0x00, 0xEC, 0x80, 0x00, 0x00, 0xEC, 0x80, 0x00, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_0224669C
MOD12_0224669C: ; 0x0224669C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xEA, 0x80, 0x00, 0x00, 0xEB, 0x80, 0x00, 0x00, 0xEA, 0x80, 0x00, 0x00
	.byte 0xEA, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD12_022466D0
MOD12_022466D0: ; 0x022466D0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xEE, 0x80, 0x00, 0x00, 0xE9, 0x80, 0x00, 0x00
	.byte 0xEB, 0x80, 0x00, 0x00, 0xEB, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02246704
MOD12_02246704: ; 0x02246704
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xF0, 0x80, 0x00, 0x00
	.byte 0xEC, 0x80, 0x00, 0x00, 0xED, 0x80, 0x00, 0x00, 0xED, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD12_02246738
MOD12_02246738: ; 0x02246738
	.byte 0x0F, 0x0B, 0x07, 0x03, 0xFF, 0x00, 0x00, 0x00

	.global MOD12_02246740
MOD12_02246740: ; 0x02246740
	.byte 0x20, 0x00, 0x28, 0x00, 0x30, 0x00, 0x38, 0x00, 0xA0, 0x00, 0xA8, 0x00
	.byte 0xB0, 0x00, 0xB8, 0x00, 0x20, 0x01, 0x28, 0x01, 0x30, 0x01, 0x38, 0x01

	.global MOD12_02246758
MOD12_02246758: ; 0x02246758
	.word MOD12_02243A60
	.word MOD12_02243A74, MOD12_02243A84, MOD12_02243A88, MOD12_02243A9C
	.word 0x00000000, MOD12_02243B08, MOD12_02243B1C, 0x00000000
	.word MOD12_02243CBC, MOD12_02243CD0, 0x00000000, MOD12_02243E98
	.word MOD12_02243EAC, 0x00000000, MOD12_02243EC4, MOD12_02243ED8
	.word 0x00000000, MOD12_02243FF8, MOD12_0224400C, 0x00000000
	.word MOD12_022441C8, MOD12_022441DC, 0x00000000, MOD12_022442C0
	.word MOD12_022442D4, 0x00000000, MOD12_02244438, MOD12_0224444C
	.word 0x00000000, MOD12_02244610, MOD12_02244624, 0x00000000

	.global MOD12_022467DC
MOD12_022467DC: ; 0x022467DC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.section .sinit
	.word MOD12_022312BC
