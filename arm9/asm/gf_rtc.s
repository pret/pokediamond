    .include "asm/macros.inc"
    .include "global.inc"

	.rodata

	.global sMaxTime
sMaxTime: ; 0x020ED498
	; 23:59:59
	.word 23, 59, 59

	.global sMaxDate
sMaxDate: ; 0x020ED4A4
	; 31 December, 2099
	.word 99, 12, 31, 0

	.global sGF_DaysPerMonth
sGF_DaysPerMonth: ; 0x020ED4B2
	.short   0
	.short  31
	.short  59
	.short  90
	.short 120
	.short 151
	.short 181
	.short 212
	.short 243
	.short 273
	.short 304
	.short 334

	.global sTimeOfDayByHour
sTimeOfDayByHour: ; 0x020ED4CC
	; 00:00 - 03:59
	.byte 0x04, 0x04, 0x04, 0x04
	; 04:00 - 09:59
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	; 10:00 - 16:59
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	; 17:00 - 19:59
	.byte 0x02, 0x02, 0x02
	; 20:00 - 23:59
	.byte 0x03, 0x03, 0x03, 0x03

	.section .bss

	.global sGFRTCWork
sGFRTCWork: ; 0x021C4808
	.space 0x48

	.text

	thumb_func_start GF_InitRTCWork
GF_InitRTCWork: ; 0x0201259C
	push {r3, lr}
	bl RTC_Init
	ldr r3, _020125CC ; =sGFRTCWork
	mov r0, #0x0
	add r2, r3, #0x0
	add r1, r0, #0x0
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r1, _020125D0 ; =sGFRTCWork
	str r0, [r1, #0x0]
	str r0, [r1, #0x4]
	str r0, [r1, #0x8]
	add r0, r3, #0x0
	bl GF_RTC_GetDateTime
	pop {r3, pc}
	.balign 4
_020125CC: .word sGFRTCWork
_020125D0: .word sGFRTCWork

	thumb_func_start GF_RTC_UpdateOnFrame
GF_RTC_UpdateOnFrame: ; 0x020125D4
	push {r3, lr}
	ldr r0, _020125F4 ; =sGFRTCWork
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	bne _020125F2
	ldr r1, [r0, #0x8]
	add r1, r1, #0x1
	str r1, [r0, #0x8]
	cmp r1, #0xa
	ble _020125F2
	mov r1, #0x0
	str r1, [r0, #0x8]
	ldr r0, _020125F8 ; =sGFRTCWork
	bl GF_RTC_GetDateTime
_020125F2:
	pop {r3, pc}
	.balign 4
_020125F4: .word sGFRTCWork
_020125F8: .word sGFRTCWork

	thumb_func_start GF_RTC_GetDateTime_Callback
GF_RTC_GetDateTime_Callback: ; 0x020125FC
	push {r4, lr}
	add r4, r1, #0x0
	str r0, [r4, #0xc]
	cmp r0, #0x0
	beq _0201260A
	bl ErrorHandling
_0201260A:
	add r3, r4, #0x0
	mov r0, #0x1
	add r2, r4, #0x0
	add r3, #0x2c
	str r0, [r4, #0x0]
	ldmia r3!, {r0-r1}
	add r2, #0x10
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	add r3, r4, #0x0
	add r3, #0x3c
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x20
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x4]
	pop {r4, pc}

	thumb_func_start GF_RTC_GetDateTime
GF_RTC_GetDateTime: ; 0x02012634
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x1
	str r0, [r4, #0x4]
	add r0, r4, #0x0
	add r1, r4, #0x0
	ldr r2, _02012658 ; =GF_RTC_GetDateTime_Callback
	add r0, #0x2c
	add r1, #0x3c
	add r3, r4, #0x0
	bl RTC_GetDateTimeAsync
	str r0, [r4, #0xc]
	cmp r0, #0x0
	beq _02012656
	bl ErrorHandling
_02012656:
	pop {r4, pc}
	.balign 4
_02012658: .word GF_RTC_GetDateTime_Callback

	thumb_func_start GF_RTC_CopyDateTime
GF_RTC_CopyDateTime: ; 0x0201265C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02012684 ; =sGFRTCWork
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _0201266E
	bl ErrorHandling
_0201266E:
	ldr r2, _02012688 ; =sGFRTCWork + 16
	ldmia r2!, {r0-r1}
	stmia r5!, {r0-r1}
	ldmia r2!, {r0-r1}
	ldr r2, _0201268C ; =sGFRTCWork + 32
	stmia r5!, {r0-r1}
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4
_02012684: .word sGFRTCWork
_02012688: .word sGFRTCWork + 16
_0201268C: .word sGFRTCWork + 32

	thumb_func_start GF_RTC_CopyTime
GF_RTC_CopyTime: ; 0x02012690
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020126AC ; =sGFRTCWork
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _020126A0
	bl ErrorHandling
_020126A0:
	ldr r2, _020126B0 ; =sGFRTCWork + 32
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4
_020126AC: .word sGFRTCWork
_020126B0: .word sGFRTCWork + 32

	thumb_func_start GF_RTC_CopyDate
GF_RTC_CopyDate: ; 0x020126B4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020126D0 ; =sGFRTCWork
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _020126C4
	bl ErrorHandling
_020126C4:
	ldr r2, _020126D4 ; =sGFRTCWork + 16
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	pop {r4, pc}
	.balign 4
_020126D0: .word sGFRTCWork
_020126D4: .word sGFRTCWork + 16

	thumb_func_start GF_RTC_TimeToSec
GF_RTC_TimeToSec: ; 0x020126D8
	push {r3-r4}
	ldr r4, _020126F8 ; =sGFRTCWork + 32
	mov r0, #0x3c
	ldr r1, [r4, #0x4]
	ldr r3, [r4, #0x8]
	add r2, r1, #0x0
	mul r2, r0
	mov r0, #0xe1
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x4
	mul r0, r1
	add r0, r2, r0
	add r0, r3, r0
	pop {r3-r4}
	bx lr
	nop
_020126F8: .word sGFRTCWork + 32

	thumb_func_start GF_RTC_DateTimeToSec
GF_RTC_DateTimeToSec: ; 0x020126FC
	ldr r3, _02012704 ; =RTC_ConvertDateTimeToSecond
	ldr r0, _02012708 ; =sGFRTCWork + 16
	ldr r1, _0201270C ; =sGFRTCWork + 32
	bx r3
	.balign 4
_02012704: .word RTC_ConvertDateTimeToSecond
_02012708: .word sGFRTCWork + 16
_0201270C: .word sGFRTCWork + 32

	thumb_func_start FUN_02012710
FUN_02012710: ; 0x02012710
	push {r4-r6, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r2, [r5, #0x4]
	ldr r0, _02012778 ; =sGF_DaysPerMonth - 2
	lsl r1, r2, #0x1
	ldrh r0, [r0, r1]
	ldr r3, [r5, #0x8]
	add r4, r3, r0
	cmp r2, #0x3
	blo _02012752
	ldr r6, [r5, #0x0]
	mov r0, #0x1e
	lsr r2, r6, #0x1f
	lsl r1, r6, #0x1e
	sub r1, r1, r2
	ror r1, r0
	add r0, r2, r1
	bne _02012742
	add r0, r6, #0x0
	mov r1, #0x64
	bl _s32_div_f
	cmp r1, #0x0
	bne _02012750
_02012742:
	mov r1, #0x19
	add r0, r6, #0x0
	lsl r1, r1, #0x4
	bl _s32_div_f
	cmp r1, #0x0
	bne _02012752
_02012750:
	add r4, r4, #0x1
_02012752:
	add r6, r5, #0x0
	add r3, sp, #0x0
	add r2, r3, #0x0
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	add r0, r2, #0x0
	bl RTC_ConvertDateToDay
	add r0, r5, #0x0
	bl RTC_ConvertDateToDay
	add r0, r4, #0x0
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_02012778: .word sGF_DaysPerMonth - 2

	thumb_func_start IsNighttime
IsNighttime: ; 0x0201277C
	push {r3, lr}
	bl GF_RTC_GetTimeOfDay
	cmp r0, #0x3
	beq _0201278A
	cmp r0, #0x4
	bne _0201278E
_0201278A:
	mov r0, #0x1
	pop {r3, pc}
_0201278E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start GF_RTC_GetTimeOfDay
GF_RTC_GetTimeOfDay: ; 0x02012794
	push {lr}
	sub sp, #0xc
	add r0, sp, #0x0
	bl GF_RTC_CopyTime
	ldr r0, [sp, #0x0]
	bl GF_RTC_GetTimeOfDayByHour
	add sp, #0xc
	pop {pc}

	thumb_func_start GF_RTC_GetTimeOfDayByHour
GF_RTC_GetTimeOfDayByHour: ; 0x020127A8
	push {r4, lr}
	add r4, r0, #0x0
	bmi _020127B2
	cmp r4, #0x18
	blt _020127B6
_020127B2:
	bl ErrorHandling
_020127B6:
	ldr r0, _020127BC ; =sTimeOfDayByHour
	ldrb r0, [r0, r4]
	pop {r4, pc}
	.balign 4
_020127BC: .word sTimeOfDayByHour

	thumb_func_start FUN_020127C0
FUN_020127C0: ; 0x020127C0
	push {r4-r7, lr}
	sub sp, #0x24
	add r6, r3, #0x0
	ldr r3, _0201282C ; =sMaxDate
	add r4, r0, #0x0
	add r7, r1, #0x0
	add r5, r2, #0x0
	add r2, sp, #0x14
	ldmia r3!, {r0-r1}
	str r2, [sp, #0x0]
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r3, _02012830 ; =sMaxTime
	add r2, sp, #0x8
	ldmia r3!, {r0-r1}
	str r2, [sp, #0x4]
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	ldr r1, [sp, #0x4]
	str r0, [r2, #0x0]
	ldr r0, [sp, #0x0]
	bl RTC_ConvertDateTimeToSecond
	add r2, r1, #0x0
	add r3, r0, #0x0
	mov r1, #0x0
	ldr r0, _02012834 ; =0xBC19137F
	eor r1, r2
	eor r0, r3
	orr r0, r1
	beq _02012804
	bl ErrorHandling
_02012804:
	sub r0, r4, r5
	mov r12, r7
	mov r0, r12
	sbc r0, r6
	bge _02012818
	sub r0, r5, r4
	sbc r6, r7
	add sp, #0x24
	add r1, r6, #0x0
	pop {r4-r7, pc}
_02012818:
	ldr r0, _02012834 ; =0xBC19137F
	mov r1, #0x0
	sub r0, r0, r4
	sbc r1, r7
	add r0, r5, r0
	adc r6, r1
	add r1, r6, #0x0
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_0201282C: .word sMaxDate
_02012830: .word sMaxTime
_02012834: .word 0xBC19137F
