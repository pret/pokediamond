
	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	; 0x020EC710
	.global UNK_020EC710
UNK_020EC710: ; 0x020EC710
	.byte 0x20, 0xFF, 0x09, 0x60
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020EC718
UNK_020EC718: ; 0x020EC718
	.byte 0x00, 0xFF, 0x01, 0xB0
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020EC720
UNK_020EC720: ; 0x020EC720
	.byte 0x00, 0xFF, 0x01, 0xD0
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020EC728
UNK_020EC728: ; 0x020EC728
	.byte 0x20, 0xFF, 0x09, 0x60
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020EC730
UNK_020EC730: ; 0x020EC730
	.byte 0x20, 0xFF, 0x11, 0x68
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020EC738
UNK_020EC738: ; 0x020EC738
	.byte 0x20, 0xFF, 0x01, 0xB8
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020EC740
UNK_020EC740: ; 0x020EC740
	.byte 0x00, 0xFF, 0x05, 0x20
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020EC748
UNK_020EC748: ; 0x020EC748
	.word abort
	.short 37
	.word 0x00100000
	.word exit
	.short 77
	.word 0x00100100
	.word __exit
	.short 297
	.word 0x00200300
	.word nan
	.short 25
	.word 0x00000000
	.word __flush_line_buffered_output_files
	.short 141
	.word 0x00403F00
	.word __flush_all
	.short 105
	.word 0x00403F00
	.word __msl_assertion_failed
	.short 61
	.word 0x00200100
	.word __load_buffer
	.short 141
	.word 0x00200700
	.word __flush_buffer
	.short 137
	.word 0x00200300
	.word fread
	.short 269
	.word 0x00407F00
	.word __fread
	.short 841
	.word 0x00507F00
	.word __fwrite
	.short 689
	.word 0x0060FF00
	.word fclose
	.short 117
	.word 0x00200300
	.word fflush
	.short 233
	.word 0x00100100
	.word ftell
	.short 285
	.word 0x00300F00
	.word _fseek
	.short 489
	.word 0x00400320
	.word fseek
	.short 301
	.word 0x00403F00
	.word rewind
	.short 37
	.word 0x00100100
	.word mbtowc
	.short 29
	.word 0x00100000
	.word wctomb
	.short 29
	.word 0x00100000
	.word mbstowcs
	.short 137
	.word 0x00301F00
	.word wcstombs
	.short 121
	.word 0x00403F00
	.word memset
	.short 21
	.word 0x00100100
	.word long2str
	.short 589
	.word 0x0090FF20
	.word longlong2str
	.short 737
	.word 0x00A0FF20
	.word double2hex
	.short 1245
	.word 0x00F07F20
	.word float2str
	.short 1893
	.word 0x00C0FF20
	.word __pformatter
	.short 2084
	.word UNK_020EC710
	.word __FileWrite
	.short 45
	.word 0x00200300
	.word __StringWrite
	.short 69
	.word 0x00200300
	.word printf
	.short 281
	.word 0x00300120
	.word vsnprintf
	.short 105
	.word 0x00300300
	.word snprintf
	.short 41
	.word 0x00300020
	.word sprintf
	.short 45
	.word 0x00300020
	.word qsort
	.short 357
	.word 0x0070FF00
	.word __sformatter
	.short 3412
	.word UNK_020EC718
	.word vsscanf
	.short 85
	.word 0x00200000
	.word sscanf
	.short 41
	.word 0x00300020
	.word raise
	.short 305
	.word 0x00200300
	.word __strtold
	.short 4684
	.word UNK_020EC720
	.word strtold
	.short 225
	.word 0x00500F00
	.word atod
	.short 17
	.word 0x00000000
	.word __strtoul
	.short 1001
	.word 0x0060FF00
	.word __strtoull
	.short 1101
	.word 0x0080FF00
	.word strtoul
	.short 153
	.word 0x00600300
	.word strtold2
	.short 201
	.word 0x00600300
	.word atol
	.short 21
	.word 0x00000000
	.word wmemcpy
	.short 17
	.word 0x00000000
	.word long2str_wide
	.short 593
	.word 0x0090FF20
	.word longlong2str_wide
	.short 741
	.word 0x00A0FF20
	.word double2hex_wide
	.short 921
	.word 0x00F07F20
	.word float2str_wide
	.short 1612
	.word UNK_020EC728
	.word __wpformatter
	.short 2288
	.word UNK_020EC730
	.word __wStringWrite
	.short 65
	.word 0x00200300
	.word swprintf
	.short 41
	.word 0x00300020
	.word vswprintf
	.short 113
	.word 0x00300300
	.word __ieee754_pow
	.short 4488
	.word UNK_020EC738
	.word frexp
	.short 189
	.word 0x00300120
	.word ldexp
	.short 589
	.word 0x00300120
	.word pow
	.short 13
	.word 0x00000000
	.word __rounddec
	.short 65
	.word 0x00200300
	.word __ull2dec
	.short 205
	.word 0x0050FF00
	.word __timesdec
	.short 389
	.word 0x00D0FF00
	.word __str2dec
	.short 157
	.word 0x00100000
	.word __two_exp
	.short 901
	.word 0x00B00300
	.word __num2dec_internal
	.short 385
	.word 0x00E01F00
	.word __num2dec_internal2
	.short 169
	.word 0x00200300
	.word __dec2num
	.short 1572
	.word UNK_020EC740
	.word scalbn
	.short 45
	.word 0x00200100
	.word __read_console
	.short 81
	.word 0x00300F00
	.word __write_console
	.short 53
	.word 0x00200700
	.word __call_static_initializers
	.short 45
	.word 0x00100100
	.word __destroy_global_chain
	.short 69
	.word 0x00200300
	.word _ExitProcess
	.short 13
	.word 0x00000000

	.global UNK_020ECAC0
UNK_020ECAC0: ; 0x020ECAC0
	.byte 0x0A, 0x00, 0x00, 0x00

	.global UNK_020ECAC4
UNK_020ECAC4: ; 0x020ECAC4
	.byte 0x02, 0x00, 0x00, 0x00

	.global UNK_020ECAC8
UNK_020ECAC8: ; 0x020ECAC8
	.byte 0xFF, 0xFF, 0xFF, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0x00
	.byte 0x21, 0xFF, 0xFF, 0x00
	.byte 0x11, 0xF2, 0xFF, 0x00
	.byte 0x11, 0x21, 0xFF, 0x00
	.byte 0x11, 0x11, 0xF2, 0x00
	.byte 0x11, 0x11, 0x21, 0x00
	.byte 0x11, 0x11, 0x22, 0x00
	.byte 0x11, 0x21, 0xF2, 0x00
	.byte 0x11, 0x22, 0xFF, 0x00
	.byte 0x21, 0xF2, 0xFF, 0x00
	.byte 0x22, 0xFF, 0xFF, 0x00
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

