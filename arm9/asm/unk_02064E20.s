	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start FUN_02064E20
FUN_02064E20: ; 0x02064E20
	push {r4, lr}
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02024ED8
	add r4, r0, #0x0
	bl FUN_020254B4
	cmp r0, #0x6
	beq _02064E48
	add r0, r4, #0x0
	mov r1, #0x6
	bl FUN_02025490
	add r0, r4, #0x0
	mov r1, #0x6
	bl FUN_020254A0
	mov r1, #0x2
	strh r1, [r0, #0x0]
_02064E48:
	pop {r4, pc}
	.balign 4
