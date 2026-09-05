#include "npc_trade.h"

#include "global.h"

#include "field_system.h"
#include "heap.h"
#include "overlay_manager.h"
#include "pokemon.h"
#include "task.h"
#include "field_transition.h"

extern BOOL ov81_02237E40(struct OverlayManager *manager, u32 *status);
extern BOOL ov81_02238064(struct OverlayManager *manager, u32 *status);
extern BOOL ov81_02238004(struct OverlayManager *manager, u32 *status);

extern void NPCTrade_ReceiveMon(FieldSystem *fieldSystem, NPCTradeData *npcTradeData, u32 partySlot);
extern void NPCTrade_FillAnimationTemplate(FieldSystem *fieldSystem, NPCTradeData *npcTradeData, u32 partySlot, TradeAnimationTemplate *animationConfig, Pokemon *givingPokemon, Pokemon *receivingPokemon);

typedef struct NPCTradeTaskEnv {
    NPCTradeData *npcTradeData;
    u32 state;
    u32 partySlot;
    TradeAnimationTemplate tradeAnimTemplate;
    Pokemon *givingPokemon;
    Pokemon *receivingPokemon;
} NPCTradeTaskEnv;

static void StartTradeApplication(TaskManager *taskManager);
static BOOL FieldTask_ProcessNPCTrade(TaskManager *taskManager);

FS_EXTERN_OVERLAY(OVERLAY_81);

const OverlayManagerTemplate UNK_020F7630 = {
    ov81_02237E40,
    ov81_02238064,
    ov81_02238004,
    FS_OVERLAY_ID(OVERLAY_81),
};

static void StartTradeApplication(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    NPCTradeTaskEnv *env = TaskManager_GetEnvironment(taskManager);

#pragma unused(fieldSystem)
    sub_02046500(taskManager, (u32)&UNK_020F7630, (u32)&env->tradeAnimTemplate);
}

static BOOL FieldTask_ProcessNPCTrade(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    NPCTradeTaskEnv *env = TaskManager_GetEnvironment(taskManager);

    switch (env->state) {
    case 0:
        NPCTrade_FillAnimationTemplate(fieldSystem, env->npcTradeData, env->partySlot, &env->tradeAnimTemplate, env->givingPokemon, env->receivingPokemon);
        NPCTrade_ReceiveMon(fieldSystem, env->npcTradeData, env->partySlot);
        env->state++;
        break;
    case 1:
        FieldTransition_FadeOut(taskManager);
        env->state++;
        break;
    case 2:
        FieldTransition_FinishMap(taskManager);
        env->state++;
        break;
    case 3:
        StartTradeApplication(taskManager);
        env->state++;
        break;
    case 4:
        FieldTransition_StartMap(taskManager);
        env->state++;
        break;
    case 5:
        FieldTransition_FadeIn(taskManager);
        env->state++;
        break;
    case 6:
        Heap_Free(env->givingPokemon);
        Heap_Free(env->receivingPokemon);
        Heap_Free(env);
        return TRUE;
    }

    return FALSE;
}

void FieldTask_StartNPCTrade(TaskManager *taskManager, NPCTradeData *npcTradeData, u16 partySlot, enum HeapID heapID) {
    NPCTradeTaskEnv *env = Heap_Alloc(heapID, sizeof(NPCTradeTaskEnv));
    memset(env, 0, sizeof(NPCTradeTaskEnv));

    env->state = 0;
    env->npcTradeData = npcTradeData;
    env->partySlot = partySlot;
    env->givingPokemon = AllocMonZeroed(heapID);
    env->receivingPokemon = AllocMonZeroed(heapID);

    TaskManager_Call(taskManager, FieldTask_ProcessNPCTrade, env);
}
