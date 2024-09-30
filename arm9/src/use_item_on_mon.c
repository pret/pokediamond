#include "use_item_on_mon.h"

#include "global.h"

#include "constants/moves.h"

#include "heap.h"
#include "itemtool.h"
#include "move_data.h"
#include "party.h"
#include "pokemon.h"

BOOL CanUseItemOnPokemon(struct Pokemon *pokemon, u16 itemId, s32 moveId, HeapID heapId) {
    s32 atkEv;
    s32 defEv;
    s32 speedEv;
    s32 spAtkEv;
    s32 spDefEv;
    s32 hpEv;
    u32 hp;
    struct ItemData *itemData;
    u32 status;

    itemData = LoadItemDataOrGfx(itemId, ITEMDATA_DATA, heapId);

    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PARTY_USE) != 1) {
        FreeToHeap(itemData);
        return FALSE;
    }
    status = GetMonData(pokemon, MON_DATA_STATUS, NULL);
    // slp
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_SLP_HEAL) && (status & MON_STATUS_SLP_MASK)) {
        FreeToHeap(itemData);
        return TRUE;
    }
    // psn
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PSN_HEAL) && (status & (MON_STATUS_PSN_MASK | MON_STATUS_TOX_MASK))) {
        FreeToHeap(itemData);
        return TRUE;
    }
    // brn
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_BRN_HEAL) && (status & MON_STATUS_BRN_MASK)) {
        FreeToHeap(itemData);
        return TRUE;
    }
    // frz
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_FRZ_HEAL) && (status & MON_STATUS_FRZ_MASK)) {
        FreeToHeap(itemData);
        return TRUE;
    }
    // prz
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PRZ_HEAL) && (status & MON_STATUS_PRZ_MASK)) {
        FreeToHeap(itemData);
        return TRUE;
    }
    hp = GetMonData(pokemon, MON_DATA_HP, NULL);
    if ((GetItemAttr_PreloadedItemData(itemData, ITEMATTR_REVIVE) || GetItemAttr_PreloadedItemData(itemData, ITEMATTR_REVIVE_ALL)) && !GetItemAttr_PreloadedItemData(itemData, ITEMATTR_LEVEL_UP)) {
        if (hp == 0) {
            FreeToHeap(itemData);
            return TRUE;
        }
    } else if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_HP_RESTORE) && hp != 0 && hp < GetMonData(pokemon, MON_DATA_MAXHP, NULL)) {
        FreeToHeap(itemData);
        return TRUE;
    }
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_LEVEL_UP) && GetMonData(pokemon, MON_DATA_LEVEL, NULL) < MAX_LEVEL) {
        FreeToHeap(itemData);
        return TRUE;
    }
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_EVOLVE) && GetMonEvolution(NULL, pokemon, 3, itemId, NULL) != SPECIES_NONE) {
        FreeToHeap(itemData);
        return TRUE;
    }
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PP_UP) || GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PP_MAX)) {
        if (GetMonData(pokemon, MON_DATA_MOVE1PPUP + moveId, NULL) < 3 && WazaGetMaxPp((u16)GetMonData(pokemon, MON_DATA_MOVE1 + moveId, NULL), 0) >= 5) {
            FreeToHeap(itemData);
            return TRUE;
        }
    }
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PP_RESTORE) && MonMoveCanRestorePP(pokemon, moveId) == TRUE) {
        FreeToHeap(itemData);
        return TRUE;
    }
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PP_RESTORE_ALL)) {
        for (int i = 0; i < MAX_MON_MOVES; i++) {
            if (MonMoveCanRestorePP(pokemon, i) == TRUE) {
                FreeToHeap(itemData);
                return TRUE;
            }
        }
    }
    hpEv    = (s32)GetMonData(pokemon, MON_DATA_HP_EV, NULL);
    atkEv   = (s32)GetMonData(pokemon, MON_DATA_ATK_EV, NULL);
    defEv   = (s32)GetMonData(pokemon, MON_DATA_DEF_EV, NULL);
    speedEv = (s32)GetMonData(pokemon, MON_DATA_SPEED_EV, NULL);
    spAtkEv = (s32)GetMonData(pokemon, MON_DATA_SPATK_EV, NULL);
    spDefEv = (s32)GetMonData(pokemon, MON_DATA_SPDEF_EV, NULL);
    if (GetMonData(pokemon, MON_DATA_SPECIES, NULL) != SPECIES_SHEDINJA && GetItemAttr_PreloadedItemData(itemData, ITEMATTR_HP_EV_UP)) {
        s32 dHpEv = (s32)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_HP_EV_UP_PARAM);
        if (dHpEv > 0) {
            if (hpEv < MAX_EV && (hpEv + atkEv + defEv + speedEv + spAtkEv + spDefEv) < MAX_EV_SUM) {
                FreeToHeap(itemData);
                return TRUE;
            }
        } else if (dHpEv < 0) {
            if (hpEv > 0) {
                FreeToHeap(itemData);
                return TRUE;
            } else if (CanItemModFriendship(pokemon, itemData) == TRUE) {
                FreeToHeap(itemData);
                return TRUE;
            }
        }
    }
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_ATK_EV_UP)) {
        s32 dAtkEv = (s32)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_ATK_EV_UP_PARAM);
        if (dAtkEv > 0) {
            if (atkEv < MAX_EV && (hpEv + atkEv + defEv + speedEv + spAtkEv + spDefEv) < MAX_EV_SUM) {
                FreeToHeap(itemData);
                return TRUE;
            }
        } else if (dAtkEv < 0) {
            if (atkEv > 0) {
                FreeToHeap(itemData);
                return TRUE;
            } else if (CanItemModFriendship(pokemon, itemData) == TRUE) {
                FreeToHeap(itemData);
                return TRUE;
            }
        }
    }
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_DEF_EV_UP)) {
        s32 dDefEv = (s32)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_DEF_EV_UP_PARAM);
        if (dDefEv > 0) {
            if (defEv < MAX_EV && (hpEv + atkEv + defEv + speedEv + spAtkEv + spDefEv) < MAX_EV_SUM) {
                FreeToHeap(itemData);
                return TRUE;
            }
        } else if (dDefEv < 0) {
            if (defEv > 0) {
                FreeToHeap(itemData);
                return TRUE;
            } else if (CanItemModFriendship(pokemon, itemData) == TRUE) {
                FreeToHeap(itemData);
                return TRUE;
            }
        }
    }
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_SPEED_EV_UP)) {
        s32 dSpeedEv = (s32)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_SPEED_EV_UP_PARAM);
        if (dSpeedEv > 0) {
            if (speedEv < MAX_EV && (hpEv + atkEv + defEv + speedEv + spAtkEv + spDefEv) < MAX_EV_SUM) {
                FreeToHeap(itemData);
                return TRUE;
            }
        } else if (dSpeedEv < 0) {
            if (speedEv > 0) {
                FreeToHeap(itemData);
                return TRUE;
            } else if (CanItemModFriendship(pokemon, itemData) == TRUE) {
                FreeToHeap(itemData);
                return TRUE;
            }
        }
    }
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_SPATK_EV_UP)) {
        s32 dSpAtkEv = (s32)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_SPATK_EV_UP_PARAM);
        if (dSpAtkEv > 0) {
            if (spAtkEv < MAX_EV && (hpEv + atkEv + defEv + speedEv + spAtkEv + spDefEv) < MAX_EV_SUM) {
                FreeToHeap(itemData);
                return TRUE;
            }
        } else if (dSpAtkEv < 0) {
            if (spAtkEv > 0) {
                FreeToHeap(itemData);
                return TRUE;
            } else if (CanItemModFriendship(pokemon, itemData) == TRUE) {
                FreeToHeap(itemData);
                return TRUE;
            }
        }
    }
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_SPDEF_EV_UP)) {

        s32 dSpDefEv = (s32)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_SPDEF_EV_UP_PARAM);
        if (dSpDefEv > 0) {
            if (spDefEv < MAX_EV && (hpEv + atkEv + defEv + speedEv + spAtkEv + spDefEv) < MAX_EV_SUM) {
                FreeToHeap(itemData);
                return TRUE;
            }
        } else if (dSpDefEv < 0) {
            if (spDefEv > 0) {
                FreeToHeap(itemData);
                return TRUE;
            } else if (CanItemModFriendship(pokemon, itemData) == TRUE) {
                FreeToHeap(itemData);
                return TRUE;
            }
        }
    }
    FreeToHeap(itemData);
    return FALSE;
}

BOOL CanUseItemOnMonInParty(struct Party *party, u16 itemId, s32 partyIdx, s32 moveIdx, HeapID heapId) {
    struct Pokemon *pokemon = Party_GetMonByIndex(party, partyIdx);
    return CanUseItemOnPokemon(pokemon, itemId, moveIdx, heapId);
}

BOOL UseItemOnPokemon(struct Pokemon *pokemon, u16 itemId, s32 moveIdx, u16 location, HeapID heapId) {
    s32 stack_data[8];
#define sp6C stack_data[7]
#define sp68 stack_data[6]
#define sp64 stack_data[5]
#define sp60 stack_data[4]
#define sp5C stack_data[3]
#define sp58 stack_data[2]
#define sp54 stack_data[1]
#define sp50 stack_data[0]
    BOOL hadEffect;
    BOOL effectFound;

    struct ItemData *itemData = LoadItemDataOrGfx(itemId, ITEMDATA_DATA, heapId);
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PARTY_USE) != 1) {
        FreeToHeap(itemData);
        return FALSE;
    }
    hadEffect   = FALSE;
    effectFound = FALSE;
    {
        sp54 = sp50 = (int)GetMonData(pokemon, MON_DATA_STATUS, NULL);
        if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_SLP_HEAL)) {
            sp54 &= ~MON_STATUS_SLP_MASK;
            effectFound = TRUE;
        }
        if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PSN_HEAL)) {
            sp54 &= ~(MON_STATUS_PSN_MASK | MON_STATUS_TOX_MASK | 0xF00);
            effectFound = TRUE;
        }
        if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_BRN_HEAL)) {
            sp54 &= ~MON_STATUS_BRN_MASK;
            effectFound = TRUE;
        }
        if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_FRZ_HEAL)) {
            sp54 &= ~MON_STATUS_FRZ_MASK;
            effectFound = TRUE;
        }
        if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PRZ_HEAL)) {
            sp54 &= ~MON_STATUS_PRZ_MASK;
            effectFound = TRUE;
        }
        if (sp50 != sp54) {
            SetMonData(pokemon, MON_DATA_STATUS, &sp54);
            hadEffect = TRUE;
        }
    }
    {
        sp50 = (int)GetMonData(pokemon, MON_DATA_HP, NULL);
        sp54 = (int)GetMonData(pokemon, MON_DATA_MAXHP, NULL);
        if ((GetItemAttr_PreloadedItemData(itemData, ITEMATTR_REVIVE) || GetItemAttr_PreloadedItemData(itemData, ITEMATTR_REVIVE_ALL)) && GetItemAttr_PreloadedItemData(itemData, ITEMATTR_LEVEL_UP)) {
            if (sp50 == 0) {
                RestoreMonHPBy(pokemon, (u32)sp50, (u32)sp54, GetItemAttr_PreloadedItemData(itemData, ITEMATTR_HP_RESTORE_PARAM));
                hadEffect = TRUE;
            }
            effectFound = TRUE;
        } else if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_HP_RESTORE)) {
            if (sp50 < sp54) {
                RestoreMonHPBy(pokemon, (u32)sp50, (u32)sp54, GetItemAttr_PreloadedItemData(itemData, ITEMATTR_HP_RESTORE_PARAM));
                hadEffect = TRUE;
            }
            effectFound = TRUE;
        }
        sp58 = (s32)GetMonData(pokemon, MON_DATA_LEVEL, NULL);
        if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_LEVEL_UP)) {
            if (sp58 < MAX_LEVEL) {
                AddMonData(pokemon, MON_DATA_EXPERIENCE, (int)CalcMonExpToNextLevel(pokemon));
                CalcMonLevelAndStats(pokemon);
                if (sp50 == 0) {
                    sp5C = (s32)GetMonData(pokemon, MON_DATA_MAXHP, NULL);
                    RestoreMonHPBy(pokemon, (u32)sp50, (u32)sp5C, (u32)(sp5C - sp54));
                }
                hadEffect = TRUE;
            }
            effectFound = TRUE;
        }
    }
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_EVOLVE)) {
        effectFound = TRUE;
    }
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PP_UP)) {
        if (BoostMonMovePpUpBy(pokemon, moveIdx, 1) == TRUE) {
            hadEffect = TRUE;
        }
        effectFound = TRUE;
    } else if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PP_MAX)) {
        if (BoostMonMovePpUpBy(pokemon, moveIdx, 3) == TRUE) {
            hadEffect = TRUE;
        }
        effectFound = TRUE;
    }
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PP_RESTORE)) {
        if (MonMoveRestorePP(pokemon, moveIdx, (s32)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PP_RESTORE_PARAM)) == 1) {
            hadEffect = TRUE;
        }
        effectFound = TRUE;
    } else if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PP_RESTORE_ALL)) {
        sp50 = 0;
        for (; sp50 < MAX_MON_MOVES; sp50++) {
            if (MonMoveRestorePP(pokemon, sp50, (s32)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PP_RESTORE_PARAM)) == 1) {
                hadEffect = TRUE;
            }
        }
        effectFound = TRUE;
    }
    {
        sp50 = (s32)GetMonData(pokemon, MON_DATA_HP_EV, NULL);
        sp54 = (s32)GetMonData(pokemon, MON_DATA_ATK_EV, NULL);
        sp58 = (s32)GetMonData(pokemon, MON_DATA_DEF_EV, NULL);
        sp5C = (s32)GetMonData(pokemon, MON_DATA_SPEED_EV, NULL);
        sp60 = (s32)GetMonData(pokemon, MON_DATA_SPATK_EV, NULL);
        sp64 = (s32)GetMonData(pokemon, MON_DATA_SPDEF_EV, NULL);
        if (GetMonData(pokemon, MON_DATA_SPECIES, NULL) != SPECIES_SHEDINJA && GetItemAttr_PreloadedItemData(itemData, ITEMATTR_HP_EV_UP)) {
            sp6C = (int)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_HP_EV_UP_PARAM);
            sp68 = TryModEV(sp50, sp54 + sp58 + sp5C + sp60 + sp64, sp6C);
            if (sp68 != -1) {
                sp50 = sp68;
                SetMonData(pokemon, MON_DATA_HP_EV, &sp50);
                CalcMonLevelAndStats(pokemon);
                hadEffect = TRUE;
            }
            if (sp6C > 0) {
                effectFound = TRUE;
            }
        }
        if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_ATK_EV_UP)) {
            sp6C = (int)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_ATK_EV_UP_PARAM);
            sp68 = TryModEV(sp54, sp50 + sp58 + sp5C + sp60 + sp64, sp6C);
            if (sp68 != -1) {
                sp54 = sp68;
                SetMonData(pokemon, MON_DATA_ATK_EV, &sp54);
                CalcMonLevelAndStats(pokemon);
                hadEffect = TRUE;
            }
            if (sp6C > 0) {
                effectFound = TRUE;
            }
        }
        if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_DEF_EV_UP)) {
            sp6C = (int)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_DEF_EV_UP_PARAM);
            sp68 = TryModEV(sp58, sp50 + sp54 + sp5C + sp60 + sp64, sp6C);
            if (sp68 != -1) {
                sp58 = sp68;
                SetMonData(pokemon, MON_DATA_DEF_EV, &sp58);
                CalcMonLevelAndStats(pokemon);
                hadEffect = TRUE;
            }
            if (sp6C > 0) {
                effectFound = TRUE;
            }
        }
        if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_SPEED_EV_UP)) {
            sp6C = (int)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_SPEED_EV_UP_PARAM);
            sp68 = TryModEV(sp5C, sp50 + sp54 + sp58 + sp60 + sp64, sp6C);
            if (sp68 != -1) {
                sp5C = sp68;
                SetMonData(pokemon, MON_DATA_SPEED_EV, &sp5C);
                CalcMonLevelAndStats(pokemon);
                hadEffect = TRUE;
            }
            if (sp6C > 0) {
                effectFound = TRUE;
            }
        }
        if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_SPATK_EV_UP)) {
            sp6C = (int)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_SPATK_EV_UP_PARAM);
            sp68 = TryModEV(sp60, sp50 + sp54 + sp58 + sp5C + sp64, sp6C);
            if (sp68 != -1) {
                sp60 = sp68;
                SetMonData(pokemon, MON_DATA_SPATK_EV, &sp60);
                CalcMonLevelAndStats(pokemon);
                hadEffect = TRUE;
            }
            if (sp6C > 0) {
                effectFound = TRUE;
            }
        }
        if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_SPDEF_EV_UP)) {
            sp6C = (int)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_SPDEF_EV_UP_PARAM);
            sp68 = TryModEV(sp64, sp50 + sp54 + sp58 + sp5C + sp60, sp6C);
            if (sp68 != -1) {
                sp64 = sp68;
                SetMonData(pokemon, MON_DATA_SPDEF_EV, &sp64);
                CalcMonLevelAndStats(pokemon);
                hadEffect = TRUE;
            }
            if (sp6C > 0) {
                effectFound = TRUE;
            }
        }
    }
    if (hadEffect == FALSE && effectFound == TRUE) {
        FreeToHeap(itemData);
        return FALSE;
    }
    {
        sp50 = (s32)GetMonData(pokemon, MON_DATA_FRIENDSHIP, NULL);
        if (sp50 < 100) {
            if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_FRIENDSHIP_MOD_LO)) {
                DoItemFriendshipMod(pokemon, sp50, (s32)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_FRIENDSHIP_MOD_LO_PARAM), location, heapId);
                FreeToHeap(itemData);
                return hadEffect;
            }
        } else if (sp50 >= 100 && sp50 < 200) {
            if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_FRIENDSHIP_MOD_MED)) {
                DoItemFriendshipMod(pokemon, sp50, (s32)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_FRIENDSHIP_MOD_MED_PARAM), location, heapId);
                FreeToHeap(itemData);
                return hadEffect;
            }
        } else if (sp50 >= 200 && sp50 <= 255) {
            if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_FRIENDSHIP_MOD_HI)) {
                DoItemFriendshipMod(pokemon, sp50, (s32)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_FRIENDSHIP_MOD_HI_PARAM), location, heapId);
                FreeToHeap(itemData);
                return hadEffect;
            }
        }
    }
    FreeToHeap(itemData);
    return hadEffect;
}
#undef sp6C
#undef sp68
#undef sp64
#undef sp60
#undef sp5C
#undef sp58
#undef sp54
#undef sp50

BOOL UseItemOnMonInParty(struct Party *party, u16 itemId, s32 partyIdx, s32 moveIdx, u16 location, HeapID heapId) {
    struct Pokemon *pokemon = Party_GetMonByIndex(party, partyIdx);
    return UseItemOnPokemon(pokemon, itemId, moveIdx, location, heapId);
}

u8 MonMoveCanRestorePP(struct Pokemon *pokemon, s32 moveIdx) {
    u16 move_id = (u16)GetMonData(pokemon, MON_DATA_MOVE1 + moveIdx, NULL);
    if (move_id == MOVE_NONE) {
        return FALSE;
    }
    u8 pp   = (u8)GetMonData(pokemon, MON_DATA_MOVE1PP + moveIdx, NULL);
    u8 ppUp = (u8)GetMonData(pokemon, MON_DATA_MOVE1PPUP + moveIdx, NULL);
    return (u8)(pp < WazaGetMaxPp(move_id, ppUp));
}

BOOL MonMoveRestorePP(struct Pokemon *pokemon, s32 moveIdx, s32 ppRestore) {
    u16 move_id;
    u8 pp;
    u8 maxPp;
    s32 ppAttr;
    s32 ppUpAttr;

    move_id = (u16)GetMonData(pokemon, MON_DATA_MOVE1 + moveIdx, NULL);
    if (move_id == MOVE_NONE) {
        return FALSE;
    }
    ppAttr   = MON_DATA_MOVE1PP + moveIdx;
    pp       = (u8)GetMonData(pokemon, ppAttr, NULL);
    ppUpAttr = MON_DATA_MOVE1PPUP + moveIdx;
    maxPp    = WazaGetMaxPp(move_id, (u8)GetMonData(pokemon, ppUpAttr, NULL));
    if (pp < maxPp) {
        if (ppRestore == PP_RESTORE_ALL) {
            pp = maxPp;
        } else {
            pp += ppRestore;
            if (pp > maxPp) {
                pp = maxPp;
            }
        }
        SetMonData(pokemon, ppAttr, &pp);
        return TRUE;
    }
    return FALSE;
}

BOOL BoostMonMovePpUpBy(struct Pokemon *pokemon, s32 moveIdx, u32 nPpUp) {
    u16 move;
    u8 pp, ppUp, maxPp, newMaxPp;
    s32 ppUpAttr;
    s32 ppAttr;

    ppUpAttr = MON_DATA_MOVE1PPUP + moveIdx;
    ppUp     = (u8)GetMonData(pokemon, ppUpAttr, NULL);
    if (ppUp == 3) {
        return FALSE;
    }
    move = (u16)GetMonData(pokemon, MON_DATA_MOVE1 + moveIdx, NULL);
    if (WazaGetMaxPp(move, 0) < 5) {
        return FALSE;
    }
    ppAttr = MON_DATA_MOVE1PP + moveIdx;
    pp     = (u8)GetMonData(pokemon, ppAttr, NULL);
    maxPp  = WazaGetMaxPp(move, ppUp);
    if (ppUp + nPpUp > 3) {
        ppUp = 3;
    } else {
        ppUp = (u8)(ppUp + nPpUp);
    }
    newMaxPp = WazaGetMaxPp(move, ppUp);
    pp       = (u8)(pp + newMaxPp - maxPp);
    SetMonData(pokemon, ppUpAttr, &ppUp);
    SetMonData(pokemon, ppAttr, &pp);
    return TRUE;
}

void RestoreMonHPBy(struct Pokemon *pokemon, u32 hp, u32 maxHp, u32 restoration) {
    if (maxHp == 1) {
        restoration = 1;
    } else if (restoration == HP_RESTORE_ALL) {
        restoration = maxHp;
    } else if (restoration == HP_RESTORE_HALF) {
        restoration = maxHp / 2;
    } else if (restoration == HP_RESTORE_QTR) {
        restoration = maxHp / 4;
    }
    if (hp + restoration > maxHp) {
        hp = maxHp;
    } else {
        hp = hp + restoration;
    }
    SetMonData(pokemon, MON_DATA_HP, &hp);
}

s32 TryModEV(s32 ev, s32 evSum, s32 by) {
    if (ev == 0 && by < 0) {
        return -1;
    }
    if (ev >= MAX_EV && by > 0) {
        return -1;
    }
    if (ev + evSum >= MAX_EV_SUM && by > 0) {
        return -1;
    }
    ev += by;
    if (ev > MAX_EV) {
        ev = MAX_EV;
    } else if (ev < 0) {
        ev = 0;
    }
    if (ev + evSum > MAX_EV_SUM) {
        ev = MAX_EV_SUM - evSum;
    }
    return ev;
}

BOOL CanItemModFriendship(struct Pokemon *pokemon, struct ItemData *itemData) {
    s32 friendship = (s32)GetMonData(pokemon, MON_DATA_FRIENDSHIP, NULL);
    if (friendship >= 255) {
        return FALSE;
    }
    if (friendship < 100) {
        return GetItemAttr_PreloadedItemData(itemData, ITEMATTR_FRIENDSHIP_MOD_LO) && (s32)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_FRIENDSHIP_MOD_LO_PARAM) > 0;
    }
    if (friendship >= 100 && friendship < 200) {
        return GetItemAttr_PreloadedItemData(itemData, ITEMATTR_FRIENDSHIP_MOD_MED) && (s32)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_FRIENDSHIP_MOD_MED_PARAM) > 0;
    }
    if (friendship >= 200 && friendship < 255) {
        return GetItemAttr_PreloadedItemData(itemData, ITEMATTR_FRIENDSHIP_MOD_HI) && (s32)GetItemAttr_PreloadedItemData(itemData, ITEMATTR_FRIENDSHIP_MOD_HI_PARAM) > 0;
    }
    return FALSE;
}

BOOL DoItemFriendshipMod(struct Pokemon *pokemon, s32 friendship, s32 mod, u16 location, HeapID heapId) {
    if (friendship == 255 && mod > 0) {
        return FALSE;
    }
    if (friendship == 0 && mod < 0) {
        return FALSE;
    }
    if (mod > 0) {
        if (GetItemAttr((u16)GetMonData(pokemon, MON_DATA_HELD_ITEM, NULL), ITEMATTR_HOLD_EFFECT, heapId) == HOLD_EFFECT_FRIENDSHIP_UP) {
            mod = mod * 150 / 100;
        }
        if (GetMonData(pokemon, MON_DATA_POKEBALL, NULL) == ITEM_LUXURY_BALL) {
            mod++;
        }
        if (location == GetMonData(pokemon, MON_DATA_EGG_MET_LOCATION, NULL)) {
            mod++;
        }
    }
    mod += friendship;
    if (mod > 255) {
        mod = 255;
    }
    if (mod < 0) {
        mod = 0;
    }
    SetMonData(pokemon, MON_DATA_FRIENDSHIP, &mod);
    return TRUE;
}

void HealParty(struct Party *party) {
    u32 sp8;
    s32 nmons;
    s32 i;
    s32 j;

    nmons = Party_GetCount(party);
    for (i = 0; i < nmons; i++) {
        struct Pokemon *pokemon = Party_GetMonByIndex(party, i);
        if (GetMonData(pokemon, MON_DATA_SPECIES_EXISTS, NULL)) {
            sp8 = GetMonData(pokemon, MON_DATA_MAXHP, NULL);
            SetMonData(pokemon, MON_DATA_HP, &sp8);

            sp8 = 0;
            SetMonData(pokemon, MON_DATA_STATUS, &sp8);

            for (j = 0; j < MAX_MON_MOVES; j++) {
                if (MonMoveCanRestorePP(pokemon, j) == 1) {
                    MonMoveRestorePP(pokemon, j, PP_RESTORE_ALL);
                }
            }
        }
    }
}
