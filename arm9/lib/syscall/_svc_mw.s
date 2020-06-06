	.include "asm/macros.inc"

	.text
	; NITRO SYSCALL LIBRARY
	; VERSION 3.2

	; Secure area
	.space 0x800

	non_word_aligned_thumb_func_start SVC_SoftReset
SVC_SoftReset:
	swi 0
	bx lr
	thumb_func_end SVC_SoftReset

	non_word_aligned_thumb_func_start SVC_WaitByLoop
SVC_WaitByLoop:
	swi 3
	bx lr
	thumb_func_end SVC_WaitByLoop

	non_word_aligned_thumb_func_start SVC_WaitIntr
SVC_WaitIntr:
	mov r2, #0
	swi 4
	bx lr
	thumb_func_end SVC_WaitIntr

	non_word_aligned_thumb_func_start SVC_WaitVBlankIntr
SVC_WaitVBlankIntr:
	mov r2, #0
	swi 5
	bx lr
	thumb_func_end SVC_WaitVBlankIntr

	non_word_aligned_thumb_func_start SVC_Halt
SVC_Halt:
	swi 6
	bx lr
	thumb_func_end SVC_Halt

	non_word_aligned_thumb_func_start SVC_Div
SVC_Div:
	swi 9
	bx lr
	thumb_func_end SVC_Div

	non_word_aligned_thumb_func_start SVC_DimRem
SVC_DivRem:
	swi 9
	add r0, r1, #0
	bx lr
	thumb_func_end SVC_DivRem

	non_word_aligned_thumb_func_start SVC_CpuSet
SVC_CpuSet:
	swi 11
	bx lr
	thumb_func_end SVC_CpuSet

	non_word_aligned_thumb_func_start SVC_CpuFastSet
SVC_CpuFastSet:
	swi 12
	bx lr
	thumb_func_end SVC_CpuFastSet

	non_word_aligned_thumb_func_start SVC_Sqrt
SVC_Sqrt:
	swi 13
	bx lr
	thumb_func_end SVC_Sqrt

	non_word_aligned_thumb_func_start SVC_GetCRC16
SVC_GetCRC16:
	swi 14
	bx lr
	thumb_func_end SVC_GetCRC16

	non_word_aligned_thumb_func_start IsMemExpanded
IsMemExpanded:
	swi 15
	bx lr
	thumb_func_end IsMemExpanded

	non_word_aligned_thumb_func_start SVC_UnpackBits
SVC_UnpackBits:
	swi 16
	bx lr
	thumb_func_end SVC_UnpackBits

	non_word_aligned_thumb_func_start SVC_UncompressLZ8
SVC_UncompressLZ8:
	swi 17
	bx lr
	thumb_func_end SVC_UncompressLZ8

	non_word_aligned_thumb_func_start SVC_UncompressLZ16FromDevice
SVC_UncompressLZ16FromDevice:
	swi 18
	bx lr
	thumb_func_end SVC_UncompressLZ16FromDevice

	non_word_aligned_thumb_func_start SVC_UncompressHuffmanFromDevice
SVC_UncompressHuffmanFromDevice:
	swi 19
	bx lr
	thumb_func_end SVC_UncompressHuffmanFromDevice

	non_word_aligned_thumb_func_start SVC_UncompressRL8
SVC_UncompressRL8:
	swi 20
	bx lr
	thumb_func_end SVC_UncompressRL8

	non_word_aligned_thumb_func_start SVC_UncompressRL16FromDevice
SVC_UncompressRL16FromDevice:
	swi 21
	bx lr
	thumb_func_end SVC_UncompressRL16FromDevice

	.balign 4, 0 ; Don't pad with nop
