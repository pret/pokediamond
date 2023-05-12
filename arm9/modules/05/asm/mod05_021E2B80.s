	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021E2B80
MOD05_021E2B80: ; 0x021E2B80
	add r2, r0, #0
	add r2, #0x97
	ldrb r3, [r2]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	mov r2, #0x40
	lsl r1, r1, #0x1f
	bic r3, r2
	lsr r1, r1, #0x19
	orr r1, r3
	add r0, #0x97
	strb r1, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021E2B9C
MOD05_021E2B9C: ; 0x021E2B9C
	add r2, r0, #0
	add r2, #0x97
	ldrb r3, [r2]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	mov r2, #0x80
	lsl r1, r1, #0x1f
	bic r3, r2
	lsr r1, r1, #0x18
	orr r1, r3
	add r0, #0x97
	strb r1, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021E2BB8
MOD05_021E2BB8: ; 0x021E2BB8
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	bl MOD05_ScriptContext_GetTextFrameDelay
	strb r0, [r4]
	mov r0, #0
	strb r0, [r4, #1]
	mov r0, #1
	strb r0, [r4, #2]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E2BD0
MOD05_021E2BD0: ; 0x021E2BD0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	str r3, [sp, #4]
	add r0, #0x80
	add r6, r1, #0
	ldr r0, [r0]
	add r1, sp, #8
	add r7, r2, #0
	ldr r4, [sp, #0x38]
	bl MOD05_021E2D14
	add r0, r5, #0
	add r0, #0x80
	ldr r0, [r0]
	add r1, sp, #8
	bl MOD05_CreateMessageBox
	add r0, sp, #8
	add r1, r6, #0
	add r2, r7, #0
	bl MOD05_ReadAndExpandMsgDataViaBuffer
	cmp r4, #0
	bne _021E2C10
	add r0, r5, #0
	bl MOD05_ScriptContext_GetTextFrameDelay
	add r2, r0, #0
	mov r0, #0
	mov r1, #1
	b _021E2C16
_021E2C10:
	ldrb r2, [r4]
	ldrb r0, [r4, #1]
	ldrb r1, [r4, #2]
_021E2C16:
	str r0, [sp]
	ldr r3, [sp, #4]
	add r0, sp, #8
	bl MOD05_DrawFieldMessage
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_ShowMessageInField
MOD05_ShowMessageInField: ; 0x021E2C24
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r0, #0x80
	add r4, r1, #0
	ldr r0, [r0]
	add r1, sp, #0
	add r6, r2, #0
	bl MOD05_021E2D14
	add r5, #0x80
	ldr r0, [r5]
	add r1, sp, #0
	bl MOD05_CreateMessageBox
	add r0, sp, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD05_ReadAndExpandMsgDataViaBuffer
	add r0, sp, #0
	mov r1, #1
	bl MOD05_AddTextPrinterParameterized
	add sp, #0x18
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021E2C58
MOD05_021E2C58: ; 0x021E2C58
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	add r0, #0x80
	add r4, r1, #0
	ldr r0, [r0]
	add r1, sp, #4
	add r6, r2, #0
	add r7, r3, #0
	bl MOD05_021E2D14
	add r0, r5, #0
	add r0, #0x80
	ldr r0, [r0]
	add r1, sp, #4
	bl MOD05_CreateMessageBox
	add r0, sp, #0x20
	ldrh r0, [r0, #0x10]
	add r1, r4, #0
	add r2, r6, #0
	str r0, [sp]
	add r0, sp, #4
	add r3, r7, #0
	bl MOD05_ExpandEasyChatMessage
	add r0, sp, #0x20
	ldrb r0, [r0, #0x14]
	cmp r0, #0xff
	beq _021E2CB0
	add r0, r5, #0
	bl MOD05_ScriptContext_GetTextFrameDelay
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	add r3, sp, #0x20
	ldrb r3, [r3, #0x14]
	add r0, sp, #4
	mov r1, #1
	bl MOD05_DrawFieldMessage
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
_021E2CB0:
	add r0, sp, #4
	mov r1, #1
	bl MOD05_AddTextPrinterParameterized
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021E2CBC
MOD05_021E2CBC: ; 0x021E2CBC
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r5, r0, #0
	add r0, #0x80
	add r4, r2, #0
	ldr r0, [r0]
	add r2, sp, #4
	add r6, r3, #0
	bl MOD05_021E2D5C
	add r0, r5, #0
	add r0, #0x80
	ldr r0, [r0]
	add r1, sp, #4
	bl MOD05_CreateMessageBox
	ldr r1, [r5, #0x78]
	add r0, sp, #4
	add r2, r4, #0
	bl MOD05_ReadAndExpandMsgDataViaBuffer
	add r0, r5, #0
	bl MOD05_ScriptContext_GetTextFrameDelay
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	add r0, sp, #4
	mov r1, #1
	add r3, r6, #0
	bl MOD05_DrawFieldMessage
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}

	thumb_func_start MOD05_ScriptContext_GetTextFrameDelay
MOD05_ScriptContext_GetTextFrameDelay: ; 0x021E2D00
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	bl Options_GetTextFrameDelay
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E2D14
MOD05_021E2D14: ; 0x021E2D14
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #0x10
	add r5, r0, #0
	bl FieldSysGetAttrAddr
	ldr r0, [r0]
	mov r1, #0x11
	str r0, [r4]
	add r0, r5, #0
	bl FieldSysGetAttrAddr
	ldr r0, [r0]
	mov r1, #0xf
	str r0, [r4, #4]
	add r0, r5, #0
	bl FieldSysGetAttrAddr
	ldr r0, [r0]
	mov r1, #1
	str r0, [r4, #8]
	add r0, r5, #0
	bl FieldSysGetAttrAddr
	str r0, [r4, #0xc]
	add r0, r5, #0
	mov r1, #6
	bl FieldSysGetAttrAddr
	str r0, [r4, #0x10]
	add r0, r5, #0
	mov r1, #3
	bl FieldSysGetAttrAddr
	str r0, [r4, #0x14]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021E2D5C
MOD05_021E2D5C: ; 0x021E2D5C
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r1, #0x10
	add r5, r0, #0
	add r4, r2, #0
	bl FieldSysGetAttrAddr
	ldr r0, [r0]
	mov r1, #0x11
	str r0, [r4]
	add r0, r5, #0
	bl FieldSysGetAttrAddr
	ldr r0, [r0]
	mov r1, #1
	str r0, [r4, #4]
	str r6, [r4, #8]
	add r0, r5, #0
	bl FieldSysGetAttrAddr
	str r0, [r4, #0xc]
	add r0, r5, #0
	mov r1, #6
	bl FieldSysGetAttrAddr
	str r0, [r4, #0x10]
	add r0, r5, #0
	mov r1, #3
	bl FieldSysGetAttrAddr
	str r0, [r4, #0x14]
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_CreateMessageBox
MOD05_CreateMessageBox: ; 0x021E2D9C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x10]
	ldrb r0, [r0]
	cmp r0, #0
	bne _021E2DC8
	ldr r0, [r5, #8]
	ldr r1, [r4, #0xc]
	mov r2, #3
	bl FUN_020545B8
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r1, r0, #0
	ldr r0, [r4, #0xc]
	bl FUN_02054608
	ldr r0, [r4, #0x10]
	mov r1, #1
	strb r1, [r0]
_021E2DC8:
	ldr r0, [r4, #0xc]
	mov r1, #0xf
	bl FillWindowPixelBuffer
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_ReadAndExpandMsgDataViaBuffer
MOD05_ReadAndExpandMsgDataViaBuffer: ; 0x021E2DD4
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	add r1, r2, #0
	ldr r2, [r4, #4]
	bl ReadMsgDataIntoString
	ldr r0, [r4, #8]
	ldr r1, [r4]
	ldr r2, [r4, #4]
	bl StringExpandPlaceholders
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_ExpandEasyChatMessage
MOD05_ExpandEasyChatMessage: ; 0x021E2DF0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r0, sp, #0
	add r7, r3, #0
	bl MailMsg_init
	add r0, sp, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MailMsg_SetMsgBankAndNum
	add r0, sp, #0
	mov r1, #0
	add r2, r7, #0
	bl MailMsg_SetFieldI
	add r2, sp, #0x10
	ldrh r2, [r2, #0x10]
	add r0, sp, #0
	mov r1, #1
	bl MailMsg_SetFieldI
	add r0, sp, #0
	mov r1, #0x20
	bl MailMsg_GetExpandedString
	add r4, r0, #0
	ldr r0, [r5]
	add r1, r4, #0
	bl StringCopy
	add r0, r4, #0
	bl String_dtor
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_DrawFieldMessage
MOD05_DrawFieldMessage: ; 0x021E2E40
	push {r4, r5, r6, lr}
	sub sp, #8
	add r4, r0, #0
	lsl r0, r3, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [sp, #0x18]
	add r5, r2, #0
	str r0, [sp, #4]
	add r6, r1, #0
	ldr r0, [r4, #0xc]
	ldr r1, [r4]
	add r2, r6, #0
	add r3, r5, #0
	bl DrawFieldMessage
	ldr r1, [r4, #0x14]
	strb r0, [r1]
	add sp, #8
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_AddTextPrinterParameterized
MOD05_AddTextPrinterParameterized: ; 0x021E2E68
	push {r3, r4, lr}
	sub sp, #0xc
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	add r4, r0, #0
	str r3, [sp, #8]
	ldr r0, [r4, #0xc]
	ldr r2, [r4]
	bl AddTextPrinterParameterized
	ldr r1, [r4, #0x14]
	strb r0, [r1]
	add sp, #0xc
	pop {r3, r4, pc}
	.balign 4, 0
