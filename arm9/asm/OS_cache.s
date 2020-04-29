    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start DC_InvalidateAll
DC_InvalidateAll: ; 0x020CC0B8
	mov r0, #0x0
	mcr p15, 0x0, r0, c7, c6, 0x0
	bx lr

	arm_func_start DC_StoreAll
DC_StoreAll: ; 0x020CC0C4
	mov r1, #0x0
_020CC0C8:
	mov r0, #0x0
_020CC0CC:
	orr r2, r1, r0
	mcr p15, 0x0, r2, c7, c10, 0x2
	add r0, r0, #0x20
	cmp r0, #0x400
	blt _020CC0CC
	add r1, r1, #0x40000000
	cmp r1, #0x0
	bne _020CC0C8
	bx lr

	arm_func_start DC_FlushAll
DC_FlushAll: ; 0x020CC0F0
	mov r12, #0x0
	mov r1, #0x0
_020CC0F8:
	mov r0, #0x0
_020CC0FC:
	orr r2, r1, r0
	mcr p15, 0x0, r12, c7, c10, 0x4
	mcr p15, 0x0, r2, c7, c14, 0x2
	add r0, r0, #0x20
	cmp r0, #0x400
	blt _020CC0FC
	add r1, r1, #0x40000000
	cmp r1, #0x0
	bne _020CC0F8
	bx lr

	arm_func_start DC_InvalidateRange
DC_InvalidateRange: ; 0x020CC124
	add r1, r1, r0
	bic r0, r0, #0x1f
_020CC12C:
	mcr p15, 0x0, r0, c7, c6, 0x1
	add r0, r0, #0x20
	cmp r0, r1
	blt _020CC12C
	bx lr

	arm_func_start DC_StoreRange
DC_StoreRange: ; 0x020CC140
	add r1, r1, r0
	bic r0, r0, #0x1f
_020CC148:
	mcr p15, 0x0, r0, c7, c10, 0x1
	add r0, r0, #0x20
	cmp r0, r1
	blt _020CC148
	bx lr

	arm_func_start DC_FlushRange
DC_FlushRange: ; 0x020CC15C
	mov r12, #0x0
	add r1, r1, r0
	bic r0, r0, #0x1f
_020CC168:
	mcr p15, 0x0, r12, c7, c10, 0x4
	mcr p15, 0x0, r0, c7, c14, 0x1
	add r0, r0, #0x20
	cmp r0, r1
	blt _020CC168
	bx lr

	arm_func_start DC_WaitWriteBufferEmpty
DC_WaitWriteBufferEmpty: ; 0x020CC180
	mov r0, #0x0
	mcr p15, 0x0, r0, c7, c10, 0x4
	bx lr

	arm_func_start IC_InvalidateAll
IC_InvalidateAll: ; 0x020CC18C
	mov r0, #0x0
	mcr p15, 0x0, r0, c7, c5, 0x0
	bx lr

	arm_func_start IC_InvalidateRange
IC_InvalidateRange:
	add r1, r1, r0
	bic r0, r0, #0x1f
_020CC1A0:
	mcr p15, 0x0, r0, c7, c5, 0x1
	add r0, r0, #0x20
	cmp r0, r1
	blt _020CC1A0
	bx lr
