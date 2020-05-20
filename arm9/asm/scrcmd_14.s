    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02043A44
FUN_02043A44: ; 0x02043A44
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
	add r0, r5, #0x0
	mov r1, #0x26
	bl FUN_02039438
	lsl r1, r6, #0x18
	lsl r2, r7, #0x18
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl MOD05_021E2950
	str r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02043A94
FUN_02043A94: ; 0x02043A94
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x26
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl MOD05_021E29B4
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02043AAC
FUN_02043AAC: ; 0x02043AAC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x26
	bl FUN_02039438
	add r1, r0, #0x0
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r1, [r1, #0x0]
	bl MOD05_021E29C8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02043ACC
FUN_02043ACC: ; 0x02043ACC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202390C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02028930
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02043AFC
FUN_02043AFC: ; 0x02043AFC
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202390C
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02028934
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02043B28
FUN_02043B28: ; 0x02043B28
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202390C
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0202896C
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02043B54
FUN_02043B54: ; 0x02043B54
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202390C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r1, r0, #0x0
	ldrh r1, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_0202896C
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02043B84
FUN_02043B84: ; 0x02043B84
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	add r0, r5, #0x0
	bl FUN_020377AC
	bl FUN_020238F4
	ldr r0, [r5, #0xc]
	bl FUN_0202390C
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadWord
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02028930
	cmp r0, r4
	bhs _02043BC8
	mov r0, #0x0
	b _02043BCA
_02043BC8:
	mov r0, #0x1
_02043BCA:
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02043BD0
FUN_02043BD0: ; 0x02043BD0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_020377AC
	bl FUN_020238F4
	ldr r0, [r4, #0xc]
	bl FUN_0202390C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	ldrh r5, [r0, #0x0]
	add r0, r6, #0x0
	bl FUN_02028930
	cmp r0, r5
	bhs _02043C1E
	mov r0, #0x0
	b _02043C20
_02043C1E:
	mov r0, #0x1
_02043C20:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02043C28
FUN_02043C28: ; 0x02043C28
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202390C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02028954
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
