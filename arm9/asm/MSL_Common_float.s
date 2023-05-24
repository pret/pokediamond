	.include "asm/macros.inc"
	.include "global.inc"

	.data
	.global __float_huge
__float_huge: ; 0x02106B74
	.word 0x7F800000 ; inf
	.size __float_huge,.-__float_huge

	.global __float_nan
__float_nan: ; 0x02106B78
	.word 0x7FFFFFFF ; nan
	.size __float_nan,.-__float_nan

	.global __double_huge
__double_huge: ; 0x02106B7C
	.word 0x00000000, 0x7FF00000 ; inf
	.size __double_huge,.-__double_huge
