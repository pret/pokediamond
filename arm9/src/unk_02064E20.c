#include "global.h"
#include "scrcmd.h"
#include "unk_02025484.h"
#include "unk_02024E64.h"
#include "unk_02064E20.h"

void FUN_02064E20(struct FieldSystem* fieldSystem)
{
    struct unk_2025484 * r4 = (struct unk_2025484 *)FUN_02024ED8(ScriptEnvironment_GetSavePtr(fieldSystem));
    if((u32)FUN_020254B4(r4) == 6)
    {
        return;
    }
    FUN_02025490(r4, 6);
    u16 * ptr0 = (u16 *)FUN_020254A0(r4 , 6);
    ptr0[0] = 2;
}
