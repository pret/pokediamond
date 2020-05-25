	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global pairlist
pairlist: ; 0x0210623C
	.byte 0x04, 0x00, 0x05, 0x00

	.global UNK_02106240
UNK_02106240: ; 0x02106240
	.byte 0xFF, 0xFF, 0xFF, 0x00

	.global ssl_handshake_priority
ssl_handshake_priority: ; 0x02106244
	.byte 0xFF, 0xFF, 0xFF, 0xFF

	.global UNK_02106248
UNK_02106248: ; 0x02106248
	.byte 0x55, 0x04, 0x03, 0x00

	.global UNK_0210624C
UNK_0210624C: ; 0x0210624C
	.byte 0x55, 0x08, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00

	.global UNK_02106254
UNK_02106254: ; 0x02106254
	.byte 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00

	.global UNK_02106260
UNK_02106260: ; 0x02106260
	.byte 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x04, 0x00, 0x00, 0x00

	.global UNK_0210626C
UNK_0210626C: ; 0x0210626C
	.byte 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x05, 0x00, 0x00, 0x00

	.global object
object: ; 0x02106278
	.word UNK_02106240
	.word UNK_02106254
	.word UNK_0210624C
	.word UNK_02106260
	.word UNK_0210626C
	.word UNK_02106248

	.global UNK_02106290
UNK_02106290: ; 0x02106290
	.byte 0x53, 0x52, 0x56, 0x52, 0x00, 0x00, 0x00, 0x00

	.global UNK_02106298
UNK_02106298: ; 0x02106298
	.byte 0x43, 0x4C, 0x4E, 0x54, 0x00, 0x00, 0x00, 0x00

	.global UNK_021062A0
UNK_021062A0: ; 0x021062A0
	.byte 0x41, 0x00, 0x00, 0x00

	.global UNK_021062A4
UNK_021062A4: ; 0x021062A4
	.byte 0x42, 0x42, 0x00, 0x00

	.global UNK_021062A8
UNK_021062A8: ; 0x021062A8
	.byte 0x43, 0x43, 0x43, 0x00

	.section .bss

	.global pool_initialized
pool_initialized: ; 0x021CA6E0
	.space 0x4

	.global UNK_021CA6E4
UNK_021CA6E4: ; 0x021CA6E4
	.space 0x4

	.global pool
pool: ; 0x021CA6E8
	.space 0x14

	.global session
session: ; 0x021CA6FC
	.space 0x170

	.section .text

	arm_func_start CPSi_SslCleanup
CPSi_SslCleanup: ; 0x020A01E0
	ldr ip, _020A01F4 ; =MI_CpuFill8
	ldr r0, _020A01F8 ; =session
	mov r1, #0x0
	mov r2, #0x170
	bx r12
	.balign 4
_020A01F4: .word MI_CpuFill8
_020A01F8: .word session

	arm_func_start CPSi_SslPeriodical
CPSi_SslPeriodical: ; 0x020A01FC
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r4, _020A02E0 ; =session
	mov r6, #0x0
	mov r2, r6
	ldr r1, _020A02E4 ; =0x000003BD
_020A0218:
	ldrb r3, [r4, #0x5a]
	cmp r3, #0x0
	beq _020A0234
	ldr r3, [r4, #0x50]
	sub r3, r5, r3
	cmp r3, r1
	strgtb r2, [r4, #0x5a]
_020A0234:
	add r6, r6, #0x1
	cmp r6, #0x4
	add r4, r4, #0x5c
	blt _020A0218
	bl OS_RestoreInterrupts
	ldr r0, _020A02E8 ; =OSi_ThreadInfo
	ldr r4, [r0, #0x8]
	cmp r4, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r6, #0x0
_020A0260:
	ldr r1, [r4, #0xa4]
	cmp r1, #0x0
	beq _020A02CC
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	beq _020A02CC
	ldrb r0, [r1, #0x9]
	cmp r0, #0x0
	beq _020A02CC
	ldrb r0, [r1, #0x8]
	cmp r0, #0x4
	bne _020A02CC
	ldr r0, [r1, #0xc]
	ldrb r0, [r0, #0x455]
	cmp r0, #0x8
	bhs _020A02CC
	ldr r0, [r1, #0x10]
	sub r0, r5, r0
	cmp r0, #0xef
	ble _020A02CC
	ldr r0, [r1, #0x4]
	cmp r0, #0x2
	bne _020A02CC
	strb r6, [r1, #0x8]
	str r6, [r1, #0x4]
	ldr r0, [r1, #0x0]
	bl OS_WakeupThreadDirect
_020A02CC:
	ldr r4, [r4, #0x68]
	cmp r4, #0x0
	bne _020A0260
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A02E0: .word session
_020A02E4: .word 0x000003BD
_020A02E8: .word OSi_ThreadInfo

	.extern _SDK_UbiquitousSSL
	; SDK_DEFINE_MIDDLEWARE(id_string, "UBIQUITOUS", "SSL");

	arm_func_start CPS_SetSsl
CPS_SetSsl:
	stmdb sp!, {r4,lr}
	mov r4, r0
	; SDK_USING_MIDDLEWARE(id_string)
	ldr r0, _020A0318 ; =_SDK_UbiquitousSSL
	bl OSi_ReferSymbol
	ldr r0, _020A031C ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xa4]
	cmp r0, #0x0
	strneb r4, [r0, #0x9]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A0318: .word _SDK_UbiquitousSSL
_020A031C: .word OSi_ThreadInfo

	arm_func_start CPSi_SslClose
CPSi_SslClose: ; 0x020A0320
	stmdb sp!, {r4,lr}
	ldr r4, [r0, #0xc]
	mov r0, #0x0
	strb r0, [r4, #0x455]
	ldr r0, [r4, #0x824]
	cmp r0, #0x0
	beq _020A0348
	ldr r1, _020A0358 ; =CPSiFree
	ldr r1, [r1, #0x0]
	blx r1
_020A0348:
	mov r0, #0x0
	str r0, [r4, #0x824]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A0358: .word CPSiFree

	arm_func_start CPSi_SslShutdown
CPSi_SslShutdown: ; 0x020A035C
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x20
	mov r5, r0
	ldr r4, [r5, #0xc]
	ldrb r0, [r4, #0x455]
	cmp r0, #0x8
	bne _020A03CC
	mov r12, #0x0
	mov r6, #0x15
	mov lr, #0x3
	mov r3, #0x2
	mov r2, #0x1
	add r1, sp, #0x4
	mov r0, r4
	strb r6, [sp, #0x4]
	strb lr, [sp, #0x5]
	strb r12, [sp, #0x6]
	strb r12, [sp, #0x7]
	strb r3, [sp, #0x8]
	strb r2, [sp, #0x9]
	strb r12, [sp, #0xa]
	bl make_ciphertext
	mov r2, #0x0
	mov r1, r0
	add r0, sp, #0x4
	mov r3, r2
	str r5, [sp, #0x0]
	bl CPSi_TcpWrite2Raw
_020A03CC:
	mov r0, #0x0
	strb r0, [r4, #0x455]
	add sp, sp, #0x20
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start CPSi_SslWrite2
CPSi_SslWrite2: ; 0x020A03E0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x24
	ldr r4, [sp, #0x48]
	mov r9, r1
	mov r1, r4
	mov r10, r0
	mov r0, #0x0
	ldr r1, [r1, #0xc]
	str r0, [sp, #0x8]
	str r0, [sp, #0x1c]
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	mov r0, #0x17
	str r0, [sp, #0xc]
	mov r0, #0x3
	str r4, [sp, #0x48]
	str r1, [sp, #0x4]
	mov r8, r2
	add r6, r9, r3
	str r0, [sp, #0x10]
_020A0430:
	ldr r0, _020A052C ; =0x00000B4F
	ldr r1, _020A0530 ; =CPSiAlloc
	cmp r6, r0
	movgt r5, r0
	movle r5, r6
	ldr r1, [r1, #0x0]
	add r0, r5, #0x19
	blx r1
	movs r7, r0
	beq _020A051C
	cmp r9, r5
	movcs r4, r5
	movcc r4, r9
	mov r0, r10
	add r1, r7, #0x5
	mov r2, r4
	sub r11, r5, r4
	bl MI_CpuCopy8
	add r1, r7, #0x5
	mov r0, r8
	add r1, r1, r4
	mov r2, r11
	add r10, r10, r4
	sub r9, r9, r4
	bl MI_CpuCopy8
	ldr r0, [sp, #0xc]
	mov r1, r7
	strb r0, [r7, #0x0]
	ldr r0, [sp, #0x10]
	add r8, r8, r11
	strb r0, [r7, #0x1]
	ldr r0, [sp, #0x14]
	strb r0, [r7, #0x2]
	mov r0, r5, asr #0x8
	strb r0, [r7, #0x3]
	ldr r0, [sp, #0x4]
	strb r5, [r7, #0x4]
	bl make_ciphertext
	ldr r1, [sp, #0x48]
	ldr r2, [sp, #0x18]
	mov r4, r0
	str r1, [sp, #0x0]
	mov r0, r7
	mov r1, r4
	mov r3, r2
	bl CPSi_TcpWrite2Raw
	cmp r0, r4
	ldr r1, _020A0534 ; =CPSiFree
	mov r0, r7
	ldr r1, [r1, #0x0]
	ldrcc r5, [sp, #0x1c]
	blx r1
	ldr r0, [sp, #0x8]
	subs r6, r6, r5
	add r0, r0, r5
	str r0, [sp, #0x8]
	beq _020A051C
	cmp r5, #0x0
	bne _020A0430
_020A051C:
	ldr r0, [sp, #0x8]
	add sp, sp, #0x24
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A052C: .word 0x00000B4F
_020A0530: .word CPSiAlloc
_020A0534: .word CPSiFree

	arm_func_start CPSi_SslGetLength
CPSi_SslGetLength: ; 0x020A0538
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r4, [r5, #0xc]
	ldr r0, [r4, #0x824]
	cmp r0, #0x0
	beq _020A0560
	ldrb r0, [r4, #0x456]
	cmp r0, #0x0
	bne _020A0568
_020A0560:
	mov r0, r5
	bl try_fill_record
_020A0568:
	ldr r1, [r4, #0x824]
	cmp r1, #0x0
	beq _020A0594
	ldrb r0, [r4, #0x456]
	cmp r0, #0x0
	ldrne r1, [r4, #0x828]
	ldrne r0, [r4, #0x82c]
	addne sp, sp, #0x4
	subne r0, r1, r0
	ldmneia sp!, {r4-r5,lr}
	bxne lr
_020A0594:
	cmp r1, #0x0
	bne _020A05C4
	ldrb r0, [r5, #0x8]
	cmp r0, #0x4
	bne _020A05B4
	ldrb r0, [r4, #0x455]
	cmp r0, #0x9
	bne _020A05C4
_020A05B4:
	add sp, sp, #0x4
	mvn r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A05C4:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start try_fill_record
try_fill_record: ; 0x020A05D4
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r5, r0
	ldr r4, [r5, #0xc]
	ldr r0, [r4, #0x824]
	cmp r0, #0x0
	bne _020A0684
	ldr r0, [r5, #0x44]
	cmp r0, #0x5
	addcc sp, sp, #0x8
	ldmccia sp!, {r4-r6,lr}
	bxcc lr
	add r0, sp, #0x0
	mov r1, r5
	bl CPSi_TcpReadRaw
	ldrb r2, [r0, #0x3]
	ldrb r0, [r0, #0x4]
	ldr r1, _020A0730 ; =0x00004805
	add r0, r0, r2, lsl #0x8
	add r0, r0, #0x5
	str r0, [sp, #0x0]
	cmp r0, r1
	movhi r0, #0x9
	addhi sp, sp, #0x8
	strhib r0, [r4, #0x455]
	ldmhiia sp!, {r4-r6,lr}
	bxhi lr
	ldr r1, _020A0734 ; =CPSiAlloc
	ldr r1, [r1, #0x0]
	blx r1
	str r0, [r4, #0x824]
	ldr r0, [r4, #0x824]
	cmp r0, #0x0
	moveq r0, #0x9
	addeq sp, sp, #0x8
	streqb r0, [r4, #0x455]
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r1, [sp, #0x0]
	mov r0, #0x0
	str r1, [r4, #0x828]
	str r0, [r4, #0x82c]
	strb r0, [r4, #0x456]
	b _020A0698
_020A0684:
	ldr r0, [r5, #0x44]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
_020A0698:
	add r0, sp, #0x0
	mov r1, r5
	bl CPSi_TcpReadRaw
	ldr r3, [r4, #0x828]
	ldr r2, [r4, #0x82c]
	ldr r1, [sp, #0x0]
	sub r2, r3, r2
	cmp r1, r2
	strcs r2, [sp, #0x0]
	movcs r6, #0x1
	ldr r3, [r4, #0x824]
	ldr r1, [r4, #0x82c]
	ldr r2, [sp, #0x0]
	add r1, r3, r1
	movcc r6, #0x0
	bl MI_CpuCopy8
	ldr r0, [sp, #0x0]
	mov r1, r5
	bl CPSi_SocConsumeRaw
	cmp r6, #0x0
	beq _020A0714
	ldr r1, [r4, #0x824]
	mov r0, r4
	bl parse_record_in_buf
	ldrb r0, [r4, #0x456]
	add sp, sp, #0x8
	cmp r0, #0x0
	moveq r0, #0x0
	streq r0, [r4, #0x824]
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A0714:
	ldr r1, [r4, #0x82c]
	ldr r0, [sp, #0x0]
	add r0, r1, r0
	str r0, [r4, #0x82c]
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A0730: .word 0x00004805
_020A0734: .word CPSiAlloc

	arm_func_start CPSi_SslConsume
CPSi_SslConsume: ; 0x020A0738
	stmdb sp!, {r4,lr}
	ldr r4, [r1, #0xc]
	ldr r2, [r4, #0x828]
	ldr r1, [r4, #0x82c]
	sub r2, r2, r1
	cmp r0, r2
	blo _020A077C
	ldr r0, [r4, #0x824]
	cmp r0, #0x0
	beq _020A076C
	ldr r1, _020A078C ; =CPSiFree
	ldr r1, [r1, #0x0]
	blx r1
_020A076C:
	mov r0, #0x0
	str r0, [r4, #0x824]
	ldmia sp!, {r4,lr}
	bx lr
_020A077C:
	add r0, r1, r0
	str r0, [r4, #0x82c]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A078C: .word CPSiFree

	arm_func_start CPSi_SslRead
CPSi_SslRead: ; 0x020A0790
	stmdb sp!, {r4-r6,lr}
	mov r5, r1
	ldr r4, [r5, #0xc]
	mov r6, r0
	ldr r12, [r4, #0x824]
	cmp r12, #0x0
	beq _020A0818
	ldrb r0, [r4, #0x456]
	cmp r0, #0x0
	bne _020A0818
	ldr r3, [r4, #0x82c]
	ldr r1, [r4, #0x828]
	mov r2, r5
	add r0, r12, r3
	sub r1, r1, r3
	bl tcp_read_raw_nbytes
	cmp r0, #0x0
	beq _020A07FC
	ldr r1, _020A0870 ; =CPSiFree
	ldr r0, [r4, #0x824]
	ldr r1, [r1, #0x0]
	blx r1
	mov r0, #0x0
	str r0, [r4, #0x824]
	str r0, [r6, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A07FC:
	ldr r1, [r4, #0x824]
	mov r0, r4
	bl parse_record_in_buf
	ldrb r0, [r4, #0x456]
	cmp r0, #0x0
	moveq r0, #0x0
	streq r0, [r4, #0x824]
_020A0818:
	ldr r0, [r4, #0x824]
	cmp r0, #0x0
	bne _020A084C
_020A0824:
	mov r0, r5
	bl parse_record
	cmp r0, #0x9
	moveq r0, #0x0
	streq r0, [r6, #0x0]
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, [r4, #0x824]
	cmp r0, #0x0
	beq _020A0824
_020A084C:
	ldr r1, [r4, #0x828]
	ldr r0, [r4, #0x82c]
	sub r0, r1, r0
	str r0, [r6, #0x0]
	ldr r1, [r4, #0x824]
	ldr r0, [r4, #0x82c]
	add r0, r1, r0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A0870: .word CPSiFree

	arm_func_start CPSi_SslConnect
CPSi_SslConnect: ; 0x020A0874
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrb r1, [r5, #0x8]
	ldr r4, [r5, #0xc]
	cmp r1, #0x4
	beq _020A08A8
	bl CPSi_TcpConnectRaw
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, #0x1
	ldmneia sp!, {r4-r5,lr}
	bxne lr
_020A08A8:
	mov r1, #0x0
	strb r1, [r4, #0x455]
	str r1, [r4, #0x1d4]
	add r0, r4, #0x2ec
	strb r1, [r4, #0x454]
	bl CPSi_sha1_init
	add r0, r4, #0x3a4
	bl CPSi_md5_init
	mov r0, r5
	bl ssl_connect_try
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start ssl_connect_try
ssl_connect_try: ; 0x020A08DC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r4, [r5, #0xc]
	bl send_client_hello
_020A08F0:
	mov r0, r5
	bl parse_record
	cmp r0, #0x9
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	cmp r0, #0x4
	beq _020A0920
	ldrb r0, [r4, #0x31]
	cmp r0, #0x0
	beq _020A08F0
_020A0920:
	ldrb r0, [r4, #0x31]
	cmp r0, #0x0
	beq _020A095C
	mov r0, r4
	bl create_key_block
	mov r0, r5
	bl mustget_change_cipher_spec_and_finished
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, #0x1
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r0, r5
	bl send_change_cipher_spec_and_finished
	b _020A09B4
_020A095C:
	mov r0, r5
	bl send_client_key_exchange
	mov r0, r4
	bl create_master_secret
	ldrb r0, [r4, #0x30]
	cmp r0, #0x0
	beq _020A0988
	ldrh r2, [r5, #0x18]
	ldr r1, [r5, #0x1c]
	mov r0, r4
	bl cache_session
_020A0988:
	mov r0, r4
	bl create_key_block
	mov r0, r5
	bl send_change_cipher_spec_and_finished
	mov r0, r5
	bl mustget_change_cipher_spec_and_finished
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, #0x1
	ldmneia sp!, {r4-r5,lr}
	bxne lr
_020A09B4:
	mov r0, #0x8
	strb r0, [r4, #0x455]
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start CPSi_SslListen
CPSi_SslListen: ; 0x020A09CC
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	ldr r8, [r9, #0xc]
	add r5, r8, #0x2ec
	add r4, r8, #0x3a4
	mov r7, #0x0
	mov r6, #0x1
_020A09EC:
	mov r0, r9
	bl CPSi_TcpListenRaw
	strb r7, [r8, #0x455]
	str r7, [r8, #0x1d4]
	mov r0, r5
	strb r6, [r8, #0x454]
	bl CPSi_sha1_init
	mov r0, r4
	bl CPSi_md5_init
	mov r0, r9
	bl ssl_listen_try
	cmp r0, #0x0
	moveq r0, #0x8
	addeq sp, sp, #0x4
	streqb r0, [r8, #0x455]
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r0, r9
	bl CPSi_TcpShutdownRaw
	ldrh r0, [r9, #0x1a]
	strh r0, [r9, #0x18]
	ldr r0, [r9, #0x20]
	str r0, [r9, #0x1c]
	b _020A09EC
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start ssl_listen_try
ssl_listen_try:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl parse_record
	cmp r0, #0x1
	movne r0, #0x1
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r0, r4
	bl send_server_hello
	cmp r0, #0x0
	beq _020A0AB0
	ldr r0, [r4, #0xc]
	bl create_key_block
	mov r0, r4
	bl send_change_cipher_spec_and_finished
	mov r0, r4
	bl mustget_change_cipher_spec_and_finished
	cmp r0, #0x0
	beq _020A0AE8
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A0AB0:
	mov r0, r4
	bl parse_record
	cmp r0, #0x5
	movne r0, #0x1
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r0, r4
	bl mustget_change_cipher_spec_and_finished
	cmp r0, #0x0
	movne r0, #0x1
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r0, r4
	bl send_change_cipher_spec_and_finished
_020A0AE8:
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start mustget_change_cipher_spec_and_finished
mustget_change_cipher_spec_and_finished:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl parse_record
	cmp r0, #0x7
	movne r0, #0x1
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r0, r4
	bl parse_record
	cmp r0, #0x6
	movne r0, #0x1
	moveq r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start send_client_key_exchange
send_client_key_exchange: ; 0x020A0B2C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r11, r0
	ldr r10, [r11, #0xc]
	mov r0, #0x3
	strb r0, [r10, #0x0]
	mov r0, #0x0
	strb r0, [r10, #0x1]
	add r0, r10, #0x2
	mov r1, #0x2e
	bl set_random
	ldr r4, [r10, #0x594]
	ldr r0, _020A0DD4 ; =CPSiAlloc
	mov r1, r4, lsl #0x1
	ldr r2, [r0, #0x0]
	add r1, r1, r1, lsr #0x1f
	mov r0, r4
	mov r6, r1, asr #0x1
	blx r2
	movs r5, r0
	moveq r0, #0x9
	addeq sp, sp, #0xc
	streqb r0, [r10, #0x455]
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	mov r0, #0x0
	strb r0, [r5, #0x0]
	mov r2, #0x2
	add r0, r5, #0x2
	sub r1, r4, #0x33
	strb r2, [r5, #0x1]
	bl set_random
	add r1, r5, r4
	mov r0, r10
	sub r3, r4, #0x31
	mov r7, #0x0
	sub r1, r1, #0x30
	mov r2, #0x30
	strb r7, [r5, r3]
	bl MI_CpuCopy8
	ldr r1, _020A0DD4 ; =CPSiAlloc
	mov r0, r6, lsl #0x3
	ldr r1, [r1, #0x0]
	blx r1
	movs r9, r0
	bne _020A0C08
	ldr r1, _020A0DD8 ; =CPSiFree
	mov r0, r5
	ldr r1, [r1, #0x0]
	blx r1
	mov r0, #0x9
	add sp, sp, #0xc
	strb r0, [r10, #0x455]
	ldmia sp!, {r4-r11,lr}
	bx lr
_020A0C08:
	add r0, r9, r6, lsl #0x1
	add r8, r0, r6, lsl #0x1
	mov r1, r5
	mov r2, r4
	mov r3, r6
	str r0, [sp, #0x4]
	add r7, r8, r6, lsl #0x1
	bl CPSi_big_from_char
	ldr r1, _020A0DDC ; =0x00000598
	ldr r2, [r10, #0x5a0]
	mov r0, r8
	add r1, r10, r1
	mov r3, r6
	bl CPSi_big_from_char
	ldr r1, _020A0DE0 ; =0x00000494
	mov r0, r7
	mov r2, r4
	add r1, r10, r1
	mov r3, r6
	bl CPSi_big_from_char
	bl enter_computebound
	mov r3, r6
	mov r6, r0
	ldr r1, [sp, #0x4]
	mov r2, r8
	mov r0, r9
	str r7, [sp, #0x0]
	bl CPSi_big_power
	mov r0, r6
	bl exit_computebound
	ldr r1, _020A0DD4 ; =CPSiAlloc
	add r0, r4, #0x49
	ldr r1, [r1, #0x0]
	blx r1
	movs r6, r0
	bne _020A0CCC
	ldr r1, _020A0DD8 ; =CPSiFree
	mov r0, r5
	ldr r1, [r1, #0x0]
	blx r1
	ldr r1, _020A0DD8 ; =CPSiFree
	mov r0, r9
	ldr r1, [r1, #0x0]
	blx r1
	mov r0, #0x9
	add sp, sp, #0xc
	strb r0, [r10, #0x455]
	ldmia sp!, {r4-r11,lr}
	bx lr
_020A0CCC:
	mov r0, #0x16
	strb r0, [r6, #0x0]
	mov r1, #0x3
	add r0, r4, #0x4
	strb r1, [r6, #0x1]
	mov r1, #0x0
	strb r1, [r6, #0x2]
	mov r1, r0, asr #0x8
	strb r1, [r6, #0x3]
	add r2, r6, #0x9
	strb r0, [r6, #0x4]
	mov r0, #0x10
	strb r0, [r6, #0x5]
	mov r0, r4, asr #0x10
	strb r0, [r6, #0x6]
	mov r0, r4, asr #0x8
	strb r0, [r6, #0x7]
	mov r0, r2
	strb r4, [r6, #0x8]
	ands r1, r4, #0x1
	beq _020A0D38
	add r0, r4, r4, lsr #0x1f
	mov r0, r0, asr #0x1
	mov r0, r0, lsl #0x1
	ldrh r1, [r9, r0]
	add r0, r2, #0x1
	strb r1, [r2, #0x0]
_020A0D38:
	add r1, r4, r4, lsr #0x1f
	mov r1, r1, asr #0x1
	subs r7, r1, #0x1
	bmi _020A0D70
_020A0D48:
	mov r3, r7, lsl #0x1
	ldrh r1, [r9, r3]
	add r2, r0, #0x1
	subs r7, r7, #0x1
	mov r1, r1, asr #0x8
	strb r1, [r0, #0x0]
	ldrh r1, [r9, r3]
	add r0, r0, #0x2
	strb r1, [r2, #0x0]
	bpl _020A0D48
_020A0D70:
	mov r2, #0x0
	mov r0, r6
	mov r3, r2
	add r1, r4, #0x9
	str r11, [sp, #0x0]
	bl CPSi_TcpWrite2Raw
	mov r0, r10
	add r1, r6, #0x5
	add r2, r4, #0x4
	bl update_digest
	ldr r1, _020A0DD8 ; =CPSiFree
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	ldr r1, _020A0DD8 ; =CPSiFree
	mov r0, r9
	ldr r1, [r1, #0x0]
	blx r1
	ldr r1, _020A0DD8 ; =CPSiFree
	mov r0, r5
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A0DD4: .word CPSiAlloc
_020A0DD8: .word CPSiFree
_020A0DDC: .word 0x00000598
_020A0DE0: .word 0x00000494

	arm_func_start send_client_hello
send_client_hello: ; 0x020A0DE4
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	ldr r1, _020A0F88 ; =CPSiAlloc
	mov r8, r0
	ldr r1, [r1, #0x0]
	mov r0, #0x98
	ldr r7, [r8, #0xc]
	blx r1
	movs r6, r0
	moveq r0, #0x9
	addeq sp, sp, #0x8
	streqb r0, [r7, #0x455]
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r0, #0x3
	strb r0, [r6, #0x9]
	add r5, r6, #0x9
	mov r0, #0x0
	strb r0, [r5, #0x1]
	bl date2sec
	mov r1, r0, lsr #0x18
	strb r1, [r7, #0x34]
	mov r1, r0, lsr #0x10
	strb r1, [r7, #0x35]
	mov r1, r0, lsr #0x8
	strb r1, [r7, #0x36]
	strb r0, [r7, #0x37]
	add r0, r7, #0x38
	mov r1, #0x1c
	bl set_random
	add r0, r7, #0x34
	add r1, r5, #0x2
	mov r2, #0x20
	bl MI_CpuCopy8
	ldrh r2, [r8, #0x18]
	ldr r1, [r8, #0x1c]
	mov r0, r7
	bl find_session_from_IP
	ldrb r0, [r7, #0x30]
	cmp r0, #0x0
	moveq r0, #0x0
	streqb r0, [r5, #0x22]
	addeq r5, r5, #0x23
	beq _020A0EAC
	mov r2, #0x20
	add r0, r7, #0x74
	add r1, r5, #0x23
	strb r2, [r5, #0x22]
	bl MI_CpuCopy8
	add r5, r5, #0x43
_020A0EAC:
	mov r4, #0x0
	strb r4, [r5, #0x0]
	mov r0, #0x4
	strb r0, [r5, #0x1]
	ldr r2, _020A0F8C ; =pairlist
	add r5, r5, #0x2
_020A0EC4:
	mov r3, r4, lsl #0x1
	ldrh r0, [r2, r3]
	add r4, r4, #0x1
	add r1, r5, #0x1
	mov r0, r0, asr #0x8
	strb r0, [r5, #0x0]
	ldrh r0, [r2, r3]
	cmp r4, #0x2
	add r5, r5, #0x2
	strb r0, [r1, #0x0]
	blo _020A0EC4
	mov r3, #0x1
	mov r2, #0x0
	strb r3, [r5, #0x0]
	add r0, r5, #0x2
	sub r0, r0, r6
	sub r4, r0, #0x5
	strb r2, [r5, #0x1]
	sub r1, r4, #0x4
	mov r0, #0x16
	strb r0, [r6, #0x0]
	mov r0, #0x3
	strb r0, [r6, #0x1]
	strb r2, [r6, #0x2]
	mov r0, r4, asr #0x8
	strb r0, [r6, #0x3]
	strb r4, [r6, #0x4]
	strb r3, [r6, #0x5]
	mov r0, r1, asr #0x10
	strb r0, [r6, #0x6]
	mov r0, r1, asr #0x8
	strb r0, [r6, #0x7]
	strb r1, [r6, #0x8]
	mov r0, r6
	mov r3, r2
	add r1, r4, #0x5
	str r8, [sp, #0x0]
	bl CPSi_TcpWrite2Raw
	mov r0, r7
	mov r2, r4
	add r1, r6, #0x5
	bl update_digest
	ldr r1, _020A0F90 ; =CPSiFree
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A0F88: .word CPSiAlloc
_020A0F8C: .word pairlist
_020A0F90: .word CPSiFree

	arm_func_start send_change_cipher_spec_and_finished
send_change_cipher_spec_and_finished: ; 0x020A0F94
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	ldr r1, _020A10EC ; =CPSiAlloc
	mov r6, r0
	ldr r1, [r1, #0x0]
	mov r0, #0x83
	ldr r5, [r6, #0xc]
	blx r1
	movs r4, r0
	moveq r0, #0x9
	addeq sp, sp, #0x8
	streqb r0, [r5, #0x455]
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r0, #0x14
	strb r0, [r4, #0x0]
	mov r0, #0x3
	strb r0, [r4, #0x1]
	mov r1, #0x0
	strb r1, [r4, #0x2]
	strb r1, [r4, #0x3]
	mov r3, #0x1
	strb r3, [r4, #0x4]
	add r0, r5, #0x1cc
	mov r2, #0x8
	strb r3, [r4, #0x5]
	bl MI_CpuFill8
	mov r0, #0x16
	strb r0, [r4, #0x6]
	mov r0, #0x3
	strb r0, [r4, #0x7]
	mov r1, #0x0
	strb r1, [r4, #0x8]
	strb r1, [r4, #0x9]
	mov r0, #0x28
	strb r0, [r4, #0xa]
	mov r0, #0x14
	strb r0, [r4, #0xb]
	strb r1, [r4, #0xc]
	strb r1, [r4, #0xd]
	mov r3, #0x24
	add r0, r5, #0x3a4
	add r1, r5, #0x3fc
	mov r2, #0x58
	strb r3, [r4, #0xe]
	bl MI_CpuCopy8
	mov r0, r5
	add r1, r4, #0xf
	mov r2, #0x0
	bl finished_md5
	add r0, r5, #0x3fc
	add r1, r5, #0x3a4
	mov r2, #0x58
	bl MI_CpuCopy8
	add r0, r5, #0x2ec
	add r1, r5, #0x348
	mov r2, #0x5c
	bl MI_CpuCopy8
	mov r0, r5
	add r1, r4, #0x1f
	mov r2, #0x0
	bl finished_sha1
	add r0, r5, #0x348
	add r1, r5, #0x2ec
	mov r2, #0x5c
	bl MI_CpuCopy8
	mov r0, r5
	add r1, r4, #0xb
	mov r2, #0x28
	bl update_digest
	mov r0, r5
	add r1, r4, #0x6
	bl make_ciphertext
	mov r2, #0x0
	add r1, r0, #0x6
	mov r0, r4
	mov r3, r2
	str r6, [sp, #0x0]
	bl CPSi_TcpWrite2Raw
	ldr r1, _020A10F0 ; =CPSiFree
	mov r0, r4
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A10EC: .word CPSiAlloc
_020A10F0: .word CPSiFree

	arm_func_start send_server_hello
send_server_hello:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	ldr r7, [r9, #0xc]
	ldr r4, [r7, #0x820]
	cmp r4, #0x0
	ldrne r8, [r4, #0x0]
	moveq r8, #0x0
	bl date2sec
	mov r1, r0, lsr #0x18
	strb r1, [r7, #0x54]
	mov r1, r0, lsr #0x10
	strb r1, [r7, #0x55]
	mov r1, r0, lsr #0x8
	strb r1, [r7, #0x56]
	strb r0, [r7, #0x57]
	add r0, r7, #0x58
	mov r1, #0x1c
	bl set_random
	ldr r1, _020A1360 ; =CPSiAlloc
	add r0, r8, #0x9d
	ldr r1, [r1, #0x0]
	blx r1
	movs r6, r0
	moveq r0, #0x9
	streqb r0, [r7, #0x455]
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r0, #0x2
	add r5, r6, #0x5
	strb r0, [r6, #0x5]
	mov r3, #0x0
	strb r3, [r5, #0x1]
	strb r3, [r5, #0x2]
	mov r0, #0x46
	strb r0, [r5, #0x3]
	mov r0, #0x3
	strb r0, [r5, #0x4]
	add r0, r7, #0x54
	add r1, r5, #0x6
	mov r2, #0x20
	strb r3, [r5, #0x5]
	bl MI_CpuCopy8
	mov r2, #0x20
	strb r2, [r5, #0x26]
	ldrb r0, [r7, #0x30]
	cmp r0, #0x0
	beq _020A11D8
	add r0, r7, #0x74
	add r1, r5, #0x27
	bl MI_CpuCopy8
	mov r0, #0x1
	strb r0, [r7, #0x31]
	add r5, r5, #0x47
	b _020A1238
_020A11D8:
	add r0, r5, #0x27
	mov r1, #0x1c
	bl set_random
	ldr r0, _020A1364 ; =UNK_021CA6E4
	add r2, r5, #0x46
	ldr r3, [r0, #0x0]
	add r1, r7, #0x74
	mov r0, r3, lsr #0x18
	strb r0, [r5, #0x43]
	mov r0, r3, lsr #0x10
	strb r0, [r5, #0x44]
	mov r0, r3, lsr #0x8
	strb r0, [r5, #0x45]
	add r5, r5, #0x47
	sub r0, r5, #0x20
	strb r3, [r2, #0x0]
	mov r2, #0x20
	bl MI_CpuCopy8
	ldr r0, _020A1364 ; =UNK_021CA6E4
	mov r1, #0x0
	ldr r2, [r0, #0x0]
	add r2, r2, #0x1
	str r2, [r0, #0x0]
	strb r1, [r7, #0x31]
_020A1238:
	ldrh r2, [r7, #0x32]
	mov r0, #0x0
	mov r2, r2, asr #0x8
	strb r2, [r5, #0x0]
	ldrh r2, [r7, #0x32]
	strb r2, [r5, #0x1]
	strb r0, [r5, #0x2]
	ldrb r0, [r7, #0x31]
	add r5, r5, #0x3
	cmp r0, #0x0
	bne _020A12EC
	cmp r8, #0x0
	beq _020A12D0
	mov r0, #0xb
	add r2, r8, #0x6
	strb r0, [r5, #0x0]
	mov r0, r2, asr #0x10
	strb r0, [r5, #0x1]
	mov r0, r2, asr #0x8
	strb r0, [r5, #0x2]
	add r1, r8, #0x3
	strb r2, [r5, #0x3]
	mov r0, r1, asr #0x10
	strb r0, [r5, #0x4]
	mov r0, r1, asr #0x8
	strb r0, [r5, #0x5]
	strb r1, [r5, #0x6]
	mov r0, r8, asr #0x10
	strb r0, [r5, #0x7]
	mov r0, r8, asr #0x8
	strb r0, [r5, #0x8]
	strb r8, [r5, #0x9]
	add r5, r5, #0xa
	ldr r0, [r4, #0x4]
	mov r1, r5
	mov r2, r8
	bl MI_CpuCopy8
	add r5, r5, r8
_020A12D0:
	mov r0, #0xe
	strb r0, [r5, #0x0]
	mov r1, #0x0
	strb r1, [r5, #0x1]
	strb r1, [r5, #0x2]
	strb r1, [r5, #0x3]
	add r5, r5, #0x4
_020A12EC:
	mov r0, #0x16
	sub r1, r5, r6
	sub r4, r1, #0x5
	strb r0, [r6, #0x0]
	mov r0, #0x3
	strb r0, [r6, #0x1]
	mov r0, #0x0
	strb r0, [r6, #0x2]
	mov r0, r4, asr #0x8
	strb r0, [r6, #0x3]
	mov r0, r7
	mov r2, r4
	add r1, r6, #0x5
	strb r4, [r6, #0x4]
	bl update_digest
	mov r2, #0x0
	mov r0, r6
	mov r3, r2
	add r1, r4, #0x5
	str r9, [sp, #0x0]
	bl CPSi_TcpWrite2Raw
	ldr r1, _020A1368 ; =CPSiFree
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	ldrb r0, [r7, #0x31]
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020A1360: .word CPSiAlloc
_020A1364: .word UNK_021CA6E4 ; anonymous
_020A1368: .word CPSiFree

	arm_func_start CPS_SslAddRandomSeed
CPS_SslAddRandomSeed:
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x60
	mov r6, r0
	add r0, sp, #0x0
	mov r5, r1
	bl CPSi_sha1_init
	bl OS_DisableInterrupts
	mov r4, r0
	ldr r1, _020A13D8 ; =pool
	add r0, sp, #0x0
	mov r2, #0x14
	bl CPSi_sha1_calc
	mov r1, r6
	mov r2, r5
	add r0, sp, #0x0
	bl CPSi_sha1_calc
	ldr r1, _020A13D8 ; =pool
	add r0, sp, #0x0
	bl CPSi_sha1_result
	mov r0, r4
	bl OS_RestoreInterrupts
	ldr r0, _020A13DC ; =pool_initialized
	mov r1, #0x1
	strb r1, [r0, #0x0]
	add sp, sp, #0x60
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A13D8: .word pool
_020A13DC: .word pool_initialized

	arm_func_start set_random
set_random: ; 0x020A13E0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x7c
	ldr r2, _020A1518 ; =pool_initialized
	mov r10, r0
	ldrb r0, [r2, #0x0]
	mov r9, r1
	cmp r0, #0x0
	bne _020A1448
	ldr r2, _020A151C ; =CPSiRand32ctx
	add r0, sp, #0x4
	ldr r4, [r2, #0x8]
	ldr r3, [r2, #0x0]
	ldr r1, [r2, #0x4]
	umull r6, r5, r4, r3
	mla r5, r4, r1, r5
	ldr r1, [r2, #0xc]
	ldr r4, [r2, #0x10]
	mla r5, r1, r3, r5
	adds r4, r4, r6
	ldr r3, [r2, #0x14]
	mov r1, #0x4
	adc r3, r3, r5
	str r4, [r2, #0x0]
	str r3, [r2, #0x4]
	str r3, [sp, #0x4]
	bl CPS_SslAddRandomSeed
_020A1448:
	cmp r9, #0x0
	mov r7, #0x0
	addle sp, sp, #0x7c
	mov r1, #0x14
	ldmleia sp!, {r4-r11,lr}
	bxle lr
	add r6, sp, #0x1c
	mov r11, r1
	str r7, [sp, #0x0]
	mov r5, #0x1
	mov r4, #0x13
_020A1474:
	cmp r1, #0x14
	bne _020A14EC
	mov r0, r6
	bl CPSi_sha1_init
	bl OS_DisableInterrupts
	mov r8, r0
	ldr r1, _020A1520 ; =pool
	mov r0, r6
	mov r2, r11
	bl CPSi_sha1_calc
	mov r0, r6
	add r1, sp, #0x8
	bl CPSi_sha1_result_prng
	ldr r2, _020A1524 ; =pool+0x13
	mov r12, r5
	mov lr, r4
	add r3, sp, #0x1b
_020A14B8:
	ldrb r1, [r2, #0x0]
	ldrb r0, [r3], #-0x1
	subs lr, lr, #0x1
	add r0, r1, r0
	add r0, r12, r0
	strb r0, [r2, #0x0]
	mov r12, r0, lsr #0x8
	sub r2, r2, #0x1
	bpl _020A14B8
	str r0, [sp, #0x4]
	mov r0, r8
	bl OS_RestoreInterrupts
	ldr r1, [sp, #0x0]
_020A14EC:
	add r0, sp, #0x8
	ldrb r0, [r0, r1]
	add r1, r1, #0x1
	cmp r0, #0x0
	strneb r0, [r10, r7]
	addne r7, r7, #0x1
	cmp r7, r9
	blt _020A1474
	add sp, sp, #0x7c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A1518: .word pool_initialized
_020A151C: .word CPSiRand32ctx
_020A1520: .word pool
_020A1524: .word pool+0x13

	arm_func_start parse_record
parse_record: ; 0x020A1528
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r5, r0
	ldr r4, [r5, #0xc]
	add r6, sp, #0x0
_020A153C:
	mov r0, r6
	mov r1, r5
	bl CPSi_TcpReadRaw
	ldr r1, [sp, #0x0]
	cmp r1, #0x0
	moveq r0, #0x9
	addeq sp, sp, #0x8
	streqb r0, [r4, #0x455]
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	cmp r1, #0x5
	blo _020A153C
	ldrb r1, [r0, #0x0]
	cmp r1, #0x80
	bne _020A1634
	ldrb r1, [r4, #0x454]
	cmp r1, #0x0
	beq _020A1628
	ldrb r1, [r4, #0x455]
	cmp r1, #0x0
	bne _020A1628
	ldrb r2, [r0, #0x1]
	mov r1, r5
	mov r0, #0x2
	str r2, [sp, #0x0]
	bl CPSi_SocConsumeRaw
	ldr r1, _020A16DC ; =CPSiAlloc
	ldr r0, [sp, #0x0]
	ldr r1, [r1, #0x0]
	blx r1
	movs r6, r0
	moveq r0, #0x9
	addeq sp, sp, #0x8
	streqb r0, [r4, #0x455]
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r1, [sp, #0x0]
	mov r2, r5
	bl tcp_read_raw_nbytes
	cmp r0, #0x0
	bne _020A15FC
	ldrb r0, [r6, #0x0]
	cmp r0, #0x1
	bne _020A15FC
	mov r0, r4
	add r1, r6, #0x1
	bl client_hello_v2
	b _020A1604
_020A15FC:
	mov r0, #0x9
	strb r0, [r4, #0x455]
_020A1604:
	ldr r2, [sp, #0x0]
	mov r0, r4
	mov r1, r6
	bl update_digest
	ldr r1, _020A16E0 ; =CPSiFree
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	b _020A16CC
_020A1628:
	mov r0, #0x9
	strb r0, [r4, #0x455]
	b _020A16CC
_020A1634:
	ldrb r2, [r0, #0x3]
	ldrb r0, [r0, #0x4]
	ldr r1, _020A16E4 ; =0x00004805
	add r0, r0, r2, lsl #0x8
	add r0, r0, #0x5
	str r0, [sp, #0x0]
	cmp r0, r1
	movhi r0, #0x9
	addhi sp, sp, #0x8
	strhib r0, [r4, #0x455]
	ldmhiia sp!, {r4-r6,lr}
	bxhi lr
	ldr r1, _020A16DC ; =CPSiAlloc
	ldr r1, [r1, #0x0]
	blx r1
	movs r6, r0
	moveq r0, #0x9
	addeq sp, sp, #0x8
	streqb r0, [r4, #0x455]
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r1, [sp, #0x0]
	mov r2, r5
	bl tcp_read_raw_nbytes
	cmp r0, #0x0
	beq _020A16C0
	ldr r1, _020A16E0 ; =CPSiFree
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	mov r0, #0x9
	add sp, sp, #0x8
	strb r0, [r4, #0x455]
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A16C0:
	mov r0, r4
	mov r1, r6
	bl parse_record_in_buf
_020A16CC:
	ldrb r0, [r4, #0x455]
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A16DC: .word CPSiAlloc
_020A16E0: .word CPSiFree
_020A16E4: .word 0x00004805

	arm_func_start parse_record_in_buf
parse_record_in_buf: ; 0x020A16E8
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	ldrb r0, [r8, #0x455]
	mov r7, r1
	cmp r0, #0x9
	bne _020A1718
	ldr r1, _020A1940 ; =CPSiFree
	mov r0, r7
	ldr r1, [r1, #0x0]
	blx r1
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A1718:
	ldrb r2, [r7, #0x3]
	ldrb r1, [r7, #0x4]
	add r0, r0, #0xf9
	and r0, r0, #0xff
	add r1, r1, r2, lsl #0x8
	cmp r0, #0x1
	add r5, r1, #0x5
	ldrb r4, [r7, #0x0]
	bhi _020A1744
	cmp r4, #0x15
	bne _020A1754
_020A1744:
	cmp r4, #0x15
	bne _020A1764
	cmp r5, #0x7
	bls _020A1764
_020A1754:
	mov r0, r8
	mov r1, r7
	bl make_plaintext
	mov r5, r0
_020A1764:
	sub r0, r4, #0x14
	cmp r0, #0x3
	add r6, r7, #0x5
	sub r5, r5, #0x5
	addls pc, pc, r0, lsl #0x2
	b _020A1920
	b _020A178C
	b _020A17BC
	b _020A17D0
	b _020A18FC
_020A178C:
	ldr r0, [r8, #0x1d4]
	cmp r0, #0x0
	moveq r0, #0x9
	streqb r0, [r8, #0x455]
	beq _020A1928
	add r0, r8, #0x2e4
	mov r1, #0x0
	mov r2, #0x8
	bl MI_CpuFill8
	mov r0, #0x7
	strb r0, [r8, #0x455]
	b _020A1928
_020A17BC:
	ldrb r0, [r6, #0x0]
	cmp r0, #0x2
	moveq r0, #0x9
	streqb r0, [r8, #0x455]
	b _020A1928
_020A17D0:
	ldrb r1, [r6, #0x1]
	ldrb r0, [r6, #0x2]
	ldrb r3, [r6, #0x0]
	ldrb r2, [r6, #0x3]
	mov r1, r1, lsl #0x10
	add r0, r1, r0, lsl #0x8
	cmp r3, #0xb
	add r4, r2, r0
	add r6, r6, #0x4
	bgt _020A1824
	cmp r3, #0xb
	bge _020A1898
	cmp r3, #0x2
	bgt _020A18C4
	cmp r3, #0x1
	blt _020A18C4
	cmp r3, #0x1
	beq _020A1850
	cmp r3, #0x2
	beq _020A1888
	b _020A18C4
_020A1824:
	cmp r3, #0x14
	bgt _020A18C4
	cmp r3, #0xe
	blt _020A18C4
	cmp r3, #0xe
	beq _020A18A8
	cmp r3, #0x10
	beq _020A1878
	cmp r3, #0x14
	beq _020A18B4
	b _020A18C4
_020A1850:
	ldrb r0, [r8, #0x454]
	cmp r0, #0x0
	beq _020A18CC
	ldrb r0, [r8, #0x455]
	cmp r0, #0x0
	bne _020A18CC
	mov r0, r8
	mov r1, r6
	bl client_hello
	b _020A18CC
_020A1878:
	mov r0, r8
	mov r1, r6
	bl rcv_client_key_exchange
	b _020A18CC
_020A1888:
	mov r0, r8
	mov r1, r6
	bl rcv_server_hello
	b _020A18CC
_020A1898:
	mov r0, r8
	mov r1, r6
	bl rcv_certificate
	b _020A18CC
_020A18A8:
	mov r0, #0x4
	strb r0, [r8, #0x455]
	b _020A18CC
_020A18B4:
	mov r0, r8
	mov r1, r6
	bl rcv_finished
	b _020A18CC
_020A18C4:
	mov r0, #0x9
	strb r0, [r8, #0x455]
_020A18CC:
	mov r0, r8
	sub r1, r6, #0x4
	add r2, r4, #0x4
	bl update_digest
	add r0, r4, #0x4
	add r6, r6, r4
	subs r5, r5, r0
	beq _020A1928
	ldrb r0, [r8, #0x455]
	cmp r0, #0x9
	bne _020A17D0
	b _020A1928
_020A18FC:
	str r7, [r8, #0x824]
	mov r0, #0x5
	str r0, [r8, #0x82c]
	add r0, r5, #0x5
	str r0, [r8, #0x828]
	mov r0, #0x1
	strb r0, [r8, #0x456]
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A1920:
	mov r0, #0x9
	strb r0, [r8, #0x455]
_020A1928:
	ldr r1, _020A1940 ; =CPSiFree
	mov r0, r7
	ldr r1, [r1, #0x0]
	blx r1
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A1940: .word CPSiFree

	arm_func_start update_digest
update_digest: ; 0x020A1944
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	add r0, r6, #0x2ec
	bl CPSi_sha1_calc
	mov r1, r5
	mov r2, r4
	add r0, r6, #0x3a4
	bl CPSi_md5_calc
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start tcp_read_raw_nbytes
tcp_read_raw_nbytes:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	add r4, sp, #0x0
_020A198C:
	mov r0, r4
	mov r1, r5
	bl CPSi_TcpReadRaw
	ldr r1, [sp, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	cmp r1, r6
	strhi r6, [sp, #0x0]
	ldr r2, [sp, #0x0]
	mov r1, r7
	bl MI_CpuCopy8
	ldr r0, [sp, #0x0]
	mov r1, r5
	bl CPSi_SocConsumeRaw
	ldr r0, [sp, #0x0]
	sub r6, r6, r0
	cmp r6, #0x0
	add r7, r7, r0
	bgt _020A198C
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start make_ciphertext
make_ciphertext: ; 0x020A19F4
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x30
	mov r5, r1
	mov r6, r0
	ldrh r0, [r6, #0x32]
	ldrb r3, [r5, #0x3]
	ldrb r2, [r5, #0x4]
	add r1, r5, #0x5
	cmp r0, #0x4
	add r4, r2, r3, lsl #0x8
	add r8, r1, r4
	beq _020A1A30
	cmp r0, #0x5
	beq _020A1B04
	b _020A1BD4
_020A1A30:
	add r7, r6, #0x3fc
	mov r0, r7
	bl CPSi_md5_init
	ldr r1, [r6, #0xbc]
	mov r0, r7
	mov r2, #0x10
	bl CPSi_md5_calc
	add r0, sp, #0x0
	mov r1, #0x36
	mov r2, #0x30
	bl MI_CpuFill8
	mov r0, r7
	add r1, sp, #0x0
	mov r2, #0x30
	bl CPSi_md5_calc
	mov r0, r7
	add r1, r6, #0x1cc
	mov r2, #0x8
	bl CPSi_md5_calc
	mov r0, r7
	mov r1, r5
	mov r2, #0x1
	bl CPSi_md5_calc
	mov r0, r7
	add r1, r5, #0x3
	add r2, r4, #0x2
	bl CPSi_md5_calc
	mov r0, r7
	mov r1, r8
	bl CPSi_md5_result
	mov r0, r7
	bl CPSi_md5_init
	ldr r1, [r6, #0xbc]
	mov r0, r7
	mov r2, #0x10
	bl CPSi_md5_calc
	add r0, sp, #0x0
	mov r1, #0x5c
	mov r2, #0x30
	bl MI_CpuFill8
	mov r0, r7
	add r1, sp, #0x0
	mov r2, #0x30
	bl CPSi_md5_calc
	mov r0, r7
	mov r1, r8
	mov r2, #0x10
	bl CPSi_md5_calc
	mov r0, r7
	mov r1, r8
	bl CPSi_md5_result
	add r4, r4, #0x10
	b _020A1BD4
_020A1B04:
	add r7, r6, #0x348
	mov r0, r7
	bl CPSi_sha1_init
	ldr r1, [r6, #0xbc]
	mov r0, r7
	mov r2, #0x14
	bl CPSi_sha1_calc
	add r0, sp, #0x0
	mov r1, #0x36
	mov r2, #0x28
	bl MI_CpuFill8
	mov r0, r7
	add r1, sp, #0x0
	mov r2, #0x28
	bl CPSi_sha1_calc
	mov r0, r7
	add r1, r6, #0x1cc
	mov r2, #0x8
	bl CPSi_sha1_calc
	mov r0, r7
	mov r1, r5
	mov r2, #0x1
	bl CPSi_sha1_calc
	mov r0, r7
	add r1, r5, #0x3
	add r2, r4, #0x2
	bl CPSi_sha1_calc
	mov r0, r7
	mov r1, r8
	bl CPSi_sha1_result
	mov r0, r7
	bl CPSi_sha1_init
	ldr r1, [r6, #0xbc]
	mov r0, r7
	mov r2, #0x14
	bl CPSi_sha1_calc
	add r0, sp, #0x0
	mov r1, #0x5c
	mov r2, #0x28
	bl MI_CpuFill8
	mov r0, r7
	add r1, sp, #0x0
	mov r2, #0x28
	bl CPSi_sha1_calc
	mov r0, r7
	mov r1, r8
	mov r2, #0x14
	bl CPSi_sha1_calc
	mov r0, r7
	mov r1, r8
	bl CPSi_sha1_result
	add r4, r4, #0x14
_020A1BD4:
	mov r0, r4, asr #0x8
	strb r0, [r5, #0x3]
	mov r2, r4
	add r0, r6, #0xc8
	add r1, r5, #0x5
	strb r4, [r5, #0x4]
	bl CPSi_rc4_crypt
	add r0, r6, #0x1d4
	bl add1_be8
	add r0, r4, #0x5
	add sp, sp, #0x30
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start make_plaintext
make_plaintext: ; 0x020A1C08
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x44
	mov r6, r1
	ldrb r3, [r6, #0x3]
	ldrb r2, [r6, #0x4]
	mov r7, r0
	add r1, r6, #0x5
	add r2, r2, r3, lsl #0x8
	bl decrypt
	ldrh r1, [r7, #0x32]
	mov r5, r0
	cmp r1, #0x4
	beq _020A1C48
	cmp r1, #0x5
	beq _020A1D2C
	b _020A1E0C
_020A1C48:
	sub r5, r5, #0x10
	mov r0, r5, asr #0x8
	strb r0, [r6, #0x3]
	add r4, r7, #0x3fc
	mov r0, r4
	strb r5, [r6, #0x4]
	bl CPSi_md5_init
	ldr r1, [r7, #0x1d4]
	mov r0, r4
	mov r2, #0x10
	bl CPSi_md5_calc
	add r0, sp, #0x14
	mov r1, #0x36
	mov r2, #0x30
	bl MI_CpuFill8
	mov r0, r4
	add r1, sp, #0x14
	mov r2, #0x30
	bl CPSi_md5_calc
	mov r0, r4
	add r1, r7, #0x2e4
	mov r2, #0x8
	bl CPSi_md5_calc
	mov r0, r4
	mov r1, r6
	mov r2, #0x1
	bl CPSi_md5_calc
	mov r0, r4
	add r1, r6, #0x3
	add r2, r5, #0x2
	bl CPSi_md5_calc
	mov r0, r4
	add r1, sp, #0x0
	bl CPSi_md5_result
	mov r0, r4
	bl CPSi_md5_init
	ldr r1, [r7, #0x1d4]
	mov r0, r4
	mov r2, #0x10
	bl CPSi_md5_calc
	add r0, sp, #0x14
	mov r1, #0x5c
	mov r2, #0x30
	bl MI_CpuFill8
	mov r0, r4
	add r1, sp, #0x14
	mov r2, #0x30
	bl CPSi_md5_calc
	mov r0, r4
	add r1, sp, #0x0
	mov r2, #0x10
	bl CPSi_md5_calc
	mov r0, r4
	add r1, sp, #0x0
	bl CPSi_md5_result
	mov r4, #0x10
	b _020A1E0C
_020A1D2C:
	sub r5, r5, #0x14
	mov r0, r5, asr #0x8
	strb r0, [r6, #0x3]
	add r4, r7, #0x348
	mov r0, r4
	strb r5, [r6, #0x4]
	bl CPSi_sha1_init
	ldr r1, [r7, #0x1d4]
	mov r0, r4
	mov r2, #0x14
	bl CPSi_sha1_calc
	add r0, sp, #0x14
	mov r1, #0x36
	mov r2, #0x28
	bl MI_CpuFill8
	mov r0, r4
	add r1, sp, #0x14
	mov r2, #0x28
	bl CPSi_sha1_calc
	mov r0, r4
	add r1, r7, #0x2e4
	mov r2, #0x8
	bl CPSi_sha1_calc
	mov r0, r4
	mov r1, r6
	mov r2, #0x1
	bl CPSi_sha1_calc
	mov r0, r4
	add r1, r6, #0x3
	add r2, r5, #0x2
	bl CPSi_sha1_calc
	mov r0, r4
	add r1, sp, #0x0
	bl CPSi_sha1_result
	mov r0, r4
	bl CPSi_sha1_init
	ldr r1, [r7, #0x1d4]
	mov r0, r4
	mov r2, #0x14
	bl CPSi_sha1_calc
	add r0, sp, #0x14
	mov r1, #0x5c
	mov r2, #0x28
	bl MI_CpuFill8
	mov r0, r4
	add r1, sp, #0x14
	mov r2, #0x28
	bl CPSi_sha1_calc
	mov r0, r4
	add r1, sp, #0x0
	mov r2, #0x14
	bl CPSi_sha1_calc
	mov r0, r4
	add r1, sp, #0x0
	bl CPSi_sha1_result
	mov r4, #0x14
_020A1E0C:
	add r0, r6, #0x5
	add r1, sp, #0x0
	mov r2, r4
	add r0, r0, r5
	bl memcmp
	cmp r0, #0x0
	movne r0, #0x9
	strneb r0, [r7, #0x455]
	add r0, r7, #0x2ec
	bl add1_be8
	add r0, r5, #0x5
	add sp, sp, #0x44
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start decrypt
decrypt: ; 0x020A1E44
	stmdb sp!, {r4,lr}
	add r0, r0, #0x1e0
	mov r4, r2
	bl CPSi_rc4_crypt
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start add1_be8
add1_be8: ; 0x020A1E60
	mov r2, #0x8
_020A1E64:
	ldrb r1, [r0, #-0x1]!
	add r1, r1, #0x1
	ands r1, r1, #0xff
	strb r1, [r0, #0x0]
	bxne lr
	subs r2, r2, #0x1
	bne _020A1E64
	bx lr

	arm_func_start rcv_finished
rcv_finished: ; 0x020A1E84
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x14
	mov r5, r0
	mov r4, r1
	add r0, r5, #0x3a4
	add r1, r5, #0x3fc
	mov r2, #0x58
	bl MI_CpuCopy8
	add r1, sp, #0x0
	mov r0, r5
	mov r2, #0x1
	bl finished_md5
	add r0, r5, #0x3fc
	add r1, r5, #0x3a4
	mov r2, #0x58
	bl MI_CpuCopy8
	add r1, sp, #0x0
	mov r0, r4
	mov r2, #0x10
	bl memcmp
	cmp r0, #0x0
	movne r0, #0x9
	addne sp, sp, #0x14
	strneb r0, [r5, #0x455]
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	add r0, r5, #0x2ec
	add r1, r5, #0x348
	mov r2, #0x5c
	bl MI_CpuCopy8
	add r1, sp, #0x0
	mov r0, r5
	mov r2, #0x1
	bl finished_sha1
	add r0, r5, #0x348
	add r1, r5, #0x2ec
	mov r2, #0x5c
	bl MI_CpuCopy8
	add r1, sp, #0x0
	add r0, r4, #0x10
	mov r2, #0x14
	bl memcmp
	cmp r0, #0x0
	movne r0, #0x9
	strneb r0, [r5, #0x455]
	moveq r0, #0x6
	streqb r0, [r5, #0x455]
	add sp, sp, #0x14
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start finished_sha1
finished_sha1: ; 0x020A1F4C
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x28
	mov r6, r0
	ldrb r0, [r6, #0x454]
	mov r5, r1
	add r4, r6, #0x2ec
	eors r0, r0, r2
	beq _020A1F80
	ldr r1, _020A202C ; =UNK_02106290
	mov r0, r4
	mov r2, #0x4
	bl CPSi_sha1_calc
	b _020A1F90
_020A1F80:
	ldr r1, _020A2030 ; =UNK_02106298
	mov r0, r4
	mov r2, #0x4
	bl CPSi_sha1_calc
_020A1F90:
	mov r0, r4
	mov r1, r6
	mov r2, #0x30
	bl CPSi_sha1_calc
	add r0, sp, #0x0
	mov r1, #0x36
	mov r2, #0x28
	bl MI_CpuFill8
	add r1, sp, #0x0
	mov r0, r4
	mov r2, #0x28
	bl CPSi_sha1_calc
	mov r0, r4
	mov r1, r5
	bl CPSi_sha1_result
	mov r0, r4
	bl CPSi_sha1_init
	mov r1, r6
	mov r0, r4
	mov r2, #0x30
	bl CPSi_sha1_calc
	add r0, sp, #0x0
	mov r1, #0x5c
	mov r2, #0x28
	bl MI_CpuFill8
	mov r0, r4
	add r1, sp, #0x0
	mov r2, #0x28
	bl CPSi_sha1_calc
	mov r0, r4
	mov r1, r5
	mov r2, #0x14
	bl CPSi_sha1_calc
	mov r0, r4
	mov r1, r5
	bl CPSi_sha1_result
	add sp, sp, #0x28
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A202C: .word UNK_02106290
_020A2030: .word UNK_02106298

	arm_func_start finished_md5
finished_md5: ; 0x020A2034
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x30
	mov r6, r0
	ldrb r0, [r6, #0x454]
	mov r5, r1
	add r4, r6, #0x3a4
	eors r0, r0, r2
	beq _020A2068
	ldr r1, _020A2114 ; =UNK_02106290
	mov r0, r4
	mov r2, #0x4
	bl CPSi_md5_calc
	b _020A2078
_020A2068:
	ldr r1, _020A2118 ; =UNK_02106298
	mov r0, r4
	mov r2, #0x4
	bl CPSi_md5_calc
_020A2078:
	mov r0, r4
	mov r1, r6
	mov r2, #0x30
	bl CPSi_md5_calc
	add r0, sp, #0x0
	mov r1, #0x36
	mov r2, #0x30
	bl MI_CpuFill8
	add r1, sp, #0x0
	mov r0, r4
	mov r2, #0x30
	bl CPSi_md5_calc
	mov r0, r4
	mov r1, r5
	bl CPSi_md5_result
	mov r0, r4
	bl CPSi_md5_init
	mov r1, r6
	mov r0, r4
	mov r2, #0x30
	bl CPSi_md5_calc
	add r0, sp, #0x0
	mov r1, #0x5c
	mov r2, #0x30
	bl MI_CpuFill8
	mov r0, r4
	add r1, sp, #0x0
	mov r2, #0x30
	bl CPSi_md5_calc
	mov r0, r4
	mov r1, r5
	mov r2, #0x10
	bl CPSi_md5_calc
	mov r0, r4
	mov r1, r5
	bl CPSi_md5_result
	add sp, sp, #0x30
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A2114: .word UNK_02106290
_020A2118: .word UNK_02106298

	arm_func_start rcv_client_key_exchange
rcv_client_key_exchange: ; 0x020A211C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r2, [r4, #0x81c]
	bl decrypt_premaster_secret
	mov r0, r4
	bl create_master_secret
	mov r1, #0x0
	mov r0, r4
	mov r2, r1
	bl cache_session
	mov r0, r4
	bl create_key_block
	mov r0, #0x5
	strb r0, [r4, #0x455]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start create_key_block
create_key_block: ; 0x020A215C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	mov r10, r0
	ldrh r0, [r10, #0x32]
	cmp r0, #0x4
	beq _020A2190
	cmp r0, #0x5
	moveq r0, #0x14
	streq r0, [sp, #0x0]
	moveq r0, #0x10
	streq r0, [sp, #0x4]
	moveq r2, #0x0
	b _020A21A0
_020A2190:
	mov r0, #0x10
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r2, #0x0
_020A21A0:
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	mov r9, #0x0
	add r0, r1, r0
	add r0, r2, r0
	mov r0, r0, lsl #0x1
	str r0, [sp, #0x8]
	cmp r0, #0x0
	ble _020A22B8
	mov r0, #0x20
	str r0, [sp, #0x10]
	mov r0, #0x14
	mov r6, r9
	add r5, sp, #0x18
	str r9, [sp, #0xc]
	mov r4, #0x1
	mov r11, #0x30
	str r0, [sp, #0x14]
_020A21E8:
	add r7, r10, #0x348
	mov r0, r7
	bl CPSi_sha1_init
	add r0, r9, #0x41
	strb r0, [sp, #0x18]
	add r0, r9, #0x1
	ldr r8, [sp, #0xc]
	cmp r0, #0x0
	ble _020A222C
_020A220C:
	mov r0, r7
	mov r1, r5
	mov r2, r4
	bl CPSi_sha1_calc
	add r8, r8, #0x1
	add r0, r9, #0x1
	cmp r8, r0
	blt _020A220C
_020A222C:
	mov r0, r7
	mov r1, r10
	mov r2, r11
	bl CPSi_sha1_calc
	ldr r2, [sp, #0x10]
	mov r0, r7
	add r1, r10, #0x54
	bl CPSi_sha1_calc
	ldr r2, [sp, #0x10]
	mov r0, r7
	add r1, r10, #0x34
	bl CPSi_sha1_calc
	mov r0, r7
	add r1, sp, #0x19
	bl CPSi_sha1_result
	add r7, r10, #0x3fc
	mov r0, r7
	bl CPSi_md5_init
	mov r0, r7
	mov r1, r10
	mov r2, r11
	bl CPSi_md5_calc
	ldr r2, [sp, #0x14]
	mov r0, r7
	add r1, sp, #0x19
	bl CPSi_md5_calc
	add r1, r10, #0x74
	mov r0, r7
	add r1, r1, r6
	bl CPSi_md5_result
	ldr r0, [sp, #0x8]
	add r6, r6, #0x10
	cmp r6, r0
	add r9, r9, #0x1
	blt _020A21E8
_020A22B8:
	ldrb r0, [r10, #0x454]
	cmp r0, #0x0
	beq _020A2300
	add r1, r10, #0x74
	str r1, [r10, #0x1d4]
	ldr r0, [sp, #0x0]
	ldr r2, [r10, #0x1d4]
	add r1, r1, r0
	add r0, r2, r0, lsl #0x1
	str r0, [r10, #0x1d8]
	str r1, [r10, #0xbc]
	ldr r1, [r10, #0xbc]
	ldr r0, [sp, #0x0]
	add r1, r1, r0
	ldr r0, [sp, #0x4]
	add r0, r1, r0
	str r0, [r10, #0xc0]
	b _020A2338
_020A2300:
	add r1, r10, #0x74
	str r1, [r10, #0xbc]
	ldr r0, [sp, #0x0]
	ldr r2, [r10, #0xbc]
	add r1, r1, r0
	add r0, r2, r0, lsl #0x1
	str r0, [r10, #0xc0]
	str r1, [r10, #0x1d4]
	ldr r1, [r10, #0x1d4]
	ldr r0, [sp, #0x0]
	add r1, r1, r0
	ldr r0, [sp, #0x4]
	add r0, r1, r0
	str r0, [r10, #0x1d8]
_020A2338:
	ldr r1, [r10, #0x1d8]
	add r0, r10, #0x1e0
	mov r2, #0x10
	bl CPSi_rc4_init
	ldr r1, [r10, #0xc0]
	add r0, r10, #0xc8
	mov r2, #0x10
	bl CPSi_rc4_init
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start create_master_secret
create_master_secret: ; 0x020A2364
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x30
	mov r4, r0
	ldr r1, _020A23BC ; =UNK_021062A0
	add r0, sp, #0x0
	mov r2, r4
	bl create_ms_sub
	ldr r1, _020A23C0 ; =UNK_021062A4
	add r0, sp, #0x10
	mov r2, r4
	bl create_ms_sub
	ldr r1, _020A23C4 ; =UNK_021062A8
	add r0, sp, #0x20
	mov r2, r4
	bl create_ms_sub
	add r0, sp, #0x0
	mov r1, r4
	mov r2, #0x30
	bl MI_CpuCopy8
	add sp, sp, #0x30
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A23BC: .word UNK_021062A0
_020A23C0: .word UNK_021062A4
_020A23C4: .word UNK_021062A8

	arm_func_start create_ms_sub
create_ms_sub:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov r5, r2
	add r4, r5, #0x348
	mov r7, r0
	mov r6, r1
	mov r0, r4
	bl CPSi_sha1_init
	mov r0, r6
	bl strlen
	mov r2, r0
	mov r1, r6
	mov r0, r4
	bl CPSi_sha1_calc
	mov r0, r4
	mov r1, r5
	mov r2, #0x30
	bl CPSi_sha1_calc
	mov r0, r4
	add r1, r5, #0x34
	mov r2, #0x40
	bl CPSi_sha1_calc
	mov r0, r4
	add r1, sp, #0x0
	bl CPSi_sha1_result
	add r4, r5, #0x3fc
	mov r0, r4
	bl CPSi_md5_init
	mov r1, r5
	mov r0, r4
	mov r2, #0x30
	bl CPSi_md5_calc
	mov r0, r4
	add r1, sp, #0x0
	mov r2, #0x14
	bl CPSi_md5_calc
	mov r0, r4
	mov r1, r7
	bl CPSi_md5_result
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start decrypt_premaster_secret
decrypt_premaster_secret: ; 0x020A2470
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	movs r10, r2
	str r0, [sp, #0x8]
	mov r11, r1
	addeq sp, sp, #0x1c
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r0, [r10, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x1c
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	mov r0, r0, lsl #0x1
	add r0, r0, r0, lsr #0x1f
	mov r0, r0, asr #0x1
	add r9, r0, #0x1
	mov r0, #0x14
	mul r0, r9, r0
	ldr r1, _020A26C8 ; =CPSiAlloc
	ldr r1, [r1, #0x0]
	blx r1
	movs r8, r0
	addeq sp, sp, #0x1c
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	add r7, r8, r9, lsl #0x1
	add r6, r7, r9, lsl #0x1
	add r1, r6, r9, lsl #0x1
	str r1, [sp, #0xc]
	add r1, r1, r9, lsl #0x1
	add r5, r1, r9, lsl #0x1
	str r1, [sp, #0x10]
	ldr r2, [r10, #0x0]
	add r4, r5, r9, lsl #0x1
	mov r1, r11
	mov r3, r9
	add r11, r4, r9, lsl #0x1
	bl CPSi_big_from_char
	ldr r1, [r10, #0x1c]
	ldr r2, [r10, #0x18]
	mov r0, r7
	mov r3, r9
	bl CPSi_big_from_char
	ldr r1, [r10, #0xc]
	ldr r2, [r10, #0x8]
	mov r0, r5
	mov r3, r9
	bl CPSi_big_from_char
	bl enter_computebound
	str r0, [sp, #0x14]
	ldr r0, [sp, #0xc]
	str r5, [sp, #0x0]
	mov r1, r8
	mov r2, r7
	mov r3, r9
	bl CPSi_big_montpower
	ldr r1, [r10, #0x24]
	ldr r2, [r10, #0x20]
	mov r0, r7
	mov r3, r9
	bl CPSi_big_from_char
	ldr r1, [r10, #0x14]
	ldr r2, [r10, #0x10]
	mov r0, r5
	mov r3, r9
	bl CPSi_big_from_char
	ldr r0, [sp, #0x10]
	mov r1, r8
	mov r2, r7
	mov r3, r9
	str r5, [sp, #0x0]
	bl CPSi_big_montpower
	ldr r0, [sp, #0x14]
	bl exit_computebound
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x10]
	mov r0, r8
	mov r3, r9
	bl CPSi_big_sub
	ldr r1, [r10, #0x2c]
	ldr r2, [r10, #0x28]
	mov r0, r7
	mov r3, r9
	bl CPSi_big_from_char
	mov r0, r6
	mov r1, r8
	mov r2, r7
	mov r3, r9
	bl CPSi_big_mult
	ldr r1, [r10, #0x14]
	ldr r2, [r10, #0x10]
	mov r0, r7
	mov r3, r9
	bl CPSi_big_from_char
	mov r0, r8
	mov r1, r6
	mov r2, r7
	mov r3, r9
	bl CPSi_big_mult
	ldr r2, [sp, #0x10]
	mov r0, r6
	mov r1, r8
	mov r3, r9
	bl CPSi_big_add
	ldr r1, [r10, #0x4]
	ldr r2, [r10, #0x0]
	mov r0, r7
	mov r3, r9
	bl CPSi_big_from_char
	mov r0, r6
	mov r1, r9
	bl CPSi_big_sign
	cmp r0, #0x0
	bge _020A267C
	mov r0, r6
	mov r1, r9
	bl CPSi_big_negate
	str r9, [sp, #0x0]
	mov r1, r6
	mov r2, r7
	mov r3, r4
	mov r0, #0x0
	str r11, [sp, #0x4]
	bl CPSi_big_div
	mov r0, r4
	mov r1, r7
	mov r2, r4
	mov r3, r9
	bl CPSi_big_sub
	b _020A2698
_020A267C:
	str r9, [sp, #0x0]
	mov r1, r6
	mov r2, r7
	mov r3, r4
	mov r0, #0x0
	str r11, [sp, #0x4]
	bl CPSi_big_div
_020A2698:
	ldr r0, [sp, #0x8]
	mov r1, r4
	mov r3, r9
	mov r2, #0x30
	bl CPSi_char_from_big
	ldr r1, _020A26CC ; =CPSiFree
	mov r0, r8
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x1c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A26C8: .word CPSiAlloc
_020A26CC: .word CPSiFree

	arm_func_start client_hello
client_hello: ; 0x020A26D0
	stmdb sp!, {r4-r6,lr}
	mov r6, r1
	mov r4, r0
	ldrb r0, [r6, #0x0]
	ldrb r1, [r6, #0x1]
	bl version_ok
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	add r0, r6, #0x2
	add r1, r4, #0x34
	mov r2, #0x20
	bl MI_CpuCopy8
	ldrb r5, [r6, #0x22]
	add r6, r6, #0x23
	cmp r5, #0x20
	movne r0, #0x0
	strneb r0, [r4, #0x30]
	bne _020A2734
	mov r0, r6
	add r1, r4, #0x74
	mov r2, #0x20
	bl MI_CpuCopy8
	mov r0, r4
	bl find_session_from_id
_020A2734:
	add r0, r6, r5
	ldrb r1, [r0, #0x1]
	ldrb r3, [r6, r5]
	add r0, r0, #0x2
	mov r2, #0x2
	add r1, r1, r3, lsl #0x8
	add r1, r1, r1, lsr #0x1f
	mov r1, r1, asr #0x1
	bl select_method
	mov r0, r0, lsl #0x10
	movs r0, r0, lsr #0x10
	strh r0, [r4, #0x32]
	movne r0, #0x1
	strneb r0, [r4, #0x455]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start client_hello_v2
client_hello_v2: ; 0x020A2774
	stmdb sp!, {r4-r6,lr}
	mov r5, r1
	mov r6, r0
	ldrb r0, [r5, #0x0]
	ldrb r1, [r5, #0x1]
	bl version_ok
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrb r2, [r5, #0x2]
	ldrb r1, [r5, #0x3]
	ldr r3, _020A2848 ; =0x55555556
	add r0, r5, #0x8
	add r4, r1, r2, lsl #0x8
	smull r2, r1, r3, r4
	add r1, r1, r4, lsr #0x1f
	mov r2, #0x3
	bl select_method
	mov r0, r0, lsl #0x10
	movs r0, r0, lsr #0x10
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	strh r0, [r6, #0x32]
	ldrb r12, [r5, #0x4]
	ldrb r0, [r5, #0x5]
	ldrb r3, [r5, #0x6]
	ldrb r2, [r5, #0x7]
	mov r1, #0x0
	add r12, r0, r12, lsl #0x8
	add r0, r4, #0x8
	add r4, r2, r3, lsl #0x8
	add r0, r0, r12
	strb r1, [r6, #0x30]
	cmp r4, #0x20
	add r5, r5, r0
	blt _020A2818
	mov r0, r5
	add r1, r6, #0x34
	mov r2, #0x20
	bl MI_CpuCopy8
	b _020A2838
_020A2818:
	add r0, r6, #0x34
	rsb r2, r4, #0x20
	bl MI_CpuFill8
	add r1, r6, #0x54
	mov r0, r5
	mov r2, r4
	sub r1, r1, r4
	bl MI_CpuCopy8
_020A2838:
	mov r0, #0x1
	strb r0, [r6, #0x455]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A2848: .word 0x55555556

	arm_func_start version_ok
version_ok:
	cmp r0, #0x3
	moveq r0, #0x1
	movne r0, #0x0
	bx lr

	arm_func_start select_method
select_method: ; 0x020A285C
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r5, #0x0
	ldr r4, _020A28BC ; =pairlist
_020A2874:
	mov r0, r5, lsl #0x1
	ldrh r3, [r4, r0]
	mov r0, r8
	mov r1, r7
	mov r2, r6
	bl has_method
	cmp r0, #0x0
	ldrne r0, _020A28BC ; =pairlist
	movne r1, r5, lsl #0x1
	ldrneh r0, [r0, r1]
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	add r5, r5, #0x1
	cmp r5, #0x2
	blo _020A2874
	mov r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A28BC: .word pairlist

	arm_func_start has_method
has_method:
	stmdb sp!, {r4,lr}
	cmp r1, #0x0
	mov r4, #0x0
	ble _020A2908
_020A28D0:
	ldrb lr, [r0, #0x0]
	ldrb r12, [r0, #0x1]
	cmp r2, #0x3
	add lr, r12, lr, lsl #0x8
	ldreqb r12, [r0, #0x2]
	addeq lr, r12, lr, lsl #0x8
	cmp lr, r3
	moveq r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	add r4, r4, #0x1
	cmp r4, r1
	add r0, r0, r2
	blt _020A28D0
_020A2908:
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start rcv_server_hello
rcv_server_hello: ; 0x020A2914
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r5, r1
	add r0, r5, #0x2
	add r1, r6, #0x54
	mov r2, #0x20
	bl MI_CpuCopy8
	add r0, r5, #0x22
	ldrb r7, [r6, #0x30]
	add r5, r5, #0x23
	ldrb r4, [r0, #0x0]
	cmp r7, #0x0
	beq _020A2974
	cmp r4, #0x20
	bne _020A2974
	mov r1, r5
	add r0, r6, #0x74
	mov r2, #0x20
	bl memcmp
	cmp r0, #0x0
	moveq r0, #0x1
	streqb r0, [r6, #0x31]
	beq _020A29B4
_020A2974:
	cmp r7, #0x0
	beq _020A2984
	mov r0, r6
	bl purge_session
_020A2984:
	cmp r4, #0x0
	moveq r0, #0x0
	streqb r0, [r6, #0x30]
	beq _020A29AC
	mov r0, r5
	add r1, r6, #0x74
	mov r2, #0x20
	bl MI_CpuCopy8
	mov r0, #0x1
	strb r0, [r6, #0x30]
_020A29AC:
	mov r0, #0x0
	strb r0, [r6, #0x31]
_020A29B4:
	add r0, r5, r4
	ldrb r2, [r5, r4]
	ldrb r1, [r0, #0x1]
	mov r0, #0x2
	add r1, r1, r2, lsl #0x8
	strh r1, [r6, #0x32]
	strb r0, [r6, #0x455]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start rcv_certificate
rcv_certificate: ; 0x020A29DC
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x24
	ldr r1, [sp, #0x4c]
	mov r10, r0
	ldrb r4, [r1, #0x2]
	ldrb r3, [r1, #0x0]
	ldrb r2, [r1, #0x1]
	add r0, r1, #0x3
	mvn r1, #0x0
	str r0, [sp, #0x4c]
	add r2, r2, r3, lsl #0x8
	add r0, sp, #0x14
	str r1, [r10, #0x45c]
	add r7, r4, r2, lsl #0x8
	bl RTC_GetDate
	mov r8, #0x0
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x1c]
	add r1, r0, #0x7d0
	ldr r0, [sp, #0x18]
	mov r1, r1, lsl #0x10
	add r0, r1, r0, lsl #0x8
	add r0, r2, r0
	str r0, [r10, #0x80c]
	strb r8, [r10, #0x6b0]
	str r8, [r10, #0x5a0]
	ldr r0, [r10, #0x5a0]
	mov r6, r8
	str r0, [r10, #0x594]
	add r0, r10, #0x7b0
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r8, [sp, #0x8]
	mov r4, r8
	mov r11, #0x2
	str r0, [sp, #0xc]
	mvn r5, #0x0
_020A2A74:
	ldr r1, [sp, #0x4c]
	mov r0, r10
	ldrb r2, [r1, #0x2]
	ldrb r12, [r1, #0x0]
	ldrb r3, [r1, #0x1]
	add r9, r1, #0x3
	add r1, sp, #0x4c
	str r9, [sp, #0x4c]
	str r5, [r10, #0x458]
	strb r4, [r10, #0x5ad]
	strb r4, [r10, #0x5ac]
	strb r4, [r10, #0x5af]
	strb r4, [r10, #0x6b0]
	strb r4, [r10, #0x5b0]
	strb r4, [r10, #0x7b0]
	add r3, r3, r12, lsl #0x8
	ldr r9, [sp, #0x4c]
	add r3, r2, r3, lsl #0x8
	add r2, r3, #0x3
	str r9, [r10, #0x804]
	str r3, [r10, #0x808]
	sub r7, r7, r2
	mov r2, r4
	mov r3, r4
	str r8, [sp, #0x0]
	bl cert_item
	cmp r0, #0x0
	bne _020A2AFC
	ldr r0, [r10, #0x594]
	cmp r0, #0x33
	blo _020A2AFC
	ldr r0, [r10, #0x5a0]
	cmp r0, #0x0
	bne _020A2B14
_020A2AFC:
	mov r0, #0x9
	add sp, sp, #0x24
	strb r0, [r10, #0x455]
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020A2B14:
	mov r0, r10
	bl auth_cert
	mov r8, r0
	cmp r6, #0x0
	bne _020A2B44
	ldr r0, [r10, #0x800]
	cmp r0, #0x0
	beq _020A2B44
	ldr r1, [sp, #0x4]
	bl compare_fqdn
	cmp r0, #0x0
	orrne r8, r8, #0x4000
_020A2B44:
	and r9, r8, #0xff
	cmp r9, #0x1
	bne _020A2BB4
	cmp r7, #0x0
	beq _020A2BB4
	ldr r1, [sp, #0x4c]
	ldr r2, [sp, #0x8]
	add r1, r1, #0x3
	str r1, [sp, #0x10]
	ldr r1, [sp, #0x8]
	mov r0, r10
	strb r1, [r10, #0x5ad]
	add r1, sp, #0x10
	mov r3, r2
	str r11, [sp, #0x0]
	bl cert_item
	cmp r0, #0x0
	movne r0, #0x9
	addne sp, sp, #0x24
	strneb r0, [r10, #0x455]
	ldmneia sp!, {r4-r11,lr}
	addne sp, sp, #0x10
	bxne lr
	mov r0, r10
	add r1, r10, #0x480
	bl validate_signature
	bic r1, r8, #0xff
	orr r8, r1, r0
_020A2BB4:
	ldr r3, [r10, #0x810]
	cmp r3, #0x0
	beq _020A2BD4
	mov r0, r8
	mov r1, r10
	mov r2, r6
	blx r3
	mov r8, r0
_020A2BD4:
	cmp r9, #0x0
	add r6, r6, #0x1
	beq _020A2BF4
	cmp r8, #0x0
	bne _020A2BF4
	cmp r7, #0x0
	ldrne r8, [sp, #0xc]
	bne _020A2A74
_020A2BF4:
	cmp r8, #0x0
	moveq r0, #0x3
	streqb r0, [r10, #0x455]
	movne r0, #0x9
	strneb r0, [r10, #0x455]
	add sp, sp, #0x24
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr

	arm_func_start compare_fqdn
compare_fqdn:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	b _020A2C38
_020A2C28:
	cmp r1, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
_020A2C38:
	ldrsb r0, [r5], #0x1
	ldrsb r1, [r6], #0x1
	cmp r1, r0
	beq _020A2C28
	cmp r0, #0x2a
	movne r0, #0x1
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	sub r6, r6, #0x1
	mov r0, r6
	bl chars_till_end
	mov r4, r0
	mov r0, r5
	bl chars_till_end
	cmp r0, r4
	movgt r0, #0x1
	ldmgtia sp!, {r4-r6,lr}
	bxgt lr
	sub r0, r4, r0
	add r6, r6, r0
	b _020A2C38
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start chars_till_end
chars_till_end: ; 0x020A2C94
	mov r2, r0
	b _020A2CA0
_020A2C9C:
	add r0, r0, #0x1
_020A2CA0:
	ldrsb r1, [r0, #0x0]
	cmp r1, #0x2e
	beq _020A2CB4
	cmp r1, #0x0
	bne _020A2C9C
_020A2CB4:
	sub r0, r0, r2
	bx lr

	arm_func_start auth_cert
auth_cert: ; 0x020A2CBC
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	ldrb r0, [r5, #0x5af]
	ldr r1, [r5, #0x45c]
	cmp r0, #0x0
	movne r4, #0x0
	moveq r4, #0x8000
	mvn r0, #0x0
	cmp r1, r0
	orreq r0, r4, #0x4
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, [r5, #0x458]
	cmp r0, #0x3
	beq _020A2D04
	cmp r0, #0x4
	beq _020A2D40
	b _020A2D7C
_020A2D04:
	add r6, r5, #0x3fc
	mov r0, r6
	bl CPSi_md5_init
	ldr r1, [r5, #0x460]
	ldr r2, [r5, #0x464]
	mov r0, r6
	sub r2, r2, r1
	bl CPSi_md5_calc
	ldr r1, _020A2DB8 ; =0x00000468
	mov r0, r6
	add r1, r5, r1
	bl CPSi_md5_result
	mov r0, #0x10
	str r0, [r5, #0x47c]
	b _020A2D88
_020A2D40:
	add r6, r5, #0x348
	mov r0, r6
	bl CPSi_sha1_init
	ldr r1, [r5, #0x460]
	ldr r2, [r5, #0x464]
	mov r0, r6
	sub r2, r2, r1
	bl CPSi_sha1_calc
	ldr r1, _020A2DB8 ; =0x00000468
	mov r0, r6
	add r1, r5, r1
	bl CPSi_sha1_result
	mov r0, #0x14
	str r0, [r5, #0x47c]
	b _020A2D88
_020A2D7C:
	orr r0, r4, #0x3
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A2D88:
	mov r0, r5
	add r1, r5, #0x5b0
	bl get_rootCA
	movs r1, r0
	orreq r0, r4, #0x1
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r0, r5
	bl validate_signature
	orr r0, r4, r0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A2DB8: .word 0x00000468

	arm_func_start validate_signature
validate_signature:
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x8
	mov r8, r0
	ldr r0, [r8, #0x5a4]
	mov r7, r1
	cmp r0, #0x0
	beq _020A2E14
	ldr r0, [r8, #0x5a8]
	cmp r0, #0x0
	beq _020A2E14
	ldr r0, [r7, #0x10]
	cmp r0, #0x0
	beq _020A2E14
	ldr r0, [r7, #0xc]
	cmp r0, #0x0
	beq _020A2E14
	ldr r0, [r7, #0x8]
	cmp r0, #0x0
	beq _020A2E14
	ldr r0, [r7, #0x4]
	cmp r0, #0x0
	bne _020A2E24
_020A2E14:
	add sp, sp, #0x8
	mov r0, #0x2
	ldmia sp!, {r4-r10,lr}
	bx lr
_020A2E24:
	mov r0, r0, lsl #0x1
	ldr r1, _020A2F8C ; =CPSiAlloc
	add r0, r0, r0, lsr #0x1f
	mov r4, r0, asr #0x1
	ldr r1, [r1, #0x0]
	mov r0, r4, lsl #0x3
	blx r1
	movs r6, r0
	addeq sp, sp, #0x8
	moveq r0, #0x2
	ldmeqia sp!, {r4-r10,lr}
	bxeq lr
	add r5, r6, r4, lsl #0x1
	add r10, r5, r4, lsl #0x1
	ldr r1, [r8, #0x5a4]
	ldr r2, [r8, #0x5a8]
	mov r0, r5
	mov r3, r4
	add r9, r10, r4, lsl #0x1
	bl CPSi_big_from_char
	ldr r1, [r7, #0x10]
	ldr r2, [r7, #0xc]
	mov r0, r10
	mov r3, r4
	bl CPSi_big_from_char
	mov r0, r9
	ldr r1, [r7, #0x8]
	ldr r2, [r7, #0x4]
	mov r3, r4
	bl CPSi_big_from_char
	bl enter_computebound
	str r9, [sp, #0x0]
	mov r2, r10
	mov r9, r0
	mov r0, r6
	mov r1, r5
	mov r3, r4
	bl CPSi_big_power
	mov r0, r9
	bl exit_computebound
	mov r0, r5
	mov r1, r6
	ldr r2, [r7, #0x4]
	mov r3, r4
	bl CPSi_char_from_big
	ldrb r0, [r6, r4, lsl #0x1]
	mov r4, #0x0
	cmp r0, #0x0
	bne _020A2EF4
	ldrb r0, [r5, #0x1]
	cmp r0, #0x1
	beq _020A2EFC
_020A2EF4:
	mov r4, #0x2
	b _020A2F6C
_020A2EFC:
	ldr r3, [r7, #0x4]
	mov r2, #0x2
	cmp r3, #0x2
	ble _020A2F24
_020A2F0C:
	ldrb r0, [r5, r2]
	cmp r0, #0xff
	bne _020A2F24
	add r2, r2, #0x1
	cmp r2, r3
	blt _020A2F0C
_020A2F24:
	add r1, r2, #0x1
	cmp r1, r3
	bge _020A2F68
	ldrb r0, [r5, r2]
	cmp r0, #0x0
	bne _020A2F68
	ldrb r0, [r5, r1]
	cmp r0, #0x30
	bne _020A2F68
	ldr r0, _020A2F90 ; =0x00000468
	ldr r2, [r8, #0x47c]
	add r1, r5, r3
	add r0, r8, r0
	sub r1, r1, r2
	bl memcmp
	cmp r0, #0x0
	beq _020A2F6C
_020A2F68:
	mov r4, #0x2
_020A2F6C:
	ldr r1, _020A2F94 ; =CPSiFree
	mov r0, r6
	ldr r1, [r1, #0x0]
	blx r1
	mov r0, r4
	add sp, sp, #0x8
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_020A2F8C: .word CPSiAlloc
_020A2F90: .word 0x00000468
_020A2F94: .word CPSiFree

	arm_func_start cert_item
cert_item:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	str r1, [sp, #0x4]
	ldr r1, [r1, #0x0]
	mov r9, r0
	str r1, [sp, #0x8]
	add r0, r1, #0x1
	str r0, [sp, #0x8]
	add r0, sp, #0x8
	mov r5, r2
	mov r4, r3
	ldr r8, [sp, #0x30]
	ldrb r6, [r1, #0x0]
	bl cert_item_len
	movs r7, r0
	bmi _020A2FE0
	cmp r7, #0x7d0
	ble _020A2FF0
_020A2FE0:
	add sp, sp, #0xc
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020A2FF0:
	and r1, r6, #0x1f
	cmp r1, #0x18
	addls pc, pc, r1, lsl #0x2
	b _020A3430
_020A3000: ; jump table
	b _020A3430 ; case 0
	b _020A3430 ; case 1
	b _020A3064 ; case 2
	b _020A315C ; case 3
	b _020A3430 ; case 4
	b _020A3430 ; case 5
	b _020A31DC ; case 6
	b _020A3430 ; case 7
	b _020A3430 ; case 8
	b _020A3430 ; case 9
	b _020A3430 ; case 10
	b _020A3430 ; case 11
	b _020A3274 ; case 12
	b _020A3430 ; case 13
	b _020A3430 ; case 14
	b _020A3430 ; case 15
	b _020A3348 ; case 16
	b _020A33D8 ; case 17
	b _020A3430 ; case 18
	b _020A3274 ; case 19
	b _020A3274 ; case 20
	b _020A3430 ; case 21
	b _020A3274 ; case 22
	b _020A32F4 ; case 23
	b _020A32F4 ; case 24
_020A3064:
	ldrb r0, [r9, #0x5ad]
	cmp r0, #0x0
	beq _020A314C
	cmp r4, #0x0
	bne _020A30E0
	ldr r0, [sp, #0x8]
	ldrb r1, [r0, #0x0]
	cmp r1, #0x0
	bne _020A30A4
_020A3088:
	ldr r1, [sp, #0x8]
	sub r7, r7, #0x1
	add r0, r1, #0x1
	str r0, [sp, #0x8]
	ldrb r1, [r1, #0x1]
	cmp r1, #0x0
	beq _020A3088
_020A30A4:
	cmp r8, #0x0
	beq _020A30C0
	cmp r8, #0x2
	streq r7, [r9, #0x484]
	ldreq r0, [sp, #0x8]
	streq r0, [r9, #0x488]
	b _020A314C
_020A30C0:
	cmp r7, #0x100
	bgt _020A314C
	ldr r1, _020A34B8 ; =0x00000494
	mov r2, r7
	add r1, r9, r1
	bl MI_CpuCopy8
	str r7, [r9, #0x594]
	b _020A314C
_020A30E0:
	cmp r4, #0x1
	bne _020A314C
	ldr r0, [sp, #0x8]
	ldrb r1, [r0, #0x0]
	cmp r1, #0x0
	bne _020A3114
_020A30F8:
	ldr r1, [sp, #0x8]
	sub r7, r7, #0x1
	add r0, r1, #0x1
	str r0, [sp, #0x8]
	ldrb r1, [r1, #0x1]
	cmp r1, #0x0
	beq _020A30F8
_020A3114:
	cmp r8, #0x0
	beq _020A3130
	cmp r8, #0x2
	streq r7, [r9, #0x48c]
	ldreq r0, [sp, #0x8]
	streq r0, [r9, #0x490]
	b _020A314C
_020A3130:
	cmp r7, #0x8
	bgt _020A314C
	ldr r1, _020A34BC ; =0x00000598
	mov r2, r7
	add r1, r9, r1
	bl MI_CpuCopy8
	str r7, [r9, #0x5a0]
_020A314C:
	ldr r0, [sp, #0x8]
	add r0, r0, r7
	str r0, [sp, #0x8]
	b _020A349C
_020A315C:
	cmp r5, #0x1
	bne _020A317C
	cmp r8, #0x2
	ldrne r1, [sp, #0x8]
	subne r0, r7, #0x1
	addne r1, r1, #0x1
	strne r1, [r9, #0x5a4]
	strne r0, [r9, #0x5a8]
_020A317C:
	ldrb r0, [r9, #0x5ad]
	cmp r0, #0x0
	beq _020A31CC
	ldr r0, [sp, #0x8]
	add r1, sp, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x8]
	mov r0, r9
	mov r2, r5
	mov r3, #0x0
	str r8, [sp, #0x0]
	bl cert_item
	cmp r0, #0x0
	addne sp, sp, #0xc
	movne r0, #0x1
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	mov r0, #0x0
	strb r0, [r9, #0x5ad]
	b _020A349C
_020A31CC:
	ldr r0, [sp, #0x8]
	add r0, r0, r7
	str r0, [sp, #0x8]
	b _020A349C
_020A31DC:
	ldr r5, [sp, #0x8]
	mov r6, #0x0
	ldr sl, _020A34C0 ; =object
_020A31E8:
	ldr r4, [r10, r6, lsl #0x2]
	mov r0, r4
	bl strlen
	mov r2, r0
	mov r0, r5
	mov r1, r4
	bl memcmp
	cmp r0, #0x0
	bne _020A3258
	cmp r6, #0x5
	addls pc, pc, r6, lsl #0x2
	b _020A3264
_020A3218: ; jump table
	b _020A3264 ; case 0
	b _020A3230 ; case 1
	b _020A3230 ; case 2
	b _020A3240 ; case 3
	b _020A3240 ; case 4
	b _020A324C ; case 5
_020A3230:
	cmp r8, #0x0
	streq r6, [r9, #0x45c]
	strb r6, [r9, #0x5ad]
	b _020A3264
_020A3240:
	cmp r8, #0x2
	strne r6, [r9, #0x458]
	b _020A3264
_020A324C:
	cmp r8, #0x2
	strneb r6, [r9, #0x5ae]
	b _020A3264
_020A3258:
	add r6, r6, #0x1
	cmp r6, #0x6
	blt _020A31E8
_020A3264:
	ldr r0, [sp, #0x8]
	add r0, r0, r7
	str r0, [sp, #0x8]
	b _020A349C
_020A3274:
	cmp r8, #0x2
	beq _020A32DC
	ldrb r0, [r9, #0x5ac]
	cmp r0, #0x0
	beq _020A32CC
	ldr r1, [sp, #0x8]
	mov r2, r7
	add r0, r9, #0x6b0
	bl make_dn
	ldrb r0, [r9, #0x5ae]
	cmp r0, #0x5
	bne _020A32DC
	cmp r7, #0x4f
	bgt _020A32DC
	ldr r0, [sp, #0x8]
	mov r2, r7
	add r1, r9, #0x7b0
	bl MI_CpuCopy8
	add r0, r9, r7
	mov r1, #0x0
	strb r1, [r0, #0x7b0]
	b _020A32DC
_020A32CC:
	ldr r1, [sp, #0x8]
	mov r2, r7
	add r0, r9, #0x5b0
	bl make_dn
_020A32DC:
	mov r0, #0x0
	strb r0, [r9, #0x5ae]
	ldr r0, [sp, #0x8]
	add r0, r0, r7
	str r0, [sp, #0x8]
	b _020A349C
_020A32F4:
	cmp r8, #0x2
	beq _020A3330
	ldr r0, [sp, #0x8]
	bl parse_time
	cmp r4, #0x0
	bne _020A3320
	ldr r1, [r9, #0x80c]
	cmp r1, r0
	movcs r0, #0x1
	strcsb r0, [r9, #0x5af]
	b _020A3330
_020A3320:
	ldr r1, [r9, #0x80c]
	cmp r1, r0
	movhi r0, #0x0
	strhib r0, [r9, #0x5af]
_020A3330:
	ldr r1, [sp, #0x8]
	mov r0, #0x1
	add r1, r1, r7
	str r1, [sp, #0x8]
	strb r0, [r9, #0x5ac]
	b _020A349C
_020A3348:
	cmp r5, #0x0
	bne _020A3364
	cmp r4, #0x0
	bne _020A3364
	cmp r8, #0x2
	ldrne r0, [sp, #0x8]
	strne r0, [r9, #0x460]
_020A3364:
	ldr r0, [sp, #0x8]
	mov r10, #0x0
	add r7, r0, r7
	cmp r0, r7
	bhs _020A33BC
	add r11, sp, #0x8
	add r6, r5, #0x1
_020A3380:
	mov r0, r9
	mov r1, r11
	mov r2, r6
	mov r3, r10
	str r8, [sp, #0x0]
	bl cert_item
	cmp r0, #0x0
	add r10, r10, #0x1
	addne sp, sp, #0xc
	movne r0, #0x1
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	ldr r0, [sp, #0x8]
	cmp r0, r7
	blo _020A3380
_020A33BC:
	cmp r5, #0x1
	bne _020A349C
	cmp r4, #0x0
	bne _020A349C
	cmp r8, #0x2
	strne r0, [r9, #0x464]
	b _020A349C
_020A33D8:
	ldr r0, [sp, #0x8]
	add r6, r0, r7
	cmp r0, r6
	bhs _020A349C
	add r7, r5, #0x1
	add r4, sp, #0x8
	mov r5, #0x0
_020A33F4:
	mov r0, r9
	mov r1, r4
	mov r2, r7
	mov r3, r5
	str r8, [sp, #0x0]
	bl cert_item
	cmp r0, #0x0
	addne sp, sp, #0xc
	movne r0, #0x1
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	ldr r0, [sp, #0x8]
	cmp r0, r6
	blo _020A33F4
	b _020A349C
_020A3430:
	cmp r6, #0xa0
	bne _020A3490
	ldr r0, [sp, #0x8]
	add r6, r0, r7
	cmp r0, r6
	bhs _020A349C
	add r7, r5, #0x1
	add r4, sp, #0x8
	mov r5, #0x0
_020A3454:
	mov r0, r9
	mov r1, r4
	mov r2, r7
	mov r3, r5
	str r8, [sp, #0x0]
	bl cert_item
	cmp r0, #0x0
	addne sp, sp, #0xc
	movne r0, #0x1
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	ldr r0, [sp, #0x8]
	cmp r0, r6
	blo _020A3454
	b _020A349C
_020A3490:
	ldr r0, [sp, #0x8]
	add r0, r0, r7
	str r0, [sp, #0x8]
_020A349C:
	ldr r2, [sp, #0x8]
	ldr r1, [sp, #0x4]
	mov r0, #0x0
	str r2, [r1, #0x0]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020A34B8: .word 0x00000494
_020A34BC: .word 0x00000598
_020A34C0: .word object

	arm_func_start parse_time
parse_time:
	stmdb sp!, {r4,lr}
	ldrb r12, [r0, #0x1]
	ldrb r3, [r0, #0x0]
	mov r2, #0xa
	cmp r1, #0x17
	mla r1, r3, r2, r12
	sub lr, r1, #0x210
	add r0, r0, #0x2
	bne _020A34FC
	cmp lr, #0x32
	ldrhs r1, _020A3550 ; =0x0000076C
	addcc r4, lr, #0x7d0
	addcs r4, lr, r1
	b _020A3518
_020A34FC:
	ldrb r12, [r0, #0x1]
	ldrb r3, [r0, #0x0]
	mov r1, #0x64
	add r0, r0, #0x2
	mla r2, r3, r2, r12
	sub r2, r2, #0x210
	mla r4, lr, r1, r2
_020A3518:
	ldrb r12, [r0, #0x1]
	ldrb r3, [r0, #0x0]
	mov r1, #0xa
	ldrb r2, [r0, #0x3]
	ldrb r0, [r0, #0x2]
	mla r12, r3, r1, r12
	mla r1, r0, r1, r2
	mov r2, r4, lsl #0x10
	sub r0, r12, #0x210
	add r2, r2, r0, lsl #0x8
	sub r0, r1, #0x210
	add r0, r2, r0
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A3550: .word 0x0000076C

	arm_func_start make_dn
make_dn:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrsb r3, [r0, #0x0]
	mov lr, r0
	cmp r3, #0x0
	beq _020A35AC
_020A356C:
	ldrsb r3, [r0, #0x1]!
	cmp r3, #0x0
	bne _020A356C
	sub r3, r0, lr
	cmp r3, #0xff
	addge sp, sp, #0x4
	ldmgeia sp!, {lr}
	bxge lr
	mov r3, #0x2c
	strb r3, [r0, #0x0]
	mov r3, #0x20
	strb r3, [r0, #0x1]
	add r0, r0, #0x2
	b _020A35AC
_020A35A4:
	ldrsb r3, [r1], #0x1
	strb r3, [r0], #0x1
_020A35AC:
	cmp r2, #0x0
	sub r2, r2, #0x1
	beq _020A35C4
	sub r3, r0, lr
	cmp r3, #0xff
	blt _020A35A4
_020A35C4:
	mov r1, #0x0
	strb r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start cert_item_len
cert_item_len: ; 0x020A35D8
	ldr r1, [r0, #0x0]
	ldrb r3, [r1, #0x0]
	add r12, r1, #0x1
	ands r1, r3, #0x80
	beq _020A361C
	ands r1, r3, #0x7f
	sub r2, r1, #0x1
	mov r3, #0x0
	beq _020A361C
_020A35FC:
	ands r1, r3, #0xff000000
	mvnne r0, #0x0
	bxne lr
	ldrb r1, [r12], #0x1
	cmp r2, #0x0
	sub r2, r2, #0x1
	add r3, r1, r3, lsl #0x8
	bne _020A35FC
_020A361C:
	str r12, [r0, #0x0]
	mov r0, r3
	bx lr

	arm_func_start get_rootCA
get_rootCA: ; 0x020A3628
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r4, [r0, #0x818]
	mov r7, r1
	cmp r4, #0x0
	mov r6, #0x0
	ble _020A3678
	ldr r5, [r0, #0x814]
_020A3648:
	ldr r0, [r5, r6, lsl #0x2]
	mov r1, r7
	ldr r0, [r0, #0x0]
	bl strcmp
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldreq r0, [r5, r6, lsl #0x2]
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	add r6, r6, #0x1
	cmp r6, r4
	blt _020A3648
_020A3678:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start CPS_SetRootCa
CPS_SetRootCa: ; 0x020A3688
	ldr r2, _020A36B0 ; =OSi_ThreadInfo
	ldr r2, [r2, #0x4]
	ldr r2, [r2, #0xa4]
	cmp r2, #0x0
	bxeq lr
	ldr r2, [r2, #0xc]
	cmp r2, #0x0
	strne r0, [r2, #0x814]
	strne r1, [r2, #0x818]
	bx lr
	.balign 4
_020A36B0: .word OSi_ThreadInfo

	arm_func_start exit_computebound
exit_computebound: ; 0x020A36B4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r1, r0
	cmp r1, #0x20
	addcs sp, sp, #0x4
	ldmcsia sp!, {lr}
	bxcs lr
	ldr r0, _020A36E8 ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	bl OS_SetThreadPriority
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A36E8: .word OSi_ThreadInfo

	arm_func_start enter_computebound
enter_computebound: ; 0x020A36EC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020A3744 ; =ssl_handshake_priority
	ldr r0, [r0, #0x0]
	cmp r0, #0x20
	addcs sp, sp, #0x4
	mvncs r0, #0x0
	ldmcsia sp!, {r4-r5,lr}
	bxcs lr
	ldr r0, _020A3748 ; =OSi_ThreadInfo
	ldr r5, [r0, #0x4]
	mov r0, r5
	bl OS_GetThreadPriority
	ldr r1, _020A3744 ; =ssl_handshake_priority
	mov r4, r0
	ldr r1, [r1, #0x0]
	mov r0, r5
	bl OS_SetThreadPriority
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A3744: .word ssl_handshake_priority
_020A3748: .word OSi_ThreadInfo

	arm_func_start CPS_SetSslHandshakePriority
CPS_SetSslHandshakePriority: ; 0x020A374C
	ldr r1, _020A3758 ; =ssl_handshake_priority
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020A3758: .word ssl_handshake_priority

	arm_func_start date2sec
date2sec: ; 0x020A375C
	stmdb sp!, {lr}
	sub sp, sp, #0x1c
	add r0, sp, #0x0
	bl RTC_GetDate
	add r0, sp, #0x10
	bl RTC_GetTime
	add r0, sp, #0x0
	add r1, sp, #0x10
	bl RTC_ConvertDateTimeToSecond
	ldr r1, _020A3794 ; =0x386D4380
	add r0, r0, r1
	add sp, sp, #0x1c
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A3794: .word 0x386D4380

	arm_func_start purge_session
purge_session:
	stmdb sp!, {r4-r8,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r6, _020A3804 ; =session
	mov r7, r0
	mov r8, #0x0
	add r5, r4, #0x74
	mov r4, #0x20
_020A37B8:
	ldrb r0, [r6, #0x5a]
	cmp r0, #0x0
	beq _020A37E4
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl memcmp
	cmp r0, #0x0
	moveq r0, #0x0
	streqb r0, [r6, #0x5a]
	beq _020A37F4
_020A37E4:
	add r8, r8, #0x1
	cmp r8, #0x4
	add r6, r6, #0x5c
	blt _020A37B8
_020A37F4:
	mov r0, r7
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A3804: .word session

	arm_func_start cache_session
cache_session: ; 0x020A3808
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	mov r8, r1
	mov r7, r2
	bl OS_DisableInterrupts
	mov r5, r0
	bl OS_GetTick
	ldr r6, _020A3904 ; =session
	mov r4, r0, lsr #0x10
	mov r3, #0x0
	mov r12, r3
	mov r2, r6
	orr r4, r4, r1, lsl #0x10
	mvn r0, #0x0
_020A3844:
	ldrb r1, [r2, #0x5a]
	cmp r1, #0x0
	beq _020A387C
	cmp r8, #0x0
	beq _020A387C
	ldr lr, [r2, #0x54]
	cmp r8, lr
	bne _020A387C
	cmp r7, #0x0
	beq _020A387C
	ldrh lr, [r2, #0x58]
	cmp r7, lr
	moveq r6, r2
	beq _020A38BC
_020A387C:
	mvn lr, #0x0
	cmp r3, lr
	beq _020A38AC
	cmp r1, #0x0
	moveq r3, r0
	moveq r6, r2
	beq _020A38AC
	ldr r1, [r2, #0x50]
	sub r1, r4, r1
	cmp r1, r3
	movhi r3, r1
	movhi r6, r2
_020A38AC:
	add r12, r12, #0x1
	cmp r12, #0x4
	add r2, r2, #0x5c
	blt _020A3844
_020A38BC:
	mov r1, r6
	add r0, r9, #0x74
	mov r2, #0x20
	bl MI_CpuCopy8
	mov r0, r9
	add r1, r6, #0x20
	mov r2, #0x30
	bl MI_CpuCopy8
	str r4, [r6, #0x50]
	mov r0, #0x1
	strb r0, [r6, #0x5a]
	str r8, [r6, #0x54]
	mov r0, r5
	strh r7, [r6, #0x58]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020A3904: .word session

	arm_func_start find_session_from_IP
find_session_from_IP: ; 0x020A3908
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	mov r6, r2
	bl OS_DisableInterrupts
	mov r1, #0x0
	ldr r4, _020A39AC ; =session
	mov r5, r0
	strb r1, [r8, #0x30]
_020A392C:
	ldrb r0, [r4, #0x5a]
	cmp r0, #0x0
	beq _020A398C
	ldr r0, [r4, #0x54]
	cmp r0, r7
	bne _020A398C
	ldrh r0, [r4, #0x58]
	cmp r0, r6
	bne _020A398C
	mov r0, r4
	add r1, r8, #0x74
	mov r2, #0x20
	bl MI_CpuCopy8
	mov r1, r8
	add r0, r4, #0x20
	mov r2, #0x30
	bl MI_CpuCopy8
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	str r0, [r4, #0x50]
	mov r0, #0x1
	strb r0, [r8, #0x30]
	b _020A399C
_020A398C:
	add r1, r1, #0x1
	cmp r1, #0x4
	add r4, r4, #0x5c
	blt _020A392C
_020A399C:
	mov r0, r5
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A39AC: .word session

	arm_func_start find_session_from_id
find_session_from_id: ; 0x020A39B0
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r7, r0
	bl OS_DisableInterrupts
	mov r6, #0x0
	ldr r4, _020A3A54 ; =session
	mov r5, r0
	strb r6, [r7, #0x30]
	add r9, r7, #0x74
	mov r8, #0x20
_020A39D8:
	ldrb r0, [r4, #0x5a]
	cmp r0, #0x0
	beq _020A3A30
	ldr r0, [r4, #0x54]
	cmp r0, #0x0
	bne _020A3A30
	ldrh r0, [r4, #0x58]
	cmp r0, #0x0
	bne _020A3A30
	mov r0, r4
	mov r1, r9
	mov r2, r8
	bl memcmp
	cmp r0, #0x0
	bne _020A3A30
	mov r1, r7
	add r0, r4, #0x20
	mov r2, #0x30
	bl MI_CpuCopy8
	mov r0, #0x1
	strb r0, [r7, #0x30]
	b _020A3A40
_020A3A30:
	add r6, r6, #0x1
	cmp r6, #0x4
	add r4, r4, #0x5c
	blt _020A39D8
_020A3A40:
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020A3A54: .word session
