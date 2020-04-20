.include "asm/macros.inc"

/* rom2.s TODO: Disassemble */

.section .text

.incbin "baserom.nds", 0xF0B50, 0x1ABD4
