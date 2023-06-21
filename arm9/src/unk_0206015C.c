#include "global.h"
#include "unk_0206015C.h"

#include "constants/sndseq.h"
#include "event_data.h"
#include "heap.h"
#include "main.h"
#include "unk_020051F4.h"
#include "unk_0204AF24.h"

/*  Note to future reader, there might be some errors
    in the return type / parameters. They are right for this code
    but they might not be for every code, please do not blindly
    trust these prototypes if you are decompiling these functions. */
extern u32  MOD06_02244DB0(u32);
extern void MOD06_02244DBC(void*);
extern void MOD06_02244DC4(void*, void*);
extern void MOD06_02244EF8(void*);
extern void MOD06_02244F18(void*);
extern BOOL MOD06_02244F24(void*);
extern void MOD06_02244F2C(void*);
extern void * MOD06_02245088(struct FieldSystem *fieldSystem);
extern u32  MOD06_02245114(u32, struct FieldSystem *);
extern void MOD06_02245190(u32);
extern void MOD06_02245198(u8, u32);
extern u32  MOD06_022451F0(u32);

extern void sub_02049160(struct TaskManager *taskManager, u32);
extern void sub_0204C1B4(struct TaskManager *taskManager, u32,u32,u32,u32,u32,u32,u32);
extern struct Vecx32 *PlayerAvatar_GetMapObject(struct PlayerAvatar *playerAvatar);
extern void sub_0205889C(struct Vecx32 *param0, u32);
extern void sub_0205F1C4(struct ScriptState *);
extern void sub_0205F1D4(struct ScriptState *);
extern void sub_0206367C(struct FieldSystem *, u32);

void sub_0206015C(struct FieldSystem *fieldSystem)
{
    struct UnkStruct_0206015C *unkStruct = AllocFromHeapAtEnd(0xb, 0x10);
    unkStruct->unk0 = MOD06_02244DB0(0xb);
    unkStruct->unk4 = MOD06_02245114(0xb, fieldSystem);
    unkStruct->unkC = 0;
    unkStruct->unkD = 0;

    sub_0204640C(fieldSystem->taskManager, sub_02060194, (u32 *)unkStruct);
}

BOOL sub_02060194(struct TaskManager *taskManager)
{
    struct FieldSystem *fieldSystem = sub_02046528(taskManager);
    struct UnkStruct_0204652C *unkStruct1 = (struct UnkStruct_0204652C *)sub_0204652C(taskManager);

    switch (unkStruct1->action)
    {
    case 0:
        sub_0206367C(fieldSystem, 1);
        MOD06_02245198(unkStruct1->unkD, unkStruct1->unk4);
        unkStruct1->unk8 = MOD06_022451F0(unkStruct1->unk4);
        sub_0204AFC8(taskManager);
        unkStruct1->action = 1;
        break;

    case 1:
        sub_0204AF3C(taskManager);
        unkStruct1->action = 2;
        break;

    case 2:
        struct ScriptState *scrState = SaveArray_Flags_Get(fieldSystem->saveData);
        u8 unkD = unkStruct1->unkD;
        if (unkD == 0)
        {
            sub_0205F1C4(scrState);
        }
        else if (unkD == 5)
        {
            sub_0205F1D4(scrState);
        }
        sub_02049160(taskManager, unkStruct1->unk8);
        unkStruct1->action = 3;
        break;

    case 3:
        sub_0204AF84(taskManager);
        unkStruct1->action = 4;
        break;

    case 4:
        struct Vecx32 *unk0 = PlayerAvatar_GetMapObject(fieldSystem->playerAvatar);
        unkStruct1->unkD += 1;
        if (unkStruct1->unkD <= 5)
        {
            void *unkAddr = MOD06_02245088(fieldSystem);
            sub_0205889C(unk0, 1);
            MOD06_02244DC4(unkStruct1->unk0, unkAddr);
            MOD06_02244EF8(unkStruct1->unk0);
            unkStruct1->unkE = 0;
            PlaySE(SEQ_SE_DP_KASYA);
            sub_0204C1B4(taskManager, 0x3, 0x11, 0x0000FFFF, 0, 6, 1, 0xb);
            unkStruct1->action = 5;
        }
        else
        {
            sub_0205889C(unk0, 0);
            sub_0204B00C(taskManager);
            unkStruct1->action = 8;
        }
        break;

    case 5:
        unkStruct1->unkE += 1;
        if (unkStruct1->unkE < 0x3c && !(gSystem.newKeys & 1))
            break;

        MOD06_02245198(unkStruct1->unkD, unkStruct1->unk4);
        unkStruct1->unk8 = MOD06_022451F0(unkStruct1->unk4);

        PlaySE(SEQ_SE_DP_KASYA);
        sub_0204C1B4(taskManager, 0x3, 0x10, 0x0000FFFF, 0, 6, 1, 0xb);
        unkStruct1->action = 6;
        break;

    case 6:
        MOD06_02244F18(unkStruct1->unk0);
        unkStruct1->action = 7;
        break;

    case 7:
        if (MOD06_02244F24(unkStruct1->unk0))
        {
            MOD06_02244F2C(unkStruct1->unk0);
            unkStruct1->action = 1;
        }
        break;

    case 8:
        sub_0206367C(fieldSystem, 0);
        MOD06_02245190(unkStruct1->unk4);
        MOD06_02244DBC(unkStruct1->unk0);
        FreeToHeap(unkStruct1);
        return TRUE;

    default:
        break;
    }
    return FALSE;
}
