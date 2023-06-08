#include "nitro/types.h"
#include "main.h"
#include "gx.h"
#include "code32.h"

extern u32 GXi_DmaId;

static s32 sBGExtPltt = 0;
static u32 sBGExtPlttLCDCBlk = 0;
static u32 sBGExtPlttLCDCOffset = 0;
static s32 sOBJExtPltt = 0;
static u32 sOBJExtPlttLCDCBlk = 0;
static s32 sSubBGExtPltt = 0;
static s32 sSubOBJExtPltt = 0;


static inline void *_GX_OBJ_PTR(){
    return (void *)0x6400000;
}
static inline void *_GXS_OBJ_PTR(){
    return (void *)0x6600000;
}

void GX_LoadBGPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(0x5000000 + offset), size);
}

void GXS_LoadBGPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(0x5000400 + offset), size);
}

void GX_LoadOBJPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(0x5000200 + offset), size);
}

void GXS_LoadOBJPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(0x5000600 + offset), size);
}

void GX_LoadOAM(void *src, u32 offset, u32 size){
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(0x7000000 + offset), size);
}

void GXS_LoadOAM(void *src, u32 offset, u32 size){
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(0x7000400 + offset), size);
}

void GX_LoadOBJ(void *src, u32 offset, u32 size){
    u32 base = (u32)_GX_OBJ_PTR();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

void GXS_LoadOBJ(void *src, u32 offset, u32 size){
    u32 base = (u32)_GXS_OBJ_PTR();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

void GX_LoadBG0Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG0ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

void GXS_LoadBG0Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG0ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

void GX_LoadBG1Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG1ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

void GXS_LoadBG1Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG1ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

void GX_LoadBG2Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG2ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

void GXS_LoadBG2Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG2ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

void GX_LoadBG3Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG3ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

void GXS_LoadBG3Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG3ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

void GX_LoadBG0Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG0CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

void GXS_LoadBG0Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG0CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

void GX_LoadBG1Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG1CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

void GXS_LoadBG1Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG1CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

void GX_LoadBG2Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG2CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

void GXS_LoadBG2Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG2CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

void GX_LoadBG3Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG3CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

void GXS_LoadBG3Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG3CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

void GX_BeginLoadBGExtPltt(){
    sBGExtPltt = (s32)GX_ResetBankForBGExtPltt();
    switch (sBGExtPltt)
    {
    case 0: //needed to match
        break;
    case 0x10:
        sBGExtPlttLCDCBlk = 0x06880000;
        sBGExtPlttLCDCOffset = 0x0;
        break;
    case 0x40:
        sBGExtPlttLCDCBlk = 0x06894000;
        sBGExtPlttLCDCOffset = 0x4000;
        break;
    case 0x20:
    case 0x60:
        sBGExtPlttLCDCBlk = 0x06890000;
        sBGExtPlttLCDCOffset = 0x0;
        break;
    }
}

void GX_LoadBGExtPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy32Async(GXi_DmaId, src, (void *)(sBGExtPlttLCDCBlk + offset - sBGExtPlttLCDCOffset), size, NULL, NULL);
}

void GX_EndLoadBGExtPltt(){
    GXi_WaitDma(GXi_DmaId);
    GX_SetBankForBGExtPltt(sBGExtPltt);
    sBGExtPltt = 0x0;
    sBGExtPlttLCDCBlk = 0x0;
    sBGExtPlttLCDCOffset = 0x0;
}

void GX_BeginLoadOBJExtPltt(){
    sOBJExtPltt = (s32)GX_ResetBankForOBJExtPltt();
    switch (sOBJExtPltt)
    {
    case 0: //needed to match
        break;
    case 0x40:
        sOBJExtPlttLCDCBlk = 0x06894000;
        break;
    case 0x20:
        sOBJExtPlttLCDCBlk = 0x06890000;
        break;
    }
}

void GX_LoadOBJExtPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy32Async(GXi_DmaId, src, (void *)(sOBJExtPlttLCDCBlk + offset), size, NULL, NULL);
}

void GX_EndLoadOBJExtPltt(){
    GXi_WaitDma(GXi_DmaId);
    GX_SetBankForOBJExtPltt(sOBJExtPltt);
    sOBJExtPltt = 0x0;
    sOBJExtPlttLCDCBlk = 0x0;
}

void GXS_BeginLoadBGExtPltt(){
    sSubBGExtPltt = (s32)GX_ResetBankForSubBGExtPltt();
}

void GXS_LoadBGExtPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy32Async(GXi_DmaId, src, (void *)(0x06898000 + offset), size, NULL, NULL);
}

void GXS_EndLoadBGExtPltt(){
    GXi_WaitDma(GXi_DmaId);
    GX_SetBankForSubBGExtPltt(sSubBGExtPltt);
    sSubBGExtPltt = 0x0;
}

void GXS_BeginLoadOBJExtPltt(){
    sSubOBJExtPltt = (s32)GX_ResetBankForSubOBJExtPltt();
}

void GXS_LoadOBJExtPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy32Async(GXi_DmaId, src, (void *)(0x068A0000 + offset), size, NULL, NULL);
}

void GXS_EndLoadOBJExtPltt(){
    GXi_WaitDma(GXi_DmaId);
    GX_SetBankForSubOBJExtPltt(sSubOBJExtPltt);
    sSubOBJExtPltt = 0x0;
}
