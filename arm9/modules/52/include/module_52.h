#ifndef POKEDIAMOND_MODULE_52_H
#define POKEDIAMOND_MODULE_52_H

#include "global.h"
#include "event_data.h"
#include "main.h"
#include "math_util.h"
#include "options.h"
#include "overlay_manager.h"
#include "player_data.h"
#include "poke_overlay.h"
#include "sav_system_info.h"
#include "save_block_2.h"
#include "unk_02024E64.h"
#include "unk_020286F8.h"

extern const struct OverlayManagerTemplate MOD52_021D76E8;
extern const struct OverlayManagerTemplate MOD52_021D76D8;
extern const struct OverlayManagerTemplate MOD52_021D76C8;

BOOL MOD52_021D74E0(struct OverlayManager *manager, u32 *status);
BOOL MOD52_021D74F8(struct OverlayManager *param0, u32 *status);
BOOL MOD52_021D750C(struct OverlayManager *arg1, u32 *status);

BOOL MOD52_021D7528(struct OverlayManager *arg1, u32 *status);
BOOL MOD52_021D7540(struct OverlayManager *param0, u32 *status);
BOOL MOD52_021D7560(struct OverlayManager *arg1, u32 *status);

BOOL MOD52_021D757C(struct OverlayManager *arg1, u32 *status);
BOOL MOD52_021D7594(struct OverlayManager *param0, u32 *status);
BOOL MOD52_021D75E8(struct OverlayManager *arg1, u32 *status);

void MOD52_021D7604(u32 heap_id, struct SaveBlock2 *sav2, BOOL set_trainerid);
void MOD52_021D7688(u32 param0, struct SaveBlock2 *sav2);
void MOD52_021D769C(u32 param0, struct SaveBlock2 *sav2);

#endif // POKEDIAMOND_MODULE_52_H