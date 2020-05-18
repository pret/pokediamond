#include "global.h"
#include "main.h"
#include "gx.h"

extern u32 UNK_02106814;

extern s32 UNK_021D33F8;
extern s32 UNK_021D33F4;
extern u32 UNK_021D33F0;
extern u32 UNK_021D33EC;
extern s32 UNK_021D33E8;
extern u32 UNK_021D33E4;
extern s32 UNK_021D33E0;


static inline void *_GX_OBJ_PTR(){
    return (void *)0x6400000;
}
static inline void *_GXS_OBJ_PTR(){
    return (void *)0x6600000;
}

ARM_FUNC void GX_LoadBGPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy16(UNK_02106814, src, (void *)(0x5000000 + offset), size);
}

ARM_FUNC void GXS_LoadBGPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy16(UNK_02106814, src, (void *)(0x5000400 + offset), size);
}

ARM_FUNC void GX_LoadOBJPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy16(UNK_02106814, src, (void *)(0x5000200 + offset), size);
}

ARM_FUNC void GXS_LoadOBJPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy16(UNK_02106814, src, (void *)(0x5000600 + offset), size);
}

ARM_FUNC void GX_LoadOAM(void *src, u32 offset, u32 size){
    GXi_DmaCopy32(UNK_02106814, src, (void *)(0x7000000 + offset), size);
}

ARM_FUNC void GXS_LoadOAM(void *src, u32 offset, u32 size){
    GXi_DmaCopy32(UNK_02106814, src, (void *)(0x7000400 + offset), size);
}

ARM_FUNC void GX_LoadOBJ(void *src, u32 offset, u32 size){
    u32 base = (u32)_GX_OBJ_PTR();
    GXi_DmaCopy32(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadOBJ(void *src, u32 offset, u32 size){
    u32 base = (u32)_GXS_OBJ_PTR();
    GXi_DmaCopy32(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG0Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG0ScrPtr();
    GXi_DmaCopy16(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG0Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG0ScrPtr();
    GXi_DmaCopy16(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG1Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG1ScrPtr();
    GXi_DmaCopy16(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG1Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG1ScrPtr();
    GXi_DmaCopy16(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG2Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG2ScrPtr();
    GXi_DmaCopy16(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG2Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG2ScrPtr();
    GXi_DmaCopy16(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG3Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG3ScrPtr();
    GXi_DmaCopy16(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG3Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG3ScrPtr();
    GXi_DmaCopy16(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG0Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG0CharPtr();
    GXi_DmaCopy32(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG0Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG0CharPtr();
    GXi_DmaCopy32(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG1Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG1CharPtr();
    GXi_DmaCopy32(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG1Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG1CharPtr();
    GXi_DmaCopy32(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG2Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG2CharPtr();
    GXi_DmaCopy32(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG2Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG2CharPtr();
    GXi_DmaCopy32(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG3Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG3CharPtr();
    GXi_DmaCopy32(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG3Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG3CharPtr();
    GXi_DmaCopy32(UNK_02106814, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_BeginLoadBGExtPltt(){
    UNK_021D33F4 = GX_ResetBankForBGExtPltt();
    switch (UNK_021D33F4)
    {
    case 0: //needed to match
        break;
    case 0x10:
        UNK_021D33F0 = 0x06880000;
        UNK_021D33EC = 0x0;
        break;
    case 0x40:
        UNK_021D33F0 = 0x06894000;
        UNK_021D33EC = 0x4000;
        break;
    case 0x20:
    case 0x60:
        UNK_021D33F0 = 0x06890000;
        UNK_021D33EC = 0x0;
        break;
    }
}

ARM_FUNC void GX_LoadBGExtPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy32Async(UNK_02106814, src, (void *)(UNK_021D33F0 + offset - UNK_021D33EC), size, NULL, NULL);
}

ARM_FUNC void GX_EndLoadBGExtPltt(){
    GXi_WaitDma(UNK_02106814);
    GX_SetBankForBGExtPltt(UNK_021D33F4);
    UNK_021D33F4 = 0x0;
    UNK_021D33F0 = 0x0;
    UNK_021D33EC = 0x0;
}

ARM_FUNC void GX_BeginLoadOBJExtPltt(){
    UNK_021D33E8 = GX_ResetBankForOBJExtPltt();
    switch (UNK_021D33E8)
    {
    case 0: //needed to match
        break;
    case 0x40:
        UNK_021D33E4 = 0x06894000;
        break;
    case 0x20:
        UNK_021D33E4 = 0x06890000;
        break;
    }
}

ARM_FUNC void GX_LoadOBJExtPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy32Async(UNK_02106814, src, (void *)(UNK_021D33E4 + offset), size, NULL, NULL);
}

ARM_FUNC void GX_EndLoadOBJExtPltt(){
    GXi_WaitDma(UNK_02106814);
    GX_SetBankForOBJExtPltt(UNK_021D33E8);
    UNK_021D33E8 = 0x0;
    UNK_021D33E4 = 0x0;
}

ARM_FUNC void GXS_BeginLoadBGExtPltt(){
    UNK_021D33E0 = FUN_020C6034();
}

ARM_FUNC void GXS_LoadBGExtPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy32Async(UNK_02106814, src, (void *)(0x06898000 + offset), size, NULL, NULL);
}

ARM_FUNC void GXS_EndLoadBGExtPltt(){
    GXi_WaitDma(UNK_02106814);
    GX_SetBankForSubBGExtPltt(UNK_021D33E0);
    UNK_021D33E0 = 0x0;
}

ARM_FUNC void GXS_BeginLoadOBJExtPltt(){
    UNK_021D33F8 = GX_ResetBankForSubOBJ();
}

ARM_FUNC void GXS_LoadOBJExtPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy32Async(UNK_02106814, src, (void *)(0x068A0000 + offset), size, NULL, NULL);
}

ARM_FUNC void GXS_EndLoadOBJExtPltt(){
    GXi_WaitDma(UNK_02106814);
    GX_SetBankForSubOBJExtPltt(UNK_021D33F8);
    UNK_021D33F8 = 0x0;
}
