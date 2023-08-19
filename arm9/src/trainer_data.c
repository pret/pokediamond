#include "global.h"
#include "heap.h"
#include "trainer_data.h"
#include "battle_setup.h"
#include "math_util.h"
#include "party.h"
#include "proto.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "constants/trainer_classes.h"
#include "unk_02024E64.h"

// Loads all battle opponents, including multi-battle partner if exists.
void EnemyTrainerSet_Init(BattleSetup *setup, struct SaveData * save, HeapID heapId)
{
    Trainer trdata;
    struct MsgData * msgData;
    u16 * rivalName;
    s32 i;
    struct String * str;

    msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0559_bin, heapId);
    rivalName = GetRivalNamePtr(sub_02024EC0(save));
    for (i = 0; i < 4; i++)
    {
        if (setup->trainerId[i] != 0)
        {
            TrainerData_ReadTrData(setup->trainerId[i], &trdata.data);
            setup->trainers[i] = trdata;
            if (trdata.data.trainerClass == TRAINER_CLASS_PKMN_TRAINER_BARRY)
            {
                CopyU16StringArray(setup->trainers[i].name, rivalName);
            }
            else
            {
                str = NewString_ReadMsgData(msgData, setup->trainerId[i]);
                CopyStringToU16Array(str, setup->trainers[i].name, PLAYER_NAME_LENGTH + 1);
                String_Delete(str);
            }
            CreateNPCTrainerParty(setup, i, heapId);
        }
    }
    setup->flags |= trdata.data.doubleBattle;
    DestroyMsgData(msgData);
}

s32 TrainerData_GetAttr(u32 tr_idx, u32 attr_no)
{
    Trainer trainer;
    s32 ret;

    TrainerData_ReadTrData(tr_idx, &trainer.data);
    switch (attr_no)
    {
    case 0:
        ret = trainer.data.trainerType;
        break;
    case 1:
        ret = trainer.data.trainerClass;
        break;
    case 2:
        ret = trainer.data.unk_2;
        break;
    case 3:
        ret = trainer.data.npoke;
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        attr_no -= 4;
        ret = trainer.data.items[attr_no];
        break;
    case 8:
        ret = (s32)trainer.data.aiFlags;
        break;
    case 9:
        ret = (s32)trainer.data.doubleBattle;
        break;
    }
    return ret; // UB: uninitialized in event of invalid attr
}

// Relevant files:
//   files/poketool/trmsg/trtbl.narc
//   files/poketool/trmsg/trtblofs.narc
//   files/msgdata/msg/narc_0558.txt
// trtbl is a single-member NARC whose entries are two shorts each. The first short
// designates the trainer ID and the second the message ID. They are ordered the same
// as the corresponding msgdata file. All messages for a given trainer are found together,
// however the trainers are not in order in this file. trtblofs gives a pointer into trtbl
// for each trainer. trtblofs is also a single-member NARC whose entries are shorts, one
// per NPC trainer.
BOOL TrainerMessageWithIdPairExists(u32 trainer_idx, u32 msg_id, HeapID heapId)
{
    u16 rdbuf[3];
    struct NARC * trTblNarc;
    BOOL ret = FALSE;
    u32 trTblSize;

    trTblSize = GetNarcMemberSizeByIdPair(NARC_POKETOOL_TRMSG_TRTBL, 0);
    ReadFromNarcMemberByIdPair(&rdbuf[0], NARC_POKETOOL_TRMSG_TRTBLOFS, 0, trainer_idx * 2, 2);
    trTblNarc = NARC_New(NARC_POKETOOL_TRMSG_TRTBL, heapId);
    while (rdbuf[0] != trTblSize)
    {
        NARC_ReadFromMember(trTblNarc, 0, rdbuf[0], 4, &rdbuf[1]);
        if (rdbuf[1] == trainer_idx && rdbuf[2] == msg_id)
        {
            ret = TRUE;
            break;
        }
        if (rdbuf[1] != trainer_idx)
            break;
        rdbuf[0] += 4;
    }
    NARC_Delete(trTblNarc);
    return ret;
}

void GetTrainerMessageByIdPair(u32 trainer_idx, u32 msg_id, struct String * str, HeapID heapId)
{
    u16 rdbuf[3];
    u32 trTblSize;
    struct NARC * trTblNarc;

    trTblSize = GetNarcMemberSizeByIdPair(NARC_POKETOOL_TRMSG_TRTBL, 0);
    ReadFromNarcMemberByIdPair(&rdbuf[0], NARC_POKETOOL_TRMSG_TRTBLOFS, 0, trainer_idx * 2, 2);
    trTblNarc = NARC_New(NARC_POKETOOL_TRMSG_TRTBL, heapId);
    while (rdbuf[0] != trTblSize)
    {
        NARC_ReadFromMember(trTblNarc, 0, rdbuf[0], 4, &rdbuf[1]);
        if (rdbuf[1] == trainer_idx && rdbuf[2] == msg_id)
        {
            ReadMsgData_NewNarc_ExistingString(NARC_MSGDATA_MSG, 558, (u32)(rdbuf[0] / 4), heapId, str);
            break;
        }
        rdbuf[0] += 4;
    }
    NARC_Delete(trTblNarc);
    if (rdbuf[0] == trTblSize)
        String_SetEmpty(str);
}

void TrainerData_ReadTrData(u32 idx, struct TrainerData * dest)
{
    ReadWholeNarcMemberByIdPair(dest, NARC_POKETOOL_TRAINER_TRDATA, (s32)idx);
}

void TrainerData_ReadTrPoke(u32 idx, union TrainerMon * dest)
{
    ReadWholeNarcMemberByIdPair(dest, NARC_POKETOOL_TRAINER_TRPOKE, (s32)idx);
}

const u8 sTrainerClassGenderCountTbl[] = {
    /*TRAINER_CLASS_PKMN_TRAINER_M*/             0,
    /*TRAINER_CLASS_PKMN_TRAINER_F*/             1,
    /*TRAINER_CLASS_YOUNGSTER*/                  0,
    /*TRAINER_CLASS_LASS*/                       1,
    /*TRAINER_CLASS_CAMPER*/                     0,
    /*TRAINER_CLASS_PICNICKER*/                  1,
    /*TRAINER_CLASS_BUG_CATCHER*/                0,
    /*TRAINER_CLASS_AROMA_LADY*/                 1,
    /*TRAINER_CLASS_TWINS*/                      1,
    /*TRAINER_CLASS_HIKER*/                      0,
    /*TRAINER_CLASS_BATTLE_GIRL*/                1,
    /*TRAINER_CLASS_FISHERMAN*/                  0,
    /*TRAINER_CLASS_CYCLIST_M*/                  0,
    /*TRAINER_CLASS_CYCLIST_F*/                  1,
    /*TRAINER_CLASS_BLACK_BELT*/                 0,
    /*TRAINER_CLASS_ARTIST*/                     0,
    /*TRAINER_CLASS_PKMN_BREEDER_M*/             0,
    /*TRAINER_CLASS_PKMN_BREEDER_F*/             1,
    /*TRAINER_CLASS_COWGIRL*/                    1,
    /*TRAINER_CLASS_JOGGER*/                     0,
    /*TRAINER_CLASS_POKEFAN_M*/                  0,
    /*TRAINER_CLASS_POKEFAN_F*/                  1,
    /*TRAINER_CLASS_POKE_KID*/                   1,
    /*TRAINER_CLASS_YOUNG_COUPLE*/               2,
    /*TRAINER_CLASS_ACE_TRAINER_M*/              0,
    /*TRAINER_CLASS_ACE_TRAINER_F*/              1,
    /*TRAINER_CLASS_WAITRESS*/                   1,
    /*TRAINER_CLASS_VETERAN*/                    0,
    /*TRAINER_CLASS_NINJA_BOY*/                  0,
    /*TRAINER_CLASS_DRAGON_TAMER*/               0,
    /*TRAINER_CLASS_BIRD_KEEPER*/                1,
    /*TRAINER_CLASS_DOUBLE_TEAM*/                2,
    /*TRAINER_CLASS_RICH_BOY*/                   0,
    /*TRAINER_CLASS_LADY*/                       1,
    /*TRAINER_CLASS_GENTLEMAN*/                  0,
    /*TRAINER_CLASS_SOCIALITE*/                  1,
    /*TRAINER_CLASS_BEAUTY*/                     1,
    /*TRAINER_CLASS_COLLECTOR*/                  0,
    /*TRAINER_CLASS_POLICEMAN*/                  0,
    /*TRAINER_CLASS_PKMN_RANGER_M*/              0,
    /*TRAINER_CLASS_PKMN_RANGER_F*/              1,
    /*TRAINER_CLASS_SCIENTIST*/                  0,
    /*TRAINER_CLASS_SWIMMER_M*/                  0,
    /*TRAINER_CLASS_SWIMMER_F*/                  1,
    /*TRAINER_CLASS_TUBER_M*/                    0,
    /*TRAINER_CLASS_TUBER_F*/                    1,
    /*TRAINER_CLASS_SAILOR*/                     0,
    /*TRAINER_CLASS_SIS_AND_BRO*/                2,
    /*TRAINER_CLASS_RUIN_MANIAC*/                0,
    /*TRAINER_CLASS_PSYCHIC_M*/                  0,
    /*TRAINER_CLASS_PSYCHIC_F*/                  1,
    /*TRAINER_CLASS_PI*/                         0,
    /*TRAINER_CLASS_GUITARIST*/                  0,
    /*TRAINER_CLASS_ACE_TRAINER_SNOW_M*/         0,
    /*TRAINER_CLASS_ACE_TRAINER_SNOW_F*/         1,
    /*TRAINER_CLASS_SKIER_M*/                    0,
    /*TRAINER_CLASS_SKIER_F*/                    1,
    /*TRAINER_CLASS_ROUGHNECK*/                  0,
    /*TRAINER_CLASS_CLOWN*/                      0,
    /*TRAINER_CLASS_WORKER*/                     0,
    /*TRAINER_CLASS_SCHOOL_KID_M*/               0,
    /*TRAINER_CLASS_SCHOOL_KID_F*/               1,
    /*TRAINER_CLASS_LEADER_ROARK*/               0,
    /*TRAINER_CLASS_PKMN_TRAINER_BARRY*/         0,
    /*TRAINER_CLASS_LEADER_BYRON*/               0,
    /*TRAINER_CLASS_ELITE_FOUR_AARON*/           0,
    /*TRAINER_CLASS_ELITE_FOUR_BERTHA*/          1,
    /*TRAINER_CLASS_ELITE_FOUR_FLINT*/           0,
    /*TRAINER_CLASS_ELITE_FOUR_LUCIEN*/          0,
    /*TRAINER_CLASS_CHAMPION*/                   1,
    /*TRAINER_CLASS_BELLE__PA*/                  2,
    /*TRAINER_CLASS_RANCHER*/                    0,
    /*TRAINER_CLASS_COMMANDER_MARS*/             1,
    /*TRAINER_CLASS_GALACTIC*/                   0,
    /*TRAINER_CLASS_LEADER_GARDENIA*/            1,
    /*TRAINER_CLASS_LEADER_WAKE*/                0,
    /*TRAINER_CLASS_LEADER_MAYLENE*/             1,
    /*TRAINER_CLASS_LEADER_FANTINA*/             1,
    /*TRAINER_CLASS_LEADER_CANDICE*/             1,
    /*TRAINER_CLASS_LEADER_VOLKNER*/             0,
    /*TRAINER_CLASS_PARASOL_LADY*/               1,
    /*TRAINER_CLASS_WAITER*/                     0,
    /*TRAINER_CLASS_INTERVIEWERS*/               2,
    /*TRAINER_CLASS_CAMERAMAN*/                  0,
    /*TRAINER_CLASS_REPORTER*/                   1,
    /*TRAINER_CLASS_IDOL*/                       1,
    /*TRAINER_CLASS_GALACTIC_BOSS*/              0,
    /*TRAINER_CLASS_COMMANDER_JUPITER*/          1,
    /*TRAINER_CLASS_COMMANDER_SATURN*/           1,
    /*TRAINER_CLASS_GALACTIC_F*/                 1,
    /*TRAINER_CLASS_PKMN_TRAINER_CHERYL*/        1,
    /*TRAINER_CLASS_PKMN_TRAINER_RILEY*/         0,
    /*TRAINER_CLASS_PKMN_TRAINER_MARLEY*/        1,
    /*TRAINER_CLASS_PKMN_TRAINER_BUCK*/          0,
    /*TRAINER_CLASS_PKMN_TRAINER_MIRA*/          1,
    /*TRAINER_CLASS_PKMN_TRAINER_LUCAS*/         0,
    /*TRAINER_CLASS_PKMN_TRAINER_DAWN*/          1,
    /*TRAINER_CLASS_TOWER_TYCOON*/               0
};

// Returns 0 for male, 1 for female, 2 for doubles. See above vector.
int TrainerClass_GetGenderOrTrainerCount(int a0)
{
    return sTrainerClassGenderCountTbl[a0];
}

void CreateNPCTrainerParty(BattleSetup *setup, s32 party_id, HeapID heapId)
{
    union TrainerMon * data;
    s32 i;
    s32 j;
    u32 seed_bak;
    struct Pokemon * pokemon;
    struct TrainerMonSpeciesItemMoves * monSpeciesItemMoves;
    struct TrainerMonSpeciesItem * monSpeciesItem;
    struct TrainerMonSpeciesMoves * monSpeciesMoves;
    struct TrainerMonSpecies * monSpecies;
    u32 seed;
    u32 personality;
    u8 iv;
    u32 pid_gender;

    // We abuse the RNG for personality value generation, so back up the overworld
    // state
    seed_bak = GetLCRNGSeed();
    InitPartyWithMaxSize(setup->party[party_id], PARTY_SIZE);
    data = (union TrainerMon *)AllocFromHeap(heapId, sizeof(union TrainerMon) * PARTY_SIZE);
    pokemon = AllocMonZeroed(heapId);
    TrainerData_ReadTrPoke(setup->trainerId[party_id], data);

    // If a Pokemon's gender ratio is 50/50, the generated Pokemon will be the same
    // gender as its trainer. Otherwise, it will assume the more abundant gender
    // according to its species gender ratio. In double battles, the behavior is
    // identical to that of a solitary male opponent.
    pid_gender = (u32)((TrainerClass_GetGenderOrTrainerCount(setup->trainers[party_id].data.trainerClass) == 1) ? 0x78 : 0x88);

    // The trainer types can be more efficiently and expandibly treated as a flag
    // array, with bit 0 being custom moveset and bit 1 being held item.
    // Nintendo didn't do it that way, instead using a switch statement and a lot
    // of code duplication. This has been the case since the 2nd generation games.
    switch (setup->trainers[party_id].data.trainerType)
    {
    case TRTYPE_MON:
    {
        monSpecies = &data->species;
        for (i = 0; i < setup->trainers[party_id].data.npoke; i++)
        {
            // Generate personality by seeding with a value based on the difficulty,
            // level, species, and opponent ID. Roll the RNG N times, where N is
            // the index of its trainer class. Finally, left shift the 16-bit
            // pseudorandom value and add the gender selector.
            // This guarantees that NPC trainers' Pokemon are generated in a
            // consistent manner between attempts.
            seed = monSpecies[i].difficulty + monSpecies[i].level + monSpecies[i].species + setup->trainerId[party_id];
            SetLCRNGSeed(seed);
            for (j = 0; j < setup->trainers[party_id].data.trainerClass; j++)
            {
                seed = LCRandom();
            }
            personality = (seed << 8);
            personality += pid_gender;

            // Difficulty is a number between 0 and 250 which directly corresponds
            // to the (uniform) IV spread of the generated Pokemon.
            iv = (u8)((monSpecies[i].difficulty * 31) / 255);
            CreateMon(pokemon, monSpecies[i].species, monSpecies[i].level, iv, 1, (s32)personality, 2, 0);

            // If you were treating the trainer type as a bitfield, you'd put the
            // checks for held item and moves here. You'd also treat the trpoke
            // data as a flat u16 array rather than an array of fixed-width structs.
            Party_AddMon(setup->party[party_id], pokemon);
        }
        break;
    }
    case TRTYPE_MON_MOVES:
    {
        monSpeciesMoves = &data->species_moves;
        for (i = 0; i < setup->trainers[party_id].data.npoke; i++)
        {
            seed = monSpeciesMoves[i].difficulty + monSpeciesMoves[i].level + monSpeciesMoves[i].species + setup->trainerId[party_id];
            SetLCRNGSeed(seed);
            for (j = 0; j < setup->trainers[party_id].data.trainerClass; j++)
            {
                seed = LCRandom();
            }
            personality = (seed << 8);
            personality += pid_gender;
            iv = (u8)((monSpeciesMoves[i].difficulty * 31) / 255);
            CreateMon(pokemon, monSpeciesMoves[i].species, monSpeciesMoves[i].level, iv, 1, (s32)personality, 2, 0);
            for (j = 0; j < 4; j++)
            {
                MonSetMoveInSlot(pokemon, monSpeciesMoves[i].moves[j], (u8)j);
            }
            Party_AddMon(setup->party[party_id], pokemon);
        }
        break;
    }
    case TRTYPE_MON_ITEM:
    {
        monSpeciesItem = &data->species_item;
        for (i = 0; i < setup->trainers[party_id].data.npoke; i++)
        {
            seed = monSpeciesItem[i].difficulty + monSpeciesItem[i].level + monSpeciesItem[i].species + setup->trainerId[party_id];
            SetLCRNGSeed(seed);
            for (j = 0; j < setup->trainers[party_id].data.trainerClass; j++)
            {
                seed = LCRandom();
            }
            personality = (seed << 8);
            personality += pid_gender;
            iv = (u8)((monSpeciesItem[i].difficulty * 31) / 255);
            CreateMon(pokemon, monSpeciesItem[i].species, monSpeciesItem[i].level, iv, 1, (s32)personality, 2, 0);
            SetMonData(pokemon, MON_DATA_HELD_ITEM, &monSpeciesItem[i].item);
            Party_AddMon(setup->party[party_id], pokemon);
        }
        break;
    }
    case TRTYPE_MON_ITEM_MOVES:
    {
        monSpeciesItemMoves = &data->species_item_moves;
        for (i = 0; i < setup->trainers[party_id].data.npoke; i++)
        {
            seed = monSpeciesItemMoves[i].difficulty + monSpeciesItemMoves[i].level + monSpeciesItemMoves[i].species + setup->trainerId[party_id];
            SetLCRNGSeed(seed);
            for (j = 0; j < setup->trainers[party_id].data.trainerClass; j++)
            {
                seed = LCRandom();
            }
            personality = (seed << 8);
            personality += pid_gender;
            iv = (u8)((monSpeciesItemMoves[i].difficulty * 31) / 255);
            CreateMon(pokemon, monSpeciesItemMoves[i].species, monSpeciesItemMoves[i].level, iv, 1, (s32)personality, 2, 0);
            SetMonData(pokemon, MON_DATA_HELD_ITEM, &monSpeciesItemMoves[i].item);
            for (j = 0; j < 4; j++)
            {
                MonSetMoveInSlot(pokemon, monSpeciesItemMoves[i].moves[j], (u8)j);
            }
            Party_AddMon(setup->party[party_id], pokemon);
        }
        break;
    }
    }
    FreeToHeap(data);
    FreeToHeap(pokemon);
    SetLCRNGSeed(seed_bak);
}
