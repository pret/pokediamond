	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD19_02252440
MOD19_02252440: ; 0x02252440
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #3
	mov r1, #8
	lsl r2, r0, #0xf
	bl CreateHeap
	mov r0, #0
	bl GXS_SetGraphicsMode
	mov r0, #0x80
	bl GX_SetBankForSubBG
	mov r0, #1
	lsl r0, r0, #8
	bl GX_SetBankForSubOBJ
	ldr r2, _022524E0 ; =0x04001000
	ldr r0, _022524E4 ; =0xFFCFFFEF
	ldr r1, [r2]
	mov r3, #0
	and r1, r0
	mov r0, #0x10
	orr r0, r1
	str r0, [r2]
	ldr r2, _022524E8 ; =0x02252508
	add r0, r4, #0
	mov r1, #4
	bl InitBgFromTemplate
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	mov r0, #0xc
	mov r1, #0xa
	add r2, r4, #0
	mov r3, #4
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	mov r0, #0xc
	mov r1, #0xb
	add r2, r4, #0
	mov r3, #4
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x20
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #0xc
	add r1, r0, #0
	mov r2, #4
	mov r3, #0
	bl GfGfxLoader_GXLoadPal
	ldr r2, _022524E0 ; =0x04001000
	ldr r0, _022524EC ; =0xFFFF1FFF
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	ldr r1, [r2]
	ldr r0, _022524F0 ; =0xFFFFE0FF
	and r1, r0
	lsr r0, r2, #0x12
	orr r0, r1
	str r0, [r2]
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_022524E0: .word 0x04001000
_022524E4: .word 0xFFCFFFEF
_022524E8: .word MOD19_02252508
_022524EC: .word 0xFFFF1FFF
_022524F0: .word 0xFFFFE0FF
	thumb_func_end MOD19_02252440

	thumb_func_start MOD19_022524F4
MOD19_022524F4: ; 0x022524F4
	push {r3, lr}
	mov r1, #4
	bl FreeBgTilemapBuffer
	mov r0, #8
	bl DestroyHeap
	pop {r3, pc}
	thumb_func_end MOD19_022524F4

	thumb_func_start MOD19_02252504
MOD19_02252504: ; 0x02252504
	mov r0, #1
	bx lr
	thumb_func_end MOD19_02252504

	.rodata
	.global MOD19_02252508
MOD19_02252508: ; 0x02252508
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.data
	.bss
