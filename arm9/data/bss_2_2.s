    .section .bss

	.global OSi_StackForDestructor
OSi_StackForDestructor: ; 0x021D3480
	.space 0x4

	.global OSi_RescheduleCount
OSi_RescheduleCount: ; 0x021D3484
	.space 0x4

	.global OSi_ThreadIdCount
OSi_ThreadIdCount: ; 0x021D3488
	.space 0x4

	.global OSi_SystemCallbackInSwitchThread
OSi_SystemCallbackInSwitchThread: ; 0x021D348C
	.space 0x4

	.global OSi_CurrentThreadPtr
OSi_CurrentThreadPtr: ; 0x021D3490
	.space 0x4

	.global OSi_IsThreadInitialized
OSi_IsThreadInitialized: ; 0x021D3494
	.space 0x4

	.global OSi_ThreadInfo
OSi_ThreadInfo: ; 0x021D3498
	.space 0x4

	.global UNK_021D349C
UNK_021D349C: ; 0x021D349C
	.space 0xc

	.global OSi_IdleThread
OSi_IdleThread: ; 0x021D34A8
	.space 0xc0

	.global OSi_LauncherThread
OSi_LauncherThread: ; 0x021D3568
	.space 0xC0

	.global OSi_IdleThreadStack
OSi_IdleThreadStack: ; 0x021D3628
	.space 0xC8

	.global OSi_Initialized
OSi_Initialized: ; 0x021D36F0
	.space 0x4

	.global OSi_MainExArenaEnabled
OSi_MainExArenaEnabled: ; 0x021D36F4
	.space 0x4
