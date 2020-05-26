	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020FF578
UNK_020FF578: ; 0x020FF578
	.byte 0x01, 0x02, 0x00, 0x04, 0x03, 0x05, 0x06, 0x07

	.global UNK_020FF580
UNK_020FF580: ; 0x020FF580
	.byte 0x05, 0x09, 0x01, 0x0E, 0x0C, 0x02, 0x0A, 0x00, 0x0B, 0x0D, 0x03, 0x04, 0x08, 0x06, 0x0F, 0x07

	.text

	arm_func_start DWC_Auth_CheckWiFiIDNeedCreate
DWC_Auth_CheckWiFiIDNeedCreate:
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	add r0, sp, #0x0
	bl DWCi_BM_GetWiFiInfo
	ldr r2, [sp, #0x8]
	ldr r1, [sp, #0xc]
	mov r0, #0x0
	cmp r1, r0
	cmpeq r2, r0
	bne _0209650C
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	cmp r1, r0
	cmpeq r2, r0
	addeq sp, sp, #0x14
	moveq r0, #0x1
	ldmeqia sp!, {pc}
_0209650C:
	mov r0, #0x0
	add sp, sp, #0x14
	ldmia sp!, {pc}

	arm_func_start DWC_Auth_GetId
DWC_Auth_GetId: ; 0x02096518
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x18
	mov r4, r0
	add r0, sp, #0x0
	bl DWCi_BM_GetWiFiInfo
	add r0, sp, #0x0
	ldmia r0, {r2-r3}
	stmia r4, {r2-r3}
	add r1, sp, #0x8
	add r0, r4, #0x8
	ldmia r1, {r2-r3}
	stmia r0, {r2-r3}
	ldr r2, [sp, #0x0]
	ldr r1, [sp, #0x4]
	mov r0, #0x0
	cmp r1, r0
	cmpeq r2, r0
	streq r0, [r4, #0x10]
	movne r0, #0x1
	strne r0, [r4, #0x10]
	add sp, sp, #0x18
	ldmia sp!, {r4,pc}

	arm_func_start FUN_02096570
FUN_02096570: ; 0x02096570
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x28
	add r2, sp, #0x0
	mov r1, #0x0
	strb r1, [r2, #0x0]
	strb r1, [r2, #0x1]
	strb r1, [r2, #0x2]
	strb r1, [r2, #0x3]
	strb r1, [r2, #0x4]
	mov r5, r0
	strb r1, [r2, #0x5]
	bl DWCi_BM_GetWiFiInfo
	bl RTC_Init
	add r0, sp, #0x8
	bl RTC_GetDate
	cmp r0, #0x0
	addne sp, sp, #0x28
	movne r0, #0x0
	ldmneia sp!, {r4-r10,pc}
	add r0, sp, #0x18
	bl RTC_GetTime
	cmp r0, #0x0
	addne sp, sp, #0x28
	movne r0, #0x0
	ldmneia sp!, {r4-r10,pc}
	add r0, sp, #0x8
	add r1, sp, #0x18
	bl RTC_ConvertDateTimeToSecond
	mov r4, r0
	mov r0, #0x0
	subs r2, r4, r0
	sbcs r2, r1, r0
	addlt sp, sp, #0x28
	ldmltia sp!, {r4-r10,pc}
	bl OS_IsTickAvailable
	cmp r0, #0x0
	beq _0209660C
	ldr r0, _02096700 ; =OS_GetTick
	adds r4, r4, r0
_0209660C:
	add r0, sp, #0x0
	bl OS_GetMacAddress
	ldrb r1, [sp, #0x0]
	ldr r6, _02096704 ; =0x5D588B65
	ldr r7, _02096708 ; =0x00269EC3
	ldrb r0, [sp, #0x1]
	mla r9, r4, r6, r7
	mov r1, r1, lsl #0x10
	orr r1, r1, r0, lsl #0x8
	ldrb r2, [sp, #0x2]
	ldr r0, _0209670C ; =0x000009BF
	ldrb r8, [sp, #0x3]
	orr r1, r2, r1
	cmp r1, r0
	movne r1, #0x1
	mov r2, r9, lsr #0x10
	mov r0, #0x3e8
	mul r3, r2, r0
	mov r2, r3, lsr #0x10
	mov r3, r8, lsl #0x10
	ldrb r4, [sp, #0x4]
	ldrb r0, [sp, #0x5]
	mov r8, #0x0
	orr r10, r3, r4, lsl #0x8
	strh r2, [r5, #0x10]
	str r8, [r5, #0x8]
	str r8, [r5, #0xc]
	moveq r1, #0x0
	ldr r2, [r5, #0xc]
	ldr r3, [r5, #0x8]
	cmp r2, r8
	cmpeq r3, r8
	and r4, r1, #0xff
	orr r10, r0, r10
	bne _020966F4
_02096698:
	mla r9, r6, r9, r7
	b _020966A4
_020966A0:
	mla r9, r6, r9, r7
_020966A4:
	cmp r9, #0x0
	beq _020966A0
	ldrh r1, [r5, #0x12]
	mov r0, r9, lsl #0x10
	mov r0, r0, lsr #0x10
	cmp r1, r0
	beq _020966A0
	strh r0, [r5, #0x12]
	ldrh r0, [r5, #0x12]
	mov r1, r10
	mov r2, r4
	mov r3, r8
	bl FUN_02096988
	str r0, [r5, #0x8]
	str r1, [r5, #0xc]
	ldr r0, [r5, #0xc]
	ldr r1, [r5, #0x8]
	cmp r0, r8
	cmpeq r1, r8
	beq _02096698
_020966F4:
	mov r0, #0x1
	add sp, sp, #0x28
	ldmia sp!, {r4-r10,pc}
	.balign 4
_02096700: .word OS_GetTick
_02096704: .word 0x5D588B65
_02096708: .word 0x00269EC3
_0209670C: .word 0x000009BF

	arm_func_start FUN_02096710
FUN_02096710: ; 0x02096710
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x14
	mov r5, r0
	add r0, sp, #0x0
	mov r4, r1
	bl DWCi_BM_GetWiFiInfo
	add r12, r5, #0x8
	ldmia r12, {r2-r3}
	stmia r5, {r2-r3}
	add r1, sp, #0x8
	ldmia r1, {r2-r3}
	mov r0, r5
	mov r1, r4
	stmia r12, {r2-r3}
	bl DWCi_BM_SetWiFiInfo
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x14
	ldmia sp!, {r4-r5,pc}

	arm_func_start DWCi_AUTH_MakeWiFiID
DWCi_AUTH_MakeWiFiID: ; 0x02096760
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x18
	mov r4, r0
	add r0, sp, #0x0
	bl DWCi_AUTH_GetNewWiFiInfo
	cmp r0, #0x0
	addeq sp, sp, #0x18
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	add r0, sp, #0x0
	mov r1, r4
	bl DWCi_BM_SetWiFiInfo
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x18
	ldmia sp!, {r4,pc}

	arm_func_start DWCi_AUTH_GetNewWiFiInfo
DWCi_AUTH_GetNewWiFiInfo:
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x28
	mov r8, r0
	bl DWCi_BM_GetWiFiInfo
	bl RTC_Init
	add r0, sp, #0x8
	bl RTC_GetDate
	cmp r0, #0x0
	addne sp, sp, #0x28
	movne r0, #0x0
	ldmneia sp!, {r4-r10,pc}
	add r0, sp, #0x18
	bl RTC_GetTime
	cmp r0, #0x0
	addne sp, sp, #0x28
	movne r0, #0x0
	ldmneia sp!, {r4-r10,pc}
	add r0, sp, #0x8
	add r1, sp, #0x18
	bl RTC_ConvertDateTimeToSecond
	mov r4, r0
	mov r0, #0x0
	subs r2, r4, r0
	sbcs r2, r1, r0
	addlt sp, sp, #0x28
	ldmltia sp!, {r4-r10,pc}
	bl OS_IsTickAvailable
	cmp r0, #0x0
	beq _02096820
	ldr r0, _02096978 ; =OS_GetTick
	adds r4, r4, r0
_02096820:
	add r0, sp, #0x0
	bl OS_GetMacAddress
	ldrb r1, [sp, #0x0]
	ldr sb, _0209697C ; =0x5D588B65
	ldr sl, _02096980 ; =0x00269EC3
	ldrb r0, [sp, #0x1]
	mla r5, r4, r9, r10
	mov r1, r1, lsl #0x10
	orr r1, r1, r0, lsl #0x8
	ldrb r2, [sp, #0x2]
	ldr r0, _02096984 ; =0x000009BF
	ldrb r6, [sp, #0x3]
	orr r1, r2, r1
	cmp r1, r0
	movne r1, #0x1
	moveq r1, #0x0
	mov r2, r5, lsr #0x10
	mov r0, #0x3e8
	mul r3, r2, r0
	mov r2, r3, lsr #0x10
	ldrb r0, [sp, #0x5]
	ldrb r4, [sp, #0x4]
	mov r3, r6, lsl #0x10
	and r7, r1, #0xff
	orr r3, r3, r4, lsl #0x8
	strh r2, [r8, #0x10]
	mov r4, #0x0
	str r4, [r8, #0x0]
	str r4, [r8, #0x4]
	ldrh r2, [r8, #0x12]
	orr r6, r0, r3
	cmp r2, #0x0
	bne _02096910
	str r4, [r8, #0x8]
	str r4, [r8, #0xc]
	ldr r0, [r8, #0xc]
	ldr r1, [r8, #0x8]
	cmp r0, r4
	cmpeq r1, r4
	bne _0209696C
_020968C0:
	mul r0, r5, r9
	adds r5, r0, r10
	bne _020968D8
_020968CC:
	mul r0, r5, r9
	adds r5, r0, r10
	beq _020968CC
_020968D8:
	strh r5, [r8, #0x12]
	ldrh r0, [r8, #0x12]
	mov r1, r6
	mov r2, r7
	mov r3, r4
	bl FUN_02096988
	str r0, [r8, #0x8]
	str r1, [r8, #0xc]
	ldr r0, [r8, #0xc]
	ldr r1, [r8, #0x8]
	cmp r0, r4
	cmpeq r1, #0x0
	beq _020968C0
	b _0209696C
_02096910:
	str r4, [r8, #0x8]
	str r4, [r8, #0xc]
	ldr r0, [r8, #0xc]
	ldr r1, [r8, #0x8]
	cmp r0, r4
	cmpeq r1, r4
	bne _0209696C
	add r5, r8, #0x12
_02096930:
	ldrh r0, [r5, #0x0]
	mov r1, r6
	mov r2, r7
	add r0, r0, #0x1
	strh r0, [r5, #0x0]
	ldrh r0, [r8, #0x12]
	mov r3, r4
	bl FUN_02096988
	str r0, [r8, #0x8]
	str r1, [r8, #0xc]
	ldr r0, [r8, #0xc]
	ldr r1, [r8, #0x8]
	cmp r0, r4
	cmpeq r1, r4
	beq _02096930
_0209696C:
	mov r0, #0x1
	add sp, sp, #0x28
	ldmia sp!, {r4-r10,pc}
	.balign 4
_02096978: .word OS_GetTick
_0209697C: .word 0x5D588B65
_02096980: .word 0x00269EC3
_02096984: .word 0x000009BF

	arm_func_start FUN_02096988
FUN_02096988: ; 0x02096988
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov lr, #0x0
	and r12, lr, #0x0
	mvn r5, #0xff000000
	ldr r4, _02096B08 ; =0x0000FFFF
	and r2, r2, #0x1
	mov r6, r12, lsl #0x2
	and r3, r3, #0x3
	and r5, r1, r5
	orr r1, r3, r2, lsl #0x2
	orr r6, r6, r2, lsr #0x1e
	mov r7, r12, lsl #0x3
	and r2, r0, r4
	orr r0, r1, r5, lsl #0x3
	orr r1, r0, r2, lsl #0x1b
	mov r3, r12, lsl #0x1b
	orr r3, r3, r2, lsr #0x5
	orr r7, r7, r5, lsr #0x1d
	orr r0, r12, r6
	orr r0, r7, r0
	orr r0, r3, r0
	add r2, sp, #0x0
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
_020969EC:
	ldrb r0, [r2, #0x0]
	add lr, lr, #0x1
	cmp lr, #0x6
	eor r0, r0, #0xd6
	strb r0, [r2], #0x1
	blt _020969EC
	ldr r2, _02096B0C ; =UNK_020FF580
	add r5, sp, #0x0
	mov r4, #0x0
_02096A10:
	ldrb r3, [r5, #0x0]
	add r4, r4, #0x1
	cmp r4, #0x5
	mov r0, r3, asr #0x4
	and r1, r0, #0xf
	and r0, r3, #0xf
	ldrb r1, [r2, r1]
	ldrb r0, [r2, r0]
	orr r0, r0, r1, lsl #0x4
	strb r0, [r5], #0x1
	blt _02096A10
	add r0, sp, #0x0
	add r1, sp, #0x8
	mov r2, #0x8
	bl MI_CpuCopy8
	ldr r4, _02096B10 ; =UNK_020FF578
	add r5, sp, #0x8
	mov r3, #0x0
	add r1, sp, #0x0
_02096A5C:
	ldrb r2, [r5, #0x0]
	ldrb r0, [r4, #0x0]
	add r3, r3, #0x1
	cmp r3, #0x5
	strb r2, [r1, r0]
	add r5, r5, #0x1
	add r4, r4, #0x1
	blt _02096A5C
	ldrb r2, [sp, #0x5]
	mov r0, #0x0
	ldr r3, [sp, #0x0]
	and r2, r2, #0x7
	strb r0, [sp, #0x7]
	strb r0, [sp, #0x6]
	strb r2, [sp, #0x5]
	ldr r2, [sp, #0x4]
	mov r4, r3, lsl #0x1
	mov r2, r2, lsl #0x1
	orr r2, r2, r3, lsr #0x1f
	str r2, [sp, #0x4]
	ldrb r2, [sp, #0x5]
	str r4, [sp, #0x0]
	ldrb r3, [sp, #0x0]
	mov r2, r2, asr #0x3
	and r2, r2, #0x1
	orr r2, r3, r2
	strb r2, [sp, #0x0]
_02096AC8:
	ldrb r2, [r1, #0x0]
	add r0, r0, #0x1
	cmp r0, #0x6
	eor r2, r2, #0x67
	strb r2, [r1], #0x1
	blt _02096AC8
	ldrb r0, [sp, #0x5]
	mov r1, #0x0
	strb r1, [sp, #0x7]
	and r0, r0, #0x7
	strb r1, [sp, #0x6]
	strb r0, [sp, #0x5]
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,pc}
	.balign 4
_02096B08: .word 0x0000FFFF
_02096B0C: .word UNK_020FF580
_02096B10: .word UNK_020FF578
