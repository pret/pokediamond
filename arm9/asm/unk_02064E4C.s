    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02064E4C
FUN_02064E4C: ; 0x02064E4C
	push {r4, lr}
	add r4, r2, #0x0
	bl ReadMsgDataIntoString
	mov r0, #0x0
	add r1, r4, #0x0
	add r2, r0, #0x0
	bl FUN_02002E14
	pop {r4, pc}

	thumb_func_start FUN_02064E60
FUN_02064E60: ; 0x02064E60
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r3, r1, #0x0
	ldr r2, _02064E8C ; =0x0000017E
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02034824
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02064E4C
	add r0, r4, #0x0
	bl DestroyMsgData
	pop {r4-r6, pc}
	.balign 4
_02064E8C: .word 0x0000017E
