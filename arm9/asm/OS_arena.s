    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_AllocFromArenaHi
OS_AllocFromArenaHi: ; 0x020CC204
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	mov r6, r1
	mov r5, r2
	bl OS_GetArenaHi
_020CC218:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	sub r1, r5, #0x1
	mvn r2, r1
	and r0, r0, r2
	sub r1, r0, r6
	mov r0, r4
	and r5, r1, r2
	bl OS_GetArenaLo
	cmp r5, r0
	movcc r0, #0x0
	ldmccia sp!, {r4-r6, lr}
	bxcc lr
	mov r0, r4
	mov r1, r5
	bl OS_SetArenaHi
	mov r0, r5
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start OS_AllocFromArenaLo
OS_AllocFromArenaLo: ; 0x020CC26C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl OS_GetArenaLo
_020CC284:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7, lr}
	bxeq lr
	add r0, r0, r5
	sub r1, r5, #0x1
	mvn r2, r1
	sub r0, r0, #0x1
	and r4, r2, r0
	add r0, r4, r6
	add r0, r0, r5
	sub r1, r0, #0x1
	mov r0, r7
	and r5, r2, r1
	bl OS_GetArenaHi
	cmp r5, r0
	addhi sp, sp, #0x4
	movhi r0, #0x0
	ldmhiia sp!, {r4-r7, lr}
	bxhi lr
	mov r0, r7
	mov r1, r5
	bl OS_SetArenaLo
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7, lr}
	bx lr

	arm_func_start OS_SetArenaLo
OS_SetArenaLo: ; 0x020CC2F4
	mov r0, r0, lsl #0x2
	add r0, r0, #0x2700000
	add r0, r0, #0xff000
	str r1, [r0, #0xda0]
	bx lr

	arm_func_start OS_SetArenaHi
OS_SetArenaHi:
	mov r0, r0, lsl #0x2
	add r0, r0, #0x2700000
	add r0, r0, #0xff000
	str r1, [r0, #0xdc4]
	bx lr

	arm_func_start OS_GetInitArenaLo
OS_GetInitArenaLo: ; 0x020CC31C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x6
	addls pc, pc, r0, lsl #0x2
	b _020CC3DC
_020CC330:
	b _020CC34C
	b _020CC3DC
	b _020CC35C
	b _020CC39C
	b _020CC3AC
	b _020CC3BC
	b _020CC3CC
_020CC34C:
	add sp, sp, #0x4
	ldr r0, _020CC3EC ; =0x0225FFA0
	ldmfd sp!, {lr}
	bx lr
_020CC35C:
	ldr r0, _020CC3F0 ; =OSi_MainExArenaEnabled
	ldr r0, [r0]
	cmp r0, #0x0
	beq _020CC37C
	bl OS_GetConsoleType
	and r0, r0, #0x3
	cmp r0, #0x1
	bne _020CC38C
_020CC37C:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmfd sp!, {lr}
	bx lr
_020CC38C:
	add sp, sp, #0x4
	ldr r0, _020CC3F4 ; =0x023E0000
	ldmfd sp!, {lr}
	bx lr
_020CC39C:
	add sp, sp, #0x4
	ldr r0, _020CC3F8 ; =0x01FF8720
	ldmfd sp!, {lr}
	bx lr
_020CC3AC:
	add sp, sp, #0x4
	ldr r0, _020CC3FC ; =0x027E0080
	ldmfd sp!, {lr}
	bx lr
_020CC3BC:
	add sp, sp, #0x4
	ldr r0, _020CC400 ; =0x027FF000
	ldmfd sp!, {lr}
	bx lr
_020CC3CC:
	add sp, sp, #0x4
	ldr r0, _020CC404 ; =0x037F8000
	ldmfd sp!, {lr}
	bx lr
_020CC3DC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020CC3EC: .word SDK_MAIN_ARENA_LO
_020CC3F0: .word OSi_MainExArenaEnabled
_020CC3F4: .word SDK_SECTION_ARENA_EX_START
_020CC3F8: .word SDK_SECTION_ARENA_ITCM_START
_020CC3FC: .word SDK_SECTION_ARENA_DTCM_START
_020CC400: .word 0x027FF000
_020CC404: .word 0x037F8000

	arm_func_start OS_GetInitArenaHi
OS_GetInitArenaHi: ; 0x020CC408
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x6
	addls pc, pc, r0, lsl #0x2
	b _020CC508
_020CC41C:
	b _020CC438
	b _020CC508
	b _020CC448
	b _020CC488
	b _020CC498
	b _020CC4E8
	b _020CC4F8
_020CC438:
	add sp, sp, #0x4
	ldr r0, _020CC518 ; =0x023E0000
	ldmfd sp!, {lr}
	bx lr
_020CC448:
	ldr r0, _020CC51C ; =OSi_MainExArenaEnabled
	ldr r0, [r0]
	cmp r0, #0x0
	beq _020CC468
	bl OS_GetConsoleType
	and r0, r0, #0x3
	cmp r0, #0x1
	bne _020CC478
_020CC468:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmfd sp!, {lr}
	bx lr
_020CC478:
	add sp, sp, #0x4
	mov r0, #0x2700000
	ldmfd sp!, {lr}
	bx lr
_020CC488:
	add sp, sp, #0x4
	mov r0, #0x2000000
	ldmfd sp!, {lr}
	bx lr
_020CC498:
	ldr r0, _020CC520 ; =0x027E0000
	ldr r1, _020CC524 ; =0x00000000
	ldr r2, _020CC528 ; =0x00000400
	add r3, r0, #0x3f80
	cmp r1, #0x0
	sub r2, r3, r2
	bne _020CC4CC
	ldr r1, _020CC52C ; =0x027E0080
	add sp, sp, #0x4
	cmp r0, r1
	movcc r0, r1
	ldmfd sp!, {lr}
	bx lr
_020CC4CC:
	cmp r1, #0x0
	ldrlt r0, _020CC52C ; =0x027E0080
	add sp, sp, #0x4
	sublt r0, r0, r1
	subge r0, r2, r1
	ldmfd sp!, {lr}
	bx lr
_020CC4E8:
	add sp, sp, #0x4
	ldr r0, _020CC530 ; =0x027FF680
	ldmfd sp!, {lr}
	bx lr
_020CC4F8:
	add sp, sp, #0x4
	ldr r0, _020CC534 ; =0x037F8000
	ldmfd sp!, {lr}
	bx lr
_020CC508:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020CC518: .word 0x023E0000
_020CC51C: .word OSi_MainExArenaEnabled
_020CC520: .word 0x027E0000
_020CC524: .word 0x00000000
_020CC528: .word 0x00000400
_020CC52C: .word 0x027E0080
_020CC530: .word 0x027FF680
_020CC534: .word 0x037F8000

	arm_func_start OS_GetArenaLo
OS_GetArenaLo:
	mov r0, r0, lsl #0x2
	add r0, r0, #0x2700000
	add r0, r0, #0xff000
	ldr r0, [r0, #0xda0]
	bx lr

	arm_func_start OS_GetArenaHi
OS_GetArenaHi:
	mov r0, r0, lsl #0x2
	add r0, r0, #0x2700000
	add r0, r0, #0xff000
	ldr r0, [r0, #0xdc4]
	bx lr

	arm_func_start OS_InitArenaEx
OS_InitArenaEx: ; 0x020CC560
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0x2
	bl OS_GetInitArenaHi
	mov r1, r0
	mov r0, #0x2
	bl OS_SetArenaHi
	mov r0, #0x2
	bl OS_GetInitArenaLo
	mov r1, r0
	mov r0, #0x2
	bl OS_SetArenaLo
	ldr r0, _020CC5D4 ; =OSi_MainExArenaEnabled
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020CC5B8
	bl OS_GetConsoleType
	and r0, r0, #0x3
	cmp r0, #0x1
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
_020CC5B8:
	ldr r0, _020CC5D8 ; =0x0200002B
	bl OS_SetProtectionRegion1
	ldr r0, _020CC5DC ; =0x023E0021
	bl OS_SetProtectionRegion2
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CC5D4: .word OSi_MainExArenaEnabled
_020CC5D8: .word 0x0200002B
_020CC5DC: .word 0x023E0021

	arm_func_start OS_InitArena
OS_InitArena: ; 0x020CC5E0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020CC6F4 ; =OSi_Initialized
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	mov r2, #0x1
	mov r0, #0x0
	str r2, [r1, #0x0]
	bl OS_GetInitArenaHi
	mov r1, r0
	mov r0, #0x0
	bl OS_SetArenaHi
_020CC61C:
	mov r0, #0x0
	bl OS_GetInitArenaLo
	mov r1, r0
	mov r0, #0x0
	bl OS_SetArenaLo
	mov r0, #0x2
	mov r1, #0x0
	bl OS_SetArenaLo
	mov r0, #0x2
	mov r1, #0x0
	bl OS_SetArenaHi
	mov r0, #0x3
	bl OS_GetInitArenaHi
	mov r1, r0
	mov r0, #0x3
	bl OS_SetArenaHi
	mov r0, #0x3
	bl OS_GetInitArenaLo
	mov r1, r0
	mov r0, #0x3
	bl OS_SetArenaLo
	mov r0, #0x4
	bl OS_GetInitArenaHi
	mov r1, r0
	mov r0, #0x4
	bl OS_SetArenaHi
	mov r0, #0x4
	bl OS_GetInitArenaLo
	mov r1, r0
	mov r0, #0x4
	bl OS_SetArenaLo
	mov r0, #0x5
	bl OS_GetInitArenaHi
	mov r1, r0
	mov r0, #0x5
	bl OS_SetArenaHi
	mov r0, #0x5
	bl OS_GetInitArenaLo
	mov r1, r0
	mov r0, #0x5
	bl OS_SetArenaLo
	mov r0, #0x6
	bl OS_GetInitArenaHi
	mov r1, r0
	mov r0, #0x6
	bl OS_SetArenaHi
	mov r0, #0x6
	bl OS_GetInitArenaLo
	mov r1, r0
	mov r0, #0x6
	bl OS_SetArenaLo
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr
_020CC6F4: .word OSi_Initialized
