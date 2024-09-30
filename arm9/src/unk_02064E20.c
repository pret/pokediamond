#include "unk_02064E20.h"

#include "global.h"

#include "scrcmd.h"
#include "unk_02024E64.h"
#include "unk_02025484.h"

void KeepSafariTrain(struct FieldSystem *fieldSystem) {
    struct unk_2025484 *r4 = (struct unk_2025484 *)sub_02024ED8(FieldSystem_GetSaveData(fieldSystem));
    if ((u32)sub_020254B4(r4) == 6) {
        return;
    }
    sub_02025490(r4, 6);
    u16 *ptr0 = (u16 *)sub_020254A0(r4, 6);
    ptr0[0]   = 2;
}
