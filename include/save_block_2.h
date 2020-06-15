#ifndef POKEDIAMOND_SAVE_BLOCK_2_H
#define POKEDIAMOND_SAVE_BLOCK_2_H

struct SaveBlock2
{
    u16 playerName[OT_NAME_LENGTH + 1];
    u32 playerId;
    u8 filler_14[4];
    u8 gender;
    u8 padding[3];
    // TODO: finish this struct
};

struct String * FUN_020239A0(struct SaveBlock2 *, u32 heap_id);
u32 FUN_020239BC(struct SaveBlock2 *);
u32 FUN_020239CC(struct SaveBlock2 *);

#endif //POKEDIAMOND_SAVE_BLOCK_2_H
