#ifndef GUARD_UNK_0204639C_H
#define GUARD_UNK_0204639C_H

#include "script.h"

struct UnkStruct_0204639C;

typedef BOOL (*UnkStruct_0204639C_cb)(struct UnkStruct_0204639C * );

struct UnkStruct_0204639C
{
    struct UnkStruct_0204639C * unk0;
    UnkStruct_0204639C_cb unk4;
    u32 unk8;
    u32 * unkC;
    struct UnkStruct_0204639C * unk10;
    void * unk14;
    struct FieldSystem *fieldSystem;
    u32 * unk1C;
};

extern void LoadOverlay_MODULE_05(void *);
extern void FUN_020373D4(struct FieldSystem *, u32, u32);
extern BOOL FUN_020373AC(void *);
extern BOOL FUN_0203739C(void *);
extern BOOL FUN_020373C4(void *);

struct UnkStruct_0204639C * FUN_0204639C(struct FieldSystem *fieldSystem, UnkStruct_0204639C_cb r6, u32 * r7);
void FUN_020463CC(struct FieldSystem *fieldSystem, UnkStruct_0204639C_cb r4, u32 * r6);
void FUN_020463EC(struct UnkStruct_0204639C * r4, UnkStruct_0204639C_cb r1, u32 * r2);
void FUN_0204640C(struct UnkStruct_0204639C * r4, UnkStruct_0204639C_cb r1, u32 * r2);
BOOL FUN_02046420(struct UnkStruct_0204639C * r5);
BOOL FUN_0204646C(struct UnkStruct_0204639C * r0);
BOOL FUN_0204647C(void * r4);
void FUN_0204649C(void * r0);
BOOL FUN_020464A4(void * r0);
BOOL FUN_020464B8(struct UnkStruct_0204639C * r4);
void FUN_02046500(struct UnkStruct_0204639C * r6, u32 r5, u32 r4);
u32 * FUN_0204652C(struct UnkStruct_0204639C * r0);
u32 * FUN_02046530(struct UnkStruct_0204639C * r0);
u32 FUN_02046534(struct UnkStruct_0204639C * r0);
struct FieldSystem *FUN_02046528(struct UnkStruct_0204639C *);

#endif //GUARD_UNK_0204639C_H
