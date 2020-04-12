/* rom.s TODO: Disassemble */
.include "asm/macros.inc"

.section .text

	thumb_func_start NdsMain
NdsMain:
.incbin "baserom.nds", 0x4C54, 0x1A0
