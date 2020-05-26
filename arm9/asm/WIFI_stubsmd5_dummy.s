	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start MD5Final
MD5Final: ; 0x020A8BA4
	ldr ip, _020A8BAC ; =DGT_Hash1GetDigest_R
	bx r12
	.balign 4
_020A8BAC: .word DGT_Hash1GetDigest_R

	arm_func_start MD5Update
MD5Update: ; 0x020A8BB0
	ldr ip, _020A8BB8 ; =DGT_Hash1SetSource
	bx r12
	.balign 4
_020A8BB8: .word DGT_Hash1SetSource

	arm_func_start MD5Init
MD5Init: ; 0x020A8BBC
	ldr ip, _020A8BC4 ; =DGT_Hash1Reset
	bx r12
	.balign 4
_020A8BC4: .word DGT_Hash1Reset
