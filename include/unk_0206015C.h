#ifndef UNK_0206015C_H_GUARD
#define UNK_0206015C_H_GUARD

#include "global.h"
#include "script.h"
#include "task.h"

struct UnkStruct_0206015C
{
    u32   unk0;
    u32   unk4;
    u32   unk8;
    u8    unkC;
    u8    unkD;
};

struct UnkStruct_0204652C
{
    void* unk0;
    u32   unk4;
    u32   unk8;
    u8    action;
    u8    unkD; // some kind of counter?
    u8    unkE; // some kind of counter?
};

void FUN_0206015C(struct FieldSystem *fieldSystem);
BOOL FUN_02060194(struct TaskManager *taskManager);

#endif //UNK_0206015C_H_GUARD
