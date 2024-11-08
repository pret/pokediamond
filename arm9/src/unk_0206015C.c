#include "unk_0206015C.h"

#include "global.h"

#include "constants/sndseq.h"

#include "heap.h"
#include "main.h"
#include "map_object.h"
#include "save_vars_flags.h"
#include "unk_020051F4.h"
#include "unk_0204AF24.h"

/*  Note to future reader, there might be some errors
    in the return type / parameters. They are right for this code
    but they might not be for every code, please do not blindly
    trust these prototypes if you are decompiling these functions. */
extern u32 ov06_02244DB0(HeapID);
extern void ov06_02244DBC(void *);
extern void ov06_02244DC4(void *, void *);
extern void ov06_02244EF8(void *);
extern void ov06_02244F18(void *);
extern BOOL ov06_02244F24(void *);
extern void ov06_02244F2C(void *);
extern void *ov06_02245088(struct FieldSystem *fieldSystem);
extern u32 ov06_02245114(HeapID, struct FieldSystem *);
extern void ov06_02245190(u32);
extern void ov06_02245198(u8, u32);
extern u32 ov06_022451F0(u32);

extern void sub_02049160(struct TaskManager *taskManager, u32);
extern void sub_0204C1B4(struct TaskManager *taskManager, u32, u32, u32, u32, u32, u32, u32);
extern LocalMapObject *PlayerAvatar_GetMapObject(struct PlayerAvatar *playerAvatar);
extern void sub_0205F1C4(struct SaveVarsFlags *);
extern void sub_0205F1D4(struct SaveVarsFlags *);
extern void sub_0206367C(struct FieldSystem *, u32);

void CallTask_UseGreatMarshBinoculars(struct FieldSystem *fieldSystem) {
    struct UnkStruct_0206015C *unkStruct = AllocFromHeapAtEnd(HEAP_ID_FIELD, 0x10);
    unkStruct->unk0                      = ov06_02244DB0(HEAP_ID_FIELD);
    unkStruct->unk4                      = ov06_02245114(HEAP_ID_FIELD, fieldSystem);
    unkStruct->unkC                      = 0;
    unkStruct->unkD                      = 0;

    TaskManager_Call(fieldSystem->taskManager, Task_UseGreatMarshBinoculars, (u32 *)unkStruct);
}

BOOL Task_UseGreatMarshBinoculars(struct TaskManager *taskManager) {
    struct FieldSystem *fieldSystem       = TaskManager_GetFieldSystem(taskManager);
    struct UnkStruct_0204652C *unkStruct1 = (struct UnkStruct_0204652C *)TaskManager_GetEnvironment(taskManager);

    switch (unkStruct1->action) {
    case 0:
        sub_0206367C(fieldSystem, 1);
        ov06_02245198(unkStruct1->unkD, unkStruct1->unk4);
        unkStruct1->unk8 = ov06_022451F0(unkStruct1->unk4);
        CallTask_FadeToBlack(taskManager);
        unkStruct1->action = 1;
        break;

    case 1:
        sub_0204AF3C(taskManager);
        unkStruct1->action = 2;
        break;

    case 2:
        struct SaveVarsFlags *scrState = Save_VarsFlags_Get(fieldSystem->saveData);
        u8 unkD                        = unkStruct1->unkD;
        if (unkD == 0) {
            sub_0205F1C4(scrState);
        } else if (unkD == 5) {
            sub_0205F1D4(scrState);
        }
        sub_02049160(taskManager, unkStruct1->unk8);
        unkStruct1->action = 3;
        break;

    case 3:
        CallTask_RestoreOverworld(taskManager);
        unkStruct1->action = 4;
        break;

    case 4:
        LocalMapObject *playerObject = PlayerAvatar_GetMapObject(fieldSystem->playerAvatar);
        unkStruct1->unkD += 1;
        if (unkStruct1->unkD <= 5) {
            void *unkAddr = ov06_02245088(fieldSystem);
            MapObject_SetVisible(playerObject, TRUE);
            ov06_02244DC4(unkStruct1->unk0, unkAddr);
            ov06_02244EF8(unkStruct1->unk0);
            unkStruct1->unkE = 0;
            PlaySE(SEQ_SE_DP_KASYA);
            sub_0204C1B4(taskManager, 0x3, 0x11, 0x0000FFFF, 0, 6, 1, 0xb);
            unkStruct1->action = 5;
        } else {
            MapObject_SetVisible(playerObject, FALSE);
            CallTask_FadeFromBlack(taskManager);
            unkStruct1->action = 8;
        }
        break;

    case 5:
        unkStruct1->unkE += 1;
        if (unkStruct1->unkE < 0x3c && !(gSystem.newKeys & 1)) {
            break;
        }

        ov06_02245198(unkStruct1->unkD, unkStruct1->unk4);
        unkStruct1->unk8 = ov06_022451F0(unkStruct1->unk4);

        PlaySE(SEQ_SE_DP_KASYA);
        sub_0204C1B4(taskManager, 0x3, 0x10, 0x0000FFFF, 0, 6, 1, 0xb);
        unkStruct1->action = 6;
        break;

    case 6:
        ov06_02244F18(unkStruct1->unk0);
        unkStruct1->action = 7;
        break;

    case 7:
        if (ov06_02244F24(unkStruct1->unk0)) {
            ov06_02244F2C(unkStruct1->unk0);
            unkStruct1->action = 1;
        }
        break;

    case 8:
        sub_0206367C(fieldSystem, 0);
        ov06_02245190(unkStruct1->unk4);
        ov06_02244DBC(unkStruct1->unk0);
        FreeToHeap(unkStruct1);
        return TRUE;

    default:
        break;
    }
    return FALSE;
}
