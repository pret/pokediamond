#ifndef POKEDIAMOND_ARM7_SYSCALL_H
#define POKEDIAMOND_ARM7_SYSCALL_H

void SVC_WaitByLoop(u32 ct);
u8 SVC_GetVolumeTable(int idx);
u16 SVC_GetPitchTable(int idx);

#endif //POKEDIAMOND_ARM7_SYSCALL_H
