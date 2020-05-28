//=============================================================================
/**
 * @file	honey_tree_enc.h
 * @bfief	蜜塗りエンカウント
 * @author	Nozomu Saito
 *
 *
 */
//=============================================================================
#ifndef _HONEY_TREE_ENC_H_
#define _HONEY_TREE_ENC_H_

#include "field_common.h"
#include "map3d_object.h"

#define HONEY_TREE_LV_MIN	(5)
#define HONEY_TREE_LV_MAX	(15)


typedef struct HONEY_TREE_DAT_tag * HTD_PTR;

extern HTD_PTR HTE_AllocHoneyTreeDat(void);
extern void HTE_FreeHoneyTreeDat(HTD_PTR *outHoneyTree);
extern BOOL HTE_CheckHoneyTree(FIELDSYS_WORK *fsys, int *outScrID);
extern u16 HTE_GetNowLocHoneyTreeState(FIELDSYS_WORK *fsys);
extern void HTE_SetupNowLocHoneyTree(FIELDSYS_WORK *fsys);
extern void HTE_SetHoneyTreeInfoAfterBtl(FIELDSYS_WORK *fsys);
extern void HTE_SetHoneyTreeAnimation(FIELDSYS_WORK *fsys, M3DOL_PTR inMap3DObjList);
extern int HTE_GetHoneyTreeMonster(FIELDSYS_WORK *fsys);
extern void HTE_SetHoneyTreeAnimeCallBack(void* work, const int inBlockIndex, const M3DOL_PTR inObjList);
extern void HTE_ResetAnimeFlg(FIELDSYS_WORK *fsys);
//extern void HTE_UpdateHoneyTreeTime(FIELDSYS_WORK *fsys,  const int inDiffMinute);

#endif	//_HONEY_TREE_ENC_H_
