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
extern u32 Sav2_GameStats_sizeof(void);
extern u32 Sav2_Chatot_sizeof(void);
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
extern void Sav2_GameStats_init(void *);
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
    { 0, 32, (SAVSIZEFN)Sav2_HOF_sizeof, (SAVINITFN)Sav2_HOF_init },
    { 1, 35, (SAVSIZEFN)FUN_0202AC20, (SAVINITFN)FUN_0202AC28 }
};

const struct SaveChunkHeader UNK_020EE700[] = {
    {  0, 0, (SAVSIZEFN)Sav2_SysInfo_sizeof, (SAVINITFN)Sav2_SysInfo_init },
    {  1, 0, (SAVSIZEFN)Sav2_PlayerData_sizeof, (SAVINITFN)Sav2_PlayerData_init },
    {  2, 0, (SAVSIZEFN)SavArray_Party_sizeof, (SAVINITFN)SavArray_Party_init },
    {  3, 0, (SAVSIZEFN)Sav2_Bag_sizeof, (SAVINITFN)Sav2_Bag_init },
    {  4, 0, (SAVSIZEFN)SavArray_Flags_sizeof, (SAVINITFN)SavArray_Flags_init },
    {  5, 0, (SAVSIZEFN)Sav2_Poketch_sizeof, (SAVINITFN)Sav2_Poketch_init },
    {  6, 0, (SAVSIZEFN)FUN_02034D7C, (SAVINITFN)FUN_02034D98 },
    {  7, 0, (SAVSIZEFN)Sav2_Pokedex_sizeof, (SAVINITFN)Sav2_Pokedex_init },
    {  8, 0, (SAVSIZEFN)Sav2_DayCare_sizeof, (SAVINITFN)Sav2_DayCare_init },
    {  9, 0, (SAVSIZEFN)FUN_020254B8, (SAVINITFN)FUN_020254CC },
    { 10, 0, (SAVSIZEFN)FUN_02024E64,          (SAVINITFN)FUN_02024E6C },
    { 11, 0, (SAVSIZEFN)FUN_02034D80,          (SAVINITFN)FUN_02034D88 },
    { 12, 0, (SAVSIZEFN)FUN_02025954,          (SAVINITFN)FUN_0202597C },
    { 13, 0, (SAVSIZEFN)FUN_02023AC8,          (SAVINITFN)FUN_02023AD8 },
    { 14, 0, (SAVSIZEFN)FUN_02026FD8,          (SAVINITFN)FUN_02026F60 },
    { 15, 0, (SAVSIZEFN)Sav2_Mailbox_sizeof,   (SAVINITFN)Sav2_Mailbox_init },
    { 16, 0, (SAVSIZEFN)FUN_02028054,          (SAVINITFN)FUN_0202805C },
    { 17, 0, (SAVSIZEFN)FUN_020286F8,          (SAVINITFN)FUN_02028724 },
    { 18, 0, (SAVSIZEFN)FUN_02028980,          (SAVINITFN)FUN_02028994 },
    { 19, 0, (SAVSIZEFN)FUN_02029A84,          (SAVINITFN)FUN_02029A8C },
    { 20, 0, (SAVSIZEFN)Sav2_GameStats_sizeof, (SAVINITFN)Sav2_GameStats_init },
    { 21, 0, (SAVSIZEFN)Sav2_SealCase_sizeof,  (SAVINITFN)Sav2_SealCase_init },
    { 22, 0, (SAVSIZEFN)Sav2_Chatot_sizeof,    (SAVINITFN)Sav2_Chatot_init },
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
    { 35, 1, (SAVSIZEFN)PCStorage_sizeof, (SAVINITFN)PCStorage_init },
};

const int UNK_020EE6D8 = NELEMS(UNK_020EE6E0);
const int UNK_020EE6DC = NELEMS(UNK_020EE700);
