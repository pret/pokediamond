	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	non_word_aligned_thumb_func_start SVC_SoftReset
SVC_SoftReset: ; 0x038010D4
	swi	0
	bx	lr

	non_word_aligned_thumb_func_start SVC_WaitByLoop
SVC_WaitByLoop: ; 0x038010D8
	swi	3
	bx	lr

	non_word_aligned_thumb_func_start SVC_WaitIntr
SVC_WaitIntr: ; 0x038010DC
	ldr	r2, _038010E8	; =0x04000000
	mov	ip, r2
	mov	r2, #0
	swi	4
	bx	lr
_038010E8:	.word	0x04000000

	non_word_aligned_thumb_func_start SVC_WaitVBlankIntr
SVC_WaitVBlankIntr: ; 0x038010EC
	mov	r2, #0
	swi	5
	bx	lr

	non_word_aligned_thumb_func_start SVC_Halt
SVC_Halt: ; 0x038010F2
	swi	6
	bx	lr

	non_word_aligned_thumb_func_start SVC_Stop
SVC_Stop: ; 0x038010F6
	swi	7
	bx	lr

	non_word_aligned_thumb_func_start SVC_SoundBias
SVC_SoundBias: ; 0x038010FA
	swi	8
	bx	lr

	non_word_aligned_thumb_func_start SVC_SoundBiasSet
SVC_SoundBiasSet: ; 0x038010FE
	add	r1, r0, #0
	mov	r0, #1
	swi	8
	bx	lr

	non_word_aligned_thumb_func_start SVC_SoundBiasReset
SVC_SoundBiasReset: ; 0x03801106
	add	r1, r0, #0
	mov	r0, #0
	swi	8
	bx	lr

	non_word_aligned_thumb_func_start SVC_Div
SVC_Div: ; 0x0380110E
	swi	9
	bx	lr

	non_word_aligned_thumb_func_start SVC_DivRem
SVC_DivRem: ; 0x03801112
	swi	9
	add	r0, r1, #0
	bx	lr

	non_word_aligned_thumb_func_start SVC_CpuSet
SVC_CpuSet: ; 0x03801118
	swi	11
	bx	lr

	non_word_aligned_thumb_func_start SVC_CpuFastSet
SVC_CpuFastSet: ; 0x0380111C
	swi	12
	bx	lr

	non_word_aligned_thumb_func_start SVC_Sqrt
SVC_Sqrt: ; 0x03801120
	swi	13
	bx	lr

	non_word_aligned_thumb_func_start SVC_GetCRC16
SVC_GetCRC16: ; 0x03801124
	swi	14
	bx	lr

	non_word_aligned_thumb_func_start SVC_IsDebugger
SVC_IsDebugger: ; 0x03801128
	swi	15
	bx	lr

	non_word_aligned_thumb_func_start SVC_BitUnPack
SVC_BitUnPack: ; 0x0380112C
	swi	16
	bx	lr

	non_word_aligned_thumb_func_start SVC_LZ77UnCompWram
SVC_LZ77UnCompWram: ; 0x03801130
	swi	17
	bx	lr

	non_word_aligned_thumb_func_start SVC_LZ77UnCompVramWithReadCB
SVC_LZ77UnCompVramWithReadCB: ; 0x03801134
	swi	18
	bx	lr

	non_word_aligned_thumb_func_start SVC_HuffUnCompWithReadCB
SVC_HuffUnCompWithReadCB: ; 0x03801138
	swi	19
	bx	lr

	non_word_aligned_thumb_func_start SVC_RLUnCompWram
SVC_RLUnCompWram: ; 0x0380113C
	swi	20
	bx	lr

	non_word_aligned_thumb_func_start SVC_RLUnCompVramWithReadCB
SVC_RLUnCompVramWithReadCB: ; 0x03801140
	swi	21
	bx	lr

	non_word_aligned_thumb_func_start SVC_GetSineTable
SVC_GetSineTable: ; 0x03801144
	swi	26
	bx	lr

	non_word_aligned_thumb_func_start SVC_GetPitchTable
SVC_GetPitchTable: ; 0x03801148
	swi	27
	bx	lr

	non_word_aligned_thumb_func_start SVC_GetVolumeTable
SVC_GetVolumeTable: ; 0x0380114C
	swi	28
	bx	lr
	.balign 2, 0 ; Don't pad with nop
