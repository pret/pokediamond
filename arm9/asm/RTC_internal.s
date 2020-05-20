    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start RtcSendPxiCommand
RtcSendPxiCommand: ; 0x020D61D4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, r0, lsl #0x8
	and r1, r0, #0x7f00
	mov r0, #0x5
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020D61F0: ; 0x020D61F0
	cmp r0, #0x0
	movge r0, #0x1
	movlt r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start RTCi_WriteRawStatus2Async
RTCi_WriteRawStatus2Async:
	ldr ip, _020D6214 ; =RtcSendPxiCommand
	mov r0, #0x27
	bx r12
	.balign 4
_020D6214: .word RtcSendPxiCommand

	arm_func_start RTCi_ReadRawTimeAsync
RTCi_ReadRawTimeAsync:
	ldr ip, _020D6224 ; =RtcSendPxiCommand
	mov r0, #0x12
	bx r12
	.balign 4
_020D6224: .word RtcSendPxiCommand

	arm_func_start RTCi_ReadRawDateAsync
RTCi_ReadRawDateAsync:
	ldr ip, _020D6234 ; =RtcSendPxiCommand
	mov r0, #0x11
	bx r12
	.balign 4
_020D6234: .word RtcSendPxiCommand

	arm_func_start RTCi_ReadRawDateTimeAsync
RTCi_ReadRawDateTimeAsync:
	ldr ip, _020D6244 ; =RtcSendPxiCommand
	mov r0, #0x10
	bx r12
	.balign 4
_020D6244: .word RtcSendPxiCommand
