#ifndef POKEDIAMOND_UNK_020377F0_H
#define POKEDIAMOND_UNK_020377F0_H

struct Options;
struct PlayerParty;

// This struct gets created from a bunch of places, not just 0x02037CF0. This was
// just the first place I (tgsm) found it being created.
struct UnkStruct_02037CF0
{
    struct PlayerParty* party;
    struct Options* options;
    u16* name_buf;
    u32 trainer_id;
    u8 gender;
    u8 unk11;
    u8 unk12;
    u8 party_count;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 padding;
    u16 unk18;
    u8 padding2[0x2];
    BOOL has_national_dex;
    u8 padding3[0xC];
    BOOL unk2C;
};

#endif
