    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0206439C
FUN_0206439C: ; 0x0206439C
	push {r4-r6, lr}
	add r5, r1, #0x0
	add r6, r2, #0x0
	mov r1, #0x8
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl SavArray_PlayerParty_get
	add r1, r5, #0x0
	bl GetPartyMonByIndex
	str r0, [r4, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x4]
	add r0, r4, #0x0
	pop {r4-r6, pc}
