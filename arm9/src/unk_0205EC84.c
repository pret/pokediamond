#include "global.h"
#include "event_data.h"

THUMB_FUNC void FUN_0205EC84(struct ScriptState * state, u16 flag_id)
{
    SetFlagInArray(state, flag_id);
}

THUMB_FUNC void FUN_0205EC8C(struct ScriptState * state, u16 flag_id)
{
    ClearFlagInArray(state, flag_id);
}

THUMB_FUNC BOOL FUN_0205EC94(struct ScriptState * state, u16 flag_id)
{
    return CheckFlagInArray(state, flag_id);
}

THUMB_FUNC BOOL FUN_0205EC9C(struct ScriptState * state, u32 op, u32 flag_id)
{
    switch (op)
    {
    case 1:
        FUN_0205EC84(state, (u16)flag_id);
        break;
    case 0:
        FUN_0205EC8C(state, (u16)flag_id);
        break;
    case 2:
        return FUN_0205EC94(state, (u16)flag_id);
    default:
        GF_ASSERT(0);
    }
    return FALSE;
}

THUMB_FUNC void FUN_0205ECD4(struct ScriptState * state)
{
    FUN_0205EC84(state, 0x960);
}

THUMB_FUNC BOOL FUN_0205ECE0(struct ScriptState * state)
{
    return FUN_0205EC94(state, 0x960);
}

THUMB_FUNC BOOL FUN_0205ECEC(struct ScriptState * state)
{
    return FUN_0205EC94(state, 0x98D);
}

THUMB_FUNC void FUN_0205ECFC(struct ScriptState * state)
{
    FUN_0205EC84(state, 0x964);
}

THUMB_FUNC BOOL FUN_0205ED0C(struct ScriptState * state)
{
    return FUN_0205EC94(state, 0x964);
}

THUMB_FUNC void FUN_0205ED1C(struct ScriptState * state)
{
    FUN_0205EC84(state, 0x961);
}

THUMB_FUNC void FUN_0205ED2C(struct ScriptState * state)
{
    FUN_0205EC8C(state, 0x961);
}

THUMB_FUNC BOOL FUN_0205ED3C(struct ScriptState * state)
{
    return FUN_0205EC94(state, 0x961);
}

THUMB_FUNC void FUN_0205ED4C(struct ScriptState * state)
{
    FUN_0205EC84(state, 0x965);
}

THUMB_FUNC void FUN_0205ED5C(struct ScriptState * state)
{
    FUN_0205EC8C(state, 0x965);
}

THUMB_FUNC BOOL FUN_0205ED6C(struct ScriptState * state)
{
    return FUN_0205EC94(state, 0x965);
}

THUMB_FUNC void FUN_0205ED7C(struct ScriptState * state)
{
    FUN_0205EC84(state, 0x96D);
}

THUMB_FUNC void FUN_0205ED8C(struct ScriptState * state)
{
    FUN_0205EC8C(state, 0x96D);
}

THUMB_FUNC BOOL FUN_0205ED9C(struct ScriptState * state)
{
    return FUN_0205EC94(state, 0x96D);
}

THUMB_FUNC void FUN_0205EDAC(struct ScriptState * state)
{
    FUN_0205EC84(state, 0x96E);
}

THUMB_FUNC void FUN_0205EDBC(struct ScriptState * state)
{
    FUN_0205EC84(state, 0x96F);
}

THUMB_FUNC void FUN_0205EDCC(struct ScriptState * state)
{
    FUN_0205EC84(state, 0x970);
}

THUMB_FUNC void FUN_0205EDD8(struct ScriptState * state)
{
    FUN_0205EC84(state, 0x971);
}

THUMB_FUNC void FUN_0205EDE8(struct ScriptState * state)
{
    FUN_0205EC84(state, 0x972);
}

THUMB_FUNC void FUN_0205EDF8(struct ScriptState * state)
{
    FUN_0205EC84(state, 0x973);
}

THUMB_FUNC void FUN_0205EE08(struct ScriptState * state, u32 a1)
{
    switch (a1)
    {
    case 0:
        FUN_0205EC84(state, 0x968);
        break;
    case 1:
        FUN_0205EC84(state, 0x969);
        break;
    case 2:
        FUN_0205EC84(state, 0x96A);
        break;
    case 3:
        FUN_0205EC84(state, 0x96B);
        break;
    case 4:
        FUN_0205EC84(state, 0x96C);
        break;
    }
}

THUMB_FUNC BOOL FUN_0205EE60(struct ScriptState * state, u32 a1)
{
    switch (a1)
    {
    case 0:
        return FUN_0205EC94(state, 0x968);
    case 1:
        return FUN_0205EC94(state, 0x969);
    case 2:
        return FUN_0205EC94(state, 0x96A);
    case 3:
        return FUN_0205EC94(state, 0x96B);
    case 4:
        return FUN_0205EC94(state, 0x96C);
    }
    // UB: No return value
}

THUMB_FUNC BOOL FUN_0205EEB8(struct ScriptState * state, u32 a1)
{
    BOOL ret = FALSE;
    switch (a1)
    {
    case 0:
        break;
    case 1:
        ret = FUN_0205EC94(state, 0x97F);
        break;
    case 2:
        ret = FUN_0205EC94(state, 0x980);
        break;
    case 3:
        ret = FUN_0205EC94(state, 0x981);
        break;
    case 4:
        ret = FUN_0205EC94(state, 0x982);
        break;
    case 5:
        ret = FUN_0205EC94(state, 0x983);
        break;
    }
    return ret;
}
