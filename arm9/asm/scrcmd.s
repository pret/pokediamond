    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020F34E0
	.extern sScriptConditionTable
	.extern UNK_020F34FC
	.extern UNK_020F3538
	.extern gMain

	.section .bss

	.global UNK_021C5A0C
UNK_021C5A0C: ; 0x021C5A0C
	.space 0x4

	.text

	thumb_func_start ScrCmd_nop
ScrCmd_nop: ; 0x020399A0
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_nop2
ScrCmd_nop2: ; 0x020399A4
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_end
ScrCmd_end: ; 0x020399A8
	push {r3, lr}
	bl StopScript
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_delay
ScrCmd_delay: ; 0x020399B4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl GetVarPointer
	strh r7, [r0, #0x0]
	ldr r1, _020399E4 ; =RunPauseTimer
	add r0, r5, #0x0
	str r4, [r5, #0x64]
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_020399E4: .word RunPauseTimer 

	thumb_func_start RunPauseTimer
RunPauseTimer: ; 0x020399E8
	push {r3, lr}
	add r1, r0, #0x0
	ldr r1, [r1, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl GetVarPointer
	ldrh r1, [r0, #0x0]
	sub r1, r1, #0x1
	strh r1, [r0, #0x0]
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02039A0A
	mov r0, #0x1
	pop {r3, pc}
_02039A0A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_505
ScrCmd_unk_505: ; 0x02039A10
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_loadbyte
ScrCmd_loadbyte: ; 0x02039A28
	ldr r1, [r0, #0x8]
	add r2, r1, #0x1
	str r2, [r0, #0x8]
	ldrb r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r2, [r2, #0x0]
	lsl r1, r3, #0x2
	add r0, r0, r1
	str r2, [r0, #0x64]
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_loadword
ScrCmd_loadword: ; 0x02039A40
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r5, [r2, #0x0]
	bl ScriptReadWord
	lsl r1, r5, #0x2
	add r1, r4, r1
	str r0, [r1, #0x64]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_loadbytefromaddr
ScrCmd_loadbytefromaddr: ; 0x02039A5C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadWord
	ldrb r1, [r0, #0x0]
	lsl r0, r4, #0x2
	add r0, r5, r0
	str r1, [r0, #0x64]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_writebytetoaddr
ScrCmd_writebytetoaddr: ; 0x02039A78
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadWord
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	strb r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_setptrbyte
ScrCmd_setptrbyte: ; 0x02039A90
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadWord
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	lsl r1, r1, #0x2
	add r1, r4, r1
	ldr r1, [r1, #0x64]
	strb r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_copylocal
ScrCmd_copylocal: ; 0x02039AAC
	ldr r1, [r0, #0x8]
	add r2, r1, #0x1
	str r2, [r0, #0x8]
	ldrb r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	lsl r1, r1, #0x2
	add r1, r0, r1
	ldr r2, [r1, #0x64]
	lsl r1, r3, #0x2
	add r0, r0, r1
	str r2, [r0, #0x64]
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start ScrCmd_copybyte
ScrCmd_copybyte: ; 0x02039ACC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadWord
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadWord
	ldrb r0, [r0, #0x0]
	strb r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start compare_012
compare_012: ; 0x02039AE4
	cmp r0, r1
	bhs _02039AEC
	mov r0, #0x0
	bx lr
_02039AEC:
	cmp r0, r1
	bne _02039AF4
	mov r0, #0x1
	bx lr
_02039AF4:
	mov r0, #0x2
	bx lr

	thumb_func_start ScrCmd_compare_local_to_local
ScrCmd_compare_local_to_local: ; 0x02039AF8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x8]
	add r1, r0, #0x1
	str r1, [r4, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x64]
	str r2, [r4, #0x8]
	ldrb r1, [r1, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r1, r1, #0x2
	add r1, r4, r1
	ldr r1, [r1, #0x64]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl compare_012
	strb r0, [r4, #0x2]
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_compare_local_to_value
ScrCmd_compare_local_to_value: ; 0x02039B28
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x8]
	add r1, r0, #0x1
	str r1, [r4, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x64]
	str r2, [r4, #0x8]
	ldrb r1, [r1, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl compare_012
	strb r0, [r4, #0x2]
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_compare_local_to_addr
ScrCmd_compare_local_to_addr: ; 0x02039B50
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	lsl r1, r1, #0x2
	add r1, r4, r1
	ldr r1, [r1, #0x64]
	lsl r1, r1, #0x18
	lsr r5, r1, #0x18
	bl ScriptReadWord
	ldrb r1, [r0, #0x0]
	add r0, r5, #0x0
	bl compare_012
	strb r0, [r4, #0x2]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_compare_addr_to_local
ScrCmd_compare_addr_to_local: ; 0x02039B78
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadWord
	ldr r2, [r4, #0x8]
	ldrb r0, [r0, #0x0]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	lsl r1, r1, #0x2
	add r1, r4, r1
	ldr r1, [r1, #0x64]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl compare_012
	strb r0, [r4, #0x2]
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_compare_addr_to_value
ScrCmd_compare_addr_to_value: ; 0x02039BA0
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadWord
	ldr r2, [r4, #0x8]
	ldrb r0, [r0, #0x0]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	bl compare_012
	strb r0, [r4, #0x2]
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_compare_addr_to_addr
ScrCmd_compare_addr_to_addr: ; 0x02039BBC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadWord
	ldrb r4, [r0, #0x0]
	add r0, r5, #0x0
	bl ScriptReadWord
	ldrb r1, [r0, #0x0]
	add r0, r4, #0x0
	bl compare_012
	strb r0, [r5, #0x2]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_compare_var_to_value
ScrCmd_compare_var_to_value: ; 0x02039BDC
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	ldrh r5, [r0, #0x0]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl compare_012
	strb r0, [r4, #0x2]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_compare_var_to_var
ScrCmd_compare_var_to_var: ; 0x02039C08
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r1, r0, #0x0
	ldrh r0, [r4, #0x0]
	ldrh r1, [r1, #0x0]
	bl compare_012
	strb r0, [r5, #0x2]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_19
ScrCmd_unk_19: ; 0x02039C40
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x7
	add r0, r5, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xe
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl CreateScriptContext
	str r0, [r6, #0x0]
	ldrb r0, [r4, #0x0]
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_20
ScrCmd_unk_20: ; 0x02039C78
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x5
	add r0, r5, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x7
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xe
	bl FUN_02039438
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	mov r0, #0x1
	strb r0, [r6, #0x0]
	add r0, r5, #0x0
	bl CreateScriptContext
	str r0, [r7, #0x0]
	ldrb r0, [r4, #0x0]
	ldr r1, _02039CC4 ; =FUN_02039CC8
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	ldr r0, [sp, #0x0]
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_02039CC4: .word FUN_02039CC8 

	thumb_func_start FUN_02039CC8
FUN_02039CC8: ; 0x02039CC8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x5
	bl FUN_02039438
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02039CDE
	mov r0, #0x1
	pop {r3, pc}
_02039CDE:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_21
ScrCmd_unk_21: ; 0x02039CE4
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x5
	bl FUN_02039438
	mov r1, #0x0
	strb r1, [r0, #0x0]
	add r0, r1, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_goto
ScrCmd_goto: ; 0x02039CF8
	; relative jump
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadWord
	add r2, r0, #0x0
	ldr r1, [r4, #0x8]
	add r0, r4, #0x0
	add r1, r1, r2
	bl ScriptJump
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_23
ScrCmd_unk_23: ; 0x02039D10
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadWord
	add r7, r0, #0x0
	ldr r0, [r6, #0x0]
	bl FUN_02058448
	cmp r4, r0
	bne _02039D44
	ldr r1, [r5, #0x8]
	add r0, r5, #0x0
	add r1, r1, r7
	bl ScriptJump
_02039D44:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_unk_24
ScrCmd_unk_24: ; 0x02039D48
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x74]
	bl FUN_02046534
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r4, [r1, #0x0]
	add r0, r5, #0x0
	bl ScriptReadWord
	add r2, r0, #0x0
	cmp r6, r4
	bne _02039D72
	ldr r1, [r5, #0x8]
	add r0, r5, #0x0
	add r1, r1, r2
	bl ScriptJump
_02039D72:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_25
ScrCmd_unk_25: ; 0x02039D78
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x9
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r4, [r1, #0x0]
	add r0, r5, #0x0
	bl ScriptReadWord
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	cmp r0, r4
	bne _02039DA8
	ldr r1, [r5, #0x8]
	add r0, r5, #0x0
	add r1, r1, r2
	bl ScriptJump
_02039DA8:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_call
ScrCmd_call: ; 0x02039DAC
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadWord
	add r2, r0, #0x0
	ldr r1, [r4, #0x8]
	add r0, r4, #0x0
	add r1, r1, r2
	bl ScriptCall
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_return
ScrCmd_return: ; 0x02039DC4
	push {r3, lr}
	bl ScriptReturn
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_goto_if
ScrCmd_goto_if: ; 0x02039DD0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadWord
	add r1, r0, #0x0
	lsl r0, r4, #0x1
	add r3, r4, r0
	ldr r0, _02039E00 ; =sScriptConditionTable
	ldrb r2, [r5, #0x2]
	add r0, r0, r3
	ldrb r0, [r2, r0]
	cmp r0, #0x1
	bne _02039DFC
	ldr r2, [r5, #0x8]
	add r0, r5, #0x0
	add r1, r2, r1
	bl ScriptJump
_02039DFC:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_02039E00: .word sScriptConditionTable

	thumb_func_start ScrCmd_call_if
ScrCmd_call_if: ; 0x02039E04
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadWord
	add r1, r0, #0x0
	lsl r0, r4, #0x1
	add r3, r4, r0
	ldr r0, _02039E34 ; =sScriptConditionTable
	ldrb r2, [r5, #0x2]
	add r0, r0, r3
	ldrb r0, [r2, r0]
	cmp r0, #0x1
	bne _02039E30
	ldr r2, [r5, #0x8]
	add r0, r5, #0x0
	add r1, r2, r1
	bl ScriptCall
_02039E30:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_02039E34: .word sScriptConditionTable

	thumb_func_start ScrCmd_setflag
ScrCmd_setflag: ; 0x02039E38
	push {r4, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FlagSet
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_clearflag
ScrCmd_clearflag: ; 0x02039E50
	push {r4, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FlagClear
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_checkflag
ScrCmd_checkflag: ; 0x02039E68
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FlagCheck
	strb r0, [r4, #0x2]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_33
ScrCmd_unk_33: ; 0x02039E84
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	ldrh r1, [r6, #0x0]
	add r0, r5, #0x0
	bl FlagCheck
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_34
ScrCmd_unk_34: ; 0x02039EC0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r1, r0, #0x0
	ldrh r1, [r1, #0x0]
	add r0, r4, #0x0
	bl FlagSet
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_settrainerflag
ScrCmd_settrainerflag: ; 0x02039EE8
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl TrainerFlagSet
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_cleartrainerflag
ScrCmd_cleartrainerflag: ; 0x02039F0C
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl TrainerFlagClear
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_checktrainerflag
ScrCmd_checktrainerflag: ; 0x02039F30
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl TrainerFlagCheck
	strb r0, [r5, #0x2]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_addvar
ScrCmd_addvar: ; 0x02039F58
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	ldrh r1, [r4, #0x0]
	add r0, r1, r0
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_subvar
ScrCmd_subvar: ; 0x02039F88
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	ldrh r1, [r4, #0x0]
	sub r0, r1, r0
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_setvar
ScrCmd_setvar: ; 0x02039FB8
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_copyvar
ScrCmd_copyvar: ; 0x02039FDC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	ldrh r0, [r0, #0x0]
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_setorcopyvar
ScrCmd_setorcopyvar: ; 0x0203A00C
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_message
ScrCmd_message: ; 0x0203A038
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r2, [r2, #0x0]
	ldr r1, [r0, #0x78]
	bl MOD05_ShowMessageInField
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_message_from
ScrCmd_message_from: ; 0x0203A04C
	; message_from bank, id
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	add r2, r5, #0x0
	mov r3, #0x20
	bl NewMsgDataFromNarc
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl MOD05_ShowMessageInField
	add r0, r5, #0x0
	bl DestroyMsgData
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_507
ScrCmd_unk_507: ; 0x0203A098
	push {r3-r6, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	add r2, r5, #0x0
	mov r3, #0x20
	bl NewMsgDataFromNarc
	add r5, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	mov r3, #0x1
	bl MOD05_021E2BD0
	add r0, r5, #0x0
	bl DestroyMsgData
	ldr r1, _0203A0F8 ; =FUN_0203A2F0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r6, pc}
	nop
_0203A0F8: .word FUN_0203A2F0 

	thumb_func_start ScrCmd_unk_508
ScrCmd_unk_508: ; 0x0203A0FC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl MOD05_021E2C58
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_509
ScrCmd_unk_509: ; 0x0203A13C
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl MOD05_021E2C58
	ldr r1, _0203A184 ; =FUN_0203A2F0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203A184: .word FUN_0203A2F0 

	thumb_func_start ScrCmd_unk_510
ScrCmd_unk_510: ; 0x0203A188
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldrb r3, [r2, #0x0]
	add r1, #0xa8
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	bne _0203A1AA
	add sp, #0x8
	mov r0, #0x0
	pop {r4-r6, pc}
_0203A1AA:
	lsl r1, r3, #0x4
	add r1, r3, r1
	add r2, #0x90
	lsl r1, r1, #0x4
	add r4, r2, r1
	ldrh r1, [r2, r1]
	ldr r2, _0203A204 ; =0x0000FFFF
	cmp r1, r2
	bne _0203A1E2
	ldr r2, _0203A208 ; =0x0000022B
	mov r0, #0x1
	mov r1, #0x1a
	mov r3, #0x20
	bl NewMsgDataFromNarc
	add r6, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldrh r2, [r4, #0x2]
	add r0, r5, #0x0
	add r1, r6, #0x0
	mov r3, #0x1
	bl MOD05_021E2BD0
	add r0, r6, #0x0
	bl DestroyMsgData
	b _0203A1F4
_0203A1E2:
	mov r2, #0x6
	ldrsh r2, [r4, r2]
	str r2, [sp, #0x0]
	mov r2, #0x1
	str r2, [sp, #0x4]
	ldrh r2, [r4, #0x2]
	ldrh r3, [r4, #0x4]
	bl MOD05_021E2C58
_0203A1F4:
	ldr r1, _0203A20C ; =FUN_0203A2F0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_0203A204: .word 0x0000FFFF
_0203A208: .word 0x0000022B
_0203A20C: .word FUN_0203A2F0 

	thumb_func_start ScrCmd_unk_511
ScrCmd_unk_511: ; 0x0203A210
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r2, [r5, #0x8]
	ldr r6, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	ldr r1, [r5, #0x8]
	add r2, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r3, [r1, #0x0]
	mov r1, #0x0
	add r0, sp, #0x4
	strb r1, [r0, #0x0]
	add r0, sp, #0x4
	str r0, [sp, #0x0]
	ldr r0, [r6, #0xc]
	add r1, r7, #0x0
	bl MOD06_02244210
	add r6, r0, #0x0
	add r2, sp, #0x4
	ldrb r2, [r2, #0x0]
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, r2
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	mov r3, #0x1
	bl MOD05_021E2CBC
	add r0, r6, #0x0
	bl ScrStrBufs_delete
	ldr r1, _0203A284 ; =FUN_0203A2F0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203A284: .word FUN_0203A2F0 

	thumb_func_start ScrCmd_unk_621
ScrCmd_unk_621: ; 0x0203A288
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, sp, #0x4
	add r1, r5, #0x0
	bl MOD05_021E2BB8
	mov r1, #0x3
	add r0, sp, #0x4
	strb r1, [r0, #0x2]
	add r0, sp, #0x4
	str r0, [sp, #0x0]
	ldr r1, [r5, #0x78]
	add r0, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x0
	bl MOD05_021E2BD0
	ldr r1, _0203A2C0 ; =FUN_0203A2F0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_0203A2C0: .word FUN_0203A2F0 

	thumb_func_start ScrCmd_unk_44
ScrCmd_unk_44: ; 0x0203A2C4
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	ldr r2, [r4, #0x8]
	mov r3, #0x1
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldrb r2, [r2, #0x0]
	ldr r1, [r4, #0x78]
	bl MOD05_021E2BD0
	ldr r1, _0203A2EC ; =FUN_0203A2F0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0203A2EC: .word FUN_0203A2F0 

	thumb_func_start FUN_0203A2F0
FUN_0203A2F0: ; 0x0203A2F0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x3
	bl FUN_02039438
	ldrb r0, [r0, #0x0]
	bl FUN_020546C8
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_45
ScrCmd_unk_45: ; 0x0203A304
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	lsl r2, r2, #0x18
	ldr r1, [r4, #0x78]
	add r0, r4, #0x0
	lsr r2, r2, #0x18
	mov r3, #0x1
	bl MOD05_021E2BD0
	ldr r1, _0203A33C ; =FUN_0203A2F0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0203A33C: .word FUN_0203A2F0 

	thumb_func_start ScrCmd_unk_704
ScrCmd_unk_704: ; 0x0203A340
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, sp, #0x4
	add r1, r5, #0x0
	bl MOD05_021E2BB8
	lsl r2, r4, #0x18
	mov r3, #0x1
	add r0, sp, #0x4
	strb r3, [r0, #0x1]
	add r0, sp, #0x4
	str r0, [sp, #0x0]
	ldr r1, [r5, #0x78]
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl MOD05_021E2BD0
	ldr r1, _0203A384 ; =FUN_0203A2F0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_0203A384: .word FUN_0203A2F0 

	thumb_func_start ScrCmd_unk_46
ScrCmd_unk_46: ; 0x0203A388
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r2, r0, #0x0
	mov r3, #0x0
	str r3, [sp, #0x0]
	lsl r2, r2, #0x18
	ldr r1, [r4, #0x78]
	add r0, r4, #0x0
	lsr r2, r2, #0x18
	bl MOD05_021E2BD0
	ldr r1, _0203A3C0 ; =FUN_0203A2F0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	nop
_0203A3C0: .word FUN_0203A2F0 

	thumb_func_start ScrCmd_unk_524
ScrCmd_unk_524: ; 0x0203A3C4
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_02058488
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, [r4, #0x78]
	add r0, r4, #0x0
	mov r3, #0x1
	bl MOD05_021E2BD0
	ldr r1, _0203A3FC ; =FUN_0203A2F0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	nop
_0203A3FC: .word FUN_0203A2F0 

	thumb_func_start ScrCmd_unk_47
ScrCmd_unk_47: ; 0x0203A400
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r1, [r5, #0x8]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r4, [r1, #0x0]
	bl FUN_02030F40
	cmp r0, #0x0
	bne _0203A428
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, [r5, #0x78]
	add r0, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x1
	bl MOD05_021E2BD0
	b _0203A448
_0203A428:
	add r0, sp, #0x4
	add r1, r5, #0x0
	bl MOD05_021E2BB8
	mov r1, #0x1
	add r0, sp, #0x4
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	add r0, sp, #0x4
	str r0, [sp, #0x0]
	ldr r1, [r5, #0x78]
	add r0, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x0
	bl MOD05_021E2BD0
_0203A448:
	ldr r1, _0203A458 ; =FUN_0203A2F0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r5, pc}
	nop
_0203A458: .word FUN_0203A2F0 

	thumb_func_start ScrCmd_unk_48
ScrCmd_unk_48: ; 0x0203A45C
	push {r3, lr}
	ldr r1, _0203A468 ; =FUN_0203A46C
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0203A468: .word FUN_0203A46C 

	thumb_func_start FUN_0203A46C
FUN_0203A46C: ; 0x0203A46C
	ldr r0, _0203A480 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _0203A47A
	mov r0, #0x1
	bx lr
_0203A47A:
	mov r0, #0x0
	bx lr
	nop
_0203A480: .word gMain

	thumb_func_start ScrCmd_unk_400
ScrCmd_unk_400: ; 0x0203A484
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [r4, #0x64]
	ldr r1, _0203A4A8 ; =FUN_0203A4AC
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203A4A8: .word FUN_0203A4AC 

	thumb_func_start FUN_0203A4AC
FUN_0203A4AC: ; 0x0203A4AC
	ldr r1, _0203A4CC ; =gMain
	ldr r2, [r1, #0x48]
	mov r1, #0x3
	tst r1, r2
	beq _0203A4BA
	mov r0, #0x1
	bx lr
_0203A4BA:
	ldr r1, [r0, #0x64]
	sub r1, r1, #0x1
	str r1, [r0, #0x64]
	bne _0203A4C6
	mov r0, #0x1
	bx lr
_0203A4C6:
	mov r0, #0x0
	bx lr
	nop
_0203A4CC: .word gMain

	thumb_func_start ScrCmd_unk_49
ScrCmd_unk_49: ; 0x0203A4D0
	push {r3, lr}
	ldr r1, _0203A4DC ; =FUN_0203A4E0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0203A4DC: .word FUN_0203A4E0 

	thumb_func_start FUN_0203A4E0
FUN_0203A4E0: ; 0x0203A4E0
	push {r4, lr}
	ldr r1, _0203A55C ; =gMain
	ldr r2, [r1, #0x48]
	mov r1, #0x3
	add r3, r2, #0x0
	tst r3, r1
	beq _0203A4F2
	mov r0, #0x1
	pop {r4, pc}
_0203A4F2:
	mov r3, #0x40
	tst r3, r2
	beq _0203A506
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	b _0203A556
_0203A506:
	mov r3, #0x80
	tst r3, r2
	beq _0203A51A
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	b _0203A556
_0203A51A:
	mov r3, #0x20
	tst r3, r2
	beq _0203A52E
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x2
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	b _0203A556
_0203A52E:
	mov r3, #0x10
	add r4, r2, #0x0
	tst r4, r3
	beq _0203A542
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	b _0203A556
_0203A542:
	lsl r1, r3, #0x6
	tst r1, r2
	beq _0203A552
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02039460
	b _0203A556
_0203A552:
	mov r0, #0x0
	pop {r4, pc}
_0203A556:
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203A55C: .word gMain

	thumb_func_start ScrCmd_unk_50
ScrCmd_unk_50: ; 0x0203A560
	push {r3, lr}
	ldr r1, _0203A56C ; =FUN_0203A570
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0203A56C: .word FUN_0203A570 

	thumb_func_start FUN_0203A570
FUN_0203A570: ; 0x0203A570
	ldr r0, _0203A58C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _0203A57E
	mov r0, #0x1
	bx lr
_0203A57E:
	mov r0, #0xf0
	tst r0, r1
	beq _0203A588
	mov r0, #0x1
	bx lr
_0203A588:
	mov r0, #0x0
	bx lr
	.balign 4
_0203A58C: .word gMain

	thumb_func_start ScrCmd_unk_51
ScrCmd_unk_51: ; 0x0203A590
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x6
	add r0, r4, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02039438
	add r1, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r2, #0x3
	bl FUN_020545B8
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02039438
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02054608
	mov r0, #0x1
	strb r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_52
ScrCmd_unk_52: ; 0x0203A5D8
	push {r3-r5, lr}
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x1
	add r0, r4, #0x0
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x6
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0200D0E0
	add r0, r5, #0x0
	bl FUN_02019178
	mov r0, #0x0
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_53
ScrCmd_unk_53: ; 0x0203A608
	push {r3-r5, lr}
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x1
	add r0, r4, #0x0
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x6
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02019178
	mov r0, #0x0
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_61
ScrCmd_unk_61: ; 0x0203A630
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x31
	add r0, r4, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x2d
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x32
	bl FUN_02039438
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x33
	bl FUN_02039438
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0x2e
	bl FUN_02039438
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	mov r1, #0x34
	bl FUN_02039438
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	strh r1, [r6, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	strh r1, [r7, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r2, [r2, #0x0]
	ldr r1, [sp, #0x0]
	strh r2, [r1, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r2, [r2, #0x0]
	ldr r1, [sp, #0x4]
	strh r2, [r1, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r2, [r2, #0x0]
	ldr r1, [sp, #0x8]
	strh r2, [r1, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	strh r1, [r0, #0x0]
	ldr r1, _0203A6C4 ; =FUN_0203A6C8
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_0203A6C4: .word FUN_0203A6C8 

	thumb_func_start FUN_0203A6C8
FUN_0203A6C8: ; 0x0203A6C8
	push {r4-r7, lr}
	sub sp, #0xc
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x31
	add r0, r4, #0x0
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x32
	bl FUN_02039438
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	mov r1, #0x33
	bl FUN_02039438
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0x34
	bl FUN_02039438
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x2d
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x2e
	bl FUN_02039438
	add r5, r0, #0x0
	ldrh r0, [r6, #0x0]
	cmp r0, #0x0
	bne _0203A71E
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	bne _0203A71E
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0203A71E:
	ldrh r3, [r7, #0x0]
	cmp r3, #0x0
	beq _0203A740
	ldr r0, [sp, #0x8]
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	ldr r0, [r4, #0x8]
	bne _0203A738
	mov r1, #0x3
	mov r2, #0x1
	bl FUN_020179E0
	b _0203A740
_0203A738:
	mov r1, #0x3
	mov r2, #0x2
	bl FUN_020179E0
_0203A740:
	ldr r0, [sp, #0x4]
	ldrh r3, [r0, #0x0]
	cmp r3, #0x0
	beq _0203A764
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	ldr r0, [r4, #0x8]
	bne _0203A75C
	mov r1, #0x3
	mov r2, #0x4
	bl FUN_020179E0
	b _0203A764
_0203A75C:
	mov r1, #0x3
	mov r2, #0x5
	bl FUN_020179E0
_0203A764:
	ldrh r0, [r6, #0x0]
	cmp r0, #0x0
	beq _0203A76E
	sub r0, r0, #0x1
	strh r0, [r6, #0x0]
_0203A76E:
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0203A778
	sub r0, r0, #0x1
	strh r0, [r5, #0x0]
_0203A778:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_54
ScrCmd_unk_54: ; 0x0203A780
	push {r4-r7, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x11
	add r0, r4, #0x0
	bl FUN_02039438
	str r0, [sp, #0x18]
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0xf
	bl FUN_02039438
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r0, [r0, #0x0]
	str r0, [sp, #0xc]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	str r0, [sp, #0x10]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	cmp r6, #0x0
	bne _0203A7E0
	add r0, r4, #0x0
	mov r1, #0xa
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02058510
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
_0203A7E0:
	ldr r0, [r4, #0x60]
	ldr r1, [sp, #0x10]
	add r2, r6, #0x0
	bl MOD05_021E8128
	ldr r0, [r4, #0x60]
	mov r1, #0x1
	bl MOD05_021E8130
	add r0, r4, #0x0
	bl MOD05_021E8158
	ldr r2, [sp, #0x18]
	ldr r0, [r5, #0x78]
	ldr r1, [sp, #0xc]
	ldr r2, [r2, #0x0]
	bl ReadMsgDataIntoString
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x18]
	ldr r0, [r0, #0x0]
	ldr r1, [r7, #0x0]
	ldr r2, [r2, #0x0]
	bl StringExpandPlaceholders
	ldr r0, [r4, #0x60]
	bl MOD05_021E8140
	mov r3, #0x0
	str r3, [sp, #0x0]
	str r3, [sp, #0x4]
	str r3, [sp, #0x8]
	ldr r2, [r7, #0x0]
	mov r1, #0x1
	bl AddTextPrinterParameterized
	mov r0, #0x1
	add sp, #0x1c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_55
ScrCmd_unk_55: ; 0x0203A830
	push {r3-r5, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r4, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r5, [r2, #0x0]
	bl ScriptReadHalfword
	add r2, r0, #0x0
	ldr r0, [r4, #0x60]
	add r1, r5, #0x0
	bl MOD05_021E8128
	ldr r0, [r4, #0x60]
	mov r1, #0x1
	bl MOD05_021E8130
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_56
ScrCmd_unk_56: ; 0x0203A85C
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	ldr r0, [r3, #0x60]
	bl MOD05_021E8130
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_57
ScrCmd_unk_57: ; 0x0203A878
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x60]
	bl MOD05_021E8148
	cmp r0, #0x1
	bne _0203A88E
	mov r0, #0x0
	pop {r4, pc}
_0203A88E:
	ldr r1, _0203A89C ; =FUN_0203A8A0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203A89C: .word FUN_0203A8A0 

	thumb_func_start FUN_0203A8A0
FUN_0203A8A0: ; 0x0203A8A0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x60]
	bl MOD05_021E8148
	cmp r0, #0x1
	bne _0203A8B4
	mov r0, #0x1
	pop {r3, pc}
_0203A8B4:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_58
ScrCmd_unk_58: ; 0x0203A8B8
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x3
	add r0, r4, #0x0
	bl FUN_02039438
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0x11
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	str r0, [sp, #0x8]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x78]
	ldr r1, [sp, #0x0]
	ldr r2, [r6, #0x0]
	bl ReadMsgDataIntoString
	ldr r0, [sp, #0x8]
	ldr r1, [r7, #0x0]
	ldr r0, [r0, #0x0]
	ldr r2, [r6, #0x0]
	bl StringExpandPlaceholders
	ldr r0, [r4, #0x60]
	bl MOD05_021E8140
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r2, r0, #0x0
	ldr r1, [r7, #0x0]
	add r0, r4, #0x0
	mov r3, #0x1
	bl FUN_02054658
	ldr r1, [sp, #0x4]
	strb r0, [r1, #0x0]
	ldr r0, [sp, #0xc]
	ldr r1, _0203A948 ; =FUN_0203A94C
	str r0, [r5, #0x64]
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_0203A948: .word FUN_0203A94C 

	thumb_func_start FUN_0203A94C
FUN_0203A94C: ; 0x0203A94C
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x3
	add r0, r5, #0x0
	bl FUN_02039438
	ldr r1, [r7, #0x64]
	add r6, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl GetVarPointer
	add r4, r0, #0x0
	ldr r0, [r5, #0x60]
	bl MOD05_021E8144
	ldrb r0, [r6, #0x0]
	ldr r5, _0203A9E8 ; =0x0000FFFF
	bl FUN_020546C8
	cmp r0, #0x1
	bne _0203A986
	mov r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
_0203A986:
	ldr r0, _0203A9EC ; =gMain
	mov r1, #0x40
	ldr r0, [r0, #0x48]
	tst r1, r0
	beq _0203A994
	mov r5, #0x0
	b _0203A9B0
_0203A994:
	mov r1, #0x80
	tst r1, r0
	beq _0203A99E
	mov r5, #0x1
	b _0203A9B0
_0203A99E:
	mov r1, #0x20
	tst r1, r0
	beq _0203A9A8
	mov r5, #0x2
	b _0203A9B0
_0203A9A8:
	mov r1, #0x10
	tst r1, r0
	beq _0203A9B0
	mov r5, #0x3
_0203A9B0:
	ldr r1, _0203A9E8 ; =0x0000FFFF
	cmp r5, r1
	beq _0203A9D0
	ldrb r0, [r6, #0x0]
	bl FUN_0201BD7C
	add r7, #0x80
	ldr r0, [r7, #0x0]
	add r1, r5, #0x0
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	mov r0, #0x0
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
_0203A9D0:
	mov r1, #0x1
	lsl r1, r1, #0xa
	tst r0, r1
	beq _0203A9E4
	ldrb r0, [r6, #0x0]
	bl FUN_0201BD7C
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r3-r7, pc}
_0203A9E4:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0203A9E8: .word 0x0000FFFF
_0203A9EC: .word gMain

	thumb_func_start ScrCmd_unk_59
ScrCmd_unk_59: ; 0x0203A9F0
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	str r0, [r4, #0x64]
	ldr r1, _0203AA08 ; =FUN_0203AA0C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203AA08: .word FUN_0203AA0C 

	thumb_func_start FUN_0203AA0C
FUN_0203AA0C: ; 0x0203AA0C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl GetVarPointer
	add r4, r0, #0x0
	ldr r0, _0203AA88 ; =gMain
	ldr r1, _0203AA8C ; =0x0000FFFF
	ldr r2, [r0, #0x48]
	mov r0, #0x3
	add r3, r2, #0x0
	tst r3, r0
	beq _0203AA36
	mov r0, #0x0
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
_0203AA36:
	mov r3, #0x40
	tst r3, r2
	beq _0203AA40
	mov r1, #0x0
	b _0203AA5C
_0203AA40:
	mov r3, #0x80
	tst r3, r2
	beq _0203AA4A
	mov r1, #0x1
	b _0203AA5C
_0203AA4A:
	mov r3, #0x20
	tst r3, r2
	beq _0203AA54
	mov r1, #0x2
	b _0203AA5C
_0203AA54:
	mov r3, #0x10
	tst r3, r2
	beq _0203AA5C
	add r1, r0, #0x0
_0203AA5C:
	ldr r0, _0203AA8C ; =0x0000FFFF
	cmp r1, r0
	beq _0203AA74
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	mov r0, #0x0
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
_0203AA74:
	mov r0, #0x1
	lsl r0, r0, #0xa
	tst r0, r2
	beq _0203AA82
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r3-r5, pc}
_0203AA82:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203AA88: .word gMain
_0203AA8C: .word 0x0000FFFF

	thumb_func_start ScrCmd_unk_60
ScrCmd_unk_60: ; 0x0203AA90
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02039460
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_62
ScrCmd_unk_62: ; 0x0203AAA0
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x2
	add r0, r4, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x4
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x8]
	ldr r2, _0203AAF4 ; =0x000003D9
	mov r1, #0x3
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x8]
	ldr r1, _0203AAF8 ; =UNK_020F34E0
	ldr r2, _0203AAF4 ; =0x000003D9
	mov r3, #0xb
	bl FUN_02002198
	str r0, [r6, #0x0]
	ldr r1, _0203AAFC ; =FUN_0203AB00
	add r0, r5, #0x0
	str r7, [r5, #0x64]
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203AAF4: .word 0x000003D9
_0203AAF8: .word UNK_020F34E0
_0203AAFC: .word FUN_0203AB00 

	thumb_func_start FUN_0203AB00
FUN_0203AB00: ; 0x0203AB00
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0x2
	add r0, r6, #0x0
	bl FUN_02039438
	ldr r1, [r5, #0x64]
	add r4, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x4
	bl FUN_020021AC
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	bne _0203AB34
	mov r0, #0x0
	pop {r4-r6, pc}
_0203AB34:
	cmp r0, #0x0
	bne _0203AB3C
	mov r0, #0x0
	b _0203AB3E
_0203AB3C:
	mov r0, #0x1
_0203AB3E:
	strh r0, [r5, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_397
ScrCmd_unk_397: ; 0x0203AB44
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02039438
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x12
	bl FUN_02039438
	add r5, r0, #0x0
	ldr r1, _0203AB70 ; =0x000003E2
	add r0, r4, #0x0
	bl FUN_0200D858
	str r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203AB70: .word 0x000003E2

	thumb_func_start ScrCmd_unk_398
ScrCmd_unk_398: ; 0x0203AB74
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x12
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_0200DBFC
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_64
ScrCmd_unk_64: ; 0x0203AB8C
	push {r4-r7, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0x0
	add r0, r6, #0x0
	bl FUN_02039438
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	mov r1, #0xf
	bl FUN_02039438
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	str r0, [sp, #0x18]
	str r2, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	add r1, r2, #0x1
	str r0, [sp, #0x14]
	str r1, [r5, #0x8]
	ldrb r7, [r2, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x24]
	add r0, r6, #0x0
	bl GetVarPointer
	str r0, [sp, #0x28]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02039438
	ldr r1, [sp, #0x28]
	str r4, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x20]
	add r3, r7, #0x0
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r6, #0x0
	bl MOD05_021E1BF8
	ldr r1, [sp, #0x1c]
	str r0, [r1, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [r5, #0x64]
	mov r0, #0x1
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_65
ScrCmd_unk_65: ; 0x0203AC14
	push {r4-r7, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0x0
	add r0, r6, #0x0
	bl FUN_02039438
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	mov r1, #0xf
	bl FUN_02039438
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	str r0, [sp, #0x18]
	str r2, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	add r1, r2, #0x1
	str r0, [sp, #0x14]
	str r1, [r5, #0x8]
	ldrb r7, [r2, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x24]
	add r0, r6, #0x0
	bl GetVarPointer
	str r0, [sp, #0x28]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02039438
	ldr r1, [sp, #0x28]
	str r4, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x20]
	add r3, r7, #0x0
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x78]
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r6, #0x0
	bl MOD05_021E1BF8
	ldr r1, [sp, #0x1c]
	str r0, [r1, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [r5, #0x64]
	mov r0, #0x1
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_66
ScrCmd_unk_66: ; 0x0203AC9C
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r1, [r4, #0x8]
	add r3, r1, #0x1
	str r3, [r4, #0x8]
	ldrb r1, [r1, #0x0]
	add r2, r3, #0x1
	str r2, [r4, #0x8]
	ldrb r2, [r3, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021E1C4C
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_669
ScrCmd_unk_669: ; 0x0203ACC4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	add r1, r6, #0x0
	bl MOD05_021E1C4C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_67
ScrCmd_unk_67: ; 0x0203AD08
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl MOD05_021E1C54
	ldr r1, _0203AD28 ; =FUN_0203AD2C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203AD28: .word FUN_0203AD2C 

	thumb_func_start FUN_0203AD2C
FUN_0203AD2C: ; 0x0203AD2C
	push {r3, lr}
	add r1, r0, #0x0
	ldr r1, [r1, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl GetVarPointer
	ldrh r1, [r0, #0x0]
	ldr r0, _0203AD50 ; =0x0000EEEE
	cmp r1, r0
	beq _0203AD4A
	mov r0, #0x1
	pop {r3, pc}
_0203AD4A:
	mov r0, #0x0
	pop {r3, pc}
	nop
_0203AD50: .word 0x0000EEEE

	thumb_func_start ScrCmd_unk_697
ScrCmd_unk_697: ; 0x0203AD54
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl MOD05_021E1C54
	ldr r1, _0203AD74 ; =FUN_0203AD78
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203AD74: .word FUN_0203AD78 

	thumb_func_start FUN_0203AD78
FUN_0203AD78: ; 0x0203AD78
	push {r4-r6, lr}
	add r1, r0, #0x0
	add r0, #0x80
	ldr r1, [r1, #0x64]
	ldr r5, [r0, #0x0]
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	ldrh r1, [r4, #0x0]
	ldr r0, _0203ADC0 ; =0x0000EEEE
	cmp r1, r0
	bne _0203ADBC
	ldr r0, [r5, #0x78]
	bl FUN_02052714
	cmp r0, #0x0
	beq _0203ADB8
	mov r0, #0x8
	strh r0, [r4, #0x0]
	ldr r0, [r6, #0x0]
	bl MOD05_021E1ECC
	mov r0, #0x1
	pop {r4-r6, pc}
_0203ADB8:
	mov r0, #0x0
	pop {r4-r6, pc}
_0203ADBC:
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203ADC0: .word 0x0000EEEE

	thumb_func_start ScrCmd_unk_68
ScrCmd_unk_68: ; 0x0203ADC4
	push {r4-r7, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0x0
	add r0, r6, #0x0
	bl FUN_02039438
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	mov r1, #0xf
	bl FUN_02039438
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	str r0, [sp, #0x18]
	str r2, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	add r1, r2, #0x1
	str r0, [sp, #0x14]
	str r1, [r5, #0x8]
	ldrb r7, [r2, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x24]
	add r0, r6, #0x0
	bl GetVarPointer
	str r0, [sp, #0x28]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02039438
	ldr r1, [sp, #0x28]
	str r4, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x20]
	add r3, r7, #0x0
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r6, #0x0
	bl MOD05_021E1F34
	ldr r1, [sp, #0x1c]
	str r0, [r1, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [r5, #0x64]
	mov r0, #0x1
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_69
ScrCmd_unk_69: ; 0x0203AE4C
	push {r4-r7, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0x0
	add r0, r6, #0x0
	bl FUN_02039438
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	mov r1, #0xf
	bl FUN_02039438
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	str r0, [sp, #0x18]
	str r2, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	add r1, r2, #0x1
	str r0, [sp, #0x14]
	str r1, [r5, #0x8]
	ldrb r7, [r2, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x24]
	add r0, r6, #0x0
	bl GetVarPointer
	str r0, [sp, #0x28]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02039438
	ldr r1, [sp, #0x28]
	str r4, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x20]
	add r3, r7, #0x0
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x78]
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r6, #0x0
	bl MOD05_021E1F34
	ldr r1, [sp, #0x1c]
	str r0, [r1, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [r5, #0x64]
	mov r0, #0x1
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_70
ScrCmd_unk_70: ; 0x0203AED4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r3, r0, #0x0
	lsl r1, r6, #0x18
	lsl r2, r7, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl MOD05_021E1F58
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_unk_71
ScrCmd_unk_71: ; 0x0203AF34
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl MOD05_021E1F60
	ldr r1, _0203AF54 ; =FUN_0203AD2C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203AF54: .word FUN_0203AD2C 

	thumb_func_start ScrCmd_unk_72
ScrCmd_unk_72: ; 0x0203AF58
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021E26CC
	ldr r1, _0203AF80 ; =FUN_0203AD2C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203AF80: .word FUN_0203AD2C 

	thumb_func_start ScrCmd_unk_719
ScrCmd_unk_719: ; 0x0203AF84
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021E2B80
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_720
ScrCmd_unk_720: ; 0x0203AFA4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021E2B9C
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_94
ScrCmd_unk_94: ; 0x0203AFC4
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadWord
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r6, #0x0
	bl FUN_0203B120
	add r6, r0, #0x0
	bne _0203AFF6
	bl ErrorHandling
_0203AFF6:
	ldr r1, [r5, #0x8]
	add r0, r6, #0x0
	add r1, r1, r4
	bl FUN_0205AEA4
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x4
	bl FUN_02039438
	ldrb r1, [r0, #0x0]
	add r5, #0x80
	mov r2, #0x0
	add r1, r1, #0x1
	strb r1, [r0, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_0203B174
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_673
ScrCmd_unk_673: ; 0x0203B024
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	bl FUN_0203B120
	str r0, [sp, #0x4]
	cmp r0, #0x0
	bne _0203B07A
	bl ErrorHandling
_0203B07A:
	mov r0, #0x4
	add r1, r0, #0x0
	add r1, #0xfc
	bl AllocFromHeap
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	bl FUN_02058B2C
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r0, [sp, #0x4]
	bl FUN_02058B4C
	lsl r0, r0, #0x10
	ldr r2, [sp, #0x0]
	lsr r0, r0, #0x10
	mov r1, #0x0
	cmp r6, r2
	bhs _0203B0B0
	mov r2, #0xf
	strh r2, [r4, #0x0]
	ldr r2, [sp, #0x0]
	add r1, r1, #0x1
	sub r2, r2, r6
	strh r2, [r4, #0x2]
	b _0203B0C0
_0203B0B0:
	cmp r6, r2
	bls _0203B0C0
	mov r2, #0xe
	strh r2, [r4, #0x0]
	ldr r2, [sp, #0x0]
	add r1, r1, #0x1
	sub r2, r6, r2
	strh r2, [r4, #0x2]
_0203B0C0:
	cmp r0, r7
	bhs _0203B0D4
	lsl r2, r1, #0x2
	mov r3, #0xc
	strh r3, [r4, r2]
	sub r3, r7, r0
	add r0, r4, r2
	strh r3, [r0, #0x2]
	add r1, r1, #0x1
	b _0203B0E6
_0203B0D4:
	cmp r0, r7
	bls _0203B0E6
	lsl r2, r1, #0x2
	mov r3, #0xd
	strh r3, [r4, r2]
	sub r3, r0, r7
	add r0, r4, r2
	strh r3, [r0, #0x2]
	add r1, r1, #0x1
_0203B0E6:
	lsl r2, r1, #0x2
	mov r0, #0xfe
	strh r0, [r4, r2]
	mov r1, #0x0
	add r0, r4, r2
	strh r1, [r0, #0x2]
	ldr r0, [sp, #0x4]
	add r1, r4, #0x0
	bl FUN_0205AEA4
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x4
	bl FUN_02039438
	ldrb r1, [r0, #0x0]
	add r5, #0x80
	add r2, r4, #0x0
	add r1, r1, #0x1
	strb r1, [r0, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	bl FUN_0203B174
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0203B120
FUN_0203B120: ; 0x0203B120
	push {r3, lr}
	cmp r1, #0xf2
	bne _0203B130
	ldr r0, [r0, #0x34]
	mov r1, #0x30
	bl FUN_020580B4
	pop {r3, pc}
_0203B130:
	cmp r1, #0xf1
	bne _0203B13E
	mov r1, #0xb
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	pop {r3, pc}
_0203B13E:
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_95
ScrCmd_unk_95: ; 0x0203B148
	push {r3, lr}
	ldr r1, _0203B154 ; =FUN_0203B158
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0203B154: .word FUN_0203B158 

	thumb_func_start FUN_0203B158
FUN_0203B158: ; 0x0203B158
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x4
	bl FUN_02039438
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203B16E
	mov r0, #0x1
	pop {r3, pc}
_0203B16E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203B174
FUN_0203B174: ; 0x0203B174
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0x4
	mov r1, #0x10
	add r7, r2, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	bne _0203B18E
	bl ErrorHandling
	pop {r3-r7, pc}
_0203B18E:
	str r5, [r4, #0xc]
	str r6, [r4, #0x4]
	ldr r0, _0203B1A4 ; =FUN_0203B1A8
	add r1, r4, #0x0
	mov r2, #0x0
	str r7, [r4, #0x8]
	bl FUN_0200CA44
	str r0, [r4, #0x0]
	pop {r3-r7, pc}
	nop
_0203B1A4: .word FUN_0203B1A8 

	thumb_func_start FUN_0203B1A8
FUN_0203B1A8: ; 0x0203B1A8
	push {r3-r5, lr}
	add r5, r1, #0x0
	ldr r0, [r5, #0xc]
	mov r1, #0x4
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r5, #0x4]
	bl FUN_0205AEF0
	cmp r0, #0x1
	bne _0203B1EC
	ldr r0, [r5, #0x4]
	bl FUN_0205AEFC
	ldr r0, [r5, #0x0]
	bl FUN_0200CAB4
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	beq _0203B1D6
	bl FreeToHeap
_0203B1D6:
	add r0, r5, #0x0
	bl FreeToHeap
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203B1E8
	bl ErrorHandling
	pop {r3-r5, pc}
_0203B1E8:
	sub r0, r0, #0x1
	strb r0, [r4, #0x0]
_0203B1EC:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_96
ScrCmd_unk_96: ; 0x0203B1F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0xa
	add r0, r4, #0x0
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203B20E
	ldr r0, [r4, #0x34]
	bl FUN_02058780
	b _0203B214
_0203B20E:
	add r0, r5, #0x0
	bl ScrCmd_unk_692
_0203B214:
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0203B218
FUN_0203B218: ; 0x0203B218
	push {r4-r6, lr}
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0xa
	add r0, r4, #0x0
	bl FUN_02039438
	add r5, r0, #0x0
	ldr r0, [r4, #0x38]
	bl FUN_020553A0
	ldr r1, _0203B2DC ; =UNK_021C5A0C
	add r6, r0, #0x0
	ldrb r2, [r1, #0x0]
	mov r1, #0x1
	tst r1, r2
	beq _0203B252
	bl FUN_0205AE28
	cmp r0, #0x1
	bne _0203B252
	add r0, r6, #0x0
	bl FUN_02058908
	ldr r1, _0203B2DC ; =UNK_021C5A0C
	mov r0, #0xfe
	ldrb r2, [r1, #0x0]
	and r0, r2
	strb r0, [r1, #0x0]
_0203B252:
	ldr r0, _0203B2DC ; =UNK_021C5A0C
	ldrb r1, [r0, #0x0]
	mov r0, #0x4
	tst r0, r1
	beq _0203B276
	ldr r0, [r5, #0x0]
	bl FUN_02058854
	cmp r0, #0x0
	bne _0203B276
	ldr r0, [r5, #0x0]
	bl FUN_02058908
	ldr r1, _0203B2DC ; =UNK_021C5A0C
	mov r0, #0xfb
	ldrb r2, [r1, #0x0]
	and r0, r2
	strb r0, [r1, #0x0]
_0203B276:
	ldr r0, _0203B2DC ; =UNK_021C5A0C
	ldrb r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0203B2A2
	ldr r0, [r4, #0x34]
	mov r1, #0x30
	bl FUN_020580B4
	add r4, r0, #0x0
	bl FUN_02058854
	cmp r0, #0x0
	bne _0203B2A2
	add r0, r4, #0x0
	bl FUN_02058908
	ldr r1, _0203B2DC ; =UNK_021C5A0C
	mov r0, #0xfd
	ldrb r2, [r1, #0x0]
	and r0, r2
	strb r0, [r1, #0x0]
_0203B2A2:
	ldr r0, _0203B2DC ; =UNK_021C5A0C
	ldrb r1, [r0, #0x0]
	mov r0, #0x8
	tst r0, r1
	beq _0203B2CC
	ldr r0, [r5, #0x0]
	bl FUN_0205E7C4
	add r4, r0, #0x0
	bl FUN_02058854
	cmp r0, #0x0
	bne _0203B2CC
	add r0, r4, #0x0
	bl FUN_02058908
	ldr r1, _0203B2DC ; =UNK_021C5A0C
	mov r0, #0xf7
	ldrb r2, [r1, #0x0]
	and r0, r2
	strb r0, [r1, #0x0]
_0203B2CC:
	ldr r0, _0203B2DC ; =UNK_021C5A0C
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203B2D8
	mov r0, #0x1
	pop {r4-r6, pc}
_0203B2D8:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_0203B2DC: .word UNK_021C5A0C

	thumb_func_start ScrCmd_unk_692
ScrCmd_unk_692: ; 0x0203B2E0
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0xa
	add r0, r4, #0x0
	bl FUN_02039438
	add r5, r0, #0x0
	ldr r0, [r4, #0x38]
	bl FUN_020553A0
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x34]
	mov r1, #0x30
	bl FUN_020580B4
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_0205E7C4
	add r6, r0, #0x0
	ldr r0, [r4, #0x34]
	ldr r1, _0203B3A8 ; =UNK_021C5A0C
	mov r2, #0x0
	strb r2, [r1, #0x0]
	bl FUN_02058780
	ldr r0, [sp, #0x4]
	bl FUN_0205AE28
	cmp r0, #0x0
	bne _0203B334
	ldr r1, _0203B3A8 ; =UNK_021C5A0C
	mov r0, #0x1
	ldrb r2, [r1, #0x0]
	orr r0, r2
	strb r0, [r1, #0x0]
	ldr r0, [sp, #0x4]
	bl FUN_02058914
_0203B334:
	ldr r0, [r5, #0x0]
	bl FUN_02058854
	cmp r0, #0x0
	beq _0203B34E
	ldr r1, _0203B3A8 ; =UNK_021C5A0C
	mov r0, #0x4
	ldrb r2, [r1, #0x0]
	orr r0, r2
	strb r0, [r1, #0x0]
	ldr r0, [r5, #0x0]
	bl FUN_02058914
_0203B34E:
	cmp r7, #0x0
	beq _0203B37A
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205ED3C
	cmp r0, #0x1
	bne _0203B37A
	add r0, r7, #0x0
	bl FUN_02058854
	cmp r0, #0x0
	beq _0203B37A
	ldr r1, _0203B3A8 ; =UNK_021C5A0C
	mov r0, #0x2
	ldrb r2, [r1, #0x0]
	orr r0, r2
	strb r0, [r1, #0x0]
	add r0, r7, #0x0
	bl FUN_02058914
_0203B37A:
	cmp r6, #0x0
	beq _0203B398
	add r0, r6, #0x0
	bl FUN_02058854
	cmp r0, #0x0
	beq _0203B398
	ldr r1, _0203B3A8 ; =UNK_021C5A0C
	mov r0, #0x8
	ldrb r2, [r1, #0x0]
	orr r0, r2
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	bl FUN_02058914
_0203B398:
	ldr r0, [sp, #0x0]
	ldr r1, _0203B3AC ; =FUN_0203B218
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203B3A8: .word UNK_021C5A0C
_0203B3AC: .word FUN_0203B218 

	thumb_func_start ScrCmd_unk_97
ScrCmd_unk_97: ; 0x0203B3B0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_020587B0
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_98
ScrCmd_unk_98: ; 0x0203B3C0
	push {r4, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	ldr r0, [r4, #0x34]
	bl FUN_02058060
	bl FUN_02058908
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_99
ScrCmd_unk_99: ; 0x0203B3DC
	push {r4, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	ldr r0, [r4, #0x34]
	bl FUN_02058060
	bl FUN_02058914
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_100
ScrCmd_unk_100: ; 0x0203B3F8
	push {r3-r6, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02034B64
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02034B6C
	str r0, [sp, #0x0]
	ldr r3, [r5, #0x1c]
	ldr r0, [r5, #0x34]
	ldr r3, [r3, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020575D4
	cmp r0, #0x0
	bne _0203B43A
	bl ErrorHandling
_0203B43A:
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}

	thumb_func_start ScrCmd_unk_101
ScrCmd_unk_101: ; 0x0203B440
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r1, r0, #0x0
	ldr r0, [r5, #0x34]
	bl FUN_02058060
	bl FUN_02057688
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_102
ScrCmd_unk_102: ; 0x0203B468
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xb
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0xc
	str r1, [sp, #0x0]
	mov r3, #0x0
	str r3, [sp, #0x4]
	ldr r1, [r0, #0x1c]
	add r2, r7, #0x0
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x8]
	ldr r0, [r0, #0x34]
	add r1, r6, #0x0
	bl FUN_0205753C
	str r0, [r4, #0x0]
	bl FUN_02059D1C
	ldr r0, [r4, #0x0]
	mov r1, #0x1
	bl FUN_0205889C
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl FUN_020588B8
	ldr r0, [r4, #0x0]
	bl FUN_02058B7C
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	add r4, r0, #0x0
	ldr r1, [r1, #0x24]
	bl MOD05_021EF5E0
	add r5, #0x80
	ldr r1, [r5, #0x0]
	add r0, r4, #0x0
	ldr r1, [r1, #0x20]
	bl FUN_0201EC68
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_103
ScrCmd_unk_103: ; 0x0203B500
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xb
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_02057654
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xff
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	bl FUN_02058B7C
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	add r4, r0, #0x0
	ldr r1, [r1, #0x24]
	bl MOD05_021EF5E0
	add r5, #0x80
	ldr r1, [r5, #0x0]
	add r0, r4, #0x0
	ldr r1, [r1, #0x20]
	bl FUN_0201EC68
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_104
ScrCmd_unk_104: ; 0x0203B544
	push {r3-r5, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	ldr r0, [r5, #0x38]
	bl FUN_020552F8
	bl FUN_02059E74
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xa
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203B568
	mov r0, #0x0
	pop {r3-r5, pc}
_0203B568:
	add r1, r4, #0x0
	bl MOD05_021F1EC0
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_105
ScrCmd_unk_105: ; 0x0203B574
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	ldr r0, [r5, #0x38]
	bl FUN_02055320
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x38]
	bl FUN_0205532C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_106
ScrCmd_unk_106: ; 0x0203B5B8
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r1, r0, #0x0
	ldr r0, [r5, #0x34]
	bl FUN_02058060
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B2C
	strh r0, [r6, #0x0]
	add r0, r5, #0x0
	bl FUN_02058B4C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_445
ScrCmd_unk_445: ; 0x0203B618
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_107
ScrCmd_unk_107: ; 0x0203B640
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	cmp r7, #0x0
	beq _0203B696
	lsl r0, r7, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0203B6A4
_0203B696:
	lsl r0, r7, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0203B6A4:
	bl _ffix
	str r0, [sp, #0x0]
	cmp r6, #0x0
	beq _0203B6C0
	lsl r0, r6, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0203B6CE
_0203B6C0:
	lsl r0, r6, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0203B6CE:
	bl _ffix
	str r0, [sp, #0x4]
	cmp r4, #0x0
	beq _0203B6EA
	lsl r0, r4, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0203B6F8
_0203B6EA:
	lsl r0, r4, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0203B6F8:
	bl _ffix
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553A0
	add r1, sp, #0x0
	bl FUN_02058BB4
	add r5, #0x80
	ldr r1, [r5, #0x0]
	add r0, sp, #0x0
	ldr r1, [r1, #0x20]
	bl FUN_0201EF70
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_108
ScrCmd_unk_108: ; 0x0203B724
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	bl FUN_02058994
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_109
ScrCmd_unk_109: ; 0x0203B758
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058E90
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_685
ScrCmd_unk_685: ; 0x0203B790
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	mov r0, #0x0
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	cmp r0, #0x0
	beq _0203B7D2
	bl FUN_02058480
	strh r0, [r4, #0x0]
_0203B7D2:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_110
ScrCmd_unk_110: ; 0x0203B7D8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x30
	ldr r0, [r0, #0x34]
	bl FUN_020580B4
	mov r1, #0xfe
	bl FUN_02058EB0
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_683
ScrCmd_unk_683: ; 0x0203B7F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_SealCase_get
	bl FUN_02029E0C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_147
ScrCmd_unk_147: ; 0x0203B81C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_SealCase_get
	add r1, r6, #0x0
	bl FUN_02029E2C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_148
ScrCmd_unk_148: ; 0x0203B85C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_SealCase_get
	lsl r2, r4, #0x10
	add r1, r6, #0x0
	asr r2, r2, #0x10
	bl FUN_02029D44
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_149
ScrCmd_unk_149: ; 0x0203B8A0
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r6, #0x0
	bl GetPartyMonByIndex
	bl GetMonUnownLetter
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_401
ScrCmd_unk_401: ; 0x0203B8E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r1, r5, #0x0
	add r1, #0x80
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0x20
	bl FUN_020379F8
	str r0, [r4, #0x0]
	ldr r1, _0203B910 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203B910: .word FUN_0203BC04 

	thumb_func_start ScrCmd_unk_677
ScrCmd_unk_677: ; 0x0203B914
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r1, r5, #0x0
	add r1, #0x80
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0x20
	bl FUN_02037A1C
	str r0, [r4, #0x0]
	ldr r1, _0203B940 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203B940: .word FUN_0203BC04 

	thumb_func_start ScrCmd_unk_402
ScrCmd_unk_402: ; 0x0203B944
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x20
	ldr r0, [r0, #0x10]
	bl FUN_02037B44
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_403
ScrCmd_unk_403: ; 0x0203B968
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203B994
	bl ErrorHandling
_0203B994:
	ldr r0, [r4, #0x0]
	bl FUN_02037A40
	strh r0, [r5, #0x0]
	ldrh r0, [r5, #0x0]
	cmp r0, #0x7
	bne _0203B9A6
	mov r0, #0xff
	strh r0, [r5, #0x0]
_0203B9A6:
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_404
ScrCmd_unk_404: ; 0x0203B9B4
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
	add r1, r5, #0x0
	str r6, [sp, #0x4]
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r2, [sp, #0x8]
	mov r0, #0x20
	add r3, r7, #0x0
	bl FUN_02037BB0
	str r0, [r4, #0x0]
	ldr r1, _0203BA38 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_0203BA38: .word FUN_0203BC04 

	thumb_func_start ScrCmd_unk_405
ScrCmd_unk_405: ; 0x0203BA3C
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203BA7C
	bl ErrorHandling
_0203BA7C:
	ldr r0, [r4, #0x0]
	bl FUN_02037A40
	strh r0, [r6, #0x0]
	ldrh r0, [r6, #0x0]
	cmp r0, #0x7
	bne _0203BA8E
	mov r0, #0xff
	strh r0, [r6, #0x0]
_0203BA8E:
	ldr r0, [r4, #0x0]
	bl FUN_02037A70
	strh r0, [r5, #0x0]
	ldrh r0, [r5, #0x0]
	cmp r0, #0x1
	bne _0203BAA0
	mov r0, #0x1
	b _0203BAA2
_0203BAA0:
	mov r0, #0x0
_0203BAA2:
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_406
ScrCmd_unk_406: ; 0x0203BAB0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r1, r5, #0x0
	add r1, #0x80
	add r2, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0x20
	bl FUN_02037C00
	str r0, [r4, #0x0]
	ldr r1, _0203BAF0 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203BAF0: .word FUN_0203BC04 

	thumb_func_start ScrCmd_unk_407
ScrCmd_unk_407: ; 0x0203BAF4
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203BB20
	bl ErrorHandling
_0203BB20:
	ldr r0, [r4, #0x0]
	bl FUN_02037A78
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_155
ScrCmd_unk_155: ; 0x0203BB34
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	add r2, r7, #0x0
	bl MOD05_021E1858
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_156
ScrCmd_unk_156: ; 0x0203BB80
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_unk_157
ScrCmd_unk_157: ; 0x0203BB84
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_unk_158
ScrCmd_unk_158: ; 0x0203BB88
	mov r0, #0x1
	bx lr

	thumb_func_start ScrCmd_unk_159
ScrCmd_unk_159: ; 0x0203BB8C
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0203BB90
FUN_0203BB90: ; 0x0203BB90
	push {r3-r5, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x13
	add r0, r5, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	beq _0203BBAE
	mov r0, #0x0
	pop {r3-r5, pc}
_0203BBAE:
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0203BBBC
FUN_0203BBBC: ; 0x0203BBBC
	push {r4-r6, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x13
	add r0, r5, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	ldr r6, [r4, #0x0]
	bl FUN_0204647C
	cmp r0, #0x0
	beq _0203BBDC
	mov r0, #0x0
	pop {r4-r6, pc}
_0203BBDC:
	ldr r0, [r6, #0x8]
	cmp r0, #0x1
	bne _0203BBF4
	mov r0, #0xb
	bl FUN_02029048
	add r5, #0x98
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r2, #0x1
	bl FUN_02028AD4
_0203BBF4:
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203BC04
FUN_0203BC04: ; 0x0203BC04
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0204647C
	cmp r0, #0x0
	bne _0203BC16
	mov r0, #0x1
	pop {r3, pc}
_0203BC16:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_161
ScrCmd_unk_161: ; 0x0203BC1C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_0204AF84
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_504
ScrCmd_unk_504: ; 0x0203BC2C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_0204AF3C
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203BC3C
FUN_0203BC3C: ; 0x0203BC3C
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02027E24
	cmp r5, #0x0
	bne _0203BC5A
	add r1, r4, #0x0
	bl FUN_02027098
	cmp r0, #0x0
	bne _0203BC68
	mov r0, #0x0
	pop {r3-r5, pc}
_0203BC5A:
	add r1, r4, #0x0
	bl FUN_020270B4
	cmp r0, #0x0
	bne _0203BC68
	mov r0, #0x0
	pop {r3-r5, pc}
_0203BC68:
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0203BC6C
FUN_0203BC6C: ; 0x0203BC6C
	push {r3-r7, lr}
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0xc]
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02027E24
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0203BC3C
	cmp r0, #0x0
	bne _0203BC90
	mov r0, #0x0
	pop {r3-r7, pc}
_0203BC90:
	ldr r0, [sp, #0x0]
	mov r1, #0xc
	bl AllocFromHeap
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	strb r1, [r0, #0x4]
	strb r1, [r0, #0x5]
	strb r1, [r0, #0x6]
	strb r1, [r0, #0x7]
	strb r1, [r0, #0x8]
	strb r1, [r0, #0x9]
	strb r1, [r0, #0xa]
	strb r1, [r0, #0xb]
	str r7, [r0, #0x0]
	str r4, [r0, #0x8]
	str r6, [r0, #0x4]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_162
ScrCmd_unk_162: ; 0x0203BCBC
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl MOD05_021F02C4
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_163
ScrCmd_unk_163: ; 0x0203BCCC
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_0206F3B8
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_164
ScrCmd_unk_164: ; 0x0203BCD8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	ldr r1, [r4, #0x0]
	ldr r1, [r1, #0x4]
	strh r1, [r0, #0x0]
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_519
ScrCmd_unk_519: ; 0x0203BD08
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	bl FUN_02031190
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_520
ScrCmd_unk_520: ; 0x0203BD28
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x4
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r2, _0203BDB4 ; =0x000003D9
	ldr r0, [r0, #0x8]
	mov r1, #0x3
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0xb
	str r0, [sp, #0x0]
	ldr r0, _0203BDB4 ; =0x000003D9
	mov r1, #0x3
	str r0, [sp, #0x4]
	lsl r0, r7, #0x18
	str r4, [sp, #0x8]
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	mov r0, #0x4
	str r0, [sp, #0x10]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r2, #0xa
	ldr r0, [r0, #0x8]
	mov r3, #0x5
	bl FUN_0200DC4C
	add r5, #0x80
	str r0, [r6, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_0203ED2C
	mov r0, #0x0
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_0203BDB4: .word 0x000003D9

	thumb_func_start ScrCmd_unk_652
ScrCmd_unk_652: ; 0x0203BDB8
	push {r4-r6, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r4, #0x0
	bl GetPartyMonByIndex
	add r4, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x4
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r2, _0203BE4C ; =0x000003D9
	ldr r0, [r0, #0x8]
	mov r1, #0x3
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0xb
	str r0, [sp, #0x0]
	ldr r0, _0203BE4C ; =0x000003D9
	mov r1, #0x3
	str r0, [sp, #0x4]
	str r4, [sp, #0x8]
	mov r0, #0x4
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r2, #0xa
	ldr r0, [r0, #0x8]
	mov r3, #0x5
	bl FUN_0200DCA4
	str r0, [r6, #0x0]
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	add r1, r0, #0x0
	add r5, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r5, #0x0]
	lsr r1, r1, #0x10
	bl FUN_0203ED2C
	mov r0, #0x0
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_0203BE4C: .word 0x000003D9

	thumb_func_start ScrCmd_unk_521
ScrCmd_unk_521: ; 0x0203BE50
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	strb r1, [r0, #0x0]
	add r0, r1, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_653
ScrCmd_unk_653: ; 0x0203BE68
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	mov r1, #0x2
	strb r1, [r0, #0x0]
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_654
ScrCmd_unk_654: ; 0x0203BE80
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	str r0, [r4, #0x64]
	ldr r1, _0203BE98 ; =FUN_0203BE9C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203BE98: .word FUN_0203BE9C 

	thumb_func_start FUN_0203BE9C
FUN_0203BE9C: ; 0x0203BE9C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	ldr r1, [r5, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl GetVarPointer
	ldr r0, [r4, #0x0]
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	beq _0203BEC8
	mov r0, #0x1
	pop {r3-r5, pc}
_0203BEC8:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_522
ScrCmd_unk_522: ; 0x0203BECC
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r6, #0x0
	bl GetVarPointer
	add r2, r0, #0x0
	ldr r0, [r5, #0x74]
	ldr r1, [r4, #0x0]
	bl MOD05_021E1374
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_523
ScrCmd_unk_523: ; 0x0203BF00
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0203BF1C
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl MOD05_021E1994
_0203BF1C:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_165
ScrCmd_unk_165: ; 0x0203BF20
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_0208A338
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_166
ScrCmd_unk_166: ; 0x0203BF2C
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	ldr r2, [r5, #0x0]
	add r1, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r2, #0x10]
	ldr r2, [r2, #0xc]
	add r3, r4, #0x0
	bl FUN_020380CC
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_167
ScrCmd_unk_167: ; 0x0203BF84
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r1, r5, #0x0
	add r1, #0x80
	add r6, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0xb
	mov r2, #0x0
	add r3, r7, #0x0
	bl FUN_0203BC6C
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203BFCC
	mov r0, #0x1
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_0203BFCC:
	mov r0, #0x0
	strh r0, [r6, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_02038130
	ldr r1, _0203BFE8 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0203BFE8: .word FUN_0203BB90 

	thumb_func_start ScrCmd_unk_168
ScrCmd_unk_168: ; 0x0203BFEC
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r1, r5, #0x0
	add r1, #0x80
	add r6, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0xb
	mov r2, #0x1
	add r3, r7, #0x0
	bl FUN_0203BC6C
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203C034
	mov r0, #0x1
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_0203C034:
	mov r0, #0x0
	strh r0, [r6, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_02038130
	ldr r1, _0203C050 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0203C050: .word FUN_0203BB90 

	thumb_func_start ScrCmd_unk_302
ScrCmd_unk_302: ; 0x0203C054
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_0203BC3C
	cmp r0, #0x1
	bne _0203C088
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
_0203C088:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_303
ScrCmd_unk_303: ; 0x0203C090
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_0203BC3C
	cmp r0, #0x1
	bne _0203C0C4
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
_0203C0C4:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_304
ScrCmd_unk_304: ; 0x0203C0CC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	mov r1, #0x0
	bl FUN_02027008
	add r1, r4, #0x0
	bl FUN_02027478
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_517
ScrCmd_unk_517: ; 0x0203C0FC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02038804
	ldr r1, _0203C114 ; =FUN_0203BC04
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203C114: .word FUN_0203BC04 

	thumb_func_start ScrCmd_unk_169
ScrCmd_unk_169: ; 0x0203C118
	push {r3, lr}
	add r1, r0, #0x0
	ldr r0, [r1, #0x74]
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0xc]
	bl FUN_02085F48
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_170
ScrCmd_unk_170: ; 0x0203C12C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	mov r1, #0x5
	add r4, r0, #0x0
	mov r0, #0xb
	lsl r1, r1, #0x6
	bl AllocFromHeap
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	mov r2, #0x2
	bl FUN_0205F7A0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_02037E90
	ldr r1, _0203C170 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203C170: .word FUN_0203BB90 

	thumb_func_start ScrCmd_unk_471
ScrCmd_unk_471: ; 0x0203C174
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r2, #0xb
	bl FUN_02088960
	str r0, [r4, #0x0]
	ldr r1, _0203C1A8 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203C1A8: .word FUN_0203BB90 

	thumb_func_start ScrCmd_unk_472
ScrCmd_unk_472: ; 0x0203C1AC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Bag_get
	mov r1, #0x4
	bl Bag_PocketNotEmpty
	cmp r0, #0x0
	bne _0203C1E0
	mov r0, #0x1
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
_0203C1E0:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02028048
	bl FUN_020281B8
	cmp r0, #0x64
	blo _0203C1FA
	mov r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
_0203C1FA:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_473
ScrCmd_unk_473: ; 0x0203C200
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r6, r0, #0x0
	mov r0, #0xb
	mov r1, #0x8
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x8
	str r0, [r6, #0x0]
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, [sp, #0x0]
	strh r7, [r4, #0x4]
	strh r0, [r4, #0x6]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r6, #0x0]
	bl FUN_02037FE4
	ldr r1, _0203C274 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0203C274: .word FUN_0203BB90 

	thumb_func_start ScrCmd_monstoragepc
ScrCmd_monstoragepc: ; 0x0203C278
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0xc
	bl AllocFromHeap
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0xc]
	str r1, [r0, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	str r1, [r0, #0x4]
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl LaunchStoragePCInterface
	ldr r1, _0203C2C0 ; =FUN_0203BBBC
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203C2C0: .word FUN_0203BBBC 

	thumb_func_start ScrCmd_unk_172
ScrCmd_unk_172: ; 0x0203C2C4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020383F8
	ldr r1, _0203C2DC ; =FUN_0203BC04
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203C2DC: .word FUN_0203BC04 

	thumb_func_start ScrCmd_unk_173
ScrCmd_unk_173: ; 0x0203C2E0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02065344
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_174
ScrCmd_unk_174: ; 0x0203C2F0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_020383D8
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_175
ScrCmd_unk_175: ; 0x0203C300
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0203842C
	str r0, [r4, #0x0]
	ldr r1, _0203C328 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203C328: .word FUN_0203BB90 

	thumb_func_start ScrCmd_halloffame
ScrCmd_halloffame: ; 0x0203C32C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl Special_EnterHallOfFame
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_177
ScrCmd_unk_177: ; 0x0203C33C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02038824
	str r0, [r4, #0x0]
	ldr r1, _0203C364 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203C364: .word FUN_0203BB90 

	thumb_func_start ScrCmd_unk_178
ScrCmd_unk_178: ; 0x0203C368
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0203384C
	cmp r0, #0x0
	beq _0203C3BC
	mov r0, #0x1
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r6, #0x0
	bl FUN_020386E0
	ldr r1, _0203C3C4 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	b _0203C3C0
_0203C3BC:
	mov r0, #0x0
	strh r0, [r4, #0x0]
_0203C3C0:
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203C3C4: .word FUN_0203BC04 

	thumb_func_start ScrCmd_unk_179
ScrCmd_unk_179: ; 0x0203C3C8
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r1, r0, #0x0
	ldr r0, [r4, #0x74]
	bl FUN_0206F3D8
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_180
ScrCmd_unk_180: ; 0x0203C3E8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0x8
	bl AllocFromHeap
	str r0, [r4, #0x0]
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r6, #0x4]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_020386A4
	ldr r1, _0203C42C ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4-r6, pc}
	nop
_0203C42C: .word FUN_0203BC04 

	thumb_func_start ScrCmd_unk_181
ScrCmd_unk_181: ; 0x0203C430
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	ldr r1, [r4, #0x0]
	ldr r1, [r1, #0x0]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_0205F378
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_376
ScrCmd_unk_376: ; 0x0203C460
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0x8]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	cmp r0, #0x0
	beq _0203C474
	mov r0, #0x1
	b _0203C476
_0203C474:
	mov r0, #0x0
_0203C476:
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r6, r0, #0x0
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	beq _0203C492
	bl ErrorHandling
_0203C492:
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	bl FUN_0203789C
	str r0, [r6, #0x0]
	ldr r1, _0203C4AC ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203C4AC: .word FUN_0203BC04 

	thumb_func_start ScrCmd_unk_377
ScrCmd_unk_377: ; 0x0203C4B0
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203C4DC
	bl ErrorHandling
_0203C4DC:
	ldr r0, [r4, #0x0]
	bl FUN_020378FC
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_186
ScrCmd_unk_186: ; 0x0203C4F0
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x74]
	add r2, r1, #0x0
	mov r3, #0x7
	bl FUN_020385CC
	mov r0, #0x1
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_187
ScrCmd_unk_187: ; 0x0203C520
	push {r4-r7, lr}
	sub sp, #0x34
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	ldr r0, [r4, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r6, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x74
	add r2, sp, #0xc
	add r7, r0, #0x0
	bl GetMonData
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r7, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	str r6, [sp, #0x0]
	add r0, sp, #0xc
	str r0, [sp, #0x4]
	str r4, [sp, #0x8]
	ldr r0, [r5, #0x74]
	mov r1, #0x1
	mov r3, #0xa
	bl FUN_020385CC
	mov r0, #0x1
	add sp, #0x34
	pop {r4-r7, pc}

	thumb_func_start ScrCmd_unk_625
ScrCmd_unk_625: ; 0x0203C58C
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	mov r2, #0x0
	str r2, [sp, #0x0]
	str r2, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x74]
	mov r1, #0x6
	mov r3, #0xa
	bl FUN_020385CC
	mov r0, #0x1
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_579
ScrCmd_unk_579: ; 0x0203C5BC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r2, r0, #0x0
	ldr r0, _0203C610 ; =0x0000FFFF
	add r5, #0x80
	strh r0, [r2, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x10]
	mov r3, #0x0
	bl FUN_02037E18
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203C610: .word 0x0000FFFF

	thumb_func_start ScrCmd_unk_580
ScrCmd_unk_580: ; 0x0203C614
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r3, r0, #0x0
	ldr r0, _0203C67C ; =0x0000FFFF
	add r5, #0x80
	strh r0, [r4, #0x0]
	strh r0, [r3, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	ldr r0, [r0, #0x10]
	add r2, r4, #0x0
	bl FUN_02037E18
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203C67C: .word 0x0000FFFF

	thumb_func_start ScrCmd_unk_581
ScrCmd_unk_581: ; 0x0203C680
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	add r1, r6, #0x0
	bl FUN_0200B518
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_188
ScrCmd_unk_188: ; 0x0203C6C4
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r4, [sp, #0x0]
	add r3, r0, #0x0
	str r6, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0x0
	add r1, r7, #0x0
	add r2, r7, #0x0
	bl FUN_0200E1D0
	mov r0, #0x0
	bl FUN_0200E388
	mov r0, #0x1
	bl FUN_0200E388
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start ScrCmd_unk_189
ScrCmd_unk_189: ; 0x0203C70C
	push {r3, lr}
	ldr r1, _0203C718 ; =FUN_0203C71C
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0203C718: .word FUN_0203C71C 

	thumb_func_start FUN_0203C71C
FUN_0203C71C: ; 0x0203C71C
	push {r3, lr}
	bl FUN_0200E308
	cmp r0, #0x1
	bne _0203C72A
	mov r0, #0x1
	pop {r3, pc}
_0203C72A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_190
ScrCmd_unk_190: ; 0x0203C730
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r2, #0x0
	ldr r0, [r5, #0x74]
	add r1, r6, #0x0
	mvn r2, r2
	add r3, r7, #0x0
	bl FUN_02049240
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_unk_515
ScrCmd_unk_515: ; 0x0203C788
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r4, [sp, #0x0]
	mov r2, #0x0
	add r5, #0x80
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	ldr r0, [r0, #0x10]
	mvn r2, r2
	add r3, r7, #0x0
	bl FUN_02049F98
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_unk_516
ScrCmd_unk_516: ; 0x0203C7E4
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02049FFC
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_512
ScrCmd_unk_512: ; 0x0203C7F4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034DC8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	ldr r1, [r5, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_513
ScrCmd_unk_513: ; 0x0203C820
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	ldr r1, [r4, #0x0]
	ldr r1, [r1, #0x1c]
	ldr r1, [r1, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_191
ScrCmd_unk_191: ; 0x0203C844
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	add r1, r0, #0x0
	ldr r0, [r5, #0x74]
	add r2, r4, #0x0
	bl MOD05_021E6990
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_192
ScrCmd_unk_192: ; 0x0203C874
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl FUN_0205DD40
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	add r1, r0, #0x0
	ldr r0, [r5, #0x74]
	add r2, r4, #0x0
	bl MOD05_021E6410
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_193
ScrCmd_unk_193: ; 0x0203C8B4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	add r1, r0, #0x0
	ldr r0, [r5, #0x74]
	add r2, r4, #0x0
	bl MOD05_021E6BF4
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_194
ScrCmd_unk_194: ; 0x0203C8E4
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
	mov r2, #0x1
	str r2, [sp, #0x4]
	add r5, #0x80
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	sub r2, r2, #0x2
	add r3, r6, #0x0
	bl FUN_02049274
	mov r0, #0x1
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_195
ScrCmd_unk_195: ; 0x0203C930
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	add r5, r0, #0x0
	mov r1, #0x0
	bl FUN_02034DF4
	add r0, r5, #0x0
	bl FUN_02034DEC
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xc]
	bl MOD05_021DC174
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_196
ScrCmd_unk_196: ; 0x0203C960
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	add r5, r0, #0x0
	mov r1, #0x0
	bl FUN_02034DF4
	add r0, r5, #0x0
	bl FUN_02034DEC
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xc]
	bl MOD05_021DC174
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_197
ScrCmd_unk_197: ; 0x0203C990
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r6, #0x0
	bl GetPartyMonByIndex
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553E8
	add r3, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	add r2, r6, #0x0
	bl MOD06_0224666C
	str r0, [r4, #0x0]
	ldr r1, _0203C9F4 ; =FUN_0203C9F8
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4-r6, pc}
	nop
_0203C9F4: .word FUN_0203C9F8 

	thumb_func_start FUN_0203C9F8
FUN_0203C9F8: ; 0x0203C9F8
	push {r4, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl MOD06_022466A0
	cmp r0, #0x1
	bne _0203CA1A
	ldr r0, [r4, #0x0]
	bl MOD06_022466AC
	mov r0, #0x1
	pop {r4, pc}
_0203CA1A:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_198
ScrCmd_unk_198: ; 0x0203CA20
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl MOD05_021E7030
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_199
ScrCmd_unk_199: ; 0x0203CA2C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553C4
	cmp r0, #0x1
	bne _0203CA54
	mov r0, #0x1
	b _0203CA56
_0203CA54:
	mov r0, #0x0
_0203CA56:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_200
ScrCmd_unk_200: ; 0x0203CA5C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x8]
	add r0, r1, #0x1
	str r0, [r4, #0x8]
	ldrb r0, [r1, #0x0]
	cmp r0, #0x1
	bne _0203CAA4
	add r0, r4, #0x0
	add r0, #0x80
	mov r1, #0x12
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x6
	bl FUN_0204AB20
	add r0, r4, #0x0
	add r0, #0x80
	mov r1, #0x12
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x6
	mov r2, #0x1
	bl FUN_0204ABDC
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x2
	ldr r0, [r0, #0x38]
	bl MOD05_021E5FD8
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x38]
	bl MOD05_021E5FE0
	b _0203CAE4
_0203CAA4:
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	ldr r0, [r0, #0x38]
	bl MOD05_021E5FD8
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl MOD05_021E5FE0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_0204AB20
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x1c]
	ldr r1, [r1, #0x0]
	bl FUN_0204AB58
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r2, #0x1
	bl FUN_0204ABDC
_0203CAE4:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_703
ScrCmd_unk_703: ; 0x0203CAE8
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x2
	ldr r0, [r0, #0x38]
	bl MOD05_021E5FD8
	add r4, #0x80
	mov r1, #0x12
	ldr r0, [r4, #0x0]
	lsl r1, r1, #0x6
	bl FUN_0204AB20
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_201
ScrCmd_unk_201: ; 0x0203CB08
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_02055720
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_202
ScrCmd_unk_202: ; 0x0203CB20
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553C4
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_203
ScrCmd_unk_203: ; 0x0203CB48
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553D4
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_204
ScrCmd_unk_204: ; 0x0203CB60
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl MOD05_021E5FE0
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_227
ScrCmd_unk_227: ; 0x0203CB70
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202A9B0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0202A990
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl MOD06_02245910
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_222
ScrCmd_unk_222: ; 0x0203CBBC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F388
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_230
ScrCmd_unk_230: ; 0x0203CBE8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x8
	add r0, r4, #0x0
	bl FUN_02039438
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x6
	bl FUN_02039438
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r1, r0, #0x0
	ldr r0, [sp, #0x0]
	ldr r2, [r6, #0x0]
	mov r3, #0xb
	bl GetTrainerMessageByIdPair
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02039438
	mov r1, #0xf
	bl FUN_02019620
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r2, r0, #0x0
	ldr r1, [r6, #0x0]
	add r0, r4, #0x0
	mov r3, #0x1
	bl FUN_02054658
	strb r0, [r7, #0x0]
	ldr r1, _0203CC84 ; =FUN_0203A2F0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0203CC84: .word FUN_0203A2F0 

	thumb_func_start ScrCmd_unk_242
ScrCmd_unk_242: ; 0x0203CC88
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	ldr r2, [sp, #0x0]
	ldr r3, [sp, #0x4]
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl MOD06_02240790
	ldr r1, _0203CCF4 ; =FUN_0203CCF8
	add r0, r5, #0x0
	str r6, [r5, #0x64]
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203CCF4: .word FUN_0203CCF8 

	thumb_func_start FUN_0203CCF8
FUN_0203CCF8: ; 0x0203CCF8
	push {r4, lr}
	add r1, r0, #0x0
	ldr r1, [r1, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl GetVarPointer
	add r4, r0, #0x0
	bl MOD06_022407DC
	cmp r0, #0x0
	bne _0203CD18
	mov r0, #0x0
	pop {r4, pc}
_0203CD18:
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_243
ScrCmd_unk_243: ; 0x0203CD20
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	ldr r2, [sp, #0x0]
	ldr r3, [sp, #0x4]
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl MOD06_022407F8
	ldr r1, _0203CD8C ; =FUN_0203CD90
	add r0, r5, #0x0
	str r6, [r5, #0x64]
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203CD8C: .word FUN_0203CD90 

	thumb_func_start FUN_0203CD90
FUN_0203CD90: ; 0x0203CD90
	push {r4, lr}
	add r1, r0, #0x0
	ldr r1, [r1, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl GetVarPointer
	add r4, r0, #0x0
	bl MOD06_02240844
	cmp r0, #0x0
	bne _0203CDB0
	mov r0, #0x0
	pop {r4, pc}
_0203CDB0:
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_244
ScrCmd_unk_244: ; 0x0203CDB8
	push {r3, lr}
	bl ScriptReadHalfword
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_245
ScrCmd_unk_245: ; 0x0203CDC4
	push {r3, lr}
	bl ScriptReadHalfword
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_246
ScrCmd_unk_246: ; 0x0203CDD0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r6, r0, #0x0
	add r5, #0x80
	ldr r4, [r6, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x10]
	add r1, #0x2c
	mov r2, #0x5
	bl FUN_02047174
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r6, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_247
ScrCmd_unk_247: ; 0x0203CE00
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_02080C38
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_283
ScrCmd_unk_283: ; 0x0203CE0C
	push {r3-r4, lr}
	sub sp, #0x14
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, #0x80
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	add r1, sp, #0x0
	bl FUN_02034DD4
	mov r0, #0x0
	add sp, #0x14
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_284
ScrCmd_unk_284: ; 0x0203CE8C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034DD0
	ldr r0, [r0, #0x0]
	bl MOD05_021E2608
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_285
ScrCmd_unk_285: ; 0x0203CEBC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	str r0, [sp, #0x4]
	bl FUN_02039438
	add r7, r0, #0x0
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r6, [r0, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r3, r0, #0x0
	ldr r0, [r7, #0x0]
	add r1, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	add r2, r4, #0x0
	bl MOD05_021E2464
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_unk_286
ScrCmd_unk_286: ; 0x0203CF04
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl Pokedex_CountSinnohDexSeenMons
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_287
ScrCmd_unk_287: ; 0x0203CF34
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl Pokedex_CountSinnohDexCaughtMons
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_288
ScrCmd_unk_288: ; 0x0203CF64
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl Pokedex_CountNationalDexSeenMons
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_289
ScrCmd_unk_289: ; 0x0203CF94
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl Pokedex_CountNationalDexCaughtMons
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_290
ScrCmd_unk_290: ; 0x0203CFC4
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_unk_291
ScrCmd_unk_291: ; 0x0203CFC8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	ldr r1, [r5, #0x8]
	str r0, [sp, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	cmp r6, #0x0
	bne _0203D02E
	add r0, r7, #0x0
	bl Pokedex_CountSinnohDexSeenMons_OmitMythicals
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	mov r1, #0x2
	mov r2, #0xa
	bl FUN_0205F2E4
	add r1, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_02054CC8
	b _0203D048
_0203D02E:
	add r0, r7, #0x0
	bl Pokedex_CountNationalDexCaughtMons_OmitMythicals
	add r5, r0, #0x0
	ldr r0, [sp, #0x0]
	bl PlayerProfile_GetTrainerGender
	add r1, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl FUN_02054D1C
_0203D048:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_292
ScrCmd_unk_292: ; 0x0203D050
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	lsl r2, r2, #0x18
	ldr r0, [r5, #0x74]
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	add r3, r4, #0x0
	bl FUN_02046E18
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_701
ScrCmd_unk_701: ; 0x0203D0A4
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r2, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	lsl r2, r2, #0x18
	ldr r0, [r5, #0x74]
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	add r3, r4, #0x0
	bl FUN_02046E18
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_293
ScrCmd_unk_293: ; 0x0203D0F8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r2, r0, #0x0
	lsl r2, r2, #0x18
	ldr r0, [r5, #0x74]
	add r1, r4, #0x0
	lsr r2, r2, #0x18
	bl FUN_02046FA0
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_294
ScrCmd_unk_294: ; 0x0203D134
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_020470AC
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_295
ScrCmd_unk_295: ; 0x0203D140
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl MOD05_021F4DC8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_296
ScrCmd_unk_296: ; 0x0203D150
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl MOD05_021F4D80
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_297
ScrCmd_unk_297: ; 0x0203D178
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FUN_02039438
	add r1, r0, #0x0
	ldr r0, [r4, #0x74]
	bl FUN_02046DB4
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_298
ScrCmd_unk_298: ; 0x0203D194
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl MOD05_021F4E7C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_299
ScrCmd_unk_299: ; 0x0203D1A4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020386B4
	ldr r1, _0203D1BC ; =FUN_0203BC04
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203D1BC: .word FUN_0203BC04 

	thumb_func_start ScrCmd_unk_300
ScrCmd_unk_300: ; 0x0203D1C0
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r5, [r1, #0xc]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0202280C
	cmp r0, #0x0
	beq _0203D1EC
	mov r0, #0x0
	strh r0, [r4, #0x0]
	b _0203D210
_0203D1EC:
	add r0, r5, #0x0
	bl FUN_02022804
	cmp r0, #0x0
	bne _0203D1FC
	mov r0, #0x1
	strh r0, [r4, #0x0]
	b _0203D210
_0203D1FC:
	add r0, r5, #0x0
	bl SaveGetDirtyBit
	cmp r0, #0x0
	beq _0203D20C
	mov r0, #0x2
	strh r0, [r4, #0x0]
	b _0203D210
_0203D20C:
	mov r0, #0x3
	strh r0, [r4, #0x0]
_0203D210:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_301
ScrCmd_unk_301: ; 0x0203D214
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl MOD05_021E85FC
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_305
ScrCmd_unk_305: ; 0x0203D23C
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl MOD05_021E3424
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_306
ScrCmd_unk_306: ; 0x0203D248
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Poketch_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl Sav2_Poketch_IsGiven
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_307
ScrCmd_unk_307: ; 0x0203D278
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl Sav2_Poketch_get
	add r1, r5, #0x0
	bl Sav2_Poketch_UnlockApp
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_308
ScrCmd_unk_308: ; 0x0203D2A4
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl Sav2_Poketch_get
	add r1, r6, #0x0
	bl Sav2_Poketch_AppIsUnlocked
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_309
ScrCmd_unk_309: ; 0x0203D2E4
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [r4, #0x64]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02031588
	ldr r1, _0203D310 ; =FUN_0203D314
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203D310: .word FUN_0203D314 

	thumb_func_start FUN_0203D314
FUN_0203D314: ; 0x0203D314
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02030F20
	cmp r0, #0x2
	bge _0203D324
	mov r0, #0x1
	pop {r4, pc}
_0203D324:
	ldr r0, [r4, #0x64]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020315D8
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_310
ScrCmd_unk_310: ; 0x0203D330
	push {r3, lr}
	bl FUN_0203168C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_311
ScrCmd_unk_311: ; 0x0203D33C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0205296C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_312
ScrCmd_unk_312: ; 0x0203D36C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r1, r0, #0x0
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r1, [r1, #0x0]
	ldr r0, [r0, #0x78]
	bl FUN_02052C0C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_313
ScrCmd_unk_313: ; 0x0203D3A4
	push {r4, lr}
	bl ScriptReadHalfword
	add r4, r0, #0x0
	cmp r4, #0x5
	beq _0203D3BC
	cmp r4, #0x7
	beq _0203D3BC
	cmp r4, #0x9
	beq _0203D3BC
	cmp r4, #0x6
	bne _0203D3C2
_0203D3BC:
	bl FUN_02031C54
	b _0203D3CA
_0203D3C2:
	cmp r4, #0xb
	bne _0203D3CA
	bl FUN_02031C64
_0203D3CA:
	bl FUN_02031190
	cmp r0, #0x0
	bne _0203D3D8
	add r0, r4, #0x0
	bl FUN_02052B74
_0203D3D8:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_316
ScrCmd_unk_316: ; 0x0203D3DC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl ScriptEnvironment_GetSav2Ptr
	bl Sav2_PlayerData_GetProfileAddr
	add r5, #0x80
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02013B5C
	add r5, r0, #0x0
	cmp r4, #0x0
	bne _0203D432
	ldr r0, [r7, #0x0]
	bl FUN_02058448
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	b _0203D434
_0203D432:
	mov r2, #0x0
_0203D434:
	str r5, [sp, #0x0]
	ldr r0, [r6, #0x0]
	ldr r3, [sp, #0x4]
	add r1, r4, #0x0
	bl FUN_02052D08
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_317
ScrCmd_unk_317: ; 0x0203D448
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0208881C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_318
ScrCmd_unk_318: ; 0x0203D458
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x7c]
	bl FUN_02052F74
	bl FUN_02031B50
	ldr r1, _0203D478 ; =FUN_0203D47C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203D478: .word FUN_0203D47C 

	thumb_func_start FUN_0203D47C
FUN_0203D47C: ; 0x0203D47C
	push {r3, lr}
	bl FUN_02030F20
	cmp r0, #0x2
	bge _0203D48A
	mov r0, #0x1
	pop {r3, pc}
_0203D48A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_319
ScrCmd_unk_319: ; 0x0203D490
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r7, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02058448
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r2, [sp, #0x0]
	ldr r0, [r0, #0x78]
	ldr r3, [r7, #0x0]
	bl FUN_02052A10
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_698
ScrCmd_unk_698: ; 0x0203D4E8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x78]
	bl FUN_020527A8
	strh r0, [r4, #0x0]
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0203D522
	add r5, #0x80
	ldr r0, [r5, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FreeToHeap
_0203D522:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_320
ScrCmd_unk_320: ; 0x0203D528
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0xa
	add r0, r5, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	ldr r0, [r6, #0x0]
	bl FUN_02058448
	add r1, r0, #0x0
	ldr r0, [r5, #0x78]
	bl FUN_020524CC
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_326
ScrCmd_unk_326: ; 0x0203D560
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0xa
	add r0, r5, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	ldr r0, [r6, #0x0]
	bl FUN_02058448
	add r1, r0, #0x0
	ldr r0, [r5, #0x78]
	add r2, r7, #0x0
	bl FUN_02052544
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_321
ScrCmd_unk_321: ; 0x0203D5B0
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	str r0, [r4, #0x64]
	ldr r1, _0203D5C8 ; =FUN_0203D5CC
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203D5C8: .word FUN_0203D5CC 

	thumb_func_start FUN_0203D5CC
FUN_0203D5CC: ; 0x0203D5CC
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	ldr r0, [r5, #0x78]
	bl FUN_02052604
	ldr r1, [r6, #0x64]
	add r4, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl GetVarPointer
	cmp r4, #0x0
	bne _0203D5F0
	mov r0, #0x0
	pop {r4-r6, pc}
_0203D5F0:
	strh r4, [r0, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_322
ScrCmd_unk_322: ; 0x0203D5F8
	push {r3, lr}
	add r0, #0x80
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x34]
	ldr r1, [r1, #0x7c]
	bl FUN_020534DC
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_314
ScrCmd_unk_314: ; 0x0203D60C
	push {r3, lr}
	mov r0, #0x4
	bl FUN_02052B74
	bl FUN_02031C2C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_315
ScrCmd_unk_315: ; 0x0203D61C
	push {r3, lr}
	bl FUN_02031C64
	bl FUN_02031B50
	mov r0, #0x0
	bl FUN_02052B74
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_323
ScrCmd_unk_323: ; 0x0203D630
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r2, r0, #0x0
	ldr r0, [r4, #0x78]
	add r1, r6, #0x0
	bl FUN_0205265C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_324
ScrCmd_unk_324: ; 0x0203D66C
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	str r0, [r4, #0x64]
	ldr r1, _0203D684 ; =FUN_0203D688
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203D684: .word FUN_0203D688 

	thumb_func_start FUN_0203D688
FUN_0203D688: ; 0x0203D688
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x78]
	bl FUN_02052608
	cmp r0, #0x1
	blo _0203D6BC
	add r5, #0x80
	strh r0, [r4, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x78]
	bl FUN_02052E10
	mov r0, #0x1
	pop {r3-r5, pc}
_0203D6BC:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_325
ScrCmd_unk_325: ; 0x0203D6C4
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	str r0, [r4, #0x64]
	ldr r1, _0203D6DC ; =FUN_0203D6E0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203D6DC: .word FUN_0203D6E0 

	thumb_func_start FUN_0203D6E0
FUN_0203D6E0: ; 0x0203D6E0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x78]
	bl FUN_02052648
	ldr r1, _0203D724 ; =gMain
	ldr r2, [r1, #0x48]
	mov r1, #0x2
	tst r1, r2
	beq _0203D716
	add r5, #0x80
	ldr r0, [r5, #0x0]
	mov r1, #0x8
	ldr r0, [r0, #0x78]
	bl FUN_02052718
_0203D716:
	cmp r0, #0x0
	beq _0203D720
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
_0203D720:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0203D724: .word gMain

	thumb_func_start ScrCmd_unk_339
ScrCmd_unk_339: ; 0x0203D728
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02049EA4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_340
ScrCmd_unk_340: ; 0x0203D738
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl ScriptEnvironment_GetSav2Ptr
	bl Sav2_PlayerData_GetProfileAddr
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl PlayerProfile_GetTrainerID
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl PlayerProfile_GetTrainerGender
	add r1, r0, #0x0
	ldr r2, [r4, #0x0]
	add r0, r6, #0x0
	bl FUN_0205363C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_341
ScrCmd_unk_341: ; 0x0203D774
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl ScriptEnvironment_GetSav2Ptr
	bl Sav2_PlayerData_GetProfileAddr
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl PlayerProfile_GetTrainerID
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl PlayerProfile_GetTrainerGender
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02053678
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl PlayerProfile_GetTrainerGender
	ldrh r1, [r4, #0x0]
	mov r2, #0x2
	bl FUN_020536D0
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_668
ScrCmd_unk_668: ; 0x0203D7DC
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl ScriptEnvironment_GetSav2Ptr
	bl Sav2_PlayerData_GetProfileAddr
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl PlayerProfile_GetTrainerID
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl PlayerProfile_GetTrainerGender
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02053678
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_342
ScrCmd_unk_342: ; 0x0203D834
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl ScriptEnvironment_GetSav2Ptr
	bl Sav2_PlayerData_GetProfileAddr
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r1, r0, #0x0
	lsl r1, r1, #0x18
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	bl PlayerProfile_SetAvatar
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_331
ScrCmd_unk_331: ; 0x0203D868
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_02048498
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_332
ScrCmd_unk_332: ; 0x0203D874
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	add r1, r4, #0x0
	bl FUN_02034E04
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_getplayergender
ScrCmd_getplayergender: ; 0x0203D8A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl ScriptEnvironment_GetSav2Ptr
	bl Sav2_PlayerData_GetProfileAddr
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl PlayerProfile_GetTrainerGender
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_healparty
ScrCmd_healparty: ; 0x0203D8D0
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_02046528
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	bl HealParty
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_335
ScrCmd_unk_335: ; 0x0203D8E8
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_unk_336
ScrCmd_unk_336: ; 0x0203D8EC
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02050024
	ldr r1, _0203D900 ; =FUN_0203D904
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203D900: .word FUN_0203D904 

	thumb_func_start FUN_0203D904
FUN_0203D904: ; 0x0203D904
	push {r3, lr}
	bl FUN_02031810
	cmp r0, #0x1
	beq _0203D91A
	bl FUN_0202EDF8
	cmp r0, #0x1
	beq _0203D91A
	mov r0, #0x1
	pop {r3, pc}
_0203D91A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_699
ScrCmd_unk_699: ; 0x0203D920
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02050048
	ldr r1, _0203D934 ; =FUN_0203D904
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203D934: .word FUN_0203D904 

	thumb_func_start ScrCmd_unk_337
ScrCmd_unk_337: ; 0x0203D938
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0204FF5C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_338
ScrCmd_unk_338: ; 0x0203D948
	push {r3, lr}
	bl ScriptReadHalfword
	bl FUN_0204F6DC
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_378
ScrCmd_unk_378: ; 0x0203D958
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Bag_get
	add r1, r6, #0x0
	bl Bag_PocketNotEmpty
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_390
ScrCmd_unk_390: ; 0x0203D998
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r3, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02034B74
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_391
ScrCmd_unk_391: ; 0x0203D9E8
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x8]
	add r5, r0, #0x0
	add r1, r7, #0x0
	str r4, [sp, #0x0]
	bl FUN_02058E28
	add r0, r5, #0x0
	bl FUN_02059D1C
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_392
ScrCmd_unk_392: ; 0x0203DA78
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r2, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_02034BDC
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_393
ScrCmd_unk_393: ; 0x0203DAB0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r2, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_02034BAC
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_394
ScrCmd_unk_394: ; 0x0203DAE8
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r3, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02034C0C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_395
ScrCmd_unk_395: ; 0x0203DB38
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r3, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02034C34
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_396
ScrCmd_unk_396: ; 0x0203DB88
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	add r5, r0, #0x0
	bne _0203DBC6
	bl ErrorHandling
_0203DBC6:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl MOD05_021F1EC0
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_399
ScrCmd_unk_399: ; 0x0203DBD4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xc
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	ldr r1, [r5, #0x0]
	cmp r1, #0x0
	beq _0203DBFC
	strh r0, [r1, #0x0]
_0203DBFC:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_360
ScrCmd_unk_360: ; 0x0203DC00
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	lsl r1, r4, #0x5
	ldr r3, [r5, #0x8]
	add r2, r0, #0x0
	add r0, r3, #0x1
	str r0, [r5, #0x8]
	add r5, #0x80
	lsl r4, r6, #0x5
	ldrb r3, [r3, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r7, r1
	add r2, r2, r4
	bl MOD05_021DAE40
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_361
ScrCmd_unk_361: ; 0x0203DC58
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021DAF78
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_362
ScrCmd_unk_362: ; 0x0203DC70
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021DAF98
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_363
ScrCmd_unk_363: ; 0x0203DC88
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021DAED4
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_364
ScrCmd_unk_364: ; 0x0203DCA0
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021DAF28
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_367
ScrCmd_unk_367: ; 0x0203DCB8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02064CA8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_368
ScrCmd_unk_368: ; 0x0203DCC8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl MOD06_02241230
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_369
ScrCmd_unk_369: ; 0x0203DCD8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02064CC8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_370
ScrCmd_unk_370: ; 0x0203DCE8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl MOD06_02241914
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_371
ScrCmd_unk_371: ; 0x0203DCF8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02064D10
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_372
ScrCmd_unk_372: ; 0x0203DD08
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02064D4C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_373
ScrCmd_unk_373: ; 0x0203DD18
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	add r0, r3, #0x0
	bl FUN_02064D88
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_374
ScrCmd_unk_374: ; 0x0203DD34
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	add r0, r3, #0x0
	bl MOD06_02242A38
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_428
ScrCmd_unk_428: ; 0x0203DD50
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020388B4
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_414
ScrCmd_unk_414: ; 0x0203DD60
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r0, [r5, #0x64]
	ldr r0, [r6, #0x0]
	bl FUN_02058448
	add r1, r5, #0x0
	add r1, #0x80
	add r2, r0, #0x0
	ldr r1, [r1, #0x0]
	add r0, r7, #0x0
	bl MOD18_0224CA54
	str r0, [r4, #0x0]
	ldr r1, _0203DDBC ; =FUN_0203DDC0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0203DDBC: .word FUN_0203DDC0 

	thumb_func_start FUN_0203DDC0
FUN_0203DDC0: ; 0x0203DDC0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	ldr r1, [r5, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl MOD18_0224CA2C
	strh r0, [r5, #0x0]
	ldrh r1, [r5, #0x0]
	ldr r0, _0203DDFC ; =0x0000FFFE
	cmp r1, r0
	beq _0203DDF6
	mov r0, #0x1
	pop {r3-r5, pc}
_0203DDF6:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203DDFC: .word 0x0000FFFE

	thumb_func_start ScrCmd_unk_415
ScrCmd_unk_415: ; 0x0203DE00
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x3
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	bl MOD18_0224CA58
	strb r0, [r4, #0x0]
	ldr r1, _0203DE34 ; =FUN_0203DE38
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203DE34: .word FUN_0203DE38 

	thumb_func_start FUN_0203DE38
FUN_0203DE38: ; 0x0203DE38
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x3
	bl FUN_02039438
	ldrb r0, [r0, #0x0]
	bl FUN_020546C8
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_416
ScrCmd_unk_416: ; 0x0203DE4C
	push {r3, lr}
	bl MOD11_0224CA94
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_417
ScrCmd_unk_417: ; 0x0203DE58
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r5, [r2, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MOD18_0224CAA0
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_418
ScrCmd_unk_418: ; 0x0203DE80
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r5, [r2, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MOD18_0224CAB4
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_63
ScrCmd_unk_63: ; 0x0203DEA8
	push {r3, lr}
	sub sp, #0x8
	mov r3, #0x0
	str r3, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r1, #0x1
	ldr r0, [r0, #0x74]
	add r2, r1, #0x0
	bl MOD06_02242BE0
	mov r0, #0x1
	add sp, #0x8
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_433
ScrCmd_unk_433: ; 0x0203DEC4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r1, r0, #0x0
	ldr r0, [r5, #0x34]
	bl FUN_02058060
	add r4, r0, #0x0
	bne _0203DEEC
	bl ErrorHandling
_0203DEEC:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0205889C
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_434
ScrCmd_unk_434: ; 0x0203DEF8
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r1, r0, #0x0
	ldr r0, [r5, #0x34]
	bl FUN_02058060
	add r4, r0, #0x0
	bne _0203DF20
	bl ErrorHandling
_0203DF20:
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0205889C
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_435
ScrCmd_unk_435: ; 0x0203DF2C
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_02066818
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_436
ScrCmd_unk_436: ; 0x0203DF38
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl Sav2_Mailbox_get
	mov r1, #0x0
	bl Mailbox_CountMessages
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_437
ScrCmd_unk_437: ; 0x0203DF64
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r1, r0, #0x0
	ldr r0, [r4, #0x74]
	bl FUN_02063650
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_438
ScrCmd_unk_438: ; 0x0203DF84
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl Script_GetTimeOfDay
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_439
ScrCmd_unk_439: ; 0x0203DFA8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r5, r0, #0x0
	bl LCRandom
	add r1, r5, #0x0
	bl _s32_div_f
	strh r1, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_440
ScrCmd_unk_440: ; 0x0203DFE0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r5, r0, #0x0
	bl LCRandom
	add r1, r5, #0x0
	bl _s32_div_f
	strh r1, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_449
ScrCmd_unk_449: ; 0x0203E018
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl MOD05_021F3A18
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_450
ScrCmd_unk_450: ; 0x0203E054
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MOD05_021F3AB4
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_451
ScrCmd_unk_451: ; 0x0203E078
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	lsl r1, r6, #0x18
	lsl r2, r7, #0x18
	add r3, r0, #0x0
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl MOD05_021F3B7C
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_unk_452
ScrCmd_unk_452: ; 0x0203E0CC
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	lsl r1, r6, #0x18
	lsl r2, r7, #0x18
	add r3, r0, #0x0
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl MOD05_021F3B4C
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_unk_453
ScrCmd_unk_453: ; 0x0203E120
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	mov r1, #0x82
	lsl r1, r1, #0x8
	bl FUN_0205F3F8
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_460
ScrCmd_unk_460: ; 0x0203E138
	push {r4, lr}
	add r0, #0x80
	ldr r4, [r0, #0x0]
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	mov r1, #0x1
	bl FUN_0205F2D4
	ldr r0, [r4, #0xc]
	bl FUN_020289A4
	mov r1, #0x1
	bl FUN_020289B0
	add r1, r4, #0x0
	add r1, #0x98
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_02048C58
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_461
ScrCmd_unk_461: ; 0x0203E168
	push {r3-r7, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r7, #0x0
	sub r0, #0x10
	cmp r0, #0xa
	bhi _0203E23A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0203E1EA: ; jump table (using 16-bit offset)
	.short _0203E200 - _0203E1EA - 2; case 0
	.short _0203E20C - _0203E1EA - 2; case 1
	.short _0203E218 - _0203E1EA - 2; case 2
	.short _0203E226 - _0203E1EA - 2; case 3
	.short _0203E23A - _0203E1EA - 2; case 4
	.short _0203E226 - _0203E1EA - 2; case 5
	.short _0203E226 - _0203E1EA - 2; case 6
	.short _0203E226 - _0203E1EA - 2; case 7
	.short _0203E226 - _0203E1EA - 2; case 8
	.short _0203E226 - _0203E1EA - 2; case 9
	.short _0203E226 - _0203E1EA - 2; case 10
_0203E200:
	mov r0, #0x4
	mov r6, #0x1
	bl FUN_02029120
	str r0, [r5, #0x0]
	b _0203E23E
_0203E20C:
	mov r0, #0x4
	mov r6, #0x1
	bl FUN_0202912C
	str r0, [r5, #0x0]
	b _0203E23E
_0203E218:
	ldr r0, [sp, #0x0]
	mov r1, #0x4
	mov r6, #0x1
	bl FUN_02029138
	str r0, [r5, #0x0]
	b _0203E23E
_0203E226:
	sub r7, #0x13
	lsl r0, r7, #0x18
	ldr r1, [sp, #0x0]
	lsr r0, r0, #0x18
	mov r2, #0x4
	mov r6, #0x1
	bl FUN_0202914C
	str r0, [r5, #0x0]
	b _0203E23E
_0203E23A:
	mov r0, #0x1
	pop {r3-r7, pc}
_0203E23E:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r1, [r5, #0x0]
	add r0, #0x98
	ldr r0, [r0, #0x0]
	add r2, r6, #0x0
	bl FUN_02028AD4
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_462
ScrCmd_unk_462: ; 0x0203E254
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_unk_466
ScrCmd_unk_466: ; 0x0203E258
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020271A4
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_467
ScrCmd_unk_467: ; 0x0203E29C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020270D8
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_468
ScrCmd_unk_468: ; 0x0203E2F8
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r7, #0x0
	bl FUN_02027114
	cmp r6, r0
	bhi _0203E352
	mov r0, #0x1
	b _0203E354
_0203E352:
	mov r0, #0x0
_0203E354:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_469
ScrCmd_unk_469: ; 0x0203E35C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r4, #0x0
	bl FUN_02027264
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_470
ScrCmd_unk_470: ; 0x0203E38C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r6, #0x0
	bl FUN_02027100
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_488
ScrCmd_unk_488: ; 0x0203E3D0
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	mov r0, #0x0
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl Pokedex_HasCompletedSinnohDex
	cmp r0, #0x1
	bne _0203E404
	mov r0, #0x1
	strh r0, [r4, #0x0]
_0203E404:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_489
ScrCmd_unk_489: ; 0x0203E408
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	mov r0, #0x0
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl Pokedex_HasCompletedNationalDex
	cmp r0, #0x1
	bne _0203E43C
	mov r0, #0x1
	strh r0, [r4, #0x0]
_0203E43C:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_490
ScrCmd_unk_490: ; 0x0203E440
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x20
	mov r2, #0x0
	bl FUN_02038AF4
	str r0, [r4, #0x0]
	ldr r1, _0203E46C ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203E46C: .word FUN_0203BB90 

	thumb_func_start ScrCmd_unk_491
ScrCmd_unk_491: ; 0x0203E470
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x20
	mov r2, #0x1
	bl FUN_02038AF4
	str r0, [r4, #0x0]
	ldr r1, _0203E49C ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203E49C: .word FUN_0203BB90 

	thumb_func_start ScrCmd_unk_492
ScrCmd_unk_492: ; 0x0203E4A0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl MOD06_0224CBB0
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_493
ScrCmd_unk_493: ; 0x0203E4B0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl MOD06_0224CC24
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_495
ScrCmd_unk_495: ; 0x0203E4D8
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_485
ScrCmd_unk_485: ; 0x0203E4F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r4, #0x0
	bl FUN_0202A0E8
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_486
ScrCmd_unk_486: ; 0x0203E510
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r6, #0x0
	bl GetVarPointer
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r7, #0x0
	bl FUN_0202A150
	ldr r1, _0203E564 ; =0xFFFF0000
	and r1, r0
	lsr r1, r1, #0x10
	strh r1, [r4, #0x0]
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0203E564: .word 0xFFFF0000

	thumb_func_start ScrCmd_unk_487
ScrCmd_unk_487: ; 0x0203E568
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	ldr r1, [r5, #0x8]
	add r2, r1, #0x1
	str r2, [r5, #0x8]
	lsl r2, r4, #0x10
	add r4, r2, #0x0
	orr r4, r0
	ldrb r0, [r1, #0x0]
	cmp r0, #0x0
	beq _0203E59C
	cmp r0, #0x1
	beq _0203E5B0
	cmp r0, #0x2
	beq _0203E5C4
	b _0203E5D6
_0203E59C:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0202A11C
	b _0203E5D6
_0203E5B0:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0202A07C
	b _0203E5D6
_0203E5C4:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0202A0A8
_0203E5D6:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_514
ScrCmd_unk_514: ; 0x0203E5DC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02022504
	ldr r1, [r5, #0x8]
	str r0, [sp, #0x4]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r4, [r1, #0x0]
	add r0, r7, #0x0
	bl FUN_02034E24
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl FUN_02034E28
	add r7, r0, #0x0
	cmp r4, #0x0
	beq _0203E62C
	cmp r4, #0x1
	beq _0203E642
	b _0203E66E
_0203E62C:
	ldr r0, [sp, #0x0]
	bl FUN_0205F1F4
	ldr r0, [sp, #0x4]
	bl FUN_02060FD0
	mov r0, #0x1e
	strh r0, [r6, #0x0]
	mov r0, #0x0
	strh r0, [r7, #0x0]
	b _0203E66E
_0203E642:
	ldr r0, [sp, #0x0]
	bl FUN_0205F204
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02061574
	mov r0, #0x4
	bl FUN_0202912C
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r2, #0x1
	add r0, #0x98
	ldr r0, [r0, #0x0]
	bl FUN_02028AD4
	mov r0, #0x0
	strh r0, [r6, #0x0]
	strh r0, [r7, #0x0]
_0203E66E:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_unk_518
ScrCmd_unk_518: ; 0x0203E674
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0206015C
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_525
ScrCmd_unk_525: ; 0x0203E684
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl MOD06_022456E8
	strh r0, [r6, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_526
ScrCmd_unk_526: ; 0x0203E6B4
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02064E20
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_527
ScrCmd_unk_527: ; 0x0203E6C4
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	mov r1, #0x0
	add r6, r0, #0x0
	mov r0, #0x41
	add r2, r1, #0x0
	bl FUN_0200433C
	add r5, #0x80
	ldrh r1, [r4, #0x0]
	ldr r0, [r5, #0x0]
	add r2, r6, #0x0
	bl MOD06_0224525C
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_528
ScrCmd_unk_528: ; 0x0203E6FC
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	bl MOD06_02245340
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_529
ScrCmd_unk_529: ; 0x0203E72C
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_02055560
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_532
ScrCmd_unk_532: ; 0x0203E744
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F688
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_536
ScrCmd_unk_536: ; 0x0203E774
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	bl Pokedex_CountSinnohDexSeenMons
	add r4, r0, #0x0
	bl LCRandom
	add r1, r4, #0x0
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r6, r0, #0x10
	ldr r0, [sp, #0x0]
	mov r1, #0x19
	strh r1, [r0, #0x0]
	mov r4, #0x1
	mov r5, #0x0
_0203E7B6:
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl Pokedex_CheckMonSeenFlag
	cmp r0, #0x1
	bne _0203E7DC
	add r0, r4, #0x0
	bl SpeciesToSinnohDexNo
	cmp r0, #0x0
	beq _0203E7DC
	cmp r5, r6
	bne _0203E7D6
	ldr r0, [sp, #0x0]
	strh r4, [r0, #0x0]
	b _0203E7E8
_0203E7D6:
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_0203E7DC:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, _0203E7EC ; =0x000001ED
	cmp r4, r0
	bls _0203E7B6
_0203E7E8:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0203E7EC: .word 0x000001ED

	thumb_func_start ScrCmd_unk_537
ScrCmd_unk_537: ; 0x0203E7F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	add r1, r4, #0x0
	bl FUN_0205F5A4
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_538
ScrCmd_unk_538: ; 0x0203E81C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F594
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_539
ScrCmd_unk_539: ; 0x0203E848
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202AA00
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_540
ScrCmd_unk_540: ; 0x0203E858
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02060490
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_550
ScrCmd_unk_550: ; 0x0203E870
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r4, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r1, [r1, #0x0]
	mov r0, #0xb
	bl MOD06_0224884C
	str r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_551
ScrCmd_unk_551: ; 0x0203E894
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl MOD06_022488EC
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_552
ScrCmd_unk_552: ; 0x0203E8C4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl MOD06_022488F4
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_553
ScrCmd_unk_553: ; 0x0203E8F4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r2, r0, #0x0
	ldr r0, [r5, #0x74]
	ldr r1, [r4, #0x0]
	mov r3, #0xb
	bl FUN_02060790
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_554
ScrCmd_unk_554: ; 0x0203E928
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl MOD06_022488CC
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_555
ScrCmd_unk_555: ; 0x0203E940
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	bl FUN_02024D4C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_556
ScrCmd_unk_556: ; 0x0203E954
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	bl FUN_02024CE0
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_557
ScrCmd_unk_557: ; 0x0203E968
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	mov r0, #0x0
	strh r0, [r6, #0x0]
	cmp r4, #0x1
	bne _0203E9AE
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	bl Pokedex_SetNatDexFlag
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	bl PlayerProfile_SetNatDexFlag
	b _0203E9C8
_0203E9AE:
	cmp r4, #0x2
	bne _0203E9C4
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	bl Pokedex_GetNatDexFlag
	strh r0, [r6, #0x0]
	b _0203E9C8
_0203E9C4:
	bl ErrorHandling
_0203E9C8:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_563
ScrCmd_unk_563: ; 0x0203E9CC
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r4, #0x0
	bl GetPartyMonByIndex
	add r5, r0, #0x0
	mov r1, #0xd
	mov r2, #0x0
	bl GetMonData
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xe
	mov r2, #0x0
	bl GetMonData
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xf
	mov r2, #0x0
	bl GetMonData
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x10
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x11
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x12
	mov r2, #0x0
	bl GetMonData
	add r1, r4, r6
	add r2, r7, r1
	ldr r1, [sp, #0x4]
	add r2, r1, r2
	ldr r1, [sp, #0x8]
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, [sp, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_564
ScrCmd_unk_564: ; 0x0203EA68
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl GF_RTC_CopyDate
	ldr r0, [sp, #0xc]
	strh r0, [r4, #0x0]
	mov r0, #0x0
	add sp, #0x10
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_569
ScrCmd_unk_569: ; 0x0203EA90
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r1, r0, #0x0
	ldr r0, [r4, #0x74]
	bl MOD06_022411F4
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_570
ScrCmd_unk_570: ; 0x0203EAB0
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r7, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r5, #0x0
	bl MOD05_021F61E8
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl MOD05_021F61DC
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_571
ScrCmd_unk_571: ; 0x0203EB20
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r4, #0x80
	lsl r1, r1, #0x18
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	bl MOD06_0224C27C
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_572
ScrCmd_unk_572: ; 0x0203EB48
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r2, r0, #0x0
	add r5, #0x80
	lsl r1, r4, #0x18
	lsl r2, r2, #0x18
	ldr r0, [r5, #0x0]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl MOD06_0224C520
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_573
ScrCmd_unk_573: ; 0x0203EB88
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	ldr r1, [r5, #0x8]
	add r2, r1, #0x1
	str r2, [r5, #0x8]
	ldrb r6, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r7, [sp, #0x0]
	add r5, #0x80
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	ldr r3, [sp, #0x8]
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_020607D4
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start ScrCmd_gameversion
ScrCmd_gameversion: ; 0x0203EBC8
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	mov r1, #GAME_VERSION
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_givewallpaper
ScrCmd_givewallpaper: ; 0x0203EBE4
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	add r0, r6, #0x0
	bl ScriptEnvironment_GetSav2Ptr
	bl Sav2_PlayerData_GetProfileAddr
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	ldr r0, [r6, #0xc]
	bl GetStoragePCPointer
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	add r1, r7, #0x0
	bl MOD06_0224D14C
	add r5, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r5, r0
	beq _0203EC7E
	cmp r5, #0x7
	ble _0203EC88
_0203EC7E:
	mov r0, #0xff
	strh r0, [r4, #0x0]
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0203EC88:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl PCStorage_IsBonusWallpaperUnlocked
	cmp r0, #0x0
	beq _0203EC98
	mov r0, #0x0
	b _0203ECA2
_0203EC98:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl PCStorage_UnlockBonusWallpaper
	add r0, r5, #0x1
_0203ECA2:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_586
ScrCmd_unk_586: ; 0x0203ECAC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r4, [r1, #0xc]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02026CB4
	bl FUN_020269CC
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_587
ScrCmd_unk_587: ; 0x0203ECD8
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	add r0, r3, #0x0
	bl MOD06_0224C678
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_588
ScrCmd_unk_588: ; 0x0203ECF4
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	add r0, r3, #0x0
	bl MOD06_0224C6E8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_589
ScrCmd_unk_589: ; 0x0203ED10
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	add r0, r3, #0x0
	bl MOD06_0224C6F4
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203ED2C
FUN_0203ED2C: ; 0x0203ED2C
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	bl Sav2_Pokedex_get
	add r6, r0, #0x0
	mov r0, #0x20
	bl AllocMonZeroed
	add r4, r0, #0x0
	bl ZeroMonData
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x32
	mov r3, #0x20
	bl CreateMon
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl Pokedex_SetMonSeenFlag
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_pcfreespace
ScrCmd_pcfreespace: ; 0x0203ED70
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl GetStoragePCPointer
	bl PCStorage_CountMonsAndEggsInAllBoxes
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	mov r0, #0x87
	lsl r0, r0, #0x2
	sub r0, r0, r1
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_600
ScrCmd_unk_600: ; 0x0203EDA4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x16
	bl FUN_02039438
	add r4, r0, #0x0
	mov r0, #0x0
	add r5, #0x80
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x0]
	bl MOD05_021E7184
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_601
ScrCmd_unk_601: ; 0x0203EDC8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x16
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl MOD05_021E71E8
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_602
ScrCmd_unk_602: ; 0x0203EDE0
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r1, r0, #0x0
	add r4, #0x80
	lsl r1, r1, #0x18
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	bl MOD06_0224E554
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_603
ScrCmd_unk_603: ; 0x0203EE08
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0206486C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_604
ScrCmd_unk_604: ; 0x0203EE18
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020649D4
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_605
ScrCmd_unk_605: ; 0x0203EE28
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020649B0
	cmp r0, #0x0
	beq _0203EE4E
	mov r0, #0x1
	b _0203EE50
_0203EE4E:
	mov r0, #0x0
_0203EE50:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_606
ScrCmd_unk_606: ; 0x0203EE58
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl MOD06_0224E764
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_607
ScrCmd_unk_607: ; 0x0203EE68
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl MOD06_0224E7C4
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_608
ScrCmd_unk_608: ; 0x0203EE78
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r4, #0x0
	bl FUN_0202A170
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_610
ScrCmd_unk_610: ; 0x0203EE98
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r6, #0x0
	bl PartyHasMon
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_611
ScrCmd_unk_611: ; 0x0203EED8
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r1, sp, #0x4
	strh r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	str r0, [sp, #0x0]
	bl GetPartyCount
	add r4, #0x80
	add r6, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	add r7, r0, #0x0
	mov r5, #0x0
	cmp r6, #0x0
	ble _0203EF4E
_0203EF18:
	ldr r0, [sp, #0x0]
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x5
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	ldr r1, _0203EF54 ; =0x00000182
	cmp r0, r1
	bne _0203EF48
	add r0, r4, #0x0
	mov r1, #0x70
	add r2, sp, #0x4
	bl SetMonData
	add r0, r4, #0x0
	bl CalcMonLevelAndStats
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl Pokedex_SetMonCaughtFlag
_0203EF48:
	add r5, r5, #0x1
	cmp r5, r6
	blt _0203EF18
_0203EF4E:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0203EF54: .word 0x00000182

	thumb_func_start ScrCmd_unk_612
ScrCmd_unk_612: ; 0x0203EF58
	push {r3-r7, lr}
	sub sp, #0x30
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	str r0, [sp, #0xc]
	bl GetPartyCount
	add r2, sp, #0x18
	mov r4, #0x0
	ldr r3, _0203F008 ; =UNK_020F34FC
	str r0, [sp, #0x8]
	add r7, r2, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [sp, #0x8]
	str r4, [sp, #0x4]
	cmp r0, #0x0
	ble _0203EFFC
	mov r5, #0x1
	str r7, [sp, #0x14]
_0203EFA2:
	ldr r0, [sp, #0xc]
	add r1, r4, #0x0
	bl GetPartyMonByIndex
	add r6, r0, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x10]
	add r0, r6, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl GetMonData
	add r3, r0, #0x0
	mov r0, #0x67
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0x2
	cmp r1, r0
	bne _0203EFF2
	mov r2, #0x0
	add r1, r2, #0x0
	str r3, [r7, #0x0]
	cmp r4, #0x0
	ble _0203EFE8
	ldr r6, [sp, #0x14]
_0203EFD8:
	ldr r0, [r6, #0x0]
	cmp r3, r0
	bne _0203EFE0
	add r2, r5, #0x0
_0203EFE0:
	add r1, r1, #0x1
	add r6, r6, #0x4
	cmp r1, r4
	blt _0203EFD8
_0203EFE8:
	cmp r2, #0x0
	bne _0203EFF2
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	str r0, [sp, #0x4]
_0203EFF2:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r7, r7, #0x4
	cmp r4, r0
	blt _0203EFA2
_0203EFFC:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x1
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_0203F008: .word UNK_020F34FC

	thumb_func_start ScrCmd_unk_613
ScrCmd_unk_613: ; 0x0203F00C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F1C4
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_614
ScrCmd_unk_614: ; 0x0203F020
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F1D4
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_615
ScrCmd_unk_615: ; 0x0203F034
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_020389CC
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start ScrCmd_unk_616
ScrCmd_unk_616: ; 0x0203F058
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl Script_GetHour
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_617
ScrCmd_unk_617: ; 0x0203F07C
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	add r7, r0, #0x0
	bne _0203F0FA
	bl ErrorHandling
_0203F0FA:
	str r6, [sp, #0x0]
	str r4, [sp, #0x4]
	ldr r0, [r5, #0x74]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x8]
	add r1, r7, #0x0
	bl FUN_02054F50
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_unk_618
ScrCmd_unk_618: ; 0x0203F110
	push {r3-r7, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r5, #0x0
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	add r5, r0, #0x0
	bne _0203F164
	bl ErrorHandling
_0203F164:
	ldr r0, [r4, #0x74]
	add r1, r5, #0x0
	add r2, r7, #0x0
	add r3, r6, #0x0
	bl FUN_0205502C
	mov r0, #0x1
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_unk_619
ScrCmd_unk_619: ; 0x0203F174
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02054E30
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_620
ScrCmd_unk_620: ; 0x0203F19C
	push {r4-r7, lr}
	sub sp, #0x24
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	mov r6, #0x0
	add r7, r0, #0x0
	add r4, r6, #0x0
	add r5, sp, #0x4
_0203F1CA:
	add r1, r4, #0x0
	add r0, r7, #0x0
	add r1, #0x22
	mov r2, #0x1
	bl FUN_020270D8
	cmp r0, #0x1
	bne _0203F1E0
	mov r0, #0x1
	strh r0, [r5, #0x0]
	add r6, r6, #0x1
_0203F1E0:
	add r4, r4, #0x1
	add r5, r5, #0x2
	cmp r4, #0x10
	blt _0203F1CA
	cmp r6, #0x0
	bne _0203F1F8
	ldr r0, [sp, #0x0]
	ldr r1, _0203F230 ; =0x0000FFFF
	add sp, #0x24
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4-r7, pc}
_0203F1F8:
	bl LCRandom
	add r1, r6, #0x0
	bl _s32_div_f
	mov r4, #0x0
	add r2, sp, #0x4
_0203F206:
	ldrh r0, [r2, #0x0]
	cmp r0, #0x1
	bne _0203F212
	cmp r1, #0x0
	beq _0203F21A
	sub r1, r1, #0x1
_0203F212:
	add r4, r4, #0x1
	add r2, r2, #0x2
	cmp r4, #0x10
	blt _0203F206
_0203F21A:
	cmp r4, #0x10
	blt _0203F222
	bl ErrorHandling
_0203F222:
	ldr r0, [sp, #0x0]
	add r4, #0x22
	strh r4, [r0, #0x0]
	mov r0, #0x0
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_0203F230: .word 0x0000FFFF

	thumb_func_start ScrCmd_unk_622
ScrCmd_unk_622: ; 0x0203F234
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	ldr r1, _0203F250 ; =gMain + 0x60
	ldrb r1, [r1, #0x6]
	strh r1, [r0, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203F250: .word gMain + 0x60

	thumb_func_start ScrCmd_unk_623
ScrCmd_unk_623: ; 0x0203F254
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	mov r1, #0x0
	bl FUN_0205F698
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_624
ScrCmd_unk_624: ; 0x0203F26C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldrb r4, [r1, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	cmp r4, #0x0
	beq _0203F2A0
	add r1, r6, #0x0
	bl FUN_0205F4E4
	b _0203F2A6
_0203F2A0:
	add r1, r6, #0x0
	bl FUN_0205F50C
_0203F2A6:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_627
ScrCmd_unk_627: ; 0x0203F2AC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl BufferContestBackgroundName
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_629
ScrCmd_unk_629: ; 0x0203F2E4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205F6C8
	cmp r0, #0xa
	blo _0203F314
	mov r0, #0x1
	b _0203F316
_0203F314:
	mov r0, #0x0
_0203F316:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_631
ScrCmd_unk_631: ; 0x0203F31C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F648
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_633
ScrCmd_unk_633: ; 0x0203F348
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02027210
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_634
ScrCmd_unk_634: ; 0x0203F38C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02046030
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_635
ScrCmd_unk_635: ; 0x0203F39C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0205F668
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_unk_637
ScrCmd_unk_637: ; 0x0203F3AC
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02013B5C
	bl FUN_02013B74
	cmp r0, #0x20
	bne _0203F3FE
	ldr r0, _0203F414 ; =0x0000FFFF
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
_0203F3FE:
	strh r0, [r4, #0x0]
	bl FUN_02013BE4
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r7, #0x0
	bl FUN_0200B518
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_0203F414: .word 0x0000FFFF

	thumb_func_start ScrCmd_unk_639
ScrCmd_unk_639: ; 0x0203F418
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02013B5C
	bl FUN_02013BC8
	cmp r0, #0x1
	bne _0203F444
	mov r0, #0x1
	b _0203F446
_0203F444:
	mov r0, #0x0
_0203F446:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_638
ScrCmd_unk_638: ; 0x0203F44C
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205F710
	cmp r0, #0x5
	blo _0203F47C
	mov r0, #0x1
	b _0203F47E
_0203F47C:
	mov r0, #0x0
_0203F47E:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_642
ScrCmd_unk_642: ; 0x0203F484
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	ldr r5, [r5, #0x0]
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl Sav2_SysInfo_get
	add r7, r0, #0x0
	bl Sav2_SysInfo_GetBirthMonth
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl Script_GetMonth
	cmp r6, r0
	bne _0203F4CE
	add r0, r7, #0x0
	bl Sav2_SysInfo_GetBirthDay
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl Script_GetDay
	cmp r6, r0
	bne _0203F4CE
	mov r0, #0x1
	strh r0, [r4, #0x0]
	b _0203F4D2
_0203F4CE:
	mov r0, #0x0
	strh r0, [r4, #0x0]
_0203F4D2:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_644
ScrCmd_unk_644: ; 0x0203F4D8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_Pokedex_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl Pokedex_CountSeenUnown
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_645
ScrCmd_unk_645: ; 0x0203F508
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r1, r6, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r2, [r1, #0x1c]
	ldr r1, [r2, #0x8]
	lsl r1, r1, #0x10
	lsr r5, r1, #0x10
	ldr r1, [r2, #0xc]
	lsl r1, r1, #0x10
	lsr r4, r1, #0x10
	cmp r7, #0x3
	blo _0203F54C
	ldr r7, _0203F5C8 ; =0x0000010E
	b _0203F582
_0203F54C:
	cmp r0, #0x1e
	blo _0203F556
	mov r7, #0x43
	lsl r7, r7, #0x2
	b _0203F582
_0203F556:
	bl LCRandom
	mov r1, #0x64
	bl _s32_div_f
	cmp r1, #0x19
	bge _0203F568
	ldr r7, _0203F5CC ; =0x0000010D
	b _0203F582
_0203F568:
	bl LCRandom
	mov r1, #0x6
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r1, r0, #0x10
	mov r0, #0x6
	mul r0, r7
	add r0, r1, r0
	lsl r1, r0, #0x1
	ldr r0, _0203F5D0 ; =UNK_020F3538
	ldrh r7, [r0, r1]
_0203F582:
	cmp r5, #0xb
	bne _0203F59A
	cmp r4, #0x1
	bne _0203F58E
	mov r4, #0x0
	b _0203F5A4
_0203F58E:
	cmp r4, #0x14
	bne _0203F596
	mov r4, #0x2
	b _0203F5A4
_0203F596:
	mov r4, #0x5
	b _0203F5A4
_0203F59A:
	cmp r5, #0x14
	bne _0203F5A2
	mov r4, #0x1
	b _0203F5A4
_0203F5A2:
	mov r4, #0x3
_0203F5A4:
	mov r5, #0x0
_0203F5A6:
	cmp r5, r4
	beq _0203F5B8
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl FUN_02034C24
_0203F5B8:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x4
	blo _0203F5A6
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_0203F5C8: .word 0x0000010E
_0203F5CC: .word 0x0000010D
_0203F5D0: .word UNK_020F3538

	thumb_func_start ScrCmd_unk_646
ScrCmd_unk_646: ; 0x0203F5D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F720
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_647
ScrCmd_unk_647: ; 0x0203F604
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F740
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_648
ScrCmd_unk_648: ; 0x0203F634
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F760
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_649
ScrCmd_unk_649: ; 0x0203F664
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x0
	add r3, sp, #0x0
	add r0, #0x8
_0203F684:
	ldr r6, [r0, #0x0]
	ldr r1, [r5, #0x8]
	add r6, r6, #0x1
	str r6, [r0, #0x0]
	ldrb r1, [r1, #0x0]
	add r2, r2, #0x1
	strb r1, [r3, #0x0]
	add r3, r3, #0x1
	cmp r2, #0x5
	blt _0203F684
	ldr r1, [r0, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	ldrb r6, [r2, #0x0]
	mov r0, #0x4
	bl FUN_02027E5C
	add r1, sp, #0x0
	add r2, r6, #0x0
	mov r3, #0x0
	add r7, r0, #0x0
	bl FUN_02027F04
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02028048
	add r1, r7, #0x0
	bl FUN_02028094
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl FreeToHeap
	ldr r0, _0203F6E0 ; =0x0000FFFF
	cmp r5, r0
	bne _0203F6D8
	strh r0, [r4, #0x0]
	b _0203F6DA
_0203F6D8:
	strh r6, [r4, #0x0]
_0203F6DA:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0203F6E0: .word 0x0000FFFF

	thumb_func_start ScrCmd_unk_650
ScrCmd_unk_650: ; 0x0203F6E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02028048
	bl FUN_02028074
	ldr r1, _0203F71C ; =0x0000FFFF
	cmp r0, r1
	bne _0203F712
	mov r0, #0x0
	b _0203F714
_0203F712:
	mov r0, #0x1
_0203F714:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203F71C: .word 0x0000FFFF

	thumb_func_start ScrCmd_unk_651
ScrCmd_unk_651: ; 0x0203F720
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	add r5, r0, #0x0
	cmp r4, #0x3
	bls _0203F752
	bl ErrorHandling
_0203F752:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0205F4A0
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_655
ScrCmd_unk_655: ; 0x0203F760
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x20
	ldr r0, [r0, #0xc]
	add r2, sp, #0x0
	bl LoadHallOfFame
	ldr r1, [sp, #0x0]
	add r4, r0, #0x0
	cmp r1, #0x0
	bne _0203F798
	mov r1, #0x0
	strh r1, [r5, #0x0]
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0203F798:
	cmp r1, #0x1
	bne _0203F7AE
	mov r1, #0x0
	bl Sav2_HOF_TranslateRecordIdx
	strh r0, [r5, #0x0]
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0203F7AE:
	cmp r1, #0x2
	bne _0203F7BE
	mov r1, #0x0
	strh r1, [r5, #0x0]
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0203F7BE:
	mov r0, #0x0
	strh r0, [r5, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_656
ScrCmd_unk_656: ; 0x0203F7C8
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r1, r5, #0x0
	add r1, #0x80
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0x20
	add r2, r6, #0x0
	bl FUN_02037A48
	str r0, [r4, #0x0]
	ldr r1, _0203F808 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203F808: .word FUN_0203BC04 

	thumb_func_start ScrCmd_unk_657
ScrCmd_unk_657: ; 0x0203F80C
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203F84C
	bl ErrorHandling
_0203F84C:
	ldr r0, [r4, #0x0]
	bl FUN_02037A40
	strh r0, [r6, #0x0]
	ldrh r0, [r6, #0x0]
	cmp r0, #0x7
	bne _0203F85E
	mov r0, #0xff
	strh r0, [r6, #0x0]
_0203F85E:
	ldr r0, [r4, #0x0]
	bl FUN_02037A70
	strh r0, [r5, #0x0]
	ldrh r0, [r5, #0x0]
	cmp r0, #0x1
	bne _0203F870
	mov r0, #0x1
	b _0203F872
_0203F870:
	mov r0, #0x0
_0203F872:
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_unk_658
ScrCmd_unk_658: ; 0x0203F880
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	cmp r4, #0x64
	bls _0203F8A2
	mov r4, #0x64
_0203F8A2:
	bl LCRandom
	mov r1, #0x65
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	cmp r0, r4
	bgt _0203F8B8
	mov r0, #0x1
	b _0203F8BA
_0203F8B8:
	mov r0, #0x0
_0203F8BA:
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_670
ScrCmd_unk_670: ; 0x0203F8C0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r4, #0x0
	beq _0203F8FC
	cmp r4, #0x1
	beq _0203F906
	cmp r4, #0x2
	beq _0203F910
	b _0203F91A
_0203F8FC:
	mov r2, #0x0
	mov r3, #0x20
	bl MOD06_0224F12C
	b _0203F91E
_0203F906:
	mov r2, #0x1
	mov r3, #0x20
	bl MOD06_0224F12C
	b _0203F91E
_0203F910:
	mov r2, #0x2
	mov r3, #0x20
	bl MOD06_0224F12C
	b _0203F91E
_0203F91A:
	bl ErrorHandling
_0203F91E:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_659
ScrCmd_unk_659: ; 0x0203F924
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F6A8
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_671
ScrCmd_unk_671: ; 0x0203F954
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	cmp r0, #0x0
	bne _0203F978
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl MOD06_02239944
	b _0203F982
_0203F978:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl MOD06_02239AAC
_0203F982:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_675
ScrCmd_unk_675: ; 0x0203F988
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0203384C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_676
ScrCmd_unk_676: ; 0x0203F9B0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020286EC
	bl FUN_02028448
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_674
ScrCmd_unk_674: ; 0x0203F9DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	ldr r1, _0203FA10 ; =0x0000FF79
	add r1, r4, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	cmp r1, #0x1
	bhi _0203FA0C
	bl FUN_02025C30
_0203FA0C:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0203FA10: .word 0x0000FF79

	thumb_func_start ScrCmd_unk_679
ScrCmd_unk_679: ; 0x0203FA14
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	mov r1, #0x0
	strh r1, [r0, #0x0]
	ldr r1, _0203FA54 ; =0x0000012A
	cmp r4, r1
	blo _0203FA4E
	add r1, #0xf
	cmp r4, r1
	bhi _0203FA4E
	mov r1, #0x1
	strh r1, [r0, #0x0]
_0203FA4E:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203FA54: .word 0x0000012A

	thumb_func_start ScrCmd_unk_682
ScrCmd_unk_682: ; 0x0203FA58
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	add r7, r0, #0x0
	mov r0, #0x20
	bl ScrStrBufs_new
	add r4, r0, #0x0
	ldr r2, _0203FB48 ; =0x00000147
	mov r0, #0x0
	mov r1, #0x1a
	mov r3, #0x20
	bl NewMsgDataFromNarc
	add r5, r0, #0x0
	ldr r2, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0200B518
	ldr r2, [sp, #0x8]
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0200B518
	ldr r2, [sp, #0xc]
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0200B518
	add r0, r4, #0x0
	mov r1, #0x3
	add r2, r7, #0x0
	bl FUN_0200B518
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x1
	mov r3, #0x20
	bl ReadMsgData_ExpandPlaceholders
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl NewString_ReadMsgData
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	add r0, r7, #0x0
	bl StringCompare
	cmp r0, #0x0
	bne _0203FB24
	mov r0, #0x1
	b _0203FB26
_0203FB24:
	mov r0, #0x0
_0203FB26:
	strh r0, [r6, #0x0]
	add r0, r7, #0x0
	bl String_dtor
	ldr r0, [sp, #0x0]
	bl String_dtor
	add r0, r5, #0x0
	bl DestroyMsgData
	add r0, r4, #0x0
	bl ScrStrBufs_delete
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_0203FB48: .word 0x00000147

	thumb_func_start ScrCmd_unk_684
ScrCmd_unk_684: ; 0x0203FB4C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl Sav2_SysInfo_get
	mov r1, #0x1
	bl FUN_02023828
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_687
ScrCmd_unk_687: ; 0x0203FB64
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0xf
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_0205296C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_688
ScrCmd_unk_688: ; 0x0203FB94
	push {r3, lr}
	bl FUN_02033E74
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_689
ScrCmd_unk_689: ; 0x0203FBA0
	push {r3, lr}
	bl FUN_02033ED0
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_690
ScrCmd_unk_690: ; 0x0203FBAC
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02034E48
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_693
ScrCmd_unk_693: ; 0x0203FBBC
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r5, #0x80
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034DCC
	str r4, [r0, #0x0]
	str r6, [r0, #0x8]
	mov r1, #0x0
	str r7, [r0, #0xc]
	mvn r1, r1
	str r1, [r0, #0x4]
	mov r1, #0x1
	str r1, [r0, #0x10]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_unk_694
ScrCmd_unk_694: ; 0x0203FC1C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	ldr r2, [r5, #0x8]
	add r1, r0, #0x0
	add r0, r2, #0x1
	str r0, [r5, #0x8]
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldrb r4, [r2, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	add r5, r0, #0x0
	bne _0203FC4C
	bl ErrorHandling
_0203FC4C:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020588B8
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_unk_702
ScrCmd_unk_702: ; 0x0203FC58
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl GetVarPointer
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02065078
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_705
ScrCmd_unk_705: ; 0x0203FC80
	push {r3-r5, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x28
	add r0, r5, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0202280C
	cmp r0, #0x0
	bne _0203FCAA
	add r0, r5, #0x0
	mov r1, #0x4
	mov r2, #0x3
	bl MOD05_021E8588
	str r0, [r4, #0x0]
	bl MOD05_021E84F4
_0203FCAA:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_706
ScrCmd_unk_706: ; 0x0203FCB0
	push {r3-r5, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x28
	add r0, r5, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0202280C
	cmp r0, #0x0
	bne _0203FCD6
	ldr r0, [r4, #0x0]
	bl MOD05_021E856C
	ldr r0, [r4, #0x0]
	bl MOD05_021E85E4
_0203FCD6:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_unk_707
ScrCmd_unk_707: ; 0x0203FCDC
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_0206367C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
