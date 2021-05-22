#ifndef POKEDIAMOND_MODULE_52_H
#define POKEDIAMOND_MODULE_52_H

#include "global.h"
#include "event_data.h"
#include "main.h"
#include "math_util.h"
#include "options.h"
#include "overlay_manager.h"
#include "player_data.h"
#include "sav_system_info.h"
#include "save_block_2.h"
#include "unk_02024E64.h"
#include "unk_020286F8.h"

extern const struct Unk21DBE18 MOD52_021D76E8;
extern const struct Unk21DBE18 MOD52_021D76D8;
extern const struct Unk21DBE18 MOD52_021D76C8;

BOOL MOD52_021D74E0(struct UnkStruct_02006234 *arg1, u32 *arg2);
BOOL MOD52_021D74F8(struct UnkStruct_02006234 *param0, u32 *unused);
BOOL MOD52_021D750C(struct UnkStruct_02006234 *arg1, u32 *arg2);

BOOL MOD52_021D7528(struct UnkStruct_02006234 *arg1, u32 *arg2);
BOOL MOD52_021D7540(struct UnkStruct_02006234 *param0, u32 *unused);
BOOL MOD52_021D7560(struct UnkStruct_02006234 *arg1, u32 *arg2);

BOOL MOD52_021D757C(struct UnkStruct_02006234 *arg1, u32 *arg2);
BOOL MOD52_021D7594(struct UnkStruct_02006234 *param0, u32 *unused);
BOOL MOD52_021D75E8(struct UnkStruct_02006234 *arg1, u32 *arg2);

void MOD52_021D7604(u32 heap_id, struct SaveBlock2 *sav2, BOOL set_trainerid);
void MOD52_021D7688(u32 param0, struct SaveBlock2 *sav2);
void MOD52_021D769C(u32 param0, struct SaveBlock2 *sav2);

#endif // POKEDIAMOND_MODULE_52_H