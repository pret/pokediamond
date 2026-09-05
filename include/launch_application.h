#ifndef POKEDIAMOND_LAUNCH_APPLICATION_H
#define POKEDIAMOND_LAUNCH_APPLICATION_H

#include "task.h"

// this file likely has to do with scrcmd apps.

struct Options;
struct Party;

struct Bag;
struct BoxPokemon;
struct Mail;
struct PlayerProfile;
struct FieldMoveCheckData;

// Arguments for the party menu application.
typedef struct PartyMenuArgs {
    struct Party *party;
    struct Bag *bag;
    struct Mail *mailbox;
    struct Options *options;
    void *unk_10;
    void *linkBattleRuleset;
    struct FieldMoveCheckData *fieldMoveCheckData;
    FieldSystem *fieldSystem;
    u8 context;
    u8 unk_21;
    u8 partySlot;
    u8 selectedAction;
    u16 itemId;
    u16 moveId;
    u8 selectedMoveIdx;
    u8 unk_29;
    u8 contestStat;
    u8 contestLevel;
    u8 selectedOrder[6];
    u8 minMonsToSelect : 4;
    u8 maxMonsToSelect : 4;
    u8 maxLevel;
    int levelUpMoveSearchState;
    u16 species;
    int evoMethod;
} PartyMenuArgs;

// Arguments for the Pokemon summary application.
typedef struct PokemonSummaryArgs {
    struct Party *party;
    struct Options *options;
    u16 *name_buf;
    u32 trainer_id;
    u8 gender;
    u8 unk11;
    u8 unk12;
    u8 partyCount;
    u8 partySlot;
    u8 unk15;
    u8 unk16;
    u8 padding17;
    u16 moveToLearn;
    u8 padding1A[0x2];
    BOOL natDexEnabled;
    void *ribbons;
    u32 unk24;
    u32 unk28;
    int unk2C;
} PokemonSummaryArgs;

enum TradeType {
    TRADE_TYPE_NORMAL = 1,
    TRADE_TYPE_SEND_ONLY,
    TRADE_TYPE_RECEIVE_ONLY = 4,
};

enum TradeBackground {
    TRADE_BACKGROUND_DAY = 0,
    TRADE_BACKGROUND_EVENING,
    TRADE_BACKGROUND_NIGHT,
    TRADE_BACKGROUND_WIFI,
};

// Arguments for the trade animation application (overlay 81).
// Shared by the wireless trade task and the in-game (NPC) trade task.
typedef struct TradeAnimationTemplate {
    struct BoxPokemon *sendingPokemon;
    struct BoxPokemon *receivingPokemon;
    struct PlayerProfile *otherTrainer;
    enum TradeBackground background;
    enum TradeType tradeType;
    struct Options *options;
} TradeAnimationTemplate;

enum NamingScreenType {
    NAMINGSCREEN_PLAYER,
    NAMINGSCREEN_POKEMON,
    NAMINGSCREEN_BOX,
    NAMINGSCREEN_RIVAL,
    NAMINGSCREEN_GROUP = 5,
    NAMINGSCREEN_SHAYMIN_ROCK = 6,
};

void CreateNamingScreen(TaskManager *taskManager, enum NamingScreenType type, s32 param2, s32 maxLen, s32 initPos, const u16 *defaultStr, u16 *retVar);

#endif
