//
// Created by red031000 on 2020-05-03.
//

#ifndef POKEDIAMOND_OS_SPINLOCK_H
#define POKEDIAMOND_OS_SPINLOCK_H

typedef volatile struct OSLockWord {
    u32 lockFlag;
    u16 ownerID;
    u16 extension;
} OSLockWord;

s32 OS_GetLockID(void);

#endif //POKEDIAMOND_OS_SPINLOCK_H
