	.macro arm_func_start name
	.align 2, 0
	.global \name
	.arm
	.endm

	.macro arm_func_end name
	.size \name, .-\name
	.endm

	.macro thumb_func_start name
	.align 2, 0
	.global \name
	.thumb
	.endm

	.macro non_word_aligned_thumb_func_start name
	.global \name
	.thumb
	.endm

	.macro thumb_func_end name
	.size \name, .-\name
	.endm
