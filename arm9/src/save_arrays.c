#include "global.h"
#include "bag.h"
#include "player_data.h"
#include "save_block_2.h"
#include "party.h"
#include "event_data.h"
#include "pokemon_storage_system.h"
#include "sav_system_info.h"
#include "poketch.h"
#include "hall_of_fame.h"
#include "unk_020286F8.h"
#include "unk_020254B8.h"
#include "daycare.h"
#include "pokedex.h"
#include "seal.h"
#include "unk_020139D8.h"
#include "unk_02024E64.h"
#include "sav_chatot.h"
#include "unk_0202A1E0.h"

extern u32 FUN_0202AC20(void);
extern u32 FUN_02034D7C(void);
extern u32 FUN_02034D80(void);
extern u32 FUN_02025954(void);
extern u32 FUN_02023AC8(void);
extern u32 FUN_02026FD8(void);
extern u32 FUN_02028054(void);
extern u32 FUN_02028980(void);
extern u32 FUN_02029A84(void);
extern u32 Save_GameStats_sizeof(void);
extern u32 Save_Chatot_sizeof(void);
extern u32 FUN_0202A8F4(void);
extern u32 FUN_0202A924(void);
extern u32 FUN_0202ABC8(void);
extern u32 FUN_0202B374(void);
extern u32 FUN_0202B8B0(void);
extern u32 FUN_020281E0(void);
extern u32 FUN_02029AE0(void);
extern u32 FUN_0202BE98(void);
extern u32 FUN_0202C0E0(void);
extern void FUN_0202AC28(void *);
extern void FUN_02034D98(void *);
extern void FUN_02034D88(void *);
extern void FUN_0202597C(void *);
extern void FUN_02023AD8(void *);
extern void FUN_02026F60(void *);
extern void FUN_0202805C(void *);
extern void FUN_02028994(void *);
extern void FUN_02029A8C(void *);
extern void Save_GameStats_Init(void *);
extern void FUN_0202A8F8(void *);
extern void FUN_0202A92C(void *);
extern void FUN_0202ABCC(void *);
extern void FUN_0202B37C(void *);
extern void FUN_0202B8B8(void *);
extern void FUN_020281E8(void *);
extern void FUN_02029AE8(void *);
extern void FUN_0202BEA0(void *);
extern void FUN_0202C0E4(void *);

const struct SaveChunkHeader UNK_020EE6E0[] = {
    { 0, 32, (SAVSIZEFN)Save_HOF_sizeof, (SAVINITFN)Save_HOF_Init },
    { 1, 35, (SAVSIZEFN)FUN_0202AC20, (SAVINITFN)FUN_0202AC28 }
};

const struct SaveChunkHeader UNK_020EE700[] = {
    {  0, 0, (SAVSIZEFN)Save_SysInfo_sizeof, (SAVINITFN)Save_SysInfo_Init },
    {  1, 0, (SAVSIZEFN)Save_PlayerData_sizeof, (SAVINITFN)Save_PlayerData_Init },
    {  2, 0, (SAVSIZEFN)SaveArray_Party_sizeof, (SAVINITFN)SaveArray_Party_Init },
    {  3, 0, (SAVSIZEFN)Save_Bag_sizeof, (SAVINITFN)Save_Bag_Init },
    {  4, 0, (SAVSIZEFN)SaveArray_Flags_sizeof, (SAVINITFN)SaveArray_Flags_Init },
    {  5, 0, (SAVSIZEFN)Save_Poketch_sizeof, (SAVINITFN)Save_Poketch_Init },
    {  6, 0, (SAVSIZEFN)FUN_02034D7C, (SAVINITFN)FUN_02034D98 },
    {  7, 0, (SAVSIZEFN)Save_Pokedex_sizeof, (SAVINITFN)Save_Pokedex_Init },
    {  8, 0, (SAVSIZEFN)Save_DayCare_sizeof, (SAVINITFN)Save_DayCare_Init },
    {  9, 0, (SAVSIZEFN)FUN_020254B8, (SAVINITFN)FUN_020254CC },
    { 10, 0, (SAVSIZEFN)FUN_02024E64,          (SAVINITFN)FUN_02024E6C },
    { 11, 0, (SAVSIZEFN)FUN_02034D80,          (SAVINITFN)FUN_02034D88 },
    { 12, 0, (SAVSIZEFN)FUN_02025954,          (SAVINITFN)FUN_0202597C },
    { 13, 0, (SAVSIZEFN)FUN_02023AC8,          (SAVINITFN)FUN_02023AD8 },
    { 14, 0, (SAVSIZEFN)FUN_02026FD8,          (SAVINITFN)FUN_02026F60 },
    { 15, 0, (SAVSIZEFN)Save_Mailbox_sizeof,   (SAVINITFN)Save_Mailbox_Init },
    { 16, 0, (SAVSIZEFN)FUN_02028054,          (SAVINITFN)FUN_0202805C },
    { 17, 0, (SAVSIZEFN)FUN_020286F8,          (SAVINITFN)FUN_02028724 },
    { 18, 0, (SAVSIZEFN)FUN_02028980,          (SAVINITFN)FUN_02028994 },
    { 19, 0, (SAVSIZEFN)FUN_02029A84,          (SAVINITFN)FUN_02029A8C },
    { 20, 0, (SAVSIZEFN)Save_GameStats_sizeof, (SAVINITFN)Save_GameStats_Init },
    { 21, 0, (SAVSIZEFN)Save_SealCase_sizeof,  (SAVINITFN)Save_SealCase_Init },
    { 22, 0, (SAVSIZEFN)Save_Chatot_sizeof,    (SAVINITFN)Save_Chatot_Init },
    { 23, 0, (SAVSIZEFN)SaveStruct23_sizeof,   (SAVINITFN)SaveStruct23_Init },
    { 24, 0, (SAVSIZEFN)FUN_0202A8F4,          (SAVINITFN)FUN_0202A8F8 },
    { 25, 0, (SAVSIZEFN)FUN_0202A924,          (SAVINITFN)FUN_0202A92C },
    { 26, 0, (SAVSIZEFN)FUN_0202ABC8,          (SAVINITFN)FUN_0202ABCC },
    { 27, 0, (SAVSIZEFN)FUN_0202B374,          (SAVINITFN)FUN_0202B37C },
    { 28, 0, (SAVSIZEFN)FUN_0202B8B0,          (SAVINITFN)FUN_0202B8B8 },
    { 29, 0, (SAVSIZEFN)FUN_020281E0,          (SAVINITFN)FUN_020281E8 },
    { 30, 0, (SAVSIZEFN)FUN_02029AE0,          (SAVINITFN)FUN_02029AE8 },
    { 31, 0, (SAVSIZEFN)FUN_0202AC20, (SAVINITFN)FUN_0202AC28 },
    { 32, 0, (SAVSIZEFN)FUN_0202BE98, (SAVINITFN)FUN_0202BEA0 },
    { 33, 0, (SAVSIZEFN)FUN_0202C0E0, (SAVINITFN)FUN_0202C0E4 },
    { 34, 0, (SAVSIZEFN)FUN_02013B28, (SAVINITFN)FUN_02013B2C },
    { 35, 1, (SAVSIZEFN)PCStorage_sizeof, (SAVINITFN)PCStorage_Init },
};

const int UNK_020EE6D8 = NELEMS(UNK_020EE6E0);
const int UNK_020EE6DC = NELEMS(UNK_020EE700);
