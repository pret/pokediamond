    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020FFA38
	.extern UNK_02105AF8
	.extern UNK_02105B00
	.extern UNK_02105B08
	.extern UNK_02105B10
	.extern UNK_02105B18
	.extern UNK_02105B20
	.extern UNK_02105B28
	.extern UNK_02105B30
	.extern UNK_02105B38
	.extern UNK_02105B40
	.extern UNK_02105B48
	.extern UNK_02105B78

	.section .rodata

	.global UNK_020ECF9C
UNK_020ECF9C: ; 0x020ECF9C
	.byte 0x00, 0xC0, 0x00

	.global UNK_020ECF9F
UNK_020ECF9F: ; 0x020ECF9F
	.byte 0x00, 0xC0, 0x01

	.global UNK_020ECFA2
UNK_020ECFA2: ; 0x020ECFA2
	.byte 0xC0, 0x00, 0x00

	.global UNK_020ECFA5
UNK_020ECFA5: ; 0x020ECFA5
	.byte 0xC0, 0x00, 0x01

	.global UNK_020ECFA8
UNK_020ECFA8: ; 0x020ECFA8
	.byte 0x60, 0x00, 0x01, 0x60, 0xC0, 0x01

	.global UNK_020ECFAE
UNK_020ECFAE: ; 0x020ECFAE
	.byte 0x00, 0x5E, 0x01, 0xC0, 0x62, 0x01

	.global UNK_020ECFB4
UNK_020ECFB4: ; 0x020ECFB4
	.byte 0x00, 0x60, 0x00, 0xC0, 0x60, 0x00

	.global UNK_020ECFBA
UNK_020ECFBA: ; 0x020ECFBA
	.byte 0x5E, 0x00, 0x00, 0x62, 0xC0, 0x00

	.global UNK_020ECFC0
UNK_020ECFC0: ; 0x020ECFC0
	.byte 0x00, 0x60, 0x01, 0xC0, 0x60, 0x01

	.global UNK_020ECFC6
UNK_020ECFC6: ; 0x020ECFC6
	.byte 0x60, 0x00, 0x00, 0x60, 0xC0, 0x00

	.global UNK_020ECFCC
UNK_020ECFCC: ; 0x020ECFCC
	.byte 0x40, 0x00, 0x00, 0x80, 0x40, 0x00, 0xC0, 0x80, 0x00

	.global UNK_020ECFD5
UNK_020ECFD5: ; 0x020ECFD5
	.byte 0x00, 0x40, 0x01, 0x40, 0x80, 0x01, 0x80, 0xC0, 0x01, 0x00, 0x00

	.global UNK_020ECFE0
UNK_020ECFE0: ; 0x020ECFE0
	.byte 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x20, 0x01

	.global UNK_020ECFEC
UNK_020ECFEC: ; 0x020ECFEC
	.byte 0x00, 0x00, 0x00, 0x00, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x20, 0x00

	.global UNK_020ECFF8
UNK_020ECFF8: ; 0x020ECFF8
	.byte 0x00, 0x00, 0x00, 0x00, 0x49, 0x7F, 0x00, 0x00, 0x20, 0x3F, 0x01, 0x00

	.global UNK_020ED004
UNK_020ED004: ; 0x020ED004
	.byte 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x20, 0x01

	.global UNK_020ED010
UNK_020ED010: ; 0x020ED010
	.byte 0x00, 0x00, 0x00, 0x00, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x20, 0x00

	.global UNK_020ED01C
UNK_020ED01C: ; 0x020ED01C
	.byte 0x00, 0x00, 0x00, 0x00, 0xFF, 0x1F, 0x00, 0x00, 0x3F, 0x20, 0x01, 0x00

	.global UNK_020ED028
UNK_020ED028: ; 0x020ED028
	.byte 0x00, 0x00, 0x00, 0x00, 0xFF, 0x1F, 0x00, 0x00, 0x20, 0x3F, 0x00, 0x00

	.global UNK_020ED034
UNK_020ED034: ; 0x020ED034
	.byte 0x00, 0x00, 0x00, 0x00, 0x49, 0x7F, 0x00, 0x00, 0x3F, 0x20, 0x00, 0x00

	.global UNK_020ED040
UNK_020ED040: ; 0x020ED040
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x80, 0x00, 0x60, 0x00, 0x00, 0x3F, 0x20, 0x00

	.global UNK_020ED050
UNK_020ED050: ; 0x020ED050
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x20, 0x01, 0x00, 0x3F, 0x20, 0x01

	.global UNK_020ED060
UNK_020ED060: ; 0x020ED060
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x80, 0x00, 0x20, 0x01, 0x00, 0x3F, 0x20, 0x00

	.global UNK_020ED070
UNK_020ED070: ; 0x020ED070
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x80, 0x00, 0xB0, 0xFF, 0x00, 0x3F, 0x20, 0x00

	.global UNK_020ED080
UNK_020ED080: ; 0x020ED080
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0xB0, 0xFF, 0x00, 0x3F, 0x20, 0x01

	.global UNK_020ED090
UNK_020ED090: ; 0x020ED090
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x60, 0x00, 0x00, 0x3F, 0x20, 0x01

	.global UNK_020ED0A0
UNK_020ED0A0: ; 0x020ED0A0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00
	.byte 0x00, 0x3F, 0x20, 0x01

	.global UNK_020ED0C4
UNK_020ED0C4: ; 0x020ED0C4
	.byte 0x80, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x3F, 0x20, 0x00

	.global UNK_020ED0E8
UNK_020ED0E8: ; 0x020ED0E8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x3F, 0x20, 0x01

	.global UNK_020ED10C
UNK_020ED10C: ; 0x020ED10C
	.byte 0x80, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x20, 0x3F, 0x01

	.global UNK_020ED130
UNK_020ED130: ; 0x020ED130
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x20, 0x3F, 0x01

	.global UNK_020ED154
UNK_020ED154: ; 0x020ED154
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x3F, 0x20, 0x00

	.global UNK_020ED178
UNK_020ED178: ; 0x020ED178
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00
	.byte 0x00, 0x20, 0x3F, 0x00

	.global UNK_020ED19C
UNK_020ED19C: ; 0x020ED19C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x20, 0x3F, 0x00

	.global UNK_020ED1C0
UNK_020ED1C0: ; 0x020ED1C0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x3F, 0x20, 0x01

	.global UNK_020ED1E4
UNK_020ED1E4: ; 0x020ED1E4
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x3F, 0x20, 0x00

	.global UNK_020ED208
UNK_020ED208: ; 0x020ED208
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x20, 0x3F, 0x01

	.global UNK_020ED22C
UNK_020ED22C: ; 0x020ED22C
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x01, 0x20, 0x3F, 0x01

	.global UNK_020ED250
UNK_020ED250: ; 0x020ED250
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x00, 0x20, 0x3F, 0x00

	.global UNK_020ED274
UNK_020ED274: ; 0x020ED274
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0x01, 0x20, 0x3F, 0x00

	.global UNK_020ED298
UNK_020ED298: ; 0x020ED298
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00

	.global UNK_020ED2D8
UNK_020ED2D8: ; 0x020ED2D8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00

	.global UNK_020ED318
UNK_020ED318: ; 0x020ED318
	.byte 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00

	.global UNK_020ED358
UNK_020ED358: ; 0x020ED358
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_0200E850
FUN_0200E850: ; 0x0200E850
	push {r3, lr}
	ldr r1, [r0, #0xc]
	cmp r1, #0x0
	bne _0200E866
	mov r1, #0x1
	str r1, [r0, #0x28]
	str r1, [r0, #0x2c]
	bl FUN_0200F20C
	mov r0, #0x0
	pop {r3, pc}
_0200E866:
	bl FUN_0200F2AC
	pop {r3, pc}

	thumb_func_start FUN_0200E86C
FUN_0200E86C: ; 0x0200E86C
	push {r3, lr}
	ldr r1, [r0, #0xc]
	cmp r1, #0x0
	bne _0200E884
	mov r1, #0x0
	str r1, [r0, #0x28]
	mov r2, #0x1
	str r2, [r0, #0x2c]
	bl FUN_0200F20C
	mov r0, #0x0
	pop {r3, pc}
_0200E884:
	bl FUN_0200F2AC
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0200E88C
FUN_0200E88C: ; 0x0200E88C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200E8B4
	ldr r1, _0200E8BC ; =UNK_020ECF9F
	ldr r0, _0200E8C0 ; =UNK_02105AF8
	str r1, [r0, #0x30]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200E8C4 ; =UNK_02105B28
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200E8B4:
	bl FUN_02010F70
	pop {r4, pc}
	nop
_0200E8BC: .word UNK_020ECF9F
_0200E8C0: .word UNK_02105AF8
_0200E8C4: .word UNK_02105B28

	thumb_func_start FUN_0200E8C8
FUN_0200E8C8: ; 0x0200E8C8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200E8EE
	ldr r1, _0200E8F4 ; =UNK_020ECF9C
	ldr r0, _0200E8F8 ; =UNK_02105AF8
	str r1, [r0, #0x40]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200E8FC ; =UNK_02105B38
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200E8EE:
	bl FUN_02010F70
	pop {r4, pc}
	.balign 4
_0200E8F4: .word UNK_020ECF9C
_0200E8F8: .word UNK_02105AF8
_0200E8FC: .word UNK_02105B38

	thumb_func_start FUN_0200E900
FUN_0200E900: ; 0x0200E900
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200E928
	ldr r1, _0200E930 ; =UNK_020ECFA5
	ldr r0, _0200E934 ; =UNK_02105AF8
	str r1, [r0, #0x48]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200E938 ; =UNK_02105B40
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200E928:
	bl FUN_02010F70
	pop {r4, pc}
	nop
_0200E930: .word UNK_020ECFA5
_0200E934: .word UNK_02105AF8
_0200E938: .word UNK_02105B40

	thumb_func_start FUN_0200E93C
FUN_0200E93C: ; 0x0200E93C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200E962
	ldr r1, _0200E968 ; =UNK_020ECFA2
	ldr r0, _0200E96C ; =UNK_02105AF8
	str r1, [r0, #0x38]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200E970 ; =UNK_02105B30
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200E962:
	bl FUN_02010F70
	pop {r4, pc}
	.balign 4
_0200E968: .word UNK_020ECFA2
_0200E96C: .word UNK_02105AF8
_0200E970: .word UNK_02105B30

	thumb_func_start FUN_0200E974
FUN_0200E974: ; 0x0200E974
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200E996
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200E99C ; =UNK_020ED0E8
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200E996:
	bl FUN_0200FD1C
	pop {r4, pc}
	.balign 4
_0200E99C: .word UNK_020ED0E8

	thumb_func_start FUN_0200E9A0
FUN_0200E9A0: ; 0x0200E9A0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200E9C0
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200E9C8 ; =UNK_020ED154
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200E9C0:
	bl FUN_0200FD1C
	pop {r4, pc}
	nop
_0200E9C8: .word UNK_020ED154

	thumb_func_start FUN_0200E9CC
FUN_0200E9CC: ; 0x0200E9CC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200E9F4
	ldr r1, _0200E9FC ; =UNK_020ECFC0
	ldr r0, _0200EA00 ; =UNK_02105AF8
	str r1, [r0, #0x20]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EA04 ; =UNK_02105B18
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200E9F4:
	bl FUN_02010F70
	pop {r4, pc}
	nop
_0200E9FC: .word UNK_020ECFC0
_0200EA00: .word UNK_02105AF8
_0200EA04: .word UNK_02105B18

	thumb_func_start FUN_0200EA08
FUN_0200EA08: ; 0x0200EA08
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EA2E
	ldr r1, _0200EA34 ; =UNK_020ECFC6
	ldr r0, _0200EA38 ; =UNK_02105AF8
	str r1, [r0, #0x28]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EA3C ; =UNK_02105B20
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EA2E:
	bl FUN_02010F70
	pop {r4, pc}
	.balign 4
_0200EA34: .word UNK_020ECFC6
_0200EA38: .word UNK_02105AF8
_0200EA3C: .word UNK_02105B20

	thumb_func_start FUN_0200EA40
FUN_0200EA40: ; 0x0200EA40
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EA68
	ldr r1, _0200EA70 ; =UNK_020ECFA8
	ldr r0, _0200EA74 ; =UNK_02105AF8
	str r1, [r0, #0x10]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EA78 ; =UNK_02105B08
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EA68:
	bl FUN_02010F70
	pop {r4, pc}
	nop
_0200EA70: .word UNK_020ECFA8
_0200EA74: .word UNK_02105AF8
_0200EA78: .word UNK_02105B08

	thumb_func_start FUN_0200EA7C
FUN_0200EA7C: ; 0x0200EA7C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EAA2
	ldr r1, _0200EAA8 ; =UNK_020ECFB4
	ldr r0, _0200EAAC ; =UNK_02105AF8
	str r1, [r0, #0x18]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EAB0 ; =UNK_02105B10
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EAA2:
	bl FUN_02010F70
	pop {r4, pc}
	.balign 4
_0200EAA8: .word UNK_020ECFB4
_0200EAAC: .word UNK_02105AF8
_0200EAB0: .word UNK_02105B10

	thumb_func_start FUN_0200EAB4
FUN_0200EAB4: ; 0x0200EAB4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EAD6
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EADC ; =UNK_020ED1C0
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EAD6:
	bl FUN_0200FD1C
	pop {r4, pc}
	.balign 4
_0200EADC: .word UNK_020ED1C0

	thumb_func_start FUN_0200EAE0
FUN_0200EAE0: ; 0x0200EAE0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EB00
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EB08 ; =UNK_020ED1E4
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EB00:
	bl FUN_0200FD1C
	pop {r4, pc}
	nop
_0200EB08: .word UNK_020ED1E4

	thumb_func_start FUN_0200EB0C
FUN_0200EB0C: ; 0x0200EB0C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EB30
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EB38 ; =UNK_020ED208
	ldr r2, _0200EB3C ; =UNK_020ED22C
	add r0, r4, #0x0
	bl FUN_0200FD6C
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EB30:
	bl FUN_0200FDC4
	pop {r4, pc}
	nop
_0200EB38: .word UNK_020ED208
_0200EB3C: .word UNK_020ED22C

	thumb_func_start FUN_0200EB40
FUN_0200EB40: ; 0x0200EB40
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EB62
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EB68 ; =UNK_020ED250
	ldr r2, _0200EB6C ; =UNK_020ED274
	add r0, r4, #0x0
	bl FUN_0200FD6C
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EB62:
	bl FUN_0200FDC4
	pop {r4, pc}
	.balign 4
_0200EB68: .word UNK_020ED250
_0200EB6C: .word UNK_020ED274

	thumb_func_start FUN_0200EB70
FUN_0200EB70: ; 0x0200EB70
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EB92
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EB98 ; =UNK_020ED090
	add r0, r4, #0x0
	bl FUN_0200FF18
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EB92:
	bl FUN_0200FF50
	pop {r4, pc}
	.balign 4
_0200EB98: .word UNK_020ED090

	thumb_func_start FUN_0200EB9C
FUN_0200EB9C: ; 0x0200EB9C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EBBC
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EBC4 ; =UNK_020ED040
	add r0, r4, #0x0
	bl FUN_0200FF18
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EBBC:
	bl FUN_0200FF50
	pop {r4, pc}
	nop
_0200EBC4: .word UNK_020ED040

	thumb_func_start FUN_0200EBC8
FUN_0200EBC8: ; 0x0200EBC8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EBEA
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EBF0 ; =UNK_020ED050
	add r0, r4, #0x0
	bl FUN_0200FF18
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EBEA:
	bl FUN_0200FF50
	pop {r4, pc}
	.balign 4
_0200EBF0: .word UNK_020ED050

	thumb_func_start FUN_0200EBF4
FUN_0200EBF4: ; 0x0200EBF4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EC14
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EC1C ; =UNK_020ED060
	add r0, r4, #0x0
	bl FUN_0200FF18
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EC14:
	bl FUN_0200FF50
	pop {r4, pc}
	nop
_0200EC1C: .word UNK_020ED060

	thumb_func_start FUN_0200EC20
FUN_0200EC20: ; 0x0200EC20
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EC42
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EC48 ; =UNK_020ECFE0
	add r0, r4, #0x0
	bl FUN_020101EC
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EC42:
	bl FUN_02010224
	pop {r4, pc}
	.balign 4
_0200EC48: .word UNK_020ECFE0

	thumb_func_start FUN_0200EC4C
FUN_0200EC4C: ; 0x0200EC4C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EC6C
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EC74 ; =UNK_020ECFEC
	add r0, r4, #0x0
	bl FUN_020101EC
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EC6C:
	bl FUN_02010224
	pop {r4, pc}
	nop
_0200EC74: .word UNK_020ECFEC

	thumb_func_start FUN_0200EC78
FUN_0200EC78: ; 0x0200EC78
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EC9A
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200ECA0 ; =UNK_020ED0A0
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EC9A:
	bl FUN_0200FD1C
	pop {r4, pc}
	.balign 4
_0200ECA0: .word UNK_020ED0A0

	thumb_func_start FUN_0200ECA4
FUN_0200ECA4: ; 0x0200ECA4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200ECC4
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200ECCC ; =UNK_020ED0C4
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200ECC4:
	bl FUN_0200FD1C
	pop {r4, pc}
	nop
_0200ECCC: .word UNK_020ED0C4

	thumb_func_start FUN_0200ECD0
FUN_0200ECD0: ; 0x0200ECD0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200ECF2
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200ECF8 ; =UNK_020ED10C
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200ECF2:
	bl FUN_0200FD1C
	pop {r4, pc}
	.balign 4
_0200ECF8: .word UNK_020ED10C

	thumb_func_start FUN_0200ECFC
FUN_0200ECFC: ; 0x0200ECFC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200ED1C
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200ED24 ; =UNK_020ED178
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200ED1C:
	bl FUN_0200FD1C
	pop {r4, pc}
	nop
_0200ED24: .word UNK_020ED178

	thumb_func_start FUN_0200ED28
FUN_0200ED28: ; 0x0200ED28
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200ED4A
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200ED50 ; =UNK_020ED004
	add r0, r4, #0x0
	bl FUN_020103F0
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200ED4A:
	bl FUN_02010428
	pop {r4, pc}
	.balign 4
_0200ED50: .word UNK_020ED004

	thumb_func_start FUN_0200ED54
FUN_0200ED54: ; 0x0200ED54
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200ED74
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200ED7C ; =UNK_020ED010
	add r0, r4, #0x0
	bl FUN_020103F0
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200ED74:
	bl FUN_02010428
	pop {r4, pc}
	nop
_0200ED7C: .word UNK_020ED010

	thumb_func_start FUN_0200ED80
FUN_0200ED80: ; 0x0200ED80
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EDC4
	ldr r0, _0200EDCC ; =UNK_020ED298
	mov r1, #0x4
	str r0, [sp, #0x0]
	ldr r0, _0200EDD0 ; =UNK_020ED2D8
	str r0, [sp, #0x4]
	add r0, sp, #0x0
	strb r1, [r0, #0x8]
	mov r1, #0x0
	strb r1, [r0, #0x9]
	mov r1, #0x3f
	strb r1, [r0, #0xa]
	mov r1, #0x20
	strb r1, [r0, #0xb]
	mov r1, #0x1
	strb r1, [r0, #0xc]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02010688
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	add sp, #0x10
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EDC4:
	bl FUN_020106C0
	add sp, #0x10
	pop {r4, pc}
	.balign 4
_0200EDCC: .word UNK_020ED298
_0200EDD0: .word UNK_020ED2D8

	thumb_func_start FUN_0200EDD4
FUN_0200EDD4: ; 0x0200EDD4
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EE14
	ldr r0, _0200EE1C ; =UNK_020ED318
	mov r1, #0x4
	str r0, [sp, #0x0]
	ldr r0, _0200EE20 ; =UNK_020ED358
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0x0
	strb r1, [r0, #0x8]
	strb r2, [r0, #0x9]
	mov r1, #0x3f
	strb r1, [r0, #0xa]
	mov r1, #0x20
	strb r1, [r0, #0xb]
	strb r2, [r0, #0xc]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02010688
	mov r0, #0x0
	str r0, [r4, #0x28]
	add sp, #0x10
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EE14:
	bl FUN_020106C0
	add sp, #0x10
	pop {r4, pc}
	.balign 4
_0200EE1C: .word UNK_020ED318
_0200EE20: .word UNK_020ED358

	thumb_func_start FUN_0200EE24
FUN_0200EE24: ; 0x0200EE24
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EE4C
	ldr r1, _0200EE54 ; =UNK_020ECFD5
	ldr r0, _0200EE58 ; =UNK_02105AF8
	str r1, [r0, #0x0]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EE5C ; =UNK_02105AF8
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EE4C:
	bl FUN_02010F70
	pop {r4, pc}
	nop
_0200EE54: .word UNK_020ECFD5
_0200EE58: .word UNK_02105AF8
_0200EE5C: .word UNK_02105AF8

	thumb_func_start FUN_0200EE60
FUN_0200EE60: ; 0x0200EE60
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EE86
	ldr r1, _0200EE8C ; =UNK_020ECFCC
	ldr r0, _0200EE90 ; =UNK_02105AF8
	str r1, [r0, #0x8]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EE94 ; =UNK_02105B00
	add r0, r4, #0x0
	bl FUN_02010F2C
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EE86:
	bl FUN_02010F70
	pop {r4, pc}
	.balign 4
_0200EE8C: .word UNK_020ECFCC
_0200EE90: .word UNK_02105AF8
_0200EE94: .word UNK_02105B00

	thumb_func_start FUN_0200EE98
FUN_0200EE98: ; 0x0200EE98
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EECA
	ldr r3, _0200EED4 ; =UNK_020ECFF8
	add r2, sp, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02010948
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	add sp, #0xc
	str r0, [r4, #0x2c]
	pop {r3-r4, pc}
_0200EECA:
	bl FUN_02010988
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_0200EED4: .word UNK_020ECFF8

	thumb_func_start FUN_0200EED8
FUN_0200EED8: ; 0x0200EED8
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EF08
	ldr r3, _0200EF10 ; =UNK_020ED034
	add r2, sp, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02010948
	mov r0, #0x0
	str r0, [r4, #0x28]
	add sp, #0xc
	str r0, [r4, #0x2c]
	pop {r3-r4, pc}
_0200EF08:
	bl FUN_02010988
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4
_0200EF10: .word UNK_020ED034

	thumb_func_start FUN_0200EF14
FUN_0200EF14: ; 0x0200EF14
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EF46
	ldr r3, _0200EF50 ; =UNK_020ED01C
	add r2, sp, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02010C7C
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	add sp, #0xc
	str r0, [r4, #0x2c]
	pop {r3-r4, pc}
_0200EF46:
	bl FUN_02010CBC
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_0200EF50: .word UNK_020ED01C

	thumb_func_start FUN_0200EF54
FUN_0200EF54: ; 0x0200EF54
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EF84
	ldr r3, _0200EF8C ; =UNK_020ED028
	add r2, sp, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02010C7C
	mov r0, #0x0
	str r0, [r4, #0x28]
	add sp, #0xc
	str r0, [r4, #0x2c]
	pop {r3-r4, pc}
_0200EF84:
	bl FUN_02010CBC
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4
_0200EF8C: .word UNK_020ED028

	thumb_func_start FUN_0200EF90
FUN_0200EF90: ; 0x0200EF90
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EFB2
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EFB8 ; =UNK_020ED080
	add r0, r4, #0x0
	bl FUN_0200FF18
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EFB2:
	bl FUN_0200FF50
	pop {r4, pc}
	.balign 4
_0200EFB8: .word UNK_020ED080

	thumb_func_start FUN_0200EFBC
FUN_0200EFBC: ; 0x0200EFBC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200EFDC
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200EFE4 ; =UNK_020ED070
	add r0, r4, #0x0
	bl FUN_0200FF18
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200EFDC:
	bl FUN_0200FF50
	pop {r4, pc}
	nop
_0200EFE4: .word UNK_020ED070

	thumb_func_start FUN_0200EFE8
FUN_0200EFE8: ; 0x0200EFE8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200F00A
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200F010 ; =UNK_020ED130
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200F00A:
	bl FUN_0200FD1C
	pop {r4, pc}
	.balign 4
_0200F010: .word UNK_020ED130

	thumb_func_start FUN_0200F014
FUN_0200F014: ; 0x0200F014
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200F034
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200F03C ; =UNK_020ED19C
	add r0, r4, #0x0
	bl FUN_0200FCC8
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200F034:
	bl FUN_0200FD1C
	pop {r4, pc}
	nop
_0200F03C: .word UNK_020ED19C

	thumb_func_start FUN_0200F040
FUN_0200F040: ; 0x0200F040
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200F068
	ldr r1, _0200F070 ; =UNK_020ECFAE
	ldr r0, _0200F074 ; =UNK_02105AF8
	str r1, [r0, #0x74]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200F078 ; =UNK_02105B48
	add r0, r4, #0x0
	bl FUN_020111AC
	mov r0, #0x1
	str r0, [r4, #0x28]
	mov r0, #0x0
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200F068:
	bl FUN_02011214
	pop {r4, pc}
	nop
_0200F070: .word UNK_020ECFAE
_0200F074: .word UNK_02105AF8
_0200F078: .word UNK_02105B48

	thumb_func_start FUN_0200F07C
FUN_0200F07C: ; 0x0200F07C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	bne _0200F0A2
	ldr r1, _0200F0A8 ; =UNK_020ECFBA
	ldr r0, _0200F0AC ; =UNK_02105B78
	str r1, [r0, #0x24]
	ldrh r0, [r4, #0x24]
	bl FUN_0200E420
	ldr r1, _0200F0B0 ; =UNK_02105B78
	add r0, r4, #0x0
	bl FUN_020111AC
	mov r0, #0x0
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	pop {r4, pc}
_0200F0A2:
	bl FUN_02011214
	pop {r4, pc}
	.balign 4
_0200F0A8: .word UNK_020ECFBA
_0200F0AC: .word UNK_02105B78
_0200F0B0: .word UNK_02105B78

	thumb_func_start FUN_0200F0B4
FUN_0200F0B4: ; 0x0200F0B4
	asr r0, r0, #0x4
	lsl r1, r0, #0x1
	lsl r0, r1, #0x1
	ldr r2, _0200F0C8 ; =UNK_020FFA38
	add r1, r1, #0x1
	lsl r1, r1, #0x1
	ldr r3, _0200F0CC ; =FX_Div
	ldrsh r0, [r2, r0]
	ldrsh r1, [r2, r1]
	bx r3
	.balign 4
_0200F0C8: .word UNK_020FFA38
_0200F0CC: .word FX_Div

	thumb_func_start FUN_0200F0D0
FUN_0200F0D0: ; 0x0200F0D0
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_0200F0B4
	lsl r2, r4, #0xc
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	asr r0, r1, #0xc
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0200F0F8
FUN_0200F0F8: ; 0x0200F0F8
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r1, #0x0
	add r7, r2, #0x0
	add r6, r3, #0x0
	bl FUN_0200F0B4
	cmp r6, r7
	bge _0200F142
	lsl r1, r6, #0x2
	str r0, [sp, #0x0]
	asr r0, r0, #0x1f
	lsl r4, r6, #0xc
	add r5, r5, r1
	str r0, [sp, #0x4]
_0200F116:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	asr r3, r4, #0x1f
	add r2, r4, #0x0
	bl _ll_mul
	mov r2, #0x2
	lsl r2, r2, #0xa
	add r0, r0, r2
	ldr r2, _0200F148 ; =0x00000000
	adc r1, r2
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	asr r0, r0, #0xc
	stmia r5!, {r0}
	mov r0, #0x1
	lsl r0, r0, #0xc
	add r6, r6, #0x1
	add r4, r4, r0
	cmp r6, r7
	blt _0200F116
_0200F142:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0200F148: .word 0x00000000

	thumb_func_start FUN_0200F14C
FUN_0200F14C: ; 0x0200F14C
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_0200F0B4
	add r1, r0, #0x0
	lsr r0, r4, #0x1f
	add r0, r4, r0
	asr r0, r0, #0x1
	lsl r0, r0, #0xc
	bl FX_Div
	pop {r4, pc}

	thumb_func_start FUN_0200F164
FUN_0200F164: ; 0x0200F164
	ldr r3, _0200F170 ; =_s32_div_f
	sub r0, r1, r0
	lsl r0, r0, #0x7
	add r1, r2, #0x0
	bx r3
	nop
_0200F170: .word _s32_div_f

	thumb_func_start FUN_0200F174
FUN_0200F174: ; 0x0200F174
	add r0, r0, r1
	bpl _0200F17A
	mov r0, #0x0
_0200F17A:
	cmp r0, #0xff
	ble _0200F180
	mov r0, #0xff
_0200F180:
	bx lr
	.balign 4

	thumb_func_start FUN_0200F184
FUN_0200F184: ; 0x0200F184
	ldr r3, [r0, #0x0]
	ldr r2, [r1, #0x0]
	add r2, r3, r2
	str r2, [r0, #0x0]
	ldr r3, [r0, #0x4]
	ldr r2, [r1, #0x4]
	add r2, r3, r2
	str r2, [r0, #0x4]
	ldr r3, [r0, #0x8]
	ldr r2, [r1, #0x8]
	add r2, r3, r2
	str r2, [r0, #0x8]
	ldr r2, [r0, #0xc]
	ldr r1, [r1, #0xc]
	add r1, r2, r1
	str r1, [r0, #0xc]
	bx lr
	.balign 4

	thumb_func_start FUN_0200F1A8
FUN_0200F1A8: ; 0x0200F1A8
	push {r3-r7, lr}
	add r7, r1, #0x0
	ldr r1, [sp, #0x1c]
	add r5, r3, #0x0
	str r1, [sp, #0x1c]
	ldr r1, [r5, #0x0]
	ldr r4, [sp, #0x18]
	lsl r1, r1, #0x7
	str r1, [r0, #0x0]
	ldr r1, [r5, #0x4]
	add r6, r2, #0x0
	lsl r1, r1, #0x7
	str r1, [r0, #0x4]
	ldr r1, [r5, #0x8]
	add r2, r4, #0x0
	lsl r1, r1, #0x7
	str r1, [r0, #0x8]
	ldr r1, [r5, #0xc]
	lsl r1, r1, #0x7
	str r1, [r0, #0xc]
	ldmia r2!, {r0-r1}
	stmia r7!, {r0-r1}
	ldmia r2!, {r0-r1}
	stmia r7!, {r0-r1}
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	ldr r2, [sp, #0x1c]
	bl FUN_0200F164
	str r0, [r6, #0x0]
	ldr r0, [r5, #0x4]
	ldr r1, [r4, #0x4]
	ldr r2, [sp, #0x1c]
	bl FUN_0200F164
	str r0, [r6, #0x4]
	ldr r0, [r5, #0x8]
	ldr r1, [r4, #0x8]
	ldr r2, [sp, #0x1c]
	bl FUN_0200F164
	str r0, [r6, #0x8]
	ldr r0, [r5, #0xc]
	ldr r1, [r4, #0xc]
	ldr r2, [sp, #0x1c]
	bl FUN_0200F164
	str r0, [r6, #0xc]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200F20C
FUN_0200F20C: ; 0x0200F20C
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r6, r1, #0x0
	mov r1, #0x1c
	bl FUN_02016998
	str r0, [r5, #0x14]
	mov r2, #0x1c
	mov r1, #0x0
_0200F220:
	strb r1, [r0, #0x0]
	add r0, r0, #0x1
	sub r2, r2, #0x1
	bne _0200F220
	ldr r4, [r5, #0x14]
	cmp r6, #0x0
	ldrh r1, [r5, #0x24]
	ldr r0, _0200F2A8 ; =0x00007FFF
	bne _0200F254
	cmp r1, r0
	bne _0200F23C
	mov r7, #0x10
	mov r6, #0x0
	b _0200F274
_0200F23C:
	cmp r1, #0x0
	bne _0200F248
	mov r7, #0xf
	mvn r7, r7
	mov r6, #0x0
	b _0200F274
_0200F248:
	mov r7, #0xf
	mvn r7, r7
	mov r6, #0x0
	bl ErrorHandling
	b _0200F274
_0200F254:
	cmp r1, r0
	bne _0200F25E
	mov r7, #0x0
	mov r6, #0x10
	b _0200F274
_0200F25E:
	cmp r1, #0x0
	bne _0200F26A
	mov r7, #0x0
	add r6, r7, #0x0
	sub r6, #0x10
	b _0200F274
_0200F26A:
	mov r7, #0x0
	add r6, r7, #0x0
	sub r6, #0x10
	bl ErrorHandling
_0200F274:
	ldr r0, [r5, #0x10]
	add r1, r7, #0x0
	bl FUN_0200E440
	ldr r0, [r5, #0x4]
	add r1, r6, #0x0
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x8]
	str r0, [r4, #0x4]
	mov r0, #0x0
	str r0, [r4, #0x8]
	lsl r0, r7, #0x7
	str r0, [r4, #0xc]
	lsl r0, r6, #0x7
	str r0, [r4, #0x10]
	ldr r2, [r5, #0x4]
	add r0, r7, #0x0
	bl FUN_0200F164
	str r0, [r4, #0x14]
	ldr r0, [r5, #0x10]
	str r0, [r4, #0x18]
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	pop {r3-r7, pc}
	.balign 4
_0200F2A8: .word 0x00007FFF

	thumb_func_start FUN_0200F2AC
FUN_0200F2AC: ; 0x0200F2AC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0xc]
	mov r4, #0x0
	ldr r0, [r5, #0x14]
	cmp r1, #0x1
	beq _0200F2C4
	cmp r1, #0x2
	beq _0200F2D4
	cmp r1, #0x3
	beq _0200F2E6
	b _0200F2E8
_0200F2C4:
	bl FUN_0200F2EC
	cmp r0, #0x1
	bne _0200F2E8
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200F2E8
_0200F2D4:
	bl FUN_02016A18
	add r0, r4, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r4, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200F2E8
_0200F2E6:
	mov r4, #0x1
_0200F2E8:
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0200F2EC
FUN_0200F2EC: ; 0x0200F2EC
	push {r4, lr}
	add r1, r0, #0x0
	ldr r0, [r1, #0x8]
	mov r4, #0x0
	add r2, r0, #0x1
	str r2, [r1, #0x8]
	ldr r0, [r1, #0x4]
	cmp r2, r0
	blt _0200F32A
	str r4, [r1, #0x8]
	ldr r0, [r1, #0x0]
	sub r0, r0, #0x1
	cmp r0, #0x0
	ble _0200F314
	str r0, [r1, #0x0]
	ldr r2, [r1, #0xc]
	ldr r0, [r1, #0x14]
	add r0, r2, r0
	str r0, [r1, #0xc]
	b _0200F31A
_0200F314:
	ldr r0, [r1, #0x10]
	mov r4, #0x1
	str r0, [r1, #0xc]
_0200F31A:
	ldr r2, [r1, #0xc]
	ldr r0, [r1, #0x18]
	asr r1, r2, #0x6
	lsr r1, r1, #0x19
	add r1, r2, r1
	asr r1, r1, #0x7
	bl FUN_0200E440
_0200F32A:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0200F330
FUN_0200F330: ; 0x0200F330
	push {r4-r6, lr}
	add r4, r0, #0x0
	bne _0200F33A
	bl ErrorHandling
_0200F33A:
	ldr r0, _0200F54C ; =0x04000006
	ldrh r0, [r0, #0x0]
	cmp r0, #0xc0
	bge _0200F3E0
	add r5, r0, #0x1
	cmp r5, #0xbf
	ble _0200F34A
	sub r5, #0xc0
_0200F34A:
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	bne _0200F3FA
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	ldr r3, [r4, #0x8]
	lsl r5, r5, #0x1
	mov r4, #0x6
	add r1, r0, r5
	lsl r4, r4, #0x6
	ldrsh r2, [r1, r4]
	lsl r4, r4, #0x2
	ldrsh r1, [r0, r5]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	ldr r0, _0200F550 ; =0x04000004
	bne _0200F3B4
	cmp r3, #0x0
	bne _0200F394
	ldrh r4, [r0, #0x0]
	mov r3, #0x2
	tst r3, r4
	beq _0200F3E0
	lsl r3, r1, #0x8
	mov r1, #0xff
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	orr r1, r3
	strh r1, [r0, #0x3c]
	mov r1, #0xc0
	add r0, #0x40
	strh r1, [r0, #0x0]
	pop {r4-r6, pc}
_0200F394:
	ldrh r3, [r0, #0x0]
	mov r0, #0x2
	tst r0, r3
	beq _0200F3E0
	mov r0, #0xff
	lsl r1, r1, #0x8
	lsl r0, r0, #0x8
	and r1, r0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	ldr r1, _0200F554 ; =0x04001040
	strh r0, [r1, #0x0]
	mov r0, #0xc0
	strh r0, [r1, #0x4]
	pop {r4-r6, pc}
_0200F3B4:
	cmp r3, #0x0
	bne _0200F3D8
	ldrh r4, [r0, #0x0]
	mov r3, #0x2
	tst r3, r4
	beq _0200F3E0
	lsl r3, r1, #0x8
	mov r1, #0xff
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	orr r1, r3
	strh r1, [r0, #0x3e]
	mov r1, #0xc0
	add r0, #0x42
	strh r1, [r0, #0x0]
	pop {r4-r6, pc}
_0200F3D8:
	ldrh r3, [r0, #0x0]
	mov r0, #0x2
	tst r0, r3
	bne _0200F3E2
_0200F3E0:
	b _0200F548
_0200F3E2:
	mov r0, #0xff
	lsl r1, r1, #0x8
	lsl r0, r0, #0x8
	and r1, r0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	ldr r1, _0200F558 ; =0x04001042
	strh r0, [r1, #0x0]
	mov r0, #0xc0
	strh r0, [r1, #0x4]
	pop {r4-r6, pc}
_0200F3FA:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	add r3, r0, #0x0
	lsl r5, r5, #0x1
	mov r6, #0x6
	add r1, r3, r5
	lsl r6, r6, #0x6
	ldrsh r2, [r1, r6]
	lsl r6, r6, #0x2
	ldrsh r1, [r3, r5]
	ldr r3, [r3, r6]
	ldr r0, [r4, #0x8]
	cmp r3, #0x0
	bne _0200F460
	cmp r0, #0x0
	ldr r0, _0200F550 ; =0x04000004
	bne _0200F440
	ldrh r6, [r0, #0x0]
	mov r3, #0x2
	tst r3, r6
	beq _0200F4A4
	lsl r3, r1, #0x8
	mov r1, #0xff
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	orr r1, r3
	strh r1, [r0, #0x3c]
	mov r1, #0xc0
	add r0, #0x40
	strh r1, [r0, #0x0]
	b _0200F4A4
_0200F440:
	ldrh r3, [r0, #0x0]
	mov r0, #0x2
	tst r0, r3
	beq _0200F4A4
	mov r0, #0xff
	lsl r1, r1, #0x8
	lsl r0, r0, #0x8
	and r1, r0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	ldr r1, _0200F554 ; =0x04001040
	strh r0, [r1, #0x0]
	mov r0, #0xc0
	strh r0, [r1, #0x4]
	b _0200F4A4
_0200F460:
	cmp r0, #0x0
	ldr r0, _0200F550 ; =0x04000004
	bne _0200F486
	ldrh r6, [r0, #0x0]
	mov r3, #0x2
	tst r3, r6
	beq _0200F4A4
	lsl r3, r1, #0x8
	mov r1, #0xff
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	orr r1, r3
	strh r1, [r0, #0x3e]
	mov r1, #0xc0
	add r0, #0x42
	strh r1, [r0, #0x0]
	b _0200F4A4
_0200F486:
	ldrh r3, [r0, #0x0]
	mov r0, #0x2
	tst r0, r3
	beq _0200F4A4
	mov r0, #0xff
	lsl r1, r1, #0x8
	lsl r0, r0, #0x8
	and r1, r0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	ldr r1, _0200F558 ; =0x04001042
	strh r0, [r1, #0x0]
	mov r0, #0xc0
	strh r0, [r1, #0x4]
_0200F4A4:
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0200F5D8
	ldr r3, [r4, #0x8]
	mov r4, #0x6
	add r1, r0, r5
	lsl r4, r4, #0x6
	ldrsh r2, [r1, r4]
	lsl r4, r4, #0x2
	ldrsh r1, [r0, r5]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	ldr r0, _0200F550 ; =0x04000004
	bne _0200F506
	cmp r3, #0x0
	bne _0200F4E6
	ldrh r4, [r0, #0x0]
	mov r3, #0x2
	tst r3, r4
	beq _0200F548
	lsl r3, r1, #0x8
	mov r1, #0xff
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	orr r1, r3
	strh r1, [r0, #0x3c]
	mov r1, #0xc0
	add r0, #0x40
	strh r1, [r0, #0x0]
	pop {r4-r6, pc}
_0200F4E6:
	ldrh r3, [r0, #0x0]
	mov r0, #0x2
	tst r0, r3
	beq _0200F548
	mov r0, #0xff
	lsl r1, r1, #0x8
	lsl r0, r0, #0x8
	and r1, r0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	ldr r1, _0200F554 ; =0x04001040
	strh r0, [r1, #0x0]
	mov r0, #0xc0
	strh r0, [r1, #0x4]
	pop {r4-r6, pc}
_0200F506:
	cmp r3, #0x0
	bne _0200F52A
	ldrh r4, [r0, #0x0]
	mov r3, #0x2
	tst r3, r4
	beq _0200F548
	lsl r3, r1, #0x8
	mov r1, #0xff
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	orr r1, r3
	strh r1, [r0, #0x3e]
	mov r1, #0xc0
	add r0, #0x42
	strh r1, [r0, #0x0]
	pop {r4-r6, pc}
_0200F52A:
	ldrh r3, [r0, #0x0]
	mov r0, #0x2
	tst r0, r3
	beq _0200F548
	mov r0, #0xff
	lsl r1, r1, #0x8
	lsl r0, r0, #0x8
	and r1, r0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	ldr r1, _0200F558 ; =0x04001042
	strh r0, [r1, #0x0]
	mov r0, #0xc0
	strh r0, [r1, #0x4]
_0200F548:
	pop {r4-r6, pc}
	nop
_0200F54C: .word 0x04000006
_0200F550: .word 0x04000004
_0200F554: .word 0x04001040
_0200F558: .word 0x04001042

	thumb_func_start FUN_0200F55C
FUN_0200F55C: ; 0x0200F55C
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x0
	beq _0200F572
	cmp r4, #0x1
	beq _0200F572
	cmp r4, #0x2
	beq _0200F58C
	pop {r4-r6, pc}
_0200F572:
	ldr r1, _0200F5B8 ; =0x00000604
	add r0, r3, #0x0
	bl FUN_02016998
	str r0, [r5, #0x0]
	mov r0, #0x1
	str r0, [r5, #0x4]
	str r6, [r5, #0x8]
	mov r0, #0x6
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x8
	str r4, [r1, r0]
	pop {r4-r6, pc}
_0200F58C:
	ldr r1, _0200F5BC ; =0x00000C08
	add r0, r3, #0x0
	bl FUN_02016998
	str r0, [r5, #0x0]
	mov r0, #0x2
	str r0, [r5, #0x4]
	mov r0, #0x6
	mov r3, #0x0
	lsl r0, r0, #0x8
	str r6, [r5, #0x8]
	add r4, r3, #0x0
	add r1, r0, #0x4
_0200F5A6:
	ldr r2, [r5, #0x0]
	add r2, r2, r4
	str r3, [r2, r0]
	add r3, r3, #0x1
	add r4, r4, r1
	cmp r3, #0x2
	blt _0200F5A6
	pop {r4-r6, pc}
	nop
_0200F5B8: .word 0x00000604
_0200F5BC: .word 0x00000C08

	thumb_func_start FUN_0200F5C0
FUN_0200F5C0: ; 0x0200F5C0
	ldr r3, _0200F5C4 ; =FUN_0200F5C8
	bx r3
	.balign 4
_0200F5C4: .word FUN_0200F5C8

	thumb_func_start FUN_0200F5C8
FUN_0200F5C8: ; 0x0200F5C8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_0200F5D8
FUN_0200F5D8: ; 0x0200F5D8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	add r4, r1, #0x0
	cmp r0, r4
	bgt _0200F5E8
	bl ErrorHandling
_0200F5E8:
	ldr r0, _0200F5F4 ; =0x00000604
	ldr r1, [r5, #0x0]
	mul r0, r4
	add r0, r1, r0
	pop {r3-r5, pc}
	nop
_0200F5F4: .word 0x00000604

	thumb_func_start FUN_0200F5F8
FUN_0200F5F8: ; 0x0200F5F8
	push {r3-r7, lr}
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x4]
	mov r4, #0x0
	cmp r0, #0x0
	ble _0200F624
	mov r7, #0x3
	lsl r7, r7, #0x8
	add r6, r7, #0x0
_0200F60C:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0200F5D8
	add r1, r0, r6
	add r2, r7, #0x0
	bl memcpy
	ldr r0, [r5, #0x4]
	add r4, r4, #0x1
	cmp r4, r0
	blt _0200F60C
_0200F624:
	ldr r0, [sp, #0x0]
	bl FUN_0200CAB4
	pop {r3-r7, pc}

	thumb_func_start FUN_0200F62C
FUN_0200F62C: ; 0x0200F62C
	push {r4-r5, lr}
	sub sp, #0xc
	add r5, r1, #0x0
	add r4, r2, #0x0
	cmp r0, #0x0
	bne _0200F644
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02011634
	add sp, #0xc
	pop {r4-r5, pc}
_0200F644:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02011634
	mov r2, #0x0
	add r0, r5, #0x0
	mov r1, #0x3f
	add r3, r2, #0x0
	str r4, [sp, #0x0]
	bl FUN_02011650
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	add r0, r5, #0x0
	add r2, r1, #0x0
	add r3, r1, #0x0
	str r4, [sp, #0x8]
	bl FUN_02011698
	add r0, r5, #0x0
	mov r1, #0x20
	mov r2, #0x0
	add r3, r4, #0x0
	bl FUN_02011678
	add sp, #0xc
	pop {r4-r5, pc}

	thumb_func_start FUN_0200F67C
FUN_0200F67C: ; 0x0200F67C
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r2, #0x0
	ldr r2, [sp, #0x34]
	add r6, r0, #0x0
	add r5, r3, #0x0
	ldr r4, [sp, #0x20]
	cmp r2, #0x0
	bne _0200F6B8
	add r0, r1, #0x0
	mov r1, #0x0
	add r2, r5, #0x0
	add r3, r4, #0x0
	bl FUN_020114AC
	add r0, r7, #0x0
	mov r1, #0x0
	add r2, r4, #0x0
	bl FUN_02011534
	str r5, [sp, #0x0]
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x2c]
	ldr r3, [sp, #0x30]
	str r4, [sp, #0x4]
	bl FUN_02011574
	add sp, #0xc
	pop {r4-r7, pc}
_0200F6B8:
	mov r2, #0x0
	str r4, [sp, #0x0]
	bl FUN_02011650
	add r0, r6, #0x0
	add r1, r7, #0x0
	mov r2, #0x0
	add r3, r4, #0x0
	bl FUN_02011678
	ldr r0, [sp, #0x30]
	ldr r1, [sp, #0x24]
	str r0, [sp, #0x0]
	str r5, [sp, #0x4]
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x2c]
	add r0, r6, #0x0
	str r4, [sp, #0x8]
	bl FUN_02011698
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0200F6E4
FUN_0200F6E4: ; 0x0200F6E4
	push {r3, lr}
	cmp r3, #0x0
	bne _0200F6F4
	add r0, r1, #0x0
	add r1, r2, #0x0
	bl FUN_02011480
	pop {r3, pc}
_0200F6F4:
	bl FUN_02011634
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0200F6FC
FUN_0200F6FC: ; 0x0200F6FC
	push {r3-r7, lr}
	add r4, r2, #0x0
	mov r2, #0xc3
	add r6, r1, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x2
	add r5, r0, #0x0
	add r7, r3, #0x0
	bl memset
	cmp r4, #0x1
	bne _0200F726
	mov r0, #0x6
	lsl r0, r0, #0x6
	str r7, [r5, r0]
	mov r0, #0xc2
	lsl r0, r0, #0x2
	strb r4, [r5, r0]
	add r0, r0, #0x1
	strb r6, [r5, r0]
	pop {r3-r7, pc}
_0200F726:
	mov r0, #0x6
	lsl r0, r0, #0x6
	str r7, [r5, r0]
	mov r0, #0xc1
	ldr r1, [sp, #0x18]
	lsl r0, r0, #0x2
	str r1, [r5, r0]
	add r1, r0, #0x4
	strb r4, [r5, r1]
	add r0, r0, #0x5
	strb r6, [r5, r0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200F740
FUN_0200F740: ; 0x0200F740
	ldr r3, _0200F74C ; =FUN_0200CA98
	add r1, r0, #0x0
	ldr r0, _0200F750 ; =FUN_0200F780
	ldr r2, _0200F754 ; =0x000003FF
	bx r3
	nop
_0200F74C: .word FUN_0200CA98
_0200F750: .word FUN_0200F780
_0200F754: .word 0x000003FF

	thumb_func_start FUN_0200F758
FUN_0200F758: ; 0x0200F758
	push {r3, lr}
	ldr r3, _0200F768 ; =0x00000309
	str r2, [sp, #0x0]
	ldrb r3, [r1, r3]
	ldr r2, _0200F76C ; =FUN_0200F7AC
	bl FUN_0200E6CC
	pop {r3, pc}
	.balign 4
_0200F768: .word 0x00000309
_0200F76C: .word FUN_0200F7AC

	thumb_func_start FUN_0200F770
FUN_0200F770: ; 0x0200F770
	ldr r3, _0200F778 ; =0x00000309
	ldrb r1, [r1, r3]
	ldr r3, _0200F77C ; =FUN_0200E6F8
	bx r3
	.balign 4
_0200F778: .word 0x00000309
_0200F77C: .word FUN_0200E6F8

	thumb_func_start FUN_0200F780
FUN_0200F780: ; 0x0200F780
	push {r3-r7, lr}
	mov r7, #0xc0
	add r6, r7, #0x0
	str r0, [sp, #0x0]
	add r5, r1, #0x0
	mov r4, #0x0
	add r6, #0xc4
_0200F78E:
	add r0, r5, #0x0
	add r0, #0xc0
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl memcpy
	add r4, r4, #0x1
	add r5, r5, r6
	cmp r4, #0x2
	blt _0200F78E
	ldr r0, [sp, #0x0]
	bl FUN_0200CAB4
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200F7AC
FUN_0200F7AC: ; 0x0200F7AC
	push {r3-r5, lr}
	add r4, r0, #0x0
	bne _0200F7B6
	bl ErrorHandling
_0200F7B6:
	ldr r0, _0200FAC0 ; =0x04000006
	ldrh r0, [r0, #0x0]
	cmp r0, #0xc0
	bge _0200F838
	add r0, r0, #0x1
	cmp r0, #0xbf
	ble _0200F7C6
	sub r0, #0xc0
_0200F7C6:
	mov r2, #0xc2
	lsl r2, r2, #0x2
	ldrb r1, [r4, r2]
	cmp r1, #0x1
	beq _0200F7D2
	b _0200F96C
_0200F7D2:
	add r0, r4, r0
	add r0, #0xc0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0200F8A2
	add r0, r2, #0x1
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	ldr r0, _0200FAC4 ; =0x04000004
	bne _0200F802
	ldrh r2, [r0, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200F81C
	add r0, #0x46
	ldrh r2, [r0, #0x0]
	mov r1, #0x3f
	bic r2, r1
	mov r1, #0x3f
	orr r2, r1
	mov r1, #0x20
	orr r1, r2
	strh r1, [r0, #0x0]
	b _0200F81C
_0200F802:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200F81C
	ldr r1, _0200FAC8 ; =0x0400104A
	mov r0, #0x3f
	ldrh r2, [r1, #0x0]
	bic r2, r0
	mov r0, #0x3f
	orr r2, r0
	mov r0, #0x20
	orr r0, r2
	strh r0, [r1, #0x0]
_0200F81C:
	ldr r0, _0200FACC ; =0x00000309
	ldrb r1, [r4, r0]
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	cmp r0, #0x0
	bne _0200F868
	cmp r1, #0x0
	bne _0200F84C
	ldr r2, _0200FAC4 ; =0x04000004
	mov r0, #0x2
	ldrh r1, [r2, #0x0]
	tst r0, r1
	bne _0200F83A
_0200F838:
	b _0200FCB0
_0200F83A:
	add r2, #0x44
	ldrh r1, [r2, #0x0]
	mov r0, #0x3f
	bic r1, r0
	mov r0, #0x20
	orr r1, r0
	orr r0, r1
	strh r0, [r2, #0x0]
	pop {r3-r5, pc}
_0200F84C:
	ldr r0, _0200FAC4 ; =0x04000004
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200F954
	ldr r1, _0200FAD0 ; =0x04001048
	mov r0, #0x3f
	ldrh r2, [r1, #0x0]
	bic r2, r0
	mov r0, #0x20
	orr r2, r0
	orr r0, r2
	strh r0, [r1, #0x0]
	pop {r3-r5, pc}
_0200F868:
	cmp r1, #0x0
	ldr r0, _0200FAC4 ; =0x04000004
	bne _0200F888
	ldrh r1, [r0, #0x0]
	mov r2, #0x2
	tst r1, r2
	beq _0200F954
	add r0, #0x44
	ldrh r3, [r0, #0x0]
	ldr r1, _0200FAD4 ; =0xFFFFC0FF
	and r3, r1
	lsl r1, r2, #0xc
	orr r3, r1
	orr r1, r3
	strh r1, [r0, #0x0]
	pop {r3-r5, pc}
_0200F888:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200F954
	ldr r2, _0200FAD0 ; =0x04001048
	ldr r0, _0200FAD4 ; =0xFFFFC0FF
	ldrh r1, [r2, #0x0]
	and r1, r0
	lsr r0, r2, #0xd
	orr r1, r0
	orr r0, r1
	strh r0, [r2, #0x0]
	pop {r3-r5, pc}
_0200F8A2:
	add r0, r2, #0x1
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	ldr r0, _0200FAC4 ; =0x04000004
	bne _0200F8C6
	ldrh r2, [r0, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200F8DE
	add r0, #0x46
	ldrh r2, [r0, #0x0]
	mov r1, #0x3f
	bic r2, r1
	mov r1, #0x20
	orr r2, r1
	orr r1, r2
	strh r1, [r0, #0x0]
	b _0200F8DE
_0200F8C6:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200F8DE
	ldr r1, _0200FAC8 ; =0x0400104A
	mov r0, #0x3f
	ldrh r2, [r1, #0x0]
	bic r2, r0
	mov r0, #0x20
	orr r2, r0
	orr r0, r2
	strh r0, [r1, #0x0]
_0200F8DE:
	ldr r0, _0200FACC ; =0x00000309
	ldrb r1, [r4, r0]
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	cmp r0, #0x0
	ldr r0, _0200FAC4 ; =0x04000004
	bne _0200F92A
	cmp r1, #0x0
	bne _0200F90E
	ldrh r2, [r0, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200F954
	add r0, #0x44
	ldrh r2, [r0, #0x0]
	mov r1, #0x3f
	bic r2, r1
	mov r1, #0x3f
	orr r2, r1
	mov r1, #0x20
	orr r1, r2
	strh r1, [r0, #0x0]
	pop {r3-r5, pc}
_0200F90E:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200F954
	ldr r1, _0200FAD0 ; =0x04001048
	mov r0, #0x3f
	ldrh r2, [r1, #0x0]
	bic r2, r0
	mov r0, #0x3f
	orr r2, r0
	mov r0, #0x20
	orr r0, r2
	strh r0, [r1, #0x0]
	pop {r3-r5, pc}
_0200F92A:
	cmp r1, #0x0
	bne _0200F94C
	ldrh r1, [r0, #0x0]
	mov r2, #0x2
	tst r1, r2
	beq _0200F954
	add r0, #0x44
	ldrh r3, [r0, #0x0]
	ldr r1, _0200FAD4 ; =0xFFFFC0FF
	and r3, r1
	mov r1, #0x3f
	lsl r1, r1, #0x8
	orr r3, r1
	lsl r1, r2, #0xc
	orr r1, r3
	strh r1, [r0, #0x0]
	pop {r3-r5, pc}
_0200F94C:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	bne _0200F956
_0200F954:
	b _0200FCB0
_0200F956:
	ldr r2, _0200FAD0 ; =0x04001048
	ldr r0, _0200FAD4 ; =0xFFFFC0FF
	ldrh r1, [r2, #0x0]
	and r1, r0
	mov r0, #0x3f
	lsl r0, r0, #0x8
	orr r1, r0
	lsr r0, r2, #0xd
	orr r0, r1
	strh r0, [r2, #0x0]
	pop {r3-r5, pc}
_0200F96C:
	add r1, r4, r0
	add r1, #0xc0
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	bne _0200FA38
	add r1, r2, #0x1
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	ldr r1, _0200FAC4 ; =0x04000004
	bne _0200F99C
	ldrh r3, [r1, #0x0]
	mov r2, #0x2
	tst r2, r3
	beq _0200F9B6
	add r1, #0x46
	ldrh r3, [r1, #0x0]
	mov r2, #0x3f
	bic r3, r2
	mov r2, #0x3f
	orr r3, r2
	mov r2, #0x20
	orr r2, r3
	strh r2, [r1, #0x0]
	b _0200F9B6
_0200F99C:
	ldrh r2, [r1, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200F9B6
	ldr r2, _0200FAC8 ; =0x0400104A
	mov r1, #0x3f
	ldrh r3, [r2, #0x0]
	bic r3, r1
	mov r1, #0x3f
	orr r3, r1
	mov r1, #0x20
	orr r1, r3
	strh r1, [r2, #0x0]
_0200F9B6:
	ldr r1, _0200FACC ; =0x00000309
	ldrb r2, [r4, r1]
	mov r1, #0x6
	lsl r1, r1, #0x6
	ldr r1, [r4, r1]
	cmp r1, #0x0
	ldr r1, _0200FAC4 ; =0x04000004
	bne _0200F9FE
	cmp r2, #0x0
	bne _0200F9E4
	ldrh r3, [r1, #0x0]
	mov r2, #0x2
	tst r2, r3
	beq _0200FA0A
	add r1, #0x44
	ldrh r3, [r1, #0x0]
	mov r2, #0x3f
	bic r3, r2
	mov r2, #0x20
	orr r3, r2
	orr r2, r3
	strh r2, [r1, #0x0]
	b _0200FB16
_0200F9E4:
	ldrh r2, [r1, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200FA0A
	ldr r2, _0200FAD0 ; =0x04001048
	mov r1, #0x3f
	ldrh r3, [r2, #0x0]
	bic r3, r1
	mov r1, #0x20
	orr r3, r1
	orr r1, r3
	strh r1, [r2, #0x0]
	b _0200FB16
_0200F9FE:
	cmp r2, #0x0
	bne _0200FA1E
	ldrh r2, [r1, #0x0]
	mov r3, #0x2
	tst r2, r3
	bne _0200FA0C
_0200FA0A:
	b _0200FB16
_0200FA0C:
	add r1, #0x44
	ldrh r5, [r1, #0x0]
	ldr r2, _0200FAD4 ; =0xFFFFC0FF
	and r5, r2
	lsl r2, r3, #0xc
	orr r5, r2
	orr r2, r5
	strh r2, [r1, #0x0]
	b _0200FB16
_0200FA1E:
	ldrh r2, [r1, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200FB16
	ldr r3, _0200FAD0 ; =0x04001048
	ldr r1, _0200FAD4 ; =0xFFFFC0FF
	ldrh r2, [r3, #0x0]
	and r2, r1
	lsr r1, r3, #0xd
	orr r2, r1
	orr r1, r2
	strh r1, [r3, #0x0]
	b _0200FB16
_0200FA38:
	add r1, r2, #0x1
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	ldr r1, _0200FAC4 ; =0x04000004
	bne _0200FA5C
	ldrh r3, [r1, #0x0]
	mov r2, #0x2
	tst r2, r3
	beq _0200FA74
	add r1, #0x46
	ldrh r3, [r1, #0x0]
	mov r2, #0x3f
	bic r3, r2
	mov r2, #0x20
	orr r3, r2
	orr r2, r3
	strh r2, [r1, #0x0]
	b _0200FA74
_0200FA5C:
	ldrh r2, [r1, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200FA74
	ldr r2, _0200FAC8 ; =0x0400104A
	mov r1, #0x3f
	ldrh r3, [r2, #0x0]
	bic r3, r1
	mov r1, #0x20
	orr r3, r1
	orr r1, r3
	strh r1, [r2, #0x0]
_0200FA74:
	ldr r1, _0200FACC ; =0x00000309
	ldrb r2, [r4, r1]
	mov r1, #0x6
	lsl r1, r1, #0x6
	ldr r1, [r4, r1]
	cmp r1, #0x0
	ldr r1, _0200FAC4 ; =0x04000004
	bne _0200FAD8
	cmp r2, #0x0
	bne _0200FAA4
	ldrh r3, [r1, #0x0]
	mov r2, #0x2
	tst r2, r3
	beq _0200FB16
	add r1, #0x44
	ldrh r3, [r1, #0x0]
	mov r2, #0x3f
	bic r3, r2
	mov r2, #0x3f
	orr r3, r2
	mov r2, #0x20
	orr r2, r3
	strh r2, [r1, #0x0]
	b _0200FB16
_0200FAA4:
	ldrh r2, [r1, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200FB16
	ldr r2, _0200FAD0 ; =0x04001048
	mov r1, #0x3f
	ldrh r3, [r2, #0x0]
	bic r3, r1
	mov r1, #0x3f
	orr r3, r1
	mov r1, #0x20
	orr r1, r3
	strh r1, [r2, #0x0]
	b _0200FB16
	.balign 4
_0200FAC0: .word 0x04000006
_0200FAC4: .word 0x04000004
_0200FAC8: .word 0x0400104A
_0200FACC: .word 0x00000309
_0200FAD0: .word 0x04001048
_0200FAD4: .word 0xFFFFC0FF
_0200FAD8:
	cmp r2, #0x0
	bne _0200FAFA
	ldrh r2, [r1, #0x0]
	mov r3, #0x2
	tst r2, r3
	beq _0200FB16
	add r1, #0x44
	ldrh r5, [r1, #0x0]
	ldr r2, _0200FCB4 ; =0xFFFFC0FF
	and r5, r2
	mov r2, #0x3f
	lsl r2, r2, #0x8
	orr r5, r2
	lsl r2, r3, #0xc
	orr r2, r5
	strh r2, [r1, #0x0]
	b _0200FB16
_0200FAFA:
	ldrh r2, [r1, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200FB16
	ldr r3, _0200FCB8 ; =0x04001048
	ldr r1, _0200FCB4 ; =0xFFFFC0FF
	ldrh r2, [r3, #0x0]
	and r2, r1
	mov r1, #0x3f
	lsl r1, r1, #0x8
	orr r2, r1
	lsr r1, r3, #0xd
	orr r1, r2
	strh r1, [r3, #0x0]
_0200FB16:
	mov r1, #0x61
	lsl r1, r1, #0x2
	add r1, r4, r1
	add r0, r1, r0
	add r0, #0xc0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	ldr r0, _0200FCBC ; =0x00000309
	bne _0200FBEC
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	ldr r0, _0200FCC0 ; =0x04000004
	bne _0200FB4C
	ldrh r3, [r0, #0x0]
	mov r2, #0x2
	tst r2, r3
	beq _0200FB66
	add r0, #0x46
	ldrh r3, [r0, #0x0]
	mov r2, #0x3f
	bic r3, r2
	mov r2, #0x3f
	orr r3, r2
	mov r2, #0x20
	orr r2, r3
	strh r2, [r0, #0x0]
	b _0200FB66
_0200FB4C:
	ldrh r2, [r0, #0x0]
	mov r0, #0x2
	tst r0, r2
	beq _0200FB66
	ldr r2, _0200FCC4 ; =0x0400104A
	mov r0, #0x3f
	ldrh r3, [r2, #0x0]
	bic r3, r0
	mov r0, #0x3f
	orr r3, r0
	mov r0, #0x20
	orr r0, r3
	strh r0, [r2, #0x0]
_0200FB66:
	ldr r0, _0200FCBC ; =0x00000309
	ldrb r2, [r4, r0]
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r0, [r1, r0]
	cmp r0, #0x0
	bne _0200FBB2
	cmp r2, #0x0
	bne _0200FB94
	ldr r2, _0200FCC0 ; =0x04000004
	mov r0, #0x2
	ldrh r1, [r2, #0x0]
	tst r0, r1
	beq _0200FB9E
	add r2, #0x44
	ldrh r1, [r2, #0x0]
	mov r0, #0x3f
	bic r1, r0
	mov r0, #0x20
	orr r1, r0
	orr r0, r1
	strh r0, [r2, #0x0]
	pop {r3-r5, pc}
_0200FB94:
	ldr r0, _0200FCC0 ; =0x04000004
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	bne _0200FBA0
_0200FB9E:
	b _0200FCB0
_0200FBA0:
	ldr r1, _0200FCB8 ; =0x04001048
	mov r0, #0x3f
	ldrh r2, [r1, #0x0]
	bic r2, r0
	mov r0, #0x20
	orr r2, r0
	orr r0, r2
	strh r0, [r1, #0x0]
	pop {r3-r5, pc}
_0200FBB2:
	cmp r2, #0x0
	ldr r0, _0200FCC0 ; =0x04000004
	bne _0200FBD2
	ldrh r1, [r0, #0x0]
	mov r2, #0x2
	tst r1, r2
	beq _0200FCB0
	add r0, #0x44
	ldrh r3, [r0, #0x0]
	ldr r1, _0200FCB4 ; =0xFFFFC0FF
	and r3, r1
	lsl r1, r2, #0xc
	orr r3, r1
	orr r1, r3
	strh r1, [r0, #0x0]
	pop {r3-r5, pc}
_0200FBD2:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200FCB0
	ldr r2, _0200FCB8 ; =0x04001048
	ldr r0, _0200FCB4 ; =0xFFFFC0FF
	ldrh r1, [r2, #0x0]
	and r1, r0
	lsr r0, r2, #0xd
	orr r1, r0
	orr r0, r1
	strh r0, [r2, #0x0]
	pop {r3-r5, pc}
_0200FBEC:
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	ldr r0, _0200FCC0 ; =0x04000004
	bne _0200FC0E
	ldrh r3, [r0, #0x0]
	mov r2, #0x2
	tst r2, r3
	beq _0200FC26
	add r0, #0x46
	ldrh r3, [r0, #0x0]
	mov r2, #0x3f
	bic r3, r2
	mov r2, #0x20
	orr r3, r2
	orr r2, r3
	strh r2, [r0, #0x0]
	b _0200FC26
_0200FC0E:
	ldrh r2, [r0, #0x0]
	mov r0, #0x2
	tst r0, r2
	beq _0200FC26
	ldr r2, _0200FCC4 ; =0x0400104A
	mov r0, #0x3f
	ldrh r3, [r2, #0x0]
	bic r3, r0
	mov r0, #0x20
	orr r3, r0
	orr r0, r3
	strh r0, [r2, #0x0]
_0200FC26:
	ldr r0, _0200FCBC ; =0x00000309
	ldrb r2, [r4, r0]
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r0, [r1, r0]
	cmp r0, #0x0
	ldr r0, _0200FCC0 ; =0x04000004
	bne _0200FC72
	cmp r2, #0x0
	bne _0200FC56
	ldrh r2, [r0, #0x0]
	mov r1, #0x2
	tst r1, r2
	beq _0200FCB0
	add r0, #0x44
	ldrh r2, [r0, #0x0]
	mov r1, #0x3f
	bic r2, r1
	mov r1, #0x3f
	orr r2, r1
	mov r1, #0x20
	orr r1, r2
	strh r1, [r0, #0x0]
	pop {r3-r5, pc}
_0200FC56:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200FCB0
	ldr r1, _0200FCB8 ; =0x04001048
	mov r0, #0x3f
	ldrh r2, [r1, #0x0]
	bic r2, r0
	mov r0, #0x3f
	orr r2, r0
	mov r0, #0x20
	orr r0, r2
	strh r0, [r1, #0x0]
	pop {r3-r5, pc}
_0200FC72:
	cmp r2, #0x0
	bne _0200FC94
	ldrh r1, [r0, #0x0]
	mov r2, #0x2
	tst r1, r2
	beq _0200FCB0
	add r0, #0x44
	ldrh r3, [r0, #0x0]
	ldr r1, _0200FCB4 ; =0xFFFFC0FF
	and r3, r1
	mov r1, #0x3f
	lsl r1, r1, #0x8
	orr r3, r1
	lsl r1, r2, #0xc
	orr r1, r3
	strh r1, [r0, #0x0]
	pop {r3-r5, pc}
_0200FC94:
	ldrh r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0200FCB0
	ldr r2, _0200FCB8 ; =0x04001048
	ldr r0, _0200FCB4 ; =0xFFFFC0FF
	ldrh r1, [r2, #0x0]
	and r1, r0
	mov r0, #0x3f
	lsl r0, r0, #0x8
	orr r1, r0
	lsr r0, r2, #0xd
	orr r0, r1
	strh r0, [r2, #0x0]
_0200FCB0:
	pop {r3-r5, pc}
	nop
_0200FCB4: .word 0xFFFFC0FF
_0200FCB8: .word 0x04001048
_0200FCBC: .word 0x00000309
_0200FCC0: .word 0x04000004
_0200FCC4: .word 0x0400104A

	thumb_func_start FUN_0200FCC8
FUN_0200FCC8: ; 0x0200FCC8
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r6, r1, #0x0
	mov r1, #0x4c
	bl FUN_02016998
	str r0, [r5, #0x14]
	add r4, r0, #0x0
	ldr r0, [r5, #0x10]
	add r1, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	add r0, r4, #0x0
	bl FUN_0200FE20
	add r6, #0x20
	ldrb r0, [r6, #0x0]
	cmp r0, #0x0
	ldr r0, [r5, #0x18]
	bne _0200FD06
	ldr r2, [r4, #0x30]
	ldr r3, [r4, #0x44]
	mov r1, #0x1
	bl FUN_0200F6E4
	b _0200FD10
_0200FD06:
	ldr r2, [r4, #0x30]
	ldr r3, [r4, #0x44]
	mov r1, #0x2
	bl FUN_0200F6E4
_0200FD10:
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0200FD1C
FUN_0200FD1C: ; 0x0200FD1C
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _0200FD34
	cmp r0, #0x2
	beq _0200FD50
	cmp r0, #0x3
	beq _0200FD64
	b _0200FD66
_0200FD34:
	add r0, r4, #0x0
	bl FUN_0200FE90
	cmp r0, #0x1
	bne _0200FD66
	ldr r0, [r4, #0x44]
	ldr r1, [r5, #0x18]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200FD66
_0200FD50:
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200FD66
_0200FD64:
	mov r6, #0x1
_0200FD66:
	add r0, r6, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0200FD6C
FUN_0200FD6C: ; 0x0200FD6C
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r6, r1, #0x0
	mov r1, #0x98
	add r7, r2, #0x0
	bl FUN_02016998
	str r0, [r5, #0x14]
	add r4, r0, #0x0
	ldr r0, [r5, #0x10]
	add r1, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	add r0, r4, #0x0
	bl FUN_0200FE20
	ldr r0, [r5, #0x10]
	add r1, r7, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	add r0, #0x4c
	bl FUN_0200FE20
	ldr r0, [r5, #0x18]
	ldr r2, [r5, #0x10]
	ldr r3, [r4, #0x44]
	mov r1, #0x3
	bl FUN_0200F6E4
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200FDC4
FUN_0200FDC4: ; 0x0200FDC4
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _0200FDDC
	cmp r0, #0x2
	beq _0200FE04
	cmp r0, #0x3
	beq _0200FE18
	b _0200FE1A
_0200FDDC:
	add r0, r4, #0x0
	bl FUN_0200FE90
	add r7, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x4c
	bl FUN_0200FE90
	add r0, r7, r0
	cmp r0, #0x2
	bne _0200FE1A
	ldr r0, [r4, #0x44]
	ldr r1, [r5, #0x18]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200FE1A
_0200FE04:
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200FE1A
_0200FE18:
	mov r6, #0x1
_0200FE1A:
	add r0, r6, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200FE20
FUN_0200FE20: ; 0x0200FE20
	push {r3-r7, lr}
	sub sp, #0x18
	add r4, r1, #0x0
	add r1, #0x10
	add r7, r3, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	str r1, [sp, #0x0]
	add r1, r5, #0x0
	add r2, r5, #0x0
	add r1, #0x20
	add r2, #0x10
	add r3, r4, #0x0
	str r6, [sp, #0x4]
	bl FUN_0200F1A8
	ldr r1, [sp, #0x30]
	add r0, r4, #0x0
	add r2, r4, #0x0
	str r1, [r5, #0x30]
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	add r2, #0x23
	str r0, [r5, #0x34]
	str r6, [r5, #0x38]
	str r7, [r5, #0x3c]
	mov r0, #0x0
	str r0, [r5, #0x40]
	ldr r0, [sp, #0x34]
	str r0, [r5, #0x48]
	ldrb r2, [r2, #0x0]
	str r2, [r5, #0x44]
	str r1, [sp, #0x0]
	ldr r1, [r4, #0x0]
	add r2, r4, #0x0
	str r1, [sp, #0x4]
	ldr r1, [r4, #0x4]
	add r2, #0x22
	str r1, [sp, #0x8]
	ldr r1, [r4, #0x8]
	str r1, [sp, #0xc]
	ldr r1, [r4, #0xc]
	str r1, [sp, #0x10]
	ldr r1, [r5, #0x44]
	str r1, [sp, #0x14]
	add r1, r4, #0x0
	add r1, #0x21
	add r4, #0x20
	ldrb r1, [r1, #0x0]
	ldrb r2, [r2, #0x0]
	ldrb r3, [r4, #0x0]
	bl FUN_0200F67C
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200FE90
FUN_0200FE90: ; 0x0200FE90
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r1, [r4, #0x40]
	add r2, r1, #0x1
	str r2, [r4, #0x40]
	ldr r1, [r4, #0x3c]
	cmp r2, r1
	blt _0200FF10
	mov r1, #0x0
	str r1, [r4, #0x40]
	ldr r1, [r4, #0x38]
	sub r1, r1, #0x1
	cmp r1, #0x0
	ble _0200FEBA
	str r1, [r4, #0x38]
	add r1, r4, #0x0
	add r1, #0x10
	bl FUN_0200F184
	b _0200FED8
_0200FEBA:
	ldr r0, [r4, #0x2c]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x34]
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x30]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x48]
	ldr r1, [r4, #0x20]
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x28]
	bl FUN_02011698
	add sp, #0xc
	mov r0, #0x1
	pop {r3-r4, pc}
_0200FED8:
	ldr r1, [r4, #0xc]
	asr r0, r1, #0x6
	lsr r0, r0, #0x19
	add r0, r1, r0
	asr r0, r0, #0x7
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x34]
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x30]
	str r0, [sp, #0x8]
	ldr r2, [r4, #0x0]
	ldr r3, [r4, #0x4]
	asr r1, r2, #0x6
	lsr r1, r1, #0x19
	add r1, r2, r1
	ldr r0, [r4, #0x48]
	asr r2, r3, #0x6
	lsr r2, r2, #0x19
	add r2, r3, r2
	ldr r4, [r4, #0x8]
	asr r1, r1, #0x7
	asr r3, r4, #0x6
	lsr r3, r3, #0x19
	add r3, r4, r3
	asr r2, r2, #0x7
	asr r3, r3, #0x7
	bl FUN_02011698
_0200FF10:
	mov r0, #0x0
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0200FF18
FUN_0200FF18: ; 0x0200FF18
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r4, r1, #0x0
	mov r1, #0x38
	bl FUN_02016998
	str r0, [r5, #0x14]
	ldr r0, [r5, #0x10]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	bl FUN_0200FFAC
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_0200FF50
FUN_0200FF50: ; 0x0200FF50
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _0200FF68
	cmp r0, #0x2
	beq _0200FF84
	cmp r0, #0x3
	beq _0200FF9E
	b _0200FFA2
_0200FF68:
	add r0, r4, #0x0
	bl FUN_02010084
	cmp r0, #0x1
	bne _0200FFA6
	ldr r0, [r4, #0x2c]
	ldr r1, [r4, #0x30]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200FFA6
_0200FF84:
	add r0, r4, #0x0
	bl FUN_0200F5C0
	ldr r0, [r5, #0x14]
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0200FFA6
_0200FF9E:
	mov r6, #0x1
	b _0200FFA6
_0200FFA2:
	bl ErrorHandling
_0200FFA6:
	add r0, r6, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0200FFAC
FUN_0200FFAC: ; 0x0200FFAC
	push {r4-r7, lr}
	sub sp, #0x24
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x4]
	str r2, [sp, #0x18]
	str r3, [sp, #0x1c]
	ldr r6, [sp, #0x38]
	ldr r7, [sp, #0x3c]
	bl FUN_0200F164
	str r0, [sp, #0x20]
	ldrb r1, [r4, #0xc]
	ldr r3, [sp, #0x44]
	add r0, r5, #0x0
	add r2, r6, #0x0
	bl FUN_0200F55C
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x7
	str r0, [r5, #0xc]
	mov r0, #0x8
	ldrsh r0, [r4, r0]
	str r0, [r5, #0x10]
	mov r0, #0xa
	ldrsh r0, [r4, r0]
	str r0, [r5, #0x14]
	ldr r0, [sp, #0x20]
	str r0, [r5, #0x18]
	ldr r0, [sp, #0x18]
	str r0, [r5, #0x1c]
	ldr r0, [sp, #0x1c]
	str r0, [r5, #0x20]
	mov r0, #0x0
	str r0, [r5, #0x24]
	ldr r0, [sp, #0x40]
	str r7, [r5, #0x30]
	str r0, [r5, #0x34]
	ldr r0, [sp, #0x44]
	str r0, [r5, #0x28]
	ldrb r0, [r4, #0xf]
	str r0, [r5, #0x2c]
	add r0, r5, #0x0
	bl FUN_02010168
	ldr r0, _02010078 ; =FUN_0200F5F8
	ldr r2, _0201007C ; =0x000003FF
	add r1, r5, #0x0
	bl FUN_0200CA98
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	mov r1, #0x3
	str r6, [sp, #0x0]
	lsl r1, r1, #0x8
	ldrsh r1, [r0, r1]
	str r1, [sp, #0x4]
	mov r1, #0x0
	str r1, [sp, #0x8]
	mov r1, #0x12
	lsl r1, r1, #0x6
	ldrsh r0, [r0, r1]
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x2c]
	str r0, [sp, #0x14]
	ldrb r1, [r4, #0xd]
	ldrb r2, [r4, #0xe]
	ldrb r3, [r4, #0xc]
	add r0, r7, #0x0
	bl FUN_0200F67C
	ldrb r0, [r4, #0xc]
	cmp r0, #0x0
	bne _02010058
	ldr r3, [r5, #0x2c]
	add r0, r7, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_0200F6E4
	b _02010064
_02010058:
	ldr r3, [r5, #0x2c]
	add r0, r7, #0x0
	mov r1, #0x2
	add r2, r6, #0x0
	bl FUN_0200F6E4
_02010064:
	ldr r0, [sp, #0x44]
	ldr r2, _02010080 ; =FUN_0200F330
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x34]
	add r1, r5, #0x0
	add r3, r6, #0x0
	bl FUN_0200E6CC
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_02010078: .word FUN_0200F5F8
_0201007C: .word 0x000003FF
_02010080: .word FUN_0200F330

	thumb_func_start FUN_02010084
FUN_02010084: ; 0x02010084
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x24]
	add r2, r1, #0x1
	str r2, [r4, #0x24]
	ldr r1, [r4, #0x20]
	cmp r2, r1
	blt _020100C8
	mov r1, #0x0
	str r1, [r4, #0x24]
	ldr r1, [r4, #0x1c]
	sub r1, r1, #0x1
	cmp r1, #0x0
	ble _020100BA
	str r1, [r4, #0x1c]
	ldr r2, [r4, #0xc]
	ldr r1, [r4, #0x18]
	add r1, r2, r1
	str r1, [r4, #0xc]
	bl FUN_02010168
	ldr r0, _020100CC ; =FUN_0200F5F8
	ldr r2, _020100D0 ; =0x000003FF
	add r1, r4, #0x0
	bl FUN_0200CA98
	b _020100C8
_020100BA:
	ldr r0, [r4, #0x34]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x28]
	bl FUN_0200E6F8
	mov r0, #0x1
	pop {r4, pc}
_020100C8:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_020100CC: .word FUN_0200F5F8
_020100D0: .word 0x000003FF

	thumb_func_start FUN_020100D4
FUN_020100D4: ; 0x020100D4
	push {r4-r7, lr}
	sub sp, #0xc
	str r1, [sp, #0x0]
	asr r1, r0, #0x6
	lsr r1, r1, #0x19
	add r1, r0, r1
	asr r1, r1, #0x7
	ldr r5, [sp, #0x20]
	ldr r4, [sp, #0x24]
	sub r0, r3, r2
	bpl _020100EC
	neg r0, r0
_020100EC:
	cmp r0, r1
	blt _020100FA
	mov r0, #0x0
	str r0, [r5, #0x0]
	add sp, #0xc
	str r0, [r4, #0x0]
	pop {r4-r7, pc}
_020100FA:
	lsl r0, r0, #0xc
	str r0, [sp, #0x4]
	asr r7, r0, #0x1f
	lsl r0, r1, #0xc
	asr r1, r0, #0x1f
	add r2, r0, #0x0
	add r3, r1, #0x0
	bl _ll_mul
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x4]
	add r6, r1, #0x0
	add r1, r7, #0x0
	add r2, r0, #0x0
	add r3, r7, #0x0
	bl _ll_mul
	add r2, r0, #0x0
	add r3, r1, #0x0
	mov r0, #0x2
	ldr r1, [sp, #0x8]
	mov r7, #0x0
	lsl r0, r0, #0xa
	add r0, r1, r0
	adc r6, r7
	lsl r1, r6, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	mov r1, #0x2
	lsl r1, r1, #0xa
	add r2, r2, r1
	adc r3, r7
	lsl r1, r3, #0x14
	lsr r2, r2, #0xc
	orr r2, r1
	sub r0, r0, r2
	bl FX_Sqrt
	asr r2, r0, #0xc
	ldr r0, [sp, #0x0]
	sub r0, r0, r2
	str r0, [r5, #0x0]
	bpl _02010154
	add r0, r7, #0x0
	str r0, [r5, #0x0]
_02010154:
	ldr r1, [r5, #0x0]
	lsl r0, r2, #0x1
	add r0, r1, r0
	str r0, [r4, #0x0]
	cmp r0, #0xff
	ble _02010164
	mov r0, #0xff
	str r0, [r4, #0x0]
_02010164:
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_02010168
FUN_02010168: ; 0x02010168
	push {r3-r7, lr}
	sub sp, #0x10
	mov r1, #0x0
	add r5, r0, #0x0
	bl FUN_0200F5D8
	add r7, r0, #0x0
	mov r4, #0x0
	add r6, r7, #0x0
_0201017A:
	ldr r2, [r5, #0x14]
	cmp r4, r2
	bgt _02010194
	add r0, sp, #0xc
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	ldr r0, [r5, #0xc]
	ldr r1, [r5, #0x10]
	add r3, r4, #0x0
	bl FUN_020100D4
	b _020101CE
_02010194:
	lsl r0, r2, #0x1
	cmp r4, r0
	bgt _020101BC
	sub r0, r0, r4
	lsl r0, r0, #0x1
	add r1, r7, r0
	mov r0, #0x3
	lsl r0, r0, #0x8
	ldrsh r0, [r1, r0]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	lsl r0, r0, #0x1
	sub r0, r0, r4
	lsl r0, r0, #0x1
	add r1, r7, r0
	mov r0, #0x12
	lsl r0, r0, #0x6
	ldrsh r0, [r1, r0]
	str r0, [sp, #0x8]
	b _020101CE
_020101BC:
	add r0, sp, #0xc
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	ldr r0, [r5, #0xc]
	ldr r1, [r5, #0x10]
	add r3, r4, #0x0
	bl FUN_020100D4
_020101CE:
	mov r0, #0x3
	ldr r1, [sp, #0xc]
	lsl r0, r0, #0x8
	strh r1, [r6, r0]
	mov r0, #0x12
	ldr r1, [sp, #0x8]
	lsl r0, r0, #0x6
	strh r1, [r6, r0]
	add r4, r4, #0x1
	add r6, r6, #0x2
	cmp r4, #0xc0
	blt _0201017A
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020101EC
FUN_020101EC: ; 0x020101EC
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r4, r1, #0x0
	mov r1, #0x30
	bl FUN_02016998
	str r0, [r5, #0x14]
	ldr r0, [r5, #0x10]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	bl FUN_02010280
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_02010224
FUN_02010224: ; 0x02010224
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _0201023C
	cmp r0, #0x2
	beq _02010258
	cmp r0, #0x3
	beq _02010272
	b _02010276
_0201023C:
	add r0, r4, #0x0
	bl FUN_02010348
	cmp r0, #0x1
	bne _0201027A
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0x24]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0201027A
_02010258:
	add r0, r4, #0x0
	bl FUN_0200F5C0
	ldr r0, [r5, #0x14]
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0201027A
_02010272:
	mov r6, #0x1
	b _0201027A
_02010276:
	bl ErrorHandling
_0201027A:
	add r0, r6, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02010280
FUN_02010280: ; 0x02010280
	push {r3-r7, lr}
	sub sp, #0x20
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x4]
	str r2, [sp, #0x18]
	str r3, [sp, #0x1c]
	ldr r6, [sp, #0x38]
	ldr r7, [sp, #0x3c]
	bl FUN_0200F164
	str r0, [r5, #0x10]
	ldrb r1, [r4, #0x8]
	ldr r3, [sp, #0x44]
	add r0, r5, #0x0
	add r2, r6, #0x0
	bl FUN_0200F55C
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x7
	str r0, [r5, #0xc]
	ldr r0, [sp, #0x18]
	str r0, [r5, #0x14]
	ldr r0, [sp, #0x1c]
	str r0, [r5, #0x18]
	mov r0, #0x0
	str r0, [r5, #0x1c]
	ldr r0, [sp, #0x40]
	str r7, [r5, #0x24]
	str r0, [r5, #0x28]
	ldr r0, [sp, #0x44]
	str r0, [r5, #0x2c]
	ldrb r0, [r4, #0xb]
	str r0, [r5, #0x20]
	add r0, r5, #0x0
	bl FUN_02010398
	ldr r0, _0201033C ; =FUN_0200F5F8
	ldr r2, _02010340 ; =0x000003FF
	add r1, r5, #0x0
	bl FUN_0200CA98
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	mov r1, #0x3
	str r6, [sp, #0x0]
	lsl r1, r1, #0x8
	ldrsh r1, [r0, r1]
	str r1, [sp, #0x4]
	mov r1, #0x0
	str r1, [sp, #0x8]
	mov r1, #0x12
	lsl r1, r1, #0x6
	ldrsh r0, [r0, r1]
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0x14]
	ldrb r1, [r4, #0x9]
	ldrb r2, [r4, #0xa]
	ldrb r3, [r4, #0x8]
	add r0, r7, #0x0
	bl FUN_0200F67C
	ldrb r0, [r4, #0x8]
	cmp r0, #0x0
	bne _0201031C
	ldr r3, [r5, #0x20]
	add r0, r7, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_0200F6E4
	b _02010328
_0201031C:
	ldr r3, [r5, #0x20]
	add r0, r7, #0x0
	mov r1, #0x2
	add r2, r6, #0x0
	bl FUN_0200F6E4
_02010328:
	ldr r0, [sp, #0x44]
	ldr r2, _02010344 ; =FUN_0200F330
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x28]
	add r1, r5, #0x0
	add r3, r6, #0x0
	bl FUN_0200E6CC
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4
_0201033C: .word FUN_0200F5F8
_02010340: .word 0x000003FF
_02010344: .word FUN_0200F330

	thumb_func_start FUN_02010348
FUN_02010348: ; 0x02010348
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x1c]
	add r2, r1, #0x1
	str r2, [r4, #0x1c]
	ldr r1, [r4, #0x18]
	cmp r2, r1
	blt _0201038C
	mov r1, #0x0
	str r1, [r4, #0x1c]
	ldr r1, [r4, #0x14]
	sub r1, r1, #0x1
	cmp r1, #0x0
	ble _0201037E
	str r1, [r4, #0x14]
	ldr r2, [r4, #0xc]
	ldr r1, [r4, #0x10]
	add r1, r2, r1
	str r1, [r4, #0xc]
	bl FUN_02010398
	ldr r0, _02010390 ; =FUN_0200F5F8
	ldr r2, _02010394 ; =0x000003FF
	add r1, r4, #0x0
	bl FUN_0200CA98
	b _0201038C
_0201037E:
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x2c]
	bl FUN_0200E6F8
	mov r0, #0x1
	pop {r4, pc}
_0201038C:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_02010390: .word FUN_0200F5F8
_02010394: .word 0x000003FF

	thumb_func_start FUN_02010398
FUN_02010398: ; 0x02010398
	push {r3-r7, lr}
	sub sp, #0x1fc
	sub sp, #0x104
	add r4, r0, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	ldr r1, [r4, #0xc]
	add r5, r0, #0x0
	asr r0, r1, #0x6
	lsr r0, r0, #0x19
	add r0, r1, r0
	asr r0, r0, #0x7
	add r1, sp, #0x0
	mov r2, #0xc0
	mov r3, #0x0
	bl FUN_0200F0F8
	mov r7, #0x12
	mov r6, #0x0
	add r4, sp, #0x0
	lsl r7, r7, #0x6
_020103C4:
	ldr r1, [r4, #0x0]
	mov r0, #0x80
	neg r1, r1
	bl FUN_0200F174
	mov r1, #0x3
	lsl r1, r1, #0x8
	strh r0, [r5, r1]
	ldr r1, [r4, #0x0]
	mov r0, #0x80
	bl FUN_0200F174
	strh r0, [r5, r7]
	add r6, r6, #0x1
	add r4, r4, #0x4
	add r5, r5, #0x2
	cmp r6, #0xc0
	blt _020103C4
	add sp, #0x1fc
	add sp, #0x104
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020103F0
FUN_020103F0: ; 0x020103F0
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r4, r1, #0x0
	mov r1, #0x34
	bl FUN_02016998
	str r0, [r5, #0x14]
	ldr r0, [r5, #0x10]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	bl FUN_0201047C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_02010428
FUN_02010428: ; 0x02010428
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _02010440
	cmp r0, #0x2
	beq _0201045C
	cmp r0, #0x3
	beq _02010476
	b _02010478
_02010440:
	add r0, r4, #0x0
	bl FUN_02010550
	cmp r0, #0x1
	bne _02010478
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x28]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02010478
_0201045C:
	add r0, r4, #0x0
	bl FUN_0200F5C0
	ldr r0, [r5, #0x14]
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02010478
_02010476:
	mov r6, #0x1
_02010478:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0201047C
FUN_0201047C: ; 0x0201047C
	push {r4-r7, lr}
	sub sp, #0x24
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	str r2, [sp, #0x18]
	sub r0, r1, r0
	add r1, r2, #0x0
	str r3, [sp, #0x1c]
	ldr r6, [sp, #0x38]
	ldr r7, [sp, #0x3c]
	bl _s32_div_f
	str r0, [sp, #0x20]
	ldrb r1, [r4, #0x8]
	ldr r3, [sp, #0x44]
	add r0, r5, #0x0
	add r2, r6, #0x0
	bl FUN_0200F55C
	mov r0, #0x2
	lsl r0, r0, #0x12
	str r0, [r5, #0xc]
	ldr r0, [r4, #0x0]
	str r0, [r5, #0x10]
	ldr r0, [sp, #0x20]
	str r0, [r5, #0x14]
	ldr r0, [sp, #0x18]
	str r0, [r5, #0x18]
	ldr r0, [sp, #0x1c]
	str r0, [r5, #0x1c]
	mov r0, #0x0
	str r0, [r5, #0x20]
	ldr r0, [sp, #0x40]
	str r7, [r5, #0x28]
	str r0, [r5, #0x2c]
	ldr r0, [sp, #0x44]
	str r0, [r5, #0x30]
	ldrb r0, [r4, #0xb]
	str r0, [r5, #0x24]
	add r0, r5, #0x0
	bl FUN_020105A0
	ldr r0, _02010544 ; =FUN_0200F5F8
	ldr r2, _02010548 ; =0x000003FF
	add r1, r5, #0x0
	bl FUN_0200CA98
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	mov r1, #0xf
	str r6, [sp, #0x0]
	lsl r1, r1, #0x6
	ldrsh r1, [r0, r1]
	str r1, [sp, #0x4]
	mov r1, #0x0
	str r1, [sp, #0x8]
	mov r1, #0x15
	lsl r1, r1, #0x6
	ldrsh r0, [r0, r1]
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x24]
	str r0, [sp, #0x14]
	ldrb r1, [r4, #0x9]
	ldrb r2, [r4, #0xa]
	ldrb r3, [r4, #0x8]
	add r0, r7, #0x0
	bl FUN_0200F67C
	ldrb r0, [r4, #0x8]
	cmp r0, #0x0
	bne _02010524
	ldr r3, [r5, #0x24]
	add r0, r7, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_0200F6E4
	b _02010530
_02010524:
	ldr r3, [r5, #0x24]
	add r0, r7, #0x0
	mov r1, #0x2
	add r2, r6, #0x0
	bl FUN_0200F6E4
_02010530:
	ldr r0, [sp, #0x44]
	ldr r2, _0201054C ; =FUN_0200F330
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x2c]
	add r1, r5, #0x0
	add r3, r6, #0x0
	bl FUN_0200E6CC
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_02010544: .word FUN_0200F5F8
_02010548: .word 0x000003FF
_0201054C: .word FUN_0200F330

	thumb_func_start FUN_02010550
FUN_02010550: ; 0x02010550
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x20]
	add r2, r1, #0x1
	str r2, [r4, #0x20]
	ldr r1, [r4, #0x1c]
	cmp r2, r1
	blt _02010594
	mov r1, #0x0
	str r1, [r4, #0x20]
	ldr r1, [r4, #0x18]
	sub r1, r1, #0x1
	cmp r1, #0x0
	ble _02010586
	str r1, [r4, #0x18]
	ldr r2, [r4, #0x10]
	ldr r1, [r4, #0x14]
	add r1, r2, r1
	str r1, [r4, #0x10]
	bl FUN_020105A0
	ldr r0, _02010598 ; =FUN_0200F5F8
	ldr r2, _0201059C ; =0x000003FF
	add r1, r4, #0x0
	bl FUN_0200CA98
	b _02010594
_02010586:
	ldr r0, [r4, #0x2c]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x30]
	bl FUN_0200E6F8
	mov r0, #0x1
	pop {r4, pc}
_02010594:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_02010598: .word FUN_0200F5F8
_0201059C: .word 0x000003FF

	thumb_func_start FUN_020105A0
FUN_020105A0: ; 0x020105A0
	push {r4-r7, lr}
	sub sp, #0x1fc
	sub sp, #0x110
	add r4, r0, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x10]
	ldr r2, [r4, #0xc]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02010680 ; =UNK_020FFA38
	asr r3, r2, #0x1f
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	asr r7, r1, #0xc
	lsl r0, r7, #0x1
	mov r1, #0x15
	bl _s32_div_f
	add r0, r0, #0x1
	lsl r0, r0, #0x1
	mov r1, #0xb4
	sub r2, r1, r0
	ldr r0, _02010684 ; =0x0000FFFF
	add r1, #0xb4
	mul r0, r2
	bl _s32_div_f
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r4, r1, #0x1
	mov r1, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0x8
	bl FUN_0200F14C
	asr r0, r0, #0xc
	str r0, [sp, #0x4]
	cmp r0, #0xc0
	blt _0201060C
	bl ErrorHandling
_0201060C:
	ldr r2, [sp, #0x4]
	add r0, r4, #0x0
	add r1, sp, #0xc
	mov r3, #0x0
	bl FUN_0200F0F8
	ldr r5, [sp, #0x0]
	mov r4, #0x0
_0201061C:
	ldr r0, [sp, #0x4]
	add r1, r4, #0x1
	sub r0, r0, r1
	add r6, r7, #0x0
	cmp r0, #0x0
	ble _02010634
	lsl r1, r0, #0x2
	add r0, sp, #0xc
	ldr r0, [r0, r1]
	cmp r0, r7
	ble _02010634
	add r6, r0, #0x0
_02010634:
	mov r0, #0x80
	neg r1, r6
	bl FUN_0200F174
	str r0, [sp, #0x8]
	mov r0, #0x80
	add r1, r6, #0x0
	bl FUN_0200F174
	ldr r1, [sp, #0x8]
	lsl r0, r0, #0x10
	lsl r1, r1, #0x10
	asr r2, r1, #0x10
	mov r1, #0x3
	lsl r1, r1, #0x8
	strh r2, [r5, r1]
	asr r1, r0, #0x10
	mov r0, #0x12
	lsl r0, r0, #0x6
	strh r1, [r5, r0]
	mov r0, #0xbf
	sub r0, r0, r4
	lsl r3, r0, #0x1
	ldr r0, [sp, #0x0]
	add r4, r4, #0x1
	add r0, r0, r3
	mov r3, #0x3
	lsl r3, r3, #0x8
	strh r2, [r0, r3]
	mov r2, #0x12
	lsl r2, r2, #0x6
	add r5, r5, #0x2
	strh r1, [r0, r2]
	cmp r4, #0x60
	blt _0201061C
	add sp, #0x1fc
	add sp, #0x110
	pop {r4-r7, pc}
	.balign 4
_02010680: .word UNK_020FFA38
_02010684: .word 0x0000FFFF

	thumb_func_start FUN_02010688
FUN_02010688: ; 0x02010688
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r4, r1, #0x0
	mov r1, #0x30
	bl FUN_02016998
	str r0, [r5, #0x14]
	ldr r0, [r5, #0x10]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	bl FUN_02010720
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_020106C0
FUN_020106C0: ; 0x020106C0
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _020106D8
	cmp r0, #0x2
	beq _020106F4
	cmp r0, #0x3
	beq _02010714
	b _02010718
_020106D8:
	add r0, r4, #0x0
	bl FUN_02010834
	cmp r0, #0x1
	bne _0201071C
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0x24]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0201071C
_020106F4:
	add r0, r4, #0x0
	bl FUN_02010884
	add r0, r4, #0x0
	bl FUN_0200F5C0
	ldr r0, [r5, #0x14]
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _0201071C
_02010714:
	mov r6, #0x1
	b _0201071C
_02010718:
	bl ErrorHandling
_0201071C:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02010720
FUN_02010720: ; 0x02010720
	push {r4-r7, lr}
	sub sp, #0x24
	add r5, r1, #0x0
	add r7, r0, #0x0
	str r2, [sp, #0x18]
	ldr r0, [sp, #0x38]
	ldrb r2, [r5, #0x8]
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x44]
	mov r1, #0x30
	mul r1, r2
	str r3, [sp, #0x1c]
	str r0, [sp, #0x44]
	bl FUN_02016998
	str r0, [r7, #0xc]
	cmp r0, #0x0
	bne _02010748
	bl ErrorHandling
_02010748:
	ldrb r0, [r5, #0x8]
	str r0, [r7, #0x10]
	mov r0, #0x0
	str r0, [sp, #0x20]
	ldrb r0, [r5, #0x8]
	cmp r0, #0x0
	ble _02010788
	ldr r6, [sp, #0x20]
	add r4, r6, #0x0
_0201075A:
	ldr r0, [r5, #0x4]
	ldr r2, [r7, #0xc]
	add r0, r0, r6
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x18]
	str r0, [sp, #0x4]
	add r0, r2, r4
	ldr r3, [r5, #0x0]
	add r1, r0, #0x0
	add r2, r2, r4
	add r1, #0x20
	add r2, #0x10
	add r3, r3, r6
	bl FUN_0200F1A8
	ldr r0, [sp, #0x20]
	ldrb r1, [r5, #0x8]
	add r0, r0, #0x1
	add r6, #0x10
	add r4, #0x30
	str r0, [sp, #0x20]
	cmp r0, r1
	blt _0201075A
_02010788:
	ldrb r1, [r5, #0x9]
	ldr r2, [sp, #0x38]
	ldr r3, [sp, #0x44]
	add r0, r7, #0x0
	bl FUN_0200F55C
	ldr r0, [sp, #0x18]
	str r0, [r7, #0x14]
	ldr r0, [sp, #0x1c]
	str r0, [r7, #0x18]
	mov r0, #0x0
	str r0, [r7, #0x1c]
	ldr r0, [sp, #0x3c]
	str r0, [r7, #0x24]
	ldr r0, [sp, #0x40]
	str r0, [r7, #0x28]
	ldr r0, [sp, #0x44]
	str r0, [r7, #0x2c]
	ldrb r0, [r5, #0xc]
	str r0, [r7, #0x20]
	add r0, r7, #0x0
	bl FUN_02010894
	ldr r0, _02010828 ; =FUN_0200F5F8
	ldr r2, _0201082C ; =0x000003FF
	add r1, r7, #0x0
	bl FUN_0200CA98
	add r0, r7, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	ldr r1, [sp, #0x38]
	str r1, [sp, #0x0]
	mov r1, #0x3
	lsl r1, r1, #0x8
	ldrsh r1, [r0, r1]
	str r1, [sp, #0x4]
	mov r1, #0x0
	str r1, [sp, #0x8]
	mov r1, #0x12
	lsl r1, r1, #0x6
	ldrsh r0, [r0, r1]
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r7, #0x20]
	str r0, [sp, #0x14]
	ldrb r1, [r5, #0xa]
	ldrb r2, [r5, #0xb]
	ldrb r3, [r5, #0x9]
	ldr r0, [sp, #0x3c]
	bl FUN_0200F67C
	ldrb r0, [r5, #0x9]
	cmp r0, #0x0
	ldr r0, [r7, #0x24]
	bne _02010808
	ldr r2, [sp, #0x38]
	ldr r3, [r7, #0x20]
	mov r1, #0x1
	bl FUN_0200F6E4
	b _02010812
_02010808:
	ldr r2, [sp, #0x38]
	ldr r3, [r7, #0x20]
	mov r1, #0x2
	bl FUN_0200F6E4
_02010812:
	ldr r0, [sp, #0x44]
	ldr r2, _02010830 ; =FUN_0200F330
	str r0, [sp, #0x0]
	ldr r0, [r7, #0x28]
	ldr r3, [sp, #0x38]
	add r1, r7, #0x0
	bl FUN_0200E6CC
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_02010828: .word FUN_0200F5F8
_0201082C: .word 0x000003FF
_02010830: .word FUN_0200F330

	thumb_func_start FUN_02010834
FUN_02010834: ; 0x02010834
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x1c]
	add r2, r1, #0x1
	str r2, [r4, #0x1c]
	ldr r1, [r4, #0x18]
	cmp r2, r1
	blt _02010876
	mov r1, #0x0
	str r1, [r4, #0x1c]
	ldr r1, [r4, #0x14]
	sub r1, r1, #0x1
	cmp r1, #0x0
	ble _02010868
	str r1, [r4, #0x14]
	bl FUN_02010920
	add r0, r4, #0x0
	bl FUN_02010894
	ldr r0, _0201087C ; =FUN_0200F5F8
	ldr r2, _02010880 ; =0x000003FF
	add r1, r4, #0x0
	bl FUN_0200CA98
	b _02010876
_02010868:
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x2c]
	bl FUN_0200E6F8
	mov r0, #0x1
	pop {r4, pc}
_02010876:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0201087C: .word FUN_0200F5F8
_02010880: .word 0x000003FF

	thumb_func_start FUN_02010884
FUN_02010884: ; 0x02010884
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0xc]
	pop {r4, pc}

	thumb_func_start FUN_02010894
FUN_02010894: ; 0x02010894
	push {r4-r6, lr}
	mov r1, #0x0
	add r6, r0, #0x0
	bl FUN_0200F5D8
	mov r2, #0x3
	lsl r2, r2, #0x8
	add r0, r0, r2
	mov r1, #0x0
	bl memset
	ldr r0, [r6, #0x10]
	sub r4, r0, #0x1
	bmi _020108C6
	mov r0, #0x30
	add r5, r4, #0x0
	mul r5, r0
_020108B6:
	ldr r1, [r6, #0xc]
	add r0, r6, #0x0
	add r1, r1, r5
	bl FUN_020108C8
	sub r5, #0x30
	sub r4, r4, #0x1
	bpl _020108B6
_020108C6:
	pop {r4-r6, pc}

	thumb_func_start FUN_020108C8
FUN_020108C8: ; 0x020108C8
	push {r4-r6, lr}
	add r4, r1, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	ldr r2, [r4, #0x0]
	ldr r3, [r4, #0x8]
	asr r1, r2, #0x6
	lsr r1, r1, #0x19
	add r1, r2, r1
	asr r2, r1, #0x7
	asr r1, r3, #0x6
	ldr r5, [r4, #0xc]
	lsr r1, r1, #0x19
	add r1, r3, r1
	asr r3, r5, #0x6
	lsr r3, r3, #0x19
	add r3, r5, r3
	ldr r4, [r4, #0x4]
	asr r5, r3, #0x7
	asr r3, r4, #0x6
	lsr r3, r3, #0x19
	add r3, r4, r3
	asr r3, r3, #0x7
	asr r1, r1, #0x7
	cmp r3, r5
	bge _0201091E
	lsl r4, r3, #0x1
	lsl r1, r1, #0x10
	add r4, r0, r4
	lsl r0, r2, #0x10
	asr r6, r1, #0x10
	mov r1, #0x3
	mov r2, #0x12
	asr r0, r0, #0x10
	lsl r1, r1, #0x8
	lsl r2, r2, #0x6
_02010912:
	strh r0, [r4, r1]
	strh r6, [r4, r2]
	add r3, r3, #0x1
	add r4, r4, #0x2
	cmp r3, r5
	blt _02010912
_0201091E:
	pop {r4-r6, pc}

	thumb_func_start FUN_02010920
FUN_02010920: ; 0x02010920
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x10]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02010944
	add r4, r6, #0x0
_0201092E:
	ldr r1, [r5, #0xc]
	add r0, r1, r4
	add r1, r1, r4
	add r1, #0x10
	bl FUN_0200F184
	ldr r0, [r5, #0x10]
	add r6, r6, #0x1
	add r4, #0x30
	cmp r6, r0
	blt _0201092E
_02010944:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02010948
FUN_02010948: ; 0x02010948
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r4, r1, #0x0
	mov r1, #0x38
	bl FUN_02016998
	str r0, [r5, #0x14]
	mov r1, #0x0
	mov r2, #0x38
	bl memset
	ldr r0, [r5, #0x10]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	bl FUN_020109E8
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_02010988
FUN_02010988: ; 0x02010988
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _020109A0
	cmp r0, #0x2
	beq _020109BC
	cmp r0, #0x3
	beq _020109DC
	b _020109E0
_020109A0:
	add r0, r4, #0x0
	bl FUN_02010AE4
	cmp r0, #0x1
	bne _020109E4
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x30]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _020109E4
_020109BC:
	add r0, r4, #0x0
	bl FUN_02010B3C
	add r0, r4, #0x0
	bl FUN_0200F5C0
	ldr r0, [r5, #0x14]
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _020109E4
_020109DC:
	mov r6, #0x1
	b _020109E4
_020109E0:
	bl ErrorHandling
_020109E4:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020109E8
FUN_020109E8: ; 0x020109E8
	push {r3-r7, lr}
	sub sp, #0x28
	add r4, r1, #0x0
	add r5, r0, #0x0
	mov r1, #0x0
	str r1, [r5, #0xc]
	ldr r1, [r4, #0x0]
	str r2, [sp, #0x18]
	str r1, [r5, #0x10]
	str r3, [sp, #0x1c]
	ldr r2, [r4, #0x4]
	ldr r1, [r4, #0x0]
	ldr r6, [sp, #0x40]
	sub r1, r2, r1
	str r1, [r5, #0x14]
	ldr r3, [sp, #0x4c]
	mov r1, #0x2
	add r2, r6, #0x0
	ldr r7, [sp, #0x44]
	bl FUN_0200F55C
	ldr r0, [sp, #0x18]
	mov r1, #0x0
	str r0, [r5, #0x18]
	ldr r0, [sp, #0x1c]
	str r1, [r5, #0x1c]
	str r0, [r5, #0x20]
	str r1, [r5, #0x24]
	ldr r0, [sp, #0x48]
	str r7, [r5, #0x30]
	str r0, [r5, #0x34]
	ldr r0, [sp, #0x4c]
	str r0, [r5, #0x2c]
	ldrb r0, [r4, #0xa]
	str r0, [r5, #0x28]
	add r0, r5, #0x0
	ldr r1, [r5, #0x1c]
	ldr r2, [r5, #0x18]
	add r0, #0xc
	bl FUN_02010C64
	add r0, r5, #0x0
	bl FUN_02010B40
	ldr r0, _02010AD8 ; =FUN_0200F5F8
	ldr r2, _02010ADC ; =0x000003FF
	add r1, r5, #0x0
	bl FUN_0200CA98
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	str r0, [sp, #0x20]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0200F5D8
	str r0, [sp, #0x24]
	mov r1, #0x3
	ldr r0, [sp, #0x20]
	str r6, [sp, #0x0]
	lsl r1, r1, #0x8
	ldrsh r0, [r0, r1]
	mov r1, #0x12
	mov r3, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x20]
	str r3, [sp, #0x8]
	lsl r1, r1, #0x6
	ldrsh r0, [r0, r1]
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	str r0, [sp, #0x14]
	ldrb r1, [r4, #0x8]
	ldrb r2, [r4, #0x9]
	add r0, r7, #0x0
	bl FUN_0200F67C
	mov r1, #0x3
	ldr r0, [sp, #0x24]
	str r6, [sp, #0x0]
	lsl r1, r1, #0x8
	ldrsh r0, [r0, r1]
	mov r1, #0x12
	lsl r1, r1, #0x6
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x24]
	mov r3, #0x1
	ldrsh r0, [r0, r1]
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	str r0, [sp, #0x14]
	ldrb r1, [r4, #0x8]
	ldrb r2, [r4, #0x9]
	add r0, r7, #0x0
	bl FUN_0200F67C
	ldr r3, [r5, #0x28]
	add r0, r7, #0x0
	mov r1, #0x3
	add r2, r6, #0x0
	bl FUN_0200F6E4
	ldr r0, [sp, #0x4c]
	ldr r2, _02010AE0 ; =FUN_0200F330
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x34]
	add r1, r5, #0x0
	add r3, r6, #0x0
	bl FUN_0200E6CC
	add sp, #0x28
	pop {r3-r7, pc}
	.balign 4
_02010AD8: .word FUN_0200F5F8
_02010ADC: .word 0x000003FF
_02010AE0: .word FUN_0200F330

	thumb_func_start FUN_02010AE4
FUN_02010AE4: ; 0x02010AE4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x24]
	add r1, r0, #0x1
	str r1, [r4, #0x24]
	ldr r0, [r4, #0x20]
	cmp r1, r0
	blt _02010B2E
	mov r0, #0x0
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x1c]
	add r1, r0, #0x1
	ldr r0, [r4, #0x18]
	cmp r1, r0
	bgt _02010B20
	str r1, [r4, #0x1c]
	add r0, r4, #0x0
	ldr r2, [r4, #0x18]
	add r0, #0xc
	bl FUN_02010C64
	add r0, r4, #0x0
	bl FUN_02010B40
	ldr r0, _02010B34 ; =FUN_0200F5F8
	ldr r2, _02010B38 ; =0x000003FF
	add r1, r4, #0x0
	bl FUN_0200CA98
	b _02010B2E
_02010B20:
	ldr r0, [r4, #0x34]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x2c]
	bl FUN_0200E6F8
	mov r0, #0x1
	pop {r4, pc}
_02010B2E:
	mov r0, #0x0
	pop {r4, pc}
	nop
_02010B34: .word FUN_0200F5F8
_02010B38: .word 0x000003FF

	thumb_func_start FUN_02010B3C
FUN_02010B3C: ; 0x02010B3C
	bx lr
	.balign 4

	thumb_func_start FUN_02010B40
FUN_02010B40: ; 0x02010B40
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	ldr r0, [r0, #0xc]
	ldr r1, _02010C60 ; =0x00003FFF
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	bl FUN_0200F5D8
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	bl FUN_0200F5D8
	add r4, r0, #0x0
	mov r6, #0x0
	add r5, r4, #0x0
_02010B6C:
	ldr r0, [sp, #0x0]
	ldr r1, [r0, #0xc]
	ldr r0, _02010C60 ; =0x00003FFF
	cmp r1, r0
	bge _02010BB0
	mov r1, #0x60
	ldr r0, [sp, #0x4]
	sub r1, r1, r6
	bl FUN_0200F0D0
	cmp r0, #0x7f
	ble _02010B86
	mov r0, #0x7f
_02010B86:
	mov r1, #0xbf
	sub r1, r1, r6
	lsl r1, r1, #0x1
	add r3, r7, r1
	mov r1, #0x80
	sub r2, r1, r0
	mov r1, #0x3
	lsl r1, r1, #0x8
	strh r2, [r3, r1]
	mov r1, #0x12
	mov r2, #0x80
	lsl r1, r1, #0x6
	strh r2, [r3, r1]
	mov r1, #0x3
	lsl r1, r1, #0x8
	strh r2, [r5, r1]
	mov r1, #0x12
	add r0, #0x80
	lsl r1, r1, #0x6
	strh r0, [r5, r1]
	b _02010BD8
_02010BB0:
	mov r0, #0xbf
	sub r0, r0, r6
	lsl r0, r0, #0x1
	mov r1, #0x3
	add r0, r7, r0
	mov r2, #0x0
	lsl r1, r1, #0x8
	strh r2, [r0, r1]
	mov r1, #0x12
	mov r2, #0x80
	lsl r1, r1, #0x6
	strh r2, [r0, r1]
	mov r0, #0x3
	add r1, r2, #0x0
	lsl r0, r0, #0x8
	strh r1, [r5, r0]
	mov r0, #0x12
	mov r1, #0xff
	lsl r0, r0, #0x6
	strh r1, [r5, r0]
_02010BD8:
	add r6, r6, #0x1
	add r5, r5, #0x2
	cmp r6, #0x60
	blt _02010B6C
	ldr r1, _02010C60 ; =0x00003FFF
	ldr r0, [sp, #0x4]
	mov r5, #0x60
	add r4, #0xc0
	sub r6, r1, r0
_02010BEA:
	ldr r0, [sp, #0x0]
	ldr r1, [r0, #0xc]
	ldr r0, _02010C60 ; =0x00003FFF
	cmp r1, r0
	bge _02010C1A
	mov r0, #0xbf
	sub r0, r0, r5
	lsl r0, r0, #0x1
	mov r1, #0x3
	add r0, r7, r0
	mov r2, #0x80
	lsl r1, r1, #0x8
	strh r2, [r0, r1]
	mov r1, #0x12
	lsl r1, r1, #0x6
	strh r2, [r0, r1]
	mov r0, #0x3
	add r1, r2, #0x0
	lsl r0, r0, #0x8
	strh r1, [r4, r0]
	mov r0, #0x12
	lsl r0, r0, #0x6
	strh r1, [r4, r0]
	b _02010C54
_02010C1A:
	add r1, r5, #0x0
	add r0, r6, #0x0
	sub r1, #0x60
	bl FUN_0200F0D0
	add r1, r0, #0x0
	cmp r1, #0x7f
	ble _02010C2C
	mov r1, #0x7f
_02010C2C:
	mov r0, #0xbf
	sub r0, r0, r5
	lsl r0, r0, #0x1
	mov r2, #0x3
	add r0, r7, r0
	mov r3, #0x0
	lsl r2, r2, #0x8
	strh r3, [r0, r2]
	mov r2, #0x80
	sub r3, r2, r1
	mov r2, #0x12
	lsl r2, r2, #0x6
	strh r3, [r0, r2]
	mov r0, #0x3
	add r1, #0x80
	lsl r0, r0, #0x8
	strh r1, [r4, r0]
	mov r1, #0xff
	add r0, r2, #0x0
	strh r1, [r4, r0]
_02010C54:
	add r5, r5, #0x1
	add r4, r4, #0x2
	cmp r5, #0xc0
	blt _02010BEA
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02010C60: .word 0x00003FFF

	thumb_func_start FUN_02010C64
FUN_02010C64: ; 0x02010C64
	push {r4, lr}
	add r4, r0, #0x0
	ldr r3, [r4, #0x8]
	add r0, r3, #0x0
	mul r0, r1
	add r1, r2, #0x0
	bl _s32_div_f
	ldr r1, [r4, #0x4]
	add r0, r0, r1
	str r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02010C7C
FUN_02010C7C: ; 0x02010C7C
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	add r4, r1, #0x0
	mov r1, #0x38
	bl FUN_02016998
	str r0, [r5, #0x14]
	mov r1, #0x0
	mov r2, #0x38
	bl memset
	ldr r0, [r5, #0x10]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	bl FUN_02010D1C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_02010CBC
FUN_02010CBC: ; 0x02010CBC
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _02010CD4
	cmp r0, #0x2
	beq _02010CF0
	cmp r0, #0x3
	beq _02010D10
	b _02010D14
_02010CD4:
	add r0, r4, #0x0
	bl FUN_02010DEC
	cmp r0, #0x1
	bne _02010D18
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x30]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02010D18
_02010CF0:
	add r0, r4, #0x0
	bl FUN_02010E44
	add r0, r4, #0x0
	bl FUN_0200F5C0
	ldr r0, [r5, #0x14]
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02010D18
_02010D10:
	mov r6, #0x1
	b _02010D18
_02010D14:
	bl ErrorHandling
_02010D18:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02010D1C
FUN_02010D1C: ; 0x02010D1C
	push {r3-r7, lr}
	sub sp, #0x20
	add r4, r1, #0x0
	ldr r1, [r4, #0x0]
	add r5, r0, #0x0
	str r1, [r5, #0xc]
	ldr r1, [r4, #0x0]
	str r3, [sp, #0x1c]
	str r1, [r5, #0x10]
	str r2, [sp, #0x18]
	ldr r2, [r4, #0x4]
	ldr r1, [r4, #0x0]
	ldr r6, [sp, #0x38]
	sub r1, r2, r1
	str r1, [r5, #0x14]
	ldr r3, [sp, #0x44]
	mov r1, #0x2
	add r2, r6, #0x0
	ldr r7, [sp, #0x3c]
	bl FUN_0200F55C
	ldr r0, [sp, #0x18]
	mov r1, #0x0
	str r0, [r5, #0x18]
	ldr r0, [sp, #0x1c]
	str r1, [r5, #0x1c]
	str r0, [r5, #0x20]
	str r1, [r5, #0x24]
	ldr r0, [sp, #0x40]
	str r7, [r5, #0x30]
	str r0, [r5, #0x34]
	ldr r0, [sp, #0x44]
	str r0, [r5, #0x2c]
	ldrb r0, [r4, #0xa]
	str r0, [r5, #0x28]
	add r0, r5, #0x0
	bl FUN_02010E48
	ldr r0, _02010DE0 ; =FUN_0200F5F8
	ldr r2, _02010DE4 ; =0x000003FF
	add r1, r5, #0x0
	bl FUN_0200CA98
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0200F5D8
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0200F5D8
	str r6, [sp, #0x0]
	mov r3, #0x0
	str r3, [sp, #0x4]
	str r3, [sp, #0x8]
	mov r0, #0xff
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	str r0, [sp, #0x14]
	ldrb r1, [r4, #0x8]
	ldrb r2, [r4, #0x9]
	add r0, r7, #0x0
	bl FUN_0200F67C
	str r6, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0xff
	str r0, [sp, #0xc]
	mov r0, #0xc0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	mov r3, #0x1
	str r0, [sp, #0x14]
	ldrb r1, [r4, #0x8]
	ldrb r2, [r4, #0x9]
	add r0, r7, #0x0
	bl FUN_0200F67C
	ldr r3, [r5, #0x28]
	add r0, r7, #0x0
	mov r1, #0x3
	add r2, r6, #0x0
	bl FUN_0200F6E4
	ldr r0, [sp, #0x44]
	ldr r2, _02010DE8 ; =FUN_0200F330
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x34]
	add r1, r5, #0x0
	add r3, r6, #0x0
	bl FUN_0200E6CC
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4
_02010DE0: .word FUN_0200F5F8
_02010DE4: .word 0x000003FF
_02010DE8: .word FUN_0200F330

	thumb_func_start FUN_02010DEC
FUN_02010DEC: ; 0x02010DEC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x24]
	add r1, r0, #0x1
	str r1, [r4, #0x24]
	ldr r0, [r4, #0x20]
	cmp r1, r0
	blt _02010E36
	mov r0, #0x0
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x1c]
	add r1, r0, #0x1
	ldr r0, [r4, #0x18]
	cmp r1, r0
	bgt _02010E28
	str r1, [r4, #0x1c]
	add r0, r4, #0x0
	ldr r2, [r4, #0x18]
	add r0, #0xc
	bl FUN_02010F14
	add r0, r4, #0x0
	bl FUN_02010E48
	ldr r0, _02010E3C ; =FUN_0200F5F8
	ldr r2, _02010E40 ; =0x000003FF
	add r1, r4, #0x0
	bl FUN_0200CA98
	b _02010E36
_02010E28:
	ldr r0, [r4, #0x34]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x2c]
	bl FUN_0200E6F8
	mov r0, #0x1
	pop {r4, pc}
_02010E36:
	mov r0, #0x0
	pop {r4, pc}
	nop
_02010E3C: .word FUN_0200F5F8
_02010E40: .word 0x000003FF

	thumb_func_start FUN_02010E44
FUN_02010E44: ; 0x02010E44
	bx lr
	.balign 4

	thumb_func_start FUN_02010E48
FUN_02010E48: ; 0x02010E48
	push {r4-r7, lr}
	sub sp, #0x1c
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	str r1, [sp, #0x8]
	mov r1, #0x0
	bl FUN_0200F5D8
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0200F5D8
	str r0, [sp, #0xc]
	add r5, r0, #0x0
	ldr r1, _02010F10 ; =0x00003FFF
	ldr r0, [sp, #0x8]
	ldr r6, [sp, #0x10]
	sub r0, r1, r0
	mov r7, #0x0
	str r0, [sp, #0x4]
_02010E76:
	mov r0, #0x60
	sub r0, r0, r7
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x0]
	bl FUN_0200F0D0
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x0]
	bl FUN_0200F0D0
	cmp r4, #0x7f
	ble _02010E94
	mov r4, #0x7f
_02010E94:
	cmp r0, #0x7f
	ble _02010E9A
	mov r0, #0x7f
_02010E9A:
	mov r1, #0x80
	sub r1, r1, r0
	lsl r1, r1, #0x10
	mov r2, #0x3
	asr r1, r1, #0x10
	lsl r2, r2, #0x8
	str r1, [sp, #0x14]
	strh r1, [r6, r2]
	mov r1, #0x80
	sub r1, r1, r4
	lsl r1, r1, #0x10
	asr r2, r1, #0x10
	mov r1, #0x12
	lsl r1, r1, #0x6
	strh r2, [r6, r1]
	mov r1, #0xbf
	sub r1, r1, r7
	mov r12, r2
	lsl r1, r1, #0x1
	ldr r2, [sp, #0x10]
	add r0, #0x80
	add r3, r2, r1
	str r1, [sp, #0x18]
	mov r2, #0x3
	ldr r1, [sp, #0x14]
	lsl r2, r2, #0x8
	strh r1, [r3, r2]
	mov r1, #0x12
	mov r2, r12
	lsl r1, r1, #0x6
	strh r2, [r3, r1]
	add r4, #0x80
	lsl r1, r4, #0x10
	asr r2, r1, #0x10
	mov r1, #0x3
	lsl r1, r1, #0x8
	lsl r0, r0, #0x10
	strh r2, [r5, r1]
	asr r1, r0, #0x10
	mov r0, #0x12
	lsl r0, r0, #0x6
	strh r1, [r5, r0]
	ldr r3, [sp, #0xc]
	ldr r0, [sp, #0x18]
	add r7, r7, #0x1
	add r0, r3, r0
	mov r3, #0x3
	lsl r3, r3, #0x8
	strh r2, [r0, r3]
	mov r2, #0x12
	lsl r2, r2, #0x6
	strh r1, [r0, r2]
	add r6, r6, #0x2
	add r5, r5, #0x2
	cmp r7, #0x60
	blt _02010E76
	add sp, #0x1c
	pop {r4-r7, pc}
	nop
_02010F10: .word 0x00003FFF

	thumb_func_start FUN_02010F14
FUN_02010F14: ; 0x02010F14
	push {r4, lr}
	add r4, r0, #0x0
	ldr r3, [r4, #0x8]
	add r0, r3, #0x0
	mul r0, r1
	add r1, r2, #0x0
	bl _s32_div_f
	ldr r1, [r4, #0x4]
	add r0, r0, r1
	str r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02010F2C
FUN_02010F2C: ; 0x02010F2C
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r1, #0xcd
	ldr r0, [r5, #0x20]
	lsl r1, r1, #0x2
	bl FUN_02016998
	mov r2, #0xcd
	str r0, [r5, #0x14]
	mov r1, #0x0
	lsl r2, r2, #0x2
	bl memset
	ldr r0, [r5, #0x10]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x20]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	bl FUN_02010FD0
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_02010F70
FUN_02010F70: ; 0x02010F70
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r6, #0x0
	ldr r4, [r5, #0x14]
	cmp r0, #0x1
	beq _02010F88
	cmp r0, #0x2
	beq _02010FAA
	cmp r0, #0x3
	beq _02010FC4
	b _02010FC8
_02010F88:
	add r0, r4, #0x0
	bl FUN_020110BC
	cmp r0, #0x1
	bne _02010FCC
	mov r1, #0xc9
	lsl r1, r1, #0x2
	ldr r0, [r4, r1]
	add r1, #0x8
	ldr r1, [r4, r1]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02010FCC
_02010FAA:
	add r0, r4, #0x0
	bl FUN_0201111C
	ldr r0, [r5, #0x14]
	bl FUN_02016A18
	add r0, r6, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r6, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02010FCC
_02010FC4:
	mov r6, #0x1
	b _02010FCC
_02010FC8:
	bl ErrorHandling
_02010FCC:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02010FD0
FUN_02010FD0: ; 0x02010FD0
	push {r3-r7, lr}
	sub sp, #0x20
	ldr r7, [sp, #0x38]
	str r3, [sp, #0x1c]
	mov r3, #0x0
	add r4, r1, #0x0
	str r2, [sp, #0x18]
	str r3, [sp, #0x0]
	add r1, r7, #0x0
	mov r2, #0x1
	add r5, r0, #0x0
	ldr r6, [sp, #0x3c]
	bl FUN_0200F6FC
	ldrb r0, [r4, #0x5]
	cmp r0, #0x0
	bne _0201100A
	add r0, r5, #0x0
	mov r1, #0x1
	mov r2, #0xc0
	bl memset
	add r0, r5, #0x0
	add r0, #0xc0
	mov r1, #0x1
	mov r2, #0xc0
	bl memset
	b _02011020
_0201100A:
	add r0, r5, #0x0
	mov r1, #0x0
	mov r2, #0xc0
	bl memset
	add r0, r5, #0x0
	add r0, #0xc0
	mov r1, #0x0
	mov r2, #0xc0
	bl memset
_02011020:
	mov r1, #0xc3
	lsl r1, r1, #0x2
	ldr r0, [r4, #0x0]
	add r3, r1, #0x0
	str r0, [r5, r1]
	ldrb r2, [r4, #0x4]
	add r0, r1, #0x4
	add r3, #0x8
	str r2, [r5, r0]
	add r0, r1, #0x0
	ldrb r2, [r4, #0x5]
	add r0, #0x18
	str r2, [r5, r0]
	add r0, r1, #0x0
	ldr r2, [sp, #0x44]
	add r0, #0x1c
	str r2, [r5, r0]
	ldr r0, [sp, #0x18]
	str r0, [r5, r3]
	add r3, r1, #0x0
	add r3, #0xc
	mov r0, #0x0
	str r0, [r5, r3]
	add r3, r1, #0x0
	ldr r0, [sp, #0x1c]
	add r3, #0x10
	str r0, [r5, r3]
	add r3, r1, #0x0
	add r3, #0x14
	mov r0, #0x0
	str r0, [r5, r3]
	add r0, r1, #0x0
	add r0, #0x20
	str r6, [r5, r0]
	ldr r0, [sp, #0x40]
	add r1, #0x24
	str r0, [r5, r1]
	add r1, r5, #0x0
	bl FUN_0200F758
	ldrb r0, [r4, #0x5]
	cmp r0, #0x1
	str r7, [sp, #0x0]
	bne _02011090
	mov r3, #0x0
	str r3, [sp, #0x4]
	str r3, [sp, #0x8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	str r0, [sp, #0x14]
	add r0, r6, #0x0
	mov r1, #0x20
	mov r2, #0x3f
	bl FUN_0200F67C
	b _020110A6
_02011090:
	mov r3, #0x0
	str r3, [sp, #0x4]
	str r3, [sp, #0x8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	str r0, [sp, #0x14]
	add r0, r6, #0x0
	mov r1, #0x3f
	mov r2, #0x20
	bl FUN_0200F67C
_020110A6:
	mov r3, #0xc9
	lsl r3, r3, #0x2
	ldr r3, [r5, r3]
	add r0, r6, #0x0
	mov r1, #0x1
	add r2, r7, #0x0
	bl FUN_0200F6E4
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020110BC
FUN_020110BC: ; 0x020110BC
	push {r4, lr}
	mov r2, #0x32
	add r4, r0, #0x0
	lsl r2, r2, #0x4
	ldr r1, [r4, r2]
	add r1, r1, #0x1
	str r1, [r4, r2]
	sub r1, r2, #0x4
	ldr r3, [r4, r2]
	ldr r1, [r4, r1]
	cmp r3, r1
	blt _02011116
	mov r1, #0x0
	str r1, [r4, r2]
	add r1, r2, #0x0
	sub r1, #0x8
	ldr r1, [r4, r1]
	add r3, r1, #0x1
	add r1, r2, #0x0
	sub r1, #0xc
	ldr r1, [r4, r1]
	cmp r3, r1
	bgt _02011102
	add r1, r2, #0x0
	sub r1, #0x8
	ldr r1, [r4, r1]
	sub r2, #0x8
	add r1, r1, #0x1
	str r1, [r4, r2]
	bl FUN_02011120
	add r0, r4, #0x0
	bl FUN_0200F740
	b _02011116
_02011102:
	add r0, r2, #0x0
	add r0, #0x10
	add r2, #0x8
	ldr r0, [r4, r0]
	ldr r2, [r4, r2]
	add r1, r4, #0x0
	bl FUN_0200F770
	mov r0, #0x1
	pop {r4, pc}
_02011116:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201111C
FUN_0201111C: ; 0x0201111C
	bx lr
	.balign 4

	thumb_func_start FUN_02011120
FUN_02011120: ; 0x02011120
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x31
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r6, #0x0
	cmp r0, #0x0
	ble _0201115A
	mov r7, #0x31
	add r4, r6, #0x0
	lsl r7, r7, #0x4
_02011136:
	mov r0, #0xc3
	lsl r0, r0, #0x2
	mov r2, #0xc6
	mov r3, #0xc5
	ldr r0, [r5, r0]
	lsl r2, r2, #0x2
	lsl r3, r3, #0x2
	ldr r2, [r5, r2]
	ldr r3, [r5, r3]
	add r0, r0, r4
	add r1, r5, #0x0
	bl FUN_0201115C
	ldr r0, [r5, r7]
	add r6, r6, #0x1
	add r4, r4, #0x3
	cmp r6, r0
	blt _02011136
_0201115A:
	pop {r3-r7, pc}

	thumb_func_start FUN_0201115C
FUN_0201115C: ; 0x0201115C
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldrb r6, [r7, #0x0]
	ldrb r4, [r7, #0x1]
	add r5, r1, #0x0
	add r1, r3, #0x0
	sub r0, r4, r6
	mul r0, r2
	bl _s32_div_f
	add r0, r0, r6
	cmp r6, r4
	bhi _0201117C
	add r1, r6, #0x0
	ldrb r6, [r7, #0x2]
	b _0201118C
_0201117C:
	ldrb r2, [r7, #0x2]
	add r1, r4, #0x0
	add r4, r6, #0x0
	cmp r2, #0x0
	bne _0201118A
	mov r6, #0x1
	b _0201118C
_0201118A:
	mov r6, #0x0
_0201118C:
	cmp r1, r4
	bge _020111AA
	mov r2, #0x0
	mov r3, #0x1
_02011194:
	cmp r1, r0
	bne _020111A2
	cmp r6, #0x0
	bne _020111A0
	add r6, r3, #0x0
	b _020111A2
_020111A0:
	add r6, r2, #0x0
_020111A2:
	strb r6, [r5, r1]
	add r1, r1, #0x1
	cmp r1, r4
	blt _02011194
_020111AA:
	pop {r3-r7, pc}

	thumb_func_start FUN_020111AC
FUN_020111AC: ; 0x020111AC
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r1, #0xe2
	ldr r0, [r5, #0x20]
	lsl r1, r1, #0x2
	bl FUN_02016998
	mov r2, #0xe2
	mov r1, #0x0
	lsl r2, r2, #0x2
	str r0, [r5, #0x14]
	bl memset
	add r1, r4, #0x0
	add r1, #0x23
	ldrb r1, [r1, #0x0]
	ldr r0, [r5, #0x14]
	cmp r1, #0x0
	ldr r1, [r5, #0x10]
	bne _020111F2
	str r1, [sp, #0x0]
	ldr r1, [r5, #0x18]
	str r1, [sp, #0x4]
	ldr r1, [r5, #0x1c]
	str r1, [sp, #0x8]
	ldr r1, [r5, #0x20]
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	add r1, r4, #0x0
	bl FUN_0201127C
	b _0201120A
_020111F2:
	str r1, [sp, #0x0]
	ldr r1, [r5, #0x18]
	str r1, [sp, #0x4]
	ldr r1, [r5, #0x1c]
	str r1, [sp, #0x8]
	ldr r1, [r5, #0x20]
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x4]
	ldr r3, [r5, #0x8]
	add r1, r4, #0x0
	bl FUN_0201137C
_0201120A:
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_02011214
FUN_02011214: ; 0x02011214
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0xc]
	mov r4, #0x0
	ldr r0, [r5, #0x14]
	cmp r1, #0x1
	beq _0201122C
	cmp r1, #0x2
	beq _02011258
	cmp r1, #0x3
	beq _0201126A
	b _0201126E
_0201122C:
	ldr r1, _02011278 ; =0x00000386
	ldrb r1, [r0, r1]
	cmp r1, #0x0
	bne _0201123C
	add r1, r5, #0x0
	bl FUN_02011308
	b _02011242
_0201123C:
	add r1, r5, #0x0
	bl FUN_020113EC
_02011242:
	cmp r0, #0x1
	bne _02011272
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #0x18]
	ldr r2, [r5, #0x10]
	bl FUN_0200F62C
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02011272
_02011258:
	bl FUN_02016A18
	add r0, r4, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0xc]
	mov r4, #0x1
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02011272
_0201126A:
	mov r4, #0x1
	b _02011272
_0201126E:
	bl ErrorHandling
_02011272:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	nop
_02011278: .word 0x00000386

	thumb_func_start FUN_0201127C
FUN_0201127C: ; 0x0201127C
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r5, r0, #0x0
	lsl r0, r6, #0xc
	ldr r2, [r4, #0x2c]
	add r7, r3, #0x0
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	add r2, r0, #0x0
	mov r0, #0x2
	mov r3, #0x0
	lsl r0, r0, #0xa
	add r0, r2, r0
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	asr r2, r0, #0xc
	mov r0, #0xe1
	sub r1, r6, r2
	lsl r0, r0, #0x2
	strb r1, [r5, r0]
	sub r1, r0, #0x4
	str r4, [r5, r1]
	add r1, r4, #0x0
	add r1, #0x23
	ldrb r1, [r1, #0x0]
	add r0, r0, #0x2
	add r3, r7, #0x0
	strb r1, [r5, r0]
	ldr r0, [sp, #0x20]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_0200FE20
	add r0, r4, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020112EA
	add r4, #0x23
	ldrb r3, [r4, #0x0]
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x20]
	mov r1, #0x1
	bl FUN_0200F6E4
	b _020112F8
_020112EA:
	add r4, #0x23
	ldrb r3, [r4, #0x0]
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x20]
	mov r1, #0x2
	bl FUN_0200F6E4
_020112F8:
	ldr r0, _02011304 ; =0x00000385
	mov r1, #0x0
	strb r1, [r5, r0]
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02011304: .word 0x00000385

	thumb_func_start FUN_02011308
FUN_02011308: ; 0x02011308
	push {r4-r6, lr}
	sub sp, #0x10
	add r4, r1, #0x0
	ldr r1, _02011378 ; =0x00000385
	add r5, r0, #0x0
	ldrb r1, [r5, r1]
	mov r6, #0x0
	cmp r1, #0x0
	beq _02011324
	cmp r1, #0x1
	beq _0201135A
	cmp r1, #0x2
	beq _02011370
	b _02011372
_02011324:
	bl FUN_0200FE90
	cmp r0, #0x1
	bne _02011372
	ldr r2, _02011378 ; =0x00000385
	ldrb r0, [r5, r2]
	sub r1, r2, #0x5
	add r0, r0, #0x1
	strb r0, [r5, r2]
	ldr r0, [r4, #0x10]
	sub r2, r2, #0x1
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x20]
	str r0, [sp, #0xc]
	ldr r1, [r5, r1]
	add r0, r5, #0x0
	ldrb r2, [r5, r2]
	ldr r3, [r4, #0x8]
	add r0, #0x4c
	add r1, #0x24
	bl FUN_02010FD0
	b _02011372
_0201135A:
	add r0, #0x4c
	bl FUN_020110BC
	cmp r0, #0x1
	bne _02011372
	ldr r0, _02011378 ; =0x00000385
	mov r6, #0x1
	ldrb r1, [r5, r0]
	add r1, r1, #0x1
	strb r1, [r5, r0]
	b _02011372
_02011370:
	mov r6, #0x1
_02011372:
	add r0, r6, #0x0
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_02011378: .word 0x00000385
