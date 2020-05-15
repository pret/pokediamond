	.section .bss

	.global OSi_UserExceptionHandler
OSi_UserExceptionHandler: ; 0x021D371C
	.space 0x4

	.global OSi_UserExceptionHandlerArg
OSi_UserExceptionHandlerArg: ; 0x021D3720
	.space 0x4

	.global OSi_DebuggerHandler
OSi_DebuggerHandler: ; 0x021D3724
	.space 0x4

	.global OSi_ExContext
OSi_ExContext: ; 0x021D3728
	.space 0x80

	.global OSi_TimerReserved
OSi_TimerReserved: ; 0x021D37A8
	.space 0x4

	.global OSi_UseTick
OSi_UseTick: ; 0x021D37AC
	.space 0x4

	.global OSi_NeedResetTimer
OSi_NeedResetTimer: ; 0x021D37B0
	.space 0x4

	.global OSi_TickCounter
OSi_TickCounter: ; 0x021D37B4
	.space 0x8

	.global OSi_UseAlarm
OSi_UseAlarm: ; 0x021D37BC
	.space 0x4

	.global OSi_AlarmQueue
OSi_AlarmQueue: ; 0x021D37C0
	.space 0x8

	.global OSi_UseVAlarm
OSi_UseVAlarm: ; 0x021D37C8
	.space 0x4

	.global OSi_PreviousVCount
OSi_PreviousVCount: ; 0x021D37CC
	.space 0x4

	.global OSi_VFrameCount
OSi_VFrameCount: ; 0x021D37D0
	.space 0x4

	.global OSi_VAlarmQueue
OSi_VAlarmQueue: ; 0x021D37D4
	.space 0x8

	.global OSi_IsInitReset
OSi_IsInitReset: ; 0x021D37DC
	.space 0x4

	.global OSi_IsResetOccurred
OSi_IsResetOccurred: ; 0x021D37E0
	.space 0x4

	.global OSi_vramExclusive
OSi_vramExclusive: ; 0x021D37E4
	.space 0x4

	.global OSi_vramLockId
OSi_vramLockId: ; 0x021D37E8
	.space 0x14

	.global UNK_021D37FC
UNK_021D37FC: ; 0x021D37FC
	.space 0x20

	.global UNK_021D381C
UNK_021D381C: ; 0x021D381C
	.space 0x4

	.global UNK_021D3820
UNK_021D3820: ; 0x021D3820
	.space 0x18

	.global UNK_021D3838
UNK_021D3838: ; 0x021D3838
	.space 0x4

	.global UNK_021D383C
UNK_021D383C: ; 0x021D383C
	.space 0x4

	.global UNK_021D3840
UNK_021D3840: ; 0x021D3840
	.space 0x4

	.global UNK_021D3844
UNK_021D3844: ; 0x021D3844
	.space 0x4

	.global UNK_021D3848
UNK_021D3848: ; 0x021D3848
	.space 0x4

	.global UNK_021D384C
UNK_021D384C: ; 0x021D384C
	.space 0x4

	.global UNK_021D3850
UNK_021D3850: ; 0x021D3850
	.space 0x4

	.global UNK_021D3854
UNK_021D3854: ; 0x021D3854
	.space 0x4

	.global UNK_021D3858
UNK_021D3858: ; 0x021D3858
	.space 0x4

	.global UNK_021D385C
UNK_021D385C: ; 0x021D385C
	.space 0x24

	.global UNK_021D3880
UNK_021D3880: ; 0x021D3880
	.space 0x280

	.global UNK_021D3B00
UNK_021D3B00: ; 0x021D3B00
	.space 0x1000

	.global UNK_021D4B00
UNK_021D4B00: ; 0x021D4B00
	.space 0x7e8

	.global UNK_021D52E8
UNK_021D52E8: ; 0x021D52E8
	.space 0x18

	.global UNK_021D5300
UNK_021D5300: ; 0x021D5300
	.space 0x60

	.global UNK_021D5360
UNK_021D5360: ; 0x021D5360
	.space 0x4

	.global UNK_021D5364
UNK_021D5364: ; 0x021D5364
	.space 0x4

	.global UNK_021D5368
UNK_021D5368: ; 0x021D5368
	.space 0x80
