	.include "asm/macros.inc"

	.text
	; NITRO SYSCALL LIBRARY
	; VERSION 3.2

	; Secure area
	.space 0x800

	.global SVC_SoftReset
	.thumb
SVC_SoftReset:
	swi 0
	bx lr

	.global SVC_WaitByLoop
	.thumb
SVC_WaitByLoop:
	swi 3
	bx lr

	.global SVC_WaitIntr
	.thumb
SVC_WaitIntr:
	mov r2, #0
	swi 4
	bx lr

	.global SVC_WaitVBlankIntr
	.thumb
SVC_WaitVBlankIntr:
	mov r2, #0
	swi 5
	bx lr

	.global SVC_Halt
	.thumb
SVC_Halt:
	swi 6
	bx lr

	.global SVC_Div
	.thumb
SVC_Div:
	swi 9
	bx lr

	.global SVC_DivRem
	.thumb
SVC_DivRem:
	swi 9
	add r0, r1, #0
	bx lr

	.global SVC_CpuSet
	.thumb
SVC_CpuSet:
	swi 11
	bx lr

	.global SVC_CpuSetFast
	.thumb
SVC_CpuSetFast:
	swi 12
	bx lr

	.global SVC_Sqrt
	.thumb
SVC_Sqrt:
	swi 13
	bx lr

	.global SVC_GetCRC16
	.thumb
SVC_GetCRC16:
	swi 14
	bx lr

	.global IsMmemExpanded
	.thumb
IsMmemExpanded:
	swi 15
	bx lr

	.global SVC_UnpackBits
	.thumb
SVC_UnpackBits:
	swi 16
	bx lr

	.global SVC_UncompressLZ8
	.thumb
SVC_UncompressLZ8:
	swi 17
	bx lr

	.global SVC_UncompressLZ16FromDevice
	.thumb
SVC_UncompressLZ16FromDevice:
	swi 18
	bx lr

	.global SVC_UncompressHuffmanFromDevice
	.thumb
SVC_UncompressHuffmanFromDevice:
	swi 19
	bx lr

	.global SVC_UncompressRL8
	.thumb
SVC_UncompressRL8:
	swi 20
	bx lr

	.global SVC_UncompressRL16FromDevice
	.thumb
SVC_UncompressRL16FromDevice:
	swi 21
	bx lr

	.balign 4, 0 ; Don't pad with nop
