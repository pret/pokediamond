#ifndef POKEDIAMOND_USE_ITEM_ON_MON_H
#define POKEDIAMOND_USE_ITEM_ON_MON_H

BOOL CanUseItemOnPokemon(struct Pokemon * pokemon, u16 itemId, s32 moveId, u32 heap_id);
BOOL CanUseItemOnMonInParty(struct PlayerParty * party, u16 itemId, s32 partyIdx, s32 moveIdx, u32 heap_id);
BOOL UseItemOnPokemon(struct Pokemon * pokemon, u16 itemId, s32 moveIdx, u16 location, u32 heap_id);
BOOL UseItemOnMonInParty(struct PlayerParty * party, u16 itemId, s32 partyIdx, s32 moveIdx, u16 location, u32 heap_id);
u8 MonMoveCanRestorePP(struct Pokemon * pokemon, s32 moveIdx);
BOOL MonMoveRestorePP(struct Pokemon * pokemon, s32 moveIdx, s32 ppRestore);
BOOL BoostMonMovePpUpBy(struct Pokemon * pokemon, s32 moveIdx, u32 nPpUp);
void RestoreMonHPBy(struct Pokemon * pokemon, u32 hp, u32 maxHp, u32 restoration);
s32 TryModEV(s32 ev, s32 evSum, s32 by);
BOOL CanItemModFriendship(struct Pokemon * pokemon, struct ItemData * itemData);
BOOL DoItemFriendshipMod(struct Pokemon * pokemon, s32 friendship, s32 mod, u16 location, u32 heap_id);
void HealParty(struct PlayerParty * party);

#endif //POKEDIAMOND_USE_ITEM_ON_MON_H
