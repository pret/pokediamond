/* secure.s TODO: Disassemble */
	.include "asm/macros.inc"

.section .text

.ifdef DIAMOND
	.byte 0xFF, 0xDE, 0xFF, 0xE7, 0xFF, 0xDE, 0xFF, 0xE7, 0xFF, 0xDE, 0xFF, 0xE7, 0xFF, 0xDE, 0x42, 0x6E
	.byte 0xF9, 0xCC, 0x54, 0x4B, 0x74, 0x53, 0x91, 0x91, 0xBC, 0x95, 0xD2, 0x12, 0xE1, 0xD0, 0xF0, 0x41
	.byte 0xE5, 0xB6, 0x47, 0xA4, 0x23, 0x18, 0x61, 0xE9, 0xC4, 0x0A, 0xA2, 0xAD, 0xF8, 0x77, 0xB5, 0x6E
	.byte 0x4C, 0x8D, 0x57, 0x83, 0x2F, 0x99, 0x16, 0x1A, 0x51, 0x4A, 0x6A, 0x1F, 0x07, 0x78, 0x92, 0xD3
	.byte 0xDF, 0x3D, 0x25, 0x0E, 0xF5, 0xA5, 0x93, 0x29, 0x1D, 0xC4, 0xA5, 0x97, 0x54, 0xA0, 0xA8, 0xB2
	.byte 0x1B, 0x9B, 0x58, 0x3C, 0xA5, 0xA4, 0x9D, 0x8B, 0x9F, 0x13, 0xAB, 0xF8, 0x09, 0x0D, 0x63, 0xE9
	.byte 0xAC, 0xF0, 0x80, 0x2D, 0xA7, 0x87, 0x5F, 0x1C, 0xDC, 0x1B, 0x0C, 0x6D, 0xED, 0xB5, 0x46, 0x60
	.byte 0x04, 0x1C, 0x11, 0xDF, 0x70, 0x47, 0xEC, 0xA5, 0x91, 0x81, 0x4D, 0xFF, 0x9E, 0x6D, 0x24, 0x87
	.byte 0x2E, 0x74, 0xAB, 0x34, 0x55, 0x7A, 0x0C, 0xA4, 0xC7, 0x66, 0xB7, 0x5A, 0xA7, 0x14, 0x64, 0xDE
	.byte 0xFD, 0xC7, 0x24, 0xF7, 0xD9, 0xE0, 0x2D, 0x67, 0x16, 0x72, 0xD3, 0x68, 0x8A, 0xA0, 0xE1, 0xD2
	.byte 0x09, 0x2A, 0x35, 0xD5, 0x40, 0x75, 0x41, 0xFC, 0xA3, 0xCA, 0xEB, 0x03, 0xDA, 0x58, 0x31, 0x72
	.byte 0x00, 0xFF, 0x46, 0xC7, 0xBA, 0xDF, 0xEE, 0x29, 0xC5, 0xE1, 0xDB, 0x7D, 0x1C, 0x37, 0x87, 0x63
	.byte 0x9A, 0x5A, 0x23, 0xCA, 0x8C, 0x38, 0x5E, 0x98
	.thumb
	.global SVC_GetCRC16
SVC_GetCRC16: ; 0x020000C8
	swi 14
	bx lr
	thumb_func_end SVC_GetCRC16

	.byte 0x27, 0x2C, 0x80, 0x42, 0xAA, 0x04, 0x05, 0x4F, 0x89, 0xDD, 0x4D, 0x3A, 0xAB, 0xF0, 0xC9, 0x2F
	.byte 0xA0, 0xAF, 0x40, 0x64, 0x08, 0xF4, 0xD8, 0x2A, 0x5D, 0xB2, 0x38, 0xD2, 0xBB, 0x11, 0xE9, 0xDA
	.byte 0x6F, 0x72, 0x75, 0x37, 0x66, 0x7C, 0x31, 0xB1, 0xAF, 0x8E, 0xD1, 0x97, 0xC6, 0x7F, 0x7C, 0x4A
	.byte 0xEA, 0xE7, 0xF6, 0x4D, 0x6D, 0x83, 0x7F, 0xAA, 0xA3, 0x0C, 0x78, 0xF6, 0x1B, 0xF7, 0x13, 0xDD
	.byte 0x71, 0x23, 0x45, 0x1B, 0xFB, 0x8D, 0x6E, 0x65, 0x13, 0xB3, 0x08, 0x71, 0x2C, 0xD8, 0xEE, 0x3C
	.byte 0x99, 0xB7, 0xC1, 0xA7, 0x2E, 0xDA, 0xA9, 0x58, 0x55, 0x26, 0xAB, 0xC8, 0xBE, 0x0B, 0xD9, 0xCC
	.byte 0x0F, 0x9B, 0xE5, 0x3C, 0x83, 0x54, 0x80, 0xF8, 0xCF, 0x0A, 0x15, 0xDF, 0x70, 0x47, 0x26, 0xB5
	.byte 0x77, 0xA0, 0x8A, 0x8B, 0xC1, 0x8F, 0xD7, 0x8A, 0xA5, 0xBC, 0xB5, 0x48, 0xD9, 0xC9, 0x29, 0x97
	.byte 0x33, 0xAC, 0x12, 0x04, 0x81, 0x8F, 0x99, 0x51, 0x78, 0x77, 0xB3, 0xED, 0xF0, 0x2F, 0x34, 0xE4
	.byte 0x30, 0x45, 0x97, 0x29, 0xF7, 0xCC, 0x1B, 0xCF, 0x15, 0x64, 0x9E, 0x7C, 0x94, 0xF0, 0x4A, 0x98
	.byte 0x5D, 0x28, 0x94, 0x12, 0x62, 0x2D, 0xE6, 0x82, 0x0D, 0xB4, 0x98, 0xC6, 0x16, 0xD8, 0xB8, 0x94
	.byte 0xFE, 0x65, 0xED, 0x31, 0xE5, 0x88, 0xA5, 0xF0, 0xF6, 0xD6, 0x8F, 0xE6, 0x42, 0x7F, 0xF1, 0xBC
	.byte 0xA2, 0xD5, 0x0E, 0x50, 0xFC, 0x83, 0x70, 0x45, 0x55, 0xAF, 0xF5, 0x89, 0xE2, 0x69, 0x71, 0xBA
	.byte 0xFA, 0x75

	.thumb
	.global SVC_Sqrt
SVC_Sqrt: ; 0x0200019E
	swi 13
	bx lr
	thumb_func_end SVC_Sqrt

	.byte 0x1C, 0x85, 0x9C, 0xB6, 0x15, 0xC1, 0x40, 0x1B, 0x79, 0x01, 0x96, 0xC4, 0x80, 0x99, 0xF1, 0x28
	.byte 0x6E, 0x3E, 0xE1, 0x0D, 0x73, 0xD8, 0x07, 0xCB, 0x75, 0x1C, 0x44, 0x41, 0xC4, 0x60, 0xE5, 0xB0
	.byte 0xBA, 0x74, 0xF1, 0x11, 0xA4, 0x7E, 0xE7, 0x00, 0x6A, 0xBB, 0xB6, 0x78, 0x45, 0xDF, 0x93, 0xF2
	.byte 0xF3, 0x8B, 0xA1, 0xE4, 0xA4, 0x9B, 0x2B, 0x56, 0xBF, 0xE1, 0x07, 0xE9, 0xEF, 0x0F, 0x7A, 0xA0
	.byte 0x0F, 0x49, 0x9D, 0xC9, 0x14, 0x90, 0x63, 0x4D, 0xCD, 0x84, 0x9D, 0xB3, 0x48, 0xB5, 0x92, 0x08
	.byte 0x27, 0x5C, 0x2C, 0xC1, 0xD3, 0x49, 0x09, 0x0C, 0xD6, 0xBA, 0xFE, 0xC4, 0xAA, 0xA1, 0x36, 0x88
	.byte 0x3E, 0x64, 0x23, 0x34, 0xA5, 0x58, 0xFF, 0x60, 0x27, 0x72, 0x09, 0xDF, 0x08, 0x1C, 0x70, 0x47
	.byte 0x63, 0xC7, 0xA0, 0x60, 0x53, 0xFC, 0x9A, 0x98, 0x48, 0x47, 0x42, 0x83, 0xC1, 0xE8, 0x4D, 0xBC
	.byte 0xE6, 0xF4, 0x2F, 0xD7, 0x6D, 0x6C, 0xCF, 0x44, 0x0A, 0x68, 0xDC, 0xAC, 0xB8, 0x27, 0x24, 0x44
	.byte 0x59, 0x7F, 0x2D, 0xE3, 0x79, 0x0C, 0x6B, 0x9F, 0x4A, 0xF9, 0x5B, 0x1D, 0x57, 0x2A, 0xD5, 0xC2
	.byte 0x76, 0x15, 0xF8, 0x04, 0x7B, 0xF1, 0xD3, 0x2B, 0x15, 0xA1, 0x26, 0x29, 0xA2, 0x81, 0xE8, 0x63
	.byte 0xC9, 0xBF, 0x1C, 0x88, 0x2A, 0x1A, 0x61, 0x97, 0x12, 0x08, 0xE0, 0x4A, 0x2B, 0x25, 0x72, 0x8C
	.byte 0xB8, 0x57, 0xAF, 0xE7, 0x48, 0x62, 0x30, 0x9A, 0x8B, 0x13, 0x4A, 0x79, 0xED, 0x95, 0xED, 0xED
	.byte 0x65, 0x56, 0x02, 0x2B, 0xCA, 0x6A, 0x0F, 0x26, 0xC8, 0xC4, 0x94, 0xEB, 0x5A, 0xF2, 0xD2, 0xBE
	.byte 0x49, 0x0A, 0x77, 0xAE, 0x17, 0x08, 0x02, 0xD0, 0x35, 0x26, 0x12, 0xDF, 0x70, 0x47, 0xE7, 0xAA
	.byte 0x20, 0x31, 0x36, 0x88, 0x88, 0x14, 0xA3, 0x8F, 0x38, 0x7F, 0xA7, 0x30, 0x3F, 0x62, 0xB1, 0xD9
	.byte 0x76, 0x59, 0x7B, 0x55, 0xFB, 0x73, 0x2D, 0x64, 0xB0, 0xD1, 0x01, 0x96, 0xDA, 0x04, 0x35, 0x81
	.byte 0xF9, 0x35, 0x9D, 0xAE, 0x24, 0x60, 0xFF, 0x5D, 0xE4, 0xD2, 0xC5, 0x8B, 0x2B, 0xD0, 0xC2, 0x24
	.byte 0x78, 0x3D, 0xF5, 0x38, 0x2A, 0x78, 0x44, 0xA2, 0x7C, 0xF0, 0x5F, 0x49, 0x9D, 0x40, 0x18, 0xD9
	.byte 0xF2, 0x82, 0xB5, 0xC0, 0xC5, 0x59, 0x8A, 0x5E, 0xB5, 0xCF, 0xDC, 0x03, 0xAA, 0xC3, 0x4A, 0x96
	.byte 0x12, 0x75, 0xD5, 0xC2, 0xE9, 0x3E, 0xA9, 0x6E, 0xFB, 0x38, 0xAC, 0xB8, 0x5B, 0x94, 0x81, 0xD5
	.byte 0x2F, 0x37, 0xC2, 0xD7, 0xC4, 0xEF, 0x6E, 0x8C, 0x1F, 0xFB, 0x36, 0x1D

	.thumb
	.global SVC_CpuSet
SVC_CpuSet: ; 0x020002FE
	swi 11
	bx lr

	.byte 0x9A, 0xCF, 0x03, 0x50, 0xA1, 0xE4, 0x98, 0xEA, 0x2E, 0x86, 0xBC, 0xBE, 0x31, 0x3D, 0xE8, 0xA4
	.byte 0x52, 0x6D, 0x18, 0x28, 0x8F, 0x2C, 0xED, 0x3F, 0xA2, 0xD5, 0x2A, 0xEC, 0x62, 0x15, 0x54, 0xDA
	.byte 0x09, 0x05, 0x4D, 0x31, 0x97, 0x87, 0xC8, 0xA9, 0x5D, 0x16, 0x72, 0xAB, 0x72, 0xD1, 0x40, 0xFF
	.byte 0x68, 0x58, 0x6C, 0xB0, 0x2F, 0xED, 0x61, 0xA5, 0xF6, 0x2E, 0x9A, 0xE2, 0x68, 0x53, 0xEB, 0xAA
	.byte 0x22, 0x7F, 0x5C, 0xA1, 0xFA, 0x16, 0x49, 0x80, 0x6E, 0xDA, 0xFA, 0xAC, 0x1C, 0xE3, 0xC1, 0xC4
	.byte 0x5A, 0xCC, 0x0C, 0xDF, 0x70, 0x47, 0xF2, 0x98, 0x8D, 0xBF, 0xE0, 0x13, 0xFA, 0x9B, 0x06, 0x02
	.byte 0x9C, 0x8D, 0x25, 0xB2, 0xE3, 0xFD, 0xAE, 0xCF, 0x4E, 0x37, 0x89, 0x20, 0x26, 0xEB, 0xBA, 0xE3
	.byte 0x3D, 0xF3, 0x15, 0x0E, 0x6D, 0x4F, 0xE9, 0xB8, 0x97, 0xB8, 0xD8, 0x88, 0xF8, 0xA8, 0xCA, 0x33
	.byte 0x4D, 0x95, 0x06, 0x0F, 0xCB, 0xEE, 0x66, 0xFB, 0xA5, 0xF4, 0x74, 0xB4, 0xC0, 0x02, 0xC9, 0xAE
	.byte 0x6B, 0x9D, 0x42, 0xF5, 0xD4, 0xF5, 0xBB, 0x4F, 0x36, 0x45, 0xCA, 0x61, 0x8E, 0x81, 0x70, 0x08
	.byte 0x8F, 0x53, 0xF6, 0x42, 0x5C, 0x19, 0xB1, 0x88, 0xB6, 0x3C, 0x7F, 0x46, 0xC4, 0x35, 0x85, 0xFC
	.byte 0x6F, 0xED, 0xA4, 0xDE, 0x8D, 0x22, 0x9F, 0x0D, 0xE5, 0xFE, 0x0C, 0x64, 0xC3, 0xD4, 0x7D, 0x6A
	.byte 0xC8, 0xD9, 0xD9, 0x87, 0xB4, 0x76, 0xAB, 0x7B, 0x00, 0x22, 0x05, 0xDF, 0x70, 0x47, 0x01, 0x76
	.byte 0xA5, 0x8A, 0x83, 0xAB, 0x61, 0xBE, 0x95, 0x9E, 0x89, 0xA4, 0xE8, 0xED, 0x31, 0x3C, 0x3E, 0xBF
	.byte 0x13, 0x1F, 0x51, 0xDE, 0x0D, 0x0F, 0x91, 0xA0, 0xB8, 0xE3, 0xAA, 0x0E, 0xC6, 0x59, 0xC1, 0x0B
	.byte 0x86, 0xDC, 0xE9, 0xCB, 0xFB, 0x42, 0x8A, 0xC8, 0x98, 0x33, 0x4E, 0xAE, 0xB9, 0x3D, 0xCF, 0x31
	.byte 0x92, 0x69, 0xA4, 0x74, 0x46, 0x13, 0xCE, 0x6B, 0x6F, 0xE2, 0xDD, 0xE2, 0x4C, 0x3A, 0xF9, 0xCF
	.byte 0xA9, 0x28, 0xE8, 0xFE, 0x66, 0xE0, 0x34, 0x8E, 0xE7, 0xEE, 0x1D, 0x01, 0xB0, 0xA6, 0x8D, 0x56
	.byte 0xCE, 0xAD, 0x44, 0x4E, 0x56, 0x5F, 0x41, 0x0D, 0x7B, 0xD7, 0x87, 0xA2, 0xF5, 0xF9, 0x86, 0xE7
	.byte 0x7F, 0x14, 0xCB, 0x01, 0x51, 0xDB, 0xB0, 0x35, 0x13, 0xDF, 0x70, 0x47, 0xE8, 0xD5, 0x44, 0x23
	.byte 0x77, 0x99, 0x4C, 0xF1, 0x0F, 0x18, 0xBF, 0x84, 0x9F, 0xC3, 0xA0, 0x08, 0x8B, 0x9D, 0xD3, 0x34
	.byte 0x8B, 0xF8, 0xC6, 0xF3, 0x6E, 0x1E, 0x9A, 0xA3, 0x2E, 0x43, 0xBF, 0x27, 0xE4, 0xED, 0xEF, 0x0D
	.byte 0x2E, 0x71, 0xE4, 0x49, 0x74, 0x11, 0xBF, 0x47, 0x7E, 0x65, 0xE1, 0x17, 0x4C, 0x1B, 0x8B, 0xA3
	.byte 0x8E, 0x7A, 0x7A, 0xB4, 0x35, 0x6C, 0x9E, 0x51, 0x68, 0x6A, 0x63, 0x2C, 0xF3, 0xCA, 0x58, 0xF3
	.byte 0x06, 0x99, 0xF2, 0x47, 0x91, 0x78, 0xCD, 0xFE, 0x4E, 0xE4, 0x99, 0x65, 0x32, 0x52, 0x28, 0xFA
	.byte 0xF3, 0xE4, 0xBF, 0xFA, 0x3F, 0x37, 0x36, 0x98, 0x3A, 0x18, 0xA9, 0x42, 0x92, 0x7F, 0xDC, 0x17
	.byte 0x59, 0x2F, 0x3A, 0x06, 0x38, 0xDA, 0xE5, 0x27, 0x13, 0x41, 0xD1, 0xEC, 0x95, 0xC6, 0xEC, 0xD6
	.byte 0x10, 0xDF, 0x70, 0x47, 0x7E, 0x9D, 0x05, 0xD3, 0xF5, 0x36, 0x3B, 0xE7, 0x7C, 0xAE, 0x81, 0xEF
	.byte 0xC8, 0x4B, 0x92, 0xB5, 0x6C, 0x12, 0x4F, 0x3B, 0x26, 0x6A, 0x7E, 0x22, 0xBF, 0x08, 0xAB, 0x6D
	.byte 0x5F, 0xFE, 0xB2, 0x12, 0xD8, 0xFA, 0x8E, 0x17, 0x2A, 0x7B, 0xB1, 0xA2, 0x98, 0x69, 0x19, 0xAC
	.byte 0xEE, 0x7E, 0x86, 0xA5, 0xD2, 0x7A, 0x4C, 0x7C, 0x17, 0x4A, 0x52, 0x80, 0x45, 0xD3, 0x3A, 0xD5
	.byte 0x3D, 0x6C, 0xD7, 0xE5, 0xBD, 0x9A, 0x4A, 0x58, 0x9B, 0x2A, 0xD9, 0xF9, 0x23, 0x02, 0x5E, 0x92
	.byte 0x0A, 0x31, 0x23, 0x2B, 0x5C, 0x0F, 0xB4, 0x16, 0x5E, 0x34, 0xED, 0xF2, 0x4A, 0xB6, 0x3C, 0xB6
	.byte 0xE5, 0x41, 0xD5, 0x24, 0x3A, 0xBA, 0xFB, 0xF1, 0x6D, 0x2B, 0x6E, 0x6A, 0x6A, 0x88, 0xD5, 0x3E
	.byte 0x4F, 0x05, 0x0F, 0xDF, 0x70, 0x47, 0xEC, 0xB5, 0x44, 0xF9, 0x2C, 0xAF, 0x08, 0xE7, 0x9F, 0x4D
	.byte 0xA9, 0x31, 0x6A, 0x8C, 0x11, 0xEE, 0x40, 0x23, 0xE5, 0x56, 0xB0, 0x11, 0xDA, 0x7B, 0x25, 0xB6
	.byte 0x8D, 0x8B, 0x53, 0xD6, 0xFD, 0xD4, 0x27, 0xDB, 0xDD, 0xBD, 0x83, 0x38, 0xB4, 0x56, 0x60, 0xC5
	.byte 0x9F, 0x11, 0xFC, 0xB3, 0xED, 0xE4, 0x32, 0x98, 0x61, 0x6E, 0x1B, 0x0E, 0x14, 0xEB, 0xC5, 0xA3
	.byte 0x11, 0x17, 0x21, 0xBA, 0xDC, 0x0A, 0x3D, 0x4D, 0xED, 0x8D, 0xA6, 0x4C, 0x1B, 0xC2, 0xFB, 0xD0
	.byte 0xCA, 0xA0, 0x0D, 0xDA, 0x68, 0x2D, 0x5A, 0x77, 0x20, 0xD9, 0xD0, 0x55, 0x5D, 0x3B, 0xC2, 0x1D
	.byte 0x4C, 0x93, 0x56, 0x16, 0xCA, 0x36, 0x7E, 0xB0, 0x14, 0xDF, 0x70, 0x47, 0x78, 0x49, 0xE1, 0x21
	.byte 0x68, 0x63, 0x9E, 0x8B, 0xE1, 0x36, 0x90, 0x4D, 0xB6, 0x5F, 0x50, 0x3D, 0xBD, 0x26, 0x97, 0xA3
	.byte 0x2E, 0x17, 0xA4, 0x89, 0x04, 0xAF, 0x83, 0x71, 0x41, 0x4C, 0x5A, 0x36, 0x75, 0x26, 0x57, 0x13
	.byte 0xA7, 0xBC, 0x4C, 0x17, 0xAD, 0x27, 0xBF, 0xF0, 0xFE, 0xB2, 0xFB, 0x7D, 0x7C, 0x2B, 0x6E, 0x9E
	.byte 0xAB, 0x44, 0xC4, 0x96, 0xC4, 0x7F, 0xA8, 0xA9, 0x36, 0xCF, 0x5E, 0x26, 0x86, 0x9D, 0x3B, 0x9C
	.byte 0xB1, 0x6D, 0xE0, 0xC6, 0x6B, 0x27, 0xBD, 0x38, 0xC8, 0x69, 0xA3, 0xFE, 0x50, 0x6D, 0xE1, 0x54
	.byte 0x6E, 0xB2, 0x1C, 0x5D, 0x04, 0x50, 0x0B, 0x71, 0x97, 0x53, 0x7F, 0x6D, 0x1C, 0x80, 0xA9, 0xE2

	.thumb
	.global SVC_WaitByLoop
SVC_WaitByLoop:
	swi 3
	bx lr

	.byte 0x6E, 0x47, 0x18, 0xE1, 0x7B, 0xB7, 0xC4, 0xAA, 0xEC, 0xC4, 0x6C, 0xFF, 0xED, 0x0B, 0x2B, 0x24
	.byte 0xE1, 0xF7, 0xCD, 0xE0, 0x48, 0x7F, 0xE4, 0x61, 0x33, 0x72, 0x52, 0x72, 0x76, 0x05, 0x51, 0x72
	.byte 0xF7, 0xCA, 0xFA, 0x86, 0x4A, 0x13, 0xA5, 0x9B, 0xC5, 0x13, 0xF2, 0xFE, 0xA7, 0x3F, 0x2A, 0x69
	.byte 0x85, 0xFA, 0xE9, 0x15, 0x66, 0xEC, 0x67, 0xCE, 0x72, 0x11, 0xF5, 0xB2, 0xA4, 0xCF, 0x75, 0x15
	.byte 0x42, 0x92, 0x1E, 0x58, 0x98, 0x55, 0xFE, 0xF9, 0xDA, 0x13, 0xE1, 0x6D, 0xCA, 0xAB, 0xD4, 0x00
	.byte 0x1B, 0x2A, 0x04, 0x86, 0x5D, 0x9D, 0xEB, 0xF8, 0x58, 0xDC, 0x26, 0x1A, 0xD8, 0xA1, 0x20, 0x65
	.byte 0x3F, 0x1D, 0xD8, 0x32, 0x1B, 0x3E, 0xE9, 0x12, 0xE8, 0x25, 0x74, 0x1F, 0xE6, 0xDB, 0xEF, 0x23
	.byte 0xF9, 0xE0, 0x99, 0x3C, 0x7E, 0xBF, 0x42, 0x5B, 0x09, 0xDF, 0x70, 0x47, 0xD5, 0x1D, 0xDE, 0x36
	.byte 0x47, 0x99, 0xEA, 0x96, 0xE7, 0xB5, 0x3D, 0x2A, 0xAA, 0x23, 0x48, 0x11, 0x04, 0xA5, 0x1A, 0xBC
	.byte 0xA9, 0x22, 0x3F, 0x9F, 0x61, 0x10, 0xED, 0x1E, 0x57, 0x72, 0x0E, 0x8F, 0xFA, 0x08, 0x56, 0xEA
	.byte 0xA4, 0x16, 0x02, 0xDE, 0x39, 0x73, 0xE2, 0x5A, 0xC0, 0x61, 0x83, 0x79, 0xAD, 0x6F, 0xB4, 0x6D
	.byte 0xF8, 0xF7, 0xAC, 0xBB, 0x76, 0xAA, 0xE6, 0x49, 0x79, 0x9E, 0x99, 0x07, 0x3C, 0x23, 0x2E, 0x63
	.byte 0xA4, 0x77, 0xBC, 0xCB, 0x3C, 0x64, 0x3C, 0x91, 0x5E, 0x7C, 0xE3, 0xAB, 0xFF, 0xC9, 0xCE, 0x95
	.byte 0x7D, 0x97, 0x21, 0x83, 0x13, 0x41, 0x7D, 0x6D, 0x99, 0xCE, 0x7A, 0xBB, 0x7F, 0x7C, 0x98, 0x5C
	.byte 0x96, 0x5F, 0x35, 0x78, 0x95, 0x3C, 0xAC, 0x1A, 0x43, 0x07, 0x8B, 0x60, 0xBB, 0x61, 0x7B, 0x3B
	.byte 0x59, 0xCF, 0x5D, 0xF4, 0xCA, 0x19, 0x11, 0x2E, 0x06, 0xDF, 0x70, 0x47, 0x7D, 0x64, 0xA1, 0x4D
	.byte 0x22, 0xE9, 0x4E, 0xFC, 0x2E, 0xAA, 0x6F, 0x29, 0xBA, 0x38, 0x77, 0xED, 0x0A, 0x33, 0x37, 0xDF
	.byte 0x9F, 0xC7, 0x38, 0xC5, 0x80, 0x88, 0x63, 0xBD, 0x75, 0x6E, 0x71, 0x9C, 0x7F, 0xEC, 0x1E, 0x0C
	.byte 0x95, 0xF9, 0xCA, 0xA5, 0x1B, 0x89, 0x72, 0xE2, 0x92, 0x88, 0x9B, 0x0D, 0xB7, 0x5C, 0xC0, 0xA8
	.byte 0x30, 0x0D, 0xA8, 0x69, 0x74, 0xA0, 0xE1, 0xEE, 0x07, 0x1D, 0x2C, 0x4A, 0xC8, 0x72, 0x9D, 0x14
	.byte 0x81, 0xF9, 0x00, 0xDF, 0x70, 0x47, 0xA9, 0xC6, 0x77, 0x11, 0x80, 0x51, 0x50, 0xAC, 0x5B, 0x70
	.byte 0x4F, 0x48, 0x21, 0x7E, 0xC4, 0x84, 0x46, 0xDF, 0x05, 0x93, 0x11, 0x89, 0x79, 0x24, 0x15, 0x86
	.byte 0x97, 0xC9, 0x86, 0x10, 0x86, 0x5D, 0xC4, 0x34, 0x25, 0x7E, 0x15, 0xDC, 0x45, 0x04, 0x55, 0x74
	.byte 0x15, 0x80, 0xEC, 0x90, 0x3C, 0x00, 0x1B, 0xB0, 0xCB, 0xBD, 0x8F, 0x30, 0x02, 0x7F, 0xFD, 0x23
	.byte 0x66, 0x78, 0xCC, 0x51, 0x4C, 0x17, 0x4A, 0xD2, 0xD1, 0x81, 0xEC, 0xE2, 0xF2, 0x49, 0xAF, 0x24
	.byte 0x49, 0x37, 0x7D, 0x66, 0xE4, 0x50, 0x27, 0x8C, 0xE5, 0x01, 0x1D, 0x72, 0x89, 0xCD, 0x05, 0xD8
	.byte 0x72, 0x53, 0x98, 0x7D, 0x2F, 0x51, 0x0B, 0x2B, 0x00, 0x22, 0x04, 0xDF, 0x70, 0x47, 0x5E, 0x7D
	.byte 0xDC, 0x69, 0x73, 0xF1, 0x9F, 0xD4, 0xC0, 0xA5, 0x9F, 0x3C, 0xD6, 0xF5, 0x01, 0xF7, 0x6A, 0xF1
	.byte 0xE5, 0xCA, 0xAA, 0x6A, 0x3C, 0xA5, 0x81, 0xB6, 0x3C, 0x0A, 0xAC, 0x77, 0x32, 0x54, 0x85, 0x77
	.byte 0x7C, 0x56, 0xF9, 0xC9, 0x43, 0x93, 0xA0, 0x61, 0x8D, 0x92, 0x17, 0xBD, 0xDE, 0xAC, 0x1E, 0x35
	.byte 0x33, 0xCD, 0xDD, 0xD0, 0x49, 0x49, 0x2A, 0x45, 0xDD, 0x0E, 0x6F, 0xF7, 0x76, 0x20, 0xBF, 0xD8
	.byte 0xCE, 0x6A, 0x21, 0x6F, 0x09, 0xA6, 0x03, 0xC2, 0x6B, 0x91, 0x46, 0x86, 0x86, 0x30, 0x16, 0x20
	.byte 0x32, 0xBE, 0x4F, 0x6F, 0x6A, 0x34, 0xA8, 0xEB, 0x00, 0x00
.else
	.byte 0xFF, 0xDE, 0xFF, 0xE7, 0xFF, 0xDE, 0xFF, 0xE7, 0xFF, 0xDE, 0xFF, 0xE7, 0xFF, 0xDE, 0xF2, 0xB4
	.byte 0x81, 0xC1, 0x6E, 0x73, 0x2D, 0xF1, 0xAB, 0x13, 0x78, 0xCB, 0x22, 0x23, 0xB5, 0xDD, 0xE7, 0x6F
	.byte 0xE8, 0xFE, 0xA2, 0x31, 0x84, 0x32, 0x7F, 0xB3, 0xFC, 0x32, 0x3B, 0x5F, 0xD2, 0x19, 0x8B, 0xE0
	.byte 0x9E, 0x58, 0x5A, 0x86, 0xD1, 0x2C, 0x49, 0xC6, 0x75, 0x82, 0xF1, 0xE9, 0x9C, 0x3F, 0x72, 0x77
	.byte 0xE5, 0x18, 0xFB, 0xE7, 0xCF, 0x29, 0x15, 0xC8, 0xB7, 0x91, 0x73, 0x77, 0xC8, 0x89, 0xD9, 0xE3
	.byte 0x91, 0x39, 0xA8, 0xC1, 0x22, 0x64, 0xD1, 0xDC, 0x23, 0xDD, 0xA8, 0xD8, 0x40, 0x6A, 0xDE, 0x49
	.byte 0x0D, 0xFC, 0x09, 0x4F, 0x9C, 0x4B, 0x19, 0xBF, 0xF7, 0xA5, 0x49, 0xA6, 0x2B, 0x2A, 0x7E, 0x76
	.byte 0xC0, 0x0D, 0x5E, 0x0D, 0xE7, 0x62, 0xE1, 0xCA

	.thumb
	.global SVC_UncompressRL16FromDevice
SVC_UncompressRL16FromDevice: ; 0x02000078
	swi 21
	bx lr

	.byte 0x8E, 0xCD, 0x45, 0x99, 0xC2, 0xFC, 0x47, 0x0B, 0xF9, 0x33, 0x43, 0x20, 0xED, 0x62, 0xDC, 0x65
	.byte 0x98, 0x98, 0x03, 0x41, 0x07, 0x6C, 0xA1, 0xF0, 0xF7, 0x76, 0x6A, 0x80, 0xF5, 0xE9, 0xB1, 0xA3
	.byte 0x7F, 0xEE, 0xC1, 0xC0, 0x9C, 0xD8, 0x22, 0xA3, 0x3A, 0x48, 0x10, 0x9B, 0x49, 0x66, 0xE8, 0x09
	.byte 0x1C, 0xE0, 0x23, 0xF4, 0x92, 0x78, 0x92, 0x76, 0xFB, 0xBD, 0x4E, 0x63, 0x4A, 0x4B, 0x80, 0xAE
	.byte 0x98, 0xFC, 0x58, 0x35, 0xC4, 0x08, 0x8A, 0x6F, 0xDD, 0x30, 0xCC, 0x06, 0xAE, 0x80, 0xBC, 0x0C
	.byte 0xC5, 0xDB, 0x41, 0x60, 0x68, 0x9B, 0xBC, 0x70, 0xD9, 0x93, 0x4C, 0x71, 0xCE, 0xF4, 0x3C, 0x40
	.byte 0x36, 0xDF, 0x51, 0xDC, 0x88, 0x76, 0xCE, 0x94

	.thumb
	.global SVC_WaitVBlankIntr
SVC_WaitVBlankIntr: ; 0x020000E4
	mov r2, #0
	swi 5
	bx lr

	.byte 0x8F, 0x25, 0x5F, 0x13, 0xE1, 0x3C, 0xF0, 0x99, 0x96, 0x05, 0xF2, 0xB5, 0x87, 0xF9, 0x3D, 0x6C
	.byte 0x5B, 0x0B, 0x85, 0x71, 0x3F, 0x92, 0xE0, 0x2E, 0xC3, 0x56, 0x26, 0x8B, 0xF4, 0x4B, 0x6D, 0x48
	.byte 0x25, 0xF0, 0x17, 0x26, 0x95, 0x35, 0x09, 0x85, 0xB9, 0xFB, 0x57, 0x08, 0x3A, 0xE6, 0xAF, 0x38
	.byte 0x5F, 0x0C, 0xAB, 0x8F, 0x7B, 0x81, 0x35, 0xE2, 0xC1, 0xD3, 0x5A, 0x9B, 0x85, 0xC5, 0xE6, 0x1C
	.byte 0x10, 0xEC, 0xF5, 0x3C, 0x2B, 0x77, 0x27, 0xE2, 0xC3, 0x87, 0x07, 0x09, 0x2F, 0x78, 0xB2, 0x1E
	.byte 0x72, 0x59, 0xEF, 0xC8

	.thumb
	.global SVC_UnpackBits
SVC_UnpackBits: ; 0x0200013E
	swi 16
	bx lr

	.byte 0x7F, 0x0D, 0x98, 0xCA, 0x0D, 0x6B, 0xAA, 0xE1, 0xBB, 0x0E, 0xC6, 0x6B, 0xB9, 0x85, 0x13, 0x01
	.byte 0x11, 0xC9, 0xC0, 0x37, 0x2B, 0xB5, 0x7A, 0x1B, 0x98, 0xA7, 0xA4, 0x53, 0x3F, 0xCD, 0x02, 0xD1
	.byte 0xFA, 0xF1, 0xE5, 0xAC, 0x05, 0x1C, 0xCD, 0x10, 0x19, 0x76, 0xAB, 0xDC, 0xBF, 0xEE, 0x2B, 0x10
	.byte 0x80, 0x04, 0xFF, 0x43, 0x83, 0x91, 0x48, 0x0F, 0x62, 0xC6, 0xC4, 0xE2, 0x87, 0x4E, 0x51, 0x94
	.byte 0x84, 0xBE, 0x25, 0x57, 0x56, 0x35, 0xA8, 0x74, 0xE8, 0x5B, 0x23, 0x77, 0xE5, 0x9A, 0x51, 0xDC
	.byte 0x6F, 0x2E, 0xBF, 0x2B, 0xF6, 0x1B, 0xC7, 0x60, 0x89, 0xE0, 0xE3, 0x66, 0xDD, 0x82, 0x2D, 0xE1
	.byte 0xE7, 0xC9, 0x66, 0x08, 0x37, 0x48, 0xD4, 0x0D, 0x6F, 0x84, 0xBB, 0x28, 0xF7, 0x9A, 0x0F, 0x81
	.byte 0xF5, 0xF9, 0xD7, 0x05, 0x5C, 0x5B, 0xA4, 0xCF, 0x3F, 0xBD, 0x02, 0xC6, 0x54, 0x59

	.thumb
	.global SVC_UncompressLZ16FromDevice
SVC_UncompressLZ16FromDevice: ; 0x020001C0
	swi 18
	bx lr

	.byte 0xEA, 0xE2, 0x38, 0xCD, 0x7B, 0x60, 0x77, 0x99, 0x13, 0x94, 0x94, 0x7C, 0xD1, 0xB4, 0xA2, 0x68
	.byte 0xB3, 0x9A, 0x06, 0x50, 0xA5, 0xB8, 0x42, 0x29, 0x6F, 0x7F, 0xBB, 0xC3, 0xB6, 0xDC, 0x6F, 0x3E
	.byte 0x8E, 0x83, 0xD6, 0x49, 0x09, 0x87, 0x2F, 0x33, 0xA8, 0x9C, 0xBA, 0x1C, 0x7B, 0x94, 0xFA, 0x3B
	.byte 0xE9, 0xED, 0xA8, 0x5A, 0xE5, 0x56, 0x78, 0xDA, 0xDC, 0x01, 0xAB, 0x56, 0xE7, 0x49, 0xF3, 0xC6
	.byte 0xED, 0x36, 0x9C, 0x6A, 0xC9, 0xC0, 0x91, 0x9E, 0x7A, 0xDA, 0x05, 0x96, 0xB3, 0xF3, 0x22, 0x2E
	.byte 0xB8, 0xA9, 0x9F, 0xA9, 0xCC, 0xDA, 0x01, 0x3A, 0xA3, 0x31, 0xDA, 0x35, 0x27, 0xF2, 0x58, 0xA5
	.byte 0x53, 0x89, 0x8C, 0xA5, 0xBA, 0x7F, 0x13, 0x0F, 0x3A, 0xC5

	.thumb
	.global SVC_SoftReset
SVC_SoftReset: ; 0x0200022E
	swi 0
	bx lr

	.byte 0x80, 0xBE, 0x17, 0xC4, 0x7B, 0x18, 0xE4, 0x43, 0x96, 0x59, 0x0A, 0x7B, 0xB0, 0x46, 0xEE, 0x18
	.byte 0x40, 0x4E, 0x48, 0x1A, 0xB8, 0x78, 0x9E, 0x1A, 0x19, 0xD5, 0x3A, 0x7E, 0x80, 0x39, 0xD0, 0xFA
	.byte 0x8B, 0x56, 0xB7, 0x0F, 0x28, 0x90, 0xFC, 0x7F, 0xFF, 0x44, 0xB2, 0x2B, 0xE0, 0xE6, 0x72, 0x03
	.byte 0x34, 0x30, 0x8B, 0x45, 0x80, 0x56, 0xD2, 0xD0, 0xB0, 0xC5, 0xF8, 0xCA, 0xF9, 0xC3, 0x9C, 0x4E
	.byte 0xC7, 0x51, 0x9B, 0xAA, 0x9A, 0x73, 0x81, 0x21, 0x7B, 0x8C, 0xBC, 0x79, 0x53, 0x7F, 0x9D, 0xE0
	.byte 0xFD, 0x82, 0xAE, 0x4E, 0x09, 0xDF, 0x08, 0x1C, 0x70, 0x47, 0x2F, 0x43, 0x55, 0x76, 0x8C, 0x0A
	.byte 0x13, 0x3A, 0x13, 0x61, 0x9F, 0xF0, 0xD3, 0x7C, 0x7C, 0x85, 0x69, 0x62, 0x91, 0x29, 0x6D, 0x5F
	.byte 0xB6, 0xAD, 0x42, 0x9D, 0x66, 0x8C, 0x02, 0x01, 0x3F, 0x78, 0x41, 0x25, 0xDE, 0xE7, 0x30, 0xE4
	.byte 0xBA, 0xEC, 0x6C, 0x0F, 0x4B, 0x23, 0x75, 0x84, 0xD7, 0x19, 0x95, 0xBB, 0x86, 0x6D, 0xCC, 0x36
	.byte 0xCF, 0xEC, 0x0A, 0xCF, 0x99, 0x3A, 0x0B, 0x01, 0xCF, 0x52, 0x7D, 0xD5, 0x33, 0x2D, 0x99, 0x31
	.byte 0x48, 0x43, 0xFE, 0x53, 0xF6, 0x49, 0x74, 0xF7, 0xCC, 0x85, 0xAE, 0xD1, 0x9D, 0x56, 0x6E, 0xDE
	.byte 0xC3, 0x0D, 0x19, 0x29, 0x27, 0xC6, 0x1F, 0x39, 0x6C, 0xDB, 0x9F, 0x56, 0x4E, 0x39, 0x9E, 0x5F
	.byte 0xB1, 0xBD, 0x25, 0xE9, 0x1D, 0xFB, 0x12, 0xCF

	.thumb
	.global SVC_UncompressHuffmanFromDevice
SVC_UncompressHuffmanFromDevice: ; 0x020002FA
	swi 19
	bx lr

	.byte 0x88, 0x07, 0x93, 0x96, 0xCD, 0xEF, 0xB4, 0x07, 0x96, 0xD3, 0xE6, 0xD8, 0x05, 0x2A, 0xF5, 0xCB
	.byte 0x2D, 0x82, 0x9D, 0xB1, 0xA7, 0xDA, 0x38, 0xC1, 0x37, 0x70, 0x6A, 0xA3, 0x28, 0x43, 0xAC, 0x7A
	.byte 0x20, 0x83, 0xBA, 0x90, 0x8A, 0x49, 0xAA, 0x1A, 0x41, 0x6E, 0x92, 0x21, 0xE8, 0xDA, 0x66, 0x70
	.byte 0x78, 0x32, 0x77, 0x66, 0x7F, 0xCD, 0xE4, 0x0C, 0x69, 0x20, 0x35, 0x9C, 0x9A, 0xC7, 0xDC, 0x1F
	.byte 0x4C, 0x73, 0x57, 0xB5, 0xBA, 0xFB, 0x44, 0x05, 0xBA, 0x06, 0x7B, 0x29, 0xAC, 0x5E, 0x04, 0x66
	.byte 0xC5, 0x77, 0x87, 0x6B, 0x3F, 0xE4, 0xC1, 0xEE, 0x8C, 0x22, 0x1A, 0x07, 0x63, 0xD5, 0xB6, 0xAF
	.byte 0x32, 0xA2, 0xFE, 0x6E, 0x38, 0x11, 0xF3, 0x45, 0x7C, 0xB5, 0x1C, 0x3D, 0x5C, 0x62, 0xFA, 0x7A
	.byte 0x2B, 0x4E, 0x8C, 0x92, 0x66, 0x60

	.thumb
	.global SVC_UncompressRL8
SVC_UncompressRL8: ; 0x02000374
	swi 20
	bx lr

	.byte 0x43, 0xA3, 0x40, 0x36, 0x0E, 0x7C, 0xAE, 0x48, 0x76, 0xF1, 0x9F, 0xF4, 0x6F, 0xA8, 0x27, 0x16
	.byte 0xDD, 0xEC, 0x04, 0x90, 0xA0, 0x83, 0x47, 0x9E, 0xE6, 0x5E, 0x84, 0x83, 0xDE, 0x53, 0x31, 0xFF
	.byte 0xFE, 0xF3, 0x6A, 0xB2, 0x00, 0xBC, 0x2C, 0x03, 0x94, 0x79, 0x0C, 0x82, 0xE4, 0x6A, 0xE2, 0xB6
	.byte 0x36, 0xFB, 0x39, 0x9B, 0xE0, 0xBC, 0xBF, 0x11, 0x07, 0x36, 0x4C, 0xD0, 0x88, 0xD7, 0x3D, 0x27
	.byte 0xDF, 0x72, 0x65, 0x63, 0x15, 0x7E, 0x5E, 0x1A, 0x52, 0xBA, 0xA8, 0xCA, 0xA1, 0xEA, 0x91, 0x2D
	.byte 0x86, 0x78, 0x86, 0xB8, 0xC1, 0x1B, 0x54, 0x44, 0xD6, 0xDA, 0xE5, 0x47, 0x2B, 0x18, 0x0D, 0xB8
	.byte 0x6B, 0xAB, 0x68, 0xCF, 0x27, 0x8D

	.thumb
	.global SVC_Halt
SVC_Halt: ; 0x020003DE
	swi 6
	bx lr

	.byte 0x5F, 0x28, 0xC9, 0x01, 0xDD, 0x41, 0xE2, 0x97, 0x5F, 0xEE, 0xA6, 0xC6, 0x20, 0x09, 0xB0, 0xC9
	.byte 0x56, 0xC1, 0x3F, 0x32, 0xBF, 0x1C, 0xD6, 0xF4, 0x1F, 0x0D, 0xD3, 0xA2, 0xBC, 0xA3, 0xBA, 0x4D
	.byte 0x7A, 0x75, 0xE9, 0xB6, 0x47, 0x5A, 0xDA, 0x7C, 0x43, 0x88, 0xFD, 0x04, 0x16, 0xA5, 0x8E, 0xC8
	.byte 0xE4, 0x11, 0xEB, 0x4F, 0x73, 0x9C, 0x7C, 0x70, 0x90, 0xC6, 0x01, 0x56, 0x3E, 0x29, 0xF0, 0x0B
	.byte 0xC4, 0xA1, 0x9F, 0x2D, 0x57, 0x65, 0xA7, 0x8B, 0xA4, 0xEC, 0x97, 0xDB, 0x80, 0xA6, 0xC3, 0x1A
	.byte 0x5A, 0x6D, 0xBE, 0x22, 0x94, 0x34, 0xC4, 0x84, 0x7B, 0x39, 0xDE, 0xB5, 0x00, 0x16, 0xB0, 0x5B
	.byte 0xE4, 0xE1, 0xF4, 0xB6, 0xE8, 0x02, 0x2A, 0xBF, 0x10, 0x0C, 0x34, 0x6D, 0x42, 0xF5, 0xC5, 0x60

	.thumb
	.global SVC_Div
SVC_Div: ; 0x02000452
	swi 9
	bx lr

	.byte 0x4E, 0xC7, 0xBB, 0x05, 0x37, 0xAE, 0x1C, 0x8C, 0x47, 0x91, 0xCF, 0x51, 0x1C, 0x20, 0xC6, 0xD4
	.byte 0x66, 0x00, 0xD3, 0x84, 0x92, 0x0C, 0xF4, 0xF8, 0x43, 0xBC, 0x47, 0x4D, 0x7A, 0xBC, 0xC8, 0x2B
	.byte 0x1D, 0x1D, 0xD3, 0x47, 0x14, 0xCF, 0x27, 0x41, 0x03, 0x89, 0xE8, 0xCD, 0xD4, 0x60, 0x6A, 0xBF
	.byte 0x96, 0xDD, 0x82, 0xE6, 0x13, 0x2C, 0x2D, 0xB7, 0xA9, 0xB0, 0xB2, 0x5D, 0xF0, 0x2A, 0x49, 0x22
	.byte 0xEC, 0xAE, 0x7C, 0x8E, 0xE7, 0x13, 0xE6, 0x56, 0x96, 0x65, 0x78, 0xA9, 0x68, 0x42, 0x59, 0x96
	.byte 0x82, 0x9C, 0xFF, 0xEE, 0x0F, 0xB2

	.thumb
	.global SVC_Sqrt
SVC_Sqrt: ; 0x020004AC
	swi 13
	bx lr

	.byte 0x64, 0x00, 0xAB, 0xE4, 0xBB, 0xA5, 0xF3, 0x44, 0x45, 0x5D, 0xA2, 0xBE, 0x0A, 0x71, 0xB5, 0xFB
	.byte 0xAE, 0x64, 0x4B, 0xF4, 0x05, 0xA3, 0x21, 0x4F, 0x4F, 0x6A, 0x62, 0xA7, 0x72, 0xFE, 0xD9, 0x98
	.byte 0x37, 0x36, 0x79, 0xFC, 0xE7, 0x9C, 0xBB, 0xFB, 0x98, 0x1B, 0x6D, 0x03, 0xBE, 0x96, 0x72, 0x69
	.byte 0xC7, 0x69, 0x1A, 0xFA, 0x15, 0x84, 0x37, 0xA2, 0x1C, 0x6F, 0x83, 0xCF, 0x02, 0x4D, 0xCF, 0x5F
	.byte 0x4E, 0x41, 0xE0, 0x7C, 0x30, 0xE8, 0x3C, 0xB0, 0x24, 0x76, 0x7A, 0x4D, 0xAF, 0x20, 0xD3, 0x7D
	.byte 0x08, 0x2B, 0xA5, 0x1D, 0xA1, 0xC6, 0x60, 0xD2, 0x72, 0xC6

	.thumb
	.global SVC_WaitByLoop
SVC_WaitByLoop: ; 0x0200050A
	swi 3
	bx lr

	.byte 0x25, 0x1F, 0xBA, 0x2C, 0x1B, 0x23, 0xC3, 0xFE, 0x7D, 0xED, 0x2E, 0x19, 0xE1, 0x77, 0xBE, 0x6A
	.byte 0x0D, 0x4B, 0xBA, 0x67, 0x8E, 0x98, 0xC0, 0x40, 0x29, 0x30, 0x80, 0xD1, 0x7E, 0xCD, 0x76, 0xB2
	.byte 0xE6, 0xC9, 0x20, 0x88, 0xCC, 0x25, 0x62, 0x6E, 0xCF, 0xC1, 0x1F, 0x35, 0x08, 0x8F, 0x18, 0x40
	.byte 0x41, 0x30, 0x03, 0xAE, 0xE0, 0x5A, 0xB7, 0x03, 0xCB, 0x18, 0x83, 0x98, 0xCB, 0x25, 0x9B, 0xD0
	.byte 0xC6, 0x7B, 0xE0, 0x7B, 0x02, 0x86, 0xCE, 0x55, 0x80, 0x7F, 0x15, 0x64, 0x79, 0xC6, 0xBB, 0x2C
	.byte 0x25, 0xCA, 0x08, 0x51, 0x77, 0x56, 0x0C, 0x5F, 0x63, 0x91, 0x80, 0xF5, 0x5B, 0x66, 0xCD, 0x00
	.byte 0xDF, 0x32, 0x29, 0x7F, 0xEF, 0x32, 0x1D, 0xBB, 0xAA, 0xF3, 0xDC, 0xAC, 0xBF, 0xF4, 0xA1, 0x87
	.byte 0xF5, 0x59

	.thumb
	.global SVC_GetCRC16
SVC_GetCRC16: ; 0x02000580
	swi 14
	bx lr

	.byte 0xFF, 0x01, 0xBB, 0x78, 0xAC, 0xB6, 0x11, 0x1F, 0x37, 0xF3, 0x01, 0x06, 0xD0, 0x01, 0x00, 0x9A
	.byte 0xFD, 0xCB, 0x18, 0x06, 0x0A, 0xF4, 0xD6, 0x8D, 0x71, 0x57, 0xFE, 0xCA, 0xF2, 0x2B, 0xF2, 0xDF
	.byte 0xC7, 0xE8, 0x8A, 0x28, 0x52, 0x95, 0x19, 0xF1, 0x3B, 0xE6, 0x4E, 0x8B, 0xD2, 0x02, 0x54, 0x42
	.byte 0x02, 0x4A, 0x40, 0x04, 0xA6, 0x24, 0xC1, 0xDB, 0x7E, 0x6A, 0x73, 0x19, 0xD2, 0x18, 0x86, 0x48
	.byte 0x99, 0xC3, 0x7B, 0x35, 0x3A, 0x7B, 0x76, 0x35, 0x0C, 0x82, 0x53, 0xD0, 0x5D, 0xD9, 0x97, 0xBC
	.byte 0x48, 0x80, 0x4C, 0xD5

	.thumb
	.global SVC_CpuSetFast
SVC_CpuSetFast: ; 0x020005D8
	swi 12
	bx lr

	.byte 0x36, 0xF2, 0xD9, 0x9A, 0xDB, 0xAA, 0x63, 0xF2, 0xBD, 0x54, 0xFC, 0x40, 0x84, 0xB2, 0x35, 0xE5
	.byte 0x26, 0x36, 0x25, 0x89, 0x4B, 0x9C, 0xE2, 0x94, 0x28, 0x21, 0xB7, 0x46, 0x78, 0x4C, 0xBB, 0x52
	.byte 0x43, 0x6E, 0x23, 0x67, 0xDB, 0xEC, 0x8F, 0x93, 0xD2, 0xA2, 0x3A, 0xA5, 0x7D, 0x92, 0x97, 0x00
	.byte 0xAD, 0xDC, 0x3B, 0xF1, 0x37, 0x7E, 0x9E, 0x7B, 0x4E, 0xD0, 0xE2, 0xE9, 0x6B, 0xBC, 0xB7, 0x50
	.byte 0xE7, 0x00, 0x0C, 0x0A, 0x1E, 0xA5, 0x2D, 0x16, 0xB7, 0xF8, 0xBF, 0x54

	.thumb
	.global SVC_WaitIntr
SVC_WaitIntr: ; 0x02000628
	mov r2, #0
	swi 4
	bx lr

	.byte 0x8C, 0x18, 0xF9, 0x04, 0x15, 0x40, 0x93, 0x79, 0xC7, 0x6A, 0xA8, 0x38, 0x08, 0xD6, 0xB3, 0x87
	.byte 0xCB, 0xBB, 0x55, 0xDE, 0xF6, 0x4D, 0xBC, 0x95, 0xD7, 0x64, 0xE6, 0x66, 0xA5, 0xA5, 0xDA, 0x49
	.byte 0x77, 0x69, 0x14, 0x0F, 0x0C, 0xFE, 0x30, 0x61, 0x05, 0xA3, 0x72, 0xFB, 0x20, 0xB7, 0x1A, 0xE1
	.byte 0x5D, 0x17, 0xCC, 0x8A, 0x12, 0x36, 0x08, 0x63, 0x63, 0xE6, 0xA8, 0x09, 0x12, 0x62, 0x30, 0x4F
	.byte 0xAA, 0x47, 0x70, 0x67, 0x08, 0xE1, 0x35, 0x28, 0xFE, 0xFE, 0x24, 0x75, 0x14, 0x03, 0x40, 0x3E
	.byte 0x47, 0xEC, 0xC1, 0xA3, 0x4C, 0x42, 0xE9, 0xB0, 0x27, 0x33, 0x3F, 0xC1, 0xFC, 0xE8, 0x34, 0x66
	.byte 0xB7, 0xDB, 0xCB, 0x66, 0x6A, 0x9E, 0x2F, 0x5D, 0x69, 0xB4, 0x38, 0x57, 0x49, 0x1E, 0x0F, 0xBF
	.byte 0x4F, 0x98, 0x7F, 0x35, 0xB8, 0xAB, 0x7C, 0x02, 0xB4, 0x5B, 0xA9, 0x1F, 0x75, 0x00, 0xF1, 0x7D
	.byte 0xC7, 0x79, 0xFB, 0x23

	.thumb
	.global SVC_CpuSet
SVC_CpuSet: ; 0x020006B2
	swi 11
	bx lr

	.byte 0x41, 0x89, 0x4D, 0x99, 0x93, 0xBA, 0xCE, 0x99, 0xE6, 0xAF, 0x92, 0x54, 0x2F, 0x8E, 0xB3, 0xCD
	.byte 0x2E, 0xD0, 0x48, 0x52, 0x5B, 0xE6, 0xE1, 0x31, 0x6A, 0x30, 0xF8, 0x3B, 0x54, 0x0B, 0x4B, 0xC9
	.byte 0x17, 0x06, 0x9F, 0xA0, 0xAE, 0x24, 0xFF, 0x94, 0x33, 0x32, 0x41, 0x1D, 0x89, 0xAC, 0x9E, 0x42
	.byte 0xA4, 0x8E, 0x75, 0x48, 0x1F, 0x6E, 0x2A, 0xDB, 0xAC, 0x54, 0x55, 0x27, 0x36, 0xBB, 0x7F, 0x9D
	.byte 0x57, 0xD4, 0x32, 0x5B, 0xA9, 0x29, 0x15, 0x98, 0xBB, 0x9C, 0x93, 0x88, 0x62, 0x25, 0xA0, 0x8B
	.byte 0x2F, 0x19, 0xDF, 0x72, 0x7E, 0x73, 0x86, 0x0C, 0x1E, 0x5B, 0xA5, 0x9D, 0xF1, 0xCD, 0x45, 0x62
	.byte 0xE5, 0x62, 0xCA, 0xE4, 0x2F, 0x20, 0xCE, 0x44, 0x9F, 0xFC, 0x14, 0xCF, 0x0E, 0xD2, 0xC3, 0x56
	.byte 0x92, 0x29, 0x5A, 0xF1, 0x11, 0xDF, 0x70, 0x47, 0xC8, 0x58, 0x5C, 0x38, 0x05, 0x09, 0x09, 0x37
	.byte 0x19, 0x37, 0xE9, 0x0A, 0x56, 0xF5, 0x5F, 0x57, 0x9C, 0xA8, 0x91, 0x87, 0xFB, 0x03, 0xE3, 0xD2
	.byte 0x07, 0x4E, 0xC9, 0x39, 0x37, 0xC1, 0x50, 0x29, 0x1C, 0x36, 0x33, 0xBC, 0x57, 0x37, 0x82, 0xA4
	.byte 0x69, 0x2C, 0xA2, 0x3D, 0x05, 0x3E, 0xCE, 0x4C, 0x53, 0x89, 0x49, 0x3B, 0xCC, 0x15, 0xF2, 0xB5
	.byte 0xD6, 0x28, 0x97, 0x98, 0xFB, 0x28, 0xFA, 0xD4, 0x58, 0x1C, 0x29, 0x37, 0x0C, 0x52, 0xB4, 0xCA
	.byte 0x4B, 0x0B, 0x39, 0x6A, 0xDB, 0x40, 0xF9, 0xA2, 0xA3, 0x5B, 0x6C, 0x58, 0x17, 0x75, 0x8E, 0xB3
	.byte 0xF2, 0xF4, 0xA1, 0x39, 0x17, 0xD9, 0x7B, 0x9C

	.thumb
	.global IsMmemExpanded
IsMmemExpanded: ; 0x0200078E
	swi 15
	bx lr

	.byte 0x77, 0x04, 0xED, 0xD8, 0xD3, 0x0B, 0xEB, 0x51, 0x73, 0xA7, 0x84, 0x7E, 0x54, 0x52, 0xDE, 0x0B
	.byte 0x6F, 0xF4, 0xC4, 0x7F, 0xF6, 0x60, 0x00, 0xD6, 0x24, 0xD3, 0x41, 0x86, 0x99, 0xE8, 0x29, 0xAF
	.byte 0x5C, 0x16, 0xC1, 0x5D, 0x6E, 0xE6, 0x4B, 0x67, 0x51, 0xAC, 0xE4, 0xD6, 0x5B, 0x50, 0x6B, 0xDE
	.byte 0x27, 0x38, 0xF8, 0x0D, 0x0E, 0x81, 0xDB, 0x80, 0x93, 0xF0, 0xD8, 0x08, 0xA5, 0xF6, 0x7C, 0xE5
	.byte 0x34, 0xCC, 0x86, 0x4D, 0xDE, 0xC3, 0x81, 0xB4, 0xB7, 0x4B, 0x8B, 0x94, 0x41, 0xD8, 0x98, 0x7B
	.byte 0x5F, 0x79, 0x21, 0x3D, 0xC5, 0x92, 0xFC, 0x3B, 0x9A, 0x88, 0x54, 0x14, 0x40, 0x00, 0x3E, 0x7D
	.byte 0x98, 0xE4, 0x50, 0xA9, 0xA0, 0xB7, 0xCC, 0x79, 0x30, 0xFE, 0xAC, 0x85, 0x00, 0x00

	.endif