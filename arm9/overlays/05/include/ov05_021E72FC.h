#ifndef POKEDIAMOND_ov05_021E72FC_H
#define POKEDIAMOND_ov05_021E72FC_H

#include "nitro/types.h"

#include "field_system.h"
#include "task.h"

typedef struct UnkStruct021E7358 {
    u32 Unk00;
    u32 Unk04;
    u32 Unk08;
    FieldSystem *fieldSystem;
    u32 Unk10;

} UnkStruct021E7358;

BOOL ov05_021E72FC(FieldSystem *fieldSystem, u32 param1);
void ov05_021E7358(FieldSystem *fieldSystem, u32 param1, u32 param2);
u32 ov05_021E7388(u32 param0);
BOOL ov05_021E73B4(TaskManager *taskManager);
UnkStruct021E7358 *ov05_021E74D4(u32 param0);
void ov05_021E74F8(UnkStruct021E7358 *param0);

#endif // POKEDIAMOND_ov05_021E72FC_H
