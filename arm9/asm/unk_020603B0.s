	#include "constants/maps.h"
	#include "constants/roamer.h"
	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F7460
UNK_020F7460: ; 0x020F7460
	.word MAP_ROUTE_201
	.word MAP_ROUTE_202
	.word MAP_ROUTE_203
	.word MAP_ROUTE_204_SOUTH
	.word MAP_ROUTE_204_NORTH
	.word MAP_ROUTE_205_SOUTH
	.word MAP_ROUTE_205_NORTH
	.word MAP_ROUTE_206
	.word MAP_ROUTE_207
	.word MAP_ROUTE_208
	.word MAP_ROUTE_209
	.word MAP_ROUTE_210_SOUTH
	.word MAP_ROUTE_210_NORTH
	.word MAP_ROUTE_211_WEST
	.word MAP_ROUTE_211_EAST
	.word MAP_ROUTE_212_NORTH
	.word MAP_ROUTE_212_SOUTH
	.word MAP_ROUTE_213
	.word MAP_ROUTE_214
	.word MAP_ROUTE_215
	.word MAP_ROUTE_216
	.word MAP_ROUTE_217
	.word MAP_ROUTE_218
	.word MAP_ROUTE_219
	.word MAP_ROUTE_220
	.word MAP_ROUTE_221
	.word MAP_ROUTE_222
	.word MAP_VALLEY_WINDWORKS_EXTERIOR
	.word MAP_FUEGO_IRONWORKS_EXTERIOR

	.global UNK_020F74D4
UNK_020F74D4: ; 0x020F74D4
	.short 2, ROAMER_LOC_R202, ROAMER_LOC_R219, 0xFFFF, 0xFFFF, 0xFFFF
	.short 5, ROAMER_LOC_R201, ROAMER_LOC_R203, ROAMER_LOC_R204A, ROAMER_LOC_R218, ROAMER_LOC_R219
	.short 4, ROAMER_LOC_R202, ROAMER_LOC_R204A, ROAMER_LOC_R207, ROAMER_LOC_R218, 0xFFFF
	.short 4, ROAMER_LOC_R202, ROAMER_LOC_R203, ROAMER_LOC_R204B, ROAMER_LOC_R218, 0xFFFF
	.short 2, ROAMER_LOC_R204A, ROAMER_LOC_R205A, 0xFFFF, 0xFFFF, 0xFFFF
	.short 4, ROAMER_LOC_R204B, ROAMER_LOC_R205B, ROAMER_LOC_D02, ROAMER_LOC_D04, 0xFFFF
	.short 3, ROAMER_LOC_R205A, ROAMER_LOC_R206, ROAMER_LOC_R208, 0xFFFF, 0xFFFF
	.short 3, ROAMER_LOC_R205B, ROAMER_LOC_R207, ROAMER_LOC_R211A, 0xFFFF, 0xFFFF
	.short 3, ROAMER_LOC_R203, ROAMER_LOC_R206, ROAMER_LOC_R208, 0xFFFF, 0xFFFF
	.short 3, ROAMER_LOC_R207, ROAMER_LOC_R209, ROAMER_LOC_R212A, 0xFFFF, 0xFFFF
	.short 3, ROAMER_LOC_R208, ROAMER_LOC_R210A, ROAMER_LOC_R212A, 0xFFFF, 0xFFFF
	.short 3, ROAMER_LOC_R209, ROAMER_LOC_R210B, ROAMER_LOC_R215, 0xFFFF, 0xFFFF
	.short 2, ROAMER_LOC_R210A, ROAMER_LOC_R211B, 0xFFFF, 0xFFFF, 0xFFFF
	.short 4, ROAMER_LOC_R205B, ROAMER_LOC_R206, ROAMER_LOC_R211B, ROAMER_LOC_R216, 0xFFFF
	.short 3, ROAMER_LOC_R210B, ROAMER_LOC_R211A, ROAMER_LOC_R216, 0xFFFF, ROAMER_LOC_R201
	.short 3, ROAMER_LOC_R208, ROAMER_LOC_R209, ROAMER_LOC_R212B, 0xFFFF, 0xFFFF
	.short 2, ROAMER_LOC_R212A, ROAMER_LOC_R213, 0xFFFF, 0xFFFF, 0xFFFF
	.short 3, ROAMER_LOC_R212B, ROAMER_LOC_R214, ROAMER_LOC_R222, 0xFFFF, 0xFFFF
	.short 3, ROAMER_LOC_R213, ROAMER_LOC_R215, ROAMER_LOC_R222, 0xFFFF, 0xFFFF
	.short 2, ROAMER_LOC_R210A, ROAMER_LOC_R214, 0xFFFF, 0xFFFF, 0xFFFF
	.short 3, ROAMER_LOC_R211A, ROAMER_LOC_R211B, ROAMER_LOC_R217, 0xFFFF, 0xFFFF
	.short 1, ROAMER_LOC_R216, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
	.short 3, ROAMER_LOC_R202, ROAMER_LOC_R203, ROAMER_LOC_R204A, 0xFFFF, 0xFFFF
	.short 3, ROAMER_LOC_R201, ROAMER_LOC_R202, ROAMER_LOC_W220, 0xFFFF, 0xFFFF
	.short 2, ROAMER_LOC_R219, ROAMER_LOC_R221, 0xFFFF, 0xFFFF, 0xFFFF
	.short 1, ROAMER_LOC_W220, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
	.short 2, ROAMER_LOC_R213, ROAMER_LOC_R214, 0xFFFF, 0xFFFF, 0xFFFF
	.short 1, ROAMER_LOC_R205A, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
	.short 1, ROAMER_LOC_R205A, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF

	.text

	thumb_func_start sub_020603B0
sub_020603B0: ; 0x020603B0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl sub_0202AA38
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_02060588
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_020603C8
sub_020603C8: ; 0x020603C8
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r5, #0x0
_020603CE:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl sub_0202AA74
	cmp r0, #0x0
	beq _020603E2
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl sub_020603B0
_020603E2:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x3
	blo _020603CE
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_020603F0
sub_020603F0: ; 0x020603F0
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r4, #0x0
_020603F6:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0202AA74
	cmp r0, #0x0
	beq _02060430
	bl LCRandom
	lsl r0, r0, #0x4
	lsr r6, r0, #0x10
	cmp r6, #0x10
	blo _02060412
	bl GF_AssertFail
_02060412:
	cmp r6, #0x0
	bne _02060420
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_020603B0
	b _02060430
_02060420:
	add r0, r5, #0x0
	bl sub_0202AA38
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_020605D8
_02060430:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x3
	blo _020603F6
	pop {r4-r6, pc}

	thumb_func_start sub_0206043C
sub_0206043C: ; 0x0206043C
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x1d
	blo _02060448
	bl GF_AssertFail
_02060448:
	ldr r0, _02060450 ; =UNK_020F7460
	lsl r1, r4, #0x2
	ldr r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_02060450: .word UNK_020F7460

	thumb_func_start sub_02060454
sub_02060454: ; 0x02060454
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r5, #0x0
_0206045A:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl sub_0202AA74
	cmp r0, #0x0
	beq _0206046A
	mov r0, #0x1
	pop {r3-r5, pc}
_0206046A:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x3
	blo _0206045A
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start sub_02060478
sub_02060478: ; 0x02060478
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl sub_02060454
	cmp r0, #0x0
	beq _0206048E
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0202AA20
_0206048E:
	pop {r3-r5, pc}

	thumb_func_start Save_CreateRoamerByID
Save_CreateRoamerByID: ; 0x02060490
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r1, #0x0
	str r0, [sp, #0x10]
	bl Save_Roamers_Get
	add r1, r5, #0x0
	str r0, [sp, #0x14]
	bl sub_0202AAA0
	add r4, r0, #0x0
	cmp r5, #0x0
	beq _020604B4
	cmp r5, #0x1
	beq _020604BA
	cmp r5, #0x2
	beq _020604C2
	b _020604C8
_020604B4:
	ldr r7, _02060580 ; =0x000001E1
	mov r6, #0x32
	b _020604D0
_020604BA:
	mov r7, #0x7a
	lsl r7, r7, #0x2
	mov r6, #0x32
	b _020604D0
_020604C2:
	ldr r7, _02060584 ; =0x000001EB
	mov r6, #0x28
	b _020604D0
_020604C8:
	bl GF_AssertFail
	add sp, #0x20
	pop {r3-r7, pc}
_020604D0:
	add r0, r4, #0x0
	mov r1, #0x4
	add r2, r7, #0x0
	bl sub_0202AAFC
	add r0, r4, #0x0
	mov r1, #0x6
	add r2, r6, #0x0
	bl sub_0202AAFC
	ldr r0, [sp, #0x10]
	bl Save_PlayerData_GetProfile
	str r0, [sp, #0x18]
	mov r0, #0x4
	bl AllocMonZeroed
	str r0, [sp, #0x1c]
	bl ZeroMonData
	ldr r0, [sp, #0x18]
	bl PlayerProfile_GetTrainerID_VisibleHalf
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	mov r1, #0x1
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x1c]
	add r1, r7, #0x0
	add r2, r6, #0x0
	mov r3, #0x20
	bl CreateMon
	add r0, r4, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl sub_0202AAFC
	add r0, r4, #0x0
	mov r1, #0x8
	mov r2, #0x1
	bl sub_0202AAFC
	ldr r0, [sp, #0x1c]
	mov r1, #0xae
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x2
	bl sub_0202AAFC
	mov r1, #0x0
	ldr r0, [sp, #0x1c]
	add r2, r1, #0x0
	bl GetMonData
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x3
	bl sub_0202AAFC
	ldr r0, [sp, #0x1c]
	mov r1, #0xa3
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x5
	bl sub_0202AAFC
	ldr r0, [sp, #0x1c]
	bl FreeToHeap
	ldr r0, [sp, #0x14]
	bl sub_0202AA38
	add r2, r0, #0x0
	ldr r0, [sp, #0x14]
	add r1, r5, #0x0
	bl sub_02060588
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4
_02060580: .word 0x000001E1
_02060584: .word 0x000001EB

	thumb_func_start sub_02060588
sub_02060588: ; 0x02060588
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	add r6, r2, #0x0
	bl sub_0202AA40
	ldr r7, _020605D0 ; =UNK_020F7460
	lsl r0, r0, #0x2
	ldr r4, [r7, r0]
_0206059C:
	bl LCRandom
	ldr r1, _020605D4 ; =0x000008D4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x1d
	blo _020605B2
	bl GF_AssertFail
_020605B2:
	lsl r0, r5, #0x18
	lsr r2, r0, #0x18
	lsl r0, r2, #0x2
	ldr r3, [r7, r0]
	cmp r3, r6
	beq _0206059C
	cmp r3, r4
	beq _0206059C
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	bl sub_02060688
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_020605D0: .word UNK_020F7460
_020605D4: .word 0x000008D4

	thumb_func_start sub_020605D8
sub_020605D8: ; 0x020605D8
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	add r7, r2, #0x0
	bl sub_0202AA40
	mov r1, #0xc
	ldr r2, _0206067C ; =UNK_020F74D4
	mul r1, r0
	ldrh r0, [r2, r1]
	add r4, r2, r1
	cmp r0, #0x1
	bne _0206061E
	ldrh r0, [r4, #0x2]
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	ldr r0, _02060680 ; =UNK_020F7460
	lsl r1, r2, #0x2
	ldr r3, [r0, r1]
	cmp r3, r7
	bne _02060612
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r2, r7, #0x0
	bl sub_02060588
	add sp, #0x8
	pop {r3-r7, pc}
_02060612:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	bl sub_02060688
	add sp, #0x8
	pop {r3-r7, pc}
_0206061E:
	ldrh r5, [r4, #0x0]
	cmp r5, #0x0
	bne _02060628
	bl GF_AssertFail
_02060628:
	cmp r5, #0x1
	bhi _02060630
	mov r6, #0x0
	b _02060658
_02060630:
	bl LCRandom
	add r6, r0, #0x0
	ldr r0, _02060684 ; =0x0000FFFF
	add r1, r5, #0x0
	bl _s32_div_f
	add r1, r0, #0x0
	add r1, r1, #0x1
	lsl r1, r1, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, r5
	blo _02060658
	bl GF_AssertFail
_02060658:
	lsl r0, r6, #0x18
	lsr r0, r0, #0x17
	add r0, r4, r0
	ldrh r0, [r0, #0x2]
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	ldr r0, _02060680 ; =UNK_020F7460
	lsl r1, r2, #0x2
	ldr r3, [r0, r1]
	cmp r3, r7
	beq _0206061E
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	bl sub_02060688
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0206067C: .word UNK_020F74D4
_02060680: .word UNK_020F7460
_02060684: .word 0x0000FFFF

	thumb_func_start sub_02060688
sub_02060688: ; 0x02060688
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl sub_0202AAA0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl sub_0202AA58
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	add r2, r7, #0x0
	bl sub_0202AAFC
	pop {r3-r7, pc}
	.balign 4
