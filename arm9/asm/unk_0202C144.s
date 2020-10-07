	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0202C144
FUN_0202C144: ; 0x0202C144
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _0202C194
	add r0, r5, #0x0
	bl Sav2_Pokedex_get
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02029FC8
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	lsl r2, r2, #0x10
	add r0, r7, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x10
	bl FUN_0202A1C4
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl Pokedex_SetMonCaughtFlag
	add r0, r5, #0x0
	bl Sav2_Poketch_get
	add r1, r4, #0x0
	bl Sav2_Poketch_PokemonHistoryAddMon
_0202C194:
	pop {r3-r7, pc}
	.balign 4
