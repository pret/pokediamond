	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0202376C
FUN_0202376C: ; 0x0202376C
	mov r0, #0x5c
	bx lr

	thumb_func_start FUN_02023770
FUN_02023770: ; 0x02023770
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r4, #0x0
	mov r2, #0x5c
	bl MIi_CpuClearFast
	add r4, #0x10
	add r0, r4, #0x0
	bl FUN_02023840
	pop {r4, pc}

	thumb_func_start FUN_02023788
FUN_02023788: ; 0x02023788
	ldr r3, _02023790 ; =FUN_02022610
	mov r1, #0x0
	bx r3
	nop
_02023790: .word FUN_02022610

	thumb_func_start FUN_02023794
FUN_02023794: ; 0x02023794
	push {r3, lr}
	bl FUN_02023788
	add r0, #0x10
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020237A0
FUN_020237A0: ; 0x020237A0
	push {r4, lr}
	sub sp, #0x50
	add r4, r0, #0x0
	bl OS_GetOwnerRtcOffset
	str r0, [r4, #0x0]
	add r0, r4, #0x0
	add r0, #0x8
	str r1, [r4, #0x4]
	bl OS_GetMacAddress
	add r0, sp, #0x0
	bl OS_GetOwnerInfo
	add r0, sp, #0x0
	ldrb r1, [r0, #0x2]
	strb r1, [r4, #0xe]
	ldrb r0, [r0, #0x3]
	strb r0, [r4, #0xf]
	add sp, #0x50
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020237CC
FUN_020237CC: ; 0x020237CC
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl OS_GetMacAddress
	mov r2, #0x0
	add r3, sp, #0x0
_020237DC:
	add r0, r4, r2
	ldrb r1, [r3, #0x0]
	ldrb r0, [r0, #0x8]
	cmp r1, r0
	beq _020237EC
	add sp, #0x8
	mov r0, #0x0
	pop {r4, pc}
_020237EC:
	add r2, r2, #0x1
	add r3, r3, #0x1
	cmp r2, #0x6
	blt _020237DC
	mov r0, #0x1
	add sp, #0x8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020237FC
FUN_020237FC: ; 0x020237FC
	push {r4, lr}
	add r4, r0, #0x0
	bl OS_GetOwnerRtcOffset
	ldr r3, [r4, #0x0]
	ldr r2, [r4, #0x4]
	eor r0, r3
	eor r1, r2
	orr r0, r1
	bne _02023814
	mov r0, #0x1
	pop {r4, pc}
_02023814:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02023818
FUN_02023818: ; 0x02023818
	ldrb r0, [r0, #0xe]
	bx lr

	thumb_func_start FUN_0202381C
FUN_0202381C: ; 0x0202381C
	ldrb r0, [r0, #0xf]
	bx lr

	thumb_func_start FUN_02023820
FUN_02023820: ; 0x02023820
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02023828
FUN_02023828: ; 0x02023828
	add r0, #0x48
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02023830
FUN_02023830: ; 0x02023830
	ldr r0, [r0, #0x4c]
	bx lr

	thumb_func_start FUN_02023834
FUN_02023834: ; 0x02023834
	ldr r2, [r0, #0x4c]
	cmp r2, #0x0
	bne _0202383C
	str r1, [r0, #0x4c]
_0202383C:
	bx lr
	.balign 4

	thumb_func_start FUN_02023840
FUN_02023840: ; 0x02023840
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x1
	add r1, r4, #0x0
	str r0, [r4, #0x0]
	add r0, r4, #0x4
	add r1, #0x14
	bl FUN_0201265C
	add r0, r4, #0x4
	bl RTC_ConvertDateToDay
	add r1, r4, #0x0
	str r0, [r4, #0x20]
	add r0, r4, #0x4
	add r1, #0x14
	bl RTC_ConvertDateTimeToSecond
	str r0, [r4, #0x24]
	str r1, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	str r0, [r4, #0x30]
	str r0, [r4, #0x34]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02023874
FUN_02023874: ; 0x02023874
	ldr r0, [r0, #0x34]
	cmp r0, #0x0
	beq _0202387E
	mov r0, #0x1
	bx lr
_0202387E:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02023884
FUN_02023884: ; 0x02023884
	mov r2, #0x5a
	ldr r3, [r0, #0x34]
	lsl r2, r2, #0x4
	cmp r3, r2
	bls _02023890
	str r2, [r0, #0x34]
_02023890:
	ldr r2, [r0, #0x34]
	cmp r2, r1
	bhs _0202389C
	mov r1, #0x0
	str r1, [r0, #0x34]
	bx lr
_0202389C:
	sub r1, r2, r1
	str r1, [r0, #0x34]
	bx lr
	.balign 4

	thumb_func_start FUN_020238A4
FUN_020238A4: ; 0x020238A4
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x5a
	lsl r0, r0, #0x4
	add r1, r4, #0x0
	str r0, [r4, #0x34]
	add r0, r4, #0x4
	add r1, #0x14
	bl FUN_0201265C
	add r0, r4, #0x4
	bl RTC_ConvertDateToDay
	str r0, [r4, #0x20]
	pop {r4, pc}
	.balign 4
