    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0204B0F8
FUN_0204B0F8: ; 0x0204B0F8
	push {r4-r5, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02023794
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0204B12A
	add r0, sp, #0xc
	add r1, sp, #0x0
	bl FUN_0201265C
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, sp, #0xc
	bl FUN_0204B130
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, sp, #0xc
	add r3, sp, #0x0
	bl FUN_0204B158
_0204B12A:
	add sp, #0x1c
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_0204B130
FUN_0204B130: ; 0x0204B130
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r0, r2, #0x0
	bl RTC_ConvertDateToDay
	ldr r1, [r5, #0x20]
	add r4, r0, #0x0
	cmp r4, r1
	bhs _0204B148
	str r4, [r5, #0x20]
	pop {r4-r6, pc}
_0204B148:
	cmp r4, r1
	bls _0204B156
	add r0, r6, #0x0
	sub r1, r4, r1
	bl FUN_0204B1DC
	str r4, [r5, #0x20]
_0204B156:
	pop {r4-r6, pc}

	thumb_func_start FUN_0204B158
FUN_0204B158: ; 0x0204B158
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r2, #0x0
	str r0, [sp, #0x0]
	add r6, r3, #0x0
	add r5, r1, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl RTC_ConvertDateTimeToSecond
	str r1, [sp, #0x8]
	add r1, r5, #0x0
	add r7, r0, #0x0
	add r0, r5, #0x4
	add r1, #0x14
	bl RTC_ConvertDateTimeToSecond
	add r2, r1, #0x0
	sub r1, r7, r0
	ldr r1, [sp, #0x8]
	sbc r1, r2
	bge _0204B19C
	add r2, r5, #0x4
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r6!, {r0-r1}
	add r5, #0x14
	stmia r5!, {r0-r1}
	ldr r0, [r6, #0x0]
	add sp, #0xc
	str r0, [r5, #0x0]
	pop {r4-r7, pc}
_0204B19C:
	ldr r1, [sp, #0x8]
	sub r0, r7, r0
	sbc r1, r2
	mov r2, #0x3c
	mov r3, #0x0
	str r1, [sp, #0x8]
	bl _ll_sdiv
	add r7, r0, #0x0
	cmp r7, #0x0
	ble _0204B1D8
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02023884
	ldr r0, [sp, #0x0]
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_0204B270
	add r2, r5, #0x4
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r6!, {r0-r1}
	add r5, #0x14
	stmia r5!, {r0-r1}
	ldr r0, [r6, #0x0]
	str r0, [r5, #0x0]
_0204B1D8:
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0204B1DC
FUN_0204B1DC: ; 0x0204B1DC
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	bl FUN_020377AC
	add r1, r4, #0x0
	bl FUN_02025A60
	add r0, r5, #0x0
	bl FUN_0203959C
	ldr r0, [r5, #0xc]
	add r1, r4, #0x0
	bl FUN_02060344
	ldr r0, [r5, #0xc]
	bl FUN_0202881C
	add r1, r4, #0x0
	bl FUN_02028754
	ldr r0, [r5, #0xc]
	bl FUN_0202A9B0
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0202881C
	bl FUN_020287A4
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0202A988
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	add r1, r4, #0x0
	bl FUN_02069D50
	ldr r0, [r5, #0xc]
	bl FUN_020462AC
	add r6, r0, #0x0
	bl FUN_0205F594
	cmp r0, r4
	ble _0204B244
	sub r0, r0, r4
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	b _0204B246
_0204B244:
	mov r1, #0x0
_0204B246:
	add r0, r6, #0x0
	bl FUN_0205F5A4
	lsl r1, r4, #0x10
	ldr r0, [r5, #0xc]
	lsr r1, r1, #0x10
	bl FUN_0205F618
	ldr r0, [r5, #0xc]
	bl FUN_0205F668
	ldr r0, [r5, #0xc]
	bl FUN_0206007C
	ldr r0, [r5, #0xc]
	bl FUN_02029AFC
	bl FUN_02029C08
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0204B270
FUN_0204B270: ; 0x0204B270
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_0204B3D0
	ldr r0, [r5, #0xc]
	add r1, r4, #0x0
	bl FUN_0202A9D0
	add r0, r5, #0x0
	bl FUN_0204B33C
	add r2, r0, #0x0
	ldr r0, [r5, #0xc]
	add r1, r4, #0x0
	bl FUN_02025B60
	ldr r0, [r5, #0xc]
	bl FUN_02022504
	ldr r2, [r6, #0x4]
	add r1, r4, #0x0
	bl FUN_0202B3C4
	pop {r4-r6, pc}

	thumb_func_start FUN_0204B2A4
FUN_0204B2A4: ; 0x0204B2A4
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02023794
	ldr r0, [r0, #0x14]
	bl FUN_020127A8
	pop {r3, pc}

	thumb_func_start FUN_0204B2B4
FUN_0204B2B4: ; 0x0204B2B4
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02023794
	ldr r0, [r0, #0x8]
	pop {r3, pc}

	thumb_func_start FUN_0204B2C0
FUN_0204B2C0: ; 0x0204B2C0
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02023794
	ldr r0, [r0, #0xc]
	pop {r3, pc}

	thumb_func_start FUN_0204B2CC
FUN_0204B2CC: ; 0x0204B2CC
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02023794
	ldr r0, [r0, #0x10]
	pop {r3, pc}

	thumb_func_start FUN_0204B2D8
FUN_0204B2D8: ; 0x0204B2D8
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02023794
	ldr r0, [r0, #0x14]
	pop {r3, pc}

	thumb_func_start FUN_0204B2E4
FUN_0204B2E4: ; 0x0204B2E4
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02023794
	ldr r0, [r0, #0x18]
	pop {r3, pc}

	thumb_func_start FUN_0204B2F0
FUN_0204B2F0: ; 0x0204B2F0
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02023794
	add r3, r0, #0x0
	ldr r2, [r3, #0x24]
	ldr r3, [r3, #0x28]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl RTC_ConvertSecondToDateTime
	pop {r3-r5, pc}

	thumb_func_start FUN_0204B30C
FUN_0204B30C: ; 0x0204B30C
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02023794
	add r3, r0, #0x0
	ldr r2, [r3, #0x2c]
	ldr r3, [r3, #0x30]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl RTC_ConvertSecondToDateTime
	pop {r3-r5, pc}

	thumb_func_start FUN_0204B328
FUN_0204B328: ; 0x0204B328
	push {r4, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02023794
	add r4, r0, #0x0
	bl FUN_020126FC
	str r0, [r4, #0x2c]
	str r1, [r4, #0x30]
	pop {r4, pc}

	thumb_func_start FUN_0204B33C
FUN_0204B33C: ; 0x0204B33C
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02023794
	bl FUN_02023874
	pop {r3, pc}
	.balign 4
