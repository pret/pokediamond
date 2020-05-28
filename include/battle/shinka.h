
//============================================================================================
/**
 * @file	shinka.h
 * @bfief	戦闘進化デモプログラム
 * @author	HisashiSogabe
 * @date	05.10.25
 */
//============================================================================================

#ifndef __SHINKA_H_
#define __SHINKA_H_

#include "battle/battle_common.h"
#include "system/procsys.h"

//shinka_status_flag
#define	SHINKA_STATUS_FLAG_CANCEL_ON	(0x00000001)	//進化キャンセルON
#define	SHINKA_STATUS_FLAG_BATTLE_MODE	(0x00000002)	//戦闘からの進化
#define	SHINKA_STATUS_FLAG_SIO_MODE		(0x00000004)	//通信からの進化

extern	SHINKA_WORK		*ShinkaInit(POKEPARTY *ppt,POKEMON_PARAM *pp,int after_mons_no,
									CONFIG *config,int contest_see_flag,ZUKAN_WORK *zw,MYITEM *my_item,
									RECORD *record,POKETCH_DATA *poketch_data,
									int shinka_cond,int shinka_status_flag,int heapID);
extern	BOOL			ShinkaEndCheck(SHINKA_WORK *sw);
extern	void			ShinkaEnd(SHINKA_WORK *sw);

#endif __SHINKA_H_
