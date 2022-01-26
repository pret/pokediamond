#include "global.h"
#include "proto.h"
#include "unk_0205EC84.h"
#include "constants/sndseq.h"
#include "constants/maps.h"

static THUMB_FUNC void _flag_set(struct ScriptState * state, u16 flag_id)
{
    SetFlagInArray(state, flag_id);
}

static THUMB_FUNC void _flag_clear(struct ScriptState * state, u16 flag_id)
{
    ClearFlagInArray(state, flag_id);
}

static THUMB_FUNC BOOL _flag_check(struct ScriptState * state, u16 flag_id)
{
    return CheckFlagInArray(state, flag_id);
}

static THUMB_FUNC BOOL _flag_op(struct ScriptState * state, u32 op, u32 flag_id)
{
    switch (op)
    {
    case 1:
        _flag_set(state, (u16)flag_id);
        break;
    case 0:
        _flag_clear(state, (u16)flag_id);
        break;
    case 2:
        return _flag_check(state, (u16)flag_id);
    default:
        GF_ASSERT(0);
    }
    return FALSE;
}

THUMB_FUNC void FUN_0205ECD4(struct ScriptState * state)
{
    _flag_set(state, 0x960);
}

THUMB_FUNC BOOL FUN_0205ECE0(struct ScriptState * state)
{
    return _flag_check(state, 0x960);
}

THUMB_FUNC BOOL FUN_0205ECEC(struct ScriptState * state)
{
    return _flag_check(state, 0x98D);
}

THUMB_FUNC void FUN_0205ECFC(struct ScriptState * state)
{
    _flag_set(state, 0x964);
}

THUMB_FUNC BOOL FUN_0205ED0C(struct ScriptState * state)
{
    return _flag_check(state, 0x964);
}

THUMB_FUNC void FUN_0205ED1C(struct ScriptState * state)
{
    _flag_set(state, 0x961);
}

THUMB_FUNC void FUN_0205ED2C(struct ScriptState * state)
{
    _flag_clear(state, 0x961);
}

THUMB_FUNC BOOL FUN_0205ED3C(struct ScriptState * state)
{
    return _flag_check(state, 0x961);
}

THUMB_FUNC void FUN_0205ED4C(struct ScriptState * state)
{
    _flag_set(state, 0x965);
}

THUMB_FUNC void FUN_0205ED5C(struct ScriptState * state)
{
    _flag_clear(state, 0x965);
}

THUMB_FUNC BOOL FUN_0205ED6C(struct ScriptState * state)
{
    return _flag_check(state, 0x965);
}

THUMB_FUNC void FUN_0205ED7C(struct ScriptState * state)
{
    _flag_set(state, 0x96D);
}

THUMB_FUNC void FUN_0205ED8C(struct ScriptState * state)
{
    _flag_clear(state, 0x96D);
}

THUMB_FUNC BOOL FUN_0205ED9C(struct ScriptState * state)
{
    return _flag_check(state, 0x96D);
}

THUMB_FUNC void FUN_0205EDAC(struct ScriptState * state)
{
    _flag_set(state, 0x96E);
}

THUMB_FUNC void FUN_0205EDBC(struct ScriptState * state)
{
    _flag_set(state, 0x96F);
}

THUMB_FUNC void FUN_0205EDCC(struct ScriptState * state)
{
    _flag_set(state, 0x970);
}

THUMB_FUNC void FUN_0205EDD8(struct ScriptState * state)
{
    _flag_set(state, 0x971);
}

THUMB_FUNC void FUN_0205EDE8(struct ScriptState * state)
{
    _flag_set(state, 0x972);
}

THUMB_FUNC void FUN_0205EDF8(struct ScriptState * state)
{
    _flag_set(state, 0x973);
}

THUMB_FUNC void FUN_0205EE08(struct ScriptState * state, u32 a1)
{
    switch (a1)
    {
    case 0:
        _flag_set(state, 0x968);
        break;
    case 1:
        _flag_set(state, 0x969);
        break;
    case 2:
        _flag_set(state, 0x96A);
        break;
    case 3:
        _flag_set(state, 0x96B);
        break;
    case 4:
        _flag_set(state, 0x96C);
        break;
    }
}

THUMB_FUNC BOOL FUN_0205EE60(struct ScriptState * state, u32 a1)
{
    switch (a1)
    {
    case 0:
        return _flag_check(state, 0x968);
    case 1:
        return _flag_check(state, 0x969);
    case 2:
        return _flag_check(state, 0x96A);
    case 3:
        return _flag_check(state, 0x96B);
    case 4:
        return _flag_check(state, 0x96C);
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
        ret = _flag_check(state, 0x97F);
        break;
    case 2:
        ret = _flag_check(state, 0x980);
        break;
    case 3:
        ret = _flag_check(state, 0x981);
        break;
    case 4:
        ret = _flag_check(state, 0x982);
        break;
    case 5:
        ret = _flag_check(state, 0x983);
        break;
    }
    return ret;
}

THUMB_FUNC s32 FUN_0205EF20(struct ScriptState * state, s32 a1)
{
    s32 ret = 0;
    switch (a1)
    {
    case MAP_D28R0101:
        if (_flag_check(state, 0x984) == TRUE)
            ret = SEQ_D_LAKE;
        break;
    case MAP_D28R0103:
        if (_flag_check(state, 0x984) == TRUE)
            ret = SEQ_D_RYAYHY;
        break;
    case MAP_D27R0102:
        if (_flag_check(state, 0x98E) == TRUE)
            ret = SEQ_D_LAKE;
        break;
    case MAP_D29R0102:
        if (_flag_check(state, 0x98F) == TRUE)
            ret = SEQ_D_LAKE;
        break;
    case MAP_D10R0101:
        if (_flag_check(state, 0x995) == TRUE)
            ret = SEQ_D_SAFARI;
        break;
    case MAP_T02R0101:
        if (_flag_check(state, 0x993) == TRUE)
            ret = SEQ_OPENING2;
        break;
    case MAP_D26R0101:
    case MAP_D26R0102:
    case MAP_D26R0103:
    case MAP_D26R0104:
    case MAP_D26R0105:
    case MAP_D26R0106:
    case MAP_D26R0107:
    case MAP_D26R0108:
        if (_flag_check(state, 0x985) == TRUE)
        {
            if (!IsNighttime())
                ret = SEQ_CITY07_D;
            else
                ret = SEQ_CITY07_N;
        }
        else if (a1 == MAP_D26R0101)
        {
            if (_flag_check(state, 0x986) == TRUE)
                ret = SEQ_D_AGITO;
        }
        break;
    case MAP_C04R0201:
    case MAP_C04R0202:
    case MAP_C04R0203:
    case MAP_C04R0204:
        if (_flag_check(state, 0x987) == TRUE)
        {
            if (!IsNighttime())
                ret = SEQ_CITY04_D;
            else
                ret = SEQ_CITY04_N;
        }
        break;
    case MAP_D02R0101:
        if (_flag_check(state, 0x988) == TRUE)
        {
            if (!IsNighttime())
                ret = SEQ_ROAD_C_D;
            else
                ret = SEQ_ROAD_C_N;
        }
        break;
    case MAP_D13R0101:
        if (_flag_check(state, 0x989) == TRUE)
        {
            if (!IsNighttime())
                ret = SEQ_TOWN03_D;
            else
                ret = SEQ_TOWN03_N;
        }
        break;
    case MAP_R224:
        if (_flag_check(state, 0x98A) == TRUE)
        {
            if (!IsNighttime())
                ret = SEQ_TOWN03_D;
            else
                ret = SEQ_TOWN03_N;
        }
        break;
    case MAP_C10R0111:
        if (_flag_check(state, 0x98B) == TRUE)
            ret = SEQ_SILENCE_FIELD;
        break;
    }
    return ret;
}


THUMB_FUNC void FUN_0205F154(struct ScriptState * state)
{
    _flag_set(state, 0x966);
}

THUMB_FUNC void FUN_0205F164(struct ScriptState * state)
{
    _flag_clear(state, 0x966);
}

THUMB_FUNC BOOL FUN_0205F174(struct ScriptState * state)
{
    return _flag_check(state, 0x966);
}

THUMB_FUNC BOOL FUN_0205F184(struct ScriptState * state)
{
    return _flag_check(state, 0x978);
}

THUMB_FUNC BOOL FUN_0205F194(struct ScriptState * state)
{
    return _flag_check(state, 0x992);
}

THUMB_FUNC BOOL FUN_0205F1A4(struct ScriptState * state)
{
    return _flag_check(state, 0x97D);
}

THUMB_FUNC BOOL FUN_0205F1B4(struct ScriptState * state)
{
    return _flag_check(state, 0x97E);
}

THUMB_FUNC void FUN_0205F1C4(struct ScriptState * state)
{
    _flag_set(state, 0x97C);
}

THUMB_FUNC void FUN_0205F1D4(struct ScriptState * state)
{
    _flag_clear(state, 0x97C);
}

THUMB_FUNC BOOL FUN_0205F1E4(struct ScriptState * state)
{
    return _flag_check(state, 0x97C);
}

THUMB_FUNC void FUN_0205F1F4(struct ScriptState * state)
{
    _flag_set(state, 0x967);
}

THUMB_FUNC void FUN_0205F204(struct ScriptState * state)
{
    _flag_clear(state, 0x967);
}

THUMB_FUNC BOOL FUN_0205F214(struct ScriptState * state)
{
    return _flag_check(state, 0x967);
}

THUMB_FUNC void FUN_0205F224(struct ScriptState * state)
{
    _flag_set(state, 0x979);
}

THUMB_FUNC void FUN_0205F234(struct ScriptState * state)
{
    _flag_clear(state, 0x979);
}

THUMB_FUNC BOOL FUN_0205F244(struct ScriptState * state)
{
    return _flag_check(state, 0x979);
}

THUMB_FUNC void FUN_0205F254(struct ScriptState * state)
{
    _flag_clear(state, 0x994);
}

THUMB_FUNC BOOL FUN_0205F264(struct ScriptState * state, u32 op)
{
    return _flag_op(state, op, 0x962);
}

THUMB_FUNC void FUN_0205F274(struct ScriptState * state)
{
    _flag_set(state, 0x97A);
}

THUMB_FUNC void FUN_0205F284(struct ScriptState * state)
{
    _flag_clear(state, 0x97A);
}

THUMB_FUNC BOOL FUN_0205F294(struct ScriptState * state)
{
    return _flag_check(state, 0x97A);
}

THUMB_FUNC void FUN_0205F2A4(struct ScriptState * state)
{
    _flag_set(state, 0x97B);
}

THUMB_FUNC void FUN_0205F2B4(struct ScriptState * state)
{
    _flag_clear(state, 0x97B);
}

THUMB_FUNC BOOL FUN_0205F2C4(struct ScriptState * state)
{
    return _flag_check(state, 0x97B);
}

THUMB_FUNC BOOL FUN_0205F2D4(struct ScriptState * state, u32 op)
{
    return _flag_op(state, op, 0x963);
}

THUMB_FUNC BOOL FUN_0205F2E4(struct ScriptState * state, u32 op, u16 flag_id)
{
    GF_ASSERT(flag_id < 69);
    return _flag_op(state, op, 0x9B0 + flag_id);
}

THUMB_FUNC void FUN_0205F304(struct ScriptState * state)
{
    _flag_set(state, 0x98C);
}
