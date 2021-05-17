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

const u16 MOD52_021D76F8[];

THUMB_FUNC BOOL MOD52_021D74E0();
THUMB_FUNC BOOL MOD52_021D74F8(struct UnkStruct_02006234 *param0, u32 *unused);
THUMB_FUNC BOOL MOD52_021D750C();

THUMB_FUNC BOOL MOD52_021D7528();
THUMB_FUNC BOOL MOD52_021D7540(struct UnkStruct_02006234 *param0, u32 *unused);
THUMB_FUNC BOOL MOD52_021D7560();

THUMB_FUNC BOOL MOD52_021D757C();
THUMB_FUNC BOOL MOD52_021D7594(struct UnkStruct_02006234 *param0, u32 *unused);
THUMB_FUNC BOOL MOD52_021D75E8();

THUMB_FUNC void MOD52_021D7604(u32 heap_id, struct SaveBlock2 *sav2, BOOL set_trainerid);
THUMB_FUNC void MOD52_021D7688(u32 param0, struct SaveBlock2 *sav2);
THUMB_FUNC void MOD52_021D769C(u32 param0, struct SaveBlock2 *sav2);

#endif // POKEDIAMOND_MODULE_52_H