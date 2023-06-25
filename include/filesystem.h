#ifndef POKEDIAMOND_FILESYSTEM_H
#define POKEDIAMOND_FILESYSTEM_H

#include "heap.h"
#include "nitro/types.h"
#include "FS_file.h"

typedef struct NARC
{
    FSFile file;
    u32 btaf_start;
    u32 gmif_start;
    u16 num_files;
} NARC;

typedef enum NarcId
{
    NARC_BATTLE_SKILL_WAZA_SEQ                              =   0,
    NARC_BATTLE_SKILL_SUB_SEQ                               =   1,
    NARC_POKETOOL_PERSONAL_PERSONAL                         =   2,
    NARC_POKETOOL_PERSONAL_GROWTBL                          =   3,
    NARC_POKETOOL_POKEGRA_POKEGRA                           =   4,
    NARC_POKETOOL_POKEGRA_HEIGHT                            =   5,
    NARC_POKETOOL_TRGRA_TRBGRA                              =   6,
    NARC_BATTLE_GRAPHIC_BATT_BG                             =   7,
    NARC_WAZAEFFECT_WE                                      =   8,
    NARC_POKETOOL_WAZA_WAZA_TBL                             =   9,
    NARC_FIELDDATA_SCRIPT_SCR_SEQ_RELEASE                   =  10,
    NARC_MSGDATA_SCENARIO_SCR_MSG                           =  11,
    NARC_GRAPHIC_POKETCH                                    =  12,
    NARC_GRAPHIC_BAG_GRA                                    =  13,
    NARC_GRAPHIC_FONT                                       =  14,
    NARC_ITEMTOOL_ITEMDATA_ITEM_DATA                        =  15,
    NARC_ITEMTOOL_ITEMDATA_ITEM_ICON                        =  16,
    NARC_GRAPHIC_TMAP_GRA                                   =  17,
    NARC_GRAPHIC_BOX                                        =  18,
    NARC_POKETOOL_ICONGRA_POKE_ICON                         =  19,
    NARC_GRAPHIC_PLIST_GRA                                  =  20,
    NARC_WAZAEFFECT_EFFECTCLACT_WECHAR                      =  21,
    NARC_WAZAEFFECT_EFFECTCLACT_WEPLTT                      =  22,
    NARC_WAZAEFFECT_EFFECTCLACT_WECELL                      =  23,
    NARC_WAZAEFFECT_EFFECTCLACT_WECELLANM                   =  24,
    NARC_GRAPHIC_IMAGECLIP                                  =  25,
    NARC_MSGDATA_MSG                                        =  26,
    NARC_BATTLE_GRAPHIC_BATT_OBJ                            =  27,
    NARC_DATA_UNDERG_RADAR                                  =  28,
    NARC_WAZAEFFECT_EFFECTDATA_WAZA_PARTICLE                =  29,
    NARC_BATTLE_SKILL_BE_SEQ                                =  30,
    NARC_DATA_NAMEIN                                        =  31,
    NARC_FIELDDATA_EVENTDATA_ZONE_EVENT_RELEASE             =  32,
    NARC_POKETOOL_PERSONAL_WOTBL                            =  33,
    NARC_POKETOOL_PERSONAL_EVO                              =  34,
    NARC_GRAPHIC_FONTOAM                                    =  35,
    NARC_GRAPHIC_FIELD_BOARD                                =  36,
    NARC_FIELDDATA_ENCOUNTDATA_D_ENC_DATA                   =  37,
    NARC_GRAPHIC_WINFRAME                                   =  38,
    NARC_GRAPHIC_PST_GRA                                    =  39,
    NARC_FIELDDATA_BUILD_MODEL_BUILD_MODEL                  =  40,
    NARC_FIELDDATA_MAPMATRIX_MAP_MATRIX                     =  41,
    NARC_FIELDDATA_AREADATA_AREA_DATA                       =  42,
    NARC_FIELDDATA_AREADATA_AREA_BUILD_MODEL_AREA_BUILD     =  43,
    NARC_FIELDDATA_AREADATA_AREA_MAP_TEX_MAP_TEX_SET        =  44,
    NARC_CONTEST_GRAPHIC_CONTEST_BG                         =  45,
    NARC_CONTEST_GRAPHIC_CONTEST_OBJ                        =  46,
    NARC_DATA_UGEFFECT_OBJ_GRAPHIC                          =  47,
    NARC_DEMO_TITLE_TITLEDEMO                               =  48,
    NARC_FIELDDATA_AREADATA_AREA_MOVE_MODEL_MOVE_MODEL_LIST =  49,
    NARC_DATA_UG_TRAP                                       =  50,
    NARC_GRAPHIC_TRAINER_CASE                               =  51,
    NARC_DATA_UG_FOSSIL                                     =  52,
    NARC_GRAPHIC_NTAG_GRA                                   =  53,
    NARC_DATA_TRADELIST                                     =  54,
    NARC_DATA_UG_PARTS                                      =  55,
    NARC_GRAPHIC_OPENING                                    =  56,
    NARC_POKETOOL_TRAINER_TRDATA                            =  57,
    NARC_POKETOOL_TRAINER_TRPOKE                            =  58,
    NARC_POKETOOL_TRMSG_TRTBL                               =  59,
    NARC_POKETOOL_TRGRA_TRFGRA                              =  60,
    NARC_PARTICLEDATA_PARTICLEDATA                          =  61,
    NARC_GRAPHIC_SHOP_GRA                                   =  62,
    NARC_WAZAEFFECT_WE_SUB                                  =  63,
    NARC_DATA_UG_ANIM                                       =  64,
    NARC_DATA_WEATHER_SYS                                   =  65,
    NARC_GRAPHIC_MENU_GRA                                   =  66,
    NARC_FIELDDATA_LAND_DATA_LAND_DATA_RELEASE              =  67,
    NARC_ITEMTOOL_ITEMDATA_NUTS_DATA                        =  68,
    NARC_RESOURCE_ENG_ZUKAN_ZUKAN                           =  69,
    NARC_POKETOOL_POKEFOOT_POKEFOOT                         =  70,
    NARC_FIELDDATA_AREADATA_AREA_BUILD_MODEL_AREABM_TEXSET  =  71,
    NARC_BATTLE_GRAPHIC_B_PLIST_GRA                         =  72,
    NARC_GRAPHIC_CONFIG_GRA                                 =  73,
    NARC_GRAPHIC_UNIONROOM                                  =  74,
    NARC_APPLICATION_ZUKANLIST_ZKN_DATA_ZUKAN_DATA          =  75,
    NARC_GRAPHIC_PMSI                                       =  76,
    NARC_BATTLE_GRAPHIC_B_BAG_GRA                           =  77,
    NARC_GRAPHIC_OEKAKI                                     =  78,
    NARC_GRAPHIC_MAIL_GRA                                   =  79,
    NARC_GRAPHIC_F_NOTE_GRA                                 =  80,
    NARC_DATA_MMODEL_MMODEL                                 =  81,
    NARC_GRAPHIC_EV_POKESELECT                              =  82,
    NARC_GRAPHIC_PORU_GRA                                   =  83,
    NARC_GRAPHIC_TOUCH_SUBWINDOW                            =  84,
    NARC_GRAPHIC_FLD_COMACT                                 =  85,
    NARC_GRAPHIC_RECORD                                     =  86,
    NARC_GRAPHIC_PORUDEMO                                   =  87,
    NARC_GRAPHIC_PORUACT                                    =  88,
    NARC_DATA_WIFINOTE                                      =  89,
    NARC_CONTEST_DATA_CONTEST_DATA                          =  90,
    NARC_APPLICATION_CUSTOM_BALL_DATA_CB_DATA               =  91,
    NARC_DATA_WIFIP2PMATCH                                  =  92,
    NARC_GRAPHIC_DEMO_TRADE                                 =  93,
    NARC_POKEANIME_POKE_ANM                                 =  94,
    NARC_GRAPHIC_MYSIGN                                     =  95,
    NARC_FIELDDATA_MM_LIST_MOVE_MODEL_LIST                  =  96,
    NARC_DATA_FIELD_CUTIN                                   =  97,
    NARC_DATA_DEMO_CLIMAX                                   =  98,
    NARC_WAZAEFFECT_EFFECTDATA_BALL_PARTICLE                =  99,
    NARC_WAZAEFFECT_PT_DEBUG_DEBUG_PARTICLE                 = 100,
    NARC_GRAPHIC_DENDOU_PC                                  = 101,
    NARC_APPLICATION_WIFI_EARTH_WIFI_EARTH_PLACE            = 102,
    NARC_BATTLE_TR_AI_TR_AI_SEQ                             = 103,
    NARC_GRAPHIC_WORLDTRADE                                 = 104,
    NARC_GRAPHIC_DENDOU_DEMO                                = 105,
    NARC_ARC_ENCDATA_EX                                     = 106,
    NARC_DATA_MMODEL_FLDEFF                                 = 107,
    NARC_BATTLE_GRAPHIC_VS_DEMO_GRA                         = 108,
    NARC_POKETOOL_POKEZUKAN                                 = 109,
    NARC_ARC_BM_ANIME                                       = 110,
    NARC_ARC_BM_ANIME_LIST                                  = 111,
    NARC_GRAPHIC_FIELD_ENCOUNTEFFECT                        = 112,
    NARC_GRAPHIC_WAZA_OSHIE_GRA                             = 113,
    NARC_POKETOOL_POKEANM_POKEANM                           = 114,
    NARC_FIELDDATA_POKEMON_TRADE_FLD_TRADE                  = 115,
    NARC_GRAPHIC_MYSTERY                                    = 116,
    NARC_POKETOOL_POKEGRA_OTHERPOKE                         = 117,
    NARC_DEMO_EGG_DATA_EGG_DATA                             = 118,
    NARC_DEMO_EGG_DATA_PARTICLE_EGG_DEMO_PARTICLE           = 119,
    NARC_ARC_SHIP_DEMO                                      = 120,
    NARC_POKETOOL_POKEGRA_HEIGHT_O                          = 121,
    NARC_GRAPHIC_NUTMIXER                                   = 122,
    NARC_GRAPHIC_BTOWER                                     = 123,
    NARC_DEMO_SHINKA_DATA_PARTICLE_SHINKA_DEMO_PARTICLE     = 124,
    NARC_DEMO_INTRO_INTRO                                   = 125,
    NARC_ARC_TV                                             = 126,
    NARC_GRAPHIC_ENDING                                     = 127,
    NARC_DEMO_TITLE_OP_DEMO                                 = 128,
    NARC_APPLICATION_WIFI_EARTH_WIFI_EARTH                  = 129,
    NARC_GRAPHIC_RANKING                                    = 130,
    NARC_ARC_PPARK                                          = 131,
    NARC_DEMO_SYOUJYOU_SYOUJYOU                             = 132,
    NARC_DATA_SLOT                                          = 133,
    NARC_BATTLE_B_TOWER_BTDTR                               = 134,
    NARC_BATTLE_B_TOWER_BTDPM                               = 135,
    NARC_DEMO_INTRO_INTRO_TV                                = 136,
    NARC_POKETOOL_TRMSG_TRTBLOFS                            = 137,
    NARC_POKETOOL_POKEGRA_POKE_YOFS                         = 138,
    NARC_APPLICATION_ZUKANLIST_ZKN_DATA_ZUKAN_ENC_DIAMOND   = 139,
    NARC_APPLICATION_ZUKANLIST_ZKN_DATA_ZUKAN_ENC_PEARL     = 140,
    NARC_GRAPHIC_HIDEN_EFFECT                               = 141,
    NARC_POKETOOL_POKEGRA_POKE_SHADOW                       = 142,
    NARC_FIELDDATA_ENCOUNTDATA_P_ENC_DATA                   = 143,
    NARC_POKETOOL_POKEGRA_POKE_SHADOW_OFX                   = 144,
    NARC_POKETOOL_SHINZUKAN                                 = 145,
} NarcId;

void ReadFromNarcMemberByPathAndId(void * dest, const char * path, s32 file_idx, u32 offset, u32 size);
void * AllocAndReadFromNarcMemberByPathAndId(const char * path, s32 file_idx, HeapID heapId, u32 offset, u32 size, BOOL r4);
void ReadWholeNarcMemberByIdPair(void * dest, NarcId narc_id, s32 file_id);
void * AllocAndReadWholeNarcMemberByIdPair(NarcId narc_id, s32 file_id, HeapID heapId);
void * AllocAtEndAndReadWholeNarcMemberByIdPair(NarcId narc_id, s32 file_id, HeapID heapId);
void ReadFromNarcMemberByIdPair(void * dest, NarcId narc_id, s32 file_id, u32 offset, u32 size);
void * AllocAndReadFromNarcMemberByIdPair(NarcId narc_id, s32 file_id, HeapID heapId, u32 offset, u32 size);
void * AllocAtEndAndReadFromNarcMemberByIdPair(NarcId narc_id, s32 file_id, HeapID heapId, u32 offset, u32 size);
u32 GetNarcMemberSizeByIdPair(NarcId narc_id, s32 file_idx);
NARC * NARC_New(NarcId narc_id, HeapID heapId);
void NARC_Delete(NARC * narc);
void * NARC_AllocAndReadWholeMember(NARC * narc, u32 file_id, HeapID heapId);
void NARC_ReadWholeMember(NARC * narc, u32 file_id, void * dest);
u32 NARC_GetMemberSize(NARC * narc, u32 file_id);
void NARC_ReadFromMember(NARC * narc, u32 file_id, u32 pos, u32 size, void * dest);
void NARC_ReadFile(NARC * narc, u32 size, void * dest);
u16 NARC_GetFileCount(NARC * narc);

#endif //POKEDIAMOND_FILESYSTEM_H
