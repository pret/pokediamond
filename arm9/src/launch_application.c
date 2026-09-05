#include "launch_application.h"

#include "global.h"

#include "MI_memory.h"
#include "constants/items.h"
#include "constants/pokemon.h"

#include "bag.h"
#include "bag_view.h"
#include "coins.h"
#include "error_handling.h"
#include "field_move.h"
#include "field_system.h"
#include "gf_rtc.h"
#include "heap.h"
#include "mail.h"
#include "math_util.h"
#include "options.h"
#include "overlay_manager.h"
#include "party.h"
#include "player_avatar.h"
#include "player_data.h"
#include "pokedex.h"
#include "pokemon.h"
#include "poketch.h"
#include "save.h"
#include "save_system_info.h"
#include "save_vars_flags.h"
#include "string16.h"
#include "task.h"
#include "unk_02022504.h"
#include "unk_02024E64.h"
#include "unk_02029FB0.h"
#include "unk_0202A1E0.h"
#include "unk_0202ABBC.h"
#include "unk_020286F8.h"
#include "unk_020337E8.h"
#include "field_transition.h"
#include "unk_0204B0A0.h"
#include "unk_0206BB28.h"

// Arguments for the naming screen application (overlay 17).
typedef struct NamingScreenArgs {
    u32 kind;
    u8 unk04[0x4];
    u32 monForm;
    u8 unk0C[0x4];
    u32 monGender;
    u32 noInput;
    struct String *nameInputString;
    u16 nameInputFlat[1];
} NamingScreenArgs;

typedef struct NamingScreenData {
    u32 state;
    u32 partyIdx;
    u16 *retVar;
    NamingScreenArgs *args;
    struct String *unk10;
} NamingScreenData;

typedef struct EasyChatTaskData {
    u16 *unk00;
    u16 *unk04;
    u16 *unk08;
    void *easyChat;
} EasyChatTaskData;

// Arguments for the accessory portrait application (overlay 17).
typedef struct AccessoryPortraitArgs {
    Pokemon *mon;
    void *unk04;
    void *fashionCase;
    Options *options;
    GameStats *gameStats;
    PlayerProfile *profile;
    u32 *unk18;
    u32 unk1C;
} AccessoryPortraitArgs;

typedef struct AccessoryPortraitTaskData {
    u32 state;
    u16 *retVar;
    u32 unk08;
    AccessoryPortraitArgs *args;
} AccessoryPortraitTaskData;

typedef struct UnionRoomBattleSelectData {
    enum HeapID heapID;
    PartyMenuArgs *partyMenuArgs;
    PokemonSummaryArgs *summaryArgs;
} UnionRoomBattleSelectData;

typedef struct WirelessTradeSelectMonArgs {
    FieldSystem *fieldSystem;
    PlayerProfile *profile;
    Party *party;
    void *palPad;
    SaveData *saveData;
    void *unk14;
    Options *options;
    u32 *unk1C;
    GameStats *gameStats;
    Pokedex *pokedex;
    u32 tradeConfirmed;
    u32 partySlot;
    BOOL natDexEnabled;
    u32 tradeCount;
    PlayerProfile *partnerProfile;
    Pokemon *sentMon;
    Pokemon *receivedMon;
} WirelessTradeSelectMonArgs;

typedef struct WirelessTradeData {
    u32 state;
    WirelessTradeSelectMonArgs selectMon;
    TradeAnimationTemplate tradeSequence;
    void *evolutionTaskData;
    u32 unk64;
} WirelessTradeData;

typedef struct SlotMachineData {
    u32 coins;
    s64 startTime;
    void *args;
    u32 unk10;
    GameStats *gameStats;
    s32 unk18;
    u32 frame;
} SlotMachineData;

typedef struct HatchEggArgs {
    Pokemon *mon;
    Options *options;
    PlayerProfile *profile;
    u16 bgm;
} HatchEggArgs;

extern SaveData *FieldSystem_GetSaveData(FieldSystem *fieldSystem);
extern BOOL ov11_0222D5C0(void);

extern BOOL ov15_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov15_021D7558(struct OverlayManager *manager, u32 *status);
extern BOOL ov15_021D7608(struct OverlayManager *manager, u32 *status);
extern BOOL ov16_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov16_021D7588(struct OverlayManager *manager, u32 *status);
extern BOOL ov16_021D7614(struct OverlayManager *manager, u32 *status);
extern BOOL ov17_021D83E4(struct OverlayManager *manager, u32 *status);
extern BOOL ov17_021D84F0(struct OverlayManager *manager, u32 *status);
extern BOOL ov17_021D8738(struct OverlayManager *manager, u32 *status);
extern BOOL ov17_021DDB58(struct OverlayManager *manager, u32 *status);
extern BOOL ov17_021DDC30(struct OverlayManager *manager, u32 *status);
extern BOOL ov17_021DDCF4(struct OverlayManager *manager, u32 *status);
extern BOOL ov53_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov53_021D7654(struct OverlayManager *manager, u32 *status);
extern BOOL ov53_021D7764(struct OverlayManager *manager, u32 *status);
extern BOOL ov54_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov54_021D764C(struct OverlayManager *manager, u32 *status);
extern BOOL ov54_021D7740(struct OverlayManager *manager, u32 *status);
extern BOOL ov55_021D756C(struct OverlayManager *manager, u32 *status);
extern BOOL ov55_021D7614(struct OverlayManager *manager, u32 *status);
extern BOOL ov55_021D76BC(struct OverlayManager *manager, u32 *status);
extern BOOL ov55_021D77AC(struct OverlayManager *manager, u32 *status);
extern BOOL ov57_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov57_021D7714(struct OverlayManager *manager, u32 *status);
extern BOOL ov57_021D7944(struct OverlayManager *manager, u32 *status);
extern BOOL ov58_021D9A20(struct OverlayManager *manager, u32 *status);
extern BOOL ov58_021D9B8C(struct OverlayManager *manager, u32 *status);
extern BOOL ov58_021D9BF0(struct OverlayManager *manager, u32 *status);
extern BOOL ov60_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov60_021D75B0(struct OverlayManager *manager, u32 *status);
extern BOOL ov60_021D76B8(struct OverlayManager *manager, u32 *status);
extern BOOL ov64_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov64_021D7640(struct OverlayManager *manager, u32 *status);
extern BOOL ov64_021D76F4(struct OverlayManager *manager, u32 *status);
extern BOOL ov66_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov66_021D7538(struct OverlayManager *manager, u32 *status);
extern BOOL ov66_021D75B0(struct OverlayManager *manager, u32 *status);
extern BOOL ov67_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov67_021D75D0(struct OverlayManager *manager, u32 *status);
extern BOOL ov67_021D7624(struct OverlayManager *manager, u32 *status);
extern BOOL ov68_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov68_021D75D8(struct OverlayManager *manager, u32 *status);
extern BOOL ov68_021D762C(struct OverlayManager *manager, u32 *status);
extern BOOL ov70_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov70_021D755C(struct OverlayManager *manager, u32 *status);
extern BOOL ov70_021D758C(struct OverlayManager *manager, u32 *status);
extern BOOL ov71_0222D5C0(struct OverlayManager *manager, u32 *status);
extern BOOL ov71_0222D9C8(struct OverlayManager *manager, u32 *status);
extern BOOL ov71_0222E438(struct OverlayManager *manager, u32 *status);
extern BOOL ov74_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov74_021D7540(struct OverlayManager *manager, u32 *status);
extern BOOL ov74_021D755C(struct OverlayManager *manager, u32 *status);
extern BOOL ov75_021E6BA0(struct OverlayManager *manager, u32 *status);
extern BOOL ov75_021E6D6C(struct OverlayManager *manager, u32 *status);
extern BOOL ov75_021E6F00(struct OverlayManager *manager, u32 *status);
extern BOOL ov76_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov76_021D7568(struct OverlayManager *manager, u32 *status);
extern BOOL ov76_021D761C(struct OverlayManager *manager, u32 *status);
extern BOOL ov77_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov77_021D7604(struct OverlayManager *manager, u32 *status);
extern BOOL ov77_021D7BAC(struct OverlayManager *manager, u32 *status);
extern BOOL ov78_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov78_021D75D0(struct OverlayManager *manager, u32 *status);
extern BOOL ov78_021D76B8(struct OverlayManager *manager, u32 *status);
extern BOOL ov80_0222DFD0(struct OverlayManager *manager, u32 *status);
extern BOOL ov80_0222E134(struct OverlayManager *manager, u32 *status);
extern BOOL ov80_0222E25C(struct OverlayManager *manager, u32 *status);
extern BOOL ov81_02237E40(struct OverlayManager *manager, u32 *status);
extern BOOL ov81_02238004(struct OverlayManager *manager, u32 *status);
extern BOOL ov81_02238064(struct OverlayManager *manager, u32 *status);
extern BOOL ov82_0222DA34(struct OverlayManager *manager, u32 *status);
extern BOOL ov82_0222DB7C(struct OverlayManager *manager, u32 *status);
extern BOOL ov82_0222DC50(struct OverlayManager *manager, u32 *status);
extern BOOL ov84_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov84_021D76A4(struct OverlayManager *manager, u32 *status);
extern BOOL ov84_021D7748(struct OverlayManager *manager, u32 *status);
extern BOOL ov85_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov85_021D75A0(struct OverlayManager *manager, u32 *status);
extern BOOL ov85_021D7644(struct OverlayManager *manager, u32 *status);
extern BOOL ov86_021D74E0(struct OverlayManager *manager, u32 *status);
extern BOOL ov86_021D758C(struct OverlayManager *manager, u32 *status);
extern BOOL ov86_021D76B0(struct OverlayManager *manager, u32 *status);

extern BOOL StoragePC_Overlay_Init(struct OverlayManager *manager, u32 *status);
extern BOOL StoragePC_Overlay_Run(struct OverlayManager *manager, u32 *status);
extern BOOL StoragePC_Overlay_Teardown(struct OverlayManager *manager, u32 *status);
extern BOOL HOF_OverlayInit(struct OverlayManager *manager, u32 *status);
extern BOOL HOF_OverlayRun(struct OverlayManager *manager, u32 *status);
extern BOOL HOF_OverlayTeardown(struct OverlayManager *manager, u32 *status);

extern const u8 UNK_020F2A9C[];
extern OverlayManagerTemplate UNK_020F96DC;
extern OverlayManagerTemplate UNK_020FA5FC;
extern OverlayManagerTemplate UNK_020FA6E8;
extern OverlayManagerTemplate UNK_020FCAC8;
extern OverlayManagerTemplate UNK_020FD1B0;

extern void sub_020527D8(u32 a0);
extern void *sub_0202A918(SaveData *save);
extern void *sub_02079C70(SaveData *save);
extern void sub_0207B000(PokemonSummaryArgs *args, const u8 *order);
extern void sub_0207C2A4(PokemonSummaryArgs *args, PlayerProfile *profile);
extern void *sub_02085338(u8 a0, u8 a1, SaveData *save, enum HeapID heapID);
extern void sub_020853A8(void *easyChat);
extern void sub_020853B0(void *easyChat, u16 a1);
extern void sub_020853B4(void *easyChat, u16 a1, u16 a2);
extern u8 sub_020853E4(void *easyChat);
extern u8 sub_020853E8(void *easyChat);
extern u16 sub_020853EC(void *easyChat);
extern void sub_020853F0(void *easyChat, u16 *a1);
extern void *sub_020854E0(SaveData *save, u32 a1, u32 a2, u32 a3, enum HeapID heapID);
extern void *sub_02085538(SaveData *save, u32 a1, u32 a2, u32 a3);
extern void *sub_02085578(SaveData *save, u32 a1, u32 a2);
extern void *sub_020855B0(SaveData *save, u32 a1, u32 a2);
extern void *sub_02087D00(SaveData *save, u32 a1);
extern void *Save_LocalFieldData_Get(SaveData *save);
extern void sub_02034E0C(void *localFieldData);
extern void TownMap_Init(FieldSystem *fieldSystem, void *args, u32 a2);
extern void *Save_FashionData_Get(SaveData *save);
extern void *Save_FashionData_GetFashionCase(void *fashionData);
extern void *sub_02027008(void *fashionData, u32 a1);
extern u32 sub_02033590(void);
extern void *sub_02029AFC(SaveData *save);
extern void *sub_02029ABC(SaveData *save);
extern void *sub_020286EC(SaveData *save);
extern void *sub_02028228(void *a0);
extern Pokemon *ov05_021ED49C(Party *party);
extern void sub_020613CC(FieldSystem *fieldSystem, Pokemon *mon);
extern u16 FieldSystem_GetOverriddenMusicId(FieldSystem *fieldSystem, u32 mapId);
extern void sub_020863DC(TaskManager *taskManager, HatchEggArgs *args);
extern void sub_02061A8C(FieldSystem *fieldSystem, u32 a1, u32 a2, s32 a3);
extern s32 sub_0205F6C8(void *varsFlags);
extern void sub_0205F6D8(void *varsFlags, u16 a1);
extern NamingScreenArgs *sub_02077A84(enum HeapID heapID, u32 kind, u32 species, u32 maxLen, Options *options);
extern void sub_02077AC4(NamingScreenArgs *args);
extern BOOL ov06_0224D79C(void *a0);
extern void ov06_0224D76C(void *a0);
extern void *ov06_0224D70C(u32 a0, SaveData *save, BgConfig *bgConfig);
extern BoxPokemon *sub_020690E4(Pokemon *mon);
extern u32 sub_020690C4(void);
extern void *sub_0206C700(void *a0, Pokemon *mon, u16 species, Options *options, void *a4, Pokedex *pokedex, Bag *bag, GameStats *gameStats, void *poketch, u32 evoMethod, u32 a10, enum HeapID heapID);
extern BOOL sub_0206C91C(void *evolutionTaskData);
extern void sub_0206C92C(void *evolutionTaskData);

BOOL ApplicationInit_Battle(struct OverlayManager *manager, u32 *status);
BOOL ApplicationMain_Battle(struct OverlayManager *manager, u32 *status);
BOOL ApplicationExit_Battle(struct OverlayManager *manager, u32 *status);
void FieldSystem_StartBattleProcess(FieldSystem *fieldSystem, void *data);
BagView *FieldSystem_OpenBag(FieldSystem *fieldSystem, void *itemUseCtx);
BagView *FieldSystem_CreateBagContext(FieldSystem *fieldSystem, u32 pocketType);
u16 BagContext_GetSelectedItem(BagView *bagView);
void FieldSystem_OpenSummaryScreen(FieldSystem *fieldSystem, void *data);
PartyMenuArgs *FieldSystem_OpenPartyMenu(FieldSystem *fieldSystem, FieldMoveCheckData *fieldMoveCheckData, u8 selectedMonSlot);
PartyMenuArgs *FieldSystem_OpenPartyMenu_SelectPokemon(u32 unused, FieldSystem *fieldSystem);
PartyMenuArgs *FieldSystem_OpenPartyMenu_SelectForTrade(u32 unused, FieldSystem *fieldSystem);
u8 PartyMenu_GetSelectedSlot(PartyMenuArgs *args);
PartyMenuArgs *FieldSystem_OpenPartyMenu_SelectForDaycare(u32 unused, FieldSystem *fieldSystem, u8 selectedMonSlot);
u8 PartyMenu_GetMenuSelectionResult(PartyMenuArgs *args);
u8 PokemonSummary_GetPartySlot(PokemonSummaryArgs *args);
PartyMenuArgs *FieldSystem_OpenPartyMenu_SelectForUnionRoomBattle(TaskManager *taskManager, enum HeapID heapID);
PartyMenuArgs *FieldSystem_OpenPartyMenu_SelectForContest(u32 unused, FieldSystem *fieldSystem, u8 contestType, u8 contestRank, u32 useDefaultContestRank, u32 selectedMonSlot);
PokemonSummaryArgs *FieldSystem_GetPartyMenuMonSummary(u32 unused, FieldSystem *fieldSystem, u8 partySlot);
PokemonSummaryArgs *PokemonSummary_CreateArgs(FieldSystem *fieldSystem, enum HeapID heapID, u8 mode);
PokemonSummaryArgs *sub_02037CF0(enum HeapID heapID, FieldSystem *fieldSystem, u8 r2);
u8 PokemonSummary_GetSelectedMoveSlot(PokemonSummaryArgs *args);
void FieldSystem_OpenPokemonStorage(FieldSystem *fieldSystem, void *data);
void CallTask_EasyChat(TaskManager *taskManager, u16 *a1, u16 *a2, u16 *a3);
void FieldSystem_OpenEasyChat(FieldSystem *fieldSystem, void *data);
void FieldSystem_OpenTownMap(FieldSystem *fieldSystem, void *data);
void *FieldSystem_OpenTownMapItem(FieldSystem *fieldSystem);
void OpenOptionsMenu(FieldSystem *fieldSystem, void *data);
void *FieldSystem_OpenOptionsMenu(FieldSystem *fieldSystem);
void LaunchMailApp(FieldSystem *fieldSystem, void *data);
void *FieldSystem_LaunchMailApp_Write(FieldSystem *fieldSystem, u32 a1, u32 a2, u32 a3);
void *FieldSystem_LaunchMailApp_Read(FieldSystem *fieldSystem, u32 kind, u32 a2, u32 a3);
void *FieldSystem_LaunchMailApp_ReadHeld(FieldSystem *fieldSystem, u32 a1, u32 a2);
void OpenPoffinCaseApp(FieldSystem *fieldSystem, void *data);
void *FieldSystem_LaunchPoffinCaseApp(FieldSystem *fieldSystem, u32 a1);
void FieldSystem_OpenBattleTowerRecordsApp(FieldSystem *fieldSystem, void *data);
void sub_020380CC(TaskManager *taskManager, u16 *retVar, SaveData *save, u16 partySlot, u16 a4);
BOOL AccessoryPortrait_LaunchApp(FieldSystem *fieldSystem, void *data);
BOOL sub_02038130(FieldSystem *fieldSystem, void *data);
void CallTask_WirelessTrade(TaskManager *taskManager);
void sub_020383F8(FieldSystem *fieldSystem);
void *sub_0203842C(FieldSystem *fieldSystem);
void sub_0203846C(FieldSystem *fieldSystem, void *data);
void FieldSystem_OpenTrainerCase(FieldSystem *fieldSystem, void *data);
BOOL FieldSystem_OpenPokedex(FieldSystem *fieldSystem, void *data);
void FieldSystem_LaunchChooseStarterApp(FieldSystem *fieldSystem, void *data);
void FieldSystem_LaunchSignatureApp(FieldSystem *fieldSystem);
void FieldSystem_LaunchGTSApp(FieldSystem *fieldSystem, BOOL connectToWiFi);
u32 *NintendoWifiConnection_LaunchApp(FieldSystem *fieldSystem, u32 a1, u32 a2);
void ShowGeonetScreen(FieldSystem *fieldSystem);
void FieldTask_StartHallOfFame(FieldSystem *fieldSystem, void *data);
void *FieldTask_OpenPCHallOfFameScreen(FieldSystem *fieldSystem);
void FieldSystem_StartEndCredits(FieldSystem *fieldSystem, void *data);
void FieldSystem_OpenMoveReminderMenu(FieldSystem *fieldSystem, void *data);
void sub_0203888C(FieldSystem *fieldSystem, void *data);
void FieldSystem_HatchEgg(FieldSystem *fieldSystem);
BOOL sub_02038900(FieldSystem *fieldSystem, void *data);
void sub_020389CC(TaskManager *taskManager, u32 slotMachineID);
u8 sub_02038A3C(SaveData *save, u8 slotMachineID);
void AccessoryShop_Init(TaskManager *taskManager);
void *FieldSystem_ShowDiploma(FieldSystem *fieldSystem, enum HeapID heapID, BOOL isNatDex);

void Bag_LaunchApp(FieldSystem *fieldSystem, void *data);
void sub_0203791C(FieldSystem *fieldSystem, void *data);
void sub_02037944(FieldSystem *fieldSystem);
static PartyMenuArgs *PartyMenu_New(enum HeapID heapID, FieldSystem *fieldSystem, u8 type, u8 mode);
static BOOL Task_OpenPartyMenuForUnionRoomBattleSelect(TaskManager *taskManager);
static BOOL Task_EasyChat(TaskManager *taskManager);
AccessoryPortraitArgs *sub_0203800C(enum HeapID heapID, SaveData *save, u32 partySlot, u32 *r3, u32 r4);
static BOOL Task_AccessoryPortrait(TaskManager *taskManager);
static void InitWirelessTradeSelectMonArgs(WirelessTradeSelectMonArgs *args, FieldSystem *fieldSystem);
static void WirelessTradeSelectMon_FreeArgs(WirelessTradeSelectMonArgs *args);
static BOOL Task_WirelessTrade(TaskManager *taskManager);
static BOOL Task_NamingScreen(TaskManager *taskManager);
static void SetName(TaskManager *taskManager);
static BOOL Task_SlotMachine(TaskManager *taskManager);
static BOOL FieldTask_AccessoryShop(TaskManager *taskManager);

FS_EXTERN_OVERLAY(OVERLAY_11);
FS_EXTERN_OVERLAY(OVERLAY_14);
FS_EXTERN_OVERLAY(OVERLAY_15);
FS_EXTERN_OVERLAY(OVERLAY_16);
FS_EXTERN_OVERLAY(OVERLAY_17);
FS_EXTERN_OVERLAY(OVERLAY_53);
FS_EXTERN_OVERLAY(OVERLAY_54);
FS_EXTERN_OVERLAY(OVERLAY_55);
FS_EXTERN_OVERLAY(OVERLAY_57);
FS_EXTERN_OVERLAY(OVERLAY_58);
FS_EXTERN_OVERLAY(OVERLAY_60);
FS_EXTERN_OVERLAY(OVERLAY_64);
FS_EXTERN_OVERLAY(OVERLAY_66);
FS_EXTERN_OVERLAY(OVERLAY_67);
FS_EXTERN_OVERLAY(OVERLAY_68);
FS_EXTERN_OVERLAY(OVERLAY_69);
FS_EXTERN_OVERLAY(OVERLAY_70);
FS_EXTERN_OVERLAY(OVERLAY_71);
FS_EXTERN_OVERLAY(OVERLAY_74);
FS_EXTERN_OVERLAY(OVERLAY_75);
FS_EXTERN_OVERLAY(OVERLAY_76);
FS_EXTERN_OVERLAY(OVERLAY_77);
FS_EXTERN_OVERLAY(OVERLAY_78);
FS_EXTERN_OVERLAY(OVERLAY_80);
FS_EXTERN_OVERLAY(OVERLAY_81);
FS_EXTERN_OVERLAY(OVERLAY_82);
FS_EXTERN_OVERLAY(OVERLAY_84);
FS_EXTERN_OVERLAY(OVERLAY_85);
FS_EXTERN_OVERLAY(OVERLAY_86);

const u8 UNK_020F2BC4[] = { POCKET_BERRIES, POCKET_BAG_VIEW_END };
const u8 UNK_020F2BC8[] = { POCKET_ITEMS, POCKET_BAG_VIEW_END };
const u8 UNK_020F2BCC[] = { POCKET_TMHMS, POCKET_MAIL, 0x08 };
const u8 UNK_020F2BDC[] = {
    POCKET_ITEMS, POCKET_MEDICINE, POCKET_BALLS, POCKET_TMHMS,
    POCKET_BERRIES, POCKET_MAIL, POCKET_BATTLE_ITEMS, POCKET_KEY_ITEMS,
    POCKET_BAG_VIEW_END,
};
const u8 UNK_020F2BD0[] = { 0x00, 0x01, 0x02, 0x04, 0x03, 0x05, 0x06, 0x07, 0x08 };
const u8 UNK_020F2BE8[] = { 0x00, 0x05, 0x01, 0x01, 0x04, 0x04, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03 };


// One contiguous table at 0x020F2BF4; sApplicationTemplates[APP_*] replaces the
// individual UNK_020F2xxx labels. Entry 0x020F2D34 is dead data in the original ROM.
const OverlayManagerTemplate sApplicationTemplates[] = {
    /* 0x020F2BF4 */ { ov70_021D74E0, ov70_021D758C, ov70_021D755C, FS_OVERLAY_ID(OVERLAY_70) },
    /* 0x020F2C04 */ { ov84_021D74E0, ov84_021D7748, ov84_021D76A4, FS_OVERLAY_ID(OVERLAY_84) },
    /* 0x020F2C14 */ { ov85_021D74E0, ov85_021D75A0, ov85_021D7644, FS_OVERLAY_ID(OVERLAY_85) },
    /* 0x020F2C24 */ { ov58_021D9A20, ov58_021D9B8C, ov58_021D9BF0, FS_OVERLAY_ID(OVERLAY_58) },
    /* 0x020F2C34 */ { ov64_021D74E0, ov64_021D7640, ov64_021D76F4, FS_OVERLAY_ID(OVERLAY_64) },
    /* 0x020F2C44 */ { ov16_021D74E0, ov16_021D7588, ov16_021D7614, FS_OVERLAY_ID(OVERLAY_16) },
    /* 0x020F2C54 */ { ov57_021D74E0, ov57_021D7714, ov57_021D7944, FS_OVERLAY_ID(OVERLAY_57) },
    /* 0x020F2C64 */ { ov80_0222DFD0, ov80_0222E134, ov80_0222E25C, FS_OVERLAY_ID(OVERLAY_80) },
    /* 0x020F2C74 */ { ov82_0222DA34, ov82_0222DB7C, ov82_0222DC50, FS_OVERLAY_ID(OVERLAY_82) },
    /* 0x020F2C84 */ { ov76_021D74E0, ov76_021D7568, ov76_021D761C, FS_OVERLAY_ID(OVERLAY_76) },
    /* 0x020F2C94 */ { ov53_021D74E0, ov53_021D7654, ov53_021D7764, FS_OVERLAY_ID(OVERLAY_53) },
    /* 0x020F2CA4 */ { ov81_02237E40, ov81_02238064, ov81_02238004, FS_OVERLAY_ID(OVERLAY_81) },
    /* 0x020F2CB4 */ { ov74_021D74E0, ov74_021D755C, ov74_021D7540, FS_OVERLAY_ID(OVERLAY_74) },
    /* 0x020F2CC4 */ { ov60_021D74E0, ov60_021D76B8, ov60_021D75B0, FS_OVERLAY_ID(OVERLAY_60) },
    /* 0x020F2CD4 */ { ov66_021D74E0, ov66_021D7538, ov66_021D75B0, FS_OVERLAY_ID(OVERLAY_66) },
    /* 0x020F2CE4 */ { ov15_021D74E0, ov15_021D7558, ov15_021D7608, FS_OVERLAY_ID(OVERLAY_15) },
    /* 0x020F2CF4 */ { StoragePC_Overlay_Init, StoragePC_Overlay_Run, StoragePC_Overlay_Teardown, FS_OVERLAY_ID(OVERLAY_14) },
    /* 0x020F2D04 */ { ov54_021D74E0, ov54_021D764C, ov54_021D7740, FS_OVERLAY_ID(OVERLAY_54) },
    /* 0x020F2D14 */ { ov77_021D74E0, ov77_021D7604, ov77_021D7BAC, FS_OVERLAY_ID(OVERLAY_77) },
    /* 0x020F2D24 */ { ov67_021D74E0, ov67_021D75D0, ov67_021D7624, FS_OVERLAY_ID(OVERLAY_67) },
    /* 0x020F2D34 */ { ov55_021D7614, ov55_021D76BC, ov55_021D77AC, FS_OVERLAY_ID(OVERLAY_55) },
    /* 0x020F2D44 */ { ov68_021D74E0, ov68_021D75D8, ov68_021D762C, FS_OVERLAY_ID(OVERLAY_68) },
    /* 0x020F2D54 */ { ov55_021D756C, ov55_021D76BC, ov55_021D77AC, FS_OVERLAY_ID(OVERLAY_55) },
    /* 0x020F2D64 */ { HOF_OverlayInit, HOF_OverlayRun, HOF_OverlayTeardown, FS_OVERLAY_ID(OVERLAY_69) },
    /* 0x020F2D74 */ { ov75_021E6BA0, ov75_021E6D6C, ov75_021E6F00, FS_OVERLAY_ID(OVERLAY_75) },
    /* 0x020F2D84 */ { ov78_021D74E0, ov78_021D75D0, ov78_021D76B8, FS_OVERLAY_ID(OVERLAY_78) },
    /* 0x020F2D94 */ { ApplicationInit_Battle, ApplicationMain_Battle, ApplicationExit_Battle, FS_OVERLAY_ID(OVERLAY_11) },
    /* 0x020F2DA4 */ { ov86_021D74E0, ov86_021D758C, ov86_021D76B0, FS_OVERLAY_ID(OVERLAY_86) },
};

const u8 *UNK_02105DB8 = NULL;
OverlayManagerTemplate UNK_02105DBC = { ov71_0222D5C0, ov71_0222D9C8, ov71_0222E438, FS_OVERLAY_ID(OVERLAY_71) };
OverlayManagerTemplate UNK_02105DCC = { ov17_021DDB58, ov17_021DDC30, ov17_021DDCF4, FS_OVERLAY_ID(OVERLAY_17) };
OverlayManagerTemplate UNK_02105DDC = { ov17_021D83E4, ov17_021D84F0, ov17_021D8738, FS_OVERLAY_ID(OVERLAY_17) };

BOOL ApplicationInit_Battle(struct OverlayManager *manager, u32 *status) {
    return TRUE;
}

BOOL ApplicationMain_Battle(struct OverlayManager *manager, u32 *status) {
    if (ov11_0222D5C0()) {
        return TRUE;
    }
    return FALSE;
}

BOOL ApplicationExit_Battle(struct OverlayManager *manager, u32 *status) {
    return TRUE;
}

void FieldSystem_StartBattleProcess(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[26], data);
}

void Bag_LaunchApp(FieldSystem *fieldSystem, void *data) {
    OverlayManagerTemplate template = sApplicationTemplates[24];
    sub_020373D4(fieldSystem, &template, data);
}

BagView *FieldSystem_OpenBag(FieldSystem *fieldSystem, void *itemUseCtx) {
    BagView *bagView = Bag_CreateView(Save_Bag_Get(fieldSystem->saveData), UNK_020F2BDC, HEAP_ID_FIELD);

    sub_0206E314(bagView, fieldSystem->saveData, 0, fieldSystem->bagCursor);
    sub_0206E360(bagView, (u16)fieldSystem->unk6C);
    if (PlayerAvatar_GetState(fieldSystem->playerAvatar) == 1) {
        sub_0206E340(bagView);
    }
    sub_0206E354(bagView, itemUseCtx);
    Bag_LaunchApp(fieldSystem, bagView);
    return bagView;
}

BagView *FieldSystem_CreateBagContext(FieldSystem *fieldSystem, u32 pocketType) {
    Bag *bag = Save_Bag_Get(fieldSystem->saveData);
    BagView *bagView;

    switch (pocketType) {
    case 0:
        UNK_02105DB8 = UNK_020F2BC8;
        break;
    case 1:
        UNK_02105DB8 = UNK_020F2BC4;
        break;
    default:
        GF_AssertFail();
        break;
    }

    bagView = Bag_CreateView(bag, UNK_02105DB8, HEAP_ID_32);
    sub_0206E314(bagView, fieldSystem->saveData, 3, fieldSystem->bagCursor);
    Bag_LaunchApp(fieldSystem, bagView);
    return bagView;
}

u16 BagContext_GetSelectedItem(BagView *bagView) {
    u16 item = sub_0206E37C(bagView);

    if (item != 0 && sub_0206E384(bagView) == 5) {
        GF_AssertFail();
    }
    return item;
}

void sub_0203791C(FieldSystem *fieldSystem, void *data) {
    OverlayManagerTemplate template = sApplicationTemplates[21];
    sub_020373D4(fieldSystem, &template, data);
}

void sub_02037944(FieldSystem *fieldSystem) {
    OverlayManagerTemplate template = sApplicationTemplates[19];
    sub_020373D4(fieldSystem, &template, fieldSystem->saveData);
}

void FieldSystem_OpenSummaryScreen(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, &UNK_020FA6E8, data);
}

static PartyMenuArgs *PartyMenu_New(enum HeapID heapID, FieldSystem *fieldSystem, u8 type, u8 mode) {
    PartyMenuArgs *args = Heap_Alloc(heapID, sizeof(PartyMenuArgs));

    MI_CpuClearFast(args, sizeof(PartyMenuArgs));
    args->party = SaveArray_Party_Get(fieldSystem->saveData);
    args->bag = Save_Bag_Get(fieldSystem->saveData);
    args->mailbox = Save_Mailbox_Get(fieldSystem->saveData);
    args->options = Save_PlayerData_GetOptionsAddr(fieldSystem->saveData);
    args->unk_21 = type;
    args->context = mode;
    args->fieldSystem = fieldSystem;
    return args;
}

PartyMenuArgs *FieldSystem_OpenPartyMenu(FieldSystem *fieldSystem, FieldMoveCheckData *fieldMoveCheckData, u8 selectedMonSlot) {
    PartyMenuArgs *args = PartyMenu_New(HEAP_ID_FIELD, fieldSystem, 0, 0);

    args->fieldMoveCheckData = fieldMoveCheckData;
    args->partySlot = selectedMonSlot;
    sub_020373D4(fieldSystem, &UNK_020F96DC, args);
    return args;
}

PartyMenuArgs *FieldSystem_OpenPartyMenu_SelectPokemon(u32 unused, FieldSystem *fieldSystem) {
    PartyMenuArgs *args = PartyMenu_New(HEAP_ID_FIELD, fieldSystem, 0, 3);

    sub_020373D4(fieldSystem, &UNK_020F96DC, args);
    return args;
}

PartyMenuArgs *FieldSystem_OpenPartyMenu_SelectForTrade(u32 unused, FieldSystem *fieldSystem) {
    PartyMenuArgs *args = PartyMenu_New(HEAP_ID_FIELD, fieldSystem, 0, 0x13);

    sub_020373D4(fieldSystem, &UNK_020F96DC, args);
    return args;
}

u8 PartyMenu_GetSelectedSlot(PartyMenuArgs *args) {
    return args->partySlot;
}

PartyMenuArgs *FieldSystem_OpenPartyMenu_SelectForDaycare(u32 unused, FieldSystem *fieldSystem, u8 selectedMonSlot) {
    PartyMenuArgs *args = PartyMenu_New(HEAP_ID_FIELD, fieldSystem, 0, 0x12);

    args->partySlot = selectedMonSlot;
    sub_020373D4(fieldSystem, &UNK_020F96DC, args);
    return args;
}

u8 PartyMenu_GetMenuSelectionResult(PartyMenuArgs *args) {
    return args->selectedAction;
}

u8 PokemonSummary_GetPartySlot(PokemonSummaryArgs *args) {
    return args->partySlot;
}

static BOOL Task_OpenPartyMenuForUnionRoomBattleSelect(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    UnionRoomBattleSelectData *data = TaskManager_GetEnvironment(taskManager);
    u32 *state = TaskManager_GetStatePtr(taskManager);

    switch (*state) {
    case 0:
        sub_020373D4(fieldSystem, &UNK_020F96DC, data->partyMenuArgs);
        *state = 1;
        break;
    case 1:
        if (!FieldSystem_ApplicationIsRunning(fieldSystem)) {
            switch (data->partyMenuArgs->partySlot) {
            case 7:
                sub_020527D8(2);
                *state = 4;
                break;
            case 6:
                sub_020527D8(1);
                *state = 4;
                break;
            default:
                *state = 2;
                break;
            }
        }
        break;
    case 2:
        data->summaryArgs = PokemonSummary_CreateArgs(fieldSystem, data->heapID, 0);
        data->summaryArgs->partySlot = data->partyMenuArgs->partySlot;
        FieldSystem_OpenSummaryScreen(fieldSystem, data->summaryArgs);
        *state = 3;
        break;
    case 3:
        if (!FieldSystem_ApplicationIsRunning(fieldSystem)) {
            Heap_Free(data->summaryArgs);
            *state = 0;
        }
        break;
    case 4:
        Heap_Free(data);
        return TRUE;
    }

    return FALSE;
}

PartyMenuArgs *FieldSystem_OpenPartyMenu_SelectForUnionRoomBattle(TaskManager *taskManager, enum HeapID heapID) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    UnionRoomBattleSelectData *data = Heap_Alloc(heapID, sizeof(UnionRoomBattleSelectData));
    PartyMenuArgs *args;

    data->heapID = heapID;
    args = PartyMenu_New(heapID, fieldSystem, 0, 2);
    args->minMonsToSelect = 2;
    args->maxMonsToSelect = 2;
    args->maxLevel = 30;
    args->linkBattleRuleset = NULL;
    data->partyMenuArgs = args;
    TaskManager_Call(taskManager, Task_OpenPartyMenuForUnionRoomBattleSelect, data);
    return args;
}

PartyMenuArgs *FieldSystem_OpenPartyMenu_SelectForContest(u32 unused, FieldSystem *fieldSystem, u8 contestType, u8 contestRank, u32 useDefaultContestRank, u32 selectedMonSlot) {
    PartyMenuArgs *args = PartyMenu_New(HEAP_ID_FIELD, fieldSystem, 0, 0xD);

    args->partySlot = (u8)selectedMonSlot;
    args->unk_29 = 2;
    args->contestStat = contestType;
    if (useDefaultContestRank == 0) {
        args->contestLevel = contestRank;
    } else {
        args->contestLevel = 0;
    }
    sub_020373D4(fieldSystem, &UNK_020F96DC, args);
    return args;
}

PokemonSummaryArgs *FieldSystem_GetPartyMenuMonSummary(u32 unused, FieldSystem *fieldSystem, u8 partySlot) {
    PokemonSummaryArgs *args = Heap_Alloc(HEAP_ID_FIELD, sizeof(PokemonSummaryArgs));

    args->party = SaveArray_Party_Get(fieldSystem->saveData);
    args->options = Save_PlayerData_GetOptionsAddr(fieldSystem->saveData);
    args->unk11 = 1;
    args->partySlot = partySlot;
    args->partyCount = (u8)Party_GetCount(args->party);
    args->moveToLearn = 0;
    args->unk12 = 0;
    args->ribbons = sub_0202A918(fieldSystem->saveData);
    args->natDexEnabled = SaveArray_IsNatDexEnabled(fieldSystem->saveData);
    args->unk2C = (int)sub_02079C70(fieldSystem->saveData);
    args->unk28 = 0;
    sub_0207B000(args, UNK_020F2A9C);
    sub_0207C2A4(args, Save_PlayerData_GetProfile(fieldSystem->saveData));
    sub_020373D4(fieldSystem, &UNK_020FA6E8, args);
    return args;
}

PokemonSummaryArgs *PokemonSummary_CreateArgs(FieldSystem *fieldSystem, enum HeapID heapID, u8 mode) {
    SaveData *saveData = fieldSystem->saveData;
    PokemonSummaryArgs *args = Heap_AllocAtEnd(heapID, sizeof(PokemonSummaryArgs));

    MI_CpuFill8(args, 0, sizeof(PokemonSummaryArgs));
    args->options = Save_PlayerData_GetOptionsAddr(saveData);
    args->party = SaveArray_Party_Get(saveData);
    args->unk11 = 1;
    args->partySlot = 0;
    args->partyCount = (u8)Party_GetCount(args->party);
    args->moveToLearn = 0;
    args->unk12 = mode;
    args->natDexEnabled = SaveArray_IsNatDexEnabled(saveData);
    args->unk2C = (int)sub_02079C70(saveData);
    args->ribbons = sub_0202A918(saveData);
    sub_0207B000(args, UNK_020F2BD0);
    sub_0207C2A4(args, Save_PlayerData_GetProfile(saveData));
    return args;
}

PokemonSummaryArgs *sub_02037CF0(enum HeapID heapID, FieldSystem *fieldSystem, u8 r2) {
    PokemonSummaryArgs *args = Heap_Alloc(heapID, sizeof(PokemonSummaryArgs));

    memset(args, 0, sizeof(PokemonSummaryArgs));
    args->party = SaveArray_Party_Get(fieldSystem->saveData);
    args->options = Save_PlayerData_GetOptionsAddr(fieldSystem->saveData);
    args->unk11 = 1;
    args->partySlot = r2;
    args->partyCount = 1;
    args->moveToLearn = 0;
    args->unk12 = 2;
    args->natDexEnabled = SaveArray_IsNatDexEnabled(fieldSystem->saveData);
    args->unk2C = (int)sub_02079C70(fieldSystem->saveData);
    sub_0207B000(args, UNK_020F2BCC);
    sub_0207C2A4(args, Save_PlayerData_GetProfile(fieldSystem->saveData));
    FieldSystem_OpenSummaryScreen(fieldSystem, args);
    return args;
}

u8 PokemonSummary_GetSelectedMoveSlot(PokemonSummaryArgs *args) {
    return args->unk16;
}

void FieldSystem_OpenPokemonStorage(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[16], data);
}

static BOOL Task_EasyChat(TaskManager *taskManager) {
    u16 sp[2];

    u32 *state = TaskManager_GetStatePtr(taskManager);
    EasyChatTaskData *data = TaskManager_GetEnvironment(taskManager);
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);

    switch (*state) {
    case 0:
        FieldSystem_OpenEasyChat(fieldSystem, data->easyChat);
        (*state)++;
        break;
    case 1:
        if (!FieldSystem_ApplicationIsRunning(fieldSystem)) {
            (*state)++;
        }
        break;
    case 2:
        if (sub_020853E4(data->easyChat) || !sub_020853E8(data->easyChat)) {
            *data->unk00 = 0;
        } else {
            *data->unk00 = 1;
            if (data->unk08 == NULL) {
                *data->unk04 = sub_020853EC(data->easyChat);
            } else {
                sub_020853F0(data->easyChat, sp);
                *data->unk04 = sp[0];
                *data->unk08 = sp[1];
            }
        }
        sub_020853A8(data->easyChat);
        Heap_Free(data);
        return TRUE;
    }

    return FALSE;
}

void CallTask_EasyChat(TaskManager *taskManager, u16 *a1, u16 *a2, u16 *a3) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    EasyChatTaskData *data = Heap_Alloc(HEAP_ID_32, sizeof(EasyChatTaskData));

    data->unk00 = a1;
    data->unk04 = a2;
    data->unk08 = a3;
    if (a3 == NULL) {
        data->easyChat = sub_02085338(0, 0, fieldSystem->saveData, HEAP_ID_32);
        sub_020853B0(data->easyChat, *a2);
    } else {
        data->easyChat = sub_02085338(1, 0, fieldSystem->saveData, HEAP_ID_32);
        sub_020853B4(data->easyChat, *a2, *a3);
    }
    TaskManager_Call(taskManager, Task_EasyChat, data);
}

void FieldSystem_OpenEasyChat(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[15], data);
}

void FieldSystem_OpenTownMap(FieldSystem *fieldSystem, void *data) {
    OverlayManagerTemplate template = sApplicationTemplates[14];
    sub_020373D4(fieldSystem, &template, data);
}

void *FieldSystem_OpenTownMapItem(FieldSystem *fieldSystem) {
    void *args;

    sub_02034E0C(Save_LocalFieldData_Get(fieldSystem->saveData));
    args = Heap_AllocAtEnd(HEAP_ID_FIELD, 320);
    TownMap_Init(fieldSystem, args, 0);
    FieldSystem_OpenTownMap(fieldSystem, args);
    return args;
}

void OpenOptionsMenu(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[13], data);
}

void *FieldSystem_OpenOptionsMenu(FieldSystem *fieldSystem) {
    void *args = Heap_AllocAtEnd(HEAP_ID_FIELD, 2);

    OpenOptionsMenu(fieldSystem, Save_PlayerData_GetOptionsAddr(FieldSystem_GetSaveData(fieldSystem)));
    return args;
}

void LaunchMailApp(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, &UNK_020FCAC8, data);
}

void *FieldSystem_LaunchMailApp_Write(FieldSystem *fieldSystem, u32 a1, u32 a2, u32 a3) {
    void *args = sub_020854E0(FieldSystem_GetSaveData(fieldSystem), a1, a2, a3, HEAP_ID_FIELD);

    LaunchMailApp(fieldSystem, args);
    return args;
}

void *FieldSystem_LaunchMailApp_Read(FieldSystem *fieldSystem, u32 kind, u32 a2, u32 a3) {
    void *args;

    if (kind == 3) {
        args = sub_020855B0(FieldSystem_GetSaveData(fieldSystem), a2, a3);
    } else {
        args = sub_02085538(FieldSystem_GetSaveData(fieldSystem), kind, a2, a3);
    }
    LaunchMailApp(fieldSystem, args);
    return args;
}

void *FieldSystem_LaunchMailApp_ReadHeld(FieldSystem *fieldSystem, u32 a1, u32 a2) {
    void *args = sub_02085578(FieldSystem_GetSaveData(fieldSystem), a1, a2);

    LaunchMailApp(fieldSystem, args);
    return args;
}

void OpenPoffinCaseApp(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, &UNK_020FD1B0, data);
}

void *FieldSystem_LaunchPoffinCaseApp(FieldSystem *fieldSystem, u32 a1) {
    void *args = sub_02087D00(FieldSystem_GetSaveData(fieldSystem), a1);

    OpenPoffinCaseApp(fieldSystem, args);
    return args;
}

void FieldSystem_OpenBattleTowerRecordsApp(FieldSystem *fieldSystem, void *data) {
    OverlayManagerTemplate template = sApplicationTemplates[12];
    sub_020373D4(fieldSystem, &template, data);
}

AccessoryPortraitArgs *sub_0203800C(enum HeapID heapID, SaveData *save, u32 partySlot, u32 *r3, u32 r4) {
    AccessoryPortraitArgs *args = Heap_Alloc(heapID, sizeof(AccessoryPortraitArgs));
    void *fashionData;
    void *portrait;
    void *fashionCase;

    memset(args, 0, sizeof(AccessoryPortraitArgs));
    args->mon = Party_GetMonByIndex(SaveArray_Party_Get(save), partySlot);
    fashionData = Save_FashionData_Get(save);
    portrait = sub_02027008(fashionData, 0);
    fashionCase = Save_FashionData_GetFashionCase(fashionData);
    args->unk04 = portrait;
    args->fashionCase = fashionCase;
    args->options = Save_PlayerData_GetOptionsAddr(save);
    args->gameStats = Save_GameStats_Get(save);
    args->profile = Save_PlayerData_GetProfile(save);
    args->unk18 = r3;
    args->unk1C = r4;
    return args;
}

static BOOL Task_AccessoryPortrait(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    AccessoryPortraitTaskData *data = TaskManager_GetEnvironment(taskManager);

    switch (data->state) {
    case 0:
        AccessoryPortrait_LaunchApp(fieldSystem, data->args);
        data->state++;
        break;
    case 1:
        if (!FieldSystem_ApplicationIsRunning(fieldSystem)) {
            if (data->unk08 == 1) {
                *data->retVar = 1;
            } else {
                *data->retVar = 0;
            }
            Heap_Free(data->args);
            Heap_Free(data);
            return TRUE;
        }
        break;
    }

    return FALSE;
}

void sub_020380CC(TaskManager *taskManager, u16 *retVar, SaveData *save, u16 partySlot, u16 a4) {
    AccessoryPortraitTaskData *data = Heap_Alloc(HEAP_ID_32, sizeof(AccessoryPortraitTaskData));
    u8 *ptr = (u8 *)data;
    u32 size;

    for (size = sizeof(AccessoryPortraitTaskData); size != 0; size--) {
        *ptr++ = 0;
    }
    data->args = sub_0203800C(HEAP_ID_32, save, partySlot, &data->unk08, a4);
    data->retVar = retVar;
    TaskManager_Call(taskManager, Task_AccessoryPortrait, data);
}

BOOL AccessoryPortrait_LaunchApp(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, &UNK_02105DDC, data);
    return TRUE;
}

BOOL sub_02038130(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, &UNK_02105DCC, data);
    return TRUE;
}

static void InitWirelessTradeSelectMonArgs(WirelessTradeSelectMonArgs *args, FieldSystem *fieldSystem) {
    args->profile = Save_PlayerData_GetProfile(fieldSystem->saveData);
    args->party = SaveArray_Party_Get(fieldSystem->saveData);
    args->palPad = SaveArray_Get(fieldSystem->saveData, 9);
    args->unk14 = sub_02029AFC(fieldSystem->saveData);
    args->options = Save_PlayerData_GetOptionsAddr(fieldSystem->saveData);
    args->pokedex = Save_Pokedex_Get(fieldSystem->saveData);
    args->natDexEnabled = SaveArray_IsNatDexEnabled(fieldSystem->saveData);
    args->saveData = fieldSystem->saveData;
    args->unk1C = fieldSystem->unk98;
    args->gameStats = Save_GameStats_Get(fieldSystem->saveData);
    args->partnerProfile = Heap_Alloc(HEAP_ID_32, PlayerProfile_sizeof());
    args->sentMon = Heap_Alloc(HEAP_ID_32, sub_020690C4());
    args->receivedMon = Heap_Alloc(HEAP_ID_32, sub_020690C4());
    args->fieldSystem = fieldSystem;
    args->tradeCount = 0;
}

static void WirelessTradeSelectMon_FreeArgs(WirelessTradeSelectMonArgs *args) {
    if (args->partnerProfile != NULL) {
        Heap_Free(args->partnerProfile);
        args->partnerProfile = NULL;
    }
    if (args->sentMon != NULL) {
        Heap_Free(args->sentMon);
        args->sentMon = NULL;
    }
    if (args->receivedMon != NULL) {
        Heap_Free(args->receivedMon);
        args->receivedMon = NULL;
    }
}

static BOOL Task_WirelessTrade(TaskManager *taskManager) {
    u32 evoMethod;

    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    WirelessTradeData *data = TaskManager_GetEnvironment(taskManager);

    switch (data->state) {
    case 0:
        if (!sub_02033590()) {
            FieldTransition_FinishMap(taskManager);
        }
        data->state++;
        break;
    case 1:
        InitWirelessTradeSelectMonArgs(&data->selectMon, fieldSystem);
        data->state++;
    case 2:
        sub_02046500(taskManager, (u32)&UNK_02105DBC, (u32)&data->selectMon);
        data->state++;
        break;
    case 3:
        if (data->selectMon.tradeConfirmed == 0) {
            WirelessTradeSelectMon_FreeArgs(&data->selectMon);
            Heap_Free(data);
            return TRUE;
        }
        data->state++;
        break;
    case 4:
        data->tradeSequence.otherTrainer = data->selectMon.partnerProfile;
        data->tradeSequence.sendingPokemon = sub_020690E4(data->selectMon.sentMon);
        data->tradeSequence.receivingPokemon = sub_020690E4(data->selectMon.receivedMon);
        data->tradeSequence.options = Save_PlayerData_GetOptionsAddr(fieldSystem->saveData);
        data->tradeSequence.tradeType = TRADE_TYPE_NORMAL;

        switch (Script_GetTimeOfDay(fieldSystem)) {
        case 0:
        default:
            data->tradeSequence.background = TRADE_BACKGROUND_DAY;
            break;
        case 2:
            data->tradeSequence.background = TRADE_BACKGROUND_EVENING;
            break;
        case 3:
        case 4:
            data->tradeSequence.background = TRADE_BACKGROUND_NIGHT;
            break;
        }
        if (sub_02033590()) {
            data->tradeSequence.background = TRADE_BACKGROUND_WIFI;
        }
        sub_02046500(taskManager, (u32)&sApplicationTemplates[11], (u32)&data->tradeSequence);
        data->state = 5;
        break;
    case 5: {
        int heldItem = GetMonData(data->selectMon.receivedMon, MON_DATA_HELD_ITEM, NULL);
        u16 species = GetMonEvolution(NULL, data->selectMon.receivedMon, 1, (u16)heldItem, &evoMethod);
        if (species != SPECIES_NONE) {
            Heap_Create(HEAP_ID_MAIN, HEAP_ID_26, 0x30000);
            data->evolutionTaskData = sub_0206C700(NULL, data->selectMon.receivedMon, species,
                Save_PlayerData_GetOptionsAddr(fieldSystem->saveData),
                sub_02079C70(fieldSystem->saveData),
                Save_Pokedex_Get(fieldSystem->saveData),
                Save_Bag_Get(fieldSystem->saveData),
                Save_GameStats_Get(fieldSystem->saveData),
                Save_Poketch_Get(fieldSystem->saveData),
                evoMethod, 4, HEAP_ID_26);
            data->state = 6;
        } else {
            data->state = 7;
        }
        break;
    }
    case 6:
        if (sub_0206C91C(data->evolutionTaskData)) {
            CopyPokemonToPokemon(data->selectMon.receivedMon,
                Party_GetMonByIndex(data->selectMon.party, data->selectMon.partySlot));
            sub_0206C92C(data->evolutionTaskData);
            Heap_Destroy(HEAP_ID_26);
            data->state = 7;
        }
        break;
    case 7:
        data->selectMon.tradeCount++;
        data->state = 2;
        GameStats_AddSpecial(Save_GameStats_Get(fieldSystem->saveData), 0x10);
        break;
    }

    return FALSE;
}

void CallTask_WirelessTrade(TaskManager *taskManager) {
    WirelessTradeData *data = Heap_Alloc(HEAP_ID_32, sizeof(WirelessTradeData));

    data->state = 0;
    TaskManager_Call(taskManager, Task_WirelessTrade, data);
}

void sub_020383F8(FieldSystem *fieldSystem) {
    u32 *args = Heap_Alloc(HEAP_ID_32, 0xC);

    args[0] = fieldSystem->unk7C;
    args[1] = (u32)fieldSystem->unk98;
    args[2] = (u32)Save_PlayerData_GetOptionsAddr(fieldSystem->saveData);
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[10], args);
}

void *sub_0203842C(FieldSystem *fieldSystem) {
    u32 *args = Heap_Alloc(HEAP_ID_FIELD, 0x14);

    args[0] = (u32)fieldSystem->saveData;
    args[1] = fieldSystem->unk7C;
    args[2] = (u32)Save_PlayerData_GetOptionsAddr(fieldSystem->saveData);
    args[3] = (u32)Save_GameStats_Get(fieldSystem->saveData);
    args[4] = (u32)fieldSystem->unk98;
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[17], args);
    return args;
}

void sub_0203846C(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[22], data);
}

static BOOL Task_NamingScreen(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    NamingScreenData *data = TaskManager_GetEnvironment(taskManager);

    switch (data->state) {
    case 0:
        FieldTransition_FinishMap(taskManager);
        data->state++;
        break;
    case 1:
        sub_02046500(taskManager, (u32)&UNK_020FA5FC, (u32)data->args);
        data->state++;
        break;
    case 2:
        FieldTransition_StartMap(taskManager);
        data->state++;
        break;
    case 3: {
        NamingScreenArgs *args = data->args;
        if (args->kind == 1) {
            if (String_Compare(args->nameInputString, data->unk10) == 0) {
                data->args->noInput = 1;
            }
        } else if (args->kind == 5) {
            u16 *name = String_c_str(args->nameInputString);
            if (sub_02028854(sub_0202881C(fieldSystem->saveData), name)) {
                data->args->noInput = 2;
            }
        }
        if (data->args->noInput == 0) {
            SetName(taskManager);
        }
        if (data->retVar != NULL) {
            *data->retVar = (u16)data->args->noInput;
        }
        sub_02077AC4(data->args);
        String_Delete(data->unk10);
        Heap_Free(data);
        return TRUE;
    }
    }

    return FALSE;
}

static void SetName(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    NamingScreenData *data = TaskManager_GetEnvironment(taskManager);

    switch (data->args->kind) {
    case NAMINGSCREEN_PLAYER: {
        PlayerProfile *profile = Save_PlayerData_GetProfile(fieldSystem->saveData);
        CopyPlayerName((u16 *)profile, (PlayerProfile *)data->args->nameInputFlat);
        break;
    }
    case NAMINGSCREEN_POKEMON: {
        Pokemon *mon = Party_GetMonByIndex(SaveArray_Party_Get(fieldSystem->saveData), data->partyIdx);
        SetMonData(mon, MON_DATA_NICKNAME_FLAT_COMPARE, data->args->nameInputFlat);
        break;
    }
    case NAMINGSCREEN_GROUP: {
        void *palPad = sub_0202881C(fieldSystem->saveData);
        sub_020287C0(palPad, 0, 0, data->args->nameInputString);
        break;
    }
    case NAMINGSCREEN_SHAYMIN_ROCK: {
        void *misc = sub_02024EB4(fieldSystem->saveData);
        sub_02024F18(misc, data->args->nameInputString);
        break;
    }
    case NAMINGSCREEN_BOX:
    case NAMINGSCREEN_RIVAL:
    default:
        break;
    }
}

void CreateNamingScreen(TaskManager *taskManager, enum NamingScreenType type, s32 param2, s32 maxLen, s32 initPos, const u16 *defaultStr, u16 *retVar) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    NamingScreenData *data = Heap_AllocAtEnd(HEAP_ID_FIELD, sizeof(NamingScreenData));

    data->state = 0;
    data->partyIdx = initPos;
    data->retVar = retVar;
    data->args = sub_02077A84(HEAP_ID_FIELD, type, param2, maxLen, Save_PlayerData_GetOptionsAddr(fieldSystem->saveData));
    data->unk10 = String_New(12, HEAP_ID_FIELD);

    switch (type) {
    case NAMINGSCREEN_POKEMON: {
        Pokemon *mon = Party_GetMonByIndex(SaveArray_Party_Get(fieldSystem->saveData), data->partyIdx);
        data->args->monGender = GetMonData(mon, MON_DATA_GENDER, NULL);
        data->args->monForm = GetMonData(mon, MON_DATA_FORM, NULL);
        if (defaultStr != NULL) {
            CopyU16ArrayToString(data->unk10, (u16 *)defaultStr);
        }
        break;
    }
    case NAMINGSCREEN_GROUP:
        CopyU16ArrayToString(data->unk10, (u16 *)defaultStr);
        break;
    default:
        if (defaultStr != NULL) {
            CopyU16ArrayToString(data->args->nameInputString, (u16 *)defaultStr);
        }
        break;
    }
    TaskManager_Call(taskManager, Task_NamingScreen, data);
}

void FieldSystem_OpenTrainerCase(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[6], data);
}

BOOL FieldSystem_OpenPokedex(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[5], data);
    return TRUE;
}

void FieldSystem_LaunchChooseStarterApp(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[4], data);
}

void FieldSystem_LaunchSignatureApp(FieldSystem *fieldSystem) {
    OverlayManagerTemplate template;

    sub_02029ABC(fieldSystem->saveData);
    template = sApplicationTemplates[3];
    sub_020373D4(fieldSystem, &template, fieldSystem->saveData);
}

void FieldSystem_LaunchGTSApp(FieldSystem *fieldSystem, BOOL connectToWiFi) {
    OverlayManagerTemplate template = sApplicationTemplates[7];
    u32 *args = Heap_AllocAtEnd(HEAP_ID_FIELD, 0x44);

    args[0] = (u32)sub_0202ABBC(fieldSystem->saveData);
    args[1] = (u32)Save_SysInfo_Get(fieldSystem->saveData);
    args[2] = (u32)SaveArray_Get(fieldSystem->saveData, 2);
    args[3] = (u32)SaveArray_PCStorage_Get(fieldSystem->saveData);
    args[4] = (u32)Save_Pokedex_Get(fieldSystem->saveData);
    args[5] = (u32)sub_020286EC(fieldSystem->saveData);
    args[6] = (u32)sub_02029AFC(fieldSystem->saveData);
    args[7] = (u32)Save_PlayerData_GetProfile(fieldSystem->saveData);
    args[9] = (u32)Save_PlayerData_GetOptionsAddr(fieldSystem->saveData);
    args[10] = (u32)Save_GameStats_Get(fieldSystem->saveData);
    args[11] = (u32)fieldSystem->unk98;
    args[15] = (u32)sub_02079C70(fieldSystem->saveData);
    args[8] = (u32)fieldSystem->saveData;
    args[13] = SaveArray_IsNatDexEnabled(fieldSystem->saveData);
    args[14] = (u32)sub_02033830((void *)args[5]);
    args[12] = (u32)Save_Bag_Get(fieldSystem->saveData);
    args[16] = connectToWiFi;
    sub_020373D4(fieldSystem, &template, args);
}

u32 *NintendoWifiConnection_LaunchApp(FieldSystem *fieldSystem, u32 a1, u32 a2) {
    OverlayManagerTemplate template = sApplicationTemplates[8];
    u32 *args = Heap_AllocAtEnd(HEAP_ID_FIELD, 0x28);

    args[0] = (u32)Save_FrontierData_Get(fieldSystem->saveData);
    args[1] = (u32)SaveStruct23_GetSubstruct4(fieldSystem->saveData);
    args[2] = (u32)Save_SysInfo_Get(fieldSystem->saveData);
    args[4] = (u32)Save_PlayerData_GetOptionsAddr(fieldSystem->saveData);
    args[5] = (u32)sub_02028228(sub_020286EC(fieldSystem->saveData));
    args[3] = (u32)fieldSystem->saveData;
    args[7] = (u32)sub_02033830(sub_020286EC(fieldSystem->saveData));
    args[6] = a1;
    args[9] = a2;
    sub_020373D4(fieldSystem, &template, args);
    return args;
}

void ShowGeonetScreen(FieldSystem *fieldSystem) {
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[18], fieldSystem->saveData);
}

void FieldTask_StartHallOfFame(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[23], data);
}

void *FieldTask_OpenPCHallOfFameScreen(FieldSystem *fieldSystem) {
    u32 result;
    void *hallOfFame = LoadHallOfFame(fieldSystem->saveData, HEAP_ID_FIELD, &result);

    if (result == 2) {
        Heap_Free(hallOfFame);
        return NULL;
    }
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[0], hallOfFame);
    return hallOfFame;
}

void FieldSystem_StartEndCredits(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[1], data);
}

void FieldSystem_OpenMoveReminderMenu(FieldSystem *fieldSystem, void *data) {
    OverlayManagerTemplate template = sApplicationTemplates[9];
    sub_020373D4(fieldSystem, &template, data);
}

void sub_0203888C(FieldSystem *fieldSystem, void *data) {
    OverlayManagerTemplate template = sApplicationTemplates[25];
    sub_020373D4(fieldSystem, &template, data);
}

void FieldSystem_HatchEgg(FieldSystem *fieldSystem) {
    HatchEggArgs data;

    Pokemon *mon = ov05_021ED49C(SaveArray_Party_Get(fieldSystem->saveData));
    if (mon == NULL) {
        GF_AssertFail();
    }
    sub_020613CC(fieldSystem, mon);
    data.mon = mon;
    data.options = Save_PlayerData_GetOptionsAddr(fieldSystem->saveData);
    data.profile = Save_PlayerData_GetProfile(fieldSystem->saveData);
    data.bgm = FieldSystem_GetOverriddenMusicId(fieldSystem, fieldSystem->location->mapId);
    sub_020863DC(fieldSystem->taskManager, &data);
}

BOOL sub_02038900(FieldSystem *fieldSystem, void *data) {
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[2], data);
    return TRUE;
}

static BOOL Task_SlotMachine(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    void *varsFlags = Save_VarsFlags_Get(fieldSystem->saveData);
    SlotMachineData *data = TaskManager_GetEnvironment(taskManager);
    u32 *state = TaskManager_GetStatePtr(taskManager);

    switch (*state) {
    case 0:
        sub_02038900(fieldSystem, &data->args);
        (*state)++;
        break;
    case 1:
        if (!FieldSystem_ApplicationIsRunning(fieldSystem)) {
            u16 *coins = Save_PlayerData_GetCoinsAddr(fieldSystem->saveData);
            s64 now = GF_RTC_DateTimeToSec();
            u32 coinValue = Coins_GetValue(coins);
            sub_02061A8C(fieldSystem, coinValue, data->coins, (s32)(GF_RTC_TimeDelta(data->startTime, now) / 60));
            Coins_SetValue(Save_PlayerData_GetCoinsAddr(fieldSystem->saveData), data->coins);
            s32 best = sub_0205F6C8(varsFlags);
            if (data->unk18 > best) {
                sub_0205F6D8(varsFlags, (u16)data->unk18);
            }
            Heap_Free(data);
            return TRUE;
        }
        break;
    }

    return FALSE;
}

void sub_020389CC(TaskManager *taskManager, u32 slotMachineID) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    Options *options = Save_PlayerData_GetOptionsAddr(fieldSystem->saveData);
    SlotMachineData *data = Heap_Alloc(HEAP_ID_32, sizeof(SlotMachineData));

    data->args = data;
    data->coins = Coins_GetValue(Save_PlayerData_GetCoinsAddr(fieldSystem->saveData));
    data->startTime = GF_RTC_DateTimeToSec();
    data->gameStats = Save_GameStats_Get(fieldSystem->saveData);
    data->unk18 = 0;
    data->frame = Options_GetFrame(options);
    data->unk10 = sub_02038A3C(fieldSystem->saveData, (u8)slotMachineID);
    GameStats_AddSpecial(Save_GameStats_Get(fieldSystem->saveData), 5);
    TaskManager_Call(taskManager, Task_SlotMachine, data);
}

u8 sub_02038A3C(SaveData *save, u8 slotMachineID) {
    u8 table[12];
    u32 seed;
    u8 i;
    u8 j;

    void *unk = sub_0202881C(save);
    seed = GetLCRNGSeed();
    SetLCRNGSeed(sub_020287A4(unk));
    MI_CpuCopy8(UNK_020F2BE8, table, 12);
    for (i = 0; i < 12; i++) {
        for (j = (u8)(i + 1); j < 12; j++) {
            u8 k = (u8)(LCRandom() % 12);
            u8 tmp = table[i];
            table[i] = table[k];
            table[k] = tmp;
        }
    }
    SetLCRNGSeed(seed);
    return table[slotMachineID];
}

static BOOL FieldTask_AccessoryShop(TaskManager *taskManager) {
    void *data = TaskManager_GetEnvironment(taskManager);

    if (ov06_0224D79C(data) == 1) {
        ov06_0224D76C(data);
        return TRUE;
    }
    return FALSE;
}

void AccessoryShop_Init(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);

    TaskManager_Call(taskManager, FieldTask_AccessoryShop, ov06_0224D70C(4, fieldSystem->saveData, fieldSystem->bgConfig));
}

void *FieldSystem_ShowDiploma(FieldSystem *fieldSystem, enum HeapID heapID, BOOL isNatDex) {
    u32 *args = Heap_Alloc(heapID, 8);

    args[1] = isNatDex;
    args[0] = (u32)fieldSystem->saveData;
    sub_020373D4(fieldSystem, (OverlayManagerTemplate *)&sApplicationTemplates[27], args);
    return args;
}
