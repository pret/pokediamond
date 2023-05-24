	.include "asm/macros.inc"
	.include "global.inc"

	.bss

	.global __cs_id
__cs_id: ; 0x021D7088
	.space 0x24
	.size __cs_id,.-__cs_id

	.global __cs_ref
__cs_ref: ; 0x021D70AC
	.space 0x24
	.size __cs_ref,.-__cs_ref

	.global __cs
__cs: ; 0x021D70D0
	.space 0xD8
	.size __cs,.-__cs
