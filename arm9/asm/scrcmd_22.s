    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start ScrCmd_AddItem
ScrCmd_AddItem: ; 0x02045784
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	add r1, r6, #0x0
	add r2, r7, #0x0
	mov r3, #0x4
	bl FUN_0206ED38
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_SubItem
ScrCmd_SubItem: ; 0x020457DC
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	add r1, r6, #0x0
	add r2, r7, #0x0
	mov r3, #0x4
	bl FUN_0206EDD4
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_AddItemChk
ScrCmd_AddItemChk: ; 0x02045834
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	add r1, r6, #0x0
	add r2, r7, #0x0
	mov r3, #0x4
	bl FUN_0206ED24
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_CheckItem
ScrCmd_CheckItem: ; 0x0204588C
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	add r1, r6, #0x0
	add r2, r7, #0x0
	mov r3, #0xb
	bl FUN_0206EE50
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_WazaMachineItemNoCheck
ScrCmd_WazaMachineItemNoCheck: ; 0x020458E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02054CB0
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_GetPocketNo
ScrCmd_GetPocketNo: ; 0x02045918
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0xb
	bl FUN_0206E7B8
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_AddPCBoxItem
ScrCmd_AddPCBoxItem: ; 0x02045950
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_CheckPCBoxItem
ScrCmd_CheckPCBoxItem: ; 0x02045954
	mov r0, #0x0
	bx lr
