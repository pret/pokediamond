/**
 *	@file	tmap_act.h
 *	@brief	タウンマップモジュール　セルアクター制御
 *	@data	05.12.21
 *	@author	Miyuki Iwasawa
 */

#include "tmap_act.dat"

extern void TMapCellActorInit(TMAP_MAIN_DAT *pMain);
extern void TMapCellActorRelease(TMAP_MAIN_DAT *pMain);
extern void TMapCellActorMain(TMAP_MAIN_DAT *pMain);
extern void TMapCellActorTrans(TMAP_MAIN_DAT* pMain);
