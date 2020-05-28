//============================================================================================
/**
 * @file	sway_grass_hist.h
 * @brief	揺れ草エンカウント履歴
 * @author	saito GAME FREAK inc.
 * @date	2006.02.14
 */
//============================================================================================
#ifndef _SWAY_GRASS_HIST_H_
#define _SWAY_GRASS_HIST_H_

#include "field_common.h"
#include "sway_grass_hist_def.h"

extern int SwayGrassHist_GetHistNum(FIELDSYS_WORK * fsys);
extern int SwayGrassHist_GetMonsNo(FIELDSYS_WORK * fsys, const u8 inNo);
extern int SwayGrassHist_GetChain(FIELDSYS_WORK * fsys, const u8 inNo);
extern int SwayGrassHist_GetNowChain(FIELDSYS_WORK * fsys);
extern int SwayGrassHist_GetNowMonsNo(FIELDSYS_WORK * fsys);
extern void SwayGrassHist_SortHistData(SWAY_GRASS_HIST *ioHist);

#endif //_SWAY_GRASS_HIST_H_
