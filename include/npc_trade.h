#ifndef POKEDIAMOND_NPC_TRADE_H
#define POKEDIAMOND_NPC_TRADE_H

#include "field_types_def.h"
#include "heap.h"
#include "options.h"
#include "player_data.h"
#include "pokemon.h"
#include "launch_application.h"
#include "script.h"

void FieldTask_StartNPCTrade(TaskManager *taskManager, NPCTradeData *npcTradeData, u16 partySlot, enum HeapID heapID);

#endif // POKEDIAMOND_NPC_TRADE_H
