    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0206BB28
FUN_0206BB28: ; 0x0206BB28
	push {r3, lr}
	bl FUN_02024DA0
	bl FUN_0206BB34
	pop {r3, pc}

	thumb_func_start FUN_0206BB34
FUN_0206BB34: ; 0x0206BB34
	push {r3, lr}
	bl Pokedex_GetNatDexFlag
	cmp r0, #0x1
	bne _0206BB42
	mov r0, #0x1
	pop {r3, pc}
_0206BB42:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0206BB48
FUN_0206BB48: ; 0x0206BB48
	push {r3, lr}
	cmp r0, #0x0
	bne _0206BB58
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	bl FUN_02069B40
	add r1, r0, #0x0
_0206BB58:
	add r0, r1, #0x0
	pop {r3, pc}
