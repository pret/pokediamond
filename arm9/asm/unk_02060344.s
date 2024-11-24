	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start sub_02060344
sub_02060344: ; 0x02060344
	push {r3-r7, lr}
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	cmp r1, #0x0
	ble _020603AE
	bl sub_02029ABC
	bl sub_02029ACC
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl Save_PlayerData_GetProfile
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r1, #0xa
	add r6, r0, #0x0
	mov r5, #0x0
	mul r6, r1
_0206036A:
	add r0, r7, #0x0
	add r1, r5, #0x0
	bl PlayerProfile_TestBadgeFlag
	cmp r0, #0x0
	beq _020603A4
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_02029AD0
	add r1, r0, #0x0
	cmp r1, #0x0
	ble _0206038C
	cmp r1, #0xc8
	bge _0206038C
	sub r1, r1, r6
	b _02060396
_0206038C:
	cmp r1, #0xc8
	blt _02060394
	bl GF_AssertFail
_02060394:
	mov r1, #0x0
_02060396:
	cmp r1, #0x0
	bge _0206039C
	mov r1, #0x0
_0206039C:
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl sub_02029AD8
_020603A4:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x8
	blo _0206036A
_020603AE:
	pop {r3-r7, pc}
